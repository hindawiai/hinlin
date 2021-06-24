<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "debug.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "evsel_config.h"
#समावेश "parse-events.h"
#समावेश <त्रुटिसं.स>
#समावेश <सीमा.स>
#समावेश <मानककोष.स>
#समावेश <api/fs/fs.h>
#समावेश <subcmd/parse-options.h>
#समावेश <perf/cpumap.h>
#समावेश "cloexec.h"
#समावेश "util/perf_api_probe.h"
#समावेश "record.h"
#समावेश "../perf-sys.h"
#समावेश "topdown.h"
#समावेश "map_symbol.h"
#समावेश "mem-events.h"

/*
 * evsel__config_leader_sampling() uses special rules क्रम leader sampling.
 * However, अगर the leader is an AUX area event, then assume the event to sample
 * is the next event.
 */
अटल काष्ठा evsel *evsel__पढ़ो_sampler(काष्ठा evsel *evsel, काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *leader = evsel->leader;

	अगर (evsel__is_aux_event(leader) || arch_topकरोwn_sample_पढ़ो(leader) ||
	    is_mem_loads_aux_event(leader)) अणु
		evlist__क्रम_each_entry(evlist, evsel) अणु
			अगर (evsel->leader == leader && evsel != evsel->leader)
				वापस evsel;
		पूर्ण
	पूर्ण

	वापस leader;
पूर्ण

अटल u64 evsel__config_term_mask(काष्ठा evsel *evsel)
अणु
	काष्ठा evsel_config_term *term;
	काष्ठा list_head *config_terms = &evsel->config_terms;
	u64 term_types = 0;

	list_क्रम_each_entry(term, config_terms, list) अणु
		term_types |= 1 << term->type;
	पूर्ण
	वापस term_types;
पूर्ण

अटल व्योम evsel__config_leader_sampling(काष्ठा evsel *evsel, काष्ठा evlist *evlist)
अणु
	काष्ठा perf_event_attr *attr = &evsel->core.attr;
	काष्ठा evsel *leader = evsel->leader;
	काष्ठा evsel *पढ़ो_sampler;
	u64 term_types, freq_mask;

	अगर (!leader->sample_पढ़ो)
		वापस;

	पढ़ो_sampler = evsel__पढ़ो_sampler(evsel, evlist);

	अगर (evsel == पढ़ो_sampler)
		वापस;

	term_types = evsel__config_term_mask(evsel);
	/*
	 * Disable sampling क्रम all group members except those with explicit
	 * config terms or the leader. In the हाल of an AUX area event, the 2nd
	 * event in the group is the one that 'leads' the sampling.
	 */
	freq_mask = (1 << EVSEL__CONFIG_TERM_FREQ) | (1 << EVSEL__CONFIG_TERM_PERIOD);
	अगर ((term_types & freq_mask) == 0) अणु
		attr->freq           = 0;
		attr->sample_freq    = 0;
		attr->sample_period  = 0;
	पूर्ण
	अगर ((term_types & (1 << EVSEL__CONFIG_TERM_OVERWRITE)) == 0)
		attr->ग_लिखो_backward = 0;

	/*
	 * We करोn't get a sample क्रम slave events, we make them when delivering
	 * the group leader sample. Set the slave event to follow the master
	 * sample_type to ease up reporting.
	 * An AUX area event also has sample_type requirements, so also include
	 * the sample type bits from the leader's sample_type to cover that
	 * हाल.
	 */
	attr->sample_type = पढ़ो_sampler->core.attr.sample_type |
			    leader->core.attr.sample_type;
पूर्ण

व्योम evlist__config(काष्ठा evlist *evlist, काष्ठा record_opts *opts, काष्ठा callchain_param *callchain)
अणु
	काष्ठा evsel *evsel;
	bool use_sample_identअगरier = false;
	bool use_comm_exec;
	bool sample_id = opts->sample_id;

	/*
	 * Set the evsel leader links beक्रमe we configure attributes,
	 * since some might depend on this info.
	 */
	अगर (opts->group)
		evlist__set_leader(evlist);

	अगर (evlist->core.cpus->map[0] < 0)
		opts->no_inherit = true;

	use_comm_exec = perf_can_comm_exec();

	evlist__क्रम_each_entry(evlist, evsel) अणु
		evsel__config(evsel, opts, callchain);
		अगर (evsel->tracking && use_comm_exec)
			evsel->core.attr.comm_exec = 1;
	पूर्ण

	/* Configure leader sampling here now that the sample type is known */
	evlist__क्रम_each_entry(evlist, evsel)
		evsel__config_leader_sampling(evsel, evlist);

	अगर (opts->full_auxtrace) अणु
		/*
		 * Need to be able to synthesize and parse selected events with
		 * arbitrary sample types, which requires always being able to
		 * match the id.
		 */
		use_sample_identअगरier = perf_can_sample_identअगरier();
		sample_id = true;
	पूर्ण अन्यथा अगर (evlist->core.nr_entries > 1) अणु
		काष्ठा evsel *first = evlist__first(evlist);

		evlist__क्रम_each_entry(evlist, evsel) अणु
			अगर (evsel->core.attr.sample_type == first->core.attr.sample_type)
				जारी;
			use_sample_identअगरier = perf_can_sample_identअगरier();
			अवरोध;
		पूर्ण
		sample_id = true;
	पूर्ण

	अगर (sample_id) अणु
		evlist__क्रम_each_entry(evlist, evsel)
			evsel__set_sample_id(evsel, use_sample_identअगरier);
	पूर्ण

	evlist__set_id_pos(evlist);
पूर्ण

अटल पूर्णांक get_max_rate(अचिन्हित पूर्णांक *rate)
अणु
	वापस sysctl__पढ़ो_पूर्णांक("kernel/perf_event_max_sample_rate", (पूर्णांक *)rate);
पूर्ण

अटल पूर्णांक record_opts__config_freq(काष्ठा record_opts *opts)
अणु
	bool user_freq = opts->user_freq != अच_पूर्णांक_उच्च;
	bool user_पूर्णांकerval = opts->user_पूर्णांकerval != ULदीर्घ_उच्च;
	अचिन्हित पूर्णांक max_rate;

	अगर (user_पूर्णांकerval && user_freq) अणु
		pr_err("cannot set frequency and period at the same time\n");
		वापस -1;
	पूर्ण

	अगर (user_पूर्णांकerval)
		opts->शेष_पूर्णांकerval = opts->user_पूर्णांकerval;
	अगर (user_freq)
		opts->freq = opts->user_freq;

	/*
	 * User specअगरied count overrides शेष frequency.
	 */
	अगर (opts->शेष_पूर्णांकerval)
		opts->freq = 0;
	अन्यथा अगर (opts->freq) अणु
		opts->शेष_पूर्णांकerval = opts->freq;
	पूर्ण अन्यथा अणु
		pr_err("frequency and count are zero, aborting\n");
		वापस -1;
	पूर्ण

	अगर (get_max_rate(&max_rate))
		वापस 0;

	/*
	 * User specअगरied frequency is over current maximum.
	 */
	अगर (user_freq && (max_rate < opts->freq)) अणु
		अगर (opts->strict_freq) अणु
			pr_err("error: Maximum frequency rate (%'u Hz) exceeded.\n"
			       "       Please use -F freq option with a lower value or consider\n"
			       "       tweaking /proc/sys/kernel/perf_event_max_sample_rate.\n",
			       max_rate);
			वापस -1;
		पूर्ण अन्यथा अणु
			pr_warning("warning: Maximum frequency rate (%'u Hz) exceeded, throttling from %'u Hz to %'u Hz.\n"
				   "         The limit can be raised via /proc/sys/kernel/perf_event_max_sample_rate.\n"
				   "         The kernel will lower it when perf's interrupts take too long.\n"
				   "         Use --strict-freq to disable this throttling, refusing to record.\n",
				   max_rate, opts->freq, max_rate);

			opts->freq = max_rate;
		पूर्ण
	पूर्ण

	/*
	 * Default frequency is over current maximum.
	 */
	अगर (max_rate < opts->freq) अणु
		pr_warning("Lowering default frequency rate from %u to %u.\n"
			   "Please consider tweaking "
			   "/proc/sys/kernel/perf_event_max_sample_rate.\n",
			   opts->freq, max_rate);
		opts->freq = max_rate;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक record_opts__config(काष्ठा record_opts *opts)
अणु
	वापस record_opts__config_freq(opts);
पूर्ण

bool evlist__can_select_event(काष्ठा evlist *evlist, स्थिर अक्षर *str)
अणु
	काष्ठा evlist *temp_evlist;
	काष्ठा evsel *evsel;
	पूर्णांक err, fd, cpu;
	bool ret = false;
	pid_t pid = -1;

	temp_evlist = evlist__new();
	अगर (!temp_evlist)
		वापस false;

	err = parse_events(temp_evlist, str, शून्य);
	अगर (err)
		जाओ out_delete;

	evsel = evlist__last(temp_evlist);

	अगर (!evlist || perf_cpu_map__empty(evlist->core.cpus)) अणु
		काष्ठा perf_cpu_map *cpus = perf_cpu_map__new(शून्य);

		cpu =  cpus ? cpus->map[0] : 0;
		perf_cpu_map__put(cpus);
	पूर्ण अन्यथा अणु
		cpu = evlist->core.cpus->map[0];
	पूर्ण

	जबतक (1) अणु
		fd = sys_perf_event_खोलो(&evsel->core.attr, pid, cpu, -1,
					 perf_event_खोलो_cloexec_flag());
		अगर (fd < 0) अणु
			अगर (pid == -1 && त्रुटि_सं == EACCES) अणु
				pid = 0;
				जारी;
			पूर्ण
			जाओ out_delete;
		पूर्ण
		अवरोध;
	पूर्ण
	बंद(fd);
	ret = true;

out_delete:
	evlist__delete(temp_evlist);
	वापस ret;
पूर्ण

पूर्णांक record__parse_freq(स्थिर काष्ठा option *opt, स्थिर अक्षर *str, पूर्णांक unset __maybe_unused)
अणु
	अचिन्हित पूर्णांक freq;
	काष्ठा record_opts *opts = opt->value;

	अगर (!str)
		वापस -EINVAL;

	अगर (strहालcmp(str, "max") == 0) अणु
		अगर (get_max_rate(&freq)) अणु
			pr_err("couldn't read /proc/sys/kernel/perf_event_max_sample_rate\n");
			वापस -1;
		पूर्ण
		pr_info("info: Using a maximum frequency rate of %'d Hz\n", freq);
	पूर्ण अन्यथा अणु
		freq = म_से_प(str);
	पूर्ण

	opts->user_freq = freq;
	वापस 0;
पूर्ण
