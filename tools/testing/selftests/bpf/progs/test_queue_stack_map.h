<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (c) 2018 Politecnico di Torino
#समावेश <मानकघोष.स>
#समावेश <माला.स>
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/ip.h>
#समावेश <linux/pkt_cls.h>
#समावेश <bpf/bpf_helpers.h>

पूर्णांक _version SEC("version") = 1;

काष्ठा अणु
	__uपूर्णांक(type, MAP_TYPE);
	__uपूर्णांक(max_entries, 32);
	__uपूर्णांक(map_flags, 0);
	__uपूर्णांक(key_size, 0);
	__uपूर्णांक(value_size, माप(__u32));
पूर्ण map_in SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, MAP_TYPE);
	__uपूर्णांक(max_entries, 32);
	__uपूर्णांक(map_flags, 0);
	__uपूर्णांक(key_size, 0);
	__uपूर्णांक(value_size, माप(__u32));
पूर्ण map_out SEC(".maps");

SEC("test")
पूर्णांक _test(काष्ठा __sk_buff *skb)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;
	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	काष्ठा ethhdr *eth = (काष्ठा ethhdr *)(data);
	__u32 value;
	पूर्णांक err;

	अगर (eth + 1 > data_end)
		वापस TC_ACT_SHOT;

	काष्ठा iphdr *iph = (काष्ठा iphdr *)(eth + 1);

	अगर (iph + 1 > data_end)
		वापस TC_ACT_SHOT;

	err = bpf_map_pop_elem(&map_in, &value);
	अगर (err)
		वापस TC_ACT_SHOT;

	iph->daddr = value;

	err = bpf_map_push_elem(&map_out, &iph->saddr, 0);
	अगर (err)
		वापस TC_ACT_SHOT;

	वापस TC_ACT_OK;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
