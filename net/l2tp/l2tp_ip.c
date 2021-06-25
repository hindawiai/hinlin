<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* L2TPv3 IP encapsulation support
 *
 * Copyright (c) 2008,2009,2010 Katalix Systems Ltd
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <यंत्र/ioctls.h>
#समावेश <linux/icmp.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/socket.h>
#समावेश <linux/l2tp.h>
#समावेश <linux/in.h>
#समावेश <net/sock.h>
#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/udp.h>
#समावेश <net/inet_common.h>
#समावेश <net/tcp_states.h>
#समावेश <net/protocol.h>
#समावेश <net/xfrm.h>

#समावेश "l2tp_core.h"

काष्ठा l2tp_ip_sock अणु
	/* inet_sock has to be the first member of l2tp_ip_sock */
	काष्ठा inet_sock	inet;

	u32			conn_id;
	u32			peer_conn_id;
पूर्ण;

अटल DEFINE_RWLOCK(l2tp_ip_lock);
अटल काष्ठा hlist_head l2tp_ip_table;
अटल काष्ठा hlist_head l2tp_ip_bind_table;

अटल अंतरभूत काष्ठा l2tp_ip_sock *l2tp_ip_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा l2tp_ip_sock *)sk;
पूर्ण

अटल काष्ठा sock *__l2tp_ip_bind_lookup(स्थिर काष्ठा net *net, __be32 laddr,
					  __be32 raddr, पूर्णांक dअगर, u32 tunnel_id)
अणु
	काष्ठा sock *sk;

	sk_क्रम_each_bound(sk, &l2tp_ip_bind_table) अणु
		स्थिर काष्ठा l2tp_ip_sock *l2tp = l2tp_ip_sk(sk);
		स्थिर काष्ठा inet_sock *inet = inet_sk(sk);

		अगर (!net_eq(sock_net(sk), net))
			जारी;

		अगर (sk->sk_bound_dev_अगर && dअगर && sk->sk_bound_dev_अगर != dअगर)
			जारी;

		अगर (inet->inet_rcv_saddr && laddr &&
		    inet->inet_rcv_saddr != laddr)
			जारी;

		अगर (inet->inet_daddr && raddr && inet->inet_daddr != raddr)
			जारी;

		अगर (l2tp->conn_id != tunnel_id)
			जारी;

		जाओ found;
	पूर्ण

	sk = शून्य;
found:
	वापस sk;
पूर्ण

/* When processing receive frames, there are two हालs to
 * consider. Data frames consist of a non-zero session-id and an
 * optional cookie. Control frames consist of a regular L2TP header
 * preceded by 32-bits of zeros.
 *
 * L2TPv3 Session Header Over IP
 *
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                           Session ID                          |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |               Cookie (optional, maximum 64 bits)...
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *                                                                 |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * L2TPv3 Control Message Header Over IP
 *
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                      (32 bits of zeros)                       |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |T|L|x|x|S|x|x|x|x|x|x|x|  Ver  |             Length            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                     Control Connection ID                     |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |               Ns              |               Nr              |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * All control frames are passed to userspace.
 */
अटल पूर्णांक l2tp_ip_recv(काष्ठा sk_buff *skb)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा sock *sk;
	u32 session_id;
	u32 tunnel_id;
	अचिन्हित अक्षर *ptr, *optr;
	काष्ठा l2tp_session *session;
	काष्ठा l2tp_tunnel *tunnel = शून्य;
	काष्ठा iphdr *iph;

	अगर (!pskb_may_pull(skb, 4))
		जाओ discard;

	/* Poपूर्णांक to L2TP header */
	optr = skb->data;
	ptr = skb->data;
	session_id = ntohl(*((__be32 *)ptr));
	ptr += 4;

	/* RFC3931: L2TP/IP packets have the first 4 bytes containing
	 * the session_id. If it is 0, the packet is a L2TP control
	 * frame and the session_id value can be discarded.
	 */
	अगर (session_id == 0) अणु
		__skb_pull(skb, 4);
		जाओ pass_up;
	पूर्ण

	/* Ok, this is a data packet. Lookup the session. */
	session = l2tp_session_get(net, session_id);
	अगर (!session)
		जाओ discard;

	tunnel = session->tunnel;
	अगर (!tunnel)
		जाओ discard_sess;

	अगर (l2tp_v3_ensure_opt_in_linear(session, skb, &ptr, &optr))
		जाओ discard_sess;

	l2tp_recv_common(session, skb, ptr, optr, 0, skb->len);
	l2tp_session_dec_refcount(session);

	वापस 0;

pass_up:
	/* Get the tunnel_id from the L2TP header */
	अगर (!pskb_may_pull(skb, 12))
		जाओ discard;

	अगर ((skb->data[0] & 0xc0) != 0xc0)
		जाओ discard;

	tunnel_id = ntohl(*(__be32 *)&skb->data[4]);
	iph = (काष्ठा iphdr *)skb_network_header(skb);

	पढ़ो_lock_bh(&l2tp_ip_lock);
	sk = __l2tp_ip_bind_lookup(net, iph->daddr, iph->saddr, inet_iअगर(skb),
				   tunnel_id);
	अगर (!sk) अणु
		पढ़ो_unlock_bh(&l2tp_ip_lock);
		जाओ discard;
	पूर्ण
	sock_hold(sk);
	पढ़ो_unlock_bh(&l2tp_ip_lock);

	अगर (!xfrm4_policy_check(sk, XFRM_POLICY_IN, skb))
		जाओ discard_put;

	nf_reset_ct(skb);

	वापस sk_receive_skb(sk, skb, 1);

discard_sess:
	l2tp_session_dec_refcount(session);
	जाओ discard;

discard_put:
	sock_put(sk);

discard:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक l2tp_ip_hash(काष्ठा sock *sk)
अणु
	अगर (sk_unhashed(sk)) अणु
		ग_लिखो_lock_bh(&l2tp_ip_lock);
		sk_add_node(sk, &l2tp_ip_table);
		ग_लिखो_unlock_bh(&l2tp_ip_lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम l2tp_ip_unhash(काष्ठा sock *sk)
अणु
	अगर (sk_unhashed(sk))
		वापस;
	ग_लिखो_lock_bh(&l2tp_ip_lock);
	sk_del_node_init(sk);
	ग_लिखो_unlock_bh(&l2tp_ip_lock);
पूर्ण

अटल पूर्णांक l2tp_ip_खोलो(काष्ठा sock *sk)
अणु
	/* Prevent स्वतःbind. We करोn't have ports. */
	inet_sk(sk)->inet_num = IPPROTO_L2TP;

	l2tp_ip_hash(sk);
	वापस 0;
पूर्ण

अटल व्योम l2tp_ip_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	ग_लिखो_lock_bh(&l2tp_ip_lock);
	hlist_del_init(&sk->sk_bind_node);
	sk_del_node_init(sk);
	ग_लिखो_unlock_bh(&l2tp_ip_lock);
	sk_common_release(sk);
पूर्ण

अटल व्योम l2tp_ip_destroy_sock(काष्ठा sock *sk)
अणु
	काष्ठा l2tp_tunnel *tunnel = l2tp_sk_to_tunnel(sk);
	काष्ठा sk_buff *skb;

	जबतक ((skb = __skb_dequeue_tail(&sk->sk_ग_लिखो_queue)) != शून्य)
		kमुक्त_skb(skb);

	अगर (tunnel)
		l2tp_tunnel_delete(tunnel);
पूर्ण

अटल पूर्णांक l2tp_ip_bind(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा sockaddr_l2tpip *addr = (काष्ठा sockaddr_l2tpip *)uaddr;
	काष्ठा net *net = sock_net(sk);
	पूर्णांक ret;
	पूर्णांक chk_addr_ret;

	अगर (addr_len < माप(काष्ठा sockaddr_l2tpip))
		वापस -EINVAL;
	अगर (addr->l2tp_family != AF_INET)
		वापस -EINVAL;

	lock_sock(sk);

	ret = -EINVAL;
	अगर (!sock_flag(sk, SOCK_ZAPPED))
		जाओ out;

	अगर (sk->sk_state != TCP_CLOSE)
		जाओ out;

	chk_addr_ret = inet_addr_type(net, addr->l2tp_addr.s_addr);
	ret = -EADDRNOTAVAIL;
	अगर (addr->l2tp_addr.s_addr && chk_addr_ret != RTN_LOCAL &&
	    chk_addr_ret != RTN_MULTICAST && chk_addr_ret != RTN_BROADCAST)
		जाओ out;

	अगर (addr->l2tp_addr.s_addr) अणु
		inet->inet_rcv_saddr = addr->l2tp_addr.s_addr;
		inet->inet_saddr = addr->l2tp_addr.s_addr;
	पूर्ण
	अगर (chk_addr_ret == RTN_MULTICAST || chk_addr_ret == RTN_BROADCAST)
		inet->inet_saddr = 0;  /* Use device */

	ग_लिखो_lock_bh(&l2tp_ip_lock);
	अगर (__l2tp_ip_bind_lookup(net, addr->l2tp_addr.s_addr, 0,
				  sk->sk_bound_dev_अगर, addr->l2tp_conn_id)) अणु
		ग_लिखो_unlock_bh(&l2tp_ip_lock);
		ret = -EADDRINUSE;
		जाओ out;
	पूर्ण

	sk_dst_reset(sk);
	l2tp_ip_sk(sk)->conn_id = addr->l2tp_conn_id;

	sk_add_bind_node(sk, &l2tp_ip_bind_table);
	sk_del_node_init(sk);
	ग_लिखो_unlock_bh(&l2tp_ip_lock);

	ret = 0;
	sock_reset_flag(sk, SOCK_ZAPPED);

out:
	release_sock(sk);

	वापस ret;
पूर्ण

अटल पूर्णांक l2tp_ip_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा sockaddr_l2tpip *lsa = (काष्ठा sockaddr_l2tpip *)uaddr;
	पूर्णांक rc;

	अगर (addr_len < माप(*lsa))
		वापस -EINVAL;

	अगर (ipv4_is_multicast(lsa->l2tp_addr.s_addr))
		वापस -EINVAL;

	lock_sock(sk);

	/* Must bind first - स्वतःbinding करोes not work */
	अगर (sock_flag(sk, SOCK_ZAPPED)) अणु
		rc = -EINVAL;
		जाओ out_sk;
	पूर्ण

	rc = __ip4_datagram_connect(sk, uaddr, addr_len);
	अगर (rc < 0)
		जाओ out_sk;

	l2tp_ip_sk(sk)->peer_conn_id = lsa->l2tp_conn_id;

	ग_लिखो_lock_bh(&l2tp_ip_lock);
	hlist_del_init(&sk->sk_bind_node);
	sk_add_bind_node(sk, &l2tp_ip_bind_table);
	ग_लिखो_unlock_bh(&l2tp_ip_lock);

out_sk:
	release_sock(sk);

	वापस rc;
पूर्ण

अटल पूर्णांक l2tp_ip_disconnect(काष्ठा sock *sk, पूर्णांक flags)
अणु
	अगर (sock_flag(sk, SOCK_ZAPPED))
		वापस 0;

	वापस __udp_disconnect(sk, flags);
पूर्ण

अटल पूर्णांक l2tp_ip_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			   पूर्णांक peer)
अणु
	काष्ठा sock *sk		= sock->sk;
	काष्ठा inet_sock *inet	= inet_sk(sk);
	काष्ठा l2tp_ip_sock *lsk = l2tp_ip_sk(sk);
	काष्ठा sockaddr_l2tpip *lsa = (काष्ठा sockaddr_l2tpip *)uaddr;

	स_रखो(lsa, 0, माप(*lsa));
	lsa->l2tp_family = AF_INET;
	अगर (peer) अणु
		अगर (!inet->inet_dport)
			वापस -ENOTCONN;
		lsa->l2tp_conn_id = lsk->peer_conn_id;
		lsa->l2tp_addr.s_addr = inet->inet_daddr;
	पूर्ण अन्यथा अणु
		__be32 addr = inet->inet_rcv_saddr;

		अगर (!addr)
			addr = inet->inet_saddr;
		lsa->l2tp_conn_id = lsk->conn_id;
		lsa->l2tp_addr.s_addr = addr;
	पूर्ण
	वापस माप(*lsa);
पूर्ण

अटल पूर्णांक l2tp_ip_backlog_recv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc;

	/* Charge it to the socket, dropping अगर the queue is full. */
	rc = sock_queue_rcv_skb(sk, skb);
	अगर (rc < 0)
		जाओ drop;

	वापस 0;

drop:
	IP_INC_STATS(sock_net(sk), IPSTATS_MIB_INDISCARDS);
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/* Userspace will call sendmsg() on the tunnel socket to send L2TP
 * control frames.
 */
अटल पूर्णांक l2tp_ip_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक rc;
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा rtable *rt = शून्य;
	काष्ठा flowi4 *fl4;
	पूर्णांक connected = 0;
	__be32 daddr;

	lock_sock(sk);

	rc = -ENOTCONN;
	अगर (sock_flag(sk, SOCK_DEAD))
		जाओ out;

	/* Get and verअगरy the address. */
	अगर (msg->msg_name) अणु
		DECLARE_SOCKADDR(काष्ठा sockaddr_l2tpip *, lip, msg->msg_name);

		rc = -EINVAL;
		अगर (msg->msg_namelen < माप(*lip))
			जाओ out;

		अगर (lip->l2tp_family != AF_INET) अणु
			rc = -EAFNOSUPPORT;
			अगर (lip->l2tp_family != AF_UNSPEC)
				जाओ out;
		पूर्ण

		daddr = lip->l2tp_addr.s_addr;
	पूर्ण अन्यथा अणु
		rc = -EDESTADDRREQ;
		अगर (sk->sk_state != TCP_ESTABLISHED)
			जाओ out;

		daddr = inet->inet_daddr;
		connected = 1;
	पूर्ण

	/* Allocate a socket buffer */
	rc = -ENOMEM;
	skb = sock_wदो_स्मृति(sk, 2 + NET_SKB_PAD + माप(काष्ठा iphdr) +
			   4 + len, 0, GFP_KERNEL);
	अगर (!skb)
		जाओ error;

	/* Reserve space क्रम headers, putting IP header on 4-byte boundary. */
	skb_reserve(skb, 2 + NET_SKB_PAD);
	skb_reset_network_header(skb);
	skb_reserve(skb, माप(काष्ठा iphdr));
	skb_reset_transport_header(skb);

	/* Insert 0 session_id */
	*((__be32 *)skb_put(skb, 4)) = 0;

	/* Copy user data पूर्णांकo skb */
	rc = स_नकल_from_msg(skb_put(skb, len), msg, len);
	अगर (rc < 0) अणु
		kमुक्त_skb(skb);
		जाओ error;
	पूर्ण

	fl4 = &inet->cork.fl.u.ip4;
	अगर (connected)
		rt = (काष्ठा rtable *)__sk_dst_check(sk, 0);

	rcu_पढ़ो_lock();
	अगर (!rt) अणु
		स्थिर काष्ठा ip_options_rcu *inet_opt;

		inet_opt = rcu_dereference(inet->inet_opt);

		/* Use correct destination address अगर we have options. */
		अगर (inet_opt && inet_opt->opt.srr)
			daddr = inet_opt->opt.faddr;

		/* If this fails, retransmit mechanism of transport layer will
		 * keep trying until route appears or the connection बार
		 * itself out.
		 */
		rt = ip_route_output_ports(sock_net(sk), fl4, sk,
					   daddr, inet->inet_saddr,
					   inet->inet_dport, inet->inet_sport,
					   sk->sk_protocol, RT_CONN_FLAGS(sk),
					   sk->sk_bound_dev_अगर);
		अगर (IS_ERR(rt))
			जाओ no_route;
		अगर (connected) अणु
			sk_setup_caps(sk, &rt->dst);
		पूर्ण अन्यथा अणु
			skb_dst_set(skb, &rt->dst);
			जाओ xmit;
		पूर्ण
	पूर्ण

	/* We करोnt need to clone dst here, it is guaranteed to not disappear.
	 *  __dev_xmit_skb() might क्रमce a refcount अगर needed.
	 */
	skb_dst_set_noref(skb, &rt->dst);

xmit:
	/* Queue the packet to IP क्रम output */
	rc = ip_queue_xmit(sk, skb, &inet->cork.fl);
	rcu_पढ़ो_unlock();

error:
	अगर (rc >= 0)
		rc = len;

out:
	release_sock(sk);
	वापस rc;

no_route:
	rcu_पढ़ो_unlock();
	IP_INC_STATS(sock_net(sk), IPSTATS_MIB_OUTNOROUTES);
	kमुक्त_skb(skb);
	rc = -EHOSTUNREACH;
	जाओ out;
पूर्ण

अटल पूर्णांक l2tp_ip_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg,
			   माप_प्रकार len, पूर्णांक noblock, पूर्णांक flags, पूर्णांक *addr_len)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	माप_प्रकार copied = 0;
	पूर्णांक err = -EOPNOTSUPP;
	DECLARE_SOCKADDR(काष्ठा sockaddr_in *, sin, msg->msg_name);
	काष्ठा sk_buff *skb;

	अगर (flags & MSG_OOB)
		जाओ out;

	skb = skb_recv_datagram(sk, flags, noblock, &err);
	अगर (!skb)
		जाओ out;

	copied = skb->len;
	अगर (len < copied) अणु
		msg->msg_flags |= MSG_TRUNC;
		copied = len;
	पूर्ण

	err = skb_copy_datagram_msg(skb, 0, msg, copied);
	अगर (err)
		जाओ करोne;

	sock_recv_बारtamp(msg, sk, skb);

	/* Copy the address. */
	अगर (sin) अणु
		sin->sin_family = AF_INET;
		sin->sin_addr.s_addr = ip_hdr(skb)->saddr;
		sin->sin_port = 0;
		स_रखो(&sin->sin_zero, 0, माप(sin->sin_zero));
		*addr_len = माप(*sin);
	पूर्ण
	अगर (inet->cmsg_flags)
		ip_cmsg_recv(msg, skb);
	अगर (flags & MSG_TRUNC)
		copied = skb->len;
करोne:
	skb_मुक्त_datagram(sk, skb);
out:
	वापस err ? err : copied;
पूर्ण

पूर्णांक l2tp_ioctl(काष्ठा sock *sk, पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक amount;

	चयन (cmd) अणु
	हाल SIOCOUTQ:
		amount = sk_wmem_alloc_get(sk);
		अवरोध;
	हाल SIOCINQ:
		spin_lock_bh(&sk->sk_receive_queue.lock);
		skb = skb_peek(&sk->sk_receive_queue);
		amount = skb ? skb->len : 0;
		spin_unlock_bh(&sk->sk_receive_queue.lock);
		अवरोध;

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस put_user(amount, (पूर्णांक __user *)arg);
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_ioctl);

अटल काष्ठा proto l2tp_ip_prot = अणु
	.name		   = "L2TP/IP",
	.owner		   = THIS_MODULE,
	.init		   = l2tp_ip_खोलो,
	.बंद		   = l2tp_ip_बंद,
	.bind		   = l2tp_ip_bind,
	.connect	   = l2tp_ip_connect,
	.disconnect	   = l2tp_ip_disconnect,
	.ioctl		   = l2tp_ioctl,
	.destroy	   = l2tp_ip_destroy_sock,
	.setsockopt	   = ip_setsockopt,
	.माला_लोockopt	   = ip_माला_लोockopt,
	.sendmsg	   = l2tp_ip_sendmsg,
	.recvmsg	   = l2tp_ip_recvmsg,
	.backlog_rcv	   = l2tp_ip_backlog_recv,
	.hash		   = l2tp_ip_hash,
	.unhash		   = l2tp_ip_unhash,
	.obj_size	   = माप(काष्ठा l2tp_ip_sock),
पूर्ण;

अटल स्थिर काष्ठा proto_ops l2tp_ip_ops = अणु
	.family		   = PF_INET,
	.owner		   = THIS_MODULE,
	.release	   = inet_release,
	.bind		   = inet_bind,
	.connect	   = inet_dgram_connect,
	.socketpair	   = sock_no_socketpair,
	.accept		   = sock_no_accept,
	.getname	   = l2tp_ip_getname,
	.poll		   = datagram_poll,
	.ioctl		   = inet_ioctl,
	.gettstamp	   = sock_gettstamp,
	.listen		   = sock_no_listen,
	.shutकरोwn	   = inet_shutकरोwn,
	.setsockopt	   = sock_common_setsockopt,
	.माला_लोockopt	   = sock_common_माला_लोockopt,
	.sendmsg	   = inet_sendmsg,
	.recvmsg	   = sock_common_recvmsg,
	.mmap		   = sock_no_mmap,
	.sendpage	   = sock_no_sendpage,
पूर्ण;

अटल काष्ठा inet_protosw l2tp_ip_protosw = अणु
	.type		= SOCK_DGRAM,
	.protocol	= IPPROTO_L2TP,
	.prot		= &l2tp_ip_prot,
	.ops		= &l2tp_ip_ops,
पूर्ण;

अटल काष्ठा net_protocol l2tp_ip_protocol __पढ़ो_mostly = अणु
	.handler	= l2tp_ip_recv,
	.netns_ok	= 1,
पूर्ण;

अटल पूर्णांक __init l2tp_ip_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("L2TP IP encapsulation support (L2TPv3)\n");

	err = proto_रेजिस्टर(&l2tp_ip_prot, 1);
	अगर (err != 0)
		जाओ out;

	err = inet_add_protocol(&l2tp_ip_protocol, IPPROTO_L2TP);
	अगर (err)
		जाओ out1;

	inet_रेजिस्टर_protosw(&l2tp_ip_protosw);
	वापस 0;

out1:
	proto_unरेजिस्टर(&l2tp_ip_prot);
out:
	वापस err;
पूर्ण

अटल व्योम __निकास l2tp_ip_निकास(व्योम)
अणु
	inet_unरेजिस्टर_protosw(&l2tp_ip_protosw);
	inet_del_protocol(&l2tp_ip_protocol, IPPROTO_L2TP);
	proto_unरेजिस्टर(&l2tp_ip_prot);
पूर्ण

module_init(l2tp_ip_init);
module_निकास(l2tp_ip_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("James Chapman <jchapman@katalix.com>");
MODULE_DESCRIPTION("L2TP over IP");
MODULE_VERSION("1.0");

/* Use the value of SOCK_DGRAM (2) directory, because __stringअगरy करोesn't like
 * क्रमागतs
 */
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_INET, 2, IPPROTO_L2TP);
MODULE_ALIAS_NET_PF_PROTO(PF_INET, IPPROTO_L2TP);
