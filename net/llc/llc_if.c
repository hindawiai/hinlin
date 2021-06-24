<शैली गुरु>
/*
 * llc_अगर.c - Defines LLC पूर्णांकerface to upper layer
 *
 * Copyright (c) 1997 by Procom Technology, Inc.
 * 		 2001-2003 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */
#समावेश <linux/gfp.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <net/llc_अगर.h>
#समावेश <net/llc_sap.h>
#समावेश <net/llc_s_ev.h>
#समावेश <net/llc_conn.h>
#समावेश <net/sock.h>
#समावेश <net/llc_c_ev.h>
#समावेश <net/llc_c_ac.h>
#समावेश <net/llc_c_st.h>
#समावेश <net/tcp_states.h>

/**
 *	llc_build_and_send_pkt - Connection data sending क्रम upper layers.
 *	@sk: connection
 *	@skb: packet to send
 *
 *	This function is called when upper layer wants to send data using
 *	connection oriented communication mode. During sending data, connection
 *	will be locked and received frames and expired समयrs will be queued.
 *	Returns 0 क्रम success, -ECONNABORTED when the connection alपढ़ोy
 *	बंदd and -EBUSY when sending data is not permitted in this state or
 *	LLC has send an I pdu with p bit set to 1 and is रुकोing क्रम it's
 *	response.
 *
 *	This function always consumes a reference to the skb.
 */
पूर्णांक llc_build_and_send_pkt(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_conn_state_ev *ev;
	पूर्णांक rc = -ECONNABORTED;
	काष्ठा llc_sock *llc = llc_sk(sk);

	अगर (unlikely(llc->state == LLC_CONN_STATE_ADM))
		जाओ out_मुक्त;
	rc = -EBUSY;
	अगर (unlikely(llc_data_accept_state(llc->state) || /* data_conn_refuse */
		     llc->p_flag)) अणु
		llc->failed_data_req = 1;
		जाओ out_मुक्त;
	पूर्ण
	ev = llc_conn_ev(skb);
	ev->type      = LLC_CONN_EV_TYPE_PRIM;
	ev->prim      = LLC_DATA_PRIM;
	ev->prim_type = LLC_PRIM_TYPE_REQ;
	skb->dev      = llc->dev;
	वापस llc_conn_state_process(sk, skb);

out_मुक्त:
	kमुक्त_skb(skb);
	वापस rc;
पूर्ण

/**
 *	llc_establish_connection - Called by upper layer to establish a conn
 *	@sk: connection
 *	@lmac: local mac address
 *	@dmac: destination mac address
 *	@dsap: destination sap
 *
 *	Upper layer calls this to establish an LLC connection with a remote
 *	machine. This function packages a proper event and sends it connection
 *	component state machine. Success or failure of connection
 *	establishment will inक्रमm to upper layer via calling it's confirm
 *	function and passing proper inक्रमmation.
 */
पूर्णांक llc_establish_connection(काष्ठा sock *sk, u8 *lmac, u8 *dmac, u8 dsap)
अणु
	पूर्णांक rc = -EISCONN;
	काष्ठा llc_addr laddr, daddr;
	काष्ठा sk_buff *skb;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sock *existing;

	laddr.lsap = llc->sap->laddr.lsap;
	daddr.lsap = dsap;
	स_नकल(daddr.mac, dmac, माप(daddr.mac));
	स_नकल(laddr.mac, lmac, माप(laddr.mac));
	existing = llc_lookup_established(llc->sap, &daddr, &laddr);
	अगर (existing) अणु
		अगर (existing->sk_state == TCP_ESTABLISHED) अणु
			sk = existing;
			जाओ out_put;
		पूर्ण अन्यथा
			sock_put(existing);
	पूर्ण
	sock_hold(sk);
	rc = -ENOMEM;
	skb = alloc_skb(0, GFP_ATOMIC);
	अगर (skb) अणु
		काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

		ev->type      = LLC_CONN_EV_TYPE_PRIM;
		ev->prim      = LLC_CONN_PRIM;
		ev->prim_type = LLC_PRIM_TYPE_REQ;
		skb_set_owner_w(skb, sk);
		rc = llc_conn_state_process(sk, skb);
	पूर्ण
out_put:
	sock_put(sk);
	वापस rc;
पूर्ण

/**
 *	llc_send_disc - Called by upper layer to बंद a connection
 *	@sk: connection to be बंदd
 *
 *	Upper layer calls this when it wants to बंद an established LLC
 *	connection with a remote machine. This function packages a proper event
 *	and sends it to connection component state machine. Returns 0 क्रम
 *	success, 1 otherwise.
 */
पूर्णांक llc_send_disc(काष्ठा sock *sk)
अणु
	u16 rc = 1;
	काष्ठा llc_conn_state_ev *ev;
	काष्ठा sk_buff *skb;

	sock_hold(sk);
	अगर (sk->sk_type != SOCK_STREAM || sk->sk_state != TCP_ESTABLISHED ||
	    llc_sk(sk)->state == LLC_CONN_STATE_ADM ||
	    llc_sk(sk)->state == LLC_CONN_OUT_OF_SVC)
		जाओ out;
	/*
	 * Postpone unassigning the connection from its SAP and वापसing the
	 * connection until all ACTIONs have been completely executed
	 */
	skb = alloc_skb(0, GFP_ATOMIC);
	अगर (!skb)
		जाओ out;
	skb_set_owner_w(skb, sk);
	sk->sk_state  = TCP_CLOSING;
	ev	      = llc_conn_ev(skb);
	ev->type      = LLC_CONN_EV_TYPE_PRIM;
	ev->prim      = LLC_DISC_PRIM;
	ev->prim_type = LLC_PRIM_TYPE_REQ;
	rc = llc_conn_state_process(sk, skb);
out:
	sock_put(sk);
	वापस rc;
पूर्ण
