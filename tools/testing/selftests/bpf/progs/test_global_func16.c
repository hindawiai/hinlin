<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

__noअंतरभूत पूर्णांक foo(पूर्णांक (*arr)[10])
अणु
	अगर (arr)
		वापस (*arr)[9];

	वापस 0;
पूर्ण

SEC("cgroup_skb/ingress")
पूर्णांक test_cls(काष्ठा __sk_buff *skb)
अणु
	पूर्णांक array[10];

	स्थिर पूर्णांक rv = foo(&array);

	वापस rv ? 1 : 0;
पूर्ण
