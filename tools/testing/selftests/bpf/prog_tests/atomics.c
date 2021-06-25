<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <test_progs.h>

#समावेश "atomics.skel.h"

अटल व्योम test_add(काष्ठा atomics *skel)
अणु
	पूर्णांक err, prog_fd;
	__u32 duration = 0, retval;
	काष्ठा bpf_link *link;

	link = bpf_program__attach(skel->progs.add);
	अगर (CHECK(IS_ERR(link), "attach(add)", "err: %ld\n", PTR_ERR(link)))
		वापस;

	prog_fd = bpf_program__fd(skel->progs.add);
	err = bpf_prog_test_run(prog_fd, 1, शून्य, 0,
				शून्य, शून्य, &retval, &duration);
	अगर (CHECK(err || retval, "test_run add",
		  "err %d errno %d retval %d duration %d\n", err, त्रुटि_सं, retval, duration))
		जाओ cleanup;

	ASSERT_EQ(skel->data->add64_value, 3, "add64_value");
	ASSERT_EQ(skel->bss->add64_result, 1, "add64_result");

	ASSERT_EQ(skel->data->add32_value, 3, "add32_value");
	ASSERT_EQ(skel->bss->add32_result, 1, "add32_result");

	ASSERT_EQ(skel->bss->add_stack_value_copy, 3, "add_stack_value");
	ASSERT_EQ(skel->bss->add_stack_result, 1, "add_stack_result");

	ASSERT_EQ(skel->data->add_noवापस_value, 3, "add_noreturn_value");

cleanup:
	bpf_link__destroy(link);
पूर्ण

अटल व्योम test_sub(काष्ठा atomics *skel)
अणु
	पूर्णांक err, prog_fd;
	__u32 duration = 0, retval;
	काष्ठा bpf_link *link;

	link = bpf_program__attach(skel->progs.sub);
	अगर (CHECK(IS_ERR(link), "attach(sub)", "err: %ld\n", PTR_ERR(link)))
		वापस;

	prog_fd = bpf_program__fd(skel->progs.sub);
	err = bpf_prog_test_run(prog_fd, 1, शून्य, 0,
				शून्य, शून्य, &retval, &duration);
	अगर (CHECK(err || retval, "test_run sub",
		  "err %d errno %d retval %d duration %d\n",
		  err, त्रुटि_सं, retval, duration))
		जाओ cleanup;

	ASSERT_EQ(skel->data->sub64_value, -1, "sub64_value");
	ASSERT_EQ(skel->bss->sub64_result, 1, "sub64_result");

	ASSERT_EQ(skel->data->sub32_value, -1, "sub32_value");
	ASSERT_EQ(skel->bss->sub32_result, 1, "sub32_result");

	ASSERT_EQ(skel->bss->sub_stack_value_copy, -1, "sub_stack_value");
	ASSERT_EQ(skel->bss->sub_stack_result, 1, "sub_stack_result");

	ASSERT_EQ(skel->data->sub_noवापस_value, -1, "sub_noreturn_value");

cleanup:
	bpf_link__destroy(link);
पूर्ण

अटल व्योम test_and(काष्ठा atomics *skel)
अणु
	पूर्णांक err, prog_fd;
	__u32 duration = 0, retval;
	काष्ठा bpf_link *link;

	link = bpf_program__attach(skel->progs.and);
	अगर (CHECK(IS_ERR(link), "attach(and)", "err: %ld\n", PTR_ERR(link)))
		वापस;

	prog_fd = bpf_program__fd(skel->progs.and);
	err = bpf_prog_test_run(prog_fd, 1, शून्य, 0,
				शून्य, शून्य, &retval, &duration);
	अगर (CHECK(err || retval, "test_run and",
		  "err %d errno %d retval %d duration %d\n", err, त्रुटि_सं, retval, duration))
		जाओ cleanup;

	ASSERT_EQ(skel->data->and64_value, 0x010ull << 32, "and64_value");
	ASSERT_EQ(skel->bss->and64_result, 0x110ull << 32, "and64_result");

	ASSERT_EQ(skel->data->and32_value, 0x010, "and32_value");
	ASSERT_EQ(skel->bss->and32_result, 0x110, "and32_result");

	ASSERT_EQ(skel->data->and_noवापस_value, 0x010ull << 32, "and_noreturn_value");
cleanup:
	bpf_link__destroy(link);
पूर्ण

अटल व्योम test_or(काष्ठा atomics *skel)
अणु
	पूर्णांक err, prog_fd;
	__u32 duration = 0, retval;
	काष्ठा bpf_link *link;

	link = bpf_program__attach(skel->progs.or);
	अगर (CHECK(IS_ERR(link), "attach(or)", "err: %ld\n", PTR_ERR(link)))
		वापस;

	prog_fd = bpf_program__fd(skel->progs.or);
	err = bpf_prog_test_run(prog_fd, 1, शून्य, 0,
				शून्य, शून्य, &retval, &duration);
	अगर (CHECK(err || retval, "test_run or",
		  "err %d errno %d retval %d duration %d\n",
		  err, त्रुटि_सं, retval, duration))
		जाओ cleanup;

	ASSERT_EQ(skel->data->or64_value, 0x111ull << 32, "or64_value");
	ASSERT_EQ(skel->bss->or64_result, 0x110ull << 32, "or64_result");

	ASSERT_EQ(skel->data->or32_value, 0x111, "or32_value");
	ASSERT_EQ(skel->bss->or32_result, 0x110, "or32_result");

	ASSERT_EQ(skel->data->or_noवापस_value, 0x111ull << 32, "or_noreturn_value");
cleanup:
	bpf_link__destroy(link);
पूर्ण

अटल व्योम test_xor(काष्ठा atomics *skel)
अणु
	पूर्णांक err, prog_fd;
	__u32 duration = 0, retval;
	काष्ठा bpf_link *link;

	link = bpf_program__attach(skel->progs.xor);
	अगर (CHECK(IS_ERR(link), "attach(xor)", "err: %ld\n", PTR_ERR(link)))
		वापस;

	prog_fd = bpf_program__fd(skel->progs.xor);
	err = bpf_prog_test_run(prog_fd, 1, शून्य, 0,
				शून्य, शून्य, &retval, &duration);
	अगर (CHECK(err || retval, "test_run xor",
		  "err %d errno %d retval %d duration %d\n", err, त्रुटि_सं, retval, duration))
		जाओ cleanup;

	ASSERT_EQ(skel->data->xor64_value, 0x101ull << 32, "xor64_value");
	ASSERT_EQ(skel->bss->xor64_result, 0x110ull << 32, "xor64_result");

	ASSERT_EQ(skel->data->xor32_value, 0x101, "xor32_value");
	ASSERT_EQ(skel->bss->xor32_result, 0x110, "xor32_result");

	ASSERT_EQ(skel->data->xor_noवापस_value, 0x101ull << 32, "xor_nxoreturn_value");
cleanup:
	bpf_link__destroy(link);
पूर्ण

अटल व्योम test_cmpxchg(काष्ठा atomics *skel)
अणु
	पूर्णांक err, prog_fd;
	__u32 duration = 0, retval;
	काष्ठा bpf_link *link;

	link = bpf_program__attach(skel->progs.cmpxchg);
	अगर (CHECK(IS_ERR(link), "attach(cmpxchg)", "err: %ld\n", PTR_ERR(link)))
		वापस;

	prog_fd = bpf_program__fd(skel->progs.cmpxchg);
	err = bpf_prog_test_run(prog_fd, 1, शून्य, 0,
				शून्य, शून्य, &retval, &duration);
	अगर (CHECK(err || retval, "test_run add",
		  "err %d errno %d retval %d duration %d\n", err, त्रुटि_सं, retval, duration))
		जाओ cleanup;

	ASSERT_EQ(skel->data->cmpxchg64_value, 2, "cmpxchg64_value");
	ASSERT_EQ(skel->bss->cmpxchg64_result_fail, 1, "cmpxchg_result_fail");
	ASSERT_EQ(skel->bss->cmpxchg64_result_succeed, 1, "cmpxchg_result_succeed");

	ASSERT_EQ(skel->data->cmpxchg32_value, 2, "lcmpxchg32_value");
	ASSERT_EQ(skel->bss->cmpxchg32_result_fail, 1, "cmpxchg_result_fail");
	ASSERT_EQ(skel->bss->cmpxchg32_result_succeed, 1, "cmpxchg_result_succeed");

cleanup:
	bpf_link__destroy(link);
पूर्ण

अटल व्योम test_xchg(काष्ठा atomics *skel)
अणु
	पूर्णांक err, prog_fd;
	__u32 duration = 0, retval;
	काष्ठा bpf_link *link;

	link = bpf_program__attach(skel->progs.xchg);
	अगर (CHECK(IS_ERR(link), "attach(xchg)", "err: %ld\n", PTR_ERR(link)))
		वापस;

	prog_fd = bpf_program__fd(skel->progs.xchg);
	err = bpf_prog_test_run(prog_fd, 1, शून्य, 0,
				शून्य, शून्य, &retval, &duration);
	अगर (CHECK(err || retval, "test_run add",
		  "err %d errno %d retval %d duration %d\n", err, त्रुटि_सं, retval, duration))
		जाओ cleanup;

	ASSERT_EQ(skel->data->xchg64_value, 2, "xchg64_value");
	ASSERT_EQ(skel->bss->xchg64_result, 1, "xchg64_result");

	ASSERT_EQ(skel->data->xchg32_value, 2, "xchg32_value");
	ASSERT_EQ(skel->bss->xchg32_result, 1, "xchg32_result");

cleanup:
	bpf_link__destroy(link);
पूर्ण

व्योम test_atomics(व्योम)
अणु
	काष्ठा atomics *skel;
	__u32 duration = 0;

	skel = atomics__खोलो_and_load();
	अगर (CHECK(!skel, "skel_load", "atomics skeleton failed\n"))
		वापस;

	अगर (skel->data->skip_tests) अणु
		म_लिखो("%s:SKIP:no ENABLE_ATOMICS_TESTS (missing Clang BPF atomics support)",
		       __func__);
		test__skip();
		जाओ cleanup;
	पूर्ण

	अगर (test__start_subtest("add"))
		test_add(skel);
	अगर (test__start_subtest("sub"))
		test_sub(skel);
	अगर (test__start_subtest("and"))
		test_and(skel);
	अगर (test__start_subtest("or"))
		test_or(skel);
	अगर (test__start_subtest("xor"))
		test_xor(skel);
	अगर (test__start_subtest("cmpxchg"))
		test_cmpxchg(skel);
	अगर (test__start_subtest("xchg"))
		test_xchg(skel);

cleanup:
	atomics__destroy(skel);
पूर्ण
