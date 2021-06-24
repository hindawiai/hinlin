<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_PARSE_EVENTS_H
#घोषणा __PERF_PARSE_EVENTS_H
/*
 * Parse symbolic events/counts passed in as options:
 */

#समावेश <linux/list.h>
#समावेश <stdbool.h>
#समावेश <linux/types.h>
#समावेश <linux/perf_event.h>
#समावेश <माला.स>

काष्ठा list_head;
काष्ठा evsel;
काष्ठा evlist;
काष्ठा parse_events_error;

काष्ठा option;
काष्ठा perf_pmu;

काष्ठा tracepoपूर्णांक_path अणु
	अक्षर *प्रणाली;
	अक्षर *name;
	काष्ठा tracepoपूर्णांक_path *next;
पूर्ण;

काष्ठा tracepoपूर्णांक_path *tracepoपूर्णांक_id_to_path(u64 config);
काष्ठा tracepoपूर्णांक_path *tracepoपूर्णांक_name_to_path(स्थिर अक्षर *name);
bool have_tracepoपूर्णांकs(काष्ठा list_head *evlist);

स्थिर अक्षर *event_type(पूर्णांक type);

पूर्णांक parse_events_option(स्थिर काष्ठा option *opt, स्थिर अक्षर *str, पूर्णांक unset);
पूर्णांक parse_events_option_new_evlist(स्थिर काष्ठा option *opt, स्थिर अक्षर *str, पूर्णांक unset);
पूर्णांक __parse_events(काष्ठा evlist *evlist, स्थिर अक्षर *str, काष्ठा parse_events_error *error,
		   काष्ठा perf_pmu *fake_pmu);

अटल अंतरभूत पूर्णांक parse_events(काष्ठा evlist *evlist, स्थिर अक्षर *str,
			       काष्ठा parse_events_error *err)
अणु
	वापस __parse_events(evlist, str, err, शून्य);
पूर्ण

पूर्णांक parse_events_terms(काष्ठा list_head *terms, स्थिर अक्षर *str);
पूर्णांक parse_filter(स्थिर काष्ठा option *opt, स्थिर अक्षर *str, पूर्णांक unset);
पूर्णांक exclude_perf(स्थिर काष्ठा option *opt, स्थिर अक्षर *arg, पूर्णांक unset);

#घोषणा EVENTS_HELP_MAX (128*1024)

क्रमागत perf_pmu_event_symbol_type अणु
	PMU_EVENT_SYMBOL_ERR,		/* not a PMU EVENT */
	PMU_EVENT_SYMBOL,		/* normal style PMU event */
	PMU_EVENT_SYMBOL_PREFIX,	/* prefix of pre-suf style event */
	PMU_EVENT_SYMBOL_SUFFIX,	/* suffix of pre-suf style event */
पूर्ण;

काष्ठा perf_pmu_event_symbol अणु
	अक्षर	*symbol;
	क्रमागत perf_pmu_event_symbol_type	type;
पूर्ण;

क्रमागत अणु
	PARSE_EVENTS__TERM_TYPE_NUM,
	PARSE_EVENTS__TERM_TYPE_STR,
पूर्ण;

क्रमागत अणु
	PARSE_EVENTS__TERM_TYPE_USER,
	PARSE_EVENTS__TERM_TYPE_CONFIG,
	PARSE_EVENTS__TERM_TYPE_CONFIG1,
	PARSE_EVENTS__TERM_TYPE_CONFIG2,
	PARSE_EVENTS__TERM_TYPE_NAME,
	PARSE_EVENTS__TERM_TYPE_SAMPLE_PERIOD,
	PARSE_EVENTS__TERM_TYPE_SAMPLE_FREQ,
	PARSE_EVENTS__TERM_TYPE_BRANCH_SAMPLE_TYPE,
	PARSE_EVENTS__TERM_TYPE_TIME,
	PARSE_EVENTS__TERM_TYPE_CALLGRAPH,
	PARSE_EVENTS__TERM_TYPE_STACKSIZE,
	PARSE_EVENTS__TERM_TYPE_NOINHERIT,
	PARSE_EVENTS__TERM_TYPE_INHERIT,
	PARSE_EVENTS__TERM_TYPE_MAX_STACK,
	PARSE_EVENTS__TERM_TYPE_MAX_EVENTS,
	PARSE_EVENTS__TERM_TYPE_NOOVERWRITE,
	PARSE_EVENTS__TERM_TYPE_OVERWRITE,
	PARSE_EVENTS__TERM_TYPE_DRV_CFG,
	PARSE_EVENTS__TERM_TYPE_PERCORE,
	PARSE_EVENTS__TERM_TYPE_AUX_OUTPUT,
	PARSE_EVENTS__TERM_TYPE_AUX_SAMPLE_SIZE,
	__PARSE_EVENTS__TERM_TYPE_NR,
पूर्ण;

काष्ठा parse_events_array अणु
	माप_प्रकार nr_ranges;
	काष्ठा अणु
		अचिन्हित पूर्णांक start;
		माप_प्रकार length;
	पूर्ण *ranges;
पूर्ण;

काष्ठा parse_events_term अणु
	अक्षर *config;
	काष्ठा parse_events_array array;
	जोड़ अणु
		अक्षर *str;
		u64  num;
	पूर्ण val;
	पूर्णांक type_val;
	पूर्णांक type_term;
	काष्ठा list_head list;
	bool used;
	bool no_value;

	/* error string indexes क्रम within parsed string */
	पूर्णांक err_term;
	पूर्णांक err_val;

	/* Coming from implicit alias */
	bool weak;
पूर्ण;

काष्ठा parse_events_error अणु
	पूर्णांक   num_errors;       /* number of errors encountered */
	पूर्णांक   idx;	/* index in the parsed string */
	अक्षर *str;      /* string to display at the index */
	अक्षर *help;	/* optional help string */
	पूर्णांक   first_idx;/* as above, but क्रम the first encountered error */
	अक्षर *first_str;
	अक्षर *first_help;
पूर्ण;

काष्ठा parse_events_state अणु
	काष्ठा list_head	   list;
	पूर्णांक			   idx;
	पूर्णांक			   nr_groups;
	काष्ठा parse_events_error *error;
	काष्ठा evlist		  *evlist;
	काष्ठा list_head	  *terms;
	पूर्णांक			   stoken;
	काष्ठा perf_pmu		  *fake_pmu;
	अक्षर			  *hybrid_pmu_name;
पूर्ण;

व्योम parse_events__handle_error(काष्ठा parse_events_error *err, पूर्णांक idx,
				अक्षर *str, अक्षर *help);
व्योम parse_events__shrink_config_terms(व्योम);
पूर्णांक parse_events__is_hardcoded_term(काष्ठा parse_events_term *term);
पूर्णांक parse_events_term__num(काष्ठा parse_events_term **term,
			   पूर्णांक type_term, अक्षर *config, u64 num,
			   bool novalue,
			   व्योम *loc_term, व्योम *loc_val);
पूर्णांक parse_events_term__str(काष्ठा parse_events_term **term,
			   पूर्णांक type_term, अक्षर *config, अक्षर *str,
			   व्योम *loc_term, व्योम *loc_val);
पूर्णांक parse_events_term__sym_hw(काष्ठा parse_events_term **term,
			      अक्षर *config, अचिन्हित idx);
पूर्णांक parse_events_term__clone(काष्ठा parse_events_term **new,
			     काष्ठा parse_events_term *term);
व्योम parse_events_term__delete(काष्ठा parse_events_term *term);
व्योम parse_events_terms__delete(काष्ठा list_head *terms);
व्योम parse_events_terms__purge(काष्ठा list_head *terms);
व्योम parse_events__clear_array(काष्ठा parse_events_array *a);
पूर्णांक parse_events__modअगरier_event(काष्ठा list_head *list, अक्षर *str, bool add);
पूर्णांक parse_events__modअगरier_group(काष्ठा list_head *list, अक्षर *event_mod);
पूर्णांक parse_events_name(काष्ठा list_head *list, अक्षर *name);
पूर्णांक parse_events_add_tracepoपूर्णांक(काष्ठा list_head *list, पूर्णांक *idx,
				स्थिर अक्षर *sys, स्थिर अक्षर *event,
				काष्ठा parse_events_error *error,
				काष्ठा list_head *head_config);
पूर्णांक parse_events_load_bpf(काष्ठा parse_events_state *parse_state,
			  काष्ठा list_head *list,
			  अक्षर *bpf_file_name,
			  bool source,
			  काष्ठा list_head *head_config);
/* Provide this function क्रम perf test */
काष्ठा bpf_object;
पूर्णांक parse_events_load_bpf_obj(काष्ठा parse_events_state *parse_state,
			      काष्ठा list_head *list,
			      काष्ठा bpf_object *obj,
			      काष्ठा list_head *head_config);
पूर्णांक parse_events_add_numeric(काष्ठा parse_events_state *parse_state,
			     काष्ठा list_head *list,
			     u32 type, u64 config,
			     काष्ठा list_head *head_config);
क्रमागत perf_tool_event;
पूर्णांक parse_events_add_tool(काष्ठा parse_events_state *parse_state,
			  काष्ठा list_head *list,
			  क्रमागत perf_tool_event tool_event);
पूर्णांक parse_events_add_cache(काष्ठा list_head *list, पूर्णांक *idx,
			   अक्षर *type, अक्षर *op_result1, अक्षर *op_result2,
			   काष्ठा parse_events_error *error,
			   काष्ठा list_head *head_config,
			   काष्ठा parse_events_state *parse_state);
पूर्णांक parse_events_add_अवरोधpoपूर्णांक(काष्ठा list_head *list, पूर्णांक *idx,
				u64 addr, अक्षर *type, u64 len);
पूर्णांक parse_events_add_pmu(काष्ठा parse_events_state *parse_state,
			 काष्ठा list_head *list, अक्षर *name,
			 काष्ठा list_head *head_config,
			 bool स्वतः_merge_stats,
			 bool use_alias);

काष्ठा evsel *parse_events__add_event(पूर्णांक idx, काष्ठा perf_event_attr *attr,
					अक्षर *name, काष्ठा perf_pmu *pmu);

पूर्णांक parse_events_multi_pmu_add(काष्ठा parse_events_state *parse_state,
			       अक्षर *str,
			       काष्ठा list_head **listp);

पूर्णांक parse_events_copy_term_list(काष्ठा list_head *old,
				 काष्ठा list_head **new);

क्रमागत perf_pmu_event_symbol_type
perf_pmu__parse_check(स्थिर अक्षर *name);
व्योम parse_events__set_leader(अक्षर *name, काष्ठा list_head *list,
			      काष्ठा parse_events_state *parse_state);
व्योम parse_events_update_lists(काष्ठा list_head *list_event,
			       काष्ठा list_head *list_all);
व्योम parse_events_evlist_error(काष्ठा parse_events_state *parse_state,
			       पूर्णांक idx, स्थिर अक्षर *str);

व्योम prपूर्णांक_events(स्थिर अक्षर *event_glob, bool name_only, bool quiet,
		  bool दीर्घ_desc, bool details_flag, bool deprecated);

काष्ठा event_symbol अणु
	स्थिर अक्षर	*symbol;
	स्थिर अक्षर	*alias;
पूर्ण;
बाह्य काष्ठा event_symbol event_symbols_hw[];
बाह्य काष्ठा event_symbol event_symbols_sw[];
व्योम prपूर्णांक_symbol_events(स्थिर अक्षर *event_glob, अचिन्हित type,
				काष्ठा event_symbol *syms, अचिन्हित max,
				bool name_only);
व्योम prपूर्णांक_tool_events(स्थिर अक्षर *event_glob, bool name_only);
व्योम prपूर्णांक_tracepoपूर्णांक_events(स्थिर अक्षर *subsys_glob, स्थिर अक्षर *event_glob,
			     bool name_only);
पूर्णांक prपूर्णांक_hwcache_events(स्थिर अक्षर *event_glob, bool name_only);
व्योम prपूर्णांक_sdt_events(स्थिर अक्षर *subsys_glob, स्थिर अक्षर *event_glob,
		      bool name_only);
पूर्णांक is_valid_tracepoपूर्णांक(स्थिर अक्षर *event_string);

पूर्णांक valid_event_mount(स्थिर अक्षर *eventfs);
अक्षर *parse_events_क्रमmats_error_string(अक्षर *additional_terms);

व्योम parse_events_prपूर्णांक_error(काष्ठा parse_events_error *err,
			      स्थिर अक्षर *event);

#अगर_घोषित HAVE_LIBELF_SUPPORT
/*
 * If the probe poपूर्णांक starts with '%',
 * or starts with "sdt_" and has a ':' but no '=',
 * then it should be a SDT/cached probe poपूर्णांक.
 */
अटल अंतरभूत bool is_sdt_event(अक्षर *str)
अणु
	वापस (str[0] == '%' ||
		(!म_भेदन(str, "sdt_", 4) &&
		 !!म_अक्षर(str, ':') && !strchr(str, '=')));
पूर्ण
#अन्यथा
अटल अंतरभूत bool is_sdt_event(अक्षर *str __maybe_unused)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* HAVE_LIBELF_SUPPORT */

पूर्णांक perf_pmu__test_parse_init(व्योम);

काष्ठा evsel *parse_events__add_event_hybrid(काष्ठा list_head *list, पूर्णांक *idx,
					     काष्ठा perf_event_attr *attr,
					     अक्षर *name, काष्ठा perf_pmu *pmu,
					     काष्ठा list_head *config_terms);

#पूर्ण_अगर /* __PERF_PARSE_EVENTS_H */
