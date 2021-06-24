<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * builtin-stat.c
 *
 * Builtin stat command: Give a precise perक्रमmance counters summary
 * overview about any workload, CPU or specअगरic PID.
 *
 * Sample output:

   $ perf stat ./hackbench 10

  Time: 0.118

  Perक्रमmance counter stats क्रम './hackbench 10':

       1708.761321 task-घड़ी                #   11.037 CPUs utilized
            41,190 context-चयनes          #    0.024 M/sec
             6,735 CPU-migrations            #    0.004 M/sec
            17,318 page-faults               #    0.010 M/sec
     5,205,202,243 cycles                    #    3.046 GHz
     3,856,436,920 stalled-cycles-frontend   #   74.09% frontend cycles idle
     1,600,790,871 stalled-cycles-backend    #   30.75% backend  cycles idle
     2,603,501,247 inकाष्ठाions              #    0.50  insns per cycle
                                             #    1.48  stalled cycles per insn
       484,357,498 branches                  #  283.455 M/sec
         6,388,934 branch-misses             #    1.32% of all branches

        0.154822978  seconds समय elapsed

 *
 * Copyright (C) 2008-2011, Red Hat Inc, Ingo Molnar <mingo@redhat.com>
 *
 * Improvements and fixes by:
 *
 *   Arjan van de Ven <arjan@linux.पूर्णांकel.com>
 *   Yanmin Zhang <yanmin.zhang@पूर्णांकel.com>
 *   Wu Fengguang <fengguang.wu@पूर्णांकel.com>
 *   Mike Galbraith <efault@gmx.de>
 *   Paul Mackerras <paulus@samba.org>
 *   Jaswinder Singh Rajput <jaswinder@kernel.org>
 */

#समावेश "builtin.h"
#समावेश "perf.h"
#समावेश "util/cgroup.h"
#समावेश <subcmd/parse-options.h>
#समावेश "util/parse-events.h"
#समावेश "util/pmu.h"
#समावेश "util/event.h"
#समावेश "util/evlist.h"
#समावेश "util/evlist-hybrid.h"
#समावेश "util/evsel.h"
#समावेश "util/debug.h"
#समावेश "util/color.h"
#समावेश "util/stat.h"
#समावेश "util/header.h"
#समावेश "util/cpumap.h"
#समावेश "util/thread_map.h"
#समावेश "util/counts.h"
#समावेश "util/topdown.h"
#समावेश "util/session.h"
#समावेश "util/tool.h"
#समावेश "util/string2.h"
#समावेश "util/metricgroup.h"
#समावेश "util/synthetic-events.h"
#समावेश "util/target.h"
#समावेश "util/time-utils.h"
#समावेश "util/top.h"
#समावेश "util/affinity.h"
#समावेश "util/pfm.h"
#समावेश "util/bpf_counter.h"
#समावेश "util/iostat.h"
#समावेश "util/pmu-hybrid.h"
#समावेश "asm/bug.h"

#समावेश <linux/समय64.h>
#समावेश <linux/zभाग.स>
#समावेश <api/fs/fs.h>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <मानककोष.स>
#समावेश <sys/prctl.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <क्षेत्र.स>
#समावेश <गणित.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>
#समावेश <sys/समय.स>
#समावेश <sys/resource.h>
#समावेश <linux/err.h>

#समावेश <linux/प्रकार.स>
#समावेश <perf/evlist.h>

#घोषणा DEFAULT_SEPARATOR	" "
#घोषणा FREEZE_ON_SMI_PATH	"devices/cpu/freeze_on_smi"

अटल व्योम prपूर्णांक_counters(काष्ठा बारpec *ts, पूर्णांक argc, स्थिर अक्षर **argv);

/* Default events used क्रम perf stat -T */
अटल स्थिर अक्षर *transaction_attrs = अणु
	"task-clock,"
	"{"
	"instructions,"
	"cycles,"
	"cpu/cycles-t/,"
	"cpu/tx-start/,"
	"cpu/el-start/,"
	"cpu/cycles-ct/"
	"}"
पूर्ण;

/* More limited version when the CPU करोes not have all events. */
अटल स्थिर अक्षर * transaction_limited_attrs = अणु
	"task-clock,"
	"{"
	"instructions,"
	"cycles,"
	"cpu/cycles-t/,"
	"cpu/tx-start/"
	"}"
पूर्ण;

अटल स्थिर अक्षर * topकरोwn_attrs[] = अणु
	"topdown-total-slots",
	"topdown-slots-retired",
	"topdown-recovery-bubbles",
	"topdown-fetch-bubbles",
	"topdown-slots-issued",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर *topकरोwn_metric_attrs[] = अणु
	"slots",
	"topdown-retiring",
	"topdown-bad-spec",
	"topdown-fe-bound",
	"topdown-be-bound",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर *topकरोwn_metric_L2_attrs[] = अणु
	"slots",
	"topdown-retiring",
	"topdown-bad-spec",
	"topdown-fe-bound",
	"topdown-be-bound",
	"topdown-heavy-ops",
	"topdown-br-mispredict",
	"topdown-fetch-lat",
	"topdown-mem-bound",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर *smi_cost_attrs = अणु
	"{"
	"msr/aperf/,"
	"msr/smi/,"
	"cycles"
	"}"
पूर्ण;

अटल काष्ठा evlist	*evsel_list;
अटल bool all_counters_use_bpf = true;

अटल काष्ठा target target = अणु
	.uid	= अच_पूर्णांक_उच्च,
पूर्ण;

#घोषणा METRIC_ONLY_LEN 20

अटल अस्थिर pid_t		child_pid			= -1;
अटल पूर्णांक			detailed_run			=  0;
अटल bool			transaction_run;
अटल bool			topकरोwn_run			= false;
अटल bool			smi_cost			= false;
अटल bool			smi_reset			= false;
अटल पूर्णांक			big_num_opt			=  -1;
अटल bool			group				= false;
अटल स्थिर अक्षर		*pre_cmd			= शून्य;
अटल स्थिर अक्षर		*post_cmd			= शून्य;
अटल bool			sync_run			= false;
अटल bool			क्रमever				= false;
अटल bool			क्रमce_metric_only		= false;
अटल काष्ठा बारpec		ref_समय;
अटल bool			append_file;
अटल bool			पूर्णांकerval_count;
अटल स्थिर अक्षर		*output_name;
अटल पूर्णांक			output_fd;

काष्ठा perf_stat अणु
	bool			 record;
	काष्ठा perf_data	 data;
	काष्ठा perf_session	*session;
	u64			 bytes_written;
	काष्ठा perf_tool	 tool;
	bool			 maps_allocated;
	काष्ठा perf_cpu_map	*cpus;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;
	क्रमागत aggr_mode		 aggr_mode;
पूर्ण;

अटल काष्ठा perf_stat		perf_stat;
#घोषणा STAT_RECORD		perf_stat.record

अटल अस्थिर पूर्णांक करोne = 0;

अटल काष्ठा perf_stat_config stat_config = अणु
	.aggr_mode		= AGGR_GLOBAL,
	.scale			= true,
	.unit_width		= 4, /* म_माप("unit") */
	.run_count		= 1,
	.metric_only_len	= METRIC_ONLY_LEN,
	.wallसमय_nsecs_stats	= &wallसमय_nsecs_stats,
	.big_num		= true,
	.ctl_fd			= -1,
	.ctl_fd_ack		= -1,
	.iostat_run		= false,
पूर्ण;

अटल bool cpus_map_matched(काष्ठा evsel *a, काष्ठा evsel *b)
अणु
	अगर (!a->core.cpus && !b->core.cpus)
		वापस true;

	अगर (!a->core.cpus || !b->core.cpus)
		वापस false;

	अगर (a->core.cpus->nr != b->core.cpus->nr)
		वापस false;

	क्रम (पूर्णांक i = 0; i < a->core.cpus->nr; i++) अणु
		अगर (a->core.cpus->map[i] != b->core.cpus->map[i])
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम evlist__check_cpu_maps(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel, *pos, *leader;
	अक्षर buf[1024];

	अगर (evlist__has_hybrid(evlist))
		evlist__warn_hybrid_group(evlist);

	evlist__क्रम_each_entry(evlist, evsel) अणु
		leader = evsel->leader;

		/* Check that leader matches cpus with each member. */
		अगर (leader == evsel)
			जारी;
		अगर (cpus_map_matched(leader, evsel))
			जारी;

		/* If there's mismatch disable the group and warn user. */
		WARN_ONCE(1, "WARNING: grouped events cpus do not match, disabling group:\n");
		evsel__group_desc(leader, buf, माप(buf));
		pr_warning("  %s\n", buf);

		अगर (verbose) अणु
			cpu_map__snprपूर्णांक(leader->core.cpus, buf, माप(buf));
			pr_warning("     %s: %s\n", leader->name, buf);
			cpu_map__snprपूर्णांक(evsel->core.cpus, buf, माप(buf));
			pr_warning("     %s: %s\n", evsel->name, buf);
		पूर्ण

		क्रम_each_group_evsel(pos, leader) अणु
			pos->leader = pos;
			pos->core.nr_members = 0;
		पूर्ण
		evsel->leader->core.nr_members = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम dअगरf_बारpec(काष्ठा बारpec *r, काष्ठा बारpec *a,
				 काष्ठा बारpec *b)
अणु
	r->tv_sec = a->tv_sec - b->tv_sec;
	अगर (a->tv_nsec < b->tv_nsec) अणु
		r->tv_nsec = a->tv_nsec + NSEC_PER_SEC - b->tv_nsec;
		r->tv_sec--;
	पूर्ण अन्यथा अणु
		r->tv_nsec = a->tv_nsec - b->tv_nsec ;
	पूर्ण
पूर्ण

अटल व्योम perf_stat__reset_stats(व्योम)
अणु
	पूर्णांक i;

	evlist__reset_stats(evsel_list);
	perf_stat__reset_shaकरोw_stats();

	क्रम (i = 0; i < stat_config.stats_num; i++)
		perf_stat__reset_shaकरोw_per_stat(&stat_config.stats[i]);
पूर्ण

अटल पूर्णांक process_synthesized_event(काष्ठा perf_tool *tool __maybe_unused,
				     जोड़ perf_event *event,
				     काष्ठा perf_sample *sample __maybe_unused,
				     काष्ठा machine *machine __maybe_unused)
अणु
	अगर (perf_data__ग_लिखो(&perf_stat.data, event, event->header.size) < 0) अणु
		pr_err("failed to write perf data, error: %m\n");
		वापस -1;
	पूर्ण

	perf_stat.bytes_written += event->header.size;
	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_stat_round_event(u64 पंचांग, u64 type)
अणु
	वापस perf_event__synthesize_stat_round(शून्य, पंचांग, type,
						 process_synthesized_event,
						 शून्य);
पूर्ण

#घोषणा WRITE_STAT_ROUND_EVENT(समय, पूर्णांकerval) \
	ग_लिखो_stat_round_event(समय, PERF_STAT_ROUND_TYPE__ ## पूर्णांकerval)

#घोषणा SID(e, x, y) xyarray__entry(e->core.sample_id, x, y)

अटल पूर्णांक evsel__ग_लिखो_stat_event(काष्ठा evsel *counter, u32 cpu, u32 thपढ़ो,
				   काष्ठा perf_counts_values *count)
अणु
	काष्ठा perf_sample_id *sid = SID(counter, cpu, thपढ़ो);

	वापस perf_event__synthesize_stat(शून्य, cpu, thपढ़ो, sid->id, count,
					   process_synthesized_event, शून्य);
पूर्ण

अटल पूर्णांक पढ़ो_single_counter(काष्ठा evsel *counter, पूर्णांक cpu,
			       पूर्णांक thपढ़ो, काष्ठा बारpec *rs)
अणु
	अगर (counter->tool_event == PERF_TOOL_DURATION_TIME) अणु
		u64 val = rs->tv_nsec + rs->tv_sec*1000000000ULL;
		काष्ठा perf_counts_values *count =
			perf_counts(counter->counts, cpu, thपढ़ो);
		count->ena = count->run = val;
		count->val = val;
		वापस 0;
	पूर्ण
	वापस evsel__पढ़ो_counter(counter, cpu, thपढ़ो);
पूर्ण

/*
 * Read out the results of a single counter:
 * करो not aggregate counts across CPUs in प्रणाली-wide mode
 */
अटल पूर्णांक पढ़ो_counter_cpu(काष्ठा evsel *counter, काष्ठा बारpec *rs, पूर्णांक cpu)
अणु
	पूर्णांक nthपढ़ोs = perf_thपढ़ो_map__nr(evsel_list->core.thपढ़ोs);
	पूर्णांक thपढ़ो;

	अगर (!counter->supported)
		वापस -ENOENT;

	अगर (counter->core.प्रणाली_wide)
		nthपढ़ोs = 1;

	क्रम (thपढ़ो = 0; thपढ़ो < nthपढ़ोs; thपढ़ो++) अणु
		काष्ठा perf_counts_values *count;

		count = perf_counts(counter->counts, cpu, thपढ़ो);

		/*
		 * The leader's group पढ़ो loads data पूर्णांकo its group members
		 * (via evsel__पढ़ो_counter()) and sets their count->loaded.
		 */
		अगर (!perf_counts__is_loaded(counter->counts, cpu, thपढ़ो) &&
		    पढ़ो_single_counter(counter, cpu, thपढ़ो, rs)) अणु
			counter->counts->scaled = -1;
			perf_counts(counter->counts, cpu, thपढ़ो)->ena = 0;
			perf_counts(counter->counts, cpu, thपढ़ो)->run = 0;
			वापस -1;
		पूर्ण

		perf_counts__set_loaded(counter->counts, cpu, thपढ़ो, false);

		अगर (STAT_RECORD) अणु
			अगर (evsel__ग_लिखो_stat_event(counter, cpu, thपढ़ो, count)) अणु
				pr_err("failed to write stat event\n");
				वापस -1;
			पूर्ण
		पूर्ण

		अगर (verbose > 1) अणु
			ख_लिखो(stat_config.output,
				"%s: %d: %" PRIu64 " %" PRIu64 " %" PRIu64 "\n",
					evsel__name(counter),
					cpu,
					count->val, count->ena, count->run);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_affinity_counters(काष्ठा बारpec *rs)
अणु
	काष्ठा evsel *counter;
	काष्ठा affinity affinity;
	पूर्णांक i, ncpus, cpu;

	अगर (all_counters_use_bpf)
		वापस 0;

	अगर (affinity__setup(&affinity) < 0)
		वापस -1;

	ncpus = perf_cpu_map__nr(evsel_list->core.all_cpus);
	अगर (!target__has_cpu(&target) || target__has_per_thपढ़ो(&target))
		ncpus = 1;
	evlist__क्रम_each_cpu(evsel_list, i, cpu) अणु
		अगर (i >= ncpus)
			अवरोध;
		affinity__set(&affinity, cpu);

		evlist__क्रम_each_entry(evsel_list, counter) अणु
			अगर (evsel__cpu_iter_skip(counter, cpu))
				जारी;
			अगर (evsel__is_bpf(counter))
				जारी;
			अगर (!counter->err) अणु
				counter->err = पढ़ो_counter_cpu(counter, rs,
								counter->cpu_iter - 1);
			पूर्ण
		पूर्ण
	पूर्ण
	affinity__cleanup(&affinity);
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_bpf_map_counters(व्योम)
अणु
	काष्ठा evsel *counter;
	पूर्णांक err;

	evlist__क्रम_each_entry(evsel_list, counter) अणु
		अगर (!evsel__is_bpf(counter))
			जारी;

		err = bpf_counter__पढ़ो(counter);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम पढ़ो_counters(काष्ठा बारpec *rs)
अणु
	काष्ठा evsel *counter;

	अगर (!stat_config.stop_पढ़ो_counter) अणु
		अगर (पढ़ो_bpf_map_counters() ||
		    पढ़ो_affinity_counters(rs))
			वापस;
	पूर्ण

	evlist__क्रम_each_entry(evsel_list, counter) अणु
		अगर (counter->err)
			pr_debug("failed to read counter %s\n", counter->name);
		अगर (counter->err == 0 && perf_stat_process_counter(&stat_config, counter))
			pr_warning("failed to process counter %s\n", counter->name);
		counter->err = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक runसमय_stat_new(काष्ठा perf_stat_config *config, पूर्णांक nthपढ़ोs)
अणु
	पूर्णांक i;

	config->stats = सुस्मृति(nthपढ़ोs, माप(काष्ठा runसमय_stat));
	अगर (!config->stats)
		वापस -1;

	config->stats_num = nthपढ़ोs;

	क्रम (i = 0; i < nthपढ़ोs; i++)
		runसमय_stat__init(&config->stats[i]);

	वापस 0;
पूर्ण

अटल व्योम runसमय_stat_delete(काष्ठा perf_stat_config *config)
अणु
	पूर्णांक i;

	अगर (!config->stats)
		वापस;

	क्रम (i = 0; i < config->stats_num; i++)
		runसमय_stat__निकास(&config->stats[i]);

	zमुक्त(&config->stats);
पूर्ण

अटल व्योम runसमय_stat_reset(काष्ठा perf_stat_config *config)
अणु
	पूर्णांक i;

	अगर (!config->stats)
		वापस;

	क्रम (i = 0; i < config->stats_num; i++)
		perf_stat__reset_shaकरोw_per_stat(&config->stats[i]);
पूर्ण

अटल व्योम process_पूर्णांकerval(व्योम)
अणु
	काष्ठा बारpec ts, rs;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &ts);
	dअगरf_बारpec(&rs, &ts, &ref_समय);

	perf_stat__reset_shaकरोw_per_stat(&rt_stat);
	runसमय_stat_reset(&stat_config);
	पढ़ो_counters(&rs);

	अगर (STAT_RECORD) अणु
		अगर (WRITE_STAT_ROUND_EVENT(rs.tv_sec * NSEC_PER_SEC + rs.tv_nsec, INTERVAL))
			pr_err("failed to write stat round event\n");
	पूर्ण

	init_stats(&wallसमय_nsecs_stats);
	update_stats(&wallसमय_nsecs_stats, stat_config.पूर्णांकerval * 1000000ULL);
	prपूर्णांक_counters(&rs, 0, शून्य);
पूर्ण

अटल bool handle_पूर्णांकerval(अचिन्हित पूर्णांक पूर्णांकerval, पूर्णांक *बार)
अणु
	अगर (पूर्णांकerval) अणु
		process_पूर्णांकerval();
		अगर (पूर्णांकerval_count && !(--(*बार)))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक enable_counters(व्योम)
अणु
	काष्ठा evsel *evsel;
	पूर्णांक err;

	evlist__क्रम_each_entry(evsel_list, evsel) अणु
		अगर (!evsel__is_bpf(evsel))
			जारी;

		err = bpf_counter__enable(evsel);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (stat_config.initial_delay < 0) अणु
		pr_info(EVLIST_DISABLED_MSG);
		वापस 0;
	पूर्ण

	अगर (stat_config.initial_delay > 0) अणु
		pr_info(EVLIST_DISABLED_MSG);
		usleep(stat_config.initial_delay * USEC_PER_MSEC);
	पूर्ण

	/*
	 * We need to enable counters only अगर:
	 * - we करोn't have tracee (attaching to task or cpu)
	 * - we have initial delay configured
	 */
	अगर (!target__none(&target) || stat_config.initial_delay) अणु
		अगर (!all_counters_use_bpf)
			evlist__enable(evsel_list);
		अगर (stat_config.initial_delay > 0)
			pr_info(EVLIST_ENABLED_MSG);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम disable_counters(व्योम)
अणु
	काष्ठा evsel *counter;

	/*
	 * If we करोn't have tracee (attaching to task or cpu), counters may
	 * still be running. To get accurate group ratios, we must stop groups
	 * from counting beक्रमe पढ़ोing their स्थिरituent counters.
	 */
	अगर (!target__none(&target)) अणु
		evlist__क्रम_each_entry(evsel_list, counter)
			bpf_counter__disable(counter);
		अगर (!all_counters_use_bpf)
			evlist__disable(evsel_list);
	पूर्ण
पूर्ण

अटल अस्थिर पूर्णांक workload_exec_त्रुटि_सं;

/*
 * evlist__prepare_workload will send a SIGUSR1
 * अगर the विभाजन fails, since we asked by setting its
 * want_संकेत to true.
 */
अटल व्योम workload_exec_failed_संकेत(पूर्णांक signo __maybe_unused, siginfo_t *info,
					व्योम *ucontext __maybe_unused)
अणु
	workload_exec_त्रुटि_सं = info->si_value.sival_पूर्णांक;
पूर्ण

अटल bool evsel__should_store_id(काष्ठा evsel *counter)
अणु
	वापस STAT_RECORD || counter->core.attr.पढ़ो_क्रमmat & PERF_FORMAT_ID;
पूर्ण

अटल bool is_target_alive(काष्ठा target *_target,
			    काष्ठा perf_thपढ़ो_map *thपढ़ोs)
अणु
	काष्ठा stat st;
	पूर्णांक i;

	अगर (!target__has_task(_target))
		वापस true;

	क्रम (i = 0; i < thपढ़ोs->nr; i++) अणु
		अक्षर path[PATH_MAX];

		scnम_लिखो(path, PATH_MAX, "%s/%d", procfs__mountpoपूर्णांक(),
			  thपढ़ोs->map[i].pid);

		अगर (!stat(path, &st))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम process_evlist(काष्ठा evlist *evlist, अचिन्हित पूर्णांक पूर्णांकerval)
अणु
	क्रमागत evlist_ctl_cmd cmd = EVLIST_CTL_CMD_UNSUPPORTED;

	अगर (evlist__ctlfd_process(evlist, &cmd) > 0) अणु
		चयन (cmd) अणु
		हाल EVLIST_CTL_CMD_ENABLE:
			अगर (पूर्णांकerval)
				process_पूर्णांकerval();
			अवरोध;
		हाल EVLIST_CTL_CMD_DISABLE:
			अगर (पूर्णांकerval)
				process_पूर्णांकerval();
			अवरोध;
		हाल EVLIST_CTL_CMD_SNAPSHOT:
		हाल EVLIST_CTL_CMD_ACK:
		हाल EVLIST_CTL_CMD_UNSUPPORTED:
		हाल EVLIST_CTL_CMD_EVLIST:
		हाल EVLIST_CTL_CMD_STOP:
		हाल EVLIST_CTL_CMD_PING:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम compute_tts(काष्ठा बारpec *समय_start, काष्ठा बारpec *समय_stop,
			पूर्णांक *समय_प्रकारo_sleep)
अणु
	पूर्णांक tts = *समय_प्रकारo_sleep;
	काष्ठा बारpec समय_dअगरf;

	dअगरf_बारpec(&समय_dअगरf, समय_stop, समय_start);

	tts -= समय_dअगरf.tv_sec * MSEC_PER_SEC +
	       समय_dअगरf.tv_nsec / NSEC_PER_MSEC;

	अगर (tts < 0)
		tts = 0;

	*समय_प्रकारo_sleep = tts;
पूर्ण

अटल पूर्णांक dispatch_events(bool विभाजनs, पूर्णांक समयout, पूर्णांक पूर्णांकerval, पूर्णांक *बार)
अणु
	पूर्णांक child_निकासed = 0, status = 0;
	पूर्णांक समय_प्रकारo_sleep, sleep_समय;
	काष्ठा बारpec समय_start, समय_stop;

	अगर (पूर्णांकerval)
		sleep_समय = पूर्णांकerval;
	अन्यथा अगर (समयout)
		sleep_समय = समयout;
	अन्यथा
		sleep_समय = 1000;

	समय_प्रकारo_sleep = sleep_समय;

	जबतक (!करोne) अणु
		अगर (विभाजनs)
			child_निकासed = रुकोpid(child_pid, &status, WNOHANG);
		अन्यथा
			child_निकासed = !is_target_alive(&target, evsel_list->core.thपढ़ोs) ? 1 : 0;

		अगर (child_निकासed)
			अवरोध;

		घड़ी_समय_लो(CLOCK_MONOTONIC, &समय_start);
		अगर (!(evlist__poll(evsel_list, समय_प्रकारo_sleep) > 0)) अणु /* poll समयout or EINTR */
			अगर (समयout || handle_पूर्णांकerval(पूर्णांकerval, बार))
				अवरोध;
			समय_प्रकारo_sleep = sleep_समय;
		पूर्ण अन्यथा अणु /* fd revent */
			process_evlist(evsel_list, पूर्णांकerval);
			घड़ी_समय_लो(CLOCK_MONOTONIC, &समय_stop);
			compute_tts(&समय_start, &समय_stop, &समय_प्रकारo_sleep);
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

क्रमागत counter_recovery अणु
	COUNTER_SKIP,
	COUNTER_RETRY,
	COUNTER_FATAL,
पूर्ण;

अटल क्रमागत counter_recovery stat_handle_error(काष्ठा evsel *counter)
अणु
	अक्षर msg[बफ_मान];
	/*
	 * PPC वापसs ENXIO क्रम HW counters until 2.6.37
	 * (behavior changed with commit b0a873e).
	 */
	अगर (त्रुटि_सं == EINVAL || त्रुटि_सं == ENOSYS ||
	    त्रुटि_सं == ENOENT || त्रुटि_सं == EOPNOTSUPP ||
	    त्रुटि_सं == ENXIO) अणु
		अगर (verbose > 0)
			ui__warning("%s event is not supported by the kernel.\n",
				    evsel__name(counter));
		counter->supported = false;
		/*
		 * errored is a sticky flag that means one of the counter's
		 * cpu event had a problem and needs to be reexamined.
		 */
		counter->errored = true;

		अगर ((counter->leader != counter) ||
		    !(counter->leader->core.nr_members > 1))
			वापस COUNTER_SKIP;
	पूर्ण अन्यथा अगर (evsel__fallback(counter, त्रुटि_सं, msg, माप(msg))) अणु
		अगर (verbose > 0)
			ui__warning("%s\n", msg);
		वापस COUNTER_RETRY;
	पूर्ण अन्यथा अगर (target__has_per_thपढ़ो(&target) &&
		   evsel_list->core.thपढ़ोs &&
		   evsel_list->core.thपढ़ोs->err_thपढ़ो != -1) अणु
		/*
		 * For global --per-thपढ़ो हाल, skip current
		 * error thपढ़ो.
		 */
		अगर (!thपढ़ो_map__हटाओ(evsel_list->core.thपढ़ोs,
					evsel_list->core.thपढ़ोs->err_thपढ़ो)) अणु
			evsel_list->core.thपढ़ोs->err_thपढ़ो = -1;
			वापस COUNTER_RETRY;
		पूर्ण
	पूर्ण

	evsel__खोलो_म_त्रुटि(counter, &target, त्रुटि_सं, msg, माप(msg));
	ui__error("%s\n", msg);

	अगर (child_pid != -1)
		समाप्त(child_pid, संक_इति);
	वापस COUNTER_FATAL;
पूर्ण

अटल पूर्णांक __run_perf_stat(पूर्णांक argc, स्थिर अक्षर **argv, पूर्णांक run_idx)
अणु
	पूर्णांक पूर्णांकerval = stat_config.पूर्णांकerval;
	पूर्णांक बार = stat_config.बार;
	पूर्णांक समयout = stat_config.समयout;
	अक्षर msg[बफ_मान];
	अचिन्हित दीर्घ दीर्घ t0, t1;
	काष्ठा evsel *counter;
	माप_प्रकार l;
	पूर्णांक status = 0;
	स्थिर bool विभाजनs = (argc > 0);
	bool is_pipe = STAT_RECORD ? perf_stat.data.is_pipe : false;
	काष्ठा affinity affinity;
	पूर्णांक i, cpu, err;
	bool second_pass = false;

	अगर (विभाजनs) अणु
		अगर (evlist__prepare_workload(evsel_list, &target, argv, is_pipe, workload_exec_failed_संकेत) < 0) अणु
			लिखो_त्रुटि("failed to prepare workload");
			वापस -1;
		पूर्ण
		child_pid = evsel_list->workload.pid;
	पूर्ण

	अगर (group)
		evlist__set_leader(evsel_list);

	अगर (affinity__setup(&affinity) < 0)
		वापस -1;

	evlist__क्रम_each_entry(evsel_list, counter) अणु
		अगर (bpf_counter__load(counter, &target))
			वापस -1;
		अगर (!evsel__is_bpf(counter))
			all_counters_use_bpf = false;
	पूर्ण

	evlist__क्रम_each_cpu (evsel_list, i, cpu) अणु
		/*
		 * bperf calls evsel__खोलो_per_cpu() in bperf__load(), so
		 * no need to call it again here.
		 */
		अगर (target.use_bpf)
			अवरोध;
		affinity__set(&affinity, cpu);

		evlist__क्रम_each_entry(evsel_list, counter) अणु
			अगर (evsel__cpu_iter_skip(counter, cpu))
				जारी;
			अगर (counter->reset_group || counter->errored)
				जारी;
			अगर (evsel__is_bpf(counter))
				जारी;
try_again:
			अगर (create_perf_stat_counter(counter, &stat_config, &target,
						     counter->cpu_iter - 1) < 0) अणु

				/*
				 * Weak group failed. We cannot just unकरो this here
				 * because earlier CPUs might be in group mode, and the kernel
				 * करोesn't support mixing group and non group पढ़ोs. Defer
				 * it to later.
				 * Don't close here because we're in the wrong affinity.
				 */
				अगर ((त्रुटि_सं == EINVAL || त्रुटि_सं == EBADF) &&
				    counter->leader != counter &&
				    counter->weak_group) अणु
					evlist__reset_weak_group(evsel_list, counter, false);
					निश्चित(counter->reset_group);
					second_pass = true;
					जारी;
				पूर्ण

				चयन (stat_handle_error(counter)) अणु
				हाल COUNTER_FATAL:
					वापस -1;
				हाल COUNTER_RETRY:
					जाओ try_again;
				हाल COUNTER_SKIP:
					जारी;
				शेष:
					अवरोध;
				पूर्ण

			पूर्ण
			counter->supported = true;
		पूर्ण
	पूर्ण

	अगर (second_pass) अणु
		/*
		 * Now reकरो all the weak group after closing them,
		 * and also बंद errored counters.
		 */

		evlist__क्रम_each_cpu(evsel_list, i, cpu) अणु
			affinity__set(&affinity, cpu);
			/* First बंद errored or weak retry */
			evlist__क्रम_each_entry(evsel_list, counter) अणु
				अगर (!counter->reset_group && !counter->errored)
					जारी;
				अगर (evsel__cpu_iter_skip_no_inc(counter, cpu))
					जारी;
				perf_evsel__बंद_cpu(&counter->core, counter->cpu_iter);
			पूर्ण
			/* Now reखोलो weak */
			evlist__क्रम_each_entry(evsel_list, counter) अणु
				अगर (!counter->reset_group && !counter->errored)
					जारी;
				अगर (evsel__cpu_iter_skip(counter, cpu))
					जारी;
				अगर (!counter->reset_group)
					जारी;
try_again_reset:
				pr_debug2("reopening weak %s\n", evsel__name(counter));
				अगर (create_perf_stat_counter(counter, &stat_config, &target,
							     counter->cpu_iter - 1) < 0) अणु

					चयन (stat_handle_error(counter)) अणु
					हाल COUNTER_FATAL:
						वापस -1;
					हाल COUNTER_RETRY:
						जाओ try_again_reset;
					हाल COUNTER_SKIP:
						जारी;
					शेष:
						अवरोध;
					पूर्ण
				पूर्ण
				counter->supported = true;
			पूर्ण
		पूर्ण
	पूर्ण
	affinity__cleanup(&affinity);

	evlist__क्रम_each_entry(evsel_list, counter) अणु
		अगर (!counter->supported) अणु
			perf_evsel__मुक्त_fd(&counter->core);
			जारी;
		पूर्ण

		l = म_माप(counter->unit);
		अगर (l > stat_config.unit_width)
			stat_config.unit_width = l;

		अगर (evsel__should_store_id(counter) &&
		    evsel__store_ids(counter, evsel_list))
			वापस -1;
	पूर्ण

	अगर (evlist__apply_filters(evsel_list, &counter)) अणु
		pr_err("failed to set filter \"%s\" on event %s with %d (%s)\n",
			counter->filter, evsel__name(counter), त्रुटि_सं,
			str_error_r(त्रुटि_सं, msg, माप(msg)));
		वापस -1;
	पूर्ण

	अगर (STAT_RECORD) अणु
		पूर्णांक fd = perf_data__fd(&perf_stat.data);

		अगर (is_pipe) अणु
			err = perf_header__ग_लिखो_pipe(perf_data__fd(&perf_stat.data));
		पूर्ण अन्यथा अणु
			err = perf_session__ग_लिखो_header(perf_stat.session, evsel_list,
							 fd, false);
		पूर्ण

		अगर (err < 0)
			वापस err;

		err = perf_event__synthesize_stat_events(&stat_config, शून्य, evsel_list,
							 process_synthesized_event, is_pipe);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/*
	 * Enable counters and exec the command:
	 */
	अगर (विभाजनs) अणु
		evlist__start_workload(evsel_list);
		err = enable_counters();
		अगर (err)
			वापस -1;

		t0 = rdघड़ी();
		घड़ी_समय_लो(CLOCK_MONOTONIC, &ref_समय);

		अगर (पूर्णांकerval || समयout || evlist__ctlfd_initialized(evsel_list))
			status = dispatch_events(विभाजनs, समयout, पूर्णांकerval, &बार);
		अगर (child_pid != -1) अणु
			अगर (समयout)
				समाप्त(child_pid, संक_इति);
			रुको4(child_pid, &status, 0, &stat_config.ru_data);
		पूर्ण

		अगर (workload_exec_त्रुटि_सं) अणु
			स्थिर अक्षर *emsg = str_error_r(workload_exec_त्रुटि_सं, msg, माप(msg));
			pr_err("Workload failed: %s\n", emsg);
			वापस -1;
		पूर्ण

		अगर (WIFSIGNALED(status))
			pसंकेत(WTERMSIG(status), argv[0]);
	पूर्ण अन्यथा अणु
		err = enable_counters();
		अगर (err)
			वापस -1;

		t0 = rdघड़ी();
		घड़ी_समय_लो(CLOCK_MONOTONIC, &ref_समय);

		status = dispatch_events(विभाजनs, समयout, पूर्णांकerval, &बार);
	पूर्ण

	disable_counters();

	t1 = rdघड़ी();

	अगर (stat_config.wallसमय_run_table)
		stat_config.wallसमय_run[run_idx] = t1 - t0;

	अगर (पूर्णांकerval && stat_config.summary) अणु
		stat_config.पूर्णांकerval = 0;
		stat_config.stop_पढ़ो_counter = true;
		init_stats(&wallसमय_nsecs_stats);
		update_stats(&wallसमय_nsecs_stats, t1 - t0);

		अगर (stat_config.aggr_mode == AGGR_GLOBAL)
			evlist__save_aggr_prev_raw_counts(evsel_list);

		evlist__copy_prev_raw_counts(evsel_list);
		evlist__reset_prev_raw_counts(evsel_list);
		runसमय_stat_reset(&stat_config);
		perf_stat__reset_shaकरोw_per_stat(&rt_stat);
	पूर्ण अन्यथा
		update_stats(&wallसमय_nsecs_stats, t1 - t0);

	/*
	 * Closing a group leader splits the group, and as we only disable
	 * group leaders, results in reमुख्यing events becoming enabled. To
	 * aव्योम arbitrary skew, we must पढ़ो all counters beक्रमe closing any
	 * group leaders.
	 */
	पढ़ो_counters(&(काष्ठा बारpec) अणु .tv_nsec = t1-t0 पूर्ण);

	/*
	 * We need to keep evsel_list alive, because it's processed
	 * later the evsel_list will be बंदd after.
	 */
	अगर (!STAT_RECORD)
		evlist__बंद(evsel_list);

	वापस WEXITSTATUS(status);
पूर्ण

अटल पूर्णांक run_perf_stat(पूर्णांक argc, स्थिर अक्षर **argv, पूर्णांक run_idx)
अणु
	पूर्णांक ret;

	अगर (pre_cmd) अणु
		ret = प्रणाली(pre_cmd);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (sync_run)
		sync();

	ret = __run_perf_stat(argc, argv, run_idx);
	अगर (ret)
		वापस ret;

	अगर (post_cmd) अणु
		ret = प्रणाली(post_cmd);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम prपूर्णांक_counters(काष्ठा बारpec *ts, पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	/* Do not prपूर्णांक anything अगर we record to the pipe. */
	अगर (STAT_RECORD && perf_stat.data.is_pipe)
		वापस;
	अगर (stat_config.quiet)
		वापस;

	evlist__prपूर्णांक_counters(evsel_list, &stat_config, &target, ts, argc, argv);
पूर्ण

अटल अस्थिर पूर्णांक signr = -1;

अटल व्योम skip_संकेत(पूर्णांक signo)
अणु
	अगर ((child_pid == -1) || stat_config.पूर्णांकerval)
		करोne = 1;

	signr = signo;
	/*
	 * render child_pid harmless
	 * won't send संक_इति to a अक्रमom
	 * process in हाल of race condition
	 * and fast PID recycling
	 */
	child_pid = -1;
पूर्ण

अटल व्योम sig_निकास_पर(व्योम)
अणु
	sigset_t set, oset;

	/*
	 * aव्योम race condition with SIGCHLD handler
	 * in skip_संकेत() which is modअगरying child_pid
	 * goal is to aव्योम send संक_इति to a अक्रमom
	 * process
	 */
	sigemptyset(&set);
	sigaddset(&set, SIGCHLD);
	sigprocmask(SIG_BLOCK, &set, &oset);

	अगर (child_pid != -1)
		समाप्त(child_pid, संक_इति);

	sigprocmask(SIG_SETMASK, &oset, शून्य);

	अगर (signr == -1)
		वापस;

	संकेत(signr, संक_पूर्व);
	समाप्त(getpid(), signr);
पूर्ण

व्योम perf_stat__set_big_num(पूर्णांक set)
अणु
	stat_config.big_num = (set != 0);
पूर्ण

व्योम perf_stat__set_no_csv_summary(पूर्णांक set)
अणु
	stat_config.no_csv_summary = (set != 0);
पूर्ण

अटल पूर्णांक stat__set_big_num(स्थिर काष्ठा option *opt __maybe_unused,
			     स्थिर अक्षर *s __maybe_unused, पूर्णांक unset)
अणु
	big_num_opt = unset ? 0 : 1;
	perf_stat__set_big_num(!unset);
	वापस 0;
पूर्ण

अटल पूर्णांक enable_metric_only(स्थिर काष्ठा option *opt __maybe_unused,
			      स्थिर अक्षर *s __maybe_unused, पूर्णांक unset)
अणु
	क्रमce_metric_only = true;
	stat_config.metric_only = !unset;
	वापस 0;
पूर्ण

अटल पूर्णांक parse_metric_groups(स्थिर काष्ठा option *opt,
			       स्थिर अक्षर *str,
			       पूर्णांक unset __maybe_unused)
अणु
	वापस metricgroup__parse_groups(opt, str,
					 stat_config.metric_no_group,
					 stat_config.metric_no_merge,
					 &stat_config.metric_events);
पूर्ण

अटल पूर्णांक parse_control_option(स्थिर काष्ठा option *opt,
				स्थिर अक्षर *str,
				पूर्णांक unset __maybe_unused)
अणु
	काष्ठा perf_stat_config *config = opt->value;

	वापस evlist__parse_control(str, &config->ctl_fd, &config->ctl_fd_ack, &config->ctl_fd_बंद);
पूर्ण

अटल पूर्णांक parse_stat_cgroups(स्थिर काष्ठा option *opt,
			      स्थिर अक्षर *str, पूर्णांक unset)
अणु
	अगर (stat_config.cgroup_list) अणु
		pr_err("--cgroup and --for-each-cgroup cannot be used together\n");
		वापस -1;
	पूर्ण

	वापस parse_cgroups(opt, str, unset);
पूर्ण

अटल काष्ठा option stat_options[] = अणु
	OPT_BOOLEAN('T', "transaction", &transaction_run,
		    "hardware transaction statistics"),
	OPT_CALLBACK('e', "event", &evsel_list, "event",
		     "event selector. use 'perf list' to list available events",
		     parse_events_option),
	OPT_CALLBACK(0, "filter", &evsel_list, "filter",
		     "event filter", parse_filter),
	OPT_BOOLEAN('i', "no-inherit", &stat_config.no_inherit,
		    "child tasks do not inherit counters"),
	OPT_STRING('p', "pid", &target.pid, "pid",
		   "stat events on existing process id"),
	OPT_STRING('t', "tid", &target.tid, "tid",
		   "stat events on existing thread id"),
#अगर_घोषित HAVE_BPF_SKEL
	OPT_STRING('b', "bpf-prog", &target.bpf_str, "bpf-prog-id",
		   "stat events on existing bpf program id"),
	OPT_BOOLEAN(0, "bpf-counters", &target.use_bpf,
		    "use bpf program to count events"),
	OPT_STRING(0, "bpf-attr-map", &target.attr_map, "attr-map-path",
		   "path to perf_event_attr map"),
#पूर्ण_अगर
	OPT_BOOLEAN('a', "all-cpus", &target.प्रणाली_wide,
		    "system-wide collection from all CPUs"),
	OPT_BOOLEAN('g', "group", &group,
		    "put the counters into a counter group"),
	OPT_BOOLEAN(0, "scale", &stat_config.scale,
		    "Use --no-scale to disable counter scaling for multiplexing"),
	OPT_INCR('v', "verbose", &verbose,
		    "be more verbose (show counter open errors, etc)"),
	OPT_INTEGER('r', "repeat", &stat_config.run_count,
		    "repeat command and print average + stddev (max: 100, forever: 0)"),
	OPT_BOOLEAN(0, "table", &stat_config.wallसमय_run_table,
		    "display details about each run (only with -r option)"),
	OPT_BOOLEAN('n', "null", &stat_config.null_run,
		    "null run - dont start any counters"),
	OPT_INCR('d', "detailed", &detailed_run,
		    "detailed run - start a lot of events"),
	OPT_BOOLEAN('S', "sync", &sync_run,
		    "call sync() before starting a run"),
	OPT_CALLBACK_NOOPT('B', "big-num", शून्य, शून्य,
			   "print large numbers with thousands\' separators",
			   stat__set_big_num),
	OPT_STRING('C', "cpu", &target.cpu_list, "cpu",
		    "list of cpus to monitor in system-wide"),
	OPT_SET_UINT('A', "no-aggr", &stat_config.aggr_mode,
		    "disable CPU count aggregation", AGGR_NONE),
	OPT_BOOLEAN(0, "no-merge", &stat_config.no_merge, "Do not merge identical named events"),
	OPT_STRING('x', "field-separator", &stat_config.csv_sep, "separator",
		   "print counts with custom separator"),
	OPT_CALLBACK('G', "cgroup", &evsel_list, "name",
		     "monitor event in cgroup name only", parse_stat_cgroups),
	OPT_STRING(0, "for-each-cgroup", &stat_config.cgroup_list, "name",
		    "expand events for each cgroup"),
	OPT_STRING('o', "output", &output_name, "file", "output file name"),
	OPT_BOOLEAN(0, "append", &append_file, "append to the output file"),
	OPT_INTEGER(0, "log-fd", &output_fd,
		    "log output to fd, instead of stderr"),
	OPT_STRING(0, "pre", &pre_cmd, "command",
			"command to run prior to the measured command"),
	OPT_STRING(0, "post", &post_cmd, "command",
			"command to run after to the measured command"),
	OPT_UINTEGER('I', "interval-print", &stat_config.पूर्णांकerval,
		    "print counts at regular interval in ms "
		    "(overhead is possible for values <= 100ms)"),
	OPT_INTEGER(0, "interval-count", &stat_config.बार,
		    "print counts for fixed number of times"),
	OPT_BOOLEAN(0, "interval-clear", &stat_config.पूर्णांकerval_clear,
		    "clear screen in between new interval"),
	OPT_UINTEGER(0, "timeout", &stat_config.समयout,
		    "stop workload and print counts after a timeout period in ms (>= 10ms)"),
	OPT_SET_UINT(0, "per-socket", &stat_config.aggr_mode,
		     "aggregate counts per processor socket", AGGR_SOCKET),
	OPT_SET_UINT(0, "per-die", &stat_config.aggr_mode,
		     "aggregate counts per processor die", AGGR_DIE),
	OPT_SET_UINT(0, "per-core", &stat_config.aggr_mode,
		     "aggregate counts per physical processor core", AGGR_CORE),
	OPT_SET_UINT(0, "per-thread", &stat_config.aggr_mode,
		     "aggregate counts per thread", AGGR_THREAD),
	OPT_SET_UINT(0, "per-node", &stat_config.aggr_mode,
		     "aggregate counts per numa node", AGGR_NODE),
	OPT_INTEGER('D', "delay", &stat_config.initial_delay,
		    "ms to wait before starting measurement after program start (-1: start with events disabled)"),
	OPT_CALLBACK_NOOPT(0, "metric-only", &stat_config.metric_only, शून्य,
			"Only print computed metrics. No raw values", enable_metric_only),
	OPT_BOOLEAN(0, "metric-no-group", &stat_config.metric_no_group,
		       "don't group metric events, impacts multiplexing"),
	OPT_BOOLEAN(0, "metric-no-merge", &stat_config.metric_no_merge,
		       "don't try to share events between metrics in a group"),
	OPT_BOOLEAN(0, "topdown", &topकरोwn_run,
			"measure top-down statistics"),
	OPT_UINTEGER(0, "td-level", &stat_config.topकरोwn_level,
			"Set the metrics level for the top-down statistics (0: max level)"),
	OPT_BOOLEAN(0, "smi-cost", &smi_cost,
			"measure SMI cost"),
	OPT_CALLBACK('M', "metrics", &evsel_list, "metric/metric group list",
		     "monitor specified metrics or metric groups (separated by ,)",
		     parse_metric_groups),
	OPT_BOOLEAN_FLAG(0, "all-kernel", &stat_config.all_kernel,
			 "Configure all used events to run in kernel space.",
			 PARSE_OPT_EXCLUSIVE),
	OPT_BOOLEAN_FLAG(0, "all-user", &stat_config.all_user,
			 "Configure all used events to run in user space.",
			 PARSE_OPT_EXCLUSIVE),
	OPT_BOOLEAN(0, "percore-show-thread", &stat_config.percore_show_thपढ़ो,
		    "Use with 'percore' event qualifier to show the event "
		    "counts of one hardware thread by sum up total hardware "
		    "threads of same physical core"),
	OPT_BOOLEAN(0, "summary", &stat_config.summary,
		       "print summary for interval mode"),
	OPT_BOOLEAN(0, "no-csv-summary", &stat_config.no_csv_summary,
		       "don't print 'summary' for CSV summary output"),
	OPT_BOOLEAN(0, "quiet", &stat_config.quiet,
			"don't print output (useful with record)"),
#अगर_घोषित HAVE_LIBPFM
	OPT_CALLBACK(0, "pfm-events", &evsel_list, "event",
		"libpfm4 event selector. use 'perf list' to list available events",
		parse_libpfm_events_option),
#पूर्ण_अगर
	OPT_CALLBACK(0, "control", &stat_config, "fd:ctl-fd[,ack-fd] or fifo:ctl-fifo[,ack-fifo]",
		     "Listen on ctl-fd descriptor for command to control measurement ('enable': enable events, 'disable': disable events).\n"
		     "\t\t\t  Optionally send control command completion ('ack\\n') to ack-fd descriptor.\n"
		     "\t\t\t  Alternatively, ctl-fifo / ack-fifo will be opened and used as ctl-fd / ack-fd.",
		      parse_control_option),
	OPT_CALLBACK_OPTARG(0, "iostat", &evsel_list, &stat_config, "default",
			    "measure I/O performance metrics provided by arch/platform",
			    iostat_parse),
	OPT_END()
पूर्ण;

अटल काष्ठा aggr_cpu_id perf_stat__get_socket(काष्ठा perf_stat_config *config __maybe_unused,
				 काष्ठा perf_cpu_map *map, पूर्णांक cpu)
अणु
	वापस cpu_map__get_socket(map, cpu, शून्य);
पूर्ण

अटल काष्ठा aggr_cpu_id perf_stat__get_die(काष्ठा perf_stat_config *config __maybe_unused,
			      काष्ठा perf_cpu_map *map, पूर्णांक cpu)
अणु
	वापस cpu_map__get_die(map, cpu, शून्य);
पूर्ण

अटल काष्ठा aggr_cpu_id perf_stat__get_core(काष्ठा perf_stat_config *config __maybe_unused,
			       काष्ठा perf_cpu_map *map, पूर्णांक cpu)
अणु
	वापस cpu_map__get_core(map, cpu, शून्य);
पूर्ण

अटल काष्ठा aggr_cpu_id perf_stat__get_node(काष्ठा perf_stat_config *config __maybe_unused,
			       काष्ठा perf_cpu_map *map, पूर्णांक cpu)
अणु
	वापस cpu_map__get_node(map, cpu, शून्य);
पूर्ण

अटल काष्ठा aggr_cpu_id perf_stat__get_aggr(काष्ठा perf_stat_config *config,
			       aggr_get_id_t get_id, काष्ठा perf_cpu_map *map, पूर्णांक idx)
अणु
	पूर्णांक cpu;
	काष्ठा aggr_cpu_id id = cpu_map__empty_aggr_cpu_id();

	अगर (idx >= map->nr)
		वापस id;

	cpu = map->map[idx];

	अगर (cpu_map__aggr_cpu_id_is_empty(config->cpus_aggr_map->map[cpu]))
		config->cpus_aggr_map->map[cpu] = get_id(config, map, idx);

	id = config->cpus_aggr_map->map[cpu];
	वापस id;
पूर्ण

अटल काष्ठा aggr_cpu_id perf_stat__get_socket_cached(काष्ठा perf_stat_config *config,
					काष्ठा perf_cpu_map *map, पूर्णांक idx)
अणु
	वापस perf_stat__get_aggr(config, perf_stat__get_socket, map, idx);
पूर्ण

अटल काष्ठा aggr_cpu_id perf_stat__get_die_cached(काष्ठा perf_stat_config *config,
					काष्ठा perf_cpu_map *map, पूर्णांक idx)
अणु
	वापस perf_stat__get_aggr(config, perf_stat__get_die, map, idx);
पूर्ण

अटल काष्ठा aggr_cpu_id perf_stat__get_core_cached(काष्ठा perf_stat_config *config,
				      काष्ठा perf_cpu_map *map, पूर्णांक idx)
अणु
	वापस perf_stat__get_aggr(config, perf_stat__get_core, map, idx);
पूर्ण

अटल काष्ठा aggr_cpu_id perf_stat__get_node_cached(काष्ठा perf_stat_config *config,
				      काष्ठा perf_cpu_map *map, पूर्णांक idx)
अणु
	वापस perf_stat__get_aggr(config, perf_stat__get_node, map, idx);
पूर्ण

अटल bool term_percore_set(व्योम)
अणु
	काष्ठा evsel *counter;

	evlist__क्रम_each_entry(evsel_list, counter) अणु
		अगर (counter->percore)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक perf_stat_init_aggr_mode(व्योम)
अणु
	पूर्णांक nr;

	चयन (stat_config.aggr_mode) अणु
	हाल AGGR_SOCKET:
		अगर (cpu_map__build_socket_map(evsel_list->core.cpus, &stat_config.aggr_map)) अणु
			लिखो_त्रुटि("cannot build socket map");
			वापस -1;
		पूर्ण
		stat_config.aggr_get_id = perf_stat__get_socket_cached;
		अवरोध;
	हाल AGGR_DIE:
		अगर (cpu_map__build_die_map(evsel_list->core.cpus, &stat_config.aggr_map)) अणु
			लिखो_त्रुटि("cannot build die map");
			वापस -1;
		पूर्ण
		stat_config.aggr_get_id = perf_stat__get_die_cached;
		अवरोध;
	हाल AGGR_CORE:
		अगर (cpu_map__build_core_map(evsel_list->core.cpus, &stat_config.aggr_map)) अणु
			लिखो_त्रुटि("cannot build core map");
			वापस -1;
		पूर्ण
		stat_config.aggr_get_id = perf_stat__get_core_cached;
		अवरोध;
	हाल AGGR_NODE:
		अगर (cpu_map__build_node_map(evsel_list->core.cpus, &stat_config.aggr_map)) अणु
			लिखो_त्रुटि("cannot build core map");
			वापस -1;
		पूर्ण
		stat_config.aggr_get_id = perf_stat__get_node_cached;
		अवरोध;
	हाल AGGR_NONE:
		अगर (term_percore_set()) अणु
			अगर (cpu_map__build_core_map(evsel_list->core.cpus,
						    &stat_config.aggr_map)) अणु
				लिखो_त्रुटि("cannot build core map");
				वापस -1;
			पूर्ण
			stat_config.aggr_get_id = perf_stat__get_core_cached;
		पूर्ण
		अवरोध;
	हाल AGGR_GLOBAL:
	हाल AGGR_THREAD:
	हाल AGGR_UNSET:
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * The evsel_list->cpus is the base we operate on,
	 * taking the highest cpu number to be the size of
	 * the aggregation translate cpumap.
	 */
	nr = perf_cpu_map__max(evsel_list->core.cpus);
	stat_config.cpus_aggr_map = cpu_aggr_map__empty_new(nr + 1);
	वापस stat_config.cpus_aggr_map ? 0 : -ENOMEM;
पूर्ण

अटल व्योम cpu_aggr_map__delete(काष्ठा cpu_aggr_map *map)
अणु
	अगर (map) अणु
		WARN_ONCE(refcount_पढ़ो(&map->refcnt) != 0,
			  "cpu_aggr_map refcnt unbalanced\n");
		मुक्त(map);
	पूर्ण
पूर्ण

अटल व्योम cpu_aggr_map__put(काष्ठा cpu_aggr_map *map)
अणु
	अगर (map && refcount_dec_and_test(&map->refcnt))
		cpu_aggr_map__delete(map);
पूर्ण

अटल व्योम perf_stat__निकास_aggr_mode(व्योम)
अणु
	cpu_aggr_map__put(stat_config.aggr_map);
	cpu_aggr_map__put(stat_config.cpus_aggr_map);
	stat_config.aggr_map = शून्य;
	stat_config.cpus_aggr_map = शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक perf_env__get_cpu(काष्ठा perf_env *env, काष्ठा perf_cpu_map *map, पूर्णांक idx)
अणु
	पूर्णांक cpu;

	अगर (idx > map->nr)
		वापस -1;

	cpu = map->map[idx];

	अगर (cpu >= env->nr_cpus_avail)
		वापस -1;

	वापस cpu;
पूर्ण

अटल काष्ठा aggr_cpu_id perf_env__get_socket(काष्ठा perf_cpu_map *map, पूर्णांक idx, व्योम *data)
अणु
	काष्ठा perf_env *env = data;
	पूर्णांक cpu = perf_env__get_cpu(env, map, idx);
	काष्ठा aggr_cpu_id id = cpu_map__empty_aggr_cpu_id();

	अगर (cpu != -1)
		id.socket = env->cpu[cpu].socket_id;

	वापस id;
पूर्ण

अटल काष्ठा aggr_cpu_id perf_env__get_die(काष्ठा perf_cpu_map *map, पूर्णांक idx, व्योम *data)
अणु
	काष्ठा perf_env *env = data;
	काष्ठा aggr_cpu_id id = cpu_map__empty_aggr_cpu_id();
	पूर्णांक cpu = perf_env__get_cpu(env, map, idx);

	अगर (cpu != -1) अणु
		/*
		 * die_id is relative to socket, so start
		 * with the socket ID and then add die to
		 * make a unique ID.
		 */
		id.socket = env->cpu[cpu].socket_id;
		id.die = env->cpu[cpu].die_id;
	पूर्ण

	वापस id;
पूर्ण

अटल काष्ठा aggr_cpu_id perf_env__get_core(काष्ठा perf_cpu_map *map, पूर्णांक idx, व्योम *data)
अणु
	काष्ठा perf_env *env = data;
	काष्ठा aggr_cpu_id id = cpu_map__empty_aggr_cpu_id();
	पूर्णांक cpu = perf_env__get_cpu(env, map, idx);

	अगर (cpu != -1) अणु
		/*
		 * core_id is relative to socket and die,
		 * we need a global id. So we set
		 * socket, die id and core id
		 */
		id.socket = env->cpu[cpu].socket_id;
		id.die = env->cpu[cpu].die_id;
		id.core = env->cpu[cpu].core_id;
	पूर्ण

	वापस id;
पूर्ण

अटल काष्ठा aggr_cpu_id perf_env__get_node(काष्ठा perf_cpu_map *map, पूर्णांक idx, व्योम *data)
अणु
	पूर्णांक cpu = perf_env__get_cpu(data, map, idx);
	काष्ठा aggr_cpu_id id = cpu_map__empty_aggr_cpu_id();

	id.node = perf_env__numa_node(data, cpu);
	वापस id;
पूर्ण

अटल पूर्णांक perf_env__build_socket_map(काष्ठा perf_env *env, काष्ठा perf_cpu_map *cpus,
				      काष्ठा cpu_aggr_map **sockp)
अणु
	वापस cpu_map__build_map(cpus, sockp, perf_env__get_socket, env);
पूर्ण

अटल पूर्णांक perf_env__build_die_map(काष्ठा perf_env *env, काष्ठा perf_cpu_map *cpus,
				   काष्ठा cpu_aggr_map **diep)
अणु
	वापस cpu_map__build_map(cpus, diep, perf_env__get_die, env);
पूर्ण

अटल पूर्णांक perf_env__build_core_map(काष्ठा perf_env *env, काष्ठा perf_cpu_map *cpus,
				    काष्ठा cpu_aggr_map **corep)
अणु
	वापस cpu_map__build_map(cpus, corep, perf_env__get_core, env);
पूर्ण

अटल पूर्णांक perf_env__build_node_map(काष्ठा perf_env *env, काष्ठा perf_cpu_map *cpus,
				    काष्ठा cpu_aggr_map **nodep)
अणु
	वापस cpu_map__build_map(cpus, nodep, perf_env__get_node, env);
पूर्ण

अटल काष्ठा aggr_cpu_id perf_stat__get_socket_file(काष्ठा perf_stat_config *config __maybe_unused,
				      काष्ठा perf_cpu_map *map, पूर्णांक idx)
अणु
	वापस perf_env__get_socket(map, idx, &perf_stat.session->header.env);
पूर्ण
अटल काष्ठा aggr_cpu_id perf_stat__get_die_file(काष्ठा perf_stat_config *config __maybe_unused,
				   काष्ठा perf_cpu_map *map, पूर्णांक idx)
अणु
	वापस perf_env__get_die(map, idx, &perf_stat.session->header.env);
पूर्ण

अटल काष्ठा aggr_cpu_id perf_stat__get_core_file(काष्ठा perf_stat_config *config __maybe_unused,
				    काष्ठा perf_cpu_map *map, पूर्णांक idx)
अणु
	वापस perf_env__get_core(map, idx, &perf_stat.session->header.env);
पूर्ण

अटल काष्ठा aggr_cpu_id perf_stat__get_node_file(काष्ठा perf_stat_config *config __maybe_unused,
				    काष्ठा perf_cpu_map *map, पूर्णांक idx)
अणु
	वापस perf_env__get_node(map, idx, &perf_stat.session->header.env);
पूर्ण

अटल पूर्णांक perf_stat_init_aggr_mode_file(काष्ठा perf_stat *st)
अणु
	काष्ठा perf_env *env = &st->session->header.env;

	चयन (stat_config.aggr_mode) अणु
	हाल AGGR_SOCKET:
		अगर (perf_env__build_socket_map(env, evsel_list->core.cpus, &stat_config.aggr_map)) अणु
			लिखो_त्रुटि("cannot build socket map");
			वापस -1;
		पूर्ण
		stat_config.aggr_get_id = perf_stat__get_socket_file;
		अवरोध;
	हाल AGGR_DIE:
		अगर (perf_env__build_die_map(env, evsel_list->core.cpus, &stat_config.aggr_map)) अणु
			लिखो_त्रुटि("cannot build die map");
			वापस -1;
		पूर्ण
		stat_config.aggr_get_id = perf_stat__get_die_file;
		अवरोध;
	हाल AGGR_CORE:
		अगर (perf_env__build_core_map(env, evsel_list->core.cpus, &stat_config.aggr_map)) अणु
			लिखो_त्रुटि("cannot build core map");
			वापस -1;
		पूर्ण
		stat_config.aggr_get_id = perf_stat__get_core_file;
		अवरोध;
	हाल AGGR_NODE:
		अगर (perf_env__build_node_map(env, evsel_list->core.cpus, &stat_config.aggr_map)) अणु
			लिखो_त्रुटि("cannot build core map");
			वापस -1;
		पूर्ण
		stat_config.aggr_get_id = perf_stat__get_node_file;
		अवरोध;
	हाल AGGR_NONE:
	हाल AGGR_GLOBAL:
	हाल AGGR_THREAD:
	हाल AGGR_UNSET:
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Add शेष attributes, अगर there were no attributes specअगरied or
 * अगर -d/--detailed, -d -d or -d -d -d is used:
 */
अटल पूर्णांक add_शेष_attributes(व्योम)
अणु
	पूर्णांक err;
	काष्ठा perf_event_attr शेष_attrs0[] = अणु

  अणु .type = PERF_TYPE_SOFTWARE, .config = PERF_COUNT_SW_TASK_CLOCK		पूर्ण,
  अणु .type = PERF_TYPE_SOFTWARE, .config = PERF_COUNT_SW_CONTEXT_SWITCHES	पूर्ण,
  अणु .type = PERF_TYPE_SOFTWARE, .config = PERF_COUNT_SW_CPU_MIGRATIONS		पूर्ण,
  अणु .type = PERF_TYPE_SOFTWARE, .config = PERF_COUNT_SW_PAGE_FAULTS		पूर्ण,

  अणु .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_CPU_CYCLES		पूर्ण,
पूर्ण;
	काष्ठा perf_event_attr frontend_attrs[] = अणु
  अणु .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_STALLED_CYCLES_FRONTEND	पूर्ण,
पूर्ण;
	काष्ठा perf_event_attr backend_attrs[] = अणु
  अणु .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_STALLED_CYCLES_BACKEND	पूर्ण,
पूर्ण;
	काष्ठा perf_event_attr शेष_attrs1[] = अणु
  अणु .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_INSTRUCTIONS		पूर्ण,
  अणु .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_BRANCH_INSTRUCTIONS	पूर्ण,
  अणु .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_BRANCH_MISSES		पूर्ण,

पूर्ण;
	काष्ठा perf_event_attr शेष_sw_attrs[] = अणु
  अणु .type = PERF_TYPE_SOFTWARE, .config = PERF_COUNT_SW_TASK_CLOCK		पूर्ण,
  अणु .type = PERF_TYPE_SOFTWARE, .config = PERF_COUNT_SW_CONTEXT_SWITCHES	पूर्ण,
  अणु .type = PERF_TYPE_SOFTWARE, .config = PERF_COUNT_SW_CPU_MIGRATIONS		पूर्ण,
  अणु .type = PERF_TYPE_SOFTWARE, .config = PERF_COUNT_SW_PAGE_FAULTS		पूर्ण,
पूर्ण;

/*
 * Detailed stats (-d), covering the L1 and last level data caches:
 */
	काष्ठा perf_event_attr detailed_attrs[] = अणु

  अणु .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_L1D		<<  0  |
	(PERF_COUNT_HW_CACHE_OP_READ		<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_ACCESS	<< 16)				पूर्ण,

  अणु .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_L1D		<<  0  |
	(PERF_COUNT_HW_CACHE_OP_READ		<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_MISS	<< 16)				पूर्ण,

  अणु .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_LL			<<  0  |
	(PERF_COUNT_HW_CACHE_OP_READ		<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_ACCESS	<< 16)				पूर्ण,

  अणु .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_LL			<<  0  |
	(PERF_COUNT_HW_CACHE_OP_READ		<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_MISS	<< 16)				पूर्ण,
पूर्ण;

/*
 * Very detailed stats (-d -d), covering the inकाष्ठाion cache and the TLB caches:
 */
	काष्ठा perf_event_attr very_detailed_attrs[] = अणु

  अणु .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_L1I		<<  0  |
	(PERF_COUNT_HW_CACHE_OP_READ		<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_ACCESS	<< 16)				पूर्ण,

  अणु .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_L1I		<<  0  |
	(PERF_COUNT_HW_CACHE_OP_READ		<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_MISS	<< 16)				पूर्ण,

  अणु .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_DTLB		<<  0  |
	(PERF_COUNT_HW_CACHE_OP_READ		<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_ACCESS	<< 16)				पूर्ण,

  अणु .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_DTLB		<<  0  |
	(PERF_COUNT_HW_CACHE_OP_READ		<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_MISS	<< 16)				पूर्ण,

  अणु .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_ITLB		<<  0  |
	(PERF_COUNT_HW_CACHE_OP_READ		<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_ACCESS	<< 16)				पूर्ण,

  अणु .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_ITLB		<<  0  |
	(PERF_COUNT_HW_CACHE_OP_READ		<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_MISS	<< 16)				पूर्ण,

पूर्ण;

/*
 * Very, very detailed stats (-d -d -d), adding prefetch events:
 */
	काष्ठा perf_event_attr very_very_detailed_attrs[] = अणु

  अणु .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_L1D		<<  0  |
	(PERF_COUNT_HW_CACHE_OP_PREFETCH	<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_ACCESS	<< 16)				पूर्ण,

  अणु .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_L1D		<<  0  |
	(PERF_COUNT_HW_CACHE_OP_PREFETCH	<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_MISS	<< 16)				पूर्ण,
पूर्ण;
	काष्ठा parse_events_error errinfo;

	/* Set attrs अगर no event is selected and !null_run: */
	अगर (stat_config.null_run)
		वापस 0;

	bzero(&errinfo, माप(errinfo));
	अगर (transaction_run) अणु
		/* Handle -T as -M transaction. Once platक्रमm specअगरic metrics
		 * support has been added to the json files, all architectures
		 * will use this approach. To determine transaction support
		 * on an architecture test क्रम such a metric name.
		 */
		अगर (metricgroup__has_metric("transaction")) अणु
			काष्ठा option opt = अणु .value = &evsel_list पूर्ण;

			वापस metricgroup__parse_groups(&opt, "transaction",
							 stat_config.metric_no_group,
							stat_config.metric_no_merge,
							 &stat_config.metric_events);
		पूर्ण

		अगर (pmu_have_event("cpu", "cycles-ct") &&
		    pmu_have_event("cpu", "el-start"))
			err = parse_events(evsel_list, transaction_attrs,
					   &errinfo);
		अन्यथा
			err = parse_events(evsel_list,
					   transaction_limited_attrs,
					   &errinfo);
		अगर (err) अणु
			ख_लिखो(मानक_त्रुटि, "Cannot set up transaction events\n");
			parse_events_prपूर्णांक_error(&errinfo, transaction_attrs);
			वापस -1;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (smi_cost) अणु
		पूर्णांक smi;

		अगर (sysfs__पढ़ो_पूर्णांक(FREEZE_ON_SMI_PATH, &smi) < 0) अणु
			ख_लिखो(मानक_त्रुटि, "freeze_on_smi is not supported.\n");
			वापस -1;
		पूर्ण

		अगर (!smi) अणु
			अगर (sysfs__ग_लिखो_पूर्णांक(FREEZE_ON_SMI_PATH, 1) < 0) अणु
				ख_लिखो(मानक_त्रुटि, "Failed to set freeze_on_smi.\n");
				वापस -1;
			पूर्ण
			smi_reset = true;
		पूर्ण

		अगर (pmu_have_event("msr", "aperf") &&
		    pmu_have_event("msr", "smi")) अणु
			अगर (!क्रमce_metric_only)
				stat_config.metric_only = true;
			err = parse_events(evsel_list, smi_cost_attrs, &errinfo);
		पूर्ण अन्यथा अणु
			ख_लिखो(मानक_त्रुटि, "To measure SMI cost, it needs "
				"msr/aperf/, msr/smi/ and cpu/cycles/ support\n");
			parse_events_prपूर्णांक_error(&errinfo, smi_cost_attrs);
			वापस -1;
		पूर्ण
		अगर (err) अणु
			parse_events_prपूर्णांक_error(&errinfo, smi_cost_attrs);
			ख_लिखो(मानक_त्रुटि, "Cannot set up SMI cost events\n");
			वापस -1;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (topकरोwn_run) अणु
		स्थिर अक्षर **metric_attrs = topकरोwn_metric_attrs;
		अचिन्हित पूर्णांक max_level = 1;
		अक्षर *str = शून्य;
		bool warn = false;

		अगर (!क्रमce_metric_only)
			stat_config.metric_only = true;

		अगर (pmu_have_event("cpu", topकरोwn_metric_L2_attrs[5])) अणु
			metric_attrs = topकरोwn_metric_L2_attrs;
			max_level = 2;
		पूर्ण

		अगर (stat_config.topकरोwn_level > max_level) अणु
			pr_err("Invalid top-down metrics level. The max level is %u.\n", max_level);
			वापस -1;
		पूर्ण अन्यथा अगर (!stat_config.topकरोwn_level)
			stat_config.topकरोwn_level = max_level;

		अगर (topकरोwn_filter_events(metric_attrs, &str, 1) < 0) अणु
			pr_err("Out of memory\n");
			वापस -1;
		पूर्ण
		अगर (metric_attrs[0] && str) अणु
			अगर (!stat_config.पूर्णांकerval && !stat_config.metric_only) अणु
				ख_लिखो(stat_config.output,
					"Topdown accuracy may decrease when measuring long periods.\n"
					"Please print the result regularly, e.g. -I1000\n");
			पूर्ण
			जाओ setup_metrics;
		पूर्ण

		zमुक्त(&str);

		अगर (stat_config.aggr_mode != AGGR_GLOBAL &&
		    stat_config.aggr_mode != AGGR_CORE) अणु
			pr_err("top down event configuration requires --per-core mode\n");
			वापस -1;
		पूर्ण
		stat_config.aggr_mode = AGGR_CORE;
		अगर (nr_cgroups || !target__has_cpu(&target)) अणु
			pr_err("top down event configuration requires system-wide mode (-a)\n");
			वापस -1;
		पूर्ण

		अगर (topकरोwn_filter_events(topकरोwn_attrs, &str,
				arch_topकरोwn_check_group(&warn)) < 0) अणु
			pr_err("Out of memory\n");
			वापस -1;
		पूर्ण
		अगर (topकरोwn_attrs[0] && str) अणु
			अगर (warn)
				arch_topकरोwn_group_warn();
setup_metrics:
			err = parse_events(evsel_list, str, &errinfo);
			अगर (err) अणु
				ख_लिखो(मानक_त्रुटि,
					"Cannot set up top down events %s: %d\n",
					str, err);
				parse_events_prपूर्णांक_error(&errinfo, str);
				मुक्त(str);
				वापस -1;
			पूर्ण
		पूर्ण अन्यथा अणु
			ख_लिखो(मानक_त्रुटि, "System does not support topdown\n");
			वापस -1;
		पूर्ण
		मुक्त(str);
	पूर्ण

	अगर (!evsel_list->core.nr_entries) अणु
		अगर (perf_pmu__has_hybrid()) अणु
			स्थिर अक्षर *hybrid_str = "cycles,instructions,branches,branch-misses";

			अगर (target__has_cpu(&target))
				शेष_sw_attrs[0].config = PERF_COUNT_SW_CPU_CLOCK;

			अगर (evlist__add_शेष_attrs(evsel_list,
						      शेष_sw_attrs) < 0) अणु
				वापस -1;
			पूर्ण

			err = parse_events(evsel_list, hybrid_str, &errinfo);
			अगर (err) अणु
				ख_लिखो(मानक_त्रुटि,
					"Cannot set up hybrid events %s: %d\n",
					hybrid_str, err);
				parse_events_prपूर्णांक_error(&errinfo, hybrid_str);
				वापस -1;
			पूर्ण
			वापस err;
		पूर्ण

		अगर (target__has_cpu(&target))
			शेष_attrs0[0].config = PERF_COUNT_SW_CPU_CLOCK;

		अगर (evlist__add_शेष_attrs(evsel_list, शेष_attrs0) < 0)
			वापस -1;
		अगर (pmu_have_event("cpu", "stalled-cycles-frontend")) अणु
			अगर (evlist__add_शेष_attrs(evsel_list, frontend_attrs) < 0)
				वापस -1;
		पूर्ण
		अगर (pmu_have_event("cpu", "stalled-cycles-backend")) अणु
			अगर (evlist__add_शेष_attrs(evsel_list, backend_attrs) < 0)
				वापस -1;
		पूर्ण
		अगर (evlist__add_शेष_attrs(evsel_list, शेष_attrs1) < 0)
			वापस -1;

		अगर (arch_evlist__add_शेष_attrs(evsel_list) < 0)
			वापस -1;
	पूर्ण

	/* Detailed events get appended to the event list: */

	अगर (detailed_run <  1)
		वापस 0;

	/* Append detailed run extra attributes: */
	अगर (evlist__add_शेष_attrs(evsel_list, detailed_attrs) < 0)
		वापस -1;

	अगर (detailed_run < 2)
		वापस 0;

	/* Append very detailed run extra attributes: */
	अगर (evlist__add_शेष_attrs(evsel_list, very_detailed_attrs) < 0)
		वापस -1;

	अगर (detailed_run < 3)
		वापस 0;

	/* Append very, very detailed run extra attributes: */
	वापस evlist__add_शेष_attrs(evsel_list, very_very_detailed_attrs);
पूर्ण

अटल स्थिर अक्षर * स्थिर stat_record_usage[] = अणु
	"perf stat record [<options>]",
	शून्य,
पूर्ण;

अटल व्योम init_features(काष्ठा perf_session *session)
अणु
	पूर्णांक feat;

	क्रम (feat = HEADER_FIRST_FEATURE; feat < HEADER_LAST_FEATURE; feat++)
		perf_header__set_feat(&session->header, feat);

	perf_header__clear_feat(&session->header, HEADER_सूची_FORMAT);
	perf_header__clear_feat(&session->header, HEADER_BUILD_ID);
	perf_header__clear_feat(&session->header, HEADER_TRACING_DATA);
	perf_header__clear_feat(&session->header, HEADER_BRANCH_STACK);
	perf_header__clear_feat(&session->header, HEADER_AUXTRACE);
पूर्ण

अटल पूर्णांक __cmd_record(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा perf_session *session;
	काष्ठा perf_data *data = &perf_stat.data;

	argc = parse_options(argc, argv, stat_options, stat_record_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION);

	अगर (output_name)
		data->path = output_name;

	अगर (stat_config.run_count != 1 || क्रमever) अणु
		pr_err("Cannot use -r option with perf stat record.\n");
		वापस -1;
	पूर्ण

	session = perf_session__new(data, false, शून्य);
	अगर (IS_ERR(session)) अणु
		pr_err("Perf session creation failed\n");
		वापस PTR_ERR(session);
	पूर्ण

	init_features(session);

	session->evlist   = evsel_list;
	perf_stat.session = session;
	perf_stat.record  = true;
	वापस argc;
पूर्ण

अटल पूर्णांक process_stat_round_event(काष्ठा perf_session *session,
				    जोड़ perf_event *event)
अणु
	काष्ठा perf_record_stat_round *stat_round = &event->stat_round;
	काष्ठा evsel *counter;
	काष्ठा बारpec tsh, *ts = शून्य;
	स्थिर अक्षर **argv = session->header.env.cmdline_argv;
	पूर्णांक argc = session->header.env.nr_cmdline;

	evlist__क्रम_each_entry(evsel_list, counter)
		perf_stat_process_counter(&stat_config, counter);

	अगर (stat_round->type == PERF_STAT_ROUND_TYPE__FINAL)
		update_stats(&wallसमय_nsecs_stats, stat_round->समय);

	अगर (stat_config.पूर्णांकerval && stat_round->समय) अणु
		tsh.tv_sec  = stat_round->समय / NSEC_PER_SEC;
		tsh.tv_nsec = stat_round->समय % NSEC_PER_SEC;
		ts = &tsh;
	पूर्ण

	prपूर्णांक_counters(ts, argc, argv);
	वापस 0;
पूर्ण

अटल
पूर्णांक process_stat_config_event(काष्ठा perf_session *session,
			      जोड़ perf_event *event)
अणु
	काष्ठा perf_tool *tool = session->tool;
	काष्ठा perf_stat *st = container_of(tool, काष्ठा perf_stat, tool);

	perf_event__पढ़ो_stat_config(&stat_config, &event->stat_config);

	अगर (perf_cpu_map__empty(st->cpus)) अणु
		अगर (st->aggr_mode != AGGR_UNSET)
			pr_warning("warning: processing task data, aggregation mode not set\n");
		वापस 0;
	पूर्ण

	अगर (st->aggr_mode != AGGR_UNSET)
		stat_config.aggr_mode = st->aggr_mode;

	अगर (perf_stat.data.is_pipe)
		perf_stat_init_aggr_mode();
	अन्यथा
		perf_stat_init_aggr_mode_file(st);

	वापस 0;
पूर्ण

अटल पूर्णांक set_maps(काष्ठा perf_stat *st)
अणु
	अगर (!st->cpus || !st->thपढ़ोs)
		वापस 0;

	अगर (WARN_ONCE(st->maps_allocated, "stats double allocation\n"))
		वापस -EINVAL;

	perf_evlist__set_maps(&evsel_list->core, st->cpus, st->thपढ़ोs);

	अगर (evlist__alloc_stats(evsel_list, true))
		वापस -ENOMEM;

	st->maps_allocated = true;
	वापस 0;
पूर्ण

अटल
पूर्णांक process_thपढ़ो_map_event(काष्ठा perf_session *session,
			     जोड़ perf_event *event)
अणु
	काष्ठा perf_tool *tool = session->tool;
	काष्ठा perf_stat *st = container_of(tool, काष्ठा perf_stat, tool);

	अगर (st->thपढ़ोs) अणु
		pr_warning("Extra thread map event, ignoring.\n");
		वापस 0;
	पूर्ण

	st->thपढ़ोs = thपढ़ो_map__new_event(&event->thपढ़ो_map);
	अगर (!st->thपढ़ोs)
		वापस -ENOMEM;

	वापस set_maps(st);
पूर्ण

अटल
पूर्णांक process_cpu_map_event(काष्ठा perf_session *session,
			  जोड़ perf_event *event)
अणु
	काष्ठा perf_tool *tool = session->tool;
	काष्ठा perf_stat *st = container_of(tool, काष्ठा perf_stat, tool);
	काष्ठा perf_cpu_map *cpus;

	अगर (st->cpus) अणु
		pr_warning("Extra cpu map event, ignoring.\n");
		वापस 0;
	पूर्ण

	cpus = cpu_map__new_data(&event->cpu_map.data);
	अगर (!cpus)
		वापस -ENOMEM;

	st->cpus = cpus;
	वापस set_maps(st);
पूर्ण

अटल स्थिर अक्षर * स्थिर stat_report_usage[] = अणु
	"perf stat report [<options>]",
	शून्य,
पूर्ण;

अटल काष्ठा perf_stat perf_stat = अणु
	.tool = अणु
		.attr		= perf_event__process_attr,
		.event_update	= perf_event__process_event_update,
		.thपढ़ो_map	= process_thपढ़ो_map_event,
		.cpu_map	= process_cpu_map_event,
		.stat_config	= process_stat_config_event,
		.stat		= perf_event__process_stat_event,
		.stat_round	= process_stat_round_event,
	पूर्ण,
	.aggr_mode = AGGR_UNSET,
पूर्ण;

अटल पूर्णांक __cmd_report(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा perf_session *session;
	स्थिर काष्ठा option options[] = अणु
	OPT_STRING('i', "input", &input_name, "file", "input file name"),
	OPT_SET_UINT(0, "per-socket", &perf_stat.aggr_mode,
		     "aggregate counts per processor socket", AGGR_SOCKET),
	OPT_SET_UINT(0, "per-die", &perf_stat.aggr_mode,
		     "aggregate counts per processor die", AGGR_DIE),
	OPT_SET_UINT(0, "per-core", &perf_stat.aggr_mode,
		     "aggregate counts per physical processor core", AGGR_CORE),
	OPT_SET_UINT(0, "per-node", &perf_stat.aggr_mode,
		     "aggregate counts per numa node", AGGR_NODE),
	OPT_SET_UINT('A', "no-aggr", &perf_stat.aggr_mode,
		     "disable CPU count aggregation", AGGR_NONE),
	OPT_END()
	पूर्ण;
	काष्ठा stat st;
	पूर्णांक ret;

	argc = parse_options(argc, argv, options, stat_report_usage, 0);

	अगर (!input_name || !म_माप(input_name)) अणु
		अगर (!ख_स्थिति(STDIN_खाताNO, &st) && S_ISFIFO(st.st_mode))
			input_name = "-";
		अन्यथा
			input_name = "perf.data";
	पूर्ण

	perf_stat.data.path = input_name;
	perf_stat.data.mode = PERF_DATA_MODE_READ;

	session = perf_session__new(&perf_stat.data, false, &perf_stat.tool);
	अगर (IS_ERR(session))
		वापस PTR_ERR(session);

	perf_stat.session  = session;
	stat_config.output = मानक_त्रुटि;
	evsel_list         = session->evlist;

	ret = perf_session__process_events(session);
	अगर (ret)
		वापस ret;

	perf_session__delete(session);
	वापस 0;
पूर्ण

अटल व्योम setup_प्रणाली_wide(पूर्णांक विभाजनs)
अणु
	/*
	 * Make प्रणाली wide (-a) the शेष target अगर
	 * no target was specअगरied and one of following
	 * conditions is met:
	 *
	 *   - there's no workload specअगरied
	 *   - there is workload specअगरied but all requested
	 *     events are प्रणाली wide events
	 */
	अगर (!target__none(&target))
		वापस;

	अगर (!विभाजनs)
		target.प्रणाली_wide = true;
	अन्यथा अणु
		काष्ठा evsel *counter;

		evlist__क्रम_each_entry(evsel_list, counter) अणु
			अगर (!counter->core.प्रणाली_wide &&
			    म_भेद(counter->name, "duration_time")) अणु
				वापस;
			पूर्ण
		पूर्ण

		अगर (evsel_list->core.nr_entries)
			target.प्रणाली_wide = true;
	पूर्ण
पूर्ण

पूर्णांक cmd_stat(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	स्थिर अक्षर * स्थिर stat_usage[] = अणु
		"perf stat [<options>] [<command>]",
		शून्य
	पूर्ण;
	पूर्णांक status = -EINVAL, run_idx, err;
	स्थिर अक्षर *mode;
	खाता *output = मानक_त्रुटि;
	अचिन्हित पूर्णांक पूर्णांकerval, समयout;
	स्थिर अक्षर * स्थिर stat_subcommands[] = अणु "record", "report" पूर्ण;
	अक्षर errbuf[बफ_मान];

	रखो_क्षेत्र(LC_ALL, "");

	evsel_list = evlist__new();
	अगर (evsel_list == शून्य)
		वापस -ENOMEM;

	parse_events__shrink_config_terms();

	/* String-parsing callback-based options would segfault when negated */
	set_option_flag(stat_options, 'e', "event", PARSE_OPT_NONEG);
	set_option_flag(stat_options, 'M', "metrics", PARSE_OPT_NONEG);
	set_option_flag(stat_options, 'G', "cgroup", PARSE_OPT_NONEG);

	argc = parse_options_subcommand(argc, argv, stat_options, stat_subcommands,
					(स्थिर अक्षर **) stat_usage,
					PARSE_OPT_STOP_AT_NON_OPTION);
	perf_stat__collect_metric_expr(evsel_list);
	perf_stat__init_shaकरोw_stats();

	अगर (stat_config.csv_sep) अणु
		stat_config.csv_output = true;
		अगर (!म_भेद(stat_config.csv_sep, "\\t"))
			stat_config.csv_sep = "\t";
	पूर्ण अन्यथा
		stat_config.csv_sep = DEFAULT_SEPARATOR;

	अगर (argc && !म_भेदन(argv[0], "rec", 3)) अणु
		argc = __cmd_record(argc, argv);
		अगर (argc < 0)
			वापस -1;
	पूर्ण अन्यथा अगर (argc && !म_भेदन(argv[0], "rep", 3))
		वापस __cmd_report(argc, argv);

	पूर्णांकerval = stat_config.पूर्णांकerval;
	समयout = stat_config.समयout;

	/*
	 * For record command the -o is alपढ़ोy taken care of.
	 */
	अगर (!STAT_RECORD && output_name && म_भेद(output_name, "-"))
		output = शून्य;

	अगर (output_name && output_fd) अणु
		ख_लिखो(मानक_त्रुटि, "cannot use both --output and --log-fd\n");
		parse_options_usage(stat_usage, stat_options, "o", 1);
		parse_options_usage(शून्य, stat_options, "log-fd", 0);
		जाओ out;
	पूर्ण

	अगर (stat_config.metric_only && stat_config.aggr_mode == AGGR_THREAD) अणु
		ख_लिखो(मानक_त्रुटि, "--metric-only is not supported with --per-thread\n");
		जाओ out;
	पूर्ण

	अगर (stat_config.metric_only && stat_config.run_count > 1) अणु
		ख_लिखो(मानक_त्रुटि, "--metric-only is not supported with -r\n");
		जाओ out;
	पूर्ण

	अगर (stat_config.wallसमय_run_table && stat_config.run_count <= 1) अणु
		ख_लिखो(मानक_त्रुटि, "--table is only supported with -r\n");
		parse_options_usage(stat_usage, stat_options, "r", 1);
		parse_options_usage(शून्य, stat_options, "table", 0);
		जाओ out;
	पूर्ण

	अगर (output_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "argument to --log-fd must be a > 0\n");
		parse_options_usage(stat_usage, stat_options, "log-fd", 0);
		जाओ out;
	पूर्ण

	अगर (!output && !stat_config.quiet) अणु
		काष्ठा बारpec पंचांग;
		mode = append_file ? "a" : "w";

		output = ख_खोलो(output_name, mode);
		अगर (!output) अणु
			लिखो_त्रुटि("failed to create output file");
			वापस -1;
		पूर्ण
		घड़ी_समय_लो(CLOCK_REALTIME, &पंचांग);
		ख_लिखो(output, "# started on %s\n", स_समय(&पंचांग.tv_sec));
	पूर्ण अन्यथा अगर (output_fd > 0) अणु
		mode = append_file ? "a" : "w";
		output = fकरोpen(output_fd, mode);
		अगर (!output) अणु
			लिखो_त्रुटि("Failed opening logfd");
			वापस -त्रुटि_सं;
		पूर्ण
	पूर्ण

	stat_config.output = output;

	/*
	 * let the spपढ़ोsheet करो the pretty-prपूर्णांकing
	 */
	अगर (stat_config.csv_output) अणु
		/* User explicitly passed -B? */
		अगर (big_num_opt == 1) अणु
			ख_लिखो(मानक_त्रुटि, "-B option not supported with -x\n");
			parse_options_usage(stat_usage, stat_options, "B", 1);
			parse_options_usage(शून्य, stat_options, "x", 1);
			जाओ out;
		पूर्ण अन्यथा /* Nope, so disable big number क्रमmatting */
			stat_config.big_num = false;
	पूर्ण अन्यथा अगर (big_num_opt == 0) /* User passed --no-big-num */
		stat_config.big_num = false;

	err = target__validate(&target);
	अगर (err) अणु
		target__म_त्रुटि(&target, err, errbuf, बफ_मान);
		pr_warning("%s\n", errbuf);
	पूर्ण

	setup_प्रणाली_wide(argc);

	/*
	 * Display user/प्रणाली बार only क्रम single
	 * run and when there's specअगरied tracee.
	 */
	अगर ((stat_config.run_count == 1) && target__none(&target))
		stat_config.ru_display = true;

	अगर (stat_config.run_count < 0) अणु
		pr_err("Run count must be a positive number\n");
		parse_options_usage(stat_usage, stat_options, "r", 1);
		जाओ out;
	पूर्ण अन्यथा अगर (stat_config.run_count == 0) अणु
		क्रमever = true;
		stat_config.run_count = 1;
	पूर्ण

	अगर (stat_config.wallसमय_run_table) अणु
		stat_config.wallसमय_run = zalloc(stat_config.run_count * माप(stat_config.wallसमय_run[0]));
		अगर (!stat_config.wallसमय_run) अणु
			pr_err("failed to setup -r option");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर ((stat_config.aggr_mode == AGGR_THREAD) &&
		!target__has_task(&target)) अणु
		अगर (!target.प्रणाली_wide || target.cpu_list) अणु
			ख_लिखो(मानक_त्रुटि, "The --per-thread option is only "
				"available when monitoring via -p -t -a "
				"options or only --per-thread.\n");
			parse_options_usage(शून्य, stat_options, "p", 1);
			parse_options_usage(शून्य, stat_options, "t", 1);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * no_aggr, cgroup are क्रम प्रणाली-wide only
	 * --per-thपढ़ो is aggregated per thपढ़ो, we करोnt mix it with cpu mode
	 */
	अगर (((stat_config.aggr_mode != AGGR_GLOBAL &&
	      stat_config.aggr_mode != AGGR_THREAD) || nr_cgroups) &&
	    !target__has_cpu(&target)) अणु
		ख_लिखो(मानक_त्रुटि, "both cgroup and no-aggregation "
			"modes only available in system-wide mode\n");

		parse_options_usage(stat_usage, stat_options, "G", 1);
		parse_options_usage(शून्य, stat_options, "A", 1);
		parse_options_usage(शून्य, stat_options, "a", 1);
		जाओ out;
	पूर्ण

	अगर (stat_config.iostat_run) अणु
		status = iostat_prepare(evsel_list, &stat_config);
		अगर (status)
			जाओ out;
		अगर (iostat_mode == IOSTAT_LIST) अणु
			iostat_list(evsel_list, &stat_config);
			जाओ out;
		पूर्ण अन्यथा अगर (verbose)
			iostat_list(evsel_list, &stat_config);
	पूर्ण

	अगर (add_शेष_attributes())
		जाओ out;

	अगर (stat_config.cgroup_list) अणु
		अगर (nr_cgroups > 0) अणु
			pr_err("--cgroup and --for-each-cgroup cannot be used together\n");
			parse_options_usage(stat_usage, stat_options, "G", 1);
			parse_options_usage(शून्य, stat_options, "for-each-cgroup", 0);
			जाओ out;
		पूर्ण

		अगर (evlist__expand_cgroup(evsel_list, stat_config.cgroup_list,
					  &stat_config.metric_events, true) < 0) अणु
			parse_options_usage(stat_usage, stat_options,
					    "for-each-cgroup", 0);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर ((stat_config.aggr_mode == AGGR_THREAD) && (target.प्रणाली_wide))
		target.per_thपढ़ो = true;

	अगर (evlist__create_maps(evsel_list, &target) < 0) अणु
		अगर (target__has_task(&target)) अणु
			pr_err("Problems finding threads of monitor\n");
			parse_options_usage(stat_usage, stat_options, "p", 1);
			parse_options_usage(शून्य, stat_options, "t", 1);
		पूर्ण अन्यथा अगर (target__has_cpu(&target)) अणु
			लिखो_त्रुटि("failed to parse CPUs map");
			parse_options_usage(stat_usage, stat_options, "C", 1);
			parse_options_usage(शून्य, stat_options, "a", 1);
		पूर्ण
		जाओ out;
	पूर्ण

	evlist__check_cpu_maps(evsel_list);

	अगर (perf_pmu__has_hybrid())
		stat_config.no_merge = true;

	/*
	 * Initialize thपढ़ो_map with comm names,
	 * so we could prपूर्णांक it out on output.
	 */
	अगर (stat_config.aggr_mode == AGGR_THREAD) अणु
		thपढ़ो_map__पढ़ो_comms(evsel_list->core.thपढ़ोs);
		अगर (target.प्रणाली_wide) अणु
			अगर (runसमय_stat_new(&stat_config,
				perf_thपढ़ो_map__nr(evsel_list->core.thपढ़ोs))) अणु
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (stat_config.aggr_mode == AGGR_NODE)
		cpu__setup_cpunode_map();

	अगर (stat_config.बार && पूर्णांकerval)
		पूर्णांकerval_count = true;
	अन्यथा अगर (stat_config.बार && !पूर्णांकerval) अणु
		pr_err("interval-count option should be used together with "
				"interval-print.\n");
		parse_options_usage(stat_usage, stat_options, "interval-count", 0);
		parse_options_usage(stat_usage, stat_options, "I", 1);
		जाओ out;
	पूर्ण

	अगर (समयout && समयout < 100) अणु
		अगर (समयout < 10) अणु
			pr_err("timeout must be >= 10ms.\n");
			parse_options_usage(stat_usage, stat_options, "timeout", 0);
			जाओ out;
		पूर्ण अन्यथा
			pr_warning("timeout < 100ms. "
				   "The overhead percentage could be high in some cases. "
				   "Please proceed with caution.\n");
	पूर्ण
	अगर (समयout && पूर्णांकerval) अणु
		pr_err("timeout option is not supported with interval-print.\n");
		parse_options_usage(stat_usage, stat_options, "timeout", 0);
		parse_options_usage(stat_usage, stat_options, "I", 1);
		जाओ out;
	पूर्ण

	अगर (evlist__alloc_stats(evsel_list, पूर्णांकerval))
		जाओ out;

	अगर (perf_stat_init_aggr_mode())
		जाओ out;

	/*
	 * Set sample_type to PERF_SAMPLE_IDENTIFIER, which should be harmless
	 * जबतक aव्योमing that older tools show confusing messages.
	 *
	 * However क्रम pipe sessions we need to keep it zero,
	 * because script's perf_evsel__check_attr is triggered
	 * by attr->sample_type != 0, and we can't run it on
	 * stat sessions.
	 */
	stat_config.identअगरier = !(STAT_RECORD && perf_stat.data.is_pipe);

	/*
	 * We करोnt want to block the संकेतs - that would cause
	 * child tasks to inherit that and Ctrl-C would not work.
	 * What we want is क्रम Ctrl-C to work in the exec()-ed
	 * task, but being ignored by perf stat itself:
	 */
	निकास_पर(sig_निकास_पर);
	अगर (!क्रमever)
		संकेत(संक_विघ्न,  skip_संकेत);
	संकेत(SIGCHLD, skip_संकेत);
	संकेत(SIGALRM, skip_संकेत);
	संकेत(SIGABRT, skip_संकेत);

	अगर (evlist__initialize_ctlfd(evsel_list, stat_config.ctl_fd, stat_config.ctl_fd_ack))
		जाओ out;

	status = 0;
	क्रम (run_idx = 0; क्रमever || run_idx < stat_config.run_count; run_idx++) अणु
		अगर (stat_config.run_count != 1 && verbose > 0)
			ख_लिखो(output, "[ perf stat: executing run #%d ... ]\n",
				run_idx + 1);

		अगर (run_idx != 0)
			evlist__reset_prev_raw_counts(evsel_list);

		status = run_perf_stat(argc, argv, run_idx);
		अगर (क्रमever && status != -1 && !पूर्णांकerval) अणु
			prपूर्णांक_counters(शून्य, argc, argv);
			perf_stat__reset_stats();
		पूर्ण
	पूर्ण

	अगर (!क्रमever && status != -1 && (!पूर्णांकerval || stat_config.summary))
		prपूर्णांक_counters(शून्य, argc, argv);

	evlist__finalize_ctlfd(evsel_list);

	अगर (STAT_RECORD) अणु
		/*
		 * We synthesize the kernel mmap record just so that older tools
		 * करोn't emit warnings about not being able to resolve symbols
		 * due to /proc/sys/kernel/kptr_restrict settings and instead provide
		 * a saner message about no samples being in the perf.data file.
		 *
		 * This also serves to suppress a warning about f_header.data.size == 0
		 * in header.c at the moment 'perf stat record' माला_लो पूर्णांकroduced, which
		 * is not really needed once we start adding the stat specअगरic PERF_RECORD_
		 * records, but the need to suppress the kptr_restrict messages in older
		 * tools reमुख्य  -acme
		 */
		पूर्णांक fd = perf_data__fd(&perf_stat.data);

		err = perf_event__synthesize_kernel_mmap((व्योम *)&perf_stat,
							 process_synthesized_event,
							 &perf_stat.session->machines.host);
		अगर (err) अणु
			pr_warning("Couldn't synthesize the kernel mmap record, harmless, "
				   "older tools may produce warnings about this file\n.");
		पूर्ण

		अगर (!पूर्णांकerval) अणु
			अगर (WRITE_STAT_ROUND_EVENT(wallसमय_nsecs_stats.max, FINAL))
				pr_err("failed to write stat round event\n");
		पूर्ण

		अगर (!perf_stat.data.is_pipe) अणु
			perf_stat.session->header.data_size += perf_stat.bytes_written;
			perf_session__ग_लिखो_header(perf_stat.session, evsel_list, fd, true);
		पूर्ण

		evlist__बंद(evsel_list);
		perf_session__delete(perf_stat.session);
	पूर्ण

	perf_stat__निकास_aggr_mode();
	evlist__मुक्त_stats(evsel_list);
out:
	अगर (stat_config.iostat_run)
		iostat_release(evsel_list);

	zमुक्त(&stat_config.wallसमय_run);

	अगर (smi_cost && smi_reset)
		sysfs__ग_लिखो_पूर्णांक(FREEZE_ON_SMI_PATH, 0);

	evlist__delete(evsel_list);

	metricgroup__rblist_निकास(&stat_config.metric_events);
	runसमय_stat_delete(&stat_config);
	evlist__बंद_control(stat_config.ctl_fd, stat_config.ctl_fd_ack, &stat_config.ctl_fd_बंद);

	वापस status;
पूर्ण
