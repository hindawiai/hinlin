<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/etherdevice.h>

#समावेश "dsa_priv.h"

#घोषणा QCA_HDR_LEN	2
#घोषणा QCA_HDR_VERSION	0x2

#घोषणा QCA_HDR_RECV_VERSION_MASK	GENMASK(15, 14)
#घोषणा QCA_HDR_RECV_VERSION_S		14
#घोषणा QCA_HDR_RECV_PRIORITY_MASK	GENMASK(13, 11)
#घोषणा QCA_HDR_RECV_PRIORITY_S		11
#घोषणा QCA_HDR_RECV_TYPE_MASK		GENMASK(10, 6)
#घोषणा QCA_HDR_RECV_TYPE_S		6
#घोषणा QCA_HDR_RECV_FRAME_IS_TAGGED	BIT(3)
#घोषणा QCA_HDR_RECV_SOURCE_PORT_MASK	GENMASK(2, 0)

#घोषणा QCA_HDR_XMIT_VERSION_MASK	GENMASK(15, 14)
#घोषणा QCA_HDR_XMIT_VERSION_S		14
#घोषणा QCA_HDR_XMIT_PRIORITY_MASK	GENMASK(13, 11)
#घोषणा QCA_HDR_XMIT_PRIORITY_S		11
#घोषणा QCA_HDR_XMIT_CONTROL_MASK	GENMASK(10, 8)
#घोषणा QCA_HDR_XMIT_CONTROL_S		8
#घोषणा QCA_HDR_XMIT_FROM_CPU		BIT(7)
#घोषणा QCA_HDR_XMIT_DP_BIT_MASK	GENMASK(6, 0)

अटल काष्ठा sk_buff *qca_tag_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	__be16 *phdr;
	u16 hdr;

	skb_push(skb, QCA_HDR_LEN);

	स_हटाओ(skb->data, skb->data + QCA_HDR_LEN, 2 * ETH_ALEN);
	phdr = (__be16 *)(skb->data + 2 * ETH_ALEN);

	/* Set the version field, and set destination port inक्रमmation */
	hdr = QCA_HDR_VERSION << QCA_HDR_XMIT_VERSION_S |
		QCA_HDR_XMIT_FROM_CPU | BIT(dp->index);

	*phdr = htons(hdr);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *qca_tag_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				   काष्ठा packet_type *pt)
अणु
	u8 ver;
	u16  hdr;
	पूर्णांक port;
	__be16 *phdr;

	अगर (unlikely(!pskb_may_pull(skb, QCA_HDR_LEN)))
		वापस शून्य;

	/* The QCA header is added by the चयन between src addr and Ethertype
	 * At this poपूर्णांक, skb->data poपूर्णांकs to ethertype so header should be
	 * right beक्रमe
	 */
	phdr = (__be16 *)(skb->data - 2);
	hdr = ntohs(*phdr);

	/* Make sure the version is correct */
	ver = (hdr & QCA_HDR_RECV_VERSION_MASK) >> QCA_HDR_RECV_VERSION_S;
	अगर (unlikely(ver != QCA_HDR_VERSION))
		वापस शून्य;

	/* Remove QCA tag and recalculate checksum */
	skb_pull_rcsum(skb, QCA_HDR_LEN);
	स_हटाओ(skb->data - ETH_HLEN, skb->data - ETH_HLEN - QCA_HDR_LEN,
		ETH_HLEN - QCA_HDR_LEN);

	/* Get source port inक्रमmation */
	port = (hdr & QCA_HDR_RECV_SOURCE_PORT_MASK);

	skb->dev = dsa_master_find_slave(dev, 0, port);
	अगर (!skb->dev)
		वापस शून्य;

	वापस skb;
पूर्ण

अटल स्थिर काष्ठा dsa_device_ops qca_netdev_ops = अणु
	.name	= "qca",
	.proto	= DSA_TAG_PROTO_QCA,
	.xmit	= qca_tag_xmit,
	.rcv	= qca_tag_rcv,
	.overhead = QCA_HDR_LEN,
पूर्ण;

MODULE_LICENSE("GPL");
MODULE_ALIAS_DSA_TAG_DRIVER(DSA_TAG_PROTO_QCA);

module_dsa_tag_driver(qca_netdev_ops);
