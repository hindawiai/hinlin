<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <linux/types.h>
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <syscall.h>
#समावेश <sys/epoll.h>
#समावेश <sys/mman.h>
#समावेश <sys/mount.h>
#समावेश <sys/रुको.h>
#समावेश <समय.स>
#समावेश <unistd.h>

#समावेश "pidfd.h"
#समावेश "../kselftest.h"

#घोषणा str(s) _str(s)
#घोषणा _str(s) #s
#घोषणा CHILD_THREAD_MIN_WAIT 3 /* seconds */

#घोषणा MAX_EVENTS 5

अटल bool have_pidfd_send_संकेत;

अटल pid_t pidfd_clone(पूर्णांक flags, पूर्णांक *pidfd, पूर्णांक (*fn)(व्योम *))
अणु
	माप_प्रकार stack_size = 1024;
	अक्षर *stack[1024] = अणु 0 पूर्ण;

#अगर_घोषित __ia64__
	वापस __clone2(fn, stack, stack_size, flags | SIGCHLD, शून्य, pidfd);
#अन्यथा
	वापस clone(fn, stack + stack_size, flags | SIGCHLD, शून्य, pidfd);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक संकेत_received;

अटल व्योम set_संकेत_received_on_sigusr1(पूर्णांक sig)
अणु
	अगर (sig == SIGUSR1)
		संकेत_received = 1;
पूर्ण

/*
 * Straightक्रमward test to see whether pidfd_send_संकेत() works is to send
 * a संकेत to ourself.
 */
अटल पूर्णांक test_pidfd_send_संकेत_simple_success(व्योम)
अणु
	पूर्णांक pidfd, ret;
	स्थिर अक्षर *test_name = "pidfd_send_signal send SIGUSR1";

	अगर (!have_pidfd_send_संकेत) अणु
		ksft_test_result_skip(
			"%s test: pidfd_send_signal() syscall not supported\n",
			test_name);
		वापस 0;
	पूर्ण

	pidfd = खोलो("/proc/self", O_सूचीECTORY | O_CLOEXEC);
	अगर (pidfd < 0)
		ksft_निकास_fail_msg(
			"%s test: Failed to open process file descriptor\n",
			test_name);

	संकेत(SIGUSR1, set_संकेत_received_on_sigusr1);

	ret = sys_pidfd_send_संकेत(pidfd, SIGUSR1, शून्य, 0);
	बंद(pidfd);
	अगर (ret < 0)
		ksft_निकास_fail_msg("%s test: Failed to send signal\n",
				   test_name);

	अगर (संकेत_received != 1)
		ksft_निकास_fail_msg("%s test: Failed to receive signal\n",
				   test_name);

	संकेत_received = 0;
	ksft_test_result_pass("%s test: Sent signal\n", test_name);
	वापस 0;
पूर्ण

अटल पूर्णांक test_pidfd_send_संकेत_निकासed_fail(व्योम)
अणु
	पूर्णांक pidfd, ret, saved_त्रुटि_सं;
	अक्षर buf[256];
	pid_t pid;
	स्थिर अक्षर *test_name = "pidfd_send_signal signal exited process";

	अगर (!have_pidfd_send_संकेत) अणु
		ksft_test_result_skip(
			"%s test: pidfd_send_signal() syscall not supported\n",
			test_name);
		वापस 0;
	पूर्ण

	pid = विभाजन();
	अगर (pid < 0)
		ksft_निकास_fail_msg("%s test: Failed to create new process\n",
				   test_name);

	अगर (pid == 0)
		_निकास(निकास_सफल);

	snम_लिखो(buf, माप(buf), "/proc/%d", pid);

	pidfd = खोलो(buf, O_सूचीECTORY | O_CLOEXEC);

	(व्योम)रुको_क्रम_pid(pid);

	अगर (pidfd < 0)
		ksft_निकास_fail_msg(
			"%s test: Failed to open process file descriptor\n",
			test_name);

	ret = sys_pidfd_send_संकेत(pidfd, 0, शून्य, 0);
	saved_त्रुटि_सं = त्रुटि_सं;
	बंद(pidfd);
	अगर (ret == 0)
		ksft_निकास_fail_msg(
			"%s test: Managed to send signal to process even though it should have failed\n",
			test_name);

	अगर (saved_त्रुटि_सं != ESRCH)
		ksft_निकास_fail_msg(
			"%s test: Expected to receive ESRCH as errno value but received %d instead\n",
			test_name, saved_त्रुटि_सं);

	ksft_test_result_pass("%s test: Failed to send signal as expected\n",
			      test_name);
	वापस 0;
पूर्ण

/*
 * Maximum number of cycles we allow. This is equivalent to PID_MAX_DEFAULT.
 * If users set a higher limit or we have cycled PIDFD_MAX_DEFAULT number of
 * बार then we skip the test to not go पूर्णांकo an infinite loop or block क्रम a
 * दीर्घ समय.
 */
#घोषणा PIDFD_MAX_DEFAULT 0x8000

अटल पूर्णांक test_pidfd_send_संकेत_recycled_pid_fail(व्योम)
अणु
	पूर्णांक i, ret;
	pid_t pid1;
	स्थिर अक्षर *test_name = "pidfd_send_signal signal recycled pid";

	अगर (!have_pidfd_send_संकेत) अणु
		ksft_test_result_skip(
			"%s test: pidfd_send_signal() syscall not supported\n",
			test_name);
		वापस 0;
	पूर्ण

	ret = unshare(CLONE_NEWPID);
	अगर (ret < 0) अणु
		अगर (त्रुटि_सं == EPERM) अणु
			ksft_test_result_skip("%s test: Unsharing pid namespace not permitted\n",
					      test_name);
			वापस 0;
		पूर्ण
		ksft_निकास_fail_msg("%s test: Failed to unshare pid namespace\n",
				   test_name);
	पूर्ण

	ret = unshare(CLONE_NEWNS);
	अगर (ret < 0) अणु
		अगर (त्रुटि_सं == EPERM) अणु
			ksft_test_result_skip("%s test: Unsharing mount namespace not permitted\n",
					      test_name);
			वापस 0;
		पूर्ण
		ksft_निकास_fail_msg("%s test: Failed to unshare mount namespace\n",
				   test_name);
	पूर्ण

	ret = mount(शून्य, "/", शून्य, MS_REC | MS_PRIVATE, 0);
	अगर (ret < 0)
		ksft_निकास_fail_msg("%s test: Failed to remount / private\n",
				   test_name);

	/* pid 1 in new pid namespace */
	pid1 = विभाजन();
	अगर (pid1 < 0)
		ksft_निकास_fail_msg("%s test: Failed to create new process\n",
				   test_name);

	अगर (pid1 == 0) अणु
		अक्षर buf[256];
		pid_t pid2;
		पूर्णांक pidfd = -1;

		(व्योम)umount2("/proc", MNT_DETACH);
		ret = mount("proc", "/proc", "proc", 0, शून्य);
		अगर (ret < 0)
			_निकास(PIDFD_ERROR);

		/* grab pid PID_RECYCLE */
		क्रम (i = 0; i <= PIDFD_MAX_DEFAULT; i++) अणु
			pid2 = विभाजन();
			अगर (pid2 < 0)
				_निकास(PIDFD_ERROR);

			अगर (pid2 == 0)
				_निकास(PIDFD_PASS);

			अगर (pid2 == PID_RECYCLE) अणु
				snम_लिखो(buf, माप(buf), "/proc/%d", pid2);
				ksft_prपूर्णांक_msg("pid to recycle is %d\n", pid2);
				pidfd = खोलो(buf, O_सूचीECTORY | O_CLOEXEC);
			पूर्ण

			अगर (रुको_क्रम_pid(pid2))
				_निकास(PIDFD_ERROR);

			अगर (pid2 >= PID_RECYCLE)
				अवरोध;
		पूर्ण

		/*
		 * We want to be as predictable as we can so अगर we haven't been
		 * able to grab pid PID_RECYCLE skip the test.
		 */
		अगर (pid2 != PID_RECYCLE) अणु
			/* skip test */
			बंद(pidfd);
			_निकास(PIDFD_SKIP);
		पूर्ण

		अगर (pidfd < 0)
			_निकास(PIDFD_ERROR);

		क्रम (i = 0; i <= PIDFD_MAX_DEFAULT; i++) अणु
			अक्षर c;
			पूर्णांक pipe_fds[2];
			pid_t recycled_pid;
			पूर्णांक child_ret = PIDFD_PASS;

			ret = pipe2(pipe_fds, O_CLOEXEC);
			अगर (ret < 0)
				_निकास(PIDFD_ERROR);

			recycled_pid = विभाजन();
			अगर (recycled_pid < 0)
				_निकास(PIDFD_ERROR);

			अगर (recycled_pid == 0) अणु
				बंद(pipe_fds[1]);
				(व्योम)पढ़ो(pipe_fds[0], &c, 1);
				बंद(pipe_fds[0]);

				_निकास(PIDFD_PASS);
			पूर्ण

			/*
			 * Stop the child so we can inspect whether we have
			 * recycled pid PID_RECYCLE.
			 */
			बंद(pipe_fds[0]);
			ret = समाप्त(recycled_pid, SIGSTOP);
			बंद(pipe_fds[1]);
			अगर (ret) अणु
				(व्योम)रुको_क्रम_pid(recycled_pid);
				_निकास(PIDFD_ERROR);
			पूर्ण

			/*
			 * We have recycled the pid. Try to संकेत it. This
			 * needs to fail since this is a dअगरferent process than
			 * the one the pidfd refers to.
			 */
			अगर (recycled_pid == PID_RECYCLE) अणु
				ret = sys_pidfd_send_संकेत(pidfd, SIGCONT,
							    शून्य, 0);
				अगर (ret && त्रुटि_सं == ESRCH)
					child_ret = PIDFD_XFAIL;
				अन्यथा
					child_ret = PIDFD_FAIL;
			पूर्ण

			/* let the process move on */
			ret = समाप्त(recycled_pid, SIGCONT);
			अगर (ret)
				(व्योम)समाप्त(recycled_pid, SIGKILL);

			अगर (रुको_क्रम_pid(recycled_pid))
				_निकास(PIDFD_ERROR);

			चयन (child_ret) अणु
			हाल PIDFD_FAIL:
				/* fallthrough */
			हाल PIDFD_XFAIL:
				_निकास(child_ret);
			हाल PIDFD_PASS:
				अवरोध;
			शेष:
				/* not reached */
				_निकास(PIDFD_ERROR);
			पूर्ण

			/*
			 * If the user set a custom pid_max limit we could be
			 * in the millions.
			 * Skip the test in this हाल.
			 */
			अगर (recycled_pid > PIDFD_MAX_DEFAULT)
				_निकास(PIDFD_SKIP);
		पूर्ण

		/* failed to recycle pid */
		_निकास(PIDFD_SKIP);
	पूर्ण

	ret = रुको_क्रम_pid(pid1);
	चयन (ret) अणु
	हाल PIDFD_FAIL:
		ksft_निकास_fail_msg(
			"%s test: Managed to signal recycled pid %d\n",
			test_name, PID_RECYCLE);
	हाल PIDFD_PASS:
		ksft_निकास_fail_msg("%s test: Failed to recycle pid %d\n",
				   test_name, PID_RECYCLE);
	हाल PIDFD_SKIP:
		ksft_test_result_skip("%s test: Skipping test\n", test_name);
		ret = 0;
		अवरोध;
	हाल PIDFD_XFAIL:
		ksft_test_result_pass(
			"%s test: Failed to signal recycled pid as expected\n",
			test_name);
		ret = 0;
		अवरोध;
	शेष /* PIDFD_ERROR */:
		ksft_निकास_fail_msg("%s test: Error while running tests\n",
				   test_name);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक test_pidfd_send_संकेत_syscall_support(व्योम)
अणु
	पूर्णांक pidfd, ret;
	स्थिर अक्षर *test_name = "pidfd_send_signal check for support";

	pidfd = खोलो("/proc/self", O_सूचीECTORY | O_CLOEXEC);
	अगर (pidfd < 0)
		ksft_निकास_fail_msg(
			"%s test: Failed to open process file descriptor\n",
			test_name);

	ret = sys_pidfd_send_संकेत(pidfd, 0, शून्य, 0);
	अगर (ret < 0) अणु
		अगर (त्रुटि_सं == ENOSYS) अणु
			ksft_test_result_skip(
				"%s test: pidfd_send_signal() syscall not supported\n",
				test_name);
			वापस 0;
		पूर्ण
		ksft_निकास_fail_msg("%s test: Failed to send signal\n",
				   test_name);
	पूर्ण

	have_pidfd_send_संकेत = true;
	बंद(pidfd);
	ksft_test_result_pass(
		"%s test: pidfd_send_signal() syscall is supported. Tests can be executed\n",
		test_name);
	वापस 0;
पूर्ण

अटल व्योम *test_pidfd_poll_exec_thपढ़ो(व्योम *priv)
अणु
	ksft_prपूर्णांक_msg("Child Thread: starting. pid %d tid %d ; and sleeping\n",
			getpid(), syscall(SYS_gettid));
	ksft_prपूर्णांक_msg("Child Thread: doing exec of sleep\n");

	execl("/bin/sleep", "sleep", str(CHILD_THREAD_MIN_WAIT), (अक्षर *)शून्य);

	ksft_prपूर्णांक_msg("Child Thread: DONE. pid %d tid %d\n",
			getpid(), syscall(SYS_gettid));
	वापस शून्य;
पूर्ण

अटल व्योम poll_pidfd(स्थिर अक्षर *test_name, पूर्णांक pidfd)
अणु
	पूर्णांक c;
	पूर्णांक epoll_fd = epoll_create1(EPOLL_CLOEXEC);
	काष्ठा epoll_event event, events[MAX_EVENTS];

	अगर (epoll_fd == -1)
		ksft_निकास_fail_msg("%s test: Failed to create epoll file descriptor "
				   "(errno %d)\n",
				   test_name, त्रुटि_सं);

	event.events = EPOLLIN;
	event.data.fd = pidfd;

	अगर (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, pidfd, &event)) अणु
		ksft_निकास_fail_msg("%s test: Failed to add epoll file descriptor "
				   "(errno %d)\n",
				   test_name, त्रुटि_सं);
	पूर्ण

	c = epoll_रुको(epoll_fd, events, MAX_EVENTS, 5000);
	अगर (c != 1 || !(events[0].events & EPOLLIN))
		ksft_निकास_fail_msg("%s test: Unexpected epoll_wait result (c=%d, events=%x) ",
				   "(errno %d)\n",
				   test_name, c, events[0].events, त्रुटि_सं);

	बंद(epoll_fd);
	वापस;

पूर्ण

अटल पूर्णांक child_poll_exec_test(व्योम *args)
अणु
	pthपढ़ो_t t1;

	ksft_prपूर्णांक_msg("Child (pidfd): starting. pid %d tid %d\n", getpid(),
			syscall(SYS_gettid));
	pthपढ़ो_create(&t1, शून्य, test_pidfd_poll_exec_thपढ़ो, शून्य);
	/*
	 * Exec in the non-leader thपढ़ो will destroy the leader immediately.
	 * If the रुको in the parent वापसs too soon, the test fails.
	 */
	जबतक (1)
		sleep(1);
पूर्ण

अटल व्योम test_pidfd_poll_exec(पूर्णांक use_रुकोpid)
अणु
	पूर्णांक pid, pidfd = 0;
	पूर्णांक status, ret;
	pthपढ़ो_t t1;
	समय_प्रकार prog_start = समय(शून्य);
	स्थिर अक्षर *test_name = "pidfd_poll check for premature notification on child thread exec";

	ksft_prपूर्णांक_msg("Parent: pid: %d\n", getpid());
	pid = pidfd_clone(CLONE_PIDFD, &pidfd, child_poll_exec_test);
	अगर (pid < 0)
		ksft_निकास_fail_msg("%s test: pidfd_clone failed (ret %d, errno %d)\n",
				   test_name, pid, त्रुटि_सं);

	ksft_prपूर्णांक_msg("Parent: Waiting for Child (%d) to complete.\n", pid);

	अगर (use_रुकोpid) अणु
		ret = रुकोpid(pid, &status, 0);
		अगर (ret == -1)
			ksft_prपूर्णांक_msg("Parent: error\n");

		अगर (ret == pid)
			ksft_prपूर्णांक_msg("Parent: Child process waited for.\n");
	पूर्ण अन्यथा अणु
		poll_pidfd(test_name, pidfd);
	पूर्ण

	समय_प्रकार prog_समय = समय(शून्य) - prog_start;

	ksft_prपूर्णांक_msg("Time waited for child: %lu\n", prog_समय);

	बंद(pidfd);

	अगर (prog_समय < CHILD_THREAD_MIN_WAIT || prog_समय > CHILD_THREAD_MIN_WAIT + 2)
		ksft_निकास_fail_msg("%s test: Failed\n", test_name);
	अन्यथा
		ksft_test_result_pass("%s test: Passed\n", test_name);
पूर्ण

अटल व्योम *test_pidfd_poll_leader_निकास_thपढ़ो(व्योम *priv)
अणु
	ksft_prपूर्णांक_msg("Child Thread: starting. pid %d tid %d ; and sleeping\n",
			getpid(), syscall(SYS_gettid));
	sleep(CHILD_THREAD_MIN_WAIT);
	ksft_prपूर्णांक_msg("Child Thread: DONE. pid %d tid %d\n", getpid(), syscall(SYS_gettid));
	वापस शून्य;
पूर्ण

अटल समय_प्रकार *child_निकास_secs;
अटल पूर्णांक child_poll_leader_निकास_test(व्योम *args)
अणु
	pthपढ़ो_t t1, t2;

	ksft_prपूर्णांक_msg("Child: starting. pid %d tid %d\n", getpid(), syscall(SYS_gettid));
	pthपढ़ो_create(&t1, शून्य, test_pidfd_poll_leader_निकास_thपढ़ो, शून्य);
	pthपढ़ो_create(&t2, शून्य, test_pidfd_poll_leader_निकास_thपढ़ो, शून्य);

	/*
	 * glibc निकास calls निकास_group syscall, so explicity call निकास only
	 * so that only the group leader निकासs, leaving the thपढ़ोs alone.
	 */
	*child_निकास_secs = समय(शून्य);
	syscall(SYS_निकास, 0);
पूर्ण

अटल व्योम test_pidfd_poll_leader_निकास(पूर्णांक use_रुकोpid)
अणु
	पूर्णांक pid, pidfd = 0;
	पूर्णांक status, ret;
	समय_प्रकार prog_start = समय(शून्य);
	स्थिर अक्षर *test_name = "pidfd_poll check for premature notification on non-empty"
				"group leader exit";

	child_निकास_secs = mmap(शून्य, माप *child_निकास_secs, PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	अगर (child_निकास_secs == MAP_FAILED)
		ksft_निकास_fail_msg("%s test: mmap failed (errno %d)\n",
				   test_name, त्रुटि_सं);

	ksft_prपूर्णांक_msg("Parent: pid: %d\n", getpid());
	pid = pidfd_clone(CLONE_PIDFD, &pidfd, child_poll_leader_निकास_test);
	अगर (pid < 0)
		ksft_निकास_fail_msg("%s test: pidfd_clone failed (ret %d, errno %d)\n",
				   test_name, pid, त्रुटि_सं);

	ksft_prपूर्णांक_msg("Parent: Waiting for Child (%d) to complete.\n", pid);

	अगर (use_रुकोpid) अणु
		ret = रुकोpid(pid, &status, 0);
		अगर (ret == -1)
			ksft_prपूर्णांक_msg("Parent: error\n");
	पूर्ण अन्यथा अणु
		/*
		 * This sleep tests क्रम the हाल where अगर the child निकासs, and is in
		 * EXIT_ZOMBIE, but the thपढ़ो group leader is non-empty, then the poll
		 * करोesn't prematurely वापस even though there are active thपढ़ोs
		 */
		sleep(1);
		poll_pidfd(test_name, pidfd);
	पूर्ण

	अगर (ret == pid)
		ksft_prपूर्णांक_msg("Parent: Child process waited for.\n");

	समय_प्रकार since_child_निकास = समय(शून्य) - *child_निकास_secs;

	ksft_prपूर्णांक_msg("Time since child exit: %lu\n", since_child_निकास);

	बंद(pidfd);

	अगर (since_child_निकास < CHILD_THREAD_MIN_WAIT ||
			since_child_निकास > CHILD_THREAD_MIN_WAIT + 2)
		ksft_निकास_fail_msg("%s test: Failed\n", test_name);
	अन्यथा
		ksft_test_result_pass("%s test: Passed\n", test_name);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	ksft_prपूर्णांक_header();
	ksft_set_plan(8);

	test_pidfd_poll_exec(0);
	test_pidfd_poll_exec(1);
	test_pidfd_poll_leader_निकास(0);
	test_pidfd_poll_leader_निकास(1);
	test_pidfd_send_संकेत_syscall_support();
	test_pidfd_send_संकेत_simple_success();
	test_pidfd_send_संकेत_निकासed_fail();
	test_pidfd_send_संकेत_recycled_pid_fail();

	वापस ksft_निकास_pass();
पूर्ण
