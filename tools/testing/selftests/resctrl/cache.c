<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <मानक_निवेशt.h>
#समावेश "resctrl.h"

काष्ठा पढ़ो_क्रमmat अणु
	__u64 nr;			/* The number of events */
	काष्ठा अणु
		__u64 value;		/* The value of the event */
	पूर्ण values[2];
पूर्ण;

अटल काष्ठा perf_event_attr pea_llc_miss;
अटल काष्ठा पढ़ो_क्रमmat rf_cqm;
अटल पूर्णांक fd_lm;
अक्षर llc_occup_path[1024];

अटल व्योम initialize_perf_event_attr(व्योम)
अणु
	pea_llc_miss.type = PERF_TYPE_HARDWARE;
	pea_llc_miss.size = माप(काष्ठा perf_event_attr);
	pea_llc_miss.पढ़ो_क्रमmat = PERF_FORMAT_GROUP;
	pea_llc_miss.exclude_kernel = 1;
	pea_llc_miss.exclude_hv = 1;
	pea_llc_miss.exclude_idle = 1;
	pea_llc_miss.exclude_callchain_kernel = 1;
	pea_llc_miss.inherit = 1;
	pea_llc_miss.exclude_guest = 1;
	pea_llc_miss.disabled = 1;
पूर्ण

अटल व्योम ioctl_perf_event_ioc_reset_enable(व्योम)
अणु
	ioctl(fd_lm, PERF_EVENT_IOC_RESET, 0);
	ioctl(fd_lm, PERF_EVENT_IOC_ENABLE, 0);
पूर्ण

अटल पूर्णांक perf_event_खोलो_llc_miss(pid_t pid, पूर्णांक cpu_no)
अणु
	fd_lm = perf_event_खोलो(&pea_llc_miss, pid, cpu_no, -1,
				PERF_FLAG_FD_CLOEXEC);
	अगर (fd_lm == -1) अणु
		लिखो_त्रुटि("Error opening leader");
		ctrlc_handler(0, शून्य, शून्य);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक initialize_llc_perf(व्योम)
अणु
	स_रखो(&pea_llc_miss, 0, माप(काष्ठा perf_event_attr));
	स_रखो(&rf_cqm, 0, माप(काष्ठा पढ़ो_क्रमmat));

	/* Initialize perf_event_attr काष्ठाures क्रम HW_CACHE_MISSES */
	initialize_perf_event_attr();

	pea_llc_miss.config = PERF_COUNT_HW_CACHE_MISSES;

	rf_cqm.nr = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक reset_enable_llc_perf(pid_t pid, पूर्णांक cpu_no)
अणु
	पूर्णांक ret = 0;

	ret = perf_event_खोलो_llc_miss(pid, cpu_no);
	अगर (ret < 0)
		वापस ret;

	/* Start counters to log values */
	ioctl_perf_event_ioc_reset_enable();

	वापस 0;
पूर्ण

/*
 * get_llc_perf:	llc cache miss through perf events
 * @cpu_no:		CPU number that the benchmark PID is binded to
 *
 * Perf events like HW_CACHE_MISSES could be used to validate number of
 * cache lines allocated.
 *
 * Return: =0 on success.  <0 on failure.
 */
अटल पूर्णांक get_llc_perf(अचिन्हित दीर्घ *llc_perf_miss)
अणु
	__u64 total_misses;

	/* Stop counters after one span to get miss rate */

	ioctl(fd_lm, PERF_EVENT_IOC_DISABLE, 0);

	अगर (पढ़ो(fd_lm, &rf_cqm, माप(काष्ठा पढ़ो_क्रमmat)) == -1) अणु
		लिखो_त्रुटि("Could not get llc misses through perf");

		वापस -1;
	पूर्ण

	total_misses = rf_cqm.values[0].value;

	बंद(fd_lm);

	*llc_perf_miss = total_misses;

	वापस 0;
पूर्ण

/*
 * Get LLC Occupancy as reported by RESCTRL FS
 * For CMT,
 * 1. If con_mon grp and mon grp given, then पढ़ो from mon grp in
 * con_mon grp
 * 2. If only con_mon grp given, then पढ़ो from con_mon grp
 * 3. If both not given, then पढ़ो from root con_mon grp
 * For CAT,
 * 1. If con_mon grp given, then पढ़ो from it
 * 2. If con_mon grp not given, then पढ़ो from root con_mon grp
 *
 * Return: =0 on success.  <0 on failure.
 */
अटल पूर्णांक get_llc_occu_resctrl(अचिन्हित दीर्घ *llc_occupancy)
अणु
	खाता *fp;

	fp = ख_खोलो(llc_occup_path, "r");
	अगर (!fp) अणु
		लिखो_त्रुटि("Failed to open results file");

		वापस त्रुटि_सं;
	पूर्ण
	अगर (ख_पूछो(fp, "%lu", llc_occupancy) <= 0) अणु
		लिखो_त्रुटि("Could not get llc occupancy");
		ख_बंद(fp);

		वापस -1;
	पूर्ण
	ख_बंद(fp);

	वापस 0;
पूर्ण

/*
 * prपूर्णांक_results_cache:	the cache results are stored in a file
 * @filename:		file that stores the results
 * @bm_pid:		child pid that runs benchmark
 * @llc_value:		perf miss value /
 *			llc occupancy value reported by resctrl FS
 *
 * Return:		0 on success. non-zero on failure.
 */
अटल पूर्णांक prपूर्णांक_results_cache(अक्षर *filename, पूर्णांक bm_pid,
			       अचिन्हित दीर्घ llc_value)
अणु
	खाता *fp;

	अगर (म_भेद(filename, "stdio") == 0 || म_भेद(filename, "stderr") == 0) अणु
		म_लिखो("Pid: %d \t LLC_value: %lu\n", bm_pid,
		       llc_value);
	पूर्ण अन्यथा अणु
		fp = ख_खोलो(filename, "a");
		अगर (!fp) अणु
			लिखो_त्रुटि("Cannot open results file");

			वापस त्रुटि_सं;
		पूर्ण
		ख_लिखो(fp, "Pid: %d \t llc_value: %lu\n", bm_pid, llc_value);
		ख_बंद(fp);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक measure_cache_vals(काष्ठा resctrl_val_param *param, पूर्णांक bm_pid)
अणु
	अचिन्हित दीर्घ llc_perf_miss = 0, llc_occu_resc = 0, llc_value = 0;
	पूर्णांक ret;

	/*
	 * Measure cache miss from perf.
	 */
	अगर (!म_भेदन(param->resctrl_val, CAT_STR, माप(CAT_STR))) अणु
		ret = get_llc_perf(&llc_perf_miss);
		अगर (ret < 0)
			वापस ret;
		llc_value = llc_perf_miss;
	पूर्ण

	/*
	 * Measure llc occupancy from resctrl.
	 */
	अगर (!म_भेदन(param->resctrl_val, CMT_STR, माप(CMT_STR))) अणु
		ret = get_llc_occu_resctrl(&llc_occu_resc);
		अगर (ret < 0)
			वापस ret;
		llc_value = llc_occu_resc;
	पूर्ण
	ret = prपूर्णांक_results_cache(param->filename, bm_pid, llc_value);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * cache_val:		execute benchmark and measure LLC occupancy resctrl
 * and perf cache miss क्रम the benchmark
 * @param:		parameters passed to cache_val()
 *
 * Return:		0 on success. non-zero on failure.
 */
पूर्णांक cat_val(काष्ठा resctrl_val_param *param)
अणु
	पूर्णांक दो_स्मृति_and_init_memory = 1, memflush = 1, operation = 0, ret = 0;
	अक्षर *resctrl_val = param->resctrl_val;
	pid_t bm_pid;

	अगर (म_भेद(param->filename, "") == 0)
		प्र_लिखो(param->filename, "stdio");

	bm_pid = getpid();

	/* Taskset benchmark to specअगरied cpu */
	ret = taskset_benchmark(bm_pid, param->cpu_no);
	अगर (ret)
		वापस ret;

	/* Write benchmark to specअगरied con_mon grp, mon_grp in resctrl FS*/
	ret = ग_लिखो_bm_pid_to_resctrl(bm_pid, param->ctrlgrp, param->mongrp,
				      resctrl_val);
	अगर (ret)
		वापस ret;

	अगर (!म_भेदन(resctrl_val, CAT_STR, माप(CAT_STR))) अणु
		ret = initialize_llc_perf();
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Test runs until the callback setup() tells the test to stop. */
	जबतक (1) अणु
		अगर (!म_भेदन(resctrl_val, CAT_STR, माप(CAT_STR))) अणु
			ret = param->setup(1, param);
			अगर (ret) अणु
				ret = 0;
				अवरोध;
			पूर्ण
			ret = reset_enable_llc_perf(bm_pid, param->cpu_no);
			अगर (ret)
				अवरोध;

			अगर (run_fill_buf(param->span, दो_स्मृति_and_init_memory,
					 memflush, operation, resctrl_val)) अणु
				ख_लिखो(मानक_त्रुटि, "Error-running fill buffer\n");
				ret = -1;
				अवरोध;
			पूर्ण

			sleep(1);
			ret = measure_cache_vals(param, bm_pid);
			अगर (ret)
				अवरोध;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * show_cache_info:	show cache test result inक्रमmation
 * @sum_llc_val:	sum of LLC cache result data
 * @no_of_bits:		number of bits
 * @cache_span:		cache span in bytes क्रम CMT or in lines क्रम CAT
 * @max_dअगरf:		max dअगरference
 * @max_dअगरf_percent:	max dअगरference percentage
 * @num_of_runs:	number of runs
 * @platक्रमm:		show test inक्रमmation on this platक्रमm
 * @cmt:		CMT test or CAT test
 *
 * Return:		0 on success. non-zero on failure.
 */
पूर्णांक show_cache_info(अचिन्हित दीर्घ sum_llc_val, पूर्णांक no_of_bits,
		    अचिन्हित दीर्घ cache_span, अचिन्हित दीर्घ max_dअगरf,
		    अचिन्हित दीर्घ max_dअगरf_percent, अचिन्हित दीर्घ num_of_runs,
		    bool platक्रमm, bool cmt)
अणु
	अचिन्हित दीर्घ avg_llc_val = 0;
	भग्न dअगरf_percent;
	दीर्घ avg_dअगरf = 0;
	पूर्णांक ret;

	avg_llc_val = sum_llc_val / (num_of_runs - 1);
	avg_dअगरf = (दीर्घ)असल(cache_span - avg_llc_val);
	dअगरf_percent = ((भग्न)cache_span - avg_llc_val) / cache_span * 100;

	ret = platक्रमm && असल((पूर्णांक)dअगरf_percent) > max_dअगरf_percent &&
	      (cmt ? (असल(avg_dअगरf) > max_dअगरf) : true);

	ksft_prपूर्णांक_msg("%s Check cache miss rate within %d%%\n",
		       ret ? "Fail:" : "Pass:", max_dअगरf_percent);

	ksft_prपूर्णांक_msg("Percent diff=%d\n", असल((पूर्णांक)dअगरf_percent));
	ksft_prपूर्णांक_msg("Number of bits: %d\n", no_of_bits);
	ksft_prपूर्णांक_msg("Average LLC val: %lu\n", avg_llc_val);
	ksft_prपूर्णांक_msg("Cache span (%s): %lu\n", cmt ? "bytes" : "lines",
		       cache_span);

	वापस ret;
पूर्ण
