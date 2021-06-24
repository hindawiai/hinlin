<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Implementation of the Transmission Control Protocol(TCP).
 *
 *		IPv4 specअगरic functions
 *
 *		code split from:
 *		linux/ipv4/tcp.c
 *		linux/ipv4/tcp_input.c
 *		linux/ipv4/tcp_output.c
 *
 *		See tcp.c क्रम author inक्रमmation
 */

/*
 * Changes:
 *		David S. Miller	:	New socket lookup architecture.
 *					This code is dedicated to John Dyson.
 *		David S. Miller :	Change semantics of established hash,
 *					half is devoted to TIME_WAIT sockets
 *					and the rest go in the other half.
 *		Andi Kleen :		Add support क्रम syncookies and fixed
 *					some bugs: ip options weren't passed to
 *					the TCP layer, missed a check क्रम an
 *					ACK bit.
 *		Andi Kleen :		Implemented fast path mtu discovery.
 *	     				Fixed many serious bugs in the
 *					request_sock handling and moved
 *					most of it पूर्णांकo the af independent code.
 *					Added tail drop and some other bugfixes.
 *					Added new listen semantics.
 *		Mike McLagan	:	Routing by source
 *	Juan Jose Ciarlante:		ip_dynaddr bits
 *		Andi Kleen:		various fixes.
 *	Vitaly E. Lavrov	:	Transparent proxy revived after year
 *					coma.
 *	Andi Kleen		:	Fix new listen.
 *	Andi Kleen		:	Fix accept error reporting.
 *	YOSHIFUJI Hideaki @USAGI and:	Support IPV6_V6ONLY socket option, which
 *	Alexey Kuznetsov		allow both IPv4 and IPv6 sockets to bind
 *					a single port at the same समय.
 */

#घोषणा pr_fmt(fmt) "TCP: " fmt

#समावेश <linux/bottom_half.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/cache.h>
#समावेश <linux/jhash.h>
#समावेश <linux/init.h>
#समावेश <linux/बार.h>
#समावेश <linux/slab.h>

#समावेश <net/net_namespace.h>
#समावेश <net/icmp.h>
#समावेश <net/inet_hashtables.h>
#समावेश <net/tcp.h>
#समावेश <net/transp_v6.h>
#समावेश <net/ipv6.h>
#समावेश <net/inet_common.h>
#समावेश <net/समयरुको_sock.h>
#समावेश <net/xfrm.h>
#समावेश <net/secure_seq.h>
#समावेश <net/busy_poll.h>

#समावेश <linux/inet.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/btf_ids.h>

#समावेश <crypto/hash.h>
#समावेश <linux/scatterlist.h>

#समावेश <trace/events/tcp.h>

#अगर_घोषित CONFIG_TCP_MD5SIG
अटल पूर्णांक tcp_v4_md5_hash_hdr(अक्षर *md5_hash, स्थिर काष्ठा tcp_md5sig_key *key,
			       __be32 daddr, __be32 saddr, स्थिर काष्ठा tcphdr *th);
#पूर्ण_अगर

काष्ठा inet_hashinfo tcp_hashinfo;
EXPORT_SYMBOL(tcp_hashinfo);

अटल u32 tcp_v4_init_seq(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस secure_tcp_seq(ip_hdr(skb)->daddr,
			      ip_hdr(skb)->saddr,
			      tcp_hdr(skb)->dest,
			      tcp_hdr(skb)->source);
पूर्ण

अटल u32 tcp_v4_init_ts_off(स्थिर काष्ठा net *net, स्थिर काष्ठा sk_buff *skb)
अणु
	वापस secure_tcp_ts_off(net, ip_hdr(skb)->daddr, ip_hdr(skb)->saddr);
पूर्ण

पूर्णांक tcp_twsk_unique(काष्ठा sock *sk, काष्ठा sock *sktw, व्योम *twp)
अणु
	स्थिर काष्ठा inet_समयरुको_sock *tw = inet_twsk(sktw);
	स्थिर काष्ठा tcp_समयरुको_sock *tcptw = tcp_twsk(sktw);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	पूर्णांक reuse = sock_net(sk)->ipv4.sysctl_tcp_tw_reuse;

	अगर (reuse == 2) अणु
		/* Still करोes not detect *everything* that goes through
		 * lo, since we require a loopback src or dst address
		 * or direct binding to 'lo' पूर्णांकerface.
		 */
		bool loopback = false;
		अगर (tw->tw_bound_dev_अगर == LOOPBACK_IFINDEX)
			loopback = true;
#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (tw->tw_family == AF_INET6) अणु
			अगर (ipv6_addr_loopback(&tw->tw_v6_daddr) ||
			    ipv6_addr_v4mapped_loopback(&tw->tw_v6_daddr) ||
			    ipv6_addr_loopback(&tw->tw_v6_rcv_saddr) ||
			    ipv6_addr_v4mapped_loopback(&tw->tw_v6_rcv_saddr))
				loopback = true;
		पूर्ण अन्यथा
#पूर्ण_अगर
		अणु
			अगर (ipv4_is_loopback(tw->tw_daddr) ||
			    ipv4_is_loopback(tw->tw_rcv_saddr))
				loopback = true;
		पूर्ण
		अगर (!loopback)
			reuse = 0;
	पूर्ण

	/* With PAWS, it is safe from the viewpoपूर्णांक
	   of data पूर्णांकegrity. Even without PAWS it is safe provided sequence
	   spaces करो not overlap i.e. at data rates <= 80Mbit/sec.

	   Actually, the idea is बंद to VJ's one, only बारtamp cache is
	   held not per host, but per port pair and TW bucket is used as state
	   holder.

	   If TW bucket has been alपढ़ोy destroyed we fall back to VJ's scheme
	   and use initial बारtamp retrieved from peer table.
	 */
	अगर (tcptw->tw_ts_recent_stamp &&
	    (!twp || (reuse && समय_after32(kसमय_get_seconds(),
					    tcptw->tw_ts_recent_stamp)))) अणु
		/* In हाल of repair and re-using TIME-WAIT sockets we still
		 * want to be sure that it is safe as above but honor the
		 * sequence numbers and समय stamps set as part of the repair
		 * process.
		 *
		 * Without this check re-using a TIME-WAIT socket with TCP
		 * repair would accumulate a -1 on the repair asचिन्हित
		 * sequence number. The first समय it is reused the sequence
		 * is -1, the second समय -2, etc. This fixes that issue
		 * without appearing to create any others.
		 */
		अगर (likely(!tp->repair)) अणु
			u32 seq = tcptw->tw_snd_nxt + 65535 + 2;

			अगर (!seq)
				seq = 1;
			WRITE_ONCE(tp->ग_लिखो_seq, seq);
			tp->rx_opt.ts_recent	   = tcptw->tw_ts_recent;
			tp->rx_opt.ts_recent_stamp = tcptw->tw_ts_recent_stamp;
		पूर्ण
		sock_hold(sktw);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tcp_twsk_unique);

अटल पूर्णांक tcp_v4_pre_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr,
			      पूर्णांक addr_len)
अणु
	/* This check is replicated from tcp_v4_connect() and पूर्णांकended to
	 * prevent BPF program called below from accessing bytes that are out
	 * of the bound specअगरied by user in addr_len.
	 */
	अगर (addr_len < माप(काष्ठा sockaddr_in))
		वापस -EINVAL;

	sock_owned_by_me(sk);

	वापस BPF_CGROUP_RUN_PROG_INET4_CONNECT(sk, uaddr);
पूर्ण

/* This will initiate an outgoing connection. */
पूर्णांक tcp_v4_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा sockaddr_in *usin = (काष्ठा sockaddr_in *)uaddr;
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	__be16 orig_sport, orig_dport;
	__be32 daddr, nexthop;
	काष्ठा flowi4 *fl4;
	काष्ठा rtable *rt;
	पूर्णांक err;
	काष्ठा ip_options_rcu *inet_opt;
	काष्ठा inet_समयरुको_death_row *tcp_death_row = &sock_net(sk)->ipv4.tcp_death_row;

	अगर (addr_len < माप(काष्ठा sockaddr_in))
		वापस -EINVAL;

	अगर (usin->sin_family != AF_INET)
		वापस -EAFNOSUPPORT;

	nexthop = daddr = usin->sin_addr.s_addr;
	inet_opt = rcu_dereference_रक्षित(inet->inet_opt,
					     lockdep_sock_is_held(sk));
	अगर (inet_opt && inet_opt->opt.srr) अणु
		अगर (!daddr)
			वापस -EINVAL;
		nexthop = inet_opt->opt.faddr;
	पूर्ण

	orig_sport = inet->inet_sport;
	orig_dport = usin->sin_port;
	fl4 = &inet->cork.fl.u.ip4;
	rt = ip_route_connect(fl4, nexthop, inet->inet_saddr,
			      RT_CONN_FLAGS(sk), sk->sk_bound_dev_अगर,
			      IPPROTO_TCP,
			      orig_sport, orig_dport, sk);
	अगर (IS_ERR(rt)) अणु
		err = PTR_ERR(rt);
		अगर (err == -ENETUNREACH)
			IP_INC_STATS(sock_net(sk), IPSTATS_MIB_OUTNOROUTES);
		वापस err;
	पूर्ण

	अगर (rt->rt_flags & (RTCF_MULTICAST | RTCF_BROADCAST)) अणु
		ip_rt_put(rt);
		वापस -ENETUNREACH;
	पूर्ण

	अगर (!inet_opt || !inet_opt->opt.srr)
		daddr = fl4->daddr;

	अगर (!inet->inet_saddr)
		inet->inet_saddr = fl4->saddr;
	sk_rcv_saddr_set(sk, inet->inet_saddr);

	अगर (tp->rx_opt.ts_recent_stamp && inet->inet_daddr != daddr) अणु
		/* Reset inherited state */
		tp->rx_opt.ts_recent	   = 0;
		tp->rx_opt.ts_recent_stamp = 0;
		अगर (likely(!tp->repair))
			WRITE_ONCE(tp->ग_लिखो_seq, 0);
	पूर्ण

	inet->inet_dport = usin->sin_port;
	sk_daddr_set(sk, daddr);

	inet_csk(sk)->icsk_ext_hdr_len = 0;
	अगर (inet_opt)
		inet_csk(sk)->icsk_ext_hdr_len = inet_opt->opt.optlen;

	tp->rx_opt.mss_clamp = TCP_MSS_DEFAULT;

	/* Socket identity is still unknown (sport may be zero).
	 * However we set state to SYN-SENT and not releasing socket
	 * lock select source port, enter ourselves पूर्णांकo the hash tables and
	 * complete initialization after this.
	 */
	tcp_set_state(sk, TCP_SYN_SENT);
	err = inet_hash_connect(tcp_death_row, sk);
	अगर (err)
		जाओ failure;

	sk_set_txhash(sk);

	rt = ip_route_newports(fl4, rt, orig_sport, orig_dport,
			       inet->inet_sport, inet->inet_dport, sk);
	अगर (IS_ERR(rt)) अणु
		err = PTR_ERR(rt);
		rt = शून्य;
		जाओ failure;
	पूर्ण
	/* OK, now commit destination to socket.  */
	sk->sk_gso_type = SKB_GSO_TCPV4;
	sk_setup_caps(sk, &rt->dst);
	rt = शून्य;

	अगर (likely(!tp->repair)) अणु
		अगर (!tp->ग_लिखो_seq)
			WRITE_ONCE(tp->ग_लिखो_seq,
				   secure_tcp_seq(inet->inet_saddr,
						  inet->inet_daddr,
						  inet->inet_sport,
						  usin->sin_port));
		tp->tsoffset = secure_tcp_ts_off(sock_net(sk),
						 inet->inet_saddr,
						 inet->inet_daddr);
	पूर्ण

	inet->inet_id = pअक्रमom_u32();

	अगर (tcp_fastखोलो_defer_connect(sk, &err))
		वापस err;
	अगर (err)
		जाओ failure;

	err = tcp_connect(sk);

	अगर (err)
		जाओ failure;

	वापस 0;

failure:
	/*
	 * This unhashes the socket and releases the local port,
	 * अगर necessary.
	 */
	tcp_set_state(sk, TCP_CLOSE);
	ip_rt_put(rt);
	sk->sk_route_caps = 0;
	inet->inet_dport = 0;
	वापस err;
पूर्ण
EXPORT_SYMBOL(tcp_v4_connect);

/*
 * This routine reacts to ICMP_FRAG_NEEDED mtu indications as defined in RFC1191.
 * It can be called through tcp_release_cb() अगर socket was owned by user
 * at the समय tcp_v4_err() was called to handle ICMP message.
 */
व्योम tcp_v4_mtu_reduced(काष्ठा sock *sk)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा dst_entry *dst;
	u32 mtu;

	अगर ((1 << sk->sk_state) & (TCPF_LISTEN | TCPF_CLOSE))
		वापस;
	mtu = tcp_sk(sk)->mtu_info;
	dst = inet_csk_update_pmtu(sk, mtu);
	अगर (!dst)
		वापस;

	/* Something is about to be wrong... Remember soft error
	 * क्रम the हाल, अगर this connection will not able to recover.
	 */
	अगर (mtu < dst_mtu(dst) && ip_करोnt_fragment(sk, dst))
		sk->sk_err_soft = EMSGSIZE;

	mtu = dst_mtu(dst);

	अगर (inet->pmtudisc != IP_PMTUDISC_DONT &&
	    ip_sk_accept_pmtu(sk) &&
	    inet_csk(sk)->icsk_pmtu_cookie > mtu) अणु
		tcp_sync_mss(sk, mtu);

		/* Resend the TCP packet because it's
		 * clear that the old packet has been
		 * dropped. This is the new "fast" path mtu
		 * discovery.
		 */
		tcp_simple_retransmit(sk);
	पूर्ण /* अन्यथा let the usual retransmit समयr handle it */
पूर्ण
EXPORT_SYMBOL(tcp_v4_mtu_reduced);

अटल व्योम करो_redirect(काष्ठा sk_buff *skb, काष्ठा sock *sk)
अणु
	काष्ठा dst_entry *dst = __sk_dst_check(sk, 0);

	अगर (dst)
		dst->ops->redirect(dst, sk, skb);
पूर्ण


/* handle ICMP messages on TCP_NEW_SYN_RECV request sockets */
व्योम tcp_req_err(काष्ठा sock *sk, u32 seq, bool पात)
अणु
	काष्ठा request_sock *req = inet_reqsk(sk);
	काष्ठा net *net = sock_net(sk);

	/* ICMPs are not backlogged, hence we cannot get
	 * an established socket here.
	 */
	अगर (seq != tcp_rsk(req)->snt_isn) अणु
		__NET_INC_STATS(net, LINUX_MIB_OUTOFWINDOWICMPS);
	पूर्ण अन्यथा अगर (पात) अणु
		/*
		 * Still in SYN_RECV, just हटाओ it silently.
		 * There is no good way to pass the error to the newly
		 * created socket, and POSIX करोes not want network
		 * errors वापसed from accept().
		 */
		inet_csk_reqsk_queue_drop(req->rsk_listener, req);
		tcp_listendrop(req->rsk_listener);
	पूर्ण
	reqsk_put(req);
पूर्ण
EXPORT_SYMBOL(tcp_req_err);

/* TCP-LD (RFC 6069) logic */
व्योम tcp_ld_RTO_revert(काष्ठा sock *sk, u32 seq)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *skb;
	s32 reमुख्यing;
	u32 delta_us;

	अगर (sock_owned_by_user(sk))
		वापस;

	अगर (seq != tp->snd_una  || !icsk->icsk_retransmits ||
	    !icsk->icsk_backoff)
		वापस;

	skb = tcp_rtx_queue_head(sk);
	अगर (WARN_ON_ONCE(!skb))
		वापस;

	icsk->icsk_backoff--;
	icsk->icsk_rto = tp->srtt_us ? __tcp_set_rto(tp) : TCP_TIMEOUT_INIT;
	icsk->icsk_rto = inet_csk_rto_backoff(icsk, TCP_RTO_MAX);

	tcp_mstamp_refresh(tp);
	delta_us = (u32)(tp->tcp_mstamp - tcp_skb_बारtamp_us(skb));
	reमुख्यing = icsk->icsk_rto - usecs_to_jअगरfies(delta_us);

	अगर (reमुख्यing > 0) अणु
		inet_csk_reset_xmit_समयr(sk, ICSK_TIME_RETRANS,
					  reमुख्यing, TCP_RTO_MAX);
	पूर्ण अन्यथा अणु
		/* RTO revert घड़ीed out retransmission.
		 * Will retransmit now.
		 */
		tcp_retransmit_समयr(sk);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(tcp_ld_RTO_revert);

/*
 * This routine is called by the ICMP module when it माला_लो some
 * sort of error condition.  If err < 0 then the socket should
 * be बंदd and the error वापसed to the user.  If err > 0
 * it's just the icmp type << 8 | icmp code.  After adjusपंचांगent
 * header poपूर्णांकs to the first 8 bytes of the tcp header.  We need
 * to find the appropriate port.
 *
 * The locking strategy used here is very "optimistic". When
 * someone अन्यथा accesses the socket the ICMP is just dropped
 * and क्रम some paths there is no check at all.
 * A more general error queue to queue errors क्रम later handling
 * is probably better.
 *
 */

पूर्णांक tcp_v4_err(काष्ठा sk_buff *skb, u32 info)
अणु
	स्थिर काष्ठा iphdr *iph = (स्थिर काष्ठा iphdr *)skb->data;
	काष्ठा tcphdr *th = (काष्ठा tcphdr *)(skb->data + (iph->ihl << 2));
	काष्ठा tcp_sock *tp;
	काष्ठा inet_sock *inet;
	स्थिर पूर्णांक type = icmp_hdr(skb)->type;
	स्थिर पूर्णांक code = icmp_hdr(skb)->code;
	काष्ठा sock *sk;
	काष्ठा request_sock *fastखोलो;
	u32 seq, snd_una;
	पूर्णांक err;
	काष्ठा net *net = dev_net(skb->dev);

	sk = __inet_lookup_established(net, &tcp_hashinfo, iph->daddr,
				       th->dest, iph->saddr, ntohs(th->source),
				       inet_iअगर(skb), 0);
	अगर (!sk) अणु
		__ICMP_INC_STATS(net, ICMP_MIB_INERRORS);
		वापस -ENOENT;
	पूर्ण
	अगर (sk->sk_state == TCP_TIME_WAIT) अणु
		inet_twsk_put(inet_twsk(sk));
		वापस 0;
	पूर्ण
	seq = ntohl(th->seq);
	अगर (sk->sk_state == TCP_NEW_SYN_RECV) अणु
		tcp_req_err(sk, seq, type == ICMP_PARAMETERPROB ||
				     type == ICMP_TIME_EXCEEDED ||
				     (type == ICMP_DEST_UNREACH &&
				      (code == ICMP_NET_UNREACH ||
				       code == ICMP_HOST_UNREACH)));
		वापस 0;
	पूर्ण

	bh_lock_sock(sk);
	/* If too many ICMPs get dropped on busy
	 * servers this needs to be solved dअगरferently.
	 * We करो take care of PMTU discovery (RFC1191) special हाल :
	 * we can receive locally generated ICMP messages जबतक socket is held.
	 */
	अगर (sock_owned_by_user(sk)) अणु
		अगर (!(type == ICMP_DEST_UNREACH && code == ICMP_FRAG_NEEDED))
			__NET_INC_STATS(net, LINUX_MIB_LOCKDROPPEDICMPS);
	पूर्ण
	अगर (sk->sk_state == TCP_CLOSE)
		जाओ out;

	अगर (unlikely(iph->ttl < inet_sk(sk)->min_ttl)) अणु
		__NET_INC_STATS(net, LINUX_MIB_TCPMINTTLDROP);
		जाओ out;
	पूर्ण

	tp = tcp_sk(sk);
	/* XXX (TFO) - tp->snd_una should be ISN (tcp_create_खोलोreq_child() */
	fastखोलो = rcu_dereference(tp->fastखोलो_rsk);
	snd_una = fastखोलो ? tcp_rsk(fastखोलो)->snt_isn : tp->snd_una;
	अगर (sk->sk_state != TCP_LISTEN &&
	    !between(seq, snd_una, tp->snd_nxt)) अणु
		__NET_INC_STATS(net, LINUX_MIB_OUTOFWINDOWICMPS);
		जाओ out;
	पूर्ण

	चयन (type) अणु
	हाल ICMP_REसूचीECT:
		अगर (!sock_owned_by_user(sk))
			करो_redirect(skb, sk);
		जाओ out;
	हाल ICMP_SOURCE_QUENCH:
		/* Just silently ignore these. */
		जाओ out;
	हाल ICMP_PARAMETERPROB:
		err = EPROTO;
		अवरोध;
	हाल ICMP_DEST_UNREACH:
		अगर (code > NR_ICMP_UNREACH)
			जाओ out;

		अगर (code == ICMP_FRAG_NEEDED) अणु /* PMTU discovery (RFC1191) */
			/* We are not पूर्णांकerested in TCP_LISTEN and खोलो_requests
			 * (SYN-ACKs send out by Linux are always <576bytes so
			 * they should go through unfragmented).
			 */
			अगर (sk->sk_state == TCP_LISTEN)
				जाओ out;

			tp->mtu_info = info;
			अगर (!sock_owned_by_user(sk)) अणु
				tcp_v4_mtu_reduced(sk);
			पूर्ण अन्यथा अणु
				अगर (!test_and_set_bit(TCP_MTU_REDUCED_DEFERRED, &sk->sk_tsq_flags))
					sock_hold(sk);
			पूर्ण
			जाओ out;
		पूर्ण

		err = icmp_err_convert[code].त्रुटि_सं;
		/* check अगर this ICMP message allows revert of backoff.
		 * (see RFC 6069)
		 */
		अगर (!fastखोलो &&
		    (code == ICMP_NET_UNREACH || code == ICMP_HOST_UNREACH))
			tcp_ld_RTO_revert(sk, seq);
		अवरोध;
	हाल ICMP_TIME_EXCEEDED:
		err = EHOSTUNREACH;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	चयन (sk->sk_state) अणु
	हाल TCP_SYN_SENT:
	हाल TCP_SYN_RECV:
		/* Only in fast or simultaneous खोलो. If a fast खोलो socket is
		 * alपढ़ोy accepted it is treated as a connected one below.
		 */
		अगर (fastखोलो && !fastखोलो->sk)
			अवरोध;

		ip_icmp_error(sk, skb, err, th->dest, info, (u8 *)th);

		अगर (!sock_owned_by_user(sk)) अणु
			sk->sk_err = err;

			sk->sk_error_report(sk);

			tcp_करोne(sk);
		पूर्ण अन्यथा अणु
			sk->sk_err_soft = err;
		पूर्ण
		जाओ out;
	पूर्ण

	/* If we've alपढ़ोy connected we will keep trying
	 * until we समय out, or the user gives up.
	 *
	 * rfc1122 4.2.3.9 allows to consider as hard errors
	 * only PROTO_UNREACH and PORT_UNREACH (well, FRAG_FAILED too,
	 * but it is obsoleted by pmtu discovery).
	 *
	 * Note, that in modern पूर्णांकernet, where routing is unreliable
	 * and in each dark corner broken firewalls sit, sending अक्रमom
	 * errors ordered by their masters even this two messages finally lose
	 * their original sense (even Linux sends invalid PORT_UNREACHs)
	 *
	 * Now we are in compliance with RFCs.
	 *							--ANK (980905)
	 */

	inet = inet_sk(sk);
	अगर (!sock_owned_by_user(sk) && inet->recverr) अणु
		sk->sk_err = err;
		sk->sk_error_report(sk);
	पूर्ण अन्यथा	अणु /* Only an error on समयout */
		sk->sk_err_soft = err;
	पूर्ण

out:
	bh_unlock_sock(sk);
	sock_put(sk);
	वापस 0;
पूर्ण

व्योम __tcp_v4_send_check(काष्ठा sk_buff *skb, __be32 saddr, __be32 daddr)
अणु
	काष्ठा tcphdr *th = tcp_hdr(skb);

	th->check = ~tcp_v4_check(skb->len, saddr, daddr, 0);
	skb->csum_start = skb_transport_header(skb) - skb->head;
	skb->csum_offset = दुरत्व(काष्ठा tcphdr, check);
पूर्ण

/* This routine computes an IPv4 TCP checksum. */
व्योम tcp_v4_send_check(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा inet_sock *inet = inet_sk(sk);

	__tcp_v4_send_check(skb, inet->inet_saddr, inet->inet_daddr);
पूर्ण
EXPORT_SYMBOL(tcp_v4_send_check);

/*
 *	This routine will send an RST to the other tcp.
 *
 *	Someone asks: why I NEVER use socket parameters (TOS, TTL etc.)
 *		      क्रम reset.
 *	Answer: अगर a packet caused RST, it is not क्रम a socket
 *		existing in our प्रणाली, अगर it is matched to a socket,
 *		it is just duplicate segment or bug in other side's TCP.
 *		So that we build reply only basing on parameters
 *		arrived with segment.
 *	Exception: precedence violation. We करो not implement it in any हाल.
 */

#अगर_घोषित CONFIG_TCP_MD5SIG
#घोषणा OPTION_BYTES TCPOLEN_MD5SIG_ALIGNED
#अन्यथा
#घोषणा OPTION_BYTES माप(__be32)
#पूर्ण_अगर

अटल व्योम tcp_v4_send_reset(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा tcphdr *th = tcp_hdr(skb);
	काष्ठा अणु
		काष्ठा tcphdr th;
		__be32 opt[OPTION_BYTES / माप(__be32)];
	पूर्ण rep;
	काष्ठा ip_reply_arg arg;
#अगर_घोषित CONFIG_TCP_MD5SIG
	काष्ठा tcp_md5sig_key *key = शून्य;
	स्थिर __u8 *hash_location = शून्य;
	अचिन्हित अक्षर newhash[16];
	पूर्णांक genhash;
	काष्ठा sock *sk1 = शून्य;
#पूर्ण_अगर
	u64 transmit_समय = 0;
	काष्ठा sock *ctl_sk;
	काष्ठा net *net;

	/* Never send a reset in response to a reset. */
	अगर (th->rst)
		वापस;

	/* If sk not शून्य, it means we did a successful lookup and incoming
	 * route had to be correct. prequeue might have dropped our dst.
	 */
	अगर (!sk && skb_rtable(skb)->rt_type != RTN_LOCAL)
		वापस;

	/* Swap the send and the receive. */
	स_रखो(&rep, 0, माप(rep));
	rep.th.dest   = th->source;
	rep.th.source = th->dest;
	rep.th.करोff   = माप(काष्ठा tcphdr) / 4;
	rep.th.rst    = 1;

	अगर (th->ack) अणु
		rep.th.seq = th->ack_seq;
	पूर्ण अन्यथा अणु
		rep.th.ack = 1;
		rep.th.ack_seq = htonl(ntohl(th->seq) + th->syn + th->fin +
				       skb->len - (th->करोff << 2));
	पूर्ण

	स_रखो(&arg, 0, माप(arg));
	arg.iov[0].iov_base = (अचिन्हित अक्षर *)&rep;
	arg.iov[0].iov_len  = माप(rep.th);

	net = sk ? sock_net(sk) : dev_net(skb_dst(skb)->dev);
#अगर_घोषित CONFIG_TCP_MD5SIG
	rcu_पढ़ो_lock();
	hash_location = tcp_parse_md5sig_option(th);
	अगर (sk && sk_fullsock(sk)) अणु
		स्थिर जोड़ tcp_md5_addr *addr;
		पूर्णांक l3index;

		/* sdअगर set, means packet ingressed via a device
		 * in an L3 करोमुख्य and inet_iअगर is set to it.
		 */
		l3index = tcp_v4_sdअगर(skb) ? inet_iअगर(skb) : 0;
		addr = (जोड़ tcp_md5_addr *)&ip_hdr(skb)->saddr;
		key = tcp_md5_करो_lookup(sk, l3index, addr, AF_INET);
	पूर्ण अन्यथा अगर (hash_location) अणु
		स्थिर जोड़ tcp_md5_addr *addr;
		पूर्णांक sdअगर = tcp_v4_sdअगर(skb);
		पूर्णांक dअगर = inet_iअगर(skb);
		पूर्णांक l3index;

		/*
		 * active side is lost. Try to find listening socket through
		 * source port, and then find md5 key through listening socket.
		 * we are not loose security here:
		 * Incoming packet is checked with md5 hash with finding key,
		 * no RST generated अगर md5 hash करोesn't match.
		 */
		sk1 = __inet_lookup_listener(net, &tcp_hashinfo, शून्य, 0,
					     ip_hdr(skb)->saddr,
					     th->source, ip_hdr(skb)->daddr,
					     ntohs(th->source), dअगर, sdअगर);
		/* करोn't send rst if it can't find key */
		अगर (!sk1)
			जाओ out;

		/* sdअगर set, means packet ingressed via a device
		 * in an L3 करोमुख्य and dअगर is set to it.
		 */
		l3index = sdअगर ? dअगर : 0;
		addr = (जोड़ tcp_md5_addr *)&ip_hdr(skb)->saddr;
		key = tcp_md5_करो_lookup(sk1, l3index, addr, AF_INET);
		अगर (!key)
			जाओ out;


		genhash = tcp_v4_md5_hash_skb(newhash, key, शून्य, skb);
		अगर (genhash || स_भेद(hash_location, newhash, 16) != 0)
			जाओ out;

	पूर्ण

	अगर (key) अणु
		rep.opt[0] = htonl((TCPOPT_NOP << 24) |
				   (TCPOPT_NOP << 16) |
				   (TCPOPT_MD5SIG << 8) |
				   TCPOLEN_MD5SIG);
		/* Update length and the length the header thinks exists */
		arg.iov[0].iov_len += TCPOLEN_MD5SIG_ALIGNED;
		rep.th.करोff = arg.iov[0].iov_len / 4;

		tcp_v4_md5_hash_hdr((__u8 *) &rep.opt[1],
				     key, ip_hdr(skb)->saddr,
				     ip_hdr(skb)->daddr, &rep.th);
	पूर्ण
#पूर्ण_अगर
	/* Can't co-exist with TCPMD5, hence check rep.opt[0] */
	अगर (rep.opt[0] == 0) अणु
		__be32 mrst = mptcp_reset_option(skb);

		अगर (mrst) अणु
			rep.opt[0] = mrst;
			arg.iov[0].iov_len += माप(mrst);
			rep.th.करोff = arg.iov[0].iov_len / 4;
		पूर्ण
	पूर्ण

	arg.csum = csum_tcpudp_nofold(ip_hdr(skb)->daddr,
				      ip_hdr(skb)->saddr, /* XXX */
				      arg.iov[0].iov_len, IPPROTO_TCP, 0);
	arg.csumoffset = दुरत्व(काष्ठा tcphdr, check) / 2;
	arg.flags = (sk && inet_sk_transparent(sk)) ? IP_REPLY_ARG_NOSRCCHECK : 0;

	/* When socket is gone, all binding inक्रमmation is lost.
	 * routing might fail in this हाल. No choice here, अगर we choose to क्रमce
	 * input पूर्णांकerface, we will misroute in हाल of asymmetric route.
	 */
	अगर (sk) अणु
		arg.bound_dev_अगर = sk->sk_bound_dev_अगर;
		अगर (sk_fullsock(sk))
			trace_tcp_send_reset(sk, skb);
	पूर्ण

	BUILD_BUG_ON(दुरत्व(काष्ठा sock, sk_bound_dev_अगर) !=
		     दुरत्व(काष्ठा inet_समयरुको_sock, tw_bound_dev_अगर));

	arg.tos = ip_hdr(skb)->tos;
	arg.uid = sock_net_uid(net, sk && sk_fullsock(sk) ? sk : शून्य);
	local_bh_disable();
	ctl_sk = this_cpu_पढ़ो(*net->ipv4.tcp_sk);
	अगर (sk) अणु
		ctl_sk->sk_mark = (sk->sk_state == TCP_TIME_WAIT) ?
				   inet_twsk(sk)->tw_mark : sk->sk_mark;
		ctl_sk->sk_priority = (sk->sk_state == TCP_TIME_WAIT) ?
				   inet_twsk(sk)->tw_priority : sk->sk_priority;
		transmit_समय = tcp_transmit_समय(sk);
	पूर्ण
	ip_send_unicast_reply(ctl_sk,
			      skb, &TCP_SKB_CB(skb)->header.h4.opt,
			      ip_hdr(skb)->saddr, ip_hdr(skb)->daddr,
			      &arg, arg.iov[0].iov_len,
			      transmit_समय);

	ctl_sk->sk_mark = 0;
	__TCP_INC_STATS(net, TCP_MIB_OUTSEGS);
	__TCP_INC_STATS(net, TCP_MIB_OUTRSTS);
	local_bh_enable();

#अगर_घोषित CONFIG_TCP_MD5SIG
out:
	rcu_पढ़ो_unlock();
#पूर्ण_अगर
पूर्ण

/* The code following below sending ACKs in SYN-RECV and TIME-WAIT states
   outside socket context is ugly, certainly. What can I करो?
 */

अटल व्योम tcp_v4_send_ack(स्थिर काष्ठा sock *sk,
			    काष्ठा sk_buff *skb, u32 seq, u32 ack,
			    u32 win, u32 tsval, u32 tsecr, पूर्णांक oअगर,
			    काष्ठा tcp_md5sig_key *key,
			    पूर्णांक reply_flags, u8 tos)
अणु
	स्थिर काष्ठा tcphdr *th = tcp_hdr(skb);
	काष्ठा अणु
		काष्ठा tcphdr th;
		__be32 opt[(TCPOLEN_TSTAMP_ALIGNED >> 2)
#अगर_घोषित CONFIG_TCP_MD5SIG
			   + (TCPOLEN_MD5SIG_ALIGNED >> 2)
#पूर्ण_अगर
			];
	पूर्ण rep;
	काष्ठा net *net = sock_net(sk);
	काष्ठा ip_reply_arg arg;
	काष्ठा sock *ctl_sk;
	u64 transmit_समय;

	स_रखो(&rep.th, 0, माप(काष्ठा tcphdr));
	स_रखो(&arg, 0, माप(arg));

	arg.iov[0].iov_base = (अचिन्हित अक्षर *)&rep;
	arg.iov[0].iov_len  = माप(rep.th);
	अगर (tsecr) अणु
		rep.opt[0] = htonl((TCPOPT_NOP << 24) | (TCPOPT_NOP << 16) |
				   (TCPOPT_TIMESTAMP << 8) |
				   TCPOLEN_TIMESTAMP);
		rep.opt[1] = htonl(tsval);
		rep.opt[2] = htonl(tsecr);
		arg.iov[0].iov_len += TCPOLEN_TSTAMP_ALIGNED;
	पूर्ण

	/* Swap the send and the receive. */
	rep.th.dest    = th->source;
	rep.th.source  = th->dest;
	rep.th.करोff    = arg.iov[0].iov_len / 4;
	rep.th.seq     = htonl(seq);
	rep.th.ack_seq = htonl(ack);
	rep.th.ack     = 1;
	rep.th.winकरोw  = htons(win);

#अगर_घोषित CONFIG_TCP_MD5SIG
	अगर (key) अणु
		पूर्णांक offset = (tsecr) ? 3 : 0;

		rep.opt[offset++] = htonl((TCPOPT_NOP << 24) |
					  (TCPOPT_NOP << 16) |
					  (TCPOPT_MD5SIG << 8) |
					  TCPOLEN_MD5SIG);
		arg.iov[0].iov_len += TCPOLEN_MD5SIG_ALIGNED;
		rep.th.करोff = arg.iov[0].iov_len/4;

		tcp_v4_md5_hash_hdr((__u8 *) &rep.opt[offset],
				    key, ip_hdr(skb)->saddr,
				    ip_hdr(skb)->daddr, &rep.th);
	पूर्ण
#पूर्ण_अगर
	arg.flags = reply_flags;
	arg.csum = csum_tcpudp_nofold(ip_hdr(skb)->daddr,
				      ip_hdr(skb)->saddr, /* XXX */
				      arg.iov[0].iov_len, IPPROTO_TCP, 0);
	arg.csumoffset = दुरत्व(काष्ठा tcphdr, check) / 2;
	अगर (oअगर)
		arg.bound_dev_अगर = oअगर;
	arg.tos = tos;
	arg.uid = sock_net_uid(net, sk_fullsock(sk) ? sk : शून्य);
	local_bh_disable();
	ctl_sk = this_cpu_पढ़ो(*net->ipv4.tcp_sk);
	ctl_sk->sk_mark = (sk->sk_state == TCP_TIME_WAIT) ?
			   inet_twsk(sk)->tw_mark : sk->sk_mark;
	ctl_sk->sk_priority = (sk->sk_state == TCP_TIME_WAIT) ?
			   inet_twsk(sk)->tw_priority : sk->sk_priority;
	transmit_समय = tcp_transmit_समय(sk);
	ip_send_unicast_reply(ctl_sk,
			      skb, &TCP_SKB_CB(skb)->header.h4.opt,
			      ip_hdr(skb)->saddr, ip_hdr(skb)->daddr,
			      &arg, arg.iov[0].iov_len,
			      transmit_समय);

	ctl_sk->sk_mark = 0;
	__TCP_INC_STATS(net, TCP_MIB_OUTSEGS);
	local_bh_enable();
पूर्ण

अटल व्योम tcp_v4_समयरुको_ack(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा inet_समयरुको_sock *tw = inet_twsk(sk);
	काष्ठा tcp_समयरुको_sock *tcptw = tcp_twsk(sk);

	tcp_v4_send_ack(sk, skb,
			tcptw->tw_snd_nxt, tcptw->tw_rcv_nxt,
			tcptw->tw_rcv_wnd >> tw->tw_rcv_wscale,
			tcp_समय_stamp_raw() + tcptw->tw_ts_offset,
			tcptw->tw_ts_recent,
			tw->tw_bound_dev_अगर,
			tcp_twsk_md5_key(tcptw),
			tw->tw_transparent ? IP_REPLY_ARG_NOSRCCHECK : 0,
			tw->tw_tos
			);

	inet_twsk_put(tw);
पूर्ण

अटल व्योम tcp_v4_reqsk_send_ack(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb,
				  काष्ठा request_sock *req)
अणु
	स्थिर जोड़ tcp_md5_addr *addr;
	पूर्णांक l3index;

	/* sk->sk_state == TCP_LISTEN -> क्रम regular TCP_SYN_RECV
	 * sk->sk_state == TCP_SYN_RECV -> क्रम Fast Open.
	 */
	u32 seq = (sk->sk_state == TCP_LISTEN) ? tcp_rsk(req)->snt_isn + 1 :
					     tcp_sk(sk)->snd_nxt;

	/* RFC 7323 2.3
	 * The winकरोw field (SEG.WND) of every outgoing segment, with the
	 * exception of <SYN> segments, MUST be right-shअगरted by
	 * Rcv.Wind.Shअगरt bits:
	 */
	addr = (जोड़ tcp_md5_addr *)&ip_hdr(skb)->saddr;
	l3index = tcp_v4_sdअगर(skb) ? inet_iअगर(skb) : 0;
	tcp_v4_send_ack(sk, skb, seq,
			tcp_rsk(req)->rcv_nxt,
			req->rsk_rcv_wnd >> inet_rsk(req)->rcv_wscale,
			tcp_समय_stamp_raw() + tcp_rsk(req)->ts_off,
			req->ts_recent,
			0,
			tcp_md5_करो_lookup(sk, l3index, addr, AF_INET),
			inet_rsk(req)->no_srccheck ? IP_REPLY_ARG_NOSRCCHECK : 0,
			ip_hdr(skb)->tos);
पूर्ण

/*
 *	Send a SYN-ACK after having received a SYN.
 *	This still operates on a request_sock only, not on a big
 *	socket.
 */
अटल पूर्णांक tcp_v4_send_synack(स्थिर काष्ठा sock *sk, काष्ठा dst_entry *dst,
			      काष्ठा flowi *fl,
			      काष्ठा request_sock *req,
			      काष्ठा tcp_fastखोलो_cookie *foc,
			      क्रमागत tcp_synack_type synack_type,
			      काष्ठा sk_buff *syn_skb)
अणु
	स्थिर काष्ठा inet_request_sock *ireq = inet_rsk(req);
	काष्ठा flowi4 fl4;
	पूर्णांक err = -1;
	काष्ठा sk_buff *skb;
	u8 tos;

	/* First, grab a route. */
	अगर (!dst && (dst = inet_csk_route_req(sk, &fl4, req)) == शून्य)
		वापस -1;

	skb = tcp_make_synack(sk, dst, req, foc, synack_type, syn_skb);

	अगर (skb) अणु
		__tcp_v4_send_check(skb, ireq->ir_loc_addr, ireq->ir_rmt_addr);

		tos = sock_net(sk)->ipv4.sysctl_tcp_reflect_tos ?
				(tcp_rsk(req)->syn_tos & ~INET_ECN_MASK) |
				(inet_sk(sk)->tos & INET_ECN_MASK) :
				inet_sk(sk)->tos;

		अगर (!INET_ECN_is_capable(tos) &&
		    tcp_bpf_ca_needs_ecn((काष्ठा sock *)req))
			tos |= INET_ECN_ECT_0;

		rcu_पढ़ो_lock();
		err = ip_build_and_send_pkt(skb, sk, ireq->ir_loc_addr,
					    ireq->ir_rmt_addr,
					    rcu_dereference(ireq->ireq_opt),
					    tos);
		rcu_पढ़ो_unlock();
		err = net_xmit_eval(err);
	पूर्ण

	वापस err;
पूर्ण

/*
 *	IPv4 request_sock deकाष्ठाor.
 */
अटल व्योम tcp_v4_reqsk_deकाष्ठाor(काष्ठा request_sock *req)
अणु
	kमुक्त(rcu_dereference_रक्षित(inet_rsk(req)->ireq_opt, 1));
पूर्ण

#अगर_घोषित CONFIG_TCP_MD5SIG
/*
 * RFC2385 MD5 checksumming requires a mapping of
 * IP address->MD5 Key.
 * We need to मुख्यtain these in the sk काष्ठाure.
 */

DEFINE_STATIC_KEY_FALSE(tcp_md5_needed);
EXPORT_SYMBOL(tcp_md5_needed);

/* Find the Key काष्ठाure क्रम an address.  */
काष्ठा tcp_md5sig_key *__tcp_md5_करो_lookup(स्थिर काष्ठा sock *sk, पूर्णांक l3index,
					   स्थिर जोड़ tcp_md5_addr *addr,
					   पूर्णांक family)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा tcp_md5sig_key *key;
	स्थिर काष्ठा tcp_md5sig_info *md5sig;
	__be32 mask;
	काष्ठा tcp_md5sig_key *best_match = शून्य;
	bool match;

	/* caller either holds rcu_पढ़ो_lock() or socket lock */
	md5sig = rcu_dereference_check(tp->md5sig_info,
				       lockdep_sock_is_held(sk));
	अगर (!md5sig)
		वापस शून्य;

	hlist_क्रम_each_entry_rcu(key, &md5sig->head, node,
				 lockdep_sock_is_held(sk)) अणु
		अगर (key->family != family)
			जारी;
		अगर (key->l3index && key->l3index != l3index)
			जारी;
		अगर (family == AF_INET) अणु
			mask = inet_make_mask(key->prefixlen);
			match = (key->addr.a4.s_addr & mask) ==
				(addr->a4.s_addr & mask);
#अगर IS_ENABLED(CONFIG_IPV6)
		पूर्ण अन्यथा अगर (family == AF_INET6) अणु
			match = ipv6_prefix_equal(&key->addr.a6, &addr->a6,
						  key->prefixlen);
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			match = false;
		पूर्ण

		अगर (match && (!best_match ||
			      key->prefixlen > best_match->prefixlen))
			best_match = key;
	पूर्ण
	वापस best_match;
पूर्ण
EXPORT_SYMBOL(__tcp_md5_करो_lookup);

अटल काष्ठा tcp_md5sig_key *tcp_md5_करो_lookup_exact(स्थिर काष्ठा sock *sk,
						      स्थिर जोड़ tcp_md5_addr *addr,
						      पूर्णांक family, u8 prefixlen,
						      पूर्णांक l3index)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा tcp_md5sig_key *key;
	अचिन्हित पूर्णांक size = माप(काष्ठा in_addr);
	स्थिर काष्ठा tcp_md5sig_info *md5sig;

	/* caller either holds rcu_पढ़ो_lock() or socket lock */
	md5sig = rcu_dereference_check(tp->md5sig_info,
				       lockdep_sock_is_held(sk));
	अगर (!md5sig)
		वापस शून्य;
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (family == AF_INET6)
		size = माप(काष्ठा in6_addr);
#पूर्ण_अगर
	hlist_क्रम_each_entry_rcu(key, &md5sig->head, node,
				 lockdep_sock_is_held(sk)) अणु
		अगर (key->family != family)
			जारी;
		अगर (key->l3index && key->l3index != l3index)
			जारी;
		अगर (!स_भेद(&key->addr, addr, size) &&
		    key->prefixlen == prefixlen)
			वापस key;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा tcp_md5sig_key *tcp_v4_md5_lookup(स्थिर काष्ठा sock *sk,
					 स्थिर काष्ठा sock *addr_sk)
अणु
	स्थिर जोड़ tcp_md5_addr *addr;
	पूर्णांक l3index;

	l3index = l3mdev_master_अगरindex_by_index(sock_net(sk),
						 addr_sk->sk_bound_dev_अगर);
	addr = (स्थिर जोड़ tcp_md5_addr *)&addr_sk->sk_daddr;
	वापस tcp_md5_करो_lookup(sk, l3index, addr, AF_INET);
पूर्ण
EXPORT_SYMBOL(tcp_v4_md5_lookup);

/* This can be called on a newly created socket, from other files */
पूर्णांक tcp_md5_करो_add(काष्ठा sock *sk, स्थिर जोड़ tcp_md5_addr *addr,
		   पूर्णांक family, u8 prefixlen, पूर्णांक l3index,
		   स्थिर u8 *newkey, u8 newkeylen, gfp_t gfp)
अणु
	/* Add Key to the list */
	काष्ठा tcp_md5sig_key *key;
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा tcp_md5sig_info *md5sig;

	key = tcp_md5_करो_lookup_exact(sk, addr, family, prefixlen, l3index);
	अगर (key) अणु
		/* Pre-existing entry - just update that one.
		 * Note that the key might be used concurrently.
		 * data_race() is telling kcsan that we करो not care of
		 * key mismatches, since changing MD5 key on live flows
		 * can lead to packet drops.
		 */
		data_race(स_नकल(key->key, newkey, newkeylen));

		/* Pairs with READ_ONCE() in tcp_md5_hash_key().
		 * Also note that a पढ़ोer could catch new key->keylen value
		 * but old key->key[], this is the reason we use __GFP_ZERO
		 * at sock_kदो_स्मृति() समय below these lines.
		 */
		WRITE_ONCE(key->keylen, newkeylen);

		वापस 0;
	पूर्ण

	md5sig = rcu_dereference_रक्षित(tp->md5sig_info,
					   lockdep_sock_is_held(sk));
	अगर (!md5sig) अणु
		md5sig = kदो_स्मृति(माप(*md5sig), gfp);
		अगर (!md5sig)
			वापस -ENOMEM;

		sk_nocaps_add(sk, NETIF_F_GSO_MASK);
		INIT_HLIST_HEAD(&md5sig->head);
		rcu_assign_poपूर्णांकer(tp->md5sig_info, md5sig);
	पूर्ण

	key = sock_kदो_स्मृति(sk, माप(*key), gfp | __GFP_ZERO);
	अगर (!key)
		वापस -ENOMEM;
	अगर (!tcp_alloc_md5sig_pool()) अणु
		sock_kमुक्त_s(sk, key, माप(*key));
		वापस -ENOMEM;
	पूर्ण

	स_नकल(key->key, newkey, newkeylen);
	key->keylen = newkeylen;
	key->family = family;
	key->prefixlen = prefixlen;
	key->l3index = l3index;
	स_नकल(&key->addr, addr,
	       (family == AF_INET6) ? माप(काष्ठा in6_addr) :
				      माप(काष्ठा in_addr));
	hlist_add_head_rcu(&key->node, &md5sig->head);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tcp_md5_करो_add);

पूर्णांक tcp_md5_करो_del(काष्ठा sock *sk, स्थिर जोड़ tcp_md5_addr *addr, पूर्णांक family,
		   u8 prefixlen, पूर्णांक l3index)
अणु
	काष्ठा tcp_md5sig_key *key;

	key = tcp_md5_करो_lookup_exact(sk, addr, family, prefixlen, l3index);
	अगर (!key)
		वापस -ENOENT;
	hlist_del_rcu(&key->node);
	atomic_sub(माप(*key), &sk->sk_omem_alloc);
	kमुक्त_rcu(key, rcu);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tcp_md5_करो_del);

अटल व्योम tcp_clear_md5_list(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा tcp_md5sig_key *key;
	काष्ठा hlist_node *n;
	काष्ठा tcp_md5sig_info *md5sig;

	md5sig = rcu_dereference_रक्षित(tp->md5sig_info, 1);

	hlist_क्रम_each_entry_safe(key, n, &md5sig->head, node) अणु
		hlist_del_rcu(&key->node);
		atomic_sub(माप(*key), &sk->sk_omem_alloc);
		kमुक्त_rcu(key, rcu);
	पूर्ण
पूर्ण

अटल पूर्णांक tcp_v4_parse_md5_keys(काष्ठा sock *sk, पूर्णांक optname,
				 sockptr_t optval, पूर्णांक optlen)
अणु
	काष्ठा tcp_md5sig cmd;
	काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *)&cmd.tcpm_addr;
	स्थिर जोड़ tcp_md5_addr *addr;
	u8 prefixlen = 32;
	पूर्णांक l3index = 0;

	अगर (optlen < माप(cmd))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&cmd, optval, माप(cmd)))
		वापस -EFAULT;

	अगर (sin->sin_family != AF_INET)
		वापस -EINVAL;

	अगर (optname == TCP_MD5SIG_EXT &&
	    cmd.tcpm_flags & TCP_MD5SIG_FLAG_PREFIX) अणु
		prefixlen = cmd.tcpm_prefixlen;
		अगर (prefixlen > 32)
			वापस -EINVAL;
	पूर्ण

	अगर (optname == TCP_MD5SIG_EXT &&
	    cmd.tcpm_flags & TCP_MD5SIG_FLAG_IFINDEX) अणु
		काष्ठा net_device *dev;

		rcu_पढ़ो_lock();
		dev = dev_get_by_index_rcu(sock_net(sk), cmd.tcpm_अगरindex);
		अगर (dev && netअगर_is_l3_master(dev))
			l3index = dev->अगरindex;

		rcu_पढ़ो_unlock();

		/* ok to reference set/not set outside of rcu;
		 * right now device MUST be an L3 master
		 */
		अगर (!dev || !l3index)
			वापस -EINVAL;
	पूर्ण

	addr = (जोड़ tcp_md5_addr *)&sin->sin_addr.s_addr;

	अगर (!cmd.tcpm_keylen)
		वापस tcp_md5_करो_del(sk, addr, AF_INET, prefixlen, l3index);

	अगर (cmd.tcpm_keylen > TCP_MD5SIG_MAXKEYLEN)
		वापस -EINVAL;

	वापस tcp_md5_करो_add(sk, addr, AF_INET, prefixlen, l3index,
			      cmd.tcpm_key, cmd.tcpm_keylen, GFP_KERNEL);
पूर्ण

अटल पूर्णांक tcp_v4_md5_hash_headers(काष्ठा tcp_md5sig_pool *hp,
				   __be32 daddr, __be32 saddr,
				   स्थिर काष्ठा tcphdr *th, पूर्णांक nbytes)
अणु
	काष्ठा tcp4_pseuकरोhdr *bp;
	काष्ठा scatterlist sg;
	काष्ठा tcphdr *_th;

	bp = hp->scratch;
	bp->saddr = saddr;
	bp->daddr = daddr;
	bp->pad = 0;
	bp->protocol = IPPROTO_TCP;
	bp->len = cpu_to_be16(nbytes);

	_th = (काष्ठा tcphdr *)(bp + 1);
	स_नकल(_th, th, माप(*th));
	_th->check = 0;

	sg_init_one(&sg, bp, माप(*bp) + माप(*th));
	ahash_request_set_crypt(hp->md5_req, &sg, शून्य,
				माप(*bp) + माप(*th));
	वापस crypto_ahash_update(hp->md5_req);
पूर्ण

अटल पूर्णांक tcp_v4_md5_hash_hdr(अक्षर *md5_hash, स्थिर काष्ठा tcp_md5sig_key *key,
			       __be32 daddr, __be32 saddr, स्थिर काष्ठा tcphdr *th)
अणु
	काष्ठा tcp_md5sig_pool *hp;
	काष्ठा ahash_request *req;

	hp = tcp_get_md5sig_pool();
	अगर (!hp)
		जाओ clear_hash_noput;
	req = hp->md5_req;

	अगर (crypto_ahash_init(req))
		जाओ clear_hash;
	अगर (tcp_v4_md5_hash_headers(hp, daddr, saddr, th, th->करोff << 2))
		जाओ clear_hash;
	अगर (tcp_md5_hash_key(hp, key))
		जाओ clear_hash;
	ahash_request_set_crypt(req, शून्य, md5_hash, 0);
	अगर (crypto_ahash_final(req))
		जाओ clear_hash;

	tcp_put_md5sig_pool();
	वापस 0;

clear_hash:
	tcp_put_md5sig_pool();
clear_hash_noput:
	स_रखो(md5_hash, 0, 16);
	वापस 1;
पूर्ण

पूर्णांक tcp_v4_md5_hash_skb(अक्षर *md5_hash, स्थिर काष्ठा tcp_md5sig_key *key,
			स्थिर काष्ठा sock *sk,
			स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_md5sig_pool *hp;
	काष्ठा ahash_request *req;
	स्थिर काष्ठा tcphdr *th = tcp_hdr(skb);
	__be32 saddr, daddr;

	अगर (sk) अणु /* valid क्रम establish/request sockets */
		saddr = sk->sk_rcv_saddr;
		daddr = sk->sk_daddr;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
		saddr = iph->saddr;
		daddr = iph->daddr;
	पूर्ण

	hp = tcp_get_md5sig_pool();
	अगर (!hp)
		जाओ clear_hash_noput;
	req = hp->md5_req;

	अगर (crypto_ahash_init(req))
		जाओ clear_hash;

	अगर (tcp_v4_md5_hash_headers(hp, daddr, saddr, th, skb->len))
		जाओ clear_hash;
	अगर (tcp_md5_hash_skb_data(hp, skb, th->करोff << 2))
		जाओ clear_hash;
	अगर (tcp_md5_hash_key(hp, key))
		जाओ clear_hash;
	ahash_request_set_crypt(req, शून्य, md5_hash, 0);
	अगर (crypto_ahash_final(req))
		जाओ clear_hash;

	tcp_put_md5sig_pool();
	वापस 0;

clear_hash:
	tcp_put_md5sig_pool();
clear_hash_noput:
	स_रखो(md5_hash, 0, 16);
	वापस 1;
पूर्ण
EXPORT_SYMBOL(tcp_v4_md5_hash_skb);

#पूर्ण_अगर

/* Called with rcu_पढ़ो_lock() */
अटल bool tcp_v4_inbound_md5_hash(स्थिर काष्ठा sock *sk,
				    स्थिर काष्ठा sk_buff *skb,
				    पूर्णांक dअगर, पूर्णांक sdअगर)
अणु
#अगर_घोषित CONFIG_TCP_MD5SIG
	/*
	 * This माला_लो called क्रम each TCP segment that arrives
	 * so we want to be efficient.
	 * We have 3 drop हालs:
	 * o No MD5 hash and one expected.
	 * o MD5 hash and we're not expecting one.
	 * o MD5 hash and its wrong.
	 */
	स्थिर __u8 *hash_location = शून्य;
	काष्ठा tcp_md5sig_key *hash_expected;
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	स्थिर काष्ठा tcphdr *th = tcp_hdr(skb);
	स्थिर जोड़ tcp_md5_addr *addr;
	अचिन्हित अक्षर newhash[16];
	पूर्णांक genhash, l3index;

	/* sdअगर set, means packet ingressed via a device
	 * in an L3 करोमुख्य and dअगर is set to the l3mdev
	 */
	l3index = sdअगर ? dअगर : 0;

	addr = (जोड़ tcp_md5_addr *)&iph->saddr;
	hash_expected = tcp_md5_करो_lookup(sk, l3index, addr, AF_INET);
	hash_location = tcp_parse_md5sig_option(th);

	/* We've parsed the options - करो we have a hash? */
	अगर (!hash_expected && !hash_location)
		वापस false;

	अगर (hash_expected && !hash_location) अणु
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPMD5NOTFOUND);
		वापस true;
	पूर्ण

	अगर (!hash_expected && hash_location) अणु
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPMD5UNEXPECTED);
		वापस true;
	पूर्ण

	/* Okay, so this is hash_expected and hash_location -
	 * so we need to calculate the checksum.
	 */
	genhash = tcp_v4_md5_hash_skb(newhash,
				      hash_expected,
				      शून्य, skb);

	अगर (genhash || स_भेद(hash_location, newhash, 16) != 0) अणु
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPMD5FAILURE);
		net_info_ratelimited("MD5 Hash failed for (%pI4, %d)->(%pI4, %d)%s L3 index %d\n",
				     &iph->saddr, ntohs(th->source),
				     &iph->daddr, ntohs(th->dest),
				     genhash ? " tcp_v4_calc_md5_hash failed"
				     : "", l3index);
		वापस true;
	पूर्ण
	वापस false;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल व्योम tcp_v4_init_req(काष्ठा request_sock *req,
			    स्थिर काष्ठा sock *sk_listener,
			    काष्ठा sk_buff *skb)
अणु
	काष्ठा inet_request_sock *ireq = inet_rsk(req);
	काष्ठा net *net = sock_net(sk_listener);

	sk_rcv_saddr_set(req_to_sk(req), ip_hdr(skb)->daddr);
	sk_daddr_set(req_to_sk(req), ip_hdr(skb)->saddr);
	RCU_INIT_POINTER(ireq->ireq_opt, tcp_v4_save_options(net, skb));
पूर्ण

अटल काष्ठा dst_entry *tcp_v4_route_req(स्थिर काष्ठा sock *sk,
					  काष्ठा sk_buff *skb,
					  काष्ठा flowi *fl,
					  काष्ठा request_sock *req)
अणु
	tcp_v4_init_req(req, sk, skb);

	अगर (security_inet_conn_request(sk, skb, req))
		वापस शून्य;

	वापस inet_csk_route_req(sk, &fl->u.ip4, req);
पूर्ण

काष्ठा request_sock_ops tcp_request_sock_ops __पढ़ो_mostly = अणु
	.family		=	PF_INET,
	.obj_size	=	माप(काष्ठा tcp_request_sock),
	.rtx_syn_ack	=	tcp_rtx_synack,
	.send_ack	=	tcp_v4_reqsk_send_ack,
	.deकाष्ठाor	=	tcp_v4_reqsk_deकाष्ठाor,
	.send_reset	=	tcp_v4_send_reset,
	.syn_ack_समयout =	tcp_syn_ack_समयout,
पूर्ण;

स्थिर काष्ठा tcp_request_sock_ops tcp_request_sock_ipv4_ops = अणु
	.mss_clamp	=	TCP_MSS_DEFAULT,
#अगर_घोषित CONFIG_TCP_MD5SIG
	.req_md5_lookup	=	tcp_v4_md5_lookup,
	.calc_md5_hash	=	tcp_v4_md5_hash_skb,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYN_COOKIES
	.cookie_init_seq =	cookie_v4_init_sequence,
#पूर्ण_अगर
	.route_req	=	tcp_v4_route_req,
	.init_seq	=	tcp_v4_init_seq,
	.init_ts_off	=	tcp_v4_init_ts_off,
	.send_synack	=	tcp_v4_send_synack,
पूर्ण;

पूर्णांक tcp_v4_conn_request(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	/* Never answer to SYNs send to broadcast or multicast */
	अगर (skb_rtable(skb)->rt_flags & (RTCF_BROADCAST | RTCF_MULTICAST))
		जाओ drop;

	वापस tcp_conn_request(&tcp_request_sock_ops,
				&tcp_request_sock_ipv4_ops, sk, skb);

drop:
	tcp_listendrop(sk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tcp_v4_conn_request);


/*
 * The three way handshake has completed - we got a valid synack -
 * now create the new socket.
 */
काष्ठा sock *tcp_v4_syn_recv_sock(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb,
				  काष्ठा request_sock *req,
				  काष्ठा dst_entry *dst,
				  काष्ठा request_sock *req_unhash,
				  bool *own_req)
अणु
	काष्ठा inet_request_sock *ireq;
	bool found_dup_sk = false;
	काष्ठा inet_sock *newinet;
	काष्ठा tcp_sock *newtp;
	काष्ठा sock *newsk;
#अगर_घोषित CONFIG_TCP_MD5SIG
	स्थिर जोड़ tcp_md5_addr *addr;
	काष्ठा tcp_md5sig_key *key;
	पूर्णांक l3index;
#पूर्ण_अगर
	काष्ठा ip_options_rcu *inet_opt;

	अगर (sk_acceptq_is_full(sk))
		जाओ निकास_overflow;

	newsk = tcp_create_खोलोreq_child(sk, req, skb);
	अगर (!newsk)
		जाओ निकास_nonewsk;

	newsk->sk_gso_type = SKB_GSO_TCPV4;
	inet_sk_rx_dst_set(newsk, skb);

	newtp		      = tcp_sk(newsk);
	newinet		      = inet_sk(newsk);
	ireq		      = inet_rsk(req);
	sk_daddr_set(newsk, ireq->ir_rmt_addr);
	sk_rcv_saddr_set(newsk, ireq->ir_loc_addr);
	newsk->sk_bound_dev_अगर = ireq->ir_iअगर;
	newinet->inet_saddr   = ireq->ir_loc_addr;
	inet_opt	      = rcu_dereference(ireq->ireq_opt);
	RCU_INIT_POINTER(newinet->inet_opt, inet_opt);
	newinet->mc_index     = inet_iअगर(skb);
	newinet->mc_ttl	      = ip_hdr(skb)->ttl;
	newinet->rcv_tos      = ip_hdr(skb)->tos;
	inet_csk(newsk)->icsk_ext_hdr_len = 0;
	अगर (inet_opt)
		inet_csk(newsk)->icsk_ext_hdr_len = inet_opt->opt.optlen;
	newinet->inet_id = pअक्रमom_u32();

	/* Set ToS of the new socket based upon the value of incoming SYN.
	 * ECT bits are set later in tcp_init_transfer().
	 */
	अगर (sock_net(sk)->ipv4.sysctl_tcp_reflect_tos)
		newinet->tos = tcp_rsk(req)->syn_tos & ~INET_ECN_MASK;

	अगर (!dst) अणु
		dst = inet_csk_route_child_sock(sk, newsk, req);
		अगर (!dst)
			जाओ put_and_निकास;
	पूर्ण अन्यथा अणु
		/* syncookie हाल : see end of cookie_v4_check() */
	पूर्ण
	sk_setup_caps(newsk, dst);

	tcp_ca_खोलोreq_child(newsk, dst);

	tcp_sync_mss(newsk, dst_mtu(dst));
	newtp->advmss = tcp_mss_clamp(tcp_sk(sk), dst_metric_advmss(dst));

	tcp_initialize_rcv_mss(newsk);

#अगर_घोषित CONFIG_TCP_MD5SIG
	l3index = l3mdev_master_अगरindex_by_index(sock_net(sk), ireq->ir_iअगर);
	/* Copy over the MD5 key from the original socket */
	addr = (जोड़ tcp_md5_addr *)&newinet->inet_daddr;
	key = tcp_md5_करो_lookup(sk, l3index, addr, AF_INET);
	अगर (key) अणु
		/*
		 * We're using one, so create a matching key
		 * on the newsk काष्ठाure. If we fail to get
		 * memory, then we end up not copying the key
		 * across. Shucks.
		 */
		tcp_md5_करो_add(newsk, addr, AF_INET, 32, l3index,
			       key->key, key->keylen, GFP_ATOMIC);
		sk_nocaps_add(newsk, NETIF_F_GSO_MASK);
	पूर्ण
#पूर्ण_अगर

	अगर (__inet_inherit_port(sk, newsk) < 0)
		जाओ put_and_निकास;
	*own_req = inet_ehash_nolisten(newsk, req_to_sk(req_unhash),
				       &found_dup_sk);
	अगर (likely(*own_req)) अणु
		tcp_move_syn(newtp, req);
		ireq->ireq_opt = शून्य;
	पूर्ण अन्यथा अणु
		newinet->inet_opt = शून्य;

		अगर (!req_unhash && found_dup_sk) अणु
			/* This code path should only be executed in the
			 * syncookie हाल only
			 */
			bh_unlock_sock(newsk);
			sock_put(newsk);
			newsk = शून्य;
		पूर्ण
	पूर्ण
	वापस newsk;

निकास_overflow:
	NET_INC_STATS(sock_net(sk), LINUX_MIB_LISTENOVERFLOWS);
निकास_nonewsk:
	dst_release(dst);
निकास:
	tcp_listendrop(sk);
	वापस शून्य;
put_and_निकास:
	newinet->inet_opt = शून्य;
	inet_csk_prepare_क्रमced_बंद(newsk);
	tcp_करोne(newsk);
	जाओ निकास;
पूर्ण
EXPORT_SYMBOL(tcp_v4_syn_recv_sock);

अटल काष्ठा sock *tcp_v4_cookie_check(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_SYN_COOKIES
	स्थिर काष्ठा tcphdr *th = tcp_hdr(skb);

	अगर (!th->syn)
		sk = cookie_v4_check(sk, skb);
#पूर्ण_अगर
	वापस sk;
पूर्ण

u16 tcp_v4_get_syncookie(काष्ठा sock *sk, काष्ठा iphdr *iph,
			 काष्ठा tcphdr *th, u32 *cookie)
अणु
	u16 mss = 0;
#अगर_घोषित CONFIG_SYN_COOKIES
	mss = tcp_get_syncookie_mss(&tcp_request_sock_ops,
				    &tcp_request_sock_ipv4_ops, sk, th);
	अगर (mss) अणु
		*cookie = __cookie_v4_init_sequence(iph, th, &mss);
		tcp_synq_overflow(sk);
	पूर्ण
#पूर्ण_अगर
	वापस mss;
पूर्ण

INसूचीECT_CALLABLE_DECLARE(काष्ठा dst_entry *ipv4_dst_check(काष्ठा dst_entry *,
							   u32));
/* The socket must have it's spinlock held when we get
 * here, unless it is a TCP_LISTEN socket.
 *
 * We have a potential द्विगुन-lock हाल here, so even when
 * करोing backlog processing we use the BH locking scheme.
 * This is because we cannot sleep with the original spinlock
 * held.
 */
पूर्णांक tcp_v4_करो_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *rsk;

	अगर (sk->sk_state == TCP_ESTABLISHED) अणु /* Fast path */
		काष्ठा dst_entry *dst = sk->sk_rx_dst;

		sock_rps_save_rxhash(sk, skb);
		sk_mark_napi_id(sk, skb);
		अगर (dst) अणु
			अगर (inet_sk(sk)->rx_dst_अगरindex != skb->skb_iअगर ||
			    !INसूचीECT_CALL_1(dst->ops->check, ipv4_dst_check,
					     dst, 0)) अणु
				dst_release(dst);
				sk->sk_rx_dst = शून्य;
			पूर्ण
		पूर्ण
		tcp_rcv_established(sk, skb);
		वापस 0;
	पूर्ण

	अगर (tcp_checksum_complete(skb))
		जाओ csum_err;

	अगर (sk->sk_state == TCP_LISTEN) अणु
		काष्ठा sock *nsk = tcp_v4_cookie_check(sk, skb);

		अगर (!nsk)
			जाओ discard;
		अगर (nsk != sk) अणु
			अगर (tcp_child_process(sk, nsk, skb)) अणु
				rsk = nsk;
				जाओ reset;
			पूर्ण
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा
		sock_rps_save_rxhash(sk, skb);

	अगर (tcp_rcv_state_process(sk, skb)) अणु
		rsk = sk;
		जाओ reset;
	पूर्ण
	वापस 0;

reset:
	tcp_v4_send_reset(rsk, skb);
discard:
	kमुक्त_skb(skb);
	/* Be careful here. If this function माला_लो more complicated and
	 * gcc suffers from रेजिस्टर pressure on the x86, sk (in %ebx)
	 * might be destroyed here. This current version compiles correctly,
	 * but you have been warned.
	 */
	वापस 0;

csum_err:
	TCP_INC_STATS(sock_net(sk), TCP_MIB_CSUMERRORS);
	TCP_INC_STATS(sock_net(sk), TCP_MIB_INERRS);
	जाओ discard;
पूर्ण
EXPORT_SYMBOL(tcp_v4_करो_rcv);

पूर्णांक tcp_v4_early_demux(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा iphdr *iph;
	स्थिर काष्ठा tcphdr *th;
	काष्ठा sock *sk;

	अगर (skb->pkt_type != PACKET_HOST)
		वापस 0;

	अगर (!pskb_may_pull(skb, skb_transport_offset(skb) + माप(काष्ठा tcphdr)))
		वापस 0;

	iph = ip_hdr(skb);
	th = tcp_hdr(skb);

	अगर (th->करोff < माप(काष्ठा tcphdr) / 4)
		वापस 0;

	sk = __inet_lookup_established(dev_net(skb->dev), &tcp_hashinfo,
				       iph->saddr, th->source,
				       iph->daddr, ntohs(th->dest),
				       skb->skb_iअगर, inet_sdअगर(skb));
	अगर (sk) अणु
		skb->sk = sk;
		skb->deकाष्ठाor = sock_edemux;
		अगर (sk_fullsock(sk)) अणु
			काष्ठा dst_entry *dst = READ_ONCE(sk->sk_rx_dst);

			अगर (dst)
				dst = dst_check(dst, 0);
			अगर (dst &&
			    inet_sk(sk)->rx_dst_अगरindex == skb->skb_iअगर)
				skb_dst_set_noref(skb, dst);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

bool tcp_add_backlog(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	u32 limit = READ_ONCE(sk->sk_rcvbuf) + READ_ONCE(sk->sk_sndbuf);
	u32 tail_gso_size, tail_gso_segs;
	काष्ठा skb_shared_info *shinfo;
	स्थिर काष्ठा tcphdr *th;
	काष्ठा tcphdr *thtail;
	काष्ठा sk_buff *tail;
	अचिन्हित पूर्णांक hdrlen;
	bool fragstolen;
	u32 gso_segs;
	u32 gso_size;
	पूर्णांक delta;

	/* In हाल all data was pulled from skb frags (in __pskb_pull_tail()),
	 * we can fix skb->truesize to its real value to aव्योम future drops.
	 * This is valid because skb is not yet अक्षरged to the socket.
	 * It has been noticed pure SACK packets were someबार dropped
	 * (अगर cooked by drivers without copyअवरोध feature).
	 */
	skb_condense(skb);

	skb_dst_drop(skb);

	अगर (unlikely(tcp_checksum_complete(skb))) अणु
		bh_unlock_sock(sk);
		__TCP_INC_STATS(sock_net(sk), TCP_MIB_CSUMERRORS);
		__TCP_INC_STATS(sock_net(sk), TCP_MIB_INERRS);
		वापस true;
	पूर्ण

	/* Attempt coalescing to last skb in backlog, even अगर we are
	 * above the limits.
	 * This is okay because skb capacity is limited to MAX_SKB_FRAGS.
	 */
	th = (स्थिर काष्ठा tcphdr *)skb->data;
	hdrlen = th->करोff * 4;

	tail = sk->sk_backlog.tail;
	अगर (!tail)
		जाओ no_coalesce;
	thtail = (काष्ठा tcphdr *)tail->data;

	अगर (TCP_SKB_CB(tail)->end_seq != TCP_SKB_CB(skb)->seq ||
	    TCP_SKB_CB(tail)->ip_dsfield != TCP_SKB_CB(skb)->ip_dsfield ||
	    ((TCP_SKB_CB(tail)->tcp_flags |
	      TCP_SKB_CB(skb)->tcp_flags) & (TCPHDR_SYN | TCPHDR_RST | TCPHDR_URG)) ||
	    !((TCP_SKB_CB(tail)->tcp_flags &
	      TCP_SKB_CB(skb)->tcp_flags) & TCPHDR_ACK) ||
	    ((TCP_SKB_CB(tail)->tcp_flags ^
	      TCP_SKB_CB(skb)->tcp_flags) & (TCPHDR_ECE | TCPHDR_CWR)) ||
#अगर_घोषित CONFIG_TLS_DEVICE
	    tail->decrypted != skb->decrypted ||
#पूर्ण_अगर
	    thtail->करोff != th->करोff ||
	    स_भेद(thtail + 1, th + 1, hdrlen - माप(*th)))
		जाओ no_coalesce;

	__skb_pull(skb, hdrlen);

	shinfo = skb_shinfo(skb);
	gso_size = shinfo->gso_size ?: skb->len;
	gso_segs = shinfo->gso_segs ?: 1;

	shinfo = skb_shinfo(tail);
	tail_gso_size = shinfo->gso_size ?: (tail->len - hdrlen);
	tail_gso_segs = shinfo->gso_segs ?: 1;

	अगर (skb_try_coalesce(tail, skb, &fragstolen, &delta)) अणु
		TCP_SKB_CB(tail)->end_seq = TCP_SKB_CB(skb)->end_seq;

		अगर (likely(!beक्रमe(TCP_SKB_CB(skb)->ack_seq, TCP_SKB_CB(tail)->ack_seq))) अणु
			TCP_SKB_CB(tail)->ack_seq = TCP_SKB_CB(skb)->ack_seq;
			thtail->winकरोw = th->winकरोw;
		पूर्ण

		/* We have to update both TCP_SKB_CB(tail)->tcp_flags and
		 * thtail->fin, so that the fast path in tcp_rcv_established()
		 * is not entered अगर we append a packet with a FIN.
		 * SYN, RST, URG are not present.
		 * ACK is set on both packets.
		 * PSH : we करो not really care in TCP stack,
		 *       at least क्रम 'GRO' packets.
		 */
		thtail->fin |= th->fin;
		TCP_SKB_CB(tail)->tcp_flags |= TCP_SKB_CB(skb)->tcp_flags;

		अगर (TCP_SKB_CB(skb)->has_rxtstamp) अणु
			TCP_SKB_CB(tail)->has_rxtstamp = true;
			tail->tstamp = skb->tstamp;
			skb_hwtstamps(tail)->hwtstamp = skb_hwtstamps(skb)->hwtstamp;
		पूर्ण

		/* Not as strict as GRO. We only need to carry mss max value */
		shinfo->gso_size = max(gso_size, tail_gso_size);
		shinfo->gso_segs = min_t(u32, gso_segs + tail_gso_segs, 0xFFFF);

		sk->sk_backlog.len += delta;
		__NET_INC_STATS(sock_net(sk),
				LINUX_MIB_TCPBACKLOGCOALESCE);
		kमुक्त_skb_partial(skb, fragstolen);
		वापस false;
	पूर्ण
	__skb_push(skb, hdrlen);

no_coalesce:
	/* Only socket owner can try to collapse/prune rx queues
	 * to reduce memory overhead, so add a little headroom here.
	 * Few sockets backlog are possibly concurrently non empty.
	 */
	limit += 64*1024;

	अगर (unlikely(sk_add_backlog(sk, skb, limit))) अणु
		bh_unlock_sock(sk);
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPBACKLOGDROP);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL(tcp_add_backlog);

पूर्णांक tcp_filter(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा tcphdr *th = (काष्ठा tcphdr *)skb->data;

	वापस sk_filter_trim_cap(sk, skb, th->करोff * 4);
पूर्ण
EXPORT_SYMBOL(tcp_filter);

अटल व्योम tcp_v4_restore_cb(काष्ठा sk_buff *skb)
अणु
	स_हटाओ(IPCB(skb), &TCP_SKB_CB(skb)->header.h4,
		माप(काष्ठा inet_skb_parm));
पूर्ण

अटल व्योम tcp_v4_fill_cb(काष्ठा sk_buff *skb, स्थिर काष्ठा iphdr *iph,
			   स्थिर काष्ठा tcphdr *th)
अणु
	/* This is tricky : We move IPCB at its correct location पूर्णांकo TCP_SKB_CB()
	 * barrier() makes sure compiler wont play fool^Waliasing games.
	 */
	स_हटाओ(&TCP_SKB_CB(skb)->header.h4, IPCB(skb),
		माप(काष्ठा inet_skb_parm));
	barrier();

	TCP_SKB_CB(skb)->seq = ntohl(th->seq);
	TCP_SKB_CB(skb)->end_seq = (TCP_SKB_CB(skb)->seq + th->syn + th->fin +
				    skb->len - th->करोff * 4);
	TCP_SKB_CB(skb)->ack_seq = ntohl(th->ack_seq);
	TCP_SKB_CB(skb)->tcp_flags = tcp_flag_byte(th);
	TCP_SKB_CB(skb)->tcp_tw_isn = 0;
	TCP_SKB_CB(skb)->ip_dsfield = ipv4_get_dsfield(iph);
	TCP_SKB_CB(skb)->sacked	 = 0;
	TCP_SKB_CB(skb)->has_rxtstamp =
			skb->tstamp || skb_hwtstamps(skb)->hwtstamp;
पूर्ण

/*
 *	From tcp_input.c
 */

पूर्णांक tcp_v4_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा sk_buff *skb_to_मुक्त;
	पूर्णांक sdअगर = inet_sdअगर(skb);
	पूर्णांक dअगर = inet_iअगर(skb);
	स्थिर काष्ठा iphdr *iph;
	स्थिर काष्ठा tcphdr *th;
	bool refcounted;
	काष्ठा sock *sk;
	पूर्णांक ret;

	अगर (skb->pkt_type != PACKET_HOST)
		जाओ discard_it;

	/* Count it even अगर it's bad */
	__TCP_INC_STATS(net, TCP_MIB_INSEGS);

	अगर (!pskb_may_pull(skb, माप(काष्ठा tcphdr)))
		जाओ discard_it;

	th = (स्थिर काष्ठा tcphdr *)skb->data;

	अगर (unlikely(th->करोff < माप(काष्ठा tcphdr) / 4))
		जाओ bad_packet;
	अगर (!pskb_may_pull(skb, th->करोff * 4))
		जाओ discard_it;

	/* An explanation is required here, I think.
	 * Packet length and करोff are validated by header prediction,
	 * provided हाल of th->करोff==0 is eliminated.
	 * So, we defer the checks. */

	अगर (skb_checksum_init(skb, IPPROTO_TCP, inet_compute_pseuकरो))
		जाओ csum_error;

	th = (स्थिर काष्ठा tcphdr *)skb->data;
	iph = ip_hdr(skb);
lookup:
	sk = __inet_lookup_skb(&tcp_hashinfo, skb, __tcp_hdrlen(th), th->source,
			       th->dest, sdअगर, &refcounted);
	अगर (!sk)
		जाओ no_tcp_socket;

process:
	अगर (sk->sk_state == TCP_TIME_WAIT)
		जाओ करो_समय_रुको;

	अगर (sk->sk_state == TCP_NEW_SYN_RECV) अणु
		काष्ठा request_sock *req = inet_reqsk(sk);
		bool req_stolen = false;
		काष्ठा sock *nsk;

		sk = req->rsk_listener;
		अगर (unlikely(tcp_v4_inbound_md5_hash(sk, skb, dअगर, sdअगर))) अणु
			sk_drops_add(sk, skb);
			reqsk_put(req);
			जाओ discard_it;
		पूर्ण
		अगर (tcp_checksum_complete(skb)) अणु
			reqsk_put(req);
			जाओ csum_error;
		पूर्ण
		अगर (unlikely(sk->sk_state != TCP_LISTEN)) अणु
			inet_csk_reqsk_queue_drop_and_put(sk, req);
			जाओ lookup;
		पूर्ण
		/* We own a reference on the listener, increase it again
		 * as we might lose it too soon.
		 */
		sock_hold(sk);
		refcounted = true;
		nsk = शून्य;
		अगर (!tcp_filter(sk, skb)) अणु
			th = (स्थिर काष्ठा tcphdr *)skb->data;
			iph = ip_hdr(skb);
			tcp_v4_fill_cb(skb, iph, th);
			nsk = tcp_check_req(sk, skb, req, false, &req_stolen);
		पूर्ण
		अगर (!nsk) अणु
			reqsk_put(req);
			अगर (req_stolen) अणु
				/* Another cpu got exclusive access to req
				 * and created a full blown socket.
				 * Try to feed this packet to this socket
				 * instead of discarding it.
				 */
				tcp_v4_restore_cb(skb);
				sock_put(sk);
				जाओ lookup;
			पूर्ण
			जाओ discard_and_rअन्यथा;
		पूर्ण
		अगर (nsk == sk) अणु
			reqsk_put(req);
			tcp_v4_restore_cb(skb);
		पूर्ण अन्यथा अगर (tcp_child_process(sk, nsk, skb)) अणु
			tcp_v4_send_reset(nsk, skb);
			जाओ discard_and_rअन्यथा;
		पूर्ण अन्यथा अणु
			sock_put(sk);
			वापस 0;
		पूर्ण
	पूर्ण
	अगर (unlikely(iph->ttl < inet_sk(sk)->min_ttl)) अणु
		__NET_INC_STATS(net, LINUX_MIB_TCPMINTTLDROP);
		जाओ discard_and_rअन्यथा;
	पूर्ण

	अगर (!xfrm4_policy_check(sk, XFRM_POLICY_IN, skb))
		जाओ discard_and_rअन्यथा;

	अगर (tcp_v4_inbound_md5_hash(sk, skb, dअगर, sdअगर))
		जाओ discard_and_rअन्यथा;

	nf_reset_ct(skb);

	अगर (tcp_filter(sk, skb))
		जाओ discard_and_rअन्यथा;
	th = (स्थिर काष्ठा tcphdr *)skb->data;
	iph = ip_hdr(skb);
	tcp_v4_fill_cb(skb, iph, th);

	skb->dev = शून्य;

	अगर (sk->sk_state == TCP_LISTEN) अणु
		ret = tcp_v4_करो_rcv(sk, skb);
		जाओ put_and_वापस;
	पूर्ण

	sk_incoming_cpu_update(sk);

	bh_lock_sock_nested(sk);
	tcp_segs_in(tcp_sk(sk), skb);
	ret = 0;
	अगर (!sock_owned_by_user(sk)) अणु
		skb_to_मुक्त = sk->sk_rx_skb_cache;
		sk->sk_rx_skb_cache = शून्य;
		ret = tcp_v4_करो_rcv(sk, skb);
	पूर्ण अन्यथा अणु
		अगर (tcp_add_backlog(sk, skb))
			जाओ discard_and_rअन्यथा;
		skb_to_मुक्त = शून्य;
	पूर्ण
	bh_unlock_sock(sk);
	अगर (skb_to_मुक्त)
		__kमुक्त_skb(skb_to_मुक्त);

put_and_वापस:
	अगर (refcounted)
		sock_put(sk);

	वापस ret;

no_tcp_socket:
	अगर (!xfrm4_policy_check(शून्य, XFRM_POLICY_IN, skb))
		जाओ discard_it;

	tcp_v4_fill_cb(skb, iph, th);

	अगर (tcp_checksum_complete(skb)) अणु
csum_error:
		__TCP_INC_STATS(net, TCP_MIB_CSUMERRORS);
bad_packet:
		__TCP_INC_STATS(net, TCP_MIB_INERRS);
	पूर्ण अन्यथा अणु
		tcp_v4_send_reset(शून्य, skb);
	पूर्ण

discard_it:
	/* Discard frame. */
	kमुक्त_skb(skb);
	वापस 0;

discard_and_rअन्यथा:
	sk_drops_add(sk, skb);
	अगर (refcounted)
		sock_put(sk);
	जाओ discard_it;

करो_समय_रुको:
	अगर (!xfrm4_policy_check(शून्य, XFRM_POLICY_IN, skb)) अणु
		inet_twsk_put(inet_twsk(sk));
		जाओ discard_it;
	पूर्ण

	tcp_v4_fill_cb(skb, iph, th);

	अगर (tcp_checksum_complete(skb)) अणु
		inet_twsk_put(inet_twsk(sk));
		जाओ csum_error;
	पूर्ण
	चयन (tcp_समयरुको_state_process(inet_twsk(sk), skb, th)) अणु
	हाल TCP_TW_SYN: अणु
		काष्ठा sock *sk2 = inet_lookup_listener(dev_net(skb->dev),
							&tcp_hashinfo, skb,
							__tcp_hdrlen(th),
							iph->saddr, th->source,
							iph->daddr, th->dest,
							inet_iअगर(skb),
							sdअगर);
		अगर (sk2) अणु
			inet_twsk_deschedule_put(inet_twsk(sk));
			sk = sk2;
			tcp_v4_restore_cb(skb);
			refcounted = false;
			जाओ process;
		पूर्ण
	पूर्ण
		/* to ACK */
		fallthrough;
	हाल TCP_TW_ACK:
		tcp_v4_समयरुको_ack(sk, skb);
		अवरोध;
	हाल TCP_TW_RST:
		tcp_v4_send_reset(sk, skb);
		inet_twsk_deschedule_put(inet_twsk(sk));
		जाओ discard_it;
	हाल TCP_TW_SUCCESS:;
	पूर्ण
	जाओ discard_it;
पूर्ण

अटल काष्ठा समयरुको_sock_ops tcp_समयरुको_sock_ops = अणु
	.twsk_obj_size	= माप(काष्ठा tcp_समयरुको_sock),
	.twsk_unique	= tcp_twsk_unique,
	.twsk_deकाष्ठाor= tcp_twsk_deकाष्ठाor,
पूर्ण;

व्योम inet_sk_rx_dst_set(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);

	अगर (dst && dst_hold_safe(dst)) अणु
		sk->sk_rx_dst = dst;
		inet_sk(sk)->rx_dst_अगरindex = skb->skb_iअगर;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(inet_sk_rx_dst_set);

स्थिर काष्ठा inet_connection_sock_af_ops ipv4_specअगरic = अणु
	.queue_xmit	   = ip_queue_xmit,
	.send_check	   = tcp_v4_send_check,
	.rebuild_header	   = inet_sk_rebuild_header,
	.sk_rx_dst_set	   = inet_sk_rx_dst_set,
	.conn_request	   = tcp_v4_conn_request,
	.syn_recv_sock	   = tcp_v4_syn_recv_sock,
	.net_header_len	   = माप(काष्ठा iphdr),
	.setsockopt	   = ip_setsockopt,
	.माला_लोockopt	   = ip_माला_लोockopt,
	.addr2sockaddr	   = inet_csk_addr2sockaddr,
	.sockaddr_len	   = माप(काष्ठा sockaddr_in),
	.mtu_reduced	   = tcp_v4_mtu_reduced,
पूर्ण;
EXPORT_SYMBOL(ipv4_specअगरic);

#अगर_घोषित CONFIG_TCP_MD5SIG
अटल स्थिर काष्ठा tcp_sock_af_ops tcp_sock_ipv4_specअगरic = अणु
	.md5_lookup		= tcp_v4_md5_lookup,
	.calc_md5_hash		= tcp_v4_md5_hash_skb,
	.md5_parse		= tcp_v4_parse_md5_keys,
पूर्ण;
#पूर्ण_अगर

/* NOTE: A lot of things set to zero explicitly by call to
 *       sk_alloc() so need not be करोne here.
 */
अटल पूर्णांक tcp_v4_init_sock(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	tcp_init_sock(sk);

	icsk->icsk_af_ops = &ipv4_specअगरic;

#अगर_घोषित CONFIG_TCP_MD5SIG
	tcp_sk(sk)->af_specअगरic = &tcp_sock_ipv4_specअगरic;
#पूर्ण_अगर

	वापस 0;
पूर्ण

व्योम tcp_v4_destroy_sock(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	trace_tcp_destroy_sock(sk);

	tcp_clear_xmit_समयrs(sk);

	tcp_cleanup_congestion_control(sk);

	tcp_cleanup_ulp(sk);

	/* Cleanup up the ग_लिखो buffer. */
	tcp_ग_लिखो_queue_purge(sk);

	/* Check अगर we want to disable active TFO */
	tcp_fastखोलो_active_disable_ofo_check(sk);

	/* Cleans up our, hopefully empty, out_of_order_queue. */
	skb_rbtree_purge(&tp->out_of_order_queue);

#अगर_घोषित CONFIG_TCP_MD5SIG
	/* Clean up the MD5 key list, अगर any */
	अगर (tp->md5sig_info) अणु
		tcp_clear_md5_list(sk);
		kमुक्त_rcu(rcu_dereference_रक्षित(tp->md5sig_info, 1), rcu);
		tp->md5sig_info = शून्य;
	पूर्ण
#पूर्ण_अगर

	/* Clean up a referenced TCP bind bucket. */
	अगर (inet_csk(sk)->icsk_bind_hash)
		inet_put_port(sk);

	BUG_ON(rcu_access_poपूर्णांकer(tp->fastखोलो_rsk));

	/* If socket is पातed during connect operation */
	tcp_मुक्त_fastखोलो_req(tp);
	tcp_fastखोलो_destroy_cipher(sk);
	tcp_saved_syn_मुक्त(tp);

	sk_sockets_allocated_dec(sk);
पूर्ण
EXPORT_SYMBOL(tcp_v4_destroy_sock);

#अगर_घोषित CONFIG_PROC_FS
/* Proc fileप्रणाली TCP sock list dumping. */

/*
 * Get next listener socket follow cur.  If cur is शून्य, get first socket
 * starting from bucket given in st->bucket; when st->bucket is zero the
 * very first socket in the hash table is वापसed.
 */
अटल व्योम *listening_get_next(काष्ठा seq_file *seq, व्योम *cur)
अणु
	काष्ठा tcp_seq_afinfo *afinfo;
	काष्ठा tcp_iter_state *st = seq->निजी;
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा inet_listen_hashbucket *ilb;
	काष्ठा hlist_nulls_node *node;
	काष्ठा sock *sk = cur;

	अगर (st->bpf_seq_afinfo)
		afinfo = st->bpf_seq_afinfo;
	अन्यथा
		afinfo = PDE_DATA(file_inode(seq->file));

	अगर (!sk) अणु
get_head:
		ilb = &tcp_hashinfo.listening_hash[st->bucket];
		spin_lock(&ilb->lock);
		sk = sk_nulls_head(&ilb->nulls_head);
		st->offset = 0;
		जाओ get_sk;
	पूर्ण
	ilb = &tcp_hashinfo.listening_hash[st->bucket];
	++st->num;
	++st->offset;

	sk = sk_nulls_next(sk);
get_sk:
	sk_nulls_क्रम_each_from(sk, node) अणु
		अगर (!net_eq(sock_net(sk), net))
			जारी;
		अगर (afinfo->family == AF_UNSPEC ||
		    sk->sk_family == afinfo->family)
			वापस sk;
	पूर्ण
	spin_unlock(&ilb->lock);
	st->offset = 0;
	अगर (++st->bucket < INET_LHTABLE_SIZE)
		जाओ get_head;
	वापस शून्य;
पूर्ण

अटल व्योम *listening_get_idx(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा tcp_iter_state *st = seq->निजी;
	व्योम *rc;

	st->bucket = 0;
	st->offset = 0;
	rc = listening_get_next(seq, शून्य);

	जबतक (rc && *pos) अणु
		rc = listening_get_next(seq, rc);
		--*pos;
	पूर्ण
	वापस rc;
पूर्ण

अटल अंतरभूत bool empty_bucket(स्थिर काष्ठा tcp_iter_state *st)
अणु
	वापस hlist_nulls_empty(&tcp_hashinfo.ehash[st->bucket].chain);
पूर्ण

/*
 * Get first established socket starting from bucket given in st->bucket.
 * If st->bucket is zero, the very first socket in the hash is वापसed.
 */
अटल व्योम *established_get_first(काष्ठा seq_file *seq)
अणु
	काष्ठा tcp_seq_afinfo *afinfo;
	काष्ठा tcp_iter_state *st = seq->निजी;
	काष्ठा net *net = seq_file_net(seq);
	व्योम *rc = शून्य;

	अगर (st->bpf_seq_afinfo)
		afinfo = st->bpf_seq_afinfo;
	अन्यथा
		afinfo = PDE_DATA(file_inode(seq->file));

	st->offset = 0;
	क्रम (; st->bucket <= tcp_hashinfo.ehash_mask; ++st->bucket) अणु
		काष्ठा sock *sk;
		काष्ठा hlist_nulls_node *node;
		spinlock_t *lock = inet_ehash_lockp(&tcp_hashinfo, st->bucket);

		/* Lockless fast path क्रम the common हाल of empty buckets */
		अगर (empty_bucket(st))
			जारी;

		spin_lock_bh(lock);
		sk_nulls_क्रम_each(sk, node, &tcp_hashinfo.ehash[st->bucket].chain) अणु
			अगर ((afinfo->family != AF_UNSPEC &&
			     sk->sk_family != afinfo->family) ||
			    !net_eq(sock_net(sk), net)) अणु
				जारी;
			पूर्ण
			rc = sk;
			जाओ out;
		पूर्ण
		spin_unlock_bh(lock);
	पूर्ण
out:
	वापस rc;
पूर्ण

अटल व्योम *established_get_next(काष्ठा seq_file *seq, व्योम *cur)
अणु
	काष्ठा tcp_seq_afinfo *afinfo;
	काष्ठा sock *sk = cur;
	काष्ठा hlist_nulls_node *node;
	काष्ठा tcp_iter_state *st = seq->निजी;
	काष्ठा net *net = seq_file_net(seq);

	अगर (st->bpf_seq_afinfo)
		afinfo = st->bpf_seq_afinfo;
	अन्यथा
		afinfo = PDE_DATA(file_inode(seq->file));

	++st->num;
	++st->offset;

	sk = sk_nulls_next(sk);

	sk_nulls_क्रम_each_from(sk, node) अणु
		अगर ((afinfo->family == AF_UNSPEC ||
		     sk->sk_family == afinfo->family) &&
		    net_eq(sock_net(sk), net))
			वापस sk;
	पूर्ण

	spin_unlock_bh(inet_ehash_lockp(&tcp_hashinfo, st->bucket));
	++st->bucket;
	वापस established_get_first(seq);
पूर्ण

अटल व्योम *established_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा tcp_iter_state *st = seq->निजी;
	व्योम *rc;

	st->bucket = 0;
	rc = established_get_first(seq);

	जबतक (rc && pos) अणु
		rc = established_get_next(seq, rc);
		--pos;
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम *tcp_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	व्योम *rc;
	काष्ठा tcp_iter_state *st = seq->निजी;

	st->state = TCP_SEQ_STATE_LISTENING;
	rc	  = listening_get_idx(seq, &pos);

	अगर (!rc) अणु
		st->state = TCP_SEQ_STATE_ESTABLISHED;
		rc	  = established_get_idx(seq, pos);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम *tcp_seek_last_pos(काष्ठा seq_file *seq)
अणु
	काष्ठा tcp_iter_state *st = seq->निजी;
	पूर्णांक offset = st->offset;
	पूर्णांक orig_num = st->num;
	व्योम *rc = शून्य;

	चयन (st->state) अणु
	हाल TCP_SEQ_STATE_LISTENING:
		अगर (st->bucket >= INET_LHTABLE_SIZE)
			अवरोध;
		st->state = TCP_SEQ_STATE_LISTENING;
		rc = listening_get_next(seq, शून्य);
		जबतक (offset-- && rc)
			rc = listening_get_next(seq, rc);
		अगर (rc)
			अवरोध;
		st->bucket = 0;
		st->state = TCP_SEQ_STATE_ESTABLISHED;
		fallthrough;
	हाल TCP_SEQ_STATE_ESTABLISHED:
		अगर (st->bucket > tcp_hashinfo.ehash_mask)
			अवरोध;
		rc = established_get_first(seq);
		जबतक (offset-- && rc)
			rc = established_get_next(seq, rc);
	पूर्ण

	st->num = orig_num;

	वापस rc;
पूर्ण

व्योम *tcp_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा tcp_iter_state *st = seq->निजी;
	व्योम *rc;

	अगर (*pos && *pos == st->last_pos) अणु
		rc = tcp_seek_last_pos(seq);
		अगर (rc)
			जाओ out;
	पूर्ण

	st->state = TCP_SEQ_STATE_LISTENING;
	st->num = 0;
	st->bucket = 0;
	st->offset = 0;
	rc = *pos ? tcp_get_idx(seq, *pos - 1) : SEQ_START_TOKEN;

out:
	st->last_pos = *pos;
	वापस rc;
पूर्ण
EXPORT_SYMBOL(tcp_seq_start);

व्योम *tcp_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा tcp_iter_state *st = seq->निजी;
	व्योम *rc = शून्य;

	अगर (v == SEQ_START_TOKEN) अणु
		rc = tcp_get_idx(seq, 0);
		जाओ out;
	पूर्ण

	चयन (st->state) अणु
	हाल TCP_SEQ_STATE_LISTENING:
		rc = listening_get_next(seq, v);
		अगर (!rc) अणु
			st->state = TCP_SEQ_STATE_ESTABLISHED;
			st->bucket = 0;
			st->offset = 0;
			rc	  = established_get_first(seq);
		पूर्ण
		अवरोध;
	हाल TCP_SEQ_STATE_ESTABLISHED:
		rc = established_get_next(seq, v);
		अवरोध;
	पूर्ण
out:
	++*pos;
	st->last_pos = *pos;
	वापस rc;
पूर्ण
EXPORT_SYMBOL(tcp_seq_next);

व्योम tcp_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा tcp_iter_state *st = seq->निजी;

	चयन (st->state) अणु
	हाल TCP_SEQ_STATE_LISTENING:
		अगर (v != SEQ_START_TOKEN)
			spin_unlock(&tcp_hashinfo.listening_hash[st->bucket].lock);
		अवरोध;
	हाल TCP_SEQ_STATE_ESTABLISHED:
		अगर (v)
			spin_unlock_bh(inet_ehash_lockp(&tcp_hashinfo, st->bucket));
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(tcp_seq_stop);

अटल व्योम get_खोलोreq4(स्थिर काष्ठा request_sock *req,
			 काष्ठा seq_file *f, पूर्णांक i)
अणु
	स्थिर काष्ठा inet_request_sock *ireq = inet_rsk(req);
	दीर्घ delta = req->rsk_समयr.expires - jअगरfies;

	seq_म_लिखो(f, "%4d: %08X:%04X %08X:%04X"
		" %02X %08X:%08X %02X:%08lX %08X %5u %8d %u %d %pK",
		i,
		ireq->ir_loc_addr,
		ireq->ir_num,
		ireq->ir_rmt_addr,
		ntohs(ireq->ir_rmt_port),
		TCP_SYN_RECV,
		0, 0, /* could prपूर्णांक option size, but that is af dependent. */
		1,    /* समयrs active (only the expire समयr) */
		jअगरfies_delta_to_घड़ी_प्रकार(delta),
		req->num_समयout,
		from_kuid_munged(seq_user_ns(f),
				 sock_i_uid(req->rsk_listener)),
		0,  /* non standard समयr */
		0, /* खोलो_requests have no inode */
		0,
		req);
पूर्ण

अटल व्योम get_tcp4_sock(काष्ठा sock *sk, काष्ठा seq_file *f, पूर्णांक i)
अणु
	पूर्णांक समयr_active;
	अचिन्हित दीर्घ समयr_expires;
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	स्थिर काष्ठा inet_sock *inet = inet_sk(sk);
	स्थिर काष्ठा fastखोलो_queue *fastखोलोq = &icsk->icsk_accept_queue.fastखोलोq;
	__be32 dest = inet->inet_daddr;
	__be32 src = inet->inet_rcv_saddr;
	__u16 destp = ntohs(inet->inet_dport);
	__u16 srcp = ntohs(inet->inet_sport);
	पूर्णांक rx_queue;
	पूर्णांक state;

	अगर (icsk->icsk_pending == ICSK_TIME_RETRANS ||
	    icsk->icsk_pending == ICSK_TIME_REO_TIMEOUT ||
	    icsk->icsk_pending == ICSK_TIME_LOSS_PROBE) अणु
		समयr_active	= 1;
		समयr_expires	= icsk->icsk_समयout;
	पूर्ण अन्यथा अगर (icsk->icsk_pending == ICSK_TIME_PROBE0) अणु
		समयr_active	= 4;
		समयr_expires	= icsk->icsk_समयout;
	पूर्ण अन्यथा अगर (समयr_pending(&sk->sk_समयr)) अणु
		समयr_active	= 2;
		समयr_expires	= sk->sk_समयr.expires;
	पूर्ण अन्यथा अणु
		समयr_active	= 0;
		समयr_expires = jअगरfies;
	पूर्ण

	state = inet_sk_state_load(sk);
	अगर (state == TCP_LISTEN)
		rx_queue = READ_ONCE(sk->sk_ack_backlog);
	अन्यथा
		/* Because we करोn't lock the socket,
		 * we might find a transient negative value.
		 */
		rx_queue = max_t(पूर्णांक, READ_ONCE(tp->rcv_nxt) -
				      READ_ONCE(tp->copied_seq), 0);

	seq_म_लिखो(f, "%4d: %08X:%04X %08X:%04X %02X %08X:%08X %02X:%08lX "
			"%08X %5u %8d %lu %d %pK %lu %lu %u %u %d",
		i, src, srcp, dest, destp, state,
		READ_ONCE(tp->ग_लिखो_seq) - tp->snd_una,
		rx_queue,
		समयr_active,
		jअगरfies_delta_to_घड़ी_प्रकार(समयr_expires - jअगरfies),
		icsk->icsk_retransmits,
		from_kuid_munged(seq_user_ns(f), sock_i_uid(sk)),
		icsk->icsk_probes_out,
		sock_i_ino(sk),
		refcount_पढ़ो(&sk->sk_refcnt), sk,
		jअगरfies_to_घड़ी_प्रकार(icsk->icsk_rto),
		jअगरfies_to_घड़ी_प्रकार(icsk->icsk_ack.ato),
		(icsk->icsk_ack.quick << 1) | inet_csk_in_pingpong_mode(sk),
		tp->snd_cwnd,
		state == TCP_LISTEN ?
		    fastखोलोq->max_qlen :
		    (tcp_in_initial_slowstart(tp) ? -1 : tp->snd_ssthresh));
पूर्ण

अटल व्योम get_समयरुको4_sock(स्थिर काष्ठा inet_समयरुको_sock *tw,
			       काष्ठा seq_file *f, पूर्णांक i)
अणु
	दीर्घ delta = tw->tw_समयr.expires - jअगरfies;
	__be32 dest, src;
	__u16 destp, srcp;

	dest  = tw->tw_daddr;
	src   = tw->tw_rcv_saddr;
	destp = ntohs(tw->tw_dport);
	srcp  = ntohs(tw->tw_sport);

	seq_म_लिखो(f, "%4d: %08X:%04X %08X:%04X"
		" %02X %08X:%08X %02X:%08lX %08X %5d %8d %d %d %pK",
		i, src, srcp, dest, destp, tw->tw_substate, 0, 0,
		3, jअगरfies_delta_to_घड़ी_प्रकार(delta), 0, 0, 0, 0,
		refcount_पढ़ो(&tw->tw_refcnt), tw);
पूर्ण

#घोषणा TMPSZ 150

अटल पूर्णांक tcp4_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा tcp_iter_state *st;
	काष्ठा sock *sk = v;

	seq_setwidth(seq, TMPSZ - 1);
	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "  sl  local_address rem_address   st tx_queue "
			   "rx_queue tr tm->when retrnsmt   uid  timeout "
			   "inode");
		जाओ out;
	पूर्ण
	st = seq->निजी;

	अगर (sk->sk_state == TCP_TIME_WAIT)
		get_समयरुको4_sock(v, seq, st->num);
	अन्यथा अगर (sk->sk_state == TCP_NEW_SYN_RECV)
		get_खोलोreq4(v, seq, st->num);
	अन्यथा
		get_tcp4_sock(v, seq, st->num);
out:
	seq_pad(seq, '\n');
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_BPF_SYSCALL
काष्ठा bpf_iter__tcp अणु
	__bpf_md_ptr(काष्ठा bpf_iter_meta *, meta);
	__bpf_md_ptr(काष्ठा sock_common *, sk_common);
	uid_t uid __aligned(8);
पूर्ण;

अटल पूर्णांक tcp_prog_seq_show(काष्ठा bpf_prog *prog, काष्ठा bpf_iter_meta *meta,
			     काष्ठा sock_common *sk_common, uid_t uid)
अणु
	काष्ठा bpf_iter__tcp ctx;

	meta->seq_num--;  /* skip SEQ_START_TOKEN */
	ctx.meta = meta;
	ctx.sk_common = sk_common;
	ctx.uid = uid;
	वापस bpf_iter_run_prog(prog, &ctx);
पूर्ण

अटल पूर्णांक bpf_iter_tcp_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा bpf_iter_meta meta;
	काष्ठा bpf_prog *prog;
	काष्ठा sock *sk = v;
	uid_t uid;

	अगर (v == SEQ_START_TOKEN)
		वापस 0;

	अगर (sk->sk_state == TCP_TIME_WAIT) अणु
		uid = 0;
	पूर्ण अन्यथा अगर (sk->sk_state == TCP_NEW_SYN_RECV) अणु
		स्थिर काष्ठा request_sock *req = v;

		uid = from_kuid_munged(seq_user_ns(seq),
				       sock_i_uid(req->rsk_listener));
	पूर्ण अन्यथा अणु
		uid = from_kuid_munged(seq_user_ns(seq), sock_i_uid(sk));
	पूर्ण

	meta.seq = seq;
	prog = bpf_iter_get_info(&meta, false);
	वापस tcp_prog_seq_show(prog, &meta, v, uid);
पूर्ण

अटल व्योम bpf_iter_tcp_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा bpf_iter_meta meta;
	काष्ठा bpf_prog *prog;

	अगर (!v) अणु
		meta.seq = seq;
		prog = bpf_iter_get_info(&meta, true);
		अगर (prog)
			(व्योम)tcp_prog_seq_show(prog, &meta, v, 0);
	पूर्ण

	tcp_seq_stop(seq, v);
पूर्ण

अटल स्थिर काष्ठा seq_operations bpf_iter_tcp_seq_ops = अणु
	.show		= bpf_iter_tcp_seq_show,
	.start		= tcp_seq_start,
	.next		= tcp_seq_next,
	.stop		= bpf_iter_tcp_seq_stop,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा seq_operations tcp4_seq_ops = अणु
	.show		= tcp4_seq_show,
	.start		= tcp_seq_start,
	.next		= tcp_seq_next,
	.stop		= tcp_seq_stop,
पूर्ण;

अटल काष्ठा tcp_seq_afinfo tcp4_seq_afinfo = अणु
	.family		= AF_INET,
पूर्ण;

अटल पूर्णांक __net_init tcp4_proc_init_net(काष्ठा net *net)
अणु
	अगर (!proc_create_net_data("tcp", 0444, net->proc_net, &tcp4_seq_ops,
			माप(काष्ठा tcp_iter_state), &tcp4_seq_afinfo))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम __net_निकास tcp4_proc_निकास_net(काष्ठा net *net)
अणु
	हटाओ_proc_entry("tcp", net->proc_net);
पूर्ण

अटल काष्ठा pernet_operations tcp4_net_ops = अणु
	.init = tcp4_proc_init_net,
	.निकास = tcp4_proc_निकास_net,
पूर्ण;

पूर्णांक __init tcp4_proc_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&tcp4_net_ops);
पूर्ण

व्योम tcp4_proc_निकास(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&tcp4_net_ops);
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

/* @wake is one when sk_stream_ग_लिखो_space() calls us.
 * This sends EPOLLOUT only अगर notsent_bytes is half the limit.
 * This mimics the strategy used in sock_def_ग_लिखो_space().
 */
bool tcp_stream_memory_मुक्त(स्थिर काष्ठा sock *sk, पूर्णांक wake)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 notsent_bytes = READ_ONCE(tp->ग_लिखो_seq) -
			    READ_ONCE(tp->snd_nxt);

	वापस (notsent_bytes << wake) < tcp_notsent_lowat(tp);
पूर्ण
EXPORT_SYMBOL(tcp_stream_memory_मुक्त);

काष्ठा proto tcp_prot = अणु
	.name			= "TCP",
	.owner			= THIS_MODULE,
	.बंद			= tcp_बंद,
	.pre_connect		= tcp_v4_pre_connect,
	.connect		= tcp_v4_connect,
	.disconnect		= tcp_disconnect,
	.accept			= inet_csk_accept,
	.ioctl			= tcp_ioctl,
	.init			= tcp_v4_init_sock,
	.destroy		= tcp_v4_destroy_sock,
	.shutकरोwn		= tcp_shutकरोwn,
	.setsockopt		= tcp_setsockopt,
	.माला_लोockopt		= tcp_माला_लोockopt,
	.bpf_bypass_माला_लोockopt	= tcp_bpf_bypass_माला_लोockopt,
	.keepalive		= tcp_set_keepalive,
	.recvmsg		= tcp_recvmsg,
	.sendmsg		= tcp_sendmsg,
	.sendpage		= tcp_sendpage,
	.backlog_rcv		= tcp_v4_करो_rcv,
	.release_cb		= tcp_release_cb,
	.hash			= inet_hash,
	.unhash			= inet_unhash,
	.get_port		= inet_csk_get_port,
#अगर_घोषित CONFIG_BPF_SYSCALL
	.psock_update_sk_prot	= tcp_bpf_update_proto,
#पूर्ण_अगर
	.enter_memory_pressure	= tcp_enter_memory_pressure,
	.leave_memory_pressure	= tcp_leave_memory_pressure,
	.stream_memory_मुक्त	= tcp_stream_memory_मुक्त,
	.sockets_allocated	= &tcp_sockets_allocated,
	.orphan_count		= &tcp_orphan_count,
	.memory_allocated	= &tcp_memory_allocated,
	.memory_pressure	= &tcp_memory_pressure,
	.sysctl_mem		= sysctl_tcp_mem,
	.sysctl_wmem_offset	= दुरत्व(काष्ठा net, ipv4.sysctl_tcp_wmem),
	.sysctl_rmem_offset	= दुरत्व(काष्ठा net, ipv4.sysctl_tcp_rmem),
	.max_header		= MAX_TCP_HEADER,
	.obj_size		= माप(काष्ठा tcp_sock),
	.slab_flags		= SLAB_TYPESAFE_BY_RCU,
	.twsk_prot		= &tcp_समयरुको_sock_ops,
	.rsk_prot		= &tcp_request_sock_ops,
	.h.hashinfo		= &tcp_hashinfo,
	.no_स्वतःbind		= true,
	.diag_destroy		= tcp_पात,
पूर्ण;
EXPORT_SYMBOL(tcp_prot);

अटल व्योम __net_निकास tcp_sk_निकास(काष्ठा net *net)
अणु
	पूर्णांक cpu;

	अगर (net->ipv4.tcp_congestion_control)
		bpf_module_put(net->ipv4.tcp_congestion_control,
			       net->ipv4.tcp_congestion_control->owner);

	क्रम_each_possible_cpu(cpu)
		inet_ctl_sock_destroy(*per_cpu_ptr(net->ipv4.tcp_sk, cpu));
	मुक्त_percpu(net->ipv4.tcp_sk);
पूर्ण

अटल पूर्णांक __net_init tcp_sk_init(काष्ठा net *net)
अणु
	पूर्णांक res, cpu, cnt;

	net->ipv4.tcp_sk = alloc_percpu(काष्ठा sock *);
	अगर (!net->ipv4.tcp_sk)
		वापस -ENOMEM;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा sock *sk;

		res = inet_ctl_sock_create(&sk, PF_INET, SOCK_RAW,
					   IPPROTO_TCP, net);
		अगर (res)
			जाओ fail;
		sock_set_flag(sk, SOCK_USE_WRITE_QUEUE);

		/* Please enक्रमce IP_DF and IPID==0 क्रम RST and
		 * ACK sent in SYN-RECV and TIME-WAIT state.
		 */
		inet_sk(sk)->pmtudisc = IP_PMTUDISC_DO;

		*per_cpu_ptr(net->ipv4.tcp_sk, cpu) = sk;
	पूर्ण

	net->ipv4.sysctl_tcp_ecn = 2;
	net->ipv4.sysctl_tcp_ecn_fallback = 1;

	net->ipv4.sysctl_tcp_base_mss = TCP_BASE_MSS;
	net->ipv4.sysctl_tcp_min_snd_mss = TCP_MIN_SND_MSS;
	net->ipv4.sysctl_tcp_probe_threshold = TCP_PROBE_THRESHOLD;
	net->ipv4.sysctl_tcp_probe_पूर्णांकerval = TCP_PROBE_INTERVAL;
	net->ipv4.sysctl_tcp_mtu_probe_न्यूनमान = TCP_MIN_SND_MSS;

	net->ipv4.sysctl_tcp_keepalive_समय = TCP_KEEPALIVE_TIME;
	net->ipv4.sysctl_tcp_keepalive_probes = TCP_KEEPALIVE_PROBES;
	net->ipv4.sysctl_tcp_keepalive_पूर्णांकvl = TCP_KEEPALIVE_INTVL;

	net->ipv4.sysctl_tcp_syn_retries = TCP_SYN_RETRIES;
	net->ipv4.sysctl_tcp_synack_retries = TCP_SYNACK_RETRIES;
	net->ipv4.sysctl_tcp_syncookies = 1;
	net->ipv4.sysctl_tcp_reordering = TCP_FASTRETRANS_THRESH;
	net->ipv4.sysctl_tcp_retries1 = TCP_RETR1;
	net->ipv4.sysctl_tcp_retries2 = TCP_RETR2;
	net->ipv4.sysctl_tcp_orphan_retries = 0;
	net->ipv4.sysctl_tcp_fin_समयout = TCP_FIN_TIMEOUT;
	net->ipv4.sysctl_tcp_notsent_lowat = अच_पूर्णांक_उच्च;
	net->ipv4.sysctl_tcp_tw_reuse = 2;
	net->ipv4.sysctl_tcp_no_ssthresh_metrics_save = 1;

	cnt = tcp_hashinfo.ehash_mask + 1;
	net->ipv4.tcp_death_row.sysctl_max_tw_buckets = cnt / 2;
	net->ipv4.tcp_death_row.hashinfo = &tcp_hashinfo;

	net->ipv4.sysctl_max_syn_backlog = max(128, cnt / 128);
	net->ipv4.sysctl_tcp_sack = 1;
	net->ipv4.sysctl_tcp_winकरोw_scaling = 1;
	net->ipv4.sysctl_tcp_बारtamps = 1;
	net->ipv4.sysctl_tcp_early_retrans = 3;
	net->ipv4.sysctl_tcp_recovery = TCP_RACK_LOSS_DETECTION;
	net->ipv4.sysctl_tcp_slow_start_after_idle = 1; /* By शेष, RFC2861 behavior.  */
	net->ipv4.sysctl_tcp_retrans_collapse = 1;
	net->ipv4.sysctl_tcp_max_reordering = 300;
	net->ipv4.sysctl_tcp_dsack = 1;
	net->ipv4.sysctl_tcp_app_win = 31;
	net->ipv4.sysctl_tcp_adv_win_scale = 1;
	net->ipv4.sysctl_tcp_frto = 2;
	net->ipv4.sysctl_tcp_moderate_rcvbuf = 1;
	/* This limits the percentage of the congestion winकरोw which we
	 * will allow a single TSO frame to consume.  Building TSO frames
	 * which are too large can cause TCP streams to be bursty.
	 */
	net->ipv4.sysctl_tcp_tso_win_भागisor = 3;
	/* Default TSQ limit of 16 TSO segments */
	net->ipv4.sysctl_tcp_limit_output_bytes = 16 * 65536;
	/* rfc5961 challenge ack rate limiting */
	net->ipv4.sysctl_tcp_challenge_ack_limit = 1000;
	net->ipv4.sysctl_tcp_min_tso_segs = 2;
	net->ipv4.sysctl_tcp_min_rtt_wlen = 300;
	net->ipv4.sysctl_tcp_स्वतःcorking = 1;
	net->ipv4.sysctl_tcp_invalid_ratelimit = HZ/2;
	net->ipv4.sysctl_tcp_pacing_ss_ratio = 200;
	net->ipv4.sysctl_tcp_pacing_ca_ratio = 120;
	अगर (net != &init_net) अणु
		स_नकल(net->ipv4.sysctl_tcp_rmem,
		       init_net.ipv4.sysctl_tcp_rmem,
		       माप(init_net.ipv4.sysctl_tcp_rmem));
		स_नकल(net->ipv4.sysctl_tcp_wmem,
		       init_net.ipv4.sysctl_tcp_wmem,
		       माप(init_net.ipv4.sysctl_tcp_wmem));
	पूर्ण
	net->ipv4.sysctl_tcp_comp_sack_delay_ns = NSEC_PER_MSEC;
	net->ipv4.sysctl_tcp_comp_sack_slack_ns = 100 * NSEC_PER_USEC;
	net->ipv4.sysctl_tcp_comp_sack_nr = 44;
	net->ipv4.sysctl_tcp_fastखोलो = TFO_CLIENT_ENABLE;
	spin_lock_init(&net->ipv4.tcp_fastखोलो_ctx_lock);
	net->ipv4.sysctl_tcp_fastखोलो_blackhole_समयout = 60 * 60;
	atomic_set(&net->ipv4.tfo_active_disable_बार, 0);

	/* Reno is always built in */
	अगर (!net_eq(net, &init_net) &&
	    bpf_try_module_get(init_net.ipv4.tcp_congestion_control,
			       init_net.ipv4.tcp_congestion_control->owner))
		net->ipv4.tcp_congestion_control = init_net.ipv4.tcp_congestion_control;
	अन्यथा
		net->ipv4.tcp_congestion_control = &tcp_reno;

	वापस 0;
fail:
	tcp_sk_निकास(net);

	वापस res;
पूर्ण

अटल व्योम __net_निकास tcp_sk_निकास_batch(काष्ठा list_head *net_निकास_list)
अणु
	काष्ठा net *net;

	inet_twsk_purge(&tcp_hashinfo, AF_INET);

	list_क्रम_each_entry(net, net_निकास_list, निकास_list)
		tcp_fastखोलो_ctx_destroy(net);
पूर्ण

अटल काष्ठा pernet_operations __net_initdata tcp_sk_ops = अणु
       .init	   = tcp_sk_init,
       .निकास	   = tcp_sk_निकास,
       .निकास_batch = tcp_sk_निकास_batch,
पूर्ण;

#अगर defined(CONFIG_BPF_SYSCALL) && defined(CONFIG_PROC_FS)
DEFINE_BPF_ITER_FUNC(tcp, काष्ठा bpf_iter_meta *meta,
		     काष्ठा sock_common *sk_common, uid_t uid)

अटल पूर्णांक bpf_iter_init_tcp(व्योम *priv_data, काष्ठा bpf_iter_aux_info *aux)
अणु
	काष्ठा tcp_iter_state *st = priv_data;
	काष्ठा tcp_seq_afinfo *afinfo;
	पूर्णांक ret;

	afinfo = kदो_स्मृति(माप(*afinfo), GFP_USER | __GFP_NOWARN);
	अगर (!afinfo)
		वापस -ENOMEM;

	afinfo->family = AF_UNSPEC;
	st->bpf_seq_afinfo = afinfo;
	ret = bpf_iter_init_seq_net(priv_data, aux);
	अगर (ret)
		kमुक्त(afinfo);
	वापस ret;
पूर्ण

अटल व्योम bpf_iter_fini_tcp(व्योम *priv_data)
अणु
	काष्ठा tcp_iter_state *st = priv_data;

	kमुक्त(st->bpf_seq_afinfo);
	bpf_iter_fini_seq_net(priv_data);
पूर्ण

अटल स्थिर काष्ठा bpf_iter_seq_info tcp_seq_info = अणु
	.seq_ops		= &bpf_iter_tcp_seq_ops,
	.init_seq_निजी	= bpf_iter_init_tcp,
	.fini_seq_निजी	= bpf_iter_fini_tcp,
	.seq_priv_size		= माप(काष्ठा tcp_iter_state),
पूर्ण;

अटल काष्ठा bpf_iter_reg tcp_reg_info = अणु
	.target			= "tcp",
	.ctx_arg_info_size	= 1,
	.ctx_arg_info		= अणु
		अणु दुरत्व(काष्ठा bpf_iter__tcp, sk_common),
		  PTR_TO_BTF_ID_OR_शून्य पूर्ण,
	पूर्ण,
	.seq_info		= &tcp_seq_info,
पूर्ण;

अटल व्योम __init bpf_iter_रेजिस्टर(व्योम)
अणु
	tcp_reg_info.ctx_arg_info[0].btf_id = btf_sock_ids[BTF_SOCK_TYPE_SOCK_COMMON];
	अगर (bpf_iter_reg_target(&tcp_reg_info))
		pr_warn("Warning: could not register bpf iterator tcp\n");
पूर्ण

#पूर्ण_अगर

व्योम __init tcp_v4_init(व्योम)
अणु
	अगर (रेजिस्टर_pernet_subsys(&tcp_sk_ops))
		panic("Failed to create the TCP control socket.\n");

#अगर defined(CONFIG_BPF_SYSCALL) && defined(CONFIG_PROC_FS)
	bpf_iter_रेजिस्टर();
#पूर्ण_अगर
पूर्ण
