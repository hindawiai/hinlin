<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * XRS700x tag क्रमmat handling
 * Copyright (c) 2008-2009 Marvell Semiconductor
 * Copyright (c) 2020 NovaTech LLC
 */

#समावेश <linux/bitops.h>

#समावेश "dsa_priv.h"

अटल काष्ठा sk_buff *xrs700x_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *partner, *dp = dsa_slave_to_port(dev);
	u8 *trailer;

	trailer = skb_put(skb, 1);
	trailer[0] = BIT(dp->index);

	अगर (dp->hsr_dev)
		dsa_hsr_क्रमeach_port(partner, dp->ds, dp->hsr_dev)
			अगर (partner != dp)
				trailer[0] |= BIT(partner->index);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *xrs700x_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				   काष्ठा packet_type *pt)
अणु
	पूर्णांक source_port;
	u8 *trailer;

	trailer = skb_tail_poपूर्णांकer(skb) - 1;

	source_port = ffs((पूर्णांक)trailer[0]) - 1;

	अगर (source_port < 0)
		वापस शून्य;

	skb->dev = dsa_master_find_slave(dev, 0, source_port);
	अगर (!skb->dev)
		वापस शून्य;

	अगर (pskb_trim_rcsum(skb, skb->len - 1))
		वापस शून्य;

	/* Frame is क्रमwarded by hardware, करोn't क्रमward in software. */
	skb->offload_fwd_mark = 1;

	वापस skb;
पूर्ण

अटल स्थिर काष्ठा dsa_device_ops xrs700x_netdev_ops = अणु
	.name	= "xrs700x",
	.proto	= DSA_TAG_PROTO_XRS700X,
	.xmit	= xrs700x_xmit,
	.rcv	= xrs700x_rcv,
	.overhead = 1,
	.tail_tag = true,
पूर्ण;

MODULE_LICENSE("GPL");
MODULE_ALIAS_DSA_TAG_DRIVER(DSA_TAG_PROTO_XRS700X);

module_dsa_tag_driver(xrs700x_netdev_ops);
