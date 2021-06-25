<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_SYNTHETIC_EVENTS_H
#घोषणा __PERF_SYNTHETIC_EVENTS_H

#समावेश <stdbool.h>
#समावेश <sys/types.h> // pid_t
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

काष्ठा auxtrace_record;
काष्ठा dso;
काष्ठा evlist;
काष्ठा evsel;
काष्ठा machine;
काष्ठा perf_counts_values;
काष्ठा perf_cpu_map;
काष्ठा perf_event_attr;
काष्ठा perf_event_mmap_page;
काष्ठा perf_sample;
काष्ठा perf_session;
काष्ठा perf_stat_config;
काष्ठा perf_thपढ़ो_map;
काष्ठा perf_tool;
काष्ठा record_opts;
काष्ठा target;

जोड़ perf_event;

प्रकार पूर्णांक (*perf_event__handler_t)(काष्ठा perf_tool *tool, जोड़ perf_event *event,
				     काष्ठा perf_sample *sample, काष्ठा machine *machine);

पूर्णांक perf_event__synthesize_attrs(काष्ठा perf_tool *tool, काष्ठा evlist *evlist, perf_event__handler_t process);
पूर्णांक perf_event__synthesize_attr(काष्ठा perf_tool *tool, काष्ठा perf_event_attr *attr, u32 ids, u64 *id, perf_event__handler_t process);
पूर्णांक perf_event__synthesize_build_id(काष्ठा perf_tool *tool, काष्ठा dso *pos, u16 misc, perf_event__handler_t process, काष्ठा machine *machine);
पूर्णांक perf_event__synthesize_cpu_map(काष्ठा perf_tool *tool, काष्ठा perf_cpu_map *cpus, perf_event__handler_t process, काष्ठा machine *machine);
पूर्णांक perf_event__synthesize_event_update_cpus(काष्ठा perf_tool *tool, काष्ठा evsel *evsel, perf_event__handler_t process);
पूर्णांक perf_event__synthesize_event_update_name(काष्ठा perf_tool *tool, काष्ठा evsel *evsel, perf_event__handler_t process);
पूर्णांक perf_event__synthesize_event_update_scale(काष्ठा perf_tool *tool, काष्ठा evsel *evsel, perf_event__handler_t process);
पूर्णांक perf_event__synthesize_event_update_unit(काष्ठा perf_tool *tool, काष्ठा evsel *evsel, perf_event__handler_t process);
पूर्णांक perf_event__synthesize_extra_attr(काष्ठा perf_tool *tool, काष्ठा evlist *evsel_list, perf_event__handler_t process, bool is_pipe);
पूर्णांक perf_event__synthesize_extra_kmaps(काष्ठा perf_tool *tool, perf_event__handler_t process, काष्ठा machine *machine);
पूर्णांक perf_event__synthesize_features(काष्ठा perf_tool *tool, काष्ठा perf_session *session, काष्ठा evlist *evlist, perf_event__handler_t process);
पूर्णांक perf_event__synthesize_id_index(काष्ठा perf_tool *tool, perf_event__handler_t process, काष्ठा evlist *evlist, काष्ठा machine *machine);
पूर्णांक perf_event__synthesize_kernel_mmap(काष्ठा perf_tool *tool, perf_event__handler_t process, काष्ठा machine *machine);
पूर्णांक perf_event__synthesize_mmap_events(काष्ठा perf_tool *tool, जोड़ perf_event *event, pid_t pid, pid_t tgid, perf_event__handler_t process, काष्ठा machine *machine, bool mmap_data);
पूर्णांक perf_event__synthesize_modules(काष्ठा perf_tool *tool, perf_event__handler_t process, काष्ठा machine *machine);
पूर्णांक perf_event__synthesize_namespaces(काष्ठा perf_tool *tool, जोड़ perf_event *event, pid_t pid, pid_t tgid, perf_event__handler_t process, काष्ठा machine *machine);
पूर्णांक perf_event__synthesize_cgroups(काष्ठा perf_tool *tool, perf_event__handler_t process, काष्ठा machine *machine);
पूर्णांक perf_event__synthesize_sample(जोड़ perf_event *event, u64 type, u64 पढ़ो_क्रमmat, स्थिर काष्ठा perf_sample *sample);
पूर्णांक perf_event__synthesize_stat_config(काष्ठा perf_tool *tool, काष्ठा perf_stat_config *config, perf_event__handler_t process, काष्ठा machine *machine);
पूर्णांक perf_event__synthesize_stat_events(काष्ठा perf_stat_config *config, काष्ठा perf_tool *tool, काष्ठा evlist *evlist, perf_event__handler_t process, bool attrs);
पूर्णांक perf_event__synthesize_stat_round(काष्ठा perf_tool *tool, u64 समय, u64 type, perf_event__handler_t process, काष्ठा machine *machine);
पूर्णांक perf_event__synthesize_stat(काष्ठा perf_tool *tool, u32 cpu, u32 thपढ़ो, u64 id, काष्ठा perf_counts_values *count, perf_event__handler_t process, काष्ठा machine *machine);
पूर्णांक perf_event__syntheमाप_प्रकारhपढ़ो_map2(काष्ठा perf_tool *tool, काष्ठा perf_thपढ़ो_map *thपढ़ोs, perf_event__handler_t process, काष्ठा machine *machine);
पूर्णांक perf_event__syntheमाप_प्रकारhपढ़ो_map(काष्ठा perf_tool *tool, काष्ठा perf_thपढ़ो_map *thपढ़ोs, perf_event__handler_t process, काष्ठा machine *machine, bool mmap_data);
पूर्णांक perf_event__syntheमाप_प्रकारhपढ़ोs(काष्ठा perf_tool *tool, perf_event__handler_t process, काष्ठा machine *machine, bool mmap_data, अचिन्हित पूर्णांक nr_thपढ़ोs_synthesize);
पूर्णांक perf_event__syntheमाप_प्रकारracing_data(काष्ठा perf_tool *tool, पूर्णांक fd, काष्ठा evlist *evlist, perf_event__handler_t process);
पूर्णांक perf_event__synth_समय_conv(स्थिर काष्ठा perf_event_mmap_page *pc, काष्ठा perf_tool *tool, perf_event__handler_t process, काष्ठा machine *machine);
pid_t perf_event__synthesize_comm(काष्ठा perf_tool *tool, जोड़ perf_event *event, pid_t pid, perf_event__handler_t process, काष्ठा machine *machine);

पूर्णांक perf_tool__process_synth_event(काष्ठा perf_tool *tool, जोड़ perf_event *event, काष्ठा machine *machine, perf_event__handler_t process);

माप_प्रकार perf_event__sample_event_size(स्थिर काष्ठा perf_sample *sample, u64 type, u64 पढ़ो_क्रमmat);

पूर्णांक __machine__syntheमाप_प्रकारhपढ़ोs(काष्ठा machine *machine, काष्ठा perf_tool *tool,
				  काष्ठा target *target, काष्ठा perf_thपढ़ो_map *thपढ़ोs,
				  perf_event__handler_t process, bool data_mmap,
				  अचिन्हित पूर्णांक nr_thपढ़ोs_synthesize);
पूर्णांक machine__syntheमाप_प्रकारhपढ़ोs(काष्ठा machine *machine, काष्ठा target *target,
				काष्ठा perf_thपढ़ो_map *thपढ़ोs, bool data_mmap,
				अचिन्हित पूर्णांक nr_thपढ़ोs_synthesize);

#अगर_घोषित HAVE_AUXTRACE_SUPPORT
पूर्णांक perf_event__synthesize_auxtrace_info(काष्ठा auxtrace_record *itr, काष्ठा perf_tool *tool,
					 काष्ठा perf_session *session, perf_event__handler_t process);

#अन्यथा // HAVE_AUXTRACE_SUPPORT

#समावेश <त्रुटिसं.स>

अटल अंतरभूत पूर्णांक
perf_event__synthesize_auxtrace_info(काष्ठा auxtrace_record *itr __maybe_unused,
				     काष्ठा perf_tool *tool __maybe_unused,
				     काष्ठा perf_session *session __maybe_unused,
				     perf_event__handler_t process __maybe_unused)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर // HAVE_AUXTRACE_SUPPORT

#अगर_घोषित HAVE_LIBBPF_SUPPORT
पूर्णांक perf_event__synthesize_bpf_events(काष्ठा perf_session *session, perf_event__handler_t process,
				      काष्ठा machine *machine, काष्ठा record_opts *opts);
#अन्यथा // HAVE_LIBBPF_SUPPORT
अटल अंतरभूत पूर्णांक perf_event__synthesize_bpf_events(काष्ठा perf_session *session __maybe_unused,
						    perf_event__handler_t process __maybe_unused,
						    काष्ठा machine *machine __maybe_unused,
						    काष्ठा record_opts *opts __maybe_unused)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर // HAVE_LIBBPF_SUPPORT

#पूर्ण_अगर // __PERF_SYNTHETIC_EVENTS_H
