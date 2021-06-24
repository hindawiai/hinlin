<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * syscall_arg_fault.c - tests faults 32-bit fast syscall stack args
 * Copyright (c) 2015 Andrew Lutomirski
 */

#घोषणा _GNU_SOURCE

#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <sys/संकेत.स>
#समावेश <sys/ucontext.h>
#समावेश <err.h>
#समावेश <समलाँघ.स>
#समावेश <त्रुटिसं.स>

#समावेश "helpers.h"

/* Our sigaltstack scratch space. */
अटल अचिन्हित अक्षर altstack_data[SIGSTKSZ];

अटल व्योम sethandler(पूर्णांक sig, व्योम (*handler)(पूर्णांक, siginfo_t *, व्योम *),
		       पूर्णांक flags)
अणु
	काष्ठा sigaction sa;
	स_रखो(&sa, 0, माप(sa));
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO | flags;
	sigemptyset(&sa.sa_mask);
	अगर (sigaction(sig, &sa, 0))
		err(1, "sigaction");
पूर्ण

अटल अस्थिर संक_पूर्ण_प्रकार sig_traps;
अटल sigलाँघ_बफ jmpbuf;

अटल अस्थिर संक_पूर्ण_प्रकार n_errs;

#अगर_घोषित __x86_64__
#घोषणा REG_AX REG_RAX
#घोषणा REG_IP REG_RIP
#अन्यथा
#घोषणा REG_AX REG_EAX
#घोषणा REG_IP REG_EIP
#पूर्ण_अगर

अटल व्योम sigsegv_or_sigbus(पूर्णांक sig, siginfo_t *info, व्योम *ctx_व्योम)
अणु
	ucontext_t *ctx = (ucontext_t*)ctx_व्योम;
	दीर्घ ax = (दीर्घ)ctx->uc_mcontext.gregs[REG_AX];

	अगर (ax != -EFAULT && ax != -ENOSYS) अणु
		म_लिखो("[FAIL]\tAX had the wrong value: 0x%lx\n",
		       (अचिन्हित दीर्घ)ax);
		म_लिखो("\tIP = 0x%lx\n", (अचिन्हित दीर्घ)ctx->uc_mcontext.gregs[REG_IP]);
		n_errs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tSeems okay\n");
	पूर्ण

	sigदीर्घ_लाँघ(jmpbuf, 1);
पूर्ण

अटल अस्थिर संक_पूर्ण_प्रकार sigtrap_consecutive_syscalls;

अटल व्योम sigtrap(पूर्णांक sig, siginfo_t *info, व्योम *ctx_व्योम)
अणु
	/*
	 * KVM has some bugs that can cause us to stop making progress.
	 * detect them and complain, but करोn't infinite loop or fail the
	 * test.
	 */

	ucontext_t *ctx = (ucontext_t*)ctx_व्योम;
	अचिन्हित लघु *ip = (अचिन्हित लघु *)ctx->uc_mcontext.gregs[REG_IP];

	अगर (*ip == 0x340f || *ip == 0x050f) अणु
		/* The trap was on SYSCALL or SYSENTER */
		sigtrap_consecutive_syscalls++;
		अगर (sigtrap_consecutive_syscalls > 3) अणु
			म_लिखो("[WARN]\tGot stuck single-stepping -- you probably have a KVM bug\n");
			sigदीर्घ_लाँघ(jmpbuf, 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		sigtrap_consecutive_syscalls = 0;
	पूर्ण
पूर्ण

अटल व्योम sigill(पूर्णांक sig, siginfo_t *info, व्योम *ctx_व्योम)
अणु
	ucontext_t *ctx = (ucontext_t*)ctx_व्योम;
	अचिन्हित लघु *ip = (अचिन्हित लघु *)ctx->uc_mcontext.gregs[REG_IP];

	अगर (*ip == 0x0b0f) अणु
		/* one of the ud2 inकाष्ठाions faulted */
		म_लिखो("[OK]\tSYSCALL returned normally\n");
	पूर्ण अन्यथा अणु
		म_लिखो("[SKIP]\tIllegal instruction\n");
	पूर्ण
	sigदीर्घ_लाँघ(jmpbuf, 1);
पूर्ण

पूर्णांक मुख्य()
अणु
	stack_t stack = अणु
		.ss_sp = altstack_data,
		.ss_size = SIGSTKSZ,
	पूर्ण;
	अगर (sigaltstack(&stack, शून्य) != 0)
		err(1, "sigaltstack");

	sethandler(संक_अंश, sigsegv_or_sigbus, SA_ONSTACK);
	/*
	 * The actual exception can vary.  On Atom CPUs, we get #SS
	 * instead of #PF when the vDSO fails to access the stack when
	 * ESP is too बंद to 2^32, and #SS causes SIGBUS.
	 */
	sethandler(SIGBUS, sigsegv_or_sigbus, SA_ONSTACK);
	sethandler(संक_अवैध, sigill, SA_ONSTACK);

	/*
	 * Exercise another nasty special हाल.  The 32-bit SYSCALL
	 * and SYSENTER inकाष्ठाions (even in compat mode) each
	 * clobber one रेजिस्टर.  A Linux प्रणाली call has a syscall
	 * number and six arguments, and the user stack poपूर्णांकer
	 * needs to live in some रेजिस्टर on वापस.  That means
	 * that we need eight रेजिस्टरs, but SYSCALL and SYSENTER
	 * only preserve seven रेजिस्टरs.  As a result, one argument
	 * ends up on the stack.  The stack is user memory, which
	 * means that the kernel can fail to पढ़ो it.
	 *
	 * The 32-bit fast प्रणाली calls करोn't have a defined ABI:
	 * we're supposed to invoke them through the vDSO.  So we'll
	 * fudge it: we set all regs to invalid poपूर्णांकer values and
	 * invoke the entry inकाष्ठाion.  The वापस will fail no
	 * matter what, and we completely lose our program state,
	 * but we can fix it up with a संकेत handler.
	 */

	म_लिखो("[RUN]\tSYSENTER with invalid state\n");
	अगर (sigबनाओ_लाँघ(jmpbuf, 1) == 0) अणु
		यंत्र अस्थिर (
			"movl $-1, %%eax\n\t"
			"movl $-1, %%ebx\n\t"
			"movl $-1, %%ecx\n\t"
			"movl $-1, %%edx\n\t"
			"movl $-1, %%esi\n\t"
			"movl $-1, %%edi\n\t"
			"movl $-1, %%ebp\n\t"
			"movl $-1, %%esp\n\t"
			"sysenter"
			: : : "memory", "flags");
	पूर्ण

	म_लिखो("[RUN]\tSYSCALL with invalid state\n");
	अगर (sigबनाओ_लाँघ(jmpbuf, 1) == 0) अणु
		यंत्र अस्थिर (
			"movl $-1, %%eax\n\t"
			"movl $-1, %%ebx\n\t"
			"movl $-1, %%ecx\n\t"
			"movl $-1, %%edx\n\t"
			"movl $-1, %%esi\n\t"
			"movl $-1, %%edi\n\t"
			"movl $-1, %%ebp\n\t"
			"movl $-1, %%esp\n\t"
			"syscall\n\t"
			"ud2"		/* make sure we recover cleanly */
			: : : "memory", "flags");
	पूर्ण

	म_लिखो("[RUN]\tSYSENTER with TF and invalid state\n");
	sethandler(SIGTRAP, sigtrap, SA_ONSTACK);

	अगर (sigबनाओ_लाँघ(jmpbuf, 1) == 0) अणु
		sigtrap_consecutive_syscalls = 0;
		set_eflags(get_eflags() | X86_EFLAGS_TF);
		यंत्र अस्थिर (
			"movl $-1, %%eax\n\t"
			"movl $-1, %%ebx\n\t"
			"movl $-1, %%ecx\n\t"
			"movl $-1, %%edx\n\t"
			"movl $-1, %%esi\n\t"
			"movl $-1, %%edi\n\t"
			"movl $-1, %%ebp\n\t"
			"movl $-1, %%esp\n\t"
			"sysenter"
			: : : "memory", "flags");
	पूर्ण
	set_eflags(get_eflags() & ~X86_EFLAGS_TF);

	म_लिखो("[RUN]\tSYSCALL with TF and invalid state\n");
	अगर (sigबनाओ_लाँघ(jmpbuf, 1) == 0) अणु
		sigtrap_consecutive_syscalls = 0;
		set_eflags(get_eflags() | X86_EFLAGS_TF);
		यंत्र अस्थिर (
			"movl $-1, %%eax\n\t"
			"movl $-1, %%ebx\n\t"
			"movl $-1, %%ecx\n\t"
			"movl $-1, %%edx\n\t"
			"movl $-1, %%esi\n\t"
			"movl $-1, %%edi\n\t"
			"movl $-1, %%ebp\n\t"
			"movl $-1, %%esp\n\t"
			"syscall\n\t"
			"ud2"		/* make sure we recover cleanly */
			: : : "memory", "flags");
	पूर्ण
	set_eflags(get_eflags() & ~X86_EFLAGS_TF);

#अगर_घोषित __x86_64__
	म_लिखो("[RUN]\tSYSENTER with TF, invalid state, and GSBASE < 0\n");

	अगर (sigबनाओ_लाँघ(jmpbuf, 1) == 0) अणु
		sigtrap_consecutive_syscalls = 0;

		यंत्र अस्थिर ("wrgsbase %%rax\n\t"
			      :: "a" (0xffffffffffff0000UL));

		set_eflags(get_eflags() | X86_EFLAGS_TF);
		यंत्र अस्थिर (
			"movl $-1, %%eax\n\t"
			"movl $-1, %%ebx\n\t"
			"movl $-1, %%ecx\n\t"
			"movl $-1, %%edx\n\t"
			"movl $-1, %%esi\n\t"
			"movl $-1, %%edi\n\t"
			"movl $-1, %%ebp\n\t"
			"movl $-1, %%esp\n\t"
			"sysenter"
			: : : "memory", "flags");
	पूर्ण
	set_eflags(get_eflags() & ~X86_EFLAGS_TF);
#पूर्ण_अगर

	वापस 0;
पूर्ण
