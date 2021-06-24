<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Benchmark synthesis of perf events such as at the start of a 'perf
 * record'. Synthesis is done on the current process and the 'dummy' event
 * handlers are invoked that support dump_trace but otherwise करो nothing.
 *
 * Copyright 2019 Google LLC.
 */
#समावेश <मानकपन.स>
#समावेश "bench.h"
#समावेश "../util/debug.h"
#समावेश "../util/session.h"
#समावेश "../util/stat.h"
#समावेश "../util/synthetic-events.h"
#समावेश "../util/target.h"
#समावेश "../util/thread_map.h"
#समावेश "../util/tool.h"
#समावेश "../util/util.h"
#समावेश <linux/atomic.h>
#समावेश <linux/err.h>
#समावेश <linux/समय64.h>
#समावेश <subcmd/parse-options.h>

अटल अचिन्हित पूर्णांक min_thपढ़ोs = 1;
अटल अचिन्हित पूर्णांक max_thपढ़ोs = अच_पूर्णांक_उच्च;
अटल अचिन्हित पूर्णांक single_iterations = 10000;
अटल अचिन्हित पूर्णांक multi_iterations = 10;
अटल bool run_st;
अटल bool run_mt;

अटल स्थिर काष्ठा option options[] = अणु
	OPT_BOOLEAN('s', "st", &run_st, "Run single threaded benchmark"),
	OPT_BOOLEAN('t', "mt", &run_mt, "Run multi-threaded benchmark"),
	OPT_UINTEGER('m', "min-threads", &min_thपढ़ोs,
		"Minimum number of threads in multithreaded bench"),
	OPT_UINTEGER('M', "max-threads", &max_thपढ़ोs,
		"Maximum number of threads in multithreaded bench"),
	OPT_UINTEGER('i', "single-iterations", &single_iterations,
		"Number of iterations used to compute single-threaded average"),
	OPT_UINTEGER('I', "multi-iterations", &multi_iterations,
		"Number of iterations used to compute multi-threaded average"),
	OPT_END()
पूर्ण;

अटल स्थिर अक्षर *स्थिर bench_usage[] = अणु
	"perf bench internals synthesize <options>",
	शून्य
पूर्ण;

अटल atomic_t event_count;

अटल पूर्णांक process_synthesized_event(काष्ठा perf_tool *tool __maybe_unused,
				     जोड़ perf_event *event __maybe_unused,
				     काष्ठा perf_sample *sample __maybe_unused,
				     काष्ठा machine *machine __maybe_unused)
अणु
	atomic_inc(&event_count);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_run_single_thपढ़ोed(काष्ठा perf_session *session,
				काष्ठा perf_thपढ़ो_map *thपढ़ोs,
				काष्ठा target *target, bool data_mmap)
अणु
	स्थिर अचिन्हित पूर्णांक nr_thपढ़ोs_synthesize = 1;
	काष्ठा समयval start, end, dअगरf;
	u64 runसमय_us;
	अचिन्हित पूर्णांक i;
	द्विगुन समय_average, समय_stddev, event_average, event_stddev;
	पूर्णांक err;
	काष्ठा stats समय_stats, event_stats;

	init_stats(&समय_stats);
	init_stats(&event_stats);

	क्रम (i = 0; i < single_iterations; i++) अणु
		atomic_set(&event_count, 0);
		समय_लोofday(&start, शून्य);
		err = __machine__syntheमाप_प्रकारhपढ़ोs(&session->machines.host,
						शून्य,
						target, thपढ़ोs,
						process_synthesized_event,
						data_mmap,
						nr_thपढ़ोs_synthesize);
		अगर (err)
			वापस err;

		समय_लोofday(&end, शून्य);
		समयrsub(&end, &start, &dअगरf);
		runसमय_us = dअगरf.tv_sec * USEC_PER_SEC + dअगरf.tv_usec;
		update_stats(&समय_stats, runसमय_us);
		update_stats(&event_stats, atomic_पढ़ो(&event_count));
	पूर्ण

	समय_average = avg_stats(&समय_stats);
	समय_stddev = stddev_stats(&समय_stats);
	म_लिखो("  Average %ssynthesis took: %.3f usec (+- %.3f usec)\n",
		data_mmap ? "data " : "", समय_average, समय_stddev);

	event_average = avg_stats(&event_stats);
	event_stddev = stddev_stats(&event_stats);
	म_लिखो("  Average num. events: %.3f (+- %.3f)\n",
		event_average, event_stddev);

	म_लिखो("  Average time per event %.3f usec\n",
		समय_average / event_average);
	वापस 0;
पूर्ण

अटल पूर्णांक run_single_thपढ़ोed(व्योम)
अणु
	काष्ठा perf_session *session;
	काष्ठा target target = अणु
		.pid = "self",
	पूर्ण;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;
	पूर्णांक err;

	perf_set_singlethपढ़ोed();
	session = perf_session__new(शून्य, false, शून्य);
	अगर (IS_ERR(session)) अणु
		pr_err("Session creation failed.\n");
		वापस PTR_ERR(session);
	पूर्ण
	thपढ़ोs = thपढ़ो_map__new_by_pid(getpid());
	अगर (!thपढ़ोs) अणु
		pr_err("Thread map creation failed.\n");
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	माला_दो(
"Computing performance of single threaded perf event synthesis by\n"
"synthesizing events on the perf process itself:");

	err = करो_run_single_thपढ़ोed(session, thपढ़ोs, &target, false);
	अगर (err)
		जाओ err_out;

	err = करो_run_single_thपढ़ोed(session, thपढ़ोs, &target, true);

err_out:
	अगर (thपढ़ोs)
		perf_thपढ़ो_map__put(thपढ़ोs);

	perf_session__delete(session);
	वापस err;
पूर्ण

अटल पूर्णांक करो_run_multi_thपढ़ोed(काष्ठा target *target,
				अचिन्हित पूर्णांक nr_thपढ़ोs_synthesize)
अणु
	काष्ठा समयval start, end, dअगरf;
	u64 runसमय_us;
	अचिन्हित पूर्णांक i;
	द्विगुन समय_average, समय_stddev, event_average, event_stddev;
	पूर्णांक err;
	काष्ठा stats समय_stats, event_stats;
	काष्ठा perf_session *session;

	init_stats(&समय_stats);
	init_stats(&event_stats);
	क्रम (i = 0; i < multi_iterations; i++) अणु
		session = perf_session__new(शून्य, false, शून्य);
		अगर (IS_ERR(session))
			वापस PTR_ERR(session);

		atomic_set(&event_count, 0);
		समय_लोofday(&start, शून्य);
		err = __machine__syntheमाप_प्रकारhपढ़ोs(&session->machines.host,
						शून्य,
						target, शून्य,
						process_synthesized_event,
						false,
						nr_thपढ़ोs_synthesize);
		अगर (err) अणु
			perf_session__delete(session);
			वापस err;
		पूर्ण

		समय_लोofday(&end, शून्य);
		समयrsub(&end, &start, &dअगरf);
		runसमय_us = dअगरf.tv_sec * USEC_PER_SEC + dअगरf.tv_usec;
		update_stats(&समय_stats, runसमय_us);
		update_stats(&event_stats, atomic_पढ़ो(&event_count));
		perf_session__delete(session);
	पूर्ण

	समय_average = avg_stats(&समय_stats);
	समय_stddev = stddev_stats(&समय_stats);
	म_लिखो("    Average synthesis took: %.3f usec (+- %.3f usec)\n",
		समय_average, समय_stddev);

	event_average = avg_stats(&event_stats);
	event_stddev = stddev_stats(&event_stats);
	म_लिखो("    Average num. events: %.3f (+- %.3f)\n",
		event_average, event_stddev);

	म_लिखो("    Average time per event %.3f usec\n",
		समय_average / event_average);
	वापस 0;
पूर्ण

अटल पूर्णांक run_multi_thपढ़ोed(व्योम)
अणु
	काष्ठा target target = अणु
		.cpu_list = "0"
	पूर्ण;
	अचिन्हित पूर्णांक nr_thपढ़ोs_synthesize;
	पूर्णांक err;

	अगर (max_thपढ़ोs == अच_पूर्णांक_उच्च)
		max_thपढ़ोs = sysconf(_SC_NPROCESSORS_ONLN);

	माला_दो(
"Computing performance of multi threaded perf event synthesis by\n"
"synthesizing events on CPU 0:");

	क्रम (nr_thपढ़ोs_synthesize = min_thपढ़ोs;
	     nr_thपढ़ोs_synthesize <= max_thपढ़ोs;
	     nr_thपढ़ोs_synthesize++) अणु
		अगर (nr_thपढ़ोs_synthesize == 1)
			perf_set_singlethपढ़ोed();
		अन्यथा
			perf_set_multithपढ़ोed();

		म_लिखो("  Number of synthesis threads: %u\n",
			nr_thपढ़ोs_synthesize);

		err = करो_run_multi_thपढ़ोed(&target, nr_thपढ़ोs_synthesize);
		अगर (err)
			वापस err;
	पूर्ण
	perf_set_singlethपढ़ोed();
	वापस 0;
पूर्ण

पूर्णांक bench_synthesize(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक err = 0;

	argc = parse_options(argc, argv, options, bench_usage, 0);
	अगर (argc) अणु
		usage_with_options(bench_usage, options);
		निकास(निकास_त्रुटि);
	पूर्ण

	/*
	 * If neither single thपढ़ोed or multi-thपढ़ोed are specअगरied, शेष
	 * to running just single thपढ़ोed.
	 */
	अगर (!run_st && !run_mt)
		run_st = true;

	अगर (run_st)
		err = run_single_thपढ़ोed();

	अगर (!err && run_mt)
		err = run_multi_thपढ़ोed();

	वापस err;
पूर्ण
