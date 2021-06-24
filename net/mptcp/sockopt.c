<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Multipath TCP
 *
 * Copyright (c) 2021, Red Hat.
 */

#घोषणा pr_fmt(fmt) "MPTCP: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <net/sock.h>
#समावेश <net/protocol.h>
#समावेश <net/tcp.h>
#समावेश <net/mptcp.h>
#समावेश "protocol.h"

अटल काष्ठा sock *__mptcp_tcp_fallback(काष्ठा mptcp_sock *msk)
अणु
	sock_owned_by_me((स्थिर काष्ठा sock *)msk);

	अगर (likely(!__mptcp_check_fallback(msk)))
		वापस शून्य;

	वापस msk->first;
पूर्ण

अटल u32 sockopt_seq_reset(स्थिर काष्ठा sock *sk)
अणु
	sock_owned_by_me(sk);

	/* Highbits contain state.  Allows to distinguish sockopt_seq
	 * of listener and established:
	 * s0 = new_listener()
	 * sockopt(s0) - seq is 1
	 * s1 = accept(s0) - s1 inherits seq 1 अगर listener sk (s0)
	 * sockopt(s0) - seq increments to 2 on s0
	 * sockopt(s1) // seq increments to 2 on s1 (dअगरferent option)
	 * new ssk completes join, inherits options from s0 // seq 2
	 * Needs sync from mptcp join logic, but ssk->seq == msk->seq
	 *
	 * Set High order bits to sk_state so ssk->seq == msk->seq test
	 * will fail.
	 */

	वापस (u32)sk->sk_state << 24u;
पूर्ण

अटल व्योम sockopt_seq_inc(काष्ठा mptcp_sock *msk)
अणु
	u32 seq = (msk->setsockopt_seq + 1) & 0x00ffffff;

	msk->setsockopt_seq = sockopt_seq_reset((काष्ठा sock *)msk) + seq;
पूर्ण

अटल पूर्णांक mptcp_get_पूर्णांक_option(काष्ठा mptcp_sock *msk, sockptr_t optval,
				अचिन्हित पूर्णांक optlen, पूर्णांक *val)
अणु
	अगर (optlen < माप(पूर्णांक))
		वापस -EINVAL;

	अगर (copy_from_sockptr(val, optval, माप(*val)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल व्योम mptcp_sol_socket_sync_पूर्णांकval(काष्ठा mptcp_sock *msk, पूर्णांक optname, पूर्णांक val)
अणु
	काष्ठा mptcp_subflow_context *subflow;
	काष्ठा sock *sk = (काष्ठा sock *)msk;

	lock_sock(sk);
	sockopt_seq_inc(msk);

	mptcp_क्रम_each_subflow(msk, subflow) अणु
		काष्ठा sock *ssk = mptcp_subflow_tcp_sock(subflow);
		bool slow = lock_sock_fast(ssk);

		चयन (optname) अणु
		हाल SO_DEBUG:
			sock_valbool_flag(ssk, SOCK_DBG, !!val);
			अवरोध;
		हाल SO_KEEPALIVE:
			अगर (ssk->sk_prot->keepalive)
				ssk->sk_prot->keepalive(ssk, !!val);
			sock_valbool_flag(ssk, SOCK_KEEPOPEN, !!val);
			अवरोध;
		हाल SO_PRIORITY:
			ssk->sk_priority = val;
			अवरोध;
		हाल SO_SNDBUF:
		हाल SO_SNDBUFFORCE:
			ssk->sk_userlocks |= SOCK_SNDBUF_LOCK;
			WRITE_ONCE(ssk->sk_sndbuf, sk->sk_sndbuf);
			अवरोध;
		हाल SO_RCVBUF:
		हाल SO_RCVBUFFORCE:
			ssk->sk_userlocks |= SOCK_RCVBUF_LOCK;
			WRITE_ONCE(ssk->sk_rcvbuf, sk->sk_rcvbuf);
			अवरोध;
		हाल SO_MARK:
			अगर (READ_ONCE(ssk->sk_mark) != sk->sk_mark) अणु
				ssk->sk_mark = sk->sk_mark;
				sk_dst_reset(ssk);
			पूर्ण
			अवरोध;
		हाल SO_INCOMING_CPU:
			WRITE_ONCE(ssk->sk_incoming_cpu, val);
			अवरोध;
		पूर्ण

		subflow->setsockopt_seq = msk->setsockopt_seq;
		unlock_sock_fast(ssk, slow);
	पूर्ण

	release_sock(sk);
पूर्ण

अटल पूर्णांक mptcp_sol_socket_पूर्णांकval(काष्ठा mptcp_sock *msk, पूर्णांक optname, पूर्णांक val)
अणु
	sockptr_t optval = KERNEL_SOCKPTR(&val);
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	पूर्णांक ret;

	ret = sock_setsockopt(sk->sk_socket, SOL_SOCKET, optname,
			      optval, माप(val));
	अगर (ret)
		वापस ret;

	mptcp_sol_socket_sync_पूर्णांकval(msk, optname, val);
	वापस 0;
पूर्ण

अटल व्योम mptcp_so_incoming_cpu(काष्ठा mptcp_sock *msk, पूर्णांक val)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)msk;

	WRITE_ONCE(sk->sk_incoming_cpu, val);

	mptcp_sol_socket_sync_पूर्णांकval(msk, SO_INCOMING_CPU, val);
पूर्ण

अटल पूर्णांक mptcp_setsockopt_sol_socket_पूर्णांक(काष्ठा mptcp_sock *msk, पूर्णांक optname,
					   sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	पूर्णांक val, ret;

	ret = mptcp_get_पूर्णांक_option(msk, optval, optlen, &val);
	अगर (ret)
		वापस ret;

	चयन (optname) अणु
	हाल SO_KEEPALIVE:
		mptcp_sol_socket_sync_पूर्णांकval(msk, optname, val);
		वापस 0;
	हाल SO_DEBUG:
	हाल SO_MARK:
	हाल SO_PRIORITY:
	हाल SO_SNDBUF:
	हाल SO_SNDBUFFORCE:
	हाल SO_RCVBUF:
	हाल SO_RCVBUFFORCE:
		वापस mptcp_sol_socket_पूर्णांकval(msk, optname, val);
	हाल SO_INCOMING_CPU:
		mptcp_so_incoming_cpu(msk, val);
		वापस 0;
	पूर्ण

	वापस -ENOPROTOOPT;
पूर्ण

अटल पूर्णांक mptcp_setsockopt_sol_socket_linger(काष्ठा mptcp_sock *msk, sockptr_t optval,
					      अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा mptcp_subflow_context *subflow;
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	काष्ठा linger ling;
	sockptr_t kopt;
	पूर्णांक ret;

	अगर (optlen < माप(ling))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&ling, optval, माप(ling)))
		वापस -EFAULT;

	kopt = KERNEL_SOCKPTR(&ling);
	ret = sock_setsockopt(sk->sk_socket, SOL_SOCKET, SO_LINGER, kopt, माप(ling));
	अगर (ret)
		वापस ret;

	lock_sock(sk);
	sockopt_seq_inc(msk);
	mptcp_क्रम_each_subflow(msk, subflow) अणु
		काष्ठा sock *ssk = mptcp_subflow_tcp_sock(subflow);
		bool slow = lock_sock_fast(ssk);

		अगर (!ling.l_onoff) अणु
			sock_reset_flag(ssk, SOCK_LINGER);
		पूर्ण अन्यथा अणु
			ssk->sk_lingerसमय = sk->sk_lingerसमय;
			sock_set_flag(ssk, SOCK_LINGER);
		पूर्ण

		subflow->setsockopt_seq = msk->setsockopt_seq;
		unlock_sock_fast(ssk, slow);
	पूर्ण

	release_sock(sk);
	वापस 0;
पूर्ण

अटल पूर्णांक mptcp_setsockopt_sol_socket(काष्ठा mptcp_sock *msk, पूर्णांक optname,
				       sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	काष्ठा socket *ssock;
	पूर्णांक ret;

	चयन (optname) अणु
	हाल SO_REUSEPORT:
	हाल SO_REUSEADDR:
	हाल SO_BINDTODEVICE:
	हाल SO_BINDTOIFINDEX:
		lock_sock(sk);
		ssock = __mptcp_nmpc_socket(msk);
		अगर (!ssock) अणु
			release_sock(sk);
			वापस -EINVAL;
		पूर्ण

		ret = sock_setsockopt(ssock, SOL_SOCKET, optname, optval, optlen);
		अगर (ret == 0) अणु
			अगर (optname == SO_REUSEPORT)
				sk->sk_reuseport = ssock->sk->sk_reuseport;
			अन्यथा अगर (optname == SO_REUSEADDR)
				sk->sk_reuse = ssock->sk->sk_reuse;
			अन्यथा अगर (optname == SO_BINDTODEVICE)
				sk->sk_bound_dev_अगर = ssock->sk->sk_bound_dev_अगर;
			अन्यथा अगर (optname == SO_BINDTOIFINDEX)
				sk->sk_bound_dev_अगर = ssock->sk->sk_bound_dev_अगर;
		पूर्ण
		release_sock(sk);
		वापस ret;
	हाल SO_KEEPALIVE:
	हाल SO_PRIORITY:
	हाल SO_SNDBUF:
	हाल SO_SNDBUFFORCE:
	हाल SO_RCVBUF:
	हाल SO_RCVBUFFORCE:
	हाल SO_MARK:
	हाल SO_INCOMING_CPU:
	हाल SO_DEBUG:
		वापस mptcp_setsockopt_sol_socket_पूर्णांक(msk, optname, optval, optlen);
	हाल SO_LINGER:
		वापस mptcp_setsockopt_sol_socket_linger(msk, optval, optlen);
	हाल SO_NO_CHECK:
	हाल SO_DONTROUTE:
	हाल SO_BROADCAST:
	हाल SO_BSDCOMPAT:
	हाल SO_PASSCRED:
	हाल SO_PASSSEC:
	हाल SO_RXQ_OVFL:
	हाल SO_WIFI_STATUS:
	हाल SO_NOFCS:
	हाल SO_SELECT_ERR_QUEUE:
		वापस 0;
	पूर्ण

	वापस sock_setsockopt(sk->sk_socket, SOL_SOCKET, optname, optval, optlen);
पूर्ण

अटल पूर्णांक mptcp_setsockopt_v6(काष्ठा mptcp_sock *msk, पूर्णांक optname,
			       sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	पूर्णांक ret = -EOPNOTSUPP;
	काष्ठा socket *ssock;

	चयन (optname) अणु
	हाल IPV6_V6ONLY:
		lock_sock(sk);
		ssock = __mptcp_nmpc_socket(msk);
		अगर (!ssock) अणु
			release_sock(sk);
			वापस -EINVAL;
		पूर्ण

		ret = tcp_setsockopt(ssock->sk, SOL_IPV6, optname, optval, optlen);
		अगर (ret == 0)
			sk->sk_ipv6only = ssock->sk->sk_ipv6only;

		release_sock(sk);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool mptcp_supported_sockopt(पूर्णांक level, पूर्णांक optname)
अणु
	अगर (level == SOL_SOCKET) अणु
		चयन (optname) अणु
		हाल SO_DEBUG:
		हाल SO_REUSEPORT:
		हाल SO_REUSEADDR:

		/* the following ones need a better implementation,
		 * but are quite common we want to preserve them
		 */
		हाल SO_BINDTODEVICE:
		हाल SO_SNDBUF:
		हाल SO_SNDBUFFORCE:
		हाल SO_RCVBUF:
		हाल SO_RCVBUFFORCE:
		हाल SO_KEEPALIVE:
		हाल SO_PRIORITY:
		हाल SO_LINGER:
		हाल SO_TIMESTAMP_OLD:
		हाल SO_TIMESTAMP_NEW:
		हाल SO_TIMESTAMPNS_OLD:
		हाल SO_TIMESTAMPNS_NEW:
		हाल SO_TIMESTAMPING_OLD:
		हाल SO_TIMESTAMPING_NEW:
		हाल SO_RCVLOWAT:
		हाल SO_RCVTIMEO_OLD:
		हाल SO_RCVTIMEO_NEW:
		हाल SO_SNDTIMEO_OLD:
		हाल SO_SNDTIMEO_NEW:
		हाल SO_MARK:
		हाल SO_INCOMING_CPU:
		हाल SO_BINDTOIFINDEX:
		हाल SO_BUSY_POLL:
		हाल SO_PREFER_BUSY_POLL:
		हाल SO_BUSY_POLL_BUDGET:

		/* next ones are no-op क्रम plain TCP */
		हाल SO_NO_CHECK:
		हाल SO_DONTROUTE:
		हाल SO_BROADCAST:
		हाल SO_BSDCOMPAT:
		हाल SO_PASSCRED:
		हाल SO_PASSSEC:
		हाल SO_RXQ_OVFL:
		हाल SO_WIFI_STATUS:
		हाल SO_NOFCS:
		हाल SO_SELECT_ERR_QUEUE:
			वापस true;
		पूर्ण

		/* SO_OOBINLINE is not supported, let's aव्योम the related mess */
		/* SO_ATTACH_FILTER, SO_ATTACH_BPF, SO_ATTACH_REUSEPORT_CBPF,
		 * SO_DETACH_REUSEPORT_BPF, SO_DETACH_FILTER, SO_LOCK_FILTER,
		 * we must be careful with subflows
		 */
		/* SO_ATTACH_REUSEPORT_EBPF is not supported, at it checks
		 * explicitly the sk_protocol field
		 */
		/* SO_PEEK_OFF is unsupported, as it is क्रम plain TCP */
		/* SO_MAX_PACING_RATE is unsupported, we must be careful with subflows */
		/* SO_CNX_ADVICE is currently unsupported, could possibly be relevant,
		 * but likely needs careful design
		 */
		/* SO_ZEROCOPY is currently unsupported, TODO in sndmsg */
		/* SO_TXTIME is currently unsupported */
		वापस false;
	पूर्ण
	अगर (level == SOL_IP) अणु
		चयन (optname) अणु
		/* should work fine */
		हाल IP_FREEBIND:
		हाल IP_TRANSPARENT:

		/* the following are control cmsg related */
		हाल IP_PKTINFO:
		हाल IP_RECVTTL:
		हाल IP_RECVTOS:
		हाल IP_RECVOPTS:
		हाल IP_RETOPTS:
		हाल IP_PASSSEC:
		हाल IP_RECVORIGDSTADDR:
		हाल IP_CHECKSUM:
		हाल IP_RECVFRAGSIZE:

		/* common stuff that need some love */
		हाल IP_TOS:
		हाल IP_TTL:
		हाल IP_BIND_ADDRESS_NO_PORT:
		हाल IP_MTU_DISCOVER:
		हाल IP_RECVERR:

		/* possibly less common may deserve some love */
		हाल IP_MINTTL:

		/* the following is apparently a no-op क्रम plain TCP */
		हाल IP_RECVERR_RFC4884:
			वापस true;
		पूर्ण

		/* IP_OPTIONS is not supported, needs subflow care */
		/* IP_HDRINCL, IP_NODEFRAG are not supported, RAW specअगरic */
		/* IP_MULTICAST_TTL, IP_MULTICAST_LOOP, IP_UNICAST_IF,
		 * IP_ADD_MEMBERSHIP, IP_ADD_SOURCE_MEMBERSHIP, IP_DROP_MEMBERSHIP,
		 * IP_DROP_SOURCE_MEMBERSHIP, IP_BLOCK_SOURCE, IP_UNBLOCK_SOURCE,
		 * MCAST_JOIN_GROUP, MCAST_LEAVE_GROUP MCAST_JOIN_SOURCE_GROUP,
		 * MCAST_LEAVE_SOURCE_GROUP, MCAST_BLOCK_SOURCE, MCAST_UNBLOCK_SOURCE,
		 * MCAST_MSFILTER, IP_MULTICAST_ALL are not supported, better not deal
		 * with mcast stuff
		 */
		/* IP_IPSEC_POLICY, IP_XFRM_POLICY are nut supported, unrelated here */
		वापस false;
	पूर्ण
	अगर (level == SOL_IPV6) अणु
		चयन (optname) अणु
		हाल IPV6_V6ONLY:

		/* the following are control cmsg related */
		हाल IPV6_RECVPKTINFO:
		हाल IPV6_2292PKTINFO:
		हाल IPV6_RECVHOPLIMIT:
		हाल IPV6_2292HOPLIMIT:
		हाल IPV6_RECVRTHDR:
		हाल IPV6_2292RTHDR:
		हाल IPV6_RECVHOPOPTS:
		हाल IPV6_2292HOPOPTS:
		हाल IPV6_RECVDSTOPTS:
		हाल IPV6_2292DSTOPTS:
		हाल IPV6_RECVTCLASS:
		हाल IPV6_FLOWINFO:
		हाल IPV6_RECVPATHMTU:
		हाल IPV6_RECVORIGDSTADDR:
		हाल IPV6_RECVFRAGSIZE:

		/* the following ones need some love but are quite common */
		हाल IPV6_TCLASS:
		हाल IPV6_TRANSPARENT:
		हाल IPV6_FREEBIND:
		हाल IPV6_PKTINFO:
		हाल IPV6_2292PKTOPTIONS:
		हाल IPV6_UNICAST_HOPS:
		हाल IPV6_MTU_DISCOVER:
		हाल IPV6_MTU:
		हाल IPV6_RECVERR:
		हाल IPV6_FLOWINFO_SEND:
		हाल IPV6_FLOWLABEL_MGR:
		हाल IPV6_MINHOPCOUNT:
		हाल IPV6_DONTFRAG:
		हाल IPV6_AUTOFLOWLABEL:

		/* the following one is a no-op क्रम plain TCP */
		हाल IPV6_RECVERR_RFC4884:
			वापस true;
		पूर्ण

		/* IPV6_HOPOPTS, IPV6_RTHDRDSTOPTS, IPV6_RTHDR, IPV6_DSTOPTS are
		 * not supported
		 */
		/* IPV6_MULTICAST_HOPS, IPV6_MULTICAST_LOOP, IPV6_UNICAST_IF,
		 * IPV6_MULTICAST_IF, IPV6_ADDRFORM,
		 * IPV6_ADD_MEMBERSHIP, IPV6_DROP_MEMBERSHIP, IPV6_JOIN_ANYCAST,
		 * IPV6_LEAVE_ANYCAST, IPV6_MULTICAST_ALL, MCAST_JOIN_GROUP, MCAST_LEAVE_GROUP,
		 * MCAST_JOIN_SOURCE_GROUP, MCAST_LEAVE_SOURCE_GROUP,
		 * MCAST_BLOCK_SOURCE, MCAST_UNBLOCK_SOURCE, MCAST_MSFILTER
		 * are not supported better not deal with mcast
		 */
		/* IPV6_ROUTER_ALERT, IPV6_ROUTER_ALERT_ISOLATE are not supported, since are evil */

		/* IPV6_IPSEC_POLICY, IPV6_XFRM_POLICY are not supported */
		/* IPV6_ADDR_PREFERENCES is not supported, we must be careful with subflows */
		वापस false;
	पूर्ण
	अगर (level == SOL_TCP) अणु
		चयन (optname) अणु
		/* the following are no-op or should work just fine */
		हाल TCP_THIN_DUPACK:
		हाल TCP_DEFER_ACCEPT:

		/* the following need some love */
		हाल TCP_MAXSEG:
		हाल TCP_NODELAY:
		हाल TCP_THIN_LINEAR_TIMEOUTS:
		हाल TCP_CONGESTION:
		हाल TCP_ULP:
		हाल TCP_CORK:
		हाल TCP_KEEPIDLE:
		हाल TCP_KEEPINTVL:
		हाल TCP_KEEPCNT:
		हाल TCP_SYNCNT:
		हाल TCP_SAVE_SYN:
		हाल TCP_LINGER2:
		हाल TCP_WINDOW_CLAMP:
		हाल TCP_QUICKACK:
		हाल TCP_USER_TIMEOUT:
		हाल TCP_TIMESTAMP:
		हाल TCP_NOTSENT_LOWAT:
		हाल TCP_TX_DELAY:
			वापस true;
		पूर्ण

		/* TCP_MD5SIG, TCP_MD5SIG_EXT are not supported, MD5 is not compatible with MPTCP */

		/* TCP_REPAIR, TCP_REPAIR_QUEUE, TCP_QUEUE_SEQ, TCP_REPAIR_OPTIONS,
		 * TCP_REPAIR_WINDOW are not supported, better aव्योम this mess
		 */
		/* TCP_FASTOPEN_KEY, TCP_FASTOPEN TCP_FASTOPEN_CONNECT, TCP_FASTOPEN_NO_COOKIE,
		 * are not supported fastखोलो is currently unsupported
		 */
		/* TCP_INQ is currently unsupported, needs some recvmsg work */
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक mptcp_setsockopt_sol_tcp_congestion(काष्ठा mptcp_sock *msk, sockptr_t optval,
					       अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा mptcp_subflow_context *subflow;
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	अक्षर name[TCP_CA_NAME_MAX];
	bool cap_net_admin;
	पूर्णांक ret;

	अगर (optlen < 1)
		वापस -EINVAL;

	ret = म_नकलन_from_sockptr(name, optval,
				   min_t(दीर्घ, TCP_CA_NAME_MAX - 1, optlen));
	अगर (ret < 0)
		वापस -EFAULT;

	name[ret] = 0;

	cap_net_admin = ns_capable(sock_net(sk)->user_ns, CAP_NET_ADMIN);

	ret = 0;
	lock_sock(sk);
	sockopt_seq_inc(msk);
	mptcp_क्रम_each_subflow(msk, subflow) अणु
		काष्ठा sock *ssk = mptcp_subflow_tcp_sock(subflow);
		पूर्णांक err;

		lock_sock(ssk);
		err = tcp_set_congestion_control(ssk, name, true, cap_net_admin);
		अगर (err < 0 && ret == 0)
			ret = err;
		subflow->setsockopt_seq = msk->setsockopt_seq;
		release_sock(ssk);
	पूर्ण

	अगर (ret == 0)
		म_नकल(msk->ca_name, name);

	release_sock(sk);
	वापस ret;
पूर्ण

अटल पूर्णांक mptcp_setsockopt_sol_tcp(काष्ठा mptcp_sock *msk, पूर्णांक optname,
				    sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	चयन (optname) अणु
	हाल TCP_ULP:
		वापस -EOPNOTSUPP;
	हाल TCP_CONGESTION:
		वापस mptcp_setsockopt_sol_tcp_congestion(msk, optval, optlen);
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक mptcp_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		     sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	काष्ठा sock *ssk;

	pr_debug("msk=%p", msk);

	अगर (!mptcp_supported_sockopt(level, optname))
		वापस -ENOPROTOOPT;

	अगर (level == SOL_SOCKET)
		वापस mptcp_setsockopt_sol_socket(msk, optname, optval, optlen);

	/* @@ the meaning of setsockopt() when the socket is connected and
	 * there are multiple subflows is not yet defined. It is up to the
	 * MPTCP-level socket to configure the subflows until the subflow
	 * is in TCP fallback, when TCP socket options are passed through
	 * to the one reमुख्यing subflow.
	 */
	lock_sock(sk);
	ssk = __mptcp_tcp_fallback(msk);
	release_sock(sk);
	अगर (ssk)
		वापस tcp_setsockopt(ssk, level, optname, optval, optlen);

	अगर (level == SOL_IPV6)
		वापस mptcp_setsockopt_v6(msk, optname, optval, optlen);

	अगर (level == SOL_TCP)
		वापस mptcp_setsockopt_sol_tcp(msk, optname, optval, optlen);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक mptcp_माला_लोockopt_first_sf_only(काष्ठा mptcp_sock *msk, पूर्णांक level, पूर्णांक optname,
					  अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	काष्ठा socket *ssock;
	पूर्णांक ret = -EINVAL;
	काष्ठा sock *ssk;

	lock_sock(sk);
	ssk = msk->first;
	अगर (ssk) अणु
		ret = tcp_माला_लोockopt(ssk, level, optname, optval, optlen);
		जाओ out;
	पूर्ण

	ssock = __mptcp_nmpc_socket(msk);
	अगर (!ssock)
		जाओ out;

	ret = tcp_माला_लोockopt(ssock->sk, level, optname, optval, optlen);

out:
	release_sock(sk);
	वापस ret;
पूर्ण

अटल पूर्णांक mptcp_माला_लोockopt_sol_tcp(काष्ठा mptcp_sock *msk, पूर्णांक optname,
				    अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	चयन (optname) अणु
	हाल TCP_ULP:
	हाल TCP_CONGESTION:
	हाल TCP_INFO:
	हाल TCP_CC_INFO:
		वापस mptcp_माला_लोockopt_first_sf_only(msk, SOL_TCP, optname,
						      optval, optlen);
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक mptcp_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		     अक्षर __user *optval, पूर्णांक __user *option)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	काष्ठा sock *ssk;

	pr_debug("msk=%p", msk);

	/* @@ the meaning of setsockopt() when the socket is connected and
	 * there are multiple subflows is not yet defined. It is up to the
	 * MPTCP-level socket to configure the subflows until the subflow
	 * is in TCP fallback, when socket options are passed through
	 * to the one reमुख्यing subflow.
	 */
	lock_sock(sk);
	ssk = __mptcp_tcp_fallback(msk);
	release_sock(sk);
	अगर (ssk)
		वापस tcp_माला_लोockopt(ssk, level, optname, optval, option);

	अगर (level == SOL_TCP)
		वापस mptcp_माला_लोockopt_sol_tcp(msk, optname, optval, option);
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम sync_socket_options(काष्ठा mptcp_sock *msk, काष्ठा sock *ssk)
अणु
	अटल स्थिर अचिन्हित पूर्णांक tx_rx_locks = SOCK_RCVBUF_LOCK | SOCK_SNDBUF_LOCK;
	काष्ठा sock *sk = (काष्ठा sock *)msk;

	अगर (ssk->sk_prot->keepalive) अणु
		अगर (sock_flag(sk, SOCK_KEEPOPEN))
			ssk->sk_prot->keepalive(ssk, 1);
		अन्यथा
			ssk->sk_prot->keepalive(ssk, 0);
	पूर्ण

	ssk->sk_priority = sk->sk_priority;
	ssk->sk_bound_dev_अगर = sk->sk_bound_dev_अगर;
	ssk->sk_incoming_cpu = sk->sk_incoming_cpu;

	अगर (sk->sk_userlocks & tx_rx_locks) अणु
		ssk->sk_userlocks |= sk->sk_userlocks & tx_rx_locks;
		अगर (sk->sk_userlocks & SOCK_SNDBUF_LOCK)
			WRITE_ONCE(ssk->sk_sndbuf, sk->sk_sndbuf);
		अगर (sk->sk_userlocks & SOCK_RCVBUF_LOCK)
			WRITE_ONCE(ssk->sk_rcvbuf, sk->sk_rcvbuf);
	पूर्ण

	अगर (sock_flag(sk, SOCK_LINGER)) अणु
		ssk->sk_lingerसमय = sk->sk_lingerसमय;
		sock_set_flag(ssk, SOCK_LINGER);
	पूर्ण अन्यथा अणु
		sock_reset_flag(ssk, SOCK_LINGER);
	पूर्ण

	अगर (sk->sk_mark != ssk->sk_mark) अणु
		ssk->sk_mark = sk->sk_mark;
		sk_dst_reset(ssk);
	पूर्ण

	sock_valbool_flag(ssk, SOCK_DBG, sock_flag(sk, SOCK_DBG));

	अगर (inet_csk(sk)->icsk_ca_ops != inet_csk(ssk)->icsk_ca_ops)
		tcp_set_congestion_control(ssk, msk->ca_name, false, true);
पूर्ण

अटल व्योम __mptcp_sockopt_sync(काष्ठा mptcp_sock *msk, काष्ठा sock *ssk)
अणु
	bool slow = lock_sock_fast(ssk);

	sync_socket_options(msk, ssk);

	unlock_sock_fast(ssk, slow);
पूर्ण

व्योम mptcp_sockopt_sync(काष्ठा mptcp_sock *msk, काष्ठा sock *ssk)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(ssk);

	msk_owned_by_me(msk);

	अगर (READ_ONCE(subflow->setsockopt_seq) != msk->setsockopt_seq) अणु
		__mptcp_sockopt_sync(msk, ssk);

		subflow->setsockopt_seq = msk->setsockopt_seq;
	पूर्ण
पूर्ण

व्योम mptcp_sockopt_sync_all(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा mptcp_subflow_context *subflow;
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	u32 seq;

	seq = sockopt_seq_reset(sk);

	mptcp_क्रम_each_subflow(msk, subflow) अणु
		काष्ठा sock *ssk = mptcp_subflow_tcp_sock(subflow);
		u32 sseq = READ_ONCE(subflow->setsockopt_seq);

		अगर (sseq != msk->setsockopt_seq) अणु
			__mptcp_sockopt_sync(msk, ssk);
			WRITE_ONCE(subflow->setsockopt_seq, seq);
		पूर्ण अन्यथा अगर (sseq != seq) अणु
			WRITE_ONCE(subflow->setsockopt_seq, seq);
		पूर्ण

		cond_resched();
	पूर्ण

	msk->setsockopt_seq = seq;
पूर्ण
