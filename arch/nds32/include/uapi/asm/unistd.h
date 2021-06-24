<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
// Copyright (C) 2005-2017 Andes Technology Corporation

#घोषणा __ARCH_WANT_STAT64
#घोषणा __ARCH_WANT_SYNC_खाता_RANGE2
#घोषणा __ARCH_WANT_SET_GET_RLIMIT
#घोषणा __ARCH_WANT_TIME32_SYSCALLS

/* Use the standard ABI क्रम syscalls */
#समावेश <यंत्र-generic/unistd.h>

/* Additional NDS32 specअगरic syscalls. */
#घोषणा __NR_cacheflush		(__NR_arch_specअगरic_syscall)
#घोषणा __NR_fp_udfiex_crtl	(__NR_arch_specअगरic_syscall + 1)
__SYSCALL(__NR_cacheflush, sys_cacheflush)
__SYSCALL(__NR_fp_udfiex_crtl, sys_fp_udfiex_crtl)
