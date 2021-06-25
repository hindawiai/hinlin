<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	TCP over IPv6
 *	Linux INET6 implementation
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>
 *
 *	Based on:
 *	linux/net/ipv4/tcp.c
 *	linux/net/ipv4/tcp_input.c
 *	linux/net/ipv4/tcp_output.c
 *
 *	Fixes:
 *	Hideaki YOSHIFUJI	:	sin6_scope_id support
 *	YOSHIFUJI Hideaki @USAGI and:	Support IPV6_V6ONLY socket option, which
 *	Alexey Kuznetsov		allow both IPv4 and IPv6 sockets to bind
 *					a single port at the same समय.
 *	YOSHIFUJI Hideaki @USAGI:	convert /proc/net/tcp6 to seq_file.
 */

#समावेश <linux/bottom_half.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/jhash.h>
#समावेश <linux/ipsec.h>
#समावेश <linux/बार.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/indirect_call_wrapper.h>

#समावेश <net/tcp.h>
#समावेश <net/ndisc.h>
#समावेश <net/inet6_hashtables.h>
#समावेश <net/inet6_connection_sock.h>
#समावेश <net/ipv6.h>
#समावेश <net/transp_v6.h>
#समावेश <net/addrconf.h>
#समावेश <net/ip6_route.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/protocol.h>
#समावेश <net/xfrm.h>
#समावेश <net/snmp.h>
#समावेश <net/dsfield.h>
#समावेश <net/समयरुको_sock.h>
#समावेश <net/inet_common.h>
#समावेश <net/secure_seq.h>
#समावेश <net/busy_poll.h>

#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>

#समावेश <crypto/hash.h>
#समावेश <linux/scatterlist.h>

#समावेश <trace/events/tcp.h>

अटल व्योम	tcp_v6_send_reset(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb);
अटल व्योम	tcp_v6_reqsk_send_ack(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb,
				      काष्ठा request_sock *req);

अटल पूर्णांक	tcp_v6_करो_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb);

अटल स्थिर काष्ठा inet_connection_sock_af_ops ipv6_mapped;
स्थिर काष्ठा inet_connection_sock_af_ops ipv6_specअगरic;
#अगर_घोषित CONFIG_TCP_MD5SIG
अटल स्थिर काष्ठा tcp_sock_af_ops tcp_sock_ipv6_specअगरic;
अटल स्थिर काष्ठा tcp_sock_af_ops tcp_sock_ipv6_mapped_specअगरic;
#अन्यथा
अटल काष्ठा tcp_md5sig_key *tcp_v6_md5_करो_lookup(स्थिर काष्ठा sock *sk,
						   स्थिर काष्ठा in6_addr *addr,
						   पूर्णांक l3index)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

/* Helper वापसing the inet6 address from a given tcp socket.
 * It can be used in TCP stack instead of inet6_sk(sk).
 * This aव्योमs a dereference and allow compiler optimizations.
 * It is a specialized version of inet6_sk_generic().
 */
अटल काष्ठा ipv6_pinfo *tcp_inet6_sk(स्थिर काष्ठा sock *sk)
अणु
	अचिन्हित पूर्णांक offset = माप(काष्ठा tcp6_sock) - माप(काष्ठा ipv6_pinfo);

	वापस (काष्ठा ipv6_pinfo *)(((u8 *)sk) + offset);
पूर्ण

अटल व्योम inet6_sk_rx_dst_set(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);

	अगर (dst && dst_hold_safe(dst)) अणु
		स्थिर काष्ठा rt6_info *rt = (स्थिर काष्ठा rt6_info *)dst;

		sk->sk_rx_dst = dst;
		inet_sk(sk)->rx_dst_अगरindex = skb->skb_iअगर;
		tcp_inet6_sk(sk)->rx_dst_cookie = rt6_get_cookie(rt);
	पूर्ण
पूर्ण

अटल u32 tcp_v6_init_seq(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस secure_tcpv6_seq(ipv6_hdr(skb)->daddr.s6_addr32,
				ipv6_hdr(skb)->saddr.s6_addr32,
				tcp_hdr(skb)->dest,
				tcp_hdr(skb)->source);
पूर्ण

अटल u32 tcp_v6_init_ts_off(स्थिर काष्ठा net *net, स्थिर काष्ठा sk_buff *skb)
अणु
	वापस secure_tcpv6_ts_off(net, ipv6_hdr(skb)->daddr.s6_addr32,
				   ipv6_hdr(skb)->saddr.s6_addr32);
पूर्ण

अटल पूर्णांक tcp_v6_pre_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr,
			      पूर्णांक addr_len)
अणु
	/* This check is replicated from tcp_v6_connect() and पूर्णांकended to
	 * prevent BPF program called below from accessing bytes that are out
	 * of the bound specअगरied by user in addr_len.
	 */
	अगर (addr_len < SIN6_LEN_RFC2133)
		वापस -EINVAL;

	sock_owned_by_me(sk);

	वापस BPF_CGROUP_RUN_PROG_INET6_CONNECT(sk, uaddr);
पूर्ण

अटल पूर्णांक tcp_v6_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr,
			  पूर्णांक addr_len)
अणु
	काष्ठा sockaddr_in6 *usin = (काष्ठा sockaddr_in6 *) uaddr;
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा ipv6_pinfo *np = tcp_inet6_sk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा in6_addr *saddr = शून्य, *final_p, final;
	काष्ठा ipv6_txoptions *opt;
	काष्ठा flowi6 fl6;
	काष्ठा dst_entry *dst;
	पूर्णांक addr_type;
	पूर्णांक err;
	काष्ठा inet_समयरुको_death_row *tcp_death_row = &sock_net(sk)->ipv4.tcp_death_row;

	अगर (addr_len < SIN6_LEN_RFC2133)
		वापस -EINVAL;

	अगर (usin->sin6_family != AF_INET6)
		वापस -EAFNOSUPPORT;

	स_रखो(&fl6, 0, माप(fl6));

	अगर (np->sndflow) अणु
		fl6.flowlabel = usin->sin6_flowinfo&IPV6_FLOWINFO_MASK;
		IP6_ECN_flow_init(fl6.flowlabel);
		अगर (fl6.flowlabel&IPV6_FLOWLABEL_MASK) अणु
			काष्ठा ip6_flowlabel *flowlabel;
			flowlabel = fl6_sock_lookup(sk, fl6.flowlabel);
			अगर (IS_ERR(flowlabel))
				वापस -EINVAL;
			fl6_sock_release(flowlabel);
		पूर्ण
	पूर्ण

	/*
	 *	connect() to INADDR_ANY means loopback (BSD'ism).
	 */

	अगर (ipv6_addr_any(&usin->sin6_addr)) अणु
		अगर (ipv6_addr_v4mapped(&sk->sk_v6_rcv_saddr))
			ipv6_addr_set_v4mapped(htonl(INADDR_LOOPBACK),
					       &usin->sin6_addr);
		अन्यथा
			usin->sin6_addr = in6addr_loopback;
	पूर्ण

	addr_type = ipv6_addr_type(&usin->sin6_addr);

	अगर (addr_type & IPV6_ADDR_MULTICAST)
		वापस -ENETUNREACH;

	अगर (addr_type&IPV6_ADDR_LINKLOCAL) अणु
		अगर (addr_len >= माप(काष्ठा sockaddr_in6) &&
		    usin->sin6_scope_id) अणु
			/* If पूर्णांकerface is set जबतक binding, indices
			 * must coincide.
			 */
			अगर (!sk_dev_equal_l3scope(sk, usin->sin6_scope_id))
				वापस -EINVAL;

			sk->sk_bound_dev_अगर = usin->sin6_scope_id;
		पूर्ण

		/* Connect to link-local address requires an पूर्णांकerface */
		अगर (!sk->sk_bound_dev_अगर)
			वापस -EINVAL;
	पूर्ण

	अगर (tp->rx_opt.ts_recent_stamp &&
	    !ipv6_addr_equal(&sk->sk_v6_daddr, &usin->sin6_addr)) अणु
		tp->rx_opt.ts_recent = 0;
		tp->rx_opt.ts_recent_stamp = 0;
		WRITE_ONCE(tp->ग_लिखो_seq, 0);
	पूर्ण

	sk->sk_v6_daddr = usin->sin6_addr;
	np->flow_label = fl6.flowlabel;

	/*
	 *	TCP over IPv4
	 */

	अगर (addr_type & IPV6_ADDR_MAPPED) अणु
		u32 exthdrlen = icsk->icsk_ext_hdr_len;
		काष्ठा sockaddr_in sin;

		अगर (__ipv6_only_sock(sk))
			वापस -ENETUNREACH;

		sin.sin_family = AF_INET;
		sin.sin_port = usin->sin6_port;
		sin.sin_addr.s_addr = usin->sin6_addr.s6_addr32[3];

		icsk->icsk_af_ops = &ipv6_mapped;
		अगर (sk_is_mptcp(sk))
			mptcpv6_handle_mapped(sk, true);
		sk->sk_backlog_rcv = tcp_v4_करो_rcv;
#अगर_घोषित CONFIG_TCP_MD5SIG
		tp->af_specअगरic = &tcp_sock_ipv6_mapped_specअगरic;
#पूर्ण_अगर

		err = tcp_v4_connect(sk, (काष्ठा sockaddr *)&sin, माप(sin));

		अगर (err) अणु
			icsk->icsk_ext_hdr_len = exthdrlen;
			icsk->icsk_af_ops = &ipv6_specअगरic;
			अगर (sk_is_mptcp(sk))
				mptcpv6_handle_mapped(sk, false);
			sk->sk_backlog_rcv = tcp_v6_करो_rcv;
#अगर_घोषित CONFIG_TCP_MD5SIG
			tp->af_specअगरic = &tcp_sock_ipv6_specअगरic;
#पूर्ण_अगर
			जाओ failure;
		पूर्ण
		np->saddr = sk->sk_v6_rcv_saddr;

		वापस err;
	पूर्ण

	अगर (!ipv6_addr_any(&sk->sk_v6_rcv_saddr))
		saddr = &sk->sk_v6_rcv_saddr;

	fl6.flowi6_proto = IPPROTO_TCP;
	fl6.daddr = sk->sk_v6_daddr;
	fl6.saddr = saddr ? *saddr : np->saddr;
	fl6.flowi6_oअगर = sk->sk_bound_dev_अगर;
	fl6.flowi6_mark = sk->sk_mark;
	fl6.fl6_dport = usin->sin6_port;
	fl6.fl6_sport = inet->inet_sport;
	fl6.flowi6_uid = sk->sk_uid;

	opt = rcu_dereference_रक्षित(np->opt, lockdep_sock_is_held(sk));
	final_p = fl6_update_dst(&fl6, opt, &final);

	security_sk_classअगरy_flow(sk, flowi6_to_flowi_common(&fl6));

	dst = ip6_dst_lookup_flow(sock_net(sk), sk, &fl6, final_p);
	अगर (IS_ERR(dst)) अणु
		err = PTR_ERR(dst);
		जाओ failure;
	पूर्ण

	अगर (!saddr) अणु
		saddr = &fl6.saddr;
		sk->sk_v6_rcv_saddr = *saddr;
	पूर्ण

	/* set the source address */
	np->saddr = *saddr;
	inet->inet_rcv_saddr = LOOPBACK4_IPV6;

	sk->sk_gso_type = SKB_GSO_TCPV6;
	ip6_dst_store(sk, dst, शून्य, शून्य);

	icsk->icsk_ext_hdr_len = 0;
	अगर (opt)
		icsk->icsk_ext_hdr_len = opt->opt_flen +
					 opt->opt_nflen;

	tp->rx_opt.mss_clamp = IPV6_MIN_MTU - माप(काष्ठा tcphdr) - माप(काष्ठा ipv6hdr);

	inet->inet_dport = usin->sin6_port;

	tcp_set_state(sk, TCP_SYN_SENT);
	err = inet6_hash_connect(tcp_death_row, sk);
	अगर (err)
		जाओ late_failure;

	sk_set_txhash(sk);

	अगर (likely(!tp->repair)) अणु
		अगर (!tp->ग_लिखो_seq)
			WRITE_ONCE(tp->ग_लिखो_seq,
				   secure_tcpv6_seq(np->saddr.s6_addr32,
						    sk->sk_v6_daddr.s6_addr32,
						    inet->inet_sport,
						    inet->inet_dport));
		tp->tsoffset = secure_tcpv6_ts_off(sock_net(sk),
						   np->saddr.s6_addr32,
						   sk->sk_v6_daddr.s6_addr32);
	पूर्ण

	अगर (tcp_fastखोलो_defer_connect(sk, &err))
		वापस err;
	अगर (err)
		जाओ late_failure;

	err = tcp_connect(sk);
	अगर (err)
		जाओ late_failure;

	वापस 0;

late_failure:
	tcp_set_state(sk, TCP_CLOSE);
failure:
	inet->inet_dport = 0;
	sk->sk_route_caps = 0;
	वापस err;
पूर्ण

अटल व्योम tcp_v6_mtu_reduced(काष्ठा sock *sk)
अणु
	काष्ठा dst_entry *dst;

	अगर ((1 << sk->sk_state) & (TCPF_LISTEN | TCPF_CLOSE))
		वापस;

	dst = inet6_csk_update_pmtu(sk, tcp_sk(sk)->mtu_info);
	अगर (!dst)
		वापस;

	अगर (inet_csk(sk)->icsk_pmtu_cookie > dst_mtu(dst)) अणु
		tcp_sync_mss(sk, dst_mtu(dst));
		tcp_simple_retransmit(sk);
	पूर्ण
पूर्ण

अटल पूर्णांक tcp_v6_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
		u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	स्थिर काष्ठा ipv6hdr *hdr = (स्थिर काष्ठा ipv6hdr *)skb->data;
	स्थिर काष्ठा tcphdr *th = (काष्ठा tcphdr *)(skb->data+offset);
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा request_sock *fastखोलो;
	काष्ठा ipv6_pinfo *np;
	काष्ठा tcp_sock *tp;
	__u32 seq, snd_una;
	काष्ठा sock *sk;
	bool fatal;
	पूर्णांक err;

	sk = __inet6_lookup_established(net, &tcp_hashinfo,
					&hdr->daddr, th->dest,
					&hdr->saddr, ntohs(th->source),
					skb->dev->अगरindex, inet6_sdअगर(skb));

	अगर (!sk) अणु
		__ICMP6_INC_STATS(net, __in6_dev_get(skb->dev),
				  ICMP6_MIB_INERRORS);
		वापस -ENOENT;
	पूर्ण

	अगर (sk->sk_state == TCP_TIME_WAIT) अणु
		inet_twsk_put(inet_twsk(sk));
		वापस 0;
	पूर्ण
	seq = ntohl(th->seq);
	fatal = icmpv6_err_convert(type, code, &err);
	अगर (sk->sk_state == TCP_NEW_SYN_RECV) अणु
		tcp_req_err(sk, seq, fatal);
		वापस 0;
	पूर्ण

	bh_lock_sock(sk);
	अगर (sock_owned_by_user(sk) && type != ICMPV6_PKT_TOOBIG)
		__NET_INC_STATS(net, LINUX_MIB_LOCKDROPPEDICMPS);

	अगर (sk->sk_state == TCP_CLOSE)
		जाओ out;

	अगर (ipv6_hdr(skb)->hop_limit < tcp_inet6_sk(sk)->min_hopcount) अणु
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

	np = tcp_inet6_sk(sk);

	अगर (type == NDISC_REसूचीECT) अणु
		अगर (!sock_owned_by_user(sk)) अणु
			काष्ठा dst_entry *dst = __sk_dst_check(sk, np->dst_cookie);

			अगर (dst)
				dst->ops->redirect(dst, sk, skb);
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (type == ICMPV6_PKT_TOOBIG) अणु
		/* We are not पूर्णांकerested in TCP_LISTEN and खोलो_requests
		 * (SYN-ACKs send out by Linux are always <576bytes so
		 * they should go through unfragmented).
		 */
		अगर (sk->sk_state == TCP_LISTEN)
			जाओ out;

		अगर (!ip6_sk_accept_pmtu(sk))
			जाओ out;

		tp->mtu_info = ntohl(info);
		अगर (!sock_owned_by_user(sk))
			tcp_v6_mtu_reduced(sk);
		अन्यथा अगर (!test_and_set_bit(TCP_MTU_REDUCED_DEFERRED,
					   &sk->sk_tsq_flags))
			sock_hold(sk);
		जाओ out;
	पूर्ण


	/* Might be क्रम an request_sock */
	चयन (sk->sk_state) अणु
	हाल TCP_SYN_SENT:
	हाल TCP_SYN_RECV:
		/* Only in fast or simultaneous खोलो. If a fast खोलो socket is
		 * alपढ़ोy accepted it is treated as a connected one below.
		 */
		अगर (fastखोलो && !fastखोलो->sk)
			अवरोध;

		ipv6_icmp_error(sk, skb, err, th->dest, ntohl(info), (u8 *)th);

		अगर (!sock_owned_by_user(sk)) अणु
			sk->sk_err = err;
			sk->sk_error_report(sk);		/* Wake people up to see the error (see connect in sock.c) */

			tcp_करोne(sk);
		पूर्ण अन्यथा
			sk->sk_err_soft = err;
		जाओ out;
	हाल TCP_LISTEN:
		अवरोध;
	शेष:
		/* check अगर this ICMP message allows revert of backoff.
		 * (see RFC 6069)
		 */
		अगर (!fastखोलो && type == ICMPV6_DEST_UNREACH &&
		    code == ICMPV6_NOROUTE)
			tcp_ld_RTO_revert(sk, seq);
	पूर्ण

	अगर (!sock_owned_by_user(sk) && np->recverr) अणु
		sk->sk_err = err;
		sk->sk_error_report(sk);
	पूर्ण अन्यथा
		sk->sk_err_soft = err;

out:
	bh_unlock_sock(sk);
	sock_put(sk);
	वापस 0;
पूर्ण


अटल पूर्णांक tcp_v6_send_synack(स्थिर काष्ठा sock *sk, काष्ठा dst_entry *dst,
			      काष्ठा flowi *fl,
			      काष्ठा request_sock *req,
			      काष्ठा tcp_fastखोलो_cookie *foc,
			      क्रमागत tcp_synack_type synack_type,
			      काष्ठा sk_buff *syn_skb)
अणु
	काष्ठा inet_request_sock *ireq = inet_rsk(req);
	काष्ठा ipv6_pinfo *np = tcp_inet6_sk(sk);
	काष्ठा ipv6_txoptions *opt;
	काष्ठा flowi6 *fl6 = &fl->u.ip6;
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOMEM;
	u8 tclass;

	/* First, grab a route. */
	अगर (!dst && (dst = inet6_csk_route_req(sk, fl6, req,
					       IPPROTO_TCP)) == शून्य)
		जाओ करोne;

	skb = tcp_make_synack(sk, dst, req, foc, synack_type, syn_skb);

	अगर (skb) अणु
		__tcp_v6_send_check(skb, &ireq->ir_v6_loc_addr,
				    &ireq->ir_v6_rmt_addr);

		fl6->daddr = ireq->ir_v6_rmt_addr;
		अगर (np->repflow && ireq->pktopts)
			fl6->flowlabel = ip6_flowlabel(ipv6_hdr(ireq->pktopts));

		tclass = sock_net(sk)->ipv4.sysctl_tcp_reflect_tos ?
				(tcp_rsk(req)->syn_tos & ~INET_ECN_MASK) |
				(np->tclass & INET_ECN_MASK) :
				np->tclass;

		अगर (!INET_ECN_is_capable(tclass) &&
		    tcp_bpf_ca_needs_ecn((काष्ठा sock *)req))
			tclass |= INET_ECN_ECT_0;

		rcu_पढ़ो_lock();
		opt = ireq->ipv6_opt;
		अगर (!opt)
			opt = rcu_dereference(np->opt);
		err = ip6_xmit(sk, skb, fl6, sk->sk_mark, opt,
			       tclass, sk->sk_priority);
		rcu_पढ़ो_unlock();
		err = net_xmit_eval(err);
	पूर्ण

करोne:
	वापस err;
पूर्ण


अटल व्योम tcp_v6_reqsk_deकाष्ठाor(काष्ठा request_sock *req)
अणु
	kमुक्त(inet_rsk(req)->ipv6_opt);
	kमुक्त_skb(inet_rsk(req)->pktopts);
पूर्ण

#अगर_घोषित CONFIG_TCP_MD5SIG
अटल काष्ठा tcp_md5sig_key *tcp_v6_md5_करो_lookup(स्थिर काष्ठा sock *sk,
						   स्थिर काष्ठा in6_addr *addr,
						   पूर्णांक l3index)
अणु
	वापस tcp_md5_करो_lookup(sk, l3index,
				 (जोड़ tcp_md5_addr *)addr, AF_INET6);
पूर्ण

अटल काष्ठा tcp_md5sig_key *tcp_v6_md5_lookup(स्थिर काष्ठा sock *sk,
						स्थिर काष्ठा sock *addr_sk)
अणु
	पूर्णांक l3index;

	l3index = l3mdev_master_अगरindex_by_index(sock_net(sk),
						 addr_sk->sk_bound_dev_अगर);
	वापस tcp_v6_md5_करो_lookup(sk, &addr_sk->sk_v6_daddr,
				    l3index);
पूर्ण

अटल पूर्णांक tcp_v6_parse_md5_keys(काष्ठा sock *sk, पूर्णांक optname,
				 sockptr_t optval, पूर्णांक optlen)
अणु
	काष्ठा tcp_md5sig cmd;
	काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *)&cmd.tcpm_addr;
	पूर्णांक l3index = 0;
	u8 prefixlen;

	अगर (optlen < माप(cmd))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&cmd, optval, माप(cmd)))
		वापस -EFAULT;

	अगर (sin6->sin6_family != AF_INET6)
		वापस -EINVAL;

	अगर (optname == TCP_MD5SIG_EXT &&
	    cmd.tcpm_flags & TCP_MD5SIG_FLAG_PREFIX) अणु
		prefixlen = cmd.tcpm_prefixlen;
		अगर (prefixlen > 128 || (ipv6_addr_v4mapped(&sin6->sin6_addr) &&
					prefixlen > 32))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		prefixlen = ipv6_addr_v4mapped(&sin6->sin6_addr) ? 32 : 128;
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

	अगर (!cmd.tcpm_keylen) अणु
		अगर (ipv6_addr_v4mapped(&sin6->sin6_addr))
			वापस tcp_md5_करो_del(sk, (जोड़ tcp_md5_addr *)&sin6->sin6_addr.s6_addr32[3],
					      AF_INET, prefixlen,
					      l3index);
		वापस tcp_md5_करो_del(sk, (जोड़ tcp_md5_addr *)&sin6->sin6_addr,
				      AF_INET6, prefixlen, l3index);
	पूर्ण

	अगर (cmd.tcpm_keylen > TCP_MD5SIG_MAXKEYLEN)
		वापस -EINVAL;

	अगर (ipv6_addr_v4mapped(&sin6->sin6_addr))
		वापस tcp_md5_करो_add(sk, (जोड़ tcp_md5_addr *)&sin6->sin6_addr.s6_addr32[3],
				      AF_INET, prefixlen, l3index,
				      cmd.tcpm_key, cmd.tcpm_keylen,
				      GFP_KERNEL);

	वापस tcp_md5_करो_add(sk, (जोड़ tcp_md5_addr *)&sin6->sin6_addr,
			      AF_INET6, prefixlen, l3index,
			      cmd.tcpm_key, cmd.tcpm_keylen, GFP_KERNEL);
पूर्ण

अटल पूर्णांक tcp_v6_md5_hash_headers(काष्ठा tcp_md5sig_pool *hp,
				   स्थिर काष्ठा in6_addr *daddr,
				   स्थिर काष्ठा in6_addr *saddr,
				   स्थिर काष्ठा tcphdr *th, पूर्णांक nbytes)
अणु
	काष्ठा tcp6_pseuकरोhdr *bp;
	काष्ठा scatterlist sg;
	काष्ठा tcphdr *_th;

	bp = hp->scratch;
	/* 1. TCP pseuकरो-header (RFC2460) */
	bp->saddr = *saddr;
	bp->daddr = *daddr;
	bp->protocol = cpu_to_be32(IPPROTO_TCP);
	bp->len = cpu_to_be32(nbytes);

	_th = (काष्ठा tcphdr *)(bp + 1);
	स_नकल(_th, th, माप(*th));
	_th->check = 0;

	sg_init_one(&sg, bp, माप(*bp) + माप(*th));
	ahash_request_set_crypt(hp->md5_req, &sg, शून्य,
				माप(*bp) + माप(*th));
	वापस crypto_ahash_update(hp->md5_req);
पूर्ण

अटल पूर्णांक tcp_v6_md5_hash_hdr(अक्षर *md5_hash, स्थिर काष्ठा tcp_md5sig_key *key,
			       स्थिर काष्ठा in6_addr *daddr, काष्ठा in6_addr *saddr,
			       स्थिर काष्ठा tcphdr *th)
अणु
	काष्ठा tcp_md5sig_pool *hp;
	काष्ठा ahash_request *req;

	hp = tcp_get_md5sig_pool();
	अगर (!hp)
		जाओ clear_hash_noput;
	req = hp->md5_req;

	अगर (crypto_ahash_init(req))
		जाओ clear_hash;
	अगर (tcp_v6_md5_hash_headers(hp, daddr, saddr, th, th->करोff << 2))
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

अटल पूर्णांक tcp_v6_md5_hash_skb(अक्षर *md5_hash,
			       स्थिर काष्ठा tcp_md5sig_key *key,
			       स्थिर काष्ठा sock *sk,
			       स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा in6_addr *saddr, *daddr;
	काष्ठा tcp_md5sig_pool *hp;
	काष्ठा ahash_request *req;
	स्थिर काष्ठा tcphdr *th = tcp_hdr(skb);

	अगर (sk) अणु /* valid क्रम establish/request sockets */
		saddr = &sk->sk_v6_rcv_saddr;
		daddr = &sk->sk_v6_daddr;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);
		saddr = &ip6h->saddr;
		daddr = &ip6h->daddr;
	पूर्ण

	hp = tcp_get_md5sig_pool();
	अगर (!hp)
		जाओ clear_hash_noput;
	req = hp->md5_req;

	अगर (crypto_ahash_init(req))
		जाओ clear_hash;

	अगर (tcp_v6_md5_hash_headers(hp, daddr, saddr, th, skb->len))
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

#पूर्ण_अगर

अटल bool tcp_v6_inbound_md5_hash(स्थिर काष्ठा sock *sk,
				    स्थिर काष्ठा sk_buff *skb,
				    पूर्णांक dअगर, पूर्णांक sdअगर)
अणु
#अगर_घोषित CONFIG_TCP_MD5SIG
	स्थिर __u8 *hash_location = शून्य;
	काष्ठा tcp_md5sig_key *hash_expected;
	स्थिर काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);
	स्थिर काष्ठा tcphdr *th = tcp_hdr(skb);
	पूर्णांक genhash, l3index;
	u8 newhash[16];

	/* sdअगर set, means packet ingressed via a device
	 * in an L3 करोमुख्य and dअगर is set to the l3mdev
	 */
	l3index = sdअगर ? dअगर : 0;

	hash_expected = tcp_v6_md5_करो_lookup(sk, &ip6h->saddr, l3index);
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

	/* check the signature */
	genhash = tcp_v6_md5_hash_skb(newhash,
				      hash_expected,
				      शून्य, skb);

	अगर (genhash || स_भेद(hash_location, newhash, 16) != 0) अणु
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPMD5FAILURE);
		net_info_ratelimited("MD5 Hash %s for [%pI6c]:%u->[%pI6c]:%u L3 index %d\n",
				     genhash ? "failed" : "mismatch",
				     &ip6h->saddr, ntohs(th->source),
				     &ip6h->daddr, ntohs(th->dest), l3index);
		वापस true;
	पूर्ण
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल व्योम tcp_v6_init_req(काष्ठा request_sock *req,
			    स्थिर काष्ठा sock *sk_listener,
			    काष्ठा sk_buff *skb)
अणु
	bool l3_slave = ipv6_l3mdev_skb(TCP_SKB_CB(skb)->header.h6.flags);
	काष्ठा inet_request_sock *ireq = inet_rsk(req);
	स्थिर काष्ठा ipv6_pinfo *np = tcp_inet6_sk(sk_listener);

	ireq->ir_v6_rmt_addr = ipv6_hdr(skb)->saddr;
	ireq->ir_v6_loc_addr = ipv6_hdr(skb)->daddr;

	/* So that link locals have meaning */
	अगर ((!sk_listener->sk_bound_dev_अगर || l3_slave) &&
	    ipv6_addr_type(&ireq->ir_v6_rmt_addr) & IPV6_ADDR_LINKLOCAL)
		ireq->ir_iअगर = tcp_v6_iअगर(skb);

	अगर (!TCP_SKB_CB(skb)->tcp_tw_isn &&
	    (ipv6_opt_accepted(sk_listener, skb, &TCP_SKB_CB(skb)->header.h6) ||
	     np->rxopt.bits.rxinfo ||
	     np->rxopt.bits.rxoinfo || np->rxopt.bits.rxhlim ||
	     np->rxopt.bits.rxohlim || np->repflow)) अणु
		refcount_inc(&skb->users);
		ireq->pktopts = skb;
	पूर्ण
पूर्ण

अटल काष्ठा dst_entry *tcp_v6_route_req(स्थिर काष्ठा sock *sk,
					  काष्ठा sk_buff *skb,
					  काष्ठा flowi *fl,
					  काष्ठा request_sock *req)
अणु
	tcp_v6_init_req(req, sk, skb);

	अगर (security_inet_conn_request(sk, skb, req))
		वापस शून्य;

	वापस inet6_csk_route_req(sk, &fl->u.ip6, req, IPPROTO_TCP);
पूर्ण

काष्ठा request_sock_ops tcp6_request_sock_ops __पढ़ो_mostly = अणु
	.family		=	AF_INET6,
	.obj_size	=	माप(काष्ठा tcp6_request_sock),
	.rtx_syn_ack	=	tcp_rtx_synack,
	.send_ack	=	tcp_v6_reqsk_send_ack,
	.deकाष्ठाor	=	tcp_v6_reqsk_deकाष्ठाor,
	.send_reset	=	tcp_v6_send_reset,
	.syn_ack_समयout =	tcp_syn_ack_समयout,
पूर्ण;

स्थिर काष्ठा tcp_request_sock_ops tcp_request_sock_ipv6_ops = अणु
	.mss_clamp	=	IPV6_MIN_MTU - माप(काष्ठा tcphdr) -
				माप(काष्ठा ipv6hdr),
#अगर_घोषित CONFIG_TCP_MD5SIG
	.req_md5_lookup	=	tcp_v6_md5_lookup,
	.calc_md5_hash	=	tcp_v6_md5_hash_skb,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYN_COOKIES
	.cookie_init_seq =	cookie_v6_init_sequence,
#पूर्ण_अगर
	.route_req	=	tcp_v6_route_req,
	.init_seq	=	tcp_v6_init_seq,
	.init_ts_off	=	tcp_v6_init_ts_off,
	.send_synack	=	tcp_v6_send_synack,
पूर्ण;

अटल व्योम tcp_v6_send_response(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb, u32 seq,
				 u32 ack, u32 win, u32 tsval, u32 tsecr,
				 पूर्णांक oअगर, काष्ठा tcp_md5sig_key *key, पूर्णांक rst,
				 u8 tclass, __be32 label, u32 priority)
अणु
	स्थिर काष्ठा tcphdr *th = tcp_hdr(skb);
	काष्ठा tcphdr *t1;
	काष्ठा sk_buff *buff;
	काष्ठा flowi6 fl6;
	काष्ठा net *net = sk ? sock_net(sk) : dev_net(skb_dst(skb)->dev);
	काष्ठा sock *ctl_sk = net->ipv6.tcp_sk;
	अचिन्हित पूर्णांक tot_len = माप(काष्ठा tcphdr);
	__be32 mrst = 0, *topt;
	काष्ठा dst_entry *dst;
	__u32 mark = 0;

	अगर (tsecr)
		tot_len += TCPOLEN_TSTAMP_ALIGNED;
#अगर_घोषित CONFIG_TCP_MD5SIG
	अगर (key)
		tot_len += TCPOLEN_MD5SIG_ALIGNED;
#पूर्ण_अगर

#अगर_घोषित CONFIG_MPTCP
	अगर (rst && !key) अणु
		mrst = mptcp_reset_option(skb);

		अगर (mrst)
			tot_len += माप(__be32);
	पूर्ण
#पूर्ण_अगर

	buff = alloc_skb(MAX_HEADER + माप(काष्ठा ipv6hdr) + tot_len,
			 GFP_ATOMIC);
	अगर (!buff)
		वापस;

	skb_reserve(buff, MAX_HEADER + माप(काष्ठा ipv6hdr) + tot_len);

	t1 = skb_push(buff, tot_len);
	skb_reset_transport_header(buff);

	/* Swap the send and the receive. */
	स_रखो(t1, 0, माप(*t1));
	t1->dest = th->source;
	t1->source = th->dest;
	t1->करोff = tot_len / 4;
	t1->seq = htonl(seq);
	t1->ack_seq = htonl(ack);
	t1->ack = !rst || !th->ack;
	t1->rst = rst;
	t1->winकरोw = htons(win);

	topt = (__be32 *)(t1 + 1);

	अगर (tsecr) अणु
		*topt++ = htonl((TCPOPT_NOP << 24) | (TCPOPT_NOP << 16) |
				(TCPOPT_TIMESTAMP << 8) | TCPOLEN_TIMESTAMP);
		*topt++ = htonl(tsval);
		*topt++ = htonl(tsecr);
	पूर्ण

	अगर (mrst)
		*topt++ = mrst;

#अगर_घोषित CONFIG_TCP_MD5SIG
	अगर (key) अणु
		*topt++ = htonl((TCPOPT_NOP << 24) | (TCPOPT_NOP << 16) |
				(TCPOPT_MD5SIG << 8) | TCPOLEN_MD5SIG);
		tcp_v6_md5_hash_hdr((__u8 *)topt, key,
				    &ipv6_hdr(skb)->saddr,
				    &ipv6_hdr(skb)->daddr, t1);
	पूर्ण
#पूर्ण_अगर

	स_रखो(&fl6, 0, माप(fl6));
	fl6.daddr = ipv6_hdr(skb)->saddr;
	fl6.saddr = ipv6_hdr(skb)->daddr;
	fl6.flowlabel = label;

	buff->ip_summed = CHECKSUM_PARTIAL;
	buff->csum = 0;

	__tcp_v6_send_check(buff, &fl6.saddr, &fl6.daddr);

	fl6.flowi6_proto = IPPROTO_TCP;
	अगर (rt6_need_strict(&fl6.daddr) && !oअगर)
		fl6.flowi6_oअगर = tcp_v6_iअगर(skb);
	अन्यथा अणु
		अगर (!oअगर && netअगर_index_is_l3_master(net, skb->skb_iअगर))
			oअगर = skb->skb_iअगर;

		fl6.flowi6_oअगर = oअगर;
	पूर्ण

	अगर (sk) अणु
		अगर (sk->sk_state == TCP_TIME_WAIT) अणु
			mark = inet_twsk(sk)->tw_mark;
			/* स्वतःflowlabel relies on buff->hash */
			skb_set_hash(buff, inet_twsk(sk)->tw_txhash,
				     PKT_HASH_TYPE_L4);
		पूर्ण अन्यथा अणु
			mark = sk->sk_mark;
		पूर्ण
		buff->tstamp = tcp_transmit_समय(sk);
	पूर्ण
	fl6.flowi6_mark = IP6_REPLY_MARK(net, skb->mark) ?: mark;
	fl6.fl6_dport = t1->dest;
	fl6.fl6_sport = t1->source;
	fl6.flowi6_uid = sock_net_uid(net, sk && sk_fullsock(sk) ? sk : शून्य);
	security_skb_classअगरy_flow(skb, flowi6_to_flowi_common(&fl6));

	/* Pass a socket to ip6_dst_lookup either it is क्रम RST
	 * Underlying function will use this to retrieve the network
	 * namespace
	 */
	dst = ip6_dst_lookup_flow(sock_net(ctl_sk), ctl_sk, &fl6, शून्य);
	अगर (!IS_ERR(dst)) अणु
		skb_dst_set(buff, dst);
		ip6_xmit(ctl_sk, buff, &fl6, fl6.flowi6_mark, शून्य,
			 tclass & ~INET_ECN_MASK, priority);
		TCP_INC_STATS(net, TCP_MIB_OUTSEGS);
		अगर (rst)
			TCP_INC_STATS(net, TCP_MIB_OUTRSTS);
		वापस;
	पूर्ण

	kमुक्त_skb(buff);
पूर्ण

अटल व्योम tcp_v6_send_reset(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा tcphdr *th = tcp_hdr(skb);
	काष्ठा ipv6hdr *ipv6h = ipv6_hdr(skb);
	u32 seq = 0, ack_seq = 0;
	काष्ठा tcp_md5sig_key *key = शून्य;
#अगर_घोषित CONFIG_TCP_MD5SIG
	स्थिर __u8 *hash_location = शून्य;
	अचिन्हित अक्षर newhash[16];
	पूर्णांक genhash;
	काष्ठा sock *sk1 = शून्य;
#पूर्ण_अगर
	__be32 label = 0;
	u32 priority = 0;
	काष्ठा net *net;
	पूर्णांक oअगर = 0;

	अगर (th->rst)
		वापस;

	/* If sk not शून्य, it means we did a successful lookup and incoming
	 * route had to be correct. prequeue might have dropped our dst.
	 */
	अगर (!sk && !ipv6_unicast_destination(skb))
		वापस;

	net = sk ? sock_net(sk) : dev_net(skb_dst(skb)->dev);
#अगर_घोषित CONFIG_TCP_MD5SIG
	rcu_पढ़ो_lock();
	hash_location = tcp_parse_md5sig_option(th);
	अगर (sk && sk_fullsock(sk)) अणु
		पूर्णांक l3index;

		/* sdअगर set, means packet ingressed via a device
		 * in an L3 करोमुख्य and inet_iअगर is set to it.
		 */
		l3index = tcp_v6_sdअगर(skb) ? tcp_v6_iअगर_l3_slave(skb) : 0;
		key = tcp_v6_md5_करो_lookup(sk, &ipv6h->saddr, l3index);
	पूर्ण अन्यथा अगर (hash_location) अणु
		पूर्णांक dअगर = tcp_v6_iअगर_l3_slave(skb);
		पूर्णांक sdअगर = tcp_v6_sdअगर(skb);
		पूर्णांक l3index;

		/*
		 * active side is lost. Try to find listening socket through
		 * source port, and then find md5 key through listening socket.
		 * we are not loose security here:
		 * Incoming packet is checked with md5 hash with finding key,
		 * no RST generated अगर md5 hash करोesn't match.
		 */
		sk1 = inet6_lookup_listener(net,
					   &tcp_hashinfo, शून्य, 0,
					   &ipv6h->saddr,
					   th->source, &ipv6h->daddr,
					   ntohs(th->source), dअगर, sdअगर);
		अगर (!sk1)
			जाओ out;

		/* sdअगर set, means packet ingressed via a device
		 * in an L3 करोमुख्य and dअगर is set to it.
		 */
		l3index = tcp_v6_sdअगर(skb) ? dअगर : 0;

		key = tcp_v6_md5_करो_lookup(sk1, &ipv6h->saddr, l3index);
		अगर (!key)
			जाओ out;

		genhash = tcp_v6_md5_hash_skb(newhash, key, शून्य, skb);
		अगर (genhash || स_भेद(hash_location, newhash, 16) != 0)
			जाओ out;
	पूर्ण
#पूर्ण_अगर

	अगर (th->ack)
		seq = ntohl(th->ack_seq);
	अन्यथा
		ack_seq = ntohl(th->seq) + th->syn + th->fin + skb->len -
			  (th->करोff << 2);

	अगर (sk) अणु
		oअगर = sk->sk_bound_dev_अगर;
		अगर (sk_fullsock(sk)) अणु
			स्थिर काष्ठा ipv6_pinfo *np = tcp_inet6_sk(sk);

			trace_tcp_send_reset(sk, skb);
			अगर (np->repflow)
				label = ip6_flowlabel(ipv6h);
			priority = sk->sk_priority;
		पूर्ण
		अगर (sk->sk_state == TCP_TIME_WAIT) अणु
			label = cpu_to_be32(inet_twsk(sk)->tw_flowlabel);
			priority = inet_twsk(sk)->tw_priority;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (net->ipv6.sysctl.flowlabel_reflect & FLOWLABEL_REFLECT_TCP_RESET)
			label = ip6_flowlabel(ipv6h);
	पूर्ण

	tcp_v6_send_response(sk, skb, seq, ack_seq, 0, 0, 0, oअगर, key, 1,
			     ipv6_get_dsfield(ipv6h), label, priority);

#अगर_घोषित CONFIG_TCP_MD5SIG
out:
	rcu_पढ़ो_unlock();
#पूर्ण_अगर
पूर्ण

अटल व्योम tcp_v6_send_ack(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb, u32 seq,
			    u32 ack, u32 win, u32 tsval, u32 tsecr, पूर्णांक oअगर,
			    काष्ठा tcp_md5sig_key *key, u8 tclass,
			    __be32 label, u32 priority)
अणु
	tcp_v6_send_response(sk, skb, seq, ack, win, tsval, tsecr, oअगर, key, 0,
			     tclass, label, priority);
पूर्ण

अटल व्योम tcp_v6_समयरुको_ack(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा inet_समयरुको_sock *tw = inet_twsk(sk);
	काष्ठा tcp_समयरुको_sock *tcptw = tcp_twsk(sk);

	tcp_v6_send_ack(sk, skb, tcptw->tw_snd_nxt, tcptw->tw_rcv_nxt,
			tcptw->tw_rcv_wnd >> tw->tw_rcv_wscale,
			tcp_समय_stamp_raw() + tcptw->tw_ts_offset,
			tcptw->tw_ts_recent, tw->tw_bound_dev_अगर, tcp_twsk_md5_key(tcptw),
			tw->tw_tclass, cpu_to_be32(tw->tw_flowlabel), tw->tw_priority);

	inet_twsk_put(tw);
पूर्ण

अटल व्योम tcp_v6_reqsk_send_ack(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb,
				  काष्ठा request_sock *req)
अणु
	पूर्णांक l3index;

	l3index = tcp_v6_sdअगर(skb) ? tcp_v6_iअगर_l3_slave(skb) : 0;

	/* sk->sk_state == TCP_LISTEN -> क्रम regular TCP_SYN_RECV
	 * sk->sk_state == TCP_SYN_RECV -> क्रम Fast Open.
	 */
	/* RFC 7323 2.3
	 * The winकरोw field (SEG.WND) of every outgoing segment, with the
	 * exception of <SYN> segments, MUST be right-shअगरted by
	 * Rcv.Wind.Shअगरt bits:
	 */
	tcp_v6_send_ack(sk, skb, (sk->sk_state == TCP_LISTEN) ?
			tcp_rsk(req)->snt_isn + 1 : tcp_sk(sk)->snd_nxt,
			tcp_rsk(req)->rcv_nxt,
			req->rsk_rcv_wnd >> inet_rsk(req)->rcv_wscale,
			tcp_समय_stamp_raw() + tcp_rsk(req)->ts_off,
			req->ts_recent, sk->sk_bound_dev_अगर,
			tcp_v6_md5_करो_lookup(sk, &ipv6_hdr(skb)->saddr, l3index),
			ipv6_get_dsfield(ipv6_hdr(skb)), 0, sk->sk_priority);
पूर्ण


अटल काष्ठा sock *tcp_v6_cookie_check(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_SYN_COOKIES
	स्थिर काष्ठा tcphdr *th = tcp_hdr(skb);

	अगर (!th->syn)
		sk = cookie_v6_check(sk, skb);
#पूर्ण_अगर
	वापस sk;
पूर्ण

u16 tcp_v6_get_syncookie(काष्ठा sock *sk, काष्ठा ipv6hdr *iph,
			 काष्ठा tcphdr *th, u32 *cookie)
अणु
	u16 mss = 0;
#अगर_घोषित CONFIG_SYN_COOKIES
	mss = tcp_get_syncookie_mss(&tcp6_request_sock_ops,
				    &tcp_request_sock_ipv6_ops, sk, th);
	अगर (mss) अणु
		*cookie = __cookie_v6_init_sequence(iph, th, &mss);
		tcp_synq_overflow(sk);
	पूर्ण
#पूर्ण_अगर
	वापस mss;
पूर्ण

अटल पूर्णांक tcp_v6_conn_request(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अगर (skb->protocol == htons(ETH_P_IP))
		वापस tcp_v4_conn_request(sk, skb);

	अगर (!ipv6_unicast_destination(skb))
		जाओ drop;

	अगर (ipv6_addr_v4mapped(&ipv6_hdr(skb)->saddr)) अणु
		__IP6_INC_STATS(sock_net(sk), शून्य, IPSTATS_MIB_INHDRERRORS);
		वापस 0;
	पूर्ण

	वापस tcp_conn_request(&tcp6_request_sock_ops,
				&tcp_request_sock_ipv6_ops, sk, skb);

drop:
	tcp_listendrop(sk);
	वापस 0; /* करोn't send reset */
पूर्ण

अटल व्योम tcp_v6_restore_cb(काष्ठा sk_buff *skb)
अणु
	/* We need to move header back to the beginning अगर xfrm6_policy_check()
	 * and tcp_v6_fill_cb() are going to be called again.
	 * ip6_datagram_recv_specअगरic_ctl() also expects IP6CB to be there.
	 */
	स_हटाओ(IP6CB(skb), &TCP_SKB_CB(skb)->header.h6,
		माप(काष्ठा inet6_skb_parm));
पूर्ण

अटल काष्ठा sock *tcp_v6_syn_recv_sock(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb,
					 काष्ठा request_sock *req,
					 काष्ठा dst_entry *dst,
					 काष्ठा request_sock *req_unhash,
					 bool *own_req)
अणु
	काष्ठा inet_request_sock *ireq;
	काष्ठा ipv6_pinfo *newnp;
	स्थिर काष्ठा ipv6_pinfo *np = tcp_inet6_sk(sk);
	काष्ठा ipv6_txoptions *opt;
	काष्ठा inet_sock *newinet;
	bool found_dup_sk = false;
	काष्ठा tcp_sock *newtp;
	काष्ठा sock *newsk;
#अगर_घोषित CONFIG_TCP_MD5SIG
	काष्ठा tcp_md5sig_key *key;
	पूर्णांक l3index;
#पूर्ण_अगर
	काष्ठा flowi6 fl6;

	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		/*
		 *	v6 mapped
		 */

		newsk = tcp_v4_syn_recv_sock(sk, skb, req, dst,
					     req_unhash, own_req);

		अगर (!newsk)
			वापस शून्य;

		inet_sk(newsk)->pinet6 = tcp_inet6_sk(newsk);

		newinet = inet_sk(newsk);
		newnp = tcp_inet6_sk(newsk);
		newtp = tcp_sk(newsk);

		स_नकल(newnp, np, माप(काष्ठा ipv6_pinfo));

		newnp->saddr = newsk->sk_v6_rcv_saddr;

		inet_csk(newsk)->icsk_af_ops = &ipv6_mapped;
		अगर (sk_is_mptcp(newsk))
			mptcpv6_handle_mapped(newsk, true);
		newsk->sk_backlog_rcv = tcp_v4_करो_rcv;
#अगर_घोषित CONFIG_TCP_MD5SIG
		newtp->af_specअगरic = &tcp_sock_ipv6_mapped_specअगरic;
#पूर्ण_अगर

		newnp->ipv6_mc_list = शून्य;
		newnp->ipv6_ac_list = शून्य;
		newnp->ipv6_fl_list = शून्य;
		newnp->pktoptions  = शून्य;
		newnp->opt	   = शून्य;
		newnp->mcast_oअगर   = inet_iअगर(skb);
		newnp->mcast_hops  = ip_hdr(skb)->ttl;
		newnp->rcv_flowinfo = 0;
		अगर (np->repflow)
			newnp->flow_label = 0;

		/*
		 * No need to अक्षरge this sock to the relevant IPv6 refcnt debug socks count
		 * here, tcp_create_खोलोreq_child now करोes this क्रम us, see the comment in
		 * that function क्रम the gory details. -acme
		 */

		/* It is tricky place. Until this moment IPv4 tcp
		   worked with IPv6 icsk.icsk_af_ops.
		   Sync it now.
		 */
		tcp_sync_mss(newsk, inet_csk(newsk)->icsk_pmtu_cookie);

		वापस newsk;
	पूर्ण

	ireq = inet_rsk(req);

	अगर (sk_acceptq_is_full(sk))
		जाओ out_overflow;

	अगर (!dst) अणु
		dst = inet6_csk_route_req(sk, &fl6, req, IPPROTO_TCP);
		अगर (!dst)
			जाओ out;
	पूर्ण

	newsk = tcp_create_खोलोreq_child(sk, req, skb);
	अगर (!newsk)
		जाओ out_nonewsk;

	/*
	 * No need to अक्षरge this sock to the relevant IPv6 refcnt debug socks
	 * count here, tcp_create_खोलोreq_child now करोes this क्रम us, see the
	 * comment in that function क्रम the gory details. -acme
	 */

	newsk->sk_gso_type = SKB_GSO_TCPV6;
	ip6_dst_store(newsk, dst, शून्य, शून्य);
	inet6_sk_rx_dst_set(newsk, skb);

	inet_sk(newsk)->pinet6 = tcp_inet6_sk(newsk);

	newtp = tcp_sk(newsk);
	newinet = inet_sk(newsk);
	newnp = tcp_inet6_sk(newsk);

	स_नकल(newnp, np, माप(काष्ठा ipv6_pinfo));

	newsk->sk_v6_daddr = ireq->ir_v6_rmt_addr;
	newnp->saddr = ireq->ir_v6_loc_addr;
	newsk->sk_v6_rcv_saddr = ireq->ir_v6_loc_addr;
	newsk->sk_bound_dev_अगर = ireq->ir_iअगर;

	/* Now IPv6 options...

	   First: no IPv4 options.
	 */
	newinet->inet_opt = शून्य;
	newnp->ipv6_mc_list = शून्य;
	newnp->ipv6_ac_list = शून्य;
	newnp->ipv6_fl_list = शून्य;

	/* Clone RX bits */
	newnp->rxopt.all = np->rxopt.all;

	newnp->pktoptions = शून्य;
	newnp->opt	  = शून्य;
	newnp->mcast_oअगर  = tcp_v6_iअगर(skb);
	newnp->mcast_hops = ipv6_hdr(skb)->hop_limit;
	newnp->rcv_flowinfo = ip6_flowinfo(ipv6_hdr(skb));
	अगर (np->repflow)
		newnp->flow_label = ip6_flowlabel(ipv6_hdr(skb));

	/* Set ToS of the new socket based upon the value of incoming SYN.
	 * ECT bits are set later in tcp_init_transfer().
	 */
	अगर (sock_net(sk)->ipv4.sysctl_tcp_reflect_tos)
		newnp->tclass = tcp_rsk(req)->syn_tos & ~INET_ECN_MASK;

	/* Clone native IPv6 options from listening socket (अगर any)

	   Yes, keeping reference count would be much more clever,
	   but we make one more one thing there: reattach opपंचांगem
	   to newsk.
	 */
	opt = ireq->ipv6_opt;
	अगर (!opt)
		opt = rcu_dereference(np->opt);
	अगर (opt) अणु
		opt = ipv6_dup_options(newsk, opt);
		RCU_INIT_POINTER(newnp->opt, opt);
	पूर्ण
	inet_csk(newsk)->icsk_ext_hdr_len = 0;
	अगर (opt)
		inet_csk(newsk)->icsk_ext_hdr_len = opt->opt_nflen +
						    opt->opt_flen;

	tcp_ca_खोलोreq_child(newsk, dst);

	tcp_sync_mss(newsk, dst_mtu(dst));
	newtp->advmss = tcp_mss_clamp(tcp_sk(sk), dst_metric_advmss(dst));

	tcp_initialize_rcv_mss(newsk);

	newinet->inet_daddr = newinet->inet_saddr = LOOPBACK4_IPV6;
	newinet->inet_rcv_saddr = LOOPBACK4_IPV6;

#अगर_घोषित CONFIG_TCP_MD5SIG
	l3index = l3mdev_master_अगरindex_by_index(sock_net(sk), ireq->ir_iअगर);

	/* Copy over the MD5 key from the original socket */
	key = tcp_v6_md5_करो_lookup(sk, &newsk->sk_v6_daddr, l3index);
	अगर (key) अणु
		/* We're using one, so create a matching key
		 * on the newsk काष्ठाure. If we fail to get
		 * memory, then we end up not copying the key
		 * across. Shucks.
		 */
		tcp_md5_करो_add(newsk, (जोड़ tcp_md5_addr *)&newsk->sk_v6_daddr,
			       AF_INET6, 128, l3index, key->key, key->keylen,
			       sk_gfp_mask(sk, GFP_ATOMIC));
	पूर्ण
#पूर्ण_अगर

	अगर (__inet_inherit_port(sk, newsk) < 0) अणु
		inet_csk_prepare_क्रमced_बंद(newsk);
		tcp_करोne(newsk);
		जाओ out;
	पूर्ण
	*own_req = inet_ehash_nolisten(newsk, req_to_sk(req_unhash),
				       &found_dup_sk);
	अगर (*own_req) अणु
		tcp_move_syn(newtp, req);

		/* Clone pktoptions received with SYN, अगर we own the req */
		अगर (ireq->pktopts) अणु
			newnp->pktoptions = skb_clone(ireq->pktopts,
						      sk_gfp_mask(sk, GFP_ATOMIC));
			consume_skb(ireq->pktopts);
			ireq->pktopts = शून्य;
			अगर (newnp->pktoptions) अणु
				tcp_v6_restore_cb(newnp->pktoptions);
				skb_set_owner_r(newnp->pktoptions, newsk);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
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

out_overflow:
	__NET_INC_STATS(sock_net(sk), LINUX_MIB_LISTENOVERFLOWS);
out_nonewsk:
	dst_release(dst);
out:
	tcp_listendrop(sk);
	वापस शून्य;
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
अटल पूर्णांक tcp_v6_करो_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6_pinfo *np = tcp_inet6_sk(sk);
	काष्ठा sk_buff *opt_skb = शून्य;
	काष्ठा tcp_sock *tp;

	/* Imagine: socket is IPv6. IPv4 packet arrives,
	   goes to IPv4 receive handler and backlogged.
	   From backlog it always goes here. Kerboom...
	   Fortunately, tcp_rcv_established and rcv_established
	   handle them correctly, but it is not हाल with
	   tcp_v6_hnd_req and tcp_v6_send_reset().   --ANK
	 */

	अगर (skb->protocol == htons(ETH_P_IP))
		वापस tcp_v4_करो_rcv(sk, skb);

	/*
	 *	socket locking is here क्रम SMP purposes as backlog rcv
	 *	is currently called with bh processing disabled.
	 */

	/* Do Stevens' IPV6_PKTOPTIONS.

	   Yes, guys, it is the only place in our code, where we
	   may make it not affecting IPv4.
	   The rest of code is protocol independent,
	   and I करो not like idea to uglअगरy IPv4.

	   Actually, all the idea behind IPV6_PKTOPTIONS
	   looks not very well thought. For now we latch
	   options, received in the last packet, enqueued
	   by tcp. Feel मुक्त to propose better solution.
					       --ANK (980728)
	 */
	अगर (np->rxopt.all)
		opt_skb = skb_clone(skb, sk_gfp_mask(sk, GFP_ATOMIC));

	अगर (sk->sk_state == TCP_ESTABLISHED) अणु /* Fast path */
		काष्ठा dst_entry *dst = sk->sk_rx_dst;

		sock_rps_save_rxhash(sk, skb);
		sk_mark_napi_id(sk, skb);
		अगर (dst) अणु
			अगर (inet_sk(sk)->rx_dst_अगरindex != skb->skb_iअगर ||
			    INसूचीECT_CALL_1(dst->ops->check, ip6_dst_check,
					    dst, np->rx_dst_cookie) == शून्य) अणु
				dst_release(dst);
				sk->sk_rx_dst = शून्य;
			पूर्ण
		पूर्ण

		tcp_rcv_established(sk, skb);
		अगर (opt_skb)
			जाओ ipv6_pktoptions;
		वापस 0;
	पूर्ण

	अगर (tcp_checksum_complete(skb))
		जाओ csum_err;

	अगर (sk->sk_state == TCP_LISTEN) अणु
		काष्ठा sock *nsk = tcp_v6_cookie_check(sk, skb);

		अगर (!nsk)
			जाओ discard;

		अगर (nsk != sk) अणु
			अगर (tcp_child_process(sk, nsk, skb))
				जाओ reset;
			अगर (opt_skb)
				__kमुक्त_skb(opt_skb);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा
		sock_rps_save_rxhash(sk, skb);

	अगर (tcp_rcv_state_process(sk, skb))
		जाओ reset;
	अगर (opt_skb)
		जाओ ipv6_pktoptions;
	वापस 0;

reset:
	tcp_v6_send_reset(sk, skb);
discard:
	अगर (opt_skb)
		__kमुक्त_skb(opt_skb);
	kमुक्त_skb(skb);
	वापस 0;
csum_err:
	TCP_INC_STATS(sock_net(sk), TCP_MIB_CSUMERRORS);
	TCP_INC_STATS(sock_net(sk), TCP_MIB_INERRS);
	जाओ discard;


ipv6_pktoptions:
	/* Do you ask, what is it?

	   1. skb was enqueued by tcp.
	   2. skb is added to tail of पढ़ो queue, rather than out of order.
	   3. socket is not in passive state.
	   4. Finally, it really contains options, which user wants to receive.
	 */
	tp = tcp_sk(sk);
	अगर (TCP_SKB_CB(opt_skb)->end_seq == tp->rcv_nxt &&
	    !((1 << sk->sk_state) & (TCPF_CLOSE | TCPF_LISTEN))) अणु
		अगर (np->rxopt.bits.rxinfo || np->rxopt.bits.rxoinfo)
			np->mcast_oअगर = tcp_v6_iअगर(opt_skb);
		अगर (np->rxopt.bits.rxhlim || np->rxopt.bits.rxohlim)
			np->mcast_hops = ipv6_hdr(opt_skb)->hop_limit;
		अगर (np->rxopt.bits.rxflow || np->rxopt.bits.rxtclass)
			np->rcv_flowinfo = ip6_flowinfo(ipv6_hdr(opt_skb));
		अगर (np->repflow)
			np->flow_label = ip6_flowlabel(ipv6_hdr(opt_skb));
		अगर (ipv6_opt_accepted(sk, opt_skb, &TCP_SKB_CB(opt_skb)->header.h6)) अणु
			skb_set_owner_r(opt_skb, sk);
			tcp_v6_restore_cb(opt_skb);
			opt_skb = xchg(&np->pktoptions, opt_skb);
		पूर्ण अन्यथा अणु
			__kमुक्त_skb(opt_skb);
			opt_skb = xchg(&np->pktoptions, शून्य);
		पूर्ण
	पूर्ण

	kमुक्त_skb(opt_skb);
	वापस 0;
पूर्ण

अटल व्योम tcp_v6_fill_cb(काष्ठा sk_buff *skb, स्थिर काष्ठा ipv6hdr *hdr,
			   स्थिर काष्ठा tcphdr *th)
अणु
	/* This is tricky: we move IP6CB at its correct location पूर्णांकo
	 * TCP_SKB_CB(). It must be करोne after xfrm6_policy_check(), because
	 * _decode_session6() uses IP6CB().
	 * barrier() makes sure compiler won't play aliasing games.
	 */
	स_हटाओ(&TCP_SKB_CB(skb)->header.h6, IP6CB(skb),
		माप(काष्ठा inet6_skb_parm));
	barrier();

	TCP_SKB_CB(skb)->seq = ntohl(th->seq);
	TCP_SKB_CB(skb)->end_seq = (TCP_SKB_CB(skb)->seq + th->syn + th->fin +
				    skb->len - th->करोff*4);
	TCP_SKB_CB(skb)->ack_seq = ntohl(th->ack_seq);
	TCP_SKB_CB(skb)->tcp_flags = tcp_flag_byte(th);
	TCP_SKB_CB(skb)->tcp_tw_isn = 0;
	TCP_SKB_CB(skb)->ip_dsfield = ipv6_get_dsfield(hdr);
	TCP_SKB_CB(skb)->sacked = 0;
	TCP_SKB_CB(skb)->has_rxtstamp =
			skb->tstamp || skb_hwtstamps(skb)->hwtstamp;
पूर्ण

INसूचीECT_CALLABLE_SCOPE पूर्णांक tcp_v6_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *skb_to_मुक्त;
	पूर्णांक sdअगर = inet6_sdअगर(skb);
	पूर्णांक dअगर = inet6_iअगर(skb);
	स्थिर काष्ठा tcphdr *th;
	स्थिर काष्ठा ipv6hdr *hdr;
	bool refcounted;
	काष्ठा sock *sk;
	पूर्णांक ret;
	काष्ठा net *net = dev_net(skb->dev);

	अगर (skb->pkt_type != PACKET_HOST)
		जाओ discard_it;

	/*
	 *	Count it even अगर it's bad.
	 */
	__TCP_INC_STATS(net, TCP_MIB_INSEGS);

	अगर (!pskb_may_pull(skb, माप(काष्ठा tcphdr)))
		जाओ discard_it;

	th = (स्थिर काष्ठा tcphdr *)skb->data;

	अगर (unlikely(th->करोff < माप(काष्ठा tcphdr)/4))
		जाओ bad_packet;
	अगर (!pskb_may_pull(skb, th->करोff*4))
		जाओ discard_it;

	अगर (skb_checksum_init(skb, IPPROTO_TCP, ip6_compute_pseuकरो))
		जाओ csum_error;

	th = (स्थिर काष्ठा tcphdr *)skb->data;
	hdr = ipv6_hdr(skb);

lookup:
	sk = __inet6_lookup_skb(&tcp_hashinfo, skb, __tcp_hdrlen(th),
				th->source, th->dest, inet6_iअगर(skb), sdअगर,
				&refcounted);
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
		अगर (tcp_v6_inbound_md5_hash(sk, skb, dअगर, sdअगर)) अणु
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
		sock_hold(sk);
		refcounted = true;
		nsk = शून्य;
		अगर (!tcp_filter(sk, skb)) अणु
			th = (स्थिर काष्ठा tcphdr *)skb->data;
			hdr = ipv6_hdr(skb);
			tcp_v6_fill_cb(skb, hdr, th);
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
				tcp_v6_restore_cb(skb);
				sock_put(sk);
				जाओ lookup;
			पूर्ण
			जाओ discard_and_rअन्यथा;
		पूर्ण
		अगर (nsk == sk) अणु
			reqsk_put(req);
			tcp_v6_restore_cb(skb);
		पूर्ण अन्यथा अगर (tcp_child_process(sk, nsk, skb)) अणु
			tcp_v6_send_reset(nsk, skb);
			जाओ discard_and_rअन्यथा;
		पूर्ण अन्यथा अणु
			sock_put(sk);
			वापस 0;
		पूर्ण
	पूर्ण
	अगर (hdr->hop_limit < tcp_inet6_sk(sk)->min_hopcount) अणु
		__NET_INC_STATS(net, LINUX_MIB_TCPMINTTLDROP);
		जाओ discard_and_rअन्यथा;
	पूर्ण

	अगर (!xfrm6_policy_check(sk, XFRM_POLICY_IN, skb))
		जाओ discard_and_rअन्यथा;

	अगर (tcp_v6_inbound_md5_hash(sk, skb, dअगर, sdअगर))
		जाओ discard_and_rअन्यथा;

	अगर (tcp_filter(sk, skb))
		जाओ discard_and_rअन्यथा;
	th = (स्थिर काष्ठा tcphdr *)skb->data;
	hdr = ipv6_hdr(skb);
	tcp_v6_fill_cb(skb, hdr, th);

	skb->dev = शून्य;

	अगर (sk->sk_state == TCP_LISTEN) अणु
		ret = tcp_v6_करो_rcv(sk, skb);
		जाओ put_and_वापस;
	पूर्ण

	sk_incoming_cpu_update(sk);

	bh_lock_sock_nested(sk);
	tcp_segs_in(tcp_sk(sk), skb);
	ret = 0;
	अगर (!sock_owned_by_user(sk)) अणु
		skb_to_मुक्त = sk->sk_rx_skb_cache;
		sk->sk_rx_skb_cache = शून्य;
		ret = tcp_v6_करो_rcv(sk, skb);
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
	वापस ret ? -1 : 0;

no_tcp_socket:
	अगर (!xfrm6_policy_check(शून्य, XFRM_POLICY_IN, skb))
		जाओ discard_it;

	tcp_v6_fill_cb(skb, hdr, th);

	अगर (tcp_checksum_complete(skb)) अणु
csum_error:
		__TCP_INC_STATS(net, TCP_MIB_CSUMERRORS);
bad_packet:
		__TCP_INC_STATS(net, TCP_MIB_INERRS);
	पूर्ण अन्यथा अणु
		tcp_v6_send_reset(शून्य, skb);
	पूर्ण

discard_it:
	kमुक्त_skb(skb);
	वापस 0;

discard_and_rअन्यथा:
	sk_drops_add(sk, skb);
	अगर (refcounted)
		sock_put(sk);
	जाओ discard_it;

करो_समय_रुको:
	अगर (!xfrm6_policy_check(शून्य, XFRM_POLICY_IN, skb)) अणु
		inet_twsk_put(inet_twsk(sk));
		जाओ discard_it;
	पूर्ण

	tcp_v6_fill_cb(skb, hdr, th);

	अगर (tcp_checksum_complete(skb)) अणु
		inet_twsk_put(inet_twsk(sk));
		जाओ csum_error;
	पूर्ण

	चयन (tcp_समयरुको_state_process(inet_twsk(sk), skb, th)) अणु
	हाल TCP_TW_SYN:
	अणु
		काष्ठा sock *sk2;

		sk2 = inet6_lookup_listener(dev_net(skb->dev), &tcp_hashinfo,
					    skb, __tcp_hdrlen(th),
					    &ipv6_hdr(skb)->saddr, th->source,
					    &ipv6_hdr(skb)->daddr,
					    ntohs(th->dest),
					    tcp_v6_iअगर_l3_slave(skb),
					    sdअगर);
		अगर (sk2) अणु
			काष्ठा inet_समयरुको_sock *tw = inet_twsk(sk);
			inet_twsk_deschedule_put(tw);
			sk = sk2;
			tcp_v6_restore_cb(skb);
			refcounted = false;
			जाओ process;
		पूर्ण
	पूर्ण
		/* to ACK */
		fallthrough;
	हाल TCP_TW_ACK:
		tcp_v6_समयरुको_ack(sk, skb);
		अवरोध;
	हाल TCP_TW_RST:
		tcp_v6_send_reset(sk, skb);
		inet_twsk_deschedule_put(inet_twsk(sk));
		जाओ discard_it;
	हाल TCP_TW_SUCCESS:
		;
	पूर्ण
	जाओ discard_it;
पूर्ण

INसूचीECT_CALLABLE_SCOPE व्योम tcp_v6_early_demux(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ipv6hdr *hdr;
	स्थिर काष्ठा tcphdr *th;
	काष्ठा sock *sk;

	अगर (skb->pkt_type != PACKET_HOST)
		वापस;

	अगर (!pskb_may_pull(skb, skb_transport_offset(skb) + माप(काष्ठा tcphdr)))
		वापस;

	hdr = ipv6_hdr(skb);
	th = tcp_hdr(skb);

	अगर (th->करोff < माप(काष्ठा tcphdr) / 4)
		वापस;

	/* Note : We use inet6_iअगर() here, not tcp_v6_iअगर() */
	sk = __inet6_lookup_established(dev_net(skb->dev), &tcp_hashinfo,
					&hdr->saddr, th->source,
					&hdr->daddr, ntohs(th->dest),
					inet6_iअगर(skb), inet6_sdअगर(skb));
	अगर (sk) अणु
		skb->sk = sk;
		skb->deकाष्ठाor = sock_edemux;
		अगर (sk_fullsock(sk)) अणु
			काष्ठा dst_entry *dst = READ_ONCE(sk->sk_rx_dst);

			अगर (dst)
				dst = dst_check(dst, tcp_inet6_sk(sk)->rx_dst_cookie);
			अगर (dst &&
			    inet_sk(sk)->rx_dst_अगरindex == skb->skb_iअगर)
				skb_dst_set_noref(skb, dst);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा समयरुको_sock_ops tcp6_समयरुको_sock_ops = अणु
	.twsk_obj_size	= माप(काष्ठा tcp6_समयरुको_sock),
	.twsk_unique	= tcp_twsk_unique,
	.twsk_deकाष्ठाor = tcp_twsk_deकाष्ठाor,
पूर्ण;

INसूचीECT_CALLABLE_SCOPE व्योम tcp_v6_send_check(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);

	__tcp_v6_send_check(skb, &np->saddr, &sk->sk_v6_daddr);
पूर्ण

स्थिर काष्ठा inet_connection_sock_af_ops ipv6_specअगरic = अणु
	.queue_xmit	   = inet6_csk_xmit,
	.send_check	   = tcp_v6_send_check,
	.rebuild_header	   = inet6_sk_rebuild_header,
	.sk_rx_dst_set	   = inet6_sk_rx_dst_set,
	.conn_request	   = tcp_v6_conn_request,
	.syn_recv_sock	   = tcp_v6_syn_recv_sock,
	.net_header_len	   = माप(काष्ठा ipv6hdr),
	.net_frag_header_len = माप(काष्ठा frag_hdr),
	.setsockopt	   = ipv6_setsockopt,
	.माला_लोockopt	   = ipv6_माला_लोockopt,
	.addr2sockaddr	   = inet6_csk_addr2sockaddr,
	.sockaddr_len	   = माप(काष्ठा sockaddr_in6),
	.mtu_reduced	   = tcp_v6_mtu_reduced,
पूर्ण;

#अगर_घोषित CONFIG_TCP_MD5SIG
अटल स्थिर काष्ठा tcp_sock_af_ops tcp_sock_ipv6_specअगरic = अणु
	.md5_lookup	=	tcp_v6_md5_lookup,
	.calc_md5_hash	=	tcp_v6_md5_hash_skb,
	.md5_parse	=	tcp_v6_parse_md5_keys,
पूर्ण;
#पूर्ण_अगर

/*
 *	TCP over IPv4 via INET6 API
 */
अटल स्थिर काष्ठा inet_connection_sock_af_ops ipv6_mapped = अणु
	.queue_xmit	   = ip_queue_xmit,
	.send_check	   = tcp_v4_send_check,
	.rebuild_header	   = inet_sk_rebuild_header,
	.sk_rx_dst_set	   = inet_sk_rx_dst_set,
	.conn_request	   = tcp_v6_conn_request,
	.syn_recv_sock	   = tcp_v6_syn_recv_sock,
	.net_header_len	   = माप(काष्ठा iphdr),
	.setsockopt	   = ipv6_setsockopt,
	.माला_लोockopt	   = ipv6_माला_लोockopt,
	.addr2sockaddr	   = inet6_csk_addr2sockaddr,
	.sockaddr_len	   = माप(काष्ठा sockaddr_in6),
	.mtu_reduced	   = tcp_v4_mtu_reduced,
पूर्ण;

#अगर_घोषित CONFIG_TCP_MD5SIG
अटल स्थिर काष्ठा tcp_sock_af_ops tcp_sock_ipv6_mapped_specअगरic = अणु
	.md5_lookup	=	tcp_v4_md5_lookup,
	.calc_md5_hash	=	tcp_v4_md5_hash_skb,
	.md5_parse	=	tcp_v6_parse_md5_keys,
पूर्ण;
#पूर्ण_अगर

/* NOTE: A lot of things set to zero explicitly by call to
 *       sk_alloc() so need not be करोne here.
 */
अटल पूर्णांक tcp_v6_init_sock(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	tcp_init_sock(sk);

	icsk->icsk_af_ops = &ipv6_specअगरic;

#अगर_घोषित CONFIG_TCP_MD5SIG
	tcp_sk(sk)->af_specअगरic = &tcp_sock_ipv6_specअगरic;
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम tcp_v6_destroy_sock(काष्ठा sock *sk)
अणु
	tcp_v4_destroy_sock(sk);
	inet6_destroy_sock(sk);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
/* Proc fileप्रणाली TCPv6 sock list dumping. */
अटल व्योम get_खोलोreq6(काष्ठा seq_file *seq,
			 स्थिर काष्ठा request_sock *req, पूर्णांक i)
अणु
	दीर्घ ttd = req->rsk_समयr.expires - jअगरfies;
	स्थिर काष्ठा in6_addr *src = &inet_rsk(req)->ir_v6_loc_addr;
	स्थिर काष्ठा in6_addr *dest = &inet_rsk(req)->ir_v6_rmt_addr;

	अगर (ttd < 0)
		ttd = 0;

	seq_म_लिखो(seq,
		   "%4d: %08X%08X%08X%08X:%04X %08X%08X%08X%08X:%04X "
		   "%02X %08X:%08X %02X:%08lX %08X %5u %8d %d %d %pK\n",
		   i,
		   src->s6_addr32[0], src->s6_addr32[1],
		   src->s6_addr32[2], src->s6_addr32[3],
		   inet_rsk(req)->ir_num,
		   dest->s6_addr32[0], dest->s6_addr32[1],
		   dest->s6_addr32[2], dest->s6_addr32[3],
		   ntohs(inet_rsk(req)->ir_rmt_port),
		   TCP_SYN_RECV,
		   0, 0, /* could prपूर्णांक option size, but that is af dependent. */
		   1,   /* समयrs active (only the expire समयr) */
		   jअगरfies_to_घड़ी_प्रकार(ttd),
		   req->num_समयout,
		   from_kuid_munged(seq_user_ns(seq),
				    sock_i_uid(req->rsk_listener)),
		   0,  /* non standard समयr */
		   0, /* खोलो_requests have no inode */
		   0, req);
पूर्ण

अटल व्योम get_tcp6_sock(काष्ठा seq_file *seq, काष्ठा sock *sp, पूर्णांक i)
अणु
	स्थिर काष्ठा in6_addr *dest, *src;
	__u16 destp, srcp;
	पूर्णांक समयr_active;
	अचिन्हित दीर्घ समयr_expires;
	स्थिर काष्ठा inet_sock *inet = inet_sk(sp);
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sp);
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sp);
	स्थिर काष्ठा fastखोलो_queue *fastखोलोq = &icsk->icsk_accept_queue.fastखोलोq;
	पूर्णांक rx_queue;
	पूर्णांक state;

	dest  = &sp->sk_v6_daddr;
	src   = &sp->sk_v6_rcv_saddr;
	destp = ntohs(inet->inet_dport);
	srcp  = ntohs(inet->inet_sport);

	अगर (icsk->icsk_pending == ICSK_TIME_RETRANS ||
	    icsk->icsk_pending == ICSK_TIME_REO_TIMEOUT ||
	    icsk->icsk_pending == ICSK_TIME_LOSS_PROBE) अणु
		समयr_active	= 1;
		समयr_expires	= icsk->icsk_समयout;
	पूर्ण अन्यथा अगर (icsk->icsk_pending == ICSK_TIME_PROBE0) अणु
		समयr_active	= 4;
		समयr_expires	= icsk->icsk_समयout;
	पूर्ण अन्यथा अगर (समयr_pending(&sp->sk_समयr)) अणु
		समयr_active	= 2;
		समयr_expires	= sp->sk_समयr.expires;
	पूर्ण अन्यथा अणु
		समयr_active	= 0;
		समयr_expires = jअगरfies;
	पूर्ण

	state = inet_sk_state_load(sp);
	अगर (state == TCP_LISTEN)
		rx_queue = READ_ONCE(sp->sk_ack_backlog);
	अन्यथा
		/* Because we करोn't lock the socket,
		 * we might find a transient negative value.
		 */
		rx_queue = max_t(पूर्णांक, READ_ONCE(tp->rcv_nxt) -
				      READ_ONCE(tp->copied_seq), 0);

	seq_म_लिखो(seq,
		   "%4d: %08X%08X%08X%08X:%04X %08X%08X%08X%08X:%04X "
		   "%02X %08X:%08X %02X:%08lX %08X %5u %8d %lu %d %pK %lu %lu %u %u %d\n",
		   i,
		   src->s6_addr32[0], src->s6_addr32[1],
		   src->s6_addr32[2], src->s6_addr32[3], srcp,
		   dest->s6_addr32[0], dest->s6_addr32[1],
		   dest->s6_addr32[2], dest->s6_addr32[3], destp,
		   state,
		   READ_ONCE(tp->ग_लिखो_seq) - tp->snd_una,
		   rx_queue,
		   समयr_active,
		   jअगरfies_delta_to_घड़ी_प्रकार(समयr_expires - jअगरfies),
		   icsk->icsk_retransmits,
		   from_kuid_munged(seq_user_ns(seq), sock_i_uid(sp)),
		   icsk->icsk_probes_out,
		   sock_i_ino(sp),
		   refcount_पढ़ो(&sp->sk_refcnt), sp,
		   jअगरfies_to_घड़ी_प्रकार(icsk->icsk_rto),
		   jअगरfies_to_घड़ी_प्रकार(icsk->icsk_ack.ato),
		   (icsk->icsk_ack.quick << 1) | inet_csk_in_pingpong_mode(sp),
		   tp->snd_cwnd,
		   state == TCP_LISTEN ?
			fastखोलोq->max_qlen :
			(tcp_in_initial_slowstart(tp) ? -1 : tp->snd_ssthresh)
		   );
पूर्ण

अटल व्योम get_समयरुको6_sock(काष्ठा seq_file *seq,
			       काष्ठा inet_समयरुको_sock *tw, पूर्णांक i)
अणु
	दीर्घ delta = tw->tw_समयr.expires - jअगरfies;
	स्थिर काष्ठा in6_addr *dest, *src;
	__u16 destp, srcp;

	dest = &tw->tw_v6_daddr;
	src  = &tw->tw_v6_rcv_saddr;
	destp = ntohs(tw->tw_dport);
	srcp  = ntohs(tw->tw_sport);

	seq_म_लिखो(seq,
		   "%4d: %08X%08X%08X%08X:%04X %08X%08X%08X%08X:%04X "
		   "%02X %08X:%08X %02X:%08lX %08X %5d %8d %d %d %pK\n",
		   i,
		   src->s6_addr32[0], src->s6_addr32[1],
		   src->s6_addr32[2], src->s6_addr32[3], srcp,
		   dest->s6_addr32[0], dest->s6_addr32[1],
		   dest->s6_addr32[2], dest->s6_addr32[3], destp,
		   tw->tw_substate, 0, 0,
		   3, jअगरfies_delta_to_घड़ी_प्रकार(delta), 0, 0, 0, 0,
		   refcount_पढ़ो(&tw->tw_refcnt), tw);
पूर्ण

अटल पूर्णांक tcp6_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा tcp_iter_state *st;
	काष्ठा sock *sk = v;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq,
			 "  sl  "
			 "local_address                         "
			 "remote_address                        "
			 "st tx_queue rx_queue tr tm->when retrnsmt"
			 "   uid  timeout inode\n");
		जाओ out;
	पूर्ण
	st = seq->निजी;

	अगर (sk->sk_state == TCP_TIME_WAIT)
		get_समयरुको6_sock(seq, v, st->num);
	अन्यथा अगर (sk->sk_state == TCP_NEW_SYN_RECV)
		get_खोलोreq6(seq, v, st->num);
	अन्यथा
		get_tcp6_sock(seq, v, st->num);
out:
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations tcp6_seq_ops = अणु
	.show		= tcp6_seq_show,
	.start		= tcp_seq_start,
	.next		= tcp_seq_next,
	.stop		= tcp_seq_stop,
पूर्ण;

अटल काष्ठा tcp_seq_afinfo tcp6_seq_afinfo = अणु
	.family		= AF_INET6,
पूर्ण;

पूर्णांक __net_init tcp6_proc_init(काष्ठा net *net)
अणु
	अगर (!proc_create_net_data("tcp6", 0444, net->proc_net, &tcp6_seq_ops,
			माप(काष्ठा tcp_iter_state), &tcp6_seq_afinfo))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम tcp6_proc_निकास(काष्ठा net *net)
अणु
	हटाओ_proc_entry("tcp6", net->proc_net);
पूर्ण
#पूर्ण_अगर

काष्ठा proto tcpv6_prot = अणु
	.name			= "TCPv6",
	.owner			= THIS_MODULE,
	.बंद			= tcp_बंद,
	.pre_connect		= tcp_v6_pre_connect,
	.connect		= tcp_v6_connect,
	.disconnect		= tcp_disconnect,
	.accept			= inet_csk_accept,
	.ioctl			= tcp_ioctl,
	.init			= tcp_v6_init_sock,
	.destroy		= tcp_v6_destroy_sock,
	.shutकरोwn		= tcp_shutकरोwn,
	.setsockopt		= tcp_setsockopt,
	.माला_लोockopt		= tcp_माला_लोockopt,
	.bpf_bypass_माला_लोockopt	= tcp_bpf_bypass_माला_लोockopt,
	.keepalive		= tcp_set_keepalive,
	.recvmsg		= tcp_recvmsg,
	.sendmsg		= tcp_sendmsg,
	.sendpage		= tcp_sendpage,
	.backlog_rcv		= tcp_v6_करो_rcv,
	.release_cb		= tcp_release_cb,
	.hash			= inet6_hash,
	.unhash			= inet_unhash,
	.get_port		= inet_csk_get_port,
#अगर_घोषित CONFIG_BPF_SYSCALL
	.psock_update_sk_prot	= tcp_bpf_update_proto,
#पूर्ण_अगर
	.enter_memory_pressure	= tcp_enter_memory_pressure,
	.leave_memory_pressure	= tcp_leave_memory_pressure,
	.stream_memory_मुक्त	= tcp_stream_memory_मुक्त,
	.sockets_allocated	= &tcp_sockets_allocated,
	.memory_allocated	= &tcp_memory_allocated,
	.memory_pressure	= &tcp_memory_pressure,
	.orphan_count		= &tcp_orphan_count,
	.sysctl_mem		= sysctl_tcp_mem,
	.sysctl_wmem_offset	= दुरत्व(काष्ठा net, ipv4.sysctl_tcp_wmem),
	.sysctl_rmem_offset	= दुरत्व(काष्ठा net, ipv4.sysctl_tcp_rmem),
	.max_header		= MAX_TCP_HEADER,
	.obj_size		= माप(काष्ठा tcp6_sock),
	.slab_flags		= SLAB_TYPESAFE_BY_RCU,
	.twsk_prot		= &tcp6_समयरुको_sock_ops,
	.rsk_prot		= &tcp6_request_sock_ops,
	.h.hashinfo		= &tcp_hashinfo,
	.no_स्वतःbind		= true,
	.diag_destroy		= tcp_पात,
पूर्ण;
EXPORT_SYMBOL_GPL(tcpv6_prot);

/* thinking of making this स्थिर? Don't.
 * early_demux can change based on sysctl.
 */
अटल काष्ठा inet6_protocol tcpv6_protocol = अणु
	.early_demux	=	tcp_v6_early_demux,
	.early_demux_handler =  tcp_v6_early_demux,
	.handler	=	tcp_v6_rcv,
	.err_handler	=	tcp_v6_err,
	.flags		=	INET6_PROTO_NOPOLICY|INET6_PROTO_FINAL,
पूर्ण;

अटल काष्ठा inet_protosw tcpv6_protosw = अणु
	.type		=	SOCK_STREAM,
	.protocol	=	IPPROTO_TCP,
	.prot		=	&tcpv6_prot,
	.ops		=	&inet6_stream_ops,
	.flags		=	INET_PROTOSW_PERMANENT |
				INET_PROTOSW_ICSK,
पूर्ण;

अटल पूर्णांक __net_init tcpv6_net_init(काष्ठा net *net)
अणु
	वापस inet_ctl_sock_create(&net->ipv6.tcp_sk, PF_INET6,
				    SOCK_RAW, IPPROTO_TCP, net);
पूर्ण

अटल व्योम __net_निकास tcpv6_net_निकास(काष्ठा net *net)
अणु
	inet_ctl_sock_destroy(net->ipv6.tcp_sk);
पूर्ण

अटल व्योम __net_निकास tcpv6_net_निकास_batch(काष्ठा list_head *net_निकास_list)
अणु
	inet_twsk_purge(&tcp_hashinfo, AF_INET6);
पूर्ण

अटल काष्ठा pernet_operations tcpv6_net_ops = अणु
	.init	    = tcpv6_net_init,
	.निकास	    = tcpv6_net_निकास,
	.निकास_batch = tcpv6_net_निकास_batch,
पूर्ण;

पूर्णांक __init tcpv6_init(व्योम)
अणु
	पूर्णांक ret;

	ret = inet6_add_protocol(&tcpv6_protocol, IPPROTO_TCP);
	अगर (ret)
		जाओ out;

	/* रेजिस्टर inet6 protocol */
	ret = inet6_रेजिस्टर_protosw(&tcpv6_protosw);
	अगर (ret)
		जाओ out_tcpv6_protocol;

	ret = रेजिस्टर_pernet_subsys(&tcpv6_net_ops);
	अगर (ret)
		जाओ out_tcpv6_protosw;

	ret = mptcpv6_init();
	अगर (ret)
		जाओ out_tcpv6_pernet_subsys;

out:
	वापस ret;

out_tcpv6_pernet_subsys:
	unरेजिस्टर_pernet_subsys(&tcpv6_net_ops);
out_tcpv6_protosw:
	inet6_unरेजिस्टर_protosw(&tcpv6_protosw);
out_tcpv6_protocol:
	inet6_del_protocol(&tcpv6_protocol, IPPROTO_TCP);
	जाओ out;
पूर्ण

व्योम tcpv6_निकास(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&tcpv6_net_ops);
	inet6_unरेजिस्टर_protosw(&tcpv6_protosw);
	inet6_del_protocol(&tcpv6_protocol, IPPROTO_TCP);
पूर्ण
