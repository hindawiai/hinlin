<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Local endpoपूर्णांक object management
 *
 * Copyright (C) 2016 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/udp.h>
#समावेश <linux/ip.h>
#समावेश <linux/hashtable.h>
#समावेश <net/sock.h>
#समावेश <net/udp.h>
#समावेश <net/udp_tunnel.h>
#समावेश <net/af_rxrpc.h>
#समावेश "ar-internal.h"

अटल व्योम rxrpc_local_processor(काष्ठा work_काष्ठा *);
अटल व्योम rxrpc_local_rcu(काष्ठा rcu_head *);

/*
 * Compare a local to an address.  Return -ve, 0 or +ve to indicate less than,
 * same or greater than.
 *
 * We explicitly करोn't compare the RxRPC service ID as we want to reject
 * conflicting uses by dअगरfering services.  Further, we करोn't want to share
 * addresses with dअगरferent options (IPv6), so we करोn't compare those bits
 * either.
 */
अटल दीर्घ rxrpc_local_cmp_key(स्थिर काष्ठा rxrpc_local *local,
				स्थिर काष्ठा sockaddr_rxrpc *srx)
अणु
	दीर्घ dअगरf;

	dअगरf = ((local->srx.transport_type - srx->transport_type) ?:
		(local->srx.transport_len - srx->transport_len) ?:
		(local->srx.transport.family - srx->transport.family));
	अगर (dअगरf != 0)
		वापस dअगरf;

	चयन (srx->transport.family) अणु
	हाल AF_INET:
		/* If the choice of UDP port is left up to the transport, then
		 * the endpoपूर्णांक record करोesn't match.
		 */
		वापस ((u16 __क्रमce)local->srx.transport.sin.sin_port -
			(u16 __क्रमce)srx->transport.sin.sin_port) ?:
			स_भेद(&local->srx.transport.sin.sin_addr,
			       &srx->transport.sin.sin_addr,
			       माप(काष्ठा in_addr));
#अगर_घोषित CONFIG_AF_RXRPC_IPV6
	हाल AF_INET6:
		/* If the choice of UDP6 port is left up to the transport, then
		 * the endpoपूर्णांक record करोesn't match.
		 */
		वापस ((u16 __क्रमce)local->srx.transport.sin6.sin6_port -
			(u16 __क्रमce)srx->transport.sin6.sin6_port) ?:
			स_भेद(&local->srx.transport.sin6.sin6_addr,
			       &srx->transport.sin6.sin6_addr,
			       माप(काष्ठा in6_addr));
#पूर्ण_अगर
	शेष:
		BUG();
	पूर्ण
पूर्ण

/*
 * Allocate a new local endpoपूर्णांक.
 */
अटल काष्ठा rxrpc_local *rxrpc_alloc_local(काष्ठा rxrpc_net *rxnet,
					     स्थिर काष्ठा sockaddr_rxrpc *srx)
अणु
	काष्ठा rxrpc_local *local;

	local = kzalloc(माप(काष्ठा rxrpc_local), GFP_KERNEL);
	अगर (local) अणु
		atomic_set(&local->usage, 1);
		atomic_set(&local->active_users, 1);
		local->rxnet = rxnet;
		INIT_LIST_HEAD(&local->link);
		INIT_WORK(&local->processor, rxrpc_local_processor);
		init_rwsem(&local->defrag_sem);
		skb_queue_head_init(&local->reject_queue);
		skb_queue_head_init(&local->event_queue);
		local->client_bundles = RB_ROOT;
		spin_lock_init(&local->client_bundles_lock);
		spin_lock_init(&local->lock);
		rwlock_init(&local->services_lock);
		local->debug_id = atomic_inc_वापस(&rxrpc_debug_id);
		स_नकल(&local->srx, srx, माप(*srx));
		local->srx.srx_service = 0;
		trace_rxrpc_local(local->debug_id, rxrpc_local_new, 1, शून्य);
	पूर्ण

	_leave(" = %p", local);
	वापस local;
पूर्ण

/*
 * create the local socket
 * - must be called with rxrpc_local_mutex locked
 */
अटल पूर्णांक rxrpc_खोलो_socket(काष्ठा rxrpc_local *local, काष्ठा net *net)
अणु
	काष्ठा udp_tunnel_sock_cfg tuncfg = अणुशून्यपूर्ण;
	काष्ठा sockaddr_rxrpc *srx = &local->srx;
	काष्ठा udp_port_cfg udp_conf = अणु0पूर्ण;
	काष्ठा sock *usk;
	पूर्णांक ret;

	_enter("%p{%d,%d}",
	       local, srx->transport_type, srx->transport.family);

	udp_conf.family = srx->transport.family;
	अगर (udp_conf.family == AF_INET) अणु
		udp_conf.local_ip = srx->transport.sin.sin_addr;
		udp_conf.local_udp_port = srx->transport.sin.sin_port;
#अगर IS_ENABLED(CONFIG_AF_RXRPC_IPV6)
	पूर्ण अन्यथा अणु
		udp_conf.local_ip6 = srx->transport.sin6.sin6_addr;
		udp_conf.local_udp_port = srx->transport.sin6.sin6_port;
#पूर्ण_अगर
	पूर्ण
	ret = udp_sock_create(net, &udp_conf, &local->socket);
	अगर (ret < 0) अणु
		_leave(" = %d [socket]", ret);
		वापस ret;
	पूर्ण

	tuncfg.encap_type = UDP_ENCAP_RXRPC;
	tuncfg.encap_rcv = rxrpc_input_packet;
	tuncfg.sk_user_data = local;
	setup_udp_tunnel_sock(net, local->socket, &tuncfg);

	/* set the socket up */
	usk = local->socket->sk;
	usk->sk_error_report = rxrpc_error_report;

	चयन (srx->transport.family) अणु
	हाल AF_INET6:
		/* we want to receive ICMPv6 errors */
		ip6_sock_set_recverr(usk);

		/* Fall through and set IPv4 options too otherwise we करोn't get
		 * errors from IPv4 packets sent through the IPv6 socket.
		 */
		fallthrough;
	हाल AF_INET:
		/* we want to receive ICMP errors */
		ip_sock_set_recverr(usk);

		/* we want to set the करोn't fragment bit */
		ip_sock_set_mtu_discover(usk, IP_PMTUDISC_DO);

		/* We want receive बारtamps. */
		sock_enable_बारtamps(usk);
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	_leave(" = 0");
	वापस 0;
पूर्ण

/*
 * Look up or create a new local endpoपूर्णांक using the specअगरied local address.
 */
काष्ठा rxrpc_local *rxrpc_lookup_local(काष्ठा net *net,
				       स्थिर काष्ठा sockaddr_rxrpc *srx)
अणु
	काष्ठा rxrpc_local *local;
	काष्ठा rxrpc_net *rxnet = rxrpc_net(net);
	काष्ठा list_head *cursor;
	स्थिर अक्षर *age;
	दीर्घ dअगरf;
	पूर्णांक ret;

	_enter("{%d,%d,%pISp}",
	       srx->transport_type, srx->transport.family, &srx->transport);

	mutex_lock(&rxnet->local_mutex);

	क्रम (cursor = rxnet->local_endpoपूर्णांकs.next;
	     cursor != &rxnet->local_endpoपूर्णांकs;
	     cursor = cursor->next) अणु
		local = list_entry(cursor, काष्ठा rxrpc_local, link);

		dअगरf = rxrpc_local_cmp_key(local, srx);
		अगर (dअगरf < 0)
			जारी;
		अगर (dअगरf > 0)
			अवरोध;

		/* Services aren't allowed to share transport sockets, so
		 * reject that here.  It is possible that the object is dying -
		 * but it may also still have the local transport address that
		 * we want bound.
		 */
		अगर (srx->srx_service) अणु
			local = शून्य;
			जाओ addr_in_use;
		पूर्ण

		/* Found a match.  We replace a dying object.  Attempting to
		 * bind the transport socket may still fail अगर we're attempting
		 * to use a local address that the dying object is still using.
		 */
		अगर (!rxrpc_use_local(local))
			अवरोध;

		age = "old";
		जाओ found;
	पूर्ण

	local = rxrpc_alloc_local(rxnet, srx);
	अगर (!local)
		जाओ nomem;

	ret = rxrpc_खोलो_socket(local, net);
	अगर (ret < 0)
		जाओ sock_error;

	अगर (cursor != &rxnet->local_endpoपूर्णांकs)
		list_replace_init(cursor, &local->link);
	अन्यथा
		list_add_tail(&local->link, cursor);
	age = "new";

found:
	mutex_unlock(&rxnet->local_mutex);

	_net("LOCAL %s %d {%pISp}",
	     age, local->debug_id, &local->srx.transport);

	_leave(" = %p", local);
	वापस local;

nomem:
	ret = -ENOMEM;
sock_error:
	mutex_unlock(&rxnet->local_mutex);
	अगर (local)
		call_rcu(&local->rcu, rxrpc_local_rcu);
	_leave(" = %d", ret);
	वापस ERR_PTR(ret);

addr_in_use:
	mutex_unlock(&rxnet->local_mutex);
	_leave(" = -EADDRINUSE");
	वापस ERR_PTR(-EADDRINUSE);
पूर्ण

/*
 * Get a ref on a local endpoपूर्णांक.
 */
काष्ठा rxrpc_local *rxrpc_get_local(काष्ठा rxrpc_local *local)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	पूर्णांक n;

	n = atomic_inc_वापस(&local->usage);
	trace_rxrpc_local(local->debug_id, rxrpc_local_got, n, here);
	वापस local;
पूर्ण

/*
 * Get a ref on a local endpoपूर्णांक unless its usage has alपढ़ोy reached 0.
 */
काष्ठा rxrpc_local *rxrpc_get_local_maybe(काष्ठा rxrpc_local *local)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);

	अगर (local) अणु
		पूर्णांक n = atomic_fetch_add_unless(&local->usage, 1, 0);
		अगर (n > 0)
			trace_rxrpc_local(local->debug_id, rxrpc_local_got,
					  n + 1, here);
		अन्यथा
			local = शून्य;
	पूर्ण
	वापस local;
पूर्ण

/*
 * Queue a local endpoपूर्णांक and pass the caller's reference to the work item.
 */
व्योम rxrpc_queue_local(काष्ठा rxrpc_local *local)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	अचिन्हित पूर्णांक debug_id = local->debug_id;
	पूर्णांक n = atomic_पढ़ो(&local->usage);

	अगर (rxrpc_queue_work(&local->processor))
		trace_rxrpc_local(debug_id, rxrpc_local_queued, n, here);
	अन्यथा
		rxrpc_put_local(local);
पूर्ण

/*
 * Drop a ref on a local endpoपूर्णांक.
 */
व्योम rxrpc_put_local(काष्ठा rxrpc_local *local)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	अचिन्हित पूर्णांक debug_id;
	पूर्णांक n;

	अगर (local) अणु
		debug_id = local->debug_id;

		n = atomic_dec_वापस(&local->usage);
		trace_rxrpc_local(debug_id, rxrpc_local_put, n, here);

		अगर (n == 0)
			call_rcu(&local->rcu, rxrpc_local_rcu);
	पूर्ण
पूर्ण

/*
 * Start using a local endpoपूर्णांक.
 */
काष्ठा rxrpc_local *rxrpc_use_local(काष्ठा rxrpc_local *local)
अणु
	local = rxrpc_get_local_maybe(local);
	अगर (!local)
		वापस शून्य;

	अगर (!__rxrpc_use_local(local)) अणु
		rxrpc_put_local(local);
		वापस शून्य;
	पूर्ण

	वापस local;
पूर्ण

/*
 * Cease using a local endpoपूर्णांक.  Once the number of active users reaches 0, we
 * start the closure of the transport in the work processor.
 */
व्योम rxrpc_unuse_local(काष्ठा rxrpc_local *local)
अणु
	अगर (local) अणु
		अगर (__rxrpc_unuse_local(local)) अणु
			rxrpc_get_local(local);
			rxrpc_queue_local(local);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Destroy a local endpoपूर्णांक's socket and then hand the record to RCU to dispose
 * of.
 *
 * Closing the socket cannot be करोne from bottom half context or RCU callback
 * context because it might sleep.
 */
अटल व्योम rxrpc_local_destroyer(काष्ठा rxrpc_local *local)
अणु
	काष्ठा socket *socket = local->socket;
	काष्ठा rxrpc_net *rxnet = local->rxnet;

	_enter("%d", local->debug_id);

	local->dead = true;

	mutex_lock(&rxnet->local_mutex);
	list_del_init(&local->link);
	mutex_unlock(&rxnet->local_mutex);

	rxrpc_clean_up_local_conns(local);
	rxrpc_service_connection_reaper(&rxnet->service_conn_reaper);
	ASSERT(!local->service);

	अगर (socket) अणु
		local->socket = शून्य;
		kernel_sock_shutकरोwn(socket, SHUT_RDWR);
		socket->sk->sk_user_data = शून्य;
		sock_release(socket);
	पूर्ण

	/* At this poपूर्णांक, there should be no more packets coming in to the
	 * local endpoपूर्णांक.
	 */
	rxrpc_purge_queue(&local->reject_queue);
	rxrpc_purge_queue(&local->event_queue);
पूर्ण

/*
 * Process events on an endpoपूर्णांक.  The work item carries a ref which
 * we must release.
 */
अटल व्योम rxrpc_local_processor(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rxrpc_local *local =
		container_of(work, काष्ठा rxrpc_local, processor);
	bool again;

	trace_rxrpc_local(local->debug_id, rxrpc_local_processing,
			  atomic_पढ़ो(&local->usage), शून्य);

	करो अणु
		again = false;
		अगर (!__rxrpc_use_local(local)) अणु
			rxrpc_local_destroyer(local);
			अवरोध;
		पूर्ण

		अगर (!skb_queue_empty(&local->reject_queue)) अणु
			rxrpc_reject_packets(local);
			again = true;
		पूर्ण

		अगर (!skb_queue_empty(&local->event_queue)) अणु
			rxrpc_process_local_events(local);
			again = true;
		पूर्ण

		__rxrpc_unuse_local(local);
	पूर्ण जबतक (again);

	rxrpc_put_local(local);
पूर्ण

/*
 * Destroy a local endpoपूर्णांक after the RCU grace period expires.
 */
अटल व्योम rxrpc_local_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा rxrpc_local *local = container_of(rcu, काष्ठा rxrpc_local, rcu);

	_enter("%d", local->debug_id);

	ASSERT(!work_pending(&local->processor));

	_net("DESTROY LOCAL %d", local->debug_id);
	kमुक्त(local);
	_leave("");
पूर्ण

/*
 * Verअगरy the local endpoपूर्णांक list is empty by this poपूर्णांक.
 */
व्योम rxrpc_destroy_all_locals(काष्ठा rxrpc_net *rxnet)
अणु
	काष्ठा rxrpc_local *local;

	_enter("");

	flush_workqueue(rxrpc_workqueue);

	अगर (!list_empty(&rxnet->local_endpoपूर्णांकs)) अणु
		mutex_lock(&rxnet->local_mutex);
		list_क्रम_each_entry(local, &rxnet->local_endpoपूर्णांकs, link) अणु
			pr_err("AF_RXRPC: Leaked local %p {%d}\n",
			       local, atomic_पढ़ो(&local->usage));
		पूर्ण
		mutex_unlock(&rxnet->local_mutex);
		BUG();
	पूर्ण
पूर्ण
