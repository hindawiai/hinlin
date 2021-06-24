<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Broadcom tag support
 *
 * Copyright (C) 2014 Broadcom Corporation
 */

#समावेश <linux/dsa/brcm.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>

#समावेश "dsa_priv.h"

/* Legacy Broadcom tag (6 bytes) */
#घोषणा BRCM_LEG_TAG_LEN	6

/* Type fields */
/* 1st byte in the tag */
#घोषणा BRCM_LEG_TYPE_HI	0x88
/* 2nd byte in the tag */
#घोषणा BRCM_LEG_TYPE_LO	0x74

/* Tag fields */
/* 3rd byte in the tag */
#घोषणा BRCM_LEG_UNICAST	(0 << 5)
#घोषणा BRCM_LEG_MULTICAST	(1 << 5)
#घोषणा BRCM_LEG_EGRESS		(2 << 5)
#घोषणा BRCM_LEG_INGRESS	(3 << 5)

/* 6th byte in the tag */
#घोषणा BRCM_LEG_PORT_ID	(0xf)

/* Newer Broadcom tag (4 bytes) */
#घोषणा BRCM_TAG_LEN	4

/* Tag is स्थिरructed and desस्थिरructed using byte by byte access
 * because the tag is placed after the MAC Source Address, which करोes
 * not make it 4-bytes aligned, so this might cause unaligned accesses
 * on most प्रणालीs where this is used.
 */

/* Ingress and egress opcodes */
#घोषणा BRCM_OPCODE_SHIFT	5
#घोषणा BRCM_OPCODE_MASK	0x7

/* Ingress fields */
/* 1st byte in the tag */
#घोषणा BRCM_IG_TC_SHIFT	2
#घोषणा BRCM_IG_TC_MASK		0x7
/* 2nd byte in the tag */
#घोषणा BRCM_IG_TE_MASK		0x3
#घोषणा BRCM_IG_TS_SHIFT	7
/* 3rd byte in the tag */
#घोषणा BRCM_IG_DSTMAP2_MASK	1
#घोषणा BRCM_IG_DSTMAP1_MASK	0xff

/* Egress fields */

/* 2nd byte in the tag */
#घोषणा BRCM_EG_CID_MASK	0xff

/* 3rd byte in the tag */
#घोषणा BRCM_EG_RC_MASK		0xff
#घोषणा  BRCM_EG_RC_RSVD	(3 << 6)
#घोषणा  BRCM_EG_RC_EXCEPTION	(1 << 5)
#घोषणा  BRCM_EG_RC_PROT_SNOOP	(1 << 4)
#घोषणा  BRCM_EG_RC_PROT_TERM	(1 << 3)
#घोषणा  BRCM_EG_RC_SWITCH	(1 << 2)
#घोषणा  BRCM_EG_RC_MAC_LEARN	(1 << 1)
#घोषणा  BRCM_EG_RC_MIRROR	(1 << 0)
#घोषणा BRCM_EG_TC_SHIFT	5
#घोषणा BRCM_EG_TC_MASK		0x7
#घोषणा BRCM_EG_PID_MASK	0x1f

#अगर IS_ENABLED(CONFIG_NET_DSA_TAG_BRCM) || \
	IS_ENABLED(CONFIG_NET_DSA_TAG_BRCM_PREPEND)

अटल काष्ठा sk_buff *brcm_tag_xmit_ll(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev,
					अचिन्हित पूर्णांक offset)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	u16 queue = skb_get_queue_mapping(skb);
	u8 *brcm_tag;

	/* The Ethernet चयन we are पूर्णांकerfaced with needs packets to be at
	 * least 64 bytes (including FCS) otherwise they will be discarded when
	 * they enter the चयन port logic. When Broadcom tags are enabled, we
	 * need to make sure that packets are at least 68 bytes
	 * (including FCS and tag) because the length verअगरication is करोne after
	 * the Broadcom tag is stripped off the ingress packet.
	 *
	 * Let dsa_slave_xmit() मुक्त the SKB
	 */
	अगर (__skb_put_padto(skb, ETH_ZLEN + BRCM_TAG_LEN, false))
		वापस शून्य;

	skb_push(skb, BRCM_TAG_LEN);

	अगर (offset)
		स_हटाओ(skb->data, skb->data + BRCM_TAG_LEN, offset);

	brcm_tag = skb->data + offset;

	/* Set the ingress opcode, traffic class, tag enक्रमcment is
	 * deprecated
	 */
	brcm_tag[0] = (1 << BRCM_OPCODE_SHIFT) |
		       ((queue & BRCM_IG_TC_MASK) << BRCM_IG_TC_SHIFT);
	brcm_tag[1] = 0;
	brcm_tag[2] = 0;
	अगर (dp->index == 8)
		brcm_tag[2] = BRCM_IG_DSTMAP2_MASK;
	brcm_tag[3] = (1 << dp->index) & BRCM_IG_DSTMAP1_MASK;

	/* Now tell the master network device about the desired output queue
	 * as well
	 */
	skb_set_queue_mapping(skb, BRCM_TAG_SET_PORT_QUEUE(dp->index, queue));

	वापस skb;
पूर्ण

/* Frames with this tag have one of these two layouts:
 * -----------------------------------
 * | MAC DA | MAC SA | 4b tag | Type | DSA_TAG_PROTO_BRCM
 * -----------------------------------
 * -----------------------------------
 * | 4b tag | MAC DA | MAC SA | Type | DSA_TAG_PROTO_BRCM_PREPEND
 * -----------------------------------
 * In both हालs, at receive समय, skb->data poपूर्णांकs 2 bytes beक्रमe the actual
 * Ethernet type field and we have an offset of 4bytes between where skb->data
 * and where the payload starts. So the same low-level receive function can be
 * used.
 */
अटल काष्ठा sk_buff *brcm_tag_rcv_ll(काष्ठा sk_buff *skb,
				       काष्ठा net_device *dev,
				       काष्ठा packet_type *pt,
				       अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक source_port;
	u8 *brcm_tag;

	अगर (unlikely(!pskb_may_pull(skb, BRCM_TAG_LEN)))
		वापस शून्य;

	brcm_tag = skb->data - offset;

	/* The opcode should never be dअगरferent than 0b000 */
	अगर (unlikely((brcm_tag[0] >> BRCM_OPCODE_SHIFT) & BRCM_OPCODE_MASK))
		वापस शून्य;

	/* We should never see a reserved reason code without knowing how to
	 * handle it
	 */
	अगर (unlikely(brcm_tag[2] & BRCM_EG_RC_RSVD))
		वापस शून्य;

	/* Locate which port this is coming from */
	source_port = brcm_tag[3] & BRCM_EG_PID_MASK;

	skb->dev = dsa_master_find_slave(dev, 0, source_port);
	अगर (!skb->dev)
		वापस शून्य;

	/* Remove Broadcom tag and update checksum */
	skb_pull_rcsum(skb, BRCM_TAG_LEN);

	skb->offload_fwd_mark = 1;

	वापस skb;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_NET_DSA_TAG_BRCM)
अटल काष्ठा sk_buff *brcm_tag_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev)
अणु
	/* Build the tag after the MAC Source Address */
	वापस brcm_tag_xmit_ll(skb, dev, 2 * ETH_ALEN);
पूर्ण


अटल काष्ठा sk_buff *brcm_tag_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				    काष्ठा packet_type *pt)
अणु
	काष्ठा sk_buff *nskb;

	/* skb->data poपूर्णांकs to the EtherType, the tag is right beक्रमe it */
	nskb = brcm_tag_rcv_ll(skb, dev, pt, 2);
	अगर (!nskb)
		वापस nskb;

	/* Move the Ethernet DA and SA */
	स_हटाओ(nskb->data - ETH_HLEN,
		nskb->data - ETH_HLEN - BRCM_TAG_LEN,
		2 * ETH_ALEN);

	वापस nskb;
पूर्ण

अटल स्थिर काष्ठा dsa_device_ops brcm_netdev_ops = अणु
	.name	= "brcm",
	.proto	= DSA_TAG_PROTO_BRCM,
	.xmit	= brcm_tag_xmit,
	.rcv	= brcm_tag_rcv,
	.overhead = BRCM_TAG_LEN,
पूर्ण;

DSA_TAG_DRIVER(brcm_netdev_ops);
MODULE_ALIAS_DSA_TAG_DRIVER(DSA_TAG_PROTO_BRCM);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_NET_DSA_TAG_BRCM_LEGACY)
अटल काष्ठा sk_buff *brcm_leg_tag_xmit(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	u8 *brcm_tag;

	/* The Ethernet चयन we are पूर्णांकerfaced with needs packets to be at
	 * least 64 bytes (including FCS) otherwise they will be discarded when
	 * they enter the चयन port logic. When Broadcom tags are enabled, we
	 * need to make sure that packets are at least 70 bytes
	 * (including FCS and tag) because the length verअगरication is करोne after
	 * the Broadcom tag is stripped off the ingress packet.
	 *
	 * Let dsa_slave_xmit() मुक्त the SKB
	 */
	अगर (__skb_put_padto(skb, ETH_ZLEN + BRCM_LEG_TAG_LEN, false))
		वापस शून्य;

	skb_push(skb, BRCM_LEG_TAG_LEN);

	स_हटाओ(skb->data, skb->data + BRCM_LEG_TAG_LEN, 2 * ETH_ALEN);

	brcm_tag = skb->data + 2 * ETH_ALEN;

	/* Broadcom tag type */
	brcm_tag[0] = BRCM_LEG_TYPE_HI;
	brcm_tag[1] = BRCM_LEG_TYPE_LO;

	/* Broadcom tag value */
	brcm_tag[2] = BRCM_LEG_EGRESS;
	brcm_tag[3] = 0;
	brcm_tag[4] = 0;
	brcm_tag[5] = dp->index & BRCM_LEG_PORT_ID;

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *brcm_leg_tag_rcv(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev,
					काष्ठा packet_type *pt)
अणु
	पूर्णांक source_port;
	u8 *brcm_tag;

	अगर (unlikely(!pskb_may_pull(skb, BRCM_LEG_PORT_ID)))
		वापस शून्य;

	brcm_tag = skb->data - 2;

	source_port = brcm_tag[5] & BRCM_LEG_PORT_ID;

	skb->dev = dsa_master_find_slave(dev, 0, source_port);
	अगर (!skb->dev)
		वापस शून्य;

	/* Remove Broadcom tag and update checksum */
	skb_pull_rcsum(skb, BRCM_LEG_TAG_LEN);

	skb->offload_fwd_mark = 1;

	/* Move the Ethernet DA and SA */
	स_हटाओ(skb->data - ETH_HLEN,
		skb->data - ETH_HLEN - BRCM_LEG_TAG_LEN,
		2 * ETH_ALEN);

	वापस skb;
पूर्ण

अटल स्थिर काष्ठा dsa_device_ops brcm_legacy_netdev_ops = अणु
	.name = "brcm-legacy",
	.proto = DSA_TAG_PROTO_BRCM_LEGACY,
	.xmit = brcm_leg_tag_xmit,
	.rcv = brcm_leg_tag_rcv,
	.overhead = BRCM_LEG_TAG_LEN,
पूर्ण;

DSA_TAG_DRIVER(brcm_legacy_netdev_ops);
MODULE_ALIAS_DSA_TAG_DRIVER(DSA_TAG_PROTO_BRCM_LEGACY);
#पूर्ण_अगर /* CONFIG_NET_DSA_TAG_BRCM_LEGACY */

#अगर IS_ENABLED(CONFIG_NET_DSA_TAG_BRCM_PREPEND)
अटल काष्ठा sk_buff *brcm_tag_xmit_prepend(काष्ठा sk_buff *skb,
					     काष्ठा net_device *dev)
अणु
	/* tag is prepended to the packet */
	वापस brcm_tag_xmit_ll(skb, dev, 0);
पूर्ण

अटल काष्ठा sk_buff *brcm_tag_rcv_prepend(काष्ठा sk_buff *skb,
					    काष्ठा net_device *dev,
					    काष्ठा packet_type *pt)
अणु
	/* tag is prepended to the packet */
	वापस brcm_tag_rcv_ll(skb, dev, pt, ETH_HLEN);
पूर्ण

अटल स्थिर काष्ठा dsa_device_ops brcm_prepend_netdev_ops = अणु
	.name	= "brcm-prepend",
	.proto	= DSA_TAG_PROTO_BRCM_PREPEND,
	.xmit	= brcm_tag_xmit_prepend,
	.rcv	= brcm_tag_rcv_prepend,
	.overhead = BRCM_TAG_LEN,
पूर्ण;

DSA_TAG_DRIVER(brcm_prepend_netdev_ops);
MODULE_ALIAS_DSA_TAG_DRIVER(DSA_TAG_PROTO_BRCM_PREPEND);
#पूर्ण_अगर

अटल काष्ठा dsa_tag_driver *dsa_tag_driver_array[] =	अणु
#अगर IS_ENABLED(CONFIG_NET_DSA_TAG_BRCM)
	&DSA_TAG_DRIVER_NAME(brcm_netdev_ops),
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_NET_DSA_TAG_BRCM_LEGACY)
	&DSA_TAG_DRIVER_NAME(brcm_legacy_netdev_ops),
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_NET_DSA_TAG_BRCM_PREPEND)
	&DSA_TAG_DRIVER_NAME(brcm_prepend_netdev_ops),
#पूर्ण_अगर
पूर्ण;

module_dsa_tag_drivers(dsa_tag_driver_array);

MODULE_LICENSE("GPL");
