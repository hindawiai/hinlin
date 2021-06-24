<शैली गुरु>
/*
 * Copyright (c) 2006, 2019 Oracle and/or its affiliates. All rights reserved.
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
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/in.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/poll.h>
#समावेश <net/sock.h>

#समावेश "rds.h"

/* this is just used क्रम stats gathering :/ */
अटल DEFINE_SPINLOCK(rds_sock_lock);
अटल अचिन्हित दीर्घ rds_sock_count;
अटल LIST_HEAD(rds_sock_list);
DECLARE_WAIT_QUEUE_HEAD(rds_poll_रुकोq);

/*
 * This is called as the final descriptor referencing this socket is बंदd.
 * We have to unbind the socket so that another socket can be bound to the
 * address it was using.
 *
 * We have to be careful about racing with the incoming path.  sock_orphan()
 * sets SOCK_DEAD and we use that as an indicator to the rx path that new
 * messages shouldn't be queued.
 */
अटल पूर्णांक rds_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा rds_sock *rs;

	अगर (!sk)
		जाओ out;

	rs = rds_sk_to_rs(sk);

	sock_orphan(sk);
	/* Note - rds_clear_recv_queue grअसल rs_recv_lock, so
	 * that ensures the recv path has completed messing
	 * with the socket. */
	rds_clear_recv_queue(rs);
	rds_cong_हटाओ_socket(rs);

	rds_हटाओ_bound(rs);

	rds_send_drop_to(rs, शून्य);
	rds_rdma_drop_keys(rs);
	rds_notअगरy_queue_get(rs, शून्य);
	rds_notअगरy_msg_zcopy_purge(&rs->rs_zcookie_queue);

	spin_lock_bh(&rds_sock_lock);
	list_del_init(&rs->rs_item);
	rds_sock_count--;
	spin_unlock_bh(&rds_sock_lock);

	rds_trans_put(rs->rs_transport);

	sock->sk = शून्य;
	sock_put(sk);
out:
	वापस 0;
पूर्ण

/*
 * Careful not to race with rds_release -> sock_orphan which clears sk_sleep.
 * _bh() isn't OK here, we're called from interrupt handlers.  It's probably OK
 * to wake the रुकोqueue after sk_sleep is clear as we hold a sock ref, but
 * this seems more conservative.
 * NB - normally, one would use sk_callback_lock क्रम this, but we can
 * get here from पूर्णांकerrupts, whereas the network code grअसल sk_callback_lock
 * with _lock_bh only - so relying on sk_callback_lock पूर्णांकroduces livelocks.
 */
व्योम rds_wake_sk_sleep(काष्ठा rds_sock *rs)
अणु
	अचिन्हित दीर्घ flags;

	पढ़ो_lock_irqsave(&rs->rs_recv_lock, flags);
	__rds_wake_sk_sleep(rds_rs_to_sk(rs));
	पढ़ो_unlock_irqrestore(&rs->rs_recv_lock, flags);
पूर्ण

अटल पूर्णांक rds_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
		       पूर्णांक peer)
अणु
	काष्ठा rds_sock *rs = rds_sk_to_rs(sock->sk);
	काष्ठा sockaddr_in6 *sin6;
	काष्ठा sockaddr_in *sin;
	पूर्णांक uaddr_len;

	/* racey, करोn't care */
	अगर (peer) अणु
		अगर (ipv6_addr_any(&rs->rs_conn_addr))
			वापस -ENOTCONN;

		अगर (ipv6_addr_v4mapped(&rs->rs_conn_addr)) अणु
			sin = (काष्ठा sockaddr_in *)uaddr;
			स_रखो(sin->sin_zero, 0, माप(sin->sin_zero));
			sin->sin_family = AF_INET;
			sin->sin_port = rs->rs_conn_port;
			sin->sin_addr.s_addr = rs->rs_conn_addr_v4;
			uaddr_len = माप(*sin);
		पूर्ण अन्यथा अणु
			sin6 = (काष्ठा sockaddr_in6 *)uaddr;
			sin6->sin6_family = AF_INET6;
			sin6->sin6_port = rs->rs_conn_port;
			sin6->sin6_addr = rs->rs_conn_addr;
			sin6->sin6_flowinfo = 0;
			/* scope_id is the same as in the bound address. */
			sin6->sin6_scope_id = rs->rs_bound_scope_id;
			uaddr_len = माप(*sin6);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* If socket is not yet bound and the socket is connected,
		 * set the वापस address family to be the same as the
		 * connected address, but with 0 address value.  If it is not
		 * connected, set the family to be AF_UNSPEC (value 0) and
		 * the address size to be that of an IPv4 address.
		 */
		अगर (ipv6_addr_any(&rs->rs_bound_addr)) अणु
			अगर (ipv6_addr_any(&rs->rs_conn_addr)) अणु
				sin = (काष्ठा sockaddr_in *)uaddr;
				स_रखो(sin, 0, माप(*sin));
				sin->sin_family = AF_UNSPEC;
				वापस माप(*sin);
			पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
			अगर (!(ipv6_addr_type(&rs->rs_conn_addr) &
			      IPV6_ADDR_MAPPED)) अणु
				sin6 = (काष्ठा sockaddr_in6 *)uaddr;
				स_रखो(sin6, 0, माप(*sin6));
				sin6->sin6_family = AF_INET6;
				वापस माप(*sin6);
			पूर्ण
#पूर्ण_अगर

			sin = (काष्ठा sockaddr_in *)uaddr;
			स_रखो(sin, 0, माप(*sin));
			sin->sin_family = AF_INET;
			वापस माप(*sin);
		पूर्ण
		अगर (ipv6_addr_v4mapped(&rs->rs_bound_addr)) अणु
			sin = (काष्ठा sockaddr_in *)uaddr;
			स_रखो(sin->sin_zero, 0, माप(sin->sin_zero));
			sin->sin_family = AF_INET;
			sin->sin_port = rs->rs_bound_port;
			sin->sin_addr.s_addr = rs->rs_bound_addr_v4;
			uaddr_len = माप(*sin);
		पूर्ण अन्यथा अणु
			sin6 = (काष्ठा sockaddr_in6 *)uaddr;
			sin6->sin6_family = AF_INET6;
			sin6->sin6_port = rs->rs_bound_port;
			sin6->sin6_addr = rs->rs_bound_addr;
			sin6->sin6_flowinfo = 0;
			sin6->sin6_scope_id = rs->rs_bound_scope_id;
			uaddr_len = माप(*sin6);
		पूर्ण
	पूर्ण

	वापस uaddr_len;
पूर्ण

/*
 * RDS' poll is without a करोubt the least पूर्णांकuitive part of the पूर्णांकerface,
 * as EPOLLIN and EPOLLOUT करो not behave entirely as you would expect from
 * a network protocol.
 *
 * EPOLLIN is निश्चितed अगर
 *  -	there is data on the receive queue.
 *  -	to संकेत that a previously congested destination may have become
 *	uncongested
 *  -	A notअगरication has been queued to the socket (this can be a congestion
 *	update, or a RDMA completion, or a MSG_ZEROCOPY completion).
 *
 * EPOLLOUT is निश्चितed अगर there is room on the send queue. This करोes not mean
 * however, that the next sendmsg() call will succeed. If the application tries
 * to send to a congested destination, the प्रणाली call may still fail (and
 * वापस ENOBUFS).
 */
अटल __poll_t rds_poll(काष्ठा file *file, काष्ठा socket *sock,
			     poll_table *रुको)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा rds_sock *rs = rds_sk_to_rs(sk);
	__poll_t mask = 0;
	अचिन्हित दीर्घ flags;

	poll_रुको(file, sk_sleep(sk), रुको);

	अगर (rs->rs_seen_congestion)
		poll_रुको(file, &rds_poll_रुकोq, रुको);

	पढ़ो_lock_irqsave(&rs->rs_recv_lock, flags);
	अगर (!rs->rs_cong_monitor) अणु
		/* When a congestion map was updated, we संकेत EPOLLIN क्रम
		 * "historical" reasons. Applications can also poll क्रम
		 * WRBAND instead. */
		अगर (rds_cong_updated_since(&rs->rs_cong_track))
			mask |= (EPOLLIN | EPOLLRDNORM | EPOLLWRBAND);
	पूर्ण अन्यथा अणु
		spin_lock(&rs->rs_lock);
		अगर (rs->rs_cong_notअगरy)
			mask |= (EPOLLIN | EPOLLRDNORM);
		spin_unlock(&rs->rs_lock);
	पूर्ण
	अगर (!list_empty(&rs->rs_recv_queue) ||
	    !list_empty(&rs->rs_notअगरy_queue) ||
	    !list_empty(&rs->rs_zcookie_queue.zcookie_head))
		mask |= (EPOLLIN | EPOLLRDNORM);
	अगर (rs->rs_snd_bytes < rds_sk_sndbuf(rs))
		mask |= (EPOLLOUT | EPOLLWRNORM);
	अगर (sk->sk_err || !skb_queue_empty(&sk->sk_error_queue))
		mask |= POLLERR;
	पढ़ो_unlock_irqrestore(&rs->rs_recv_lock, flags);

	/* clear state any समय we wake a seen-congested socket */
	अगर (mask)
		rs->rs_seen_congestion = 0;

	वापस mask;
पूर्ण

अटल पूर्णांक rds_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा rds_sock *rs = rds_sk_to_rs(sock->sk);
	rds_tos_t utos, tos = 0;

	चयन (cmd) अणु
	हाल SIOCRDSSETTOS:
		अगर (get_user(utos, (rds_tos_t __user *)arg))
			वापस -EFAULT;

		अगर (rs->rs_transport &&
		    rs->rs_transport->get_tos_map)
			tos = rs->rs_transport->get_tos_map(utos);
		अन्यथा
			वापस -ENOIOCTLCMD;

		spin_lock_bh(&rds_sock_lock);
		अगर (rs->rs_tos || rs->rs_conn) अणु
			spin_unlock_bh(&rds_sock_lock);
			वापस -EINVAL;
		पूर्ण
		rs->rs_tos = tos;
		spin_unlock_bh(&rds_sock_lock);
		अवरोध;
	हाल SIOCRDSGETTOS:
		spin_lock_bh(&rds_sock_lock);
		tos = rs->rs_tos;
		spin_unlock_bh(&rds_sock_lock);
		अगर (put_user(tos, (rds_tos_t __user *)arg))
			वापस -EFAULT;
		अवरोध;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rds_cancel_sent_to(काष्ठा rds_sock *rs, sockptr_t optval, पूर्णांक len)
अणु
	काष्ठा sockaddr_in6 sin6;
	काष्ठा sockaddr_in sin;
	पूर्णांक ret = 0;

	/* racing with another thपढ़ो binding seems ok here */
	अगर (ipv6_addr_any(&rs->rs_bound_addr)) अणु
		ret = -ENOTCONN; /* XXX not a great त्रुटि_सं */
		जाओ out;
	पूर्ण

	अगर (len < माप(काष्ठा sockaddr_in)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण अन्यथा अगर (len < माप(काष्ठा sockaddr_in6)) अणु
		/* Assume IPv4 */
		अगर (copy_from_sockptr(&sin, optval,
				माप(काष्ठा sockaddr_in))) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण
		ipv6_addr_set_v4mapped(sin.sin_addr.s_addr, &sin6.sin6_addr);
		sin6.sin6_port = sin.sin_port;
	पूर्ण अन्यथा अणु
		अगर (copy_from_sockptr(&sin6, optval,
				   माप(काष्ठा sockaddr_in6))) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

	rds_send_drop_to(rs, &sin6);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक rds_set_bool_option(अचिन्हित अक्षर *optvar, sockptr_t optval,
			       पूर्णांक optlen)
अणु
	पूर्णांक value;

	अगर (optlen < माप(पूर्णांक))
		वापस -EINVAL;
	अगर (copy_from_sockptr(&value, optval, माप(पूर्णांक)))
		वापस -EFAULT;
	*optvar = !!value;
	वापस 0;
पूर्ण

अटल पूर्णांक rds_cong_monitor(काष्ठा rds_sock *rs, sockptr_t optval, पूर्णांक optlen)
अणु
	पूर्णांक ret;

	ret = rds_set_bool_option(&rs->rs_cong_monitor, optval, optlen);
	अगर (ret == 0) अणु
		अगर (rs->rs_cong_monitor) अणु
			rds_cong_add_socket(rs);
		पूर्ण अन्यथा अणु
			rds_cong_हटाओ_socket(rs);
			rs->rs_cong_mask = 0;
			rs->rs_cong_notअगरy = 0;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक rds_set_transport(काष्ठा rds_sock *rs, sockptr_t optval, पूर्णांक optlen)
अणु
	पूर्णांक t_type;

	अगर (rs->rs_transport)
		वापस -EOPNOTSUPP; /* previously attached to transport */

	अगर (optlen != माप(पूर्णांक))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&t_type, optval, माप(t_type)))
		वापस -EFAULT;

	अगर (t_type < 0 || t_type >= RDS_TRANS_COUNT)
		वापस -EINVAL;

	rs->rs_transport = rds_trans_get(t_type);

	वापस rs->rs_transport ? 0 : -ENOPROTOOPT;
पूर्ण

अटल पूर्णांक rds_enable_recvtstamp(काष्ठा sock *sk, sockptr_t optval,
				 पूर्णांक optlen, पूर्णांक optname)
अणु
	पूर्णांक val, valbool;

	अगर (optlen != माप(पूर्णांक))
		वापस -EFAULT;

	अगर (copy_from_sockptr(&val, optval, माप(पूर्णांक)))
		वापस -EFAULT;

	valbool = val ? 1 : 0;

	अगर (optname == SO_TIMESTAMP_NEW)
		sock_set_flag(sk, SOCK_TSTAMP_NEW);

	अगर (valbool)
		sock_set_flag(sk, SOCK_RCVTSTAMP);
	अन्यथा
		sock_reset_flag(sk, SOCK_RCVTSTAMP);

	वापस 0;
पूर्ण

अटल पूर्णांक rds_recv_track_latency(काष्ठा rds_sock *rs, sockptr_t optval,
				  पूर्णांक optlen)
अणु
	काष्ठा rds_rx_trace_so trace;
	पूर्णांक i;

	अगर (optlen != माप(काष्ठा rds_rx_trace_so))
		वापस -EFAULT;

	अगर (copy_from_sockptr(&trace, optval, माप(trace)))
		वापस -EFAULT;

	अगर (trace.rx_traces > RDS_MSG_RX_DGRAM_TRACE_MAX)
		वापस -EFAULT;

	rs->rs_rx_traces = trace.rx_traces;
	क्रम (i = 0; i < rs->rs_rx_traces; i++) अणु
		अगर (trace.rx_trace_pos[i] > RDS_MSG_RX_DGRAM_TRACE_MAX) अणु
			rs->rs_rx_traces = 0;
			वापस -EFAULT;
		पूर्ण
		rs->rs_rx_trace[i] = trace.rx_trace_pos[i];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rds_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			  sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा rds_sock *rs = rds_sk_to_rs(sock->sk);
	पूर्णांक ret;

	अगर (level != SOL_RDS) अणु
		ret = -ENOPROTOOPT;
		जाओ out;
	पूर्ण

	चयन (optname) अणु
	हाल RDS_CANCEL_SENT_TO:
		ret = rds_cancel_sent_to(rs, optval, optlen);
		अवरोध;
	हाल RDS_GET_MR:
		ret = rds_get_mr(rs, optval, optlen);
		अवरोध;
	हाल RDS_GET_MR_FOR_DEST:
		ret = rds_get_mr_क्रम_dest(rs, optval, optlen);
		अवरोध;
	हाल RDS_FREE_MR:
		ret = rds_मुक्त_mr(rs, optval, optlen);
		अवरोध;
	हाल RDS_RECVERR:
		ret = rds_set_bool_option(&rs->rs_recverr, optval, optlen);
		अवरोध;
	हाल RDS_CONG_MONITOR:
		ret = rds_cong_monitor(rs, optval, optlen);
		अवरोध;
	हाल SO_RDS_TRANSPORT:
		lock_sock(sock->sk);
		ret = rds_set_transport(rs, optval, optlen);
		release_sock(sock->sk);
		अवरोध;
	हाल SO_TIMESTAMP_OLD:
	हाल SO_TIMESTAMP_NEW:
		lock_sock(sock->sk);
		ret = rds_enable_recvtstamp(sock->sk, optval, optlen, optname);
		release_sock(sock->sk);
		अवरोध;
	हाल SO_RDS_MSG_RXPATH_LATENCY:
		ret = rds_recv_track_latency(rs, optval, optlen);
		अवरोध;
	शेष:
		ret = -ENOPROTOOPT;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक rds_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			  अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा rds_sock *rs = rds_sk_to_rs(sock->sk);
	पूर्णांक ret = -ENOPROTOOPT, len;
	पूर्णांक trans;

	अगर (level != SOL_RDS)
		जाओ out;

	अगर (get_user(len, optlen)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	चयन (optname) अणु
	हाल RDS_INFO_FIRST ... RDS_INFO_LAST:
		ret = rds_info_माला_लोockopt(sock, optname, optval,
					  optlen);
		अवरोध;

	हाल RDS_RECVERR:
		अगर (len < माप(पूर्णांक))
			ret = -EINVAL;
		अन्यथा
		अगर (put_user(rs->rs_recverr, (पूर्णांक __user *) optval) ||
		    put_user(माप(पूर्णांक), optlen))
			ret = -EFAULT;
		अन्यथा
			ret = 0;
		अवरोध;
	हाल SO_RDS_TRANSPORT:
		अगर (len < माप(पूर्णांक)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		trans = (rs->rs_transport ? rs->rs_transport->t_type :
			 RDS_TRANS_NONE); /* unbound */
		अगर (put_user(trans, (पूर्णांक __user *)optval) ||
		    put_user(माप(पूर्णांक), optlen))
			ret = -EFAULT;
		अन्यथा
			ret = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

out:
	वापस ret;

पूर्ण

अटल पूर्णांक rds_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
		       पूर्णांक addr_len, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sockaddr_in *sin;
	काष्ठा rds_sock *rs = rds_sk_to_rs(sk);
	पूर्णांक ret = 0;

	अगर (addr_len < दुरत्वend(काष्ठा sockaddr, sa_family))
		वापस -EINVAL;

	lock_sock(sk);

	चयन (uaddr->sa_family) अणु
	हाल AF_INET:
		sin = (काष्ठा sockaddr_in *)uaddr;
		अगर (addr_len < माप(काष्ठा sockaddr_in)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (sin->sin_addr.s_addr == htonl(INADDR_ANY)) अणु
			ret = -EDESTADDRREQ;
			अवरोध;
		पूर्ण
		अगर (ipv4_is_multicast(sin->sin_addr.s_addr) ||
		    sin->sin_addr.s_addr == htonl(INADDR_BROADCAST)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ipv6_addr_set_v4mapped(sin->sin_addr.s_addr, &rs->rs_conn_addr);
		rs->rs_conn_port = sin->sin_port;
		अवरोध;

#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6: अणु
		काष्ठा sockaddr_in6 *sin6;
		पूर्णांक addr_type;

		sin6 = (काष्ठा sockaddr_in6 *)uaddr;
		अगर (addr_len < माप(काष्ठा sockaddr_in6)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		addr_type = ipv6_addr_type(&sin6->sin6_addr);
		अगर (!(addr_type & IPV6_ADDR_UNICAST)) अणु
			__be32 addr4;

			अगर (!(addr_type & IPV6_ADDR_MAPPED)) अणु
				ret = -EPROTOTYPE;
				अवरोध;
			पूर्ण

			/* It is a mapped address.  Need to करो some sanity
			 * checks.
			 */
			addr4 = sin6->sin6_addr.s6_addr32[3];
			अगर (addr4 == htonl(INADDR_ANY) ||
			    addr4 == htonl(INADDR_BROADCAST) ||
			    ipv4_is_multicast(addr4)) अणु
				ret = -EPROTOTYPE;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (addr_type & IPV6_ADDR_LINKLOCAL) अणु
			/* If socket is arleady bound to a link local address,
			 * the peer address must be on the same link.
			 */
			अगर (sin6->sin6_scope_id == 0 ||
			    (!ipv6_addr_any(&rs->rs_bound_addr) &&
			     rs->rs_bound_scope_id &&
			     sin6->sin6_scope_id != rs->rs_bound_scope_id)) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			/* Remember the connected address scope ID.  It will
			 * be checked against the binding local address when
			 * the socket is bound.
			 */
			rs->rs_bound_scope_id = sin6->sin6_scope_id;
		पूर्ण
		rs->rs_conn_addr = sin6->sin6_addr;
		rs->rs_conn_port = sin6->sin6_port;
		अवरोध;
	पूर्ण
#पूर्ण_अगर

	शेष:
		ret = -EAFNOSUPPORT;
		अवरोध;
	पूर्ण

	release_sock(sk);
	वापस ret;
पूर्ण

अटल काष्ठा proto rds_proto = अणु
	.name	  = "RDS",
	.owner	  = THIS_MODULE,
	.obj_size = माप(काष्ठा rds_sock),
पूर्ण;

अटल स्थिर काष्ठा proto_ops rds_proto_ops = अणु
	.family =	AF_RDS,
	.owner =	THIS_MODULE,
	.release =	rds_release,
	.bind =		rds_bind,
	.connect =	rds_connect,
	.socketpair =	sock_no_socketpair,
	.accept =	sock_no_accept,
	.getname =	rds_getname,
	.poll =		rds_poll,
	.ioctl =	rds_ioctl,
	.listen =	sock_no_listen,
	.shutकरोwn =	sock_no_shutकरोwn,
	.setsockopt =	rds_setsockopt,
	.माला_लोockopt =	rds_माला_लोockopt,
	.sendmsg =	rds_sendmsg,
	.recvmsg =	rds_recvmsg,
	.mmap =		sock_no_mmap,
	.sendpage =	sock_no_sendpage,
पूर्ण;

अटल व्योम rds_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा rds_sock *rs = rds_sk_to_rs(sk);

	WARN_ON((&rs->rs_item != rs->rs_item.next ||
		 &rs->rs_item != rs->rs_item.prev));
पूर्ण

अटल पूर्णांक __rds_create(काष्ठा socket *sock, काष्ठा sock *sk, पूर्णांक protocol)
अणु
	काष्ठा rds_sock *rs;

	sock_init_data(sock, sk);
	sock->ops		= &rds_proto_ops;
	sk->sk_protocol		= protocol;
	sk->sk_deकाष्ठा		= rds_sock_deकाष्ठा;

	rs = rds_sk_to_rs(sk);
	spin_lock_init(&rs->rs_lock);
	rwlock_init(&rs->rs_recv_lock);
	INIT_LIST_HEAD(&rs->rs_send_queue);
	INIT_LIST_HEAD(&rs->rs_recv_queue);
	INIT_LIST_HEAD(&rs->rs_notअगरy_queue);
	INIT_LIST_HEAD(&rs->rs_cong_list);
	rds_message_zcopy_queue_init(&rs->rs_zcookie_queue);
	spin_lock_init(&rs->rs_rdma_lock);
	rs->rs_rdma_keys = RB_ROOT;
	rs->rs_rx_traces = 0;
	rs->rs_tos = 0;
	rs->rs_conn = शून्य;

	spin_lock_bh(&rds_sock_lock);
	list_add_tail(&rs->rs_item, &rds_sock_list);
	rds_sock_count++;
	spin_unlock_bh(&rds_sock_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक rds_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
		      पूर्णांक kern)
अणु
	काष्ठा sock *sk;

	अगर (sock->type != SOCK_SEQPACKET || protocol)
		वापस -ESOCKTNOSUPPORT;

	sk = sk_alloc(net, AF_RDS, GFP_KERNEL, &rds_proto, kern);
	अगर (!sk)
		वापस -ENOMEM;

	वापस __rds_create(sock, sk, protocol);
पूर्ण

व्योम rds_sock_addref(काष्ठा rds_sock *rs)
अणु
	sock_hold(rds_rs_to_sk(rs));
पूर्ण

व्योम rds_sock_put(काष्ठा rds_sock *rs)
अणु
	sock_put(rds_rs_to_sk(rs));
पूर्ण

अटल स्थिर काष्ठा net_proto_family rds_family_ops = अणु
	.family =	AF_RDS,
	.create =	rds_create,
	.owner	=	THIS_MODULE,
पूर्ण;

अटल व्योम rds_sock_inc_info(काष्ठा socket *sock, अचिन्हित पूर्णांक len,
			      काष्ठा rds_info_iterator *iter,
			      काष्ठा rds_info_lengths *lens)
अणु
	काष्ठा rds_sock *rs;
	काष्ठा rds_incoming *inc;
	अचिन्हित पूर्णांक total = 0;

	len /= माप(काष्ठा rds_info_message);

	spin_lock_bh(&rds_sock_lock);

	list_क्रम_each_entry(rs, &rds_sock_list, rs_item) अणु
		/* This option only supports IPv4 sockets. */
		अगर (!ipv6_addr_v4mapped(&rs->rs_bound_addr))
			जारी;

		पढ़ो_lock(&rs->rs_recv_lock);

		/* XXX too lazy to मुख्यtain counts.. */
		list_क्रम_each_entry(inc, &rs->rs_recv_queue, i_item) अणु
			total++;
			अगर (total <= len)
				rds_inc_info_copy(inc, iter,
						  inc->i_saddr.s6_addr32[3],
						  rs->rs_bound_addr_v4,
						  1);
		पूर्ण

		पढ़ो_unlock(&rs->rs_recv_lock);
	पूर्ण

	spin_unlock_bh(&rds_sock_lock);

	lens->nr = total;
	lens->each = माप(काष्ठा rds_info_message);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम rds6_sock_inc_info(काष्ठा socket *sock, अचिन्हित पूर्णांक len,
			       काष्ठा rds_info_iterator *iter,
			       काष्ठा rds_info_lengths *lens)
अणु
	काष्ठा rds_incoming *inc;
	अचिन्हित पूर्णांक total = 0;
	काष्ठा rds_sock *rs;

	len /= माप(काष्ठा rds6_info_message);

	spin_lock_bh(&rds_sock_lock);

	list_क्रम_each_entry(rs, &rds_sock_list, rs_item) अणु
		पढ़ो_lock(&rs->rs_recv_lock);

		list_क्रम_each_entry(inc, &rs->rs_recv_queue, i_item) अणु
			total++;
			अगर (total <= len)
				rds6_inc_info_copy(inc, iter, &inc->i_saddr,
						   &rs->rs_bound_addr, 1);
		पूर्ण

		पढ़ो_unlock(&rs->rs_recv_lock);
	पूर्ण

	spin_unlock_bh(&rds_sock_lock);

	lens->nr = total;
	lens->each = माप(काष्ठा rds6_info_message);
पूर्ण
#पूर्ण_अगर

अटल व्योम rds_sock_info(काष्ठा socket *sock, अचिन्हित पूर्णांक len,
			  काष्ठा rds_info_iterator *iter,
			  काष्ठा rds_info_lengths *lens)
अणु
	काष्ठा rds_info_socket sinfo;
	अचिन्हित पूर्णांक cnt = 0;
	काष्ठा rds_sock *rs;

	len /= माप(काष्ठा rds_info_socket);

	spin_lock_bh(&rds_sock_lock);

	अगर (len < rds_sock_count) अणु
		cnt = rds_sock_count;
		जाओ out;
	पूर्ण

	list_क्रम_each_entry(rs, &rds_sock_list, rs_item) अणु
		/* This option only supports IPv4 sockets. */
		अगर (!ipv6_addr_v4mapped(&rs->rs_bound_addr))
			जारी;
		sinfo.sndbuf = rds_sk_sndbuf(rs);
		sinfo.rcvbuf = rds_sk_rcvbuf(rs);
		sinfo.bound_addr = rs->rs_bound_addr_v4;
		sinfo.connected_addr = rs->rs_conn_addr_v4;
		sinfo.bound_port = rs->rs_bound_port;
		sinfo.connected_port = rs->rs_conn_port;
		sinfo.inum = sock_i_ino(rds_rs_to_sk(rs));

		rds_info_copy(iter, &sinfo, माप(sinfo));
		cnt++;
	पूर्ण

out:
	lens->nr = cnt;
	lens->each = माप(काष्ठा rds_info_socket);

	spin_unlock_bh(&rds_sock_lock);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम rds6_sock_info(काष्ठा socket *sock, अचिन्हित पूर्णांक len,
			   काष्ठा rds_info_iterator *iter,
			   काष्ठा rds_info_lengths *lens)
अणु
	काष्ठा rds6_info_socket sinfo6;
	काष्ठा rds_sock *rs;

	len /= माप(काष्ठा rds6_info_socket);

	spin_lock_bh(&rds_sock_lock);

	अगर (len < rds_sock_count)
		जाओ out;

	list_क्रम_each_entry(rs, &rds_sock_list, rs_item) अणु
		sinfo6.sndbuf = rds_sk_sndbuf(rs);
		sinfo6.rcvbuf = rds_sk_rcvbuf(rs);
		sinfo6.bound_addr = rs->rs_bound_addr;
		sinfo6.connected_addr = rs->rs_conn_addr;
		sinfo6.bound_port = rs->rs_bound_port;
		sinfo6.connected_port = rs->rs_conn_port;
		sinfo6.inum = sock_i_ino(rds_rs_to_sk(rs));

		rds_info_copy(iter, &sinfo6, माप(sinfo6));
	पूर्ण

 out:
	lens->nr = rds_sock_count;
	lens->each = माप(काष्ठा rds6_info_socket);

	spin_unlock_bh(&rds_sock_lock);
पूर्ण
#पूर्ण_अगर

अटल व्योम rds_निकास(व्योम)
अणु
	sock_unरेजिस्टर(rds_family_ops.family);
	proto_unरेजिस्टर(&rds_proto);
	rds_conn_निकास();
	rds_cong_निकास();
	rds_sysctl_निकास();
	rds_thपढ़ोs_निकास();
	rds_stats_निकास();
	rds_page_निकास();
	rds_bind_lock_destroy();
	rds_info_deरेजिस्टर_func(RDS_INFO_SOCKETS, rds_sock_info);
	rds_info_deरेजिस्टर_func(RDS_INFO_RECV_MESSAGES, rds_sock_inc_info);
#अगर IS_ENABLED(CONFIG_IPV6)
	rds_info_deरेजिस्टर_func(RDS6_INFO_SOCKETS, rds6_sock_info);
	rds_info_deरेजिस्टर_func(RDS6_INFO_RECV_MESSAGES, rds6_sock_inc_info);
#पूर्ण_अगर
पूर्ण
module_निकास(rds_निकास);

u32 rds_gen_num;

अटल पूर्णांक rds_init(व्योम)
अणु
	पूर्णांक ret;

	net_get_अक्रमom_once(&rds_gen_num, माप(rds_gen_num));

	ret = rds_bind_lock_init();
	अगर (ret)
		जाओ out;

	ret = rds_conn_init();
	अगर (ret)
		जाओ out_bind;

	ret = rds_thपढ़ोs_init();
	अगर (ret)
		जाओ out_conn;
	ret = rds_sysctl_init();
	अगर (ret)
		जाओ out_thपढ़ोs;
	ret = rds_stats_init();
	अगर (ret)
		जाओ out_sysctl;
	ret = proto_रेजिस्टर(&rds_proto, 1);
	अगर (ret)
		जाओ out_stats;
	ret = sock_रेजिस्टर(&rds_family_ops);
	अगर (ret)
		जाओ out_proto;

	rds_info_रेजिस्टर_func(RDS_INFO_SOCKETS, rds_sock_info);
	rds_info_रेजिस्टर_func(RDS_INFO_RECV_MESSAGES, rds_sock_inc_info);
#अगर IS_ENABLED(CONFIG_IPV6)
	rds_info_रेजिस्टर_func(RDS6_INFO_SOCKETS, rds6_sock_info);
	rds_info_रेजिस्टर_func(RDS6_INFO_RECV_MESSAGES, rds6_sock_inc_info);
#पूर्ण_अगर

	जाओ out;

out_proto:
	proto_unरेजिस्टर(&rds_proto);
out_stats:
	rds_stats_निकास();
out_sysctl:
	rds_sysctl_निकास();
out_thपढ़ोs:
	rds_thपढ़ोs_निकास();
out_conn:
	rds_conn_निकास();
	rds_cong_निकास();
	rds_page_निकास();
out_bind:
	rds_bind_lock_destroy();
out:
	वापस ret;
पूर्ण
module_init(rds_init);

#घोषणा DRV_VERSION     "4.0"
#घोषणा DRV_RELDATE     "Feb 12, 2009"

MODULE_AUTHOR("Oracle Corporation <rds-devel@oss.oracle.com>");
MODULE_DESCRIPTION("RDS: Reliable Datagram Sockets"
		   " v" DRV_VERSION " (" DRV_RELDATE ")");
MODULE_VERSION(DRV_VERSION);
MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS_NETPROTO(PF_RDS);
