<शैली गुरु>
/*
 * llc_conn.c - Driver routines क्रम connection component.
 *
 * Copyright (c) 1997 by Procom Technology, Inc.
 *		 2001-2003 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <net/llc_sap.h>
#समावेश <net/llc_conn.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <net/llc_c_ev.h>
#समावेश <net/llc_c_ac.h>
#समावेश <net/llc_c_st.h>
#समावेश <net/llc_pdu.h>

#अगर 0
#घोषणा dprपूर्णांकk(args...) prपूर्णांकk(KERN_DEBUG args)
#अन्यथा
#घोषणा dprपूर्णांकk(args...)
#पूर्ण_अगर

अटल पूर्णांक llc_find_offset(पूर्णांक state, पूर्णांक ev_type);
अटल व्योम llc_conn_send_pdus(काष्ठा sock *sk);
अटल पूर्णांक llc_conn_service(काष्ठा sock *sk, काष्ठा sk_buff *skb);
अटल पूर्णांक llc_exec_conn_trans_actions(काष्ठा sock *sk,
				       काष्ठा llc_conn_state_trans *trans,
				       काष्ठा sk_buff *ev);
अटल काष्ठा llc_conn_state_trans *llc_qualअगरy_conn_ev(काष्ठा sock *sk,
							काष्ठा sk_buff *skb);

/* Offset table on connection states transition diagram */
अटल पूर्णांक llc_offset_table[NBR_CONN_STATES][NBR_CONN_EV];

पूर्णांक sysctl_llc2_ack_समयout = LLC2_ACK_TIME * HZ;
पूर्णांक sysctl_llc2_p_समयout = LLC2_P_TIME * HZ;
पूर्णांक sysctl_llc2_rej_समयout = LLC2_REJ_TIME * HZ;
पूर्णांक sysctl_llc2_busy_समयout = LLC2_BUSY_TIME * HZ;

/**
 *	llc_conn_state_process - sends event to connection state machine
 *	@sk: connection
 *	@skb: occurred event
 *
 *	Sends an event to connection state machine. After processing event
 *	(executing it's actions and changing state), upper layer will be
 *	indicated or confirmed, अगर needed. Returns 0 क्रम success, 1 क्रम
 *	failure. The socket lock has to be held beक्रमe calling this function.
 *
 *	This function always consumes a reference to the skb.
 */
पूर्णांक llc_conn_state_process(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc;
	काष्ठा llc_sock *llc = llc_sk(skb->sk);
	काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	ev->ind_prim = ev->cfm_prim = 0;
	/*
	 * Send event to state machine
	 */
	rc = llc_conn_service(skb->sk, skb);
	अगर (unlikely(rc != 0)) अणु
		prपूर्णांकk(KERN_ERR "%s: llc_conn_service failed\n", __func__);
		जाओ out_skb_put;
	पूर्ण

	चयन (ev->ind_prim) अणु
	हाल LLC_DATA_PRIM:
		skb_get(skb);
		llc_save_primitive(sk, skb, LLC_DATA_PRIM);
		अगर (unlikely(sock_queue_rcv_skb(sk, skb))) अणु
			/*
			 * shouldn't happen
			 */
			prपूर्णांकk(KERN_ERR "%s: sock_queue_rcv_skb failed!\n",
			       __func__);
			kमुक्त_skb(skb);
		पूर्ण
		अवरोध;
	हाल LLC_CONN_PRIM:
		/*
		 * Can't be sock_queue_rcv_skb, because we have to leave the
		 * skb->sk poपूर्णांकing to the newly created काष्ठा sock in
		 * llc_conn_handler. -acme
		 */
		skb_get(skb);
		skb_queue_tail(&sk->sk_receive_queue, skb);
		sk->sk_state_change(sk);
		अवरोध;
	हाल LLC_DISC_PRIM:
		sock_hold(sk);
		अगर (sk->sk_type == SOCK_STREAM &&
		    sk->sk_state == TCP_ESTABLISHED) अणु
			sk->sk_shutकरोwn       = SHUTDOWN_MASK;
			sk->sk_socket->state  = SS_UNCONNECTED;
			sk->sk_state          = TCP_CLOSE;
			अगर (!sock_flag(sk, SOCK_DEAD)) अणु
				sock_set_flag(sk, SOCK_DEAD);
				sk->sk_state_change(sk);
			पूर्ण
		पूर्ण
		sock_put(sk);
		अवरोध;
	हाल LLC_RESET_PRIM:
		/*
		 * FIXME:
		 * RESET is not being notअगरied to upper layers क्रम now
		 */
		prपूर्णांकk(KERN_INFO "%s: received a reset ind!\n", __func__);
		अवरोध;
	शेष:
		अगर (ev->ind_prim)
			prपूर्णांकk(KERN_INFO "%s: received unknown %d prim!\n",
				__func__, ev->ind_prim);
		/* No indication */
		अवरोध;
	पूर्ण

	चयन (ev->cfm_prim) अणु
	हाल LLC_DATA_PRIM:
		अगर (!llc_data_accept_state(llc->state))
			sk->sk_ग_लिखो_space(sk);
		अन्यथा
			rc = llc->failed_data_req = 1;
		अवरोध;
	हाल LLC_CONN_PRIM:
		अगर (sk->sk_type == SOCK_STREAM &&
		    sk->sk_state == TCP_SYN_SENT) अणु
			अगर (ev->status) अणु
				sk->sk_socket->state = SS_UNCONNECTED;
				sk->sk_state         = TCP_CLOSE;
			पूर्ण अन्यथा अणु
				sk->sk_socket->state = SS_CONNECTED;
				sk->sk_state         = TCP_ESTABLISHED;
			पूर्ण
			sk->sk_state_change(sk);
		पूर्ण
		अवरोध;
	हाल LLC_DISC_PRIM:
		sock_hold(sk);
		अगर (sk->sk_type == SOCK_STREAM && sk->sk_state == TCP_CLOSING) अणु
			sk->sk_socket->state = SS_UNCONNECTED;
			sk->sk_state         = TCP_CLOSE;
			sk->sk_state_change(sk);
		पूर्ण
		sock_put(sk);
		अवरोध;
	हाल LLC_RESET_PRIM:
		/*
		 * FIXME:
		 * RESET is not being notअगरied to upper layers क्रम now
		 */
		prपूर्णांकk(KERN_INFO "%s: received a reset conf!\n", __func__);
		अवरोध;
	शेष:
		अगर (ev->cfm_prim)
			prपूर्णांकk(KERN_INFO "%s: received unknown %d prim!\n",
					__func__, ev->cfm_prim);
		/* No confirmation */
		अवरोध;
	पूर्ण
out_skb_put:
	kमुक्त_skb(skb);
	वापस rc;
पूर्ण

व्योम llc_conn_send_pdu(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	/* queue PDU to send to MAC layer */
	skb_queue_tail(&sk->sk_ग_लिखो_queue, skb);
	llc_conn_send_pdus(sk);
पूर्ण

/**
 *	llc_conn_rtn_pdu - sends received data pdu to upper layer
 *	@sk: Active connection
 *	@skb: Received data frame
 *
 *	Sends received data pdu to upper layer (by using indicate function).
 *	Prepares service parameters (prim and prim_data). calling indication
 *	function will be करोne in llc_conn_state_process.
 */
व्योम llc_conn_rtn_pdu(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	ev->ind_prim = LLC_DATA_PRIM;
पूर्ण

/**
 *	llc_conn_resend_i_pdu_as_cmd - resend all all unacknowledged I PDUs
 *	@sk: active connection
 *	@nr: NR
 *	@first_p_bit: p_bit value of first pdu
 *
 *	Resend all unacknowledged I PDUs, starting with the NR; send first as
 *	command PDU with P bit equal first_p_bit; अगर more than one send
 *	subsequent as command PDUs with P bit equal zero (0).
 */
व्योम llc_conn_resend_i_pdu_as_cmd(काष्ठा sock *sk, u8 nr, u8 first_p_bit)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा llc_pdu_sn *pdu;
	u16 nbr_unack_pdus;
	काष्ठा llc_sock *llc;
	u8 howmany_resend = 0;

	llc_conn_हटाओ_acked_pdus(sk, nr, &nbr_unack_pdus);
	अगर (!nbr_unack_pdus)
		जाओ out;
	/*
	 * Process unack PDUs only अगर unack queue is not empty; हटाओ
	 * appropriate PDUs, fix them up, and put them on mac_pdu_q.
	 */
	llc = llc_sk(sk);

	जबतक ((skb = skb_dequeue(&llc->pdu_unack_q)) != शून्य) अणु
		pdu = llc_pdu_sn_hdr(skb);
		llc_pdu_set_cmd_rsp(skb, LLC_PDU_CMD);
		llc_pdu_set_pf_bit(skb, first_p_bit);
		skb_queue_tail(&sk->sk_ग_लिखो_queue, skb);
		first_p_bit = 0;
		llc->vS = LLC_I_GET_NS(pdu);
		howmany_resend++;
	पूर्ण
	अगर (howmany_resend > 0)
		llc->vS = (llc->vS + 1) % LLC_2_SEQ_NBR_MODULO;
	/* any PDUs to re-send are queued up; start sending to MAC */
	llc_conn_send_pdus(sk);
out:;
पूर्ण

/**
 *	llc_conn_resend_i_pdu_as_rsp - Resend all unacknowledged I PDUs
 *	@sk: active connection.
 *	@nr: NR
 *	@first_f_bit: f_bit value of first pdu.
 *
 *	Resend all unacknowledged I PDUs, starting with the NR; send first as
 *	response PDU with F bit equal first_f_bit; अगर more than one send
 *	subsequent as response PDUs with F bit equal zero (0).
 */
व्योम llc_conn_resend_i_pdu_as_rsp(काष्ठा sock *sk, u8 nr, u8 first_f_bit)
अणु
	काष्ठा sk_buff *skb;
	u16 nbr_unack_pdus;
	काष्ठा llc_sock *llc = llc_sk(sk);
	u8 howmany_resend = 0;

	llc_conn_हटाओ_acked_pdus(sk, nr, &nbr_unack_pdus);
	अगर (!nbr_unack_pdus)
		जाओ out;
	/*
	 * Process unack PDUs only अगर unack queue is not empty; हटाओ
	 * appropriate PDUs, fix them up, and put them on mac_pdu_q
	 */
	जबतक ((skb = skb_dequeue(&llc->pdu_unack_q)) != शून्य) अणु
		काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

		llc_pdu_set_cmd_rsp(skb, LLC_PDU_RSP);
		llc_pdu_set_pf_bit(skb, first_f_bit);
		skb_queue_tail(&sk->sk_ग_लिखो_queue, skb);
		first_f_bit = 0;
		llc->vS = LLC_I_GET_NS(pdu);
		howmany_resend++;
	पूर्ण
	अगर (howmany_resend > 0)
		llc->vS = (llc->vS + 1) % LLC_2_SEQ_NBR_MODULO;
	/* any PDUs to re-send are queued up; start sending to MAC */
	llc_conn_send_pdus(sk);
out:;
पूर्ण

/**
 *	llc_conn_हटाओ_acked_pdus - Removes acknowledged pdus from tx queue
 *	@sk: active connection
 *	@nr: NR
 *	@how_many_unacked: size of pdu_unack_q after removing acked pdus
 *
 *	Removes acknowledged pdus from transmit queue (pdu_unack_q). Returns
 *	the number of pdus that हटाओd from queue.
 */
पूर्णांक llc_conn_हटाओ_acked_pdus(काष्ठा sock *sk, u8 nr, u16 *how_many_unacked)
अणु
	पूर्णांक pdu_pos, i;
	काष्ठा sk_buff *skb;
	काष्ठा llc_pdu_sn *pdu;
	पूर्णांक nbr_acked = 0;
	काष्ठा llc_sock *llc = llc_sk(sk);
	पूर्णांक q_len = skb_queue_len(&llc->pdu_unack_q);

	अगर (!q_len)
		जाओ out;
	skb = skb_peek(&llc->pdu_unack_q);
	pdu = llc_pdu_sn_hdr(skb);

	/* finding position of last acked pdu in queue */
	pdu_pos = ((पूर्णांक)LLC_2_SEQ_NBR_MODULO + (पूर्णांक)nr -
			(पूर्णांक)LLC_I_GET_NS(pdu)) % LLC_2_SEQ_NBR_MODULO;

	क्रम (i = 0; i < pdu_pos && i < q_len; i++) अणु
		skb = skb_dequeue(&llc->pdu_unack_q);
		kमुक्त_skb(skb);
		nbr_acked++;
	पूर्ण
out:
	*how_many_unacked = skb_queue_len(&llc->pdu_unack_q);
	वापस nbr_acked;
पूर्ण

/**
 *	llc_conn_send_pdus - Sends queued PDUs
 *	@sk: active connection
 *
 *	Sends queued pdus to MAC layer क्रम transmission.
 */
अटल व्योम llc_conn_send_pdus(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(&sk->sk_ग_लिखो_queue)) != शून्य) अणु
		काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

		अगर (LLC_PDU_TYPE_IS_I(pdu) &&
		    !(skb->dev->flags & IFF_LOOPBACK)) अणु
			काष्ठा sk_buff *skb2 = skb_clone(skb, GFP_ATOMIC);

			skb_queue_tail(&llc_sk(sk)->pdu_unack_q, skb);
			अगर (!skb2)
				अवरोध;
			skb = skb2;
		पूर्ण
		dev_queue_xmit(skb);
	पूर्ण
पूर्ण

/**
 *	llc_conn_service - finds transition and changes state of connection
 *	@sk: connection
 *	@skb: happened event
 *
 *	This function finds transition that matches with happened event, then
 *	executes related actions and finally changes state of connection.
 *	Returns 0 क्रम success, 1 क्रम failure.
 */
अटल पूर्णांक llc_conn_service(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = 1;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा llc_conn_state_trans *trans;

	अगर (llc->state > NBR_CONN_STATES)
		जाओ out;
	rc = 0;
	trans = llc_qualअगरy_conn_ev(sk, skb);
	अगर (trans) अणु
		rc = llc_exec_conn_trans_actions(sk, trans, skb);
		अगर (!rc && trans->next_state != NO_STATE_CHANGE) अणु
			llc->state = trans->next_state;
			अगर (!llc_data_accept_state(llc->state))
				sk->sk_state_change(sk);
		पूर्ण
	पूर्ण
out:
	वापस rc;
पूर्ण

/**
 *	llc_qualअगरy_conn_ev - finds transition क्रम event
 *	@sk: connection
 *	@skb: happened event
 *
 *	This function finds transition that matches with happened event.
 *	Returns poपूर्णांकer to found transition on success, %शून्य otherwise.
 */
अटल काष्ठा llc_conn_state_trans *llc_qualअगरy_conn_ev(काष्ठा sock *sk,
							काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_conn_state_trans **next_trans;
	स्थिर llc_conn_ev_qfyr_t *next_qualअगरier;
	काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा llc_conn_state *curr_state =
					&llc_conn_state_table[llc->state - 1];

	/* search thru events क्रम this state until
	 * list exhausted or until no more
	 */
	क्रम (next_trans = curr_state->transitions +
		llc_find_offset(llc->state - 1, ev->type);
	     (*next_trans)->ev; next_trans++) अणु
		अगर (!((*next_trans)->ev)(sk, skb)) अणु
			/* got POSSIBLE event match; the event may require
			 * qualअगरication based on the values of a number of
			 * state flags; अगर all qualअगरications are met (i.e.,
			 * अगर all qualअगरying functions वापस success, or 0,
			 * then this is THE event we're looking क्रम
			 */
			क्रम (next_qualअगरier = (*next_trans)->ev_qualअगरiers;
			     next_qualअगरier && *next_qualअगरier &&
			     !(*next_qualअगरier)(sk, skb); next_qualअगरier++)
				/* nothing */;
			अगर (!next_qualअगरier || !*next_qualअगरier)
				/* all qualअगरiers executed successfully; this is
				 * our transition; वापस it so we can perक्रमm
				 * the associated actions & change the state
				 */
				वापस *next_trans;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 *	llc_exec_conn_trans_actions - executes related actions
 *	@sk: connection
 *	@trans: transition that it's actions must be perक्रमmed
 *	@skb: event
 *
 *	Executes actions that is related to happened event. Returns 0 क्रम
 *	success, 1 to indicate failure of at least one action.
 */
अटल पूर्णांक llc_exec_conn_trans_actions(काष्ठा sock *sk,
				       काष्ठा llc_conn_state_trans *trans,
				       काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = 0;
	स्थिर llc_conn_action_t *next_action;

	क्रम (next_action = trans->ev_actions;
	     next_action && *next_action; next_action++) अणु
		पूर्णांक rc2 = (*next_action)(sk, skb);

		अगर (rc2 == 2) अणु
			rc = rc2;
			अवरोध;
		पूर्ण अन्यथा अगर (rc2)
			rc = 1;
	पूर्ण
	वापस rc;
पूर्ण

अटल अंतरभूत bool llc_estab_match(स्थिर काष्ठा llc_sap *sap,
				   स्थिर काष्ठा llc_addr *daddr,
				   स्थिर काष्ठा llc_addr *laddr,
				   स्थिर काष्ठा sock *sk)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);

	वापस llc->laddr.lsap == laddr->lsap &&
		llc->daddr.lsap == daddr->lsap &&
		ether_addr_equal(llc->laddr.mac, laddr->mac) &&
		ether_addr_equal(llc->daddr.mac, daddr->mac);
पूर्ण

/**
 *	__llc_lookup_established - Finds connection क्रम the remote/local sap/mac
 *	@sap: SAP
 *	@daddr: address of remote LLC (MAC + SAP)
 *	@laddr: address of local LLC (MAC + SAP)
 *
 *	Search connection list of the SAP and finds connection using the remote
 *	mac, remote sap, local mac, and local sap. Returns poपूर्णांकer क्रम
 *	connection found, %शून्य otherwise.
 *	Caller has to make sure local_bh is disabled.
 */
अटल काष्ठा sock *__llc_lookup_established(काष्ठा llc_sap *sap,
					     काष्ठा llc_addr *daddr,
					     काष्ठा llc_addr *laddr)
अणु
	काष्ठा sock *rc;
	काष्ठा hlist_nulls_node *node;
	पूर्णांक slot = llc_sk_laddr_hashfn(sap, laddr);
	काष्ठा hlist_nulls_head *laddr_hb = &sap->sk_laddr_hash[slot];

	rcu_पढ़ो_lock();
again:
	sk_nulls_क्रम_each_rcu(rc, node, laddr_hb) अणु
		अगर (llc_estab_match(sap, daddr, laddr, rc)) अणु
			/* Extra checks required by SLAB_TYPESAFE_BY_RCU */
			अगर (unlikely(!refcount_inc_not_zero(&rc->sk_refcnt)))
				जाओ again;
			अगर (unlikely(llc_sk(rc)->sap != sap ||
				     !llc_estab_match(sap, daddr, laddr, rc))) अणु
				sock_put(rc);
				जारी;
			पूर्ण
			जाओ found;
		पूर्ण
	पूर्ण
	rc = शून्य;
	/*
	 * अगर the nulls value we got at the end of this lookup is
	 * not the expected one, we must restart lookup.
	 * We probably met an item that was moved to another chain.
	 */
	अगर (unlikely(get_nulls_value(node) != slot))
		जाओ again;
found:
	rcu_पढ़ो_unlock();
	वापस rc;
पूर्ण

काष्ठा sock *llc_lookup_established(काष्ठा llc_sap *sap,
				    काष्ठा llc_addr *daddr,
				    काष्ठा llc_addr *laddr)
अणु
	काष्ठा sock *sk;

	local_bh_disable();
	sk = __llc_lookup_established(sap, daddr, laddr);
	local_bh_enable();
	वापस sk;
पूर्ण

अटल अंतरभूत bool llc_listener_match(स्थिर काष्ठा llc_sap *sap,
				      स्थिर काष्ठा llc_addr *laddr,
				      स्थिर काष्ठा sock *sk)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);

	वापस sk->sk_type == SOCK_STREAM && sk->sk_state == TCP_LISTEN &&
		llc->laddr.lsap == laddr->lsap &&
		ether_addr_equal(llc->laddr.mac, laddr->mac);
पूर्ण

अटल काष्ठा sock *__llc_lookup_listener(काष्ठा llc_sap *sap,
					  काष्ठा llc_addr *laddr)
अणु
	काष्ठा sock *rc;
	काष्ठा hlist_nulls_node *node;
	पूर्णांक slot = llc_sk_laddr_hashfn(sap, laddr);
	काष्ठा hlist_nulls_head *laddr_hb = &sap->sk_laddr_hash[slot];

	rcu_पढ़ो_lock();
again:
	sk_nulls_क्रम_each_rcu(rc, node, laddr_hb) अणु
		अगर (llc_listener_match(sap, laddr, rc)) अणु
			/* Extra checks required by SLAB_TYPESAFE_BY_RCU */
			अगर (unlikely(!refcount_inc_not_zero(&rc->sk_refcnt)))
				जाओ again;
			अगर (unlikely(llc_sk(rc)->sap != sap ||
				     !llc_listener_match(sap, laddr, rc))) अणु
				sock_put(rc);
				जारी;
			पूर्ण
			जाओ found;
		पूर्ण
	पूर्ण
	rc = शून्य;
	/*
	 * अगर the nulls value we got at the end of this lookup is
	 * not the expected one, we must restart lookup.
	 * We probably met an item that was moved to another chain.
	 */
	अगर (unlikely(get_nulls_value(node) != slot))
		जाओ again;
found:
	rcu_पढ़ो_unlock();
	वापस rc;
पूर्ण

/**
 *	llc_lookup_listener - Finds listener क्रम local MAC + SAP
 *	@sap: SAP
 *	@laddr: address of local LLC (MAC + SAP)
 *
 *	Search connection list of the SAP and finds connection listening on
 *	local mac, and local sap. Returns poपूर्णांकer क्रम parent socket found,
 *	%शून्य otherwise.
 *	Caller has to make sure local_bh is disabled.
 */
अटल काष्ठा sock *llc_lookup_listener(काष्ठा llc_sap *sap,
					काष्ठा llc_addr *laddr)
अणु
	अटल काष्ठा llc_addr null_addr;
	काष्ठा sock *rc = __llc_lookup_listener(sap, laddr);

	अगर (!rc)
		rc = __llc_lookup_listener(sap, &null_addr);

	वापस rc;
पूर्ण

अटल काष्ठा sock *__llc_lookup(काष्ठा llc_sap *sap,
				 काष्ठा llc_addr *daddr,
				 काष्ठा llc_addr *laddr)
अणु
	काष्ठा sock *sk = __llc_lookup_established(sap, daddr, laddr);

	वापस sk ? : llc_lookup_listener(sap, laddr);
पूर्ण

/**
 *	llc_data_accept_state - designates अगर in this state data can be sent.
 *	@state: state of connection.
 *
 *	Returns 0 अगर data can be sent, 1 otherwise.
 */
u8 llc_data_accept_state(u8 state)
अणु
	वापस state != LLC_CONN_STATE_NORMAL && state != LLC_CONN_STATE_BUSY &&
	       state != LLC_CONN_STATE_REJ;
पूर्ण

/**
 *	llc_find_next_offset - finds offset क्रम next category of transitions
 *	@state: state table.
 *	@offset: start offset.
 *
 *	Finds offset of next category of transitions in transition table.
 *	Returns the start index of next category.
 */
अटल u16 __init llc_find_next_offset(काष्ठा llc_conn_state *state, u16 offset)
अणु
	u16 cnt = 0;
	काष्ठा llc_conn_state_trans **next_trans;

	क्रम (next_trans = state->transitions + offset;
	     (*next_trans)->ev; next_trans++)
		++cnt;
	वापस cnt;
पूर्ण

/**
 *	llc_build_offset_table - builds offset table of connection
 *
 *	Fills offset table of connection state transition table
 *	(llc_offset_table).
 */
व्योम __init llc_build_offset_table(व्योम)
अणु
	काष्ठा llc_conn_state *curr_state;
	पूर्णांक state, ev_type, next_offset;

	क्रम (state = 0; state < NBR_CONN_STATES; state++) अणु
		curr_state = &llc_conn_state_table[state];
		next_offset = 0;
		क्रम (ev_type = 0; ev_type < NBR_CONN_EV; ev_type++) अणु
			llc_offset_table[state][ev_type] = next_offset;
			next_offset += llc_find_next_offset(curr_state,
							    next_offset) + 1;
		पूर्ण
	पूर्ण
पूर्ण

/**
 *	llc_find_offset - finds start offset of category of transitions
 *	@state: state of connection
 *	@ev_type: type of happened event
 *
 *	Finds start offset of desired category of transitions. Returns the
 *	desired start offset.
 */
अटल पूर्णांक llc_find_offset(पूर्णांक state, पूर्णांक ev_type)
अणु
	पूर्णांक rc = 0;
	/* at this stage, llc_offset_table[..][2] is not important. it is क्रम
	 * init_pf_cycle and I करोn't know what is it.
	 */
	चयन (ev_type) अणु
	हाल LLC_CONN_EV_TYPE_PRIM:
		rc = llc_offset_table[state][0]; अवरोध;
	हाल LLC_CONN_EV_TYPE_PDU:
		rc = llc_offset_table[state][4]; अवरोध;
	हाल LLC_CONN_EV_TYPE_SIMPLE:
		rc = llc_offset_table[state][1]; अवरोध;
	हाल LLC_CONN_EV_TYPE_P_TMR:
	हाल LLC_CONN_EV_TYPE_ACK_TMR:
	हाल LLC_CONN_EV_TYPE_REJ_TMR:
	हाल LLC_CONN_EV_TYPE_BUSY_TMR:
		rc = llc_offset_table[state][3]; अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

/**
 *	llc_sap_add_socket - adds a socket to a SAP
 *	@sap: SAP
 *	@sk: socket
 *
 *	This function adds a socket to the hash tables of a SAP.
 */
व्योम llc_sap_add_socket(काष्ठा llc_sap *sap, काष्ठा sock *sk)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा hlist_head *dev_hb = llc_sk_dev_hash(sap, llc->dev->अगरindex);
	काष्ठा hlist_nulls_head *laddr_hb = llc_sk_laddr_hash(sap, &llc->laddr);

	llc_sap_hold(sap);
	llc_sk(sk)->sap = sap;

	spin_lock_bh(&sap->sk_lock);
	sock_set_flag(sk, SOCK_RCU_FREE);
	sap->sk_count++;
	sk_nulls_add_node_rcu(sk, laddr_hb);
	hlist_add_head(&llc->dev_hash_node, dev_hb);
	spin_unlock_bh(&sap->sk_lock);
पूर्ण

/**
 *	llc_sap_हटाओ_socket - हटाओs a socket from SAP
 *	@sap: SAP
 *	@sk: socket
 *
 *	This function हटाओs a connection from the hash tables of a SAP अगर
 *	the connection was in this list.
 */
व्योम llc_sap_हटाओ_socket(काष्ठा llc_sap *sap, काष्ठा sock *sk)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);

	spin_lock_bh(&sap->sk_lock);
	sk_nulls_del_node_init_rcu(sk);
	hlist_del(&llc->dev_hash_node);
	sap->sk_count--;
	spin_unlock_bh(&sap->sk_lock);
	llc_sap_put(sap);
पूर्ण

/**
 *	llc_conn_rcv - sends received pdus to the connection state machine
 *	@sk: current connection काष्ठाure.
 *	@skb: received frame.
 *
 *	Sends received pdus to the connection state machine.
 */
अटल पूर्णांक llc_conn_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	ev->type   = LLC_CONN_EV_TYPE_PDU;
	ev->reason = 0;
	वापस llc_conn_state_process(sk, skb);
पूर्ण

अटल काष्ठा sock *llc_create_incoming_sock(काष्ठा sock *sk,
					     काष्ठा net_device *dev,
					     काष्ठा llc_addr *saddr,
					     काष्ठा llc_addr *daddr)
अणु
	काष्ठा sock *newsk = llc_sk_alloc(sock_net(sk), sk->sk_family, GFP_ATOMIC,
					  sk->sk_prot, 0);
	काष्ठा llc_sock *newllc, *llc = llc_sk(sk);

	अगर (!newsk)
		जाओ out;
	newllc = llc_sk(newsk);
	स_नकल(&newllc->laddr, daddr, माप(newllc->laddr));
	स_नकल(&newllc->daddr, saddr, माप(newllc->daddr));
	newllc->dev = dev;
	dev_hold(dev);
	llc_sap_add_socket(llc->sap, newsk);
	llc_sap_hold(llc->sap);
out:
	वापस newsk;
पूर्ण

व्योम llc_conn_handler(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_addr saddr, daddr;
	काष्ठा sock *sk;

	llc_pdu_decode_sa(skb, saddr.mac);
	llc_pdu_decode_ssap(skb, &saddr.lsap);
	llc_pdu_decode_da(skb, daddr.mac);
	llc_pdu_decode_dsap(skb, &daddr.lsap);

	sk = __llc_lookup(sap, &saddr, &daddr);
	अगर (!sk)
		जाओ drop;

	bh_lock_sock(sk);
	/*
	 * This has to be करोne here and not at the upper layer ->accept
	 * method because of the way the PROCOM state machine works:
	 * it needs to set several state variables (see, क्रम instance,
	 * llc_adm_actions_2 in net/llc/llc_c_st.c) and send a packet to
	 * the originator of the new connection, and this state has to be
	 * in the newly created काष्ठा sock निजी area. -acme
	 */
	अगर (unlikely(sk->sk_state == TCP_LISTEN)) अणु
		काष्ठा sock *newsk = llc_create_incoming_sock(sk, skb->dev,
							      &saddr, &daddr);
		अगर (!newsk)
			जाओ drop_unlock;
		skb_set_owner_r(skb, newsk);
	पूर्ण अन्यथा अणु
		/*
		 * Can't be skb_set_owner_r, this will be करोne at the
		 * llc_conn_state_process function, later on, when we will use
		 * skb_queue_rcv_skb to send it to upper layers, this is
		 * another trick required to cope with how the PROCOM state
		 * machine works. -acme
		 */
		skb_orphan(skb);
		sock_hold(sk);
		skb->sk = sk;
		skb->deकाष्ठाor = sock_eमुक्त;
	पूर्ण
	अगर (!sock_owned_by_user(sk))
		llc_conn_rcv(sk, skb);
	अन्यथा अणु
		dprपूर्णांकk("%s: adding to backlog...\n", __func__);
		llc_set_backlog_type(skb, LLC_PACKET);
		अगर (sk_add_backlog(sk, skb, READ_ONCE(sk->sk_rcvbuf)))
			जाओ drop_unlock;
	पूर्ण
out:
	bh_unlock_sock(sk);
	sock_put(sk);
	वापस;
drop:
	kमुक्त_skb(skb);
	वापस;
drop_unlock:
	kमुक्त_skb(skb);
	जाओ out;
पूर्ण

#अघोषित LLC_REFCNT_DEBUG
#अगर_घोषित LLC_REFCNT_DEBUG
अटल atomic_t llc_sock_nr;
#पूर्ण_अगर

/**
 *	llc_backlog_rcv - Processes rx frames and expired समयrs.
 *	@sk: LLC sock (p8022 connection)
 *	@skb: queued rx frame or event
 *
 *	This function processes frames that has received and समयrs that has
 *	expired during sending an I pdu (refer to data_req_handler).  frames
 *	queue by llc_rcv function (llc_mac.c) and समयrs queue by समयr
 *	callback functions(llc_c_ac.c).
 */
अटल पूर्णांक llc_backlog_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = 0;
	काष्ठा llc_sock *llc = llc_sk(sk);

	अगर (likely(llc_backlog_type(skb) == LLC_PACKET)) अणु
		अगर (likely(llc->state > 1)) /* not बंदd */
			rc = llc_conn_rcv(sk, skb);
		अन्यथा
			जाओ out_kमुक्त_skb;
	पूर्ण अन्यथा अगर (llc_backlog_type(skb) == LLC_EVENT) अणु
		/* समयr expiration event */
		अगर (likely(llc->state > 1))  /* not बंदd */
			rc = llc_conn_state_process(sk, skb);
		अन्यथा
			जाओ out_kमुक्त_skb;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "%s: invalid skb in backlog\n", __func__);
		जाओ out_kमुक्त_skb;
	पूर्ण
out:
	वापस rc;
out_kमुक्त_skb:
	kमुक्त_skb(skb);
	जाओ out;
पूर्ण

/**
 *     llc_sk_init - Initializes a socket with शेष llc values.
 *     @sk: socket to initialize.
 *
 *     Initializes a socket with शेष llc values.
 */
अटल व्योम llc_sk_init(काष्ठा sock *sk)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);

	llc->state    = LLC_CONN_STATE_ADM;
	llc->inc_cntr = llc->dec_cntr = 2;
	llc->dec_step = llc->connect_step = 1;

	समयr_setup(&llc->ack_समयr.समयr, llc_conn_ack_पंचांगr_cb, 0);
	llc->ack_समयr.expire	      = sysctl_llc2_ack_समयout;

	समयr_setup(&llc->pf_cycle_समयr.समयr, llc_conn_pf_cycle_पंचांगr_cb, 0);
	llc->pf_cycle_समयr.expire	   = sysctl_llc2_p_समयout;

	समयr_setup(&llc->rej_sent_समयr.समयr, llc_conn_rej_पंचांगr_cb, 0);
	llc->rej_sent_समयr.expire	   = sysctl_llc2_rej_समयout;

	समयr_setup(&llc->busy_state_समयr.समयr, llc_conn_busy_पंचांगr_cb, 0);
	llc->busy_state_समयr.expire	     = sysctl_llc2_busy_समयout;

	llc->n2 = 2;   /* max retransmit */
	llc->k  = 2;   /* tx win size, will adjust dynam */
	llc->rw = 128; /* rx win size (opt and equal to
			* tx_win of remote LLC) */
	skb_queue_head_init(&llc->pdu_unack_q);
	sk->sk_backlog_rcv = llc_backlog_rcv;
पूर्ण

/**
 *	llc_sk_alloc - Allocates LLC sock
 *	@net: network namespace
 *	@family: upper layer protocol family
 *	@priority: क्रम allocation (%GFP_KERNEL, %GFP_ATOMIC, etc)
 *	@prot: काष्ठा proto associated with this new sock instance
 *	@kern: is this to be a kernel socket?
 *
 *	Allocates a LLC sock and initializes it. Returns the new LLC sock
 *	or %शून्य अगर there's no memory available क्रम one
 */
काष्ठा sock *llc_sk_alloc(काष्ठा net *net, पूर्णांक family, gfp_t priority, काष्ठा proto *prot, पूर्णांक kern)
अणु
	काष्ठा sock *sk = sk_alloc(net, family, priority, prot, kern);

	अगर (!sk)
		जाओ out;
	llc_sk_init(sk);
	sock_init_data(शून्य, sk);
#अगर_घोषित LLC_REFCNT_DEBUG
	atomic_inc(&llc_sock_nr);
	prपूर्णांकk(KERN_DEBUG "LLC socket %p created in %s, now we have %d alive\n", sk,
		__func__, atomic_पढ़ो(&llc_sock_nr));
#पूर्ण_अगर
out:
	वापस sk;
पूर्ण

व्योम llc_sk_stop_all_समयrs(काष्ठा sock *sk, bool sync)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);

	अगर (sync) अणु
		del_समयr_sync(&llc->pf_cycle_समयr.समयr);
		del_समयr_sync(&llc->ack_समयr.समयr);
		del_समयr_sync(&llc->rej_sent_समयr.समयr);
		del_समयr_sync(&llc->busy_state_समयr.समयr);
	पूर्ण अन्यथा अणु
		del_समयr(&llc->pf_cycle_समयr.समयr);
		del_समयr(&llc->ack_समयr.समयr);
		del_समयr(&llc->rej_sent_समयr.समयr);
		del_समयr(&llc->busy_state_समयr.समयr);
	पूर्ण

	llc->ack_must_be_send = 0;
	llc->ack_pf = 0;
पूर्ण

/**
 *	llc_sk_मुक्त - Frees a LLC socket
 *	@sk: - socket to मुक्त
 *
 *	Frees a LLC socket
 */
व्योम llc_sk_मुक्त(काष्ठा sock *sk)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);

	llc->state = LLC_CONN_OUT_OF_SVC;
	/* Stop all (possibly) running समयrs */
	llc_sk_stop_all_समयrs(sk, true);
#अगर_घोषित DEBUG_LLC_CONN_ALLOC
	prपूर्णांकk(KERN_INFO "%s: unackq=%d, txq=%d\n", __func__,
		skb_queue_len(&llc->pdu_unack_q),
		skb_queue_len(&sk->sk_ग_लिखो_queue));
#पूर्ण_अगर
	skb_queue_purge(&sk->sk_receive_queue);
	skb_queue_purge(&sk->sk_ग_लिखो_queue);
	skb_queue_purge(&llc->pdu_unack_q);
#अगर_घोषित LLC_REFCNT_DEBUG
	अगर (refcount_पढ़ो(&sk->sk_refcnt) != 1) अणु
		prपूर्णांकk(KERN_DEBUG "Destruction of LLC sock %p delayed in %s, cnt=%d\n",
			sk, __func__, refcount_पढ़ो(&sk->sk_refcnt));
		prपूर्णांकk(KERN_DEBUG "%d LLC sockets are still alive\n",
			atomic_पढ़ो(&llc_sock_nr));
	पूर्ण अन्यथा अणु
		atomic_dec(&llc_sock_nr);
		prपूर्णांकk(KERN_DEBUG "LLC socket %p released in %s, %d are still alive\n", sk,
			__func__, atomic_पढ़ो(&llc_sock_nr));
	पूर्ण
#पूर्ण_अगर
	sock_put(sk);
पूर्ण

/**
 *	llc_sk_reset - resets a connection
 *	@sk: LLC socket to reset
 *
 *	Resets a connection to the out of service state. Stops its समयrs
 *	and मुक्तs any frames in the queues of the connection.
 */
व्योम llc_sk_reset(काष्ठा sock *sk)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);

	llc_conn_ac_stop_all_समयrs(sk, शून्य);
	skb_queue_purge(&sk->sk_ग_लिखो_queue);
	skb_queue_purge(&llc->pdu_unack_q);
	llc->remote_busy_flag	= 0;
	llc->cause_flag		= 0;
	llc->retry_count	= 0;
	llc_conn_set_p_flag(sk, 0);
	llc->f_flag		= 0;
	llc->s_flag		= 0;
	llc->ack_pf		= 0;
	llc->first_pdu_Ns	= 0;
	llc->ack_must_be_send	= 0;
	llc->dec_step		= 1;
	llc->inc_cntr		= 2;
	llc->dec_cntr		= 2;
	llc->X			= 0;
	llc->failed_data_req	= 0 ;
	llc->last_nr		= 0;
पूर्ण
