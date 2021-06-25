<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013 Nicira, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/init.h>
#समावेश <linux/in6.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अटल_key.h>

#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/protocol.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/ip6_tunnel.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/arp.h>
#समावेश <net/checksum.h>
#समावेश <net/dsfield.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/xfrm.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/dst_metadata.h>
#समावेश <net/geneve.h>
#समावेश <net/vxlan.h>
#समावेश <net/erspan.h>

स्थिर काष्ठा ip_tunnel_encap_ops __rcu *
		iptun_encaps[MAX_IPTUN_ENCAP_OPS] __पढ़ो_mostly;
EXPORT_SYMBOL(iptun_encaps);

स्थिर काष्ठा ip6_tnl_encap_ops __rcu *
		ip6tun_encaps[MAX_IPTUN_ENCAP_OPS] __पढ़ो_mostly;
EXPORT_SYMBOL(ip6tun_encaps);

व्योम iptunnel_xmit(काष्ठा sock *sk, काष्ठा rtable *rt, काष्ठा sk_buff *skb,
		   __be32 src, __be32 dst, __u8 proto,
		   __u8 tos, __u8 ttl, __be16 df, bool xnet)
अणु
	पूर्णांक pkt_len = skb->len - skb_inner_network_offset(skb);
	काष्ठा net *net = dev_net(rt->dst.dev);
	काष्ठा net_device *dev = skb->dev;
	काष्ठा iphdr *iph;
	पूर्णांक err;

	skb_scrub_packet(skb, xnet);

	skb_clear_hash_अगर_not_l4(skb);
	skb_dst_set(skb, &rt->dst);
	स_रखो(IPCB(skb), 0, माप(*IPCB(skb)));

	/* Push करोwn and install the IP header. */
	skb_push(skb, माप(काष्ठा iphdr));
	skb_reset_network_header(skb);

	iph = ip_hdr(skb);

	iph->version	=	4;
	iph->ihl	=	माप(काष्ठा iphdr) >> 2;
	iph->frag_off	=	ip_mtu_locked(&rt->dst) ? 0 : df;
	iph->protocol	=	proto;
	iph->tos	=	tos;
	iph->daddr	=	dst;
	iph->saddr	=	src;
	iph->ttl	=	ttl;
	__ip_select_ident(net, iph, skb_shinfo(skb)->gso_segs ?: 1);

	err = ip_local_out(net, sk, skb);

	अगर (dev) अणु
		अगर (unlikely(net_xmit_eval(err)))
			pkt_len = 0;
		iptunnel_xmit_stats(dev, pkt_len);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(iptunnel_xmit);

पूर्णांक __iptunnel_pull_header(काष्ठा sk_buff *skb, पूर्णांक hdr_len,
			   __be16 inner_proto, bool raw_proto, bool xnet)
अणु
	अगर (unlikely(!pskb_may_pull(skb, hdr_len)))
		वापस -ENOMEM;

	skb_pull_rcsum(skb, hdr_len);

	अगर (!raw_proto && inner_proto == htons(ETH_P_TEB)) अणु
		काष्ठा ethhdr *eh;

		अगर (unlikely(!pskb_may_pull(skb, ETH_HLEN)))
			वापस -ENOMEM;

		eh = (काष्ठा ethhdr *)skb->data;
		अगर (likely(eth_proto_is_802_3(eh->h_proto)))
			skb->protocol = eh->h_proto;
		अन्यथा
			skb->protocol = htons(ETH_P_802_2);

	पूर्ण अन्यथा अणु
		skb->protocol = inner_proto;
	पूर्ण

	skb_clear_hash_अगर_not_l4(skb);
	__vlan_hwaccel_clear_tag(skb);
	skb_set_queue_mapping(skb, 0);
	skb_scrub_packet(skb, xnet);

	वापस iptunnel_pull_offloads(skb);
पूर्ण
EXPORT_SYMBOL_GPL(__iptunnel_pull_header);

काष्ठा metadata_dst *iptunnel_metadata_reply(काष्ठा metadata_dst *md,
					     gfp_t flags)
अणु
	काष्ठा metadata_dst *res;
	काष्ठा ip_tunnel_info *dst, *src;

	अगर (!md || md->type != METADATA_IP_TUNNEL ||
	    md->u.tun_info.mode & IP_TUNNEL_INFO_TX)
		वापस शून्य;

	src = &md->u.tun_info;
	res = metadata_dst_alloc(src->options_len, METADATA_IP_TUNNEL, flags);
	अगर (!res)
		वापस शून्य;

	dst = &res->u.tun_info;
	dst->key.tun_id = src->key.tun_id;
	अगर (src->mode & IP_TUNNEL_INFO_IPV6)
		स_नकल(&dst->key.u.ipv6.dst, &src->key.u.ipv6.src,
		       माप(काष्ठा in6_addr));
	अन्यथा
		dst->key.u.ipv4.dst = src->key.u.ipv4.src;
	dst->key.tun_flags = src->key.tun_flags;
	dst->mode = src->mode | IP_TUNNEL_INFO_TX;
	ip_tunnel_info_opts_set(dst, ip_tunnel_info_opts(src),
				src->options_len, 0);

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(iptunnel_metadata_reply);

पूर्णांक iptunnel_handle_offloads(काष्ठा sk_buff *skb,
			     पूर्णांक gso_type_mask)
अणु
	पूर्णांक err;

	अगर (likely(!skb->encapsulation)) अणु
		skb_reset_inner_headers(skb);
		skb->encapsulation = 1;
	पूर्ण

	अगर (skb_is_gso(skb)) अणु
		err = skb_header_unclone(skb, GFP_ATOMIC);
		अगर (unlikely(err))
			वापस err;
		skb_shinfo(skb)->gso_type |= gso_type_mask;
		वापस 0;
	पूर्ण

	अगर (skb->ip_summed != CHECKSUM_PARTIAL) अणु
		skb->ip_summed = CHECKSUM_NONE;
		/* We clear encapsulation here to prevent badly-written
		 * drivers potentially deciding to offload an inner checksum
		 * अगर we set CHECKSUM_PARTIAL on the outer header.
		 * This should go away when the drivers are all fixed.
		 */
		skb->encapsulation = 0;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iptunnel_handle_offloads);

/**
 * iptunnel_pmtud_build_icmp() - Build ICMP error message क्रम PMTUD
 * @skb:	Original packet with L2 header
 * @mtu:	MTU value क्रम ICMP error
 *
 * Return: length on success, negative error code अगर message couldn't be built.
 */
अटल पूर्णांक iptunnel_pmtud_build_icmp(काष्ठा sk_buff *skb, पूर्णांक mtu)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा icmphdr *icmph;
	काष्ठा iphdr *niph;
	काष्ठा ethhdr eh;
	पूर्णांक len, err;

	अगर (!pskb_may_pull(skb, ETH_HLEN + माप(काष्ठा iphdr)))
		वापस -EINVAL;

	skb_copy_bits(skb, skb_mac_offset(skb), &eh, ETH_HLEN);
	pskb_pull(skb, ETH_HLEN);
	skb_reset_network_header(skb);

	err = pskb_trim(skb, 576 - माप(*niph) - माप(*icmph));
	अगर (err)
		वापस err;

	len = skb->len + माप(*icmph);
	err = skb_cow(skb, माप(*niph) + माप(*icmph) + ETH_HLEN);
	अगर (err)
		वापस err;

	icmph = skb_push(skb, माप(*icmph));
	*icmph = (काष्ठा icmphdr) अणु
		.type			= ICMP_DEST_UNREACH,
		.code			= ICMP_FRAG_NEEDED,
		.checksum		= 0,
		.un.frag.__unused	= 0,
		.un.frag.mtu		= htons(mtu),
	पूर्ण;
	icmph->checksum = ip_compute_csum(icmph, len);
	skb_reset_transport_header(skb);

	niph = skb_push(skb, माप(*niph));
	*niph = (काष्ठा iphdr) अणु
		.ihl			= माप(*niph) / 4u,
		.version 		= 4,
		.tos 			= 0,
		.tot_len		= htons(len + माप(*niph)),
		.id			= 0,
		.frag_off		= htons(IP_DF),
		.ttl			= iph->ttl,
		.protocol		= IPPROTO_ICMP,
		.saddr			= iph->daddr,
		.daddr			= iph->saddr,
	पूर्ण;
	ip_send_check(niph);
	skb_reset_network_header(skb);

	skb->ip_summed = CHECKSUM_NONE;

	eth_header(skb, skb->dev, ntohs(eh.h_proto), eh.h_source, eh.h_dest, 0);
	skb_reset_mac_header(skb);

	वापस skb->len;
पूर्ण

/**
 * iptunnel_pmtud_check_icmp() - Trigger ICMP reply अगर needed and allowed
 * @skb:	Buffer being sent by encapsulation, L2 headers expected
 * @mtu:	Network MTU क्रम path
 *
 * Return: 0 क्रम no ICMP reply, length अगर built, negative value on error.
 */
अटल पूर्णांक iptunnel_pmtud_check_icmp(काष्ठा sk_buff *skb, पूर्णांक mtu)
अणु
	स्थिर काष्ठा icmphdr *icmph = icmp_hdr(skb);
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);

	अगर (mtu < 576 || iph->frag_off != htons(IP_DF))
		वापस 0;

	अगर (ipv4_is_lbcast(iph->daddr)  || ipv4_is_multicast(iph->daddr) ||
	    ipv4_is_zeronet(iph->saddr) || ipv4_is_loopback(iph->saddr)  ||
	    ipv4_is_lbcast(iph->saddr)  || ipv4_is_multicast(iph->saddr))
		वापस 0;

	अगर (iph->protocol == IPPROTO_ICMP && icmp_is_err(icmph->type))
		वापस 0;

	वापस iptunnel_pmtud_build_icmp(skb, mtu);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
/**
 * iptunnel_pmtud_build_icmpv6() - Build ICMPv6 error message क्रम PMTUD
 * @skb:	Original packet with L2 header
 * @mtu:	MTU value क्रम ICMPv6 error
 *
 * Return: length on success, negative error code अगर message couldn't be built.
 */
अटल पूर्णांक iptunnel_pmtud_build_icmpv6(काष्ठा sk_buff *skb, पूर्णांक mtu)
अणु
	स्थिर काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);
	काष्ठा icmp6hdr *icmp6h;
	काष्ठा ipv6hdr *nip6h;
	काष्ठा ethhdr eh;
	पूर्णांक len, err;
	__wsum csum;

	अगर (!pskb_may_pull(skb, ETH_HLEN + माप(काष्ठा ipv6hdr)))
		वापस -EINVAL;

	skb_copy_bits(skb, skb_mac_offset(skb), &eh, ETH_HLEN);
	pskb_pull(skb, ETH_HLEN);
	skb_reset_network_header(skb);

	err = pskb_trim(skb, IPV6_MIN_MTU - माप(*nip6h) - माप(*icmp6h));
	अगर (err)
		वापस err;

	len = skb->len + माप(*icmp6h);
	err = skb_cow(skb, माप(*nip6h) + माप(*icmp6h) + ETH_HLEN);
	अगर (err)
		वापस err;

	icmp6h = skb_push(skb, माप(*icmp6h));
	*icmp6h = (काष्ठा icmp6hdr) अणु
		.icmp6_type		= ICMPV6_PKT_TOOBIG,
		.icmp6_code		= 0,
		.icmp6_cksum		= 0,
		.icmp6_mtu		= htonl(mtu),
	पूर्ण;
	skb_reset_transport_header(skb);

	nip6h = skb_push(skb, माप(*nip6h));
	*nip6h = (काष्ठा ipv6hdr) अणु
		.priority		= 0,
		.version		= 6,
		.flow_lbl		= अणु 0 पूर्ण,
		.payload_len		= htons(len),
		.nexthdr		= IPPROTO_ICMPV6,
		.hop_limit		= ip6h->hop_limit,
		.saddr			= ip6h->daddr,
		.daddr			= ip6h->saddr,
	पूर्ण;
	skb_reset_network_header(skb);

	csum = csum_partial(icmp6h, len, 0);
	icmp6h->icmp6_cksum = csum_ipv6_magic(&nip6h->saddr, &nip6h->daddr, len,
					      IPPROTO_ICMPV6, csum);

	skb->ip_summed = CHECKSUM_NONE;

	eth_header(skb, skb->dev, ntohs(eh.h_proto), eh.h_source, eh.h_dest, 0);
	skb_reset_mac_header(skb);

	वापस skb->len;
पूर्ण

/**
 * iptunnel_pmtud_check_icmpv6() - Trigger ICMPv6 reply अगर needed and allowed
 * @skb:	Buffer being sent by encapsulation, L2 headers expected
 * @mtu:	Network MTU क्रम path
 *
 * Return: 0 क्रम no ICMPv6 reply, length अगर built, negative value on error.
 */
अटल पूर्णांक iptunnel_pmtud_check_icmpv6(काष्ठा sk_buff *skb, पूर्णांक mtu)
अणु
	स्थिर काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);
	पूर्णांक stype = ipv6_addr_type(&ip6h->saddr);
	u8 proto = ip6h->nexthdr;
	__be16 frag_off;
	पूर्णांक offset;

	अगर (mtu < IPV6_MIN_MTU)
		वापस 0;

	अगर (stype == IPV6_ADDR_ANY || stype == IPV6_ADDR_MULTICAST ||
	    stype == IPV6_ADDR_LOOPBACK)
		वापस 0;

	offset = ipv6_skip_exthdr(skb, माप(काष्ठा ipv6hdr), &proto,
				  &frag_off);
	अगर (offset < 0 || (frag_off & htons(~0x7)))
		वापस 0;

	अगर (proto == IPPROTO_ICMPV6) अणु
		काष्ठा icmp6hdr *icmp6h;

		अगर (!pskb_may_pull(skb, skb_network_header(skb) +
					offset + 1 - skb->data))
			वापस 0;

		icmp6h = (काष्ठा icmp6hdr *)(skb_network_header(skb) + offset);
		अगर (icmpv6_is_err(icmp6h->icmp6_type) ||
		    icmp6h->icmp6_type == NDISC_REसूचीECT)
			वापस 0;
	पूर्ण

	वापस iptunnel_pmtud_build_icmpv6(skb, mtu);
पूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_IPV6) */

/**
 * skb_tunnel_check_pmtu() - Check, update PMTU and trigger ICMP reply as needed
 * @skb:	Buffer being sent by encapsulation, L2 headers expected
 * @encap_dst:	Destination क्रम tunnel encapsulation (outer IP)
 * @headroom:	Encapsulation header size, bytes
 * @reply:	Build matching ICMP or ICMPv6 message as a result
 *
 * L2 tunnel implementations that can carry IP and can be directly bridged
 * (currently UDP tunnels) can't always rely on IP क्रमwarding paths to handle
 * PMTU discovery. In the bridged हाल, ICMP or ICMPv6 messages need to be built
 * based on payload and sent back by the encapsulation itself.
 *
 * For routable पूर्णांकerfaces, we just need to update the PMTU क्रम the destination.
 *
 * Return: 0 अगर ICMP error not needed, length अगर built, negative value on error
 */
पूर्णांक skb_tunnel_check_pmtu(काष्ठा sk_buff *skb, काष्ठा dst_entry *encap_dst,
			  पूर्णांक headroom, bool reply)
अणु
	u32 mtu = dst_mtu(encap_dst) - headroom;

	अगर ((skb_is_gso(skb) && skb_gso_validate_network_len(skb, mtu)) ||
	    (!skb_is_gso(skb) && (skb->len - skb_mac_header_len(skb)) <= mtu))
		वापस 0;

	skb_dst_update_pmtu_no_confirm(skb, mtu);

	अगर (!reply || skb->pkt_type == PACKET_HOST)
		वापस 0;

	अगर (skb->protocol == htons(ETH_P_IP))
		वापस iptunnel_pmtud_check_icmp(skb, mtu);

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (skb->protocol == htons(ETH_P_IPV6))
		वापस iptunnel_pmtud_check_icmpv6(skb, mtu);
#पूर्ण_अगर
	वापस 0;
पूर्ण
EXPORT_SYMBOL(skb_tunnel_check_pmtu);

अटल स्थिर काष्ठा nla_policy ip_tun_policy[LWTUNNEL_IP_MAX + 1] = अणु
	[LWTUNNEL_IP_UNSPEC]	= अणु .strict_start_type = LWTUNNEL_IP_OPTS पूर्ण,
	[LWTUNNEL_IP_ID]	= अणु .type = NLA_U64 पूर्ण,
	[LWTUNNEL_IP_DST]	= अणु .type = NLA_U32 पूर्ण,
	[LWTUNNEL_IP_SRC]	= अणु .type = NLA_U32 पूर्ण,
	[LWTUNNEL_IP_TTL]	= अणु .type = NLA_U8 पूर्ण,
	[LWTUNNEL_IP_TOS]	= अणु .type = NLA_U8 पूर्ण,
	[LWTUNNEL_IP_FLAGS]	= अणु .type = NLA_U16 पूर्ण,
	[LWTUNNEL_IP_OPTS]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy ip_opts_policy[LWTUNNEL_IP_OPTS_MAX + 1] = अणु
	[LWTUNNEL_IP_OPTS_GENEVE]	= अणु .type = NLA_NESTED पूर्ण,
	[LWTUNNEL_IP_OPTS_VXLAN]	= अणु .type = NLA_NESTED पूर्ण,
	[LWTUNNEL_IP_OPTS_ERSPAN]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
geneve_opt_policy[LWTUNNEL_IP_OPT_GENEVE_MAX + 1] = अणु
	[LWTUNNEL_IP_OPT_GENEVE_CLASS]	= अणु .type = NLA_U16 पूर्ण,
	[LWTUNNEL_IP_OPT_GENEVE_TYPE]	= अणु .type = NLA_U8 पूर्ण,
	[LWTUNNEL_IP_OPT_GENEVE_DATA]	= अणु .type = NLA_BINARY, .len = 128 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
vxlan_opt_policy[LWTUNNEL_IP_OPT_VXLAN_MAX + 1] = अणु
	[LWTUNNEL_IP_OPT_VXLAN_GBP]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
erspan_opt_policy[LWTUNNEL_IP_OPT_ERSPAN_MAX + 1] = अणु
	[LWTUNNEL_IP_OPT_ERSPAN_VER]	= अणु .type = NLA_U8 पूर्ण,
	[LWTUNNEL_IP_OPT_ERSPAN_INDEX]	= अणु .type = NLA_U32 पूर्ण,
	[LWTUNNEL_IP_OPT_ERSPAN_सूची]	= अणु .type = NLA_U8 पूर्ण,
	[LWTUNNEL_IP_OPT_ERSPAN_HWID]	= अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल पूर्णांक ip_tun_parse_opts_geneve(काष्ठा nlattr *attr,
				    काष्ठा ip_tunnel_info *info, पूर्णांक opts_len,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[LWTUNNEL_IP_OPT_GENEVE_MAX + 1];
	पूर्णांक data_len, err;

	err = nla_parse_nested(tb, LWTUNNEL_IP_OPT_GENEVE_MAX, attr,
			       geneve_opt_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[LWTUNNEL_IP_OPT_GENEVE_CLASS] ||
	    !tb[LWTUNNEL_IP_OPT_GENEVE_TYPE] ||
	    !tb[LWTUNNEL_IP_OPT_GENEVE_DATA])
		वापस -EINVAL;

	attr = tb[LWTUNNEL_IP_OPT_GENEVE_DATA];
	data_len = nla_len(attr);
	अगर (data_len % 4)
		वापस -EINVAL;

	अगर (info) अणु
		काष्ठा geneve_opt *opt = ip_tunnel_info_opts(info) + opts_len;

		स_नकल(opt->opt_data, nla_data(attr), data_len);
		opt->length = data_len / 4;
		attr = tb[LWTUNNEL_IP_OPT_GENEVE_CLASS];
		opt->opt_class = nla_get_be16(attr);
		attr = tb[LWTUNNEL_IP_OPT_GENEVE_TYPE];
		opt->type = nla_get_u8(attr);
		info->key.tun_flags |= TUNNEL_GENEVE_OPT;
	पूर्ण

	वापस माप(काष्ठा geneve_opt) + data_len;
पूर्ण

अटल पूर्णांक ip_tun_parse_opts_vxlan(काष्ठा nlattr *attr,
				   काष्ठा ip_tunnel_info *info, पूर्णांक opts_len,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[LWTUNNEL_IP_OPT_VXLAN_MAX + 1];
	पूर्णांक err;

	err = nla_parse_nested(tb, LWTUNNEL_IP_OPT_VXLAN_MAX, attr,
			       vxlan_opt_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[LWTUNNEL_IP_OPT_VXLAN_GBP])
		वापस -EINVAL;

	अगर (info) अणु
		काष्ठा vxlan_metadata *md =
			ip_tunnel_info_opts(info) + opts_len;

		attr = tb[LWTUNNEL_IP_OPT_VXLAN_GBP];
		md->gbp = nla_get_u32(attr);
		md->gbp &= VXLAN_GBP_MASK;
		info->key.tun_flags |= TUNNEL_VXLAN_OPT;
	पूर्ण

	वापस माप(काष्ठा vxlan_metadata);
पूर्ण

अटल पूर्णांक ip_tun_parse_opts_erspan(काष्ठा nlattr *attr,
				    काष्ठा ip_tunnel_info *info, पूर्णांक opts_len,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[LWTUNNEL_IP_OPT_ERSPAN_MAX + 1];
	पूर्णांक err;
	u8 ver;

	err = nla_parse_nested(tb, LWTUNNEL_IP_OPT_ERSPAN_MAX, attr,
			       erspan_opt_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[LWTUNNEL_IP_OPT_ERSPAN_VER])
		वापस -EINVAL;

	ver = nla_get_u8(tb[LWTUNNEL_IP_OPT_ERSPAN_VER]);
	अगर (ver == 1) अणु
		अगर (!tb[LWTUNNEL_IP_OPT_ERSPAN_INDEX])
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (ver == 2) अणु
		अगर (!tb[LWTUNNEL_IP_OPT_ERSPAN_सूची] ||
		    !tb[LWTUNNEL_IP_OPT_ERSPAN_HWID])
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (info) अणु
		काष्ठा erspan_metadata *md =
			ip_tunnel_info_opts(info) + opts_len;

		md->version = ver;
		अगर (ver == 1) अणु
			attr = tb[LWTUNNEL_IP_OPT_ERSPAN_INDEX];
			md->u.index = nla_get_be32(attr);
		पूर्ण अन्यथा अणु
			attr = tb[LWTUNNEL_IP_OPT_ERSPAN_सूची];
			md->u.md2.dir = nla_get_u8(attr);
			attr = tb[LWTUNNEL_IP_OPT_ERSPAN_HWID];
			set_hwid(&md->u.md2, nla_get_u8(attr));
		पूर्ण

		info->key.tun_flags |= TUNNEL_ERSPAN_OPT;
	पूर्ण

	वापस माप(काष्ठा erspan_metadata);
पूर्ण

अटल पूर्णांक ip_tun_parse_opts(काष्ठा nlattr *attr, काष्ठा ip_tunnel_info *info,
			     काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err, rem, opt_len, opts_len = 0;
	काष्ठा nlattr *nla;
	__be16 type = 0;

	अगर (!attr)
		वापस 0;

	err = nla_validate(nla_data(attr), nla_len(attr), LWTUNNEL_IP_OPTS_MAX,
			   ip_opts_policy, extack);
	अगर (err)
		वापस err;

	nla_क्रम_each_attr(nla, nla_data(attr), nla_len(attr), rem) अणु
		चयन (nla_type(nla)) अणु
		हाल LWTUNNEL_IP_OPTS_GENEVE:
			अगर (type && type != TUNNEL_GENEVE_OPT)
				वापस -EINVAL;
			opt_len = ip_tun_parse_opts_geneve(nla, info, opts_len,
							   extack);
			अगर (opt_len < 0)
				वापस opt_len;
			opts_len += opt_len;
			अगर (opts_len > IP_TUNNEL_OPTS_MAX)
				वापस -EINVAL;
			type = TUNNEL_GENEVE_OPT;
			अवरोध;
		हाल LWTUNNEL_IP_OPTS_VXLAN:
			अगर (type)
				वापस -EINVAL;
			opt_len = ip_tun_parse_opts_vxlan(nla, info, opts_len,
							  extack);
			अगर (opt_len < 0)
				वापस opt_len;
			opts_len += opt_len;
			type = TUNNEL_VXLAN_OPT;
			अवरोध;
		हाल LWTUNNEL_IP_OPTS_ERSPAN:
			अगर (type)
				वापस -EINVAL;
			opt_len = ip_tun_parse_opts_erspan(nla, info, opts_len,
							   extack);
			अगर (opt_len < 0)
				वापस opt_len;
			opts_len += opt_len;
			type = TUNNEL_ERSPAN_OPT;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस opts_len;
पूर्ण

अटल पूर्णांक ip_tun_get_optlen(काष्ठा nlattr *attr,
			     काष्ठा netlink_ext_ack *extack)
अणु
	वापस ip_tun_parse_opts(attr, शून्य, extack);
पूर्ण

अटल पूर्णांक ip_tun_set_opts(काष्ठा nlattr *attr, काष्ठा ip_tunnel_info *info,
			   काष्ठा netlink_ext_ack *extack)
अणु
	वापस ip_tun_parse_opts(attr, info, extack);
पूर्ण

अटल पूर्णांक ip_tun_build_state(काष्ठा net *net, काष्ठा nlattr *attr,
			      अचिन्हित पूर्णांक family, स्थिर व्योम *cfg,
			      काष्ठा lwtunnel_state **ts,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[LWTUNNEL_IP_MAX + 1];
	काष्ठा lwtunnel_state *new_state;
	काष्ठा ip_tunnel_info *tun_info;
	पूर्णांक err, opt_len;

	err = nla_parse_nested_deprecated(tb, LWTUNNEL_IP_MAX, attr,
					  ip_tun_policy, extack);
	अगर (err < 0)
		वापस err;

	opt_len = ip_tun_get_optlen(tb[LWTUNNEL_IP_OPTS], extack);
	अगर (opt_len < 0)
		वापस opt_len;

	new_state = lwtunnel_state_alloc(माप(*tun_info) + opt_len);
	अगर (!new_state)
		वापस -ENOMEM;

	new_state->type = LWTUNNEL_ENCAP_IP;

	tun_info = lwt_tun_info(new_state);

	err = ip_tun_set_opts(tb[LWTUNNEL_IP_OPTS], tun_info, extack);
	अगर (err < 0) अणु
		lwtstate_मुक्त(new_state);
		वापस err;
	पूर्ण

#अगर_घोषित CONFIG_DST_CACHE
	err = dst_cache_init(&tun_info->dst_cache, GFP_KERNEL);
	अगर (err) अणु
		lwtstate_मुक्त(new_state);
		वापस err;
	पूर्ण
#पूर्ण_अगर

	अगर (tb[LWTUNNEL_IP_ID])
		tun_info->key.tun_id = nla_get_be64(tb[LWTUNNEL_IP_ID]);

	अगर (tb[LWTUNNEL_IP_DST])
		tun_info->key.u.ipv4.dst = nla_get_in_addr(tb[LWTUNNEL_IP_DST]);

	अगर (tb[LWTUNNEL_IP_SRC])
		tun_info->key.u.ipv4.src = nla_get_in_addr(tb[LWTUNNEL_IP_SRC]);

	अगर (tb[LWTUNNEL_IP_TTL])
		tun_info->key.ttl = nla_get_u8(tb[LWTUNNEL_IP_TTL]);

	अगर (tb[LWTUNNEL_IP_TOS])
		tun_info->key.tos = nla_get_u8(tb[LWTUNNEL_IP_TOS]);

	अगर (tb[LWTUNNEL_IP_FLAGS])
		tun_info->key.tun_flags |=
				(nla_get_be16(tb[LWTUNNEL_IP_FLAGS]) &
				 ~TUNNEL_OPTIONS_PRESENT);

	tun_info->mode = IP_TUNNEL_INFO_TX;
	tun_info->options_len = opt_len;

	*ts = new_state;

	वापस 0;
पूर्ण

अटल व्योम ip_tun_destroy_state(काष्ठा lwtunnel_state *lwtstate)
अणु
#अगर_घोषित CONFIG_DST_CACHE
	काष्ठा ip_tunnel_info *tun_info = lwt_tun_info(lwtstate);

	dst_cache_destroy(&tun_info->dst_cache);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक ip_tun_fill_encap_opts_geneve(काष्ठा sk_buff *skb,
					 काष्ठा ip_tunnel_info *tun_info)
अणु
	काष्ठा geneve_opt *opt;
	काष्ठा nlattr *nest;
	पूर्णांक offset = 0;

	nest = nla_nest_start_noflag(skb, LWTUNNEL_IP_OPTS_GENEVE);
	अगर (!nest)
		वापस -ENOMEM;

	जबतक (tun_info->options_len > offset) अणु
		opt = ip_tunnel_info_opts(tun_info) + offset;
		अगर (nla_put_be16(skb, LWTUNNEL_IP_OPT_GENEVE_CLASS,
				 opt->opt_class) ||
		    nla_put_u8(skb, LWTUNNEL_IP_OPT_GENEVE_TYPE, opt->type) ||
		    nla_put(skb, LWTUNNEL_IP_OPT_GENEVE_DATA, opt->length * 4,
			    opt->opt_data)) अणु
			nla_nest_cancel(skb, nest);
			वापस -ENOMEM;
		पूर्ण
		offset += माप(*opt) + opt->length * 4;
	पूर्ण

	nla_nest_end(skb, nest);
	वापस 0;
पूर्ण

अटल पूर्णांक ip_tun_fill_encap_opts_vxlan(काष्ठा sk_buff *skb,
					काष्ठा ip_tunnel_info *tun_info)
अणु
	काष्ठा vxlan_metadata *md;
	काष्ठा nlattr *nest;

	nest = nla_nest_start_noflag(skb, LWTUNNEL_IP_OPTS_VXLAN);
	अगर (!nest)
		वापस -ENOMEM;

	md = ip_tunnel_info_opts(tun_info);
	अगर (nla_put_u32(skb, LWTUNNEL_IP_OPT_VXLAN_GBP, md->gbp)) अणु
		nla_nest_cancel(skb, nest);
		वापस -ENOMEM;
	पूर्ण

	nla_nest_end(skb, nest);
	वापस 0;
पूर्ण

अटल पूर्णांक ip_tun_fill_encap_opts_erspan(काष्ठा sk_buff *skb,
					 काष्ठा ip_tunnel_info *tun_info)
अणु
	काष्ठा erspan_metadata *md;
	काष्ठा nlattr *nest;

	nest = nla_nest_start_noflag(skb, LWTUNNEL_IP_OPTS_ERSPAN);
	अगर (!nest)
		वापस -ENOMEM;

	md = ip_tunnel_info_opts(tun_info);
	अगर (nla_put_u8(skb, LWTUNNEL_IP_OPT_ERSPAN_VER, md->version))
		जाओ err;

	अगर (md->version == 1 &&
	    nla_put_be32(skb, LWTUNNEL_IP_OPT_ERSPAN_INDEX, md->u.index))
		जाओ err;

	अगर (md->version == 2 &&
	    (nla_put_u8(skb, LWTUNNEL_IP_OPT_ERSPAN_सूची, md->u.md2.dir) ||
	     nla_put_u8(skb, LWTUNNEL_IP_OPT_ERSPAN_HWID,
			get_hwid(&md->u.md2))))
		जाओ err;

	nla_nest_end(skb, nest);
	वापस 0;
err:
	nla_nest_cancel(skb, nest);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक ip_tun_fill_encap_opts(काष्ठा sk_buff *skb, पूर्णांक type,
				  काष्ठा ip_tunnel_info *tun_info)
अणु
	काष्ठा nlattr *nest;
	पूर्णांक err = 0;

	अगर (!(tun_info->key.tun_flags & TUNNEL_OPTIONS_PRESENT))
		वापस 0;

	nest = nla_nest_start_noflag(skb, type);
	अगर (!nest)
		वापस -ENOMEM;

	अगर (tun_info->key.tun_flags & TUNNEL_GENEVE_OPT)
		err = ip_tun_fill_encap_opts_geneve(skb, tun_info);
	अन्यथा अगर (tun_info->key.tun_flags & TUNNEL_VXLAN_OPT)
		err = ip_tun_fill_encap_opts_vxlan(skb, tun_info);
	अन्यथा अगर (tun_info->key.tun_flags & TUNNEL_ERSPAN_OPT)
		err = ip_tun_fill_encap_opts_erspan(skb, tun_info);

	अगर (err) अणु
		nla_nest_cancel(skb, nest);
		वापस err;
	पूर्ण

	nla_nest_end(skb, nest);
	वापस 0;
पूर्ण

अटल पूर्णांक ip_tun_fill_encap_info(काष्ठा sk_buff *skb,
				  काष्ठा lwtunnel_state *lwtstate)
अणु
	काष्ठा ip_tunnel_info *tun_info = lwt_tun_info(lwtstate);

	अगर (nla_put_be64(skb, LWTUNNEL_IP_ID, tun_info->key.tun_id,
			 LWTUNNEL_IP_PAD) ||
	    nla_put_in_addr(skb, LWTUNNEL_IP_DST, tun_info->key.u.ipv4.dst) ||
	    nla_put_in_addr(skb, LWTUNNEL_IP_SRC, tun_info->key.u.ipv4.src) ||
	    nla_put_u8(skb, LWTUNNEL_IP_TOS, tun_info->key.tos) ||
	    nla_put_u8(skb, LWTUNNEL_IP_TTL, tun_info->key.ttl) ||
	    nla_put_be16(skb, LWTUNNEL_IP_FLAGS, tun_info->key.tun_flags) ||
	    ip_tun_fill_encap_opts(skb, LWTUNNEL_IP_OPTS, tun_info))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक ip_tun_opts_nlsize(काष्ठा ip_tunnel_info *info)
अणु
	पूर्णांक opt_len;

	अगर (!(info->key.tun_flags & TUNNEL_OPTIONS_PRESENT))
		वापस 0;

	opt_len = nla_total_size(0);		/* LWTUNNEL_IP_OPTS */
	अगर (info->key.tun_flags & TUNNEL_GENEVE_OPT) अणु
		काष्ठा geneve_opt *opt;
		पूर्णांक offset = 0;

		opt_len += nla_total_size(0);	/* LWTUNNEL_IP_OPTS_GENEVE */
		जबतक (info->options_len > offset) अणु
			opt = ip_tunnel_info_opts(info) + offset;
			opt_len += nla_total_size(2)	/* OPT_GENEVE_CLASS */
				   + nla_total_size(1)	/* OPT_GENEVE_TYPE */
				   + nla_total_size(opt->length * 4);
							/* OPT_GENEVE_DATA */
			offset += माप(*opt) + opt->length * 4;
		पूर्ण
	पूर्ण अन्यथा अगर (info->key.tun_flags & TUNNEL_VXLAN_OPT) अणु
		opt_len += nla_total_size(0)	/* LWTUNNEL_IP_OPTS_VXLAN */
			   + nla_total_size(4);	/* OPT_VXLAN_GBP */
	पूर्ण अन्यथा अगर (info->key.tun_flags & TUNNEL_ERSPAN_OPT) अणु
		काष्ठा erspan_metadata *md = ip_tunnel_info_opts(info);

		opt_len += nla_total_size(0)	/* LWTUNNEL_IP_OPTS_ERSPAN */
			   + nla_total_size(1)	/* OPT_ERSPAN_VER */
			   + (md->version == 1 ? nla_total_size(4)
						/* OPT_ERSPAN_INDEX (v1) */
					       : nla_total_size(1) +
						 nla_total_size(1));
						/* OPT_ERSPAN_सूची + HWID (v2) */
	पूर्ण

	वापस opt_len;
पूर्ण

अटल पूर्णांक ip_tun_encap_nlsize(काष्ठा lwtunnel_state *lwtstate)
अणु
	वापस nla_total_size_64bit(8)	/* LWTUNNEL_IP_ID */
		+ nla_total_size(4)	/* LWTUNNEL_IP_DST */
		+ nla_total_size(4)	/* LWTUNNEL_IP_SRC */
		+ nla_total_size(1)	/* LWTUNNEL_IP_TOS */
		+ nla_total_size(1)	/* LWTUNNEL_IP_TTL */
		+ nla_total_size(2)	/* LWTUNNEL_IP_FLAGS */
		+ ip_tun_opts_nlsize(lwt_tun_info(lwtstate));
					/* LWTUNNEL_IP_OPTS */
पूर्ण

अटल पूर्णांक ip_tun_cmp_encap(काष्ठा lwtunnel_state *a, काष्ठा lwtunnel_state *b)
अणु
	काष्ठा ip_tunnel_info *info_a = lwt_tun_info(a);
	काष्ठा ip_tunnel_info *info_b = lwt_tun_info(b);

	वापस स_भेद(info_a, info_b, माप(info_a->key)) ||
	       info_a->mode != info_b->mode ||
	       info_a->options_len != info_b->options_len ||
	       स_भेद(ip_tunnel_info_opts(info_a),
		      ip_tunnel_info_opts(info_b), info_a->options_len);
पूर्ण

अटल स्थिर काष्ठा lwtunnel_encap_ops ip_tun_lwt_ops = अणु
	.build_state = ip_tun_build_state,
	.destroy_state = ip_tun_destroy_state,
	.fill_encap = ip_tun_fill_encap_info,
	.get_encap_size = ip_tun_encap_nlsize,
	.cmp_encap = ip_tun_cmp_encap,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा nla_policy ip6_tun_policy[LWTUNNEL_IP6_MAX + 1] = अणु
	[LWTUNNEL_IP6_UNSPEC]	= अणु .strict_start_type = LWTUNNEL_IP6_OPTS पूर्ण,
	[LWTUNNEL_IP6_ID]		= अणु .type = NLA_U64 पूर्ण,
	[LWTUNNEL_IP6_DST]		= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[LWTUNNEL_IP6_SRC]		= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[LWTUNNEL_IP6_HOPLIMIT]		= अणु .type = NLA_U8 पूर्ण,
	[LWTUNNEL_IP6_TC]		= अणु .type = NLA_U8 पूर्ण,
	[LWTUNNEL_IP6_FLAGS]		= अणु .type = NLA_U16 पूर्ण,
	[LWTUNNEL_IP6_OPTS]		= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक ip6_tun_build_state(काष्ठा net *net, काष्ठा nlattr *attr,
			       अचिन्हित पूर्णांक family, स्थिर व्योम *cfg,
			       काष्ठा lwtunnel_state **ts,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[LWTUNNEL_IP6_MAX + 1];
	काष्ठा lwtunnel_state *new_state;
	काष्ठा ip_tunnel_info *tun_info;
	पूर्णांक err, opt_len;

	err = nla_parse_nested_deprecated(tb, LWTUNNEL_IP6_MAX, attr,
					  ip6_tun_policy, extack);
	अगर (err < 0)
		वापस err;

	opt_len = ip_tun_get_optlen(tb[LWTUNNEL_IP6_OPTS], extack);
	अगर (opt_len < 0)
		वापस opt_len;

	new_state = lwtunnel_state_alloc(माप(*tun_info) + opt_len);
	अगर (!new_state)
		वापस -ENOMEM;

	new_state->type = LWTUNNEL_ENCAP_IP6;

	tun_info = lwt_tun_info(new_state);

	err = ip_tun_set_opts(tb[LWTUNNEL_IP6_OPTS], tun_info, extack);
	अगर (err < 0) अणु
		lwtstate_मुक्त(new_state);
		वापस err;
	पूर्ण

	अगर (tb[LWTUNNEL_IP6_ID])
		tun_info->key.tun_id = nla_get_be64(tb[LWTUNNEL_IP6_ID]);

	अगर (tb[LWTUNNEL_IP6_DST])
		tun_info->key.u.ipv6.dst = nla_get_in6_addr(tb[LWTUNNEL_IP6_DST]);

	अगर (tb[LWTUNNEL_IP6_SRC])
		tun_info->key.u.ipv6.src = nla_get_in6_addr(tb[LWTUNNEL_IP6_SRC]);

	अगर (tb[LWTUNNEL_IP6_HOPLIMIT])
		tun_info->key.ttl = nla_get_u8(tb[LWTUNNEL_IP6_HOPLIMIT]);

	अगर (tb[LWTUNNEL_IP6_TC])
		tun_info->key.tos = nla_get_u8(tb[LWTUNNEL_IP6_TC]);

	अगर (tb[LWTUNNEL_IP6_FLAGS])
		tun_info->key.tun_flags |=
				(nla_get_be16(tb[LWTUNNEL_IP6_FLAGS]) &
				 ~TUNNEL_OPTIONS_PRESENT);

	tun_info->mode = IP_TUNNEL_INFO_TX | IP_TUNNEL_INFO_IPV6;
	tun_info->options_len = opt_len;

	*ts = new_state;

	वापस 0;
पूर्ण

अटल पूर्णांक ip6_tun_fill_encap_info(काष्ठा sk_buff *skb,
				   काष्ठा lwtunnel_state *lwtstate)
अणु
	काष्ठा ip_tunnel_info *tun_info = lwt_tun_info(lwtstate);

	अगर (nla_put_be64(skb, LWTUNNEL_IP6_ID, tun_info->key.tun_id,
			 LWTUNNEL_IP6_PAD) ||
	    nla_put_in6_addr(skb, LWTUNNEL_IP6_DST, &tun_info->key.u.ipv6.dst) ||
	    nla_put_in6_addr(skb, LWTUNNEL_IP6_SRC, &tun_info->key.u.ipv6.src) ||
	    nla_put_u8(skb, LWTUNNEL_IP6_TC, tun_info->key.tos) ||
	    nla_put_u8(skb, LWTUNNEL_IP6_HOPLIMIT, tun_info->key.ttl) ||
	    nla_put_be16(skb, LWTUNNEL_IP6_FLAGS, tun_info->key.tun_flags) ||
	    ip_tun_fill_encap_opts(skb, LWTUNNEL_IP6_OPTS, tun_info))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक ip6_tun_encap_nlsize(काष्ठा lwtunnel_state *lwtstate)
अणु
	वापस nla_total_size_64bit(8)	/* LWTUNNEL_IP6_ID */
		+ nla_total_size(16)	/* LWTUNNEL_IP6_DST */
		+ nla_total_size(16)	/* LWTUNNEL_IP6_SRC */
		+ nla_total_size(1)	/* LWTUNNEL_IP6_HOPLIMIT */
		+ nla_total_size(1)	/* LWTUNNEL_IP6_TC */
		+ nla_total_size(2)	/* LWTUNNEL_IP6_FLAGS */
		+ ip_tun_opts_nlsize(lwt_tun_info(lwtstate));
					/* LWTUNNEL_IP6_OPTS */
पूर्ण

अटल स्थिर काष्ठा lwtunnel_encap_ops ip6_tun_lwt_ops = अणु
	.build_state = ip6_tun_build_state,
	.fill_encap = ip6_tun_fill_encap_info,
	.get_encap_size = ip6_tun_encap_nlsize,
	.cmp_encap = ip_tun_cmp_encap,
	.owner = THIS_MODULE,
पूर्ण;

व्योम __init ip_tunnel_core_init(व्योम)
अणु
	/* If you land here, make sure whether increasing ip_tunnel_info's
	 * options_len is a reasonable choice with its usage in front ends
	 * (f.e., it's part of flow keys, etc).
	 */
	BUILD_BUG_ON(IP_TUNNEL_OPTS_MAX != 255);

	lwtunnel_encap_add_ops(&ip_tun_lwt_ops, LWTUNNEL_ENCAP_IP);
	lwtunnel_encap_add_ops(&ip6_tun_lwt_ops, LWTUNNEL_ENCAP_IP6);
पूर्ण

DEFINE_STATIC_KEY_FALSE(ip_tunnel_metadata_cnt);
EXPORT_SYMBOL(ip_tunnel_metadata_cnt);

व्योम ip_tunnel_need_metadata(व्योम)
अणु
	अटल_branch_inc(&ip_tunnel_metadata_cnt);
पूर्ण
EXPORT_SYMBOL_GPL(ip_tunnel_need_metadata);

व्योम ip_tunnel_unneed_metadata(व्योम)
अणु
	अटल_branch_dec(&ip_tunnel_metadata_cnt);
पूर्ण
EXPORT_SYMBOL_GPL(ip_tunnel_unneed_metadata);

/* Returns either the correct skb->protocol value, or 0 अगर invalid. */
__be16 ip_tunnel_parse_protocol(स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (skb_network_header(skb) >= skb->head &&
	    (skb_network_header(skb) + माप(काष्ठा iphdr)) <= skb_tail_poपूर्णांकer(skb) &&
	    ip_hdr(skb)->version == 4)
		वापस htons(ETH_P_IP);
	अगर (skb_network_header(skb) >= skb->head &&
	    (skb_network_header(skb) + माप(काष्ठा ipv6hdr)) <= skb_tail_poपूर्णांकer(skb) &&
	    ipv6_hdr(skb)->version == 6)
		वापस htons(ETH_P_IPV6);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ip_tunnel_parse_protocol);

स्थिर काष्ठा header_ops ip_tunnel_header_ops = अणु .parse_protocol = ip_tunnel_parse_protocol पूर्ण;
EXPORT_SYMBOL(ip_tunnel_header_ops);
