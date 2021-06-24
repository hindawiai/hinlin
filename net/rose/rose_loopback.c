<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 */
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/socket.h>
#समावेश <linux/समयr.h>
#समावेश <net/ax25.h>
#समावेश <linux/skbuff.h>
#समावेश <net/rose.h>
#समावेश <linux/init.h>

अटल काष्ठा sk_buff_head loopback_queue;
#घोषणा ROSE_LOOPBACK_LIMIT 1000
अटल काष्ठा समयr_list loopback_समयr;

अटल व्योम rose_set_loopback_समयr(व्योम);
अटल व्योम rose_loopback_समयr(काष्ठा समयr_list *unused);

व्योम rose_loopback_init(व्योम)
अणु
	skb_queue_head_init(&loopback_queue);

	समयr_setup(&loopback_समयr, rose_loopback_समयr, 0);
पूर्ण

अटल पूर्णांक rose_loopback_running(व्योम)
अणु
	वापस समयr_pending(&loopback_समयr);
पूर्ण

पूर्णांक rose_loopback_queue(काष्ठा sk_buff *skb, काष्ठा rose_neigh *neigh)
अणु
	काष्ठा sk_buff *skbn = शून्य;

	अगर (skb_queue_len(&loopback_queue) < ROSE_LOOPBACK_LIMIT)
		skbn = skb_clone(skb, GFP_ATOMIC);

	अगर (skbn) अणु
		consume_skb(skb);
		skb_queue_tail(&loopback_queue, skbn);

		अगर (!rose_loopback_running())
			rose_set_loopback_समयr();
	पूर्ण अन्यथा अणु
		kमुक्त_skb(skb);
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम rose_set_loopback_समयr(व्योम)
अणु
	mod_समयr(&loopback_समयr, jअगरfies + 10);
पूर्ण

अटल व्योम rose_loopback_समयr(काष्ठा समयr_list *unused)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा net_device *dev;
	rose_address *dest;
	काष्ठा sock *sk;
	अचिन्हित लघु frametype;
	अचिन्हित पूर्णांक lci_i, lci_o;
	पूर्णांक count;

	क्रम (count = 0; count < ROSE_LOOPBACK_LIMIT; count++) अणु
		skb = skb_dequeue(&loopback_queue);
		अगर (!skb)
			वापस;
		अगर (skb->len < ROSE_MIN_LEN) अणु
			kमुक्त_skb(skb);
			जारी;
		पूर्ण
		lci_i     = ((skb->data[0] << 8) & 0xF00) + ((skb->data[1] << 0) & 0x0FF);
		frametype = skb->data[2];
		अगर (frametype == ROSE_CALL_REQUEST &&
		    (skb->len <= ROSE_CALL_REQ_FACILITIES_OFF ||
		     skb->data[ROSE_CALL_REQ_ADDR_LEN_OFF] !=
		     ROSE_CALL_REQ_ADDR_LEN_VAL)) अणु
			kमुक्त_skb(skb);
			जारी;
		पूर्ण
		dest      = (rose_address *)(skb->data + ROSE_CALL_REQ_DEST_ADDR_OFF);
		lci_o     = ROSE_DEFAULT_MAXVC + 1 - lci_i;

		skb_reset_transport_header(skb);

		sk = rose_find_socket(lci_o, rose_loopback_neigh);
		अगर (sk) अणु
			अगर (rose_process_rx_frame(sk, skb) == 0)
				kमुक्त_skb(skb);
			जारी;
		पूर्ण

		अगर (frametype == ROSE_CALL_REQUEST) अणु
			अगर (!rose_loopback_neigh->dev) अणु
				kमुक्त_skb(skb);
				जारी;
			पूर्ण

			dev = rose_dev_get(dest);
			अगर (!dev) अणु
				kमुक्त_skb(skb);
				जारी;
			पूर्ण

			अगर (rose_rx_call_request(skb, dev, rose_loopback_neigh, lci_o) == 0) अणु
				dev_put(dev);
				kमुक्त_skb(skb);
			पूर्ण
		पूर्ण अन्यथा अणु
			kमुक्त_skb(skb);
		पूर्ण
	पूर्ण
	अगर (!skb_queue_empty(&loopback_queue))
		mod_समयr(&loopback_समयr, jअगरfies + 1);
पूर्ण

व्योम __निकास rose_loopback_clear(व्योम)
अणु
	काष्ठा sk_buff *skb;

	del_समयr(&loopback_समयr);

	जबतक ((skb = skb_dequeue(&loopback_queue)) != शून्य) अणु
		skb->sk = शून्य;
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण
