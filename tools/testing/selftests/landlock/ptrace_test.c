<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Landlock tests - Ptrace
 *
 * Copyright तऊ 2017-2020 Mickaथ+l Salaथञn <mic@digikod.net>
 * Copyright तऊ 2019-2020 ANSSI
 */

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <linux/landlock.h>
#समावेश <संकेत.स>
#समावेश <sys/prctl.h>
#समावेश <sys/ptrace.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

#समावेश "common.h"

अटल व्योम create_करोमुख्य(काष्ठा __test_metadata *स्थिर _metadata)
अणु
	पूर्णांक ruleset_fd;
	काष्ठा landlock_ruleset_attr ruleset_attr = अणु
		.handled_access_fs = LANDLOCK_ACCESS_FS_MAKE_BLOCK,
	पूर्ण;

	ruleset_fd = landlock_create_ruleset(&ruleset_attr,
			माप(ruleset_attr), 0);
	EXPECT_LE(0, ruleset_fd) अणु
		TH_LOG("Failed to create a ruleset: %s", म_त्रुटि(त्रुटि_सं));
	पूर्ण
	EXPECT_EQ(0, prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0));
	EXPECT_EQ(0, landlock_restrict_self(ruleset_fd, 0));
	EXPECT_EQ(0, बंद(ruleset_fd));
पूर्ण

अटल पूर्णांक test_ptrace_पढ़ो(स्थिर pid_t pid)
अणु
	अटल स्थिर अक्षर path_ढाँचा[] = "/proc/%d/environ";
	अक्षर procenv_path[माप(path_ढाँचा) + 10];
	पूर्णांक procenv_path_size, fd;

	procenv_path_size = snम_लिखो(procenv_path, माप(procenv_path),
			path_ढाँचा, pid);
	अगर (procenv_path_size >= माप(procenv_path))
		वापस E2BIG;

	fd = खोलो(procenv_path, O_RDONLY | O_CLOEXEC);
	अगर (fd < 0)
		वापस त्रुटि_सं;
	/*
	 * Mixing error codes from बंद(2) and खोलो(2) should not lead to any
	 * (access type) confusion क्रम this test.
	 */
	अगर (बंद(fd) != 0)
		वापस त्रुटि_सं;
	वापस 0;
पूर्ण

FIXTURE(hierarchy) अणु पूर्ण;

FIXTURE_VARIANT(hierarchy) अणु
	स्थिर bool करोमुख्य_both;
	स्थिर bool करोमुख्य_parent;
	स्थिर bool करोमुख्य_child;
पूर्ण;

/*
 * Test multiple tracing combinations between a parent process P1 and a child
 * process P2.
 *
 * Yama's scoped ptrace is presumed disabled.  If enabled, this optional
 * restriction is enक्रमced in addition to any Landlock check, which means that
 * all P2 requests to trace P1 would be denied.
 */

/*
 *        No करोमुख्य
 *
 *   P1-.               P1 -> P2 : allow
 *       \              P2 -> P1 : allow
 *        'P2
 */
FIXTURE_VARIANT_ADD(hierarchy, allow_without_करोमुख्य) अणु
	.करोमुख्य_both = false,
	.करोमुख्य_parent = false,
	.करोमुख्य_child = false,
पूर्ण;

/*
 *        Child करोमुख्य
 *
 *   P1--.              P1 -> P2 : allow
 *        \             P2 -> P1 : deny
 *        .'-----.
 *        |  P2  |
 *        '------'
 */
FIXTURE_VARIANT_ADD(hierarchy, allow_with_one_करोमुख्य) अणु
	.करोमुख्य_both = false,
	.करोमुख्य_parent = false,
	.करोमुख्य_child = true,
पूर्ण;

/*
 *        Parent करोमुख्य
 * .------.
 * |  P1  --.           P1 -> P2 : deny
 * '------'  \          P2 -> P1 : allow
 *            '
 *            P2
 */
FIXTURE_VARIANT_ADD(hierarchy, deny_with_parent_करोमुख्य) अणु
	.करोमुख्य_both = false,
	.करोमुख्य_parent = true,
	.करोमुख्य_child = false,
पूर्ण;

/*
 *        Parent + child करोमुख्य (siblings)
 * .------.
 * |  P1  ---.          P1 -> P2 : deny
 * '------'   \         P2 -> P1 : deny
 *         .---'--.
 *         |  P2  |
 *         '------'
 */
FIXTURE_VARIANT_ADD(hierarchy, deny_with_sibling_करोमुख्य) अणु
	.करोमुख्य_both = false,
	.करोमुख्य_parent = true,
	.करोमुख्य_child = true,
पूर्ण;

/*
 *         Same करोमुख्य (inherited)
 * .-------------.
 * | P1----.     |      P1 -> P2 : allow
 * |        \    |      P2 -> P1 : allow
 * |         '   |
 * |         P2  |
 * '-------------'
 */
FIXTURE_VARIANT_ADD(hierarchy, allow_sibling_करोमुख्य) अणु
	.करोमुख्य_both = true,
	.करोमुख्य_parent = false,
	.करोमुख्य_child = false,
पूर्ण;

/*
 *         Inherited + child करोमुख्य
 * .-----------------.
 * |  P1----.        |  P1 -> P2 : allow
 * |         \       |  P2 -> P1 : deny
 * |        .-'----. |
 * |        |  P2  | |
 * |        '------' |
 * '-----------------'
 */
FIXTURE_VARIANT_ADD(hierarchy, allow_with_nested_करोमुख्य) अणु
	.करोमुख्य_both = true,
	.करोमुख्य_parent = false,
	.करोमुख्य_child = true,
पूर्ण;

/*
 *         Inherited + parent करोमुख्य
 * .-----------------.
 * |.------.         |  P1 -> P2 : deny
 * ||  P1  ----.     |  P2 -> P1 : allow
 * |'------'    \    |
 * |             '   |
 * |             P2  |
 * '-----------------'
 */
FIXTURE_VARIANT_ADD(hierarchy, deny_with_nested_and_parent_करोमुख्य) अणु
	.करोमुख्य_both = true,
	.करोमुख्य_parent = true,
	.करोमुख्य_child = false,
पूर्ण;

/*
 *         Inherited + parent and child करोमुख्य (siblings)
 * .-----------------.
 * | .------.        |  P1 -> P2 : deny
 * | |  P1  .        |  P2 -> P1 : deny
 * | '------'\       |
 * |          \      |
 * |        .--'---. |
 * |        |  P2  | |
 * |        '------' |
 * '-----------------'
 */
FIXTURE_VARIANT_ADD(hierarchy, deny_with_विभाजनed_करोमुख्य) अणु
	.करोमुख्य_both = true,
	.करोमुख्य_parent = true,
	.करोमुख्य_child = true,
पूर्ण;

FIXTURE_SETUP(hierarchy)
अणु पूर्ण

FIXTURE_TEARDOWN(hierarchy)
अणु पूर्ण

/* Test PTRACE_TRACEME and PTRACE_ATTACH क्रम parent and child. */
TEST_F(hierarchy, trace)
अणु
	pid_t child, parent;
	पूर्णांक status, err_proc_पढ़ो;
	पूर्णांक pipe_child[2], pipe_parent[2];
	अक्षर buf_parent;
	दीर्घ ret;

	/*
	 * Removes all effective and permitted capabilities to not पूर्णांकerfere
	 * with cap_ptrace_access_check() in हाल of PTRACE_MODE_FSCREDS.
	 */
	drop_caps(_metadata);

	parent = getpid();
	ASSERT_EQ(0, pipe2(pipe_child, O_CLOEXEC));
	ASSERT_EQ(0, pipe2(pipe_parent, O_CLOEXEC));
	अगर (variant->करोमुख्य_both) अणु
		create_करोमुख्य(_metadata);
		अगर (!_metadata->passed)
			/* Aborts beक्रमe विभाजनing. */
			वापस;
	पूर्ण

	child = विभाजन();
	ASSERT_LE(0, child);
	अगर (child == 0) अणु
		अक्षर buf_child;

		ASSERT_EQ(0, बंद(pipe_parent[1]));
		ASSERT_EQ(0, बंद(pipe_child[0]));
		अगर (variant->करोमुख्य_child)
			create_करोमुख्य(_metadata);

		/* Waits क्रम the parent to be in a करोमुख्य, अगर any. */
		ASSERT_EQ(1, पढ़ो(pipe_parent[0], &buf_child, 1));

		/* Tests PTRACE_ATTACH and PTRACE_MODE_READ on the parent. */
		err_proc_पढ़ो = test_ptrace_पढ़ो(parent);
		ret = ptrace(PTRACE_ATTACH, parent, शून्य, 0);
		अगर (variant->करोमुख्य_child) अणु
			EXPECT_EQ(-1, ret);
			EXPECT_EQ(EPERM, त्रुटि_सं);
			EXPECT_EQ(EACCES, err_proc_पढ़ो);
		पूर्ण अन्यथा अणु
			EXPECT_EQ(0, ret);
			EXPECT_EQ(0, err_proc_पढ़ो);
		पूर्ण
		अगर (ret == 0) अणु
			ASSERT_EQ(parent, रुकोpid(parent, &status, 0));
			ASSERT_EQ(1, WIFSTOPPED(status));
			ASSERT_EQ(0, ptrace(PTRACE_DETACH, parent, शून्य, 0));
		पूर्ण

		/* Tests child PTRACE_TRACEME. */
		ret = ptrace(PTRACE_TRACEME);
		अगर (variant->करोमुख्य_parent) अणु
			EXPECT_EQ(-1, ret);
			EXPECT_EQ(EPERM, त्रुटि_सं);
		पूर्ण अन्यथा अणु
			EXPECT_EQ(0, ret);
		पूर्ण

		/*
		 * Signals that the PTRACE_ATTACH test is करोne and the
		 * PTRACE_TRACEME test is ongoing.
		 */
		ASSERT_EQ(1, ग_लिखो(pipe_child[1], ".", 1));

		अगर (!variant->करोमुख्य_parent) अणु
			ASSERT_EQ(0, उठाओ(SIGSTOP));
		पूर्ण

		/* Waits क्रम the parent PTRACE_ATTACH test. */
		ASSERT_EQ(1, पढ़ो(pipe_parent[0], &buf_child, 1));
		_निकास(_metadata->passed ? निकास_सफल : निकास_त्रुटि);
		वापस;
	पूर्ण

	ASSERT_EQ(0, बंद(pipe_child[1]));
	ASSERT_EQ(0, बंद(pipe_parent[0]));
	अगर (variant->करोमुख्य_parent)
		create_करोमुख्य(_metadata);

	/* Signals that the parent is in a करोमुख्य, अगर any. */
	ASSERT_EQ(1, ग_लिखो(pipe_parent[1], ".", 1));

	/*
	 * Waits क्रम the child to test PTRACE_ATTACH on the parent and start
	 * testing PTRACE_TRACEME.
	 */
	ASSERT_EQ(1, पढ़ो(pipe_child[0], &buf_parent, 1));

	/* Tests child PTRACE_TRACEME. */
	अगर (!variant->करोमुख्य_parent) अणु
		ASSERT_EQ(child, रुकोpid(child, &status, 0));
		ASSERT_EQ(1, WIFSTOPPED(status));
		ASSERT_EQ(0, ptrace(PTRACE_DETACH, child, शून्य, 0));
	पूर्ण अन्यथा अणु
		/* The child should not be traced by the parent. */
		EXPECT_EQ(-1, ptrace(PTRACE_DETACH, child, शून्य, 0));
		EXPECT_EQ(ESRCH, त्रुटि_सं);
	पूर्ण

	/* Tests PTRACE_ATTACH and PTRACE_MODE_READ on the child. */
	err_proc_पढ़ो = test_ptrace_पढ़ो(child);
	ret = ptrace(PTRACE_ATTACH, child, शून्य, 0);
	अगर (variant->करोमुख्य_parent) अणु
		EXPECT_EQ(-1, ret);
		EXPECT_EQ(EPERM, त्रुटि_सं);
		EXPECT_EQ(EACCES, err_proc_पढ़ो);
	पूर्ण अन्यथा अणु
		EXPECT_EQ(0, ret);
		EXPECT_EQ(0, err_proc_पढ़ो);
	पूर्ण
	अगर (ret == 0) अणु
		ASSERT_EQ(child, रुकोpid(child, &status, 0));
		ASSERT_EQ(1, WIFSTOPPED(status));
		ASSERT_EQ(0, ptrace(PTRACE_DETACH, child, शून्य, 0));
	पूर्ण

	/* Signals that the parent PTRACE_ATTACH test is करोne. */
	ASSERT_EQ(1, ग_लिखो(pipe_parent[1], ".", 1));
	ASSERT_EQ(child, रुकोpid(child, &status, 0));
	अगर (WIFSIGNALED(status) || !WIFEXITED(status) ||
			WEXITSTATUS(status) != निकास_सफल)
		_metadata->passed = 0;
पूर्ण

TEST_HARNESS_MAIN
