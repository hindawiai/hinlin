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

#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/अटल_key.h>
#समावेश <net/tcp.h>
#समावेश <net/inet_common.h>
#समावेश <net/xfrm.h>
#समावेश <net/busy_poll.h>

अटल bool tcp_in_winकरोw(u32 seq, u32 end_seq, u32 s_win, u32 e_win)
अणु
	अगर (seq == s_win)
		वापस true;
	अगर (after(end_seq, s_win) && beक्रमe(seq, e_win))
		वापस true;
	वापस seq == e_win && seq == end_seq;
पूर्ण

अटल क्रमागत tcp_tw_status
tcp_समयरुको_check_oow_rate_limit(काष्ठा inet_समयरुको_sock *tw,
				  स्थिर काष्ठा sk_buff *skb, पूर्णांक mib_idx)
अणु
	काष्ठा tcp_समयरुको_sock *tcptw = tcp_twsk((काष्ठा sock *)tw);

	अगर (!tcp_oow_rate_limited(twsk_net(tw), skb, mib_idx,
				  &tcptw->tw_last_oow_ack_समय)) अणु
		/* Send ACK. Note, we करो not put the bucket,
		 * it will be released by caller.
		 */
		वापस TCP_TW_ACK;
	पूर्ण

	/* We are rate-limiting, so just release the tw sock and drop skb. */
	inet_twsk_put(tw);
	वापस TCP_TW_SUCCESS;
पूर्ण

/*
 * * Main purpose of TIME-WAIT state is to बंद connection gracefully,
 *   when one of ends sits in LAST-ACK or CLOSING retransmitting FIN
 *   (and, probably, tail of data) and one or more our ACKs are lost.
 * * What is TIME-WAIT समयout? It is associated with maximal packet
 *   lअगरeसमय in the पूर्णांकernet, which results in wrong conclusion, that
 *   it is set to catch "old duplicate segments" wandering out of their path.
 *   It is not quite correct. This समयout is calculated so that it exceeds
 *   maximal retransmission समयout enough to allow to lose one (or more)
 *   segments sent by peer and our ACKs. This समय may be calculated from RTO.
 * * When TIME-WAIT socket receives RST, it means that another end
 *   finally बंदd and we are allowed to समाप्त TIME-WAIT too.
 * * Second purpose of TIME-WAIT is catching old duplicate segments.
 *   Well, certainly it is pure paranoia, but अगर we load TIME-WAIT
 *   with this semantics, we MUST NOT समाप्त TIME-WAIT state with RSTs.
 * * If we invented some more clever way to catch duplicates
 *   (f.e. based on PAWS), we could truncate TIME-WAIT to several RTOs.
 *
 * The algorithm below is based on FORMAL INTERPRETATION of RFCs.
 * When you compare it to RFCs, please, पढ़ो section SEGMENT ARRIVES
 * from the very beginning.
 *
 * NOTE. With recycling (and later with fin-रुको-2) TW bucket
 * is _not_ stateless. It means, that strictly speaking we must
 * spinlock it. I करो not want! Well, probability of misbehaviour
 * is ridiculously low and, seems, we could use some mb() tricks
 * to aव्योम misपढ़ो sequence numbers, states etc.  --ANK
 *
 * We करोn't need to initialize tmp_out.sack_ok as we don't use the results
 */
क्रमागत tcp_tw_status
tcp_समयरुको_state_process(काष्ठा inet_समयरुको_sock *tw, काष्ठा sk_buff *skb,
			   स्थिर काष्ठा tcphdr *th)
अणु
	काष्ठा tcp_options_received पंचांगp_opt;
	काष्ठा tcp_समयरुको_sock *tcptw = tcp_twsk((काष्ठा sock *)tw);
	bool paws_reject = false;

	पंचांगp_opt.saw_tstamp = 0;
	अगर (th->करोff > (माप(*th) >> 2) && tcptw->tw_ts_recent_stamp) अणु
		tcp_parse_options(twsk_net(tw), skb, &पंचांगp_opt, 0, शून्य);

		अगर (पंचांगp_opt.saw_tstamp) अणु
			अगर (पंचांगp_opt.rcv_tsecr)
				पंचांगp_opt.rcv_tsecr -= tcptw->tw_ts_offset;
			पंचांगp_opt.ts_recent	= tcptw->tw_ts_recent;
			पंचांगp_opt.ts_recent_stamp	= tcptw->tw_ts_recent_stamp;
			paws_reject = tcp_paws_reject(&पंचांगp_opt, th->rst);
		पूर्ण
	पूर्ण

	अगर (tw->tw_substate == TCP_FIN_WAIT2) अणु
		/* Just repeat all the checks of tcp_rcv_state_process() */

		/* Out of winकरोw, send ACK */
		अगर (paws_reject ||
		    !tcp_in_winकरोw(TCP_SKB_CB(skb)->seq, TCP_SKB_CB(skb)->end_seq,
				   tcptw->tw_rcv_nxt,
				   tcptw->tw_rcv_nxt + tcptw->tw_rcv_wnd))
			वापस tcp_समयरुको_check_oow_rate_limit(
				tw, skb, LINUX_MIB_TCPACKSKIPPEDFINWAIT2);

		अगर (th->rst)
			जाओ समाप्त;

		अगर (th->syn && !beक्रमe(TCP_SKB_CB(skb)->seq, tcptw->tw_rcv_nxt))
			वापस TCP_TW_RST;

		/* Dup ACK? */
		अगर (!th->ack ||
		    !after(TCP_SKB_CB(skb)->end_seq, tcptw->tw_rcv_nxt) ||
		    TCP_SKB_CB(skb)->end_seq == TCP_SKB_CB(skb)->seq) अणु
			inet_twsk_put(tw);
			वापस TCP_TW_SUCCESS;
		पूर्ण

		/* New data or FIN. If new data arrive after half-duplex बंद,
		 * reset.
		 */
		अगर (!th->fin ||
		    TCP_SKB_CB(skb)->end_seq != tcptw->tw_rcv_nxt + 1)
			वापस TCP_TW_RST;

		/* FIN arrived, enter true समय-रुको state. */
		tw->tw_substate	  = TCP_TIME_WAIT;
		tcptw->tw_rcv_nxt = TCP_SKB_CB(skb)->end_seq;
		अगर (पंचांगp_opt.saw_tstamp) अणु
			tcptw->tw_ts_recent_stamp = kसमय_get_seconds();
			tcptw->tw_ts_recent	  = पंचांगp_opt.rcv_tsval;
		पूर्ण

		inet_twsk_reschedule(tw, TCP_TIMEWAIT_LEN);
		वापस TCP_TW_ACK;
	पूर्ण

	/*
	 *	Now real TIME-WAIT state.
	 *
	 *	RFC 1122:
	 *	"When a connection is [...] on TIME-WAIT state [...]
	 *	[a TCP] MAY accept a new SYN from the remote TCP to
	 *	reखोलो the connection directly, अगर it:
	 *
	 *	(1)  assigns its initial sequence number क्रम the new
	 *	connection to be larger than the largest sequence
	 *	number it used on the previous connection incarnation,
	 *	and
	 *
	 *	(2)  वापसs to TIME-WAIT state अगर the SYN turns out
	 *	to be an old duplicate".
	 */

	अगर (!paws_reject &&
	    (TCP_SKB_CB(skb)->seq == tcptw->tw_rcv_nxt &&
	     (TCP_SKB_CB(skb)->seq == TCP_SKB_CB(skb)->end_seq || th->rst))) अणु
		/* In winकरोw segment, it may be only reset or bare ack. */

		अगर (th->rst) अणु
			/* This is TIME_WAIT assassination, in two flavors.
			 * Oh well... nobody has a sufficient solution to this
			 * protocol bug yet.
			 */
			अगर (twsk_net(tw)->ipv4.sysctl_tcp_rfc1337 == 0) अणु
समाप्त:
				inet_twsk_deschedule_put(tw);
				वापस TCP_TW_SUCCESS;
			पूर्ण
		पूर्ण अन्यथा अणु
			inet_twsk_reschedule(tw, TCP_TIMEWAIT_LEN);
		पूर्ण

		अगर (पंचांगp_opt.saw_tstamp) अणु
			tcptw->tw_ts_recent	  = पंचांगp_opt.rcv_tsval;
			tcptw->tw_ts_recent_stamp = kसमय_get_seconds();
		पूर्ण

		inet_twsk_put(tw);
		वापस TCP_TW_SUCCESS;
	पूर्ण

	/* Out of winकरोw segment.

	   All the segments are ACKed immediately.

	   The only exception is new SYN. We accept it, अगर it is
	   not old duplicate and we are not in danger to be समाप्तed
	   by delayed old duplicates. RFC check is that it has
	   newer sequence number works at rates <40Mbit/sec.
	   However, अगर paws works, it is reliable AND even more,
	   we even may relax silly seq space cutoff.

	   RED-PEN: we violate मुख्य RFC requirement, अगर this SYN will appear
	   old duplicate (i.e. we receive RST in reply to SYN-ACK),
	   we must वापस socket to समय-रुको state. It is not good,
	   but not fatal yet.
	 */

	अगर (th->syn && !th->rst && !th->ack && !paws_reject &&
	    (after(TCP_SKB_CB(skb)->seq, tcptw->tw_rcv_nxt) ||
	     (पंचांगp_opt.saw_tstamp &&
	      (s32)(tcptw->tw_ts_recent - पंचांगp_opt.rcv_tsval) < 0))) अणु
		u32 isn = tcptw->tw_snd_nxt + 65535 + 2;
		अगर (isn == 0)
			isn++;
		TCP_SKB_CB(skb)->tcp_tw_isn = isn;
		वापस TCP_TW_SYN;
	पूर्ण

	अगर (paws_reject)
		__NET_INC_STATS(twsk_net(tw), LINUX_MIB_PAWSESTABREJECTED);

	अगर (!th->rst) अणु
		/* In this हाल we must reset the TIMEWAIT समयr.
		 *
		 * If it is ACKless SYN it may be both old duplicate
		 * and new good SYN with अक्रमom sequence number <rcv_nxt.
		 * Do not reschedule in the last हाल.
		 */
		अगर (paws_reject || th->ack)
			inet_twsk_reschedule(tw, TCP_TIMEWAIT_LEN);

		वापस tcp_समयरुको_check_oow_rate_limit(
			tw, skb, LINUX_MIB_TCPACKSKIPPEDTIMEWAIT);
	पूर्ण
	inet_twsk_put(tw);
	वापस TCP_TW_SUCCESS;
पूर्ण
EXPORT_SYMBOL(tcp_समयरुको_state_process);

/*
 * Move a socket to समय-रुको or dead fin-रुको-2 state.
 */
व्योम tcp_समय_रुको(काष्ठा sock *sk, पूर्णांक state, पूर्णांक समयo)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा inet_समयरुको_sock *tw;
	काष्ठा inet_समयरुको_death_row *tcp_death_row = &sock_net(sk)->ipv4.tcp_death_row;

	tw = inet_twsk_alloc(sk, tcp_death_row, state);

	अगर (tw) अणु
		काष्ठा tcp_समयरुको_sock *tcptw = tcp_twsk((काष्ठा sock *)tw);
		स्थिर पूर्णांक rto = (icsk->icsk_rto << 2) - (icsk->icsk_rto >> 1);
		काष्ठा inet_sock *inet = inet_sk(sk);

		tw->tw_transparent	= inet->transparent;
		tw->tw_mark		= sk->sk_mark;
		tw->tw_priority		= sk->sk_priority;
		tw->tw_rcv_wscale	= tp->rx_opt.rcv_wscale;
		tcptw->tw_rcv_nxt	= tp->rcv_nxt;
		tcptw->tw_snd_nxt	= tp->snd_nxt;
		tcptw->tw_rcv_wnd	= tcp_receive_winकरोw(tp);
		tcptw->tw_ts_recent	= tp->rx_opt.ts_recent;
		tcptw->tw_ts_recent_stamp = tp->rx_opt.ts_recent_stamp;
		tcptw->tw_ts_offset	= tp->tsoffset;
		tcptw->tw_last_oow_ack_समय = 0;
		tcptw->tw_tx_delay	= tp->tcp_tx_delay;
#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (tw->tw_family == PF_INET6) अणु
			काष्ठा ipv6_pinfo *np = inet6_sk(sk);

			tw->tw_v6_daddr = sk->sk_v6_daddr;
			tw->tw_v6_rcv_saddr = sk->sk_v6_rcv_saddr;
			tw->tw_tclass = np->tclass;
			tw->tw_flowlabel = be32_to_cpu(np->flow_label & IPV6_FLOWLABEL_MASK);
			tw->tw_txhash = sk->sk_txhash;
			tw->tw_ipv6only = sk->sk_ipv6only;
		पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_TCP_MD5SIG
		/*
		 * The समयरुको bucket करोes not have the key DB from the
		 * sock काष्ठाure. We just make a quick copy of the
		 * md5 key being used (अगर indeed we are using one)
		 * so the समयरुको ack generating code has the key.
		 */
		करो अणु
			tcptw->tw_md5_key = शून्य;
			अगर (अटल_branch_unlikely(&tcp_md5_needed)) अणु
				काष्ठा tcp_md5sig_key *key;

				key = tp->af_specअगरic->md5_lookup(sk, sk);
				अगर (key) अणु
					tcptw->tw_md5_key = kmemdup(key, माप(*key), GFP_ATOMIC);
					BUG_ON(tcptw->tw_md5_key && !tcp_alloc_md5sig_pool());
				पूर्ण
			पूर्ण
		पूर्ण जबतक (0);
#पूर्ण_अगर

		/* Get the TIME_WAIT समयout firing. */
		अगर (समयo < rto)
			समयo = rto;

		अगर (state == TCP_TIME_WAIT)
			समयo = TCP_TIMEWAIT_LEN;

		/* tw_समयr is pinned, so we need to make sure BH are disabled
		 * in following section, otherwise समयr handler could run beक्रमe
		 * we complete the initialization.
		 */
		local_bh_disable();
		inet_twsk_schedule(tw, समयo);
		/* Linkage updates.
		 * Note that access to tw after this poपूर्णांक is illegal.
		 */
		inet_twsk_hashdance(tw, sk, &tcp_hashinfo);
		local_bh_enable();
	पूर्ण अन्यथा अणु
		/* Sorry, अगर we're out of memory, just CLOSE this
		 * socket up.  We've got bigger problems than
		 * non-graceful socket closings.
		 */
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPTIMEWAITOVERFLOW);
	पूर्ण

	tcp_update_metrics(sk);
	tcp_करोne(sk);
पूर्ण
EXPORT_SYMBOL(tcp_समय_रुको);

व्योम tcp_twsk_deकाष्ठाor(काष्ठा sock *sk)
अणु
#अगर_घोषित CONFIG_TCP_MD5SIG
	अगर (अटल_branch_unlikely(&tcp_md5_needed)) अणु
		काष्ठा tcp_समयरुको_sock *twsk = tcp_twsk(sk);

		अगर (twsk->tw_md5_key)
			kमुक्त_rcu(twsk->tw_md5_key, rcu);
	पूर्ण
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(tcp_twsk_deकाष्ठाor);

/* Warning : This function is called without sk_listener being locked.
 * Be sure to पढ़ो socket fields once, as their value could change under us.
 */
व्योम tcp_खोलोreq_init_rwin(काष्ठा request_sock *req,
			   स्थिर काष्ठा sock *sk_listener,
			   स्थिर काष्ठा dst_entry *dst)
अणु
	काष्ठा inet_request_sock *ireq = inet_rsk(req);
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk_listener);
	पूर्णांक full_space = tcp_full_space(sk_listener);
	u32 winकरोw_clamp;
	__u8 rcv_wscale;
	u32 rcv_wnd;
	पूर्णांक mss;

	mss = tcp_mss_clamp(tp, dst_metric_advmss(dst));
	winकरोw_clamp = READ_ONCE(tp->winकरोw_clamp);
	/* Set this up on the first call only */
	req->rsk_winकरोw_clamp = winकरोw_clamp ? : dst_metric(dst, RTAX_WINDOW);

	/* limit the winकरोw selection अगर the user enक्रमce a smaller rx buffer */
	अगर (sk_listener->sk_userlocks & SOCK_RCVBUF_LOCK &&
	    (req->rsk_winकरोw_clamp > full_space || req->rsk_winकरोw_clamp == 0))
		req->rsk_winकरोw_clamp = full_space;

	rcv_wnd = tcp_rwnd_init_bpf((काष्ठा sock *)req);
	अगर (rcv_wnd == 0)
		rcv_wnd = dst_metric(dst, RTAX_INITRWND);
	अन्यथा अगर (full_space < rcv_wnd * mss)
		full_space = rcv_wnd * mss;

	/* tcp_full_space because it is guaranteed to be the first packet */
	tcp_select_initial_winकरोw(sk_listener, full_space,
		mss - (ireq->tstamp_ok ? TCPOLEN_TSTAMP_ALIGNED : 0),
		&req->rsk_rcv_wnd,
		&req->rsk_winकरोw_clamp,
		ireq->wscale_ok,
		&rcv_wscale,
		rcv_wnd);
	ireq->rcv_wscale = rcv_wscale;
पूर्ण
EXPORT_SYMBOL(tcp_खोलोreq_init_rwin);

अटल व्योम tcp_ecn_खोलोreq_child(काष्ठा tcp_sock *tp,
				  स्थिर काष्ठा request_sock *req)
अणु
	tp->ecn_flags = inet_rsk(req)->ecn_ok ? TCP_ECN_OK : 0;
पूर्ण

व्योम tcp_ca_खोलोreq_child(काष्ठा sock *sk, स्थिर काष्ठा dst_entry *dst)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	u32 ca_key = dst_metric(dst, RTAX_CC_ALGO);
	bool ca_got_dst = false;

	अगर (ca_key != TCP_CA_UNSPEC) अणु
		स्थिर काष्ठा tcp_congestion_ops *ca;

		rcu_पढ़ो_lock();
		ca = tcp_ca_find_key(ca_key);
		अगर (likely(ca && bpf_try_module_get(ca, ca->owner))) अणु
			icsk->icsk_ca_dst_locked = tcp_ca_dst_locked(dst);
			icsk->icsk_ca_ops = ca;
			ca_got_dst = true;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	/* If no valid choice made yet, assign current प्रणाली शेष ca. */
	अगर (!ca_got_dst &&
	    (!icsk->icsk_ca_setsockopt ||
	     !bpf_try_module_get(icsk->icsk_ca_ops, icsk->icsk_ca_ops->owner)))
		tcp_assign_congestion_control(sk);

	tcp_set_ca_state(sk, TCP_CA_Open);
पूर्ण
EXPORT_SYMBOL_GPL(tcp_ca_खोलोreq_child);

अटल व्योम smc_check_reset_syn_req(काष्ठा tcp_sock *oldtp,
				    काष्ठा request_sock *req,
				    काष्ठा tcp_sock *newtp)
अणु
#अगर IS_ENABLED(CONFIG_SMC)
	काष्ठा inet_request_sock *ireq;

	अगर (अटल_branch_unlikely(&tcp_have_smc)) अणु
		ireq = inet_rsk(req);
		अगर (oldtp->syn_smc && !ireq->smc_ok)
			newtp->syn_smc = 0;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/* This is not only more efficient than what we used to करो, it eliminates
 * a lot of code duplication between IPv4/IPv6 SYN recv processing. -DaveM
 *
 * Actually, we could lots of memory ग_लिखोs here. tp of listening
 * socket contains all necessary शेष parameters.
 */
काष्ठा sock *tcp_create_खोलोreq_child(स्थिर काष्ठा sock *sk,
				      काष्ठा request_sock *req,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *newsk = inet_csk_clone_lock(sk, req, GFP_ATOMIC);
	स्थिर काष्ठा inet_request_sock *ireq = inet_rsk(req);
	काष्ठा tcp_request_sock *treq = tcp_rsk(req);
	काष्ठा inet_connection_sock *newicsk;
	काष्ठा tcp_sock *oldtp, *newtp;
	u32 seq;

	अगर (!newsk)
		वापस शून्य;

	newicsk = inet_csk(newsk);
	newtp = tcp_sk(newsk);
	oldtp = tcp_sk(sk);

	smc_check_reset_syn_req(oldtp, req, newtp);

	/* Now setup tcp_sock */
	newtp->pred_flags = 0;

	seq = treq->rcv_isn + 1;
	newtp->rcv_wup = seq;
	WRITE_ONCE(newtp->copied_seq, seq);
	WRITE_ONCE(newtp->rcv_nxt, seq);
	newtp->segs_in = 1;

	seq = treq->snt_isn + 1;
	newtp->snd_sml = newtp->snd_una = seq;
	WRITE_ONCE(newtp->snd_nxt, seq);
	newtp->snd_up = seq;

	INIT_LIST_HEAD(&newtp->tsq_node);
	INIT_LIST_HEAD(&newtp->tsorted_sent_queue);

	tcp_init_wl(newtp, treq->rcv_isn);

	minmax_reset(&newtp->rtt_min, tcp_jअगरfies32, ~0U);
	newicsk->icsk_ack.lrcvसमय = tcp_jअगरfies32;

	newtp->lsndसमय = tcp_jअगरfies32;
	newsk->sk_txhash = treq->txhash;
	newtp->total_retrans = req->num_retrans;

	tcp_init_xmit_समयrs(newsk);
	WRITE_ONCE(newtp->ग_लिखो_seq, newtp->pushed_seq = treq->snt_isn + 1);

	अगर (sock_flag(newsk, SOCK_KEEPOPEN))
		inet_csk_reset_keepalive_समयr(newsk,
					       keepalive_समय_when(newtp));

	newtp->rx_opt.tstamp_ok = ireq->tstamp_ok;
	newtp->rx_opt.sack_ok = ireq->sack_ok;
	newtp->winकरोw_clamp = req->rsk_winकरोw_clamp;
	newtp->rcv_ssthresh = req->rsk_rcv_wnd;
	newtp->rcv_wnd = req->rsk_rcv_wnd;
	newtp->rx_opt.wscale_ok = ireq->wscale_ok;
	अगर (newtp->rx_opt.wscale_ok) अणु
		newtp->rx_opt.snd_wscale = ireq->snd_wscale;
		newtp->rx_opt.rcv_wscale = ireq->rcv_wscale;
	पूर्ण अन्यथा अणु
		newtp->rx_opt.snd_wscale = newtp->rx_opt.rcv_wscale = 0;
		newtp->winकरोw_clamp = min(newtp->winकरोw_clamp, 65535U);
	पूर्ण
	newtp->snd_wnd = ntohs(tcp_hdr(skb)->winकरोw) << newtp->rx_opt.snd_wscale;
	newtp->max_winकरोw = newtp->snd_wnd;

	अगर (newtp->rx_opt.tstamp_ok) अणु
		newtp->rx_opt.ts_recent = req->ts_recent;
		newtp->rx_opt.ts_recent_stamp = kसमय_get_seconds();
		newtp->tcp_header_len = माप(काष्ठा tcphdr) + TCPOLEN_TSTAMP_ALIGNED;
	पूर्ण अन्यथा अणु
		newtp->rx_opt.ts_recent_stamp = 0;
		newtp->tcp_header_len = माप(काष्ठा tcphdr);
	पूर्ण
	अगर (req->num_समयout) अणु
		newtp->unकरो_marker = treq->snt_isn;
		newtp->retrans_stamp = भाग_u64(treq->snt_synack,
					       USEC_PER_SEC / TCP_TS_HZ);
	पूर्ण
	newtp->tsoffset = treq->ts_off;
#अगर_घोषित CONFIG_TCP_MD5SIG
	newtp->md5sig_info = शून्य;	/*XXX*/
	अगर (newtp->af_specअगरic->md5_lookup(sk, newsk))
		newtp->tcp_header_len += TCPOLEN_MD5SIG_ALIGNED;
#पूर्ण_अगर
	अगर (skb->len >= TCP_MSS_DEFAULT + newtp->tcp_header_len)
		newicsk->icsk_ack.last_seg_size = skb->len - newtp->tcp_header_len;
	newtp->rx_opt.mss_clamp = req->mss;
	tcp_ecn_खोलोreq_child(newtp, req);
	newtp->fastखोलो_req = शून्य;
	RCU_INIT_POINTER(newtp->fastखोलो_rsk, शून्य);

	tcp_bpf_clone(sk, newsk);

	__TCP_INC_STATS(sock_net(sk), TCP_MIB_PASSIVEOPENS);

	वापस newsk;
पूर्ण
EXPORT_SYMBOL(tcp_create_खोलोreq_child);

/*
 * Process an incoming packet क्रम SYN_RECV sockets represented as a
 * request_sock. Normally sk is the listener socket but क्रम TFO it
 * poपूर्णांकs to the child socket.
 *
 * XXX (TFO) - The current impl contains a special check क्रम ack
 * validation and inside tcp_v4_reqsk_send_ack(). Can we करो better?
 *
 * We करोn't need to initialize tmp_opt.sack_ok as we don't use the results
 */

काष्ठा sock *tcp_check_req(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			   काष्ठा request_sock *req,
			   bool fastखोलो, bool *req_stolen)
अणु
	काष्ठा tcp_options_received पंचांगp_opt;
	काष्ठा sock *child;
	स्थिर काष्ठा tcphdr *th = tcp_hdr(skb);
	__be32 flg = tcp_flag_word(th) & (TCP_FLAG_RST|TCP_FLAG_SYN|TCP_FLAG_ACK);
	bool paws_reject = false;
	bool own_req;

	पंचांगp_opt.saw_tstamp = 0;
	अगर (th->करोff > (माप(काष्ठा tcphdr)>>2)) अणु
		tcp_parse_options(sock_net(sk), skb, &पंचांगp_opt, 0, शून्य);

		अगर (पंचांगp_opt.saw_tstamp) अणु
			पंचांगp_opt.ts_recent = req->ts_recent;
			अगर (पंचांगp_opt.rcv_tsecr)
				पंचांगp_opt.rcv_tsecr -= tcp_rsk(req)->ts_off;
			/* We करो not store true stamp, but it is not required,
			 * it can be estimated (approximately)
			 * from another data.
			 */
			पंचांगp_opt.ts_recent_stamp = kसमय_get_seconds() - ((TCP_TIMEOUT_INIT/HZ)<<req->num_समयout);
			paws_reject = tcp_paws_reject(&पंचांगp_opt, th->rst);
		पूर्ण
	पूर्ण

	/* Check क्रम pure retransmitted SYN. */
	अगर (TCP_SKB_CB(skb)->seq == tcp_rsk(req)->rcv_isn &&
	    flg == TCP_FLAG_SYN &&
	    !paws_reject) अणु
		/*
		 * RFC793 draws (Incorrectly! It was fixed in RFC1122)
		 * this हाल on figure 6 and figure 8, but क्रमmal
		 * protocol description says NOTHING.
		 * To be more exact, it says that we should send ACK,
		 * because this segment (at least, अगर it has no data)
		 * is out of winकरोw.
		 *
		 *  CONCLUSION: RFC793 (even with RFC1122) DOES NOT
		 *  describe SYN-RECV state. All the description
		 *  is wrong, we cannot believe to it and should
		 *  rely only on common sense and implementation
		 *  experience.
		 *
		 * Enक्रमce "SYN-ACK" according to figure 8, figure 6
		 * of RFC793, fixed by RFC1122.
		 *
		 * Note that even अगर there is new data in the SYN packet
		 * they will be thrown away too.
		 *
		 * Reset समयr after retransmitting SYNACK, similar to
		 * the idea of fast retransmit in recovery.
		 */
		अगर (!tcp_oow_rate_limited(sock_net(sk), skb,
					  LINUX_MIB_TCPACKSKIPPEDSYNRECV,
					  &tcp_rsk(req)->last_oow_ack_समय) &&

		    !inet_rtx_syn_ack(sk, req)) अणु
			अचिन्हित दीर्घ expires = jअगरfies;

			expires += min(TCP_TIMEOUT_INIT << req->num_समयout,
				       TCP_RTO_MAX);
			अगर (!fastखोलो)
				mod_समयr_pending(&req->rsk_समयr, expires);
			अन्यथा
				req->rsk_समयr.expires = expires;
		पूर्ण
		वापस शून्य;
	पूर्ण

	/* Further reproduces section "SEGMENT ARRIVES"
	   क्रम state SYN-RECEIVED of RFC793.
	   It is broken, however, it करोes not work only
	   when SYNs are crossed.

	   You would think that SYN crossing is impossible here, since
	   we should have a SYN_SENT socket (from connect()) on our end,
	   but this is not true अगर the crossed SYNs were sent to both
	   ends by a malicious third party.  We must defend against this,
	   and to करो that we first verअगरy the ACK (as per RFC793, page
	   36) and reset अगर it is invalid.  Is this a true full defense?
	   To convince ourselves, let us consider a way in which the ACK
	   test can still pass in this 'malicious crossed SYNs' हाल.
	   Malicious sender sends identical SYNs (and thus identical sequence
	   numbers) to both A and B:

		A: माला_लो SYN, seq=7
		B: माला_लो SYN, seq=7

	   By our good क्रमtune, both A and B select the same initial
	   send sequence number of seven :-)

		A: sends SYN|ACK, seq=7, ack_seq=8
		B: sends SYN|ACK, seq=7, ack_seq=8

	   So we are now A eating this SYN|ACK, ACK test passes.  So
	   करोes sequence test, SYN is truncated, and thus we consider
	   it a bare ACK.

	   If icsk->icsk_accept_queue.rskq_defer_accept, we silently drop this
	   bare ACK.  Otherwise, we create an established connection.  Both
	   ends (listening sockets) accept the new incoming connection and try
	   to talk to each other. 8-)

	   Note: This हाल is both harmless, and rare.  Possibility is about the
	   same as us discovering पूर्णांकelligent lअगरe on another plant tomorrow.

	   But generally, we should (RFC lies!) to accept ACK
	   from SYNACK both here and in tcp_rcv_state_process().
	   tcp_rcv_state_process() करोes not, hence, we करो not too.

	   Note that the हाल is असलolutely generic:
	   we cannot optimize anything here without
	   violating protocol. All the checks must be made
	   beक्रमe attempt to create socket.
	 */

	/* RFC793 page 36: "If the connection is in any non-synchronized state ...
	 *                  and the incoming segment acknowledges something not yet
	 *                  sent (the segment carries an unacceptable ACK) ...
	 *                  a reset is sent."
	 *
	 * Invalid ACK: reset will be sent by listening socket.
	 * Note that the ACK validity check क्रम a Fast Open socket is करोne
	 * अन्यथाwhere and is checked directly against the child socket rather
	 * than req because user data may have been sent out.
	 */
	अगर ((flg & TCP_FLAG_ACK) && !fastखोलो &&
	    (TCP_SKB_CB(skb)->ack_seq !=
	     tcp_rsk(req)->snt_isn + 1))
		वापस sk;

	/* Also, it would be not so bad idea to check rcv_tsecr, which
	 * is essentially ACK extension and too early or too late values
	 * should cause reset in unsynchronized states.
	 */

	/* RFC793: "first check sequence number". */

	अगर (paws_reject || !tcp_in_winकरोw(TCP_SKB_CB(skb)->seq, TCP_SKB_CB(skb)->end_seq,
					  tcp_rsk(req)->rcv_nxt, tcp_rsk(req)->rcv_nxt + req->rsk_rcv_wnd)) अणु
		/* Out of winकरोw: send ACK and drop. */
		अगर (!(flg & TCP_FLAG_RST) &&
		    !tcp_oow_rate_limited(sock_net(sk), skb,
					  LINUX_MIB_TCPACKSKIPPEDSYNRECV,
					  &tcp_rsk(req)->last_oow_ack_समय))
			req->rsk_ops->send_ack(sk, skb, req);
		अगर (paws_reject)
			__NET_INC_STATS(sock_net(sk), LINUX_MIB_PAWSESTABREJECTED);
		वापस शून्य;
	पूर्ण

	/* In sequence, PAWS is OK. */

	अगर (पंचांगp_opt.saw_tstamp && !after(TCP_SKB_CB(skb)->seq, tcp_rsk(req)->rcv_nxt))
		req->ts_recent = पंचांगp_opt.rcv_tsval;

	अगर (TCP_SKB_CB(skb)->seq == tcp_rsk(req)->rcv_isn) अणु
		/* Truncate SYN, it is out of winकरोw starting
		   at tcp_rsk(req)->rcv_isn + 1. */
		flg &= ~TCP_FLAG_SYN;
	पूर्ण

	/* RFC793: "second check the RST bit" and
	 *	   "fourth, check the SYN bit"
	 */
	अगर (flg & (TCP_FLAG_RST|TCP_FLAG_SYN)) अणु
		__TCP_INC_STATS(sock_net(sk), TCP_MIB_ATTEMPTFAILS);
		जाओ embryonic_reset;
	पूर्ण

	/* ACK sequence verअगरied above, just make sure ACK is
	 * set.  If ACK not set, just silently drop the packet.
	 *
	 * XXX (TFO) - अगर we ever allow "data after SYN", the
	 * following check needs to be हटाओd.
	 */
	अगर (!(flg & TCP_FLAG_ACK))
		वापस शून्य;

	/* For Fast Open no more processing is needed (sk is the
	 * child socket).
	 */
	अगर (fastखोलो)
		वापस sk;

	/* While TCP_DEFER_ACCEPT is active, drop bare ACK. */
	अगर (req->num_समयout < inet_csk(sk)->icsk_accept_queue.rskq_defer_accept &&
	    TCP_SKB_CB(skb)->end_seq == tcp_rsk(req)->rcv_isn + 1) अणु
		inet_rsk(req)->acked = 1;
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPDEFERACCEPTDROP);
		वापस शून्य;
	पूर्ण

	/* OK, ACK is valid, create big socket and
	 * feed this segment to it. It will repeat all
	 * the tests. THIS SEGMENT MUST MOVE SOCKET TO
	 * ESTABLISHED STATE. If it will be dropped after
	 * socket is created, रुको क्रम troubles.
	 */
	child = inet_csk(sk)->icsk_af_ops->syn_recv_sock(sk, skb, req, शून्य,
							 req, &own_req);
	अगर (!child)
		जाओ listen_overflow;

	अगर (own_req && rsk_drop_req(req)) अणु
		reqsk_queue_हटाओd(&inet_csk(sk)->icsk_accept_queue, req);
		inet_csk_reqsk_queue_drop_and_put(sk, req);
		वापस child;
	पूर्ण

	sock_rps_save_rxhash(child, skb);
	tcp_synack_rtt_meas(child, req);
	*req_stolen = !own_req;
	वापस inet_csk_complete_hashdance(sk, child, req, own_req);

listen_overflow:
	अगर (!sock_net(sk)->ipv4.sysctl_tcp_पात_on_overflow) अणु
		inet_rsk(req)->acked = 1;
		वापस शून्य;
	पूर्ण

embryonic_reset:
	अगर (!(flg & TCP_FLAG_RST)) अणु
		/* Received a bad SYN pkt - क्रम TFO We try not to reset
		 * the local connection unless it's really necessary to
		 * aव्योम becoming vulnerable to outside attack aiming at
		 * resetting legit local connections.
		 */
		req->rsk_ops->send_reset(sk, skb);
	पूर्ण अन्यथा अगर (fastखोलो) अणु /* received a valid RST pkt */
		reqsk_fastखोलो_हटाओ(sk, req, true);
		tcp_reset(sk, skb);
	पूर्ण
	अगर (!fastखोलो) अणु
		bool unlinked = inet_csk_reqsk_queue_drop(sk, req);

		अगर (unlinked)
			__NET_INC_STATS(sock_net(sk), LINUX_MIB_EMBRYONICRSTS);
		*req_stolen = !unlinked;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(tcp_check_req);

/*
 * Queue segment on the new socket अगर the new socket is active,
 * otherwise we just लघुcircuit this and जारी with
 * the new socket.
 *
 * For the vast majority of हालs child->sk_state will be TCP_SYN_RECV
 * when entering. But other states are possible due to a race condition
 * where after __inet_lookup_established() fails but beक्रमe the listener
 * locked is obtained, other packets cause the same connection to
 * be created.
 */

पूर्णांक tcp_child_process(काष्ठा sock *parent, काष्ठा sock *child,
		      काष्ठा sk_buff *skb)
	__releases(&((child)->sk_lock.slock))
अणु
	पूर्णांक ret = 0;
	पूर्णांक state = child->sk_state;

	/* record NAPI ID of child */
	sk_mark_napi_id(child, skb);

	tcp_segs_in(tcp_sk(child), skb);
	अगर (!sock_owned_by_user(child)) अणु
		ret = tcp_rcv_state_process(child, skb);
		/* Wakeup parent, send SIGIO */
		अगर (state == TCP_SYN_RECV && child->sk_state != state)
			parent->sk_data_पढ़ोy(parent);
	पूर्ण अन्यथा अणु
		/* Alas, it is possible again, because we करो lookup
		 * in मुख्य socket hash table and lock on listening
		 * socket करोes not protect us more.
		 */
		__sk_add_backlog(child, skb);
	पूर्ण

	bh_unlock_sock(child);
	sock_put(child);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(tcp_child_process);
