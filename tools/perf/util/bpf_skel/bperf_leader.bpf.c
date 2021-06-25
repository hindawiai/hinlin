<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
// Copyright (c) 2021 Facebook
#समावेश <linux/bpf.h>
#समावेश <linux/perf_event.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश "bperf.h"

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uपूर्णांक(key_size, माप(__u32));
	__uपूर्णांक(value_size, माप(पूर्णांक));
	__uपूर्णांक(map_flags, BPF_F_PRESERVE_ELEMS);
पूर्ण events SEC(".maps");

पढ़ोing_map prev_पढ़ोings SEC(".maps");
पढ़ोing_map dअगरf_पढ़ोings SEC(".maps");

SEC("raw_tp/sched_switch")
पूर्णांक BPF_PROG(on_चयन)
अणु
	काष्ठा bpf_perf_event_value val, *prev_val, *dअगरf_val;
	__u32 key = bpf_get_smp_processor_id();
	__u32 zero = 0;
	दीर्घ err;

	prev_val = bpf_map_lookup_elem(&prev_पढ़ोings, &zero);
	अगर (!prev_val)
		वापस 0;

	dअगरf_val = bpf_map_lookup_elem(&dअगरf_पढ़ोings, &zero);
	अगर (!dअगरf_val)
		वापस 0;

	err = bpf_perf_event_पढ़ो_value(&events, key, &val, माप(val));
	अगर (err)
		वापस 0;

	dअगरf_val->counter = val.counter - prev_val->counter;
	dअगरf_val->enabled = val.enabled - prev_val->enabled;
	dअगरf_val->running = val.running - prev_val->running;
	*prev_val = val;
	वापस 0;
पूर्ण

अक्षर LICENSE[] SEC("license") = "Dual BSD/GPL";
