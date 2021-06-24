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
#समावेश <net/ip.h>
#समावेश <bpf/bpf_helpers.h>

#घोषणा DEFAULT_PKTGEN_UDP_PORT 9

/* copy of 'struct ethhdr' without __packed */
काष्ठा eth_hdr अणु
	अचिन्हित अक्षर   h_dest[ETH_ALEN];
	अचिन्हित अक्षर   h_source[ETH_ALEN];
	अचिन्हित लघु  h_proto;
पूर्ण;

SEC("simple")
पूर्णांक handle_ingress(काष्ठा __sk_buff *skb)
अणु
	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	काष्ठा eth_hdr *eth = data;
	काष्ठा iphdr *iph = data + माप(*eth);
	काष्ठा udphdr *udp = data + माप(*eth) + माप(*iph);
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;

	/* single length check */
	अगर (data + माप(*eth) + माप(*iph) + माप(*udp) > data_end)
		वापस 0;

	अगर (eth->h_proto != htons(ETH_P_IP))
		वापस 0;
	अगर (iph->protocol != IPPROTO_UDP || iph->ihl != 5)
		वापस 0;
	अगर (ip_is_fragment(iph))
		वापस 0;
	अगर (udp->dest == htons(DEFAULT_PKTGEN_UDP_PORT))
		वापस TC_ACT_SHOT;
	वापस 0;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
