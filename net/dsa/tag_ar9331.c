<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019 Pengutronix, Oleksij Rempel <kernel@pengutronix.de>
 */


#समावेश <linux/bitfield.h>
#समावेश <linux/etherdevice.h>

#समावेश "dsa_priv.h"

#घोषणा AR9331_HDR_LEN			2
#घोषणा AR9331_HDR_VERSION		1

#घोषणा AR9331_HDR_VERSION_MASK		GENMASK(15, 14)
#घोषणा AR9331_HDR_PRIORITY_MASK	GENMASK(13, 12)
#घोषणा AR9331_HDR_TYPE_MASK		GENMASK(10, 8)
#घोषणा AR9331_HDR_BROADCAST		BIT(7)
#घोषणा AR9331_HDR_FROM_CPU		BIT(6)
/* AR9331_HDR_RESERVED - not used or may be version field.
 * According to the AR8216 करोc it should 0b10. On AR9331 it is 0b11 on RX path
 * and should be set to 0b11 to make it work.
 */
#घोषणा AR9331_HDR_RESERVED_MASK	GENMASK(5, 4)
#घोषणा AR9331_HDR_PORT_NUM_MASK	GENMASK(3, 0)

अटल काष्ठा sk_buff *ar9331_tag_xmit(काष्ठा sk_buff *skb,
				       काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	__le16 *phdr;
	u16 hdr;

	phdr = skb_push(skb, AR9331_HDR_LEN);

	hdr = FIELD_PREP(AR9331_HDR_VERSION_MASK, AR9331_HDR_VERSION);
	hdr |= AR9331_HDR_FROM_CPU | dp->index;
	/* 0b10 क्रम AR8216 and 0b11 क्रम AR9331 */
	hdr |= AR9331_HDR_RESERVED_MASK;

	phdr[0] = cpu_to_le16(hdr);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *ar9331_tag_rcv(काष्ठा sk_buff *skb,
				      काष्ठा net_device *ndev,
				      काष्ठा packet_type *pt)
अणु
	u8 ver, port;
	u16 hdr;

	अगर (unlikely(!pskb_may_pull(skb, AR9331_HDR_LEN)))
		वापस शून्य;

	hdr = le16_to_cpu(*(__le16 *)skb_mac_header(skb));

	ver = FIELD_GET(AR9331_HDR_VERSION_MASK, hdr);
	अगर (unlikely(ver != AR9331_HDR_VERSION)) अणु
		netdev_warn_once(ndev, "%s:%i wrong header version 0x%2x\n",
				 __func__, __LINE__, hdr);
		वापस शून्य;
	पूर्ण

	अगर (unlikely(hdr & AR9331_HDR_FROM_CPU)) अणु
		netdev_warn_once(ndev, "%s:%i packet should not be from cpu 0x%2x\n",
				 __func__, __LINE__, hdr);
		वापस शून्य;
	पूर्ण

	skb_pull_rcsum(skb, AR9331_HDR_LEN);

	/* Get source port inक्रमmation */
	port = FIELD_GET(AR9331_HDR_PORT_NUM_MASK, hdr);

	skb->dev = dsa_master_find_slave(ndev, 0, port);
	अगर (!skb->dev)
		वापस शून्य;

	वापस skb;
पूर्ण

अटल स्थिर काष्ठा dsa_device_ops ar9331_netdev_ops = अणु
	.name	= "ar9331",
	.proto	= DSA_TAG_PROTO_AR9331,
	.xmit	= ar9331_tag_xmit,
	.rcv	= ar9331_tag_rcv,
	.overhead = AR9331_HDR_LEN,
पूर्ण;

MODULE_LICENSE("GPL v2");
MODULE_ALIAS_DSA_TAG_DRIVER(DSA_TAG_PROTO_AR9331);
module_dsa_tag_driver(ar9331_netdev_ops);
