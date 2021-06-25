<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cache Allocation Technology (CAT) test
 *
 * Copyright (C) 2018 Intel Corporation
 *
 * Authors:
 *    Sai Praneeth Prakhya <sai.praneeth.prakhya@पूर्णांकel.com>,
 *    Fenghua Yu <fenghua.yu@पूर्णांकel.com>
 */
#समावेश "resctrl.h"
#समावेश <unistd.h>

#घोषणा RESULT_खाता_NAME1	"result_cat1"
#घोषणा RESULT_खाता_NAME2	"result_cat2"
#घोषणा NUM_OF_RUNS		5
#घोषणा MAX_DIFF_PERCENT	4
#घोषणा MAX_DIFF		1000000

अटल पूर्णांक count_of_bits;
अटल अक्षर cbm_mask[256];
अटल अचिन्हित दीर्घ दीर्घ_mask;
अटल अचिन्हित दीर्घ cache_size;

/*
 * Change schemata. Write schemata to specअगरied
 * con_mon grp, mon_grp in resctrl FS.
 * Run 5 बार in order to get average values.
 */
अटल पूर्णांक cat_setup(पूर्णांक num, ...)
अणु
	काष्ठा resctrl_val_param *p;
	अक्षर schemata[64];
	बहु_सूची param;
	पूर्णांक ret = 0;

	बहु_शुरू(param, num);
	p = बहु_तर्क(param, काष्ठा resctrl_val_param *);
	बहु_पूर्ण(param);

	/* Run NUM_OF_RUNS बार */
	अगर (p->num_of_runs >= NUM_OF_RUNS)
		वापस -1;

	अगर (p->num_of_runs == 0) अणु
		प्र_लिखो(schemata, "%lx", p->mask);
		ret = ग_लिखो_schemata(p->ctrlgrp, schemata, p->cpu_no,
				     p->resctrl_val);
	पूर्ण
	p->num_of_runs++;

	वापस ret;
पूर्ण

अटल पूर्णांक check_results(काष्ठा resctrl_val_param *param)
अणु
	अक्षर *token_array[8], temp[512];
	अचिन्हित दीर्घ sum_llc_perf_miss = 0;
	पूर्णांक runs = 0, no_of_bits = 0;
	खाता *fp;

	ksft_prपूर्णांक_msg("Checking for pass/fail\n");
	fp = ख_खोलो(param->filename, "r");
	अगर (!fp) अणु
		लिखो_त्रुटि("# Cannot open file");

		वापस त्रुटि_सं;
	पूर्ण

	जबतक (ख_माला_लो(temp, माप(temp), fp)) अणु
		अक्षर *token = म_मोहर(temp, ":\t");
		पूर्णांक fields = 0;

		जबतक (token) अणु
			token_array[fields++] = token;
			token = म_मोहर(शून्य, ":\t");
		पूर्ण
		/*
		 * Discard the first value which is inaccurate due to monitoring
		 * setup transition phase.
		 */
		अगर (runs > 0)
			sum_llc_perf_miss += म_से_अदीर्घ(token_array[3], शून्य, 0);
		runs++;
	पूर्ण

	ख_बंद(fp);
	no_of_bits = count_bits(param->mask);

	वापस show_cache_info(sum_llc_perf_miss, no_of_bits, param->span / 64,
			       MAX_DIFF, MAX_DIFF_PERCENT, NUM_OF_RUNS,
			       !is_amd, false);
पूर्ण

व्योम cat_test_cleanup(व्योम)
अणु
	हटाओ(RESULT_खाता_NAME1);
	हटाओ(RESULT_खाता_NAME2);
पूर्ण

पूर्णांक cat_perf_miss_val(पूर्णांक cpu_no, पूर्णांक n, अक्षर *cache_type)
अणु
	अचिन्हित दीर्घ l_mask, l_mask_1;
	पूर्णांक ret, pipefd[2], sibling_cpu_no;
	अक्षर pipe_message;
	pid_t bm_pid;

	cache_size = 0;

	ret = remount_resctrlfs(true);
	अगर (ret)
		वापस ret;

	/* Get शेष cbm mask क्रम L3/L2 cache */
	ret = get_cbm_mask(cache_type, cbm_mask);
	अगर (ret)
		वापस ret;

	दीर्घ_mask = म_से_अदीर्घ(cbm_mask, शून्य, 16);

	/* Get L3/L2 cache size */
	ret = get_cache_size(cpu_no, cache_type, &cache_size);
	अगर (ret)
		वापस ret;
	ksft_prपूर्णांक_msg("Cache size :%lu\n", cache_size);

	/* Get max number of bits from शेष-cabm mask */
	count_of_bits = count_bits(दीर्घ_mask);

	अगर (!n)
		n = count_of_bits / 2;

	अगर (n > count_of_bits - 1) अणु
		ksft_prपूर्णांक_msg("Invalid input value for no_of_bits n!\n");
		ksft_prपूर्णांक_msg("Please enter value in range 1 to %d\n",
			       count_of_bits - 1);
		वापस -1;
	पूर्ण

	/* Get core id from same socket क्रम running another thपढ़ो */
	sibling_cpu_no = get_core_sibling(cpu_no);
	अगर (sibling_cpu_no < 0)
		वापस -1;

	काष्ठा resctrl_val_param param = अणु
		.resctrl_val	= CAT_STR,
		.cpu_no		= cpu_no,
		.mum_resctrlfs	= 0,
		.setup		= cat_setup,
	पूर्ण;

	l_mask = दीर्घ_mask >> n;
	l_mask_1 = ~l_mask & दीर्घ_mask;

	/* Set param values क्रम parent thपढ़ो which will be allocated biपंचांगask
	 * with (max_bits - n) bits
	 */
	param.span = cache_size * (count_of_bits - n) / count_of_bits;
	म_नकल(param.ctrlgrp, "c2");
	म_नकल(param.mongrp, "m2");
	म_नकल(param.filename, RESULT_खाता_NAME2);
	param.mask = l_mask;
	param.num_of_runs = 0;

	अगर (pipe(pipefd)) अणु
		लिखो_त्रुटि("# Unable to create pipe");
		वापस त्रुटि_सं;
	पूर्ण

	bm_pid = विभाजन();

	/* Set param values क्रम child thपढ़ो which will be allocated biपंचांगask
	 * with n bits
	 */
	अगर (bm_pid == 0) अणु
		param.mask = l_mask_1;
		म_नकल(param.ctrlgrp, "c1");
		म_नकल(param.mongrp, "m1");
		param.span = cache_size * n / count_of_bits;
		म_नकल(param.filename, RESULT_खाता_NAME1);
		param.num_of_runs = 0;
		param.cpu_no = sibling_cpu_no;
	पूर्ण

	हटाओ(param.filename);

	ret = cat_val(&param);
	अगर (ret)
		वापस ret;

	ret = check_results(&param);
	अगर (ret)
		वापस ret;

	अगर (bm_pid == 0) अणु
		/* Tell parent that child is पढ़ोy */
		बंद(pipefd[0]);
		pipe_message = 1;
		अगर (ग_लिखो(pipefd[1], &pipe_message, माप(pipe_message)) <
		    माप(pipe_message)) अणु
			बंद(pipefd[1]);
			लिखो_त्रुटि("# failed signaling parent process");
			वापस त्रुटि_सं;
		पूर्ण

		बंद(pipefd[1]);
		जबतक (1)
			;
	पूर्ण अन्यथा अणु
		/* Parent रुकोs क्रम child to be पढ़ोy. */
		बंद(pipefd[1]);
		pipe_message = 0;
		जबतक (pipe_message != 1) अणु
			अगर (पढ़ो(pipefd[0], &pipe_message,
				 माप(pipe_message)) < माप(pipe_message)) अणु
				लिखो_त्रुटि("# failed reading from child process");
				अवरोध;
			पूर्ण
		पूर्ण
		बंद(pipefd[0]);
		समाप्त(bm_pid, SIGKILL);
	पूर्ण

	cat_test_cleanup();
	अगर (bm_pid)
		umount_resctrlfs();

	वापस 0;
पूर्ण
