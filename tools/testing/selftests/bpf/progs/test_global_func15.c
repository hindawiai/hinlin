<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

__noअंतरभूत पूर्णांक foo(अचिन्हित पूर्णांक *v)
अणु
	अगर (v)
		*v = bpf_get_pअक्रमom_u32();

	वापस 0;
पूर्ण

SEC("cgroup_skb/ingress")
पूर्णांक test_cls(काष्ठा __sk_buff *skb)
अणु
	अचिन्हित पूर्णांक v = 1;

	foo(&v);

	वापस v;
पूर्ण
