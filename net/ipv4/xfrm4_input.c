<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xfrm4_input.c
 *
 * Changes:
 *	YOSHIFUJI Hideaki @USAGI
 *		Split up af-specअगरic portion
 *	Derek Atkins <derek@ihtfp.com>
 *		Add Encapsulation support
 *
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <net/ip.h>
#समावेश <net/xfrm.h>

अटल पूर्णांक xfrm4_rcv_encap_finish2(काष्ठा net *net, काष्ठा sock *sk,
				   काष्ठा sk_buff *skb)
अणु
	वापस dst_input(skb);
पूर्ण

अटल अंतरभूत पूर्णांक xfrm4_rcv_encap_finish(काष्ठा net *net, काष्ठा sock *sk,
					 काष्ठा sk_buff *skb)
अणु
	अगर (!skb_dst(skb)) अणु
		स्थिर काष्ठा iphdr *iph = ip_hdr(skb);

		अगर (ip_route_input_noref(skb, iph->daddr, iph->saddr,
					 iph->tos, skb->dev))
			जाओ drop;
	पूर्ण

	अगर (xfrm_trans_queue(skb, xfrm4_rcv_encap_finish2))
		जाओ drop;

	वापस 0;
drop:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण

पूर्णांक xfrm4_transport_finish(काष्ठा sk_buff *skb, पूर्णांक async)
अणु
	काष्ठा xfrm_offload *xo = xfrm_offload(skb);
	काष्ठा iphdr *iph = ip_hdr(skb);

	iph->protocol = XFRM_MODE_SKB_CB(skb)->protocol;

#अगर_अघोषित CONFIG_NETFILTER
	अगर (!async)
		वापस -iph->protocol;
#पूर्ण_अगर

	__skb_push(skb, skb->data - skb_network_header(skb));
	iph->tot_len = htons(skb->len);
	ip_send_check(iph);

	अगर (xo && (xo->flags & XFRM_GRO)) अणु
		skb_mac_header_rebuild(skb);
		skb_reset_transport_header(skb);
		वापस 0;
	पूर्ण

	NF_HOOK(NFPROTO_IPV4, NF_INET_PRE_ROUTING,
		dev_net(skb->dev), शून्य, skb, skb->dev, शून्य,
		xfrm4_rcv_encap_finish);
	वापस 0;
पूर्ण

/* If it's a keepalive packet, then just eat it.
 * If it's an encapsulated packet, then pass it to the
 * IPsec xfrm input.
 * Returns 0 अगर skb passed to xfrm or was dropped.
 * Returns >0 अगर skb should be passed to UDP.
 * Returns <0 अगर skb should be resubmitted (-ret is protocol)
 */
पूर्णांक xfrm4_udp_encap_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा udp_sock *up = udp_sk(sk);
	काष्ठा udphdr *uh;
	काष्ठा iphdr *iph;
	पूर्णांक iphlen, len;

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
	iph = ip_hdr(skb);
	iphlen = iph->ihl << 2;
	iph->tot_len = htons(ntohs(iph->tot_len) - len);
	अगर (skb->len < iphlen + len) अणु
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
	वापस xfrm4_rcv_encap(skb, IPPROTO_ESP, 0, encap_type);

drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

पूर्णांक xfrm4_rcv(काष्ठा sk_buff *skb)
अणु
	वापस xfrm4_rcv_spi(skb, ip_hdr(skb)->protocol, 0);
पूर्ण
EXPORT_SYMBOL(xfrm4_rcv);
