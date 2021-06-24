<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook

#समावेश <linux/मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <linux/pkt_cls.h>
#समावेश <bpf/bpf_endian.h>
#समावेश <bpf/bpf_helpers.h>

काष्ठा bpf_map_def SEC("maps") sock_map = अणु
	.type = BPF_MAP_TYPE_SOCKMAP,
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.max_entries = 2,
पूर्ण;

SEC("freplace/cls_redirect")
पूर्णांक freplace_cls_redirect_test(काष्ठा __sk_buff *skb)
अणु
	पूर्णांक ret = 0;
	स्थिर पूर्णांक zero = 0;
	काष्ठा bpf_sock *sk;

	sk = bpf_map_lookup_elem(&sock_map, &zero);
	अगर (!sk)
		वापस TC_ACT_SHOT;

	ret = bpf_map_update_elem(&sock_map, &zero, sk, 0);
	bpf_sk_release(sk);

	वापस ret == 0 ? TC_ACT_OK : TC_ACT_SHOT;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
