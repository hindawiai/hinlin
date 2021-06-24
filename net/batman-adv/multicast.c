<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Linus Lथञssing
 */

#समावेश "multicast.h"
#समावेश "main.h"

#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/gfp.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/igmp.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netlink.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश <net/addrconf.h>
#समावेश <net/genetlink.h>
#समावेश <net/अगर_inet6.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/netlink.h>
#समावेश <net/sock.h>
#समावेश <uapi/linux/batadv_packet.h>
#समावेश <uapi/linux/baपंचांगan_adv.h>

#समावेश "bridge_loop_avoidance.h"
#समावेश "hard-interface.h"
#समावेश "hash.h"
#समावेश "log.h"
#समावेश "netlink.h"
#समावेश "send.h"
#समावेश "soft-interface.h"
#समावेश "translation-table.h"
#समावेश "tvlv.h"

अटल व्योम batadv_mcast_mla_update(काष्ठा work_काष्ठा *work);

/**
 * batadv_mcast_start_समयr() - schedule the multicast periodic worker
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
अटल व्योम batadv_mcast_start_समयr(काष्ठा batadv_priv *bat_priv)
अणु
	queue_delayed_work(batadv_event_workqueue, &bat_priv->mcast.work,
			   msecs_to_jअगरfies(BATADV_MCAST_WORK_PERIOD));
पूर्ण

/**
 * batadv_mcast_get_bridge() - get the bridge on top of the softअगर अगर it exists
 * @soft_अगरace: netdev काष्ठा of the mesh पूर्णांकerface
 *
 * If the given soft पूर्णांकerface has a bridge on top then the refcount
 * of the according net device is increased.
 *
 * Return: शून्य अगर no such bridge exists. Otherwise the net device of the
 * bridge.
 */
अटल काष्ठा net_device *batadv_mcast_get_bridge(काष्ठा net_device *soft_अगरace)
अणु
	काष्ठा net_device *upper = soft_अगरace;

	rcu_पढ़ो_lock();
	करो अणु
		upper = netdev_master_upper_dev_get_rcu(upper);
	पूर्ण जबतक (upper && !(upper->priv_flags & IFF_EBRIDGE));

	अगर (upper)
		dev_hold(upper);
	rcu_पढ़ो_unlock();

	वापस upper;
पूर्ण

/**
 * batadv_mcast_mla_rtr_flags_softअगर_get_ipv4() - get mcast router flags from
 *  node क्रम IPv4
 * @dev: the पूर्णांकerface to check
 *
 * Checks the presence of an IPv4 multicast router on this node.
 *
 * Caller needs to hold rcu पढ़ो lock.
 *
 * Return: BATADV_NO_FLAGS अगर present, BATADV_MCAST_WANT_NO_RTR4 otherwise.
 */
अटल u8 batadv_mcast_mla_rtr_flags_softअगर_get_ipv4(काष्ठा net_device *dev)
अणु
	काष्ठा in_device *in_dev = __in_dev_get_rcu(dev);

	अगर (in_dev && IN_DEV_MFORWARD(in_dev))
		वापस BATADV_NO_FLAGS;
	अन्यथा
		वापस BATADV_MCAST_WANT_NO_RTR4;
पूर्ण

/**
 * batadv_mcast_mla_rtr_flags_softअगर_get_ipv6() - get mcast router flags from
 *  node क्रम IPv6
 * @dev: the पूर्णांकerface to check
 *
 * Checks the presence of an IPv6 multicast router on this node.
 *
 * Caller needs to hold rcu पढ़ो lock.
 *
 * Return: BATADV_NO_FLAGS अगर present, BATADV_MCAST_WANT_NO_RTR6 otherwise.
 */
#अगर IS_ENABLED(CONFIG_IPV6_MROUTE)
अटल u8 batadv_mcast_mla_rtr_flags_softअगर_get_ipv6(काष्ठा net_device *dev)
अणु
	काष्ठा inet6_dev *in6_dev = __in6_dev_get(dev);

	अगर (in6_dev && in6_dev->cnf.mc_क्रमwarding)
		वापस BATADV_NO_FLAGS;
	अन्यथा
		वापस BATADV_MCAST_WANT_NO_RTR6;
पूर्ण
#अन्यथा
अटल अंतरभूत u8
batadv_mcast_mla_rtr_flags_softअगर_get_ipv6(काष्ठा net_device *dev)
अणु
	वापस BATADV_MCAST_WANT_NO_RTR6;
पूर्ण
#पूर्ण_अगर

/**
 * batadv_mcast_mla_rtr_flags_softअगर_get() - get mcast router flags from node
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @bridge: bridge पूर्णांकerface on top of the soft_अगरace अगर present,
 *  otherwise pass शून्य
 *
 * Checks the presence of IPv4 and IPv6 multicast routers on this
 * node.
 *
 * Return:
 *	BATADV_NO_FLAGS: Both an IPv4 and IPv6 multicast router is present
 *	BATADV_MCAST_WANT_NO_RTR4: No IPv4 multicast router is present
 *	BATADV_MCAST_WANT_NO_RTR6: No IPv6 multicast router is present
 *	The क्रमmer two OR'd: no multicast router is present
 */
अटल u8 batadv_mcast_mla_rtr_flags_softअगर_get(काष्ठा batadv_priv *bat_priv,
						काष्ठा net_device *bridge)
अणु
	काष्ठा net_device *dev = bridge ? bridge : bat_priv->soft_अगरace;
	u8 flags = BATADV_NO_FLAGS;

	rcu_पढ़ो_lock();

	flags |= batadv_mcast_mla_rtr_flags_softअगर_get_ipv4(dev);
	flags |= batadv_mcast_mla_rtr_flags_softअगर_get_ipv6(dev);

	rcu_पढ़ो_unlock();

	वापस flags;
पूर्ण

/**
 * batadv_mcast_mla_rtr_flags_bridge_get() - get mcast router flags from bridge
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @bridge: bridge पूर्णांकerface on top of the soft_अगरace अगर present,
 *  otherwise pass शून्य
 *
 * Checks the presence of IPv4 and IPv6 multicast routers behind a bridge.
 *
 * Return:
 *	BATADV_NO_FLAGS: Both an IPv4 and IPv6 multicast router is present
 *	BATADV_MCAST_WANT_NO_RTR4: No IPv4 multicast router is present
 *	BATADV_MCAST_WANT_NO_RTR6: No IPv6 multicast router is present
 *	The क्रमmer two OR'd: no multicast router is present
 */
#अगर IS_ENABLED(CONFIG_IPV6)
अटल u8 batadv_mcast_mla_rtr_flags_bridge_get(काष्ठा batadv_priv *bat_priv,
						काष्ठा net_device *bridge)
अणु
	काष्ठा list_head bridge_mcast_list = LIST_HEAD_INIT(bridge_mcast_list);
	काष्ठा net_device *dev = bat_priv->soft_अगरace;
	काष्ठा br_ip_list *br_ip_entry, *पंचांगp;
	u8 flags = BATADV_MCAST_WANT_NO_RTR6;
	पूर्णांक ret;

	अगर (!bridge)
		वापस BATADV_MCAST_WANT_NO_RTR4 | BATADV_MCAST_WANT_NO_RTR6;

	/* TODO: ask the bridge अगर a multicast router is present (the bridge
	 * is capable of perक्रमming proper RFC4286 multicast router
	 * discovery) instead of searching क्रम a ff02::2 listener here
	 */
	ret = br_multicast_list_adjacent(dev, &bridge_mcast_list);
	अगर (ret < 0)
		वापस BATADV_NO_FLAGS;

	list_क्रम_each_entry_safe(br_ip_entry, पंचांगp, &bridge_mcast_list, list) अणु
		/* the bridge snooping करोes not मुख्यtain IPv4 link-local
		 * addresses - thereक्रमe we won't find any IPv4 multicast router
		 * address here, only IPv6 ones
		 */
		अगर (br_ip_entry->addr.proto == htons(ETH_P_IPV6) &&
		    ipv6_addr_is_ll_all_routers(&br_ip_entry->addr.dst.ip6))
			flags &= ~BATADV_MCAST_WANT_NO_RTR6;

		list_del(&br_ip_entry->list);
		kमुक्त(br_ip_entry);
	पूर्ण

	वापस flags;
पूर्ण
#अन्यथा
अटल अंतरभूत u8
batadv_mcast_mla_rtr_flags_bridge_get(काष्ठा batadv_priv *bat_priv,
				      काष्ठा net_device *bridge)
अणु
	अगर (bridge)
		वापस BATADV_NO_FLAGS;
	अन्यथा
		वापस BATADV_MCAST_WANT_NO_RTR4 | BATADV_MCAST_WANT_NO_RTR6;
पूर्ण
#पूर्ण_अगर

/**
 * batadv_mcast_mla_rtr_flags_get() - get multicast router flags
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @bridge: bridge पूर्णांकerface on top of the soft_अगरace अगर present,
 *  otherwise pass शून्य
 *
 * Checks the presence of IPv4 and IPv6 multicast routers on this
 * node or behind its bridge.
 *
 * Return:
 *	BATADV_NO_FLAGS: Both an IPv4 and IPv6 multicast router is present
 *	BATADV_MCAST_WANT_NO_RTR4: No IPv4 multicast router is present
 *	BATADV_MCAST_WANT_NO_RTR6: No IPv6 multicast router is present
 *	The क्रमmer two OR'd: no multicast router is present
 */
अटल u8 batadv_mcast_mla_rtr_flags_get(काष्ठा batadv_priv *bat_priv,
					 काष्ठा net_device *bridge)
अणु
	u8 flags = BATADV_MCAST_WANT_NO_RTR4 | BATADV_MCAST_WANT_NO_RTR6;

	flags &= batadv_mcast_mla_rtr_flags_softअगर_get(bat_priv, bridge);
	flags &= batadv_mcast_mla_rtr_flags_bridge_get(bat_priv, bridge);

	वापस flags;
पूर्ण

/**
 * batadv_mcast_mla_flags_get() - get the new multicast flags
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: A set of flags क्रम the current/next TVLV, querier and
 * bridge state.
 */
अटल काष्ठा batadv_mcast_mla_flags
batadv_mcast_mla_flags_get(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा net_device *dev = bat_priv->soft_अगरace;
	काष्ठा batadv_mcast_querier_state *qr4, *qr6;
	काष्ठा batadv_mcast_mla_flags mla_flags;
	काष्ठा net_device *bridge;

	bridge = batadv_mcast_get_bridge(dev);

	स_रखो(&mla_flags, 0, माप(mla_flags));
	mla_flags.enabled = 1;
	mla_flags.tvlv_flags |= batadv_mcast_mla_rtr_flags_get(bat_priv,
							       bridge);

	अगर (!bridge)
		वापस mla_flags;

	dev_put(bridge);

	mla_flags.bridged = 1;
	qr4 = &mla_flags.querier_ipv4;
	qr6 = &mla_flags.querier_ipv6;

	अगर (!IS_ENABLED(CONFIG_BRIDGE_IGMP_SNOOPING))
		pr_warn_once("No bridge IGMP snooping compiled - multicast optimizations disabled\n");

	qr4->exists = br_multicast_has_querier_anywhere(dev, ETH_P_IP);
	qr4->shaकरोwing = br_multicast_has_querier_adjacent(dev, ETH_P_IP);

	qr6->exists = br_multicast_has_querier_anywhere(dev, ETH_P_IPV6);
	qr6->shaकरोwing = br_multicast_has_querier_adjacent(dev, ETH_P_IPV6);

	mla_flags.tvlv_flags |= BATADV_MCAST_WANT_ALL_UNSNOOPABLES;

	/* 1) If no querier exists at all, then multicast listeners on
	 *    our local TT clients behind the bridge will keep silent.
	 * 2) If the selected querier is on one of our local TT clients,
	 *    behind the bridge, then this querier might shaकरोw multicast
	 *    listeners on our local TT clients, behind this bridge.
	 *
	 * In both हालs, we will संकेतize other baपंचांगan nodes that
	 * we need all multicast traffic of the according protocol.
	 */
	अगर (!qr4->exists || qr4->shaकरोwing) अणु
		mla_flags.tvlv_flags |= BATADV_MCAST_WANT_ALL_IPV4;
		mla_flags.tvlv_flags &= ~BATADV_MCAST_WANT_NO_RTR4;
	पूर्ण

	अगर (!qr6->exists || qr6->shaकरोwing) अणु
		mla_flags.tvlv_flags |= BATADV_MCAST_WANT_ALL_IPV6;
		mla_flags.tvlv_flags &= ~BATADV_MCAST_WANT_NO_RTR6;
	पूर्ण

	वापस mla_flags;
पूर्ण

/**
 * batadv_mcast_mla_is_duplicate() - check whether an address is in a list
 * @mcast_addr: the multicast address to check
 * @mcast_list: the list with multicast addresses to search in
 *
 * Return: true अगर the given address is alपढ़ोy in the given list.
 * Otherwise वापसs false.
 */
अटल bool batadv_mcast_mla_is_duplicate(u8 *mcast_addr,
					  काष्ठा hlist_head *mcast_list)
अणु
	काष्ठा batadv_hw_addr *mcast_entry;

	hlist_क्रम_each_entry(mcast_entry, mcast_list, list)
		अगर (batadv_compare_eth(mcast_entry->addr, mcast_addr))
			वापस true;

	वापस false;
पूर्ण

/**
 * batadv_mcast_mla_softअगर_get_ipv4() - get softअगर IPv4 multicast listeners
 * @dev: the device to collect multicast addresses from
 * @mcast_list: a list to put found addresses पूर्णांकo
 * @flags: flags indicating the new multicast state
 *
 * Collects multicast addresses of IPv4 multicast listeners residing
 * on this kernel on the given soft पूर्णांकerface, dev, in
 * the given mcast_list. In general, multicast listeners provided by
 * your multicast receiving applications run directly on this node.
 *
 * Return: -ENOMEM on memory allocation error or the number of
 * items added to the mcast_list otherwise.
 */
अटल पूर्णांक
batadv_mcast_mla_softअगर_get_ipv4(काष्ठा net_device *dev,
				 काष्ठा hlist_head *mcast_list,
				 काष्ठा batadv_mcast_mla_flags *flags)
अणु
	काष्ठा batadv_hw_addr *new;
	काष्ठा in_device *in_dev;
	u8 mcast_addr[ETH_ALEN];
	काष्ठा ip_mc_list *pmc;
	पूर्णांक ret = 0;

	अगर (flags->tvlv_flags & BATADV_MCAST_WANT_ALL_IPV4)
		वापस 0;

	rcu_पढ़ो_lock();

	in_dev = __in_dev_get_rcu(dev);
	अगर (!in_dev) अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण

	क्रम (pmc = rcu_dereference(in_dev->mc_list); pmc;
	     pmc = rcu_dereference(pmc->next_rcu)) अणु
		अगर (flags->tvlv_flags & BATADV_MCAST_WANT_ALL_UNSNOOPABLES &&
		    ipv4_is_local_multicast(pmc->multiaddr))
			जारी;

		अगर (!(flags->tvlv_flags & BATADV_MCAST_WANT_NO_RTR4) &&
		    !ipv4_is_local_multicast(pmc->multiaddr))
			जारी;

		ip_eth_mc_map(pmc->multiaddr, mcast_addr);

		अगर (batadv_mcast_mla_is_duplicate(mcast_addr, mcast_list))
			जारी;

		new = kदो_स्मृति(माप(*new), GFP_ATOMIC);
		अगर (!new) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		ether_addr_copy(new->addr, mcast_addr);
		hlist_add_head(&new->list, mcast_list);
		ret++;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/**
 * batadv_mcast_mla_softअगर_get_ipv6() - get softअगर IPv6 multicast listeners
 * @dev: the device to collect multicast addresses from
 * @mcast_list: a list to put found addresses पूर्णांकo
 * @flags: flags indicating the new multicast state
 *
 * Collects multicast addresses of IPv6 multicast listeners residing
 * on this kernel on the given soft पूर्णांकerface, dev, in
 * the given mcast_list. In general, multicast listeners provided by
 * your multicast receiving applications run directly on this node.
 *
 * Return: -ENOMEM on memory allocation error or the number of
 * items added to the mcast_list otherwise.
 */
#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक
batadv_mcast_mla_softअगर_get_ipv6(काष्ठा net_device *dev,
				 काष्ठा hlist_head *mcast_list,
				 काष्ठा batadv_mcast_mla_flags *flags)
अणु
	काष्ठा batadv_hw_addr *new;
	काष्ठा inet6_dev *in6_dev;
	u8 mcast_addr[ETH_ALEN];
	काष्ठा अगरmcaddr6 *pmc6;
	पूर्णांक ret = 0;

	अगर (flags->tvlv_flags & BATADV_MCAST_WANT_ALL_IPV6)
		वापस 0;

	rcu_पढ़ो_lock();

	in6_dev = __in6_dev_get(dev);
	अगर (!in6_dev) अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण

	क्रम (pmc6 = rcu_dereference(in6_dev->mc_list);
	     pmc6;
	     pmc6 = rcu_dereference(pmc6->next)) अणु
		अगर (IPV6_ADDR_MC_SCOPE(&pmc6->mca_addr) <
		    IPV6_ADDR_SCOPE_LINKLOCAL)
			जारी;

		अगर (flags->tvlv_flags & BATADV_MCAST_WANT_ALL_UNSNOOPABLES &&
		    ipv6_addr_is_ll_all_nodes(&pmc6->mca_addr))
			जारी;

		अगर (!(flags->tvlv_flags & BATADV_MCAST_WANT_NO_RTR6) &&
		    IPV6_ADDR_MC_SCOPE(&pmc6->mca_addr) >
		    IPV6_ADDR_SCOPE_LINKLOCAL)
			जारी;

		ipv6_eth_mc_map(&pmc6->mca_addr, mcast_addr);

		अगर (batadv_mcast_mla_is_duplicate(mcast_addr, mcast_list))
			जारी;

		new = kदो_स्मृति(माप(*new), GFP_ATOMIC);
		अगर (!new) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		ether_addr_copy(new->addr, mcast_addr);
		hlist_add_head(&new->list, mcast_list);
		ret++;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक
batadv_mcast_mla_softअगर_get_ipv6(काष्ठा net_device *dev,
				 काष्ठा hlist_head *mcast_list,
				 काष्ठा batadv_mcast_mla_flags *flags)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/**
 * batadv_mcast_mla_softअगर_get() - get softअगर multicast listeners
 * @dev: the device to collect multicast addresses from
 * @mcast_list: a list to put found addresses पूर्णांकo
 * @flags: flags indicating the new multicast state
 *
 * Collects multicast addresses of multicast listeners residing
 * on this kernel on the given soft पूर्णांकerface, dev, in
 * the given mcast_list. In general, multicast listeners provided by
 * your multicast receiving applications run directly on this node.
 *
 * If there is a bridge पूर्णांकerface on top of dev, collect from that one
 * instead. Just like with IP addresses and routes, multicast listeners
 * will(/should) रेजिस्टर to the bridge पूर्णांकerface instead of an
 * enslaved bat0.
 *
 * Return: -ENOMEM on memory allocation error or the number of
 * items added to the mcast_list otherwise.
 */
अटल पूर्णांक
batadv_mcast_mla_softअगर_get(काष्ठा net_device *dev,
			    काष्ठा hlist_head *mcast_list,
			    काष्ठा batadv_mcast_mla_flags *flags)
अणु
	काष्ठा net_device *bridge = batadv_mcast_get_bridge(dev);
	पूर्णांक ret4, ret6 = 0;

	अगर (bridge)
		dev = bridge;

	ret4 = batadv_mcast_mla_softअगर_get_ipv4(dev, mcast_list, flags);
	अगर (ret4 < 0)
		जाओ out;

	ret6 = batadv_mcast_mla_softअगर_get_ipv6(dev, mcast_list, flags);
	अगर (ret6 < 0) अणु
		ret4 = 0;
		जाओ out;
	पूर्ण

out:
	अगर (bridge)
		dev_put(bridge);

	वापस ret4 + ret6;
पूर्ण

/**
 * batadv_mcast_mla_br_addr_cpy() - copy a bridge multicast address
 * @dst: destination to ग_लिखो to - a multicast MAC address
 * @src: source to पढ़ो from - a multicast IP address
 *
 * Converts a given multicast IPv4/IPv6 address from a bridge
 * to its matching multicast MAC address and copies it पूर्णांकo the given
 * destination buffer.
 *
 * Caller needs to make sure the destination buffer can hold
 * at least ETH_ALEN bytes.
 */
अटल व्योम batadv_mcast_mla_br_addr_cpy(अक्षर *dst, स्थिर काष्ठा br_ip *src)
अणु
	अगर (src->proto == htons(ETH_P_IP))
		ip_eth_mc_map(src->dst.ip4, dst);
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा अगर (src->proto == htons(ETH_P_IPV6))
		ipv6_eth_mc_map(&src->dst.ip6, dst);
#पूर्ण_अगर
	अन्यथा
		eth_zero_addr(dst);
पूर्ण

/**
 * batadv_mcast_mla_bridge_get() - get bridged-in multicast listeners
 * @dev: a bridge slave whose bridge to collect multicast addresses from
 * @mcast_list: a list to put found addresses पूर्णांकo
 * @flags: flags indicating the new multicast state
 *
 * Collects multicast addresses of multicast listeners residing
 * on क्रमeign, non-mesh devices which we gave access to our mesh via
 * a bridge on top of the given soft पूर्णांकerface, dev, in the given
 * mcast_list.
 *
 * Return: -ENOMEM on memory allocation error or the number of
 * items added to the mcast_list otherwise.
 */
अटल पूर्णांक batadv_mcast_mla_bridge_get(काष्ठा net_device *dev,
				       काष्ठा hlist_head *mcast_list,
				       काष्ठा batadv_mcast_mla_flags *flags)
अणु
	काष्ठा list_head bridge_mcast_list = LIST_HEAD_INIT(bridge_mcast_list);
	काष्ठा br_ip_list *br_ip_entry, *पंचांगp;
	u8 tvlv_flags = flags->tvlv_flags;
	काष्ठा batadv_hw_addr *new;
	u8 mcast_addr[ETH_ALEN];
	पूर्णांक ret;

	/* we करोn't need to detect these devices/listeners, the IGMP/MLD
	 * snooping code of the Linux bridge alपढ़ोy करोes that क्रम us
	 */
	ret = br_multicast_list_adjacent(dev, &bridge_mcast_list);
	अगर (ret < 0)
		जाओ out;

	list_क्रम_each_entry(br_ip_entry, &bridge_mcast_list, list) अणु
		अगर (br_ip_entry->addr.proto == htons(ETH_P_IP)) अणु
			अगर (tvlv_flags & BATADV_MCAST_WANT_ALL_IPV4)
				जारी;

			अगर (tvlv_flags & BATADV_MCAST_WANT_ALL_UNSNOOPABLES &&
			    ipv4_is_local_multicast(br_ip_entry->addr.dst.ip4))
				जारी;

			अगर (!(tvlv_flags & BATADV_MCAST_WANT_NO_RTR4) &&
			    !ipv4_is_local_multicast(br_ip_entry->addr.dst.ip4))
				जारी;
		पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (br_ip_entry->addr.proto == htons(ETH_P_IPV6)) अणु
			अगर (tvlv_flags & BATADV_MCAST_WANT_ALL_IPV6)
				जारी;

			अगर (tvlv_flags & BATADV_MCAST_WANT_ALL_UNSNOOPABLES &&
			    ipv6_addr_is_ll_all_nodes(&br_ip_entry->addr.dst.ip6))
				जारी;

			अगर (!(tvlv_flags & BATADV_MCAST_WANT_NO_RTR6) &&
			    IPV6_ADDR_MC_SCOPE(&br_ip_entry->addr.dst.ip6) >
			    IPV6_ADDR_SCOPE_LINKLOCAL)
				जारी;
		पूर्ण
#पूर्ण_अगर

		batadv_mcast_mla_br_addr_cpy(mcast_addr, &br_ip_entry->addr);
		अगर (batadv_mcast_mla_is_duplicate(mcast_addr, mcast_list))
			जारी;

		new = kदो_स्मृति(माप(*new), GFP_ATOMIC);
		अगर (!new) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		ether_addr_copy(new->addr, mcast_addr);
		hlist_add_head(&new->list, mcast_list);
	पूर्ण

out:
	list_क्रम_each_entry_safe(br_ip_entry, पंचांगp, &bridge_mcast_list, list) अणु
		list_del(&br_ip_entry->list);
		kमुक्त(br_ip_entry);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * batadv_mcast_mla_list_मुक्त() - मुक्त a list of multicast addresses
 * @mcast_list: the list to मुक्त
 *
 * Removes and मुक्तs all items in the given mcast_list.
 */
अटल व्योम batadv_mcast_mla_list_मुक्त(काष्ठा hlist_head *mcast_list)
अणु
	काष्ठा batadv_hw_addr *mcast_entry;
	काष्ठा hlist_node *पंचांगp;

	hlist_क्रम_each_entry_safe(mcast_entry, पंचांगp, mcast_list, list) अणु
		hlist_del(&mcast_entry->list);
		kमुक्त(mcast_entry);
	पूर्ण
पूर्ण

/**
 * batadv_mcast_mla_tt_retract() - clean up multicast listener announcements
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @mcast_list: a list of addresses which should _not_ be हटाओd
 *
 * Retracts the announcement of any multicast listener from the
 * translation table except the ones listed in the given mcast_list.
 *
 * If mcast_list is शून्य then all are retracted.
 */
अटल व्योम batadv_mcast_mla_tt_retract(काष्ठा batadv_priv *bat_priv,
					काष्ठा hlist_head *mcast_list)
अणु
	काष्ठा batadv_hw_addr *mcast_entry;
	काष्ठा hlist_node *पंचांगp;

	hlist_क्रम_each_entry_safe(mcast_entry, पंचांगp, &bat_priv->mcast.mla_list,
				  list) अणु
		अगर (mcast_list &&
		    batadv_mcast_mla_is_duplicate(mcast_entry->addr,
						  mcast_list))
			जारी;

		batadv_tt_local_हटाओ(bat_priv, mcast_entry->addr,
				       BATADV_NO_FLAGS,
				       "mcast TT outdated", false);

		hlist_del(&mcast_entry->list);
		kमुक्त(mcast_entry);
	पूर्ण
पूर्ण

/**
 * batadv_mcast_mla_tt_add() - add multicast listener announcements
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @mcast_list: a list of addresses which are going to get added
 *
 * Adds multicast listener announcements from the given mcast_list to the
 * translation table अगर they have not been added yet.
 */
अटल व्योम batadv_mcast_mla_tt_add(काष्ठा batadv_priv *bat_priv,
				    काष्ठा hlist_head *mcast_list)
अणु
	काष्ठा batadv_hw_addr *mcast_entry;
	काष्ठा hlist_node *पंचांगp;

	अगर (!mcast_list)
		वापस;

	hlist_क्रम_each_entry_safe(mcast_entry, पंचांगp, mcast_list, list) अणु
		अगर (batadv_mcast_mla_is_duplicate(mcast_entry->addr,
						  &bat_priv->mcast.mla_list))
			जारी;

		अगर (!batadv_tt_local_add(bat_priv->soft_अगरace,
					 mcast_entry->addr, BATADV_NO_FLAGS,
					 BATADV_शून्य_IFINDEX, BATADV_NO_MARK))
			जारी;

		hlist_del(&mcast_entry->list);
		hlist_add_head(&mcast_entry->list, &bat_priv->mcast.mla_list);
	पूर्ण
पूर्ण

/**
 * batadv_mcast_querier_log() - debug output regarding the querier status on
 *  link
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @str_proto: a string क्रम the querier protocol (e.g. "IGMP" or "MLD")
 * @old_state: the previous querier state on our link
 * @new_state: the new querier state on our link
 *
 * Outमाला_दो debug messages to the logging facility with log level 'mcast'
 * regarding changes to the querier status on the link which are relevant
 * to our multicast optimizations.
 *
 * Usually this is about whether a querier appeared or vanished in
 * our mesh or whether the querier is in the suboptimal position of being
 * behind our local bridge segment: Snooping चयनes will directly
 * क्रमward listener reports to the querier, thereक्रमe baपंचांगan-adv and
 * the bridge will potentially not see these listeners - the querier is
 * potentially shaकरोwing listeners from us then.
 *
 * This is only पूर्णांकeresting क्रम nodes with a bridge on top of their
 * soft पूर्णांकerface.
 */
अटल व्योम
batadv_mcast_querier_log(काष्ठा batadv_priv *bat_priv, अक्षर *str_proto,
			 काष्ठा batadv_mcast_querier_state *old_state,
			 काष्ठा batadv_mcast_querier_state *new_state)
अणु
	अगर (!old_state->exists && new_state->exists)
		batadv_info(bat_priv->soft_अगरace, "%s Querier appeared\n",
			    str_proto);
	अन्यथा अगर (old_state->exists && !new_state->exists)
		batadv_info(bat_priv->soft_अगरace,
			    "%s Querier disappeared - multicast optimizations disabled\n",
			    str_proto);
	अन्यथा अगर (!bat_priv->mcast.mla_flags.bridged && !new_state->exists)
		batadv_info(bat_priv->soft_अगरace,
			    "No %s Querier present - multicast optimizations disabled\n",
			    str_proto);

	अगर (new_state->exists) अणु
		अगर ((!old_state->shaकरोwing && new_state->shaकरोwing) ||
		    (!old_state->exists && new_state->shaकरोwing))
			batadv_dbg(BATADV_DBG_MCAST, bat_priv,
				   "%s Querier is behind our bridged segment: Might shadow listeners\n",
				   str_proto);
		अन्यथा अगर (old_state->shaकरोwing && !new_state->shaकरोwing)
			batadv_dbg(BATADV_DBG_MCAST, bat_priv,
				   "%s Querier is not behind our bridged segment\n",
				   str_proto);
	पूर्ण
पूर्ण

/**
 * batadv_mcast_bridge_log() - debug output क्रम topology changes in bridged
 *  setups
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @new_flags: flags indicating the new multicast state
 *
 * If no bridges are ever used on this node, then this function करोes nothing.
 *
 * Otherwise this function outमाला_दो debug inक्रमmation to the 'mcast' log level
 * which might be relevant to our multicast optimizations.
 *
 * More precisely, it outमाला_दो inक्रमmation when a bridge पूर्णांकerface is added or
 * हटाओd from a soft पूर्णांकerface. And when a bridge is present, it further
 * outमाला_दो inक्रमmation about the querier state which is relevant क्रम the
 * multicast flags this node is going to set.
 */
अटल व्योम
batadv_mcast_bridge_log(काष्ठा batadv_priv *bat_priv,
			काष्ठा batadv_mcast_mla_flags *new_flags)
अणु
	काष्ठा batadv_mcast_mla_flags *old_flags = &bat_priv->mcast.mla_flags;

	अगर (!old_flags->bridged && new_flags->bridged)
		batadv_dbg(BATADV_DBG_MCAST, bat_priv,
			   "Bridge added: Setting Unsnoopables(U)-flag\n");
	अन्यथा अगर (old_flags->bridged && !new_flags->bridged)
		batadv_dbg(BATADV_DBG_MCAST, bat_priv,
			   "Bridge removed: Unsetting Unsnoopables(U)-flag\n");

	अगर (new_flags->bridged) अणु
		batadv_mcast_querier_log(bat_priv, "IGMP",
					 &old_flags->querier_ipv4,
					 &new_flags->querier_ipv4);
		batadv_mcast_querier_log(bat_priv, "MLD",
					 &old_flags->querier_ipv6,
					 &new_flags->querier_ipv6);
	पूर्ण
पूर्ण

/**
 * batadv_mcast_flags_log() - output debug inक्रमmation about mcast flag changes
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @flags: TVLV flags indicating the new multicast state
 *
 * Whenever the multicast TVLV flags this node announces change, this function
 * should be used to notअगरy userspace about the change.
 */
अटल व्योम batadv_mcast_flags_log(काष्ठा batadv_priv *bat_priv, u8 flags)
अणु
	bool old_enabled = bat_priv->mcast.mla_flags.enabled;
	u8 old_flags = bat_priv->mcast.mla_flags.tvlv_flags;
	अक्षर str_old_flags[] = "[.... . ]";

	प्र_लिखो(str_old_flags, "[%c%c%c%s%s]",
		(old_flags & BATADV_MCAST_WANT_ALL_UNSNOOPABLES) ? 'U' : '.',
		(old_flags & BATADV_MCAST_WANT_ALL_IPV4) ? '4' : '.',
		(old_flags & BATADV_MCAST_WANT_ALL_IPV6) ? '6' : '.',
		!(old_flags & BATADV_MCAST_WANT_NO_RTR4) ? "R4" : ". ",
		!(old_flags & BATADV_MCAST_WANT_NO_RTR6) ? "R6" : ". ");

	batadv_dbg(BATADV_DBG_MCAST, bat_priv,
		   "Changing multicast flags from '%s' to '[%c%c%c%s%s]'\n",
		   old_enabled ? str_old_flags : "<undefined>",
		   (flags & BATADV_MCAST_WANT_ALL_UNSNOOPABLES) ? 'U' : '.',
		   (flags & BATADV_MCAST_WANT_ALL_IPV4) ? '4' : '.',
		   (flags & BATADV_MCAST_WANT_ALL_IPV6) ? '6' : '.',
		   !(flags & BATADV_MCAST_WANT_NO_RTR4) ? "R4" : ". ",
		   !(flags & BATADV_MCAST_WANT_NO_RTR6) ? "R6" : ". ");
पूर्ण

/**
 * batadv_mcast_mla_flags_update() - update multicast flags
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @flags: flags indicating the new multicast state
 *
 * Updates the own multicast tvlv with our current multicast related settings,
 * capabilities and inabilities.
 */
अटल व्योम
batadv_mcast_mla_flags_update(काष्ठा batadv_priv *bat_priv,
			      काष्ठा batadv_mcast_mla_flags *flags)
अणु
	काष्ठा batadv_tvlv_mcast_data mcast_data;

	अगर (!स_भेद(flags, &bat_priv->mcast.mla_flags, माप(*flags)))
		वापस;

	batadv_mcast_bridge_log(bat_priv, flags);
	batadv_mcast_flags_log(bat_priv, flags->tvlv_flags);

	mcast_data.flags = flags->tvlv_flags;
	स_रखो(mcast_data.reserved, 0, माप(mcast_data.reserved));

	batadv_tvlv_container_रेजिस्टर(bat_priv, BATADV_TVLV_MCAST, 2,
				       &mcast_data, माप(mcast_data));

	bat_priv->mcast.mla_flags = *flags;
पूर्ण

/**
 * __batadv_mcast_mla_update() - update the own MLAs
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Updates the own multicast listener announcements in the translation
 * table as well as the own, announced multicast tvlv container.
 *
 * Note that non-conflicting पढ़ोs and ग_लिखोs to bat_priv->mcast.mla_list
 * in batadv_mcast_mla_tt_retract() and batadv_mcast_mla_tt_add() are
 * ensured by the non-parallel execution of the worker this function
 * beदीर्घs to.
 */
अटल व्योम __batadv_mcast_mla_update(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा net_device *soft_अगरace = bat_priv->soft_अगरace;
	काष्ठा hlist_head mcast_list = HLIST_HEAD_INIT;
	काष्ठा batadv_mcast_mla_flags flags;
	पूर्णांक ret;

	flags = batadv_mcast_mla_flags_get(bat_priv);

	ret = batadv_mcast_mla_softअगर_get(soft_अगरace, &mcast_list, &flags);
	अगर (ret < 0)
		जाओ out;

	ret = batadv_mcast_mla_bridge_get(soft_अगरace, &mcast_list, &flags);
	अगर (ret < 0)
		जाओ out;

	spin_lock(&bat_priv->mcast.mla_lock);
	batadv_mcast_mla_tt_retract(bat_priv, &mcast_list);
	batadv_mcast_mla_tt_add(bat_priv, &mcast_list);
	batadv_mcast_mla_flags_update(bat_priv, &flags);
	spin_unlock(&bat_priv->mcast.mla_lock);

out:
	batadv_mcast_mla_list_मुक्त(&mcast_list);
पूर्ण

/**
 * batadv_mcast_mla_update() - update the own MLAs
 * @work: kernel work काष्ठा
 *
 * Updates the own multicast listener announcements in the translation
 * table as well as the own, announced multicast tvlv container.
 *
 * In the end, reschedules the work समयr.
 */
अटल व्योम batadv_mcast_mla_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delayed_work;
	काष्ठा batadv_priv_mcast *priv_mcast;
	काष्ठा batadv_priv *bat_priv;

	delayed_work = to_delayed_work(work);
	priv_mcast = container_of(delayed_work, काष्ठा batadv_priv_mcast, work);
	bat_priv = container_of(priv_mcast, काष्ठा batadv_priv, mcast);

	__batadv_mcast_mla_update(bat_priv);
	batadv_mcast_start_समयr(bat_priv);
पूर्ण

/**
 * batadv_mcast_is_report_ipv4() -ै /check क्रम IGMP reports
 * @skb: the ethernet frame destined क्रम the mesh
 *
 * This call might पुनः_स्मृतिate skb data.
 *
 * Checks whether the given frame is a valid IGMP report.
 *
 * Return: If so then true, otherwise false.
 */
अटल bool batadv_mcast_is_report_ipv4(काष्ठा sk_buff *skb)
अणु
	अगर (ip_mc_check_igmp(skb) < 0)
		वापस false;

	चयन (igmp_hdr(skb)->type) अणु
	हाल IGMP_HOST_MEMBERSHIP_REPORT:
	हाल IGMPV2_HOST_MEMBERSHIP_REPORT:
	हाल IGMPV3_HOST_MEMBERSHIP_REPORT:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * batadv_mcast_क्रमw_mode_check_ipv4() - check क्रम optimized क्रमwarding
 *  potential
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the IPv4 packet to check
 * @is_unsnoopable: stores whether the destination is snoopable
 * @is_routable: stores whether the destination is routable
 *
 * Checks whether the given IPv4 packet has the potential to be क्रमwarded with a
 * mode more optimal than classic flooding.
 *
 * Return: If so then 0. Otherwise -EINVAL or -ENOMEM in हाल of memory
 * allocation failure.
 */
अटल पूर्णांक batadv_mcast_क्रमw_mode_check_ipv4(काष्ठा batadv_priv *bat_priv,
					     काष्ठा sk_buff *skb,
					     bool *is_unsnoopable,
					     पूर्णांक *is_routable)
अणु
	काष्ठा iphdr *iphdr;

	/* We might fail due to out-of-memory -> drop it */
	अगर (!pskb_may_pull(skb, माप(काष्ठा ethhdr) + माप(*iphdr)))
		वापस -ENOMEM;

	अगर (batadv_mcast_is_report_ipv4(skb))
		वापस -EINVAL;

	iphdr = ip_hdr(skb);

	/* link-local multicast listeners behind a bridge are
	 * not snoopable (see RFC4541, section 2.1.2.2)
	 */
	अगर (ipv4_is_local_multicast(iphdr->daddr))
		*is_unsnoopable = true;
	अन्यथा
		*is_routable = ETH_P_IP;

	वापस 0;
पूर्ण

/**
 * batadv_mcast_is_report_ipv6() - check क्रम MLD reports
 * @skb: the ethernet frame destined क्रम the mesh
 *
 * This call might पुनः_स्मृतिate skb data.
 *
 * Checks whether the given frame is a valid MLD report.
 *
 * Return: If so then true, otherwise false.
 */
अटल bool batadv_mcast_is_report_ipv6(काष्ठा sk_buff *skb)
अणु
	अगर (ipv6_mc_check_mld(skb) < 0)
		वापस false;

	चयन (icmp6_hdr(skb)->icmp6_type) अणु
	हाल ICMPV6_MGM_REPORT:
	हाल ICMPV6_MLD2_REPORT:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * batadv_mcast_क्रमw_mode_check_ipv6() - check क्रम optimized क्रमwarding
 *  potential
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the IPv6 packet to check
 * @is_unsnoopable: stores whether the destination is snoopable
 * @is_routable: stores whether the destination is routable
 *
 * Checks whether the given IPv6 packet has the potential to be क्रमwarded with a
 * mode more optimal than classic flooding.
 *
 * Return: If so then 0. Otherwise -EINVAL is or -ENOMEM अगर we are out of memory
 */
अटल पूर्णांक batadv_mcast_क्रमw_mode_check_ipv6(काष्ठा batadv_priv *bat_priv,
					     काष्ठा sk_buff *skb,
					     bool *is_unsnoopable,
					     पूर्णांक *is_routable)
अणु
	काष्ठा ipv6hdr *ip6hdr;

	/* We might fail due to out-of-memory -> drop it */
	अगर (!pskb_may_pull(skb, माप(काष्ठा ethhdr) + माप(*ip6hdr)))
		वापस -ENOMEM;

	अगर (batadv_mcast_is_report_ipv6(skb))
		वापस -EINVAL;

	ip6hdr = ipv6_hdr(skb);

	अगर (IPV6_ADDR_MC_SCOPE(&ip6hdr->daddr) < IPV6_ADDR_SCOPE_LINKLOCAL)
		वापस -EINVAL;

	/* link-local-all-nodes multicast listeners behind a bridge are
	 * not snoopable (see RFC4541, section 3, paragraph 3)
	 */
	अगर (ipv6_addr_is_ll_all_nodes(&ip6hdr->daddr))
		*is_unsnoopable = true;
	अन्यथा अगर (IPV6_ADDR_MC_SCOPE(&ip6hdr->daddr) > IPV6_ADDR_SCOPE_LINKLOCAL)
		*is_routable = ETH_P_IPV6;

	वापस 0;
पूर्ण

/**
 * batadv_mcast_क्रमw_mode_check() - check क्रम optimized क्रमwarding potential
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the multicast frame to check
 * @is_unsnoopable: stores whether the destination is snoopable
 * @is_routable: stores whether the destination is routable
 *
 * Checks whether the given multicast ethernet frame has the potential to be
 * क्रमwarded with a mode more optimal than classic flooding.
 *
 * Return: If so then 0. Otherwise -EINVAL is or -ENOMEM अगर we are out of memory
 */
अटल पूर्णांक batadv_mcast_क्रमw_mode_check(काष्ठा batadv_priv *bat_priv,
					काष्ठा sk_buff *skb,
					bool *is_unsnoopable,
					पूर्णांक *is_routable)
अणु
	काष्ठा ethhdr *ethhdr = eth_hdr(skb);

	अगर (!atomic_पढ़ो(&bat_priv->multicast_mode))
		वापस -EINVAL;

	चयन (ntohs(ethhdr->h_proto)) अणु
	हाल ETH_P_IP:
		वापस batadv_mcast_क्रमw_mode_check_ipv4(bat_priv, skb,
							 is_unsnoopable,
							 is_routable);
	हाल ETH_P_IPV6:
		अगर (!IS_ENABLED(CONFIG_IPV6))
			वापस -EINVAL;

		वापस batadv_mcast_क्रमw_mode_check_ipv6(bat_priv, skb,
							 is_unsnoopable,
							 is_routable);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * batadv_mcast_क्रमw_want_all_ip_count() - count nodes with unspecअगरic mcast
 *  पूर्णांकerest
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @ethhdr: ethernet header of a packet
 *
 * Return: the number of nodes which want all IPv4 multicast traffic अगर the
 * given ethhdr is from an IPv4 packet or the number of nodes which want all
 * IPv6 traffic अगर it matches an IPv6 packet.
 */
अटल पूर्णांक batadv_mcast_क्रमw_want_all_ip_count(काष्ठा batadv_priv *bat_priv,
					       काष्ठा ethhdr *ethhdr)
अणु
	चयन (ntohs(ethhdr->h_proto)) अणु
	हाल ETH_P_IP:
		वापस atomic_पढ़ो(&bat_priv->mcast.num_want_all_ipv4);
	हाल ETH_P_IPV6:
		वापस atomic_पढ़ो(&bat_priv->mcast.num_want_all_ipv6);
	शेष:
		/* we shouldn't be here... */
		वापस 0;
	पूर्ण
पूर्ण

/**
 * batadv_mcast_क्रमw_rtr_count() - count nodes with a multicast router
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @protocol: the ethernet protocol type to count multicast routers क्रम
 *
 * Return: the number of nodes which want all routable IPv4 multicast traffic
 * अगर the protocol is ETH_P_IP or the number of nodes which want all routable
 * IPv6 traffic अगर the protocol is ETH_P_IPV6. Otherwise वापसs 0.
 */

अटल पूर्णांक batadv_mcast_क्रमw_rtr_count(काष्ठा batadv_priv *bat_priv,
				       पूर्णांक protocol)
अणु
	चयन (protocol) अणु
	हाल ETH_P_IP:
		वापस atomic_पढ़ो(&bat_priv->mcast.num_want_all_rtr4);
	हाल ETH_P_IPV6:
		वापस atomic_पढ़ो(&bat_priv->mcast.num_want_all_rtr6);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/**
 * batadv_mcast_क्रमw_tt_node_get() - get a multicast tt node
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @ethhdr: the ether header containing the multicast destination
 *
 * Return: an orig_node matching the multicast address provided by ethhdr
 * via a translation table lookup. This increases the वापसed nodes refcount.
 */
अटल काष्ठा batadv_orig_node *
batadv_mcast_क्रमw_tt_node_get(काष्ठा batadv_priv *bat_priv,
			      काष्ठा ethhdr *ethhdr)
अणु
	वापस batadv_transtable_search(bat_priv, शून्य, ethhdr->h_dest,
					BATADV_NO_FLAGS);
पूर्ण

/**
 * batadv_mcast_क्रमw_ipv4_node_get() - get a node with an ipv4 flag
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: an orig_node which has the BATADV_MCAST_WANT_ALL_IPV4 flag set and
 * increases its refcount.
 */
अटल काष्ठा batadv_orig_node *
batadv_mcast_क्रमw_ipv4_node_get(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_orig_node *पंचांगp_orig_node, *orig_node = शून्य;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(पंचांगp_orig_node,
				 &bat_priv->mcast.want_all_ipv4_list,
				 mcast_want_all_ipv4_node) अणु
		अगर (!kref_get_unless_zero(&पंचांगp_orig_node->refcount))
			जारी;

		orig_node = पंचांगp_orig_node;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस orig_node;
पूर्ण

/**
 * batadv_mcast_क्रमw_ipv6_node_get() - get a node with an ipv6 flag
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: an orig_node which has the BATADV_MCAST_WANT_ALL_IPV6 flag set
 * and increases its refcount.
 */
अटल काष्ठा batadv_orig_node *
batadv_mcast_क्रमw_ipv6_node_get(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_orig_node *पंचांगp_orig_node, *orig_node = शून्य;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(पंचांगp_orig_node,
				 &bat_priv->mcast.want_all_ipv6_list,
				 mcast_want_all_ipv6_node) अणु
		अगर (!kref_get_unless_zero(&पंचांगp_orig_node->refcount))
			जारी;

		orig_node = पंचांगp_orig_node;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस orig_node;
पूर्ण

/**
 * batadv_mcast_क्रमw_ip_node_get() - get a node with an ipv4/ipv6 flag
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @ethhdr: an ethernet header to determine the protocol family from
 *
 * Return: an orig_node which has the BATADV_MCAST_WANT_ALL_IPV4 or
 * BATADV_MCAST_WANT_ALL_IPV6 flag, depending on the provided ethhdr, sets and
 * increases its refcount.
 */
अटल काष्ठा batadv_orig_node *
batadv_mcast_क्रमw_ip_node_get(काष्ठा batadv_priv *bat_priv,
			      काष्ठा ethhdr *ethhdr)
अणु
	चयन (ntohs(ethhdr->h_proto)) अणु
	हाल ETH_P_IP:
		वापस batadv_mcast_क्रमw_ipv4_node_get(bat_priv);
	हाल ETH_P_IPV6:
		वापस batadv_mcast_क्रमw_ipv6_node_get(bat_priv);
	शेष:
		/* we shouldn't be here... */
		वापस शून्य;
	पूर्ण
पूर्ण

/**
 * batadv_mcast_क्रमw_unsnoop_node_get() - get a node with an unsnoopable flag
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: an orig_node which has the BATADV_MCAST_WANT_ALL_UNSNOOPABLES flag
 * set and increases its refcount.
 */
अटल काष्ठा batadv_orig_node *
batadv_mcast_क्रमw_unsnoop_node_get(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_orig_node *पंचांगp_orig_node, *orig_node = शून्य;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(पंचांगp_orig_node,
				 &bat_priv->mcast.want_all_unsnoopables_list,
				 mcast_want_all_unsnoopables_node) अणु
		अगर (!kref_get_unless_zero(&पंचांगp_orig_node->refcount))
			जारी;

		orig_node = पंचांगp_orig_node;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस orig_node;
पूर्ण

/**
 * batadv_mcast_क्रमw_rtr4_node_get() - get a node with an ipv4 mcast router flag
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: an orig_node which has the BATADV_MCAST_WANT_NO_RTR4 flag unset and
 * increases its refcount.
 */
अटल काष्ठा batadv_orig_node *
batadv_mcast_क्रमw_rtr4_node_get(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_orig_node *पंचांगp_orig_node, *orig_node = शून्य;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(पंचांगp_orig_node,
				 &bat_priv->mcast.want_all_rtr4_list,
				 mcast_want_all_rtr4_node) अणु
		अगर (!kref_get_unless_zero(&पंचांगp_orig_node->refcount))
			जारी;

		orig_node = पंचांगp_orig_node;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस orig_node;
पूर्ण

/**
 * batadv_mcast_क्रमw_rtr6_node_get() - get a node with an ipv6 mcast router flag
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: an orig_node which has the BATADV_MCAST_WANT_NO_RTR6 flag unset
 * and increases its refcount.
 */
अटल काष्ठा batadv_orig_node *
batadv_mcast_क्रमw_rtr6_node_get(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_orig_node *पंचांगp_orig_node, *orig_node = शून्य;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(पंचांगp_orig_node,
				 &bat_priv->mcast.want_all_rtr6_list,
				 mcast_want_all_rtr6_node) अणु
		अगर (!kref_get_unless_zero(&पंचांगp_orig_node->refcount))
			जारी;

		orig_node = पंचांगp_orig_node;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस orig_node;
पूर्ण

/**
 * batadv_mcast_क्रमw_rtr_node_get() - get a node with an ipv4/ipv6 router flag
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @ethhdr: an ethernet header to determine the protocol family from
 *
 * Return: an orig_node which has no BATADV_MCAST_WANT_NO_RTR4 or
 * BATADV_MCAST_WANT_NO_RTR6 flag, depending on the provided ethhdr, set and
 * increases its refcount.
 */
अटल काष्ठा batadv_orig_node *
batadv_mcast_क्रमw_rtr_node_get(काष्ठा batadv_priv *bat_priv,
			       काष्ठा ethhdr *ethhdr)
अणु
	चयन (ntohs(ethhdr->h_proto)) अणु
	हाल ETH_P_IP:
		वापस batadv_mcast_क्रमw_rtr4_node_get(bat_priv);
	हाल ETH_P_IPV6:
		वापस batadv_mcast_क्रमw_rtr6_node_get(bat_priv);
	शेष:
		/* we shouldn't be here... */
		वापस शून्य;
	पूर्ण
पूर्ण

/**
 * batadv_mcast_क्रमw_mode() - check on how to क्रमward a multicast packet
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: The multicast packet to check
 * @orig: an originator to be set to क्रमward the skb to
 *
 * Return: the क्रमwarding mode as क्रमागत batadv_क्रमw_mode and in हाल of
 * BATADV_FORW_SINGLE set the orig to the single originator the skb
 * should be क्रमwarded to.
 */
क्रमागत batadv_क्रमw_mode
batadv_mcast_क्रमw_mode(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb,
		       काष्ठा batadv_orig_node **orig)
अणु
	पूर्णांक ret, tt_count, ip_count, unsnoop_count, total_count;
	bool is_unsnoopable = false;
	अचिन्हित पूर्णांक mcast_fanout;
	काष्ठा ethhdr *ethhdr;
	पूर्णांक is_routable = 0;
	पूर्णांक rtr_count = 0;

	ret = batadv_mcast_क्रमw_mode_check(bat_priv, skb, &is_unsnoopable,
					   &is_routable);
	अगर (ret == -ENOMEM)
		वापस BATADV_FORW_NONE;
	अन्यथा अगर (ret < 0)
		वापस BATADV_FORW_ALL;

	ethhdr = eth_hdr(skb);

	tt_count = batadv_tt_global_hash_count(bat_priv, ethhdr->h_dest,
					       BATADV_NO_FLAGS);
	ip_count = batadv_mcast_क्रमw_want_all_ip_count(bat_priv, ethhdr);
	unsnoop_count = !is_unsnoopable ? 0 :
			atomic_पढ़ो(&bat_priv->mcast.num_want_all_unsnoopables);
	rtr_count = batadv_mcast_क्रमw_rtr_count(bat_priv, is_routable);

	total_count = tt_count + ip_count + unsnoop_count + rtr_count;

	चयन (total_count) अणु
	हाल 1:
		अगर (tt_count)
			*orig = batadv_mcast_क्रमw_tt_node_get(bat_priv, ethhdr);
		अन्यथा अगर (ip_count)
			*orig = batadv_mcast_क्रमw_ip_node_get(bat_priv, ethhdr);
		अन्यथा अगर (unsnoop_count)
			*orig = batadv_mcast_क्रमw_unsnoop_node_get(bat_priv);
		अन्यथा अगर (rtr_count)
			*orig = batadv_mcast_क्रमw_rtr_node_get(bat_priv,
							       ethhdr);

		अगर (*orig)
			वापस BATADV_FORW_SINGLE;

		fallthrough;
	हाल 0:
		वापस BATADV_FORW_NONE;
	शेष:
		mcast_fanout = atomic_पढ़ो(&bat_priv->multicast_fanout);

		अगर (!unsnoop_count && total_count <= mcast_fanout)
			वापस BATADV_FORW_SOME;
	पूर्ण

	वापस BATADV_FORW_ALL;
पूर्ण

/**
 * batadv_mcast_क्रमw_send_orig() - send a multicast packet to an originator
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the multicast packet to send
 * @vid: the vlan identअगरier
 * @orig_node: the originator to send the packet to
 *
 * Return: NET_XMIT_DROP in हाल of error or NET_XMIT_SUCCESS otherwise.
 */
पूर्णांक batadv_mcast_क्रमw_send_orig(काष्ठा batadv_priv *bat_priv,
				काष्ठा sk_buff *skb,
				अचिन्हित लघु vid,
				काष्ठा batadv_orig_node *orig_node)
अणु
	/* Aव्योम sending multicast-in-unicast packets to other BLA
	 * gateways - they alपढ़ोy got the frame from the LAN side
	 * we share with them.
	 * TODO: Refactor to take BLA पूर्णांकo account earlier, to aव्योम
	 * reducing the mcast_fanout count.
	 */
	अगर (batadv_bla_is_backbone_gw_orig(bat_priv, orig_node->orig, vid)) अणु
		dev_kमुक्त_skb(skb);
		वापस NET_XMIT_SUCCESS;
	पूर्ण

	वापस batadv_send_skb_unicast(bat_priv, skb, BATADV_UNICAST, 0,
				       orig_node, vid);
पूर्ण

/**
 * batadv_mcast_क्रमw_tt() - क्रमwards a packet to multicast listeners
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the multicast packet to transmit
 * @vid: the vlan identअगरier
 *
 * Sends copies of a frame with multicast destination to any multicast
 * listener रेजिस्टरed in the translation table. A transmission is perक्रमmed
 * via a baपंचांगan-adv unicast packet क्रम each such destination node.
 *
 * Return: NET_XMIT_DROP on memory allocation failure, NET_XMIT_SUCCESS
 * otherwise.
 */
अटल पूर्णांक
batadv_mcast_क्रमw_tt(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb,
		     अचिन्हित लघु vid)
अणु
	पूर्णांक ret = NET_XMIT_SUCCESS;
	काष्ठा sk_buff *newskb;

	काष्ठा batadv_tt_orig_list_entry *orig_entry;

	काष्ठा batadv_tt_global_entry *tt_global;
	स्थिर u8 *addr = eth_hdr(skb)->h_dest;

	tt_global = batadv_tt_global_hash_find(bat_priv, addr, vid);
	अगर (!tt_global)
		जाओ out;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(orig_entry, &tt_global->orig_list, list) अणु
		newskb = skb_copy(skb, GFP_ATOMIC);
		अगर (!newskb) अणु
			ret = NET_XMIT_DROP;
			अवरोध;
		पूर्ण

		batadv_mcast_क्रमw_send_orig(bat_priv, newskb, vid,
					    orig_entry->orig_node);
	पूर्ण
	rcu_पढ़ो_unlock();

	batadv_tt_global_entry_put(tt_global);

out:
	वापस ret;
पूर्ण

/**
 * batadv_mcast_क्रमw_want_all_ipv4() - क्रमward to nodes with want-all-ipv4
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the multicast packet to transmit
 * @vid: the vlan identअगरier
 *
 * Sends copies of a frame with multicast destination to any node with a
 * BATADV_MCAST_WANT_ALL_IPV4 flag set. A transmission is perक्रमmed via a
 * baपंचांगan-adv unicast packet क्रम each such destination node.
 *
 * Return: NET_XMIT_DROP on memory allocation failure, NET_XMIT_SUCCESS
 * otherwise.
 */
अटल पूर्णांक
batadv_mcast_क्रमw_want_all_ipv4(काष्ठा batadv_priv *bat_priv,
				काष्ठा sk_buff *skb, अचिन्हित लघु vid)
अणु
	काष्ठा batadv_orig_node *orig_node;
	पूर्णांक ret = NET_XMIT_SUCCESS;
	काष्ठा sk_buff *newskb;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(orig_node,
				 &bat_priv->mcast.want_all_ipv4_list,
				 mcast_want_all_ipv4_node) अणु
		newskb = skb_copy(skb, GFP_ATOMIC);
		अगर (!newskb) अणु
			ret = NET_XMIT_DROP;
			अवरोध;
		पूर्ण

		batadv_mcast_क्रमw_send_orig(bat_priv, newskb, vid, orig_node);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/**
 * batadv_mcast_क्रमw_want_all_ipv6() - क्रमward to nodes with want-all-ipv6
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: The multicast packet to transmit
 * @vid: the vlan identअगरier
 *
 * Sends copies of a frame with multicast destination to any node with a
 * BATADV_MCAST_WANT_ALL_IPV6 flag set. A transmission is perक्रमmed via a
 * baपंचांगan-adv unicast packet क्रम each such destination node.
 *
 * Return: NET_XMIT_DROP on memory allocation failure, NET_XMIT_SUCCESS
 * otherwise.
 */
अटल पूर्णांक
batadv_mcast_क्रमw_want_all_ipv6(काष्ठा batadv_priv *bat_priv,
				काष्ठा sk_buff *skb, अचिन्हित लघु vid)
अणु
	काष्ठा batadv_orig_node *orig_node;
	पूर्णांक ret = NET_XMIT_SUCCESS;
	काष्ठा sk_buff *newskb;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(orig_node,
				 &bat_priv->mcast.want_all_ipv6_list,
				 mcast_want_all_ipv6_node) अणु
		newskb = skb_copy(skb, GFP_ATOMIC);
		अगर (!newskb) अणु
			ret = NET_XMIT_DROP;
			अवरोध;
		पूर्ण

		batadv_mcast_क्रमw_send_orig(bat_priv, newskb, vid, orig_node);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/**
 * batadv_mcast_क्रमw_want_all() - क्रमward packet to nodes in a want-all list
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the multicast packet to transmit
 * @vid: the vlan identअगरier
 *
 * Sends copies of a frame with multicast destination to any node with a
 * BATADV_MCAST_WANT_ALL_IPV4 or BATADV_MCAST_WANT_ALL_IPV6 flag set. A
 * transmission is perक्रमmed via a baपंचांगan-adv unicast packet क्रम each such
 * destination node.
 *
 * Return: NET_XMIT_DROP on memory allocation failure or अगर the protocol family
 * is neither IPv4 nor IPv6. NET_XMIT_SUCCESS otherwise.
 */
अटल पूर्णांक
batadv_mcast_क्रमw_want_all(काष्ठा batadv_priv *bat_priv,
			   काष्ठा sk_buff *skb, अचिन्हित लघु vid)
अणु
	चयन (ntohs(eth_hdr(skb)->h_proto)) अणु
	हाल ETH_P_IP:
		वापस batadv_mcast_क्रमw_want_all_ipv4(bat_priv, skb, vid);
	हाल ETH_P_IPV6:
		वापस batadv_mcast_क्रमw_want_all_ipv6(bat_priv, skb, vid);
	शेष:
		/* we shouldn't be here... */
		वापस NET_XMIT_DROP;
	पूर्ण
पूर्ण

/**
 * batadv_mcast_क्रमw_want_all_rtr4() - क्रमward to nodes with want-all-rtr4
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the multicast packet to transmit
 * @vid: the vlan identअगरier
 *
 * Sends copies of a frame with multicast destination to any node with a
 * BATADV_MCAST_WANT_NO_RTR4 flag unset. A transmission is perक्रमmed via a
 * baपंचांगan-adv unicast packet क्रम each such destination node.
 *
 * Return: NET_XMIT_DROP on memory allocation failure, NET_XMIT_SUCCESS
 * otherwise.
 */
अटल पूर्णांक
batadv_mcast_क्रमw_want_all_rtr4(काष्ठा batadv_priv *bat_priv,
				काष्ठा sk_buff *skb, अचिन्हित लघु vid)
अणु
	काष्ठा batadv_orig_node *orig_node;
	पूर्णांक ret = NET_XMIT_SUCCESS;
	काष्ठा sk_buff *newskb;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(orig_node,
				 &bat_priv->mcast.want_all_rtr4_list,
				 mcast_want_all_rtr4_node) अणु
		newskb = skb_copy(skb, GFP_ATOMIC);
		अगर (!newskb) अणु
			ret = NET_XMIT_DROP;
			अवरोध;
		पूर्ण

		batadv_mcast_क्रमw_send_orig(bat_priv, newskb, vid, orig_node);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/**
 * batadv_mcast_क्रमw_want_all_rtr6() - क्रमward to nodes with want-all-rtr6
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: The multicast packet to transmit
 * @vid: the vlan identअगरier
 *
 * Sends copies of a frame with multicast destination to any node with a
 * BATADV_MCAST_WANT_NO_RTR6 flag unset. A transmission is perक्रमmed via a
 * baपंचांगan-adv unicast packet क्रम each such destination node.
 *
 * Return: NET_XMIT_DROP on memory allocation failure, NET_XMIT_SUCCESS
 * otherwise.
 */
अटल पूर्णांक
batadv_mcast_क्रमw_want_all_rtr6(काष्ठा batadv_priv *bat_priv,
				काष्ठा sk_buff *skb, अचिन्हित लघु vid)
अणु
	काष्ठा batadv_orig_node *orig_node;
	पूर्णांक ret = NET_XMIT_SUCCESS;
	काष्ठा sk_buff *newskb;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(orig_node,
				 &bat_priv->mcast.want_all_rtr6_list,
				 mcast_want_all_rtr6_node) अणु
		newskb = skb_copy(skb, GFP_ATOMIC);
		अगर (!newskb) अणु
			ret = NET_XMIT_DROP;
			अवरोध;
		पूर्ण

		batadv_mcast_क्रमw_send_orig(bat_priv, newskb, vid, orig_node);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/**
 * batadv_mcast_क्रमw_want_rtr() - क्रमward packet to nodes in a want-all-rtr list
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the multicast packet to transmit
 * @vid: the vlan identअगरier
 *
 * Sends copies of a frame with multicast destination to any node with a
 * BATADV_MCAST_WANT_NO_RTR4 or BATADV_MCAST_WANT_NO_RTR6 flag unset. A
 * transmission is perक्रमmed via a baपंचांगan-adv unicast packet क्रम each such
 * destination node.
 *
 * Return: NET_XMIT_DROP on memory allocation failure or अगर the protocol family
 * is neither IPv4 nor IPv6. NET_XMIT_SUCCESS otherwise.
 */
अटल पूर्णांक
batadv_mcast_क्रमw_want_rtr(काष्ठा batadv_priv *bat_priv,
			   काष्ठा sk_buff *skb, अचिन्हित लघु vid)
अणु
	चयन (ntohs(eth_hdr(skb)->h_proto)) अणु
	हाल ETH_P_IP:
		वापस batadv_mcast_क्रमw_want_all_rtr4(bat_priv, skb, vid);
	हाल ETH_P_IPV6:
		वापस batadv_mcast_क्रमw_want_all_rtr6(bat_priv, skb, vid);
	शेष:
		/* we shouldn't be here... */
		वापस NET_XMIT_DROP;
	पूर्ण
पूर्ण

/**
 * batadv_mcast_क्रमw_send() - send packet to any detected multicast recipient
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the multicast packet to transmit
 * @vid: the vlan identअगरier
 *
 * Sends copies of a frame with multicast destination to any node that संकेतed
 * पूर्णांकerest in it, that is either via the translation table or the according
 * want-all flags. A transmission is perक्रमmed via a baपंचांगan-adv unicast packet
 * क्रम each such destination node.
 *
 * The given skb is consumed/मुक्तd.
 *
 * Return: NET_XMIT_DROP on memory allocation failure or अगर the protocol family
 * is neither IPv4 nor IPv6. NET_XMIT_SUCCESS otherwise.
 */
पूर्णांक batadv_mcast_क्रमw_send(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb,
			   अचिन्हित लघु vid)
अणु
	पूर्णांक ret;

	ret = batadv_mcast_क्रमw_tt(bat_priv, skb, vid);
	अगर (ret != NET_XMIT_SUCCESS) अणु
		kमुक्त_skb(skb);
		वापस ret;
	पूर्ण

	ret = batadv_mcast_क्रमw_want_all(bat_priv, skb, vid);
	अगर (ret != NET_XMIT_SUCCESS) अणु
		kमुक्त_skb(skb);
		वापस ret;
	पूर्ण

	ret = batadv_mcast_क्रमw_want_rtr(bat_priv, skb, vid);
	अगर (ret != NET_XMIT_SUCCESS) अणु
		kमुक्त_skb(skb);
		वापस ret;
	पूर्ण

	consume_skb(skb);
	वापस ret;
पूर्ण

/**
 * batadv_mcast_want_unsnoop_update() - update unsnoop counter and list
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig: the orig_node which multicast state might have changed of
 * @mcast_flags: flags indicating the new multicast state
 *
 * If the BATADV_MCAST_WANT_ALL_UNSNOOPABLES flag of this originator,
 * orig, has toggled then this method updates the counter and the list
 * accordingly.
 *
 * Caller needs to hold orig->mcast_handler_lock.
 */
अटल व्योम batadv_mcast_want_unsnoop_update(काष्ठा batadv_priv *bat_priv,
					     काष्ठा batadv_orig_node *orig,
					     u8 mcast_flags)
अणु
	काष्ठा hlist_node *node = &orig->mcast_want_all_unsnoopables_node;
	काष्ठा hlist_head *head = &bat_priv->mcast.want_all_unsnoopables_list;

	lockdep_निश्चित_held(&orig->mcast_handler_lock);

	/* चयनed from flag unset to set */
	अगर (mcast_flags & BATADV_MCAST_WANT_ALL_UNSNOOPABLES &&
	    !(orig->mcast_flags & BATADV_MCAST_WANT_ALL_UNSNOOPABLES)) अणु
		atomic_inc(&bat_priv->mcast.num_want_all_unsnoopables);

		spin_lock_bh(&bat_priv->mcast.want_lists_lock);
		/* flag checks above + mcast_handler_lock prevents this */
		WARN_ON(!hlist_unhashed(node));

		hlist_add_head_rcu(node, head);
		spin_unlock_bh(&bat_priv->mcast.want_lists_lock);
	/* चयनed from flag set to unset */
	पूर्ण अन्यथा अगर (!(mcast_flags & BATADV_MCAST_WANT_ALL_UNSNOOPABLES) &&
		   orig->mcast_flags & BATADV_MCAST_WANT_ALL_UNSNOOPABLES) अणु
		atomic_dec(&bat_priv->mcast.num_want_all_unsnoopables);

		spin_lock_bh(&bat_priv->mcast.want_lists_lock);
		/* flag checks above + mcast_handler_lock prevents this */
		WARN_ON(hlist_unhashed(node));

		hlist_del_init_rcu(node);
		spin_unlock_bh(&bat_priv->mcast.want_lists_lock);
	पूर्ण
पूर्ण

/**
 * batadv_mcast_want_ipv4_update() - update want-all-ipv4 counter and list
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig: the orig_node which multicast state might have changed of
 * @mcast_flags: flags indicating the new multicast state
 *
 * If the BATADV_MCAST_WANT_ALL_IPV4 flag of this originator, orig, has
 * toggled then this method updates the counter and the list accordingly.
 *
 * Caller needs to hold orig->mcast_handler_lock.
 */
अटल व्योम batadv_mcast_want_ipv4_update(काष्ठा batadv_priv *bat_priv,
					  काष्ठा batadv_orig_node *orig,
					  u8 mcast_flags)
अणु
	काष्ठा hlist_node *node = &orig->mcast_want_all_ipv4_node;
	काष्ठा hlist_head *head = &bat_priv->mcast.want_all_ipv4_list;

	lockdep_निश्चित_held(&orig->mcast_handler_lock);

	/* चयनed from flag unset to set */
	अगर (mcast_flags & BATADV_MCAST_WANT_ALL_IPV4 &&
	    !(orig->mcast_flags & BATADV_MCAST_WANT_ALL_IPV4)) अणु
		atomic_inc(&bat_priv->mcast.num_want_all_ipv4);

		spin_lock_bh(&bat_priv->mcast.want_lists_lock);
		/* flag checks above + mcast_handler_lock prevents this */
		WARN_ON(!hlist_unhashed(node));

		hlist_add_head_rcu(node, head);
		spin_unlock_bh(&bat_priv->mcast.want_lists_lock);
	/* चयनed from flag set to unset */
	पूर्ण अन्यथा अगर (!(mcast_flags & BATADV_MCAST_WANT_ALL_IPV4) &&
		   orig->mcast_flags & BATADV_MCAST_WANT_ALL_IPV4) अणु
		atomic_dec(&bat_priv->mcast.num_want_all_ipv4);

		spin_lock_bh(&bat_priv->mcast.want_lists_lock);
		/* flag checks above + mcast_handler_lock prevents this */
		WARN_ON(hlist_unhashed(node));

		hlist_del_init_rcu(node);
		spin_unlock_bh(&bat_priv->mcast.want_lists_lock);
	पूर्ण
पूर्ण

/**
 * batadv_mcast_want_ipv6_update() - update want-all-ipv6 counter and list
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig: the orig_node which multicast state might have changed of
 * @mcast_flags: flags indicating the new multicast state
 *
 * If the BATADV_MCAST_WANT_ALL_IPV6 flag of this originator, orig, has
 * toggled then this method updates the counter and the list accordingly.
 *
 * Caller needs to hold orig->mcast_handler_lock.
 */
अटल व्योम batadv_mcast_want_ipv6_update(काष्ठा batadv_priv *bat_priv,
					  काष्ठा batadv_orig_node *orig,
					  u8 mcast_flags)
अणु
	काष्ठा hlist_node *node = &orig->mcast_want_all_ipv6_node;
	काष्ठा hlist_head *head = &bat_priv->mcast.want_all_ipv6_list;

	lockdep_निश्चित_held(&orig->mcast_handler_lock);

	/* चयनed from flag unset to set */
	अगर (mcast_flags & BATADV_MCAST_WANT_ALL_IPV6 &&
	    !(orig->mcast_flags & BATADV_MCAST_WANT_ALL_IPV6)) अणु
		atomic_inc(&bat_priv->mcast.num_want_all_ipv6);

		spin_lock_bh(&bat_priv->mcast.want_lists_lock);
		/* flag checks above + mcast_handler_lock prevents this */
		WARN_ON(!hlist_unhashed(node));

		hlist_add_head_rcu(node, head);
		spin_unlock_bh(&bat_priv->mcast.want_lists_lock);
	/* चयनed from flag set to unset */
	पूर्ण अन्यथा अगर (!(mcast_flags & BATADV_MCAST_WANT_ALL_IPV6) &&
		   orig->mcast_flags & BATADV_MCAST_WANT_ALL_IPV6) अणु
		atomic_dec(&bat_priv->mcast.num_want_all_ipv6);

		spin_lock_bh(&bat_priv->mcast.want_lists_lock);
		/* flag checks above + mcast_handler_lock prevents this */
		WARN_ON(hlist_unhashed(node));

		hlist_del_init_rcu(node);
		spin_unlock_bh(&bat_priv->mcast.want_lists_lock);
	पूर्ण
पूर्ण

/**
 * batadv_mcast_want_rtr4_update() - update want-all-rtr4 counter and list
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig: the orig_node which multicast state might have changed of
 * @mcast_flags: flags indicating the new multicast state
 *
 * If the BATADV_MCAST_WANT_NO_RTR4 flag of this originator, orig, has
 * toggled then this method updates the counter and the list accordingly.
 *
 * Caller needs to hold orig->mcast_handler_lock.
 */
अटल व्योम batadv_mcast_want_rtr4_update(काष्ठा batadv_priv *bat_priv,
					  काष्ठा batadv_orig_node *orig,
					  u8 mcast_flags)
अणु
	काष्ठा hlist_node *node = &orig->mcast_want_all_rtr4_node;
	काष्ठा hlist_head *head = &bat_priv->mcast.want_all_rtr4_list;

	lockdep_निश्चित_held(&orig->mcast_handler_lock);

	/* चयनed from flag set to unset */
	अगर (!(mcast_flags & BATADV_MCAST_WANT_NO_RTR4) &&
	    orig->mcast_flags & BATADV_MCAST_WANT_NO_RTR4) अणु
		atomic_inc(&bat_priv->mcast.num_want_all_rtr4);

		spin_lock_bh(&bat_priv->mcast.want_lists_lock);
		/* flag checks above + mcast_handler_lock prevents this */
		WARN_ON(!hlist_unhashed(node));

		hlist_add_head_rcu(node, head);
		spin_unlock_bh(&bat_priv->mcast.want_lists_lock);
	/* चयनed from flag unset to set */
	पूर्ण अन्यथा अगर (mcast_flags & BATADV_MCAST_WANT_NO_RTR4 &&
		   !(orig->mcast_flags & BATADV_MCAST_WANT_NO_RTR4)) अणु
		atomic_dec(&bat_priv->mcast.num_want_all_rtr4);

		spin_lock_bh(&bat_priv->mcast.want_lists_lock);
		/* flag checks above + mcast_handler_lock prevents this */
		WARN_ON(hlist_unhashed(node));

		hlist_del_init_rcu(node);
		spin_unlock_bh(&bat_priv->mcast.want_lists_lock);
	पूर्ण
पूर्ण

/**
 * batadv_mcast_want_rtr6_update() - update want-all-rtr6 counter and list
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig: the orig_node which multicast state might have changed of
 * @mcast_flags: flags indicating the new multicast state
 *
 * If the BATADV_MCAST_WANT_NO_RTR6 flag of this originator, orig, has
 * toggled then this method updates the counter and the list accordingly.
 *
 * Caller needs to hold orig->mcast_handler_lock.
 */
अटल व्योम batadv_mcast_want_rtr6_update(काष्ठा batadv_priv *bat_priv,
					  काष्ठा batadv_orig_node *orig,
					  u8 mcast_flags)
अणु
	काष्ठा hlist_node *node = &orig->mcast_want_all_rtr6_node;
	काष्ठा hlist_head *head = &bat_priv->mcast.want_all_rtr6_list;

	lockdep_निश्चित_held(&orig->mcast_handler_lock);

	/* चयनed from flag set to unset */
	अगर (!(mcast_flags & BATADV_MCAST_WANT_NO_RTR6) &&
	    orig->mcast_flags & BATADV_MCAST_WANT_NO_RTR6) अणु
		atomic_inc(&bat_priv->mcast.num_want_all_rtr6);

		spin_lock_bh(&bat_priv->mcast.want_lists_lock);
		/* flag checks above + mcast_handler_lock prevents this */
		WARN_ON(!hlist_unhashed(node));

		hlist_add_head_rcu(node, head);
		spin_unlock_bh(&bat_priv->mcast.want_lists_lock);
	/* चयनed from flag unset to set */
	पूर्ण अन्यथा अगर (mcast_flags & BATADV_MCAST_WANT_NO_RTR6 &&
		   !(orig->mcast_flags & BATADV_MCAST_WANT_NO_RTR6)) अणु
		atomic_dec(&bat_priv->mcast.num_want_all_rtr6);

		spin_lock_bh(&bat_priv->mcast.want_lists_lock);
		/* flag checks above + mcast_handler_lock prevents this */
		WARN_ON(hlist_unhashed(node));

		hlist_del_init_rcu(node);
		spin_unlock_bh(&bat_priv->mcast.want_lists_lock);
	पूर्ण
पूर्ण

/**
 * batadv_mcast_tvlv_flags_get() - get multicast flags from an OGM TVLV
 * @enabled: whether the originator has multicast TVLV support enabled
 * @tvlv_value: tvlv buffer containing the multicast flags
 * @tvlv_value_len: tvlv buffer length
 *
 * Return: multicast flags क्रम the given tvlv buffer
 */
अटल u8
batadv_mcast_tvlv_flags_get(bool enabled, व्योम *tvlv_value, u16 tvlv_value_len)
अणु
	u8 mcast_flags = BATADV_NO_FLAGS;

	अगर (enabled && tvlv_value && tvlv_value_len >= माप(mcast_flags))
		mcast_flags = *(u8 *)tvlv_value;

	अगर (!enabled) अणु
		mcast_flags |= BATADV_MCAST_WANT_ALL_IPV4;
		mcast_flags |= BATADV_MCAST_WANT_ALL_IPV6;
	पूर्ण

	/* हटाओ redundant flags to aव्योम sending duplicate packets later */
	अगर (mcast_flags & BATADV_MCAST_WANT_ALL_IPV4)
		mcast_flags |= BATADV_MCAST_WANT_NO_RTR4;

	अगर (mcast_flags & BATADV_MCAST_WANT_ALL_IPV6)
		mcast_flags |= BATADV_MCAST_WANT_NO_RTR6;

	वापस mcast_flags;
पूर्ण

/**
 * batadv_mcast_tvlv_ogm_handler() - process incoming multicast tvlv container
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig: the orig_node of the ogm
 * @flags: flags indicating the tvlv state (see batadv_tvlv_handler_flags)
 * @tvlv_value: tvlv buffer containing the multicast data
 * @tvlv_value_len: tvlv buffer length
 */
अटल व्योम batadv_mcast_tvlv_ogm_handler(काष्ठा batadv_priv *bat_priv,
					  काष्ठा batadv_orig_node *orig,
					  u8 flags,
					  व्योम *tvlv_value,
					  u16 tvlv_value_len)
अणु
	bool orig_mcast_enabled = !(flags & BATADV_TVLV_HANDLER_OGM_CIFNOTFND);
	u8 mcast_flags;

	mcast_flags = batadv_mcast_tvlv_flags_get(orig_mcast_enabled,
						  tvlv_value, tvlv_value_len);

	spin_lock_bh(&orig->mcast_handler_lock);

	अगर (orig_mcast_enabled &&
	    !test_bit(BATADV_ORIG_CAPA_HAS_MCAST, &orig->capabilities)) अणु
		set_bit(BATADV_ORIG_CAPA_HAS_MCAST, &orig->capabilities);
	पूर्ण अन्यथा अगर (!orig_mcast_enabled &&
		   test_bit(BATADV_ORIG_CAPA_HAS_MCAST, &orig->capabilities)) अणु
		clear_bit(BATADV_ORIG_CAPA_HAS_MCAST, &orig->capabilities);
	पूर्ण

	set_bit(BATADV_ORIG_CAPA_HAS_MCAST, &orig->capa_initialized);

	batadv_mcast_want_unsnoop_update(bat_priv, orig, mcast_flags);
	batadv_mcast_want_ipv4_update(bat_priv, orig, mcast_flags);
	batadv_mcast_want_ipv6_update(bat_priv, orig, mcast_flags);
	batadv_mcast_want_rtr4_update(bat_priv, orig, mcast_flags);
	batadv_mcast_want_rtr6_update(bat_priv, orig, mcast_flags);

	orig->mcast_flags = mcast_flags;
	spin_unlock_bh(&orig->mcast_handler_lock);
पूर्ण

/**
 * batadv_mcast_init() - initialize the multicast optimizations काष्ठाures
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
व्योम batadv_mcast_init(काष्ठा batadv_priv *bat_priv)
अणु
	batadv_tvlv_handler_रेजिस्टर(bat_priv, batadv_mcast_tvlv_ogm_handler,
				     शून्य, BATADV_TVLV_MCAST, 2,
				     BATADV_TVLV_HANDLER_OGM_CIFNOTFND);

	INIT_DELAYED_WORK(&bat_priv->mcast.work, batadv_mcast_mla_update);
	batadv_mcast_start_समयr(bat_priv);
पूर्ण

/**
 * batadv_mcast_mesh_info_put() - put multicast info पूर्णांकo a netlink message
 * @msg: buffer क्रम the message
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: 0 or error code.
 */
पूर्णांक batadv_mcast_mesh_info_put(काष्ठा sk_buff *msg,
			       काष्ठा batadv_priv *bat_priv)
अणु
	u32 flags = bat_priv->mcast.mla_flags.tvlv_flags;
	u32 flags_priv = BATADV_NO_FLAGS;

	अगर (bat_priv->mcast.mla_flags.bridged) अणु
		flags_priv |= BATADV_MCAST_FLAGS_BRIDGED;

		अगर (bat_priv->mcast.mla_flags.querier_ipv4.exists)
			flags_priv |= BATADV_MCAST_FLAGS_QUERIER_IPV4_EXISTS;
		अगर (bat_priv->mcast.mla_flags.querier_ipv6.exists)
			flags_priv |= BATADV_MCAST_FLAGS_QUERIER_IPV6_EXISTS;
		अगर (bat_priv->mcast.mla_flags.querier_ipv4.shaकरोwing)
			flags_priv |= BATADV_MCAST_FLAGS_QUERIER_IPV4_SHADOWING;
		अगर (bat_priv->mcast.mla_flags.querier_ipv6.shaकरोwing)
			flags_priv |= BATADV_MCAST_FLAGS_QUERIER_IPV6_SHADOWING;
	पूर्ण

	अगर (nla_put_u32(msg, BATADV_ATTR_MCAST_FLAGS, flags) ||
	    nla_put_u32(msg, BATADV_ATTR_MCAST_FLAGS_PRIV, flags_priv))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

/**
 * batadv_mcast_flags_dump_entry() - dump one entry of the multicast flags table
 *  to a netlink socket
 * @msg: buffer क्रम the message
 * @portid: netlink port
 * @cb: Control block containing additional options
 * @orig_node: originator to dump the multicast flags of
 *
 * Return: 0 or error code.
 */
अटल पूर्णांक
batadv_mcast_flags_dump_entry(काष्ठा sk_buff *msg, u32 portid,
			      काष्ठा netlink_callback *cb,
			      काष्ठा batadv_orig_node *orig_node)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(msg, portid, cb->nlh->nlmsg_seq,
			  &batadv_netlink_family, NLM_F_MULTI,
			  BATADV_CMD_GET_MCAST_FLAGS);
	अगर (!hdr)
		वापस -ENOBUFS;

	genl_dump_check_consistent(cb, hdr);

	अगर (nla_put(msg, BATADV_ATTR_ORIG_ADDRESS, ETH_ALEN,
		    orig_node->orig)) अणु
		genlmsg_cancel(msg, hdr);
		वापस -EMSGSIZE;
	पूर्ण

	अगर (test_bit(BATADV_ORIG_CAPA_HAS_MCAST,
		     &orig_node->capabilities)) अणु
		अगर (nla_put_u32(msg, BATADV_ATTR_MCAST_FLAGS,
				orig_node->mcast_flags)) अणु
			genlmsg_cancel(msg, hdr);
			वापस -EMSGSIZE;
		पूर्ण
	पूर्ण

	genlmsg_end(msg, hdr);
	वापस 0;
पूर्ण

/**
 * batadv_mcast_flags_dump_bucket() - dump one bucket of the multicast flags
 *  table to a netlink socket
 * @msg: buffer क्रम the message
 * @portid: netlink port
 * @cb: Control block containing additional options
 * @hash: hash to dump
 * @bucket: bucket index to dump
 * @idx_skip: How many entries to skip
 *
 * Return: 0 or error code.
 */
अटल पूर्णांक
batadv_mcast_flags_dump_bucket(काष्ठा sk_buff *msg, u32 portid,
			       काष्ठा netlink_callback *cb,
			       काष्ठा batadv_hashtable *hash,
			       अचिन्हित पूर्णांक bucket, दीर्घ *idx_skip)
अणु
	काष्ठा batadv_orig_node *orig_node;
	दीर्घ idx = 0;

	spin_lock_bh(&hash->list_locks[bucket]);
	cb->seq = atomic_पढ़ो(&hash->generation) << 1 | 1;

	hlist_क्रम_each_entry(orig_node, &hash->table[bucket], hash_entry) अणु
		अगर (!test_bit(BATADV_ORIG_CAPA_HAS_MCAST,
			      &orig_node->capa_initialized))
			जारी;

		अगर (idx < *idx_skip)
			जाओ skip;

		अगर (batadv_mcast_flags_dump_entry(msg, portid, cb, orig_node)) अणु
			spin_unlock_bh(&hash->list_locks[bucket]);
			*idx_skip = idx;

			वापस -EMSGSIZE;
		पूर्ण

skip:
		idx++;
	पूर्ण
	spin_unlock_bh(&hash->list_locks[bucket]);

	वापस 0;
पूर्ण

/**
 * __batadv_mcast_flags_dump() - dump multicast flags table to a netlink socket
 * @msg: buffer क्रम the message
 * @portid: netlink port
 * @cb: Control block containing additional options
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @bucket: current bucket to dump
 * @idx: index in current bucket to the next entry to dump
 *
 * Return: 0 or error code.
 */
अटल पूर्णांक
__batadv_mcast_flags_dump(काष्ठा sk_buff *msg, u32 portid,
			  काष्ठा netlink_callback *cb,
			  काष्ठा batadv_priv *bat_priv, दीर्घ *bucket, दीर्घ *idx)
अणु
	काष्ठा batadv_hashtable *hash = bat_priv->orig_hash;
	दीर्घ bucket_पंचांगp = *bucket;
	दीर्घ idx_पंचांगp = *idx;

	जबतक (bucket_पंचांगp < hash->size) अणु
		अगर (batadv_mcast_flags_dump_bucket(msg, portid, cb, hash,
						   bucket_पंचांगp, &idx_पंचांगp))
			अवरोध;

		bucket_पंचांगp++;
		idx_पंचांगp = 0;
	पूर्ण

	*bucket = bucket_पंचांगp;
	*idx = idx_पंचांगp;

	वापस msg->len;
पूर्ण

/**
 * batadv_mcast_netlink_get_primary() - get primary पूर्णांकerface from netlink
 *  callback
 * @cb: netlink callback काष्ठाure
 * @primary_अगर: the primary पूर्णांकerface poपूर्णांकer to वापस the result in
 *
 * Return: 0 or error code.
 */
अटल पूर्णांक
batadv_mcast_netlink_get_primary(काष्ठा netlink_callback *cb,
				 काष्ठा batadv_hard_अगरace **primary_अगर)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace = शून्य;
	काष्ठा net *net = sock_net(cb->skb->sk);
	काष्ठा net_device *soft_अगरace;
	काष्ठा batadv_priv *bat_priv;
	पूर्णांक अगरindex;
	पूर्णांक ret = 0;

	अगरindex = batadv_netlink_get_अगरindex(cb->nlh, BATADV_ATTR_MESH_IFINDEX);
	अगर (!अगरindex)
		वापस -EINVAL;

	soft_अगरace = dev_get_by_index(net, अगरindex);
	अगर (!soft_अगरace || !batadv_softअगर_is_valid(soft_अगरace)) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	bat_priv = netdev_priv(soft_अगरace);

	hard_अगरace = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!hard_अगरace || hard_अगरace->अगर_status != BATADV_IF_ACTIVE) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

out:
	अगर (soft_अगरace)
		dev_put(soft_अगरace);

	अगर (!ret && primary_अगर)
		*primary_अगर = hard_अगरace;
	अन्यथा अगर (hard_अगरace)
		batadv_hardअगर_put(hard_अगरace);

	वापस ret;
पूर्ण

/**
 * batadv_mcast_flags_dump() - dump multicast flags table to a netlink socket
 * @msg: buffer क्रम the message
 * @cb: callback काष्ठाure containing arguments
 *
 * Return: message length.
 */
पूर्णांक batadv_mcast_flags_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb)
अणु
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	पूर्णांक portid = NETLINK_CB(cb->skb).portid;
	काष्ठा batadv_priv *bat_priv;
	दीर्घ *bucket = &cb->args[0];
	दीर्घ *idx = &cb->args[1];
	पूर्णांक ret;

	ret = batadv_mcast_netlink_get_primary(cb, &primary_अगर);
	अगर (ret)
		वापस ret;

	bat_priv = netdev_priv(primary_अगर->soft_अगरace);
	ret = __batadv_mcast_flags_dump(msg, portid, cb, bat_priv, bucket, idx);

	batadv_hardअगर_put(primary_अगर);
	वापस ret;
पूर्ण

/**
 * batadv_mcast_मुक्त() - मुक्त the multicast optimizations काष्ठाures
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
व्योम batadv_mcast_मुक्त(काष्ठा batadv_priv *bat_priv)
अणु
	cancel_delayed_work_sync(&bat_priv->mcast.work);

	batadv_tvlv_container_unरेजिस्टर(bat_priv, BATADV_TVLV_MCAST, 2);
	batadv_tvlv_handler_unरेजिस्टर(bat_priv, BATADV_TVLV_MCAST, 2);

	/* safely calling outside of worker, as worker was canceled above */
	batadv_mcast_mla_tt_retract(bat_priv, शून्य);
पूर्ण

/**
 * batadv_mcast_purge_orig() - reset originator global mcast state modअगरications
 * @orig: the originator which is going to get purged
 */
व्योम batadv_mcast_purge_orig(काष्ठा batadv_orig_node *orig)
अणु
	काष्ठा batadv_priv *bat_priv = orig->bat_priv;

	spin_lock_bh(&orig->mcast_handler_lock);

	batadv_mcast_want_unsnoop_update(bat_priv, orig, BATADV_NO_FLAGS);
	batadv_mcast_want_ipv4_update(bat_priv, orig, BATADV_NO_FLAGS);
	batadv_mcast_want_ipv6_update(bat_priv, orig, BATADV_NO_FLAGS);
	batadv_mcast_want_rtr4_update(bat_priv, orig,
				      BATADV_MCAST_WANT_NO_RTR4);
	batadv_mcast_want_rtr6_update(bat_priv, orig,
				      BATADV_MCAST_WANT_NO_RTR6);

	spin_unlock_bh(&orig->mcast_handler_lock);
पूर्ण
