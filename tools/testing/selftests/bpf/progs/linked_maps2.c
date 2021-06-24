<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */

#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

/* modअगरiers and प्रकारs are ignored when comparing key/value types */
प्रकार काष्ठा my_key अणु दीर्घ x; पूर्ण key_type;
प्रकार काष्ठा my_value अणु दीर्घ x; पूर्ण value_type;

बाह्य काष्ठा अणु
	__uपूर्णांक(max_entries, 16);
	__type(key, key_type);
	__type(value, value_type);
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
पूर्ण map1 SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
	__uपूर्णांक(max_entries, 8);
पूर्ण map2 SEC(".maps");

/* this definition will lose, but it has to exactly match the winner */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
	__uपूर्णांक(max_entries, 16);
पूर्ण map_weak __weak SEC(".maps");

पूर्णांक output_first2;
पूर्णांक output_second2;
पूर्णांक output_weak2;

SEC("raw_tp/sys_enter")
पूर्णांक BPF_PROG(handler_enter2)
अणु
	/* update values with key = 2 */
	पूर्णांक key = 2, val = 2;
	key_type key_काष्ठा = अणु .x = 2 पूर्ण;
	value_type val_काष्ठा = अणु .x = 2000 पूर्ण;

	bpf_map_update_elem(&map1, &key_काष्ठा, &val_काष्ठा, 0);
	bpf_map_update_elem(&map2, &key, &val, 0);
	bpf_map_update_elem(&map_weak, &key, &val, 0);

	वापस 0;
पूर्ण

SEC("raw_tp/sys_exit")
पूर्णांक BPF_PROG(handler_निकास2)
अणु
	/* lookup values with key = 1, set in another file */
	पूर्णांक key = 1, *val;
	key_type key_काष्ठा = अणु .x = 1 पूर्ण;
	value_type *value_काष्ठा;

	value_काष्ठा = bpf_map_lookup_elem(&map1, &key_काष्ठा);
	अगर (value_काष्ठा)
		output_first2 = value_काष्ठा->x;

	val = bpf_map_lookup_elem(&map2, &key);
	अगर (val)
		output_second2 = *val;

	val = bpf_map_lookup_elem(&map_weak, &key);
	अगर (val)
		output_weak2 = *val;

	वापस 0;
पूर्ण

अक्षर LICENSE[] SEC("license") = "GPL";
