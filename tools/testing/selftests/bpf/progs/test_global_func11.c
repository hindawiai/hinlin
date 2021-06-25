<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

काष्ठा S अणु
	पूर्णांक x;
पूर्ण;

__noअंतरभूत पूर्णांक foo(स्थिर काष्ठा S *s)
अणु
	वापस s ? bpf_get_pअक्रमom_u32() < s->x : 0;
पूर्ण

SEC("cgroup_skb/ingress")
पूर्णांक test_cls(काष्ठा __sk_buff *skb)
अणु
	वापस foo((स्थिर व्योम *)skb);
पूर्ण
