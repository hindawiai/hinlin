<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	IPv6 input
 *	Linux INET6 implementation
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>
 *	Ian P. Morris		<I.P.Morris@soton.ac.uk>
 *
 *	Based in linux/net/ipv4/ip_input.c
 */
/* Changes
 *
 *	Mitsuru KANDA @USAGI and
 *	YOSHIFUJI Hideaki @USAGI: Remove ipv6_parse_exthdrs().
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/in6.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/mroute6.h>
#समावेश <linux/slab.h>
#समावेश <linux/indirect_call_wrapper.h>

#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv6.h>

#समावेश <net/sock.h>
#समावेश <net/snmp.h>
#समावेश <net/udp.h>

#समावेश <net/ipv6.h>
#समावेश <net/protocol.h>
#समावेश <net/transp_v6.h>
#समावेश <net/rawv6.h>
#समावेश <net/ndisc.h>
#समावेश <net/ip6_route.h>
#समावेश <net/addrconf.h>
#समावेश <net/xfrm.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/dst_metadata.h>

INसूचीECT_CALLABLE_DECLARE(व्योम tcp_v6_early_demux(काष्ठा sk_buff *));
अटल व्योम ip6_rcv_finish_core(काष्ठा net *net, काष्ठा sock *sk,
				काष्ठा sk_buff *skb)
अणु
	व्योम (*edemux)(काष्ठा sk_buff *skb);

	अगर (net->ipv4.sysctl_ip_early_demux && !skb_dst(skb) && skb->sk == शून्य) अणु
		स्थिर काष्ठा inet6_protocol *ipprot;

		ipprot = rcu_dereference(inet6_protos[ipv6_hdr(skb)->nexthdr]);
		अगर (ipprot && (edemux = READ_ONCE(ipprot->early_demux)))
			INसूचीECT_CALL_2(edemux, tcp_v6_early_demux,
					udp_v6_early_demux, skb);
	पूर्ण
	अगर (!skb_valid_dst(skb))
		ip6_route_input(skb);
पूर्ण

पूर्णांक ip6_rcv_finish(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	/* अगर ingress device is enslaved to an L3 master device pass the
	 * skb to its handler क्रम processing
	 */
	skb = l3mdev_ip6_rcv(skb);
	अगर (!skb)
		वापस NET_RX_SUCCESS;
	ip6_rcv_finish_core(net, sk, skb);

	वापस dst_input(skb);
पूर्ण

अटल व्योम ip6_sublist_rcv_finish(काष्ठा list_head *head)
अणु
	काष्ठा sk_buff *skb, *next;

	list_क्रम_each_entry_safe(skb, next, head, list) अणु
		skb_list_del_init(skb);
		dst_input(skb);
	पूर्ण
पूर्ण

अटल bool ip6_can_use_hपूर्णांक(स्थिर काष्ठा sk_buff *skb,
			     स्थिर काष्ठा sk_buff *hपूर्णांक)
अणु
	वापस hपूर्णांक && !skb_dst(skb) &&
	       ipv6_addr_equal(&ipv6_hdr(hपूर्णांक)->daddr, &ipv6_hdr(skb)->daddr);
पूर्ण

अटल काष्ठा sk_buff *ip6_extract_route_hपूर्णांक(स्थिर काष्ठा net *net,
					      काष्ठा sk_buff *skb)
अणु
	अगर (fib6_routes_require_src(net) || fib6_has_custom_rules(net))
		वापस शून्य;

	वापस skb;
पूर्ण

अटल व्योम ip6_list_rcv_finish(काष्ठा net *net, काष्ठा sock *sk,
				काष्ठा list_head *head)
अणु
	काष्ठा sk_buff *skb, *next, *hपूर्णांक = शून्य;
	काष्ठा dst_entry *curr_dst = शून्य;
	काष्ठा list_head sublist;

	INIT_LIST_HEAD(&sublist);
	list_क्रम_each_entry_safe(skb, next, head, list) अणु
		काष्ठा dst_entry *dst;

		skb_list_del_init(skb);
		/* अगर ingress device is enslaved to an L3 master device pass the
		 * skb to its handler क्रम processing
		 */
		skb = l3mdev_ip6_rcv(skb);
		अगर (!skb)
			जारी;

		अगर (ip6_can_use_hपूर्णांक(skb, hपूर्णांक))
			skb_dst_copy(skb, hपूर्णांक);
		अन्यथा
			ip6_rcv_finish_core(net, sk, skb);
		dst = skb_dst(skb);
		अगर (curr_dst != dst) अणु
			hपूर्णांक = ip6_extract_route_hपूर्णांक(net, skb);

			/* dispatch old sublist */
			अगर (!list_empty(&sublist))
				ip6_sublist_rcv_finish(&sublist);
			/* start new sublist */
			INIT_LIST_HEAD(&sublist);
			curr_dst = dst;
		पूर्ण
		list_add_tail(&skb->list, &sublist);
	पूर्ण
	/* dispatch final sublist */
	ip6_sublist_rcv_finish(&sublist);
पूर्ण

अटल काष्ठा sk_buff *ip6_rcv_core(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				    काष्ठा net *net)
अणु
	स्थिर काष्ठा ipv6hdr *hdr;
	u32 pkt_len;
	काष्ठा inet6_dev *idev;

	अगर (skb->pkt_type == PACKET_OTHERHOST) अणु
		kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण

	rcu_पढ़ो_lock();

	idev = __in6_dev_get(skb->dev);

	__IP6_UPD_PO_STATS(net, idev, IPSTATS_MIB_IN, skb->len);

	अगर ((skb = skb_share_check(skb, GFP_ATOMIC)) == शून्य ||
	    !idev || unlikely(idev->cnf.disable_ipv6)) अणु
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INDISCARDS);
		जाओ drop;
	पूर्ण

	स_रखो(IP6CB(skb), 0, माप(काष्ठा inet6_skb_parm));

	/*
	 * Store incoming device index. When the packet will
	 * be queued, we cannot refer to skb->dev anymore.
	 *
	 * BTW, when we send a packet क्रम our own local address on a
	 * non-loopback पूर्णांकerface (e.g. ethX), it is being delivered
	 * via the loopback पूर्णांकerface (lo) here; skb->dev = loopback_dev.
	 * It, however, should be considered as अगर it is being
	 * arrived via the sending पूर्णांकerface (ethX), because of the
	 * nature of scoping architecture. --yoshfuji
	 */
	IP6CB(skb)->iअगर = skb_valid_dst(skb) ? ip6_dst_idev(skb_dst(skb))->dev->अगरindex : dev->अगरindex;

	अगर (unlikely(!pskb_may_pull(skb, माप(*hdr))))
		जाओ err;

	hdr = ipv6_hdr(skb);

	अगर (hdr->version != 6)
		जाओ err;

	__IP6_ADD_STATS(net, idev,
			IPSTATS_MIB_NOECTPKTS +
				(ipv6_get_dsfield(hdr) & INET_ECN_MASK),
			max_t(अचिन्हित लघु, 1, skb_shinfo(skb)->gso_segs));
	/*
	 * RFC4291 2.5.3
	 * The loopback address must not be used as the source address in IPv6
	 * packets that are sent outside of a single node. [..]
	 * A packet received on an पूर्णांकerface with a destination address
	 * of loopback must be dropped.
	 */
	अगर ((ipv6_addr_loopback(&hdr->saddr) ||
	     ipv6_addr_loopback(&hdr->daddr)) &&
	    !(dev->flags & IFF_LOOPBACK) &&
	    !netअगर_is_l3_master(dev))
		जाओ err;

	/* RFC4291 Errata ID: 3480
	 * Interface-Local scope spans only a single पूर्णांकerface on a
	 * node and is useful only क्रम loopback transmission of
	 * multicast.  Packets with पूर्णांकerface-local scope received
	 * from another node must be discarded.
	 */
	अगर (!(skb->pkt_type == PACKET_LOOPBACK ||
	      dev->flags & IFF_LOOPBACK) &&
	    ipv6_addr_is_multicast(&hdr->daddr) &&
	    IPV6_ADDR_MC_SCOPE(&hdr->daddr) == 1)
		जाओ err;

	/* If enabled, drop unicast packets that were encapsulated in link-layer
	 * multicast or broadcast to रक्षित against the so-called "hole-196"
	 * attack in 802.11 wireless.
	 */
	अगर (!ipv6_addr_is_multicast(&hdr->daddr) &&
	    (skb->pkt_type == PACKET_BROADCAST ||
	     skb->pkt_type == PACKET_MULTICAST) &&
	    idev->cnf.drop_unicast_in_l2_multicast)
		जाओ err;

	/* RFC4291 2.7
	 * Nodes must not originate a packet to a multicast address whose scope
	 * field contains the reserved value 0; अगर such a packet is received, it
	 * must be silently dropped.
	 */
	अगर (ipv6_addr_is_multicast(&hdr->daddr) &&
	    IPV6_ADDR_MC_SCOPE(&hdr->daddr) == 0)
		जाओ err;

	/*
	 * RFC4291 2.7
	 * Multicast addresses must not be used as source addresses in IPv6
	 * packets or appear in any Routing header.
	 */
	अगर (ipv6_addr_is_multicast(&hdr->saddr))
		जाओ err;

	skb->transport_header = skb->network_header + माप(*hdr);
	IP6CB(skb)->nhoff = दुरत्व(काष्ठा ipv6hdr, nexthdr);

	pkt_len = ntohs(hdr->payload_len);

	/* pkt_len may be zero अगर Jumbo payload option is present */
	अगर (pkt_len || hdr->nexthdr != NEXTHDR_HOP) अणु
		अगर (pkt_len + माप(काष्ठा ipv6hdr) > skb->len) अणु
			__IP6_INC_STATS(net,
					idev, IPSTATS_MIB_INTRUNCATEDPKTS);
			जाओ drop;
		पूर्ण
		अगर (pskb_trim_rcsum(skb, pkt_len + माप(काष्ठा ipv6hdr))) अणु
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
			जाओ drop;
		पूर्ण
		hdr = ipv6_hdr(skb);
	पूर्ण

	अगर (hdr->nexthdr == NEXTHDR_HOP) अणु
		अगर (ipv6_parse_hopopts(skb) < 0) अणु
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
			rcu_पढ़ो_unlock();
			वापस शून्य;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	/* Must drop socket now because of tproxy. */
	अगर (!skb_sk_is_prefetched(skb))
		skb_orphan(skb);

	वापस skb;
err:
	__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
drop:
	rcu_पढ़ो_unlock();
	kमुक्त_skb(skb);
	वापस शून्य;
पूर्ण

पूर्णांक ipv6_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev, काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	काष्ठा net *net = dev_net(skb->dev);

	skb = ip6_rcv_core(skb, dev, net);
	अगर (skb == शून्य)
		वापस NET_RX_DROP;
	वापस NF_HOOK(NFPROTO_IPV6, NF_INET_PRE_ROUTING,
		       net, शून्य, skb, dev, शून्य,
		       ip6_rcv_finish);
पूर्ण

अटल व्योम ip6_sublist_rcv(काष्ठा list_head *head, काष्ठा net_device *dev,
			    काष्ठा net *net)
अणु
	NF_HOOK_LIST(NFPROTO_IPV6, NF_INET_PRE_ROUTING, net, शून्य,
		     head, dev, शून्य, ip6_rcv_finish);
	ip6_list_rcv_finish(net, शून्य, head);
पूर्ण

/* Receive a list of IPv6 packets */
व्योम ipv6_list_rcv(काष्ठा list_head *head, काष्ठा packet_type *pt,
		   काष्ठा net_device *orig_dev)
अणु
	काष्ठा net_device *curr_dev = शून्य;
	काष्ठा net *curr_net = शून्य;
	काष्ठा sk_buff *skb, *next;
	काष्ठा list_head sublist;

	INIT_LIST_HEAD(&sublist);
	list_क्रम_each_entry_safe(skb, next, head, list) अणु
		काष्ठा net_device *dev = skb->dev;
		काष्ठा net *net = dev_net(dev);

		skb_list_del_init(skb);
		skb = ip6_rcv_core(skb, dev, net);
		अगर (skb == शून्य)
			जारी;

		अगर (curr_dev != dev || curr_net != net) अणु
			/* dispatch old sublist */
			अगर (!list_empty(&sublist))
				ip6_sublist_rcv(&sublist, curr_dev, curr_net);
			/* start new sublist */
			INIT_LIST_HEAD(&sublist);
			curr_dev = dev;
			curr_net = net;
		पूर्ण
		list_add_tail(&skb->list, &sublist);
	पूर्ण
	/* dispatch final sublist */
	अगर (!list_empty(&sublist))
		ip6_sublist_rcv(&sublist, curr_dev, curr_net);
पूर्ण

INसूचीECT_CALLABLE_DECLARE(पूर्णांक tcp_v6_rcv(काष्ठा sk_buff *));

/*
 *	Deliver the packet to the host
 */
व्योम ip6_protocol_deliver_rcu(काष्ठा net *net, काष्ठा sk_buff *skb, पूर्णांक nexthdr,
			      bool have_final)
अणु
	स्थिर काष्ठा inet6_protocol *ipprot;
	काष्ठा inet6_dev *idev;
	अचिन्हित पूर्णांक nhoff;
	bool raw;

	/*
	 *	Parse extension headers
	 */

resubmit:
	idev = ip6_dst_idev(skb_dst(skb));
	nhoff = IP6CB(skb)->nhoff;
	अगर (!have_final) अणु
		अगर (!pskb_pull(skb, skb_transport_offset(skb)))
			जाओ discard;
		nexthdr = skb_network_header(skb)[nhoff];
	पूर्ण

resubmit_final:
	raw = raw6_local_deliver(skb, nexthdr);
	ipprot = rcu_dereference(inet6_protos[nexthdr]);
	अगर (ipprot) अणु
		पूर्णांक ret;

		अगर (have_final) अणु
			अगर (!(ipprot->flags & INET6_PROTO_FINAL)) अणु
				/* Once we've seen a final protocol don't
				 * allow encapsulation on any non-final
				 * ones. This allows foo in UDP encapsulation
				 * to work.
				 */
				जाओ discard;
			पूर्ण
		पूर्ण अन्यथा अगर (ipprot->flags & INET6_PROTO_FINAL) अणु
			स्थिर काष्ठा ipv6hdr *hdr;
			पूर्णांक sdअगर = inet6_sdअगर(skb);
			काष्ठा net_device *dev;

			/* Only करो this once क्रम first final protocol */
			have_final = true;

			/* Free reference early: we करोn't need it any more,
			   and it may hold ip_conntrack module loaded
			   indefinitely. */
			nf_reset_ct(skb);

			skb_postpull_rcsum(skb, skb_network_header(skb),
					   skb_network_header_len(skb));
			hdr = ipv6_hdr(skb);

			/* skb->dev passed may be master dev क्रम vrfs. */
			अगर (sdअगर) अणु
				dev = dev_get_by_index_rcu(net, sdअगर);
				अगर (!dev)
					जाओ discard;
			पूर्ण अन्यथा अणु
				dev = skb->dev;
			पूर्ण

			अगर (ipv6_addr_is_multicast(&hdr->daddr) &&
			    !ipv6_chk_mcast_addr(dev, &hdr->daddr,
						 &hdr->saddr) &&
			    !ipv6_is_mld(skb, nexthdr, skb_network_header_len(skb)))
				जाओ discard;
		पूर्ण
		अगर (!(ipprot->flags & INET6_PROTO_NOPOLICY) &&
		    !xfrm6_policy_check(शून्य, XFRM_POLICY_IN, skb))
			जाओ discard;

		ret = INसूचीECT_CALL_2(ipprot->handler, tcp_v6_rcv, udpv6_rcv,
				      skb);
		अगर (ret > 0) अणु
			अगर (ipprot->flags & INET6_PROTO_FINAL) अणु
				/* Not an extension header, most likely UDP
				 * encapsulation. Use वापस value as nexthdr
				 * protocol not nhoff (which presumably is
				 * not set by handler).
				 */
				nexthdr = ret;
				जाओ resubmit_final;
			पूर्ण अन्यथा अणु
				जाओ resubmit;
			पूर्ण
		पूर्ण अन्यथा अगर (ret == 0) अणु
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INDELIVERS);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!raw) अणु
			अगर (xfrm6_policy_check(शून्य, XFRM_POLICY_IN, skb)) अणु
				__IP6_INC_STATS(net, idev,
						IPSTATS_MIB_INUNKNOWNPROTOS);
				icmpv6_send(skb, ICMPV6_PARAMPROB,
					    ICMPV6_UNK_NEXTHDR, nhoff);
			पूर्ण
			kमुक्त_skb(skb);
		पूर्ण अन्यथा अणु
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INDELIVERS);
			consume_skb(skb);
		पूर्ण
	पूर्ण
	वापस;

discard:
	__IP6_INC_STATS(net, idev, IPSTATS_MIB_INDISCARDS);
	kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक ip6_input_finish(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	rcu_पढ़ो_lock();
	ip6_protocol_deliver_rcu(net, skb, 0, false);
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण


पूर्णांक ip6_input(काष्ठा sk_buff *skb)
अणु
	वापस NF_HOOK(NFPROTO_IPV6, NF_INET_LOCAL_IN,
		       dev_net(skb->dev), शून्य, skb, skb->dev, शून्य,
		       ip6_input_finish);
पूर्ण
EXPORT_SYMBOL_GPL(ip6_input);

पूर्णांक ip6_mc_input(काष्ठा sk_buff *skb)
अणु
	पूर्णांक sdअगर = inet6_sdअगर(skb);
	स्थिर काष्ठा ipv6hdr *hdr;
	काष्ठा net_device *dev;
	bool deliver;

	__IP6_UPD_PO_STATS(dev_net(skb_dst(skb)->dev),
			 __in6_dev_get_safely(skb->dev), IPSTATS_MIB_INMCAST,
			 skb->len);

	/* skb->dev passed may be master dev क्रम vrfs. */
	अगर (sdअगर) अणु
		rcu_पढ़ो_lock();
		dev = dev_get_by_index_rcu(dev_net(skb->dev), sdअगर);
		अगर (!dev) अणु
			rcu_पढ़ो_unlock();
			kमुक्त_skb(skb);
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev = skb->dev;
	पूर्ण

	hdr = ipv6_hdr(skb);
	deliver = ipv6_chk_mcast_addr(dev, &hdr->daddr, शून्य);
	अगर (sdअगर)
		rcu_पढ़ो_unlock();

#अगर_घोषित CONFIG_IPV6_MROUTE
	/*
	 *      IPv6 multicast router mode is now supported ;)
	 */
	अगर (dev_net(skb->dev)->ipv6.devconf_all->mc_क्रमwarding &&
	    !(ipv6_addr_type(&hdr->daddr) &
	      (IPV6_ADDR_LOOPBACK|IPV6_ADDR_LINKLOCAL)) &&
	    likely(!(IP6CB(skb)->flags & IP6SKB_FORWARDED))) अणु
		/*
		 * Okay, we try to क्रमward - split and duplicate
		 * packets.
		 */
		काष्ठा sk_buff *skb2;
		काष्ठा inet6_skb_parm *opt = IP6CB(skb);

		/* Check क्रम MLD */
		अगर (unlikely(opt->flags & IP6SKB_ROUTERALERT)) अणु
			/* Check अगर this is a mld message */
			u8 nexthdr = hdr->nexthdr;
			__be16 frag_off;
			पूर्णांक offset;

			/* Check अगर the value of Router Alert
			 * is क्रम MLD (0x0000).
			 */
			अगर (opt->ra == htons(IPV6_OPT_ROUTERALERT_MLD)) अणु
				deliver = false;

				अगर (!ipv6_ext_hdr(nexthdr)) अणु
					/* BUG */
					जाओ out;
				पूर्ण
				offset = ipv6_skip_exthdr(skb, माप(*hdr),
							  &nexthdr, &frag_off);
				अगर (offset < 0)
					जाओ out;

				अगर (ipv6_is_mld(skb, nexthdr, offset))
					deliver = true;

				जाओ out;
			पूर्ण
			/* unknown RA - process it normally */
		पूर्ण

		अगर (deliver)
			skb2 = skb_clone(skb, GFP_ATOMIC);
		अन्यथा अणु
			skb2 = skb;
			skb = शून्य;
		पूर्ण

		अगर (skb2) अणु
			ip6_mr_input(skb2);
		पूर्ण
	पूर्ण
out:
#पूर्ण_अगर
	अगर (likely(deliver))
		ip6_input(skb);
	अन्यथा अणु
		/* discard */
		kमुक्त_skb(skb);
	पूर्ण

	वापस 0;
पूर्ण
