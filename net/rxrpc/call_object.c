<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* RxRPC inभागidual remote procedure call handling
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/spinlock_types.h>
#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश "ar-internal.h"

स्थिर अक्षर *स्थिर rxrpc_call_states[NR__RXRPC_CALL_STATES] = अणु
	[RXRPC_CALL_UNINITIALISED]		= "Uninit  ",
	[RXRPC_CALL_CLIENT_AWAIT_CONN]		= "ClWtConn",
	[RXRPC_CALL_CLIENT_SEND_REQUEST]	= "ClSndReq",
	[RXRPC_CALL_CLIENT_AWAIT_REPLY]		= "ClAwtRpl",
	[RXRPC_CALL_CLIENT_RECV_REPLY]		= "ClRcvRpl",
	[RXRPC_CALL_SERVER_PREALLOC]		= "SvPrealc",
	[RXRPC_CALL_SERVER_SECURING]		= "SvSecure",
	[RXRPC_CALL_SERVER_RECV_REQUEST]	= "SvRcvReq",
	[RXRPC_CALL_SERVER_ACK_REQUEST]		= "SvAckReq",
	[RXRPC_CALL_SERVER_SEND_REPLY]		= "SvSndRpl",
	[RXRPC_CALL_SERVER_AWAIT_ACK]		= "SvAwtACK",
	[RXRPC_CALL_COMPLETE]			= "Complete",
पूर्ण;

स्थिर अक्षर *स्थिर rxrpc_call_completions[NR__RXRPC_CALL_COMPLETIONS] = अणु
	[RXRPC_CALL_SUCCEEDED]			= "Complete",
	[RXRPC_CALL_REMOTELY_ABORTED]		= "RmtAbort",
	[RXRPC_CALL_LOCALLY_ABORTED]		= "LocAbort",
	[RXRPC_CALL_LOCAL_ERROR]		= "LocError",
	[RXRPC_CALL_NETWORK_ERROR]		= "NetError",
पूर्ण;

काष्ठा kmem_cache *rxrpc_call_jar;

अटल काष्ठा semaphore rxrpc_call_limiter =
	__SEMAPHORE_INITIALIZER(rxrpc_call_limiter, 1000);
अटल काष्ठा semaphore rxrpc_kernel_call_limiter =
	__SEMAPHORE_INITIALIZER(rxrpc_kernel_call_limiter, 1000);

अटल व्योम rxrpc_call_समयr_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा rxrpc_call *call = from_समयr(call, t, समयr);

	_enter("%d", call->debug_id);

	अगर (call->state < RXRPC_CALL_COMPLETE) अणु
		trace_rxrpc_समयr(call, rxrpc_समयr_expired, jअगरfies);
		rxrpc_queue_call(call);
	पूर्ण
पूर्ण

अटल काष्ठा lock_class_key rxrpc_call_user_mutex_lock_class_key;

/*
 * find an extant server call
 * - called in process context with IRQs enabled
 */
काष्ठा rxrpc_call *rxrpc_find_call_by_user_ID(काष्ठा rxrpc_sock *rx,
					      अचिन्हित दीर्घ user_call_ID)
अणु
	काष्ठा rxrpc_call *call;
	काष्ठा rb_node *p;

	_enter("%p,%lx", rx, user_call_ID);

	पढ़ो_lock(&rx->call_lock);

	p = rx->calls.rb_node;
	जबतक (p) अणु
		call = rb_entry(p, काष्ठा rxrpc_call, sock_node);

		अगर (user_call_ID < call->user_call_ID)
			p = p->rb_left;
		अन्यथा अगर (user_call_ID > call->user_call_ID)
			p = p->rb_right;
		अन्यथा
			जाओ found_extant_call;
	पूर्ण

	पढ़ो_unlock(&rx->call_lock);
	_leave(" = NULL");
	वापस शून्य;

found_extant_call:
	rxrpc_get_call(call, rxrpc_call_got);
	पढ़ो_unlock(&rx->call_lock);
	_leave(" = %p [%d]", call, atomic_पढ़ो(&call->usage));
	वापस call;
पूर्ण

/*
 * allocate a new call
 */
काष्ठा rxrpc_call *rxrpc_alloc_call(काष्ठा rxrpc_sock *rx, gfp_t gfp,
				    अचिन्हित पूर्णांक debug_id)
अणु
	काष्ठा rxrpc_call *call;
	काष्ठा rxrpc_net *rxnet = rxrpc_net(sock_net(&rx->sk));

	call = kmem_cache_zalloc(rxrpc_call_jar, gfp);
	अगर (!call)
		वापस शून्य;

	call->rxtx_buffer = kसुस्मृति(RXRPC_RXTX_BUFF_SIZE,
				    माप(काष्ठा sk_buff *),
				    gfp);
	अगर (!call->rxtx_buffer)
		जाओ nomem;

	call->rxtx_annotations = kसुस्मृति(RXRPC_RXTX_BUFF_SIZE, माप(u8), gfp);
	अगर (!call->rxtx_annotations)
		जाओ nomem_2;

	mutex_init(&call->user_mutex);

	/* Prevent lockdep reporting a deadlock false positive between the afs
	 * fileप्रणाली and sys_sendmsg() via the mmap sem.
	 */
	अगर (rx->sk.sk_kern_sock)
		lockdep_set_class(&call->user_mutex,
				  &rxrpc_call_user_mutex_lock_class_key);

	समयr_setup(&call->समयr, rxrpc_call_समयr_expired, 0);
	INIT_WORK(&call->processor, &rxrpc_process_call);
	INIT_LIST_HEAD(&call->link);
	INIT_LIST_HEAD(&call->chan_रुको_link);
	INIT_LIST_HEAD(&call->accept_link);
	INIT_LIST_HEAD(&call->recvmsg_link);
	INIT_LIST_HEAD(&call->sock_link);
	init_रुकोqueue_head(&call->रुकोq);
	spin_lock_init(&call->lock);
	spin_lock_init(&call->notअगरy_lock);
	spin_lock_init(&call->input_lock);
	rwlock_init(&call->state_lock);
	atomic_set(&call->usage, 1);
	call->debug_id = debug_id;
	call->tx_total_len = -1;
	call->next_rx_timo = 20 * HZ;
	call->next_req_timo = 1 * HZ;

	स_रखो(&call->sock_node, 0xed, माप(call->sock_node));

	/* Leave space in the ring to handle a maxed-out jumbo packet */
	call->rx_winsize = rxrpc_rx_winकरोw_size;
	call->tx_winsize = 16;
	call->rx_expect_next = 1;

	call->cong_cwnd = 2;
	call->cong_ssthresh = RXRPC_RXTX_BUFF_SIZE - 1;

	call->rxnet = rxnet;
	call->rtt_avail = RXRPC_CALL_RTT_AVAIL_MASK;
	atomic_inc(&rxnet->nr_calls);
	वापस call;

nomem_2:
	kमुक्त(call->rxtx_buffer);
nomem:
	kmem_cache_मुक्त(rxrpc_call_jar, call);
	वापस शून्य;
पूर्ण

/*
 * Allocate a new client call.
 */
अटल काष्ठा rxrpc_call *rxrpc_alloc_client_call(काष्ठा rxrpc_sock *rx,
						  काष्ठा sockaddr_rxrpc *srx,
						  gfp_t gfp,
						  अचिन्हित पूर्णांक debug_id)
अणु
	काष्ठा rxrpc_call *call;
	kसमय_प्रकार now;

	_enter("");

	call = rxrpc_alloc_call(rx, gfp, debug_id);
	अगर (!call)
		वापस ERR_PTR(-ENOMEM);
	call->state = RXRPC_CALL_CLIENT_AWAIT_CONN;
	call->service_id = srx->srx_service;
	call->tx_phase = true;
	now = kसमय_get_real();
	call->acks_latest_ts = now;
	call->cong_tstamp = now;

	_leave(" = %p", call);
	वापस call;
पूर्ण

/*
 * Initiate the call ack/resend/expiry समयr.
 */
अटल व्योम rxrpc_start_call_समयr(काष्ठा rxrpc_call *call)
अणु
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ j = now + MAX_JIFFY_OFFSET;

	call->ack_at = j;
	call->ack_lost_at = j;
	call->resend_at = j;
	call->ping_at = j;
	call->expect_rx_by = j;
	call->expect_req_by = j;
	call->expect_term_by = j;
	call->समयr.expires = now;
पूर्ण

/*
 * Wait क्रम a call slot to become available.
 */
अटल काष्ठा semaphore *rxrpc_get_call_slot(काष्ठा rxrpc_call_params *p, gfp_t gfp)
अणु
	काष्ठा semaphore *limiter = &rxrpc_call_limiter;

	अगर (p->kernel)
		limiter = &rxrpc_kernel_call_limiter;
	अगर (p->पूर्णांकerruptibility == RXRPC_UNINTERRUPTIBLE) अणु
		करोwn(limiter);
		वापस limiter;
	पूर्ण
	वापस करोwn_पूर्णांकerruptible(limiter) < 0 ? शून्य : limiter;
पूर्ण

/*
 * Release a call slot.
 */
अटल व्योम rxrpc_put_call_slot(काष्ठा rxrpc_call *call)
अणु
	काष्ठा semaphore *limiter = &rxrpc_call_limiter;

	अगर (test_bit(RXRPC_CALL_KERNEL, &call->flags))
		limiter = &rxrpc_kernel_call_limiter;
	up(limiter);
पूर्ण

/*
 * Set up a call क्रम the given parameters.
 * - Called with the socket lock held, which it must release.
 * - If it वापसs a call, the call's lock will need releasing by the caller.
 */
काष्ठा rxrpc_call *rxrpc_new_client_call(काष्ठा rxrpc_sock *rx,
					 काष्ठा rxrpc_conn_parameters *cp,
					 काष्ठा sockaddr_rxrpc *srx,
					 काष्ठा rxrpc_call_params *p,
					 gfp_t gfp,
					 अचिन्हित पूर्णांक debug_id)
	__releases(&rx->sk.sk_lock.slock)
	__acquires(&call->user_mutex)
अणु
	काष्ठा rxrpc_call *call, *xcall;
	काष्ठा rxrpc_net *rxnet;
	काष्ठा semaphore *limiter;
	काष्ठा rb_node *parent, **pp;
	स्थिर व्योम *here = __builtin_वापस_address(0);
	पूर्णांक ret;

	_enter("%p,%lx", rx, p->user_call_ID);

	limiter = rxrpc_get_call_slot(p, gfp);
	अगर (!limiter)
		वापस ERR_PTR(-ERESTARTSYS);

	call = rxrpc_alloc_client_call(rx, srx, gfp, debug_id);
	अगर (IS_ERR(call)) अणु
		release_sock(&rx->sk);
		up(limiter);
		_leave(" = %ld", PTR_ERR(call));
		वापस call;
	पूर्ण

	call->पूर्णांकerruptibility = p->पूर्णांकerruptibility;
	call->tx_total_len = p->tx_total_len;
	trace_rxrpc_call(call->debug_id, rxrpc_call_new_client,
			 atomic_पढ़ो(&call->usage),
			 here, (स्थिर व्योम *)p->user_call_ID);
	अगर (p->kernel)
		__set_bit(RXRPC_CALL_KERNEL, &call->flags);

	/* We need to protect a partially set up call against the user as we
	 * will be acting outside the socket lock.
	 */
	mutex_lock(&call->user_mutex);

	/* Publish the call, even though it is incompletely set up as yet */
	ग_लिखो_lock(&rx->call_lock);

	pp = &rx->calls.rb_node;
	parent = शून्य;
	जबतक (*pp) अणु
		parent = *pp;
		xcall = rb_entry(parent, काष्ठा rxrpc_call, sock_node);

		अगर (p->user_call_ID < xcall->user_call_ID)
			pp = &(*pp)->rb_left;
		अन्यथा अगर (p->user_call_ID > xcall->user_call_ID)
			pp = &(*pp)->rb_right;
		अन्यथा
			जाओ error_dup_user_ID;
	पूर्ण

	rcu_assign_poपूर्णांकer(call->socket, rx);
	call->user_call_ID = p->user_call_ID;
	__set_bit(RXRPC_CALL_HAS_USERID, &call->flags);
	rxrpc_get_call(call, rxrpc_call_got_userid);
	rb_link_node(&call->sock_node, parent, pp);
	rb_insert_color(&call->sock_node, &rx->calls);
	list_add(&call->sock_link, &rx->sock_calls);

	ग_लिखो_unlock(&rx->call_lock);

	rxnet = call->rxnet;
	ग_लिखो_lock(&rxnet->call_lock);
	list_add_tail(&call->link, &rxnet->calls);
	ग_लिखो_unlock(&rxnet->call_lock);

	/* From this poपूर्णांक on, the call is रक्षित by its own lock. */
	release_sock(&rx->sk);

	/* Set up or get a connection record and set the protocol parameters,
	 * including channel number and call ID.
	 */
	ret = rxrpc_connect_call(rx, call, cp, srx, gfp);
	अगर (ret < 0)
		जाओ error_attached_to_socket;

	trace_rxrpc_call(call->debug_id, rxrpc_call_connected,
			 atomic_पढ़ो(&call->usage), here, शून्य);

	rxrpc_start_call_समयr(call);

	_net("CALL new %d on CONN %d", call->debug_id, call->conn->debug_id);

	_leave(" = %p [new]", call);
	वापस call;

	/* We unexpectedly found the user ID in the list after taking
	 * the call_lock.  This shouldn't happen unless the user races
	 * with itself and tries to add the same user ID twice at the
	 * same समय in dअगरferent thपढ़ोs.
	 */
error_dup_user_ID:
	ग_लिखो_unlock(&rx->call_lock);
	release_sock(&rx->sk);
	__rxrpc_set_call_completion(call, RXRPC_CALL_LOCAL_ERROR,
				    RX_CALL_DEAD, -EEXIST);
	trace_rxrpc_call(call->debug_id, rxrpc_call_error,
			 atomic_पढ़ो(&call->usage), here, ERR_PTR(-EEXIST));
	rxrpc_release_call(rx, call);
	mutex_unlock(&call->user_mutex);
	rxrpc_put_call(call, rxrpc_call_put);
	_leave(" = -EEXIST");
	वापस ERR_PTR(-EEXIST);

	/* We got an error, but the call is attached to the socket and is in
	 * need of release.  However, we might now race with recvmsg() when
	 * completing the call queues it.  Return 0 from sys_sendmsg() and
	 * leave the error to recvmsg() to deal with.
	 */
error_attached_to_socket:
	trace_rxrpc_call(call->debug_id, rxrpc_call_error,
			 atomic_पढ़ो(&call->usage), here, ERR_PTR(ret));
	set_bit(RXRPC_CALL_DISCONNECTED, &call->flags);
	__rxrpc_set_call_completion(call, RXRPC_CALL_LOCAL_ERROR,
				    RX_CALL_DEAD, ret);
	_leave(" = c=%08x [err]", call->debug_id);
	वापस call;
पूर्ण

/*
 * Set up an incoming call.  call->conn poपूर्णांकs to the connection.
 * This is called in BH context and isn't allowed to fail.
 */
व्योम rxrpc_incoming_call(काष्ठा rxrpc_sock *rx,
			 काष्ठा rxrpc_call *call,
			 काष्ठा sk_buff *skb)
अणु
	काष्ठा rxrpc_connection *conn = call->conn;
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	u32 chan;

	_enter(",%d", call->conn->debug_id);

	rcu_assign_poपूर्णांकer(call->socket, rx);
	call->call_id		= sp->hdr.callNumber;
	call->service_id	= sp->hdr.serviceId;
	call->cid		= sp->hdr.cid;
	call->state		= RXRPC_CALL_SERVER_SECURING;
	call->cong_tstamp	= skb->tstamp;

	/* Set the channel क्रम this call.  We करोn't get channel_lock as we're
	 * only defending against the data_पढ़ोy handler (which we're called
	 * from) and the RESPONSE packet parser (which is only really
	 * पूर्णांकerested in call_counter and can cope with a disagreement with the
	 * call poपूर्णांकer).
	 */
	chan = sp->hdr.cid & RXRPC_CHANNELMASK;
	conn->channels[chan].call_counter = call->call_id;
	conn->channels[chan].call_id = call->call_id;
	rcu_assign_poपूर्णांकer(conn->channels[chan].call, call);

	spin_lock(&conn->params.peer->lock);
	hlist_add_head_rcu(&call->error_link, &conn->params.peer->error_tarमाला_लो);
	spin_unlock(&conn->params.peer->lock);

	_net("CALL incoming %d on CONN %d", call->debug_id, call->conn->debug_id);

	rxrpc_start_call_समयr(call);
	_leave("");
पूर्ण

/*
 * Queue a call's work processor, getting a ref to pass to the work queue.
 */
bool rxrpc_queue_call(काष्ठा rxrpc_call *call)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	पूर्णांक n = atomic_fetch_add_unless(&call->usage, 1, 0);
	अगर (n == 0)
		वापस false;
	अगर (rxrpc_queue_work(&call->processor))
		trace_rxrpc_call(call->debug_id, rxrpc_call_queued, n + 1,
				 here, शून्य);
	अन्यथा
		rxrpc_put_call(call, rxrpc_call_put_noqueue);
	वापस true;
पूर्ण

/*
 * Queue a call's work processor, passing the callers ref to the work queue.
 */
bool __rxrpc_queue_call(काष्ठा rxrpc_call *call)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	पूर्णांक n = atomic_पढ़ो(&call->usage);
	ASSERTCMP(n, >=, 1);
	अगर (rxrpc_queue_work(&call->processor))
		trace_rxrpc_call(call->debug_id, rxrpc_call_queued_ref, n,
				 here, शून्य);
	अन्यथा
		rxrpc_put_call(call, rxrpc_call_put_noqueue);
	वापस true;
पूर्ण

/*
 * Note the re-emergence of a call.
 */
व्योम rxrpc_see_call(काष्ठा rxrpc_call *call)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	अगर (call) अणु
		पूर्णांक n = atomic_पढ़ो(&call->usage);

		trace_rxrpc_call(call->debug_id, rxrpc_call_seen, n,
				 here, शून्य);
	पूर्ण
पूर्ण

/*
 * Note the addition of a ref on a call.
 */
व्योम rxrpc_get_call(काष्ठा rxrpc_call *call, क्रमागत rxrpc_call_trace op)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	पूर्णांक n = atomic_inc_वापस(&call->usage);

	trace_rxrpc_call(call->debug_id, op, n, here, शून्य);
पूर्ण

/*
 * Clean up the RxTx skb ring.
 */
अटल व्योम rxrpc_cleanup_ring(काष्ठा rxrpc_call *call)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RXRPC_RXTX_BUFF_SIZE; i++) अणु
		rxrpc_मुक्त_skb(call->rxtx_buffer[i], rxrpc_skb_cleaned);
		call->rxtx_buffer[i] = शून्य;
	पूर्ण
पूर्ण

/*
 * Detach a call from its owning socket.
 */
व्योम rxrpc_release_call(काष्ठा rxrpc_sock *rx, काष्ठा rxrpc_call *call)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	काष्ठा rxrpc_connection *conn = call->conn;
	bool put = false;

	_enter("{%d,%d}", call->debug_id, atomic_पढ़ो(&call->usage));

	trace_rxrpc_call(call->debug_id, rxrpc_call_release,
			 atomic_पढ़ो(&call->usage),
			 here, (स्थिर व्योम *)call->flags);

	ASSERTCMP(call->state, ==, RXRPC_CALL_COMPLETE);

	spin_lock_bh(&call->lock);
	अगर (test_and_set_bit(RXRPC_CALL_RELEASED, &call->flags))
		BUG();
	spin_unlock_bh(&call->lock);

	rxrpc_put_call_slot(call);

	del_समयr_sync(&call->समयr);

	/* Make sure we करोn't get any more notअगरications */
	ग_लिखो_lock_bh(&rx->recvmsg_lock);

	अगर (!list_empty(&call->recvmsg_link)) अणु
		_debug("unlinking once-pending call %p { e=%lx f=%lx }",
		       call, call->events, call->flags);
		list_del(&call->recvmsg_link);
		put = true;
	पूर्ण

	/* list_empty() must वापस false in rxrpc_notअगरy_socket() */
	call->recvmsg_link.next = शून्य;
	call->recvmsg_link.prev = शून्य;

	ग_लिखो_unlock_bh(&rx->recvmsg_lock);
	अगर (put)
		rxrpc_put_call(call, rxrpc_call_put);

	ग_लिखो_lock(&rx->call_lock);

	अगर (test_and_clear_bit(RXRPC_CALL_HAS_USERID, &call->flags)) अणु
		rb_erase(&call->sock_node, &rx->calls);
		स_रखो(&call->sock_node, 0xdd, माप(call->sock_node));
		rxrpc_put_call(call, rxrpc_call_put_userid);
	पूर्ण

	list_del(&call->sock_link);
	ग_लिखो_unlock(&rx->call_lock);

	_debug("RELEASE CALL %p (%d CONN %p)", call, call->debug_id, conn);

	अगर (conn && !test_bit(RXRPC_CALL_DISCONNECTED, &call->flags))
		rxrpc_disconnect_call(call);
	अगर (call->security)
		call->security->मुक्त_call_crypto(call);
	_leave("");
पूर्ण

/*
 * release all the calls associated with a socket
 */
व्योम rxrpc_release_calls_on_socket(काष्ठा rxrpc_sock *rx)
अणु
	काष्ठा rxrpc_call *call;

	_enter("%p", rx);

	जबतक (!list_empty(&rx->to_be_accepted)) अणु
		call = list_entry(rx->to_be_accepted.next,
				  काष्ठा rxrpc_call, accept_link);
		list_del(&call->accept_link);
		rxrpc_पात_call("SKR", call, 0, RX_CALL_DEAD, -ECONNRESET);
		rxrpc_put_call(call, rxrpc_call_put);
	पूर्ण

	जबतक (!list_empty(&rx->sock_calls)) अणु
		call = list_entry(rx->sock_calls.next,
				  काष्ठा rxrpc_call, sock_link);
		rxrpc_get_call(call, rxrpc_call_got);
		rxrpc_पात_call("SKT", call, 0, RX_CALL_DEAD, -ECONNRESET);
		rxrpc_send_पात_packet(call);
		rxrpc_release_call(rx, call);
		rxrpc_put_call(call, rxrpc_call_put);
	पूर्ण

	_leave("");
पूर्ण

/*
 * release a call
 */
व्योम rxrpc_put_call(काष्ठा rxrpc_call *call, क्रमागत rxrpc_call_trace op)
अणु
	काष्ठा rxrpc_net *rxnet = call->rxnet;
	स्थिर व्योम *here = __builtin_वापस_address(0);
	अचिन्हित पूर्णांक debug_id = call->debug_id;
	पूर्णांक n;

	ASSERT(call != शून्य);

	n = atomic_dec_वापस(&call->usage);
	trace_rxrpc_call(debug_id, op, n, here, शून्य);
	ASSERTCMP(n, >=, 0);
	अगर (n == 0) अणु
		_debug("call %d dead", call->debug_id);
		ASSERTCMP(call->state, ==, RXRPC_CALL_COMPLETE);

		अगर (!list_empty(&call->link)) अणु
			ग_लिखो_lock(&rxnet->call_lock);
			list_del_init(&call->link);
			ग_लिखो_unlock(&rxnet->call_lock);
		पूर्ण

		rxrpc_cleanup_call(call);
	पूर्ण
पूर्ण

/*
 * Final call deकाष्ठाion - but must be करोne in process context.
 */
अटल व्योम rxrpc_destroy_call(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rxrpc_call *call = container_of(work, काष्ठा rxrpc_call, processor);
	काष्ठा rxrpc_net *rxnet = call->rxnet;

	rxrpc_put_connection(call->conn);
	rxrpc_put_peer(call->peer);
	kमुक्त(call->rxtx_buffer);
	kमुक्त(call->rxtx_annotations);
	kmem_cache_मुक्त(rxrpc_call_jar, call);
	अगर (atomic_dec_and_test(&rxnet->nr_calls))
		wake_up_var(&rxnet->nr_calls);
पूर्ण

/*
 * Final call deकाष्ठाion under RCU.
 */
अटल व्योम rxrpc_rcu_destroy_call(काष्ठा rcu_head *rcu)
अणु
	काष्ठा rxrpc_call *call = container_of(rcu, काष्ठा rxrpc_call, rcu);

	अगर (in_softirq()) अणु
		INIT_WORK(&call->processor, rxrpc_destroy_call);
		अगर (!rxrpc_queue_work(&call->processor))
			BUG();
	पूर्ण अन्यथा अणु
		rxrpc_destroy_call(&call->processor);
	पूर्ण
पूर्ण

/*
 * clean up a call
 */
व्योम rxrpc_cleanup_call(काष्ठा rxrpc_call *call)
अणु
	_net("DESTROY CALL %d", call->debug_id);

	स_रखो(&call->sock_node, 0xcd, माप(call->sock_node));

	del_समयr_sync(&call->समयr);

	ASSERTCMP(call->state, ==, RXRPC_CALL_COMPLETE);
	ASSERT(test_bit(RXRPC_CALL_RELEASED, &call->flags));

	rxrpc_cleanup_ring(call);
	rxrpc_मुक्त_skb(call->tx_pending, rxrpc_skb_cleaned);

	call_rcu(&call->rcu, rxrpc_rcu_destroy_call);
पूर्ण

/*
 * Make sure that all calls are gone from a network namespace.  To reach this
 * poपूर्णांक, any खोलो UDP sockets in that namespace must have been बंदd, so any
 * outstanding calls cannot be करोing I/O.
 */
व्योम rxrpc_destroy_all_calls(काष्ठा rxrpc_net *rxnet)
अणु
	काष्ठा rxrpc_call *call;

	_enter("");

	अगर (!list_empty(&rxnet->calls)) अणु
		ग_लिखो_lock(&rxnet->call_lock);

		जबतक (!list_empty(&rxnet->calls)) अणु
			call = list_entry(rxnet->calls.next,
					  काष्ठा rxrpc_call, link);
			_debug("Zapping call %p", call);

			rxrpc_see_call(call);
			list_del_init(&call->link);

			pr_err("Call %p still in use (%d,%s,%lx,%lx)!\n",
			       call, atomic_पढ़ो(&call->usage),
			       rxrpc_call_states[call->state],
			       call->flags, call->events);

			ग_लिखो_unlock(&rxnet->call_lock);
			cond_resched();
			ग_लिखो_lock(&rxnet->call_lock);
		पूर्ण

		ग_लिखो_unlock(&rxnet->call_lock);
	पूर्ण

	atomic_dec(&rxnet->nr_calls);
	रुको_var_event(&rxnet->nr_calls, !atomic_पढ़ो(&rxnet->nr_calls));
पूर्ण
