<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* System call table क्रम x86-64. */

#समावेश <linux/linkage.h>
#समावेश <linux/sys.h>
#समावेश <linux/cache.h>
#समावेश <linux/syscalls.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/syscall.h>

#घोषणा __SYSCALL_X32(nr, sym)
#घोषणा __SYSCALL_COMMON(nr, sym) __SYSCALL_64(nr, sym)

#घोषणा __SYSCALL_64(nr, sym) बाह्य दीर्घ __x64_##sym(स्थिर काष्ठा pt_regs *);
#समावेश <यंत्र/syscalls_64.h>
#अघोषित __SYSCALL_64

#घोषणा __SYSCALL_64(nr, sym) [nr] = __x64_##sym,

यंत्रlinkage स्थिर sys_call_ptr_t sys_call_table[__NR_syscall_max+1] = अणु
	/*
	 * Smells like a compiler bug -- it करोesn't work
	 * when the & below is हटाओd.
	 */
	[0 ... __NR_syscall_max] = &__x64_sys_ni_syscall,
#समावेश <यंत्र/syscalls_64.h>
पूर्ण;
