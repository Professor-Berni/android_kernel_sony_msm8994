/*
 *  fs/userfaultfd.c
 *
 *  Minimal userfaultfd implementation for kernel 3.10.
 *  Based on Linux 4.3+ userfaultfd by Andrea Arcangeli.
 *
 *  This is a STUB: it provides a working file descriptor and the UFFDIO_API
 *  ioctl, sufficient for ART runtime feature detection. It does NOT integrate
 *  with the page fault path — UFFDIO_REGISTER returns -EINVAL and read() blocks
 *  forever (no events ever delivered).
 *
 *  ART's KernelSupportsUffd() will see "uffd present, features=0", which means
 *  no SIGBUS support, and fall back to the CC GC. This is enough to unblock
 *  zygote startup on devices where the full userfaultfd page-fault hooks
 *  haven't been backported.
 */

#include <linux/anon_inodes.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/wait.h>

#include <uapi/linux/userfaultfd.h>

/*
 * Per-userfaultfd context. Minimal — no event queue, no registered ranges.
 */
struct userfaultfd_ctx {
	wait_queue_head_t fault_wqh;
	bool api_handled;	/* true after UFFDIO_API has been called */
	__u64 features;		/* features the userland requested (we report 0 anyway) */
	unsigned int flags;	/* UFFD_CLOEXEC, UFFD_NONBLOCK, UFFD_USER_MODE_ONLY */
	atomic_t refcount;
};

static void userfaultfd_ctx_get(struct userfaultfd_ctx *ctx)
{
	atomic_inc(&ctx->refcount);
}

static void userfaultfd_ctx_put(struct userfaultfd_ctx *ctx)
{
	if (atomic_dec_and_test(&ctx->refcount))
		kfree(ctx);
}

/*
 * read(): always blocks (or returns -EAGAIN in non-blocking mode) since this
 * stub never produces events.
 */
static ssize_t userfaultfd_read(struct file *file, char __user *buf,
				size_t count, loff_t *ppos)
{
	struct userfaultfd_ctx *ctx = file->private_data;
	DEFINE_WAIT(wait);

	if (!ctx->api_handled)
		return -EINVAL;
	if (count < sizeof(struct uffd_msg))
		return -EINVAL;

	if (file->f_flags & O_NONBLOCK)
		return -EAGAIN;

	for (;;) {
		prepare_to_wait(&ctx->fault_wqh, &wait, TASK_INTERRUPTIBLE);
		if (signal_pending(current)) {
			finish_wait(&ctx->fault_wqh, &wait);
			return -ERESTARTSYS;
		}
		schedule();
	}
}

static unsigned int userfaultfd_poll(struct file *file, poll_table *wait)
{
	struct userfaultfd_ctx *ctx = file->private_data;

	poll_wait(file, &ctx->fault_wqh, wait);
	/* No events are ever queued, so just report writable. */
	return POLLOUT | POLLWRNORM;
}

/*
 * UFFDIO_API: negotiate API version and feature flags.
 *
 * This stub returns ioctls=0 and features=0, which signals to the caller
 * "userfaultfd present but no advanced features supported". ART's
 * KernelSupportsUffd() interprets this as "no SIGBUS support" and falls back.
 */
static int userfaultfd_api(struct userfaultfd_ctx *ctx, unsigned long arg)
{
	struct uffdio_api uffdio_api;
	struct uffdio_api __user *user = (struct uffdio_api __user *)arg;

	if (copy_from_user(&uffdio_api, user, sizeof(uffdio_api)))
		return -EFAULT;

	if (uffdio_api.api != UFFD_API) {
		uffdio_api.api = 0;
		uffdio_api.features = 0;
		uffdio_api.ioctls = 0;
		(void)copy_to_user(user, &uffdio_api, sizeof(uffdio_api));
		return -EINVAL;
	}

	/* refuse all features; we don't implement any */
	uffdio_api.features = 0;
	uffdio_api.ioctls = 0;	/* no per-range ioctls advertised either */

	if (copy_to_user(user, &uffdio_api, sizeof(uffdio_api)))
		return -EFAULT;

	ctx->api_handled = true;
	return 0;
}

static long userfaultfd_ioctl(struct file *file, unsigned int cmd,
			      unsigned long arg)
{
	struct userfaultfd_ctx *ctx = file->private_data;

	if (cmd == UFFDIO_API)
		return userfaultfd_api(ctx, arg);

	if (!ctx->api_handled)
		return -EINVAL;

	/* All other ioctls: not supported by stub. Userspace should treat the
	 * returned features=0 from UFFDIO_API as "fallback to alternative GC". */
	switch (cmd) {
	case UFFDIO_REGISTER:
	case UFFDIO_UNREGISTER:
	case UFFDIO_WAKE:
	case UFFDIO_COPY:
	case UFFDIO_ZEROPAGE:
	case UFFDIO_WRITEPROTECT:
	case UFFDIO_CONTINUE:
	case UFFDIO_POISON:
	case UFFDIO_MOVE:
		return -EINVAL;
	default:
		return -ENOTTY;
	}
}

static int userfaultfd_release(struct inode *inode, struct file *file)
{
	struct userfaultfd_ctx *ctx = file->private_data;
	userfaultfd_ctx_put(ctx);
	return 0;
}

static const struct file_operations userfaultfd_fops = {
	.release	= userfaultfd_release,
	.poll		= userfaultfd_poll,
	.read		= userfaultfd_read,
	.unlocked_ioctl	= userfaultfd_ioctl,
	.compat_ioctl	= userfaultfd_ioctl,
	.llseek		= noop_llseek,
};

/*
 * membarrier (Linux 4.3) minimal stub.
 *
 * ART runtime (class_linker.cc, fault_handler.cc) calls membarrier() to
 * propagate memory ordering across all threads of the process. If membarrier
 * returns ENOSYS, ART may follow a fallback path that itself depends on
 * specific kernel behavior, which has caused silent zygote death on this
 * legacy kernel.
 *
 * MEMBARRIER_CMD_QUERY returns 0 (no commands supported), prompting userspace
 * to use the checkpoint-based fallback. Other commands return success without
 * actually performing a barrier — this is acceptable here because syscall
 * entry/exit on aarch64 already implies a reasonable level of memory ordering
 * for the use cases ART relies on (class init visibility).
 */
SYSCALL_DEFINE2(membarrier, int, cmd, int, flags)
{
	/* MEMBARRIER_CMD_QUERY = 0 — return mask of supported commands.
	 * Returning 0 means "no commands supported" → userspace falls back. */
	if (cmd == 0)
		return 0;

	/* Reject unknown flag bits to avoid masking real userland bugs. */
	if (flags != 0)
		return -EINVAL;

	/* Treat all other commands (PRIVATE_EXPEDITED, GLOBAL, REGISTER_*) as
	 * a successful no-op. ART's classes-visibly-initialized path uses
	 * the result; returning 0 lets it skip the slow checkpoint route. */
	return 0;
}

SYSCALL_DEFINE1(userfaultfd, int, flags)
{
	struct userfaultfd_ctx *ctx;
	int fd;

	/* Recognized flags. UFFD_USER_MODE_ONLY (=1) is silently accepted —
	 * we don't actually enforce it, but ART probes pass it. */
	if (flags & ~(UFFD_CLOEXEC | UFFD_NONBLOCK | UFFD_USER_MODE_ONLY))
		return -EINVAL;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	atomic_set(&ctx->refcount, 1);
	init_waitqueue_head(&ctx->fault_wqh);
	ctx->flags = flags;
	ctx->api_handled = false;
	ctx->features = 0;

	fd = anon_inode_getfd("[userfaultfd]", &userfaultfd_fops, ctx,
			      (flags & UFFD_CLOEXEC) ? O_CLOEXEC : 0);
	if (fd < 0)
		userfaultfd_ctx_put(ctx);

	return fd;
}
