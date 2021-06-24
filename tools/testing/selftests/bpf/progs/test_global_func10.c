<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

काष्ठा Small अणु
	पूर्णांक x;
पूर्ण;

काष्ठा Big अणु
	पूर्णांक x;
	पूर्णांक y;
पूर्ण;

__noअंतरभूत पूर्णांक foo(स्थिर काष्ठा Big *big)
अणु
	अगर (!big)
		वापस 0;

	वापस bpf_get_pअक्रमom_u32() < big->y;
पूर्ण

SEC("cgroup_skb/ingress")
पूर्णांक test_cls(काष्ठा __sk_buff *skb)
अणु
	स्थिर काष्ठा Small small = अणु.x = skb->len पूर्ण;

	वापस foo((काष्ठा Big *)&small) ? 1 : 0;
पूर्ण
