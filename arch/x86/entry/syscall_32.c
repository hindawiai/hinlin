<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* System call table क्रम i386. */

#समावेश <linux/linkage.h>
#समावेश <linux/sys.h>
#समावेश <linux/cache.h>
#समावेश <linux/syscalls.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/syscall.h>

#घोषणा __SYSCALL_I386(nr, sym) बाह्य दीर्घ __ia32_##sym(स्थिर काष्ठा pt_regs *);

#समावेश <यंत्र/syscalls_32.h>
#अघोषित __SYSCALL_I386

#घोषणा __SYSCALL_I386(nr, sym) [nr] = __ia32_##sym,

__visible स्थिर sys_call_ptr_t ia32_sys_call_table[__NR_ia32_syscall_max+1] = अणु
	/*
	 * Smells like a compiler bug -- it करोesn't work
	 * when the & below is हटाओd.
	 */
	[0 ... __NR_ia32_syscall_max] = &__ia32_sys_ni_syscall,
#समावेश <यंत्र/syscalls_32.h>
पूर्ण;
