<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_घोषित CONFIG_COMPAT
#घोषणा __ARCH_WANT_COMPAT_STAT64
#घोषणा __ARCH_WANT_SYS_GETHOSTNAME
#घोषणा __ARCH_WANT_SYS_PAUSE
#घोषणा __ARCH_WANT_SYS_GETPGRP
#घोषणा __ARCH_WANT_SYS_NICE
#घोषणा __ARCH_WANT_SYS_SIGPENDING
#घोषणा __ARCH_WANT_SYS_SIGPROCMASK
#घोषणा __ARCH_WANT_COMPAT_SYS_SENDखाता
#घोषणा __ARCH_WANT_SYS_UTIME32
#घोषणा __ARCH_WANT_SYS_FORK
#घोषणा __ARCH_WANT_SYS_VFORK

/*
 * Compat syscall numbers used by the AArch64 kernel.
 */
#घोषणा __NR_compat_restart_syscall	0
#घोषणा __NR_compat_निकास		1
#घोषणा __NR_compat_पढ़ो		3
#घोषणा __NR_compat_ग_लिखो		4
#घोषणा __NR_compat_समय_लोofday	78
#घोषणा __NR_compat_sigवापस		119
#घोषणा __NR_compat_rt_sigवापस	173
#घोषणा __NR_compat_घड़ी_समय_लो	263
#घोषणा __NR_compat_घड़ी_getres	264
#घोषणा __NR_compat_घड़ी_समय_लो64	403
#घोषणा __NR_compat_घड़ी_getres_समय64	406

/*
 * The following SVCs are ARM निजी.
 */
#घोषणा __ARM_NR_COMPAT_BASE		0x0f0000
#घोषणा __ARM_NR_compat_cacheflush	(__ARM_NR_COMPAT_BASE + 2)
#घोषणा __ARM_NR_compat_set_tls		(__ARM_NR_COMPAT_BASE + 5)
#घोषणा __ARM_NR_COMPAT_END		(__ARM_NR_COMPAT_BASE + 0x800)

#घोषणा __NR_compat_syscalls		447
#पूर्ण_अगर

#घोषणा __ARCH_WANT_SYS_CLONE

#अगर_अघोषित __COMPAT_SYSCALL_NR
#समावेश <uapi/यंत्र/unistd.h>
#पूर्ण_अगर

#घोषणा NR_syscalls (__NR_syscalls)
