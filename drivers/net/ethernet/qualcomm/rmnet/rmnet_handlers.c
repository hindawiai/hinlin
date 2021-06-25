<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2013-2018, The Linux Foundation. All rights reserved.
 *
 * RMNET Data ingress/egress handler
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/netdev_features.h>
#समावेश <linux/अगर_arp.h>
#समावेश <net/sock.h>
#समावेश "rmnet_private.h"
#समावेश "rmnet_config.h"
#समावेश "rmnet_vnd.h"
#समावेश "rmnet_map.h"
#समावेश "rmnet_handlers.h"

#घोषणा RMNET_IP_VERSION_4 0x40
#घोषणा RMNET_IP_VERSION_6 0x60

/* Helper Functions */

अटल व्योम rmnet_set_skb_proto(काष्ठा sk_buff *skb)
अणु
	चयन (skb->data[0] & 0xF0) अणु
	हाल RMNET_IP_VERSION_4:
		skb->protocol = htons(ETH_P_IP);
		अवरोध;
	हाल RMNET_IP_VERSION_6:
		skb->protocol = htons(ETH_P_IPV6);
		अवरोध;
	शेष:
		skb->protocol = htons(ETH_P_MAP);
		अवरोध;
	पूर्ण
पूर्ण

/* Generic handler */

अटल व्योम
rmnet_deliver_skb(काष्ठा sk_buff *skb)
अणु
	काष्ठा rmnet_priv *priv = netdev_priv(skb->dev);

	skb_reset_transport_header(skb);
	skb_reset_network_header(skb);
	rmnet_vnd_rx_fixup(skb, skb->dev);

	skb->pkt_type = PACKET_HOST;
	skb_set_mac_header(skb, 0);
	gro_cells_receive(&priv->gro_cells, skb);
पूर्ण

/* MAP handler */

अटल व्योम
__rmnet_map_ingress_handler(काष्ठा sk_buff *skb,
			    काष्ठा rmnet_port *port)
अणु
	काष्ठा rmnet_map_header *map_header = (व्योम *)skb->data;
	काष्ठा rmnet_endpoपूर्णांक *ep;
	u16 len, pad;
	u8 mux_id;

	अगर (map_header->flags & MAP_CMD_FLAG) अणु
		/* Packet contains a MAP command (not data) */
		अगर (port->data_क्रमmat & RMNET_FLAGS_INGRESS_MAP_COMMANDS)
			वापस rmnet_map_command(skb, port);

		जाओ मुक्त_skb;
	पूर्ण

	mux_id = map_header->mux_id;
	pad = map_header->flags & MAP_PAD_LEN_MASK;
	len = ntohs(map_header->pkt_len) - pad;

	अगर (mux_id >= RMNET_MAX_LOGICAL_EP)
		जाओ मुक्त_skb;

	ep = rmnet_get_endpoपूर्णांक(port, mux_id);
	अगर (!ep)
		जाओ मुक्त_skb;

	skb->dev = ep->egress_dev;

	/* Subtract MAP header */
	skb_pull(skb, माप(काष्ठा rmnet_map_header));
	rmnet_set_skb_proto(skb);

	अगर (port->data_क्रमmat & RMNET_FLAGS_INGRESS_MAP_CKSUMV4) अणु
		अगर (!rmnet_map_checksum_करोwnlink_packet(skb, len + pad))
			skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण

	skb_trim(skb, len);
	rmnet_deliver_skb(skb);
	वापस;

मुक्त_skb:
	kमुक्त_skb(skb);
पूर्ण

अटल व्योम
rmnet_map_ingress_handler(काष्ठा sk_buff *skb,
			  काष्ठा rmnet_port *port)
अणु
	काष्ठा sk_buff *skbn;

	अगर (skb->dev->type == ARPHRD_ETHER) अणु
		अगर (pskb_expand_head(skb, ETH_HLEN, 0, GFP_ATOMIC)) अणु
			kमुक्त_skb(skb);
			वापस;
		पूर्ण

		skb_push(skb, ETH_HLEN);
	पूर्ण

	अगर (port->data_क्रमmat & RMNET_FLAGS_INGRESS_DEAGGREGATION) अणु
		जबतक ((skbn = rmnet_map_deaggregate(skb, port)) != शून्य)
			__rmnet_map_ingress_handler(skbn, port);

		consume_skb(skb);
	पूर्ण अन्यथा अणु
		__rmnet_map_ingress_handler(skb, port);
	पूर्ण
पूर्ण

अटल पूर्णांक rmnet_map_egress_handler(काष्ठा sk_buff *skb,
				    काष्ठा rmnet_port *port, u8 mux_id,
				    काष्ठा net_device *orig_dev)
अणु
	पूर्णांक required_headroom, additional_header_len;
	काष्ठा rmnet_map_header *map_header;

	additional_header_len = 0;
	required_headroom = माप(काष्ठा rmnet_map_header);

	अगर (port->data_क्रमmat & RMNET_FLAGS_EGRESS_MAP_CKSUMV4) अणु
		additional_header_len = माप(काष्ठा rmnet_map_ul_csum_header);
		required_headroom += additional_header_len;
	पूर्ण

	अगर (skb_headroom(skb) < required_headroom) अणु
		अगर (pskb_expand_head(skb, required_headroom, 0, GFP_ATOMIC))
			वापस -ENOMEM;
	पूर्ण

	अगर (port->data_क्रमmat & RMNET_FLAGS_EGRESS_MAP_CKSUMV4)
		rmnet_map_checksum_uplink_packet(skb, orig_dev);

	map_header = rmnet_map_add_map_header(skb, additional_header_len, 0);
	अगर (!map_header)
		वापस -ENOMEM;

	map_header->mux_id = mux_id;

	skb->protocol = htons(ETH_P_MAP);

	वापस 0;
पूर्ण

अटल व्योम
rmnet_bridge_handler(काष्ठा sk_buff *skb, काष्ठा net_device *bridge_dev)
अणु
	अगर (skb_mac_header_was_set(skb))
		skb_push(skb, skb->mac_len);

	अगर (bridge_dev) अणु
		skb->dev = bridge_dev;
		dev_queue_xmit(skb);
	पूर्ण
पूर्ण

/* Ingress / Egress Entry Poपूर्णांकs */

/* Processes packet as per ingress data क्रमmat क्रम receiving device. Logical
 * endpoपूर्णांक is determined from packet inspection. Packet is then sent to the
 * egress device listed in the logical endpoपूर्णांक configuration.
 */
rx_handler_result_t rmnet_rx_handler(काष्ठा sk_buff **pskb)
अणु
	काष्ठा sk_buff *skb = *pskb;
	काष्ठा rmnet_port *port;
	काष्ठा net_device *dev;

	अगर (!skb)
		जाओ करोne;

	अगर (skb_linearize(skb)) अणु
		kमुक्त_skb(skb);
		जाओ करोne;
	पूर्ण

	अगर (skb->pkt_type == PACKET_LOOPBACK)
		वापस RX_HANDLER_PASS;

	dev = skb->dev;
	port = rmnet_get_port_rcu(dev);
	अगर (unlikely(!port)) अणु
		atomic_दीर्घ_inc(&skb->dev->rx_nohandler);
		kमुक्त_skb(skb);
		जाओ करोne;
	पूर्ण

	चयन (port->rmnet_mode) अणु
	हाल RMNET_EPMODE_VND:
		rmnet_map_ingress_handler(skb, port);
		अवरोध;
	हाल RMNET_EPMODE_BRIDGE:
		rmnet_bridge_handler(skb, port->bridge_ep);
		अवरोध;
	पूर्ण

करोne:
	वापस RX_HANDLER_CONSUMED;
पूर्ण

/* Modअगरies packet as per logical endpoपूर्णांक configuration and egress data क्रमmat
 * क्रम egress device configured in logical endpoपूर्णांक. Packet is then transmitted
 * on the egress device.
 */
व्योम rmnet_egress_handler(काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *orig_dev;
	काष्ठा rmnet_port *port;
	काष्ठा rmnet_priv *priv;
	u8 mux_id;

	sk_pacing_shअगरt_update(skb->sk, 8);

	orig_dev = skb->dev;
	priv = netdev_priv(orig_dev);
	skb->dev = priv->real_dev;
	mux_id = priv->mux_id;

	port = rmnet_get_port_rcu(skb->dev);
	अगर (!port)
		जाओ drop;

	अगर (rmnet_map_egress_handler(skb, port, mux_id, orig_dev))
		जाओ drop;

	rmnet_vnd_tx_fixup(skb, orig_dev);

	dev_queue_xmit(skb);
	वापस;

drop:
	this_cpu_inc(priv->pcpu_stats->stats.tx_drops);
	kमुक्त_skb(skb);
पूर्ण
