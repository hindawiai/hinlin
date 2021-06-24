<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2020 Facebook */
#समावेश <मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

__noअंतरभूत पूर्णांक foo(काष्ठा __sk_buff *skb)
अणु
	वापस bpf_get_pअक्रमom_u32();
पूर्ण

SEC("cgroup_skb/ingress")
पूर्णांक test_cls(काष्ठा __sk_buff *skb)
अणु
	अगर (!foo(skb))
		वापस 0;

	वापस 1;
पूर्ण
