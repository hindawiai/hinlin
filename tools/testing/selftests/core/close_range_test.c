<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <linux/kernel.h>
#समावेश <सीमा.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <syscall.h>
#समावेश <unistd.h>
#समावेश <sys/resource.h>

#समावेश "../kselftest_harness.h"
#समावेश "../clone3/clone3_selftests.h"

#अगर_अघोषित __NR_बंद_range
	#अगर defined __alpha__
		#घोषणा __NR_बंद_range 546
	#या_अगर defined _MIPS_SIM
		#अगर _MIPS_SIM == _MIPS_SIM_ABI32	/* o32 */
			#घोषणा __NR_बंद_range (436 + 4000)
		#पूर्ण_अगर
		#अगर _MIPS_SIM == _MIPS_SIM_NABI32	/* n32 */
			#घोषणा __NR_बंद_range (436 + 6000)
		#पूर्ण_अगर
		#अगर _MIPS_SIM == _MIPS_SIM_ABI64	/* n64 */
			#घोषणा __NR_बंद_range (436 + 5000)
		#पूर्ण_अगर
	#या_अगर defined __ia64__
		#घोषणा __NR_बंद_range (436 + 1024)
	#अन्यथा
		#घोषणा __NR_बंद_range 436
	#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित CLOSE_RANGE_UNSHARE
#घोषणा CLOSE_RANGE_UNSHARE	(1U << 1)
#पूर्ण_अगर

#अगर_अघोषित CLOSE_RANGE_CLOEXEC
#घोषणा CLOSE_RANGE_CLOEXEC	(1U << 2)
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक sys_बंद_range(अचिन्हित पूर्णांक fd, अचिन्हित पूर्णांक max_fd,
				  अचिन्हित पूर्णांक flags)
अणु
	वापस syscall(__NR_बंद_range, fd, max_fd, flags);
पूर्ण

#अगर_अघोषित ARRAY_SIZE
#घोषणा ARRAY_SIZE(x) (माप(x) / माप((x)[0]))
#पूर्ण_अगर

TEST(बंद_range)
अणु
	पूर्णांक i, ret;
	पूर्णांक खोलो_fds[101];

	क्रम (i = 0; i < ARRAY_SIZE(खोलो_fds); i++) अणु
		पूर्णांक fd;

		fd = खोलो("/dev/null", O_RDONLY | O_CLOEXEC);
		ASSERT_GE(fd, 0) अणु
			अगर (त्रुटि_सं == ENOENT)
				SKIP(वापस, "Skipping test since /dev/null does not exist");
		पूर्ण

		खोलो_fds[i] = fd;
	पूर्ण

	EXPECT_EQ(-1, sys_बंद_range(खोलो_fds[0], खोलो_fds[100], -1)) अणु
		अगर (त्रुटि_सं == ENOSYS)
			SKIP(वापस, "close_range() syscall not supported");
	पूर्ण

	EXPECT_EQ(0, sys_बंद_range(खोलो_fds[0], खोलो_fds[50], 0));

	क्रम (i = 0; i <= 50; i++)
		EXPECT_EQ(-1, fcntl(खोलो_fds[i], F_GETFL));

	क्रम (i = 51; i <= 100; i++)
		EXPECT_GT(fcntl(खोलो_fds[i], F_GETFL), -1);

	/* create a couple of gaps */
	बंद(57);
	बंद(78);
	बंद(81);
	बंद(82);
	बंद(84);
	बंद(90);

	EXPECT_EQ(0, sys_बंद_range(खोलो_fds[51], खोलो_fds[92], 0));

	क्रम (i = 51; i <= 92; i++)
		EXPECT_EQ(-1, fcntl(खोलो_fds[i], F_GETFL));

	क्रम (i = 93; i <= 100; i++)
		EXPECT_GT(fcntl(खोलो_fds[i], F_GETFL), -1);

	/* test that the kernel caps and still बंदs all fds */
	EXPECT_EQ(0, sys_बंद_range(खोलो_fds[93], खोलो_fds[99], 0));

	क्रम (i = 93; i <= 99; i++)
		EXPECT_EQ(-1, fcntl(खोलो_fds[i], F_GETFL));

	EXPECT_GT(fcntl(खोलो_fds[i], F_GETFL), -1);

	EXPECT_EQ(0, sys_बंद_range(खोलो_fds[100], खोलो_fds[100], 0));

	EXPECT_EQ(-1, fcntl(खोलो_fds[100], F_GETFL));
पूर्ण

TEST(बंद_range_unshare)
अणु
	पूर्णांक i, ret, status;
	pid_t pid;
	पूर्णांक खोलो_fds[101];
	काष्ठा __clone_args args = अणु
		.flags = CLONE_खाताS,
		.निकास_संकेत = SIGCHLD,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(खोलो_fds); i++) अणु
		पूर्णांक fd;

		fd = खोलो("/dev/null", O_RDONLY | O_CLOEXEC);
		ASSERT_GE(fd, 0) अणु
			अगर (त्रुटि_सं == ENOENT)
				SKIP(वापस, "Skipping test since /dev/null does not exist");
		पूर्ण

		खोलो_fds[i] = fd;
	पूर्ण

	pid = sys_clone3(&args, माप(args));
	ASSERT_GE(pid, 0);

	अगर (pid == 0) अणु
		ret = sys_बंद_range(खोलो_fds[0], खोलो_fds[50],
				      CLOSE_RANGE_UNSHARE);
		अगर (ret)
			निकास(निकास_त्रुटि);

		क्रम (i = 0; i <= 50; i++)
			अगर (fcntl(खोलो_fds[i], F_GETFL) != -1)
				निकास(निकास_त्रुटि);

		क्रम (i = 51; i <= 100; i++)
			अगर (fcntl(खोलो_fds[i], F_GETFL) == -1)
				निकास(निकास_त्रुटि);

		/* create a couple of gaps */
		बंद(57);
		बंद(78);
		बंद(81);
		बंद(82);
		बंद(84);
		बंद(90);

		ret = sys_बंद_range(खोलो_fds[51], खोलो_fds[92],
				      CLOSE_RANGE_UNSHARE);
		अगर (ret)
			निकास(निकास_त्रुटि);

		क्रम (i = 51; i <= 92; i++)
			अगर (fcntl(खोलो_fds[i], F_GETFL) != -1)
				निकास(निकास_त्रुटि);

		क्रम (i = 93; i <= 100; i++)
			अगर (fcntl(खोलो_fds[i], F_GETFL) == -1)
				निकास(निकास_त्रुटि);

		/* test that the kernel caps and still बंदs all fds */
		ret = sys_बंद_range(खोलो_fds[93], खोलो_fds[99],
				      CLOSE_RANGE_UNSHARE);
		अगर (ret)
			निकास(निकास_त्रुटि);

		क्रम (i = 93; i <= 99; i++)
			अगर (fcntl(खोलो_fds[i], F_GETFL) != -1)
				निकास(निकास_त्रुटि);

		अगर (fcntl(खोलो_fds[100], F_GETFL) == -1)
			निकास(निकास_त्रुटि);

		ret = sys_बंद_range(खोलो_fds[100], खोलो_fds[100],
				      CLOSE_RANGE_UNSHARE);
		अगर (ret)
			निकास(निकास_त्रुटि);

		अगर (fcntl(खोलो_fds[100], F_GETFL) != -1)
			निकास(निकास_त्रुटि);

		निकास(निकास_सफल);
	पूर्ण

	EXPECT_EQ(रुकोpid(pid, &status, 0), pid);
	EXPECT_EQ(true, WIFEXITED(status));
	EXPECT_EQ(0, WEXITSTATUS(status));
पूर्ण

TEST(बंद_range_unshare_capped)
अणु
	पूर्णांक i, ret, status;
	pid_t pid;
	पूर्णांक खोलो_fds[101];
	काष्ठा __clone_args args = अणु
		.flags = CLONE_खाताS,
		.निकास_संकेत = SIGCHLD,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(खोलो_fds); i++) अणु
		पूर्णांक fd;

		fd = खोलो("/dev/null", O_RDONLY | O_CLOEXEC);
		ASSERT_GE(fd, 0) अणु
			अगर (त्रुटि_सं == ENOENT)
				SKIP(वापस, "Skipping test since /dev/null does not exist");
		पूर्ण

		खोलो_fds[i] = fd;
	पूर्ण

	pid = sys_clone3(&args, माप(args));
	ASSERT_GE(pid, 0);

	अगर (pid == 0) अणु
		ret = sys_बंद_range(खोलो_fds[0], अच_पूर्णांक_उच्च,
				      CLOSE_RANGE_UNSHARE);
		अगर (ret)
			निकास(निकास_त्रुटि);

		क्रम (i = 0; i <= 100; i++)
			अगर (fcntl(खोलो_fds[i], F_GETFL) != -1)
				निकास(निकास_त्रुटि);

		निकास(निकास_सफल);
	पूर्ण

	EXPECT_EQ(रुकोpid(pid, &status, 0), pid);
	EXPECT_EQ(true, WIFEXITED(status));
	EXPECT_EQ(0, WEXITSTATUS(status));
पूर्ण

TEST(बंद_range_cloexec)
अणु
	पूर्णांक i, ret;
	पूर्णांक खोलो_fds[101];
	काष्ठा rlimit rlimit;

	क्रम (i = 0; i < ARRAY_SIZE(खोलो_fds); i++) अणु
		पूर्णांक fd;

		fd = खोलो("/dev/null", O_RDONLY);
		ASSERT_GE(fd, 0) अणु
			अगर (त्रुटि_सं == ENOENT)
				SKIP(वापस, "Skipping test since /dev/null does not exist");
		पूर्ण

		खोलो_fds[i] = fd;
	पूर्ण

	ret = sys_बंद_range(1000, 1000, CLOSE_RANGE_CLOEXEC);
	अगर (ret < 0) अणु
		अगर (त्रुटि_सं == ENOSYS)
			SKIP(वापस, "close_range() syscall not supported");
		अगर (त्रुटि_सं == EINVAL)
			SKIP(वापस, "close_range() doesn't support CLOSE_RANGE_CLOEXEC");
	पूर्ण

	/* Ensure the FD_CLOEXEC bit is set also with a resource limit in place.  */
	ASSERT_EQ(0, getrlimit(RLIMIT_NOखाता, &rlimit));
	rlimit.rlim_cur = 25;
	ASSERT_EQ(0, setrlimit(RLIMIT_NOखाता, &rlimit));

	/* Set बंद-on-exec क्रम two ranges: [0-50] and [75-100].  */
	ret = sys_बंद_range(खोलो_fds[0], खोलो_fds[50], CLOSE_RANGE_CLOEXEC);
	ASSERT_EQ(0, ret);
	ret = sys_बंद_range(खोलो_fds[75], खोलो_fds[100], CLOSE_RANGE_CLOEXEC);
	ASSERT_EQ(0, ret);

	क्रम (i = 0; i <= 50; i++) अणु
		पूर्णांक flags = fcntl(खोलो_fds[i], F_GETFD);

		EXPECT_GT(flags, -1);
		EXPECT_EQ(flags & FD_CLOEXEC, FD_CLOEXEC);
	पूर्ण

	क्रम (i = 51; i <= 74; i++) अणु
		पूर्णांक flags = fcntl(खोलो_fds[i], F_GETFD);

		EXPECT_GT(flags, -1);
		EXPECT_EQ(flags & FD_CLOEXEC, 0);
	पूर्ण

	क्रम (i = 75; i <= 100; i++) अणु
		पूर्णांक flags = fcntl(खोलो_fds[i], F_GETFD);

		EXPECT_GT(flags, -1);
		EXPECT_EQ(flags & FD_CLOEXEC, FD_CLOEXEC);
	पूर्ण

	/* Test a common pattern.  */
	ret = sys_बंद_range(3, अच_पूर्णांक_उच्च, CLOSE_RANGE_CLOEXEC);
	क्रम (i = 0; i <= 100; i++) अणु
		पूर्णांक flags = fcntl(खोलो_fds[i], F_GETFD);

		EXPECT_GT(flags, -1);
		EXPECT_EQ(flags & FD_CLOEXEC, FD_CLOEXEC);
	पूर्ण
पूर्ण

TEST(बंद_range_cloexec_unshare)
अणु
	पूर्णांक i, ret;
	पूर्णांक खोलो_fds[101];
	काष्ठा rlimit rlimit;

	क्रम (i = 0; i < ARRAY_SIZE(खोलो_fds); i++) अणु
		पूर्णांक fd;

		fd = खोलो("/dev/null", O_RDONLY);
		ASSERT_GE(fd, 0) अणु
			अगर (त्रुटि_सं == ENOENT)
				SKIP(वापस, "Skipping test since /dev/null does not exist");
		पूर्ण

		खोलो_fds[i] = fd;
	पूर्ण

	ret = sys_बंद_range(1000, 1000, CLOSE_RANGE_CLOEXEC);
	अगर (ret < 0) अणु
		अगर (त्रुटि_सं == ENOSYS)
			SKIP(वापस, "close_range() syscall not supported");
		अगर (त्रुटि_सं == EINVAL)
			SKIP(वापस, "close_range() doesn't support CLOSE_RANGE_CLOEXEC");
	पूर्ण

	/* Ensure the FD_CLOEXEC bit is set also with a resource limit in place.  */
	ASSERT_EQ(0, getrlimit(RLIMIT_NOखाता, &rlimit));
	rlimit.rlim_cur = 25;
	ASSERT_EQ(0, setrlimit(RLIMIT_NOखाता, &rlimit));

	/* Set बंद-on-exec क्रम two ranges: [0-50] and [75-100].  */
	ret = sys_बंद_range(खोलो_fds[0], खोलो_fds[50],
			      CLOSE_RANGE_CLOEXEC | CLOSE_RANGE_UNSHARE);
	ASSERT_EQ(0, ret);
	ret = sys_बंद_range(खोलो_fds[75], खोलो_fds[100],
			      CLOSE_RANGE_CLOEXEC | CLOSE_RANGE_UNSHARE);
	ASSERT_EQ(0, ret);

	क्रम (i = 0; i <= 50; i++) अणु
		पूर्णांक flags = fcntl(खोलो_fds[i], F_GETFD);

		EXPECT_GT(flags, -1);
		EXPECT_EQ(flags & FD_CLOEXEC, FD_CLOEXEC);
	पूर्ण

	क्रम (i = 51; i <= 74; i++) अणु
		पूर्णांक flags = fcntl(खोलो_fds[i], F_GETFD);

		EXPECT_GT(flags, -1);
		EXPECT_EQ(flags & FD_CLOEXEC, 0);
	पूर्ण

	क्रम (i = 75; i <= 100; i++) अणु
		पूर्णांक flags = fcntl(खोलो_fds[i], F_GETFD);

		EXPECT_GT(flags, -1);
		EXPECT_EQ(flags & FD_CLOEXEC, FD_CLOEXEC);
	पूर्ण

	/* Test a common pattern.  */
	ret = sys_बंद_range(3, अच_पूर्णांक_उच्च,
			      CLOSE_RANGE_CLOEXEC | CLOSE_RANGE_UNSHARE);
	क्रम (i = 0; i <= 100; i++) अणु
		पूर्णांक flags = fcntl(खोलो_fds[i], F_GETFD);

		EXPECT_GT(flags, -1);
		EXPECT_EQ(flags & FD_CLOEXEC, FD_CLOEXEC);
	पूर्ण
पूर्ण

/*
 * Regression test क्रम syzbot+96cfd2b22b3213646a93@syzkaller.appspoपंचांगail.com
 */
TEST(बंद_range_cloexec_syzbot)
अणु
	पूर्णांक fd1, fd2, fd3, flags, ret, status;
	pid_t pid;
	काष्ठा __clone_args args = अणु
		.flags = CLONE_खाताS,
		.निकास_संकेत = SIGCHLD,
	पूर्ण;

	/* Create a huge gap in the fd table. */
	fd1 = खोलो("/dev/null", O_RDWR);
	EXPECT_GT(fd1, 0);

	fd2 = dup2(fd1, 1000);
	EXPECT_GT(fd2, 0);

	pid = sys_clone3(&args, माप(args));
	ASSERT_GE(pid, 0);

	अगर (pid == 0) अणु
		ret = sys_बंद_range(3, ~0U, CLOSE_RANGE_CLOEXEC);
		अगर (ret)
			निकास(निकास_त्रुटि);

		/*
			 * We now have a निजी file descriptor table and all
			 * our खोलो fds should still be खोलो but made
			 * बंद-on-exec.
			 */
		flags = fcntl(fd1, F_GETFD);
		EXPECT_GT(flags, -1);
		EXPECT_EQ(flags & FD_CLOEXEC, FD_CLOEXEC);

		flags = fcntl(fd2, F_GETFD);
		EXPECT_GT(flags, -1);
		EXPECT_EQ(flags & FD_CLOEXEC, FD_CLOEXEC);

		fd3 = dup2(fd1, 42);
		EXPECT_GT(fd3, 0);

		/*
			 * Duplicating the file descriptor must हटाओ the
			 * FD_CLOEXEC flag.
			 */
		flags = fcntl(fd3, F_GETFD);
		EXPECT_GT(flags, -1);
		EXPECT_EQ(flags & FD_CLOEXEC, 0);

		निकास(निकास_सफल);
	पूर्ण

	EXPECT_EQ(रुकोpid(pid, &status, 0), pid);
	EXPECT_EQ(true, WIFEXITED(status));
	EXPECT_EQ(0, WEXITSTATUS(status));

	/*
	 * We had a shared file descriptor table beक्रमe aदीर्घ with requesting
	 * बंद-on-exec so the original fds must not be बंद-on-exec.
	 */
	flags = fcntl(fd1, F_GETFD);
	EXPECT_GT(flags, -1);
	EXPECT_EQ(flags & FD_CLOEXEC, FD_CLOEXEC);

	flags = fcntl(fd2, F_GETFD);
	EXPECT_GT(flags, -1);
	EXPECT_EQ(flags & FD_CLOEXEC, FD_CLOEXEC);

	fd3 = dup2(fd1, 42);
	EXPECT_GT(fd3, 0);

	flags = fcntl(fd3, F_GETFD);
	EXPECT_GT(flags, -1);
	EXPECT_EQ(flags & FD_CLOEXEC, 0);

	EXPECT_EQ(बंद(fd1), 0);
	EXPECT_EQ(बंद(fd2), 0);
	EXPECT_EQ(बंद(fd3), 0);
पूर्ण

/*
 * Regression test क्रम syzbot+96cfd2b22b3213646a93@syzkaller.appspoपंचांगail.com
 */
TEST(बंद_range_cloexec_unshare_syzbot)
अणु
	पूर्णांक i, fd1, fd2, fd3, flags, ret, status;
	pid_t pid;
	काष्ठा __clone_args args = अणु
		.flags = CLONE_खाताS,
		.निकास_संकेत = SIGCHLD,
	पूर्ण;

	/*
	 * Create a huge gap in the fd table. When we now call
	 * CLOSE_RANGE_UNSHARE with a shared fd table and and with ~0U as upper
	 * bound the kernel will only copy up to fd1 file descriptors पूर्णांकo the
	 * new fd table. If the kernel is buggy and करोesn't handle
	 * CLOSE_RANGE_CLOEXEC correctly it will not have copied all file
	 * descriptors and we will oops!
	 *
	 * On a buggy kernel this should immediately oops. But let's loop just
	 * to be sure.
	 */
	fd1 = खोलो("/dev/null", O_RDWR);
	EXPECT_GT(fd1, 0);

	fd2 = dup2(fd1, 1000);
	EXPECT_GT(fd2, 0);

	क्रम (i = 0; i < 100; i++) अणु

		pid = sys_clone3(&args, माप(args));
		ASSERT_GE(pid, 0);

		अगर (pid == 0) अणु
			ret = sys_बंद_range(3, ~0U, CLOSE_RANGE_UNSHARE |
						      CLOSE_RANGE_CLOEXEC);
			अगर (ret)
				निकास(निकास_त्रुटि);

			/*
			 * We now have a निजी file descriptor table and all
			 * our खोलो fds should still be खोलो but made
			 * बंद-on-exec.
			 */
			flags = fcntl(fd1, F_GETFD);
			EXPECT_GT(flags, -1);
			EXPECT_EQ(flags & FD_CLOEXEC, FD_CLOEXEC);

			flags = fcntl(fd2, F_GETFD);
			EXPECT_GT(flags, -1);
			EXPECT_EQ(flags & FD_CLOEXEC, FD_CLOEXEC);

			fd3 = dup2(fd1, 42);
			EXPECT_GT(fd3, 0);

			/*
			 * Duplicating the file descriptor must हटाओ the
			 * FD_CLOEXEC flag.
			 */
			flags = fcntl(fd3, F_GETFD);
			EXPECT_GT(flags, -1);
			EXPECT_EQ(flags & FD_CLOEXEC, 0);

			EXPECT_EQ(बंद(fd1), 0);
			EXPECT_EQ(बंद(fd2), 0);
			EXPECT_EQ(बंद(fd3), 0);

			निकास(निकास_सफल);
		पूर्ण

		EXPECT_EQ(रुकोpid(pid, &status, 0), pid);
		EXPECT_EQ(true, WIFEXITED(status));
		EXPECT_EQ(0, WEXITSTATUS(status));
	पूर्ण

	/*
	 * We created a निजी file descriptor table beक्रमe aदीर्घ with
	 * requesting बंद-on-exec so the original fds must not be
	 * बंद-on-exec.
	 */
	flags = fcntl(fd1, F_GETFD);
	EXPECT_GT(flags, -1);
	EXPECT_EQ(flags & FD_CLOEXEC, 0);

	flags = fcntl(fd2, F_GETFD);
	EXPECT_GT(flags, -1);
	EXPECT_EQ(flags & FD_CLOEXEC, 0);

	fd3 = dup2(fd1, 42);
	EXPECT_GT(fd3, 0);

	flags = fcntl(fd3, F_GETFD);
	EXPECT_GT(flags, -1);
	EXPECT_EQ(flags & FD_CLOEXEC, 0);

	EXPECT_EQ(बंद(fd1), 0);
	EXPECT_EQ(बंद(fd2), 0);
	EXPECT_EQ(बंद(fd3), 0);
पूर्ण

TEST_HARNESS_MAIN
