<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* /proc/net/ support क्रम AF_RXRPC
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/module.h>
#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश "ar-internal.h"

अटल स्थिर अक्षर *स्थिर rxrpc_conn_states[RXRPC_CONN__NR_STATES] = अणु
	[RXRPC_CONN_UNUSED]			= "Unused  ",
	[RXRPC_CONN_CLIENT]			= "Client  ",
	[RXRPC_CONN_SERVICE_PREALLOC]		= "SvPrealc",
	[RXRPC_CONN_SERVICE_UNSECURED]		= "SvUnsec ",
	[RXRPC_CONN_SERVICE_CHALLENGING]	= "SvChall ",
	[RXRPC_CONN_SERVICE]			= "SvSecure",
	[RXRPC_CONN_REMOTELY_ABORTED]		= "RmtAbort",
	[RXRPC_CONN_LOCALLY_ABORTED]		= "LocAbort",
पूर्ण;

/*
 * generate a list of extant and dead calls in /proc/net/rxrpc_calls
 */
अटल व्योम *rxrpc_call_seq_start(काष्ठा seq_file *seq, loff_t *_pos)
	__acquires(rcu)
	__acquires(rxnet->call_lock)
अणु
	काष्ठा rxrpc_net *rxnet = rxrpc_net(seq_file_net(seq));

	rcu_पढ़ो_lock();
	पढ़ो_lock(&rxnet->call_lock);
	वापस seq_list_start_head(&rxnet->calls, *_pos);
पूर्ण

अटल व्योम *rxrpc_call_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा rxrpc_net *rxnet = rxrpc_net(seq_file_net(seq));

	वापस seq_list_next(v, &rxnet->calls, pos);
पूर्ण

अटल व्योम rxrpc_call_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(rxnet->call_lock)
	__releases(rcu)
अणु
	काष्ठा rxrpc_net *rxnet = rxrpc_net(seq_file_net(seq));

	पढ़ो_unlock(&rxnet->call_lock);
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक rxrpc_call_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा rxrpc_local *local;
	काष्ठा rxrpc_sock *rx;
	काष्ठा rxrpc_peer *peer;
	काष्ठा rxrpc_call *call;
	काष्ठा rxrpc_net *rxnet = rxrpc_net(seq_file_net(seq));
	अचिन्हित दीर्घ समयout = 0;
	rxrpc_seq_t tx_hard_ack, rx_hard_ack;
	अक्षर lbuff[50], rbuff[50];

	अगर (v == &rxnet->calls) अणु
		seq_माला_दो(seq,
			 "Proto Local                                          "
			 " Remote                                         "
			 " SvID ConnID   CallID   End Use State    Abort   "
			 " DebugId  TxSeq    TW RxSeq    RW RxSerial RxTimo\n");
		वापस 0;
	पूर्ण

	call = list_entry(v, काष्ठा rxrpc_call, link);

	rx = rcu_dereference(call->socket);
	अगर (rx) अणु
		local = READ_ONCE(rx->local);
		अगर (local)
			प्र_लिखो(lbuff, "%pISpc", &local->srx.transport);
		अन्यथा
			म_नकल(lbuff, "no_local");
	पूर्ण अन्यथा अणु
		म_नकल(lbuff, "no_socket");
	पूर्ण

	peer = call->peer;
	अगर (peer)
		प्र_लिखो(rbuff, "%pISpc", &peer->srx.transport);
	अन्यथा
		म_नकल(rbuff, "no_connection");

	अगर (call->state != RXRPC_CALL_SERVER_PREALLOC) अणु
		समयout = READ_ONCE(call->expect_rx_by);
		समयout -= jअगरfies;
	पूर्ण

	tx_hard_ack = READ_ONCE(call->tx_hard_ack);
	rx_hard_ack = READ_ONCE(call->rx_hard_ack);
	seq_म_लिखो(seq,
		   "UDP   %-47.47s %-47.47s %4x %08x %08x %s %3u"
		   " %-8.8s %08x %08x %08x %02x %08x %02x %08x %06lx\n",
		   lbuff,
		   rbuff,
		   call->service_id,
		   call->cid,
		   call->call_id,
		   rxrpc_is_service_call(call) ? "Svc" : "Clt",
		   atomic_पढ़ो(&call->usage),
		   rxrpc_call_states[call->state],
		   call->पात_code,
		   call->debug_id,
		   tx_hard_ack, READ_ONCE(call->tx_top) - tx_hard_ack,
		   rx_hard_ack, READ_ONCE(call->rx_top) - rx_hard_ack,
		   call->rx_serial,
		   समयout);

	वापस 0;
पूर्ण

स्थिर काष्ठा seq_operations rxrpc_call_seq_ops = अणु
	.start  = rxrpc_call_seq_start,
	.next   = rxrpc_call_seq_next,
	.stop   = rxrpc_call_seq_stop,
	.show   = rxrpc_call_seq_show,
पूर्ण;

/*
 * generate a list of extant भव connections in /proc/net/rxrpc_conns
 */
अटल व्योम *rxrpc_connection_seq_start(काष्ठा seq_file *seq, loff_t *_pos)
	__acquires(rxnet->conn_lock)
अणु
	काष्ठा rxrpc_net *rxnet = rxrpc_net(seq_file_net(seq));

	पढ़ो_lock(&rxnet->conn_lock);
	वापस seq_list_start_head(&rxnet->conn_proc_list, *_pos);
पूर्ण

अटल व्योम *rxrpc_connection_seq_next(काष्ठा seq_file *seq, व्योम *v,
				       loff_t *pos)
अणु
	काष्ठा rxrpc_net *rxnet = rxrpc_net(seq_file_net(seq));

	वापस seq_list_next(v, &rxnet->conn_proc_list, pos);
पूर्ण

अटल व्योम rxrpc_connection_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(rxnet->conn_lock)
अणु
	काष्ठा rxrpc_net *rxnet = rxrpc_net(seq_file_net(seq));

	पढ़ो_unlock(&rxnet->conn_lock);
पूर्ण

अटल पूर्णांक rxrpc_connection_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा rxrpc_connection *conn;
	काष्ठा rxrpc_net *rxnet = rxrpc_net(seq_file_net(seq));
	अक्षर lbuff[50], rbuff[50];

	अगर (v == &rxnet->conn_proc_list) अणु
		seq_माला_दो(seq,
			 "Proto Local                                          "
			 " Remote                                         "
			 " SvID ConnID   End Use State    Key     "
			 " Serial   ISerial  CallId0  CallId1  CallId2  CallId3\n"
			 );
		वापस 0;
	पूर्ण

	conn = list_entry(v, काष्ठा rxrpc_connection, proc_link);
	अगर (conn->state == RXRPC_CONN_SERVICE_PREALLOC) अणु
		म_नकल(lbuff, "no_local");
		म_नकल(rbuff, "no_connection");
		जाओ prपूर्णांक;
	पूर्ण

	प्र_लिखो(lbuff, "%pISpc", &conn->params.local->srx.transport);

	प्र_लिखो(rbuff, "%pISpc", &conn->params.peer->srx.transport);
prपूर्णांक:
	seq_म_लिखो(seq,
		   "UDP   %-47.47s %-47.47s %4x %08x %s %3u"
		   " %s %08x %08x %08x %08x %08x %08x %08x\n",
		   lbuff,
		   rbuff,
		   conn->service_id,
		   conn->proto.cid,
		   rxrpc_conn_is_service(conn) ? "Svc" : "Clt",
		   atomic_पढ़ो(&conn->usage),
		   rxrpc_conn_states[conn->state],
		   key_serial(conn->params.key),
		   atomic_पढ़ो(&conn->serial),
		   conn->hi_serial,
		   conn->channels[0].call_id,
		   conn->channels[1].call_id,
		   conn->channels[2].call_id,
		   conn->channels[3].call_id);

	वापस 0;
पूर्ण

स्थिर काष्ठा seq_operations rxrpc_connection_seq_ops = अणु
	.start  = rxrpc_connection_seq_start,
	.next   = rxrpc_connection_seq_next,
	.stop   = rxrpc_connection_seq_stop,
	.show   = rxrpc_connection_seq_show,
पूर्ण;

/*
 * generate a list of extant भव peers in /proc/net/rxrpc/peers
 */
अटल पूर्णांक rxrpc_peer_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा rxrpc_peer *peer;
	समय64_t now;
	अक्षर lbuff[50], rbuff[50];

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq,
			 "Proto Local                                          "
			 " Remote                                         "
			 " Use  CW   MTU LastUse      RTT      RTO\n"
			 );
		वापस 0;
	पूर्ण

	peer = list_entry(v, काष्ठा rxrpc_peer, hash_link);

	प्र_लिखो(lbuff, "%pISpc", &peer->local->srx.transport);

	प्र_लिखो(rbuff, "%pISpc", &peer->srx.transport);

	now = kसमय_get_seconds();
	seq_म_लिखो(seq,
		   "UDP   %-47.47s %-47.47s %3u"
		   " %3u %5u %6llus %8u %8u\n",
		   lbuff,
		   rbuff,
		   atomic_पढ़ो(&peer->usage),
		   peer->cong_cwnd,
		   peer->mtu,
		   now - peer->last_tx_at,
		   peer->srtt_us >> 3,
		   jअगरfies_to_usecs(peer->rto_j));

	वापस 0;
पूर्ण

अटल व्योम *rxrpc_peer_seq_start(काष्ठा seq_file *seq, loff_t *_pos)
	__acquires(rcu)
अणु
	काष्ठा rxrpc_net *rxnet = rxrpc_net(seq_file_net(seq));
	अचिन्हित पूर्णांक bucket, n;
	अचिन्हित पूर्णांक shअगरt = 32 - HASH_BITS(rxnet->peer_hash);
	व्योम *p;

	rcu_पढ़ो_lock();

	अगर (*_pos >= अच_पूर्णांक_उच्च)
		वापस शून्य;

	n = *_pos & ((1U << shअगरt) - 1);
	bucket = *_pos >> shअगरt;
	क्रम (;;) अणु
		अगर (bucket >= HASH_SIZE(rxnet->peer_hash)) अणु
			*_pos = अच_पूर्णांक_उच्च;
			वापस शून्य;
		पूर्ण
		अगर (n == 0) अणु
			अगर (bucket == 0)
				वापस SEQ_START_TOKEN;
			*_pos += 1;
			n++;
		पूर्ण

		p = seq_hlist_start_rcu(&rxnet->peer_hash[bucket], n - 1);
		अगर (p)
			वापस p;
		bucket++;
		n = 1;
		*_pos = (bucket << shअगरt) | n;
	पूर्ण
पूर्ण

अटल व्योम *rxrpc_peer_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *_pos)
अणु
	काष्ठा rxrpc_net *rxnet = rxrpc_net(seq_file_net(seq));
	अचिन्हित पूर्णांक bucket, n;
	अचिन्हित पूर्णांक shअगरt = 32 - HASH_BITS(rxnet->peer_hash);
	व्योम *p;

	अगर (*_pos >= अच_पूर्णांक_उच्च)
		वापस शून्य;

	bucket = *_pos >> shअगरt;

	p = seq_hlist_next_rcu(v, &rxnet->peer_hash[bucket], _pos);
	अगर (p)
		वापस p;

	क्रम (;;) अणु
		bucket++;
		n = 1;
		*_pos = (bucket << shअगरt) | n;

		अगर (bucket >= HASH_SIZE(rxnet->peer_hash)) अणु
			*_pos = अच_पूर्णांक_उच्च;
			वापस शून्य;
		पूर्ण
		अगर (n == 0) अणु
			*_pos += 1;
			n++;
		पूर्ण

		p = seq_hlist_start_rcu(&rxnet->peer_hash[bucket], n - 1);
		अगर (p)
			वापस p;
	पूर्ण
पूर्ण

अटल व्योम rxrpc_peer_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(rcu)
अणु
	rcu_पढ़ो_unlock();
पूर्ण


स्थिर काष्ठा seq_operations rxrpc_peer_seq_ops = अणु
	.start  = rxrpc_peer_seq_start,
	.next   = rxrpc_peer_seq_next,
	.stop   = rxrpc_peer_seq_stop,
	.show   = rxrpc_peer_seq_show,
पूर्ण;
