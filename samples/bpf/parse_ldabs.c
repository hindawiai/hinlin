<शैली गुरु>
/* Copyright (c) 2016 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#घोषणा KBUILD_MODNAME "foo"
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/in.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश "bpf_legacy.h"

#घोषणा DEFAULT_PKTGEN_UDP_PORT	9
#घोषणा IP_MF			0x2000
#घोषणा IP_OFFSET		0x1FFF

अटल अंतरभूत पूर्णांक ip_is_fragment(काष्ठा __sk_buff *ctx, __u64 nhoff)
अणु
	वापस load_half(ctx, nhoff + दुरत्व(काष्ठा iphdr, frag_off))
		& (IP_MF | IP_OFFSET);
पूर्ण

SEC("ldabs")
पूर्णांक handle_ingress(काष्ठा __sk_buff *skb)
अणु
	__u64 troff = ETH_HLEN + माप(काष्ठा iphdr);

	अगर (load_half(skb, दुरत्व(काष्ठा ethhdr, h_proto)) != ETH_P_IP)
		वापस 0;
	अगर (load_byte(skb, ETH_HLEN + दुरत्व(काष्ठा iphdr, protocol)) != IPPROTO_UDP ||
	    load_byte(skb, ETH_HLEN) != 0x45)
		वापस 0;
	अगर (ip_is_fragment(skb, ETH_HLEN))
		वापस 0;
	अगर (load_half(skb, troff + दुरत्व(काष्ठा udphdr, dest)) == DEFAULT_PKTGEN_UDP_PORT)
		वापस TC_ACT_SHOT;
	वापस 0;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
