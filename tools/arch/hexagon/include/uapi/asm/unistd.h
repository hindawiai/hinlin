<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Syscall support क्रम Hexagon
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fअगरth Floor, Boston, MA
 * 02110-1301, USA.
 */

/*
 *  The kernel pulls this unistd.h in three dअगरferent ways:
 *  1.  the "normal" way which माला_लो all the __NR defines
 *  2.  with __SYSCALL defined to produce function declarations
 *  3.  with __SYSCALL defined to produce syscall table initialization
 *  See also:  syscalltab.c
 */

#घोषणा sys_mmap2 sys_mmap_pgoff
#घोषणा __ARCH_WANT_RENAMEAT
#घोषणा __ARCH_WANT_STAT64
#घोषणा __ARCH_WANT_SET_GET_RLIMIT
#घोषणा __ARCH_WANT_SYS_EXECVE
#घोषणा __ARCH_WANT_SYS_CLONE
#घोषणा __ARCH_WANT_SYS_VFORK
#घोषणा __ARCH_WANT_SYS_FORK
#घोषणा __ARCH_WANT_TIME32_SYSCALLS

#समावेश <यंत्र-generic/unistd.h>
