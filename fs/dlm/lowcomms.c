<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) Sistina Software, Inc.  1997-2003  All rights reserved.
**  Copyright (C) 2004-2009 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

/*
 * lowcomms.c
 *
 * This is the "low-level" comms layer.
 *
 * It is responsible क्रम sending/receiving messages
 * from other nodes in the cluster.
 *
 * Cluster nodes are referred to by their nodeids. nodeids are
 * simply 32 bit numbers to the locking module - अगर they need to
 * be expanded क्रम the cluster infraकाष्ठाure then that is its
 * responsibility. It is this layer's
 * responsibility to resolve these पूर्णांकo IP address or
 * whatever it needs क्रम पूर्णांकer-node communication.
 *
 * The comms level is two kernel thपढ़ोs that deal मुख्यly with
 * the receiving of messages from other nodes and passing them
 * up to the mid-level comms layer (which understands the
 * message क्रमmat) क्रम execution by the locking core, and
 * a send thपढ़ो which करोes all the setting up of connections
 * to remote nodes and the sending of data. Thपढ़ोs are not allowed
 * to send their own data because it may cause them to रुको in बार
 * of high load. Also, this way, the sending thपढ़ो can collect together
 * messages bound क्रम one node and send them in one block.
 *
 * lowcomms will choose to use either TCP or SCTP as its transport layer
 * depending on the configuration variable 'protocol'. This should be set
 * to 0 (शेष) क्रम TCP or 1 क्रम SCTP. It should be configured using a
 * cluster-wide mechanism as it must be the same on all nodes of the cluster
 * क्रम the DLM to function.
 *
 */

#समावेश <यंत्र/ioctls.h>
#समावेश <net/sock.h>
#समावेश <net/tcp.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/file.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sctp.h>
#समावेश <linux/slab.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/ipv6.h>

#समावेश "dlm_internal.h"
#समावेश "lowcomms.h"
#समावेश "midcomms.h"
#समावेश "config.h"

#घोषणा NEEDED_RMEM (4*1024*1024)
#घोषणा CONN_HASH_SIZE 32

/* Number of messages to send beक्रमe rescheduling */
#घोषणा MAX_SEND_MSG_COUNT 25
#घोषणा DLM_SHUTDOWN_WAIT_TIMEOUT msecs_to_jअगरfies(10000)

काष्ठा connection अणु
	काष्ठा socket *sock;	/* शून्य अगर not connected */
	uपूर्णांक32_t nodeid;	/* So we know who we are in the list */
	काष्ठा mutex sock_mutex;
	अचिन्हित दीर्घ flags;
#घोषणा CF_READ_PENDING 1
#घोषणा CF_WRITE_PENDING 2
#घोषणा CF_INIT_PENDING 4
#घोषणा CF_IS_OTHERCON 5
#घोषणा CF_CLOSE 6
#घोषणा CF_APP_LIMITED 7
#घोषणा CF_CLOSING 8
#घोषणा CF_SHUTDOWN 9
#घोषणा CF_CONNECTED 10
	काष्ठा list_head ग_लिखोqueue;  /* List of outgoing ग_लिखोqueue_entries */
	spinlock_t ग_लिखोqueue_lock;
	व्योम (*connect_action) (काष्ठा connection *);	/* What to करो to connect */
	व्योम (*shutकरोwn_action)(काष्ठा connection *con); /* What to करो to shutकरोwn */
	पूर्णांक retries;
#घोषणा MAX_CONNECT_RETRIES 3
	काष्ठा hlist_node list;
	काष्ठा connection *othercon;
	काष्ठा work_काष्ठा rwork; /* Receive workqueue */
	काष्ठा work_काष्ठा swork; /* Send workqueue */
	रुको_queue_head_t shutकरोwn_रुको; /* रुको क्रम graceful shutकरोwn */
	अचिन्हित अक्षर *rx_buf;
	पूर्णांक rx_buflen;
	पूर्णांक rx_leftover;
	काष्ठा rcu_head rcu;
पूर्ण;
#घोषणा sock2con(x) ((काष्ठा connection *)(x)->sk_user_data)

काष्ठा listen_connection अणु
	काष्ठा socket *sock;
	काष्ठा work_काष्ठा rwork;
पूर्ण;

#घोषणा DLM_WQ_REMAIN_BYTES(e) (PAGE_SIZE - e->end)
#घोषणा DLM_WQ_LENGTH_BYTES(e) (e->end - e->offset)

/* An entry रुकोing to be sent */
काष्ठा ग_लिखोqueue_entry अणु
	काष्ठा list_head list;
	काष्ठा page *page;
	पूर्णांक offset;
	पूर्णांक len;
	पूर्णांक end;
	पूर्णांक users;
	काष्ठा connection *con;
पूर्ण;

काष्ठा dlm_node_addr अणु
	काष्ठा list_head list;
	पूर्णांक nodeid;
	पूर्णांक mark;
	पूर्णांक addr_count;
	पूर्णांक curr_addr_index;
	काष्ठा sockaddr_storage *addr[DLM_MAX_ADDR_COUNT];
पूर्ण;

अटल काष्ठा listen_sock_callbacks अणु
	व्योम (*sk_error_report)(काष्ठा sock *);
	व्योम (*sk_data_पढ़ोy)(काष्ठा sock *);
	व्योम (*sk_state_change)(काष्ठा sock *);
	व्योम (*sk_ग_लिखो_space)(काष्ठा sock *);
पूर्ण listen_sock;

अटल LIST_HEAD(dlm_node_addrs);
अटल DEFINE_SPINLOCK(dlm_node_addrs_spin);

अटल काष्ठा listen_connection listen_con;
अटल काष्ठा sockaddr_storage *dlm_local_addr[DLM_MAX_ADDR_COUNT];
अटल पूर्णांक dlm_local_count;
पूर्णांक dlm_allow_conn;

/* Work queues */
अटल काष्ठा workqueue_काष्ठा *recv_workqueue;
अटल काष्ठा workqueue_काष्ठा *send_workqueue;

अटल काष्ठा hlist_head connection_hash[CONN_HASH_SIZE];
अटल DEFINE_SPINLOCK(connections_lock);
DEFINE_STATIC_SRCU(connections_srcu);

अटल व्योम process_recv_sockets(काष्ठा work_काष्ठा *work);
अटल व्योम process_send_sockets(काष्ठा work_काष्ठा *work);

अटल व्योम sctp_connect_to_sock(काष्ठा connection *con);
अटल व्योम tcp_connect_to_sock(काष्ठा connection *con);
अटल व्योम dlm_tcp_shutकरोwn(काष्ठा connection *con);

/* This is deliberately very simple because most clusters have simple
   sequential nodeids, so we should be able to go straight to a connection
   काष्ठा in the array */
अटल अंतरभूत पूर्णांक nodeid_hash(पूर्णांक nodeid)
अणु
	वापस nodeid & (CONN_HASH_SIZE-1);
पूर्ण

अटल काष्ठा connection *__find_con(पूर्णांक nodeid)
अणु
	पूर्णांक r, idx;
	काष्ठा connection *con;

	r = nodeid_hash(nodeid);

	idx = srcu_पढ़ो_lock(&connections_srcu);
	hlist_क्रम_each_entry_rcu(con, &connection_hash[r], list) अणु
		अगर (con->nodeid == nodeid) अणु
			srcu_पढ़ो_unlock(&connections_srcu, idx);
			वापस con;
		पूर्ण
	पूर्ण
	srcu_पढ़ो_unlock(&connections_srcu, idx);

	वापस शून्य;
पूर्ण

अटल पूर्णांक dlm_con_init(काष्ठा connection *con, पूर्णांक nodeid)
अणु
	con->rx_buflen = dlm_config.ci_buffer_size;
	con->rx_buf = kदो_स्मृति(con->rx_buflen, GFP_NOFS);
	अगर (!con->rx_buf)
		वापस -ENOMEM;

	con->nodeid = nodeid;
	mutex_init(&con->sock_mutex);
	INIT_LIST_HEAD(&con->ग_लिखोqueue);
	spin_lock_init(&con->ग_लिखोqueue_lock);
	INIT_WORK(&con->swork, process_send_sockets);
	INIT_WORK(&con->rwork, process_recv_sockets);
	init_रुकोqueue_head(&con->shutकरोwn_रुको);

	अगर (dlm_config.ci_protocol == 0) अणु
		con->connect_action = tcp_connect_to_sock;
		con->shutकरोwn_action = dlm_tcp_shutकरोwn;
	पूर्ण अन्यथा अणु
		con->connect_action = sctp_connect_to_sock;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * If 'allocation' is zero then we don't attempt to create a new
 * connection काष्ठाure क्रम this node.
 */
अटल काष्ठा connection *nodeid2con(पूर्णांक nodeid, gfp_t alloc)
अणु
	काष्ठा connection *con, *पंचांगp;
	पूर्णांक r, ret;

	con = __find_con(nodeid);
	अगर (con || !alloc)
		वापस con;

	con = kzalloc(माप(*con), alloc);
	अगर (!con)
		वापस शून्य;

	ret = dlm_con_init(con, nodeid);
	अगर (ret) अणु
		kमुक्त(con);
		वापस शून्य;
	पूर्ण

	r = nodeid_hash(nodeid);

	spin_lock(&connections_lock);
	/* Because multiple workqueues/thपढ़ोs calls this function it can
	 * race on multiple cpu's. Instead of locking hot path __find_con()
	 * we just check in rare हालs of recently added nodes again
	 * under protection of connections_lock. If this is the हाल we
	 * पात our connection creation and वापस the existing connection.
	 */
	पंचांगp = __find_con(nodeid);
	अगर (पंचांगp) अणु
		spin_unlock(&connections_lock);
		kमुक्त(con->rx_buf);
		kमुक्त(con);
		वापस पंचांगp;
	पूर्ण

	hlist_add_head_rcu(&con->list, &connection_hash[r]);
	spin_unlock(&connections_lock);

	वापस con;
पूर्ण

/* Loop round all connections */
अटल व्योम क्रमeach_conn(व्योम (*conn_func)(काष्ठा connection *c))
अणु
	पूर्णांक i, idx;
	काष्ठा connection *con;

	idx = srcu_पढ़ो_lock(&connections_srcu);
	क्रम (i = 0; i < CONN_HASH_SIZE; i++) अणु
		hlist_क्रम_each_entry_rcu(con, &connection_hash[i], list)
			conn_func(con);
	पूर्ण
	srcu_पढ़ो_unlock(&connections_srcu, idx);
पूर्ण

अटल काष्ठा dlm_node_addr *find_node_addr(पूर्णांक nodeid)
अणु
	काष्ठा dlm_node_addr *na;

	list_क्रम_each_entry(na, &dlm_node_addrs, list) अणु
		अगर (na->nodeid == nodeid)
			वापस na;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक addr_compare(स्थिर काष्ठा sockaddr_storage *x,
			स्थिर काष्ठा sockaddr_storage *y)
अणु
	चयन (x->ss_family) अणु
	हाल AF_INET: अणु
		काष्ठा sockaddr_in *sinx = (काष्ठा sockaddr_in *)x;
		काष्ठा sockaddr_in *siny = (काष्ठा sockaddr_in *)y;
		अगर (sinx->sin_addr.s_addr != siny->sin_addr.s_addr)
			वापस 0;
		अगर (sinx->sin_port != siny->sin_port)
			वापस 0;
		अवरोध;
	पूर्ण
	हाल AF_INET6: अणु
		काष्ठा sockaddr_in6 *sinx = (काष्ठा sockaddr_in6 *)x;
		काष्ठा sockaddr_in6 *siny = (काष्ठा sockaddr_in6 *)y;
		अगर (!ipv6_addr_equal(&sinx->sin6_addr, &siny->sin6_addr))
			वापस 0;
		अगर (sinx->sin6_port != siny->sin6_port)
			वापस 0;
		अवरोध;
	पूर्ण
	शेष:
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक nodeid_to_addr(पूर्णांक nodeid, काष्ठा sockaddr_storage *sas_out,
			  काष्ठा sockaddr *sa_out, bool try_new_addr,
			  अचिन्हित पूर्णांक *mark)
अणु
	काष्ठा sockaddr_storage sas;
	काष्ठा dlm_node_addr *na;

	अगर (!dlm_local_count)
		वापस -1;

	spin_lock(&dlm_node_addrs_spin);
	na = find_node_addr(nodeid);
	अगर (na && na->addr_count) अणु
		स_नकल(&sas, na->addr[na->curr_addr_index],
		       माप(काष्ठा sockaddr_storage));

		अगर (try_new_addr) अणु
			na->curr_addr_index++;
			अगर (na->curr_addr_index == na->addr_count)
				na->curr_addr_index = 0;
		पूर्ण
	पूर्ण
	spin_unlock(&dlm_node_addrs_spin);

	अगर (!na)
		वापस -EEXIST;

	अगर (!na->addr_count)
		वापस -ENOENT;

	*mark = na->mark;

	अगर (sas_out)
		स_नकल(sas_out, &sas, माप(काष्ठा sockaddr_storage));

	अगर (!sa_out)
		वापस 0;

	अगर (dlm_local_addr[0]->ss_family == AF_INET) अणु
		काष्ठा sockaddr_in *in4  = (काष्ठा sockaddr_in *) &sas;
		काष्ठा sockaddr_in *ret4 = (काष्ठा sockaddr_in *) sa_out;
		ret4->sin_addr.s_addr = in4->sin_addr.s_addr;
	पूर्ण अन्यथा अणु
		काष्ठा sockaddr_in6 *in6  = (काष्ठा sockaddr_in6 *) &sas;
		काष्ठा sockaddr_in6 *ret6 = (काष्ठा sockaddr_in6 *) sa_out;
		ret6->sin6_addr = in6->sin6_addr;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक addr_to_nodeid(काष्ठा sockaddr_storage *addr, पूर्णांक *nodeid,
			  अचिन्हित पूर्णांक *mark)
अणु
	काष्ठा dlm_node_addr *na;
	पूर्णांक rv = -EEXIST;
	पूर्णांक addr_i;

	spin_lock(&dlm_node_addrs_spin);
	list_क्रम_each_entry(na, &dlm_node_addrs, list) अणु
		अगर (!na->addr_count)
			जारी;

		क्रम (addr_i = 0; addr_i < na->addr_count; addr_i++) अणु
			अगर (addr_compare(na->addr[addr_i], addr)) अणु
				*nodeid = na->nodeid;
				*mark = na->mark;
				rv = 0;
				जाओ unlock;
			पूर्ण
		पूर्ण
	पूर्ण
unlock:
	spin_unlock(&dlm_node_addrs_spin);
	वापस rv;
पूर्ण

/* caller need to held dlm_node_addrs_spin lock */
अटल bool dlm_lowcomms_na_has_addr(स्थिर काष्ठा dlm_node_addr *na,
				     स्थिर काष्ठा sockaddr_storage *addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < na->addr_count; i++) अणु
		अगर (addr_compare(na->addr[i], addr))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक dlm_lowcomms_addr(पूर्णांक nodeid, काष्ठा sockaddr_storage *addr, पूर्णांक len)
अणु
	काष्ठा sockaddr_storage *new_addr;
	काष्ठा dlm_node_addr *new_node, *na;
	bool ret;

	new_node = kzalloc(माप(काष्ठा dlm_node_addr), GFP_NOFS);
	अगर (!new_node)
		वापस -ENOMEM;

	new_addr = kzalloc(माप(काष्ठा sockaddr_storage), GFP_NOFS);
	अगर (!new_addr) अणु
		kमुक्त(new_node);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(new_addr, addr, len);

	spin_lock(&dlm_node_addrs_spin);
	na = find_node_addr(nodeid);
	अगर (!na) अणु
		new_node->nodeid = nodeid;
		new_node->addr[0] = new_addr;
		new_node->addr_count = 1;
		new_node->mark = dlm_config.ci_mark;
		list_add(&new_node->list, &dlm_node_addrs);
		spin_unlock(&dlm_node_addrs_spin);
		वापस 0;
	पूर्ण

	ret = dlm_lowcomms_na_has_addr(na, addr);
	अगर (ret) अणु
		spin_unlock(&dlm_node_addrs_spin);
		kमुक्त(new_addr);
		kमुक्त(new_node);
		वापस -EEXIST;
	पूर्ण

	अगर (na->addr_count >= DLM_MAX_ADDR_COUNT) अणु
		spin_unlock(&dlm_node_addrs_spin);
		kमुक्त(new_addr);
		kमुक्त(new_node);
		वापस -ENOSPC;
	पूर्ण

	na->addr[na->addr_count++] = new_addr;
	spin_unlock(&dlm_node_addrs_spin);
	kमुक्त(new_node);
	वापस 0;
पूर्ण

/* Data available on socket or listen socket received a connect */
अटल व्योम lowcomms_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा connection *con;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	con = sock2con(sk);
	अगर (con && !test_and_set_bit(CF_READ_PENDING, &con->flags))
		queue_work(recv_workqueue, &con->rwork);
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल व्योम lowcomms_listen_data_पढ़ोy(काष्ठा sock *sk)
अणु
	queue_work(recv_workqueue, &listen_con.rwork);
पूर्ण

अटल व्योम lowcomms_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा connection *con;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	con = sock2con(sk);
	अगर (!con)
		जाओ out;

	अगर (!test_and_set_bit(CF_CONNECTED, &con->flags)) अणु
		log_prपूर्णांक("successful connected to node %d", con->nodeid);
		queue_work(send_workqueue, &con->swork);
		जाओ out;
	पूर्ण

	clear_bit(SOCK_NOSPACE, &con->sock->flags);

	अगर (test_and_clear_bit(CF_APP_LIMITED, &con->flags)) अणु
		con->sock->sk->sk_ग_लिखो_pending--;
		clear_bit(SOCKWQ_ASYNC_NOSPACE, &con->sock->flags);
	पूर्ण

	queue_work(send_workqueue, &con->swork);
out:
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल अंतरभूत व्योम lowcomms_connect_sock(काष्ठा connection *con)
अणु
	अगर (test_bit(CF_CLOSE, &con->flags))
		वापस;
	queue_work(send_workqueue, &con->swork);
	cond_resched();
पूर्ण

अटल व्योम lowcomms_state_change(काष्ठा sock *sk)
अणु
	/* SCTP layer is not calling sk_data_पढ़ोy when the connection
	 * is करोne, so we catch the संकेत through here. Also, it
	 * करोesn't चयन socket state when entering shutकरोwn, so we
	 * skip the ग_लिखो in that हाल.
	 */
	अगर (sk->sk_shutकरोwn) अणु
		अगर (sk->sk_shutकरोwn == RCV_SHUTDOWN)
			lowcomms_data_पढ़ोy(sk);
	पूर्ण अन्यथा अगर (sk->sk_state == TCP_ESTABLISHED) अणु
		lowcomms_ग_लिखो_space(sk);
	पूर्ण
पूर्ण

पूर्णांक dlm_lowcomms_connect_node(पूर्णांक nodeid)
अणु
	काष्ठा connection *con;

	अगर (nodeid == dlm_our_nodeid())
		वापस 0;

	con = nodeid2con(nodeid, GFP_NOFS);
	अगर (!con)
		वापस -ENOMEM;
	lowcomms_connect_sock(con);
	वापस 0;
पूर्ण

पूर्णांक dlm_lowcomms_nodes_set_mark(पूर्णांक nodeid, अचिन्हित पूर्णांक mark)
अणु
	काष्ठा dlm_node_addr *na;

	spin_lock(&dlm_node_addrs_spin);
	na = find_node_addr(nodeid);
	अगर (!na) अणु
		spin_unlock(&dlm_node_addrs_spin);
		वापस -ENOENT;
	पूर्ण

	na->mark = mark;
	spin_unlock(&dlm_node_addrs_spin);

	वापस 0;
पूर्ण

अटल व्योम lowcomms_error_report(काष्ठा sock *sk)
अणु
	काष्ठा connection *con;
	काष्ठा sockaddr_storage saddr;
	व्योम (*orig_report)(काष्ठा sock *) = शून्य;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	con = sock2con(sk);
	अगर (con == शून्य)
		जाओ out;

	orig_report = listen_sock.sk_error_report;
	अगर (con->sock == शून्य ||
	    kernel_getpeername(con->sock, (काष्ठा sockaddr *)&saddr) < 0) अणु
		prपूर्णांकk_ratelimited(KERN_ERR "dlm: node %d: socket error "
				   "sending to node %d, port %d, "
				   "sk_err=%d/%d\n", dlm_our_nodeid(),
				   con->nodeid, dlm_config.ci_tcp_port,
				   sk->sk_err, sk->sk_err_soft);
	पूर्ण अन्यथा अगर (saddr.ss_family == AF_INET) अणु
		काष्ठा sockaddr_in *sin4 = (काष्ठा sockaddr_in *)&saddr;

		prपूर्णांकk_ratelimited(KERN_ERR "dlm: node %d: socket error "
				   "sending to node %d at %pI4, port %d, "
				   "sk_err=%d/%d\n", dlm_our_nodeid(),
				   con->nodeid, &sin4->sin_addr.s_addr,
				   dlm_config.ci_tcp_port, sk->sk_err,
				   sk->sk_err_soft);
	पूर्ण अन्यथा अणु
		काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *)&saddr;

		prपूर्णांकk_ratelimited(KERN_ERR "dlm: node %d: socket error "
				   "sending to node %d at %u.%u.%u.%u, "
				   "port %d, sk_err=%d/%d\n", dlm_our_nodeid(),
				   con->nodeid, sin6->sin6_addr.s6_addr32[0],
				   sin6->sin6_addr.s6_addr32[1],
				   sin6->sin6_addr.s6_addr32[2],
				   sin6->sin6_addr.s6_addr32[3],
				   dlm_config.ci_tcp_port, sk->sk_err,
				   sk->sk_err_soft);
	पूर्ण
out:
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
	अगर (orig_report)
		orig_report(sk);
पूर्ण

/* Note: sk_callback_lock must be locked beक्रमe calling this function. */
अटल व्योम save_listen_callbacks(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	listen_sock.sk_data_पढ़ोy = sk->sk_data_पढ़ोy;
	listen_sock.sk_state_change = sk->sk_state_change;
	listen_sock.sk_ग_लिखो_space = sk->sk_ग_लिखो_space;
	listen_sock.sk_error_report = sk->sk_error_report;
पूर्ण

अटल व्योम restore_callbacks(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	sk->sk_user_data = शून्य;
	sk->sk_data_पढ़ोy = listen_sock.sk_data_पढ़ोy;
	sk->sk_state_change = listen_sock.sk_state_change;
	sk->sk_ग_लिखो_space = listen_sock.sk_ग_लिखो_space;
	sk->sk_error_report = listen_sock.sk_error_report;
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल व्योम add_listen_sock(काष्ठा socket *sock, काष्ठा listen_connection *con)
अणु
	काष्ठा sock *sk = sock->sk;

	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	save_listen_callbacks(sock);
	con->sock = sock;

	sk->sk_user_data = con;
	sk->sk_allocation = GFP_NOFS;
	/* Install a data_पढ़ोy callback */
	sk->sk_data_पढ़ोy = lowcomms_listen_data_पढ़ोy;
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

/* Make a socket active */
अटल व्योम add_sock(काष्ठा socket *sock, काष्ठा connection *con)
अणु
	काष्ठा sock *sk = sock->sk;

	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	con->sock = sock;

	sk->sk_user_data = con;
	/* Install a data_पढ़ोy callback */
	sk->sk_data_पढ़ोy = lowcomms_data_पढ़ोy;
	sk->sk_ग_लिखो_space = lowcomms_ग_लिखो_space;
	sk->sk_state_change = lowcomms_state_change;
	sk->sk_allocation = GFP_NOFS;
	sk->sk_error_report = lowcomms_error_report;
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

/* Add the port number to an IPv6 or 4 sockaddr and वापस the address
   length */
अटल व्योम make_sockaddr(काष्ठा sockaddr_storage *saddr, uपूर्णांक16_t port,
			  पूर्णांक *addr_len)
अणु
	saddr->ss_family =  dlm_local_addr[0]->ss_family;
	अगर (saddr->ss_family == AF_INET) अणु
		काष्ठा sockaddr_in *in4_addr = (काष्ठा sockaddr_in *)saddr;
		in4_addr->sin_port = cpu_to_be16(port);
		*addr_len = माप(काष्ठा sockaddr_in);
		स_रखो(&in4_addr->sin_zero, 0, माप(in4_addr->sin_zero));
	पूर्ण अन्यथा अणु
		काष्ठा sockaddr_in6 *in6_addr = (काष्ठा sockaddr_in6 *)saddr;
		in6_addr->sin6_port = cpu_to_be16(port);
		*addr_len = माप(काष्ठा sockaddr_in6);
	पूर्ण
	स_रखो((अक्षर *)saddr + *addr_len, 0, माप(काष्ठा sockaddr_storage) - *addr_len);
पूर्ण

अटल व्योम dlm_बंद_sock(काष्ठा socket **sock)
अणु
	अगर (*sock) अणु
		restore_callbacks(*sock);
		sock_release(*sock);
		*sock = शून्य;
	पूर्ण
पूर्ण

/* Close a remote connection and tidy up */
अटल व्योम बंद_connection(काष्ठा connection *con, bool and_other,
			     bool tx, bool rx)
अणु
	bool closing = test_and_set_bit(CF_CLOSING, &con->flags);

	अगर (tx && !closing && cancel_work_sync(&con->swork)) अणु
		log_prपूर्णांक("canceled swork for node %d", con->nodeid);
		clear_bit(CF_WRITE_PENDING, &con->flags);
	पूर्ण
	अगर (rx && !closing && cancel_work_sync(&con->rwork)) अणु
		log_prपूर्णांक("canceled rwork for node %d", con->nodeid);
		clear_bit(CF_READ_PENDING, &con->flags);
	पूर्ण

	mutex_lock(&con->sock_mutex);
	dlm_बंद_sock(&con->sock);

	अगर (con->othercon && and_other) अणु
		/* Will only re-enter once. */
		बंद_connection(con->othercon, false, true, true);
	पूर्ण

	con->rx_leftover = 0;
	con->retries = 0;
	clear_bit(CF_CONNECTED, &con->flags);
	mutex_unlock(&con->sock_mutex);
	clear_bit(CF_CLOSING, &con->flags);
पूर्ण

अटल व्योम shutकरोwn_connection(काष्ठा connection *con)
अणु
	पूर्णांक ret;

	flush_work(&con->swork);

	mutex_lock(&con->sock_mutex);
	/* nothing to shutकरोwn */
	अगर (!con->sock) अणु
		mutex_unlock(&con->sock_mutex);
		वापस;
	पूर्ण

	set_bit(CF_SHUTDOWN, &con->flags);
	ret = kernel_sock_shutकरोwn(con->sock, SHUT_WR);
	mutex_unlock(&con->sock_mutex);
	अगर (ret) अणु
		log_prपूर्णांक("Connection %p failed to shutdown: %d will force close",
			  con, ret);
		जाओ क्रमce_बंद;
	पूर्ण अन्यथा अणु
		ret = रुको_event_समयout(con->shutकरोwn_रुको,
					 !test_bit(CF_SHUTDOWN, &con->flags),
					 DLM_SHUTDOWN_WAIT_TIMEOUT);
		अगर (ret == 0) अणु
			log_prपूर्णांक("Connection %p shutdown timed out, will force close",
				  con);
			जाओ क्रमce_बंद;
		पूर्ण
	पूर्ण

	वापस;

क्रमce_बंद:
	clear_bit(CF_SHUTDOWN, &con->flags);
	बंद_connection(con, false, true, true);
पूर्ण

अटल व्योम dlm_tcp_shutकरोwn(काष्ठा connection *con)
अणु
	अगर (con->othercon)
		shutकरोwn_connection(con->othercon);
	shutकरोwn_connection(con);
पूर्ण

अटल पूर्णांक con_पुनः_स्मृति_receive_buf(काष्ठा connection *con, पूर्णांक newlen)
अणु
	अचिन्हित अक्षर *newbuf;

	newbuf = kदो_स्मृति(newlen, GFP_NOFS);
	अगर (!newbuf)
		वापस -ENOMEM;

	/* copy any leftover from last receive */
	अगर (con->rx_leftover)
		स_हटाओ(newbuf, con->rx_buf, con->rx_leftover);

	/* swap to new buffer space */
	kमुक्त(con->rx_buf);
	con->rx_buflen = newlen;
	con->rx_buf = newbuf;

	वापस 0;
पूर्ण

/* Data received from remote end */
अटल पूर्णांक receive_from_sock(काष्ठा connection *con)
अणु
	पूर्णांक call_again_soon = 0;
	काष्ठा msghdr msg;
	काष्ठा kvec iov;
	पूर्णांक ret, buflen;

	mutex_lock(&con->sock_mutex);

	अगर (con->sock == शून्य) अणु
		ret = -EAGAIN;
		जाओ out_बंद;
	पूर्ण

	/* पुनः_स्मृति अगर we get new buffer size to पढ़ो out */
	buflen = dlm_config.ci_buffer_size;
	अगर (con->rx_buflen != buflen && con->rx_leftover <= buflen) अणु
		ret = con_पुनः_स्मृति_receive_buf(con, buflen);
		अगर (ret < 0)
			जाओ out_resched;
	पूर्ण

	/* calculate new buffer parameter regarding last receive and
	 * possible leftover bytes
	 */
	iov.iov_base = con->rx_buf + con->rx_leftover;
	iov.iov_len = con->rx_buflen - con->rx_leftover;

	स_रखो(&msg, 0, माप(msg));
	msg.msg_flags = MSG_DONTWAIT | MSG_NOSIGNAL;
	ret = kernel_recvmsg(con->sock, &msg, &iov, 1, iov.iov_len,
			     msg.msg_flags);
	अगर (ret <= 0)
		जाओ out_बंद;
	अन्यथा अगर (ret == iov.iov_len)
		call_again_soon = 1;

	/* new buflen according पढ़ोed bytes and leftover from last receive */
	buflen = ret + con->rx_leftover;
	ret = dlm_process_incoming_buffer(con->nodeid, con->rx_buf, buflen);
	अगर (ret < 0)
		जाओ out_बंद;

	/* calculate leftover bytes from process and put it पूर्णांकo begin of
	 * the receive buffer, so next receive we have the full message
	 * at the start address of the receive buffer.
	 */
	con->rx_leftover = buflen - ret;
	अगर (con->rx_leftover) अणु
		स_हटाओ(con->rx_buf, con->rx_buf + ret,
			con->rx_leftover);
		call_again_soon = true;
	पूर्ण

	अगर (call_again_soon)
		जाओ out_resched;

	mutex_unlock(&con->sock_mutex);
	वापस 0;

out_resched:
	अगर (!test_and_set_bit(CF_READ_PENDING, &con->flags))
		queue_work(recv_workqueue, &con->rwork);
	mutex_unlock(&con->sock_mutex);
	वापस -EAGAIN;

out_बंद:
	mutex_unlock(&con->sock_mutex);
	अगर (ret != -EAGAIN) अणु
		/* Reconnect when there is something to send */
		बंद_connection(con, false, true, false);
		अगर (ret == 0) अणु
			log_prपूर्णांक("connection %p got EOF from %d",
				  con, con->nodeid);
			/* handling क्रम tcp shutकरोwn */
			clear_bit(CF_SHUTDOWN, &con->flags);
			wake_up(&con->shutकरोwn_रुको);
			/* संकेत to अवरोधing receive worker */
			ret = -1;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/* Listening socket is busy, accept a connection */
अटल पूर्णांक accept_from_sock(काष्ठा listen_connection *con)
अणु
	पूर्णांक result;
	काष्ठा sockaddr_storage peeraddr;
	काष्ठा socket *newsock;
	पूर्णांक len;
	पूर्णांक nodeid;
	काष्ठा connection *newcon;
	काष्ठा connection *addcon;
	अचिन्हित पूर्णांक mark;

	अगर (!dlm_allow_conn) अणु
		वापस -1;
	पूर्ण

	अगर (!con->sock)
		वापस -ENOTCONN;

	result = kernel_accept(con->sock, &newsock, O_NONBLOCK);
	अगर (result < 0)
		जाओ accept_err;

	/* Get the connected socket's peer */
	स_रखो(&peeraddr, 0, माप(peeraddr));
	len = newsock->ops->getname(newsock, (काष्ठा sockaddr *)&peeraddr, 2);
	अगर (len < 0) अणु
		result = -ECONNABORTED;
		जाओ accept_err;
	पूर्ण

	/* Get the new node's NODEID */
	make_sockaddr(&peeraddr, 0, &len);
	अगर (addr_to_nodeid(&peeraddr, &nodeid, &mark)) अणु
		अचिन्हित अक्षर *b=(अचिन्हित अक्षर *)&peeraddr;
		log_prपूर्णांक("connect from non cluster node");
		prपूर्णांक_hex_dump_bytes("ss: ", DUMP_PREFIX_NONE, 
				     b, माप(काष्ठा sockaddr_storage));
		sock_release(newsock);
		वापस -1;
	पूर्ण

	log_prपूर्णांक("got connection from %d", nodeid);

	/*  Check to see अगर we alपढ़ोy have a connection to this node. This
	 *  could happen अगर the two nodes initiate a connection at roughly
	 *  the same समय and the connections cross on the wire.
	 *  In this हाल we store the incoming one in "othercon"
	 */
	newcon = nodeid2con(nodeid, GFP_NOFS);
	अगर (!newcon) अणु
		result = -ENOMEM;
		जाओ accept_err;
	पूर्ण

	sock_set_mark(newsock->sk, mark);

	mutex_lock(&newcon->sock_mutex);
	अगर (newcon->sock) अणु
		काष्ठा connection *othercon = newcon->othercon;

		अगर (!othercon) अणु
			othercon = kzalloc(माप(*othercon), GFP_NOFS);
			अगर (!othercon) अणु
				log_prपूर्णांक("failed to allocate incoming socket");
				mutex_unlock(&newcon->sock_mutex);
				result = -ENOMEM;
				जाओ accept_err;
			पूर्ण

			result = dlm_con_init(othercon, nodeid);
			अगर (result < 0) अणु
				kमुक्त(othercon);
				mutex_unlock(&newcon->sock_mutex);
				जाओ accept_err;
			पूर्ण

			lockdep_set_subclass(&othercon->sock_mutex, 1);
			newcon->othercon = othercon;
		पूर्ण अन्यथा अणु
			/* बंद other sock con अगर we have something new */
			बंद_connection(othercon, false, true, false);
		पूर्ण

		mutex_lock(&othercon->sock_mutex);
		add_sock(newsock, othercon);
		addcon = othercon;
		mutex_unlock(&othercon->sock_mutex);
	पूर्ण
	अन्यथा अणु
		/* accept copies the sk after we've saved the callbacks, so we
		   करोn't want to save them a second समय or comm errors will
		   result in calling sk_error_report recursively. */
		add_sock(newsock, newcon);
		addcon = newcon;
	पूर्ण

	set_bit(CF_CONNECTED, &addcon->flags);
	mutex_unlock(&newcon->sock_mutex);

	/*
	 * Add it to the active queue in हाल we got data
	 * between processing the accept adding the socket
	 * to the पढ़ो_sockets list
	 */
	अगर (!test_and_set_bit(CF_READ_PENDING, &addcon->flags))
		queue_work(recv_workqueue, &addcon->rwork);

	वापस 0;

accept_err:
	अगर (newsock)
		sock_release(newsock);

	अगर (result != -EAGAIN)
		log_prपूर्णांक("error accepting connection from node: %d", result);
	वापस result;
पूर्ण

अटल व्योम मुक्त_entry(काष्ठा ग_लिखोqueue_entry *e)
अणु
	__मुक्त_page(e->page);
	kमुक्त(e);
पूर्ण

/*
 * ग_लिखोqueue_entry_complete - try to delete and मुक्त ग_लिखो queue entry
 * @e: ग_लिखो queue entry to try to delete
 * @completed: bytes completed
 *
 * ग_लिखोqueue_lock must be held.
 */
अटल व्योम ग_लिखोqueue_entry_complete(काष्ठा ग_लिखोqueue_entry *e, पूर्णांक completed)
अणु
	e->offset += completed;
	e->len -= completed;

	अगर (e->len == 0 && e->users == 0) अणु
		list_del(&e->list);
		मुक्त_entry(e);
	पूर्ण
पूर्ण

/*
 * sctp_bind_addrs - bind a SCTP socket to all our addresses
 */
अटल पूर्णांक sctp_bind_addrs(काष्ठा socket *sock, uपूर्णांक16_t port)
अणु
	काष्ठा sockaddr_storage localaddr;
	काष्ठा sockaddr *addr = (काष्ठा sockaddr *)&localaddr;
	पूर्णांक i, addr_len, result = 0;

	क्रम (i = 0; i < dlm_local_count; i++) अणु
		स_नकल(&localaddr, dlm_local_addr[i], माप(localaddr));
		make_sockaddr(&localaddr, port, &addr_len);

		अगर (!i)
			result = kernel_bind(sock, addr, addr_len);
		अन्यथा
			result = sock_bind_add(sock->sk, addr, addr_len);

		अगर (result < 0) अणु
			log_prपूर्णांक("Can't bind to %d addr number %d, %d.\n",
				  port, i + 1, result);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस result;
पूर्ण

/* Initiate an SCTP association.
   This is a special हाल of send_to_sock() in that we करोn't yet have a
   peeled-off socket क्रम this association, so we use the listening socket
   and add the primary IP address of the remote node.
 */
अटल व्योम sctp_connect_to_sock(काष्ठा connection *con)
अणु
	काष्ठा sockaddr_storage daddr;
	पूर्णांक result;
	पूर्णांक addr_len;
	काष्ठा socket *sock;
	अचिन्हित पूर्णांक mark;

	mutex_lock(&con->sock_mutex);

	/* Some odd races can cause द्विगुन-connects, ignore them */
	अगर (con->retries++ > MAX_CONNECT_RETRIES)
		जाओ out;

	अगर (con->sock) अणु
		log_prपूर्णांक("node %d already connected.", con->nodeid);
		जाओ out;
	पूर्ण

	स_रखो(&daddr, 0, माप(daddr));
	result = nodeid_to_addr(con->nodeid, &daddr, शून्य, true, &mark);
	अगर (result < 0) अणु
		log_prपूर्णांक("no address for nodeid %d", con->nodeid);
		जाओ out;
	पूर्ण

	/* Create a socket to communicate with */
	result = sock_create_kern(&init_net, dlm_local_addr[0]->ss_family,
				  SOCK_STREAM, IPPROTO_SCTP, &sock);
	अगर (result < 0)
		जाओ socket_err;

	sock_set_mark(sock->sk, mark);

	add_sock(sock, con);

	/* Bind to all addresses. */
	अगर (sctp_bind_addrs(con->sock, 0))
		जाओ bind_err;

	make_sockaddr(&daddr, dlm_config.ci_tcp_port, &addr_len);

	log_prपूर्णांक("connecting to %d", con->nodeid);

	/* Turn off Nagle's algorithm */
	sctp_sock_set_nodelay(sock->sk);

	/*
	 * Make sock->ops->connect() function वापस in specअगरied समय,
	 * since O_NONBLOCK argument in connect() function करोes not work here,
	 * then, we should restore the शेष value of this attribute.
	 */
	sock_set_sndसमयo(sock->sk, 5);
	result = sock->ops->connect(sock, (काष्ठा sockaddr *)&daddr, addr_len,
				   0);
	sock_set_sndसमयo(sock->sk, 0);

	अगर (result == -EINPROGRESS)
		result = 0;
	अगर (result == 0) अणु
		अगर (!test_and_set_bit(CF_CONNECTED, &con->flags))
			log_prपूर्णांक("successful connected to node %d", con->nodeid);
		जाओ out;
	पूर्ण

bind_err:
	con->sock = शून्य;
	sock_release(sock);

socket_err:
	/*
	 * Some errors are fatal and this list might need adjusting. For other
	 * errors we try again until the max number of retries is reached.
	 */
	अगर (result != -EHOSTUNREACH &&
	    result != -ENETUNREACH &&
	    result != -ENETDOWN &&
	    result != -EINVAL &&
	    result != -EPROTONOSUPPORT) अणु
		log_prपूर्णांक("connect %d try %d error %d", con->nodeid,
			  con->retries, result);
		mutex_unlock(&con->sock_mutex);
		msleep(1000);
		lowcomms_connect_sock(con);
		वापस;
	पूर्ण

out:
	mutex_unlock(&con->sock_mutex);
पूर्ण

/* Connect a new socket to its peer */
अटल व्योम tcp_connect_to_sock(काष्ठा connection *con)
अणु
	काष्ठा sockaddr_storage saddr, src_addr;
	अचिन्हित पूर्णांक mark;
	पूर्णांक addr_len;
	काष्ठा socket *sock = शून्य;
	पूर्णांक result;

	mutex_lock(&con->sock_mutex);
	अगर (con->retries++ > MAX_CONNECT_RETRIES)
		जाओ out;

	/* Some odd races can cause द्विगुन-connects, ignore them */
	अगर (con->sock)
		जाओ out;

	/* Create a socket to communicate with */
	result = sock_create_kern(&init_net, dlm_local_addr[0]->ss_family,
				  SOCK_STREAM, IPPROTO_TCP, &sock);
	अगर (result < 0)
		जाओ out_err;

	स_रखो(&saddr, 0, माप(saddr));
	result = nodeid_to_addr(con->nodeid, &saddr, शून्य, false, &mark);
	अगर (result < 0) अणु
		log_prपूर्णांक("no address for nodeid %d", con->nodeid);
		जाओ out_err;
	पूर्ण

	sock_set_mark(sock->sk, mark);

	add_sock(sock, con);

	/* Bind to our cluster-known address connecting to aव्योम
	   routing problems */
	स_नकल(&src_addr, dlm_local_addr[0], माप(src_addr));
	make_sockaddr(&src_addr, 0, &addr_len);
	result = sock->ops->bind(sock, (काष्ठा sockaddr *) &src_addr,
				 addr_len);
	अगर (result < 0) अणु
		log_prपूर्णांक("could not bind for connect: %d", result);
		/* This *may* not indicate a critical error */
	पूर्ण

	make_sockaddr(&saddr, dlm_config.ci_tcp_port, &addr_len);

	log_prपूर्णांक("connecting to %d", con->nodeid);

	/* Turn off Nagle's algorithm */
	tcp_sock_set_nodelay(sock->sk);

	result = sock->ops->connect(sock, (काष्ठा sockaddr *)&saddr, addr_len,
				   O_NONBLOCK);
	अगर (result == -EINPROGRESS)
		result = 0;
	अगर (result == 0)
		जाओ out;

out_err:
	अगर (con->sock) अणु
		sock_release(con->sock);
		con->sock = शून्य;
	पूर्ण अन्यथा अगर (sock) अणु
		sock_release(sock);
	पूर्ण
	/*
	 * Some errors are fatal and this list might need adjusting. For other
	 * errors we try again until the max number of retries is reached.
	 */
	अगर (result != -EHOSTUNREACH &&
	    result != -ENETUNREACH &&
	    result != -ENETDOWN && 
	    result != -EINVAL &&
	    result != -EPROTONOSUPPORT) अणु
		log_prपूर्णांक("connect %d try %d error %d", con->nodeid,
			  con->retries, result);
		mutex_unlock(&con->sock_mutex);
		msleep(1000);
		lowcomms_connect_sock(con);
		वापस;
	पूर्ण
out:
	mutex_unlock(&con->sock_mutex);
	वापस;
पूर्ण

/* On error caller must run dlm_बंद_sock() क्रम the
 * listen connection socket.
 */
अटल पूर्णांक tcp_create_listen_sock(काष्ठा listen_connection *con,
				  काष्ठा sockaddr_storage *saddr)
अणु
	काष्ठा socket *sock = शून्य;
	पूर्णांक result = 0;
	पूर्णांक addr_len;

	अगर (dlm_local_addr[0]->ss_family == AF_INET)
		addr_len = माप(काष्ठा sockaddr_in);
	अन्यथा
		addr_len = माप(काष्ठा sockaddr_in6);

	/* Create a socket to communicate with */
	result = sock_create_kern(&init_net, dlm_local_addr[0]->ss_family,
				  SOCK_STREAM, IPPROTO_TCP, &sock);
	अगर (result < 0) अणु
		log_prपूर्णांक("Can't create listening comms socket");
		जाओ create_out;
	पूर्ण

	sock_set_mark(sock->sk, dlm_config.ci_mark);

	/* Turn off Nagle's algorithm */
	tcp_sock_set_nodelay(sock->sk);

	sock_set_reuseaddr(sock->sk);

	add_listen_sock(sock, con);

	/* Bind to our port */
	make_sockaddr(saddr, dlm_config.ci_tcp_port, &addr_len);
	result = sock->ops->bind(sock, (काष्ठा sockaddr *) saddr, addr_len);
	अगर (result < 0) अणु
		log_prपूर्णांक("Can't bind to port %d", dlm_config.ci_tcp_port);
		जाओ create_out;
	पूर्ण
	sock_set_keepalive(sock->sk);

	result = sock->ops->listen(sock, 5);
	अगर (result < 0) अणु
		log_prपूर्णांक("Can't listen on port %d", dlm_config.ci_tcp_port);
		जाओ create_out;
	पूर्ण

	वापस 0;

create_out:
	वापस result;
पूर्ण

/* Get local addresses */
अटल व्योम init_local(व्योम)
अणु
	काष्ठा sockaddr_storage sas, *addr;
	पूर्णांक i;

	dlm_local_count = 0;
	क्रम (i = 0; i < DLM_MAX_ADDR_COUNT; i++) अणु
		अगर (dlm_our_addr(&sas, i))
			अवरोध;

		addr = kmemdup(&sas, माप(*addr), GFP_NOFS);
		अगर (!addr)
			अवरोध;
		dlm_local_addr[dlm_local_count++] = addr;
	पूर्ण
पूर्ण

अटल व्योम deinit_local(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dlm_local_count; i++)
		kमुक्त(dlm_local_addr[i]);
पूर्ण

/* Initialise SCTP socket and bind to all पूर्णांकerfaces
 * On error caller must run dlm_बंद_sock() क्रम the
 * listen connection socket.
 */
अटल पूर्णांक sctp_listen_क्रम_all(काष्ठा listen_connection *con)
अणु
	काष्ठा socket *sock = शून्य;
	पूर्णांक result = -EINVAL;

	log_prपूर्णांक("Using SCTP for communications");

	result = sock_create_kern(&init_net, dlm_local_addr[0]->ss_family,
				  SOCK_STREAM, IPPROTO_SCTP, &sock);
	अगर (result < 0) अणु
		log_prपूर्णांक("Can't create comms socket, check SCTP is loaded");
		जाओ out;
	पूर्ण

	sock_set_rcvbuf(sock->sk, NEEDED_RMEM);
	sock_set_mark(sock->sk, dlm_config.ci_mark);
	sctp_sock_set_nodelay(sock->sk);

	add_listen_sock(sock, con);

	/* Bind to all addresses. */
	result = sctp_bind_addrs(con->sock, dlm_config.ci_tcp_port);
	अगर (result < 0)
		जाओ out;

	result = sock->ops->listen(sock, 5);
	अगर (result < 0) अणु
		log_prपूर्णांक("Can't set socket listening");
		जाओ out;
	पूर्ण

	वापस 0;

out:
	वापस result;
पूर्ण

अटल पूर्णांक tcp_listen_क्रम_all(व्योम)
अणु
	/* We करोn't support multi-homed hosts */
	अगर (dlm_local_count > 1) अणु
		log_prपूर्णांक("TCP protocol can't handle multi-homed hosts, "
			  "try SCTP");
		वापस -EINVAL;
	पूर्ण

	log_prपूर्णांक("Using TCP for communications");

	वापस tcp_create_listen_sock(&listen_con, dlm_local_addr[0]);
पूर्ण



अटल काष्ठा ग_लिखोqueue_entry *new_ग_लिखोqueue_entry(काष्ठा connection *con,
						     gfp_t allocation)
अणु
	काष्ठा ग_लिखोqueue_entry *entry;

	entry = kzalloc(माप(*entry), allocation);
	अगर (!entry)
		वापस शून्य;

	entry->page = alloc_page(allocation | __GFP_ZERO);
	अगर (!entry->page) अणु
		kमुक्त(entry);
		वापस शून्य;
	पूर्ण

	entry->con = con;
	entry->users = 1;

	वापस entry;
पूर्ण

अटल काष्ठा ग_लिखोqueue_entry *new_wq_entry(काष्ठा connection *con, पूर्णांक len,
					     gfp_t allocation, अक्षर **ppc)
अणु
	काष्ठा ग_लिखोqueue_entry *e;

	spin_lock(&con->ग_लिखोqueue_lock);
	अगर (!list_empty(&con->ग_लिखोqueue)) अणु
		e = list_last_entry(&con->ग_लिखोqueue, काष्ठा ग_लिखोqueue_entry, list);
		अगर (DLM_WQ_REMAIN_BYTES(e) >= len) अणु
			*ppc = page_address(e->page) + e->end;
			e->end += len;
			e->users++;
			spin_unlock(&con->ग_लिखोqueue_lock);

			वापस e;
		पूर्ण
	पूर्ण
	spin_unlock(&con->ग_लिखोqueue_lock);

	e = new_ग_लिखोqueue_entry(con, allocation);
	अगर (!e)
		वापस शून्य;

	*ppc = page_address(e->page);
	e->end += len;

	spin_lock(&con->ग_लिखोqueue_lock);
	list_add_tail(&e->list, &con->ग_लिखोqueue);
	spin_unlock(&con->ग_लिखोqueue_lock);

	वापस e;
पूर्ण;

व्योम *dlm_lowcomms_get_buffer(पूर्णांक nodeid, पूर्णांक len, gfp_t allocation, अक्षर **ppc)
अणु
	काष्ठा connection *con;

	अगर (len > DEFAULT_BUFFER_SIZE ||
	    len < माप(काष्ठा dlm_header)) अणु
		BUILD_BUG_ON(PAGE_SIZE < DEFAULT_BUFFER_SIZE);
		log_prपूर्णांक("failed to allocate a buffer of size %d", len);
		WARN_ON(1);
		वापस शून्य;
	पूर्ण

	con = nodeid2con(nodeid, allocation);
	अगर (!con)
		वापस शून्य;

	वापस new_wq_entry(con, len, allocation, ppc);
पूर्ण

व्योम dlm_lowcomms_commit_buffer(व्योम *mh)
अणु
	काष्ठा ग_लिखोqueue_entry *e = (काष्ठा ग_लिखोqueue_entry *)mh;
	काष्ठा connection *con = e->con;
	पूर्णांक users;

	spin_lock(&con->ग_लिखोqueue_lock);
	users = --e->users;
	अगर (users)
		जाओ out;

	e->len = DLM_WQ_LENGTH_BYTES(e);
	spin_unlock(&con->ग_लिखोqueue_lock);

	queue_work(send_workqueue, &con->swork);
	वापस;

out:
	spin_unlock(&con->ग_लिखोqueue_lock);
	वापस;
पूर्ण

/* Send a message */
अटल व्योम send_to_sock(काष्ठा connection *con)
अणु
	पूर्णांक ret = 0;
	स्थिर पूर्णांक msg_flags = MSG_DONTWAIT | MSG_NOSIGNAL;
	काष्ठा ग_लिखोqueue_entry *e;
	पूर्णांक len, offset;
	पूर्णांक count = 0;

	mutex_lock(&con->sock_mutex);
	अगर (con->sock == शून्य)
		जाओ out_connect;

	spin_lock(&con->ग_लिखोqueue_lock);
	क्रम (;;) अणु
		अगर (list_empty(&con->ग_लिखोqueue))
			अवरोध;

		e = list_first_entry(&con->ग_लिखोqueue, काष्ठा ग_लिखोqueue_entry, list);
		len = e->len;
		offset = e->offset;
		BUG_ON(len == 0 && e->users == 0);
		spin_unlock(&con->ग_लिखोqueue_lock);

		ret = 0;
		अगर (len) अणु
			ret = kernel_sendpage(con->sock, e->page, offset, len,
					      msg_flags);
			अगर (ret == -EAGAIN || ret == 0) अणु
				अगर (ret == -EAGAIN &&
				    test_bit(SOCKWQ_ASYNC_NOSPACE, &con->sock->flags) &&
				    !test_and_set_bit(CF_APP_LIMITED, &con->flags)) अणु
					/* Notअगरy TCP that we're limited by the
					 * application winकरोw size.
					 */
					set_bit(SOCK_NOSPACE, &con->sock->flags);
					con->sock->sk->sk_ग_लिखो_pending++;
				पूर्ण
				cond_resched();
				जाओ out;
			पूर्ण अन्यथा अगर (ret < 0)
				जाओ send_error;
		पूर्ण

		/* Don't starve people filling buffers */
		अगर (++count >= MAX_SEND_MSG_COUNT) अणु
			cond_resched();
			count = 0;
		पूर्ण

		spin_lock(&con->ग_लिखोqueue_lock);
		ग_लिखोqueue_entry_complete(e, ret);
	पूर्ण
	spin_unlock(&con->ग_लिखोqueue_lock);
out:
	mutex_unlock(&con->sock_mutex);
	वापस;

send_error:
	mutex_unlock(&con->sock_mutex);
	बंद_connection(con, false, false, true);
	/* Requeue the send work. When the work daemon runs again, it will try
	   a new connection, then call this function again. */
	queue_work(send_workqueue, &con->swork);
	वापस;

out_connect:
	mutex_unlock(&con->sock_mutex);
	queue_work(send_workqueue, &con->swork);
	cond_resched();
पूर्ण

अटल व्योम clean_one_ग_लिखोqueue(काष्ठा connection *con)
अणु
	काष्ठा ग_लिखोqueue_entry *e, *safe;

	spin_lock(&con->ग_लिखोqueue_lock);
	list_क्रम_each_entry_safe(e, safe, &con->ग_लिखोqueue, list) अणु
		list_del(&e->list);
		मुक्त_entry(e);
	पूर्ण
	spin_unlock(&con->ग_लिखोqueue_lock);
पूर्ण

/* Called from recovery when it knows that a node has
   left the cluster */
पूर्णांक dlm_lowcomms_बंद(पूर्णांक nodeid)
अणु
	काष्ठा connection *con;
	काष्ठा dlm_node_addr *na;

	log_prपूर्णांक("closing connection to node %d", nodeid);
	con = nodeid2con(nodeid, 0);
	अगर (con) अणु
		set_bit(CF_CLOSE, &con->flags);
		बंद_connection(con, true, true, true);
		clean_one_ग_लिखोqueue(con);
		अगर (con->othercon)
			clean_one_ग_लिखोqueue(con->othercon);
	पूर्ण

	spin_lock(&dlm_node_addrs_spin);
	na = find_node_addr(nodeid);
	अगर (na) अणु
		list_del(&na->list);
		जबतक (na->addr_count--)
			kमुक्त(na->addr[na->addr_count]);
		kमुक्त(na);
	पूर्ण
	spin_unlock(&dlm_node_addrs_spin);

	वापस 0;
पूर्ण

/* Receive workqueue function */
अटल व्योम process_recv_sockets(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा connection *con = container_of(work, काष्ठा connection, rwork);
	पूर्णांक err;

	clear_bit(CF_READ_PENDING, &con->flags);
	करो अणु
		err = receive_from_sock(con);
	पूर्ण जबतक (!err);
पूर्ण

अटल व्योम process_listen_recv_socket(काष्ठा work_काष्ठा *work)
अणु
	accept_from_sock(&listen_con);
पूर्ण

/* Send workqueue function */
अटल व्योम process_send_sockets(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा connection *con = container_of(work, काष्ठा connection, swork);

	clear_bit(CF_WRITE_PENDING, &con->flags);
	अगर (con->sock == शून्य) /* not mutex रक्षित so check it inside too */
		con->connect_action(con);
	अगर (!list_empty(&con->ग_लिखोqueue))
		send_to_sock(con);
पूर्ण

अटल व्योम work_stop(व्योम)
अणु
	अगर (recv_workqueue)
		destroy_workqueue(recv_workqueue);
	अगर (send_workqueue)
		destroy_workqueue(send_workqueue);
पूर्ण

अटल पूर्णांक work_start(व्योम)
अणु
	recv_workqueue = alloc_workqueue("dlm_recv",
					 WQ_UNBOUND | WQ_MEM_RECLAIM, 1);
	अगर (!recv_workqueue) अणु
		log_prपूर्णांक("can't start dlm_recv");
		वापस -ENOMEM;
	पूर्ण

	send_workqueue = alloc_workqueue("dlm_send",
					 WQ_UNBOUND | WQ_MEM_RECLAIM, 1);
	अगर (!send_workqueue) अणु
		log_prपूर्णांक("can't start dlm_send");
		destroy_workqueue(recv_workqueue);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम shutकरोwn_conn(काष्ठा connection *con)
अणु
	अगर (con->shutकरोwn_action)
		con->shutकरोwn_action(con);
पूर्ण

व्योम dlm_lowcomms_shutकरोwn(व्योम)
अणु
	/* Set all the flags to prevent any
	 * socket activity.
	 */
	dlm_allow_conn = 0;

	अगर (recv_workqueue)
		flush_workqueue(recv_workqueue);
	अगर (send_workqueue)
		flush_workqueue(send_workqueue);

	dlm_बंद_sock(&listen_con.sock);

	क्रमeach_conn(shutकरोwn_conn);
पूर्ण

अटल व्योम _stop_conn(काष्ठा connection *con, bool and_other)
अणु
	mutex_lock(&con->sock_mutex);
	set_bit(CF_CLOSE, &con->flags);
	set_bit(CF_READ_PENDING, &con->flags);
	set_bit(CF_WRITE_PENDING, &con->flags);
	अगर (con->sock && con->sock->sk) अणु
		ग_लिखो_lock_bh(&con->sock->sk->sk_callback_lock);
		con->sock->sk->sk_user_data = शून्य;
		ग_लिखो_unlock_bh(&con->sock->sk->sk_callback_lock);
	पूर्ण
	अगर (con->othercon && and_other)
		_stop_conn(con->othercon, false);
	mutex_unlock(&con->sock_mutex);
पूर्ण

अटल व्योम stop_conn(काष्ठा connection *con)
अणु
	_stop_conn(con, true);
पूर्ण

अटल व्योम connection_release(काष्ठा rcu_head *rcu)
अणु
	काष्ठा connection *con = container_of(rcu, काष्ठा connection, rcu);

	kमुक्त(con->rx_buf);
	kमुक्त(con);
पूर्ण

अटल व्योम मुक्त_conn(काष्ठा connection *con)
अणु
	बंद_connection(con, true, true, true);
	spin_lock(&connections_lock);
	hlist_del_rcu(&con->list);
	spin_unlock(&connections_lock);
	अगर (con->othercon) अणु
		clean_one_ग_लिखोqueue(con->othercon);
		call_srcu(&connections_srcu, &con->othercon->rcu,
			  connection_release);
	पूर्ण
	clean_one_ग_लिखोqueue(con);
	call_srcu(&connections_srcu, &con->rcu, connection_release);
पूर्ण

अटल व्योम work_flush(व्योम)
अणु
	पूर्णांक ok, idx;
	पूर्णांक i;
	काष्ठा connection *con;

	करो अणु
		ok = 1;
		क्रमeach_conn(stop_conn);
		अगर (recv_workqueue)
			flush_workqueue(recv_workqueue);
		अगर (send_workqueue)
			flush_workqueue(send_workqueue);
		idx = srcu_पढ़ो_lock(&connections_srcu);
		क्रम (i = 0; i < CONN_HASH_SIZE && ok; i++) अणु
			hlist_क्रम_each_entry_rcu(con, &connection_hash[i],
						 list) अणु
				ok &= test_bit(CF_READ_PENDING, &con->flags);
				ok &= test_bit(CF_WRITE_PENDING, &con->flags);
				अगर (con->othercon) अणु
					ok &= test_bit(CF_READ_PENDING,
						       &con->othercon->flags);
					ok &= test_bit(CF_WRITE_PENDING,
						       &con->othercon->flags);
				पूर्ण
			पूर्ण
		पूर्ण
		srcu_पढ़ो_unlock(&connections_srcu, idx);
	पूर्ण जबतक (!ok);
पूर्ण

व्योम dlm_lowcomms_stop(व्योम)
अणु
	work_flush();
	क्रमeach_conn(मुक्त_conn);
	work_stop();
	deinit_local();
पूर्ण

पूर्णांक dlm_lowcomms_start(व्योम)
अणु
	पूर्णांक error = -EINVAL;
	पूर्णांक i;

	क्रम (i = 0; i < CONN_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&connection_hash[i]);

	init_local();
	अगर (!dlm_local_count) अणु
		error = -ENOTCONN;
		log_prपूर्णांक("no local IP address has been set");
		जाओ fail;
	पूर्ण

	INIT_WORK(&listen_con.rwork, process_listen_recv_socket);

	error = work_start();
	अगर (error)
		जाओ fail;

	dlm_allow_conn = 1;

	/* Start listening */
	अगर (dlm_config.ci_protocol == 0)
		error = tcp_listen_क्रम_all();
	अन्यथा
		error = sctp_listen_क्रम_all(&listen_con);
	अगर (error)
		जाओ fail_unlisten;

	वापस 0;

fail_unlisten:
	dlm_allow_conn = 0;
	dlm_बंद_sock(&listen_con.sock);
fail:
	वापस error;
पूर्ण

व्योम dlm_lowcomms_निकास(व्योम)
अणु
	काष्ठा dlm_node_addr *na, *safe;

	spin_lock(&dlm_node_addrs_spin);
	list_क्रम_each_entry_safe(na, safe, &dlm_node_addrs, list) अणु
		list_del(&na->list);
		जबतक (na->addr_count--)
			kमुक्त(na->addr[na->addr_count]);
		kमुक्त(na);
	पूर्ण
	spin_unlock(&dlm_node_addrs_spin);
पूर्ण
