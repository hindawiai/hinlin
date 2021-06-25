<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <linux/netlink.h>
#समावेश <संकेत.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/prctl.h>
#समावेश <sys/socket.h>
#समावेश <sched.h>
#समावेश <sys/eventfd.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

#समावेश "../kselftest_harness.h"

#घोषणा __DEV_FULL "/sys/devices/virtual/mem/full/uevent"
#घोषणा __UEVENT_BUFFER_SIZE (2048 * 2)
#घोषणा __UEVENT_HEADER "add@/devices/virtual/mem/full"
#घोषणा __UEVENT_HEADER_LEN माप("add@/devices/virtual/mem/full")
#घोषणा __UEVENT_LISTEN_ALL -1

sमाप_प्रकार पढ़ो_noपूर्णांकr(पूर्णांक fd, व्योम *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार ret;

again:
	ret = पढ़ो(fd, buf, count);
	अगर (ret < 0 && त्रुटि_सं == EINTR)
		जाओ again;

	वापस ret;
पूर्ण

sमाप_प्रकार ग_लिखो_noपूर्णांकr(पूर्णांक fd, स्थिर व्योम *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार ret;

again:
	ret = ग_लिखो(fd, buf, count);
	अगर (ret < 0 && त्रुटि_सं == EINTR)
		जाओ again;

	वापस ret;
पूर्ण

पूर्णांक रुको_क्रम_pid(pid_t pid)
अणु
	पूर्णांक status, ret;

again:
	ret = रुकोpid(pid, &status, 0);
	अगर (ret == -1) अणु
		अगर (त्रुटि_सं == EINTR)
			जाओ again;

		वापस -1;
	पूर्ण

	अगर (ret != pid)
		जाओ again;

	अगर (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक uevent_listener(अचिन्हित दीर्घ post_flags, bool expect_uevent,
			   पूर्णांक sync_fd)
अणु
	पूर्णांक sk_fd, ret;
	socklen_t sk_addr_len;
	पूर्णांक fret = -1, rcv_buf_sz = __UEVENT_BUFFER_SIZE;
	uपूर्णांक64_t sync_add = 1;
	काष्ठा sockaddr_nl sk_addr = अणु 0 पूर्ण, rcv_addr = अणु 0 पूर्ण;
	अक्षर buf[__UEVENT_BUFFER_SIZE] = अणु 0 पूर्ण;
	काष्ठा iovec iov = अणु buf, __UEVENT_BUFFER_SIZE पूर्ण;
	अक्षर control[CMSG_SPACE(माप(काष्ठा ucred))];
	काष्ठा msghdr hdr = अणु
		&rcv_addr, माप(rcv_addr), &iov, 1,
		control,   माप(control),  0,
	पूर्ण;

	sk_fd = socket(AF_NETLINK, SOCK_RAW | SOCK_CLOEXEC,
		       NETLINK_KOBJECT_UEVENT);
	अगर (sk_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s - Failed to open uevent socket\n", म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	ret = setsockopt(sk_fd, SOL_SOCKET, SO_RCVBUF, &rcv_buf_sz,
			 माप(rcv_buf_sz));
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s - Failed to set socket options\n", म_त्रुटि(त्रुटि_सं));
		जाओ on_error;
	पूर्ण

	sk_addr.nl_family = AF_NETLINK;
	sk_addr.nl_groups = __UEVENT_LISTEN_ALL;

	sk_addr_len = माप(sk_addr);
	ret = bind(sk_fd, (काष्ठा sockaddr *)&sk_addr, sk_addr_len);
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s - Failed to bind socket\n", म_त्रुटि(त्रुटि_सं));
		जाओ on_error;
	पूर्ण

	ret = माला_लोockname(sk_fd, (काष्ठा sockaddr *)&sk_addr, &sk_addr_len);
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s - Failed to retrieve socket name\n", म_त्रुटि(त्रुटि_सं));
		जाओ on_error;
	पूर्ण

	अगर ((माप_प्रकार)sk_addr_len != माप(sk_addr)) अणु
		ख_लिखो(मानक_त्रुटि, "Invalid socket address size\n");
		जाओ on_error;
	पूर्ण

	अगर (post_flags & CLONE_NEWUSER) अणु
		ret = unshare(CLONE_NEWUSER);
		अगर (ret < 0) अणु
			ख_लिखो(मानक_त्रुटि,
				"%s - Failed to unshare user namespace\n",
				म_त्रुटि(त्रुटि_सं));
			जाओ on_error;
		पूर्ण
	पूर्ण

	अगर (post_flags & CLONE_NEWNET) अणु
		ret = unshare(CLONE_NEWNET);
		अगर (ret < 0) अणु
			ख_लिखो(मानक_त्रुटि,
				"%s - Failed to unshare network namespace\n",
				म_त्रुटि(त्रुटि_सं));
			जाओ on_error;
		पूर्ण
	पूर्ण

	ret = ग_लिखो_noपूर्णांकr(sync_fd, &sync_add, माप(sync_add));
	बंद(sync_fd);
	अगर (ret != माप(sync_add)) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to synchronize with parent process\n");
		जाओ on_error;
	पूर्ण

	fret = 0;
	क्रम (;;) अणु
		sमाप_प्रकार r;

		r = recvmsg(sk_fd, &hdr, 0);
		अगर (r <= 0) अणु
			ख_लिखो(मानक_त्रुटि, "%s - Failed to receive uevent\n", म_त्रुटि(त्रुटि_सं));
			ret = -1;
			अवरोध;
		पूर्ण

		/* ignore libudev messages */
		अगर (स_भेद(buf, "libudev", 8) == 0)
			जारी;

		/* ignore uevents we didn't trigger */
		अगर (स_भेद(buf, __UEVENT_HEADER, __UEVENT_HEADER_LEN) != 0)
			जारी;

		अगर (!expect_uevent) अणु
			ख_लिखो(मानक_त्रुटि, "Received unexpected uevent:\n");
			ret = -1;
		पूर्ण

		अगर (TH_LOG_ENABLED) अणु
			/* If logging is enabled dump the received uevent. */
			(व्योम)ग_लिखो_noपूर्णांकr(STDERR_खाताNO, buf, r);
			(व्योम)ग_लिखो_noपूर्णांकr(STDERR_खाताNO, "\n", 1);
		पूर्ण

		अवरोध;
	पूर्ण

on_error:
	बंद(sk_fd);

	वापस fret;
पूर्ण

पूर्णांक trigger_uevent(अचिन्हित पूर्णांक बार)
अणु
	पूर्णांक fd, ret;
	अचिन्हित पूर्णांक i;

	fd = खोलो(__DEV_FULL, O_RDWR | O_CLOEXEC);
	अगर (fd < 0) अणु
		अगर (त्रुटि_सं != ENOENT)
			वापस -EINVAL;

		वापस -1;
	पूर्ण

	क्रम (i = 0; i < बार; i++) अणु
		ret = ग_लिखो_noपूर्णांकr(fd, "add\n", माप("add\n") - 1);
		अगर (ret < 0) अणु
			ख_लिखो(मानक_त्रुटि, "Failed to trigger uevent\n");
			अवरोध;
		पूर्ण
	पूर्ण
	बंद(fd);

	वापस ret;
पूर्ण

पूर्णांक set_death_संकेत(व्योम)
अणु
	पूर्णांक ret;
	pid_t ppid;

	ret = prctl(PR_SET_PDEATHSIG, SIGKILL, 0, 0, 0);

	/* Check whether we have been orphaned. */
	ppid = getppid();
	अगर (ppid == 1) अणु
		pid_t self;

		self = getpid();
		ret = समाप्त(self, SIGKILL);
	पूर्ण

	अगर (ret < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक करो_test(अचिन्हित दीर्घ pre_flags, अचिन्हित दीर्घ post_flags,
		   bool expect_uevent, पूर्णांक sync_fd)
अणु
	पूर्णांक ret;
	uपूर्णांक64_t रुको_val;
	pid_t pid;
	sigset_t mask;
	sigset_t orig_mask;
	काष्ठा बारpec समयout;

	sigemptyset(&mask);
	sigaddset(&mask, SIGCHLD);

	ret = sigprocmask(SIG_BLOCK, &mask, &orig_mask);
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s- Failed to block SIGCHLD\n", म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	pid = विभाजन();
	अगर (pid < 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s - Failed to fork() new process\n", म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	अगर (pid == 0) अणु
		/* Make sure that we go away when our parent dies. */
		ret = set_death_संकेत();
		अगर (ret < 0) अणु
			ख_लिखो(मानक_त्रुटि, "Failed to set PR_SET_PDEATHSIG to SIGKILL\n");
			_निकास(निकास_त्रुटि);
		पूर्ण

		अगर (pre_flags & CLONE_NEWUSER) अणु
			ret = unshare(CLONE_NEWUSER);
			अगर (ret < 0) अणु
				ख_लिखो(मानक_त्रुटि,
					"%s - Failed to unshare user namespace\n",
					म_त्रुटि(त्रुटि_सं));
				_निकास(निकास_त्रुटि);
			पूर्ण
		पूर्ण

		अगर (pre_flags & CLONE_NEWNET) अणु
			ret = unshare(CLONE_NEWNET);
			अगर (ret < 0) अणु
				ख_लिखो(मानक_त्रुटि,
					"%s - Failed to unshare network namespace\n",
					म_त्रुटि(त्रुटि_सं));
				_निकास(निकास_त्रुटि);
			पूर्ण
		पूर्ण

		अगर (uevent_listener(post_flags, expect_uevent, sync_fd) < 0)
			_निकास(निकास_त्रुटि);

		_निकास(निकास_सफल);
	पूर्ण

	ret = पढ़ो_noपूर्णांकr(sync_fd, &रुको_val, माप(रुको_val));
	अगर (ret != माप(रुको_val)) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to synchronize with child process\n");
		_निकास(निकास_त्रुटि);
	पूर्ण

	/* Trigger 10 uevents to account क्रम the हाल where the kernel might
	 * drop some.
	 */
	ret = trigger_uevent(10);
	अगर (ret < 0)
		ख_लिखो(मानक_त्रुटि, "Failed triggering uevents\n");

	/* Wait क्रम 2 seconds beक्रमe considering this failed. This should be
	 * plenty of समय क्रम the kernel to deliver the uevent even under heavy
	 * load.
	 */
	समयout.tv_sec = 2;
	समयout.tv_nsec = 0;

again:
	ret = sigसमयdरुको(&mask, शून्य, &समयout);
	अगर (ret < 0) अणु
		अगर (त्रुटि_सं == EINTR)
			जाओ again;

		अगर (!expect_uevent)
			ret = समाप्त(pid, संक_इति); /* success */
		अन्यथा
			ret = समाप्त(pid, SIGUSR1); /* error */
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	ret = रुको_क्रम_pid(pid);
	अगर (ret < 0)
		वापस -1;

	वापस ret;
पूर्ण

अटल व्योम संकेत_handler(पूर्णांक sig)
अणु
	अगर (sig == संक_इति)
		_निकास(निकास_सफल);

	_निकास(निकास_त्रुटि);
पूर्ण

TEST(uevent_filtering)
अणु
	पूर्णांक ret, sync_fd;
	काष्ठा sigaction act;

	अगर (geteuid()) अणु
		TH_LOG("Uevent filtering tests require root privileges. Skipping test");
		_निकास(KSFT_SKIP);
	पूर्ण

	ret = access(__DEV_FULL, F_OK);
	EXPECT_EQ(0, ret) अणु
		अगर (त्रुटि_सं == ENOENT) अणु
			TH_LOG(__DEV_FULL " does not exist. Skipping test");
			_निकास(KSFT_SKIP);
		पूर्ण

		_निकास(KSFT_FAIL);
	पूर्ण

	act.sa_handler = संकेत_handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);

	ret = sigaction(संक_इति, &act, शून्य);
	ASSERT_EQ(0, ret);

	sync_fd = eventfd(0, EFD_CLOEXEC);
	ASSERT_GE(sync_fd, 0);

	/*
	 * Setup:
	 * - Open uevent listening socket in initial network namespace owned by
	 *   initial user namespace.
	 * - Trigger uevent in initial network namespace owned by initial user
	 *   namespace.
	 * Expected Result:
	 * - uevent listening socket receives uevent
	 */
	ret = करो_test(0, 0, true, sync_fd);
	ASSERT_EQ(0, ret) अणु
		जाओ करो_cleanup;
	पूर्ण

	/*
	 * Setup:
	 * - Open uevent listening socket in non-initial network namespace
	 *   owned by initial user namespace.
	 * - Trigger uevent in initial network namespace owned by initial user
	 *   namespace.
	 * Expected Result:
	 * - uevent listening socket receives uevent
	 */
	ret = करो_test(CLONE_NEWNET, 0, true, sync_fd);
	ASSERT_EQ(0, ret) अणु
		जाओ करो_cleanup;
	पूर्ण

	/*
	 * Setup:
	 * - unshare user namespace
	 * - Open uevent listening socket in initial network namespace
	 *   owned by initial user namespace.
	 * - Trigger uevent in initial network namespace owned by initial user
	 *   namespace.
	 * Expected Result:
	 * - uevent listening socket receives uevent
	 */
	ret = करो_test(CLONE_NEWUSER, 0, true, sync_fd);
	ASSERT_EQ(0, ret) अणु
		जाओ करो_cleanup;
	पूर्ण

	/*
	 * Setup:
	 * - Open uevent listening socket in non-initial network namespace
	 *   owned by non-initial user namespace.
	 * - Trigger uevent in initial network namespace owned by initial user
	 *   namespace.
	 * Expected Result:
	 * - uevent listening socket receives no uevent
	 */
	ret = करो_test(CLONE_NEWUSER | CLONE_NEWNET, 0, false, sync_fd);
	ASSERT_EQ(0, ret) अणु
		जाओ करो_cleanup;
	पूर्ण

	/*
	 * Setup:
	 * - Open uevent listening socket in initial network namespace
	 *   owned by initial user namespace.
	 * - unshare network namespace
	 * - Trigger uevent in initial network namespace owned by initial user
	 *   namespace.
	 * Expected Result:
	 * - uevent listening socket receives uevent
	 */
	ret = करो_test(0, CLONE_NEWNET, true, sync_fd);
	ASSERT_EQ(0, ret) अणु
		जाओ करो_cleanup;
	पूर्ण

	/*
	 * Setup:
	 * - Open uevent listening socket in initial network namespace
	 *   owned by initial user namespace.
	 * - unshare user namespace
	 * - Trigger uevent in initial network namespace owned by initial user
	 *   namespace.
	 * Expected Result:
	 * - uevent listening socket receives uevent
	 */
	ret = करो_test(0, CLONE_NEWUSER, true, sync_fd);
	ASSERT_EQ(0, ret) अणु
		जाओ करो_cleanup;
	पूर्ण

	/*
	 * Setup:
	 * - Open uevent listening socket in initial network namespace
	 *   owned by initial user namespace.
	 * - unshare user namespace
	 * - unshare network namespace
	 * - Trigger uevent in initial network namespace owned by initial user
	 *   namespace.
	 * Expected Result:
	 * - uevent listening socket receives uevent
	 */
	ret = करो_test(0, CLONE_NEWUSER | CLONE_NEWNET, true, sync_fd);
	ASSERT_EQ(0, ret) अणु
		जाओ करो_cleanup;
	पूर्ण

करो_cleanup:
	बंद(sync_fd);
पूर्ण

TEST_HARNESS_MAIN
