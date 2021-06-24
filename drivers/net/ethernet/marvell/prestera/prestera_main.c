<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2019-2020 Marvell International Ltd. All rights reserved */

#समावेश <linux/etherdevice.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/netdev_features.h>
#समावेश <linux/of.h>
#समावेश <linux/of_net.h>

#समावेश "prestera.h"
#समावेश "prestera_hw.h"
#समावेश "prestera_rxtx.h"
#समावेश "prestera_devlink.h"
#समावेश "prestera_ethtool.h"
#समावेश "prestera_switchdev.h"

#घोषणा PRESTERA_MTU_DEFAULT	1536

#घोषणा PRESTERA_STATS_DELAY_MS	1000

#घोषणा PRESTERA_MAC_ADDR_NUM_MAX	255

अटल काष्ठा workqueue_काष्ठा *prestera_wq;

पूर्णांक prestera_port_pvid_set(काष्ठा prestera_port *port, u16 vid)
अणु
	क्रमागत prestera_accept_frm_type frm_type;
	पूर्णांक err;

	frm_type = PRESTERA_ACCEPT_FRAME_TYPE_TAGGED;

	अगर (vid) अणु
		err = prestera_hw_vlan_port_vid_set(port, vid);
		अगर (err)
			वापस err;

		frm_type = PRESTERA_ACCEPT_FRAME_TYPE_ALL;
	पूर्ण

	err = prestera_hw_port_accept_frm_type(port, frm_type);
	अगर (err && frm_type == PRESTERA_ACCEPT_FRAME_TYPE_ALL)
		prestera_hw_vlan_port_vid_set(port, port->pvid);

	port->pvid = vid;
	वापस 0;
पूर्ण

काष्ठा prestera_port *prestera_port_find_by_hwid(काष्ठा prestera_चयन *sw,
						 u32 dev_id, u32 hw_id)
अणु
	काष्ठा prestera_port *port = शून्य;

	पढ़ो_lock(&sw->port_list_lock);
	list_क्रम_each_entry(port, &sw->port_list, list) अणु
		अगर (port->dev_id == dev_id && port->hw_id == hw_id)
			अवरोध;
	पूर्ण
	पढ़ो_unlock(&sw->port_list_lock);

	वापस port;
पूर्ण

काष्ठा prestera_port *prestera_find_port(काष्ठा prestera_चयन *sw, u32 id)
अणु
	काष्ठा prestera_port *port = शून्य;

	पढ़ो_lock(&sw->port_list_lock);
	list_क्रम_each_entry(port, &sw->port_list, list) अणु
		अगर (port->id == id)
			अवरोध;
	पूर्ण
	पढ़ो_unlock(&sw->port_list_lock);

	वापस port;
पूर्ण

अटल पूर्णांक prestera_port_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा prestera_port *port = netdev_priv(dev);
	पूर्णांक err;

	err = prestera_hw_port_state_set(port, true);
	अगर (err)
		वापस err;

	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक prestera_port_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा prestera_port *port = netdev_priv(dev);

	netअगर_stop_queue(dev);

	वापस prestera_hw_port_state_set(port, false);
पूर्ण

अटल netdev_tx_t prestera_port_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev)
अणु
	वापस prestera_rxtx_xmit(netdev_priv(dev), skb);
पूर्ण

अटल पूर्णांक prestera_is_valid_mac_addr(काष्ठा prestera_port *port, u8 *addr)
अणु
	अगर (!is_valid_ether_addr(addr))
		वापस -EADDRNOTAVAIL;

	/* firmware requires that port's MAC address contains first 5 bytes
	 * of the base MAC address
	 */
	अगर (स_भेद(port->sw->base_mac, addr, ETH_ALEN - 1))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक prestera_port_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा prestera_port *port = netdev_priv(dev);
	काष्ठा sockaddr *addr = p;
	पूर्णांक err;

	err = prestera_is_valid_mac_addr(port, addr->sa_data);
	अगर (err)
		वापस err;

	err = prestera_hw_port_mac_set(port, addr->sa_data);
	अगर (err)
		वापस err;

	ether_addr_copy(dev->dev_addr, addr->sa_data);

	वापस 0;
पूर्ण

अटल पूर्णांक prestera_port_change_mtu(काष्ठा net_device *dev, पूर्णांक mtu)
अणु
	काष्ठा prestera_port *port = netdev_priv(dev);
	पूर्णांक err;

	err = prestera_hw_port_mtu_set(port, mtu);
	अगर (err)
		वापस err;

	dev->mtu = mtu;

	वापस 0;
पूर्ण

अटल व्योम prestera_port_get_stats64(काष्ठा net_device *dev,
				      काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा prestera_port *port = netdev_priv(dev);
	काष्ठा prestera_port_stats *port_stats = &port->cached_hw_stats.stats;

	stats->rx_packets = port_stats->broadcast_frames_received +
				port_stats->multicast_frames_received +
				port_stats->unicast_frames_received;

	stats->tx_packets = port_stats->broadcast_frames_sent +
				port_stats->multicast_frames_sent +
				port_stats->unicast_frames_sent;

	stats->rx_bytes = port_stats->good_octets_received;

	stats->tx_bytes = port_stats->good_octets_sent;

	stats->rx_errors = port_stats->rx_error_frame_received;
	stats->tx_errors = port_stats->mac_trans_error;

	stats->rx_dropped = port_stats->buffer_overrun;
	stats->tx_dropped = 0;

	stats->multicast = port_stats->multicast_frames_received;
	stats->collisions = port_stats->excessive_collision;

	stats->rx_crc_errors = port_stats->bad_crc;
पूर्ण

अटल व्योम prestera_port_get_hw_stats(काष्ठा prestera_port *port)
अणु
	prestera_hw_port_stats_get(port, &port->cached_hw_stats.stats);
पूर्ण

अटल व्योम prestera_port_stats_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा prestera_port *port =
		container_of(work, काष्ठा prestera_port,
			     cached_hw_stats.caching_dw.work);

	prestera_port_get_hw_stats(port);

	queue_delayed_work(prestera_wq, &port->cached_hw_stats.caching_dw,
			   msecs_to_jअगरfies(PRESTERA_STATS_DELAY_MS));
पूर्ण

अटल स्थिर काष्ठा net_device_ops prestera_netdev_ops = अणु
	.nकरो_खोलो = prestera_port_खोलो,
	.nकरो_stop = prestera_port_बंद,
	.nकरो_start_xmit = prestera_port_xmit,
	.nकरो_change_mtu = prestera_port_change_mtu,
	.nकरो_get_stats64 = prestera_port_get_stats64,
	.nकरो_set_mac_address = prestera_port_set_mac_address,
	.nकरो_get_devlink_port = prestera_devlink_get_port,
पूर्ण;

पूर्णांक prestera_port_स्वतःneg_set(काष्ठा prestera_port *port, bool enable,
			      u64 adver_link_modes, u8 adver_fec)
अणु
	bool refresh = false;
	u64 link_modes;
	पूर्णांक err;
	u8 fec;

	अगर (port->caps.type != PRESTERA_PORT_TYPE_TP)
		वापस enable ? -EINVAL : 0;

	अगर (!enable)
		जाओ set_स्वतःneg;

	link_modes = port->caps.supp_link_modes & adver_link_modes;
	fec = port->caps.supp_fec & adver_fec;

	अगर (!link_modes && !fec)
		वापस -EOPNOTSUPP;

	अगर (link_modes && port->adver_link_modes != link_modes) अणु
		port->adver_link_modes = link_modes;
		refresh = true;
	पूर्ण

	अगर (fec && port->adver_fec != fec) अणु
		port->adver_fec = fec;
		refresh = true;
	पूर्ण

set_स्वतःneg:
	अगर (port->स्वतःneg == enable && !refresh)
		वापस 0;

	err = prestera_hw_port_स्वतःneg_set(port, enable, port->adver_link_modes,
					   port->adver_fec);
	अगर (err)
		वापस err;

	port->स्वतःneg = enable;

	वापस 0;
पूर्ण

अटल व्योम prestera_port_list_add(काष्ठा prestera_port *port)
अणु
	ग_लिखो_lock(&port->sw->port_list_lock);
	list_add(&port->list, &port->sw->port_list);
	ग_लिखो_unlock(&port->sw->port_list_lock);
पूर्ण

अटल व्योम prestera_port_list_del(काष्ठा prestera_port *port)
अणु
	ग_लिखो_lock(&port->sw->port_list_lock);
	list_del(&port->list);
	ग_लिखो_unlock(&port->sw->port_list_lock);
पूर्ण

अटल पूर्णांक prestera_port_create(काष्ठा prestera_चयन *sw, u32 id)
अणु
	काष्ठा prestera_port *port;
	काष्ठा net_device *dev;
	पूर्णांक err;

	dev = alloc_etherdev(माप(*port));
	अगर (!dev)
		वापस -ENOMEM;

	port = netdev_priv(dev);

	INIT_LIST_HEAD(&port->vlans_list);
	port->pvid = PRESTERA_DEFAULT_VID;
	port->dev = dev;
	port->id = id;
	port->sw = sw;

	err = prestera_hw_port_info_get(port, &port->dev_id, &port->hw_id,
					&port->fp_id);
	अगर (err) अणु
		dev_err(prestera_dev(sw), "Failed to get port(%u) info\n", id);
		जाओ err_port_info_get;
	पूर्ण

	err = prestera_devlink_port_रेजिस्टर(port);
	अगर (err)
		जाओ err_dl_port_रेजिस्टर;

	dev->features |= NETIF_F_NETNS_LOCAL;
	dev->netdev_ops = &prestera_netdev_ops;
	dev->ethtool_ops = &prestera_ethtool_ops;

	netअगर_carrier_off(dev);

	dev->mtu = min_t(अचिन्हित पूर्णांक, sw->mtu_max, PRESTERA_MTU_DEFAULT);
	dev->min_mtu = sw->mtu_min;
	dev->max_mtu = sw->mtu_max;

	err = prestera_hw_port_mtu_set(port, dev->mtu);
	अगर (err) अणु
		dev_err(prestera_dev(sw), "Failed to set port(%u) mtu(%d)\n",
			id, dev->mtu);
		जाओ err_port_init;
	पूर्ण

	अगर (port->fp_id >= PRESTERA_MAC_ADDR_NUM_MAX) अणु
		err = -EINVAL;
		जाओ err_port_init;
	पूर्ण

	/* firmware requires that port's MAC address consist of the first
	 * 5 bytes of the base MAC address
	 */
	स_नकल(dev->dev_addr, sw->base_mac, dev->addr_len - 1);
	dev->dev_addr[dev->addr_len - 1] = port->fp_id;

	err = prestera_hw_port_mac_set(port, dev->dev_addr);
	अगर (err) अणु
		dev_err(prestera_dev(sw), "Failed to set port(%u) mac addr\n", id);
		जाओ err_port_init;
	पूर्ण

	err = prestera_hw_port_cap_get(port, &port->caps);
	अगर (err) अणु
		dev_err(prestera_dev(sw), "Failed to get port(%u) caps\n", id);
		जाओ err_port_init;
	पूर्ण

	port->adver_fec = BIT(PRESTERA_PORT_FEC_OFF);
	prestera_port_स्वतःneg_set(port, true, port->caps.supp_link_modes,
				  port->caps.supp_fec);

	err = prestera_hw_port_state_set(port, false);
	अगर (err) अणु
		dev_err(prestera_dev(sw), "Failed to set port(%u) down\n", id);
		जाओ err_port_init;
	पूर्ण

	err = prestera_rxtx_port_init(port);
	अगर (err)
		जाओ err_port_init;

	INIT_DELAYED_WORK(&port->cached_hw_stats.caching_dw,
			  &prestera_port_stats_update);

	prestera_port_list_add(port);

	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ err_रेजिस्टर_netdev;

	prestera_devlink_port_set(port);

	वापस 0;

err_रेजिस्टर_netdev:
	prestera_port_list_del(port);
err_port_init:
	prestera_devlink_port_unरेजिस्टर(port);
err_dl_port_रेजिस्टर:
err_port_info_get:
	मुक्त_netdev(dev);
	वापस err;
पूर्ण

अटल व्योम prestera_port_destroy(काष्ठा prestera_port *port)
अणु
	काष्ठा net_device *dev = port->dev;

	cancel_delayed_work_sync(&port->cached_hw_stats.caching_dw);
	prestera_devlink_port_clear(port);
	unरेजिस्टर_netdev(dev);
	prestera_port_list_del(port);
	prestera_devlink_port_unरेजिस्टर(port);
	मुक्त_netdev(dev);
पूर्ण

अटल व्योम prestera_destroy_ports(काष्ठा prestera_चयन *sw)
अणु
	काष्ठा prestera_port *port, *पंचांगp;

	list_क्रम_each_entry_safe(port, पंचांगp, &sw->port_list, list)
		prestera_port_destroy(port);
पूर्ण

अटल पूर्णांक prestera_create_ports(काष्ठा prestera_चयन *sw)
अणु
	काष्ठा prestera_port *port, *पंचांगp;
	u32 port_idx;
	पूर्णांक err;

	क्रम (port_idx = 0; port_idx < sw->port_count; port_idx++) अणु
		err = prestera_port_create(sw, port_idx);
		अगर (err)
			जाओ err_port_create;
	पूर्ण

	वापस 0;

err_port_create:
	list_क्रम_each_entry_safe(port, पंचांगp, &sw->port_list, list)
		prestera_port_destroy(port);

	वापस err;
पूर्ण

अटल व्योम prestera_port_handle_event(काष्ठा prestera_चयन *sw,
				       काष्ठा prestera_event *evt, व्योम *arg)
अणु
	काष्ठा delayed_work *caching_dw;
	काष्ठा prestera_port *port;

	port = prestera_find_port(sw, evt->port_evt.port_id);
	अगर (!port || !port->dev)
		वापस;

	caching_dw = &port->cached_hw_stats.caching_dw;

	अगर (evt->id == PRESTERA_PORT_EVENT_STATE_CHANGED) अणु
		अगर (evt->port_evt.data.oper_state) अणु
			netअगर_carrier_on(port->dev);
			अगर (!delayed_work_pending(caching_dw))
				queue_delayed_work(prestera_wq, caching_dw, 0);
		पूर्ण अन्यथा अगर (netअगर_running(port->dev) &&
			   netअगर_carrier_ok(port->dev)) अणु
			netअगर_carrier_off(port->dev);
			अगर (delayed_work_pending(caching_dw))
				cancel_delayed_work(caching_dw);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक prestera_event_handlers_रेजिस्टर(काष्ठा prestera_चयन *sw)
अणु
	वापस prestera_hw_event_handler_रेजिस्टर(sw, PRESTERA_EVENT_TYPE_PORT,
						  prestera_port_handle_event,
						  शून्य);
पूर्ण

अटल व्योम prestera_event_handlers_unरेजिस्टर(काष्ठा prestera_चयन *sw)
अणु
	prestera_hw_event_handler_unरेजिस्टर(sw, PRESTERA_EVENT_TYPE_PORT,
					     prestera_port_handle_event);
पूर्ण

अटल पूर्णांक prestera_चयन_set_base_mac_addr(काष्ठा prestera_चयन *sw)
अणु
	काष्ठा device_node *base_mac_np;
	काष्ठा device_node *np;
	पूर्णांक ret;

	np = of_find_compatible_node(शून्य, शून्य, "marvell,prestera");
	base_mac_np = of_parse_phandle(np, "base-mac-provider", 0);

	ret = of_get_mac_address(base_mac_np, sw->base_mac);
	अगर (ret) अणु
		eth_अक्रमom_addr(sw->base_mac);
		dev_info(prestera_dev(sw), "using random base mac address\n");
	पूर्ण
	of_node_put(base_mac_np);

	वापस prestera_hw_चयन_mac_set(sw, sw->base_mac);
पूर्ण

bool prestera_netdev_check(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->netdev_ops == &prestera_netdev_ops;
पूर्ण

अटल पूर्णांक prestera_lower_dev_walk(काष्ठा net_device *dev,
				   काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा prestera_port **pport = (काष्ठा prestera_port **)priv->data;

	अगर (prestera_netdev_check(dev)) अणु
		*pport = netdev_priv(dev);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा prestera_port *prestera_port_dev_lower_find(काष्ठा net_device *dev)
अणु
	काष्ठा prestera_port *port = शून्य;
	काष्ठा netdev_nested_priv priv = अणु
		.data = (व्योम *)&port,
	पूर्ण;

	अगर (prestera_netdev_check(dev))
		वापस netdev_priv(dev);

	netdev_walk_all_lower_dev(dev, prestera_lower_dev_walk, &priv);

	वापस port;
पूर्ण

अटल पूर्णांक prestera_netdev_port_event(काष्ठा net_device *dev,
				      अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	चयन (event) अणु
	हाल NETDEV_PRECHANGEUPPER:
	हाल NETDEV_CHANGEUPPER:
		वापस prestera_bridge_port_event(dev, event, ptr);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक prestera_netdev_event_handler(काष्ठा notअगरier_block *nb,
					 अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	पूर्णांक err = 0;

	अगर (prestera_netdev_check(dev))
		err = prestera_netdev_port_event(dev, event, ptr);

	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

अटल पूर्णांक prestera_netdev_event_handler_रेजिस्टर(काष्ठा prestera_चयन *sw)
अणु
	sw->netdev_nb.notअगरier_call = prestera_netdev_event_handler;

	वापस रेजिस्टर_netdevice_notअगरier(&sw->netdev_nb);
पूर्ण

अटल व्योम prestera_netdev_event_handler_unरेजिस्टर(काष्ठा prestera_चयन *sw)
अणु
	unरेजिस्टर_netdevice_notअगरier(&sw->netdev_nb);
पूर्ण

अटल पूर्णांक prestera_चयन_init(काष्ठा prestera_चयन *sw)
अणु
	पूर्णांक err;

	err = prestera_hw_चयन_init(sw);
	अगर (err) अणु
		dev_err(prestera_dev(sw), "Failed to init Switch device\n");
		वापस err;
	पूर्ण

	rwlock_init(&sw->port_list_lock);
	INIT_LIST_HEAD(&sw->port_list);

	err = prestera_चयन_set_base_mac_addr(sw);
	अगर (err)
		वापस err;

	err = prestera_netdev_event_handler_रेजिस्टर(sw);
	अगर (err)
		वापस err;

	err = prestera_चयनdev_init(sw);
	अगर (err)
		जाओ err_swdev_रेजिस्टर;

	err = prestera_rxtx_चयन_init(sw);
	अगर (err)
		जाओ err_rxtx_रेजिस्टर;

	err = prestera_event_handlers_रेजिस्टर(sw);
	अगर (err)
		जाओ err_handlers_रेजिस्टर;

	err = prestera_devlink_रेजिस्टर(sw);
	अगर (err)
		जाओ err_dl_रेजिस्टर;

	err = prestera_create_ports(sw);
	अगर (err)
		जाओ err_ports_create;

	वापस 0;

err_ports_create:
	prestera_devlink_unरेजिस्टर(sw);
err_dl_रेजिस्टर:
	prestera_event_handlers_unरेजिस्टर(sw);
err_handlers_रेजिस्टर:
	prestera_rxtx_चयन_fini(sw);
err_rxtx_रेजिस्टर:
	prestera_चयनdev_fini(sw);
err_swdev_रेजिस्टर:
	prestera_netdev_event_handler_unरेजिस्टर(sw);
	prestera_hw_चयन_fini(sw);

	वापस err;
पूर्ण

अटल व्योम prestera_चयन_fini(काष्ठा prestera_चयन *sw)
अणु
	prestera_destroy_ports(sw);
	prestera_devlink_unरेजिस्टर(sw);
	prestera_event_handlers_unरेजिस्टर(sw);
	prestera_rxtx_चयन_fini(sw);
	prestera_चयनdev_fini(sw);
	prestera_netdev_event_handler_unरेजिस्टर(sw);
	prestera_hw_चयन_fini(sw);
पूर्ण

पूर्णांक prestera_device_रेजिस्टर(काष्ठा prestera_device *dev)
अणु
	काष्ठा prestera_चयन *sw;
	पूर्णांक err;

	sw = prestera_devlink_alloc();
	अगर (!sw)
		वापस -ENOMEM;

	dev->priv = sw;
	sw->dev = dev;

	err = prestera_चयन_init(sw);
	अगर (err) अणु
		prestera_devlink_मुक्त(sw);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(prestera_device_रेजिस्टर);

व्योम prestera_device_unरेजिस्टर(काष्ठा prestera_device *dev)
अणु
	काष्ठा prestera_चयन *sw = dev->priv;

	prestera_चयन_fini(sw);
	prestera_devlink_मुक्त(sw);
पूर्ण
EXPORT_SYMBOL(prestera_device_unरेजिस्टर);

अटल पूर्णांक __init prestera_module_init(व्योम)
अणु
	prestera_wq = alloc_workqueue("prestera", 0, 0);
	अगर (!prestera_wq)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम __निकास prestera_module_निकास(व्योम)
अणु
	destroy_workqueue(prestera_wq);
पूर्ण

module_init(prestera_module_init);
module_निकास(prestera_module_निकास);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Marvell Prestera switch driver");
