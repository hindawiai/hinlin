<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/crc32c.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/inet.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/net.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/socket.h>
#समावेश <linux/माला.स>
#अगर_घोषित	CONFIG_BLOCK
#समावेश <linux/bपन.स>
#पूर्ण_अगर	/* CONFIG_BLOCK */
#समावेश <linux/dns_resolver.h>
#समावेश <net/tcp.h>

#समावेश <linux/ceph/ceph_features.h>
#समावेश <linux/ceph/libceph.h>
#समावेश <linux/ceph/messenger.h>
#समावेश <linux/ceph/decode.h>
#समावेश <linux/ceph/pagelist.h>
#समावेश <linux/export.h>

/*
 * Ceph uses the messenger to exchange ceph_msg messages with other
 * hosts in the प्रणाली.  The messenger provides ordered and reliable
 * delivery.  We tolerate TCP disconnects by reconnecting (with
 * exponential backoff) in the हाल of a fault (disconnection, bad
 * crc, protocol error).  Acks allow sent messages to be discarded by
 * the sender.
 */

/*
 * We track the state of the socket on a given connection using
 * values defined below.  The transition to a new socket state is
 * handled by a function which verअगरies we aren't coming from an
 * unexpected state.
 *
 *      --------
 *      | NEW* |  transient initial state
 *      --------
 *          | con_sock_state_init()
 *          v
 *      ----------
 *      | CLOSED |  initialized, but no socket (and no
 *      ----------  TCP connection)
 *       ^      \
 *       |       \ con_sock_state_connecting()
 *       |        ----------------------
 *       |                              \
 *       + con_sock_state_बंदd()       \
 *       |+---------------------------    \
 *       | \                          \    \
 *       |  -----------                \    \
 *       |  | CLOSING |  socket event;  \    \
 *       |  -----------  aरुको बंद     \    \
 *       |       ^                        \   |
 *       |       |                         \  |
 *       |       + con_sock_state_closing() \ |
 *       |      / \                         | |
 *       |     /   ---------------          | |
 *       |    /                   \         v v
 *       |   /                    --------------
 *       |  /    -----------------| CONNECTING |  socket created, TCP
 *       |  |   /                 --------------  connect initiated
 *       |  |   | con_sock_state_connected()
 *       |  |   v
 *      -------------
 *      | CONNECTED |  TCP connection established
 *      -------------
 *
 * State values क्रम ceph_connection->sock_state; NEW is assumed to be 0.
 */

#घोषणा CON_SOCK_STATE_NEW		0	/* -> CLOSED */
#घोषणा CON_SOCK_STATE_CLOSED		1	/* -> CONNECTING */
#घोषणा CON_SOCK_STATE_CONNECTING	2	/* -> CONNECTED or -> CLOSING */
#घोषणा CON_SOCK_STATE_CONNECTED	3	/* -> CLOSING or -> CLOSED */
#घोषणा CON_SOCK_STATE_CLOSING		4	/* -> CLOSED */

अटल bool con_flag_valid(अचिन्हित दीर्घ con_flag)
अणु
	चयन (con_flag) अणु
	हाल CEPH_CON_F_LOSSYTX:
	हाल CEPH_CON_F_KEEPALIVE_PENDING:
	हाल CEPH_CON_F_WRITE_PENDING:
	हाल CEPH_CON_F_SOCK_CLOSED:
	हाल CEPH_CON_F_BACKOFF:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

व्योम ceph_con_flag_clear(काष्ठा ceph_connection *con, अचिन्हित दीर्घ con_flag)
अणु
	BUG_ON(!con_flag_valid(con_flag));

	clear_bit(con_flag, &con->flags);
पूर्ण

व्योम ceph_con_flag_set(काष्ठा ceph_connection *con, अचिन्हित दीर्घ con_flag)
अणु
	BUG_ON(!con_flag_valid(con_flag));

	set_bit(con_flag, &con->flags);
पूर्ण

bool ceph_con_flag_test(काष्ठा ceph_connection *con, अचिन्हित दीर्घ con_flag)
अणु
	BUG_ON(!con_flag_valid(con_flag));

	वापस test_bit(con_flag, &con->flags);
पूर्ण

bool ceph_con_flag_test_and_clear(काष्ठा ceph_connection *con,
				  अचिन्हित दीर्घ con_flag)
अणु
	BUG_ON(!con_flag_valid(con_flag));

	वापस test_and_clear_bit(con_flag, &con->flags);
पूर्ण

bool ceph_con_flag_test_and_set(काष्ठा ceph_connection *con,
				अचिन्हित दीर्घ con_flag)
अणु
	BUG_ON(!con_flag_valid(con_flag));

	वापस test_and_set_bit(con_flag, &con->flags);
पूर्ण

/* Slab caches क्रम frequently-allocated काष्ठाures */

अटल काष्ठा kmem_cache	*ceph_msg_cache;

#अगर_घोषित CONFIG_LOCKDEP
अटल काष्ठा lock_class_key socket_class;
#पूर्ण_अगर

अटल व्योम queue_con(काष्ठा ceph_connection *con);
अटल व्योम cancel_con(काष्ठा ceph_connection *con);
अटल व्योम ceph_con_workfn(काष्ठा work_काष्ठा *);
अटल व्योम con_fault(काष्ठा ceph_connection *con);

/*
 * Nicely render a sockaddr as a string.  An array of क्रमmatted
 * strings is used, to approximate reentrancy.
 */
#घोषणा ADDR_STR_COUNT_LOG	5	/* log2(# address strings in array) */
#घोषणा ADDR_STR_COUNT		(1 << ADDR_STR_COUNT_LOG)
#घोषणा ADDR_STR_COUNT_MASK	(ADDR_STR_COUNT - 1)
#घोषणा MAX_ADDR_STR_LEN	64	/* 54 is enough */

अटल अक्षर addr_str[ADDR_STR_COUNT][MAX_ADDR_STR_LEN];
अटल atomic_t addr_str_seq = ATOMIC_INIT(0);

काष्ठा page *ceph_zero_page;		/* used in certain error हालs */

स्थिर अक्षर *ceph_pr_addr(स्थिर काष्ठा ceph_entity_addr *addr)
अणु
	पूर्णांक i;
	अक्षर *s;
	काष्ठा sockaddr_storage ss = addr->in_addr; /* align */
	काष्ठा sockaddr_in *in4 = (काष्ठा sockaddr_in *)&ss;
	काष्ठा sockaddr_in6 *in6 = (काष्ठा sockaddr_in6 *)&ss;

	i = atomic_inc_वापस(&addr_str_seq) & ADDR_STR_COUNT_MASK;
	s = addr_str[i];

	चयन (ss.ss_family) अणु
	हाल AF_INET:
		snम_लिखो(s, MAX_ADDR_STR_LEN, "(%d)%pI4:%hu",
			 le32_to_cpu(addr->type), &in4->sin_addr,
			 ntohs(in4->sin_port));
		अवरोध;

	हाल AF_INET6:
		snम_लिखो(s, MAX_ADDR_STR_LEN, "(%d)[%pI6c]:%hu",
			 le32_to_cpu(addr->type), &in6->sin6_addr,
			 ntohs(in6->sin6_port));
		अवरोध;

	शेष:
		snम_लिखो(s, MAX_ADDR_STR_LEN, "(unknown sockaddr family %hu)",
			 ss.ss_family);
	पूर्ण

	वापस s;
पूर्ण
EXPORT_SYMBOL(ceph_pr_addr);

व्योम ceph_encode_my_addr(काष्ठा ceph_messenger *msgr)
अणु
	अगर (!ceph_msgr2(from_msgr(msgr))) अणु
		स_नकल(&msgr->my_enc_addr, &msgr->inst.addr,
		       माप(msgr->my_enc_addr));
		ceph_encode_banner_addr(&msgr->my_enc_addr);
	पूर्ण
पूर्ण

/*
 * work queue क्रम all पढ़ोing and writing to/from the socket.
 */
अटल काष्ठा workqueue_काष्ठा *ceph_msgr_wq;

अटल पूर्णांक ceph_msgr_slab_init(व्योम)
अणु
	BUG_ON(ceph_msg_cache);
	ceph_msg_cache = KMEM_CACHE(ceph_msg, 0);
	अगर (!ceph_msg_cache)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम ceph_msgr_slab_निकास(व्योम)
अणु
	BUG_ON(!ceph_msg_cache);
	kmem_cache_destroy(ceph_msg_cache);
	ceph_msg_cache = शून्य;
पूर्ण

अटल व्योम _ceph_msgr_निकास(व्योम)
अणु
	अगर (ceph_msgr_wq) अणु
		destroy_workqueue(ceph_msgr_wq);
		ceph_msgr_wq = शून्य;
	पूर्ण

	BUG_ON(!ceph_zero_page);
	put_page(ceph_zero_page);
	ceph_zero_page = शून्य;

	ceph_msgr_slab_निकास();
पूर्ण

पूर्णांक __init ceph_msgr_init(व्योम)
अणु
	अगर (ceph_msgr_slab_init())
		वापस -ENOMEM;

	BUG_ON(ceph_zero_page);
	ceph_zero_page = ZERO_PAGE(0);
	get_page(ceph_zero_page);

	/*
	 * The number of active work items is limited by the number of
	 * connections, so leave @max_active at शेष.
	 */
	ceph_msgr_wq = alloc_workqueue("ceph-msgr", WQ_MEM_RECLAIM, 0);
	अगर (ceph_msgr_wq)
		वापस 0;

	pr_err("msgr_init failed to create workqueue\n");
	_ceph_msgr_निकास();

	वापस -ENOMEM;
पूर्ण

व्योम ceph_msgr_निकास(व्योम)
अणु
	BUG_ON(ceph_msgr_wq == शून्य);

	_ceph_msgr_निकास();
पूर्ण

व्योम ceph_msgr_flush(व्योम)
अणु
	flush_workqueue(ceph_msgr_wq);
पूर्ण
EXPORT_SYMBOL(ceph_msgr_flush);

/* Connection socket state transition functions */

अटल व्योम con_sock_state_init(काष्ठा ceph_connection *con)
अणु
	पूर्णांक old_state;

	old_state = atomic_xchg(&con->sock_state, CON_SOCK_STATE_CLOSED);
	अगर (WARN_ON(old_state != CON_SOCK_STATE_NEW))
		prपूर्णांकk("%s: unexpected old state %d\n", __func__, old_state);
	करोut("%s con %p sock %d -> %d\n", __func__, con, old_state,
	     CON_SOCK_STATE_CLOSED);
पूर्ण

अटल व्योम con_sock_state_connecting(काष्ठा ceph_connection *con)
अणु
	पूर्णांक old_state;

	old_state = atomic_xchg(&con->sock_state, CON_SOCK_STATE_CONNECTING);
	अगर (WARN_ON(old_state != CON_SOCK_STATE_CLOSED))
		prपूर्णांकk("%s: unexpected old state %d\n", __func__, old_state);
	करोut("%s con %p sock %d -> %d\n", __func__, con, old_state,
	     CON_SOCK_STATE_CONNECTING);
पूर्ण

अटल व्योम con_sock_state_connected(काष्ठा ceph_connection *con)
अणु
	पूर्णांक old_state;

	old_state = atomic_xchg(&con->sock_state, CON_SOCK_STATE_CONNECTED);
	अगर (WARN_ON(old_state != CON_SOCK_STATE_CONNECTING))
		prपूर्णांकk("%s: unexpected old state %d\n", __func__, old_state);
	करोut("%s con %p sock %d -> %d\n", __func__, con, old_state,
	     CON_SOCK_STATE_CONNECTED);
पूर्ण

अटल व्योम con_sock_state_closing(काष्ठा ceph_connection *con)
अणु
	पूर्णांक old_state;

	old_state = atomic_xchg(&con->sock_state, CON_SOCK_STATE_CLOSING);
	अगर (WARN_ON(old_state != CON_SOCK_STATE_CONNECTING &&
			old_state != CON_SOCK_STATE_CONNECTED &&
			old_state != CON_SOCK_STATE_CLOSING))
		prपूर्णांकk("%s: unexpected old state %d\n", __func__, old_state);
	करोut("%s con %p sock %d -> %d\n", __func__, con, old_state,
	     CON_SOCK_STATE_CLOSING);
पूर्ण

अटल व्योम con_sock_state_बंदd(काष्ठा ceph_connection *con)
अणु
	पूर्णांक old_state;

	old_state = atomic_xchg(&con->sock_state, CON_SOCK_STATE_CLOSED);
	अगर (WARN_ON(old_state != CON_SOCK_STATE_CONNECTED &&
		    old_state != CON_SOCK_STATE_CLOSING &&
		    old_state != CON_SOCK_STATE_CONNECTING &&
		    old_state != CON_SOCK_STATE_CLOSED))
		prपूर्णांकk("%s: unexpected old state %d\n", __func__, old_state);
	करोut("%s con %p sock %d -> %d\n", __func__, con, old_state,
	     CON_SOCK_STATE_CLOSED);
पूर्ण

/*
 * socket callback functions
 */

/* data available on socket, or listen socket received a connect */
अटल व्योम ceph_sock_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा ceph_connection *con = sk->sk_user_data;
	अगर (atomic_पढ़ो(&con->msgr->stopping)) अणु
		वापस;
	पूर्ण

	अगर (sk->sk_state != TCP_CLOSE_WAIT) अणु
		करोut("%s %p state = %d, queueing work\n", __func__,
		     con, con->state);
		queue_con(con);
	पूर्ण
पूर्ण

/* socket has buffer space क्रम writing */
अटल व्योम ceph_sock_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा ceph_connection *con = sk->sk_user_data;

	/* only queue to workqueue अगर there is data we want to ग_लिखो,
	 * and there is sufficient space in the socket buffer to accept
	 * more data.  clear SOCK_NOSPACE so that ceph_sock_ग_लिखो_space()
	 * करोesn't get called again until try_ग_लिखो() fills the socket
	 * buffer. See net/ipv4/tcp_input.c:tcp_check_space()
	 * and net/core/stream.c:sk_stream_ग_लिखो_space().
	 */
	अगर (ceph_con_flag_test(con, CEPH_CON_F_WRITE_PENDING)) अणु
		अगर (sk_stream_is_ग_लिखोable(sk)) अणु
			करोut("%s %p queueing write work\n", __func__, con);
			clear_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
			queue_con(con);
		पूर्ण
	पूर्ण अन्यथा अणु
		करोut("%s %p nothing to write\n", __func__, con);
	पूर्ण
पूर्ण

/* socket's state has changed */
अटल व्योम ceph_sock_state_change(काष्ठा sock *sk)
अणु
	काष्ठा ceph_connection *con = sk->sk_user_data;

	करोut("%s %p state = %d sk_state = %u\n", __func__,
	     con, con->state, sk->sk_state);

	चयन (sk->sk_state) अणु
	हाल TCP_CLOSE:
		करोut("%s TCP_CLOSE\n", __func__);
		fallthrough;
	हाल TCP_CLOSE_WAIT:
		करोut("%s TCP_CLOSE_WAIT\n", __func__);
		con_sock_state_closing(con);
		ceph_con_flag_set(con, CEPH_CON_F_SOCK_CLOSED);
		queue_con(con);
		अवरोध;
	हाल TCP_ESTABLISHED:
		करोut("%s TCP_ESTABLISHED\n", __func__);
		con_sock_state_connected(con);
		queue_con(con);
		अवरोध;
	शेष:	/* Everything अन्यथा is unपूर्णांकeresting */
		अवरोध;
	पूर्ण
पूर्ण

/*
 * set up socket callbacks
 */
अटल व्योम set_sock_callbacks(काष्ठा socket *sock,
			       काष्ठा ceph_connection *con)
अणु
	काष्ठा sock *sk = sock->sk;
	sk->sk_user_data = con;
	sk->sk_data_पढ़ोy = ceph_sock_data_पढ़ोy;
	sk->sk_ग_लिखो_space = ceph_sock_ग_लिखो_space;
	sk->sk_state_change = ceph_sock_state_change;
पूर्ण


/*
 * socket helpers
 */

/*
 * initiate connection to a remote socket.
 */
पूर्णांक ceph_tcp_connect(काष्ठा ceph_connection *con)
अणु
	काष्ठा sockaddr_storage ss = con->peer_addr.in_addr; /* align */
	काष्ठा socket *sock;
	अचिन्हित पूर्णांक noio_flag;
	पूर्णांक ret;

	करोut("%s con %p peer_addr %s\n", __func__, con,
	     ceph_pr_addr(&con->peer_addr));
	BUG_ON(con->sock);

	/* sock_create_kern() allocates with GFP_KERNEL */
	noio_flag = meदो_स्मृति_noio_save();
	ret = sock_create_kern(पढ़ो_pnet(&con->msgr->net), ss.ss_family,
			       SOCK_STREAM, IPPROTO_TCP, &sock);
	meदो_स्मृति_noio_restore(noio_flag);
	अगर (ret)
		वापस ret;
	sock->sk->sk_allocation = GFP_NOFS;

#अगर_घोषित CONFIG_LOCKDEP
	lockdep_set_class(&sock->sk->sk_lock, &socket_class);
#पूर्ण_अगर

	set_sock_callbacks(sock, con);

	con_sock_state_connecting(con);
	ret = sock->ops->connect(sock, (काष्ठा sockaddr *)&ss, माप(ss),
				 O_NONBLOCK);
	अगर (ret == -EINPROGRESS) अणु
		करोut("connect %s EINPROGRESS sk_state = %u\n",
		     ceph_pr_addr(&con->peer_addr),
		     sock->sk->sk_state);
	पूर्ण अन्यथा अगर (ret < 0) अणु
		pr_err("connect %s error %d\n",
		       ceph_pr_addr(&con->peer_addr), ret);
		sock_release(sock);
		वापस ret;
	पूर्ण

	अगर (ceph_test_opt(from_msgr(con->msgr), TCP_NODELAY))
		tcp_sock_set_nodelay(sock->sk);

	con->sock = sock;
	वापस 0;
पूर्ण

/*
 * Shutकरोwn/बंद the socket क्रम the given connection.
 */
पूर्णांक ceph_con_बंद_socket(काष्ठा ceph_connection *con)
अणु
	पूर्णांक rc = 0;

	करोut("%s con %p sock %p\n", __func__, con, con->sock);
	अगर (con->sock) अणु
		rc = con->sock->ops->shutकरोwn(con->sock, SHUT_RDWR);
		sock_release(con->sock);
		con->sock = शून्य;
	पूर्ण

	/*
	 * Forcibly clear the SOCK_CLOSED flag.  It माला_लो set
	 * independent of the connection mutex, and we could have
	 * received a socket बंद event beक्रमe we had the chance to
	 * shut the socket करोwn.
	 */
	ceph_con_flag_clear(con, CEPH_CON_F_SOCK_CLOSED);

	con_sock_state_बंदd(con);
	वापस rc;
पूर्ण

अटल व्योम ceph_con_reset_protocol(काष्ठा ceph_connection *con)
अणु
	करोut("%s con %p\n", __func__, con);

	ceph_con_बंद_socket(con);
	अगर (con->in_msg) अणु
		WARN_ON(con->in_msg->con != con);
		ceph_msg_put(con->in_msg);
		con->in_msg = शून्य;
	पूर्ण
	अगर (con->out_msg) अणु
		WARN_ON(con->out_msg->con != con);
		ceph_msg_put(con->out_msg);
		con->out_msg = शून्य;
	पूर्ण

	अगर (ceph_msgr2(from_msgr(con->msgr)))
		ceph_con_v2_reset_protocol(con);
	अन्यथा
		ceph_con_v1_reset_protocol(con);
पूर्ण

/*
 * Reset a connection.  Discard all incoming and outgoing messages
 * and clear *_seq state.
 */
अटल व्योम ceph_msg_हटाओ(काष्ठा ceph_msg *msg)
अणु
	list_del_init(&msg->list_head);

	ceph_msg_put(msg);
पूर्ण

अटल व्योम ceph_msg_हटाओ_list(काष्ठा list_head *head)
अणु
	जबतक (!list_empty(head)) अणु
		काष्ठा ceph_msg *msg = list_first_entry(head, काष्ठा ceph_msg,
							list_head);
		ceph_msg_हटाओ(msg);
	पूर्ण
पूर्ण

व्योम ceph_con_reset_session(काष्ठा ceph_connection *con)
अणु
	करोut("%s con %p\n", __func__, con);

	WARN_ON(con->in_msg);
	WARN_ON(con->out_msg);
	ceph_msg_हटाओ_list(&con->out_queue);
	ceph_msg_हटाओ_list(&con->out_sent);
	con->out_seq = 0;
	con->in_seq = 0;
	con->in_seq_acked = 0;

	अगर (ceph_msgr2(from_msgr(con->msgr)))
		ceph_con_v2_reset_session(con);
	अन्यथा
		ceph_con_v1_reset_session(con);
पूर्ण

/*
 * mark a peer करोwn.  drop any खोलो connections.
 */
व्योम ceph_con_बंद(काष्ठा ceph_connection *con)
अणु
	mutex_lock(&con->mutex);
	करोut("con_close %p peer %s\n", con, ceph_pr_addr(&con->peer_addr));
	con->state = CEPH_CON_S_CLOSED;

	ceph_con_flag_clear(con, CEPH_CON_F_LOSSYTX);  /* so we retry next
							  connect */
	ceph_con_flag_clear(con, CEPH_CON_F_KEEPALIVE_PENDING);
	ceph_con_flag_clear(con, CEPH_CON_F_WRITE_PENDING);
	ceph_con_flag_clear(con, CEPH_CON_F_BACKOFF);

	ceph_con_reset_protocol(con);
	ceph_con_reset_session(con);
	cancel_con(con);
	mutex_unlock(&con->mutex);
पूर्ण
EXPORT_SYMBOL(ceph_con_बंद);

/*
 * Reखोलो a बंदd connection, with a new peer address.
 */
व्योम ceph_con_खोलो(काष्ठा ceph_connection *con,
		   __u8 entity_type, __u64 entity_num,
		   काष्ठा ceph_entity_addr *addr)
अणु
	mutex_lock(&con->mutex);
	करोut("con_open %p %s\n", con, ceph_pr_addr(addr));

	WARN_ON(con->state != CEPH_CON_S_CLOSED);
	con->state = CEPH_CON_S_PREOPEN;

	con->peer_name.type = (__u8) entity_type;
	con->peer_name.num = cpu_to_le64(entity_num);

	स_नकल(&con->peer_addr, addr, माप(*addr));
	con->delay = 0;      /* reset backoff memory */
	mutex_unlock(&con->mutex);
	queue_con(con);
पूर्ण
EXPORT_SYMBOL(ceph_con_खोलो);

/*
 * वापस true अगर this connection ever successfully खोलोed
 */
bool ceph_con_खोलोed(काष्ठा ceph_connection *con)
अणु
	अगर (ceph_msgr2(from_msgr(con->msgr)))
		वापस ceph_con_v2_खोलोed(con);

	वापस ceph_con_v1_खोलोed(con);
पूर्ण

/*
 * initialize a new connection.
 */
व्योम ceph_con_init(काष्ठा ceph_connection *con, व्योम *निजी,
	स्थिर काष्ठा ceph_connection_operations *ops,
	काष्ठा ceph_messenger *msgr)
अणु
	करोut("con_init %p\n", con);
	स_रखो(con, 0, माप(*con));
	con->निजी = निजी;
	con->ops = ops;
	con->msgr = msgr;

	con_sock_state_init(con);

	mutex_init(&con->mutex);
	INIT_LIST_HEAD(&con->out_queue);
	INIT_LIST_HEAD(&con->out_sent);
	INIT_DELAYED_WORK(&con->work, ceph_con_workfn);

	con->state = CEPH_CON_S_CLOSED;
पूर्ण
EXPORT_SYMBOL(ceph_con_init);

/*
 * We मुख्यtain a global counter to order connection attempts.  Get
 * a unique seq greater than @gt.
 */
u32 ceph_get_global_seq(काष्ठा ceph_messenger *msgr, u32 gt)
अणु
	u32 ret;

	spin_lock(&msgr->global_seq_lock);
	अगर (msgr->global_seq < gt)
		msgr->global_seq = gt;
	ret = ++msgr->global_seq;
	spin_unlock(&msgr->global_seq_lock);
	वापस ret;
पूर्ण

/*
 * Discard messages that have been acked by the server.
 */
व्योम ceph_con_discard_sent(काष्ठा ceph_connection *con, u64 ack_seq)
अणु
	काष्ठा ceph_msg *msg;
	u64 seq;

	करोut("%s con %p ack_seq %llu\n", __func__, con, ack_seq);
	जबतक (!list_empty(&con->out_sent)) अणु
		msg = list_first_entry(&con->out_sent, काष्ठा ceph_msg,
				       list_head);
		WARN_ON(msg->needs_out_seq);
		seq = le64_to_cpu(msg->hdr.seq);
		अगर (seq > ack_seq)
			अवरोध;

		करोut("%s con %p discarding msg %p seq %llu\n", __func__, con,
		     msg, seq);
		ceph_msg_हटाओ(msg);
	पूर्ण
पूर्ण

/*
 * Discard messages that have been requeued in con_fault(), up to
 * reconnect_seq.  This aव्योमs gratuitously resending messages that
 * the server had received and handled prior to reconnect.
 */
व्योम ceph_con_discard_requeued(काष्ठा ceph_connection *con, u64 reconnect_seq)
अणु
	काष्ठा ceph_msg *msg;
	u64 seq;

	करोut("%s con %p reconnect_seq %llu\n", __func__, con, reconnect_seq);
	जबतक (!list_empty(&con->out_queue)) अणु
		msg = list_first_entry(&con->out_queue, काष्ठा ceph_msg,
				       list_head);
		अगर (msg->needs_out_seq)
			अवरोध;
		seq = le64_to_cpu(msg->hdr.seq);
		अगर (seq > reconnect_seq)
			अवरोध;

		करोut("%s con %p discarding msg %p seq %llu\n", __func__, con,
		     msg, seq);
		ceph_msg_हटाओ(msg);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_BLOCK

/*
 * For a bio data item, a piece is whatever reमुख्यs of the next
 * entry in the current bio iovec, or the first entry in the next
 * bio in the list.
 */
अटल व्योम ceph_msg_data_bio_cursor_init(काष्ठा ceph_msg_data_cursor *cursor,
					माप_प्रकार length)
अणु
	काष्ठा ceph_msg_data *data = cursor->data;
	काष्ठा ceph_bio_iter *it = &cursor->bio_iter;

	cursor->resid = min_t(माप_प्रकार, length, data->bio_length);
	*it = data->bio_pos;
	अगर (cursor->resid < it->iter.bi_size)
		it->iter.bi_size = cursor->resid;

	BUG_ON(cursor->resid < bio_iter_len(it->bio, it->iter));
	cursor->last_piece = cursor->resid == bio_iter_len(it->bio, it->iter);
पूर्ण

अटल काष्ठा page *ceph_msg_data_bio_next(काष्ठा ceph_msg_data_cursor *cursor,
						माप_प्रकार *page_offset,
						माप_प्रकार *length)
अणु
	काष्ठा bio_vec bv = bio_iter_iovec(cursor->bio_iter.bio,
					   cursor->bio_iter.iter);

	*page_offset = bv.bv_offset;
	*length = bv.bv_len;
	वापस bv.bv_page;
पूर्ण

अटल bool ceph_msg_data_bio_advance(काष्ठा ceph_msg_data_cursor *cursor,
					माप_प्रकार bytes)
अणु
	काष्ठा ceph_bio_iter *it = &cursor->bio_iter;
	काष्ठा page *page = bio_iter_page(it->bio, it->iter);

	BUG_ON(bytes > cursor->resid);
	BUG_ON(bytes > bio_iter_len(it->bio, it->iter));
	cursor->resid -= bytes;
	bio_advance_iter(it->bio, &it->iter, bytes);

	अगर (!cursor->resid) अणु
		BUG_ON(!cursor->last_piece);
		वापस false;   /* no more data */
	पूर्ण

	अगर (!bytes || (it->iter.bi_size && it->iter.bi_bvec_करोne &&
		       page == bio_iter_page(it->bio, it->iter)))
		वापस false;	/* more bytes to process in this segment */

	अगर (!it->iter.bi_size) अणु
		it->bio = it->bio->bi_next;
		it->iter = it->bio->bi_iter;
		अगर (cursor->resid < it->iter.bi_size)
			it->iter.bi_size = cursor->resid;
	पूर्ण

	BUG_ON(cursor->last_piece);
	BUG_ON(cursor->resid < bio_iter_len(it->bio, it->iter));
	cursor->last_piece = cursor->resid == bio_iter_len(it->bio, it->iter);
	वापस true;
पूर्ण
#पूर्ण_अगर /* CONFIG_BLOCK */

अटल व्योम ceph_msg_data_bvecs_cursor_init(काष्ठा ceph_msg_data_cursor *cursor,
					माप_प्रकार length)
अणु
	काष्ठा ceph_msg_data *data = cursor->data;
	काष्ठा bio_vec *bvecs = data->bvec_pos.bvecs;

	cursor->resid = min_t(माप_प्रकार, length, data->bvec_pos.iter.bi_size);
	cursor->bvec_iter = data->bvec_pos.iter;
	cursor->bvec_iter.bi_size = cursor->resid;

	BUG_ON(cursor->resid < bvec_iter_len(bvecs, cursor->bvec_iter));
	cursor->last_piece =
	    cursor->resid == bvec_iter_len(bvecs, cursor->bvec_iter);
पूर्ण

अटल काष्ठा page *ceph_msg_data_bvecs_next(काष्ठा ceph_msg_data_cursor *cursor,
						माप_प्रकार *page_offset,
						माप_प्रकार *length)
अणु
	काष्ठा bio_vec bv = bvec_iter_bvec(cursor->data->bvec_pos.bvecs,
					   cursor->bvec_iter);

	*page_offset = bv.bv_offset;
	*length = bv.bv_len;
	वापस bv.bv_page;
पूर्ण

अटल bool ceph_msg_data_bvecs_advance(काष्ठा ceph_msg_data_cursor *cursor,
					माप_प्रकार bytes)
अणु
	काष्ठा bio_vec *bvecs = cursor->data->bvec_pos.bvecs;
	काष्ठा page *page = bvec_iter_page(bvecs, cursor->bvec_iter);

	BUG_ON(bytes > cursor->resid);
	BUG_ON(bytes > bvec_iter_len(bvecs, cursor->bvec_iter));
	cursor->resid -= bytes;
	bvec_iter_advance(bvecs, &cursor->bvec_iter, bytes);

	अगर (!cursor->resid) अणु
		BUG_ON(!cursor->last_piece);
		वापस false;   /* no more data */
	पूर्ण

	अगर (!bytes || (cursor->bvec_iter.bi_bvec_करोne &&
		       page == bvec_iter_page(bvecs, cursor->bvec_iter)))
		वापस false;	/* more bytes to process in this segment */

	BUG_ON(cursor->last_piece);
	BUG_ON(cursor->resid < bvec_iter_len(bvecs, cursor->bvec_iter));
	cursor->last_piece =
	    cursor->resid == bvec_iter_len(bvecs, cursor->bvec_iter);
	वापस true;
पूर्ण

/*
 * For a page array, a piece comes from the first page in the array
 * that has not alपढ़ोy been fully consumed.
 */
अटल व्योम ceph_msg_data_pages_cursor_init(काष्ठा ceph_msg_data_cursor *cursor,
					माप_प्रकार length)
अणु
	काष्ठा ceph_msg_data *data = cursor->data;
	पूर्णांक page_count;

	BUG_ON(data->type != CEPH_MSG_DATA_PAGES);

	BUG_ON(!data->pages);
	BUG_ON(!data->length);

	cursor->resid = min(length, data->length);
	page_count = calc_pages_क्रम(data->alignment, (u64)data->length);
	cursor->page_offset = data->alignment & ~PAGE_MASK;
	cursor->page_index = 0;
	BUG_ON(page_count > (पूर्णांक)अच_लघु_उच्च);
	cursor->page_count = (अचिन्हित लघु)page_count;
	BUG_ON(length > SIZE_MAX - cursor->page_offset);
	cursor->last_piece = cursor->page_offset + cursor->resid <= PAGE_SIZE;
पूर्ण

अटल काष्ठा page *
ceph_msg_data_pages_next(काष्ठा ceph_msg_data_cursor *cursor,
					माप_प्रकार *page_offset, माप_प्रकार *length)
अणु
	काष्ठा ceph_msg_data *data = cursor->data;

	BUG_ON(data->type != CEPH_MSG_DATA_PAGES);

	BUG_ON(cursor->page_index >= cursor->page_count);
	BUG_ON(cursor->page_offset >= PAGE_SIZE);

	*page_offset = cursor->page_offset;
	अगर (cursor->last_piece)
		*length = cursor->resid;
	अन्यथा
		*length = PAGE_SIZE - *page_offset;

	वापस data->pages[cursor->page_index];
पूर्ण

अटल bool ceph_msg_data_pages_advance(काष्ठा ceph_msg_data_cursor *cursor,
						माप_प्रकार bytes)
अणु
	BUG_ON(cursor->data->type != CEPH_MSG_DATA_PAGES);

	BUG_ON(cursor->page_offset + bytes > PAGE_SIZE);

	/* Advance the cursor page offset */

	cursor->resid -= bytes;
	cursor->page_offset = (cursor->page_offset + bytes) & ~PAGE_MASK;
	अगर (!bytes || cursor->page_offset)
		वापस false;	/* more bytes to process in the current page */

	अगर (!cursor->resid)
		वापस false;   /* no more data */

	/* Move on to the next page; offset is alपढ़ोy at 0 */

	BUG_ON(cursor->page_index >= cursor->page_count);
	cursor->page_index++;
	cursor->last_piece = cursor->resid <= PAGE_SIZE;

	वापस true;
पूर्ण

/*
 * For a pagelist, a piece is whatever reमुख्यs to be consumed in the
 * first page in the list, or the front of the next page.
 */
अटल व्योम
ceph_msg_data_pagelist_cursor_init(काष्ठा ceph_msg_data_cursor *cursor,
					माप_प्रकार length)
अणु
	काष्ठा ceph_msg_data *data = cursor->data;
	काष्ठा ceph_pagelist *pagelist;
	काष्ठा page *page;

	BUG_ON(data->type != CEPH_MSG_DATA_PAGELIST);

	pagelist = data->pagelist;
	BUG_ON(!pagelist);

	अगर (!length)
		वापस;		/* pagelist can be asचिन्हित but empty */

	BUG_ON(list_empty(&pagelist->head));
	page = list_first_entry(&pagelist->head, काष्ठा page, lru);

	cursor->resid = min(length, pagelist->length);
	cursor->page = page;
	cursor->offset = 0;
	cursor->last_piece = cursor->resid <= PAGE_SIZE;
पूर्ण

अटल काष्ठा page *
ceph_msg_data_pagelist_next(काष्ठा ceph_msg_data_cursor *cursor,
				माप_प्रकार *page_offset, माप_प्रकार *length)
अणु
	काष्ठा ceph_msg_data *data = cursor->data;
	काष्ठा ceph_pagelist *pagelist;

	BUG_ON(data->type != CEPH_MSG_DATA_PAGELIST);

	pagelist = data->pagelist;
	BUG_ON(!pagelist);

	BUG_ON(!cursor->page);
	BUG_ON(cursor->offset + cursor->resid != pagelist->length);

	/* offset of first page in pagelist is always 0 */
	*page_offset = cursor->offset & ~PAGE_MASK;
	अगर (cursor->last_piece)
		*length = cursor->resid;
	अन्यथा
		*length = PAGE_SIZE - *page_offset;

	वापस cursor->page;
पूर्ण

अटल bool ceph_msg_data_pagelist_advance(काष्ठा ceph_msg_data_cursor *cursor,
						माप_प्रकार bytes)
अणु
	काष्ठा ceph_msg_data *data = cursor->data;
	काष्ठा ceph_pagelist *pagelist;

	BUG_ON(data->type != CEPH_MSG_DATA_PAGELIST);

	pagelist = data->pagelist;
	BUG_ON(!pagelist);

	BUG_ON(cursor->offset + cursor->resid != pagelist->length);
	BUG_ON((cursor->offset & ~PAGE_MASK) + bytes > PAGE_SIZE);

	/* Advance the cursor offset */

	cursor->resid -= bytes;
	cursor->offset += bytes;
	/* offset of first page in pagelist is always 0 */
	अगर (!bytes || cursor->offset & ~PAGE_MASK)
		वापस false;	/* more bytes to process in the current page */

	अगर (!cursor->resid)
		वापस false;   /* no more data */

	/* Move on to the next page */

	BUG_ON(list_is_last(&cursor->page->lru, &pagelist->head));
	cursor->page = list_next_entry(cursor->page, lru);
	cursor->last_piece = cursor->resid <= PAGE_SIZE;

	वापस true;
पूर्ण

/*
 * Message data is handled (sent or received) in pieces, where each
 * piece resides on a single page.  The network layer might not
 * consume an entire piece at once.  A data item's cursor keeps
 * track of which piece is next to process and how much reमुख्यs to
 * be processed in that piece.  It also tracks whether the current
 * piece is the last one in the data item.
 */
अटल व्योम __ceph_msg_data_cursor_init(काष्ठा ceph_msg_data_cursor *cursor)
अणु
	माप_प्रकार length = cursor->total_resid;

	चयन (cursor->data->type) अणु
	हाल CEPH_MSG_DATA_PAGELIST:
		ceph_msg_data_pagelist_cursor_init(cursor, length);
		अवरोध;
	हाल CEPH_MSG_DATA_PAGES:
		ceph_msg_data_pages_cursor_init(cursor, length);
		अवरोध;
#अगर_घोषित CONFIG_BLOCK
	हाल CEPH_MSG_DATA_BIO:
		ceph_msg_data_bio_cursor_init(cursor, length);
		अवरोध;
#पूर्ण_अगर /* CONFIG_BLOCK */
	हाल CEPH_MSG_DATA_BVECS:
		ceph_msg_data_bvecs_cursor_init(cursor, length);
		अवरोध;
	हाल CEPH_MSG_DATA_NONE:
	शेष:
		/* BUG(); */
		अवरोध;
	पूर्ण
	cursor->need_crc = true;
पूर्ण

व्योम ceph_msg_data_cursor_init(काष्ठा ceph_msg_data_cursor *cursor,
			       काष्ठा ceph_msg *msg, माप_प्रकार length)
अणु
	BUG_ON(!length);
	BUG_ON(length > msg->data_length);
	BUG_ON(!msg->num_data_items);

	cursor->total_resid = length;
	cursor->data = msg->data;

	__ceph_msg_data_cursor_init(cursor);
पूर्ण

/*
 * Return the page containing the next piece to process क्रम a given
 * data item, and supply the page offset and length of that piece.
 * Indicate whether this is the last piece in this data item.
 */
काष्ठा page *ceph_msg_data_next(काष्ठा ceph_msg_data_cursor *cursor,
				माप_प्रकार *page_offset, माप_प्रकार *length,
				bool *last_piece)
अणु
	काष्ठा page *page;

	चयन (cursor->data->type) अणु
	हाल CEPH_MSG_DATA_PAGELIST:
		page = ceph_msg_data_pagelist_next(cursor, page_offset, length);
		अवरोध;
	हाल CEPH_MSG_DATA_PAGES:
		page = ceph_msg_data_pages_next(cursor, page_offset, length);
		अवरोध;
#अगर_घोषित CONFIG_BLOCK
	हाल CEPH_MSG_DATA_BIO:
		page = ceph_msg_data_bio_next(cursor, page_offset, length);
		अवरोध;
#पूर्ण_अगर /* CONFIG_BLOCK */
	हाल CEPH_MSG_DATA_BVECS:
		page = ceph_msg_data_bvecs_next(cursor, page_offset, length);
		अवरोध;
	हाल CEPH_MSG_DATA_NONE:
	शेष:
		page = शून्य;
		अवरोध;
	पूर्ण

	BUG_ON(!page);
	BUG_ON(*page_offset + *length > PAGE_SIZE);
	BUG_ON(!*length);
	BUG_ON(*length > cursor->resid);
	अगर (last_piece)
		*last_piece = cursor->last_piece;

	वापस page;
पूर्ण

/*
 * Returns true अगर the result moves the cursor on to the next piece
 * of the data item.
 */
व्योम ceph_msg_data_advance(काष्ठा ceph_msg_data_cursor *cursor, माप_प्रकार bytes)
अणु
	bool new_piece;

	BUG_ON(bytes > cursor->resid);
	चयन (cursor->data->type) अणु
	हाल CEPH_MSG_DATA_PAGELIST:
		new_piece = ceph_msg_data_pagelist_advance(cursor, bytes);
		अवरोध;
	हाल CEPH_MSG_DATA_PAGES:
		new_piece = ceph_msg_data_pages_advance(cursor, bytes);
		अवरोध;
#अगर_घोषित CONFIG_BLOCK
	हाल CEPH_MSG_DATA_BIO:
		new_piece = ceph_msg_data_bio_advance(cursor, bytes);
		अवरोध;
#पूर्ण_अगर /* CONFIG_BLOCK */
	हाल CEPH_MSG_DATA_BVECS:
		new_piece = ceph_msg_data_bvecs_advance(cursor, bytes);
		अवरोध;
	हाल CEPH_MSG_DATA_NONE:
	शेष:
		BUG();
		अवरोध;
	पूर्ण
	cursor->total_resid -= bytes;

	अगर (!cursor->resid && cursor->total_resid) अणु
		WARN_ON(!cursor->last_piece);
		cursor->data++;
		__ceph_msg_data_cursor_init(cursor);
		new_piece = true;
	पूर्ण
	cursor->need_crc = new_piece;
पूर्ण

u32 ceph_crc32c_page(u32 crc, काष्ठा page *page, अचिन्हित पूर्णांक page_offset,
		     अचिन्हित पूर्णांक length)
अणु
	अक्षर *kaddr;

	kaddr = kmap(page);
	BUG_ON(kaddr == शून्य);
	crc = crc32c(crc, kaddr + page_offset, length);
	kunmap(page);

	वापस crc;
पूर्ण

bool ceph_addr_is_blank(स्थिर काष्ठा ceph_entity_addr *addr)
अणु
	काष्ठा sockaddr_storage ss = addr->in_addr; /* align */
	काष्ठा in_addr *addr4 = &((काष्ठा sockaddr_in *)&ss)->sin_addr;
	काष्ठा in6_addr *addr6 = &((काष्ठा sockaddr_in6 *)&ss)->sin6_addr;

	चयन (ss.ss_family) अणु
	हाल AF_INET:
		वापस addr4->s_addr == htonl(INADDR_ANY);
	हाल AF_INET6:
		वापस ipv6_addr_any(addr6);
	शेष:
		वापस true;
	पूर्ण
पूर्ण

पूर्णांक ceph_addr_port(स्थिर काष्ठा ceph_entity_addr *addr)
अणु
	चयन (get_unaligned(&addr->in_addr.ss_family)) अणु
	हाल AF_INET:
		वापस ntohs(get_unaligned(&((काष्ठा sockaddr_in *)&addr->in_addr)->sin_port));
	हाल AF_INET6:
		वापस ntohs(get_unaligned(&((काष्ठा sockaddr_in6 *)&addr->in_addr)->sin6_port));
	पूर्ण
	वापस 0;
पूर्ण

व्योम ceph_addr_set_port(काष्ठा ceph_entity_addr *addr, पूर्णांक p)
अणु
	चयन (get_unaligned(&addr->in_addr.ss_family)) अणु
	हाल AF_INET:
		put_unaligned(htons(p), &((काष्ठा sockaddr_in *)&addr->in_addr)->sin_port);
		अवरोध;
	हाल AF_INET6:
		put_unaligned(htons(p), &((काष्ठा sockaddr_in6 *)&addr->in_addr)->sin6_port);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Unlike other *_pton function semantics, zero indicates success.
 */
अटल पूर्णांक ceph_pton(स्थिर अक्षर *str, माप_प्रकार len, काष्ठा ceph_entity_addr *addr,
		अक्षर delim, स्थिर अक्षर **ipend)
अणु
	स_रखो(&addr->in_addr, 0, माप(addr->in_addr));

	अगर (in4_pton(str, len, (u8 *)&((काष्ठा sockaddr_in *)&addr->in_addr)->sin_addr.s_addr, delim, ipend)) अणु
		put_unaligned(AF_INET, &addr->in_addr.ss_family);
		वापस 0;
	पूर्ण

	अगर (in6_pton(str, len, (u8 *)&((काष्ठा sockaddr_in6 *)&addr->in_addr)->sin6_addr.s6_addr, delim, ipend)) अणु
		put_unaligned(AF_INET6, &addr->in_addr.ss_family);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * Extract hostname string and resolve using kernel DNS facility.
 */
#अगर_घोषित CONFIG_CEPH_LIB_USE_DNS_RESOLVER
अटल पूर्णांक ceph_dns_resolve_name(स्थिर अक्षर *name, माप_प्रकार namelen,
		काष्ठा ceph_entity_addr *addr, अक्षर delim, स्थिर अक्षर **ipend)
अणु
	स्थिर अक्षर *end, *delim_p;
	अक्षर *colon_p, *ip_addr = शून्य;
	पूर्णांक ip_len, ret;

	/*
	 * The end of the hostname occurs immediately preceding the delimiter or
	 * the port marker (':') where the delimiter takes precedence.
	 */
	delim_p = स_प्रथम(name, delim, namelen);
	colon_p = स_प्रथम(name, ':', namelen);

	अगर (delim_p && colon_p)
		end = delim_p < colon_p ? delim_p : colon_p;
	अन्यथा अगर (!delim_p && colon_p)
		end = colon_p;
	अन्यथा अणु
		end = delim_p;
		अगर (!end) /* हाल: hostname:/ */
			end = name + namelen;
	पूर्ण

	अगर (end <= name)
		वापस -EINVAL;

	/* करो dns_resolve upcall */
	ip_len = dns_query(current->nsproxy->net_ns,
			   शून्य, name, end - name, शून्य, &ip_addr, शून्य, false);
	अगर (ip_len > 0)
		ret = ceph_pton(ip_addr, ip_len, addr, -1, शून्य);
	अन्यथा
		ret = -ESRCH;

	kमुक्त(ip_addr);

	*ipend = end;

	pr_info("resolve '%.*s' (ret=%d): %s\n", (पूर्णांक)(end - name), name,
			ret, ret ? "failed" : ceph_pr_addr(addr));

	वापस ret;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक ceph_dns_resolve_name(स्थिर अक्षर *name, माप_प्रकार namelen,
		काष्ठा ceph_entity_addr *addr, अक्षर delim, स्थिर अक्षर **ipend)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

/*
 * Parse a server name (IP or hostname). If a valid IP address is not found
 * then try to extract a hostname to resolve using userspace DNS upcall.
 */
अटल पूर्णांक ceph_parse_server_name(स्थिर अक्षर *name, माप_प्रकार namelen,
		काष्ठा ceph_entity_addr *addr, अक्षर delim, स्थिर अक्षर **ipend)
अणु
	पूर्णांक ret;

	ret = ceph_pton(name, namelen, addr, delim, ipend);
	अगर (ret)
		ret = ceph_dns_resolve_name(name, namelen, addr, delim, ipend);

	वापस ret;
पूर्ण

/*
 * Parse an ip[:port] list पूर्णांकo an addr array.  Use the शेष
 * monitor port अगर a port isn't specअगरied.
 */
पूर्णांक ceph_parse_ips(स्थिर अक्षर *c, स्थिर अक्षर *end,
		   काष्ठा ceph_entity_addr *addr,
		   पूर्णांक max_count, पूर्णांक *count)
अणु
	पूर्णांक i, ret = -EINVAL;
	स्थिर अक्षर *p = c;

	करोut("parse_ips on '%.*s'\n", (पूर्णांक)(end-c), c);
	क्रम (i = 0; i < max_count; i++) अणु
		स्थिर अक्षर *ipend;
		पूर्णांक port;
		अक्षर delim = ',';

		अगर (*p == '[') अणु
			delim = ']';
			p++;
		पूर्ण

		ret = ceph_parse_server_name(p, end - p, &addr[i], delim, &ipend);
		अगर (ret)
			जाओ bad;
		ret = -EINVAL;

		p = ipend;

		अगर (delim == ']') अणु
			अगर (*p != ']') अणु
				करोut("missing matching ']'\n");
				जाओ bad;
			पूर्ण
			p++;
		पूर्ण

		/* port? */
		अगर (p < end && *p == ':') अणु
			port = 0;
			p++;
			जबतक (p < end && *p >= '0' && *p <= '9') अणु
				port = (port * 10) + (*p - '0');
				p++;
			पूर्ण
			अगर (port == 0)
				port = CEPH_MON_PORT;
			अन्यथा अगर (port > 65535)
				जाओ bad;
		पूर्ण अन्यथा अणु
			port = CEPH_MON_PORT;
		पूर्ण

		ceph_addr_set_port(&addr[i], port);
		/*
		 * We want the type to be set according to ms_mode
		 * option, but options are normally parsed after mon
		 * addresses.  Rather than complicating parsing, set
		 * to LEGACY and override in build_initial_monmap()
		 * क्रम mon addresses and ceph_messenger_init() क्रम
		 * ip option.
		 */
		addr[i].type = CEPH_ENTITY_ADDR_TYPE_LEGACY;
		addr[i].nonce = 0;

		करोut("parse_ips got %s\n", ceph_pr_addr(&addr[i]));

		अगर (p == end)
			अवरोध;
		अगर (*p != ',')
			जाओ bad;
		p++;
	पूर्ण

	अगर (p != end)
		जाओ bad;

	अगर (count)
		*count = i + 1;
	वापस 0;

bad:
	वापस ret;
पूर्ण

/*
 * Process message.  This happens in the worker thपढ़ो.  The callback should
 * be careful not to करो anything that रुकोs on other incoming messages or it
 * may deadlock.
 */
व्योम ceph_con_process_message(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_msg *msg = con->in_msg;

	BUG_ON(con->in_msg->con != con);
	con->in_msg = शून्य;

	/* अगर first message, set peer_name */
	अगर (con->peer_name.type == 0)
		con->peer_name = msg->hdr.src;

	con->in_seq++;
	mutex_unlock(&con->mutex);

	करोut("===== %p %llu from %s%lld %d=%s len %d+%d+%d (%u %u %u) =====\n",
	     msg, le64_to_cpu(msg->hdr.seq),
	     ENTITY_NAME(msg->hdr.src),
	     le16_to_cpu(msg->hdr.type),
	     ceph_msg_type_name(le16_to_cpu(msg->hdr.type)),
	     le32_to_cpu(msg->hdr.front_len),
	     le32_to_cpu(msg->hdr.middle_len),
	     le32_to_cpu(msg->hdr.data_len),
	     con->in_front_crc, con->in_middle_crc, con->in_data_crc);
	con->ops->dispatch(con, msg);

	mutex_lock(&con->mutex);
पूर्ण

/*
 * Atomically queue work on a connection after the specअगरied delay.
 * Bump @con reference to aव्योम races with connection tearकरोwn.
 * Returns 0 अगर work was queued, or an error code otherwise.
 */
अटल पूर्णांक queue_con_delay(काष्ठा ceph_connection *con, अचिन्हित दीर्घ delay)
अणु
	अगर (!con->ops->get(con)) अणु
		करोut("%s %p ref count 0\n", __func__, con);
		वापस -ENOENT;
	पूर्ण

	अगर (delay >= HZ)
		delay = round_jअगरfies_relative(delay);

	करोut("%s %p %lu\n", __func__, con, delay);
	अगर (!queue_delayed_work(ceph_msgr_wq, &con->work, delay)) अणु
		करोut("%s %p - already queued\n", __func__, con);
		con->ops->put(con);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम queue_con(काष्ठा ceph_connection *con)
अणु
	(व्योम) queue_con_delay(con, 0);
पूर्ण

अटल व्योम cancel_con(काष्ठा ceph_connection *con)
अणु
	अगर (cancel_delayed_work(&con->work)) अणु
		करोut("%s %p\n", __func__, con);
		con->ops->put(con);
	पूर्ण
पूर्ण

अटल bool con_sock_बंदd(काष्ठा ceph_connection *con)
अणु
	अगर (!ceph_con_flag_test_and_clear(con, CEPH_CON_F_SOCK_CLOSED))
		वापस false;

#घोषणा CASE(x)								\
	हाल CEPH_CON_S_ ## x:						\
		con->error_msg = "socket closed (con state " #x ")";	\
		अवरोध;

	चयन (con->state) अणु
	CASE(CLOSED);
	CASE(PREOPEN);
	CASE(V1_BANNER);
	CASE(V1_CONNECT_MSG);
	CASE(V2_BANNER_PREFIX);
	CASE(V2_BANNER_PAYLOAD);
	CASE(V2_HELLO);
	CASE(V2_AUTH);
	CASE(V2_AUTH_SIGNATURE);
	CASE(V2_SESSION_CONNECT);
	CASE(V2_SESSION_RECONNECT);
	CASE(OPEN);
	CASE(STANDBY);
	शेष:
		BUG();
	पूर्ण
#अघोषित CASE

	वापस true;
पूर्ण

अटल bool con_backoff(काष्ठा ceph_connection *con)
अणु
	पूर्णांक ret;

	अगर (!ceph_con_flag_test_and_clear(con, CEPH_CON_F_BACKOFF))
		वापस false;

	ret = queue_con_delay(con, con->delay);
	अगर (ret) अणु
		करोut("%s: con %p FAILED to back off %lu\n", __func__,
			con, con->delay);
		BUG_ON(ret == -ENOENT);
		ceph_con_flag_set(con, CEPH_CON_F_BACKOFF);
	पूर्ण

	वापस true;
पूर्ण

/* Finish fault handling; con->mutex must *not* be held here */

अटल व्योम con_fault_finish(काष्ठा ceph_connection *con)
अणु
	करोut("%s %p\n", __func__, con);

	/*
	 * in हाल we faulted due to authentication, invalidate our
	 * current tickets so that we can get new ones.
	 */
	अगर (con->v1.auth_retry) अणु
		करोut("auth_retry %d, invalidating\n", con->v1.auth_retry);
		अगर (con->ops->invalidate_authorizer)
			con->ops->invalidate_authorizer(con);
		con->v1.auth_retry = 0;
	पूर्ण

	अगर (con->ops->fault)
		con->ops->fault(con);
पूर्ण

/*
 * Do some work on a connection.  Drop a connection ref when we're करोne.
 */
अटल व्योम ceph_con_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ceph_connection *con = container_of(work, काष्ठा ceph_connection,
						   work.work);
	bool fault;

	mutex_lock(&con->mutex);
	जबतक (true) अणु
		पूर्णांक ret;

		अगर ((fault = con_sock_बंदd(con))) अणु
			करोut("%s: con %p SOCK_CLOSED\n", __func__, con);
			अवरोध;
		पूर्ण
		अगर (con_backoff(con)) अणु
			करोut("%s: con %p BACKOFF\n", __func__, con);
			अवरोध;
		पूर्ण
		अगर (con->state == CEPH_CON_S_STANDBY) अणु
			करोut("%s: con %p STANDBY\n", __func__, con);
			अवरोध;
		पूर्ण
		अगर (con->state == CEPH_CON_S_CLOSED) अणु
			करोut("%s: con %p CLOSED\n", __func__, con);
			BUG_ON(con->sock);
			अवरोध;
		पूर्ण
		अगर (con->state == CEPH_CON_S_PREOPEN) अणु
			करोut("%s: con %p PREOPEN\n", __func__, con);
			BUG_ON(con->sock);
		पूर्ण

		अगर (ceph_msgr2(from_msgr(con->msgr)))
			ret = ceph_con_v2_try_पढ़ो(con);
		अन्यथा
			ret = ceph_con_v1_try_पढ़ो(con);
		अगर (ret < 0) अणु
			अगर (ret == -EAGAIN)
				जारी;
			अगर (!con->error_msg)
				con->error_msg = "socket error on read";
			fault = true;
			अवरोध;
		पूर्ण

		अगर (ceph_msgr2(from_msgr(con->msgr)))
			ret = ceph_con_v2_try_ग_लिखो(con);
		अन्यथा
			ret = ceph_con_v1_try_ग_लिखो(con);
		अगर (ret < 0) अणु
			अगर (ret == -EAGAIN)
				जारी;
			अगर (!con->error_msg)
				con->error_msg = "socket error on write";
			fault = true;
		पूर्ण

		अवरोध;	/* If we make it to here, we're करोne */
	पूर्ण
	अगर (fault)
		con_fault(con);
	mutex_unlock(&con->mutex);

	अगर (fault)
		con_fault_finish(con);

	con->ops->put(con);
पूर्ण

/*
 * Generic error/fault handler.  A retry mechanism is used with
 * exponential backoff
 */
अटल व्योम con_fault(काष्ठा ceph_connection *con)
अणु
	करोut("fault %p state %d to peer %s\n",
	     con, con->state, ceph_pr_addr(&con->peer_addr));

	pr_warn("%s%lld %s %s\n", ENTITY_NAME(con->peer_name),
		ceph_pr_addr(&con->peer_addr), con->error_msg);
	con->error_msg = शून्य;

	WARN_ON(con->state == CEPH_CON_S_STANDBY ||
		con->state == CEPH_CON_S_CLOSED);

	ceph_con_reset_protocol(con);

	अगर (ceph_con_flag_test(con, CEPH_CON_F_LOSSYTX)) अणु
		करोut("fault on LOSSYTX channel, marking CLOSED\n");
		con->state = CEPH_CON_S_CLOSED;
		वापस;
	पूर्ण

	/* Requeue anything that hasn't been acked */
	list_splice_init(&con->out_sent, &con->out_queue);

	/* If there are no messages queued or keepalive pending, place
	 * the connection in a STANDBY state */
	अगर (list_empty(&con->out_queue) &&
	    !ceph_con_flag_test(con, CEPH_CON_F_KEEPALIVE_PENDING)) अणु
		करोut("fault %p setting STANDBY clearing WRITE_PENDING\n", con);
		ceph_con_flag_clear(con, CEPH_CON_F_WRITE_PENDING);
		con->state = CEPH_CON_S_STANDBY;
	पूर्ण अन्यथा अणु
		/* retry after a delay. */
		con->state = CEPH_CON_S_PREOPEN;
		अगर (!con->delay) अणु
			con->delay = BASE_DELAY_INTERVAL;
		पूर्ण अन्यथा अगर (con->delay < MAX_DELAY_INTERVAL) अणु
			con->delay *= 2;
			अगर (con->delay > MAX_DELAY_INTERVAL)
				con->delay = MAX_DELAY_INTERVAL;
		पूर्ण
		ceph_con_flag_set(con, CEPH_CON_F_BACKOFF);
		queue_con(con);
	पूर्ण
पूर्ण

व्योम ceph_messenger_reset_nonce(काष्ठा ceph_messenger *msgr)
अणु
	u32 nonce = le32_to_cpu(msgr->inst.addr.nonce) + 1000000;
	msgr->inst.addr.nonce = cpu_to_le32(nonce);
	ceph_encode_my_addr(msgr);
पूर्ण

/*
 * initialize a new messenger instance
 */
व्योम ceph_messenger_init(काष्ठा ceph_messenger *msgr,
			 काष्ठा ceph_entity_addr *myaddr)
अणु
	spin_lock_init(&msgr->global_seq_lock);

	अगर (myaddr) अणु
		स_नकल(&msgr->inst.addr.in_addr, &myaddr->in_addr,
		       माप(msgr->inst.addr.in_addr));
		ceph_addr_set_port(&msgr->inst.addr, 0);
	पूर्ण

	/*
	 * Since nautilus, clients are identअगरied using type ANY.
	 * For msgr1, ceph_encode_banner_addr() munges it to NONE.
	 */
	msgr->inst.addr.type = CEPH_ENTITY_ADDR_TYPE_ANY;

	/* generate a अक्रमom non-zero nonce */
	करो अणु
		get_अक्रमom_bytes(&msgr->inst.addr.nonce,
				 माप(msgr->inst.addr.nonce));
	पूर्ण जबतक (!msgr->inst.addr.nonce);
	ceph_encode_my_addr(msgr);

	atomic_set(&msgr->stopping, 0);
	ग_लिखो_pnet(&msgr->net, get_net(current->nsproxy->net_ns));

	करोut("%s %p\n", __func__, msgr);
पूर्ण

व्योम ceph_messenger_fini(काष्ठा ceph_messenger *msgr)
अणु
	put_net(पढ़ो_pnet(&msgr->net));
पूर्ण

अटल व्योम msg_con_set(काष्ठा ceph_msg *msg, काष्ठा ceph_connection *con)
अणु
	अगर (msg->con)
		msg->con->ops->put(msg->con);

	msg->con = con ? con->ops->get(con) : शून्य;
	BUG_ON(msg->con != con);
पूर्ण

अटल व्योम clear_standby(काष्ठा ceph_connection *con)
अणु
	/* come back from STANDBY? */
	अगर (con->state == CEPH_CON_S_STANDBY) अणु
		करोut("clear_standby %p and ++connect_seq\n", con);
		con->state = CEPH_CON_S_PREOPEN;
		con->v1.connect_seq++;
		WARN_ON(ceph_con_flag_test(con, CEPH_CON_F_WRITE_PENDING));
		WARN_ON(ceph_con_flag_test(con, CEPH_CON_F_KEEPALIVE_PENDING));
	पूर्ण
पूर्ण

/*
 * Queue up an outgoing message on the given connection.
 *
 * Consumes a ref on @msg.
 */
व्योम ceph_con_send(काष्ठा ceph_connection *con, काष्ठा ceph_msg *msg)
अणु
	/* set src+dst */
	msg->hdr.src = con->msgr->inst.name;
	BUG_ON(msg->front.iov_len != le32_to_cpu(msg->hdr.front_len));
	msg->needs_out_seq = true;

	mutex_lock(&con->mutex);

	अगर (con->state == CEPH_CON_S_CLOSED) अणु
		करोut("con_send %p closed, dropping %p\n", con, msg);
		ceph_msg_put(msg);
		mutex_unlock(&con->mutex);
		वापस;
	पूर्ण

	msg_con_set(msg, con);

	BUG_ON(!list_empty(&msg->list_head));
	list_add_tail(&msg->list_head, &con->out_queue);
	करोut("----- %p to %s%lld %d=%s len %d+%d+%d -----\n", msg,
	     ENTITY_NAME(con->peer_name), le16_to_cpu(msg->hdr.type),
	     ceph_msg_type_name(le16_to_cpu(msg->hdr.type)),
	     le32_to_cpu(msg->hdr.front_len),
	     le32_to_cpu(msg->hdr.middle_len),
	     le32_to_cpu(msg->hdr.data_len));

	clear_standby(con);
	mutex_unlock(&con->mutex);

	/* अगर there wasn't anything रुकोing to send beक्रमe, queue
	 * new work */
	अगर (!ceph_con_flag_test_and_set(con, CEPH_CON_F_WRITE_PENDING))
		queue_con(con);
पूर्ण
EXPORT_SYMBOL(ceph_con_send);

/*
 * Revoke a message that was previously queued क्रम send
 */
व्योम ceph_msg_revoke(काष्ठा ceph_msg *msg)
अणु
	काष्ठा ceph_connection *con = msg->con;

	अगर (!con) अणु
		करोut("%s msg %p null con\n", __func__, msg);
		वापस;		/* Message not in our possession */
	पूर्ण

	mutex_lock(&con->mutex);
	अगर (list_empty(&msg->list_head)) अणु
		WARN_ON(con->out_msg == msg);
		करोut("%s con %p msg %p not linked\n", __func__, con, msg);
		mutex_unlock(&con->mutex);
		वापस;
	पूर्ण

	करोut("%s con %p msg %p was linked\n", __func__, con, msg);
	msg->hdr.seq = 0;
	ceph_msg_हटाओ(msg);

	अगर (con->out_msg == msg) अणु
		WARN_ON(con->state != CEPH_CON_S_OPEN);
		करोut("%s con %p msg %p was sending\n", __func__, con, msg);
		अगर (ceph_msgr2(from_msgr(con->msgr)))
			ceph_con_v2_revoke(con);
		अन्यथा
			ceph_con_v1_revoke(con);
		ceph_msg_put(con->out_msg);
		con->out_msg = शून्य;
	पूर्ण अन्यथा अणु
		करोut("%s con %p msg %p not current, out_msg %p\n", __func__,
		     con, msg, con->out_msg);
	पूर्ण
	mutex_unlock(&con->mutex);
पूर्ण

/*
 * Revoke a message that we may be पढ़ोing data पूर्णांकo
 */
व्योम ceph_msg_revoke_incoming(काष्ठा ceph_msg *msg)
अणु
	काष्ठा ceph_connection *con = msg->con;

	अगर (!con) अणु
		करोut("%s msg %p null con\n", __func__, msg);
		वापस;		/* Message not in our possession */
	पूर्ण

	mutex_lock(&con->mutex);
	अगर (con->in_msg == msg) अणु
		WARN_ON(con->state != CEPH_CON_S_OPEN);
		करोut("%s con %p msg %p was recving\n", __func__, con, msg);
		अगर (ceph_msgr2(from_msgr(con->msgr)))
			ceph_con_v2_revoke_incoming(con);
		अन्यथा
			ceph_con_v1_revoke_incoming(con);
		ceph_msg_put(con->in_msg);
		con->in_msg = शून्य;
	पूर्ण अन्यथा अणु
		करोut("%s con %p msg %p not current, in_msg %p\n", __func__,
		     con, msg, con->in_msg);
	पूर्ण
	mutex_unlock(&con->mutex);
पूर्ण

/*
 * Queue a keepalive byte to ensure the tcp connection is alive.
 */
व्योम ceph_con_keepalive(काष्ठा ceph_connection *con)
अणु
	करोut("con_keepalive %p\n", con);
	mutex_lock(&con->mutex);
	clear_standby(con);
	ceph_con_flag_set(con, CEPH_CON_F_KEEPALIVE_PENDING);
	mutex_unlock(&con->mutex);

	अगर (!ceph_con_flag_test_and_set(con, CEPH_CON_F_WRITE_PENDING))
		queue_con(con);
पूर्ण
EXPORT_SYMBOL(ceph_con_keepalive);

bool ceph_con_keepalive_expired(काष्ठा ceph_connection *con,
			       अचिन्हित दीर्घ पूर्णांकerval)
अणु
	अगर (पूर्णांकerval > 0 &&
	    (con->peer_features & CEPH_FEATURE_MSGR_KEEPALIVE2)) अणु
		काष्ठा बारpec64 now;
		काष्ठा बारpec64 ts;
		kसमय_get_real_ts64(&now);
		jअगरfies_to_बारpec64(पूर्णांकerval, &ts);
		ts = बारpec64_add(con->last_keepalive_ack, ts);
		वापस बारpec64_compare(&now, &ts) >= 0;
	पूर्ण
	वापस false;
पूर्ण

अटल काष्ठा ceph_msg_data *ceph_msg_data_add(काष्ठा ceph_msg *msg)
अणु
	BUG_ON(msg->num_data_items >= msg->max_data_items);
	वापस &msg->data[msg->num_data_items++];
पूर्ण

अटल व्योम ceph_msg_data_destroy(काष्ठा ceph_msg_data *data)
अणु
	अगर (data->type == CEPH_MSG_DATA_PAGES && data->own_pages) अणु
		पूर्णांक num_pages = calc_pages_क्रम(data->alignment, data->length);
		ceph_release_page_vector(data->pages, num_pages);
	पूर्ण अन्यथा अगर (data->type == CEPH_MSG_DATA_PAGELIST) अणु
		ceph_pagelist_release(data->pagelist);
	पूर्ण
पूर्ण

व्योम ceph_msg_data_add_pages(काष्ठा ceph_msg *msg, काष्ठा page **pages,
			     माप_प्रकार length, माप_प्रकार alignment, bool own_pages)
अणु
	काष्ठा ceph_msg_data *data;

	BUG_ON(!pages);
	BUG_ON(!length);

	data = ceph_msg_data_add(msg);
	data->type = CEPH_MSG_DATA_PAGES;
	data->pages = pages;
	data->length = length;
	data->alignment = alignment & ~PAGE_MASK;
	data->own_pages = own_pages;

	msg->data_length += length;
पूर्ण
EXPORT_SYMBOL(ceph_msg_data_add_pages);

व्योम ceph_msg_data_add_pagelist(काष्ठा ceph_msg *msg,
				काष्ठा ceph_pagelist *pagelist)
अणु
	काष्ठा ceph_msg_data *data;

	BUG_ON(!pagelist);
	BUG_ON(!pagelist->length);

	data = ceph_msg_data_add(msg);
	data->type = CEPH_MSG_DATA_PAGELIST;
	refcount_inc(&pagelist->refcnt);
	data->pagelist = pagelist;

	msg->data_length += pagelist->length;
पूर्ण
EXPORT_SYMBOL(ceph_msg_data_add_pagelist);

#अगर_घोषित	CONFIG_BLOCK
व्योम ceph_msg_data_add_bio(काष्ठा ceph_msg *msg, काष्ठा ceph_bio_iter *bio_pos,
			   u32 length)
अणु
	काष्ठा ceph_msg_data *data;

	data = ceph_msg_data_add(msg);
	data->type = CEPH_MSG_DATA_BIO;
	data->bio_pos = *bio_pos;
	data->bio_length = length;

	msg->data_length += length;
पूर्ण
EXPORT_SYMBOL(ceph_msg_data_add_bio);
#पूर्ण_अगर	/* CONFIG_BLOCK */

व्योम ceph_msg_data_add_bvecs(काष्ठा ceph_msg *msg,
			     काष्ठा ceph_bvec_iter *bvec_pos)
अणु
	काष्ठा ceph_msg_data *data;

	data = ceph_msg_data_add(msg);
	data->type = CEPH_MSG_DATA_BVECS;
	data->bvec_pos = *bvec_pos;

	msg->data_length += bvec_pos->iter.bi_size;
पूर्ण
EXPORT_SYMBOL(ceph_msg_data_add_bvecs);

/*
 * स्थिरruct a new message with given type, size
 * the new msg has a ref count of 1.
 */
काष्ठा ceph_msg *ceph_msg_new2(पूर्णांक type, पूर्णांक front_len, पूर्णांक max_data_items,
			       gfp_t flags, bool can_fail)
अणु
	काष्ठा ceph_msg *m;

	m = kmem_cache_zalloc(ceph_msg_cache, flags);
	अगर (m == शून्य)
		जाओ out;

	m->hdr.type = cpu_to_le16(type);
	m->hdr.priority = cpu_to_le16(CEPH_MSG_PRIO_DEFAULT);
	m->hdr.front_len = cpu_to_le32(front_len);

	INIT_LIST_HEAD(&m->list_head);
	kref_init(&m->kref);

	/* front */
	अगर (front_len) अणु
		m->front.iov_base = ceph_kvदो_स्मृति(front_len, flags);
		अगर (m->front.iov_base == शून्य) अणु
			करोut("ceph_msg_new can't allocate %d bytes\n",
			     front_len);
			जाओ out2;
		पूर्ण
	पूर्ण अन्यथा अणु
		m->front.iov_base = शून्य;
	पूर्ण
	m->front_alloc_len = m->front.iov_len = front_len;

	अगर (max_data_items) अणु
		m->data = kदो_स्मृति_array(max_data_items, माप(*m->data),
					flags);
		अगर (!m->data)
			जाओ out2;

		m->max_data_items = max_data_items;
	पूर्ण

	करोut("ceph_msg_new %p front %d\n", m, front_len);
	वापस m;

out2:
	ceph_msg_put(m);
out:
	अगर (!can_fail) अणु
		pr_err("msg_new can't create type %d front %d\n", type,
		       front_len);
		WARN_ON(1);
	पूर्ण अन्यथा अणु
		करोut("msg_new can't create type %d front %d\n", type,
		     front_len);
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(ceph_msg_new2);

काष्ठा ceph_msg *ceph_msg_new(पूर्णांक type, पूर्णांक front_len, gfp_t flags,
			      bool can_fail)
अणु
	वापस ceph_msg_new2(type, front_len, 0, flags, can_fail);
पूर्ण
EXPORT_SYMBOL(ceph_msg_new);

/*
 * Allocate "middle" portion of a message, अगर it is needed and wasn't
 * allocated by alloc_msg.  This allows us to पढ़ो a small fixed-size
 * per-type header in the front and then gracefully fail (i.e.,
 * propagate the error to the caller based on info in the front) when
 * the middle is too large.
 */
अटल पूर्णांक ceph_alloc_middle(काष्ठा ceph_connection *con, काष्ठा ceph_msg *msg)
अणु
	पूर्णांक type = le16_to_cpu(msg->hdr.type);
	पूर्णांक middle_len = le32_to_cpu(msg->hdr.middle_len);

	करोut("alloc_middle %p type %d %s middle_len %d\n", msg, type,
	     ceph_msg_type_name(type), middle_len);
	BUG_ON(!middle_len);
	BUG_ON(msg->middle);

	msg->middle = ceph_buffer_new(middle_len, GFP_NOFS);
	अगर (!msg->middle)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/*
 * Allocate a message क्रम receiving an incoming message on a
 * connection, and save the result in con->in_msg.  Uses the
 * connection's निजी alloc_msg op अगर available.
 *
 * Returns 0 on success, or a negative error code.
 *
 * On success, अगर we set *skip = 1:
 *  - the next message should be skipped and ignored.
 *  - con->in_msg == शून्य
 * or अगर we set *skip = 0:
 *  - con->in_msg is non-null.
 * On error (ENOMEM, EAGAIN, ...),
 *  - con->in_msg == शून्य
 */
पूर्णांक ceph_con_in_msg_alloc(काष्ठा ceph_connection *con,
			  काष्ठा ceph_msg_header *hdr, पूर्णांक *skip)
अणु
	पूर्णांक middle_len = le32_to_cpu(hdr->middle_len);
	काष्ठा ceph_msg *msg;
	पूर्णांक ret = 0;

	BUG_ON(con->in_msg != शून्य);
	BUG_ON(!con->ops->alloc_msg);

	mutex_unlock(&con->mutex);
	msg = con->ops->alloc_msg(con, hdr, skip);
	mutex_lock(&con->mutex);
	अगर (con->state != CEPH_CON_S_OPEN) अणु
		अगर (msg)
			ceph_msg_put(msg);
		वापस -EAGAIN;
	पूर्ण
	अगर (msg) अणु
		BUG_ON(*skip);
		msg_con_set(msg, con);
		con->in_msg = msg;
	पूर्ण अन्यथा अणु
		/*
		 * Null message poपूर्णांकer means either we should skip
		 * this message or we couldn't allocate memory.  The
		 * क्रमmer is not an error.
		 */
		अगर (*skip)
			वापस 0;

		con->error_msg = "error allocating memory for incoming message";
		वापस -ENOMEM;
	पूर्ण
	स_नकल(&con->in_msg->hdr, hdr, माप(*hdr));

	अगर (middle_len && !con->in_msg->middle) अणु
		ret = ceph_alloc_middle(con, con->in_msg);
		अगर (ret < 0) अणु
			ceph_msg_put(con->in_msg);
			con->in_msg = शून्य;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

व्योम ceph_con_get_out_msg(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_msg *msg;

	BUG_ON(list_empty(&con->out_queue));
	msg = list_first_entry(&con->out_queue, काष्ठा ceph_msg, list_head);
	WARN_ON(msg->con != con);

	/*
	 * Put the message on "sent" list using a ref from ceph_con_send().
	 * It is put when the message is acked or revoked.
	 */
	list_move_tail(&msg->list_head, &con->out_sent);

	/*
	 * Only assign outgoing seq # अगर we haven't sent this message
	 * yet.  If it is requeued, resend with it's original seq.
	 */
	अगर (msg->needs_out_seq) अणु
		msg->hdr.seq = cpu_to_le64(++con->out_seq);
		msg->needs_out_seq = false;

		अगर (con->ops->reencode_message)
			con->ops->reencode_message(msg);
	पूर्ण

	/*
	 * Get a ref क्रम out_msg.  It is put when we are करोne sending the
	 * message or in हाल of a fault.
	 */
	WARN_ON(con->out_msg);
	con->out_msg = ceph_msg_get(msg);
पूर्ण

/*
 * Free a generically kदो_स्मृति'd message.
 */
अटल व्योम ceph_msg_मुक्त(काष्ठा ceph_msg *m)
अणु
	करोut("%s %p\n", __func__, m);
	kvमुक्त(m->front.iov_base);
	kमुक्त(m->data);
	kmem_cache_मुक्त(ceph_msg_cache, m);
पूर्ण

अटल व्योम ceph_msg_release(काष्ठा kref *kref)
अणु
	काष्ठा ceph_msg *m = container_of(kref, काष्ठा ceph_msg, kref);
	पूर्णांक i;

	करोut("%s %p\n", __func__, m);
	WARN_ON(!list_empty(&m->list_head));

	msg_con_set(m, शून्य);

	/* drop middle, data, अगर any */
	अगर (m->middle) अणु
		ceph_buffer_put(m->middle);
		m->middle = शून्य;
	पूर्ण

	क्रम (i = 0; i < m->num_data_items; i++)
		ceph_msg_data_destroy(&m->data[i]);

	अगर (m->pool)
		ceph_msgpool_put(m->pool, m);
	अन्यथा
		ceph_msg_मुक्त(m);
पूर्ण

काष्ठा ceph_msg *ceph_msg_get(काष्ठा ceph_msg *msg)
अणु
	करोut("%s %p (was %d)\n", __func__, msg,
	     kref_पढ़ो(&msg->kref));
	kref_get(&msg->kref);
	वापस msg;
पूर्ण
EXPORT_SYMBOL(ceph_msg_get);

व्योम ceph_msg_put(काष्ठा ceph_msg *msg)
अणु
	करोut("%s %p (was %d)\n", __func__, msg,
	     kref_पढ़ो(&msg->kref));
	kref_put(&msg->kref, ceph_msg_release);
पूर्ण
EXPORT_SYMBOL(ceph_msg_put);

व्योम ceph_msg_dump(काष्ठा ceph_msg *msg)
अणु
	pr_debug("msg_dump %p (front_alloc_len %d length %zd)\n", msg,
		 msg->front_alloc_len, msg->data_length);
	prपूर्णांक_hex_dump(KERN_DEBUG, "header: ",
		       DUMP_PREFIX_OFFSET, 16, 1,
		       &msg->hdr, माप(msg->hdr), true);
	prपूर्णांक_hex_dump(KERN_DEBUG, " front: ",
		       DUMP_PREFIX_OFFSET, 16, 1,
		       msg->front.iov_base, msg->front.iov_len, true);
	अगर (msg->middle)
		prपूर्णांक_hex_dump(KERN_DEBUG, "middle: ",
			       DUMP_PREFIX_OFFSET, 16, 1,
			       msg->middle->vec.iov_base,
			       msg->middle->vec.iov_len, true);
	prपूर्णांक_hex_dump(KERN_DEBUG, "footer: ",
		       DUMP_PREFIX_OFFSET, 16, 1,
		       &msg->footer, माप(msg->footer), true);
पूर्ण
EXPORT_SYMBOL(ceph_msg_dump);
