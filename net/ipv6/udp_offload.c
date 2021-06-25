<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	IPV6 GSO/GRO offload support
 *	Linux INET6 implementation
 *
 *      UDPv6 GSO support
 */
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/indirect_call_wrapper.h>
#समावेश <net/protocol.h>
#समावेश <net/ipv6.h>
#समावेश <net/udp.h>
#समावेश <net/ip6_checksum.h>
#समावेश "ip6_offload.h"

अटल काष्ठा sk_buff *udp6_ufo_fragment(काष्ठा sk_buff *skb,
					 netdev_features_t features)
अणु
	काष्ठा sk_buff *segs = ERR_PTR(-EINVAL);
	अचिन्हित पूर्णांक mss;
	अचिन्हित पूर्णांक unfrag_ip6hlen, unfrag_len;
	काष्ठा frag_hdr *fptr;
	u8 *packet_start, *prevhdr;
	u8 nexthdr;
	u8 frag_hdr_sz = माप(काष्ठा frag_hdr);
	__wsum csum;
	पूर्णांक tnl_hlen;
	पूर्णांक err;

	अगर (skb->encapsulation && skb_shinfo(skb)->gso_type &
	    (SKB_GSO_UDP_TUNNEL|SKB_GSO_UDP_TUNNEL_CSUM))
		segs = skb_udp_tunnel_segment(skb, features, true);
	अन्यथा अणु
		स्थिर काष्ठा ipv6hdr *ipv6h;
		काष्ठा udphdr *uh;

		अगर (!(skb_shinfo(skb)->gso_type & (SKB_GSO_UDP | SKB_GSO_UDP_L4)))
			जाओ out;

		अगर (!pskb_may_pull(skb, माप(काष्ठा udphdr)))
			जाओ out;

		अगर (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4)
			वापस __udp_gso_segment(skb, features, true);

		mss = skb_shinfo(skb)->gso_size;
		अगर (unlikely(skb->len <= mss))
			जाओ out;

		/* Do software UFO. Complete and fill in the UDP checksum as HW cannot
		 * करो checksum of UDP packets sent as multiple IP fragments.
		 */

		uh = udp_hdr(skb);
		ipv6h = ipv6_hdr(skb);

		uh->check = 0;
		csum = skb_checksum(skb, 0, skb->len, 0);
		uh->check = udp_v6_check(skb->len, &ipv6h->saddr,
					  &ipv6h->daddr, csum);
		अगर (uh->check == 0)
			uh->check = CSUM_MANGLED_0;

		skb->ip_summed = CHECKSUM_UNNECESSARY;

		/* If there is no outer header we can fake a checksum offload
		 * due to the fact that we have alपढ़ोy करोne the checksum in
		 * software prior to segmenting the frame.
		 */
		अगर (!skb->encap_hdr_csum)
			features |= NETIF_F_HW_CSUM;

		/* Check अगर there is enough headroom to insert fragment header. */
		tnl_hlen = skb_tnl_header_len(skb);
		अगर (skb->mac_header < (tnl_hlen + frag_hdr_sz)) अणु
			अगर (gso_pskb_expand_head(skb, tnl_hlen + frag_hdr_sz))
				जाओ out;
		पूर्ण

		/* Find the unfragmentable header and shअगरt it left by frag_hdr_sz
		 * bytes to insert fragment header.
		 */
		err = ip6_find_1stfragopt(skb, &prevhdr);
		अगर (err < 0)
			वापस ERR_PTR(err);
		unfrag_ip6hlen = err;
		nexthdr = *prevhdr;
		*prevhdr = NEXTHDR_FRAGMENT;
		unfrag_len = (skb_network_header(skb) - skb_mac_header(skb)) +
			     unfrag_ip6hlen + tnl_hlen;
		packet_start = (u8 *) skb->head + SKB_GSO_CB(skb)->mac_offset;
		स_हटाओ(packet_start-frag_hdr_sz, packet_start, unfrag_len);

		SKB_GSO_CB(skb)->mac_offset -= frag_hdr_sz;
		skb->mac_header -= frag_hdr_sz;
		skb->network_header -= frag_hdr_sz;

		fptr = (काष्ठा frag_hdr *)(skb_network_header(skb) + unfrag_ip6hlen);
		fptr->nexthdr = nexthdr;
		fptr->reserved = 0;
		fptr->identअगरication = ipv6_proxy_select_ident(dev_net(skb->dev), skb);

		/* Fragment the skb. ipv6 header and the reमुख्यing fields of the
		 * fragment header are updated in ipv6_gso_segment()
		 */
		segs = skb_segment(skb, features);
	पूर्ण

out:
	वापस segs;
पूर्ण

अटल काष्ठा sock *udp6_gro_lookup_skb(काष्ठा sk_buff *skb, __be16 sport,
					__be16 dport)
अणु
	स्थिर काष्ठा ipv6hdr *iph = skb_gro_network_header(skb);

	वापस __udp6_lib_lookup(dev_net(skb->dev), &iph->saddr, sport,
				 &iph->daddr, dport, inet6_iअगर(skb),
				 inet6_sdअगर(skb), &udp_table, शून्य);
पूर्ण

INसूचीECT_CALLABLE_SCOPE
काष्ठा sk_buff *udp6_gro_receive(काष्ठा list_head *head, काष्ठा sk_buff *skb)
अणु
	काष्ठा udphdr *uh = udp_gro_udphdr(skb);
	काष्ठा sock *sk = शून्य;
	काष्ठा sk_buff *pp;

	अगर (unlikely(!uh))
		जाओ flush;

	/* Don't bother verifying checksum if we're going to flush anyway. */
	अगर (NAPI_GRO_CB(skb)->flush)
		जाओ skip;

	अगर (skb_gro_checksum_validate_zero_check(skb, IPPROTO_UDP, uh->check,
						 ip6_gro_compute_pseuकरो))
		जाओ flush;
	अन्यथा अगर (uh->check)
		skb_gro_checksum_try_convert(skb, IPPROTO_UDP,
					     ip6_gro_compute_pseuकरो);

skip:
	NAPI_GRO_CB(skb)->is_ipv6 = 1;
	rcu_पढ़ो_lock();

	अगर (अटल_branch_unlikely(&udpv6_encap_needed_key))
		sk = udp6_gro_lookup_skb(skb, uh->source, uh->dest);

	pp = udp_gro_receive(head, skb, uh, sk);
	rcu_पढ़ो_unlock();
	वापस pp;

flush:
	NAPI_GRO_CB(skb)->flush = 1;
	वापस शून्य;
पूर्ण

INसूचीECT_CALLABLE_SCOPE पूर्णांक udp6_gro_complete(काष्ठा sk_buff *skb, पूर्णांक nhoff)
अणु
	स्थिर काष्ठा ipv6hdr *ipv6h = ipv6_hdr(skb);
	काष्ठा udphdr *uh = (काष्ठा udphdr *)(skb->data + nhoff);

	/* करो fraglist only अगर there is no outer UDP encap (or we alपढ़ोy processed it) */
	अगर (NAPI_GRO_CB(skb)->is_flist && !NAPI_GRO_CB(skb)->encap_mark) अणु
		uh->len = htons(skb->len - nhoff);

		skb_shinfo(skb)->gso_type |= (SKB_GSO_FRAGLIST|SKB_GSO_UDP_L4);
		skb_shinfo(skb)->gso_segs = NAPI_GRO_CB(skb)->count;

		अगर (skb->ip_summed == CHECKSUM_UNNECESSARY) अणु
			अगर (skb->csum_level < SKB_MAX_CSUM_LEVEL)
				skb->csum_level++;
		पूर्ण अन्यथा अणु
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			skb->csum_level = 0;
		पूर्ण

		वापस 0;
	पूर्ण

	अगर (uh->check)
		uh->check = ~udp_v6_check(skb->len - nhoff, &ipv6h->saddr,
					  &ipv6h->daddr, 0);

	वापस udp_gro_complete(skb, nhoff, udp6_lib_lookup_skb);
पूर्ण

अटल स्थिर काष्ठा net_offload udpv6_offload = अणु
	.callbacks = अणु
		.gso_segment	=	udp6_ufo_fragment,
		.gro_receive	=	udp6_gro_receive,
		.gro_complete	=	udp6_gro_complete,
	पूर्ण,
पूर्ण;

पूर्णांक udpv6_offload_init(व्योम)
अणु
	वापस inet6_add_offload(&udpv6_offload, IPPROTO_UDP);
पूर्ण

पूर्णांक udpv6_offload_निकास(व्योम)
अणु
	वापस inet6_del_offload(&udpv6_offload, IPPROTO_UDP);
पूर्ण
