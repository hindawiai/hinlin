<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Service connection management
 *
 * Copyright (C) 2016 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/slab.h>
#समावेश "ar-internal.h"

अटल काष्ठा rxrpc_bundle rxrpc_service_dummy_bundle = अणु
	.usage		= ATOMIC_INIT(1),
	.debug_id	= अच_पूर्णांक_उच्च,
	.channel_lock	= __SPIN_LOCK_UNLOCKED(&rxrpc_service_dummy_bundle.channel_lock),
पूर्ण;

/*
 * Find a service connection under RCU conditions.
 *
 * We could use a hash table, but that is subject to bucket stuffing by an
 * attacker as the client माला_लो to pick the epoch and cid values and would know
 * the hash function.  So, instead, we use a hash table क्रम the peer and from
 * that an rbtree to find the service connection.  Under ordinary circumstances
 * it might be slower than a large hash table, but it is at least limited in
 * depth.
 */
काष्ठा rxrpc_connection *rxrpc_find_service_conn_rcu(काष्ठा rxrpc_peer *peer,
						     काष्ठा sk_buff *skb)
अणु
	काष्ठा rxrpc_connection *conn = शून्य;
	काष्ठा rxrpc_conn_proto k;
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	काष्ठा rb_node *p;
	अचिन्हित पूर्णांक seq = 0;

	k.epoch	= sp->hdr.epoch;
	k.cid	= sp->hdr.cid & RXRPC_CIDMASK;

	करो अणु
		/* Unक्रमtunately, rbtree walking करोesn't give reliable results
		 * under just the RCU पढ़ो lock, so we have to check क्रम
		 * changes.
		 */
		पढ़ो_seqbegin_or_lock(&peer->service_conn_lock, &seq);

		p = rcu_dereference_raw(peer->service_conns.rb_node);
		जबतक (p) अणु
			conn = rb_entry(p, काष्ठा rxrpc_connection, service_node);

			अगर (conn->proto.index_key < k.index_key)
				p = rcu_dereference_raw(p->rb_left);
			अन्यथा अगर (conn->proto.index_key > k.index_key)
				p = rcu_dereference_raw(p->rb_right);
			अन्यथा
				अवरोध;
			conn = शून्य;
		पूर्ण
	पूर्ण जबतक (need_seqretry(&peer->service_conn_lock, seq));

	करोne_seqretry(&peer->service_conn_lock, seq);
	_leave(" = %d", conn ? conn->debug_id : -1);
	वापस conn;
पूर्ण

/*
 * Insert a service connection पूर्णांकo a peer's tree, thereby making it a target
 * क्रम incoming packets.
 */
अटल व्योम rxrpc_publish_service_conn(काष्ठा rxrpc_peer *peer,
				       काष्ठा rxrpc_connection *conn)
अणु
	काष्ठा rxrpc_connection *cursor = शून्य;
	काष्ठा rxrpc_conn_proto k = conn->proto;
	काष्ठा rb_node **pp, *parent;

	ग_लिखो_seqlock_bh(&peer->service_conn_lock);

	pp = &peer->service_conns.rb_node;
	parent = शून्य;
	जबतक (*pp) अणु
		parent = *pp;
		cursor = rb_entry(parent,
				  काष्ठा rxrpc_connection, service_node);

		अगर (cursor->proto.index_key < k.index_key)
			pp = &(*pp)->rb_left;
		अन्यथा अगर (cursor->proto.index_key > k.index_key)
			pp = &(*pp)->rb_right;
		अन्यथा
			जाओ found_extant_conn;
	पूर्ण

	rb_link_node_rcu(&conn->service_node, parent, pp);
	rb_insert_color(&conn->service_node, &peer->service_conns);
conn_published:
	set_bit(RXRPC_CONN_IN_SERVICE_CONNS, &conn->flags);
	ग_लिखो_sequnlock_bh(&peer->service_conn_lock);
	_leave(" = %d [new]", conn->debug_id);
	वापस;

found_extant_conn:
	अगर (atomic_पढ़ो(&cursor->usage) == 0)
		जाओ replace_old_connection;
	ग_लिखो_sequnlock_bh(&peer->service_conn_lock);
	/* We should not be able to get here.  rxrpc_incoming_connection() is
	 * called in a non-reentrant context, so there can't be a race to
	 * insert a new connection.
	 */
	BUG();

replace_old_connection:
	/* The old connection is from an outdated epoch. */
	_debug("replace conn");
	rb_replace_node_rcu(&cursor->service_node,
			    &conn->service_node,
			    &peer->service_conns);
	clear_bit(RXRPC_CONN_IN_SERVICE_CONNS, &cursor->flags);
	जाओ conn_published;
पूर्ण

/*
 * Pपुनः_स्मृतिate a service connection.  The connection is placed on the proc and
 * reap lists so that we करोn't have to get the lock from BH context.
 */
काष्ठा rxrpc_connection *rxrpc_pपुनः_स्मृति_service_connection(काष्ठा rxrpc_net *rxnet,
							   gfp_t gfp)
अणु
	काष्ठा rxrpc_connection *conn = rxrpc_alloc_connection(gfp);

	अगर (conn) अणु
		/* We मुख्यtain an extra ref on the connection whilst it is on
		 * the rxrpc_connections list.
		 */
		conn->state = RXRPC_CONN_SERVICE_PREALLOC;
		atomic_set(&conn->usage, 2);
		conn->bundle = rxrpc_get_bundle(&rxrpc_service_dummy_bundle);

		atomic_inc(&rxnet->nr_conns);
		ग_लिखो_lock(&rxnet->conn_lock);
		list_add_tail(&conn->link, &rxnet->service_conns);
		list_add_tail(&conn->proc_link, &rxnet->conn_proc_list);
		ग_लिखो_unlock(&rxnet->conn_lock);

		trace_rxrpc_conn(conn->debug_id, rxrpc_conn_new_service,
				 atomic_पढ़ो(&conn->usage),
				 __builtin_वापस_address(0));
	पूर्ण

	वापस conn;
पूर्ण

/*
 * Set up an incoming connection.  This is called in BH context with the RCU
 * पढ़ो lock held.
 */
व्योम rxrpc_new_incoming_connection(काष्ठा rxrpc_sock *rx,
				   काष्ठा rxrpc_connection *conn,
				   स्थिर काष्ठा rxrpc_security *sec,
				   काष्ठा sk_buff *skb)
अणु
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);

	_enter("");

	conn->proto.epoch	= sp->hdr.epoch;
	conn->proto.cid		= sp->hdr.cid & RXRPC_CIDMASK;
	conn->params.service_id	= sp->hdr.serviceId;
	conn->service_id	= sp->hdr.serviceId;
	conn->security_ix	= sp->hdr.securityIndex;
	conn->out_clientflag	= 0;
	conn->security		= sec;
	अगर (conn->security_ix)
		conn->state	= RXRPC_CONN_SERVICE_UNSECURED;
	अन्यथा
		conn->state	= RXRPC_CONN_SERVICE;

	/* See अगर we should upgrade the service.  This can only happen on the
	 * first packet on a new connection.  Once करोne, it applies to all
	 * subsequent calls on that connection.
	 */
	अगर (sp->hdr.userStatus == RXRPC_USERSTATUS_SERVICE_UPGRADE &&
	    conn->service_id == rx->service_upgrade.from)
		conn->service_id = rx->service_upgrade.to;

	/* Make the connection a target क्रम incoming packets. */
	rxrpc_publish_service_conn(conn->params.peer, conn);

	_net("CONNECTION new %d {%x}", conn->debug_id, conn->proto.cid);
पूर्ण

/*
 * Remove the service connection from the peer's tree, thereby removing it as a
 * target क्रम incoming packets.
 */
व्योम rxrpc_unpublish_service_conn(काष्ठा rxrpc_connection *conn)
अणु
	काष्ठा rxrpc_peer *peer = conn->params.peer;

	ग_लिखो_seqlock_bh(&peer->service_conn_lock);
	अगर (test_and_clear_bit(RXRPC_CONN_IN_SERVICE_CONNS, &conn->flags))
		rb_erase(&conn->service_node, &peer->service_conns);
	ग_लिखो_sequnlock_bh(&peer->service_conn_lock);
पूर्ण
