<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* incoming call handling
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/errqueue.h>
#समावेश <linux/udp.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/icmp.h>
#समावेश <linux/gfp.h>
#समावेश <linux/circ_buf.h>
#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश <net/ip.h>
#समावेश "ar-internal.h"

अटल व्योम rxrpc_dummy_notअगरy(काष्ठा sock *sk, काष्ठा rxrpc_call *call,
			       अचिन्हित दीर्घ user_call_ID)
अणु
पूर्ण

/*
 * Pपुनः_स्मृतिate a single service call, connection and peer and, अगर possible,
 * give them a user ID and attach the user's side of the ID to them.
 */
अटल पूर्णांक rxrpc_service_pपुनः_स्मृति_one(काष्ठा rxrpc_sock *rx,
				      काष्ठा rxrpc_backlog *b,
				      rxrpc_notअगरy_rx_t notअगरy_rx,
				      rxrpc_user_attach_call_t user_attach_call,
				      अचिन्हित दीर्घ user_call_ID, gfp_t gfp,
				      अचिन्हित पूर्णांक debug_id)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	काष्ठा rxrpc_call *call, *xcall;
	काष्ठा rxrpc_net *rxnet = rxrpc_net(sock_net(&rx->sk));
	काष्ठा rb_node *parent, **pp;
	पूर्णांक max, पंचांगp;
	अचिन्हित पूर्णांक size = RXRPC_BACKLOG_MAX;
	अचिन्हित पूर्णांक head, tail, call_head, call_tail;

	max = rx->sk.sk_max_ack_backlog;
	पंचांगp = rx->sk.sk_ack_backlog;
	अगर (पंचांगp >= max) अणु
		_leave(" = -ENOBUFS [full %u]", max);
		वापस -ENOBUFS;
	पूर्ण
	max -= पंचांगp;

	/* We करोn't need more conns and peers than we have calls, but on the
	 * other hand, we shouldn't ever use more peers than conns or conns
	 * than calls.
	 */
	call_head = b->call_backlog_head;
	call_tail = READ_ONCE(b->call_backlog_tail);
	पंचांगp = CIRC_CNT(call_head, call_tail, size);
	अगर (पंचांगp >= max) अणु
		_leave(" = -ENOBUFS [enough %u]", पंचांगp);
		वापस -ENOBUFS;
	पूर्ण
	max = पंचांगp + 1;

	head = b->peer_backlog_head;
	tail = READ_ONCE(b->peer_backlog_tail);
	अगर (CIRC_CNT(head, tail, size) < max) अणु
		काष्ठा rxrpc_peer *peer = rxrpc_alloc_peer(rx->local, gfp);
		अगर (!peer)
			वापस -ENOMEM;
		b->peer_backlog[head] = peer;
		smp_store_release(&b->peer_backlog_head,
				  (head + 1) & (size - 1));
	पूर्ण

	head = b->conn_backlog_head;
	tail = READ_ONCE(b->conn_backlog_tail);
	अगर (CIRC_CNT(head, tail, size) < max) अणु
		काष्ठा rxrpc_connection *conn;

		conn = rxrpc_pपुनः_स्मृति_service_connection(rxnet, gfp);
		अगर (!conn)
			वापस -ENOMEM;
		b->conn_backlog[head] = conn;
		smp_store_release(&b->conn_backlog_head,
				  (head + 1) & (size - 1));

		trace_rxrpc_conn(conn->debug_id, rxrpc_conn_new_service,
				 atomic_पढ़ो(&conn->usage), here);
	पूर्ण

	/* Now it माला_लो complicated, because calls get रेजिस्टरed with the
	 * socket here, with a user ID preasचिन्हित by the user.
	 */
	call = rxrpc_alloc_call(rx, gfp, debug_id);
	अगर (!call)
		वापस -ENOMEM;
	call->flags |= (1 << RXRPC_CALL_IS_SERVICE);
	call->state = RXRPC_CALL_SERVER_PREALLOC;

	trace_rxrpc_call(call->debug_id, rxrpc_call_new_service,
			 atomic_पढ़ो(&call->usage),
			 here, (स्थिर व्योम *)user_call_ID);

	ग_लिखो_lock(&rx->call_lock);

	/* Check the user ID isn't alपढ़ोy in use */
	pp = &rx->calls.rb_node;
	parent = शून्य;
	जबतक (*pp) अणु
		parent = *pp;
		xcall = rb_entry(parent, काष्ठा rxrpc_call, sock_node);
		अगर (user_call_ID < xcall->user_call_ID)
			pp = &(*pp)->rb_left;
		अन्यथा अगर (user_call_ID > xcall->user_call_ID)
			pp = &(*pp)->rb_right;
		अन्यथा
			जाओ id_in_use;
	पूर्ण

	call->user_call_ID = user_call_ID;
	call->notअगरy_rx = notअगरy_rx;
	अगर (user_attach_call) अणु
		rxrpc_get_call(call, rxrpc_call_got_kernel);
		user_attach_call(call, user_call_ID);
	पूर्ण

	rxrpc_get_call(call, rxrpc_call_got_userid);
	rb_link_node(&call->sock_node, parent, pp);
	rb_insert_color(&call->sock_node, &rx->calls);
	set_bit(RXRPC_CALL_HAS_USERID, &call->flags);

	list_add(&call->sock_link, &rx->sock_calls);

	ग_लिखो_unlock(&rx->call_lock);

	rxnet = call->rxnet;
	ग_लिखो_lock(&rxnet->call_lock);
	list_add_tail(&call->link, &rxnet->calls);
	ग_लिखो_unlock(&rxnet->call_lock);

	b->call_backlog[call_head] = call;
	smp_store_release(&b->call_backlog_head, (call_head + 1) & (size - 1));
	_leave(" = 0 [%d -> %lx]", call->debug_id, user_call_ID);
	वापस 0;

id_in_use:
	ग_लिखो_unlock(&rx->call_lock);
	rxrpc_cleanup_call(call);
	_leave(" = -EBADSLT");
	वापस -EBADSLT;
पूर्ण

/*
 * Allocate the pपुनः_स्मृतिation buffers क्रम incoming service calls.  These must
 * be अक्षरged manually.
 */
पूर्णांक rxrpc_service_pपुनः_स्मृति(काष्ठा rxrpc_sock *rx, gfp_t gfp)
अणु
	काष्ठा rxrpc_backlog *b = rx->backlog;

	अगर (!b) अणु
		b = kzalloc(माप(काष्ठा rxrpc_backlog), gfp);
		अगर (!b)
			वापस -ENOMEM;
		rx->backlog = b;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Discard the pपुनः_स्मृतिation on a service.
 */
व्योम rxrpc_discard_pपुनः_स्मृति(काष्ठा rxrpc_sock *rx)
अणु
	काष्ठा rxrpc_backlog *b = rx->backlog;
	काष्ठा rxrpc_net *rxnet = rxrpc_net(sock_net(&rx->sk));
	अचिन्हित पूर्णांक size = RXRPC_BACKLOG_MAX, head, tail;

	अगर (!b)
		वापस;
	rx->backlog = शून्य;

	/* Make sure that there aren't any incoming calls in progress beक्रमe we
	 * clear the pपुनः_स्मृतिation buffers.
	 */
	spin_lock_bh(&rx->incoming_lock);
	spin_unlock_bh(&rx->incoming_lock);

	head = b->peer_backlog_head;
	tail = b->peer_backlog_tail;
	जबतक (CIRC_CNT(head, tail, size) > 0) अणु
		काष्ठा rxrpc_peer *peer = b->peer_backlog[tail];
		rxrpc_put_local(peer->local);
		kमुक्त(peer);
		tail = (tail + 1) & (size - 1);
	पूर्ण

	head = b->conn_backlog_head;
	tail = b->conn_backlog_tail;
	जबतक (CIRC_CNT(head, tail, size) > 0) अणु
		काष्ठा rxrpc_connection *conn = b->conn_backlog[tail];
		ग_लिखो_lock(&rxnet->conn_lock);
		list_del(&conn->link);
		list_del(&conn->proc_link);
		ग_लिखो_unlock(&rxnet->conn_lock);
		kमुक्त(conn);
		अगर (atomic_dec_and_test(&rxnet->nr_conns))
			wake_up_var(&rxnet->nr_conns);
		tail = (tail + 1) & (size - 1);
	पूर्ण

	head = b->call_backlog_head;
	tail = b->call_backlog_tail;
	जबतक (CIRC_CNT(head, tail, size) > 0) अणु
		काष्ठा rxrpc_call *call = b->call_backlog[tail];
		rcu_assign_poपूर्णांकer(call->socket, rx);
		अगर (rx->discard_new_call) अणु
			_debug("discard %lx", call->user_call_ID);
			rx->discard_new_call(call, call->user_call_ID);
			अगर (call->notअगरy_rx)
				call->notअगरy_rx = rxrpc_dummy_notअगरy;
			rxrpc_put_call(call, rxrpc_call_put_kernel);
		पूर्ण
		rxrpc_call_completed(call);
		rxrpc_release_call(rx, call);
		rxrpc_put_call(call, rxrpc_call_put);
		tail = (tail + 1) & (size - 1);
	पूर्ण

	kमुक्त(b);
पूर्ण

/*
 * Ping the other end to fill our RTT cache and to retrieve the rwind
 * and MTU parameters.
 */
अटल व्योम rxrpc_send_ping(काष्ठा rxrpc_call *call, काष्ठा sk_buff *skb)
अणु
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	kसमय_प्रकार now = skb->tstamp;

	अगर (call->peer->rtt_count < 3 ||
	    kसमय_beक्रमe(kसमय_add_ms(call->peer->rtt_last_req, 1000), now))
		rxrpc_propose_ACK(call, RXRPC_ACK_PING, sp->hdr.serial,
				  true, true,
				  rxrpc_propose_ack_ping_क्रम_params);
पूर्ण

/*
 * Allocate a new incoming call from the pपुनः_स्मृति pool, aदीर्घ with a connection
 * and a peer as necessary.
 */
अटल काष्ठा rxrpc_call *rxrpc_alloc_incoming_call(काष्ठा rxrpc_sock *rx,
						    काष्ठा rxrpc_local *local,
						    काष्ठा rxrpc_peer *peer,
						    काष्ठा rxrpc_connection *conn,
						    स्थिर काष्ठा rxrpc_security *sec,
						    काष्ठा sk_buff *skb)
अणु
	काष्ठा rxrpc_backlog *b = rx->backlog;
	काष्ठा rxrpc_call *call;
	अचिन्हित लघु call_head, conn_head, peer_head;
	अचिन्हित लघु call_tail, conn_tail, peer_tail;
	अचिन्हित लघु call_count, conn_count;

	/* #calls >= #conns >= #peers must hold true. */
	call_head = smp_load_acquire(&b->call_backlog_head);
	call_tail = b->call_backlog_tail;
	call_count = CIRC_CNT(call_head, call_tail, RXRPC_BACKLOG_MAX);
	conn_head = smp_load_acquire(&b->conn_backlog_head);
	conn_tail = b->conn_backlog_tail;
	conn_count = CIRC_CNT(conn_head, conn_tail, RXRPC_BACKLOG_MAX);
	ASSERTCMP(conn_count, >=, call_count);
	peer_head = smp_load_acquire(&b->peer_backlog_head);
	peer_tail = b->peer_backlog_tail;
	ASSERTCMP(CIRC_CNT(peer_head, peer_tail, RXRPC_BACKLOG_MAX), >=,
		  conn_count);

	अगर (call_count == 0)
		वापस शून्य;

	अगर (!conn) अणु
		अगर (peer && !rxrpc_get_peer_maybe(peer))
			peer = शून्य;
		अगर (!peer) अणु
			peer = b->peer_backlog[peer_tail];
			अगर (rxrpc_extract_addr_from_skb(&peer->srx, skb) < 0)
				वापस शून्य;
			b->peer_backlog[peer_tail] = शून्य;
			smp_store_release(&b->peer_backlog_tail,
					  (peer_tail + 1) &
					  (RXRPC_BACKLOG_MAX - 1));

			rxrpc_new_incoming_peer(rx, local, peer);
		पूर्ण

		/* Now allocate and set up the connection */
		conn = b->conn_backlog[conn_tail];
		b->conn_backlog[conn_tail] = शून्य;
		smp_store_release(&b->conn_backlog_tail,
				  (conn_tail + 1) & (RXRPC_BACKLOG_MAX - 1));
		conn->params.local = rxrpc_get_local(local);
		conn->params.peer = peer;
		rxrpc_see_connection(conn);
		rxrpc_new_incoming_connection(rx, conn, sec, skb);
	पूर्ण अन्यथा अणु
		rxrpc_get_connection(conn);
	पूर्ण

	/* And now we can allocate and set up a new call */
	call = b->call_backlog[call_tail];
	b->call_backlog[call_tail] = शून्य;
	smp_store_release(&b->call_backlog_tail,
			  (call_tail + 1) & (RXRPC_BACKLOG_MAX - 1));

	rxrpc_see_call(call);
	call->conn = conn;
	call->security = conn->security;
	call->security_ix = conn->security_ix;
	call->peer = rxrpc_get_peer(conn->params.peer);
	call->cong_cwnd = call->peer->cong_cwnd;
	वापस call;
पूर्ण

/*
 * Set up a new incoming call.  Called in BH context with the RCU पढ़ो lock
 * held.
 *
 * If this is क्रम a kernel service, when we allocate the call, it will have
 * three refs on it: (1) the kernel service, (2) the user_call_ID tree, (3) the
 * retainer ref obtained from the backlog buffer.  Pपुनः_स्मृति calls क्रम userspace
 * services only have the ref from the backlog buffer.  We want to pass this
 * ref to non-BH context to dispose of.
 *
 * If we want to report an error, we mark the skb with the packet type and
 * पात code and वापस शून्य.
 *
 * The call is वापसed with the user access mutex held.
 */
काष्ठा rxrpc_call *rxrpc_new_incoming_call(काष्ठा rxrpc_local *local,
					   काष्ठा rxrpc_sock *rx,
					   काष्ठा sk_buff *skb)
अणु
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	स्थिर काष्ठा rxrpc_security *sec = शून्य;
	काष्ठा rxrpc_connection *conn;
	काष्ठा rxrpc_peer *peer = शून्य;
	काष्ठा rxrpc_call *call = शून्य;

	_enter("");

	spin_lock(&rx->incoming_lock);
	अगर (rx->sk.sk_state == RXRPC_SERVER_LISTEN_DISABLED ||
	    rx->sk.sk_state == RXRPC_CLOSE) अणु
		trace_rxrpc_पात(0, "CLS", sp->hdr.cid, sp->hdr.callNumber,
				  sp->hdr.seq, RX_INVALID_OPERATION, ESHUTDOWN);
		skb->mark = RXRPC_SKB_MARK_REJECT_ABORT;
		skb->priority = RX_INVALID_OPERATION;
		जाओ no_call;
	पूर्ण

	/* The peer, connection and call may all have sprung पूर्णांकo existence due
	 * to a duplicate packet being handled on another CPU in parallel, so
	 * we have to recheck the routing.  However, we're now holding
	 * rx->incoming_lock, so the values should reमुख्य stable.
	 */
	conn = rxrpc_find_connection_rcu(local, skb, &peer);

	अगर (!conn) अणु
		sec = rxrpc_get_incoming_security(rx, skb);
		अगर (!sec)
			जाओ no_call;
	पूर्ण

	call = rxrpc_alloc_incoming_call(rx, local, peer, conn, sec, skb);
	अगर (!call) अणु
		skb->mark = RXRPC_SKB_MARK_REJECT_BUSY;
		जाओ no_call;
	पूर्ण

	trace_rxrpc_receive(call, rxrpc_receive_incoming,
			    sp->hdr.serial, sp->hdr.seq);

	/* Make the call live. */
	rxrpc_incoming_call(rx, call, skb);
	conn = call->conn;

	अगर (rx->notअगरy_new_call)
		rx->notअगरy_new_call(&rx->sk, call, call->user_call_ID);

	spin_lock(&conn->state_lock);
	चयन (conn->state) अणु
	हाल RXRPC_CONN_SERVICE_UNSECURED:
		conn->state = RXRPC_CONN_SERVICE_CHALLENGING;
		set_bit(RXRPC_CONN_EV_CHALLENGE, &call->conn->events);
		rxrpc_queue_conn(call->conn);
		अवरोध;

	हाल RXRPC_CONN_SERVICE:
		ग_लिखो_lock(&call->state_lock);
		अगर (call->state < RXRPC_CALL_COMPLETE)
			call->state = RXRPC_CALL_SERVER_RECV_REQUEST;
		ग_लिखो_unlock(&call->state_lock);
		अवरोध;

	हाल RXRPC_CONN_REMOTELY_ABORTED:
		rxrpc_set_call_completion(call, RXRPC_CALL_REMOTELY_ABORTED,
					  conn->पात_code, conn->error);
		अवरोध;
	हाल RXRPC_CONN_LOCALLY_ABORTED:
		rxrpc_पात_call("CON", call, sp->hdr.seq,
				 conn->पात_code, conn->error);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	spin_unlock(&conn->state_lock);
	spin_unlock(&rx->incoming_lock);

	rxrpc_send_ping(call, skb);

	/* We have to discard the pपुनः_स्मृति queue's ref here and rely on a
	 * combination of the RCU पढ़ो lock and refs held either by the socket
	 * (recvmsg queue, to-be-accepted queue or user ID tree) or the kernel
	 * service to prevent the call from being deallocated too early.
	 */
	rxrpc_put_call(call, rxrpc_call_put);

	_leave(" = %p{%d}", call, call->debug_id);
	वापस call;

no_call:
	spin_unlock(&rx->incoming_lock);
	_leave(" = NULL [%u]", skb->mark);
	वापस शून्य;
पूर्ण

/*
 * Charge up socket with pपुनः_स्मृतिated calls, attaching user call IDs.
 */
पूर्णांक rxrpc_user_अक्षरge_accept(काष्ठा rxrpc_sock *rx, अचिन्हित दीर्घ user_call_ID)
अणु
	काष्ठा rxrpc_backlog *b = rx->backlog;

	अगर (rx->sk.sk_state == RXRPC_CLOSE)
		वापस -ESHUTDOWN;

	वापस rxrpc_service_pपुनः_स्मृति_one(rx, b, शून्य, शून्य, user_call_ID,
					  GFP_KERNEL,
					  atomic_inc_वापस(&rxrpc_debug_id));
पूर्ण

/*
 * rxrpc_kernel_अक्षरge_accept - Charge up socket with pपुनः_स्मृतिated calls
 * @sock: The socket on which to pपुनः_स्मृतिate
 * @notअगरy_rx: Event notअगरication function क्रम the call
 * @user_attach_call: Func to attach call to user_call_ID
 * @user_call_ID: The tag to attach to the pपुनः_स्मृतिated call
 * @gfp: The allocation conditions.
 * @debug_id: The tracing debug ID.
 *
 * Charge up the socket with pपुनः_स्मृतिated calls, each with a user ID.  A
 * function should be provided to effect the attachment from the user's side.
 * The user is given a ref to hold on the call.
 *
 * Note that the call may be come connected beक्रमe this function वापसs.
 */
पूर्णांक rxrpc_kernel_अक्षरge_accept(काष्ठा socket *sock,
			       rxrpc_notअगरy_rx_t notअगरy_rx,
			       rxrpc_user_attach_call_t user_attach_call,
			       अचिन्हित दीर्घ user_call_ID, gfp_t gfp,
			       अचिन्हित पूर्णांक debug_id)
अणु
	काष्ठा rxrpc_sock *rx = rxrpc_sk(sock->sk);
	काष्ठा rxrpc_backlog *b = rx->backlog;

	अगर (sock->sk->sk_state == RXRPC_CLOSE)
		वापस -ESHUTDOWN;

	वापस rxrpc_service_pपुनः_स्मृति_one(rx, b, notअगरy_rx,
					  user_attach_call, user_call_ID,
					  gfp, debug_id);
पूर्ण
EXPORT_SYMBOL(rxrpc_kernel_अक्षरge_accept);
