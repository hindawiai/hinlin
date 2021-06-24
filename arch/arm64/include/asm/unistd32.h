<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AArch32 (compat) प्रणाली call definitions.
 *
 * Copyright (C) 2001-2005 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */

#अगर_अघोषित __SYSCALL
#घोषणा __SYSCALL(x, y)
#पूर्ण_अगर

#घोषणा __NR_restart_syscall 0
__SYSCALL(__NR_restart_syscall, sys_restart_syscall)
#घोषणा __NR_निकास 1
__SYSCALL(__NR_निकास, sys_निकास)
#घोषणा __NR_विभाजन 2
__SYSCALL(__NR_विभाजन, sys_विभाजन)
#घोषणा __NR_पढ़ो 3
__SYSCALL(__NR_पढ़ो, sys_पढ़ो)
#घोषणा __NR_ग_लिखो 4
__SYSCALL(__NR_ग_लिखो, sys_ग_लिखो)
#घोषणा __NR_खोलो 5
__SYSCALL(__NR_खोलो, compat_sys_खोलो)
#घोषणा __NR_बंद 6
__SYSCALL(__NR_बंद, sys_बंद)
			/* 7 was sys_रुकोpid */
__SYSCALL(7, sys_ni_syscall)
#घोषणा __NR_creat 8
__SYSCALL(__NR_creat, sys_creat)
#घोषणा __NR_link 9
__SYSCALL(__NR_link, sys_link)
#घोषणा __NR_unlink 10
__SYSCALL(__NR_unlink, sys_unlink)
#घोषणा __NR_execve 11
__SYSCALL(__NR_execve, compat_sys_execve)
#घोषणा __NR_स_बदलो 12
__SYSCALL(__NR_स_बदलो, sys_स_बदलो)
			/* 13 was sys_समय */
__SYSCALL(13, sys_ni_syscall)
#घोषणा __NR_mknod 14
__SYSCALL(__NR_mknod, sys_mknod)
#घोषणा __NR_chmod 15
__SYSCALL(__NR_chmod, sys_chmod)
#घोषणा __NR_lchown 16
__SYSCALL(__NR_lchown, sys_lchown16)
			/* 17 was sys_अवरोध */
__SYSCALL(17, sys_ni_syscall)
			/* 18 was sys_stat */
__SYSCALL(18, sys_ni_syscall)
#घोषणा __NR_lseek 19
__SYSCALL(__NR_lseek, compat_sys_lseek)
#घोषणा __NR_getpid 20
__SYSCALL(__NR_getpid, sys_getpid)
#घोषणा __NR_mount 21
__SYSCALL(__NR_mount, sys_mount)
			/* 22 was sys_umount */
__SYSCALL(22, sys_ni_syscall)
#घोषणा __NR_setuid 23
__SYSCALL(__NR_setuid, sys_setuid16)
#घोषणा __NR_getuid 24
__SYSCALL(__NR_getuid, sys_getuid16)
			/* 25 was sys_sसमय */
__SYSCALL(25, sys_ni_syscall)
#घोषणा __NR_ptrace 26
__SYSCALL(__NR_ptrace, compat_sys_ptrace)
			/* 27 was sys_alarm */
__SYSCALL(27, sys_ni_syscall)
			/* 28 was sys_ख_स्थिति */
__SYSCALL(28, sys_ni_syscall)
#घोषणा __NR_छोड़ो 29
__SYSCALL(__NR_छोड़ो, sys_छोड़ो)
			/* 30 was sys_uसमय */
__SYSCALL(30, sys_ni_syscall)
			/* 31 was sys_stty */
__SYSCALL(31, sys_ni_syscall)
			/* 32 was sys_gtty */
__SYSCALL(32, sys_ni_syscall)
#घोषणा __NR_access 33
__SYSCALL(__NR_access, sys_access)
#घोषणा __NR_nice 34
__SYSCALL(__NR_nice, sys_nice)
			/* 35 was sys_fसमय */
__SYSCALL(35, sys_ni_syscall)
#घोषणा __NR_sync 36
__SYSCALL(__NR_sync, sys_sync)
#घोषणा __NR_समाप्त 37
__SYSCALL(__NR_समाप्त, sys_समाप्त)
#घोषणा __NR_नाम 38
__SYSCALL(__NR_नाम, sys_नाम)
#घोषणा __NR_सूची_गढ़ो 39
__SYSCALL(__NR_सूची_गढ़ो, sys_सूची_गढ़ो)
#घोषणा __NR_सूची_हटाओ 40
__SYSCALL(__NR_सूची_हटाओ, sys_सूची_हटाओ)
#घोषणा __NR_dup 41
__SYSCALL(__NR_dup, sys_dup)
#घोषणा __NR_pipe 42
__SYSCALL(__NR_pipe, sys_pipe)
#घोषणा __NR_बार 43
__SYSCALL(__NR_बार, compat_sys_बार)
			/* 44 was sys_prof */
__SYSCALL(44, sys_ni_syscall)
#घोषणा __NR_brk 45
__SYSCALL(__NR_brk, sys_brk)
#घोषणा __NR_setgid 46
__SYSCALL(__NR_setgid, sys_setgid16)
#घोषणा __NR_getgid 47
__SYSCALL(__NR_getgid, sys_getgid16)
			/* 48 was sys_संकेत */
__SYSCALL(48, sys_ni_syscall)
#घोषणा __NR_geteuid 49
__SYSCALL(__NR_geteuid, sys_geteuid16)
#घोषणा __NR_getegid 50
__SYSCALL(__NR_getegid, sys_getegid16)
#घोषणा __NR_acct 51
__SYSCALL(__NR_acct, sys_acct)
#घोषणा __NR_umount2 52
__SYSCALL(__NR_umount2, sys_umount)
			/* 53 was sys_lock */
__SYSCALL(53, sys_ni_syscall)
#घोषणा __NR_ioctl 54
__SYSCALL(__NR_ioctl, compat_sys_ioctl)
#घोषणा __NR_fcntl 55
__SYSCALL(__NR_fcntl, compat_sys_fcntl)
			/* 56 was sys_mpx */
__SYSCALL(56, sys_ni_syscall)
#घोषणा __NR_setpgid 57
__SYSCALL(__NR_setpgid, sys_setpgid)
			/* 58 was sys_ulimit */
__SYSCALL(58, sys_ni_syscall)
			/* 59 was sys_olduname */
__SYSCALL(59, sys_ni_syscall)
#घोषणा __NR_umask 60
__SYSCALL(__NR_umask, sys_umask)
#घोषणा __NR_chroot 61
__SYSCALL(__NR_chroot, sys_chroot)
#घोषणा __NR_ustat 62
__SYSCALL(__NR_ustat, compat_sys_ustat)
#घोषणा __NR_dup2 63
__SYSCALL(__NR_dup2, sys_dup2)
#घोषणा __NR_getppid 64
__SYSCALL(__NR_getppid, sys_getppid)
#घोषणा __NR_getpgrp 65
__SYSCALL(__NR_getpgrp, sys_getpgrp)
#घोषणा __NR_setsid 66
__SYSCALL(__NR_setsid, sys_setsid)
#घोषणा __NR_sigaction 67
__SYSCALL(__NR_sigaction, compat_sys_sigaction)
			/* 68 was sys_sgeपंचांगask */
__SYSCALL(68, sys_ni_syscall)
			/* 69 was sys_sseपंचांगask */
__SYSCALL(69, sys_ni_syscall)
#घोषणा __NR_setreuid 70
__SYSCALL(__NR_setreuid, sys_setreuid16)
#घोषणा __NR_setregid 71
__SYSCALL(__NR_setregid, sys_setregid16)
#घोषणा __NR_संक_रोको 72
__SYSCALL(__NR_संक_रोको, sys_संक_रोको)
#घोषणा __NR_संक_बाकी 73
__SYSCALL(__NR_संक_बाकी, compat_sys_संक_बाकी)
#घोषणा __NR_sethostname 74
__SYSCALL(__NR_sethostname, sys_sethostname)
#घोषणा __NR_setrlimit 75
__SYSCALL(__NR_setrlimit, compat_sys_setrlimit)
			/* 76 was compat_sys_getrlimit */
__SYSCALL(76, sys_ni_syscall)
#घोषणा __NR_getrusage 77
__SYSCALL(__NR_getrusage, compat_sys_getrusage)
#घोषणा __NR_समय_लोofday 78
__SYSCALL(__NR_समय_लोofday, compat_sys_समय_लोofday)
#घोषणा __NR_समय_रखोofday 79
__SYSCALL(__NR_समय_रखोofday, compat_sys_समय_रखोofday)
#घोषणा __NR_getgroups 80
__SYSCALL(__NR_getgroups, sys_getgroups16)
#घोषणा __NR_setgroups 81
__SYSCALL(__NR_setgroups, sys_setgroups16)
			/* 82 was compat_sys_select */
__SYSCALL(82, sys_ni_syscall)
#घोषणा __NR_symlink 83
__SYSCALL(__NR_symlink, sys_symlink)
			/* 84 was sys_lstat */
__SYSCALL(84, sys_ni_syscall)
#घोषणा __NR_पढ़ोlink 85
__SYSCALL(__NR_पढ़ोlink, sys_पढ़ोlink)
#घोषणा __NR_uselib 86
__SYSCALL(__NR_uselib, sys_uselib)
#घोषणा __NR_swapon 87
__SYSCALL(__NR_swapon, sys_swapon)
#घोषणा __NR_reboot 88
__SYSCALL(__NR_reboot, sys_reboot)
			/* 89 was sys_सूची_पढ़ो */
__SYSCALL(89, sys_ni_syscall)
			/* 90 was sys_mmap */
__SYSCALL(90, sys_ni_syscall)
#घोषणा __NR_munmap 91
__SYSCALL(__NR_munmap, sys_munmap)
#घोषणा __NR_truncate 92
__SYSCALL(__NR_truncate, compat_sys_truncate)
#घोषणा __NR_ftruncate 93
__SYSCALL(__NR_ftruncate, compat_sys_ftruncate)
#घोषणा __NR_fchmod 94
__SYSCALL(__NR_fchmod, sys_fchmod)
#घोषणा __NR_fchown 95
__SYSCALL(__NR_fchown, sys_fchown16)
#घोषणा __NR_getpriority 96
__SYSCALL(__NR_getpriority, sys_getpriority)
#घोषणा __NR_setpriority 97
__SYSCALL(__NR_setpriority, sys_setpriority)
			/* 98 was sys_profil */
__SYSCALL(98, sys_ni_syscall)
#घोषणा __NR_statfs 99
__SYSCALL(__NR_statfs, compat_sys_statfs)
#घोषणा __NR_ख_स्थितिfs 100
__SYSCALL(__NR_ख_स्थितिfs, compat_sys_ख_स्थितिfs)
			/* 101 was sys_ioperm */
__SYSCALL(101, sys_ni_syscall)
			/* 102 was sys_socketcall */
__SYSCALL(102, sys_ni_syscall)
#घोषणा __NR_syslog 103
__SYSCALL(__NR_syslog, sys_syslog)
#घोषणा __NR_setiसमयr 104
__SYSCALL(__NR_setiसमयr, compat_sys_setiसमयr)
#घोषणा __NR_getiसमयr 105
__SYSCALL(__NR_getiसमयr, compat_sys_getiसमयr)
#घोषणा __NR_stat 106
__SYSCALL(__NR_stat, compat_sys_newstat)
#घोषणा __NR_lstat 107
__SYSCALL(__NR_lstat, compat_sys_newlstat)
#घोषणा __NR_ख_स्थिति 108
__SYSCALL(__NR_ख_स्थिति, compat_sys_newख_स्थिति)
			/* 109 was sys_uname */
__SYSCALL(109, sys_ni_syscall)
			/* 110 was sys_iopl */
__SYSCALL(110, sys_ni_syscall)
#घोषणा __NR_vhangup 111
__SYSCALL(__NR_vhangup, sys_vhangup)
			/* 112 was sys_idle */
__SYSCALL(112, sys_ni_syscall)
			/* 113 was sys_syscall */
__SYSCALL(113, sys_ni_syscall)
#घोषणा __NR_रुको4 114
__SYSCALL(__NR_रुको4, compat_sys_रुको4)
#घोषणा __NR_swapoff 115
__SYSCALL(__NR_swapoff, sys_swapoff)
#घोषणा __NR_sysinfo 116
__SYSCALL(__NR_sysinfo, compat_sys_sysinfo)
			/* 117 was sys_ipc */
__SYSCALL(117, sys_ni_syscall)
#घोषणा __NR_fsync 118
__SYSCALL(__NR_fsync, sys_fsync)
#घोषणा __NR_sigवापस 119
__SYSCALL(__NR_sigवापस, compat_sys_sigवापस)
#घोषणा __NR_clone 120
__SYSCALL(__NR_clone, sys_clone)
#घोषणा __NR_setकरोमुख्यname 121
__SYSCALL(__NR_setकरोमुख्यname, sys_setकरोमुख्यname)
#घोषणा __NR_uname 122
__SYSCALL(__NR_uname, sys_newuname)
			/* 123 was sys_modअगरy_ldt */
__SYSCALL(123, sys_ni_syscall)
#घोषणा __NR_adjसमयx 124
__SYSCALL(__NR_adjसमयx, sys_adjसमयx_समय32)
#घोषणा __NR_mprotect 125
__SYSCALL(__NR_mprotect, sys_mprotect)
#घोषणा __NR_sigprocmask 126
__SYSCALL(__NR_sigprocmask, compat_sys_sigprocmask)
			/* 127 was sys_create_module */
__SYSCALL(127, sys_ni_syscall)
#घोषणा __NR_init_module 128
__SYSCALL(__NR_init_module, sys_init_module)
#घोषणा __NR_delete_module 129
__SYSCALL(__NR_delete_module, sys_delete_module)
			/* 130 was sys_get_kernel_syms */
__SYSCALL(130, sys_ni_syscall)
#घोषणा __NR_quotactl 131
__SYSCALL(__NR_quotactl, sys_quotactl)
#घोषणा __NR_getpgid 132
__SYSCALL(__NR_getpgid, sys_getpgid)
#घोषणा __NR_fस_बदलो 133
__SYSCALL(__NR_fस_बदलो, sys_fस_बदलो)
#घोषणा __NR_bdflush 134
__SYSCALL(__NR_bdflush, sys_bdflush)
#घोषणा __NR_sysfs 135
__SYSCALL(__NR_sysfs, sys_sysfs)
#घोषणा __NR_personality 136
__SYSCALL(__NR_personality, sys_personality)
			/* 137 was sys_afs_syscall */
__SYSCALL(137, sys_ni_syscall)
#घोषणा __NR_setfsuid 138
__SYSCALL(__NR_setfsuid, sys_setfsuid16)
#घोषणा __NR_setfsgid 139
__SYSCALL(__NR_setfsgid, sys_setfsgid16)
#घोषणा __NR__llseek 140
__SYSCALL(__NR__llseek, sys_llseek)
#घोषणा __NR_getdents 141
__SYSCALL(__NR_getdents, compat_sys_getdents)
#घोषणा __NR__newselect 142
__SYSCALL(__NR__newselect, compat_sys_select)
#घोषणा __NR_flock 143
__SYSCALL(__NR_flock, sys_flock)
#घोषणा __NR_msync 144
__SYSCALL(__NR_msync, sys_msync)
#घोषणा __NR_पढ़ोv 145
__SYSCALL(__NR_पढ़ोv, sys_पढ़ोv)
#घोषणा __NR_ग_लिखोv 146
__SYSCALL(__NR_ग_लिखोv, sys_ग_लिखोv)
#घोषणा __NR_माला_लोid 147
__SYSCALL(__NR_माला_लोid, sys_माला_लोid)
#घोषणा __NR_fdatasync 148
__SYSCALL(__NR_fdatasync, sys_fdatasync)
			/* 149 was sys_sysctl */
__SYSCALL(149, sys_ni_syscall)
#घोषणा __NR_mlock 150
__SYSCALL(__NR_mlock, sys_mlock)
#घोषणा __NR_munlock 151
__SYSCALL(__NR_munlock, sys_munlock)
#घोषणा __NR_mlockall 152
__SYSCALL(__NR_mlockall, sys_mlockall)
#घोषणा __NR_munlockall 153
__SYSCALL(__NR_munlockall, sys_munlockall)
#घोषणा __NR_sched_setparam 154
__SYSCALL(__NR_sched_setparam, sys_sched_setparam)
#घोषणा __NR_sched_getparam 155
__SYSCALL(__NR_sched_getparam, sys_sched_getparam)
#घोषणा __NR_sched_setscheduler 156
__SYSCALL(__NR_sched_setscheduler, sys_sched_setscheduler)
#घोषणा __NR_sched_माला_लोcheduler 157
__SYSCALL(__NR_sched_माला_लोcheduler, sys_sched_माला_लोcheduler)
#घोषणा __NR_sched_yield 158
__SYSCALL(__NR_sched_yield, sys_sched_yield)
#घोषणा __NR_sched_get_priority_max 159
__SYSCALL(__NR_sched_get_priority_max, sys_sched_get_priority_max)
#घोषणा __NR_sched_get_priority_min 160
__SYSCALL(__NR_sched_get_priority_min, sys_sched_get_priority_min)
#घोषणा __NR_sched_rr_get_पूर्णांकerval 161
__SYSCALL(__NR_sched_rr_get_पूर्णांकerval, sys_sched_rr_get_पूर्णांकerval_समय32)
#घोषणा __NR_nanosleep 162
__SYSCALL(__NR_nanosleep, sys_nanosleep_समय32)
#घोषणा __NR_mremap 163
__SYSCALL(__NR_mremap, sys_mremap)
#घोषणा __NR_setresuid 164
__SYSCALL(__NR_setresuid, sys_setresuid16)
#घोषणा __NR_getresuid 165
__SYSCALL(__NR_getresuid, sys_getresuid16)
			/* 166 was sys_vm86 */
__SYSCALL(166, sys_ni_syscall)
			/* 167 was sys_query_module */
__SYSCALL(167, sys_ni_syscall)
#घोषणा __NR_poll 168
__SYSCALL(__NR_poll, sys_poll)
#घोषणा __NR_nfsservctl 169
__SYSCALL(__NR_nfsservctl, sys_ni_syscall)
#घोषणा __NR_setresgid 170
__SYSCALL(__NR_setresgid, sys_setresgid16)
#घोषणा __NR_getresgid 171
__SYSCALL(__NR_getresgid, sys_getresgid16)
#घोषणा __NR_prctl 172
__SYSCALL(__NR_prctl, sys_prctl)
#घोषणा __NR_rt_sigवापस 173
__SYSCALL(__NR_rt_sigवापस, compat_sys_rt_sigवापस)
#घोषणा __NR_rt_sigaction 174
__SYSCALL(__NR_rt_sigaction, compat_sys_rt_sigaction)
#घोषणा __NR_rt_sigprocmask 175
__SYSCALL(__NR_rt_sigprocmask, compat_sys_rt_sigprocmask)
#घोषणा __NR_rt_संक_बाकी 176
__SYSCALL(__NR_rt_संक_बाकी, compat_sys_rt_संक_बाकी)
#घोषणा __NR_rt_sigसमयdरुको 177
__SYSCALL(__NR_rt_sigसमयdरुको, compat_sys_rt_sigसमयdरुको_समय32)
#घोषणा __NR_rt_sigqueueinfo 178
__SYSCALL(__NR_rt_sigqueueinfo, compat_sys_rt_sigqueueinfo)
#घोषणा __NR_rt_संक_रोको 179
__SYSCALL(__NR_rt_संक_रोको, compat_sys_rt_संक_रोको)
#घोषणा __NR_pपढ़ो64 180
__SYSCALL(__NR_pपढ़ो64, compat_sys_aarch32_pपढ़ो64)
#घोषणा __NR_pग_लिखो64 181
__SYSCALL(__NR_pग_लिखो64, compat_sys_aarch32_pग_लिखो64)
#घोषणा __NR_chown 182
__SYSCALL(__NR_chown, sys_chown16)
#घोषणा __NR_अ_लोwd 183
__SYSCALL(__NR_अ_लोwd, sys_अ_लोwd)
#घोषणा __NR_capget 184
__SYSCALL(__NR_capget, sys_capget)
#घोषणा __NR_capset 185
__SYSCALL(__NR_capset, sys_capset)
#घोषणा __NR_sigaltstack 186
__SYSCALL(__NR_sigaltstack, compat_sys_sigaltstack)
#घोषणा __NR_sendfile 187
__SYSCALL(__NR_sendfile, compat_sys_sendfile)
			/* 188 reserved */
__SYSCALL(188, sys_ni_syscall)
			/* 189 reserved */
__SYSCALL(189, sys_ni_syscall)
#घोषणा __NR_vविभाजन 190
__SYSCALL(__NR_vविभाजन, sys_vविभाजन)
#घोषणा __NR_ugetrlimit 191	/* SuS compliant getrlimit */
__SYSCALL(__NR_ugetrlimit, compat_sys_getrlimit)		/* SuS compliant getrlimit */
#घोषणा __NR_mmap2 192
__SYSCALL(__NR_mmap2, compat_sys_aarch32_mmap2)
#घोषणा __NR_truncate64 193
__SYSCALL(__NR_truncate64, compat_sys_aarch32_truncate64)
#घोषणा __NR_ftruncate64 194
__SYSCALL(__NR_ftruncate64, compat_sys_aarch32_ftruncate64)
#घोषणा __NR_stat64 195
__SYSCALL(__NR_stat64, sys_stat64)
#घोषणा __NR_lstat64 196
__SYSCALL(__NR_lstat64, sys_lstat64)
#घोषणा __NR_ख_स्थिति64 197
__SYSCALL(__NR_ख_स्थिति64, sys_ख_स्थिति64)
#घोषणा __NR_lchown32 198
__SYSCALL(__NR_lchown32, sys_lchown)
#घोषणा __NR_getuid32 199
__SYSCALL(__NR_getuid32, sys_getuid)
#घोषणा __NR_getgid32 200
__SYSCALL(__NR_getgid32, sys_getgid)
#घोषणा __NR_geteuid32 201
__SYSCALL(__NR_geteuid32, sys_geteuid)
#घोषणा __NR_getegid32 202
__SYSCALL(__NR_getegid32, sys_getegid)
#घोषणा __NR_setreuid32 203
__SYSCALL(__NR_setreuid32, sys_setreuid)
#घोषणा __NR_setregid32 204
__SYSCALL(__NR_setregid32, sys_setregid)
#घोषणा __NR_getgroups32 205
__SYSCALL(__NR_getgroups32, sys_getgroups)
#घोषणा __NR_setgroups32 206
__SYSCALL(__NR_setgroups32, sys_setgroups)
#घोषणा __NR_fchown32 207
__SYSCALL(__NR_fchown32, sys_fchown)
#घोषणा __NR_setresuid32 208
__SYSCALL(__NR_setresuid32, sys_setresuid)
#घोषणा __NR_getresuid32 209
__SYSCALL(__NR_getresuid32, sys_getresuid)
#घोषणा __NR_setresgid32 210
__SYSCALL(__NR_setresgid32, sys_setresgid)
#घोषणा __NR_getresgid32 211
__SYSCALL(__NR_getresgid32, sys_getresgid)
#घोषणा __NR_chown32 212
__SYSCALL(__NR_chown32, sys_chown)
#घोषणा __NR_setuid32 213
__SYSCALL(__NR_setuid32, sys_setuid)
#घोषणा __NR_setgid32 214
__SYSCALL(__NR_setgid32, sys_setgid)
#घोषणा __NR_setfsuid32 215
__SYSCALL(__NR_setfsuid32, sys_setfsuid)
#घोषणा __NR_setfsgid32 216
__SYSCALL(__NR_setfsgid32, sys_setfsgid)
#घोषणा __NR_getdents64 217
__SYSCALL(__NR_getdents64, sys_getdents64)
#घोषणा __NR_pivot_root 218
__SYSCALL(__NR_pivot_root, sys_pivot_root)
#घोषणा __NR_mincore 219
__SYSCALL(__NR_mincore, sys_mincore)
#घोषणा __NR_madvise 220
__SYSCALL(__NR_madvise, sys_madvise)
#घोषणा __NR_fcntl64 221
__SYSCALL(__NR_fcntl64, compat_sys_fcntl64)
			/* 222 क्रम tux */
__SYSCALL(222, sys_ni_syscall)
			/* 223 is unused */
__SYSCALL(223, sys_ni_syscall)
#घोषणा __NR_gettid 224
__SYSCALL(__NR_gettid, sys_gettid)
#घोषणा __NR_पढ़ोahead 225
__SYSCALL(__NR_पढ़ोahead, compat_sys_aarch32_पढ़ोahead)
#घोषणा __NR_setxattr 226
__SYSCALL(__NR_setxattr, sys_setxattr)
#घोषणा __NR_lsetxattr 227
__SYSCALL(__NR_lsetxattr, sys_lsetxattr)
#घोषणा __NR_fsetxattr 228
__SYSCALL(__NR_fsetxattr, sys_fsetxattr)
#घोषणा __NR_getxattr 229
__SYSCALL(__NR_getxattr, sys_getxattr)
#घोषणा __NR_lgetxattr 230
__SYSCALL(__NR_lgetxattr, sys_lgetxattr)
#घोषणा __NR_fgetxattr 231
__SYSCALL(__NR_fgetxattr, sys_fgetxattr)
#घोषणा __NR_listxattr 232
__SYSCALL(__NR_listxattr, sys_listxattr)
#घोषणा __NR_llistxattr 233
__SYSCALL(__NR_llistxattr, sys_llistxattr)
#घोषणा __NR_flistxattr 234
__SYSCALL(__NR_flistxattr, sys_flistxattr)
#घोषणा __NR_हटाओxattr 235
__SYSCALL(__NR_हटाओxattr, sys_हटाओxattr)
#घोषणा __NR_lहटाओxattr 236
__SYSCALL(__NR_lहटाओxattr, sys_lहटाओxattr)
#घोषणा __NR_fहटाओxattr 237
__SYSCALL(__NR_fहटाओxattr, sys_fहटाओxattr)
#घोषणा __NR_tसमाप्त 238
__SYSCALL(__NR_tसमाप्त, sys_tसमाप्त)
#घोषणा __NR_sendfile64 239
__SYSCALL(__NR_sendfile64, sys_sendfile64)
#घोषणा __NR_futex 240
__SYSCALL(__NR_futex, sys_futex_समय32)
#घोषणा __NR_sched_setaffinity 241
__SYSCALL(__NR_sched_setaffinity, compat_sys_sched_setaffinity)
#घोषणा __NR_sched_getaffinity 242
__SYSCALL(__NR_sched_getaffinity, compat_sys_sched_getaffinity)
#घोषणा __NR_io_setup 243
__SYSCALL(__NR_io_setup, compat_sys_io_setup)
#घोषणा __NR_io_destroy 244
__SYSCALL(__NR_io_destroy, sys_io_destroy)
#घोषणा __NR_io_getevents 245
__SYSCALL(__NR_io_getevents, sys_io_getevents_समय32)
#घोषणा __NR_io_submit 246
__SYSCALL(__NR_io_submit, compat_sys_io_submit)
#घोषणा __NR_io_cancel 247
__SYSCALL(__NR_io_cancel, sys_io_cancel)
#घोषणा __NR_निकास_group 248
__SYSCALL(__NR_निकास_group, sys_निकास_group)
#घोषणा __NR_lookup_dcookie 249
__SYSCALL(__NR_lookup_dcookie, compat_sys_lookup_dcookie)
#घोषणा __NR_epoll_create 250
__SYSCALL(__NR_epoll_create, sys_epoll_create)
#घोषणा __NR_epoll_ctl 251
__SYSCALL(__NR_epoll_ctl, sys_epoll_ctl)
#घोषणा __NR_epoll_रुको 252
__SYSCALL(__NR_epoll_रुको, sys_epoll_रुको)
#घोषणा __NR_remap_file_pages 253
__SYSCALL(__NR_remap_file_pages, sys_remap_file_pages)
			/* 254 क्रम set_thपढ़ो_area */
__SYSCALL(254, sys_ni_syscall)
			/* 255 क्रम get_thपढ़ो_area */
__SYSCALL(255, sys_ni_syscall)
#घोषणा __NR_set_tid_address 256
__SYSCALL(__NR_set_tid_address, sys_set_tid_address)
#घोषणा __NR_समयr_create 257
__SYSCALL(__NR_समयr_create, compat_sys_समयr_create)
#घोषणा __NR_समयr_समय_रखो 258
__SYSCALL(__NR_समयr_समय_रखो, sys_समयr_समय_रखो32)
#घोषणा __NR_समयr_समय_लो 259
__SYSCALL(__NR_समयr_समय_लो, sys_समयr_समय_लो32)
#घोषणा __NR_समयr_getoverrun 260
__SYSCALL(__NR_समयr_getoverrun, sys_समयr_getoverrun)
#घोषणा __NR_समयr_delete 261
__SYSCALL(__NR_समयr_delete, sys_समयr_delete)
#घोषणा __NR_घड़ी_समय_रखो 262
__SYSCALL(__NR_घड़ी_समय_रखो, sys_घड़ी_समय_रखो32)
#घोषणा __NR_घड़ी_समय_लो 263
__SYSCALL(__NR_घड़ी_समय_लो, sys_घड़ी_समय_लो32)
#घोषणा __NR_घड़ी_getres 264
__SYSCALL(__NR_घड़ी_getres, sys_घड़ी_getres_समय32)
#घोषणा __NR_घड़ी_nanosleep 265
__SYSCALL(__NR_घड़ी_nanosleep, sys_घड़ी_nanosleep_समय32)
#घोषणा __NR_statfs64 266
__SYSCALL(__NR_statfs64, compat_sys_aarch32_statfs64)
#घोषणा __NR_ख_स्थितिfs64 267
__SYSCALL(__NR_ख_स्थितिfs64, compat_sys_aarch32_ख_स्थितिfs64)
#घोषणा __NR_tgसमाप्त 268
__SYSCALL(__NR_tgसमाप्त, sys_tgसमाप्त)
#घोषणा __NR_uबार 269
__SYSCALL(__NR_uबार, sys_uबार_समय32)
#घोषणा __NR_arm_fadvise64_64 270
__SYSCALL(__NR_arm_fadvise64_64, compat_sys_aarch32_fadvise64_64)
#घोषणा __NR_pciconfig_iobase 271
__SYSCALL(__NR_pciconfig_iobase, sys_pciconfig_iobase)
#घोषणा __NR_pciconfig_पढ़ो 272
__SYSCALL(__NR_pciconfig_पढ़ो, sys_pciconfig_पढ़ो)
#घोषणा __NR_pciconfig_ग_लिखो 273
__SYSCALL(__NR_pciconfig_ग_लिखो, sys_pciconfig_ग_लिखो)
#घोषणा __NR_mq_खोलो 274
__SYSCALL(__NR_mq_खोलो, compat_sys_mq_खोलो)
#घोषणा __NR_mq_unlink 275
__SYSCALL(__NR_mq_unlink, sys_mq_unlink)
#घोषणा __NR_mq_समयdsend 276
__SYSCALL(__NR_mq_समयdsend, sys_mq_समयdsend_समय32)
#घोषणा __NR_mq_समयdreceive 277
__SYSCALL(__NR_mq_समयdreceive, sys_mq_समयdreceive_समय32)
#घोषणा __NR_mq_notअगरy 278
__SYSCALL(__NR_mq_notअगरy, compat_sys_mq_notअगरy)
#घोषणा __NR_mq_माला_लोetattr 279
__SYSCALL(__NR_mq_माला_लोetattr, compat_sys_mq_माला_लोetattr)
#घोषणा __NR_रुकोid 280
__SYSCALL(__NR_रुकोid, compat_sys_रुकोid)
#घोषणा __NR_socket 281
__SYSCALL(__NR_socket, sys_socket)
#घोषणा __NR_bind 282
__SYSCALL(__NR_bind, sys_bind)
#घोषणा __NR_connect 283
__SYSCALL(__NR_connect, sys_connect)
#घोषणा __NR_listen 284
__SYSCALL(__NR_listen, sys_listen)
#घोषणा __NR_accept 285
__SYSCALL(__NR_accept, sys_accept)
#घोषणा __NR_माला_लोockname 286
__SYSCALL(__NR_माला_लोockname, sys_माला_लोockname)
#घोषणा __NR_getpeername 287
__SYSCALL(__NR_getpeername, sys_getpeername)
#घोषणा __NR_socketpair 288
__SYSCALL(__NR_socketpair, sys_socketpair)
#घोषणा __NR_send 289
__SYSCALL(__NR_send, sys_send)
#घोषणा __NR_sendto 290
__SYSCALL(__NR_sendto, sys_sendto)
#घोषणा __NR_recv 291
__SYSCALL(__NR_recv, compat_sys_recv)
#घोषणा __NR_recvfrom 292
__SYSCALL(__NR_recvfrom, compat_sys_recvfrom)
#घोषणा __NR_shutकरोwn 293
__SYSCALL(__NR_shutकरोwn, sys_shutकरोwn)
#घोषणा __NR_setsockopt 294
__SYSCALL(__NR_setsockopt, sys_setsockopt)
#घोषणा __NR_माला_लोockopt 295
__SYSCALL(__NR_माला_लोockopt, sys_माला_लोockopt)
#घोषणा __NR_sendmsg 296
__SYSCALL(__NR_sendmsg, compat_sys_sendmsg)
#घोषणा __NR_recvmsg 297
__SYSCALL(__NR_recvmsg, compat_sys_recvmsg)
#घोषणा __NR_semop 298
__SYSCALL(__NR_semop, sys_semop)
#घोषणा __NR_semget 299
__SYSCALL(__NR_semget, sys_semget)
#घोषणा __NR_semctl 300
__SYSCALL(__NR_semctl, compat_sys_old_semctl)
#घोषणा __NR_msgsnd 301
__SYSCALL(__NR_msgsnd, compat_sys_msgsnd)
#घोषणा __NR_msgrcv 302
__SYSCALL(__NR_msgrcv, compat_sys_msgrcv)
#घोषणा __NR_msgget 303
__SYSCALL(__NR_msgget, sys_msgget)
#घोषणा __NR_msgctl 304
__SYSCALL(__NR_msgctl, compat_sys_old_msgctl)
#घोषणा __NR_shmat 305
__SYSCALL(__NR_shmat, compat_sys_shmat)
#घोषणा __NR_shmdt 306
__SYSCALL(__NR_shmdt, sys_shmdt)
#घोषणा __NR_shmget 307
__SYSCALL(__NR_shmget, sys_shmget)
#घोषणा __NR_shmctl 308
__SYSCALL(__NR_shmctl, compat_sys_old_shmctl)
#घोषणा __NR_add_key 309
__SYSCALL(__NR_add_key, sys_add_key)
#घोषणा __NR_request_key 310
__SYSCALL(__NR_request_key, sys_request_key)
#घोषणा __NR_keyctl 311
__SYSCALL(__NR_keyctl, compat_sys_keyctl)
#घोषणा __NR_semसमयकरोp 312
__SYSCALL(__NR_semसमयकरोp, sys_semसमयकरोp_समय32)
#घोषणा __NR_vserver 313
__SYSCALL(__NR_vserver, sys_ni_syscall)
#घोषणा __NR_ioprio_set 314
__SYSCALL(__NR_ioprio_set, sys_ioprio_set)
#घोषणा __NR_ioprio_get 315
__SYSCALL(__NR_ioprio_get, sys_ioprio_get)
#घोषणा __NR_inotअगरy_init 316
__SYSCALL(__NR_inotअगरy_init, sys_inotअगरy_init)
#घोषणा __NR_inotअगरy_add_watch 317
__SYSCALL(__NR_inotअगरy_add_watch, sys_inotअगरy_add_watch)
#घोषणा __NR_inotअगरy_rm_watch 318
__SYSCALL(__NR_inotअगरy_rm_watch, sys_inotअगरy_rm_watch)
#घोषणा __NR_mbind 319
__SYSCALL(__NR_mbind, compat_sys_mbind)
#घोषणा __NR_get_mempolicy 320
__SYSCALL(__NR_get_mempolicy, compat_sys_get_mempolicy)
#घोषणा __NR_set_mempolicy 321
__SYSCALL(__NR_set_mempolicy, compat_sys_set_mempolicy)
#घोषणा __NR_खोलोat 322
__SYSCALL(__NR_खोलोat, compat_sys_खोलोat)
#घोषणा __NR_सूची_गढ़ोat 323
__SYSCALL(__NR_सूची_गढ़ोat, sys_सूची_गढ़ोat)
#घोषणा __NR_mknodat 324
__SYSCALL(__NR_mknodat, sys_mknodat)
#घोषणा __NR_fchownat 325
__SYSCALL(__NR_fchownat, sys_fchownat)
#घोषणा __NR_fuबारat 326
__SYSCALL(__NR_fuबारat, sys_fuबारat_समय32)
#घोषणा __NR_ख_स्थितिat64 327
__SYSCALL(__NR_ख_स्थितिat64, sys_ख_स्थितिat64)
#घोषणा __NR_unlinkat 328
__SYSCALL(__NR_unlinkat, sys_unlinkat)
#घोषणा __NR_नामat 329
__SYSCALL(__NR_नामat, sys_नामat)
#घोषणा __NR_linkat 330
__SYSCALL(__NR_linkat, sys_linkat)
#घोषणा __NR_symlinkat 331
__SYSCALL(__NR_symlinkat, sys_symlinkat)
#घोषणा __NR_पढ़ोlinkat 332
__SYSCALL(__NR_पढ़ोlinkat, sys_पढ़ोlinkat)
#घोषणा __NR_fchmodat 333
__SYSCALL(__NR_fchmodat, sys_fchmodat)
#घोषणा __NR_faccessat 334
__SYSCALL(__NR_faccessat, sys_faccessat)
#घोषणा __NR_pselect6 335
__SYSCALL(__NR_pselect6, compat_sys_pselect6_समय32)
#घोषणा __NR_ppoll 336
__SYSCALL(__NR_ppoll, compat_sys_ppoll_समय32)
#घोषणा __NR_unshare 337
__SYSCALL(__NR_unshare, sys_unshare)
#घोषणा __NR_set_robust_list 338
__SYSCALL(__NR_set_robust_list, compat_sys_set_robust_list)
#घोषणा __NR_get_robust_list 339
__SYSCALL(__NR_get_robust_list, compat_sys_get_robust_list)
#घोषणा __NR_splice 340
__SYSCALL(__NR_splice, sys_splice)
#घोषणा __NR_sync_file_range2 341
__SYSCALL(__NR_sync_file_range2, compat_sys_aarch32_sync_file_range2)
#घोषणा __NR_tee 342
__SYSCALL(__NR_tee, sys_tee)
#घोषणा __NR_vmsplice 343
__SYSCALL(__NR_vmsplice, sys_vmsplice)
#घोषणा __NR_move_pages 344
__SYSCALL(__NR_move_pages, compat_sys_move_pages)
#घोषणा __NR_अ_लोpu 345
__SYSCALL(__NR_अ_लोpu, sys_अ_लोpu)
#घोषणा __NR_epoll_pरुको 346
__SYSCALL(__NR_epoll_pरुको, compat_sys_epoll_pरुको)
#घोषणा __NR_kexec_load 347
__SYSCALL(__NR_kexec_load, compat_sys_kexec_load)
#घोषणा __NR_uसमयnsat 348
__SYSCALL(__NR_uसमयnsat, sys_uसमयnsat_समय32)
#घोषणा __NR_संकेतfd 349
__SYSCALL(__NR_संकेतfd, compat_sys_संकेतfd)
#घोषणा __NR_समयrfd_create 350
__SYSCALL(__NR_समयrfd_create, sys_समयrfd_create)
#घोषणा __NR_eventfd 351
__SYSCALL(__NR_eventfd, sys_eventfd)
#घोषणा __NR_fallocate 352
__SYSCALL(__NR_fallocate, compat_sys_aarch32_fallocate)
#घोषणा __NR_समयrfd_समय_रखो 353
__SYSCALL(__NR_समयrfd_समय_रखो, sys_समयrfd_समय_रखो32)
#घोषणा __NR_समयrfd_समय_लो 354
__SYSCALL(__NR_समयrfd_समय_लो, sys_समयrfd_समय_लो32)
#घोषणा __NR_संकेतfd4 355
__SYSCALL(__NR_संकेतfd4, compat_sys_संकेतfd4)
#घोषणा __NR_eventfd2 356
__SYSCALL(__NR_eventfd2, sys_eventfd2)
#घोषणा __NR_epoll_create1 357
__SYSCALL(__NR_epoll_create1, sys_epoll_create1)
#घोषणा __NR_dup3 358
__SYSCALL(__NR_dup3, sys_dup3)
#घोषणा __NR_pipe2 359
__SYSCALL(__NR_pipe2, sys_pipe2)
#घोषणा __NR_inotअगरy_init1 360
__SYSCALL(__NR_inotअगरy_init1, sys_inotअगरy_init1)
#घोषणा __NR_pपढ़ोv 361
__SYSCALL(__NR_pपढ़ोv, compat_sys_pपढ़ोv)
#घोषणा __NR_pग_लिखोv 362
__SYSCALL(__NR_pग_लिखोv, compat_sys_pग_लिखोv)
#घोषणा __NR_rt_tgsigqueueinfo 363
__SYSCALL(__NR_rt_tgsigqueueinfo, compat_sys_rt_tgsigqueueinfo)
#घोषणा __NR_perf_event_खोलो 364
__SYSCALL(__NR_perf_event_खोलो, sys_perf_event_खोलो)
#घोषणा __NR_recvmmsg 365
__SYSCALL(__NR_recvmmsg, compat_sys_recvmmsg_समय32)
#घोषणा __NR_accept4 366
__SYSCALL(__NR_accept4, sys_accept4)
#घोषणा __NR_fanotअगरy_init 367
__SYSCALL(__NR_fanotअगरy_init, sys_fanotअगरy_init)
#घोषणा __NR_fanotअगरy_mark 368
__SYSCALL(__NR_fanotअगरy_mark, compat_sys_fanotअगरy_mark)
#घोषणा __NR_prlimit64 369
__SYSCALL(__NR_prlimit64, sys_prlimit64)
#घोषणा __NR_name_to_handle_at 370
__SYSCALL(__NR_name_to_handle_at, sys_name_to_handle_at)
#घोषणा __NR_खोलो_by_handle_at 371
__SYSCALL(__NR_खोलो_by_handle_at, compat_sys_खोलो_by_handle_at)
#घोषणा __NR_घड़ी_adjसमय 372
__SYSCALL(__NR_घड़ी_adjसमय, sys_घड़ी_adjसमय32)
#घोषणा __NR_syncfs 373
__SYSCALL(__NR_syncfs, sys_syncfs)
#घोषणा __NR_sendmmsg 374
__SYSCALL(__NR_sendmmsg, compat_sys_sendmmsg)
#घोषणा __NR_setns 375
__SYSCALL(__NR_setns, sys_setns)
#घोषणा __NR_process_vm_पढ़ोv 376
__SYSCALL(__NR_process_vm_पढ़ोv, sys_process_vm_पढ़ोv)
#घोषणा __NR_process_vm_ग_लिखोv 377
__SYSCALL(__NR_process_vm_ग_लिखोv, sys_process_vm_ग_लिखोv)
#घोषणा __NR_kcmp 378
__SYSCALL(__NR_kcmp, sys_kcmp)
#घोषणा __NR_finit_module 379
__SYSCALL(__NR_finit_module, sys_finit_module)
#घोषणा __NR_sched_setattr 380
__SYSCALL(__NR_sched_setattr, sys_sched_setattr)
#घोषणा __NR_sched_getattr 381
__SYSCALL(__NR_sched_getattr, sys_sched_getattr)
#घोषणा __NR_नामat2 382
__SYSCALL(__NR_नामat2, sys_नामat2)
#घोषणा __NR_seccomp 383
__SYSCALL(__NR_seccomp, sys_seccomp)
#घोषणा __NR_getअक्रमom 384
__SYSCALL(__NR_getअक्रमom, sys_getअक्रमom)
#घोषणा __NR_memfd_create 385
__SYSCALL(__NR_memfd_create, sys_memfd_create)
#घोषणा __NR_bpf 386
__SYSCALL(__NR_bpf, sys_bpf)
#घोषणा __NR_execveat 387
__SYSCALL(__NR_execveat, compat_sys_execveat)
#घोषणा __NR_userfaultfd 388
__SYSCALL(__NR_userfaultfd, sys_userfaultfd)
#घोषणा __NR_membarrier 389
__SYSCALL(__NR_membarrier, sys_membarrier)
#घोषणा __NR_mlock2 390
__SYSCALL(__NR_mlock2, sys_mlock2)
#घोषणा __NR_copy_file_range 391
__SYSCALL(__NR_copy_file_range, sys_copy_file_range)
#घोषणा __NR_pपढ़ोv2 392
__SYSCALL(__NR_pपढ़ोv2, compat_sys_pपढ़ोv2)
#घोषणा __NR_pग_लिखोv2 393
__SYSCALL(__NR_pग_लिखोv2, compat_sys_pग_लिखोv2)
#घोषणा __NR_pkey_mprotect 394
__SYSCALL(__NR_pkey_mprotect, sys_pkey_mprotect)
#घोषणा __NR_pkey_alloc 395
__SYSCALL(__NR_pkey_alloc, sys_pkey_alloc)
#घोषणा __NR_pkey_मुक्त 396
__SYSCALL(__NR_pkey_मुक्त, sys_pkey_मुक्त)
#घोषणा __NR_statx 397
__SYSCALL(__NR_statx, sys_statx)
#घोषणा __NR_rseq 398
__SYSCALL(__NR_rseq, sys_rseq)
#घोषणा __NR_io_pgetevents 399
__SYSCALL(__NR_io_pgetevents, compat_sys_io_pgetevents)
#घोषणा __NR_migrate_pages 400
__SYSCALL(__NR_migrate_pages, compat_sys_migrate_pages)
#घोषणा __NR_kexec_file_load 401
__SYSCALL(__NR_kexec_file_load, sys_kexec_file_load)
/* 402 is unused */
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
__SYSCALL(__NR_pselect6_समय64, compat_sys_pselect6_समय64)
#घोषणा __NR_ppoll_समय64 414
__SYSCALL(__NR_ppoll_समय64, compat_sys_ppoll_समय64)
#घोषणा __NR_io_pgetevents_समय64 416
__SYSCALL(__NR_io_pgetevents_समय64, sys_io_pgetevents)
#घोषणा __NR_recvmmsg_समय64 417
__SYSCALL(__NR_recvmmsg_समय64, compat_sys_recvmmsg_समय64)
#घोषणा __NR_mq_समयdsend_समय64 418
__SYSCALL(__NR_mq_समयdsend_समय64, sys_mq_समयdsend)
#घोषणा __NR_mq_समयdreceive_समय64 419
__SYSCALL(__NR_mq_समयdreceive_समय64, sys_mq_समयdreceive)
#घोषणा __NR_semसमयकरोp_समय64 420
__SYSCALL(__NR_semसमयकरोp_समय64, sys_semसमयकरोp)
#घोषणा __NR_rt_sigसमयdरुको_समय64 421
__SYSCALL(__NR_rt_sigसमयdरुको_समय64, compat_sys_rt_sigसमयdरुको_समय64)
#घोषणा __NR_futex_समय64 422
__SYSCALL(__NR_futex_समय64, sys_futex)
#घोषणा __NR_sched_rr_get_पूर्णांकerval_समय64 423
__SYSCALL(__NR_sched_rr_get_पूर्णांकerval_समय64, sys_sched_rr_get_पूर्णांकerval)
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
#घोषणा __NR_clone3 435
__SYSCALL(__NR_clone3, sys_clone3)
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
__SYSCALL(__NR_epoll_pरुको2, compat_sys_epoll_pरुको2)
#घोषणा __NR_mount_setattr 442
__SYSCALL(__NR_mount_setattr, sys_mount_setattr)
/* 443 is reserved क्रम quotactl_path */
#घोषणा __NR_landlock_create_ruleset 444
__SYSCALL(__NR_landlock_create_ruleset, sys_landlock_create_ruleset)
#घोषणा __NR_landlock_add_rule 445
__SYSCALL(__NR_landlock_add_rule, sys_landlock_add_rule)
#घोषणा __NR_landlock_restrict_self 446
__SYSCALL(__NR_landlock_restrict_self, sys_landlock_restrict_self)

/*
 * Please add new compat syscalls above this comment and update
 * __NR_compat_syscalls in यंत्र/unistd.h.
 */
