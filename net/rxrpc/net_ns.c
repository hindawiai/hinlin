<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* rxrpc network namespace handling.
 *
 * Copyright (C) 2017 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/proc_fs.h>
#समावेश "ar-internal.h"

अचिन्हित पूर्णांक rxrpc_net_id;

अटल व्योम rxrpc_client_conn_reap_समयout(काष्ठा समयr_list *समयr)
अणु
	काष्ठा rxrpc_net *rxnet =
		container_of(समयr, काष्ठा rxrpc_net, client_conn_reap_समयr);

	अगर (rxnet->live)
		rxrpc_queue_work(&rxnet->client_conn_reaper);
पूर्ण

अटल व्योम rxrpc_service_conn_reap_समयout(काष्ठा समयr_list *समयr)
अणु
	काष्ठा rxrpc_net *rxnet =
		container_of(समयr, काष्ठा rxrpc_net, service_conn_reap_समयr);

	अगर (rxnet->live)
		rxrpc_queue_work(&rxnet->service_conn_reaper);
पूर्ण

अटल व्योम rxrpc_peer_keepalive_समयout(काष्ठा समयr_list *समयr)
अणु
	काष्ठा rxrpc_net *rxnet =
		container_of(समयr, काष्ठा rxrpc_net, peer_keepalive_समयr);

	अगर (rxnet->live)
		rxrpc_queue_work(&rxnet->peer_keepalive_work);
पूर्ण

/*
 * Initialise a per-network namespace record.
 */
अटल __net_init पूर्णांक rxrpc_init_net(काष्ठा net *net)
अणु
	काष्ठा rxrpc_net *rxnet = rxrpc_net(net);
	पूर्णांक ret, i;

	rxnet->live = true;
	get_अक्रमom_bytes(&rxnet->epoch, माप(rxnet->epoch));
	rxnet->epoch |= RXRPC_RANDOM_EPOCH;

	INIT_LIST_HEAD(&rxnet->calls);
	rwlock_init(&rxnet->call_lock);
	atomic_set(&rxnet->nr_calls, 1);

	atomic_set(&rxnet->nr_conns, 1);
	INIT_LIST_HEAD(&rxnet->conn_proc_list);
	INIT_LIST_HEAD(&rxnet->service_conns);
	rwlock_init(&rxnet->conn_lock);
	INIT_WORK(&rxnet->service_conn_reaper,
		  rxrpc_service_connection_reaper);
	समयr_setup(&rxnet->service_conn_reap_समयr,
		    rxrpc_service_conn_reap_समयout, 0);

	atomic_set(&rxnet->nr_client_conns, 0);
	rxnet->समाप्त_all_client_conns = false;
	spin_lock_init(&rxnet->client_conn_cache_lock);
	spin_lock_init(&rxnet->client_conn_discard_lock);
	INIT_LIST_HEAD(&rxnet->idle_client_conns);
	INIT_WORK(&rxnet->client_conn_reaper,
		  rxrpc_discard_expired_client_conns);
	समयr_setup(&rxnet->client_conn_reap_समयr,
		    rxrpc_client_conn_reap_समयout, 0);

	INIT_LIST_HEAD(&rxnet->local_endpoपूर्णांकs);
	mutex_init(&rxnet->local_mutex);

	hash_init(rxnet->peer_hash);
	spin_lock_init(&rxnet->peer_hash_lock);
	क्रम (i = 0; i < ARRAY_SIZE(rxnet->peer_keepalive); i++)
		INIT_LIST_HEAD(&rxnet->peer_keepalive[i]);
	INIT_LIST_HEAD(&rxnet->peer_keepalive_new);
	समयr_setup(&rxnet->peer_keepalive_समयr,
		    rxrpc_peer_keepalive_समयout, 0);
	INIT_WORK(&rxnet->peer_keepalive_work, rxrpc_peer_keepalive_worker);
	rxnet->peer_keepalive_base = kसमय_get_seconds();

	ret = -ENOMEM;
	rxnet->proc_net = proc_net_सूची_गढ़ो(net, "rxrpc", net->proc_net);
	अगर (!rxnet->proc_net)
		जाओ err_proc;

	proc_create_net("calls", 0444, rxnet->proc_net, &rxrpc_call_seq_ops,
			माप(काष्ठा seq_net_निजी));
	proc_create_net("conns", 0444, rxnet->proc_net,
			&rxrpc_connection_seq_ops,
			माप(काष्ठा seq_net_निजी));
	proc_create_net("peers", 0444, rxnet->proc_net,
			&rxrpc_peer_seq_ops,
			माप(काष्ठा seq_net_निजी));
	वापस 0;

err_proc:
	rxnet->live = false;
	वापस ret;
पूर्ण

/*
 * Clean up a per-network namespace record.
 */
अटल __net_निकास व्योम rxrpc_निकास_net(काष्ठा net *net)
अणु
	काष्ठा rxrpc_net *rxnet = rxrpc_net(net);

	rxnet->live = false;
	del_समयr_sync(&rxnet->peer_keepalive_समयr);
	cancel_work_sync(&rxnet->peer_keepalive_work);
	rxrpc_destroy_all_calls(rxnet);
	rxrpc_destroy_all_connections(rxnet);
	rxrpc_destroy_all_peers(rxnet);
	rxrpc_destroy_all_locals(rxnet);
	proc_हटाओ(rxnet->proc_net);
पूर्ण

काष्ठा pernet_operations rxrpc_net_ops = अणु
	.init	= rxrpc_init_net,
	.निकास	= rxrpc_निकास_net,
	.id	= &rxrpc_net_id,
	.size	= माप(काष्ठा rxrpc_net),
पूर्ण;
