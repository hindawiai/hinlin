<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_TOOL_H
#घोषणा __PERF_TOOL_H

#समावेश <stdbool.h>

#समावेश <linux/types.h>

काष्ठा perf_session;
जोड़ perf_event;
काष्ठा evlist;
काष्ठा evsel;
काष्ठा perf_sample;
काष्ठा perf_tool;
काष्ठा machine;
काष्ठा ordered_events;

प्रकार पूर्णांक (*event_sample)(काष्ठा perf_tool *tool, जोड़ perf_event *event,
			    काष्ठा perf_sample *sample,
			    काष्ठा evsel *evsel, काष्ठा machine *machine);

प्रकार पूर्णांक (*event_op)(काष्ठा perf_tool *tool, जोड़ perf_event *event,
			काष्ठा perf_sample *sample, काष्ठा machine *machine);

प्रकार पूर्णांक (*event_attr_op)(काष्ठा perf_tool *tool,
			     जोड़ perf_event *event,
			     काष्ठा evlist **pevlist);

प्रकार पूर्णांक (*event_op2)(काष्ठा perf_session *session, जोड़ perf_event *event);
प्रकार s64 (*event_op3)(काष्ठा perf_session *session, जोड़ perf_event *event);
प्रकार पूर्णांक (*event_op4)(काष्ठा perf_session *session, जोड़ perf_event *event, u64 data);

प्रकार पूर्णांक (*event_oe)(काष्ठा perf_tool *tool, जोड़ perf_event *event,
			काष्ठा ordered_events *oe);

क्रमागत show_feature_header अणु
	SHOW_FEAT_NO_HEADER = 0,
	SHOW_FEAT_HEADER,
	SHOW_FEAT_HEADER_FULL_INFO,
पूर्ण;

काष्ठा perf_tool अणु
	event_sample	sample,
			पढ़ो;
	event_op	mmap,
			mmap2,
			comm,
			namespaces,
			cgroup,
			विभाजन,
			निकास,
			lost,
			lost_samples,
			aux,
			itrace_start,
			context_चयन,
			throttle,
			unthrottle,
			ksymbol,
			bpf,
			text_poke;

	event_attr_op	attr;
	event_attr_op	event_update;
	event_op2	tracing_data;
	event_oe	finished_round;
	event_op2	build_id,
			id_index,
			auxtrace_info,
			auxtrace_error,
			समय_conv,
			thपढ़ो_map,
			cpu_map,
			stat_config,
			stat,
			stat_round,
			feature;
	event_op4	compressed;
	event_op3	auxtrace;
	bool		ordered_events;
	bool		ordering_requires_बारtamps;
	bool		namespace_events;
	bool		cgroup_events;
	bool		no_warn;
	क्रमागत show_feature_header show_feat_hdr;
पूर्ण;

#पूर्ण_अगर /* __PERF_TOOL_H */
