<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <संकेत.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sched.h>
#समावेश <माला.स>
#समावेश <sys/resource.h>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

#समावेश "pidfd.h"
#समावेश "../kselftest_harness.h"

#घोषणा ptr_to_u64(ptr) ((__u64)((uपूर्णांकptr_t)(ptr)))

/* Attempt to de-conflict with the selftests tree. */
#अगर_अघोषित SKIP
#घोषणा SKIP(s, ...)	XFAIL(s, ##__VA_ARGS__)
#पूर्ण_अगर

अटल pid_t sys_clone3(काष्ठा clone_args *args)
अणु
	वापस syscall(__NR_clone3, args, माप(काष्ठा clone_args));
पूर्ण

अटल पूर्णांक sys_रुकोid(पूर्णांक which, pid_t pid, siginfo_t *info, पूर्णांक options,
		      काष्ठा rusage *ru)
अणु
	वापस syscall(__NR_रुकोid, which, pid, info, options, ru);
पूर्ण

TEST(रुको_simple)
अणु
	पूर्णांक pidfd = -1, status = 0;
	pid_t parent_tid = -1;
	काष्ठा clone_args args = अणु
		.parent_tid = ptr_to_u64(&parent_tid),
		.pidfd = ptr_to_u64(&pidfd),
		.flags = CLONE_PIDFD | CLONE_PARENT_SETTID,
		.निकास_संकेत = SIGCHLD,
	पूर्ण;
	पूर्णांक ret;
	pid_t pid;
	siginfo_t info = अणु
		.si_signo = 0,
	पूर्ण;

	pidfd = खोलो("/proc/self", O_सूचीECTORY | O_RDONLY | O_CLOEXEC);
	ASSERT_GE(pidfd, 0);

	pid = sys_रुकोid(P_PIDFD, pidfd, &info, WEXITED, शून्य);
	ASSERT_NE(pid, 0);
	EXPECT_EQ(बंद(pidfd), 0);
	pidfd = -1;

	pidfd = खोलो("/dev/null", O_RDONLY | O_CLOEXEC);
	ASSERT_GE(pidfd, 0);

	pid = sys_रुकोid(P_PIDFD, pidfd, &info, WEXITED, शून्य);
	ASSERT_NE(pid, 0);
	EXPECT_EQ(बंद(pidfd), 0);
	pidfd = -1;

	pid = sys_clone3(&args);
	ASSERT_GE(pid, 0);

	अगर (pid == 0)
		निकास(निकास_सफल);

	pid = sys_रुकोid(P_PIDFD, pidfd, &info, WEXITED, शून्य);
	ASSERT_GE(pid, 0);
	ASSERT_EQ(WIFEXITED(info.si_status), true);
	ASSERT_EQ(WEXITSTATUS(info.si_status), 0);
	EXPECT_EQ(बंद(pidfd), 0);

	ASSERT_EQ(info.si_signo, SIGCHLD);
	ASSERT_EQ(info.si_code, CLD_EXITED);
	ASSERT_EQ(info.si_pid, parent_tid);
पूर्ण

TEST(रुको_states)
अणु
	पूर्णांक pidfd = -1, status = 0;
	pid_t parent_tid = -1;
	काष्ठा clone_args args = अणु
		.parent_tid = ptr_to_u64(&parent_tid),
		.pidfd = ptr_to_u64(&pidfd),
		.flags = CLONE_PIDFD | CLONE_PARENT_SETTID,
		.निकास_संकेत = SIGCHLD,
	पूर्ण;
	पूर्णांक ret;
	pid_t pid;
	siginfo_t info = अणु
		.si_signo = 0,
	पूर्ण;

	pid = sys_clone3(&args);
	ASSERT_GE(pid, 0);

	अगर (pid == 0) अणु
		समाप्त(getpid(), SIGSTOP);
		समाप्त(getpid(), SIGSTOP);
		निकास(निकास_सफल);
	पूर्ण

	ASSERT_EQ(sys_रुकोid(P_PIDFD, pidfd, &info, WSTOPPED, शून्य), 0);
	ASSERT_EQ(info.si_signo, SIGCHLD);
	ASSERT_EQ(info.si_code, CLD_STOPPED);
	ASSERT_EQ(info.si_pid, parent_tid);

	ASSERT_EQ(sys_pidfd_send_संकेत(pidfd, SIGCONT, शून्य, 0), 0);

	ASSERT_EQ(sys_रुकोid(P_PIDFD, pidfd, &info, WCONTINUED, शून्य), 0);
	ASSERT_EQ(info.si_signo, SIGCHLD);
	ASSERT_EQ(info.si_code, CLD_CONTINUED);
	ASSERT_EQ(info.si_pid, parent_tid);

	ASSERT_EQ(sys_रुकोid(P_PIDFD, pidfd, &info, WUNTRACED, शून्य), 0);
	ASSERT_EQ(info.si_signo, SIGCHLD);
	ASSERT_EQ(info.si_code, CLD_STOPPED);
	ASSERT_EQ(info.si_pid, parent_tid);

	ASSERT_EQ(sys_pidfd_send_संकेत(pidfd, SIGKILL, शून्य, 0), 0);

	ASSERT_EQ(sys_रुकोid(P_PIDFD, pidfd, &info, WEXITED, शून्य), 0);
	ASSERT_EQ(info.si_signo, SIGCHLD);
	ASSERT_EQ(info.si_code, CLD_KILLED);
	ASSERT_EQ(info.si_pid, parent_tid);

	EXPECT_EQ(बंद(pidfd), 0);
पूर्ण

TEST(रुको_nonblock)
अणु
	पूर्णांक pidfd, status = 0;
	अचिन्हित पूर्णांक flags = 0;
	pid_t parent_tid = -1;
	काष्ठा clone_args args = अणु
		.parent_tid = ptr_to_u64(&parent_tid),
		.flags = CLONE_PARENT_SETTID,
		.निकास_संकेत = SIGCHLD,
	पूर्ण;
	पूर्णांक ret;
	pid_t pid;
	siginfo_t info = अणु
		.si_signo = 0,
	पूर्ण;

	/*
	 * Callers need to see ECHILD with non-blocking pidfds when no child
	 * processes exists.
	 */
	pidfd = sys_pidfd_खोलो(getpid(), PIDFD_NONBLOCK);
	EXPECT_GE(pidfd, 0) अणु
		/* pidfd_खोलो() करोesn't support PIDFD_NONBLOCK. */
		ASSERT_EQ(त्रुटि_सं, EINVAL);
		SKIP(वापस, "Skipping PIDFD_NONBLOCK test");
	पूर्ण

	ret = sys_रुकोid(P_PIDFD, pidfd, &info, WEXITED, शून्य);
	ASSERT_LT(ret, 0);
	ASSERT_EQ(त्रुटि_सं, ECHILD);
	EXPECT_EQ(बंद(pidfd), 0);

	pid = sys_clone3(&args);
	ASSERT_GE(pid, 0);

	अगर (pid == 0) अणु
		समाप्त(getpid(), SIGSTOP);
		निकास(निकास_सफल);
	पूर्ण

	pidfd = sys_pidfd_खोलो(pid, PIDFD_NONBLOCK);
	EXPECT_GE(pidfd, 0) अणु
		/* pidfd_खोलो() करोesn't support PIDFD_NONBLOCK. */
		ASSERT_EQ(त्रुटि_सं, EINVAL);
		SKIP(वापस, "Skipping PIDFD_NONBLOCK test");
	पूर्ण

	flags = fcntl(pidfd, F_GETFL, 0);
	ASSERT_GT(flags, 0);
	ASSERT_GT((flags & O_NONBLOCK), 0);

	/*
	 * Callers need to see EAGAIN/EWOULDBLOCK with non-blocking pidfd when
	 * child processes exist but none have निकासed.
	 */
	ret = sys_रुकोid(P_PIDFD, pidfd, &info, WEXITED, शून्य);
	ASSERT_LT(ret, 0);
	ASSERT_EQ(त्रुटि_सं, EAGAIN);

	/*
	 * Callers need to जारी seeing 0 with non-blocking pidfd and
	 * WNOHANG उठाओd explicitly when child processes exist but none have
	 * निकासed.
	 */
	ret = sys_रुकोid(P_PIDFD, pidfd, &info, WEXITED | WNOHANG, शून्य);
	ASSERT_EQ(ret, 0);

	ASSERT_EQ(fcntl(pidfd, F_SETFL, (flags & ~O_NONBLOCK)), 0);

	ASSERT_EQ(sys_रुकोid(P_PIDFD, pidfd, &info, WSTOPPED, शून्य), 0);
	ASSERT_EQ(info.si_signo, SIGCHLD);
	ASSERT_EQ(info.si_code, CLD_STOPPED);
	ASSERT_EQ(info.si_pid, parent_tid);

	ASSERT_EQ(sys_pidfd_send_संकेत(pidfd, SIGCONT, शून्य, 0), 0);

	ASSERT_EQ(sys_रुकोid(P_PIDFD, pidfd, &info, WEXITED, शून्य), 0);
	ASSERT_EQ(info.si_signo, SIGCHLD);
	ASSERT_EQ(info.si_code, CLD_EXITED);
	ASSERT_EQ(info.si_pid, parent_tid);

	EXPECT_EQ(बंद(pidfd), 0);
पूर्ण

TEST_HARNESS_MAIN
