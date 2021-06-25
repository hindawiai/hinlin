<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */

#घोषणा _GNU_SOURCE         /* See feature_test_macros(7) */
#समावेश <unistd.h>
#समावेश <sys/syscall.h>   /* For SYS_xxx definitions */
#समावेश <sys/types.h>
#समावेश <test_progs.h>
#समावेश "task_local_storage.skel.h"
#समावेश "task_local_storage_exit_creds.skel.h"
#समावेश "task_ls_recursion.skel.h"

अटल व्योम test_sys_enter_निकास(व्योम)
अणु
	काष्ठा task_local_storage *skel;
	पूर्णांक err;

	skel = task_local_storage__खोलो_and_load();
	अगर (!ASSERT_OK_PTR(skel, "skel_open_and_load"))
		वापस;

	skel->bss->target_pid = syscall(SYS_gettid);

	err = task_local_storage__attach(skel);
	अगर (!ASSERT_OK(err, "skel_attach"))
		जाओ out;

	syscall(SYS_gettid);
	syscall(SYS_gettid);

	/* 3x syscalls: 1x attach and 2x gettid */
	ASSERT_EQ(skel->bss->enter_cnt, 3, "enter_cnt");
	ASSERT_EQ(skel->bss->निकास_cnt, 3, "exit_cnt");
	ASSERT_EQ(skel->bss->mismatch_cnt, 0, "mismatch_cnt");
out:
	task_local_storage__destroy(skel);
पूर्ण

अटल व्योम test_निकास_creds(व्योम)
अणु
	काष्ठा task_local_storage_निकास_creds *skel;
	पूर्णांक err;

	skel = task_local_storage_निकास_creds__खोलो_and_load();
	अगर (!ASSERT_OK_PTR(skel, "skel_open_and_load"))
		वापस;

	err = task_local_storage_निकास_creds__attach(skel);
	अगर (!ASSERT_OK(err, "skel_attach"))
		जाओ out;

	/* trigger at least one निकास_creds() */
	अगर (CHECK_FAIL(प्रणाली("ls > /dev/null")))
		जाओ out;

	/* sync rcu to make sure निकास_creds() is called क्रम "ls" */
	kern_sync_rcu();
	ASSERT_EQ(skel->bss->valid_ptr_count, 0, "valid_ptr_count");
	ASSERT_NEQ(skel->bss->null_ptr_count, 0, "null_ptr_count");
out:
	task_local_storage_निकास_creds__destroy(skel);
पूर्ण

अटल व्योम test_recursion(व्योम)
अणु
	काष्ठा task_ls_recursion *skel;
	पूर्णांक err;

	skel = task_ls_recursion__खोलो_and_load();
	अगर (!ASSERT_OK_PTR(skel, "skel_open_and_load"))
		वापस;

	err = task_ls_recursion__attach(skel);
	अगर (!ASSERT_OK(err, "skel_attach"))
		जाओ out;

	/* trigger sys_enter, make sure it करोes not cause deadlock */
	syscall(SYS_gettid);

out:
	task_ls_recursion__destroy(skel);
पूर्ण

व्योम test_task_local_storage(व्योम)
अणु
	अगर (test__start_subtest("sys_enter_exit"))
		test_sys_enter_निकास();
	अगर (test__start_subtest("exit_creds"))
		test_निकास_creds();
	अगर (test__start_subtest("recursion"))
		test_recursion();
पूर्ण
