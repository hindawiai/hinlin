<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <sched.h>

#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <समय.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <संकेत.स>

#समावेश "log.h"
#समावेश "timens.h"

पूर्णांक run_test(पूर्णांक घड़ीid, काष्ठा बारpec now)
अणु
	काष्ठा iसमयrspec new_value;
	दीर्घ दीर्घ elapsed;
	समयr_t fd;
	पूर्णांक i;

	अगर (check_skip(घड़ीid))
		वापस 0;

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा sigevent sevp = अणु.sigev_notअगरy = SIGEV_NONEपूर्ण;
		पूर्णांक flags = 0;

		new_value.it_value.tv_sec = 3600;
		new_value.it_value.tv_nsec = 0;
		new_value.it_पूर्णांकerval.tv_sec = 1;
		new_value.it_पूर्णांकerval.tv_nsec = 0;

		अगर (i == 1) अणु
			new_value.it_value.tv_sec += now.tv_sec;
			new_value.it_value.tv_nsec += now.tv_nsec;
		पूर्ण

		अगर (समयr_create(घड़ीid, &sevp, &fd) == -1) अणु
			अगर (त्रुटि_सं == ENOSYS) अणु
				ksft_test_result_skip("Posix Clocks & timers are supported\n");
				वापस 0;
			पूर्ण
			वापस pr_लिखो_त्रुटि("timerfd_create");
		पूर्ण

		अगर (i == 1)
			flags |= TIMER_ABSTIME;
		अगर (समयr_समय_रखो(fd, flags, &new_value, शून्य) == -1)
			वापस pr_लिखो_त्रुटि("timerfd_settime");

		अगर (समयr_समय_लो(fd, &new_value) == -1)
			वापस pr_लिखो_त्रुटि("timerfd_gettime");

		elapsed = new_value.it_value.tv_sec;
		अगर (असल(elapsed - 3600) > 60) अणु
			ksft_test_result_fail("clockid: %d elapsed: %lld\n",
					      घड़ीid, elapsed);
			वापस 1;
		पूर्ण
	पूर्ण

	ksft_test_result_pass("clockid=%d\n", घड़ीid);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक ret, status, len, fd;
	अक्षर buf[4096];
	pid_t pid;
	काष्ठा बारpec bसमय_now, mसमय_now;

	nscheck();

	check_supported_समयrs();

	ksft_set_plan(3);

	घड़ी_समय_लो(CLOCK_MONOTONIC, &mसमय_now);
	घड़ी_समय_लो(CLOCK_BOOTTIME, &bसमय_now);

	अगर (unshare_समयns())
		वापस 1;

	len = snम_लिखो(buf, माप(buf), "%d %d 0\n%d %d 0",
			CLOCK_MONOTONIC, 70 * 24 * 3600,
			CLOCK_BOOTTIME, 9 * 24 * 3600);
	fd = खोलो("/proc/self/timens_offsets", O_WRONLY);
	अगर (fd < 0)
		वापस pr_लिखो_त्रुटि("/proc/self/timens_offsets");

	अगर (ग_लिखो(fd, buf, len) != len)
		वापस pr_लिखो_त्रुटि("/proc/self/timens_offsets");

	बंद(fd);
	mसमय_now.tv_sec += 70 * 24 * 3600;
	bसमय_now.tv_sec += 9 * 24 * 3600;

	pid = विभाजन();
	अगर (pid < 0)
		वापस pr_लिखो_त्रुटि("Unable to fork");
	अगर (pid == 0) अणु
		ret = 0;
		ret |= run_test(CLOCK_BOOTTIME, bसमय_now);
		ret |= run_test(CLOCK_MONOTONIC, mसमय_now);
		ret |= run_test(CLOCK_BOOTTIME_ALARM, bसमय_now);

		अगर (ret)
			ksft_निकास_fail();
		ksft_निकास_pass();
		वापस ret;
	पूर्ण

	अगर (रुकोpid(pid, &status, 0) != pid)
		वापस pr_लिखो_त्रुटि("Unable to wait the child process");

	अगर (WIFEXITED(status))
		वापस WEXITSTATUS(status);

	वापस 1;
पूर्ण
