<शैली गुरु>
/*
 * net/tipc/server.c: TIPC server infraकाष्ठाure
 *
 * Copyright (c) 2012-2013, Wind River Systems
 * Copyright (c) 2017-2018, Ericsson AB
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश "subscr.h"
#समावेश "topsrv.h"
#समावेश "core.h"
#समावेश "socket.h"
#समावेश "addr.h"
#समावेश "msg.h"
#समावेश "bearer.h"
#समावेश <net/sock.h>
#समावेश <linux/module.h>

/* Number of messages to send beक्रमe rescheduling */
#घोषणा MAX_SEND_MSG_COUNT	25
#घोषणा MAX_RECV_MSG_COUNT	25
#घोषणा CF_CONNECTED		1

#घोषणा TIPC_SERVER_NAME_LEN	32

/**
 * काष्ठा tipc_topsrv - TIPC server काष्ठाure
 * @conn_idr: identअगरier set of connection
 * @idr_lock: protect the connection identअगरier set
 * @idr_in_use: amount of allocated identअगरier entry
 * @net: network namspace instance
 * @awork: accept work item
 * @rcv_wq: receive workqueue
 * @send_wq: send workqueue
 * @listener: topsrv listener socket
 * @name: server name
 */
काष्ठा tipc_topsrv अणु
	काष्ठा idr conn_idr;
	spinlock_t idr_lock; /* क्रम idr list */
	पूर्णांक idr_in_use;
	काष्ठा net *net;
	काष्ठा work_काष्ठा awork;
	काष्ठा workqueue_काष्ठा *rcv_wq;
	काष्ठा workqueue_काष्ठा *send_wq;
	काष्ठा socket *listener;
	अक्षर name[TIPC_SERVER_NAME_LEN];
पूर्ण;

/**
 * काष्ठा tipc_conn - TIPC connection काष्ठाure
 * @kref: reference counter to connection object
 * @conid: connection identअगरier
 * @sock: socket handler associated with connection
 * @flags: indicates connection state
 * @server: poपूर्णांकer to connected server
 * @sub_list: lsit to all pertaing subscriptions
 * @sub_lock: lock protecting the subscription list
 * @rwork: receive work item
 * @outqueue: poपूर्णांकer to first outbound message in queue
 * @outqueue_lock: control access to the outqueue
 * @swork: send work item
 */
काष्ठा tipc_conn अणु
	काष्ठा kref kref;
	पूर्णांक conid;
	काष्ठा socket *sock;
	अचिन्हित दीर्घ flags;
	काष्ठा tipc_topsrv *server;
	काष्ठा list_head sub_list;
	spinlock_t sub_lock; /* क्रम subscription list */
	काष्ठा work_काष्ठा rwork;
	काष्ठा list_head outqueue;
	spinlock_t outqueue_lock; /* क्रम outqueue */
	काष्ठा work_काष्ठा swork;
पूर्ण;

/* An entry रुकोing to be sent */
काष्ठा outqueue_entry अणु
	bool inactive;
	काष्ठा tipc_event evt;
	काष्ठा list_head list;
पूर्ण;

अटल व्योम tipc_conn_recv_work(काष्ठा work_काष्ठा *work);
अटल व्योम tipc_conn_send_work(काष्ठा work_काष्ठा *work);
अटल व्योम tipc_topsrv_kern_evt(काष्ठा net *net, काष्ठा tipc_event *evt);
अटल व्योम tipc_conn_delete_sub(काष्ठा tipc_conn *con, काष्ठा tipc_subscr *s);

अटल bool connected(काष्ठा tipc_conn *con)
अणु
	वापस con && test_bit(CF_CONNECTED, &con->flags);
पूर्ण

अटल व्योम tipc_conn_kref_release(काष्ठा kref *kref)
अणु
	काष्ठा tipc_conn *con = container_of(kref, काष्ठा tipc_conn, kref);
	काष्ठा tipc_topsrv *s = con->server;
	काष्ठा outqueue_entry *e, *safe;

	spin_lock_bh(&s->idr_lock);
	idr_हटाओ(&s->conn_idr, con->conid);
	s->idr_in_use--;
	spin_unlock_bh(&s->idr_lock);
	अगर (con->sock)
		sock_release(con->sock);

	spin_lock_bh(&con->outqueue_lock);
	list_क्रम_each_entry_safe(e, safe, &con->outqueue, list) अणु
		list_del(&e->list);
		kमुक्त(e);
	पूर्ण
	spin_unlock_bh(&con->outqueue_lock);
	kमुक्त(con);
पूर्ण

अटल व्योम conn_put(काष्ठा tipc_conn *con)
अणु
	kref_put(&con->kref, tipc_conn_kref_release);
पूर्ण

अटल व्योम conn_get(काष्ठा tipc_conn *con)
अणु
	kref_get(&con->kref);
पूर्ण

अटल व्योम tipc_conn_बंद(काष्ठा tipc_conn *con)
अणु
	काष्ठा sock *sk = con->sock->sk;
	bool disconnect = false;

	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	disconnect = test_and_clear_bit(CF_CONNECTED, &con->flags);

	अगर (disconnect) अणु
		sk->sk_user_data = शून्य;
		tipc_conn_delete_sub(con, शून्य);
	पूर्ण
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);

	/* Handle concurrent calls from sending and receiving thपढ़ोs */
	अगर (!disconnect)
		वापस;

	/* Don't flush pending works, -just let them expire */
	kernel_sock_shutकरोwn(con->sock, SHUT_RDWR);

	conn_put(con);
पूर्ण

अटल काष्ठा tipc_conn *tipc_conn_alloc(काष्ठा tipc_topsrv *s)
अणु
	काष्ठा tipc_conn *con;
	पूर्णांक ret;

	con = kzalloc(माप(*con), GFP_ATOMIC);
	अगर (!con)
		वापस ERR_PTR(-ENOMEM);

	kref_init(&con->kref);
	INIT_LIST_HEAD(&con->outqueue);
	INIT_LIST_HEAD(&con->sub_list);
	spin_lock_init(&con->outqueue_lock);
	spin_lock_init(&con->sub_lock);
	INIT_WORK(&con->swork, tipc_conn_send_work);
	INIT_WORK(&con->rwork, tipc_conn_recv_work);

	spin_lock_bh(&s->idr_lock);
	ret = idr_alloc(&s->conn_idr, con, 0, 0, GFP_ATOMIC);
	अगर (ret < 0) अणु
		kमुक्त(con);
		spin_unlock_bh(&s->idr_lock);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	con->conid = ret;
	s->idr_in_use++;
	spin_unlock_bh(&s->idr_lock);

	set_bit(CF_CONNECTED, &con->flags);
	con->server = s;

	वापस con;
पूर्ण

अटल काष्ठा tipc_conn *tipc_conn_lookup(काष्ठा tipc_topsrv *s, पूर्णांक conid)
अणु
	काष्ठा tipc_conn *con;

	spin_lock_bh(&s->idr_lock);
	con = idr_find(&s->conn_idr, conid);
	अगर (!connected(con) || !kref_get_unless_zero(&con->kref))
		con = शून्य;
	spin_unlock_bh(&s->idr_lock);
	वापस con;
पूर्ण

/* tipc_conn_delete_sub - delete a specअगरic or all subscriptions
 * क्रम a given subscriber
 */
अटल व्योम tipc_conn_delete_sub(काष्ठा tipc_conn *con, काष्ठा tipc_subscr *s)
अणु
	काष्ठा tipc_net *tn = tipc_net(con->server->net);
	काष्ठा list_head *sub_list = &con->sub_list;
	काष्ठा tipc_subscription *sub, *पंचांगp;

	spin_lock_bh(&con->sub_lock);
	list_क्रम_each_entry_safe(sub, पंचांगp, sub_list, sub_list) अणु
		अगर (!s || !स_भेद(s, &sub->evt.s, माप(*s))) अणु
			tipc_sub_unsubscribe(sub);
			atomic_dec(&tn->subscription_count);
			अगर (s)
				अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&con->sub_lock);
पूर्ण

अटल व्योम tipc_conn_send_to_sock(काष्ठा tipc_conn *con)
अणु
	काष्ठा list_head *queue = &con->outqueue;
	काष्ठा tipc_topsrv *srv = con->server;
	काष्ठा outqueue_entry *e;
	काष्ठा tipc_event *evt;
	काष्ठा msghdr msg;
	काष्ठा kvec iov;
	पूर्णांक count = 0;
	पूर्णांक ret;

	spin_lock_bh(&con->outqueue_lock);

	जबतक (!list_empty(queue)) अणु
		e = list_first_entry(queue, काष्ठा outqueue_entry, list);
		evt = &e->evt;
		spin_unlock_bh(&con->outqueue_lock);

		अगर (e->inactive)
			tipc_conn_delete_sub(con, &evt->s);

		स_रखो(&msg, 0, माप(msg));
		msg.msg_flags = MSG_DONTWAIT;
		iov.iov_base = evt;
		iov.iov_len = माप(*evt);
		msg.msg_name = शून्य;

		अगर (con->sock) अणु
			ret = kernel_sendmsg(con->sock, &msg, &iov,
					     1, माप(*evt));
			अगर (ret == -EWOULDBLOCK || ret == 0) अणु
				cond_resched();
				वापस;
			पूर्ण अन्यथा अगर (ret < 0) अणु
				वापस tipc_conn_बंद(con);
			पूर्ण
		पूर्ण अन्यथा अणु
			tipc_topsrv_kern_evt(srv->net, evt);
		पूर्ण

		/* Don't starve users filling buffers */
		अगर (++count >= MAX_SEND_MSG_COUNT) अणु
			cond_resched();
			count = 0;
		पूर्ण
		spin_lock_bh(&con->outqueue_lock);
		list_del(&e->list);
		kमुक्त(e);
	पूर्ण
	spin_unlock_bh(&con->outqueue_lock);
पूर्ण

अटल व्योम tipc_conn_send_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tipc_conn *con = container_of(work, काष्ठा tipc_conn, swork);

	अगर (connected(con))
		tipc_conn_send_to_sock(con);

	conn_put(con);
पूर्ण

/* tipc_topsrv_queue_evt() - पूर्णांकerrupt level call from a subscription instance
 * The queued work is launched पूर्णांकo tipc_conn_send_work()->tipc_conn_send_to_sock()
 */
व्योम tipc_topsrv_queue_evt(काष्ठा net *net, पूर्णांक conid,
			   u32 event, काष्ठा tipc_event *evt)
अणु
	काष्ठा tipc_topsrv *srv = tipc_topsrv(net);
	काष्ठा outqueue_entry *e;
	काष्ठा tipc_conn *con;

	con = tipc_conn_lookup(srv, conid);
	अगर (!con)
		वापस;

	अगर (!connected(con))
		जाओ err;

	e = kदो_स्मृति(माप(*e), GFP_ATOMIC);
	अगर (!e)
		जाओ err;
	e->inactive = (event == TIPC_SUBSCR_TIMEOUT);
	स_नकल(&e->evt, evt, माप(*evt));
	spin_lock_bh(&con->outqueue_lock);
	list_add_tail(&e->list, &con->outqueue);
	spin_unlock_bh(&con->outqueue_lock);

	अगर (queue_work(srv->send_wq, &con->swork))
		वापस;
err:
	conn_put(con);
पूर्ण

/* tipc_conn_ग_लिखो_space - पूर्णांकerrupt callback after a sendmsg EAGAIN
 * Indicates that there now is more space in the send buffer
 * The queued work is launched पूर्णांकo tipc_send_work()->tipc_conn_send_to_sock()
 */
अटल व्योम tipc_conn_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा tipc_conn *con;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	con = sk->sk_user_data;
	अगर (connected(con)) अणु
		conn_get(con);
		अगर (!queue_work(con->server->send_wq, &con->swork))
			conn_put(con);
	पूर्ण
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल पूर्णांक tipc_conn_rcv_sub(काष्ठा tipc_topsrv *srv,
			     काष्ठा tipc_conn *con,
			     काष्ठा tipc_subscr *s)
अणु
	काष्ठा tipc_net *tn = tipc_net(srv->net);
	काष्ठा tipc_subscription *sub;
	u32 s_filter = tipc_sub_पढ़ो(s, filter);

	अगर (s_filter & TIPC_SUB_CANCEL) अणु
		tipc_sub_ग_लिखो(s, filter, s_filter & ~TIPC_SUB_CANCEL);
		tipc_conn_delete_sub(con, s);
		वापस 0;
	पूर्ण
	अगर (atomic_पढ़ो(&tn->subscription_count) >= TIPC_MAX_SUBSCR) अणु
		pr_warn("Subscription rejected, max (%u)\n", TIPC_MAX_SUBSCR);
		वापस -1;
	पूर्ण
	sub = tipc_sub_subscribe(srv->net, s, con->conid);
	अगर (!sub)
		वापस -1;
	atomic_inc(&tn->subscription_count);
	spin_lock_bh(&con->sub_lock);
	list_add(&sub->sub_list, &con->sub_list);
	spin_unlock_bh(&con->sub_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक tipc_conn_rcv_from_sock(काष्ठा tipc_conn *con)
अणु
	काष्ठा tipc_topsrv *srv = con->server;
	काष्ठा sock *sk = con->sock->sk;
	काष्ठा msghdr msg = अणुपूर्ण;
	काष्ठा tipc_subscr s;
	काष्ठा kvec iov;
	पूर्णांक ret;

	iov.iov_base = &s;
	iov.iov_len = माप(s);
	msg.msg_name = शून्य;
	iov_iter_kvec(&msg.msg_iter, READ, &iov, 1, iov.iov_len);
	ret = sock_recvmsg(con->sock, &msg, MSG_DONTWAIT);
	अगर (ret == -EWOULDBLOCK)
		वापस -EWOULDBLOCK;
	अगर (ret == माप(s)) अणु
		पढ़ो_lock_bh(&sk->sk_callback_lock);
		/* RACE: the connection can be बंदd in the meanसमय */
		अगर (likely(connected(con)))
			ret = tipc_conn_rcv_sub(srv, con, &s);
		पढ़ो_unlock_bh(&sk->sk_callback_lock);
		अगर (!ret)
			वापस 0;
	पूर्ण

	tipc_conn_बंद(con);
	वापस ret;
पूर्ण

अटल व्योम tipc_conn_recv_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tipc_conn *con = container_of(work, काष्ठा tipc_conn, rwork);
	पूर्णांक count = 0;

	जबतक (connected(con)) अणु
		अगर (tipc_conn_rcv_from_sock(con))
			अवरोध;

		/* Don't flood Rx machine */
		अगर (++count >= MAX_RECV_MSG_COUNT) अणु
			cond_resched();
			count = 0;
		पूर्ण
	पूर्ण
	conn_put(con);
पूर्ण

/* tipc_conn_data_पढ़ोy - पूर्णांकerrupt callback indicating the socket has data
 * The queued work is launched पूर्णांकo tipc_recv_work()->tipc_conn_rcv_from_sock()
 */
अटल व्योम tipc_conn_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा tipc_conn *con;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	con = sk->sk_user_data;
	अगर (connected(con)) अणु
		conn_get(con);
		अगर (!queue_work(con->server->rcv_wq, &con->rwork))
			conn_put(con);
	पूर्ण
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल व्योम tipc_topsrv_accept(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tipc_topsrv *srv = container_of(work, काष्ठा tipc_topsrv, awork);
	काष्ठा socket *lsock = srv->listener;
	काष्ठा socket *newsock;
	काष्ठा tipc_conn *con;
	काष्ठा sock *newsk;
	पूर्णांक ret;

	जबतक (1) अणु
		ret = kernel_accept(lsock, &newsock, O_NONBLOCK);
		अगर (ret < 0)
			वापस;
		con = tipc_conn_alloc(srv);
		अगर (IS_ERR(con)) अणु
			ret = PTR_ERR(con);
			sock_release(newsock);
			वापस;
		पूर्ण
		/* Register callbacks */
		newsk = newsock->sk;
		ग_लिखो_lock_bh(&newsk->sk_callback_lock);
		newsk->sk_data_पढ़ोy = tipc_conn_data_पढ़ोy;
		newsk->sk_ग_लिखो_space = tipc_conn_ग_लिखो_space;
		newsk->sk_user_data = con;
		con->sock = newsock;
		ग_लिखो_unlock_bh(&newsk->sk_callback_lock);

		/* Wake up receive process in हाल of 'SYN+' message */
		newsk->sk_data_पढ़ोy(newsk);
	पूर्ण
पूर्ण

/* tipc_topsrv_listener_data_पढ़ोy - पूर्णांकerrupt callback with connection request
 * The queued job is launched पूर्णांकo tipc_topsrv_accept()
 */
अटल व्योम tipc_topsrv_listener_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा tipc_topsrv *srv;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	srv = sk->sk_user_data;
	अगर (srv->listener)
		queue_work(srv->rcv_wq, &srv->awork);
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल पूर्णांक tipc_topsrv_create_listener(काष्ठा tipc_topsrv *srv)
अणु
	काष्ठा socket *lsock = शून्य;
	काष्ठा sockaddr_tipc saddr;
	काष्ठा sock *sk;
	पूर्णांक rc;

	rc = sock_create_kern(srv->net, AF_TIPC, SOCK_SEQPACKET, 0, &lsock);
	अगर (rc < 0)
		वापस rc;

	srv->listener = lsock;
	sk = lsock->sk;
	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	sk->sk_data_पढ़ोy = tipc_topsrv_listener_data_पढ़ोy;
	sk->sk_user_data = srv;
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);

	lock_sock(sk);
	rc = tsk_set_importance(sk, TIPC_CRITICAL_IMPORTANCE);
	release_sock(sk);
	अगर (rc < 0)
		जाओ err;

	saddr.family	                = AF_TIPC;
	saddr.addrtype		        = TIPC_SERVICE_RANGE;
	saddr.addr.nameseq.type	= TIPC_TOP_SRV;
	saddr.addr.nameseq.lower	= TIPC_TOP_SRV;
	saddr.addr.nameseq.upper	= TIPC_TOP_SRV;
	saddr.scope			= TIPC_NODE_SCOPE;

	rc = tipc_sk_bind(lsock, (काष्ठा sockaddr *)&saddr, माप(saddr));
	अगर (rc < 0)
		जाओ err;
	rc = kernel_listen(lsock, 0);
	अगर (rc < 0)
		जाओ err;

	/* As server's listening socket owner and creator is the same module,
	 * we have to decrease TIPC module reference count to guarantee that
	 * it reमुख्यs zero after the server socket is created, otherwise,
	 * executing "rmmod" command is unable to make TIPC module deleted
	 * after TIPC module is inserted successfully.
	 *
	 * However, the reference count is ever increased twice in
	 * sock_create_kern(): one is to increase the reference count of owner
	 * of TIPC socket's proto_ops काष्ठा; another is to increment the
	 * reference count of owner of TIPC proto काष्ठा. Thereक्रमe, we must
	 * decrement the module reference count twice to ensure that it keeps
	 * zero after server's listening socket is created. Of course, we
	 * must bump the module reference count twice as well beक्रमe the socket
	 * is बंदd.
	 */
	module_put(lsock->ops->owner);
	module_put(sk->sk_prot_creator->owner);

	वापस 0;
err:
	sock_release(lsock);
	वापस -EINVAL;
पूर्ण

bool tipc_topsrv_kern_subscr(काष्ठा net *net, u32 port, u32 type, u32 lower,
			     u32 upper, u32 filter, पूर्णांक *conid)
अणु
	काष्ठा tipc_subscr sub;
	काष्ठा tipc_conn *con;
	पूर्णांक rc;

	sub.seq.type = type;
	sub.seq.lower = lower;
	sub.seq.upper = upper;
	sub.समयout = TIPC_WAIT_FOREVER;
	sub.filter = filter;
	*(u32 *)&sub.usr_handle = port;

	con = tipc_conn_alloc(tipc_topsrv(net));
	अगर (IS_ERR(con))
		वापस false;

	*conid = con->conid;
	con->sock = शून्य;
	rc = tipc_conn_rcv_sub(tipc_topsrv(net), con, &sub);
	अगर (rc >= 0)
		वापस true;
	conn_put(con);
	वापस false;
पूर्ण

व्योम tipc_topsrv_kern_unsubscr(काष्ठा net *net, पूर्णांक conid)
अणु
	काष्ठा tipc_conn *con;

	con = tipc_conn_lookup(tipc_topsrv(net), conid);
	अगर (!con)
		वापस;

	test_and_clear_bit(CF_CONNECTED, &con->flags);
	tipc_conn_delete_sub(con, शून्य);
	conn_put(con);
	conn_put(con);
पूर्ण

अटल व्योम tipc_topsrv_kern_evt(काष्ठा net *net, काष्ठा tipc_event *evt)
अणु
	u32 port = *(u32 *)&evt->s.usr_handle;
	u32 self = tipc_own_addr(net);
	काष्ठा sk_buff_head evtq;
	काष्ठा sk_buff *skb;

	skb = tipc_msg_create(TOP_SRV, 0, INT_H_SIZE, माप(*evt),
			      self, self, port, port, 0);
	अगर (!skb)
		वापस;
	msg_set_dest_droppable(buf_msg(skb), true);
	स_नकल(msg_data(buf_msg(skb)), evt, माप(*evt));
	skb_queue_head_init(&evtq);
	__skb_queue_tail(&evtq, skb);
	tipc_loopback_trace(net, &evtq);
	tipc_sk_rcv(net, &evtq);
पूर्ण

अटल पूर्णांक tipc_topsrv_work_start(काष्ठा tipc_topsrv *s)
अणु
	s->rcv_wq = alloc_ordered_workqueue("tipc_rcv", 0);
	अगर (!s->rcv_wq) अणु
		pr_err("can't start tipc receive workqueue\n");
		वापस -ENOMEM;
	पूर्ण

	s->send_wq = alloc_ordered_workqueue("tipc_send", 0);
	अगर (!s->send_wq) अणु
		pr_err("can't start tipc send workqueue\n");
		destroy_workqueue(s->rcv_wq);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tipc_topsrv_work_stop(काष्ठा tipc_topsrv *s)
अणु
	destroy_workqueue(s->rcv_wq);
	destroy_workqueue(s->send_wq);
पूर्ण

अटल पूर्णांक tipc_topsrv_start(काष्ठा net *net)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	स्थिर अक्षर name[] = "topology_server";
	काष्ठा tipc_topsrv *srv;
	पूर्णांक ret;

	srv = kzalloc(माप(*srv), GFP_ATOMIC);
	अगर (!srv)
		वापस -ENOMEM;

	srv->net = net;
	INIT_WORK(&srv->awork, tipc_topsrv_accept);

	strscpy(srv->name, name, माप(srv->name));
	tn->topsrv = srv;
	atomic_set(&tn->subscription_count, 0);

	spin_lock_init(&srv->idr_lock);
	idr_init(&srv->conn_idr);
	srv->idr_in_use = 0;

	ret = tipc_topsrv_work_start(srv);
	अगर (ret < 0)
		जाओ err_start;

	ret = tipc_topsrv_create_listener(srv);
	अगर (ret < 0)
		जाओ err_create;

	वापस 0;

err_create:
	tipc_topsrv_work_stop(srv);
err_start:
	kमुक्त(srv);
	वापस ret;
पूर्ण

अटल व्योम tipc_topsrv_stop(काष्ठा net *net)
अणु
	काष्ठा tipc_topsrv *srv = tipc_topsrv(net);
	काष्ठा socket *lsock = srv->listener;
	काष्ठा tipc_conn *con;
	पूर्णांक id;

	spin_lock_bh(&srv->idr_lock);
	क्रम (id = 0; srv->idr_in_use; id++) अणु
		con = idr_find(&srv->conn_idr, id);
		अगर (con) अणु
			spin_unlock_bh(&srv->idr_lock);
			tipc_conn_बंद(con);
			spin_lock_bh(&srv->idr_lock);
		पूर्ण
	पूर्ण
	__module_get(lsock->ops->owner);
	__module_get(lsock->sk->sk_prot_creator->owner);
	srv->listener = शून्य;
	spin_unlock_bh(&srv->idr_lock);
	sock_release(lsock);
	tipc_topsrv_work_stop(srv);
	idr_destroy(&srv->conn_idr);
	kमुक्त(srv);
पूर्ण

पूर्णांक __net_init tipc_topsrv_init_net(काष्ठा net *net)
अणु
	वापस tipc_topsrv_start(net);
पूर्ण

व्योम __net_निकास tipc_topsrv_निकास_net(काष्ठा net *net)
अणु
	tipc_topsrv_stop(net);
पूर्ण
