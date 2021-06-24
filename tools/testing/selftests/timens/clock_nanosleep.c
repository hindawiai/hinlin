<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <sched.h>

#समावेश <sys/समयrfd.h>
#समावेश <sys/syscall.h>
#समावेश <समय.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <pthपढ़ो.h>
#समावेश <संकेत.स>
#समावेश <माला.स>

#समावेश "log.h"
#समावेश "timens.h"

व्योम test_sig(पूर्णांक sig)
अणु
	अगर (sig == SIGUSR2)
		pthपढ़ो_निकास(शून्य);
पूर्ण

काष्ठा thपढ़ो_args अणु
	काष्ठा बारpec *now, *rem;
	pthपढ़ो_mutex_t *lock;
	पूर्णांक घड़ीid;
	पूर्णांक असल;
पूर्ण;

व्योम *call_nanosleep(व्योम *_args)
अणु
	काष्ठा thपढ़ो_args *args = _args;

	घड़ी_nanosleep(args->घड़ीid, args->असल ? TIMER_ABSTIME : 0, args->now, args->rem);
	pthपढ़ो_mutex_unlock(args->lock);
	वापस शून्य;
पूर्ण

पूर्णांक run_test(पूर्णांक घड़ीid, पूर्णांक असल)
अणु
	काष्ठा बारpec now = अणुपूर्ण, rem;
	काष्ठा thपढ़ो_args args = अणु .now = &now, .rem = &rem, .घड़ीid = घड़ीidपूर्ण;
	काष्ठा बारpec start;
	pthपढ़ो_mutex_t lock;
	pthपढ़ो_t thपढ़ो;
	पूर्णांक j, ok, ret;

	संकेत(SIGUSR1, test_sig);
	संकेत(SIGUSR2, test_sig);

	pthपढ़ो_mutex_init(&lock, शून्य);
	pthपढ़ो_mutex_lock(&lock);

	अगर (घड़ी_समय_लो(घड़ीid, &start) == -1) अणु
		अगर (त्रुटि_सं == EINVAL && check_skip(घड़ीid))
			वापस 0;
		वापस pr_लिखो_त्रुटि("clock_gettime");
	पूर्ण


	अगर (असल) अणु
		now.tv_sec = start.tv_sec;
		now.tv_nsec = start.tv_nsec;
	पूर्ण

	now.tv_sec += 3600;
	args.असल = असल;
	args.lock = &lock;
	ret = pthपढ़ो_create(&thपढ़ो, शून्य, call_nanosleep, &args);
	अगर (ret != 0) अणु
		pr_err("Unable to create a thread: %s", म_त्रुटि(ret));
		वापस 1;
	पूर्ण

	/* Wait when the thपढ़ो will call घड़ी_nanosleep(). */
	ok = 0;
	क्रम (j = 0; j < 8; j++) अणु
		/* The maximum समयout is about 5 seconds. */
		usleep(10000 << j);

		/* Try to पूर्णांकerrupt घड़ी_nanosleep(). */
		pthपढ़ो_समाप्त(thपढ़ो, SIGUSR1);

		usleep(10000 << j);
		/* Check whether घड़ी_nanosleep() has been पूर्णांकerrupted or not. */
		अगर (pthपढ़ो_mutex_trylock(&lock) == 0) अणु
			/**/
			ok = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!ok)
		pthपढ़ो_समाप्त(thपढ़ो, SIGUSR2);
	pthपढ़ो_join(thपढ़ो, शून्य);
	pthपढ़ो_mutex_destroy(&lock);

	अगर (!ok) अणु
		ksft_test_result_pass("clockid: %d abs:%d timeout\n", घड़ीid, असल);
		वापस 1;
	पूर्ण

	अगर (rem.tv_sec < 3300 || rem.tv_sec > 3900) अणु
		pr_fail("clockid: %d abs: %d remain: %ld\n",
			घड़ीid, असल, rem.tv_sec);
		वापस 1;
	पूर्ण
	ksft_test_result_pass("clockid: %d abs:%d\n", घड़ीid, असल);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक ret, nsfd;

	nscheck();

	ksft_set_plan(4);

	check_supported_समयrs();

	अगर (unshare_समयns())
		वापस 1;

	अगर (_समय_रखो(CLOCK_MONOTONIC, 7 * 24 * 3600))
		वापस 1;
	अगर (_समय_रखो(CLOCK_BOOTTIME, 9 * 24 * 3600))
		वापस 1;

	nsfd = खोलो("/proc/self/ns/time_for_children", O_RDONLY);
	अगर (nsfd < 0)
		वापस pr_लिखो_त्रुटि("Unable to open timens_for_children");

	अगर (setns(nsfd, CLONE_NEWTIME))
		वापस pr_लिखो_त्रुटि("Unable to set timens");

	ret = 0;
	ret |= run_test(CLOCK_MONOTONIC, 0);
	ret |= run_test(CLOCK_MONOTONIC, 1);
	ret |= run_test(CLOCK_BOOTTIME_ALARM, 0);
	ret |= run_test(CLOCK_BOOTTIME_ALARM, 1);

	अगर (ret)
		ksft_निकास_fail();
	ksft_निकास_pass();
	वापस ret;
पूर्ण
