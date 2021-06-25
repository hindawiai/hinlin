<शैली गुरु>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <linux/माला.स>
#समावेश <linux/समय64.h>
#समावेश <गणित.स>
#समावेश "color.h"
#समावेश "counts.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "stat.h"
#समावेश "top.h"
#समावेश "thread_map.h"
#समावेश "cpumap.h"
#समावेश "string2.h"
#समावेश <linux/प्रकार.स>
#समावेश "cgroup.h"
#समावेश <api/fs/fs.h>
#समावेश "util.h"
#समावेश "iostat.h"
#समावेश "pmu-hybrid.h"

#घोषणा CNTR_NOT_SUPPORTED	"<not supported>"
#घोषणा CNTR_NOT_COUNTED	"<not counted>"

अटल व्योम prपूर्णांक_running(काष्ठा perf_stat_config *config,
			  u64 run, u64 ena)
अणु
	अगर (config->csv_output) अणु
		ख_लिखो(config->output, "%s%" PRIu64 "%s%.2f",
					config->csv_sep,
					run,
					config->csv_sep,
					ena ? 100.0 * run / ena : 100.0);
	पूर्ण अन्यथा अगर (run != ena) अणु
		ख_लिखो(config->output, "  (%.2f%%)", 100.0 * run / ena);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_noise_pct(काष्ठा perf_stat_config *config,
			    द्विगुन total, द्विगुन avg)
अणु
	द्विगुन pct = rel_stddev_stats(total, avg);

	अगर (config->csv_output)
		ख_लिखो(config->output, "%s%.2f%%", config->csv_sep, pct);
	अन्यथा अगर (pct)
		ख_लिखो(config->output, "  ( +-%6.2f%% )", pct);
पूर्ण

अटल व्योम prपूर्णांक_noise(काष्ठा perf_stat_config *config,
			काष्ठा evsel *evsel, द्विगुन avg)
अणु
	काष्ठा perf_stat_evsel *ps;

	अगर (config->run_count == 1)
		वापस;

	ps = evsel->stats;
	prपूर्णांक_noise_pct(config, stddev_stats(&ps->res_stats[0]), avg);
पूर्ण

अटल व्योम prपूर्णांक_cgroup(काष्ठा perf_stat_config *config, काष्ठा evsel *evsel)
अणु
	अगर (nr_cgroups) अणु
		स्थिर अक्षर *cgrp_name = evsel->cgrp ? evsel->cgrp->name  : "";
		ख_लिखो(config->output, "%s%s", config->csv_sep, cgrp_name);
	पूर्ण
पूर्ण


अटल व्योम aggr_prपूर्णांकout(काष्ठा perf_stat_config *config,
			  काष्ठा evsel *evsel, काष्ठा aggr_cpu_id id, पूर्णांक nr)
अणु
	चयन (config->aggr_mode) अणु
	हाल AGGR_CORE:
		ख_लिखो(config->output, "S%d-D%d-C%*d%s%*d%s",
			id.socket,
			id.die,
			config->csv_output ? 0 : -8,
			id.core,
			config->csv_sep,
			config->csv_output ? 0 : 4,
			nr,
			config->csv_sep);
		अवरोध;
	हाल AGGR_DIE:
		ख_लिखो(config->output, "S%d-D%*d%s%*d%s",
			id.socket,
			config->csv_output ? 0 : -8,
			id.die,
			config->csv_sep,
			config->csv_output ? 0 : 4,
			nr,
			config->csv_sep);
		अवरोध;
	हाल AGGR_SOCKET:
		ख_लिखो(config->output, "S%*d%s%*d%s",
			config->csv_output ? 0 : -5,
			id.socket,
			config->csv_sep,
			config->csv_output ? 0 : 4,
			nr,
			config->csv_sep);
			अवरोध;
	हाल AGGR_NODE:
		ख_लिखो(config->output, "N%*d%s%*d%s",
			config->csv_output ? 0 : -5,
			id.node,
			config->csv_sep,
			config->csv_output ? 0 : 4,
			nr,
			config->csv_sep);
			अवरोध;
	हाल AGGR_NONE:
		अगर (evsel->percore && !config->percore_show_thपढ़ो) अणु
			ख_लिखो(config->output, "S%d-D%d-C%*d%s",
				id.socket,
				id.die,
				config->csv_output ? 0 : -3,
				id.core, config->csv_sep);
		पूर्ण अन्यथा अगर (id.core > -1) अणु
			ख_लिखो(config->output, "CPU%*d%s",
				config->csv_output ? 0 : -7,
				evsel__cpus(evsel)->map[id.core],
				config->csv_sep);
		पूर्ण
		अवरोध;
	हाल AGGR_THREAD:
		ख_लिखो(config->output, "%*s-%*d%s",
			config->csv_output ? 0 : 16,
			perf_thपढ़ो_map__comm(evsel->core.thपढ़ोs, id.thपढ़ो),
			config->csv_output ? 0 : -8,
			perf_thपढ़ो_map__pid(evsel->core.thपढ़ोs, id.thपढ़ो),
			config->csv_sep);
		अवरोध;
	हाल AGGR_GLOBAL:
	हाल AGGR_UNSET:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

काष्ठा outstate अणु
	खाता *fh;
	bool newline;
	स्थिर अक्षर *prefix;
	पूर्णांक  nfields;
	पूर्णांक  nr;
	काष्ठा aggr_cpu_id id;
	काष्ठा evsel *evsel;
पूर्ण;

#घोषणा METRIC_LEN  35

अटल व्योम new_line_std(काष्ठा perf_stat_config *config __maybe_unused,
			 व्योम *ctx)
अणु
	काष्ठा outstate *os = ctx;

	os->newline = true;
पूर्ण

अटल व्योम करो_new_line_std(काष्ठा perf_stat_config *config,
			    काष्ठा outstate *os)
अणु
	ख_अक्षर_दो('\n', os->fh);
	ख_माला_दो(os->prefix, os->fh);
	aggr_prपूर्णांकout(config, os->evsel, os->id, os->nr);
	अगर (config->aggr_mode == AGGR_NONE)
		ख_लिखो(os->fh, "        ");
	ख_लिखो(os->fh, "                                                 ");
पूर्ण

अटल व्योम prपूर्णांक_metric_std(काष्ठा perf_stat_config *config,
			     व्योम *ctx, स्थिर अक्षर *color, स्थिर अक्षर *fmt,
			     स्थिर अक्षर *unit, द्विगुन val)
अणु
	काष्ठा outstate *os = ctx;
	खाता *out = os->fh;
	पूर्णांक n;
	bool newline = os->newline;

	os->newline = false;

	अगर (unit == शून्य || fmt == शून्य) अणु
		ख_लिखो(out, "%-*s", METRIC_LEN, "");
		वापस;
	पूर्ण

	अगर (newline)
		करो_new_line_std(config, os);

	n = ख_लिखो(out, " # ");
	अगर (color)
		n += color_ख_लिखो(out, color, fmt, val);
	अन्यथा
		n += ख_लिखो(out, fmt, val);
	ख_लिखो(out, " %-*s", METRIC_LEN - n - 1, unit);
पूर्ण

अटल व्योम new_line_csv(काष्ठा perf_stat_config *config, व्योम *ctx)
अणु
	काष्ठा outstate *os = ctx;
	पूर्णांक i;

	ख_अक्षर_दो('\n', os->fh);
	अगर (os->prefix)
		ख_लिखो(os->fh, "%s%s", os->prefix, config->csv_sep);
	aggr_prपूर्णांकout(config, os->evsel, os->id, os->nr);
	क्रम (i = 0; i < os->nfields; i++)
		ख_माला_दो(config->csv_sep, os->fh);
पूर्ण

अटल व्योम prपूर्णांक_metric_csv(काष्ठा perf_stat_config *config __maybe_unused,
			     व्योम *ctx,
			     स्थिर अक्षर *color __maybe_unused,
			     स्थिर अक्षर *fmt, स्थिर अक्षर *unit, द्विगुन val)
अणु
	काष्ठा outstate *os = ctx;
	खाता *out = os->fh;
	अक्षर buf[64], *vals, *ends;

	अगर (unit == शून्य || fmt == शून्य) अणु
		ख_लिखो(out, "%s%s", config->csv_sep, config->csv_sep);
		वापस;
	पूर्ण
	snम_लिखो(buf, माप(buf), fmt, val);
	ends = vals = skip_spaces(buf);
	जबतक (है_अंक(*ends) || *ends == '.')
		ends++;
	*ends = 0;
	ख_लिखो(out, "%s%s%s%s", config->csv_sep, vals, config->csv_sep, skip_spaces(unit));
पूर्ण

/* Filter out some columns that करोn't work well in metrics only mode */

अटल bool valid_only_metric(स्थिर अक्षर *unit)
अणु
	अगर (!unit)
		वापस false;
	अगर (म_माला(unit, "/sec") ||
	    म_माला(unit, "CPUs utilized"))
		वापस false;
	वापस true;
पूर्ण

अटल स्थिर अक्षर *fixunit(अक्षर *buf, काष्ठा evsel *evsel,
			   स्थिर अक्षर *unit)
अणु
	अगर (!म_भेदन(unit, "of all", 6)) अणु
		snम_लिखो(buf, 1024, "%s %s", evsel__name(evsel),
			 unit);
		वापस buf;
	पूर्ण
	वापस unit;
पूर्ण

अटल व्योम prपूर्णांक_metric_only(काष्ठा perf_stat_config *config,
			      व्योम *ctx, स्थिर अक्षर *color, स्थिर अक्षर *fmt,
			      स्थिर अक्षर *unit, द्विगुन val)
अणु
	काष्ठा outstate *os = ctx;
	खाता *out = os->fh;
	अक्षर buf[1024], str[1024];
	अचिन्हित mlen = config->metric_only_len;

	अगर (!valid_only_metric(unit))
		वापस;
	unit = fixunit(buf, os->evsel, unit);
	अगर (mlen < म_माप(unit))
		mlen = म_माप(unit) + 1;

	अगर (color)
		mlen += म_माप(color) + माप(PERF_COLOR_RESET) - 1;

	color_snम_लिखो(str, माप(str), color ?: "", fmt, val);
	ख_लिखो(out, "%*s ", mlen, str);
पूर्ण

अटल व्योम prपूर्णांक_metric_only_csv(काष्ठा perf_stat_config *config __maybe_unused,
				  व्योम *ctx, स्थिर अक्षर *color __maybe_unused,
				  स्थिर अक्षर *fmt,
				  स्थिर अक्षर *unit, द्विगुन val)
अणु
	काष्ठा outstate *os = ctx;
	खाता *out = os->fh;
	अक्षर buf[64], *vals, *ends;
	अक्षर tbuf[1024];

	अगर (!valid_only_metric(unit))
		वापस;
	unit = fixunit(tbuf, os->evsel, unit);
	snम_लिखो(buf, माप buf, fmt, val);
	ends = vals = skip_spaces(buf);
	जबतक (है_अंक(*ends) || *ends == '.')
		ends++;
	*ends = 0;
	ख_लिखो(out, "%s%s", vals, config->csv_sep);
पूर्ण

अटल व्योम new_line_metric(काष्ठा perf_stat_config *config __maybe_unused,
			    व्योम *ctx __maybe_unused)
अणु
पूर्ण

अटल व्योम prपूर्णांक_metric_header(काष्ठा perf_stat_config *config,
				व्योम *ctx, स्थिर अक्षर *color __maybe_unused,
				स्थिर अक्षर *fmt __maybe_unused,
				स्थिर अक्षर *unit, द्विगुन val __maybe_unused)
अणु
	काष्ठा outstate *os = ctx;
	अक्षर tbuf[1024];

	/* In हाल of iostat, prपूर्णांक metric header क्रम first root port only */
	अगर (config->iostat_run &&
	    os->evsel->priv != os->evsel->evlist->selected->priv)
		वापस;

	अगर (!valid_only_metric(unit))
		वापस;
	unit = fixunit(tbuf, os->evsel, unit);
	अगर (config->csv_output)
		ख_लिखो(os->fh, "%s%s", unit, config->csv_sep);
	अन्यथा
		ख_लिखो(os->fh, "%*s ", config->metric_only_len, unit);
पूर्ण

अटल पूर्णांक first_shaकरोw_cpu(काष्ठा perf_stat_config *config,
			    काष्ठा evsel *evsel, काष्ठा aggr_cpu_id id)
अणु
	काष्ठा evlist *evlist = evsel->evlist;
	पूर्णांक i;

	अगर (config->aggr_mode == AGGR_NONE)
		वापस id.core;

	अगर (!config->aggr_get_id)
		वापस 0;

	क्रम (i = 0; i < evsel__nr_cpus(evsel); i++) अणु
		पूर्णांक cpu2 = evsel__cpus(evsel)->map[i];

		अगर (cpu_map__compare_aggr_cpu_id(
					config->aggr_get_id(config, evlist->core.cpus, cpu2),
					id)) अणु
			वापस cpu2;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम असल_prपूर्णांकout(काष्ठा perf_stat_config *config,
			 काष्ठा aggr_cpu_id id, पूर्णांक nr, काष्ठा evsel *evsel, द्विगुन avg)
अणु
	खाता *output = config->output;
	द्विगुन sc =  evsel->scale;
	स्थिर अक्षर *fmt;

	अगर (config->csv_output) अणु
		fmt = न्यूनमान(sc) != sc ?  "%.2f%s" : "%.0f%s";
	पूर्ण अन्यथा अणु
		अगर (config->big_num)
			fmt = न्यूनमान(sc) != sc ? "%'18.2f%s" : "%'18.0f%s";
		अन्यथा
			fmt = न्यूनमान(sc) != sc ? "%18.2f%s" : "%18.0f%s";
	पूर्ण

	aggr_prपूर्णांकout(config, evsel, id, nr);

	ख_लिखो(output, fmt, avg, config->csv_sep);

	अगर (evsel->unit)
		ख_लिखो(output, "%-*s%s",
			config->csv_output ? 0 : config->unit_width,
			evsel->unit, config->csv_sep);

	ख_लिखो(output, "%-*s", config->csv_output ? 0 : 25, evsel__name(evsel));

	prपूर्णांक_cgroup(config, evsel);
पूर्ण

अटल bool is_mixed_hw_group(काष्ठा evsel *counter)
अणु
	काष्ठा evlist *evlist = counter->evlist;
	u32 pmu_type = counter->core.attr.type;
	काष्ठा evsel *pos;

	अगर (counter->core.nr_members < 2)
		वापस false;

	evlist__क्रम_each_entry(evlist, pos) अणु
		/* software events can be part of any hardware group */
		अगर (pos->core.attr.type == PERF_TYPE_SOFTWARE)
			जारी;
		अगर (pmu_type == PERF_TYPE_SOFTWARE) अणु
			pmu_type = pos->core.attr.type;
			जारी;
		पूर्ण
		अगर (pmu_type != pos->core.attr.type)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम prपूर्णांकout(काष्ठा perf_stat_config *config, काष्ठा aggr_cpu_id id, पूर्णांक nr,
		     काष्ठा evsel *counter, द्विगुन uval,
		     अक्षर *prefix, u64 run, u64 ena, द्विगुन noise,
		     काष्ठा runसमय_stat *st)
अणु
	काष्ठा perf_stat_output_ctx out;
	काष्ठा outstate os = अणु
		.fh = config->output,
		.prefix = prefix ? prefix : "",
		.id = id,
		.nr = nr,
		.evsel = counter,
	पूर्ण;
	prपूर्णांक_metric_t pm = prपूर्णांक_metric_std;
	new_line_t nl;

	अगर (config->metric_only) अणु
		nl = new_line_metric;
		अगर (config->csv_output)
			pm = prपूर्णांक_metric_only_csv;
		अन्यथा
			pm = prपूर्णांक_metric_only;
	पूर्ण अन्यथा
		nl = new_line_std;

	अगर (config->csv_output && !config->metric_only) अणु
		अटल पूर्णांक aggr_fields[] = अणु
			[AGGR_GLOBAL] = 0,
			[AGGR_THREAD] = 1,
			[AGGR_NONE] = 1,
			[AGGR_SOCKET] = 2,
			[AGGR_DIE] = 2,
			[AGGR_CORE] = 2,
		पूर्ण;

		pm = prपूर्णांक_metric_csv;
		nl = new_line_csv;
		os.nfields = 3;
		os.nfields += aggr_fields[config->aggr_mode];
		अगर (counter->cgrp)
			os.nfields++;
	पूर्ण

	अगर (!config->no_csv_summary && config->csv_output &&
	    config->summary && !config->पूर्णांकerval) अणु
		ख_लिखो(config->output, "%16s%s", "summary", config->csv_sep);
	पूर्ण

	अगर (run == 0 || ena == 0 || counter->counts->scaled == -1) अणु
		अगर (config->metric_only) अणु
			pm(config, &os, शून्य, "", "", 0);
			वापस;
		पूर्ण
		aggr_prपूर्णांकout(config, counter, id, nr);

		ख_लिखो(config->output, "%*s%s",
			config->csv_output ? 0 : 18,
			counter->supported ? CNTR_NOT_COUNTED : CNTR_NOT_SUPPORTED,
			config->csv_sep);

		अगर (counter->supported) अणु
			config->prपूर्णांक_मुक्त_counters_hपूर्णांक = 1;
			अगर (is_mixed_hw_group(counter))
				config->prपूर्णांक_mixed_hw_group_error = 1;
		पूर्ण

		ख_लिखो(config->output, "%-*s%s",
			config->csv_output ? 0 : config->unit_width,
			counter->unit, config->csv_sep);

		ख_लिखो(config->output, "%*s",
			config->csv_output ? 0 : -25, evsel__name(counter));

		prपूर्णांक_cgroup(config, counter);

		अगर (!config->csv_output)
			pm(config, &os, शून्य, शून्य, "", 0);
		prपूर्णांक_noise(config, counter, noise);
		prपूर्णांक_running(config, run, ena);
		अगर (config->csv_output)
			pm(config, &os, शून्य, शून्य, "", 0);
		वापस;
	पूर्ण

	अगर (!config->metric_only)
		असल_prपूर्णांकout(config, id, nr, counter, uval);

	out.prपूर्णांक_metric = pm;
	out.new_line = nl;
	out.ctx = &os;
	out.क्रमce_header = false;

	अगर (config->csv_output && !config->metric_only) अणु
		prपूर्णांक_noise(config, counter, noise);
		prपूर्णांक_running(config, run, ena);
	पूर्ण

	perf_stat__prपूर्णांक_shaकरोw_stats(config, counter, uval,
				first_shaकरोw_cpu(config, counter, id),
				&out, &config->metric_events, st);
	अगर (!config->csv_output && !config->metric_only) अणु
		prपूर्णांक_noise(config, counter, noise);
		prपूर्णांक_running(config, run, ena);
	पूर्ण
पूर्ण

अटल व्योम aggr_update_shaकरोw(काष्ठा perf_stat_config *config,
			       काष्ठा evlist *evlist)
अणु
	पूर्णांक cpu, s;
	काष्ठा aggr_cpu_id s2, id;
	u64 val;
	काष्ठा evsel *counter;

	क्रम (s = 0; s < config->aggr_map->nr; s++) अणु
		id = config->aggr_map->map[s];
		evlist__क्रम_each_entry(evlist, counter) अणु
			val = 0;
			क्रम (cpu = 0; cpu < evsel__nr_cpus(counter); cpu++) अणु
				s2 = config->aggr_get_id(config, evlist->core.cpus, cpu);
				अगर (!cpu_map__compare_aggr_cpu_id(s2, id))
					जारी;
				val += perf_counts(counter->counts, cpu, 0)->val;
			पूर्ण
			perf_stat__update_shaकरोw_stats(counter, val,
					first_shaकरोw_cpu(config, counter, id),
					&rt_stat);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम uniquअगरy_event_name(काष्ठा evsel *counter)
अणु
	अक्षर *new_name;
	अक्षर *config;
	पूर्णांक ret = 0;

	अगर (counter->uniquअगरied_name || counter->use_config_name ||
	    !counter->pmu_name || !म_भेदन(counter->name, counter->pmu_name,
					   म_माप(counter->pmu_name)))
		वापस;

	config = म_अक्षर(counter->name, '/');
	अगर (config) अणु
		अगर (aप्र_लिखो(&new_name,
			     "%s%s", counter->pmu_name, config) > 0) अणु
			मुक्त(counter->name);
			counter->name = new_name;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (perf_pmu__has_hybrid()) अणु
			ret = aप्र_लिखो(&new_name, "%s/%s/",
				       counter->pmu_name, counter->name);
		पूर्ण अन्यथा अणु
			ret = aप्र_लिखो(&new_name, "%s [%s]",
				       counter->name, counter->pmu_name);
		पूर्ण

		अगर (ret) अणु
			मुक्त(counter->name);
			counter->name = new_name;
		पूर्ण
	पूर्ण

	counter->uniquअगरied_name = true;
पूर्ण

अटल व्योम collect_all_aliases(काष्ठा perf_stat_config *config, काष्ठा evsel *counter,
			    व्योम (*cb)(काष्ठा perf_stat_config *config, काष्ठा evsel *counter, व्योम *data,
				       bool first),
			    व्योम *data)
अणु
	काष्ठा evlist *evlist = counter->evlist;
	काष्ठा evsel *alias;

	alias = list_prepare_entry(counter, &(evlist->core.entries), core.node);
	list_क्रम_each_entry_जारी (alias, &evlist->core.entries, core.node) अणु
		अगर (म_भेद(evsel__name(alias), evsel__name(counter)) ||
		    alias->scale != counter->scale ||
		    alias->cgrp != counter->cgrp ||
		    म_भेद(alias->unit, counter->unit) ||
		    evsel__is_घड़ी(alias) != evsel__is_घड़ी(counter) ||
		    !म_भेद(alias->pmu_name, counter->pmu_name))
			अवरोध;
		alias->merged_stat = true;
		cb(config, alias, data, false);
	पूर्ण
पूर्ण

अटल bool collect_data(काष्ठा perf_stat_config *config, काष्ठा evsel *counter,
			    व्योम (*cb)(काष्ठा perf_stat_config *config, काष्ठा evsel *counter, व्योम *data,
				       bool first),
			    व्योम *data)
अणु
	अगर (counter->merged_stat)
		वापस false;
	cb(config, counter, data, true);
	अगर (config->no_merge)
		uniquअगरy_event_name(counter);
	अन्यथा अगर (counter->स्वतः_merge_stats)
		collect_all_aliases(config, counter, cb, data);
	वापस true;
पूर्ण

काष्ठा aggr_data अणु
	u64 ena, run, val;
	काष्ठा aggr_cpu_id id;
	पूर्णांक nr;
	पूर्णांक cpu;
पूर्ण;

अटल व्योम aggr_cb(काष्ठा perf_stat_config *config,
		    काष्ठा evsel *counter, व्योम *data, bool first)
अणु
	काष्ठा aggr_data *ad = data;
	पूर्णांक cpu;
	काष्ठा aggr_cpu_id s2;

	क्रम (cpu = 0; cpu < evsel__nr_cpus(counter); cpu++) अणु
		काष्ठा perf_counts_values *counts;

		s2 = config->aggr_get_id(config, evsel__cpus(counter), cpu);
		अगर (!cpu_map__compare_aggr_cpu_id(s2, ad->id))
			जारी;
		अगर (first)
			ad->nr++;
		counts = perf_counts(counter->counts, cpu, 0);
		/*
		 * When any result is bad, make them all to give
		 * consistent output in पूर्णांकerval mode.
		 */
		अगर (counts->ena == 0 || counts->run == 0 ||
		    counter->counts->scaled == -1) अणु
			ad->ena = 0;
			ad->run = 0;
			अवरोध;
		पूर्ण
		ad->val += counts->val;
		ad->ena += counts->ena;
		ad->run += counts->run;
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_counter_aggrdata(काष्ठा perf_stat_config *config,
				   काष्ठा evsel *counter, पूर्णांक s,
				   अक्षर *prefix, bool metric_only,
				   bool *first, पूर्णांक cpu)
अणु
	काष्ठा aggr_data ad;
	खाता *output = config->output;
	u64 ena, run, val;
	पूर्णांक nr;
	काष्ठा aggr_cpu_id id;
	द्विगुन uval;

	ad.id = id = config->aggr_map->map[s];
	ad.val = ad.ena = ad.run = 0;
	ad.nr = 0;
	अगर (!collect_data(config, counter, aggr_cb, &ad))
		वापस;

	अगर (perf_pmu__has_hybrid() && ad.ena == 0)
		वापस;

	nr = ad.nr;
	ena = ad.ena;
	run = ad.run;
	val = ad.val;
	अगर (*first && metric_only) अणु
		*first = false;
		aggr_prपूर्णांकout(config, counter, id, nr);
	पूर्ण
	अगर (prefix && !metric_only)
		ख_लिखो(output, "%s", prefix);

	uval = val * counter->scale;
	अगर (cpu != -1) अणु
		id = cpu_map__empty_aggr_cpu_id();
		id.core = cpu;
	पूर्ण
	prपूर्णांकout(config, id, nr, counter, uval,
		 prefix, run, ena, 1.0, &rt_stat);
	अगर (!metric_only)
		ख_अक्षर_दो('\n', output);
पूर्ण

अटल व्योम prपूर्णांक_aggr(काष्ठा perf_stat_config *config,
		       काष्ठा evlist *evlist,
		       अक्षर *prefix)
अणु
	bool metric_only = config->metric_only;
	खाता *output = config->output;
	काष्ठा evsel *counter;
	पूर्णांक s;
	bool first;

	अगर (!config->aggr_map || !config->aggr_get_id)
		वापस;

	aggr_update_shaकरोw(config, evlist);

	/*
	 * With metric_only everything is on a single line.
	 * Without each counter has its own line.
	 */
	क्रम (s = 0; s < config->aggr_map->nr; s++) अणु
		अगर (prefix && metric_only)
			ख_लिखो(output, "%s", prefix);

		first = true;
		evlist__क्रम_each_entry(evlist, counter) अणु
			prपूर्णांक_counter_aggrdata(config, counter, s,
					       prefix, metric_only,
					       &first, -1);
		पूर्ण
		अगर (metric_only)
			ख_अक्षर_दो('\n', output);
	पूर्ण
पूर्ण

अटल पूर्णांक cmp_val(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	वापस ((काष्ठा perf_aggr_thपढ़ो_value *)b)->val -
		((काष्ठा perf_aggr_thपढ़ो_value *)a)->val;
पूर्ण

अटल काष्ठा perf_aggr_thपढ़ो_value *sort_aggr_thपढ़ो(
					काष्ठा evsel *counter,
					पूर्णांक nthपढ़ोs, पूर्णांक ncpus,
					पूर्णांक *ret,
					काष्ठा target *_target)
अणु
	पूर्णांक cpu, thपढ़ो, i = 0;
	द्विगुन uval;
	काष्ठा perf_aggr_thपढ़ो_value *buf;

	buf = सुस्मृति(nthपढ़ोs, माप(काष्ठा perf_aggr_thपढ़ो_value));
	अगर (!buf)
		वापस शून्य;

	क्रम (thपढ़ो = 0; thपढ़ो < nthपढ़ोs; thपढ़ो++) अणु
		u64 ena = 0, run = 0, val = 0;

		क्रम (cpu = 0; cpu < ncpus; cpu++) अणु
			val += perf_counts(counter->counts, cpu, thपढ़ो)->val;
			ena += perf_counts(counter->counts, cpu, thपढ़ो)->ena;
			run += perf_counts(counter->counts, cpu, thपढ़ो)->run;
		पूर्ण

		uval = val * counter->scale;

		/*
		 * Skip value 0 when enabling --per-thपढ़ो globally,
		 * otherwise too many 0 output.
		 */
		अगर (uval == 0.0 && target__has_per_thपढ़ो(_target))
			जारी;

		buf[i].counter = counter;
		buf[i].id = cpu_map__empty_aggr_cpu_id();
		buf[i].id.thपढ़ो = thपढ़ो;
		buf[i].uval = uval;
		buf[i].val = val;
		buf[i].run = run;
		buf[i].ena = ena;
		i++;
	पूर्ण

	क्विक(buf, i, माप(काष्ठा perf_aggr_thपढ़ो_value), cmp_val);

	अगर (ret)
		*ret = i;

	वापस buf;
पूर्ण

अटल व्योम prपूर्णांक_aggr_thपढ़ो(काष्ठा perf_stat_config *config,
			      काष्ठा target *_target,
			      काष्ठा evsel *counter, अक्षर *prefix)
अणु
	खाता *output = config->output;
	पूर्णांक nthपढ़ोs = perf_thपढ़ो_map__nr(counter->core.thपढ़ोs);
	पूर्णांक ncpus = perf_cpu_map__nr(counter->core.cpus);
	पूर्णांक thपढ़ो, sorted_thपढ़ोs;
	काष्ठा aggr_cpu_id id;
	काष्ठा perf_aggr_thपढ़ो_value *buf;

	buf = sort_aggr_thपढ़ो(counter, nthपढ़ोs, ncpus, &sorted_thपढ़ोs, _target);
	अगर (!buf) अणु
		लिखो_त्रुटि("cannot sort aggr thread");
		वापस;
	पूर्ण

	क्रम (thपढ़ो = 0; thपढ़ो < sorted_thपढ़ोs; thपढ़ो++) अणु
		अगर (prefix)
			ख_लिखो(output, "%s", prefix);

		id = buf[thपढ़ो].id;
		अगर (config->stats)
			prपूर्णांकout(config, id, 0, buf[thपढ़ो].counter, buf[thपढ़ो].uval,
				 prefix, buf[thपढ़ो].run, buf[thपढ़ो].ena, 1.0,
				 &config->stats[id.thपढ़ो]);
		अन्यथा
			prपूर्णांकout(config, id, 0, buf[thपढ़ो].counter, buf[thपढ़ो].uval,
				 prefix, buf[thपढ़ो].run, buf[thपढ़ो].ena, 1.0,
				 &rt_stat);
		ख_अक्षर_दो('\n', output);
	पूर्ण

	मुक्त(buf);
पूर्ण

काष्ठा caggr_data अणु
	द्विगुन avg, avg_enabled, avg_running;
पूर्ण;

अटल व्योम counter_aggr_cb(काष्ठा perf_stat_config *config __maybe_unused,
			    काष्ठा evsel *counter, व्योम *data,
			    bool first __maybe_unused)
अणु
	काष्ठा caggr_data *cd = data;
	काष्ठा perf_stat_evsel *ps = counter->stats;

	cd->avg += avg_stats(&ps->res_stats[0]);
	cd->avg_enabled += avg_stats(&ps->res_stats[1]);
	cd->avg_running += avg_stats(&ps->res_stats[2]);
पूर्ण

/*
 * Prपूर्णांक out the results of a single counter:
 * aggregated counts in प्रणाली-wide mode
 */
अटल व्योम prपूर्णांक_counter_aggr(काष्ठा perf_stat_config *config,
			       काष्ठा evsel *counter, अक्षर *prefix)
अणु
	bool metric_only = config->metric_only;
	खाता *output = config->output;
	द्विगुन uval;
	काष्ठा caggr_data cd = अणु .avg = 0.0 पूर्ण;

	अगर (!collect_data(config, counter, counter_aggr_cb, &cd))
		वापस;

	अगर (prefix && !metric_only)
		ख_लिखो(output, "%s", prefix);

	uval = cd.avg * counter->scale;
	prपूर्णांकout(config, cpu_map__empty_aggr_cpu_id(), 0, counter, uval, prefix, cd.avg_running,
		 cd.avg_enabled, cd.avg, &rt_stat);
	अगर (!metric_only)
		ख_लिखो(output, "\n");
पूर्ण

अटल व्योम counter_cb(काष्ठा perf_stat_config *config __maybe_unused,
		       काष्ठा evsel *counter, व्योम *data,
		       bool first __maybe_unused)
अणु
	काष्ठा aggr_data *ad = data;

	ad->val += perf_counts(counter->counts, ad->cpu, 0)->val;
	ad->ena += perf_counts(counter->counts, ad->cpu, 0)->ena;
	ad->run += perf_counts(counter->counts, ad->cpu, 0)->run;
पूर्ण

/*
 * Prपूर्णांक out the results of a single counter:
 * करोes not use aggregated count in प्रणाली-wide
 */
अटल व्योम prपूर्णांक_counter(काष्ठा perf_stat_config *config,
			  काष्ठा evsel *counter, अक्षर *prefix)
अणु
	खाता *output = config->output;
	u64 ena, run, val;
	द्विगुन uval;
	पूर्णांक cpu;
	काष्ठा aggr_cpu_id id;

	क्रम (cpu = 0; cpu < evsel__nr_cpus(counter); cpu++) अणु
		काष्ठा aggr_data ad = अणु .cpu = cpu पूर्ण;

		अगर (!collect_data(config, counter, counter_cb, &ad))
			वापस;
		val = ad.val;
		ena = ad.ena;
		run = ad.run;

		अगर (prefix)
			ख_लिखो(output, "%s", prefix);

		uval = val * counter->scale;
		id = cpu_map__empty_aggr_cpu_id();
		id.core = cpu;
		prपूर्णांकout(config, id, 0, counter, uval, prefix,
			 run, ena, 1.0, &rt_stat);

		ख_अक्षर_दो('\n', output);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_no_aggr_metric(काष्ठा perf_stat_config *config,
				 काष्ठा evlist *evlist,
				 अक्षर *prefix)
अणु
	पूर्णांक cpu;
	पूर्णांक nrcpus = 0;
	काष्ठा evsel *counter;
	u64 ena, run, val;
	द्विगुन uval;
	काष्ठा aggr_cpu_id id;

	nrcpus = evlist->core.cpus->nr;
	क्रम (cpu = 0; cpu < nrcpus; cpu++) अणु
		bool first = true;

		अगर (prefix)
			ख_माला_दो(prefix, config->output);
		evlist__क्रम_each_entry(evlist, counter) अणु
			id = cpu_map__empty_aggr_cpu_id();
			id.core = cpu;
			अगर (first) अणु
				aggr_prपूर्णांकout(config, counter, id, 0);
				first = false;
			पूर्ण
			val = perf_counts(counter->counts, cpu, 0)->val;
			ena = perf_counts(counter->counts, cpu, 0)->ena;
			run = perf_counts(counter->counts, cpu, 0)->run;

			uval = val * counter->scale;
			prपूर्णांकout(config, id, 0, counter, uval, prefix,
				 run, ena, 1.0, &rt_stat);
		पूर्ण
		ख_अक्षर_दो('\n', config->output);
	पूर्ण
पूर्ण

अटल पूर्णांक aggr_header_lens[] = अणु
	[AGGR_CORE] = 24,
	[AGGR_DIE] = 18,
	[AGGR_SOCKET] = 12,
	[AGGR_NONE] = 6,
	[AGGR_THREAD] = 24,
	[AGGR_GLOBAL] = 0,
पूर्ण;

अटल स्थिर अक्षर *aggr_header_csv[] = अणु
	[AGGR_CORE] 	= 	"core,cpus,",
	[AGGR_DIE] 	= 	"die,cpus",
	[AGGR_SOCKET] 	= 	"socket,cpus",
	[AGGR_NONE] 	= 	"cpu,",
	[AGGR_THREAD] 	= 	"comm-pid,",
	[AGGR_GLOBAL] 	=	""
पूर्ण;

अटल व्योम prपूर्णांक_metric_headers(काष्ठा perf_stat_config *config,
				 काष्ठा evlist *evlist,
				 स्थिर अक्षर *prefix, bool no_indent)
अणु
	काष्ठा perf_stat_output_ctx out;
	काष्ठा evsel *counter;
	काष्ठा outstate os = अणु
		.fh = config->output
	पूर्ण;

	अगर (prefix)
		ख_लिखो(config->output, "%s", prefix);

	अगर (!config->csv_output && !no_indent)
		ख_लिखो(config->output, "%*s",
			aggr_header_lens[config->aggr_mode], "");
	अगर (config->csv_output) अणु
		अगर (config->पूर्णांकerval)
			ख_माला_दो("time,", config->output);
		अगर (!config->iostat_run)
			ख_माला_दो(aggr_header_csv[config->aggr_mode], config->output);
	पूर्ण
	अगर (config->iostat_run)
		iostat_prपूर्णांक_header_prefix(config);

	/* Prपूर्णांक metrics headers only */
	evlist__क्रम_each_entry(evlist, counter) अणु
		os.evsel = counter;
		out.ctx = &os;
		out.prपूर्णांक_metric = prपूर्णांक_metric_header;
		out.new_line = new_line_metric;
		out.क्रमce_header = true;
		perf_stat__prपूर्णांक_shaकरोw_stats(config, counter, 0,
					      0,
					      &out,
					      &config->metric_events,
					      &rt_stat);
	पूर्ण
	ख_अक्षर_दो('\n', config->output);
पूर्ण

अटल व्योम prपूर्णांक_पूर्णांकerval(काष्ठा perf_stat_config *config,
			   काष्ठा evlist *evlist,
			   अक्षर *prefix, काष्ठा बारpec *ts)
अणु
	bool metric_only = config->metric_only;
	अचिन्हित पूर्णांक unit_width = config->unit_width;
	खाता *output = config->output;
	अटल पूर्णांक num_prपूर्णांक_पूर्णांकerval;

	अगर (config->पूर्णांकerval_clear)
		माला_दो(CONSOLE_CLEAR);

	अगर (!config->iostat_run)
		प्र_लिखो(prefix, "%6lu.%09lu%s", (अचिन्हित दीर्घ) ts->tv_sec, ts->tv_nsec, config->csv_sep);

	अगर ((num_prपूर्णांक_पूर्णांकerval == 0 && !config->csv_output) || config->पूर्णांकerval_clear) अणु
		चयन (config->aggr_mode) अणु
		हाल AGGR_NODE:
			ख_लिखो(output, "#           time node   cpus");
			अगर (!metric_only)
				ख_लिखो(output, "             counts %*s events\n", unit_width, "unit");
			अवरोध;
		हाल AGGR_SOCKET:
			ख_लिखो(output, "#           time socket cpus");
			अगर (!metric_only)
				ख_लिखो(output, "             counts %*s events\n", unit_width, "unit");
			अवरोध;
		हाल AGGR_DIE:
			ख_लिखो(output, "#           time die          cpus");
			अगर (!metric_only)
				ख_लिखो(output, "             counts %*s events\n", unit_width, "unit");
			अवरोध;
		हाल AGGR_CORE:
			ख_लिखो(output, "#           time core            cpus");
			अगर (!metric_only)
				ख_लिखो(output, "             counts %*s events\n", unit_width, "unit");
			अवरोध;
		हाल AGGR_NONE:
			ख_लिखो(output, "#           time CPU    ");
			अगर (!metric_only)
				ख_लिखो(output, "                counts %*s events\n", unit_width, "unit");
			अवरोध;
		हाल AGGR_THREAD:
			ख_लिखो(output, "#           time             comm-pid");
			अगर (!metric_only)
				ख_लिखो(output, "                  counts %*s events\n", unit_width, "unit");
			अवरोध;
		हाल AGGR_GLOBAL:
		शेष:
			अगर (!config->iostat_run) अणु
				ख_लिखो(output, "#           time");
				अगर (!metric_only)
					ख_लिखो(output, "             counts %*s events\n", unit_width, "unit");
			पूर्ण
		हाल AGGR_UNSET:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर ((num_prपूर्णांक_पूर्णांकerval == 0 || config->पूर्णांकerval_clear) && metric_only)
		prपूर्णांक_metric_headers(config, evlist, " ", true);
	अगर (++num_prपूर्णांक_पूर्णांकerval == 25)
		num_prपूर्णांक_पूर्णांकerval = 0;
पूर्ण

अटल व्योम prपूर्णांक_header(काष्ठा perf_stat_config *config,
			 काष्ठा target *_target,
			 पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	खाता *output = config->output;
	पूर्णांक i;

	ख_साफ(मानक_निकास);

	अगर (!config->csv_output) अणु
		ख_लिखो(output, "\n");
		ख_लिखो(output, " Performance counter stats for ");
		अगर (_target->bpf_str)
			ख_लिखो(output, "\'BPF program(s) %s", _target->bpf_str);
		अन्यथा अगर (_target->प्रणाली_wide)
			ख_लिखो(output, "\'system wide");
		अन्यथा अगर (_target->cpu_list)
			ख_लिखो(output, "\'CPU(s) %s", _target->cpu_list);
		अन्यथा अगर (!target__has_task(_target)) अणु
			ख_लिखो(output, "\'%s", argv ? argv[0] : "pipe");
			क्रम (i = 1; argv && (i < argc); i++)
				ख_लिखो(output, " %s", argv[i]);
		पूर्ण अन्यथा अगर (_target->pid)
			ख_लिखो(output, "process id \'%s", _target->pid);
		अन्यथा
			ख_लिखो(output, "thread id \'%s", _target->tid);

		ख_लिखो(output, "\'");
		अगर (config->run_count > 1)
			ख_लिखो(output, " (%d runs)", config->run_count);
		ख_लिखो(output, ":\n\n");
	पूर्ण
पूर्ण

अटल पूर्णांक get_precision(द्विगुन num)
अणु
	अगर (num > 1)
		वापस 0;

	वापस lround(उच्चमान(-log10(num)));
पूर्ण

अटल व्योम prपूर्णांक_table(काष्ठा perf_stat_config *config,
			खाता *output, पूर्णांक precision, द्विगुन avg)
अणु
	अक्षर पंचांगp[64];
	पूर्णांक idx, indent = 0;

	scnम_लिखो(पंचांगp, 64, " %17.*f", precision, avg);
	जबतक (पंचांगp[indent] == ' ')
		indent++;

	ख_लिखो(output, "%*s# Table of individual measurements:\n", indent, "");

	क्रम (idx = 0; idx < config->run_count; idx++) अणु
		द्विगुन run = (द्विगुन) config->wallसमय_run[idx] / NSEC_PER_SEC;
		पूर्णांक h, n = 1 + असल((पूर्णांक) (100.0 * (run - avg)/run) / 5);

		ख_लिखो(output, " %17.*f (%+.*f) ",
			precision, run, precision, run - avg);

		क्रम (h = 0; h < n; h++)
			ख_लिखो(output, "#");

		ख_लिखो(output, "\n");
	पूर्ण

	ख_लिखो(output, "\n%*s# Final result:\n", indent, "");
पूर्ण

अटल द्विगुन समयval2द्विगुन(काष्ठा समयval *t)
अणु
	वापस t->tv_sec + (द्विगुन) t->tv_usec/USEC_PER_SEC;
पूर्ण

अटल व्योम prपूर्णांक_footer(काष्ठा perf_stat_config *config)
अणु
	द्विगुन avg = avg_stats(config->wallसमय_nsecs_stats) / NSEC_PER_SEC;
	खाता *output = config->output;

	अगर (!config->null_run)
		ख_लिखो(output, "\n");

	अगर (config->run_count == 1) अणु
		ख_लिखो(output, " %17.9f seconds time elapsed", avg);

		अगर (config->ru_display) अणु
			द्विगुन ru_uसमय = समयval2द्विगुन(&config->ru_data.ru_uसमय);
			द्विगुन ru_sसमय = समयval2द्विगुन(&config->ru_data.ru_sसमय);

			ख_लिखो(output, "\n\n");
			ख_लिखो(output, " %17.9f seconds user\n", ru_uसमय);
			ख_लिखो(output, " %17.9f seconds sys\n", ru_sसमय);
		पूर्ण
	पूर्ण अन्यथा अणु
		द्विगुन sd = stddev_stats(config->wallसमय_nsecs_stats) / NSEC_PER_SEC;
		/*
		 * Display at most 2 more signअगरicant
		 * digits than the stddev inaccuracy.
		 */
		पूर्णांक precision = get_precision(sd) + 2;

		अगर (config->wallसमय_run_table)
			prपूर्णांक_table(config, output, precision, avg);

		ख_लिखो(output, " %17.*f +- %.*f seconds time elapsed",
			precision, avg, precision, sd);

		prपूर्णांक_noise_pct(config, sd, avg);
	पूर्ण
	ख_लिखो(output, "\n\n");

	अगर (config->prपूर्णांक_मुक्त_counters_hपूर्णांक && sysctl__nmi_watchकरोg_enabled())
		ख_लिखो(output,
"Some events weren't counted. Try disabling the NMI watchdog:\n"
"	echo 0 > /proc/sys/kernel/nmi_watchdog\n"
"	perf stat ...\n"
"	echo 1 > /proc/sys/kernel/nmi_watchdog\n");

	अगर (config->prपूर्णांक_mixed_hw_group_error)
		ख_लिखो(output,
			"The events in group usually have to be from "
			"the same PMU. Try reorganizing the group.\n");
पूर्ण

अटल व्योम prपूर्णांक_percore_thपढ़ो(काष्ठा perf_stat_config *config,
				 काष्ठा evsel *counter, अक्षर *prefix)
अणु
	पूर्णांक s;
	काष्ठा aggr_cpu_id s2, id;
	bool first = true;

	क्रम (पूर्णांक i = 0; i < evsel__nr_cpus(counter); i++) अणु
		s2 = config->aggr_get_id(config, evsel__cpus(counter), i);
		क्रम (s = 0; s < config->aggr_map->nr; s++) अणु
			id = config->aggr_map->map[s];
			अगर (cpu_map__compare_aggr_cpu_id(s2, id))
				अवरोध;
		पूर्ण

		prपूर्णांक_counter_aggrdata(config, counter, s,
				       prefix, false,
				       &first, i);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_percore(काष्ठा perf_stat_config *config,
			  काष्ठा evsel *counter, अक्षर *prefix)
अणु
	bool metric_only = config->metric_only;
	खाता *output = config->output;
	पूर्णांक s;
	bool first = true;

	अगर (!config->aggr_map || !config->aggr_get_id)
		वापस;

	अगर (config->percore_show_thपढ़ो)
		वापस prपूर्णांक_percore_thपढ़ो(config, counter, prefix);

	क्रम (s = 0; s < config->aggr_map->nr; s++) अणु
		अगर (prefix && metric_only)
			ख_लिखो(output, "%s", prefix);

		prपूर्णांक_counter_aggrdata(config, counter, s,
				       prefix, metric_only,
				       &first, -1);
	पूर्ण

	अगर (metric_only)
		ख_अक्षर_दो('\n', output);
पूर्ण

व्योम evlist__prपूर्णांक_counters(काष्ठा evlist *evlist, काष्ठा perf_stat_config *config,
			    काष्ठा target *_target, काष्ठा बारpec *ts, पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	bool metric_only = config->metric_only;
	पूर्णांक पूर्णांकerval = config->पूर्णांकerval;
	काष्ठा evsel *counter;
	अक्षर buf[64], *prefix = शून्य;

	अगर (config->iostat_run)
		evlist->selected = evlist__first(evlist);

	अगर (पूर्णांकerval)
		prपूर्णांक_पूर्णांकerval(config, evlist, prefix = buf, ts);
	अन्यथा
		prपूर्णांक_header(config, _target, argc, argv);

	अगर (metric_only) अणु
		अटल पूर्णांक num_prपूर्णांक_iv;

		अगर (num_prपूर्णांक_iv == 0 && !पूर्णांकerval)
			prपूर्णांक_metric_headers(config, evlist, prefix, false);
		अगर (num_prपूर्णांक_iv++ == 25)
			num_prपूर्णांक_iv = 0;
		अगर (config->aggr_mode == AGGR_GLOBAL && prefix && !config->iostat_run)
			ख_लिखो(config->output, "%s", prefix);
	पूर्ण

	चयन (config->aggr_mode) अणु
	हाल AGGR_CORE:
	हाल AGGR_DIE:
	हाल AGGR_SOCKET:
	हाल AGGR_NODE:
		prपूर्णांक_aggr(config, evlist, prefix);
		अवरोध;
	हाल AGGR_THREAD:
		evlist__क्रम_each_entry(evlist, counter) अणु
			prपूर्णांक_aggr_thपढ़ो(config, _target, counter, prefix);
		पूर्ण
		अवरोध;
	हाल AGGR_GLOBAL:
		अगर (config->iostat_run)
			iostat_prपूर्णांक_counters(evlist, config, ts, prefix = buf,
					      prपूर्णांक_counter_aggr);
		अन्यथा अणु
			evlist__क्रम_each_entry(evlist, counter) अणु
				prपूर्णांक_counter_aggr(config, counter, prefix);
			पूर्ण
			अगर (metric_only)
				ख_अक्षर_दो('\n', config->output);
		पूर्ण
		अवरोध;
	हाल AGGR_NONE:
		अगर (metric_only)
			prपूर्णांक_no_aggr_metric(config, evlist, prefix);
		अन्यथा अणु
			evlist__क्रम_each_entry(evlist, counter) अणु
				अगर (counter->percore)
					prपूर्णांक_percore(config, counter, prefix);
				अन्यथा
					prपूर्णांक_counter(config, counter, prefix);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल AGGR_UNSET:
	शेष:
		अवरोध;
	पूर्ण

	अगर (!पूर्णांकerval && !config->csv_output)
		prपूर्णांक_footer(config);

	ख_साफ(config->output);
पूर्ण
