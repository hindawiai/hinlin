<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mov_ss_trap.c: Exercise the bizarre side effects of a watchpoपूर्णांक on MOV SS
 *
 * This करोes MOV SS from a watchpoपूर्णांकed address followed by various
 * types of kernel entries.  A MOV SS that hits a watchpoपूर्णांक will queue
 * up a #DB trap but will not actually deliver that trap.  The trap
 * will be delivered after the next inकाष्ठाion instead.  The CPU's logic
 * seems to be:
 *
 *  - Any fault: drop the pending #DB trap.
 *  - INT $N, INT3, INTO, SYSCALL, SYSENTER: enter the kernel and then
 *    deliver #DB.
 *  - ICEBP: enter the kernel but करो not deliver the watchpoपूर्णांक trap
 *  - अवरोधpoपूर्णांक: only one #DB is delivered (phew!)
 *
 * There are plenty of ways क्रम a kernel to handle this incorrectly.  This
 * test tries to exercise all the हालs.
 *
 * This should mostly cover CVE-2018-1087 and CVE-2018-8897.
 */
#घोषणा _GNU_SOURCE

#समावेश <मानककोष.स>
#समावेश <sys/ptrace.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <sys/user.h>
#समावेश <sys/syscall.h>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <मानकघोष.स>
#समावेश <मानकपन.स>
#समावेश <err.h>
#समावेश <माला.स>
#समावेश <समलाँघ.स>
#समावेश <sys/prctl.h>

#घोषणा X86_EFLAGS_RF (1UL << 16)

#अगर __x86_64__
# define REG_IP REG_RIP
#अन्यथा
# define REG_IP REG_EIP
#पूर्ण_अगर

अचिन्हित लघु ss;
बाह्य अचिन्हित अक्षर अवरोधpoपूर्णांक_insn[];
sigलाँघ_बफ jmpbuf;
अटल अचिन्हित अक्षर altstack_data[SIGSTKSZ];

अटल व्योम enable_watchpoपूर्णांक(व्योम)
अणु
	pid_t parent = getpid();
	पूर्णांक status;

	pid_t child = विभाजन();
	अगर (child < 0)
		err(1, "fork");

	अगर (child) अणु
		अगर (रुकोpid(child, &status, 0) != child)
			err(1, "waitpid for child");
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ dr0, dr1, dr7;

		dr0 = (अचिन्हित दीर्घ)&ss;
		dr1 = (अचिन्हित दीर्घ)अवरोधpoपूर्णांक_insn;
		dr7 = ((1UL << 1) |	/* G0 */
		       (3UL << 16) |	/* RW0 = पढ़ो or ग_लिखो */
		       (1UL << 18) |	/* LEN0 = 2 bytes */
		       (1UL << 3));	/* G1, RW1 = insn */

		अगर (ptrace(PTRACE_ATTACH, parent, शून्य, शून्य) != 0)
			err(1, "PTRACE_ATTACH");

		अगर (रुकोpid(parent, &status, 0) != parent)
			err(1, "waitpid for child");

		अगर (ptrace(PTRACE_POKEUSER, parent, (व्योम *)दुरत्व(काष्ठा user, u_debugreg[0]), dr0) != 0)
			err(1, "PTRACE_POKEUSER DR0");

		अगर (ptrace(PTRACE_POKEUSER, parent, (व्योम *)दुरत्व(काष्ठा user, u_debugreg[1]), dr1) != 0)
			err(1, "PTRACE_POKEUSER DR1");

		अगर (ptrace(PTRACE_POKEUSER, parent, (व्योम *)दुरत्व(काष्ठा user, u_debugreg[7]), dr7) != 0)
			err(1, "PTRACE_POKEUSER DR7");

		म_लिखो("\tDR0 = %lx, DR1 = %lx, DR7 = %lx\n", dr0, dr1, dr7);

		अगर (ptrace(PTRACE_DETACH, parent, शून्य, शून्य) != 0)
			err(1, "PTRACE_DETACH");

		निकास(0);
	पूर्ण
पूर्ण

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

अटल अक्षर स्थिर * स्थिर signames[] = अणु
	[संक_अंश] = "SIGSEGV",
	[SIGBUS] = "SIBGUS",
	[SIGTRAP] = "SIGTRAP",
	[संक_अवैध] = "SIGILL",
पूर्ण;

अटल व्योम sigtrap(पूर्णांक sig, siginfo_t *si, व्योम *ctx_व्योम)
अणु
	ucontext_t *ctx = ctx_व्योम;

	म_लिखो("\tGot SIGTRAP with RIP=%lx, EFLAGS.RF=%d\n",
	       (अचिन्हित दीर्घ)ctx->uc_mcontext.gregs[REG_IP],
	       !!(ctx->uc_mcontext.gregs[REG_EFL] & X86_EFLAGS_RF));
पूर्ण

अटल व्योम handle_and_वापस(पूर्णांक sig, siginfo_t *si, व्योम *ctx_व्योम)
अणु
	ucontext_t *ctx = ctx_व्योम;

	म_लिखो("\tGot %s with RIP=%lx\n", signames[sig],
	       (अचिन्हित दीर्घ)ctx->uc_mcontext.gregs[REG_IP]);
पूर्ण

अटल व्योम handle_and_दीर्घ_लाँघ(पूर्णांक sig, siginfo_t *si, व्योम *ctx_व्योम)
अणु
	ucontext_t *ctx = ctx_व्योम;

	म_लिखो("\tGot %s with RIP=%lx\n", signames[sig],
	       (अचिन्हित दीर्घ)ctx->uc_mcontext.gregs[REG_IP]);

	sigदीर्घ_लाँघ(jmpbuf, 1);
पूर्ण

पूर्णांक मुख्य()
अणु
	अचिन्हित दीर्घ nr;

	यंत्र अस्थिर ("mov %%ss, %[ss]" : [ss] "=m" (ss));
	म_लिखो("\tSS = 0x%hx, &SS = 0x%p\n", ss, &ss);

	अगर (prctl(PR_SET_PTRACER, PR_SET_PTRACER_ANY, 0, 0, 0) == 0)
		म_लिखो("\tPR_SET_PTRACER_ANY succeeded\n");

	म_लिखो("\tSet up a watchpoint\n");
	sethandler(SIGTRAP, sigtrap, 0);
	enable_watchpoपूर्णांक();

	म_लिखो("[RUN]\tRead from watched memory (should get SIGTRAP)\n");
	यंत्र अस्थिर ("mov %[ss], %[tmp]" : [पंचांगp] "=r" (nr) : [ss] "m" (ss));

	म_लिखो("[RUN]\tMOV SS; INT3\n");
	यंत्र अस्थिर ("mov %[ss], %%ss; int3" :: [ss] "m" (ss));

	म_लिखो("[RUN]\tMOV SS; INT 3\n");
	यंत्र अस्थिर ("mov %[ss], %%ss; .byte 0xcd, 0x3" :: [ss] "m" (ss));

	म_लिखो("[RUN]\tMOV SS; CS CS INT3\n");
	यंत्र अस्थिर ("mov %[ss], %%ss; .byte 0x2e, 0x2e; int3" :: [ss] "m" (ss));

	म_लिखो("[RUN]\tMOV SS; CSx14 INT3\n");
	यंत्र अस्थिर ("mov %[ss], %%ss; .fill 14,1,0x2e; int3" :: [ss] "m" (ss));

	म_लिखो("[RUN]\tMOV SS; INT 4\n");
	sethandler(संक_अंश, handle_and_वापस, SA_RESETHAND);
	यंत्र अस्थिर ("mov %[ss], %%ss; int $4" :: [ss] "m" (ss));

#अगर_घोषित __i386__
	म_लिखो("[RUN]\tMOV SS; INTO\n");
	sethandler(संक_अंश, handle_and_वापस, SA_RESETHAND);
	nr = -1;
	यंत्र अस्थिर ("add $1, %[tmp]; mov %[ss], %%ss; into"
		      : [पंचांगp] "+r" (nr) : [ss] "m" (ss));
#पूर्ण_अगर

	अगर (sigबनाओ_लाँघ(jmpbuf, 1) == 0) अणु
		म_लिखो("[RUN]\tMOV SS; ICEBP\n");

		/* Some emulators (e.g. QEMU TCG) करोn't emulate ICEBP. */
		sethandler(संक_अवैध, handle_and_दीर्घ_लाँघ, SA_RESETHAND);

		यंत्र अस्थिर ("mov %[ss], %%ss; .byte 0xf1" :: [ss] "m" (ss));
	पूर्ण

	अगर (sigबनाओ_लाँघ(jmpbuf, 1) == 0) अणु
		म_लिखो("[RUN]\tMOV SS; CLI\n");
		sethandler(संक_अंश, handle_and_दीर्घ_लाँघ, SA_RESETHAND);
		यंत्र अस्थिर ("mov %[ss], %%ss; cli" :: [ss] "m" (ss));
	पूर्ण

	अगर (sigबनाओ_लाँघ(jmpbuf, 1) == 0) अणु
		म_लिखो("[RUN]\tMOV SS; #PF\n");
		sethandler(संक_अंश, handle_and_दीर्घ_लाँघ, SA_RESETHAND);
		यंत्र अस्थिर ("mov %[ss], %%ss; mov (-1), %[tmp]"
			      : [पंचांगp] "=r" (nr) : [ss] "m" (ss));
	पूर्ण

	/*
	 * INT $1: अगर #DB has DPL=3 and there isn't special handling,
	 * then the kernel will die.
	 */
	अगर (sigबनाओ_लाँघ(jmpbuf, 1) == 0) अणु
		म_लिखो("[RUN]\tMOV SS; INT 1\n");
		sethandler(संक_अंश, handle_and_दीर्घ_लाँघ, SA_RESETHAND);
		यंत्र अस्थिर ("mov %[ss], %%ss; int $1" :: [ss] "m" (ss));
	पूर्ण

#अगर_घोषित __x86_64__
	/*
	 * In principle, we should test 32-bit SYSCALL as well, but
	 * the calling convention is so unpredictable that it's
	 * not obviously worth the efक्रमt.
	 */
	अगर (sigबनाओ_लाँघ(jmpbuf, 1) == 0) अणु
		म_लिखो("[RUN]\tMOV SS; SYSCALL\n");
		sethandler(संक_अवैध, handle_and_दीर्घ_लाँघ, SA_RESETHAND);
		nr = SYS_getpid;
		/*
		 * Toggle the high bit of RSP to make it noncanonical to
		 * strengthen this test on non-SMAP प्रणालीs.
		 */
		यंत्र अस्थिर ("btc $63, %%rsp\n\t"
			      "mov %[ss], %%ss; syscall\n\t"
			      "btc $63, %%rsp"
			      : "+a" (nr) : [ss] "m" (ss)
			      : "rcx"
#अगर_घोषित __x86_64__
				, "r11"
#पूर्ण_अगर
			);
	पूर्ण
#पूर्ण_अगर

	म_लिखो("[RUN]\tMOV SS; breakpointed NOP\n");
	यंत्र अस्थिर ("mov %[ss], %%ss; breakpoint_insn: nop" :: [ss] "m" (ss));

	/*
	 * Invoking SYSENTER directly अवरोधs all the rules.  Just handle
	 * the संक_अंश.
	 */
	अगर (sigबनाओ_लाँघ(jmpbuf, 1) == 0) अणु
		म_लिखो("[RUN]\tMOV SS; SYSENTER\n");
		stack_t stack = अणु
			.ss_sp = altstack_data,
			.ss_size = SIGSTKSZ,
		पूर्ण;
		अगर (sigaltstack(&stack, शून्य) != 0)
			err(1, "sigaltstack");
		sethandler(संक_अंश, handle_and_दीर्घ_लाँघ, SA_RESETHAND | SA_ONSTACK);
		nr = SYS_getpid;
		/* Clear EBP first to make sure we segfault cleanly. */
		यंत्र अस्थिर ("xorl %%ebp, %%ebp; mov %[ss], %%ss; SYSENTER" : "+a" (nr)
			      : [ss] "m" (ss) : "flags", "rcx"
#अगर_घोषित __x86_64__
				, "r11"
#पूर्ण_अगर
			);

		/* We're unreachable here.  SYSENTER क्रममाला_लो RIP. */
	पूर्ण

	अगर (sigबनाओ_लाँघ(jmpbuf, 1) == 0) अणु
		म_लिखो("[RUN]\tMOV SS; INT $0x80\n");
		sethandler(संक_अंश, handle_and_दीर्घ_लाँघ, SA_RESETHAND);
		nr = 20;	/* compat getpid */
		यंत्र अस्थिर ("mov %[ss], %%ss; int $0x80"
			      : "+a" (nr) : [ss] "m" (ss)
			      : "flags"
#अगर_घोषित __x86_64__
				, "r8", "r9", "r10", "r11"
#पूर्ण_अगर
			);
	पूर्ण

	म_लिखो("[OK]\tI aten't dead\n");
	वापस 0;
पूर्ण
