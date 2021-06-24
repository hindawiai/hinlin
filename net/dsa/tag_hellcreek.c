<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * net/dsa/tag_hellcreek.c - Hirschmann Hellcreek चयन tag क्रमmat handling
 *
 * Copyright (C) 2019,2020 Linutronix GmbH
 * Author Kurt Kanzenbach <kurt@linutronix.de>
 *
 * Based on tag_ksz.c.
 */

#समावेश <linux/skbuff.h>
#समावेश <net/dsa.h>

#समावेश "dsa_priv.h"

#घोषणा HELLCREEK_TAG_LEN	1

अटल काष्ठा sk_buff *hellcreek_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	u8 *tag;

	/* Tag encoding */
	tag  = skb_put(skb, HELLCREEK_TAG_LEN);
	*tag = BIT(dp->index);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *hellcreek_rcv(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev,
				     काष्ठा packet_type *pt)
अणु
	/* Tag decoding */
	u8 *tag = skb_tail_poपूर्णांकer(skb) - HELLCREEK_TAG_LEN;
	अचिन्हित पूर्णांक port = tag[0] & 0x03;

	skb->dev = dsa_master_find_slave(dev, 0, port);
	अगर (!skb->dev) अणु
		netdev_warn(dev, "Failed to get source port: %d\n", port);
		वापस शून्य;
	पूर्ण

	pskb_trim_rcsum(skb, skb->len - HELLCREEK_TAG_LEN);

	skb->offload_fwd_mark = true;

	वापस skb;
पूर्ण

अटल स्थिर काष्ठा dsa_device_ops hellcreek_netdev_ops = अणु
	.name	  = "hellcreek",
	.proto	  = DSA_TAG_PROTO_HELLCREEK,
	.xmit	  = hellcreek_xmit,
	.rcv	  = hellcreek_rcv,
	.overhead = HELLCREEK_TAG_LEN,
	.tail_tag = true,
पूर्ण;

MODULE_LICENSE("Dual MIT/GPL");
MODULE_ALIAS_DSA_TAG_DRIVER(DSA_TAG_PROTO_HELLCREEK);

module_dsa_tag_driver(hellcreek_netdev_ops);
