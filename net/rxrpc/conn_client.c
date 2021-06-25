<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Client connection-specअगरic management code.
 *
 * Copyright (C) 2016, 2020 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * Client connections need to be cached क्रम a little जबतक after they've made a
 * call so as to handle retransmitted DATA packets in हाल the server didn't
 * receive the final ACK or terminating ABORT we sent it.
 *
 * There are flags of relevance to the cache:
 *
 *  (2) DONT_REUSE - The connection should be discarded as soon as possible and
 *      should not be reused.  This is set when an exclusive connection is used
 *      or a call ID counter overflows.
 *
 * The caching state may only be changed अगर the cache lock is held.
 *
 * There are two idle client connection expiry durations.  If the total number
 * of connections is below the reap threshold, we use the normal duration; अगर
 * it's above, we use the fast duration.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/slab.h>
#समावेश <linux/idr.h>
#समावेश <linux/समयr.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "ar-internal.h"

__पढ़ो_mostly अचिन्हित पूर्णांक rxrpc_reap_client_connections = 900;
__पढ़ो_mostly अचिन्हित दीर्घ rxrpc_conn_idle_client_expiry = 2 * 60 * HZ;
__पढ़ो_mostly अचिन्हित दीर्घ rxrpc_conn_idle_client_fast_expiry = 2 * HZ;

/*
 * We use machine-unique IDs क्रम our client connections.
 */
DEFINE_IDR(rxrpc_client_conn_ids);
अटल DEFINE_SPINLOCK(rxrpc_conn_id_lock);

/*
 * Get a connection ID and epoch क्रम a client connection from the global pool.
 * The connection काष्ठा poपूर्णांकer is then recorded in the idr radix tree.  The
 * epoch करोesn't change until the client is rebooted (or, at least, unless the
 * module is unloaded).
 */
अटल पूर्णांक rxrpc_get_client_connection_id(काष्ठा rxrpc_connection *conn,
					  gfp_t gfp)
अणु
	काष्ठा rxrpc_net *rxnet = conn->params.local->rxnet;
	पूर्णांक id;

	_enter("");

	idr_preload(gfp);
	spin_lock(&rxrpc_conn_id_lock);

	id = idr_alloc_cyclic(&rxrpc_client_conn_ids, conn,
			      1, 0x40000000, GFP_NOWAIT);
	अगर (id < 0)
		जाओ error;

	spin_unlock(&rxrpc_conn_id_lock);
	idr_preload_end();

	conn->proto.epoch = rxnet->epoch;
	conn->proto.cid = id << RXRPC_CIDSHIFT;
	set_bit(RXRPC_CONN_HAS_IDR, &conn->flags);
	_leave(" [CID %x]", conn->proto.cid);
	वापस 0;

error:
	spin_unlock(&rxrpc_conn_id_lock);
	idr_preload_end();
	_leave(" = %d", id);
	वापस id;
पूर्ण

/*
 * Release a connection ID क्रम a client connection from the global pool.
 */
अटल व्योम rxrpc_put_client_connection_id(काष्ठा rxrpc_connection *conn)
अणु
	अगर (test_bit(RXRPC_CONN_HAS_IDR, &conn->flags)) अणु
		spin_lock(&rxrpc_conn_id_lock);
		idr_हटाओ(&rxrpc_client_conn_ids,
			   conn->proto.cid >> RXRPC_CIDSHIFT);
		spin_unlock(&rxrpc_conn_id_lock);
	पूर्ण
पूर्ण

/*
 * Destroy the client connection ID tree.
 */
व्योम rxrpc_destroy_client_conn_ids(व्योम)
अणु
	काष्ठा rxrpc_connection *conn;
	पूर्णांक id;

	अगर (!idr_is_empty(&rxrpc_client_conn_ids)) अणु
		idr_क्रम_each_entry(&rxrpc_client_conn_ids, conn, id) अणु
			pr_err("AF_RXRPC: Leaked client conn %p {%d}\n",
			       conn, atomic_पढ़ो(&conn->usage));
		पूर्ण
		BUG();
	पूर्ण

	idr_destroy(&rxrpc_client_conn_ids);
पूर्ण

/*
 * Allocate a connection bundle.
 */
अटल काष्ठा rxrpc_bundle *rxrpc_alloc_bundle(काष्ठा rxrpc_conn_parameters *cp,
					       gfp_t gfp)
अणु
	काष्ठा rxrpc_bundle *bundle;

	bundle = kzalloc(माप(*bundle), gfp);
	अगर (bundle) अणु
		bundle->params = *cp;
		rxrpc_get_peer(bundle->params.peer);
		atomic_set(&bundle->usage, 1);
		spin_lock_init(&bundle->channel_lock);
		INIT_LIST_HEAD(&bundle->रुकोing_calls);
	पूर्ण
	वापस bundle;
पूर्ण

काष्ठा rxrpc_bundle *rxrpc_get_bundle(काष्ठा rxrpc_bundle *bundle)
अणु
	atomic_inc(&bundle->usage);
	वापस bundle;
पूर्ण

व्योम rxrpc_put_bundle(काष्ठा rxrpc_bundle *bundle)
अणु
	अचिन्हित पूर्णांक d = bundle->debug_id;
	अचिन्हित पूर्णांक u = atomic_dec_वापस(&bundle->usage);

	_debug("PUT B=%x %u", d, u);
	अगर (u == 0) अणु
		rxrpc_put_peer(bundle->params.peer);
		kमुक्त(bundle);
	पूर्ण
पूर्ण

/*
 * Allocate a client connection.
 */
अटल काष्ठा rxrpc_connection *
rxrpc_alloc_client_connection(काष्ठा rxrpc_bundle *bundle, gfp_t gfp)
अणु
	काष्ठा rxrpc_connection *conn;
	काष्ठा rxrpc_net *rxnet = bundle->params.local->rxnet;
	पूर्णांक ret;

	_enter("");

	conn = rxrpc_alloc_connection(gfp);
	अगर (!conn) अणु
		_leave(" = -ENOMEM");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	atomic_set(&conn->usage, 1);
	conn->bundle		= bundle;
	conn->params		= bundle->params;
	conn->out_clientflag	= RXRPC_CLIENT_INITIATED;
	conn->state		= RXRPC_CONN_CLIENT;
	conn->service_id	= conn->params.service_id;

	ret = rxrpc_get_client_connection_id(conn, gfp);
	अगर (ret < 0)
		जाओ error_0;

	ret = rxrpc_init_client_conn_security(conn);
	अगर (ret < 0)
		जाओ error_1;

	atomic_inc(&rxnet->nr_conns);
	ग_लिखो_lock(&rxnet->conn_lock);
	list_add_tail(&conn->proc_link, &rxnet->conn_proc_list);
	ग_लिखो_unlock(&rxnet->conn_lock);

	rxrpc_get_bundle(bundle);
	rxrpc_get_peer(conn->params.peer);
	rxrpc_get_local(conn->params.local);
	key_get(conn->params.key);

	trace_rxrpc_conn(conn->debug_id, rxrpc_conn_new_client,
			 atomic_पढ़ो(&conn->usage),
			 __builtin_वापस_address(0));

	atomic_inc(&rxnet->nr_client_conns);
	trace_rxrpc_client(conn, -1, rxrpc_client_alloc);
	_leave(" = %p", conn);
	वापस conn;

error_1:
	rxrpc_put_client_connection_id(conn);
error_0:
	kमुक्त(conn);
	_leave(" = %d", ret);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * Determine अगर a connection may be reused.
 */
अटल bool rxrpc_may_reuse_conn(काष्ठा rxrpc_connection *conn)
अणु
	काष्ठा rxrpc_net *rxnet;
	पूर्णांक id_cursor, id, distance, limit;

	अगर (!conn)
		जाओ करोnt_reuse;

	rxnet = conn->params.local->rxnet;
	अगर (test_bit(RXRPC_CONN_DONT_REUSE, &conn->flags))
		जाओ करोnt_reuse;

	अगर (conn->state != RXRPC_CONN_CLIENT ||
	    conn->proto.epoch != rxnet->epoch)
		जाओ mark_करोnt_reuse;

	/* The IDR tree माला_लो very expensive on memory अगर the connection IDs are
	 * widely scattered throughout the number space, so we shall want to
	 * समाप्त off connections that, say, have an ID more than about four
	 * बार the maximum number of client conns away from the current
	 * allocation poपूर्णांक to try and keep the IDs concentrated.
	 */
	id_cursor = idr_get_cursor(&rxrpc_client_conn_ids);
	id = conn->proto.cid >> RXRPC_CIDSHIFT;
	distance = id - id_cursor;
	अगर (distance < 0)
		distance = -distance;
	limit = max_t(अचिन्हित दीर्घ, atomic_पढ़ो(&rxnet->nr_conns) * 4, 1024);
	अगर (distance > limit)
		जाओ mark_करोnt_reuse;

	वापस true;

mark_करोnt_reuse:
	set_bit(RXRPC_CONN_DONT_REUSE, &conn->flags);
करोnt_reuse:
	वापस false;
पूर्ण

/*
 * Look up the conn bundle that matches the connection parameters, adding it अगर
 * it करोesn't yet exist.
 */
अटल काष्ठा rxrpc_bundle *rxrpc_look_up_bundle(काष्ठा rxrpc_conn_parameters *cp,
						 gfp_t gfp)
अणु
	अटल atomic_t rxrpc_bundle_id;
	काष्ठा rxrpc_bundle *bundle, *candidate;
	काष्ठा rxrpc_local *local = cp->local;
	काष्ठा rb_node *p, **pp, *parent;
	दीर्घ dअगरf;

	_enter("{%px,%x,%u,%u}",
	       cp->peer, key_serial(cp->key), cp->security_level, cp->upgrade);

	अगर (cp->exclusive)
		वापस rxrpc_alloc_bundle(cp, gfp);

	/* First, see अगर the bundle is alपढ़ोy there. */
	_debug("search 1");
	spin_lock(&local->client_bundles_lock);
	p = local->client_bundles.rb_node;
	जबतक (p) अणु
		bundle = rb_entry(p, काष्ठा rxrpc_bundle, local_node);

#घोषणा cmp(X) ((दीर्घ)bundle->params.X - (दीर्घ)cp->X)
		dअगरf = (cmp(peer) ?:
			cmp(key) ?:
			cmp(security_level) ?:
			cmp(upgrade));
#अघोषित cmp
		अगर (dअगरf < 0)
			p = p->rb_left;
		अन्यथा अगर (dअगरf > 0)
			p = p->rb_right;
		अन्यथा
			जाओ found_bundle;
	पूर्ण
	spin_unlock(&local->client_bundles_lock);
	_debug("not found");

	/* It wasn't.  We need to add one. */
	candidate = rxrpc_alloc_bundle(cp, gfp);
	अगर (!candidate)
		वापस शून्य;

	_debug("search 2");
	spin_lock(&local->client_bundles_lock);
	pp = &local->client_bundles.rb_node;
	parent = शून्य;
	जबतक (*pp) अणु
		parent = *pp;
		bundle = rb_entry(parent, काष्ठा rxrpc_bundle, local_node);

#घोषणा cmp(X) ((दीर्घ)bundle->params.X - (दीर्घ)cp->X)
		dअगरf = (cmp(peer) ?:
			cmp(key) ?:
			cmp(security_level) ?:
			cmp(upgrade));
#अघोषित cmp
		अगर (dअगरf < 0)
			pp = &(*pp)->rb_left;
		अन्यथा अगर (dअगरf > 0)
			pp = &(*pp)->rb_right;
		अन्यथा
			जाओ found_bundle_मुक्त;
	पूर्ण

	_debug("new bundle");
	candidate->debug_id = atomic_inc_वापस(&rxrpc_bundle_id);
	rb_link_node(&candidate->local_node, parent, pp);
	rb_insert_color(&candidate->local_node, &local->client_bundles);
	rxrpc_get_bundle(candidate);
	spin_unlock(&local->client_bundles_lock);
	_leave(" = %u [new]", candidate->debug_id);
	वापस candidate;

found_bundle_मुक्त:
	kमुक्त(candidate);
found_bundle:
	rxrpc_get_bundle(bundle);
	spin_unlock(&local->client_bundles_lock);
	_leave(" = %u [found]", bundle->debug_id);
	वापस bundle;
पूर्ण

/*
 * Create or find a client bundle to use क्रम a call.
 *
 * If we वापस with a connection, the call will be on its रुकोing list.  It's
 * left to the caller to assign a channel and wake up the call.
 */
अटल काष्ठा rxrpc_bundle *rxrpc_prep_call(काष्ठा rxrpc_sock *rx,
					    काष्ठा rxrpc_call *call,
					    काष्ठा rxrpc_conn_parameters *cp,
					    काष्ठा sockaddr_rxrpc *srx,
					    gfp_t gfp)
अणु
	काष्ठा rxrpc_bundle *bundle;

	_enter("{%d,%lx},", call->debug_id, call->user_call_ID);

	cp->peer = rxrpc_lookup_peer(rx, cp->local, srx, gfp);
	अगर (!cp->peer)
		जाओ error;

	call->cong_cwnd = cp->peer->cong_cwnd;
	अगर (call->cong_cwnd >= call->cong_ssthresh)
		call->cong_mode = RXRPC_CALL_CONGEST_AVOIDANCE;
	अन्यथा
		call->cong_mode = RXRPC_CALL_SLOW_START;
	अगर (cp->upgrade)
		__set_bit(RXRPC_CALL_UPGRADE, &call->flags);

	/* Find the client connection bundle. */
	bundle = rxrpc_look_up_bundle(cp, gfp);
	अगर (!bundle)
		जाओ error;

	/* Get this call queued.  Someone अन्यथा may activate it whilst we're
	 * lining up a new connection, but that's fine.
	 */
	spin_lock(&bundle->channel_lock);
	list_add_tail(&call->chan_रुको_link, &bundle->रुकोing_calls);
	spin_unlock(&bundle->channel_lock);

	_leave(" = [B=%x]", bundle->debug_id);
	वापस bundle;

error:
	_leave(" = -ENOMEM");
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/*
 * Allocate a new connection and add it पूर्णांकo a bundle.
 */
अटल व्योम rxrpc_add_conn_to_bundle(काष्ठा rxrpc_bundle *bundle, gfp_t gfp)
	__releases(bundle->channel_lock)
अणु
	काष्ठा rxrpc_connection *candidate = शून्य, *old = शून्य;
	bool conflict;
	पूर्णांक i;

	_enter("");

	conflict = bundle->alloc_conn;
	अगर (!conflict)
		bundle->alloc_conn = true;
	spin_unlock(&bundle->channel_lock);
	अगर (conflict) अणु
		_leave(" [conf]");
		वापस;
	पूर्ण

	candidate = rxrpc_alloc_client_connection(bundle, gfp);

	spin_lock(&bundle->channel_lock);
	bundle->alloc_conn = false;

	अगर (IS_ERR(candidate)) अणु
		bundle->alloc_error = PTR_ERR(candidate);
		spin_unlock(&bundle->channel_lock);
		_leave(" [err %ld]", PTR_ERR(candidate));
		वापस;
	पूर्ण

	bundle->alloc_error = 0;

	क्रम (i = 0; i < ARRAY_SIZE(bundle->conns); i++) अणु
		अचिन्हित पूर्णांक shअगरt = i * RXRPC_MAXCALLS;
		पूर्णांक j;

		old = bundle->conns[i];
		अगर (!rxrpc_may_reuse_conn(old)) अणु
			अगर (old)
				trace_rxrpc_client(old, -1, rxrpc_client_replace);
			candidate->bundle_shअगरt = shअगरt;
			bundle->conns[i] = candidate;
			क्रम (j = 0; j < RXRPC_MAXCALLS; j++)
				set_bit(shअगरt + j, &bundle->avail_chans);
			candidate = शून्य;
			अवरोध;
		पूर्ण

		old = शून्य;
	पूर्ण

	spin_unlock(&bundle->channel_lock);

	अगर (candidate) अणु
		_debug("discard C=%x", candidate->debug_id);
		trace_rxrpc_client(candidate, -1, rxrpc_client_duplicate);
		rxrpc_put_connection(candidate);
	पूर्ण

	rxrpc_put_connection(old);
	_leave("");
पूर्ण

/*
 * Add a connection to a bundle अगर there are no usable connections or we have
 * connections रुकोing क्रम extra capacity.
 */
अटल व्योम rxrpc_maybe_add_conn(काष्ठा rxrpc_bundle *bundle, gfp_t gfp)
अणु
	काष्ठा rxrpc_call *call;
	पूर्णांक i, usable;

	_enter("");

	spin_lock(&bundle->channel_lock);

	/* See अगर there are any usable connections. */
	usable = 0;
	क्रम (i = 0; i < ARRAY_SIZE(bundle->conns); i++)
		अगर (rxrpc_may_reuse_conn(bundle->conns[i]))
			usable++;

	अगर (!usable && !list_empty(&bundle->रुकोing_calls)) अणु
		call = list_first_entry(&bundle->रुकोing_calls,
					काष्ठा rxrpc_call, chan_रुको_link);
		अगर (test_bit(RXRPC_CALL_UPGRADE, &call->flags))
			bundle->try_upgrade = true;
	पूर्ण

	अगर (!usable)
		जाओ alloc_conn;

	अगर (!bundle->avail_chans &&
	    !bundle->try_upgrade &&
	    !list_empty(&bundle->रुकोing_calls) &&
	    usable < ARRAY_SIZE(bundle->conns))
		जाओ alloc_conn;

	spin_unlock(&bundle->channel_lock);
	_leave("");
	वापस;

alloc_conn:
	वापस rxrpc_add_conn_to_bundle(bundle, gfp);
पूर्ण

/*
 * Assign a channel to the call at the front of the queue and wake the call up.
 * We करोn't increment the callNumber counter until this number has been exposed
 * to the world.
 */
अटल व्योम rxrpc_activate_one_channel(काष्ठा rxrpc_connection *conn,
				       अचिन्हित पूर्णांक channel)
अणु
	काष्ठा rxrpc_channel *chan = &conn->channels[channel];
	काष्ठा rxrpc_bundle *bundle = conn->bundle;
	काष्ठा rxrpc_call *call = list_entry(bundle->रुकोing_calls.next,
					     काष्ठा rxrpc_call, chan_रुको_link);
	u32 call_id = chan->call_counter + 1;

	_enter("C=%x,%u", conn->debug_id, channel);

	trace_rxrpc_client(conn, channel, rxrpc_client_chan_activate);

	/* Cancel the final ACK on the previous call अगर it hasn't been sent yet
	 * as the DATA packet will implicitly ACK it.
	 */
	clear_bit(RXRPC_CONN_FINAL_ACK_0 + channel, &conn->flags);
	clear_bit(conn->bundle_shअगरt + channel, &bundle->avail_chans);

	rxrpc_see_call(call);
	list_del_init(&call->chan_रुको_link);
	call->peer	= rxrpc_get_peer(conn->params.peer);
	call->conn	= rxrpc_get_connection(conn);
	call->cid	= conn->proto.cid | channel;
	call->call_id	= call_id;
	call->security	= conn->security;
	call->security_ix = conn->security_ix;
	call->service_id = conn->service_id;

	trace_rxrpc_connect_call(call);
	_net("CONNECT call %08x:%08x as call %d on conn %d",
	     call->cid, call->call_id, call->debug_id, conn->debug_id);

	ग_लिखो_lock_bh(&call->state_lock);
	call->state = RXRPC_CALL_CLIENT_SEND_REQUEST;
	ग_लिखो_unlock_bh(&call->state_lock);

	/* Paired with the पढ़ो barrier in rxrpc_connect_call().  This orders
	 * cid and epoch in the connection wrt to call_id without the need to
	 * take the channel_lock.
	 *
	 * We provisionally assign a callNumber at this poपूर्णांक, but we करोn't
	 * confirm it until the call is about to be exposed.
	 *
	 * TODO: Pair with a barrier in the data_पढ़ोy handler when that looks
	 * at the call ID through a connection channel.
	 */
	smp_wmb();

	chan->call_id		= call_id;
	chan->call_debug_id	= call->debug_id;
	rcu_assign_poपूर्णांकer(chan->call, call);
	wake_up(&call->रुकोq);
पूर्ण

/*
 * Remove a connection from the idle list अगर it's on it.
 */
अटल व्योम rxrpc_unidle_conn(काष्ठा rxrpc_bundle *bundle, काष्ठा rxrpc_connection *conn)
अणु
	काष्ठा rxrpc_net *rxnet = bundle->params.local->rxnet;
	bool drop_ref;

	अगर (!list_empty(&conn->cache_link)) अणु
		drop_ref = false;
		spin_lock(&rxnet->client_conn_cache_lock);
		अगर (!list_empty(&conn->cache_link)) अणु
			list_del_init(&conn->cache_link);
			drop_ref = true;
		पूर्ण
		spin_unlock(&rxnet->client_conn_cache_lock);
		अगर (drop_ref)
			rxrpc_put_connection(conn);
	पूर्ण
पूर्ण

/*
 * Assign channels and callNumbers to रुकोing calls with channel_lock
 * held by caller.
 */
अटल व्योम rxrpc_activate_channels_locked(काष्ठा rxrpc_bundle *bundle)
अणु
	काष्ठा rxrpc_connection *conn;
	अचिन्हित दीर्घ avail, mask;
	अचिन्हित पूर्णांक channel, slot;

	अगर (bundle->try_upgrade)
		mask = 1;
	अन्यथा
		mask = अच_दीर्घ_उच्च;

	जबतक (!list_empty(&bundle->रुकोing_calls)) अणु
		avail = bundle->avail_chans & mask;
		अगर (!avail)
			अवरोध;
		channel = __ffs(avail);
		clear_bit(channel, &bundle->avail_chans);

		slot = channel / RXRPC_MAXCALLS;
		conn = bundle->conns[slot];
		अगर (!conn)
			अवरोध;

		अगर (bundle->try_upgrade)
			set_bit(RXRPC_CONN_PROBING_FOR_UPGRADE, &conn->flags);
		rxrpc_unidle_conn(bundle, conn);

		channel &= (RXRPC_MAXCALLS - 1);
		conn->act_chans	|= 1 << channel;
		rxrpc_activate_one_channel(conn, channel);
	पूर्ण
पूर्ण

/*
 * Assign channels and callNumbers to रुकोing calls.
 */
अटल व्योम rxrpc_activate_channels(काष्ठा rxrpc_bundle *bundle)
अणु
	_enter("B=%x", bundle->debug_id);

	trace_rxrpc_client(शून्य, -1, rxrpc_client_activate_chans);

	अगर (!bundle->avail_chans)
		वापस;

	spin_lock(&bundle->channel_lock);
	rxrpc_activate_channels_locked(bundle);
	spin_unlock(&bundle->channel_lock);
	_leave("");
पूर्ण

/*
 * Wait क्रम a callNumber and a channel to be granted to a call.
 */
अटल पूर्णांक rxrpc_रुको_क्रम_channel(काष्ठा rxrpc_bundle *bundle,
				  काष्ठा rxrpc_call *call, gfp_t gfp)
अणु
	DECLARE_WAITQUEUE(myself, current);
	पूर्णांक ret = 0;

	_enter("%d", call->debug_id);

	अगर (!gfpflags_allow_blocking(gfp)) अणु
		rxrpc_maybe_add_conn(bundle, gfp);
		rxrpc_activate_channels(bundle);
		ret = bundle->alloc_error ?: -EAGAIN;
		जाओ out;
	पूर्ण

	add_रुको_queue_exclusive(&call->रुकोq, &myself);
	क्रम (;;) अणु
		rxrpc_maybe_add_conn(bundle, gfp);
		rxrpc_activate_channels(bundle);
		ret = bundle->alloc_error;
		अगर (ret < 0)
			अवरोध;

		चयन (call->पूर्णांकerruptibility) अणु
		हाल RXRPC_INTERRUPTIBLE:
		हाल RXRPC_PREINTERRUPTIBLE:
			set_current_state(TASK_INTERRUPTIBLE);
			अवरोध;
		हाल RXRPC_UNINTERRUPTIBLE:
		शेष:
			set_current_state(TASK_UNINTERRUPTIBLE);
			अवरोध;
		पूर्ण
		अगर (READ_ONCE(call->state) != RXRPC_CALL_CLIENT_AWAIT_CONN)
			अवरोध;
		अगर ((call->पूर्णांकerruptibility == RXRPC_INTERRUPTIBLE ||
		     call->पूर्णांकerruptibility == RXRPC_PREINTERRUPTIBLE) &&
		    संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		schedule();
	पूर्ण
	हटाओ_रुको_queue(&call->रुकोq, &myself);
	__set_current_state(TASK_RUNNING);

out:
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * find a connection क्रम a call
 * - called in process context with IRQs enabled
 */
पूर्णांक rxrpc_connect_call(काष्ठा rxrpc_sock *rx,
		       काष्ठा rxrpc_call *call,
		       काष्ठा rxrpc_conn_parameters *cp,
		       काष्ठा sockaddr_rxrpc *srx,
		       gfp_t gfp)
अणु
	काष्ठा rxrpc_bundle *bundle;
	काष्ठा rxrpc_net *rxnet = cp->local->rxnet;
	पूर्णांक ret = 0;

	_enter("{%d,%lx},", call->debug_id, call->user_call_ID);

	rxrpc_discard_expired_client_conns(&rxnet->client_conn_reaper);

	bundle = rxrpc_prep_call(rx, call, cp, srx, gfp);
	अगर (IS_ERR(bundle)) अणु
		ret = PTR_ERR(bundle);
		जाओ out;
	पूर्ण

	अगर (call->state == RXRPC_CALL_CLIENT_AWAIT_CONN) अणु
		ret = rxrpc_रुको_क्रम_channel(bundle, call, gfp);
		अगर (ret < 0)
			जाओ रुको_failed;
	पूर्ण

granted_channel:
	/* Paired with the ग_लिखो barrier in rxrpc_activate_one_channel(). */
	smp_rmb();

out_put_bundle:
	rxrpc_put_bundle(bundle);
out:
	_leave(" = %d", ret);
	वापस ret;

रुको_failed:
	spin_lock(&bundle->channel_lock);
	list_del_init(&call->chan_रुको_link);
	spin_unlock(&bundle->channel_lock);

	अगर (call->state != RXRPC_CALL_CLIENT_AWAIT_CONN) अणु
		ret = 0;
		जाओ granted_channel;
	पूर्ण

	trace_rxrpc_client(call->conn, ret, rxrpc_client_chan_रुको_failed);
	rxrpc_set_call_completion(call, RXRPC_CALL_LOCAL_ERROR, 0, ret);
	rxrpc_disconnect_client_call(bundle, call);
	जाओ out_put_bundle;
पूर्ण

/*
 * Note that a call, and thus a connection, is about to be exposed to the
 * world.
 */
व्योम rxrpc_expose_client_call(काष्ठा rxrpc_call *call)
अणु
	अचिन्हित पूर्णांक channel = call->cid & RXRPC_CHANNELMASK;
	काष्ठा rxrpc_connection *conn = call->conn;
	काष्ठा rxrpc_channel *chan = &conn->channels[channel];

	अगर (!test_and_set_bit(RXRPC_CALL_EXPOSED, &call->flags)) अणु
		/* Mark the call ID as being used.  If the callNumber counter
		 * exceeds ~2 billion, we समाप्त the connection after its
		 * outstanding calls have finished so that the counter करोesn't
		 * wrap.
		 */
		chan->call_counter++;
		अगर (chan->call_counter >= पूर्णांक_उच्च)
			set_bit(RXRPC_CONN_DONT_REUSE, &conn->flags);
		trace_rxrpc_client(conn, channel, rxrpc_client_exposed);
	पूर्ण
पूर्ण

/*
 * Set the reap समयr.
 */
अटल व्योम rxrpc_set_client_reap_समयr(काष्ठा rxrpc_net *rxnet)
अणु
	अगर (!rxnet->समाप्त_all_client_conns) अणु
		अचिन्हित दीर्घ now = jअगरfies;
		अचिन्हित दीर्घ reap_at = now + rxrpc_conn_idle_client_expiry;

		अगर (rxnet->live)
			समयr_reduce(&rxnet->client_conn_reap_समयr, reap_at);
	पूर्ण
पूर्ण

/*
 * Disconnect a client call.
 */
व्योम rxrpc_disconnect_client_call(काष्ठा rxrpc_bundle *bundle, काष्ठा rxrpc_call *call)
अणु
	काष्ठा rxrpc_connection *conn;
	काष्ठा rxrpc_channel *chan = शून्य;
	काष्ठा rxrpc_net *rxnet = bundle->params.local->rxnet;
	अचिन्हित पूर्णांक channel;
	bool may_reuse;
	u32 cid;

	_enter("c=%x", call->debug_id);

	spin_lock(&bundle->channel_lock);
	set_bit(RXRPC_CALL_DISCONNECTED, &call->flags);

	/* Calls that have never actually been asचिन्हित a channel can simply be
	 * discarded.
	 */
	conn = call->conn;
	अगर (!conn) अणु
		_debug("call is waiting");
		ASSERTCMP(call->call_id, ==, 0);
		ASSERT(!test_bit(RXRPC_CALL_EXPOSED, &call->flags));
		list_del_init(&call->chan_रुको_link);
		जाओ out;
	पूर्ण

	cid = call->cid;
	channel = cid & RXRPC_CHANNELMASK;
	chan = &conn->channels[channel];
	trace_rxrpc_client(conn, channel, rxrpc_client_chan_disconnect);

	अगर (rcu_access_poपूर्णांकer(chan->call) != call) अणु
		spin_unlock(&bundle->channel_lock);
		BUG();
	पूर्ण

	may_reuse = rxrpc_may_reuse_conn(conn);

	/* If a client call was exposed to the world, we save the result क्रम
	 * retransmission.
	 *
	 * We use a barrier here so that the call number and पात code can be
	 * पढ़ो without needing to take a lock.
	 *
	 * TODO: Make the incoming packet handler check this and handle
	 * terminal retransmission without requiring access to the call.
	 */
	अगर (test_bit(RXRPC_CALL_EXPOSED, &call->flags)) अणु
		_debug("exposed %u,%u", call->call_id, call->पात_code);
		__rxrpc_disconnect_call(conn, call);

		अगर (test_and_clear_bit(RXRPC_CONN_PROBING_FOR_UPGRADE, &conn->flags)) अणु
			trace_rxrpc_client(conn, channel, rxrpc_client_to_active);
			bundle->try_upgrade = false;
			अगर (may_reuse)
				rxrpc_activate_channels_locked(bundle);
		पूर्ण

	पूर्ण

	/* See अगर we can pass the channel directly to another call. */
	अगर (may_reuse && !list_empty(&bundle->रुकोing_calls)) अणु
		trace_rxrpc_client(conn, channel, rxrpc_client_chan_pass);
		rxrpc_activate_one_channel(conn, channel);
		जाओ out;
	पूर्ण

	/* Schedule the final ACK to be transmitted in a लघु जबतक so that it
	 * can be skipped अगर we find a follow-on call.  The first DATA packet
	 * of the follow on call will implicitly ACK this call.
	 */
	अगर (call->completion == RXRPC_CALL_SUCCEEDED &&
	    test_bit(RXRPC_CALL_EXPOSED, &call->flags)) अणु
		अचिन्हित दीर्घ final_ack_at = jअगरfies + 2;

		WRITE_ONCE(chan->final_ack_at, final_ack_at);
		smp_wmb(); /* vs rxrpc_process_delayed_final_acks() */
		set_bit(RXRPC_CONN_FINAL_ACK_0 + channel, &conn->flags);
		rxrpc_reduce_conn_समयr(conn, final_ack_at);
	पूर्ण

	/* Deactivate the channel. */
	rcu_assign_poपूर्णांकer(chan->call, शून्य);
	set_bit(conn->bundle_shअगरt + channel, &conn->bundle->avail_chans);
	conn->act_chans	&= ~(1 << channel);

	/* If no channels reमुख्य active, then put the connection on the idle
	 * list क्रम a लघु जबतक.  Give it a ref to stop it going away अगर it
	 * becomes unbundled.
	 */
	अगर (!conn->act_chans) अणु
		trace_rxrpc_client(conn, channel, rxrpc_client_to_idle);
		conn->idle_बारtamp = jअगरfies;

		rxrpc_get_connection(conn);
		spin_lock(&rxnet->client_conn_cache_lock);
		list_move_tail(&conn->cache_link, &rxnet->idle_client_conns);
		spin_unlock(&rxnet->client_conn_cache_lock);

		rxrpc_set_client_reap_समयr(rxnet);
	पूर्ण

out:
	spin_unlock(&bundle->channel_lock);
	_leave("");
	वापस;
पूर्ण

/*
 * Remove a connection from a bundle.
 */
अटल व्योम rxrpc_unbundle_conn(काष्ठा rxrpc_connection *conn)
अणु
	काष्ठा rxrpc_bundle *bundle = conn->bundle;
	काष्ठा rxrpc_local *local = bundle->params.local;
	अचिन्हित पूर्णांक bindex;
	bool need_drop = false, need_put = false;
	पूर्णांक i;

	_enter("C=%x", conn->debug_id);

	अगर (conn->flags & RXRPC_CONN_FINAL_ACK_MASK)
		rxrpc_process_delayed_final_acks(conn, true);

	spin_lock(&bundle->channel_lock);
	bindex = conn->bundle_shअगरt / RXRPC_MAXCALLS;
	अगर (bundle->conns[bindex] == conn) अणु
		_debug("clear slot %u", bindex);
		bundle->conns[bindex] = शून्य;
		क्रम (i = 0; i < RXRPC_MAXCALLS; i++)
			clear_bit(conn->bundle_shअगरt + i, &bundle->avail_chans);
		need_drop = true;
	पूर्ण
	spin_unlock(&bundle->channel_lock);

	/* If there are no more connections, हटाओ the bundle */
	अगर (!bundle->avail_chans) अणु
		_debug("maybe unbundle");
		spin_lock(&local->client_bundles_lock);

		क्रम (i = 0; i < ARRAY_SIZE(bundle->conns); i++)
			अगर (bundle->conns[i])
				अवरोध;
		अगर (i == ARRAY_SIZE(bundle->conns) && !bundle->params.exclusive) अणु
			_debug("erase bundle");
			rb_erase(&bundle->local_node, &local->client_bundles);
			need_put = true;
		पूर्ण

		spin_unlock(&local->client_bundles_lock);
		अगर (need_put)
			rxrpc_put_bundle(bundle);
	पूर्ण

	अगर (need_drop)
		rxrpc_put_connection(conn);
	_leave("");
पूर्ण

/*
 * Clean up a dead client connection.
 */
अटल व्योम rxrpc_समाप्त_client_conn(काष्ठा rxrpc_connection *conn)
अणु
	काष्ठा rxrpc_local *local = conn->params.local;
	काष्ठा rxrpc_net *rxnet = local->rxnet;

	_enter("C=%x", conn->debug_id);

	trace_rxrpc_client(conn, -1, rxrpc_client_cleanup);
	atomic_dec(&rxnet->nr_client_conns);

	rxrpc_put_client_connection_id(conn);
	rxrpc_समाप्त_connection(conn);
पूर्ण

/*
 * Clean up a dead client connections.
 */
व्योम rxrpc_put_client_conn(काष्ठा rxrpc_connection *conn)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	अचिन्हित पूर्णांक debug_id = conn->debug_id;
	पूर्णांक n;

	n = atomic_dec_वापस(&conn->usage);
	trace_rxrpc_conn(debug_id, rxrpc_conn_put_client, n, here);
	अगर (n <= 0) अणु
		ASSERTCMP(n, >=, 0);
		rxrpc_समाप्त_client_conn(conn);
	पूर्ण
पूर्ण

/*
 * Discard expired client connections from the idle list.  Each conn in the
 * idle list has been exposed and holds an extra ref because of that.
 *
 * This may be called from conn setup or from a work item so cannot be
 * considered non-reentrant.
 */
व्योम rxrpc_discard_expired_client_conns(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rxrpc_connection *conn;
	काष्ठा rxrpc_net *rxnet =
		container_of(work, काष्ठा rxrpc_net, client_conn_reaper);
	अचिन्हित दीर्घ expiry, conn_expires_at, now;
	अचिन्हित पूर्णांक nr_conns;

	_enter("");

	अगर (list_empty(&rxnet->idle_client_conns)) अणु
		_leave(" [empty]");
		वापस;
	पूर्ण

	/* Don't द्विगुन up on the discarding */
	अगर (!spin_trylock(&rxnet->client_conn_discard_lock)) अणु
		_leave(" [already]");
		वापस;
	पूर्ण

	/* We keep an estimate of what the number of conns ought to be after
	 * we've discarded some so that we don't overकरो the discarding.
	 */
	nr_conns = atomic_पढ़ो(&rxnet->nr_client_conns);

next:
	spin_lock(&rxnet->client_conn_cache_lock);

	अगर (list_empty(&rxnet->idle_client_conns))
		जाओ out;

	conn = list_entry(rxnet->idle_client_conns.next,
			  काष्ठा rxrpc_connection, cache_link);

	अगर (!rxnet->समाप्त_all_client_conns) अणु
		/* If the number of connections is over the reap limit, we
		 * expedite discard by reducing the expiry समयout.  We must,
		 * however, have at least a लघु grace period to be able to करो
		 * final-ACK or ABORT retransmission.
		 */
		expiry = rxrpc_conn_idle_client_expiry;
		अगर (nr_conns > rxrpc_reap_client_connections)
			expiry = rxrpc_conn_idle_client_fast_expiry;
		अगर (conn->params.local->service_बंदd)
			expiry = rxrpc_बंदd_conn_expiry * HZ;

		conn_expires_at = conn->idle_बारtamp + expiry;

		now = READ_ONCE(jअगरfies);
		अगर (समय_after(conn_expires_at, now))
			जाओ not_yet_expired;
	पूर्ण

	trace_rxrpc_client(conn, -1, rxrpc_client_discard);
	list_del_init(&conn->cache_link);

	spin_unlock(&rxnet->client_conn_cache_lock);

	rxrpc_unbundle_conn(conn);
	rxrpc_put_connection(conn); /* Drop the ->cache_link ref */

	nr_conns--;
	जाओ next;

not_yet_expired:
	/* The connection at the front of the queue hasn't yet expired, so
	 * schedule the work item क्रम that poपूर्णांक अगर we discarded something.
	 *
	 * We करोn't worry अगर the work item is alपढ़ोy scheduled - it can look
	 * after rescheduling itself at a later समय.  We could cancel it, but
	 * then things get messier.
	 */
	_debug("not yet");
	अगर (!rxnet->समाप्त_all_client_conns)
		समयr_reduce(&rxnet->client_conn_reap_समयr, conn_expires_at);

out:
	spin_unlock(&rxnet->client_conn_cache_lock);
	spin_unlock(&rxnet->client_conn_discard_lock);
	_leave("");
पूर्ण

/*
 * Preemptively destroy all the client connection records rather than रुकोing
 * क्रम them to समय out
 */
व्योम rxrpc_destroy_all_client_connections(काष्ठा rxrpc_net *rxnet)
अणु
	_enter("");

	spin_lock(&rxnet->client_conn_cache_lock);
	rxnet->समाप्त_all_client_conns = true;
	spin_unlock(&rxnet->client_conn_cache_lock);

	del_समयr_sync(&rxnet->client_conn_reap_समयr);

	अगर (!rxrpc_queue_work(&rxnet->client_conn_reaper))
		_debug("destroy: queue failed");

	_leave("");
पूर्ण

/*
 * Clean up the client connections on a local endpoपूर्णांक.
 */
व्योम rxrpc_clean_up_local_conns(काष्ठा rxrpc_local *local)
अणु
	काष्ठा rxrpc_connection *conn, *पंचांगp;
	काष्ठा rxrpc_net *rxnet = local->rxnet;
	LIST_HEAD(graveyard);

	_enter("");

	spin_lock(&rxnet->client_conn_cache_lock);

	list_क्रम_each_entry_safe(conn, पंचांगp, &rxnet->idle_client_conns,
				 cache_link) अणु
		अगर (conn->params.local == local) अणु
			trace_rxrpc_client(conn, -1, rxrpc_client_discard);
			list_move(&conn->cache_link, &graveyard);
		पूर्ण
	पूर्ण

	spin_unlock(&rxnet->client_conn_cache_lock);

	जबतक (!list_empty(&graveyard)) अणु
		conn = list_entry(graveyard.next,
				  काष्ठा rxrpc_connection, cache_link);
		list_del_init(&conn->cache_link);
		rxrpc_unbundle_conn(conn);
		rxrpc_put_connection(conn);
	पूर्ण

	_leave(" [culled]");
पूर्ण
