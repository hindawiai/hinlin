<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <poll.h>
#समावेश <संकेत.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <syscall.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

#समावेश "pidfd.h"
#समावेश "../kselftest.h"

अटल bool समयout;

अटल व्योम handle_alarm(पूर्णांक sig)
अणु
	समयout = true;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा pollfd fds;
	पूर्णांक iter, nevents;
	पूर्णांक nr_iterations = 10000;

	fds.events = POLLIN;

	अगर (argc > 2)
		ksft_निकास_fail_msg("Unexpected command line argument\n");

	अगर (argc == 2) अणु
		nr_iterations = म_से_प(argv[1]);
		अगर (nr_iterations <= 0)
			ksft_निकास_fail_msg("invalid input parameter %s\n",
					argv[1]);
	पूर्ण

	ksft_prपूर्णांक_msg("running pidfd poll test for %d iterations\n",
		nr_iterations);

	क्रम (iter = 0; iter < nr_iterations; iter++) अणु
		पूर्णांक pidfd;
		पूर्णांक child_pid = विभाजन();

		अगर (child_pid < 0) अणु
			अगर (त्रुटि_सं == EAGAIN) अणु
				iter--;
				जारी;
			पूर्ण
			ksft_निकास_fail_msg(
				"%s - failed to fork a child process\n",
				म_त्रुटि(त्रुटि_सं));
		पूर्ण

		अगर (child_pid == 0) अणु
			/* Child process just sleeps क्रम a min and निकासs */
			sleep(60);
			निकास(निकास_सफल);
		पूर्ण

		/* Parent समाप्तs the child and रुकोs क्रम its death */
		pidfd = sys_pidfd_खोलो(child_pid, 0);
		अगर (pidfd < 0)
			ksft_निकास_fail_msg("%s - pidfd_open failed\n",
					म_त्रुटि(त्रुटि_सं));

		/* Setup 3 sec alarm - plenty of समय */
		अगर (संकेत(SIGALRM, handle_alarm) == संक_त्रुटि)
			ksft_निकास_fail_msg("%s - signal failed\n",
					म_त्रुटि(त्रुटि_सं));
		alarm(3);

		/* Send SIGKILL to the child */
		अगर (sys_pidfd_send_संकेत(pidfd, SIGKILL, शून्य, 0))
			ksft_निकास_fail_msg("%s - pidfd_send_signal failed\n",
					म_त्रुटि(त्रुटि_सं));

		/* Wait क्रम the death notअगरication */
		fds.fd = pidfd;
		nevents = poll(&fds, 1, -1);

		/* Check क्रम error conditions */
		अगर (nevents < 0)
			ksft_निकास_fail_msg("%s - poll failed\n",
					म_त्रुटि(त्रुटि_सं));

		अगर (nevents != 1)
			ksft_निकास_fail_msg("unexpected poll result: %d\n",
					nevents);

		अगर (!(fds.revents & POLLIN))
			ksft_निकास_fail_msg(
				"unexpected event type received: 0x%x\n",
				fds.revents);

		अगर (समयout)
			ksft_निकास_fail_msg(
				"death notification wait timeout\n");

		बंद(pidfd);
		/* Wait क्रम child to prevent zombies */
		अगर (रुकोpid(child_pid, शून्य, 0) < 0)
			ksft_निकास_fail_msg("%s - waitpid failed\n",
					म_त्रुटि(त्रुटि_सं));

	पूर्ण

	ksft_test_result_pass("pidfd poll test: pass\n");
	वापस ksft_निकास_pass();
पूर्ण
