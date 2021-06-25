<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * net/dsa/tag_ksz.c - Microchip KSZ Switch tag क्रमmat handling
 * Copyright (c) 2017 Microchip Technology
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <net/dsa.h>
#समावेश "dsa_priv.h"

/* Typically only one byte is used क्रम tail tag. */
#घोषणा KSZ_EGRESS_TAG_LEN		1
#घोषणा KSZ_INGRESS_TAG_LEN		1

अटल काष्ठा sk_buff *ksz_common_rcv(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev,
				      अचिन्हित पूर्णांक port, अचिन्हित पूर्णांक len)
अणु
	skb->dev = dsa_master_find_slave(dev, 0, port);
	अगर (!skb->dev)
		वापस शून्य;

	pskb_trim_rcsum(skb, skb->len - len);

	skb->offload_fwd_mark = true;

	वापस skb;
पूर्ण

/*
 * For Ingress (Host -> KSZ8795), 1 byte is added beक्रमe FCS.
 * ---------------------------------------------------------------------------
 * DA(6bytes)|SA(6bytes)|....|Data(nbytes)|tag(1byte)|FCS(4bytes)
 * ---------------------------------------------------------------------------
 * tag : each bit represents port (eg, 0x01=port1, 0x02=port2, 0x10=port5)
 *
 * For Egress (KSZ8795 -> Host), 1 byte is added beक्रमe FCS.
 * ---------------------------------------------------------------------------
 * DA(6bytes)|SA(6bytes)|....|Data(nbytes)|tag0(1byte)|FCS(4bytes)
 * ---------------------------------------------------------------------------
 * tag0 : zero-based value represents port
 *	  (eg, 0x00=port1, 0x02=port3, 0x06=port7)
 */

#घोषणा KSZ8795_TAIL_TAG_OVERRIDE	BIT(6)
#घोषणा KSZ8795_TAIL_TAG_LOOKUP		BIT(7)

अटल काष्ठा sk_buff *ksz8795_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	u8 *tag;
	u8 *addr;

	/* Tag encoding */
	tag = skb_put(skb, KSZ_INGRESS_TAG_LEN);
	addr = skb_mac_header(skb);

	*tag = 1 << dp->index;
	अगर (is_link_local_ether_addr(addr))
		*tag |= KSZ8795_TAIL_TAG_OVERRIDE;

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *ksz8795_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				  काष्ठा packet_type *pt)
अणु
	u8 *tag = skb_tail_poपूर्णांकer(skb) - KSZ_EGRESS_TAG_LEN;

	वापस ksz_common_rcv(skb, dev, tag[0] & 7, KSZ_EGRESS_TAG_LEN);
पूर्ण

अटल स्थिर काष्ठा dsa_device_ops ksz8795_netdev_ops = अणु
	.name	= "ksz8795",
	.proto	= DSA_TAG_PROTO_KSZ8795,
	.xmit	= ksz8795_xmit,
	.rcv	= ksz8795_rcv,
	.overhead = KSZ_INGRESS_TAG_LEN,
	.tail_tag = true,
पूर्ण;

DSA_TAG_DRIVER(ksz8795_netdev_ops);
MODULE_ALIAS_DSA_TAG_DRIVER(DSA_TAG_PROTO_KSZ8795);

/*
 * For Ingress (Host -> KSZ9477), 2 bytes are added beक्रमe FCS.
 * ---------------------------------------------------------------------------
 * DA(6bytes)|SA(6bytes)|....|Data(nbytes)|tag0(1byte)|tag1(1byte)|FCS(4bytes)
 * ---------------------------------------------------------------------------
 * tag0 : Prioritization (not used now)
 * tag1 : each bit represents port (eg, 0x01=port1, 0x02=port2, 0x10=port5)
 *
 * For Egress (KSZ9477 -> Host), 1 byte is added beक्रमe FCS.
 * ---------------------------------------------------------------------------
 * DA(6bytes)|SA(6bytes)|....|Data(nbytes)|tag0(1byte)|FCS(4bytes)
 * ---------------------------------------------------------------------------
 * tag0 : zero-based value represents port
 *	  (eg, 0x00=port1, 0x02=port3, 0x06=port7)
 */

#घोषणा KSZ9477_INGRESS_TAG_LEN		2
#घोषणा KSZ9477_PTP_TAG_LEN		4
#घोषणा KSZ9477_PTP_TAG_INDICATION	0x80

#घोषणा KSZ9477_TAIL_TAG_OVERRIDE	BIT(9)
#घोषणा KSZ9477_TAIL_TAG_LOOKUP		BIT(10)

अटल काष्ठा sk_buff *ksz9477_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	__be16 *tag;
	u8 *addr;
	u16 val;

	/* Tag encoding */
	tag = skb_put(skb, KSZ9477_INGRESS_TAG_LEN);
	addr = skb_mac_header(skb);

	val = BIT(dp->index);

	अगर (is_link_local_ether_addr(addr))
		val |= KSZ9477_TAIL_TAG_OVERRIDE;

	*tag = cpu_to_be16(val);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *ksz9477_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				   काष्ठा packet_type *pt)
अणु
	/* Tag decoding */
	u8 *tag = skb_tail_poपूर्णांकer(skb) - KSZ_EGRESS_TAG_LEN;
	अचिन्हित पूर्णांक port = tag[0] & 7;
	अचिन्हित पूर्णांक len = KSZ_EGRESS_TAG_LEN;

	/* Extra 4-bytes PTP बारtamp */
	अगर (tag[0] & KSZ9477_PTP_TAG_INDICATION)
		len += KSZ9477_PTP_TAG_LEN;

	वापस ksz_common_rcv(skb, dev, port, len);
पूर्ण

अटल स्थिर काष्ठा dsa_device_ops ksz9477_netdev_ops = अणु
	.name	= "ksz9477",
	.proto	= DSA_TAG_PROTO_KSZ9477,
	.xmit	= ksz9477_xmit,
	.rcv	= ksz9477_rcv,
	.overhead = KSZ9477_INGRESS_TAG_LEN,
	.tail_tag = true,
पूर्ण;

DSA_TAG_DRIVER(ksz9477_netdev_ops);
MODULE_ALIAS_DSA_TAG_DRIVER(DSA_TAG_PROTO_KSZ9477);

#घोषणा KSZ9893_TAIL_TAG_OVERRIDE	BIT(5)
#घोषणा KSZ9893_TAIL_TAG_LOOKUP		BIT(6)

अटल काष्ठा sk_buff *ksz9893_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	u8 *addr;
	u8 *tag;

	/* Tag encoding */
	tag = skb_put(skb, KSZ_INGRESS_TAG_LEN);
	addr = skb_mac_header(skb);

	*tag = BIT(dp->index);

	अगर (is_link_local_ether_addr(addr))
		*tag |= KSZ9893_TAIL_TAG_OVERRIDE;

	वापस skb;
पूर्ण

अटल स्थिर काष्ठा dsa_device_ops ksz9893_netdev_ops = अणु
	.name	= "ksz9893",
	.proto	= DSA_TAG_PROTO_KSZ9893,
	.xmit	= ksz9893_xmit,
	.rcv	= ksz9477_rcv,
	.overhead = KSZ_INGRESS_TAG_LEN,
	.tail_tag = true,
पूर्ण;

DSA_TAG_DRIVER(ksz9893_netdev_ops);
MODULE_ALIAS_DSA_TAG_DRIVER(DSA_TAG_PROTO_KSZ9893);

अटल काष्ठा dsa_tag_driver *dsa_tag_driver_array[] = अणु
	&DSA_TAG_DRIVER_NAME(ksz8795_netdev_ops),
	&DSA_TAG_DRIVER_NAME(ksz9477_netdev_ops),
	&DSA_TAG_DRIVER_NAME(ksz9893_netdev_ops),
पूर्ण;

module_dsa_tag_drivers(dsa_tag_driver_array);

MODULE_LICENSE("GPL");
