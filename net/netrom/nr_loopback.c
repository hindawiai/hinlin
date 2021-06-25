<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright Tomi Manninen OH2BNS (oh2bns@sral.fi)
 */
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/socket.h>
#समावेश <linux/समयr.h>
#समावेश <net/ax25.h>
#समावेश <linux/skbuff.h>
#समावेश <net/netrom.h>
#समावेश <linux/init.h>

अटल व्योम nr_loopback_समयr(काष्ठा समयr_list *);

अटल काष्ठा sk_buff_head loopback_queue;
अटल DEFINE_TIMER(loopback_समयr, nr_loopback_समयr);

व्योम __init nr_loopback_init(व्योम)
अणु
	skb_queue_head_init(&loopback_queue);
पूर्ण

अटल अंतरभूत पूर्णांक nr_loopback_running(व्योम)
अणु
	वापस समयr_pending(&loopback_समयr);
पूर्ण

पूर्णांक nr_loopback_queue(काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *skbn;

	अगर ((skbn = alloc_skb(skb->len, GFP_ATOMIC)) != शून्य) अणु
		skb_copy_from_linear_data(skb, skb_put(skbn, skb->len), skb->len);
		skb_reset_transport_header(skbn);

		skb_queue_tail(&loopback_queue, skbn);

		अगर (!nr_loopback_running())
			mod_समयr(&loopback_समयr, jअगरfies + 10);
	पूर्ण

	kमुक्त_skb(skb);
	वापस 1;
पूर्ण

अटल व्योम nr_loopback_समयr(काष्ठा समयr_list *unused)
अणु
	काष्ठा sk_buff *skb;
	ax25_address *nr_dest;
	काष्ठा net_device *dev;

	अगर ((skb = skb_dequeue(&loopback_queue)) != शून्य) अणु
		nr_dest = (ax25_address *)(skb->data + 7);

		dev = nr_dev_get(nr_dest);

		अगर (dev == शून्य || nr_rx_frame(skb, dev) == 0)
			kमुक्त_skb(skb);

		अगर (dev != शून्य)
			dev_put(dev);

		अगर (!skb_queue_empty(&loopback_queue) && !nr_loopback_running())
			mod_समयr(&loopback_समयr, jअगरfies + 10);
	पूर्ण
पूर्ण

व्योम nr_loopback_clear(व्योम)
अणु
	del_समयr_sync(&loopback_समयr);
	skb_queue_purge(&loopback_queue);
पूर्ण
