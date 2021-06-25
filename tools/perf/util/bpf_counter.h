<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_BPF_COUNTER_H
#घोषणा __PERF_BPF_COUNTER_H 1

#समावेश <linux/list.h>

काष्ठा evsel;
काष्ठा target;
काष्ठा bpf_counter;

प्रकार पूर्णांक (*bpf_counter_evsel_op)(काष्ठा evsel *evsel);
प्रकार पूर्णांक (*bpf_counter_evsel_target_op)(काष्ठा evsel *evsel,
					   काष्ठा target *target);
प्रकार पूर्णांक (*bpf_counter_evsel_install_pe_op)(काष्ठा evsel *evsel,
					       पूर्णांक cpu,
					       पूर्णांक fd);

काष्ठा bpf_counter_ops अणु
	bpf_counter_evsel_target_op load;
	bpf_counter_evsel_op enable;
	bpf_counter_evsel_op disable;
	bpf_counter_evsel_op पढ़ो;
	bpf_counter_evsel_op destroy;
	bpf_counter_evsel_install_pe_op install_pe;
पूर्ण;

काष्ठा bpf_counter अणु
	व्योम *skel;
	काष्ठा list_head list;
पूर्ण;

#अगर_घोषित HAVE_BPF_SKEL

पूर्णांक bpf_counter__load(काष्ठा evsel *evsel, काष्ठा target *target);
पूर्णांक bpf_counter__enable(काष्ठा evsel *evsel);
पूर्णांक bpf_counter__disable(काष्ठा evsel *evsel);
पूर्णांक bpf_counter__पढ़ो(काष्ठा evsel *evsel);
व्योम bpf_counter__destroy(काष्ठा evsel *evsel);
पूर्णांक bpf_counter__install_pe(काष्ठा evsel *evsel, पूर्णांक cpu, पूर्णांक fd);

#अन्यथा /* HAVE_BPF_SKEL */

#समावेश <linux/err.h>

अटल अंतरभूत पूर्णांक bpf_counter__load(काष्ठा evsel *evsel __maybe_unused,
				    काष्ठा target *target __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक bpf_counter__enable(काष्ठा evsel *evsel __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक bpf_counter__disable(काष्ठा evsel *evsel __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक bpf_counter__पढ़ो(काष्ठा evsel *evsel __maybe_unused)
अणु
	वापस -EAGAIN;
पूर्ण

अटल अंतरभूत व्योम bpf_counter__destroy(काष्ठा evsel *evsel __maybe_unused)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक bpf_counter__install_pe(काष्ठा evsel *evsel __maybe_unused,
					  पूर्णांक cpu __maybe_unused,
					  पूर्णांक fd __maybe_unused)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* HAVE_BPF_SKEL */

#पूर्ण_अगर /* __PERF_BPF_COUNTER_H */
