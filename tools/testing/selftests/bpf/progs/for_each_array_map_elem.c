<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */
#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>

अक्षर _license[] SEC("license") = "GPL";

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 3);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण arraymap SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण percpu_map SEC(".maps");

काष्ठा callback_ctx अणु
	पूर्णांक output;
पूर्ण;

अटल __u64
check_array_elem(काष्ठा bpf_map *map, __u32 *key, __u64 *val,
		 काष्ठा callback_ctx *data)
अणु
	data->output += *val;
	अगर (*key == 1)
		वापस 1; /* stop the iteration */
	वापस 0;
पूर्ण

__u32 cpu = 0;
__u64 percpu_val = 0;

अटल __u64
check_percpu_elem(काष्ठा bpf_map *map, __u32 *key, __u64 *val,
		  काष्ठा callback_ctx *data)
अणु
	cpu = bpf_get_smp_processor_id();
	percpu_val = *val;
	वापस 0;
पूर्ण

u32 arraymap_output = 0;

SEC("classifier")
पूर्णांक test_pkt_access(काष्ठा __sk_buff *skb)
अणु
	काष्ठा callback_ctx data;

	data.output = 0;
	bpf_क्रम_each_map_elem(&arraymap, check_array_elem, &data, 0);
	arraymap_output = data.output;

	bpf_क्रम_each_map_elem(&percpu_map, check_percpu_elem, (व्योम *)0, 0);
	वापस 0;
पूर्ण
