<शैली गुरु>
/*
 * Copyright (c) 2006, 2018 Oracle and/or its affiliates. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/in.h>
#समावेश <net/tcp.h>

#समावेश "rds.h"
#समावेश "tcp.h"

व्योम rds_tcp_keepalive(काष्ठा socket *sock)
अणु
	/* values below based on xs_udp_शेष_समयout */
	पूर्णांक keepidle = 5; /* send a probe 'keepidle' secs after last data */
	पूर्णांक keepcnt = 5; /* number of unack'ed probes beक्रमe declaring dead */

	sock_set_keepalive(sock->sk);
	tcp_sock_set_keepcnt(sock->sk, keepcnt);
	tcp_sock_set_keepidle(sock->sk, keepidle);
	/* KEEPINTVL is the पूर्णांकerval between successive probes. We follow
	 * the model in xs_tcp_finish_connecting() and re-use keepidle.
	 */
	tcp_sock_set_keepपूर्णांकvl(sock->sk, keepidle);
पूर्ण

/* rds_tcp_accept_one_path(): अगर accepting on cp_index > 0, make sure the
 * client's ipaddr < server's ipaddr. Otherwise, बंद the accepted
 * socket and क्रमce a reconneect from smaller -> larger ip addr. The reason
 * we special हाल cp_index 0 is to allow the rds probe ping itself to itself
 * get through efficiently.
 * Since reconnects are only initiated from the node with the numerically
 * smaller ip address, we recycle conns in RDS_CONN_ERROR on the passive side
 * by moving them to CONNECTING in this function.
 */
अटल
काष्ठा rds_tcp_connection *rds_tcp_accept_one_path(काष्ठा rds_connection *conn)
अणु
	पूर्णांक i;
	पूर्णांक npaths = max_t(पूर्णांक, 1, conn->c_npaths);

	/* क्रम mprds, all paths MUST be initiated by the peer
	 * with the smaller address.
	 */
	अगर (rds_addr_cmp(&conn->c_faddr, &conn->c_laddr) >= 0) अणु
		/* Make sure we initiate at least one path अगर this
		 * has not alपढ़ोy been करोne; rds_start_mprds() will
		 * take care of additional paths, अगर necessary.
		 */
		अगर (npaths == 1)
			rds_conn_path_connect_अगर_करोwn(&conn->c_path[0]);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < npaths; i++) अणु
		काष्ठा rds_conn_path *cp = &conn->c_path[i];

		अगर (rds_conn_path_transition(cp, RDS_CONN_DOWN,
					     RDS_CONN_CONNECTING) ||
		    rds_conn_path_transition(cp, RDS_CONN_ERROR,
					     RDS_CONN_CONNECTING)) अणु
			वापस cp->cp_transport_data;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक rds_tcp_accept_one(काष्ठा socket *sock)
अणु
	काष्ठा socket *new_sock = शून्य;
	काष्ठा rds_connection *conn;
	पूर्णांक ret;
	काष्ठा inet_sock *inet;
	काष्ठा rds_tcp_connection *rs_tcp = शून्य;
	पूर्णांक conn_state;
	काष्ठा rds_conn_path *cp;
	काष्ठा in6_addr *my_addr, *peer_addr;
#अगर !IS_ENABLED(CONFIG_IPV6)
	काष्ठा in6_addr saddr, daddr;
#पूर्ण_अगर
	पूर्णांक dev_अगर = 0;

	अगर (!sock) /* module unload or netns delete in progress */
		वापस -ENETUNREACH;

	ret = sock_create_lite(sock->sk->sk_family,
			       sock->sk->sk_type, sock->sk->sk_protocol,
			       &new_sock);
	अगर (ret)
		जाओ out;

	ret = sock->ops->accept(sock, new_sock, O_NONBLOCK, true);
	अगर (ret < 0)
		जाओ out;

	/* sock_create_lite() करोes not get a hold on the owner module so we
	 * need to करो it here.  Note that sock_release() uses sock->ops to
	 * determine अगर it needs to decrement the reference count.  So set
	 * sock->ops after calling accept() in हाल that fails.  And there's
	 * no need to करो try_module_get() as the listener should have a hold
	 * alपढ़ोy.
	 */
	new_sock->ops = sock->ops;
	__module_get(new_sock->ops->owner);

	rds_tcp_keepalive(new_sock);
	rds_tcp_tune(new_sock);

	inet = inet_sk(new_sock->sk);

#अगर IS_ENABLED(CONFIG_IPV6)
	my_addr = &new_sock->sk->sk_v6_rcv_saddr;
	peer_addr = &new_sock->sk->sk_v6_daddr;
#अन्यथा
	ipv6_addr_set_v4mapped(inet->inet_saddr, &saddr);
	ipv6_addr_set_v4mapped(inet->inet_daddr, &daddr);
	my_addr = &saddr;
	peer_addr = &daddr;
#पूर्ण_अगर
	rdsdebug("accepted family %d tcp %pI6c:%u -> %pI6c:%u\n",
		 sock->sk->sk_family,
		 my_addr, ntohs(inet->inet_sport),
		 peer_addr, ntohs(inet->inet_dport));

#अगर IS_ENABLED(CONFIG_IPV6)
	/* sk_bound_dev_अगर is not set अगर the peer address is not link local
	 * address.  In this हाल, it happens that mcast_oअगर is set.  So
	 * just use it.
	 */
	अगर ((ipv6_addr_type(my_addr) & IPV6_ADDR_LINKLOCAL) &&
	    !(ipv6_addr_type(peer_addr) & IPV6_ADDR_LINKLOCAL)) अणु
		काष्ठा ipv6_pinfo *inet6;

		inet6 = inet6_sk(new_sock->sk);
		dev_अगर = inet6->mcast_oअगर;
	पूर्ण अन्यथा अणु
		dev_अगर = new_sock->sk->sk_bound_dev_अगर;
	पूर्ण
#पूर्ण_अगर

	अगर (!rds_tcp_laddr_check(sock_net(sock->sk), peer_addr, dev_अगर)) अणु
		/* local address connection is only allowed via loopback */
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	conn = rds_conn_create(sock_net(sock->sk),
			       my_addr, peer_addr,
			       &rds_tcp_transport, 0, GFP_KERNEL, dev_अगर);

	अगर (IS_ERR(conn)) अणु
		ret = PTR_ERR(conn);
		जाओ out;
	पूर्ण
	/* An incoming SYN request came in, and TCP just accepted it.
	 *
	 * If the client reboots, this conn will need to be cleaned up.
	 * rds_tcp_state_change() will करो that cleanup
	 */
	rs_tcp = rds_tcp_accept_one_path(conn);
	अगर (!rs_tcp)
		जाओ rst_nsk;
	mutex_lock(&rs_tcp->t_conn_path_lock);
	cp = rs_tcp->t_cpath;
	conn_state = rds_conn_path_state(cp);
	WARN_ON(conn_state == RDS_CONN_UP);
	अगर (conn_state != RDS_CONN_CONNECTING && conn_state != RDS_CONN_ERROR)
		जाओ rst_nsk;
	अगर (rs_tcp->t_sock) अणु
		/* Duelling SYN has been handled in rds_tcp_accept_one() */
		rds_tcp_reset_callbacks(new_sock, cp);
		/* rds_connect_path_complete() marks RDS_CONN_UP */
		rds_connect_path_complete(cp, RDS_CONN_RESETTING);
	पूर्ण अन्यथा अणु
		rds_tcp_set_callbacks(new_sock, cp);
		rds_connect_path_complete(cp, RDS_CONN_CONNECTING);
	पूर्ण
	new_sock = शून्य;
	ret = 0;
	अगर (conn->c_npaths == 0)
		rds_send_ping(cp->cp_conn, cp->cp_index);
	जाओ out;
rst_nsk:
	/* reset the newly वापसed accept sock and bail.
	 * It is safe to set linger on new_sock because the RDS connection
	 * has not been brought up on new_sock, so no RDS-level data could
	 * be pending on it. By setting linger, we achieve the side-effect
	 * of aव्योमing TIME_WAIT state on new_sock.
	 */
	sock_no_linger(new_sock->sk);
	kernel_sock_shutकरोwn(new_sock, SHUT_RDWR);
	ret = 0;
out:
	अगर (rs_tcp)
		mutex_unlock(&rs_tcp->t_conn_path_lock);
	अगर (new_sock)
		sock_release(new_sock);
	वापस ret;
पूर्ण

व्योम rds_tcp_listen_data_पढ़ोy(काष्ठा sock *sk)
अणु
	व्योम (*पढ़ोy)(काष्ठा sock *sk);

	rdsdebug("listen data ready sk %p\n", sk);

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	पढ़ोy = sk->sk_user_data;
	अगर (!पढ़ोy) अणु /* check क्रम tearकरोwn race */
		पढ़ोy = sk->sk_data_पढ़ोy;
		जाओ out;
	पूर्ण

	/*
	 * ->sk_data_पढ़ोy is also called क्रम a newly established child socket
	 * beक्रमe it has been accepted and the accepter has set up their
	 * data_पढ़ोy.. we only want to queue listen work क्रम our listening
	 * socket
	 *
	 * (*पढ़ोy)() may be null अगर we are racing with netns delete, and
	 * the listen socket is being torn करोwn.
	 */
	अगर (sk->sk_state == TCP_LISTEN)
		rds_tcp_accept_work(sk);
	अन्यथा
		पढ़ोy = rds_tcp_listen_sock_def_पढ़ोable(sock_net(sk));

out:
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
	अगर (पढ़ोy)
		पढ़ोy(sk);
पूर्ण

काष्ठा socket *rds_tcp_listen_init(काष्ठा net *net, bool isv6)
अणु
	काष्ठा socket *sock = शून्य;
	काष्ठा sockaddr_storage ss;
	काष्ठा sockaddr_in6 *sin6;
	काष्ठा sockaddr_in *sin;
	पूर्णांक addr_len;
	पूर्णांक ret;

	ret = sock_create_kern(net, isv6 ? PF_INET6 : PF_INET, SOCK_STREAM,
			       IPPROTO_TCP, &sock);
	अगर (ret < 0) अणु
		rdsdebug("could not create %s listener socket: %d\n",
			 isv6 ? "IPv6" : "IPv4", ret);
		जाओ out;
	पूर्ण

	sock->sk->sk_reuse = SK_CAN_REUSE;
	tcp_sock_set_nodelay(sock->sk);

	ग_लिखो_lock_bh(&sock->sk->sk_callback_lock);
	sock->sk->sk_user_data = sock->sk->sk_data_पढ़ोy;
	sock->sk->sk_data_पढ़ोy = rds_tcp_listen_data_पढ़ोy;
	ग_लिखो_unlock_bh(&sock->sk->sk_callback_lock);

	अगर (isv6) अणु
		sin6 = (काष्ठा sockaddr_in6 *)&ss;
		sin6->sin6_family = PF_INET6;
		sin6->sin6_addr = in6addr_any;
		sin6->sin6_port = (__क्रमce u16)htons(RDS_TCP_PORT);
		sin6->sin6_scope_id = 0;
		sin6->sin6_flowinfo = 0;
		addr_len = माप(*sin6);
	पूर्ण अन्यथा अणु
		sin = (काष्ठा sockaddr_in *)&ss;
		sin->sin_family = PF_INET;
		sin->sin_addr.s_addr = INADDR_ANY;
		sin->sin_port = (__क्रमce u16)htons(RDS_TCP_PORT);
		addr_len = माप(*sin);
	पूर्ण

	ret = sock->ops->bind(sock, (काष्ठा sockaddr *)&ss, addr_len);
	अगर (ret < 0) अणु
		rdsdebug("could not bind %s listener socket: %d\n",
			 isv6 ? "IPv6" : "IPv4", ret);
		जाओ out;
	पूर्ण

	ret = sock->ops->listen(sock, 64);
	अगर (ret < 0)
		जाओ out;

	वापस sock;
out:
	अगर (sock)
		sock_release(sock);
	वापस शून्य;
पूर्ण

व्योम rds_tcp_listen_stop(काष्ठा socket *sock, काष्ठा work_काष्ठा *acceptor)
अणु
	काष्ठा sock *sk;

	अगर (!sock)
		वापस;

	sk = sock->sk;

	/* serialize with and prevent further callbacks */
	lock_sock(sk);
	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	अगर (sk->sk_user_data) अणु
		sk->sk_data_पढ़ोy = sk->sk_user_data;
		sk->sk_user_data = शून्य;
	पूर्ण
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
	release_sock(sk);

	/* रुको क्रम accepts to stop and बंद the socket */
	flush_workqueue(rds_wq);
	flush_work(acceptor);
	sock_release(sock);
पूर्ण
