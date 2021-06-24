<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <सीमा.स>
#समावेश <linux/types.h>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <syscall.h>
#समावेश <sys/prctl.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>
#समावेश <sys/socket.h>
#समावेश <linux/kcmp.h>

#समावेश "pidfd.h"
#समावेश "../kselftest_harness.h"

/*
 * UNKNOWN_FD is an fd number that should never exist in the child, as it is
 * used to check the negative हाल.
 */
#घोषणा UNKNOWN_FD 111
#घोषणा UID_NOBODY 65535

अटल पूर्णांक sys_kcmp(pid_t pid1, pid_t pid2, पूर्णांक type, अचिन्हित दीर्घ idx1,
		    अचिन्हित दीर्घ idx2)
अणु
	वापस syscall(__NR_kcmp, pid1, pid2, type, idx1, idx2);
पूर्ण

अटल पूर्णांक __child(पूर्णांक sk, पूर्णांक memfd)
अणु
	पूर्णांक ret;
	अक्षर buf;

	/*
	 * Ensure we करोn't leave around a bunch of orphaned children अगर our
	 * tests fail.
	 */
	ret = prctl(PR_SET_PDEATHSIG, SIGKILL);
	अगर (ret) अणु
		ख_लिखो(मानक_त्रुटि, "%s: Child could not set DEATHSIG\n",
			म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	ret = send(sk, &memfd, माप(memfd), 0);
	अगर (ret != माप(memfd)) अणु
		ख_लिखो(मानक_त्रुटि, "%s: Child failed to send fd number\n",
			म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	/*
	 * The fixture setup is completed at this poपूर्णांक. The tests will run.
	 *
	 * This blocking recv enables the parent to message the child.
	 * Either we will पढ़ो 'P' off of the sk, indicating that we need
	 * to disable ptrace, or we will पढ़ो a 0, indicating that the other
	 * side has बंदd the sk. This occurs during fixture tearकरोwn समय,
	 * indicating that the child should निकास.
	 */
	जबतक ((ret = recv(sk, &buf, माप(buf), 0)) > 0) अणु
		अगर (buf == 'P') अणु
			ret = prctl(PR_SET_DUMPABLE, 0);
			अगर (ret < 0) अणु
				ख_लिखो(मानक_त्रुटि,
					"%s: Child failed to disable ptrace\n",
					म_त्रुटि(त्रुटि_सं));
				वापस -1;
			पूर्ण
		पूर्ण अन्यथा अणु
			ख_लिखो(मानक_त्रुटि, "Child received unknown command %c\n",
				buf);
			वापस -1;
		पूर्ण
		ret = send(sk, &buf, माप(buf), 0);
		अगर (ret != 1) अणु
			ख_लिखो(मानक_त्रुटि, "%s: Child failed to ack\n",
				म_त्रुटि(त्रुटि_सं));
			वापस -1;
		पूर्ण
	पूर्ण
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s: Child failed to read from socket\n",
			म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक child(पूर्णांक sk)
अणु
	पूर्णांक memfd, ret;

	memfd = sys_memfd_create("test", 0);
	अगर (memfd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s: Child could not create memfd\n",
			म_त्रुटि(त्रुटि_सं));
		ret = -1;
	पूर्ण अन्यथा अणु
		ret = __child(sk, memfd);
		बंद(memfd);
	पूर्ण

	बंद(sk);
	वापस ret;
पूर्ण

FIXTURE(child)
अणु
	/*
	 * remote_fd is the number of the FD which we are trying to retrieve
	 * from the child.
	 */
	पूर्णांक remote_fd;
	/* pid poपूर्णांकs to the child which we are fetching FDs from */
	pid_t pid;
	/* pidfd is the pidfd of the child */
	पूर्णांक pidfd;
	/*
	 * sk is our side of the socketpair used to communicate with the child.
	 * When it is बंदd, the child will निकास.
	 */
	पूर्णांक sk;
पूर्ण;

FIXTURE_SETUP(child)
अणु
	पूर्णांक ret, sk_pair[2];

	ASSERT_EQ(0, socketpair(PF_LOCAL, SOCK_SEQPACKET, 0, sk_pair)) अणु
		TH_LOG("%s: failed to create socketpair", म_त्रुटि(त्रुटि_सं));
	पूर्ण
	self->sk = sk_pair[0];

	self->pid = विभाजन();
	ASSERT_GE(self->pid, 0);

	अगर (self->pid == 0) अणु
		बंद(sk_pair[0]);
		अगर (child(sk_pair[1]))
			_निकास(निकास_त्रुटि);
		_निकास(निकास_सफल);
	पूर्ण

	बंद(sk_pair[1]);

	self->pidfd = sys_pidfd_खोलो(self->pid, 0);
	ASSERT_GE(self->pidfd, 0);

	/*
	 * Wait क्रम the child to complete setup. It'll send the remote memfd's
	 * number when पढ़ोy.
	 */
	ret = recv(sk_pair[0], &self->remote_fd, माप(self->remote_fd), 0);
	ASSERT_EQ(माप(self->remote_fd), ret);
पूर्ण

FIXTURE_TEARDOWN(child)
अणु
	EXPECT_EQ(0, बंद(self->pidfd));
	EXPECT_EQ(0, बंद(self->sk));

	EXPECT_EQ(0, रुको_क्रम_pid(self->pid));
पूर्ण

TEST_F(child, disable_ptrace)
अणु
	पूर्णांक uid, fd;
	अक्षर c;

	/*
	 * Turn पूर्णांकo nobody अगर we're root, to aव्योम CAP_SYS_PTRACE
	 *
	 * The tests should run in their own process, so even this test fails,
	 * it shouldn't result in subsequent tests failing.
	 */
	uid = getuid();
	अगर (uid == 0)
		ASSERT_EQ(0, seteuid(UID_NOBODY));

	ASSERT_EQ(1, send(self->sk, "P", 1, 0));
	ASSERT_EQ(1, recv(self->sk, &c, 1, 0));

	fd = sys_pidfd_getfd(self->pidfd, self->remote_fd, 0);
	EXPECT_EQ(-1, fd);
	EXPECT_EQ(EPERM, त्रुटि_सं);

	अगर (uid == 0)
		ASSERT_EQ(0, seteuid(0));
पूर्ण

TEST_F(child, fetch_fd)
अणु
	पूर्णांक fd, ret;

	fd = sys_pidfd_getfd(self->pidfd, self->remote_fd, 0);
	ASSERT_GE(fd, 0);

	ret = sys_kcmp(getpid(), self->pid, KCMP_खाता, fd, self->remote_fd);
	अगर (ret < 0 && त्रुटि_सं == ENOSYS)
		SKIP(वापस, "kcmp() syscall not supported");
	EXPECT_EQ(ret, 0);

	ret = fcntl(fd, F_GETFD);
	ASSERT_GE(ret, 0);
	EXPECT_GE(ret & FD_CLOEXEC, 0);

	बंद(fd);
पूर्ण

TEST_F(child, test_unknown_fd)
अणु
	पूर्णांक fd;

	fd = sys_pidfd_getfd(self->pidfd, UNKNOWN_FD, 0);
	EXPECT_EQ(-1, fd) अणु
		TH_LOG("getfd succeeded while fetching unknown fd");
	पूर्ण;
	EXPECT_EQ(EBADF, त्रुटि_सं) अणु
		TH_LOG("%s: getfd did not get EBADF", म_त्रुटि(त्रुटि_सं));
	पूर्ण
पूर्ण

TEST(flags_set)
अणु
	ASSERT_EQ(-1, sys_pidfd_getfd(0, 0, 1));
	EXPECT_EQ(त्रुटि_सं, EINVAL);
पूर्ण

#अगर __NR_pidfd_getfd == -1
पूर्णांक मुख्य(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "__NR_pidfd_getfd undefined. The pidfd_getfd syscall is unavailable. Test aborting\n");
	वापस KSFT_SKIP;
पूर्ण
#अन्यथा
TEST_HARNESS_MAIN
#पूर्ण_अगर
