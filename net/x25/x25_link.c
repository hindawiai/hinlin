<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	X.25 Packet Layer release 002
 *
 *	This is ALPHA test software. This code may अवरोध your machine,
 *	अक्रमomly fail to work with new releases, misbehave and/or generally
 *	screw up. It might even work.
 *
 *	This code REQUIRES 2.1.15 or higher
 *
 *	History
 *	X.25 001	Jonathan Naylor	  Started coding.
 *	X.25 002	Jonathan Naylor	  New समयr architecture.
 *	mar/20/00	Daniela Squassoni Disabling/enabling of facilities
 *					  negotiation.
 *	2000-09-04	Henner Eisen	  dev_hold() / dev_put() क्रम x25_neigh.
 */

#घोषणा pr_fmt(fmt) "X25: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/init.h>
#समावेश <net/x25.h>

LIST_HEAD(x25_neigh_list);
DEFINE_RWLOCK(x25_neigh_list_lock);

अटल व्योम x25_t20समयr_expiry(काष्ठा समयr_list *);

अटल व्योम x25_transmit_restart_confirmation(काष्ठा x25_neigh *nb);
अटल व्योम x25_transmit_restart_request(काष्ठा x25_neigh *nb);

/*
 *	Linux set/reset समयr routines
 */
अटल अंतरभूत व्योम x25_start_t20समयr(काष्ठा x25_neigh *nb)
अणु
	mod_समयr(&nb->t20समयr, jअगरfies + nb->t20);
पूर्ण

अटल व्योम x25_t20समयr_expiry(काष्ठा समयr_list *t)
अणु
	काष्ठा x25_neigh *nb = from_समयr(nb, t, t20समयr);

	x25_transmit_restart_request(nb);

	x25_start_t20समयr(nb);
पूर्ण

अटल अंतरभूत व्योम x25_stop_t20समयr(काष्ठा x25_neigh *nb)
अणु
	del_समयr(&nb->t20समयr);
पूर्ण

/*
 *	This handles all restart and diagnostic frames.
 */
व्योम x25_link_control(काष्ठा sk_buff *skb, काष्ठा x25_neigh *nb,
		      अचिन्हित लघु frametype)
अणु
	काष्ठा sk_buff *skbn;

	चयन (frametype) अणु
	हाल X25_RESTART_REQUEST:
		चयन (nb->state) अणु
		हाल X25_LINK_STATE_0:
			/* This can happen when the x25 module just माला_लो loaded
			 * and करोesn't know layer 2 has alपढ़ोy connected
			 */
			nb->state = X25_LINK_STATE_3;
			x25_transmit_restart_confirmation(nb);
			अवरोध;
		हाल X25_LINK_STATE_2:
			x25_stop_t20समयr(nb);
			nb->state = X25_LINK_STATE_3;
			अवरोध;
		हाल X25_LINK_STATE_3:
			/* clear existing भव calls */
			x25_समाप्त_by_neigh(nb);

			x25_transmit_restart_confirmation(nb);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल X25_RESTART_CONFIRMATION:
		चयन (nb->state) अणु
		हाल X25_LINK_STATE_2:
			x25_stop_t20समयr(nb);
			nb->state = X25_LINK_STATE_3;
			अवरोध;
		हाल X25_LINK_STATE_3:
			/* clear existing भव calls */
			x25_समाप्त_by_neigh(nb);

			x25_transmit_restart_request(nb);
			nb->state = X25_LINK_STATE_2;
			x25_start_t20समयr(nb);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल X25_DIAGNOSTIC:
		अगर (!pskb_may_pull(skb, X25_STD_MIN_LEN + 4))
			अवरोध;

		pr_warn("diagnostic #%d - %02X %02X %02X\n",
		       skb->data[3], skb->data[4],
		       skb->data[5], skb->data[6]);
		अवरोध;

	शेष:
		pr_warn("received unknown %02X with LCI 000\n",
		       frametype);
		अवरोध;
	पूर्ण

	अगर (nb->state == X25_LINK_STATE_3)
		जबतक ((skbn = skb_dequeue(&nb->queue)) != शून्य)
			x25_send_frame(skbn, nb);
पूर्ण

/*
 *	This routine is called when a Restart Request is needed
 */
अटल व्योम x25_transmit_restart_request(काष्ठा x25_neigh *nb)
अणु
	अचिन्हित अक्षर *dptr;
	पूर्णांक len = X25_MAX_L2_LEN + X25_STD_MIN_LEN + 2;
	काष्ठा sk_buff *skb = alloc_skb(len, GFP_ATOMIC);

	अगर (!skb)
		वापस;

	skb_reserve(skb, X25_MAX_L2_LEN);

	dptr = skb_put(skb, X25_STD_MIN_LEN + 2);

	*dptr++ = nb->extended ? X25_GFI_EXTSEQ : X25_GFI_STDSEQ;
	*dptr++ = 0x00;
	*dptr++ = X25_RESTART_REQUEST;
	*dptr++ = 0x00;
	*dptr++ = 0;

	skb->sk = शून्य;

	x25_send_frame(skb, nb);
पूर्ण

/*
 * This routine is called when a Restart Confirmation is needed
 */
अटल व्योम x25_transmit_restart_confirmation(काष्ठा x25_neigh *nb)
अणु
	अचिन्हित अक्षर *dptr;
	पूर्णांक len = X25_MAX_L2_LEN + X25_STD_MIN_LEN;
	काष्ठा sk_buff *skb = alloc_skb(len, GFP_ATOMIC);

	अगर (!skb)
		वापस;

	skb_reserve(skb, X25_MAX_L2_LEN);

	dptr = skb_put(skb, X25_STD_MIN_LEN);

	*dptr++ = nb->extended ? X25_GFI_EXTSEQ : X25_GFI_STDSEQ;
	*dptr++ = 0x00;
	*dptr++ = X25_RESTART_CONFIRMATION;

	skb->sk = शून्य;

	x25_send_frame(skb, nb);
पूर्ण

/*
 *	This routine is called when a Clear Request is needed outside of the context
 *	of a connected socket.
 */
व्योम x25_transmit_clear_request(काष्ठा x25_neigh *nb, अचिन्हित पूर्णांक lci,
				अचिन्हित अक्षर cause)
अणु
	अचिन्हित अक्षर *dptr;
	पूर्णांक len = X25_MAX_L2_LEN + X25_STD_MIN_LEN + 2;
	काष्ठा sk_buff *skb = alloc_skb(len, GFP_ATOMIC);

	अगर (!skb)
		वापस;

	skb_reserve(skb, X25_MAX_L2_LEN);

	dptr = skb_put(skb, X25_STD_MIN_LEN + 2);

	*dptr++ = ((lci >> 8) & 0x0F) | (nb->extended ?
					 X25_GFI_EXTSEQ :
					 X25_GFI_STDSEQ);
	*dptr++ = (lci >> 0) & 0xFF;
	*dptr++ = X25_CLEAR_REQUEST;
	*dptr++ = cause;
	*dptr++ = 0x00;

	skb->sk = शून्य;

	x25_send_frame(skb, nb);
पूर्ण

व्योम x25_transmit_link(काष्ठा sk_buff *skb, काष्ठा x25_neigh *nb)
अणु
	चयन (nb->state) अणु
	हाल X25_LINK_STATE_0:
		skb_queue_tail(&nb->queue, skb);
		nb->state = X25_LINK_STATE_1;
		x25_establish_link(nb);
		अवरोध;
	हाल X25_LINK_STATE_1:
	हाल X25_LINK_STATE_2:
		skb_queue_tail(&nb->queue, skb);
		अवरोध;
	हाल X25_LINK_STATE_3:
		x25_send_frame(skb, nb);
		अवरोध;
	पूर्ण
पूर्ण

/*
 *	Called when the link layer has become established.
 */
व्योम x25_link_established(काष्ठा x25_neigh *nb)
अणु
	चयन (nb->state) अणु
	हाल X25_LINK_STATE_0:
	हाल X25_LINK_STATE_1:
		x25_transmit_restart_request(nb);
		nb->state = X25_LINK_STATE_2;
		x25_start_t20समयr(nb);
		अवरोध;
	पूर्ण
पूर्ण

/*
 *	Called when the link layer has terminated, or an establishment
 *	request has failed.
 */

व्योम x25_link_terminated(काष्ठा x25_neigh *nb)
अणु
	nb->state = X25_LINK_STATE_0;
	skb_queue_purge(&nb->queue);
	x25_stop_t20समयr(nb);

	/* Out of order: clear existing भव calls (X.25 03/93 4.6.3) */
	x25_समाप्त_by_neigh(nb);
पूर्ण

/*
 *	Add a new device.
 */
व्योम x25_link_device_up(काष्ठा net_device *dev)
अणु
	काष्ठा x25_neigh *nb = kदो_स्मृति(माप(*nb), GFP_ATOMIC);

	अगर (!nb)
		वापस;

	skb_queue_head_init(&nb->queue);
	समयr_setup(&nb->t20समयr, x25_t20समयr_expiry, 0);

	dev_hold(dev);
	nb->dev      = dev;
	nb->state    = X25_LINK_STATE_0;
	nb->extended = 0;
	/*
	 * Enables negotiation
	 */
	nb->global_facil_mask = X25_MASK_REVERSE |
				       X25_MASK_THROUGHPUT |
				       X25_MASK_PACKET_SIZE |
				       X25_MASK_WINDOW_SIZE;
	nb->t20      = sysctl_x25_restart_request_समयout;
	refcount_set(&nb->refcnt, 1);

	ग_लिखो_lock_bh(&x25_neigh_list_lock);
	list_add(&nb->node, &x25_neigh_list);
	ग_लिखो_unlock_bh(&x25_neigh_list_lock);
पूर्ण

/**
 *	__x25_हटाओ_neigh - हटाओ neighbour from x25_neigh_list
 *	@nb: - neigh to हटाओ
 *
 *	Remove neighbour from x25_neigh_list. If it was there.
 *	Caller must hold x25_neigh_list_lock.
 */
अटल व्योम __x25_हटाओ_neigh(काष्ठा x25_neigh *nb)
अणु
	अगर (nb->node.next) अणु
		list_del(&nb->node);
		x25_neigh_put(nb);
	पूर्ण
पूर्ण

/*
 *	A device has been हटाओd, हटाओ its links.
 */
व्योम x25_link_device_करोwn(काष्ठा net_device *dev)
अणु
	काष्ठा x25_neigh *nb;
	काष्ठा list_head *entry, *पंचांगp;

	ग_लिखो_lock_bh(&x25_neigh_list_lock);

	list_क्रम_each_safe(entry, पंचांगp, &x25_neigh_list) अणु
		nb = list_entry(entry, काष्ठा x25_neigh, node);

		अगर (nb->dev == dev) अणु
			__x25_हटाओ_neigh(nb);
			dev_put(dev);
		पूर्ण
	पूर्ण

	ग_लिखो_unlock_bh(&x25_neigh_list_lock);
पूर्ण

/*
 *	Given a device, वापस the neighbour address.
 */
काष्ठा x25_neigh *x25_get_neigh(काष्ठा net_device *dev)
अणु
	काष्ठा x25_neigh *nb, *use = शून्य;
	काष्ठा list_head *entry;

	पढ़ो_lock_bh(&x25_neigh_list_lock);
	list_क्रम_each(entry, &x25_neigh_list) अणु
		nb = list_entry(entry, काष्ठा x25_neigh, node);

		अगर (nb->dev == dev) अणु
			use = nb;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (use)
		x25_neigh_hold(use);
	पढ़ो_unlock_bh(&x25_neigh_list_lock);
	वापस use;
पूर्ण

/*
 *	Handle the ioctls that control the subscription functions.
 */
पूर्णांक x25_subscr_ioctl(अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	काष्ठा x25_subscrip_काष्ठा x25_subscr;
	काष्ठा x25_neigh *nb;
	काष्ठा net_device *dev;
	पूर्णांक rc = -EINVAL;

	अगर (cmd != SIOCX25GSUBSCRIP && cmd != SIOCX25SSUBSCRIP)
		जाओ out;

	rc = -EFAULT;
	अगर (copy_from_user(&x25_subscr, arg, माप(x25_subscr)))
		जाओ out;

	rc = -EINVAL;
	अगर ((dev = x25_dev_get(x25_subscr.device)) == शून्य)
		जाओ out;

	अगर ((nb = x25_get_neigh(dev)) == शून्य)
		जाओ out_dev_put;

	dev_put(dev);

	अगर (cmd == SIOCX25GSUBSCRIP) अणु
		पढ़ो_lock_bh(&x25_neigh_list_lock);
		x25_subscr.extended	     = nb->extended;
		x25_subscr.global_facil_mask = nb->global_facil_mask;
		पढ़ो_unlock_bh(&x25_neigh_list_lock);
		rc = copy_to_user(arg, &x25_subscr,
				  माप(x25_subscr)) ? -EFAULT : 0;
	पूर्ण अन्यथा अणु
		rc = -EINVAL;
		अगर (!(x25_subscr.extended && x25_subscr.extended != 1)) अणु
			rc = 0;
			ग_लिखो_lock_bh(&x25_neigh_list_lock);
			nb->extended	     = x25_subscr.extended;
			nb->global_facil_mask = x25_subscr.global_facil_mask;
			ग_लिखो_unlock_bh(&x25_neigh_list_lock);
		पूर्ण
	पूर्ण
	x25_neigh_put(nb);
out:
	वापस rc;
out_dev_put:
	dev_put(dev);
	जाओ out;
पूर्ण


/*
 *	Release all memory associated with X.25 neighbour काष्ठाures.
 */
व्योम __निकास x25_link_मुक्त(व्योम)
अणु
	काष्ठा x25_neigh *nb;
	काष्ठा list_head *entry, *पंचांगp;

	ग_लिखो_lock_bh(&x25_neigh_list_lock);

	list_क्रम_each_safe(entry, पंचांगp, &x25_neigh_list) अणु
		काष्ठा net_device *dev;

		nb = list_entry(entry, काष्ठा x25_neigh, node);
		dev = nb->dev;
		__x25_हटाओ_neigh(nb);
		dev_put(dev);
	पूर्ण
	ग_लिखो_unlock_bh(&x25_neigh_list_lock);
पूर्ण
