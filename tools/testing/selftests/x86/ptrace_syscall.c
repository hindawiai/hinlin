<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE

#समावेश <sys/ptrace.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <sys/syscall.h>
#समावेश <sys/user.h>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <मानकघोष.स>
#समावेश <मानकपन.स>
#समावेश <err.h>
#समावेश <माला.स>
#समावेश <यंत्र/ptrace-abi.h>
#समावेश <sys/auxv.h>

/* Bitness-agnostic defines क्रम user_regs_काष्ठा fields. */
#अगर_घोषित __x86_64__
# define user_syscall_nr	orig_rax
# define user_arg0		rdi
# define user_arg1		rsi
# define user_arg2		rdx
# define user_arg3		r10
# define user_arg4		r8
# define user_arg5		r9
# define user_ip		rip
# define user_ax		rax
#अन्यथा
# define user_syscall_nr	orig_eax
# define user_arg0		ebx
# define user_arg1		ecx
# define user_arg2		edx
# define user_arg3		esi
# define user_arg4		edi
# define user_arg5		ebp
# define user_ip		eip
# define user_ax		eax
#पूर्ण_अगर

अटल पूर्णांक nerrs = 0;

काष्ठा syscall_args32 अणु
	uपूर्णांक32_t nr, arg0, arg1, arg2, arg3, arg4, arg5;
पूर्ण;

#अगर_घोषित __i386__
बाह्य व्योम sys32_helper(काष्ठा syscall_args32 *, व्योम *);
बाह्य व्योम पूर्णांक80_and_ret(व्योम);
#पूर्ण_अगर

/*
 * Helper to invoke पूर्णांक80 with controlled regs and capture the final regs.
 */
अटल व्योम करो_full_पूर्णांक80(काष्ठा syscall_args32 *args)
अणु
#अगर_घोषित __x86_64__
	रेजिस्टर अचिन्हित दीर्घ bp यंत्र("bp") = args->arg5;
	यंत्र अस्थिर ("int $0x80"
		      : "+a" (args->nr),
			"+b" (args->arg0), "+c" (args->arg1), "+d" (args->arg2),
			"+S" (args->arg3), "+D" (args->arg4), "+r" (bp)
			: : "r8", "r9", "r10", "r11");
	args->arg5 = bp;
#अन्यथा
	sys32_helper(args, पूर्णांक80_and_ret);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित __i386__
अटल व्योम (*vsyscall32)(व्योम);

/*
 * Nasty helper to invoke AT_SYSINFO (i.e. __kernel_vsyscall) with
 * controlled regs and capture the final regs.  This is so nasty that it
 * crashes my copy of gdb :)
 */
अटल व्योम करो_full_vsyscall32(काष्ठा syscall_args32 *args)
अणु
	sys32_helper(args, vsyscall32);
पूर्ण
#पूर्ण_अगर

अटल siginfo_t रुको_trap(pid_t chld)
अणु
	siginfo_t si;
	अगर (रुकोid(P_PID, chld, &si, WEXITED|WSTOPPED) != 0)
		err(1, "waitid");
	अगर (si.si_pid != chld)
		errx(1, "got unexpected pid in event\n");
	अगर (si.si_code != CLD_TRAPPED)
		errx(1, "got unexpected event type %d\n", si.si_code);
	वापस si;
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

अटल व्योम setsigign(पूर्णांक sig, पूर्णांक flags)
अणु
	काष्ठा sigaction sa;
	स_रखो(&sa, 0, माप(sa));
	sa.sa_sigaction = (व्योम *)संक_छोड़ो;
	sa.sa_flags = flags;
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

#अगर_घोषित __x86_64__
# define REG_BP REG_RBP
#अन्यथा
# define REG_BP REG_EBP
#पूर्ण_अगर

अटल व्योम empty_handler(पूर्णांक sig, siginfo_t *si, व्योम *ctx_व्योम)
अणु
पूर्ण

अटल व्योम test_sys32_regs(व्योम (*करो_syscall)(काष्ठा syscall_args32 *))
अणु
	काष्ठा syscall_args32 args = अणु
		.nr = 224,	/* gettid */
		.arg0 = 10, .arg1 = 11, .arg2 = 12,
		.arg3 = 13, .arg4 = 14, .arg5 = 15,
	पूर्ण;

	करो_syscall(&args);

	अगर (args.nr != getpid() ||
	    args.arg0 != 10 || args.arg1 != 11 || args.arg2 != 12 ||
	    args.arg3 != 13 || args.arg4 != 14 || args.arg5 != 15) अणु
		म_लिखो("[FAIL]\tgetpid() failed to preserve regs\n");
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tgetpid() preserves regs\n");
	पूर्ण

	sethandler(SIGUSR1, empty_handler, 0);

	args.nr = 37;	/* समाप्त */
	args.arg0 = getpid();
	args.arg1 = SIGUSR1;
	करो_syscall(&args);
	अगर (args.nr != 0 ||
	    args.arg0 != getpid() || args.arg1 != SIGUSR1 || args.arg2 != 12 ||
	    args.arg3 != 13 || args.arg4 != 14 || args.arg5 != 15) अणु
		म_लिखो("[FAIL]\tkill(getpid(), SIGUSR1) failed to preserve regs\n");
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tkill(getpid(), SIGUSR1) preserves regs\n");
	पूर्ण
	clearhandler(SIGUSR1);
पूर्ण

अटल व्योम test_ptrace_syscall_restart(व्योम)
अणु
	म_लिखो("[RUN]\tptrace-induced syscall restart\n");
	pid_t chld = विभाजन();
	अगर (chld < 0)
		err(1, "fork");

	अगर (chld == 0) अणु
		अगर (ptrace(PTRACE_TRACEME, 0, 0, 0) != 0)
			err(1, "PTRACE_TRACEME");

		pid_t pid = getpid(), tid = syscall(SYS_gettid);

		म_लिखो("\tChild will make one syscall\n");
		syscall(SYS_tgसमाप्त, pid, tid, SIGSTOP);

		syscall(SYS_gettid, 10, 11, 12, 13, 14, 15);
		_निकास(0);
	पूर्ण

	पूर्णांक status;

	/* Wait क्रम SIGSTOP. */
	अगर (रुकोpid(chld, &status, 0) != chld || !WIFSTOPPED(status))
		err(1, "waitpid");

	काष्ठा user_regs_काष्ठा regs;

	म_लिखो("[RUN]\tSYSEMU\n");
	अगर (ptrace(PTRACE_SYSEMU, chld, 0, 0) != 0)
		err(1, "PTRACE_SYSEMU");
	रुको_trap(chld);

	अगर (ptrace(PTRACE_GETREGS, chld, 0, &regs) != 0)
		err(1, "PTRACE_GETREGS");

	अगर (regs.user_syscall_nr != SYS_gettid ||
	    regs.user_arg0 != 10 || regs.user_arg1 != 11 ||
	    regs.user_arg2 != 12 || regs.user_arg3 != 13 ||
	    regs.user_arg4 != 14 || regs.user_arg5 != 15) अणु
		म_लिखो("[FAIL]\tInitial args are wrong (nr=%lu, args=%lu %lu %lu %lu %lu %lu)\n", (अचिन्हित दीर्घ)regs.user_syscall_nr, (अचिन्हित दीर्घ)regs.user_arg0, (अचिन्हित दीर्घ)regs.user_arg1, (अचिन्हित दीर्घ)regs.user_arg2, (अचिन्हित दीर्घ)regs.user_arg3, (अचिन्हित दीर्घ)regs.user_arg4, (अचिन्हित दीर्घ)regs.user_arg5);
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tInitial nr and args are correct\n");
	पूर्ण

	म_लिखो("[RUN]\tRestart the syscall (ip = 0x%lx)\n",
	       (अचिन्हित दीर्घ)regs.user_ip);

	/*
	 * This करोes exactly what it appears to करो अगर syscall is पूर्णांक80 or
	 * SYSCALL64.  For SYSCALL32 or SYSENTER, though, this is highly
	 * magical.  It needs to work so that ptrace and syscall restart
	 * work as expected.
	 */
	regs.user_ax = regs.user_syscall_nr;
	regs.user_ip -= 2;
	अगर (ptrace(PTRACE_SETREGS, chld, 0, &regs) != 0)
		err(1, "PTRACE_SETREGS");

	अगर (ptrace(PTRACE_SYSEMU, chld, 0, 0) != 0)
		err(1, "PTRACE_SYSEMU");
	रुको_trap(chld);

	अगर (ptrace(PTRACE_GETREGS, chld, 0, &regs) != 0)
		err(1, "PTRACE_GETREGS");

	अगर (regs.user_syscall_nr != SYS_gettid ||
	    regs.user_arg0 != 10 || regs.user_arg1 != 11 ||
	    regs.user_arg2 != 12 || regs.user_arg3 != 13 ||
	    regs.user_arg4 != 14 || regs.user_arg5 != 15) अणु
		म_लिखो("[FAIL]\tRestart nr or args are wrong (nr=%lu, args=%lu %lu %lu %lu %lu %lu)\n", (अचिन्हित दीर्घ)regs.user_syscall_nr, (अचिन्हित दीर्घ)regs.user_arg0, (अचिन्हित दीर्घ)regs.user_arg1, (अचिन्हित दीर्घ)regs.user_arg2, (अचिन्हित दीर्घ)regs.user_arg3, (अचिन्हित दीर्घ)regs.user_arg4, (अचिन्हित दीर्घ)regs.user_arg5);
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tRestarted nr and args are correct\n");
	पूर्ण

	म_लिखो("[RUN]\tChange nr and args and restart the syscall (ip = 0x%lx)\n",
	       (अचिन्हित दीर्घ)regs.user_ip);

	regs.user_ax = SYS_getpid;
	regs.user_arg0 = 20;
	regs.user_arg1 = 21;
	regs.user_arg2 = 22;
	regs.user_arg3 = 23;
	regs.user_arg4 = 24;
	regs.user_arg5 = 25;
	regs.user_ip -= 2;

	अगर (ptrace(PTRACE_SETREGS, chld, 0, &regs) != 0)
		err(1, "PTRACE_SETREGS");

	अगर (ptrace(PTRACE_SYSEMU, chld, 0, 0) != 0)
		err(1, "PTRACE_SYSEMU");
	रुको_trap(chld);

	अगर (ptrace(PTRACE_GETREGS, chld, 0, &regs) != 0)
		err(1, "PTRACE_GETREGS");

	अगर (regs.user_syscall_nr != SYS_getpid ||
	    regs.user_arg0 != 20 || regs.user_arg1 != 21 || regs.user_arg2 != 22 ||
	    regs.user_arg3 != 23 || regs.user_arg4 != 24 || regs.user_arg5 != 25) अणु
		म_लिखो("[FAIL]\tRestart nr or args are wrong (nr=%lu, args=%lu %lu %lu %lu %lu %lu)\n", (अचिन्हित दीर्घ)regs.user_syscall_nr, (अचिन्हित दीर्घ)regs.user_arg0, (अचिन्हित दीर्घ)regs.user_arg1, (अचिन्हित दीर्घ)regs.user_arg2, (अचिन्हित दीर्घ)regs.user_arg3, (अचिन्हित दीर्घ)regs.user_arg4, (अचिन्हित दीर्घ)regs.user_arg5);
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tReplacement nr and args are correct\n");
	पूर्ण

	अगर (ptrace(PTRACE_CONT, chld, 0, 0) != 0)
		err(1, "PTRACE_CONT");
	अगर (रुकोpid(chld, &status, 0) != chld)
		err(1, "waitpid");
	अगर (!WIFEXITED(status) || WEXITSTATUS(status) != 0) अणु
		म_लिखो("[FAIL]\tChild failed\n");
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tChild exited cleanly\n");
	पूर्ण
पूर्ण

अटल व्योम test_restart_under_ptrace(व्योम)
अणु
	म_लिखो("[RUN]\tkernel syscall restart under ptrace\n");
	pid_t chld = विभाजन();
	अगर (chld < 0)
		err(1, "fork");

	अगर (chld == 0) अणु
		अगर (ptrace(PTRACE_TRACEME, 0, 0, 0) != 0)
			err(1, "PTRACE_TRACEME");

		pid_t pid = getpid(), tid = syscall(SYS_gettid);

		म_लिखो("\tChild will take a nap until signaled\n");
		setsigign(SIGUSR1, SA_RESTART);
		syscall(SYS_tgसमाप्त, pid, tid, SIGSTOP);

		syscall(SYS_छोड़ो, 0, 0, 0, 0, 0, 0);
		_निकास(0);
	पूर्ण

	पूर्णांक status;

	/* Wait क्रम SIGSTOP. */
	अगर (रुकोpid(chld, &status, 0) != chld || !WIFSTOPPED(status))
		err(1, "waitpid");

	काष्ठा user_regs_काष्ठा regs;

	म_लिखो("[RUN]\tSYSCALL\n");
	अगर (ptrace(PTRACE_SYSCALL, chld, 0, 0) != 0)
		err(1, "PTRACE_SYSCALL");
	रुको_trap(chld);

	/* We should be stopped at छोड़ो(2) entry. */

	अगर (ptrace(PTRACE_GETREGS, chld, 0, &regs) != 0)
		err(1, "PTRACE_GETREGS");

	अगर (regs.user_syscall_nr != SYS_छोड़ो ||
	    regs.user_arg0 != 0 || regs.user_arg1 != 0 ||
	    regs.user_arg2 != 0 || regs.user_arg3 != 0 ||
	    regs.user_arg4 != 0 || regs.user_arg5 != 0) अणु
		म_लिखो("[FAIL]\tInitial args are wrong (nr=%lu, args=%lu %lu %lu %lu %lu %lu)\n", (अचिन्हित दीर्घ)regs.user_syscall_nr, (अचिन्हित दीर्घ)regs.user_arg0, (अचिन्हित दीर्घ)regs.user_arg1, (अचिन्हित दीर्घ)regs.user_arg2, (अचिन्हित दीर्घ)regs.user_arg3, (अचिन्हित दीर्घ)regs.user_arg4, (अचिन्हित दीर्घ)regs.user_arg5);
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tInitial nr and args are correct\n");
	पूर्ण

	/* Interrupt it. */
	समाप्त(chld, SIGUSR1);

	/* Advance.  We should be stopped at निकास. */
	म_लिखो("[RUN]\tSYSCALL\n");
	अगर (ptrace(PTRACE_SYSCALL, chld, 0, 0) != 0)
		err(1, "PTRACE_SYSCALL");
	रुको_trap(chld);

	अगर (ptrace(PTRACE_GETREGS, chld, 0, &regs) != 0)
		err(1, "PTRACE_GETREGS");

	अगर (regs.user_syscall_nr != SYS_छोड़ो ||
	    regs.user_arg0 != 0 || regs.user_arg1 != 0 ||
	    regs.user_arg2 != 0 || regs.user_arg3 != 0 ||
	    regs.user_arg4 != 0 || regs.user_arg5 != 0) अणु
		म_लिखो("[FAIL]\tArgs after SIGUSR1 are wrong (nr=%lu, args=%lu %lu %lu %lu %lu %lu)\n", (अचिन्हित दीर्घ)regs.user_syscall_nr, (अचिन्हित दीर्घ)regs.user_arg0, (अचिन्हित दीर्घ)regs.user_arg1, (अचिन्हित दीर्घ)regs.user_arg2, (अचिन्हित दीर्घ)regs.user_arg3, (अचिन्हित दीर्घ)regs.user_arg4, (अचिन्हित दीर्घ)regs.user_arg5);
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tArgs after SIGUSR1 are correct (ax = %ld)\n",
		       (दीर्घ)regs.user_ax);
	पूर्ण

	/* Poke the regs back in.  This must not अवरोध anything. */
	अगर (ptrace(PTRACE_SETREGS, chld, 0, &regs) != 0)
		err(1, "PTRACE_SETREGS");

	/* Catch the (ignored) SIGUSR1. */
	अगर (ptrace(PTRACE_CONT, chld, 0, 0) != 0)
		err(1, "PTRACE_CONT");
	अगर (रुकोpid(chld, &status, 0) != chld)
		err(1, "waitpid");
	अगर (!WIFSTOPPED(status)) अणु
		म_लिखो("[FAIL]\tChild was stopped for SIGUSR1 (status = 0x%x)\n", status);
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tChild got SIGUSR1\n");
	पूर्ण

	/* The next event should be छोड़ो(2) again. */
	म_लिखो("[RUN]\tStep again\n");
	अगर (ptrace(PTRACE_SYSCALL, chld, 0, 0) != 0)
		err(1, "PTRACE_SYSCALL");
	रुको_trap(chld);

	/* We should be stopped at छोड़ो(2) entry. */

	अगर (ptrace(PTRACE_GETREGS, chld, 0, &regs) != 0)
		err(1, "PTRACE_GETREGS");

	अगर (regs.user_syscall_nr != SYS_छोड़ो ||
	    regs.user_arg0 != 0 || regs.user_arg1 != 0 ||
	    regs.user_arg2 != 0 || regs.user_arg3 != 0 ||
	    regs.user_arg4 != 0 || regs.user_arg5 != 0) अणु
		म_लिखो("[FAIL]\tpause did not restart (nr=%lu, args=%lu %lu %lu %lu %lu %lu)\n", (अचिन्हित दीर्घ)regs.user_syscall_nr, (अचिन्हित दीर्घ)regs.user_arg0, (अचिन्हित दीर्घ)regs.user_arg1, (अचिन्हित दीर्घ)regs.user_arg2, (अचिन्हित दीर्घ)regs.user_arg3, (अचिन्हित दीर्घ)regs.user_arg4, (अचिन्हित दीर्घ)regs.user_arg5);
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tpause(2) restarted correctly\n");
	पूर्ण

	/* Kill it. */
	समाप्त(chld, SIGKILL);
	अगर (रुकोpid(chld, &status, 0) != chld)
		err(1, "waitpid");
पूर्ण

पूर्णांक मुख्य()
अणु
	म_लिखो("[RUN]\tCheck int80 return regs\n");
	test_sys32_regs(करो_full_पूर्णांक80);

#अगर defined(__i386__) && (!defined(__GLIBC__) || __GLIBC__ > 2 || __GLIBC_MINOR__ >= 16)
	vsyscall32 = (व्योम *)getauxval(AT_SYSINFO);
	अगर (vsyscall32) अणु
		म_लिखो("[RUN]\tCheck AT_SYSINFO return regs\n");
		test_sys32_regs(करो_full_vsyscall32);
	पूर्ण अन्यथा अणु
		म_लिखो("[SKIP]\tAT_SYSINFO is not available\n");
	पूर्ण
#पूर्ण_अगर

	test_ptrace_syscall_restart();

	test_restart_under_ptrace();

	वापस 0;
पूर्ण
