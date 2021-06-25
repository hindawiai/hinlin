<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Carlos Neira cneirabustos@gmail.com */

#घोषणा _GNU_SOURCE
#समावेश <test_progs.h>
#समावेश "test_ns_current_pid_tgid.skel.h"
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <unistd.h>
#समावेश <sys/syscall.h>
#समावेश <sched.h>
#समावेश <sys/रुको.h>
#समावेश <sys/mount.h>
#समावेश <sys/fcntl.h>

#घोषणा STACK_SIZE (1024 * 1024)
अटल अक्षर child_stack[STACK_SIZE];

अटल पूर्णांक test_current_pid_tgid(व्योम *args)
अणु
	काष्ठा test_ns_current_pid_tgid__bss  *bss;
	काष्ठा test_ns_current_pid_tgid *skel;
	पूर्णांक err = -1, duration = 0;
	pid_t tgid, pid;
	काष्ठा stat st;

	skel = test_ns_current_pid_tgid__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open_load", "failed to load skeleton\n"))
		जाओ cleanup;

	pid = syscall(SYS_gettid);
	tgid = getpid();

	err = stat("/proc/self/ns/pid", &st);
	अगर (CHECK(err, "stat", "failed /proc/self/ns/pid: %d\n", err))
		जाओ cleanup;

	bss = skel->bss;
	bss->dev = st.st_dev;
	bss->ino = st.st_ino;
	bss->user_pid = 0;
	bss->user_tgid = 0;

	err = test_ns_current_pid_tgid__attach(skel);
	अगर (CHECK(err, "skel_attach", "skeleton attach failed: %d\n", err))
		जाओ cleanup;

	/* trigger tracepoपूर्णांक */
	usleep(1);
	ASSERT_EQ(bss->user_pid, pid, "pid");
	ASSERT_EQ(bss->user_tgid, tgid, "tgid");
	err = 0;

cleanup:
	 test_ns_current_pid_tgid__destroy(skel);

	वापस err;
पूर्ण

अटल व्योम test_ns_current_pid_tgid_new_ns(व्योम)
अणु
	पूर्णांक wstatus, duration = 0;
	pid_t cpid;

	/* Create a process in a new namespace, this process
	 * will be the init process of this new namespace hence will be pid 1.
	 */
	cpid = clone(test_current_pid_tgid, child_stack + STACK_SIZE,
		     CLONE_NEWPID | SIGCHLD, शून्य);

	अगर (CHECK(cpid == -1, "clone", "%s\n", म_त्रुटि(त्रुटि_सं)))
		वापस;

	अगर (CHECK(रुकोpid(cpid, &wstatus, 0) == -1, "waitpid", "%s\n", म_त्रुटि(त्रुटि_सं)))
		वापस;

	अगर (CHECK(WEXITSTATUS(wstatus) != 0, "newns_pidtgid", "failed"))
		वापस;
पूर्ण

व्योम test_ns_current_pid_tgid(व्योम)
अणु
	अगर (test__start_subtest("ns_current_pid_tgid_root_ns"))
		test_current_pid_tgid(शून्य);
	अगर (test__start_subtest("ns_current_pid_tgid_new_ns"))
		test_ns_current_pid_tgid_new_ns();
पूर्ण
