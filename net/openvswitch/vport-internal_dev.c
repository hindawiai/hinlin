<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2007-2012 Nicira, Inc.
 */

#समावेश <linux/अगर_vlan.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/skbuff.h>

#समावेश <net/dst.h>
#समावेश <net/xfrm.h>
#समावेश <net/rtnetlink.h>

#समावेश "datapath.h"
#समावेश "vport-internal_dev.h"
#समावेश "vport-netdev.h"

काष्ठा पूर्णांकernal_dev अणु
	काष्ठा vport *vport;
पूर्ण;

अटल काष्ठा vport_ops ovs_पूर्णांकernal_vport_ops;

अटल काष्ठा पूर्णांकernal_dev *पूर्णांकernal_dev_priv(काष्ठा net_device *netdev)
अणु
	वापस netdev_priv(netdev);
पूर्ण

/* Called with rcu_पढ़ो_lock_bh. */
अटल netdev_tx_t
पूर्णांकernal_dev_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	पूर्णांक len, err;

	/* store len value because skb can be मुक्तd inside ovs_vport_receive() */
	len = skb->len;

	rcu_पढ़ो_lock();
	err = ovs_vport_receive(पूर्णांकernal_dev_priv(netdev)->vport, skb, शून्य);
	rcu_पढ़ो_unlock();

	अगर (likely(!err))
		dev_sw_netstats_tx_add(netdev, 1, len);
	अन्यथा
		netdev->stats.tx_errors++;

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक पूर्णांकernal_dev_खोलो(काष्ठा net_device *netdev)
अणु
	netअगर_start_queue(netdev);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकernal_dev_stop(काष्ठा net_device *netdev)
अणु
	netअगर_stop_queue(netdev);
	वापस 0;
पूर्ण

अटल व्योम पूर्णांकernal_dev_getinfo(काष्ठा net_device *netdev,
				 काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, "openvswitch", माप(info->driver));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops पूर्णांकernal_dev_ethtool_ops = अणु
	.get_drvinfo	= पूर्णांकernal_dev_getinfo,
	.get_link	= ethtool_op_get_link,
पूर्ण;

अटल व्योम पूर्णांकernal_dev_deकाष्ठाor(काष्ठा net_device *dev)
अणु
	काष्ठा vport *vport = ovs_पूर्णांकernal_dev_get_vport(dev);

	ovs_vport_मुक्त(vport);
पूर्ण

अटल स्थिर काष्ठा net_device_ops पूर्णांकernal_dev_netdev_ops = अणु
	.nकरो_खोलो = पूर्णांकernal_dev_खोलो,
	.nकरो_stop = पूर्णांकernal_dev_stop,
	.nकरो_start_xmit = पूर्णांकernal_dev_xmit,
	.nकरो_set_mac_address = eth_mac_addr,
	.nकरो_get_stats64 = dev_get_tstats64,
पूर्ण;

अटल काष्ठा rtnl_link_ops पूर्णांकernal_dev_link_ops __पढ़ो_mostly = अणु
	.kind = "openvswitch",
पूर्ण;

अटल व्योम करो_setup(काष्ठा net_device *netdev)
अणु
	ether_setup(netdev);

	netdev->max_mtu = ETH_MAX_MTU;

	netdev->netdev_ops = &पूर्णांकernal_dev_netdev_ops;

	netdev->priv_flags &= ~IFF_TX_SKB_SHARING;
	netdev->priv_flags |= IFF_LIVE_ADDR_CHANGE | IFF_OPENVSWITCH |
			      IFF_NO_QUEUE;
	netdev->needs_मुक्त_netdev = true;
	netdev->priv_deकाष्ठाor = शून्य;
	netdev->ethtool_ops = &पूर्णांकernal_dev_ethtool_ops;
	netdev->rtnl_link_ops = &पूर्णांकernal_dev_link_ops;

	netdev->features = NETIF_F_LLTX | NETIF_F_SG | NETIF_F_FRAGLIST |
			   NETIF_F_HIGHDMA | NETIF_F_HW_CSUM |
			   NETIF_F_GSO_SOFTWARE | NETIF_F_GSO_ENCAP_ALL;

	netdev->vlan_features = netdev->features;
	netdev->hw_enc_features = netdev->features;
	netdev->features |= NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_STAG_TX;
	netdev->hw_features = netdev->features & ~NETIF_F_LLTX;

	eth_hw_addr_अक्रमom(netdev);
पूर्ण

अटल काष्ठा vport *पूर्णांकernal_dev_create(स्थिर काष्ठा vport_parms *parms)
अणु
	काष्ठा vport *vport;
	काष्ठा पूर्णांकernal_dev *पूर्णांकernal_dev;
	काष्ठा net_device *dev;
	पूर्णांक err;

	vport = ovs_vport_alloc(0, &ovs_पूर्णांकernal_vport_ops, parms);
	अगर (IS_ERR(vport)) अणु
		err = PTR_ERR(vport);
		जाओ error;
	पूर्ण

	dev = alloc_netdev(माप(काष्ठा पूर्णांकernal_dev),
			   parms->name, NET_NAME_USER, करो_setup);
	vport->dev = dev;
	अगर (!vport->dev) अणु
		err = -ENOMEM;
		जाओ error_मुक्त_vport;
	पूर्ण
	vport->dev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
	अगर (!vport->dev->tstats) अणु
		err = -ENOMEM;
		जाओ error_मुक्त_netdev;
	पूर्ण

	dev_net_set(vport->dev, ovs_dp_get_net(vport->dp));
	पूर्णांकernal_dev = पूर्णांकernal_dev_priv(vport->dev);
	पूर्णांकernal_dev->vport = vport;

	/* Restrict bridge port to current netns. */
	अगर (vport->port_no == OVSP_LOCAL)
		vport->dev->features |= NETIF_F_NETNS_LOCAL;

	rtnl_lock();
	err = रेजिस्टर_netdevice(vport->dev);
	अगर (err)
		जाओ error_unlock;
	vport->dev->priv_deकाष्ठाor = पूर्णांकernal_dev_deकाष्ठाor;

	dev_set_promiscuity(vport->dev, 1);
	rtnl_unlock();
	netअगर_start_queue(vport->dev);

	वापस vport;

error_unlock:
	rtnl_unlock();
	मुक्त_percpu(dev->tstats);
error_मुक्त_netdev:
	मुक्त_netdev(dev);
error_मुक्त_vport:
	ovs_vport_मुक्त(vport);
error:
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम पूर्णांकernal_dev_destroy(काष्ठा vport *vport)
अणु
	netअगर_stop_queue(vport->dev);
	rtnl_lock();
	dev_set_promiscuity(vport->dev, -1);

	/* unरेजिस्टर_netdevice() रुकोs क्रम an RCU grace period. */
	unरेजिस्टर_netdevice(vport->dev);
	मुक्त_percpu(vport->dev->tstats);
	rtnl_unlock();
पूर्ण

अटल netdev_tx_t पूर्णांकernal_dev_recv(काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *netdev = skb->dev;

	अगर (unlikely(!(netdev->flags & IFF_UP))) अणु
		kमुक्त_skb(skb);
		netdev->stats.rx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	skb_dst_drop(skb);
	nf_reset_ct(skb);
	secpath_reset(skb);

	skb->pkt_type = PACKET_HOST;
	skb->protocol = eth_type_trans(skb, netdev);
	skb_postpull_rcsum(skb, eth_hdr(skb), ETH_HLEN);
	dev_sw_netstats_rx_add(netdev, skb->len);

	netअगर_rx(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल काष्ठा vport_ops ovs_पूर्णांकernal_vport_ops = अणु
	.type		= OVS_VPORT_TYPE_INTERNAL,
	.create		= पूर्णांकernal_dev_create,
	.destroy	= पूर्णांकernal_dev_destroy,
	.send		= पूर्णांकernal_dev_recv,
पूर्ण;

पूर्णांक ovs_is_पूर्णांकernal_dev(स्थिर काष्ठा net_device *netdev)
अणु
	वापस netdev->netdev_ops == &पूर्णांकernal_dev_netdev_ops;
पूर्ण

काष्ठा vport *ovs_पूर्णांकernal_dev_get_vport(काष्ठा net_device *netdev)
अणु
	अगर (!ovs_is_पूर्णांकernal_dev(netdev))
		वापस शून्य;

	वापस पूर्णांकernal_dev_priv(netdev)->vport;
पूर्ण

पूर्णांक ovs_पूर्णांकernal_dev_rtnl_link_रेजिस्टर(व्योम)
अणु
	पूर्णांक err;

	err = rtnl_link_रेजिस्टर(&पूर्णांकernal_dev_link_ops);
	अगर (err < 0)
		वापस err;

	err = ovs_vport_ops_रेजिस्टर(&ovs_पूर्णांकernal_vport_ops);
	अगर (err < 0)
		rtnl_link_unरेजिस्टर(&पूर्णांकernal_dev_link_ops);

	वापस err;
पूर्ण

व्योम ovs_पूर्णांकernal_dev_rtnl_link_unरेजिस्टर(व्योम)
अणु
	ovs_vport_ops_unरेजिस्टर(&ovs_पूर्णांकernal_vport_ops);
	rtnl_link_unरेजिस्टर(&पूर्णांकernal_dev_link_ops);
पूर्ण
