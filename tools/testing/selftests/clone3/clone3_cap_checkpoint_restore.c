<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Based on Christian Brauner's clone3() example.
 * These tests are assuming to be running in the host's
 * PID namespace.
 */

/* capabilities related code based on selftests/bpf/test_verअगरier.c */

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <sys/capability.h>
#समावेश <sys/prctl.h>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <sys/un.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>
#समावेश <sched.h>

#समावेश "../kselftest_harness.h"
#समावेश "clone3_selftests.h"

#अगर_अघोषित MAX_PID_NS_LEVEL
#घोषणा MAX_PID_NS_LEVEL 32
#पूर्ण_अगर

अटल व्योम child_निकास(पूर्णांक ret)
अणु
	ख_साफ(मानक_निकास);
	ख_साफ(मानक_त्रुटि);
	_निकास(ret);
पूर्ण

अटल पूर्णांक call_clone3_set_tid(काष्ठा __test_metadata *_metadata,
			       pid_t *set_tid, माप_प्रकार set_tid_size)
अणु
	पूर्णांक status;
	pid_t pid = -1;

	काष्ठा __clone_args args = अणु
		.निकास_संकेत = SIGCHLD,
		.set_tid = ptr_to_u64(set_tid),
		.set_tid_size = set_tid_size,
	पूर्ण;

	pid = sys_clone3(&args, माप(args));
	अगर (pid < 0) अणु
		TH_LOG("%s - Failed to create new process", म_त्रुटि(त्रुटि_सं));
		वापस -त्रुटि_सं;
	पूर्ण

	अगर (pid == 0) अणु
		पूर्णांक ret;
		अक्षर पंचांगp = 0;

		TH_LOG("I am the child, my PID is %d (expected %d)", getpid(), set_tid[0]);

		अगर (set_tid[0] != getpid())
			child_निकास(निकास_त्रुटि);
		child_निकास(निकास_सफल);
	पूर्ण

	TH_LOG("I am the parent (%d). My child's pid is %d", getpid(), pid);

	अगर (रुकोpid(pid, &status, 0) < 0) अणु
		TH_LOG("Child returned %s", म_त्रुटि(त्रुटि_सं));
		वापस -त्रुटि_सं;
	पूर्ण

	अगर (!WIFEXITED(status))
		वापस -1;

	वापस WEXITSTATUS(status);
पूर्ण

अटल पूर्णांक test_clone3_set_tid(काष्ठा __test_metadata *_metadata,
			       pid_t *set_tid, माप_प्रकार set_tid_size)
अणु
	पूर्णांक ret;

	TH_LOG("[%d] Trying clone3() with CLONE_SET_TID to %d", getpid(), set_tid[0]);
	ret = call_clone3_set_tid(_metadata, set_tid, set_tid_size);
	TH_LOG("[%d] clone3() with CLONE_SET_TID %d says:%d", getpid(), set_tid[0], ret);
	वापस ret;
पूर्ण

काष्ठा libcap अणु
	काष्ठा __user_cap_header_काष्ठा hdr;
	काष्ठा __user_cap_data_काष्ठा data[2];
पूर्ण;

अटल पूर्णांक set_capability(व्योम)
अणु
	cap_value_t cap_values[] = अणु CAP_SETUID, CAP_SETGID पूर्ण;
	काष्ठा libcap *cap;
	पूर्णांक ret = -1;
	cap_t caps;

	caps = cap_get_proc();
	अगर (!caps) अणु
		लिखो_त्रुटि("cap_get_proc");
		वापस -1;
	पूर्ण

	/* Drop all capabilities */
	अगर (cap_clear(caps)) अणु
		लिखो_त्रुटि("cap_clear");
		जाओ out;
	पूर्ण

	cap_set_flag(caps, CAP_EFFECTIVE, 2, cap_values, CAP_SET);
	cap_set_flag(caps, CAP_PERMITTED, 2, cap_values, CAP_SET);

	cap = (काष्ठा libcap *) caps;

	/* 40 -> CAP_CHECKPOINT_RESTORE */
	cap->data[1].effective |= 1 << (40 - 32);
	cap->data[1].permitted |= 1 << (40 - 32);

	अगर (cap_set_proc(caps)) अणु
		लिखो_त्रुटि("cap_set_proc");
		जाओ out;
	पूर्ण
	ret = 0;
out:
	अगर (cap_मुक्त(caps))
		लिखो_त्रुटि("cap_free");
	वापस ret;
पूर्ण

TEST(clone3_cap_checkpoपूर्णांक_restore)
अणु
	pid_t pid;
	पूर्णांक status;
	पूर्णांक ret = 0;
	pid_t set_tid[1];

	test_clone3_supported();

	EXPECT_EQ(getuid(), 0)
		SKIP(वापस, "Skipping all tests as non-root");

	स_रखो(&set_tid, 0, माप(set_tid));

	/* Find the current active PID */
	pid = विभाजन();
	अगर (pid == 0) अणु
		TH_LOG("Child has PID %d", getpid());
		child_निकास(निकास_सफल);
	पूर्ण
	ASSERT_GT(रुकोpid(pid, &status, 0), 0)
		TH_LOG("Waiting for child %d failed", pid);

	/* After the child has finished, its PID should be मुक्त. */
	set_tid[0] = pid;

	ASSERT_EQ(set_capability(), 0)
		TH_LOG("Could not set CAP_CHECKPOINT_RESTORE");

	ASSERT_EQ(prctl(PR_SET_KEEPCAPS, 1, 0, 0, 0), 0);

	EXPECT_EQ(setgid(65534), 0)
		TH_LOG("Failed to setgid(65534)");
	ASSERT_EQ(setuid(65534), 0);

	set_tid[0] = pid;
	/* This would fail without CAP_CHECKPOINT_RESTORE */
	ASSERT_EQ(test_clone3_set_tid(_metadata, set_tid, 1), -EPERM);
	ASSERT_EQ(set_capability(), 0)
		TH_LOG("Could not set CAP_CHECKPOINT_RESTORE");
	/* This should work as we have CAP_CHECKPOINT_RESTORE as non-root */
	ASSERT_EQ(test_clone3_set_tid(_metadata, set_tid, 1), 0);
पूर्ण

TEST_HARNESS_MAIN
