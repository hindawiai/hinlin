<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2018 David Abdurachmanov <david.abdurachmanov@gmail.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#अगर_घोषित __LP64__
#घोषणा __ARCH_WANT_NEW_STAT
#घोषणा __ARCH_WANT_SET_GET_RLIMIT
#घोषणा __ARCH_WANT_SYS_CLONE3
#पूर्ण_अगर /* __LP64__ */

#समावेश <यंत्र-generic/unistd.h>

/*
 * Allows the inकाष्ठाion cache to be flushed from userspace.  Despite RISC-V
 * having a direct 'fence.i' inकाष्ठाion available to userspace (which we
 * can't trap!), that's not actually viable when running on Linux because the
 * kernel might schedule a process on another hart.  There is no way क्रम
 * userspace to handle this without invoking the kernel (as it करोesn't know the
 * thपढ़ो->hart mappings), so we've defined a RISC-V specअगरic प्रणाली call to
 * flush the inकाष्ठाion cache.
 *
 * __NR_riscv_flush_icache is defined to flush the inकाष्ठाion cache over an
 * address range, with the flush applying to either all thपढ़ोs or just the
 * caller.  We करोn't currently do anything with the address range, that's just
 * in there क्रम क्रमwards compatibility.
 */
#अगर_अघोषित __NR_riscv_flush_icache
#घोषणा __NR_riscv_flush_icache (__NR_arch_specअगरic_syscall + 15)
#पूर्ण_अगर
__SYSCALL(__NR_riscv_flush_icache, sys_riscv_flush_icache)
