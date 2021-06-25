<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश "evsel.h"
#समावेश "stat.h"
#समावेश "color.h"
#समावेश "pmu.h"
#समावेश "rblist.h"
#समावेश "evlist.h"
#समावेश "expr.h"
#समावेश "metricgroup.h"
#समावेश "cgroup.h"
#समावेश "units.h"
#समावेश <linux/zभाग.स>
#समावेश "iostat.h"

/*
 * AGGR_GLOBAL: Use CPU 0
 * AGGR_SOCKET: Use first CPU of socket
 * AGGR_DIE: Use first CPU of die
 * AGGR_CORE: Use first CPU of core
 * AGGR_NONE: Use matching CPU
 * AGGR_THREAD: Not supported?
 */

काष्ठा runसमय_stat rt_stat;
काष्ठा stats wallसमय_nsecs_stats;

काष्ठा saved_value अणु
	काष्ठा rb_node rb_node;
	काष्ठा evsel *evsel;
	क्रमागत stat_type type;
	पूर्णांक ctx;
	पूर्णांक cpu;
	काष्ठा cgroup *cgrp;
	काष्ठा runसमय_stat *stat;
	काष्ठा stats stats;
	u64 metric_total;
	पूर्णांक metric_other;
पूर्ण;

अटल पूर्णांक saved_value_cmp(काष्ठा rb_node *rb_node, स्थिर व्योम *entry)
अणु
	काष्ठा saved_value *a = container_of(rb_node,
					     काष्ठा saved_value,
					     rb_node);
	स्थिर काष्ठा saved_value *b = entry;

	अगर (a->cpu != b->cpu)
		वापस a->cpu - b->cpu;

	/*
	 * Previously the rbtree was used to link generic metrics.
	 * The keys were evsel/cpu. Now the rbtree is extended to support
	 * per-thपढ़ो shaकरोw stats. For shaकरोw stats हाल, the keys
	 * are cpu/type/ctx/stat (evsel is शून्य). For generic metrics
	 * हाल, the keys are still evsel/cpu (type/ctx/stat are 0 or शून्य).
	 */
	अगर (a->type != b->type)
		वापस a->type - b->type;

	अगर (a->ctx != b->ctx)
		वापस a->ctx - b->ctx;

	अगर (a->cgrp != b->cgrp)
		वापस (अक्षर *)a->cgrp < (अक्षर *)b->cgrp ? -1 : +1;

	अगर (a->evsel == शून्य && b->evsel == शून्य) अणु
		अगर (a->stat == b->stat)
			वापस 0;

		अगर ((अक्षर *)a->stat < (अक्षर *)b->stat)
			वापस -1;

		वापस 1;
	पूर्ण

	अगर (a->evsel == b->evsel)
		वापस 0;
	अगर ((अक्षर *)a->evsel < (अक्षर *)b->evsel)
		वापस -1;
	वापस +1;
पूर्ण

अटल काष्ठा rb_node *saved_value_new(काष्ठा rblist *rblist __maybe_unused,
				     स्थिर व्योम *entry)
अणु
	काष्ठा saved_value *nd = दो_स्मृति(माप(काष्ठा saved_value));

	अगर (!nd)
		वापस शून्य;
	स_नकल(nd, entry, माप(काष्ठा saved_value));
	वापस &nd->rb_node;
पूर्ण

अटल व्योम saved_value_delete(काष्ठा rblist *rblist __maybe_unused,
			       काष्ठा rb_node *rb_node)
अणु
	काष्ठा saved_value *v;

	BUG_ON(!rb_node);
	v = container_of(rb_node, काष्ठा saved_value, rb_node);
	मुक्त(v);
पूर्ण

अटल काष्ठा saved_value *saved_value_lookup(काष्ठा evsel *evsel,
					      पूर्णांक cpu,
					      bool create,
					      क्रमागत stat_type type,
					      पूर्णांक ctx,
					      काष्ठा runसमय_stat *st,
					      काष्ठा cgroup *cgrp)
अणु
	काष्ठा rblist *rblist;
	काष्ठा rb_node *nd;
	काष्ठा saved_value dm = अणु
		.cpu = cpu,
		.evsel = evsel,
		.type = type,
		.ctx = ctx,
		.stat = st,
		.cgrp = cgrp,
	पूर्ण;

	rblist = &st->value_list;

	/* करोn't use context info क्रम घड़ी events */
	अगर (type == STAT_NSECS)
		dm.ctx = 0;

	nd = rblist__find(rblist, &dm);
	अगर (nd)
		वापस container_of(nd, काष्ठा saved_value, rb_node);
	अगर (create) अणु
		rblist__add_node(rblist, &dm);
		nd = rblist__find(rblist, &dm);
		अगर (nd)
			वापस container_of(nd, काष्ठा saved_value, rb_node);
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम runसमय_stat__init(काष्ठा runसमय_stat *st)
अणु
	काष्ठा rblist *rblist = &st->value_list;

	rblist__init(rblist);
	rblist->node_cmp = saved_value_cmp;
	rblist->node_new = saved_value_new;
	rblist->node_delete = saved_value_delete;
पूर्ण

व्योम runसमय_stat__निकास(काष्ठा runसमय_stat *st)
अणु
	rblist__निकास(&st->value_list);
पूर्ण

व्योम perf_stat__init_shaकरोw_stats(व्योम)
अणु
	runसमय_stat__init(&rt_stat);
पूर्ण

अटल पूर्णांक evsel_context(काष्ठा evsel *evsel)
अणु
	पूर्णांक ctx = 0;

	अगर (evsel->core.attr.exclude_kernel)
		ctx |= CTX_BIT_KERNEL;
	अगर (evsel->core.attr.exclude_user)
		ctx |= CTX_BIT_USER;
	अगर (evsel->core.attr.exclude_hv)
		ctx |= CTX_BIT_HV;
	अगर (evsel->core.attr.exclude_host)
		ctx |= CTX_BIT_HOST;
	अगर (evsel->core.attr.exclude_idle)
		ctx |= CTX_BIT_IDLE;

	वापस ctx;
पूर्ण

अटल व्योम reset_stat(काष्ठा runसमय_stat *st)
अणु
	काष्ठा rblist *rblist;
	काष्ठा rb_node *pos, *next;

	rblist = &st->value_list;
	next = rb_first_cached(&rblist->entries);
	जबतक (next) अणु
		pos = next;
		next = rb_next(pos);
		स_रखो(&container_of(pos, काष्ठा saved_value, rb_node)->stats,
		       0,
		       माप(काष्ठा stats));
	पूर्ण
पूर्ण

व्योम perf_stat__reset_shaकरोw_stats(व्योम)
अणु
	reset_stat(&rt_stat);
	स_रखो(&wallसमय_nsecs_stats, 0, माप(wallसमय_nsecs_stats));
पूर्ण

व्योम perf_stat__reset_shaकरोw_per_stat(काष्ठा runसमय_stat *st)
अणु
	reset_stat(st);
पूर्ण

काष्ठा runसमय_stat_data अणु
	पूर्णांक ctx;
	काष्ठा cgroup *cgrp;
पूर्ण;

अटल व्योम update_runसमय_stat(काष्ठा runसमय_stat *st,
				क्रमागत stat_type type,
				पूर्णांक cpu, u64 count,
				काष्ठा runसमय_stat_data *rsd)
अणु
	काष्ठा saved_value *v = saved_value_lookup(शून्य, cpu, true, type,
						   rsd->ctx, st, rsd->cgrp);

	अगर (v)
		update_stats(&v->stats, count);
पूर्ण

/*
 * Update various tracking values we मुख्यtain to prपूर्णांक
 * more semantic inक्रमmation such as miss/hit ratios,
 * inकाष्ठाion rates, etc:
 */
व्योम perf_stat__update_shaकरोw_stats(काष्ठा evsel *counter, u64 count,
				    पूर्णांक cpu, काष्ठा runसमय_stat *st)
अणु
	u64 count_ns = count;
	काष्ठा saved_value *v;
	काष्ठा runसमय_stat_data rsd = अणु
		.ctx = evsel_context(counter),
		.cgrp = counter->cgrp,
	पूर्ण;

	count *= counter->scale;

	अगर (evsel__is_घड़ी(counter))
		update_runसमय_stat(st, STAT_NSECS, cpu, count_ns, &rsd);
	अन्यथा अगर (evsel__match(counter, HARDWARE, HW_CPU_CYCLES))
		update_runसमय_stat(st, STAT_CYCLES, cpu, count, &rsd);
	अन्यथा अगर (perf_stat_evsel__is(counter, CYCLES_IN_TX))
		update_runसमय_stat(st, STAT_CYCLES_IN_TX, cpu, count, &rsd);
	अन्यथा अगर (perf_stat_evsel__is(counter, TRANSACTION_START))
		update_runसमय_stat(st, STAT_TRANSACTION, cpu, count, &rsd);
	अन्यथा अगर (perf_stat_evsel__is(counter, ELISION_START))
		update_runसमय_stat(st, STAT_ELISION, cpu, count, &rsd);
	अन्यथा अगर (perf_stat_evsel__is(counter, TOPDOWN_TOTAL_SLOTS))
		update_runसमय_stat(st, STAT_TOPDOWN_TOTAL_SLOTS,
				    cpu, count, &rsd);
	अन्यथा अगर (perf_stat_evsel__is(counter, TOPDOWN_SLOTS_ISSUED))
		update_runसमय_stat(st, STAT_TOPDOWN_SLOTS_ISSUED,
				    cpu, count, &rsd);
	अन्यथा अगर (perf_stat_evsel__is(counter, TOPDOWN_SLOTS_RETIRED))
		update_runसमय_stat(st, STAT_TOPDOWN_SLOTS_RETIRED,
				    cpu, count, &rsd);
	अन्यथा अगर (perf_stat_evsel__is(counter, TOPDOWN_FETCH_BUBBLES))
		update_runसमय_stat(st, STAT_TOPDOWN_FETCH_BUBBLES,
				    cpu, count, &rsd);
	अन्यथा अगर (perf_stat_evsel__is(counter, TOPDOWN_RECOVERY_BUBBLES))
		update_runसमय_stat(st, STAT_TOPDOWN_RECOVERY_BUBBLES,
				    cpu, count, &rsd);
	अन्यथा अगर (perf_stat_evsel__is(counter, TOPDOWN_RETIRING))
		update_runसमय_stat(st, STAT_TOPDOWN_RETIRING,
				    cpu, count, &rsd);
	अन्यथा अगर (perf_stat_evsel__is(counter, TOPDOWN_BAD_SPEC))
		update_runसमय_stat(st, STAT_TOPDOWN_BAD_SPEC,
				    cpu, count, &rsd);
	अन्यथा अगर (perf_stat_evsel__is(counter, TOPDOWN_FE_BOUND))
		update_runसमय_stat(st, STAT_TOPDOWN_FE_BOUND,
				    cpu, count, &rsd);
	अन्यथा अगर (perf_stat_evsel__is(counter, TOPDOWN_BE_BOUND))
		update_runसमय_stat(st, STAT_TOPDOWN_BE_BOUND,
				    cpu, count, &rsd);
	अन्यथा अगर (perf_stat_evsel__is(counter, TOPDOWN_HEAVY_OPS))
		update_runसमय_stat(st, STAT_TOPDOWN_HEAVY_OPS,
				    cpu, count, &rsd);
	अन्यथा अगर (perf_stat_evsel__is(counter, TOPDOWN_BR_MISPREDICT))
		update_runसमय_stat(st, STAT_TOPDOWN_BR_MISPREDICT,
				    cpu, count, &rsd);
	अन्यथा अगर (perf_stat_evsel__is(counter, TOPDOWN_FETCH_LAT))
		update_runसमय_stat(st, STAT_TOPDOWN_FETCH_LAT,
				    cpu, count, &rsd);
	अन्यथा अगर (perf_stat_evsel__is(counter, TOPDOWN_MEM_BOUND))
		update_runसमय_stat(st, STAT_TOPDOWN_MEM_BOUND,
				    cpu, count, &rsd);
	अन्यथा अगर (evsel__match(counter, HARDWARE, HW_STALLED_CYCLES_FRONTEND))
		update_runसमय_stat(st, STAT_STALLED_CYCLES_FRONT,
				    cpu, count, &rsd);
	अन्यथा अगर (evsel__match(counter, HARDWARE, HW_STALLED_CYCLES_BACKEND))
		update_runसमय_stat(st, STAT_STALLED_CYCLES_BACK,
				    cpu, count, &rsd);
	अन्यथा अगर (evsel__match(counter, HARDWARE, HW_BRANCH_INSTRUCTIONS))
		update_runसमय_stat(st, STAT_BRANCHES, cpu, count, &rsd);
	अन्यथा अगर (evsel__match(counter, HARDWARE, HW_CACHE_REFERENCES))
		update_runसमय_stat(st, STAT_CACHEREFS, cpu, count, &rsd);
	अन्यथा अगर (evsel__match(counter, HW_CACHE, HW_CACHE_L1D))
		update_runसमय_stat(st, STAT_L1_DCACHE, cpu, count, &rsd);
	अन्यथा अगर (evsel__match(counter, HW_CACHE, HW_CACHE_L1I))
		update_runसमय_stat(st, STAT_L1_ICACHE, cpu, count, &rsd);
	अन्यथा अगर (evsel__match(counter, HW_CACHE, HW_CACHE_LL))
		update_runसमय_stat(st, STAT_LL_CACHE, cpu, count, &rsd);
	अन्यथा अगर (evsel__match(counter, HW_CACHE, HW_CACHE_DTLB))
		update_runसमय_stat(st, STAT_DTLB_CACHE, cpu, count, &rsd);
	अन्यथा अगर (evsel__match(counter, HW_CACHE, HW_CACHE_ITLB))
		update_runसमय_stat(st, STAT_ITLB_CACHE, cpu, count, &rsd);
	अन्यथा अगर (perf_stat_evsel__is(counter, SMI_NUM))
		update_runसमय_stat(st, STAT_SMI_NUM, cpu, count, &rsd);
	अन्यथा अगर (perf_stat_evsel__is(counter, APERF))
		update_runसमय_stat(st, STAT_APERF, cpu, count, &rsd);

	अगर (counter->collect_stat) अणु
		v = saved_value_lookup(counter, cpu, true, STAT_NONE, 0, st,
				       rsd.cgrp);
		update_stats(&v->stats, count);
		अगर (counter->metric_leader)
			v->metric_total += count;
	पूर्ण अन्यथा अगर (counter->metric_leader) अणु
		v = saved_value_lookup(counter->metric_leader,
				       cpu, true, STAT_NONE, 0, st, rsd.cgrp);
		v->metric_total += count;
		v->metric_other++;
	पूर्ण
पूर्ण

/* used क्रम get_ratio_color() */
क्रमागत grc_type अणु
	GRC_STALLED_CYCLES_FE,
	GRC_STALLED_CYCLES_BE,
	GRC_CACHE_MISSES,
	GRC_MAX_NR
पूर्ण;

अटल स्थिर अक्षर *get_ratio_color(क्रमागत grc_type type, द्विगुन ratio)
अणु
	अटल स्थिर द्विगुन grc_table[GRC_MAX_NR][3] = अणु
		[GRC_STALLED_CYCLES_FE] = अणु 50.0, 30.0, 10.0 पूर्ण,
		[GRC_STALLED_CYCLES_BE] = अणु 75.0, 50.0, 20.0 पूर्ण,
		[GRC_CACHE_MISSES] 	= अणु 20.0, 10.0, 5.0 पूर्ण,
	पूर्ण;
	स्थिर अक्षर *color = PERF_COLOR_NORMAL;

	अगर (ratio > grc_table[type][0])
		color = PERF_COLOR_RED;
	अन्यथा अगर (ratio > grc_table[type][1])
		color = PERF_COLOR_MAGENTA;
	अन्यथा अगर (ratio > grc_table[type][2])
		color = PERF_COLOR_YELLOW;

	वापस color;
पूर्ण

अटल काष्ठा evsel *perf_stat__find_event(काष्ठा evlist *evsel_list,
						स्थिर अक्षर *name)
अणु
	काष्ठा evsel *c2;

	evlist__क्रम_each_entry (evsel_list, c2) अणु
		अगर (!strहालcmp(c2->name, name) && !c2->collect_stat)
			वापस c2;
	पूर्ण
	वापस शून्य;
पूर्ण

/* Mark MetricExpr target events and link events using them to them. */
व्योम perf_stat__collect_metric_expr(काष्ठा evlist *evsel_list)
अणु
	काष्ठा evsel *counter, *leader, **metric_events, *oc;
	bool found;
	काष्ठा expr_parse_ctx ctx;
	काष्ठा hashmap_entry *cur;
	माप_प्रकार bkt;
	पूर्णांक i;

	expr__ctx_init(&ctx);
	evlist__क्रम_each_entry(evsel_list, counter) अणु
		bool invalid = false;

		leader = counter->leader;
		अगर (!counter->metric_expr)
			जारी;

		expr__ctx_clear(&ctx);
		metric_events = counter->metric_events;
		अगर (!metric_events) अणु
			अगर (expr__find_other(counter->metric_expr,
					     counter->name,
					     &ctx, 1) < 0)
				जारी;

			metric_events = सुस्मृति(माप(काष्ठा evsel *),
					       hashmap__size(&ctx.ids) + 1);
			अगर (!metric_events) अणु
				expr__ctx_clear(&ctx);
				वापस;
			पूर्ण
			counter->metric_events = metric_events;
		पूर्ण

		i = 0;
		hashmap__क्रम_each_entry((&ctx.ids), cur, bkt) अणु
			स्थिर अक्षर *metric_name = (स्थिर अक्षर *)cur->key;

			found = false;
			अगर (leader) अणु
				/* Search in group */
				क्रम_each_group_member (oc, leader) अणु
					अगर (!strहालcmp(oc->name,
							metric_name) &&
						!oc->collect_stat) अणु
						found = true;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
			अगर (!found) अणु
				/* Search ignoring groups */
				oc = perf_stat__find_event(evsel_list,
							   metric_name);
			पूर्ण
			अगर (!oc) अणु
				/* Deduping one is good enough to handle duplicated PMUs. */
				अटल अक्षर *prपूर्णांकed;

				/*
				 * Adding events स्वतःmatically would be dअगरficult, because
				 * it would risk creating groups that are not schedulable.
				 * perf stat करोesn't understand all the scheduling स्थिरraपूर्णांकs
				 * of events. So we ask the user instead to add the missing
				 * events.
				 */
				अगर (!prपूर्णांकed ||
				    strहालcmp(prपूर्णांकed, metric_name)) अणु
					ख_लिखो(मानक_त्रुटि,
						"Add %s event to groups to get metric expression for %s\n",
						metric_name,
						counter->name);
					prपूर्णांकed = strdup(metric_name);
				पूर्ण
				invalid = true;
				जारी;
			पूर्ण
			metric_events[i++] = oc;
			oc->collect_stat = true;
		पूर्ण
		metric_events[i] = शून्य;
		अगर (invalid) अणु
			मुक्त(metric_events);
			counter->metric_events = शून्य;
			counter->metric_expr = शून्य;
		पूर्ण
	पूर्ण
	expr__ctx_clear(&ctx);
पूर्ण

अटल द्विगुन runसमय_stat_avg(काष्ठा runसमय_stat *st,
			       क्रमागत stat_type type, पूर्णांक cpu,
			       काष्ठा runसमय_stat_data *rsd)
अणु
	काष्ठा saved_value *v;

	v = saved_value_lookup(शून्य, cpu, false, type, rsd->ctx, st, rsd->cgrp);
	अगर (!v)
		वापस 0.0;

	वापस avg_stats(&v->stats);
पूर्ण

अटल द्विगुन runसमय_stat_n(काष्ठा runसमय_stat *st,
			     क्रमागत stat_type type, पूर्णांक cpu,
			     काष्ठा runसमय_stat_data *rsd)
अणु
	काष्ठा saved_value *v;

	v = saved_value_lookup(शून्य, cpu, false, type, rsd->ctx, st, rsd->cgrp);
	अगर (!v)
		वापस 0.0;

	वापस v->stats.n;
पूर्ण

अटल व्योम prपूर्णांक_stalled_cycles_frontend(काष्ठा perf_stat_config *config,
					  पूर्णांक cpu, द्विगुन avg,
					  काष्ठा perf_stat_output_ctx *out,
					  काष्ठा runसमय_stat *st,
					  काष्ठा runसमय_stat_data *rsd)
अणु
	द्विगुन total, ratio = 0.0;
	स्थिर अक्षर *color;

	total = runसमय_stat_avg(st, STAT_CYCLES, cpu, rsd);

	अगर (total)
		ratio = avg / total * 100.0;

	color = get_ratio_color(GRC_STALLED_CYCLES_FE, ratio);

	अगर (ratio)
		out->prपूर्णांक_metric(config, out->ctx, color, "%7.2f%%", "frontend cycles idle",
				  ratio);
	अन्यथा
		out->prपूर्णांक_metric(config, out->ctx, शून्य, शून्य, "frontend cycles idle", 0);
पूर्ण

अटल व्योम prपूर्णांक_stalled_cycles_backend(काष्ठा perf_stat_config *config,
					 पूर्णांक cpu, द्विगुन avg,
					 काष्ठा perf_stat_output_ctx *out,
					 काष्ठा runसमय_stat *st,
					 काष्ठा runसमय_stat_data *rsd)
अणु
	द्विगुन total, ratio = 0.0;
	स्थिर अक्षर *color;

	total = runसमय_stat_avg(st, STAT_CYCLES, cpu, rsd);

	अगर (total)
		ratio = avg / total * 100.0;

	color = get_ratio_color(GRC_STALLED_CYCLES_BE, ratio);

	out->prपूर्णांक_metric(config, out->ctx, color, "%7.2f%%", "backend cycles idle", ratio);
पूर्ण

अटल व्योम prपूर्णांक_branch_misses(काष्ठा perf_stat_config *config,
				पूर्णांक cpu, द्विगुन avg,
				काष्ठा perf_stat_output_ctx *out,
				काष्ठा runसमय_stat *st,
				काष्ठा runसमय_stat_data *rsd)
अणु
	द्विगुन total, ratio = 0.0;
	स्थिर अक्षर *color;

	total = runसमय_stat_avg(st, STAT_BRANCHES, cpu, rsd);

	अगर (total)
		ratio = avg / total * 100.0;

	color = get_ratio_color(GRC_CACHE_MISSES, ratio);

	out->prपूर्णांक_metric(config, out->ctx, color, "%7.2f%%", "of all branches", ratio);
पूर्ण

अटल व्योम prपूर्णांक_l1_dcache_misses(काष्ठा perf_stat_config *config,
				   पूर्णांक cpu, द्विगुन avg,
				   काष्ठा perf_stat_output_ctx *out,
				   काष्ठा runसमय_stat *st,
				   काष्ठा runसमय_stat_data *rsd)
अणु
	द्विगुन total, ratio = 0.0;
	स्थिर अक्षर *color;

	total = runसमय_stat_avg(st, STAT_L1_DCACHE, cpu, rsd);

	अगर (total)
		ratio = avg / total * 100.0;

	color = get_ratio_color(GRC_CACHE_MISSES, ratio);

	out->prपूर्णांक_metric(config, out->ctx, color, "%7.2f%%", "of all L1-dcache accesses", ratio);
पूर्ण

अटल व्योम prपूर्णांक_l1_icache_misses(काष्ठा perf_stat_config *config,
				   पूर्णांक cpu, द्विगुन avg,
				   काष्ठा perf_stat_output_ctx *out,
				   काष्ठा runसमय_stat *st,
				   काष्ठा runसमय_stat_data *rsd)
अणु
	द्विगुन total, ratio = 0.0;
	स्थिर अक्षर *color;

	total = runसमय_stat_avg(st, STAT_L1_ICACHE, cpu, rsd);

	अगर (total)
		ratio = avg / total * 100.0;

	color = get_ratio_color(GRC_CACHE_MISSES, ratio);
	out->prपूर्णांक_metric(config, out->ctx, color, "%7.2f%%", "of all L1-icache accesses", ratio);
पूर्ण

अटल व्योम prपूर्णांक_dtlb_cache_misses(काष्ठा perf_stat_config *config,
				    पूर्णांक cpu, द्विगुन avg,
				    काष्ठा perf_stat_output_ctx *out,
				    काष्ठा runसमय_stat *st,
				    काष्ठा runसमय_stat_data *rsd)
अणु
	द्विगुन total, ratio = 0.0;
	स्थिर अक्षर *color;

	total = runसमय_stat_avg(st, STAT_DTLB_CACHE, cpu, rsd);

	अगर (total)
		ratio = avg / total * 100.0;

	color = get_ratio_color(GRC_CACHE_MISSES, ratio);
	out->prपूर्णांक_metric(config, out->ctx, color, "%7.2f%%", "of all dTLB cache accesses", ratio);
पूर्ण

अटल व्योम prपूर्णांक_itlb_cache_misses(काष्ठा perf_stat_config *config,
				    पूर्णांक cpu, द्विगुन avg,
				    काष्ठा perf_stat_output_ctx *out,
				    काष्ठा runसमय_stat *st,
				    काष्ठा runसमय_stat_data *rsd)
अणु
	द्विगुन total, ratio = 0.0;
	स्थिर अक्षर *color;

	total = runसमय_stat_avg(st, STAT_ITLB_CACHE, cpu, rsd);

	अगर (total)
		ratio = avg / total * 100.0;

	color = get_ratio_color(GRC_CACHE_MISSES, ratio);
	out->prपूर्णांक_metric(config, out->ctx, color, "%7.2f%%", "of all iTLB cache accesses", ratio);
पूर्ण

अटल व्योम prपूर्णांक_ll_cache_misses(काष्ठा perf_stat_config *config,
				  पूर्णांक cpu, द्विगुन avg,
				  काष्ठा perf_stat_output_ctx *out,
				  काष्ठा runसमय_stat *st,
				  काष्ठा runसमय_stat_data *rsd)
अणु
	द्विगुन total, ratio = 0.0;
	स्थिर अक्षर *color;

	total = runसमय_stat_avg(st, STAT_LL_CACHE, cpu, rsd);

	अगर (total)
		ratio = avg / total * 100.0;

	color = get_ratio_color(GRC_CACHE_MISSES, ratio);
	out->prपूर्णांक_metric(config, out->ctx, color, "%7.2f%%", "of all LL-cache accesses", ratio);
पूर्ण

/*
 * High level "TopDown" CPU core pipe line bottleneck अवरोध करोwn.
 *
 * Basic concept following
 * Yasin, A Top Down Method क्रम Perक्रमmance analysis and Counter architecture
 * ISPASS14
 *
 * The CPU pipeline is भागided पूर्णांकo 4 areas that can be bottlenecks:
 *
 * Frontend -> Backend -> Retiring
 * BadSpeculation in addition means out of order execution that is thrown away
 * (क्रम example branch mispredictions)
 * Frontend is inकाष्ठाion decoding.
 * Backend is execution, like computation and accessing data in memory
 * Retiring is good execution that is not directly bottlenecked
 *
 * The क्रमmulas are computed in slots.
 * A slot is an entry in the pipeline each क्रम the pipeline width
 * (क्रम example a 4-wide pipeline has 4 slots क्रम each cycle)
 *
 * Formulas:
 * BadSpeculation = ((SlotsIssued - SlotsRetired) + RecoveryBubbles) /
 *			TotalSlots
 * Retiring = SlotsRetired / TotalSlots
 * FrontendBound = FetchBubbles / TotalSlots
 * BackendBound = 1.0 - BadSpeculation - Retiring - FrontendBound
 *
 * The kernel provides the mapping to the low level CPU events and any scaling
 * needed क्रम the CPU pipeline width, क्रम example:
 *
 * TotalSlots = Cycles * 4
 *
 * The scaling factor is communicated in the sysfs unit.
 *
 * In some हालs the CPU may not be able to measure all the क्रमmulas due to
 * missing events. In this हाल multiple क्रमmulas are combined, as possible.
 *
 * Full TopDown supports more levels to sub-भागide each area: क्रम example
 * BackendBound पूर्णांकo computing bound and memory bound. For now we only
 * support Level 1 TopDown.
 */

अटल द्विगुन sanitize_val(द्विगुन x)
अणु
	अगर (x < 0 && x >= -0.02)
		वापस 0.0;
	वापस x;
पूर्ण

अटल द्विगुन td_total_slots(पूर्णांक cpu, काष्ठा runसमय_stat *st,
			     काष्ठा runसमय_stat_data *rsd)
अणु
	वापस runसमय_stat_avg(st, STAT_TOPDOWN_TOTAL_SLOTS, cpu, rsd);
पूर्ण

अटल द्विगुन td_bad_spec(पूर्णांक cpu, काष्ठा runसमय_stat *st,
			  काष्ठा runसमय_stat_data *rsd)
अणु
	द्विगुन bad_spec = 0;
	द्विगुन total_slots;
	द्विगुन total;

	total = runसमय_stat_avg(st, STAT_TOPDOWN_SLOTS_ISSUED, cpu, rsd) -
		runसमय_stat_avg(st, STAT_TOPDOWN_SLOTS_RETIRED, cpu, rsd) +
		runसमय_stat_avg(st, STAT_TOPDOWN_RECOVERY_BUBBLES, cpu, rsd);

	total_slots = td_total_slots(cpu, st, rsd);
	अगर (total_slots)
		bad_spec = total / total_slots;
	वापस sanitize_val(bad_spec);
पूर्ण

अटल द्विगुन td_retiring(पूर्णांक cpu, काष्ठा runसमय_stat *st,
			  काष्ठा runसमय_stat_data *rsd)
अणु
	द्विगुन retiring = 0;
	द्विगुन total_slots = td_total_slots(cpu, st, rsd);
	द्विगुन ret_slots = runसमय_stat_avg(st, STAT_TOPDOWN_SLOTS_RETIRED,
					    cpu, rsd);

	अगर (total_slots)
		retiring = ret_slots / total_slots;
	वापस retiring;
पूर्ण

अटल द्विगुन td_fe_bound(पूर्णांक cpu, काष्ठा runसमय_stat *st,
			  काष्ठा runसमय_stat_data *rsd)
अणु
	द्विगुन fe_bound = 0;
	द्विगुन total_slots = td_total_slots(cpu, st, rsd);
	द्विगुन fetch_bub = runसमय_stat_avg(st, STAT_TOPDOWN_FETCH_BUBBLES,
					    cpu, rsd);

	अगर (total_slots)
		fe_bound = fetch_bub / total_slots;
	वापस fe_bound;
पूर्ण

अटल द्विगुन td_be_bound(पूर्णांक cpu, काष्ठा runसमय_stat *st,
			  काष्ठा runसमय_stat_data *rsd)
अणु
	द्विगुन sum = (td_fe_bound(cpu, st, rsd) +
		      td_bad_spec(cpu, st, rsd) +
		      td_retiring(cpu, st, rsd));
	अगर (sum == 0)
		वापस 0;
	वापस sanitize_val(1.0 - sum);
पूर्ण

/*
 * Kernel reports metrics multiplied with slots. To get back
 * the ratios we need to recreate the sum.
 */

अटल द्विगुन td_metric_ratio(पूर्णांक cpu, क्रमागत stat_type type,
			      काष्ठा runसमय_stat *stat,
			      काष्ठा runसमय_stat_data *rsd)
अणु
	द्विगुन sum = runसमय_stat_avg(stat, STAT_TOPDOWN_RETIRING, cpu, rsd) +
		runसमय_stat_avg(stat, STAT_TOPDOWN_FE_BOUND, cpu, rsd) +
		runसमय_stat_avg(stat, STAT_TOPDOWN_BE_BOUND, cpu, rsd) +
		runसमय_stat_avg(stat, STAT_TOPDOWN_BAD_SPEC, cpu, rsd);
	द्विगुन d = runसमय_stat_avg(stat, type, cpu, rsd);

	अगर (sum)
		वापस d / sum;
	वापस 0;
पूर्ण

/*
 * ... but only अगर most of the values are actually available.
 * We allow two missing.
 */

अटल bool full_td(पूर्णांक cpu, काष्ठा runसमय_stat *stat,
		    काष्ठा runसमय_stat_data *rsd)
अणु
	पूर्णांक c = 0;

	अगर (runसमय_stat_avg(stat, STAT_TOPDOWN_RETIRING, cpu, rsd) > 0)
		c++;
	अगर (runसमय_stat_avg(stat, STAT_TOPDOWN_BE_BOUND, cpu, rsd) > 0)
		c++;
	अगर (runसमय_stat_avg(stat, STAT_TOPDOWN_FE_BOUND, cpu, rsd) > 0)
		c++;
	अगर (runसमय_stat_avg(stat, STAT_TOPDOWN_BAD_SPEC, cpu, rsd) > 0)
		c++;
	वापस c >= 2;
पूर्ण

अटल व्योम prपूर्णांक_smi_cost(काष्ठा perf_stat_config *config, पूर्णांक cpu,
			   काष्ठा perf_stat_output_ctx *out,
			   काष्ठा runसमय_stat *st,
			   काष्ठा runसमय_stat_data *rsd)
अणु
	द्विगुन smi_num, aperf, cycles, cost = 0.0;
	स्थिर अक्षर *color = शून्य;

	smi_num = runसमय_stat_avg(st, STAT_SMI_NUM, cpu, rsd);
	aperf = runसमय_stat_avg(st, STAT_APERF, cpu, rsd);
	cycles = runसमय_stat_avg(st, STAT_CYCLES, cpu, rsd);

	अगर ((cycles == 0) || (aperf == 0))
		वापस;

	अगर (smi_num)
		cost = (aperf - cycles) / aperf * 100.00;

	अगर (cost > 10)
		color = PERF_COLOR_RED;
	out->prपूर्णांक_metric(config, out->ctx, color, "%8.1f%%", "SMI cycles%", cost);
	out->prपूर्णांक_metric(config, out->ctx, शून्य, "%4.0f", "SMI#", smi_num);
पूर्ण

अटल पूर्णांक prepare_metric(काष्ठा evsel **metric_events,
			  काष्ठा metric_ref *metric_refs,
			  काष्ठा expr_parse_ctx *pctx,
			  पूर्णांक cpu,
			  काष्ठा runसमय_stat *st)
अणु
	द्विगुन scale;
	अक्षर *n, *pn;
	पूर्णांक i, j, ret;

	expr__ctx_init(pctx);
	क्रम (i = 0; metric_events[i]; i++) अणु
		काष्ठा saved_value *v;
		काष्ठा stats *stats;
		u64 metric_total = 0;

		अगर (!म_भेद(metric_events[i]->name, "duration_time")) अणु
			stats = &wallसमय_nsecs_stats;
			scale = 1e-9;
		पूर्ण अन्यथा अणु
			v = saved_value_lookup(metric_events[i], cpu, false,
					       STAT_NONE, 0, st,
					       metric_events[i]->cgrp);
			अगर (!v)
				अवरोध;
			stats = &v->stats;
			scale = 1.0;

			अगर (v->metric_other)
				metric_total = v->metric_total;
		पूर्ण

		n = strdup(metric_events[i]->name);
		अगर (!n)
			वापस -ENOMEM;
		/*
		 * This display code with --no-merge adds [cpu] postfixes.
		 * These are not supported by the parser. Remove everything
		 * after the space.
		 */
		pn = म_अक्षर(n, ' ');
		अगर (pn)
			*pn = 0;

		अगर (metric_total)
			expr__add_id_val(pctx, n, metric_total);
		अन्यथा
			expr__add_id_val(pctx, n, avg_stats(stats)*scale);
	पूर्ण

	क्रम (j = 0; metric_refs && metric_refs[j].metric_name; j++) अणु
		ret = expr__add_ref(pctx, &metric_refs[j]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस i;
पूर्ण

अटल व्योम generic_metric(काष्ठा perf_stat_config *config,
			   स्थिर अक्षर *metric_expr,
			   काष्ठा evsel **metric_events,
			   काष्ठा metric_ref *metric_refs,
			   अक्षर *name,
			   स्थिर अक्षर *metric_name,
			   स्थिर अक्षर *metric_unit,
			   पूर्णांक runसमय,
			   पूर्णांक cpu,
			   काष्ठा perf_stat_output_ctx *out,
			   काष्ठा runसमय_stat *st)
अणु
	prपूर्णांक_metric_t prपूर्णांक_metric = out->prपूर्णांक_metric;
	काष्ठा expr_parse_ctx pctx;
	द्विगुन ratio, scale;
	पूर्णांक i;
	व्योम *ctxp = out->ctx;

	i = prepare_metric(metric_events, metric_refs, &pctx, cpu, st);
	अगर (i < 0)
		वापस;

	अगर (!metric_events[i]) अणु
		अगर (expr__parse(&ratio, &pctx, metric_expr, runसमय) == 0) अणु
			अक्षर *unit;
			अक्षर metric_bf[64];

			अगर (metric_unit && metric_name) अणु
				अगर (perf_pmu__convert_scale(metric_unit,
					&unit, &scale) >= 0) अणु
					ratio *= scale;
				पूर्ण
				अगर (म_माला(metric_expr, "?"))
					scnम_लिखो(metric_bf, माप(metric_bf),
					  "%s  %s_%d", unit, metric_name, runसमय);
				अन्यथा
					scnम_लिखो(metric_bf, माप(metric_bf),
					  "%s  %s", unit, metric_name);

				prपूर्णांक_metric(config, ctxp, शून्य, "%8.1f",
					     metric_bf, ratio);
			पूर्ण अन्यथा अणु
				prपूर्णांक_metric(config, ctxp, शून्य, "%8.2f",
					metric_name ?
					metric_name :
					out->क्रमce_header ?  name : "",
					ratio);
			पूर्ण
		पूर्ण अन्यथा अणु
			prपूर्णांक_metric(config, ctxp, शून्य, शून्य,
				     out->क्रमce_header ?
				     (metric_name ? metric_name : name) : "", 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांक_metric(config, ctxp, शून्य, शून्य,
			     out->क्रमce_header ?
			     (metric_name ? metric_name : name) : "", 0);
	पूर्ण

	expr__ctx_clear(&pctx);
पूर्ण

द्विगुन test_generic_metric(काष्ठा metric_expr *mexp, पूर्णांक cpu, काष्ठा runसमय_stat *st)
अणु
	काष्ठा expr_parse_ctx pctx;
	द्विगुन ratio = 0.0;

	अगर (prepare_metric(mexp->metric_events, mexp->metric_refs, &pctx, cpu, st) < 0)
		जाओ out;

	अगर (expr__parse(&ratio, &pctx, mexp->metric_expr, 1))
		ratio = 0.0;

out:
	expr__ctx_clear(&pctx);
	वापस ratio;
पूर्ण

व्योम perf_stat__prपूर्णांक_shaकरोw_stats(काष्ठा perf_stat_config *config,
				   काष्ठा evsel *evsel,
				   द्विगुन avg, पूर्णांक cpu,
				   काष्ठा perf_stat_output_ctx *out,
				   काष्ठा rblist *metric_events,
				   काष्ठा runसमय_stat *st)
अणु
	व्योम *ctxp = out->ctx;
	prपूर्णांक_metric_t prपूर्णांक_metric = out->prपूर्णांक_metric;
	द्विगुन total, ratio = 0.0, total2;
	स्थिर अक्षर *color = शून्य;
	काष्ठा runसमय_stat_data rsd = अणु
		.ctx = evsel_context(evsel),
		.cgrp = evsel->cgrp,
	पूर्ण;
	काष्ठा metric_event *me;
	पूर्णांक num = 1;

	अगर (config->iostat_run) अणु
		iostat_prपूर्णांक_metric(config, evsel, out);
	पूर्ण अन्यथा अगर (evsel__match(evsel, HARDWARE, HW_INSTRUCTIONS)) अणु
		total = runसमय_stat_avg(st, STAT_CYCLES, cpu, &rsd);

		अगर (total) अणु
			ratio = avg / total;
			prपूर्णांक_metric(config, ctxp, शून्य, "%7.2f ",
					"insn per cycle", ratio);
		पूर्ण अन्यथा अणु
			prपूर्णांक_metric(config, ctxp, शून्य, शून्य, "insn per cycle", 0);
		पूर्ण

		total = runसमय_stat_avg(st, STAT_STALLED_CYCLES_FRONT, cpu, &rsd);

		total = max(total, runसमय_stat_avg(st,
						    STAT_STALLED_CYCLES_BACK,
						    cpu, &rsd));

		अगर (total && avg) अणु
			out->new_line(config, ctxp);
			ratio = total / avg;
			prपूर्णांक_metric(config, ctxp, शून्य, "%7.2f ",
					"stalled cycles per insn",
					ratio);
		पूर्ण
	पूर्ण अन्यथा अगर (evsel__match(evsel, HARDWARE, HW_BRANCH_MISSES)) अणु
		अगर (runसमय_stat_n(st, STAT_BRANCHES, cpu, &rsd) != 0)
			prपूर्णांक_branch_misses(config, cpu, avg, out, st, &rsd);
		अन्यथा
			prपूर्णांक_metric(config, ctxp, शून्य, शून्य, "of all branches", 0);
	पूर्ण अन्यथा अगर (
		evsel->core.attr.type == PERF_TYPE_HW_CACHE &&
		evsel->core.attr.config ==  ( PERF_COUNT_HW_CACHE_L1D |
					((PERF_COUNT_HW_CACHE_OP_READ) << 8) |
					 ((PERF_COUNT_HW_CACHE_RESULT_MISS) << 16))) अणु

		अगर (runसमय_stat_n(st, STAT_L1_DCACHE, cpu, &rsd) != 0)
			prपूर्णांक_l1_dcache_misses(config, cpu, avg, out, st, &rsd);
		अन्यथा
			prपूर्णांक_metric(config, ctxp, शून्य, शून्य, "of all L1-dcache accesses", 0);
	पूर्ण अन्यथा अगर (
		evsel->core.attr.type == PERF_TYPE_HW_CACHE &&
		evsel->core.attr.config ==  ( PERF_COUNT_HW_CACHE_L1I |
					((PERF_COUNT_HW_CACHE_OP_READ) << 8) |
					 ((PERF_COUNT_HW_CACHE_RESULT_MISS) << 16))) अणु

		अगर (runसमय_stat_n(st, STAT_L1_ICACHE, cpu, &rsd) != 0)
			prपूर्णांक_l1_icache_misses(config, cpu, avg, out, st, &rsd);
		अन्यथा
			prपूर्णांक_metric(config, ctxp, शून्य, शून्य, "of all L1-icache accesses", 0);
	पूर्ण अन्यथा अगर (
		evsel->core.attr.type == PERF_TYPE_HW_CACHE &&
		evsel->core.attr.config ==  ( PERF_COUNT_HW_CACHE_DTLB |
					((PERF_COUNT_HW_CACHE_OP_READ) << 8) |
					 ((PERF_COUNT_HW_CACHE_RESULT_MISS) << 16))) अणु

		अगर (runसमय_stat_n(st, STAT_DTLB_CACHE, cpu, &rsd) != 0)
			prपूर्णांक_dtlb_cache_misses(config, cpu, avg, out, st, &rsd);
		अन्यथा
			prपूर्णांक_metric(config, ctxp, शून्य, शून्य, "of all dTLB cache accesses", 0);
	पूर्ण अन्यथा अगर (
		evsel->core.attr.type == PERF_TYPE_HW_CACHE &&
		evsel->core.attr.config ==  ( PERF_COUNT_HW_CACHE_ITLB |
					((PERF_COUNT_HW_CACHE_OP_READ) << 8) |
					 ((PERF_COUNT_HW_CACHE_RESULT_MISS) << 16))) अणु

		अगर (runसमय_stat_n(st, STAT_ITLB_CACHE, cpu, &rsd) != 0)
			prपूर्णांक_itlb_cache_misses(config, cpu, avg, out, st, &rsd);
		अन्यथा
			prपूर्णांक_metric(config, ctxp, शून्य, शून्य, "of all iTLB cache accesses", 0);
	पूर्ण अन्यथा अगर (
		evsel->core.attr.type == PERF_TYPE_HW_CACHE &&
		evsel->core.attr.config ==  ( PERF_COUNT_HW_CACHE_LL |
					((PERF_COUNT_HW_CACHE_OP_READ) << 8) |
					 ((PERF_COUNT_HW_CACHE_RESULT_MISS) << 16))) अणु

		अगर (runसमय_stat_n(st, STAT_LL_CACHE, cpu, &rsd) != 0)
			prपूर्णांक_ll_cache_misses(config, cpu, avg, out, st, &rsd);
		अन्यथा
			prपूर्णांक_metric(config, ctxp, शून्य, शून्य, "of all LL-cache accesses", 0);
	पूर्ण अन्यथा अगर (evsel__match(evsel, HARDWARE, HW_CACHE_MISSES)) अणु
		total = runसमय_stat_avg(st, STAT_CACHEREFS, cpu, &rsd);

		अगर (total)
			ratio = avg * 100 / total;

		अगर (runसमय_stat_n(st, STAT_CACHEREFS, cpu, &rsd) != 0)
			prपूर्णांक_metric(config, ctxp, शून्य, "%8.3f %%",
				     "of all cache refs", ratio);
		अन्यथा
			prपूर्णांक_metric(config, ctxp, शून्य, शून्य, "of all cache refs", 0);
	पूर्ण अन्यथा अगर (evsel__match(evsel, HARDWARE, HW_STALLED_CYCLES_FRONTEND)) अणु
		prपूर्णांक_stalled_cycles_frontend(config, cpu, avg, out, st, &rsd);
	पूर्ण अन्यथा अगर (evsel__match(evsel, HARDWARE, HW_STALLED_CYCLES_BACKEND)) अणु
		prपूर्णांक_stalled_cycles_backend(config, cpu, avg, out, st, &rsd);
	पूर्ण अन्यथा अगर (evsel__match(evsel, HARDWARE, HW_CPU_CYCLES)) अणु
		total = runसमय_stat_avg(st, STAT_NSECS, cpu, &rsd);

		अगर (total) अणु
			ratio = avg / total;
			prपूर्णांक_metric(config, ctxp, शून्य, "%8.3f", "GHz", ratio);
		पूर्ण अन्यथा अणु
			prपूर्णांक_metric(config, ctxp, शून्य, शून्य, "Ghz", 0);
		पूर्ण
	पूर्ण अन्यथा अगर (perf_stat_evsel__is(evsel, CYCLES_IN_TX)) अणु
		total = runसमय_stat_avg(st, STAT_CYCLES, cpu, &rsd);

		अगर (total)
			prपूर्णांक_metric(config, ctxp, शून्य,
					"%7.2f%%", "transactional cycles",
					100.0 * (avg / total));
		अन्यथा
			prपूर्णांक_metric(config, ctxp, शून्य, शून्य, "transactional cycles",
				     0);
	पूर्ण अन्यथा अगर (perf_stat_evsel__is(evsel, CYCLES_IN_TX_CP)) अणु
		total = runसमय_stat_avg(st, STAT_CYCLES, cpu, &rsd);
		total2 = runसमय_stat_avg(st, STAT_CYCLES_IN_TX, cpu, &rsd);

		अगर (total2 < avg)
			total2 = avg;
		अगर (total)
			prपूर्णांक_metric(config, ctxp, शून्य, "%7.2f%%", "aborted cycles",
				100.0 * ((total2-avg) / total));
		अन्यथा
			prपूर्णांक_metric(config, ctxp, शून्य, शून्य, "aborted cycles", 0);
	पूर्ण अन्यथा अगर (perf_stat_evsel__is(evsel, TRANSACTION_START)) अणु
		total = runसमय_stat_avg(st, STAT_CYCLES_IN_TX, cpu, &rsd);

		अगर (avg)
			ratio = total / avg;

		अगर (runसमय_stat_n(st, STAT_CYCLES_IN_TX, cpu, &rsd) != 0)
			prपूर्णांक_metric(config, ctxp, शून्य, "%8.0f",
				     "cycles / transaction", ratio);
		अन्यथा
			prपूर्णांक_metric(config, ctxp, शून्य, शून्य, "cycles / transaction",
				      0);
	पूर्ण अन्यथा अगर (perf_stat_evsel__is(evsel, ELISION_START)) अणु
		total = runसमय_stat_avg(st, STAT_CYCLES_IN_TX, cpu, &rsd);

		अगर (avg)
			ratio = total / avg;

		prपूर्णांक_metric(config, ctxp, शून्य, "%8.0f", "cycles / elision", ratio);
	पूर्ण अन्यथा अगर (evsel__is_घड़ी(evsel)) अणु
		अगर ((ratio = avg_stats(&wallसमय_nsecs_stats)) != 0)
			prपूर्णांक_metric(config, ctxp, शून्य, "%8.3f", "CPUs utilized",
				     avg / (ratio * evsel->scale));
		अन्यथा
			prपूर्णांक_metric(config, ctxp, शून्य, शून्य, "CPUs utilized", 0);
	पूर्ण अन्यथा अगर (perf_stat_evsel__is(evsel, TOPDOWN_FETCH_BUBBLES)) अणु
		द्विगुन fe_bound = td_fe_bound(cpu, st, &rsd);

		अगर (fe_bound > 0.2)
			color = PERF_COLOR_RED;
		prपूर्णांक_metric(config, ctxp, color, "%8.1f%%", "frontend bound",
				fe_bound * 100.);
	पूर्ण अन्यथा अगर (perf_stat_evsel__is(evsel, TOPDOWN_SLOTS_RETIRED)) अणु
		द्विगुन retiring = td_retiring(cpu, st, &rsd);

		अगर (retiring > 0.7)
			color = PERF_COLOR_GREEN;
		prपूर्णांक_metric(config, ctxp, color, "%8.1f%%", "retiring",
				retiring * 100.);
	पूर्ण अन्यथा अगर (perf_stat_evsel__is(evsel, TOPDOWN_RECOVERY_BUBBLES)) अणु
		द्विगुन bad_spec = td_bad_spec(cpu, st, &rsd);

		अगर (bad_spec > 0.1)
			color = PERF_COLOR_RED;
		prपूर्णांक_metric(config, ctxp, color, "%8.1f%%", "bad speculation",
				bad_spec * 100.);
	पूर्ण अन्यथा अगर (perf_stat_evsel__is(evsel, TOPDOWN_SLOTS_ISSUED)) अणु
		द्विगुन be_bound = td_be_bound(cpu, st, &rsd);
		स्थिर अक्षर *name = "backend bound";
		अटल पूर्णांक have_recovery_bubbles = -1;

		/* In हाल the CPU करोes not support topकरोwn-recovery-bubbles */
		अगर (have_recovery_bubbles < 0)
			have_recovery_bubbles = pmu_have_event("cpu",
					"topdown-recovery-bubbles");
		अगर (!have_recovery_bubbles)
			name = "backend bound/bad spec";

		अगर (be_bound > 0.2)
			color = PERF_COLOR_RED;
		अगर (td_total_slots(cpu, st, &rsd) > 0)
			prपूर्णांक_metric(config, ctxp, color, "%8.1f%%", name,
					be_bound * 100.);
		अन्यथा
			prपूर्णांक_metric(config, ctxp, शून्य, शून्य, name, 0);
	पूर्ण अन्यथा अगर (perf_stat_evsel__is(evsel, TOPDOWN_RETIRING) &&
		   full_td(cpu, st, &rsd)) अणु
		द्विगुन retiring = td_metric_ratio(cpu,
						  STAT_TOPDOWN_RETIRING, st,
						  &rsd);
		अगर (retiring > 0.7)
			color = PERF_COLOR_GREEN;
		prपूर्णांक_metric(config, ctxp, color, "%8.1f%%", "retiring",
				retiring * 100.);
	पूर्ण अन्यथा अगर (perf_stat_evsel__is(evsel, TOPDOWN_FE_BOUND) &&
		   full_td(cpu, st, &rsd)) अणु
		द्विगुन fe_bound = td_metric_ratio(cpu,
						  STAT_TOPDOWN_FE_BOUND, st,
						  &rsd);
		अगर (fe_bound > 0.2)
			color = PERF_COLOR_RED;
		prपूर्णांक_metric(config, ctxp, color, "%8.1f%%", "frontend bound",
				fe_bound * 100.);
	पूर्ण अन्यथा अगर (perf_stat_evsel__is(evsel, TOPDOWN_BE_BOUND) &&
		   full_td(cpu, st, &rsd)) अणु
		द्विगुन be_bound = td_metric_ratio(cpu,
						  STAT_TOPDOWN_BE_BOUND, st,
						  &rsd);
		अगर (be_bound > 0.2)
			color = PERF_COLOR_RED;
		prपूर्णांक_metric(config, ctxp, color, "%8.1f%%", "backend bound",
				be_bound * 100.);
	पूर्ण अन्यथा अगर (perf_stat_evsel__is(evsel, TOPDOWN_BAD_SPEC) &&
		   full_td(cpu, st, &rsd)) अणु
		द्विगुन bad_spec = td_metric_ratio(cpu,
						  STAT_TOPDOWN_BAD_SPEC, st,
						  &rsd);
		अगर (bad_spec > 0.1)
			color = PERF_COLOR_RED;
		prपूर्णांक_metric(config, ctxp, color, "%8.1f%%", "bad speculation",
				bad_spec * 100.);
	पूर्ण अन्यथा अगर (perf_stat_evsel__is(evsel, TOPDOWN_HEAVY_OPS) &&
			full_td(cpu, st, &rsd) && (config->topकरोwn_level > 1)) अणु
		द्विगुन retiring = td_metric_ratio(cpu,
						  STAT_TOPDOWN_RETIRING, st,
						  &rsd);
		द्विगुन heavy_ops = td_metric_ratio(cpu,
						   STAT_TOPDOWN_HEAVY_OPS, st,
						   &rsd);
		द्विगुन light_ops = retiring - heavy_ops;

		अगर (retiring > 0.7 && heavy_ops > 0.1)
			color = PERF_COLOR_GREEN;
		prपूर्णांक_metric(config, ctxp, color, "%8.1f%%", "heavy operations",
				heavy_ops * 100.);
		अगर (retiring > 0.7 && light_ops > 0.6)
			color = PERF_COLOR_GREEN;
		अन्यथा
			color = शून्य;
		prपूर्णांक_metric(config, ctxp, color, "%8.1f%%", "light operations",
				light_ops * 100.);
	पूर्ण अन्यथा अगर (perf_stat_evsel__is(evsel, TOPDOWN_BR_MISPREDICT) &&
			full_td(cpu, st, &rsd) && (config->topकरोwn_level > 1)) अणु
		द्विगुन bad_spec = td_metric_ratio(cpu,
						  STAT_TOPDOWN_BAD_SPEC, st,
						  &rsd);
		द्विगुन br_mis = td_metric_ratio(cpu,
						STAT_TOPDOWN_BR_MISPREDICT, st,
						&rsd);
		द्विगुन m_clears = bad_spec - br_mis;

		अगर (bad_spec > 0.1 && br_mis > 0.05)
			color = PERF_COLOR_RED;
		prपूर्णांक_metric(config, ctxp, color, "%8.1f%%", "branch mispredict",
				br_mis * 100.);
		अगर (bad_spec > 0.1 && m_clears > 0.05)
			color = PERF_COLOR_RED;
		अन्यथा
			color = शून्य;
		prपूर्णांक_metric(config, ctxp, color, "%8.1f%%", "machine clears",
				m_clears * 100.);
	पूर्ण अन्यथा अगर (perf_stat_evsel__is(evsel, TOPDOWN_FETCH_LAT) &&
			full_td(cpu, st, &rsd) && (config->topकरोwn_level > 1)) अणु
		द्विगुन fe_bound = td_metric_ratio(cpu,
						  STAT_TOPDOWN_FE_BOUND, st,
						  &rsd);
		द्विगुन fetch_lat = td_metric_ratio(cpu,
						   STAT_TOPDOWN_FETCH_LAT, st,
						   &rsd);
		द्विगुन fetch_bw = fe_bound - fetch_lat;

		अगर (fe_bound > 0.2 && fetch_lat > 0.15)
			color = PERF_COLOR_RED;
		prपूर्णांक_metric(config, ctxp, color, "%8.1f%%", "fetch latency",
				fetch_lat * 100.);
		अगर (fe_bound > 0.2 && fetch_bw > 0.1)
			color = PERF_COLOR_RED;
		अन्यथा
			color = शून्य;
		prपूर्णांक_metric(config, ctxp, color, "%8.1f%%", "fetch bandwidth",
				fetch_bw * 100.);
	पूर्ण अन्यथा अगर (perf_stat_evsel__is(evsel, TOPDOWN_MEM_BOUND) &&
			full_td(cpu, st, &rsd) && (config->topकरोwn_level > 1)) अणु
		द्विगुन be_bound = td_metric_ratio(cpu,
						  STAT_TOPDOWN_BE_BOUND, st,
						  &rsd);
		द्विगुन mem_bound = td_metric_ratio(cpu,
						   STAT_TOPDOWN_MEM_BOUND, st,
						   &rsd);
		द्विगुन core_bound = be_bound - mem_bound;

		अगर (be_bound > 0.2 && mem_bound > 0.2)
			color = PERF_COLOR_RED;
		prपूर्णांक_metric(config, ctxp, color, "%8.1f%%", "memory bound",
				mem_bound * 100.);
		अगर (be_bound > 0.2 && core_bound > 0.1)
			color = PERF_COLOR_RED;
		अन्यथा
			color = शून्य;
		prपूर्णांक_metric(config, ctxp, color, "%8.1f%%", "Core bound",
				core_bound * 100.);
	पूर्ण अन्यथा अगर (evsel->metric_expr) अणु
		generic_metric(config, evsel->metric_expr, evsel->metric_events, शून्य,
				evsel->name, evsel->metric_name, शून्य, 1, cpu, out, st);
	पूर्ण अन्यथा अगर (runसमय_stat_n(st, STAT_NSECS, cpu, &rsd) != 0) अणु
		अक्षर unit = ' ';
		अक्षर unit_buf[10] = "/sec";

		total = runसमय_stat_avg(st, STAT_NSECS, cpu, &rsd);
		अगर (total)
			ratio = convert_unit_द्विगुन(1000000000.0 * avg / total, &unit);

		अगर (unit != ' ')
			snम_लिखो(unit_buf, माप(unit_buf), "%c/sec", unit);
		prपूर्णांक_metric(config, ctxp, शून्य, "%8.3f", unit_buf, ratio);
	पूर्ण अन्यथा अगर (perf_stat_evsel__is(evsel, SMI_NUM)) अणु
		prपूर्णांक_smi_cost(config, cpu, out, st, &rsd);
	पूर्ण अन्यथा अणु
		num = 0;
	पूर्ण

	अगर ((me = metricgroup__lookup(metric_events, evsel, false)) != शून्य) अणु
		काष्ठा metric_expr *mexp;

		list_क्रम_each_entry (mexp, &me->head, nd) अणु
			अगर (num++ > 0)
				out->new_line(config, ctxp);
			generic_metric(config, mexp->metric_expr, mexp->metric_events,
					mexp->metric_refs, evsel->name, mexp->metric_name,
					mexp->metric_unit, mexp->runसमय, cpu, out, st);
		पूर्ण
	पूर्ण
	अगर (num == 0)
		prपूर्णांक_metric(config, ctxp, शून्य, शून्य, शून्य, 0);
पूर्ण
