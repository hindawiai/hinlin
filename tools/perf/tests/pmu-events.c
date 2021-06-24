<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "math.h"
#समावेश "parse-events.h"
#समावेश "pmu.h"
#समावेश "tests.h"
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/zभाग.स>
#समावेश "debug.h"
#समावेश "../pmu-events/pmu-events.h"
#समावेश "util/evlist.h"
#समावेश "util/expr.h"
#समावेश "util/parse-events.h"
#समावेश "metricgroup.h"

काष्ठा perf_pmu_test_event अणु
	/* used क्रम matching against events from generated pmu-events.c */
	काष्ठा pmu_event event;

	/* used क्रम matching against event aliases */
	/* extra events क्रम aliases */
	स्थिर अक्षर *alias_str;

	/*
	 * Note: For when PublicDescription करोes not exist in the JSON, we
	 * will have no दीर्घ_desc in pmu_event.दीर्घ_desc, but दीर्घ_desc may
	 * be set in the alias.
	 */
	स्थिर अक्षर *alias_दीर्घ_desc;
पूर्ण;

अटल काष्ठा perf_pmu_test_event test_cpu_events[] = अणु
	अणु
		.event = अणु
			.name = "bp_l1_btb_correct",
			.event = "event=0x8a",
			.desc = "L1 BTB Correction",
			.topic = "branch",
		पूर्ण,
		.alias_str = "event=0x8a",
		.alias_दीर्घ_desc = "L1 BTB Correction",
	पूर्ण,
	अणु
		.event = अणु
			.name = "bp_l2_btb_correct",
			.event = "event=0x8b",
			.desc = "L2 BTB Correction",
			.topic = "branch",
		पूर्ण,
		.alias_str = "event=0x8b",
		.alias_दीर्घ_desc = "L2 BTB Correction",
	पूर्ण,
	अणु
		.event = अणु
			.name = "segment_reg_loads.any",
			.event = "umask=0x80,period=200000,event=0x6",
			.desc = "Number of segment register loads",
			.topic = "other",
		पूर्ण,
		.alias_str = "umask=0x80,(null)=0x30d40,event=0x6",
		.alias_दीर्घ_desc = "Number of segment register loads",
	पूर्ण,
	अणु
		.event = अणु
			.name = "dispatch_blocked.any",
			.event = "umask=0x20,period=200000,event=0x9",
			.desc = "Memory cluster signals to block micro-op dispatch for any reason",
			.topic = "other",
		पूर्ण,
		.alias_str = "umask=0x20,(null)=0x30d40,event=0x9",
		.alias_दीर्घ_desc = "Memory cluster signals to block micro-op dispatch for any reason",
	पूर्ण,
	अणु
		.event = अणु
			.name = "eist_trans",
			.event = "umask=0x0,period=200000,event=0x3a",
			.desc = "Number of Enhanced Intel SpeedStep(R) Technology (EIST) transitions",
			.topic = "other",
		पूर्ण,
		.alias_str = "umask=0,(null)=0x30d40,event=0x3a",
		.alias_दीर्घ_desc = "Number of Enhanced Intel SpeedStep(R) Technology (EIST) transitions",
	पूर्ण,
	अणु
		.event = अणु
			.name = "l3_cache_rd",
			.event = "event=0x40",
			.desc = "L3 cache access, read",
			.दीर्घ_desc = "Attributable Level 3 cache access, read",
			.topic = "cache",
		पूर्ण,
		.alias_str = "event=0x40",
		.alias_दीर्घ_desc = "Attributable Level 3 cache access, read",
	पूर्ण,
	अणु /* sentinel */
		.event = अणु
			.name = शून्य,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा perf_pmu_test_event test_uncore_events[] = अणु
	अणु
		.event = अणु
			.name = "uncore_hisi_ddrc.flux_wcmd",
			.event = "event=0x2",
			.desc = "DDRC write commands. Unit: hisi_sccl,ddrc ",
			.topic = "uncore",
			.दीर्घ_desc = "DDRC write commands",
			.pmu = "hisi_sccl,ddrc",
		पूर्ण,
		.alias_str = "event=0x2",
		.alias_दीर्घ_desc = "DDRC write commands",
	पूर्ण,
	अणु
		.event = अणु
			.name = "unc_cbo_xsnp_response.miss_eviction",
			.event = "umask=0x81,event=0x22",
			.desc = "Unit: uncore_cbox A cross-core snoop resulted from L3 Eviction which misses in some processor core",
			.topic = "uncore",
			.दीर्घ_desc = "A cross-core snoop resulted from L3 Eviction which misses in some processor core",
			.pmu = "uncore_cbox",
		पूर्ण,
		.alias_str = "umask=0x81,event=0x22",
		.alias_दीर्घ_desc = "A cross-core snoop resulted from L3 Eviction which misses in some processor core",
	पूर्ण,
	अणु /* sentinel */
		.event = अणु
			.name = शून्य,
		पूर्ण,
	पूर्ण
पूर्ण;

स्थिर पूर्णांक total_test_events_size = ARRAY_SIZE(test_uncore_events);

अटल bool is_same(स्थिर अक्षर *reference, स्थिर अक्षर *test)
अणु
	अगर (!reference && !test)
		वापस true;

	अगर (reference && !test)
		वापस false;

	अगर (!reference && test)
		वापस false;

	वापस !म_भेद(reference, test);
पूर्ण

अटल काष्ठा pmu_events_map *__test_pmu_get_events_map(व्योम)
अणु
	काष्ठा pmu_events_map *map;

	क्रम (map = &pmu_events_map[0]; map->cpuid; map++) अणु
		अगर (!म_भेद(map->cpuid, "testcpu"))
			वापस map;
	पूर्ण

	pr_err("could not find test events map\n");

	वापस शून्य;
पूर्ण

/* Verअगरy generated events from pmu-events.c is as expected */
अटल पूर्णांक test_pmu_event_table(व्योम)
अणु
	काष्ठा pmu_events_map *map = __test_pmu_get_events_map();
	काष्ठा pmu_event *table;
	पूर्णांक map_events = 0, expected_events;

	/* ignore 2x sentinels */
	expected_events = ARRAY_SIZE(test_cpu_events) +
			  ARRAY_SIZE(test_uncore_events) - 2;

	अगर (!map)
		वापस -1;

	क्रम (table = map->table; table->name; table++) अणु
		काष्ठा perf_pmu_test_event *test;
		काष्ठा pmu_event *te;
		bool found = false;

		अगर (table->pmu)
			test = &test_uncore_events[0];
		अन्यथा
			test = &test_cpu_events[0];

		te = &test->event;

		क्रम (; te->name; test++, te = &test->event) अणु
			अगर (म_भेद(table->name, te->name))
				जारी;
			found = true;
			map_events++;

			अगर (!is_same(table->desc, te->desc)) अणु
				pr_debug2("testing event table %s: mismatched desc, %s vs %s\n",
					  table->name, table->desc, te->desc);
				वापस -1;
			पूर्ण

			अगर (!is_same(table->topic, te->topic)) अणु
				pr_debug2("testing event table %s: mismatched topic, %s vs %s\n",
					  table->name, table->topic,
					  te->topic);
				वापस -1;
			पूर्ण

			अगर (!is_same(table->दीर्घ_desc, te->दीर्घ_desc)) अणु
				pr_debug2("testing event table %s: mismatched long_desc, %s vs %s\n",
					  table->name, table->दीर्घ_desc,
					  te->दीर्घ_desc);
				वापस -1;
			पूर्ण

			अगर (!is_same(table->unit, te->unit)) अणु
				pr_debug2("testing event table %s: mismatched unit, %s vs %s\n",
					  table->name, table->unit,
					  te->unit);
				वापस -1;
			पूर्ण

			अगर (!is_same(table->perpkg, te->perpkg)) अणु
				pr_debug2("testing event table %s: mismatched perpkg, %s vs %s\n",
					  table->name, table->perpkg,
					  te->perpkg);
				वापस -1;
			पूर्ण

			अगर (!is_same(table->metric_expr, te->metric_expr)) अणु
				pr_debug2("testing event table %s: mismatched metric_expr, %s vs %s\n",
					  table->name, table->metric_expr,
					  te->metric_expr);
				वापस -1;
			पूर्ण

			अगर (!is_same(table->metric_name, te->metric_name)) अणु
				pr_debug2("testing event table %s: mismatched metric_name, %s vs %s\n",
					  table->name,  table->metric_name,
					  te->metric_name);
				वापस -1;
			पूर्ण

			अगर (!is_same(table->deprecated, te->deprecated)) अणु
				pr_debug2("testing event table %s: mismatched deprecated, %s vs %s\n",
					  table->name, table->deprecated,
					  te->deprecated);
				वापस -1;
			पूर्ण

			pr_debug("testing event table %s: pass\n", table->name);
		पूर्ण

		अगर (!found) अणु
			pr_err("testing event table: could not find event %s\n",
			       table->name);
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (map_events != expected_events) अणु
		pr_err("testing event table: found %d, but expected %d\n",
		       map_events, expected_events);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा perf_pmu_alias *find_alias(स्थिर अक्षर *test_event, काष्ठा list_head *aliases)
अणु
	काष्ठा perf_pmu_alias *alias;

	list_क्रम_each_entry(alias, aliases, list)
		अगर (!म_भेद(test_event, alias->name))
			वापस alias;

	वापस शून्य;
पूर्ण

/* Verअगरy aliases are as expected */
अटल पूर्णांक __test__pmu_event_aliases(अक्षर *pmu_name, पूर्णांक *count)
अणु
	काष्ठा perf_pmu_test_event *test;
	काष्ठा pmu_event *te;
	काष्ठा perf_pmu *pmu;
	LIST_HEAD(aliases);
	पूर्णांक res = 0;
	bool use_uncore_table;
	काष्ठा pmu_events_map *map = __test_pmu_get_events_map();
	काष्ठा perf_pmu_alias *a, *पंचांगp;

	अगर (!map)
		वापस -1;

	अगर (is_pmu_core(pmu_name)) अणु
		test = &test_cpu_events[0];
		use_uncore_table = false;
	पूर्ण अन्यथा अणु
		test = &test_uncore_events[0];
		use_uncore_table = true;
	पूर्ण

	pmu = zalloc(माप(*pmu));
	अगर (!pmu)
		वापस -1;

	pmu->name = pmu_name;

	pmu_add_cpu_aliases_map(&aliases, pmu, map);

	क्रम (te = &test->event; te->name; test++, te = &test->event) अणु
		काष्ठा perf_pmu_alias *alias = find_alias(te->name, &aliases);

		अगर (!alias) अणु
			bool uncore_match = pmu_uncore_alias_match(pmu_name,
								   te->pmu);

			अगर (use_uncore_table && !uncore_match) अणु
				pr_debug3("testing aliases PMU %s: skip matching alias %s\n",
					  pmu_name, te->name);
				जारी;
			पूर्ण

			pr_debug2("testing aliases PMU %s: no alias, alias_table->name=%s\n",
				  pmu_name, te->name);
			res = -1;
			अवरोध;
		पूर्ण

		अगर (!is_same(alias->desc, te->desc)) अणु
			pr_debug2("testing aliases PMU %s: mismatched desc, %s vs %s\n",
				  pmu_name, alias->desc, te->desc);
			res = -1;
			अवरोध;
		पूर्ण

		अगर (!is_same(alias->दीर्घ_desc, test->alias_दीर्घ_desc)) अणु
			pr_debug2("testing aliases PMU %s: mismatched long_desc, %s vs %s\n",
				  pmu_name, alias->दीर्घ_desc,
				  test->alias_दीर्घ_desc);
			res = -1;
			अवरोध;
		पूर्ण

		अगर (!is_same(alias->str, test->alias_str)) अणु
			pr_debug2("testing aliases PMU %s: mismatched str, %s vs %s\n",
				  pmu_name, alias->str, test->alias_str);
			res = -1;
			अवरोध;
		पूर्ण

		अगर (!is_same(alias->topic, te->topic)) अणु
			pr_debug2("testing aliases PMU %s: mismatched topic, %s vs %s\n",
				  pmu_name, alias->topic, te->topic);
			res = -1;
			अवरोध;
		पूर्ण

		(*count)++;
		pr_debug2("testing aliases PMU %s: matched event %s\n",
			  pmu_name, alias->name);
	पूर्ण

	list_क्रम_each_entry_safe(a, पंचांगp, &aliases, list) अणु
		list_del(&a->list);
		perf_pmu_मुक्त_alias(a);
	पूर्ण
	मुक्त(pmu);
	वापस res;
पूर्ण


/* Test that aliases generated are as expected */
अटल पूर्णांक test_aliases(व्योम)
अणु
	काष्ठा perf_pmu *pmu = शून्य;

	जबतक ((pmu = perf_pmu__scan(pmu)) != शून्य) अणु
		पूर्णांक count = 0;

		अगर (list_empty(&pmu->क्रमmat)) अणु
			pr_debug2("skipping testing PMU %s\n", pmu->name);
			जारी;
		पूर्ण

		अगर (__test__pmu_event_aliases(pmu->name, &count)) अणु
			pr_debug("testing PMU %s aliases: failed\n", pmu->name);
			वापस -1;
		पूर्ण

		अगर (count == 0)
			pr_debug3("testing PMU %s aliases: no events to match\n",
				  pmu->name);
		अन्यथा
			pr_debug("testing PMU %s aliases: pass\n", pmu->name);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool is_number(स्थिर अक्षर *str)
अणु
	अक्षर *end_ptr;
	द्विगुन v;

	त्रुटि_सं = 0;
	v = म_से_भग्न(str, &end_ptr);
	(व्योम)v; // We're not पूर्णांकerested in this value, only अगर it is valid
	वापस त्रुटि_सं == 0 && end_ptr != str;
पूर्ण

अटल पूर्णांक check_parse_id(स्थिर अक्षर *id, काष्ठा parse_events_error *error,
			  काष्ठा perf_pmu *fake_pmu)
अणु
	काष्ठा evlist *evlist;
	पूर्णांक ret;

	/* Numbers are always valid. */
	अगर (is_number(id))
		वापस 0;

	evlist = evlist__new();
	अगर (!evlist)
		वापस -ENOMEM;
	ret = __parse_events(evlist, id, error, fake_pmu);
	evlist__delete(evlist);
	वापस ret;
पूर्ण

अटल पूर्णांक check_parse_cpu(स्थिर अक्षर *id, bool same_cpu, काष्ठा pmu_event *pe)
अणु
	काष्ठा parse_events_error error = अणु .idx = 0, पूर्ण;

	पूर्णांक ret = check_parse_id(id, &error, शून्य);
	अगर (ret && same_cpu) अणु
		pr_warning("Parse event failed metric '%s' id '%s' expr '%s'\n",
			pe->metric_name, id, pe->metric_expr);
		pr_warning("Error string '%s' help '%s'\n", error.str,
			error.help);
	पूर्ण अन्यथा अगर (ret) अणु
		pr_debug3("Parse event failed, but for an event that may not be supported by this CPU.\nid '%s' metric '%s' expr '%s'\n",
			  id, pe->metric_name, pe->metric_expr);
		ret = 0;
	पूर्ण
	मुक्त(error.str);
	मुक्त(error.help);
	मुक्त(error.first_str);
	मुक्त(error.first_help);
	वापस ret;
पूर्ण

अटल पूर्णांक check_parse_fake(स्थिर अक्षर *id)
अणु
	काष्ठा parse_events_error error = अणु .idx = 0, पूर्ण;
	पूर्णांक ret = check_parse_id(id, &error, &perf_pmu__fake);

	मुक्त(error.str);
	मुक्त(error.help);
	मुक्त(error.first_str);
	मुक्त(error.first_help);
	वापस ret;
पूर्ण

अटल व्योम expr_failure(स्थिर अक्षर *msg,
			 स्थिर काष्ठा pmu_events_map *map,
			 स्थिर काष्ठा pmu_event *pe)
अणु
	pr_debug("%s for map %s %s %s\n",
		msg, map->cpuid, map->version, map->type);
	pr_debug("On metric %s\n", pe->metric_name);
	pr_debug("On expression %s\n", pe->metric_expr);
पूर्ण

काष्ठा metric अणु
	काष्ठा list_head list;
	काष्ठा metric_ref metric_ref;
पूर्ण;

अटल पूर्णांक resolve_metric_simple(काष्ठा expr_parse_ctx *pctx,
				 काष्ठा list_head *compound_list,
				 काष्ठा pmu_events_map *map,
				 स्थिर अक्षर *metric_name)
अणु
	काष्ठा hashmap_entry *cur, *cur_पंचांगp;
	काष्ठा metric *metric, *पंचांगp;
	माप_प्रकार bkt;
	bool all;
	पूर्णांक rc;

	करो अणु
		all = true;
		hashmap__क्रम_each_entry_safe((&pctx->ids), cur, cur_पंचांगp, bkt) अणु
			काष्ठा metric_ref *ref;
			काष्ठा pmu_event *pe;

			pe = metricgroup__find_metric(cur->key, map);
			अगर (!pe)
				जारी;

			अगर (!म_भेद(metric_name, (अक्षर *)cur->key)) अणु
				pr_warning("Recursion detected for metric %s\n", metric_name);
				rc = -1;
				जाओ out_err;
			पूर्ण

			all = false;

			/* The metric key itself needs to go out.. */
			expr__del_id(pctx, cur->key);

			metric = दो_स्मृति(माप(*metric));
			अगर (!metric) अणु
				rc = -ENOMEM;
				जाओ out_err;
			पूर्ण

			ref = &metric->metric_ref;
			ref->metric_name = pe->metric_name;
			ref->metric_expr = pe->metric_expr;
			list_add_tail(&metric->list, compound_list);

			rc = expr__find_other(pe->metric_expr, शून्य, pctx, 0);
			अगर (rc)
				जाओ out_err;
			अवरोध; /* The hashmap has been modअगरied, so restart */
		पूर्ण
	पूर्ण जबतक (!all);

	वापस 0;

out_err:
	list_क्रम_each_entry_safe(metric, पंचांगp, compound_list, list)
		मुक्त(metric);

	वापस rc;

पूर्ण

अटल पूर्णांक test_parsing(व्योम)
अणु
	काष्ठा pmu_events_map *cpus_map = pmu_events_map__find();
	काष्ठा pmu_events_map *map;
	काष्ठा pmu_event *pe;
	पूर्णांक i, j, k;
	पूर्णांक ret = 0;
	काष्ठा expr_parse_ctx ctx;
	द्विगुन result;

	i = 0;
	क्रम (;;) अणु
		map = &pmu_events_map[i++];
		अगर (!map->table)
			अवरोध;
		j = 0;
		क्रम (;;) अणु
			काष्ठा metric *metric, *पंचांगp;
			काष्ठा hashmap_entry *cur;
			LIST_HEAD(compound_list);
			माप_प्रकार bkt;

			pe = &map->table[j++];
			अगर (!pe->name && !pe->metric_group && !pe->metric_name)
				अवरोध;
			अगर (!pe->metric_expr)
				जारी;
			expr__ctx_init(&ctx);
			अगर (expr__find_other(pe->metric_expr, शून्य, &ctx, 0)
				  < 0) अणु
				expr_failure("Parse other failed", map, pe);
				ret++;
				जारी;
			पूर्ण

			अगर (resolve_metric_simple(&ctx, &compound_list, map,
						  pe->metric_name)) अणु
				expr_failure("Could not resolve metrics", map, pe);
				ret++;
				जाओ निकास; /* Don't tolerate errors due to severity */
			पूर्ण

			/*
			 * Add all ids with a made up value. The value may
			 * trigger भागide by zero when subtracted and so try to
			 * make them unique.
			 */
			k = 1;
			hashmap__क्रम_each_entry((&ctx.ids), cur, bkt)
				expr__add_id_val(&ctx, strdup(cur->key), k++);

			hashmap__क्रम_each_entry((&ctx.ids), cur, bkt) अणु
				अगर (check_parse_cpu(cur->key, map == cpus_map,
						   pe))
					ret++;
			पूर्ण

			list_क्रम_each_entry_safe(metric, पंचांगp, &compound_list, list) अणु
				expr__add_ref(&ctx, &metric->metric_ref);
				मुक्त(metric);
			पूर्ण

			अगर (expr__parse(&result, &ctx, pe->metric_expr, 0)) अणु
				expr_failure("Parse failed", map, pe);
				ret++;
			पूर्ण
			expr__ctx_clear(&ctx);
		पूर्ण
	पूर्ण
	/* TODO: fail when not ok */
निकास:
	वापस ret == 0 ? TEST_OK : TEST_SKIP;
पूर्ण

काष्ठा test_metric अणु
	स्थिर अक्षर *str;
पूर्ण;

अटल काष्ठा test_metric metrics[] = अणु
	अणु "(unc_p_power_state_occupancy.cores_c0 / unc_p_clockticks) * 100." पूर्ण,
	अणु "imx8_ddr0@read\\-cycles@ * 4 * 4", पूर्ण,
	अणु "imx8_ddr0@axid\\-read\\,axi_mask\\=0xffff\\,axi_id\\=0x0000@ * 4", पूर्ण,
	अणु "(cstate_pkg@c2\\-residency@ / msr@tsc@) * 100", पूर्ण,
	अणु "(imx8_ddr0@read\\-cycles@ + imx8_ddr0@write\\-cycles@)", पूर्ण,
पूर्ण;

अटल पूर्णांक metric_parse_fake(स्थिर अक्षर *str)
अणु
	काष्ठा expr_parse_ctx ctx;
	काष्ठा hashmap_entry *cur;
	द्विगुन result;
	पूर्णांक ret = -1;
	माप_प्रकार bkt;
	पूर्णांक i;

	pr_debug("parsing '%s'\n", str);

	expr__ctx_init(&ctx);
	अगर (expr__find_other(str, शून्य, &ctx, 0) < 0) अणु
		pr_err("expr__find_other failed\n");
		वापस -1;
	पूर्ण

	/*
	 * Add all ids with a made up value. The value may
	 * trigger भागide by zero when subtracted and so try to
	 * make them unique.
	 */
	i = 1;
	hashmap__क्रम_each_entry((&ctx.ids), cur, bkt)
		expr__add_id_val(&ctx, strdup(cur->key), i++);

	hashmap__क्रम_each_entry((&ctx.ids), cur, bkt) अणु
		अगर (check_parse_fake(cur->key)) अणु
			pr_err("check_parse_fake failed\n");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (expr__parse(&result, &ctx, str, 0))
		pr_err("expr__parse failed\n");
	अन्यथा
		ret = 0;

out:
	expr__ctx_clear(&ctx);
	वापस ret;
पूर्ण

/*
 * Parse all the metrics क्रम current architecture,
 * or all defined cpus via the 'fake_pmu'
 * in parse_events.
 */
अटल पूर्णांक test_parsing_fake(व्योम)
अणु
	काष्ठा pmu_events_map *map;
	काष्ठा pmu_event *pe;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक err = 0;

	क्रम (i = 0; i < ARRAY_SIZE(metrics); i++) अणु
		err = metric_parse_fake(metrics[i].str);
		अगर (err)
			वापस err;
	पूर्ण

	i = 0;
	क्रम (;;) अणु
		map = &pmu_events_map[i++];
		अगर (!map->table)
			अवरोध;
		j = 0;
		क्रम (;;) अणु
			pe = &map->table[j++];
			अगर (!pe->name && !pe->metric_group && !pe->metric_name)
				अवरोध;
			अगर (!pe->metric_expr)
				जारी;
			err = metric_parse_fake(pe->metric_expr);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा अणु
	पूर्णांक (*func)(व्योम);
	स्थिर अक्षर *desc;
पूर्ण pmu_events_testहाल_table[] = अणु
	अणु
		.func = test_pmu_event_table,
		.desc = "PMU event table sanity",
	पूर्ण,
	अणु
		.func = test_aliases,
		.desc = "PMU event map aliases",
	पूर्ण,
	अणु
		.func = test_parsing,
		.desc = "Parsing of PMU event table metrics",
	पूर्ण,
	अणु
		.func = test_parsing_fake,
		.desc = "Parsing of PMU event table metrics with fake PMUs",
	पूर्ण,
पूर्ण;

स्थिर अक्षर *test__pmu_events_subtest_get_desc(पूर्णांक subtest)
अणु
	अगर (subtest < 0 ||
	    subtest >= (पूर्णांक)ARRAY_SIZE(pmu_events_testहाल_table))
		वापस शून्य;
	वापस pmu_events_testहाल_table[subtest].desc;
पूर्ण

स्थिर अक्षर *test__pmu_events_subtest_skip_reason(पूर्णांक subtest)
अणु
	अगर (subtest < 0 ||
	    subtest >= (पूर्णांक)ARRAY_SIZE(pmu_events_testहाल_table))
		वापस शून्य;
	अगर (pmu_events_testहाल_table[subtest].func != test_parsing)
		वापस शून्य;
	वापस "some metrics failed";
पूर्ण

पूर्णांक test__pmu_events_subtest_get_nr(व्योम)
अणु
	वापस (पूर्णांक)ARRAY_SIZE(pmu_events_testहाल_table);
पूर्ण

पूर्णांक test__pmu_events(काष्ठा test *test __maybe_unused, पूर्णांक subtest)
अणु
	अगर (subtest < 0 ||
	    subtest >= (पूर्णांक)ARRAY_SIZE(pmu_events_testहाल_table))
		वापस TEST_FAIL;
	वापस pmu_events_testहाल_table[subtest].func();
पूर्ण
