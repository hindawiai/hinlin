<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook

#समावेश <linux/ptrace.h>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

#घोषणा VAR_NUM 2

काष्ठा hmap_elem अणु
	काष्ठा bpf_spin_lock lock;
	पूर्णांक var[VAR_NUM];
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, काष्ठा hmap_elem);
पूर्ण hash_map SEC(".maps");

SEC("freplace/handle_kprobe")
पूर्णांक new_handle_kprobe(काष्ठा pt_regs *ctx)
अणु
	काष्ठा hmap_elem zero = अणुपूर्ण, *val;
	पूर्णांक key = 0;

	val = bpf_map_lookup_elem(&hash_map, &key);
	अगर (!val)
		वापस 1;
	/* spin_lock in hash map */
	bpf_spin_lock(&val->lock);
	val->var[0] = 99;
	bpf_spin_unlock(&val->lock);

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
