<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook

#समावेश <linux/bpf.h>
#समावेश <मानक_निवेशt.h>
#समावेश <bpf/bpf_helpers.h>

अक्षर _license[] SEC("license") = "GPL";

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(map_flags, BPF_F_MMAPABLE | BPF_F_RDONLY_PROG);
	__type(key, __u32);
	__type(value, अक्षर);
पूर्ण rकरोnly_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(map_flags, BPF_F_MMAPABLE);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण data_map SEC(".maps");

__u64 in_val = 0;
__u64 out_val = 0;

SEC("raw_tracepoint/sys_enter")
पूर्णांक test_mmap(व्योम *ctx)
अणु
	पूर्णांक zero = 0, one = 1, two = 2, far = 1500;
	__u64 val, *p;

	out_val = in_val;

	/* data_map[2] = in_val; */
	bpf_map_update_elem(&data_map, &two, (स्थिर व्योम *)&in_val, 0);

	/* data_map[1] = data_map[0] * 2; */
	p = bpf_map_lookup_elem(&data_map, &zero);
	अगर (p) अणु
		val = (*p) * 2;
		bpf_map_update_elem(&data_map, &one, &val, 0);
	पूर्ण

	/* data_map[far] = in_val * 3; */
	val = in_val * 3;
	bpf_map_update_elem(&data_map, &far, &val, 0);

	वापस 0;
पूर्ण

