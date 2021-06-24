<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* sunvnet.c: Sun LDOM Virtual Network Driver.
 *
 * Copyright (C) 2007, 2008 David S. Miller <davem@davemloft.net>
 * Copyright (C) 2016-2017 Oracle. All rights reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/mutex.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/अगर_vlan.h>

#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <linux/icmpv6.h>
#पूर्ण_अगर

#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/route.h>

#समावेश <यंत्र/vपन.स>
#समावेश <यंत्र/ldc.h>

#समावेश "sunvnet_common.h"

/* length of समय beक्रमe we decide the hardware is borked,
 * and dev->tx_समयout() should be called to fix the problem
 */
#घोषणा VNET_TX_TIMEOUT			(5 * HZ)

#घोषणा DRV_MODULE_NAME		"sunvnet"
#घोषणा DRV_MODULE_VERSION	"2.0"
#घोषणा DRV_MODULE_RELDATE	"February 3, 2017"

अटल अक्षर version[] =
	DRV_MODULE_NAME " " DRV_MODULE_VERSION " (" DRV_MODULE_RELDATE ")";
MODULE_AUTHOR("David S. Miller (davem@davemloft.net)");
MODULE_DESCRIPTION("Sun LDOM virtual network driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_MODULE_VERSION);

/* Ordered from largest major to lowest */
अटल काष्ठा vio_version vnet_versions[] = अणु
	अणु .major = 1, .minor = 8 पूर्ण,
	अणु .major = 1, .minor = 7 पूर्ण,
	अणु .major = 1, .minor = 6 पूर्ण,
	अणु .major = 1, .minor = 0 पूर्ण,
पूर्ण;

अटल व्योम vnet_get_drvinfo(काष्ठा net_device *dev,
			     काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_MODULE_NAME, माप(info->driver));
	strlcpy(info->version, DRV_MODULE_VERSION, माप(info->version));
पूर्ण

अटल u32 vnet_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा vnet *vp = netdev_priv(dev);

	वापस vp->msg_enable;
पूर्ण

अटल व्योम vnet_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा vnet *vp = netdev_priv(dev);

	vp->msg_enable = value;
पूर्ण

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर string[ETH_GSTRING_LEN];
पूर्ण ethtool_stats_keys[] = अणु
	अणु "rx_packets" पूर्ण,
	अणु "tx_packets" पूर्ण,
	अणु "rx_bytes" पूर्ण,
	अणु "tx_bytes" पूर्ण,
	अणु "rx_errors" पूर्ण,
	अणु "tx_errors" पूर्ण,
	अणु "rx_dropped" पूर्ण,
	अणु "tx_dropped" पूर्ण,
	अणु "multicast" पूर्ण,
	अणु "rx_length_errors" पूर्ण,
	अणु "rx_frame_errors" पूर्ण,
	अणु "rx_missed_errors" पूर्ण,
	अणु "tx_carrier_errors" पूर्ण,
	अणु "nports" पूर्ण,
पूर्ण;

अटल पूर्णांक vnet_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा vnet *vp = (काष्ठा vnet *)netdev_priv(dev);

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(ethtool_stats_keys)
			+ (NUM_VNET_PORT_STATS * vp->nports);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम vnet_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *buf)
अणु
	काष्ठा vnet *vp = (काष्ठा vnet *)netdev_priv(dev);
	काष्ठा vnet_port *port;
	अक्षर *p = (अक्षर *)buf;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		स_नकल(buf, &ethtool_stats_keys, माप(ethtool_stats_keys));
		p += माप(ethtool_stats_keys);

		rcu_पढ़ो_lock();
		list_क्रम_each_entry_rcu(port, &vp->port_list, list) अणु
			snम_लिखो(p, ETH_GSTRING_LEN, "p%u.%s-%pM",
				 port->q_index, port->चयन_port ? "s" : "q",
				 port->raddr);
			p += ETH_GSTRING_LEN;
			snम_लिखो(p, ETH_GSTRING_LEN, "p%u.rx_packets",
				 port->q_index);
			p += ETH_GSTRING_LEN;
			snम_लिखो(p, ETH_GSTRING_LEN, "p%u.tx_packets",
				 port->q_index);
			p += ETH_GSTRING_LEN;
			snम_लिखो(p, ETH_GSTRING_LEN, "p%u.rx_bytes",
				 port->q_index);
			p += ETH_GSTRING_LEN;
			snम_लिखो(p, ETH_GSTRING_LEN, "p%u.tx_bytes",
				 port->q_index);
			p += ETH_GSTRING_LEN;
			snम_लिखो(p, ETH_GSTRING_LEN, "p%u.event_up",
				 port->q_index);
			p += ETH_GSTRING_LEN;
			snम_लिखो(p, ETH_GSTRING_LEN, "p%u.event_reset",
				 port->q_index);
			p += ETH_GSTRING_LEN;
		पूर्ण
		rcu_पढ़ो_unlock();
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम vnet_get_ethtool_stats(काष्ठा net_device *dev,
				   काष्ठा ethtool_stats *estats, u64 *data)
अणु
	काष्ठा vnet *vp = (काष्ठा vnet *)netdev_priv(dev);
	काष्ठा vnet_port *port;
	पूर्णांक i = 0;

	data[i++] = dev->stats.rx_packets;
	data[i++] = dev->stats.tx_packets;
	data[i++] = dev->stats.rx_bytes;
	data[i++] = dev->stats.tx_bytes;
	data[i++] = dev->stats.rx_errors;
	data[i++] = dev->stats.tx_errors;
	data[i++] = dev->stats.rx_dropped;
	data[i++] = dev->stats.tx_dropped;
	data[i++] = dev->stats.multicast;
	data[i++] = dev->stats.rx_length_errors;
	data[i++] = dev->stats.rx_frame_errors;
	data[i++] = dev->stats.rx_missed_errors;
	data[i++] = dev->stats.tx_carrier_errors;
	data[i++] = vp->nports;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(port, &vp->port_list, list) अणु
		data[i++] = port->q_index;
		data[i++] = port->stats.rx_packets;
		data[i++] = port->stats.tx_packets;
		data[i++] = port->stats.rx_bytes;
		data[i++] = port->stats.tx_bytes;
		data[i++] = port->stats.event_up;
		data[i++] = port->stats.event_reset;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल स्थिर काष्ठा ethtool_ops vnet_ethtool_ops = अणु
	.get_drvinfo		= vnet_get_drvinfo,
	.get_msglevel		= vnet_get_msglevel,
	.set_msglevel		= vnet_set_msglevel,
	.get_link		= ethtool_op_get_link,
	.get_sset_count		= vnet_get_sset_count,
	.get_strings		= vnet_get_strings,
	.get_ethtool_stats	= vnet_get_ethtool_stats,
पूर्ण;

अटल LIST_HEAD(vnet_list);
अटल DEFINE_MUTEX(vnet_list_mutex);

अटल काष्ठा vnet_port *__tx_port_find(काष्ठा vnet *vp, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक hash = vnet_hashfn(skb->data);
	काष्ठा hlist_head *hp = &vp->port_hash[hash];
	काष्ठा vnet_port *port;

	hlist_क्रम_each_entry_rcu(port, hp, hash) अणु
		अगर (!sunvnet_port_is_up_common(port))
			जारी;
		अगर (ether_addr_equal(port->raddr, skb->data))
			वापस port;
	पूर्ण
	list_क्रम_each_entry_rcu(port, &vp->port_list, list) अणु
		अगर (!port->चयन_port)
			जारी;
		अगर (!sunvnet_port_is_up_common(port))
			जारी;
		वापस port;
	पूर्ण
	वापस शून्य;
पूर्ण

/* func arg to vnet_start_xmit_common() to get the proper tx port */
अटल काष्ठा vnet_port *vnet_tx_port_find(काष्ठा sk_buff *skb,
					   काष्ठा net_device *dev)
अणु
	काष्ठा vnet *vp = netdev_priv(dev);

	वापस __tx_port_find(vp, skb);
पूर्ण

अटल u16 vnet_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			     काष्ठा net_device *sb_dev)
अणु
	काष्ठा vnet *vp = netdev_priv(dev);
	काष्ठा vnet_port *port = __tx_port_find(vp, skb);

	अगर (!port)
		वापस 0;

	वापस port->q_index;
पूर्ण

/* Wrappers to common functions */
अटल netdev_tx_t vnet_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	वापस sunvnet_start_xmit_common(skb, dev, vnet_tx_port_find);
पूर्ण

अटल व्योम vnet_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा vnet *vp = netdev_priv(dev);

	वापस sunvnet_set_rx_mode_common(dev, vp);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम vnet_poll_controller(काष्ठा net_device *dev)
अणु
	काष्ठा vnet *vp = netdev_priv(dev);

	वापस sunvnet_poll_controller_common(dev, vp);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops vnet_ops = अणु
	.nकरो_खोलो		= sunvnet_खोलो_common,
	.nकरो_stop		= sunvnet_बंद_common,
	.nकरो_set_rx_mode	= vnet_set_rx_mode,
	.nकरो_set_mac_address	= sunvnet_set_mac_addr_common,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_tx_समयout		= sunvnet_tx_समयout_common,
	.nकरो_start_xmit		= vnet_start_xmit,
	.nकरो_select_queue	= vnet_select_queue,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= vnet_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा vnet *vnet_new(स्थिर u64 *local_mac,
			     काष्ठा vio_dev *vdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा vnet *vp;
	पूर्णांक err, i;

	dev = alloc_etherdev_mqs(माप(*vp), VNET_MAX_TXQS, 1);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);
	dev->needed_headroom = VNET_PACKET_SKIP + 8;
	dev->needed_tailroom = 8;

	क्रम (i = 0; i < ETH_ALEN; i++)
		dev->dev_addr[i] = (*local_mac >> (5 - i) * 8) & 0xff;

	vp = netdev_priv(dev);

	spin_lock_init(&vp->lock);
	vp->dev = dev;

	INIT_LIST_HEAD(&vp->port_list);
	क्रम (i = 0; i < VNET_PORT_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&vp->port_hash[i]);
	INIT_LIST_HEAD(&vp->list);
	vp->local_mac = *local_mac;

	dev->netdev_ops = &vnet_ops;
	dev->ethtool_ops = &vnet_ethtool_ops;
	dev->watchकरोg_समयo = VNET_TX_TIMEOUT;

	dev->hw_features = NETIF_F_TSO | NETIF_F_GSO | NETIF_F_ALL_TSO |
			   NETIF_F_HW_CSUM | NETIF_F_SG;
	dev->features = dev->hw_features;

	/* MTU range: 68 - 65535 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = VNET_MAX_MTU;

	SET_NETDEV_DEV(dev, &vdev->dev);

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		pr_err("Cannot register net device, aborting\n");
		जाओ err_out_मुक्त_dev;
	पूर्ण

	netdev_info(dev, "Sun LDOM vnet %pM\n", dev->dev_addr);

	list_add(&vp->list, &vnet_list);

	वापस vp;

err_out_मुक्त_dev:
	मुक्त_netdev(dev);

	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा vnet *vnet_find_or_create(स्थिर u64 *local_mac,
					काष्ठा vio_dev *vdev)
अणु
	काष्ठा vnet *iter, *vp;

	mutex_lock(&vnet_list_mutex);
	vp = शून्य;
	list_क्रम_each_entry(iter, &vnet_list, list) अणु
		अगर (iter->local_mac == *local_mac) अणु
			vp = iter;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!vp)
		vp = vnet_new(local_mac, vdev);
	mutex_unlock(&vnet_list_mutex);

	वापस vp;
पूर्ण

अटल व्योम vnet_cleanup(व्योम)
अणु
	काष्ठा vnet *vp;
	काष्ठा net_device *dev;

	mutex_lock(&vnet_list_mutex);
	जबतक (!list_empty(&vnet_list)) अणु
		vp = list_first_entry(&vnet_list, काष्ठा vnet, list);
		list_del(&vp->list);
		dev = vp->dev;
		/* vio_unरेजिस्टर_driver() should have cleaned up port_list */
		BUG_ON(!list_empty(&vp->port_list));
		unरेजिस्टर_netdev(dev);
		मुक्त_netdev(dev);
	पूर्ण
	mutex_unlock(&vnet_list_mutex);
पूर्ण

अटल स्थिर अक्षर *local_mac_prop = "local-mac-address";

अटल काष्ठा vnet *vnet_find_parent(काष्ठा mdesc_handle *hp,
				     u64 port_node,
				     काष्ठा vio_dev *vdev)
अणु
	स्थिर u64 *local_mac = शून्य;
	u64 a;

	mdesc_क्रम_each_arc(a, hp, port_node, MDESC_ARC_TYPE_BACK) अणु
		u64 target = mdesc_arc_target(hp, a);
		स्थिर अक्षर *name;

		name = mdesc_get_property(hp, target, "name", शून्य);
		अगर (!name || म_भेद(name, "network"))
			जारी;

		local_mac = mdesc_get_property(hp, target,
					       local_mac_prop, शून्य);
		अगर (local_mac)
			अवरोध;
	पूर्ण
	अगर (!local_mac)
		वापस ERR_PTR(-ENODEV);

	वापस vnet_find_or_create(local_mac, vdev);
पूर्ण

अटल काष्ठा ldc_channel_config vnet_ldc_cfg = अणु
	.event		= sunvnet_event_common,
	.mtu		= 64,
	.mode		= LDC_MODE_UNRELIABLE,
पूर्ण;

अटल काष्ठा vio_driver_ops vnet_vio_ops = अणु
	.send_attr		= sunvnet_send_attr_common,
	.handle_attr		= sunvnet_handle_attr_common,
	.handshake_complete	= sunvnet_handshake_complete_common,
पूर्ण;

स्थिर अक्षर *remote_macaddr_prop = "remote-mac-address";

अटल पूर्णांक vnet_port_probe(काष्ठा vio_dev *vdev, स्थिर काष्ठा vio_device_id *id)
अणु
	काष्ठा mdesc_handle *hp;
	काष्ठा vnet_port *port;
	अचिन्हित दीर्घ flags;
	काष्ठा vnet *vp;
	स्थिर u64 *rmac;
	पूर्णांक len, i, err, चयन_port;

	hp = mdesc_grab();

	vp = vnet_find_parent(hp, vdev->mp, vdev);
	अगर (IS_ERR(vp)) अणु
		pr_err("Cannot find port parent vnet\n");
		err = PTR_ERR(vp);
		जाओ err_out_put_mdesc;
	पूर्ण

	rmac = mdesc_get_property(hp, vdev->mp, remote_macaddr_prop, &len);
	err = -ENODEV;
	अगर (!rmac) अणु
		pr_err("Port lacks %s property\n", remote_macaddr_prop);
		जाओ err_out_put_mdesc;
	पूर्ण

	port = kzalloc(माप(*port), GFP_KERNEL);
	err = -ENOMEM;
	अगर (!port)
		जाओ err_out_put_mdesc;

	क्रम (i = 0; i < ETH_ALEN; i++)
		port->raddr[i] = (*rmac >> (5 - i) * 8) & 0xff;

	port->vp = vp;

	err = vio_driver_init(&port->vio, vdev, VDEV_NETWORK,
			      vnet_versions, ARRAY_SIZE(vnet_versions),
			      &vnet_vio_ops, vp->dev->name);
	अगर (err)
		जाओ err_out_मुक्त_port;

	err = vio_ldc_alloc(&port->vio, &vnet_ldc_cfg, port);
	अगर (err)
		जाओ err_out_मुक्त_port;

	netअगर_napi_add(port->vp->dev, &port->napi, sunvnet_poll_common,
		       NAPI_POLL_WEIGHT);

	INIT_HLIST_NODE(&port->hash);
	INIT_LIST_HEAD(&port->list);

	चयन_port = 0;
	अगर (mdesc_get_property(hp, vdev->mp, "switch-port", शून्य))
		चयन_port = 1;
	port->चयन_port = चयन_port;
	port->tso = true;
	port->tsolen = 0;

	spin_lock_irqsave(&vp->lock, flags);
	अगर (चयन_port)
		list_add_rcu(&port->list, &vp->port_list);
	अन्यथा
		list_add_tail_rcu(&port->list, &vp->port_list);
	hlist_add_head_rcu(&port->hash,
			   &vp->port_hash[vnet_hashfn(port->raddr)]);
	sunvnet_port_add_txq_common(port);
	spin_unlock_irqrestore(&vp->lock, flags);

	dev_set_drvdata(&vdev->dev, port);

	pr_info("%s: PORT ( remote-mac %pM%s )\n",
		vp->dev->name, port->raddr, चयन_port ? " switch-port" : "");

	समयr_setup(&port->clean_समयr, sunvnet_clean_समयr_expire_common, 0);

	napi_enable(&port->napi);
	vio_port_up(&port->vio);

	mdesc_release(hp);

	वापस 0;

err_out_मुक्त_port:
	kमुक्त(port);

err_out_put_mdesc:
	mdesc_release(hp);
	वापस err;
पूर्ण

अटल पूर्णांक vnet_port_हटाओ(काष्ठा vio_dev *vdev)
अणु
	काष्ठा vnet_port *port = dev_get_drvdata(&vdev->dev);

	अगर (port) अणु
		del_समयr_sync(&port->vio.समयr);

		napi_disable(&port->napi);

		list_del_rcu(&port->list);
		hlist_del_rcu(&port->hash);

		synchronize_rcu();
		del_समयr_sync(&port->clean_समयr);
		sunvnet_port_rm_txq_common(port);
		netअगर_napi_del(&port->napi);
		sunvnet_port_मुक्त_tx_bufs_common(port);
		vio_ldc_मुक्त(&port->vio);

		dev_set_drvdata(&vdev->dev, शून्य);

		kमुक्त(port);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vio_device_id vnet_port_match[] = अणु
	अणु
		.type = "vnet-port",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(vio, vnet_port_match);

अटल काष्ठा vio_driver vnet_port_driver = अणु
	.id_table	= vnet_port_match,
	.probe		= vnet_port_probe,
	.हटाओ		= vnet_port_हटाओ,
	.name		= "vnet_port",
पूर्ण;

अटल पूर्णांक __init vnet_init(व्योम)
अणु
	pr_info("%s\n", version);
	वापस vio_रेजिस्टर_driver(&vnet_port_driver);
पूर्ण

अटल व्योम __निकास vnet_निकास(व्योम)
अणु
	vio_unरेजिस्टर_driver(&vnet_port_driver);
	vnet_cleanup();
पूर्ण

module_init(vnet_init);
module_निकास(vnet_निकास);
