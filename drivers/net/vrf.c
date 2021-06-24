<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * vrf.c: device driver to encapsulate a VRF space
 *
 * Copyright (c) 2015 Cumulus Networks. All rights reserved.
 * Copyright (c) 2015 Shrijeet Mukherjee <shm@cumulusnetworks.com>
 * Copyright (c) 2015 David Ahern <dsa@cumulusnetworks.com>
 *
 * Based on dummy, team and ipvlan drivers
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/init.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/rtnetlink.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/spinlock_types.h>

#समावेश <linux/inetdevice.h>
#समावेश <net/arp.h>
#समावेश <net/ip.h>
#समावेश <net/ip_fib.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/ip6_route.h>
#समावेश <net/route.h>
#समावेश <net/addrconf.h>
#समावेश <net/l3mdev.h>
#समावेश <net/fib_rules.h>
#समावेश <net/netns/generic.h>

#घोषणा DRV_NAME	"vrf"
#घोषणा DRV_VERSION	"1.1"

#घोषणा FIB_RULE_PREF  1000       /* शेष preference क्रम FIB rules */

#घोषणा HT_MAP_BITS	4
#घोषणा HASH_INITVAL	((u32)0xcafef00d)

काष्ठा  vrf_map अणु
	DECLARE_HASHTABLE(ht, HT_MAP_BITS);
	spinlock_t vmap_lock;

	/* shared_tables:
	 * count how many distinct tables करो not comply with the strict mode
	 * requirement.
	 * shared_tables value must be 0 in order to enable the strict mode.
	 *
	 * example of the evolution of shared_tables:
	 *                                                        | समय
	 * add  vrf0 --> table 100        shared_tables = 0       | t0
	 * add  vrf1 --> table 101        shared_tables = 0       | t1
	 * add  vrf2 --> table 100        shared_tables = 1       | t2
	 * add  vrf3 --> table 100        shared_tables = 1       | t3
	 * add  vrf4 --> table 101        shared_tables = 2       v t4
	 *
	 * shared_tables is a "step function" (or "staircase function")
	 * and it is increased by one when the second vrf is associated to a
	 * table.
	 *
	 * at t2, vrf0 and vrf2 are bound to table 100: shared_tables = 1.
	 *
	 * at t3, another dev (vrf3) is bound to the same table 100 but the
	 * value of shared_tables is still 1.
	 * This means that no matter how many new vrfs will रेजिस्टर on the
	 * table 100, the shared_tables will not increase (considering only
	 * table 100).
	 *
	 * at t4, vrf4 is bound to table 101, and shared_tables = 2.
	 *
	 * Looking at the value of shared_tables we can immediately know अगर
	 * the strict_mode can or cannot be enक्रमced. Indeed, strict_mode
	 * can be enक्रमced अगरf shared_tables = 0.
	 *
	 * Conversely, shared_tables is decreased when a vrf is de-associated
	 * from a table with exactly two associated vrfs.
	 */
	u32 shared_tables;

	bool strict_mode;
पूर्ण;

काष्ठा vrf_map_elem अणु
	काष्ठा hlist_node hnode;
	काष्ठा list_head vrf_list;  /* VRFs रेजिस्टरed to this table */

	u32 table_id;
	पूर्णांक users;
	पूर्णांक अगरindex;
पूर्ण;

अटल अचिन्हित पूर्णांक vrf_net_id;

/* per netns vrf data */
काष्ठा netns_vrf अणु
	/* रक्षित by rtnl lock */
	bool add_fib_rules;

	काष्ठा vrf_map vmap;
	काष्ठा ctl_table_header	*ctl_hdr;
पूर्ण;

काष्ठा net_vrf अणु
	काष्ठा rtable __rcu	*rth;
	काष्ठा rt6_info	__rcu	*rt6;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा fib6_table	*fib6_table;
#पूर्ण_अगर
	u32                     tb_id;

	काष्ठा list_head	me_list;   /* entry in vrf_map_elem */
	पूर्णांक			अगरindex;
पूर्ण;

काष्ठा pcpu_dstats अणु
	u64			tx_pkts;
	u64			tx_bytes;
	u64			tx_drps;
	u64			rx_pkts;
	u64			rx_bytes;
	u64			rx_drps;
	काष्ठा u64_stats_sync	syncp;
पूर्ण;

अटल व्योम vrf_rx_stats(काष्ठा net_device *dev, पूर्णांक len)
अणु
	काष्ठा pcpu_dstats *dstats = this_cpu_ptr(dev->dstats);

	u64_stats_update_begin(&dstats->syncp);
	dstats->rx_pkts++;
	dstats->rx_bytes += len;
	u64_stats_update_end(&dstats->syncp);
पूर्ण

अटल व्योम vrf_tx_error(काष्ठा net_device *vrf_dev, काष्ठा sk_buff *skb)
अणु
	vrf_dev->stats.tx_errors++;
	kमुक्त_skb(skb);
पूर्ण

अटल व्योम vrf_get_stats64(काष्ठा net_device *dev,
			    काष्ठा rtnl_link_stats64 *stats)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		स्थिर काष्ठा pcpu_dstats *dstats;
		u64 tbytes, tpkts, tdrops, rbytes, rpkts;
		अचिन्हित पूर्णांक start;

		dstats = per_cpu_ptr(dev->dstats, i);
		करो अणु
			start = u64_stats_fetch_begin_irq(&dstats->syncp);
			tbytes = dstats->tx_bytes;
			tpkts = dstats->tx_pkts;
			tdrops = dstats->tx_drps;
			rbytes = dstats->rx_bytes;
			rpkts = dstats->rx_pkts;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&dstats->syncp, start));
		stats->tx_bytes += tbytes;
		stats->tx_packets += tpkts;
		stats->tx_dropped += tdrops;
		stats->rx_bytes += rbytes;
		stats->rx_packets += rpkts;
	पूर्ण
पूर्ण

अटल काष्ठा vrf_map *netns_vrf_map(काष्ठा net *net)
अणु
	काष्ठा netns_vrf *nn_vrf = net_generic(net, vrf_net_id);

	वापस &nn_vrf->vmap;
पूर्ण

अटल काष्ठा vrf_map *netns_vrf_map_by_dev(काष्ठा net_device *dev)
अणु
	वापस netns_vrf_map(dev_net(dev));
पूर्ण

अटल पूर्णांक vrf_map_elem_get_vrf_अगरindex(काष्ठा vrf_map_elem *me)
अणु
	काष्ठा list_head *me_head = &me->vrf_list;
	काष्ठा net_vrf *vrf;

	अगर (list_empty(me_head))
		वापस -ENODEV;

	vrf = list_first_entry(me_head, काष्ठा net_vrf, me_list);

	वापस vrf->अगरindex;
पूर्ण

अटल काष्ठा vrf_map_elem *vrf_map_elem_alloc(gfp_t flags)
अणु
	काष्ठा vrf_map_elem *me;

	me = kदो_स्मृति(माप(*me), flags);
	अगर (!me)
		वापस शून्य;

	वापस me;
पूर्ण

अटल व्योम vrf_map_elem_मुक्त(काष्ठा vrf_map_elem *me)
अणु
	kमुक्त(me);
पूर्ण

अटल व्योम vrf_map_elem_init(काष्ठा vrf_map_elem *me, पूर्णांक table_id,
			      पूर्णांक अगरindex, पूर्णांक users)
अणु
	me->table_id = table_id;
	me->अगरindex = अगरindex;
	me->users = users;
	INIT_LIST_HEAD(&me->vrf_list);
पूर्ण

अटल काष्ठा vrf_map_elem *vrf_map_lookup_elem(काष्ठा vrf_map *vmap,
						u32 table_id)
अणु
	काष्ठा vrf_map_elem *me;
	u32 key;

	key = jhash_1word(table_id, HASH_INITVAL);
	hash_क्रम_each_possible(vmap->ht, me, hnode, key) अणु
		अगर (me->table_id == table_id)
			वापस me;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम vrf_map_add_elem(काष्ठा vrf_map *vmap, काष्ठा vrf_map_elem *me)
अणु
	u32 table_id = me->table_id;
	u32 key;

	key = jhash_1word(table_id, HASH_INITVAL);
	hash_add(vmap->ht, &me->hnode, key);
पूर्ण

अटल व्योम vrf_map_del_elem(काष्ठा vrf_map_elem *me)
अणु
	hash_del(&me->hnode);
पूर्ण

अटल व्योम vrf_map_lock(काष्ठा vrf_map *vmap) __acquires(&vmap->vmap_lock)
अणु
	spin_lock(&vmap->vmap_lock);
पूर्ण

अटल व्योम vrf_map_unlock(काष्ठा vrf_map *vmap) __releases(&vmap->vmap_lock)
अणु
	spin_unlock(&vmap->vmap_lock);
पूर्ण

/* called with rtnl lock held */
अटल पूर्णांक
vrf_map_रेजिस्टर_dev(काष्ठा net_device *dev, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा vrf_map *vmap = netns_vrf_map_by_dev(dev);
	काष्ठा net_vrf *vrf = netdev_priv(dev);
	काष्ठा vrf_map_elem *new_me, *me;
	u32 table_id = vrf->tb_id;
	bool मुक्त_new_me = false;
	पूर्णांक users;
	पूर्णांक res;

	/* we pre-allocate elements used in the spin-locked section (so that we
	 * keep the spinlock as लघु as possibile).
	 */
	new_me = vrf_map_elem_alloc(GFP_KERNEL);
	अगर (!new_me)
		वापस -ENOMEM;

	vrf_map_elem_init(new_me, table_id, dev->अगरindex, 0);

	vrf_map_lock(vmap);

	me = vrf_map_lookup_elem(vmap, table_id);
	अगर (!me) अणु
		me = new_me;
		vrf_map_add_elem(vmap, me);
		जाओ link_vrf;
	पूर्ण

	/* we alपढ़ोy have an entry in the vrf_map, so it means there is (at
	 * least) a vrf रेजिस्टरed on the specअगरic table.
	 */
	मुक्त_new_me = true;
	अगर (vmap->strict_mode) अणु
		/* vrfs cannot share the same table */
		NL_SET_ERR_MSG(extack, "Table is used by another VRF");
		res = -EBUSY;
		जाओ unlock;
	पूर्ण

link_vrf:
	users = ++me->users;
	अगर (users == 2)
		++vmap->shared_tables;

	list_add(&vrf->me_list, &me->vrf_list);

	res = 0;

unlock:
	vrf_map_unlock(vmap);

	/* clean-up, अगर needed */
	अगर (मुक्त_new_me)
		vrf_map_elem_मुक्त(new_me);

	वापस res;
पूर्ण

/* called with rtnl lock held */
अटल व्योम vrf_map_unरेजिस्टर_dev(काष्ठा net_device *dev)
अणु
	काष्ठा vrf_map *vmap = netns_vrf_map_by_dev(dev);
	काष्ठा net_vrf *vrf = netdev_priv(dev);
	u32 table_id = vrf->tb_id;
	काष्ठा vrf_map_elem *me;
	पूर्णांक users;

	vrf_map_lock(vmap);

	me = vrf_map_lookup_elem(vmap, table_id);
	अगर (!me)
		जाओ unlock;

	list_del(&vrf->me_list);

	users = --me->users;
	अगर (users == 1) अणु
		--vmap->shared_tables;
	पूर्ण अन्यथा अगर (users == 0) अणु
		vrf_map_del_elem(me);

		/* no one will refer to this element anymore */
		vrf_map_elem_मुक्त(me);
	पूर्ण

unlock:
	vrf_map_unlock(vmap);
पूर्ण

/* वापस the vrf device index associated with the table_id */
अटल पूर्णांक vrf_अगरindex_lookup_by_table_id(काष्ठा net *net, u32 table_id)
अणु
	काष्ठा vrf_map *vmap = netns_vrf_map(net);
	काष्ठा vrf_map_elem *me;
	पूर्णांक अगरindex;

	vrf_map_lock(vmap);

	अगर (!vmap->strict_mode) अणु
		अगरindex = -EPERM;
		जाओ unlock;
	पूर्ण

	me = vrf_map_lookup_elem(vmap, table_id);
	अगर (!me) अणु
		अगरindex = -ENODEV;
		जाओ unlock;
	पूर्ण

	अगरindex = vrf_map_elem_get_vrf_अगरindex(me);

unlock:
	vrf_map_unlock(vmap);

	वापस अगरindex;
पूर्ण

/* by शेष VRF devices करो not have a qdisc and are expected
 * to be created with only a single queue.
 */
अटल bool qdisc_tx_is_शेष(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा netdev_queue *txq;
	काष्ठा Qdisc *qdisc;

	अगर (dev->num_tx_queues > 1)
		वापस false;

	txq = netdev_get_tx_queue(dev, 0);
	qdisc = rcu_access_poपूर्णांकer(txq->qdisc);

	वापस !qdisc->enqueue;
पूर्ण

/* Local traffic destined to local address. Reinsert the packet to rx
 * path, similar to loopback handling.
 */
अटल पूर्णांक vrf_local_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			  काष्ठा dst_entry *dst)
अणु
	पूर्णांक len = skb->len;

	skb_orphan(skb);

	skb_dst_set(skb, dst);

	/* set pkt_type to aव्योम skb hitting packet taps twice -
	 * once on Tx and again in Rx processing
	 */
	skb->pkt_type = PACKET_LOOPBACK;

	skb->protocol = eth_type_trans(skb, dev);

	अगर (likely(netअगर_rx(skb) == NET_RX_SUCCESS))
		vrf_rx_stats(dev, len);
	अन्यथा
		this_cpu_inc(dev->dstats->rx_drps);

	वापस NETDEV_TX_OK;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक vrf_ip6_local_out(काष्ठा net *net, काष्ठा sock *sk,
			     काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	err = nf_hook(NFPROTO_IPV6, NF_INET_LOCAL_OUT, net,
		      sk, skb, शून्य, skb_dst(skb)->dev, dst_output);

	अगर (likely(err == 1))
		err = dst_output(net, sk, skb);

	वापस err;
पूर्ण

अटल netdev_tx_t vrf_process_v6_outbound(काष्ठा sk_buff *skb,
					   काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा ipv6hdr *iph;
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा flowi6 fl6;
	पूर्णांक ret = NET_XMIT_DROP;
	काष्ठा dst_entry *dst;
	काष्ठा dst_entry *dst_null = &net->ipv6.ip6_null_entry->dst;

	अगर (!pskb_may_pull(skb, ETH_HLEN + माप(काष्ठा ipv6hdr)))
		जाओ err;

	iph = ipv6_hdr(skb);

	स_रखो(&fl6, 0, माप(fl6));
	/* needed to match OIF rule */
	fl6.flowi6_oअगर = dev->अगरindex;
	fl6.flowi6_iअगर = LOOPBACK_IFINDEX;
	fl6.daddr = iph->daddr;
	fl6.saddr = iph->saddr;
	fl6.flowlabel = ip6_flowinfo(iph);
	fl6.flowi6_mark = skb->mark;
	fl6.flowi6_proto = iph->nexthdr;
	fl6.flowi6_flags = FLOWI_FLAG_SKIP_NH_OIF;

	dst = ip6_dst_lookup_flow(net, शून्य, &fl6, शून्य);
	अगर (IS_ERR(dst) || dst == dst_null)
		जाओ err;

	skb_dst_drop(skb);

	/* अगर dst.dev is the VRF device again this is locally originated traffic
	 * destined to a local address. Short circuit to Rx path.
	 */
	अगर (dst->dev == dev)
		वापस vrf_local_xmit(skb, dev, dst);

	skb_dst_set(skb, dst);

	/* strip the ethernet header added क्रम pass through VRF device */
	__skb_pull(skb, skb_network_offset(skb));

	ret = vrf_ip6_local_out(net, skb->sk, skb);
	अगर (unlikely(net_xmit_eval(ret)))
		dev->stats.tx_errors++;
	अन्यथा
		ret = NET_XMIT_SUCCESS;

	वापस ret;
err:
	vrf_tx_error(dev, skb);
	वापस NET_XMIT_DROP;
पूर्ण
#अन्यथा
अटल netdev_tx_t vrf_process_v6_outbound(काष्ठा sk_buff *skb,
					   काष्ठा net_device *dev)
अणु
	vrf_tx_error(dev, skb);
	वापस NET_XMIT_DROP;
पूर्ण
#पूर्ण_अगर

/* based on ip_local_out; can't use it b/c the dst is चयनed poपूर्णांकing to us */
अटल पूर्णांक vrf_ip_local_out(काष्ठा net *net, काष्ठा sock *sk,
			    काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	err = nf_hook(NFPROTO_IPV4, NF_INET_LOCAL_OUT, net, sk,
		      skb, शून्य, skb_dst(skb)->dev, dst_output);
	अगर (likely(err == 1))
		err = dst_output(net, sk, skb);

	वापस err;
पूर्ण

अटल netdev_tx_t vrf_process_v4_outbound(काष्ठा sk_buff *skb,
					   काष्ठा net_device *vrf_dev)
अणु
	काष्ठा iphdr *ip4h;
	पूर्णांक ret = NET_XMIT_DROP;
	काष्ठा flowi4 fl4;
	काष्ठा net *net = dev_net(vrf_dev);
	काष्ठा rtable *rt;

	अगर (!pskb_may_pull(skb, ETH_HLEN + माप(काष्ठा iphdr)))
		जाओ err;

	ip4h = ip_hdr(skb);

	स_रखो(&fl4, 0, माप(fl4));
	/* needed to match OIF rule */
	fl4.flowi4_oअगर = vrf_dev->अगरindex;
	fl4.flowi4_iअगर = LOOPBACK_IFINDEX;
	fl4.flowi4_tos = RT_TOS(ip4h->tos);
	fl4.flowi4_flags = FLOWI_FLAG_ANYSRC | FLOWI_FLAG_SKIP_NH_OIF;
	fl4.flowi4_proto = ip4h->protocol;
	fl4.daddr = ip4h->daddr;
	fl4.saddr = ip4h->saddr;

	rt = ip_route_output_flow(net, &fl4, शून्य);
	अगर (IS_ERR(rt))
		जाओ err;

	skb_dst_drop(skb);

	/* अगर dst.dev is the VRF device again this is locally originated traffic
	 * destined to a local address. Short circuit to Rx path.
	 */
	अगर (rt->dst.dev == vrf_dev)
		वापस vrf_local_xmit(skb, vrf_dev, &rt->dst);

	skb_dst_set(skb, &rt->dst);

	/* strip the ethernet header added क्रम pass through VRF device */
	__skb_pull(skb, skb_network_offset(skb));

	अगर (!ip4h->saddr) अणु
		ip4h->saddr = inet_select_addr(skb_dst(skb)->dev, 0,
					       RT_SCOPE_LINK);
	पूर्ण

	ret = vrf_ip_local_out(dev_net(skb_dst(skb)->dev), skb->sk, skb);
	अगर (unlikely(net_xmit_eval(ret)))
		vrf_dev->stats.tx_errors++;
	अन्यथा
		ret = NET_XMIT_SUCCESS;

out:
	वापस ret;
err:
	vrf_tx_error(vrf_dev, skb);
	जाओ out;
पूर्ण

अटल netdev_tx_t is_ip_tx_frame(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		वापस vrf_process_v4_outbound(skb, dev);
	हाल htons(ETH_P_IPV6):
		वापस vrf_process_v6_outbound(skb, dev);
	शेष:
		vrf_tx_error(dev, skb);
		वापस NET_XMIT_DROP;
	पूर्ण
पूर्ण

अटल netdev_tx_t vrf_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	पूर्णांक len = skb->len;
	netdev_tx_t ret = is_ip_tx_frame(skb, dev);

	अगर (likely(ret == NET_XMIT_SUCCESS || ret == NET_XMIT_CN)) अणु
		काष्ठा pcpu_dstats *dstats = this_cpu_ptr(dev->dstats);

		u64_stats_update_begin(&dstats->syncp);
		dstats->tx_pkts++;
		dstats->tx_bytes += len;
		u64_stats_update_end(&dstats->syncp);
	पूर्ण अन्यथा अणु
		this_cpu_inc(dev->dstats->tx_drps);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम vrf_finish_direct(काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *vrf_dev = skb->dev;

	अगर (!list_empty(&vrf_dev->ptype_all) &&
	    likely(skb_headroom(skb) >= ETH_HLEN)) अणु
		काष्ठा ethhdr *eth = skb_push(skb, ETH_HLEN);

		ether_addr_copy(eth->h_source, vrf_dev->dev_addr);
		eth_zero_addr(eth->h_dest);
		eth->h_proto = skb->protocol;

		rcu_पढ़ो_lock_bh();
		dev_queue_xmit_nit(skb, vrf_dev);
		rcu_पढ़ो_unlock_bh();

		skb_pull(skb, ETH_HLEN);
	पूर्ण

	/* reset skb device */
	nf_reset_ct(skb);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
/* modelled after ip6_finish_output2 */
अटल पूर्णांक vrf_finish_output6(काष्ठा net *net, काष्ठा sock *sk,
			      काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा net_device *dev = dst->dev;
	स्थिर काष्ठा in6_addr *nexthop;
	काष्ठा neighbour *neigh;
	पूर्णांक ret;

	nf_reset_ct(skb);

	skb->protocol = htons(ETH_P_IPV6);
	skb->dev = dev;

	rcu_पढ़ो_lock_bh();
	nexthop = rt6_nexthop((काष्ठा rt6_info *)dst, &ipv6_hdr(skb)->daddr);
	neigh = __ipv6_neigh_lookup_noref(dst->dev, nexthop);
	अगर (unlikely(!neigh))
		neigh = __neigh_create(&nd_tbl, nexthop, dst->dev, false);
	अगर (!IS_ERR(neigh)) अणु
		sock_confirm_neigh(skb, neigh);
		ret = neigh_output(neigh, skb, false);
		rcu_पढ़ो_unlock_bh();
		वापस ret;
	पूर्ण
	rcu_पढ़ो_unlock_bh();

	IP6_INC_STATS(dev_net(dst->dev),
		      ip6_dst_idev(dst), IPSTATS_MIB_OUTNOROUTES);
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

/* modelled after ip6_output */
अटल पूर्णांक vrf_output6(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस NF_HOOK_COND(NFPROTO_IPV6, NF_INET_POST_ROUTING,
			    net, sk, skb, शून्य, skb_dst(skb)->dev,
			    vrf_finish_output6,
			    !(IP6CB(skb)->flags & IP6SKB_REROUTED));
पूर्ण

/* set dst on skb to send packet to us via dev_xmit path. Allows
 * packet to go through device based features such as qdisc, netfilter
 * hooks and packet sockets with skb->dev set to vrf device.
 */
अटल काष्ठा sk_buff *vrf_ip6_out_redirect(काष्ठा net_device *vrf_dev,
					    काष्ठा sk_buff *skb)
अणु
	काष्ठा net_vrf *vrf = netdev_priv(vrf_dev);
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा rt6_info *rt6;

	rcu_पढ़ो_lock();

	rt6 = rcu_dereference(vrf->rt6);
	अगर (likely(rt6)) अणु
		dst = &rt6->dst;
		dst_hold(dst);
	पूर्ण

	rcu_पढ़ो_unlock();

	अगर (unlikely(!dst)) अणु
		vrf_tx_error(vrf_dev, skb);
		वापस शून्य;
	पूर्ण

	skb_dst_drop(skb);
	skb_dst_set(skb, dst);

	वापस skb;
पूर्ण

अटल पूर्णांक vrf_output6_direct_finish(काष्ठा net *net, काष्ठा sock *sk,
				     काष्ठा sk_buff *skb)
अणु
	vrf_finish_direct(skb);

	वापस vrf_ip6_local_out(net, sk, skb);
पूर्ण

अटल पूर्णांक vrf_output6_direct(काष्ठा net *net, काष्ठा sock *sk,
			      काष्ठा sk_buff *skb)
अणु
	पूर्णांक err = 1;

	skb->protocol = htons(ETH_P_IPV6);

	अगर (!(IPCB(skb)->flags & IPSKB_REROUTED))
		err = nf_hook(NFPROTO_IPV6, NF_INET_POST_ROUTING, net, sk, skb,
			      शून्य, skb->dev, vrf_output6_direct_finish);

	अगर (likely(err == 1))
		vrf_finish_direct(skb);

	वापस err;
पूर्ण

अटल पूर्णांक vrf_ip6_out_direct_finish(काष्ठा net *net, काष्ठा sock *sk,
				     काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	err = vrf_output6_direct(net, sk, skb);
	अगर (likely(err == 1))
		err = vrf_ip6_local_out(net, sk, skb);

	वापस err;
पूर्ण

अटल काष्ठा sk_buff *vrf_ip6_out_direct(काष्ठा net_device *vrf_dev,
					  काष्ठा sock *sk,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा net *net = dev_net(vrf_dev);
	पूर्णांक err;

	skb->dev = vrf_dev;

	err = nf_hook(NFPROTO_IPV6, NF_INET_LOCAL_OUT, net, sk,
		      skb, शून्य, vrf_dev, vrf_ip6_out_direct_finish);

	अगर (likely(err == 1))
		err = vrf_output6_direct(net, sk, skb);

	अगर (likely(err == 1))
		वापस skb;

	वापस शून्य;
पूर्ण

अटल काष्ठा sk_buff *vrf_ip6_out(काष्ठा net_device *vrf_dev,
				   काष्ठा sock *sk,
				   काष्ठा sk_buff *skb)
अणु
	/* करोn't भागert link scope packets */
	अगर (rt6_need_strict(&ipv6_hdr(skb)->daddr))
		वापस skb;

	अगर (qdisc_tx_is_शेष(vrf_dev) ||
	    IP6CB(skb)->flags & IP6SKB_XFRM_TRANSFORMED)
		वापस vrf_ip6_out_direct(vrf_dev, sk, skb);

	वापस vrf_ip6_out_redirect(vrf_dev, skb);
पूर्ण

/* holding rtnl */
अटल व्योम vrf_rt6_release(काष्ठा net_device *dev, काष्ठा net_vrf *vrf)
अणु
	काष्ठा rt6_info *rt6 = rtnl_dereference(vrf->rt6);
	काष्ठा net *net = dev_net(dev);
	काष्ठा dst_entry *dst;

	RCU_INIT_POINTER(vrf->rt6, शून्य);
	synchronize_rcu();

	/* move dev in dst's to loopback so this VRF device can be deleted
	 * - based on dst_अगरकरोwn
	 */
	अगर (rt6) अणु
		dst = &rt6->dst;
		dev_put(dst->dev);
		dst->dev = net->loopback_dev;
		dev_hold(dst->dev);
		dst_release(dst);
	पूर्ण
पूर्ण

अटल पूर्णांक vrf_rt6_create(काष्ठा net_device *dev)
अणु
	पूर्णांक flags = DST_NOPOLICY | DST_NOXFRM;
	काष्ठा net_vrf *vrf = netdev_priv(dev);
	काष्ठा net *net = dev_net(dev);
	काष्ठा rt6_info *rt6;
	पूर्णांक rc = -ENOMEM;

	/* IPv6 can be CONFIG enabled and then disabled runसमय */
	अगर (!ipv6_mod_enabled())
		वापस 0;

	vrf->fib6_table = fib6_new_table(net, vrf->tb_id);
	अगर (!vrf->fib6_table)
		जाओ out;

	/* create a dst क्रम routing packets out a VRF device */
	rt6 = ip6_dst_alloc(net, dev, flags);
	अगर (!rt6)
		जाओ out;

	rt6->dst.output	= vrf_output6;

	rcu_assign_poपूर्णांकer(vrf->rt6, rt6);

	rc = 0;
out:
	वापस rc;
पूर्ण
#अन्यथा
अटल काष्ठा sk_buff *vrf_ip6_out(काष्ठा net_device *vrf_dev,
				   काष्ठा sock *sk,
				   काष्ठा sk_buff *skb)
अणु
	वापस skb;
पूर्ण

अटल व्योम vrf_rt6_release(काष्ठा net_device *dev, काष्ठा net_vrf *vrf)
अणु
पूर्ण

अटल पूर्णांक vrf_rt6_create(काष्ठा net_device *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* modelled after ip_finish_output2 */
अटल पूर्णांक vrf_finish_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा rtable *rt = (काष्ठा rtable *)dst;
	काष्ठा net_device *dev = dst->dev;
	अचिन्हित पूर्णांक hh_len = LL_RESERVED_SPACE(dev);
	काष्ठा neighbour *neigh;
	bool is_v6gw = false;
	पूर्णांक ret = -EINVAL;

	nf_reset_ct(skb);

	/* Be paranoid, rather than too clever. */
	अगर (unlikely(skb_headroom(skb) < hh_len && dev->header_ops)) अणु
		काष्ठा sk_buff *skb2;

		skb2 = skb_पुनः_स्मृति_headroom(skb, LL_RESERVED_SPACE(dev));
		अगर (!skb2) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
		अगर (skb->sk)
			skb_set_owner_w(skb2, skb->sk);

		consume_skb(skb);
		skb = skb2;
	पूर्ण

	rcu_पढ़ो_lock_bh();

	neigh = ip_neigh_क्रम_gw(rt, skb, &is_v6gw);
	अगर (!IS_ERR(neigh)) अणु
		sock_confirm_neigh(skb, neigh);
		/* अगर crossing protocols, can not use the cached header */
		ret = neigh_output(neigh, skb, is_v6gw);
		rcu_पढ़ो_unlock_bh();
		वापस ret;
	पूर्ण

	rcu_पढ़ो_unlock_bh();
err:
	vrf_tx_error(skb->dev, skb);
	वापस ret;
पूर्ण

अटल पूर्णांक vrf_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb_dst(skb)->dev;

	IP_UPD_PO_STATS(net, IPSTATS_MIB_OUT, skb->len);

	skb->dev = dev;
	skb->protocol = htons(ETH_P_IP);

	वापस NF_HOOK_COND(NFPROTO_IPV4, NF_INET_POST_ROUTING,
			    net, sk, skb, शून्य, dev,
			    vrf_finish_output,
			    !(IPCB(skb)->flags & IPSKB_REROUTED));
पूर्ण

/* set dst on skb to send packet to us via dev_xmit path. Allows
 * packet to go through device based features such as qdisc, netfilter
 * hooks and packet sockets with skb->dev set to vrf device.
 */
अटल काष्ठा sk_buff *vrf_ip_out_redirect(काष्ठा net_device *vrf_dev,
					   काष्ठा sk_buff *skb)
अणु
	काष्ठा net_vrf *vrf = netdev_priv(vrf_dev);
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा rtable *rth;

	rcu_पढ़ो_lock();

	rth = rcu_dereference(vrf->rth);
	अगर (likely(rth)) अणु
		dst = &rth->dst;
		dst_hold(dst);
	पूर्ण

	rcu_पढ़ो_unlock();

	अगर (unlikely(!dst)) अणु
		vrf_tx_error(vrf_dev, skb);
		वापस शून्य;
	पूर्ण

	skb_dst_drop(skb);
	skb_dst_set(skb, dst);

	वापस skb;
पूर्ण

अटल पूर्णांक vrf_output_direct_finish(काष्ठा net *net, काष्ठा sock *sk,
				    काष्ठा sk_buff *skb)
अणु
	vrf_finish_direct(skb);

	वापस vrf_ip_local_out(net, sk, skb);
पूर्ण

अटल पूर्णांक vrf_output_direct(काष्ठा net *net, काष्ठा sock *sk,
			     काष्ठा sk_buff *skb)
अणु
	पूर्णांक err = 1;

	skb->protocol = htons(ETH_P_IP);

	अगर (!(IPCB(skb)->flags & IPSKB_REROUTED))
		err = nf_hook(NFPROTO_IPV4, NF_INET_POST_ROUTING, net, sk, skb,
			      शून्य, skb->dev, vrf_output_direct_finish);

	अगर (likely(err == 1))
		vrf_finish_direct(skb);

	वापस err;
पूर्ण

अटल पूर्णांक vrf_ip_out_direct_finish(काष्ठा net *net, काष्ठा sock *sk,
				    काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	err = vrf_output_direct(net, sk, skb);
	अगर (likely(err == 1))
		err = vrf_ip_local_out(net, sk, skb);

	वापस err;
पूर्ण

अटल काष्ठा sk_buff *vrf_ip_out_direct(काष्ठा net_device *vrf_dev,
					 काष्ठा sock *sk,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा net *net = dev_net(vrf_dev);
	पूर्णांक err;

	skb->dev = vrf_dev;

	err = nf_hook(NFPROTO_IPV4, NF_INET_LOCAL_OUT, net, sk,
		      skb, शून्य, vrf_dev, vrf_ip_out_direct_finish);

	अगर (likely(err == 1))
		err = vrf_output_direct(net, sk, skb);

	अगर (likely(err == 1))
		वापस skb;

	वापस शून्य;
पूर्ण

अटल काष्ठा sk_buff *vrf_ip_out(काष्ठा net_device *vrf_dev,
				  काष्ठा sock *sk,
				  काष्ठा sk_buff *skb)
अणु
	/* करोn't भागert multicast or local broadcast */
	अगर (ipv4_is_multicast(ip_hdr(skb)->daddr) ||
	    ipv4_is_lbcast(ip_hdr(skb)->daddr))
		वापस skb;

	अगर (qdisc_tx_is_शेष(vrf_dev) ||
	    IPCB(skb)->flags & IPSKB_XFRM_TRANSFORMED)
		वापस vrf_ip_out_direct(vrf_dev, sk, skb);

	वापस vrf_ip_out_redirect(vrf_dev, skb);
पूर्ण

/* called with rcu lock held */
अटल काष्ठा sk_buff *vrf_l3_out(काष्ठा net_device *vrf_dev,
				  काष्ठा sock *sk,
				  काष्ठा sk_buff *skb,
				  u16 proto)
अणु
	चयन (proto) अणु
	हाल AF_INET:
		वापस vrf_ip_out(vrf_dev, sk, skb);
	हाल AF_INET6:
		वापस vrf_ip6_out(vrf_dev, sk, skb);
	पूर्ण

	वापस skb;
पूर्ण

/* holding rtnl */
अटल व्योम vrf_rtable_release(काष्ठा net_device *dev, काष्ठा net_vrf *vrf)
अणु
	काष्ठा rtable *rth = rtnl_dereference(vrf->rth);
	काष्ठा net *net = dev_net(dev);
	काष्ठा dst_entry *dst;

	RCU_INIT_POINTER(vrf->rth, शून्य);
	synchronize_rcu();

	/* move dev in dst's to loopback so this VRF device can be deleted
	 * - based on dst_अगरकरोwn
	 */
	अगर (rth) अणु
		dst = &rth->dst;
		dev_put(dst->dev);
		dst->dev = net->loopback_dev;
		dev_hold(dst->dev);
		dst_release(dst);
	पूर्ण
पूर्ण

अटल पूर्णांक vrf_rtable_create(काष्ठा net_device *dev)
अणु
	काष्ठा net_vrf *vrf = netdev_priv(dev);
	काष्ठा rtable *rth;

	अगर (!fib_new_table(dev_net(dev), vrf->tb_id))
		वापस -ENOMEM;

	/* create a dst क्रम routing packets out through a VRF device */
	rth = rt_dst_alloc(dev, 0, RTN_UNICAST, 1, 1);
	अगर (!rth)
		वापस -ENOMEM;

	rth->dst.output	= vrf_output;

	rcu_assign_poपूर्णांकer(vrf->rth, rth);

	वापस 0;
पूर्ण

/**************************** device handling ********************/

/* cycle पूर्णांकerface to flush neighbor cache and move routes across tables */
अटल व्योम cycle_netdev(काष्ठा net_device *dev,
			 काष्ठा netlink_ext_ack *extack)
अणु
	अचिन्हित पूर्णांक flags = dev->flags;
	पूर्णांक ret;

	अगर (!netअगर_running(dev))
		वापस;

	ret = dev_change_flags(dev, flags & ~IFF_UP, extack);
	अगर (ret >= 0)
		ret = dev_change_flags(dev, flags, extack);

	अगर (ret < 0) अणु
		netdev_err(dev,
			   "Failed to cycle device %s; route tables might be wrong!\n",
			   dev->name);
	पूर्ण
पूर्ण

अटल पूर्णांक करो_vrf_add_slave(काष्ठा net_device *dev, काष्ठा net_device *port_dev,
			    काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक ret;

	/* करो not allow loopback device to be enslaved to a VRF.
	 * The vrf device acts as the loopback क्रम the vrf.
	 */
	अगर (port_dev == dev_net(dev)->loopback_dev) अणु
		NL_SET_ERR_MSG(extack,
			       "Can not enslave loopback device to a VRF");
		वापस -EOPNOTSUPP;
	पूर्ण

	port_dev->priv_flags |= IFF_L3MDEV_SLAVE;
	ret = netdev_master_upper_dev_link(port_dev, dev, शून्य, शून्य, extack);
	अगर (ret < 0)
		जाओ err;

	cycle_netdev(port_dev, extack);

	वापस 0;

err:
	port_dev->priv_flags &= ~IFF_L3MDEV_SLAVE;
	वापस ret;
पूर्ण

अटल पूर्णांक vrf_add_slave(काष्ठा net_device *dev, काष्ठा net_device *port_dev,
			 काष्ठा netlink_ext_ack *extack)
अणु
	अगर (netअगर_is_l3_master(port_dev)) अणु
		NL_SET_ERR_MSG(extack,
			       "Can not enslave an L3 master device to a VRF");
		वापस -EINVAL;
	पूर्ण

	अगर (netअगर_is_l3_slave(port_dev))
		वापस -EINVAL;

	वापस करो_vrf_add_slave(dev, port_dev, extack);
पूर्ण

/* inverse of करो_vrf_add_slave */
अटल पूर्णांक करो_vrf_del_slave(काष्ठा net_device *dev, काष्ठा net_device *port_dev)
अणु
	netdev_upper_dev_unlink(port_dev, dev);
	port_dev->priv_flags &= ~IFF_L3MDEV_SLAVE;

	cycle_netdev(port_dev, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक vrf_del_slave(काष्ठा net_device *dev, काष्ठा net_device *port_dev)
अणु
	वापस करो_vrf_del_slave(dev, port_dev);
पूर्ण

अटल व्योम vrf_dev_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा net_vrf *vrf = netdev_priv(dev);

	vrf_rtable_release(dev, vrf);
	vrf_rt6_release(dev, vrf);

	मुक्त_percpu(dev->dstats);
	dev->dstats = शून्य;
पूर्ण

अटल पूर्णांक vrf_dev_init(काष्ठा net_device *dev)
अणु
	काष्ठा net_vrf *vrf = netdev_priv(dev);

	dev->dstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_dstats);
	अगर (!dev->dstats)
		जाओ out_nomem;

	/* create the शेष dst which poपूर्णांकs back to us */
	अगर (vrf_rtable_create(dev) != 0)
		जाओ out_stats;

	अगर (vrf_rt6_create(dev) != 0)
		जाओ out_rth;

	dev->flags = IFF_MASTER | IFF_NOARP;

	/* similarly, oper state is irrelevant; set to up to aव्योम confusion */
	dev->operstate = IF_OPER_UP;
	netdev_lockdep_set_classes(dev);
	वापस 0;

out_rth:
	vrf_rtable_release(dev, vrf);
out_stats:
	मुक्त_percpu(dev->dstats);
	dev->dstats = शून्य;
out_nomem:
	वापस -ENOMEM;
पूर्ण

अटल स्थिर काष्ठा net_device_ops vrf_netdev_ops = अणु
	.nकरो_init		= vrf_dev_init,
	.nकरो_uninit		= vrf_dev_uninit,
	.nकरो_start_xmit		= vrf_xmit,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_get_stats64	= vrf_get_stats64,
	.nकरो_add_slave		= vrf_add_slave,
	.nकरो_del_slave		= vrf_del_slave,
पूर्ण;

अटल u32 vrf_fib_table(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा net_vrf *vrf = netdev_priv(dev);

	वापस vrf->tb_id;
पूर्ण

अटल पूर्णांक vrf_rcv_finish(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *vrf_rcv_nfhook(u8 pf, अचिन्हित पूर्णांक hook,
				      काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev)
अणु
	काष्ठा net *net = dev_net(dev);

	अगर (nf_hook(pf, hook, net, शून्य, skb, dev, शून्य, vrf_rcv_finish) != 1)
		skb = शून्य;    /* kमुक्त_skb(skb) handled by nf code */

	वापस skb;
पूर्ण

अटल पूर्णांक vrf_prepare_mac_header(काष्ठा sk_buff *skb,
				  काष्ठा net_device *vrf_dev, u16 proto)
अणु
	काष्ठा ethhdr *eth;
	पूर्णांक err;

	/* in general, we करो not know अगर there is enough space in the head of
	 * the packet क्रम hosting the mac header.
	 */
	err = skb_cow_head(skb, LL_RESERVED_SPACE(vrf_dev));
	अगर (unlikely(err))
		/* no space in the skb head */
		वापस -ENOBUFS;

	__skb_push(skb, ETH_HLEN);
	eth = (काष्ठा ethhdr *)skb->data;

	skb_reset_mac_header(skb);

	/* we set the ethernet destination and the source addresses to the
	 * address of the VRF device.
	 */
	ether_addr_copy(eth->h_dest, vrf_dev->dev_addr);
	ether_addr_copy(eth->h_source, vrf_dev->dev_addr);
	eth->h_proto = htons(proto);

	/* the destination address of the Ethernet frame corresponds to the
	 * address set on the VRF पूर्णांकerface; thereक्रमe, the packet is पूर्णांकended
	 * to be processed locally.
	 */
	skb->protocol = eth->h_proto;
	skb->pkt_type = PACKET_HOST;

	skb_postpush_rcsum(skb, skb->data, ETH_HLEN);

	skb_pull_अंतरभूत(skb, ETH_HLEN);

	वापस 0;
पूर्ण

/* prepare and add the mac header to the packet अगर it was not set previously.
 * In this way, packet snअगरfers such as tcpdump can parse the packet correctly.
 * If the mac header was alपढ़ोy set, the original mac header is left
 * untouched and the function वापसs immediately.
 */
अटल पूर्णांक vrf_add_mac_header_अगर_unset(काष्ठा sk_buff *skb,
				       काष्ठा net_device *vrf_dev,
				       u16 proto)
अणु
	अगर (skb_mac_header_was_set(skb))
		वापस 0;

	वापस vrf_prepare_mac_header(skb, vrf_dev, proto);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
/* neighbor handling is करोne with actual device; करो not want
 * to flip skb->dev क्रम those ndisc packets. This really fails
 * क्रम multiple next protocols (e.g., NEXTHDR_HOP). But it is
 * a start.
 */
अटल bool ipv6_ndisc_frame(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	bool rc = false;

	अगर (iph->nexthdr == NEXTHDR_ICMP) अणु
		स्थिर काष्ठा icmp6hdr *icmph;
		काष्ठा icmp6hdr _icmph;

		icmph = skb_header_poपूर्णांकer(skb, माप(*iph),
					   माप(_icmph), &_icmph);
		अगर (!icmph)
			जाओ out;

		चयन (icmph->icmp6_type) अणु
		हाल NDISC_ROUTER_SOLICITATION:
		हाल NDISC_ROUTER_ADVERTISEMENT:
		हाल NDISC_NEIGHBOUR_SOLICITATION:
		हाल NDISC_NEIGHBOUR_ADVERTISEMENT:
		हाल NDISC_REसूचीECT:
			rc = true;
			अवरोध;
		पूर्ण
	पूर्ण

out:
	वापस rc;
पूर्ण

अटल काष्ठा rt6_info *vrf_ip6_route_lookup(काष्ठा net *net,
					     स्थिर काष्ठा net_device *dev,
					     काष्ठा flowi6 *fl6,
					     पूर्णांक अगरindex,
					     स्थिर काष्ठा sk_buff *skb,
					     पूर्णांक flags)
अणु
	काष्ठा net_vrf *vrf = netdev_priv(dev);

	वापस ip6_pol_route(net, vrf->fib6_table, अगरindex, fl6, skb, flags);
पूर्ण

अटल व्योम vrf_ip6_input_dst(काष्ठा sk_buff *skb, काष्ठा net_device *vrf_dev,
			      पूर्णांक अगरindex)
अणु
	स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	काष्ठा flowi6 fl6 = अणु
		.flowi6_iअगर     = अगरindex,
		.flowi6_mark    = skb->mark,
		.flowi6_proto   = iph->nexthdr,
		.daddr          = iph->daddr,
		.saddr          = iph->saddr,
		.flowlabel      = ip6_flowinfo(iph),
	पूर्ण;
	काष्ठा net *net = dev_net(vrf_dev);
	काष्ठा rt6_info *rt6;

	rt6 = vrf_ip6_route_lookup(net, vrf_dev, &fl6, अगरindex, skb,
				   RT6_LOOKUP_F_HAS_SADDR | RT6_LOOKUP_F_IFACE);
	अगर (unlikely(!rt6))
		वापस;

	अगर (unlikely(&rt6->dst == &net->ipv6.ip6_null_entry->dst))
		वापस;

	skb_dst_set(skb, &rt6->dst);
पूर्ण

अटल काष्ठा sk_buff *vrf_ip6_rcv(काष्ठा net_device *vrf_dev,
				   काष्ठा sk_buff *skb)
अणु
	पूर्णांक orig_iअगर = skb->skb_iअगर;
	bool need_strict = rt6_need_strict(&ipv6_hdr(skb)->daddr);
	bool is_ndisc = ipv6_ndisc_frame(skb);
	bool is_ll_src;

	/* loopback, multicast & non-ND link-local traffic; करो not push through
	 * packet taps again. Reset pkt_type क्रम upper layers to process skb.
	 * क्रम packets with lladdr src, however, skip so that the dst can be
	 * determine at input using original अगरindex in the हाल that daddr
	 * needs strict
	 */
	is_ll_src = ipv6_addr_type(&ipv6_hdr(skb)->saddr) & IPV6_ADDR_LINKLOCAL;
	अगर (skb->pkt_type == PACKET_LOOPBACK ||
	    (need_strict && !is_ndisc && !is_ll_src)) अणु
		skb->dev = vrf_dev;
		skb->skb_iअगर = vrf_dev->अगरindex;
		IP6CB(skb)->flags |= IP6SKB_L3SLAVE;
		अगर (skb->pkt_type == PACKET_LOOPBACK)
			skb->pkt_type = PACKET_HOST;
		जाओ out;
	पूर्ण

	/* अगर packet is NDISC then keep the ingress पूर्णांकerface */
	अगर (!is_ndisc) अणु
		vrf_rx_stats(vrf_dev, skb->len);
		skb->dev = vrf_dev;
		skb->skb_iअगर = vrf_dev->अगरindex;

		अगर (!list_empty(&vrf_dev->ptype_all)) अणु
			पूर्णांक err;

			err = vrf_add_mac_header_अगर_unset(skb, vrf_dev,
							  ETH_P_IPV6);
			अगर (likely(!err)) अणु
				skb_push(skb, skb->mac_len);
				dev_queue_xmit_nit(skb, vrf_dev);
				skb_pull(skb, skb->mac_len);
			पूर्ण
		पूर्ण

		IP6CB(skb)->flags |= IP6SKB_L3SLAVE;
	पूर्ण

	अगर (need_strict)
		vrf_ip6_input_dst(skb, vrf_dev, orig_iअगर);

	skb = vrf_rcv_nfhook(NFPROTO_IPV6, NF_INET_PRE_ROUTING, skb, vrf_dev);
out:
	वापस skb;
पूर्ण

#अन्यथा
अटल काष्ठा sk_buff *vrf_ip6_rcv(काष्ठा net_device *vrf_dev,
				   काष्ठा sk_buff *skb)
अणु
	वापस skb;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा sk_buff *vrf_ip_rcv(काष्ठा net_device *vrf_dev,
				  काष्ठा sk_buff *skb)
अणु
	skb->dev = vrf_dev;
	skb->skb_iअगर = vrf_dev->अगरindex;
	IPCB(skb)->flags |= IPSKB_L3SLAVE;

	अगर (ipv4_is_multicast(ip_hdr(skb)->daddr))
		जाओ out;

	/* loopback traffic; करो not push through packet taps again.
	 * Reset pkt_type क्रम upper layers to process skb
	 */
	अगर (skb->pkt_type == PACKET_LOOPBACK) अणु
		skb->pkt_type = PACKET_HOST;
		जाओ out;
	पूर्ण

	vrf_rx_stats(vrf_dev, skb->len);

	अगर (!list_empty(&vrf_dev->ptype_all)) अणु
		पूर्णांक err;

		err = vrf_add_mac_header_अगर_unset(skb, vrf_dev, ETH_P_IP);
		अगर (likely(!err)) अणु
			skb_push(skb, skb->mac_len);
			dev_queue_xmit_nit(skb, vrf_dev);
			skb_pull(skb, skb->mac_len);
		पूर्ण
	पूर्ण

	skb = vrf_rcv_nfhook(NFPROTO_IPV4, NF_INET_PRE_ROUTING, skb, vrf_dev);
out:
	वापस skb;
पूर्ण

/* called with rcu lock held */
अटल काष्ठा sk_buff *vrf_l3_rcv(काष्ठा net_device *vrf_dev,
				  काष्ठा sk_buff *skb,
				  u16 proto)
अणु
	चयन (proto) अणु
	हाल AF_INET:
		वापस vrf_ip_rcv(vrf_dev, skb);
	हाल AF_INET6:
		वापस vrf_ip6_rcv(vrf_dev, skb);
	पूर्ण

	वापस skb;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
/* send to link-local or multicast address via पूर्णांकerface enslaved to
 * VRF device. Force lookup to VRF table without changing flow काष्ठा
 * Note: Caller to this function must hold rcu_पढ़ो_lock() and no refcnt
 * is taken on the dst by this function.
 */
अटल काष्ठा dst_entry *vrf_link_scope_lookup(स्थिर काष्ठा net_device *dev,
					      काष्ठा flowi6 *fl6)
अणु
	काष्ठा net *net = dev_net(dev);
	पूर्णांक flags = RT6_LOOKUP_F_IFACE | RT6_LOOKUP_F_DST_NOREF;
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा rt6_info *rt;

	/* VRF device करोes not have a link-local address and
	 * sending packets to link-local or mcast addresses over
	 * a VRF device करोes not make sense
	 */
	अगर (fl6->flowi6_oअगर == dev->अगरindex) अणु
		dst = &net->ipv6.ip6_null_entry->dst;
		वापस dst;
	पूर्ण

	अगर (!ipv6_addr_any(&fl6->saddr))
		flags |= RT6_LOOKUP_F_HAS_SADDR;

	rt = vrf_ip6_route_lookup(net, dev, fl6, fl6->flowi6_oअगर, शून्य, flags);
	अगर (rt)
		dst = &rt->dst;

	वापस dst;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा l3mdev_ops vrf_l3mdev_ops = अणु
	.l3mdev_fib_table	= vrf_fib_table,
	.l3mdev_l3_rcv		= vrf_l3_rcv,
	.l3mdev_l3_out		= vrf_l3_out,
#अगर IS_ENABLED(CONFIG_IPV6)
	.l3mdev_link_scope_lookup = vrf_link_scope_lookup,
#पूर्ण_अगर
पूर्ण;

अटल व्योम vrf_get_drvinfo(काष्ठा net_device *dev,
			    काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops vrf_ethtool_ops = अणु
	.get_drvinfo	= vrf_get_drvinfo,
पूर्ण;

अटल अंतरभूत माप_प्रकार vrf_fib_rule_nl_size(व्योम)
अणु
	माप_प्रकार sz;

	sz  = NLMSG_ALIGN(माप(काष्ठा fib_rule_hdr));
	sz += nla_total_size(माप(u8));	/* FRA_L3MDEV */
	sz += nla_total_size(माप(u32));	/* FRA_PRIORITY */
	sz += nla_total_size(माप(u8));       /* FRA_PROTOCOL */

	वापस sz;
पूर्ण

अटल पूर्णांक vrf_fib_rule(स्थिर काष्ठा net_device *dev, __u8 family, bool add_it)
अणु
	काष्ठा fib_rule_hdr *frh;
	काष्ठा nlmsghdr *nlh;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	अगर ((family == AF_INET6 || family == RTNL_FAMILY_IP6MR) &&
	    !ipv6_mod_enabled())
		वापस 0;

	skb = nlmsg_new(vrf_fib_rule_nl_size(), GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	nlh = nlmsg_put(skb, 0, 0, 0, माप(*frh), 0);
	अगर (!nlh)
		जाओ nla_put_failure;

	/* rule only needs to appear once */
	nlh->nlmsg_flags |= NLM_F_EXCL;

	frh = nlmsg_data(nlh);
	स_रखो(frh, 0, माप(*frh));
	frh->family = family;
	frh->action = FR_ACT_TO_TBL;

	अगर (nla_put_u8(skb, FRA_PROTOCOL, RTPROT_KERNEL))
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, FRA_L3MDEV, 1))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, FRA_PRIORITY, FIB_RULE_PREF))
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);

	/* fib_nl_अणुnew,delपूर्णrule handling looks क्रम net from skb->sk */
	skb->sk = dev_net(dev)->rtnl;
	अगर (add_it) अणु
		err = fib_nl_newrule(skb, nlh, शून्य);
		अगर (err == -EEXIST)
			err = 0;
	पूर्ण अन्यथा अणु
		err = fib_nl_delrule(skb, nlh, शून्य);
		अगर (err == -ENOENT)
			err = 0;
	पूर्ण
	nlmsg_मुक्त(skb);

	वापस err;

nla_put_failure:
	nlmsg_मुक्त(skb);

	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक vrf_add_fib_rules(स्थिर काष्ठा net_device *dev)
अणु
	पूर्णांक err;

	err = vrf_fib_rule(dev, AF_INET,  true);
	अगर (err < 0)
		जाओ out_err;

	err = vrf_fib_rule(dev, AF_INET6, true);
	अगर (err < 0)
		जाओ ipv6_err;

#अगर IS_ENABLED(CONFIG_IP_MROUTE_MULTIPLE_TABLES)
	err = vrf_fib_rule(dev, RTNL_FAMILY_IPMR, true);
	अगर (err < 0)
		जाओ ipmr_err;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IPV6_MROUTE_MULTIPLE_TABLES)
	err = vrf_fib_rule(dev, RTNL_FAMILY_IP6MR, true);
	अगर (err < 0)
		जाओ ip6mr_err;
#पूर्ण_अगर

	वापस 0;

#अगर IS_ENABLED(CONFIG_IPV6_MROUTE_MULTIPLE_TABLES)
ip6mr_err:
	vrf_fib_rule(dev, RTNL_FAMILY_IPMR,  false);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IP_MROUTE_MULTIPLE_TABLES)
ipmr_err:
	vrf_fib_rule(dev, AF_INET6,  false);
#पूर्ण_अगर

ipv6_err:
	vrf_fib_rule(dev, AF_INET,  false);

out_err:
	netdev_err(dev, "Failed to add FIB rules.\n");
	वापस err;
पूर्ण

अटल व्योम vrf_setup(काष्ठा net_device *dev)
अणु
	ether_setup(dev);

	/* Initialize the device काष्ठाure. */
	dev->netdev_ops = &vrf_netdev_ops;
	dev->l3mdev_ops = &vrf_l3mdev_ops;
	dev->ethtool_ops = &vrf_ethtool_ops;
	dev->needs_मुक्त_netdev = true;

	/* Fill in device काष्ठाure with ethernet-generic values. */
	eth_hw_addr_अक्रमom(dev);

	/* करोn't acquire vrf device's netअगर_tx_lock when transmitting */
	dev->features |= NETIF_F_LLTX;

	/* करोn't allow vrf devices to change network namespaces. */
	dev->features |= NETIF_F_NETNS_LOCAL;

	/* करोes not make sense क्रम a VLAN to be added to a vrf device */
	dev->features   |= NETIF_F_VLAN_CHALLENGED;

	/* enable offload features */
	dev->features   |= NETIF_F_GSO_SOFTWARE;
	dev->features   |= NETIF_F_RXCSUM | NETIF_F_HW_CSUM | NETIF_F_SCTP_CRC;
	dev->features   |= NETIF_F_SG | NETIF_F_FRAGLIST | NETIF_F_HIGHDMA;

	dev->hw_features = dev->features;
	dev->hw_enc_features = dev->features;

	/* शेष to no qdisc; user can add अगर desired */
	dev->priv_flags |= IFF_NO_QUEUE;
	dev->priv_flags |= IFF_NO_RX_HANDLER;
	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE;

	/* VRF devices करो not care about MTU, but अगर the MTU is set
	 * too low then the ipv4 and ipv6 protocols are disabled
	 * which अवरोधs networking.
	 */
	dev->min_mtu = IPV6_MIN_MTU;
	dev->max_mtu = IP6_MAX_MTU;
	dev->mtu = dev->max_mtu;
पूर्ण

अटल पूर्णांक vrf_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			काष्ठा netlink_ext_ack *extack)
अणु
	अगर (tb[IFLA_ADDRESS]) अणु
		अगर (nla_len(tb[IFLA_ADDRESS]) != ETH_ALEN) अणु
			NL_SET_ERR_MSG(extack, "Invalid hardware address");
			वापस -EINVAL;
		पूर्ण
		अगर (!is_valid_ether_addr(nla_data(tb[IFLA_ADDRESS]))) अणु
			NL_SET_ERR_MSG(extack, "Invalid hardware address");
			वापस -EADDRNOTAVAIL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम vrf_dellink(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा net_device *port_dev;
	काष्ठा list_head *iter;

	netdev_क्रम_each_lower_dev(dev, port_dev, iter)
		vrf_del_slave(dev, port_dev);

	vrf_map_unरेजिस्टर_dev(dev);

	unरेजिस्टर_netdevice_queue(dev, head);
पूर्ण

अटल पूर्णांक vrf_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
		       काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_vrf *vrf = netdev_priv(dev);
	काष्ठा netns_vrf *nn_vrf;
	bool *add_fib_rules;
	काष्ठा net *net;
	पूर्णांक err;

	अगर (!data || !data[IFLA_VRF_TABLE]) अणु
		NL_SET_ERR_MSG(extack, "VRF table id is missing");
		वापस -EINVAL;
	पूर्ण

	vrf->tb_id = nla_get_u32(data[IFLA_VRF_TABLE]);
	अगर (vrf->tb_id == RT_TABLE_UNSPEC) अणु
		NL_SET_ERR_MSG_ATTR(extack, data[IFLA_VRF_TABLE],
				    "Invalid VRF table id");
		वापस -EINVAL;
	पूर्ण

	dev->priv_flags |= IFF_L3MDEV_MASTER;

	err = रेजिस्टर_netdevice(dev);
	अगर (err)
		जाओ out;

	/* mapping between table_id and vrf;
	 * note: such binding could not be करोne in the dev init function
	 * because dev->अगरindex id is not available yet.
	 */
	vrf->अगरindex = dev->अगरindex;

	err = vrf_map_रेजिस्टर_dev(dev, extack);
	अगर (err) अणु
		unरेजिस्टर_netdevice(dev);
		जाओ out;
	पूर्ण

	net = dev_net(dev);
	nn_vrf = net_generic(net, vrf_net_id);

	add_fib_rules = &nn_vrf->add_fib_rules;
	अगर (*add_fib_rules) अणु
		err = vrf_add_fib_rules(dev);
		अगर (err) अणु
			vrf_map_unरेजिस्टर_dev(dev);
			unरेजिस्टर_netdevice(dev);
			जाओ out;
		पूर्ण
		*add_fib_rules = false;
	पूर्ण

out:
	वापस err;
पूर्ण

अटल माप_प्रकार vrf_nl_माला_लोize(स्थिर काष्ठा net_device *dev)
अणु
	वापस nla_total_size(माप(u32));  /* IFLA_VRF_TABLE */
पूर्ण

अटल पूर्णांक vrf_fillinfo(काष्ठा sk_buff *skb,
			स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा net_vrf *vrf = netdev_priv(dev);

	वापस nla_put_u32(skb, IFLA_VRF_TABLE, vrf->tb_id);
पूर्ण

अटल माप_प्रकार vrf_get_slave_size(स्थिर काष्ठा net_device *bond_dev,
				 स्थिर काष्ठा net_device *slave_dev)
अणु
	वापस nla_total_size(माप(u32));  /* IFLA_VRF_PORT_TABLE */
पूर्ण

अटल पूर्णांक vrf_fill_slave_info(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा net_device *vrf_dev,
			       स्थिर काष्ठा net_device *slave_dev)
अणु
	काष्ठा net_vrf *vrf = netdev_priv(vrf_dev);

	अगर (nla_put_u32(skb, IFLA_VRF_PORT_TABLE, vrf->tb_id))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy vrf_nl_policy[IFLA_VRF_MAX + 1] = अणु
	[IFLA_VRF_TABLE] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल काष्ठा rtnl_link_ops vrf_link_ops __पढ़ो_mostly = अणु
	.kind		= DRV_NAME,
	.priv_size	= माप(काष्ठा net_vrf),

	.get_size	= vrf_nl_माला_लोize,
	.policy		= vrf_nl_policy,
	.validate	= vrf_validate,
	.fill_info	= vrf_fillinfo,

	.get_slave_size  = vrf_get_slave_size,
	.fill_slave_info = vrf_fill_slave_info,

	.newlink	= vrf_newlink,
	.dellink	= vrf_dellink,
	.setup		= vrf_setup,
	.maxtype	= IFLA_VRF_MAX,
पूर्ण;

अटल पूर्णांक vrf_device_event(काष्ठा notअगरier_block *unused,
			    अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	/* only care about unरेजिस्टर events to drop slave references */
	अगर (event == NETDEV_UNREGISTER) अणु
		काष्ठा net_device *vrf_dev;

		अगर (!netअगर_is_l3_slave(dev))
			जाओ out;

		vrf_dev = netdev_master_upper_dev_get(dev);
		vrf_del_slave(vrf_dev, dev);
	पूर्ण
out:
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block vrf_notअगरier_block __पढ़ो_mostly = अणु
	.notअगरier_call = vrf_device_event,
पूर्ण;

अटल पूर्णांक vrf_map_init(काष्ठा vrf_map *vmap)
अणु
	spin_lock_init(&vmap->vmap_lock);
	hash_init(vmap->ht);

	vmap->strict_mode = false;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SYSCTL
अटल bool vrf_strict_mode(काष्ठा vrf_map *vmap)
अणु
	bool strict_mode;

	vrf_map_lock(vmap);
	strict_mode = vmap->strict_mode;
	vrf_map_unlock(vmap);

	वापस strict_mode;
पूर्ण

अटल पूर्णांक vrf_strict_mode_change(काष्ठा vrf_map *vmap, bool new_mode)
अणु
	bool *cur_mode;
	पूर्णांक res = 0;

	vrf_map_lock(vmap);

	cur_mode = &vmap->strict_mode;
	अगर (*cur_mode == new_mode)
		जाओ unlock;

	अगर (*cur_mode) अणु
		/* disable strict mode */
		*cur_mode = false;
	पूर्ण अन्यथा अणु
		अगर (vmap->shared_tables) अणु
			/* we cannot allow strict_mode because there are some
			 * vrfs that share one or more tables.
			 */
			res = -EBUSY;
			जाओ unlock;
		पूर्ण

		/* no tables are shared among vrfs, so we can go back
		 * to 1:1 association between a vrf with its table.
		 */
		*cur_mode = true;
	पूर्ण

unlock:
	vrf_map_unlock(vmap);

	वापस res;
पूर्ण

अटल पूर्णांक vrf_shared_table_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				    व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा net *net = (काष्ठा net *)table->extra1;
	काष्ठा vrf_map *vmap = netns_vrf_map(net);
	पूर्णांक proc_strict_mode = 0;
	काष्ठा ctl_table पंचांगp = अणु
		.procname	= table->procname,
		.data		= &proc_strict_mode,
		.maxlen		= माप(पूर्णांक),
		.mode		= table->mode,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण;
	पूर्णांक ret;

	अगर (!ग_लिखो)
		proc_strict_mode = vrf_strict_mode(vmap);

	ret = proc_करोपूर्णांकvec_minmax(&पंचांगp, ग_लिखो, buffer, lenp, ppos);

	अगर (ग_लिखो && ret == 0)
		ret = vrf_strict_mode_change(vmap, (bool)proc_strict_mode);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ctl_table vrf_table[] = अणु
	अणु
		.procname	= "strict_mode",
		.data		= शून्य,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= vrf_shared_table_handler,
		/* set by the vrf_netns_init */
		.extra1		= शून्य,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक vrf_netns_init_sysctl(काष्ठा net *net, काष्ठा netns_vrf *nn_vrf)
अणु
	काष्ठा ctl_table *table;

	table = kmemdup(vrf_table, माप(vrf_table), GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	/* init the extra1 parameter with the reference to current netns */
	table[0].extra1 = net;

	nn_vrf->ctl_hdr = रेजिस्टर_net_sysctl(net, "net/vrf", table);
	अगर (!nn_vrf->ctl_hdr) अणु
		kमुक्त(table);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vrf_netns_निकास_sysctl(काष्ठा net *net)
अणु
	काष्ठा netns_vrf *nn_vrf = net_generic(net, vrf_net_id);
	काष्ठा ctl_table *table;

	table = nn_vrf->ctl_hdr->ctl_table_arg;
	unरेजिस्टर_net_sysctl_table(nn_vrf->ctl_hdr);
	kमुक्त(table);
पूर्ण
#अन्यथा
अटल पूर्णांक vrf_netns_init_sysctl(काष्ठा net *net, काष्ठा netns_vrf *nn_vrf)
अणु
	वापस 0;
पूर्ण

अटल व्योम vrf_netns_निकास_sysctl(काष्ठा net *net)
अणु
पूर्ण
#पूर्ण_अगर

/* Initialize per network namespace state */
अटल पूर्णांक __net_init vrf_netns_init(काष्ठा net *net)
अणु
	काष्ठा netns_vrf *nn_vrf = net_generic(net, vrf_net_id);

	nn_vrf->add_fib_rules = true;
	vrf_map_init(&nn_vrf->vmap);

	वापस vrf_netns_init_sysctl(net, nn_vrf);
पूर्ण

अटल व्योम __net_निकास vrf_netns_निकास(काष्ठा net *net)
अणु
	vrf_netns_निकास_sysctl(net);
पूर्ण

अटल काष्ठा pernet_operations vrf_net_ops __net_initdata = अणु
	.init = vrf_netns_init,
	.निकास = vrf_netns_निकास,
	.id   = &vrf_net_id,
	.size = माप(काष्ठा netns_vrf),
पूर्ण;

अटल पूर्णांक __init vrf_init_module(व्योम)
अणु
	पूर्णांक rc;

	रेजिस्टर_netdevice_notअगरier(&vrf_notअगरier_block);

	rc = रेजिस्टर_pernet_subsys(&vrf_net_ops);
	अगर (rc < 0)
		जाओ error;

	rc = l3mdev_table_lookup_रेजिस्टर(L3MDEV_TYPE_VRF,
					  vrf_अगरindex_lookup_by_table_id);
	अगर (rc < 0)
		जाओ unreg_pernet;

	rc = rtnl_link_रेजिस्टर(&vrf_link_ops);
	अगर (rc < 0)
		जाओ table_lookup_unreg;

	वापस 0;

table_lookup_unreg:
	l3mdev_table_lookup_unरेजिस्टर(L3MDEV_TYPE_VRF,
				       vrf_अगरindex_lookup_by_table_id);

unreg_pernet:
	unरेजिस्टर_pernet_subsys(&vrf_net_ops);

error:
	unरेजिस्टर_netdevice_notअगरier(&vrf_notअगरier_block);
	वापस rc;
पूर्ण

module_init(vrf_init_module);
MODULE_AUTHOR("Shrijeet Mukherjee, David Ahern");
MODULE_DESCRIPTION("Device driver to instantiate VRF domains");
MODULE_LICENSE("GPL");
MODULE_ALIAS_RTNL_LINK(DRV_NAME);
MODULE_VERSION(DRV_VERSION);
