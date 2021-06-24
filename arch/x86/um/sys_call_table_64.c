<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System call table क्रम UML/x86-64, copied from arch/x86/kernel/syscall_*.c
 * with some changes क्रम UML.
 */

#समावेश <linux/linkage.h>
#समावेश <linux/sys.h>
#समावेश <linux/cache.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/syscall.h>

#घोषणा __NO_STUBS

/*
 * Below you can see, in terms of #घोषणा's, the dअगरferences between the x86-64
 * and the UML syscall table.
 */

/* Not going to be implemented by UML, since we have no hardware. */
#घोषणा sys_iopl sys_ni_syscall
#घोषणा sys_ioperm sys_ni_syscall

/*
 * The UML TLS problem. Note that x86_64 करोes not implement this, so the below
 * is needed only क्रम the ia32 compatibility.
 */

/* On UML we call it this way ("old" means it's not mmap2) */
#घोषणा sys_mmap old_mmap

#घोषणा stub_clone sys_clone
#घोषणा stub_विभाजन sys_विभाजन
#घोषणा stub_vविभाजन sys_vविभाजन
#घोषणा stub_execve sys_execve
#घोषणा stub_execveat sys_execveat
#घोषणा stub_rt_sigवापस sys_rt_sigवापस

#घोषणा __SYSCALL_X32(nr, sym)
#घोषणा __SYSCALL_COMMON(nr, sym) __SYSCALL_64(nr, sym)

#घोषणा __SYSCALL_64(nr, sym) बाह्य यंत्रlinkage दीर्घ sym(अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ) ;
#समावेश <यंत्र/syscalls_64.h>

#अघोषित __SYSCALL_64
#घोषणा __SYSCALL_64(nr, sym) [ nr ] = sym,

बाह्य यंत्रlinkage दीर्घ sys_ni_syscall(अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ);

स्थिर sys_call_ptr_t sys_call_table[] ____cacheline_aligned = अणु
	/*
	 * Smells like a compiler bug -- it करोesn't work
	 * when the & below is हटाओd.
	 */
	[0 ... __NR_syscall_max] = &sys_ni_syscall,
#समावेश <यंत्र/syscalls_64.h>
पूर्ण;

पूर्णांक syscall_table_size = माप(sys_call_table);
