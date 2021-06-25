<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	LAPB release 002
 *
 *	This code REQUIRES 2.1.15 or higher/ NET3.038
 *
 *	History
 *	LAPB 001	Jonathan Naulor	Started Coding
 *	LAPB 002	Jonathan Naylor	New समयr architecture.
 *	2000-10-29	Henner Eisen	lapb_data_indication() वापस status.
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
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <net/lapb.h>

/*
 *	State machine क्रम state 0, Disconnected State.
 *	The handling of the समयr(s) is in file lapb_समयr.c.
 */
अटल व्योम lapb_state0_machine(काष्ठा lapb_cb *lapb, काष्ठा sk_buff *skb,
				काष्ठा lapb_frame *frame)
अणु
	चयन (frame->type) अणु
	हाल LAPB_SABM:
		lapb_dbg(1, "(%p) S0 RX SABM(%d)\n", lapb->dev, frame->pf);
		अगर (lapb->mode & LAPB_EXTENDED) अणु
			lapb_dbg(1, "(%p) S0 TX DM(%d)\n",
				 lapb->dev, frame->pf);
			lapb_send_control(lapb, LAPB_DM, frame->pf,
					  LAPB_RESPONSE);
		पूर्ण अन्यथा अणु
			lapb_dbg(1, "(%p) S0 TX UA(%d)\n",
				 lapb->dev, frame->pf);
			lapb_dbg(0, "(%p) S0 -> S3\n", lapb->dev);
			lapb_send_control(lapb, LAPB_UA, frame->pf,
					  LAPB_RESPONSE);
			lapb_stop_t1समयr(lapb);
			lapb_stop_t2समयr(lapb);
			lapb->state     = LAPB_STATE_3;
			lapb->condition = 0x00;
			lapb->n2count   = 0;
			lapb->vs        = 0;
			lapb->vr        = 0;
			lapb->va        = 0;
			lapb_connect_indication(lapb, LAPB_OK);
		पूर्ण
		अवरोध;

	हाल LAPB_SABME:
		lapb_dbg(1, "(%p) S0 RX SABME(%d)\n", lapb->dev, frame->pf);
		अगर (lapb->mode & LAPB_EXTENDED) अणु
			lapb_dbg(1, "(%p) S0 TX UA(%d)\n",
				 lapb->dev, frame->pf);
			lapb_dbg(0, "(%p) S0 -> S3\n", lapb->dev);
			lapb_send_control(lapb, LAPB_UA, frame->pf,
					  LAPB_RESPONSE);
			lapb_stop_t1समयr(lapb);
			lapb_stop_t2समयr(lapb);
			lapb->state     = LAPB_STATE_3;
			lapb->condition = 0x00;
			lapb->n2count   = 0;
			lapb->vs        = 0;
			lapb->vr        = 0;
			lapb->va        = 0;
			lapb_connect_indication(lapb, LAPB_OK);
		पूर्ण अन्यथा अणु
			lapb_dbg(1, "(%p) S0 TX DM(%d)\n",
				 lapb->dev, frame->pf);
			lapb_send_control(lapb, LAPB_DM, frame->pf,
					  LAPB_RESPONSE);
		पूर्ण
		अवरोध;

	हाल LAPB_DISC:
		lapb_dbg(1, "(%p) S0 RX DISC(%d)\n", lapb->dev, frame->pf);
		lapb_dbg(1, "(%p) S0 TX UA(%d)\n", lapb->dev, frame->pf);
		lapb_send_control(lapb, LAPB_UA, frame->pf, LAPB_RESPONSE);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	kमुक्त_skb(skb);
पूर्ण

/*
 *	State machine क्रम state 1, Aरुकोing Connection State.
 *	The handling of the समयr(s) is in file lapb_समयr.c.
 */
अटल व्योम lapb_state1_machine(काष्ठा lapb_cb *lapb, काष्ठा sk_buff *skb,
				काष्ठा lapb_frame *frame)
अणु
	चयन (frame->type) अणु
	हाल LAPB_SABM:
		lapb_dbg(1, "(%p) S1 RX SABM(%d)\n", lapb->dev, frame->pf);
		अगर (lapb->mode & LAPB_EXTENDED) अणु
			lapb_dbg(1, "(%p) S1 TX DM(%d)\n",
				 lapb->dev, frame->pf);
			lapb_send_control(lapb, LAPB_DM, frame->pf,
					  LAPB_RESPONSE);
		पूर्ण अन्यथा अणु
			lapb_dbg(1, "(%p) S1 TX UA(%d)\n",
				 lapb->dev, frame->pf);
			lapb_send_control(lapb, LAPB_UA, frame->pf,
					  LAPB_RESPONSE);
		पूर्ण
		अवरोध;

	हाल LAPB_SABME:
		lapb_dbg(1, "(%p) S1 RX SABME(%d)\n", lapb->dev, frame->pf);
		अगर (lapb->mode & LAPB_EXTENDED) अणु
			lapb_dbg(1, "(%p) S1 TX UA(%d)\n",
				 lapb->dev, frame->pf);
			lapb_send_control(lapb, LAPB_UA, frame->pf,
					  LAPB_RESPONSE);
		पूर्ण अन्यथा अणु
			lapb_dbg(1, "(%p) S1 TX DM(%d)\n",
				 lapb->dev, frame->pf);
			lapb_send_control(lapb, LAPB_DM, frame->pf,
					  LAPB_RESPONSE);
		पूर्ण
		अवरोध;

	हाल LAPB_DISC:
		lapb_dbg(1, "(%p) S1 RX DISC(%d)\n", lapb->dev, frame->pf);
		lapb_dbg(1, "(%p) S1 TX DM(%d)\n", lapb->dev, frame->pf);
		lapb_send_control(lapb, LAPB_DM, frame->pf, LAPB_RESPONSE);
		अवरोध;

	हाल LAPB_UA:
		lapb_dbg(1, "(%p) S1 RX UA(%d)\n", lapb->dev, frame->pf);
		अगर (frame->pf) अणु
			lapb_dbg(0, "(%p) S1 -> S3\n", lapb->dev);
			lapb_stop_t1समयr(lapb);
			lapb_stop_t2समयr(lapb);
			lapb->state     = LAPB_STATE_3;
			lapb->condition = 0x00;
			lapb->n2count   = 0;
			lapb->vs        = 0;
			lapb->vr        = 0;
			lapb->va        = 0;
			lapb_connect_confirmation(lapb, LAPB_OK);
		पूर्ण
		अवरोध;

	हाल LAPB_DM:
		lapb_dbg(1, "(%p) S1 RX DM(%d)\n", lapb->dev, frame->pf);
		अगर (frame->pf) अणु
			lapb_dbg(0, "(%p) S1 -> S0\n", lapb->dev);
			lapb_clear_queues(lapb);
			lapb->state = LAPB_STATE_0;
			lapb_start_t1समयr(lapb);
			lapb_stop_t2समयr(lapb);
			lapb_disconnect_indication(lapb, LAPB_REFUSED);
		पूर्ण
		अवरोध;
	पूर्ण

	kमुक्त_skb(skb);
पूर्ण

/*
 *	State machine क्रम state 2, Aरुकोing Release State.
 *	The handling of the समयr(s) is in file lapb_समयr.c
 */
अटल व्योम lapb_state2_machine(काष्ठा lapb_cb *lapb, काष्ठा sk_buff *skb,
				काष्ठा lapb_frame *frame)
अणु
	चयन (frame->type) अणु
	हाल LAPB_SABM:
	हाल LAPB_SABME:
		lapb_dbg(1, "(%p) S2 RX {SABM,SABME}(%d)\n",
			 lapb->dev, frame->pf);
		lapb_dbg(1, "(%p) S2 TX DM(%d)\n", lapb->dev, frame->pf);
		lapb_send_control(lapb, LAPB_DM, frame->pf, LAPB_RESPONSE);
		अवरोध;

	हाल LAPB_DISC:
		lapb_dbg(1, "(%p) S2 RX DISC(%d)\n", lapb->dev, frame->pf);
		lapb_dbg(1, "(%p) S2 TX UA(%d)\n", lapb->dev, frame->pf);
		lapb_send_control(lapb, LAPB_UA, frame->pf, LAPB_RESPONSE);
		अवरोध;

	हाल LAPB_UA:
		lapb_dbg(1, "(%p) S2 RX UA(%d)\n", lapb->dev, frame->pf);
		अगर (frame->pf) अणु
			lapb_dbg(0, "(%p) S2 -> S0\n", lapb->dev);
			lapb->state = LAPB_STATE_0;
			lapb_start_t1समयr(lapb);
			lapb_stop_t2समयr(lapb);
			lapb_disconnect_confirmation(lapb, LAPB_OK);
		पूर्ण
		अवरोध;

	हाल LAPB_DM:
		lapb_dbg(1, "(%p) S2 RX DM(%d)\n", lapb->dev, frame->pf);
		अगर (frame->pf) अणु
			lapb_dbg(0, "(%p) S2 -> S0\n", lapb->dev);
			lapb->state = LAPB_STATE_0;
			lapb_start_t1समयr(lapb);
			lapb_stop_t2समयr(lapb);
			lapb_disconnect_confirmation(lapb, LAPB_NOTCONNECTED);
		पूर्ण
		अवरोध;

	हाल LAPB_I:
	हाल LAPB_REJ:
	हाल LAPB_RNR:
	हाल LAPB_RR:
		lapb_dbg(1, "(%p) S2 RX {I,REJ,RNR,RR}(%d)\n",
		       lapb->dev, frame->pf);
		lapb_dbg(1, "(%p) S2 RX DM(%d)\n", lapb->dev, frame->pf);
		अगर (frame->pf)
			lapb_send_control(lapb, LAPB_DM, frame->pf,
					  LAPB_RESPONSE);
		अवरोध;
	पूर्ण

	kमुक्त_skb(skb);
पूर्ण

/*
 *	State machine क्रम state 3, Connected State.
 *	The handling of the समयr(s) is in file lapb_समयr.c
 */
अटल व्योम lapb_state3_machine(काष्ठा lapb_cb *lapb, काष्ठा sk_buff *skb,
				काष्ठा lapb_frame *frame)
अणु
	पूर्णांक queued = 0;
	पूर्णांक modulus = (lapb->mode & LAPB_EXTENDED) ? LAPB_EMODULUS :
						     LAPB_SMODULUS;

	चयन (frame->type) अणु
	हाल LAPB_SABM:
		lapb_dbg(1, "(%p) S3 RX SABM(%d)\n", lapb->dev, frame->pf);
		अगर (lapb->mode & LAPB_EXTENDED) अणु
			lapb_dbg(1, "(%p) S3 TX DM(%d)\n",
				 lapb->dev, frame->pf);
			lapb_send_control(lapb, LAPB_DM, frame->pf,
					  LAPB_RESPONSE);
		पूर्ण अन्यथा अणु
			lapb_dbg(1, "(%p) S3 TX UA(%d)\n",
				 lapb->dev, frame->pf);
			lapb_send_control(lapb, LAPB_UA, frame->pf,
					  LAPB_RESPONSE);
			lapb_stop_t1समयr(lapb);
			lapb_stop_t2समयr(lapb);
			lapb->condition = 0x00;
			lapb->n2count   = 0;
			lapb->vs        = 0;
			lapb->vr        = 0;
			lapb->va        = 0;
			lapb_requeue_frames(lapb);
		पूर्ण
		अवरोध;

	हाल LAPB_SABME:
		lapb_dbg(1, "(%p) S3 RX SABME(%d)\n", lapb->dev, frame->pf);
		अगर (lapb->mode & LAPB_EXTENDED) अणु
			lapb_dbg(1, "(%p) S3 TX UA(%d)\n",
				 lapb->dev, frame->pf);
			lapb_send_control(lapb, LAPB_UA, frame->pf,
					  LAPB_RESPONSE);
			lapb_stop_t1समयr(lapb);
			lapb_stop_t2समयr(lapb);
			lapb->condition = 0x00;
			lapb->n2count   = 0;
			lapb->vs        = 0;
			lapb->vr        = 0;
			lapb->va        = 0;
			lapb_requeue_frames(lapb);
		पूर्ण अन्यथा अणु
			lapb_dbg(1, "(%p) S3 TX DM(%d)\n",
				 lapb->dev, frame->pf);
			lapb_send_control(lapb, LAPB_DM, frame->pf,
					  LAPB_RESPONSE);
		पूर्ण
		अवरोध;

	हाल LAPB_DISC:
		lapb_dbg(1, "(%p) S3 RX DISC(%d)\n", lapb->dev, frame->pf);
		lapb_dbg(0, "(%p) S3 -> S0\n", lapb->dev);
		lapb_clear_queues(lapb);
		lapb_send_control(lapb, LAPB_UA, frame->pf, LAPB_RESPONSE);
		lapb_start_t1समयr(lapb);
		lapb_stop_t2समयr(lapb);
		lapb->state = LAPB_STATE_0;
		lapb_disconnect_indication(lapb, LAPB_OK);
		अवरोध;

	हाल LAPB_DM:
		lapb_dbg(1, "(%p) S3 RX DM(%d)\n", lapb->dev, frame->pf);
		lapb_dbg(0, "(%p) S3 -> S0\n", lapb->dev);
		lapb_clear_queues(lapb);
		lapb->state = LAPB_STATE_0;
		lapb_start_t1समयr(lapb);
		lapb_stop_t2समयr(lapb);
		lapb_disconnect_indication(lapb, LAPB_NOTCONNECTED);
		अवरोध;

	हाल LAPB_RNR:
		lapb_dbg(1, "(%p) S3 RX RNR(%d) R%d\n",
			 lapb->dev, frame->pf, frame->nr);
		lapb->condition |= LAPB_PEER_RX_BUSY_CONDITION;
		lapb_check_need_response(lapb, frame->cr, frame->pf);
		अगर (lapb_validate_nr(lapb, frame->nr)) अणु
			lapb_check_अगरrames_acked(lapb, frame->nr);
		पूर्ण अन्यथा अणु
			lapb->frmr_data = *frame;
			lapb->frmr_type = LAPB_FRMR_Z;
			lapb_transmit_frmr(lapb);
			lapb_dbg(0, "(%p) S3 -> S4\n", lapb->dev);
			lapb_start_t1समयr(lapb);
			lapb_stop_t2समयr(lapb);
			lapb->state   = LAPB_STATE_4;
			lapb->n2count = 0;
		पूर्ण
		अवरोध;

	हाल LAPB_RR:
		lapb_dbg(1, "(%p) S3 RX RR(%d) R%d\n",
			 lapb->dev, frame->pf, frame->nr);
		lapb->condition &= ~LAPB_PEER_RX_BUSY_CONDITION;
		lapb_check_need_response(lapb, frame->cr, frame->pf);
		अगर (lapb_validate_nr(lapb, frame->nr)) अणु
			lapb_check_अगरrames_acked(lapb, frame->nr);
		पूर्ण अन्यथा अणु
			lapb->frmr_data = *frame;
			lapb->frmr_type = LAPB_FRMR_Z;
			lapb_transmit_frmr(lapb);
			lapb_dbg(0, "(%p) S3 -> S4\n", lapb->dev);
			lapb_start_t1समयr(lapb);
			lapb_stop_t2समयr(lapb);
			lapb->state   = LAPB_STATE_4;
			lapb->n2count = 0;
		पूर्ण
		अवरोध;

	हाल LAPB_REJ:
		lapb_dbg(1, "(%p) S3 RX REJ(%d) R%d\n",
			 lapb->dev, frame->pf, frame->nr);
		lapb->condition &= ~LAPB_PEER_RX_BUSY_CONDITION;
		lapb_check_need_response(lapb, frame->cr, frame->pf);
		अगर (lapb_validate_nr(lapb, frame->nr)) अणु
			lapb_frames_acked(lapb, frame->nr);
			lapb_stop_t1समयr(lapb);
			lapb->n2count = 0;
			lapb_requeue_frames(lapb);
		पूर्ण अन्यथा अणु
			lapb->frmr_data = *frame;
			lapb->frmr_type = LAPB_FRMR_Z;
			lapb_transmit_frmr(lapb);
			lapb_dbg(0, "(%p) S3 -> S4\n", lapb->dev);
			lapb_start_t1समयr(lapb);
			lapb_stop_t2समयr(lapb);
			lapb->state   = LAPB_STATE_4;
			lapb->n2count = 0;
		पूर्ण
		अवरोध;

	हाल LAPB_I:
		lapb_dbg(1, "(%p) S3 RX I(%d) S%d R%d\n",
			 lapb->dev, frame->pf, frame->ns, frame->nr);
		अगर (!lapb_validate_nr(lapb, frame->nr)) अणु
			lapb->frmr_data = *frame;
			lapb->frmr_type = LAPB_FRMR_Z;
			lapb_transmit_frmr(lapb);
			lapb_dbg(0, "(%p) S3 -> S4\n", lapb->dev);
			lapb_start_t1समयr(lapb);
			lapb_stop_t2समयr(lapb);
			lapb->state   = LAPB_STATE_4;
			lapb->n2count = 0;
			अवरोध;
		पूर्ण
		अगर (lapb->condition & LAPB_PEER_RX_BUSY_CONDITION)
			lapb_frames_acked(lapb, frame->nr);
		अन्यथा
			lapb_check_अगरrames_acked(lapb, frame->nr);

		अगर (frame->ns == lapb->vr) अणु
			पूर्णांक cn;
			cn = lapb_data_indication(lapb, skb);
			queued = 1;
			/*
			 * If upper layer has dropped the frame, we
			 * basically ignore any further protocol
			 * processing. This will cause the peer
			 * to re-transmit the frame later like
			 * a frame lost on the wire.
			 */
			अगर (cn == NET_RX_DROP) अणु
				pr_debug("rx congestion\n");
				अवरोध;
			पूर्ण
			lapb->vr = (lapb->vr + 1) % modulus;
			lapb->condition &= ~LAPB_REJECT_CONDITION;
			अगर (frame->pf)
				lapb_enquiry_response(lapb);
			अन्यथा अणु
				अगर (!(lapb->condition &
				      LAPB_ACK_PENDING_CONDITION)) अणु
					lapb->condition |= LAPB_ACK_PENDING_CONDITION;
					lapb_start_t2समयr(lapb);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (lapb->condition & LAPB_REJECT_CONDITION) अणु
				अगर (frame->pf)
					lapb_enquiry_response(lapb);
			पूर्ण अन्यथा अणु
				lapb_dbg(1, "(%p) S3 TX REJ(%d) R%d\n",
					 lapb->dev, frame->pf, lapb->vr);
				lapb->condition |= LAPB_REJECT_CONDITION;
				lapb_send_control(lapb, LAPB_REJ, frame->pf,
						  LAPB_RESPONSE);
				lapb->condition &= ~LAPB_ACK_PENDING_CONDITION;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल LAPB_FRMR:
		lapb_dbg(1, "(%p) S3 RX FRMR(%d) %5ph\n",
			 lapb->dev, frame->pf,
			 skb->data);
		lapb_establish_data_link(lapb);
		lapb_dbg(0, "(%p) S3 -> S1\n", lapb->dev);
		lapb_requeue_frames(lapb);
		lapb->state = LAPB_STATE_1;
		अवरोध;

	हाल LAPB_ILLEGAL:
		lapb_dbg(1, "(%p) S3 RX ILLEGAL(%d)\n", lapb->dev, frame->pf);
		lapb->frmr_data = *frame;
		lapb->frmr_type = LAPB_FRMR_W;
		lapb_transmit_frmr(lapb);
		lapb_dbg(0, "(%p) S3 -> S4\n", lapb->dev);
		lapb_start_t1समयr(lapb);
		lapb_stop_t2समयr(lapb);
		lapb->state   = LAPB_STATE_4;
		lapb->n2count = 0;
		अवरोध;
	पूर्ण

	अगर (!queued)
		kमुक्त_skb(skb);
पूर्ण

/*
 *	State machine क्रम state 4, Frame Reject State.
 *	The handling of the समयr(s) is in file lapb_समयr.c.
 */
अटल व्योम lapb_state4_machine(काष्ठा lapb_cb *lapb, काष्ठा sk_buff *skb,
				काष्ठा lapb_frame *frame)
अणु
	चयन (frame->type) अणु
	हाल LAPB_SABM:
		lapb_dbg(1, "(%p) S4 RX SABM(%d)\n", lapb->dev, frame->pf);
		अगर (lapb->mode & LAPB_EXTENDED) अणु
			lapb_dbg(1, "(%p) S4 TX DM(%d)\n",
				 lapb->dev, frame->pf);
			lapb_send_control(lapb, LAPB_DM, frame->pf,
					  LAPB_RESPONSE);
		पूर्ण अन्यथा अणु
			lapb_dbg(1, "(%p) S4 TX UA(%d)\n",
				 lapb->dev, frame->pf);
			lapb_dbg(0, "(%p) S4 -> S3\n", lapb->dev);
			lapb_send_control(lapb, LAPB_UA, frame->pf,
					  LAPB_RESPONSE);
			lapb_stop_t1समयr(lapb);
			lapb_stop_t2समयr(lapb);
			lapb->state     = LAPB_STATE_3;
			lapb->condition = 0x00;
			lapb->n2count   = 0;
			lapb->vs        = 0;
			lapb->vr        = 0;
			lapb->va        = 0;
			lapb_connect_indication(lapb, LAPB_OK);
		पूर्ण
		अवरोध;

	हाल LAPB_SABME:
		lapb_dbg(1, "(%p) S4 RX SABME(%d)\n", lapb->dev, frame->pf);
		अगर (lapb->mode & LAPB_EXTENDED) अणु
			lapb_dbg(1, "(%p) S4 TX UA(%d)\n",
				 lapb->dev, frame->pf);
			lapb_dbg(0, "(%p) S4 -> S3\n", lapb->dev);
			lapb_send_control(lapb, LAPB_UA, frame->pf,
					  LAPB_RESPONSE);
			lapb_stop_t1समयr(lapb);
			lapb_stop_t2समयr(lapb);
			lapb->state     = LAPB_STATE_3;
			lapb->condition = 0x00;
			lapb->n2count   = 0;
			lapb->vs        = 0;
			lapb->vr        = 0;
			lapb->va        = 0;
			lapb_connect_indication(lapb, LAPB_OK);
		पूर्ण अन्यथा अणु
			lapb_dbg(1, "(%p) S4 TX DM(%d)\n",
				 lapb->dev, frame->pf);
			lapb_send_control(lapb, LAPB_DM, frame->pf,
					  LAPB_RESPONSE);
		पूर्ण
		अवरोध;
	पूर्ण

	kमुक्त_skb(skb);
पूर्ण

/*
 *	Process an incoming LAPB frame
 */
व्योम lapb_data_input(काष्ठा lapb_cb *lapb, काष्ठा sk_buff *skb)
अणु
	काष्ठा lapb_frame frame;

	अगर (lapb_decode(lapb, skb, &frame) < 0) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	चयन (lapb->state) अणु
	हाल LAPB_STATE_0:
		lapb_state0_machine(lapb, skb, &frame); अवरोध;
	हाल LAPB_STATE_1:
		lapb_state1_machine(lapb, skb, &frame); अवरोध;
	हाल LAPB_STATE_2:
		lapb_state2_machine(lapb, skb, &frame); अवरोध;
	हाल LAPB_STATE_3:
		lapb_state3_machine(lapb, skb, &frame); अवरोध;
	हाल LAPB_STATE_4:
		lapb_state4_machine(lapb, skb, &frame); अवरोध;
	पूर्ण

	lapb_kick(lapb);
पूर्ण
