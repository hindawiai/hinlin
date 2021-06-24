<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2020 Bernd Edlinger <bernd.edlinger@hoपंचांगail.de>
 * All rights reserved.
 *
 * Check whether /proc/$pid/mem can be accessed without causing deadlocks
 * when de_thपढ़ो is blocked with ->cred_guard_mutex held.
 */

#समावेश "../kselftest_harness.h"
#समावेश <मानकपन.स>
#समावेश <fcntl.h>
#समावेश <pthपढ़ो.h>
#समावेश <संकेत.स>
#समावेश <unistd.h>
#समावेश <sys/ptrace.h>

अटल व्योम *thपढ़ो(व्योम *arg)
अणु
	ptrace(PTRACE_TRACEME, 0, 0L, 0L);
	वापस शून्य;
पूर्ण

TEST(vmaccess)
अणु
	पूर्णांक f, pid = विभाजन();
	अक्षर mm[64];

	अगर (!pid) अणु
		pthपढ़ो_t pt;

		pthपढ़ो_create(&pt, शून्य, thपढ़ो, शून्य);
		pthपढ़ो_join(pt, शून्य);
		execlp("true", "true", शून्य);
	पूर्ण

	sleep(1);
	प्र_लिखो(mm, "/proc/%d/mem", pid);
	f = खोलो(mm, O_RDONLY);
	ASSERT_GE(f, 0);
	बंद(f);
	f = समाप्त(pid, SIGCONT);
	ASSERT_EQ(f, 0);
पूर्ण

TEST(attach)
अणु
	पूर्णांक s, k, pid = विभाजन();

	अगर (!pid) अणु
		pthपढ़ो_t pt;

		pthपढ़ो_create(&pt, शून्य, thपढ़ो, शून्य);
		pthपढ़ो_join(pt, शून्य);
		execlp("sleep", "sleep", "2", शून्य);
	पूर्ण

	sleep(1);
	k = ptrace(PTRACE_ATTACH, pid, 0L, 0L);
	ASSERT_EQ(त्रुटि_सं, EAGAIN);
	ASSERT_EQ(k, -1);
	k = रुकोpid(-1, &s, WNOHANG);
	ASSERT_NE(k, -1);
	ASSERT_NE(k, 0);
	ASSERT_NE(k, pid);
	ASSERT_EQ(WIFEXITED(s), 1);
	ASSERT_EQ(WEXITSTATUS(s), 0);
	sleep(1);
	k = ptrace(PTRACE_ATTACH, pid, 0L, 0L);
	ASSERT_EQ(k, 0);
	k = रुकोpid(-1, &s, 0);
	ASSERT_EQ(k, pid);
	ASSERT_EQ(WIFSTOPPED(s), 1);
	ASSERT_EQ(WSTOPSIG(s), SIGSTOP);
	k = ptrace(PTRACE_DETACH, pid, 0L, 0L);
	ASSERT_EQ(k, 0);
	k = रुकोpid(-1, &s, 0);
	ASSERT_EQ(k, pid);
	ASSERT_EQ(WIFEXITED(s), 1);
	ASSERT_EQ(WEXITSTATUS(s), 0);
	k = रुकोpid(-1, शून्य, 0);
	ASSERT_EQ(k, -1);
	ASSERT_EQ(त्रुटि_सं, ECHILD);
पूर्ण

TEST_HARNESS_MAIN
