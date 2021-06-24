<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Copyright (c) 2014 Mahesh Bandewar <maheshb@google.com>
 */

#समावेश <linux/ethtool.h>

#समावेश "ipvlan.h"

अटल पूर्णांक ipvlan_set_port_mode(काष्ठा ipvl_port *port, u16 nval,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ipvl_dev *ipvlan;
	अचिन्हित पूर्णांक flags;
	पूर्णांक err;

	ASSERT_RTNL();
	अगर (port->mode != nval) अणु
		list_क्रम_each_entry(ipvlan, &port->ipvlans, pnode) अणु
			flags = ipvlan->dev->flags;
			अगर (nval == IPVLAN_MODE_L3 || nval == IPVLAN_MODE_L3S) अणु
				err = dev_change_flags(ipvlan->dev,
						       flags | IFF_NOARP,
						       extack);
			पूर्ण अन्यथा अणु
				err = dev_change_flags(ipvlan->dev,
						       flags & ~IFF_NOARP,
						       extack);
			पूर्ण
			अगर (unlikely(err))
				जाओ fail;
		पूर्ण
		अगर (nval == IPVLAN_MODE_L3S) अणु
			/* New mode is L3S */
			err = ipvlan_l3s_रेजिस्टर(port);
			अगर (err)
				जाओ fail;
		पूर्ण अन्यथा अगर (port->mode == IPVLAN_MODE_L3S) अणु
			/* Old mode was L3S */
			ipvlan_l3s_unरेजिस्टर(port);
		पूर्ण
		port->mode = nval;
	पूर्ण
	वापस 0;

fail:
	/* Unकरो the flags changes that have been करोne so far. */
	list_क्रम_each_entry_जारी_reverse(ipvlan, &port->ipvlans, pnode) अणु
		flags = ipvlan->dev->flags;
		अगर (port->mode == IPVLAN_MODE_L3 ||
		    port->mode == IPVLAN_MODE_L3S)
			dev_change_flags(ipvlan->dev, flags | IFF_NOARP,
					 शून्य);
		अन्यथा
			dev_change_flags(ipvlan->dev, flags & ~IFF_NOARP,
					 शून्य);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ipvlan_port_create(काष्ठा net_device *dev)
अणु
	काष्ठा ipvl_port *port;
	पूर्णांक err, idx;

	port = kzalloc(माप(काष्ठा ipvl_port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;

	ग_लिखो_pnet(&port->pnet, dev_net(dev));
	port->dev = dev;
	port->mode = IPVLAN_MODE_L3;
	INIT_LIST_HEAD(&port->ipvlans);
	क्रम (idx = 0; idx < IPVLAN_HASH_SIZE; idx++)
		INIT_HLIST_HEAD(&port->hlhead[idx]);

	skb_queue_head_init(&port->backlog);
	INIT_WORK(&port->wq, ipvlan_process_multicast);
	ida_init(&port->ida);
	port->dev_id_start = 1;

	err = netdev_rx_handler_रेजिस्टर(dev, ipvlan_handle_frame, port);
	अगर (err)
		जाओ err;

	वापस 0;

err:
	kमुक्त(port);
	वापस err;
पूर्ण

अटल व्योम ipvlan_port_destroy(काष्ठा net_device *dev)
अणु
	काष्ठा ipvl_port *port = ipvlan_port_get_rtnl(dev);
	काष्ठा sk_buff *skb;

	अगर (port->mode == IPVLAN_MODE_L3S)
		ipvlan_l3s_unरेजिस्टर(port);
	netdev_rx_handler_unरेजिस्टर(dev);
	cancel_work_sync(&port->wq);
	जबतक ((skb = __skb_dequeue(&port->backlog)) != शून्य) अणु
		अगर (skb->dev)
			dev_put(skb->dev);
		kमुक्त_skb(skb);
	पूर्ण
	ida_destroy(&port->ida);
	kमुक्त(port);
पूर्ण

#घोषणा IPVLAN_ALWAYS_ON_OFLOADS \
	(NETIF_F_SG | NETIF_F_HW_CSUM | \
	 NETIF_F_GSO_ROBUST | NETIF_F_GSO_SOFTWARE | NETIF_F_GSO_ENCAP_ALL)

#घोषणा IPVLAN_ALWAYS_ON \
	(IPVLAN_ALWAYS_ON_OFLOADS | NETIF_F_LLTX | NETIF_F_VLAN_CHALLENGED)

#घोषणा IPVLAN_FEATURES \
	(NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_HIGHDMA | NETIF_F_FRAGLIST | \
	 NETIF_F_GSO | NETIF_F_ALL_TSO | NETIF_F_GSO_ROBUST | \
	 NETIF_F_GRO | NETIF_F_RXCSUM | \
	 NETIF_F_HW_VLAN_CTAG_FILTER | NETIF_F_HW_VLAN_STAG_FILTER)

	/* NETIF_F_GSO_ENCAP_ALL NETIF_F_GSO_SOFTWARE Newly added */

#घोषणा IPVLAN_STATE_MASK \
	((1<<__LINK_STATE_NOCARRIER) | (1<<__LINK_STATE_DORMANT))

अटल पूर्णांक ipvlan_init(काष्ठा net_device *dev)
अणु
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);
	काष्ठा net_device *phy_dev = ipvlan->phy_dev;
	काष्ठा ipvl_port *port;
	पूर्णांक err;

	dev->state = (dev->state & ~IPVLAN_STATE_MASK) |
		     (phy_dev->state & IPVLAN_STATE_MASK);
	dev->features = phy_dev->features & IPVLAN_FEATURES;
	dev->features |= IPVLAN_ALWAYS_ON;
	dev->vlan_features = phy_dev->vlan_features & IPVLAN_FEATURES;
	dev->vlan_features |= IPVLAN_ALWAYS_ON_OFLOADS;
	dev->hw_enc_features |= dev->features;
	dev->gso_max_size = phy_dev->gso_max_size;
	dev->gso_max_segs = phy_dev->gso_max_segs;
	dev->hard_header_len = phy_dev->hard_header_len;

	netdev_lockdep_set_classes(dev);

	ipvlan->pcpu_stats = netdev_alloc_pcpu_stats(काष्ठा ipvl_pcpu_stats);
	अगर (!ipvlan->pcpu_stats)
		वापस -ENOMEM;

	अगर (!netअगर_is_ipvlan_port(phy_dev)) अणु
		err = ipvlan_port_create(phy_dev);
		अगर (err < 0) अणु
			मुक्त_percpu(ipvlan->pcpu_stats);
			वापस err;
		पूर्ण
	पूर्ण
	port = ipvlan_port_get_rtnl(phy_dev);
	port->count += 1;
	वापस 0;
पूर्ण

अटल व्योम ipvlan_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);
	काष्ठा net_device *phy_dev = ipvlan->phy_dev;
	काष्ठा ipvl_port *port;

	मुक्त_percpu(ipvlan->pcpu_stats);

	port = ipvlan_port_get_rtnl(phy_dev);
	port->count -= 1;
	अगर (!port->count)
		ipvlan_port_destroy(port->dev);
पूर्ण

अटल पूर्णांक ipvlan_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);
	काष्ठा ipvl_addr *addr;

	अगर (ipvlan->port->mode == IPVLAN_MODE_L3 ||
	    ipvlan->port->mode == IPVLAN_MODE_L3S)
		dev->flags |= IFF_NOARP;
	अन्यथा
		dev->flags &= ~IFF_NOARP;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(addr, &ipvlan->addrs, anode)
		ipvlan_ht_addr_add(ipvlan, addr);
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक ipvlan_stop(काष्ठा net_device *dev)
अणु
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);
	काष्ठा net_device *phy_dev = ipvlan->phy_dev;
	काष्ठा ipvl_addr *addr;

	dev_uc_unsync(phy_dev, dev);
	dev_mc_unsync(phy_dev, dev);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(addr, &ipvlan->addrs, anode)
		ipvlan_ht_addr_del(addr);
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल netdev_tx_t ipvlan_start_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);
	पूर्णांक skblen = skb->len;
	पूर्णांक ret;

	ret = ipvlan_queue_xmit(skb, dev);
	अगर (likely(ret == NET_XMIT_SUCCESS || ret == NET_XMIT_CN)) अणु
		काष्ठा ipvl_pcpu_stats *pcptr;

		pcptr = this_cpu_ptr(ipvlan->pcpu_stats);

		u64_stats_update_begin(&pcptr->syncp);
		pcptr->tx_pkts++;
		pcptr->tx_bytes += skblen;
		u64_stats_update_end(&pcptr->syncp);
	पूर्ण अन्यथा अणु
		this_cpu_inc(ipvlan->pcpu_stats->tx_drps);
	पूर्ण
	वापस ret;
पूर्ण

अटल netdev_features_t ipvlan_fix_features(काष्ठा net_device *dev,
					     netdev_features_t features)
अणु
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);

	features |= NETIF_F_ALL_FOR_ALL;
	features &= (ipvlan->sfeatures | ~IPVLAN_FEATURES);
	features = netdev_increment_features(ipvlan->phy_dev->features,
					     features, features);
	features |= IPVLAN_ALWAYS_ON;
	features &= (IPVLAN_FEATURES | IPVLAN_ALWAYS_ON);

	वापस features;
पूर्ण

अटल व्योम ipvlan_change_rx_flags(काष्ठा net_device *dev, पूर्णांक change)
अणु
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);
	काष्ठा net_device *phy_dev = ipvlan->phy_dev;

	अगर (change & IFF_ALLMULTI)
		dev_set_allmulti(phy_dev, dev->flags & IFF_ALLMULTI? 1 : -1);
पूर्ण

अटल व्योम ipvlan_set_multicast_mac_filter(काष्ठा net_device *dev)
अणु
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);

	अगर (dev->flags & (IFF_PROMISC | IFF_ALLMULTI)) अणु
		biपंचांगap_fill(ipvlan->mac_filters, IPVLAN_MAC_FILTER_SIZE);
	पूर्ण अन्यथा अणु
		काष्ठा netdev_hw_addr *ha;
		DECLARE_BITMAP(mc_filters, IPVLAN_MAC_FILTER_SIZE);

		biपंचांगap_zero(mc_filters, IPVLAN_MAC_FILTER_SIZE);
		netdev_क्रम_each_mc_addr(ha, dev)
			__set_bit(ipvlan_mac_hash(ha->addr), mc_filters);

		/* Turn-on broadcast bit irrespective of address family,
		 * since broadcast is deferred to a work-queue, hence no
		 * impact on fast-path processing.
		 */
		__set_bit(ipvlan_mac_hash(dev->broadcast), mc_filters);

		biपंचांगap_copy(ipvlan->mac_filters, mc_filters,
			    IPVLAN_MAC_FILTER_SIZE);
	पूर्ण
	dev_uc_sync(ipvlan->phy_dev, dev);
	dev_mc_sync(ipvlan->phy_dev, dev);
पूर्ण

अटल व्योम ipvlan_get_stats64(काष्ठा net_device *dev,
			       काष्ठा rtnl_link_stats64 *s)
अणु
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);

	अगर (ipvlan->pcpu_stats) अणु
		काष्ठा ipvl_pcpu_stats *pcptr;
		u64 rx_pkts, rx_bytes, rx_mcast, tx_pkts, tx_bytes;
		u32 rx_errs = 0, tx_drps = 0;
		u32 strt;
		पूर्णांक idx;

		क्रम_each_possible_cpu(idx) अणु
			pcptr = per_cpu_ptr(ipvlan->pcpu_stats, idx);
			करो अणु
				strt= u64_stats_fetch_begin_irq(&pcptr->syncp);
				rx_pkts = pcptr->rx_pkts;
				rx_bytes = pcptr->rx_bytes;
				rx_mcast = pcptr->rx_mcast;
				tx_pkts = pcptr->tx_pkts;
				tx_bytes = pcptr->tx_bytes;
			पूर्ण जबतक (u64_stats_fetch_retry_irq(&pcptr->syncp,
							   strt));

			s->rx_packets += rx_pkts;
			s->rx_bytes += rx_bytes;
			s->multicast += rx_mcast;
			s->tx_packets += tx_pkts;
			s->tx_bytes += tx_bytes;

			/* u32 values are updated without syncp protection. */
			rx_errs += pcptr->rx_errs;
			tx_drps += pcptr->tx_drps;
		पूर्ण
		s->rx_errors = rx_errs;
		s->rx_dropped = rx_errs;
		s->tx_dropped = tx_drps;
	पूर्ण
पूर्ण

अटल पूर्णांक ipvlan_vlan_rx_add_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);
	काष्ठा net_device *phy_dev = ipvlan->phy_dev;

	वापस vlan_vid_add(phy_dev, proto, vid);
पूर्ण

अटल पूर्णांक ipvlan_vlan_rx_समाप्त_vid(काष्ठा net_device *dev, __be16 proto,
				   u16 vid)
अणु
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);
	काष्ठा net_device *phy_dev = ipvlan->phy_dev;

	vlan_vid_del(phy_dev, proto, vid);
	वापस 0;
पूर्ण

अटल पूर्णांक ipvlan_get_अगरlink(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);

	वापस ipvlan->phy_dev->अगरindex;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ipvlan_netdev_ops = अणु
	.nकरो_init		= ipvlan_init,
	.nकरो_uninit		= ipvlan_uninit,
	.nकरो_खोलो		= ipvlan_खोलो,
	.nकरो_stop		= ipvlan_stop,
	.nकरो_start_xmit		= ipvlan_start_xmit,
	.nकरो_fix_features	= ipvlan_fix_features,
	.nकरो_change_rx_flags	= ipvlan_change_rx_flags,
	.nकरो_set_rx_mode	= ipvlan_set_multicast_mac_filter,
	.nकरो_get_stats64	= ipvlan_get_stats64,
	.nकरो_vlan_rx_add_vid	= ipvlan_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= ipvlan_vlan_rx_समाप्त_vid,
	.nकरो_get_अगरlink		= ipvlan_get_अगरlink,
पूर्ण;

अटल पूर्णांक ipvlan_hard_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			      अचिन्हित लघु type, स्थिर व्योम *daddr,
			      स्थिर व्योम *saddr, अचिन्हित len)
अणु
	स्थिर काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);
	काष्ठा net_device *phy_dev = ipvlan->phy_dev;

	/* TODO Probably use a dअगरferent field than dev_addr so that the
	 * mac-address on the भव device is portable and can be carried
	 * जबतक the packets use the mac-addr on the physical device.
	 */
	वापस dev_hard_header(skb, phy_dev, type, daddr,
			       saddr ? : phy_dev->dev_addr, len);
पूर्ण

अटल स्थिर काष्ठा header_ops ipvlan_header_ops = अणु
	.create  	= ipvlan_hard_header,
	.parse		= eth_header_parse,
	.cache		= eth_header_cache,
	.cache_update	= eth_header_cache_update,
पूर्ण;

अटल व्योम ipvlan_adjust_mtu(काष्ठा ipvl_dev *ipvlan, काष्ठा net_device *dev)
अणु
	ipvlan->dev->mtu = dev->mtu;
पूर्ण

अटल bool netअगर_is_ipvlan(स्थिर काष्ठा net_device *dev)
अणु
	/* both ipvlan and ipvtap devices use the same netdev_ops */
	वापस dev->netdev_ops == &ipvlan_netdev_ops;
पूर्ण

अटल पूर्णांक ipvlan_ethtool_get_link_ksettings(काष्ठा net_device *dev,
					     काष्ठा ethtool_link_ksettings *cmd)
अणु
	स्थिर काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);

	वापस __ethtool_get_link_ksettings(ipvlan->phy_dev, cmd);
पूर्ण

अटल व्योम ipvlan_ethtool_get_drvinfo(काष्ठा net_device *dev,
				       काष्ठा ethtool_drvinfo *drvinfo)
अणु
	strlcpy(drvinfo->driver, IPVLAN_DRV, माप(drvinfo->driver));
	strlcpy(drvinfo->version, IPV_DRV_VER, माप(drvinfo->version));
पूर्ण

अटल u32 ipvlan_ethtool_get_msglevel(काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);

	वापस ipvlan->msg_enable;
पूर्ण

अटल व्योम ipvlan_ethtool_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);

	ipvlan->msg_enable = value;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ipvlan_ethtool_ops = अणु
	.get_link	= ethtool_op_get_link,
	.get_link_ksettings	= ipvlan_ethtool_get_link_ksettings,
	.get_drvinfo	= ipvlan_ethtool_get_drvinfo,
	.get_msglevel	= ipvlan_ethtool_get_msglevel,
	.set_msglevel	= ipvlan_ethtool_set_msglevel,
पूर्ण;

अटल पूर्णांक ipvlan_nl_changelink(काष्ठा net_device *dev,
				काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);
	काष्ठा ipvl_port *port = ipvlan_port_get_rtnl(ipvlan->phy_dev);
	पूर्णांक err = 0;

	अगर (!data)
		वापस 0;
	अगर (!ns_capable(dev_net(ipvlan->phy_dev)->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (data[IFLA_IPVLAN_MODE]) अणु
		u16 nmode = nla_get_u16(data[IFLA_IPVLAN_MODE]);

		err = ipvlan_set_port_mode(port, nmode, extack);
	पूर्ण

	अगर (!err && data[IFLA_IPVLAN_FLAGS]) अणु
		u16 flags = nla_get_u16(data[IFLA_IPVLAN_FLAGS]);

		अगर (flags & IPVLAN_F_PRIVATE)
			ipvlan_mark_निजी(port);
		अन्यथा
			ipvlan_clear_निजी(port);

		अगर (flags & IPVLAN_F_VEPA)
			ipvlan_mark_vepa(port);
		अन्यथा
			ipvlan_clear_vepa(port);
	पूर्ण

	वापस err;
पूर्ण

अटल माप_प्रकार ipvlan_nl_माला_लोize(स्थिर काष्ठा net_device *dev)
अणु
	वापस (0
		+ nla_total_size(2) /* IFLA_IPVLAN_MODE */
		+ nla_total_size(2) /* IFLA_IPVLAN_FLAGS */
		);
पूर्ण

अटल पूर्णांक ipvlan_nl_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			      काष्ठा netlink_ext_ack *extack)
अणु
	अगर (!data)
		वापस 0;

	अगर (data[IFLA_IPVLAN_MODE]) अणु
		u16 mode = nla_get_u16(data[IFLA_IPVLAN_MODE]);

		अगर (mode >= IPVLAN_MODE_MAX)
			वापस -EINVAL;
	पूर्ण
	अगर (data[IFLA_IPVLAN_FLAGS]) अणु
		u16 flags = nla_get_u16(data[IFLA_IPVLAN_FLAGS]);

		/* Only two bits are used at this moment. */
		अगर (flags & ~(IPVLAN_F_PRIVATE | IPVLAN_F_VEPA))
			वापस -EINVAL;
		/* Also both flags can't be active at the same समय. */
		अगर ((flags & (IPVLAN_F_PRIVATE | IPVLAN_F_VEPA)) ==
		    (IPVLAN_F_PRIVATE | IPVLAN_F_VEPA))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ipvlan_nl_fillinfo(काष्ठा sk_buff *skb,
			      स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);
	काष्ठा ipvl_port *port = ipvlan_port_get_rtnl(ipvlan->phy_dev);
	पूर्णांक ret = -EINVAL;

	अगर (!port)
		जाओ err;

	ret = -EMSGSIZE;
	अगर (nla_put_u16(skb, IFLA_IPVLAN_MODE, port->mode))
		जाओ err;
	अगर (nla_put_u16(skb, IFLA_IPVLAN_FLAGS, port->flags))
		जाओ err;

	वापस 0;

err:
	वापस ret;
पूर्ण

पूर्णांक ipvlan_link_new(काष्ठा net *src_net, काष्ठा net_device *dev,
		    काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
		    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);
	काष्ठा ipvl_port *port;
	काष्ठा net_device *phy_dev;
	पूर्णांक err;
	u16 mode = IPVLAN_MODE_L3;

	अगर (!tb[IFLA_LINK])
		वापस -EINVAL;

	phy_dev = __dev_get_by_index(src_net, nla_get_u32(tb[IFLA_LINK]));
	अगर (!phy_dev)
		वापस -ENODEV;

	अगर (netअगर_is_ipvlan(phy_dev)) अणु
		काष्ठा ipvl_dev *पंचांगp = netdev_priv(phy_dev);

		phy_dev = पंचांगp->phy_dev;
		अगर (!ns_capable(dev_net(phy_dev)->user_ns, CAP_NET_ADMIN))
			वापस -EPERM;
	पूर्ण अन्यथा अगर (!netअगर_is_ipvlan_port(phy_dev)) अणु
		/* Exit early अगर the underlying link is invalid or busy */
		अगर (phy_dev->type != ARPHRD_ETHER ||
		    phy_dev->flags & IFF_LOOPBACK) अणु
			netdev_err(phy_dev,
				   "Master is either lo or non-ether device\n");
			वापस -EINVAL;
		पूर्ण

		अगर (netdev_is_rx_handler_busy(phy_dev)) अणु
			netdev_err(phy_dev, "Device is already in use.\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	ipvlan->phy_dev = phy_dev;
	ipvlan->dev = dev;
	ipvlan->sfeatures = IPVLAN_FEATURES;
	अगर (!tb[IFLA_MTU])
		ipvlan_adjust_mtu(ipvlan, phy_dev);
	INIT_LIST_HEAD(&ipvlan->addrs);
	spin_lock_init(&ipvlan->addrs_lock);

	/* TODO Probably put अक्रमom address here to be presented to the
	 * world but keep using the physical-dev address क्रम the outgoing
	 * packets.
	 */
	स_नकल(dev->dev_addr, phy_dev->dev_addr, ETH_ALEN);

	dev->priv_flags |= IFF_NO_RX_HANDLER;

	err = रेजिस्टर_netdevice(dev);
	अगर (err < 0)
		वापस err;

	/* ipvlan_init() would have created the port, अगर required */
	port = ipvlan_port_get_rtnl(phy_dev);
	ipvlan->port = port;

	/* If the port-id base is at the MAX value, then wrap it around and
	 * begin from 0x1 again. This may be due to a busy प्रणाली where lots
	 * of slaves are getting created and deleted.
	 */
	अगर (port->dev_id_start == 0xFFFE)
		port->dev_id_start = 0x1;

	/* Since L2 address is shared among all IPvlan slaves including
	 * master, use unique 16 bit dev-ids to dअगरfentiate among them.
	 * Assign IDs between 0x1 and 0xFFFE (used by the master) to each
	 * slave link [see addrconf_अगरid_eui48()].
	 */
	err = ida_simple_get(&port->ida, port->dev_id_start, 0xFFFE,
			     GFP_KERNEL);
	अगर (err < 0)
		err = ida_simple_get(&port->ida, 0x1, port->dev_id_start,
				     GFP_KERNEL);
	अगर (err < 0)
		जाओ unरेजिस्टर_netdev;
	dev->dev_id = err;

	/* Increment id-base to the next slot क्रम the future assignment */
	port->dev_id_start = err + 1;

	err = netdev_upper_dev_link(phy_dev, dev, extack);
	अगर (err)
		जाओ हटाओ_ida;

	/* Flags are per port and latest update overrides. User has
	 * to be consistent in setting it just like the mode attribute.
	 */
	अगर (data && data[IFLA_IPVLAN_FLAGS])
		port->flags = nla_get_u16(data[IFLA_IPVLAN_FLAGS]);

	अगर (data && data[IFLA_IPVLAN_MODE])
		mode = nla_get_u16(data[IFLA_IPVLAN_MODE]);

	err = ipvlan_set_port_mode(port, mode, extack);
	अगर (err)
		जाओ unlink_netdev;

	list_add_tail_rcu(&ipvlan->pnode, &port->ipvlans);
	netअगर_stacked_transfer_operstate(phy_dev, dev);
	वापस 0;

unlink_netdev:
	netdev_upper_dev_unlink(phy_dev, dev);
हटाओ_ida:
	ida_simple_हटाओ(&port->ida, dev->dev_id);
unरेजिस्टर_netdev:
	unरेजिस्टर_netdevice(dev);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(ipvlan_link_new);

व्योम ipvlan_link_delete(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);
	काष्ठा ipvl_addr *addr, *next;

	spin_lock_bh(&ipvlan->addrs_lock);
	list_क्रम_each_entry_safe(addr, next, &ipvlan->addrs, anode) अणु
		ipvlan_ht_addr_del(addr);
		list_del_rcu(&addr->anode);
		kमुक्त_rcu(addr, rcu);
	पूर्ण
	spin_unlock_bh(&ipvlan->addrs_lock);

	ida_simple_हटाओ(&ipvlan->port->ida, dev->dev_id);
	list_del_rcu(&ipvlan->pnode);
	unरेजिस्टर_netdevice_queue(dev, head);
	netdev_upper_dev_unlink(ipvlan->phy_dev, dev);
पूर्ण
EXPORT_SYMBOL_GPL(ipvlan_link_delete);

व्योम ipvlan_link_setup(काष्ठा net_device *dev)
अणु
	ether_setup(dev);

	dev->max_mtu = ETH_MAX_MTU;
	dev->priv_flags &= ~(IFF_XMIT_DST_RELEASE | IFF_TX_SKB_SHARING);
	dev->priv_flags |= IFF_UNICAST_FLT | IFF_NO_QUEUE;
	dev->netdev_ops = &ipvlan_netdev_ops;
	dev->needs_मुक्त_netdev = true;
	dev->header_ops = &ipvlan_header_ops;
	dev->ethtool_ops = &ipvlan_ethtool_ops;
पूर्ण
EXPORT_SYMBOL_GPL(ipvlan_link_setup);

अटल स्थिर काष्ठा nla_policy ipvlan_nl_policy[IFLA_IPVLAN_MAX + 1] =
अणु
	[IFLA_IPVLAN_MODE] = अणु .type = NLA_U16 पूर्ण,
	[IFLA_IPVLAN_FLAGS] = अणु .type = NLA_U16 पूर्ण,
पूर्ण;

अटल काष्ठा net *ipvlan_get_link_net(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);

	वापस dev_net(ipvlan->phy_dev);
पूर्ण

अटल काष्ठा rtnl_link_ops ipvlan_link_ops = अणु
	.kind		= "ipvlan",
	.priv_size	= माप(काष्ठा ipvl_dev),

	.setup		= ipvlan_link_setup,
	.newlink	= ipvlan_link_new,
	.dellink	= ipvlan_link_delete,
	.get_link_net   = ipvlan_get_link_net,
पूर्ण;

पूर्णांक ipvlan_link_रेजिस्टर(काष्ठा rtnl_link_ops *ops)
अणु
	ops->get_size	= ipvlan_nl_माला_लोize;
	ops->policy	= ipvlan_nl_policy;
	ops->validate	= ipvlan_nl_validate;
	ops->fill_info	= ipvlan_nl_fillinfo;
	ops->changelink = ipvlan_nl_changelink;
	ops->maxtype	= IFLA_IPVLAN_MAX;
	वापस rtnl_link_रेजिस्टर(ops);
पूर्ण
EXPORT_SYMBOL_GPL(ipvlan_link_रेजिस्टर);

अटल पूर्णांक ipvlan_device_event(काष्ठा notअगरier_block *unused,
			       अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा netlink_ext_ack *extack = netdev_notअगरier_info_to_extack(ptr);
	काष्ठा netdev_notअगरier_pre_changeaddr_info *prechaddr_info;
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा ipvl_dev *ipvlan, *next;
	काष्ठा ipvl_port *port;
	LIST_HEAD(lst_समाप्त);
	पूर्णांक err;

	अगर (!netअगर_is_ipvlan_port(dev))
		वापस NOTIFY_DONE;

	port = ipvlan_port_get_rtnl(dev);

	चयन (event) अणु
	हाल NETDEV_CHANGE:
		list_क्रम_each_entry(ipvlan, &port->ipvlans, pnode)
			netअगर_stacked_transfer_operstate(ipvlan->phy_dev,
							 ipvlan->dev);
		अवरोध;

	हाल NETDEV_REGISTER: अणु
		काष्ठा net *oldnet, *newnet = dev_net(dev);

		oldnet = पढ़ो_pnet(&port->pnet);
		अगर (net_eq(newnet, oldnet))
			अवरोध;

		ग_लिखो_pnet(&port->pnet, newnet);

		ipvlan_migrate_l3s_hook(oldnet, newnet);
		अवरोध;
	पूर्ण
	हाल NETDEV_UNREGISTER:
		अगर (dev->reg_state != NETREG_UNREGISTERING)
			अवरोध;

		list_क्रम_each_entry_safe(ipvlan, next, &port->ipvlans, pnode)
			ipvlan->dev->rtnl_link_ops->dellink(ipvlan->dev,
							    &lst_समाप्त);
		unरेजिस्टर_netdevice_many(&lst_समाप्त);
		अवरोध;

	हाल NETDEV_FEAT_CHANGE:
		list_क्रम_each_entry(ipvlan, &port->ipvlans, pnode) अणु
			ipvlan->dev->gso_max_size = dev->gso_max_size;
			ipvlan->dev->gso_max_segs = dev->gso_max_segs;
			netdev_update_features(ipvlan->dev);
		पूर्ण
		अवरोध;

	हाल NETDEV_CHANGEMTU:
		list_क्रम_each_entry(ipvlan, &port->ipvlans, pnode)
			ipvlan_adjust_mtu(ipvlan, dev);
		अवरोध;

	हाल NETDEV_PRE_CHANGEADDR:
		prechaddr_info = ptr;
		list_क्रम_each_entry(ipvlan, &port->ipvlans, pnode) अणु
			err = dev_pre_changeaddr_notअगरy(ipvlan->dev,
						    prechaddr_info->dev_addr,
						    extack);
			अगर (err)
				वापस notअगरier_from_त्रुटि_सं(err);
		पूर्ण
		अवरोध;

	हाल NETDEV_CHANGEADDR:
		list_क्रम_each_entry(ipvlan, &port->ipvlans, pnode) अणु
			ether_addr_copy(ipvlan->dev->dev_addr, dev->dev_addr);
			call_netdevice_notअगरiers(NETDEV_CHANGEADDR, ipvlan->dev);
		पूर्ण
		अवरोध;

	हाल NETDEV_PRE_TYPE_CHANGE:
		/* Forbid underlying device to change its type. */
		वापस NOTIFY_BAD;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

/* the caller must held the addrs lock */
अटल पूर्णांक ipvlan_add_addr(काष्ठा ipvl_dev *ipvlan, व्योम *iaddr, bool is_v6)
अणु
	काष्ठा ipvl_addr *addr;

	addr = kzalloc(माप(काष्ठा ipvl_addr), GFP_ATOMIC);
	अगर (!addr)
		वापस -ENOMEM;

	addr->master = ipvlan;
	अगर (!is_v6) अणु
		स_नकल(&addr->ip4addr, iaddr, माप(काष्ठा in_addr));
		addr->atype = IPVL_IPV4;
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		स_नकल(&addr->ip6addr, iaddr, माप(काष्ठा in6_addr));
		addr->atype = IPVL_IPV6;
#पूर्ण_अगर
	पूर्ण

	list_add_tail_rcu(&addr->anode, &ipvlan->addrs);

	/* If the पूर्णांकerface is not up, the address will be added to the hash
	 * list by ipvlan_खोलो.
	 */
	अगर (netअगर_running(ipvlan->dev))
		ipvlan_ht_addr_add(ipvlan, addr);

	वापस 0;
पूर्ण

अटल व्योम ipvlan_del_addr(काष्ठा ipvl_dev *ipvlan, व्योम *iaddr, bool is_v6)
अणु
	काष्ठा ipvl_addr *addr;

	spin_lock_bh(&ipvlan->addrs_lock);
	addr = ipvlan_find_addr(ipvlan, iaddr, is_v6);
	अगर (!addr) अणु
		spin_unlock_bh(&ipvlan->addrs_lock);
		वापस;
	पूर्ण

	ipvlan_ht_addr_del(addr);
	list_del_rcu(&addr->anode);
	spin_unlock_bh(&ipvlan->addrs_lock);
	kमुक्त_rcu(addr, rcu);
पूर्ण

अटल bool ipvlan_is_valid_dev(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);

	अगर (!netअगर_is_ipvlan(dev))
		वापस false;

	अगर (!ipvlan || !ipvlan->port)
		वापस false;

	वापस true;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक ipvlan_add_addr6(काष्ठा ipvl_dev *ipvlan, काष्ठा in6_addr *ip6_addr)
अणु
	पूर्णांक ret = -EINVAL;

	spin_lock_bh(&ipvlan->addrs_lock);
	अगर (ipvlan_addr_busy(ipvlan->port, ip6_addr, true))
		netअगर_err(ipvlan, अगरup, ipvlan->dev,
			  "Failed to add IPv6=%pI6c addr for %s intf\n",
			  ip6_addr, ipvlan->dev->name);
	अन्यथा
		ret = ipvlan_add_addr(ipvlan, ip6_addr, true);
	spin_unlock_bh(&ipvlan->addrs_lock);
	वापस ret;
पूर्ण

अटल व्योम ipvlan_del_addr6(काष्ठा ipvl_dev *ipvlan, काष्ठा in6_addr *ip6_addr)
अणु
	वापस ipvlan_del_addr(ipvlan, ip6_addr, true);
पूर्ण

अटल पूर्णांक ipvlan_addr6_event(काष्ठा notअगरier_block *unused,
			      अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा inet6_अगरaddr *अगर6 = (काष्ठा inet6_अगरaddr *)ptr;
	काष्ठा net_device *dev = (काष्ठा net_device *)अगर6->idev->dev;
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);

	अगर (!ipvlan_is_valid_dev(dev))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_UP:
		अगर (ipvlan_add_addr6(ipvlan, &अगर6->addr))
			वापस NOTIFY_BAD;
		अवरोध;

	हाल NETDEV_DOWN:
		ipvlan_del_addr6(ipvlan, &अगर6->addr);
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक ipvlan_addr6_validator_event(काष्ठा notअगरier_block *unused,
					अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा in6_validator_info *i6vi = (काष्ठा in6_validator_info *)ptr;
	काष्ठा net_device *dev = (काष्ठा net_device *)i6vi->i6vi_dev->dev;
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);

	अगर (!ipvlan_is_valid_dev(dev))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_UP:
		अगर (ipvlan_addr_busy(ipvlan->port, &i6vi->i6vi_addr, true)) अणु
			NL_SET_ERR_MSG(i6vi->extack,
				       "Address already assigned to an ipvlan device");
			वापस notअगरier_from_त्रुटि_सं(-EADDRINUSE);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ipvlan_add_addr4(काष्ठा ipvl_dev *ipvlan, काष्ठा in_addr *ip4_addr)
अणु
	पूर्णांक ret = -EINVAL;

	spin_lock_bh(&ipvlan->addrs_lock);
	अगर (ipvlan_addr_busy(ipvlan->port, ip4_addr, false))
		netअगर_err(ipvlan, अगरup, ipvlan->dev,
			  "Failed to add IPv4=%pI4 on %s intf.\n",
			  ip4_addr, ipvlan->dev->name);
	अन्यथा
		ret = ipvlan_add_addr(ipvlan, ip4_addr, false);
	spin_unlock_bh(&ipvlan->addrs_lock);
	वापस ret;
पूर्ण

अटल व्योम ipvlan_del_addr4(काष्ठा ipvl_dev *ipvlan, काष्ठा in_addr *ip4_addr)
अणु
	वापस ipvlan_del_addr(ipvlan, ip4_addr, false);
पूर्ण

अटल पूर्णांक ipvlan_addr4_event(काष्ठा notअगरier_block *unused,
			      अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा in_अगरaddr *अगर4 = (काष्ठा in_अगरaddr *)ptr;
	काष्ठा net_device *dev = (काष्ठा net_device *)अगर4->अगरa_dev->dev;
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);
	काष्ठा in_addr ip4_addr;

	अगर (!ipvlan_is_valid_dev(dev))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_UP:
		ip4_addr.s_addr = अगर4->अगरa_address;
		अगर (ipvlan_add_addr4(ipvlan, &ip4_addr))
			वापस NOTIFY_BAD;
		अवरोध;

	हाल NETDEV_DOWN:
		ip4_addr.s_addr = अगर4->अगरa_address;
		ipvlan_del_addr4(ipvlan, &ip4_addr);
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक ipvlan_addr4_validator_event(काष्ठा notअगरier_block *unused,
					अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा in_validator_info *ivi = (काष्ठा in_validator_info *)ptr;
	काष्ठा net_device *dev = (काष्ठा net_device *)ivi->ivi_dev->dev;
	काष्ठा ipvl_dev *ipvlan = netdev_priv(dev);

	अगर (!ipvlan_is_valid_dev(dev))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_UP:
		अगर (ipvlan_addr_busy(ipvlan->port, &ivi->ivi_addr, false)) अणु
			NL_SET_ERR_MSG(ivi->extack,
				       "Address already assigned to an ipvlan device");
			वापस notअगरier_from_त्रुटि_सं(-EADDRINUSE);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block ipvlan_addr4_notअगरier_block __पढ़ो_mostly = अणु
	.notअगरier_call = ipvlan_addr4_event,
पूर्ण;

अटल काष्ठा notअगरier_block ipvlan_addr4_vtor_notअगरier_block __पढ़ो_mostly = अणु
	.notअगरier_call = ipvlan_addr4_validator_event,
पूर्ण;

अटल काष्ठा notअगरier_block ipvlan_notअगरier_block __पढ़ो_mostly = अणु
	.notअगरier_call = ipvlan_device_event,
पूर्ण;

#अगर IS_ENABLED(CONFIG_IPV6)
अटल काष्ठा notअगरier_block ipvlan_addr6_notअगरier_block __पढ़ो_mostly = अणु
	.notअगरier_call = ipvlan_addr6_event,
पूर्ण;

अटल काष्ठा notअगरier_block ipvlan_addr6_vtor_notअगरier_block __पढ़ो_mostly = अणु
	.notअगरier_call = ipvlan_addr6_validator_event,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init ipvlan_init_module(व्योम)
अणु
	पूर्णांक err;

	ipvlan_init_secret();
	रेजिस्टर_netdevice_notअगरier(&ipvlan_notअगरier_block);
#अगर IS_ENABLED(CONFIG_IPV6)
	रेजिस्टर_inet6addr_notअगरier(&ipvlan_addr6_notअगरier_block);
	रेजिस्टर_inet6addr_validator_notअगरier(
	    &ipvlan_addr6_vtor_notअगरier_block);
#पूर्ण_अगर
	रेजिस्टर_inetaddr_notअगरier(&ipvlan_addr4_notअगरier_block);
	रेजिस्टर_inetaddr_validator_notअगरier(&ipvlan_addr4_vtor_notअगरier_block);

	err = ipvlan_l3s_init();
	अगर (err < 0)
		जाओ error;

	err = ipvlan_link_रेजिस्टर(&ipvlan_link_ops);
	अगर (err < 0) अणु
		ipvlan_l3s_cleanup();
		जाओ error;
	पूर्ण

	वापस 0;
error:
	unरेजिस्टर_inetaddr_notअगरier(&ipvlan_addr4_notअगरier_block);
	unरेजिस्टर_inetaddr_validator_notअगरier(
	    &ipvlan_addr4_vtor_notअगरier_block);
#अगर IS_ENABLED(CONFIG_IPV6)
	unरेजिस्टर_inet6addr_notअगरier(&ipvlan_addr6_notअगरier_block);
	unरेजिस्टर_inet6addr_validator_notअगरier(
	    &ipvlan_addr6_vtor_notअगरier_block);
#पूर्ण_अगर
	unरेजिस्टर_netdevice_notअगरier(&ipvlan_notअगरier_block);
	वापस err;
पूर्ण

अटल व्योम __निकास ipvlan_cleanup_module(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&ipvlan_link_ops);
	ipvlan_l3s_cleanup();
	unरेजिस्टर_netdevice_notअगरier(&ipvlan_notअगरier_block);
	unरेजिस्टर_inetaddr_notअगरier(&ipvlan_addr4_notअगरier_block);
	unरेजिस्टर_inetaddr_validator_notअगरier(
	    &ipvlan_addr4_vtor_notअगरier_block);
#अगर IS_ENABLED(CONFIG_IPV6)
	unरेजिस्टर_inet6addr_notअगरier(&ipvlan_addr6_notअगरier_block);
	unरेजिस्टर_inet6addr_validator_notअगरier(
	    &ipvlan_addr6_vtor_notअगरier_block);
#पूर्ण_अगर
पूर्ण

module_init(ipvlan_init_module);
module_निकास(ipvlan_cleanup_module);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mahesh Bandewar <maheshb@google.com>");
MODULE_DESCRIPTION("Driver for L3 (IPv6/IPv4) based VLANs");
MODULE_ALIAS_RTNL_LINK("ipvlan");
