<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
// Copyright (c) 2020 Facebook
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

/* map of perf event fds, num_cpu * num_metric entries */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uपूर्णांक(key_size, माप(__u32));
	__uपूर्णांक(value_size, माप(पूर्णांक));
पूर्ण events SEC(".maps");

/* पढ़ोings at fentry */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(key_size, माप(__u32));
	__uपूर्णांक(value_size, माप(काष्ठा bpf_perf_event_value));
	__uपूर्णांक(max_entries, 1);
पूर्ण fentry_पढ़ोings SEC(".maps");

/* accumulated पढ़ोings */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(key_size, माप(__u32));
	__uपूर्णांक(value_size, माप(काष्ठा bpf_perf_event_value));
	__uपूर्णांक(max_entries, 1);
पूर्ण accum_पढ़ोings SEC(".maps");

स्थिर अस्थिर __u32 num_cpu = 1;

SEC("fentry/XXX")
पूर्णांक BPF_PROG(fentry_XXX)
अणु
	__u32 key = bpf_get_smp_processor_id();
	काष्ठा bpf_perf_event_value *ptr;
	__u32 zero = 0;
	दीर्घ err;

	/* look up beक्रमe पढ़ोing, to reduce error */
	ptr = bpf_map_lookup_elem(&fentry_पढ़ोings, &zero);
	अगर (!ptr)
		वापस 0;

	err = bpf_perf_event_पढ़ो_value(&events, key, ptr, माप(*ptr));
	अगर (err)
		वापस 0;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
fनिकास_update_maps(काष्ठा bpf_perf_event_value *after)
अणु
	काष्ठा bpf_perf_event_value *beक्रमe, dअगरf;
	__u32 zero = 0;

	beक्रमe = bpf_map_lookup_elem(&fentry_पढ़ोings, &zero);
	/* only account samples with a valid fentry_पढ़ोing */
	अगर (beक्रमe && beक्रमe->counter) अणु
		काष्ठा bpf_perf_event_value *accum;

		dअगरf.counter = after->counter - beक्रमe->counter;
		dअगरf.enabled = after->enabled - beक्रमe->enabled;
		dअगरf.running = after->running - beक्रमe->running;

		accum = bpf_map_lookup_elem(&accum_पढ़ोings, &zero);
		अगर (accum) अणु
			accum->counter += dअगरf.counter;
			accum->enabled += dअगरf.enabled;
			accum->running += dअगरf.running;
		पूर्ण
	पूर्ण
पूर्ण

SEC("fexit/XXX")
पूर्णांक BPF_PROG(fनिकास_XXX)
अणु
	काष्ठा bpf_perf_event_value पढ़ोing;
	__u32 cpu = bpf_get_smp_processor_id();
	पूर्णांक err;

	/* पढ़ो all events beक्रमe updating the maps, to reduce error */
	err = bpf_perf_event_पढ़ो_value(&events, cpu, &पढ़ोing, माप(पढ़ोing));
	अगर (err)
		वापस 0;

	fनिकास_update_maps(&पढ़ोing);
	वापस 0;
पूर्ण

अक्षर LICENSE[] SEC("license") = "Dual BSD/GPL";
