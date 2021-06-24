<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2020 Collabora Ltd.
 *
 * Benchmark and test syscall user dispatch
 */

#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <त्रुटिसं.स>
#समावेश <समय.स>
#समावेश <sys/समय.स>
#समावेश <unistd.h>
#समावेश <sys/sysinfo.h>
#समावेश <sys/prctl.h>
#समावेश <sys/syscall.h>

#अगर_अघोषित PR_SET_SYSCALL_USER_DISPATCH
# define PR_SET_SYSCALL_USER_DISPATCH	59
# define PR_SYS_DISPATCH_OFF	0
# define PR_SYS_DISPATCH_ON	1
# define SYSCALL_DISPATCH_FILTER_ALLOW	0
# define SYSCALL_DISPATCH_FILTER_BLOCK	1
#पूर्ण_अगर

#अगर_घोषित __NR_syscalls
# define MAGIC_SYSCALL_1 (__NR_syscalls + 1) /* Bad Linux syscall number */
#अन्यथा
# define MAGIC_SYSCALL_1 (0xff00)  /* Bad Linux syscall number */
#पूर्ण_अगर

/*
 * To test वापसing from a sigsys with selector blocked, the test
 * requires some per-architecture support (i.e. knowledge about the
 * संकेत trampoline address).  On i386, we know it is on the vdso, and
 * a small trampoline is खोलो-coded क्रम x86_64.  Other architectures
 * that have a trampoline in the vdso will support TEST_BLOCKED_RETURN
 * out of the box, but करोn't enable them until they support syscall user
 * dispatch.
 */
#अगर defined(__x86_64__) || defined(__i386__)
#घोषणा TEST_BLOCKED_RETURN
#पूर्ण_अगर

#अगर_घोषित __x86_64__
व्योम* (syscall_dispatcher_start)(व्योम);
व्योम* (syscall_dispatcher_end)(व्योम);
#अन्यथा
अचिन्हित दीर्घ syscall_dispatcher_start = 0;
अचिन्हित दीर्घ syscall_dispatcher_end = 0;
#पूर्ण_अगर

अचिन्हित दीर्घ trapped_call_count = 0;
अचिन्हित दीर्घ native_call_count = 0;

अक्षर selector;
#घोषणा SYSCALL_BLOCK   (selector = SYSCALL_DISPATCH_FILTER_BLOCK)
#घोषणा SYSCALL_UNBLOCK (selector = SYSCALL_DISPATCH_FILTER_ALLOW)

#घोषणा CALIBRATION_STEP 100000
#घोषणा CALIBRATE_TO_SECS 5
पूर्णांक factor;

अटल द्विगुन one_sysinfo_step(व्योम)
अणु
	काष्ठा बारpec t1, t2;
	पूर्णांक i;
	काष्ठा sysinfo info;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &t1);
	क्रम (i = 0; i < CALIBRATION_STEP; i++)
		sysinfo(&info);
	घड़ी_समय_लो(CLOCK_MONOTONIC, &t2);
	वापस (t2.tv_sec - t1.tv_sec) + 1.0e-9 * (t2.tv_nsec - t1.tv_nsec);
पूर्ण

अटल व्योम calibrate_set(व्योम)
अणु
	द्विगुन elapsed = 0;

	म_लिखो("Calibrating test set to last ~%d seconds...\n", CALIBRATE_TO_SECS);

	जबतक (elapsed < 1) अणु
		elapsed += one_sysinfo_step();
		factor += CALIBRATE_TO_SECS;
	पूर्ण

	म_लिखो("test iterations = %d\n", CALIBRATION_STEP * factor);
पूर्ण

अटल द्विगुन perf_syscall(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	द्विगुन partial = 0;

	क्रम (i = 0; i < factor; ++i)
		partial += one_sysinfo_step()/(CALIBRATION_STEP*factor);
	वापस partial;
पूर्ण

अटल व्योम handle_sigsys(पूर्णांक sig, siginfo_t *info, व्योम *ucontext)
अणु
	अक्षर buf[1024];
	पूर्णांक len;

	SYSCALL_UNBLOCK;

	/* म_लिखो and मित्रs are not संकेत-safe. */
	len = snम_लिखो(buf, 1024, "Caught sys_%x\n", info->si_syscall);
	ग_लिखो(1, buf, len);

	अगर (info->si_syscall == MAGIC_SYSCALL_1)
		trapped_call_count++;
	अन्यथा
		native_call_count++;

#अगर_घोषित TEST_BLOCKED_RETURN
	SYSCALL_BLOCK;
#पूर्ण_अगर

#अगर_घोषित __x86_64__
	__यंत्र__ अस्थिर("movq $0xf, %rax");
	__यंत्र__ अस्थिर("leaveq");
	__यंत्र__ अस्थिर("add $0x8, %rsp");
	__यंत्र__ अस्थिर("syscall_dispatcher_start:");
	__यंत्र__ अस्थिर("syscall");
	__यंत्र__ अस्थिर("nop"); /* Landing pad within dispatcher area */
	__यंत्र__ अस्थिर("syscall_dispatcher_end:");
#पूर्ण_अगर

पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	काष्ठा sigaction act;
	द्विगुन समय1, समय2;
	पूर्णांक ret;
	sigset_t mask;

	स_रखो(&act, 0, माप(act));
	sigemptyset(&mask);

	act.sa_sigaction = handle_sigsys;
	act.sa_flags = SA_SIGINFO;
	act.sa_mask = mask;

	calibrate_set();

	समय1 = perf_syscall();
	म_लिखो("Avg syscall time %.0lfns.\n", समय1 * 1.0e9);

	ret = sigaction(SIGSYS, &act, शून्य);
	अगर (ret) अणु
		लिखो_त्रुटि("Error sigaction:");
		निकास(-1);
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "Enabling syscall trapping.\n");

	अगर (prctl(PR_SET_SYSCALL_USER_DISPATCH, PR_SYS_DISPATCH_ON,
		  syscall_dispatcher_start,
		  (syscall_dispatcher_end - syscall_dispatcher_start + 1),
		  &selector)) अणु
		लिखो_त्रुटि("prctl failed\n");
		निकास(-1);
	पूर्ण

	SYSCALL_BLOCK;
	syscall(MAGIC_SYSCALL_1);

#अगर_घोषित TEST_BLOCKED_RETURN
	अगर (selector == SYSCALL_DISPATCH_FILTER_ALLOW) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to return with selector blocked.\n");
		निकास(-1);
	पूर्ण
#पूर्ण_अगर

	SYSCALL_UNBLOCK;

	अगर (!trapped_call_count) अणु
		ख_लिखो(मानक_त्रुटि, "syscall trapping does not work.\n");
		निकास(-1);
	पूर्ण

	समय2 = perf_syscall();

	अगर (native_call_count) अणु
		लिखो_त्रुटि("syscall trapping intercepted more syscalls than expected\n");
		निकास(-1);
	पूर्ण

	म_लिखो("trapped_call_count %lu, native_call_count %lu.\n",
	       trapped_call_count, native_call_count);
	म_लिखो("Avg syscall time %.0lfns.\n", समय2 * 1.0e9);
	म_लिखो("Interception overhead: %.1lf%% (+%.0lfns).\n",
	       100.0 * (समय2 / समय1 - 1.0), 1.0e9 * (समय2 - समय1));
	वापस 0;

पूर्ण
