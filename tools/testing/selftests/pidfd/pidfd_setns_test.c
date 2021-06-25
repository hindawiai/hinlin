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
#समावेश <sys/स्थिति.स>

#समावेश "pidfd.h"
#समावेश "../clone3/clone3_selftests.h"
#समावेश "../kselftest_harness.h"

क्रमागत अणु
	PIDFD_NS_USER,
	PIDFD_NS_MNT,
	PIDFD_NS_PID,
	PIDFD_NS_UTS,
	PIDFD_NS_IPC,
	PIDFD_NS_NET,
	PIDFD_NS_CGROUP,
	PIDFD_NS_PIDCLD,
	PIDFD_NS_TIME,
	PIDFD_NS_MAX
पूर्ण;

स्थिर काष्ठा ns_info अणु
	स्थिर अक्षर *name;
	पूर्णांक flag;
पूर्ण ns_info[] = अणु
	[PIDFD_NS_USER]   = अणु "user",             CLONE_NEWUSER,   पूर्ण,
	[PIDFD_NS_MNT]    = अणु "mnt",              CLONE_NEWNS,     पूर्ण,
	[PIDFD_NS_PID]    = अणु "pid",              CLONE_NEWPID,    पूर्ण,
	[PIDFD_NS_UTS]    = अणु "uts",              CLONE_NEWUTS,    पूर्ण,
	[PIDFD_NS_IPC]    = अणु "ipc",              CLONE_NEWIPC,    पूर्ण,
	[PIDFD_NS_NET]    = अणु "net",              CLONE_NEWNET,    पूर्ण,
	[PIDFD_NS_CGROUP] = अणु "cgroup",           CLONE_NEWCGROUP, पूर्ण,
	[PIDFD_NS_PIDCLD] = अणु "pid_for_children", 0,               पूर्ण,
	[PIDFD_NS_TIME]	  = अणु "time",             CLONE_NEWTIME,   पूर्ण,
पूर्ण;

FIXTURE(current_nsset)
अणु
	pid_t pid;
	पूर्णांक pidfd;
	पूर्णांक nsfds[PIDFD_NS_MAX];

	pid_t child_pid_निकासed;
	पूर्णांक child_pidfd_निकासed;

	pid_t child_pid1;
	पूर्णांक child_pidfd1;
	पूर्णांक child_nsfds1[PIDFD_NS_MAX];

	pid_t child_pid2;
	पूर्णांक child_pidfd2;
	पूर्णांक child_nsfds2[PIDFD_NS_MAX];
पूर्ण;

अटल पूर्णांक sys_रुकोid(पूर्णांक which, pid_t pid, पूर्णांक options)
अणु
	वापस syscall(__NR_रुकोid, which, pid, शून्य, options, शून्य);
पूर्ण

pid_t create_child(पूर्णांक *pidfd, अचिन्हित flags)
अणु
	काष्ठा __clone_args args = अणु
		.flags		= CLONE_PIDFD | flags,
		.निकास_संकेत	= SIGCHLD,
		.pidfd		= ptr_to_u64(pidfd),
	पूर्ण;

	वापस sys_clone3(&args, माप(काष्ठा clone_args));
पूर्ण

अटल bool चयन_समयns(व्योम)
अणु
	पूर्णांक fd, ret;

	अगर (unshare(CLONE_NEWTIME))
		वापस false;

	fd = खोलो("/proc/self/ns/time_for_children", O_RDONLY | O_CLOEXEC);
	अगर (fd < 0)
		वापस false;

	ret = setns(fd, CLONE_NEWTIME);
	बंद(fd);
	वापस ret == 0;
पूर्ण

अटल sमाप_प्रकार पढ़ो_noपूर्णांकr(पूर्णांक fd, व्योम *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार ret;

	करो अणु
		ret = पढ़ो(fd, buf, count);
	पूर्ण जबतक (ret < 0 && त्रुटि_सं == EINTR);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ग_लिखो_noपूर्णांकr(पूर्णांक fd, स्थिर व्योम *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार ret;

	करो अणु
		ret = ग_लिखो(fd, buf, count);
	पूर्ण जबतक (ret < 0 && त्रुटि_सं == EINTR);

	वापस ret;
पूर्ण

FIXTURE_SETUP(current_nsset)
अणु
	पूर्णांक i, proc_fd, ret;
	पूर्णांक ipc_sockets[2];
	अक्षर c;

	क्रम (i = 0; i < PIDFD_NS_MAX; i++) अणु
		self->nsfds[i]		= -EBADF;
		self->child_nsfds1[i]	= -EBADF;
		self->child_nsfds2[i]	= -EBADF;
	पूर्ण

	proc_fd = खोलो("/proc/self/ns", O_सूचीECTORY | O_CLOEXEC);
	ASSERT_GE(proc_fd, 0) अणु
		TH_LOG("%m - Failed to open /proc/self/ns");
	पूर्ण

	self->pid = getpid();
	क्रम (i = 0; i < PIDFD_NS_MAX; i++) अणु
		स्थिर काष्ठा ns_info *info = &ns_info[i];
		self->nsfds[i] = खोलोat(proc_fd, info->name, O_RDONLY | O_CLOEXEC);
		अगर (self->nsfds[i] < 0) अणु
			EXPECT_EQ(त्रुटि_सं, ENOENT) अणु
				TH_LOG("%m - Failed to open %s namespace for process %d",
				       info->name, self->pid);
			पूर्ण
		पूर्ण
	पूर्ण

	self->pidfd = sys_pidfd_खोलो(self->pid, 0);
	EXPECT_GT(self->pidfd, 0) अणु
		TH_LOG("%m - Failed to open pidfd for process %d", self->pid);
	पूर्ण

	/* Create task that निकासs right away. */
	self->child_pid_निकासed = create_child(&self->child_pidfd_निकासed,
					      CLONE_NEWUSER | CLONE_NEWNET);
	EXPECT_GT(self->child_pid_निकासed, 0);

	अगर (self->child_pid_निकासed == 0)
		_निकास(निकास_सफल);

	ASSERT_EQ(sys_रुकोid(P_PID, self->child_pid_निकासed, WEXITED | WNOWAIT), 0);

	self->pidfd = sys_pidfd_खोलो(self->pid, 0);
	EXPECT_GE(self->pidfd, 0) अणु
		TH_LOG("%m - Failed to open pidfd for process %d", self->pid);
	पूर्ण

	ret = socketpair(AF_LOCAL, SOCK_STREAM | SOCK_CLOEXEC, 0, ipc_sockets);
	EXPECT_EQ(ret, 0);

	/* Create tasks that will be stopped. */
	self->child_pid1 = create_child(&self->child_pidfd1,
					CLONE_NEWUSER | CLONE_NEWNS |
					CLONE_NEWCGROUP | CLONE_NEWIPC |
					CLONE_NEWUTS | CLONE_NEWPID |
					CLONE_NEWNET);
	EXPECT_GE(self->child_pid1, 0);

	अगर (self->child_pid1 == 0) अणु
		बंद(ipc_sockets[0]);

		अगर (!चयन_समयns())
			_निकास(निकास_त्रुटि);

		अगर (ग_लिखो_noपूर्णांकr(ipc_sockets[1], "1", 1) < 0)
			_निकास(निकास_त्रुटि);

		बंद(ipc_sockets[1]);

		छोड़ो();
		_निकास(निकास_सफल);
	पूर्ण

	बंद(ipc_sockets[1]);
	ASSERT_EQ(पढ़ो_noपूर्णांकr(ipc_sockets[0], &c, 1), 1);
	बंद(ipc_sockets[0]);

	ret = socketpair(AF_LOCAL, SOCK_STREAM | SOCK_CLOEXEC, 0, ipc_sockets);
	EXPECT_EQ(ret, 0);

	self->child_pid2 = create_child(&self->child_pidfd2,
					CLONE_NEWUSER | CLONE_NEWNS |
					CLONE_NEWCGROUP | CLONE_NEWIPC |
					CLONE_NEWUTS | CLONE_NEWPID |
					CLONE_NEWNET);
	EXPECT_GE(self->child_pid2, 0);

	अगर (self->child_pid2 == 0) अणु
		बंद(ipc_sockets[0]);

		अगर (!चयन_समयns())
			_निकास(निकास_त्रुटि);

		अगर (ग_लिखो_noपूर्णांकr(ipc_sockets[1], "1", 1) < 0)
			_निकास(निकास_त्रुटि);

		बंद(ipc_sockets[1]);

		छोड़ो();
		_निकास(निकास_सफल);
	पूर्ण

	बंद(ipc_sockets[1]);
	ASSERT_EQ(पढ़ो_noपूर्णांकr(ipc_sockets[0], &c, 1), 1);
	बंद(ipc_sockets[0]);

	क्रम (i = 0; i < PIDFD_NS_MAX; i++) अणु
		अक्षर p[100];

		स्थिर काष्ठा ns_info *info = &ns_info[i];

		self->nsfds[i] = खोलोat(proc_fd, info->name, O_RDONLY | O_CLOEXEC);
		अगर (self->nsfds[i] < 0) अणु
			EXPECT_EQ(त्रुटि_सं, ENOENT) अणु
				TH_LOG("%m - Failed to open %s namespace for process %d",
				       info->name, self->pid);
			पूर्ण
		पूर्ण

		ret = snम_लिखो(p, माप(p), "/proc/%d/ns/%s",
			       self->child_pid1, info->name);
		EXPECT_GT(ret, 0);
		EXPECT_LT(ret, माप(p));

		self->child_nsfds1[i] = खोलो(p, O_RDONLY | O_CLOEXEC);
		अगर (self->child_nsfds1[i] < 0) अणु
			EXPECT_EQ(त्रुटि_सं, ENOENT) अणु
				TH_LOG("%m - Failed to open %s namespace for process %d",
				       info->name, self->child_pid1);
			पूर्ण
		पूर्ण

		ret = snम_लिखो(p, माप(p), "/proc/%d/ns/%s",
			       self->child_pid2, info->name);
		EXPECT_GT(ret, 0);
		EXPECT_LT(ret, माप(p));

		self->child_nsfds2[i] = खोलो(p, O_RDONLY | O_CLOEXEC);
		अगर (self->child_nsfds2[i] < 0) अणु
			EXPECT_EQ(त्रुटि_सं, ENOENT) अणु
				TH_LOG("%m - Failed to open %s namespace for process %d",
				       info->name, self->child_pid1);
			पूर्ण
		पूर्ण
	पूर्ण

	बंद(proc_fd);
पूर्ण

FIXTURE_TEARDOWN(current_nsset)
अणु
	पूर्णांक i;

	ASSERT_EQ(sys_pidfd_send_संकेत(self->child_pidfd1,
					SIGKILL, शून्य, 0), 0);
	ASSERT_EQ(sys_pidfd_send_संकेत(self->child_pidfd2,
					SIGKILL, शून्य, 0), 0);

	क्रम (i = 0; i < PIDFD_NS_MAX; i++) अणु
		अगर (self->nsfds[i] >= 0)
			बंद(self->nsfds[i]);
		अगर (self->child_nsfds1[i] >= 0)
			बंद(self->child_nsfds1[i]);
		अगर (self->child_nsfds2[i] >= 0)
			बंद(self->child_nsfds2[i]);
	पूर्ण

	अगर (self->child_pidfd1 >= 0)
		EXPECT_EQ(0, बंद(self->child_pidfd1));
	अगर (self->child_pidfd2 >= 0)
		EXPECT_EQ(0, बंद(self->child_pidfd2));
	ASSERT_EQ(sys_रुकोid(P_PID, self->child_pid_निकासed, WEXITED), 0);
	ASSERT_EQ(sys_रुकोid(P_PID, self->child_pid1, WEXITED), 0);
	ASSERT_EQ(sys_रुकोid(P_PID, self->child_pid2, WEXITED), 0);
पूर्ण

अटल पूर्णांक preserve_ns(स्थिर पूर्णांक pid, स्थिर अक्षर *ns)
अणु
	पूर्णांक ret;
	अक्षर path[50];

	ret = snम_लिखो(path, माप(path), "/proc/%d/ns/%s", pid, ns);
	अगर (ret < 0 || (माप_प्रकार)ret >= माप(path))
		वापस -EIO;

	वापस खोलो(path, O_RDONLY | O_CLOEXEC);
पूर्ण

अटल पूर्णांक in_same_namespace(पूर्णांक ns_fd1, pid_t pid2, स्थिर अक्षर *ns)
अणु
	पूर्णांक ns_fd2 = -EBADF;
	पूर्णांक ret = -1;
	काष्ठा stat ns_st1, ns_st2;

	ret = ख_स्थिति(ns_fd1, &ns_st1);
	अगर (ret < 0)
		वापस -1;

	ns_fd2 = preserve_ns(pid2, ns);
	अगर (ns_fd2 < 0)
		वापस -1;

	ret = ख_स्थिति(ns_fd2, &ns_st2);
	बंद(ns_fd2);
	अगर (ret < 0)
		वापस -1;

	/* processes are in the same namespace */
	अगर ((ns_st1.st_dev == ns_st2.st_dev) &&
	    (ns_st1.st_ino == ns_st2.st_ino))
		वापस 1;

	/* processes are in dअगरferent namespaces */
	वापस 0;
पूर्ण

/* Test that we can't pass garbage to the kernel. */
TEST_F(current_nsset, invalid_flags)
अणु
	ASSERT_NE(setns(self->pidfd, 0), 0);
	EXPECT_EQ(त्रुटि_सं, EINVAL);

	ASSERT_NE(setns(self->pidfd, -1), 0);
	EXPECT_EQ(त्रुटि_सं, EINVAL);

	ASSERT_NE(setns(self->pidfd, CLONE_VM), 0);
	EXPECT_EQ(त्रुटि_सं, EINVAL);

	ASSERT_NE(setns(self->pidfd, CLONE_NEWUSER | CLONE_VM), 0);
	EXPECT_EQ(त्रुटि_सं, EINVAL);
पूर्ण

/* Test that we can't attach to a task that has alपढ़ोy निकासed. */
TEST_F(current_nsset, pidfd_निकासed_child)
अणु
	पूर्णांक i;
	pid_t pid;

	ASSERT_NE(setns(self->child_pidfd_निकासed, CLONE_NEWUSER | CLONE_NEWNET),
		  0);
	EXPECT_EQ(त्रुटि_सं, ESRCH);

	pid = getpid();
	क्रम (i = 0; i < PIDFD_NS_MAX; i++) अणु
		स्थिर काष्ठा ns_info *info = &ns_info[i];
		/* Verअगरy that we haven't changed any namespaces. */
		अगर (self->nsfds[i] >= 0)
			ASSERT_EQ(in_same_namespace(self->nsfds[i], pid, info->name), 1);
	पूर्ण
पूर्ण

TEST_F(current_nsset, pidfd_incremental_setns)
अणु
	पूर्णांक i;
	pid_t pid;

	pid = getpid();
	क्रम (i = 0; i < PIDFD_NS_MAX; i++) अणु
		स्थिर काष्ठा ns_info *info = &ns_info[i];
		पूर्णांक nsfd;

		अगर (self->child_nsfds1[i] < 0)
			जारी;

		अगर (info->flag) अणु
			ASSERT_EQ(setns(self->child_pidfd1, info->flag), 0) अणु
				TH_LOG("%m - Failed to setns to %s namespace of %d via pidfd %d",
				       info->name, self->child_pid1,
				       self->child_pidfd1);
			पूर्ण
		पूर्ण

		/* Verअगरy that we have changed to the correct namespaces. */
		अगर (info->flag == CLONE_NEWPID)
			nsfd = self->nsfds[i];
		अन्यथा
			nsfd = self->child_nsfds1[i];
		ASSERT_EQ(in_same_namespace(nsfd, pid, info->name), 1) अणु
			TH_LOG("setns failed to place us correctly into %s namespace of %d via pidfd %d",
			       info->name, self->child_pid1,
			       self->child_pidfd1);
		पूर्ण
		TH_LOG("Managed to correctly setns to %s namespace of %d via pidfd %d",
		       info->name, self->child_pid1, self->child_pidfd1);
	पूर्ण
पूर्ण

TEST_F(current_nsset, nsfd_incremental_setns)
अणु
	पूर्णांक i;
	pid_t pid;

	pid = getpid();
	क्रम (i = 0; i < PIDFD_NS_MAX; i++) अणु
		स्थिर काष्ठा ns_info *info = &ns_info[i];
		पूर्णांक nsfd;

		अगर (self->child_nsfds1[i] < 0)
			जारी;

		अगर (info->flag) अणु
			ASSERT_EQ(setns(self->child_nsfds1[i], info->flag), 0) अणु
				TH_LOG("%m - Failed to setns to %s namespace of %d via nsfd %d",
				       info->name, self->child_pid1,
				       self->child_nsfds1[i]);
			पूर्ण
		पूर्ण

		/* Verअगरy that we have changed to the correct namespaces. */
		अगर (info->flag == CLONE_NEWPID)
			nsfd = self->nsfds[i];
		अन्यथा
			nsfd = self->child_nsfds1[i];
		ASSERT_EQ(in_same_namespace(nsfd, pid, info->name), 1) अणु
			TH_LOG("setns failed to place us correctly into %s namespace of %d via nsfd %d",
			       info->name, self->child_pid1,
			       self->child_nsfds1[i]);
		पूर्ण
		TH_LOG("Managed to correctly setns to %s namespace of %d via nsfd %d",
		       info->name, self->child_pid1, self->child_nsfds1[i]);
	पूर्ण
पूर्ण

TEST_F(current_nsset, pidfd_one_shot_setns)
अणु
	अचिन्हित flags = 0;
	पूर्णांक i;
	pid_t pid;

	क्रम (i = 0; i < PIDFD_NS_MAX; i++) अणु
		स्थिर काष्ठा ns_info *info = &ns_info[i];

		अगर (self->child_nsfds1[i] < 0)
			जारी;

		flags |= info->flag;
		TH_LOG("Adding %s namespace of %d to list of namespaces to attach to",
		       info->name, self->child_pid1);
	पूर्ण

	ASSERT_EQ(setns(self->child_pidfd1, flags), 0) अणु
		TH_LOG("%m - Failed to setns to namespaces of %d",
		       self->child_pid1);
	पूर्ण

	pid = getpid();
	क्रम (i = 0; i < PIDFD_NS_MAX; i++) अणु
		स्थिर काष्ठा ns_info *info = &ns_info[i];
		पूर्णांक nsfd;

		अगर (self->child_nsfds1[i] < 0)
			जारी;

		/* Verअगरy that we have changed to the correct namespaces. */
		अगर (info->flag == CLONE_NEWPID)
			nsfd = self->nsfds[i];
		अन्यथा
			nsfd = self->child_nsfds1[i];
		ASSERT_EQ(in_same_namespace(nsfd, pid, info->name), 1) अणु
			TH_LOG("setns failed to place us correctly into %s namespace of %d",
			       info->name, self->child_pid1);
		पूर्ण
		TH_LOG("Managed to correctly setns to %s namespace of %d",
		       info->name, self->child_pid1);
	पूर्ण
पूर्ण

TEST_F(current_nsset, no_foul_play)
अणु
	अचिन्हित flags = 0;
	पूर्णांक i;

	क्रम (i = 0; i < PIDFD_NS_MAX; i++) अणु
		स्थिर काष्ठा ns_info *info = &ns_info[i];

		अगर (self->child_nsfds1[i] < 0)
			जारी;

		flags |= info->flag;
		अगर (info->flag) /* No use logging pid_क्रम_children. */
			TH_LOG("Adding %s namespace of %d to list of namespaces to attach to",
			       info->name, self->child_pid1);
	पूर्ण

	ASSERT_EQ(setns(self->child_pidfd1, flags), 0) अणु
		TH_LOG("%m - Failed to setns to namespaces of %d vid pidfd %d",
		       self->child_pid1, self->child_pidfd1);
	पूर्ण

	/*
	 * Can't setns to a user namespace outside of our hierarchy since we
	 * करोn't have caps in there and didn't create it. That means that under
	 * no circumstances should we be able to setns to any of the other
	 * ones since they aren't owned by our user namespace.
	 */
	क्रम (i = 0; i < PIDFD_NS_MAX; i++) अणु
		स्थिर काष्ठा ns_info *info = &ns_info[i];

		अगर (self->child_nsfds2[i] < 0 || !info->flag)
			जारी;

		ASSERT_NE(setns(self->child_pidfd2, info->flag), 0) अणु
			TH_LOG("Managed to setns to %s namespace of %d via pidfd %d",
			       info->name, self->child_pid2,
			       self->child_pidfd2);
		पूर्ण
		TH_LOG("%m - Correctly failed to setns to %s namespace of %d via pidfd %d",
		       info->name, self->child_pid2,
		       self->child_pidfd2);

		ASSERT_NE(setns(self->child_nsfds2[i], info->flag), 0) अणु
			TH_LOG("Managed to setns to %s namespace of %d via nsfd %d",
			       info->name, self->child_pid2,
			       self->child_nsfds2[i]);
		पूर्ण
		TH_LOG("%m - Correctly failed to setns to %s namespace of %d via nsfd %d",
		       info->name, self->child_pid2,
		       self->child_nsfds2[i]);
	पूर्ण
पूर्ण

TEST(setns_einval)
अणु
	पूर्णांक fd;

	fd = sys_memfd_create("rostock", 0);
	EXPECT_GT(fd, 0);

	ASSERT_NE(setns(fd, 0), 0);
	EXPECT_EQ(त्रुटि_सं, EINVAL);
	बंद(fd);
पूर्ण

TEST_HARNESS_MAIN
