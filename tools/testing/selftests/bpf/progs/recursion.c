<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */

#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 1);
	__type(key, पूर्णांक);
	__type(value, दीर्घ);
पूर्ण hash1 SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 1);
	__type(key, पूर्णांक);
	__type(value, दीर्घ);
पूर्ण hash2 SEC(".maps");

पूर्णांक pass1 = 0;
पूर्णांक pass2 = 0;

SEC("fentry/__htab_map_lookup_elem")
पूर्णांक BPF_PROG(on_lookup, काष्ठा bpf_map *map)
अणु
	पूर्णांक key = 0;

	अगर (map == (व्योम *)&hash1) अणु
		pass1++;
		वापस 0;
	पूर्ण
	अगर (map == (व्योम *)&hash2) अणु
		pass2++;
		/* htab_map_gen_lookup() will अंतरभूत below call
		 * पूर्णांकo direct call to __htab_map_lookup_elem()
		 */
		bpf_map_lookup_elem(&hash2, &key);
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण
