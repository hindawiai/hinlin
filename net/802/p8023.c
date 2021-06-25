<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	NET3:	802.3 data link hooks used क्रम IPX 802.3
 *
 *	802.3 isn't really a protocol data link layer. Some old IPX stuff
 *	uses it however. Note that there is only one 802.3 protocol layer
 *	in the प्रणाली. We करोn't currently support dअगरferent protocols
 *	running raw 802.3 on dअगरferent devices. Thankfully nobody अन्यथा
 *	has करोne anything like the old IPX.
 */

#समावेश <linux/in.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>

#समावेश <net/datalink.h>
#समावेश <net/p8022.h>

/*
 *	Place an 802.3 header on a packet. The driver will करो the mac
 *	addresses, we just need to give it the buffer length.
 */
अटल पूर्णांक p8023_request(काष्ठा datalink_proto *dl,
			 काष्ठा sk_buff *skb, अचिन्हित अक्षर *dest_node)
अणु
	काष्ठा net_device *dev = skb->dev;

	dev_hard_header(skb, dev, ETH_P_802_3, dest_node, शून्य, skb->len);
	वापस dev_queue_xmit(skb);
पूर्ण

/*
 *	Create an 802.3 client. Note there can be only one 802.3 client
 */
काष्ठा datalink_proto *make_8023_client(व्योम)
अणु
	काष्ठा datalink_proto *proto = kदो_स्मृति(माप(*proto), GFP_ATOMIC);

	अगर (proto) अणु
		proto->header_length = 0;
		proto->request	     = p8023_request;
	पूर्ण
	वापस proto;
पूर्ण

/*
 *	Destroy the 802.3 client.
 */
व्योम destroy_8023_client(काष्ठा datalink_proto *dl)
अणु
	kमुक्त(dl);
पूर्ण

EXPORT_SYMBOL(destroy_8023_client);
EXPORT_SYMBOL(make_8023_client);

MODULE_LICENSE("GPL");
