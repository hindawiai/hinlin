<शैली गुरु>
/*
 * Copyright (c) 2006, 2017 Oracle and/or its affiliates. All rights reserved.
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
#समावेश <linux/in.h>
#समावेश <net/tcp.h>

#समावेश "rds.h"
#समावेश "tcp.h"

व्योम rds_tcp_state_change(काष्ठा sock *sk)
अणु
	व्योम (*state_change)(काष्ठा sock *sk);
	काष्ठा rds_conn_path *cp;
	काष्ठा rds_tcp_connection *tc;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	cp = sk->sk_user_data;
	अगर (!cp) अणु
		state_change = sk->sk_state_change;
		जाओ out;
	पूर्ण
	tc = cp->cp_transport_data;
	state_change = tc->t_orig_state_change;

	rdsdebug("sock %p state_change to %d\n", tc->t_sock, sk->sk_state);

	चयन (sk->sk_state) अणु
	/* ignore connecting sockets as they make progress */
	हाल TCP_SYN_SENT:
	हाल TCP_SYN_RECV:
		अवरोध;
	हाल TCP_ESTABLISHED:
		/* Force the peer to reconnect so that we have the
		 * TCP ports going from <smaller-ip>.<transient> to
		 * <larger-ip>.<RDS_TCP_PORT>. We aव्योम marking the
		 * RDS connection as RDS_CONN_UP until the reconnect,
		 * to aव्योम RDS datagram loss.
		 */
		अगर (rds_addr_cmp(&cp->cp_conn->c_laddr,
				 &cp->cp_conn->c_faddr) >= 0 &&
		    rds_conn_path_transition(cp, RDS_CONN_CONNECTING,
					     RDS_CONN_ERROR)) अणु
			rds_conn_path_drop(cp, false);
		पूर्ण अन्यथा अणु
			rds_connect_path_complete(cp, RDS_CONN_CONNECTING);
		पूर्ण
		अवरोध;
	हाल TCP_CLOSE_WAIT:
	हाल TCP_CLOSE:
		rds_conn_path_drop(cp, false);
	शेष:
		अवरोध;
	पूर्ण
out:
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
	state_change(sk);
पूर्ण

पूर्णांक rds_tcp_conn_path_connect(काष्ठा rds_conn_path *cp)
अणु
	काष्ठा socket *sock = शून्य;
	काष्ठा sockaddr_in6 sin6;
	काष्ठा sockaddr_in sin;
	काष्ठा sockaddr *addr;
	पूर्णांक addrlen;
	bool isv6;
	पूर्णांक ret;
	काष्ठा rds_connection *conn = cp->cp_conn;
	काष्ठा rds_tcp_connection *tc = cp->cp_transport_data;

	/* क्रम multipath rds,we only trigger the connection after
	 * the handshake probe has determined the number of paths.
	 */
	अगर (cp->cp_index > 0 && cp->cp_conn->c_npaths < 2)
		वापस -EAGAIN;

	mutex_lock(&tc->t_conn_path_lock);

	अगर (rds_conn_path_up(cp)) अणु
		mutex_unlock(&tc->t_conn_path_lock);
		वापस 0;
	पूर्ण
	अगर (ipv6_addr_v4mapped(&conn->c_laddr)) अणु
		ret = sock_create_kern(rds_conn_net(conn), PF_INET,
				       SOCK_STREAM, IPPROTO_TCP, &sock);
		isv6 = false;
	पूर्ण अन्यथा अणु
		ret = sock_create_kern(rds_conn_net(conn), PF_INET6,
				       SOCK_STREAM, IPPROTO_TCP, &sock);
		isv6 = true;
	पूर्ण

	अगर (ret < 0)
		जाओ out;

	rds_tcp_tune(sock);

	अगर (isv6) अणु
		sin6.sin6_family = AF_INET6;
		sin6.sin6_addr = conn->c_laddr;
		sin6.sin6_port = 0;
		sin6.sin6_flowinfo = 0;
		sin6.sin6_scope_id = conn->c_dev_अगर;
		addr = (काष्ठा sockaddr *)&sin6;
		addrlen = माप(sin6);
	पूर्ण अन्यथा अणु
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = conn->c_laddr.s6_addr32[3];
		sin.sin_port = 0;
		addr = (काष्ठा sockaddr *)&sin;
		addrlen = माप(sin);
	पूर्ण

	ret = sock->ops->bind(sock, addr, addrlen);
	अगर (ret) अणु
		rdsdebug("bind failed with %d at address %pI6c\n",
			 ret, &conn->c_laddr);
		जाओ out;
	पूर्ण

	अगर (isv6) अणु
		sin6.sin6_family = AF_INET6;
		sin6.sin6_addr = conn->c_faddr;
		sin6.sin6_port = htons(RDS_TCP_PORT);
		sin6.sin6_flowinfo = 0;
		sin6.sin6_scope_id = conn->c_dev_अगर;
		addr = (काष्ठा sockaddr *)&sin6;
		addrlen = माप(sin6);
	पूर्ण अन्यथा अणु
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = conn->c_faddr.s6_addr32[3];
		sin.sin_port = htons(RDS_TCP_PORT);
		addr = (काष्ठा sockaddr *)&sin;
		addrlen = माप(sin);
	पूर्ण

	/*
	 * once we call connect() we can start getting callbacks and they
	 * own the socket
	 */
	rds_tcp_set_callbacks(sock, cp);
	ret = sock->ops->connect(sock, addr, addrlen, O_NONBLOCK);

	rdsdebug("connect to address %pI6c returned %d\n", &conn->c_faddr, ret);
	अगर (ret == -EINPROGRESS)
		ret = 0;
	अगर (ret == 0) अणु
		rds_tcp_keepalive(sock);
		sock = शून्य;
	पूर्ण अन्यथा अणु
		rds_tcp_restore_callbacks(sock, cp->cp_transport_data);
	पूर्ण

out:
	mutex_unlock(&tc->t_conn_path_lock);
	अगर (sock)
		sock_release(sock);
	वापस ret;
पूर्ण

/*
 * Beक्रमe समाप्तing the tcp socket this needs to serialize with callbacks.  The
 * caller has alपढ़ोy grabbed the sending sem so we're serialized with other
 * senders.
 *
 * TCP calls the callbacks with the sock lock so we hold it जबतक we reset the
 * callbacks to those set by TCP.  Our callbacks won't execute again once we
 * hold the sock lock.
 */
व्योम rds_tcp_conn_path_shutकरोwn(काष्ठा rds_conn_path *cp)
अणु
	काष्ठा rds_tcp_connection *tc = cp->cp_transport_data;
	काष्ठा socket *sock = tc->t_sock;

	rdsdebug("shutting down conn %p tc %p sock %p\n",
		 cp->cp_conn, tc, sock);

	अगर (sock) अणु
		अगर (rds_destroy_pending(cp->cp_conn))
			sock_no_linger(sock->sk);
		sock->ops->shutकरोwn(sock, RCV_SHUTDOWN | SEND_SHUTDOWN);
		lock_sock(sock->sk);
		rds_tcp_restore_callbacks(sock, tc); /* tc->tc_sock = शून्य */

		release_sock(sock->sk);
		sock_release(sock);
	पूर्ण

	अगर (tc->t_tinc) अणु
		rds_inc_put(&tc->t_tinc->ti_inc);
		tc->t_tinc = शून्य;
	पूर्ण
	tc->t_tinc_hdr_rem = माप(काष्ठा rds_header);
	tc->t_tinc_data_rem = 0;
पूर्ण
