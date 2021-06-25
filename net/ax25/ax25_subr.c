<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Alan Cox GW4PTS (alan@lxorguk.ukuu.org.uk)
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 * Copyright (C) Joerg Reuter DL1BKE (jreuter@yaina.de)
 * Copyright (C) Frederic Rible F1OAT (frible@teaser.fr)
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/slab.h>
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>

/*
 *	This routine purges all the queues of frames.
 */
व्योम ax25_clear_queues(ax25_cb *ax25)
अणु
	skb_queue_purge(&ax25->ग_लिखो_queue);
	skb_queue_purge(&ax25->ack_queue);
	skb_queue_purge(&ax25->reseq_queue);
	skb_queue_purge(&ax25->frag_queue);
पूर्ण

/*
 * This routine purges the input queue of those frames that have been
 * acknowledged. This replaces the boxes labelled "V(a) <- N(r)" on the
 * SDL diagram.
 */
व्योम ax25_frames_acked(ax25_cb *ax25, अचिन्हित लघु nr)
अणु
	काष्ठा sk_buff *skb;

	/*
	 * Remove all the ack-ed frames from the ack queue.
	 */
	अगर (ax25->va != nr) अणु
		जबतक (skb_peek(&ax25->ack_queue) != शून्य && ax25->va != nr) अणु
			skb = skb_dequeue(&ax25->ack_queue);
			kमुक्त_skb(skb);
			ax25->va = (ax25->va + 1) % ax25->modulus;
		पूर्ण
	पूर्ण
पूर्ण

व्योम ax25_requeue_frames(ax25_cb *ax25)
अणु
	काष्ठा sk_buff *skb;

	/*
	 * Requeue all the un-ack-ed frames on the output queue to be picked
	 * up by ax25_kick called from the समयr. This arrangement handles the
	 * possibility of an empty output queue.
	 */
	जबतक ((skb = skb_dequeue_tail(&ax25->ack_queue)) != शून्य)
		skb_queue_head(&ax25->ग_लिखो_queue, skb);
पूर्ण

/*
 *	Validate that the value of nr is between va and vs. Return true or
 *	false क्रम testing.
 */
पूर्णांक ax25_validate_nr(ax25_cb *ax25, अचिन्हित लघु nr)
अणु
	अचिन्हित लघु vc = ax25->va;

	जबतक (vc != ax25->vs) अणु
		अगर (nr == vc) वापस 1;
		vc = (vc + 1) % ax25->modulus;
	पूर्ण

	अगर (nr == ax25->vs) वापस 1;

	वापस 0;
पूर्ण

/*
 *	This routine is the centralised routine क्रम parsing the control
 *	inक्रमmation क्रम the dअगरferent frame क्रमmats.
 */
पूर्णांक ax25_decode(ax25_cb *ax25, काष्ठा sk_buff *skb, पूर्णांक *ns, पूर्णांक *nr, पूर्णांक *pf)
अणु
	अचिन्हित अक्षर *frame;
	पूर्णांक frametype = AX25_ILLEGAL;

	frame = skb->data;
	*ns = *nr = *pf = 0;

	अगर (ax25->modulus == AX25_MODULUS) अणु
		अगर ((frame[0] & AX25_S) == 0) अणु
			frametype = AX25_I;			/* I frame - carries NR/NS/PF */
			*ns = (frame[0] >> 1) & 0x07;
			*nr = (frame[0] >> 5) & 0x07;
			*pf = frame[0] & AX25_PF;
		पूर्ण अन्यथा अगर ((frame[0] & AX25_U) == 1) अणु 	/* S frame - take out PF/NR */
			frametype = frame[0] & 0x0F;
			*nr = (frame[0] >> 5) & 0x07;
			*pf = frame[0] & AX25_PF;
		पूर्ण अन्यथा अगर ((frame[0] & AX25_U) == 3) अणु 	/* U frame - take out PF */
			frametype = frame[0] & ~AX25_PF;
			*pf = frame[0] & AX25_PF;
		पूर्ण
		skb_pull(skb, 1);
	पूर्ण अन्यथा अणु
		अगर ((frame[0] & AX25_S) == 0) अणु
			frametype = AX25_I;			/* I frame - carries NR/NS/PF */
			*ns = (frame[0] >> 1) & 0x7F;
			*nr = (frame[1] >> 1) & 0x7F;
			*pf = frame[1] & AX25_EPF;
			skb_pull(skb, 2);
		पूर्ण अन्यथा अगर ((frame[0] & AX25_U) == 1) अणु 	/* S frame - take out PF/NR */
			frametype = frame[0] & 0x0F;
			*nr = (frame[1] >> 1) & 0x7F;
			*pf = frame[1] & AX25_EPF;
			skb_pull(skb, 2);
		पूर्ण अन्यथा अगर ((frame[0] & AX25_U) == 3) अणु 	/* U frame - take out PF */
			frametype = frame[0] & ~AX25_PF;
			*pf = frame[0] & AX25_PF;
			skb_pull(skb, 1);
		पूर्ण
	पूर्ण

	वापस frametype;
पूर्ण

/*
 *	This routine is called when the HDLC layer पूर्णांकernally  generates a
 *	command or  response  क्रम  the remote machine ( eg. RR, UA etc. ).
 *	Only supervisory or unnumbered frames are processed.
 */
व्योम ax25_send_control(ax25_cb *ax25, पूर्णांक frametype, पूर्णांक poll_bit, पूर्णांक type)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर  *dptr;

	अगर ((skb = alloc_skb(ax25->ax25_dev->dev->hard_header_len + 2, GFP_ATOMIC)) == शून्य)
		वापस;

	skb_reserve(skb, ax25->ax25_dev->dev->hard_header_len);

	skb_reset_network_header(skb);

	/* Assume a response - address काष्ठाure क्रम DTE */
	अगर (ax25->modulus == AX25_MODULUS) अणु
		dptr = skb_put(skb, 1);
		*dptr = frametype;
		*dptr |= (poll_bit) ? AX25_PF : 0;
		अगर ((frametype & AX25_U) == AX25_S)		/* S frames carry NR */
			*dptr |= (ax25->vr << 5);
	पूर्ण अन्यथा अणु
		अगर ((frametype & AX25_U) == AX25_U) अणु
			dptr = skb_put(skb, 1);
			*dptr = frametype;
			*dptr |= (poll_bit) ? AX25_PF : 0;
		पूर्ण अन्यथा अणु
			dptr = skb_put(skb, 2);
			dptr[0] = frametype;
			dptr[1] = (ax25->vr << 1);
			dptr[1] |= (poll_bit) ? AX25_EPF : 0;
		पूर्ण
	पूर्ण

	ax25_transmit_buffer(ax25, skb, type);
पूर्ण

/*
 *	Send a 'DM' to an unknown connection attempt, or an invalid caller.
 *
 *	Note: src here is the sender, thus it's the target of the DM
 */
व्योम ax25_वापस_dm(काष्ठा net_device *dev, ax25_address *src, ax25_address *dest, ax25_digi *digi)
अणु
	काष्ठा sk_buff *skb;
	अक्षर *dptr;
	ax25_digi retdigi;

	अगर (dev == शून्य)
		वापस;

	अगर ((skb = alloc_skb(dev->hard_header_len + 1, GFP_ATOMIC)) == शून्य)
		वापस;	/* Next SABM will get DM'd */

	skb_reserve(skb, dev->hard_header_len);
	skb_reset_network_header(skb);

	ax25_digi_invert(digi, &retdigi);

	dptr = skb_put(skb, 1);

	*dptr = AX25_DM | AX25_PF;

	/*
	 *	Do the address ourselves
	 */
	dptr  = skb_push(skb, ax25_addr_size(digi));
	dptr += ax25_addr_build(dptr, dest, src, &retdigi, AX25_RESPONSE, AX25_MODULUS);

	ax25_queue_xmit(skb, dev);
पूर्ण

/*
 *	Exponential backoff क्रम AX.25
 */
व्योम ax25_calculate_t1(ax25_cb *ax25)
अणु
	पूर्णांक n, t = 2;

	चयन (ax25->backoff) अणु
	हाल 0:
		अवरोध;

	हाल 1:
		t += 2 * ax25->n2count;
		अवरोध;

	हाल 2:
		क्रम (n = 0; n < ax25->n2count; n++)
			t *= 2;
		अगर (t > 8) t = 8;
		अवरोध;
	पूर्ण

	ax25->t1 = t * ax25->rtt;
पूर्ण

/*
 *	Calculate the Round Trip Time
 */
व्योम ax25_calculate_rtt(ax25_cb *ax25)
अणु
	अगर (ax25->backoff == 0)
		वापस;

	अगर (ax25_t1समयr_running(ax25) && ax25->n2count == 0)
		ax25->rtt = (9 * ax25->rtt + ax25->t1 - ax25_display_समयr(&ax25->t1समयr)) / 10;

	अगर (ax25->rtt < AX25_T1CLAMPLO)
		ax25->rtt = AX25_T1CLAMPLO;

	अगर (ax25->rtt > AX25_T1CLAMPHI)
		ax25->rtt = AX25_T1CLAMPHI;
पूर्ण

व्योम ax25_disconnect(ax25_cb *ax25, पूर्णांक reason)
अणु
	ax25_clear_queues(ax25);

	अगर (!ax25->sk || !sock_flag(ax25->sk, SOCK_DESTROY))
		ax25_stop_heartbeat(ax25);
	ax25_stop_t1समयr(ax25);
	ax25_stop_t2समयr(ax25);
	ax25_stop_t3समयr(ax25);
	ax25_stop_idleसमयr(ax25);

	ax25->state = AX25_STATE_0;

	ax25_link_failed(ax25, reason);

	अगर (ax25->sk != शून्य) अणु
		local_bh_disable();
		bh_lock_sock(ax25->sk);
		ax25->sk->sk_state     = TCP_CLOSE;
		ax25->sk->sk_err       = reason;
		ax25->sk->sk_shutकरोwn |= SEND_SHUTDOWN;
		अगर (!sock_flag(ax25->sk, SOCK_DEAD)) अणु
			ax25->sk->sk_state_change(ax25->sk);
			sock_set_flag(ax25->sk, SOCK_DEAD);
		पूर्ण
		bh_unlock_sock(ax25->sk);
		local_bh_enable();
	पूर्ण
पूर्ण
