<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#समावेश <यंत्र/bitsperदीर्घ.h>

/*
 * This file contains the प्रणाली call numbers, based on the
 * layout of the x86-64 architecture, which embeds the
 * poपूर्णांकer to the syscall in the table.
 *
 * As a basic principle, no duplication of functionality
 * should be added, e.g. we करोn't use lseek when llseek
 * is present. New architectures should use this file
 * and implement the less feature-full calls in user space.
 */

#अगर_अघोषित __SYSCALL
#घोषणा __SYSCALL(x, y)
#पूर्ण_अगर

#अगर __BITS_PER_LONG == 32 || defined(__SYSCALL_COMPAT)
#घोषणा __SC_3264(_nr, _32, _64) __SYSCALL(_nr, _32)
#अन्यथा
#घोषणा __SC_3264(_nr, _32, _64) __SYSCALL(_nr, _64)
#पूर्ण_अगर

#अगर_घोषित __SYSCALL_COMPAT
#घोषणा __SC_COMP(_nr, _sys, _comp) __SYSCALL(_nr, _comp)
#घोषणा __SC_COMP_3264(_nr, _32, _64, _comp) __SYSCALL(_nr, _comp)
#अन्यथा
#घोषणा __SC_COMP(_nr, _sys, _comp) __SYSCALL(_nr, _sys)
#घोषणा __SC_COMP_3264(_nr, _32, _64, _comp) __SC_3264(_nr, _32, _64)
#पूर्ण_अगर

#घोषणा __NR_io_setup 0
__SC_COMP(__NR_io_setup, sys_io_setup, compat_sys_io_setup)
#घोषणा __NR_io_destroy 1
__SYSCALL(__NR_io_destroy, sys_io_destroy)
#घोषणा __NR_io_submit 2
__SC_COMP(__NR_io_submit, sys_io_submit, compat_sys_io_submit)
#घोषणा __NR_io_cancel 3
__SYSCALL(__NR_io_cancel, sys_io_cancel)
#अगर defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#घोषणा __NR_io_getevents 4
__SC_3264(__NR_io_getevents, sys_io_getevents_समय32, sys_io_getevents)
#पूर्ण_अगर

/* fs/xattr.c */
#घोषणा __NR_setxattr 5
__SYSCALL(__NR_setxattr, sys_setxattr)
#घोषणा __NR_lsetxattr 6
__SYSCALL(__NR_lsetxattr, sys_lsetxattr)
#घोषणा __NR_fsetxattr 7
__SYSCALL(__NR_fsetxattr, sys_fsetxattr)
#घोषणा __NR_getxattr 8
__SYSCALL(__NR_getxattr, sys_getxattr)
#घोषणा __NR_lgetxattr 9
__SYSCALL(__NR_lgetxattr, sys_lgetxattr)
#घोषणा __NR_fgetxattr 10
__SYSCALL(__NR_fgetxattr, sys_fgetxattr)
#घोषणा __NR_listxattr 11
__SYSCALL(__NR_listxattr, sys_listxattr)
#घोषणा __NR_llistxattr 12
__SYSCALL(__NR_llistxattr, sys_llistxattr)
#घोषणा __NR_flistxattr 13
__SYSCALL(__NR_flistxattr, sys_flistxattr)
#घोषणा __NR_हटाओxattr 14
__SYSCALL(__NR_हटाओxattr, sys_हटाओxattr)
#घोषणा __NR_lहटाओxattr 15
__SYSCALL(__NR_lहटाओxattr, sys_lहटाओxattr)
#घोषणा __NR_fहटाओxattr 16
__SYSCALL(__NR_fहटाओxattr, sys_fहटाओxattr)

/* fs/dcache.c */
#घोषणा __NR_अ_लोwd 17
__SYSCALL(__NR_अ_लोwd, sys_अ_लोwd)

/* fs/cookies.c */
#घोषणा __NR_lookup_dcookie 18
__SC_COMP(__NR_lookup_dcookie, sys_lookup_dcookie, compat_sys_lookup_dcookie)

/* fs/eventfd.c */
#घोषणा __NR_eventfd2 19
__SYSCALL(__NR_eventfd2, sys_eventfd2)

/* fs/eventpoll.c */
#घोषणा __NR_epoll_create1 20
__SYSCALL(__NR_epoll_create1, sys_epoll_create1)
#घोषणा __NR_epoll_ctl 21
__SYSCALL(__NR_epoll_ctl, sys_epoll_ctl)
#घोषणा __NR_epoll_pरुको 22
__SC_COMP(__NR_epoll_pरुको, sys_epoll_pरुको, compat_sys_epoll_pरुको)

/* fs/fcntl.c */
#घोषणा __NR_dup 23
__SYSCALL(__NR_dup, sys_dup)
#घोषणा __NR_dup3 24
__SYSCALL(__NR_dup3, sys_dup3)
#घोषणा __NR3264_fcntl 25
__SC_COMP_3264(__NR3264_fcntl, sys_fcntl64, sys_fcntl, compat_sys_fcntl64)

/* fs/inotअगरy_user.c */
#घोषणा __NR_inotअगरy_init1 26
__SYSCALL(__NR_inotअगरy_init1, sys_inotअगरy_init1)
#घोषणा __NR_inotअगरy_add_watch 27
__SYSCALL(__NR_inotअगरy_add_watch, sys_inotअगरy_add_watch)
#घोषणा __NR_inotअगरy_rm_watch 28
__SYSCALL(__NR_inotअगरy_rm_watch, sys_inotअगरy_rm_watch)

/* fs/ioctl.c */
#घोषणा __NR_ioctl 29
__SC_COMP(__NR_ioctl, sys_ioctl, compat_sys_ioctl)

/* fs/ioprio.c */
#घोषणा __NR_ioprio_set 30
__SYSCALL(__NR_ioprio_set, sys_ioprio_set)
#घोषणा __NR_ioprio_get 31
__SYSCALL(__NR_ioprio_get, sys_ioprio_get)

/* fs/locks.c */
#घोषणा __NR_flock 32
__SYSCALL(__NR_flock, sys_flock)

/* fs/namei.c */
#घोषणा __NR_mknodat 33
__SYSCALL(__NR_mknodat, sys_mknodat)
#घोषणा __NR_सूची_गढ़ोat 34
__SYSCALL(__NR_सूची_गढ़ोat, sys_सूची_गढ़ोat)
#घोषणा __NR_unlinkat 35
__SYSCALL(__NR_unlinkat, sys_unlinkat)
#घोषणा __NR_symlinkat 36
__SYSCALL(__NR_symlinkat, sys_symlinkat)
#घोषणा __NR_linkat 37
__SYSCALL(__NR_linkat, sys_linkat)
#अगर_घोषित __ARCH_WANT_RENAMEAT
/* नामat is superseded with flags by नामat2 */
#घोषणा __NR_नामat 38
__SYSCALL(__NR_नामat, sys_नामat)
#पूर्ण_अगर /* __ARCH_WANT_RENAMEAT */

/* fs/namespace.c */
#घोषणा __NR_umount2 39
__SYSCALL(__NR_umount2, sys_umount)
#घोषणा __NR_mount 40
__SYSCALL(__NR_mount, sys_mount)
#घोषणा __NR_pivot_root 41
__SYSCALL(__NR_pivot_root, sys_pivot_root)

/* fs/nfsctl.c */
#घोषणा __NR_nfsservctl 42
__SYSCALL(__NR_nfsservctl, sys_ni_syscall)

/* fs/खोलो.c */
#घोषणा __NR3264_statfs 43
__SC_COMP_3264(__NR3264_statfs, sys_statfs64, sys_statfs, \
	       compat_sys_statfs64)
#घोषणा __NR3264_ख_स्थितिfs 44
__SC_COMP_3264(__NR3264_ख_स्थितिfs, sys_ख_स्थितिfs64, sys_ख_स्थितिfs, \
	       compat_sys_ख_स्थितिfs64)
#घोषणा __NR3264_truncate 45
__SC_COMP_3264(__NR3264_truncate, sys_truncate64, sys_truncate, \
	       compat_sys_truncate64)
#घोषणा __NR3264_ftruncate 46
__SC_COMP_3264(__NR3264_ftruncate, sys_ftruncate64, sys_ftruncate, \
	       compat_sys_ftruncate64)

#घोषणा __NR_fallocate 47
__SC_COMP(__NR_fallocate, sys_fallocate, compat_sys_fallocate)
#घोषणा __NR_faccessat 48
__SYSCALL(__NR_faccessat, sys_faccessat)
#घोषणा __NR_स_बदलो 49
__SYSCALL(__NR_स_बदलो, sys_स_बदलो)
#घोषणा __NR_fस_बदलो 50
__SYSCALL(__NR_fस_बदलो, sys_fस_बदलो)
#घोषणा __NR_chroot 51
__SYSCALL(__NR_chroot, sys_chroot)
#घोषणा __NR_fchmod 52
__SYSCALL(__NR_fchmod, sys_fchmod)
#घोषणा __NR_fchmodat 53
__SYSCALL(__NR_fchmodat, sys_fchmodat)
#घोषणा __NR_fchownat 54
__SYSCALL(__NR_fchownat, sys_fchownat)
#घोषणा __NR_fchown 55
__SYSCALL(__NR_fchown, sys_fchown)
#घोषणा __NR_खोलोat 56
__SYSCALL(__NR_खोलोat, sys_खोलोat)
#घोषणा __NR_बंद 57
__SYSCALL(__NR_बंद, sys_बंद)
#घोषणा __NR_vhangup 58
__SYSCALL(__NR_vhangup, sys_vhangup)

/* fs/pipe.c */
#घोषणा __NR_pipe2 59
__SYSCALL(__NR_pipe2, sys_pipe2)

/* fs/quota.c */
#घोषणा __NR_quotactl 60
__SYSCALL(__NR_quotactl, sys_quotactl)

/* fs/सूची_पढ़ो.c */
#घोषणा __NR_getdents64 61
__SYSCALL(__NR_getdents64, sys_getdents64)

/* fs/पढ़ो_ग_लिखो.c */
#घोषणा __NR3264_lseek 62
__SC_3264(__NR3264_lseek, sys_llseek, sys_lseek)
#घोषणा __NR_पढ़ो 63
__SYSCALL(__NR_पढ़ो, sys_पढ़ो)
#घोषणा __NR_ग_लिखो 64
__SYSCALL(__NR_ग_लिखो, sys_ग_लिखो)
#घोषणा __NR_पढ़ोv 65
__SC_COMP(__NR_पढ़ोv, sys_पढ़ोv, sys_पढ़ोv)
#घोषणा __NR_ग_लिखोv 66
__SC_COMP(__NR_ग_लिखोv, sys_ग_लिखोv, sys_ग_लिखोv)
#घोषणा __NR_pपढ़ो64 67
__SC_COMP(__NR_pपढ़ो64, sys_pपढ़ो64, compat_sys_pपढ़ो64)
#घोषणा __NR_pग_लिखो64 68
__SC_COMP(__NR_pग_लिखो64, sys_pग_लिखो64, compat_sys_pग_लिखो64)
#घोषणा __NR_pपढ़ोv 69
__SC_COMP(__NR_pपढ़ोv, sys_pपढ़ोv, compat_sys_pपढ़ोv)
#घोषणा __NR_pग_लिखोv 70
__SC_COMP(__NR_pग_लिखोv, sys_pग_लिखोv, compat_sys_pग_लिखोv)

/* fs/sendfile.c */
#घोषणा __NR3264_sendfile 71
__SYSCALL(__NR3264_sendfile, sys_sendfile64)

/* fs/select.c */
#अगर defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#घोषणा __NR_pselect6 72
__SC_COMP_3264(__NR_pselect6, sys_pselect6_समय32, sys_pselect6, compat_sys_pselect6_समय32)
#घोषणा __NR_ppoll 73
__SC_COMP_3264(__NR_ppoll, sys_ppoll_समय32, sys_ppoll, compat_sys_ppoll_समय32)
#पूर्ण_अगर

/* fs/संकेतfd.c */
#घोषणा __NR_संकेतfd4 74
__SC_COMP(__NR_संकेतfd4, sys_संकेतfd4, compat_sys_संकेतfd4)

/* fs/splice.c */
#घोषणा __NR_vmsplice 75
__SYSCALL(__NR_vmsplice, sys_vmsplice)
#घोषणा __NR_splice 76
__SYSCALL(__NR_splice, sys_splice)
#घोषणा __NR_tee 77
__SYSCALL(__NR_tee, sys_tee)

/* fs/stat.c */
#घोषणा __NR_पढ़ोlinkat 78
__SYSCALL(__NR_पढ़ोlinkat, sys_पढ़ोlinkat)
#अगर defined(__ARCH_WANT_NEW_STAT) || defined(__ARCH_WANT_STAT64)
#घोषणा __NR3264_ख_स्थितिat 79
__SC_3264(__NR3264_ख_स्थितिat, sys_ख_स्थितिat64, sys_newख_स्थितिat)
#घोषणा __NR3264_ख_स्थिति 80
__SC_3264(__NR3264_ख_स्थिति, sys_ख_स्थिति64, sys_newख_स्थिति)
#पूर्ण_अगर

/* fs/sync.c */
#घोषणा __NR_sync 81
__SYSCALL(__NR_sync, sys_sync)
#घोषणा __NR_fsync 82
__SYSCALL(__NR_fsync, sys_fsync)
#घोषणा __NR_fdatasync 83
__SYSCALL(__NR_fdatasync, sys_fdatasync)
#अगर_घोषित __ARCH_WANT_SYNC_खाता_RANGE2
#घोषणा __NR_sync_file_range2 84
__SC_COMP(__NR_sync_file_range2, sys_sync_file_range2, \
	  compat_sys_sync_file_range2)
#अन्यथा
#घोषणा __NR_sync_file_range 84
__SC_COMP(__NR_sync_file_range, sys_sync_file_range, \
	  compat_sys_sync_file_range)
#पूर्ण_अगर

/* fs/समयrfd.c */
#घोषणा __NR_समयrfd_create 85
__SYSCALL(__NR_समयrfd_create, sys_समयrfd_create)
#अगर defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#घोषणा __NR_समयrfd_समय_रखो 86
__SC_3264(__NR_समयrfd_समय_रखो, sys_समयrfd_समय_रखो32, \
	  sys_समयrfd_समय_रखो)
#घोषणा __NR_समयrfd_समय_लो 87
__SC_3264(__NR_समयrfd_समय_लो, sys_समयrfd_समय_लो32, \
	  sys_समयrfd_समय_लो)
#पूर्ण_अगर

/* fs/uबार.c */
#अगर defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#घोषणा __NR_uसमयnsat 88
__SC_3264(__NR_uसमयnsat, sys_uसमयnsat_समय32, sys_uसमयnsat)
#पूर्ण_अगर

/* kernel/acct.c */
#घोषणा __NR_acct 89
__SYSCALL(__NR_acct, sys_acct)

/* kernel/capability.c */
#घोषणा __NR_capget 90
__SYSCALL(__NR_capget, sys_capget)
#घोषणा __NR_capset 91
__SYSCALL(__NR_capset, sys_capset)

/* kernel/exec_करोमुख्य.c */
#घोषणा __NR_personality 92
__SYSCALL(__NR_personality, sys_personality)

/* kernel/निकास.c */
#घोषणा __NR_निकास 93
__SYSCALL(__NR_निकास, sys_निकास)
#घोषणा __NR_निकास_group 94
__SYSCALL(__NR_निकास_group, sys_निकास_group)
#घोषणा __NR_रुकोid 95
__SC_COMP(__NR_रुकोid, sys_रुकोid, compat_sys_रुकोid)

/* kernel/विभाजन.c */
#घोषणा __NR_set_tid_address 96
__SYSCALL(__NR_set_tid_address, sys_set_tid_address)
#घोषणा __NR_unshare 97
__SYSCALL(__NR_unshare, sys_unshare)

/* kernel/futex.c */
#अगर defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#घोषणा __NR_futex 98
__SC_3264(__NR_futex, sys_futex_समय32, sys_futex)
#पूर्ण_अगर
#घोषणा __NR_set_robust_list 99
__SC_COMP(__NR_set_robust_list, sys_set_robust_list, \
	  compat_sys_set_robust_list)
#घोषणा __NR_get_robust_list 100
__SC_COMP(__NR_get_robust_list, sys_get_robust_list, \
	  compat_sys_get_robust_list)

/* kernel/hrसमयr.c */
#अगर defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#घोषणा __NR_nanosleep 101
__SC_3264(__NR_nanosleep, sys_nanosleep_समय32, sys_nanosleep)
#पूर्ण_अगर

/* kernel/iसमयr.c */
#घोषणा __NR_getiसमयr 102
__SC_COMP(__NR_getiसमयr, sys_getiसमयr, compat_sys_getiसमयr)
#घोषणा __NR_setiसमयr 103
__SC_COMP(__NR_setiसमयr, sys_setiसमयr, compat_sys_setiसमयr)

/* kernel/kexec.c */
#घोषणा __NR_kexec_load 104
__SC_COMP(__NR_kexec_load, sys_kexec_load, compat_sys_kexec_load)

/* kernel/module.c */
#घोषणा __NR_init_module 105
__SYSCALL(__NR_init_module, sys_init_module)
#घोषणा __NR_delete_module 106
__SYSCALL(__NR_delete_module, sys_delete_module)

/* kernel/posix-समयrs.c */
#घोषणा __NR_समयr_create 107
__SC_COMP(__NR_समयr_create, sys_समयr_create, compat_sys_समयr_create)
#अगर defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#घोषणा __NR_समयr_समय_लो 108
__SC_3264(__NR_समयr_समय_लो, sys_समयr_समय_लो32, sys_समयr_समय_लो)
#पूर्ण_अगर
#घोषणा __NR_समयr_getoverrun 109
__SYSCALL(__NR_समयr_getoverrun, sys_समयr_getoverrun)
#अगर defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#घोषणा __NR_समयr_समय_रखो 110
__SC_3264(__NR_समयr_समय_रखो, sys_समयr_समय_रखो32, sys_समयr_समय_रखो)
#पूर्ण_अगर
#घोषणा __NR_समयr_delete 111
__SYSCALL(__NR_समयr_delete, sys_समयr_delete)
#अगर defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#घोषणा __NR_घड़ी_समय_रखो 112
__SC_3264(__NR_घड़ी_समय_रखो, sys_घड़ी_समय_रखो32, sys_घड़ी_समय_रखो)
#घोषणा __NR_घड़ी_समय_लो 113
__SC_3264(__NR_घड़ी_समय_लो, sys_घड़ी_समय_लो32, sys_घड़ी_समय_लो)
#घोषणा __NR_घड़ी_getres 114
__SC_3264(__NR_घड़ी_getres, sys_घड़ी_getres_समय32, sys_घड़ी_getres)
#घोषणा __NR_घड़ी_nanosleep 115
__SC_3264(__NR_घड़ी_nanosleep, sys_घड़ी_nanosleep_समय32, \
	  sys_घड़ी_nanosleep)
#पूर्ण_अगर

/* kernel/prपूर्णांकk.c */
#घोषणा __NR_syslog 116
__SYSCALL(__NR_syslog, sys_syslog)

/* kernel/ptrace.c */
#घोषणा __NR_ptrace 117
__SYSCALL(__NR_ptrace, sys_ptrace)

/* kernel/sched/core.c */
#घोषणा __NR_sched_setparam 118
__SYSCALL(__NR_sched_setparam, sys_sched_setparam)
#घोषणा __NR_sched_setscheduler 119
__SYSCALL(__NR_sched_setscheduler, sys_sched_setscheduler)
#घोषणा __NR_sched_माला_लोcheduler 120
__SYSCALL(__NR_sched_माला_लोcheduler, sys_sched_माला_लोcheduler)
#घोषणा __NR_sched_getparam 121
__SYSCALL(__NR_sched_getparam, sys_sched_getparam)
#घोषणा __NR_sched_setaffinity 122
__SC_COMP(__NR_sched_setaffinity, sys_sched_setaffinity, \
	  compat_sys_sched_setaffinity)
#घोषणा __NR_sched_getaffinity 123
__SC_COMP(__NR_sched_getaffinity, sys_sched_getaffinity, \
	  compat_sys_sched_getaffinity)
#घोषणा __NR_sched_yield 124
__SYSCALL(__NR_sched_yield, sys_sched_yield)
#घोषणा __NR_sched_get_priority_max 125
__SYSCALL(__NR_sched_get_priority_max, sys_sched_get_priority_max)
#घोषणा __NR_sched_get_priority_min 126
__SYSCALL(__NR_sched_get_priority_min, sys_sched_get_priority_min)
#अगर defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#घोषणा __NR_sched_rr_get_पूर्णांकerval 127
__SC_3264(__NR_sched_rr_get_पूर्णांकerval, sys_sched_rr_get_पूर्णांकerval_समय32, \
	  sys_sched_rr_get_पूर्णांकerval)
#पूर्ण_अगर

/* kernel/संकेत.c */
#घोषणा __NR_restart_syscall 128
__SYSCALL(__NR_restart_syscall, sys_restart_syscall)
#घोषणा __NR_समाप्त 129
__SYSCALL(__NR_समाप्त, sys_समाप्त)
#घोषणा __NR_tसमाप्त 130
__SYSCALL(__NR_tसमाप्त, sys_tसमाप्त)
#घोषणा __NR_tgसमाप्त 131
__SYSCALL(__NR_tgसमाप्त, sys_tgसमाप्त)
#घोषणा __NR_sigaltstack 132
__SC_COMP(__NR_sigaltstack, sys_sigaltstack, compat_sys_sigaltstack)
#घोषणा __NR_rt_संक_रोको 133
__SC_COMP(__NR_rt_संक_रोको, sys_rt_संक_रोको, compat_sys_rt_संक_रोको)
#घोषणा __NR_rt_sigaction 134
__SC_COMP(__NR_rt_sigaction, sys_rt_sigaction, compat_sys_rt_sigaction)
#घोषणा __NR_rt_sigprocmask 135
__SC_COMP(__NR_rt_sigprocmask, sys_rt_sigprocmask, compat_sys_rt_sigprocmask)
#घोषणा __NR_rt_संक_बाकी 136
__SC_COMP(__NR_rt_संक_बाकी, sys_rt_संक_बाकी, compat_sys_rt_संक_बाकी)
#अगर defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#घोषणा __NR_rt_sigसमयdरुको 137
__SC_COMP_3264(__NR_rt_sigसमयdरुको, sys_rt_sigसमयdरुको_समय32, \
	  sys_rt_sigसमयdरुको, compat_sys_rt_sigसमयdरुको_समय32)
#पूर्ण_अगर
#घोषणा __NR_rt_sigqueueinfo 138
__SC_COMP(__NR_rt_sigqueueinfo, sys_rt_sigqueueinfo, \
	  compat_sys_rt_sigqueueinfo)
#घोषणा __NR_rt_sigवापस 139
__SC_COMP(__NR_rt_sigवापस, sys_rt_sigवापस, compat_sys_rt_sigवापस)

/* kernel/sys.c */
#घोषणा __NR_setpriority 140
__SYSCALL(__NR_setpriority, sys_setpriority)
#घोषणा __NR_getpriority 141
__SYSCALL(__NR_getpriority, sys_getpriority)
#घोषणा __NR_reboot 142
__SYSCALL(__NR_reboot, sys_reboot)
#घोषणा __NR_setregid 143
__SYSCALL(__NR_setregid, sys_setregid)
#घोषणा __NR_setgid 144
__SYSCALL(__NR_setgid, sys_setgid)
#घोषणा __NR_setreuid 145
__SYSCALL(__NR_setreuid, sys_setreuid)
#घोषणा __NR_setuid 146
__SYSCALL(__NR_setuid, sys_setuid)
#घोषणा __NR_setresuid 147
__SYSCALL(__NR_setresuid, sys_setresuid)
#घोषणा __NR_getresuid 148
__SYSCALL(__NR_getresuid, sys_getresuid)
#घोषणा __NR_setresgid 149
__SYSCALL(__NR_setresgid, sys_setresgid)
#घोषणा __NR_getresgid 150
__SYSCALL(__NR_getresgid, sys_getresgid)
#घोषणा __NR_setfsuid 151
__SYSCALL(__NR_setfsuid, sys_setfsuid)
#घोषणा __NR_setfsgid 152
__SYSCALL(__NR_setfsgid, sys_setfsgid)
#घोषणा __NR_बार 153
__SC_COMP(__NR_बार, sys_बार, compat_sys_बार)
#घोषणा __NR_setpgid 154
__SYSCALL(__NR_setpgid, sys_setpgid)
#घोषणा __NR_getpgid 155
__SYSCALL(__NR_getpgid, sys_getpgid)
#घोषणा __NR_माला_लोid 156
__SYSCALL(__NR_माला_लोid, sys_माला_लोid)
#घोषणा __NR_setsid 157
__SYSCALL(__NR_setsid, sys_setsid)
#घोषणा __NR_getgroups 158
__SYSCALL(__NR_getgroups, sys_getgroups)
#घोषणा __NR_setgroups 159
__SYSCALL(__NR_setgroups, sys_setgroups)
#घोषणा __NR_uname 160
__SYSCALL(__NR_uname, sys_newuname)
#घोषणा __NR_sethostname 161
__SYSCALL(__NR_sethostname, sys_sethostname)
#घोषणा __NR_setकरोमुख्यname 162
__SYSCALL(__NR_setकरोमुख्यname, sys_setकरोमुख्यname)

#अगर_घोषित __ARCH_WANT_SET_GET_RLIMIT
/* getrlimit and setrlimit are superseded with prlimit64 */
#घोषणा __NR_getrlimit 163
__SC_COMP(__NR_getrlimit, sys_getrlimit, compat_sys_getrlimit)
#घोषणा __NR_setrlimit 164
__SC_COMP(__NR_setrlimit, sys_setrlimit, compat_sys_setrlimit)
#पूर्ण_अगर

#घोषणा __NR_getrusage 165
__SC_COMP(__NR_getrusage, sys_getrusage, compat_sys_getrusage)
#घोषणा __NR_umask 166
__SYSCALL(__NR_umask, sys_umask)
#घोषणा __NR_prctl 167
__SYSCALL(__NR_prctl, sys_prctl)
#घोषणा __NR_अ_लोpu 168
__SYSCALL(__NR_अ_लोpu, sys_अ_लोpu)

/* kernel/समय.c */
#अगर defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#घोषणा __NR_समय_लोofday 169
__SC_COMP(__NR_समय_लोofday, sys_समय_लोofday, compat_sys_समय_लोofday)
#घोषणा __NR_समय_रखोofday 170
__SC_COMP(__NR_समय_रखोofday, sys_समय_रखोofday, compat_sys_समय_रखोofday)
#घोषणा __NR_adjसमयx 171
__SC_3264(__NR_adjसमयx, sys_adjसमयx_समय32, sys_adjसमयx)
#पूर्ण_अगर

/* kernel/sys.c */
#घोषणा __NR_getpid 172
__SYSCALL(__NR_getpid, sys_getpid)
#घोषणा __NR_getppid 173
__SYSCALL(__NR_getppid, sys_getppid)
#घोषणा __NR_getuid 174
__SYSCALL(__NR_getuid, sys_getuid)
#घोषणा __NR_geteuid 175
__SYSCALL(__NR_geteuid, sys_geteuid)
#घोषणा __NR_getgid 176
__SYSCALL(__NR_getgid, sys_getgid)
#घोषणा __NR_getegid 177
__SYSCALL(__NR_getegid, sys_getegid)
#घोषणा __NR_gettid 178
__SYSCALL(__NR_gettid, sys_gettid)
#घोषणा __NR_sysinfo 179
__SC_COMP(__NR_sysinfo, sys_sysinfo, compat_sys_sysinfo)

/* ipc/mqueue.c */
#घोषणा __NR_mq_खोलो 180
__SC_COMP(__NR_mq_खोलो, sys_mq_खोलो, compat_sys_mq_खोलो)
#घोषणा __NR_mq_unlink 181
__SYSCALL(__NR_mq_unlink, sys_mq_unlink)
#अगर defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#घोषणा __NR_mq_समयdsend 182
__SC_3264(__NR_mq_समयdsend, sys_mq_समयdsend_समय32, sys_mq_समयdsend)
#घोषणा __NR_mq_समयdreceive 183
__SC_3264(__NR_mq_समयdreceive, sys_mq_समयdreceive_समय32, \
	  sys_mq_समयdreceive)
#पूर्ण_अगर
#घोषणा __NR_mq_notअगरy 184
__SC_COMP(__NR_mq_notअगरy, sys_mq_notअगरy, compat_sys_mq_notअगरy)
#घोषणा __NR_mq_माला_लोetattr 185
__SC_COMP(__NR_mq_माला_लोetattr, sys_mq_माला_लोetattr, compat_sys_mq_माला_लोetattr)

/* ipc/msg.c */
#घोषणा __NR_msgget 186
__SYSCALL(__NR_msgget, sys_msgget)
#घोषणा __NR_msgctl 187
__SC_COMP(__NR_msgctl, sys_msgctl, compat_sys_msgctl)
#घोषणा __NR_msgrcv 188
__SC_COMP(__NR_msgrcv, sys_msgrcv, compat_sys_msgrcv)
#घोषणा __NR_msgsnd 189
__SC_COMP(__NR_msgsnd, sys_msgsnd, compat_sys_msgsnd)

/* ipc/sem.c */
#घोषणा __NR_semget 190
__SYSCALL(__NR_semget, sys_semget)
#घोषणा __NR_semctl 191
__SC_COMP(__NR_semctl, sys_semctl, compat_sys_semctl)
#अगर defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#घोषणा __NR_semसमयकरोp 192
__SC_3264(__NR_semसमयकरोp, sys_semसमयकरोp_समय32, sys_semसमयकरोp)
#पूर्ण_अगर
#घोषणा __NR_semop 193
__SYSCALL(__NR_semop, sys_semop)

/* ipc/shm.c */
#घोषणा __NR_shmget 194
__SYSCALL(__NR_shmget, sys_shmget)
#घोषणा __NR_shmctl 195
__SC_COMP(__NR_shmctl, sys_shmctl, compat_sys_shmctl)
#घोषणा __NR_shmat 196
__SC_COMP(__NR_shmat, sys_shmat, compat_sys_shmat)
#घोषणा __NR_shmdt 197
__SYSCALL(__NR_shmdt, sys_shmdt)

/* net/socket.c */
#घोषणा __NR_socket 198
__SYSCALL(__NR_socket, sys_socket)
#घोषणा __NR_socketpair 199
__SYSCALL(__NR_socketpair, sys_socketpair)
#घोषणा __NR_bind 200
__SYSCALL(__NR_bind, sys_bind)
#घोषणा __NR_listen 201
__SYSCALL(__NR_listen, sys_listen)
#घोषणा __NR_accept 202
__SYSCALL(__NR_accept, sys_accept)
#घोषणा __NR_connect 203
__SYSCALL(__NR_connect, sys_connect)
#घोषणा __NR_माला_लोockname 204
__SYSCALL(__NR_माला_लोockname, sys_माला_लोockname)
#घोषणा __NR_getpeername 205
__SYSCALL(__NR_getpeername, sys_getpeername)
#घोषणा __NR_sendto 206
__SYSCALL(__NR_sendto, sys_sendto)
#घोषणा __NR_recvfrom 207
__SC_COMP(__NR_recvfrom, sys_recvfrom, compat_sys_recvfrom)
#घोषणा __NR_setsockopt 208
__SC_COMP(__NR_setsockopt, sys_setsockopt, sys_setsockopt)
#घोषणा __NR_माला_लोockopt 209
__SC_COMP(__NR_माला_लोockopt, sys_माला_लोockopt, sys_माला_लोockopt)
#घोषणा __NR_shutकरोwn 210
__SYSCALL(__NR_shutकरोwn, sys_shutकरोwn)
#घोषणा __NR_sendmsg 211
__SC_COMP(__NR_sendmsg, sys_sendmsg, compat_sys_sendmsg)
#घोषणा __NR_recvmsg 212
__SC_COMP(__NR_recvmsg, sys_recvmsg, compat_sys_recvmsg)

/* mm/filemap.c */
#घोषणा __NR_पढ़ोahead 213
__SC_COMP(__NR_पढ़ोahead, sys_पढ़ोahead, compat_sys_पढ़ोahead)

/* mm/nommu.c, also with MMU */
#घोषणा __NR_brk 214
__SYSCALL(__NR_brk, sys_brk)
#घोषणा __NR_munmap 215
__SYSCALL(__NR_munmap, sys_munmap)
#घोषणा __NR_mremap 216
__SYSCALL(__NR_mremap, sys_mremap)

/* security/keys/keyctl.c */
#घोषणा __NR_add_key 217
__SYSCALL(__NR_add_key, sys_add_key)
#घोषणा __NR_request_key 218
__SYSCALL(__NR_request_key, sys_request_key)
#घोषणा __NR_keyctl 219
__SC_COMP(__NR_keyctl, sys_keyctl, compat_sys_keyctl)

/* arch/example/kernel/sys_example.c */
#घोषणा __NR_clone 220
__SYSCALL(__NR_clone, sys_clone)
#घोषणा __NR_execve 221
__SC_COMP(__NR_execve, sys_execve, compat_sys_execve)

#घोषणा __NR3264_mmap 222
__SC_3264(__NR3264_mmap, sys_mmap2, sys_mmap)
/* mm/fadvise.c */
#घोषणा __NR3264_fadvise64 223
__SC_COMP(__NR3264_fadvise64, sys_fadvise64_64, compat_sys_fadvise64_64)

/* mm/, CONFIG_MMU only */
#अगर_अघोषित __ARCH_NOMMU
#घोषणा __NR_swapon 224
__SYSCALL(__NR_swapon, sys_swapon)
#घोषणा __NR_swapoff 225
__SYSCALL(__NR_swapoff, sys_swapoff)
#घोषणा __NR_mprotect 226
__SYSCALL(__NR_mprotect, sys_mprotect)
#घोषणा __NR_msync 227
__SYSCALL(__NR_msync, sys_msync)
#घोषणा __NR_mlock 228
__SYSCALL(__NR_mlock, sys_mlock)
#घोषणा __NR_munlock 229
__SYSCALL(__NR_munlock, sys_munlock)
#घोषणा __NR_mlockall 230
__SYSCALL(__NR_mlockall, sys_mlockall)
#घोषणा __NR_munlockall 231
__SYSCALL(__NR_munlockall, sys_munlockall)
#घोषणा __NR_mincore 232
__SYSCALL(__NR_mincore, sys_mincore)
#घोषणा __NR_madvise 233
__SYSCALL(__NR_madvise, sys_madvise)
#घोषणा __NR_remap_file_pages 234
__SYSCALL(__NR_remap_file_pages, sys_remap_file_pages)
#घोषणा __NR_mbind 235
__SC_COMP(__NR_mbind, sys_mbind, compat_sys_mbind)
#घोषणा __NR_get_mempolicy 236
__SC_COMP(__NR_get_mempolicy, sys_get_mempolicy, compat_sys_get_mempolicy)
#घोषणा __NR_set_mempolicy 237
__SC_COMP(__NR_set_mempolicy, sys_set_mempolicy, compat_sys_set_mempolicy)
#घोषणा __NR_migrate_pages 238
__SC_COMP(__NR_migrate_pages, sys_migrate_pages, compat_sys_migrate_pages)
#घोषणा __NR_move_pages 239
__SC_COMP(__NR_move_pages, sys_move_pages, compat_sys_move_pages)
#पूर्ण_अगर

#घोषणा __NR_rt_tgsigqueueinfo 240
__SC_COMP(__NR_rt_tgsigqueueinfo, sys_rt_tgsigqueueinfo, \
	  compat_sys_rt_tgsigqueueinfo)
#घोषणा __NR_perf_event_खोलो 241
__SYSCALL(__NR_perf_event_खोलो, sys_perf_event_खोलो)
#घोषणा __NR_accept4 242
__SYSCALL(__NR_accept4, sys_accept4)
#अगर defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#घोषणा __NR_recvmmsg 243
__SC_COMP_3264(__NR_recvmmsg, sys_recvmmsg_समय32, sys_recvmmsg, compat_sys_recvmmsg_समय32)
#पूर्ण_अगर

/*
 * Architectures may provide up to 16 syscalls of their own
 * starting with this value.
 */
#घोषणा __NR_arch_specअगरic_syscall 244

#अगर defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#घोषणा __NR_रुको4 260
__SC_COMP(__NR_रुको4, sys_रुको4, compat_sys_रुको4)
#पूर्ण_अगर
#घोषणा __NR_prlimit64 261
__SYSCALL(__NR_prlimit64, sys_prlimit64)
#घोषणा __NR_fanotअगरy_init 262
__SYSCALL(__NR_fanotअगरy_init, sys_fanotअगरy_init)
#घोषणा __NR_fanotअगरy_mark 263
__SYSCALL(__NR_fanotअगरy_mark, sys_fanotअगरy_mark)
#घोषणा __NR_name_to_handle_at         264
__SYSCALL(__NR_name_to_handle_at, sys_name_to_handle_at)
#घोषणा __NR_खोलो_by_handle_at         265
__SYSCALL(__NR_खोलो_by_handle_at, sys_खोलो_by_handle_at)
#अगर defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#घोषणा __NR_घड़ी_adjसमय 266
__SC_3264(__NR_घड़ी_adjसमय, sys_घड़ी_adjसमय32, sys_घड़ी_adjसमय)
#पूर्ण_अगर
#घोषणा __NR_syncfs 267
__SYSCALL(__NR_syncfs, sys_syncfs)
#घोषणा __NR_setns 268
__SYSCALL(__NR_setns, sys_setns)
#घोषणा __NR_sendmmsg 269
__SC_COMP(__NR_sendmmsg, sys_sendmmsg, compat_sys_sendmmsg)
#घोषणा __NR_process_vm_पढ़ोv 270
__SYSCALL(__NR_process_vm_पढ़ोv, sys_process_vm_पढ़ोv)
#घोषणा __NR_process_vm_ग_लिखोv 271
__SYSCALL(__NR_process_vm_ग_लिखोv, sys_process_vm_ग_लिखोv)
#घोषणा __NR_kcmp 272
__SYSCALL(__NR_kcmp, sys_kcmp)
#घोषणा __NR_finit_module 273
__SYSCALL(__NR_finit_module, sys_finit_module)
#घोषणा __NR_sched_setattr 274
__SYSCALL(__NR_sched_setattr, sys_sched_setattr)
#घोषणा __NR_sched_getattr 275
__SYSCALL(__NR_sched_getattr, sys_sched_getattr)
#घोषणा __NR_नामat2 276
__SYSCALL(__NR_नामat2, sys_नामat2)
#घोषणा __NR_seccomp 277
__SYSCALL(__NR_seccomp, sys_seccomp)
#घोषणा __NR_getअक्रमom 278
__SYSCALL(__NR_getअक्रमom, sys_getअक्रमom)
#घोषणा __NR_memfd_create 279
__SYSCALL(__NR_memfd_create, sys_memfd_create)
#घोषणा __NR_bpf 280
__SYSCALL(__NR_bpf, sys_bpf)
#घोषणा __NR_execveat 281
__SC_COMP(__NR_execveat, sys_execveat, compat_sys_execveat)
#घोषणा __NR_userfaultfd 282
__SYSCALL(__NR_userfaultfd, sys_userfaultfd)
#घोषणा __NR_membarrier 283
__SYSCALL(__NR_membarrier, sys_membarrier)
#घोषणा __NR_mlock2 284
__SYSCALL(__NR_mlock2, sys_mlock2)
#घोषणा __NR_copy_file_range 285
__SYSCALL(__NR_copy_file_range, sys_copy_file_range)
#घोषणा __NR_pपढ़ोv2 286
__SC_COMP(__NR_pपढ़ोv2, sys_pपढ़ोv2, compat_sys_pपढ़ोv2)
#घोषणा __NR_pग_लिखोv2 287
__SC_COMP(__NR_pग_लिखोv2, sys_pग_लिखोv2, compat_sys_pग_लिखोv2)
#घोषणा __NR_pkey_mprotect 288
__SYSCALL(__NR_pkey_mprotect, sys_pkey_mprotect)
#घोषणा __NR_pkey_alloc 289
__SYSCALL(__NR_pkey_alloc,    sys_pkey_alloc)
#घोषणा __NR_pkey_मुक्त 290
__SYSCALL(__NR_pkey_मुक्त,     sys_pkey_मुक्त)
#घोषणा __NR_statx 291
__SYSCALL(__NR_statx,     sys_statx)
#अगर defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#घोषणा __NR_io_pgetevents 292
__SC_COMP_3264(__NR_io_pgetevents, sys_io_pgetevents_समय32, sys_io_pgetevents, compat_sys_io_pgetevents)
#पूर्ण_अगर
#घोषणा __NR_rseq 293
__SYSCALL(__NR_rseq, sys_rseq)
#घोषणा __NR_kexec_file_load 294
__SYSCALL(__NR_kexec_file_load,     sys_kexec_file_load)
/* 295 through 402 are unasचिन्हित to sync up with generic numbers, करोn't use */
#अगर __BITS_PER_LONG == 32
#घोषणा __NR_घड़ी_समय_लो64 403
__SYSCALL(__NR_घड़ी_समय_लो64, sys_घड़ी_समय_लो)
#घोषणा __NR_घड़ी_समय_रखो64 404
__SYSCALL(__NR_घड़ी_समय_रखो64, sys_घड़ी_समय_रखो)
#घोषणा __NR_घड़ी_adjसमय64 405
__SYSCALL(__NR_घड़ी_adjसमय64, sys_घड़ी_adjसमय)
#घोषणा __NR_घड़ी_getres_समय64 406
__SYSCALL(__NR_घड़ी_getres_समय64, sys_घड़ी_getres)
#घोषणा __NR_घड़ी_nanosleep_समय64 407
__SYSCALL(__NR_घड़ी_nanosleep_समय64, sys_घड़ी_nanosleep)
#घोषणा __NR_समयr_समय_लो64 408
__SYSCALL(__NR_समयr_समय_लो64, sys_समयr_समय_लो)
#घोषणा __NR_समयr_समय_रखो64 409
__SYSCALL(__NR_समयr_समय_रखो64, sys_समयr_समय_रखो)
#घोषणा __NR_समयrfd_समय_लो64 410
__SYSCALL(__NR_समयrfd_समय_लो64, sys_समयrfd_समय_लो)
#घोषणा __NR_समयrfd_समय_रखो64 411
__SYSCALL(__NR_समयrfd_समय_रखो64, sys_समयrfd_समय_रखो)
#घोषणा __NR_uसमयnsat_समय64 412
__SYSCALL(__NR_uसमयnsat_समय64, sys_uसमयnsat)
#घोषणा __NR_pselect6_समय64 413
__SC_COMP(__NR_pselect6_समय64, sys_pselect6, compat_sys_pselect6_समय64)
#घोषणा __NR_ppoll_समय64 414
__SC_COMP(__NR_ppoll_समय64, sys_ppoll, compat_sys_ppoll_समय64)
#घोषणा __NR_io_pgetevents_समय64 416
__SYSCALL(__NR_io_pgetevents_समय64, sys_io_pgetevents)
#घोषणा __NR_recvmmsg_समय64 417
__SC_COMP(__NR_recvmmsg_समय64, sys_recvmmsg, compat_sys_recvmmsg_समय64)
#घोषणा __NR_mq_समयdsend_समय64 418
__SYSCALL(__NR_mq_समयdsend_समय64, sys_mq_समयdsend)
#घोषणा __NR_mq_समयdreceive_समय64 419
__SYSCALL(__NR_mq_समयdreceive_समय64, sys_mq_समयdreceive)
#घोषणा __NR_semसमयकरोp_समय64 420
__SYSCALL(__NR_semसमयकरोp_समय64, sys_semसमयकरोp)
#घोषणा __NR_rt_sigसमयdरुको_समय64 421
__SC_COMP(__NR_rt_sigसमयdरुको_समय64, sys_rt_sigसमयdरुको, compat_sys_rt_sigसमयdरुको_समय64)
#घोषणा __NR_futex_समय64 422
__SYSCALL(__NR_futex_समय64, sys_futex)
#घोषणा __NR_sched_rr_get_पूर्णांकerval_समय64 423
__SYSCALL(__NR_sched_rr_get_पूर्णांकerval_समय64, sys_sched_rr_get_पूर्णांकerval)
#पूर्ण_अगर

#घोषणा __NR_pidfd_send_संकेत 424
__SYSCALL(__NR_pidfd_send_संकेत, sys_pidfd_send_संकेत)
#घोषणा __NR_io_uring_setup 425
__SYSCALL(__NR_io_uring_setup, sys_io_uring_setup)
#घोषणा __NR_io_uring_enter 426
__SYSCALL(__NR_io_uring_enter, sys_io_uring_enter)
#घोषणा __NR_io_uring_रेजिस्टर 427
__SYSCALL(__NR_io_uring_रेजिस्टर, sys_io_uring_रेजिस्टर)
#घोषणा __NR_खोलो_tree 428
__SYSCALL(__NR_खोलो_tree, sys_खोलो_tree)
#घोषणा __NR_move_mount 429
__SYSCALL(__NR_move_mount, sys_move_mount)
#घोषणा __NR_fsखोलो 430
__SYSCALL(__NR_fsखोलो, sys_fsखोलो)
#घोषणा __NR_fsconfig 431
__SYSCALL(__NR_fsconfig, sys_fsconfig)
#घोषणा __NR_fsmount 432
__SYSCALL(__NR_fsmount, sys_fsmount)
#घोषणा __NR_fspick 433
__SYSCALL(__NR_fspick, sys_fspick)
#घोषणा __NR_pidfd_खोलो 434
__SYSCALL(__NR_pidfd_खोलो, sys_pidfd_खोलो)
#अगर_घोषित __ARCH_WANT_SYS_CLONE3
#घोषणा __NR_clone3 435
__SYSCALL(__NR_clone3, sys_clone3)
#पूर्ण_अगर
#घोषणा __NR_बंद_range 436
__SYSCALL(__NR_बंद_range, sys_बंद_range)

#घोषणा __NR_खोलोat2 437
__SYSCALL(__NR_खोलोat2, sys_खोलोat2)
#घोषणा __NR_pidfd_getfd 438
__SYSCALL(__NR_pidfd_getfd, sys_pidfd_getfd)
#घोषणा __NR_faccessat2 439
__SYSCALL(__NR_faccessat2, sys_faccessat2)
#घोषणा __NR_process_madvise 440
__SYSCALL(__NR_process_madvise, sys_process_madvise)
#घोषणा __NR_epoll_pरुको2 441
__SC_COMP(__NR_epoll_pरुको2, sys_epoll_pरुको2, compat_sys_epoll_pरुको2)
#घोषणा __NR_mount_setattr 442
__SYSCALL(__NR_mount_setattr, sys_mount_setattr)
/* 443 is reserved क्रम quotactl_path */

#घोषणा __NR_landlock_create_ruleset 444
__SYSCALL(__NR_landlock_create_ruleset, sys_landlock_create_ruleset)
#घोषणा __NR_landlock_add_rule 445
__SYSCALL(__NR_landlock_add_rule, sys_landlock_add_rule)
#घोषणा __NR_landlock_restrict_self 446
__SYSCALL(__NR_landlock_restrict_self, sys_landlock_restrict_self)

#अघोषित __NR_syscalls
#घोषणा __NR_syscalls 447

/*
 * 32 bit प्रणालीs traditionally used dअगरferent
 * syscalls क्रम off_t and loff_t arguments, जबतक
 * 64 bit प्रणालीs only need the off_t version.
 * For new 32 bit platक्रमms, there is no need to
 * implement the old 32 bit off_t syscalls, so
 * they take dअगरferent names.
 * Here we map the numbers so that both versions
 * use the same syscall table layout.
 */
#अगर __BITS_PER_LONG == 64 && !defined(__SYSCALL_COMPAT)
#घोषणा __NR_fcntl __NR3264_fcntl
#घोषणा __NR_statfs __NR3264_statfs
#घोषणा __NR_ख_स्थितिfs __NR3264_ख_स्थितिfs
#घोषणा __NR_truncate __NR3264_truncate
#घोषणा __NR_ftruncate __NR3264_ftruncate
#घोषणा __NR_lseek __NR3264_lseek
#घोषणा __NR_sendfile __NR3264_sendfile
#अगर defined(__ARCH_WANT_NEW_STAT) || defined(__ARCH_WANT_STAT64)
#घोषणा __NR_newख_स्थितिat __NR3264_ख_स्थितिat
#घोषणा __NR_ख_स्थिति __NR3264_ख_स्थिति
#पूर्ण_अगर
#घोषणा __NR_mmap __NR3264_mmap
#घोषणा __NR_fadvise64 __NR3264_fadvise64
#अगर_घोषित __NR3264_stat
#घोषणा __NR_stat __NR3264_stat
#घोषणा __NR_lstat __NR3264_lstat
#पूर्ण_अगर
#अन्यथा
#घोषणा __NR_fcntl64 __NR3264_fcntl
#घोषणा __NR_statfs64 __NR3264_statfs
#घोषणा __NR_ख_स्थितिfs64 __NR3264_ख_स्थितिfs
#घोषणा __NR_truncate64 __NR3264_truncate
#घोषणा __NR_ftruncate64 __NR3264_ftruncate
#घोषणा __NR_llseek __NR3264_lseek
#घोषणा __NR_sendfile64 __NR3264_sendfile
#अगर defined(__ARCH_WANT_NEW_STAT) || defined(__ARCH_WANT_STAT64)
#घोषणा __NR_ख_स्थितिat64 __NR3264_ख_स्थितिat
#घोषणा __NR_ख_स्थिति64 __NR3264_ख_स्थिति
#पूर्ण_अगर
#घोषणा __NR_mmap2 __NR3264_mmap
#घोषणा __NR_fadvise64_64 __NR3264_fadvise64
#अगर_घोषित __NR3264_stat
#घोषणा __NR_stat64 __NR3264_stat
#घोषणा __NR_lstat64 __NR3264_lstat
#पूर्ण_अगर
#पूर्ण_अगर
