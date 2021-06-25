<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Mediatek DSA Tag support
 * Copyright (C) 2017 Landen Chao <landen.chao@mediatek.com>
 *		      Sean Wang <sean.wang@mediatek.com>
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>

#समावेश "dsa_priv.h"

#घोषणा MTK_HDR_LEN		4
#घोषणा MTK_HDR_XMIT_UNTAGGED		0
#घोषणा MTK_HDR_XMIT_TAGGED_TPID_8100	1
#घोषणा MTK_HDR_XMIT_TAGGED_TPID_88A8	2
#घोषणा MTK_HDR_RECV_SOURCE_PORT_MASK	GENMASK(2, 0)
#घोषणा MTK_HDR_XMIT_DP_BIT_MASK	GENMASK(5, 0)
#घोषणा MTK_HDR_XMIT_SA_DIS		BIT(6)

अटल काष्ठा sk_buff *mtk_tag_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	u8 xmit_tpid;
	u8 *mtk_tag;

	/* Build the special tag after the MAC Source Address. If VLAN header
	 * is present, it's required that VLAN header and special tag is
	 * being combined. Only in this way we can allow the चयन can parse
	 * the both special and VLAN tag at the same समय and then look up VLAN
	 * table with VID.
	 */
	चयन (skb->protocol) अणु
	हाल htons(ETH_P_8021Q):
		xmit_tpid = MTK_HDR_XMIT_TAGGED_TPID_8100;
		अवरोध;
	हाल htons(ETH_P_8021AD):
		xmit_tpid = MTK_HDR_XMIT_TAGGED_TPID_88A8;
		अवरोध;
	शेष:
		xmit_tpid = MTK_HDR_XMIT_UNTAGGED;
		skb_push(skb, MTK_HDR_LEN);
		स_हटाओ(skb->data, skb->data + MTK_HDR_LEN, 2 * ETH_ALEN);
	पूर्ण

	mtk_tag = skb->data + 2 * ETH_ALEN;

	/* Mark tag attribute on special tag insertion to notअगरy hardware
	 * whether that's a combined special tag with 802.1Q header.
	 */
	mtk_tag[0] = xmit_tpid;
	mtk_tag[1] = (1 << dp->index) & MTK_HDR_XMIT_DP_BIT_MASK;

	/* Tag control inक्रमmation is kept क्रम 802.1Q */
	अगर (xmit_tpid == MTK_HDR_XMIT_UNTAGGED) अणु
		mtk_tag[2] = 0;
		mtk_tag[3] = 0;
	पूर्ण

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *mtk_tag_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				   काष्ठा packet_type *pt)
अणु
	u16 hdr;
	पूर्णांक port;
	__be16 *phdr;

	अगर (unlikely(!pskb_may_pull(skb, MTK_HDR_LEN)))
		वापस शून्य;

	/* The MTK header is added by the चयन between src addr
	 * and ethertype at this poपूर्णांक, skb->data poपूर्णांकs to 2 bytes
	 * after src addr so header should be 2 bytes right beक्रमe.
	 */
	phdr = (__be16 *)(skb->data - 2);
	hdr = ntohs(*phdr);

	/* Remove MTK tag and recalculate checksum. */
	skb_pull_rcsum(skb, MTK_HDR_LEN);

	स_हटाओ(skb->data - ETH_HLEN,
		skb->data - ETH_HLEN - MTK_HDR_LEN,
		2 * ETH_ALEN);

	/* Get source port inक्रमmation */
	port = (hdr & MTK_HDR_RECV_SOURCE_PORT_MASK);

	skb->dev = dsa_master_find_slave(dev, 0, port);
	अगर (!skb->dev)
		वापस शून्य;

	skb->offload_fwd_mark = 1;

	वापस skb;
पूर्ण

अटल स्थिर काष्ठा dsa_device_ops mtk_netdev_ops = अणु
	.name		= "mtk",
	.proto		= DSA_TAG_PROTO_MTK,
	.xmit		= mtk_tag_xmit,
	.rcv		= mtk_tag_rcv,
	.overhead	= MTK_HDR_LEN,
पूर्ण;

MODULE_LICENSE("GPL");
MODULE_ALIAS_DSA_TAG_DRIVER(DSA_TAG_PROTO_MTK);

module_dsa_tag_driver(mtk_netdev_ops);
