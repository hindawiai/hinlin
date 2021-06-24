<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
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
#समावेश <linux/gfp.h>
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <net/rose.h>

/*
 *	This procedure is passed a buffer descriptor क्रम an अगरrame. It builds
 *	the rest of the control part of the frame and then ग_लिखोs it out.
 */
अटल व्योम rose_send_अगरrame(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा rose_sock *rose = rose_sk(sk);

	अगर (skb == शून्य)
		वापस;

	skb->data[2] |= (rose->vr << 5) & 0xE0;
	skb->data[2] |= (rose->vs << 1) & 0x0E;

	rose_start_idleसमयr(sk);

	rose_transmit_link(skb, rose->neighbour);
पूर्ण

व्योम rose_kick(काष्ठा sock *sk)
अणु
	काष्ठा rose_sock *rose = rose_sk(sk);
	काष्ठा sk_buff *skb, *skbn;
	अचिन्हित लघु start, end;

	अगर (rose->state != ROSE_STATE_3)
		वापस;

	अगर (rose->condition & ROSE_COND_PEER_RX_BUSY)
		वापस;

	अगर (!skb_peek(&sk->sk_ग_लिखो_queue))
		वापस;

	start = (skb_peek(&rose->ack_queue) == शून्य) ? rose->va : rose->vs;
	end   = (rose->va + sysctl_rose_winकरोw_size) % ROSE_MODULUS;

	अगर (start == end)
		वापस;

	rose->vs = start;

	/*
	 * Transmit data until either we're out of data to send or
	 * the winकरोw is full.
	 */

	skb  = skb_dequeue(&sk->sk_ग_लिखो_queue);

	करो अणु
		अगर ((skbn = skb_clone(skb, GFP_ATOMIC)) == शून्य) अणु
			skb_queue_head(&sk->sk_ग_लिखो_queue, skb);
			अवरोध;
		पूर्ण

		skb_set_owner_w(skbn, sk);

		/*
		 * Transmit the frame copy.
		 */
		rose_send_अगरrame(sk, skbn);

		rose->vs = (rose->vs + 1) % ROSE_MODULUS;

		/*
		 * Requeue the original data frame.
		 */
		skb_queue_tail(&rose->ack_queue, skb);

	पूर्ण जबतक (rose->vs != end &&
		 (skb = skb_dequeue(&sk->sk_ग_लिखो_queue)) != शून्य);

	rose->vl         = rose->vr;
	rose->condition &= ~ROSE_COND_ACK_PENDING;

	rose_stop_समयr(sk);
पूर्ण

/*
 * The following routines are taken from page 170 of the 7th ARRL Computer
 * Networking Conference paper, as is the whole state machine.
 */

व्योम rose_enquiry_response(काष्ठा sock *sk)
अणु
	काष्ठा rose_sock *rose = rose_sk(sk);

	अगर (rose->condition & ROSE_COND_OWN_RX_BUSY)
		rose_ग_लिखो_पूर्णांकernal(sk, ROSE_RNR);
	अन्यथा
		rose_ग_लिखो_पूर्णांकernal(sk, ROSE_RR);

	rose->vl         = rose->vr;
	rose->condition &= ~ROSE_COND_ACK_PENDING;

	rose_stop_समयr(sk);
पूर्ण
