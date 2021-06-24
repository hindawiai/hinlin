<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Implementation of the Transmission Control Protocol(TCP).
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Mark Evans, <evansmp@uhura.aston.ac.uk>
 *		Corey Minyard <wf-rch!minyard@relay.EU.net>
 *		Florian La Roche, <flla@stud.uni-sb.de>
 *		Charles Hedrick, <hedrick@klinzhai.rutgers.edu>
 *		Linus Torvalds, <torvalds@cs.helsinki.fi>
 *		Alan Cox, <gw4pts@gw4pts.ampr.org>
 *		Matthew Dillon, <dillon@apollo.west.oic.com>
 *		Arnt Gulbअक्रमsen, <agulbra@nvg.unit.no>
 *		Jorge Cwik, <jorge@laser.satlink.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#समावेश <net/tcp.h>

अटल u32 tcp_clamp_rto_to_user_समयout(स्थिर काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	u32 elapsed, start_ts;
	s32 reमुख्यing;

	start_ts = tcp_sk(sk)->retrans_stamp;
	अगर (!icsk->icsk_user_समयout)
		वापस icsk->icsk_rto;
	elapsed = tcp_समय_stamp(tcp_sk(sk)) - start_ts;
	reमुख्यing = icsk->icsk_user_समयout - elapsed;
	अगर (reमुख्यing <= 0)
		वापस 1; /* user समयout has passed; fire ASAP */

	वापस min_t(u32, icsk->icsk_rto, msecs_to_jअगरfies(reमुख्यing));
पूर्ण

u32 tcp_clamp_probe0_to_user_समयout(स्थिर काष्ठा sock *sk, u32 when)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	u32 reमुख्यing;
	s32 elapsed;

	अगर (!icsk->icsk_user_समयout || !icsk->icsk_probes_tstamp)
		वापस when;

	elapsed = tcp_jअगरfies32 - icsk->icsk_probes_tstamp;
	अगर (unlikely(elapsed < 0))
		elapsed = 0;
	reमुख्यing = msecs_to_jअगरfies(icsk->icsk_user_समयout) - elapsed;
	reमुख्यing = max_t(u32, reमुख्यing, TCP_TIMEOUT_MIN);

	वापस min_t(u32, reमुख्यing, when);
पूर्ण

/**
 *  tcp_ग_लिखो_err() - बंद socket and save error info
 *  @sk:  The socket the error has appeared on.
 *
 *  Returns: Nothing (व्योम)
 */

अटल व्योम tcp_ग_लिखो_err(काष्ठा sock *sk)
अणु
	sk->sk_err = sk->sk_err_soft ? : ETIMEDOUT;
	sk->sk_error_report(sk);

	tcp_ग_लिखो_queue_purge(sk);
	tcp_करोne(sk);
	__NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPABORTONTIMEOUT);
पूर्ण

/**
 *  tcp_out_of_resources() - Close socket अगर out of resources
 *  @sk:        poपूर्णांकer to current socket
 *  @करो_reset:  send a last packet with reset flag
 *
 *  Do not allow orphaned sockets to eat all our resources.
 *  This is direct violation of TCP specs, but it is required
 *  to prevent DoS attacks. It is called when a retransmission समयout
 *  or zero probe समयout occurs on orphaned socket.
 *
 *  Also बंद अगर our net namespace is निकासing; in that हाल there is no
 *  hope of ever communicating again since all netns पूर्णांकerfaces are alपढ़ोy
 *  करोwn (or about to be करोwn), and we need to release our dst references,
 *  which have been moved to the netns loopback पूर्णांकerface, so the namespace
 *  can finish निकासing.  This condition is only possible अगर we are a kernel
 *  socket, as those करो not hold references to the namespace.
 *
 *  Criteria is still not confirmed experimentally and may change.
 *  We समाप्त the socket, अगर:
 *  1. If number of orphaned sockets exceeds an administratively configured
 *     limit.
 *  2. If we have strong memory pressure.
 *  3. If our net namespace is निकासing.
 */
अटल पूर्णांक tcp_out_of_resources(काष्ठा sock *sk, bool करो_reset)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	पूर्णांक shअगरt = 0;

	/* If peer करोes not खोलो winकरोw क्रम दीर्घ समय, or did not transmit
	 * anything क्रम दीर्घ समय, penalize it. */
	अगर ((s32)(tcp_jअगरfies32 - tp->lsndसमय) > 2*TCP_RTO_MAX || !करो_reset)
		shअगरt++;

	/* If some dubious ICMP arrived, penalize even more. */
	अगर (sk->sk_err_soft)
		shअगरt++;

	अगर (tcp_check_oom(sk, shअगरt)) अणु
		/* Catch exceptional हालs, when connection requires reset.
		 *      1. Last segment was sent recently. */
		अगर ((s32)(tcp_jअगरfies32 - tp->lsndसमय) <= TCP_TIMEWAIT_LEN ||
		    /*  2. Winकरोw is बंदd. */
		    (!tp->snd_wnd && !tp->packets_out))
			करो_reset = true;
		अगर (करो_reset)
			tcp_send_active_reset(sk, GFP_ATOMIC);
		tcp_करोne(sk);
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPABORTONMEMORY);
		वापस 1;
	पूर्ण

	अगर (!check_net(sock_net(sk))) अणु
		/* Not possible to send reset; just बंद */
		tcp_करोne(sk);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  tcp_orphan_retries() - Returns maximal number of retries on an orphaned socket
 *  @sk:    Poपूर्णांकer to the current socket.
 *  @alive: bool, socket alive state
 */
अटल पूर्णांक tcp_orphan_retries(काष्ठा sock *sk, bool alive)
अणु
	पूर्णांक retries = sock_net(sk)->ipv4.sysctl_tcp_orphan_retries; /* May be zero. */

	/* We know from an ICMP that something is wrong. */
	अगर (sk->sk_err_soft && !alive)
		retries = 0;

	/* However, अगर socket sent something recently, select some safe
	 * number of retries. 8 corresponds to >100 seconds with minimal
	 * RTO of 200msec. */
	अगर (retries == 0 && alive)
		retries = 8;
	वापस retries;
पूर्ण

अटल व्योम tcp_mtu_probing(काष्ठा inet_connection_sock *icsk, काष्ठा sock *sk)
अणु
	स्थिर काष्ठा net *net = sock_net(sk);
	पूर्णांक mss;

	/* Black hole detection */
	अगर (!net->ipv4.sysctl_tcp_mtu_probing)
		वापस;

	अगर (!icsk->icsk_mtup.enabled) अणु
		icsk->icsk_mtup.enabled = 1;
		icsk->icsk_mtup.probe_बारtamp = tcp_jअगरfies32;
	पूर्ण अन्यथा अणु
		mss = tcp_mtu_to_mss(sk, icsk->icsk_mtup.search_low) >> 1;
		mss = min(net->ipv4.sysctl_tcp_base_mss, mss);
		mss = max(mss, net->ipv4.sysctl_tcp_mtu_probe_न्यूनमान);
		mss = max(mss, net->ipv4.sysctl_tcp_min_snd_mss);
		icsk->icsk_mtup.search_low = tcp_mss_to_mtu(sk, mss);
	पूर्ण
	tcp_sync_mss(sk, icsk->icsk_pmtu_cookie);
पूर्ण

अटल अचिन्हित पूर्णांक tcp_model_समयout(काष्ठा sock *sk,
				      अचिन्हित पूर्णांक boundary,
				      अचिन्हित पूर्णांक rto_base)
अणु
	अचिन्हित पूर्णांक linear_backoff_thresh, समयout;

	linear_backoff_thresh = ilog2(TCP_RTO_MAX / rto_base);
	अगर (boundary <= linear_backoff_thresh)
		समयout = ((2 << boundary) - 1) * rto_base;
	अन्यथा
		समयout = ((2 << linear_backoff_thresh) - 1) * rto_base +
			(boundary - linear_backoff_thresh) * TCP_RTO_MAX;
	वापस jअगरfies_to_msecs(समयout);
पूर्ण
/**
 *  retransmits_समयd_out() - वापसs true अगर this connection has समयd out
 *  @sk:       The current socket
 *  @boundary: max number of retransmissions
 *  @समयout:  A custom समयout value.
 *             If set to 0 the शेष समयout is calculated and used.
 *             Using TCP_RTO_MIN and the number of unsuccessful retransmits.
 *
 * The शेष "timeout" value this function can calculate and use
 * is equivalent to the समयout of a TCP Connection
 * after "boundary" unsuccessful, exponentially backed-off
 * retransmissions with an initial RTO of TCP_RTO_MIN.
 */
अटल bool retransmits_समयd_out(काष्ठा sock *sk,
				  अचिन्हित पूर्णांक boundary,
				  अचिन्हित पूर्णांक समयout)
अणु
	अचिन्हित पूर्णांक start_ts;

	अगर (!inet_csk(sk)->icsk_retransmits)
		वापस false;

	start_ts = tcp_sk(sk)->retrans_stamp;
	अगर (likely(समयout == 0)) अणु
		अचिन्हित पूर्णांक rto_base = TCP_RTO_MIN;

		अगर ((1 << sk->sk_state) & (TCPF_SYN_SENT | TCPF_SYN_RECV))
			rto_base = tcp_समयout_init(sk);
		समयout = tcp_model_समयout(sk, boundary, rto_base);
	पूर्ण

	वापस (s32)(tcp_समय_stamp(tcp_sk(sk)) - start_ts - समयout) >= 0;
पूर्ण

/* A ग_लिखो समयout has occurred. Process the after effects. */
अटल पूर्णांक tcp_ग_लिखो_समयout(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा net *net = sock_net(sk);
	bool expired = false, करो_reset;
	पूर्णांक retry_until;

	अगर ((1 << sk->sk_state) & (TCPF_SYN_SENT | TCPF_SYN_RECV)) अणु
		अगर (icsk->icsk_retransmits)
			__dst_negative_advice(sk);
		retry_until = icsk->icsk_syn_retries ? : net->ipv4.sysctl_tcp_syn_retries;
		expired = icsk->icsk_retransmits >= retry_until;
	पूर्ण अन्यथा अणु
		अगर (retransmits_समयd_out(sk, net->ipv4.sysctl_tcp_retries1, 0)) अणु
			/* Black hole detection */
			tcp_mtu_probing(icsk, sk);

			__dst_negative_advice(sk);
		पूर्ण

		retry_until = net->ipv4.sysctl_tcp_retries2;
		अगर (sock_flag(sk, SOCK_DEAD)) अणु
			स्थिर bool alive = icsk->icsk_rto < TCP_RTO_MAX;

			retry_until = tcp_orphan_retries(sk, alive);
			करो_reset = alive ||
				!retransmits_समयd_out(sk, retry_until, 0);

			अगर (tcp_out_of_resources(sk, करो_reset))
				वापस 1;
		पूर्ण
	पूर्ण
	अगर (!expired)
		expired = retransmits_समयd_out(sk, retry_until,
						icsk->icsk_user_समयout);
	tcp_fastखोलो_active_detect_blackhole(sk, expired);

	अगर (BPF_SOCK_OPS_TEST_FLAG(tp, BPF_SOCK_OPS_RTO_CB_FLAG))
		tcp_call_bpf_3arg(sk, BPF_SOCK_OPS_RTO_CB,
				  icsk->icsk_retransmits,
				  icsk->icsk_rto, (पूर्णांक)expired);

	अगर (expired) अणु
		/* Has it gone just too far? */
		tcp_ग_लिखो_err(sk);
		वापस 1;
	पूर्ण

	अगर (sk_rethink_txhash(sk)) अणु
		tp->समयout_rehash++;
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPTIMEOUTREHASH);
	पूर्ण

	वापस 0;
पूर्ण

/* Called with BH disabled */
व्योम tcp_delack_समयr_handler(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	sk_mem_reclaim_partial(sk);

	अगर (((1 << sk->sk_state) & (TCPF_CLOSE | TCPF_LISTEN)) ||
	    !(icsk->icsk_ack.pending & ICSK_ACK_TIMER))
		जाओ out;

	अगर (समय_after(icsk->icsk_ack.समयout, jअगरfies)) अणु
		sk_reset_समयr(sk, &icsk->icsk_delack_समयr, icsk->icsk_ack.समयout);
		जाओ out;
	पूर्ण
	icsk->icsk_ack.pending &= ~ICSK_ACK_TIMER;

	अगर (inet_csk_ack_scheduled(sk)) अणु
		अगर (!inet_csk_in_pingpong_mode(sk)) अणु
			/* Delayed ACK missed: inflate ATO. */
			icsk->icsk_ack.ato = min(icsk->icsk_ack.ato << 1, icsk->icsk_rto);
		पूर्ण अन्यथा अणु
			/* Delayed ACK missed: leave pingpong mode and
			 * deflate ATO.
			 */
			inet_csk_निकास_pingpong_mode(sk);
			icsk->icsk_ack.ato      = TCP_ATO_MIN;
		पूर्ण
		tcp_mstamp_refresh(tcp_sk(sk));
		tcp_send_ack(sk);
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_DELAYEDACKS);
	पूर्ण

out:
	अगर (tcp_under_memory_pressure(sk))
		sk_mem_reclaim(sk);
पूर्ण


/**
 *  tcp_delack_समयr() - The TCP delayed ACK समयout handler
 *  @t:  Poपूर्णांकer to the समयr. (माला_लो casted to काष्ठा sock *)
 *
 *  This function माला_लो (indirectly) called when the kernel समयr क्रम a TCP packet
 *  of this socket expires. Calls tcp_delack_समयr_handler() to करो the actual work.
 *
 *  Returns: Nothing (व्योम)
 */
अटल व्योम tcp_delack_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा inet_connection_sock *icsk =
			from_समयr(icsk, t, icsk_delack_समयr);
	काष्ठा sock *sk = &icsk->icsk_inet.sk;

	bh_lock_sock(sk);
	अगर (!sock_owned_by_user(sk)) अणु
		tcp_delack_समयr_handler(sk);
	पूर्ण अन्यथा अणु
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_DELAYEDACKLOCKED);
		/* deleguate our work to tcp_release_cb() */
		अगर (!test_and_set_bit(TCP_DELACK_TIMER_DEFERRED, &sk->sk_tsq_flags))
			sock_hold(sk);
	पूर्ण
	bh_unlock_sock(sk);
	sock_put(sk);
पूर्ण

अटल व्योम tcp_probe_समयr(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा sk_buff *skb = tcp_send_head(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	पूर्णांक max_probes;

	अगर (tp->packets_out || !skb) अणु
		icsk->icsk_probes_out = 0;
		icsk->icsk_probes_tstamp = 0;
		वापस;
	पूर्ण

	/* RFC 1122 4.2.2.17 requires the sender to stay खोलो indefinitely as
	 * दीर्घ as the receiver जारीs to respond probes. We support this by
	 * शेष and reset icsk_probes_out with incoming ACKs. But अगर the
	 * socket is orphaned or the user specअगरies TCP_USER_TIMEOUT, we
	 * समाप्त the socket when the retry count and the समय exceeds the
	 * corresponding प्रणाली limit. We also implement similar policy when
	 * we use RTO to probe winकरोw in tcp_retransmit_समयr().
	 */
	अगर (!icsk->icsk_probes_tstamp)
		icsk->icsk_probes_tstamp = tcp_jअगरfies32;
	अन्यथा अगर (icsk->icsk_user_समयout &&
		 (s32)(tcp_jअगरfies32 - icsk->icsk_probes_tstamp) >=
		 msecs_to_jअगरfies(icsk->icsk_user_समयout))
		जाओ पात;

	max_probes = sock_net(sk)->ipv4.sysctl_tcp_retries2;
	अगर (sock_flag(sk, SOCK_DEAD)) अणु
		स्थिर bool alive = inet_csk_rto_backoff(icsk, TCP_RTO_MAX) < TCP_RTO_MAX;

		max_probes = tcp_orphan_retries(sk, alive);
		अगर (!alive && icsk->icsk_backoff >= max_probes)
			जाओ पात;
		अगर (tcp_out_of_resources(sk, true))
			वापस;
	पूर्ण

	अगर (icsk->icsk_probes_out >= max_probes) अणु
पात:		tcp_ग_लिखो_err(sk);
	पूर्ण अन्यथा अणु
		/* Only send another probe अगर we didn't बंद things up. */
		tcp_send_probe0(sk);
	पूर्ण
पूर्ण

/*
 *	Timer क्रम Fast Open socket to retransmit SYNACK. Note that the
 *	sk here is the child socket, not the parent (listener) socket.
 */
अटल व्योम tcp_fastखोलो_synack_समयr(काष्ठा sock *sk, काष्ठा request_sock *req)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	पूर्णांक max_retries = icsk->icsk_syn_retries ? :
	    sock_net(sk)->ipv4.sysctl_tcp_synack_retries + 1; /* add one more retry क्रम fastखोलो */
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	req->rsk_ops->syn_ack_समयout(req);

	अगर (req->num_समयout >= max_retries) अणु
		tcp_ग_लिखो_err(sk);
		वापस;
	पूर्ण
	/* Lower cwnd after certain SYNACK समयout like tcp_init_transfer() */
	अगर (icsk->icsk_retransmits == 1)
		tcp_enter_loss(sk);
	/* XXX (TFO) - Unlike regular SYN-ACK retransmit, we ignore error
	 * वापसed from rtx_syn_ack() to make it more persistent like
	 * regular retransmit because अगर the child socket has been accepted
	 * it's not good to give up too easily.
	 */
	inet_rtx_syn_ack(sk, req);
	req->num_समयout++;
	icsk->icsk_retransmits++;
	अगर (!tp->retrans_stamp)
		tp->retrans_stamp = tcp_समय_stamp(tp);
	inet_csk_reset_xmit_समयr(sk, ICSK_TIME_RETRANS,
			  TCP_TIMEOUT_INIT << req->num_समयout, TCP_RTO_MAX);
पूर्ण


/**
 *  tcp_retransmit_समयr() - The TCP retransmit समयout handler
 *  @sk:  Poपूर्णांकer to the current socket.
 *
 *  This function माला_लो called when the kernel समयr क्रम a TCP packet
 *  of this socket expires.
 *
 *  It handles retransmission, समयr adjusपंचांगent and other necesarry measures.
 *
 *  Returns: Nothing (व्योम)
 */
व्योम tcp_retransmit_समयr(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा net *net = sock_net(sk);
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा request_sock *req;
	काष्ठा sk_buff *skb;

	req = rcu_dereference_रक्षित(tp->fastखोलो_rsk,
					lockdep_sock_is_held(sk));
	अगर (req) अणु
		WARN_ON_ONCE(sk->sk_state != TCP_SYN_RECV &&
			     sk->sk_state != TCP_FIN_WAIT1);
		tcp_fastखोलो_synack_समयr(sk, req);
		/* Beक्रमe we receive ACK to our SYN-ACK करोn't retransmit
		 * anything अन्यथा (e.g., data or FIN segments).
		 */
		वापस;
	पूर्ण

	अगर (!tp->packets_out)
		वापस;

	skb = tcp_rtx_queue_head(sk);
	अगर (WARN_ON_ONCE(!skb))
		वापस;

	tp->tlp_high_seq = 0;

	अगर (!tp->snd_wnd && !sock_flag(sk, SOCK_DEAD) &&
	    !((1 << sk->sk_state) & (TCPF_SYN_SENT | TCPF_SYN_RECV))) अणु
		/* Receiver dastardly shrinks winकरोw. Our retransmits
		 * become zero probes, but we should not समयout this
		 * connection. If the socket is an orphan, समय it out,
		 * we cannot allow such beasts to hang infinitely.
		 */
		काष्ठा inet_sock *inet = inet_sk(sk);
		अगर (sk->sk_family == AF_INET) अणु
			net_dbg_ratelimited("Peer %pI4:%u/%u unexpectedly shrunk window %u:%u (repaired)\n",
					    &inet->inet_daddr,
					    ntohs(inet->inet_dport),
					    inet->inet_num,
					    tp->snd_una, tp->snd_nxt);
		पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
		अन्यथा अगर (sk->sk_family == AF_INET6) अणु
			net_dbg_ratelimited("Peer %pI6:%u/%u unexpectedly shrunk window %u:%u (repaired)\n",
					    &sk->sk_v6_daddr,
					    ntohs(inet->inet_dport),
					    inet->inet_num,
					    tp->snd_una, tp->snd_nxt);
		पूर्ण
#पूर्ण_अगर
		अगर (tcp_jअगरfies32 - tp->rcv_tstamp > TCP_RTO_MAX) अणु
			tcp_ग_लिखो_err(sk);
			जाओ out;
		पूर्ण
		tcp_enter_loss(sk);
		tcp_retransmit_skb(sk, skb, 1);
		__sk_dst_reset(sk);
		जाओ out_reset_समयr;
	पूर्ण

	__NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPTIMEOUTS);
	अगर (tcp_ग_लिखो_समयout(sk))
		जाओ out;

	अगर (icsk->icsk_retransmits == 0) अणु
		पूर्णांक mib_idx = 0;

		अगर (icsk->icsk_ca_state == TCP_CA_Recovery) अणु
			अगर (tcp_is_sack(tp))
				mib_idx = LINUX_MIB_TCPSACKRECOVERYFAIL;
			अन्यथा
				mib_idx = LINUX_MIB_TCPRENORECOVERYFAIL;
		पूर्ण अन्यथा अगर (icsk->icsk_ca_state == TCP_CA_Loss) अणु
			mib_idx = LINUX_MIB_TCPLOSSFAILURES;
		पूर्ण अन्यथा अगर ((icsk->icsk_ca_state == TCP_CA_Disorder) ||
			   tp->sacked_out) अणु
			अगर (tcp_is_sack(tp))
				mib_idx = LINUX_MIB_TCPSACKFAILURES;
			अन्यथा
				mib_idx = LINUX_MIB_TCPRENOFAILURES;
		पूर्ण
		अगर (mib_idx)
			__NET_INC_STATS(sock_net(sk), mib_idx);
	पूर्ण

	tcp_enter_loss(sk);

	icsk->icsk_retransmits++;
	अगर (tcp_retransmit_skb(sk, tcp_rtx_queue_head(sk), 1) > 0) अणु
		/* Retransmission failed because of local congestion,
		 * Let senders fight क्रम local resources conservatively.
		 */
		inet_csk_reset_xmit_समयr(sk, ICSK_TIME_RETRANS,
					  TCP_RESOURCE_PROBE_INTERVAL,
					  TCP_RTO_MAX);
		जाओ out;
	पूर्ण

	/* Increase the समयout each समय we retransmit.  Note that
	 * we करो not increase the rtt estimate.  rto is initialized
	 * from rtt, but increases here.  Jacobson (SIGCOMM 88) suggests
	 * that करोubling rto each समय is the least we can get away with.
	 * In KA9Q, Karn uses this क्रम the first few बार, and then
	 * goes to quadratic.  netBSD द्विगुनs, but only goes up to *64,
	 * and clamps at 1 to 64 sec afterwards.  Note that 120 sec is
	 * defined in the protocol as the maximum possible RTT.  I guess
	 * we'll have to use something other than TCP to talk to the
	 * University of Mars.
	 *
	 * PAWS allows us दीर्घer समयouts and large winकरोws, so once
	 * implemented ftp to mars will work nicely. We will have to fix
	 * the 120 second clamps though!
	 */
	icsk->icsk_backoff++;

out_reset_समयr:
	/* If stream is thin, use linear समयouts. Since 'icsk_backoff' is
	 * used to reset समयr, set to 0. Recalculate 'icsk_rto' as this
	 * might be increased अगर the stream oscillates between thin and thick,
	 * thus the old value might alपढ़ोy be too high compared to the value
	 * set by 'tcp_set_rto' in tcp_input.c which resets the rto without
	 * backoff. Limit to TCP_THIN_LINEAR_RETRIES beक्रमe initiating
	 * exponential backoff behaviour to aव्योम जारी hammering
	 * linear-समयout retransmissions पूर्णांकo a black hole
	 */
	अगर (sk->sk_state == TCP_ESTABLISHED &&
	    (tp->thin_lto || net->ipv4.sysctl_tcp_thin_linear_समयouts) &&
	    tcp_stream_is_thin(tp) &&
	    icsk->icsk_retransmits <= TCP_THIN_LINEAR_RETRIES) अणु
		icsk->icsk_backoff = 0;
		icsk->icsk_rto = min(__tcp_set_rto(tp), TCP_RTO_MAX);
	पूर्ण अन्यथा अणु
		/* Use normal (exponential) backoff */
		icsk->icsk_rto = min(icsk->icsk_rto << 1, TCP_RTO_MAX);
	पूर्ण
	inet_csk_reset_xmit_समयr(sk, ICSK_TIME_RETRANS,
				  tcp_clamp_rto_to_user_समयout(sk), TCP_RTO_MAX);
	अगर (retransmits_समयd_out(sk, net->ipv4.sysctl_tcp_retries1 + 1, 0))
		__sk_dst_reset(sk);

out:;
पूर्ण

/* Called with bottom-half processing disabled.
   Called by tcp_ग_लिखो_समयr() */
व्योम tcp_ग_लिखो_समयr_handler(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	पूर्णांक event;

	अगर (((1 << sk->sk_state) & (TCPF_CLOSE | TCPF_LISTEN)) ||
	    !icsk->icsk_pending)
		जाओ out;

	अगर (समय_after(icsk->icsk_समयout, jअगरfies)) अणु
		sk_reset_समयr(sk, &icsk->icsk_retransmit_समयr, icsk->icsk_समयout);
		जाओ out;
	पूर्ण

	tcp_mstamp_refresh(tcp_sk(sk));
	event = icsk->icsk_pending;

	चयन (event) अणु
	हाल ICSK_TIME_REO_TIMEOUT:
		tcp_rack_reo_समयout(sk);
		अवरोध;
	हाल ICSK_TIME_LOSS_PROBE:
		tcp_send_loss_probe(sk);
		अवरोध;
	हाल ICSK_TIME_RETRANS:
		icsk->icsk_pending = 0;
		tcp_retransmit_समयr(sk);
		अवरोध;
	हाल ICSK_TIME_PROBE0:
		icsk->icsk_pending = 0;
		tcp_probe_समयr(sk);
		अवरोध;
	पूर्ण

out:
	sk_mem_reclaim(sk);
पूर्ण

अटल व्योम tcp_ग_लिखो_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा inet_connection_sock *icsk =
			from_समयr(icsk, t, icsk_retransmit_समयr);
	काष्ठा sock *sk = &icsk->icsk_inet.sk;

	bh_lock_sock(sk);
	अगर (!sock_owned_by_user(sk)) अणु
		tcp_ग_लिखो_समयr_handler(sk);
	पूर्ण अन्यथा अणु
		/* delegate our work to tcp_release_cb() */
		अगर (!test_and_set_bit(TCP_WRITE_TIMER_DEFERRED, &sk->sk_tsq_flags))
			sock_hold(sk);
	पूर्ण
	bh_unlock_sock(sk);
	sock_put(sk);
पूर्ण

व्योम tcp_syn_ack_समयout(स्थिर काष्ठा request_sock *req)
अणु
	काष्ठा net *net = पढ़ो_pnet(&inet_rsk(req)->ireq_net);

	__NET_INC_STATS(net, LINUX_MIB_TCPTIMEOUTS);
पूर्ण
EXPORT_SYMBOL(tcp_syn_ack_समयout);

व्योम tcp_set_keepalive(काष्ठा sock *sk, पूर्णांक val)
अणु
	अगर ((1 << sk->sk_state) & (TCPF_CLOSE | TCPF_LISTEN))
		वापस;

	अगर (val && !sock_flag(sk, SOCK_KEEPOPEN))
		inet_csk_reset_keepalive_समयr(sk, keepalive_समय_when(tcp_sk(sk)));
	अन्यथा अगर (!val)
		inet_csk_delete_keepalive_समयr(sk);
पूर्ण
EXPORT_SYMBOL_GPL(tcp_set_keepalive);


अटल व्योम tcp_keepalive_समयr (काष्ठा समयr_list *t)
अणु
	काष्ठा sock *sk = from_समयr(sk, t, sk_समयr);
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 elapsed;

	/* Only process अगर socket is not in use. */
	bh_lock_sock(sk);
	अगर (sock_owned_by_user(sk)) अणु
		/* Try again later. */
		inet_csk_reset_keepalive_समयr (sk, HZ/20);
		जाओ out;
	पूर्ण

	अगर (sk->sk_state == TCP_LISTEN) अणु
		pr_err("Hmm... keepalive on a LISTEN ???\n");
		जाओ out;
	पूर्ण

	tcp_mstamp_refresh(tp);
	अगर (sk->sk_state == TCP_FIN_WAIT2 && sock_flag(sk, SOCK_DEAD)) अणु
		अगर (tp->linger2 >= 0) अणु
			स्थिर पूर्णांक पंचांगo = tcp_fin_समय(sk) - TCP_TIMEWAIT_LEN;

			अगर (पंचांगo > 0) अणु
				tcp_समय_रुको(sk, TCP_FIN_WAIT2, पंचांगo);
				जाओ out;
			पूर्ण
		पूर्ण
		tcp_send_active_reset(sk, GFP_ATOMIC);
		जाओ death;
	पूर्ण

	अगर (!sock_flag(sk, SOCK_KEEPOPEN) ||
	    ((1 << sk->sk_state) & (TCPF_CLOSE | TCPF_SYN_SENT)))
		जाओ out;

	elapsed = keepalive_समय_when(tp);

	/* It is alive without keepalive 8) */
	अगर (tp->packets_out || !tcp_ग_लिखो_queue_empty(sk))
		जाओ resched;

	elapsed = keepalive_समय_elapsed(tp);

	अगर (elapsed >= keepalive_समय_when(tp)) अणु
		/* If the TCP_USER_TIMEOUT option is enabled, use that
		 * to determine when to समयout instead.
		 */
		अगर ((icsk->icsk_user_समयout != 0 &&
		    elapsed >= msecs_to_jअगरfies(icsk->icsk_user_समयout) &&
		    icsk->icsk_probes_out > 0) ||
		    (icsk->icsk_user_समयout == 0 &&
		    icsk->icsk_probes_out >= keepalive_probes(tp))) अणु
			tcp_send_active_reset(sk, GFP_ATOMIC);
			tcp_ग_लिखो_err(sk);
			जाओ out;
		पूर्ण
		अगर (tcp_ग_लिखो_wakeup(sk, LINUX_MIB_TCPKEEPALIVE) <= 0) अणु
			icsk->icsk_probes_out++;
			elapsed = keepalive_पूर्णांकvl_when(tp);
		पूर्ण अन्यथा अणु
			/* If keepalive was lost due to local congestion,
			 * try harder.
			 */
			elapsed = TCP_RESOURCE_PROBE_INTERVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* It is tp->rcv_tstamp + keepalive_समय_when(tp) */
		elapsed = keepalive_समय_when(tp) - elapsed;
	पूर्ण

	sk_mem_reclaim(sk);

resched:
	inet_csk_reset_keepalive_समयr (sk, elapsed);
	जाओ out;

death:
	tcp_करोne(sk);

out:
	bh_unlock_sock(sk);
	sock_put(sk);
पूर्ण

अटल क्रमागत hrसमयr_restart tcp_compressed_ack_kick(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा tcp_sock *tp = container_of(समयr, काष्ठा tcp_sock, compressed_ack_समयr);
	काष्ठा sock *sk = (काष्ठा sock *)tp;

	bh_lock_sock(sk);
	अगर (!sock_owned_by_user(sk)) अणु
		अगर (tp->compressed_ack) अणु
			/* Since we have to send one ack finally,
			 * substract one from tp->compressed_ack to keep
			 * LINUX_MIB_TCPACKCOMPRESSED accurate.
			 */
			tp->compressed_ack--;
			tcp_send_ack(sk);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!test_and_set_bit(TCP_DELACK_TIMER_DEFERRED,
				      &sk->sk_tsq_flags))
			sock_hold(sk);
	पूर्ण
	bh_unlock_sock(sk);

	sock_put(sk);

	वापस HRTIMER_NORESTART;
पूर्ण

व्योम tcp_init_xmit_समयrs(काष्ठा sock *sk)
अणु
	inet_csk_init_xmit_समयrs(sk, &tcp_ग_लिखो_समयr, &tcp_delack_समयr,
				  &tcp_keepalive_समयr);
	hrसमयr_init(&tcp_sk(sk)->pacing_समयr, CLOCK_MONOTONIC,
		     HRTIMER_MODE_ABS_PINNED_SOFT);
	tcp_sk(sk)->pacing_समयr.function = tcp_pace_kick;

	hrसमयr_init(&tcp_sk(sk)->compressed_ack_समयr, CLOCK_MONOTONIC,
		     HRTIMER_MODE_REL_PINNED_SOFT);
	tcp_sk(sk)->compressed_ack_समयr.function = tcp_compressed_ack_kick;
पूर्ण
