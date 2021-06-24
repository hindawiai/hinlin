<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test क्रम हटाओ_on_exec.
 *
 * Copyright (C) 2021, Google LLC.
 */

#घोषणा _GNU_SOURCE

/* We need the latest siginfo from the kernel repo. */
#समावेश <sys/types.h>
#समावेश <यंत्र/siginfo.h>
#घोषणा __have_siginfo_t 1
#घोषणा __have_sigval_t 1
#घोषणा __have_sigevent_t 1
#घोषणा __siginfo_t_defined
#घोषणा __sigval_t_defined
#घोषणा __sigevent_t_defined
#घोषणा _BITS_SIGINFO_CONSTS_H 1
#घोषणा _BITS_SIGEVENT_CONSTS_H 1

#समावेश <stdbool.h>
#समावेश <मानकघोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <linux/perf_event.h>
#समावेश <pthपढ़ो.h>
#समावेश <संकेत.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/syscall.h>
#समावेश <unistd.h>

#समावेश "../kselftest_harness.h"

अटल अस्थिर पूर्णांक संकेत_count;

अटल काष्ठा perf_event_attr make_event_attr(व्योम)
अणु
	काष्ठा perf_event_attr attr = अणु
		.type		= PERF_TYPE_HARDWARE,
		.size		= माप(attr),
		.config		= PERF_COUNT_HW_INSTRUCTIONS,
		.sample_period	= 1000,
		.exclude_kernel = 1,
		.exclude_hv	= 1,
		.disabled	= 1,
		.inherit	= 1,
		/*
		 * Children normally retain their inherited event on exec; with
		 * हटाओ_on_exec, we'll हटाओ their event, but the parent and
		 * any other non-exec'd children will keep their events.
		 */
		.हटाओ_on_exec = 1,
		.sigtrap	= 1,
	पूर्ण;
	वापस attr;
पूर्ण

अटल व्योम sigtrap_handler(पूर्णांक signum, siginfo_t *info, व्योम *ucontext)
अणु
	अगर (info->si_code != TRAP_PERF) अणु
		ख_लिखो(मानक_त्रुटि, "%s: unexpected si_code %d\n", __func__, info->si_code);
		वापस;
	पूर्ण

	संकेत_count++;
पूर्ण

FIXTURE(हटाओ_on_exec)
अणु
	काष्ठा sigaction oldact;
	पूर्णांक fd;
पूर्ण;

FIXTURE_SETUP(हटाओ_on_exec)
अणु
	काष्ठा perf_event_attr attr = make_event_attr();
	काष्ठा sigaction action = अणुपूर्ण;

	संकेत_count = 0;

	/* Initialize sigtrap handler. */
	action.sa_flags = SA_SIGINFO | SA_NODEFER;
	action.sa_sigaction = sigtrap_handler;
	sigemptyset(&action.sa_mask);
	ASSERT_EQ(sigaction(SIGTRAP, &action, &self->oldact), 0);

	/* Initialize perf event. */
	self->fd = syscall(__NR_perf_event_खोलो, &attr, 0, -1, -1, PERF_FLAG_FD_CLOEXEC);
	ASSERT_NE(self->fd, -1);
पूर्ण

FIXTURE_TEARDOWN(हटाओ_on_exec)
अणु
	बंद(self->fd);
	sigaction(SIGTRAP, &self->oldact, शून्य);
पूर्ण

/* Verअगरy event propagates to विभाजन'd child. */
TEST_F(हटाओ_on_exec, विभाजन_only)
अणु
	पूर्णांक status;
	pid_t pid = विभाजन();

	अगर (pid == 0) अणु
		ASSERT_EQ(संकेत_count, 0);
		ASSERT_EQ(ioctl(self->fd, PERF_EVENT_IOC_ENABLE, 0), 0);
		जबतक (!संकेत_count);
		_निकास(42);
	पूर्ण

	जबतक (!संकेत_count); /* Child enables event. */
	EXPECT_EQ(रुकोpid(pid, &status, 0), pid);
	EXPECT_EQ(WEXITSTATUS(status), 42);
पूर्ण

/*
 * Verअगरy that event करोes _not_ propagate to विभाजन+exec'd child; event enabled
 * after विभाजन+exec.
 */
TEST_F(हटाओ_on_exec, विभाजन_exec_then_enable)
अणु
	pid_t pid_exec, pid_only_विभाजन;
	पूर्णांक pipefd[2];
	पूर्णांक पंचांगp;

	/*
	 * Non-exec child, to ensure exec करोes not affect inherited events of
	 * other children.
	 */
	pid_only_विभाजन = विभाजन();
	अगर (pid_only_विभाजन == 0) अणु
		/* Block until parent enables event. */
		जबतक (!संकेत_count);
		_निकास(42);
	पूर्ण

	ASSERT_NE(pipe(pipefd), -1);
	pid_exec = विभाजन();
	अगर (pid_exec == 0) अणु
		ASSERT_NE(dup2(pipefd[1], STDOUT_खाताNO), -1);
		बंद(pipefd[0]);
		execl("/proc/self/exe", "exec_child", शून्य);
		_निकास((लिखो_त्रुटि("exec failed"), 1));
	पूर्ण
	बंद(pipefd[1]);

	ASSERT_EQ(रुकोpid(pid_exec, &पंचांगp, WNOHANG), 0); /* Child is running. */
	/* Wait क्रम exec'd child to start spinning. */
	EXPECT_EQ(पढ़ो(pipefd[0], &पंचांगp, माप(पूर्णांक)), माप(पूर्णांक));
	EXPECT_EQ(पंचांगp, 42);
	बंद(pipefd[0]);
	/* Now we can enable the event, knowing the child is करोing work. */
	EXPECT_EQ(ioctl(self->fd, PERF_EVENT_IOC_ENABLE, 0), 0);
	/* If the event propagated to the exec'd child, it will निकास normally... */
	usleep(100000); /* ... give समय क्रम event to trigger (in हाल of bug). */
	EXPECT_EQ(रुकोpid(pid_exec, &पंचांगp, WNOHANG), 0); /* Should still be running. */
	EXPECT_EQ(समाप्त(pid_exec, SIGKILL), 0);

	/* Verअगरy removal from child did not affect this task's event. */
	पंचांगp = संकेत_count;
	जबतक (संकेत_count == पंचांगp); /* Should not hang! */
	/* Nor should it have affected the first child. */
	EXPECT_EQ(रुकोpid(pid_only_विभाजन, &पंचांगp, 0), pid_only_विभाजन);
	EXPECT_EQ(WEXITSTATUS(पंचांगp), 42);
पूर्ण

/*
 * Verअगरy that event करोes _not_ propagate to विभाजन+exec'd child; event enabled
 * beक्रमe विभाजन+exec.
 */
TEST_F(हटाओ_on_exec, enable_then_विभाजन_exec)
अणु
	pid_t pid_exec;
	पूर्णांक पंचांगp;

	EXPECT_EQ(ioctl(self->fd, PERF_EVENT_IOC_ENABLE, 0), 0);

	pid_exec = विभाजन();
	अगर (pid_exec == 0) अणु
		execl("/proc/self/exe", "exec_child", शून्य);
		_निकास((लिखो_त्रुटि("exec failed"), 1));
	पूर्ण

	/*
	 * The child may निकास abnormally at any समय अगर the event propagated and
	 * a SIGTRAP is sent beक्रमe the handler was set up.
	 */
	usleep(100000); /* ... give समय क्रम event to trigger (in हाल of bug). */
	EXPECT_EQ(रुकोpid(pid_exec, &पंचांगp, WNOHANG), 0); /* Should still be running. */
	EXPECT_EQ(समाप्त(pid_exec, SIGKILL), 0);

	/* Verअगरy removal from child did not affect this task's event. */
	पंचांगp = संकेत_count;
	जबतक (संकेत_count == पंचांगp); /* Should not hang! */
पूर्ण

TEST_F(हटाओ_on_exec, exec_stress)
अणु
	pid_t pids[30];
	पूर्णांक i, पंचांगp;

	क्रम (i = 0; i < माप(pids) / माप(pids[0]); i++) अणु
		pids[i] = विभाजन();
		अगर (pids[i] == 0) अणु
			execl("/proc/self/exe", "exec_child", शून्य);
			_निकास((लिखो_त्रुटि("exec failed"), 1));
		पूर्ण

		/* Some विभाजनed with event disabled, rest with enabled. */
		अगर (i > 10)
			EXPECT_EQ(ioctl(self->fd, PERF_EVENT_IOC_ENABLE, 0), 0);
	पूर्ण

	usleep(100000); /* ... give समय क्रम event to trigger (in हाल of bug). */

	क्रम (i = 0; i < माप(pids) / माप(pids[0]); i++) अणु
		/* All children should still be running. */
		EXPECT_EQ(रुकोpid(pids[i], &पंचांगp, WNOHANG), 0);
		EXPECT_EQ(समाप्त(pids[i], SIGKILL), 0);
	पूर्ण

	/* Verअगरy event is still alive. */
	पंचांगp = संकेत_count;
	जबतक (संकेत_count == पंचांगp);
पूर्ण

/* For exec'd child. */
अटल व्योम exec_child(व्योम)
अणु
	काष्ठा sigaction action = अणुपूर्ण;
	स्थिर पूर्णांक val = 42;

	/* Set up sigtrap handler in हाल we erroneously receive a trap. */
	action.sa_flags = SA_SIGINFO | SA_NODEFER;
	action.sa_sigaction = sigtrap_handler;
	sigemptyset(&action.sa_mask);
	अगर (sigaction(SIGTRAP, &action, शून्य))
		_निकास((लिखो_त्रुटि("sigaction failed"), 1));

	/* Signal parent that we're starting to spin. */
	अगर (ग_लिखो(STDOUT_खाताNO, &val, माप(पूर्णांक)) == -1)
		_निकास((लिखो_त्रुटि("write failed"), 1));

	/* Should hang here until समाप्तed. */
	जबतक (!संकेत_count);
पूर्ण

#घोषणा मुख्य test_मुख्य
TEST_HARNESS_MAIN
#अघोषित मुख्य
पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अगर (!म_भेद(argv[0], "exec_child")) अणु
		exec_child();
		वापस 1;
	पूर्ण

	वापस test_मुख्य(argc, argv);
पूर्ण
