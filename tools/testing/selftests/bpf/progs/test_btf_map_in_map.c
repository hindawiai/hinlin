<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2020 Facebook */
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

काष्ठा inner_map अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण inner_map1 SEC(".maps"),
  inner_map2 SEC(".maps");

काष्ठा inner_map_sz2 अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 2);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण inner_map_sz2 SEC(".maps");

काष्ठा outer_arr अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY_OF_MAPS);
	__uपूर्णांक(max_entries, 3);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
	/* it's possible to use anonymous काष्ठा as inner map definition here */
	__array(values, काष्ठा अणु
		__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
		/* changing max_entries to 2 will fail during load
		 * due to incompatibility with inner_map definition */
		__uपूर्णांक(max_entries, 1);
		__type(key, पूर्णांक);
		__type(value, पूर्णांक);
	पूर्ण);
पूर्ण outer_arr SEC(".maps") = अणु
	/* (व्योम *) cast is necessary because we didn't use `काष्ठा inner_map`
	 * in __inner(values, ...)
	 * Actually, a conscious efक्रमt is required to screw up initialization
	 * of inner map slots, which is a great thing!
	 */
	.values = अणु (व्योम *)&inner_map1, 0, (व्योम *)&inner_map2 पूर्ण,
पूर्ण;

काष्ठा inner_map_sz3 अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(map_flags, BPF_F_INNER_MAP);
	__uपूर्णांक(max_entries, 3);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण inner_map3 SEC(".maps"),
  inner_map4 SEC(".maps");

काष्ठा inner_map_sz4 अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(map_flags, BPF_F_INNER_MAP);
	__uपूर्णांक(max_entries, 5);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण inner_map5 SEC(".maps");

काष्ठा outer_arr_dyn अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY_OF_MAPS);
	__uपूर्णांक(max_entries, 3);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
	__array(values, काष्ठा अणु
		__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
		__uपूर्णांक(map_flags, BPF_F_INNER_MAP);
		__uपूर्णांक(max_entries, 1);
		__type(key, पूर्णांक);
		__type(value, पूर्णांक);
	पूर्ण);
पूर्ण outer_arr_dyn SEC(".maps") = अणु
	.values = अणु
		[0] = (व्योम *)&inner_map3,
		[1] = (व्योम *)&inner_map4,
		[2] = (व्योम *)&inner_map5,
	पूर्ण,
पूर्ण;

काष्ठा outer_hash अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH_OF_MAPS);
	__uपूर्णांक(max_entries, 5);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	/* Here everything works flawlessly due to reuse of काष्ठा inner_map
	 * and compiler will complain at the attempt to use non-inner_map
	 * references below. This is great experience.
	 */
	__array(values, काष्ठा inner_map);
पूर्ण outer_hash SEC(".maps") = अणु
	.values = अणु
		[0] = &inner_map2,
		[4] = &inner_map1,
	पूर्ण,
पूर्ण;

काष्ठा sockarr_sz1 अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_REUSEPORT_SOCKARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण sockarr_sz1 SEC(".maps");

काष्ठा sockarr_sz2 अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_REUSEPORT_SOCKARRAY);
	__uपूर्णांक(max_entries, 2);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण sockarr_sz2 SEC(".maps");

काष्ठा outer_sockarr_sz1 अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY_OF_MAPS);
	__uपूर्णांक(max_entries, 1);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
	__array(values, काष्ठा sockarr_sz1);
पूर्ण outer_sockarr SEC(".maps") = अणु
	.values = अणु (व्योम *)&sockarr_sz1 पूर्ण,
पूर्ण;

पूर्णांक input = 0;

SEC("raw_tp/sys_enter")
पूर्णांक handle__sys_enter(व्योम *ctx)
अणु
	काष्ठा inner_map *inner_map;
	पूर्णांक key = 0, val;

	inner_map = bpf_map_lookup_elem(&outer_arr, &key);
	अगर (!inner_map)
		वापस 1;
	val = input;
	bpf_map_update_elem(inner_map, &key, &val, 0);

	inner_map = bpf_map_lookup_elem(&outer_hash, &key);
	अगर (!inner_map)
		वापस 1;
	val = input + 1;
	bpf_map_update_elem(inner_map, &key, &val, 0);

	inner_map = bpf_map_lookup_elem(&outer_arr_dyn, &key);
	अगर (!inner_map)
		वापस 1;
	val = input + 2;
	bpf_map_update_elem(inner_map, &key, &val, 0);

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
