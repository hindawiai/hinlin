<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook
#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>

#अगर_अघोषित PERF_MAX_STACK_DEPTH
#घोषणा PERF_MAX_STACK_DEPTH         127
#पूर्ण_अगर

प्रकार __u64 stack_trace_t[PERF_MAX_STACK_DEPTH];
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_STACK_TRACE);
	__uपूर्णांक(max_entries, 16384);
	__uपूर्णांक(key_size, माप(__u32));
	__uपूर्णांक(value_size, माप(stack_trace_t));
पूर्ण stackmap SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, stack_trace_t);
पूर्ण stackdata_map SEC(".maps");

दीर्घ stackid_kernel = 1;
दीर्घ stackid_user = 1;
दीर्घ stack_kernel = 1;
दीर्घ stack_user = 1;

SEC("perf_event")
पूर्णांक oncpu(व्योम *ctx)
अणु
	stack_trace_t *trace;
	__u32 key = 0;
	दीर्घ val;

	val = bpf_get_stackid(ctx, &stackmap, 0);
	अगर (val > 0)
		stackid_kernel = 2;
	val = bpf_get_stackid(ctx, &stackmap, BPF_F_USER_STACK);
	अगर (val > 0)
		stackid_user = 2;

	trace = bpf_map_lookup_elem(&stackdata_map, &key);
	अगर (!trace)
		वापस 0;

	val = bpf_get_stack(ctx, trace, माप(stack_trace_t), 0);
	अगर (val > 0)
		stack_kernel = 2;

	val = bpf_get_stack(ctx, trace, माप(stack_trace_t), BPF_F_USER_STACK);
	अगर (val > 0)
		stack_user = 2;

	वापस 0;
पूर्ण

अक्षर LICENSE[] SEC("license") = "GPL";
