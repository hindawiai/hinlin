<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	IPV4 GSO/GRO offload support
 *	Linux INET implementation
 *
 *	UDPv4 GSO support
 */

#समावेश <linux/skbuff.h>
#समावेश <net/udp.h>
#समावेश <net/protocol.h>
#समावेश <net/inet_common.h>

अटल काष्ठा sk_buff *__skb_udp_tunnel_segment(काष्ठा sk_buff *skb,
	netdev_features_t features,
	काष्ठा sk_buff *(*gso_inner_segment)(काष्ठा sk_buff *skb,
					     netdev_features_t features),
	__be16 new_protocol, bool is_ipv6)
अणु
	पूर्णांक tnl_hlen = skb_inner_mac_header(skb) - skb_transport_header(skb);
	bool remcsum, need_csum, offload_csum, gso_partial;
	काष्ठा sk_buff *segs = ERR_PTR(-EINVAL);
	काष्ठा udphdr *uh = udp_hdr(skb);
	u16 mac_offset = skb->mac_header;
	__be16 protocol = skb->protocol;
	u16 mac_len = skb->mac_len;
	पूर्णांक udp_offset, outer_hlen;
	__wsum partial;
	bool need_ipsec;

	अगर (unlikely(!pskb_may_pull(skb, tnl_hlen)))
		जाओ out;

	/* Adjust partial header checksum to negate old length.
	 * We cannot rely on the value contained in uh->len as it is
	 * possible that the actual value exceeds the boundaries of the
	 * 16 bit length field due to the header being added outside of an
	 * IP or IPv6 frame that was alपढ़ोy limited to 64K - 1.
	 */
	अगर (skb_shinfo(skb)->gso_type & SKB_GSO_PARTIAL)
		partial = (__क्रमce __wsum)uh->len;
	अन्यथा
		partial = (__क्रमce __wsum)htonl(skb->len);
	partial = csum_sub(csum_unfold(uh->check), partial);

	/* setup inner skb. */
	skb->encapsulation = 0;
	SKB_GSO_CB(skb)->encap_level = 0;
	__skb_pull(skb, tnl_hlen);
	skb_reset_mac_header(skb);
	skb_set_network_header(skb, skb_inner_network_offset(skb));
	skb_set_transport_header(skb, skb_inner_transport_offset(skb));
	skb->mac_len = skb_inner_network_offset(skb);
	skb->protocol = new_protocol;

	need_csum = !!(skb_shinfo(skb)->gso_type & SKB_GSO_UDP_TUNNEL_CSUM);
	skb->encap_hdr_csum = need_csum;

	remcsum = !!(skb_shinfo(skb)->gso_type & SKB_GSO_TUNNEL_REMCSUM);
	skb->remcsum_offload = remcsum;

	need_ipsec = skb_dst(skb) && dst_xfrm(skb_dst(skb));
	/* Try to offload checksum अगर possible */
	offload_csum = !!(need_csum &&
			  !need_ipsec &&
			  (skb->dev->features &
			   (is_ipv6 ? (NETIF_F_HW_CSUM | NETIF_F_IPV6_CSUM) :
				      (NETIF_F_HW_CSUM | NETIF_F_IP_CSUM))));

	features &= skb->dev->hw_enc_features;
	अगर (need_csum)
		features &= ~NETIF_F_SCTP_CRC;

	/* The only checksum offload we care about from here on out is the
	 * outer one so strip the existing checksum feature flags and
	 * instead set the flag based on our outer checksum offload value.
	 */
	अगर (remcsum) अणु
		features &= ~NETIF_F_CSUM_MASK;
		अगर (!need_csum || offload_csum)
			features |= NETIF_F_HW_CSUM;
	पूर्ण

	/* segment inner packet. */
	segs = gso_inner_segment(skb, features);
	अगर (IS_ERR_OR_शून्य(segs)) अणु
		skb_gso_error_unwind(skb, protocol, tnl_hlen, mac_offset,
				     mac_len);
		जाओ out;
	पूर्ण

	gso_partial = !!(skb_shinfo(segs)->gso_type & SKB_GSO_PARTIAL);

	outer_hlen = skb_tnl_header_len(skb);
	udp_offset = outer_hlen - tnl_hlen;
	skb = segs;
	करो अणु
		अचिन्हित पूर्णांक len;

		अगर (remcsum)
			skb->ip_summed = CHECKSUM_NONE;

		/* Set up inner headers अगर we are offloading inner checksum */
		अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
			skb_reset_inner_headers(skb);
			skb->encapsulation = 1;
		पूर्ण

		skb->mac_len = mac_len;
		skb->protocol = protocol;

		__skb_push(skb, outer_hlen);
		skb_reset_mac_header(skb);
		skb_set_network_header(skb, mac_len);
		skb_set_transport_header(skb, udp_offset);
		len = skb->len - udp_offset;
		uh = udp_hdr(skb);

		/* If we are only perक्रमming partial GSO the inner header
		 * will be using a length value equal to only one MSS sized
		 * segment instead of the entire frame.
		 */
		अगर (gso_partial && skb_is_gso(skb)) अणु
			uh->len = htons(skb_shinfo(skb)->gso_size +
					SKB_GSO_CB(skb)->data_offset +
					skb->head - (अचिन्हित अक्षर *)uh);
		पूर्ण अन्यथा अणु
			uh->len = htons(len);
		पूर्ण

		अगर (!need_csum)
			जारी;

		uh->check = ~csum_fold(csum_add(partial,
				       (__क्रमce __wsum)htonl(len)));

		अगर (skb->encapsulation || !offload_csum) अणु
			uh->check = gso_make_checksum(skb, ~uh->check);
			अगर (uh->check == 0)
				uh->check = CSUM_MANGLED_0;
		पूर्ण अन्यथा अणु
			skb->ip_summed = CHECKSUM_PARTIAL;
			skb->csum_start = skb_transport_header(skb) - skb->head;
			skb->csum_offset = दुरत्व(काष्ठा udphdr, check);
		पूर्ण
	पूर्ण जबतक ((skb = skb->next));
out:
	वापस segs;
पूर्ण

काष्ठा sk_buff *skb_udp_tunnel_segment(काष्ठा sk_buff *skb,
				       netdev_features_t features,
				       bool is_ipv6)
अणु
	__be16 protocol = skb->protocol;
	स्थिर काष्ठा net_offload **offloads;
	स्थिर काष्ठा net_offload *ops;
	काष्ठा sk_buff *segs = ERR_PTR(-EINVAL);
	काष्ठा sk_buff *(*gso_inner_segment)(काष्ठा sk_buff *skb,
					     netdev_features_t features);

	rcu_पढ़ो_lock();

	चयन (skb->inner_protocol_type) अणु
	हाल ENCAP_TYPE_ETHER:
		protocol = skb->inner_protocol;
		gso_inner_segment = skb_mac_gso_segment;
		अवरोध;
	हाल ENCAP_TYPE_IPPROTO:
		offloads = is_ipv6 ? inet6_offloads : inet_offloads;
		ops = rcu_dereference(offloads[skb->inner_ipproto]);
		अगर (!ops || !ops->callbacks.gso_segment)
			जाओ out_unlock;
		gso_inner_segment = ops->callbacks.gso_segment;
		अवरोध;
	शेष:
		जाओ out_unlock;
	पूर्ण

	segs = __skb_udp_tunnel_segment(skb, features, gso_inner_segment,
					protocol, is_ipv6);

out_unlock:
	rcu_पढ़ो_unlock();

	वापस segs;
पूर्ण
EXPORT_SYMBOL(skb_udp_tunnel_segment);

अटल व्योम __udpv4_gso_segment_csum(काष्ठा sk_buff *seg,
				     __be32 *oldip, __be32 *newip,
				     __be16 *oldport, __be16 *newport)
अणु
	काष्ठा udphdr *uh;
	काष्ठा iphdr *iph;

	अगर (*oldip == *newip && *oldport == *newport)
		वापस;

	uh = udp_hdr(seg);
	iph = ip_hdr(seg);

	अगर (uh->check) अणु
		inet_proto_csum_replace4(&uh->check, seg, *oldip, *newip,
					 true);
		inet_proto_csum_replace2(&uh->check, seg, *oldport, *newport,
					 false);
		अगर (!uh->check)
			uh->check = CSUM_MANGLED_0;
	पूर्ण
	*oldport = *newport;

	csum_replace4(&iph->check, *oldip, *newip);
	*oldip = *newip;
पूर्ण

अटल काष्ठा sk_buff *__udpv4_gso_segment_list_csum(काष्ठा sk_buff *segs)
अणु
	काष्ठा sk_buff *seg;
	काष्ठा udphdr *uh, *uh2;
	काष्ठा iphdr *iph, *iph2;

	seg = segs;
	uh = udp_hdr(seg);
	iph = ip_hdr(seg);

	अगर ((udp_hdr(seg)->dest == udp_hdr(seg->next)->dest) &&
	    (udp_hdr(seg)->source == udp_hdr(seg->next)->source) &&
	    (ip_hdr(seg)->daddr == ip_hdr(seg->next)->daddr) &&
	    (ip_hdr(seg)->saddr == ip_hdr(seg->next)->saddr))
		वापस segs;

	जबतक ((seg = seg->next)) अणु
		uh2 = udp_hdr(seg);
		iph2 = ip_hdr(seg);

		__udpv4_gso_segment_csum(seg,
					 &iph2->saddr, &iph->saddr,
					 &uh2->source, &uh->source);
		__udpv4_gso_segment_csum(seg,
					 &iph2->daddr, &iph->daddr,
					 &uh2->dest, &uh->dest);
	पूर्ण

	वापस segs;
पूर्ण

अटल काष्ठा sk_buff *__udp_gso_segment_list(काष्ठा sk_buff *skb,
					      netdev_features_t features,
					      bool is_ipv6)
अणु
	अचिन्हित पूर्णांक mss = skb_shinfo(skb)->gso_size;

	skb = skb_segment_list(skb, features, skb_mac_header_len(skb));
	अगर (IS_ERR(skb))
		वापस skb;

	udp_hdr(skb)->len = htons(माप(काष्ठा udphdr) + mss);

	वापस is_ipv6 ? skb : __udpv4_gso_segment_list_csum(skb);
पूर्ण

काष्ठा sk_buff *__udp_gso_segment(काष्ठा sk_buff *gso_skb,
				  netdev_features_t features, bool is_ipv6)
अणु
	काष्ठा sock *sk = gso_skb->sk;
	अचिन्हित पूर्णांक sum_truesize = 0;
	काष्ठा sk_buff *segs, *seg;
	काष्ठा udphdr *uh;
	अचिन्हित पूर्णांक mss;
	bool copy_dtor;
	__sum16 check;
	__be16 newlen;

	अगर (skb_shinfo(gso_skb)->gso_type & SKB_GSO_FRAGLIST)
		वापस __udp_gso_segment_list(gso_skb, features, is_ipv6);

	mss = skb_shinfo(gso_skb)->gso_size;
	अगर (gso_skb->len <= माप(*uh) + mss)
		वापस ERR_PTR(-EINVAL);

	skb_pull(gso_skb, माप(*uh));

	/* clear deकाष्ठाor to aव्योम skb_segment assigning it to tail */
	copy_dtor = gso_skb->deकाष्ठाor == sock_wमुक्त;
	अगर (copy_dtor)
		gso_skb->deकाष्ठाor = शून्य;

	segs = skb_segment(gso_skb, features);
	अगर (IS_ERR_OR_शून्य(segs)) अणु
		अगर (copy_dtor)
			gso_skb->deकाष्ठाor = sock_wमुक्त;
		वापस segs;
	पूर्ण

	/* GSO partial and frag_list segmentation only requires splitting
	 * the frame पूर्णांकo an MSS multiple and possibly a reमुख्यder, both
	 * हालs वापस a GSO skb. So update the mss now.
	 */
	अगर (skb_is_gso(segs))
		mss *= skb_shinfo(segs)->gso_segs;

	seg = segs;
	uh = udp_hdr(seg);

	/* preserve TX बारtamp flags and TS key क्रम first segment */
	skb_shinfo(seg)->tskey = skb_shinfo(gso_skb)->tskey;
	skb_shinfo(seg)->tx_flags |=
			(skb_shinfo(gso_skb)->tx_flags & SKBTX_ANY_TSTAMP);

	/* compute checksum adjusपंचांगent based on old length versus new */
	newlen = htons(माप(*uh) + mss);
	check = csum16_add(csum16_sub(uh->check, uh->len), newlen);

	क्रम (;;) अणु
		अगर (copy_dtor) अणु
			seg->deकाष्ठाor = sock_wमुक्त;
			seg->sk = sk;
			sum_truesize += seg->truesize;
		पूर्ण

		अगर (!seg->next)
			अवरोध;

		uh->len = newlen;
		uh->check = check;

		अगर (seg->ip_summed == CHECKSUM_PARTIAL)
			gso_reset_checksum(seg, ~check);
		अन्यथा
			uh->check = gso_make_checksum(seg, ~check) ? :
				    CSUM_MANGLED_0;

		seg = seg->next;
		uh = udp_hdr(seg);
	पूर्ण

	/* last packet can be partial gso_size, account क्रम that in checksum */
	newlen = htons(skb_tail_poपूर्णांकer(seg) - skb_transport_header(seg) +
		       seg->data_len);
	check = csum16_add(csum16_sub(uh->check, uh->len), newlen);

	uh->len = newlen;
	uh->check = check;

	अगर (seg->ip_summed == CHECKSUM_PARTIAL)
		gso_reset_checksum(seg, ~check);
	अन्यथा
		uh->check = gso_make_checksum(seg, ~check) ? : CSUM_MANGLED_0;

	/* update refcount क्रम the packet */
	अगर (copy_dtor) अणु
		पूर्णांक delta = sum_truesize - gso_skb->truesize;

		/* In some pathological हालs, delta can be negative.
		 * We need to either use refcount_add() or refcount_sub_and_test()
		 */
		अगर (likely(delta >= 0))
			refcount_add(delta, &sk->sk_wmem_alloc);
		अन्यथा
			WARN_ON_ONCE(refcount_sub_and_test(-delta, &sk->sk_wmem_alloc));
	पूर्ण
	वापस segs;
पूर्ण
EXPORT_SYMBOL_GPL(__udp_gso_segment);

अटल काष्ठा sk_buff *udp4_ufo_fragment(काष्ठा sk_buff *skb,
					 netdev_features_t features)
अणु
	काष्ठा sk_buff *segs = ERR_PTR(-EINVAL);
	अचिन्हित पूर्णांक mss;
	__wsum csum;
	काष्ठा udphdr *uh;
	काष्ठा iphdr *iph;

	अगर (skb->encapsulation &&
	    (skb_shinfo(skb)->gso_type &
	     (SKB_GSO_UDP_TUNNEL|SKB_GSO_UDP_TUNNEL_CSUM))) अणु
		segs = skb_udp_tunnel_segment(skb, features, false);
		जाओ out;
	पूर्ण

	अगर (!(skb_shinfo(skb)->gso_type & (SKB_GSO_UDP | SKB_GSO_UDP_L4)))
		जाओ out;

	अगर (!pskb_may_pull(skb, माप(काष्ठा udphdr)))
		जाओ out;

	अगर (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4)
		वापस __udp_gso_segment(skb, features, false);

	mss = skb_shinfo(skb)->gso_size;
	अगर (unlikely(skb->len <= mss))
		जाओ out;

	/* Do software UFO. Complete and fill in the UDP checksum as
	 * HW cannot करो checksum of UDP packets sent as multiple
	 * IP fragments.
	 */

	uh = udp_hdr(skb);
	iph = ip_hdr(skb);

	uh->check = 0;
	csum = skb_checksum(skb, 0, skb->len, 0);
	uh->check = udp_v4_check(skb->len, iph->saddr, iph->daddr, csum);
	अगर (uh->check == 0)
		uh->check = CSUM_MANGLED_0;

	skb->ip_summed = CHECKSUM_UNNECESSARY;

	/* If there is no outer header we can fake a checksum offload
	 * due to the fact that we have alपढ़ोy करोne the checksum in
	 * software prior to segmenting the frame.
	 */
	अगर (!skb->encap_hdr_csum)
		features |= NETIF_F_HW_CSUM;

	/* Fragment the skb. IP headers of the fragments are updated in
	 * inet_gso_segment()
	 */
	segs = skb_segment(skb, features);
out:
	वापस segs;
पूर्ण

#घोषणा UDP_GRO_CNT_MAX 64
अटल काष्ठा sk_buff *udp_gro_receive_segment(काष्ठा list_head *head,
					       काष्ठा sk_buff *skb)
अणु
	काष्ठा udphdr *uh = udp_gro_udphdr(skb);
	काष्ठा sk_buff *pp = शून्य;
	काष्ठा udphdr *uh2;
	काष्ठा sk_buff *p;
	अचिन्हित पूर्णांक ulen;
	पूर्णांक ret = 0;

	/* requires non zero csum, क्रम symmetry with GSO */
	अगर (!uh->check) अणु
		NAPI_GRO_CB(skb)->flush = 1;
		वापस शून्य;
	पूर्ण

	/* Do not deal with padded or malicious packets, sorry ! */
	ulen = ntohs(uh->len);
	अगर (ulen <= माप(*uh) || ulen != skb_gro_len(skb)) अणु
		NAPI_GRO_CB(skb)->flush = 1;
		वापस शून्य;
	पूर्ण
	/* pull encapsulating udp header */
	skb_gro_pull(skb, माप(काष्ठा udphdr));

	list_क्रम_each_entry(p, head, list) अणु
		अगर (!NAPI_GRO_CB(p)->same_flow)
			जारी;

		uh2 = udp_hdr(p);

		/* Match ports only, as csum is always non zero */
		अगर ((*(u32 *)&uh->source != *(u32 *)&uh2->source)) अणु
			NAPI_GRO_CB(p)->same_flow = 0;
			जारी;
		पूर्ण

		अगर (NAPI_GRO_CB(skb)->is_flist != NAPI_GRO_CB(p)->is_flist) अणु
			NAPI_GRO_CB(skb)->flush = 1;
			वापस p;
		पूर्ण

		/* Terminate the flow on len mismatch or अगर it grow "too much".
		 * Under small packet flood GRO count could अन्यथाwhere grow a lot
		 * leading to excessive truesize values.
		 * On len mismatch merge the first packet लघुer than gso_size,
		 * otherwise complete the GRO packet.
		 */
		अगर (ulen > ntohs(uh2->len)) अणु
			pp = p;
		पूर्ण अन्यथा अणु
			अगर (NAPI_GRO_CB(skb)->is_flist) अणु
				अगर (!pskb_may_pull(skb, skb_gro_offset(skb))) अणु
					NAPI_GRO_CB(skb)->flush = 1;
					वापस शून्य;
				पूर्ण
				अगर ((skb->ip_summed != p->ip_summed) ||
				    (skb->csum_level != p->csum_level)) अणु
					NAPI_GRO_CB(skb)->flush = 1;
					वापस शून्य;
				पूर्ण
				ret = skb_gro_receive_list(p, skb);
			पूर्ण अन्यथा अणु
				skb_gro_postpull_rcsum(skb, uh,
						       माप(काष्ठा udphdr));

				ret = skb_gro_receive(p, skb);
			पूर्ण
		पूर्ण

		अगर (ret || ulen != ntohs(uh2->len) ||
		    NAPI_GRO_CB(p)->count >= UDP_GRO_CNT_MAX)
			pp = p;

		वापस pp;
	पूर्ण

	/* mismatch, but we never need to flush */
	वापस शून्य;
पूर्ण

काष्ठा sk_buff *udp_gro_receive(काष्ठा list_head *head, काष्ठा sk_buff *skb,
				काष्ठा udphdr *uh, काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *pp = शून्य;
	काष्ठा sk_buff *p;
	काष्ठा udphdr *uh2;
	अचिन्हित पूर्णांक off = skb_gro_offset(skb);
	पूर्णांक flush = 1;

	/* we can करो L4 aggregation only अगर the packet can't land in a tunnel
	 * otherwise we could corrupt the inner stream
	 */
	NAPI_GRO_CB(skb)->is_flist = 0;
	अगर (!sk || !udp_sk(sk)->gro_receive) अणु
		अगर (skb->dev->features & NETIF_F_GRO_FRAGLIST)
			NAPI_GRO_CB(skb)->is_flist = sk ? !udp_sk(sk)->gro_enabled : 1;

		अगर ((!sk && (skb->dev->features & NETIF_F_GRO_UDP_FWD)) ||
		    (sk && udp_sk(sk)->gro_enabled) || NAPI_GRO_CB(skb)->is_flist)
			pp = call_gro_receive(udp_gro_receive_segment, head, skb);
		वापस pp;
	पूर्ण

	अगर (NAPI_GRO_CB(skb)->encap_mark ||
	    (uh->check && skb->ip_summed != CHECKSUM_PARTIAL &&
	     NAPI_GRO_CB(skb)->csum_cnt == 0 &&
	     !NAPI_GRO_CB(skb)->csum_valid))
		जाओ out;

	/* mark that this skb passed once through the tunnel gro layer */
	NAPI_GRO_CB(skb)->encap_mark = 1;

	flush = 0;

	list_क्रम_each_entry(p, head, list) अणु
		अगर (!NAPI_GRO_CB(p)->same_flow)
			जारी;

		uh2 = (काष्ठा udphdr   *)(p->data + off);

		/* Match ports and either checksums are either both zero
		 * or nonzero.
		 */
		अगर ((*(u32 *)&uh->source != *(u32 *)&uh2->source) ||
		    (!uh->check ^ !uh2->check)) अणु
			NAPI_GRO_CB(p)->same_flow = 0;
			जारी;
		पूर्ण
	पूर्ण

	skb_gro_pull(skb, माप(काष्ठा udphdr)); /* pull encapsulating udp header */
	skb_gro_postpull_rcsum(skb, uh, माप(काष्ठा udphdr));
	pp = call_gro_receive_sk(udp_sk(sk)->gro_receive, sk, head, skb);

out:
	skb_gro_flush_final(skb, pp, flush);
	वापस pp;
पूर्ण
EXPORT_SYMBOL(udp_gro_receive);

अटल काष्ठा sock *udp4_gro_lookup_skb(काष्ठा sk_buff *skb, __be16 sport,
					__be16 dport)
अणु
	स्थिर काष्ठा iphdr *iph = skb_gro_network_header(skb);

	वापस __udp4_lib_lookup(dev_net(skb->dev), iph->saddr, sport,
				 iph->daddr, dport, inet_iअगर(skb),
				 inet_sdअगर(skb), &udp_table, शून्य);
पूर्ण

INसूचीECT_CALLABLE_SCOPE
काष्ठा sk_buff *udp4_gro_receive(काष्ठा list_head *head, काष्ठा sk_buff *skb)
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
						 inet_gro_compute_pseuकरो))
		जाओ flush;
	अन्यथा अगर (uh->check)
		skb_gro_checksum_try_convert(skb, IPPROTO_UDP,
					     inet_gro_compute_pseuकरो);
skip:
	NAPI_GRO_CB(skb)->is_ipv6 = 0;
	rcu_पढ़ो_lock();

	अगर (अटल_branch_unlikely(&udp_encap_needed_key))
		sk = udp4_gro_lookup_skb(skb, uh->source, uh->dest);

	pp = udp_gro_receive(head, skb, uh, sk);
	rcu_पढ़ो_unlock();
	वापस pp;

flush:
	NAPI_GRO_CB(skb)->flush = 1;
	वापस शून्य;
पूर्ण

अटल पूर्णांक udp_gro_complete_segment(काष्ठा sk_buff *skb)
अणु
	काष्ठा udphdr *uh = udp_hdr(skb);

	skb->csum_start = (अचिन्हित अक्षर *)uh - skb->head;
	skb->csum_offset = दुरत्व(काष्ठा udphdr, check);
	skb->ip_summed = CHECKSUM_PARTIAL;

	skb_shinfo(skb)->gso_segs = NAPI_GRO_CB(skb)->count;
	skb_shinfo(skb)->gso_type |= SKB_GSO_UDP_L4;
	वापस 0;
पूर्ण

पूर्णांक udp_gro_complete(काष्ठा sk_buff *skb, पूर्णांक nhoff,
		     udp_lookup_t lookup)
अणु
	__be16 newlen = htons(skb->len - nhoff);
	काष्ठा udphdr *uh = (काष्ठा udphdr *)(skb->data + nhoff);
	काष्ठा sock *sk;
	पूर्णांक err;

	uh->len = newlen;

	rcu_पढ़ो_lock();
	sk = INसूचीECT_CALL_INET(lookup, udp6_lib_lookup_skb,
				udp4_lib_lookup_skb, skb, uh->source, uh->dest);
	अगर (sk && udp_sk(sk)->gro_complete) अणु
		skb_shinfo(skb)->gso_type = uh->check ? SKB_GSO_UDP_TUNNEL_CSUM
					: SKB_GSO_UDP_TUNNEL;

		/* clear the encap mark, so that inner frag_list gro_complete
		 * can take place
		 */
		NAPI_GRO_CB(skb)->encap_mark = 0;

		/* Set encapsulation beक्रमe calling पूर्णांकo inner gro_complete()
		 * functions to make them set up the inner offsets.
		 */
		skb->encapsulation = 1;
		err = udp_sk(sk)->gro_complete(sk, skb,
				nhoff + माप(काष्ठा udphdr));
	पूर्ण अन्यथा अणु
		err = udp_gro_complete_segment(skb);
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (skb->remcsum_offload)
		skb_shinfo(skb)->gso_type |= SKB_GSO_TUNNEL_REMCSUM;

	वापस err;
पूर्ण
EXPORT_SYMBOL(udp_gro_complete);

INसूचीECT_CALLABLE_SCOPE पूर्णांक udp4_gro_complete(काष्ठा sk_buff *skb, पूर्णांक nhoff)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
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
		uh->check = ~udp_v4_check(skb->len - nhoff, iph->saddr,
					  iph->daddr, 0);

	वापस udp_gro_complete(skb, nhoff, udp4_lib_lookup_skb);
पूर्ण

अटल स्थिर काष्ठा net_offload udpv4_offload = अणु
	.callbacks = अणु
		.gso_segment = udp4_ufo_fragment,
		.gro_receive  =	udp4_gro_receive,
		.gro_complete =	udp4_gro_complete,
	पूर्ण,
पूर्ण;

पूर्णांक __init udpv4_offload_init(व्योम)
अणु
	वापस inet_add_offload(&udpv4_offload, IPPROTO_UDP);
पूर्ण
