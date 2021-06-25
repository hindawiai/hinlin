<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <sys/syscall.h>
#समावेश <sys/रुको.h>

#समावेश "../kselftest.h"
#समावेश "clone3_selftests.h"

#अगर_अघोषित CLONE_CLEAR_SIGHAND
#घोषणा CLONE_CLEAR_SIGHAND 0x100000000ULL
#पूर्ण_अगर

अटल व्योम nop_handler(पूर्णांक signo)
अणु
पूर्ण

अटल पूर्णांक रुको_क्रम_pid(pid_t pid)
अणु
	पूर्णांक status, ret;

again:
	ret = रुकोpid(pid, &status, 0);
	अगर (ret == -1) अणु
		अगर (त्रुटि_सं == EINTR)
			जाओ again;

		वापस -1;
	पूर्ण

	अगर (!WIFEXITED(status))
		वापस -1;

	वापस WEXITSTATUS(status);
पूर्ण

अटल व्योम test_clone3_clear_sighand(व्योम)
अणु
	पूर्णांक ret;
	pid_t pid;
	काष्ठा __clone_args args = अणुपूर्ण;
	काष्ठा sigaction act;

	/*
	 * Check that CLONE_CLEAR_SIGHAND and CLONE_SIGHAND are mutually
	 * exclusive.
	 */
	args.flags |= CLONE_CLEAR_SIGHAND | CLONE_SIGHAND;
	args.निकास_संकेत = SIGCHLD;
	pid = sys_clone3(&args, माप(args));
	अगर (pid > 0)
		ksft_निकास_fail_msg(
			"clone3(CLONE_CLEAR_SIGHAND | CLONE_SIGHAND) succeeded\n");

	act.sa_handler = nop_handler;
	ret = sigemptyset(&act.sa_mask);
	अगर (ret < 0)
		ksft_निकास_fail_msg("%s - sigemptyset() failed\n",
				   म_त्रुटि(त्रुटि_सं));

	act.sa_flags = 0;

	/* Register संकेत handler क्रम SIGUSR1 */
	ret = sigaction(SIGUSR1, &act, शून्य);
	अगर (ret < 0)
		ksft_निकास_fail_msg(
			"%s - sigaction(SIGUSR1, &act, NULL) failed\n",
			म_त्रुटि(त्रुटि_सं));

	/* Register संकेत handler क्रम SIGUSR2 */
	ret = sigaction(SIGUSR2, &act, शून्य);
	अगर (ret < 0)
		ksft_निकास_fail_msg(
			"%s - sigaction(SIGUSR2, &act, NULL) failed\n",
			म_त्रुटि(त्रुटि_सं));

	/* Check that CLONE_CLEAR_SIGHAND works. */
	args.flags = CLONE_CLEAR_SIGHAND;
	pid = sys_clone3(&args, माप(args));
	अगर (pid < 0)
		ksft_निकास_fail_msg("%s - clone3(CLONE_CLEAR_SIGHAND) failed\n",
				   म_त्रुटि(त्रुटि_सं));

	अगर (pid == 0) अणु
		ret = sigaction(SIGUSR1, शून्य, &act);
		अगर (ret < 0)
			निकास(निकास_त्रुटि);

		अगर (act.sa_handler != संक_पूर्व)
			निकास(निकास_त्रुटि);

		ret = sigaction(SIGUSR2, शून्य, &act);
		अगर (ret < 0)
			निकास(निकास_त्रुटि);

		अगर (act.sa_handler != संक_पूर्व)
			निकास(निकास_त्रुटि);

		निकास(निकास_सफल);
	पूर्ण

	ret = रुको_क्रम_pid(pid);
	अगर (ret)
		ksft_निकास_fail_msg(
			"Failed to clear signal handler for child process\n");

	ksft_test_result_pass("Cleared signal handlers for child process\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	ksft_prपूर्णांक_header();
	ksft_set_plan(1);
	test_clone3_supported();

	test_clone3_clear_sighand();

	वापस ksft_निकास_pass();
पूर्ण
