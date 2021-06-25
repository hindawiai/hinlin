<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Device handling code
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netpoll.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/list.h>
#समावेश <linux/netfilter_bridge.h>

#समावेश <linux/uaccess.h>
#समावेश "br_private.h"

#घोषणा COMMON_FEATURES (NETIF_F_SG | NETIF_F_FRAGLIST | NETIF_F_HIGHDMA | \
			 NETIF_F_GSO_MASK | NETIF_F_HW_CSUM)

स्थिर काष्ठा nf_br_ops __rcu *nf_br_ops __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nf_br_ops);

/* net device transmit always called with BH disabled */
netdev_tx_t br_dev_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);
	काष्ठा net_bridge_fdb_entry *dst;
	काष्ठा net_bridge_mdb_entry *mdst;
	स्थिर काष्ठा nf_br_ops *nf_ops;
	u8 state = BR_STATE_FORWARDING;
	स्थिर अचिन्हित अक्षर *dest;
	u16 vid = 0;

	स_रखो(skb->cb, 0, माप(काष्ठा br_input_skb_cb));

	rcu_पढ़ो_lock();
	nf_ops = rcu_dereference(nf_br_ops);
	अगर (nf_ops && nf_ops->br_dev_xmit_hook(skb)) अणु
		rcu_पढ़ो_unlock();
		वापस NETDEV_TX_OK;
	पूर्ण

	dev_sw_netstats_tx_add(dev, 1, skb->len);

	br_चयनdev_frame_unmark(skb);
	BR_INPUT_SKB_CB(skb)->brdev = dev;
	BR_INPUT_SKB_CB(skb)->frag_max_size = 0;

	skb_reset_mac_header(skb);
	skb_pull(skb, ETH_HLEN);

	अगर (!br_allowed_ingress(br, br_vlan_group_rcu(br), skb, &vid, &state))
		जाओ out;

	अगर (IS_ENABLED(CONFIG_INET) &&
	    (eth_hdr(skb)->h_proto == htons(ETH_P_ARP) ||
	     eth_hdr(skb)->h_proto == htons(ETH_P_RARP)) &&
	    br_opt_get(br, BROPT_NEIGH_SUPPRESS_ENABLED)) अणु
		br_करो_proxy_suppress_arp(skb, br, vid, शून्य);
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_IPV6) &&
		   skb->protocol == htons(ETH_P_IPV6) &&
		   br_opt_get(br, BROPT_NEIGH_SUPPRESS_ENABLED) &&
		   pskb_may_pull(skb, माप(काष्ठा ipv6hdr) +
				 माप(काष्ठा nd_msg)) &&
		   ipv6_hdr(skb)->nexthdr == IPPROTO_ICMPV6) अणु
			काष्ठा nd_msg *msg, _msg;

			msg = br_is_nd_neigh_msg(skb, &_msg);
			अगर (msg)
				br_करो_suppress_nd(skb, br, vid, शून्य, msg);
	पूर्ण

	dest = eth_hdr(skb)->h_dest;
	अगर (is_broadcast_ether_addr(dest)) अणु
		br_flood(br, skb, BR_PKT_BROADCAST, false, true);
	पूर्ण अन्यथा अगर (is_multicast_ether_addr(dest)) अणु
		अगर (unlikely(netpoll_tx_running(dev))) अणु
			br_flood(br, skb, BR_PKT_MULTICAST, false, true);
			जाओ out;
		पूर्ण
		अगर (br_multicast_rcv(br, शून्य, skb, vid)) अणु
			kमुक्त_skb(skb);
			जाओ out;
		पूर्ण

		mdst = br_mdb_get(br, skb, vid);
		अगर ((mdst || BR_INPUT_SKB_CB_MROUTERS_ONLY(skb)) &&
		    br_multicast_querier_exists(br, eth_hdr(skb), mdst))
			br_multicast_flood(mdst, skb, false, true);
		अन्यथा
			br_flood(br, skb, BR_PKT_MULTICAST, false, true);
	पूर्ण अन्यथा अगर ((dst = br_fdb_find_rcu(br, dest, vid)) != शून्य) अणु
		br_क्रमward(dst->dst, skb, false, true);
	पूर्ण अन्यथा अणु
		br_flood(br, skb, BR_PKT_UNICAST, false, true);
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	वापस NETDEV_TX_OK;
पूर्ण

अटल काष्ठा lock_class_key bridge_netdev_addr_lock_key;

अटल व्योम br_set_lockdep_class(काष्ठा net_device *dev)
अणु
	lockdep_set_class(&dev->addr_list_lock, &bridge_netdev_addr_lock_key);
पूर्ण

अटल पूर्णांक br_dev_init(काष्ठा net_device *dev)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);
	पूर्णांक err;

	dev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
	अगर (!dev->tstats)
		वापस -ENOMEM;

	err = br_fdb_hash_init(br);
	अगर (err) अणु
		मुक्त_percpu(dev->tstats);
		वापस err;
	पूर्ण

	err = br_mdb_hash_init(br);
	अगर (err) अणु
		मुक्त_percpu(dev->tstats);
		br_fdb_hash_fini(br);
		वापस err;
	पूर्ण

	err = br_vlan_init(br);
	अगर (err) अणु
		मुक्त_percpu(dev->tstats);
		br_mdb_hash_fini(br);
		br_fdb_hash_fini(br);
		वापस err;
	पूर्ण

	err = br_multicast_init_stats(br);
	अगर (err) अणु
		मुक्त_percpu(dev->tstats);
		br_vlan_flush(br);
		br_mdb_hash_fini(br);
		br_fdb_hash_fini(br);
	पूर्ण

	br_set_lockdep_class(dev);
	वापस err;
पूर्ण

अटल व्योम br_dev_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);

	br_multicast_dev_del(br);
	br_multicast_uninit_stats(br);
	br_vlan_flush(br);
	br_mdb_hash_fini(br);
	br_fdb_hash_fini(br);
	मुक्त_percpu(dev->tstats);
पूर्ण

अटल पूर्णांक br_dev_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);

	netdev_update_features(dev);
	netअगर_start_queue(dev);
	br_stp_enable_bridge(br);
	br_multicast_खोलो(br);

	अगर (br_opt_get(br, BROPT_MULTICAST_ENABLED))
		br_multicast_join_snoopers(br);

	वापस 0;
पूर्ण

अटल व्योम br_dev_set_multicast_list(काष्ठा net_device *dev)
अणु
पूर्ण

अटल व्योम br_dev_change_rx_flags(काष्ठा net_device *dev, पूर्णांक change)
अणु
	अगर (change & IFF_PROMISC)
		br_manage_promisc(netdev_priv(dev));
पूर्ण

अटल पूर्णांक br_dev_stop(काष्ठा net_device *dev)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);

	br_stp_disable_bridge(br);
	br_multicast_stop(br);

	अगर (br_opt_get(br, BROPT_MULTICAST_ENABLED))
		br_multicast_leave_snoopers(br);

	netअगर_stop_queue(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक br_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);

	dev->mtu = new_mtu;

	/* this flag will be cleared अगर the MTU was स्वतःmatically adjusted */
	br_opt_toggle(br, BROPT_MTU_SET_BY_USER, true);
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
	/* remember the MTU in the rtable क्रम PMTU */
	dst_metric_set(&br->fake_rtable.dst, RTAX_MTU, new_mtu);
#पूर्ण_अगर

	वापस 0;
पूर्ण

/* Allow setting mac address to any valid ethernet address. */
अटल पूर्णांक br_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	/* dev_set_mac_addr() can be called by a master device on bridge's
	 * NETDEV_UNREGISTER, but since it's being destroyed करो nothing
	 */
	अगर (dev->reg_state != NETREG_REGISTERED)
		वापस -EBUSY;

	spin_lock_bh(&br->lock);
	अगर (!ether_addr_equal(dev->dev_addr, addr->sa_data)) अणु
		/* Mac address will be changed in br_stp_change_bridge_id(). */
		br_stp_change_bridge_id(br, addr->sa_data);
	पूर्ण
	spin_unlock_bh(&br->lock);

	वापस 0;
पूर्ण

अटल व्योम br_getinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, "bridge", माप(info->driver));
	strlcpy(info->version, BR_VERSION, माप(info->version));
	strlcpy(info->fw_version, "N/A", माप(info->fw_version));
	strlcpy(info->bus_info, "N/A", माप(info->bus_info));
पूर्ण

अटल पूर्णांक br_get_link_ksettings(काष्ठा net_device *dev,
				 काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);
	काष्ठा net_bridge_port *p;

	cmd->base.duplex = DUPLEX_UNKNOWN;
	cmd->base.port = PORT_OTHER;
	cmd->base.speed = SPEED_UNKNOWN;

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		काष्ठा ethtool_link_ksettings ecmd;
		काष्ठा net_device *pdev = p->dev;

		अगर (!netअगर_running(pdev) || !netअगर_oper_up(pdev))
			जारी;

		अगर (__ethtool_get_link_ksettings(pdev, &ecmd))
			जारी;

		अगर (ecmd.base.speed == (__u32)SPEED_UNKNOWN)
			जारी;

		अगर (cmd->base.speed == (__u32)SPEED_UNKNOWN ||
		    cmd->base.speed < ecmd.base.speed)
			cmd->base.speed = ecmd.base.speed;
	पूर्ण

	वापस 0;
पूर्ण

अटल netdev_features_t br_fix_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);

	वापस br_features_recompute(br, features);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम br_poll_controller(काष्ठा net_device *br_dev)
अणु
पूर्ण

अटल व्योम br_netpoll_cleanup(काष्ठा net_device *dev)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);
	काष्ठा net_bridge_port *p;

	list_क्रम_each_entry(p, &br->port_list, list)
		br_netpoll_disable(p);
पूर्ण

अटल पूर्णांक __br_netpoll_enable(काष्ठा net_bridge_port *p)
अणु
	काष्ठा netpoll *np;
	पूर्णांक err;

	np = kzalloc(माप(*p->np), GFP_KERNEL);
	अगर (!np)
		वापस -ENOMEM;

	err = __netpoll_setup(np, p->dev);
	अगर (err) अणु
		kमुक्त(np);
		वापस err;
	पूर्ण

	p->np = np;
	वापस err;
पूर्ण

पूर्णांक br_netpoll_enable(काष्ठा net_bridge_port *p)
अणु
	अगर (!p->br->dev->npinfo)
		वापस 0;

	वापस __br_netpoll_enable(p);
पूर्ण

अटल पूर्णांक br_netpoll_setup(काष्ठा net_device *dev, काष्ठा netpoll_info *ni)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);
	काष्ठा net_bridge_port *p;
	पूर्णांक err = 0;

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		अगर (!p->dev)
			जारी;
		err = __br_netpoll_enable(p);
		अगर (err)
			जाओ fail;
	पूर्ण

out:
	वापस err;

fail:
	br_netpoll_cleanup(dev);
	जाओ out;
पूर्ण

व्योम br_netpoll_disable(काष्ठा net_bridge_port *p)
अणु
	काष्ठा netpoll *np = p->np;

	अगर (!np)
		वापस;

	p->np = शून्य;

	__netpoll_मुक्त(np);
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक br_add_slave(काष्ठा net_device *dev, काष्ठा net_device *slave_dev,
			काष्ठा netlink_ext_ack *extack)

अणु
	काष्ठा net_bridge *br = netdev_priv(dev);

	वापस br_add_अगर(br, slave_dev, extack);
पूर्ण

अटल पूर्णांक br_del_slave(काष्ठा net_device *dev, काष्ठा net_device *slave_dev)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);

	वापस br_del_अगर(br, slave_dev);
पूर्ण

अटल पूर्णांक br_fill_क्रमward_path(काष्ठा net_device_path_ctx *ctx,
				काष्ठा net_device_path *path)
अणु
	काष्ठा net_bridge_fdb_entry *f;
	काष्ठा net_bridge_port *dst;
	काष्ठा net_bridge *br;

	अगर (netअगर_is_bridge_port(ctx->dev))
		वापस -1;

	br = netdev_priv(ctx->dev);

	br_vlan_fill_क्रमward_path_pvid(br, ctx, path);

	f = br_fdb_find_rcu(br, ctx->daddr, path->bridge.vlan_id);
	अगर (!f || !f->dst)
		वापस -1;

	dst = READ_ONCE(f->dst);
	अगर (!dst)
		वापस -1;

	अगर (br_vlan_fill_क्रमward_path_mode(br, dst, path))
		वापस -1;

	path->type = DEV_PATH_BRIDGE;
	path->dev = dst->br->dev;
	ctx->dev = dst->dev;

	चयन (path->bridge.vlan_mode) अणु
	हाल DEV_PATH_BR_VLAN_TAG:
		अगर (ctx->num_vlans >= ARRAY_SIZE(ctx->vlan))
			वापस -ENOSPC;
		ctx->vlan[ctx->num_vlans].id = path->bridge.vlan_id;
		ctx->vlan[ctx->num_vlans].proto = path->bridge.vlan_proto;
		ctx->num_vlans++;
		अवरोध;
	हाल DEV_PATH_BR_VLAN_UNTAG_HW:
	हाल DEV_PATH_BR_VLAN_UNTAG:
		ctx->num_vlans--;
		अवरोध;
	हाल DEV_PATH_BR_VLAN_KEEP:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops br_ethtool_ops = अणु
	.get_drvinfo		 = br_getinfo,
	.get_link		 = ethtool_op_get_link,
	.get_link_ksettings	 = br_get_link_ksettings,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops br_netdev_ops = अणु
	.nकरो_खोलो		 = br_dev_खोलो,
	.nकरो_stop		 = br_dev_stop,
	.nकरो_init		 = br_dev_init,
	.nकरो_uninit		 = br_dev_uninit,
	.nकरो_start_xmit		 = br_dev_xmit,
	.nकरो_get_stats64	 = dev_get_tstats64,
	.nकरो_set_mac_address	 = br_set_mac_address,
	.nकरो_set_rx_mode	 = br_dev_set_multicast_list,
	.nकरो_change_rx_flags	 = br_dev_change_rx_flags,
	.nकरो_change_mtu		 = br_change_mtu,
	.nकरो_करो_ioctl		 = br_dev_ioctl,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_netpoll_setup	 = br_netpoll_setup,
	.nकरो_netpoll_cleanup	 = br_netpoll_cleanup,
	.nकरो_poll_controller	 = br_poll_controller,
#पूर्ण_अगर
	.nकरो_add_slave		 = br_add_slave,
	.nकरो_del_slave		 = br_del_slave,
	.nकरो_fix_features        = br_fix_features,
	.nकरो_fdb_add		 = br_fdb_add,
	.nकरो_fdb_del		 = br_fdb_delete,
	.nकरो_fdb_dump		 = br_fdb_dump,
	.nकरो_fdb_get		 = br_fdb_get,
	.nकरो_bridge_getlink	 = br_getlink,
	.nकरो_bridge_setlink	 = br_setlink,
	.nकरो_bridge_dellink	 = br_dellink,
	.nकरो_features_check	 = passthru_features_check,
	.nकरो_fill_क्रमward_path	 = br_fill_क्रमward_path,
पूर्ण;

अटल काष्ठा device_type br_type = अणु
	.name	= "bridge",
पूर्ण;

व्योम br_dev_setup(काष्ठा net_device *dev)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);

	eth_hw_addr_अक्रमom(dev);
	ether_setup(dev);

	dev->netdev_ops = &br_netdev_ops;
	dev->needs_मुक्त_netdev = true;
	dev->ethtool_ops = &br_ethtool_ops;
	SET_NETDEV_DEVTYPE(dev, &br_type);
	dev->priv_flags = IFF_EBRIDGE | IFF_NO_QUEUE;

	dev->features = COMMON_FEATURES | NETIF_F_LLTX | NETIF_F_NETNS_LOCAL |
			NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_STAG_TX;
	dev->hw_features = COMMON_FEATURES | NETIF_F_HW_VLAN_CTAG_TX |
			   NETIF_F_HW_VLAN_STAG_TX;
	dev->vlan_features = COMMON_FEATURES;

	br->dev = dev;
	spin_lock_init(&br->lock);
	INIT_LIST_HEAD(&br->port_list);
	INIT_HLIST_HEAD(&br->fdb_list);
	INIT_HLIST_HEAD(&br->frame_type_list);
#अगर IS_ENABLED(CONFIG_BRIDGE_MRP)
	INIT_HLIST_HEAD(&br->mrp_list);
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_BRIDGE_CFM)
	INIT_HLIST_HEAD(&br->mep_list);
#पूर्ण_अगर
	spin_lock_init(&br->hash_lock);

	br->bridge_id.prio[0] = 0x80;
	br->bridge_id.prio[1] = 0x00;

	ether_addr_copy(br->group_addr, eth_stp_addr);

	br->stp_enabled = BR_NO_STP;
	br->group_fwd_mask = BR_GROUPFWD_DEFAULT;
	br->group_fwd_mask_required = BR_GROUPFWD_DEFAULT;

	br->designated_root = br->bridge_id;
	br->bridge_max_age = br->max_age = 20 * HZ;
	br->bridge_hello_समय = br->hello_समय = 2 * HZ;
	br->bridge_क्रमward_delay = br->क्रमward_delay = 15 * HZ;
	br->bridge_ageing_समय = br->ageing_समय = BR_DEFAULT_AGEING_TIME;
	dev->max_mtu = ETH_MAX_MTU;

	br_netfilter_rtable_init(br);
	br_stp_समयr_init(br);
	br_multicast_init(br);
	INIT_DELAYED_WORK(&br->gc_work, br_fdb_cleanup);
पूर्ण
