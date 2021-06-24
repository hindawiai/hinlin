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
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/inet.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <net/lapb.h>

अटल व्योम lapb_t1समयr_expiry(काष्ठा समयr_list *);
अटल व्योम lapb_t2समयr_expiry(काष्ठा समयr_list *);

व्योम lapb_start_t1समयr(काष्ठा lapb_cb *lapb)
अणु
	del_समयr(&lapb->t1समयr);

	lapb->t1समयr.function = lapb_t1समयr_expiry;
	lapb->t1समयr.expires  = jअगरfies + lapb->t1;

	lapb->t1समयr_running = true;
	add_समयr(&lapb->t1समयr);
पूर्ण

व्योम lapb_start_t2समयr(काष्ठा lapb_cb *lapb)
अणु
	del_समयr(&lapb->t2समयr);

	lapb->t2समयr.function = lapb_t2समयr_expiry;
	lapb->t2समयr.expires  = jअगरfies + lapb->t2;

	lapb->t2समयr_running = true;
	add_समयr(&lapb->t2समयr);
पूर्ण

व्योम lapb_stop_t1समयr(काष्ठा lapb_cb *lapb)
अणु
	lapb->t1समयr_running = false;
	del_समयr(&lapb->t1समयr);
पूर्ण

व्योम lapb_stop_t2समयr(काष्ठा lapb_cb *lapb)
अणु
	lapb->t2समयr_running = false;
	del_समयr(&lapb->t2समयr);
पूर्ण

पूर्णांक lapb_t1समयr_running(काष्ठा lapb_cb *lapb)
अणु
	वापस lapb->t1समयr_running;
पूर्ण

अटल व्योम lapb_t2समयr_expiry(काष्ठा समयr_list *t)
अणु
	काष्ठा lapb_cb *lapb = from_समयr(lapb, t, t2समयr);

	spin_lock_bh(&lapb->lock);
	अगर (समयr_pending(&lapb->t2समयr)) /* A new समयr has been set up */
		जाओ out;
	अगर (!lapb->t2समयr_running) /* The समयr has been stopped */
		जाओ out;

	अगर (lapb->condition & LAPB_ACK_PENDING_CONDITION) अणु
		lapb->condition &= ~LAPB_ACK_PENDING_CONDITION;
		lapb_समयout_response(lapb);
	पूर्ण
	lapb->t2समयr_running = false;

out:
	spin_unlock_bh(&lapb->lock);
पूर्ण

अटल व्योम lapb_t1समयr_expiry(काष्ठा समयr_list *t)
अणु
	काष्ठा lapb_cb *lapb = from_समयr(lapb, t, t1समयr);

	spin_lock_bh(&lapb->lock);
	अगर (समयr_pending(&lapb->t1समयr)) /* A new समयr has been set up */
		जाओ out;
	अगर (!lapb->t1समयr_running) /* The समयr has been stopped */
		जाओ out;

	चयन (lapb->state) अणु

		/*
		 *	If we are a DCE, send DM up to N2 बार, then चयन to
		 *	STATE_1 and send SABM(E).
		 */
		हाल LAPB_STATE_0:
			अगर (lapb->mode & LAPB_DCE &&
			    lapb->n2count != lapb->n2) अणु
				lapb->n2count++;
				lapb_send_control(lapb, LAPB_DM, LAPB_POLLOFF, LAPB_RESPONSE);
			पूर्ण अन्यथा अणु
				lapb->state = LAPB_STATE_1;
				lapb_establish_data_link(lapb);
			पूर्ण
			अवरोध;

		/*
		 *	Aरुकोing connection state, send SABM(E), up to N2 बार.
		 */
		हाल LAPB_STATE_1:
			अगर (lapb->n2count == lapb->n2) अणु
				lapb_clear_queues(lapb);
				lapb->state = LAPB_STATE_0;
				lapb_disconnect_indication(lapb, LAPB_TIMEDOUT);
				lapb_dbg(0, "(%p) S1 -> S0\n", lapb->dev);
				lapb->t1समयr_running = false;
				जाओ out;
			पूर्ण अन्यथा अणु
				lapb->n2count++;
				अगर (lapb->mode & LAPB_EXTENDED) अणु
					lapb_dbg(1, "(%p) S1 TX SABME(1)\n",
						 lapb->dev);
					lapb_send_control(lapb, LAPB_SABME, LAPB_POLLON, LAPB_COMMAND);
				पूर्ण अन्यथा अणु
					lapb_dbg(1, "(%p) S1 TX SABM(1)\n",
						 lapb->dev);
					lapb_send_control(lapb, LAPB_SABM, LAPB_POLLON, LAPB_COMMAND);
				पूर्ण
			पूर्ण
			अवरोध;

		/*
		 *	Aरुकोing disconnection state, send DISC, up to N2 बार.
		 */
		हाल LAPB_STATE_2:
			अगर (lapb->n2count == lapb->n2) अणु
				lapb_clear_queues(lapb);
				lapb->state = LAPB_STATE_0;
				lapb_disconnect_confirmation(lapb, LAPB_TIMEDOUT);
				lapb_dbg(0, "(%p) S2 -> S0\n", lapb->dev);
				lapb->t1समयr_running = false;
				जाओ out;
			पूर्ण अन्यथा अणु
				lapb->n2count++;
				lapb_dbg(1, "(%p) S2 TX DISC(1)\n", lapb->dev);
				lapb_send_control(lapb, LAPB_DISC, LAPB_POLLON, LAPB_COMMAND);
			पूर्ण
			अवरोध;

		/*
		 *	Data transfer state, restransmit I frames, up to N2 बार.
		 */
		हाल LAPB_STATE_3:
			अगर (lapb->n2count == lapb->n2) अणु
				lapb_clear_queues(lapb);
				lapb->state = LAPB_STATE_0;
				lapb_stop_t2समयr(lapb);
				lapb_disconnect_indication(lapb, LAPB_TIMEDOUT);
				lapb_dbg(0, "(%p) S3 -> S0\n", lapb->dev);
				lapb->t1समयr_running = false;
				जाओ out;
			पूर्ण अन्यथा अणु
				lapb->n2count++;
				lapb_requeue_frames(lapb);
				lapb_kick(lapb);
			पूर्ण
			अवरोध;

		/*
		 *	Frame reject state, restransmit FRMR frames, up to N2 बार.
		 */
		हाल LAPB_STATE_4:
			अगर (lapb->n2count == lapb->n2) अणु
				lapb_clear_queues(lapb);
				lapb->state = LAPB_STATE_0;
				lapb_disconnect_indication(lapb, LAPB_TIMEDOUT);
				lapb_dbg(0, "(%p) S4 -> S0\n", lapb->dev);
				lapb->t1समयr_running = false;
				जाओ out;
			पूर्ण अन्यथा अणु
				lapb->n2count++;
				lapb_transmit_frmr(lapb);
			पूर्ण
			अवरोध;
	पूर्ण

	lapb_start_t1समयr(lapb);

out:
	spin_unlock_bh(&lapb->lock);
पूर्ण
