<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* RxRPC भव connection handler, common bits.
 *
 * Copyright (C) 2007, 2016 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश "ar-internal.h"

/*
 * Time till a connection expires after last use (in seconds).
 */
अचिन्हित पूर्णांक __पढ़ो_mostly rxrpc_connection_expiry = 10 * 60;
अचिन्हित पूर्णांक __पढ़ो_mostly rxrpc_बंदd_conn_expiry = 10;

अटल व्योम rxrpc_destroy_connection(काष्ठा rcu_head *);

अटल व्योम rxrpc_connection_समयr(काष्ठा समयr_list *समयr)
अणु
	काष्ठा rxrpc_connection *conn =
		container_of(समयr, काष्ठा rxrpc_connection, समयr);

	rxrpc_queue_conn(conn);
पूर्ण

/*
 * allocate a new connection
 */
काष्ठा rxrpc_connection *rxrpc_alloc_connection(gfp_t gfp)
अणु
	काष्ठा rxrpc_connection *conn;

	_enter("");

	conn = kzalloc(माप(काष्ठा rxrpc_connection), gfp);
	अगर (conn) अणु
		INIT_LIST_HEAD(&conn->cache_link);
		समयr_setup(&conn->समयr, &rxrpc_connection_समयr, 0);
		INIT_WORK(&conn->processor, &rxrpc_process_connection);
		INIT_LIST_HEAD(&conn->proc_link);
		INIT_LIST_HEAD(&conn->link);
		skb_queue_head_init(&conn->rx_queue);
		conn->security = &rxrpc_no_security;
		spin_lock_init(&conn->state_lock);
		conn->debug_id = atomic_inc_वापस(&rxrpc_debug_id);
		conn->idle_बारtamp = jअगरfies;
	पूर्ण

	_leave(" = %p{%d}", conn, conn ? conn->debug_id : 0);
	वापस conn;
पूर्ण

/*
 * Look up a connection in the cache by protocol parameters.
 *
 * If successful, a poपूर्णांकer to the connection is वापसed, but no ref is taken.
 * शून्य is वापसed अगर there is no match.
 *
 * When searching क्रम a service call, अगर we find a peer but no connection, we
 * वापस that through *_peer in हाल we need to create a new service call.
 *
 * The caller must be holding the RCU पढ़ो lock.
 */
काष्ठा rxrpc_connection *rxrpc_find_connection_rcu(काष्ठा rxrpc_local *local,
						   काष्ठा sk_buff *skb,
						   काष्ठा rxrpc_peer **_peer)
अणु
	काष्ठा rxrpc_connection *conn;
	काष्ठा rxrpc_conn_proto k;
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	काष्ठा sockaddr_rxrpc srx;
	काष्ठा rxrpc_peer *peer;

	_enter(",%x", sp->hdr.cid & RXRPC_CIDMASK);

	अगर (rxrpc_extract_addr_from_skb(&srx, skb) < 0)
		जाओ not_found;

	अगर (srx.transport.family != local->srx.transport.family &&
	    (srx.transport.family == AF_INET &&
	     local->srx.transport.family != AF_INET6)) अणु
		pr_warn_ratelimited("AF_RXRPC: Protocol mismatch %u not %u\n",
				    srx.transport.family,
				    local->srx.transport.family);
		जाओ not_found;
	पूर्ण

	k.epoch	= sp->hdr.epoch;
	k.cid	= sp->hdr.cid & RXRPC_CIDMASK;

	अगर (rxrpc_to_server(sp)) अणु
		/* We need to look up service connections by the full protocol
		 * parameter set.  We look up the peer first as an पूर्णांकermediate
		 * step and then the connection from the peer's tree.
		 */
		peer = rxrpc_lookup_peer_rcu(local, &srx);
		अगर (!peer)
			जाओ not_found;
		*_peer = peer;
		conn = rxrpc_find_service_conn_rcu(peer, skb);
		अगर (!conn || atomic_पढ़ो(&conn->usage) == 0)
			जाओ not_found;
		_leave(" = %p", conn);
		वापस conn;
	पूर्ण अन्यथा अणु
		/* Look up client connections by connection ID alone as their
		 * IDs are unique क्रम this machine.
		 */
		conn = idr_find(&rxrpc_client_conn_ids,
				sp->hdr.cid >> RXRPC_CIDSHIFT);
		अगर (!conn || atomic_पढ़ो(&conn->usage) == 0) अणु
			_debug("no conn");
			जाओ not_found;
		पूर्ण

		अगर (conn->proto.epoch != k.epoch ||
		    conn->params.local != local)
			जाओ not_found;

		peer = conn->params.peer;
		चयन (srx.transport.family) अणु
		हाल AF_INET:
			अगर (peer->srx.transport.sin.sin_port !=
			    srx.transport.sin.sin_port ||
			    peer->srx.transport.sin.sin_addr.s_addr !=
			    srx.transport.sin.sin_addr.s_addr)
				जाओ not_found;
			अवरोध;
#अगर_घोषित CONFIG_AF_RXRPC_IPV6
		हाल AF_INET6:
			अगर (peer->srx.transport.sin6.sin6_port !=
			    srx.transport.sin6.sin6_port ||
			    स_भेद(&peer->srx.transport.sin6.sin6_addr,
				   &srx.transport.sin6.sin6_addr,
				   माप(काष्ठा in6_addr)) != 0)
				जाओ not_found;
			अवरोध;
#पूर्ण_अगर
		शेष:
			BUG();
		पूर्ण

		_leave(" = %p", conn);
		वापस conn;
	पूर्ण

not_found:
	_leave(" = NULL");
	वापस शून्य;
पूर्ण

/*
 * Disconnect a call and clear any channel it occupies when that call
 * terminates.  The caller must hold the channel_lock and must release the
 * call's ref on the connection.
 */
व्योम __rxrpc_disconnect_call(काष्ठा rxrpc_connection *conn,
			     काष्ठा rxrpc_call *call)
अणु
	काष्ठा rxrpc_channel *chan =
		&conn->channels[call->cid & RXRPC_CHANNELMASK];

	_enter("%d,%x", conn->debug_id, call->cid);

	अगर (rcu_access_poपूर्णांकer(chan->call) == call) अणु
		/* Save the result of the call so that we can repeat it अगर necessary
		 * through the channel, whilst disposing of the actual call record.
		 */
		trace_rxrpc_disconnect_call(call);
		चयन (call->completion) अणु
		हाल RXRPC_CALL_SUCCEEDED:
			chan->last_seq = call->rx_hard_ack;
			chan->last_type = RXRPC_PACKET_TYPE_ACK;
			अवरोध;
		हाल RXRPC_CALL_LOCALLY_ABORTED:
			chan->last_पात = call->पात_code;
			chan->last_type = RXRPC_PACKET_TYPE_ABORT;
			अवरोध;
		शेष:
			chan->last_पात = RX_USER_ABORT;
			chan->last_type = RXRPC_PACKET_TYPE_ABORT;
			अवरोध;
		पूर्ण

		/* Sync with rxrpc_conn_retransmit(). */
		smp_wmb();
		chan->last_call = chan->call_id;
		chan->call_id = chan->call_counter;

		rcu_assign_poपूर्णांकer(chan->call, शून्य);
	पूर्ण

	_leave("");
पूर्ण

/*
 * Disconnect a call and clear any channel it occupies when that call
 * terminates.
 */
व्योम rxrpc_disconnect_call(काष्ठा rxrpc_call *call)
अणु
	काष्ठा rxrpc_connection *conn = call->conn;

	call->peer->cong_cwnd = call->cong_cwnd;

	अगर (!hlist_unhashed(&call->error_link)) अणु
		spin_lock_bh(&call->peer->lock);
		hlist_del_rcu(&call->error_link);
		spin_unlock_bh(&call->peer->lock);
	पूर्ण

	अगर (rxrpc_is_client_call(call))
		वापस rxrpc_disconnect_client_call(conn->bundle, call);

	spin_lock(&conn->bundle->channel_lock);
	__rxrpc_disconnect_call(conn, call);
	spin_unlock(&conn->bundle->channel_lock);

	set_bit(RXRPC_CALL_DISCONNECTED, &call->flags);
	conn->idle_बारtamp = jअगरfies;
पूर्ण

/*
 * Kill off a connection.
 */
व्योम rxrpc_समाप्त_connection(काष्ठा rxrpc_connection *conn)
अणु
	काष्ठा rxrpc_net *rxnet = conn->params.local->rxnet;

	ASSERT(!rcu_access_poपूर्णांकer(conn->channels[0].call) &&
	       !rcu_access_poपूर्णांकer(conn->channels[1].call) &&
	       !rcu_access_poपूर्णांकer(conn->channels[2].call) &&
	       !rcu_access_poपूर्णांकer(conn->channels[3].call));
	ASSERT(list_empty(&conn->cache_link));

	ग_लिखो_lock(&rxnet->conn_lock);
	list_del_init(&conn->proc_link);
	ग_लिखो_unlock(&rxnet->conn_lock);

	/* Drain the Rx queue.  Note that even though we've unpublished, an
	 * incoming packet could still be being added to our Rx queue, so we
	 * will need to drain it again in the RCU cleanup handler.
	 */
	rxrpc_purge_queue(&conn->rx_queue);

	/* Leave final deकाष्ठाion to RCU.  The connection processor work item
	 * must carry a ref on the connection to prevent us getting here whilst
	 * it is queued or running.
	 */
	call_rcu(&conn->rcu, rxrpc_destroy_connection);
पूर्ण

/*
 * Queue a connection's work processor, getting a ref to pass to the work
 * queue.
 */
bool rxrpc_queue_conn(काष्ठा rxrpc_connection *conn)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	पूर्णांक n = atomic_fetch_add_unless(&conn->usage, 1, 0);
	अगर (n == 0)
		वापस false;
	अगर (rxrpc_queue_work(&conn->processor))
		trace_rxrpc_conn(conn->debug_id, rxrpc_conn_queued, n + 1, here);
	अन्यथा
		rxrpc_put_connection(conn);
	वापस true;
पूर्ण

/*
 * Note the re-emergence of a connection.
 */
व्योम rxrpc_see_connection(काष्ठा rxrpc_connection *conn)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	अगर (conn) अणु
		पूर्णांक n = atomic_पढ़ो(&conn->usage);

		trace_rxrpc_conn(conn->debug_id, rxrpc_conn_seen, n, here);
	पूर्ण
पूर्ण

/*
 * Get a ref on a connection.
 */
काष्ठा rxrpc_connection *rxrpc_get_connection(काष्ठा rxrpc_connection *conn)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	पूर्णांक n = atomic_inc_वापस(&conn->usage);

	trace_rxrpc_conn(conn->debug_id, rxrpc_conn_got, n, here);
	वापस conn;
पूर्ण

/*
 * Try to get a ref on a connection.
 */
काष्ठा rxrpc_connection *
rxrpc_get_connection_maybe(काष्ठा rxrpc_connection *conn)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);

	अगर (conn) अणु
		पूर्णांक n = atomic_fetch_add_unless(&conn->usage, 1, 0);
		अगर (n > 0)
			trace_rxrpc_conn(conn->debug_id, rxrpc_conn_got, n + 1, here);
		अन्यथा
			conn = शून्य;
	पूर्ण
	वापस conn;
पूर्ण

/*
 * Set the service connection reap समयr.
 */
अटल व्योम rxrpc_set_service_reap_समयr(काष्ठा rxrpc_net *rxnet,
					 अचिन्हित दीर्घ reap_at)
अणु
	अगर (rxnet->live)
		समयr_reduce(&rxnet->service_conn_reap_समयr, reap_at);
पूर्ण

/*
 * Release a service connection
 */
व्योम rxrpc_put_service_conn(काष्ठा rxrpc_connection *conn)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	अचिन्हित पूर्णांक debug_id = conn->debug_id;
	पूर्णांक n;

	n = atomic_dec_वापस(&conn->usage);
	trace_rxrpc_conn(debug_id, rxrpc_conn_put_service, n, here);
	ASSERTCMP(n, >=, 0);
	अगर (n == 1)
		rxrpc_set_service_reap_समयr(conn->params.local->rxnet,
					     jअगरfies + rxrpc_connection_expiry);
पूर्ण

/*
 * destroy a भव connection
 */
अटल व्योम rxrpc_destroy_connection(काष्ठा rcu_head *rcu)
अणु
	काष्ठा rxrpc_connection *conn =
		container_of(rcu, काष्ठा rxrpc_connection, rcu);

	_enter("{%d,u=%d}", conn->debug_id, atomic_पढ़ो(&conn->usage));

	ASSERTCMP(atomic_पढ़ो(&conn->usage), ==, 0);

	_net("DESTROY CONN %d", conn->debug_id);

	del_समयr_sync(&conn->समयr);
	rxrpc_purge_queue(&conn->rx_queue);

	conn->security->clear(conn);
	key_put(conn->params.key);
	rxrpc_put_bundle(conn->bundle);
	rxrpc_put_peer(conn->params.peer);

	अगर (atomic_dec_and_test(&conn->params.local->rxnet->nr_conns))
		wake_up_var(&conn->params.local->rxnet->nr_conns);
	rxrpc_put_local(conn->params.local);

	kमुक्त(conn);
	_leave("");
पूर्ण

/*
 * reap dead service connections
 */
व्योम rxrpc_service_connection_reaper(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rxrpc_connection *conn, *_p;
	काष्ठा rxrpc_net *rxnet =
		container_of(work, काष्ठा rxrpc_net, service_conn_reaper);
	अचिन्हित दीर्घ expire_at, earliest, idle_बारtamp, now;

	LIST_HEAD(graveyard);

	_enter("");

	now = jअगरfies;
	earliest = now + MAX_JIFFY_OFFSET;

	ग_लिखो_lock(&rxnet->conn_lock);
	list_क्रम_each_entry_safe(conn, _p, &rxnet->service_conns, link) अणु
		ASSERTCMP(atomic_पढ़ो(&conn->usage), >, 0);
		अगर (likely(atomic_पढ़ो(&conn->usage) > 1))
			जारी;
		अगर (conn->state == RXRPC_CONN_SERVICE_PREALLOC)
			जारी;

		अगर (rxnet->live && !conn->params.local->dead) अणु
			idle_बारtamp = READ_ONCE(conn->idle_बारtamp);
			expire_at = idle_बारtamp + rxrpc_connection_expiry * HZ;
			अगर (conn->params.local->service_बंदd)
				expire_at = idle_बारtamp + rxrpc_बंदd_conn_expiry * HZ;

			_debug("reap CONN %d { u=%d,t=%ld }",
			       conn->debug_id, atomic_पढ़ो(&conn->usage),
			       (दीर्घ)expire_at - (दीर्घ)now);

			अगर (समय_beक्रमe(now, expire_at)) अणु
				अगर (समय_beक्रमe(expire_at, earliest))
					earliest = expire_at;
				जारी;
			पूर्ण
		पूर्ण

		/* The usage count sits at 1 whilst the object is unused on the
		 * list; we reduce that to 0 to make the object unavailable.
		 */
		अगर (atomic_cmpxchg(&conn->usage, 1, 0) != 1)
			जारी;
		trace_rxrpc_conn(conn->debug_id, rxrpc_conn_reap_service, 0, शून्य);

		अगर (rxrpc_conn_is_client(conn))
			BUG();
		अन्यथा
			rxrpc_unpublish_service_conn(conn);

		list_move_tail(&conn->link, &graveyard);
	पूर्ण
	ग_लिखो_unlock(&rxnet->conn_lock);

	अगर (earliest != now + MAX_JIFFY_OFFSET) अणु
		_debug("reschedule reaper %ld", (दीर्घ)earliest - (दीर्घ)now);
		ASSERT(समय_after(earliest, now));
		rxrpc_set_service_reap_समयr(rxnet, earliest);
	पूर्ण

	जबतक (!list_empty(&graveyard)) अणु
		conn = list_entry(graveyard.next, काष्ठा rxrpc_connection,
				  link);
		list_del_init(&conn->link);

		ASSERTCMP(atomic_पढ़ो(&conn->usage), ==, 0);
		rxrpc_समाप्त_connection(conn);
	पूर्ण

	_leave("");
पूर्ण

/*
 * preemptively destroy all the service connection records rather than
 * रुकोing क्रम them to समय out
 */
व्योम rxrpc_destroy_all_connections(काष्ठा rxrpc_net *rxnet)
अणु
	काष्ठा rxrpc_connection *conn, *_p;
	bool leak = false;

	_enter("");

	atomic_dec(&rxnet->nr_conns);
	rxrpc_destroy_all_client_connections(rxnet);

	del_समयr_sync(&rxnet->service_conn_reap_समयr);
	rxrpc_queue_work(&rxnet->service_conn_reaper);
	flush_workqueue(rxrpc_workqueue);

	ग_लिखो_lock(&rxnet->conn_lock);
	list_क्रम_each_entry_safe(conn, _p, &rxnet->service_conns, link) अणु
		pr_err("AF_RXRPC: Leaked conn %p {%d}\n",
		       conn, atomic_पढ़ो(&conn->usage));
		leak = true;
	पूर्ण
	ग_लिखो_unlock(&rxnet->conn_lock);
	BUG_ON(leak);

	ASSERT(list_empty(&rxnet->conn_proc_list));

	/* We need to रुको क्रम the connections to be destroyed by RCU as they
	 * pin things that we still need to get rid of.
	 */
	रुको_var_event(&rxnet->nr_conns, !atomic_पढ़ो(&rxnet->nr_conns));
	_leave("");
पूर्ण
