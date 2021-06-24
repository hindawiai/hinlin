<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#घोषणा sys_mmap2 sys_mmap_pgoff

#घोषणा __ARCH_WANT_RENAMEAT
#घोषणा __ARCH_WANT_STAT64
#घोषणा __ARCH_WANT_SET_GET_RLIMIT
#घोषणा __ARCH_WANT_SYS_FORK
#घोषणा __ARCH_WANT_SYS_CLONE
#घोषणा __ARCH_WANT_SYS_CLONE3
#घोषणा __ARCH_WANT_TIME32_SYSCALLS

#समावेश <यंत्र-generic/unistd.h>

#घोषणा __NR_or1k_atomic __NR_arch_specअगरic_syscall
__SYSCALL(__NR_or1k_atomic, sys_or1k_atomic)
