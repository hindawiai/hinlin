<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <गणित.स>
#समावेश <माला.स>
#समावेश "counts.h"
#समावेश "cpumap.h"
#समावेश "debug.h"
#समावेश "header.h"
#समावेश "stat.h"
#समावेश "session.h"
#समावेश "target.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "thread_map.h"
#समावेश "hashmap.h"
#समावेश <linux/zभाग.स>

व्योम update_stats(काष्ठा stats *stats, u64 val)
अणु
	द्विगुन delta;

	stats->n++;
	delta = val - stats->mean;
	stats->mean += delta / stats->n;
	stats->M2 += delta*(val - stats->mean);

	अगर (val > stats->max)
		stats->max = val;

	अगर (val < stats->min)
		stats->min = val;
पूर्ण

द्विगुन avg_stats(काष्ठा stats *stats)
अणु
	वापस stats->mean;
पूर्ण

/*
 * http://en.wikipedia.org/wiki/Algorithms_क्रम_calculating_variance
 *
 *       (\Sum n_i^2) - ((\Sum n_i)^2)/n
 * s^2 = -------------------------------
 *                  n - 1
 *
 * http://en.wikipedia.org/wiki/Stddev
 *
 * The std dev of the mean is related to the std dev by:
 *
 *             s
 * s_mean = -------
 *          वर्ग_मूल(n)
 *
 */
द्विगुन stddev_stats(काष्ठा stats *stats)
अणु
	द्विगुन variance, variance_mean;

	अगर (stats->n < 2)
		वापस 0.0;

	variance = stats->M2 / (stats->n - 1);
	variance_mean = variance / stats->n;

	वापस वर्ग_मूल(variance_mean);
पूर्ण

द्विगुन rel_stddev_stats(द्विगुन stddev, द्विगुन avg)
अणु
	द्विगुन pct = 0.0;

	अगर (avg)
		pct = 100.0 * stddev/avg;

	वापस pct;
पूर्ण

bool __perf_stat_evsel__is(काष्ठा evsel *evsel, क्रमागत perf_stat_evsel_id id)
अणु
	काष्ठा perf_stat_evsel *ps = evsel->stats;

	वापस ps->id == id;
पूर्ण

#घोषणा ID(id, name) [PERF_STAT_EVSEL_ID__##id] = #name
अटल स्थिर अक्षर *id_str[PERF_STAT_EVSEL_ID__MAX] = अणु
	ID(NONE,		x),
	ID(CYCLES_IN_TX,	cpu/cycles-t/),
	ID(TRANSACTION_START,	cpu/tx-start/),
	ID(ELISION_START,	cpu/el-start/),
	ID(CYCLES_IN_TX_CP,	cpu/cycles-ct/),
	ID(TOPDOWN_TOTAL_SLOTS, topकरोwn-total-slots),
	ID(TOPDOWN_SLOTS_ISSUED, topकरोwn-slots-issued),
	ID(TOPDOWN_SLOTS_RETIRED, topकरोwn-slots-retired),
	ID(TOPDOWN_FETCH_BUBBLES, topकरोwn-fetch-bubbles),
	ID(TOPDOWN_RECOVERY_BUBBLES, topकरोwn-recovery-bubbles),
	ID(TOPDOWN_RETIRING, topकरोwn-retiring),
	ID(TOPDOWN_BAD_SPEC, topकरोwn-bad-spec),
	ID(TOPDOWN_FE_BOUND, topकरोwn-fe-bound),
	ID(TOPDOWN_BE_BOUND, topकरोwn-be-bound),
	ID(TOPDOWN_HEAVY_OPS, topकरोwn-heavy-ops),
	ID(TOPDOWN_BR_MISPREDICT, topकरोwn-br-mispredict),
	ID(TOPDOWN_FETCH_LAT, topकरोwn-fetch-lat),
	ID(TOPDOWN_MEM_BOUND, topकरोwn-mem-bound),
	ID(SMI_NUM, msr/smi/),
	ID(APERF, msr/aperf/),
पूर्ण;
#अघोषित ID

अटल व्योम perf_stat_evsel_id_init(काष्ठा evsel *evsel)
अणु
	काष्ठा perf_stat_evsel *ps = evsel->stats;
	पूर्णांक i;

	/* ps->id is 0 hence PERF_STAT_EVSEL_ID__NONE by शेष */

	क्रम (i = 0; i < PERF_STAT_EVSEL_ID__MAX; i++) अणु
		अगर (!म_भेद(evsel__name(evsel), id_str[i])) अणु
			ps->id = i;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम evsel__reset_stat_priv(काष्ठा evsel *evsel)
अणु
	पूर्णांक i;
	काष्ठा perf_stat_evsel *ps = evsel->stats;

	क्रम (i = 0; i < 3; i++)
		init_stats(&ps->res_stats[i]);

	perf_stat_evsel_id_init(evsel);
पूर्ण

अटल पूर्णांक evsel__alloc_stat_priv(काष्ठा evsel *evsel)
अणु
	evsel->stats = zalloc(माप(काष्ठा perf_stat_evsel));
	अगर (evsel->stats == शून्य)
		वापस -ENOMEM;
	evsel__reset_stat_priv(evsel);
	वापस 0;
पूर्ण

अटल व्योम evsel__मुक्त_stat_priv(काष्ठा evsel *evsel)
अणु
	काष्ठा perf_stat_evsel *ps = evsel->stats;

	अगर (ps)
		zमुक्त(&ps->group_data);
	zमुक्त(&evsel->stats);
पूर्ण

अटल पूर्णांक evsel__alloc_prev_raw_counts(काष्ठा evsel *evsel, पूर्णांक ncpus, पूर्णांक nthपढ़ोs)
अणु
	काष्ठा perf_counts *counts;

	counts = perf_counts__new(ncpus, nthपढ़ोs);
	अगर (counts)
		evsel->prev_raw_counts = counts;

	वापस counts ? 0 : -ENOMEM;
पूर्ण

अटल व्योम evsel__मुक्त_prev_raw_counts(काष्ठा evsel *evsel)
अणु
	perf_counts__delete(evsel->prev_raw_counts);
	evsel->prev_raw_counts = शून्य;
पूर्ण

अटल व्योम evsel__reset_prev_raw_counts(काष्ठा evsel *evsel)
अणु
	अगर (evsel->prev_raw_counts)
		perf_counts__reset(evsel->prev_raw_counts);
पूर्ण

अटल पूर्णांक evsel__alloc_stats(काष्ठा evsel *evsel, bool alloc_raw)
अणु
	पूर्णांक ncpus = evsel__nr_cpus(evsel);
	पूर्णांक nthपढ़ोs = perf_thपढ़ो_map__nr(evsel->core.thपढ़ोs);

	अगर (evsel__alloc_stat_priv(evsel) < 0 ||
	    evsel__alloc_counts(evsel, ncpus, nthपढ़ोs) < 0 ||
	    (alloc_raw && evsel__alloc_prev_raw_counts(evsel, ncpus, nthपढ़ोs) < 0))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

पूर्णांक evlist__alloc_stats(काष्ठा evlist *evlist, bool alloc_raw)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel__alloc_stats(evsel, alloc_raw))
			जाओ out_मुक्त;
	पूर्ण

	वापस 0;

out_मुक्त:
	evlist__मुक्त_stats(evlist);
	वापस -1;
पूर्ण

व्योम evlist__मुक्त_stats(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		evsel__मुक्त_stat_priv(evsel);
		evsel__मुक्त_counts(evsel);
		evsel__मुक्त_prev_raw_counts(evsel);
	पूर्ण
पूर्ण

व्योम evlist__reset_stats(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		evsel__reset_stat_priv(evsel);
		evsel__reset_counts(evsel);
	पूर्ण
पूर्ण

व्योम evlist__reset_prev_raw_counts(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel)
		evsel__reset_prev_raw_counts(evsel);
पूर्ण

अटल व्योम evsel__copy_prev_raw_counts(काष्ठा evsel *evsel)
अणु
	पूर्णांक ncpus = evsel__nr_cpus(evsel);
	पूर्णांक nthपढ़ोs = perf_thपढ़ो_map__nr(evsel->core.thपढ़ोs);

	क्रम (पूर्णांक thपढ़ो = 0; thपढ़ो < nthपढ़ोs; thपढ़ो++) अणु
		क्रम (पूर्णांक cpu = 0; cpu < ncpus; cpu++) अणु
			*perf_counts(evsel->counts, cpu, thपढ़ो) =
				*perf_counts(evsel->prev_raw_counts, cpu,
					     thपढ़ो);
		पूर्ण
	पूर्ण

	evsel->counts->aggr = evsel->prev_raw_counts->aggr;
पूर्ण

व्योम evlist__copy_prev_raw_counts(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel)
		evsel__copy_prev_raw_counts(evsel);
पूर्ण

व्योम evlist__save_aggr_prev_raw_counts(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;

	/*
	 * To collect the overall statistics क्रम पूर्णांकerval mode,
	 * we copy the counts from evsel->prev_raw_counts to
	 * evsel->counts. The perf_stat_process_counter creates
	 * aggr values from per cpu values, but the per cpu values
	 * are 0 क्रम AGGR_GLOBAL. So we use a trick that saves the
	 * previous aggr value to the first member of perf_counts,
	 * then aggr calculation in process_counter_values can work
	 * correctly.
	 */
	evlist__क्रम_each_entry(evlist, evsel) अणु
		*perf_counts(evsel->prev_raw_counts, 0, 0) =
			evsel->prev_raw_counts->aggr;
	पूर्ण
पूर्ण

अटल माप_प्रकार pkg_id_hash(स्थिर व्योम *__key, व्योम *ctx __maybe_unused)
अणु
	uपूर्णांक64_t *key = (uपूर्णांक64_t *) __key;

	वापस *key & 0xffffffff;
पूर्ण

अटल bool pkg_id_equal(स्थिर व्योम *__key1, स्थिर व्योम *__key2,
			 व्योम *ctx __maybe_unused)
अणु
	uपूर्णांक64_t *key1 = (uपूर्णांक64_t *) __key1;
	uपूर्णांक64_t *key2 = (uपूर्णांक64_t *) __key2;

	वापस *key1 == *key2;
पूर्ण

अटल पूर्णांक check_per_pkg(काष्ठा evsel *counter,
			 काष्ठा perf_counts_values *vals, पूर्णांक cpu, bool *skip)
अणु
	काष्ठा hashmap *mask = counter->per_pkg_mask;
	काष्ठा perf_cpu_map *cpus = evsel__cpus(counter);
	पूर्णांक s, d, ret = 0;
	uपूर्णांक64_t *key;

	*skip = false;

	अगर (!counter->per_pkg)
		वापस 0;

	अगर (perf_cpu_map__empty(cpus))
		वापस 0;

	अगर (!mask) अणु
		mask = hashmap__new(pkg_id_hash, pkg_id_equal, शून्य);
		अगर (!mask)
			वापस -ENOMEM;

		counter->per_pkg_mask = mask;
	पूर्ण

	/*
	 * we करो not consider an event that has not run as a good
	 * instance to mark a package as used (skip=1). Otherwise
	 * we may run पूर्णांकo a situation where the first CPU in a package
	 * is not running anything, yet the second is, and this function
	 * would mark the package as used after the first CPU and would
	 * not पढ़ो the values from the second CPU.
	 */
	अगर (!(vals->run && vals->ena))
		वापस 0;

	s = cpu_map__get_socket(cpus, cpu, शून्य).socket;
	अगर (s < 0)
		वापस -1;

	/*
	 * On multi-die प्रणाली, die_id > 0. On no-die प्रणाली, die_id = 0.
	 * We use hashmap(socket, die) to check the used socket+die pair.
	 */
	d = cpu_map__get_die(cpus, cpu, शून्य).die;
	अगर (d < 0)
		वापस -1;

	key = दो_स्मृति(माप(*key));
	अगर (!key)
		वापस -ENOMEM;

	*key = (uपूर्णांक64_t)d << 32 | s;
	अगर (hashmap__find(mask, (व्योम *)key, शून्य))
		*skip = true;
	अन्यथा
		ret = hashmap__add(mask, (व्योम *)key, (व्योम *)1);

	वापस ret;
पूर्ण

अटल पूर्णांक
process_counter_values(काष्ठा perf_stat_config *config, काष्ठा evsel *evsel,
		       पूर्णांक cpu, पूर्णांक thपढ़ो,
		       काष्ठा perf_counts_values *count)
अणु
	काष्ठा perf_counts_values *aggr = &evsel->counts->aggr;
	अटल काष्ठा perf_counts_values zero;
	bool skip = false;

	अगर (check_per_pkg(evsel, count, cpu, &skip)) अणु
		pr_err("failed to read per-pkg counter\n");
		वापस -1;
	पूर्ण

	अगर (skip)
		count = &zero;

	चयन (config->aggr_mode) अणु
	हाल AGGR_THREAD:
	हाल AGGR_CORE:
	हाल AGGR_DIE:
	हाल AGGR_SOCKET:
	हाल AGGR_NODE:
	हाल AGGR_NONE:
		अगर (!evsel->snapshot)
			evsel__compute_deltas(evsel, cpu, thपढ़ो, count);
		perf_counts_values__scale(count, config->scale, शून्य);
		अगर ((config->aggr_mode == AGGR_NONE) && (!evsel->percore)) अणु
			perf_stat__update_shaकरोw_stats(evsel, count->val,
						       cpu, &rt_stat);
		पूर्ण

		अगर (config->aggr_mode == AGGR_THREAD) अणु
			अगर (config->stats)
				perf_stat__update_shaकरोw_stats(evsel,
					count->val, 0, &config->stats[thपढ़ो]);
			अन्यथा
				perf_stat__update_shaकरोw_stats(evsel,
					count->val, 0, &rt_stat);
		पूर्ण
		अवरोध;
	हाल AGGR_GLOBAL:
		aggr->val += count->val;
		aggr->ena += count->ena;
		aggr->run += count->run;
	हाल AGGR_UNSET:
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_counter_maps(काष्ठा perf_stat_config *config,
				काष्ठा evsel *counter)
अणु
	पूर्णांक nthपढ़ोs = perf_thपढ़ो_map__nr(counter->core.thपढ़ोs);
	पूर्णांक ncpus = evsel__nr_cpus(counter);
	पूर्णांक cpu, thपढ़ो;

	अगर (counter->core.प्रणाली_wide)
		nthपढ़ोs = 1;

	क्रम (thपढ़ो = 0; thपढ़ो < nthपढ़ोs; thपढ़ो++) अणु
		क्रम (cpu = 0; cpu < ncpus; cpu++) अणु
			अगर (process_counter_values(config, counter, cpu, thपढ़ो,
						   perf_counts(counter->counts, cpu, thपढ़ो)))
				वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक perf_stat_process_counter(काष्ठा perf_stat_config *config,
			      काष्ठा evsel *counter)
अणु
	काष्ठा perf_counts_values *aggr = &counter->counts->aggr;
	काष्ठा perf_stat_evsel *ps = counter->stats;
	u64 *count = counter->counts->aggr.values;
	पूर्णांक i, ret;

	aggr->val = aggr->ena = aggr->run = 0;

	/*
	 * We calculate counter's data every पूर्णांकerval,
	 * and the display code shows ps->res_stats
	 * avg value. We need to zero the stats क्रम
	 * पूर्णांकerval mode, otherwise overall avg running
	 * averages will be shown क्रम each पूर्णांकerval.
	 */
	अगर (config->पूर्णांकerval || config->summary) अणु
		क्रम (i = 0; i < 3; i++)
			init_stats(&ps->res_stats[i]);
	पूर्ण

	अगर (counter->per_pkg)
		evsel__zero_per_pkg(counter);

	ret = process_counter_maps(config, counter);
	अगर (ret)
		वापस ret;

	अगर (config->aggr_mode != AGGR_GLOBAL)
		वापस 0;

	अगर (!counter->snapshot)
		evsel__compute_deltas(counter, -1, -1, aggr);
	perf_counts_values__scale(aggr, config->scale, &counter->counts->scaled);

	क्रम (i = 0; i < 3; i++)
		update_stats(&ps->res_stats[i], count[i]);

	अगर (verbose > 0) अणु
		ख_लिखो(config->output, "%s: %" PRIu64 " %" PRIu64 " %" PRIu64 "\n",
			evsel__name(counter), count[0], count[1], count[2]);
	पूर्ण

	/*
	 * Save the full runसमय - to allow normalization during prपूर्णांकout:
	 */
	perf_stat__update_shaकरोw_stats(counter, *count, 0, &rt_stat);

	वापस 0;
पूर्ण

पूर्णांक perf_event__process_stat_event(काष्ठा perf_session *session,
				   जोड़ perf_event *event)
अणु
	काष्ठा perf_counts_values count;
	काष्ठा perf_record_stat *st = &event->stat;
	काष्ठा evsel *counter;

	count.val = st->val;
	count.ena = st->ena;
	count.run = st->run;

	counter = evlist__id2evsel(session->evlist, st->id);
	अगर (!counter) अणु
		pr_err("Failed to resolve counter for stat event.\n");
		वापस -EINVAL;
	पूर्ण

	*perf_counts(counter->counts, st->cpu, st->thपढ़ो) = count;
	counter->supported = true;
	वापस 0;
पूर्ण

माप_प्रकार perf_event__ख_लिखो_stat(जोड़ perf_event *event, खाता *fp)
अणु
	काष्ठा perf_record_stat *st = (काष्ठा perf_record_stat *)event;
	माप_प्रकार ret;

	ret  = ख_लिखो(fp, "\n... id %" PRI_lu64 ", cpu %d, thread %d\n",
		       st->id, st->cpu, st->thपढ़ो);
	ret += ख_लिखो(fp, "... value %" PRI_lu64 ", enabled %" PRI_lu64 ", running %" PRI_lu64 "\n",
		       st->val, st->ena, st->run);

	वापस ret;
पूर्ण

माप_प्रकार perf_event__ख_लिखो_stat_round(जोड़ perf_event *event, खाता *fp)
अणु
	काष्ठा perf_record_stat_round *rd = (काष्ठा perf_record_stat_round *)event;
	माप_प्रकार ret;

	ret = ख_लिखो(fp, "\n... time %" PRI_lu64 ", type %s\n", rd->समय,
		      rd->type == PERF_STAT_ROUND_TYPE__FINAL ? "FINAL" : "INTERVAL");

	वापस ret;
पूर्ण

माप_प्रकार perf_event__ख_लिखो_stat_config(जोड़ perf_event *event, खाता *fp)
अणु
	काष्ठा perf_stat_config sc;
	माप_प्रकार ret;

	perf_event__पढ़ो_stat_config(&sc, &event->stat_config);

	ret  = ख_लिखो(fp, "\n");
	ret += ख_लिखो(fp, "... aggr_mode %d\n", sc.aggr_mode);
	ret += ख_लिखो(fp, "... scale     %d\n", sc.scale);
	ret += ख_लिखो(fp, "... interval  %u\n", sc.पूर्णांकerval);

	वापस ret;
पूर्ण

पूर्णांक create_perf_stat_counter(काष्ठा evsel *evsel,
			     काष्ठा perf_stat_config *config,
			     काष्ठा target *target,
			     पूर्णांक cpu)
अणु
	काष्ठा perf_event_attr *attr = &evsel->core.attr;
	काष्ठा evsel *leader = evsel->leader;

	attr->पढ़ो_क्रमmat = PERF_FORMAT_TOTAL_TIME_ENABLED |
			    PERF_FORMAT_TOTAL_TIME_RUNNING;

	/*
	 * The event is part of non trivial group, let's enable
	 * the group पढ़ो (क्रम leader) and ID retrieval क्रम all
	 * members.
	 */
	अगर (leader->core.nr_members > 1)
		attr->पढ़ो_क्रमmat |= PERF_FORMAT_ID|PERF_FORMAT_GROUP;

	attr->inherit = !config->no_inherit && list_empty(&evsel->bpf_counter_list);

	/*
	 * Some events get initialized with sample_(period/type) set,
	 * like tracepoपूर्णांकs. Clear it up क्रम counting.
	 */
	attr->sample_period = 0;

	अगर (config->identअगरier)
		attr->sample_type = PERF_SAMPLE_IDENTIFIER;

	अगर (config->all_user) अणु
		attr->exclude_kernel = 1;
		attr->exclude_user   = 0;
	पूर्ण

	अगर (config->all_kernel) अणु
		attr->exclude_kernel = 0;
		attr->exclude_user   = 1;
	पूर्ण

	/*
	 * Disabling all counters initially, they will be enabled
	 * either manually by us or by kernel via enable_on_exec
	 * set later.
	 */
	अगर (evsel__is_group_leader(evsel)) अणु
		attr->disabled = 1;

		/*
		 * In हाल of initial_delay we enable tracee
		 * events manually.
		 */
		अगर (target__none(target) && !config->initial_delay)
			attr->enable_on_exec = 1;
	पूर्ण

	अगर (target__has_cpu(target) && !target__has_per_thपढ़ो(target))
		वापस evsel__खोलो_per_cpu(evsel, evsel__cpus(evsel), cpu);

	वापस evsel__खोलो_per_thपढ़ो(evsel, evsel->core.thपढ़ोs);
पूर्ण
