<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 Pengutronix, Juergen Borleis <jbe@pengutronix.de>
 */
#समावेश <linux/dsa/lan9303.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>

#समावेश "dsa_priv.h"

/* To define the outgoing port and to discover the incoming port a regular
 * VLAN tag is used by the LAN9303. But its VID meaning is 'special':
 *
 *       Dest MAC       Src MAC        TAG    Type
 * ...| 1 2 3 4 5 6 | 1 2 3 4 5 6 | 1 2 3 4 | 1 2 |...
 *                                |<------->|
 * TAG:
 *    |<------------->|
 *    |  1  2 | 3  4  |
 *      TPID    VID
 *     0x8100
 *
 * VID bit 3 indicates a request क्रम an ALR lookup.
 *
 * If VID bit 3 is zero, then bits 0 and 1 specअगरy the destination port
 * (0, 1, 2) or broadcast (3) or the source port (1, 2).
 *
 * VID bit 4 is used to specअगरy अगर the STP port state should be overridden.
 * Required when no क्रमwarding between the बाह्यal ports should happen.
 */

#घोषणा LAN9303_TAG_LEN 4
# define LAN9303_TAG_TX_USE_ALR BIT(3)
# define LAN9303_TAG_TX_STP_OVERRIDE BIT(4)
# define LAN9303_TAG_RX_IGMP BIT(3)
# define LAN9303_TAG_RX_STP BIT(4)
# define LAN9303_TAG_RX_TRAPPED_TO_CPU (LAN9303_TAG_RX_IGMP | \
					LAN9303_TAG_RX_STP)

/* Decide whether to transmit using ALR lookup, or transmit directly to
 * port using tag. ALR learning is perक्रमmed only when using ALR lookup.
 * If the two बाह्यal ports are bridged and the frame is unicast,
 * then use ALR lookup to allow ALR learning on CPU port.
 * Otherwise transmit directly to port with STP state override.
 * See also: lan9303_separate_ports() and lan9303.pdf 6.4.10.1
 */
अटल पूर्णांक lan9303_xmit_use_arl(काष्ठा dsa_port *dp, u8 *dest_addr)
अणु
	काष्ठा lan9303 *chip = dp->ds->priv;

	वापस chip->is_bridged && !is_multicast_ether_addr(dest_addr);
पूर्ण

अटल काष्ठा sk_buff *lan9303_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	__be16 *lan9303_tag;
	u16 tag;

	/* provide 'LAN9303_TAG_LEN' bytes additional space */
	skb_push(skb, LAN9303_TAG_LEN);

	/* make room between MACs and Ether-Type */
	स_हटाओ(skb->data, skb->data + LAN9303_TAG_LEN, 2 * ETH_ALEN);

	lan9303_tag = (__be16 *)(skb->data + 2 * ETH_ALEN);
	tag = lan9303_xmit_use_arl(dp, skb->data) ?
		LAN9303_TAG_TX_USE_ALR :
		dp->index | LAN9303_TAG_TX_STP_OVERRIDE;
	lan9303_tag[0] = htons(ETH_P_8021Q);
	lan9303_tag[1] = htons(tag);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *lan9303_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				   काष्ठा packet_type *pt)
अणु
	__be16 *lan9303_tag;
	u16 lan9303_tag1;
	अचिन्हित पूर्णांक source_port;

	अगर (unlikely(!pskb_may_pull(skb, LAN9303_TAG_LEN))) अणु
		dev_warn_ratelimited(&dev->dev,
				     "Dropping packet, cannot pull\n");
		वापस शून्य;
	पूर्ण

	/* '->data' poपूर्णांकs पूर्णांकo the middle of our special VLAN tag inक्रमmation:
	 *
	 * ~ MAC src   | 0x81 | 0x00 | 0xyy | 0xzz | ether type
	 *                           ^
	 *                        ->data
	 */
	lan9303_tag = (__be16 *)(skb->data - 2);

	अगर (lan9303_tag[0] != htons(ETH_P_8021Q)) अणु
		dev_warn_ratelimited(&dev->dev, "Dropping packet due to invalid VLAN marker\n");
		वापस शून्य;
	पूर्ण

	lan9303_tag1 = ntohs(lan9303_tag[1]);
	source_port = lan9303_tag1 & 0x3;

	skb->dev = dsa_master_find_slave(dev, 0, source_port);
	अगर (!skb->dev) अणु
		dev_warn_ratelimited(&dev->dev, "Dropping packet due to invalid source port\n");
		वापस शून्य;
	पूर्ण

	/* हटाओ the special VLAN tag between the MAC addresses
	 * and the current ethertype field.
	 */
	skb_pull_rcsum(skb, 2 + 2);
	स_हटाओ(skb->data - ETH_HLEN, skb->data - (ETH_HLEN + LAN9303_TAG_LEN),
		2 * ETH_ALEN);
	skb->offload_fwd_mark = !(lan9303_tag1 & LAN9303_TAG_RX_TRAPPED_TO_CPU);

	वापस skb;
पूर्ण

अटल स्थिर काष्ठा dsa_device_ops lan9303_netdev_ops = अणु
	.name = "lan9303",
	.proto	= DSA_TAG_PROTO_LAN9303,
	.xmit = lan9303_xmit,
	.rcv = lan9303_rcv,
	.overhead = LAN9303_TAG_LEN,
पूर्ण;

MODULE_LICENSE("GPL");
MODULE_ALIAS_DSA_TAG_DRIVER(DSA_TAG_PROTO_LAN9303);

module_dsa_tag_driver(lan9303_netdev_ops);
