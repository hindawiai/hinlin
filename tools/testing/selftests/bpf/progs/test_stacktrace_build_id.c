<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Facebook

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

#अगर_अघोषित PERF_MAX_STACK_DEPTH
#घोषणा PERF_MAX_STACK_DEPTH         127
#पूर्ण_अगर

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण control_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 16384);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण stackid_hmap SEC(".maps");

प्रकार काष्ठा bpf_stack_build_id stack_trace_t[PERF_MAX_STACK_DEPTH];

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_STACK_TRACE);
	__uपूर्णांक(max_entries, 128);
	__uपूर्णांक(map_flags, BPF_F_STACK_BUILD_ID);
	__uपूर्णांक(key_size, माप(__u32));
	__uपूर्णांक(value_size, माप(stack_trace_t));
पूर्ण stackmap SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 128);
	__type(key, __u32);
	__type(value, stack_trace_t);
पूर्ण stack_amap SEC(".maps");

/* taken from /sys/kernel/debug/tracing/events/अक्रमom/uअक्रमom_पढ़ो/क्रमmat */
काष्ठा अक्रमom_uअक्रमom_args अणु
	अचिन्हित दीर्घ दीर्घ pad;
	पूर्णांक got_bits;
	पूर्णांक pool_left;
	पूर्णांक input_left;
पूर्ण;

SEC("tracepoint/random/urandom_read")
पूर्णांक oncpu(काष्ठा अक्रमom_uअक्रमom_args *args)
अणु
	__u32 max_len = माप(काष्ठा bpf_stack_build_id)
			* PERF_MAX_STACK_DEPTH;
	__u32 key = 0, val = 0, *value_p;
	व्योम *stack_p;

	value_p = bpf_map_lookup_elem(&control_map, &key);
	अगर (value_p && *value_p)
		वापस 0; /* skip अगर non-zero *value_p */

	/* The size of stackmap and stackid_hmap should be the same */
	key = bpf_get_stackid(args, &stackmap, BPF_F_USER_STACK);
	अगर ((पूर्णांक)key >= 0) अणु
		bpf_map_update_elem(&stackid_hmap, &key, &val, 0);
		stack_p = bpf_map_lookup_elem(&stack_amap, &key);
		अगर (stack_p)
			bpf_get_stack(args, stack_p, max_len,
				      BPF_F_USER_STACK | BPF_F_USER_BUILD_ID);
	पूर्ण

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
__u32 _version SEC("version") = 1; /* ignored by tracepoपूर्णांकs, required by libbpf.a */
