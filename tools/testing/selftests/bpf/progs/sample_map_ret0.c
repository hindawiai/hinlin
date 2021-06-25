<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-2-Clause) */
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

काष्ठा bpf_map_def SEC("maps") htab = अणु
	.type = BPF_MAP_TYPE_HASH,
	.key_size = माप(__u32),
	.value_size = माप(दीर्घ),
	.max_entries = 2,
पूर्ण;

काष्ठा bpf_map_def SEC("maps") array = अणु
	.type = BPF_MAP_TYPE_ARRAY,
	.key_size = माप(__u32),
	.value_size = माप(दीर्घ),
	.max_entries = 2,
पूर्ण;

/* Sample program which should always load क्रम testing control paths. */
SEC(".text") पूर्णांक func()
अणु
	__u64 key64 = 0;
	__u32 key = 0;
	दीर्घ *value;

	value = bpf_map_lookup_elem(&htab, &key);
	अगर (!value)
		वापस 1;
	value = bpf_map_lookup_elem(&array, &key64);
	अगर (!value)
		वापस 1;

	वापस 0;
पूर्ण
