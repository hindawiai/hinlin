<शैली गुरु>
/*
 * Copyright (C) 2017 Netronome Systems, Inc.
 *
 * This software is licensed under the GNU General License Version 2,
 * June 1991 as shown in the file COPYING in the top-level directory of this
 * source tree.
 *
 * THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS"
 * WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE
 * OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME
 * THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/udp_tunnel.h>

#समावेश "netdevsim.h"

अटल netdev_tx_t nsim_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);

	अगर (!nsim_ipsec_tx(ns, skb))
		जाओ out;

	u64_stats_update_begin(&ns->syncp);
	ns->tx_packets++;
	ns->tx_bytes += skb->len;
	u64_stats_update_end(&ns->syncp);

out:
	dev_kमुक्त_skb(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम nsim_set_rx_mode(काष्ठा net_device *dev)
अणु
पूर्ण

अटल पूर्णांक nsim_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);

	अगर (ns->xdp.prog && new_mtu > NSIM_XDP_MAX_MTU)
		वापस -EBUSY;

	dev->mtu = new_mtu;

	वापस 0;
पूर्ण

अटल व्योम
nsim_get_stats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);
	अचिन्हित पूर्णांक start;

	करो अणु
		start = u64_stats_fetch_begin(&ns->syncp);
		stats->tx_bytes = ns->tx_bytes;
		stats->tx_packets = ns->tx_packets;
	पूर्ण जबतक (u64_stats_fetch_retry(&ns->syncp, start));
पूर्ण

अटल पूर्णांक
nsim_setup_tc_block_cb(क्रमागत tc_setup_type type, व्योम *type_data, व्योम *cb_priv)
अणु
	वापस nsim_bpf_setup_tc_block_cb(type, type_data, cb_priv);
पूर्ण

अटल पूर्णांक nsim_set_vf_mac(काष्ठा net_device *dev, पूर्णांक vf, u8 *mac)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);
	काष्ठा nsim_bus_dev *nsim_bus_dev = ns->nsim_bus_dev;

	/* Only refuse multicast addresses, zero address can mean unset/any. */
	अगर (vf >= nsim_bus_dev->num_vfs || is_multicast_ether_addr(mac))
		वापस -EINVAL;
	स_नकल(nsim_bus_dev->vfconfigs[vf].vf_mac, mac, ETH_ALEN);

	वापस 0;
पूर्ण

अटल पूर्णांक nsim_set_vf_vlan(काष्ठा net_device *dev, पूर्णांक vf,
			    u16 vlan, u8 qos, __be16 vlan_proto)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);
	काष्ठा nsim_bus_dev *nsim_bus_dev = ns->nsim_bus_dev;

	अगर (vf >= nsim_bus_dev->num_vfs || vlan > 4095 || qos > 7)
		वापस -EINVAL;

	nsim_bus_dev->vfconfigs[vf].vlan = vlan;
	nsim_bus_dev->vfconfigs[vf].qos = qos;
	nsim_bus_dev->vfconfigs[vf].vlan_proto = vlan_proto;

	वापस 0;
पूर्ण

अटल पूर्णांक nsim_set_vf_rate(काष्ठा net_device *dev, पूर्णांक vf, पूर्णांक min, पूर्णांक max)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);
	काष्ठा nsim_bus_dev *nsim_bus_dev = ns->nsim_bus_dev;

	अगर (vf >= nsim_bus_dev->num_vfs)
		वापस -EINVAL;

	nsim_bus_dev->vfconfigs[vf].min_tx_rate = min;
	nsim_bus_dev->vfconfigs[vf].max_tx_rate = max;

	वापस 0;
पूर्ण

अटल पूर्णांक nsim_set_vf_spoofchk(काष्ठा net_device *dev, पूर्णांक vf, bool val)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);
	काष्ठा nsim_bus_dev *nsim_bus_dev = ns->nsim_bus_dev;

	अगर (vf >= nsim_bus_dev->num_vfs)
		वापस -EINVAL;
	nsim_bus_dev->vfconfigs[vf].spoofchk_enabled = val;

	वापस 0;
पूर्ण

अटल पूर्णांक nsim_set_vf_rss_query_en(काष्ठा net_device *dev, पूर्णांक vf, bool val)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);
	काष्ठा nsim_bus_dev *nsim_bus_dev = ns->nsim_bus_dev;

	अगर (vf >= nsim_bus_dev->num_vfs)
		वापस -EINVAL;
	nsim_bus_dev->vfconfigs[vf].rss_query_enabled = val;

	वापस 0;
पूर्ण

अटल पूर्णांक nsim_set_vf_trust(काष्ठा net_device *dev, पूर्णांक vf, bool val)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);
	काष्ठा nsim_bus_dev *nsim_bus_dev = ns->nsim_bus_dev;

	अगर (vf >= nsim_bus_dev->num_vfs)
		वापस -EINVAL;
	nsim_bus_dev->vfconfigs[vf].trusted = val;

	वापस 0;
पूर्ण

अटल पूर्णांक
nsim_get_vf_config(काष्ठा net_device *dev, पूर्णांक vf, काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);
	काष्ठा nsim_bus_dev *nsim_bus_dev = ns->nsim_bus_dev;

	अगर (vf >= nsim_bus_dev->num_vfs)
		वापस -EINVAL;

	ivi->vf = vf;
	ivi->linkstate = nsim_bus_dev->vfconfigs[vf].link_state;
	ivi->min_tx_rate = nsim_bus_dev->vfconfigs[vf].min_tx_rate;
	ivi->max_tx_rate = nsim_bus_dev->vfconfigs[vf].max_tx_rate;
	ivi->vlan = nsim_bus_dev->vfconfigs[vf].vlan;
	ivi->vlan_proto = nsim_bus_dev->vfconfigs[vf].vlan_proto;
	ivi->qos = nsim_bus_dev->vfconfigs[vf].qos;
	स_नकल(&ivi->mac, nsim_bus_dev->vfconfigs[vf].vf_mac, ETH_ALEN);
	ivi->spoofchk = nsim_bus_dev->vfconfigs[vf].spoofchk_enabled;
	ivi->trusted = nsim_bus_dev->vfconfigs[vf].trusted;
	ivi->rss_query_en = nsim_bus_dev->vfconfigs[vf].rss_query_enabled;

	वापस 0;
पूर्ण

अटल पूर्णांक nsim_set_vf_link_state(काष्ठा net_device *dev, पूर्णांक vf, पूर्णांक state)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);
	काष्ठा nsim_bus_dev *nsim_bus_dev = ns->nsim_bus_dev;

	अगर (vf >= nsim_bus_dev->num_vfs)
		वापस -EINVAL;

	चयन (state) अणु
	हाल IFLA_VF_LINK_STATE_AUTO:
	हाल IFLA_VF_LINK_STATE_ENABLE:
	हाल IFLA_VF_LINK_STATE_DISABLE:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	nsim_bus_dev->vfconfigs[vf].link_state = state;

	वापस 0;
पूर्ण

अटल LIST_HEAD(nsim_block_cb_list);

अटल पूर्णांक
nsim_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type, व्योम *type_data)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);

	चयन (type) अणु
	हाल TC_SETUP_BLOCK:
		वापस flow_block_cb_setup_simple(type_data,
						  &nsim_block_cb_list,
						  nsim_setup_tc_block_cb,
						  ns, ns, true);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक
nsim_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);

	अगर ((dev->features & NETIF_F_HW_TC) > (features & NETIF_F_HW_TC))
		वापस nsim_bpf_disable_tc(ns);

	वापस 0;
पूर्ण

अटल काष्ठा devlink_port *nsim_get_devlink_port(काष्ठा net_device *dev)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);

	वापस &ns->nsim_dev_port->devlink_port;
पूर्ण

अटल स्थिर काष्ठा net_device_ops nsim_netdev_ops = अणु
	.nकरो_start_xmit		= nsim_start_xmit,
	.nकरो_set_rx_mode	= nsim_set_rx_mode,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_change_mtu		= nsim_change_mtu,
	.nकरो_get_stats64	= nsim_get_stats64,
	.nकरो_set_vf_mac		= nsim_set_vf_mac,
	.nकरो_set_vf_vlan	= nsim_set_vf_vlan,
	.nकरो_set_vf_rate	= nsim_set_vf_rate,
	.nकरो_set_vf_spoofchk	= nsim_set_vf_spoofchk,
	.nकरो_set_vf_trust	= nsim_set_vf_trust,
	.nकरो_get_vf_config	= nsim_get_vf_config,
	.nकरो_set_vf_link_state	= nsim_set_vf_link_state,
	.nकरो_set_vf_rss_query_en = nsim_set_vf_rss_query_en,
	.nकरो_setup_tc		= nsim_setup_tc,
	.nकरो_set_features	= nsim_set_features,
	.nकरो_bpf		= nsim_bpf,
	.nकरो_get_devlink_port	= nsim_get_devlink_port,
पूर्ण;

अटल व्योम nsim_setup(काष्ठा net_device *dev)
अणु
	ether_setup(dev);
	eth_hw_addr_अक्रमom(dev);

	dev->tx_queue_len = 0;
	dev->flags |= IFF_NOARP;
	dev->flags &= ~IFF_MULTICAST;
	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE |
			   IFF_NO_QUEUE;
	dev->features |= NETIF_F_HIGHDMA |
			 NETIF_F_SG |
			 NETIF_F_FRAGLIST |
			 NETIF_F_HW_CSUM |
			 NETIF_F_TSO;
	dev->hw_features |= NETIF_F_HW_TC;
	dev->max_mtu = ETH_MAX_MTU;
पूर्ण

काष्ठा netdevsim *
nsim_create(काष्ठा nsim_dev *nsim_dev, काष्ठा nsim_dev_port *nsim_dev_port)
अणु
	काष्ठा net_device *dev;
	काष्ठा netdevsim *ns;
	पूर्णांक err;

	dev = alloc_netdev(माप(*ns), "eth%d", NET_NAME_UNKNOWN, nsim_setup);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	dev_net_set(dev, nsim_dev_net(nsim_dev));
	ns = netdev_priv(dev);
	ns->netdev = dev;
	u64_stats_init(&ns->syncp);
	ns->nsim_dev = nsim_dev;
	ns->nsim_dev_port = nsim_dev_port;
	ns->nsim_bus_dev = nsim_dev->nsim_bus_dev;
	SET_NETDEV_DEV(dev, &ns->nsim_bus_dev->dev);
	dev->netdev_ops = &nsim_netdev_ops;
	nsim_ethtool_init(ns);

	err = nsim_udp_tunnels_info_create(nsim_dev, dev);
	अगर (err)
		जाओ err_मुक्त_netdev;

	rtnl_lock();
	err = nsim_bpf_init(ns);
	अगर (err)
		जाओ err_utn_destroy;

	nsim_ipsec_init(ns);

	err = रेजिस्टर_netdevice(dev);
	अगर (err)
		जाओ err_ipsec_tearकरोwn;
	rtnl_unlock();

	वापस ns;

err_ipsec_tearकरोwn:
	nsim_ipsec_tearकरोwn(ns);
	nsim_bpf_uninit(ns);
err_utn_destroy:
	rtnl_unlock();
	nsim_udp_tunnels_info_destroy(dev);
err_मुक्त_netdev:
	मुक्त_netdev(dev);
	वापस ERR_PTR(err);
पूर्ण

व्योम nsim_destroy(काष्ठा netdevsim *ns)
अणु
	काष्ठा net_device *dev = ns->netdev;

	rtnl_lock();
	unरेजिस्टर_netdevice(dev);
	nsim_ipsec_tearकरोwn(ns);
	nsim_bpf_uninit(ns);
	rtnl_unlock();
	nsim_udp_tunnels_info_destroy(dev);
	मुक्त_netdev(dev);
पूर्ण

अटल पूर्णांक nsim_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			 काष्ठा netlink_ext_ack *extack)
अणु
	NL_SET_ERR_MSG_MOD(extack, "Please use: echo \"[ID] [PORT_COUNT]\" > /sys/bus/netdevsim/new_device");
	वापस -EOPNOTSUPP;
पूर्ण

अटल काष्ठा rtnl_link_ops nsim_link_ops __पढ़ो_mostly = अणु
	.kind		= DRV_NAME,
	.validate	= nsim_validate,
पूर्ण;

अटल पूर्णांक __init nsim_module_init(व्योम)
अणु
	पूर्णांक err;

	err = nsim_dev_init();
	अगर (err)
		वापस err;

	err = nsim_bus_init();
	अगर (err)
		जाओ err_dev_निकास;

	err = rtnl_link_रेजिस्टर(&nsim_link_ops);
	अगर (err)
		जाओ err_bus_निकास;

	वापस 0;

err_bus_निकास:
	nsim_bus_निकास();
err_dev_निकास:
	nsim_dev_निकास();
	वापस err;
पूर्ण

अटल व्योम __निकास nsim_module_निकास(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&nsim_link_ops);
	nsim_bus_निकास();
	nsim_dev_निकास();
पूर्ण

module_init(nsim_module_init);
module_निकास(nsim_module_निकास);
MODULE_LICENSE("GPL");
MODULE_ALIAS_RTNL_LINK(DRV_NAME);
