<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2007 Patrick McHardy <kaber@trash.net>
 *
 * The code this is based on carried the following copyright notice:
 * ---
 * (C) Copyright 2001-2006
 * Alex Zeffertt, Cambridge Broadband Ltd, ajz@cambridgebroadband.com
 * Re-worked by Ben Greear <greearb@candelatech.com>
 * ---
 */
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/rculist.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_link.h>
#समावेश <linux/अगर_macvlan.h>
#समावेश <linux/hash.h>
#समावेश <linux/workqueue.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/xfrm.h>
#समावेश <linux/netpoll.h>
#समावेश <linux/phy.h>

#घोषणा MACVLAN_HASH_BITS	8
#घोषणा MACVLAN_HASH_SIZE	(1<<MACVLAN_HASH_BITS)
#घोषणा MACVLAN_DEFAULT_BC_QUEUE_LEN	1000

#घोषणा MACVLAN_F_PASSTHRU	1
#घोषणा MACVLAN_F_ADDRCHANGE	2

काष्ठा macvlan_port अणु
	काष्ठा net_device	*dev;
	काष्ठा hlist_head	vlan_hash[MACVLAN_HASH_SIZE];
	काष्ठा list_head	vlans;
	काष्ठा sk_buff_head	bc_queue;
	काष्ठा work_काष्ठा	bc_work;
	u32			bc_queue_len_used;
	u32			flags;
	पूर्णांक			count;
	काष्ठा hlist_head	vlan_source_hash[MACVLAN_HASH_SIZE];
	DECLARE_BITMAP(mc_filter, MACVLAN_MC_FILTER_SZ);
	अचिन्हित अक्षर           perm_addr[ETH_ALEN];
पूर्ण;

काष्ठा macvlan_source_entry अणु
	काष्ठा hlist_node	hlist;
	काष्ठा macvlan_dev	*vlan;
	अचिन्हित अक्षर		addr[6+2] __aligned(माप(u16));
	काष्ठा rcu_head		rcu;
पूर्ण;

काष्ठा macvlan_skb_cb अणु
	स्थिर काष्ठा macvlan_dev *src;
पूर्ण;

#घोषणा MACVLAN_SKB_CB(__skb) ((काष्ठा macvlan_skb_cb *)&((__skb)->cb[0]))

अटल व्योम macvlan_port_destroy(काष्ठा net_device *dev);
अटल व्योम update_port_bc_queue_len(काष्ठा macvlan_port *port);

अटल अंतरभूत bool macvlan_passthru(स्थिर काष्ठा macvlan_port *port)
अणु
	वापस port->flags & MACVLAN_F_PASSTHRU;
पूर्ण

अटल अंतरभूत व्योम macvlan_set_passthru(काष्ठा macvlan_port *port)
अणु
	port->flags |= MACVLAN_F_PASSTHRU;
पूर्ण

अटल अंतरभूत bool macvlan_addr_change(स्थिर काष्ठा macvlan_port *port)
अणु
	वापस port->flags & MACVLAN_F_ADDRCHANGE;
पूर्ण

अटल अंतरभूत व्योम macvlan_set_addr_change(काष्ठा macvlan_port *port)
अणु
	port->flags |= MACVLAN_F_ADDRCHANGE;
पूर्ण

अटल अंतरभूत व्योम macvlan_clear_addr_change(काष्ठा macvlan_port *port)
अणु
	port->flags &= ~MACVLAN_F_ADDRCHANGE;
पूर्ण

/* Hash Ethernet address */
अटल u32 macvlan_eth_hash(स्थिर अचिन्हित अक्षर *addr)
अणु
	u64 value = get_unaligned((u64 *)addr);

	/* only want 6 bytes */
#अगर_घोषित __BIG_ENDIAN
	value >>= 16;
#अन्यथा
	value <<= 16;
#पूर्ण_अगर
	वापस hash_64(value, MACVLAN_HASH_BITS);
पूर्ण

अटल काष्ठा macvlan_port *macvlan_port_get_rcu(स्थिर काष्ठा net_device *dev)
अणु
	वापस rcu_dereference(dev->rx_handler_data);
पूर्ण

अटल काष्ठा macvlan_port *macvlan_port_get_rtnl(स्थिर काष्ठा net_device *dev)
अणु
	वापस rtnl_dereference(dev->rx_handler_data);
पूर्ण

अटल काष्ठा macvlan_dev *macvlan_hash_lookup(स्थिर काष्ठा macvlan_port *port,
					       स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा macvlan_dev *vlan;
	u32 idx = macvlan_eth_hash(addr);

	hlist_क्रम_each_entry_rcu(vlan, &port->vlan_hash[idx], hlist,
				 lockdep_rtnl_is_held()) अणु
		अगर (ether_addr_equal_64bits(vlan->dev->dev_addr, addr))
			वापस vlan;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा macvlan_source_entry *macvlan_hash_lookup_source(
	स्थिर काष्ठा macvlan_dev *vlan,
	स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा macvlan_source_entry *entry;
	u32 idx = macvlan_eth_hash(addr);
	काष्ठा hlist_head *h = &vlan->port->vlan_source_hash[idx];

	hlist_क्रम_each_entry_rcu(entry, h, hlist) अणु
		अगर (ether_addr_equal_64bits(entry->addr, addr) &&
		    entry->vlan == vlan)
			वापस entry;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक macvlan_hash_add_source(काष्ठा macvlan_dev *vlan,
				   स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा macvlan_port *port = vlan->port;
	काष्ठा macvlan_source_entry *entry;
	काष्ठा hlist_head *h;

	entry = macvlan_hash_lookup_source(vlan, addr);
	अगर (entry)
		वापस 0;

	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	ether_addr_copy(entry->addr, addr);
	entry->vlan = vlan;
	h = &port->vlan_source_hash[macvlan_eth_hash(addr)];
	hlist_add_head_rcu(&entry->hlist, h);
	vlan->macaddr_count++;

	वापस 0;
पूर्ण

अटल व्योम macvlan_hash_add(काष्ठा macvlan_dev *vlan)
अणु
	काष्ठा macvlan_port *port = vlan->port;
	स्थिर अचिन्हित अक्षर *addr = vlan->dev->dev_addr;
	u32 idx = macvlan_eth_hash(addr);

	hlist_add_head_rcu(&vlan->hlist, &port->vlan_hash[idx]);
पूर्ण

अटल व्योम macvlan_hash_del_source(काष्ठा macvlan_source_entry *entry)
अणु
	hlist_del_rcu(&entry->hlist);
	kमुक्त_rcu(entry, rcu);
पूर्ण

अटल व्योम macvlan_hash_del(काष्ठा macvlan_dev *vlan, bool sync)
अणु
	hlist_del_rcu(&vlan->hlist);
	अगर (sync)
		synchronize_rcu();
पूर्ण

अटल व्योम macvlan_hash_change_addr(काष्ठा macvlan_dev *vlan,
					स्थिर अचिन्हित अक्षर *addr)
अणु
	macvlan_hash_del(vlan, true);
	/* Now that we are unhashed it is safe to change the device
	 * address without confusing packet delivery.
	 */
	स_नकल(vlan->dev->dev_addr, addr, ETH_ALEN);
	macvlan_hash_add(vlan);
पूर्ण

अटल bool macvlan_addr_busy(स्थिर काष्ठा macvlan_port *port,
			      स्थिर अचिन्हित अक्षर *addr)
अणु
	/* Test to see अगर the specअगरied address is
	 * currently in use by the underlying device or
	 * another macvlan.
	 */
	अगर (!macvlan_passthru(port) && !macvlan_addr_change(port) &&
	    ether_addr_equal_64bits(port->dev->dev_addr, addr))
		वापस true;

	अगर (macvlan_hash_lookup(port, addr))
		वापस true;

	वापस false;
पूर्ण


अटल पूर्णांक macvlan_broadcast_one(काष्ठा sk_buff *skb,
				 स्थिर काष्ठा macvlan_dev *vlan,
				 स्थिर काष्ठा ethhdr *eth, bool local)
अणु
	काष्ठा net_device *dev = vlan->dev;

	अगर (local)
		वापस __dev_क्रमward_skb(dev, skb);

	skb->dev = dev;
	अगर (ether_addr_equal_64bits(eth->h_dest, dev->broadcast))
		skb->pkt_type = PACKET_BROADCAST;
	अन्यथा
		skb->pkt_type = PACKET_MULTICAST;

	वापस 0;
पूर्ण

अटल u32 macvlan_hash_mix(स्थिर काष्ठा macvlan_dev *vlan)
अणु
	वापस (u32)(((अचिन्हित दीर्घ)vlan) >> L1_CACHE_SHIFT);
पूर्ण


अटल अचिन्हित पूर्णांक mc_hash(स्थिर काष्ठा macvlan_dev *vlan,
			    स्थिर अचिन्हित अक्षर *addr)
अणु
	u32 val = __get_unaligned_cpu32(addr + 2);

	val ^= macvlan_hash_mix(vlan);
	वापस hash_32(val, MACVLAN_MC_FILTER_BITS);
पूर्ण

अटल व्योम macvlan_broadcast(काष्ठा sk_buff *skb,
			      स्थिर काष्ठा macvlan_port *port,
			      काष्ठा net_device *src,
			      क्रमागत macvlan_mode mode)
अणु
	स्थिर काष्ठा ethhdr *eth = eth_hdr(skb);
	स्थिर काष्ठा macvlan_dev *vlan;
	काष्ठा sk_buff *nskb;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;
	अचिन्हित पूर्णांक hash;

	अगर (skb->protocol == htons(ETH_P_PAUSE))
		वापस;

	hash_क्रम_each_rcu(port->vlan_hash, i, vlan, hlist) अणु
		अगर (vlan->dev == src || !(vlan->mode & mode))
			जारी;

		hash = mc_hash(vlan, eth->h_dest);
		अगर (!test_bit(hash, vlan->mc_filter))
			जारी;

		err = NET_RX_DROP;
		nskb = skb_clone(skb, GFP_ATOMIC);
		अगर (likely(nskb))
			err = macvlan_broadcast_one(nskb, vlan, eth,
					mode == MACVLAN_MODE_BRIDGE) ?:
			      netअगर_rx_ni(nskb);
		macvlan_count_rx(vlan, skb->len + ETH_HLEN,
				 err == NET_RX_SUCCESS, true);
	पूर्ण
पूर्ण

अटल व्योम macvlan_process_broadcast(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा macvlan_port *port = container_of(w, काष्ठा macvlan_port,
						 bc_work);
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff_head list;

	__skb_queue_head_init(&list);

	spin_lock_bh(&port->bc_queue.lock);
	skb_queue_splice_tail_init(&port->bc_queue, &list);
	spin_unlock_bh(&port->bc_queue.lock);

	जबतक ((skb = __skb_dequeue(&list))) अणु
		स्थिर काष्ठा macvlan_dev *src = MACVLAN_SKB_CB(skb)->src;

		rcu_पढ़ो_lock();

		अगर (!src)
			/* frame comes from an बाह्यal address */
			macvlan_broadcast(skb, port, शून्य,
					  MACVLAN_MODE_PRIVATE |
					  MACVLAN_MODE_VEPA    |
					  MACVLAN_MODE_PASSTHRU|
					  MACVLAN_MODE_BRIDGE);
		अन्यथा अगर (src->mode == MACVLAN_MODE_VEPA)
			/* flood to everyone except source */
			macvlan_broadcast(skb, port, src->dev,
					  MACVLAN_MODE_VEPA |
					  MACVLAN_MODE_BRIDGE);
		अन्यथा
			/*
			 * flood only to VEPA ports, bridge ports
			 * alपढ़ोy saw the frame on the way out.
			 */
			macvlan_broadcast(skb, port, src->dev,
					  MACVLAN_MODE_VEPA);

		rcu_पढ़ो_unlock();

		अगर (src)
			dev_put(src->dev);
		consume_skb(skb);

		cond_resched();
	पूर्ण
पूर्ण

अटल व्योम macvlan_broadcast_enqueue(काष्ठा macvlan_port *port,
				      स्थिर काष्ठा macvlan_dev *src,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *nskb;
	पूर्णांक err = -ENOMEM;

	nskb = skb_clone(skb, GFP_ATOMIC);
	अगर (!nskb)
		जाओ err;

	MACVLAN_SKB_CB(nskb)->src = src;

	spin_lock(&port->bc_queue.lock);
	अगर (skb_queue_len(&port->bc_queue) < port->bc_queue_len_used) अणु
		अगर (src)
			dev_hold(src->dev);
		__skb_queue_tail(&port->bc_queue, nskb);
		err = 0;
	पूर्ण
	spin_unlock(&port->bc_queue.lock);

	schedule_work(&port->bc_work);

	अगर (err)
		जाओ मुक्त_nskb;

	वापस;

मुक्त_nskb:
	kमुक्त_skb(nskb);
err:
	atomic_दीर्घ_inc(&skb->dev->rx_dropped);
पूर्ण

अटल व्योम macvlan_flush_sources(काष्ठा macvlan_port *port,
				  काष्ठा macvlan_dev *vlan)
अणु
	काष्ठा macvlan_source_entry *entry;
	काष्ठा hlist_node *next;
	पूर्णांक i;

	hash_क्रम_each_safe(port->vlan_source_hash, i, next, entry, hlist)
		अगर (entry->vlan == vlan)
			macvlan_hash_del_source(entry);

	vlan->macaddr_count = 0;
पूर्ण

अटल व्योम macvlan_क्रमward_source_one(काष्ठा sk_buff *skb,
				       काष्ठा macvlan_dev *vlan)
अणु
	काष्ठा sk_buff *nskb;
	काष्ठा net_device *dev;
	पूर्णांक len;
	पूर्णांक ret;

	dev = vlan->dev;
	अगर (unlikely(!(dev->flags & IFF_UP)))
		वापस;

	nskb = skb_clone(skb, GFP_ATOMIC);
	अगर (!nskb)
		वापस;

	len = nskb->len + ETH_HLEN;
	nskb->dev = dev;

	अगर (ether_addr_equal_64bits(eth_hdr(skb)->h_dest, dev->dev_addr))
		nskb->pkt_type = PACKET_HOST;

	ret = netअगर_rx(nskb);
	macvlan_count_rx(vlan, len, ret == NET_RX_SUCCESS, false);
पूर्ण

अटल bool macvlan_क्रमward_source(काष्ठा sk_buff *skb,
				   काष्ठा macvlan_port *port,
				   स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा macvlan_source_entry *entry;
	u32 idx = macvlan_eth_hash(addr);
	काष्ठा hlist_head *h = &port->vlan_source_hash[idx];
	bool consume = false;

	hlist_क्रम_each_entry_rcu(entry, h, hlist) अणु
		अगर (ether_addr_equal_64bits(entry->addr, addr)) अणु
			अगर (entry->vlan->flags & MACVLAN_FLAG_NODST)
				consume = true;
			macvlan_क्रमward_source_one(skb, entry->vlan);
		पूर्ण
	पूर्ण

	वापस consume;
पूर्ण

/* called under rcu_पढ़ो_lock() from netअगर_receive_skb */
अटल rx_handler_result_t macvlan_handle_frame(काष्ठा sk_buff **pskb)
अणु
	काष्ठा macvlan_port *port;
	काष्ठा sk_buff *skb = *pskb;
	स्थिर काष्ठा ethhdr *eth = eth_hdr(skb);
	स्थिर काष्ठा macvlan_dev *vlan;
	स्थिर काष्ठा macvlan_dev *src;
	काष्ठा net_device *dev;
	अचिन्हित पूर्णांक len = 0;
	पूर्णांक ret;
	rx_handler_result_t handle_res;

	/* Packets from dev_loopback_xmit() करो not have L2 header, bail out */
	अगर (unlikely(skb->pkt_type == PACKET_LOOPBACK))
		वापस RX_HANDLER_PASS;

	port = macvlan_port_get_rcu(skb->dev);
	अगर (is_multicast_ether_addr(eth->h_dest)) अणु
		अचिन्हित पूर्णांक hash;

		skb = ip_check_defrag(dev_net(skb->dev), skb, IP_DEFRAG_MACVLAN);
		अगर (!skb)
			वापस RX_HANDLER_CONSUMED;
		*pskb = skb;
		eth = eth_hdr(skb);
		अगर (macvlan_क्रमward_source(skb, port, eth->h_source))
			वापस RX_HANDLER_CONSUMED;
		src = macvlan_hash_lookup(port, eth->h_source);
		अगर (src && src->mode != MACVLAN_MODE_VEPA &&
		    src->mode != MACVLAN_MODE_BRIDGE) अणु
			/* क्रमward to original port. */
			vlan = src;
			ret = macvlan_broadcast_one(skb, vlan, eth, 0) ?:
			      netअगर_rx(skb);
			handle_res = RX_HANDLER_CONSUMED;
			जाओ out;
		पूर्ण

		hash = mc_hash(शून्य, eth->h_dest);
		अगर (test_bit(hash, port->mc_filter))
			macvlan_broadcast_enqueue(port, src, skb);

		वापस RX_HANDLER_PASS;
	पूर्ण

	अगर (macvlan_क्रमward_source(skb, port, eth->h_source))
		वापस RX_HANDLER_CONSUMED;
	अगर (macvlan_passthru(port))
		vlan = list_first_or_null_rcu(&port->vlans,
					      काष्ठा macvlan_dev, list);
	अन्यथा
		vlan = macvlan_hash_lookup(port, eth->h_dest);
	अगर (!vlan || vlan->mode == MACVLAN_MODE_SOURCE)
		वापस RX_HANDLER_PASS;

	dev = vlan->dev;
	अगर (unlikely(!(dev->flags & IFF_UP))) अणु
		kमुक्त_skb(skb);
		वापस RX_HANDLER_CONSUMED;
	पूर्ण
	len = skb->len + ETH_HLEN;
	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (!skb) अणु
		ret = NET_RX_DROP;
		handle_res = RX_HANDLER_CONSUMED;
		जाओ out;
	पूर्ण

	*pskb = skb;
	skb->dev = dev;
	skb->pkt_type = PACKET_HOST;

	ret = NET_RX_SUCCESS;
	handle_res = RX_HANDLER_ANOTHER;
out:
	macvlan_count_rx(vlan, len, ret == NET_RX_SUCCESS, false);
	वापस handle_res;
पूर्ण

अटल पूर्णांक macvlan_queue_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा macvlan_dev *vlan = netdev_priv(dev);
	स्थिर काष्ठा macvlan_port *port = vlan->port;
	स्थिर काष्ठा macvlan_dev *dest;

	अगर (vlan->mode == MACVLAN_MODE_BRIDGE) अणु
		स्थिर काष्ठा ethhdr *eth = skb_eth_hdr(skb);

		/* send to other bridge ports directly */
		अगर (is_multicast_ether_addr(eth->h_dest)) अणु
			skb_reset_mac_header(skb);
			macvlan_broadcast(skb, port, dev, MACVLAN_MODE_BRIDGE);
			जाओ xmit_world;
		पूर्ण

		dest = macvlan_hash_lookup(port, eth->h_dest);
		अगर (dest && dest->mode == MACVLAN_MODE_BRIDGE) अणु
			/* send to lowerdev first क्रम its network taps */
			dev_क्रमward_skb(vlan->lowerdev, skb);

			वापस NET_XMIT_SUCCESS;
		पूर्ण
	पूर्ण
xmit_world:
	skb->dev = vlan->lowerdev;
	वापस dev_queue_xmit_accel(skb,
				    netdev_get_sb_channel(dev) ? dev : शून्य);
पूर्ण

अटल अंतरभूत netdev_tx_t macvlan_netpoll_send_skb(काष्ठा macvlan_dev *vlan, काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	वापस netpoll_send_skb(vlan->netpoll, skb);
#अन्यथा
	BUG();
	वापस NETDEV_TX_OK;
#पूर्ण_अगर
पूर्ण

अटल netdev_tx_t macvlan_start_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);
	अचिन्हित पूर्णांक len = skb->len;
	पूर्णांक ret;

	अगर (unlikely(netpoll_tx_running(dev)))
		वापस macvlan_netpoll_send_skb(vlan, skb);

	ret = macvlan_queue_xmit(skb, dev);

	अगर (likely(ret == NET_XMIT_SUCCESS || ret == NET_XMIT_CN)) अणु
		काष्ठा vlan_pcpu_stats *pcpu_stats;

		pcpu_stats = this_cpu_ptr(vlan->pcpu_stats);
		u64_stats_update_begin(&pcpu_stats->syncp);
		pcpu_stats->tx_packets++;
		pcpu_stats->tx_bytes += len;
		u64_stats_update_end(&pcpu_stats->syncp);
	पूर्ण अन्यथा अणु
		this_cpu_inc(vlan->pcpu_stats->tx_dropped);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक macvlan_hard_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			       अचिन्हित लघु type, स्थिर व्योम *daddr,
			       स्थिर व्योम *saddr, अचिन्हित len)
अणु
	स्थिर काष्ठा macvlan_dev *vlan = netdev_priv(dev);
	काष्ठा net_device *lowerdev = vlan->lowerdev;

	वापस dev_hard_header(skb, lowerdev, type, daddr,
			       saddr ? : dev->dev_addr, len);
पूर्ण

अटल स्थिर काष्ठा header_ops macvlan_hard_header_ops = अणु
	.create  	= macvlan_hard_header,
	.parse		= eth_header_parse,
	.cache		= eth_header_cache,
	.cache_update	= eth_header_cache_update,
पूर्ण;

अटल पूर्णांक macvlan_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);
	काष्ठा net_device *lowerdev = vlan->lowerdev;
	पूर्णांक err;

	अगर (macvlan_passthru(vlan->port)) अणु
		अगर (!(vlan->flags & MACVLAN_FLAG_NOPROMISC)) अणु
			err = dev_set_promiscuity(lowerdev, 1);
			अगर (err < 0)
				जाओ out;
		पूर्ण
		जाओ hash_add;
	पूर्ण

	err = -EADDRINUSE;
	अगर (macvlan_addr_busy(vlan->port, dev->dev_addr))
		जाओ out;

	/* Attempt to populate accel_priv which is used to offload the L2
	 * क्रमwarding requests क्रम unicast packets.
	 */
	अगर (lowerdev->features & NETIF_F_HW_L2FW_DOFFLOAD)
		vlan->accel_priv =
		      lowerdev->netdev_ops->nकरो_dfwd_add_station(lowerdev, dev);

	/* If earlier attempt to offload failed, or accel_priv is not
	 * populated we must add the unicast address to the lower device.
	 */
	अगर (IS_ERR_OR_शून्य(vlan->accel_priv)) अणु
		vlan->accel_priv = शून्य;
		err = dev_uc_add(lowerdev, dev->dev_addr);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	अगर (dev->flags & IFF_ALLMULTI) अणु
		err = dev_set_allmulti(lowerdev, 1);
		अगर (err < 0)
			जाओ del_unicast;
	पूर्ण

	अगर (dev->flags & IFF_PROMISC) अणु
		err = dev_set_promiscuity(lowerdev, 1);
		अगर (err < 0)
			जाओ clear_multi;
	पूर्ण

hash_add:
	macvlan_hash_add(vlan);
	वापस 0;

clear_multi:
	अगर (dev->flags & IFF_ALLMULTI)
		dev_set_allmulti(lowerdev, -1);
del_unicast:
	अगर (vlan->accel_priv) अणु
		lowerdev->netdev_ops->nकरो_dfwd_del_station(lowerdev,
							   vlan->accel_priv);
		vlan->accel_priv = शून्य;
	पूर्ण अन्यथा अणु
		dev_uc_del(lowerdev, dev->dev_addr);
	पूर्ण
out:
	वापस err;
पूर्ण

अटल पूर्णांक macvlan_stop(काष्ठा net_device *dev)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);
	काष्ठा net_device *lowerdev = vlan->lowerdev;

	अगर (vlan->accel_priv) अणु
		lowerdev->netdev_ops->nकरो_dfwd_del_station(lowerdev,
							   vlan->accel_priv);
		vlan->accel_priv = शून्य;
	पूर्ण

	dev_uc_unsync(lowerdev, dev);
	dev_mc_unsync(lowerdev, dev);

	अगर (macvlan_passthru(vlan->port)) अणु
		अगर (!(vlan->flags & MACVLAN_FLAG_NOPROMISC))
			dev_set_promiscuity(lowerdev, -1);
		जाओ hash_del;
	पूर्ण

	अगर (dev->flags & IFF_ALLMULTI)
		dev_set_allmulti(lowerdev, -1);

	अगर (dev->flags & IFF_PROMISC)
		dev_set_promiscuity(lowerdev, -1);

	dev_uc_del(lowerdev, dev->dev_addr);

hash_del:
	macvlan_hash_del(vlan, !dev->dismantle);
	वापस 0;
पूर्ण

अटल पूर्णांक macvlan_sync_address(काष्ठा net_device *dev, अचिन्हित अक्षर *addr)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);
	काष्ठा net_device *lowerdev = vlan->lowerdev;
	काष्ठा macvlan_port *port = vlan->port;
	पूर्णांक err;

	अगर (!(dev->flags & IFF_UP)) अणु
		/* Just copy in the new address */
		ether_addr_copy(dev->dev_addr, addr);
	पूर्ण अन्यथा अणु
		/* Rehash and update the device filters */
		अगर (macvlan_addr_busy(vlan->port, addr))
			वापस -EADDRINUSE;

		अगर (!macvlan_passthru(port)) अणु
			err = dev_uc_add(lowerdev, addr);
			अगर (err)
				वापस err;

			dev_uc_del(lowerdev, dev->dev_addr);
		पूर्ण

		macvlan_hash_change_addr(vlan, addr);
	पूर्ण
	अगर (macvlan_passthru(port) && !macvlan_addr_change(port)) अणु
		/* Since addr_change isn't set, we are here due to lower
		 * device change.  Save the lower-dev address so we can
		 * restore it later.
		 */
		ether_addr_copy(vlan->port->perm_addr,
				lowerdev->dev_addr);
	पूर्ण
	macvlan_clear_addr_change(port);
	वापस 0;
पूर्ण

अटल पूर्णांक macvlan_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	/* If the addresses are the same, this is a no-op */
	अगर (ether_addr_equal(dev->dev_addr, addr->sa_data))
		वापस 0;

	अगर (vlan->mode == MACVLAN_MODE_PASSTHRU) अणु
		macvlan_set_addr_change(vlan->port);
		वापस dev_set_mac_address(vlan->lowerdev, addr, शून्य);
	पूर्ण

	अगर (macvlan_addr_busy(vlan->port, addr->sa_data))
		वापस -EADDRINUSE;

	वापस macvlan_sync_address(dev, addr->sa_data);
पूर्ण

अटल व्योम macvlan_change_rx_flags(काष्ठा net_device *dev, पूर्णांक change)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);
	काष्ठा net_device *lowerdev = vlan->lowerdev;

	अगर (dev->flags & IFF_UP) अणु
		अगर (change & IFF_ALLMULTI)
			dev_set_allmulti(lowerdev, dev->flags & IFF_ALLMULTI ? 1 : -1);
		अगर (change & IFF_PROMISC)
			dev_set_promiscuity(lowerdev,
					    dev->flags & IFF_PROMISC ? 1 : -1);

	पूर्ण
पूर्ण

अटल व्योम macvlan_compute_filter(अचिन्हित दीर्घ *mc_filter,
				   काष्ठा net_device *dev,
				   काष्ठा macvlan_dev *vlan)
अणु
	अगर (dev->flags & (IFF_PROMISC | IFF_ALLMULTI)) अणु
		biपंचांगap_fill(mc_filter, MACVLAN_MC_FILTER_SZ);
	पूर्ण अन्यथा अणु
		काष्ठा netdev_hw_addr *ha;
		DECLARE_BITMAP(filter, MACVLAN_MC_FILTER_SZ);

		biपंचांगap_zero(filter, MACVLAN_MC_FILTER_SZ);
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			__set_bit(mc_hash(vlan, ha->addr), filter);
		पूर्ण

		__set_bit(mc_hash(vlan, dev->broadcast), filter);

		biपंचांगap_copy(mc_filter, filter, MACVLAN_MC_FILTER_SZ);
	पूर्ण
पूर्ण

अटल व्योम macvlan_set_mac_lists(काष्ठा net_device *dev)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);

	macvlan_compute_filter(vlan->mc_filter, dev, vlan);

	dev_uc_sync(vlan->lowerdev, dev);
	dev_mc_sync(vlan->lowerdev, dev);

	/* This is slightly inaccurate as we're including the subscription
	 * list of vlan->lowerdev too.
	 *
	 * Bug alert: This only works अगर everyone has the same broadcast
	 * address as lowerdev.  As soon as someone changes theirs this
	 * will अवरोध.
	 *
	 * However, this is alपढ़ोy broken as when you change your broadcast
	 * address we करोn't get called.
	 *
	 * The solution is to मुख्यtain a list of broadcast addresses like
	 * we करो क्रम uc/mc, अगर you care.
	 */
	macvlan_compute_filter(vlan->port->mc_filter, vlan->lowerdev, शून्य);
पूर्ण

अटल पूर्णांक macvlan_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);

	अगर (vlan->lowerdev->mtu < new_mtu)
		वापस -EINVAL;
	dev->mtu = new_mtu;
	वापस 0;
पूर्ण

अटल पूर्णांक macvlan_करो_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा net_device *real_dev = macvlan_dev_real_dev(dev);
	स्थिर काष्ठा net_device_ops *ops = real_dev->netdev_ops;
	काष्ठा अगरreq अगरrr;
	पूर्णांक err = -EOPNOTSUPP;

	strscpy(अगरrr.अगरr_name, real_dev->name, IFNAMSIZ);
	अगरrr.अगरr_अगरru = अगरr->अगरr_अगरru;

	चयन (cmd) अणु
	हाल SIOCSHWTSTAMP:
		अगर (!net_eq(dev_net(dev), &init_net))
			अवरोध;
		fallthrough;
	हाल SIOCGHWTSTAMP:
		अगर (netअगर_device_present(real_dev) && ops->nकरो_करो_ioctl)
			err = ops->nकरो_करो_ioctl(real_dev, &अगरrr, cmd);
		अवरोध;
	पूर्ण

	अगर (!err)
		अगरr->अगरr_अगरru = अगरrr.अगरr_अगरru;

	वापस err;
पूर्ण

/*
 * macvlan network devices have devices nesting below it and are a special
 * "super class" of normal network devices; split their locks off पूर्णांकo a
 * separate class since they always nest.
 */
अटल काष्ठा lock_class_key macvlan_netdev_addr_lock_key;

#घोषणा ALWAYS_ON_OFFLOADS \
	(NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_GSO_SOFTWARE | \
	 NETIF_F_GSO_ROBUST | NETIF_F_GSO_ENCAP_ALL)

#घोषणा ALWAYS_ON_FEATURES (ALWAYS_ON_OFFLOADS | NETIF_F_LLTX)

#घोषणा MACVLAN_FEATURES \
	(NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_HIGHDMA | NETIF_F_FRAGLIST | \
	 NETIF_F_GSO | NETIF_F_TSO | NETIF_F_LRO | \
	 NETIF_F_TSO_ECN | NETIF_F_TSO6 | NETIF_F_GRO | NETIF_F_RXCSUM | \
	 NETIF_F_HW_VLAN_CTAG_FILTER | NETIF_F_HW_VLAN_STAG_FILTER)

#घोषणा MACVLAN_STATE_MASK \
	((1<<__LINK_STATE_NOCARRIER) | (1<<__LINK_STATE_DORMANT))

अटल व्योम macvlan_set_lockdep_class(काष्ठा net_device *dev)
अणु
	netdev_lockdep_set_classes(dev);
	lockdep_set_class(&dev->addr_list_lock,
			  &macvlan_netdev_addr_lock_key);
पूर्ण

अटल पूर्णांक macvlan_init(काष्ठा net_device *dev)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);
	स्थिर काष्ठा net_device *lowerdev = vlan->lowerdev;
	काष्ठा macvlan_port *port = vlan->port;

	dev->state		= (dev->state & ~MACVLAN_STATE_MASK) |
				  (lowerdev->state & MACVLAN_STATE_MASK);
	dev->features 		= lowerdev->features & MACVLAN_FEATURES;
	dev->features		|= ALWAYS_ON_FEATURES;
	dev->hw_features	|= NETIF_F_LRO;
	dev->vlan_features	= lowerdev->vlan_features & MACVLAN_FEATURES;
	dev->vlan_features	|= ALWAYS_ON_OFFLOADS;
	dev->hw_enc_features    |= dev->features;
	dev->gso_max_size	= lowerdev->gso_max_size;
	dev->gso_max_segs	= lowerdev->gso_max_segs;
	dev->hard_header_len	= lowerdev->hard_header_len;
	macvlan_set_lockdep_class(dev);

	vlan->pcpu_stats = netdev_alloc_pcpu_stats(काष्ठा vlan_pcpu_stats);
	अगर (!vlan->pcpu_stats)
		वापस -ENOMEM;

	port->count += 1;

	वापस 0;
पूर्ण

अटल व्योम macvlan_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);
	काष्ठा macvlan_port *port = vlan->port;

	मुक्त_percpu(vlan->pcpu_stats);

	macvlan_flush_sources(port, vlan);
	port->count -= 1;
	अगर (!port->count)
		macvlan_port_destroy(port->dev);
पूर्ण

अटल व्योम macvlan_dev_get_stats64(काष्ठा net_device *dev,
				    काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);

	अगर (vlan->pcpu_stats) अणु
		काष्ठा vlan_pcpu_stats *p;
		u64 rx_packets, rx_bytes, rx_multicast, tx_packets, tx_bytes;
		u32 rx_errors = 0, tx_dropped = 0;
		अचिन्हित पूर्णांक start;
		पूर्णांक i;

		क्रम_each_possible_cpu(i) अणु
			p = per_cpu_ptr(vlan->pcpu_stats, i);
			करो अणु
				start = u64_stats_fetch_begin_irq(&p->syncp);
				rx_packets	= p->rx_packets;
				rx_bytes	= p->rx_bytes;
				rx_multicast	= p->rx_multicast;
				tx_packets	= p->tx_packets;
				tx_bytes	= p->tx_bytes;
			पूर्ण जबतक (u64_stats_fetch_retry_irq(&p->syncp, start));

			stats->rx_packets	+= rx_packets;
			stats->rx_bytes		+= rx_bytes;
			stats->multicast	+= rx_multicast;
			stats->tx_packets	+= tx_packets;
			stats->tx_bytes		+= tx_bytes;
			/* rx_errors & tx_dropped are u32, updated
			 * without syncp protection.
			 */
			rx_errors	+= p->rx_errors;
			tx_dropped	+= p->tx_dropped;
		पूर्ण
		stats->rx_errors	= rx_errors;
		stats->rx_dropped	= rx_errors;
		stats->tx_dropped	= tx_dropped;
	पूर्ण
पूर्ण

अटल पूर्णांक macvlan_vlan_rx_add_vid(काष्ठा net_device *dev,
				   __be16 proto, u16 vid)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);
	काष्ठा net_device *lowerdev = vlan->lowerdev;

	वापस vlan_vid_add(lowerdev, proto, vid);
पूर्ण

अटल पूर्णांक macvlan_vlan_rx_समाप्त_vid(काष्ठा net_device *dev,
				    __be16 proto, u16 vid)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);
	काष्ठा net_device *lowerdev = vlan->lowerdev;

	vlan_vid_del(lowerdev, proto, vid);
	वापस 0;
पूर्ण

अटल पूर्णांक macvlan_fdb_add(काष्ठा ndmsg *ndm, काष्ठा nlattr *tb[],
			   काष्ठा net_device *dev,
			   स्थिर अचिन्हित अक्षर *addr, u16 vid,
			   u16 flags,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);
	पूर्णांक err = -EINVAL;

	/* Support unicast filter only on passthru devices.
	 * Multicast filter should be allowed on all devices.
	 */
	अगर (!macvlan_passthru(vlan->port) && is_unicast_ether_addr(addr))
		वापस -EOPNOTSUPP;

	अगर (flags & NLM_F_REPLACE)
		वापस -EOPNOTSUPP;

	अगर (is_unicast_ether_addr(addr))
		err = dev_uc_add_excl(dev, addr);
	अन्यथा अगर (is_multicast_ether_addr(addr))
		err = dev_mc_add_excl(dev, addr);

	वापस err;
पूर्ण

अटल पूर्णांक macvlan_fdb_del(काष्ठा ndmsg *ndm, काष्ठा nlattr *tb[],
			   काष्ठा net_device *dev,
			   स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);
	पूर्णांक err = -EINVAL;

	/* Support unicast filter only on passthru devices.
	 * Multicast filter should be allowed on all devices.
	 */
	अगर (!macvlan_passthru(vlan->port) && is_unicast_ether_addr(addr))
		वापस -EOPNOTSUPP;

	अगर (is_unicast_ether_addr(addr))
		err = dev_uc_del(dev, addr);
	अन्यथा अगर (is_multicast_ether_addr(addr))
		err = dev_mc_del(dev, addr);

	वापस err;
पूर्ण

अटल व्योम macvlan_ethtool_get_drvinfo(काष्ठा net_device *dev,
					काष्ठा ethtool_drvinfo *drvinfo)
अणु
	strlcpy(drvinfo->driver, "macvlan", माप(drvinfo->driver));
	strlcpy(drvinfo->version, "0.1", माप(drvinfo->version));
पूर्ण

अटल पूर्णांक macvlan_ethtool_get_link_ksettings(काष्ठा net_device *dev,
					      काष्ठा ethtool_link_ksettings *cmd)
अणु
	स्थिर काष्ठा macvlan_dev *vlan = netdev_priv(dev);

	वापस __ethtool_get_link_ksettings(vlan->lowerdev, cmd);
पूर्ण

अटल पूर्णांक macvlan_ethtool_get_ts_info(काष्ठा net_device *dev,
				       काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा net_device *real_dev = macvlan_dev_real_dev(dev);
	स्थिर काष्ठा ethtool_ops *ops = real_dev->ethtool_ops;
	काष्ठा phy_device *phydev = real_dev->phydev;

	अगर (phy_has_tsinfo(phydev)) अणु
		वापस phy_ts_info(phydev, info);
	पूर्ण अन्यथा अगर (ops->get_ts_info) अणु
		वापस ops->get_ts_info(real_dev, info);
	पूर्ण अन्यथा अणु
		info->so_बारtamping = SOF_TIMESTAMPING_RX_SOFTWARE |
			SOF_TIMESTAMPING_SOFTWARE;
		info->phc_index = -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल netdev_features_t macvlan_fix_features(काष्ठा net_device *dev,
					      netdev_features_t features)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);
	netdev_features_t lowerdev_features = vlan->lowerdev->features;
	netdev_features_t mask;

	features |= NETIF_F_ALL_FOR_ALL;
	features &= (vlan->set_features | ~MACVLAN_FEATURES);
	mask = features;

	lowerdev_features &= (features | ~NETIF_F_LRO);
	features = netdev_increment_features(lowerdev_features, features, mask);
	features |= ALWAYS_ON_FEATURES;
	features &= (ALWAYS_ON_FEATURES | MACVLAN_FEATURES);

	वापस features;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम macvlan_dev_poll_controller(काष्ठा net_device *dev)
अणु
	वापस;
पूर्ण

अटल पूर्णांक macvlan_dev_netpoll_setup(काष्ठा net_device *dev, काष्ठा netpoll_info *npinfo)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);
	काष्ठा net_device *real_dev = vlan->lowerdev;
	काष्ठा netpoll *netpoll;
	पूर्णांक err;

	netpoll = kzalloc(माप(*netpoll), GFP_KERNEL);
	err = -ENOMEM;
	अगर (!netpoll)
		जाओ out;

	err = __netpoll_setup(netpoll, real_dev);
	अगर (err) अणु
		kमुक्त(netpoll);
		जाओ out;
	पूर्ण

	vlan->netpoll = netpoll;

out:
	वापस err;
पूर्ण

अटल व्योम macvlan_dev_netpoll_cleanup(काष्ठा net_device *dev)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);
	काष्ठा netpoll *netpoll = vlan->netpoll;

	अगर (!netpoll)
		वापस;

	vlan->netpoll = शून्य;

	__netpoll_मुक्त(netpoll);
पूर्ण
#पूर्ण_अगर	/* CONFIG_NET_POLL_CONTROLLER */

अटल पूर्णांक macvlan_dev_get_अगरlink(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);

	वापस vlan->lowerdev->अगरindex;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops macvlan_ethtool_ops = अणु
	.get_link		= ethtool_op_get_link,
	.get_link_ksettings	= macvlan_ethtool_get_link_ksettings,
	.get_drvinfo		= macvlan_ethtool_get_drvinfo,
	.get_ts_info		= macvlan_ethtool_get_ts_info,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops macvlan_netdev_ops = अणु
	.nकरो_init		= macvlan_init,
	.nकरो_uninit		= macvlan_uninit,
	.nकरो_खोलो		= macvlan_खोलो,
	.nकरो_stop		= macvlan_stop,
	.nकरो_start_xmit		= macvlan_start_xmit,
	.nकरो_change_mtu		= macvlan_change_mtu,
	.nकरो_करो_ioctl		= macvlan_करो_ioctl,
	.nकरो_fix_features	= macvlan_fix_features,
	.nकरो_change_rx_flags	= macvlan_change_rx_flags,
	.nकरो_set_mac_address	= macvlan_set_mac_address,
	.nकरो_set_rx_mode	= macvlan_set_mac_lists,
	.nकरो_get_stats64	= macvlan_dev_get_stats64,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_vlan_rx_add_vid	= macvlan_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= macvlan_vlan_rx_समाप्त_vid,
	.nकरो_fdb_add		= macvlan_fdb_add,
	.nकरो_fdb_del		= macvlan_fdb_del,
	.nकरो_fdb_dump		= nकरो_dflt_fdb_dump,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= macvlan_dev_poll_controller,
	.nकरो_netpoll_setup	= macvlan_dev_netpoll_setup,
	.nकरो_netpoll_cleanup	= macvlan_dev_netpoll_cleanup,
#पूर्ण_अगर
	.nकरो_get_अगरlink		= macvlan_dev_get_अगरlink,
	.nकरो_features_check	= passthru_features_check,
	.nकरो_change_proto_करोwn  = dev_change_proto_करोwn_generic,
पूर्ण;

व्योम macvlan_common_setup(काष्ठा net_device *dev)
अणु
	ether_setup(dev);

	dev->min_mtu		= 0;
	dev->max_mtu		= ETH_MAX_MTU;
	dev->priv_flags	       &= ~IFF_TX_SKB_SHARING;
	netअगर_keep_dst(dev);
	dev->priv_flags	       |= IFF_UNICAST_FLT;
	dev->netdev_ops		= &macvlan_netdev_ops;
	dev->needs_मुक्त_netdev	= true;
	dev->header_ops		= &macvlan_hard_header_ops;
	dev->ethtool_ops	= &macvlan_ethtool_ops;
पूर्ण
EXPORT_SYMBOL_GPL(macvlan_common_setup);

अटल व्योम macvlan_setup(काष्ठा net_device *dev)
अणु
	macvlan_common_setup(dev);
	dev->priv_flags |= IFF_NO_QUEUE;
पूर्ण

अटल पूर्णांक macvlan_port_create(काष्ठा net_device *dev)
अणु
	काष्ठा macvlan_port *port;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (dev->type != ARPHRD_ETHER || dev->flags & IFF_LOOPBACK)
		वापस -EINVAL;

	अगर (netdev_is_rx_handler_busy(dev))
		वापस -EBUSY;

	port = kzalloc(माप(*port), GFP_KERNEL);
	अगर (port == शून्य)
		वापस -ENOMEM;

	port->dev = dev;
	ether_addr_copy(port->perm_addr, dev->dev_addr);
	INIT_LIST_HEAD(&port->vlans);
	क्रम (i = 0; i < MACVLAN_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&port->vlan_hash[i]);
	क्रम (i = 0; i < MACVLAN_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&port->vlan_source_hash[i]);

	port->bc_queue_len_used = 0;
	skb_queue_head_init(&port->bc_queue);
	INIT_WORK(&port->bc_work, macvlan_process_broadcast);

	err = netdev_rx_handler_रेजिस्टर(dev, macvlan_handle_frame, port);
	अगर (err)
		kमुक्त(port);
	अन्यथा
		dev->priv_flags |= IFF_MACVLAN_PORT;
	वापस err;
पूर्ण

अटल व्योम macvlan_port_destroy(काष्ठा net_device *dev)
अणु
	काष्ठा macvlan_port *port = macvlan_port_get_rtnl(dev);
	काष्ठा sk_buff *skb;

	dev->priv_flags &= ~IFF_MACVLAN_PORT;
	netdev_rx_handler_unरेजिस्टर(dev);

	/* After this poपूर्णांक, no packet can schedule bc_work anymore,
	 * but we need to cancel it and purge left skbs अगर any.
	 */
	cancel_work_sync(&port->bc_work);

	जबतक ((skb = __skb_dequeue(&port->bc_queue))) अणु
		स्थिर काष्ठा macvlan_dev *src = MACVLAN_SKB_CB(skb)->src;

		अगर (src)
			dev_put(src->dev);

		kमुक्त_skb(skb);
	पूर्ण

	/* If the lower device address has been changed by passthru
	 * macvlan, put it back.
	 */
	अगर (macvlan_passthru(port) &&
	    !ether_addr_equal(port->dev->dev_addr, port->perm_addr)) अणु
		काष्ठा sockaddr sa;

		sa.sa_family = port->dev->type;
		स_नकल(&sa.sa_data, port->perm_addr, port->dev->addr_len);
		dev_set_mac_address(port->dev, &sa, शून्य);
	पूर्ण

	kमुक्त(port);
पूर्ण

अटल पूर्णांक macvlan_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *nla, *head;
	पूर्णांक rem, len;

	अगर (tb[IFLA_ADDRESS]) अणु
		अगर (nla_len(tb[IFLA_ADDRESS]) != ETH_ALEN)
			वापस -EINVAL;
		अगर (!is_valid_ether_addr(nla_data(tb[IFLA_ADDRESS])))
			वापस -EADDRNOTAVAIL;
	पूर्ण

	अगर (!data)
		वापस 0;

	अगर (data[IFLA_MACVLAN_FLAGS] &&
	    nla_get_u16(data[IFLA_MACVLAN_FLAGS]) & ~(MACVLAN_FLAG_NOPROMISC |
						      MACVLAN_FLAG_NODST))
		वापस -EINVAL;

	अगर (data[IFLA_MACVLAN_MODE]) अणु
		चयन (nla_get_u32(data[IFLA_MACVLAN_MODE])) अणु
		हाल MACVLAN_MODE_PRIVATE:
		हाल MACVLAN_MODE_VEPA:
		हाल MACVLAN_MODE_BRIDGE:
		हाल MACVLAN_MODE_PASSTHRU:
		हाल MACVLAN_MODE_SOURCE:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (data[IFLA_MACVLAN_MACADDR_MODE]) अणु
		चयन (nla_get_u32(data[IFLA_MACVLAN_MACADDR_MODE])) अणु
		हाल MACVLAN_MACADDR_ADD:
		हाल MACVLAN_MACADDR_DEL:
		हाल MACVLAN_MACADDR_FLUSH:
		हाल MACVLAN_MACADDR_SET:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (data[IFLA_MACVLAN_MACADDR]) अणु
		अगर (nla_len(data[IFLA_MACVLAN_MACADDR]) != ETH_ALEN)
			वापस -EINVAL;

		अगर (!is_valid_ether_addr(nla_data(data[IFLA_MACVLAN_MACADDR])))
			वापस -EADDRNOTAVAIL;
	पूर्ण

	अगर (data[IFLA_MACVLAN_MACADDR_DATA]) अणु
		head = nla_data(data[IFLA_MACVLAN_MACADDR_DATA]);
		len = nla_len(data[IFLA_MACVLAN_MACADDR_DATA]);

		nla_क्रम_each_attr(nla, head, len, rem) अणु
			अगर (nla_type(nla) != IFLA_MACVLAN_MACADDR ||
			    nla_len(nla) != ETH_ALEN)
				वापस -EINVAL;

			अगर (!is_valid_ether_addr(nla_data(nla)))
				वापस -EADDRNOTAVAIL;
		पूर्ण
	पूर्ण

	अगर (data[IFLA_MACVLAN_MACADDR_COUNT])
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * reconfigure list of remote source mac address
 * (only क्रम macvlan devices in source mode)
 * Note regarding alignment: all netlink data is aligned to 4 Byte, which
 * suffices क्रम both ether_addr_copy and ether_addr_equal_64bits usage.
 */
अटल पूर्णांक macvlan_changelink_sources(काष्ठा macvlan_dev *vlan, u32 mode,
				      काष्ठा nlattr *data[])
अणु
	अक्षर *addr = शून्य;
	पूर्णांक ret, rem, len;
	काष्ठा nlattr *nla, *head;
	काष्ठा macvlan_source_entry *entry;

	अगर (data[IFLA_MACVLAN_MACADDR])
		addr = nla_data(data[IFLA_MACVLAN_MACADDR]);

	अगर (mode == MACVLAN_MACADDR_ADD) अणु
		अगर (!addr)
			वापस -EINVAL;

		वापस macvlan_hash_add_source(vlan, addr);

	पूर्ण अन्यथा अगर (mode == MACVLAN_MACADDR_DEL) अणु
		अगर (!addr)
			वापस -EINVAL;

		entry = macvlan_hash_lookup_source(vlan, addr);
		अगर (entry) अणु
			macvlan_hash_del_source(entry);
			vlan->macaddr_count--;
		पूर्ण
	पूर्ण अन्यथा अगर (mode == MACVLAN_MACADDR_FLUSH) अणु
		macvlan_flush_sources(vlan->port, vlan);
	पूर्ण अन्यथा अगर (mode == MACVLAN_MACADDR_SET) अणु
		macvlan_flush_sources(vlan->port, vlan);

		अगर (addr) अणु
			ret = macvlan_hash_add_source(vlan, addr);
			अगर (ret)
				वापस ret;
		पूर्ण

		अगर (!data[IFLA_MACVLAN_MACADDR_DATA])
			वापस 0;

		head = nla_data(data[IFLA_MACVLAN_MACADDR_DATA]);
		len = nla_len(data[IFLA_MACVLAN_MACADDR_DATA]);

		nla_क्रम_each_attr(nla, head, len, rem) अणु
			addr = nla_data(nla);
			ret = macvlan_hash_add_source(vlan, addr);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक macvlan_common_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			   काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);
	काष्ठा macvlan_port *port;
	काष्ठा net_device *lowerdev;
	पूर्णांक err;
	पूर्णांक macmode;
	bool create = false;

	अगर (!tb[IFLA_LINK])
		वापस -EINVAL;

	lowerdev = __dev_get_by_index(src_net, nla_get_u32(tb[IFLA_LINK]));
	अगर (lowerdev == शून्य)
		वापस -ENODEV;

	/* When creating macvlans or macvtaps on top of other macvlans - use
	 * the real device as the lowerdev.
	 */
	अगर (netअगर_is_macvlan(lowerdev))
		lowerdev = macvlan_dev_real_dev(lowerdev);

	अगर (!tb[IFLA_MTU])
		dev->mtu = lowerdev->mtu;
	अन्यथा अगर (dev->mtu > lowerdev->mtu)
		वापस -EINVAL;

	/* MTU range: 68 - lowerdev->max_mtu */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = lowerdev->max_mtu;

	अगर (!tb[IFLA_ADDRESS])
		eth_hw_addr_अक्रमom(dev);

	अगर (!netअगर_is_macvlan_port(lowerdev)) अणु
		err = macvlan_port_create(lowerdev);
		अगर (err < 0)
			वापस err;
		create = true;
	पूर्ण
	port = macvlan_port_get_rtnl(lowerdev);

	/* Only 1 macvlan device can be created in passthru mode */
	अगर (macvlan_passthru(port)) अणु
		/* The macvlan port must be not created this समय,
		 * still जाओ destroy_macvlan_port क्रम पढ़ोability.
		 */
		err = -EINVAL;
		जाओ destroy_macvlan_port;
	पूर्ण

	vlan->lowerdev = lowerdev;
	vlan->dev      = dev;
	vlan->port     = port;
	vlan->set_features = MACVLAN_FEATURES;

	vlan->mode     = MACVLAN_MODE_VEPA;
	अगर (data && data[IFLA_MACVLAN_MODE])
		vlan->mode = nla_get_u32(data[IFLA_MACVLAN_MODE]);

	अगर (data && data[IFLA_MACVLAN_FLAGS])
		vlan->flags = nla_get_u16(data[IFLA_MACVLAN_FLAGS]);

	अगर (vlan->mode == MACVLAN_MODE_PASSTHRU) अणु
		अगर (port->count) अणु
			err = -EINVAL;
			जाओ destroy_macvlan_port;
		पूर्ण
		macvlan_set_passthru(port);
		eth_hw_addr_inherit(dev, lowerdev);
	पूर्ण

	अगर (data && data[IFLA_MACVLAN_MACADDR_MODE]) अणु
		अगर (vlan->mode != MACVLAN_MODE_SOURCE) अणु
			err = -EINVAL;
			जाओ destroy_macvlan_port;
		पूर्ण
		macmode = nla_get_u32(data[IFLA_MACVLAN_MACADDR_MODE]);
		err = macvlan_changelink_sources(vlan, macmode, data);
		अगर (err)
			जाओ destroy_macvlan_port;
	पूर्ण

	vlan->bc_queue_len_req = MACVLAN_DEFAULT_BC_QUEUE_LEN;
	अगर (data && data[IFLA_MACVLAN_BC_QUEUE_LEN])
		vlan->bc_queue_len_req = nla_get_u32(data[IFLA_MACVLAN_BC_QUEUE_LEN]);

	err = रेजिस्टर_netdevice(dev);
	अगर (err < 0)
		जाओ destroy_macvlan_port;

	dev->priv_flags |= IFF_MACVLAN;
	err = netdev_upper_dev_link(lowerdev, dev, extack);
	अगर (err)
		जाओ unरेजिस्टर_netdev;

	list_add_tail_rcu(&vlan->list, &port->vlans);
	update_port_bc_queue_len(vlan->port);
	netअगर_stacked_transfer_operstate(lowerdev, dev);
	linkwatch_fire_event(dev);

	वापस 0;

unरेजिस्टर_netdev:
	/* macvlan_uninit would मुक्त the macvlan port */
	unरेजिस्टर_netdevice(dev);
	वापस err;
destroy_macvlan_port:
	/* the macvlan port may be मुक्तd by macvlan_uninit when fail to रेजिस्टर.
	 * so we destroy the macvlan port only when it's valid.
	 */
	अगर (create && macvlan_port_get_rtnl(lowerdev))
		macvlan_port_destroy(port->dev);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(macvlan_common_newlink);

अटल पूर्णांक macvlan_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			   काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			   काष्ठा netlink_ext_ack *extack)
अणु
	वापस macvlan_common_newlink(src_net, dev, tb, data, extack);
पूर्ण

व्योम macvlan_dellink(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);

	अगर (vlan->mode == MACVLAN_MODE_SOURCE)
		macvlan_flush_sources(vlan->port, vlan);
	list_del_rcu(&vlan->list);
	update_port_bc_queue_len(vlan->port);
	unरेजिस्टर_netdevice_queue(dev, head);
	netdev_upper_dev_unlink(vlan->lowerdev, dev);
पूर्ण
EXPORT_SYMBOL_GPL(macvlan_dellink);

अटल पूर्णांक macvlan_changelink(काष्ठा net_device *dev,
			      काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);
	क्रमागत macvlan_mode mode;
	bool set_mode = false;
	क्रमागत macvlan_macaddr_mode macmode;
	पूर्णांक ret;

	/* Validate mode, but करोn't set yet: setting flags may fail. */
	अगर (data && data[IFLA_MACVLAN_MODE]) अणु
		set_mode = true;
		mode = nla_get_u32(data[IFLA_MACVLAN_MODE]);
		/* Passthrough mode can't be set or cleared dynamically */
		अगर ((mode == MACVLAN_MODE_PASSTHRU) !=
		    (vlan->mode == MACVLAN_MODE_PASSTHRU))
			वापस -EINVAL;
		अगर (vlan->mode == MACVLAN_MODE_SOURCE &&
		    vlan->mode != mode)
			macvlan_flush_sources(vlan->port, vlan);
	पूर्ण

	अगर (data && data[IFLA_MACVLAN_FLAGS]) अणु
		__u16 flags = nla_get_u16(data[IFLA_MACVLAN_FLAGS]);
		bool promisc = (flags ^ vlan->flags) & MACVLAN_FLAG_NOPROMISC;
		अगर (macvlan_passthru(vlan->port) && promisc) अणु
			पूर्णांक err;

			अगर (flags & MACVLAN_FLAG_NOPROMISC)
				err = dev_set_promiscuity(vlan->lowerdev, -1);
			अन्यथा
				err = dev_set_promiscuity(vlan->lowerdev, 1);
			अगर (err < 0)
				वापस err;
		पूर्ण
		vlan->flags = flags;
	पूर्ण

	अगर (data && data[IFLA_MACVLAN_BC_QUEUE_LEN]) अणु
		vlan->bc_queue_len_req = nla_get_u32(data[IFLA_MACVLAN_BC_QUEUE_LEN]);
		update_port_bc_queue_len(vlan->port);
	पूर्ण

	अगर (set_mode)
		vlan->mode = mode;
	अगर (data && data[IFLA_MACVLAN_MACADDR_MODE]) अणु
		अगर (vlan->mode != MACVLAN_MODE_SOURCE)
			वापस -EINVAL;
		macmode = nla_get_u32(data[IFLA_MACVLAN_MACADDR_MODE]);
		ret = macvlan_changelink_sources(vlan, macmode, data);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल माप_प्रकार macvlan_get_size_mac(स्थिर काष्ठा macvlan_dev *vlan)
अणु
	अगर (vlan->macaddr_count == 0)
		वापस 0;
	वापस nla_total_size(0) /* IFLA_MACVLAN_MACADDR_DATA */
		+ vlan->macaddr_count * nla_total_size(माप(u8) * ETH_ALEN);
पूर्ण

अटल माप_प्रकार macvlan_get_size(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);

	वापस (0
		+ nla_total_size(4) /* IFLA_MACVLAN_MODE */
		+ nla_total_size(2) /* IFLA_MACVLAN_FLAGS */
		+ nla_total_size(4) /* IFLA_MACVLAN_MACADDR_COUNT */
		+ macvlan_get_size_mac(vlan) /* IFLA_MACVLAN_MACADDR */
		+ nla_total_size(4) /* IFLA_MACVLAN_BC_QUEUE_LEN */
		+ nla_total_size(4) /* IFLA_MACVLAN_BC_QUEUE_LEN_USED */
		);
पूर्ण

अटल पूर्णांक macvlan_fill_info_macaddr(काष्ठा sk_buff *skb,
				     स्थिर काष्ठा macvlan_dev *vlan,
				     स्थिर पूर्णांक i)
अणु
	काष्ठा hlist_head *h = &vlan->port->vlan_source_hash[i];
	काष्ठा macvlan_source_entry *entry;

	hlist_क्रम_each_entry_rcu(entry, h, hlist) अणु
		अगर (entry->vlan != vlan)
			जारी;
		अगर (nla_put(skb, IFLA_MACVLAN_MACADDR, ETH_ALEN, entry->addr))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक macvlan_fill_info(काष्ठा sk_buff *skb,
				स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(dev);
	काष्ठा macvlan_port *port = vlan->port;
	पूर्णांक i;
	काष्ठा nlattr *nest;

	अगर (nla_put_u32(skb, IFLA_MACVLAN_MODE, vlan->mode))
		जाओ nla_put_failure;
	अगर (nla_put_u16(skb, IFLA_MACVLAN_FLAGS, vlan->flags))
		जाओ nla_put_failure;
	अगर (nla_put_u32(skb, IFLA_MACVLAN_MACADDR_COUNT, vlan->macaddr_count))
		जाओ nla_put_failure;
	अगर (vlan->macaddr_count > 0) अणु
		nest = nla_nest_start_noflag(skb, IFLA_MACVLAN_MACADDR_DATA);
		अगर (nest == शून्य)
			जाओ nla_put_failure;

		क्रम (i = 0; i < MACVLAN_HASH_SIZE; i++) अणु
			अगर (macvlan_fill_info_macaddr(skb, vlan, i))
				जाओ nla_put_failure;
		पूर्ण
		nla_nest_end(skb, nest);
	पूर्ण
	अगर (nla_put_u32(skb, IFLA_MACVLAN_BC_QUEUE_LEN, vlan->bc_queue_len_req))
		जाओ nla_put_failure;
	अगर (nla_put_u32(skb, IFLA_MACVLAN_BC_QUEUE_LEN_USED, port->bc_queue_len_used))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल स्थिर काष्ठा nla_policy macvlan_policy[IFLA_MACVLAN_MAX + 1] = अणु
	[IFLA_MACVLAN_MODE]  = अणु .type = NLA_U32 पूर्ण,
	[IFLA_MACVLAN_FLAGS] = अणु .type = NLA_U16 पूर्ण,
	[IFLA_MACVLAN_MACADDR_MODE] = अणु .type = NLA_U32 पूर्ण,
	[IFLA_MACVLAN_MACADDR] = अणु .type = NLA_BINARY, .len = MAX_ADDR_LEN पूर्ण,
	[IFLA_MACVLAN_MACADDR_DATA] = अणु .type = NLA_NESTED पूर्ण,
	[IFLA_MACVLAN_MACADDR_COUNT] = अणु .type = NLA_U32 पूर्ण,
	[IFLA_MACVLAN_BC_QUEUE_LEN] = अणु .type = NLA_U32 पूर्ण,
	[IFLA_MACVLAN_BC_QUEUE_LEN_USED] = अणु .type = NLA_REJECT पूर्ण,
पूर्ण;

पूर्णांक macvlan_link_रेजिस्टर(काष्ठा rtnl_link_ops *ops)
अणु
	/* common fields */
	ops->validate		= macvlan_validate;
	ops->maxtype		= IFLA_MACVLAN_MAX;
	ops->policy		= macvlan_policy;
	ops->changelink		= macvlan_changelink;
	ops->get_size		= macvlan_get_size;
	ops->fill_info		= macvlan_fill_info;

	वापस rtnl_link_रेजिस्टर(ops);
पूर्ण;
EXPORT_SYMBOL_GPL(macvlan_link_रेजिस्टर);

अटल काष्ठा net *macvlan_get_link_net(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev_net(macvlan_dev_real_dev(dev));
पूर्ण

अटल काष्ठा rtnl_link_ops macvlan_link_ops = अणु
	.kind		= "macvlan",
	.setup		= macvlan_setup,
	.newlink	= macvlan_newlink,
	.dellink	= macvlan_dellink,
	.get_link_net	= macvlan_get_link_net,
	.priv_size      = माप(काष्ठा macvlan_dev),
पूर्ण;

अटल व्योम update_port_bc_queue_len(काष्ठा macvlan_port *port)
अणु
	u32 max_bc_queue_len_req = 0;
	काष्ठा macvlan_dev *vlan;

	list_क्रम_each_entry(vlan, &port->vlans, list) अणु
		अगर (vlan->bc_queue_len_req > max_bc_queue_len_req)
			max_bc_queue_len_req = vlan->bc_queue_len_req;
	पूर्ण
	port->bc_queue_len_used = max_bc_queue_len_req;
पूर्ण

अटल पूर्णांक macvlan_device_event(काष्ठा notअगरier_block *unused,
				अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा macvlan_dev *vlan, *next;
	काष्ठा macvlan_port *port;
	LIST_HEAD(list_समाप्त);

	अगर (!netअगर_is_macvlan_port(dev))
		वापस NOTIFY_DONE;

	port = macvlan_port_get_rtnl(dev);

	चयन (event) अणु
	हाल NETDEV_UP:
	हाल NETDEV_DOWN:
	हाल NETDEV_CHANGE:
		list_क्रम_each_entry(vlan, &port->vlans, list)
			netअगर_stacked_transfer_operstate(vlan->lowerdev,
							 vlan->dev);
		अवरोध;
	हाल NETDEV_FEAT_CHANGE:
		list_क्रम_each_entry(vlan, &port->vlans, list) अणु
			vlan->dev->gso_max_size = dev->gso_max_size;
			vlan->dev->gso_max_segs = dev->gso_max_segs;
			netdev_update_features(vlan->dev);
		पूर्ण
		अवरोध;
	हाल NETDEV_CHANGEMTU:
		list_क्रम_each_entry(vlan, &port->vlans, list) अणु
			अगर (vlan->dev->mtu <= dev->mtu)
				जारी;
			dev_set_mtu(vlan->dev, dev->mtu);
		पूर्ण
		अवरोध;
	हाल NETDEV_CHANGEADDR:
		अगर (!macvlan_passthru(port))
			वापस NOTIFY_DONE;

		vlan = list_first_entry_or_null(&port->vlans,
						काष्ठा macvlan_dev,
						list);

		अगर (vlan && macvlan_sync_address(vlan->dev, dev->dev_addr))
			वापस NOTIFY_BAD;

		अवरोध;
	हाल NETDEV_UNREGISTER:
		/* twiddle thumbs on netns device moves */
		अगर (dev->reg_state != NETREG_UNREGISTERING)
			अवरोध;

		list_क्रम_each_entry_safe(vlan, next, &port->vlans, list)
			vlan->dev->rtnl_link_ops->dellink(vlan->dev, &list_समाप्त);
		unरेजिस्टर_netdevice_many(&list_समाप्त);
		अवरोध;
	हाल NETDEV_PRE_TYPE_CHANGE:
		/* Forbid underlaying device to change its type. */
		वापस NOTIFY_BAD;

	हाल NETDEV_NOTIFY_PEERS:
	हाल NETDEV_BONDING_FAILOVER:
	हाल NETDEV_RESEND_IGMP:
		/* Propagate to all vlans */
		list_क्रम_each_entry(vlan, &port->vlans, list)
			call_netdevice_notअगरiers(event, vlan->dev);
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block macvlan_notअगरier_block __पढ़ो_mostly = अणु
	.notअगरier_call	= macvlan_device_event,
पूर्ण;

अटल पूर्णांक __init macvlan_init_module(व्योम)
अणु
	पूर्णांक err;

	रेजिस्टर_netdevice_notअगरier(&macvlan_notअगरier_block);

	err = macvlan_link_रेजिस्टर(&macvlan_link_ops);
	अगर (err < 0)
		जाओ err1;
	वापस 0;
err1:
	unरेजिस्टर_netdevice_notअगरier(&macvlan_notअगरier_block);
	वापस err;
पूर्ण

अटल व्योम __निकास macvlan_cleanup_module(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&macvlan_link_ops);
	unरेजिस्टर_netdevice_notअगरier(&macvlan_notअगरier_block);
पूर्ण

module_init(macvlan_init_module);
module_निकास(macvlan_cleanup_module);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_DESCRIPTION("Driver for MAC address based VLANs");
MODULE_ALIAS_RTNL_LINK("macvlan");
