<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <समय.स>
#समावेश <unistd.h>
#समावेश <माला.स>

#समावेश "log.h"
#समावेश "timens.h"

#घोषणा OFFSET (36000)

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा बारpec now, tst;
	पूर्णांक status, i;
	pid_t pid;

	अगर (argc > 1) अणु
		अगर (माला_पूछो(argv[1], "%ld", &now.tv_sec) != 1)
			वापस pr_लिखो_त्रुटि("sscanf");

		क्रम (i = 0; i < 2; i++) अणु
			_समय_लो(CLOCK_MONOTONIC, &tst, i);
			अगर (असल(tst.tv_sec - now.tv_sec) > 5)
				वापस pr_fail("%ld %ld\n", now.tv_sec, tst.tv_sec);
		पूर्ण
		वापस 0;
	पूर्ण

	nscheck();

	ksft_set_plan(1);

	घड़ी_समय_लो(CLOCK_MONOTONIC, &now);

	अगर (unshare_समयns())
		वापस 1;

	अगर (_समय_रखो(CLOCK_MONOTONIC, OFFSET))
		वापस 1;

	क्रम (i = 0; i < 2; i++) अणु
		_समय_लो(CLOCK_MONOTONIC, &tst, i);
		अगर (असल(tst.tv_sec - now.tv_sec) > 5)
			वापस pr_fail("%ld %ld\n",
					now.tv_sec, tst.tv_sec);
	पूर्ण

	अगर (argc > 1)
		वापस 0;

	pid = विभाजन();
	अगर (pid < 0)
		वापस pr_लिखो_त्रुटि("fork");

	अगर (pid == 0) अणु
		अक्षर now_str[64];
		अक्षर *cargv[] = अणु"exec", now_str, शून्यपूर्ण;
		अक्षर *cenv[] = अणुशून्यपूर्ण;

		/* Check that a child process is in the new समयns. */
		क्रम (i = 0; i < 2; i++) अणु
			_समय_लो(CLOCK_MONOTONIC, &tst, i);
			अगर (असल(tst.tv_sec - now.tv_sec - OFFSET) > 5)
				वापस pr_fail("%ld %ld\n",
						now.tv_sec + OFFSET, tst.tv_sec);
		पूर्ण

		/* Check क्रम proper vvar offsets after execve. */
		snम_लिखो(now_str, माप(now_str), "%ld", now.tv_sec + OFFSET);
		execve("/proc/self/exe", cargv, cenv);
		वापस pr_लिखो_त्रुटि("execve");
	पूर्ण

	अगर (रुकोpid(pid, &status, 0) != pid)
		वापस pr_लिखो_त्रुटि("waitpid");

	अगर (status)
		ksft_निकास_fail();

	ksft_test_result_pass("exec\n");
	ksft_निकास_pass();
	वापस 0;
पूर्ण
