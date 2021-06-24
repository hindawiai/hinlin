<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* L2TPv3 IP encapsulation support क्रम IPv6
 *
 * Copyright (c) 2012 Katalix Systems Ltd
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/icmp.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/socket.h>
#समावेश <linux/l2tp.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <net/sock.h>
#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/udp.h>
#समावेश <net/inet_common.h>
#समावेश <net/tcp_states.h>
#समावेश <net/protocol.h>
#समावेश <net/xfrm.h>

#समावेश <net/transp_v6.h>
#समावेश <net/addrconf.h>
#समावेश <net/ip6_route.h>

#समावेश "l2tp_core.h"

काष्ठा l2tp_ip6_sock अणु
	/* inet_sock has to be the first member of l2tp_ip6_sock */
	काष्ठा inet_sock	inet;

	u32			conn_id;
	u32			peer_conn_id;

	/* ipv6_pinfo has to be the last member of l2tp_ip6_sock, see
	 * inet6_sk_generic
	 */
	काष्ठा ipv6_pinfo	inet6;
पूर्ण;

अटल DEFINE_RWLOCK(l2tp_ip6_lock);
अटल काष्ठा hlist_head l2tp_ip6_table;
अटल काष्ठा hlist_head l2tp_ip6_bind_table;

अटल अंतरभूत काष्ठा l2tp_ip6_sock *l2tp_ip6_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा l2tp_ip6_sock *)sk;
पूर्ण

अटल काष्ठा sock *__l2tp_ip6_bind_lookup(स्थिर काष्ठा net *net,
					   स्थिर काष्ठा in6_addr *laddr,
					   स्थिर काष्ठा in6_addr *raddr,
					   पूर्णांक dअगर, u32 tunnel_id)
अणु
	काष्ठा sock *sk;

	sk_क्रम_each_bound(sk, &l2tp_ip6_bind_table) अणु
		स्थिर काष्ठा in6_addr *sk_laddr = inet6_rcv_saddr(sk);
		स्थिर काष्ठा in6_addr *sk_raddr = &sk->sk_v6_daddr;
		स्थिर काष्ठा l2tp_ip6_sock *l2tp = l2tp_ip6_sk(sk);

		अगर (!net_eq(sock_net(sk), net))
			जारी;

		अगर (sk->sk_bound_dev_अगर && dअगर && sk->sk_bound_dev_अगर != dअगर)
			जारी;

		अगर (sk_laddr && !ipv6_addr_any(sk_laddr) &&
		    !ipv6_addr_any(laddr) && !ipv6_addr_equal(sk_laddr, laddr))
			जारी;

		अगर (!ipv6_addr_any(sk_raddr) && raddr &&
		    !ipv6_addr_any(raddr) && !ipv6_addr_equal(sk_raddr, raddr))
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
अटल पूर्णांक l2tp_ip6_recv(काष्ठा sk_buff *skb)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा sock *sk;
	u32 session_id;
	u32 tunnel_id;
	अचिन्हित अक्षर *ptr, *optr;
	काष्ठा l2tp_session *session;
	काष्ठा l2tp_tunnel *tunnel = शून्य;
	काष्ठा ipv6hdr *iph;

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
	iph = ipv6_hdr(skb);

	पढ़ो_lock_bh(&l2tp_ip6_lock);
	sk = __l2tp_ip6_bind_lookup(net, &iph->daddr, &iph->saddr,
				    inet6_iअगर(skb), tunnel_id);
	अगर (!sk) अणु
		पढ़ो_unlock_bh(&l2tp_ip6_lock);
		जाओ discard;
	पूर्ण
	sock_hold(sk);
	पढ़ो_unlock_bh(&l2tp_ip6_lock);

	अगर (!xfrm6_policy_check(sk, XFRM_POLICY_IN, skb))
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

अटल पूर्णांक l2tp_ip6_hash(काष्ठा sock *sk)
अणु
	अगर (sk_unhashed(sk)) अणु
		ग_लिखो_lock_bh(&l2tp_ip6_lock);
		sk_add_node(sk, &l2tp_ip6_table);
		ग_लिखो_unlock_bh(&l2tp_ip6_lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम l2tp_ip6_unhash(काष्ठा sock *sk)
अणु
	अगर (sk_unhashed(sk))
		वापस;
	ग_लिखो_lock_bh(&l2tp_ip6_lock);
	sk_del_node_init(sk);
	ग_लिखो_unlock_bh(&l2tp_ip6_lock);
पूर्ण

अटल पूर्णांक l2tp_ip6_खोलो(काष्ठा sock *sk)
अणु
	/* Prevent स्वतःbind. We करोn't have ports. */
	inet_sk(sk)->inet_num = IPPROTO_L2TP;

	l2tp_ip6_hash(sk);
	वापस 0;
पूर्ण

अटल व्योम l2tp_ip6_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	ग_लिखो_lock_bh(&l2tp_ip6_lock);
	hlist_del_init(&sk->sk_bind_node);
	sk_del_node_init(sk);
	ग_लिखो_unlock_bh(&l2tp_ip6_lock);

	sk_common_release(sk);
पूर्ण

अटल व्योम l2tp_ip6_destroy_sock(काष्ठा sock *sk)
अणु
	काष्ठा l2tp_tunnel *tunnel = l2tp_sk_to_tunnel(sk);

	lock_sock(sk);
	ip6_flush_pending_frames(sk);
	release_sock(sk);

	अगर (tunnel)
		l2tp_tunnel_delete(tunnel);

	inet6_destroy_sock(sk);
पूर्ण

अटल पूर्णांक l2tp_ip6_bind(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा sockaddr_l2tpip6 *addr = (काष्ठा sockaddr_l2tpip6 *)uaddr;
	काष्ठा net *net = sock_net(sk);
	__be32 v4addr = 0;
	पूर्णांक bound_dev_अगर;
	पूर्णांक addr_type;
	पूर्णांक err;

	अगर (addr->l2tp_family != AF_INET6)
		वापस -EINVAL;
	अगर (addr_len < माप(*addr))
		वापस -EINVAL;

	addr_type = ipv6_addr_type(&addr->l2tp_addr);

	/* l2tp_ip6 sockets are IPv6 only */
	अगर (addr_type == IPV6_ADDR_MAPPED)
		वापस -EADDRNOTAVAIL;

	/* L2TP is poपूर्णांक-poपूर्णांक, not multicast */
	अगर (addr_type & IPV6_ADDR_MULTICAST)
		वापस -EADDRNOTAVAIL;

	lock_sock(sk);

	err = -EINVAL;
	अगर (!sock_flag(sk, SOCK_ZAPPED))
		जाओ out_unlock;

	अगर (sk->sk_state != TCP_CLOSE)
		जाओ out_unlock;

	bound_dev_अगर = sk->sk_bound_dev_अगर;

	/* Check अगर the address beदीर्घs to the host. */
	rcu_पढ़ो_lock();
	अगर (addr_type != IPV6_ADDR_ANY) अणु
		काष्ठा net_device *dev = शून्य;

		अगर (addr_type & IPV6_ADDR_LINKLOCAL) अणु
			अगर (addr->l2tp_scope_id)
				bound_dev_अगर = addr->l2tp_scope_id;

			/* Binding to link-local address requires an
			 * पूर्णांकerface.
			 */
			अगर (!bound_dev_अगर)
				जाओ out_unlock_rcu;

			err = -ENODEV;
			dev = dev_get_by_index_rcu(sock_net(sk), bound_dev_अगर);
			अगर (!dev)
				जाओ out_unlock_rcu;
		पूर्ण

		/* ipv4 addr of the socket is invalid.  Only the
		 * unspecअगरied and mapped address have a v4 equivalent.
		 */
		v4addr = LOOPBACK4_IPV6;
		err = -EADDRNOTAVAIL;
		अगर (!ipv6_chk_addr(sock_net(sk), &addr->l2tp_addr, dev, 0))
			जाओ out_unlock_rcu;
	पूर्ण
	rcu_पढ़ो_unlock();

	ग_लिखो_lock_bh(&l2tp_ip6_lock);
	अगर (__l2tp_ip6_bind_lookup(net, &addr->l2tp_addr, शून्य, bound_dev_अगर,
				   addr->l2tp_conn_id)) अणु
		ग_लिखो_unlock_bh(&l2tp_ip6_lock);
		err = -EADDRINUSE;
		जाओ out_unlock;
	पूर्ण

	inet->inet_saddr = v4addr;
	inet->inet_rcv_saddr = v4addr;
	sk->sk_bound_dev_अगर = bound_dev_अगर;
	sk->sk_v6_rcv_saddr = addr->l2tp_addr;
	np->saddr = addr->l2tp_addr;

	l2tp_ip6_sk(sk)->conn_id = addr->l2tp_conn_id;

	sk_add_bind_node(sk, &l2tp_ip6_bind_table);
	sk_del_node_init(sk);
	ग_लिखो_unlock_bh(&l2tp_ip6_lock);

	sock_reset_flag(sk, SOCK_ZAPPED);
	release_sock(sk);
	वापस 0;

out_unlock_rcu:
	rcu_पढ़ो_unlock();
out_unlock:
	release_sock(sk);

	वापस err;
पूर्ण

अटल पूर्णांक l2tp_ip6_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr,
			    पूर्णांक addr_len)
अणु
	काष्ठा sockaddr_l2tpip6 *lsa = (काष्ठा sockaddr_l2tpip6 *)uaddr;
	काष्ठा sockaddr_in6	*usin = (काष्ठा sockaddr_in6 *)uaddr;
	काष्ठा in6_addr	*daddr;
	पूर्णांक	addr_type;
	पूर्णांक rc;

	अगर (addr_len < माप(*lsa))
		वापस -EINVAL;

	अगर (usin->sin6_family != AF_INET6)
		वापस -EINVAL;

	addr_type = ipv6_addr_type(&usin->sin6_addr);
	अगर (addr_type & IPV6_ADDR_MULTICAST)
		वापस -EINVAL;

	अगर (addr_type & IPV6_ADDR_MAPPED) अणु
		daddr = &usin->sin6_addr;
		अगर (ipv4_is_multicast(daddr->s6_addr32[3]))
			वापस -EINVAL;
	पूर्ण

	lock_sock(sk);

	 /* Must bind first - स्वतःbinding करोes not work */
	अगर (sock_flag(sk, SOCK_ZAPPED)) अणु
		rc = -EINVAL;
		जाओ out_sk;
	पूर्ण

	rc = __ip6_datagram_connect(sk, uaddr, addr_len);
	अगर (rc < 0)
		जाओ out_sk;

	l2tp_ip6_sk(sk)->peer_conn_id = lsa->l2tp_conn_id;

	ग_लिखो_lock_bh(&l2tp_ip6_lock);
	hlist_del_init(&sk->sk_bind_node);
	sk_add_bind_node(sk, &l2tp_ip6_bind_table);
	ग_लिखो_unlock_bh(&l2tp_ip6_lock);

out_sk:
	release_sock(sk);

	वापस rc;
पूर्ण

अटल पूर्णांक l2tp_ip6_disconnect(काष्ठा sock *sk, पूर्णांक flags)
अणु
	अगर (sock_flag(sk, SOCK_ZAPPED))
		वापस 0;

	वापस __udp_disconnect(sk, flags);
पूर्ण

अटल पूर्णांक l2tp_ip6_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			    पूर्णांक peer)
अणु
	काष्ठा sockaddr_l2tpip6 *lsa = (काष्ठा sockaddr_l2tpip6 *)uaddr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा l2tp_ip6_sock *lsk = l2tp_ip6_sk(sk);

	lsa->l2tp_family = AF_INET6;
	lsa->l2tp_flowinfo = 0;
	lsa->l2tp_scope_id = 0;
	lsa->l2tp_unused = 0;
	अगर (peer) अणु
		अगर (!lsk->peer_conn_id)
			वापस -ENOTCONN;
		lsa->l2tp_conn_id = lsk->peer_conn_id;
		lsa->l2tp_addr = sk->sk_v6_daddr;
		अगर (np->sndflow)
			lsa->l2tp_flowinfo = np->flow_label;
	पूर्ण अन्यथा अणु
		अगर (ipv6_addr_any(&sk->sk_v6_rcv_saddr))
			lsa->l2tp_addr = np->saddr;
		अन्यथा
			lsa->l2tp_addr = sk->sk_v6_rcv_saddr;

		lsa->l2tp_conn_id = lsk->conn_id;
	पूर्ण
	अगर (ipv6_addr_type(&lsa->l2tp_addr) & IPV6_ADDR_LINKLOCAL)
		lsa->l2tp_scope_id = sk->sk_bound_dev_अगर;
	वापस माप(*lsa);
पूर्ण

अटल पूर्णांक l2tp_ip6_backlog_recv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
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
	वापस -1;
पूर्ण

अटल पूर्णांक l2tp_ip6_push_pending_frames(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb;
	__be32 *transhdr = शून्य;
	पूर्णांक err = 0;

	skb = skb_peek(&sk->sk_ग_लिखो_queue);
	अगर (!skb)
		जाओ out;

	transhdr = (__be32 *)skb_transport_header(skb);
	*transhdr = 0;

	err = ip6_push_pending_frames(sk);

out:
	वापस err;
पूर्ण

/* Userspace will call sendmsg() on the tunnel socket to send L2TP
 * control frames.
 */
अटल पूर्णांक l2tp_ip6_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा ipv6_txoptions opt_space;
	DECLARE_SOCKADDR(काष्ठा sockaddr_l2tpip6 *, lsa, msg->msg_name);
	काष्ठा in6_addr *daddr, *final_p, final;
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा ipv6_txoptions *opt_to_मुक्त = शून्य;
	काष्ठा ipv6_txoptions *opt = शून्य;
	काष्ठा ip6_flowlabel *flowlabel = शून्य;
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा flowi6 fl6;
	काष्ठा ipcm6_cookie ipc6;
	पूर्णांक addr_len = msg->msg_namelen;
	पूर्णांक transhdrlen = 4; /* zero session-id */
	पूर्णांक ulen = len + transhdrlen;
	पूर्णांक err;

	/* Rough check on arithmetic overflow,
	 * better check is made in ip6_append_data().
	 */
	अगर (len > पूर्णांक_उच्च)
		वापस -EMSGSIZE;

	/* Mirror BSD error message compatibility */
	अगर (msg->msg_flags & MSG_OOB)
		वापस -EOPNOTSUPP;

	/* Get and verअगरy the address */
	स_रखो(&fl6, 0, माप(fl6));

	fl6.flowi6_mark = sk->sk_mark;
	fl6.flowi6_uid = sk->sk_uid;

	ipcm6_init(&ipc6);

	अगर (lsa) अणु
		अगर (addr_len < SIN6_LEN_RFC2133)
			वापस -EINVAL;

		अगर (lsa->l2tp_family && lsa->l2tp_family != AF_INET6)
			वापस -EAFNOSUPPORT;

		daddr = &lsa->l2tp_addr;
		अगर (np->sndflow) अणु
			fl6.flowlabel = lsa->l2tp_flowinfo & IPV6_FLOWINFO_MASK;
			अगर (fl6.flowlabel & IPV6_FLOWLABEL_MASK) अणु
				flowlabel = fl6_sock_lookup(sk, fl6.flowlabel);
				अगर (IS_ERR(flowlabel))
					वापस -EINVAL;
			पूर्ण
		पूर्ण

		/* Otherwise it will be dअगरficult to मुख्यtain
		 * sk->sk_dst_cache.
		 */
		अगर (sk->sk_state == TCP_ESTABLISHED &&
		    ipv6_addr_equal(daddr, &sk->sk_v6_daddr))
			daddr = &sk->sk_v6_daddr;

		अगर (addr_len >= माप(काष्ठा sockaddr_in6) &&
		    lsa->l2tp_scope_id &&
		    ipv6_addr_type(daddr) & IPV6_ADDR_LINKLOCAL)
			fl6.flowi6_oअगर = lsa->l2tp_scope_id;
	पूर्ण अन्यथा अणु
		अगर (sk->sk_state != TCP_ESTABLISHED)
			वापस -EDESTADDRREQ;

		daddr = &sk->sk_v6_daddr;
		fl6.flowlabel = np->flow_label;
	पूर्ण

	अगर (fl6.flowi6_oअगर == 0)
		fl6.flowi6_oअगर = sk->sk_bound_dev_अगर;

	अगर (msg->msg_controllen) अणु
		opt = &opt_space;
		स_रखो(opt, 0, माप(काष्ठा ipv6_txoptions));
		opt->tot_len = माप(काष्ठा ipv6_txoptions);
		ipc6.opt = opt;

		err = ip6_datagram_send_ctl(sock_net(sk), sk, msg, &fl6, &ipc6);
		अगर (err < 0) अणु
			fl6_sock_release(flowlabel);
			वापस err;
		पूर्ण
		अगर ((fl6.flowlabel & IPV6_FLOWLABEL_MASK) && !flowlabel) अणु
			flowlabel = fl6_sock_lookup(sk, fl6.flowlabel);
			अगर (IS_ERR(flowlabel))
				वापस -EINVAL;
		पूर्ण
		अगर (!(opt->opt_nflen | opt->opt_flen))
			opt = शून्य;
	पूर्ण

	अगर (!opt) अणु
		opt = txopt_get(np);
		opt_to_मुक्त = opt;
	पूर्ण
	अगर (flowlabel)
		opt = fl6_merge_options(&opt_space, flowlabel, opt);
	opt = ipv6_fixup_options(&opt_space, opt);
	ipc6.opt = opt;

	fl6.flowi6_proto = sk->sk_protocol;
	अगर (!ipv6_addr_any(daddr))
		fl6.daddr = *daddr;
	अन्यथा
		fl6.daddr.s6_addr[15] = 0x1; /* :: means loopback (BSD'ism) */
	अगर (ipv6_addr_any(&fl6.saddr) && !ipv6_addr_any(&np->saddr))
		fl6.saddr = np->saddr;

	final_p = fl6_update_dst(&fl6, opt, &final);

	अगर (!fl6.flowi6_oअगर && ipv6_addr_is_multicast(&fl6.daddr))
		fl6.flowi6_oअगर = np->mcast_oअगर;
	अन्यथा अगर (!fl6.flowi6_oअगर)
		fl6.flowi6_oअगर = np->ucast_oअगर;

	security_sk_classअगरy_flow(sk, flowi6_to_flowi_common(&fl6));

	अगर (ipc6.tclass < 0)
		ipc6.tclass = np->tclass;

	fl6.flowlabel = ip6_make_flowinfo(ipc6.tclass, fl6.flowlabel);

	dst = ip6_dst_lookup_flow(sock_net(sk), sk, &fl6, final_p);
	अगर (IS_ERR(dst)) अणु
		err = PTR_ERR(dst);
		जाओ out;
	पूर्ण

	अगर (ipc6.hlimit < 0)
		ipc6.hlimit = ip6_sk_dst_hoplimit(np, &fl6, dst);

	अगर (ipc6.करोntfrag < 0)
		ipc6.करोntfrag = np->करोntfrag;

	अगर (msg->msg_flags & MSG_CONFIRM)
		जाओ करो_confirm;

back_from_confirm:
	lock_sock(sk);
	err = ip6_append_data(sk, ip_generic_getfrag, msg,
			      ulen, transhdrlen, &ipc6,
			      &fl6, (काष्ठा rt6_info *)dst,
			      msg->msg_flags);
	अगर (err)
		ip6_flush_pending_frames(sk);
	अन्यथा अगर (!(msg->msg_flags & MSG_MORE))
		err = l2tp_ip6_push_pending_frames(sk);
	release_sock(sk);
करोne:
	dst_release(dst);
out:
	fl6_sock_release(flowlabel);
	txopt_put(opt_to_मुक्त);

	वापस err < 0 ? err : len;

करो_confirm:
	अगर (msg->msg_flags & MSG_PROBE)
		dst_confirm_neigh(dst, &fl6.daddr);
	अगर (!(msg->msg_flags & MSG_PROBE) || len)
		जाओ back_from_confirm;
	err = 0;
	जाओ करोne;
पूर्ण

अटल पूर्णांक l2tp_ip6_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len,
			    पूर्णांक noblock, पूर्णांक flags, पूर्णांक *addr_len)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	DECLARE_SOCKADDR(काष्ठा sockaddr_l2tpip6 *, lsa, msg->msg_name);
	माप_प्रकार copied = 0;
	पूर्णांक err = -EOPNOTSUPP;
	काष्ठा sk_buff *skb;

	अगर (flags & MSG_OOB)
		जाओ out;

	अगर (flags & MSG_ERRQUEUE)
		वापस ipv6_recv_error(sk, msg, len, addr_len);

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
	अगर (lsa) अणु
		lsa->l2tp_family = AF_INET6;
		lsa->l2tp_unused = 0;
		lsa->l2tp_addr = ipv6_hdr(skb)->saddr;
		lsa->l2tp_flowinfo = 0;
		lsa->l2tp_scope_id = 0;
		lsa->l2tp_conn_id = 0;
		अगर (ipv6_addr_type(&lsa->l2tp_addr) & IPV6_ADDR_LINKLOCAL)
			lsa->l2tp_scope_id = inet6_iअगर(skb);
		*addr_len = माप(*lsa);
	पूर्ण

	अगर (np->rxopt.all)
		ip6_datagram_recv_ctl(sk, msg, skb);

	अगर (flags & MSG_TRUNC)
		copied = skb->len;
करोne:
	skb_मुक्त_datagram(sk, skb);
out:
	वापस err ? err : copied;
पूर्ण

अटल काष्ठा proto l2tp_ip6_prot = अणु
	.name		   = "L2TP/IPv6",
	.owner		   = THIS_MODULE,
	.init		   = l2tp_ip6_खोलो,
	.बंद		   = l2tp_ip6_बंद,
	.bind		   = l2tp_ip6_bind,
	.connect	   = l2tp_ip6_connect,
	.disconnect	   = l2tp_ip6_disconnect,
	.ioctl		   = l2tp_ioctl,
	.destroy	   = l2tp_ip6_destroy_sock,
	.setsockopt	   = ipv6_setsockopt,
	.माला_लोockopt	   = ipv6_माला_लोockopt,
	.sendmsg	   = l2tp_ip6_sendmsg,
	.recvmsg	   = l2tp_ip6_recvmsg,
	.backlog_rcv	   = l2tp_ip6_backlog_recv,
	.hash		   = l2tp_ip6_hash,
	.unhash		   = l2tp_ip6_unhash,
	.obj_size	   = माप(काष्ठा l2tp_ip6_sock),
पूर्ण;

अटल स्थिर काष्ठा proto_ops l2tp_ip6_ops = अणु
	.family		   = PF_INET6,
	.owner		   = THIS_MODULE,
	.release	   = inet6_release,
	.bind		   = inet6_bind,
	.connect	   = inet_dgram_connect,
	.socketpair	   = sock_no_socketpair,
	.accept		   = sock_no_accept,
	.getname	   = l2tp_ip6_getname,
	.poll		   = datagram_poll,
	.ioctl		   = inet6_ioctl,
	.gettstamp	   = sock_gettstamp,
	.listen		   = sock_no_listen,
	.shutकरोwn	   = inet_shutकरोwn,
	.setsockopt	   = sock_common_setsockopt,
	.माला_लोockopt	   = sock_common_माला_लोockopt,
	.sendmsg	   = inet_sendmsg,
	.recvmsg	   = sock_common_recvmsg,
	.mmap		   = sock_no_mmap,
	.sendpage	   = sock_no_sendpage,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	   = inet6_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा inet_protosw l2tp_ip6_protosw = अणु
	.type		= SOCK_DGRAM,
	.protocol	= IPPROTO_L2TP,
	.prot		= &l2tp_ip6_prot,
	.ops		= &l2tp_ip6_ops,
पूर्ण;

अटल काष्ठा inet6_protocol l2tp_ip6_protocol __पढ़ो_mostly = अणु
	.handler	= l2tp_ip6_recv,
पूर्ण;

अटल पूर्णांक __init l2tp_ip6_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("L2TP IP encapsulation support for IPv6 (L2TPv3)\n");

	err = proto_रेजिस्टर(&l2tp_ip6_prot, 1);
	अगर (err != 0)
		जाओ out;

	err = inet6_add_protocol(&l2tp_ip6_protocol, IPPROTO_L2TP);
	अगर (err)
		जाओ out1;

	inet6_रेजिस्टर_protosw(&l2tp_ip6_protosw);
	वापस 0;

out1:
	proto_unरेजिस्टर(&l2tp_ip6_prot);
out:
	वापस err;
पूर्ण

अटल व्योम __निकास l2tp_ip6_निकास(व्योम)
अणु
	inet6_unरेजिस्टर_protosw(&l2tp_ip6_protosw);
	inet6_del_protocol(&l2tp_ip6_protocol, IPPROTO_L2TP);
	proto_unरेजिस्टर(&l2tp_ip6_prot);
पूर्ण

module_init(l2tp_ip6_init);
module_निकास(l2tp_ip6_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chris Elston <celston@katalix.com>");
MODULE_DESCRIPTION("L2TP IP encapsulation for IPv6");
MODULE_VERSION("1.0");

/* Use the value of SOCK_DGRAM (2) directory, because __stringअगरy करोesn't like
 * क्रमागतs
 */
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_INET6, 2, IPPROTO_L2TP);
MODULE_ALIAS_NET_PF_PROTO(PF_INET6, IPPROTO_L2TP);
