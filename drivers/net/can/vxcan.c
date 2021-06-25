<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vxcan.c - Virtual CAN Tunnel क्रम cross namespace communication
 *
 * This code is derived from drivers/net/can/vcan.c क्रम the भव CAN
 * specअगरic parts and from drivers/net/veth.c to implement the netlink API
 * क्रम network पूर्णांकerface pairs in a common and established way.
 *
 * Copyright (c) 2017 Oliver Hartkopp <socketcan@hartkopp.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/skb.h>
#समावेश <linux/can/vxcan.h>
#समावेश <linux/can/can-ml.h>
#समावेश <linux/slab.h>
#समावेश <net/rtnetlink.h>

#घोषणा DRV_NAME "vxcan"

MODULE_DESCRIPTION("Virtual CAN Tunnel");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Oliver Hartkopp <socketcan@hartkopp.net>");
MODULE_ALIAS_RTNL_LINK(DRV_NAME);

काष्ठा vxcan_priv अणु
	काष्ठा net_device __rcu	*peer;
पूर्ण;

अटल netdev_tx_t vxcan_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा vxcan_priv *priv = netdev_priv(dev);
	काष्ठा net_device *peer;
	काष्ठा canfd_frame *cfd = (काष्ठा canfd_frame *)skb->data;
	काष्ठा net_device_stats *peerstats, *srcstats = &dev->stats;
	u8 len;

	अगर (can_dropped_invalid_skb(dev, skb))
		वापस NETDEV_TX_OK;

	rcu_पढ़ो_lock();
	peer = rcu_dereference(priv->peer);
	अगर (unlikely(!peer)) अणु
		kमुक्त_skb(skb);
		dev->stats.tx_dropped++;
		जाओ out_unlock;
	पूर्ण

	skb = can_create_echo_skb(skb);
	अगर (!skb)
		जाओ out_unlock;

	/* reset CAN GW hop counter */
	skb->csum_start = 0;
	skb->pkt_type   = PACKET_BROADCAST;
	skb->dev        = peer;
	skb->ip_summed  = CHECKSUM_UNNECESSARY;

	len = cfd->len;
	अगर (netअगर_rx_ni(skb) == NET_RX_SUCCESS) अणु
		srcstats->tx_packets++;
		srcstats->tx_bytes += len;
		peerstats = &peer->stats;
		peerstats->rx_packets++;
		peerstats->rx_bytes += len;
	पूर्ण

out_unlock:
	rcu_पढ़ो_unlock();
	वापस NETDEV_TX_OK;
पूर्ण


अटल पूर्णांक vxcan_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा vxcan_priv *priv = netdev_priv(dev);
	काष्ठा net_device *peer = rtnl_dereference(priv->peer);

	अगर (!peer)
		वापस -ENOTCONN;

	अगर (peer->flags & IFF_UP) अणु
		netअगर_carrier_on(dev);
		netअगर_carrier_on(peer);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vxcan_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा vxcan_priv *priv = netdev_priv(dev);
	काष्ठा net_device *peer = rtnl_dereference(priv->peer);

	netअगर_carrier_off(dev);
	अगर (peer)
		netअगर_carrier_off(peer);

	वापस 0;
पूर्ण

अटल पूर्णांक vxcan_get_अगरlink(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा vxcan_priv *priv = netdev_priv(dev);
	काष्ठा net_device *peer;
	पूर्णांक अगरlink;

	rcu_पढ़ो_lock();
	peer = rcu_dereference(priv->peer);
	अगरlink = peer ? peer->अगरindex : 0;
	rcu_पढ़ो_unlock();

	वापस अगरlink;
पूर्ण

अटल पूर्णांक vxcan_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	/* Do not allow changing the MTU जबतक running */
	अगर (dev->flags & IFF_UP)
		वापस -EBUSY;

	अगर (new_mtu != CAN_MTU && new_mtu != CANFD_MTU)
		वापस -EINVAL;

	dev->mtu = new_mtu;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops vxcan_netdev_ops = अणु
	.nकरो_खोलो	= vxcan_खोलो,
	.nकरो_stop	= vxcan_बंद,
	.nकरो_start_xmit	= vxcan_xmit,
	.nकरो_get_अगरlink	= vxcan_get_अगरlink,
	.nकरो_change_mtu = vxcan_change_mtu,
पूर्ण;

अटल व्योम vxcan_setup(काष्ठा net_device *dev)
अणु
	काष्ठा can_ml_priv *can_ml;

	dev->type		= ARPHRD_CAN;
	dev->mtu		= CANFD_MTU;
	dev->hard_header_len	= 0;
	dev->addr_len		= 0;
	dev->tx_queue_len	= 0;
	dev->flags		= (IFF_NOARP|IFF_ECHO);
	dev->netdev_ops		= &vxcan_netdev_ops;
	dev->needs_मुक्त_netdev	= true;

	can_ml = netdev_priv(dev) + ALIGN(माप(काष्ठा vxcan_priv), NETDEV_ALIGN);
	can_set_ml_priv(dev, can_ml);
पूर्ण

/* क्रमward declaration क्रम rtnl_create_link() */
अटल काष्ठा rtnl_link_ops vxcan_link_ops;

अटल पूर्णांक vxcan_newlink(काष्ठा net *net, काष्ठा net_device *dev,
			 काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा vxcan_priv *priv;
	काष्ठा net_device *peer;
	काष्ठा net *peer_net;

	काष्ठा nlattr *peer_tb[IFLA_MAX + 1], **tbp = tb;
	अक्षर अगरname[IFNAMSIZ];
	अचिन्हित अक्षर name_assign_type;
	काष्ठा अगरinfomsg *अगरmp = शून्य;
	पूर्णांक err;

	/* रेजिस्टर peer device */
	अगर (data && data[VXCAN_INFO_PEER]) अणु
		काष्ठा nlattr *nla_peer;

		nla_peer = data[VXCAN_INFO_PEER];
		अगरmp = nla_data(nla_peer);
		err = rtnl_nla_parse_अगरla(peer_tb,
					  nla_data(nla_peer) +
					  माप(काष्ठा अगरinfomsg),
					  nla_len(nla_peer) -
					  माप(काष्ठा अगरinfomsg),
					  शून्य);
		अगर (err < 0)
			वापस err;

		tbp = peer_tb;
	पूर्ण

	अगर (अगरmp && tbp[IFLA_IFNAME]) अणु
		nla_strscpy(अगरname, tbp[IFLA_IFNAME], IFNAMSIZ);
		name_assign_type = NET_NAME_USER;
	पूर्ण अन्यथा अणु
		snम_लिखो(अगरname, IFNAMSIZ, DRV_NAME "%%d");
		name_assign_type = NET_NAME_ENUM;
	पूर्ण

	peer_net = rtnl_link_get_net(net, tbp);
	अगर (IS_ERR(peer_net))
		वापस PTR_ERR(peer_net);

	peer = rtnl_create_link(peer_net, अगरname, name_assign_type,
				&vxcan_link_ops, tbp, extack);
	अगर (IS_ERR(peer)) अणु
		put_net(peer_net);
		वापस PTR_ERR(peer);
	पूर्ण

	अगर (अगरmp && dev->अगरindex)
		peer->अगरindex = अगरmp->अगरi_index;

	err = रेजिस्टर_netdevice(peer);
	put_net(peer_net);
	peer_net = शून्य;
	अगर (err < 0) अणु
		मुक्त_netdev(peer);
		वापस err;
	पूर्ण

	netअगर_carrier_off(peer);

	err = rtnl_configure_link(peer, अगरmp);
	अगर (err < 0)
		जाओ unरेजिस्टर_network_device;

	/* रेजिस्टर first device */
	अगर (tb[IFLA_IFNAME])
		nla_strscpy(dev->name, tb[IFLA_IFNAME], IFNAMSIZ);
	अन्यथा
		snम_लिखो(dev->name, IFNAMSIZ, DRV_NAME "%%d");

	err = रेजिस्टर_netdevice(dev);
	अगर (err < 0)
		जाओ unरेजिस्टर_network_device;

	netअगर_carrier_off(dev);

	/* cross link the device pair */
	priv = netdev_priv(dev);
	rcu_assign_poपूर्णांकer(priv->peer, peer);

	priv = netdev_priv(peer);
	rcu_assign_poपूर्णांकer(priv->peer, dev);

	वापस 0;

unरेजिस्टर_network_device:
	unरेजिस्टर_netdevice(peer);
	वापस err;
पूर्ण

अटल व्योम vxcan_dellink(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा vxcan_priv *priv;
	काष्ठा net_device *peer;

	priv = netdev_priv(dev);
	peer = rtnl_dereference(priv->peer);

	/* Note : dellink() is called from शेष_device_निकास_batch(),
	 * beक्रमe a rcu_synchronize() poपूर्णांक. The devices are guaranteed
	 * not being मुक्तd beक्रमe one RCU grace period.
	 */
	RCU_INIT_POINTER(priv->peer, शून्य);
	unरेजिस्टर_netdevice_queue(dev, head);

	अगर (peer) अणु
		priv = netdev_priv(peer);
		RCU_INIT_POINTER(priv->peer, शून्य);
		unरेजिस्टर_netdevice_queue(peer, head);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nla_policy vxcan_policy[VXCAN_INFO_MAX + 1] = अणु
	[VXCAN_INFO_PEER] = अणु .len = माप(काष्ठा अगरinfomsg) पूर्ण,
पूर्ण;

अटल काष्ठा net *vxcan_get_link_net(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा vxcan_priv *priv = netdev_priv(dev);
	काष्ठा net_device *peer = rtnl_dereference(priv->peer);

	वापस peer ? dev_net(peer) : dev_net(dev);
पूर्ण

अटल काष्ठा rtnl_link_ops vxcan_link_ops = अणु
	.kind		= DRV_NAME,
	.priv_size	= ALIGN(माप(काष्ठा vxcan_priv), NETDEV_ALIGN) + माप(काष्ठा can_ml_priv),
	.setup		= vxcan_setup,
	.newlink	= vxcan_newlink,
	.dellink	= vxcan_dellink,
	.policy		= vxcan_policy,
	.maxtype	= VXCAN_INFO_MAX,
	.get_link_net	= vxcan_get_link_net,
पूर्ण;

अटल __init पूर्णांक vxcan_init(व्योम)
अणु
	pr_info("vxcan: Virtual CAN Tunnel driver\n");

	वापस rtnl_link_रेजिस्टर(&vxcan_link_ops);
पूर्ण

अटल __निकास व्योम vxcan_निकास(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&vxcan_link_ops);
पूर्ण

module_init(vxcan_init);
module_निकास(vxcan_निकास);
