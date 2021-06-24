<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * net/dsa/tag_trailer.c - Trailer tag क्रमmat handling
 * Copyright (c) 2008-2009 Marvell Semiconductor
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>

#समावेश "dsa_priv.h"

अटल काष्ठा sk_buff *trailer_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	u8 *trailer;

	trailer = skb_put(skb, 4);
	trailer[0] = 0x80;
	trailer[1] = 1 << dp->index;
	trailer[2] = 0x10;
	trailer[3] = 0x00;

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *trailer_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				   काष्ठा packet_type *pt)
अणु
	u8 *trailer;
	पूर्णांक source_port;

	अगर (skb_linearize(skb))
		वापस शून्य;

	trailer = skb_tail_poपूर्णांकer(skb) - 4;
	अगर (trailer[0] != 0x80 || (trailer[1] & 0xf8) != 0x00 ||
	    (trailer[2] & 0xef) != 0x00 || trailer[3] != 0x00)
		वापस शून्य;

	source_port = trailer[1] & 7;

	skb->dev = dsa_master_find_slave(dev, 0, source_port);
	अगर (!skb->dev)
		वापस शून्य;

	अगर (pskb_trim_rcsum(skb, skb->len - 4))
		वापस शून्य;

	वापस skb;
पूर्ण

अटल स्थिर काष्ठा dsa_device_ops trailer_netdev_ops = अणु
	.name	= "trailer",
	.proto	= DSA_TAG_PROTO_TRAILER,
	.xmit	= trailer_xmit,
	.rcv	= trailer_rcv,
	.overhead = 4,
	.tail_tag = true,
पूर्ण;

MODULE_LICENSE("GPL");
MODULE_ALIAS_DSA_TAG_DRIVER(DSA_TAG_PROTO_TRAILER);

module_dsa_tag_driver(trailer_netdev_ops);
