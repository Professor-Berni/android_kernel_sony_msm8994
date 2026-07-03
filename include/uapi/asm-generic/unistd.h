#include <asm/bitsperlong.h>

/*
 * This file contains the system call numbers, based on the
 * layout of the x86-64 architecture, which embeds the
 * pointer to the syscall in the table.
 *
 * As a basic principle, no duplication of functionality
 * should be added, e.g. we don't use lseek when llseek
 * is present. New architectures should use this file
 * and implement the less feature-full calls in user space.
 */

#ifndef __SYSCALL
#define __SYSCALL(x, y)
#endif

#if __BITS_PER_LONG == 32 || defined(__SYSCALL_COMPAT)
#define __SC_3264(_nr, _32, _64) __SYSCALL(_nr, _32)
#else
#define __SC_3264(_nr, _32, _64) __SYSCALL(_nr, _64)
#endif

#ifdef __SYSCALL_COMPAT
#define __SC_COMP(_nr, _sys, _comp) __SYSCALL(_nr, _comp)
#define __SC_COMP_3264(_nr, _32, _64, _comp) __SYSCALL(_nr, _comp)
#else
#define __SC_COMP(_nr, _sys, _comp) __SYSCALL(_nr, _sys)
#define __SC_COMP_3264(_nr, _32, _64, _comp) __SC_3264(_nr, _32, _64)
#endif

#define __NR_io_setup 0
__SC_COMP(__NR_io_setup, sys_io_setup, compat_sys_io_setup)
#define __NR_io_destroy 1
__SYSCALL(__NR_io_destroy, sys_io_destroy)
#define __NR_io_submit 2
__SC_COMP(__NR_io_submit, sys_io_submit, compat_sys_io_submit)
#define __NR_io_cancel 3
__SYSCALL(__NR_io_cancel, sys_io_cancel)
#define __NR_io_getevents 4
__SC_COMP(__NR_io_getevents, sys_io_getevents, compat_sys_io_getevents)

/* fs/xattr.c */
#define __NR_setxattr 5
__SYSCALL(__NR_setxattr, sys_setxattr)
#define __NR_lsetxattr 6
__SYSCALL(__NR_lsetxattr, sys_lsetxattr)
#define __NR_fsetxattr 7
__SYSCALL(__NR_fsetxattr, sys_fsetxattr)
#define __NR_getxattr 8
__SYSCALL(__NR_getxattr, sys_getxattr)
#define __NR_lgetxattr 9
__SYSCALL(__NR_lgetxattr, sys_lgetxattr)
#define __NR_fgetxattr 10
__SYSCALL(__NR_fgetxattr, sys_fgetxattr)
#define __NR_listxattr 11
__SYSCALL(__NR_listxattr, sys_listxattr)
#define __NR_llistxattr 12
__SYSCALL(__NR_llistxattr, sys_llistxattr)
#define __NR_flistxattr 13
__SYSCALL(__NR_flistxattr, sys_flistxattr)
#define __NR_removexattr 14
__SYSCALL(__NR_removexattr, sys_removexattr)
#define __NR_lremovexattr 15
__SYSCALL(__NR_lremovexattr, sys_lremovexattr)
#define __NR_fremovexattr 16
__SYSCALL(__NR_fremovexattr, sys_fremovexattr)

/* fs/dcache.c */
#define __NR_getcwd 17
__SYSCALL(__NR_getcwd, sys_getcwd)

/* fs/cookies.c */
#define __NR_lookup_dcookie 18
__SC_COMP(__NR_lookup_dcookie, sys_lookup_dcookie, compat_sys_lookup_dcookie)

/* fs/eventfd.c */
#define __NR_eventfd2 19
__SYSCALL(__NR_eventfd2, sys_eventfd2)

/* fs/eventpoll.c */
#define __NR_epoll_create1 20
__SYSCALL(__NR_epoll_create1, sys_epoll_create1)
#define __NR_epoll_ctl 21
__SYSCALL(__NR_epoll_ctl, sys_epoll_ctl)
#define __NR_epoll_pwait 22
__SC_COMP(__NR_epoll_pwait, sys_epoll_pwait, compat_sys_epoll_pwait)

/* fs/fcntl.c */
#define __NR_dup 23
__SYSCALL(__NR_dup, sys_dup)
#define __NR_dup3 24
__SYSCALL(__NR_dup3, sys_dup3)
#define __NR3264_fcntl 25
__SC_COMP_3264(__NR3264_fcntl, sys_fcntl64, sys_fcntl, compat_sys_fcntl64)

/* fs/inotify_user.c */
#define __NR_inotify_init1 26
__SYSCALL(__NR_inotify_init1, sys_inotify_init1)
#define __NR_inotify_add_watch 27
__SYSCALL(__NR_inotify_add_watch, sys_inotify_add_watch)
#define __NR_inotify_rm_watch 28
__SYSCALL(__NR_inotify_rm_watch, sys_inotify_rm_watch)

/* fs/ioctl.c */
#define __NR_ioctl 29
__SC_COMP(__NR_ioctl, sys_ioctl, compat_sys_ioctl)

/* fs/ioprio.c */
#define __NR_ioprio_set 30
__SYSCALL(__NR_ioprio_set, sys_ioprio_set)
#define __NR_ioprio_get 31
__SYSCALL(__NR_ioprio_get, sys_ioprio_get)

/* fs/locks.c */
#define __NR_flock 32
__SYSCALL(__NR_flock, sys_flock)

/* fs/namei.c */
#define __NR_mknodat 33
__SYSCALL(__NR_mknodat, sys_mknodat)
#define __NR_mkdirat 34
__SYSCALL(__NR_mkdirat, sys_mkdirat)
#define __NR_unlinkat 35
__SYSCALL(__NR_unlinkat, sys_unlinkat)
#define __NR_symlinkat 36
__SYSCALL(__NR_symlinkat, sys_symlinkat)
#define __NR_linkat 37
__SYSCALL(__NR_linkat, sys_linkat)
#define __NR_renameat 38
__SYSCALL(__NR_renameat, sys_renameat)

/* fs/namespace.c */
#define __NR_umount2 39
__SYSCALL(__NR_umount2, sys_umount)
#define __NR_mount 40
__SC_COMP(__NR_mount, sys_mount, compat_sys_mount)
#define __NR_pivot_root 41
__SYSCALL(__NR_pivot_root, sys_pivot_root)

/* fs/nfsctl.c */
#define __NR_nfsservctl 42
__SYSCALL(__NR_nfsservctl, sys_ni_syscall)

/* fs/open.c */
#define __NR3264_statfs 43
__SC_COMP_3264(__NR3264_statfs, sys_statfs64, sys_statfs, \
	       compat_sys_statfs64)
#define __NR3264_fstatfs 44
__SC_COMP_3264(__NR3264_fstatfs, sys_fstatfs64, sys_fstatfs, \
	       compat_sys_fstatfs64)
#define __NR3264_truncate 45
__SC_COMP_3264(__NR3264_truncate, sys_truncate64, sys_truncate, \
	       compat_sys_truncate64)
#define __NR3264_ftruncate 46
__SC_COMP_3264(__NR3264_ftruncate, sys_ftruncate64, sys_ftruncate, \
	       compat_sys_ftruncate64)

#define __NR_fallocate 47
__SC_COMP(__NR_fallocate, sys_fallocate, compat_sys_fallocate)
#define __NR_faccessat 48
__SYSCALL(__NR_faccessat, sys_faccessat)
#define __NR_chdir 49
__SYSCALL(__NR_chdir, sys_chdir)
#define __NR_fchdir 50
__SYSCALL(__NR_fchdir, sys_fchdir)
#define __NR_chroot 51
__SYSCALL(__NR_chroot, sys_chroot)
#define __NR_fchmod 52
__SYSCALL(__NR_fchmod, sys_fchmod)
#define __NR_fchmodat 53
__SYSCALL(__NR_fchmodat, sys_fchmodat)
#define __NR_fchownat 54
__SYSCALL(__NR_fchownat, sys_fchownat)
#define __NR_fchown 55
__SYSCALL(__NR_fchown, sys_fchown)
#define __NR_openat 56
__SC_COMP(__NR_openat, sys_openat, compat_sys_openat)
#define __NR_close 57
__SYSCALL(__NR_close, sys_close)
#define __NR_vhangup 58
__SYSCALL(__NR_vhangup, sys_vhangup)

/* fs/pipe.c */
#define __NR_pipe2 59
__SYSCALL(__NR_pipe2, sys_pipe2)

/* fs/quota.c */
#define __NR_quotactl 60
__SYSCALL(__NR_quotactl, sys_quotactl)

/* fs/readdir.c */
#define __NR_getdents64 61
#define __ARCH_WANT_COMPAT_SYS_GETDENTS64
__SC_COMP(__NR_getdents64, sys_getdents64, compat_sys_getdents64)

/* fs/read_write.c */
#define __NR3264_lseek 62
__SC_3264(__NR3264_lseek, sys_llseek, sys_lseek)
#define __NR_read 63
__SYSCALL(__NR_read, sys_read)
#define __NR_write 64
__SYSCALL(__NR_write, sys_write)
#define __NR_readv 65
__SC_COMP(__NR_readv, sys_readv, compat_sys_readv)
#define __NR_writev 66
__SC_COMP(__NR_writev, sys_writev, compat_sys_writev)
#define __NR_pread64 67
__SC_COMP(__NR_pread64, sys_pread64, compat_sys_pread64)
#define __NR_pwrite64 68
__SC_COMP(__NR_pwrite64, sys_pwrite64, compat_sys_pwrite64)
#define __NR_preadv 69
__SC_COMP(__NR_preadv, sys_preadv, compat_sys_preadv)
#define __NR_pwritev 70
__SC_COMP(__NR_pwritev, sys_pwritev, compat_sys_pwritev)

/* fs/sendfile.c */
#define __NR3264_sendfile 71
__SYSCALL(__NR3264_sendfile, sys_sendfile64)

/* fs/select.c */
#define __NR_pselect6 72
__SC_COMP(__NR_pselect6, sys_pselect6, compat_sys_pselect6)
#define __NR_ppoll 73
__SC_COMP(__NR_ppoll, sys_ppoll, compat_sys_ppoll)

/* fs/signalfd.c */
#define __NR_signalfd4 74
__SC_COMP(__NR_signalfd4, sys_signalfd4, compat_sys_signalfd4)

/* fs/splice.c */
#define __NR_vmsplice 75
__SC_COMP(__NR_vmsplice, sys_vmsplice, compat_sys_vmsplice)
#define __NR_splice 76
__SYSCALL(__NR_splice, sys_splice)
#define __NR_tee 77
__SYSCALL(__NR_tee, sys_tee)

/* fs/stat.c */
#define __NR_readlinkat 78
__SYSCALL(__NR_readlinkat, sys_readlinkat)
#define __NR3264_fstatat 79
__SC_3264(__NR3264_fstatat, sys_fstatat64, sys_newfstatat)
#define __NR3264_fstat 80
__SC_3264(__NR3264_fstat, sys_fstat64, sys_newfstat)

/* fs/sync.c */
#define __NR_sync 81
__SYSCALL(__NR_sync, sys_sync)
#define __NR_fsync 82
__SYSCALL(__NR_fsync, sys_fsync)
#define __NR_fdatasync 83
__SYSCALL(__NR_fdatasync, sys_fdatasync)
#ifdef __ARCH_WANT_SYNC_FILE_RANGE2
#define __NR_sync_file_range2 84
__SC_COMP(__NR_sync_file_range2, sys_sync_file_range2, \
	  compat_sys_sync_file_range2)
#else
#define __NR_sync_file_range 84
__SC_COMP(__NR_sync_file_range, sys_sync_file_range, \
	  compat_sys_sync_file_range)
#endif

/* fs/timerfd.c */
#define __NR_timerfd_create 85
__SYSCALL(__NR_timerfd_create, sys_timerfd_create)
#define __NR_timerfd_settime 86
__SC_COMP(__NR_timerfd_settime, sys_timerfd_settime, \
	  compat_sys_timerfd_settime)
#define __NR_timerfd_gettime 87
__SC_COMP(__NR_timerfd_gettime, sys_timerfd_gettime, \
	  compat_sys_timerfd_gettime)

/* fs/utimes.c */
#define __NR_utimensat 88
__SC_COMP(__NR_utimensat, sys_utimensat, compat_sys_utimensat)

/* kernel/acct.c */
#define __NR_acct 89
__SYSCALL(__NR_acct, sys_acct)

/* kernel/capability.c */
#define __NR_capget 90
__SYSCALL(__NR_capget, sys_capget)
#define __NR_capset 91
__SYSCALL(__NR_capset, sys_capset)

/* kernel/exec_domain.c */
#define __NR_personality 92
__SYSCALL(__NR_personality, sys_personality)

/* kernel/exit.c */
#define __NR_exit 93
__SYSCALL(__NR_exit, sys_exit)
#define __NR_exit_group 94
__SYSCALL(__NR_exit_group, sys_exit_group)
#define __NR_waitid 95
__SC_COMP(__NR_waitid, sys_waitid, compat_sys_waitid)

/* kernel/fork.c */
#define __NR_set_tid_address 96
__SYSCALL(__NR_set_tid_address, sys_set_tid_address)
#define __NR_unshare 97
__SYSCALL(__NR_unshare, sys_unshare)

/* kernel/futex.c */
#define __NR_futex 98
__SC_COMP(__NR_futex, sys_futex, compat_sys_futex)
#define __NR_set_robust_list 99
__SC_COMP(__NR_set_robust_list, sys_set_robust_list, \
	  compat_sys_set_robust_list)
#define __NR_get_robust_list 100
__SC_COMP(__NR_get_robust_list, sys_get_robust_list, \
	  compat_sys_get_robust_list)

/* kernel/hrtimer.c */
#define __NR_nanosleep 101
__SC_COMP(__NR_nanosleep, sys_nanosleep, compat_sys_nanosleep)

/* kernel/itimer.c */
#define __NR_getitimer 102
__SC_COMP(__NR_getitimer, sys_getitimer, compat_sys_getitimer)
#define __NR_setitimer 103
__SC_COMP(__NR_setitimer, sys_setitimer, compat_sys_setitimer)

/* kernel/kexec.c */
#define __NR_kexec_load 104
__SC_COMP(__NR_kexec_load, sys_kexec_load, compat_sys_kexec_load)

/* kernel/module.c */
#define __NR_init_module 105
__SYSCALL(__NR_init_module, sys_init_module)
#define __NR_delete_module 106
__SYSCALL(__NR_delete_module, sys_delete_module)

/* kernel/posix-timers.c */
#define __NR_timer_create 107
__SC_COMP(__NR_timer_create, sys_timer_create, compat_sys_timer_create)
#define __NR_timer_gettime 108
__SC_COMP(__NR_timer_gettime, sys_timer_gettime, compat_sys_timer_gettime)
#define __NR_timer_getoverrun 109
__SYSCALL(__NR_timer_getoverrun, sys_timer_getoverrun)
#define __NR_timer_settime 110
__SC_COMP(__NR_timer_settime, sys_timer_settime, compat_sys_timer_settime)
#define __NR_timer_delete 111
__SYSCALL(__NR_timer_delete, sys_timer_delete)
#define __NR_clock_settime 112
__SC_COMP(__NR_clock_settime, sys_clock_settime, compat_sys_clock_settime)
#define __NR_clock_gettime 113
__SC_COMP(__NR_clock_gettime, sys_clock_gettime, compat_sys_clock_gettime)
#define __NR_clock_getres 114
__SC_COMP(__NR_clock_getres, sys_clock_getres, compat_sys_clock_getres)
#define __NR_clock_nanosleep 115
__SC_COMP(__NR_clock_nanosleep, sys_clock_nanosleep, \
	  compat_sys_clock_nanosleep)

/* kernel/printk.c */
#define __NR_syslog 116
__SYSCALL(__NR_syslog, sys_syslog)

/* kernel/ptrace.c */
#define __NR_ptrace 117
__SYSCALL(__NR_ptrace, sys_ptrace)

/* kernel/sched.c */
#define __NR_sched_setparam 118
__SYSCALL(__NR_sched_setparam, sys_sched_setparam)
#define __NR_sched_setscheduler 119
__SYSCALL(__NR_sched_setscheduler, sys_sched_setscheduler)
#define __NR_sched_getscheduler 120
__SYSCALL(__NR_sched_getscheduler, sys_sched_getscheduler)
#define __NR_sched_getparam 121
__SYSCALL(__NR_sched_getparam, sys_sched_getparam)
#define __NR_sched_setaffinity 122
__SC_COMP(__NR_sched_setaffinity, sys_sched_setaffinity, \
	  compat_sys_sched_setaffinity)
#define __NR_sched_getaffinity 123
__SC_COMP(__NR_sched_getaffinity, sys_sched_getaffinity, \
	  compat_sys_sched_getaffinity)
#define __NR_sched_yield 124
__SYSCALL(__NR_sched_yield, sys_sched_yield)
#define __NR_sched_get_priority_max 125
__SYSCALL(__NR_sched_get_priority_max, sys_sched_get_priority_max)
#define __NR_sched_get_priority_min 126
__SYSCALL(__NR_sched_get_priority_min, sys_sched_get_priority_min)
#define __NR_sched_rr_get_interval 127
__SC_COMP(__NR_sched_rr_get_interval, sys_sched_rr_get_interval, \
	  compat_sys_sched_rr_get_interval)

/* kernel/signal.c */
#define __NR_restart_syscall 128
__SYSCALL(__NR_restart_syscall, sys_restart_syscall)
#define __NR_kill 129
__SYSCALL(__NR_kill, sys_kill)
#define __NR_tkill 130
__SYSCALL(__NR_tkill, sys_tkill)
#define __NR_tgkill 131
__SYSCALL(__NR_tgkill, sys_tgkill)
#define __NR_sigaltstack 132
__SC_COMP(__NR_sigaltstack, sys_sigaltstack, compat_sys_sigaltstack)
#define __NR_rt_sigsuspend 133
__SC_COMP(__NR_rt_sigsuspend, sys_rt_sigsuspend, compat_sys_rt_sigsuspend)
#define __NR_rt_sigaction 134
__SC_COMP(__NR_rt_sigaction, sys_rt_sigaction, compat_sys_rt_sigaction)
#define __NR_rt_sigprocmask 135
__SC_COMP(__NR_rt_sigprocmask, sys_rt_sigprocmask, compat_sys_rt_sigprocmask)
#define __NR_rt_sigpending 136
__SC_COMP(__NR_rt_sigpending, sys_rt_sigpending, compat_sys_rt_sigpending)
#define __NR_rt_sigtimedwait 137
__SC_COMP(__NR_rt_sigtimedwait, sys_rt_sigtimedwait, \
	  compat_sys_rt_sigtimedwait)
#define __NR_rt_sigqueueinfo 138
__SC_COMP(__NR_rt_sigqueueinfo, sys_rt_sigqueueinfo, \
	  compat_sys_rt_sigqueueinfo)
#define __NR_rt_sigreturn 139
__SC_COMP(__NR_rt_sigreturn, sys_rt_sigreturn, compat_sys_rt_sigreturn)

/* kernel/sys.c */
#define __NR_setpriority 140
__SYSCALL(__NR_setpriority, sys_setpriority)
#define __NR_getpriority 141
__SYSCALL(__NR_getpriority, sys_getpriority)
#define __NR_reboot 142
__SYSCALL(__NR_reboot, sys_reboot)
#define __NR_setregid 143
__SYSCALL(__NR_setregid, sys_setregid)
#define __NR_setgid 144
__SYSCALL(__NR_setgid, sys_setgid)
#define __NR_setreuid 145
__SYSCALL(__NR_setreuid, sys_setreuid)
#define __NR_setuid 146
__SYSCALL(__NR_setuid, sys_setuid)
#define __NR_setresuid 147
__SYSCALL(__NR_setresuid, sys_setresuid)
#define __NR_getresuid 148
__SYSCALL(__NR_getresuid, sys_getresuid)
#define __NR_setresgid 149
__SYSCALL(__NR_setresgid, sys_setresgid)
#define __NR_getresgid 150
__SYSCALL(__NR_getresgid, sys_getresgid)
#define __NR_setfsuid 151
__SYSCALL(__NR_setfsuid, sys_setfsuid)
#define __NR_setfsgid 152
__SYSCALL(__NR_setfsgid, sys_setfsgid)
#define __NR_times 153
__SC_COMP(__NR_times, sys_times, compat_sys_times)
#define __NR_setpgid 154
__SYSCALL(__NR_setpgid, sys_setpgid)
#define __NR_getpgid 155
__SYSCALL(__NR_getpgid, sys_getpgid)
#define __NR_getsid 156
__SYSCALL(__NR_getsid, sys_getsid)
#define __NR_setsid 157
__SYSCALL(__NR_setsid, sys_setsid)
#define __NR_getgroups 158
__SYSCALL(__NR_getgroups, sys_getgroups)
#define __NR_setgroups 159
__SYSCALL(__NR_setgroups, sys_setgroups)
#define __NR_uname 160
__SYSCALL(__NR_uname, sys_newuname)
#define __NR_sethostname 161
__SYSCALL(__NR_sethostname, sys_sethostname)
#define __NR_setdomainname 162
__SYSCALL(__NR_setdomainname, sys_setdomainname)
#define __NR_getrlimit 163
__SC_COMP(__NR_getrlimit, sys_getrlimit, compat_sys_getrlimit)
#define __NR_setrlimit 164
__SC_COMP(__NR_setrlimit, sys_setrlimit, compat_sys_setrlimit)
#define __NR_getrusage 165
__SC_COMP(__NR_getrusage, sys_getrusage, compat_sys_getrusage)
#define __NR_umask 166
__SYSCALL(__NR_umask, sys_umask)
#define __NR_prctl 167
__SYSCALL(__NR_prctl, sys_prctl)
#define __NR_getcpu 168
__SYSCALL(__NR_getcpu, sys_getcpu)

/* kernel/time.c */
#define __NR_gettimeofday 169
__SC_COMP(__NR_gettimeofday, sys_gettimeofday, compat_sys_gettimeofday)
#define __NR_settimeofday 170
__SC_COMP(__NR_settimeofday, sys_settimeofday, compat_sys_settimeofday)
#define __NR_adjtimex 171
__SC_COMP(__NR_adjtimex, sys_adjtimex, compat_sys_adjtimex)

/* kernel/timer.c */
#define __NR_getpid 172
__SYSCALL(__NR_getpid, sys_getpid)
#define __NR_getppid 173
__SYSCALL(__NR_getppid, sys_getppid)
#define __NR_getuid 174
__SYSCALL(__NR_getuid, sys_getuid)
#define __NR_geteuid 175
__SYSCALL(__NR_geteuid, sys_geteuid)
#define __NR_getgid 176
__SYSCALL(__NR_getgid, sys_getgid)
#define __NR_getegid 177
__SYSCALL(__NR_getegid, sys_getegid)
#define __NR_gettid 178
__SYSCALL(__NR_gettid, sys_gettid)
#define __NR_sysinfo 179
__SC_COMP(__NR_sysinfo, sys_sysinfo, compat_sys_sysinfo)

/* ipc/mqueue.c */
#define __NR_mq_open 180
__SC_COMP(__NR_mq_open, sys_mq_open, compat_sys_mq_open)
#define __NR_mq_unlink 181
__SYSCALL(__NR_mq_unlink, sys_mq_unlink)
#define __NR_mq_timedsend 182
__SC_COMP(__NR_mq_timedsend, sys_mq_timedsend, compat_sys_mq_timedsend)
#define __NR_mq_timedreceive 183
__SC_COMP(__NR_mq_timedreceive, sys_mq_timedreceive, \
	  compat_sys_mq_timedreceive)
#define __NR_mq_notify 184
__SC_COMP(__NR_mq_notify, sys_mq_notify, compat_sys_mq_notify)
#define __NR_mq_getsetattr 185
__SC_COMP(__NR_mq_getsetattr, sys_mq_getsetattr, compat_sys_mq_getsetattr)

/* ipc/msg.c */
#define __NR_msgget 186
__SYSCALL(__NR_msgget, sys_msgget)
#define __NR_msgctl 187
__SC_COMP(__NR_msgctl, sys_msgctl, compat_sys_msgctl)
#define __NR_msgrcv 188
__SC_COMP(__NR_msgrcv, sys_msgrcv, compat_sys_msgrcv)
#define __NR_msgsnd 189
__SC_COMP(__NR_msgsnd, sys_msgsnd, compat_sys_msgsnd)

/* ipc/sem.c */
#define __NR_semget 190
__SYSCALL(__NR_semget, sys_semget)
#define __NR_semctl 191
__SC_COMP(__NR_semctl, sys_semctl, compat_sys_semctl)
#define __NR_semtimedop 192
__SC_COMP(__NR_semtimedop, sys_semtimedop, compat_sys_semtimedop)
#define __NR_semop 193
__SYSCALL(__NR_semop, sys_semop)

/* ipc/shm.c */
#define __NR_shmget 194
__SYSCALL(__NR_shmget, sys_shmget)
#define __NR_shmctl 195
__SC_COMP(__NR_shmctl, sys_shmctl, compat_sys_shmctl)
#define __NR_shmat 196
__SC_COMP(__NR_shmat, sys_shmat, compat_sys_shmat)
#define __NR_shmdt 197
__SYSCALL(__NR_shmdt, sys_shmdt)

/* net/socket.c */
#define __NR_socket 198
__SYSCALL(__NR_socket, sys_socket)
#define __NR_socketpair 199
__SYSCALL(__NR_socketpair, sys_socketpair)
#define __NR_bind 200
__SYSCALL(__NR_bind, sys_bind)
#define __NR_listen 201
__SYSCALL(__NR_listen, sys_listen)
#define __NR_accept 202
__SYSCALL(__NR_accept, sys_accept)
#define __NR_connect 203
__SYSCALL(__NR_connect, sys_connect)
#define __NR_getsockname 204
__SYSCALL(__NR_getsockname, sys_getsockname)
#define __NR_getpeername 205
__SYSCALL(__NR_getpeername, sys_getpeername)
#define __NR_sendto 206
__SYSCALL(__NR_sendto, sys_sendto)
#define __NR_recvfrom 207
__SC_COMP(__NR_recvfrom, sys_recvfrom, compat_sys_recvfrom)
#define __NR_setsockopt 208
__SC_COMP(__NR_setsockopt, sys_setsockopt, compat_sys_setsockopt)
#define __NR_getsockopt 209
__SC_COMP(__NR_getsockopt, sys_getsockopt, compat_sys_getsockopt)
#define __NR_shutdown 210
__SYSCALL(__NR_shutdown, sys_shutdown)
#define __NR_sendmsg 211
__SC_COMP(__NR_sendmsg, sys_sendmsg, compat_sys_sendmsg)
#define __NR_recvmsg 212
__SC_COMP(__NR_recvmsg, sys_recvmsg, compat_sys_recvmsg)

/* mm/filemap.c */
#define __NR_readahead 213
__SC_COMP(__NR_readahead, sys_readahead, compat_sys_readahead)

/* mm/nommu.c, also with MMU */
#define __NR_brk 214
__SYSCALL(__NR_brk, sys_brk)
#define __NR_munmap 215
__SYSCALL(__NR_munmap, sys_munmap)
#define __NR_mremap 216
__SYSCALL(__NR_mremap, sys_mremap)

/* security/keys/keyctl.c */
#define __NR_add_key 217
__SYSCALL(__NR_add_key, sys_add_key)
#define __NR_request_key 218
__SYSCALL(__NR_request_key, sys_request_key)
#define __NR_keyctl 219
__SC_COMP(__NR_keyctl, sys_keyctl, compat_sys_keyctl)

/* arch/example/kernel/sys_example.c */
#define __NR_clone 220
__SYSCALL(__NR_clone, sys_clone)
#define __NR_execve 221
__SC_COMP(__NR_execve, sys_execve, compat_sys_execve)

#define __NR3264_mmap 222
__SC_3264(__NR3264_mmap, sys_mmap2, sys_mmap)
/* mm/fadvise.c */
#define __NR3264_fadvise64 223
__SC_COMP(__NR3264_fadvise64, sys_fadvise64_64, compat_sys_fadvise64_64)

/* mm/, CONFIG_MMU only */
#ifndef __ARCH_NOMMU
#define __NR_swapon 224
__SYSCALL(__NR_swapon, sys_swapon)
#define __NR_swapoff 225
__SYSCALL(__NR_swapoff, sys_swapoff)
#define __NR_mprotect 226
__SYSCALL(__NR_mprotect, sys_mprotect)
#define __NR_msync 227
__SYSCALL(__NR_msync, sys_msync)
#define __NR_mlock 228
__SYSCALL(__NR_mlock, sys_mlock)
#define __NR_munlock 229
__SYSCALL(__NR_munlock, sys_munlock)
#define __NR_mlockall 230
__SYSCALL(__NR_mlockall, sys_mlockall)
#define __NR_munlockall 231
__SYSCALL(__NR_munlockall, sys_munlockall)
#define __NR_mincore 232
__SYSCALL(__NR_mincore, sys_mincore)
#define __NR_madvise 233
__SYSCALL(__NR_madvise, sys_madvise)
#define __NR_remap_file_pages 234
__SYSCALL(__NR_remap_file_pages, sys_remap_file_pages)
#define __NR_mbind 235
__SC_COMP(__NR_mbind, sys_mbind, compat_sys_mbind)
#define __NR_get_mempolicy 236
__SC_COMP(__NR_get_mempolicy, sys_get_mempolicy, compat_sys_get_mempolicy)
#define __NR_set_mempolicy 237
__SC_COMP(__NR_set_mempolicy, sys_set_mempolicy, compat_sys_set_mempolicy)
#define __NR_migrate_pages 238
__SC_COMP(__NR_migrate_pages, sys_migrate_pages, compat_sys_migrate_pages)
#define __NR_move_pages 239
__SC_COMP(__NR_move_pages, sys_move_pages, compat_sys_move_pages)
#endif

#define __NR_rt_tgsigqueueinfo 240
__SC_COMP(__NR_rt_tgsigqueueinfo, sys_rt_tgsigqueueinfo, \
	  compat_sys_rt_tgsigqueueinfo)
#define __NR_perf_event_open 241
__SYSCALL(__NR_perf_event_open, sys_perf_event_open)
#define __NR_accept4 242
__SYSCALL(__NR_accept4, sys_accept4)
#define __NR_recvmmsg 243
__SC_COMP(__NR_recvmmsg, sys_recvmmsg, compat_sys_recvmmsg)

/*
 * Architectures may provide up to 16 syscalls of their own
 * starting with this value.
 */
#define __NR_arch_specific_syscall 244

#define __NR_wait4 260
__SC_COMP(__NR_wait4, sys_wait4, compat_sys_wait4)
#define __NR_prlimit64 261
__SYSCALL(__NR_prlimit64, sys_prlimit64)
#define __NR_fanotify_init 262
__SYSCALL(__NR_fanotify_init, sys_fanotify_init)
#define __NR_fanotify_mark 263
__SYSCALL(__NR_fanotify_mark, sys_fanotify_mark)
#define __NR_name_to_handle_at         264
__SYSCALL(__NR_name_to_handle_at, sys_name_to_handle_at)
#define __NR_open_by_handle_at         265
__SC_COMP(__NR_open_by_handle_at, sys_open_by_handle_at, \
	  compat_sys_open_by_handle_at)
#define __NR_clock_adjtime 266
__SC_COMP(__NR_clock_adjtime, sys_clock_adjtime, compat_sys_clock_adjtime)
#define __NR_syncfs 267
__SYSCALL(__NR_syncfs, sys_syncfs)
#define __NR_setns 268
__SYSCALL(__NR_setns, sys_setns)
#define __NR_sendmmsg 269
__SC_COMP(__NR_sendmmsg, sys_sendmmsg, compat_sys_sendmmsg)
#define __NR_process_vm_readv 270
__SC_COMP(__NR_process_vm_readv, sys_process_vm_readv, \
          compat_sys_process_vm_readv)
#define __NR_process_vm_writev 271
__SC_COMP(__NR_process_vm_writev, sys_process_vm_writev, \
          compat_sys_process_vm_writev)
#define __NR_kcmp 272
__SYSCALL(__NR_kcmp, sys_kcmp)
#define __NR_finit_module 273
__SYSCALL(__NR_finit_module, sys_finit_module)
/* Backporting seccomp: sched_setattr/getattr (274/275) are intentionally left
 * as sys_ni_syscall — not implemented on this kernel. */

/* Expose renameat2 (276); the implementation already exists in fs/namei.c.
 * Without it userspace gets ENOSYS, breaking persistent property writes,
 * installd layout updates, and other rename-with-flags users. */
#define __NR_renameat2 276
__SYSCALL(__NR_renameat2, sys_renameat2)

#define __NR_seccomp 277
__SYSCALL(__NR_seccomp, sys_seccomp)
#define __NR_getrandom 278
__SYSCALL(__NR_getrandom, sys_getrandom)
#define __NR_memfd_create 279
__SYSCALL(__NR_memfd_create, sys_memfd_create)

#undef __NR_syscalls
#define __NR_execveat 281
__SC_COMP(__NR_execveat, sys_execveat, compat_sys_execveat)

#define __NR_userfaultfd 282
/* minimal userfaultfd stub (fs/userfaultfd.c): returns a valid fd;
 * UFFDIO_API works (features=0); other ioctls return -EINVAL. Sufficient
 * for ART feature detection on kernel 3.10. */
__SYSCALL(__NR_userfaultfd, sys_userfaultfd)
#define __NR_membarrier 283
/* minimal membarrier stub (fs/userfaultfd.c) */
__SYSCALL(__NR_membarrier, sys_membarrier)
#define __NR_mlock2 284
__SYSCALL(__NR_mlock2, sys_ni_syscall)
#define __NR_copy_file_range 285
__SYSCALL(__NR_copy_file_range, sys_ni_syscall)
#define __NR_preadv2 286
__SYSCALL(__NR_preadv2, sys_ni_syscall)
#define __NR_pwritev2 287
__SYSCALL(__NR_pwritev2, sys_ni_syscall)
#define __NR_pkey_mprotect 288
__SYSCALL(__NR_pkey_mprotect, sys_ni_syscall)
#define __NR_pkey_alloc 289
__SYSCALL(__NR_pkey_alloc, sys_ni_syscall)
#define __NR_pkey_free 290
__SYSCALL(__NR_pkey_free, sys_ni_syscall)
#define __NR_statx 291
__SYSCALL(__NR_statx, sys_statx)
#define __NR_io_pgetevents 292
__SYSCALL(__NR_io_pgetevents, sys_ni_syscall)
#define __NR_rseq 293
__SYSCALL(__NR_rseq, sys_ni_syscall)
#define __NR_ni_stub_294 294
__SYSCALL(__NR_ni_stub_294, sys_ni_syscall)
#define __NR_ni_stub_295 295
__SYSCALL(__NR_ni_stub_295, sys_ni_syscall)
#define __NR_ni_stub_296 296
__SYSCALL(__NR_ni_stub_296, sys_ni_syscall)
#define __NR_ni_stub_297 297
__SYSCALL(__NR_ni_stub_297, sys_ni_syscall)
#define __NR_ni_stub_298 298
__SYSCALL(__NR_ni_stub_298, sys_ni_syscall)
#define __NR_ni_stub_299 299
__SYSCALL(__NR_ni_stub_299, sys_ni_syscall)
#define __NR_ni_stub_300 300
__SYSCALL(__NR_ni_stub_300, sys_ni_syscall)
#define __NR_ni_stub_301 301
__SYSCALL(__NR_ni_stub_301, sys_ni_syscall)
#define __NR_ni_stub_302 302
__SYSCALL(__NR_ni_stub_302, sys_ni_syscall)
#define __NR_ni_stub_303 303
__SYSCALL(__NR_ni_stub_303, sys_ni_syscall)
#define __NR_ni_stub_304 304
__SYSCALL(__NR_ni_stub_304, sys_ni_syscall)
#define __NR_ni_stub_305 305
__SYSCALL(__NR_ni_stub_305, sys_ni_syscall)
#define __NR_ni_stub_306 306
__SYSCALL(__NR_ni_stub_306, sys_ni_syscall)
#define __NR_ni_stub_307 307
__SYSCALL(__NR_ni_stub_307, sys_ni_syscall)
#define __NR_ni_stub_308 308
__SYSCALL(__NR_ni_stub_308, sys_ni_syscall)
#define __NR_ni_stub_309 309
__SYSCALL(__NR_ni_stub_309, sys_ni_syscall)
#define __NR_ni_stub_310 310
__SYSCALL(__NR_ni_stub_310, sys_ni_syscall)
#define __NR_ni_stub_311 311
__SYSCALL(__NR_ni_stub_311, sys_ni_syscall)
#define __NR_ni_stub_312 312
__SYSCALL(__NR_ni_stub_312, sys_ni_syscall)
#define __NR_ni_stub_313 313
__SYSCALL(__NR_ni_stub_313, sys_ni_syscall)
#define __NR_ni_stub_314 314
__SYSCALL(__NR_ni_stub_314, sys_ni_syscall)
#define __NR_ni_stub_315 315
__SYSCALL(__NR_ni_stub_315, sys_ni_syscall)
#define __NR_ni_stub_316 316
__SYSCALL(__NR_ni_stub_316, sys_ni_syscall)
#define __NR_ni_stub_317 317
__SYSCALL(__NR_ni_stub_317, sys_ni_syscall)
#define __NR_ni_stub_318 318
__SYSCALL(__NR_ni_stub_318, sys_ni_syscall)
#define __NR_ni_stub_319 319
__SYSCALL(__NR_ni_stub_319, sys_ni_syscall)
#define __NR_ni_stub_320 320
__SYSCALL(__NR_ni_stub_320, sys_ni_syscall)
#define __NR_ni_stub_321 321
__SYSCALL(__NR_ni_stub_321, sys_ni_syscall)
#define __NR_ni_stub_322 322
__SYSCALL(__NR_ni_stub_322, sys_ni_syscall)
#define __NR_ni_stub_323 323
__SYSCALL(__NR_ni_stub_323, sys_ni_syscall)
#define __NR_ni_stub_324 324
__SYSCALL(__NR_ni_stub_324, sys_ni_syscall)
#define __NR_ni_stub_325 325
__SYSCALL(__NR_ni_stub_325, sys_ni_syscall)
#define __NR_ni_stub_326 326
__SYSCALL(__NR_ni_stub_326, sys_ni_syscall)
#define __NR_ni_stub_327 327
__SYSCALL(__NR_ni_stub_327, sys_ni_syscall)
#define __NR_ni_stub_328 328
__SYSCALL(__NR_ni_stub_328, sys_ni_syscall)
#define __NR_ni_stub_329 329
__SYSCALL(__NR_ni_stub_329, sys_ni_syscall)
#define __NR_ni_stub_330 330
__SYSCALL(__NR_ni_stub_330, sys_ni_syscall)
#define __NR_ni_stub_331 331
__SYSCALL(__NR_ni_stub_331, sys_ni_syscall)
#define __NR_ni_stub_332 332
__SYSCALL(__NR_ni_stub_332, sys_ni_syscall)
#define __NR_ni_stub_333 333
__SYSCALL(__NR_ni_stub_333, sys_ni_syscall)
#define __NR_ni_stub_334 334
__SYSCALL(__NR_ni_stub_334, sys_ni_syscall)
#define __NR_ni_stub_335 335
__SYSCALL(__NR_ni_stub_335, sys_ni_syscall)
#define __NR_ni_stub_336 336
__SYSCALL(__NR_ni_stub_336, sys_ni_syscall)
#define __NR_ni_stub_337 337
__SYSCALL(__NR_ni_stub_337, sys_ni_syscall)
#define __NR_ni_stub_338 338
__SYSCALL(__NR_ni_stub_338, sys_ni_syscall)
#define __NR_ni_stub_339 339
__SYSCALL(__NR_ni_stub_339, sys_ni_syscall)
#define __NR_ni_stub_340 340
__SYSCALL(__NR_ni_stub_340, sys_ni_syscall)
#define __NR_ni_stub_341 341
__SYSCALL(__NR_ni_stub_341, sys_ni_syscall)
#define __NR_ni_stub_342 342
__SYSCALL(__NR_ni_stub_342, sys_ni_syscall)
#define __NR_ni_stub_343 343
__SYSCALL(__NR_ni_stub_343, sys_ni_syscall)
#define __NR_ni_stub_344 344
__SYSCALL(__NR_ni_stub_344, sys_ni_syscall)
#define __NR_ni_stub_345 345
__SYSCALL(__NR_ni_stub_345, sys_ni_syscall)
#define __NR_ni_stub_346 346
__SYSCALL(__NR_ni_stub_346, sys_ni_syscall)
#define __NR_ni_stub_347 347
__SYSCALL(__NR_ni_stub_347, sys_ni_syscall)
#define __NR_ni_stub_348 348
__SYSCALL(__NR_ni_stub_348, sys_ni_syscall)
#define __NR_ni_stub_349 349
__SYSCALL(__NR_ni_stub_349, sys_ni_syscall)
#define __NR_ni_stub_350 350
__SYSCALL(__NR_ni_stub_350, sys_ni_syscall)
#define __NR_ni_stub_351 351
__SYSCALL(__NR_ni_stub_351, sys_ni_syscall)
#define __NR_ni_stub_352 352
__SYSCALL(__NR_ni_stub_352, sys_ni_syscall)
#define __NR_ni_stub_353 353
__SYSCALL(__NR_ni_stub_353, sys_ni_syscall)
#define __NR_ni_stub_354 354
__SYSCALL(__NR_ni_stub_354, sys_ni_syscall)
#define __NR_ni_stub_355 355
__SYSCALL(__NR_ni_stub_355, sys_ni_syscall)
#define __NR_ni_stub_356 356
__SYSCALL(__NR_ni_stub_356, sys_ni_syscall)
#define __NR_ni_stub_357 357
__SYSCALL(__NR_ni_stub_357, sys_ni_syscall)
#define __NR_ni_stub_358 358
__SYSCALL(__NR_ni_stub_358, sys_ni_syscall)
#define __NR_ni_stub_359 359
__SYSCALL(__NR_ni_stub_359, sys_ni_syscall)
#define __NR_ni_stub_360 360
__SYSCALL(__NR_ni_stub_360, sys_ni_syscall)
#define __NR_ni_stub_361 361
__SYSCALL(__NR_ni_stub_361, sys_ni_syscall)
#define __NR_ni_stub_362 362
__SYSCALL(__NR_ni_stub_362, sys_ni_syscall)
#define __NR_ni_stub_363 363
__SYSCALL(__NR_ni_stub_363, sys_ni_syscall)
#define __NR_ni_stub_364 364
__SYSCALL(__NR_ni_stub_364, sys_ni_syscall)
#define __NR_ni_stub_365 365
__SYSCALL(__NR_ni_stub_365, sys_ni_syscall)
#define __NR_ni_stub_366 366
__SYSCALL(__NR_ni_stub_366, sys_ni_syscall)
#define __NR_ni_stub_367 367
__SYSCALL(__NR_ni_stub_367, sys_ni_syscall)
#define __NR_ni_stub_368 368
__SYSCALL(__NR_ni_stub_368, sys_ni_syscall)
#define __NR_ni_stub_369 369
__SYSCALL(__NR_ni_stub_369, sys_ni_syscall)
#define __NR_ni_stub_370 370
__SYSCALL(__NR_ni_stub_370, sys_ni_syscall)
#define __NR_ni_stub_371 371
__SYSCALL(__NR_ni_stub_371, sys_ni_syscall)
#define __NR_ni_stub_372 372
__SYSCALL(__NR_ni_stub_372, sys_ni_syscall)
#define __NR_ni_stub_373 373
__SYSCALL(__NR_ni_stub_373, sys_ni_syscall)
#define __NR_ni_stub_374 374
__SYSCALL(__NR_ni_stub_374, sys_ni_syscall)
#define __NR_ni_stub_375 375
__SYSCALL(__NR_ni_stub_375, sys_ni_syscall)
#define __NR_ni_stub_376 376
__SYSCALL(__NR_ni_stub_376, sys_ni_syscall)
#define __NR_ni_stub_377 377
__SYSCALL(__NR_ni_stub_377, sys_ni_syscall)
#define __NR_ni_stub_378 378
__SYSCALL(__NR_ni_stub_378, sys_ni_syscall)
#define __NR_ni_stub_379 379
__SYSCALL(__NR_ni_stub_379, sys_ni_syscall)
#define __NR_ni_stub_380 380
__SYSCALL(__NR_ni_stub_380, sys_ni_syscall)
#define __NR_ni_stub_381 381
__SYSCALL(__NR_ni_stub_381, sys_ni_syscall)
#define __NR_ni_stub_382 382
__SYSCALL(__NR_ni_stub_382, sys_ni_syscall)
#define __NR_ni_stub_383 383
__SYSCALL(__NR_ni_stub_383, sys_ni_syscall)
#define __NR_ni_stub_384 384
__SYSCALL(__NR_ni_stub_384, sys_ni_syscall)
#define __NR_ni_stub_385 385
__SYSCALL(__NR_ni_stub_385, sys_ni_syscall)
#define __NR_ni_stub_386 386
__SYSCALL(__NR_ni_stub_386, sys_ni_syscall)
#define __NR_ni_stub_387 387
__SYSCALL(__NR_ni_stub_387, sys_ni_syscall)
#define __NR_ni_stub_388 388
__SYSCALL(__NR_ni_stub_388, sys_ni_syscall)
#define __NR_ni_stub_389 389
__SYSCALL(__NR_ni_stub_389, sys_ni_syscall)
#define __NR_ni_stub_390 390
__SYSCALL(__NR_ni_stub_390, sys_ni_syscall)
#define __NR_ni_stub_391 391
__SYSCALL(__NR_ni_stub_391, sys_ni_syscall)
#define __NR_ni_stub_392 392
__SYSCALL(__NR_ni_stub_392, sys_ni_syscall)
#define __NR_ni_stub_393 393
__SYSCALL(__NR_ni_stub_393, sys_ni_syscall)
#define __NR_ni_stub_394 394
__SYSCALL(__NR_ni_stub_394, sys_ni_syscall)
#define __NR_ni_stub_395 395
__SYSCALL(__NR_ni_stub_395, sys_ni_syscall)
#define __NR_ni_stub_396 396
__SYSCALL(__NR_ni_stub_396, sys_ni_syscall)
#define __NR_ni_stub_397 397
__SYSCALL(__NR_ni_stub_397, sys_ni_syscall)
#define __NR_ni_stub_398 398
__SYSCALL(__NR_ni_stub_398, sys_ni_syscall)
#define __NR_ni_stub_399 399
__SYSCALL(__NR_ni_stub_399, sys_ni_syscall)
#define __NR_ni_stub_400 400
__SYSCALL(__NR_ni_stub_400, sys_ni_syscall)
#define __NR_ni_stub_401 401
__SYSCALL(__NR_ni_stub_401, sys_ni_syscall)
#define __NR_ni_stub_402 402
__SYSCALL(__NR_ni_stub_402, sys_ni_syscall)
#define __NR_ni_stub_403 403
__SYSCALL(__NR_ni_stub_403, sys_ni_syscall)
#define __NR_ni_stub_404 404
__SYSCALL(__NR_ni_stub_404, sys_ni_syscall)
#define __NR_ni_stub_405 405
__SYSCALL(__NR_ni_stub_405, sys_ni_syscall)
#define __NR_ni_stub_406 406
__SYSCALL(__NR_ni_stub_406, sys_ni_syscall)
#define __NR_ni_stub_407 407
__SYSCALL(__NR_ni_stub_407, sys_ni_syscall)
#define __NR_ni_stub_408 408
__SYSCALL(__NR_ni_stub_408, sys_ni_syscall)
#define __NR_ni_stub_409 409
__SYSCALL(__NR_ni_stub_409, sys_ni_syscall)
#define __NR_ni_stub_410 410
__SYSCALL(__NR_ni_stub_410, sys_ni_syscall)
#define __NR_ni_stub_411 411
__SYSCALL(__NR_ni_stub_411, sys_ni_syscall)
#define __NR_ni_stub_412 412
__SYSCALL(__NR_ni_stub_412, sys_ni_syscall)
#define __NR_ni_stub_413 413
__SYSCALL(__NR_ni_stub_413, sys_ni_syscall)
#define __NR_ni_stub_414 414
__SYSCALL(__NR_ni_stub_414, sys_ni_syscall)
#define __NR_ni_stub_415 415
__SYSCALL(__NR_ni_stub_415, sys_ni_syscall)
#define __NR_ni_stub_416 416
__SYSCALL(__NR_ni_stub_416, sys_ni_syscall)
#define __NR_ni_stub_417 417
__SYSCALL(__NR_ni_stub_417, sys_ni_syscall)
#define __NR_ni_stub_418 418
__SYSCALL(__NR_ni_stub_418, sys_ni_syscall)
#define __NR_ni_stub_419 419
__SYSCALL(__NR_ni_stub_419, sys_ni_syscall)
#define __NR_ni_stub_420 420
__SYSCALL(__NR_ni_stub_420, sys_ni_syscall)
#define __NR_ni_stub_421 421
__SYSCALL(__NR_ni_stub_421, sys_ni_syscall)
#define __NR_ni_stub_422 422
__SYSCALL(__NR_ni_stub_422, sys_ni_syscall)
#define __NR_ni_stub_423 423
__SYSCALL(__NR_ni_stub_423, sys_ni_syscall)
#define __NR_pidfd_send_signal 424
__SYSCALL(__NR_pidfd_send_signal, sys_ni_syscall)
#define __NR_io_uring_setup 425
__SYSCALL(__NR_io_uring_setup, sys_ni_syscall)
#define __NR_io_uring_enter 426
__SYSCALL(__NR_io_uring_enter, sys_ni_syscall)
#define __NR_io_uring_register 427
__SYSCALL(__NR_io_uring_register, sys_ni_syscall)
#define __NR_open_tree 428
__SYSCALL(__NR_open_tree, sys_ni_syscall)
#define __NR_move_mount 429
__SYSCALL(__NR_move_mount, sys_ni_syscall)
#define __NR_fsopen 430
__SYSCALL(__NR_fsopen, sys_ni_syscall)
#define __NR_fsconfig 431
__SYSCALL(__NR_fsconfig, sys_ni_syscall)
#define __NR_fsmount 432
__SYSCALL(__NR_fsmount, sys_ni_syscall)
#define __NR_fspick 433
__SYSCALL(__NR_fspick, sys_ni_syscall)
#define __NR_pidfd_open 434
__SYSCALL(__NR_pidfd_open, sys_ni_syscall)
#define __NR_clone3 435
__SYSCALL(__NR_clone3, sys_clone3)
#define __NR_close_range 436
__SYSCALL(__NR_close_range, sys_ni_syscall)
#define __NR_openat2 437
__SYSCALL(__NR_openat2, sys_ni_syscall)
#define __NR_pidfd_getfd 438
__SYSCALL(__NR_pidfd_getfd, sys_ni_syscall)
#define __NR_faccessat2 439
__SYSCALL(__NR_faccessat2, sys_ni_syscall)
#define __NR_process_madvise 440
__SYSCALL(__NR_process_madvise, sys_ni_syscall)
#define __NR_epoll_pwait2 441
/* epoll_pwait2 (Linux 5.11): wrapper over sys_epoll_pwait that accepts a
 * struct timespec __user* timeout instead of int ms. Without it BootAnimation
 * and BLASTBufferQueue spam ENOSYS retries, blocking SurfaceFlinger. */
__SYSCALL(__NR_epoll_pwait2, sys_epoll_pwait2)
#define __NR_mount_setattr 442
__SYSCALL(__NR_mount_setattr, sys_ni_syscall)
#define __NR_quotactl_fd 443
__SYSCALL(__NR_quotactl_fd, sys_ni_syscall)
#define __NR_landlock_create_ruleset 444
__SYSCALL(__NR_landlock_create_ruleset, sys_ni_syscall)
#define __NR_landlock_add_rule 445
__SYSCALL(__NR_landlock_add_rule, sys_ni_syscall)
#define __NR_landlock_restrict_self 446
__SYSCALL(__NR_landlock_restrict_self, sys_ni_syscall)
#define __NR_memfd_secret 447
__SYSCALL(__NR_memfd_secret, sys_ni_syscall)
#define __NR_process_mrelease 448
__SYSCALL(__NR_process_mrelease, sys_ni_syscall)
#define __NR_futex_waitv 449
__SYSCALL(__NR_futex_waitv, sys_ni_syscall)
#define __NR_set_mempolicy_home_node 450
__SYSCALL(__NR_set_mempolicy_home_node, sys_ni_syscall)
#define __NR_ni_stub_451 451
__SYSCALL(__NR_ni_stub_451, sys_ni_syscall)
#define __NR_ni_stub_452 452
__SYSCALL(__NR_ni_stub_452, sys_ni_syscall)
#define __NR_ni_stub_453 453
__SYSCALL(__NR_ni_stub_453, sys_ni_syscall)
#define __NR_ni_stub_454 454
__SYSCALL(__NR_ni_stub_454, sys_ni_syscall)
#define __NR_ni_stub_455 455
__SYSCALL(__NR_ni_stub_455, sys_ni_syscall)
#define __NR_ni_stub_456 456
__SYSCALL(__NR_ni_stub_456, sys_ni_syscall)
#define __NR_ni_stub_457 457
__SYSCALL(__NR_ni_stub_457, sys_ni_syscall)
#define __NR_ni_stub_458 458
__SYSCALL(__NR_ni_stub_458, sys_ni_syscall)
#define __NR_ni_stub_459 459
__SYSCALL(__NR_ni_stub_459, sys_ni_syscall)
#define __NR_ni_stub_460 460
__SYSCALL(__NR_ni_stub_460, sys_ni_syscall)
#define __NR_ni_stub_461 461
__SYSCALL(__NR_ni_stub_461, sys_ni_syscall)
#define __NR_ni_stub_462 462
__SYSCALL(__NR_ni_stub_462, sys_ni_syscall)
#define __NR_syscalls 463

/*
 * All syscalls below here should go away really,
 * these are provided for both review and as a porting
 * help for the C library version.
*
 * Last chance: are any of these important enough to
 * enable by default?
 */
#ifdef __ARCH_WANT_SYSCALL_NO_AT
#define __NR_open 1024
__SYSCALL(__NR_open, sys_open)
#define __NR_link 1025
__SYSCALL(__NR_link, sys_link)
#define __NR_unlink 1026
__SYSCALL(__NR_unlink, sys_unlink)
#define __NR_mknod 1027
__SYSCALL(__NR_mknod, sys_mknod)
#define __NR_chmod 1028
__SYSCALL(__NR_chmod, sys_chmod)
#define __NR_chown 1029
__SYSCALL(__NR_chown, sys_chown)
#define __NR_mkdir 1030
__SYSCALL(__NR_mkdir, sys_mkdir)
#define __NR_rmdir 1031
__SYSCALL(__NR_rmdir, sys_rmdir)
#define __NR_lchown 1032
__SYSCALL(__NR_lchown, sys_lchown)
#define __NR_access 1033
__SYSCALL(__NR_access, sys_access)
#define __NR_rename 1034
__SYSCALL(__NR_rename, sys_rename)
#define __NR_readlink 1035
__SYSCALL(__NR_readlink, sys_readlink)
#define __NR_symlink 1036
__SYSCALL(__NR_symlink, sys_symlink)
#define __NR_utimes 1037
__SYSCALL(__NR_utimes, sys_utimes)
#define __NR3264_stat 1038
__SC_3264(__NR3264_stat, sys_stat64, sys_newstat)
#define __NR3264_lstat 1039
__SC_3264(__NR3264_lstat, sys_lstat64, sys_newlstat)

#undef __NR_syscalls
#define __NR_syscalls (__NR3264_lstat+1)
#endif /* __ARCH_WANT_SYSCALL_NO_AT */

#ifdef __ARCH_WANT_SYSCALL_NO_FLAGS
#define __NR_pipe 1040
__SYSCALL(__NR_pipe, sys_pipe)
#define __NR_dup2 1041
__SYSCALL(__NR_dup2, sys_dup2)
#define __NR_epoll_create 1042
__SYSCALL(__NR_epoll_create, sys_epoll_create)
#define __NR_inotify_init 1043
__SYSCALL(__NR_inotify_init, sys_inotify_init)
#define __NR_eventfd 1044
__SYSCALL(__NR_eventfd, sys_eventfd)
#define __NR_signalfd 1045
__SYSCALL(__NR_signalfd, sys_signalfd)

#undef __NR_syscalls
#define __NR_syscalls (__NR_signalfd+1)
#endif /* __ARCH_WANT_SYSCALL_NO_FLAGS */

#if (__BITS_PER_LONG == 32 || defined(__SYSCALL_COMPAT)) && \
     defined(__ARCH_WANT_SYSCALL_OFF_T)
#define __NR_sendfile 1046
__SYSCALL(__NR_sendfile, sys_sendfile)
#define __NR_ftruncate 1047
__SYSCALL(__NR_ftruncate, sys_ftruncate)
#define __NR_truncate 1048
__SYSCALL(__NR_truncate, sys_truncate)
#define __NR_stat 1049
__SYSCALL(__NR_stat, sys_newstat)
#define __NR_lstat 1050
__SYSCALL(__NR_lstat, sys_newlstat)
#define __NR_fstat 1051
__SYSCALL(__NR_fstat, sys_newfstat)
#define __NR_fcntl 1052
__SYSCALL(__NR_fcntl, sys_fcntl)
#define __NR_fadvise64 1053
#define __ARCH_WANT_SYS_FADVISE64
__SYSCALL(__NR_fadvise64, sys_fadvise64)
#define __NR_newfstatat 1054
#define __ARCH_WANT_SYS_NEWFSTATAT
__SYSCALL(__NR_newfstatat, sys_newfstatat)
#define __NR_fstatfs 1055
__SYSCALL(__NR_fstatfs, sys_fstatfs)
#define __NR_statfs 1056
__SYSCALL(__NR_statfs, sys_statfs)
#define __NR_lseek 1057
__SYSCALL(__NR_lseek, sys_lseek)
#define __NR_mmap 1058
__SYSCALL(__NR_mmap, sys_mmap)

#undef __NR_syscalls
#define __NR_syscalls (__NR_mmap+1)
#endif /* 32 bit off_t syscalls */

#ifdef __ARCH_WANT_SYSCALL_DEPRECATED
#define __NR_alarm 1059
#define __ARCH_WANT_SYS_ALARM
__SYSCALL(__NR_alarm, sys_alarm)
#define __NR_getpgrp 1060
#define __ARCH_WANT_SYS_GETPGRP
__SYSCALL(__NR_getpgrp, sys_getpgrp)
#define __NR_pause 1061
#define __ARCH_WANT_SYS_PAUSE
__SYSCALL(__NR_pause, sys_pause)
#define __NR_time 1062
#define __ARCH_WANT_SYS_TIME
#define __ARCH_WANT_COMPAT_SYS_TIME
__SYSCALL(__NR_time, sys_time)
#define __NR_utime 1063
#define __ARCH_WANT_SYS_UTIME
__SYSCALL(__NR_utime, sys_utime)

#define __NR_creat 1064
__SYSCALL(__NR_creat, sys_creat)
#define __NR_getdents 1065
#define __ARCH_WANT_SYS_GETDENTS
__SYSCALL(__NR_getdents, sys_getdents)
#define __NR_futimesat 1066
__SYSCALL(__NR_futimesat, sys_futimesat)
#define __NR_select 1067
#define __ARCH_WANT_SYS_SELECT
__SYSCALL(__NR_select, sys_select)
#define __NR_poll 1068
__SYSCALL(__NR_poll, sys_poll)
#define __NR_epoll_wait 1069
__SYSCALL(__NR_epoll_wait, sys_epoll_wait)
#define __NR_ustat 1070
__SYSCALL(__NR_ustat, sys_ustat)
#define __NR_vfork 1071
__SYSCALL(__NR_vfork, sys_vfork)
#define __NR_oldwait4 1072
__SYSCALL(__NR_oldwait4, sys_wait4)
#define __NR_recv 1073
__SYSCALL(__NR_recv, sys_recv)
#define __NR_send 1074
__SYSCALL(__NR_send, sys_send)
#define __NR_bdflush 1075
__SYSCALL(__NR_bdflush, sys_bdflush)
#define __NR_umount 1076
__SYSCALL(__NR_umount, sys_oldumount)
#define __ARCH_WANT_SYS_OLDUMOUNT
#define __NR_uselib 1077
__SYSCALL(__NR_uselib, sys_uselib)
#define __NR__sysctl 1078
__SYSCALL(__NR__sysctl, sys_sysctl)

#define __NR_fork 1079
#ifdef CONFIG_MMU
__SYSCALL(__NR_fork, sys_fork)
#else
__SYSCALL(__NR_fork, sys_ni_syscall)
#endif /* CONFIG_MMU */

#undef __NR_syscalls
#define __NR_syscalls (__NR_fork+1)

#endif /* __ARCH_WANT_SYSCALL_DEPRECATED */

/*
 * 32 bit systems traditionally used different
 * syscalls for off_t and loff_t arguments, while
 * 64 bit systems only need the off_t version.
 * For new 32 bit platforms, there is no need to
 * implement the old 32 bit off_t syscalls, so
 * they take different names.
 * Here we map the numbers so that both versions
 * use the same syscall table layout.
 */
#if __BITS_PER_LONG == 64 && !defined(__SYSCALL_COMPAT)
#define __NR_fcntl __NR3264_fcntl
#define __NR_statfs __NR3264_statfs
#define __NR_fstatfs __NR3264_fstatfs
#define __NR_truncate __NR3264_truncate
#define __NR_ftruncate __NR3264_ftruncate
#define __NR_lseek __NR3264_lseek
#define __NR_sendfile __NR3264_sendfile
#define __NR_newfstatat __NR3264_fstatat
#define __NR_fstat __NR3264_fstat
#define __NR_mmap __NR3264_mmap
#define __NR_fadvise64 __NR3264_fadvise64
#ifdef __NR3264_stat
#define __NR_stat __NR3264_stat
#define __NR_lstat __NR3264_lstat
#endif
#else
#define __NR_fcntl64 __NR3264_fcntl
#define __NR_statfs64 __NR3264_statfs
#define __NR_fstatfs64 __NR3264_fstatfs
#define __NR_truncate64 __NR3264_truncate
#define __NR_ftruncate64 __NR3264_ftruncate
#define __NR_llseek __NR3264_lseek
#define __NR_sendfile64 __NR3264_sendfile
#define __NR_fstatat64 __NR3264_fstatat
#define __NR_fstat64 __NR3264_fstat
#define __NR_mmap2 __NR3264_mmap
#define __NR_fadvise64_64 __NR3264_fadvise64
#ifdef __NR3264_stat
#define __NR_stat64 __NR3264_stat
#define __NR_lstat64 __NR3264_lstat
#endif
#endif
