<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */

#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

काष्ठा my_key अणु दीर्घ x; पूर्ण;
काष्ठा my_value अणु दीर्घ x; पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, काष्ठा my_key);
	__type(value, काष्ठा my_value);
	__uपूर्णांक(max_entries, 16);
पूर्ण map1 SEC(".maps");

 /* Matches map2 definition in linked_maps2.c. Order of the attributes करोesn't
  * matter.
  */
प्रकार काष्ठा अणु
	__uपूर्णांक(max_entries, 8);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
पूर्ण map2_t;

बाह्य map2_t map2 SEC(".maps");

/* This should be the winning map definition, but we have no way of verअगरying,
 * so we just make sure that it links and works without errors
 */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
	__uपूर्णांक(max_entries, 16);
पूर्ण map_weak __weak SEC(".maps");

पूर्णांक output_first1;
पूर्णांक output_second1;
पूर्णांक output_weak1;

SEC("raw_tp/sys_enter")
पूर्णांक BPF_PROG(handler_enter1)
अणु
	/* update values with key = 1 */
	पूर्णांक key = 1, val = 1;
	काष्ठा my_key key_काष्ठा = अणु .x = 1 पूर्ण;
	काष्ठा my_value val_काष्ठा = अणु .x = 1000 पूर्ण;

	bpf_map_update_elem(&map1, &key_काष्ठा, &val_काष्ठा, 0);
	bpf_map_update_elem(&map2, &key, &val, 0);
	bpf_map_update_elem(&map_weak, &key, &val, 0);

	वापस 0;
पूर्ण

SEC("raw_tp/sys_exit")
पूर्णांक BPF_PROG(handler_निकास1)
अणु
	/* lookup values with key = 2, set in another file */
	पूर्णांक key = 2, *val;
	काष्ठा my_key key_काष्ठा = अणु .x = 2 पूर्ण;
	काष्ठा my_value *value_काष्ठा;

	value_काष्ठा = bpf_map_lookup_elem(&map1, &key_काष्ठा);
	अगर (value_काष्ठा)
		output_first1 = value_काष्ठा->x;

	val = bpf_map_lookup_elem(&map2, &key);
	अगर (val)
		output_second1 = *val;

	val = bpf_map_lookup_elem(&map_weak, &key);
	अगर (val)
		output_weak1 = *val;
	
	वापस 0;
पूर्ण

अक्षर LICENSE[] SEC("license") = "GPL";
