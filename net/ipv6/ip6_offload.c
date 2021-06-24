<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	IPV6 GSO/GRO offload support
 *	Linux INET6 implementation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/socket.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/prपूर्णांकk.h>

#समावेश <net/protocol.h>
#समावेश <net/ipv6.h>
#समावेश <net/inet_common.h>
#समावेश <net/tcp.h>
#समावेश <net/udp.h>
#समावेश <net/gro.h>

#समावेश "ip6_offload.h"

/* All GRO functions are always builtin, except UDP over ipv6, which lays in
 * ipv6 module, as it depends on UDPv6 lookup function, so we need special care
 * when ipv6 is built as a module
 */
#अगर IS_BUILTIN(CONFIG_IPV6)
#घोषणा INसूचीECT_CALL_L4(f, f2, f1, ...) INसूचीECT_CALL_2(f, f2, f1, __VA_ARGS__)
#अन्यथा
#घोषणा INसूचीECT_CALL_L4(f, f2, f1, ...) INसूचीECT_CALL_1(f, f2, __VA_ARGS__)
#पूर्ण_अगर

#घोषणा indirect_call_gro_receive_l4(f2, f1, cb, head, skb)	\
(अणु								\
	unlikely(gro_recursion_inc_test(skb)) ?			\
		NAPI_GRO_CB(skb)->flush |= 1, शून्य :		\
		INसूचीECT_CALL_L4(cb, f2, f1, head, skb);	\
पूर्ण)

अटल पूर्णांक ipv6_gso_pull_exthdrs(काष्ठा sk_buff *skb, पूर्णांक proto)
अणु
	स्थिर काष्ठा net_offload *ops = शून्य;

	क्रम (;;) अणु
		काष्ठा ipv6_opt_hdr *opth;
		पूर्णांक len;

		अगर (proto != NEXTHDR_HOP) अणु
			ops = rcu_dereference(inet6_offloads[proto]);

			अगर (unlikely(!ops))
				अवरोध;

			अगर (!(ops->flags & INET6_PROTO_GSO_EXTHDR))
				अवरोध;
		पूर्ण

		अगर (unlikely(!pskb_may_pull(skb, 8)))
			अवरोध;

		opth = (व्योम *)skb->data;
		len = ipv6_optlen(opth);

		अगर (unlikely(!pskb_may_pull(skb, len)))
			अवरोध;

		opth = (व्योम *)skb->data;
		proto = opth->nexthdr;
		__skb_pull(skb, len);
	पूर्ण

	वापस proto;
पूर्ण

अटल काष्ठा sk_buff *ipv6_gso_segment(काष्ठा sk_buff *skb,
	netdev_features_t features)
अणु
	काष्ठा sk_buff *segs = ERR_PTR(-EINVAL);
	काष्ठा ipv6hdr *ipv6h;
	स्थिर काष्ठा net_offload *ops;
	पूर्णांक proto;
	काष्ठा frag_hdr *fptr;
	अचिन्हित पूर्णांक payload_len;
	u8 *prevhdr;
	पूर्णांक offset = 0;
	bool encap, udpfrag;
	पूर्णांक nhoff;
	bool gso_partial;

	skb_reset_network_header(skb);
	nhoff = skb_network_header(skb) - skb_mac_header(skb);
	अगर (unlikely(!pskb_may_pull(skb, माप(*ipv6h))))
		जाओ out;

	encap = SKB_GSO_CB(skb)->encap_level > 0;
	अगर (encap)
		features &= skb->dev->hw_enc_features;
	SKB_GSO_CB(skb)->encap_level += माप(*ipv6h);

	ipv6h = ipv6_hdr(skb);
	__skb_pull(skb, माप(*ipv6h));
	segs = ERR_PTR(-EPROTONOSUPPORT);

	proto = ipv6_gso_pull_exthdrs(skb, ipv6h->nexthdr);

	अगर (skb->encapsulation &&
	    skb_shinfo(skb)->gso_type & (SKB_GSO_IPXIP4 | SKB_GSO_IPXIP6))
		udpfrag = proto == IPPROTO_UDP && encap &&
			  (skb_shinfo(skb)->gso_type & SKB_GSO_UDP);
	अन्यथा
		udpfrag = proto == IPPROTO_UDP && !skb->encapsulation &&
			  (skb_shinfo(skb)->gso_type & SKB_GSO_UDP);

	ops = rcu_dereference(inet6_offloads[proto]);
	अगर (likely(ops && ops->callbacks.gso_segment)) अणु
		skb_reset_transport_header(skb);
		segs = ops->callbacks.gso_segment(skb, features);
	पूर्ण

	अगर (IS_ERR_OR_शून्य(segs))
		जाओ out;

	gso_partial = !!(skb_shinfo(segs)->gso_type & SKB_GSO_PARTIAL);

	क्रम (skb = segs; skb; skb = skb->next) अणु
		ipv6h = (काष्ठा ipv6hdr *)(skb_mac_header(skb) + nhoff);
		अगर (gso_partial && skb_is_gso(skb))
			payload_len = skb_shinfo(skb)->gso_size +
				      SKB_GSO_CB(skb)->data_offset +
				      skb->head - (अचिन्हित अक्षर *)(ipv6h + 1);
		अन्यथा
			payload_len = skb->len - nhoff - माप(*ipv6h);
		ipv6h->payload_len = htons(payload_len);
		skb->network_header = (u8 *)ipv6h - skb->head;
		skb_reset_mac_len(skb);

		अगर (udpfrag) अणु
			पूर्णांक err = ip6_find_1stfragopt(skb, &prevhdr);
			अगर (err < 0) अणु
				kमुक्त_skb_list(segs);
				वापस ERR_PTR(err);
			पूर्ण
			fptr = (काष्ठा frag_hdr *)((u8 *)ipv6h + err);
			fptr->frag_off = htons(offset);
			अगर (skb->next)
				fptr->frag_off |= htons(IP6_MF);
			offset += (ntohs(ipv6h->payload_len) -
				   माप(काष्ठा frag_hdr));
		पूर्ण
		अगर (encap)
			skb_reset_inner_headers(skb);
	पूर्ण

out:
	वापस segs;
पूर्ण

/* Return the total length of all the extension hdrs, following the same
 * logic in ipv6_gso_pull_exthdrs() when parsing ext-hdrs.
 */
अटल पूर्णांक ipv6_exthdrs_len(काष्ठा ipv6hdr *iph,
			    स्थिर काष्ठा net_offload **opps)
अणु
	काष्ठा ipv6_opt_hdr *opth = (व्योम *)iph;
	पूर्णांक len = 0, proto, optlen = माप(*iph);

	proto = iph->nexthdr;
	क्रम (;;) अणु
		अगर (proto != NEXTHDR_HOP) अणु
			*opps = rcu_dereference(inet6_offloads[proto]);
			अगर (unlikely(!(*opps)))
				अवरोध;
			अगर (!((*opps)->flags & INET6_PROTO_GSO_EXTHDR))
				अवरोध;
		पूर्ण
		opth = (व्योम *)opth + optlen;
		optlen = ipv6_optlen(opth);
		len += optlen;
		proto = opth->nexthdr;
	पूर्ण
	वापस len;
पूर्ण

INसूचीECT_CALLABLE_SCOPE काष्ठा sk_buff *ipv6_gro_receive(काष्ठा list_head *head,
							 काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा net_offload *ops;
	काष्ठा sk_buff *pp = शून्य;
	काष्ठा sk_buff *p;
	काष्ठा ipv6hdr *iph;
	अचिन्हित पूर्णांक nlen;
	अचिन्हित पूर्णांक hlen;
	अचिन्हित पूर्णांक off;
	u16 flush = 1;
	पूर्णांक proto;

	off = skb_gro_offset(skb);
	hlen = off + माप(*iph);
	iph = skb_gro_header_fast(skb, off);
	अगर (skb_gro_header_hard(skb, hlen)) अणु
		iph = skb_gro_header_slow(skb, hlen, off);
		अगर (unlikely(!iph))
			जाओ out;
	पूर्ण

	skb_set_network_header(skb, off);
	skb_gro_pull(skb, माप(*iph));
	skb_set_transport_header(skb, skb_gro_offset(skb));

	flush += ntohs(iph->payload_len) != skb_gro_len(skb);

	rcu_पढ़ो_lock();
	proto = iph->nexthdr;
	ops = rcu_dereference(inet6_offloads[proto]);
	अगर (!ops || !ops->callbacks.gro_receive) अणु
		__pskb_pull(skb, skb_gro_offset(skb));
		skb_gro_frag0_invalidate(skb);
		proto = ipv6_gso_pull_exthdrs(skb, proto);
		skb_gro_pull(skb, -skb_transport_offset(skb));
		skb_reset_transport_header(skb);
		__skb_push(skb, skb_gro_offset(skb));

		ops = rcu_dereference(inet6_offloads[proto]);
		अगर (!ops || !ops->callbacks.gro_receive)
			जाओ out_unlock;

		iph = ipv6_hdr(skb);
	पूर्ण

	NAPI_GRO_CB(skb)->proto = proto;

	flush--;
	nlen = skb_network_header_len(skb);

	list_क्रम_each_entry(p, head, list) अणु
		स्थिर काष्ठा ipv6hdr *iph2;
		__be32 first_word; /* <Version:4><Traffic_Class:8><Flow_Label:20> */

		अगर (!NAPI_GRO_CB(p)->same_flow)
			जारी;

		iph2 = (काष्ठा ipv6hdr *)(p->data + off);
		first_word = *(__be32 *)iph ^ *(__be32 *)iph2;

		/* All fields must match except length and Traffic Class.
		 * XXX skbs on the gro_list have all been parsed and pulled
		 * alपढ़ोy so we करोn't need to compare nlen
		 * (nlen != (माप(*iph2) + ipv6_exthdrs_len(iph2, &ops)))
		 * स_भेद() alone below is sufficient, right?
		 */
		 अगर ((first_word & htonl(0xF00FFFFF)) ||
		    !ipv6_addr_equal(&iph->saddr, &iph2->saddr) ||
		    !ipv6_addr_equal(&iph->daddr, &iph2->daddr) ||
		    *(u16 *)&iph->nexthdr != *(u16 *)&iph2->nexthdr) अणु
not_same_flow:
			NAPI_GRO_CB(p)->same_flow = 0;
			जारी;
		पूर्ण
		अगर (unlikely(nlen > माप(काष्ठा ipv6hdr))) अणु
			अगर (स_भेद(iph + 1, iph2 + 1,
				   nlen - माप(काष्ठा ipv6hdr)))
				जाओ not_same_flow;
		पूर्ण
		/* flush अगर Traffic Class fields are dअगरferent */
		NAPI_GRO_CB(p)->flush |= !!(first_word & htonl(0x0FF00000));
		NAPI_GRO_CB(p)->flush |= flush;

		/* If the previous IP ID value was based on an atomic
		 * datagram we can overग_लिखो the value and ignore it.
		 */
		अगर (NAPI_GRO_CB(skb)->is_atomic)
			NAPI_GRO_CB(p)->flush_id = 0;
	पूर्ण

	NAPI_GRO_CB(skb)->is_atomic = true;
	NAPI_GRO_CB(skb)->flush |= flush;

	skb_gro_postpull_rcsum(skb, iph, nlen);

	pp = indirect_call_gro_receive_l4(tcp6_gro_receive, udp6_gro_receive,
					 ops->callbacks.gro_receive, head, skb);

out_unlock:
	rcu_पढ़ो_unlock();

out:
	skb_gro_flush_final(skb, pp, flush);

	वापस pp;
पूर्ण

अटल काष्ठा sk_buff *sit_ip6ip6_gro_receive(काष्ठा list_head *head,
					      काष्ठा sk_buff *skb)
अणु
	/* Common GRO receive क्रम SIT and IP6IP6 */

	अगर (NAPI_GRO_CB(skb)->encap_mark) अणु
		NAPI_GRO_CB(skb)->flush = 1;
		वापस शून्य;
	पूर्ण

	NAPI_GRO_CB(skb)->encap_mark = 1;

	वापस ipv6_gro_receive(head, skb);
पूर्ण

अटल काष्ठा sk_buff *ip4ip6_gro_receive(काष्ठा list_head *head,
					  काष्ठा sk_buff *skb)
अणु
	/* Common GRO receive क्रम SIT and IP6IP6 */

	अगर (NAPI_GRO_CB(skb)->encap_mark) अणु
		NAPI_GRO_CB(skb)->flush = 1;
		वापस शून्य;
	पूर्ण

	NAPI_GRO_CB(skb)->encap_mark = 1;

	वापस inet_gro_receive(head, skb);
पूर्ण

INसूचीECT_CALLABLE_SCOPE पूर्णांक ipv6_gro_complete(काष्ठा sk_buff *skb, पूर्णांक nhoff)
अणु
	स्थिर काष्ठा net_offload *ops;
	काष्ठा ipv6hdr *iph = (काष्ठा ipv6hdr *)(skb->data + nhoff);
	पूर्णांक err = -ENOSYS;

	अगर (skb->encapsulation) अणु
		skb_set_inner_protocol(skb, cpu_to_be16(ETH_P_IPV6));
		skb_set_inner_network_header(skb, nhoff);
	पूर्ण

	iph->payload_len = htons(skb->len - nhoff - माप(*iph));

	rcu_पढ़ो_lock();

	nhoff += माप(*iph) + ipv6_exthdrs_len(iph, &ops);
	अगर (WARN_ON(!ops || !ops->callbacks.gro_complete))
		जाओ out_unlock;

	err = INसूचीECT_CALL_L4(ops->callbacks.gro_complete, tcp6_gro_complete,
			       udp6_gro_complete, skb, nhoff);

out_unlock:
	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

अटल पूर्णांक sit_gro_complete(काष्ठा sk_buff *skb, पूर्णांक nhoff)
अणु
	skb->encapsulation = 1;
	skb_shinfo(skb)->gso_type |= SKB_GSO_IPXIP4;
	वापस ipv6_gro_complete(skb, nhoff);
पूर्ण

अटल पूर्णांक ip6ip6_gro_complete(काष्ठा sk_buff *skb, पूर्णांक nhoff)
अणु
	skb->encapsulation = 1;
	skb_shinfo(skb)->gso_type |= SKB_GSO_IPXIP6;
	वापस ipv6_gro_complete(skb, nhoff);
पूर्ण

अटल पूर्णांक ip4ip6_gro_complete(काष्ठा sk_buff *skb, पूर्णांक nhoff)
अणु
	skb->encapsulation = 1;
	skb_shinfo(skb)->gso_type |= SKB_GSO_IPXIP6;
	वापस inet_gro_complete(skb, nhoff);
पूर्ण

अटल काष्ठा packet_offload ipv6_packet_offload __पढ़ो_mostly = अणु
	.type = cpu_to_be16(ETH_P_IPV6),
	.callbacks = अणु
		.gso_segment = ipv6_gso_segment,
		.gro_receive = ipv6_gro_receive,
		.gro_complete = ipv6_gro_complete,
	पूर्ण,
पूर्ण;

अटल काष्ठा sk_buff *sit_gso_segment(काष्ठा sk_buff *skb,
				       netdev_features_t features)
अणु
	अगर (!(skb_shinfo(skb)->gso_type & SKB_GSO_IPXIP4))
		वापस ERR_PTR(-EINVAL);

	वापस ipv6_gso_segment(skb, features);
पूर्ण

अटल काष्ठा sk_buff *ip4ip6_gso_segment(काष्ठा sk_buff *skb,
					  netdev_features_t features)
अणु
	अगर (!(skb_shinfo(skb)->gso_type & SKB_GSO_IPXIP6))
		वापस ERR_PTR(-EINVAL);

	वापस inet_gso_segment(skb, features);
पूर्ण

अटल काष्ठा sk_buff *ip6ip6_gso_segment(काष्ठा sk_buff *skb,
					  netdev_features_t features)
अणु
	अगर (!(skb_shinfo(skb)->gso_type & SKB_GSO_IPXIP6))
		वापस ERR_PTR(-EINVAL);

	वापस ipv6_gso_segment(skb, features);
पूर्ण

अटल स्थिर काष्ठा net_offload sit_offload = अणु
	.callbacks = अणु
		.gso_segment	= sit_gso_segment,
		.gro_receive    = sit_ip6ip6_gro_receive,
		.gro_complete   = sit_gro_complete,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा net_offload ip4ip6_offload = अणु
	.callbacks = अणु
		.gso_segment	= ip4ip6_gso_segment,
		.gro_receive    = ip4ip6_gro_receive,
		.gro_complete   = ip4ip6_gro_complete,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा net_offload ip6ip6_offload = अणु
	.callbacks = अणु
		.gso_segment	= ip6ip6_gso_segment,
		.gro_receive    = sit_ip6ip6_gro_receive,
		.gro_complete   = ip6ip6_gro_complete,
	पूर्ण,
पूर्ण;
अटल पूर्णांक __init ipv6_offload_init(व्योम)
अणु

	अगर (tcpv6_offload_init() < 0)
		pr_crit("%s: Cannot add TCP protocol offload\n", __func__);
	अगर (ipv6_exthdrs_offload_init() < 0)
		pr_crit("%s: Cannot add EXTHDRS protocol offload\n", __func__);

	dev_add_offload(&ipv6_packet_offload);

	inet_add_offload(&sit_offload, IPPROTO_IPV6);
	inet6_add_offload(&ip6ip6_offload, IPPROTO_IPV6);
	inet6_add_offload(&ip4ip6_offload, IPPROTO_IPIP);

	वापस 0;
पूर्ण

fs_initcall(ipv6_offload_init);
