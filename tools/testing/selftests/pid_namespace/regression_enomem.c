<शैली गुरु>
#घोषणा _GNU_SOURCE
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <linux/types.h>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <syscall.h>
#समावेश <sys/रुको.h>

#समावेश "../kselftest_harness.h"
#समावेश "../pidfd/pidfd.h"

/*
 * Regression test क्रम:
 * 35f71bc0a09a ("fork: report pid reservation failure properly")
 * b26ebfe12f34 ("pid: Fix error return value in some cases")
 */
TEST(regression_enomem)
अणु
	pid_t pid;

	अगर (geteuid())
		EXPECT_EQ(0, unshare(CLONE_NEWUSER));

	EXPECT_EQ(0, unshare(CLONE_NEWPID));

	pid = विभाजन();
	ASSERT_GE(pid, 0);

	अगर (pid == 0)
		निकास(निकास_सफल);

	EXPECT_EQ(0, रुको_क्रम_pid(pid));

	pid = विभाजन();
	ASSERT_LT(pid, 0);
	ASSERT_EQ(त्रुटि_सं, ENOMEM);
पूर्ण

TEST_HARNESS_MAIN
