<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xfrm6_input.c: based on net/ipv4/xfrm4_input.c
 *
 * Authors:
 *	Mitsuru KANDA @USAGI
 *	Kazunori MIYAZAWA @USAGI
 *	Kunihiro Ishiguro <kunihiro@ipinfusion.com>
 *	YOSHIFUJI Hideaki @USAGI
 *		IPv6 support
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <net/ipv6.h>
#समावेश <net/xfrm.h>

पूर्णांक xfrm6_rcv_spi(काष्ठा sk_buff *skb, पूर्णांक nexthdr, __be32 spi,
		  काष्ठा ip6_tnl *t)
अणु
	XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip6 = t;
	XFRM_SPI_SKB_CB(skb)->family = AF_INET6;
	XFRM_SPI_SKB_CB(skb)->daddroff = दुरत्व(काष्ठा ipv6hdr, daddr);
	वापस xfrm_input(skb, nexthdr, spi, 0);
पूर्ण
EXPORT_SYMBOL(xfrm6_rcv_spi);

अटल पूर्णांक xfrm6_transport_finish2(काष्ठा net *net, काष्ठा sock *sk,
				   काष्ठा sk_buff *skb)
अणु
	अगर (xfrm_trans_queue(skb, ip6_rcv_finish)) अणु
		kमुक्त_skb(skb);
		वापस NET_RX_DROP;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक xfrm6_transport_finish(काष्ठा sk_buff *skb, पूर्णांक async)
अणु
	काष्ठा xfrm_offload *xo = xfrm_offload(skb);
	पूर्णांक nhlen = skb->data - skb_network_header(skb);

	skb_network_header(skb)[IP6CB(skb)->nhoff] =
		XFRM_MODE_SKB_CB(skb)->protocol;

#अगर_अघोषित CONFIG_NETFILTER
	अगर (!async)
		वापस 1;
#पूर्ण_अगर

	__skb_push(skb, nhlen);
	ipv6_hdr(skb)->payload_len = htons(skb->len - माप(काष्ठा ipv6hdr));
	skb_postpush_rcsum(skb, skb_network_header(skb), nhlen);

	अगर (xo && (xo->flags & XFRM_GRO)) अणु
		skb_mac_header_rebuild(skb);
		skb_reset_transport_header(skb);
		वापस 0;
	पूर्ण

	NF_HOOK(NFPROTO_IPV6, NF_INET_PRE_ROUTING,
		dev_net(skb->dev), शून्य, skb, skb->dev, शून्य,
		xfrm6_transport_finish2);
	वापस 0;
पूर्ण

/* If it's a keepalive packet, then just eat it.
 * If it's an encapsulated packet, then pass it to the
 * IPsec xfrm input.
 * Returns 0 अगर skb passed to xfrm or was dropped.
 * Returns >0 अगर skb should be passed to UDP.
 * Returns <0 अगर skb should be resubmitted (-ret is protocol)
 */
पूर्णांक xfrm6_udp_encap_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा udp_sock *up = udp_sk(sk);
	काष्ठा udphdr *uh;
	काष्ठा ipv6hdr *ip6h;
	पूर्णांक len;
	पूर्णांक ip6hlen = माप(काष्ठा ipv6hdr);

	__u8 *udpdata;
	__be32 *udpdata32;
	__u16 encap_type = up->encap_type;

	/* अगर this is not encapsulated socket, then just वापस now */
	अगर (!encap_type)
		वापस 1;

	/* If this is a paged skb, make sure we pull up
	 * whatever data we need to look at. */
	len = skb->len - माप(काष्ठा udphdr);
	अगर (!pskb_may_pull(skb, माप(काष्ठा udphdr) + min(len, 8)))
		वापस 1;

	/* Now we can get the poपूर्णांकers */
	uh = udp_hdr(skb);
	udpdata = (__u8 *)uh + माप(काष्ठा udphdr);
	udpdata32 = (__be32 *)udpdata;

	चयन (encap_type) अणु
	शेष:
	हाल UDP_ENCAP_ESPINUDP:
		/* Check अगर this is a keepalive packet.  If so, eat it. */
		अगर (len == 1 && udpdata[0] == 0xff) अणु
			जाओ drop;
		पूर्ण अन्यथा अगर (len > माप(काष्ठा ip_esp_hdr) && udpdata32[0] != 0) अणु
			/* ESP Packet without Non-ESP header */
			len = माप(काष्ठा udphdr);
		पूर्ण अन्यथा
			/* Must be an IKE packet.. pass it through */
			वापस 1;
		अवरोध;
	हाल UDP_ENCAP_ESPINUDP_NON_IKE:
		/* Check अगर this is a keepalive packet.  If so, eat it. */
		अगर (len == 1 && udpdata[0] == 0xff) अणु
			जाओ drop;
		पूर्ण अन्यथा अगर (len > 2 * माप(u32) + माप(काष्ठा ip_esp_hdr) &&
			   udpdata32[0] == 0 && udpdata32[1] == 0) अणु

			/* ESP Packet with Non-IKE marker */
			len = माप(काष्ठा udphdr) + 2 * माप(u32);
		पूर्ण अन्यथा
			/* Must be an IKE packet.. pass it through */
			वापस 1;
		अवरोध;
	पूर्ण

	/* At this poपूर्णांक we are sure that this is an ESPinUDP packet,
	 * so we need to हटाओ 'len' bytes from the packet (the UDP
	 * header and optional ESP marker bytes) and then modअगरy the
	 * protocol to ESP, and then call पूर्णांकo the transक्रमm receiver.
	 */
	अगर (skb_unclone(skb, GFP_ATOMIC))
		जाओ drop;

	/* Now we can update and verअगरy the packet length... */
	ip6h = ipv6_hdr(skb);
	ip6h->payload_len = htons(ntohs(ip6h->payload_len) - len);
	अगर (skb->len < ip6hlen + len) अणु
		/* packet is too small!?! */
		जाओ drop;
	पूर्ण

	/* pull the data buffer up to the ESP header and set the
	 * transport header to poपूर्णांक to ESP.  Keep UDP on the stack
	 * क्रम later.
	 */
	__skb_pull(skb, len);
	skb_reset_transport_header(skb);

	/* process ESP */
	वापस xfrm6_rcv_encap(skb, IPPROTO_ESP, 0, encap_type);

drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

पूर्णांक xfrm6_rcv_tnl(काष्ठा sk_buff *skb, काष्ठा ip6_tnl *t)
अणु
	वापस xfrm6_rcv_spi(skb, skb_network_header(skb)[IP6CB(skb)->nhoff],
			     0, t);
पूर्ण
EXPORT_SYMBOL(xfrm6_rcv_tnl);

पूर्णांक xfrm6_rcv(काष्ठा sk_buff *skb)
अणु
	वापस xfrm6_rcv_tnl(skb, शून्य);
पूर्ण
EXPORT_SYMBOL(xfrm6_rcv);
पूर्णांक xfrm6_input_addr(काष्ठा sk_buff *skb, xfrm_address_t *daddr,
		     xfrm_address_t *saddr, u8 proto)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा xfrm_state *x = शून्य;
	काष्ठा sec_path *sp;
	पूर्णांक i = 0;

	sp = secpath_set(skb);
	अगर (!sp) अणु
		XFRM_INC_STATS(net, LINUX_MIB_XFRMINERROR);
		जाओ drop;
	पूर्ण

	अगर (1 + sp->len == XFRM_MAX_DEPTH) अणु
		XFRM_INC_STATS(net, LINUX_MIB_XFRMINBUFFERERROR);
		जाओ drop;
	पूर्ण

	क्रम (i = 0; i < 3; i++) अणु
		xfrm_address_t *dst, *src;

		चयन (i) अणु
		हाल 0:
			dst = daddr;
			src = saddr;
			अवरोध;
		हाल 1:
			/* lookup state with wild-card source address */
			dst = daddr;
			src = (xfrm_address_t *)&in6addr_any;
			अवरोध;
		शेष:
			/* lookup state with wild-card addresses */
			dst = (xfrm_address_t *)&in6addr_any;
			src = (xfrm_address_t *)&in6addr_any;
			अवरोध;
		पूर्ण

		x = xfrm_state_lookup_byaddr(net, skb->mark, dst, src, proto, AF_INET6);
		अगर (!x)
			जारी;

		spin_lock(&x->lock);

		अगर ((!i || (x->props.flags & XFRM_STATE_WILDRECV)) &&
		    likely(x->km.state == XFRM_STATE_VALID) &&
		    !xfrm_state_check_expire(x)) अणु
			spin_unlock(&x->lock);
			अगर (x->type->input(x, skb) > 0) अणु
				/* found a valid state */
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा
			spin_unlock(&x->lock);

		xfrm_state_put(x);
		x = शून्य;
	पूर्ण

	अगर (!x) अणु
		XFRM_INC_STATS(net, LINUX_MIB_XFRMINNOSTATES);
		xfrm_audit_state_notfound_simple(skb, AF_INET6);
		जाओ drop;
	पूर्ण

	sp->xvec[sp->len++] = x;

	spin_lock(&x->lock);

	x->curlft.bytes += skb->len;
	x->curlft.packets++;

	spin_unlock(&x->lock);

	वापस 1;

drop:
	वापस -1;
पूर्ण
EXPORT_SYMBOL(xfrm6_input_addr);
