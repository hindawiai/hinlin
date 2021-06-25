<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Resctrl tests
 *
 * Copyright (C) 2018 Intel Corporation
 *
 * Authors:
 *    Sai Praneeth Prakhya <sai.praneeth.prakhya@पूर्णांकel.com>,
 *    Fenghua Yu <fenghua.yu@पूर्णांकel.com>
 */
#समावेश "resctrl.h"

#घोषणा BENCHMARK_ARGS		64
#घोषणा BENCHMARK_ARG_SIZE	64

bool is_amd;

व्योम detect_amd(व्योम)
अणु
	खाता *inf = ख_खोलो("/proc/cpuinfo", "r");
	अक्षर *res;

	अगर (!inf)
		वापस;

	res = fgrep(inf, "vendor_id");

	अगर (res) अणु
		अक्षर *s = म_अक्षर(res, ':');

		is_amd = s && !म_भेद(s, ": AuthenticAMD\n");
		मुक्त(res);
	पूर्ण
	ख_बंद(inf);
पूर्ण

अटल व्योम cmd_help(व्योम)
अणु
	म_लिखो("usage: resctrl_tests [-h] [-b \"benchmark_cmd [options]\"] [-t test list] [-n no_of_bits]\n");
	म_लिखो("\t-b benchmark_cmd [options]: run specified benchmark for MBM, MBA and CMT\n");
	म_लिखो("\t   default benchmark is builtin fill_buf\n");
	म_लिखो("\t-t test list: run tests specified in the test list, ");
	म_लिखो("e.g. -t mbm, mba, cmt, cat\n");
	म_लिखो("\t-n no_of_bits: run cache tests using specified no of bits in cache bit mask\n");
	म_लिखो("\t-p cpu_no: specify CPU number to run the test. 1 is default\n");
	म_लिखो("\t-h: help\n");
पूर्ण

व्योम tests_cleanup(व्योम)
अणु
	mbm_test_cleanup();
	mba_test_cleanup();
	cmt_test_cleanup();
	cat_test_cleanup();
पूर्ण

अटल व्योम run_mbm_test(bool has_ben, अक्षर **benchmark_cmd, पूर्णांक span,
			 पूर्णांक cpu_no, अक्षर *bw_report)
अणु
	पूर्णांक res;

	ksft_prपूर्णांक_msg("Starting MBM BW change ...\n");

	अगर (!validate_resctrl_feature_request(MBM_STR)) अणु
		ksft_test_result_skip("Hardware does not support MBM or MBM is disabled\n");
		वापस;
	पूर्ण

	अगर (!has_ben)
		प्र_लिखो(benchmark_cmd[5], "%s", MBA_STR);
	res = mbm_bw_change(span, cpu_no, bw_report, benchmark_cmd);
	ksft_test_result(!res, "MBM: bw change\n");
	mbm_test_cleanup();
पूर्ण

अटल व्योम run_mba_test(bool has_ben, अक्षर **benchmark_cmd, पूर्णांक span,
			 पूर्णांक cpu_no, अक्षर *bw_report)
अणु
	पूर्णांक res;

	ksft_prपूर्णांक_msg("Starting MBA Schemata change ...\n");

	अगर (!validate_resctrl_feature_request(MBA_STR)) अणु
		ksft_test_result_skip("Hardware does not support MBA or MBA is disabled\n");
		वापस;
	पूर्ण

	अगर (!has_ben)
		प्र_लिखो(benchmark_cmd[1], "%d", span);
	res = mba_schemata_change(cpu_no, bw_report, benchmark_cmd);
	ksft_test_result(!res, "MBA: schemata change\n");
	mba_test_cleanup();
पूर्ण

अटल व्योम run_cmt_test(bool has_ben, अक्षर **benchmark_cmd, पूर्णांक cpu_no)
अणु
	पूर्णांक res;

	ksft_prपूर्णांक_msg("Starting CMT test ...\n");
	अगर (!validate_resctrl_feature_request(CMT_STR)) अणु
		ksft_test_result_skip("Hardware does not support CMT or CMT is disabled\n");
		वापस;
	पूर्ण

	अगर (!has_ben)
		प्र_लिखो(benchmark_cmd[5], "%s", CMT_STR);
	res = cmt_resctrl_val(cpu_no, 5, benchmark_cmd);
	ksft_test_result(!res, "CMT: test\n");
	cmt_test_cleanup();
पूर्ण

अटल व्योम run_cat_test(पूर्णांक cpu_no, पूर्णांक no_of_bits)
अणु
	पूर्णांक res;

	ksft_prपूर्णांक_msg("Starting CAT test ...\n");

	अगर (!validate_resctrl_feature_request(CAT_STR)) अणु
		ksft_test_result_skip("Hardware does not support CAT or CAT is disabled\n");
		वापस;
	पूर्ण

	res = cat_perf_miss_val(cpu_no, no_of_bits, "L3");
	ksft_test_result(!res, "CAT: test\n");
	cat_test_cleanup();
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	bool has_ben = false, mbm_test = true, mba_test = true, cmt_test = true;
	पूर्णांक c, cpu_no = 1, span = 250, argc_new = argc, i, no_of_bits = 0;
	अक्षर *benchmark_cmd[BENCHMARK_ARGS], bw_report[64], bm_type[64];
	अक्षर benchmark_cmd_area[BENCHMARK_ARGS][BENCHMARK_ARG_SIZE];
	पूर्णांक ben_ind, ben_count, tests = 0;
	bool cat_test = true;

	क्रम (i = 0; i < argc; i++) अणु
		अगर (म_भेद(argv[i], "-b") == 0) अणु
			ben_ind = i + 1;
			ben_count = argc - ben_ind;
			argc_new = ben_ind - 1;
			has_ben = true;
			अवरोध;
		पूर्ण
	पूर्ण

	जबतक ((c = getopt(argc_new, argv, "ht:b:n:p:")) != -1) अणु
		अक्षर *token;

		चयन (c) अणु
		हाल 't':
			token = म_मोहर(optarg, ",");

			mbm_test = false;
			mba_test = false;
			cmt_test = false;
			cat_test = false;
			जबतक (token) अणु
				अगर (!म_भेदन(token, MBM_STR, माप(MBM_STR))) अणु
					mbm_test = true;
					tests++;
				पूर्ण अन्यथा अगर (!म_भेदन(token, MBA_STR, माप(MBA_STR))) अणु
					mba_test = true;
					tests++;
				पूर्ण अन्यथा अगर (!म_भेदन(token, CMT_STR, माप(CMT_STR))) अणु
					cmt_test = true;
					tests++;
				पूर्ण अन्यथा अगर (!म_भेदन(token, CAT_STR, माप(CAT_STR))) अणु
					cat_test = true;
					tests++;
				पूर्ण अन्यथा अणु
					म_लिखो("invalid argument\n");

					वापस -1;
				पूर्ण
				token = म_मोहर(शून्य, ":\t");
			पूर्ण
			अवरोध;
		हाल 'p':
			cpu_no = म_से_प(optarg);
			अवरोध;
		हाल 'n':
			no_of_bits = म_से_प(optarg);
			अगर (no_of_bits <= 0) अणु
				म_लिखो("Bail out! invalid argument for no_of_bits\n");
				वापस -1;
			पूर्ण
			अवरोध;
		हाल 'h':
			cmd_help();

			वापस 0;
		शेष:
			म_लिखो("invalid argument\n");

			वापस -1;
		पूर्ण
	पूर्ण

	ksft_prपूर्णांक_header();

	/*
	 * Typically we need root privileges, because:
	 * 1. We ग_लिखो to resctrl FS
	 * 2. We execute perf commands
	 */
	अगर (geteuid() != 0)
		वापस ksft_निकास_fail_msg("Not running as root, abort testing.\n");

	/* Detect AMD venकरोr */
	detect_amd();

	अगर (has_ben) अणु
		/* Extract benchmark command from command line. */
		क्रम (i = ben_ind; i < argc; i++) अणु
			benchmark_cmd[i - ben_ind] = benchmark_cmd_area[i];
			प्र_लिखो(benchmark_cmd[i - ben_ind], "%s", argv[i]);
		पूर्ण
		benchmark_cmd[ben_count] = शून्य;
	पूर्ण अन्यथा अणु
		/* If no benchmark is given by "-b" argument, use fill_buf. */
		क्रम (i = 0; i < 6; i++)
			benchmark_cmd[i] = benchmark_cmd_area[i];

		म_नकल(benchmark_cmd[0], "fill_buf");
		प्र_लिखो(benchmark_cmd[1], "%d", span);
		म_नकल(benchmark_cmd[2], "1");
		म_नकल(benchmark_cmd[3], "1");
		म_नकल(benchmark_cmd[4], "0");
		म_नकल(benchmark_cmd[5], "");
		benchmark_cmd[6] = शून्य;
	पूर्ण

	प्र_लिखो(bw_report, "reads");
	प्र_लिखो(bm_type, "fill_buf");

	अगर (!check_resctrlfs_support())
		वापस ksft_निकास_fail_msg("resctrl FS does not exist\n");

	filter_dmesg();

	ksft_set_plan(tests ? : 4);

	अगर (!is_amd && mbm_test)
		run_mbm_test(has_ben, benchmark_cmd, span, cpu_no, bw_report);

	अगर (!is_amd && mba_test)
		run_mba_test(has_ben, benchmark_cmd, span, cpu_no, bw_report);

	अगर (cmt_test)
		run_cmt_test(has_ben, benchmark_cmd, cpu_no);

	अगर (cat_test)
		run_cat_test(cpu_no, no_of_bits);

	umount_resctrlfs();

	वापस ksft_निकास_pass();
पूर्ण
