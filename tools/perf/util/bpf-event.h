<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_BPF_EVENT_H
#घोषणा __PERF_BPF_EVENT_H

#समावेश <linux/compiler.h>
#समावेश <linux/rbtree.h>
#समावेश <pthपढ़ो.h>
#समावेश <api/fd/array.h>
#समावेश <मानकपन.स>

काष्ठा bpf_prog_info;
काष्ठा machine;
जोड़ perf_event;
काष्ठा perf_env;
काष्ठा perf_sample;
काष्ठा perf_session;
काष्ठा record_opts;
काष्ठा evlist;
काष्ठा target;

काष्ठा bpf_prog_info_node अणु
	काष्ठा bpf_prog_info_linear	*info_linear;
	काष्ठा rb_node			rb_node;
पूर्ण;

काष्ठा btf_node अणु
	काष्ठा rb_node	rb_node;
	u32		id;
	u32		data_size;
	अक्षर		data[];
पूर्ण;

#अगर_घोषित HAVE_LIBBPF_SUPPORT
पूर्णांक machine__process_bpf(काष्ठा machine *machine, जोड़ perf_event *event,
			 काष्ठा perf_sample *sample);
पूर्णांक evlist__add_bpf_sb_event(काष्ठा evlist *evlist, काष्ठा perf_env *env);
व्योम bpf_event__prपूर्णांक_bpf_prog_info(काष्ठा bpf_prog_info *info,
				    काष्ठा perf_env *env,
				    खाता *fp);
#अन्यथा
अटल अंतरभूत पूर्णांक machine__process_bpf(काष्ठा machine *machine __maybe_unused,
				       जोड़ perf_event *event __maybe_unused,
				       काष्ठा perf_sample *sample __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक evlist__add_bpf_sb_event(काष्ठा evlist *evlist __maybe_unused,
					   काष्ठा perf_env *env __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम bpf_event__prपूर्णांक_bpf_prog_info(काष्ठा bpf_prog_info *info __maybe_unused,
						  काष्ठा perf_env *env __maybe_unused,
						  खाता *fp __maybe_unused)
अणु

पूर्ण
#पूर्ण_अगर // HAVE_LIBBPF_SUPPORT
#पूर्ण_अगर
