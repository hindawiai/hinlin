<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	LAPB release 002
 *
 *	This code REQUIRES 2.1.15 or higher/ NET3.038
 *
 *	History
 *	LAPB 001	Jonathan Naylor	Started Coding
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
 *	This routine purges all the queues of frames.
 */
व्योम lapb_clear_queues(काष्ठा lapb_cb *lapb)
अणु
	skb_queue_purge(&lapb->ग_लिखो_queue);
	skb_queue_purge(&lapb->ack_queue);
पूर्ण

/*
 * This routine purges the input queue of those frames that have been
 * acknowledged. This replaces the boxes labelled "V(a) <- N(r)" on the
 * SDL diagram.
 */
व्योम lapb_frames_acked(काष्ठा lapb_cb *lapb, अचिन्हित लघु nr)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक modulus;

	modulus = (lapb->mode & LAPB_EXTENDED) ? LAPB_EMODULUS : LAPB_SMODULUS;

	/*
	 * Remove all the ack-ed frames from the ack queue.
	 */
	अगर (lapb->va != nr)
		जबतक (skb_peek(&lapb->ack_queue) && lapb->va != nr) अणु
			skb = skb_dequeue(&lapb->ack_queue);
			kमुक्त_skb(skb);
			lapb->va = (lapb->va + 1) % modulus;
		पूर्ण
पूर्ण

व्योम lapb_requeue_frames(काष्ठा lapb_cb *lapb)
अणु
	काष्ठा sk_buff *skb, *skb_prev = शून्य;

	/*
	 * Requeue all the un-ack-ed frames on the output queue to be picked
	 * up by lapb_kick called from the समयr. This arrangement handles the
	 * possibility of an empty output queue.
	 */
	जबतक ((skb = skb_dequeue(&lapb->ack_queue)) != शून्य) अणु
		अगर (!skb_prev)
			skb_queue_head(&lapb->ग_लिखो_queue, skb);
		अन्यथा
			skb_append(skb_prev, skb, &lapb->ग_लिखो_queue);
		skb_prev = skb;
	पूर्ण
पूर्ण

/*
 *	Validate that the value of nr is between va and vs. Return true or
 *	false क्रम testing.
 */
पूर्णांक lapb_validate_nr(काष्ठा lapb_cb *lapb, अचिन्हित लघु nr)
अणु
	अचिन्हित लघु vc = lapb->va;
	पूर्णांक modulus;

	modulus = (lapb->mode & LAPB_EXTENDED) ? LAPB_EMODULUS : LAPB_SMODULUS;

	जबतक (vc != lapb->vs) अणु
		अगर (nr == vc)
			वापस 1;
		vc = (vc + 1) % modulus;
	पूर्ण

	वापस nr == lapb->vs;
पूर्ण

/*
 *	This routine is the centralised routine क्रम parsing the control
 *	inक्रमmation क्रम the dअगरferent frame क्रमmats.
 */
पूर्णांक lapb_decode(काष्ठा lapb_cb *lapb, काष्ठा sk_buff *skb,
		काष्ठा lapb_frame *frame)
अणु
	frame->type = LAPB_ILLEGAL;

	lapb_dbg(2, "(%p) S%d RX %3ph\n", lapb->dev, lapb->state, skb->data);

	/* We always need to look at 2 bytes, someबार we need
	 * to look at 3 and those हालs are handled below.
	 */
	अगर (!pskb_may_pull(skb, 2))
		वापस -1;

	अगर (lapb->mode & LAPB_MLP) अणु
		अगर (lapb->mode & LAPB_DCE) अणु
			अगर (skb->data[0] == LAPB_ADDR_D)
				frame->cr = LAPB_COMMAND;
			अगर (skb->data[0] == LAPB_ADDR_C)
				frame->cr = LAPB_RESPONSE;
		पूर्ण अन्यथा अणु
			अगर (skb->data[0] == LAPB_ADDR_C)
				frame->cr = LAPB_COMMAND;
			अगर (skb->data[0] == LAPB_ADDR_D)
				frame->cr = LAPB_RESPONSE;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (lapb->mode & LAPB_DCE) अणु
			अगर (skb->data[0] == LAPB_ADDR_B)
				frame->cr = LAPB_COMMAND;
			अगर (skb->data[0] == LAPB_ADDR_A)
				frame->cr = LAPB_RESPONSE;
		पूर्ण अन्यथा अणु
			अगर (skb->data[0] == LAPB_ADDR_A)
				frame->cr = LAPB_COMMAND;
			अगर (skb->data[0] == LAPB_ADDR_B)
				frame->cr = LAPB_RESPONSE;
		पूर्ण
	पूर्ण

	skb_pull(skb, 1);

	अगर (lapb->mode & LAPB_EXTENDED) अणु
		अगर (!(skb->data[0] & LAPB_S)) अणु
			अगर (!pskb_may_pull(skb, 2))
				वापस -1;
			/*
			 * I frame - carries NR/NS/PF
			 */
			frame->type       = LAPB_I;
			frame->ns         = (skb->data[0] >> 1) & 0x7F;
			frame->nr         = (skb->data[1] >> 1) & 0x7F;
			frame->pf         = skb->data[1] & LAPB_EPF;
			frame->control[0] = skb->data[0];
			frame->control[1] = skb->data[1];
			skb_pull(skb, 2);
		पूर्ण अन्यथा अगर ((skb->data[0] & LAPB_U) == 1) अणु
			अगर (!pskb_may_pull(skb, 2))
				वापस -1;
			/*
			 * S frame - take out PF/NR
			 */
			frame->type       = skb->data[0] & 0x0F;
			frame->nr         = (skb->data[1] >> 1) & 0x7F;
			frame->pf         = skb->data[1] & LAPB_EPF;
			frame->control[0] = skb->data[0];
			frame->control[1] = skb->data[1];
			skb_pull(skb, 2);
		पूर्ण अन्यथा अगर ((skb->data[0] & LAPB_U) == 3) अणु
			/*
			 * U frame - take out PF
			 */
			frame->type       = skb->data[0] & ~LAPB_SPF;
			frame->pf         = skb->data[0] & LAPB_SPF;
			frame->control[0] = skb->data[0];
			frame->control[1] = 0x00;
			skb_pull(skb, 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!(skb->data[0] & LAPB_S)) अणु
			/*
			 * I frame - carries NR/NS/PF
			 */
			frame->type = LAPB_I;
			frame->ns   = (skb->data[0] >> 1) & 0x07;
			frame->nr   = (skb->data[0] >> 5) & 0x07;
			frame->pf   = skb->data[0] & LAPB_SPF;
		पूर्ण अन्यथा अगर ((skb->data[0] & LAPB_U) == 1) अणु
			/*
			 * S frame - take out PF/NR
			 */
			frame->type = skb->data[0] & 0x0F;
			frame->nr   = (skb->data[0] >> 5) & 0x07;
			frame->pf   = skb->data[0] & LAPB_SPF;
		पूर्ण अन्यथा अगर ((skb->data[0] & LAPB_U) == 3) अणु
			/*
			 * U frame - take out PF
			 */
			frame->type = skb->data[0] & ~LAPB_SPF;
			frame->pf   = skb->data[0] & LAPB_SPF;
		पूर्ण

		frame->control[0] = skb->data[0];

		skb_pull(skb, 1);
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	This routine is called when the HDLC layer पूर्णांकernally  generates a
 *	command or  response  क्रम  the remote machine ( eg. RR, UA etc. ).
 *	Only supervisory or unnumbered frames are processed, FRMRs are handled
 *	by lapb_transmit_frmr below.
 */
व्योम lapb_send_control(काष्ठा lapb_cb *lapb, पूर्णांक frametype,
		       पूर्णांक poll_bit, पूर्णांक type)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर  *dptr;

	अगर ((skb = alloc_skb(LAPB_HEADER_LEN + 3, GFP_ATOMIC)) == शून्य)
		वापस;

	skb_reserve(skb, LAPB_HEADER_LEN + 1);

	अगर (lapb->mode & LAPB_EXTENDED) अणु
		अगर ((frametype & LAPB_U) == LAPB_U) अणु
			dptr   = skb_put(skb, 1);
			*dptr  = frametype;
			*dptr |= poll_bit ? LAPB_SPF : 0;
		पूर्ण अन्यथा अणु
			dptr     = skb_put(skb, 2);
			dptr[0]  = frametype;
			dptr[1]  = (lapb->vr << 1);
			dptr[1] |= poll_bit ? LAPB_EPF : 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		dptr   = skb_put(skb, 1);
		*dptr  = frametype;
		*dptr |= poll_bit ? LAPB_SPF : 0;
		अगर ((frametype & LAPB_U) == LAPB_S)	/* S frames carry NR */
			*dptr |= (lapb->vr << 5);
	पूर्ण

	lapb_transmit_buffer(lapb, skb, type);
पूर्ण

/*
 *	This routine generates FRMRs based on inक्रमmation previously stored in
 *	the LAPB control block.
 */
व्योम lapb_transmit_frmr(काष्ठा lapb_cb *lapb)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर  *dptr;

	अगर ((skb = alloc_skb(LAPB_HEADER_LEN + 7, GFP_ATOMIC)) == शून्य)
		वापस;

	skb_reserve(skb, LAPB_HEADER_LEN + 1);

	अगर (lapb->mode & LAPB_EXTENDED) अणु
		dptr    = skb_put(skb, 6);
		*dptr++ = LAPB_FRMR;
		*dptr++ = lapb->frmr_data.control[0];
		*dptr++ = lapb->frmr_data.control[1];
		*dptr++ = (lapb->vs << 1) & 0xFE;
		*dptr   = (lapb->vr << 1) & 0xFE;
		अगर (lapb->frmr_data.cr == LAPB_RESPONSE)
			*dptr |= 0x01;
		dptr++;
		*dptr++ = lapb->frmr_type;

		lapb_dbg(1, "(%p) S%d TX FRMR %5ph\n",
			 lapb->dev, lapb->state,
			 &skb->data[1]);
	पूर्ण अन्यथा अणु
		dptr    = skb_put(skb, 4);
		*dptr++ = LAPB_FRMR;
		*dptr++ = lapb->frmr_data.control[0];
		*dptr   = (lapb->vs << 1) & 0x0E;
		*dptr  |= (lapb->vr << 5) & 0xE0;
		अगर (lapb->frmr_data.cr == LAPB_RESPONSE)
			*dptr |= 0x10;
		dptr++;
		*dptr++ = lapb->frmr_type;

		lapb_dbg(1, "(%p) S%d TX FRMR %3ph\n",
			 lapb->dev, lapb->state, &skb->data[1]);
	पूर्ण

	lapb_transmit_buffer(lapb, skb, LAPB_RESPONSE);
पूर्ण
