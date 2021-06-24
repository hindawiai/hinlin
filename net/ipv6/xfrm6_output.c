<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * xfrm6_output.c - Common IPsec encapsulation code क्रम IPv6.
 * Copyright (C) 2002 USAGI/WIDE Project
 * Copyright (c) 2004 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <linux/अगर_ether.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <net/dst.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/xfrm.h>

पूर्णांक xfrm6_find_1stfragopt(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb,
			  u8 **prevhdr)
अणु
	वापस ip6_find_1stfragopt(skb, prevhdr);
पूर्ण
EXPORT_SYMBOL(xfrm6_find_1stfragopt);

व्योम xfrm6_local_rxpmtu(काष्ठा sk_buff *skb, u32 mtu)
अणु
	काष्ठा flowi6 fl6;
	काष्ठा sock *sk = skb->sk;

	fl6.flowi6_oअगर = sk->sk_bound_dev_अगर;
	fl6.daddr = ipv6_hdr(skb)->daddr;

	ipv6_local_rxpmtu(sk, &fl6, mtu);
पूर्ण

व्योम xfrm6_local_error(काष्ठा sk_buff *skb, u32 mtu)
अणु
	काष्ठा flowi6 fl6;
	स्थिर काष्ठा ipv6hdr *hdr;
	काष्ठा sock *sk = skb->sk;

	hdr = skb->encapsulation ? inner_ipv6_hdr(skb) : ipv6_hdr(skb);
	fl6.fl6_dport = inet_sk(sk)->inet_dport;
	fl6.daddr = hdr->daddr;

	ipv6_local_error(sk, EMSGSIZE, &fl6, mtu);
पूर्ण

अटल पूर्णांक __xfrm6_output_finish(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस xfrm_output(sk, skb);
पूर्ण

अटल पूर्णांक __xfrm6_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा xfrm_state *x = dst->xfrm;
	पूर्णांक mtu;
	bool toobig;

#अगर_घोषित CONFIG_NETFILTER
	अगर (!x) अणु
		IP6CB(skb)->flags |= IP6SKB_REROUTED;
		वापस dst_output(net, sk, skb);
	पूर्ण
#पूर्ण_अगर

	अगर (x->props.mode != XFRM_MODE_TUNNEL)
		जाओ skip_frag;

	अगर (skb->protocol == htons(ETH_P_IPV6))
		mtu = ip6_skb_dst_mtu(skb);
	अन्यथा
		mtu = dst_mtu(skb_dst(skb));

	toobig = skb->len > mtu && !skb_is_gso(skb);

	अगर (toobig && xfrm6_local_करोntfrag(skb->sk)) अणु
		xfrm6_local_rxpmtu(skb, mtu);
		kमुक्त_skb(skb);
		वापस -EMSGSIZE;
	पूर्ण अन्यथा अगर (!skb->ignore_df && toobig && skb->sk) अणु
		xfrm_local_error(skb, mtu);
		kमुक्त_skb(skb);
		वापस -EMSGSIZE;
	पूर्ण

	अगर (toobig || dst_allfrag(skb_dst(skb)))
		वापस ip6_fragment(net, sk, skb,
				    __xfrm6_output_finish);

skip_frag:
	वापस xfrm_output(sk, skb);
पूर्ण

पूर्णांक xfrm6_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस NF_HOOK_COND(NFPROTO_IPV6, NF_INET_POST_ROUTING,
			    net, sk, skb,  skb->dev, skb_dst(skb)->dev,
			    __xfrm6_output,
			    !(IP6CB(skb)->flags & IP6SKB_REROUTED));
पूर्ण
