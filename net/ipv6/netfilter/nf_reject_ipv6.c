<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2004 Netfilter Core Team <coreteam@netfilter.org>
 */

#समावेश <linux/module.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/netfilter/ipv6/nf_reject.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter_bridge.h>

अटल bool nf_reject_v6_csum_ok(काष्ठा sk_buff *skb, पूर्णांक hook)
अणु
	स्थिर काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);
	पूर्णांक thoff;
	__be16 fo;
	u8 proto = ip6h->nexthdr;

	अगर (skb_csum_unnecessary(skb))
		वापस true;

	अगर (ip6h->payload_len &&
	    pskb_trim_rcsum(skb, ntohs(ip6h->payload_len) + माप(*ip6h)))
		वापस false;

	ip6h = ipv6_hdr(skb);
	thoff = ipv6_skip_exthdr(skb, ((u8*)(ip6h+1) - skb->data), &proto, &fo);
	अगर (thoff < 0 || thoff >= skb->len || (fo & htons(~0x7)) != 0)
		वापस false;

	अगर (!nf_reject_verअगरy_csum(proto))
		वापस true;

	वापस nf_ip6_checksum(skb, hook, thoff, proto) == 0;
पूर्ण

अटल पूर्णांक nf_reject_ip6hdr_validate(काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6hdr *hdr;
	u32 pkt_len;

	अगर (!pskb_may_pull(skb, माप(काष्ठा ipv6hdr)))
		वापस 0;

	hdr = ipv6_hdr(skb);
	अगर (hdr->version != 6)
		वापस 0;

	pkt_len = ntohs(hdr->payload_len);
	अगर (pkt_len + माप(काष्ठा ipv6hdr) > skb->len)
		वापस 0;

	वापस 1;
पूर्ण

काष्ठा sk_buff *nf_reject_skb_v6_tcp_reset(काष्ठा net *net,
					   काष्ठा sk_buff *oldskb,
					   स्थिर काष्ठा net_device *dev,
					   पूर्णांक hook)
अणु
	काष्ठा sk_buff *nskb;
	स्थिर काष्ठा tcphdr *oth;
	काष्ठा tcphdr _oth;
	अचिन्हित पूर्णांक otcplen;
	काष्ठा ipv6hdr *nip6h;

	अगर (!nf_reject_ip6hdr_validate(oldskb))
		वापस शून्य;

	oth = nf_reject_ip6_tcphdr_get(oldskb, &_oth, &otcplen, hook);
	अगर (!oth)
		वापस शून्य;

	nskb = alloc_skb(माप(काष्ठा ipv6hdr) + माप(काष्ठा tcphdr) +
			 LL_MAX_HEADER, GFP_ATOMIC);
	अगर (!nskb)
		वापस शून्य;

	nskb->dev = (काष्ठा net_device *)dev;

	skb_reserve(nskb, LL_MAX_HEADER);
	nip6h = nf_reject_ip6hdr_put(nskb, oldskb, IPPROTO_TCP,
				     net->ipv6.devconf_all->hop_limit);
	nf_reject_ip6_tcphdr_put(nskb, oldskb, oth, otcplen);
	nip6h->payload_len = htons(nskb->len - माप(काष्ठा ipv6hdr));

	वापस nskb;
पूर्ण
EXPORT_SYMBOL_GPL(nf_reject_skb_v6_tcp_reset);

काष्ठा sk_buff *nf_reject_skb_v6_unreach(काष्ठा net *net,
					 काष्ठा sk_buff *oldskb,
					 स्थिर काष्ठा net_device *dev,
					 पूर्णांक hook, u8 code)
अणु
	काष्ठा sk_buff *nskb;
	काष्ठा ipv6hdr *nip6h;
	काष्ठा icmp6hdr *icmp6h;
	अचिन्हित पूर्णांक len;

	अगर (!nf_reject_ip6hdr_validate(oldskb))
		वापस शून्य;

	/* Include "As much of invoking packet as possible without the ICMPv6
	 * packet exceeding the minimum IPv6 MTU" in the ICMP payload.
	 */
	len = min_t(अचिन्हित पूर्णांक, 1220, oldskb->len);

	अगर (!pskb_may_pull(oldskb, len))
		वापस शून्य;

	अगर (!nf_reject_v6_csum_ok(oldskb, hook))
		वापस शून्य;

	nskb = alloc_skb(माप(काष्ठा ipv6hdr) + माप(काष्ठा icmp6hdr) +
			 LL_MAX_HEADER + len, GFP_ATOMIC);
	अगर (!nskb)
		वापस शून्य;

	nskb->dev = (काष्ठा net_device *)dev;

	skb_reserve(nskb, LL_MAX_HEADER);
	nip6h = nf_reject_ip6hdr_put(nskb, oldskb, IPPROTO_ICMPV6,
				     net->ipv6.devconf_all->hop_limit);

	skb_reset_transport_header(nskb);
	icmp6h = skb_put_zero(nskb, माप(काष्ठा icmp6hdr));
	icmp6h->icmp6_type = ICMPV6_DEST_UNREACH;
	icmp6h->icmp6_code = code;

	skb_put_data(nskb, skb_network_header(oldskb), len);
	nip6h->payload_len = htons(nskb->len - माप(काष्ठा ipv6hdr));

	icmp6h->icmp6_cksum =
		csum_ipv6_magic(&nip6h->saddr, &nip6h->daddr,
				nskb->len - माप(काष्ठा ipv6hdr),
				IPPROTO_ICMPV6,
				csum_partial(icmp6h,
					     nskb->len - माप(काष्ठा ipv6hdr),
					     0));

	वापस nskb;
पूर्ण
EXPORT_SYMBOL_GPL(nf_reject_skb_v6_unreach);

स्थिर काष्ठा tcphdr *nf_reject_ip6_tcphdr_get(काष्ठा sk_buff *oldskb,
					      काष्ठा tcphdr *otcph,
					      अचिन्हित पूर्णांक *otcplen, पूर्णांक hook)
अणु
	स्थिर काष्ठा ipv6hdr *oip6h = ipv6_hdr(oldskb);
	u8 proto;
	__be16 frag_off;
	पूर्णांक tcphoff;

	proto = oip6h->nexthdr;
	tcphoff = ipv6_skip_exthdr(oldskb, ((u8 *)(oip6h + 1) - oldskb->data),
				   &proto, &frag_off);

	अगर ((tcphoff < 0) || (tcphoff > oldskb->len)) अणु
		pr_debug("Cannot get TCP header.\n");
		वापस शून्य;
	पूर्ण

	*otcplen = oldskb->len - tcphoff;

	/* IP header checks: fragment, too लघु. */
	अगर (proto != IPPROTO_TCP || *otcplen < माप(काष्ठा tcphdr)) अणु
		pr_debug("proto(%d) != IPPROTO_TCP or too short (len = %d)\n",
			 proto, *otcplen);
		वापस शून्य;
	पूर्ण

	otcph = skb_header_poपूर्णांकer(oldskb, tcphoff, माप(काष्ठा tcphdr),
				   otcph);
	अगर (otcph == शून्य)
		वापस शून्य;

	/* No RST क्रम RST. */
	अगर (otcph->rst) अणु
		pr_debug("RST is set\n");
		वापस शून्य;
	पूर्ण

	/* Check checksum. */
	अगर (nf_ip6_checksum(oldskb, hook, tcphoff, IPPROTO_TCP)) अणु
		pr_debug("TCP checksum is invalid\n");
		वापस शून्य;
	पूर्ण

	वापस otcph;
पूर्ण
EXPORT_SYMBOL_GPL(nf_reject_ip6_tcphdr_get);

काष्ठा ipv6hdr *nf_reject_ip6hdr_put(काष्ठा sk_buff *nskb,
				     स्थिर काष्ठा sk_buff *oldskb,
				     __u8 protocol, पूर्णांक hoplimit)
अणु
	काष्ठा ipv6hdr *ip6h;
	स्थिर काष्ठा ipv6hdr *oip6h = ipv6_hdr(oldskb);
#घोषणा DEFAULT_TOS_VALUE	0x0U
	स्थिर __u8 tclass = DEFAULT_TOS_VALUE;

	skb_put(nskb, माप(काष्ठा ipv6hdr));
	skb_reset_network_header(nskb);
	ip6h = ipv6_hdr(nskb);
	ip6_flow_hdr(ip6h, tclass, 0);
	ip6h->hop_limit = hoplimit;
	ip6h->nexthdr = protocol;
	ip6h->saddr = oip6h->daddr;
	ip6h->daddr = oip6h->saddr;

	nskb->protocol = htons(ETH_P_IPV6);

	वापस ip6h;
पूर्ण
EXPORT_SYMBOL_GPL(nf_reject_ip6hdr_put);

व्योम nf_reject_ip6_tcphdr_put(काष्ठा sk_buff *nskb,
			      स्थिर काष्ठा sk_buff *oldskb,
			      स्थिर काष्ठा tcphdr *oth, अचिन्हित पूर्णांक otcplen)
अणु
	काष्ठा tcphdr *tcph;
	पूर्णांक needs_ack;

	skb_reset_transport_header(nskb);
	tcph = skb_put(nskb, माप(काष्ठा tcphdr));
	/* Truncate to length (no data) */
	tcph->करोff = माप(काष्ठा tcphdr)/4;
	tcph->source = oth->dest;
	tcph->dest = oth->source;

	अगर (oth->ack) अणु
		needs_ack = 0;
		tcph->seq = oth->ack_seq;
		tcph->ack_seq = 0;
	पूर्ण अन्यथा अणु
		needs_ack = 1;
		tcph->ack_seq = htonl(ntohl(oth->seq) + oth->syn + oth->fin +
				      otcplen - (oth->करोff<<2));
		tcph->seq = 0;
	पूर्ण

	/* Reset flags */
	((u_पूर्णांक8_t *)tcph)[13] = 0;
	tcph->rst = 1;
	tcph->ack = needs_ack;
	tcph->winकरोw = 0;
	tcph->urg_ptr = 0;
	tcph->check = 0;

	/* Adjust TCP checksum */
	tcph->check = csum_ipv6_magic(&ipv6_hdr(nskb)->saddr,
				      &ipv6_hdr(nskb)->daddr,
				      माप(काष्ठा tcphdr), IPPROTO_TCP,
				      csum_partial(tcph,
						   माप(काष्ठा tcphdr), 0));
पूर्ण
EXPORT_SYMBOL_GPL(nf_reject_ip6_tcphdr_put);

अटल पूर्णांक nf_reject6_fill_skb_dst(काष्ठा sk_buff *skb_in)
अणु
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा flowi fl;

	स_रखो(&fl, 0, माप(काष्ठा flowi));
	fl.u.ip6.daddr = ipv6_hdr(skb_in)->saddr;
	nf_ip6_route(dev_net(skb_in->dev), &dst, &fl, false);
	अगर (!dst)
		वापस -1;

	skb_dst_set(skb_in, dst);
	वापस 0;
पूर्ण

व्योम nf_send_reset6(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *oldskb,
		    पूर्णांक hook)
अणु
	काष्ठा net_device *br_indev __maybe_unused;
	काष्ठा sk_buff *nskb;
	काष्ठा tcphdr _otcph;
	स्थिर काष्ठा tcphdr *otcph;
	अचिन्हित पूर्णांक otcplen, hh_len;
	स्थिर काष्ठा ipv6hdr *oip6h = ipv6_hdr(oldskb);
	काष्ठा ipv6hdr *ip6h;
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा flowi6 fl6;

	अगर ((!(ipv6_addr_type(&oip6h->saddr) & IPV6_ADDR_UNICAST)) ||
	    (!(ipv6_addr_type(&oip6h->daddr) & IPV6_ADDR_UNICAST))) अणु
		pr_debug("addr is not unicast.\n");
		वापस;
	पूर्ण

	otcph = nf_reject_ip6_tcphdr_get(oldskb, &_otcph, &otcplen, hook);
	अगर (!otcph)
		वापस;

	स_रखो(&fl6, 0, माप(fl6));
	fl6.flowi6_proto = IPPROTO_TCP;
	fl6.saddr = oip6h->daddr;
	fl6.daddr = oip6h->saddr;
	fl6.fl6_sport = otcph->dest;
	fl6.fl6_dport = otcph->source;

	अगर (hook == NF_INET_PRE_ROUTING || hook == NF_INET_INGRESS) अणु
		nf_ip6_route(net, &dst, flowi6_to_flowi(&fl6), false);
		अगर (!dst)
			वापस;
		skb_dst_set(oldskb, dst);
	पूर्ण

	fl6.flowi6_oअगर = l3mdev_master_अगरindex(skb_dst(oldskb)->dev);
	fl6.flowi6_mark = IP6_REPLY_MARK(net, oldskb->mark);
	security_skb_classअगरy_flow(oldskb, flowi6_to_flowi_common(&fl6));
	dst = ip6_route_output(net, शून्य, &fl6);
	अगर (dst->error) अणु
		dst_release(dst);
		वापस;
	पूर्ण
	dst = xfrm_lookup(net, dst, flowi6_to_flowi(&fl6), शून्य, 0);
	अगर (IS_ERR(dst))
		वापस;

	hh_len = (dst->dev->hard_header_len + 15)&~15;
	nskb = alloc_skb(hh_len + 15 + dst->header_len + माप(काष्ठा ipv6hdr)
			 + माप(काष्ठा tcphdr) + dst->trailer_len,
			 GFP_ATOMIC);

	अगर (!nskb) अणु
		net_dbg_ratelimited("cannot alloc skb\n");
		dst_release(dst);
		वापस;
	पूर्ण

	skb_dst_set(nskb, dst);

	nskb->mark = fl6.flowi6_mark;

	skb_reserve(nskb, hh_len + dst->header_len);
	ip6h = nf_reject_ip6hdr_put(nskb, oldskb, IPPROTO_TCP,
				    ip6_dst_hoplimit(dst));
	nf_reject_ip6_tcphdr_put(nskb, oldskb, otcph, otcplen);

	nf_ct_attach(nskb, oldskb);

#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
	/* If we use ip6_local_out क्रम bridged traffic, the MAC source on
	 * the RST will be ours, instead of the destination's.  This confuses
	 * some routers/firewalls, and they drop the packet.  So we need to
	 * build the eth header using the original destination's MAC as the
	 * source, and send the RST packet directly.
	 */
	br_indev = nf_bridge_get_physindev(oldskb);
	अगर (br_indev) अणु
		काष्ठा ethhdr *oeth = eth_hdr(oldskb);

		nskb->dev = br_indev;
		nskb->protocol = htons(ETH_P_IPV6);
		ip6h->payload_len = htons(माप(काष्ठा tcphdr));
		अगर (dev_hard_header(nskb, nskb->dev, ntohs(nskb->protocol),
				    oeth->h_source, oeth->h_dest, nskb->len) < 0) अणु
			kमुक्त_skb(nskb);
			वापस;
		पूर्ण
		dev_queue_xmit(nskb);
	पूर्ण अन्यथा
#पूर्ण_अगर
		ip6_local_out(net, sk, nskb);
पूर्ण
EXPORT_SYMBOL_GPL(nf_send_reset6);

अटल bool reject6_csum_ok(काष्ठा sk_buff *skb, पूर्णांक hook)
अणु
	स्थिर काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);
	पूर्णांक thoff;
	__be16 fo;
	u8 proto;

	अगर (skb_csum_unnecessary(skb))
		वापस true;

	proto = ip6h->nexthdr;
	thoff = ipv6_skip_exthdr(skb, ((u8 *)(ip6h + 1) - skb->data), &proto, &fo);

	अगर (thoff < 0 || thoff >= skb->len || (fo & htons(~0x7)) != 0)
		वापस false;

	अगर (!nf_reject_verअगरy_csum(proto))
		वापस true;

	वापस nf_ip6_checksum(skb, hook, thoff, proto) == 0;
पूर्ण

व्योम nf_send_unreach6(काष्ठा net *net, काष्ठा sk_buff *skb_in,
		      अचिन्हित अक्षर code, अचिन्हित पूर्णांक hooknum)
अणु
	अगर (!reject6_csum_ok(skb_in, hooknum))
		वापस;

	अगर (hooknum == NF_INET_LOCAL_OUT && skb_in->dev == शून्य)
		skb_in->dev = net->loopback_dev;

	अगर ((hooknum == NF_INET_PRE_ROUTING || hooknum == NF_INET_INGRESS) &&
	    nf_reject6_fill_skb_dst(skb_in) < 0)
		वापस;

	icmpv6_send(skb_in, ICMPV6_DEST_UNREACH, code, 0);
पूर्ण
EXPORT_SYMBOL_GPL(nf_send_unreach6);

MODULE_LICENSE("GPL");
