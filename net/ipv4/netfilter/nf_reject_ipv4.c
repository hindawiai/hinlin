<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2004 Netfilter Core Team <coreteam@netfilter.org>
 */

#समावेश <linux/module.h>
#समावेश <net/ip.h>
#समावेश <net/tcp.h>
#समावेश <net/route.h>
#समावेश <net/dst.h>
#समावेश <net/netfilter/ipv4/nf_reject.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_bridge.h>

अटल पूर्णांक nf_reject_iphdr_validate(काष्ठा sk_buff *skb)
अणु
	काष्ठा iphdr *iph;
	u32 len;

	अगर (!pskb_may_pull(skb, माप(काष्ठा iphdr)))
		वापस 0;

	iph = ip_hdr(skb);
	अगर (iph->ihl < 5 || iph->version != 4)
		वापस 0;

	len = ntohs(iph->tot_len);
	अगर (skb->len < len)
		वापस 0;
	अन्यथा अगर (len < (iph->ihl*4))
		वापस 0;

	अगर (!pskb_may_pull(skb, iph->ihl*4))
		वापस 0;

	वापस 1;
पूर्ण

काष्ठा sk_buff *nf_reject_skb_v4_tcp_reset(काष्ठा net *net,
					   काष्ठा sk_buff *oldskb,
					   स्थिर काष्ठा net_device *dev,
					   पूर्णांक hook)
अणु
	स्थिर काष्ठा tcphdr *oth;
	काष्ठा sk_buff *nskb;
	काष्ठा iphdr *niph;
	काष्ठा tcphdr _oth;

	अगर (!nf_reject_iphdr_validate(oldskb))
		वापस शून्य;

	oth = nf_reject_ip_tcphdr_get(oldskb, &_oth, hook);
	अगर (!oth)
		वापस शून्य;

	nskb = alloc_skb(माप(काष्ठा iphdr) + माप(काष्ठा tcphdr) +
			 LL_MAX_HEADER, GFP_ATOMIC);
	अगर (!nskb)
		वापस शून्य;

	nskb->dev = (काष्ठा net_device *)dev;

	skb_reserve(nskb, LL_MAX_HEADER);
	niph = nf_reject_iphdr_put(nskb, oldskb, IPPROTO_TCP,
				   net->ipv4.sysctl_ip_शेष_ttl);
	nf_reject_ip_tcphdr_put(nskb, oldskb, oth);
	niph->tot_len = htons(nskb->len);
	ip_send_check(niph);

	वापस nskb;
पूर्ण
EXPORT_SYMBOL_GPL(nf_reject_skb_v4_tcp_reset);

काष्ठा sk_buff *nf_reject_skb_v4_unreach(काष्ठा net *net,
					 काष्ठा sk_buff *oldskb,
					 स्थिर काष्ठा net_device *dev,
					 पूर्णांक hook, u8 code)
अणु
	काष्ठा sk_buff *nskb;
	काष्ठा iphdr *niph;
	काष्ठा icmphdr *icmph;
	अचिन्हित पूर्णांक len;
	__wsum csum;
	u8 proto;

	अगर (!nf_reject_iphdr_validate(oldskb))
		वापस शून्य;

	/* IP header checks: fragment. */
	अगर (ip_hdr(oldskb)->frag_off & htons(IP_OFFSET))
		वापस शून्य;

	/* RFC says वापस as much as we can without exceeding 576 bytes. */
	len = min_t(अचिन्हित पूर्णांक, 536, oldskb->len);

	अगर (!pskb_may_pull(oldskb, len))
		वापस शून्य;

	अगर (pskb_trim_rcsum(oldskb, ntohs(ip_hdr(oldskb)->tot_len)))
		वापस शून्य;

	proto = ip_hdr(oldskb)->protocol;

	अगर (!skb_csum_unnecessary(oldskb) &&
	    nf_reject_verअगरy_csum(proto) &&
	    nf_ip_checksum(oldskb, hook, ip_hdrlen(oldskb), proto))
		वापस शून्य;

	nskb = alloc_skb(माप(काष्ठा iphdr) + माप(काष्ठा icmphdr) +
			 LL_MAX_HEADER + len, GFP_ATOMIC);
	अगर (!nskb)
		वापस शून्य;

	nskb->dev = (काष्ठा net_device *)dev;

	skb_reserve(nskb, LL_MAX_HEADER);
	niph = nf_reject_iphdr_put(nskb, oldskb, IPPROTO_ICMP,
				   net->ipv4.sysctl_ip_शेष_ttl);

	skb_reset_transport_header(nskb);
	icmph = skb_put_zero(nskb, माप(काष्ठा icmphdr));
	icmph->type     = ICMP_DEST_UNREACH;
	icmph->code	= code;

	skb_put_data(nskb, skb_network_header(oldskb), len);

	csum = csum_partial((व्योम *)icmph, len + माप(काष्ठा icmphdr), 0);
	icmph->checksum = csum_fold(csum);

	niph->tot_len	= htons(nskb->len);
	ip_send_check(niph);

	वापस nskb;
पूर्ण
EXPORT_SYMBOL_GPL(nf_reject_skb_v4_unreach);

स्थिर काष्ठा tcphdr *nf_reject_ip_tcphdr_get(काष्ठा sk_buff *oldskb,
					     काष्ठा tcphdr *_oth, पूर्णांक hook)
अणु
	स्थिर काष्ठा tcphdr *oth;

	/* IP header checks: fragment. */
	अगर (ip_hdr(oldskb)->frag_off & htons(IP_OFFSET))
		वापस शून्य;

	अगर (ip_hdr(oldskb)->protocol != IPPROTO_TCP)
		वापस शून्य;

	oth = skb_header_poपूर्णांकer(oldskb, ip_hdrlen(oldskb),
				 माप(काष्ठा tcphdr), _oth);
	अगर (oth == शून्य)
		वापस शून्य;

	/* No RST क्रम RST. */
	अगर (oth->rst)
		वापस शून्य;

	/* Check checksum */
	अगर (nf_ip_checksum(oldskb, hook, ip_hdrlen(oldskb), IPPROTO_TCP))
		वापस शून्य;

	वापस oth;
पूर्ण
EXPORT_SYMBOL_GPL(nf_reject_ip_tcphdr_get);

काष्ठा iphdr *nf_reject_iphdr_put(काष्ठा sk_buff *nskb,
				  स्थिर काष्ठा sk_buff *oldskb,
				  __u8 protocol, पूर्णांक ttl)
अणु
	काष्ठा iphdr *niph, *oiph = ip_hdr(oldskb);

	skb_reset_network_header(nskb);
	niph = skb_put(nskb, माप(काष्ठा iphdr));
	niph->version	= 4;
	niph->ihl	= माप(काष्ठा iphdr) / 4;
	niph->tos	= 0;
	niph->id	= 0;
	niph->frag_off	= htons(IP_DF);
	niph->protocol	= protocol;
	niph->check	= 0;
	niph->saddr	= oiph->daddr;
	niph->daddr	= oiph->saddr;
	niph->ttl	= ttl;

	nskb->protocol = htons(ETH_P_IP);

	वापस niph;
पूर्ण
EXPORT_SYMBOL_GPL(nf_reject_iphdr_put);

व्योम nf_reject_ip_tcphdr_put(काष्ठा sk_buff *nskb, स्थिर काष्ठा sk_buff *oldskb,
			  स्थिर काष्ठा tcphdr *oth)
अणु
	काष्ठा iphdr *niph = ip_hdr(nskb);
	काष्ठा tcphdr *tcph;

	skb_reset_transport_header(nskb);
	tcph = skb_put_zero(nskb, माप(काष्ठा tcphdr));
	tcph->source	= oth->dest;
	tcph->dest	= oth->source;
	tcph->करोff	= माप(काष्ठा tcphdr) / 4;

	अगर (oth->ack) अणु
		tcph->seq = oth->ack_seq;
	पूर्ण अन्यथा अणु
		tcph->ack_seq = htonl(ntohl(oth->seq) + oth->syn + oth->fin +
				      oldskb->len - ip_hdrlen(oldskb) -
				      (oth->करोff << 2));
		tcph->ack = 1;
	पूर्ण

	tcph->rst	= 1;
	tcph->check = ~tcp_v4_check(माप(काष्ठा tcphdr), niph->saddr,
				    niph->daddr, 0);
	nskb->ip_summed = CHECKSUM_PARTIAL;
	nskb->csum_start = (अचिन्हित अक्षर *)tcph - nskb->head;
	nskb->csum_offset = दुरत्व(काष्ठा tcphdr, check);
पूर्ण
EXPORT_SYMBOL_GPL(nf_reject_ip_tcphdr_put);

अटल पूर्णांक nf_reject_fill_skb_dst(काष्ठा sk_buff *skb_in)
अणु
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा flowi fl;

	स_रखो(&fl, 0, माप(काष्ठा flowi));
	fl.u.ip4.daddr = ip_hdr(skb_in)->saddr;
	nf_ip_route(dev_net(skb_in->dev), &dst, &fl, false);
	अगर (!dst)
		वापस -1;

	skb_dst_set(skb_in, dst);
	वापस 0;
पूर्ण

/* Send RST reply */
व्योम nf_send_reset(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *oldskb,
		   पूर्णांक hook)
अणु
	काष्ठा net_device *br_indev __maybe_unused;
	काष्ठा sk_buff *nskb;
	काष्ठा iphdr *niph;
	स्थिर काष्ठा tcphdr *oth;
	काष्ठा tcphdr _oth;

	oth = nf_reject_ip_tcphdr_get(oldskb, &_oth, hook);
	अगर (!oth)
		वापस;

	अगर ((hook == NF_INET_PRE_ROUTING || hook == NF_INET_INGRESS) &&
	    nf_reject_fill_skb_dst(oldskb) < 0)
		वापस;

	अगर (skb_rtable(oldskb)->rt_flags & (RTCF_BROADCAST | RTCF_MULTICAST))
		वापस;

	nskb = alloc_skb(माप(काष्ठा iphdr) + माप(काष्ठा tcphdr) +
			 LL_MAX_HEADER, GFP_ATOMIC);
	अगर (!nskb)
		वापस;

	/* ip_route_me_harder expects skb->dst to be set */
	skb_dst_set_noref(nskb, skb_dst(oldskb));

	nskb->mark = IP4_REPLY_MARK(net, oldskb->mark);

	skb_reserve(nskb, LL_MAX_HEADER);
	niph = nf_reject_iphdr_put(nskb, oldskb, IPPROTO_TCP,
				   ip4_dst_hoplimit(skb_dst(nskb)));
	nf_reject_ip_tcphdr_put(nskb, oldskb, oth);
	अगर (ip_route_me_harder(net, sk, nskb, RTN_UNSPEC))
		जाओ मुक्त_nskb;

	niph = ip_hdr(nskb);

	/* "Never happens" */
	अगर (nskb->len > dst_mtu(skb_dst(nskb)))
		जाओ मुक्त_nskb;

	nf_ct_attach(nskb, oldskb);

#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
	/* If we use ip_local_out क्रम bridged traffic, the MAC source on
	 * the RST will be ours, instead of the destination's.  This confuses
	 * some routers/firewalls, and they drop the packet.  So we need to
	 * build the eth header using the original destination's MAC as the
	 * source, and send the RST packet directly.
	 */
	br_indev = nf_bridge_get_physindev(oldskb);
	अगर (br_indev) अणु
		काष्ठा ethhdr *oeth = eth_hdr(oldskb);

		nskb->dev = br_indev;
		niph->tot_len = htons(nskb->len);
		ip_send_check(niph);
		अगर (dev_hard_header(nskb, nskb->dev, ntohs(nskb->protocol),
				    oeth->h_source, oeth->h_dest, nskb->len) < 0)
			जाओ मुक्त_nskb;
		dev_queue_xmit(nskb);
	पूर्ण अन्यथा
#पूर्ण_अगर
		ip_local_out(net, nskb->sk, nskb);

	वापस;

 मुक्त_nskb:
	kमुक्त_skb(nskb);
पूर्ण
EXPORT_SYMBOL_GPL(nf_send_reset);

व्योम nf_send_unreach(काष्ठा sk_buff *skb_in, पूर्णांक code, पूर्णांक hook)
अणु
	काष्ठा iphdr *iph = ip_hdr(skb_in);
	u8 proto = iph->protocol;

	अगर (iph->frag_off & htons(IP_OFFSET))
		वापस;

	अगर ((hook == NF_INET_PRE_ROUTING || hook == NF_INET_INGRESS) &&
	    nf_reject_fill_skb_dst(skb_in) < 0)
		वापस;

	अगर (skb_csum_unnecessary(skb_in) || !nf_reject_verअगरy_csum(proto)) अणु
		icmp_send(skb_in, ICMP_DEST_UNREACH, code, 0);
		वापस;
	पूर्ण

	अगर (nf_ip_checksum(skb_in, hook, ip_hdrlen(skb_in), proto) == 0)
		icmp_send(skb_in, ICMP_DEST_UNREACH, code, 0);
पूर्ण
EXPORT_SYMBOL_GPL(nf_send_unreach);

MODULE_LICENSE("GPL");
