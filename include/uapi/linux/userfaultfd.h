/*
 * include/uapi/linux/userfaultfd.h
 *
 * Minimal userfaultfd UAPI for kernel 3.10. Based on Linux 4.3+
 * userfaultfd.h. Provides only what ART runtime probes during feature
 * detection (UFFD_API, UFFDIO_API ioctl, basic structs). Page fault handling
 * is NOT implemented — userfaultfd() returns a valid fd but reading events
 * always blocks/EOFs and UFFDIO_REGISTER returns -EINVAL.
 */

#ifndef _UAPI_LINUX_USERFAULTFD_H
#define _UAPI_LINUX_USERFAULTFD_H

#include <linux/types.h>

/* uffd flags accepted by the userfaultfd() syscall (third argument).
 * Only the ones ART uses are recognized; others rejected with -EINVAL. */
#define UFFD_CLOEXEC		O_CLOEXEC	/* same as O_CLOEXEC = 02000000 */
#define UFFD_NONBLOCK		O_NONBLOCK	/* same as O_NONBLOCK = 00004000 */
#define UFFD_USER_MODE_ONLY	1		/* restrict to user-mode faults */

/* API version negotiated via UFFDIO_API */
#define UFFD_API	((__u64)0xAA)

/* Feature bits returned by UFFDIO_API. This stub returns 0 (no features),
 * which lets ART's KernelSupportsUffd() cleanly conclude "uffd present but
 * unusable for sigbus mode" and fall back to CC GC. */
#define UFFD_FEATURE_PAGEFAULT_FLAG_WP		(1<<0)
#define UFFD_FEATURE_EVENT_FORK			(1<<1)
#define UFFD_FEATURE_EVENT_REMAP		(1<<2)
#define UFFD_FEATURE_EVENT_REMOVE		(1<<3)
#define UFFD_FEATURE_MISSING_HUGETLBFS		(1<<4)
#define UFFD_FEATURE_MISSING_SHMEM		(1<<5)
#define UFFD_FEATURE_EVENT_UNMAP		(1<<6)
#define UFFD_FEATURE_SIGBUS			(1<<7)
#define UFFD_FEATURE_THREAD_ID			(1<<8)
#define UFFD_FEATURE_MINOR_HUGETLBFS		(1<<9)
#define UFFD_FEATURE_MINOR_SHMEM		(1<<10)
#define UFFD_FEATURE_EXACT_ADDRESS		(1<<11)
#define UFFD_FEATURE_WP_HUGETLBFS_SHMEM		(1<<12)
#define UFFD_FEATURE_WP_UNPOPULATED		(1<<13)
#define UFFD_FEATURE_POISON			(1<<14)
#define UFFD_FEATURE_WP_ASYNC			(1<<15)
#define UFFD_FEATURE_MOVE			(1<<16)

/* Ioctls. The encoding matches upstream so binaries don't need recompilation. */
#define UFFDIO 0xAA
#define UFFDIO_API		_IOWR(UFFDIO, 0x3F, struct uffdio_api)
#define UFFDIO_REGISTER		_IOWR(UFFDIO, 0x00, struct uffdio_register)
#define UFFDIO_UNREGISTER	_IOR (UFFDIO, 0x01, struct uffdio_range)
#define UFFDIO_WAKE		_IOR (UFFDIO, 0x02, struct uffdio_range)
#define UFFDIO_COPY		_IOWR(UFFDIO, 0x03, struct uffdio_copy)
#define UFFDIO_ZEROPAGE		_IOWR(UFFDIO, 0x04, struct uffdio_zeropage)
#define UFFDIO_WRITEPROTECT	_IOWR(UFFDIO, 0x06, struct uffdio_writeprotect)
#define UFFDIO_CONTINUE		_IOWR(UFFDIO, 0x07, struct uffdio_continue)
#define UFFDIO_POISON		_IOWR(UFFDIO, 0x08, struct uffdio_poison)
#define UFFDIO_MOVE		_IOWR(UFFDIO, 0x05, struct uffdio_move)

struct uffdio_api {
	/* userland asks for an API version it supports */
	__u64 api;
	/* userland asks for which features it would like enabled */
	__u64 features;
	/* kernel returns which features are available */
	__u64 ioctls;
};

struct uffdio_range {
	__u64 start;
	__u64 len;
};

struct uffdio_register {
	struct uffdio_range range;
#define UFFDIO_REGISTER_MODE_MISSING	((__u64)1<<0)
#define UFFDIO_REGISTER_MODE_WP		((__u64)1<<1)
#define UFFDIO_REGISTER_MODE_MINOR	((__u64)1<<2)
	__u64 mode;
	/* output: ioctls available on the registered range */
	__u64 ioctls;
};

struct uffdio_copy {
	__u64 dst;
	__u64 src;
	__u64 len;
#define UFFDIO_COPY_MODE_DONTWAKE	((__u64)1<<0)
#define UFFDIO_COPY_MODE_WP		((__u64)1<<1)
	__u64 mode;
	/* output: bytes copied so far, or -errno on failure */
	__s64 copy;
};

struct uffdio_zeropage {
	struct uffdio_range range;
#define UFFDIO_ZEROPAGE_MODE_DONTWAKE	((__u64)1<<0)
	__u64 mode;
	__s64 zeropage;
};

struct uffdio_writeprotect {
	struct uffdio_range range;
#define UFFDIO_WRITEPROTECT_MODE_WP	((__u64)1<<0)
#define UFFDIO_WRITEPROTECT_MODE_DONTWAKE	((__u64)1<<1)
	__u64 mode;
};

struct uffdio_continue {
	struct uffdio_range range;
#define UFFDIO_CONTINUE_MODE_DONTWAKE	((__u64)1<<0)
	__u64 mode;
	__s64 mapped;
};

struct uffdio_poison {
	struct uffdio_range range;
#define UFFDIO_POISON_MODE_DONTWAKE	((__u64)1<<0)
	__u64 mode;
	__s64 updated;
};

struct uffdio_move {
	__u64 dst;
	__u64 src;
	__u64 len;
#define UFFDIO_MOVE_MODE_DONTWAKE	((__u64)1<<0)
#define UFFDIO_MOVE_MODE_ALLOW_SRC_HOLES	((__u64)1<<1)
	__u64 mode;
	__s64 move;
};

/* uffd events read() returns. The stub never produces events, but the structs
 * are defined for ABI compatibility. */
struct uffd_msg {
	__u8 event;
	__u8 reserved1;
	__u16 reserved2;
	__u32 reserved3;
	union {
		struct { __u64 flags; __u64 address; __u32 ptid; } pagefault;
		struct { __u32 ufd; } fork;
		struct { __u64 from; __u64 to; __u64 len; } remap;
		struct { __u64 start; __u64 end; } remove;
		struct { __u64 reserved1; __u64 reserved2; __u64 reserved3; } reserved;
	} arg;
} __attribute__((packed));

#define UFFD_EVENT_PAGEFAULT	0x12
#define UFFD_EVENT_FORK		0x13
#define UFFD_EVENT_REMAP	0x14
#define UFFD_EVENT_REMOVE	0x15
#define UFFD_EVENT_UNMAP	0x16

#endif /* _UAPI_LINUX_USERFAULTFD_H */
