<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * single_step_syscall.c - single-steps various x86 syscalls
 * Copyright (c) 2014-2015 Andrew Lutomirski
 *
 * This is a very simple series of tests that makes प्रणाली calls with
 * the TF flag set.  This exercises some nasty kernel code in the
 * SYSENTER हाल: SYSENTER करोes not clear TF, so SYSENTER with TF set
 * immediately issues #DB from CPL 0.  This requires special handling in
 * the kernel.
 */

#घोषणा _GNU_SOURCE

#समावेश <sys/समय.स>
#समावेश <समय.स>
#समावेश <मानककोष.स>
#समावेश <sys/syscall.h>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <sys/mman.h>
#समावेश <sys/संकेत.स>
#समावेश <sys/ucontext.h>
#समावेश <यंत्र/ldt.h>
#समावेश <err.h>
#समावेश <समलाँघ.स>
#समावेश <मानकघोष.स>
#समावेश <stdbool.h>
#समावेश <sys/ptrace.h>
#समावेश <sys/user.h>

#समावेश "helpers.h"

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

अटल व्योम clearhandler(पूर्णांक sig)
अणु
	काष्ठा sigaction sa;
	स_रखो(&sa, 0, माप(sa));
	sa.sa_handler = संक_पूर्व;
	sigemptyset(&sa.sa_mask);
	अगर (sigaction(sig, &sa, 0))
		err(1, "sigaction");
पूर्ण

अटल अस्थिर संक_पूर्ण_प्रकार sig_traps, sig_eflags;
sigलाँघ_बफ jmpbuf;
अटल अचिन्हित अक्षर altstack_data[SIGSTKSZ];

#अगर_घोषित __x86_64__
# define REG_IP REG_RIP
# define WIDTH "q"
# define INT80_CLOBBERS "r8", "r9", "r10", "r11"
#अन्यथा
# define REG_IP REG_EIP
# define WIDTH "l"
# define INT80_CLOBBERS
#पूर्ण_अगर

अटल व्योम sigtrap(पूर्णांक sig, siginfo_t *info, व्योम *ctx_व्योम)
अणु
	ucontext_t *ctx = (ucontext_t*)ctx_व्योम;

	अगर (get_eflags() & X86_EFLAGS_TF) अणु
		set_eflags(get_eflags() & ~X86_EFLAGS_TF);
		म_लिखो("[WARN]\tSIGTRAP handler had TF set\n");
		_निकास(1);
	पूर्ण

	sig_traps++;

	अगर (sig_traps == 10000 || sig_traps == 10001) अणु
		म_लिखो("[WARN]\tHit %d SIGTRAPs with si_addr 0x%lx, ip 0x%lx\n",
		       (पूर्णांक)sig_traps,
		       (अचिन्हित दीर्घ)info->si_addr,
		       (अचिन्हित दीर्घ)ctx->uc_mcontext.gregs[REG_IP]);
	पूर्ण
पूर्ण

अटल अक्षर स्थिर * स्थिर signames[] = अणु
	[संक_अंश] = "SIGSEGV",
	[SIGBUS] = "SIBGUS",
	[SIGTRAP] = "SIGTRAP",
	[संक_अवैध] = "SIGILL",
पूर्ण;

अटल व्योम prपूर्णांक_and_दीर्घ_लाँघ(पूर्णांक sig, siginfo_t *si, व्योम *ctx_व्योम)
अणु
	ucontext_t *ctx = ctx_व्योम;

	म_लिखो("\tGot %s with RIP=%lx, TF=%ld\n", signames[sig],
	       (अचिन्हित दीर्घ)ctx->uc_mcontext.gregs[REG_IP],
	       (अचिन्हित दीर्घ)ctx->uc_mcontext.gregs[REG_EFL] & X86_EFLAGS_TF);

	sig_eflags = (अचिन्हित दीर्घ)ctx->uc_mcontext.gregs[REG_EFL];
	sigदीर्घ_लाँघ(jmpbuf, 1);
पूर्ण

अटल व्योम check_result(व्योम)
अणु
	अचिन्हित दीर्घ new_eflags = get_eflags();
	set_eflags(new_eflags & ~X86_EFLAGS_TF);

	अगर (!sig_traps) अणु
		म_लिखो("[FAIL]\tNo SIGTRAP\n");
		निकास(1);
	पूर्ण

	अगर (!(new_eflags & X86_EFLAGS_TF)) अणु
		म_लिखो("[FAIL]\tTF was cleared\n");
		निकास(1);
	पूर्ण

	म_लिखो("[OK]\tSurvived with TF set and %d traps\n", (पूर्णांक)sig_traps);
	sig_traps = 0;
पूर्ण

अटल व्योम fast_syscall_no_tf(व्योम)
अणु
	sig_traps = 0;
	म_लिखो("[RUN]\tFast syscall with TF cleared\n");
	ख_साफ(मानक_निकास);  /* Force a syscall */
	अगर (get_eflags() & X86_EFLAGS_TF) अणु
		म_लिखो("[FAIL]\tTF is now set\n");
		निकास(1);
	पूर्ण
	अगर (sig_traps) अणु
		म_लिखो("[FAIL]\tGot SIGTRAP\n");
		निकास(1);
	पूर्ण
	म_लिखो("[OK]\tNothing unexpected happened\n");
पूर्ण

पूर्णांक मुख्य()
अणु
#अगर_घोषित CAN_BUILD_32
	पूर्णांक पंचांगp;
#पूर्ण_अगर

	sethandler(SIGTRAP, sigtrap, 0);

	म_लिखो("[RUN]\tSet TF and check nop\n");
	set_eflags(get_eflags() | X86_EFLAGS_TF);
	यंत्र अस्थिर ("nop");
	check_result();

#अगर_घोषित __x86_64__
	म_लिखो("[RUN]\tSet TF and check syscall-less opportunistic sysret\n");
	set_eflags(get_eflags() | X86_EFLAGS_TF);
	बाह्य अचिन्हित अक्षर post_nop[];
	यंत्र अस्थिर ("pushf" WIDTH "\n\t"
		      "pop" WIDTH " %%r11\n\t"
		      "nop\n\t"
		      "post_nop:"
		      : : "c" (post_nop) : "r11");
	check_result();
#पूर्ण_अगर
#अगर_घोषित CAN_BUILD_32
	म_लिखो("[RUN]\tSet TF and check int80\n");
	set_eflags(get_eflags() | X86_EFLAGS_TF);
	यंत्र अस्थिर ("int $0x80" : "=a" (पंचांगp) : "a" (SYS_getpid)
			: INT80_CLOBBERS);
	check_result();
#पूर्ण_अगर

	/*
	 * This test is particularly पूर्णांकeresting अगर fast syscalls use
	 * SYSENTER: it triggers a nasty design flaw in SYSENTER.
	 * Specअगरically, SYSENTER करोes not clear TF, so either SYSENTER
	 * or the next inकाष्ठाion traps at CPL0.  (Of course, Intel
	 * mostly क्रमgot to करोcument exactly what happens here.)  So we
	 * get a CPL0 fault with usergs (on 64-bit kernels) and possibly
	 * no stack.  The only sane way the kernel can possibly handle
	 * it is to clear TF on वापस from the #DB handler, but this
	 * happens way too early to set TF in the saved pt_regs, so the
	 * kernel has to करो something clever to aव्योम losing track of
	 * the TF bit.
	 *
	 * Needless to say, we've had bugs in this area.
	 */
	syscall(SYS_getpid);  /* Force symbol binding without TF set. */
	म_लिखो("[RUN]\tSet TF and check a fast syscall\n");
	set_eflags(get_eflags() | X86_EFLAGS_TF);
	syscall(SYS_getpid);
	check_result();

	/* Now make sure that another fast syscall करोesn't set TF again. */
	fast_syscall_no_tf();

	/*
	 * And करो a क्रमced SYSENTER to make sure that this works even अगर
	 * fast syscalls करोn't use SYSENTER.
	 *
	 * Invoking SYSENTER directly अवरोधs all the rules.  Just handle
	 * the संक_अंश.
	 */
	अगर (sigबनाओ_लाँघ(jmpbuf, 1) == 0) अणु
		अचिन्हित दीर्घ nr = SYS_getpid;
		म_लिखो("[RUN]\tSet TF and check SYSENTER\n");
		stack_t stack = अणु
			.ss_sp = altstack_data,
			.ss_size = SIGSTKSZ,
		पूर्ण;
		अगर (sigaltstack(&stack, शून्य) != 0)
			err(1, "sigaltstack");
		sethandler(संक_अंश, prपूर्णांक_and_दीर्घ_लाँघ,
			   SA_RESETHAND | SA_ONSTACK);
		sethandler(संक_अवैध, prपूर्णांक_and_दीर्घ_लाँघ, SA_RESETHAND);
		set_eflags(get_eflags() | X86_EFLAGS_TF);
		/* Clear EBP first to make sure we segfault cleanly. */
		यंत्र अस्थिर ("xorl %%ebp, %%ebp; SYSENTER" : "+a" (nr) :: "flags", "rcx"
#अगर_घोषित __x86_64__
				, "r11"
#पूर्ण_अगर
			);

		/* We're unreachable here.  SYSENTER क्रममाला_लो RIP. */
	पूर्ण
	clearhandler(संक_अंश);
	clearhandler(संक_अवैध);
	अगर (!(sig_eflags & X86_EFLAGS_TF)) अणु
		म_लिखो("[FAIL]\tTF was cleared\n");
		निकास(1);
	पूर्ण

	/* Now make sure that another fast syscall करोesn't set TF again. */
	fast_syscall_no_tf();

	वापस 0;
पूर्ण
