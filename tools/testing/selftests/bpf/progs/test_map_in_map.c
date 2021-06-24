<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018 Facebook */
#समावेश <मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <linux/types.h>
#समावेश <bpf/bpf_helpers.h>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY_OF_MAPS);
	__uपूर्णांक(max_entries, 1);
	__uपूर्णांक(map_flags, 0);
	__uपूर्णांक(key_size, माप(__u32));
	/* must be माप(__u32) क्रम map in map */
	__uपूर्णांक(value_size, माप(__u32));
पूर्ण mim_array SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH_OF_MAPS);
	__uपूर्णांक(max_entries, 1);
	__uपूर्णांक(map_flags, 0);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	/* must be माप(__u32) क्रम map in map */
	__uपूर्णांक(value_size, माप(__u32));
पूर्ण mim_hash SEC(".maps");

SEC("xdp_mimtest")
पूर्णांक xdp_mimtest0(काष्ठा xdp_md *ctx)
अणु
	पूर्णांक value = 123;
	पूर्णांक *value_p;
	पूर्णांक key = 0;
	व्योम *map;

	map = bpf_map_lookup_elem(&mim_array, &key);
	अगर (!map)
		वापस XDP_DROP;

	bpf_map_update_elem(map, &key, &value, 0);
	value_p = bpf_map_lookup_elem(map, &key);
	अगर (!value_p || *value_p != 123)
		वापस XDP_DROP;

	map = bpf_map_lookup_elem(&mim_hash, &key);
	अगर (!map)
		वापस XDP_DROP;

	bpf_map_update_elem(map, &key, &value, 0);

	वापस XDP_PASS;
पूर्ण

पूर्णांक _version SEC("version") = 1;
अक्षर _license[] SEC("license") = "GPL";
