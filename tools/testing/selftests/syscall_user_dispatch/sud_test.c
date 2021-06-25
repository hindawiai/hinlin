<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2020 Collabora Ltd.
 *
 * Test code क्रम syscall user dispatch
 */

#घोषणा _GNU_SOURCE
#समावेश <sys/prctl.h>
#समावेश <sys/sysinfo.h>
#समावेश <sys/syscall.h>
#समावेश <संकेत.स>

#समावेश <यंत्र/unistd.h>
#समावेश "../kselftest_harness.h"

#अगर_अघोषित PR_SET_SYSCALL_USER_DISPATCH
# define PR_SET_SYSCALL_USER_DISPATCH	59
# define PR_SYS_DISPATCH_OFF	0
# define PR_SYS_DISPATCH_ON	1
# define SYSCALL_DISPATCH_FILTER_ALLOW	0
# define SYSCALL_DISPATCH_FILTER_BLOCK	1
#पूर्ण_अगर

#अगर_अघोषित SYS_USER_DISPATCH
# define SYS_USER_DISPATCH	2
#पूर्ण_अगर

#अगर_घोषित __NR_syscalls
# define MAGIC_SYSCALL_1 (__NR_syscalls + 1) /* Bad Linux syscall number */
#अन्यथा
# define MAGIC_SYSCALL_1 (0xff00)  /* Bad Linux syscall number */
#पूर्ण_अगर

#घोषणा SYSCALL_DISPATCH_ON(x) ((x) = SYSCALL_DISPATCH_FILTER_BLOCK)
#घोषणा SYSCALL_DISPATCH_OFF(x) ((x) = SYSCALL_DISPATCH_FILTER_ALLOW)

/* Test Summary:
 *
 * - dispatch_trigger_sigsys: Verअगरy अगर PR_SET_SYSCALL_USER_DISPATCH is
 *   able to trigger SIGSYS on a syscall.
 *
 * - bad_selector: Test that a bad selector value triggers SIGSYS with
 *   si_त्रुटि_सं EINVAL.
 *
 * - bad_prctl_param: Test that the API correctly rejects invalid
 *   parameters on prctl
 *
 * - dispatch_and_वापस: Test that a syscall is selectively dispatched
 *   to userspace depending on the value of selector.
 *
 * - disable_dispatch: Test that the PR_SYS_DISPATCH_OFF correctly
 *   disables the dispatcher
 *
 * - direct_dispatch_range: Test that a syscall within the allowed range
 *   can bypass the dispatcher.
 */

TEST_SIGNAL(dispatch_trigger_sigsys, SIGSYS)
अणु
	अक्षर sel = SYSCALL_DISPATCH_FILTER_ALLOW;
	काष्ठा sysinfo info;
	पूर्णांक ret;

	ret = sysinfo(&info);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SYSCALL_USER_DISPATCH, PR_SYS_DISPATCH_ON, 0, 0, &sel);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support CONFIG_SYSCALL_USER_DISPATCH");
	पूर्ण

	SYSCALL_DISPATCH_ON(sel);

	sysinfo(&info);

	EXPECT_FALSE(true) अणु
		TH_LOG("Unreachable!");
	पूर्ण
पूर्ण

TEST(bad_prctl_param)
अणु
	अक्षर sel = SYSCALL_DISPATCH_FILTER_ALLOW;
	पूर्णांक op;

	/* Invalid op */
	op = -1;
	prctl(PR_SET_SYSCALL_USER_DISPATCH, op, 0, 0, &sel);
	ASSERT_EQ(EINVAL, त्रुटि_सं);

	/* PR_SYS_DISPATCH_OFF */
	op = PR_SYS_DISPATCH_OFF;

	/* offset != 0 */
	prctl(PR_SET_SYSCALL_USER_DISPATCH, op, 0x1, 0x0, 0);
	EXPECT_EQ(EINVAL, त्रुटि_सं);

	/* len != 0 */
	prctl(PR_SET_SYSCALL_USER_DISPATCH, op, 0x0, 0xff, 0);
	EXPECT_EQ(EINVAL, त्रुटि_सं);

	/* sel != शून्य */
	prctl(PR_SET_SYSCALL_USER_DISPATCH, op, 0x0, 0x0, &sel);
	EXPECT_EQ(EINVAL, त्रुटि_सं);

	/* Valid parameter */
	त्रुटि_सं = 0;
	prctl(PR_SET_SYSCALL_USER_DISPATCH, op, 0x0, 0x0, 0x0);
	EXPECT_EQ(0, त्रुटि_सं);

	/* PR_SYS_DISPATCH_ON */
	op = PR_SYS_DISPATCH_ON;

	/* Dispatcher region is bad (offset > 0 && len == 0) */
	prctl(PR_SET_SYSCALL_USER_DISPATCH, op, 0x1, 0x0, &sel);
	EXPECT_EQ(EINVAL, त्रुटि_सं);
	prctl(PR_SET_SYSCALL_USER_DISPATCH, op, -1L, 0x0, &sel);
	EXPECT_EQ(EINVAL, त्रुटि_सं);

	/* Invalid selector */
	prctl(PR_SET_SYSCALL_USER_DISPATCH, op, 0x0, 0x1, (व्योम *) -1);
	ASSERT_EQ(EFAULT, त्रुटि_सं);

	/*
	 * Dispatcher range overflows अचिन्हित दीर्घ
	 */
	prctl(PR_SET_SYSCALL_USER_DISPATCH, PR_SYS_DISPATCH_ON, 1, -1L, &sel);
	ASSERT_EQ(EINVAL, त्रुटि_सं) अणु
		TH_LOG("Should reject bad syscall range");
	पूर्ण

	/*
	 * Allowed range overflows uचिन्हित दीर्घ
	 */
	prctl(PR_SET_SYSCALL_USER_DISPATCH, PR_SYS_DISPATCH_ON, -1L, 0x1, &sel);
	ASSERT_EQ(EINVAL, त्रुटि_सं) अणु
		TH_LOG("Should reject bad syscall range");
	पूर्ण
पूर्ण

/*
 * Use global selector क्रम handle_sigsys tests, to aव्योम passing
 * selector to संकेत handler
 */
अक्षर glob_sel;
पूर्णांक nr_syscalls_emulated;
पूर्णांक si_code;
पूर्णांक si_त्रुटि_सं;

अटल व्योम handle_sigsys(पूर्णांक sig, siginfo_t *info, व्योम *ucontext)
अणु
	si_code = info->si_code;
	si_त्रुटि_सं = info->si_त्रुटि_सं;

	अगर (info->si_syscall == MAGIC_SYSCALL_1)
		nr_syscalls_emulated++;

	/* In preparation क्रम sigवापस. */
	SYSCALL_DISPATCH_OFF(glob_sel);
पूर्ण

TEST(dispatch_and_वापस)
अणु
	दीर्घ ret;
	काष्ठा sigaction act;
	sigset_t mask;

	glob_sel = 0;
	nr_syscalls_emulated = 0;
	si_code = 0;
	si_त्रुटि_सं = 0;

	स_रखो(&act, 0, माप(act));
	sigemptyset(&mask);

	act.sa_sigaction = handle_sigsys;
	act.sa_flags = SA_SIGINFO;
	act.sa_mask = mask;

	ret = sigaction(SIGSYS, &act, शून्य);
	ASSERT_EQ(0, ret);

	/* Make sure selector is good prior to prctl. */
	SYSCALL_DISPATCH_OFF(glob_sel);

	ret = prctl(PR_SET_SYSCALL_USER_DISPATCH, PR_SYS_DISPATCH_ON, 0, 0, &glob_sel);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support CONFIG_SYSCALL_USER_DISPATCH");
	पूर्ण

	/* MAGIC_SYSCALL_1 करोesn't exist. */
	SYSCALL_DISPATCH_OFF(glob_sel);
	ret = syscall(MAGIC_SYSCALL_1);
	EXPECT_EQ(-1, ret) अणु
		TH_LOG("Dispatch triggered unexpectedly");
	पूर्ण

	/* MAGIC_SYSCALL_1 should be emulated. */
	nr_syscalls_emulated = 0;
	SYSCALL_DISPATCH_ON(glob_sel);

	ret = syscall(MAGIC_SYSCALL_1);
	EXPECT_EQ(MAGIC_SYSCALL_1, ret) अणु
		TH_LOG("Failed to intercept syscall");
	पूर्ण
	EXPECT_EQ(1, nr_syscalls_emulated) अणु
		TH_LOG("Failed to emulate syscall");
	पूर्ण
	ASSERT_EQ(SYS_USER_DISPATCH, si_code) अणु
		TH_LOG("Bad si_code in SIGSYS");
	पूर्ण
	ASSERT_EQ(0, si_त्रुटि_सं) अणु
		TH_LOG("Bad si_errno in SIGSYS");
	पूर्ण
पूर्ण

TEST_SIGNAL(bad_selector, SIGSYS)
अणु
	दीर्घ ret;
	काष्ठा sigaction act;
	sigset_t mask;
	काष्ठा sysinfo info;

	glob_sel = SYSCALL_DISPATCH_FILTER_ALLOW;
	nr_syscalls_emulated = 0;
	si_code = 0;
	si_त्रुटि_सं = 0;

	स_रखो(&act, 0, माप(act));
	sigemptyset(&mask);

	act.sa_sigaction = handle_sigsys;
	act.sa_flags = SA_SIGINFO;
	act.sa_mask = mask;

	ret = sigaction(SIGSYS, &act, शून्य);
	ASSERT_EQ(0, ret);

	/* Make sure selector is good prior to prctl. */
	SYSCALL_DISPATCH_OFF(glob_sel);

	ret = prctl(PR_SET_SYSCALL_USER_DISPATCH, PR_SYS_DISPATCH_ON, 0, 0, &glob_sel);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support CONFIG_SYSCALL_USER_DISPATCH");
	पूर्ण

	glob_sel = -1;

	sysinfo(&info);

	/* Even though it is पढ़ोy to catch SIGSYS, the संकेत is
	 * supposed to be uncatchable.
	 */

	EXPECT_FALSE(true) अणु
		TH_LOG("Unreachable!");
	पूर्ण
पूर्ण

TEST(disable_dispatch)
अणु
	पूर्णांक ret;
	काष्ठा sysinfo info;
	अक्षर sel = 0;

	ret = prctl(PR_SET_SYSCALL_USER_DISPATCH, PR_SYS_DISPATCH_ON, 0, 0, &sel);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support CONFIG_SYSCALL_USER_DISPATCH");
	पूर्ण

	/* MAGIC_SYSCALL_1 करोesn't exist. */
	SYSCALL_DISPATCH_OFF(glob_sel);

	ret = prctl(PR_SET_SYSCALL_USER_DISPATCH, PR_SYS_DISPATCH_OFF, 0, 0, 0);
	EXPECT_EQ(0, ret) अणु
		TH_LOG("Failed to unset syscall user dispatch");
	पूर्ण

	/* Shouldn't have any effect... */
	SYSCALL_DISPATCH_ON(glob_sel);

	ret = syscall(__NR_sysinfo, &info);
	EXPECT_EQ(0, ret) अणु
		TH_LOG("Dispatch triggered unexpectedly");
	पूर्ण
पूर्ण

TEST(direct_dispatch_range)
अणु
	पूर्णांक ret = 0;
	काष्ठा sysinfo info;
	अक्षर sel = SYSCALL_DISPATCH_FILTER_ALLOW;

	/*
	 * Instead of calculating libc addresses; allow the entire
	 * memory map and lock the selector.
	 */
	ret = prctl(PR_SET_SYSCALL_USER_DISPATCH, PR_SYS_DISPATCH_ON, 0, -1L, &sel);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support CONFIG_SYSCALL_USER_DISPATCH");
	पूर्ण

	SYSCALL_DISPATCH_ON(sel);

	ret = sysinfo(&info);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Dispatch triggered unexpectedly");
	पूर्ण
पूर्ण

TEST_HARNESS_MAIN
