<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * xfrm4_output.c - Common IPsec encapsulation code क्रम IPv4.
 * Copyright (c) 2004 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <linux/अगर_ether.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <net/dst.h>
#समावेश <net/ip.h>
#समावेश <net/xfrm.h>
#समावेश <net/icmp.h>

अटल पूर्णांक __xfrm4_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_NETFILTER
	काष्ठा xfrm_state *x = skb_dst(skb)->xfrm;

	अगर (!x) अणु
		IPCB(skb)->flags |= IPSKB_REROUTED;
		वापस dst_output(net, sk, skb);
	पूर्ण
#पूर्ण_अगर

	वापस xfrm_output(sk, skb);
पूर्ण

पूर्णांक xfrm4_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस NF_HOOK_COND(NFPROTO_IPV4, NF_INET_POST_ROUTING,
			    net, sk, skb, skb->dev, skb_dst(skb)->dev,
			    __xfrm4_output,
			    !(IPCB(skb)->flags & IPSKB_REROUTED));
पूर्ण

व्योम xfrm4_local_error(काष्ठा sk_buff *skb, u32 mtu)
अणु
	काष्ठा iphdr *hdr;

	hdr = skb->encapsulation ? inner_ip_hdr(skb) : ip_hdr(skb);
	ip_local_error(skb->sk, EMSGSIZE, hdr->daddr,
		       inet_sk(skb->sk)->inet_dport, mtu);
पूर्ण
