<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	X.25 Packet Layer release 002
 *
 *	This is ALPHA test software. This code may अवरोध your machine, अक्रमomly fail to work with new
 *	releases, misbehave and/or generally screw up. It might even work.
 *
 *	This code REQUIRES 2.1.15 or higher
 *
 *	History
 *	X.25 001	Jonathan Naylor	Started coding.
 *      2000-09-04	Henner Eisen	Prevent मुक्तing a dangling skb.
 */

#घोषणा pr_fmt(fmt) "X25: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <linux/अगर_arp.h>
#समावेश <net/x25.h>
#समावेश <net/x25device.h>

अटल पूर्णांक x25_receive_data(काष्ठा sk_buff *skb, काष्ठा x25_neigh *nb)
अणु
	काष्ठा sock *sk;
	अचिन्हित लघु frametype;
	अचिन्हित पूर्णांक lci;

	अगर (!pskb_may_pull(skb, X25_STD_MIN_LEN))
		वापस 0;

	frametype = skb->data[2];
	lci = ((skb->data[0] << 8) & 0xF00) + ((skb->data[1] << 0) & 0x0FF);

	/*
	 *	LCI of zero is always क्रम us, and its always a link control
	 *	frame.
	 */
	अगर (lci == 0) अणु
		x25_link_control(skb, nb, frametype);
		वापस 0;
	पूर्ण

	/*
	 *	Find an existing socket.
	 */
	अगर ((sk = x25_find_socket(lci, nb)) != शून्य) अणु
		पूर्णांक queued = 1;

		skb_reset_transport_header(skb);
		bh_lock_sock(sk);
		अगर (!sock_owned_by_user(sk)) अणु
			queued = x25_process_rx_frame(sk, skb);
		पूर्ण अन्यथा अणु
			queued = !sk_add_backlog(sk, skb, READ_ONCE(sk->sk_rcvbuf));
		पूर्ण
		bh_unlock_sock(sk);
		sock_put(sk);
		वापस queued;
	पूर्ण

	/*
	 *	Is is a Call Request ? अगर so process it.
	 */
	अगर (frametype == X25_CALL_REQUEST)
		वापस x25_rx_call_request(skb, nb, lci);

	/*
	 * 	Its not a Call Request, nor is it a control frame.
	 *	Can we क्रमward it?
	 */

	अगर (x25_क्रमward_data(lci, nb, skb)) अणु
		अगर (frametype == X25_CLEAR_CONFIRMATION) अणु
			x25_clear_क्रमward_by_lci(lci);
		पूर्ण
		kमुक्त_skb(skb);
		वापस 1;
	पूर्ण

/*
	x25_transmit_clear_request(nb, lci, 0x0D);
*/

	अगर (frametype != X25_CLEAR_CONFIRMATION)
		pr_debug("x25_receive_data(): unknown frame type %2x\n",frametype);

	वापस 0;
पूर्ण

पूर्णांक x25_lapb_receive_frame(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			   काष्ठा packet_type *ptype, काष्ठा net_device *orig_dev)
अणु
	काष्ठा sk_buff *nskb;
	काष्ठा x25_neigh *nb;

	अगर (!net_eq(dev_net(dev), &init_net))
		जाओ drop;

	nskb = skb_copy(skb, GFP_ATOMIC);
	अगर (!nskb)
		जाओ drop;
	kमुक्त_skb(skb);
	skb = nskb;

	/*
	 * Packet received from unrecognised device, throw it away.
	 */
	nb = x25_get_neigh(dev);
	अगर (!nb) अणु
		pr_debug("unknown neighbour - %s\n", dev->name);
		जाओ drop;
	पूर्ण

	अगर (!pskb_may_pull(skb, 1)) अणु
		x25_neigh_put(nb);
		वापस 0;
	पूर्ण

	चयन (skb->data[0]) अणु

	हाल X25_IFACE_DATA:
		skb_pull(skb, 1);
		अगर (x25_receive_data(skb, nb)) अणु
			x25_neigh_put(nb);
			जाओ out;
		पूर्ण
		अवरोध;

	हाल X25_IFACE_CONNECT:
		x25_link_established(nb);
		अवरोध;

	हाल X25_IFACE_DISCONNECT:
		x25_link_terminated(nb);
		अवरोध;
	पूर्ण
	x25_neigh_put(nb);
drop:
	kमुक्त_skb(skb);
out:
	वापस 0;
पूर्ण

व्योम x25_establish_link(काष्ठा x25_neigh *nb)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *ptr;

	चयन (nb->dev->type) अणु
	हाल ARPHRD_X25:
		अगर ((skb = alloc_skb(1, GFP_ATOMIC)) == शून्य) अणु
			pr_err("x25_dev: out of memory\n");
			वापस;
		पूर्ण
		ptr  = skb_put(skb, 1);
		*ptr = X25_IFACE_CONNECT;
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	skb->protocol = htons(ETH_P_X25);
	skb->dev      = nb->dev;

	dev_queue_xmit(skb);
पूर्ण

व्योम x25_terminate_link(काष्ठा x25_neigh *nb)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *ptr;

	अगर (nb->dev->type != ARPHRD_X25)
		वापस;

	skb = alloc_skb(1, GFP_ATOMIC);
	अगर (!skb) अणु
		pr_err("x25_dev: out of memory\n");
		वापस;
	पूर्ण

	ptr  = skb_put(skb, 1);
	*ptr = X25_IFACE_DISCONNECT;

	skb->protocol = htons(ETH_P_X25);
	skb->dev      = nb->dev;
	dev_queue_xmit(skb);
पूर्ण

व्योम x25_send_frame(काष्ठा sk_buff *skb, काष्ठा x25_neigh *nb)
अणु
	अचिन्हित अक्षर *dptr;

	skb_reset_network_header(skb);

	चयन (nb->dev->type) अणु
	हाल ARPHRD_X25:
		dptr  = skb_push(skb, 1);
		*dptr = X25_IFACE_DATA;
		अवरोध;

	शेष:
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	skb->protocol = htons(ETH_P_X25);
	skb->dev      = nb->dev;

	dev_queue_xmit(skb);
पूर्ण
