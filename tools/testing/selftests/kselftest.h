<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * kselftest.h:	low-level kselftest framework to include from
 *		selftest programs. When possible, please use
 *		kselftest_harness.h instead.
 *
 * Copyright (c) 2014 Shuah Khan <shuahkh@osg.samsung.com>
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * Using this API consists of first counting how many tests your code
 * has to run, and then starting up the reporting:
 *
 *     ksft_prपूर्णांक_header();
 *     ksft_set_plan(total_number_of_tests);
 *
 * For each test, report any progress, debugging, etc with:
 *
 *     ksft_prपूर्णांक_msg(fmt, ...);
 *
 * and finally report the pass/fail/skip/xfail state of the test with one of:
 *
 *     ksft_test_result(condition, fmt, ...);
 *     ksft_test_result_pass(fmt, ...);
 *     ksft_test_result_fail(fmt, ...);
 *     ksft_test_result_skip(fmt, ...);
 *     ksft_test_result_xfail(fmt, ...);
 *     ksft_test_result_error(fmt, ...);
 *
 * When all tests are finished, clean up and निकास the program with one of:
 *
 *    ksft_निकास(condition);
 *    ksft_निकास_pass();
 *    ksft_निकास_fail();
 *
 * If the program wants to report details on why the entire program has
 * failed, it can instead निकास with a message (this is usually करोne when
 * the program is पातing beक्रमe finishing all tests):
 *
 *    ksft_निकास_fail_msg(fmt, ...);
 *
 */
#अगर_अघोषित __KSELFTEST_H
#घोषणा __KSELFTEST_H

#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <मानकतर्क.स>
#समावेश <मानकपन.स>

/* define kselftest निकास codes */
#घोषणा KSFT_PASS  0
#घोषणा KSFT_FAIL  1
#घोषणा KSFT_XFAIL 2
#घोषणा KSFT_XPASS 3
#घोषणा KSFT_SKIP  4

/* counters */
काष्ठा ksft_count अणु
	अचिन्हित पूर्णांक ksft_pass;
	अचिन्हित पूर्णांक ksft_fail;
	अचिन्हित पूर्णांक ksft_xfail;
	अचिन्हित पूर्णांक ksft_xpass;
	अचिन्हित पूर्णांक ksft_xskip;
	अचिन्हित पूर्णांक ksft_error;
पूर्ण;

अटल काष्ठा ksft_count ksft_cnt;
अटल अचिन्हित पूर्णांक ksft_plan;

अटल अंतरभूत अचिन्हित पूर्णांक ksft_test_num(व्योम)
अणु
	वापस ksft_cnt.ksft_pass + ksft_cnt.ksft_fail +
		ksft_cnt.ksft_xfail + ksft_cnt.ksft_xpass +
		ksft_cnt.ksft_xskip + ksft_cnt.ksft_error;
पूर्ण

अटल अंतरभूत व्योम ksft_inc_pass_cnt(व्योम) अणु ksft_cnt.ksft_pass++; पूर्ण
अटल अंतरभूत व्योम ksft_inc_fail_cnt(व्योम) अणु ksft_cnt.ksft_fail++; पूर्ण
अटल अंतरभूत व्योम ksft_inc_xfail_cnt(व्योम) अणु ksft_cnt.ksft_xfail++; पूर्ण
अटल अंतरभूत व्योम ksft_inc_xpass_cnt(व्योम) अणु ksft_cnt.ksft_xpass++; पूर्ण
अटल अंतरभूत व्योम ksft_inc_xskip_cnt(व्योम) अणु ksft_cnt.ksft_xskip++; पूर्ण
अटल अंतरभूत व्योम ksft_inc_error_cnt(व्योम) अणु ksft_cnt.ksft_error++; पूर्ण

अटल अंतरभूत पूर्णांक ksft_get_pass_cnt(व्योम) अणु वापस ksft_cnt.ksft_pass; पूर्ण
अटल अंतरभूत पूर्णांक ksft_get_fail_cnt(व्योम) अणु वापस ksft_cnt.ksft_fail; पूर्ण
अटल अंतरभूत पूर्णांक ksft_get_xfail_cnt(व्योम) अणु वापस ksft_cnt.ksft_xfail; पूर्ण
अटल अंतरभूत पूर्णांक ksft_get_xpass_cnt(व्योम) अणु वापस ksft_cnt.ksft_xpass; पूर्ण
अटल अंतरभूत पूर्णांक ksft_get_xskip_cnt(व्योम) अणु वापस ksft_cnt.ksft_xskip; पूर्ण
अटल अंतरभूत पूर्णांक ksft_get_error_cnt(व्योम) अणु वापस ksft_cnt.ksft_error; पूर्ण

अटल अंतरभूत व्योम ksft_prपूर्णांक_header(व्योम)
अणु
	अगर (!(दो_पर्या("KSFT_TAP_LEVEL")))
		म_लिखो("TAP version 13\n");
पूर्ण

अटल अंतरभूत व्योम ksft_set_plan(अचिन्हित पूर्णांक plan)
अणु
	ksft_plan = plan;
	म_लिखो("1..%d\n", ksft_plan);
पूर्ण

अटल अंतरभूत व्योम ksft_prपूर्णांक_cnts(व्योम)
अणु
	अगर (ksft_plan != ksft_test_num())
		म_लिखो("# Planned tests != run tests (%u != %u)\n",
			ksft_plan, ksft_test_num());
	म_लिखो("# Totals: pass:%d fail:%d xfail:%d xpass:%d skip:%d error:%d\n",
		ksft_cnt.ksft_pass, ksft_cnt.ksft_fail,
		ksft_cnt.ksft_xfail, ksft_cnt.ksft_xpass,
		ksft_cnt.ksft_xskip, ksft_cnt.ksft_error);
पूर्ण

अटल अंतरभूत व्योम ksft_prपूर्णांक_msg(स्थिर अक्षर *msg, ...)
अणु
	पूर्णांक saved_त्रुटि_सं = त्रुटि_सं;
	बहु_सूची args;

	बहु_शुरू(args, msg);
	म_लिखो("# ");
	त्रुटि_सं = saved_त्रुटि_सं;
	भ_लिखो(msg, args);
	बहु_पूर्ण(args);
पूर्ण

अटल अंतरभूत व्योम ksft_test_result_pass(स्थिर अक्षर *msg, ...)
अणु
	पूर्णांक saved_त्रुटि_सं = त्रुटि_सं;
	बहु_सूची args;

	ksft_cnt.ksft_pass++;

	बहु_शुरू(args, msg);
	म_लिखो("ok %d ", ksft_test_num());
	त्रुटि_सं = saved_त्रुटि_सं;
	भ_लिखो(msg, args);
	बहु_पूर्ण(args);
पूर्ण

अटल अंतरभूत व्योम ksft_test_result_fail(स्थिर अक्षर *msg, ...)
अणु
	पूर्णांक saved_त्रुटि_सं = त्रुटि_सं;
	बहु_सूची args;

	ksft_cnt.ksft_fail++;

	बहु_शुरू(args, msg);
	म_लिखो("not ok %d ", ksft_test_num());
	त्रुटि_सं = saved_त्रुटि_सं;
	भ_लिखो(msg, args);
	बहु_पूर्ण(args);
पूर्ण

/**
 * ksft_test_result() - Report test success based on truth of condition
 *
 * @condition: अगर true, report test success, otherwise failure.
 */
#घोषणा ksft_test_result(condition, fmt, ...) करो अणु	\
	अगर (!!(condition))				\
		ksft_test_result_pass(fmt, ##__VA_ARGS__);\
	अन्यथा						\
		ksft_test_result_fail(fmt, ##__VA_ARGS__);\
	पूर्ण जबतक (0)

अटल अंतरभूत व्योम ksft_test_result_xfail(स्थिर अक्षर *msg, ...)
अणु
	पूर्णांक saved_त्रुटि_सं = त्रुटि_सं;
	बहु_सूची args;

	ksft_cnt.ksft_xfail++;

	बहु_शुरू(args, msg);
	म_लिखो("ok %d # XFAIL ", ksft_test_num());
	त्रुटि_सं = saved_त्रुटि_सं;
	भ_लिखो(msg, args);
	बहु_पूर्ण(args);
पूर्ण

अटल अंतरभूत व्योम ksft_test_result_skip(स्थिर अक्षर *msg, ...)
अणु
	पूर्णांक saved_त्रुटि_सं = त्रुटि_सं;
	बहु_सूची args;

	ksft_cnt.ksft_xskip++;

	बहु_शुरू(args, msg);
	म_लिखो("ok %d # SKIP ", ksft_test_num());
	त्रुटि_सं = saved_त्रुटि_सं;
	भ_लिखो(msg, args);
	बहु_पूर्ण(args);
पूर्ण

/* TODO: how करोes "error" dअगरfer from "fail" or "skip"? */
अटल अंतरभूत व्योम ksft_test_result_error(स्थिर अक्षर *msg, ...)
अणु
	पूर्णांक saved_त्रुटि_सं = त्रुटि_सं;
	बहु_सूची args;

	ksft_cnt.ksft_error++;

	बहु_शुरू(args, msg);
	म_लिखो("not ok %d # error ", ksft_test_num());
	त्रुटि_सं = saved_त्रुटि_सं;
	भ_लिखो(msg, args);
	बहु_पूर्ण(args);
पूर्ण

अटल अंतरभूत पूर्णांक ksft_निकास_pass(व्योम)
अणु
	ksft_prपूर्णांक_cnts();
	निकास(KSFT_PASS);
पूर्ण

अटल अंतरभूत पूर्णांक ksft_निकास_fail(व्योम)
अणु
	ksft_prपूर्णांक_cnts();
	निकास(KSFT_FAIL);
पूर्ण

/**
 * ksft_निकास() - Exit selftest based on truth of condition
 *
 * @condition: अगर true, निकास self test with success, otherwise fail.
 */
#घोषणा ksft_निकास(condition) करो अणु	\
	अगर (!!(condition))		\
		ksft_निकास_pass();	\
	अन्यथा				\
		ksft_निकास_fail();	\
	पूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक ksft_निकास_fail_msg(स्थिर अक्षर *msg, ...)
अणु
	पूर्णांक saved_त्रुटि_सं = त्रुटि_सं;
	बहु_सूची args;

	बहु_शुरू(args, msg);
	म_लिखो("Bail out! ");
	त्रुटि_सं = saved_त्रुटि_सं;
	भ_लिखो(msg, args);
	बहु_पूर्ण(args);

	ksft_prपूर्णांक_cnts();
	निकास(KSFT_FAIL);
पूर्ण

अटल अंतरभूत पूर्णांक ksft_निकास_xfail(व्योम)
अणु
	ksft_prपूर्णांक_cnts();
	निकास(KSFT_XFAIL);
पूर्ण

अटल अंतरभूत पूर्णांक ksft_निकास_xpass(व्योम)
अणु
	ksft_prपूर्णांक_cnts();
	निकास(KSFT_XPASS);
पूर्ण

अटल अंतरभूत पूर्णांक ksft_निकास_skip(स्थिर अक्षर *msg, ...)
अणु
	पूर्णांक saved_त्रुटि_सं = त्रुटि_सं;
	बहु_सूची args;

	बहु_शुरू(args, msg);

	/*
	 * FIXME: several tests misuse ksft_निकास_skip so produce
	 * something sensible अगर some tests have alपढ़ोy been run
	 * or a plan has been prपूर्णांकed.  Those tests should use
	 * ksft_test_result_skip or ksft_निकास_fail_msg instead.
	 */
	अगर (ksft_plan || ksft_test_num()) अणु
		ksft_cnt.ksft_xskip++;
		म_लिखो("ok %d # SKIP ", 1 + ksft_test_num());
	पूर्ण अन्यथा अणु
		म_लिखो("1..0 # SKIP ");
	पूर्ण
	अगर (msg) अणु
		त्रुटि_सं = saved_त्रुटि_सं;
		भ_लिखो(msg, args);
		बहु_पूर्ण(args);
	पूर्ण
	अगर (ksft_test_num())
		ksft_prपूर्णांक_cnts();
	निकास(KSFT_SKIP);
पूर्ण

#पूर्ण_अगर /* __KSELFTEST_H */
