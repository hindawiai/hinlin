<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

पूर्णांक _version SEC("version") = 1;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u64);
	__uपूर्णांक(pinning, LIBBPF_PIN_BY_NAME);
पूर्ण pinmap SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण nopinmap SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u64);
	__uपूर्णांक(pinning, LIBBPF_PIN_NONE);
पूर्ण nopinmap2 SEC(".maps");

अक्षर _license[] SEC("license") = "GPL";
