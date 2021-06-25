<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */
#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>

अक्षर _license[] SEC("license") = "GPL";

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 3);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण hashmap SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_HASH);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण percpu_map SEC(".maps");

काष्ठा callback_ctx अणु
	काष्ठा __sk_buff *ctx;
	पूर्णांक input;
	पूर्णांक output;
पूर्ण;

अटल __u64
check_hash_elem(काष्ठा bpf_map *map, __u32 *key, __u64 *val,
		काष्ठा callback_ctx *data)
अणु
	काष्ठा __sk_buff *skb = data->ctx;
	__u32 k;
	__u64 v;

	अगर (skb) अणु
		k = *key;
		v = *val;
		अगर (skb->len == 10000 && k == 10 && v == 10)
			data->output = 3; /* impossible path */
		अन्यथा
			data->output = 4;
	पूर्ण अन्यथा अणु
		data->output = data->input;
		bpf_map_delete_elem(map, key);
	पूर्ण

	वापस 0;
पूर्ण

__u32 cpu = 0;
__u32 percpu_called = 0;
__u32 percpu_key = 0;
__u64 percpu_val = 0;
पूर्णांक percpu_output = 0;

अटल __u64
check_percpu_elem(काष्ठा bpf_map *map, __u32 *key, __u64 *val,
		  काष्ठा callback_ctx *unused)
अणु
	काष्ठा callback_ctx data;

	percpu_called++;
	cpu = bpf_get_smp_processor_id();
	percpu_key = *key;
	percpu_val = *val;

	data.ctx = 0;
	data.input = 100;
	data.output = 0;
	bpf_क्रम_each_map_elem(&hashmap, check_hash_elem, &data, 0);
	percpu_output = data.output;

	वापस 0;
पूर्ण

पूर्णांक hashmap_output = 0;
पूर्णांक hashmap_elems = 0;
पूर्णांक percpu_map_elems = 0;

SEC("classifier")
पूर्णांक test_pkt_access(काष्ठा __sk_buff *skb)
अणु
	काष्ठा callback_ctx data;

	data.ctx = skb;
	data.input = 10;
	data.output = 0;
	hashmap_elems = bpf_क्रम_each_map_elem(&hashmap, check_hash_elem, &data, 0);
	hashmap_output = data.output;

	percpu_map_elems = bpf_क्रम_each_map_elem(&percpu_map, check_percpu_elem,
						 (व्योम *)0, 0);
	वापस 0;
पूर्ण
