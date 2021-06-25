<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */
#समावेश <test_progs.h>
#समावेश <network_helpers.h>
#समावेश "kfunc_call_test.skel.h"
#समावेश "kfunc_call_test_subprog.skel.h"

अटल व्योम test_मुख्य(व्योम)
अणु
	काष्ठा kfunc_call_test *skel;
	पूर्णांक prog_fd, retval, err;

	skel = kfunc_call_test__खोलो_and_load();
	अगर (!ASSERT_OK_PTR(skel, "skel"))
		वापस;

	prog_fd = bpf_program__fd(skel->progs.kfunc_call_test1);
	err = bpf_prog_test_run(prog_fd, 1, &pkt_v4, माप(pkt_v4),
				शून्य, शून्य, (__u32 *)&retval, शून्य);
	ASSERT_OK(err, "bpf_prog_test_run(test1)");
	ASSERT_EQ(retval, 12, "test1-retval");

	prog_fd = bpf_program__fd(skel->progs.kfunc_call_test2);
	err = bpf_prog_test_run(prog_fd, 1, &pkt_v4, माप(pkt_v4),
				शून्य, शून्य, (__u32 *)&retval, शून्य);
	ASSERT_OK(err, "bpf_prog_test_run(test2)");
	ASSERT_EQ(retval, 3, "test2-retval");

	kfunc_call_test__destroy(skel);
पूर्ण

अटल व्योम test_subprog(व्योम)
अणु
	काष्ठा kfunc_call_test_subprog *skel;
	पूर्णांक prog_fd, retval, err;

	skel = kfunc_call_test_subprog__खोलो_and_load();
	अगर (!ASSERT_OK_PTR(skel, "skel"))
		वापस;

	prog_fd = bpf_program__fd(skel->progs.kfunc_call_test1);
	err = bpf_prog_test_run(prog_fd, 1, &pkt_v4, माप(pkt_v4),
				शून्य, शून्य, (__u32 *)&retval, शून्य);
	ASSERT_OK(err, "bpf_prog_test_run(test1)");
	ASSERT_EQ(retval, 10, "test1-retval");
	ASSERT_NEQ(skel->data->active_res, -1, "active_res");
	ASSERT_EQ(skel->data->sk_state, BPF_TCP_CLOSE, "sk_state");

	kfunc_call_test_subprog__destroy(skel);
पूर्ण

व्योम test_kfunc_call(व्योम)
अणु
	अगर (test__start_subtest("main"))
		test_मुख्य();

	अगर (test__start_subtest("subprog"))
		test_subprog();
पूर्ण
