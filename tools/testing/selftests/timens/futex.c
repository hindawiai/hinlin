<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <sched.h>

#समावेश <linux/unistd.h>
#समावेश <linux/futex.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <समय.स>
#समावेश <unistd.h>

#समावेश "log.h"
#समावेश "timens.h"

#घोषणा NSEC_PER_SEC 1000000000ULL

अटल पूर्णांक run_test(पूर्णांक घड़ीid)
अणु
	पूर्णांक futex_op = FUTEX_WAIT_BITSET;
	काष्ठा बारpec समयout, end;
	पूर्णांक val = 0;

	अगर (घड़ीid == CLOCK_REALTIME)
		futex_op |= FUTEX_CLOCK_REALTIME;

	घड़ी_समय_लो(घड़ीid, &समयout);
	समयout.tv_nsec += NSEC_PER_SEC / 10; // 100ms
	अगर (समयout.tv_nsec > NSEC_PER_SEC) अणु
		समयout.tv_sec++;
		समयout.tv_nsec -= NSEC_PER_SEC;
	पूर्ण

	अगर (syscall(__NR_futex, &val, futex_op, 0,
		    &समयout, 0, FUTEX_BITSET_MATCH_ANY) >= 0) अणु
		ksft_test_result_fail("futex didn't return ETIMEDOUT\n");
		वापस 1;
	पूर्ण

	अगर (त्रुटि_सं != ETIMEDOUT) अणु
		ksft_test_result_fail("futex didn't return ETIMEDOUT: %s\n",
							म_त्रुटि(त्रुटि_सं));
		वापस 1;
	पूर्ण

	घड़ी_समय_लो(घड़ीid, &end);

	अगर (end.tv_sec < समयout.tv_sec ||
	    (end.tv_sec == समयout.tv_sec && end.tv_nsec < समयout.tv_nsec)) अणु
		ksft_test_result_fail("futex slept less than 100ms\n");
		वापस 1;
	पूर्ण


	ksft_test_result_pass("futex with the %d clockid\n", घड़ीid);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक status, len, fd;
	अक्षर buf[4096];
	pid_t pid;
	काष्ठा बारpec mसमय_now;

	nscheck();

	ksft_set_plan(2);

	घड़ी_समय_लो(CLOCK_MONOTONIC, &mसमय_now);

	अगर (unshare_समयns())
		वापस 1;

	len = snम_लिखो(buf, माप(buf), "%d %d 0",
			CLOCK_MONOTONIC, 70 * 24 * 3600);
	fd = खोलो("/proc/self/timens_offsets", O_WRONLY);
	अगर (fd < 0)
		वापस pr_लिखो_त्रुटि("/proc/self/timens_offsets");

	अगर (ग_लिखो(fd, buf, len) != len)
		वापस pr_लिखो_त्रुटि("/proc/self/timens_offsets");

	बंद(fd);

	pid = विभाजन();
	अगर (pid < 0)
		वापस pr_लिखो_त्रुटि("Unable to fork");
	अगर (pid == 0) अणु
		पूर्णांक ret = 0;

		ret |= run_test(CLOCK_REALTIME);
		ret |= run_test(CLOCK_MONOTONIC);
		अगर (ret)
			ksft_निकास_fail();
		ksft_निकास_pass();
		वापस 0;
	पूर्ण

	अगर (रुकोpid(pid, &status, 0) != pid)
		वापस pr_लिखो_त्रुटि("Unable to wait the child process");

	अगर (WIFEXITED(status))
		वापस WEXITSTATUS(status);

	वापस 1;
पूर्ण
