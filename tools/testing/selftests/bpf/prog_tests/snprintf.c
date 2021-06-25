<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Google LLC. */

#समावेश <test_progs.h>
#समावेश "test_snprintf.skel.h"
#समावेश "test_snprintf_single.skel.h"

#घोषणा EXP_NUM_OUT  "-8 9 96 -424242 1337 DABBAD00"
#घोषणा EXP_NUM_RET  माप(EXP_NUM_OUT)

#घोषणा EXP_IP_OUT   "127.000.000.001 0000:0000:0000:0000:0000:0000:0000:0001"
#घोषणा EXP_IP_RET   माप(EXP_IP_OUT)

/* The third specअगरier, %pB, depends on compiler inlining so करोn't check it */
#घोषणा EXP_SYM_OUT  "schedule schedule+0x0/"
#घोषणा MIN_SYM_RET  माप(EXP_SYM_OUT)

/* The third specअगरier, %p, is a hashed poपूर्णांकer which changes on every reboot */
#घोषणा EXP_ADDR_OUT "0000000000000000 ffff00000add4e55 "
#घोषणा EXP_ADDR_RET माप(EXP_ADDR_OUT "unknownhashedptr")

#घोषणा EXP_STR_OUT  "str1 longstr"
#घोषणा EXP_STR_RET  माप(EXP_STR_OUT)

#घोषणा EXP_OVER_OUT "%over"
#घोषणा EXP_OVER_RET 10

#घोषणा EXP_PAD_OUT "    4 000"
#घोषणा EXP_PAD_RET 900007

#घोषणा EXP_NO_ARG_OUT "simple case"
#घोषणा EXP_NO_ARG_RET 12

#घोषणा EXP_NO_BUF_RET 29

व्योम test_snम_लिखो_positive(व्योम)
अणु
	अक्षर exp_addr_out[] = EXP_ADDR_OUT;
	अक्षर exp_sym_out[]  = EXP_SYM_OUT;
	काष्ठा test_snम_लिखो *skel;

	skel = test_snम_लिखो__खोलो_and_load();
	अगर (!ASSERT_OK_PTR(skel, "skel_open"))
		वापस;

	skel->bss->pid = getpid();

	अगर (!ASSERT_OK(test_snम_लिखो__attach(skel), "skel_attach"))
		जाओ cleanup;

	/* trigger tracepoपूर्णांक */
	usleep(1);

	ASSERT_STREQ(skel->bss->num_out, EXP_NUM_OUT, "num_out");
	ASSERT_EQ(skel->bss->num_ret, EXP_NUM_RET, "num_ret");

	ASSERT_STREQ(skel->bss->ip_out, EXP_IP_OUT, "ip_out");
	ASSERT_EQ(skel->bss->ip_ret, EXP_IP_RET, "ip_ret");

	ASSERT_OK(स_भेद(skel->bss->sym_out, exp_sym_out,
			 माप(exp_sym_out) - 1), "sym_out");
	ASSERT_LT(MIN_SYM_RET, skel->bss->sym_ret, "sym_ret");

	ASSERT_OK(स_भेद(skel->bss->addr_out, exp_addr_out,
			 माप(exp_addr_out) - 1), "addr_out");
	ASSERT_EQ(skel->bss->addr_ret, EXP_ADDR_RET, "addr_ret");

	ASSERT_STREQ(skel->bss->str_out, EXP_STR_OUT, "str_out");
	ASSERT_EQ(skel->bss->str_ret, EXP_STR_RET, "str_ret");

	ASSERT_STREQ(skel->bss->over_out, EXP_OVER_OUT, "over_out");
	ASSERT_EQ(skel->bss->over_ret, EXP_OVER_RET, "over_ret");

	ASSERT_STREQ(skel->bss->pad_out, EXP_PAD_OUT, "pad_out");
	ASSERT_EQ(skel->bss->pad_ret, EXP_PAD_RET, "pad_ret");

	ASSERT_STREQ(skel->bss->noarg_out, EXP_NO_ARG_OUT, "no_arg_out");
	ASSERT_EQ(skel->bss->noarg_ret, EXP_NO_ARG_RET, "no_arg_ret");

	ASSERT_EQ(skel->bss->nobuf_ret, EXP_NO_BUF_RET, "no_buf_ret");

cleanup:
	test_snम_लिखो__destroy(skel);
पूर्ण

#घोषणा min(a, b) ((a) < (b) ? (a) : (b))

/* Loads an eBPF object calling bpf_snम_लिखो with up to 10 अक्षरacters of fmt */
अटल पूर्णांक load_single_snम_लिखो(अक्षर *fmt)
अणु
	काष्ठा test_snम_लिखो_single *skel;
	पूर्णांक ret;

	skel = test_snम_लिखो_single__खोलो();
	अगर (!skel)
		वापस -EINVAL;

	स_नकल(skel->rodata->fmt, fmt, min(म_माप(fmt) + 1, 10));

	ret = test_snम_लिखो_single__load(skel);
	test_snम_लिखो_single__destroy(skel);

	वापस ret;
पूर्ण

व्योम test_snम_लिखो_negative(व्योम)
अणु
	ASSERT_OK(load_single_snम_लिखो("valid %d"), "valid usage");

	ASSERT_ERR(load_single_snम_लिखो("0123456789"), "no terminating zero");
	ASSERT_ERR(load_single_snम_लिखो("%d %d"), "too many specifiers");
	ASSERT_ERR(load_single_snम_लिखो("%pi5"), "invalid specifier 1");
	ASSERT_ERR(load_single_snम_लिखो("%a"), "invalid specifier 2");
	ASSERT_ERR(load_single_snम_लिखो("%"), "invalid specifier 3");
	ASSERT_ERR(load_single_snम_लिखो("%12345678"), "invalid specifier 4");
	ASSERT_ERR(load_single_snम_लिखो("%--------"), "invalid specifier 5");
	ASSERT_ERR(load_single_snम_लिखो("\x80"), "non ascii character");
	ASSERT_ERR(load_single_snम_लिखो("\x1"), "non printable character");
पूर्ण

व्योम test_snम_लिखो(व्योम)
अणु
	अगर (test__start_subtest("snprintf_positive"))
		test_snम_लिखो_positive();
	अगर (test__start_subtest("snprintf_negative"))
		test_snम_लिखो_negative();
पूर्ण
