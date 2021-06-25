<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	IPV6 GSO/GRO offload support
 *	Linux INET6 implementation
 *
 *      TCPv6 GSO/GRO support
 */
#समावेश <linux/indirect_call_wrapper.h>
#समावेश <linux/skbuff.h>
#समावेश <net/protocol.h>
#समावेश <net/tcp.h>
#समावेश <net/ip6_checksum.h>
#समावेश "ip6_offload.h"

INसूचीECT_CALLABLE_SCOPE
काष्ठा sk_buff *tcp6_gro_receive(काष्ठा list_head *head, काष्ठा sk_buff *skb)
अणु
	/* Don't bother verifying checksum if we're going to flush anyway. */
	अगर (!NAPI_GRO_CB(skb)->flush &&
	    skb_gro_checksum_validate(skb, IPPROTO_TCP,
				      ip6_gro_compute_pseuकरो)) अणु
		NAPI_GRO_CB(skb)->flush = 1;
		वापस शून्य;
	पूर्ण

	वापस tcp_gro_receive(head, skb);
पूर्ण

INसूचीECT_CALLABLE_SCOPE पूर्णांक tcp6_gro_complete(काष्ठा sk_buff *skb, पूर्णांक thoff)
अणु
	स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	काष्ठा tcphdr *th = tcp_hdr(skb);

	th->check = ~tcp_v6_check(skb->len - thoff, &iph->saddr,
				  &iph->daddr, 0);
	skb_shinfo(skb)->gso_type |= SKB_GSO_TCPV6;

	वापस tcp_gro_complete(skb);
पूर्ण

अटल काष्ठा sk_buff *tcp6_gso_segment(काष्ठा sk_buff *skb,
					netdev_features_t features)
अणु
	काष्ठा tcphdr *th;

	अगर (!(skb_shinfo(skb)->gso_type & SKB_GSO_TCPV6))
		वापस ERR_PTR(-EINVAL);

	अगर (!pskb_may_pull(skb, माप(*th)))
		वापस ERR_PTR(-EINVAL);

	अगर (unlikely(skb->ip_summed != CHECKSUM_PARTIAL)) अणु
		स्थिर काष्ठा ipv6hdr *ipv6h = ipv6_hdr(skb);
		काष्ठा tcphdr *th = tcp_hdr(skb);

		/* Set up pseuकरो header, usually expect stack to have करोne
		 * this.
		 */

		th->check = 0;
		skb->ip_summed = CHECKSUM_PARTIAL;
		__tcp_v6_send_check(skb, &ipv6h->saddr, &ipv6h->daddr);
	पूर्ण

	वापस tcp_gso_segment(skb, features);
पूर्ण
अटल स्थिर काष्ठा net_offload tcpv6_offload = अणु
	.callbacks = अणु
		.gso_segment	=	tcp6_gso_segment,
		.gro_receive	=	tcp6_gro_receive,
		.gro_complete	=	tcp6_gro_complete,
	पूर्ण,
पूर्ण;

पूर्णांक __init tcpv6_offload_init(व्योम)
अणु
	वापस inet6_add_offload(&tcpv6_offload, IPPROTO_TCP);
पूर्ण
