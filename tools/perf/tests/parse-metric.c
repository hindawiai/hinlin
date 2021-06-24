<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश <माला.स>
#समावेश <perf/cpumap.h>
#समावेश <perf/evlist.h>
#समावेश "metricgroup.h"
#समावेश "tests.h"
#समावेश "pmu-events/pmu-events.h"
#समावेश "evlist.h"
#समावेश "rblist.h"
#समावेश "debug.h"
#समावेश "expr.h"
#समावेश "stat.h"
#समावेश "pmu.h"

अटल काष्ठा pmu_event pme_test[] = अणु
अणु
	.metric_expr	= "inst_retired.any / cpu_clk_unhalted.thread",
	.metric_name	= "IPC",
	.metric_group	= "group1",
पूर्ण,
अणु
	.metric_expr	= "idq_uops_not_delivered.core / (4 * (( ( cpu_clk_unhalted.thread / 2 ) * "
			  "( 1 + cpu_clk_unhalted.one_thread_active / cpu_clk_unhalted.ref_xclk ) )))",
	.metric_name	= "Frontend_Bound_SMT",
पूर्ण,
अणु
	.metric_expr	= "l1d\\-loads\\-misses / inst_retired.any",
	.metric_name	= "dcache_miss_cpi",
पूर्ण,
अणु
	.metric_expr	= "l1i\\-loads\\-misses / inst_retired.any",
	.metric_name	= "icache_miss_cycles",
पूर्ण,
अणु
	.metric_expr	= "(dcache_miss_cpi + icache_miss_cycles)",
	.metric_name	= "cache_miss_cycles",
	.metric_group	= "group1",
पूर्ण,
अणु
	.metric_expr	= "l2_rqsts.demand_data_rd_hit + l2_rqsts.pf_hit + l2_rqsts.rfo_hit",
	.metric_name	= "DCache_L2_All_Hits",
पूर्ण,
अणु
	.metric_expr	= "max(l2_rqsts.all_demand_data_rd - l2_rqsts.demand_data_rd_hit, 0) + "
			  "l2_rqsts.pf_miss + l2_rqsts.rfo_miss",
	.metric_name	= "DCache_L2_All_Miss",
पूर्ण,
अणु
	.metric_expr	= "dcache_l2_all_hits + dcache_l2_all_miss",
	.metric_name	= "DCache_L2_All",
पूर्ण,
अणु
	.metric_expr	= "d_ratio(dcache_l2_all_hits, dcache_l2_all)",
	.metric_name	= "DCache_L2_Hits",
पूर्ण,
अणु
	.metric_expr	= "d_ratio(dcache_l2_all_miss, dcache_l2_all)",
	.metric_name	= "DCache_L2_Misses",
पूर्ण,
अणु
	.metric_expr	= "ipc + m2",
	.metric_name	= "M1",
पूर्ण,
अणु
	.metric_expr	= "ipc + m1",
	.metric_name	= "M2",
पूर्ण,
अणु
	.metric_expr	= "1/m3",
	.metric_name	= "M3",
पूर्ण,
अणु
	.metric_expr	= "64 * l1d.replacement / 1000000000 / duration_time",
	.metric_name	= "L1D_Cache_Fill_BW",
पूर्ण,
अणु
	.name	= शून्य,
पूर्ण
पूर्ण;

अटल काष्ठा pmu_events_map map = अणु
	.cpuid		= "test",
	.version	= "1",
	.type		= "core",
	.table		= pme_test,
पूर्ण;

काष्ठा value अणु
	स्थिर अक्षर	*event;
	u64		 val;
पूर्ण;

अटल u64 find_value(स्थिर अक्षर *name, काष्ठा value *values)
अणु
	काष्ठा value *v = values;

	जबतक (v->event) अणु
		अगर (!म_भेद(name, v->event))
			वापस v->val;
		v++;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम load_runसमय_stat(काष्ठा runसमय_stat *st, काष्ठा evlist *evlist,
			      काष्ठा value *vals)
अणु
	काष्ठा evsel *evsel;
	u64 count;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		count = find_value(evsel->name, vals);
		perf_stat__update_shaकरोw_stats(evsel, count, 0, st);
		अगर (!म_भेद(evsel->name, "duration_time"))
			update_stats(&wallसमय_nsecs_stats, count);
	पूर्ण
पूर्ण

अटल द्विगुन compute_single(काष्ठा rblist *metric_events, काष्ठा evlist *evlist,
			     काष्ठा runसमय_stat *st, स्थिर अक्षर *name)
अणु
	काष्ठा metric_expr *mexp;
	काष्ठा metric_event *me;
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		me = metricgroup__lookup(metric_events, evsel, false);
		अगर (me != शून्य) अणु
			list_क्रम_each_entry (mexp, &me->head, nd) अणु
				अगर (म_भेद(mexp->metric_name, name))
					जारी;
				वापस test_generic_metric(mexp, 0, st);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0.;
पूर्ण

अटल पूर्णांक __compute_metric(स्थिर अक्षर *name, काष्ठा value *vals,
			    स्थिर अक्षर *name1, द्विगुन *ratio1,
			    स्थिर अक्षर *name2, द्विगुन *ratio2)
अणु
	काष्ठा rblist metric_events = अणु
		.nr_entries = 0,
	पूर्ण;
	काष्ठा perf_cpu_map *cpus;
	काष्ठा runसमय_stat st;
	काष्ठा evlist *evlist;
	पूर्णांक err;

	/*
	 * We need to prepare evlist क्रम stat mode running on CPU 0
	 * because that's where all the stats are going to be created.
	 */
	evlist = evlist__new();
	अगर (!evlist)
		वापस -ENOMEM;

	cpus = perf_cpu_map__new("0");
	अगर (!cpus) अणु
		evlist__delete(evlist);
		वापस -ENOMEM;
	पूर्ण

	perf_evlist__set_maps(&evlist->core, cpus, शून्य);
	runसमय_stat__init(&st);

	/* Parse the metric पूर्णांकo metric_events list. */
	err = metricgroup__parse_groups_test(evlist, &map, name,
					     false, false,
					     &metric_events);
	अगर (err)
		जाओ out;

	err = evlist__alloc_stats(evlist, false);
	अगर (err)
		जाओ out;

	/* Load the runसमय stats with given numbers क्रम events. */
	load_runसमय_stat(&st, evlist, vals);

	/* And execute the metric */
	अगर (name1 && ratio1)
		*ratio1 = compute_single(&metric_events, evlist, &st, name1);
	अगर (name2 && ratio2)
		*ratio2 = compute_single(&metric_events, evlist, &st, name2);

out:
	/* ... cleanup. */
	metricgroup__rblist_निकास(&metric_events);
	runसमय_stat__निकास(&st);
	evlist__मुक्त_stats(evlist);
	perf_cpu_map__put(cpus);
	evlist__delete(evlist);
	वापस err;
पूर्ण

अटल पूर्णांक compute_metric(स्थिर अक्षर *name, काष्ठा value *vals, द्विगुन *ratio)
अणु
	वापस __compute_metric(name, vals, name, ratio, शून्य, शून्य);
पूर्ण

अटल पूर्णांक compute_metric_group(स्थिर अक्षर *name, काष्ठा value *vals,
				स्थिर अक्षर *name1, द्विगुन *ratio1,
				स्थिर अक्षर *name2, द्विगुन *ratio2)
अणु
	वापस __compute_metric(name, vals, name1, ratio1, name2, ratio2);
पूर्ण

अटल पूर्णांक test_ipc(व्योम)
अणु
	द्विगुन ratio;
	काष्ठा value vals[] = अणु
		अणु .event = "inst_retired.any",        .val = 300 पूर्ण,
		अणु .event = "cpu_clk_unhalted.thread", .val = 200 पूर्ण,
		अणु .event = शून्य, पूर्ण,
	पूर्ण;

	TEST_ASSERT_VAL("failed to compute metric",
			compute_metric("IPC", vals, &ratio) == 0);

	TEST_ASSERT_VAL("IPC failed, wrong ratio",
			ratio == 1.5);
	वापस 0;
पूर्ण

अटल पूर्णांक test_frontend(व्योम)
अणु
	द्विगुन ratio;
	काष्ठा value vals[] = अणु
		अणु .event = "idq_uops_not_delivered.core",        .val = 300 पूर्ण,
		अणु .event = "cpu_clk_unhalted.thread",            .val = 200 पूर्ण,
		अणु .event = "cpu_clk_unhalted.one_thread_active", .val = 400 पूर्ण,
		अणु .event = "cpu_clk_unhalted.ref_xclk",          .val = 600 पूर्ण,
		अणु .event = शून्य, पूर्ण,
	पूर्ण;

	TEST_ASSERT_VAL("failed to compute metric",
			compute_metric("Frontend_Bound_SMT", vals, &ratio) == 0);

	TEST_ASSERT_VAL("Frontend_Bound_SMT failed, wrong ratio",
			ratio == 0.45);
	वापस 0;
पूर्ण

अटल पूर्णांक test_cache_miss_cycles(व्योम)
अणु
	द्विगुन ratio;
	काष्ठा value vals[] = अणु
		अणु .event = "l1d-loads-misses",  .val = 300 पूर्ण,
		अणु .event = "l1i-loads-misses",  .val = 200 पूर्ण,
		अणु .event = "inst_retired.any",  .val = 400 पूर्ण,
		अणु .event = शून्य, पूर्ण,
	पूर्ण;

	TEST_ASSERT_VAL("failed to compute metric",
			compute_metric("cache_miss_cycles", vals, &ratio) == 0);

	TEST_ASSERT_VAL("cache_miss_cycles failed, wrong ratio",
			ratio == 1.25);
	वापस 0;
पूर्ण


/*
 * DCache_L2_All_Hits = l2_rqsts.demand_data_rd_hit + l2_rqsts.pf_hit + l2_rqsts.rfo_hi
 * DCache_L2_All_Miss = max(l2_rqsts.all_demand_data_rd - l2_rqsts.demand_data_rd_hit, 0) +
 *                      l2_rqsts.pf_miss + l2_rqsts.rfo_miss
 * DCache_L2_All      = dcache_l2_all_hits + dcache_l2_all_miss
 * DCache_L2_Hits     = d_ratio(dcache_l2_all_hits, dcache_l2_all)
 * DCache_L2_Misses   = d_ratio(dcache_l2_all_miss, dcache_l2_all)
 *
 * l2_rqsts.demand_data_rd_hit = 100
 * l2_rqsts.pf_hit             = 200
 * l2_rqsts.rfo_hi             = 300
 * l2_rqsts.all_demand_data_rd = 400
 * l2_rqsts.pf_miss            = 500
 * l2_rqsts.rfo_miss           = 600
 *
 * DCache_L2_All_Hits = 600
 * DCache_L2_All_Miss = MAX(400 - 100, 0) + 500 + 600 = 1400
 * DCache_L2_All      = 600 + 1400  = 2000
 * DCache_L2_Hits     = 600 / 2000  = 0.3
 * DCache_L2_Misses   = 1400 / 2000 = 0.7
 */
अटल पूर्णांक test_dcache_l2(व्योम)
अणु
	द्विगुन ratio;
	काष्ठा value vals[] = अणु
		अणु .event = "l2_rqsts.demand_data_rd_hit", .val = 100 पूर्ण,
		अणु .event = "l2_rqsts.pf_hit",             .val = 200 पूर्ण,
		अणु .event = "l2_rqsts.rfo_hit",            .val = 300 पूर्ण,
		अणु .event = "l2_rqsts.all_demand_data_rd", .val = 400 पूर्ण,
		अणु .event = "l2_rqsts.pf_miss",            .val = 500 पूर्ण,
		अणु .event = "l2_rqsts.rfo_miss",           .val = 600 पूर्ण,
		अणु .event = शून्य, पूर्ण,
	पूर्ण;

	TEST_ASSERT_VAL("failed to compute metric",
			compute_metric("DCache_L2_Hits", vals, &ratio) == 0);

	TEST_ASSERT_VAL("DCache_L2_Hits failed, wrong ratio",
			ratio == 0.3);

	TEST_ASSERT_VAL("failed to compute metric",
			compute_metric("DCache_L2_Misses", vals, &ratio) == 0);

	TEST_ASSERT_VAL("DCache_L2_Misses failed, wrong ratio",
			ratio == 0.7);
	वापस 0;
पूर्ण

अटल पूर्णांक test_recursion_fail(व्योम)
अणु
	द्विगुन ratio;
	काष्ठा value vals[] = अणु
		अणु .event = "inst_retired.any",        .val = 300 पूर्ण,
		अणु .event = "cpu_clk_unhalted.thread", .val = 200 पूर्ण,
		अणु .event = शून्य, पूर्ण,
	पूर्ण;

	TEST_ASSERT_VAL("failed to find recursion",
			compute_metric("M1", vals, &ratio) == -1);

	TEST_ASSERT_VAL("failed to find recursion",
			compute_metric("M3", vals, &ratio) == -1);
	वापस 0;
पूर्ण

अटल पूर्णांक test_memory_bandwidth(व्योम)
अणु
	द्विगुन ratio;
	काष्ठा value vals[] = अणु
		अणु .event = "l1d.replacement", .val = 4000000 पूर्ण,
		अणु .event = "duration_time",  .val = 200000000 पूर्ण,
		अणु .event = शून्य, पूर्ण,
	पूर्ण;

	TEST_ASSERT_VAL("failed to compute metric",
			compute_metric("L1D_Cache_Fill_BW", vals, &ratio) == 0);
	TEST_ASSERT_VAL("L1D_Cache_Fill_BW, wrong ratio",
			1.28 == ratio);

	वापस 0;
पूर्ण

अटल पूर्णांक test_metric_group(व्योम)
अणु
	द्विगुन ratio1, ratio2;
	काष्ठा value vals[] = अणु
		अणु .event = "cpu_clk_unhalted.thread", .val = 200 पूर्ण,
		अणु .event = "l1d-loads-misses",        .val = 300 पूर्ण,
		अणु .event = "l1i-loads-misses",        .val = 200 पूर्ण,
		अणु .event = "inst_retired.any",        .val = 400 पूर्ण,
		अणु .event = शून्य, पूर्ण,
	पूर्ण;

	TEST_ASSERT_VAL("failed to find recursion",
			compute_metric_group("group1", vals,
					     "IPC", &ratio1,
					     "cache_miss_cycles", &ratio2) == 0);

	TEST_ASSERT_VAL("group IPC failed, wrong ratio",
			ratio1 == 2.0);

	TEST_ASSERT_VAL("group cache_miss_cycles failed, wrong ratio",
			ratio2 == 1.25);
	वापस 0;
पूर्ण

पूर्णांक test__parse_metric(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	TEST_ASSERT_VAL("IPC failed", test_ipc() == 0);
	TEST_ASSERT_VAL("frontend failed", test_frontend() == 0);
	TEST_ASSERT_VAL("DCache_L2 failed", test_dcache_l2() == 0);
	TEST_ASSERT_VAL("recursion fail failed", test_recursion_fail() == 0);
	TEST_ASSERT_VAL("Memory bandwidth", test_memory_bandwidth() == 0);

	अगर (!perf_pmu__has_hybrid()) अणु
		TEST_ASSERT_VAL("cache_miss_cycles failed", test_cache_miss_cycles() == 0);
		TEST_ASSERT_VAL("test metric group", test_metric_group() == 0);
	पूर्ण
	वापस 0;
पूर्ण
