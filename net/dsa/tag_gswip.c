<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel / Lantiq GSWIP V2.0 PMAC tag support
 *
 * Copyright (C) 2017 - 2018 Hauke Mehrtens <hauke@hauke-m.de>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <net/dsa.h>

#समावेश "dsa_priv.h"

#घोषणा GSWIP_TX_HEADER_LEN		4

/* special tag in TX path header */
/* Byte 0 */
#घोषणा GSWIP_TX_SLPID_SHIFT		0	/* source port ID */
#घोषणा  GSWIP_TX_SLPID_CPU		2
#घोषणा  GSWIP_TX_SLPID_APP1		3
#घोषणा  GSWIP_TX_SLPID_APP2		4
#घोषणा  GSWIP_TX_SLPID_APP3		5
#घोषणा  GSWIP_TX_SLPID_APP4		6
#घोषणा  GSWIP_TX_SLPID_APP5		7

/* Byte 1 */
#घोषणा GSWIP_TX_CRCGEN_DIS		BIT(7)
#घोषणा GSWIP_TX_DPID_SHIFT		0	/* destination group ID */
#घोषणा  GSWIP_TX_DPID_ELAN		0
#घोषणा  GSWIP_TX_DPID_EWAN		1
#घोषणा  GSWIP_TX_DPID_CPU		2
#घोषणा  GSWIP_TX_DPID_APP1		3
#घोषणा  GSWIP_TX_DPID_APP2		4
#घोषणा  GSWIP_TX_DPID_APP3		5
#घोषणा  GSWIP_TX_DPID_APP4		6
#घोषणा  GSWIP_TX_DPID_APP5		7

/* Byte 2 */
#घोषणा GSWIP_TX_PORT_MAP_EN		BIT(7)
#घोषणा GSWIP_TX_PORT_MAP_SEL		BIT(6)
#घोषणा GSWIP_TX_LRN_DIS		BIT(5)
#घोषणा GSWIP_TX_CLASS_EN		BIT(4)
#घोषणा GSWIP_TX_CLASS_SHIFT		0
#घोषणा GSWIP_TX_CLASS_MASK		GENMASK(3, 0)

/* Byte 3 */
#घोषणा GSWIP_TX_DPID_EN		BIT(0)
#घोषणा GSWIP_TX_PORT_MAP_SHIFT		1
#घोषणा GSWIP_TX_PORT_MAP_MASK		GENMASK(6, 1)

#घोषणा GSWIP_RX_HEADER_LEN	8

/* special tag in RX path header */
/* Byte 7 */
#घोषणा GSWIP_RX_SPPID_SHIFT		4
#घोषणा GSWIP_RX_SPPID_MASK		GENMASK(6, 4)

अटल काष्ठा sk_buff *gswip_tag_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	u8 *gswip_tag;

	skb_push(skb, GSWIP_TX_HEADER_LEN);

	gswip_tag = skb->data;
	gswip_tag[0] = GSWIP_TX_SLPID_CPU;
	gswip_tag[1] = GSWIP_TX_DPID_ELAN;
	gswip_tag[2] = GSWIP_TX_PORT_MAP_EN | GSWIP_TX_PORT_MAP_SEL;
	gswip_tag[3] = BIT(dp->index + GSWIP_TX_PORT_MAP_SHIFT) & GSWIP_TX_PORT_MAP_MASK;
	gswip_tag[3] |= GSWIP_TX_DPID_EN;

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *gswip_tag_rcv(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev,
				     काष्ठा packet_type *pt)
अणु
	पूर्णांक port;
	u8 *gswip_tag;

	अगर (unlikely(!pskb_may_pull(skb, GSWIP_RX_HEADER_LEN)))
		वापस शून्य;

	gswip_tag = skb->data - ETH_HLEN;

	/* Get source port inक्रमmation */
	port = (gswip_tag[7] & GSWIP_RX_SPPID_MASK) >> GSWIP_RX_SPPID_SHIFT;
	skb->dev = dsa_master_find_slave(dev, 0, port);
	अगर (!skb->dev)
		वापस शून्य;

	/* हटाओ GSWIP tag */
	skb_pull_rcsum(skb, GSWIP_RX_HEADER_LEN);

	वापस skb;
पूर्ण

अटल स्थिर काष्ठा dsa_device_ops gswip_netdev_ops = अणु
	.name = "gswip",
	.proto	= DSA_TAG_PROTO_GSWIP,
	.xmit = gswip_tag_xmit,
	.rcv = gswip_tag_rcv,
	.overhead = GSWIP_RX_HEADER_LEN,
पूर्ण;

MODULE_LICENSE("GPL");
MODULE_ALIAS_DSA_TAG_DRIVER(DSA_TAG_PROTO_GSWIP);

module_dsa_tag_driver(gswip_netdev_ops);
