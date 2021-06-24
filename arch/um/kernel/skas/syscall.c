<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/seccomp.h>
#समावेश <kern_util.h>
#समावेश <sysdep/ptrace.h>
#समावेश <sysdep/ptrace_user.h>
#समावेश <sysdep/syscalls.h>
#समावेश <linux/समय-पूर्णांकernal.h>
#समावेश <यंत्र/unistd.h>

व्योम handle_syscall(काष्ठा uml_pt_regs *r)
अणु
	काष्ठा pt_regs *regs = container_of(r, काष्ठा pt_regs, regs);
	पूर्णांक syscall;

	/*
	 * If we have infinite CPU resources, then make every syscall also a
	 * preemption poपूर्णांक, since we करोn't have any other preemption in this
	 * हाल, and kernel thपढ़ोs would basically never run until userspace
	 * went to sleep, even अगर said userspace पूर्णांकeracts with the kernel in
	 * various ways.
	 */
	अगर (समय_प्रकारravel_mode == TT_MODE_INFCPU ||
	    समय_प्रकारravel_mode == TT_MODE_EXTERNAL)
		schedule();

	/* Initialize the syscall number and शेष वापस value. */
	UPT_SYSCALL_NR(r) = PT_SYSCALL_NR(r->gp);
	PT_REGS_SET_SYSCALL_RETURN(regs, -ENOSYS);

	अगर (syscall_trace_enter(regs))
		जाओ out;

	/* Do the seccomp check after ptrace; failures should be fast. */
	अगर (secure_computing() == -1)
		जाओ out;

	syscall = UPT_SYSCALL_NR(r);
	अगर (syscall >= 0 && syscall <= __NR_syscall_max)
		PT_REGS_SET_SYSCALL_RETURN(regs,
				EXECUTE_SYSCALL(syscall, regs));

out:
	syscall_trace_leave(regs);
पूर्ण
