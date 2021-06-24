<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		The IP क्रमwarding functionality.
 *
 * Authors:	see ip.c
 *
 * Fixes:
 *		Many		:	Split from ip.c , see ip_input.c क्रम
 *					history.
 *		Dave Gregorich	:	शून्य ip_rt_put fix क्रम multicast
 *					routing.
 *		Jos Vos		:	Add call_out_firewall beक्रमe sending,
 *					use output device क्रम accounting.
 *		Jos Vos		:	Call क्रमward firewall after routing
 *					(always use output device).
 *		Mike McLagan	:	Routing by source
 */

#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <linux/icmp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <net/ip.h>
#समावेश <net/tcp.h>
#समावेश <net/udp.h>
#समावेश <net/icmp.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <net/checksum.h>
#समावेश <linux/route.h>
#समावेश <net/route.h>
#समावेश <net/xfrm.h>

अटल bool ip_exceeds_mtu(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक mtu)
अणु
	अगर (skb->len <= mtu)
		वापस false;

	अगर (unlikely((ip_hdr(skb)->frag_off & htons(IP_DF)) == 0))
		वापस false;

	/* original fragment exceeds mtu and DF is set */
	अगर (unlikely(IPCB(skb)->frag_max_size > mtu))
		वापस true;

	अगर (skb->ignore_df)
		वापस false;

	अगर (skb_is_gso(skb) && skb_gso_validate_network_len(skb, mtu))
		वापस false;

	वापस true;
पूर्ण


अटल पूर्णांक ip_क्रमward_finish(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा ip_options *opt	= &(IPCB(skb)->opt);

	__IP_INC_STATS(net, IPSTATS_MIB_OUTFORWDATAGRAMS);
	__IP_ADD_STATS(net, IPSTATS_MIB_OUTOCTETS, skb->len);

#अगर_घोषित CONFIG_NET_SWITCHDEV
	अगर (skb->offload_l3_fwd_mark) अणु
		consume_skb(skb);
		वापस 0;
	पूर्ण
#पूर्ण_अगर

	अगर (unlikely(opt->optlen))
		ip_क्रमward_options(skb);

	skb->tstamp = 0;
	वापस dst_output(net, sk, skb);
पूर्ण

पूर्णांक ip_क्रमward(काष्ठा sk_buff *skb)
अणु
	u32 mtu;
	काष्ठा iphdr *iph;	/* Our header */
	काष्ठा rtable *rt;	/* Route we use */
	काष्ठा ip_options *opt	= &(IPCB(skb)->opt);
	काष्ठा net *net;

	/* that should never happen */
	अगर (skb->pkt_type != PACKET_HOST)
		जाओ drop;

	अगर (unlikely(skb->sk))
		जाओ drop;

	अगर (skb_warn_अगर_lro(skb))
		जाओ drop;

	अगर (!xfrm4_policy_check(शून्य, XFRM_POLICY_FWD, skb))
		जाओ drop;

	अगर (IPCB(skb)->opt.router_alert && ip_call_ra_chain(skb))
		वापस NET_RX_SUCCESS;

	skb_क्रमward_csum(skb);
	net = dev_net(skb->dev);

	/*
	 *	According to the RFC, we must first decrease the TTL field. If
	 *	that reaches zero, we must reply an ICMP control message telling
	 *	that the packet's lअगरeसमय expired.
	 */
	अगर (ip_hdr(skb)->ttl <= 1)
		जाओ too_many_hops;

	अगर (!xfrm4_route_क्रमward(skb))
		जाओ drop;

	rt = skb_rtable(skb);

	अगर (opt->is_strictroute && rt->rt_uses_gateway)
		जाओ sr_failed;

	IPCB(skb)->flags |= IPSKB_FORWARDED;
	mtu = ip_dst_mtu_maybe_क्रमward(&rt->dst, true);
	अगर (ip_exceeds_mtu(skb, mtu)) अणु
		IP_INC_STATS(net, IPSTATS_MIB_FRAGFAILS);
		icmp_send(skb, ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED,
			  htonl(mtu));
		जाओ drop;
	पूर्ण

	/* We are about to mangle packet. Copy it! */
	अगर (skb_cow(skb, LL_RESERVED_SPACE(rt->dst.dev)+rt->dst.header_len))
		जाओ drop;
	iph = ip_hdr(skb);

	/* Decrease ttl after skb cow करोne */
	ip_decrease_ttl(iph);

	/*
	 *	We now generate an ICMP HOST REसूचीECT giving the route
	 *	we calculated.
	 */
	अगर (IPCB(skb)->flags & IPSKB_DOREसूचीECT && !opt->srr &&
	    !skb_sec_path(skb))
		ip_rt_send_redirect(skb);

	अगर (net->ipv4.sysctl_ip_fwd_update_priority)
		skb->priority = rt_tos2priority(iph->tos);

	वापस NF_HOOK(NFPROTO_IPV4, NF_INET_FORWARD,
		       net, शून्य, skb, skb->dev, rt->dst.dev,
		       ip_क्रमward_finish);

sr_failed:
	/*
	 *	Strict routing permits no gatewaying
	 */
	 icmp_send(skb, ICMP_DEST_UNREACH, ICMP_SR_FAILED, 0);
	 जाओ drop;

too_many_hops:
	/* Tell the sender its packet died... */
	__IP_INC_STATS(net, IPSTATS_MIB_INHDRERRORS);
	icmp_send(skb, ICMP_TIME_EXCEEDED, ICMP_EXC_TTL, 0);
drop:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण
