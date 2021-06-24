<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  net/dccp/समयr.c
 *
 *  An implementation of the DCCP protocol
 *  Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 */

#समावेश <linux/dccp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/export.h>

#समावेश "dccp.h"

/* sysctl variables governing numbers of retransmission attempts */
पूर्णांक  sysctl_dccp_request_retries	__पढ़ो_mostly = TCP_SYN_RETRIES;
पूर्णांक  sysctl_dccp_retries1		__पढ़ो_mostly = TCP_RETR1;
पूर्णांक  sysctl_dccp_retries2		__पढ़ो_mostly = TCP_RETR2;

अटल व्योम dccp_ग_लिखो_err(काष्ठा sock *sk)
अणु
	sk->sk_err = sk->sk_err_soft ? : ETIMEDOUT;
	sk->sk_error_report(sk);

	dccp_send_reset(sk, DCCP_RESET_CODE_ABORTED);
	dccp_करोne(sk);
	__DCCP_INC_STATS(DCCP_MIB_ABORTONTIMEOUT);
पूर्ण

/* A ग_लिखो समयout has occurred. Process the after effects. */
अटल पूर्णांक dccp_ग_लिखो_समयout(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	पूर्णांक retry_until;

	अगर (sk->sk_state == DCCP_REQUESTING || sk->sk_state == DCCP_PARTOPEN) अणु
		अगर (icsk->icsk_retransmits != 0)
			dst_negative_advice(sk);
		retry_until = icsk->icsk_syn_retries ?
			    : sysctl_dccp_request_retries;
	पूर्ण अन्यथा अणु
		अगर (icsk->icsk_retransmits >= sysctl_dccp_retries1) अणु
			/* NOTE. draft-ietf-tcpimpl-pmtud-01.txt requires pmtu
			   black hole detection. :-(

			   It is place to make it. It is not made. I करो not want
			   to make it. It is disguisting. It करोes not work in any
			   हाल. Let me to cite the same draft, which requires क्रम
			   us to implement this:

   "The one security concern उठाओd by this memo is that ICMP black holes
   are often caused by over-zealous security administrators who block
   all ICMP messages.  It is vitally important that those who design and
   deploy security प्रणालीs understand the impact of strict filtering on
   upper-layer protocols.  The safest web site in the world is worthless
   अगर most TCP implementations cannot transfer data from it.  It would
   be far nicer to have all of the black holes fixed rather than fixing
   all of the TCP implementations."

			   Golden words :-).
		   */

			dst_negative_advice(sk);
		पूर्ण

		retry_until = sysctl_dccp_retries2;
		/*
		 * FIXME: see tcp_ग_लिखो_timout and tcp_out_of_resources
		 */
	पूर्ण

	अगर (icsk->icsk_retransmits >= retry_until) अणु
		/* Has it gone just too far? */
		dccp_ग_लिखो_err(sk);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 *	The DCCP retransmit समयr.
 */
अटल व्योम dccp_retransmit_समयr(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	/*
	 * More than 4MSL (8 minutes) has passed, a RESET(पातed) was
	 * sent, no need to retransmit, this sock is dead.
	 */
	अगर (dccp_ग_लिखो_समयout(sk))
		वापस;

	/*
	 * We want to know the number of packets retransmitted, not the
	 * total number of retransmissions of clones of original packets.
	 */
	अगर (icsk->icsk_retransmits == 0)
		__DCCP_INC_STATS(DCCP_MIB_TIMEOUTS);

	अगर (dccp_retransmit_skb(sk) != 0) अणु
		/*
		 * Retransmission failed because of local congestion,
		 * करो not backoff.
		 */
		अगर (--icsk->icsk_retransmits == 0)
			icsk->icsk_retransmits = 1;
		inet_csk_reset_xmit_समयr(sk, ICSK_TIME_RETRANS,
					  min(icsk->icsk_rto,
					      TCP_RESOURCE_PROBE_INTERVAL),
					  DCCP_RTO_MAX);
		वापस;
	पूर्ण

	icsk->icsk_backoff++;

	icsk->icsk_rto = min(icsk->icsk_rto << 1, DCCP_RTO_MAX);
	inet_csk_reset_xmit_समयr(sk, ICSK_TIME_RETRANS, icsk->icsk_rto,
				  DCCP_RTO_MAX);
	अगर (icsk->icsk_retransmits > sysctl_dccp_retries1)
		__sk_dst_reset(sk);
पूर्ण

अटल व्योम dccp_ग_लिखो_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा inet_connection_sock *icsk =
			from_समयr(icsk, t, icsk_retransmit_समयr);
	काष्ठा sock *sk = &icsk->icsk_inet.sk;
	पूर्णांक event = 0;

	bh_lock_sock(sk);
	अगर (sock_owned_by_user(sk)) अणु
		/* Try again later */
		sk_reset_समयr(sk, &icsk->icsk_retransmit_समयr,
			       jअगरfies + (HZ / 20));
		जाओ out;
	पूर्ण

	अगर (sk->sk_state == DCCP_CLOSED || !icsk->icsk_pending)
		जाओ out;

	अगर (समय_after(icsk->icsk_समयout, jअगरfies)) अणु
		sk_reset_समयr(sk, &icsk->icsk_retransmit_समयr,
			       icsk->icsk_समयout);
		जाओ out;
	पूर्ण

	event = icsk->icsk_pending;
	icsk->icsk_pending = 0;

	चयन (event) अणु
	हाल ICSK_TIME_RETRANS:
		dccp_retransmit_समयr(sk);
		अवरोध;
	पूर्ण
out:
	bh_unlock_sock(sk);
	sock_put(sk);
पूर्ण

अटल व्योम dccp_keepalive_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sock *sk = from_समयr(sk, t, sk_समयr);

	pr_err("dccp should not use a keepalive timer !\n");
	sock_put(sk);
पूर्ण

/* This is the same as tcp_delack_समयr, sans prequeue & mem_reclaim stuff */
अटल व्योम dccp_delack_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा inet_connection_sock *icsk =
			from_समयr(icsk, t, icsk_delack_समयr);
	काष्ठा sock *sk = &icsk->icsk_inet.sk;

	bh_lock_sock(sk);
	अगर (sock_owned_by_user(sk)) अणु
		/* Try again later. */
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_DELAYEDACKLOCKED);
		sk_reset_समयr(sk, &icsk->icsk_delack_समयr,
			       jअगरfies + TCP_DELACK_MIN);
		जाओ out;
	पूर्ण

	अगर (sk->sk_state == DCCP_CLOSED ||
	    !(icsk->icsk_ack.pending & ICSK_ACK_TIMER))
		जाओ out;
	अगर (समय_after(icsk->icsk_ack.समयout, jअगरfies)) अणु
		sk_reset_समयr(sk, &icsk->icsk_delack_समयr,
			       icsk->icsk_ack.समयout);
		जाओ out;
	पूर्ण

	icsk->icsk_ack.pending &= ~ICSK_ACK_TIMER;

	अगर (inet_csk_ack_scheduled(sk)) अणु
		अगर (!inet_csk_in_pingpong_mode(sk)) अणु
			/* Delayed ACK missed: inflate ATO. */
			icsk->icsk_ack.ato = min(icsk->icsk_ack.ato << 1,
						 icsk->icsk_rto);
		पूर्ण अन्यथा अणु
			/* Delayed ACK missed: leave pingpong mode and
			 * deflate ATO.
			 */
			inet_csk_निकास_pingpong_mode(sk);
			icsk->icsk_ack.ato = TCP_ATO_MIN;
		पूर्ण
		dccp_send_ack(sk);
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_DELAYEDACKS);
	पूर्ण
out:
	bh_unlock_sock(sk);
	sock_put(sk);
पूर्ण

/**
 * dccp_ग_लिखो_xmitlet  -  Workhorse क्रम CCID packet dequeueing पूर्णांकerface
 * @t: poपूर्णांकer to the tasklet associated with this handler
 *
 * See the comments above %ccid_dequeueing_decision क्रम supported modes.
 */
अटल व्योम dccp_ग_लिखो_xmitlet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा dccp_sock *dp = from_tasklet(dp, t, dccps_xmitlet);
	काष्ठा sock *sk = &dp->dccps_inet_connection.icsk_inet.sk;

	bh_lock_sock(sk);
	अगर (sock_owned_by_user(sk))
		sk_reset_समयr(sk, &dccp_sk(sk)->dccps_xmit_समयr, jअगरfies + 1);
	अन्यथा
		dccp_ग_लिखो_xmit(sk);
	bh_unlock_sock(sk);
	sock_put(sk);
पूर्ण

अटल व्योम dccp_ग_लिखो_xmit_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा dccp_sock *dp = from_समयr(dp, t, dccps_xmit_समयr);

	dccp_ग_लिखो_xmitlet(&dp->dccps_xmitlet);
पूर्ण

व्योम dccp_init_xmit_समयrs(काष्ठा sock *sk)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);

	tasklet_setup(&dp->dccps_xmitlet, dccp_ग_लिखो_xmitlet);
	समयr_setup(&dp->dccps_xmit_समयr, dccp_ग_लिखो_xmit_समयr, 0);
	inet_csk_init_xmit_समयrs(sk, &dccp_ग_लिखो_समयr, &dccp_delack_समयr,
				  &dccp_keepalive_समयr);
पूर्ण

अटल kसमय_प्रकार dccp_बारtamp_seed;
/**
 * dccp_बारtamp  -  10s of microseconds समय source
 * Returns the number of 10s of microseconds since loading DCCP. This is native
 * DCCP समय dअगरference क्रमmat (RFC 4340, sec. 13).
 * Please note: This will wrap around about circa every 11.9 hours.
 */
u32 dccp_बारtamp(व्योम)
अणु
	u64 delta = (u64)kसमय_us_delta(kसमय_get_real(), dccp_बारtamp_seed);

	करो_भाग(delta, 10);
	वापस delta;
पूर्ण
EXPORT_SYMBOL_GPL(dccp_बारtamp);

व्योम __init dccp_बारtamping_init(व्योम)
अणु
	dccp_बारtamp_seed = kसमय_get_real();
पूर्ण
