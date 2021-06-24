<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 * Copyright (C) Joerg Reuter DL1BKE (jreuter@yaina.de)
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
 *	State machine क्रम state 1, Aरुकोing Connection State.
 *	The handling of the समयr(s) is in file ax25_ds_समयr.c.
 *	Handling of state 0 and connection release is in ax25.c.
 */
अटल पूर्णांक ax25_ds_state1_machine(ax25_cb *ax25, काष्ठा sk_buff *skb, पूर्णांक frametype, पूर्णांक pf, पूर्णांक type)
अणु
	चयन (frametype) अणु
	हाल AX25_SABM:
		ax25->modulus = AX25_MODULUS;
		ax25->winकरोw  = ax25->ax25_dev->values[AX25_VALUES_WINDOW];
		ax25_send_control(ax25, AX25_UA, pf, AX25_RESPONSE);
		अवरोध;

	हाल AX25_SABME:
		ax25->modulus = AX25_EMODULUS;
		ax25->winकरोw  =  ax25->ax25_dev->values[AX25_VALUES_EWINDOW];
		ax25_send_control(ax25, AX25_UA, pf, AX25_RESPONSE);
		अवरोध;

	हाल AX25_DISC:
		ax25_send_control(ax25, AX25_DM, pf, AX25_RESPONSE);
		अवरोध;

	हाल AX25_UA:
		ax25_calculate_rtt(ax25);
		ax25_stop_t1समयr(ax25);
		ax25_start_t3समयr(ax25);
		ax25_start_idleसमयr(ax25);
		ax25->vs      = 0;
		ax25->va      = 0;
		ax25->vr      = 0;
		ax25->state   = AX25_STATE_3;
		ax25->n2count = 0;
		अगर (ax25->sk != शून्य) अणु
			bh_lock_sock(ax25->sk);
			ax25->sk->sk_state = TCP_ESTABLISHED;
			/*
			 * For WAIT_SABM connections we will produce an accept
			 * पढ़ोy socket here
			 */
			अगर (!sock_flag(ax25->sk, SOCK_DEAD))
				ax25->sk->sk_state_change(ax25->sk);
			bh_unlock_sock(ax25->sk);
		पूर्ण
		ax25_dama_on(ax25);

		/* according to DK4EG's spec we are required to
		 * send a RR RESPONSE FINAL NR=0.
		 */

		ax25_std_enquiry_response(ax25);
		अवरोध;

	हाल AX25_DM:
		अगर (pf)
			ax25_disconnect(ax25, ECONNREFUSED);
		अवरोध;

	शेष:
		अगर (pf)
			ax25_send_control(ax25, AX25_SABM, AX25_POLLON, AX25_COMMAND);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	State machine क्रम state 2, Aरुकोing Release State.
 *	The handling of the समयr(s) is in file ax25_ds_समयr.c
 *	Handling of state 0 and connection release is in ax25.c.
 */
अटल पूर्णांक ax25_ds_state2_machine(ax25_cb *ax25, काष्ठा sk_buff *skb, पूर्णांक frametype, पूर्णांक pf, पूर्णांक type)
अणु
	चयन (frametype) अणु
	हाल AX25_SABM:
	हाल AX25_SABME:
		ax25_send_control(ax25, AX25_DISC, AX25_POLLON, AX25_COMMAND);
		ax25_dama_off(ax25);
		अवरोध;

	हाल AX25_DISC:
		ax25_send_control(ax25, AX25_UA, pf, AX25_RESPONSE);
		ax25_dama_off(ax25);
		ax25_disconnect(ax25, 0);
		अवरोध;

	हाल AX25_DM:
	हाल AX25_UA:
		अगर (pf) अणु
			ax25_dama_off(ax25);
			ax25_disconnect(ax25, 0);
		पूर्ण
		अवरोध;

	हाल AX25_I:
	हाल AX25_REJ:
	हाल AX25_RNR:
	हाल AX25_RR:
		अगर (pf) अणु
			ax25_send_control(ax25, AX25_DISC, AX25_POLLON, AX25_COMMAND);
			ax25_dama_off(ax25);
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	State machine क्रम state 3, Connected State.
 *	The handling of the समयr(s) is in file ax25_समयr.c
 *	Handling of state 0 and connection release is in ax25.c.
 */
अटल पूर्णांक ax25_ds_state3_machine(ax25_cb *ax25, काष्ठा sk_buff *skb, पूर्णांक frametype, पूर्णांक ns, पूर्णांक nr, पूर्णांक pf, पूर्णांक type)
अणु
	पूर्णांक queued = 0;

	चयन (frametype) अणु
	हाल AX25_SABM:
	हाल AX25_SABME:
		अगर (frametype == AX25_SABM) अणु
			ax25->modulus   = AX25_MODULUS;
			ax25->winकरोw    = ax25->ax25_dev->values[AX25_VALUES_WINDOW];
		पूर्ण अन्यथा अणु
			ax25->modulus   = AX25_EMODULUS;
			ax25->winकरोw    = ax25->ax25_dev->values[AX25_VALUES_EWINDOW];
		पूर्ण
		ax25_send_control(ax25, AX25_UA, pf, AX25_RESPONSE);
		ax25_stop_t1समयr(ax25);
		ax25_start_t3समयr(ax25);
		ax25_start_idleसमयr(ax25);
		ax25->condition = 0x00;
		ax25->vs        = 0;
		ax25->va        = 0;
		ax25->vr        = 0;
		ax25_requeue_frames(ax25);
		ax25_dama_on(ax25);
		अवरोध;

	हाल AX25_DISC:
		ax25_send_control(ax25, AX25_UA, pf, AX25_RESPONSE);
		ax25_dama_off(ax25);
		ax25_disconnect(ax25, 0);
		अवरोध;

	हाल AX25_DM:
		ax25_dama_off(ax25);
		ax25_disconnect(ax25, ECONNRESET);
		अवरोध;

	हाल AX25_RR:
	हाल AX25_RNR:
		अगर (frametype == AX25_RR)
			ax25->condition &= ~AX25_COND_PEER_RX_BUSY;
		अन्यथा
			ax25->condition |= AX25_COND_PEER_RX_BUSY;

		अगर (ax25_validate_nr(ax25, nr)) अणु
			अगर (ax25_check_अगरrames_acked(ax25, nr))
				ax25->n2count=0;
			अगर (type == AX25_COMMAND && pf)
				ax25_ds_enquiry_response(ax25);
		पूर्ण अन्यथा अणु
			ax25_ds_nr_error_recovery(ax25);
			ax25->state = AX25_STATE_1;
		पूर्ण
		अवरोध;

	हाल AX25_REJ:
		ax25->condition &= ~AX25_COND_PEER_RX_BUSY;

		अगर (ax25_validate_nr(ax25, nr)) अणु
			अगर (ax25->va != nr)
				ax25->n2count=0;

			ax25_frames_acked(ax25, nr);
			ax25_calculate_rtt(ax25);
			ax25_stop_t1समयr(ax25);
			ax25_start_t3समयr(ax25);
			ax25_requeue_frames(ax25);

			अगर (type == AX25_COMMAND && pf)
				ax25_ds_enquiry_response(ax25);
		पूर्ण अन्यथा अणु
			ax25_ds_nr_error_recovery(ax25);
			ax25->state = AX25_STATE_1;
		पूर्ण
		अवरोध;

	हाल AX25_I:
		अगर (!ax25_validate_nr(ax25, nr)) अणु
			ax25_ds_nr_error_recovery(ax25);
			ax25->state = AX25_STATE_1;
			अवरोध;
		पूर्ण
		अगर (ax25->condition & AX25_COND_PEER_RX_BUSY) अणु
			ax25_frames_acked(ax25, nr);
			ax25->n2count = 0;
		पूर्ण अन्यथा अणु
			अगर (ax25_check_अगरrames_acked(ax25, nr))
				ax25->n2count = 0;
		पूर्ण
		अगर (ax25->condition & AX25_COND_OWN_RX_BUSY) अणु
			अगर (pf) ax25_ds_enquiry_response(ax25);
			अवरोध;
		पूर्ण
		अगर (ns == ax25->vr) अणु
			ax25->vr = (ax25->vr + 1) % ax25->modulus;
			queued = ax25_rx_अगरrame(ax25, skb);
			अगर (ax25->condition & AX25_COND_OWN_RX_BUSY)
				ax25->vr = ns;	/* ax25->vr - 1 */
			ax25->condition &= ~AX25_COND_REJECT;
			अगर (pf) अणु
				ax25_ds_enquiry_response(ax25);
			पूर्ण अन्यथा अणु
				अगर (!(ax25->condition & AX25_COND_ACK_PENDING)) अणु
					ax25->condition |= AX25_COND_ACK_PENDING;
					ax25_start_t2समयr(ax25);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (ax25->condition & AX25_COND_REJECT) अणु
				अगर (pf) ax25_ds_enquiry_response(ax25);
			पूर्ण अन्यथा अणु
				ax25->condition |= AX25_COND_REJECT;
				ax25_ds_enquiry_response(ax25);
				ax25->condition &= ~AX25_COND_ACK_PENDING;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल AX25_FRMR:
	हाल AX25_ILLEGAL:
		ax25_ds_establish_data_link(ax25);
		ax25->state = AX25_STATE_1;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस queued;
पूर्ण

/*
 *	Higher level upcall क्रम a LAPB frame
 */
पूर्णांक ax25_ds_frame_in(ax25_cb *ax25, काष्ठा sk_buff *skb, पूर्णांक type)
अणु
	पूर्णांक queued = 0, frametype, ns, nr, pf;

	frametype = ax25_decode(ax25, skb, &ns, &nr, &pf);

	चयन (ax25->state) अणु
	हाल AX25_STATE_1:
		queued = ax25_ds_state1_machine(ax25, skb, frametype, pf, type);
		अवरोध;
	हाल AX25_STATE_2:
		queued = ax25_ds_state2_machine(ax25, skb, frametype, pf, type);
		अवरोध;
	हाल AX25_STATE_3:
		queued = ax25_ds_state3_machine(ax25, skb, frametype, ns, nr, pf, type);
		अवरोध;
	पूर्ण

	वापस queued;
पूर्ण
