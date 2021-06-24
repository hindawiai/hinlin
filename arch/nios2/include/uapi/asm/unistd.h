<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2013 Altera Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

 #घोषणा sys_mmap2 sys_mmap_pgoff

#घोषणा __ARCH_WANT_RENAMEAT
#घोषणा __ARCH_WANT_STAT64
#घोषणा __ARCH_WANT_SET_GET_RLIMIT
#घोषणा __ARCH_WANT_TIME32_SYSCALLS

/* Use the standard ABI क्रम syscalls */
#समावेश <यंत्र-generic/unistd.h>

/* Additional Nios II specअगरic syscalls. */
#घोषणा __NR_cacheflush (__NR_arch_specअगरic_syscall)
__SYSCALL(__NR_cacheflush, sys_cacheflush)
