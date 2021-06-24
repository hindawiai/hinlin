<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
पूर्ण array_1 SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
	__uपूर्णांक(map_flags, BPF_F_PRESERVE_ELEMS);
पूर्ण array_2 SEC(".maps");

SEC("raw_tp/sched_switch")
पूर्णांक BPF_PROG(पढ़ो_array_1)
अणु
	काष्ठा bpf_perf_event_value val;

	वापस bpf_perf_event_पढ़ो_value(&array_1, 0, &val, माप(val));
पूर्ण

SEC("raw_tp/task_rename")
पूर्णांक BPF_PROG(पढ़ो_array_2)
अणु
	काष्ठा bpf_perf_event_value val;

	वापस bpf_perf_event_पढ़ो_value(&array_2, 0, &val, माप(val));
पूर्ण

अक्षर LICENSE[] SEC("license") = "GPL";
