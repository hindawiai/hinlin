<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Based on Christian Brauner's clone3() example.
 * These tests are assuming to be running in the host's
 * PID namespace.
 */

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <sys/un.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>
#समावेश <sched.h>

#समावेश "../kselftest.h"
#समावेश "clone3_selftests.h"

#अगर_अघोषित MAX_PID_NS_LEVEL
#घोषणा MAX_PID_NS_LEVEL 32
#पूर्ण_अगर

अटल पूर्णांक pipe_1[2];
अटल पूर्णांक pipe_2[2];

अटल व्योम child_निकास(पूर्णांक ret)
अणु
	ख_साफ(मानक_निकास);
	ख_साफ(मानक_त्रुटि);
	_निकास(ret);
पूर्ण

अटल पूर्णांक call_clone3_set_tid(pid_t *set_tid,
			       माप_प्रकार set_tid_size,
			       पूर्णांक flags,
			       पूर्णांक expected_pid,
			       bool रुको_क्रम_it)
अणु
	पूर्णांक status;
	pid_t pid = -1;

	काष्ठा __clone_args args = अणु
		.flags = flags,
		.निकास_संकेत = SIGCHLD,
		.set_tid = ptr_to_u64(set_tid),
		.set_tid_size = set_tid_size,
	पूर्ण;

	pid = sys_clone3(&args, माप(args));
	अगर (pid < 0) अणु
		ksft_prपूर्णांक_msg("%s - Failed to create new process\n",
			       म_त्रुटि(त्रुटि_सं));
		वापस -त्रुटि_सं;
	पूर्ण

	अगर (pid == 0) अणु
		पूर्णांक ret;
		अक्षर पंचांगp = 0;
		पूर्णांक निकास_code = निकास_सफल;

		ksft_prपूर्णांक_msg("I am the child, my PID is %d (expected %d)\n",
			       getpid(), set_tid[0]);
		अगर (रुको_क्रम_it) अणु
			ksft_prपूर्णांक_msg("[%d] Child is ready and waiting\n",
				       getpid());

			/* Signal the parent that the child is पढ़ोy */
			बंद(pipe_1[0]);
			ret = ग_लिखो(pipe_1[1], &पंचांगp, 1);
			अगर (ret != 1) अणु
				ksft_prपूर्णांक_msg(
					"Writing to pipe returned %d", ret);
				निकास_code = निकास_त्रुटि;
			पूर्ण
			बंद(pipe_1[1]);
			बंद(pipe_2[1]);
			ret = पढ़ो(pipe_2[0], &पंचांगp, 1);
			अगर (ret != 1) अणु
				ksft_prपूर्णांक_msg(
					"Reading from pipe returned %d", ret);
				निकास_code = निकास_त्रुटि;
			पूर्ण
			बंद(pipe_2[0]);
		पूर्ण

		अगर (set_tid[0] != getpid())
			child_निकास(निकास_त्रुटि);
		child_निकास(निकास_code);
	पूर्ण

	अगर (expected_pid == 0 || expected_pid == pid) अणु
		ksft_prपूर्णांक_msg("I am the parent (%d). My child's pid is %d\n",
			       getpid(), pid);
	पूर्ण अन्यथा अणु
		ksft_prपूर्णांक_msg(
			"Expected child pid %d does not match actual pid %d\n",
			expected_pid, pid);
		वापस -1;
	पूर्ण

	अगर (रुकोpid(pid, &status, 0) < 0) अणु
		ksft_prपूर्णांक_msg("Child returned %s\n", म_त्रुटि(त्रुटि_सं));
		वापस -त्रुटि_सं;
	पूर्ण

	अगर (!WIFEXITED(status))
		वापस -1;

	वापस WEXITSTATUS(status);
पूर्ण

अटल व्योम test_clone3_set_tid(pid_t *set_tid,
				माप_प्रकार set_tid_size,
				पूर्णांक flags,
				पूर्णांक expected,
				पूर्णांक expected_pid,
				bool रुको_क्रम_it)
अणु
	पूर्णांक ret;

	ksft_prपूर्णांक_msg(
		"[%d] Trying clone3() with CLONE_SET_TID to %d and 0x%x\n",
		getpid(), set_tid[0], flags);
	ret = call_clone3_set_tid(set_tid, set_tid_size, flags, expected_pid,
				  रुको_क्रम_it);
	ksft_prपूर्णांक_msg(
		"[%d] clone3() with CLONE_SET_TID %d says :%d - expected %d\n",
		getpid(), set_tid[0], ret, expected);
	अगर (ret != expected)
		ksft_test_result_fail(
			"[%d] Result (%d) is different than expected (%d)\n",
			getpid(), ret, expected);
	अन्यथा
		ksft_test_result_pass(
			"[%d] Result (%d) matches expectation (%d)\n",
			getpid(), ret, expected);
पूर्ण
पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	खाता *f;
	अक्षर buf;
	अक्षर *line;
	पूर्णांक status;
	पूर्णांक ret = -1;
	माप_प्रकार len = 0;
	पूर्णांक pid_max = 0;
	uid_t uid = getuid();
	अक्षर proc_path[100] = अणु0पूर्ण;
	pid_t pid, ns1, ns2, ns3, ns_pid;
	pid_t set_tid[MAX_PID_NS_LEVEL * 2];

	ksft_prपूर्णांक_header();
	ksft_set_plan(29);
	test_clone3_supported();

	अगर (pipe(pipe_1) < 0 || pipe(pipe_2) < 0)
		ksft_निकास_fail_msg("pipe() failed\n");

	f = ख_खोलो("/proc/sys/kernel/pid_max", "r");
	अगर (f == शून्य)
		ksft_निकास_fail_msg(
			"%s - Could not open /proc/sys/kernel/pid_max\n",
			म_त्रुटि(त्रुटि_सं));
	ख_पूछो(f, "%d", &pid_max);
	ख_बंद(f);
	ksft_prपूर्णांक_msg("/proc/sys/kernel/pid_max %d\n", pid_max);

	/* Try invalid settings */
	स_रखो(&set_tid, 0, माप(set_tid));
	test_clone3_set_tid(set_tid, MAX_PID_NS_LEVEL + 1, 0, -EINVAL, 0, 0);

	test_clone3_set_tid(set_tid, MAX_PID_NS_LEVEL * 2, 0, -EINVAL, 0, 0);

	test_clone3_set_tid(set_tid, MAX_PID_NS_LEVEL * 2 + 1, 0,
			-EINVAL, 0, 0);

	test_clone3_set_tid(set_tid, MAX_PID_NS_LEVEL * 42, 0, -EINVAL, 0, 0);

	/*
	 * This can actually work अगर this test running in a MAX_PID_NS_LEVEL - 1
	 * nested PID namespace.
	 */
	test_clone3_set_tid(set_tid, MAX_PID_NS_LEVEL - 1, 0, -EINVAL, 0, 0);

	स_रखो(&set_tid, 0xff, माप(set_tid));
	test_clone3_set_tid(set_tid, MAX_PID_NS_LEVEL + 1, 0, -EINVAL, 0, 0);

	test_clone3_set_tid(set_tid, MAX_PID_NS_LEVEL * 2, 0, -EINVAL, 0, 0);

	test_clone3_set_tid(set_tid, MAX_PID_NS_LEVEL * 2 + 1, 0,
			-EINVAL, 0, 0);

	test_clone3_set_tid(set_tid, MAX_PID_NS_LEVEL * 42, 0, -EINVAL, 0, 0);

	/*
	 * This can actually work अगर this test running in a MAX_PID_NS_LEVEL - 1
	 * nested PID namespace.
	 */
	test_clone3_set_tid(set_tid, MAX_PID_NS_LEVEL - 1, 0, -EINVAL, 0, 0);

	स_रखो(&set_tid, 0, माप(set_tid));
	/* Try with an invalid PID */
	set_tid[0] = 0;
	test_clone3_set_tid(set_tid, 1, 0, -EINVAL, 0, 0);

	set_tid[0] = -1;
	test_clone3_set_tid(set_tid, 1, 0, -EINVAL, 0, 0);

	/* Claim that the set_tid array actually contains 2 elements. */
	test_clone3_set_tid(set_tid, 2, 0, -EINVAL, 0, 0);

	/* Try it in a new PID namespace */
	अगर (uid == 0)
		test_clone3_set_tid(set_tid, 1, CLONE_NEWPID, -EINVAL, 0, 0);
	अन्यथा
		ksft_test_result_skip("Clone3() with set_tid requires root\n");

	/* Try with a valid PID (1) this should वापस -EEXIST. */
	set_tid[0] = 1;
	अगर (uid == 0)
		test_clone3_set_tid(set_tid, 1, 0, -EEXIST, 0, 0);
	अन्यथा
		ksft_test_result_skip("Clone3() with set_tid requires root\n");

	/* Try it in a new PID namespace */
	अगर (uid == 0)
		test_clone3_set_tid(set_tid, 1, CLONE_NEWPID, 0, 0, 0);
	अन्यथा
		ksft_test_result_skip("Clone3() with set_tid requires root\n");

	/* pid_max should fail everywhere */
	set_tid[0] = pid_max;
	test_clone3_set_tid(set_tid, 1, 0, -EINVAL, 0, 0);

	अगर (uid == 0)
		test_clone3_set_tid(set_tid, 1, CLONE_NEWPID, -EINVAL, 0, 0);
	अन्यथा
		ksft_test_result_skip("Clone3() with set_tid requires root\n");

	अगर (uid != 0) अणु
		/*
		 * All reमुख्यing tests require root. Tell the framework
		 * that all those tests are skipped as non-root.
		 */
		ksft_cnt.ksft_xskip += ksft_plan - ksft_test_num();
		जाओ out;
	पूर्ण

	/* Find the current active PID */
	pid = विभाजन();
	अगर (pid == 0) अणु
		ksft_prपूर्णांक_msg("Child has PID %d\n", getpid());
		child_निकास(निकास_सफल);
	पूर्ण
	अगर (रुकोpid(pid, &status, 0) < 0)
		ksft_निकास_fail_msg("Waiting for child %d failed", pid);

	/* After the child has finished, its PID should be मुक्त. */
	set_tid[0] = pid;
	test_clone3_set_tid(set_tid, 1, 0, 0, 0, 0);

	/* This should fail as there is no PID 1 in that namespace */
	test_clone3_set_tid(set_tid, 1, CLONE_NEWPID, -EINVAL, 0, 0);

	/*
	 * Creating a process with PID 1 in the newly created most nested
	 * PID namespace and PID 'pid' in the parent PID namespace. This
	 * needs to work.
	 */
	set_tid[0] = 1;
	set_tid[1] = pid;
	test_clone3_set_tid(set_tid, 2, CLONE_NEWPID, 0, pid, 0);

	ksft_prपूर्णांक_msg("unshare PID namespace\n");
	अगर (unshare(CLONE_NEWPID) == -1)
		ksft_निकास_fail_msg("unshare(CLONE_NEWPID) failed: %s\n",
				म_त्रुटि(त्रुटि_सं));

	set_tid[0] = pid;

	/* This should fail as there is no PID 1 in that namespace */
	test_clone3_set_tid(set_tid, 1, 0, -EINVAL, 0, 0);

	/* Let's create a PID 1 */
	ns_pid = विभाजन();
	अगर (ns_pid == 0) अणु
		/*
		 * This and the next test हालs check that all pid-s are
		 * released on error paths.
		 */
		set_tid[0] = 43;
		set_tid[1] = -1;
		test_clone3_set_tid(set_tid, 2, 0, -EINVAL, 0, 0);

		set_tid[0] = 43;
		set_tid[1] = pid;
		test_clone3_set_tid(set_tid, 2, 0, 0, 43, 0);

		ksft_prपूर्णांक_msg("Child in PID namespace has PID %d\n", getpid());
		set_tid[0] = 2;
		test_clone3_set_tid(set_tid, 1, 0, 0, 2, 0);

		set_tid[0] = 1;
		set_tid[1] = -1;
		set_tid[2] = pid;
		/* This should fail as there is invalid PID at level '1'. */
		test_clone3_set_tid(set_tid, 3, CLONE_NEWPID, -EINVAL, 0, 0);

		set_tid[0] = 1;
		set_tid[1] = 42;
		set_tid[2] = pid;
		/*
		 * This should fail as there are not enough active PID
		 * namespaces. Again assuming this is running in the host's
		 * PID namespace. Not yet nested.
		 */
		test_clone3_set_tid(set_tid, 4, CLONE_NEWPID, -EINVAL, 0, 0);

		/*
		 * This should work and from the parent we should see
		 * something like 'NSpid:	pid	42	1'.
		 */
		test_clone3_set_tid(set_tid, 3, CLONE_NEWPID, 0, 42, true);

		child_निकास(ksft_cnt.ksft_fail);
	पूर्ण

	बंद(pipe_1[1]);
	बंद(pipe_2[0]);
	जबतक (पढ़ो(pipe_1[0], &buf, 1) > 0) अणु
		ksft_prपूर्णांक_msg("[%d] Child is ready and waiting\n", getpid());
		अवरोध;
	पूर्ण

	snम_लिखो(proc_path, माप(proc_path), "/proc/%d/status", pid);
	f = ख_खोलो(proc_path, "r");
	अगर (f == शून्य)
		ksft_निकास_fail_msg(
			"%s - Could not open %s\n",
			म_त्रुटि(त्रुटि_सं), proc_path);

	जबतक (getline(&line, &len, f) != -1) अणु
		अगर (म_माला(line, "NSpid")) अणु
			पूर्णांक i;

			/* Verअगरy that all generated PIDs are as expected. */
			i = माला_पूछो(line, "NSpid:\t%d\t%d\t%d",
				   &ns3, &ns2, &ns1);
			अगर (i != 3) अणु
				ksft_prपूर्णांक_msg(
					"Unexpected 'NSPid:' entry: %s",
					line);
				ns1 = ns2 = ns3 = 0;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	ख_बंद(f);
	मुक्त(line);
	बंद(pipe_2[0]);

	/* Tell the clone3()'d child to finish. */
	ग_लिखो(pipe_2[1], &buf, 1);
	बंद(pipe_2[1]);

	अगर (रुकोpid(ns_pid, &status, 0) < 0) अणु
		ksft_prपूर्णांक_msg("Child returned %s\n", म_त्रुटि(त्रुटि_सं));
		ret = -त्रुटि_सं;
		जाओ out;
	पूर्ण

	अगर (!WIFEXITED(status))
		ksft_test_result_fail("Child error\n");

	ksft_cnt.ksft_pass += 6 - (ksft_cnt.ksft_fail - WEXITSTATUS(status));
	ksft_cnt.ksft_fail = WEXITSTATUS(status);

	अगर (ns3 == pid && ns2 == 42 && ns1 == 1)
		ksft_test_result_pass(
			"PIDs in all namespaces as expected (%d,%d,%d)\n",
			ns3, ns2, ns1);
	अन्यथा
		ksft_test_result_fail(
			"PIDs in all namespaces not as expected (%d,%d,%d)\n",
			ns3, ns2, ns1);
out:
	ret = 0;

	वापस !ret ? ksft_निकास_pass() : ksft_निकास_fail();
पूर्ण
