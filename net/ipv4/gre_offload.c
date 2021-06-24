<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	IPV4 GSO/GRO offload support
 *	Linux INET implementation
 *
 *	GRE GSO support
 */

#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <net/protocol.h>
#समावेश <net/gre.h>

अटल काष्ठा sk_buff *gre_gso_segment(काष्ठा sk_buff *skb,
				       netdev_features_t features)
अणु
	पूर्णांक tnl_hlen = skb_inner_mac_header(skb) - skb_transport_header(skb);
	bool need_csum, offload_csum, gso_partial, need_ipsec;
	काष्ठा sk_buff *segs = ERR_PTR(-EINVAL);
	u16 mac_offset = skb->mac_header;
	__be16 protocol = skb->protocol;
	u16 mac_len = skb->mac_len;
	पूर्णांक gre_offset, outer_hlen;

	अगर (!skb->encapsulation)
		जाओ out;

	अगर (unlikely(tnl_hlen < माप(काष्ठा gre_base_hdr)))
		जाओ out;

	अगर (unlikely(!pskb_may_pull(skb, tnl_hlen)))
		जाओ out;

	/* setup inner skb. */
	skb->encapsulation = 0;
	SKB_GSO_CB(skb)->encap_level = 0;
	__skb_pull(skb, tnl_hlen);
	skb_reset_mac_header(skb);
	skb_set_network_header(skb, skb_inner_network_offset(skb));
	skb->mac_len = skb_inner_network_offset(skb);
	skb->protocol = skb->inner_protocol;

	need_csum = !!(skb_shinfo(skb)->gso_type & SKB_GSO_GRE_CSUM);
	skb->encap_hdr_csum = need_csum;

	features &= skb->dev->hw_enc_features;
	अगर (need_csum)
		features &= ~NETIF_F_SCTP_CRC;

	need_ipsec = skb_dst(skb) && dst_xfrm(skb_dst(skb));
	/* Try to offload checksum अगर possible */
	offload_csum = !!(need_csum && !need_ipsec &&
			  (skb->dev->features & NETIF_F_HW_CSUM));

	/* segment inner packet. */
	segs = skb_mac_gso_segment(skb, features);
	अगर (IS_ERR_OR_शून्य(segs)) अणु
		skb_gso_error_unwind(skb, protocol, tnl_hlen, mac_offset,
				     mac_len);
		जाओ out;
	पूर्ण

	gso_partial = !!(skb_shinfo(segs)->gso_type & SKB_GSO_PARTIAL);

	outer_hlen = skb_tnl_header_len(skb);
	gre_offset = outer_hlen - tnl_hlen;
	skb = segs;
	करो अणु
		काष्ठा gre_base_hdr *greh;
		__sum16 *pcsum;

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
		skb_set_transport_header(skb, gre_offset);

		अगर (!need_csum)
			जारी;

		greh = (काष्ठा gre_base_hdr *)skb_transport_header(skb);
		pcsum = (__sum16 *)(greh + 1);

		अगर (gso_partial && skb_is_gso(skb)) अणु
			अचिन्हित पूर्णांक partial_adj;

			/* Adjust checksum to account क्रम the fact that
			 * the partial checksum is based on actual size
			 * whereas headers should be based on MSS size.
			 */
			partial_adj = skb->len + skb_headroom(skb) -
				      SKB_GSO_CB(skb)->data_offset -
				      skb_shinfo(skb)->gso_size;
			*pcsum = ~csum_fold((__क्रमce __wsum)htonl(partial_adj));
		पूर्ण अन्यथा अणु
			*pcsum = 0;
		पूर्ण

		*(pcsum + 1) = 0;
		अगर (skb->encapsulation || !offload_csum) अणु
			*pcsum = gso_make_checksum(skb, 0);
		पूर्ण अन्यथा अणु
			skb->ip_summed = CHECKSUM_PARTIAL;
			skb->csum_start = skb_transport_header(skb) - skb->head;
			skb->csum_offset = माप(*greh);
		पूर्ण
	पूर्ण जबतक ((skb = skb->next));
out:
	वापस segs;
पूर्ण

अटल काष्ठा sk_buff *gre_gro_receive(काष्ठा list_head *head,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *pp = शून्य;
	काष्ठा sk_buff *p;
	स्थिर काष्ठा gre_base_hdr *greh;
	अचिन्हित पूर्णांक hlen, grehlen;
	अचिन्हित पूर्णांक off;
	पूर्णांक flush = 1;
	काष्ठा packet_offload *ptype;
	__be16 type;

	अगर (NAPI_GRO_CB(skb)->encap_mark)
		जाओ out;

	NAPI_GRO_CB(skb)->encap_mark = 1;

	off = skb_gro_offset(skb);
	hlen = off + माप(*greh);
	greh = skb_gro_header_fast(skb, off);
	अगर (skb_gro_header_hard(skb, hlen)) अणु
		greh = skb_gro_header_slow(skb, hlen, off);
		अगर (unlikely(!greh))
			जाओ out;
	पूर्ण

	/* Only support version 0 and K (key), C (csum) flags. Note that
	 * although the support क्रम the S (seq#) flag can be added easily
	 * क्रम GRO, this is problematic क्रम GSO hence can not be enabled
	 * here because a GRO pkt may end up in the क्रमwarding path, thus
	 * requiring GSO support to अवरोध it up correctly.
	 */
	अगर ((greh->flags & ~(GRE_KEY|GRE_CSUM)) != 0)
		जाओ out;

	/* We can only support GRE_CSUM अगर we can track the location of
	 * the GRE header.  In the हाल of FOU/GUE we cannot because the
	 * outer UDP header displaces the GRE header leaving us in a state
	 * of limbo.
	 */
	अगर ((greh->flags & GRE_CSUM) && NAPI_GRO_CB(skb)->is_fou)
		जाओ out;

	type = greh->protocol;

	rcu_पढ़ो_lock();
	ptype = gro_find_receive_by_type(type);
	अगर (!ptype)
		जाओ out_unlock;

	grehlen = GRE_HEADER_SECTION;

	अगर (greh->flags & GRE_KEY)
		grehlen += GRE_HEADER_SECTION;

	अगर (greh->flags & GRE_CSUM)
		grehlen += GRE_HEADER_SECTION;

	hlen = off + grehlen;
	अगर (skb_gro_header_hard(skb, hlen)) अणु
		greh = skb_gro_header_slow(skb, hlen, off);
		अगर (unlikely(!greh))
			जाओ out_unlock;
	पूर्ण

	/* Don't bother verifying checksum if we're going to flush anyway. */
	अगर ((greh->flags & GRE_CSUM) && !NAPI_GRO_CB(skb)->flush) अणु
		अगर (skb_gro_checksum_simple_validate(skb))
			जाओ out_unlock;

		skb_gro_checksum_try_convert(skb, IPPROTO_GRE,
					     null_compute_pseuकरो);
	पूर्ण

	list_क्रम_each_entry(p, head, list) अणु
		स्थिर काष्ठा gre_base_hdr *greh2;

		अगर (!NAPI_GRO_CB(p)->same_flow)
			जारी;

		/* The following checks are needed to ensure only pkts
		 * from the same tunnel are considered क्रम aggregation.
		 * The criteria क्रम "the same tunnel" includes:
		 * 1) same version (we only support version 0 here)
		 * 2) same protocol (we only support ETH_P_IP क्रम now)
		 * 3) same set of flags
		 * 4) same key अगर the key field is present.
		 */
		greh2 = (काष्ठा gre_base_hdr *)(p->data + off);

		अगर (greh2->flags != greh->flags ||
		    greh2->protocol != greh->protocol) अणु
			NAPI_GRO_CB(p)->same_flow = 0;
			जारी;
		पूर्ण
		अगर (greh->flags & GRE_KEY) अणु
			/* compare keys */
			अगर (*(__be32 *)(greh2+1) != *(__be32 *)(greh+1)) अणु
				NAPI_GRO_CB(p)->same_flow = 0;
				जारी;
			पूर्ण
		पूर्ण
	पूर्ण

	skb_gro_pull(skb, grehlen);

	/* Adjusted NAPI_GRO_CB(skb)->csum after skb_gro_pull()*/
	skb_gro_postpull_rcsum(skb, greh, grehlen);

	pp = call_gro_receive(ptype->callbacks.gro_receive, head, skb);
	flush = 0;

out_unlock:
	rcu_पढ़ो_unlock();
out:
	skb_gro_flush_final(skb, pp, flush);

	वापस pp;
पूर्ण

अटल पूर्णांक gre_gro_complete(काष्ठा sk_buff *skb, पूर्णांक nhoff)
अणु
	काष्ठा gre_base_hdr *greh = (काष्ठा gre_base_hdr *)(skb->data + nhoff);
	काष्ठा packet_offload *ptype;
	अचिन्हित पूर्णांक grehlen = माप(*greh);
	पूर्णांक err = -ENOENT;
	__be16 type;

	skb->encapsulation = 1;
	skb_shinfo(skb)->gso_type = SKB_GSO_GRE;

	type = greh->protocol;
	अगर (greh->flags & GRE_KEY)
		grehlen += GRE_HEADER_SECTION;

	अगर (greh->flags & GRE_CSUM)
		grehlen += GRE_HEADER_SECTION;

	rcu_पढ़ो_lock();
	ptype = gro_find_complete_by_type(type);
	अगर (ptype)
		err = ptype->callbacks.gro_complete(skb, nhoff + grehlen);

	rcu_पढ़ो_unlock();

	skb_set_inner_mac_header(skb, nhoff + grehlen);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा net_offload gre_offload = अणु
	.callbacks = अणु
		.gso_segment = gre_gso_segment,
		.gro_receive = gre_gro_receive,
		.gro_complete = gre_gro_complete,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init gre_offload_init(व्योम)
अणु
	पूर्णांक err;

	err = inet_add_offload(&gre_offload, IPPROTO_GRE);
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (err)
		वापस err;

	err = inet6_add_offload(&gre_offload, IPPROTO_GRE);
	अगर (err)
		inet_del_offload(&gre_offload, IPPROTO_GRE);
#पूर्ण_अगर

	वापस err;
पूर्ण
device_initcall(gre_offload_init);
