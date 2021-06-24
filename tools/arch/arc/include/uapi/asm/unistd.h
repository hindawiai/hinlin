<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

/******** no-legacy-syscalls-ABI *******/

/*
 * Non-typical guard macro to enable inclusion twice in ARCH sys.c
 * That is how the Generic syscall wrapper generator works
 */
#अगर !defined(_UAPI_ASM_ARC_UNISTD_H) || defined(__SYSCALL)
#घोषणा _UAPI_ASM_ARC_UNISTD_H

#घोषणा __ARCH_WANT_RENAMEAT
#घोषणा __ARCH_WANT_STAT64
#घोषणा __ARCH_WANT_SET_GET_RLIMIT
#घोषणा __ARCH_WANT_SYS_EXECVE
#घोषणा __ARCH_WANT_SYS_CLONE
#घोषणा __ARCH_WANT_SYS_VFORK
#घोषणा __ARCH_WANT_SYS_FORK
#घोषणा __ARCH_WANT_TIME32_SYSCALLS

#घोषणा sys_mmap2 sys_mmap_pgoff

#समावेश <यंत्र-generic/unistd.h>

#घोषणा NR_syscalls	__NR_syscalls

/* Generic syscall (fs/fileप्रणालीs.c - lost in यंत्र-generic/unistd.h */
#घोषणा __NR_sysfs		(__NR_arch_specअगरic_syscall + 3)

/* ARC specअगरic syscall */
#घोषणा __NR_cacheflush		(__NR_arch_specअगरic_syscall + 0)
#घोषणा __NR_arc_settls		(__NR_arch_specअगरic_syscall + 1)
#घोषणा __NR_arc_gettls		(__NR_arch_specअगरic_syscall + 2)
#घोषणा __NR_arc_usr_cmpxchg	(__NR_arch_specअगरic_syscall + 4)

__SYSCALL(__NR_cacheflush, sys_cacheflush)
__SYSCALL(__NR_arc_settls, sys_arc_settls)
__SYSCALL(__NR_arc_gettls, sys_arc_gettls)
__SYSCALL(__NR_arc_usr_cmpxchg, sys_arc_usr_cmpxchg)
__SYSCALL(__NR_sysfs, sys_sysfs)

#अघोषित __SYSCALL

#पूर्ण_अगर
