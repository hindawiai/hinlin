<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* ldmvsw.c: Sun4v LDOM Virtual Switch Driver.
 *
 * Copyright (C) 2016-2017 Oracle. All rights reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#अगर defined(CONFIG_IPV6)
#समावेश <linux/icmpv6.h>
#पूर्ण_अगर

#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/route.h>

#समावेश <यंत्र/vपन.स>
#समावेश <यंत्र/ldc.h>

/* This driver makes use of the common code in sunvnet_common.c */
#समावेश "sunvnet_common.h"

/* Length of समय beक्रमe we decide the hardware is hung,
 * and dev->tx_समयout() should be called to fix the problem.
 */
#घोषणा VSW_TX_TIMEOUT			(10 * HZ)

/* Static HW Addr used क्रम the network पूर्णांकerfaces representing vsw ports */
अटल u8 vsw_port_hwaddr[ETH_ALEN] = अणु0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFFपूर्ण;

#घोषणा DRV_MODULE_NAME		"ldmvsw"
#घोषणा DRV_MODULE_VERSION	"1.2"
#घोषणा DRV_MODULE_RELDATE	"March 4, 2017"

अटल अक्षर version[] =
	DRV_MODULE_NAME " " DRV_MODULE_VERSION " (" DRV_MODULE_RELDATE ")";
MODULE_AUTHOR("Oracle");
MODULE_DESCRIPTION("Sun4v LDOM Virtual Switch Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_MODULE_VERSION);

/* Ordered from largest major to lowest */
अटल काष्ठा vio_version vsw_versions[] = अणु
	अणु .major = 1, .minor = 8 पूर्ण,
	अणु .major = 1, .minor = 7 पूर्ण,
	अणु .major = 1, .minor = 6 पूर्ण,
	अणु .major = 1, .minor = 0 पूर्ण,
पूर्ण;

अटल व्योम vsw_get_drvinfo(काष्ठा net_device *dev,
			    काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_MODULE_NAME, माप(info->driver));
	strlcpy(info->version, DRV_MODULE_VERSION, माप(info->version));
पूर्ण

अटल u32 vsw_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा vnet_port *port = netdev_priv(dev);

	वापस port->vp->msg_enable;
पूर्ण

अटल व्योम vsw_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा vnet_port *port = netdev_priv(dev);

	port->vp->msg_enable = value;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops vsw_ethtool_ops = अणु
	.get_drvinfo		= vsw_get_drvinfo,
	.get_msglevel		= vsw_get_msglevel,
	.set_msglevel		= vsw_set_msglevel,
	.get_link		= ethtool_op_get_link,
पूर्ण;

अटल LIST_HEAD(vnet_list);
अटल DEFINE_MUTEX(vnet_list_mutex);

/* func arg to vnet_start_xmit_common() to get the proper tx port */
अटल काष्ठा vnet_port *vsw_tx_port_find(काष्ठा sk_buff *skb,
					  काष्ठा net_device *dev)
अणु
	काष्ठा vnet_port *port = netdev_priv(dev);

	वापस port;
पूर्ण

अटल u16 vsw_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			    काष्ठा net_device *sb_dev)
अणु
	काष्ठा vnet_port *port = netdev_priv(dev);

	अगर (!port)
		वापस 0;

	वापस port->q_index;
पूर्ण

/* Wrappers to common functions */
अटल netdev_tx_t vsw_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	वापस sunvnet_start_xmit_common(skb, dev, vsw_tx_port_find);
पूर्ण

अटल व्योम vsw_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा vnet_port *port = netdev_priv(dev);

	वापस sunvnet_set_rx_mode_common(dev, port->vp);
पूर्ण

पूर्णांक ldmvsw_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा vnet_port *port = netdev_priv(dev);
	काष्ठा vio_driver_state *vio = &port->vio;

	/* reset the channel */
	vio_link_state_change(vio, LDC_EVENT_RESET);
	vnet_port_reset(port);
	vio_port_up(vio);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ldmvsw_खोलो);

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम vsw_poll_controller(काष्ठा net_device *dev)
अणु
	काष्ठा vnet_port *port = netdev_priv(dev);

	वापस sunvnet_poll_controller_common(dev, port->vp);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops vsw_ops = अणु
	.nकरो_खोलो		= ldmvsw_खोलो,
	.nकरो_stop		= sunvnet_बंद_common,
	.nकरो_set_rx_mode	= vsw_set_rx_mode,
	.nकरो_set_mac_address	= sunvnet_set_mac_addr_common,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_tx_समयout		= sunvnet_tx_समयout_common,
	.nकरो_start_xmit		= vsw_start_xmit,
	.nकरो_select_queue	= vsw_select_queue,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller    = vsw_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर अक्षर *local_mac_prop = "local-mac-address";
अटल स्थिर अक्षर *cfg_handle_prop = "cfg-handle";

अटल काष्ठा vnet *vsw_get_vnet(काष्ठा mdesc_handle *hp,
				 u64 port_node,
				 u64 *handle)
अणु
	काष्ठा vnet *vp;
	काष्ठा vnet *iter;
	स्थिर u64 *local_mac = शून्य;
	स्थिर u64 *cfghandle = शून्य;
	u64 a;

	/* Get the parent भव-network-चयन macaddr and cfghandle */
	mdesc_क्रम_each_arc(a, hp, port_node, MDESC_ARC_TYPE_BACK) अणु
		u64 target = mdesc_arc_target(hp, a);
		स्थिर अक्षर *name;

		name = mdesc_get_property(hp, target, "name", शून्य);
		अगर (!name || म_भेद(name, "virtual-network-switch"))
			जारी;

		local_mac = mdesc_get_property(hp, target,
					       local_mac_prop, शून्य);
		cfghandle = mdesc_get_property(hp, target,
					       cfg_handle_prop, शून्य);
		अवरोध;
	पूर्ण
	अगर (!local_mac || !cfghandle)
		वापस ERR_PTR(-ENODEV);

	/* find or create associated vnet */
	vp = शून्य;
	mutex_lock(&vnet_list_mutex);
	list_क्रम_each_entry(iter, &vnet_list, list) अणु
		अगर (iter->local_mac == *local_mac) अणु
			vp = iter;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!vp) अणु
		vp = kzalloc(माप(*vp), GFP_KERNEL);
		अगर (unlikely(!vp)) अणु
			mutex_unlock(&vnet_list_mutex);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण

		spin_lock_init(&vp->lock);
		INIT_LIST_HEAD(&vp->port_list);
		INIT_LIST_HEAD(&vp->list);
		vp->local_mac = *local_mac;
		list_add(&vp->list, &vnet_list);
	पूर्ण

	mutex_unlock(&vnet_list_mutex);

	*handle = (u64)*cfghandle;

	वापस vp;
पूर्ण

अटल काष्ठा net_device *vsw_alloc_netdev(u8 hwaddr[],
					   काष्ठा vio_dev *vdev,
					   u64 handle,
					   u64 port_id)
अणु
	काष्ठा net_device *dev;
	काष्ठा vnet_port *port;
	पूर्णांक i;

	dev = alloc_etherdev_mqs(माप(*port), VNET_MAX_TXQS, 1);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);
	dev->needed_headroom = VNET_PACKET_SKIP + 8;
	dev->needed_tailroom = 8;

	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		dev->dev_addr[i] = hwaddr[i];
		dev->perm_addr[i] = dev->dev_addr[i];
	पूर्ण

	प्र_लिखो(dev->name, "vif%d.%d", (पूर्णांक)handle, (पूर्णांक)port_id);

	dev->netdev_ops = &vsw_ops;
	dev->ethtool_ops = &vsw_ethtool_ops;
	dev->watchकरोg_समयo = VSW_TX_TIMEOUT;

	dev->hw_features = NETIF_F_HW_CSUM | NETIF_F_SG;
	dev->features = dev->hw_features;

	/* MTU range: 68 - 65535 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = VNET_MAX_MTU;

	SET_NETDEV_DEV(dev, &vdev->dev);

	वापस dev;
पूर्ण

अटल काष्ठा ldc_channel_config vsw_ldc_cfg = अणु
	.event		= sunvnet_event_common,
	.mtu		= 64,
	.mode		= LDC_MODE_UNRELIABLE,
पूर्ण;

अटल काष्ठा vio_driver_ops vsw_vio_ops = अणु
	.send_attr		= sunvnet_send_attr_common,
	.handle_attr		= sunvnet_handle_attr_common,
	.handshake_complete	= sunvnet_handshake_complete_common,
पूर्ण;

अटल स्थिर अक्षर *remote_macaddr_prop = "remote-mac-address";
अटल स्थिर अक्षर *id_prop = "id";

अटल पूर्णांक vsw_port_probe(काष्ठा vio_dev *vdev, स्थिर काष्ठा vio_device_id *id)
अणु
	काष्ठा mdesc_handle *hp;
	काष्ठा vnet_port *port;
	अचिन्हित दीर्घ flags;
	काष्ठा vnet *vp;
	काष्ठा net_device *dev;
	स्थिर u64 *rmac;
	पूर्णांक len, i, err;
	स्थिर u64 *port_id;
	u64 handle;

	hp = mdesc_grab();

	rmac = mdesc_get_property(hp, vdev->mp, remote_macaddr_prop, &len);
	err = -ENODEV;
	अगर (!rmac) अणु
		pr_err("Port lacks %s property\n", remote_macaddr_prop);
		mdesc_release(hp);
		वापस err;
	पूर्ण

	port_id = mdesc_get_property(hp, vdev->mp, id_prop, शून्य);
	err = -ENODEV;
	अगर (!port_id) अणु
		pr_err("Port lacks %s property\n", id_prop);
		mdesc_release(hp);
		वापस err;
	पूर्ण

	/* Get (or create) the vnet associated with this port */
	vp = vsw_get_vnet(hp, vdev->mp, &handle);
	अगर (IS_ERR(vp)) अणु
		err = PTR_ERR(vp);
		pr_err("Failed to get vnet for vsw-port\n");
		mdesc_release(hp);
		वापस err;
	पूर्ण

	mdesc_release(hp);

	dev = vsw_alloc_netdev(vsw_port_hwaddr, vdev, handle, *port_id);
	अगर (IS_ERR(dev)) अणु
		err = PTR_ERR(dev);
		pr_err("Failed to alloc netdev for vsw-port\n");
		वापस err;
	पूर्ण

	port = netdev_priv(dev);

	INIT_LIST_HEAD(&port->list);

	क्रम (i = 0; i < ETH_ALEN; i++)
		port->raddr[i] = (*rmac >> (5 - i) * 8) & 0xff;

	port->vp = vp;
	port->dev = dev;
	port->चयन_port = 1;
	port->tso = false; /* no tso in vsw, misbehaves in bridge */
	port->tsolen = 0;

	/* Mark the port as beदीर्घing to ldmvsw which directs the
	 * the common code to use the net_device in the vnet_port
	 * rather than the net_device in the vnet (which is used
	 * by sunvnet). This bit is used by the VNET_PORT_TO_NET_DEVICE
	 * macro.
	 */
	port->vsw = 1;

	err = vio_driver_init(&port->vio, vdev, VDEV_NETWORK,
			      vsw_versions, ARRAY_SIZE(vsw_versions),
			      &vsw_vio_ops, dev->name);
	अगर (err)
		जाओ err_out_मुक्त_dev;

	err = vio_ldc_alloc(&port->vio, &vsw_ldc_cfg, port);
	अगर (err)
		जाओ err_out_मुक्त_dev;

	dev_set_drvdata(&vdev->dev, port);

	netअगर_napi_add(dev, &port->napi, sunvnet_poll_common,
		       NAPI_POLL_WEIGHT);

	spin_lock_irqsave(&vp->lock, flags);
	list_add_rcu(&port->list, &vp->port_list);
	spin_unlock_irqrestore(&vp->lock, flags);

	समयr_setup(&port->clean_समयr, sunvnet_clean_समयr_expire_common, 0);

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		pr_err("Cannot register net device, aborting\n");
		जाओ err_out_del_समयr;
	पूर्ण

	spin_lock_irqsave(&vp->lock, flags);
	sunvnet_port_add_txq_common(port);
	spin_unlock_irqrestore(&vp->lock, flags);

	napi_enable(&port->napi);
	vio_port_up(&port->vio);

	/* assure no carrier until we receive an LDC_EVENT_UP,
	 * even अगर the vsw config script tries to क्रमce us up
	 */
	netअगर_carrier_off(dev);

	netdev_info(dev, "LDOM vsw-port %pM\n", dev->dev_addr);

	pr_info("%s: PORT ( remote-mac %pM%s )\n", dev->name,
		port->raddr, " switch-port");

	वापस 0;

err_out_del_समयr:
	del_समयr_sync(&port->clean_समयr);
	list_del_rcu(&port->list);
	synchronize_rcu();
	netअगर_napi_del(&port->napi);
	dev_set_drvdata(&vdev->dev, शून्य);
	vio_ldc_मुक्त(&port->vio);

err_out_मुक्त_dev:
	मुक्त_netdev(dev);
	वापस err;
पूर्ण

अटल पूर्णांक vsw_port_हटाओ(काष्ठा vio_dev *vdev)
अणु
	काष्ठा vnet_port *port = dev_get_drvdata(&vdev->dev);
	अचिन्हित दीर्घ flags;

	अगर (port) अणु
		del_समयr_sync(&port->vio.समयr);
		del_समयr_sync(&port->clean_समयr);

		napi_disable(&port->napi);
		unरेजिस्टर_netdev(port->dev);

		list_del_rcu(&port->list);

		synchronize_rcu();
		spin_lock_irqsave(&port->vp->lock, flags);
		sunvnet_port_rm_txq_common(port);
		spin_unlock_irqrestore(&port->vp->lock, flags);
		netअगर_napi_del(&port->napi);
		sunvnet_port_मुक्त_tx_bufs_common(port);
		vio_ldc_मुक्त(&port->vio);

		dev_set_drvdata(&vdev->dev, शून्य);

		मुक्त_netdev(port->dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vsw_cleanup(व्योम)
अणु
	काष्ठा vnet *vp;

	/* just need to मुक्त up the vnet list */
	mutex_lock(&vnet_list_mutex);
	जबतक (!list_empty(&vnet_list)) अणु
		vp = list_first_entry(&vnet_list, काष्ठा vnet, list);
		list_del(&vp->list);
		/* vio_unरेजिस्टर_driver() should have cleaned up port_list */
		अगर (!list_empty(&vp->port_list))
			pr_err("Ports not removed by VIO subsystem!\n");
		kमुक्त(vp);
	पूर्ण
	mutex_unlock(&vnet_list_mutex);
पूर्ण

अटल स्थिर काष्ठा vio_device_id vsw_port_match[] = अणु
	अणु
		.type = "vsw-port",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(vio, vsw_port_match);

अटल काष्ठा vio_driver vsw_port_driver = अणु
	.id_table	= vsw_port_match,
	.probe		= vsw_port_probe,
	.हटाओ		= vsw_port_हटाओ,
	.name		= "vsw_port",
पूर्ण;

अटल पूर्णांक __init vsw_init(व्योम)
अणु
	pr_info("%s\n", version);
	वापस vio_रेजिस्टर_driver(&vsw_port_driver);
पूर्ण

अटल व्योम __निकास vsw_निकास(व्योम)
अणु
	vio_unरेजिस्टर_driver(&vsw_port_driver);
	vsw_cleanup();
पूर्ण

module_init(vsw_init);
module_निकास(vsw_निकास);
