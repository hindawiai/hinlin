<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cache Monitoring Technology (CMT) test
 *
 * Copyright (C) 2018 Intel Corporation
 *
 * Authors:
 *    Sai Praneeth Prakhya <sai.praneeth.prakhya@पूर्णांकel.com>,
 *    Fenghua Yu <fenghua.yu@पूर्णांकel.com>
 */
#समावेश "resctrl.h"
#समावेश <unistd.h>

#घोषणा RESULT_खाता_NAME	"result_cmt"
#घोषणा NUM_OF_RUNS		5
#घोषणा MAX_DIFF		2000000
#घोषणा MAX_DIFF_PERCENT	15

अटल पूर्णांक count_of_bits;
अटल अक्षर cbm_mask[256];
अटल अचिन्हित दीर्घ दीर्घ_mask;
अटल अचिन्हित दीर्घ cache_size;

अटल पूर्णांक cmt_setup(पूर्णांक num, ...)
अणु
	काष्ठा resctrl_val_param *p;
	बहु_सूची param;

	बहु_शुरू(param, num);
	p = बहु_तर्क(param, काष्ठा resctrl_val_param *);
	बहु_पूर्ण(param);

	/* Run NUM_OF_RUNS बार */
	अगर (p->num_of_runs >= NUM_OF_RUNS)
		वापस -1;

	p->num_of_runs++;

	वापस 0;
पूर्ण

अटल पूर्णांक check_results(काष्ठा resctrl_val_param *param, पूर्णांक no_of_bits)
अणु
	अक्षर *token_array[8], temp[512];
	अचिन्हित दीर्घ sum_llc_occu_resc = 0;
	पूर्णांक runs = 0;
	खाता *fp;

	ksft_prपूर्णांक_msg("Checking for pass/fail\n");
	fp = ख_खोलो(param->filename, "r");
	अगर (!fp) अणु
		लिखो_त्रुटि("# Error in opening file\n");

		वापस त्रुटि_सं;
	पूर्ण

	जबतक (ख_माला_लो(temp, माप(temp), fp)) अणु
		अक्षर *token = म_मोहर(temp, ":\t");
		पूर्णांक fields = 0;

		जबतक (token) अणु
			token_array[fields++] = token;
			token = म_मोहर(शून्य, ":\t");
		पूर्ण

		/* Field 3 is llc occ resc value */
		अगर (runs > 0)
			sum_llc_occu_resc += म_से_अदीर्घ(token_array[3], शून्य, 0);
		runs++;
	पूर्ण
	ख_बंद(fp);

	वापस show_cache_info(sum_llc_occu_resc, no_of_bits, param->span,
			       MAX_DIFF, MAX_DIFF_PERCENT, NUM_OF_RUNS,
			       true, true);
पूर्ण

व्योम cmt_test_cleanup(व्योम)
अणु
	हटाओ(RESULT_खाता_NAME);
पूर्ण

पूर्णांक cmt_resctrl_val(पूर्णांक cpu_no, पूर्णांक n, अक्षर **benchmark_cmd)
अणु
	पूर्णांक ret, mum_resctrlfs;

	cache_size = 0;
	mum_resctrlfs = 1;

	ret = remount_resctrlfs(mum_resctrlfs);
	अगर (ret)
		वापस ret;

	अगर (!validate_resctrl_feature_request(CMT_STR))
		वापस -1;

	ret = get_cbm_mask("L3", cbm_mask);
	अगर (ret)
		वापस ret;

	दीर्घ_mask = म_से_अदीर्घ(cbm_mask, शून्य, 16);

	ret = get_cache_size(cpu_no, "L3", &cache_size);
	अगर (ret)
		वापस ret;
	ksft_prपूर्णांक_msg("Cache size :%lu\n", cache_size);

	count_of_bits = count_bits(दीर्घ_mask);

	अगर (n < 1 || n > count_of_bits) अणु
		ksft_prपूर्णांक_msg("Invalid input value for numbr_of_bits n!\n");
		ksft_prपूर्णांक_msg("Please enter value in range 1 to %d\n", count_of_bits);
		वापस -1;
	पूर्ण

	काष्ठा resctrl_val_param param = अणु
		.resctrl_val	= CMT_STR,
		.ctrlgrp	= "c1",
		.mongrp		= "m1",
		.cpu_no		= cpu_no,
		.mum_resctrlfs	= 0,
		.filename	= RESULT_खाता_NAME,
		.mask		= ~(दीर्घ_mask << n) & दीर्घ_mask,
		.span		= cache_size * n / count_of_bits,
		.num_of_runs	= 0,
		.setup		= cmt_setup,
	पूर्ण;

	अगर (म_भेद(benchmark_cmd[0], "fill_buf") == 0)
		प्र_लिखो(benchmark_cmd[1], "%lu", param.span);

	हटाओ(RESULT_खाता_NAME);

	ret = resctrl_val(benchmark_cmd, &param);
	अगर (ret)
		वापस ret;

	ret = check_results(&param, n);
	अगर (ret)
		वापस ret;

	cmt_test_cleanup();

	वापस 0;
पूर्ण
