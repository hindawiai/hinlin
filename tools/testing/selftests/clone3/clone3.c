<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Based on Christian Brauner's clone3() example */

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <sys/un.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>
#समावेश <sched.h>

#समावेश "../kselftest.h"
#समावेश "clone3_selftests.h"

क्रमागत test_mode अणु
	CLONE3_ARGS_NO_TEST,
	CLONE3_ARGS_ALL_0,
	CLONE3_ARGS_INVAL_EXIT_SIGNAL_BIG,
	CLONE3_ARGS_INVAL_EXIT_SIGNAL_NEG,
	CLONE3_ARGS_INVAL_EXIT_SIGNAL_CSIG,
	CLONE3_ARGS_INVAL_EXIT_SIGNAL_NSIG,
पूर्ण;

अटल पूर्णांक call_clone3(uपूर्णांक64_t flags, माप_प्रकार size, क्रमागत test_mode test_mode)
अणु
	काष्ठा __clone_args args = अणु
		.flags = flags,
		.निकास_संकेत = SIGCHLD,
	पूर्ण;

	काष्ठा clone_args_extended अणु
		काष्ठा __clone_args args;
		__aligned_u64 excess_space[2];
	पूर्ण args_ext;

	pid_t pid = -1;
	पूर्णांक status;

	स_रखो(&args_ext, 0, माप(args_ext));
	अगर (size > माप(काष्ठा __clone_args))
		args_ext.excess_space[1] = 1;

	अगर (size == 0)
		size = माप(काष्ठा __clone_args);

	चयन (test_mode) अणु
	हाल CLONE3_ARGS_ALL_0:
		args.flags = 0;
		args.निकास_संकेत = 0;
		अवरोध;
	हाल CLONE3_ARGS_INVAL_EXIT_SIGNAL_BIG:
		args.निकास_संकेत = 0xbadc0ded00000000ULL;
		अवरोध;
	हाल CLONE3_ARGS_INVAL_EXIT_SIGNAL_NEG:
		args.निकास_संकेत = 0x0000000080000000ULL;
		अवरोध;
	हाल CLONE3_ARGS_INVAL_EXIT_SIGNAL_CSIG:
		args.निकास_संकेत = 0x0000000000000100ULL;
		अवरोध;
	हाल CLONE3_ARGS_INVAL_EXIT_SIGNAL_NSIG:
		args.निकास_संकेत = 0x00000000000000f0ULL;
		अवरोध;
	पूर्ण

	स_नकल(&args_ext.args, &args, माप(काष्ठा __clone_args));

	pid = sys_clone3((काष्ठा __clone_args *)&args_ext, size);
	अगर (pid < 0) अणु
		ksft_prपूर्णांक_msg("%s - Failed to create new process\n",
				म_त्रुटि(त्रुटि_सं));
		वापस -त्रुटि_सं;
	पूर्ण

	अगर (pid == 0) अणु
		ksft_prपूर्णांक_msg("I am the child, my PID is %d\n", getpid());
		_निकास(निकास_सफल);
	पूर्ण

	ksft_prपूर्णांक_msg("I am the parent (%d). My child's pid is %d\n",
			getpid(), pid);

	अगर (रुकोpid(-1, &status, __WALL) < 0) अणु
		ksft_prपूर्णांक_msg("Child returned %s\n", म_त्रुटि(त्रुटि_सं));
		वापस -त्रुटि_सं;
	पूर्ण
	अगर (WEXITSTATUS(status))
		वापस WEXITSTATUS(status);

	वापस 0;
पूर्ण

अटल व्योम test_clone3(uपूर्णांक64_t flags, माप_प्रकार size, पूर्णांक expected,
		       क्रमागत test_mode test_mode)
अणु
	पूर्णांक ret;

	ksft_prपूर्णांक_msg(
		"[%d] Trying clone3() with flags %#" PRIx64 " (size %zu)\n",
		getpid(), flags, size);
	ret = call_clone3(flags, size, test_mode);
	ksft_prपूर्णांक_msg("[%d] clone3() with flags says: %d expected %d\n",
			getpid(), ret, expected);
	अगर (ret != expected)
		ksft_test_result_fail(
			"[%d] Result (%d) is different than expected (%d)\n",
			getpid(), ret, expected);
	अन्यथा
		ksft_test_result_pass(
			"[%d] Result (%d) matches expectation (%d)\n",
			getpid(), ret, expected);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	pid_t pid;

	uid_t uid = getuid();

	ksft_prपूर्णांक_header();
	ksft_set_plan(17);
	test_clone3_supported();

	/* Just a simple clone3() should वापस 0.*/
	test_clone3(0, 0, 0, CLONE3_ARGS_NO_TEST);

	/* Do a clone3() in a new PID NS.*/
	अगर (uid == 0)
		test_clone3(CLONE_NEWPID, 0, 0, CLONE3_ARGS_NO_TEST);
	अन्यथा
		ksft_test_result_skip("Skipping clone3() with CLONE_NEWPID\n");

	/* Do a clone3() with CLONE_ARGS_SIZE_VER0. */
	test_clone3(0, CLONE_ARGS_SIZE_VER0, 0, CLONE3_ARGS_NO_TEST);

	/* Do a clone3() with CLONE_ARGS_SIZE_VER0 - 8 */
	test_clone3(0, CLONE_ARGS_SIZE_VER0 - 8, -EINVAL, CLONE3_ARGS_NO_TEST);

	/* Do a clone3() with माप(काष्ठा clone_args) + 8 */
	test_clone3(0, माप(काष्ठा __clone_args) + 8, 0, CLONE3_ARGS_NO_TEST);

	/* Do a clone3() with निकास_संकेत having highest 32 bits non-zero */
	test_clone3(0, 0, -EINVAL, CLONE3_ARGS_INVAL_EXIT_SIGNAL_BIG);

	/* Do a clone3() with negative 32-bit निकास_संकेत */
	test_clone3(0, 0, -EINVAL, CLONE3_ARGS_INVAL_EXIT_SIGNAL_NEG);

	/* Do a clone3() with निकास_संकेत not fitting पूर्णांकo CSIGNAL mask */
	test_clone3(0, 0, -EINVAL, CLONE3_ARGS_INVAL_EXIT_SIGNAL_CSIG);

	/* Do a clone3() with NSIG < निकास_संकेत < CSIG */
	test_clone3(0, 0, -EINVAL, CLONE3_ARGS_INVAL_EXIT_SIGNAL_NSIG);

	test_clone3(0, माप(काष्ठा __clone_args) + 8, 0, CLONE3_ARGS_ALL_0);

	test_clone3(0, माप(काष्ठा __clone_args) + 16, -E2BIG,
			CLONE3_ARGS_ALL_0);

	test_clone3(0, माप(काष्ठा __clone_args) * 2, -E2BIG,
			CLONE3_ARGS_ALL_0);

	/* Do a clone3() with > page size */
	test_clone3(0, getpagesize() + 8, -E2BIG, CLONE3_ARGS_NO_TEST);

	/* Do a clone3() with CLONE_ARGS_SIZE_VER0 in a new PID NS. */
	अगर (uid == 0)
		test_clone3(CLONE_NEWPID, CLONE_ARGS_SIZE_VER0, 0,
				CLONE3_ARGS_NO_TEST);
	अन्यथा
		ksft_test_result_skip("Skipping clone3() with CLONE_NEWPID\n");

	/* Do a clone3() with CLONE_ARGS_SIZE_VER0 - 8 in a new PID NS */
	test_clone3(CLONE_NEWPID, CLONE_ARGS_SIZE_VER0 - 8, -EINVAL,
			CLONE3_ARGS_NO_TEST);

	/* Do a clone3() with माप(काष्ठा clone_args) + 8 in a new PID NS */
	अगर (uid == 0)
		test_clone3(CLONE_NEWPID, माप(काष्ठा __clone_args) + 8, 0,
				CLONE3_ARGS_NO_TEST);
	अन्यथा
		ksft_test_result_skip("Skipping clone3() with CLONE_NEWPID\n");

	/* Do a clone3() with > page size in a new PID NS */
	test_clone3(CLONE_NEWPID, getpagesize() + 8, -E2BIG,
			CLONE3_ARGS_NO_TEST);

	वापस !ksft_get_fail_cnt() ? ksft_निकास_pass() : ksft_निकास_fail();
पूर्ण
