<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
// Copyright (c) 2020 Facebook
#समावेश <vmlinux.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

/* map of perf event fds, num_cpu * num_metric entries */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uपूर्णांक(key_size, माप(u32));
	__uपूर्णांक(value_size, माप(पूर्णांक));
पूर्ण events SEC(".maps");

/* पढ़ोings at fentry */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(key_size, माप(u32));
	__uपूर्णांक(value_size, माप(काष्ठा bpf_perf_event_value));
पूर्ण fentry_पढ़ोings SEC(".maps");

/* accumulated पढ़ोings */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(key_size, माप(u32));
	__uपूर्णांक(value_size, माप(काष्ठा bpf_perf_event_value));
पूर्ण accum_पढ़ोings SEC(".maps");

/* sample counts, one per cpu */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(key_size, माप(u32));
	__uपूर्णांक(value_size, माप(u64));
पूर्ण counts SEC(".maps");

स्थिर अस्थिर __u32 num_cpu = 1;
स्थिर अस्थिर __u32 num_metric = 1;
#घोषणा MAX_NUM_MATRICS 4

SEC("fentry/XXX")
पूर्णांक BPF_PROG(fentry_XXX)
अणु
	काष्ठा bpf_perf_event_value *ptrs[MAX_NUM_MATRICS];
	u32 key = bpf_get_smp_processor_id();
	u32 i;

	/* look up beक्रमe पढ़ोing, to reduce error */
	क्रम (i = 0; i < num_metric && i < MAX_NUM_MATRICS; i++) अणु
		u32 flag = i;

		ptrs[i] = bpf_map_lookup_elem(&fentry_पढ़ोings, &flag);
		अगर (!ptrs[i])
			वापस 0;
	पूर्ण

	क्रम (i = 0; i < num_metric && i < MAX_NUM_MATRICS; i++) अणु
		काष्ठा bpf_perf_event_value पढ़ोing;
		पूर्णांक err;

		err = bpf_perf_event_पढ़ो_value(&events, key, &पढ़ोing,
						माप(पढ़ोing));
		अगर (err)
			वापस 0;
		*(ptrs[i]) = पढ़ोing;
		key += num_cpu;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
fनिकास_update_maps(u32 id, काष्ठा bpf_perf_event_value *after)
अणु
	काष्ठा bpf_perf_event_value *beक्रमe, dअगरf;

	beक्रमe = bpf_map_lookup_elem(&fentry_पढ़ोings, &id);
	/* only account samples with a valid fentry_पढ़ोing */
	अगर (beक्रमe && beक्रमe->counter) अणु
		काष्ठा bpf_perf_event_value *accum;

		dअगरf.counter = after->counter - beक्रमe->counter;
		dअगरf.enabled = after->enabled - beक्रमe->enabled;
		dअगरf.running = after->running - beक्रमe->running;

		accum = bpf_map_lookup_elem(&accum_पढ़ोings, &id);
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
	काष्ठा bpf_perf_event_value पढ़ोings[MAX_NUM_MATRICS];
	u32 cpu = bpf_get_smp_processor_id();
	u32 i, zero = 0;
	पूर्णांक err;
	u64 *count;

	/* पढ़ो all events beक्रमe updating the maps, to reduce error */
	क्रम (i = 0; i < num_metric && i < MAX_NUM_MATRICS; i++) अणु
		err = bpf_perf_event_पढ़ो_value(&events, cpu + i * num_cpu,
						पढ़ोings + i, माप(*पढ़ोings));
		अगर (err)
			वापस 0;
	पूर्ण
	count = bpf_map_lookup_elem(&counts, &zero);
	अगर (count) अणु
		*count += 1;
		क्रम (i = 0; i < num_metric && i < MAX_NUM_MATRICS; i++)
			fनिकास_update_maps(i, &पढ़ोings[i]);
	पूर्ण
	वापस 0;
पूर्ण

अक्षर LICENSE[] SEC("license") = "Dual BSD/GPL";
