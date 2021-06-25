<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Linux NET3:	GRE over IP protocol decoder.
 *
 *	Authors: Alexey Kuznetsov (kuznet@ms2.inr.ac.ru)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/in.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/init.h>
#समावेश <linux/in6.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/igmp.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_ether.h>

#समावेश <net/sock.h>
#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/protocol.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/arp.h>
#समावेश <net/checksum.h>
#समावेश <net/dsfield.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/xfrm.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/gre.h>
#समावेश <net/dst_metadata.h>
#समावेश <net/erspan.h>

/*
   Problems & solutions
   --------------------

   1. The most important issue is detecting local dead loops.
   They would cause complete host lockup in transmit, which
   would be "resolved" by stack overflow or, अगर queueing is enabled,
   with infinite looping in net_bh.

   We cannot track such dead loops during route installation,
   it is infeasible task. The most general solutions would be
   to keep skb->encapsulation counter (sort of local ttl),
   and silently drop packet when it expires. It is a good
   solution, but it supposes मुख्यtaining new variable in ALL
   skb, even अगर no tunneling is used.

   Current solution: xmit_recursion अवरोधs dead loops. This is a percpu
   counter, since when we enter the first nकरो_xmit(), cpu migration is
   क्रमbidden. We क्रमce an निकास अगर this counter reaches RECURSION_LIMIT

   2. Networking dead loops would not समाप्त routers, but would really
   समाप्त network. IP hop limit plays role of "t->recursion" in this हाल,
   अगर we copy it from packet being encapsulated to upper header.
   It is very good solution, but it पूर्णांकroduces two problems:

   - Routing protocols, using packets with ttl=1 (OSPF, RIP2),
     करो not work over tunnels.
   - traceroute करोes not work. I planned to relay ICMP from tunnel,
     so that this problem would be solved and traceroute output
     would even more inक्रमmative. This idea appeared to be wrong:
     only Linux complies to rfc1812 now (yes, guys, Linux is the only
     true router now :-)), all routers (at least, in neighbourhood of mine)
     वापस only 8 bytes of payload. It is the end.

   Hence, अगर we want that OSPF worked or traceroute said something reasonable,
   we should search क्रम another solution.

   One of them is to parse packet trying to detect inner encapsulation
   made by our node. It is dअगरficult or even impossible, especially,
   taking पूर्णांकo account fragmentation. TO be लघु, ttl is not solution at all.

   Current solution: The solution was UNEXPECTEDLY SIMPLE.
   We क्रमce DF flag on tunnels with preconfigured hop limit,
   that is ALL. :-) Well, it करोes not हटाओ the problem completely,
   but exponential growth of network traffic is changed to linear
   (branches, that exceed pmtu are pruned) and tunnel mtu
   rapidly degrades to value <68, where looping stops.
   Yes, it is not good अगर there exists a router in the loop,
   which करोes not क्रमce DF, even when encapsulating packets have DF set.
   But it is not our problem! Nobody could accuse us, we made
   all that we could make. Even अगर it is your gated who injected
   fatal route to network, even अगर it were you who configured
   fatal अटल route: you are innocent. :-)

   Alexey Kuznetsov.
 */

अटल bool log_ecn_error = true;
module_param(log_ecn_error, bool, 0644);
MODULE_PARM_DESC(log_ecn_error, "Log packets received with corrupted ECN");

अटल काष्ठा rtnl_link_ops ipgre_link_ops __पढ़ो_mostly;
अटल पूर्णांक ipgre_tunnel_init(काष्ठा net_device *dev);
अटल व्योम erspan_build_header(काष्ठा sk_buff *skb,
				u32 id, u32 index,
				bool truncate, bool is_ipv4);

अटल अचिन्हित पूर्णांक ipgre_net_id __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक gre_tap_net_id __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक erspan_net_id __पढ़ो_mostly;

अटल पूर्णांक ipgre_err(काष्ठा sk_buff *skb, u32 info,
		     स्थिर काष्ठा tnl_ptk_info *tpi)
अणु

	/* All the routers (except क्रम Linux) वापस only
	   8 bytes of packet payload. It means, that precise relaying of
	   ICMP in the real Internet is असलolutely infeasible.

	   Moreover, Cisco "wise men" put GRE key to the third word
	   in GRE header. It makes impossible मुख्यtaining even soft
	   state क्रम keyed GRE tunnels with enabled checksum. Tell
	   them "thank you".

	   Well, I wonder, rfc1812 was written by Cisco employee,
	   what the hell these idiots अवरोध standards established
	   by themselves???
	   */
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा ip_tunnel_net *itn;
	स्थिर काष्ठा iphdr *iph;
	स्थिर पूर्णांक type = icmp_hdr(skb)->type;
	स्थिर पूर्णांक code = icmp_hdr(skb)->code;
	अचिन्हित पूर्णांक data_len = 0;
	काष्ठा ip_tunnel *t;

	अगर (tpi->proto == htons(ETH_P_TEB))
		itn = net_generic(net, gre_tap_net_id);
	अन्यथा अगर (tpi->proto == htons(ETH_P_ERSPAN) ||
		 tpi->proto == htons(ETH_P_ERSPAN2))
		itn = net_generic(net, erspan_net_id);
	अन्यथा
		itn = net_generic(net, ipgre_net_id);

	iph = (स्थिर काष्ठा iphdr *)(icmp_hdr(skb) + 1);
	t = ip_tunnel_lookup(itn, skb->dev->अगरindex, tpi->flags,
			     iph->daddr, iph->saddr, tpi->key);

	अगर (!t)
		वापस -ENOENT;

	चयन (type) अणु
	शेष:
	हाल ICMP_PARAMETERPROB:
		वापस 0;

	हाल ICMP_DEST_UNREACH:
		चयन (code) अणु
		हाल ICMP_SR_FAILED:
		हाल ICMP_PORT_UNREACH:
			/* Impossible event. */
			वापस 0;
		शेष:
			/* All others are translated to HOST_UNREACH.
			   rfc2003 contains "deep thoughts" about NET_UNREACH,
			   I believe they are just ether pollution. --ANK
			 */
			अवरोध;
		पूर्ण
		अवरोध;

	हाल ICMP_TIME_EXCEEDED:
		अगर (code != ICMP_EXC_TTL)
			वापस 0;
		data_len = icmp_hdr(skb)->un.reserved[1] * 4; /* RFC 4884 4.1 */
		अवरोध;

	हाल ICMP_REसूचीECT:
		अवरोध;
	पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
       अगर (tpi->proto == htons(ETH_P_IPV6) &&
           !ip6_err_gen_icmpv6_unreach(skb, iph->ihl * 4 + tpi->hdr_len,
				       type, data_len))
               वापस 0;
#पूर्ण_अगर

	अगर (t->parms.iph.daddr == 0 ||
	    ipv4_is_multicast(t->parms.iph.daddr))
		वापस 0;

	अगर (t->parms.iph.ttl == 0 && type == ICMP_TIME_EXCEEDED)
		वापस 0;

	अगर (समय_beक्रमe(jअगरfies, t->err_समय + IPTUNNEL_ERR_TIMEO))
		t->err_count++;
	अन्यथा
		t->err_count = 1;
	t->err_समय = jअगरfies;

	वापस 0;
पूर्ण

अटल व्योम gre_err(काष्ठा sk_buff *skb, u32 info)
अणु
	/* All the routers (except क्रम Linux) वापस only
	 * 8 bytes of packet payload. It means, that precise relaying of
	 * ICMP in the real Internet is असलolutely infeasible.
	 *
	 * Moreover, Cisco "wise men" put GRE key to the third word
	 * in GRE header. It makes impossible मुख्यtaining even soft
	 * state क्रम keyed
	 * GRE tunnels with enabled checksum. Tell them "thank you".
	 *
	 * Well, I wonder, rfc1812 was written by Cisco employee,
	 * what the hell these idiots अवरोध standards established
	 * by themselves???
	 */

	स्थिर काष्ठा iphdr *iph = (काष्ठा iphdr *)skb->data;
	स्थिर पूर्णांक type = icmp_hdr(skb)->type;
	स्थिर पूर्णांक code = icmp_hdr(skb)->code;
	काष्ठा tnl_ptk_info tpi;

	अगर (gre_parse_header(skb, &tpi, शून्य, htons(ETH_P_IP),
			     iph->ihl * 4) < 0)
		वापस;

	अगर (type == ICMP_DEST_UNREACH && code == ICMP_FRAG_NEEDED) अणु
		ipv4_update_pmtu(skb, dev_net(skb->dev), info,
				 skb->dev->अगरindex, IPPROTO_GRE);
		वापस;
	पूर्ण
	अगर (type == ICMP_REसूचीECT) अणु
		ipv4_redirect(skb, dev_net(skb->dev), skb->dev->अगरindex,
			      IPPROTO_GRE);
		वापस;
	पूर्ण

	ipgre_err(skb, info, &tpi);
पूर्ण

अटल bool is_erspan_type1(पूर्णांक gre_hdr_len)
अणु
	/* Both ERSPAN type I (version 0) and type II (version 1) use
	 * protocol 0x88BE, but the type I has only 4-byte GRE header,
	 * जबतक type II has 8-byte.
	 */
	वापस gre_hdr_len == 4;
पूर्ण

अटल पूर्णांक erspan_rcv(काष्ठा sk_buff *skb, काष्ठा tnl_ptk_info *tpi,
		      पूर्णांक gre_hdr_len)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा metadata_dst *tun_dst = शून्य;
	काष्ठा erspan_base_hdr *ershdr;
	काष्ठा ip_tunnel_net *itn;
	काष्ठा ip_tunnel *tunnel;
	स्थिर काष्ठा iphdr *iph;
	काष्ठा erspan_md2 *md2;
	पूर्णांक ver;
	पूर्णांक len;

	itn = net_generic(net, erspan_net_id);
	iph = ip_hdr(skb);
	अगर (is_erspan_type1(gre_hdr_len)) अणु
		ver = 0;
		tunnel = ip_tunnel_lookup(itn, skb->dev->अगरindex,
					  tpi->flags | TUNNEL_NO_KEY,
					  iph->saddr, iph->daddr, 0);
	पूर्ण अन्यथा अणु
		ershdr = (काष्ठा erspan_base_hdr *)(skb->data + gre_hdr_len);
		ver = ershdr->ver;
		tunnel = ip_tunnel_lookup(itn, skb->dev->अगरindex,
					  tpi->flags | TUNNEL_KEY,
					  iph->saddr, iph->daddr, tpi->key);
	पूर्ण

	अगर (tunnel) अणु
		अगर (is_erspan_type1(gre_hdr_len))
			len = gre_hdr_len;
		अन्यथा
			len = gre_hdr_len + erspan_hdr_len(ver);

		अगर (unlikely(!pskb_may_pull(skb, len)))
			वापस PACKET_REJECT;

		अगर (__iptunnel_pull_header(skb,
					   len,
					   htons(ETH_P_TEB),
					   false, false) < 0)
			जाओ drop;

		अगर (tunnel->collect_md) अणु
			काष्ठा erspan_metadata *pkt_md, *md;
			काष्ठा ip_tunnel_info *info;
			अचिन्हित अक्षर *gh;
			__be64 tun_id;
			__be16 flags;

			tpi->flags |= TUNNEL_KEY;
			flags = tpi->flags;
			tun_id = key32_to_tunnel_id(tpi->key);

			tun_dst = ip_tun_rx_dst(skb, flags,
						tun_id, माप(*md));
			अगर (!tun_dst)
				वापस PACKET_REJECT;

			/* skb can be uncloned in __iptunnel_pull_header, so
			 * old pkt_md is no दीर्घer valid and we need to reset
			 * it
			 */
			gh = skb_network_header(skb) +
			     skb_network_header_len(skb);
			pkt_md = (काष्ठा erspan_metadata *)(gh + gre_hdr_len +
							    माप(*ershdr));
			md = ip_tunnel_info_opts(&tun_dst->u.tun_info);
			md->version = ver;
			md2 = &md->u.md2;
			स_नकल(md2, pkt_md, ver == 1 ? ERSPAN_V1_MDSIZE :
						       ERSPAN_V2_MDSIZE);

			info = &tun_dst->u.tun_info;
			info->key.tun_flags |= TUNNEL_ERSPAN_OPT;
			info->options_len = माप(*md);
		पूर्ण

		skb_reset_mac_header(skb);
		ip_tunnel_rcv(tunnel, skb, tpi, tun_dst, log_ecn_error);
		वापस PACKET_RCVD;
	पूर्ण
	वापस PACKET_REJECT;

drop:
	kमुक्त_skb(skb);
	वापस PACKET_RCVD;
पूर्ण

अटल पूर्णांक __ipgre_rcv(काष्ठा sk_buff *skb, स्थिर काष्ठा tnl_ptk_info *tpi,
		       काष्ठा ip_tunnel_net *itn, पूर्णांक hdr_len, bool raw_proto)
अणु
	काष्ठा metadata_dst *tun_dst = शून्य;
	स्थिर काष्ठा iphdr *iph;
	काष्ठा ip_tunnel *tunnel;

	iph = ip_hdr(skb);
	tunnel = ip_tunnel_lookup(itn, skb->dev->अगरindex, tpi->flags,
				  iph->saddr, iph->daddr, tpi->key);

	अगर (tunnel) अणु
		स्थिर काष्ठा iphdr *tnl_params;

		अगर (__iptunnel_pull_header(skb, hdr_len, tpi->proto,
					   raw_proto, false) < 0)
			जाओ drop;

		अगर (tunnel->dev->type != ARPHRD_NONE)
			skb_pop_mac_header(skb);
		अन्यथा
			skb_reset_mac_header(skb);

		tnl_params = &tunnel->parms.iph;
		अगर (tunnel->collect_md || tnl_params->daddr == 0) अणु
			__be16 flags;
			__be64 tun_id;

			flags = tpi->flags & (TUNNEL_CSUM | TUNNEL_KEY);
			tun_id = key32_to_tunnel_id(tpi->key);
			tun_dst = ip_tun_rx_dst(skb, flags, tun_id, 0);
			अगर (!tun_dst)
				वापस PACKET_REJECT;
		पूर्ण

		ip_tunnel_rcv(tunnel, skb, tpi, tun_dst, log_ecn_error);
		वापस PACKET_RCVD;
	पूर्ण
	वापस PACKET_NEXT;

drop:
	kमुक्त_skb(skb);
	वापस PACKET_RCVD;
पूर्ण

अटल पूर्णांक ipgre_rcv(काष्ठा sk_buff *skb, स्थिर काष्ठा tnl_ptk_info *tpi,
		     पूर्णांक hdr_len)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा ip_tunnel_net *itn;
	पूर्णांक res;

	अगर (tpi->proto == htons(ETH_P_TEB))
		itn = net_generic(net, gre_tap_net_id);
	अन्यथा
		itn = net_generic(net, ipgre_net_id);

	res = __ipgre_rcv(skb, tpi, itn, hdr_len, false);
	अगर (res == PACKET_NEXT && tpi->proto == htons(ETH_P_TEB)) अणु
		/* ipgre tunnels in collect metadata mode should receive
		 * also ETH_P_TEB traffic.
		 */
		itn = net_generic(net, ipgre_net_id);
		res = __ipgre_rcv(skb, tpi, itn, hdr_len, true);
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक gre_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा tnl_ptk_info tpi;
	bool csum_err = false;
	पूर्णांक hdr_len;

#अगर_घोषित CONFIG_NET_IPGRE_BROADCAST
	अगर (ipv4_is_multicast(ip_hdr(skb)->daddr)) अणु
		/* Looped back packet, drop it! */
		अगर (rt_is_output_route(skb_rtable(skb)))
			जाओ drop;
	पूर्ण
#पूर्ण_अगर

	hdr_len = gre_parse_header(skb, &tpi, &csum_err, htons(ETH_P_IP), 0);
	अगर (hdr_len < 0)
		जाओ drop;

	अगर (unlikely(tpi.proto == htons(ETH_P_ERSPAN) ||
		     tpi.proto == htons(ETH_P_ERSPAN2))) अणु
		अगर (erspan_rcv(skb, &tpi, hdr_len) == PACKET_RCVD)
			वापस 0;
		जाओ out;
	पूर्ण

	अगर (ipgre_rcv(skb, &tpi, hdr_len) == PACKET_RCVD)
		वापस 0;

out:
	icmp_send(skb, ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, 0);
drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल व्योम __gre_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		       स्थिर काष्ठा iphdr *tnl_params,
		       __be16 proto)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);

	अगर (tunnel->parms.o_flags & TUNNEL_SEQ)
		tunnel->o_seqno++;

	/* Push GRE header. */
	gre_build_header(skb, tunnel->tun_hlen,
			 tunnel->parms.o_flags, proto, tunnel->parms.o_key,
			 htonl(tunnel->o_seqno));

	ip_tunnel_xmit(skb, dev, tnl_params, tnl_params->protocol);
पूर्ण

अटल पूर्णांक gre_handle_offloads(काष्ठा sk_buff *skb, bool csum)
अणु
	वापस iptunnel_handle_offloads(skb, csum ? SKB_GSO_GRE_CSUM : SKB_GSO_GRE);
पूर्ण

अटल व्योम gre_fb_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			__be16 proto)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	काष्ठा ip_tunnel_info *tun_info;
	स्थिर काष्ठा ip_tunnel_key *key;
	पूर्णांक tunnel_hlen;
	__be16 flags;

	tun_info = skb_tunnel_info(skb);
	अगर (unlikely(!tun_info || !(tun_info->mode & IP_TUNNEL_INFO_TX) ||
		     ip_tunnel_info_af(tun_info) != AF_INET))
		जाओ err_मुक्त_skb;

	key = &tun_info->key;
	tunnel_hlen = gre_calc_hlen(key->tun_flags);

	अगर (skb_cow_head(skb, dev->needed_headroom))
		जाओ err_मुक्त_skb;

	/* Push Tunnel header. */
	अगर (gre_handle_offloads(skb, !!(tun_info->key.tun_flags & TUNNEL_CSUM)))
		जाओ err_मुक्त_skb;

	flags = tun_info->key.tun_flags &
		(TUNNEL_CSUM | TUNNEL_KEY | TUNNEL_SEQ);
	gre_build_header(skb, tunnel_hlen, flags, proto,
			 tunnel_id_to_key32(tun_info->key.tun_id),
			 (flags & TUNNEL_SEQ) ? htonl(tunnel->o_seqno++) : 0);

	ip_md_tunnel_xmit(skb, dev, IPPROTO_GRE, tunnel_hlen);

	वापस;

err_मुक्त_skb:
	kमुक्त_skb(skb);
	dev->stats.tx_dropped++;
पूर्ण

अटल व्योम erspan_fb_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	काष्ठा ip_tunnel_info *tun_info;
	स्थिर काष्ठा ip_tunnel_key *key;
	काष्ठा erspan_metadata *md;
	bool truncate = false;
	__be16 proto;
	पूर्णांक tunnel_hlen;
	पूर्णांक version;
	पूर्णांक nhoff;
	पूर्णांक thoff;

	tun_info = skb_tunnel_info(skb);
	अगर (unlikely(!tun_info || !(tun_info->mode & IP_TUNNEL_INFO_TX) ||
		     ip_tunnel_info_af(tun_info) != AF_INET))
		जाओ err_मुक्त_skb;

	key = &tun_info->key;
	अगर (!(tun_info->key.tun_flags & TUNNEL_ERSPAN_OPT))
		जाओ err_मुक्त_skb;
	अगर (tun_info->options_len < माप(*md))
		जाओ err_मुक्त_skb;
	md = ip_tunnel_info_opts(tun_info);

	/* ERSPAN has fixed 8 byte GRE header */
	version = md->version;
	tunnel_hlen = 8 + erspan_hdr_len(version);

	अगर (skb_cow_head(skb, dev->needed_headroom))
		जाओ err_मुक्त_skb;

	अगर (gre_handle_offloads(skb, false))
		जाओ err_मुक्त_skb;

	अगर (skb->len > dev->mtu + dev->hard_header_len) अणु
		pskb_trim(skb, dev->mtu + dev->hard_header_len);
		truncate = true;
	पूर्ण

	nhoff = skb_network_header(skb) - skb_mac_header(skb);
	अगर (skb->protocol == htons(ETH_P_IP) &&
	    (ntohs(ip_hdr(skb)->tot_len) > skb->len - nhoff))
		truncate = true;

	thoff = skb_transport_header(skb) - skb_mac_header(skb);
	अगर (skb->protocol == htons(ETH_P_IPV6) &&
	    (ntohs(ipv6_hdr(skb)->payload_len) > skb->len - thoff))
		truncate = true;

	अगर (version == 1) अणु
		erspan_build_header(skb, ntohl(tunnel_id_to_key32(key->tun_id)),
				    ntohl(md->u.index), truncate, true);
		proto = htons(ETH_P_ERSPAN);
	पूर्ण अन्यथा अगर (version == 2) अणु
		erspan_build_header_v2(skb,
				       ntohl(tunnel_id_to_key32(key->tun_id)),
				       md->u.md2.dir,
				       get_hwid(&md->u.md2),
				       truncate, true);
		proto = htons(ETH_P_ERSPAN2);
	पूर्ण अन्यथा अणु
		जाओ err_मुक्त_skb;
	पूर्ण

	gre_build_header(skb, 8, TUNNEL_SEQ,
			 proto, 0, htonl(tunnel->o_seqno++));

	ip_md_tunnel_xmit(skb, dev, IPPROTO_GRE, tunnel_hlen);

	वापस;

err_मुक्त_skb:
	kमुक्त_skb(skb);
	dev->stats.tx_dropped++;
पूर्ण

अटल पूर्णांक gre_fill_metadata_dst(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा ip_tunnel_info *info = skb_tunnel_info(skb);
	स्थिर काष्ठा ip_tunnel_key *key;
	काष्ठा rtable *rt;
	काष्ठा flowi4 fl4;

	अगर (ip_tunnel_info_af(info) != AF_INET)
		वापस -EINVAL;

	key = &info->key;
	ip_tunnel_init_flow(&fl4, IPPROTO_GRE, key->u.ipv4.dst, key->u.ipv4.src,
			    tunnel_id_to_key32(key->tun_id), key->tos, 0,
			    skb->mark, skb_get_hash(skb));
	rt = ip_route_output_key(dev_net(dev), &fl4);
	अगर (IS_ERR(rt))
		वापस PTR_ERR(rt);

	ip_rt_put(rt);
	info->key.u.ipv4.src = fl4.saddr;
	वापस 0;
पूर्ण

अटल netdev_tx_t ipgre_xmit(काष्ठा sk_buff *skb,
			      काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	स्थिर काष्ठा iphdr *tnl_params;

	अगर (!pskb_inet_may_pull(skb))
		जाओ मुक्त_skb;

	अगर (tunnel->collect_md) अणु
		gre_fb_xmit(skb, dev, skb->protocol);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (dev->header_ops) अणु
		अगर (skb_cow_head(skb, 0))
			जाओ मुक्त_skb;

		tnl_params = (स्थिर काष्ठा iphdr *)skb->data;

		/* Pull skb since ip_tunnel_xmit() needs skb->data poपूर्णांकing
		 * to gre header.
		 */
		skb_pull(skb, tunnel->hlen + माप(काष्ठा iphdr));
		skb_reset_mac_header(skb);
	पूर्ण अन्यथा अणु
		अगर (skb_cow_head(skb, dev->needed_headroom))
			जाओ मुक्त_skb;

		tnl_params = &tunnel->parms.iph;
	पूर्ण

	अगर (gre_handle_offloads(skb, !!(tunnel->parms.o_flags & TUNNEL_CSUM)))
		जाओ मुक्त_skb;

	__gre_xmit(skb, dev, tnl_params, skb->protocol);
	वापस NETDEV_TX_OK;

मुक्त_skb:
	kमुक्त_skb(skb);
	dev->stats.tx_dropped++;
	वापस NETDEV_TX_OK;
पूर्ण

अटल netdev_tx_t erspan_xmit(काष्ठा sk_buff *skb,
			       काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	bool truncate = false;
	__be16 proto;

	अगर (!pskb_inet_may_pull(skb))
		जाओ मुक्त_skb;

	अगर (tunnel->collect_md) अणु
		erspan_fb_xmit(skb, dev);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (gre_handle_offloads(skb, false))
		जाओ मुक्त_skb;

	अगर (skb_cow_head(skb, dev->needed_headroom))
		जाओ मुक्त_skb;

	अगर (skb->len > dev->mtu + dev->hard_header_len) अणु
		pskb_trim(skb, dev->mtu + dev->hard_header_len);
		truncate = true;
	पूर्ण

	/* Push ERSPAN header */
	अगर (tunnel->erspan_ver == 0) अणु
		proto = htons(ETH_P_ERSPAN);
		tunnel->parms.o_flags &= ~TUNNEL_SEQ;
	पूर्ण अन्यथा अगर (tunnel->erspan_ver == 1) अणु
		erspan_build_header(skb, ntohl(tunnel->parms.o_key),
				    tunnel->index,
				    truncate, true);
		proto = htons(ETH_P_ERSPAN);
	पूर्ण अन्यथा अगर (tunnel->erspan_ver == 2) अणु
		erspan_build_header_v2(skb, ntohl(tunnel->parms.o_key),
				       tunnel->dir, tunnel->hwid,
				       truncate, true);
		proto = htons(ETH_P_ERSPAN2);
	पूर्ण अन्यथा अणु
		जाओ मुक्त_skb;
	पूर्ण

	tunnel->parms.o_flags &= ~TUNNEL_KEY;
	__gre_xmit(skb, dev, &tunnel->parms.iph, proto);
	वापस NETDEV_TX_OK;

मुक्त_skb:
	kमुक्त_skb(skb);
	dev->stats.tx_dropped++;
	वापस NETDEV_TX_OK;
पूर्ण

अटल netdev_tx_t gre_tap_xmit(काष्ठा sk_buff *skb,
				काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);

	अगर (!pskb_inet_may_pull(skb))
		जाओ मुक्त_skb;

	अगर (tunnel->collect_md) अणु
		gre_fb_xmit(skb, dev, htons(ETH_P_TEB));
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (gre_handle_offloads(skb, !!(tunnel->parms.o_flags & TUNNEL_CSUM)))
		जाओ मुक्त_skb;

	अगर (skb_cow_head(skb, dev->needed_headroom))
		जाओ मुक्त_skb;

	__gre_xmit(skb, dev, &tunnel->parms.iph, htons(ETH_P_TEB));
	वापस NETDEV_TX_OK;

मुक्त_skb:
	kमुक्त_skb(skb);
	dev->stats.tx_dropped++;
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम ipgre_link_update(काष्ठा net_device *dev, bool set_mtu)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	पूर्णांक len;

	len = tunnel->tun_hlen;
	tunnel->tun_hlen = gre_calc_hlen(tunnel->parms.o_flags);
	len = tunnel->tun_hlen - len;
	tunnel->hlen = tunnel->hlen + len;

	अगर (dev->header_ops)
		dev->hard_header_len += len;
	अन्यथा
		dev->needed_headroom += len;

	अगर (set_mtu)
		dev->mtu = max_t(पूर्णांक, dev->mtu - len, 68);

	अगर (!(tunnel->parms.o_flags & TUNNEL_SEQ)) अणु
		अगर (!(tunnel->parms.o_flags & TUNNEL_CSUM) ||
		    tunnel->encap.type == TUNNEL_ENCAP_NONE) अणु
			dev->features |= NETIF_F_GSO_SOFTWARE;
			dev->hw_features |= NETIF_F_GSO_SOFTWARE;
		पूर्ण अन्यथा अणु
			dev->features &= ~NETIF_F_GSO_SOFTWARE;
			dev->hw_features &= ~NETIF_F_GSO_SOFTWARE;
		पूर्ण
		dev->features |= NETIF_F_LLTX;
	पूर्ण अन्यथा अणु
		dev->hw_features &= ~NETIF_F_GSO_SOFTWARE;
		dev->features &= ~(NETIF_F_LLTX | NETIF_F_GSO_SOFTWARE);
	पूर्ण
पूर्ण

अटल पूर्णांक ipgre_tunnel_ctl(काष्ठा net_device *dev, काष्ठा ip_tunnel_parm *p,
			    पूर्णांक cmd)
अणु
	पूर्णांक err;

	अगर (cmd == SIOCADDTUNNEL || cmd == SIOCCHGTUNNEL) अणु
		अगर (p->iph.version != 4 || p->iph.protocol != IPPROTO_GRE ||
		    p->iph.ihl != 5 || (p->iph.frag_off & htons(~IP_DF)) ||
		    ((p->i_flags | p->o_flags) & (GRE_VERSION | GRE_ROUTING)))
			वापस -EINVAL;
	पूर्ण

	p->i_flags = gre_flags_to_tnl_flags(p->i_flags);
	p->o_flags = gre_flags_to_tnl_flags(p->o_flags);

	err = ip_tunnel_ctl(dev, p, cmd);
	अगर (err)
		वापस err;

	अगर (cmd == SIOCCHGTUNNEL) अणु
		काष्ठा ip_tunnel *t = netdev_priv(dev);

		t->parms.i_flags = p->i_flags;
		t->parms.o_flags = p->o_flags;

		अगर (म_भेद(dev->rtnl_link_ops->kind, "erspan"))
			ipgre_link_update(dev, true);
	पूर्ण

	p->i_flags = gre_tnl_flags_to_gre_flags(p->i_flags);
	p->o_flags = gre_tnl_flags_to_gre_flags(p->o_flags);
	वापस 0;
पूर्ण

/* Nice toy. Unक्रमtunately, useless in real lअगरe :-)
   It allows to स्थिरruct भव multiprotocol broadcast "LAN"
   over the Internet, provided multicast routing is tuned.


   I have no idea was this bicycle invented beक्रमe me,
   so that I had to set ARPHRD_IPGRE to a अक्रमom value.
   I have an impression, that Cisco could make something similar,
   but this feature is apparently missing in IOS<=11.2(8).

   I set up 10.66.66/24 and fec0:6666:6666::0/96 as भव networks
   with broadcast 224.66.66.66. If you have access to mbone, play with me :-)

   ping -t 255 224.66.66.66

   If nobody answers, mbone करोes not work.

   ip tunnel add Universe mode gre remote 224.66.66.66 local <Your_real_addr> ttl 255
   ip addr add 10.66.66.<somewhat>/24 dev Universe
   अगरconfig Universe up
   अगरconfig Universe add fe80::<Your_real_addr>/10
   अगरconfig Universe add fec0:6666:6666::<Your_real_addr>/96
   ftp 10.66.66.66
   ...
   ftp fec0:6666:6666::193.233.7.65
   ...
 */
अटल पूर्णांक ipgre_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			अचिन्हित लघु type,
			स्थिर व्योम *daddr, स्थिर व्योम *saddr, अचिन्हित पूर्णांक len)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);
	काष्ठा iphdr *iph;
	काष्ठा gre_base_hdr *greh;

	iph = skb_push(skb, t->hlen + माप(*iph));
	greh = (काष्ठा gre_base_hdr *)(iph+1);
	greh->flags = gre_tnl_flags_to_gre_flags(t->parms.o_flags);
	greh->protocol = htons(type);

	स_नकल(iph, &t->parms.iph, माप(काष्ठा iphdr));

	/* Set the source hardware address. */
	अगर (saddr)
		स_नकल(&iph->saddr, saddr, 4);
	अगर (daddr)
		स_नकल(&iph->daddr, daddr, 4);
	अगर (iph->daddr)
		वापस t->hlen + माप(*iph);

	वापस -(t->hlen + माप(*iph));
पूर्ण

अटल पूर्णांक ipgre_header_parse(स्थिर काष्ठा sk_buff *skb, अचिन्हित अक्षर *haddr)
अणु
	स्थिर काष्ठा iphdr *iph = (स्थिर काष्ठा iphdr *) skb_mac_header(skb);
	स_नकल(haddr, &iph->saddr, 4);
	वापस 4;
पूर्ण

अटल स्थिर काष्ठा header_ops ipgre_header_ops = अणु
	.create	= ipgre_header,
	.parse	= ipgre_header_parse,
पूर्ण;

#अगर_घोषित CONFIG_NET_IPGRE_BROADCAST
अटल पूर्णांक ipgre_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);

	अगर (ipv4_is_multicast(t->parms.iph.daddr)) अणु
		काष्ठा flowi4 fl4;
		काष्ठा rtable *rt;

		rt = ip_route_output_gre(t->net, &fl4,
					 t->parms.iph.daddr,
					 t->parms.iph.saddr,
					 t->parms.o_key,
					 RT_TOS(t->parms.iph.tos),
					 t->parms.link);
		अगर (IS_ERR(rt))
			वापस -EADDRNOTAVAIL;
		dev = rt->dst.dev;
		ip_rt_put(rt);
		अगर (!__in_dev_get_rtnl(dev))
			वापस -EADDRNOTAVAIL;
		t->mlink = dev->अगरindex;
		ip_mc_inc_group(__in_dev_get_rtnl(dev), t->parms.iph.daddr);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ipgre_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);

	अगर (ipv4_is_multicast(t->parms.iph.daddr) && t->mlink) अणु
		काष्ठा in_device *in_dev;
		in_dev = inetdev_by_index(t->net, t->mlink);
		अगर (in_dev)
			ip_mc_dec_group(in_dev, t->parms.iph.daddr);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops ipgre_netdev_ops = अणु
	.nकरो_init		= ipgre_tunnel_init,
	.nकरो_uninit		= ip_tunnel_uninit,
#अगर_घोषित CONFIG_NET_IPGRE_BROADCAST
	.nकरो_खोलो		= ipgre_खोलो,
	.nकरो_stop		= ipgre_बंद,
#पूर्ण_अगर
	.nकरो_start_xmit		= ipgre_xmit,
	.nकरो_करो_ioctl		= ip_tunnel_ioctl,
	.nकरो_change_mtu		= ip_tunnel_change_mtu,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_get_अगरlink		= ip_tunnel_get_अगरlink,
	.nकरो_tunnel_ctl		= ipgre_tunnel_ctl,
पूर्ण;

#घोषणा GRE_FEATURES (NETIF_F_SG |		\
		      NETIF_F_FRAGLIST |	\
		      NETIF_F_HIGHDMA |		\
		      NETIF_F_HW_CSUM)

अटल व्योम ipgre_tunnel_setup(काष्ठा net_device *dev)
अणु
	dev->netdev_ops		= &ipgre_netdev_ops;
	dev->type		= ARPHRD_IPGRE;
	ip_tunnel_setup(dev, ipgre_net_id);
पूर्ण

अटल व्योम __gre_tunnel_init(काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel;

	tunnel = netdev_priv(dev);
	tunnel->tun_hlen = gre_calc_hlen(tunnel->parms.o_flags);
	tunnel->parms.iph.protocol = IPPROTO_GRE;

	tunnel->hlen = tunnel->tun_hlen + tunnel->encap_hlen;
	dev->needed_headroom = tunnel->hlen + माप(tunnel->parms.iph);

	dev->features		|= GRE_FEATURES;
	dev->hw_features	|= GRE_FEATURES;

	अगर (!(tunnel->parms.o_flags & TUNNEL_SEQ)) अणु
		/* TCP offload with GRE SEQ is not supported, nor
		 * can we support 2 levels of outer headers requiring
		 * an update.
		 */
		अगर (!(tunnel->parms.o_flags & TUNNEL_CSUM) ||
		    (tunnel->encap.type == TUNNEL_ENCAP_NONE)) अणु
			dev->features    |= NETIF_F_GSO_SOFTWARE;
			dev->hw_features |= NETIF_F_GSO_SOFTWARE;
		पूर्ण

		/* Can use a lockless transmit, unless we generate
		 * output sequences
		 */
		dev->features |= NETIF_F_LLTX;
	पूर्ण
पूर्ण

अटल पूर्णांक ipgre_tunnel_init(काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	काष्ठा iphdr *iph = &tunnel->parms.iph;

	__gre_tunnel_init(dev);

	स_नकल(dev->dev_addr, &iph->saddr, 4);
	स_नकल(dev->broadcast, &iph->daddr, 4);

	dev->flags		= IFF_NOARP;
	netअगर_keep_dst(dev);
	dev->addr_len		= 4;

	अगर (iph->daddr && !tunnel->collect_md) अणु
#अगर_घोषित CONFIG_NET_IPGRE_BROADCAST
		अगर (ipv4_is_multicast(iph->daddr)) अणु
			अगर (!iph->saddr)
				वापस -EINVAL;
			dev->flags = IFF_BROADCAST;
			dev->header_ops = &ipgre_header_ops;
			dev->hard_header_len = tunnel->hlen + माप(*iph);
			dev->needed_headroom = 0;
		पूर्ण
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (!tunnel->collect_md) अणु
		dev->header_ops = &ipgre_header_ops;
		dev->hard_header_len = tunnel->hlen + माप(*iph);
		dev->needed_headroom = 0;
	पूर्ण

	वापस ip_tunnel_init(dev);
पूर्ण

अटल स्थिर काष्ठा gre_protocol ipgre_protocol = अणु
	.handler     = gre_rcv,
	.err_handler = gre_err,
पूर्ण;

अटल पूर्णांक __net_init ipgre_init_net(काष्ठा net *net)
अणु
	वापस ip_tunnel_init_net(net, ipgre_net_id, &ipgre_link_ops, शून्य);
पूर्ण

अटल व्योम __net_निकास ipgre_निकास_batch_net(काष्ठा list_head *list_net)
अणु
	ip_tunnel_delete_nets(list_net, ipgre_net_id, &ipgre_link_ops);
पूर्ण

अटल काष्ठा pernet_operations ipgre_net_ops = अणु
	.init = ipgre_init_net,
	.निकास_batch = ipgre_निकास_batch_net,
	.id   = &ipgre_net_id,
	.size = माप(काष्ठा ip_tunnel_net),
पूर्ण;

अटल पूर्णांक ipgre_tunnel_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
				 काष्ठा netlink_ext_ack *extack)
अणु
	__be16 flags;

	अगर (!data)
		वापस 0;

	flags = 0;
	अगर (data[IFLA_GRE_IFLAGS])
		flags |= nla_get_be16(data[IFLA_GRE_IFLAGS]);
	अगर (data[IFLA_GRE_OFLAGS])
		flags |= nla_get_be16(data[IFLA_GRE_OFLAGS]);
	अगर (flags & (GRE_VERSION|GRE_ROUTING))
		वापस -EINVAL;

	अगर (data[IFLA_GRE_COLLECT_METADATA] &&
	    data[IFLA_GRE_ENCAP_TYPE] &&
	    nla_get_u16(data[IFLA_GRE_ENCAP_TYPE]) != TUNNEL_ENCAP_NONE)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक ipgre_tap_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			      काष्ठा netlink_ext_ack *extack)
अणु
	__be32 daddr;

	अगर (tb[IFLA_ADDRESS]) अणु
		अगर (nla_len(tb[IFLA_ADDRESS]) != ETH_ALEN)
			वापस -EINVAL;
		अगर (!is_valid_ether_addr(nla_data(tb[IFLA_ADDRESS])))
			वापस -EADDRNOTAVAIL;
	पूर्ण

	अगर (!data)
		जाओ out;

	अगर (data[IFLA_GRE_REMOTE]) अणु
		स_नकल(&daddr, nla_data(data[IFLA_GRE_REMOTE]), 4);
		अगर (!daddr)
			वापस -EINVAL;
	पूर्ण

out:
	वापस ipgre_tunnel_validate(tb, data, extack);
पूर्ण

अटल पूर्णांक erspan_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			   काष्ठा netlink_ext_ack *extack)
अणु
	__be16 flags = 0;
	पूर्णांक ret;

	अगर (!data)
		वापस 0;

	ret = ipgre_tap_validate(tb, data, extack);
	अगर (ret)
		वापस ret;

	अगर (data[IFLA_GRE_ERSPAN_VER] &&
	    nla_get_u8(data[IFLA_GRE_ERSPAN_VER]) == 0)
		वापस 0;

	/* ERSPAN type II/III should only have GRE sequence and key flag */
	अगर (data[IFLA_GRE_OFLAGS])
		flags |= nla_get_be16(data[IFLA_GRE_OFLAGS]);
	अगर (data[IFLA_GRE_IFLAGS])
		flags |= nla_get_be16(data[IFLA_GRE_IFLAGS]);
	अगर (!data[IFLA_GRE_COLLECT_METADATA] &&
	    flags != (GRE_SEQ | GRE_KEY))
		वापस -EINVAL;

	/* ERSPAN Session ID only has 10-bit. Since we reuse
	 * 32-bit key field as ID, check it's range.
	 */
	अगर (data[IFLA_GRE_IKEY] &&
	    (ntohl(nla_get_be32(data[IFLA_GRE_IKEY])) & ~ID_MASK))
		वापस -EINVAL;

	अगर (data[IFLA_GRE_OKEY] &&
	    (ntohl(nla_get_be32(data[IFLA_GRE_OKEY])) & ~ID_MASK))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक ipgre_netlink_parms(काष्ठा net_device *dev,
				काष्ठा nlattr *data[],
				काष्ठा nlattr *tb[],
				काष्ठा ip_tunnel_parm *parms,
				__u32 *fwmark)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);

	स_रखो(parms, 0, माप(*parms));

	parms->iph.protocol = IPPROTO_GRE;

	अगर (!data)
		वापस 0;

	अगर (data[IFLA_GRE_LINK])
		parms->link = nla_get_u32(data[IFLA_GRE_LINK]);

	अगर (data[IFLA_GRE_IFLAGS])
		parms->i_flags = gre_flags_to_tnl_flags(nla_get_be16(data[IFLA_GRE_IFLAGS]));

	अगर (data[IFLA_GRE_OFLAGS])
		parms->o_flags = gre_flags_to_tnl_flags(nla_get_be16(data[IFLA_GRE_OFLAGS]));

	अगर (data[IFLA_GRE_IKEY])
		parms->i_key = nla_get_be32(data[IFLA_GRE_IKEY]);

	अगर (data[IFLA_GRE_OKEY])
		parms->o_key = nla_get_be32(data[IFLA_GRE_OKEY]);

	अगर (data[IFLA_GRE_LOCAL])
		parms->iph.saddr = nla_get_in_addr(data[IFLA_GRE_LOCAL]);

	अगर (data[IFLA_GRE_REMOTE])
		parms->iph.daddr = nla_get_in_addr(data[IFLA_GRE_REMOTE]);

	अगर (data[IFLA_GRE_TTL])
		parms->iph.ttl = nla_get_u8(data[IFLA_GRE_TTL]);

	अगर (data[IFLA_GRE_TOS])
		parms->iph.tos = nla_get_u8(data[IFLA_GRE_TOS]);

	अगर (!data[IFLA_GRE_PMTUDISC] || nla_get_u8(data[IFLA_GRE_PMTUDISC])) अणु
		अगर (t->ignore_df)
			वापस -EINVAL;
		parms->iph.frag_off = htons(IP_DF);
	पूर्ण

	अगर (data[IFLA_GRE_COLLECT_METADATA]) अणु
		t->collect_md = true;
		अगर (dev->type == ARPHRD_IPGRE)
			dev->type = ARPHRD_NONE;
	पूर्ण

	अगर (data[IFLA_GRE_IGNORE_DF]) अणु
		अगर (nla_get_u8(data[IFLA_GRE_IGNORE_DF])
		  && (parms->iph.frag_off & htons(IP_DF)))
			वापस -EINVAL;
		t->ignore_df = !!nla_get_u8(data[IFLA_GRE_IGNORE_DF]);
	पूर्ण

	अगर (data[IFLA_GRE_FWMARK])
		*fwmark = nla_get_u32(data[IFLA_GRE_FWMARK]);

	वापस 0;
पूर्ण

अटल पूर्णांक erspan_netlink_parms(काष्ठा net_device *dev,
				काष्ठा nlattr *data[],
				काष्ठा nlattr *tb[],
				काष्ठा ip_tunnel_parm *parms,
				__u32 *fwmark)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);
	पूर्णांक err;

	err = ipgre_netlink_parms(dev, data, tb, parms, fwmark);
	अगर (err)
		वापस err;
	अगर (!data)
		वापस 0;

	अगर (data[IFLA_GRE_ERSPAN_VER]) अणु
		t->erspan_ver = nla_get_u8(data[IFLA_GRE_ERSPAN_VER]);

		अगर (t->erspan_ver > 2)
			वापस -EINVAL;
	पूर्ण

	अगर (t->erspan_ver == 1) अणु
		अगर (data[IFLA_GRE_ERSPAN_INDEX]) अणु
			t->index = nla_get_u32(data[IFLA_GRE_ERSPAN_INDEX]);
			अगर (t->index & ~INDEX_MASK)
				वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (t->erspan_ver == 2) अणु
		अगर (data[IFLA_GRE_ERSPAN_सूची]) अणु
			t->dir = nla_get_u8(data[IFLA_GRE_ERSPAN_सूची]);
			अगर (t->dir & ~(सूची_MASK >> सूची_OFFSET))
				वापस -EINVAL;
		पूर्ण
		अगर (data[IFLA_GRE_ERSPAN_HWID]) अणु
			t->hwid = nla_get_u16(data[IFLA_GRE_ERSPAN_HWID]);
			अगर (t->hwid & ~(HWID_MASK >> HWID_OFFSET))
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* This function वापसs true when ENCAP attributes are present in the nl msg */
अटल bool ipgre_netlink_encap_parms(काष्ठा nlattr *data[],
				      काष्ठा ip_tunnel_encap *ipencap)
अणु
	bool ret = false;

	स_रखो(ipencap, 0, माप(*ipencap));

	अगर (!data)
		वापस ret;

	अगर (data[IFLA_GRE_ENCAP_TYPE]) अणु
		ret = true;
		ipencap->type = nla_get_u16(data[IFLA_GRE_ENCAP_TYPE]);
	पूर्ण

	अगर (data[IFLA_GRE_ENCAP_FLAGS]) अणु
		ret = true;
		ipencap->flags = nla_get_u16(data[IFLA_GRE_ENCAP_FLAGS]);
	पूर्ण

	अगर (data[IFLA_GRE_ENCAP_SPORT]) अणु
		ret = true;
		ipencap->sport = nla_get_be16(data[IFLA_GRE_ENCAP_SPORT]);
	पूर्ण

	अगर (data[IFLA_GRE_ENCAP_DPORT]) अणु
		ret = true;
		ipencap->dport = nla_get_be16(data[IFLA_GRE_ENCAP_DPORT]);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक gre_tap_init(काष्ठा net_device *dev)
अणु
	__gre_tunnel_init(dev);
	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE;
	netअगर_keep_dst(dev);

	वापस ip_tunnel_init(dev);
पूर्ण

अटल स्थिर काष्ठा net_device_ops gre_tap_netdev_ops = अणु
	.nकरो_init		= gre_tap_init,
	.nकरो_uninit		= ip_tunnel_uninit,
	.nकरो_start_xmit		= gre_tap_xmit,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_change_mtu		= ip_tunnel_change_mtu,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_get_अगरlink		= ip_tunnel_get_अगरlink,
	.nकरो_fill_metadata_dst	= gre_fill_metadata_dst,
पूर्ण;

अटल पूर्णांक erspan_tunnel_init(काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);

	अगर (tunnel->erspan_ver == 0)
		tunnel->tun_hlen = 4; /* 4-byte GRE hdr. */
	अन्यथा
		tunnel->tun_hlen = 8; /* 8-byte GRE hdr. */

	tunnel->parms.iph.protocol = IPPROTO_GRE;
	tunnel->hlen = tunnel->tun_hlen + tunnel->encap_hlen +
		       erspan_hdr_len(tunnel->erspan_ver);

	dev->features		|= GRE_FEATURES;
	dev->hw_features	|= GRE_FEATURES;
	dev->priv_flags		|= IFF_LIVE_ADDR_CHANGE;
	netअगर_keep_dst(dev);

	वापस ip_tunnel_init(dev);
पूर्ण

अटल स्थिर काष्ठा net_device_ops erspan_netdev_ops = अणु
	.nकरो_init		= erspan_tunnel_init,
	.nकरो_uninit		= ip_tunnel_uninit,
	.nकरो_start_xmit		= erspan_xmit,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_change_mtu		= ip_tunnel_change_mtu,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_get_अगरlink		= ip_tunnel_get_अगरlink,
	.nकरो_fill_metadata_dst	= gre_fill_metadata_dst,
पूर्ण;

अटल व्योम ipgre_tap_setup(काष्ठा net_device *dev)
अणु
	ether_setup(dev);
	dev->max_mtu = 0;
	dev->netdev_ops	= &gre_tap_netdev_ops;
	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->priv_flags	|= IFF_LIVE_ADDR_CHANGE;
	ip_tunnel_setup(dev, gre_tap_net_id);
पूर्ण

अटल पूर्णांक
ipgre_newlink_encap_setup(काष्ठा net_device *dev, काष्ठा nlattr *data[])
अणु
	काष्ठा ip_tunnel_encap ipencap;

	अगर (ipgre_netlink_encap_parms(data, &ipencap)) अणु
		काष्ठा ip_tunnel *t = netdev_priv(dev);
		पूर्णांक err = ip_tunnel_encap_setup(t, &ipencap);

		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ipgre_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			 काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ip_tunnel_parm p;
	__u32 fwmark = 0;
	पूर्णांक err;

	err = ipgre_newlink_encap_setup(dev, data);
	अगर (err)
		वापस err;

	err = ipgre_netlink_parms(dev, data, tb, &p, &fwmark);
	अगर (err < 0)
		वापस err;
	वापस ip_tunnel_newlink(dev, tb, &p, fwmark);
पूर्ण

अटल पूर्णांक erspan_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			  काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ip_tunnel_parm p;
	__u32 fwmark = 0;
	पूर्णांक err;

	err = ipgre_newlink_encap_setup(dev, data);
	अगर (err)
		वापस err;

	err = erspan_netlink_parms(dev, data, tb, &p, &fwmark);
	अगर (err)
		वापस err;
	वापस ip_tunnel_newlink(dev, tb, &p, fwmark);
पूर्ण

अटल पूर्णांक ipgre_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			    काष्ठा nlattr *data[],
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);
	__u32 fwmark = t->fwmark;
	काष्ठा ip_tunnel_parm p;
	पूर्णांक err;

	err = ipgre_newlink_encap_setup(dev, data);
	अगर (err)
		वापस err;

	err = ipgre_netlink_parms(dev, data, tb, &p, &fwmark);
	अगर (err < 0)
		वापस err;

	err = ip_tunnel_changelink(dev, tb, &p, fwmark);
	अगर (err < 0)
		वापस err;

	t->parms.i_flags = p.i_flags;
	t->parms.o_flags = p.o_flags;

	ipgre_link_update(dev, !tb[IFLA_MTU]);

	वापस 0;
पूर्ण

अटल पूर्णांक erspan_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			     काष्ठा nlattr *data[],
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);
	__u32 fwmark = t->fwmark;
	काष्ठा ip_tunnel_parm p;
	पूर्णांक err;

	err = ipgre_newlink_encap_setup(dev, data);
	अगर (err)
		वापस err;

	err = erspan_netlink_parms(dev, data, tb, &p, &fwmark);
	अगर (err < 0)
		वापस err;

	err = ip_tunnel_changelink(dev, tb, &p, fwmark);
	अगर (err < 0)
		वापस err;

	t->parms.i_flags = p.i_flags;
	t->parms.o_flags = p.o_flags;

	वापस 0;
पूर्ण

अटल माप_प्रकार ipgre_get_size(स्थिर काष्ठा net_device *dev)
अणु
	वापस
		/* IFLA_GRE_LINK */
		nla_total_size(4) +
		/* IFLA_GRE_IFLAGS */
		nla_total_size(2) +
		/* IFLA_GRE_OFLAGS */
		nla_total_size(2) +
		/* IFLA_GRE_IKEY */
		nla_total_size(4) +
		/* IFLA_GRE_OKEY */
		nla_total_size(4) +
		/* IFLA_GRE_LOCAL */
		nla_total_size(4) +
		/* IFLA_GRE_REMOTE */
		nla_total_size(4) +
		/* IFLA_GRE_TTL */
		nla_total_size(1) +
		/* IFLA_GRE_TOS */
		nla_total_size(1) +
		/* IFLA_GRE_PMTUDISC */
		nla_total_size(1) +
		/* IFLA_GRE_ENCAP_TYPE */
		nla_total_size(2) +
		/* IFLA_GRE_ENCAP_FLAGS */
		nla_total_size(2) +
		/* IFLA_GRE_ENCAP_SPORT */
		nla_total_size(2) +
		/* IFLA_GRE_ENCAP_DPORT */
		nla_total_size(2) +
		/* IFLA_GRE_COLLECT_METADATA */
		nla_total_size(0) +
		/* IFLA_GRE_IGNORE_DF */
		nla_total_size(1) +
		/* IFLA_GRE_FWMARK */
		nla_total_size(4) +
		/* IFLA_GRE_ERSPAN_INDEX */
		nla_total_size(4) +
		/* IFLA_GRE_ERSPAN_VER */
		nla_total_size(1) +
		/* IFLA_GRE_ERSPAN_सूची */
		nla_total_size(1) +
		/* IFLA_GRE_ERSPAN_HWID */
		nla_total_size(2) +
		0;
पूर्ण

अटल पूर्णांक ipgre_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);
	काष्ठा ip_tunnel_parm *p = &t->parms;
	__be16 o_flags = p->o_flags;

	अगर (t->erspan_ver <= 2) अणु
		अगर (t->erspan_ver != 0 && !t->collect_md)
			o_flags |= TUNNEL_KEY;

		अगर (nla_put_u8(skb, IFLA_GRE_ERSPAN_VER, t->erspan_ver))
			जाओ nla_put_failure;

		अगर (t->erspan_ver == 1) अणु
			अगर (nla_put_u32(skb, IFLA_GRE_ERSPAN_INDEX, t->index))
				जाओ nla_put_failure;
		पूर्ण अन्यथा अगर (t->erspan_ver == 2) अणु
			अगर (nla_put_u8(skb, IFLA_GRE_ERSPAN_सूची, t->dir))
				जाओ nla_put_failure;
			अगर (nla_put_u16(skb, IFLA_GRE_ERSPAN_HWID, t->hwid))
				जाओ nla_put_failure;
		पूर्ण
	पूर्ण

	अगर (nla_put_u32(skb, IFLA_GRE_LINK, p->link) ||
	    nla_put_be16(skb, IFLA_GRE_IFLAGS,
			 gre_tnl_flags_to_gre_flags(p->i_flags)) ||
	    nla_put_be16(skb, IFLA_GRE_OFLAGS,
			 gre_tnl_flags_to_gre_flags(o_flags)) ||
	    nla_put_be32(skb, IFLA_GRE_IKEY, p->i_key) ||
	    nla_put_be32(skb, IFLA_GRE_OKEY, p->o_key) ||
	    nla_put_in_addr(skb, IFLA_GRE_LOCAL, p->iph.saddr) ||
	    nla_put_in_addr(skb, IFLA_GRE_REMOTE, p->iph.daddr) ||
	    nla_put_u8(skb, IFLA_GRE_TTL, p->iph.ttl) ||
	    nla_put_u8(skb, IFLA_GRE_TOS, p->iph.tos) ||
	    nla_put_u8(skb, IFLA_GRE_PMTUDISC,
		       !!(p->iph.frag_off & htons(IP_DF))) ||
	    nla_put_u32(skb, IFLA_GRE_FWMARK, t->fwmark))
		जाओ nla_put_failure;

	अगर (nla_put_u16(skb, IFLA_GRE_ENCAP_TYPE,
			t->encap.type) ||
	    nla_put_be16(skb, IFLA_GRE_ENCAP_SPORT,
			 t->encap.sport) ||
	    nla_put_be16(skb, IFLA_GRE_ENCAP_DPORT,
			 t->encap.dport) ||
	    nla_put_u16(skb, IFLA_GRE_ENCAP_FLAGS,
			t->encap.flags))
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, IFLA_GRE_IGNORE_DF, t->ignore_df))
		जाओ nla_put_failure;

	अगर (t->collect_md) अणु
		अगर (nla_put_flag(skb, IFLA_GRE_COLLECT_METADATA))
			जाओ nla_put_failure;
	पूर्ण

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम erspan_setup(काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);

	ether_setup(dev);
	dev->max_mtu = 0;
	dev->netdev_ops = &erspan_netdev_ops;
	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE;
	ip_tunnel_setup(dev, erspan_net_id);
	t->erspan_ver = 1;
पूर्ण

अटल स्थिर काष्ठा nla_policy ipgre_policy[IFLA_GRE_MAX + 1] = अणु
	[IFLA_GRE_LINK]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_GRE_IFLAGS]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_GRE_OFLAGS]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_GRE_IKEY]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_GRE_OKEY]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_GRE_LOCAL]	= अणु .len = माप_field(काष्ठा iphdr, saddr) पूर्ण,
	[IFLA_GRE_REMOTE]	= अणु .len = माप_field(काष्ठा iphdr, daddr) पूर्ण,
	[IFLA_GRE_TTL]		= अणु .type = NLA_U8 पूर्ण,
	[IFLA_GRE_TOS]		= अणु .type = NLA_U8 पूर्ण,
	[IFLA_GRE_PMTUDISC]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_GRE_ENCAP_TYPE]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_GRE_ENCAP_FLAGS]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_GRE_ENCAP_SPORT]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_GRE_ENCAP_DPORT]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_GRE_COLLECT_METADATA]	= अणु .type = NLA_FLAG पूर्ण,
	[IFLA_GRE_IGNORE_DF]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_GRE_FWMARK]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_GRE_ERSPAN_INDEX]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_GRE_ERSPAN_VER]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_GRE_ERSPAN_सूची]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_GRE_ERSPAN_HWID]	= अणु .type = NLA_U16 पूर्ण,
पूर्ण;

अटल काष्ठा rtnl_link_ops ipgre_link_ops __पढ़ो_mostly = अणु
	.kind		= "gre",
	.maxtype	= IFLA_GRE_MAX,
	.policy		= ipgre_policy,
	.priv_size	= माप(काष्ठा ip_tunnel),
	.setup		= ipgre_tunnel_setup,
	.validate	= ipgre_tunnel_validate,
	.newlink	= ipgre_newlink,
	.changelink	= ipgre_changelink,
	.dellink	= ip_tunnel_dellink,
	.get_size	= ipgre_get_size,
	.fill_info	= ipgre_fill_info,
	.get_link_net	= ip_tunnel_get_link_net,
पूर्ण;

अटल काष्ठा rtnl_link_ops ipgre_tap_ops __पढ़ो_mostly = अणु
	.kind		= "gretap",
	.maxtype	= IFLA_GRE_MAX,
	.policy		= ipgre_policy,
	.priv_size	= माप(काष्ठा ip_tunnel),
	.setup		= ipgre_tap_setup,
	.validate	= ipgre_tap_validate,
	.newlink	= ipgre_newlink,
	.changelink	= ipgre_changelink,
	.dellink	= ip_tunnel_dellink,
	.get_size	= ipgre_get_size,
	.fill_info	= ipgre_fill_info,
	.get_link_net	= ip_tunnel_get_link_net,
पूर्ण;

अटल काष्ठा rtnl_link_ops erspan_link_ops __पढ़ो_mostly = अणु
	.kind		= "erspan",
	.maxtype	= IFLA_GRE_MAX,
	.policy		= ipgre_policy,
	.priv_size	= माप(काष्ठा ip_tunnel),
	.setup		= erspan_setup,
	.validate	= erspan_validate,
	.newlink	= erspan_newlink,
	.changelink	= erspan_changelink,
	.dellink	= ip_tunnel_dellink,
	.get_size	= ipgre_get_size,
	.fill_info	= ipgre_fill_info,
	.get_link_net	= ip_tunnel_get_link_net,
पूर्ण;

काष्ठा net_device *gretap_fb_dev_create(काष्ठा net *net, स्थिर अक्षर *name,
					u8 name_assign_type)
अणु
	काष्ठा nlattr *tb[IFLA_MAX + 1];
	काष्ठा net_device *dev;
	LIST_HEAD(list_समाप्त);
	काष्ठा ip_tunnel *t;
	पूर्णांक err;

	स_रखो(&tb, 0, माप(tb));

	dev = rtnl_create_link(net, name, name_assign_type,
			       &ipgre_tap_ops, tb, शून्य);
	अगर (IS_ERR(dev))
		वापस dev;

	/* Configure flow based GRE device. */
	t = netdev_priv(dev);
	t->collect_md = true;

	err = ipgre_newlink(net, dev, tb, शून्य, शून्य);
	अगर (err < 0) अणु
		मुक्त_netdev(dev);
		वापस ERR_PTR(err);
	पूर्ण

	/* खोलोvचयन users expect packet sizes to be unrestricted,
	 * so set the largest MTU we can.
	 */
	err = __ip_tunnel_change_mtu(dev, IP_MAX_MTU, false);
	अगर (err)
		जाओ out;

	err = rtnl_configure_link(dev, शून्य);
	अगर (err < 0)
		जाओ out;

	वापस dev;
out:
	ip_tunnel_dellink(dev, &list_समाप्त);
	unरेजिस्टर_netdevice_many(&list_समाप्त);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(gretap_fb_dev_create);

अटल पूर्णांक __net_init ipgre_tap_init_net(काष्ठा net *net)
अणु
	वापस ip_tunnel_init_net(net, gre_tap_net_id, &ipgre_tap_ops, "gretap0");
पूर्ण

अटल व्योम __net_निकास ipgre_tap_निकास_batch_net(काष्ठा list_head *list_net)
अणु
	ip_tunnel_delete_nets(list_net, gre_tap_net_id, &ipgre_tap_ops);
पूर्ण

अटल काष्ठा pernet_operations ipgre_tap_net_ops = अणु
	.init = ipgre_tap_init_net,
	.निकास_batch = ipgre_tap_निकास_batch_net,
	.id   = &gre_tap_net_id,
	.size = माप(काष्ठा ip_tunnel_net),
पूर्ण;

अटल पूर्णांक __net_init erspan_init_net(काष्ठा net *net)
अणु
	वापस ip_tunnel_init_net(net, erspan_net_id,
				  &erspan_link_ops, "erspan0");
पूर्ण

अटल व्योम __net_निकास erspan_निकास_batch_net(काष्ठा list_head *net_list)
अणु
	ip_tunnel_delete_nets(net_list, erspan_net_id, &erspan_link_ops);
पूर्ण

अटल काष्ठा pernet_operations erspan_net_ops = अणु
	.init = erspan_init_net,
	.निकास_batch = erspan_निकास_batch_net,
	.id   = &erspan_net_id,
	.size = माप(काष्ठा ip_tunnel_net),
पूर्ण;

अटल पूर्णांक __init ipgre_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("GRE over IPv4 tunneling driver\n");

	err = रेजिस्टर_pernet_device(&ipgre_net_ops);
	अगर (err < 0)
		वापस err;

	err = रेजिस्टर_pernet_device(&ipgre_tap_net_ops);
	अगर (err < 0)
		जाओ pnet_tap_failed;

	err = रेजिस्टर_pernet_device(&erspan_net_ops);
	अगर (err < 0)
		जाओ pnet_erspan_failed;

	err = gre_add_protocol(&ipgre_protocol, GREPROTO_CISCO);
	अगर (err < 0) अणु
		pr_info("%s: can't add protocol\n", __func__);
		जाओ add_proto_failed;
	पूर्ण

	err = rtnl_link_रेजिस्टर(&ipgre_link_ops);
	अगर (err < 0)
		जाओ rtnl_link_failed;

	err = rtnl_link_रेजिस्टर(&ipgre_tap_ops);
	अगर (err < 0)
		जाओ tap_ops_failed;

	err = rtnl_link_रेजिस्टर(&erspan_link_ops);
	अगर (err < 0)
		जाओ erspan_link_failed;

	वापस 0;

erspan_link_failed:
	rtnl_link_unरेजिस्टर(&ipgre_tap_ops);
tap_ops_failed:
	rtnl_link_unरेजिस्टर(&ipgre_link_ops);
rtnl_link_failed:
	gre_del_protocol(&ipgre_protocol, GREPROTO_CISCO);
add_proto_failed:
	unरेजिस्टर_pernet_device(&erspan_net_ops);
pnet_erspan_failed:
	unरेजिस्टर_pernet_device(&ipgre_tap_net_ops);
pnet_tap_failed:
	unरेजिस्टर_pernet_device(&ipgre_net_ops);
	वापस err;
पूर्ण

अटल व्योम __निकास ipgre_fini(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&ipgre_tap_ops);
	rtnl_link_unरेजिस्टर(&ipgre_link_ops);
	rtnl_link_unरेजिस्टर(&erspan_link_ops);
	gre_del_protocol(&ipgre_protocol, GREPROTO_CISCO);
	unरेजिस्टर_pernet_device(&ipgre_tap_net_ops);
	unरेजिस्टर_pernet_device(&ipgre_net_ops);
	unरेजिस्टर_pernet_device(&erspan_net_ops);
पूर्ण

module_init(ipgre_init);
module_निकास(ipgre_fini);
MODULE_LICENSE("GPL");
MODULE_ALIAS_RTNL_LINK("gre");
MODULE_ALIAS_RTNL_LINK("gretap");
MODULE_ALIAS_RTNL_LINK("erspan");
MODULE_ALIAS_NETDEV("gre0");
MODULE_ALIAS_NETDEV("gretap0");
MODULE_ALIAS_NETDEV("erspan0");
