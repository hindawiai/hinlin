<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018 Facebook */
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश "bpf_legacy.h"

पूर्णांक _version SEC("version") = 1;

काष्ठा ipv_counts अणु
	अचिन्हित पूर्णांक v4;
	अचिन्हित पूर्णांक v6;
पूर्ण;

काष्ठा bpf_map_def SEC("maps") btf_map = अणु
	.type = BPF_MAP_TYPE_ARRAY,
	.key_size = माप(पूर्णांक),
	.value_size = माप(काष्ठा ipv_counts),
	.max_entries = 4,
पूर्ण;

BPF_ANNOTATE_KV_PAIR(btf_map, पूर्णांक, काष्ठा ipv_counts);

__attribute__((noअंतरभूत))
पूर्णांक test_दीर्घ_fname_2(व्योम)
अणु
	काष्ठा ipv_counts *counts;
	पूर्णांक key = 0;

	counts = bpf_map_lookup_elem(&btf_map, &key);
	अगर (!counts)
		वापस 0;

	counts->v6++;

	वापस 0;
पूर्ण

__attribute__((noअंतरभूत))
पूर्णांक test_दीर्घ_fname_1(व्योम)
अणु
	वापस test_दीर्घ_fname_2();
पूर्ण

SEC("dummy_tracepoint")
पूर्णांक _dummy_tracepoपूर्णांक(व्योम *arg)
अणु
	वापस test_दीर्घ_fname_1();
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
