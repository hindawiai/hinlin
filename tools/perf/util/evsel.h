<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_EVSEL_H
#घोषणा __PERF_EVSEL_H 1

#समावेश <linux/list.h>
#समावेश <stdbool.h>
#समावेश <sys/types.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/types.h>
#समावेश <पूर्णांकernal/evsel.h>
#समावेश <perf/evsel.h>
#समावेश "symbol_conf.h"
#समावेश <पूर्णांकernal/cpumap.h>

काष्ठा bpf_object;
काष्ठा cgroup;
काष्ठा perf_counts;
काष्ठा perf_stat_evsel;
जोड़ perf_event;
काष्ठा bpf_counter_ops;
काष्ठा target;
काष्ठा hashmap;
काष्ठा bperf_leader_bpf;
काष्ठा bperf_follower_bpf;

प्रकार पूर्णांक (evsel__sb_cb_t)(जोड़ perf_event *event, व्योम *data);

क्रमागत perf_tool_event अणु
	PERF_TOOL_NONE		= 0,
	PERF_TOOL_DURATION_TIME = 1,
पूर्ण;

/** काष्ठा evsel - event selector
 *
 * @evlist - evlist this evsel is in, अगर it is in one.
 * @core - libperf evsel object
 * @name - Can be set to retain the original event name passed by the user,
 *         so that when showing results in tools such as 'perf stat', we
 *         show the name used, not some alias.
 * @id_pos: the position of the event id (PERF_SAMPLE_ID or
 *          PERF_SAMPLE_IDENTIFIER) in a sample event i.e. in the array of
 *          काष्ठा perf_record_sample
 * @is_pos: the position (counting backwards) of the event id (PERF_SAMPLE_ID or
 *          PERF_SAMPLE_IDENTIFIER) in a non-sample event i.e. अगर sample_id_all
 *          is used there is an id sample appended to non-sample events
 * @priv:   And what is in its containing unnamed जोड़ are tool specअगरic
 */
काष्ठा evsel अणु
	काष्ठा perf_evsel	core;
	काष्ठा evlist		*evlist;
	off_t			id_offset;
	पूर्णांक			idx;
	पूर्णांक			id_pos;
	पूर्णांक			is_pos;
	अचिन्हित पूर्णांक		sample_size;

	/*
	 * These fields can be set in the parse-events code or similar.
	 * Please check evsel__clone() to copy them properly so that
	 * they can be released properly.
	 */
	काष्ठा अणु
		अक्षर			*name;
		अक्षर			*group_name;
		स्थिर अक्षर		*pmu_name;
		काष्ठा tep_event	*tp_क्रमmat;
		अक्षर			*filter;
		अचिन्हित दीर्घ		max_events;
		द्विगुन			scale;
		स्थिर अक्षर		*unit;
		काष्ठा cgroup		*cgrp;
		क्रमागत perf_tool_event	tool_event;
		/* parse modअगरier helper */
		पूर्णांक			exclude_GH;
		पूर्णांक			sample_पढ़ो;
		bool			snapshot;
		bool			per_pkg;
		bool			percore;
		bool			precise_max;
		bool			use_uncore_alias;
		bool			is_libpfm_event;
		bool			स्वतः_merge_stats;
		bool			collect_stat;
		bool			weak_group;
		bool			bpf_counter;
		bool			use_config_name;
		पूर्णांक			bpf_fd;
		काष्ठा bpf_object	*bpf_obj;
		काष्ठा list_head	config_terms;
	पूर्ण;

	/*
	 * metric fields are similar, but needs more care as they can have
	 * references to other metric (evsel).
	 */
	स्थिर अक्षर *		metric_expr;
	स्थिर अक्षर *		metric_name;
	काष्ठा evsel		**metric_events;
	काष्ठा evsel		*metric_leader;

	व्योम			*handler;
	काष्ठा perf_counts	*counts;
	काष्ठा perf_counts	*prev_raw_counts;
	अचिन्हित दीर्घ		nr_events_prपूर्णांकed;
	काष्ठा perf_stat_evsel  *stats;
	व्योम			*priv;
	u64			db_id;
	bool			uniquअगरied_name;
	bool 			supported;
	bool 			needs_swap;
	bool 			disabled;
	bool			no_aux_samples;
	bool			immediate;
	bool			tracking;
	bool			ignore_missing_thपढ़ो;
	bool			क्रमced_leader;
	bool			cmdline_group_boundary;
	bool			merged_stat;
	bool			reset_group;
	bool			errored;
	काष्ठा hashmap		*per_pkg_mask;
	काष्ठा evsel		*leader;
	पूर्णांक			err;
	पूर्णांक			cpu_iter;
	काष्ठा अणु
		evsel__sb_cb_t	*cb;
		व्योम		*data;
	पूर्ण side_band;
	/*
	 * For reporting purposes, an evsel sample can have a callchain
	 * synthesized from AUX area data. Keep track of synthesized sample
	 * types here. Note, the recorded sample_type cannot be changed because
	 * it is needed to जारी to parse events.
	 * See also evsel__has_callchain().
	 */
	__u64			synth_sample_type;

	/*
	 * bpf_counter_ops serves two use हालs:
	 *   1. perf-stat -b          counting events used byBPF programs
	 *   2. perf-stat --use-bpf   use BPF programs to aggregate counts
	 */
	काष्ठा bpf_counter_ops	*bpf_counter_ops;

	/* क्रम perf-stat -b */
	काष्ठा list_head	bpf_counter_list;

	/* क्रम perf-stat --use-bpf */
	पूर्णांक			bperf_leader_prog_fd;
	पूर्णांक			bperf_leader_link_fd;
	जोड़ अणु
		काष्ठा bperf_leader_bpf *leader_skel;
		काष्ठा bperf_follower_bpf *follower_skel;
	पूर्ण;
पूर्ण;

काष्ठा perf_missing_features अणु
	bool sample_id_all;
	bool exclude_guest;
	bool mmap2;
	bool cloexec;
	bool घड़ीid;
	bool घड़ीid_wrong;
	bool lbr_flags;
	bool ग_लिखो_backward;
	bool group_पढ़ो;
	bool ksymbol;
	bool bpf;
	bool aux_output;
	bool branch_hw_idx;
	bool cgroup;
	bool data_page_size;
	bool code_page_size;
	bool weight_काष्ठा;
पूर्ण;

बाह्य काष्ठा perf_missing_features perf_missing_features;

काष्ठा perf_cpu_map;
काष्ठा thपढ़ो_map;
काष्ठा record_opts;

अटल अंतरभूत काष्ठा perf_cpu_map *evsel__cpus(काष्ठा evsel *evsel)
अणु
	वापस perf_evsel__cpus(&evsel->core);
पूर्ण

अटल अंतरभूत पूर्णांक evsel__nr_cpus(काष्ठा evsel *evsel)
अणु
	वापस evsel__cpus(evsel)->nr;
पूर्ण

व्योम perf_counts_values__scale(काष्ठा perf_counts_values *count,
			       bool scale, s8 *pscaled);

व्योम evsel__compute_deltas(काष्ठा evsel *evsel, पूर्णांक cpu, पूर्णांक thपढ़ो,
			   काष्ठा perf_counts_values *count);

पूर्णांक evsel__object_config(माप_प्रकार object_size,
			 पूर्णांक (*init)(काष्ठा evsel *evsel),
			 व्योम (*fini)(काष्ठा evsel *evsel));

काष्ठा perf_pmu *evsel__find_pmu(काष्ठा evsel *evsel);
bool evsel__is_aux_event(काष्ठा evsel *evsel);

काष्ठा evsel *evsel__new_idx(काष्ठा perf_event_attr *attr, पूर्णांक idx);

अटल अंतरभूत काष्ठा evsel *evsel__new(काष्ठा perf_event_attr *attr)
अणु
	वापस evsel__new_idx(attr, 0);
पूर्ण

काष्ठा evsel *evsel__clone(काष्ठा evsel *orig);
काष्ठा evsel *evsel__newtp_idx(स्थिर अक्षर *sys, स्थिर अक्षर *name, पूर्णांक idx);

/*
 * Returns poपूर्णांकer with encoded error via <linux/err.h> पूर्णांकerface.
 */
अटल अंतरभूत काष्ठा evsel *evsel__newtp(स्थिर अक्षर *sys, स्थिर अक्षर *name)
अणु
	वापस evsel__newtp_idx(sys, name, 0);
पूर्ण

काष्ठा evsel *evsel__new_cycles(bool precise, __u32 type, __u64 config);

काष्ठा tep_event *event_क्रमmat__new(स्थिर अक्षर *sys, स्थिर अक्षर *name);

व्योम evsel__init(काष्ठा evsel *evsel, काष्ठा perf_event_attr *attr, पूर्णांक idx);
व्योम evsel__निकास(काष्ठा evsel *evsel);
व्योम evsel__delete(काष्ठा evsel *evsel);

काष्ठा callchain_param;

व्योम evsel__config(काष्ठा evsel *evsel, काष्ठा record_opts *opts,
		   काष्ठा callchain_param *callchain);
व्योम evsel__config_callchain(काष्ठा evsel *evsel, काष्ठा record_opts *opts,
			     काष्ठा callchain_param *callchain);

पूर्णांक __evsel__sample_size(u64 sample_type);
व्योम evsel__calc_id_pos(काष्ठा evsel *evsel);

bool evsel__is_cache_op_valid(u8 type, u8 op);

अटल अंतरभूत bool evsel__is_bpf(काष्ठा evsel *evsel)
अणु
	वापस evsel->bpf_counter_ops != शून्य;
पूर्ण

#घोषणा EVSEL__MAX_ALIASES 8

बाह्य स्थिर अक्षर *evsel__hw_cache[PERF_COUNT_HW_CACHE_MAX][EVSEL__MAX_ALIASES];
बाह्य स्थिर अक्षर *evsel__hw_cache_op[PERF_COUNT_HW_CACHE_OP_MAX][EVSEL__MAX_ALIASES];
बाह्य स्थिर अक्षर *evsel__hw_cache_result[PERF_COUNT_HW_CACHE_RESULT_MAX][EVSEL__MAX_ALIASES];
बाह्य स्थिर अक्षर *evsel__hw_names[PERF_COUNT_HW_MAX];
बाह्य स्थिर अक्षर *evsel__sw_names[PERF_COUNT_SW_MAX];
बाह्य अक्षर *evsel__bpf_counter_events;
bool evsel__match_bpf_counter_events(स्थिर अक्षर *name);

पूर्णांक __evsel__hw_cache_type_op_res_name(u8 type, u8 op, u8 result, अक्षर *bf, माप_प्रकार size);
स्थिर अक्षर *evsel__name(काष्ठा evsel *evsel);

स्थिर अक्षर *evsel__group_name(काष्ठा evsel *evsel);
पूर्णांक evsel__group_desc(काष्ठा evsel *evsel, अक्षर *buf, माप_प्रकार size);

व्योम __evsel__set_sample_bit(काष्ठा evsel *evsel, क्रमागत perf_event_sample_क्रमmat bit);
व्योम __evsel__reset_sample_bit(काष्ठा evsel *evsel, क्रमागत perf_event_sample_क्रमmat bit);

#घोषणा evsel__set_sample_bit(evsel, bit) \
	__evsel__set_sample_bit(evsel, PERF_SAMPLE_##bit)

#घोषणा evsel__reset_sample_bit(evsel, bit) \
	__evsel__reset_sample_bit(evsel, PERF_SAMPLE_##bit)

व्योम evsel__set_sample_id(काष्ठा evsel *evsel, bool use_sample_identअगरier);

व्योम arch_evsel__set_sample_weight(काष्ठा evsel *evsel);

पूर्णांक evsel__set_filter(काष्ठा evsel *evsel, स्थिर अक्षर *filter);
पूर्णांक evsel__append_tp_filter(काष्ठा evsel *evsel, स्थिर अक्षर *filter);
पूर्णांक evsel__append_addr_filter(काष्ठा evsel *evsel, स्थिर अक्षर *filter);
पूर्णांक evsel__enable_cpu(काष्ठा evsel *evsel, पूर्णांक cpu);
पूर्णांक evsel__enable(काष्ठा evsel *evsel);
पूर्णांक evsel__disable(काष्ठा evsel *evsel);
पूर्णांक evsel__disable_cpu(काष्ठा evsel *evsel, पूर्णांक cpu);

पूर्णांक evsel__खोलो_per_cpu(काष्ठा evsel *evsel, काष्ठा perf_cpu_map *cpus, पूर्णांक cpu);
पूर्णांक evsel__खोलो_per_thपढ़ो(काष्ठा evsel *evsel, काष्ठा perf_thपढ़ो_map *thपढ़ोs);
पूर्णांक evsel__खोलो(काष्ठा evsel *evsel, काष्ठा perf_cpu_map *cpus,
		काष्ठा perf_thपढ़ो_map *thपढ़ोs);
व्योम evsel__बंद(काष्ठा evsel *evsel);

काष्ठा perf_sample;

व्योम *evsel__rawptr(काष्ठा evsel *evsel, काष्ठा perf_sample *sample, स्थिर अक्षर *name);
u64 evsel__पूर्णांकval(काष्ठा evsel *evsel, काष्ठा perf_sample *sample, स्थिर अक्षर *name);

अटल अंतरभूत अक्षर *evsel__strval(काष्ठा evsel *evsel, काष्ठा perf_sample *sample, स्थिर अक्षर *name)
अणु
	वापस evsel__rawptr(evsel, sample, name);
पूर्ण

काष्ठा tep_क्रमmat_field;

u64 क्रमmat_field__पूर्णांकval(काष्ठा tep_क्रमmat_field *field, काष्ठा perf_sample *sample, bool needs_swap);

काष्ठा tep_क्रमmat_field *evsel__field(काष्ठा evsel *evsel, स्थिर अक्षर *name);

#घोषणा evsel__match(evsel, t, c)		\
	(evsel->core.attr.type == PERF_TYPE_##t &&	\
	 evsel->core.attr.config == PERF_COUNT_##c)

अटल अंतरभूत bool evsel__match2(काष्ठा evsel *e1, काष्ठा evsel *e2)
अणु
	वापस (e1->core.attr.type == e2->core.attr.type) &&
	       (e1->core.attr.config == e2->core.attr.config);
पूर्ण

पूर्णांक evsel__पढ़ो_counter(काष्ठा evsel *evsel, पूर्णांक cpu, पूर्णांक thपढ़ो);

पूर्णांक __evsel__पढ़ो_on_cpu(काष्ठा evsel *evsel, पूर्णांक cpu, पूर्णांक thपढ़ो, bool scale);

/**
 * evsel__पढ़ो_on_cpu - Read out the results on a CPU and thपढ़ो
 *
 * @evsel - event selector to पढ़ो value
 * @cpu - CPU of पूर्णांकerest
 * @thपढ़ो - thपढ़ो of पूर्णांकerest
 */
अटल अंतरभूत पूर्णांक evsel__पढ़ो_on_cpu(काष्ठा evsel *evsel, पूर्णांक cpu, पूर्णांक thपढ़ो)
अणु
	वापस __evsel__पढ़ो_on_cpu(evsel, cpu, thपढ़ो, false);
पूर्ण

/**
 * evsel__पढ़ो_on_cpu_scaled - Read out the results on a CPU and thपढ़ो, scaled
 *
 * @evsel - event selector to पढ़ो value
 * @cpu - CPU of पूर्णांकerest
 * @thपढ़ो - thपढ़ो of पूर्णांकerest
 */
अटल अंतरभूत पूर्णांक evsel__पढ़ो_on_cpu_scaled(काष्ठा evsel *evsel, पूर्णांक cpu, पूर्णांक thपढ़ो)
अणु
	वापस __evsel__पढ़ो_on_cpu(evsel, cpu, thपढ़ो, true);
पूर्ण

पूर्णांक evsel__parse_sample(काष्ठा evsel *evsel, जोड़ perf_event *event,
			काष्ठा perf_sample *sample);

पूर्णांक evsel__parse_sample_बारtamp(काष्ठा evsel *evsel, जोड़ perf_event *event,
				  u64 *बारtamp);

अटल अंतरभूत काष्ठा evsel *evsel__next(काष्ठा evsel *evsel)
अणु
	वापस list_entry(evsel->core.node.next, काष्ठा evsel, core.node);
पूर्ण

अटल अंतरभूत काष्ठा evsel *evsel__prev(काष्ठा evsel *evsel)
अणु
	वापस list_entry(evsel->core.node.prev, काष्ठा evsel, core.node);
पूर्ण

/**
 * evsel__is_group_leader - Return whether given evsel is a leader event
 *
 * @evsel - evsel selector to be tested
 *
 * Return %true अगर @evsel is a group leader or a stand-alone event
 */
अटल अंतरभूत bool evsel__is_group_leader(स्थिर काष्ठा evsel *evsel)
अणु
	वापस evsel->leader == evsel;
पूर्ण

/**
 * evsel__is_group_event - Return whether given evsel is a group event
 *
 * @evsel - evsel selector to be tested
 *
 * Return %true अगरf event group view is enabled and @evsel is a actual group
 * leader which has other members in the group
 */
अटल अंतरभूत bool evsel__is_group_event(काष्ठा evsel *evsel)
अणु
	अगर (!symbol_conf.event_group)
		वापस false;

	वापस evsel__is_group_leader(evsel) && evsel->core.nr_members > 1;
पूर्ण

bool evsel__is_function_event(काष्ठा evsel *evsel);

अटल अंतरभूत bool evsel__is_bpf_output(काष्ठा evsel *evsel)
अणु
	वापस evsel__match(evsel, SOFTWARE, SW_BPF_OUTPUT);
पूर्ण

अटल अंतरभूत bool evsel__is_घड़ी(काष्ठा evsel *evsel)
अणु
	वापस evsel__match(evsel, SOFTWARE, SW_CPU_CLOCK) ||
	       evsel__match(evsel, SOFTWARE, SW_TASK_CLOCK);
पूर्ण

bool evsel__fallback(काष्ठा evsel *evsel, पूर्णांक err, अक्षर *msg, माप_प्रकार msgsize);
पूर्णांक evsel__खोलो_म_त्रुटि(काष्ठा evsel *evsel, काष्ठा target *target,
			 पूर्णांक err, अक्षर *msg, माप_प्रकार size);

अटल अंतरभूत पूर्णांक evsel__group_idx(काष्ठा evsel *evsel)
अणु
	वापस evsel->idx - evsel->leader->idx;
पूर्ण

/* Iterates group WITHOUT the leader. */
#घोषणा क्रम_each_group_member(_evsel, _leader) 					\
क्रम ((_evsel) = list_entry((_leader)->core.node.next, काष्ठा evsel, core.node); \
     (_evsel) && (_evsel)->leader == (_leader);					\
     (_evsel) = list_entry((_evsel)->core.node.next, काष्ठा evsel, core.node))

/* Iterates group WITH the leader. */
#घोषणा क्रम_each_group_evsel(_evsel, _leader) 					\
क्रम ((_evsel) = _leader; 							\
     (_evsel) && (_evsel)->leader == (_leader);					\
     (_evsel) = list_entry((_evsel)->core.node.next, काष्ठा evsel, core.node))

अटल अंतरभूत bool evsel__has_branch_callstack(स्थिर काष्ठा evsel *evsel)
अणु
	वापस evsel->core.attr.branch_sample_type & PERF_SAMPLE_BRANCH_CALL_STACK;
पूर्ण

अटल अंतरभूत bool evsel__has_branch_hw_idx(स्थिर काष्ठा evsel *evsel)
अणु
	वापस evsel->core.attr.branch_sample_type & PERF_SAMPLE_BRANCH_HW_INDEX;
पूर्ण

अटल अंतरभूत bool evsel__has_callchain(स्थिर काष्ठा evsel *evsel)
अणु
	/*
	 * For reporting purposes, an evsel sample can have a recorded callchain
	 * or a callchain synthesized from AUX area data.
	 */
	वापस evsel->core.attr.sample_type & PERF_SAMPLE_CALLCHAIN ||
	       evsel->synth_sample_type & PERF_SAMPLE_CALLCHAIN;
पूर्ण

अटल अंतरभूत bool evsel__has_br_stack(स्थिर काष्ठा evsel *evsel)
अणु
	/*
	 * For reporting purposes, an evsel sample can have a recorded branch
	 * stack or a branch stack synthesized from AUX area data.
	 */
	वापस evsel->core.attr.sample_type & PERF_SAMPLE_BRANCH_STACK ||
	       evsel->synth_sample_type & PERF_SAMPLE_BRANCH_STACK;
पूर्ण

अटल अंतरभूत bool evsel__is_dummy_event(काष्ठा evsel *evsel)
अणु
	वापस (evsel->core.attr.type == PERF_TYPE_SOFTWARE) &&
	       (evsel->core.attr.config == PERF_COUNT_SW_DUMMY);
पूर्ण

काष्ठा perf_env *evsel__env(काष्ठा evsel *evsel);

पूर्णांक evsel__store_ids(काष्ठा evsel *evsel, काष्ठा evlist *evlist);

व्योम evsel__zero_per_pkg(काष्ठा evsel *evsel);
bool evsel__is_hybrid(काष्ठा evsel *evsel);
#पूर्ण_अगर /* __PERF_EVSEL_H */
