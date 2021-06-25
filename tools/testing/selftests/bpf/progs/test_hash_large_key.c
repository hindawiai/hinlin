<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

अक्षर _license[] SEC("license") = "GPL";

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 2);
	__type(key, काष्ठा bigelement);
	__type(value, __u32);
पूर्ण hash_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, काष्ठा bigelement);
पूर्ण key_map SEC(".maps");

काष्ठा bigelement अणु
	पूर्णांक a;
	अक्षर b[4096];
	दीर्घ दीर्घ c;
पूर्ण;

SEC("raw_tracepoint/sys_enter")
पूर्णांक bpf_hash_large_key_test(व्योम *ctx)
अणु
	पूर्णांक zero = 0, err = 1, value = 42;
	काष्ठा bigelement *key;

	key = bpf_map_lookup_elem(&key_map, &zero);
	अगर (!key)
		वापस 0;

	key->c = 1;
	अगर (bpf_map_update_elem(&hash_map, key, &value, BPF_ANY))
		वापस 0;

	वापस 0;
पूर्ण

