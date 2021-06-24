<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/err.h>
#समावेश <linux/zभाग.स>
#समावेश <dirent.h>
#समावेश <त्रुटिसं.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <sys/param.h>
#समावेश "term.h"
#समावेश "build-id.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश <subcmd/pager.h>
#समावेश <subcmd/parse-options.h>
#समावेश "parse-events.h"
#समावेश <subcmd/exec-cmd.h>
#समावेश "string2.h"
#समावेश "strlist.h"
#समावेश "symbol.h"
#समावेश "header.h"
#समावेश "bpf-loader.h"
#समावेश "debug.h"
#समावेश <api/fs/tracing_path.h>
#समावेश <perf/cpumap.h>
#समावेश "parse-events-bison.h"
#घोषणा YY_EXTRA_TYPE व्योम*
#समावेश "parse-events-flex.h"
#समावेश "pmu.h"
#समावेश "thread_map.h"
#समावेश "probe-file.h"
#समावेश "asm/bug.h"
#समावेश "util/parse-branch-options.h"
#समावेश "metricgroup.h"
#समावेश "util/evsel_config.h"
#समावेश "util/event.h"
#समावेश "util/pfm.h"
#समावेश "util/parse-events-hybrid.h"
#समावेश "util/pmu-hybrid.h"
#समावेश "perf.h"

#घोषणा MAX_NAME_LEN 100

#अगर_घोषित PARSER_DEBUG
बाह्य पूर्णांक parse_events_debug;
#पूर्ण_अगर
पूर्णांक parse_events_parse(व्योम *parse_state, व्योम *scanner);
अटल पूर्णांक get_config_terms(काष्ठा list_head *head_config,
			    काष्ठा list_head *head_terms __maybe_unused);
अटल पूर्णांक parse_events__with_hybrid_pmu(काष्ठा parse_events_state *parse_state,
					 स्थिर अक्षर *str, अक्षर *pmu_name,
					 काष्ठा list_head *list);

अटल काष्ठा perf_pmu_event_symbol *perf_pmu_events_list;
/*
 * The variable indicates the number of supported pmu event symbols.
 * 0 means not initialized and पढ़ोy to init
 * -1 means failed to init, करोn't try anymore
 * >0 is the number of supported pmu event symbols
 */
अटल पूर्णांक perf_pmu_events_list_num;

काष्ठा event_symbol event_symbols_hw[PERF_COUNT_HW_MAX] = अणु
	[PERF_COUNT_HW_CPU_CYCLES] = अणु
		.symbol = "cpu-cycles",
		.alias  = "cycles",
	पूर्ण,
	[PERF_COUNT_HW_INSTRUCTIONS] = अणु
		.symbol = "instructions",
		.alias  = "",
	पूर्ण,
	[PERF_COUNT_HW_CACHE_REFERENCES] = अणु
		.symbol = "cache-references",
		.alias  = "",
	पूर्ण,
	[PERF_COUNT_HW_CACHE_MISSES] = अणु
		.symbol = "cache-misses",
		.alias  = "",
	पूर्ण,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] = अणु
		.symbol = "branch-instructions",
		.alias  = "branches",
	पूर्ण,
	[PERF_COUNT_HW_BRANCH_MISSES] = अणु
		.symbol = "branch-misses",
		.alias  = "",
	पूर्ण,
	[PERF_COUNT_HW_BUS_CYCLES] = अणु
		.symbol = "bus-cycles",
		.alias  = "",
	पूर्ण,
	[PERF_COUNT_HW_STALLED_CYCLES_FRONTEND] = अणु
		.symbol = "stalled-cycles-frontend",
		.alias  = "idle-cycles-frontend",
	पूर्ण,
	[PERF_COUNT_HW_STALLED_CYCLES_BACKEND] = अणु
		.symbol = "stalled-cycles-backend",
		.alias  = "idle-cycles-backend",
	पूर्ण,
	[PERF_COUNT_HW_REF_CPU_CYCLES] = अणु
		.symbol = "ref-cycles",
		.alias  = "",
	पूर्ण,
पूर्ण;

काष्ठा event_symbol event_symbols_sw[PERF_COUNT_SW_MAX] = अणु
	[PERF_COUNT_SW_CPU_CLOCK] = अणु
		.symbol = "cpu-clock",
		.alias  = "",
	पूर्ण,
	[PERF_COUNT_SW_TASK_CLOCK] = अणु
		.symbol = "task-clock",
		.alias  = "",
	पूर्ण,
	[PERF_COUNT_SW_PAGE_FAULTS] = अणु
		.symbol = "page-faults",
		.alias  = "faults",
	पूर्ण,
	[PERF_COUNT_SW_CONTEXT_SWITCHES] = अणु
		.symbol = "context-switches",
		.alias  = "cs",
	पूर्ण,
	[PERF_COUNT_SW_CPU_MIGRATIONS] = अणु
		.symbol = "cpu-migrations",
		.alias  = "migrations",
	पूर्ण,
	[PERF_COUNT_SW_PAGE_FAULTS_MIN] = अणु
		.symbol = "minor-faults",
		.alias  = "",
	पूर्ण,
	[PERF_COUNT_SW_PAGE_FAULTS_MAJ] = अणु
		.symbol = "major-faults",
		.alias  = "",
	पूर्ण,
	[PERF_COUNT_SW_ALIGNMENT_FAULTS] = अणु
		.symbol = "alignment-faults",
		.alias  = "",
	पूर्ण,
	[PERF_COUNT_SW_EMULATION_FAULTS] = अणु
		.symbol = "emulation-faults",
		.alias  = "",
	पूर्ण,
	[PERF_COUNT_SW_DUMMY] = अणु
		.symbol = "dummy",
		.alias  = "",
	पूर्ण,
	[PERF_COUNT_SW_BPF_OUTPUT] = अणु
		.symbol = "bpf-output",
		.alias  = "",
	पूर्ण,
	[PERF_COUNT_SW_CGROUP_SWITCHES] = अणु
		.symbol = "cgroup-switches",
		.alias  = "",
	पूर्ण,
पूर्ण;

#घोषणा __PERF_EVENT_FIELD(config, name) \
	((config & PERF_EVENT_##name##_MASK) >> PERF_EVENT_##name##_SHIFT)

#घोषणा PERF_EVENT_RAW(config)		__PERF_EVENT_FIELD(config, RAW)
#घोषणा PERF_EVENT_CONFIG(config)	__PERF_EVENT_FIELD(config, CONFIG)
#घोषणा PERF_EVENT_TYPE(config)		__PERF_EVENT_FIELD(config, TYPE)
#घोषणा PERF_EVENT_ID(config)		__PERF_EVENT_FIELD(config, EVENT)

#घोषणा क्रम_each_subप्रणाली(sys_dir, sys_dirent)			\
	जबतक ((sys_dirent = सूची_पढ़ो(sys_dir)) != शून्य)		\
		अगर (sys_dirent->d_type == DT_सूची &&		\
		    (म_भेद(sys_dirent->d_name, ".")) &&	\
		    (म_भेद(sys_dirent->d_name, "..")))

अटल पूर्णांक tp_event_has_id(स्थिर अक्षर *dir_path, काष्ठा dirent *evt_dir)
अणु
	अक्षर evt_path[MAXPATHLEN];
	पूर्णांक fd;

	snम_लिखो(evt_path, MAXPATHLEN, "%s/%s/id", dir_path, evt_dir->d_name);
	fd = खोलो(evt_path, O_RDONLY);
	अगर (fd < 0)
		वापस -EINVAL;
	बंद(fd);

	वापस 0;
पूर्ण

#घोषणा क्रम_each_event(dir_path, evt_dir, evt_dirent)		\
	जबतक ((evt_dirent = सूची_पढ़ो(evt_dir)) != शून्य)		\
		अगर (evt_dirent->d_type == DT_सूची &&		\
		    (म_भेद(evt_dirent->d_name, ".")) &&	\
		    (म_भेद(evt_dirent->d_name, "..")) &&	\
		    (!tp_event_has_id(dir_path, evt_dirent)))

#घोषणा MAX_EVENT_LENGTH 512

व्योम parse_events__handle_error(काष्ठा parse_events_error *err, पूर्णांक idx,
				अक्षर *str, अक्षर *help)
अणु
	अगर (WARN(!str, "WARNING: failed to provide error string\n")) अणु
		मुक्त(help);
		वापस;
	पूर्ण
	चयन (err->num_errors) अणु
	हाल 0:
		err->idx = idx;
		err->str = str;
		err->help = help;
		अवरोध;
	हाल 1:
		err->first_idx = err->idx;
		err->idx = idx;
		err->first_str = err->str;
		err->str = str;
		err->first_help = err->help;
		err->help = help;
		अवरोध;
	शेष:
		pr_debug("Multiple errors dropping message: %s (%s)\n",
			err->str, err->help);
		मुक्त(err->str);
		err->str = str;
		मुक्त(err->help);
		err->help = help;
		अवरोध;
	पूर्ण
	err->num_errors++;
पूर्ण

काष्ठा tracepoपूर्णांक_path *tracepoपूर्णांक_id_to_path(u64 config)
अणु
	काष्ठा tracepoपूर्णांक_path *path = शून्य;
	सूची *sys_dir, *evt_dir;
	काष्ठा dirent *sys_dirent, *evt_dirent;
	अक्षर id_buf[24];
	पूर्णांक fd;
	u64 id;
	अक्षर evt_path[MAXPATHLEN];
	अक्षर *dir_path;

	sys_dir = tracing_events__सूची_खोलो();
	अगर (!sys_dir)
		वापस शून्य;

	क्रम_each_subप्रणाली(sys_dir, sys_dirent) अणु
		dir_path = get_events_file(sys_dirent->d_name);
		अगर (!dir_path)
			जारी;
		evt_dir = सूची_खोलो(dir_path);
		अगर (!evt_dir)
			जाओ next;

		क्रम_each_event(dir_path, evt_dir, evt_dirent) अणु

			scnम_लिखो(evt_path, MAXPATHLEN, "%s/%s/id", dir_path,
				  evt_dirent->d_name);
			fd = खोलो(evt_path, O_RDONLY);
			अगर (fd < 0)
				जारी;
			अगर (पढ़ो(fd, id_buf, माप(id_buf)) < 0) अणु
				बंद(fd);
				जारी;
			पूर्ण
			बंद(fd);
			id = म_से_दl(id_buf);
			अगर (id == config) अणु
				put_events_file(dir_path);
				बंद_सूची(evt_dir);
				बंद_सूची(sys_dir);
				path = zalloc(माप(*path));
				अगर (!path)
					वापस शून्य;
				अगर (aप्र_लिखो(&path->प्रणाली, "%.*s", MAX_EVENT_LENGTH, sys_dirent->d_name) < 0) अणु
					मुक्त(path);
					वापस शून्य;
				पूर्ण
				अगर (aप्र_लिखो(&path->name, "%.*s", MAX_EVENT_LENGTH, evt_dirent->d_name) < 0) अणु
					zमुक्त(&path->प्रणाली);
					मुक्त(path);
					वापस शून्य;
				पूर्ण
				वापस path;
			पूर्ण
		पूर्ण
		बंद_सूची(evt_dir);
next:
		put_events_file(dir_path);
	पूर्ण

	बंद_सूची(sys_dir);
	वापस शून्य;
पूर्ण

काष्ठा tracepoपूर्णांक_path *tracepoपूर्णांक_name_to_path(स्थिर अक्षर *name)
अणु
	काष्ठा tracepoपूर्णांक_path *path = zalloc(माप(*path));
	अक्षर *str = म_अक्षर(name, ':');

	अगर (path == शून्य || str == शून्य) अणु
		मुक्त(path);
		वापस शून्य;
	पूर्ण

	path->प्रणाली = strndup(name, str - name);
	path->name = strdup(str+1);

	अगर (path->प्रणाली == शून्य || path->name == शून्य) अणु
		zमुक्त(&path->प्रणाली);
		zमुक्त(&path->name);
		zमुक्त(&path);
	पूर्ण

	वापस path;
पूर्ण

स्थिर अक्षर *event_type(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल PERF_TYPE_HARDWARE:
		वापस "hardware";

	हाल PERF_TYPE_SOFTWARE:
		वापस "software";

	हाल PERF_TYPE_TRACEPOINT:
		वापस "tracepoint";

	हाल PERF_TYPE_HW_CACHE:
		वापस "hardware-cache";

	शेष:
		अवरोध;
	पूर्ण

	वापस "unknown";
पूर्ण

अटल पूर्णांक parse_events__is_name_term(काष्ठा parse_events_term *term)
अणु
	वापस term->type_term == PARSE_EVENTS__TERM_TYPE_NAME;
पूर्ण

अटल अक्षर *get_config_name(काष्ठा list_head *head_terms)
अणु
	काष्ठा parse_events_term *term;

	अगर (!head_terms)
		वापस शून्य;

	list_क्रम_each_entry(term, head_terms, list)
		अगर (parse_events__is_name_term(term))
			वापस term->val.str;

	वापस शून्य;
पूर्ण

अटल काष्ठा evsel *
__add_event(काष्ठा list_head *list, पूर्णांक *idx,
	    काष्ठा perf_event_attr *attr,
	    bool init_attr,
	    अक्षर *name, काष्ठा perf_pmu *pmu,
	    काष्ठा list_head *config_terms, bool स्वतः_merge_stats,
	    स्थिर अक्षर *cpu_list)
अणु
	काष्ठा evsel *evsel;
	काष्ठा perf_cpu_map *cpus = pmu ? perf_cpu_map__get(pmu->cpus) :
			       cpu_list ? perf_cpu_map__new(cpu_list) : शून्य;

	अगर (pmu && attr->type == PERF_TYPE_RAW)
		perf_pmu__warn_invalid_config(pmu, attr->config, name);

	अगर (init_attr)
		event_attr_init(attr);

	evsel = evsel__new_idx(attr, *idx);
	अगर (!evsel) अणु
		perf_cpu_map__put(cpus);
		वापस शून्य;
	पूर्ण

	(*idx)++;
	evsel->core.cpus = cpus;
	evsel->core.own_cpus = perf_cpu_map__get(cpus);
	evsel->core.प्रणाली_wide = pmu ? pmu->is_uncore : false;
	evsel->स्वतः_merge_stats = स्वतः_merge_stats;

	अगर (name)
		evsel->name = strdup(name);

	अगर (config_terms)
		list_splice(config_terms, &evsel->config_terms);

	अगर (list)
		list_add_tail(&evsel->core.node, list);

	वापस evsel;
पूर्ण

काष्ठा evsel *parse_events__add_event(पूर्णांक idx, काष्ठा perf_event_attr *attr,
					अक्षर *name, काष्ठा perf_pmu *pmu)
अणु
	वापस __add_event(शून्य, &idx, attr, false, name, pmu, शून्य, false,
			   शून्य);
पूर्ण

अटल पूर्णांक add_event(काष्ठा list_head *list, पूर्णांक *idx,
		     काष्ठा perf_event_attr *attr, अक्षर *name,
		     काष्ठा list_head *config_terms)
अणु
	वापस __add_event(list, idx, attr, true, name, शून्य, config_terms,
			   false, शून्य) ? 0 : -ENOMEM;
पूर्ण

अटल पूर्णांक add_event_tool(काष्ठा list_head *list, पूर्णांक *idx,
			  क्रमागत perf_tool_event tool_event)
अणु
	काष्ठा evsel *evsel;
	काष्ठा perf_event_attr attr = अणु
		.type = PERF_TYPE_SOFTWARE,
		.config = PERF_COUNT_SW_DUMMY,
	पूर्ण;

	evsel = __add_event(list, idx, &attr, true, शून्य, शून्य, शून्य, false,
			    "0");
	अगर (!evsel)
		वापस -ENOMEM;
	evsel->tool_event = tool_event;
	अगर (tool_event == PERF_TOOL_DURATION_TIME)
		evsel->unit = "ns";
	वापस 0;
पूर्ण

अटल पूर्णांक parse_aliases(अक्षर *str, स्थिर अक्षर *names[][EVSEL__MAX_ALIASES], पूर्णांक size)
अणु
	पूर्णांक i, j;
	पूर्णांक n, दीर्घest = -1;

	क्रम (i = 0; i < size; i++) अणु
		क्रम (j = 0; j < EVSEL__MAX_ALIASES && names[i][j]; j++) अणु
			n = म_माप(names[i][j]);
			अगर (n > दीर्घest && !strnहालcmp(str, names[i][j], n))
				दीर्घest = n;
		पूर्ण
		अगर (दीर्घest > 0)
			वापस i;
	पूर्ण

	वापस -1;
पूर्ण

प्रकार पूर्णांक config_term_func_t(काष्ठा perf_event_attr *attr,
			       काष्ठा parse_events_term *term,
			       काष्ठा parse_events_error *err);
अटल पूर्णांक config_term_common(काष्ठा perf_event_attr *attr,
			      काष्ठा parse_events_term *term,
			      काष्ठा parse_events_error *err);
अटल पूर्णांक config_attr(काष्ठा perf_event_attr *attr,
		       काष्ठा list_head *head,
		       काष्ठा parse_events_error *err,
		       config_term_func_t config_term);

पूर्णांक parse_events_add_cache(काष्ठा list_head *list, पूर्णांक *idx,
			   अक्षर *type, अक्षर *op_result1, अक्षर *op_result2,
			   काष्ठा parse_events_error *err,
			   काष्ठा list_head *head_config,
			   काष्ठा parse_events_state *parse_state)
अणु
	काष्ठा perf_event_attr attr;
	LIST_HEAD(config_terms);
	अक्षर name[MAX_NAME_LEN], *config_name;
	पूर्णांक cache_type = -1, cache_op = -1, cache_result = -1;
	अक्षर *op_result[2] = अणु op_result1, op_result2 पूर्ण;
	पूर्णांक i, n, ret;
	bool hybrid;

	/*
	 * No fallback - अगर we cannot get a clear cache type
	 * then bail out:
	 */
	cache_type = parse_aliases(type, evsel__hw_cache, PERF_COUNT_HW_CACHE_MAX);
	अगर (cache_type == -1)
		वापस -EINVAL;

	config_name = get_config_name(head_config);
	n = snम_लिखो(name, MAX_NAME_LEN, "%s", type);

	क्रम (i = 0; (i < 2) && (op_result[i]); i++) अणु
		अक्षर *str = op_result[i];

		n += snम_लिखो(name + n, MAX_NAME_LEN - n, "-%s", str);

		अगर (cache_op == -1) अणु
			cache_op = parse_aliases(str, evsel__hw_cache_op,
						 PERF_COUNT_HW_CACHE_OP_MAX);
			अगर (cache_op >= 0) अणु
				अगर (!evsel__is_cache_op_valid(cache_type, cache_op))
					वापस -EINVAL;
				जारी;
			पूर्ण
		पूर्ण

		अगर (cache_result == -1) अणु
			cache_result = parse_aliases(str, evsel__hw_cache_result,
						     PERF_COUNT_HW_CACHE_RESULT_MAX);
			अगर (cache_result >= 0)
				जारी;
		पूर्ण
	पूर्ण

	/*
	 * Fall back to पढ़ोs:
	 */
	अगर (cache_op == -1)
		cache_op = PERF_COUNT_HW_CACHE_OP_READ;

	/*
	 * Fall back to accesses:
	 */
	अगर (cache_result == -1)
		cache_result = PERF_COUNT_HW_CACHE_RESULT_ACCESS;

	स_रखो(&attr, 0, माप(attr));
	attr.config = cache_type | (cache_op << 8) | (cache_result << 16);
	attr.type = PERF_TYPE_HW_CACHE;

	अगर (head_config) अणु
		अगर (config_attr(&attr, head_config, err,
				config_term_common))
			वापस -EINVAL;

		अगर (get_config_terms(head_config, &config_terms))
			वापस -ENOMEM;
	पूर्ण

	ret = parse_events__add_cache_hybrid(list, idx, &attr,
					     config_name ? : name, &config_terms,
					     &hybrid, parse_state);
	अगर (hybrid)
		वापस ret;

	वापस add_event(list, idx, &attr, config_name ? : name, &config_terms);
पूर्ण

अटल व्योम tracepoपूर्णांक_error(काष्ठा parse_events_error *e, पूर्णांक err,
			     स्थिर अक्षर *sys, स्थिर अक्षर *name)
अणु
	स्थिर अक्षर *str;
	अक्षर help[बफ_मान];

	अगर (!e)
		वापस;

	/*
	 * We get error directly from syscall त्रुटि_सं ( > 0),
	 * or from encoded poपूर्णांकer's error ( < 0).
	 */
	err = असल(err);

	चयन (err) अणु
	हाल EACCES:
		str = "can't access trace events";
		अवरोध;
	हाल ENOENT:
		str = "unknown tracepoint";
		अवरोध;
	शेष:
		str = "failed to add tracepoint";
		अवरोध;
	पूर्ण

	tracing_path__म_त्रुटि_खोलो_tp(err, help, माप(help), sys, name);
	parse_events__handle_error(e, 0, strdup(str), strdup(help));
पूर्ण

अटल पूर्णांक add_tracepoपूर्णांक(काष्ठा list_head *list, पूर्णांक *idx,
			  स्थिर अक्षर *sys_name, स्थिर अक्षर *evt_name,
			  काष्ठा parse_events_error *err,
			  काष्ठा list_head *head_config)
अणु
	काष्ठा evsel *evsel = evsel__newtp_idx(sys_name, evt_name, (*idx)++);

	अगर (IS_ERR(evsel)) अणु
		tracepoपूर्णांक_error(err, PTR_ERR(evsel), sys_name, evt_name);
		वापस PTR_ERR(evsel);
	पूर्ण

	अगर (head_config) अणु
		LIST_HEAD(config_terms);

		अगर (get_config_terms(head_config, &config_terms))
			वापस -ENOMEM;
		list_splice(&config_terms, &evsel->config_terms);
	पूर्ण

	list_add_tail(&evsel->core.node, list);
	वापस 0;
पूर्ण

अटल पूर्णांक add_tracepoपूर्णांक_multi_event(काष्ठा list_head *list, पूर्णांक *idx,
				      स्थिर अक्षर *sys_name, स्थिर अक्षर *evt_name,
				      काष्ठा parse_events_error *err,
				      काष्ठा list_head *head_config)
अणु
	अक्षर *evt_path;
	काष्ठा dirent *evt_ent;
	सूची *evt_dir;
	पूर्णांक ret = 0, found = 0;

	evt_path = get_events_file(sys_name);
	अगर (!evt_path) अणु
		tracepoपूर्णांक_error(err, त्रुटि_सं, sys_name, evt_name);
		वापस -1;
	पूर्ण
	evt_dir = सूची_खोलो(evt_path);
	अगर (!evt_dir) अणु
		put_events_file(evt_path);
		tracepoपूर्णांक_error(err, त्रुटि_सं, sys_name, evt_name);
		वापस -1;
	पूर्ण

	जबतक (!ret && (evt_ent = सूची_पढ़ो(evt_dir))) अणु
		अगर (!म_भेद(evt_ent->d_name, ".")
		    || !म_भेद(evt_ent->d_name, "..")
		    || !म_भेद(evt_ent->d_name, "enable")
		    || !म_भेद(evt_ent->d_name, "filter"))
			जारी;

		अगर (!strglobmatch(evt_ent->d_name, evt_name))
			जारी;

		found++;

		ret = add_tracepoपूर्णांक(list, idx, sys_name, evt_ent->d_name,
				     err, head_config);
	पूर्ण

	अगर (!found) अणु
		tracepoपूर्णांक_error(err, ENOENT, sys_name, evt_name);
		ret = -1;
	पूर्ण

	put_events_file(evt_path);
	बंद_सूची(evt_dir);
	वापस ret;
पूर्ण

अटल पूर्णांक add_tracepoपूर्णांक_event(काष्ठा list_head *list, पूर्णांक *idx,
				स्थिर अक्षर *sys_name, स्थिर अक्षर *evt_name,
				काष्ठा parse_events_error *err,
				काष्ठा list_head *head_config)
अणु
	वापस strpbrk(evt_name, "*?") ?
	       add_tracepoपूर्णांक_multi_event(list, idx, sys_name, evt_name,
					  err, head_config) :
	       add_tracepoपूर्णांक(list, idx, sys_name, evt_name,
			      err, head_config);
पूर्ण

अटल पूर्णांक add_tracepoपूर्णांक_multi_sys(काष्ठा list_head *list, पूर्णांक *idx,
				    स्थिर अक्षर *sys_name, स्थिर अक्षर *evt_name,
				    काष्ठा parse_events_error *err,
				    काष्ठा list_head *head_config)
अणु
	काष्ठा dirent *events_ent;
	सूची *events_dir;
	पूर्णांक ret = 0;

	events_dir = tracing_events__सूची_खोलो();
	अगर (!events_dir) अणु
		tracepoपूर्णांक_error(err, त्रुटि_सं, sys_name, evt_name);
		वापस -1;
	पूर्ण

	जबतक (!ret && (events_ent = सूची_पढ़ो(events_dir))) अणु
		अगर (!म_भेद(events_ent->d_name, ".")
		    || !म_भेद(events_ent->d_name, "..")
		    || !म_भेद(events_ent->d_name, "enable")
		    || !म_भेद(events_ent->d_name, "header_event")
		    || !म_भेद(events_ent->d_name, "header_page"))
			जारी;

		अगर (!strglobmatch(events_ent->d_name, sys_name))
			जारी;

		ret = add_tracepoपूर्णांक_event(list, idx, events_ent->d_name,
					   evt_name, err, head_config);
	पूर्ण

	बंद_सूची(events_dir);
	वापस ret;
पूर्ण

#अगर_घोषित HAVE_LIBBPF_SUPPORT
काष्ठा __add_bpf_event_param अणु
	काष्ठा parse_events_state *parse_state;
	काष्ठा list_head *list;
	काष्ठा list_head *head_config;
पूर्ण;

अटल पूर्णांक add_bpf_event(स्थिर अक्षर *group, स्थिर अक्षर *event, पूर्णांक fd, काष्ठा bpf_object *obj,
			 व्योम *_param)
अणु
	LIST_HEAD(new_evsels);
	काष्ठा __add_bpf_event_param *param = _param;
	काष्ठा parse_events_state *parse_state = param->parse_state;
	काष्ठा list_head *list = param->list;
	काष्ठा evsel *pos;
	पूर्णांक err;
	/*
	 * Check अगर we should add the event, i.e. अगर it is a TP but starts with a '!',
	 * then करोn't add the tracepoपूर्णांक, this will be used क्रम something अन्यथा, like
	 * adding to a BPF_MAP_TYPE_PROG_ARRAY.
	 *
	 * See tools/perf/examples/bpf/augmented_raw_syscalls.c
	 */
	अगर (group[0] == '!')
		वापस 0;

	pr_debug("add bpf event %s:%s and attach bpf program %d\n",
		 group, event, fd);

	err = parse_events_add_tracepoपूर्णांक(&new_evsels, &parse_state->idx, group,
					  event, parse_state->error,
					  param->head_config);
	अगर (err) अणु
		काष्ठा evsel *evsel, *पंचांगp;

		pr_debug("Failed to add BPF event %s:%s\n",
			 group, event);
		list_क्रम_each_entry_safe(evsel, पंचांगp, &new_evsels, core.node) अणु
			list_del_init(&evsel->core.node);
			evsel__delete(evsel);
		पूर्ण
		वापस err;
	पूर्ण
	pr_debug("adding %s:%s\n", group, event);

	list_क्रम_each_entry(pos, &new_evsels, core.node) अणु
		pr_debug("adding %s:%s to %p\n",
			 group, event, pos);
		pos->bpf_fd = fd;
		pos->bpf_obj = obj;
	पूर्ण
	list_splice(&new_evsels, list);
	वापस 0;
पूर्ण

पूर्णांक parse_events_load_bpf_obj(काष्ठा parse_events_state *parse_state,
			      काष्ठा list_head *list,
			      काष्ठा bpf_object *obj,
			      काष्ठा list_head *head_config)
अणु
	पूर्णांक err;
	अक्षर errbuf[बफ_मान];
	काष्ठा __add_bpf_event_param param = अणुparse_state, list, head_configपूर्ण;
	अटल bool रेजिस्टरed_unprobe_निकास_पर = false;

	अगर (IS_ERR(obj) || !obj) अणु
		snम_लिखो(errbuf, माप(errbuf),
			 "Internal error: load bpf obj with NULL");
		err = -EINVAL;
		जाओ errout;
	पूर्ण

	/*
	 * Register निकास_पर handler beक्रमe calling bpf__probe() so
	 * bpf__probe() करोn't need to unprobe probe poपूर्णांकs its alपढ़ोy
	 * created when failure.
	 */
	अगर (!रेजिस्टरed_unprobe_निकास_पर) अणु
		निकास_पर(bpf__clear);
		रेजिस्टरed_unprobe_निकास_पर = true;
	पूर्ण

	err = bpf__probe(obj);
	अगर (err) अणु
		bpf__म_त्रुटि_probe(obj, err, errbuf, माप(errbuf));
		जाओ errout;
	पूर्ण

	err = bpf__load(obj);
	अगर (err) अणु
		bpf__म_त्रुटि_load(obj, err, errbuf, माप(errbuf));
		जाओ errout;
	पूर्ण

	err = bpf__क्रमeach_event(obj, add_bpf_event, &param);
	अगर (err) अणु
		snम_लिखो(errbuf, माप(errbuf),
			 "Attach events in BPF object failed");
		जाओ errout;
	पूर्ण

	वापस 0;
errout:
	parse_events__handle_error(parse_state->error, 0,
				strdup(errbuf), strdup("(add -v to see detail)"));
	वापस err;
पूर्ण

अटल पूर्णांक
parse_events_config_bpf(काष्ठा parse_events_state *parse_state,
			काष्ठा bpf_object *obj,
			काष्ठा list_head *head_config)
अणु
	काष्ठा parse_events_term *term;
	पूर्णांक error_pos;

	अगर (!head_config || list_empty(head_config))
		वापस 0;

	list_क्रम_each_entry(term, head_config, list) अणु
		पूर्णांक err;

		अगर (term->type_term != PARSE_EVENTS__TERM_TYPE_USER) अणु
			parse_events__handle_error(parse_state->error, term->err_term,
						strdup("Invalid config term for BPF object"),
						शून्य);
			वापस -EINVAL;
		पूर्ण

		err = bpf__config_obj(obj, term, parse_state->evlist, &error_pos);
		अगर (err) अणु
			अक्षर errbuf[बफ_मान];
			पूर्णांक idx;

			bpf__म_त्रुटि_config_obj(obj, term, parse_state->evlist,
						 &error_pos, err, errbuf,
						 माप(errbuf));

			अगर (err == -BPF_LOADER_ERRNO__OBJCONF_MAP_VALUE)
				idx = term->err_val;
			अन्यथा
				idx = term->err_term + error_pos;

			parse_events__handle_error(parse_state->error, idx,
						strdup(errbuf),
						strdup(
"Hint:\tValid config terms:\n"
"     \tmap:[<arraymap>].value<indices>=[value]\n"
"     \tmap:[<eventmap>].event<indices>=[event]\n"
"\n"
"     \twhere <indices> is something like [0,3...5] or [all]\n"
"     \t(add -v to see detail)"));
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Split config terms:
 * perf record -e bpf.c/call-graph=fp,map:array.value[0]=1/ ...
 *  'call-graph=fp' is 'evt config', should be applied to each
 *  events in bpf.c.
 * 'map:array.value[0]=1' is 'obj config', should be processed
 * with parse_events_config_bpf.
 *
 * Move object config terms from the first list to obj_head_config.
 */
अटल व्योम
split_bpf_config_terms(काष्ठा list_head *evt_head_config,
		       काष्ठा list_head *obj_head_config)
अणु
	काष्ठा parse_events_term *term, *temp;

	/*
	 * Currently, all possible user config term
	 * beदीर्घ to bpf object. parse_events__is_hardcoded_term()
	 * happens to be a good flag.
	 *
	 * See parse_events_config_bpf() and
	 * config_term_tracepoपूर्णांक().
	 */
	list_क्रम_each_entry_safe(term, temp, evt_head_config, list)
		अगर (!parse_events__is_hardcoded_term(term))
			list_move_tail(&term->list, obj_head_config);
पूर्ण

पूर्णांक parse_events_load_bpf(काष्ठा parse_events_state *parse_state,
			  काष्ठा list_head *list,
			  अक्षर *bpf_file_name,
			  bool source,
			  काष्ठा list_head *head_config)
अणु
	पूर्णांक err;
	काष्ठा bpf_object *obj;
	LIST_HEAD(obj_head_config);

	अगर (head_config)
		split_bpf_config_terms(head_config, &obj_head_config);

	obj = bpf__prepare_load(bpf_file_name, source);
	अगर (IS_ERR(obj)) अणु
		अक्षर errbuf[बफ_मान];

		err = PTR_ERR(obj);

		अगर (err == -ENOTSUP)
			snम_लिखो(errbuf, माप(errbuf),
				 "BPF support is not compiled");
		अन्यथा
			bpf__म_त्रुटि_prepare_load(bpf_file_name,
						   source,
						   -err, errbuf,
						   माप(errbuf));

		parse_events__handle_error(parse_state->error, 0,
					strdup(errbuf), strdup("(add -v to see detail)"));
		वापस err;
	पूर्ण

	err = parse_events_load_bpf_obj(parse_state, list, obj, head_config);
	अगर (err)
		वापस err;
	err = parse_events_config_bpf(parse_state, obj, &obj_head_config);

	/*
	 * Caller करोesn't know anything about obj_head_config,
	 * so combine them together again beक्रमe वापसing.
	 */
	अगर (head_config)
		list_splice_tail(&obj_head_config, head_config);
	वापस err;
पूर्ण
#अन्यथा // HAVE_LIBBPF_SUPPORT
पूर्णांक parse_events_load_bpf_obj(काष्ठा parse_events_state *parse_state,
			      काष्ठा list_head *list __maybe_unused,
			      काष्ठा bpf_object *obj __maybe_unused,
			      काष्ठा list_head *head_config __maybe_unused)
अणु
	parse_events__handle_error(parse_state->error, 0,
				   strdup("BPF support is not compiled"),
				   strdup("Make sure libbpf-devel is available at build time."));
	वापस -ENOTSUP;
पूर्ण

पूर्णांक parse_events_load_bpf(काष्ठा parse_events_state *parse_state,
			  काष्ठा list_head *list __maybe_unused,
			  अक्षर *bpf_file_name __maybe_unused,
			  bool source __maybe_unused,
			  काष्ठा list_head *head_config __maybe_unused)
अणु
	parse_events__handle_error(parse_state->error, 0,
				   strdup("BPF support is not compiled"),
				   strdup("Make sure libbpf-devel is available at build time."));
	वापस -ENOTSUP;
पूर्ण
#पूर्ण_अगर // HAVE_LIBBPF_SUPPORT

अटल पूर्णांक
parse_अवरोधpoपूर्णांक_type(स्थिर अक्षर *type, काष्ठा perf_event_attr *attr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		अगर (!type || !type[i])
			अवरोध;

#घोषणा CHECK_SET_TYPE(bit)		\
करो अणु					\
	अगर (attr->bp_type & bit)	\
		वापस -EINVAL;		\
	अन्यथा				\
		attr->bp_type |= bit;	\
पूर्ण जबतक (0)

		चयन (type[i]) अणु
		हाल 'r':
			CHECK_SET_TYPE(HW_BREAKPOINT_R);
			अवरोध;
		हाल 'w':
			CHECK_SET_TYPE(HW_BREAKPOINT_W);
			अवरोध;
		हाल 'x':
			CHECK_SET_TYPE(HW_BREAKPOINT_X);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

#अघोषित CHECK_SET_TYPE

	अगर (!attr->bp_type) /* Default */
		attr->bp_type = HW_BREAKPOINT_R | HW_BREAKPOINT_W;

	वापस 0;
पूर्ण

पूर्णांक parse_events_add_अवरोधpoपूर्णांक(काष्ठा list_head *list, पूर्णांक *idx,
				u64 addr, अक्षर *type, u64 len)
अणु
	काष्ठा perf_event_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.bp_addr = addr;

	अगर (parse_अवरोधpoपूर्णांक_type(type, &attr))
		वापस -EINVAL;

	/* Provide some शेषs अगर len is not specअगरied */
	अगर (!len) अणु
		अगर (attr.bp_type == HW_BREAKPOINT_X)
			len = माप(दीर्घ);
		अन्यथा
			len = HW_BREAKPOINT_LEN_4;
	पूर्ण

	attr.bp_len = len;

	attr.type = PERF_TYPE_BREAKPOINT;
	attr.sample_period = 1;

	वापस add_event(list, idx, &attr, शून्य, शून्य);
पूर्ण

अटल पूर्णांक check_type_val(काष्ठा parse_events_term *term,
			  काष्ठा parse_events_error *err,
			  पूर्णांक type)
अणु
	अगर (type == term->type_val)
		वापस 0;

	अगर (err) अणु
		parse_events__handle_error(err, term->err_val,
					type == PARSE_EVENTS__TERM_TYPE_NUM
					? strdup("expected numeric value")
					: strdup("expected string value"),
					शून्य);
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * Update according to parse-events.l
 */
अटल स्थिर अक्षर *config_term_names[__PARSE_EVENTS__TERM_TYPE_NR] = अणु
	[PARSE_EVENTS__TERM_TYPE_USER]			= "<sysfs term>",
	[PARSE_EVENTS__TERM_TYPE_CONFIG]		= "config",
	[PARSE_EVENTS__TERM_TYPE_CONFIG1]		= "config1",
	[PARSE_EVENTS__TERM_TYPE_CONFIG2]		= "config2",
	[PARSE_EVENTS__TERM_TYPE_NAME]			= "name",
	[PARSE_EVENTS__TERM_TYPE_SAMPLE_PERIOD]		= "period",
	[PARSE_EVENTS__TERM_TYPE_SAMPLE_FREQ]		= "freq",
	[PARSE_EVENTS__TERM_TYPE_BRANCH_SAMPLE_TYPE]	= "branch_type",
	[PARSE_EVENTS__TERM_TYPE_TIME]			= "time",
	[PARSE_EVENTS__TERM_TYPE_CALLGRAPH]		= "call-graph",
	[PARSE_EVENTS__TERM_TYPE_STACKSIZE]		= "stack-size",
	[PARSE_EVENTS__TERM_TYPE_NOINHERIT]		= "no-inherit",
	[PARSE_EVENTS__TERM_TYPE_INHERIT]		= "inherit",
	[PARSE_EVENTS__TERM_TYPE_MAX_STACK]		= "max-stack",
	[PARSE_EVENTS__TERM_TYPE_MAX_EVENTS]		= "nr",
	[PARSE_EVENTS__TERM_TYPE_OVERWRITE]		= "overwrite",
	[PARSE_EVENTS__TERM_TYPE_NOOVERWRITE]		= "no-overwrite",
	[PARSE_EVENTS__TERM_TYPE_DRV_CFG]		= "driver-config",
	[PARSE_EVENTS__TERM_TYPE_PERCORE]		= "percore",
	[PARSE_EVENTS__TERM_TYPE_AUX_OUTPUT]		= "aux-output",
	[PARSE_EVENTS__TERM_TYPE_AUX_SAMPLE_SIZE]	= "aux-sample-size",
पूर्ण;

अटल bool config_term_shrinked;

अटल bool
config_term_avail(पूर्णांक term_type, काष्ठा parse_events_error *err)
अणु
	अक्षर *err_str;

	अगर (term_type < 0 || term_type >= __PARSE_EVENTS__TERM_TYPE_NR) अणु
		parse_events__handle_error(err, -1,
					strdup("Invalid term_type"), शून्य);
		वापस false;
	पूर्ण
	अगर (!config_term_shrinked)
		वापस true;

	चयन (term_type) अणु
	हाल PARSE_EVENTS__TERM_TYPE_CONFIG:
	हाल PARSE_EVENTS__TERM_TYPE_CONFIG1:
	हाल PARSE_EVENTS__TERM_TYPE_CONFIG2:
	हाल PARSE_EVENTS__TERM_TYPE_NAME:
	हाल PARSE_EVENTS__TERM_TYPE_SAMPLE_PERIOD:
	हाल PARSE_EVENTS__TERM_TYPE_PERCORE:
		वापस true;
	शेष:
		अगर (!err)
			वापस false;

		/* term_type is validated so indexing is safe */
		अगर (aप्र_लिखो(&err_str, "'%s' is not usable in 'perf stat'",
				config_term_names[term_type]) >= 0)
			parse_events__handle_error(err, -1, err_str, शून्य);
		वापस false;
	पूर्ण
पूर्ण

व्योम parse_events__shrink_config_terms(व्योम)
अणु
	config_term_shrinked = true;
पूर्ण

अटल पूर्णांक config_term_common(काष्ठा perf_event_attr *attr,
			      काष्ठा parse_events_term *term,
			      काष्ठा parse_events_error *err)
अणु
#घोषणा CHECK_TYPE_VAL(type)						   \
करो अणु									   \
	अगर (check_type_val(term, err, PARSE_EVENTS__TERM_TYPE_ ## type)) \
		वापस -EINVAL;						   \
पूर्ण जबतक (0)

	चयन (term->type_term) अणु
	हाल PARSE_EVENTS__TERM_TYPE_CONFIG:
		CHECK_TYPE_VAL(NUM);
		attr->config = term->val.num;
		अवरोध;
	हाल PARSE_EVENTS__TERM_TYPE_CONFIG1:
		CHECK_TYPE_VAL(NUM);
		attr->config1 = term->val.num;
		अवरोध;
	हाल PARSE_EVENTS__TERM_TYPE_CONFIG2:
		CHECK_TYPE_VAL(NUM);
		attr->config2 = term->val.num;
		अवरोध;
	हाल PARSE_EVENTS__TERM_TYPE_SAMPLE_PERIOD:
		CHECK_TYPE_VAL(NUM);
		अवरोध;
	हाल PARSE_EVENTS__TERM_TYPE_SAMPLE_FREQ:
		CHECK_TYPE_VAL(NUM);
		अवरोध;
	हाल PARSE_EVENTS__TERM_TYPE_BRANCH_SAMPLE_TYPE:
		CHECK_TYPE_VAL(STR);
		अगर (म_भेद(term->val.str, "no") &&
		    parse_branch_str(term->val.str,
				    &attr->branch_sample_type)) अणु
			parse_events__handle_error(err, term->err_val,
					strdup("invalid branch sample type"),
					शून्य);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PARSE_EVENTS__TERM_TYPE_TIME:
		CHECK_TYPE_VAL(NUM);
		अगर (term->val.num > 1) अणु
			parse_events__handle_error(err, term->err_val,
						strdup("expected 0 or 1"),
						शून्य);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PARSE_EVENTS__TERM_TYPE_CALLGRAPH:
		CHECK_TYPE_VAL(STR);
		अवरोध;
	हाल PARSE_EVENTS__TERM_TYPE_STACKSIZE:
		CHECK_TYPE_VAL(NUM);
		अवरोध;
	हाल PARSE_EVENTS__TERM_TYPE_INHERIT:
		CHECK_TYPE_VAL(NUM);
		अवरोध;
	हाल PARSE_EVENTS__TERM_TYPE_NOINHERIT:
		CHECK_TYPE_VAL(NUM);
		अवरोध;
	हाल PARSE_EVENTS__TERM_TYPE_OVERWRITE:
		CHECK_TYPE_VAL(NUM);
		अवरोध;
	हाल PARSE_EVENTS__TERM_TYPE_NOOVERWRITE:
		CHECK_TYPE_VAL(NUM);
		अवरोध;
	हाल PARSE_EVENTS__TERM_TYPE_NAME:
		CHECK_TYPE_VAL(STR);
		अवरोध;
	हाल PARSE_EVENTS__TERM_TYPE_MAX_STACK:
		CHECK_TYPE_VAL(NUM);
		अवरोध;
	हाल PARSE_EVENTS__TERM_TYPE_MAX_EVENTS:
		CHECK_TYPE_VAL(NUM);
		अवरोध;
	हाल PARSE_EVENTS__TERM_TYPE_PERCORE:
		CHECK_TYPE_VAL(NUM);
		अगर ((अचिन्हित पूर्णांक)term->val.num > 1) अणु
			parse_events__handle_error(err, term->err_val,
						strdup("expected 0 or 1"),
						शून्य);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PARSE_EVENTS__TERM_TYPE_AUX_OUTPUT:
		CHECK_TYPE_VAL(NUM);
		अवरोध;
	हाल PARSE_EVENTS__TERM_TYPE_AUX_SAMPLE_SIZE:
		CHECK_TYPE_VAL(NUM);
		अगर (term->val.num > अच_पूर्णांक_उच्च) अणु
			parse_events__handle_error(err, term->err_val,
						strdup("too big"),
						शून्य);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		parse_events__handle_error(err, term->err_term,
				strdup("unknown term"),
				parse_events_क्रमmats_error_string(शून्य));
		वापस -EINVAL;
	पूर्ण

	/*
	 * Check term availability after basic checking so
	 * PARSE_EVENTS__TERM_TYPE_USER can be found and filtered.
	 *
	 * If check availability at the entry of this function,
	 * user will see "'<sysfs term>' is not usable in 'perf stat'"
	 * अगर an invalid config term is provided क्रम legacy events
	 * (क्रम example, inकाष्ठाions/badterm/...), which is confusing.
	 */
	अगर (!config_term_avail(term->type_term, err))
		वापस -EINVAL;
	वापस 0;
#अघोषित CHECK_TYPE_VAL
पूर्ण

अटल पूर्णांक config_term_pmu(काष्ठा perf_event_attr *attr,
			   काष्ठा parse_events_term *term,
			   काष्ठा parse_events_error *err)
अणु
	अगर (term->type_term == PARSE_EVENTS__TERM_TYPE_USER ||
	    term->type_term == PARSE_EVENTS__TERM_TYPE_DRV_CFG)
		/*
		 * Always succeed क्रम sysfs terms, as we करोnt know
		 * at this poपूर्णांक what type they need to have.
		 */
		वापस 0;
	अन्यथा
		वापस config_term_common(attr, term, err);
पूर्ण

अटल पूर्णांक config_term_tracepoपूर्णांक(काष्ठा perf_event_attr *attr,
				  काष्ठा parse_events_term *term,
				  काष्ठा parse_events_error *err)
अणु
	चयन (term->type_term) अणु
	हाल PARSE_EVENTS__TERM_TYPE_CALLGRAPH:
	हाल PARSE_EVENTS__TERM_TYPE_STACKSIZE:
	हाल PARSE_EVENTS__TERM_TYPE_INHERIT:
	हाल PARSE_EVENTS__TERM_TYPE_NOINHERIT:
	हाल PARSE_EVENTS__TERM_TYPE_MAX_STACK:
	हाल PARSE_EVENTS__TERM_TYPE_MAX_EVENTS:
	हाल PARSE_EVENTS__TERM_TYPE_OVERWRITE:
	हाल PARSE_EVENTS__TERM_TYPE_NOOVERWRITE:
	हाल PARSE_EVENTS__TERM_TYPE_AUX_OUTPUT:
	हाल PARSE_EVENTS__TERM_TYPE_AUX_SAMPLE_SIZE:
		वापस config_term_common(attr, term, err);
	शेष:
		अगर (err) अणु
			parse_events__handle_error(err, term->err_term,
				strdup("unknown term"),
				strdup("valid terms: call-graph,stack-size\n"));
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक config_attr(काष्ठा perf_event_attr *attr,
		       काष्ठा list_head *head,
		       काष्ठा parse_events_error *err,
		       config_term_func_t config_term)
अणु
	काष्ठा parse_events_term *term;

	list_क्रम_each_entry(term, head, list)
		अगर (config_term(attr, term, err))
			वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक get_config_terms(काष्ठा list_head *head_config,
			    काष्ठा list_head *head_terms __maybe_unused)
अणु
#घोषणा ADD_CONFIG_TERM(__type, __weak)				\
	काष्ठा evsel_config_term *__t;			\
								\
	__t = zalloc(माप(*__t));				\
	अगर (!__t)						\
		वापस -ENOMEM;					\
								\
	INIT_LIST_HEAD(&__t->list);				\
	__t->type       = EVSEL__CONFIG_TERM_ ## __type;	\
	__t->weak	= __weak;				\
	list_add_tail(&__t->list, head_terms)

#घोषणा ADD_CONFIG_TERM_VAL(__type, __name, __val, __weak)	\
करो अणु								\
	ADD_CONFIG_TERM(__type, __weak);			\
	__t->val.__name = __val;				\
पूर्ण जबतक (0)

#घोषणा ADD_CONFIG_TERM_STR(__type, __val, __weak)		\
करो अणु								\
	ADD_CONFIG_TERM(__type, __weak);			\
	__t->val.str = strdup(__val);				\
	अगर (!__t->val.str) अणु					\
		zमुक्त(&__t);					\
		वापस -ENOMEM;					\
	पूर्ण							\
	__t->मुक्त_str = true;					\
पूर्ण जबतक (0)

	काष्ठा parse_events_term *term;

	list_क्रम_each_entry(term, head_config, list) अणु
		चयन (term->type_term) अणु
		हाल PARSE_EVENTS__TERM_TYPE_SAMPLE_PERIOD:
			ADD_CONFIG_TERM_VAL(PERIOD, period, term->val.num, term->weak);
			अवरोध;
		हाल PARSE_EVENTS__TERM_TYPE_SAMPLE_FREQ:
			ADD_CONFIG_TERM_VAL(FREQ, freq, term->val.num, term->weak);
			अवरोध;
		हाल PARSE_EVENTS__TERM_TYPE_TIME:
			ADD_CONFIG_TERM_VAL(TIME, समय, term->val.num, term->weak);
			अवरोध;
		हाल PARSE_EVENTS__TERM_TYPE_CALLGRAPH:
			ADD_CONFIG_TERM_STR(CALLGRAPH, term->val.str, term->weak);
			अवरोध;
		हाल PARSE_EVENTS__TERM_TYPE_BRANCH_SAMPLE_TYPE:
			ADD_CONFIG_TERM_STR(BRANCH, term->val.str, term->weak);
			अवरोध;
		हाल PARSE_EVENTS__TERM_TYPE_STACKSIZE:
			ADD_CONFIG_TERM_VAL(STACK_USER, stack_user,
					    term->val.num, term->weak);
			अवरोध;
		हाल PARSE_EVENTS__TERM_TYPE_INHERIT:
			ADD_CONFIG_TERM_VAL(INHERIT, inherit,
					    term->val.num ? 1 : 0, term->weak);
			अवरोध;
		हाल PARSE_EVENTS__TERM_TYPE_NOINHERIT:
			ADD_CONFIG_TERM_VAL(INHERIT, inherit,
					    term->val.num ? 0 : 1, term->weak);
			अवरोध;
		हाल PARSE_EVENTS__TERM_TYPE_MAX_STACK:
			ADD_CONFIG_TERM_VAL(MAX_STACK, max_stack,
					    term->val.num, term->weak);
			अवरोध;
		हाल PARSE_EVENTS__TERM_TYPE_MAX_EVENTS:
			ADD_CONFIG_TERM_VAL(MAX_EVENTS, max_events,
					    term->val.num, term->weak);
			अवरोध;
		हाल PARSE_EVENTS__TERM_TYPE_OVERWRITE:
			ADD_CONFIG_TERM_VAL(OVERWRITE, overग_लिखो,
					    term->val.num ? 1 : 0, term->weak);
			अवरोध;
		हाल PARSE_EVENTS__TERM_TYPE_NOOVERWRITE:
			ADD_CONFIG_TERM_VAL(OVERWRITE, overग_लिखो,
					    term->val.num ? 0 : 1, term->weak);
			अवरोध;
		हाल PARSE_EVENTS__TERM_TYPE_DRV_CFG:
			ADD_CONFIG_TERM_STR(DRV_CFG, term->val.str, term->weak);
			अवरोध;
		हाल PARSE_EVENTS__TERM_TYPE_PERCORE:
			ADD_CONFIG_TERM_VAL(PERCORE, percore,
					    term->val.num ? true : false, term->weak);
			अवरोध;
		हाल PARSE_EVENTS__TERM_TYPE_AUX_OUTPUT:
			ADD_CONFIG_TERM_VAL(AUX_OUTPUT, aux_output,
					    term->val.num ? 1 : 0, term->weak);
			अवरोध;
		हाल PARSE_EVENTS__TERM_TYPE_AUX_SAMPLE_SIZE:
			ADD_CONFIG_TERM_VAL(AUX_SAMPLE_SIZE, aux_sample_size,
					    term->val.num, term->weak);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Add EVSEL__CONFIG_TERM_CFG_CHG where cfg_chg will have a bit set क्रम
 * each bit of attr->config that the user has changed.
 */
अटल पूर्णांक get_config_chgs(काष्ठा perf_pmu *pmu, काष्ठा list_head *head_config,
			   काष्ठा list_head *head_terms)
अणु
	काष्ठा parse_events_term *term;
	u64 bits = 0;
	पूर्णांक type;

	list_क्रम_each_entry(term, head_config, list) अणु
		चयन (term->type_term) अणु
		हाल PARSE_EVENTS__TERM_TYPE_USER:
			type = perf_pmu__क्रमmat_type(&pmu->क्रमmat, term->config);
			अगर (type != PERF_PMU_FORMAT_VALUE_CONFIG)
				जारी;
			bits |= perf_pmu__क्रमmat_bits(&pmu->क्रमmat, term->config);
			अवरोध;
		हाल PARSE_EVENTS__TERM_TYPE_CONFIG:
			bits = ~(u64)0;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (bits)
		ADD_CONFIG_TERM_VAL(CFG_CHG, cfg_chg, bits, false);

#अघोषित ADD_CONFIG_TERM
	वापस 0;
पूर्ण

पूर्णांक parse_events_add_tracepoपूर्णांक(काष्ठा list_head *list, पूर्णांक *idx,
				स्थिर अक्षर *sys, स्थिर अक्षर *event,
				काष्ठा parse_events_error *err,
				काष्ठा list_head *head_config)
अणु
	अगर (head_config) अणु
		काष्ठा perf_event_attr attr;

		अगर (config_attr(&attr, head_config, err,
				config_term_tracepoपूर्णांक))
			वापस -EINVAL;
	पूर्ण

	अगर (strpbrk(sys, "*?"))
		वापस add_tracepoपूर्णांक_multi_sys(list, idx, sys, event,
						err, head_config);
	अन्यथा
		वापस add_tracepoपूर्णांक_event(list, idx, sys, event,
					    err, head_config);
पूर्ण

पूर्णांक parse_events_add_numeric(काष्ठा parse_events_state *parse_state,
			     काष्ठा list_head *list,
			     u32 type, u64 config,
			     काष्ठा list_head *head_config)
अणु
	काष्ठा perf_event_attr attr;
	LIST_HEAD(config_terms);
	bool hybrid;
	पूर्णांक ret;

	स_रखो(&attr, 0, माप(attr));
	attr.type = type;
	attr.config = config;

	अगर (head_config) अणु
		अगर (config_attr(&attr, head_config, parse_state->error,
				config_term_common))
			वापस -EINVAL;

		अगर (get_config_terms(head_config, &config_terms))
			वापस -ENOMEM;
	पूर्ण

	ret = parse_events__add_numeric_hybrid(parse_state, list, &attr,
					       get_config_name(head_config),
					       &config_terms, &hybrid);
	अगर (hybrid)
		वापस ret;

	वापस add_event(list, &parse_state->idx, &attr,
			 get_config_name(head_config), &config_terms);
पूर्ण

पूर्णांक parse_events_add_tool(काष्ठा parse_events_state *parse_state,
			  काष्ठा list_head *list,
			  क्रमागत perf_tool_event tool_event)
अणु
	वापस add_event_tool(list, &parse_state->idx, tool_event);
पूर्ण

अटल bool config_term_percore(काष्ठा list_head *config_terms)
अणु
	काष्ठा evsel_config_term *term;

	list_क्रम_each_entry(term, config_terms, list) अणु
		अगर (term->type == EVSEL__CONFIG_TERM_PERCORE)
			वापस term->val.percore;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक parse_events__inside_hybrid_pmu(काष्ठा parse_events_state *parse_state,
					   काष्ठा list_head *list, अक्षर *name,
					   काष्ठा list_head *head_config)
अणु
	काष्ठा parse_events_term *term;
	पूर्णांक ret = -1;

	अगर (parse_state->fake_pmu || !head_config || list_empty(head_config) ||
	    !perf_pmu__is_hybrid(name)) अणु
		वापस -1;
	पूर्ण

	/*
	 * More than one term in list.
	 */
	अगर (head_config->next && head_config->next->next != head_config)
		वापस -1;

	term = list_first_entry(head_config, काष्ठा parse_events_term, list);
	अगर (term && term->config && म_भेद(term->config, "event")) अणु
		ret = parse_events__with_hybrid_pmu(parse_state, term->config,
						    name, list);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक parse_events_add_pmu(काष्ठा parse_events_state *parse_state,
			 काष्ठा list_head *list, अक्षर *name,
			 काष्ठा list_head *head_config,
			 bool स्वतः_merge_stats,
			 bool use_alias)
अणु
	काष्ठा perf_event_attr attr;
	काष्ठा perf_pmu_info info;
	काष्ठा perf_pmu *pmu;
	काष्ठा evsel *evsel;
	काष्ठा parse_events_error *err = parse_state->error;
	bool use_uncore_alias;
	LIST_HEAD(config_terms);

	अगर (verbose > 1) अणु
		ख_लिखो(मानक_त्रुटि, "Attempting to add event pmu '%s' with '",
			name);
		अगर (head_config) अणु
			काष्ठा parse_events_term *term;

			list_क्रम_each_entry(term, head_config, list) अणु
				ख_लिखो(मानक_त्रुटि, "%s,", term->config);
			पूर्ण
		पूर्ण
		ख_लिखो(मानक_त्रुटि, "' that may result in non-fatal errors\n");
	पूर्ण

	pmu = parse_state->fake_pmu ?: perf_pmu__find(name);
	अगर (!pmu) अणु
		अक्षर *err_str;

		अगर (aप्र_लिखो(&err_str,
				"Cannot find PMU `%s'. Missing kernel support?",
				name) >= 0)
			parse_events__handle_error(err, 0, err_str, शून्य);
		वापस -EINVAL;
	पूर्ण

	अगर (pmu->शेष_config) अणु
		स_नकल(&attr, pmu->शेष_config,
		       माप(काष्ठा perf_event_attr));
	पूर्ण अन्यथा अणु
		स_रखो(&attr, 0, माप(attr));
	पूर्ण

	use_uncore_alias = (pmu->is_uncore && use_alias);

	अगर (!head_config) अणु
		attr.type = pmu->type;
		evsel = __add_event(list, &parse_state->idx, &attr, true, शून्य,
				    pmu, शून्य, स्वतः_merge_stats, शून्य);
		अगर (evsel) अणु
			evsel->pmu_name = name ? strdup(name) : शून्य;
			evsel->use_uncore_alias = use_uncore_alias;
			वापस 0;
		पूर्ण अन्यथा अणु
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (!parse_state->fake_pmu && perf_pmu__check_alias(pmu, head_config, &info))
		वापस -EINVAL;

	अगर (verbose > 1) अणु
		ख_लिखो(मानक_त्रुटि, "After aliases, add event pmu '%s' with '",
			name);
		अगर (head_config) अणु
			काष्ठा parse_events_term *term;

			list_क्रम_each_entry(term, head_config, list) अणु
				ख_लिखो(मानक_त्रुटि, "%s,", term->config);
			पूर्ण
		पूर्ण
		ख_लिखो(मानक_त्रुटि, "' that may result in non-fatal errors\n");
	पूर्ण

	/*
	 * Configure hardcoded terms first, no need to check
	 * वापस value when called with fail == 0 ;)
	 */
	अगर (config_attr(&attr, head_config, parse_state->error, config_term_pmu))
		वापस -EINVAL;

	अगर (get_config_terms(head_config, &config_terms))
		वापस -ENOMEM;

	/*
	 * When using शेष config, record which bits of attr->config were
	 * changed by the user.
	 */
	अगर (pmu->शेष_config && get_config_chgs(pmu, head_config, &config_terms))
		वापस -ENOMEM;

	अगर (!parse_events__inside_hybrid_pmu(parse_state, list, name,
					     head_config)) अणु
		वापस 0;
	पूर्ण

	अगर (!parse_state->fake_pmu && perf_pmu__config(pmu, &attr, head_config, parse_state->error)) अणु
		काष्ठा evsel_config_term *pos, *पंचांगp;

		list_क्रम_each_entry_safe(pos, पंचांगp, &config_terms, list) अणु
			list_del_init(&pos->list);
			अगर (pos->मुक्त_str)
				zमुक्त(&pos->val.str);
			मुक्त(pos);
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	evsel = __add_event(list, &parse_state->idx, &attr, true,
			    get_config_name(head_config), pmu,
			    &config_terms, स्वतः_merge_stats, शून्य);
	अगर (!evsel)
		वापस -ENOMEM;

	अगर (evsel->name)
		evsel->use_config_name = true;

	evsel->pmu_name = name ? strdup(name) : शून्य;
	evsel->use_uncore_alias = use_uncore_alias;
	evsel->percore = config_term_percore(&evsel->config_terms);

	अगर (parse_state->fake_pmu)
		वापस 0;

	evsel->unit = info.unit;
	evsel->scale = info.scale;
	evsel->per_pkg = info.per_pkg;
	evsel->snapshot = info.snapshot;
	evsel->metric_expr = info.metric_expr;
	evsel->metric_name = info.metric_name;
	वापस 0;
पूर्ण

पूर्णांक parse_events_multi_pmu_add(काष्ठा parse_events_state *parse_state,
			       अक्षर *str, काष्ठा list_head **listp)
अणु
	काष्ठा parse_events_term *term;
	काष्ठा list_head *list;
	काष्ठा perf_pmu *pmu = शून्य;
	पूर्णांक ok = 0;

	*listp = शून्य;
	/* Add it क्रम all PMUs that support the alias */
	list = दो_स्मृति(माप(काष्ठा list_head));
	अगर (!list)
		वापस -1;
	INIT_LIST_HEAD(list);
	जबतक ((pmu = perf_pmu__scan(pmu)) != शून्य) अणु
		काष्ठा perf_pmu_alias *alias;

		list_क्रम_each_entry(alias, &pmu->aliases, list) अणु
			अगर (!strहालcmp(alias->name, str)) अणु
				काष्ठा list_head *head;
				अक्षर *config;

				head = दो_स्मृति(माप(काष्ठा list_head));
				अगर (!head)
					वापस -1;
				INIT_LIST_HEAD(head);
				config = strdup(str);
				अगर (!config)
					वापस -1;
				अगर (parse_events_term__num(&term,
						   PARSE_EVENTS__TERM_TYPE_USER,
						   config, 1, false, &config,
						   शून्य) < 0) अणु
					मुक्त(list);
					मुक्त(config);
					वापस -1;
				पूर्ण
				list_add_tail(&term->list, head);

				अगर (!parse_events_add_pmu(parse_state, list,
							  pmu->name, head,
							  true, true)) अणु
					pr_debug("%s -> %s/%s/\n", str,
						 pmu->name, alias->str);
					ok++;
				पूर्ण

				parse_events_terms__delete(head);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!ok) अणु
		मुक्त(list);
		वापस -1;
	पूर्ण
	*listp = list;
	वापस 0;
पूर्ण

पूर्णांक parse_events__modअगरier_group(काष्ठा list_head *list,
				 अक्षर *event_mod)
अणु
	वापस parse_events__modअगरier_event(list, event_mod, true);
पूर्ण

/*
 * Check अगर the two uncore PMUs are from the same uncore block
 * The क्रमmat of the uncore PMU name is uncore_#blockname_#pmuidx
 */
अटल bool is_same_uncore_block(स्थिर अक्षर *pmu_name_a, स्थिर अक्षर *pmu_name_b)
अणु
	अक्षर *end_a, *end_b;

	end_a = म_खोजप(pmu_name_a, '_');
	end_b = म_खोजप(pmu_name_b, '_');

	अगर (!end_a || !end_b)
		वापस false;

	अगर ((end_a - pmu_name_a) != (end_b - pmu_name_b))
		वापस false;

	वापस (म_भेदन(pmu_name_a, pmu_name_b, end_a - pmu_name_a) == 0);
पूर्ण

अटल पूर्णांक
parse_events__set_leader_क्रम_uncore_aliase(अक्षर *name, काष्ठा list_head *list,
					   काष्ठा parse_events_state *parse_state)
अणु
	काष्ठा evsel *evsel, *leader;
	uपूर्णांकptr_t *leaders;
	bool is_leader = true;
	पूर्णांक i, nr_pmu = 0, total_members, ret = 0;

	leader = list_first_entry(list, काष्ठा evsel, core.node);
	evsel = list_last_entry(list, काष्ठा evsel, core.node);
	total_members = evsel->idx - leader->idx + 1;

	leaders = सुस्मृति(total_members, माप(uपूर्णांकptr_t));
	अगर (WARN_ON(!leaders))
		वापस 0;

	/*
	 * Going through the whole group and करोing sanity check.
	 * All members must use alias, and be from the same uncore block.
	 * Also, storing the leader events in an array.
	 */
	__evlist__क्रम_each_entry(list, evsel) अणु

		/* Only split the uncore group which members use alias */
		अगर (!evsel->use_uncore_alias)
			जाओ out;

		/* The events must be from the same uncore block */
		अगर (!is_same_uncore_block(leader->pmu_name, evsel->pmu_name))
			जाओ out;

		अगर (!is_leader)
			जारी;
		/*
		 * If the event's PMU name starts to repeat, it must be a new
		 * event. That can be used to distinguish the leader from
		 * other members, even they have the same event name.
		 */
		अगर ((leader != evsel) &&
		    !म_भेद(leader->pmu_name, evsel->pmu_name)) अणु
			is_leader = false;
			जारी;
		पूर्ण

		/* Store the leader event क्रम each PMU */
		leaders[nr_pmu++] = (uपूर्णांकptr_t) evsel;
	पूर्ण

	/* only one event alias */
	अगर (nr_pmu == total_members) अणु
		parse_state->nr_groups--;
		जाओ handled;
	पूर्ण

	/*
	 * An uncore event alias is a joपूर्णांक name which means the same event
	 * runs on all PMUs of a block.
	 * Perf करोesn't support mixed events from dअगरferent PMUs in the same
	 * group. The big group has to be split पूर्णांकo multiple small groups
	 * which only include the events from the same PMU.
	 *
	 * Here the uncore event aliases must be from the same uncore block.
	 * The number of PMUs must be same क्रम each alias. The number of new
	 * small groups equals to the number of PMUs.
	 * Setting the leader event क्रम corresponding members in each group.
	 */
	i = 0;
	__evlist__क्रम_each_entry(list, evsel) अणु
		अगर (i >= nr_pmu)
			i = 0;
		evsel->leader = (काष्ठा evsel *) leaders[i++];
	पूर्ण

	/* The number of members and group name are same क्रम each group */
	क्रम (i = 0; i < nr_pmu; i++) अणु
		evsel = (काष्ठा evsel *) leaders[i];
		evsel->core.nr_members = total_members / nr_pmu;
		evsel->group_name = name ? strdup(name) : शून्य;
	पूर्ण

	/* Take the new small groups पूर्णांकo account */
	parse_state->nr_groups += nr_pmu - 1;

handled:
	ret = 1;
out:
	मुक्त(leaders);
	वापस ret;
पूर्ण

व्योम parse_events__set_leader(अक्षर *name, काष्ठा list_head *list,
			      काष्ठा parse_events_state *parse_state)
अणु
	काष्ठा evsel *leader;

	अगर (list_empty(list)) अणु
		WARN_ONCE(true, "WARNING: failed to set leader: empty list");
		वापस;
	पूर्ण

	अगर (parse_events__set_leader_क्रम_uncore_aliase(name, list, parse_state))
		वापस;

	__evlist__set_leader(list);
	leader = list_entry(list->next, काष्ठा evsel, core.node);
	leader->group_name = name ? strdup(name) : शून्य;
पूर्ण

/* list_event is assumed to poपूर्णांक to दो_स्मृति'ed memory */
व्योम parse_events_update_lists(काष्ठा list_head *list_event,
			       काष्ठा list_head *list_all)
अणु
	/*
	 * Called क्रम single event definition. Update the
	 * 'all event' list, and reinit the 'single event'
	 * list, क्रम next event definition.
	 */
	list_splice_tail(list_event, list_all);
	मुक्त(list_event);
पूर्ण

काष्ठा event_modअगरier अणु
	पूर्णांक eu;
	पूर्णांक ek;
	पूर्णांक eh;
	पूर्णांक eH;
	पूर्णांक eG;
	पूर्णांक eI;
	पूर्णांक precise;
	पूर्णांक precise_max;
	पूर्णांक exclude_GH;
	पूर्णांक sample_पढ़ो;
	पूर्णांक pinned;
	पूर्णांक weak;
	पूर्णांक exclusive;
	पूर्णांक bpf_counter;
पूर्ण;

अटल पूर्णांक get_event_modअगरier(काष्ठा event_modअगरier *mod, अक्षर *str,
			       काष्ठा evsel *evsel)
अणु
	पूर्णांक eu = evsel ? evsel->core.attr.exclude_user : 0;
	पूर्णांक ek = evsel ? evsel->core.attr.exclude_kernel : 0;
	पूर्णांक eh = evsel ? evsel->core.attr.exclude_hv : 0;
	पूर्णांक eH = evsel ? evsel->core.attr.exclude_host : 0;
	पूर्णांक eG = evsel ? evsel->core.attr.exclude_guest : 0;
	पूर्णांक eI = evsel ? evsel->core.attr.exclude_idle : 0;
	पूर्णांक precise = evsel ? evsel->core.attr.precise_ip : 0;
	पूर्णांक precise_max = 0;
	पूर्णांक sample_पढ़ो = 0;
	पूर्णांक pinned = evsel ? evsel->core.attr.pinned : 0;
	पूर्णांक exclusive = evsel ? evsel->core.attr.exclusive : 0;

	पूर्णांक exclude = eu | ek | eh;
	पूर्णांक exclude_GH = evsel ? evsel->exclude_GH : 0;
	पूर्णांक weak = 0;
	पूर्णांक bpf_counter = 0;

	स_रखो(mod, 0, माप(*mod));

	जबतक (*str) अणु
		अगर (*str == 'u') अणु
			अगर (!exclude)
				exclude = eu = ek = eh = 1;
			अगर (!exclude_GH && !perf_guest)
				eG = 1;
			eu = 0;
		पूर्ण अन्यथा अगर (*str == 'k') अणु
			अगर (!exclude)
				exclude = eu = ek = eh = 1;
			ek = 0;
		पूर्ण अन्यथा अगर (*str == 'h') अणु
			अगर (!exclude)
				exclude = eu = ek = eh = 1;
			eh = 0;
		पूर्ण अन्यथा अगर (*str == 'G') अणु
			अगर (!exclude_GH)
				exclude_GH = eG = eH = 1;
			eG = 0;
		पूर्ण अन्यथा अगर (*str == 'H') अणु
			अगर (!exclude_GH)
				exclude_GH = eG = eH = 1;
			eH = 0;
		पूर्ण अन्यथा अगर (*str == 'I') अणु
			eI = 1;
		पूर्ण अन्यथा अगर (*str == 'p') अणु
			precise++;
			/* use of precise requires exclude_guest */
			अगर (!exclude_GH)
				eG = 1;
		पूर्ण अन्यथा अगर (*str == 'P') अणु
			precise_max = 1;
		पूर्ण अन्यथा अगर (*str == 'S') अणु
			sample_पढ़ो = 1;
		पूर्ण अन्यथा अगर (*str == 'D') अणु
			pinned = 1;
		पूर्ण अन्यथा अगर (*str == 'e') अणु
			exclusive = 1;
		पूर्ण अन्यथा अगर (*str == 'W') अणु
			weak = 1;
		पूर्ण अन्यथा अगर (*str == 'b') अणु
			bpf_counter = 1;
		पूर्ण अन्यथा
			अवरोध;

		++str;
	पूर्ण

	/*
	 * precise ip:
	 *
	 *  0 - SAMPLE_IP can have arbitrary skid
	 *  1 - SAMPLE_IP must have स्थिरant skid
	 *  2 - SAMPLE_IP requested to have 0 skid
	 *  3 - SAMPLE_IP must have 0 skid
	 *
	 *  See also PERF_RECORD_MISC_EXACT_IP
	 */
	अगर (precise > 3)
		वापस -EINVAL;

	mod->eu = eu;
	mod->ek = ek;
	mod->eh = eh;
	mod->eH = eH;
	mod->eG = eG;
	mod->eI = eI;
	mod->precise = precise;
	mod->precise_max = precise_max;
	mod->exclude_GH = exclude_GH;
	mod->sample_पढ़ो = sample_पढ़ो;
	mod->pinned = pinned;
	mod->weak = weak;
	mod->bpf_counter = bpf_counter;
	mod->exclusive = exclusive;

	वापस 0;
पूर्ण

/*
 * Basic modअगरier sanity check to validate it contains only one
 * instance of any modअगरier (apart from 'p') present.
 */
अटल पूर्णांक check_modअगरier(अक्षर *str)
अणु
	अक्षर *p = str;

	/* The माप includes 0 byte as well. */
	अगर (म_माप(str) > (माप("ukhGHpppPSDIWeb") - 1))
		वापस -1;

	जबतक (*p) अणु
		अगर (*p != 'p' && म_अक्षर(p + 1, *p))
			वापस -1;
		p++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक parse_events__modअगरier_event(काष्ठा list_head *list, अक्षर *str, bool add)
अणु
	काष्ठा evsel *evsel;
	काष्ठा event_modअगरier mod;

	अगर (str == शून्य)
		वापस 0;

	अगर (check_modअगरier(str))
		वापस -EINVAL;

	अगर (!add && get_event_modअगरier(&mod, str, शून्य))
		वापस -EINVAL;

	__evlist__क्रम_each_entry(list, evsel) अणु
		अगर (add && get_event_modअगरier(&mod, str, evsel))
			वापस -EINVAL;

		evsel->core.attr.exclude_user   = mod.eu;
		evsel->core.attr.exclude_kernel = mod.ek;
		evsel->core.attr.exclude_hv     = mod.eh;
		evsel->core.attr.precise_ip     = mod.precise;
		evsel->core.attr.exclude_host   = mod.eH;
		evsel->core.attr.exclude_guest  = mod.eG;
		evsel->core.attr.exclude_idle   = mod.eI;
		evsel->exclude_GH          = mod.exclude_GH;
		evsel->sample_पढ़ो         = mod.sample_पढ़ो;
		evsel->precise_max         = mod.precise_max;
		evsel->weak_group	   = mod.weak;
		evsel->bpf_counter	   = mod.bpf_counter;

		अगर (evsel__is_group_leader(evsel)) अणु
			evsel->core.attr.pinned = mod.pinned;
			evsel->core.attr.exclusive = mod.exclusive;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक parse_events_name(काष्ठा list_head *list, अक्षर *name)
अणु
	काष्ठा evsel *evsel;

	__evlist__क्रम_each_entry(list, evsel) अणु
		अगर (!evsel->name)
			evsel->name = strdup(name);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
comp_pmu(स्थिर व्योम *p1, स्थिर व्योम *p2)
अणु
	काष्ठा perf_pmu_event_symbol *pmu1 = (काष्ठा perf_pmu_event_symbol *) p1;
	काष्ठा perf_pmu_event_symbol *pmu2 = (काष्ठा perf_pmu_event_symbol *) p2;

	वापस strहालcmp(pmu1->symbol, pmu2->symbol);
पूर्ण

अटल व्योम perf_pmu__parse_cleanup(व्योम)
अणु
	अगर (perf_pmu_events_list_num > 0) अणु
		काष्ठा perf_pmu_event_symbol *p;
		पूर्णांक i;

		क्रम (i = 0; i < perf_pmu_events_list_num; i++) अणु
			p = perf_pmu_events_list + i;
			zमुक्त(&p->symbol);
		पूर्ण
		zमुक्त(&perf_pmu_events_list);
		perf_pmu_events_list_num = 0;
	पूर्ण
पूर्ण

#घोषणा SET_SYMBOL(str, stype)		\
करो अणु					\
	p->symbol = str;		\
	अगर (!p->symbol)			\
		जाओ err;		\
	p->type = stype;		\
पूर्ण जबतक (0)

/*
 * Read the pmu events list from sysfs
 * Save it पूर्णांकo perf_pmu_events_list
 */
अटल व्योम perf_pmu__parse_init(व्योम)
अणु

	काष्ठा perf_pmu *pmu = शून्य;
	काष्ठा perf_pmu_alias *alias;
	पूर्णांक len = 0;

	pmu = शून्य;
	जबतक ((pmu = perf_pmu__scan(pmu)) != शून्य) अणु
		list_क्रम_each_entry(alias, &pmu->aliases, list) अणु
			अगर (म_अक्षर(alias->name, '-'))
				len++;
			len++;
		पूर्ण
	पूर्ण

	अगर (len == 0) अणु
		perf_pmu_events_list_num = -1;
		वापस;
	पूर्ण
	perf_pmu_events_list = दो_स्मृति(माप(काष्ठा perf_pmu_event_symbol) * len);
	अगर (!perf_pmu_events_list)
		वापस;
	perf_pmu_events_list_num = len;

	len = 0;
	pmu = शून्य;
	जबतक ((pmu = perf_pmu__scan(pmu)) != शून्य) अणु
		list_क्रम_each_entry(alias, &pmu->aliases, list) अणु
			काष्ठा perf_pmu_event_symbol *p = perf_pmu_events_list + len;
			अक्षर *पंचांगp = म_अक्षर(alias->name, '-');

			अगर (पंचांगp != शून्य) अणु
				SET_SYMBOL(strndup(alias->name, पंचांगp - alias->name),
						PMU_EVENT_SYMBOL_PREFIX);
				p++;
				SET_SYMBOL(strdup(++पंचांगp), PMU_EVENT_SYMBOL_SUFFIX);
				len += 2;
			पूर्ण अन्यथा अणु
				SET_SYMBOL(strdup(alias->name), PMU_EVENT_SYMBOL);
				len++;
			पूर्ण
		पूर्ण
	पूर्ण
	क्विक(perf_pmu_events_list, len,
		माप(काष्ठा perf_pmu_event_symbol), comp_pmu);

	वापस;
err:
	perf_pmu__parse_cleanup();
पूर्ण

/*
 * This function injects special term in
 * perf_pmu_events_list so the test code
 * can check on this functionality.
 */
पूर्णांक perf_pmu__test_parse_init(व्योम)
अणु
	काष्ठा perf_pmu_event_symbol *list;

	list = दो_स्मृति(माप(*list) * 1);
	अगर (!list)
		वापस -ENOMEM;

	list->type   = PMU_EVENT_SYMBOL;
	list->symbol = strdup("read");

	अगर (!list->symbol) अणु
		मुक्त(list);
		वापस -ENOMEM;
	पूर्ण

	perf_pmu_events_list = list;
	perf_pmu_events_list_num = 1;
	वापस 0;
पूर्ण

क्रमागत perf_pmu_event_symbol_type
perf_pmu__parse_check(स्थिर अक्षर *name)
अणु
	काष्ठा perf_pmu_event_symbol p, *r;

	/* scan kernel pmu events from sysfs अगर needed */
	अगर (perf_pmu_events_list_num == 0)
		perf_pmu__parse_init();
	/*
	 * name "cpu" could be prefix of cpu-cycles or cpu// events.
	 * cpu-cycles has been handled by hardcode.
	 * So it must be cpu// events, not kernel pmu event.
	 */
	अगर ((perf_pmu_events_list_num <= 0) || !म_भेद(name, "cpu"))
		वापस PMU_EVENT_SYMBOL_ERR;

	p.symbol = strdup(name);
	r = द्वा_खोज(&p, perf_pmu_events_list,
			(माप_प्रकार) perf_pmu_events_list_num,
			माप(काष्ठा perf_pmu_event_symbol), comp_pmu);
	zमुक्त(&p.symbol);
	वापस r ? r->type : PMU_EVENT_SYMBOL_ERR;
पूर्ण

अटल पूर्णांक parse_events__scanner(स्थिर अक्षर *str,
				 काष्ठा parse_events_state *parse_state)
अणु
	YY_BUFFER_STATE buffer;
	व्योम *scanner;
	पूर्णांक ret;

	ret = parse_events_lex_init_extra(parse_state, &scanner);
	अगर (ret)
		वापस ret;

	buffer = parse_events__scan_string(str, scanner);

#अगर_घोषित PARSER_DEBUG
	parse_events_debug = 1;
	parse_events_set_debug(1, scanner);
#पूर्ण_अगर
	ret = parse_events_parse(parse_state, scanner);

	parse_events__flush_buffer(buffer, scanner);
	parse_events__delete_buffer(buffer, scanner);
	parse_events_lex_destroy(scanner);
	वापस ret;
पूर्ण

/*
 * parse event config string, वापस a list of event terms.
 */
पूर्णांक parse_events_terms(काष्ठा list_head *terms, स्थिर अक्षर *str)
अणु
	काष्ठा parse_events_state parse_state = अणु
		.terms  = शून्य,
		.stoken = PE_START_TERMS,
	पूर्ण;
	पूर्णांक ret;

	ret = parse_events__scanner(str, &parse_state);
	perf_pmu__parse_cleanup();

	अगर (!ret) अणु
		list_splice(parse_state.terms, terms);
		zमुक्त(&parse_state.terms);
		वापस 0;
	पूर्ण

	parse_events_terms__delete(parse_state.terms);
	वापस ret;
पूर्ण

अटल पूर्णांक parse_events__with_hybrid_pmu(काष्ठा parse_events_state *parse_state,
					 स्थिर अक्षर *str, अक्षर *pmu_name,
					 काष्ठा list_head *list)
अणु
	काष्ठा parse_events_state ps = अणु
		.list            = LIST_HEAD_INIT(ps.list),
		.stoken          = PE_START_EVENTS,
		.hybrid_pmu_name = pmu_name,
		.idx             = parse_state->idx,
	पूर्ण;
	पूर्णांक ret;

	ret = parse_events__scanner(str, &ps);
	perf_pmu__parse_cleanup();

	अगर (!ret) अणु
		अगर (!list_empty(&ps.list)) अणु
			list_splice(&ps.list, list);
			parse_state->idx = ps.idx;
			वापस 0;
		पूर्ण अन्यथा
			वापस -1;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक __parse_events(काष्ठा evlist *evlist, स्थिर अक्षर *str,
		   काष्ठा parse_events_error *err, काष्ठा perf_pmu *fake_pmu)
अणु
	काष्ठा parse_events_state parse_state = अणु
		.list	  = LIST_HEAD_INIT(parse_state.list),
		.idx	  = evlist->core.nr_entries,
		.error	  = err,
		.evlist	  = evlist,
		.stoken	  = PE_START_EVENTS,
		.fake_pmu = fake_pmu,
	पूर्ण;
	पूर्णांक ret;

	ret = parse_events__scanner(str, &parse_state);
	perf_pmu__parse_cleanup();

	अगर (!ret && list_empty(&parse_state.list)) अणु
		WARN_ONCE(true, "WARNING: event parser found nothing\n");
		वापस -1;
	पूर्ण

	/*
	 * Add list to the evlist even with errors to allow callers to clean up.
	 */
	evlist__splice_list_tail(evlist, &parse_state.list);

	अगर (!ret) अणु
		काष्ठा evsel *last;

		evlist->nr_groups += parse_state.nr_groups;
		last = evlist__last(evlist);
		last->cmdline_group_boundary = true;

		वापस 0;
	पूर्ण

	/*
	 * There are 2 users - builtin-record and builtin-test objects.
	 * Both call evlist__delete in हाल of error, so we करोnt
	 * need to bother.
	 */
	वापस ret;
पूर्ण

#घोषणा MAX_WIDTH 1000
अटल पूर्णांक get_term_width(व्योम)
अणु
	काष्ठा winsize ws;

	get_term_dimensions(&ws);
	वापस ws.ws_col > MAX_WIDTH ? MAX_WIDTH : ws.ws_col;
पूर्ण

अटल व्योम __parse_events_prपूर्णांक_error(पूर्णांक err_idx, स्थिर अक्षर *err_str,
				स्थिर अक्षर *err_help, स्थिर अक्षर *event)
अणु
	स्थिर अक्षर *str = "invalid or unsupported event: ";
	अक्षर _buf[MAX_WIDTH];
	अक्षर *buf = (अक्षर *) event;
	पूर्णांक idx = 0;
	अगर (err_str) अणु
		/* -2 क्रम extra '' in the final ख_लिखो */
		पूर्णांक width       = get_term_width() - 2;
		पूर्णांक len_event   = म_माप(event);
		पूर्णांक len_str, max_len, cut = 0;

		/*
		 * Maximum error index indent, we will cut
		 * the event string अगर it's bigger.
		 */
		पूर्णांक max_err_idx = 13;

		/*
		 * Let's be specअगरic with the message when
		 * we have the precise error.
		 */
		str     = "event syntax error: ";
		len_str = म_माप(str);
		max_len = width - len_str;

		buf = _buf;

		/* We're cutting from the beginning. */
		अगर (err_idx > max_err_idx)
			cut = err_idx - max_err_idx;

		म_नकलन(buf, event + cut, max_len);

		/* Mark cut parts with '..' on both sides. */
		अगर (cut)
			buf[0] = buf[1] = '.';

		अगर ((len_event - cut) > max_len) अणु
			buf[max_len - 1] = buf[max_len - 2] = '.';
			buf[max_len] = 0;
		पूर्ण

		idx = len_str + err_idx - cut;
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "%s'%s'\n", str, buf);
	अगर (idx) अणु
		ख_लिखो(मानक_त्रुटि, "%*s\\___ %s\n", idx + 1, "", err_str);
		अगर (err_help)
			ख_लिखो(मानक_त्रुटि, "\n%s\n", err_help);
	पूर्ण
पूर्ण

व्योम parse_events_prपूर्णांक_error(काष्ठा parse_events_error *err,
			      स्थिर अक्षर *event)
अणु
	अगर (!err->num_errors)
		वापस;

	__parse_events_prपूर्णांक_error(err->idx, err->str, err->help, event);
	zमुक्त(&err->str);
	zमुक्त(&err->help);

	अगर (err->num_errors > 1) अणु
		ख_माला_दो("\nInitial error:\n", मानक_त्रुटि);
		__parse_events_prपूर्णांक_error(err->first_idx, err->first_str,
					err->first_help, event);
		zमुक्त(&err->first_str);
		zमुक्त(&err->first_help);
	पूर्ण
पूर्ण

#अघोषित MAX_WIDTH

पूर्णांक parse_events_option(स्थिर काष्ठा option *opt, स्थिर अक्षर *str,
			पूर्णांक unset __maybe_unused)
अणु
	काष्ठा evlist *evlist = *(काष्ठा evlist **)opt->value;
	काष्ठा parse_events_error err;
	पूर्णांक ret;

	bzero(&err, माप(err));
	ret = parse_events(evlist, str, &err);

	अगर (ret) अणु
		parse_events_prपूर्णांक_error(&err, str);
		ख_लिखो(मानक_त्रुटि, "Run 'perf list' for a list of valid events\n");
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक parse_events_option_new_evlist(स्थिर काष्ठा option *opt, स्थिर अक्षर *str, पूर्णांक unset)
अणु
	काष्ठा evlist **evlistp = opt->value;
	पूर्णांक ret;

	अगर (*evlistp == शून्य) अणु
		*evlistp = evlist__new();

		अगर (*evlistp == शून्य) अणु
			ख_लिखो(मानक_त्रुटि, "Not enough memory to create evlist\n");
			वापस -1;
		पूर्ण
	पूर्ण

	ret = parse_events_option(opt, str, unset);
	अगर (ret) अणु
		evlist__delete(*evlistp);
		*evlistp = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
क्रमeach_evsel_in_last_glob(काष्ठा evlist *evlist,
			   पूर्णांक (*func)(काष्ठा evsel *evsel,
				       स्थिर व्योम *arg),
			   स्थिर व्योम *arg)
अणु
	काष्ठा evsel *last = शून्य;
	पूर्णांक err;

	/*
	 * Don't वापस when list_empty, give func a chance to report
	 * error when it found last == शून्य.
	 *
	 * So no need to WARN here, let *func करो this.
	 */
	अगर (evlist->core.nr_entries > 0)
		last = evlist__last(evlist);

	करो अणु
		err = (*func)(last, arg);
		अगर (err)
			वापस -1;
		अगर (!last)
			वापस 0;

		अगर (last->core.node.prev == &evlist->core.entries)
			वापस 0;
		last = list_entry(last->core.node.prev, काष्ठा evsel, core.node);
	पूर्ण जबतक (!last->cmdline_group_boundary);

	वापस 0;
पूर्ण

अटल पूर्णांक set_filter(काष्ठा evsel *evsel, स्थिर व्योम *arg)
अणु
	स्थिर अक्षर *str = arg;
	bool found = false;
	पूर्णांक nr_addr_filters = 0;
	काष्ठा perf_pmu *pmu = शून्य;

	अगर (evsel == शून्य) अणु
		ख_लिखो(मानक_त्रुटि,
			"--filter option should follow a -e tracepoint or HW tracer option\n");
		वापस -1;
	पूर्ण

	अगर (evsel->core.attr.type == PERF_TYPE_TRACEPOINT) अणु
		अगर (evsel__append_tp_filter(evsel, str) < 0) अणु
			ख_लिखो(मानक_त्रुटि,
				"not enough memory to hold filter string\n");
			वापस -1;
		पूर्ण

		वापस 0;
	पूर्ण

	जबतक ((pmu = perf_pmu__scan(pmu)) != शून्य)
		अगर (pmu->type == evsel->core.attr.type) अणु
			found = true;
			अवरोध;
		पूर्ण

	अगर (found)
		perf_pmu__scan_file(pmu, "nr_addr_filters",
				    "%d", &nr_addr_filters);

	अगर (!nr_addr_filters) अणु
		ख_लिखो(मानक_त्रुटि,
			"This CPU does not support address filtering\n");
		वापस -1;
	पूर्ण

	अगर (evsel__append_addr_filter(evsel, str) < 0) अणु
		ख_लिखो(मानक_त्रुटि,
			"not enough memory to hold filter string\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक parse_filter(स्थिर काष्ठा option *opt, स्थिर अक्षर *str,
		 पूर्णांक unset __maybe_unused)
अणु
	काष्ठा evlist *evlist = *(काष्ठा evlist **)opt->value;

	वापस क्रमeach_evsel_in_last_glob(evlist, set_filter,
					  (स्थिर व्योम *)str);
पूर्ण

अटल पूर्णांक add_exclude_perf_filter(काष्ठा evsel *evsel,
				   स्थिर व्योम *arg __maybe_unused)
अणु
	अक्षर new_filter[64];

	अगर (evsel == शून्य || evsel->core.attr.type != PERF_TYPE_TRACEPOINT) अणु
		ख_लिखो(मानक_त्रुटि,
			"--exclude-perf option should follow a -e tracepoint option\n");
		वापस -1;
	पूर्ण

	snम_लिखो(new_filter, माप(new_filter), "common_pid != %d", getpid());

	अगर (evsel__append_tp_filter(evsel, new_filter) < 0) अणु
		ख_लिखो(मानक_त्रुटि,
			"not enough memory to hold filter string\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक exclude_perf(स्थिर काष्ठा option *opt,
		 स्थिर अक्षर *arg __maybe_unused,
		 पूर्णांक unset __maybe_unused)
अणु
	काष्ठा evlist *evlist = *(काष्ठा evlist **)opt->value;

	वापस क्रमeach_evsel_in_last_glob(evlist, add_exclude_perf_filter,
					  शून्य);
पूर्ण

अटल स्थिर अक्षर * स्थिर event_type_descriptors[] = अणु
	"Hardware event",
	"Software event",
	"Tracepoint event",
	"Hardware cache event",
	"Raw hardware event descriptor",
	"Hardware breakpoint",
पूर्ण;

अटल पूर्णांक cmp_string(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर अक्षर * स्थिर *as = a;
	स्थिर अक्षर * स्थिर *bs = b;

	वापस म_भेद(*as, *bs);
पूर्ण

/*
 * Prपूर्णांक the events from <debugfs_mount_poपूर्णांक>/tracing/events
 */

व्योम prपूर्णांक_tracepoपूर्णांक_events(स्थिर अक्षर *subsys_glob, स्थिर अक्षर *event_glob,
			     bool name_only)
अणु
	सूची *sys_dir, *evt_dir;
	काष्ठा dirent *sys_dirent, *evt_dirent;
	अक्षर evt_path[MAXPATHLEN];
	अक्षर *dir_path;
	अक्षर **evt_list = शून्य;
	अचिन्हित पूर्णांक evt_i = 0, evt_num = 0;
	bool evt_num_known = false;

restart:
	sys_dir = tracing_events__सूची_खोलो();
	अगर (!sys_dir)
		वापस;

	अगर (evt_num_known) अणु
		evt_list = zalloc(माप(अक्षर *) * evt_num);
		अगर (!evt_list)
			जाओ out_बंद_sys_dir;
	पूर्ण

	क्रम_each_subप्रणाली(sys_dir, sys_dirent) अणु
		अगर (subsys_glob != शून्य &&
		    !strglobmatch(sys_dirent->d_name, subsys_glob))
			जारी;

		dir_path = get_events_file(sys_dirent->d_name);
		अगर (!dir_path)
			जारी;
		evt_dir = सूची_खोलो(dir_path);
		अगर (!evt_dir)
			जाओ next;

		क्रम_each_event(dir_path, evt_dir, evt_dirent) अणु
			अगर (event_glob != शून्य &&
			    !strglobmatch(evt_dirent->d_name, event_glob))
				जारी;

			अगर (!evt_num_known) अणु
				evt_num++;
				जारी;
			पूर्ण

			snम_लिखो(evt_path, MAXPATHLEN, "%s:%s",
				 sys_dirent->d_name, evt_dirent->d_name);

			evt_list[evt_i] = strdup(evt_path);
			अगर (evt_list[evt_i] == शून्य) अणु
				put_events_file(dir_path);
				जाओ out_बंद_evt_dir;
			पूर्ण
			evt_i++;
		पूर्ण
		बंद_सूची(evt_dir);
next:
		put_events_file(dir_path);
	पूर्ण
	बंद_सूची(sys_dir);

	अगर (!evt_num_known) अणु
		evt_num_known = true;
		जाओ restart;
	पूर्ण
	क्विक(evt_list, evt_num, माप(अक्षर *), cmp_string);
	evt_i = 0;
	जबतक (evt_i < evt_num) अणु
		अगर (name_only) अणु
			म_लिखो("%s ", evt_list[evt_i++]);
			जारी;
		पूर्ण
		म_लिखो("  %-50s [%s]\n", evt_list[evt_i++],
				event_type_descriptors[PERF_TYPE_TRACEPOINT]);
	पूर्ण
	अगर (evt_num && pager_in_use())
		म_लिखो("\n");

out_मुक्त:
	evt_num = evt_i;
	क्रम (evt_i = 0; evt_i < evt_num; evt_i++)
		zमुक्त(&evt_list[evt_i]);
	zमुक्त(&evt_list);
	वापस;

out_बंद_evt_dir:
	बंद_सूची(evt_dir);
out_बंद_sys_dir:
	बंद_सूची(sys_dir);

	म_लिखो("FATAL: not enough memory to print %s\n",
			event_type_descriptors[PERF_TYPE_TRACEPOINT]);
	अगर (evt_list)
		जाओ out_मुक्त;
पूर्ण

/*
 * Check whether event is in <debugfs_mount_poपूर्णांक>/tracing/events
 */

पूर्णांक is_valid_tracepoपूर्णांक(स्थिर अक्षर *event_string)
अणु
	सूची *sys_dir, *evt_dir;
	काष्ठा dirent *sys_dirent, *evt_dirent;
	अक्षर evt_path[MAXPATHLEN];
	अक्षर *dir_path;

	sys_dir = tracing_events__सूची_खोलो();
	अगर (!sys_dir)
		वापस 0;

	क्रम_each_subप्रणाली(sys_dir, sys_dirent) अणु
		dir_path = get_events_file(sys_dirent->d_name);
		अगर (!dir_path)
			जारी;
		evt_dir = सूची_खोलो(dir_path);
		अगर (!evt_dir)
			जाओ next;

		क्रम_each_event(dir_path, evt_dir, evt_dirent) अणु
			snम_लिखो(evt_path, MAXPATHLEN, "%s:%s",
				 sys_dirent->d_name, evt_dirent->d_name);
			अगर (!म_भेद(evt_path, event_string)) अणु
				बंद_सूची(evt_dir);
				बंद_सूची(sys_dir);
				वापस 1;
			पूर्ण
		पूर्ण
		बंद_सूची(evt_dir);
next:
		put_events_file(dir_path);
	पूर्ण
	बंद_सूची(sys_dir);
	वापस 0;
पूर्ण

अटल bool is_event_supported(u8 type, अचिन्हित config)
अणु
	bool ret = true;
	पूर्णांक खोलो_वापस;
	काष्ठा evsel *evsel;
	काष्ठा perf_event_attr attr = अणु
		.type = type,
		.config = config,
		.disabled = 1,
	पूर्ण;
	काष्ठा perf_thपढ़ो_map *पंचांगap = thपढ़ो_map__new_by_tid(0);

	अगर (पंचांगap == शून्य)
		वापस false;

	evsel = evsel__new(&attr);
	अगर (evsel) अणु
		खोलो_वापस = evsel__खोलो(evsel, शून्य, पंचांगap);
		ret = खोलो_वापस >= 0;

		अगर (खोलो_वापस == -EACCES) अणु
			/*
			 * This happens अगर the paranoid value
			 * /proc/sys/kernel/perf_event_paranoid is set to 2
			 * Re-run with exclude_kernel set; we करोn't करो that
			 * by शेष as some ARM machines करो not support it.
			 *
			 */
			evsel->core.attr.exclude_kernel = 1;
			ret = evsel__खोलो(evsel, शून्य, पंचांगap) >= 0;
		पूर्ण
		evsel__delete(evsel);
	पूर्ण

	perf_thपढ़ो_map__put(पंचांगap);
	वापस ret;
पूर्ण

व्योम prपूर्णांक_sdt_events(स्थिर अक्षर *subsys_glob, स्थिर अक्षर *event_glob,
		      bool name_only)
अणु
	काष्ठा probe_cache *pcache;
	काष्ठा probe_cache_entry *ent;
	काष्ठा strlist *bidlist, *sdtlist;
	काष्ठा strlist_config cfg = अणु.करोnt_dupstr = trueपूर्ण;
	काष्ठा str_node *nd, *nd2;
	अक्षर *buf, *path, *ptr = शून्य;
	bool show_detail = false;
	पूर्णांक ret;

	sdtlist = strlist__new(शून्य, &cfg);
	अगर (!sdtlist) अणु
		pr_debug("Failed to allocate new strlist for SDT\n");
		वापस;
	पूर्ण
	bidlist = build_id_cache__list_all(true);
	अगर (!bidlist) अणु
		pr_debug("Failed to get buildids: %d\n", त्रुटि_सं);
		वापस;
	पूर्ण
	strlist__क्रम_each_entry(nd, bidlist) अणु
		pcache = probe_cache__new(nd->s, शून्य);
		अगर (!pcache)
			जारी;
		list_क्रम_each_entry(ent, &pcache->entries, node) अणु
			अगर (!ent->sdt)
				जारी;
			अगर (subsys_glob &&
			    !strglobmatch(ent->pev.group, subsys_glob))
				जारी;
			अगर (event_glob &&
			    !strglobmatch(ent->pev.event, event_glob))
				जारी;
			ret = aप्र_लिखो(&buf, "%s:%s@%s", ent->pev.group,
					ent->pev.event, nd->s);
			अगर (ret > 0)
				strlist__add(sdtlist, buf);
		पूर्ण
		probe_cache__delete(pcache);
	पूर्ण
	strlist__delete(bidlist);

	strlist__क्रम_each_entry(nd, sdtlist) अणु
		buf = म_अक्षर(nd->s, '@');
		अगर (buf)
			*(buf++) = '\0';
		अगर (name_only) अणु
			म_लिखो("%s ", nd->s);
			जारी;
		पूर्ण
		nd2 = strlist__next(nd);
		अगर (nd2) अणु
			ptr = म_अक्षर(nd2->s, '@');
			अगर (ptr)
				*ptr = '\0';
			अगर (म_भेद(nd->s, nd2->s) == 0)
				show_detail = true;
		पूर्ण
		अगर (show_detail) अणु
			path = build_id_cache__origname(buf);
			ret = aप्र_लिखो(&buf, "%s@%s(%.12s)", nd->s, path, buf);
			अगर (ret > 0) अणु
				म_लिखो("  %-50s [%s]\n", buf, "SDT event");
				मुक्त(buf);
			पूर्ण
			मुक्त(path);
		पूर्ण अन्यथा
			म_लिखो("  %-50s [%s]\n", nd->s, "SDT event");
		अगर (nd2) अणु
			अगर (म_भेद(nd->s, nd2->s) != 0)
				show_detail = false;
			अगर (ptr)
				*ptr = '@';
		पूर्ण
	पूर्ण
	strlist__delete(sdtlist);
पूर्ण

पूर्णांक prपूर्णांक_hwcache_events(स्थिर अक्षर *event_glob, bool name_only)
अणु
	अचिन्हित पूर्णांक type, op, i, evt_i = 0, evt_num = 0;
	अक्षर name[64];
	अक्षर **evt_list = शून्य;
	bool evt_num_known = false;

restart:
	अगर (evt_num_known) अणु
		evt_list = zalloc(माप(अक्षर *) * evt_num);
		अगर (!evt_list)
			जाओ out_enomem;
	पूर्ण

	क्रम (type = 0; type < PERF_COUNT_HW_CACHE_MAX; type++) अणु
		क्रम (op = 0; op < PERF_COUNT_HW_CACHE_OP_MAX; op++) अणु
			/* skip invalid cache type */
			अगर (!evsel__is_cache_op_valid(type, op))
				जारी;

			क्रम (i = 0; i < PERF_COUNT_HW_CACHE_RESULT_MAX; i++) अणु
				__evsel__hw_cache_type_op_res_name(type, op, i, name, माप(name));
				अगर (event_glob != शून्य && !strglobmatch(name, event_glob))
					जारी;

				अगर (!is_event_supported(PERF_TYPE_HW_CACHE,
							type | (op << 8) | (i << 16)))
					जारी;

				अगर (!evt_num_known) अणु
					evt_num++;
					जारी;
				पूर्ण

				evt_list[evt_i] = strdup(name);
				अगर (evt_list[evt_i] == शून्य)
					जाओ out_enomem;
				evt_i++;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!evt_num_known) अणु
		evt_num_known = true;
		जाओ restart;
	पूर्ण
	क्विक(evt_list, evt_num, माप(अक्षर *), cmp_string);
	evt_i = 0;
	जबतक (evt_i < evt_num) अणु
		अगर (name_only) अणु
			म_लिखो("%s ", evt_list[evt_i++]);
			जारी;
		पूर्ण
		म_लिखो("  %-50s [%s]\n", evt_list[evt_i++],
				event_type_descriptors[PERF_TYPE_HW_CACHE]);
	पूर्ण
	अगर (evt_num && pager_in_use())
		म_लिखो("\n");

out_मुक्त:
	evt_num = evt_i;
	क्रम (evt_i = 0; evt_i < evt_num; evt_i++)
		zमुक्त(&evt_list[evt_i]);
	zमुक्त(&evt_list);
	वापस evt_num;

out_enomem:
	म_लिखो("FATAL: not enough memory to print %s\n", event_type_descriptors[PERF_TYPE_HW_CACHE]);
	अगर (evt_list)
		जाओ out_मुक्त;
	वापस evt_num;
पूर्ण

अटल व्योम prपूर्णांक_tool_event(स्थिर अक्षर *name, स्थिर अक्षर *event_glob,
			     bool name_only)
अणु
	अगर (event_glob && !strglobmatch(name, event_glob))
		वापस;
	अगर (name_only)
		म_लिखो("%s ", name);
	अन्यथा
		म_लिखो("  %-50s [%s]\n", name, "Tool event");

पूर्ण

व्योम prपूर्णांक_tool_events(स्थिर अक्षर *event_glob, bool name_only)
अणु
	prपूर्णांक_tool_event("duration_time", event_glob, name_only);
	अगर (pager_in_use())
		म_लिखो("\n");
पूर्ण

व्योम prपूर्णांक_symbol_events(स्थिर अक्षर *event_glob, अचिन्हित type,
				काष्ठा event_symbol *syms, अचिन्हित max,
				bool name_only)
अणु
	अचिन्हित पूर्णांक i, evt_i = 0, evt_num = 0;
	अक्षर name[MAX_NAME_LEN];
	अक्षर **evt_list = शून्य;
	bool evt_num_known = false;

restart:
	अगर (evt_num_known) अणु
		evt_list = zalloc(माप(अक्षर *) * evt_num);
		अगर (!evt_list)
			जाओ out_enomem;
		syms -= max;
	पूर्ण

	क्रम (i = 0; i < max; i++, syms++) अणु
		/*
		 * New attr.config still not supported here, the latest
		 * example was PERF_COUNT_SW_CGROUP_SWITCHES
		 */
		अगर (syms->symbol == शून्य)
			जारी;

		अगर (event_glob != शून्य && !(strglobmatch(syms->symbol, event_glob) ||
		      (syms->alias && strglobmatch(syms->alias, event_glob))))
			जारी;

		अगर (!is_event_supported(type, i))
			जारी;

		अगर (!evt_num_known) अणु
			evt_num++;
			जारी;
		पूर्ण

		अगर (!name_only && म_माप(syms->alias))
			snम_लिखो(name, MAX_NAME_LEN, "%s OR %s", syms->symbol, syms->alias);
		अन्यथा
			strlcpy(name, syms->symbol, MAX_NAME_LEN);

		evt_list[evt_i] = strdup(name);
		अगर (evt_list[evt_i] == शून्य)
			जाओ out_enomem;
		evt_i++;
	पूर्ण

	अगर (!evt_num_known) अणु
		evt_num_known = true;
		जाओ restart;
	पूर्ण
	क्विक(evt_list, evt_num, माप(अक्षर *), cmp_string);
	evt_i = 0;
	जबतक (evt_i < evt_num) अणु
		अगर (name_only) अणु
			म_लिखो("%s ", evt_list[evt_i++]);
			जारी;
		पूर्ण
		म_लिखो("  %-50s [%s]\n", evt_list[evt_i++], event_type_descriptors[type]);
	पूर्ण
	अगर (evt_num && pager_in_use())
		म_लिखो("\n");

out_मुक्त:
	evt_num = evt_i;
	क्रम (evt_i = 0; evt_i < evt_num; evt_i++)
		zमुक्त(&evt_list[evt_i]);
	zमुक्त(&evt_list);
	वापस;

out_enomem:
	म_लिखो("FATAL: not enough memory to print %s\n", event_type_descriptors[type]);
	अगर (evt_list)
		जाओ out_मुक्त;
पूर्ण

/*
 * Prपूर्णांक the help text क्रम the event symbols:
 */
व्योम prपूर्णांक_events(स्थिर अक्षर *event_glob, bool name_only, bool quiet_flag,
			bool दीर्घ_desc, bool details_flag, bool deprecated)
अणु
	prपूर्णांक_symbol_events(event_glob, PERF_TYPE_HARDWARE,
			    event_symbols_hw, PERF_COUNT_HW_MAX, name_only);

	prपूर्णांक_symbol_events(event_glob, PERF_TYPE_SOFTWARE,
			    event_symbols_sw, PERF_COUNT_SW_MAX, name_only);
	prपूर्णांक_tool_events(event_glob, name_only);

	prपूर्णांक_hwcache_events(event_glob, name_only);

	prपूर्णांक_pmu_events(event_glob, name_only, quiet_flag, दीर्घ_desc,
			details_flag, deprecated);

	अगर (event_glob != शून्य)
		वापस;

	अगर (!name_only) अणु
		म_लिखो("  %-50s [%s]\n",
		       "rNNN",
		       event_type_descriptors[PERF_TYPE_RAW]);
		म_लिखो("  %-50s [%s]\n",
		       "cpu/t1=v1[,t2=v2,t3 ...]/modifier",
		       event_type_descriptors[PERF_TYPE_RAW]);
		अगर (pager_in_use())
			म_लिखो("   (see 'man perf-list' on how to encode it)\n\n");

		म_लिखो("  %-50s [%s]\n",
		       "mem:<addr>[/len][:access]",
			event_type_descriptors[PERF_TYPE_BREAKPOINT]);
		अगर (pager_in_use())
			म_लिखो("\n");
	पूर्ण

	prपूर्णांक_tracepoपूर्णांक_events(शून्य, शून्य, name_only);

	prपूर्णांक_sdt_events(शून्य, शून्य, name_only);

	metricgroup__prपूर्णांक(true, true, शून्य, name_only, details_flag);

	prपूर्णांक_libpfm_events(name_only, दीर्घ_desc);
पूर्ण

पूर्णांक parse_events__is_hardcoded_term(काष्ठा parse_events_term *term)
अणु
	वापस term->type_term != PARSE_EVENTS__TERM_TYPE_USER;
पूर्ण

अटल पूर्णांक new_term(काष्ठा parse_events_term **_term,
		    काष्ठा parse_events_term *temp,
		    अक्षर *str, u64 num)
अणु
	काष्ठा parse_events_term *term;

	term = दो_स्मृति(माप(*term));
	अगर (!term)
		वापस -ENOMEM;

	*term = *temp;
	INIT_LIST_HEAD(&term->list);
	term->weak = false;

	चयन (term->type_val) अणु
	हाल PARSE_EVENTS__TERM_TYPE_NUM:
		term->val.num = num;
		अवरोध;
	हाल PARSE_EVENTS__TERM_TYPE_STR:
		term->val.str = str;
		अवरोध;
	शेष:
		मुक्त(term);
		वापस -EINVAL;
	पूर्ण

	*_term = term;
	वापस 0;
पूर्ण

पूर्णांक parse_events_term__num(काष्ठा parse_events_term **term,
			   पूर्णांक type_term, अक्षर *config, u64 num,
			   bool no_value,
			   व्योम *loc_term_, व्योम *loc_val_)
अणु
	YYLTYPE *loc_term = loc_term_;
	YYLTYPE *loc_val = loc_val_;

	काष्ठा parse_events_term temp = अणु
		.type_val  = PARSE_EVENTS__TERM_TYPE_NUM,
		.type_term = type_term,
		.config    = config,
		.no_value  = no_value,
		.err_term  = loc_term ? loc_term->first_column : 0,
		.err_val   = loc_val  ? loc_val->first_column  : 0,
	पूर्ण;

	वापस new_term(term, &temp, शून्य, num);
पूर्ण

पूर्णांक parse_events_term__str(काष्ठा parse_events_term **term,
			   पूर्णांक type_term, अक्षर *config, अक्षर *str,
			   व्योम *loc_term_, व्योम *loc_val_)
अणु
	YYLTYPE *loc_term = loc_term_;
	YYLTYPE *loc_val = loc_val_;

	काष्ठा parse_events_term temp = अणु
		.type_val  = PARSE_EVENTS__TERM_TYPE_STR,
		.type_term = type_term,
		.config    = config,
		.err_term  = loc_term ? loc_term->first_column : 0,
		.err_val   = loc_val  ? loc_val->first_column  : 0,
	पूर्ण;

	वापस new_term(term, &temp, str, 0);
पूर्ण

पूर्णांक parse_events_term__sym_hw(काष्ठा parse_events_term **term,
			      अक्षर *config, अचिन्हित idx)
अणु
	काष्ठा event_symbol *sym;
	अक्षर *str;
	काष्ठा parse_events_term temp = अणु
		.type_val  = PARSE_EVENTS__TERM_TYPE_STR,
		.type_term = PARSE_EVENTS__TERM_TYPE_USER,
		.config    = config,
	पूर्ण;

	अगर (!temp.config) अणु
		temp.config = strdup("event");
		अगर (!temp.config)
			वापस -ENOMEM;
	पूर्ण
	BUG_ON(idx >= PERF_COUNT_HW_MAX);
	sym = &event_symbols_hw[idx];

	str = strdup(sym->symbol);
	अगर (!str)
		वापस -ENOMEM;
	वापस new_term(term, &temp, str, 0);
पूर्ण

पूर्णांक parse_events_term__clone(काष्ठा parse_events_term **new,
			     काष्ठा parse_events_term *term)
अणु
	अक्षर *str;
	काष्ठा parse_events_term temp = अणु
		.type_val  = term->type_val,
		.type_term = term->type_term,
		.config    = शून्य,
		.err_term  = term->err_term,
		.err_val   = term->err_val,
	पूर्ण;

	अगर (term->config) अणु
		temp.config = strdup(term->config);
		अगर (!temp.config)
			वापस -ENOMEM;
	पूर्ण
	अगर (term->type_val == PARSE_EVENTS__TERM_TYPE_NUM)
		वापस new_term(new, &temp, शून्य, term->val.num);

	str = strdup(term->val.str);
	अगर (!str)
		वापस -ENOMEM;
	वापस new_term(new, &temp, str, 0);
पूर्ण

व्योम parse_events_term__delete(काष्ठा parse_events_term *term)
अणु
	अगर (term->array.nr_ranges)
		zमुक्त(&term->array.ranges);

	अगर (term->type_val != PARSE_EVENTS__TERM_TYPE_NUM)
		zमुक्त(&term->val.str);

	zमुक्त(&term->config);
	मुक्त(term);
पूर्ण

पूर्णांक parse_events_copy_term_list(काष्ठा list_head *old,
				 काष्ठा list_head **new)
अणु
	काष्ठा parse_events_term *term, *n;
	पूर्णांक ret;

	अगर (!old) अणु
		*new = शून्य;
		वापस 0;
	पूर्ण

	*new = दो_स्मृति(माप(काष्ठा list_head));
	अगर (!*new)
		वापस -ENOMEM;
	INIT_LIST_HEAD(*new);

	list_क्रम_each_entry (term, old, list) अणु
		ret = parse_events_term__clone(&n, term);
		अगर (ret)
			वापस ret;
		list_add_tail(&n->list, *new);
	पूर्ण
	वापस 0;
पूर्ण

व्योम parse_events_terms__purge(काष्ठा list_head *terms)
अणु
	काष्ठा parse_events_term *term, *h;

	list_क्रम_each_entry_safe(term, h, terms, list) अणु
		list_del_init(&term->list);
		parse_events_term__delete(term);
	पूर्ण
पूर्ण

व्योम parse_events_terms__delete(काष्ठा list_head *terms)
अणु
	अगर (!terms)
		वापस;
	parse_events_terms__purge(terms);
	मुक्त(terms);
पूर्ण

व्योम parse_events__clear_array(काष्ठा parse_events_array *a)
अणु
	zमुक्त(&a->ranges);
पूर्ण

व्योम parse_events_evlist_error(काष्ठा parse_events_state *parse_state,
			       पूर्णांक idx, स्थिर अक्षर *str)
अणु
	अगर (!parse_state->error)
		वापस;

	parse_events__handle_error(parse_state->error, idx, strdup(str), शून्य);
पूर्ण

अटल व्योम config_terms_list(अक्षर *buf, माप_प्रकार buf_sz)
अणु
	पूर्णांक i;
	bool first = true;

	buf[0] = '\0';
	क्रम (i = 0; i < __PARSE_EVENTS__TERM_TYPE_NR; i++) अणु
		स्थिर अक्षर *name = config_term_names[i];

		अगर (!config_term_avail(i, शून्य))
			जारी;
		अगर (!name)
			जारी;
		अगर (name[0] == '<')
			जारी;

		अगर (म_माप(buf) + म_माप(name) + 2 >= buf_sz)
			वापस;

		अगर (!first)
			म_जोड़ो(buf, ",");
		अन्यथा
			first = false;
		म_जोड़ो(buf, name);
	पूर्ण
पूर्ण

/*
 * Return string contains valid config terms of an event.
 * @additional_terms: For terms such as PMU sysfs terms.
 */
अक्षर *parse_events_क्रमmats_error_string(अक्षर *additional_terms)
अणु
	अक्षर *str;
	/* "no-overwrite" is the दीर्घest name */
	अक्षर अटल_terms[__PARSE_EVENTS__TERM_TYPE_NR *
			  (माप("no-overwrite") - 1)];

	config_terms_list(अटल_terms, माप(अटल_terms));
	/* valid terms */
	अगर (additional_terms) अणु
		अगर (aप्र_लिखो(&str, "valid terms: %s,%s",
			     additional_terms, अटल_terms) < 0)
			जाओ fail;
	पूर्ण अन्यथा अणु
		अगर (aप्र_लिखो(&str, "valid terms: %s", अटल_terms) < 0)
			जाओ fail;
	पूर्ण
	वापस str;

fail:
	वापस शून्य;
पूर्ण

काष्ठा evsel *parse_events__add_event_hybrid(काष्ठा list_head *list, पूर्णांक *idx,
					     काष्ठा perf_event_attr *attr,
					     अक्षर *name, काष्ठा perf_pmu *pmu,
					     काष्ठा list_head *config_terms)
अणु
	वापस __add_event(list, idx, attr, true, name, pmu,
			   config_terms, false, शून्य);
पूर्ण
