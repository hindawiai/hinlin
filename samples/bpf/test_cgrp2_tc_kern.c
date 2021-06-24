<शैली गुरु>
/* Copyright (c) 2016 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#घोषणा KBUILD_MODNAME "foo"
#समावेश <uapi/linux/अगर_ether.h>
#समावेश <uapi/linux/in6.h>
#समावेश <uapi/linux/ipv6.h>
#समावेश <uapi/linux/pkt_cls.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

/* copy of 'struct ethhdr' without __packed */
काष्ठा eth_hdr अणु
	अचिन्हित अक्षर   h_dest[ETH_ALEN];
	अचिन्हित अक्षर   h_source[ETH_ALEN];
	अचिन्हित लघु  h_proto;
पूर्ण;

#घोषणा PIN_GLOBAL_NS		2
काष्ठा bpf_elf_map अणु
	__u32 type;
	__u32 size_key;
	__u32 size_value;
	__u32 max_elem;
	__u32 flags;
	__u32 id;
	__u32 pinning;
पूर्ण;

काष्ठा bpf_elf_map SEC("maps") test_cgrp2_array_pin = अणु
	.type		= BPF_MAP_TYPE_CGROUP_ARRAY,
	.size_key	= माप(uपूर्णांक32_t),
	.size_value	= माप(uपूर्णांक32_t),
	.pinning	= PIN_GLOBAL_NS,
	.max_elem	= 1,
पूर्ण;

SEC("filter")
पूर्णांक handle_egress(काष्ठा __sk_buff *skb)
अणु
	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	काष्ठा eth_hdr *eth = data;
	काष्ठा ipv6hdr *ip6h = data + माप(*eth);
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;
	अक्षर करोnt_care_msg[] = "dont care %04x %d\n";
	अक्षर pass_msg[] = "pass\n";
	अक्षर reject_msg[] = "reject\n";

	/* single length check */
	अगर (data + माप(*eth) + माप(*ip6h) > data_end)
		वापस TC_ACT_OK;

	अगर (eth->h_proto != htons(ETH_P_IPV6) ||
	    ip6h->nexthdr != IPPROTO_ICMPV6) अणु
		bpf_trace_prपूर्णांकk(करोnt_care_msg, माप(करोnt_care_msg),
				 eth->h_proto, ip6h->nexthdr);
		वापस TC_ACT_OK;
	पूर्ण अन्यथा अगर (bpf_skb_under_cgroup(skb, &test_cgrp2_array_pin, 0) != 1) अणु
		bpf_trace_prपूर्णांकk(pass_msg, माप(pass_msg));
		वापस TC_ACT_OK;
	पूर्ण अन्यथा अणु
		bpf_trace_prपूर्णांकk(reject_msg, माप(reject_msg));
		वापस TC_ACT_SHOT;
	पूर्ण
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
