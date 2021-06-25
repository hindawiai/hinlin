<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2011-2014 Autronica Fire and Security AS
 *
 * Author(s):
 *	2011-2014 Arvid Brodin, arvid.brodin@alten.se
 *
 * Frame handler other utility functions क्रम HSR and PRP.
 */

#समावेश "hsr_slave.h"
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश "hsr_main.h"
#समावेश "hsr_device.h"
#समावेश "hsr_forward.h"
#समावेश "hsr_framereg.h"

bool hsr_invalid_dan_ingress_frame(__be16 protocol)
अणु
	वापस (protocol != htons(ETH_P_PRP) && protocol != htons(ETH_P_HSR));
पूर्ण

अटल rx_handler_result_t hsr_handle_frame(काष्ठा sk_buff **pskb)
अणु
	काष्ठा sk_buff *skb = *pskb;
	काष्ठा hsr_port *port;
	काष्ठा hsr_priv *hsr;
	__be16 protocol;

	/* Packets from dev_loopback_xmit() करो not have L2 header, bail out */
	अगर (unlikely(skb->pkt_type == PACKET_LOOPBACK))
		वापस RX_HANDLER_PASS;

	अगर (!skb_mac_header_was_set(skb)) अणु
		WARN_ONCE(1, "%s: skb invalid", __func__);
		वापस RX_HANDLER_PASS;
	पूर्ण

	port = hsr_port_get_rcu(skb->dev);
	अगर (!port)
		जाओ finish_pass;
	hsr = port->hsr;

	अगर (hsr_addr_is_self(port->hsr, eth_hdr(skb)->h_source)) अणु
		/* Directly समाप्त frames sent by ourselves */
		kमुक्त_skb(skb);
		जाओ finish_consume;
	पूर्ण

	/* For HSR, only tagged frames are expected (unless the device offloads
	 * HSR tag removal), but क्रम PRP there could be non tagged frames as
	 * well from Single attached nodes (SANs).
	 */
	protocol = eth_hdr(skb)->h_proto;

	अगर (!(port->dev->features & NETIF_F_HW_HSR_TAG_RM) &&
	    hsr->proto_ops->invalid_dan_ingress_frame &&
	    hsr->proto_ops->invalid_dan_ingress_frame(protocol))
		जाओ finish_pass;

	skb_push(skb, ETH_HLEN);
	skb_reset_mac_header(skb);
	अगर ((!hsr->prot_version && protocol == htons(ETH_P_PRP)) ||
	    protocol == htons(ETH_P_HSR))
		skb_set_network_header(skb, ETH_HLEN + HSR_HLEN);
	skb_reset_mac_len(skb);

	hsr_क्रमward_skb(skb, port);

finish_consume:
	वापस RX_HANDLER_CONSUMED;

finish_pass:
	वापस RX_HANDLER_PASS;
पूर्ण

bool hsr_port_exists(स्थिर काष्ठा net_device *dev)
अणु
	वापस rcu_access_poपूर्णांकer(dev->rx_handler) == hsr_handle_frame;
पूर्ण

अटल पूर्णांक hsr_check_dev_ok(काष्ठा net_device *dev,
			    काष्ठा netlink_ext_ack *extack)
अणु
	/* Don't allow HSR on non-ethernet like devices */
	अगर ((dev->flags & IFF_LOOPBACK) || dev->type != ARPHRD_ETHER ||
	    dev->addr_len != ETH_ALEN) अणु
		NL_SET_ERR_MSG_MOD(extack, "Cannot use loopback or non-ethernet device as HSR slave.");
		वापस -EINVAL;
	पूर्ण

	/* Don't allow enslaving hsr devices */
	अगर (is_hsr_master(dev)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Cannot create trees of HSR devices.");
		वापस -EINVAL;
	पूर्ण

	अगर (hsr_port_exists(dev)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "This device is already a HSR slave.");
		वापस -EINVAL;
	पूर्ण

	अगर (is_vlan_dev(dev)) अणु
		NL_SET_ERR_MSG_MOD(extack, "HSR on top of VLAN is not yet supported in this driver.");
		वापस -EINVAL;
	पूर्ण

	अगर (dev->priv_flags & IFF_DONT_BRIDGE) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "This device does not support bridging.");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* HSR over bonded devices has not been tested, but I'm not sure it
	 * won't work...
	 */

	वापस 0;
पूर्ण

/* Setup device to be added to the HSR bridge. */
अटल पूर्णांक hsr_portdev_setup(काष्ठा hsr_priv *hsr, काष्ठा net_device *dev,
			     काष्ठा hsr_port *port,
			     काष्ठा netlink_ext_ack *extack)

अणु
	काष्ठा net_device *hsr_dev;
	काष्ठा hsr_port *master;
	पूर्णांक res;

	res = dev_set_promiscuity(dev, 1);
	अगर (res)
		वापस res;

	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	hsr_dev = master->dev;

	res = netdev_upper_dev_link(dev, hsr_dev, extack);
	अगर (res)
		जाओ fail_upper_dev_link;

	res = netdev_rx_handler_रेजिस्टर(dev, hsr_handle_frame, port);
	अगर (res)
		जाओ fail_rx_handler;
	dev_disable_lro(dev);

	वापस 0;

fail_rx_handler:
	netdev_upper_dev_unlink(dev, hsr_dev);
fail_upper_dev_link:
	dev_set_promiscuity(dev, -1);
	वापस res;
पूर्ण

पूर्णांक hsr_add_port(काष्ठा hsr_priv *hsr, काष्ठा net_device *dev,
		 क्रमागत hsr_port_type type, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा hsr_port *port, *master;
	पूर्णांक res;

	अगर (type != HSR_PT_MASTER) अणु
		res = hsr_check_dev_ok(dev, extack);
		अगर (res)
			वापस res;
	पूर्ण

	port = hsr_port_get_hsr(hsr, type);
	अगर (port)
		वापस -EBUSY;	/* This port alपढ़ोy exists */

	port = kzalloc(माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;

	port->hsr = hsr;
	port->dev = dev;
	port->type = type;

	अगर (type != HSR_PT_MASTER) अणु
		res = hsr_portdev_setup(hsr, dev, port, extack);
		अगर (res)
			जाओ fail_dev_setup;
	पूर्ण

	list_add_tail_rcu(&port->port_list, &hsr->ports);
	synchronize_rcu();

	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	netdev_update_features(master->dev);
	dev_set_mtu(master->dev, hsr_get_max_mtu(hsr));

	वापस 0;

fail_dev_setup:
	kमुक्त(port);
	वापस res;
पूर्ण

व्योम hsr_del_port(काष्ठा hsr_port *port)
अणु
	काष्ठा hsr_priv *hsr;
	काष्ठा hsr_port *master;

	hsr = port->hsr;
	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	list_del_rcu(&port->port_list);

	अगर (port != master) अणु
		netdev_update_features(master->dev);
		dev_set_mtu(master->dev, hsr_get_max_mtu(hsr));
		netdev_rx_handler_unरेजिस्टर(port->dev);
		dev_set_promiscuity(port->dev, -1);
		netdev_upper_dev_unlink(port->dev, master->dev);
	पूर्ण

	synchronize_rcu();

	kमुक्त(port);
पूर्ण
