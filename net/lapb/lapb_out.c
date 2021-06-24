<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	LAPB release 002
 *
 *	This code REQUIRES 2.1.15 or higher/ NET3.038
 *
 *	History
 *	LAPB 001	Jonathan Naylor	Started Coding
 *	LAPB 002	Jonathan Naylor	New समयr architecture.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/inet.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <net/lapb.h>

/*
 *  This procedure is passed a buffer descriptor क्रम an अगरrame. It builds
 *  the rest of the control part of the frame and then ग_लिखोs it out.
 */
अटल व्योम lapb_send_अगरrame(काष्ठा lapb_cb *lapb, काष्ठा sk_buff *skb, पूर्णांक poll_bit)
अणु
	अचिन्हित अक्षर *frame;

	अगर (!skb)
		वापस;

	अगर (lapb->mode & LAPB_EXTENDED) अणु
		frame = skb_push(skb, 2);

		frame[0] = LAPB_I;
		frame[0] |= lapb->vs << 1;
		frame[1] = poll_bit ? LAPB_EPF : 0;
		frame[1] |= lapb->vr << 1;
	पूर्ण अन्यथा अणु
		frame = skb_push(skb, 1);

		*frame = LAPB_I;
		*frame |= poll_bit ? LAPB_SPF : 0;
		*frame |= lapb->vr << 5;
		*frame |= lapb->vs << 1;
	पूर्ण

	lapb_dbg(1, "(%p) S%d TX I(%d) S%d R%d\n",
		 lapb->dev, lapb->state, poll_bit, lapb->vs, lapb->vr);

	lapb_transmit_buffer(lapb, skb, LAPB_COMMAND);
पूर्ण

व्योम lapb_kick(काष्ठा lapb_cb *lapb)
अणु
	काष्ठा sk_buff *skb, *skbn;
	अचिन्हित लघु modulus, start, end;

	modulus = (lapb->mode & LAPB_EXTENDED) ? LAPB_EMODULUS : LAPB_SMODULUS;
	start = !skb_peek(&lapb->ack_queue) ? lapb->va : lapb->vs;
	end   = (lapb->va + lapb->winकरोw) % modulus;

	अगर (!(lapb->condition & LAPB_PEER_RX_BUSY_CONDITION) &&
	    start != end && skb_peek(&lapb->ग_लिखो_queue)) अणु
		lapb->vs = start;

		/*
		 * Dequeue the frame and copy it.
		 */
		skb = skb_dequeue(&lapb->ग_लिखो_queue);

		करो अणु
			skbn = skb_copy(skb, GFP_ATOMIC);
			अगर (!skbn) अणु
				skb_queue_head(&lapb->ग_लिखो_queue, skb);
				अवरोध;
			पूर्ण

			अगर (skb->sk)
				skb_set_owner_w(skbn, skb->sk);

			/*
			 * Transmit the frame copy.
			 */
			lapb_send_अगरrame(lapb, skbn, LAPB_POLLOFF);

			lapb->vs = (lapb->vs + 1) % modulus;

			/*
			 * Requeue the original data frame.
			 */
			skb_queue_tail(&lapb->ack_queue, skb);

		पूर्ण जबतक (lapb->vs != end && (skb = skb_dequeue(&lapb->ग_लिखो_queue)) != शून्य);

		lapb->condition &= ~LAPB_ACK_PENDING_CONDITION;

		अगर (!lapb_t1समयr_running(lapb))
			lapb_start_t1समयr(lapb);
	पूर्ण
पूर्ण

व्योम lapb_transmit_buffer(काष्ठा lapb_cb *lapb, काष्ठा sk_buff *skb, पूर्णांक type)
अणु
	अचिन्हित अक्षर *ptr;

	ptr = skb_push(skb, 1);

	अगर (lapb->mode & LAPB_MLP) अणु
		अगर (lapb->mode & LAPB_DCE) अणु
			अगर (type == LAPB_COMMAND)
				*ptr = LAPB_ADDR_C;
			अगर (type == LAPB_RESPONSE)
				*ptr = LAPB_ADDR_D;
		पूर्ण अन्यथा अणु
			अगर (type == LAPB_COMMAND)
				*ptr = LAPB_ADDR_D;
			अगर (type == LAPB_RESPONSE)
				*ptr = LAPB_ADDR_C;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (lapb->mode & LAPB_DCE) अणु
			अगर (type == LAPB_COMMAND)
				*ptr = LAPB_ADDR_A;
			अगर (type == LAPB_RESPONSE)
				*ptr = LAPB_ADDR_B;
		पूर्ण अन्यथा अणु
			अगर (type == LAPB_COMMAND)
				*ptr = LAPB_ADDR_B;
			अगर (type == LAPB_RESPONSE)
				*ptr = LAPB_ADDR_A;
		पूर्ण
	पूर्ण

	lapb_dbg(2, "(%p) S%d TX %3ph\n", lapb->dev, lapb->state, skb->data);

	अगर (!lapb_data_transmit(lapb, skb))
		kमुक्त_skb(skb);
पूर्ण

व्योम lapb_establish_data_link(काष्ठा lapb_cb *lapb)
अणु
	lapb->condition = 0x00;
	lapb->n2count   = 0;

	अगर (lapb->mode & LAPB_EXTENDED) अणु
		lapb_dbg(1, "(%p) S%d TX SABME(1)\n", lapb->dev, lapb->state);
		lapb_send_control(lapb, LAPB_SABME, LAPB_POLLON, LAPB_COMMAND);
	पूर्ण अन्यथा अणु
		lapb_dbg(1, "(%p) S%d TX SABM(1)\n", lapb->dev, lapb->state);
		lapb_send_control(lapb, LAPB_SABM, LAPB_POLLON, LAPB_COMMAND);
	पूर्ण

	lapb_start_t1समयr(lapb);
	lapb_stop_t2समयr(lapb);
पूर्ण

व्योम lapb_enquiry_response(काष्ठा lapb_cb *lapb)
अणु
	lapb_dbg(1, "(%p) S%d TX RR(1) R%d\n",
		 lapb->dev, lapb->state, lapb->vr);

	lapb_send_control(lapb, LAPB_RR, LAPB_POLLON, LAPB_RESPONSE);

	lapb->condition &= ~LAPB_ACK_PENDING_CONDITION;
पूर्ण

व्योम lapb_समयout_response(काष्ठा lapb_cb *lapb)
अणु
	lapb_dbg(1, "(%p) S%d TX RR(0) R%d\n",
		 lapb->dev, lapb->state, lapb->vr);
	lapb_send_control(lapb, LAPB_RR, LAPB_POLLOFF, LAPB_RESPONSE);

	lapb->condition &= ~LAPB_ACK_PENDING_CONDITION;
पूर्ण

व्योम lapb_check_अगरrames_acked(काष्ठा lapb_cb *lapb, अचिन्हित लघु nr)
अणु
	अगर (lapb->vs == nr) अणु
		lapb_frames_acked(lapb, nr);
		lapb_stop_t1समयr(lapb);
		lapb->n2count = 0;
	पूर्ण अन्यथा अगर (lapb->va != nr) अणु
		lapb_frames_acked(lapb, nr);
		lapb_start_t1समयr(lapb);
	पूर्ण
पूर्ण

व्योम lapb_check_need_response(काष्ठा lapb_cb *lapb, पूर्णांक type, पूर्णांक pf)
अणु
	अगर (type == LAPB_COMMAND && pf)
		lapb_enquiry_response(lapb);
पूर्ण
