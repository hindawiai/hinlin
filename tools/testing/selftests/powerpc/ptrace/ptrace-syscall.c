<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * A ptrace test क्रम testing PTRACE_SYSEMU, PTRACE_SETREGS and
 * PTRACE_GETREG.  This test basically create a child process that executes
 * syscalls and the parent process check अगर it is being traced appropriated.
 *
 * This test is heavily based on tools/testing/selftests/x86/ptrace_syscall.c
 * test, and it was adapted to run on Powerpc by
 * Breno Leitao <leitao@debian.org>
 */
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
#समावेश <sys/auxv.h>
#समावेश "utils.h"

/* Bitness-agnostic defines क्रम user_regs_काष्ठा fields. */
#घोषणा user_syscall_nr	gpr[0]
#घोषणा user_arg0		gpr[3]
#घोषणा user_arg1		gpr[4]
#घोषणा user_arg2		gpr[5]
#घोषणा user_arg3		gpr[6]
#घोषणा user_arg4		gpr[7]
#घोषणा user_arg5		gpr[8]
#घोषणा user_ip		nip

#घोषणा PTRACE_SYSEMU		0x1d

अटल पूर्णांक nerrs;

अटल व्योम रुको_trap(pid_t chld)
अणु
	siginfo_t si;

	अगर (रुकोid(P_PID, chld, &si, WEXITED|WSTOPPED) != 0)
		err(1, "waitid");
	अगर (si.si_pid != chld)
		errx(1, "got unexpected pid in event\n");
	अगर (si.si_code != CLD_TRAPPED)
		errx(1, "got unexpected event type %d\n", si.si_code);
पूर्ण

अटल व्योम test_ptrace_syscall_restart(व्योम)
अणु
	पूर्णांक status;
	काष्ठा pt_regs regs;
	pid_t chld;

	म_लिखो("[RUN]\tptrace-induced syscall restart\n");

	chld = विभाजन();
	अगर (chld < 0)
		err(1, "fork");

	/*
	 * Child process is running 4 syscalls after ptrace.
	 *
	 * 1) getpid()
	 * 2) gettid()
	 * 3) tgसमाप्त() -> Send SIGSTOP
	 * 4) gettid() -> Where the tests will happen essentially
	 */
	अगर (chld == 0) अणु
		अगर (ptrace(PTRACE_TRACEME, 0, 0, 0) != 0)
			err(1, "PTRACE_TRACEME");

		pid_t pid = getpid(), tid = syscall(SYS_gettid);

		म_लिखो("\tChild will make one syscall\n");
		syscall(SYS_tgसमाप्त, pid, tid, SIGSTOP);

		syscall(SYS_gettid, 10, 11, 12, 13, 14, 15);
		_निकास(0);
	पूर्ण
	/* Parent process below */

	/* Wait क्रम SIGSTOP sent by tgसमाप्त above. */
	अगर (रुकोpid(chld, &status, 0) != chld || !WIFSTOPPED(status))
		err(1, "waitpid");

	म_लिखो("[RUN]\tSYSEMU\n");
	अगर (ptrace(PTRACE_SYSEMU, chld, 0, 0) != 0)
		err(1, "PTRACE_SYSEMU");
	रुको_trap(chld);

	अगर (ptrace(PTRACE_GETREGS, chld, 0, &regs) != 0)
		err(1, "PTRACE_GETREGS");

	/*
	 * Ptrace trapped prior to executing the syscall, thus r3 still has
	 * the syscall number instead of the sys_gettid() result
	 */
	अगर (regs.user_syscall_nr != SYS_gettid ||
	    regs.user_arg0 != 10 || regs.user_arg1 != 11 ||
	    regs.user_arg2 != 12 || regs.user_arg3 != 13 ||
	    regs.user_arg4 != 14 || regs.user_arg5 != 15) अणु
		म_लिखो("[FAIL]\tInitial args are wrong (nr=%lu, args=%lu %lu %lu %lu %lu %lu)\n",
			(अचिन्हित दीर्घ)regs.user_syscall_nr,
			(अचिन्हित दीर्घ)regs.user_arg0,
			(अचिन्हित दीर्घ)regs.user_arg1,
			(अचिन्हित दीर्घ)regs.user_arg2,
			(अचिन्हित दीर्घ)regs.user_arg3,
			(अचिन्हित दीर्घ)regs.user_arg4,
			(अचिन्हित दीर्घ)regs.user_arg5);
		 nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tInitial nr and args are correct\n"); पूर्ण

	म_लिखो("[RUN]\tRestart the syscall (ip = 0x%lx)\n",
	       (अचिन्हित दीर्घ)regs.user_ip);

	/*
	 * Rewind to retry the same syscall again. This will basically test
	 * the शुरुआत process together with PTRACE_SETREGS and PTRACE_GETREGS.
	 */
	regs.user_ip -= 4;
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
		म_लिखो("[FAIL]\tRestart nr or args are wrong (nr=%lu, args=%lu %lu %lu %lu %lu %lu)\n",
			(अचिन्हित दीर्घ)regs.user_syscall_nr,
			(अचिन्हित दीर्घ)regs.user_arg0,
			(अचिन्हित दीर्घ)regs.user_arg1,
			(अचिन्हित दीर्घ)regs.user_arg2,
			(अचिन्हित दीर्घ)regs.user_arg3,
			(अचिन्हित दीर्घ)regs.user_arg4,
			(अचिन्हित दीर्घ)regs.user_arg5);
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tRestarted nr and args are correct\n");
	पूर्ण

	म_लिखो("[RUN]\tChange nr and args and restart the syscall (ip = 0x%lx)\n",
	       (अचिन्हित दीर्घ)regs.user_ip);

	/*
	 * Inject a new syscall (getpid) in the same place the previous
	 * syscall (gettid), शुरुआत and re-execute.
	 */
	regs.user_syscall_nr = SYS_getpid;
	regs.user_arg0 = 20;
	regs.user_arg1 = 21;
	regs.user_arg2 = 22;
	regs.user_arg3 = 23;
	regs.user_arg4 = 24;
	regs.user_arg5 = 25;
	regs.user_ip -= 4;

	अगर (ptrace(PTRACE_SETREGS, chld, 0, &regs) != 0)
		err(1, "PTRACE_SETREGS");

	अगर (ptrace(PTRACE_SYSEMU, chld, 0, 0) != 0)
		err(1, "PTRACE_SYSEMU");
	रुको_trap(chld);

	अगर (ptrace(PTRACE_GETREGS, chld, 0, &regs) != 0)
		err(1, "PTRACE_GETREGS");

	/* Check that ptrace stopped at the new syscall that was
	 * injected, and guarantee that it haven't executed, i.e, user_args
	 * contain the arguments and not the syscall वापस value, क्रम
	 * instance.
	 */
	अगर (regs.user_syscall_nr != SYS_getpid
		|| regs.user_arg0 != 20 || regs.user_arg1 != 21
		|| regs.user_arg2 != 22 || regs.user_arg3 != 23
		|| regs.user_arg4 != 24 || regs.user_arg5 != 25) अणु

		म_लिखो("[FAIL]\tRestart nr or args are wrong (nr=%lu, args=%lu %lu %lu %lu %lu %lu)\n",
			(अचिन्हित दीर्घ)regs.user_syscall_nr,
			(अचिन्हित दीर्घ)regs.user_arg0,
			(अचिन्हित दीर्घ)regs.user_arg1,
			(अचिन्हित दीर्घ)regs.user_arg2,
			(अचिन्हित दीर्घ)regs.user_arg3,
			(अचिन्हित दीर्घ)regs.user_arg4,
			(अचिन्हित दीर्घ)regs.user_arg5);
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tReplacement nr and args are correct\n");
	पूर्ण

	अगर (ptrace(PTRACE_CONT, chld, 0, 0) != 0)
		err(1, "PTRACE_CONT");

	अगर (रुकोpid(chld, &status, 0) != chld)
		err(1, "waitpid");

	/* Guarantee that the process executed properly, वापसing 0 */
	अगर (!WIFEXITED(status) || WEXITSTATUS(status) != 0) अणु
		म_लिखो("[FAIL]\tChild failed\n");
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tChild exited cleanly\n");
	पूर्ण
पूर्ण

पूर्णांक ptrace_syscall(व्योम)
अणु
	test_ptrace_syscall_restart();

	वापस nerrs;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(ptrace_syscall, "ptrace_syscall");
पूर्ण
