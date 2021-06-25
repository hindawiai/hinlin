<शैली गुरु>
/*
 * llc_sap.c - driver routines क्रम SAP component.
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

#समावेश <net/llc.h>
#समावेश <net/llc_अगर.h>
#समावेश <net/llc_conn.h>
#समावेश <net/llc_pdu.h>
#समावेश <net/llc_sap.h>
#समावेश <net/llc_s_ac.h>
#समावेश <net/llc_s_ev.h>
#समावेश <net/llc_s_st.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <linux/llc.h>
#समावेश <linux/slab.h>

अटल पूर्णांक llc_mac_header_len(अचिन्हित लघु devtype)
अणु
	चयन (devtype) अणु
	हाल ARPHRD_ETHER:
	हाल ARPHRD_LOOPBACK:
		वापस माप(काष्ठा ethhdr);
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	llc_alloc_frame - allocates sk_buff क्रम frame
 *	@sk:  socket to allocate frame to
 *	@dev: network device this skb will be sent over
 *	@type: pdu type to allocate
 *	@data_size: data size to allocate
 *
 *	Allocates an sk_buff क्रम frame and initializes sk_buff fields.
 *	Returns allocated skb or %शून्य when out of memory.
 */
काष्ठा sk_buff *llc_alloc_frame(काष्ठा sock *sk, काष्ठा net_device *dev,
				u8 type, u32 data_size)
अणु
	पूर्णांक hlen = type == LLC_PDU_TYPE_U ? 3 : 4;
	काष्ठा sk_buff *skb;

	hlen += llc_mac_header_len(dev->type);
	skb = alloc_skb(hlen + data_size, GFP_ATOMIC);

	अगर (skb) अणु
		skb_reset_mac_header(skb);
		skb_reserve(skb, hlen);
		skb_reset_network_header(skb);
		skb_reset_transport_header(skb);
		skb->protocol = htons(ETH_P_802_2);
		skb->dev      = dev;
		अगर (sk != शून्य)
			skb_set_owner_w(skb, sk);
	पूर्ण
	वापस skb;
पूर्ण

व्योम llc_save_primitive(काष्ठा sock *sk, काष्ठा sk_buff *skb, u8 prim)
अणु
	काष्ठा sockaddr_llc *addr;

       /* save primitive क्रम use by the user. */
	addr		  = llc_ui_skb_cb(skb);

	स_रखो(addr, 0, माप(*addr));
	addr->sllc_family = sk->sk_family;
	addr->sllc_arphrd = skb->dev->type;
	addr->sllc_test   = prim == LLC_TEST_PRIM;
	addr->sllc_xid    = prim == LLC_XID_PRIM;
	addr->sllc_ua     = prim == LLC_DATAUNIT_PRIM;
	llc_pdu_decode_sa(skb, addr->sllc_mac);
	llc_pdu_decode_ssap(skb, &addr->sllc_sap);
पूर्ण

/**
 *	llc_sap_rtn_pdu - Inक्रमms upper layer on rx of an UI, XID or TEST pdu.
 *	@sap: poपूर्णांकer to SAP
 *	@skb: received pdu
 */
व्योम llc_sap_rtn_pdu(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sap_state_ev *ev = llc_sap_ev(skb);
	काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	चयन (LLC_U_PDU_RSP(pdu)) अणु
	हाल LLC_1_PDU_CMD_TEST:
		ev->prim = LLC_TEST_PRIM;	अवरोध;
	हाल LLC_1_PDU_CMD_XID:
		ev->prim = LLC_XID_PRIM;	अवरोध;
	हाल LLC_1_PDU_CMD_UI:
		ev->prim = LLC_DATAUNIT_PRIM;	अवरोध;
	पूर्ण
	ev->ind_cfm_flag = LLC_IND;
पूर्ण

/**
 *	llc_find_sap_trans - finds transition क्रम event
 *	@sap: poपूर्णांकer to SAP
 *	@skb: happened event
 *
 *	This function finds transition that matches with happened event.
 *	Returns the poपूर्णांकer to found transition on success or %शून्य क्रम
 *	failure.
 */
अटल काष्ठा llc_sap_state_trans *llc_find_sap_trans(काष्ठा llc_sap *sap,
						      काष्ठा sk_buff *skb)
अणु
	पूर्णांक i = 0;
	काष्ठा llc_sap_state_trans *rc = शून्य;
	काष्ठा llc_sap_state_trans **next_trans;
	काष्ठा llc_sap_state *curr_state = &llc_sap_state_table[sap->state - 1];
	/*
	 * Search thru events क्रम this state until list exhausted or until
	 * its obvious the event is not valid क्रम the current state
	 */
	क्रम (next_trans = curr_state->transitions; next_trans[i]->ev; i++)
		अगर (!next_trans[i]->ev(sap, skb)) अणु
			rc = next_trans[i]; /* got event match; वापस it */
			अवरोध;
		पूर्ण
	वापस rc;
पूर्ण

/**
 *	llc_exec_sap_trans_actions - execute actions related to event
 *	@sap: poपूर्णांकer to SAP
 *	@trans: poपूर्णांकer to transition that it's actions must be perक्रमmed
 *	@skb: happened event.
 *
 *	This function executes actions that is related to happened event.
 *	Returns 0 क्रम success and 1 क्रम failure of at least one action.
 */
अटल पूर्णांक llc_exec_sap_trans_actions(काष्ठा llc_sap *sap,
				      काष्ठा llc_sap_state_trans *trans,
				      काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = 0;
	स्थिर llc_sap_action_t *next_action = trans->ev_actions;

	क्रम (; next_action && *next_action; next_action++)
		अगर ((*next_action)(sap, skb))
			rc = 1;
	वापस rc;
पूर्ण

/**
 *	llc_sap_next_state - finds transition, execs actions & change SAP state
 *	@sap: poपूर्णांकer to SAP
 *	@skb: happened event
 *
 *	This function finds transition that matches with happened event, then
 *	executes related actions and finally changes state of SAP. It वापसs
 *	0 on success and 1 क्रम failure.
 */
अटल पूर्णांक llc_sap_next_state(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = 1;
	काष्ठा llc_sap_state_trans *trans;

	अगर (sap->state > LLC_NR_SAP_STATES)
		जाओ out;
	trans = llc_find_sap_trans(sap, skb);
	अगर (!trans)
		जाओ out;
	/*
	 * Got the state to which we next transition; perक्रमm the actions
	 * associated with this transition beक्रमe actually transitioning to the
	 * next state
	 */
	rc = llc_exec_sap_trans_actions(sap, trans, skb);
	अगर (rc)
		जाओ out;
	/*
	 * Transition SAP to next state अगर all actions execute successfully
	 */
	sap->state = trans->next_state;
out:
	वापस rc;
पूर्ण

/**
 *	llc_sap_state_process - sends event to SAP state machine
 *	@sap: sap to use
 *	@skb: poपूर्णांकer to occurred event
 *
 *	After executing actions of the event, upper layer will be indicated
 *	अगर needed(on receiving an UI frame). sk can be null क्रम the
 *	datalink_proto हाल.
 *
 *	This function always consumes a reference to the skb.
 */
अटल व्योम llc_sap_state_process(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sap_state_ev *ev = llc_sap_ev(skb);

	ev->ind_cfm_flag = 0;
	llc_sap_next_state(sap, skb);

	अगर (ev->ind_cfm_flag == LLC_IND && skb->sk->sk_state != TCP_LISTEN) अणु
		llc_save_primitive(skb->sk, skb, ev->prim);

		/* queue skb to the user. */
		अगर (sock_queue_rcv_skb(skb->sk, skb) == 0)
			वापस;
	पूर्ण
	kमुक्त_skb(skb);
पूर्ण

/**
 *	llc_build_and_send_test_pkt - TEST पूर्णांकerface क्रम upper layers.
 *	@sap: sap to use
 *	@skb: packet to send
 *	@dmac: destination mac address
 *	@dsap: destination sap
 *
 *	This function is called when upper layer wants to send a TEST pdu.
 *	Returns 0 क्रम success, 1 otherwise.
 */
व्योम llc_build_and_send_test_pkt(काष्ठा llc_sap *sap,
				 काष्ठा sk_buff *skb, u8 *dmac, u8 dsap)
अणु
	काष्ठा llc_sap_state_ev *ev = llc_sap_ev(skb);

	ev->saddr.lsap = sap->laddr.lsap;
	ev->daddr.lsap = dsap;
	स_नकल(ev->saddr.mac, skb->dev->dev_addr, IFHWADDRLEN);
	स_नकल(ev->daddr.mac, dmac, IFHWADDRLEN);

	ev->type      = LLC_SAP_EV_TYPE_PRIM;
	ev->prim      = LLC_TEST_PRIM;
	ev->prim_type = LLC_PRIM_TYPE_REQ;
	llc_sap_state_process(sap, skb);
पूर्ण

/**
 *	llc_build_and_send_xid_pkt - XID पूर्णांकerface क्रम upper layers
 *	@sap: sap to use
 *	@skb: packet to send
 *	@dmac: destination mac address
 *	@dsap: destination sap
 *
 *	This function is called when upper layer wants to send a XID pdu.
 *	Returns 0 क्रम success, 1 otherwise.
 */
व्योम llc_build_and_send_xid_pkt(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb,
				u8 *dmac, u8 dsap)
अणु
	काष्ठा llc_sap_state_ev *ev = llc_sap_ev(skb);

	ev->saddr.lsap = sap->laddr.lsap;
	ev->daddr.lsap = dsap;
	स_नकल(ev->saddr.mac, skb->dev->dev_addr, IFHWADDRLEN);
	स_नकल(ev->daddr.mac, dmac, IFHWADDRLEN);

	ev->type      = LLC_SAP_EV_TYPE_PRIM;
	ev->prim      = LLC_XID_PRIM;
	ev->prim_type = LLC_PRIM_TYPE_REQ;
	llc_sap_state_process(sap, skb);
पूर्ण

/**
 *	llc_sap_rcv - sends received pdus to the sap state machine
 *	@sap: current sap component काष्ठाure.
 *	@skb: received frame.
 *	@sk:  socket to associate to frame
 *
 *	Sends received pdus to the sap state machine.
 */
अटल व्योम llc_sap_rcv(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb,
			काष्ठा sock *sk)
अणु
	काष्ठा llc_sap_state_ev *ev = llc_sap_ev(skb);

	ev->type   = LLC_SAP_EV_TYPE_PDU;
	ev->reason = 0;
	skb_orphan(skb);
	sock_hold(sk);
	skb->sk = sk;
	skb->deकाष्ठाor = sock_eमुक्त;
	llc_sap_state_process(sap, skb);
पूर्ण

अटल अंतरभूत bool llc_dgram_match(स्थिर काष्ठा llc_sap *sap,
				   स्थिर काष्ठा llc_addr *laddr,
				   स्थिर काष्ठा sock *sk)
अणु
     काष्ठा llc_sock *llc = llc_sk(sk);

     वापस sk->sk_type == SOCK_DGRAM &&
	  llc->laddr.lsap == laddr->lsap &&
	  ether_addr_equal(llc->laddr.mac, laddr->mac);
पूर्ण

/**
 *	llc_lookup_dgram - Finds dgram socket क्रम the local sap/mac
 *	@sap: SAP
 *	@laddr: address of local LLC (MAC + SAP)
 *
 *	Search socket list of the SAP and finds connection using the local
 *	mac, and local sap. Returns poपूर्णांकer क्रम socket found, %शून्य otherwise.
 */
अटल काष्ठा sock *llc_lookup_dgram(काष्ठा llc_sap *sap,
				     स्थिर काष्ठा llc_addr *laddr)
अणु
	काष्ठा sock *rc;
	काष्ठा hlist_nulls_node *node;
	पूर्णांक slot = llc_sk_laddr_hashfn(sap, laddr);
	काष्ठा hlist_nulls_head *laddr_hb = &sap->sk_laddr_hash[slot];

	rcu_पढ़ो_lock_bh();
again:
	sk_nulls_क्रम_each_rcu(rc, node, laddr_hb) अणु
		अगर (llc_dgram_match(sap, laddr, rc)) अणु
			/* Extra checks required by SLAB_TYPESAFE_BY_RCU */
			अगर (unlikely(!refcount_inc_not_zero(&rc->sk_refcnt)))
				जाओ again;
			अगर (unlikely(llc_sk(rc)->sap != sap ||
				     !llc_dgram_match(sap, laddr, rc))) अणु
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
	rcu_पढ़ो_unlock_bh();
	वापस rc;
पूर्ण

अटल अंतरभूत bool llc_mcast_match(स्थिर काष्ठा llc_sap *sap,
				   स्थिर काष्ठा llc_addr *laddr,
				   स्थिर काष्ठा sk_buff *skb,
				   स्थिर काष्ठा sock *sk)
अणु
     काष्ठा llc_sock *llc = llc_sk(sk);

     वापस sk->sk_type == SOCK_DGRAM &&
	  llc->laddr.lsap == laddr->lsap &&
	  llc->dev == skb->dev;
पूर्ण

अटल व्योम llc_करो_mcast(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb,
			 काष्ठा sock **stack, पूर्णांक count)
अणु
	काष्ठा sk_buff *skb1;
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		skb1 = skb_clone(skb, GFP_ATOMIC);
		अगर (!skb1) अणु
			sock_put(stack[i]);
			जारी;
		पूर्ण

		llc_sap_rcv(sap, skb1, stack[i]);
		sock_put(stack[i]);
	पूर्ण
पूर्ण

/**
 * 	llc_sap_mcast - Deliver multicast PDU's to all matching datagram sockets.
 *	@sap: SAP
 *	@laddr: address of local LLC (MAC + SAP)
 *	@skb: PDU to deliver
 *
 *	Search socket list of the SAP and finds connections with same sap.
 *	Deliver clone to each.
 */
अटल व्योम llc_sap_mcast(काष्ठा llc_sap *sap,
			  स्थिर काष्ठा llc_addr *laddr,
			  काष्ठा sk_buff *skb)
अणु
	पूर्णांक i = 0;
	काष्ठा sock *sk;
	काष्ठा sock *stack[256 / माप(काष्ठा sock *)];
	काष्ठा llc_sock *llc;
	काष्ठा hlist_head *dev_hb = llc_sk_dev_hash(sap, skb->dev->अगरindex);

	spin_lock_bh(&sap->sk_lock);
	hlist_क्रम_each_entry(llc, dev_hb, dev_hash_node) अणु

		sk = &llc->sk;

		अगर (!llc_mcast_match(sap, laddr, skb, sk))
			जारी;

		sock_hold(sk);
		अगर (i < ARRAY_SIZE(stack))
			stack[i++] = sk;
		अन्यथा अणु
			llc_करो_mcast(sap, skb, stack, i);
			i = 0;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&sap->sk_lock);

	llc_करो_mcast(sap, skb, stack, i);
पूर्ण


व्योम llc_sap_handler(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_addr laddr;

	llc_pdu_decode_da(skb, laddr.mac);
	llc_pdu_decode_dsap(skb, &laddr.lsap);

	अगर (is_multicast_ether_addr(laddr.mac)) अणु
		llc_sap_mcast(sap, &laddr, skb);
		kमुक्त_skb(skb);
	पूर्ण अन्यथा अणु
		काष्ठा sock *sk = llc_lookup_dgram(sap, &laddr);
		अगर (sk) अणु
			llc_sap_rcv(sap, skb, sk);
			sock_put(sk);
		पूर्ण अन्यथा
			kमुक्त_skb(skb);
	पूर्ण
पूर्ण
