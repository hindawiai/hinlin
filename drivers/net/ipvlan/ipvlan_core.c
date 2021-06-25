<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Copyright (c) 2014 Mahesh Bandewar <maheshb@google.com>
 */

#समावेश "ipvlan.h"

अटल u32 ipvlan_jhash_secret __पढ़ो_mostly;

व्योम ipvlan_init_secret(व्योम)
अणु
	net_get_अक्रमom_once(&ipvlan_jhash_secret, माप(ipvlan_jhash_secret));
पूर्ण

व्योम ipvlan_count_rx(स्थिर काष्ठा ipvl_dev *ipvlan,
			    अचिन्हित पूर्णांक len, bool success, bool mcast)
अणु
	अगर (likely(success)) अणु
		काष्ठा ipvl_pcpu_stats *pcptr;

		pcptr = this_cpu_ptr(ipvlan->pcpu_stats);
		u64_stats_update_begin(&pcptr->syncp);
		pcptr->rx_pkts++;
		pcptr->rx_bytes += len;
		अगर (mcast)
			pcptr->rx_mcast++;
		u64_stats_update_end(&pcptr->syncp);
	पूर्ण अन्यथा अणु
		this_cpu_inc(ipvlan->pcpu_stats->rx_errs);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ipvlan_count_rx);

#अगर IS_ENABLED(CONFIG_IPV6)
अटल u8 ipvlan_get_v6_hash(स्थिर व्योम *iaddr)
अणु
	स्थिर काष्ठा in6_addr *ip6_addr = iaddr;

	वापस __ipv6_addr_jhash(ip6_addr, ipvlan_jhash_secret) &
	       IPVLAN_HASH_MASK;
पूर्ण
#अन्यथा
अटल u8 ipvlan_get_v6_hash(स्थिर व्योम *iaddr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल u8 ipvlan_get_v4_hash(स्थिर व्योम *iaddr)
अणु
	स्थिर काष्ठा in_addr *ip4_addr = iaddr;

	वापस jhash_1word(ip4_addr->s_addr, ipvlan_jhash_secret) &
	       IPVLAN_HASH_MASK;
पूर्ण

अटल bool addr_equal(bool is_v6, काष्ठा ipvl_addr *addr, स्थिर व्योम *iaddr)
अणु
	अगर (!is_v6 && addr->atype == IPVL_IPV4) अणु
		काष्ठा in_addr *i4addr = (काष्ठा in_addr *)iaddr;

		वापस addr->ip4addr.s_addr == i4addr->s_addr;
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (is_v6 && addr->atype == IPVL_IPV6) अणु
		काष्ठा in6_addr *i6addr = (काष्ठा in6_addr *)iaddr;

		वापस ipv6_addr_equal(&addr->ip6addr, i6addr);
#पूर्ण_अगर
	पूर्ण

	वापस false;
पूर्ण

अटल काष्ठा ipvl_addr *ipvlan_ht_addr_lookup(स्थिर काष्ठा ipvl_port *port,
					       स्थिर व्योम *iaddr, bool is_v6)
अणु
	काष्ठा ipvl_addr *addr;
	u8 hash;

	hash = is_v6 ? ipvlan_get_v6_hash(iaddr) :
	       ipvlan_get_v4_hash(iaddr);
	hlist_क्रम_each_entry_rcu(addr, &port->hlhead[hash], hlnode)
		अगर (addr_equal(is_v6, addr, iaddr))
			वापस addr;
	वापस शून्य;
पूर्ण

व्योम ipvlan_ht_addr_add(काष्ठा ipvl_dev *ipvlan, काष्ठा ipvl_addr *addr)
अणु
	काष्ठा ipvl_port *port = ipvlan->port;
	u8 hash;

	hash = (addr->atype == IPVL_IPV6) ?
	       ipvlan_get_v6_hash(&addr->ip6addr) :
	       ipvlan_get_v4_hash(&addr->ip4addr);
	अगर (hlist_unhashed(&addr->hlnode))
		hlist_add_head_rcu(&addr->hlnode, &port->hlhead[hash]);
पूर्ण

व्योम ipvlan_ht_addr_del(काष्ठा ipvl_addr *addr)
अणु
	hlist_del_init_rcu(&addr->hlnode);
पूर्ण

काष्ठा ipvl_addr *ipvlan_find_addr(स्थिर काष्ठा ipvl_dev *ipvlan,
				   स्थिर व्योम *iaddr, bool is_v6)
अणु
	काष्ठा ipvl_addr *addr, *ret = शून्य;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(addr, &ipvlan->addrs, anode) अणु
		अगर (addr_equal(is_v6, addr, iaddr)) अणु
			ret = addr;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

bool ipvlan_addr_busy(काष्ठा ipvl_port *port, व्योम *iaddr, bool is_v6)
अणु
	काष्ठा ipvl_dev *ipvlan;
	bool ret = false;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ipvlan, &port->ipvlans, pnode) अणु
		अगर (ipvlan_find_addr(ipvlan, iaddr, is_v6)) अणु
			ret = true;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

व्योम *ipvlan_get_L3_hdr(काष्ठा ipvl_port *port, काष्ठा sk_buff *skb, पूर्णांक *type)
अणु
	व्योम *lyr3h = शून्य;

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_ARP): अणु
		काष्ठा arphdr *arph;

		अगर (unlikely(!pskb_may_pull(skb, arp_hdr_len(port->dev))))
			वापस शून्य;

		arph = arp_hdr(skb);
		*type = IPVL_ARP;
		lyr3h = arph;
		अवरोध;
	पूर्ण
	हाल htons(ETH_P_IP): अणु
		u32 pktlen;
		काष्ठा iphdr *ip4h;

		अगर (unlikely(!pskb_may_pull(skb, माप(*ip4h))))
			वापस शून्य;

		ip4h = ip_hdr(skb);
		pktlen = ntohs(ip4h->tot_len);
		अगर (ip4h->ihl < 5 || ip4h->version != 4)
			वापस शून्य;
		अगर (skb->len < pktlen || pktlen < (ip4h->ihl * 4))
			वापस शून्य;

		*type = IPVL_IPV4;
		lyr3h = ip4h;
		अवरोध;
	पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल htons(ETH_P_IPV6): अणु
		काष्ठा ipv6hdr *ip6h;

		अगर (unlikely(!pskb_may_pull(skb, माप(*ip6h))))
			वापस शून्य;

		ip6h = ipv6_hdr(skb);
		अगर (ip6h->version != 6)
			वापस शून्य;

		*type = IPVL_IPV6;
		lyr3h = ip6h;
		/* Only Neighbour Solicitation pkts need dअगरferent treaपंचांगent */
		अगर (ipv6_addr_any(&ip6h->saddr) &&
		    ip6h->nexthdr == NEXTHDR_ICMP) अणु
			काष्ठा icmp6hdr	*icmph;

			अगर (unlikely(!pskb_may_pull(skb, माप(*ip6h) + माप(*icmph))))
				वापस शून्य;

			ip6h = ipv6_hdr(skb);
			icmph = (काष्ठा icmp6hdr *)(ip6h + 1);

			अगर (icmph->icmp6_type == NDISC_NEIGHBOUR_SOLICITATION) अणु
				/* Need to access the ipv6 address in body */
				अगर (unlikely(!pskb_may_pull(skb, माप(*ip6h) + माप(*icmph)
						+ माप(काष्ठा in6_addr))))
					वापस शून्य;

				ip6h = ipv6_hdr(skb);
				icmph = (काष्ठा icmp6hdr *)(ip6h + 1);
			पूर्ण

			*type = IPVL_ICMPV6;
			lyr3h = icmph;
		पूर्ण
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	शेष:
		वापस शून्य;
	पूर्ण

	वापस lyr3h;
पूर्ण

अचिन्हित पूर्णांक ipvlan_mac_hash(स्थिर अचिन्हित अक्षर *addr)
अणु
	u32 hash = jhash_1word(__get_unaligned_cpu32(addr+2),
			       ipvlan_jhash_secret);

	वापस hash & IPVLAN_MAC_FILTER_MASK;
पूर्ण

व्योम ipvlan_process_multicast(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipvl_port *port = container_of(work, काष्ठा ipvl_port, wq);
	काष्ठा ethhdr *ethh;
	काष्ठा ipvl_dev *ipvlan;
	काष्ठा sk_buff *skb, *nskb;
	काष्ठा sk_buff_head list;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक mac_hash;
	पूर्णांक ret;
	u8 pkt_type;
	bool tx_pkt;

	__skb_queue_head_init(&list);

	spin_lock_bh(&port->backlog.lock);
	skb_queue_splice_tail_init(&port->backlog, &list);
	spin_unlock_bh(&port->backlog.lock);

	जबतक ((skb = __skb_dequeue(&list)) != शून्य) अणु
		काष्ठा net_device *dev = skb->dev;
		bool consumed = false;

		ethh = eth_hdr(skb);
		tx_pkt = IPVL_SKB_CB(skb)->tx_pkt;
		mac_hash = ipvlan_mac_hash(ethh->h_dest);

		अगर (ether_addr_equal(ethh->h_dest, port->dev->broadcast))
			pkt_type = PACKET_BROADCAST;
		अन्यथा
			pkt_type = PACKET_MULTICAST;

		rcu_पढ़ो_lock();
		list_क्रम_each_entry_rcu(ipvlan, &port->ipvlans, pnode) अणु
			अगर (tx_pkt && (ipvlan->dev == skb->dev))
				जारी;
			अगर (!test_bit(mac_hash, ipvlan->mac_filters))
				जारी;
			अगर (!(ipvlan->dev->flags & IFF_UP))
				जारी;
			ret = NET_RX_DROP;
			len = skb->len + ETH_HLEN;
			nskb = skb_clone(skb, GFP_ATOMIC);
			local_bh_disable();
			अगर (nskb) अणु
				consumed = true;
				nskb->pkt_type = pkt_type;
				nskb->dev = ipvlan->dev;
				अगर (tx_pkt)
					ret = dev_क्रमward_skb(ipvlan->dev, nskb);
				अन्यथा
					ret = netअगर_rx(nskb);
			पूर्ण
			ipvlan_count_rx(ipvlan, len, ret == NET_RX_SUCCESS, true);
			local_bh_enable();
		पूर्ण
		rcu_पढ़ो_unlock();

		अगर (tx_pkt) अणु
			/* If the packet originated here, send it out. */
			skb->dev = port->dev;
			skb->pkt_type = pkt_type;
			dev_queue_xmit(skb);
		पूर्ण अन्यथा अणु
			अगर (consumed)
				consume_skb(skb);
			अन्यथा
				kमुक्त_skb(skb);
		पूर्ण
		अगर (dev)
			dev_put(dev);
		cond_resched();
	पूर्ण
पूर्ण

अटल व्योम ipvlan_skb_crossing_ns(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	bool xnet = true;

	अगर (dev)
		xnet = !net_eq(dev_net(skb->dev), dev_net(dev));

	skb_scrub_packet(skb, xnet);
	अगर (dev)
		skb->dev = dev;
पूर्ण

अटल पूर्णांक ipvlan_rcv_frame(काष्ठा ipvl_addr *addr, काष्ठा sk_buff **pskb,
			    bool local)
अणु
	काष्ठा ipvl_dev *ipvlan = addr->master;
	काष्ठा net_device *dev = ipvlan->dev;
	अचिन्हित पूर्णांक len;
	rx_handler_result_t ret = RX_HANDLER_CONSUMED;
	bool success = false;
	काष्ठा sk_buff *skb = *pskb;

	len = skb->len + ETH_HLEN;
	/* Only packets exchanged between two local slaves need to have
	 * device-up check as well as skb-share check.
	 */
	अगर (local) अणु
		अगर (unlikely(!(dev->flags & IFF_UP))) अणु
			kमुक्त_skb(skb);
			जाओ out;
		पूर्ण

		skb = skb_share_check(skb, GFP_ATOMIC);
		अगर (!skb)
			जाओ out;

		*pskb = skb;
	पूर्ण

	अगर (local) अणु
		skb->pkt_type = PACKET_HOST;
		अगर (dev_क्रमward_skb(ipvlan->dev, skb) == NET_RX_SUCCESS)
			success = true;
	पूर्ण अन्यथा अणु
		skb->dev = dev;
		ret = RX_HANDLER_ANOTHER;
		success = true;
	पूर्ण

out:
	ipvlan_count_rx(ipvlan, len, success, false);
	वापस ret;
पूर्ण

काष्ठा ipvl_addr *ipvlan_addr_lookup(काष्ठा ipvl_port *port, व्योम *lyr3h,
				     पूर्णांक addr_type, bool use_dest)
अणु
	काष्ठा ipvl_addr *addr = शून्य;

	चयन (addr_type) अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल IPVL_IPV6: अणु
		काष्ठा ipv6hdr *ip6h;
		काष्ठा in6_addr *i6addr;

		ip6h = (काष्ठा ipv6hdr *)lyr3h;
		i6addr = use_dest ? &ip6h->daddr : &ip6h->saddr;
		addr = ipvlan_ht_addr_lookup(port, i6addr, true);
		अवरोध;
	पूर्ण
	हाल IPVL_ICMPV6: अणु
		काष्ठा nd_msg *ndmh;
		काष्ठा in6_addr *i6addr;

		/* Make sure that the NeighborSolicitation ICMPv6 packets
		 * are handled to aव्योम DAD issue.
		 */
		ndmh = (काष्ठा nd_msg *)lyr3h;
		अगर (ndmh->icmph.icmp6_type == NDISC_NEIGHBOUR_SOLICITATION) अणु
			i6addr = &ndmh->target;
			addr = ipvlan_ht_addr_lookup(port, i6addr, true);
		पूर्ण
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	हाल IPVL_IPV4: अणु
		काष्ठा iphdr *ip4h;
		__be32 *i4addr;

		ip4h = (काष्ठा iphdr *)lyr3h;
		i4addr = use_dest ? &ip4h->daddr : &ip4h->saddr;
		addr = ipvlan_ht_addr_lookup(port, i4addr, false);
		अवरोध;
	पूर्ण
	हाल IPVL_ARP: अणु
		काष्ठा arphdr *arph;
		अचिन्हित अक्षर *arp_ptr;
		__be32 dip;

		arph = (काष्ठा arphdr *)lyr3h;
		arp_ptr = (अचिन्हित अक्षर *)(arph + 1);
		अगर (use_dest)
			arp_ptr += (2 * port->dev->addr_len) + 4;
		अन्यथा
			arp_ptr += port->dev->addr_len;

		स_नकल(&dip, arp_ptr, 4);
		addr = ipvlan_ht_addr_lookup(port, &dip, false);
		अवरोध;
	पूर्ण
	पूर्ण

	वापस addr;
पूर्ण

अटल पूर्णांक ipvlan_process_v4_outbound(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा iphdr *ip4h = ip_hdr(skb);
	काष्ठा net_device *dev = skb->dev;
	काष्ठा net *net = dev_net(dev);
	काष्ठा rtable *rt;
	पूर्णांक err, ret = NET_XMIT_DROP;
	काष्ठा flowi4 fl4 = अणु
		.flowi4_oअगर = dev->अगरindex,
		.flowi4_tos = RT_TOS(ip4h->tos),
		.flowi4_flags = FLOWI_FLAG_ANYSRC,
		.flowi4_mark = skb->mark,
		.daddr = ip4h->daddr,
		.saddr = ip4h->saddr,
	पूर्ण;

	rt = ip_route_output_flow(net, &fl4, शून्य);
	अगर (IS_ERR(rt))
		जाओ err;

	अगर (rt->rt_type != RTN_UNICAST && rt->rt_type != RTN_LOCAL) अणु
		ip_rt_put(rt);
		जाओ err;
	पूर्ण
	skb_dst_set(skb, &rt->dst);
	err = ip_local_out(net, skb->sk, skb);
	अगर (unlikely(net_xmit_eval(err)))
		dev->stats.tx_errors++;
	अन्यथा
		ret = NET_XMIT_SUCCESS;
	जाओ out;
err:
	dev->stats.tx_errors++;
	kमुक्त_skb(skb);
out:
	वापस ret;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक ipvlan_process_v6_outbound(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);
	काष्ठा net_device *dev = skb->dev;
	काष्ठा net *net = dev_net(dev);
	काष्ठा dst_entry *dst;
	पूर्णांक err, ret = NET_XMIT_DROP;
	काष्ठा flowi6 fl6 = अणु
		.flowi6_oअगर = dev->अगरindex,
		.daddr = ip6h->daddr,
		.saddr = ip6h->saddr,
		.flowi6_flags = FLOWI_FLAG_ANYSRC,
		.flowlabel = ip6_flowinfo(ip6h),
		.flowi6_mark = skb->mark,
		.flowi6_proto = ip6h->nexthdr,
	पूर्ण;

	dst = ip6_route_output(net, शून्य, &fl6);
	अगर (dst->error) अणु
		ret = dst->error;
		dst_release(dst);
		जाओ err;
	पूर्ण
	skb_dst_set(skb, dst);
	err = ip6_local_out(net, skb->sk, skb);
	अगर (unlikely(net_xmit_eval(err)))
		dev->stats.tx_errors++;
	अन्यथा
		ret = NET_XMIT_SUCCESS;
	जाओ out;
err:
	dev->stats.tx_errors++;
	kमुक्त_skb(skb);
out:
	वापस ret;
पूर्ण
#अन्यथा
अटल पूर्णांक ipvlan_process_v6_outbound(काष्ठा sk_buff *skb)
अणु
	वापस NET_XMIT_DROP;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ipvlan_process_outbound(काष्ठा sk_buff *skb)
अणु
	काष्ठा ethhdr *ethh = eth_hdr(skb);
	पूर्णांक ret = NET_XMIT_DROP;

	/* The ipvlan is a pseuकरो-L2 device, so the packets that we receive
	 * will have L2; which need to discarded and processed further
	 * in the net-ns of the मुख्य-device.
	 */
	अगर (skb_mac_header_was_set(skb)) अणु
		/* In this mode we करोnt care about
		 * multicast and broadcast traffic */
		अगर (is_multicast_ether_addr(ethh->h_dest)) अणु
			pr_debug_ratelimited(
				"Dropped {multi|broad}cast of type=[%x]\n",
				ntohs(skb->protocol));
			kमुक्त_skb(skb);
			जाओ out;
		पूर्ण

		skb_pull(skb, माप(*ethh));
		skb->mac_header = (typeof(skb->mac_header))~0U;
		skb_reset_network_header(skb);
	पूर्ण

	अगर (skb->protocol == htons(ETH_P_IPV6))
		ret = ipvlan_process_v6_outbound(skb);
	अन्यथा अगर (skb->protocol == htons(ETH_P_IP))
		ret = ipvlan_process_v4_outbound(skb);
	अन्यथा अणु
		pr_warn_ratelimited("Dropped outbound packet type=%x\n",
				    ntohs(skb->protocol));
		kमुक्त_skb(skb);
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल व्योम ipvlan_multicast_enqueue(काष्ठा ipvl_port *port,
				     काष्ठा sk_buff *skb, bool tx_pkt)
अणु
	अगर (skb->protocol == htons(ETH_P_PAUSE)) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	/* Record that the deferred packet is from TX or RX path. By
	 * looking at mac-addresses on packet will lead to erronus decisions.
	 * (This would be true क्रम a loopback-mode on master device or a
	 * hair-pin mode of the चयन.)
	 */
	IPVL_SKB_CB(skb)->tx_pkt = tx_pkt;

	spin_lock(&port->backlog.lock);
	अगर (skb_queue_len(&port->backlog) < IPVLAN_QBACKLOG_LIMIT) अणु
		अगर (skb->dev)
			dev_hold(skb->dev);
		__skb_queue_tail(&port->backlog, skb);
		spin_unlock(&port->backlog.lock);
		schedule_work(&port->wq);
	पूर्ण अन्यथा अणु
		spin_unlock(&port->backlog.lock);
		atomic_दीर्घ_inc(&skb->dev->rx_dropped);
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल पूर्णांक ipvlan_xmit_mode_l3(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);
	व्योम *lyr3h;
	काष्ठा ipvl_addr *addr;
	पूर्णांक addr_type;

	lyr3h = ipvlan_get_L3_hdr(ipvlan->port, skb, &addr_type);
	अगर (!lyr3h)
		जाओ out;

	अगर (!ipvlan_is_vepa(ipvlan->port)) अणु
		addr = ipvlan_addr_lookup(ipvlan->port, lyr3h, addr_type, true);
		अगर (addr) अणु
			अगर (ipvlan_is_निजी(ipvlan->port)) अणु
				consume_skb(skb);
				वापस NET_XMIT_DROP;
			पूर्ण
			वापस ipvlan_rcv_frame(addr, &skb, true);
		पूर्ण
	पूर्ण
out:
	ipvlan_skb_crossing_ns(skb, ipvlan->phy_dev);
	वापस ipvlan_process_outbound(skb);
पूर्ण

अटल पूर्णांक ipvlan_xmit_mode_l2(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);
	काष्ठा ethhdr *eth = eth_hdr(skb);
	काष्ठा ipvl_addr *addr;
	व्योम *lyr3h;
	पूर्णांक addr_type;

	अगर (!ipvlan_is_vepa(ipvlan->port) &&
	    ether_addr_equal(eth->h_dest, eth->h_source)) अणु
		lyr3h = ipvlan_get_L3_hdr(ipvlan->port, skb, &addr_type);
		अगर (lyr3h) अणु
			addr = ipvlan_addr_lookup(ipvlan->port, lyr3h, addr_type, true);
			अगर (addr) अणु
				अगर (ipvlan_is_निजी(ipvlan->port)) अणु
					consume_skb(skb);
					वापस NET_XMIT_DROP;
				पूर्ण
				वापस ipvlan_rcv_frame(addr, &skb, true);
			पूर्ण
		पूर्ण
		skb = skb_share_check(skb, GFP_ATOMIC);
		अगर (!skb)
			वापस NET_XMIT_DROP;

		/* Packet definitely करोes not beदीर्घ to any of the
		 * भव devices, but the dest is local. So क्रमward
		 * the skb क्रम the मुख्य-dev. At the RX side we just वापस
		 * RX_PASS क्रम it to be processed further on the stack.
		 */
		वापस dev_क्रमward_skb(ipvlan->phy_dev, skb);

	पूर्ण अन्यथा अगर (is_multicast_ether_addr(eth->h_dest)) अणु
		ipvlan_skb_crossing_ns(skb, शून्य);
		ipvlan_multicast_enqueue(ipvlan->port, skb, true);
		वापस NET_XMIT_SUCCESS;
	पूर्ण

	skb->dev = ipvlan->phy_dev;
	वापस dev_queue_xmit(skb);
पूर्ण

पूर्णांक ipvlan_queue_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);
	काष्ठा ipvl_port *port = ipvlan_port_get_rcu_bh(ipvlan->phy_dev);

	अगर (!port)
		जाओ out;

	अगर (unlikely(!pskb_may_pull(skb, माप(काष्ठा ethhdr))))
		जाओ out;

	चयन(port->mode) अणु
	हाल IPVLAN_MODE_L2:
		वापस ipvlan_xmit_mode_l2(skb, dev);
	हाल IPVLAN_MODE_L3:
#अगर_घोषित CONFIG_IPVLAN_L3S
	हाल IPVLAN_MODE_L3S:
#पूर्ण_अगर
		वापस ipvlan_xmit_mode_l3(skb, dev);
	पूर्ण

	/* Should not reach here */
	WARN_ONCE(true, "%s called for mode = [%x]\n", __func__, port->mode);
out:
	kमुक्त_skb(skb);
	वापस NET_XMIT_DROP;
पूर्ण

अटल bool ipvlan_बाह्यal_frame(काष्ठा sk_buff *skb, काष्ठा ipvl_port *port)
अणु
	काष्ठा ethhdr *eth = eth_hdr(skb);
	काष्ठा ipvl_addr *addr;
	व्योम *lyr3h;
	पूर्णांक addr_type;

	अगर (ether_addr_equal(eth->h_source, skb->dev->dev_addr)) अणु
		lyr3h = ipvlan_get_L3_hdr(port, skb, &addr_type);
		अगर (!lyr3h)
			वापस true;

		addr = ipvlan_addr_lookup(port, lyr3h, addr_type, false);
		अगर (addr)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल rx_handler_result_t ipvlan_handle_mode_l3(काष्ठा sk_buff **pskb,
						 काष्ठा ipvl_port *port)
अणु
	व्योम *lyr3h;
	पूर्णांक addr_type;
	काष्ठा ipvl_addr *addr;
	काष्ठा sk_buff *skb = *pskb;
	rx_handler_result_t ret = RX_HANDLER_PASS;

	lyr3h = ipvlan_get_L3_hdr(port, skb, &addr_type);
	अगर (!lyr3h)
		जाओ out;

	addr = ipvlan_addr_lookup(port, lyr3h, addr_type, true);
	अगर (addr)
		ret = ipvlan_rcv_frame(addr, pskb, false);

out:
	वापस ret;
पूर्ण

अटल rx_handler_result_t ipvlan_handle_mode_l2(काष्ठा sk_buff **pskb,
						 काष्ठा ipvl_port *port)
अणु
	काष्ठा sk_buff *skb = *pskb;
	काष्ठा ethhdr *eth = eth_hdr(skb);
	rx_handler_result_t ret = RX_HANDLER_PASS;

	अगर (is_multicast_ether_addr(eth->h_dest)) अणु
		अगर (ipvlan_बाह्यal_frame(skb, port)) अणु
			काष्ठा sk_buff *nskb = skb_clone(skb, GFP_ATOMIC);

			/* External frames are queued क्रम device local
			 * distribution, but a copy is given to master
			 * straight away to aव्योम sending duplicates later
			 * when work-queue processes this frame. This is
			 * achieved by वापसing RX_HANDLER_PASS.
			 */
			अगर (nskb) अणु
				ipvlan_skb_crossing_ns(nskb, शून्य);
				ipvlan_multicast_enqueue(port, nskb, false);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Perक्रमm like l3 mode क्रम non-multicast packet */
		ret = ipvlan_handle_mode_l3(pskb, port);
	पूर्ण

	वापस ret;
पूर्ण

rx_handler_result_t ipvlan_handle_frame(काष्ठा sk_buff **pskb)
अणु
	काष्ठा sk_buff *skb = *pskb;
	काष्ठा ipvl_port *port = ipvlan_port_get_rcu(skb->dev);

	अगर (!port)
		वापस RX_HANDLER_PASS;

	चयन (port->mode) अणु
	हाल IPVLAN_MODE_L2:
		वापस ipvlan_handle_mode_l2(pskb, port);
	हाल IPVLAN_MODE_L3:
		वापस ipvlan_handle_mode_l3(pskb, port);
#अगर_घोषित CONFIG_IPVLAN_L3S
	हाल IPVLAN_MODE_L3S:
		वापस RX_HANDLER_PASS;
#पूर्ण_अगर
	पूर्ण

	/* Should not reach here */
	WARN_ONCE(true, "%s called for mode = [%x]\n", __func__, port->mode);
	kमुक्त_skb(skb);
	वापस RX_HANDLER_CONSUMED;
पूर्ण
