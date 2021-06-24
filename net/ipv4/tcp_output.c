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

/*
 * Changes:	Pedro Roque	:	Retransmit queue handled by TCP.
 *				:	Fragmentation on mtu decrease
 *				:	Segment collapse on retransmit
 *				:	AF independence
 *
 *		Linus Torvalds	:	send_delayed_ack
 *		David S. Miller	:	Charge memory using the right skb
 *					during syn/ack processing.
 *		David S. Miller :	Output engine completely rewritten.
 *		Andrea Arcangeli:	SYNACK carry ts_recent in tsecr.
 *		Cacophonix Gaul :	draft-minshall-nagle-01
 *		J Hadi Salim	:	ECN support
 *
 */

#घोषणा pr_fmt(fmt) "TCP: " fmt

#समावेश <net/tcp.h>
#समावेश <net/mptcp.h>

#समावेश <linux/compiler.h>
#समावेश <linux/gfp.h>
#समावेश <linux/module.h>
#समावेश <linux/अटल_key.h>

#समावेश <trace/events/tcp.h>

/* Refresh घड़ीs of a TCP socket,
 * ensuring monotically increasing values.
 */
व्योम tcp_mstamp_refresh(काष्ठा tcp_sock *tp)
अणु
	u64 val = tcp_घड़ी_ns();

	tp->tcp_घड़ी_cache = val;
	tp->tcp_mstamp = भाग_u64(val, NSEC_PER_USEC);
पूर्ण

अटल bool tcp_ग_लिखो_xmit(काष्ठा sock *sk, अचिन्हित पूर्णांक mss_now, पूर्णांक nonagle,
			   पूर्णांक push_one, gfp_t gfp);

/* Account क्रम new data that has been sent to the network. */
अटल व्योम tcp_event_new_data_sent(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	अचिन्हित पूर्णांक prior_packets = tp->packets_out;

	WRITE_ONCE(tp->snd_nxt, TCP_SKB_CB(skb)->end_seq);

	__skb_unlink(skb, &sk->sk_ग_लिखो_queue);
	tcp_rbtree_insert(&sk->tcp_rtx_queue, skb);

	अगर (tp->highest_sack == शून्य)
		tp->highest_sack = skb;

	tp->packets_out += tcp_skb_pcount(skb);
	अगर (!prior_packets || icsk->icsk_pending == ICSK_TIME_LOSS_PROBE)
		tcp_rearm_rto(sk);

	NET_ADD_STATS(sock_net(sk), LINUX_MIB_TCPORIGDATASENT,
		      tcp_skb_pcount(skb));
पूर्ण

/* SND.NXT, अगर winकरोw was not shrunk or the amount of shrunk was less than one
 * winकरोw scaling factor due to loss of precision.
 * If winकरोw has been shrunk, what should we make? It is not clear at all.
 * Using SND.UNA we will fail to खोलो winकरोw, SND.NXT is out of winकरोw. :-(
 * Anything in between SND.UNA...SND.UNA+SND.WND also can be alपढ़ोy
 * invalid. OK, let's make this क्रम now:
 */
अटल अंतरभूत __u32 tcp_acceptable_seq(स्थिर काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (!beक्रमe(tcp_wnd_end(tp), tp->snd_nxt) ||
	    (tp->rx_opt.wscale_ok &&
	     ((tp->snd_nxt - tcp_wnd_end(tp)) < (1 << tp->rx_opt.rcv_wscale))))
		वापस tp->snd_nxt;
	अन्यथा
		वापस tcp_wnd_end(tp);
पूर्ण

/* Calculate mss to advertise in SYN segment.
 * RFC1122, RFC1063, draft-ietf-tcpimpl-pmtud-01 state that:
 *
 * 1. It is independent of path mtu.
 * 2. Ideally, it is maximal possible segment size i.e. 65535-40.
 * 3. For IPv4 it is reasonable to calculate it from maximal MTU of
 *    attached devices, because some buggy hosts are confused by
 *    large MSS.
 * 4. We करो not make 3, we advertise MSS, calculated from first
 *    hop device mtu, but allow to उठाओ it to ip_rt_min_advmss.
 *    This may be overridden via inक्रमmation stored in routing table.
 * 5. Value 65535 क्रम MSS is valid in IPv6 and means "as large as possible,
 *    probably even Jumbo".
 */
अटल __u16 tcp_advertise_mss(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	स्थिर काष्ठा dst_entry *dst = __sk_dst_get(sk);
	पूर्णांक mss = tp->advmss;

	अगर (dst) अणु
		अचिन्हित पूर्णांक metric = dst_metric_advmss(dst);

		अगर (metric < mss) अणु
			mss = metric;
			tp->advmss = mss;
		पूर्ण
	पूर्ण

	वापस (__u16)mss;
पूर्ण

/* RFC2861. Reset CWND after idle period दीर्घer RTO to "restart window".
 * This is the first part of cwnd validation mechanism.
 */
व्योम tcp_cwnd_restart(काष्ठा sock *sk, s32 delta)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 restart_cwnd = tcp_init_cwnd(tp, __sk_dst_get(sk));
	u32 cwnd = tp->snd_cwnd;

	tcp_ca_event(sk, CA_EVENT_CWND_RESTART);

	tp->snd_ssthresh = tcp_current_ssthresh(sk);
	restart_cwnd = min(restart_cwnd, cwnd);

	जबतक ((delta -= inet_csk(sk)->icsk_rto) > 0 && cwnd > restart_cwnd)
		cwnd >>= 1;
	tp->snd_cwnd = max(cwnd, restart_cwnd);
	tp->snd_cwnd_stamp = tcp_jअगरfies32;
	tp->snd_cwnd_used = 0;
पूर्ण

/* Congestion state accounting after a packet has been sent. */
अटल व्योम tcp_event_data_sent(काष्ठा tcp_sock *tp,
				काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	स्थिर u32 now = tcp_jअगरfies32;

	अगर (tcp_packets_in_flight(tp) == 0)
		tcp_ca_event(sk, CA_EVENT_TX_START);

	/* If this is the first data packet sent in response to the
	 * previous received data,
	 * and it is a reply क्रम ato after last received packet,
	 * increase pingpong count.
	 */
	अगर (beक्रमe(tp->lsndसमय, icsk->icsk_ack.lrcvसमय) &&
	    (u32)(now - icsk->icsk_ack.lrcvसमय) < icsk->icsk_ack.ato)
		inet_csk_inc_pingpong_cnt(sk);

	tp->lsndसमय = now;
पूर्ण

/* Account क्रम an ACK we sent. */
अटल अंतरभूत व्योम tcp_event_ack_sent(काष्ठा sock *sk, अचिन्हित पूर्णांक pkts,
				      u32 rcv_nxt)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (unlikely(tp->compressed_ack)) अणु
		NET_ADD_STATS(sock_net(sk), LINUX_MIB_TCPACKCOMPRESSED,
			      tp->compressed_ack);
		tp->compressed_ack = 0;
		अगर (hrसमयr_try_to_cancel(&tp->compressed_ack_समयr) == 1)
			__sock_put(sk);
	पूर्ण

	अगर (unlikely(rcv_nxt != tp->rcv_nxt))
		वापस;  /* Special ACK sent by DCTCP to reflect ECN */
	tcp_dec_quickack_mode(sk, pkts);
	inet_csk_clear_xmit_समयr(sk, ICSK_TIME_DACK);
पूर्ण

/* Determine a winकरोw scaling and initial winकरोw to offer.
 * Based on the assumption that the given amount of space
 * will be offered. Store the results in the tp काष्ठाure.
 * NOTE: क्रम smooth operation initial space offering should
 * be a multiple of mss अगर possible. We assume here that mss >= 1.
 * This MUST be enक्रमced by all callers.
 */
व्योम tcp_select_initial_winकरोw(स्थिर काष्ठा sock *sk, पूर्णांक __space, __u32 mss,
			       __u32 *rcv_wnd, __u32 *winकरोw_clamp,
			       पूर्णांक wscale_ok, __u8 *rcv_wscale,
			       __u32 init_rcv_wnd)
अणु
	अचिन्हित पूर्णांक space = (__space < 0 ? 0 : __space);

	/* If no clamp set the clamp to the max possible scaled winकरोw */
	अगर (*winकरोw_clamp == 0)
		(*winकरोw_clamp) = (U16_MAX << TCP_MAX_WSCALE);
	space = min(*winकरोw_clamp, space);

	/* Quantize space offering to a multiple of mss अगर possible. */
	अगर (space > mss)
		space = roundकरोwn(space, mss);

	/* NOTE: offering an initial winकरोw larger than 32767
	 * will अवरोध some buggy TCP stacks. If the admin tells us
	 * it is likely we could be speaking with such a buggy stack
	 * we will truncate our initial winकरोw offering to 32K-1
	 * unless the remote has sent us a winकरोw scaling option,
	 * which we पूर्णांकerpret as a sign the remote TCP is not
	 * misपूर्णांकerpreting the winकरोw field as a चिन्हित quantity.
	 */
	अगर (sock_net(sk)->ipv4.sysctl_tcp_workaround_चिन्हित_winकरोws)
		(*rcv_wnd) = min(space, MAX_TCP_WINDOW);
	अन्यथा
		(*rcv_wnd) = min_t(u32, space, U16_MAX);

	अगर (init_rcv_wnd)
		*rcv_wnd = min(*rcv_wnd, init_rcv_wnd * mss);

	*rcv_wscale = 0;
	अगर (wscale_ok) अणु
		/* Set winकरोw scaling on max possible winकरोw */
		space = max_t(u32, space, sock_net(sk)->ipv4.sysctl_tcp_rmem[2]);
		space = max_t(u32, space, sysctl_rmem_max);
		space = min_t(u32, space, *winकरोw_clamp);
		*rcv_wscale = clamp_t(पूर्णांक, ilog2(space) - 15,
				      0, TCP_MAX_WSCALE);
	पूर्ण
	/* Set the clamp no higher than max representable value */
	(*winकरोw_clamp) = min_t(__u32, U16_MAX << (*rcv_wscale), *winकरोw_clamp);
पूर्ण
EXPORT_SYMBOL(tcp_select_initial_winकरोw);

/* Chose a new winकरोw to advertise, update state in tcp_sock क्रम the
 * socket, and वापस result with RFC1323 scaling applied.  The वापस
 * value can be stuffed directly पूर्णांकo th->winकरोw क्रम an outgoing
 * frame.
 */
अटल u16 tcp_select_winकरोw(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 old_win = tp->rcv_wnd;
	u32 cur_win = tcp_receive_winकरोw(tp);
	u32 new_win = __tcp_select_winकरोw(sk);

	/* Never shrink the offered winकरोw */
	अगर (new_win < cur_win) अणु
		/* Danger Will Robinson!
		 * Don't update rcv_wup/rcv_wnd here or अन्यथा
		 * we will not be able to advertise a zero
		 * winकरोw in समय.  --DaveM
		 *
		 * Relax Will Robinson.
		 */
		अगर (new_win == 0)
			NET_INC_STATS(sock_net(sk),
				      LINUX_MIB_TCPWANTZEROWINDOWADV);
		new_win = ALIGN(cur_win, 1 << tp->rx_opt.rcv_wscale);
	पूर्ण
	tp->rcv_wnd = new_win;
	tp->rcv_wup = tp->rcv_nxt;

	/* Make sure we करो not exceed the maximum possible
	 * scaled winकरोw.
	 */
	अगर (!tp->rx_opt.rcv_wscale &&
	    sock_net(sk)->ipv4.sysctl_tcp_workaround_चिन्हित_winकरोws)
		new_win = min(new_win, MAX_TCP_WINDOW);
	अन्यथा
		new_win = min(new_win, (65535U << tp->rx_opt.rcv_wscale));

	/* RFC1323 scaling applied */
	new_win >>= tp->rx_opt.rcv_wscale;

	/* If we advertise zero winकरोw, disable fast path. */
	अगर (new_win == 0) अणु
		tp->pred_flags = 0;
		अगर (old_win)
			NET_INC_STATS(sock_net(sk),
				      LINUX_MIB_TCPTOZEROWINDOWADV);
	पूर्ण अन्यथा अगर (old_win == 0) अणु
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPFROMZEROWINDOWADV);
	पूर्ण

	वापस new_win;
पूर्ण

/* Packet ECN state क्रम a SYN-ACK */
अटल व्योम tcp_ecn_send_synack(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);

	TCP_SKB_CB(skb)->tcp_flags &= ~TCPHDR_CWR;
	अगर (!(tp->ecn_flags & TCP_ECN_OK))
		TCP_SKB_CB(skb)->tcp_flags &= ~TCPHDR_ECE;
	अन्यथा अगर (tcp_ca_needs_ecn(sk) ||
		 tcp_bpf_ca_needs_ecn(sk))
		INET_ECN_xmit(sk);
पूर्ण

/* Packet ECN state क्रम a SYN.  */
अटल व्योम tcp_ecn_send_syn(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	bool bpf_needs_ecn = tcp_bpf_ca_needs_ecn(sk);
	bool use_ecn = sock_net(sk)->ipv4.sysctl_tcp_ecn == 1 ||
		tcp_ca_needs_ecn(sk) || bpf_needs_ecn;

	अगर (!use_ecn) अणु
		स्थिर काष्ठा dst_entry *dst = __sk_dst_get(sk);

		अगर (dst && dst_feature(dst, RTAX_FEATURE_ECN))
			use_ecn = true;
	पूर्ण

	tp->ecn_flags = 0;

	अगर (use_ecn) अणु
		TCP_SKB_CB(skb)->tcp_flags |= TCPHDR_ECE | TCPHDR_CWR;
		tp->ecn_flags = TCP_ECN_OK;
		अगर (tcp_ca_needs_ecn(sk) || bpf_needs_ecn)
			INET_ECN_xmit(sk);
	पूर्ण
पूर्ण

अटल व्योम tcp_ecn_clear_syn(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अगर (sock_net(sk)->ipv4.sysctl_tcp_ecn_fallback)
		/* tp->ecn_flags are cleared at a later poपूर्णांक in समय when
		 * SYN ACK is ultimatively being received.
		 */
		TCP_SKB_CB(skb)->tcp_flags &= ~(TCPHDR_ECE | TCPHDR_CWR);
पूर्ण

अटल व्योम
tcp_ecn_make_synack(स्थिर काष्ठा request_sock *req, काष्ठा tcphdr *th)
अणु
	अगर (inet_rsk(req)->ecn_ok)
		th->ece = 1;
पूर्ण

/* Set up ECN state क्रम a packet on a ESTABLISHED socket that is about to
 * be sent.
 */
अटल व्योम tcp_ecn_send(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			 काष्ठा tcphdr *th, पूर्णांक tcp_header_len)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (tp->ecn_flags & TCP_ECN_OK) अणु
		/* Not-retransmitted data segment: set ECT and inject CWR. */
		अगर (skb->len != tcp_header_len &&
		    !beक्रमe(TCP_SKB_CB(skb)->seq, tp->snd_nxt)) अणु
			INET_ECN_xmit(sk);
			अगर (tp->ecn_flags & TCP_ECN_QUEUE_CWR) अणु
				tp->ecn_flags &= ~TCP_ECN_QUEUE_CWR;
				th->cwr = 1;
				skb_shinfo(skb)->gso_type |= SKB_GSO_TCP_ECN;
			पूर्ण
		पूर्ण अन्यथा अगर (!tcp_ca_needs_ecn(sk)) अणु
			/* ACK or retransmitted segment: clear ECT|CE */
			INET_ECN_करोntxmit(sk);
		पूर्ण
		अगर (tp->ecn_flags & TCP_ECN_DEMAND_CWR)
			th->ece = 1;
	पूर्ण
पूर्ण

/* Conकाष्ठाs common control bits of non-data skb. If SYN/FIN is present,
 * स्वतः increment end seqno.
 */
अटल व्योम tcp_init_nondata_skb(काष्ठा sk_buff *skb, u32 seq, u8 flags)
अणु
	skb->ip_summed = CHECKSUM_PARTIAL;

	TCP_SKB_CB(skb)->tcp_flags = flags;
	TCP_SKB_CB(skb)->sacked = 0;

	tcp_skb_pcount_set(skb, 1);

	TCP_SKB_CB(skb)->seq = seq;
	अगर (flags & (TCPHDR_SYN | TCPHDR_FIN))
		seq++;
	TCP_SKB_CB(skb)->end_seq = seq;
पूर्ण

अटल अंतरभूत bool tcp_urg_mode(स्थिर काष्ठा tcp_sock *tp)
अणु
	वापस tp->snd_una != tp->snd_up;
पूर्ण

#घोषणा OPTION_SACK_ADVERTISE	(1 << 0)
#घोषणा OPTION_TS		(1 << 1)
#घोषणा OPTION_MD5		(1 << 2)
#घोषणा OPTION_WSCALE		(1 << 3)
#घोषणा OPTION_FAST_OPEN_COOKIE	(1 << 8)
#घोषणा OPTION_SMC		(1 << 9)
#घोषणा OPTION_MPTCP		(1 << 10)

अटल व्योम smc_options_ग_लिखो(__be32 *ptr, u16 *options)
अणु
#अगर IS_ENABLED(CONFIG_SMC)
	अगर (अटल_branch_unlikely(&tcp_have_smc)) अणु
		अगर (unlikely(OPTION_SMC & *options)) अणु
			*ptr++ = htonl((TCPOPT_NOP  << 24) |
				       (TCPOPT_NOP  << 16) |
				       (TCPOPT_EXP <<  8) |
				       (TCPOLEN_EXP_SMC_BASE));
			*ptr++ = htonl(TCPOPT_SMC_MAGIC);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

काष्ठा tcp_out_options अणु
	u16 options;		/* bit field of OPTION_* */
	u16 mss;		/* 0 to disable */
	u8 ws;			/* winकरोw scale, 0 to disable */
	u8 num_sack_blocks;	/* number of SACK blocks to include */
	u8 hash_size;		/* bytes in hash_location */
	u8 bpf_opt_len;		/* length of BPF hdr option */
	__u8 *hash_location;	/* temporary poपूर्णांकer, overloaded */
	__u32 tsval, tsecr;	/* need to include OPTION_TS */
	काष्ठा tcp_fastखोलो_cookie *fastखोलो_cookie;	/* Fast खोलो cookie */
	काष्ठा mptcp_out_options mptcp;
पूर्ण;

अटल व्योम mptcp_options_ग_लिखो(__be32 *ptr, स्थिर काष्ठा tcp_sock *tp,
				काष्ठा tcp_out_options *opts)
अणु
#अगर IS_ENABLED(CONFIG_MPTCP)
	अगर (unlikely(OPTION_MPTCP & opts->options))
		mptcp_ग_लिखो_options(ptr, tp, &opts->mptcp);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_CGROUP_BPF
अटल पूर्णांक bpf_skops_ग_लिखो_hdr_opt_arg0(काष्ठा sk_buff *skb,
					क्रमागत tcp_synack_type synack_type)
अणु
	अगर (unlikely(!skb))
		वापस BPF_WRITE_HDR_TCP_CURRENT_MSS;

	अगर (unlikely(synack_type == TCP_SYNACK_COOKIE))
		वापस BPF_WRITE_HDR_TCP_SYNACK_COOKIE;

	वापस 0;
पूर्ण

/* req, syn_skb and synack_type are used when writing synack */
अटल व्योम bpf_skops_hdr_opt_len(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				  काष्ठा request_sock *req,
				  काष्ठा sk_buff *syn_skb,
				  क्रमागत tcp_synack_type synack_type,
				  काष्ठा tcp_out_options *opts,
				  अचिन्हित पूर्णांक *reमुख्यing)
अणु
	काष्ठा bpf_sock_ops_kern sock_ops;
	पूर्णांक err;

	अगर (likely(!BPF_SOCK_OPS_TEST_FLAG(tcp_sk(sk),
					   BPF_SOCK_OPS_WRITE_HDR_OPT_CB_FLAG)) ||
	    !*reमुख्यing)
		वापस;

	/* *reमुख्यing has alपढ़ोy been aligned to 4 bytes, so *reमुख्यing >= 4 */

	/* init sock_ops */
	स_रखो(&sock_ops, 0, दुरत्व(काष्ठा bpf_sock_ops_kern, temp));

	sock_ops.op = BPF_SOCK_OPS_HDR_OPT_LEN_CB;

	अगर (req) अणु
		/* The listen "sk" cannot be passed here because
		 * it is not locked.  It would not make too much
		 * sense to करो bpf_setsockopt(listen_sk) based
		 * on inभागidual connection request also.
		 *
		 * Thus, "req" is passed here and the cgroup-bpf-progs
		 * of the listen "sk" will be run.
		 *
		 * "req" is also used here क्रम fastखोलो even the "sk" here is
		 * a fullsock "child" sk.  It is to keep the behavior
		 * consistent between fastखोलो and non-fastखोलो on
		 * the bpf programming side.
		 */
		sock_ops.sk = (काष्ठा sock *)req;
		sock_ops.syn_skb = syn_skb;
	पूर्ण अन्यथा अणु
		sock_owned_by_me(sk);

		sock_ops.is_fullsock = 1;
		sock_ops.sk = sk;
	पूर्ण

	sock_ops.args[0] = bpf_skops_ग_लिखो_hdr_opt_arg0(skb, synack_type);
	sock_ops.reमुख्यing_opt_len = *reमुख्यing;
	/* tcp_current_mss() करोes not pass a skb */
	अगर (skb)
		bpf_skops_init_skb(&sock_ops, skb, 0);

	err = BPF_CGROUP_RUN_PROG_SOCK_OPS_SK(&sock_ops, sk);

	अगर (err || sock_ops.reमुख्यing_opt_len == *reमुख्यing)
		वापस;

	opts->bpf_opt_len = *reमुख्यing - sock_ops.reमुख्यing_opt_len;
	/* round up to 4 bytes */
	opts->bpf_opt_len = (opts->bpf_opt_len + 3) & ~3;

	*reमुख्यing -= opts->bpf_opt_len;
पूर्ण

अटल व्योम bpf_skops_ग_लिखो_hdr_opt(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				    काष्ठा request_sock *req,
				    काष्ठा sk_buff *syn_skb,
				    क्रमागत tcp_synack_type synack_type,
				    काष्ठा tcp_out_options *opts)
अणु
	u8 first_opt_off, nr_written, max_opt_len = opts->bpf_opt_len;
	काष्ठा bpf_sock_ops_kern sock_ops;
	पूर्णांक err;

	अगर (likely(!max_opt_len))
		वापस;

	स_रखो(&sock_ops, 0, दुरत्व(काष्ठा bpf_sock_ops_kern, temp));

	sock_ops.op = BPF_SOCK_OPS_WRITE_HDR_OPT_CB;

	अगर (req) अणु
		sock_ops.sk = (काष्ठा sock *)req;
		sock_ops.syn_skb = syn_skb;
	पूर्ण अन्यथा अणु
		sock_owned_by_me(sk);

		sock_ops.is_fullsock = 1;
		sock_ops.sk = sk;
	पूर्ण

	sock_ops.args[0] = bpf_skops_ग_लिखो_hdr_opt_arg0(skb, synack_type);
	sock_ops.reमुख्यing_opt_len = max_opt_len;
	first_opt_off = tcp_hdrlen(skb) - max_opt_len;
	bpf_skops_init_skb(&sock_ops, skb, first_opt_off);

	err = BPF_CGROUP_RUN_PROG_SOCK_OPS_SK(&sock_ops, sk);

	अगर (err)
		nr_written = 0;
	अन्यथा
		nr_written = max_opt_len - sock_ops.reमुख्यing_opt_len;

	अगर (nr_written < max_opt_len)
		स_रखो(skb->data + first_opt_off + nr_written, TCPOPT_NOP,
		       max_opt_len - nr_written);
पूर्ण
#अन्यथा
अटल व्योम bpf_skops_hdr_opt_len(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				  काष्ठा request_sock *req,
				  काष्ठा sk_buff *syn_skb,
				  क्रमागत tcp_synack_type synack_type,
				  काष्ठा tcp_out_options *opts,
				  अचिन्हित पूर्णांक *reमुख्यing)
अणु
पूर्ण

अटल व्योम bpf_skops_ग_लिखो_hdr_opt(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				    काष्ठा request_sock *req,
				    काष्ठा sk_buff *syn_skb,
				    क्रमागत tcp_synack_type synack_type,
				    काष्ठा tcp_out_options *opts)
अणु
पूर्ण
#पूर्ण_अगर

/* Write previously computed TCP options to the packet.
 *
 * Beware: Something in the Internet is very sensitive to the ordering of
 * TCP options, we learned this through the hard way, so be careful here.
 * Luckily we can at least blame others क्रम their non-compliance but from
 * पूर्णांकer-operability perspective it seems that we're somewhat stuck with
 * the ordering which we have been using अगर we want to keep working with
 * those broken things (not that it currently hurts anybody as there isn't
 * particular reason why the ordering would need to be changed).
 *
 * At least SACK_PERM as the first option is known to lead to a disaster
 * (but it may well be that other scenarios fail similarly).
 */
अटल व्योम tcp_options_ग_लिखो(__be32 *ptr, काष्ठा tcp_sock *tp,
			      काष्ठा tcp_out_options *opts)
अणु
	u16 options = opts->options;	/* mungable copy */

	अगर (unlikely(OPTION_MD5 & options)) अणु
		*ptr++ = htonl((TCPOPT_NOP << 24) | (TCPOPT_NOP << 16) |
			       (TCPOPT_MD5SIG << 8) | TCPOLEN_MD5SIG);
		/* overload cookie hash location */
		opts->hash_location = (__u8 *)ptr;
		ptr += 4;
	पूर्ण

	अगर (unlikely(opts->mss)) अणु
		*ptr++ = htonl((TCPOPT_MSS << 24) |
			       (TCPOLEN_MSS << 16) |
			       opts->mss);
	पूर्ण

	अगर (likely(OPTION_TS & options)) अणु
		अगर (unlikely(OPTION_SACK_ADVERTISE & options)) अणु
			*ptr++ = htonl((TCPOPT_SACK_PERM << 24) |
				       (TCPOLEN_SACK_PERM << 16) |
				       (TCPOPT_TIMESTAMP << 8) |
				       TCPOLEN_TIMESTAMP);
			options &= ~OPTION_SACK_ADVERTISE;
		पूर्ण अन्यथा अणु
			*ptr++ = htonl((TCPOPT_NOP << 24) |
				       (TCPOPT_NOP << 16) |
				       (TCPOPT_TIMESTAMP << 8) |
				       TCPOLEN_TIMESTAMP);
		पूर्ण
		*ptr++ = htonl(opts->tsval);
		*ptr++ = htonl(opts->tsecr);
	पूर्ण

	अगर (unlikely(OPTION_SACK_ADVERTISE & options)) अणु
		*ptr++ = htonl((TCPOPT_NOP << 24) |
			       (TCPOPT_NOP << 16) |
			       (TCPOPT_SACK_PERM << 8) |
			       TCPOLEN_SACK_PERM);
	पूर्ण

	अगर (unlikely(OPTION_WSCALE & options)) अणु
		*ptr++ = htonl((TCPOPT_NOP << 24) |
			       (TCPOPT_WINDOW << 16) |
			       (TCPOLEN_WINDOW << 8) |
			       opts->ws);
	पूर्ण

	अगर (unlikely(opts->num_sack_blocks)) अणु
		काष्ठा tcp_sack_block *sp = tp->rx_opt.dsack ?
			tp->duplicate_sack : tp->selective_acks;
		पूर्णांक this_sack;

		*ptr++ = htonl((TCPOPT_NOP  << 24) |
			       (TCPOPT_NOP  << 16) |
			       (TCPOPT_SACK <<  8) |
			       (TCPOLEN_SACK_BASE + (opts->num_sack_blocks *
						     TCPOLEN_SACK_PERBLOCK)));

		क्रम (this_sack = 0; this_sack < opts->num_sack_blocks;
		     ++this_sack) अणु
			*ptr++ = htonl(sp[this_sack].start_seq);
			*ptr++ = htonl(sp[this_sack].end_seq);
		पूर्ण

		tp->rx_opt.dsack = 0;
	पूर्ण

	अगर (unlikely(OPTION_FAST_OPEN_COOKIE & options)) अणु
		काष्ठा tcp_fastखोलो_cookie *foc = opts->fastखोलो_cookie;
		u8 *p = (u8 *)ptr;
		u32 len; /* Fast Open option length */

		अगर (foc->exp) अणु
			len = TCPOLEN_EXP_FASTOPEN_BASE + foc->len;
			*ptr = htonl((TCPOPT_EXP << 24) | (len << 16) |
				     TCPOPT_FASTOPEN_MAGIC);
			p += TCPOLEN_EXP_FASTOPEN_BASE;
		पूर्ण अन्यथा अणु
			len = TCPOLEN_FASTOPEN_BASE + foc->len;
			*p++ = TCPOPT_FASTOPEN;
			*p++ = len;
		पूर्ण

		स_नकल(p, foc->val, foc->len);
		अगर ((len & 3) == 2) अणु
			p[foc->len] = TCPOPT_NOP;
			p[foc->len + 1] = TCPOPT_NOP;
		पूर्ण
		ptr += (len + 3) >> 2;
	पूर्ण

	smc_options_ग_लिखो(ptr, &options);

	mptcp_options_ग_लिखो(ptr, tp, opts);
पूर्ण

अटल व्योम smc_set_option(स्थिर काष्ठा tcp_sock *tp,
			   काष्ठा tcp_out_options *opts,
			   अचिन्हित पूर्णांक *reमुख्यing)
अणु
#अगर IS_ENABLED(CONFIG_SMC)
	अगर (अटल_branch_unlikely(&tcp_have_smc)) अणु
		अगर (tp->syn_smc) अणु
			अगर (*reमुख्यing >= TCPOLEN_EXP_SMC_BASE_ALIGNED) अणु
				opts->options |= OPTION_SMC;
				*reमुख्यing -= TCPOLEN_EXP_SMC_BASE_ALIGNED;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम smc_set_option_cond(स्थिर काष्ठा tcp_sock *tp,
				स्थिर काष्ठा inet_request_sock *ireq,
				काष्ठा tcp_out_options *opts,
				अचिन्हित पूर्णांक *reमुख्यing)
अणु
#अगर IS_ENABLED(CONFIG_SMC)
	अगर (अटल_branch_unlikely(&tcp_have_smc)) अणु
		अगर (tp->syn_smc && ireq->smc_ok) अणु
			अगर (*reमुख्यing >= TCPOLEN_EXP_SMC_BASE_ALIGNED) अणु
				opts->options |= OPTION_SMC;
				*reमुख्यing -= TCPOLEN_EXP_SMC_BASE_ALIGNED;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम mptcp_set_option_cond(स्थिर काष्ठा request_sock *req,
				  काष्ठा tcp_out_options *opts,
				  अचिन्हित पूर्णांक *reमुख्यing)
अणु
	अगर (rsk_is_mptcp(req)) अणु
		अचिन्हित पूर्णांक size;

		अगर (mptcp_synack_options(req, &size, &opts->mptcp)) अणु
			अगर (*reमुख्यing >= size) अणु
				opts->options |= OPTION_MPTCP;
				*reमुख्यing -= size;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* Compute TCP options क्रम SYN packets. This is not the final
 * network wire क्रमmat yet.
 */
अटल अचिन्हित पूर्णांक tcp_syn_options(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				काष्ठा tcp_out_options *opts,
				काष्ठा tcp_md5sig_key **md5)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	अचिन्हित पूर्णांक reमुख्यing = MAX_TCP_OPTION_SPACE;
	काष्ठा tcp_fastखोलो_request *fastखोलो = tp->fastखोलो_req;

	*md5 = शून्य;
#अगर_घोषित CONFIG_TCP_MD5SIG
	अगर (अटल_branch_unlikely(&tcp_md5_needed) &&
	    rcu_access_poपूर्णांकer(tp->md5sig_info)) अणु
		*md5 = tp->af_specअगरic->md5_lookup(sk, sk);
		अगर (*md5) अणु
			opts->options |= OPTION_MD5;
			reमुख्यing -= TCPOLEN_MD5SIG_ALIGNED;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* We always get an MSS option.  The option bytes which will be seen in
	 * normal data packets should बारtamps be used, must be in the MSS
	 * advertised.  But we subtract them from tp->mss_cache so that
	 * calculations in tcp_sendmsg are simpler etc.  So account क्रम this
	 * fact here अगर necessary.  If we करोn't करो this correctly, as a
	 * receiver we won't recognize data packets as being full sized when we
	 * should, and thus we won't abide by the delayed ACK rules correctly.
	 * SACKs करोn't matter, we never delay an ACK when we have any of those
	 * going out.  */
	opts->mss = tcp_advertise_mss(sk);
	reमुख्यing -= TCPOLEN_MSS_ALIGNED;

	अगर (likely(sock_net(sk)->ipv4.sysctl_tcp_बारtamps && !*md5)) अणु
		opts->options |= OPTION_TS;
		opts->tsval = tcp_skb_बारtamp(skb) + tp->tsoffset;
		opts->tsecr = tp->rx_opt.ts_recent;
		reमुख्यing -= TCPOLEN_TSTAMP_ALIGNED;
	पूर्ण
	अगर (likely(sock_net(sk)->ipv4.sysctl_tcp_winकरोw_scaling)) अणु
		opts->ws = tp->rx_opt.rcv_wscale;
		opts->options |= OPTION_WSCALE;
		reमुख्यing -= TCPOLEN_WSCALE_ALIGNED;
	पूर्ण
	अगर (likely(sock_net(sk)->ipv4.sysctl_tcp_sack)) अणु
		opts->options |= OPTION_SACK_ADVERTISE;
		अगर (unlikely(!(OPTION_TS & opts->options)))
			reमुख्यing -= TCPOLEN_SACKPERM_ALIGNED;
	पूर्ण

	अगर (fastखोलो && fastखोलो->cookie.len >= 0) अणु
		u32 need = fastखोलो->cookie.len;

		need += fastखोलो->cookie.exp ? TCPOLEN_EXP_FASTOPEN_BASE :
					       TCPOLEN_FASTOPEN_BASE;
		need = (need + 3) & ~3U;  /* Align to 32 bits */
		अगर (reमुख्यing >= need) अणु
			opts->options |= OPTION_FAST_OPEN_COOKIE;
			opts->fastखोलो_cookie = &fastखोलो->cookie;
			reमुख्यing -= need;
			tp->syn_fastखोलो = 1;
			tp->syn_fastखोलो_exp = fastखोलो->cookie.exp ? 1 : 0;
		पूर्ण
	पूर्ण

	smc_set_option(tp, opts, &reमुख्यing);

	अगर (sk_is_mptcp(sk)) अणु
		अचिन्हित पूर्णांक size;

		अगर (mptcp_syn_options(sk, skb, &size, &opts->mptcp)) अणु
			opts->options |= OPTION_MPTCP;
			reमुख्यing -= size;
		पूर्ण
	पूर्ण

	bpf_skops_hdr_opt_len(sk, skb, शून्य, शून्य, 0, opts, &reमुख्यing);

	वापस MAX_TCP_OPTION_SPACE - reमुख्यing;
पूर्ण

/* Set up TCP options क्रम SYN-ACKs. */
अटल अचिन्हित पूर्णांक tcp_synack_options(स्थिर काष्ठा sock *sk,
				       काष्ठा request_sock *req,
				       अचिन्हित पूर्णांक mss, काष्ठा sk_buff *skb,
				       काष्ठा tcp_out_options *opts,
				       स्थिर काष्ठा tcp_md5sig_key *md5,
				       काष्ठा tcp_fastखोलो_cookie *foc,
				       क्रमागत tcp_synack_type synack_type,
				       काष्ठा sk_buff *syn_skb)
अणु
	काष्ठा inet_request_sock *ireq = inet_rsk(req);
	अचिन्हित पूर्णांक reमुख्यing = MAX_TCP_OPTION_SPACE;

#अगर_घोषित CONFIG_TCP_MD5SIG
	अगर (md5) अणु
		opts->options |= OPTION_MD5;
		reमुख्यing -= TCPOLEN_MD5SIG_ALIGNED;

		/* We can't fit any SACK blocks in a packet with MD5 + TS
		 * options. There was discussion about disabling SACK
		 * rather than TS in order to fit in better with old,
		 * buggy kernels, but that was deemed to be unnecessary.
		 */
		अगर (synack_type != TCP_SYNACK_COOKIE)
			ireq->tstamp_ok &= !ireq->sack_ok;
	पूर्ण
#पूर्ण_अगर

	/* We always send an MSS option. */
	opts->mss = mss;
	reमुख्यing -= TCPOLEN_MSS_ALIGNED;

	अगर (likely(ireq->wscale_ok)) अणु
		opts->ws = ireq->rcv_wscale;
		opts->options |= OPTION_WSCALE;
		reमुख्यing -= TCPOLEN_WSCALE_ALIGNED;
	पूर्ण
	अगर (likely(ireq->tstamp_ok)) अणु
		opts->options |= OPTION_TS;
		opts->tsval = tcp_skb_बारtamp(skb) + tcp_rsk(req)->ts_off;
		opts->tsecr = req->ts_recent;
		reमुख्यing -= TCPOLEN_TSTAMP_ALIGNED;
	पूर्ण
	अगर (likely(ireq->sack_ok)) अणु
		opts->options |= OPTION_SACK_ADVERTISE;
		अगर (unlikely(!ireq->tstamp_ok))
			reमुख्यing -= TCPOLEN_SACKPERM_ALIGNED;
	पूर्ण
	अगर (foc != शून्य && foc->len >= 0) अणु
		u32 need = foc->len;

		need += foc->exp ? TCPOLEN_EXP_FASTOPEN_BASE :
				   TCPOLEN_FASTOPEN_BASE;
		need = (need + 3) & ~3U;  /* Align to 32 bits */
		अगर (reमुख्यing >= need) अणु
			opts->options |= OPTION_FAST_OPEN_COOKIE;
			opts->fastखोलो_cookie = foc;
			reमुख्यing -= need;
		पूर्ण
	पूर्ण

	mptcp_set_option_cond(req, opts, &reमुख्यing);

	smc_set_option_cond(tcp_sk(sk), ireq, opts, &reमुख्यing);

	bpf_skops_hdr_opt_len((काष्ठा sock *)sk, skb, req, syn_skb,
			      synack_type, opts, &reमुख्यing);

	वापस MAX_TCP_OPTION_SPACE - reमुख्यing;
पूर्ण

/* Compute TCP options क्रम ESTABLISHED sockets. This is not the
 * final wire क्रमmat yet.
 */
अटल अचिन्हित पूर्णांक tcp_established_options(काष्ठा sock *sk, काष्ठा sk_buff *skb,
					काष्ठा tcp_out_options *opts,
					काष्ठा tcp_md5sig_key **md5)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	अचिन्हित पूर्णांक size = 0;
	अचिन्हित पूर्णांक eff_sacks;

	opts->options = 0;

	*md5 = शून्य;
#अगर_घोषित CONFIG_TCP_MD5SIG
	अगर (अटल_branch_unlikely(&tcp_md5_needed) &&
	    rcu_access_poपूर्णांकer(tp->md5sig_info)) अणु
		*md5 = tp->af_specअगरic->md5_lookup(sk, sk);
		अगर (*md5) अणु
			opts->options |= OPTION_MD5;
			size += TCPOLEN_MD5SIG_ALIGNED;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (likely(tp->rx_opt.tstamp_ok)) अणु
		opts->options |= OPTION_TS;
		opts->tsval = skb ? tcp_skb_बारtamp(skb) + tp->tsoffset : 0;
		opts->tsecr = tp->rx_opt.ts_recent;
		size += TCPOLEN_TSTAMP_ALIGNED;
	पूर्ण

	/* MPTCP options have precedence over SACK क्रम the limited TCP
	 * option space because a MPTCP connection would be क्रमced to
	 * fall back to regular TCP अगर a required multipath option is
	 * missing. SACK still माला_लो a chance to use whatever space is
	 * left.
	 */
	अगर (sk_is_mptcp(sk)) अणु
		अचिन्हित पूर्णांक reमुख्यing = MAX_TCP_OPTION_SPACE - size;
		अचिन्हित पूर्णांक opt_size = 0;

		अगर (mptcp_established_options(sk, skb, &opt_size, reमुख्यing,
					      &opts->mptcp)) अणु
			opts->options |= OPTION_MPTCP;
			size += opt_size;
		पूर्ण
	पूर्ण

	eff_sacks = tp->rx_opt.num_sacks + tp->rx_opt.dsack;
	अगर (unlikely(eff_sacks)) अणु
		स्थिर अचिन्हित पूर्णांक reमुख्यing = MAX_TCP_OPTION_SPACE - size;
		अगर (unlikely(reमुख्यing < TCPOLEN_SACK_BASE_ALIGNED +
					 TCPOLEN_SACK_PERBLOCK))
			वापस size;

		opts->num_sack_blocks =
			min_t(अचिन्हित पूर्णांक, eff_sacks,
			      (reमुख्यing - TCPOLEN_SACK_BASE_ALIGNED) /
			      TCPOLEN_SACK_PERBLOCK);

		size += TCPOLEN_SACK_BASE_ALIGNED +
			opts->num_sack_blocks * TCPOLEN_SACK_PERBLOCK;
	पूर्ण

	अगर (unlikely(BPF_SOCK_OPS_TEST_FLAG(tp,
					    BPF_SOCK_OPS_WRITE_HDR_OPT_CB_FLAG))) अणु
		अचिन्हित पूर्णांक reमुख्यing = MAX_TCP_OPTION_SPACE - size;

		bpf_skops_hdr_opt_len(sk, skb, शून्य, शून्य, 0, opts, &reमुख्यing);

		size = MAX_TCP_OPTION_SPACE - reमुख्यing;
	पूर्ण

	वापस size;
पूर्ण


/* TCP SMALL QUEUES (TSQ)
 *
 * TSQ goal is to keep small amount of skbs per tcp flow in tx queues (qdisc+dev)
 * to reduce RTT and bufferbloat.
 * We करो this using a special skb deकाष्ठाor (tcp_wमुक्त).
 *
 * Its important tcp_wमुक्त() can be replaced by sock_wमुक्त() in the event skb
 * needs to be पुनः_स्मृतिated in a driver.
 * The invariant being skb->truesize subtracted from sk->sk_wmem_alloc
 *
 * Since transmit from skb deकाष्ठाor is क्रमbidden, we use a tasklet
 * to process all sockets that eventually need to send more skbs.
 * We use one tasklet per cpu, with its own queue of sockets.
 */
काष्ठा tsq_tasklet अणु
	काष्ठा tasklet_काष्ठा	tasklet;
	काष्ठा list_head	head; /* queue of tcp sockets */
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा tsq_tasklet, tsq_tasklet);

अटल व्योम tcp_tsq_ग_लिखो(काष्ठा sock *sk)
अणु
	अगर ((1 << sk->sk_state) &
	    (TCPF_ESTABLISHED | TCPF_FIN_WAIT1 | TCPF_CLOSING |
	     TCPF_CLOSE_WAIT  | TCPF_LAST_ACK)) अणु
		काष्ठा tcp_sock *tp = tcp_sk(sk);

		अगर (tp->lost_out > tp->retrans_out &&
		    tp->snd_cwnd > tcp_packets_in_flight(tp)) अणु
			tcp_mstamp_refresh(tp);
			tcp_xmit_retransmit_queue(sk);
		पूर्ण

		tcp_ग_लिखो_xmit(sk, tcp_current_mss(sk), tp->nonagle,
			       0, GFP_ATOMIC);
	पूर्ण
पूर्ण

अटल व्योम tcp_tsq_handler(काष्ठा sock *sk)
अणु
	bh_lock_sock(sk);
	अगर (!sock_owned_by_user(sk))
		tcp_tsq_ग_लिखो(sk);
	अन्यथा अगर (!test_and_set_bit(TCP_TSQ_DEFERRED, &sk->sk_tsq_flags))
		sock_hold(sk);
	bh_unlock_sock(sk);
पूर्ण
/*
 * One tasklet per cpu tries to send more skbs.
 * We run in tasklet context but need to disable irqs when
 * transferring tsq->head because tcp_wमुक्त() might
 * पूर्णांकerrupt us (non NAPI drivers)
 */
अटल व्योम tcp_tasklet_func(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा tsq_tasklet *tsq = from_tasklet(tsq,  t, tasklet);
	LIST_HEAD(list);
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *q, *n;
	काष्ठा tcp_sock *tp;
	काष्ठा sock *sk;

	local_irq_save(flags);
	list_splice_init(&tsq->head, &list);
	local_irq_restore(flags);

	list_क्रम_each_safe(q, n, &list) अणु
		tp = list_entry(q, काष्ठा tcp_sock, tsq_node);
		list_del(&tp->tsq_node);

		sk = (काष्ठा sock *)tp;
		smp_mb__beक्रमe_atomic();
		clear_bit(TSQ_QUEUED, &sk->sk_tsq_flags);

		tcp_tsq_handler(sk);
		sk_मुक्त(sk);
	पूर्ण
पूर्ण

#घोषणा TCP_DEFERRED_ALL (TCPF_TSQ_DEFERRED |		\
			  TCPF_WRITE_TIMER_DEFERRED |	\
			  TCPF_DELACK_TIMER_DEFERRED |	\
			  TCPF_MTU_REDUCED_DEFERRED)
/**
 * tcp_release_cb - tcp release_sock() callback
 * @sk: socket
 *
 * called from release_sock() to perक्रमm protocol dependent
 * actions beक्रमe socket release.
 */
व्योम tcp_release_cb(काष्ठा sock *sk)
अणु
	अचिन्हित दीर्घ flags, nflags;

	/* perक्रमm an atomic operation only अगर at least one flag is set */
	करो अणु
		flags = sk->sk_tsq_flags;
		अगर (!(flags & TCP_DEFERRED_ALL))
			वापस;
		nflags = flags & ~TCP_DEFERRED_ALL;
	पूर्ण जबतक (cmpxchg(&sk->sk_tsq_flags, flags, nflags) != flags);

	अगर (flags & TCPF_TSQ_DEFERRED) अणु
		tcp_tsq_ग_लिखो(sk);
		__sock_put(sk);
	पूर्ण
	/* Here begins the tricky part :
	 * We are called from release_sock() with :
	 * 1) BH disabled
	 * 2) sk_lock.slock spinlock held
	 * 3) socket owned by us (sk->sk_lock.owned == 1)
	 *
	 * But following code is meant to be called from BH handlers,
	 * so we should keep BH disabled, but early release socket ownership
	 */
	sock_release_ownership(sk);

	अगर (flags & TCPF_WRITE_TIMER_DEFERRED) अणु
		tcp_ग_लिखो_समयr_handler(sk);
		__sock_put(sk);
	पूर्ण
	अगर (flags & TCPF_DELACK_TIMER_DEFERRED) अणु
		tcp_delack_समयr_handler(sk);
		__sock_put(sk);
	पूर्ण
	अगर (flags & TCPF_MTU_REDUCED_DEFERRED) अणु
		inet_csk(sk)->icsk_af_ops->mtu_reduced(sk);
		__sock_put(sk);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(tcp_release_cb);

व्योम __init tcp_tasklet_init(व्योम)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा tsq_tasklet *tsq = &per_cpu(tsq_tasklet, i);

		INIT_LIST_HEAD(&tsq->head);
		tasklet_setup(&tsq->tasklet, tcp_tasklet_func);
	पूर्ण
पूर्ण

/*
 * Write buffer deकाष्ठाor स्वतःmatically called from kमुक्त_skb.
 * We can't xmit new skbs from this context, as we might alपढ़ोy
 * hold qdisc lock.
 */
व्योम tcp_wमुक्त(काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = skb->sk;
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	अचिन्हित दीर्घ flags, nval, oval;

	/* Keep one reference on sk_wmem_alloc.
	 * Will be released by sk_मुक्त() from here or tcp_tasklet_func()
	 */
	WARN_ON(refcount_sub_and_test(skb->truesize - 1, &sk->sk_wmem_alloc));

	/* If this softirq is serviced by ksoftirqd, we are likely under stress.
	 * Wait until our queues (qdisc + devices) are drained.
	 * This gives :
	 * - less callbacks to tcp_ग_लिखो_xmit(), reducing stress (batches)
	 * - chance क्रम incoming ACK (processed by another cpu maybe)
	 *   to migrate this flow (skb->ooo_okay will be eventually set)
	 */
	अगर (refcount_पढ़ो(&sk->sk_wmem_alloc) >= SKB_TRUESIZE(1) && this_cpu_ksoftirqd() == current)
		जाओ out;

	क्रम (oval = READ_ONCE(sk->sk_tsq_flags);; oval = nval) अणु
		काष्ठा tsq_tasklet *tsq;
		bool empty;

		अगर (!(oval & TSQF_THROTTLED) || (oval & TSQF_QUEUED))
			जाओ out;

		nval = (oval & ~TSQF_THROTTLED) | TSQF_QUEUED;
		nval = cmpxchg(&sk->sk_tsq_flags, oval, nval);
		अगर (nval != oval)
			जारी;

		/* queue this socket to tasklet queue */
		local_irq_save(flags);
		tsq = this_cpu_ptr(&tsq_tasklet);
		empty = list_empty(&tsq->head);
		list_add(&tp->tsq_node, &tsq->head);
		अगर (empty)
			tasklet_schedule(&tsq->tasklet);
		local_irq_restore(flags);
		वापस;
	पूर्ण
out:
	sk_मुक्त(sk);
पूर्ण

/* Note: Called under soft irq.
 * We can call TCP stack right away, unless socket is owned by user.
 */
क्रमागत hrसमयr_restart tcp_pace_kick(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा tcp_sock *tp = container_of(समयr, काष्ठा tcp_sock, pacing_समयr);
	काष्ठा sock *sk = (काष्ठा sock *)tp;

	tcp_tsq_handler(sk);
	sock_put(sk);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल व्योम tcp_update_skb_after_send(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				      u64 prior_wstamp)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (sk->sk_pacing_status != SK_PACING_NONE) अणु
		अचिन्हित दीर्घ rate = sk->sk_pacing_rate;

		/* Original sch_fq करोes not pace first 10 MSS
		 * Note that tp->data_segs_out overflows after 2^32 packets,
		 * this is a minor annoyance.
		 */
		अगर (rate != ~0UL && rate && tp->data_segs_out >= 10) अणु
			u64 len_ns = भाग64_ul((u64)skb->len * NSEC_PER_SEC, rate);
			u64 credit = tp->tcp_wstamp_ns - prior_wstamp;

			/* take पूर्णांकo account OS jitter */
			len_ns -= min_t(u64, len_ns / 2, credit);
			tp->tcp_wstamp_ns += len_ns;
		पूर्ण
	पूर्ण
	list_move_tail(&skb->tcp_tsorted_anchor, &tp->tsorted_sent_queue);
पूर्ण

INसूचीECT_CALLABLE_DECLARE(पूर्णांक ip_queue_xmit(काष्ठा sock *sk, काष्ठा sk_buff *skb, काष्ठा flowi *fl));
INसूचीECT_CALLABLE_DECLARE(पूर्णांक inet6_csk_xmit(काष्ठा sock *sk, काष्ठा sk_buff *skb, काष्ठा flowi *fl));
INसूचीECT_CALLABLE_DECLARE(व्योम tcp_v4_send_check(काष्ठा sock *sk, काष्ठा sk_buff *skb));

/* This routine actually transmits TCP packets queued in by
 * tcp_करो_sendmsg().  This is used by both the initial
 * transmission and possible later retransmissions.
 * All SKB's seen here are completely headerless.  It is our
 * job to build the TCP header, and pass the packet करोwn to
 * IP so it can करो the same plus pass the packet off to the
 * device.
 *
 * We are working here with either a clone of the original
 * SKB, or a fresh unique copy made by the retransmit engine.
 */
अटल पूर्णांक __tcp_transmit_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			      पूर्णांक clone_it, gfp_t gfp_mask, u32 rcv_nxt)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा inet_sock *inet;
	काष्ठा tcp_sock *tp;
	काष्ठा tcp_skb_cb *tcb;
	काष्ठा tcp_out_options opts;
	अचिन्हित पूर्णांक tcp_options_size, tcp_header_size;
	काष्ठा sk_buff *oskb = शून्य;
	काष्ठा tcp_md5sig_key *md5;
	काष्ठा tcphdr *th;
	u64 prior_wstamp;
	पूर्णांक err;

	BUG_ON(!skb || !tcp_skb_pcount(skb));
	tp = tcp_sk(sk);
	prior_wstamp = tp->tcp_wstamp_ns;
	tp->tcp_wstamp_ns = max(tp->tcp_wstamp_ns, tp->tcp_घड़ी_cache);
	skb->skb_mstamp_ns = tp->tcp_wstamp_ns;
	अगर (clone_it) अणु
		TCP_SKB_CB(skb)->tx.in_flight = TCP_SKB_CB(skb)->end_seq
			- tp->snd_una;
		oskb = skb;

		tcp_skb_tsorted_save(oskb) अणु
			अगर (unlikely(skb_cloned(oskb)))
				skb = pskb_copy(oskb, gfp_mask);
			अन्यथा
				skb = skb_clone(oskb, gfp_mask);
		पूर्ण tcp_skb_tsorted_restore(oskb);

		अगर (unlikely(!skb))
			वापस -ENOBUFS;
		/* retransmit skbs might have a non zero value in skb->dev
		 * because skb->dev is aliased with skb->rbnode.rb_left
		 */
		skb->dev = शून्य;
	पूर्ण

	inet = inet_sk(sk);
	tcb = TCP_SKB_CB(skb);
	स_रखो(&opts, 0, माप(opts));

	अगर (unlikely(tcb->tcp_flags & TCPHDR_SYN)) अणु
		tcp_options_size = tcp_syn_options(sk, skb, &opts, &md5);
	पूर्ण अन्यथा अणु
		tcp_options_size = tcp_established_options(sk, skb, &opts,
							   &md5);
		/* Force a PSH flag on all (GSO) packets to expedite GRO flush
		 * at receiver : This slightly improve GRO perक्रमmance.
		 * Note that we करो not क्रमce the PSH flag क्रम non GSO packets,
		 * because they might be sent under high congestion events,
		 * and in this हाल it is better to delay the delivery of 1-MSS
		 * packets and thus the corresponding ACK packet that would
		 * release the following packet.
		 */
		अगर (tcp_skb_pcount(skb) > 1)
			tcb->tcp_flags |= TCPHDR_PSH;
	पूर्ण
	tcp_header_size = tcp_options_size + माप(काष्ठा tcphdr);

	/* अगर no packet is in qdisc/device queue, then allow XPS to select
	 * another queue. We can be called from tcp_tsq_handler()
	 * which holds one reference to sk.
	 *
	 * TODO: Ideally, in-flight pure ACK packets should not matter here.
	 * One way to get this would be to set skb->truesize = 2 on them.
	 */
	skb->ooo_okay = sk_wmem_alloc_get(sk) < SKB_TRUESIZE(1);

	/* If we had to use memory reserve to allocate this skb,
	 * this might cause drops अगर packet is looped back :
	 * Other socket might not have SOCK_MEMALLOC.
	 * Packets not looped back करो not care about pfmeदो_स्मृति.
	 */
	skb->pfmeदो_स्मृति = 0;

	skb_push(skb, tcp_header_size);
	skb_reset_transport_header(skb);

	skb_orphan(skb);
	skb->sk = sk;
	skb->deकाष्ठाor = skb_is_tcp_pure_ack(skb) ? __sock_wमुक्त : tcp_wमुक्त;
	refcount_add(skb->truesize, &sk->sk_wmem_alloc);

	skb_set_dst_pending_confirm(skb, sk->sk_dst_pending_confirm);

	/* Build TCP header and checksum it. */
	th = (काष्ठा tcphdr *)skb->data;
	th->source		= inet->inet_sport;
	th->dest		= inet->inet_dport;
	th->seq			= htonl(tcb->seq);
	th->ack_seq		= htonl(rcv_nxt);
	*(((__be16 *)th) + 6)	= htons(((tcp_header_size >> 2) << 12) |
					tcb->tcp_flags);

	th->check		= 0;
	th->urg_ptr		= 0;

	/* The urg_mode check is necessary during a below snd_una win probe */
	अगर (unlikely(tcp_urg_mode(tp) && beक्रमe(tcb->seq, tp->snd_up))) अणु
		अगर (beक्रमe(tp->snd_up, tcb->seq + 0x10000)) अणु
			th->urg_ptr = htons(tp->snd_up - tcb->seq);
			th->urg = 1;
		पूर्ण अन्यथा अगर (after(tcb->seq + 0xFFFF, tp->snd_nxt)) अणु
			th->urg_ptr = htons(0xFFFF);
			th->urg = 1;
		पूर्ण
	पूर्ण

	skb_shinfo(skb)->gso_type = sk->sk_gso_type;
	अगर (likely(!(tcb->tcp_flags & TCPHDR_SYN))) अणु
		th->winकरोw      = htons(tcp_select_winकरोw(sk));
		tcp_ecn_send(sk, skb, th, tcp_header_size);
	पूर्ण अन्यथा अणु
		/* RFC1323: The winकरोw in SYN & SYN/ACK segments
		 * is never scaled.
		 */
		th->winकरोw	= htons(min(tp->rcv_wnd, 65535U));
	पूर्ण

	tcp_options_ग_लिखो((__be32 *)(th + 1), tp, &opts);

#अगर_घोषित CONFIG_TCP_MD5SIG
	/* Calculate the MD5 hash, as we have all we need now */
	अगर (md5) अणु
		sk_nocaps_add(sk, NETIF_F_GSO_MASK);
		tp->af_specअगरic->calc_md5_hash(opts.hash_location,
					       md5, sk, skb);
	पूर्ण
#पूर्ण_अगर

	/* BPF prog is the last one writing header option */
	bpf_skops_ग_लिखो_hdr_opt(sk, skb, शून्य, शून्य, 0, &opts);

	INसूचीECT_CALL_INET(icsk->icsk_af_ops->send_check,
			   tcp_v6_send_check, tcp_v4_send_check,
			   sk, skb);

	अगर (likely(tcb->tcp_flags & TCPHDR_ACK))
		tcp_event_ack_sent(sk, tcp_skb_pcount(skb), rcv_nxt);

	अगर (skb->len != tcp_header_size) अणु
		tcp_event_data_sent(tp, sk);
		tp->data_segs_out += tcp_skb_pcount(skb);
		tp->bytes_sent += skb->len - tcp_header_size;
	पूर्ण

	अगर (after(tcb->end_seq, tp->snd_nxt) || tcb->seq == tcb->end_seq)
		TCP_ADD_STATS(sock_net(sk), TCP_MIB_OUTSEGS,
			      tcp_skb_pcount(skb));

	tp->segs_out += tcp_skb_pcount(skb);
	skb_set_hash_from_sk(skb, sk);
	/* OK, its समय to fill skb_shinfo(skb)->gso_अणुsegs|sizeपूर्ण */
	skb_shinfo(skb)->gso_segs = tcp_skb_pcount(skb);
	skb_shinfo(skb)->gso_size = tcp_skb_mss(skb);

	/* Leave earliest departure समय in skb->tstamp (skb->skb_mstamp_ns) */

	/* Cleanup our debris क्रम IP stacks */
	स_रखो(skb->cb, 0, max(माप(काष्ठा inet_skb_parm),
			       माप(काष्ठा inet6_skb_parm)));

	tcp_add_tx_delay(skb, tp);

	err = INसूचीECT_CALL_INET(icsk->icsk_af_ops->queue_xmit,
				 inet6_csk_xmit, ip_queue_xmit,
				 sk, skb, &inet->cork.fl);

	अगर (unlikely(err > 0)) अणु
		tcp_enter_cwr(sk);
		err = net_xmit_eval(err);
	पूर्ण
	अगर (!err && oskb) अणु
		tcp_update_skb_after_send(sk, oskb, prior_wstamp);
		tcp_rate_skb_sent(sk, oskb);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक tcp_transmit_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक clone_it,
			    gfp_t gfp_mask)
अणु
	वापस __tcp_transmit_skb(sk, skb, clone_it, gfp_mask,
				  tcp_sk(sk)->rcv_nxt);
पूर्ण

/* This routine just queues the buffer क्रम sending.
 *
 * NOTE: probe0 समयr is not checked, करो not क्रमget tcp_push_pending_frames,
 * otherwise socket can stall.
 */
अटल व्योम tcp_queue_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	/* Advance ग_लिखो_seq and place onto the ग_लिखो_queue. */
	WRITE_ONCE(tp->ग_लिखो_seq, TCP_SKB_CB(skb)->end_seq);
	__skb_header_release(skb);
	tcp_add_ग_लिखो_queue_tail(sk, skb);
	sk_wmem_queued_add(sk, skb->truesize);
	sk_mem_अक्षरge(sk, skb->truesize);
पूर्ण

/* Initialize TSO segments क्रम a packet. */
अटल व्योम tcp_set_skb_tso_segs(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक mss_now)
अणु
	अगर (skb->len <= mss_now) अणु
		/* Aव्योम the costly भागide in the normal
		 * non-TSO हाल.
		 */
		tcp_skb_pcount_set(skb, 1);
		TCP_SKB_CB(skb)->tcp_gso_size = 0;
	पूर्ण अन्यथा अणु
		tcp_skb_pcount_set(skb, DIV_ROUND_UP(skb->len, mss_now));
		TCP_SKB_CB(skb)->tcp_gso_size = mss_now;
	पूर्ण
पूर्ण

/* Pcount in the middle of the ग_लिखो queue got changed, we need to करो various
 * tweaks to fix counters
 */
अटल व्योम tcp_adjust_pcount(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb, पूर्णांक decr)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	tp->packets_out -= decr;

	अगर (TCP_SKB_CB(skb)->sacked & TCPCB_SACKED_ACKED)
		tp->sacked_out -= decr;
	अगर (TCP_SKB_CB(skb)->sacked & TCPCB_SACKED_RETRANS)
		tp->retrans_out -= decr;
	अगर (TCP_SKB_CB(skb)->sacked & TCPCB_LOST)
		tp->lost_out -= decr;

	/* Reno हाल is special. Sigh... */
	अगर (tcp_is_reno(tp) && decr > 0)
		tp->sacked_out -= min_t(u32, tp->sacked_out, decr);

	अगर (tp->lost_skb_hपूर्णांक &&
	    beक्रमe(TCP_SKB_CB(skb)->seq, TCP_SKB_CB(tp->lost_skb_hपूर्णांक)->seq) &&
	    (TCP_SKB_CB(skb)->sacked & TCPCB_SACKED_ACKED))
		tp->lost_cnt_hपूर्णांक -= decr;

	tcp_verअगरy_left_out(tp);
पूर्ण

अटल bool tcp_has_tx_tstamp(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस TCP_SKB_CB(skb)->txstamp_ack ||
		(skb_shinfo(skb)->tx_flags & SKBTX_ANY_TSTAMP);
पूर्ण

अटल व्योम tcp_fragment_tstamp(काष्ठा sk_buff *skb, काष्ठा sk_buff *skb2)
अणु
	काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);

	अगर (unlikely(tcp_has_tx_tstamp(skb)) &&
	    !beक्रमe(shinfo->tskey, TCP_SKB_CB(skb2)->seq)) अणु
		काष्ठा skb_shared_info *shinfo2 = skb_shinfo(skb2);
		u8 tsflags = shinfo->tx_flags & SKBTX_ANY_TSTAMP;

		shinfo->tx_flags &= ~tsflags;
		shinfo2->tx_flags |= tsflags;
		swap(shinfo->tskey, shinfo2->tskey);
		TCP_SKB_CB(skb2)->txstamp_ack = TCP_SKB_CB(skb)->txstamp_ack;
		TCP_SKB_CB(skb)->txstamp_ack = 0;
	पूर्ण
पूर्ण

अटल व्योम tcp_skb_fragment_eor(काष्ठा sk_buff *skb, काष्ठा sk_buff *skb2)
अणु
	TCP_SKB_CB(skb2)->eor = TCP_SKB_CB(skb)->eor;
	TCP_SKB_CB(skb)->eor = 0;
पूर्ण

/* Insert buff after skb on the ग_लिखो or rtx queue of sk.  */
अटल व्योम tcp_insert_ग_लिखो_queue_after(काष्ठा sk_buff *skb,
					 काष्ठा sk_buff *buff,
					 काष्ठा sock *sk,
					 क्रमागत tcp_queue tcp_queue)
अणु
	अगर (tcp_queue == TCP_FRAG_IN_WRITE_QUEUE)
		__skb_queue_after(&sk->sk_ग_लिखो_queue, skb, buff);
	अन्यथा
		tcp_rbtree_insert(&sk->tcp_rtx_queue, buff);
पूर्ण

/* Function to create two new TCP segments.  Shrinks the given segment
 * to the specअगरied size and appends a new segment with the rest of the
 * packet to the list.  This won't be called frequently, I hope.
 * Remember, these are still headerless SKBs at this poपूर्णांक.
 */
पूर्णांक tcp_fragment(काष्ठा sock *sk, क्रमागत tcp_queue tcp_queue,
		 काष्ठा sk_buff *skb, u32 len,
		 अचिन्हित पूर्णांक mss_now, gfp_t gfp)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *buff;
	पूर्णांक nsize, old_factor;
	दीर्घ limit;
	पूर्णांक nlen;
	u8 flags;

	अगर (WARN_ON(len > skb->len))
		वापस -EINVAL;

	nsize = skb_headlen(skb) - len;
	अगर (nsize < 0)
		nsize = 0;

	/* tcp_sendmsg() can overshoot sk_wmem_queued by one full size skb.
	 * We need some allowance to not penalize applications setting small
	 * SO_SNDBUF values.
	 * Also allow first and last skb in retransmit queue to be split.
	 */
	limit = sk->sk_sndbuf + 2 * SKB_TRUESIZE(GSO_MAX_SIZE);
	अगर (unlikely((sk->sk_wmem_queued >> 1) > limit &&
		     tcp_queue != TCP_FRAG_IN_WRITE_QUEUE &&
		     skb != tcp_rtx_queue_head(sk) &&
		     skb != tcp_rtx_queue_tail(sk))) अणु
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPWQUEUETOOBIG);
		वापस -ENOMEM;
	पूर्ण

	अगर (skb_unclone(skb, gfp))
		वापस -ENOMEM;

	/* Get a new skb... क्रमce flag on. */
	buff = sk_stream_alloc_skb(sk, nsize, gfp, true);
	अगर (!buff)
		वापस -ENOMEM; /* We'll just try again later. */
	skb_copy_decrypted(buff, skb);
	mptcp_skb_ext_copy(buff, skb);

	sk_wmem_queued_add(sk, buff->truesize);
	sk_mem_अक्षरge(sk, buff->truesize);
	nlen = skb->len - len - nsize;
	buff->truesize += nlen;
	skb->truesize -= nlen;

	/* Correct the sequence numbers. */
	TCP_SKB_CB(buff)->seq = TCP_SKB_CB(skb)->seq + len;
	TCP_SKB_CB(buff)->end_seq = TCP_SKB_CB(skb)->end_seq;
	TCP_SKB_CB(skb)->end_seq = TCP_SKB_CB(buff)->seq;

	/* PSH and FIN should only be set in the second packet. */
	flags = TCP_SKB_CB(skb)->tcp_flags;
	TCP_SKB_CB(skb)->tcp_flags = flags & ~(TCPHDR_FIN | TCPHDR_PSH);
	TCP_SKB_CB(buff)->tcp_flags = flags;
	TCP_SKB_CB(buff)->sacked = TCP_SKB_CB(skb)->sacked;
	tcp_skb_fragment_eor(skb, buff);

	skb_split(skb, buff, len);

	buff->ip_summed = CHECKSUM_PARTIAL;

	buff->tstamp = skb->tstamp;
	tcp_fragment_tstamp(skb, buff);

	old_factor = tcp_skb_pcount(skb);

	/* Fix up tso_factor क्रम both original and new SKB.  */
	tcp_set_skb_tso_segs(skb, mss_now);
	tcp_set_skb_tso_segs(buff, mss_now);

	/* Update delivered info क्रम the new segment */
	TCP_SKB_CB(buff)->tx = TCP_SKB_CB(skb)->tx;

	/* If this packet has been sent out alपढ़ोy, we must
	 * adjust the various packet counters.
	 */
	अगर (!beक्रमe(tp->snd_nxt, TCP_SKB_CB(buff)->end_seq)) अणु
		पूर्णांक dअगरf = old_factor - tcp_skb_pcount(skb) -
			tcp_skb_pcount(buff);

		अगर (dअगरf)
			tcp_adjust_pcount(sk, skb, dअगरf);
	पूर्ण

	/* Link BUFF पूर्णांकo the send queue. */
	__skb_header_release(buff);
	tcp_insert_ग_लिखो_queue_after(skb, buff, sk, tcp_queue);
	अगर (tcp_queue == TCP_FRAG_IN_RTX_QUEUE)
		list_add(&buff->tcp_tsorted_anchor, &skb->tcp_tsorted_anchor);

	वापस 0;
पूर्ण

/* This is similar to __pskb_pull_tail(). The dअगरference is that pulled
 * data is not copied, but immediately discarded.
 */
अटल पूर्णांक __pskb_trim_head(काष्ठा sk_buff *skb, पूर्णांक len)
अणु
	काष्ठा skb_shared_info *shinfo;
	पूर्णांक i, k, eat;

	eat = min_t(पूर्णांक, len, skb_headlen(skb));
	अगर (eat) अणु
		__skb_pull(skb, eat);
		len -= eat;
		अगर (!len)
			वापस 0;
	पूर्ण
	eat = len;
	k = 0;
	shinfo = skb_shinfo(skb);
	क्रम (i = 0; i < shinfo->nr_frags; i++) अणु
		पूर्णांक size = skb_frag_size(&shinfo->frags[i]);

		अगर (size <= eat) अणु
			skb_frag_unref(skb, i);
			eat -= size;
		पूर्ण अन्यथा अणु
			shinfo->frags[k] = shinfo->frags[i];
			अगर (eat) अणु
				skb_frag_off_add(&shinfo->frags[k], eat);
				skb_frag_size_sub(&shinfo->frags[k], eat);
				eat = 0;
			पूर्ण
			k++;
		पूर्ण
	पूर्ण
	shinfo->nr_frags = k;

	skb->data_len -= len;
	skb->len = skb->data_len;
	वापस len;
पूर्ण

/* Remove acked data from a packet in the transmit queue. */
पूर्णांक tcp_trim_head(काष्ठा sock *sk, काष्ठा sk_buff *skb, u32 len)
अणु
	u32 delta_truesize;

	अगर (skb_unclone(skb, GFP_ATOMIC))
		वापस -ENOMEM;

	delta_truesize = __pskb_trim_head(skb, len);

	TCP_SKB_CB(skb)->seq += len;
	skb->ip_summed = CHECKSUM_PARTIAL;

	अगर (delta_truesize) अणु
		skb->truesize	   -= delta_truesize;
		sk_wmem_queued_add(sk, -delta_truesize);
		sk_mem_unअक्षरge(sk, delta_truesize);
	पूर्ण

	/* Any change of skb->len requires recalculation of tso factor. */
	अगर (tcp_skb_pcount(skb) > 1)
		tcp_set_skb_tso_segs(skb, tcp_skb_mss(skb));

	वापस 0;
पूर्ण

/* Calculate MSS not accounting any TCP options.  */
अटल अंतरभूत पूर्णांक __tcp_mtu_to_mss(काष्ठा sock *sk, पूर्णांक pmtu)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	पूर्णांक mss_now;

	/* Calculate base mss without TCP options:
	   It is MMS_S - माप(tcphdr) of rfc1122
	 */
	mss_now = pmtu - icsk->icsk_af_ops->net_header_len - माप(काष्ठा tcphdr);

	/* IPv6 adds a frag_hdr in हाल RTAX_FEATURE_ALLFRAG is set */
	अगर (icsk->icsk_af_ops->net_frag_header_len) अणु
		स्थिर काष्ठा dst_entry *dst = __sk_dst_get(sk);

		अगर (dst && dst_allfrag(dst))
			mss_now -= icsk->icsk_af_ops->net_frag_header_len;
	पूर्ण

	/* Clamp it (mss_clamp करोes not include tcp options) */
	अगर (mss_now > tp->rx_opt.mss_clamp)
		mss_now = tp->rx_opt.mss_clamp;

	/* Now subtract optional transport overhead */
	mss_now -= icsk->icsk_ext_hdr_len;

	/* Then reserve room क्रम full set of TCP options and 8 bytes of data */
	mss_now = max(mss_now, sock_net(sk)->ipv4.sysctl_tcp_min_snd_mss);
	वापस mss_now;
पूर्ण

/* Calculate MSS. Not accounting क्रम SACKs here.  */
पूर्णांक tcp_mtu_to_mss(काष्ठा sock *sk, पूर्णांक pmtu)
अणु
	/* Subtract TCP options size, not including SACKs */
	वापस __tcp_mtu_to_mss(sk, pmtu) -
	       (tcp_sk(sk)->tcp_header_len - माप(काष्ठा tcphdr));
पूर्ण

/* Inverse of above */
पूर्णांक tcp_mss_to_mtu(काष्ठा sock *sk, पूर्णांक mss)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	पूर्णांक mtu;

	mtu = mss +
	      tp->tcp_header_len +
	      icsk->icsk_ext_hdr_len +
	      icsk->icsk_af_ops->net_header_len;

	/* IPv6 adds a frag_hdr in हाल RTAX_FEATURE_ALLFRAG is set */
	अगर (icsk->icsk_af_ops->net_frag_header_len) अणु
		स्थिर काष्ठा dst_entry *dst = __sk_dst_get(sk);

		अगर (dst && dst_allfrag(dst))
			mtu += icsk->icsk_af_ops->net_frag_header_len;
	पूर्ण
	वापस mtu;
पूर्ण
EXPORT_SYMBOL(tcp_mss_to_mtu);

/* MTU probing init per socket */
व्योम tcp_mtup_init(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा net *net = sock_net(sk);

	icsk->icsk_mtup.enabled = net->ipv4.sysctl_tcp_mtu_probing > 1;
	icsk->icsk_mtup.search_high = tp->rx_opt.mss_clamp + माप(काष्ठा tcphdr) +
			       icsk->icsk_af_ops->net_header_len;
	icsk->icsk_mtup.search_low = tcp_mss_to_mtu(sk, net->ipv4.sysctl_tcp_base_mss);
	icsk->icsk_mtup.probe_size = 0;
	अगर (icsk->icsk_mtup.enabled)
		icsk->icsk_mtup.probe_बारtamp = tcp_jअगरfies32;
पूर्ण
EXPORT_SYMBOL(tcp_mtup_init);

/* This function synchronize snd mss to current pmtu/exthdr set.

   tp->rx_opt.user_mss is mss set by user by TCP_MAXSEG. It करोes NOT counts
   क्रम TCP options, but includes only bare TCP header.

   tp->rx_opt.mss_clamp is mss negotiated at connection setup.
   It is minimum of user_mss and mss received with SYN.
   It also करोes not include TCP options.

   inet_csk(sk)->icsk_pmtu_cookie is last pmtu, seen by this function.

   tp->mss_cache is current effective sending mss, including
   all tcp options except क्रम SACKs. It is evaluated,
   taking पूर्णांकo account current pmtu, but never exceeds
   tp->rx_opt.mss_clamp.

   NOTE1. rfc1122 clearly states that advertised MSS
   DOES NOT include either tcp or ip options.

   NOTE2. inet_csk(sk)->icsk_pmtu_cookie and tp->mss_cache
   are READ ONLY outside this function.		--ANK (980731)
 */
अचिन्हित पूर्णांक tcp_sync_mss(काष्ठा sock *sk, u32 pmtu)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	पूर्णांक mss_now;

	अगर (icsk->icsk_mtup.search_high > pmtu)
		icsk->icsk_mtup.search_high = pmtu;

	mss_now = tcp_mtu_to_mss(sk, pmtu);
	mss_now = tcp_bound_to_half_wnd(tp, mss_now);

	/* And store cached results */
	icsk->icsk_pmtu_cookie = pmtu;
	अगर (icsk->icsk_mtup.enabled)
		mss_now = min(mss_now, tcp_mtu_to_mss(sk, icsk->icsk_mtup.search_low));
	tp->mss_cache = mss_now;

	वापस mss_now;
पूर्ण
EXPORT_SYMBOL(tcp_sync_mss);

/* Compute the current effective MSS, taking SACKs and IP options,
 * and even PMTU discovery events पूर्णांकo account.
 */
अचिन्हित पूर्णांक tcp_current_mss(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	स्थिर काष्ठा dst_entry *dst = __sk_dst_get(sk);
	u32 mss_now;
	अचिन्हित पूर्णांक header_len;
	काष्ठा tcp_out_options opts;
	काष्ठा tcp_md5sig_key *md5;

	mss_now = tp->mss_cache;

	अगर (dst) अणु
		u32 mtu = dst_mtu(dst);
		अगर (mtu != inet_csk(sk)->icsk_pmtu_cookie)
			mss_now = tcp_sync_mss(sk, mtu);
	पूर्ण

	header_len = tcp_established_options(sk, शून्य, &opts, &md5) +
		     माप(काष्ठा tcphdr);
	/* The mss_cache is sized based on tp->tcp_header_len, which assumes
	 * some common options. If this is an odd packet (because we have SACK
	 * blocks etc) then our calculated header_len will be dअगरferent, and
	 * we have to adjust mss_now correspondingly */
	अगर (header_len != tp->tcp_header_len) अणु
		पूर्णांक delta = (पूर्णांक) header_len - tp->tcp_header_len;
		mss_now -= delta;
	पूर्ण

	वापस mss_now;
पूर्ण

/* RFC2861, slow part. Adjust cwnd, after it was not full during one rto.
 * As additional protections, we करो not touch cwnd in retransmission phases,
 * and अगर application hit its sndbuf limit recently.
 */
अटल व्योम tcp_cwnd_application_limited(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (inet_csk(sk)->icsk_ca_state == TCP_CA_Open &&
	    sk->sk_socket && !test_bit(SOCK_NOSPACE, &sk->sk_socket->flags)) अणु
		/* Limited by application or receiver winकरोw. */
		u32 init_win = tcp_init_cwnd(tp, __sk_dst_get(sk));
		u32 win_used = max(tp->snd_cwnd_used, init_win);
		अगर (win_used < tp->snd_cwnd) अणु
			tp->snd_ssthresh = tcp_current_ssthresh(sk);
			tp->snd_cwnd = (tp->snd_cwnd + win_used) >> 1;
		पूर्ण
		tp->snd_cwnd_used = 0;
	पूर्ण
	tp->snd_cwnd_stamp = tcp_jअगरfies32;
पूर्ण

अटल व्योम tcp_cwnd_validate(काष्ठा sock *sk, bool is_cwnd_limited)
अणु
	स्थिर काष्ठा tcp_congestion_ops *ca_ops = inet_csk(sk)->icsk_ca_ops;
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	/* Track the maximum number of outstanding packets in each
	 * winकरोw, and remember whether we were cwnd-limited then.
	 */
	अगर (!beक्रमe(tp->snd_una, tp->max_packets_seq) ||
	    tp->packets_out > tp->max_packets_out ||
	    is_cwnd_limited) अणु
		tp->max_packets_out = tp->packets_out;
		tp->max_packets_seq = tp->snd_nxt;
		tp->is_cwnd_limited = is_cwnd_limited;
	पूर्ण

	अगर (tcp_is_cwnd_limited(sk)) अणु
		/* Network is feed fully. */
		tp->snd_cwnd_used = 0;
		tp->snd_cwnd_stamp = tcp_jअगरfies32;
	पूर्ण अन्यथा अणु
		/* Network starves. */
		अगर (tp->packets_out > tp->snd_cwnd_used)
			tp->snd_cwnd_used = tp->packets_out;

		अगर (sock_net(sk)->ipv4.sysctl_tcp_slow_start_after_idle &&
		    (s32)(tcp_jअगरfies32 - tp->snd_cwnd_stamp) >= inet_csk(sk)->icsk_rto &&
		    !ca_ops->cong_control)
			tcp_cwnd_application_limited(sk);

		/* The following conditions together indicate the starvation
		 * is caused by insufficient sender buffer:
		 * 1) just sent some data (see tcp_ग_लिखो_xmit)
		 * 2) not cwnd limited (this अन्यथा condition)
		 * 3) no more data to send (tcp_ग_लिखो_queue_empty())
		 * 4) application is hitting buffer limit (SOCK_NOSPACE)
		 */
		अगर (tcp_ग_लिखो_queue_empty(sk) && sk->sk_socket &&
		    test_bit(SOCK_NOSPACE, &sk->sk_socket->flags) &&
		    (1 << sk->sk_state) & (TCPF_ESTABLISHED | TCPF_CLOSE_WAIT))
			tcp_chrono_start(sk, TCP_CHRONO_SNDBUF_LIMITED);
	पूर्ण
पूर्ण

/* Minshall's variant of the Nagle send check. */
अटल bool tcp_minshall_check(स्थिर काष्ठा tcp_sock *tp)
अणु
	वापस after(tp->snd_sml, tp->snd_una) &&
		!after(tp->snd_sml, tp->snd_nxt);
पूर्ण

/* Update snd_sml अगर this skb is under mss
 * Note that a TSO packet might end with a sub-mss segment
 * The test is really :
 * अगर ((skb->len % mss) != 0)
 *        tp->snd_sml = TCP_SKB_CB(skb)->end_seq;
 * But we can aव्योम करोing the भागide again given we alपढ़ोy have
 *  skb_pcount = skb->len / mss_now
 */
अटल व्योम tcp_minshall_update(काष्ठा tcp_sock *tp, अचिन्हित पूर्णांक mss_now,
				स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (skb->len < tcp_skb_pcount(skb) * mss_now)
		tp->snd_sml = TCP_SKB_CB(skb)->end_seq;
पूर्ण

/* Return false, अगर packet can be sent now without violation Nagle's rules:
 * 1. It is full sized. (provided by caller in %partial bool)
 * 2. Or it contains FIN. (alपढ़ोy checked by caller)
 * 3. Or TCP_CORK is not set, and TCP_NODELAY is set.
 * 4. Or TCP_CORK is not set, and all sent packets are ACKed.
 *    With Minshall's modअगरication: all sent small packets are ACKed.
 */
अटल bool tcp_nagle_check(bool partial, स्थिर काष्ठा tcp_sock *tp,
			    पूर्णांक nonagle)
अणु
	वापस partial &&
		((nonagle & TCP_NAGLE_CORK) ||
		 (!nonagle && tp->packets_out && tcp_minshall_check(tp)));
पूर्ण

/* Return how many segs we'd like on a TSO packet,
 * to send one TSO packet per ms
 */
अटल u32 tcp_tso_स्वतःsize(स्थिर काष्ठा sock *sk, अचिन्हित पूर्णांक mss_now,
			    पूर्णांक min_tso_segs)
अणु
	u32 bytes, segs;

	bytes = min_t(अचिन्हित दीर्घ,
		      sk->sk_pacing_rate >> READ_ONCE(sk->sk_pacing_shअगरt),
		      sk->sk_gso_max_size - 1 - MAX_TCP_HEADER);

	/* Goal is to send at least one packet per ms,
	 * not one big TSO packet every 100 ms.
	 * This preserves ACK घड़ीing and is consistent
	 * with tcp_tso_should_defer() heuristic.
	 */
	segs = max_t(u32, bytes / mss_now, min_tso_segs);

	वापस segs;
पूर्ण

/* Return the number of segments we want in the skb we are transmitting.
 * See अगर congestion control module wants to decide; otherwise, स्वतःsize.
 */
अटल u32 tcp_tso_segs(काष्ठा sock *sk, अचिन्हित पूर्णांक mss_now)
अणु
	स्थिर काष्ठा tcp_congestion_ops *ca_ops = inet_csk(sk)->icsk_ca_ops;
	u32 min_tso, tso_segs;

	min_tso = ca_ops->min_tso_segs ?
			ca_ops->min_tso_segs(sk) :
			sock_net(sk)->ipv4.sysctl_tcp_min_tso_segs;

	tso_segs = tcp_tso_स्वतःsize(sk, mss_now, min_tso);
	वापस min_t(u32, tso_segs, sk->sk_gso_max_segs);
पूर्ण

/* Returns the portion of skb which can be sent right away */
अटल अचिन्हित पूर्णांक tcp_mss_split_poपूर्णांक(स्थिर काष्ठा sock *sk,
					स्थिर काष्ठा sk_buff *skb,
					अचिन्हित पूर्णांक mss_now,
					अचिन्हित पूर्णांक max_segs,
					पूर्णांक nonagle)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 partial, needed, winकरोw, max_len;

	winकरोw = tcp_wnd_end(tp) - TCP_SKB_CB(skb)->seq;
	max_len = mss_now * max_segs;

	अगर (likely(max_len <= winकरोw && skb != tcp_ग_लिखो_queue_tail(sk)))
		वापस max_len;

	needed = min(skb->len, winकरोw);

	अगर (max_len <= needed)
		वापस max_len;

	partial = needed % mss_now;
	/* If last segment is not a full MSS, check अगर Nagle rules allow us
	 * to include this last segment in this skb.
	 * Otherwise, we'll split the skb at last MSS boundary
	 */
	अगर (tcp_nagle_check(partial != 0, tp, nonagle))
		वापस needed - partial;

	वापस needed;
पूर्ण

/* Can at least one segment of SKB be sent right now, according to the
 * congestion winकरोw rules?  If so, वापस how many segments are allowed.
 */
अटल अंतरभूत अचिन्हित पूर्णांक tcp_cwnd_test(स्थिर काष्ठा tcp_sock *tp,
					 स्थिर काष्ठा sk_buff *skb)
अणु
	u32 in_flight, cwnd, halfcwnd;

	/* Don't be strict about the congestion winकरोw क्रम the final FIN.  */
	अगर ((TCP_SKB_CB(skb)->tcp_flags & TCPHDR_FIN) &&
	    tcp_skb_pcount(skb) == 1)
		वापस 1;

	in_flight = tcp_packets_in_flight(tp);
	cwnd = tp->snd_cwnd;
	अगर (in_flight >= cwnd)
		वापस 0;

	/* For better scheduling, ensure we have at least
	 * 2 GSO packets in flight.
	 */
	halfcwnd = max(cwnd >> 1, 1U);
	वापस min(halfcwnd, cwnd - in_flight);
पूर्ण

/* Initialize TSO state of a skb.
 * This must be invoked the first समय we consider transmitting
 * SKB onto the wire.
 */
अटल पूर्णांक tcp_init_tso_segs(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक mss_now)
अणु
	पूर्णांक tso_segs = tcp_skb_pcount(skb);

	अगर (!tso_segs || (tso_segs > 1 && tcp_skb_mss(skb) != mss_now)) अणु
		tcp_set_skb_tso_segs(skb, mss_now);
		tso_segs = tcp_skb_pcount(skb);
	पूर्ण
	वापस tso_segs;
पूर्ण


/* Return true अगर the Nagle test allows this packet to be
 * sent now.
 */
अटल अंतरभूत bool tcp_nagle_test(स्थिर काष्ठा tcp_sock *tp, स्थिर काष्ठा sk_buff *skb,
				  अचिन्हित पूर्णांक cur_mss, पूर्णांक nonagle)
अणु
	/* Nagle rule करोes not apply to frames, which sit in the middle of the
	 * ग_लिखो_queue (they have no chances to get new data).
	 *
	 * This is implemented in the callers, where they modअगरy the 'nonagle'
	 * argument based upon the location of SKB in the send queue.
	 */
	अगर (nonagle & TCP_NAGLE_PUSH)
		वापस true;

	/* Don't use the nagle rule क्रम urgent data (or क्रम the final FIN). */
	अगर (tcp_urg_mode(tp) || (TCP_SKB_CB(skb)->tcp_flags & TCPHDR_FIN))
		वापस true;

	अगर (!tcp_nagle_check(skb->len < cur_mss, tp, nonagle))
		वापस true;

	वापस false;
पूर्ण

/* Does at least the first segment of SKB fit पूर्णांकo the send winकरोw? */
अटल bool tcp_snd_wnd_test(स्थिर काष्ठा tcp_sock *tp,
			     स्थिर काष्ठा sk_buff *skb,
			     अचिन्हित पूर्णांक cur_mss)
अणु
	u32 end_seq = TCP_SKB_CB(skb)->end_seq;

	अगर (skb->len > cur_mss)
		end_seq = TCP_SKB_CB(skb)->seq + cur_mss;

	वापस !after(end_seq, tcp_wnd_end(tp));
पूर्ण

/* Trim TSO SKB to LEN bytes, put the reमुख्यing data पूर्णांकo a new packet
 * which is put after SKB on the list.  It is very much like
 * tcp_fragment() except that it may make several kinds of assumptions
 * in order to speed up the splitting operation.  In particular, we
 * know that all the data is in scatter-gather pages, and that the
 * packet has never been sent out beक्रमe (and thus is not cloned).
 */
अटल पूर्णांक tso_fragment(काष्ठा sock *sk, काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len,
			अचिन्हित पूर्णांक mss_now, gfp_t gfp)
अणु
	पूर्णांक nlen = skb->len - len;
	काष्ठा sk_buff *buff;
	u8 flags;

	/* All of a TSO frame must be composed of paged data.  */
	अगर (skb->len != skb->data_len)
		वापस tcp_fragment(sk, TCP_FRAG_IN_WRITE_QUEUE,
				    skb, len, mss_now, gfp);

	buff = sk_stream_alloc_skb(sk, 0, gfp, true);
	अगर (unlikely(!buff))
		वापस -ENOMEM;
	skb_copy_decrypted(buff, skb);
	mptcp_skb_ext_copy(buff, skb);

	sk_wmem_queued_add(sk, buff->truesize);
	sk_mem_अक्षरge(sk, buff->truesize);
	buff->truesize += nlen;
	skb->truesize -= nlen;

	/* Correct the sequence numbers. */
	TCP_SKB_CB(buff)->seq = TCP_SKB_CB(skb)->seq + len;
	TCP_SKB_CB(buff)->end_seq = TCP_SKB_CB(skb)->end_seq;
	TCP_SKB_CB(skb)->end_seq = TCP_SKB_CB(buff)->seq;

	/* PSH and FIN should only be set in the second packet. */
	flags = TCP_SKB_CB(skb)->tcp_flags;
	TCP_SKB_CB(skb)->tcp_flags = flags & ~(TCPHDR_FIN | TCPHDR_PSH);
	TCP_SKB_CB(buff)->tcp_flags = flags;

	/* This packet was never sent out yet, so no SACK bits. */
	TCP_SKB_CB(buff)->sacked = 0;

	tcp_skb_fragment_eor(skb, buff);

	buff->ip_summed = CHECKSUM_PARTIAL;
	skb_split(skb, buff, len);
	tcp_fragment_tstamp(skb, buff);

	/* Fix up tso_factor क्रम both original and new SKB.  */
	tcp_set_skb_tso_segs(skb, mss_now);
	tcp_set_skb_tso_segs(buff, mss_now);

	/* Link BUFF पूर्णांकo the send queue. */
	__skb_header_release(buff);
	tcp_insert_ग_लिखो_queue_after(skb, buff, sk, TCP_FRAG_IN_WRITE_QUEUE);

	वापस 0;
पूर्ण

/* Try to defer sending, अगर possible, in order to minimize the amount
 * of TSO splitting we करो.  View it as a kind of TSO Nagle test.
 *
 * This algorithm is from John Heffner.
 */
अटल bool tcp_tso_should_defer(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				 bool *is_cwnd_limited,
				 bool *is_rwnd_limited,
				 u32 max_segs)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	u32 send_win, cong_win, limit, in_flight;
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *head;
	पूर्णांक win_भागisor;
	s64 delta;

	अगर (icsk->icsk_ca_state >= TCP_CA_Recovery)
		जाओ send_now;

	/* Aव्योम bursty behavior by allowing defer
	 * only अगर the last ग_लिखो was recent (1 ms).
	 * Note that tp->tcp_wstamp_ns can be in the future अगर we have
	 * packets रुकोing in a qdisc or device क्रम EDT delivery.
	 */
	delta = tp->tcp_घड़ी_cache - tp->tcp_wstamp_ns - NSEC_PER_MSEC;
	अगर (delta > 0)
		जाओ send_now;

	in_flight = tcp_packets_in_flight(tp);

	BUG_ON(tcp_skb_pcount(skb) <= 1);
	BUG_ON(tp->snd_cwnd <= in_flight);

	send_win = tcp_wnd_end(tp) - TCP_SKB_CB(skb)->seq;

	/* From in_flight test above, we know that cwnd > in_flight.  */
	cong_win = (tp->snd_cwnd - in_flight) * tp->mss_cache;

	limit = min(send_win, cong_win);

	/* If a full-sized TSO skb can be sent, करो it. */
	अगर (limit >= max_segs * tp->mss_cache)
		जाओ send_now;

	/* Middle in queue won't get any more data, full sendable alपढ़ोy? */
	अगर ((skb != tcp_ग_लिखो_queue_tail(sk)) && (limit >= skb->len))
		जाओ send_now;

	win_भागisor = READ_ONCE(sock_net(sk)->ipv4.sysctl_tcp_tso_win_भागisor);
	अगर (win_भागisor) अणु
		u32 chunk = min(tp->snd_wnd, tp->snd_cwnd * tp->mss_cache);

		/* If at least some fraction of a winकरोw is available,
		 * just use it.
		 */
		chunk /= win_भागisor;
		अगर (limit >= chunk)
			जाओ send_now;
	पूर्ण अन्यथा अणु
		/* Dअगरferent approach, try not to defer past a single
		 * ACK.  Receiver should ACK every other full sized
		 * frame, so अगर we have space क्रम more than 3 frames
		 * then send now.
		 */
		अगर (limit > tcp_max_tso_deferred_mss(tp) * tp->mss_cache)
			जाओ send_now;
	पूर्ण

	/* TODO : use tsorted_sent_queue ? */
	head = tcp_rtx_queue_head(sk);
	अगर (!head)
		जाओ send_now;
	delta = tp->tcp_घड़ी_cache - head->tstamp;
	/* If next ACK is likely to come too late (half srtt), करो not defer */
	अगर ((s64)(delta - (u64)NSEC_PER_USEC * (tp->srtt_us >> 4)) < 0)
		जाओ send_now;

	/* Ok, it looks like it is advisable to defer.
	 * Three हालs are tracked :
	 * 1) We are cwnd-limited
	 * 2) We are rwnd-limited
	 * 3) We are application limited.
	 */
	अगर (cong_win < send_win) अणु
		अगर (cong_win <= skb->len) अणु
			*is_cwnd_limited = true;
			वापस true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (send_win <= skb->len) अणु
			*is_rwnd_limited = true;
			वापस true;
		पूर्ण
	पूर्ण

	/* If this packet won't get more data, करो not रुको. */
	अगर ((TCP_SKB_CB(skb)->tcp_flags & TCPHDR_FIN) ||
	    TCP_SKB_CB(skb)->eor)
		जाओ send_now;

	वापस true;

send_now:
	वापस false;
पूर्ण

अटल अंतरभूत व्योम tcp_mtu_check_reprobe(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा net *net = sock_net(sk);
	u32 पूर्णांकerval;
	s32 delta;

	पूर्णांकerval = net->ipv4.sysctl_tcp_probe_पूर्णांकerval;
	delta = tcp_jअगरfies32 - icsk->icsk_mtup.probe_बारtamp;
	अगर (unlikely(delta >= पूर्णांकerval * HZ)) अणु
		पूर्णांक mss = tcp_current_mss(sk);

		/* Update current search range */
		icsk->icsk_mtup.probe_size = 0;
		icsk->icsk_mtup.search_high = tp->rx_opt.mss_clamp +
			माप(काष्ठा tcphdr) +
			icsk->icsk_af_ops->net_header_len;
		icsk->icsk_mtup.search_low = tcp_mss_to_mtu(sk, mss);

		/* Update probe समय stamp */
		icsk->icsk_mtup.probe_बारtamp = tcp_jअगरfies32;
	पूर्ण
पूर्ण

अटल bool tcp_can_coalesce_send_queue_head(काष्ठा sock *sk, पूर्णांक len)
अणु
	काष्ठा sk_buff *skb, *next;

	skb = tcp_send_head(sk);
	tcp_क्रम_ग_लिखो_queue_from_safe(skb, next, sk) अणु
		अगर (len <= skb->len)
			अवरोध;

		अगर (unlikely(TCP_SKB_CB(skb)->eor) || tcp_has_tx_tstamp(skb))
			वापस false;

		len -= skb->len;
	पूर्ण

	वापस true;
पूर्ण

/* Create a new MTU probe अगर we are पढ़ोy.
 * MTU probe is regularly attempting to increase the path MTU by
 * deliberately sending larger packets.  This discovers routing
 * changes resulting in larger path MTUs.
 *
 * Returns 0 अगर we should रुको to probe (no cwnd available),
 *         1 अगर a probe was sent,
 *         -1 otherwise
 */
अटल पूर्णांक tcp_mtu_probe(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *skb, *nskb, *next;
	काष्ठा net *net = sock_net(sk);
	पूर्णांक probe_size;
	पूर्णांक size_needed;
	पूर्णांक copy, len;
	पूर्णांक mss_now;
	पूर्णांक पूर्णांकerval;

	/* Not currently probing/verअगरying,
	 * not in recovery,
	 * have enough cwnd, and
	 * not SACKing (the variable headers throw things off)
	 */
	अगर (likely(!icsk->icsk_mtup.enabled ||
		   icsk->icsk_mtup.probe_size ||
		   inet_csk(sk)->icsk_ca_state != TCP_CA_Open ||
		   tp->snd_cwnd < 11 ||
		   tp->rx_opt.num_sacks || tp->rx_opt.dsack))
		वापस -1;

	/* Use binary search क्रम probe_size between tcp_mss_base,
	 * and current mss_clamp. अगर (search_high - search_low)
	 * smaller than a threshold, backoff from probing.
	 */
	mss_now = tcp_current_mss(sk);
	probe_size = tcp_mtu_to_mss(sk, (icsk->icsk_mtup.search_high +
				    icsk->icsk_mtup.search_low) >> 1);
	size_needed = probe_size + (tp->reordering + 1) * tp->mss_cache;
	पूर्णांकerval = icsk->icsk_mtup.search_high - icsk->icsk_mtup.search_low;
	/* When misक्रमtune happens, we are reprobing actively,
	 * and then reprobe समयr has expired. We stick with current
	 * probing process by not resetting search range to its orignal.
	 */
	अगर (probe_size > tcp_mtu_to_mss(sk, icsk->icsk_mtup.search_high) ||
		पूर्णांकerval < net->ipv4.sysctl_tcp_probe_threshold) अणु
		/* Check whether enough समय has elaplased क्रम
		 * another round of probing.
		 */
		tcp_mtu_check_reprobe(sk);
		वापस -1;
	पूर्ण

	/* Have enough data in the send queue to probe? */
	अगर (tp->ग_लिखो_seq - tp->snd_nxt < size_needed)
		वापस -1;

	अगर (tp->snd_wnd < size_needed)
		वापस -1;
	अगर (after(tp->snd_nxt + size_needed, tcp_wnd_end(tp)))
		वापस 0;

	/* Do we need to रुको to drain cwnd? With none in flight, करोn't stall */
	अगर (tcp_packets_in_flight(tp) + 2 > tp->snd_cwnd) अणु
		अगर (!tcp_packets_in_flight(tp))
			वापस -1;
		अन्यथा
			वापस 0;
	पूर्ण

	अगर (!tcp_can_coalesce_send_queue_head(sk, probe_size))
		वापस -1;

	/* We're allowed to probe.  Build it now. */
	nskb = sk_stream_alloc_skb(sk, probe_size, GFP_ATOMIC, false);
	अगर (!nskb)
		वापस -1;
	sk_wmem_queued_add(sk, nskb->truesize);
	sk_mem_अक्षरge(sk, nskb->truesize);

	skb = tcp_send_head(sk);
	skb_copy_decrypted(nskb, skb);
	mptcp_skb_ext_copy(nskb, skb);

	TCP_SKB_CB(nskb)->seq = TCP_SKB_CB(skb)->seq;
	TCP_SKB_CB(nskb)->end_seq = TCP_SKB_CB(skb)->seq + probe_size;
	TCP_SKB_CB(nskb)->tcp_flags = TCPHDR_ACK;
	TCP_SKB_CB(nskb)->sacked = 0;
	nskb->csum = 0;
	nskb->ip_summed = CHECKSUM_PARTIAL;

	tcp_insert_ग_लिखो_queue_beक्रमe(nskb, skb, sk);
	tcp_highest_sack_replace(sk, skb, nskb);

	len = 0;
	tcp_क्रम_ग_लिखो_queue_from_safe(skb, next, sk) अणु
		copy = min_t(पूर्णांक, skb->len, probe_size - len);
		skb_copy_bits(skb, 0, skb_put(nskb, copy), copy);

		अगर (skb->len <= copy) अणु
			/* We've eaten all the data from this skb.
			 * Throw it away. */
			TCP_SKB_CB(nskb)->tcp_flags |= TCP_SKB_CB(skb)->tcp_flags;
			/* If this is the last SKB we copy and eor is set
			 * we need to propagate it to the new skb.
			 */
			TCP_SKB_CB(nskb)->eor = TCP_SKB_CB(skb)->eor;
			tcp_skb_collapse_tstamp(nskb, skb);
			tcp_unlink_ग_लिखो_queue(skb, sk);
			sk_wmem_मुक्त_skb(sk, skb);
		पूर्ण अन्यथा अणु
			TCP_SKB_CB(nskb)->tcp_flags |= TCP_SKB_CB(skb)->tcp_flags &
						   ~(TCPHDR_FIN|TCPHDR_PSH);
			अगर (!skb_shinfo(skb)->nr_frags) अणु
				skb_pull(skb, copy);
			पूर्ण अन्यथा अणु
				__pskb_trim_head(skb, copy);
				tcp_set_skb_tso_segs(skb, mss_now);
			पूर्ण
			TCP_SKB_CB(skb)->seq += copy;
		पूर्ण

		len += copy;

		अगर (len >= probe_size)
			अवरोध;
	पूर्ण
	tcp_init_tso_segs(nskb, nskb->len);

	/* We're पढ़ोy to send.  If this fails, the probe will
	 * be resegmented पूर्णांकo mss-sized pieces by tcp_ग_लिखो_xmit().
	 */
	अगर (!tcp_transmit_skb(sk, nskb, 1, GFP_ATOMIC)) अणु
		/* Decrement cwnd here because we are sending
		 * effectively two packets. */
		tp->snd_cwnd--;
		tcp_event_new_data_sent(sk, nskb);

		icsk->icsk_mtup.probe_size = tcp_mss_to_mtu(sk, nskb->len);
		tp->mtu_probe.probe_seq_start = TCP_SKB_CB(nskb)->seq;
		tp->mtu_probe.probe_seq_end = TCP_SKB_CB(nskb)->end_seq;

		वापस 1;
	पूर्ण

	वापस -1;
पूर्ण

अटल bool tcp_pacing_check(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (!tcp_needs_पूर्णांकernal_pacing(sk))
		वापस false;

	अगर (tp->tcp_wstamp_ns <= tp->tcp_घड़ी_cache)
		वापस false;

	अगर (!hrसमयr_is_queued(&tp->pacing_समयr)) अणु
		hrसमयr_start(&tp->pacing_समयr,
			      ns_to_kसमय(tp->tcp_wstamp_ns),
			      HRTIMER_MODE_ABS_PINNED_SOFT);
		sock_hold(sk);
	पूर्ण
	वापस true;
पूर्ण

/* TCP Small Queues :
 * Control number of packets in qdisc/devices to two packets / or ~1 ms.
 * (These limits are द्विगुनd क्रम retransmits)
 * This allows क्रम :
 *  - better RTT estimation and ACK scheduling
 *  - faster recovery
 *  - high rates
 * Alas, some drivers / subप्रणालीs require a fair amount
 * of queued bytes to ensure line rate.
 * One example is wअगरi aggregation (802.11 AMPDU)
 */
अटल bool tcp_small_queue_check(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb,
				  अचिन्हित पूर्णांक factor)
अणु
	अचिन्हित दीर्घ limit;

	limit = max_t(अचिन्हित दीर्घ,
		      2 * skb->truesize,
		      sk->sk_pacing_rate >> READ_ONCE(sk->sk_pacing_shअगरt));
	अगर (sk->sk_pacing_status == SK_PACING_NONE)
		limit = min_t(अचिन्हित दीर्घ, limit,
			      sock_net(sk)->ipv4.sysctl_tcp_limit_output_bytes);
	limit <<= factor;

	अगर (अटल_branch_unlikely(&tcp_tx_delay_enabled) &&
	    tcp_sk(sk)->tcp_tx_delay) अणु
		u64 extra_bytes = (u64)sk->sk_pacing_rate * tcp_sk(sk)->tcp_tx_delay;

		/* TSQ is based on skb truesize sum (sk_wmem_alloc), so we
		 * approximate our needs assuming an ~100% skb->truesize overhead.
		 * USEC_PER_SEC is approximated by 2^20.
		 * करो_भाग(extra_bytes, USEC_PER_SEC/2) is replaced by a right shअगरt.
		 */
		extra_bytes >>= (20 - 1);
		limit += extra_bytes;
	पूर्ण
	अगर (refcount_पढ़ो(&sk->sk_wmem_alloc) > limit) अणु
		/* Always send skb अगर rtx queue is empty.
		 * No need to रुको क्रम TX completion to call us back,
		 * after softirq/tasklet schedule.
		 * This helps when TX completions are delayed too much.
		 */
		अगर (tcp_rtx_queue_empty(sk))
			वापस false;

		set_bit(TSQ_THROTTLED, &sk->sk_tsq_flags);
		/* It is possible TX completion alपढ़ोy happened
		 * beक्रमe we set TSQ_THROTTLED, so we must
		 * test again the condition.
		 */
		smp_mb__after_atomic();
		अगर (refcount_पढ़ो(&sk->sk_wmem_alloc) > limit)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम tcp_chrono_set(काष्ठा tcp_sock *tp, स्थिर क्रमागत tcp_chrono new)
अणु
	स्थिर u32 now = tcp_jअगरfies32;
	क्रमागत tcp_chrono old = tp->chrono_type;

	अगर (old > TCP_CHRONO_UNSPEC)
		tp->chrono_stat[old - 1] += now - tp->chrono_start;
	tp->chrono_start = now;
	tp->chrono_type = new;
पूर्ण

व्योम tcp_chrono_start(काष्ठा sock *sk, स्थिर क्रमागत tcp_chrono type)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	/* If there are multiple conditions worthy of tracking in a
	 * chronograph then the highest priority क्रमागत takes precedence
	 * over the other conditions. So that अगर something "more interesting"
	 * starts happening, stop the previous chrono and start a new one.
	 */
	अगर (type > tp->chrono_type)
		tcp_chrono_set(tp, type);
पूर्ण

व्योम tcp_chrono_stop(काष्ठा sock *sk, स्थिर क्रमागत tcp_chrono type)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);


	/* There are multiple conditions worthy of tracking in a
	 * chronograph, so that the highest priority क्रमागत takes
	 * precedence over the other conditions (see tcp_chrono_start).
	 * If a condition stops, we only stop chrono tracking अगर
	 * it's the "most interesting" or current chrono we are
	 * tracking and starts busy chrono अगर we have pending data.
	 */
	अगर (tcp_rtx_and_ग_लिखो_queues_empty(sk))
		tcp_chrono_set(tp, TCP_CHRONO_UNSPEC);
	अन्यथा अगर (type == tp->chrono_type)
		tcp_chrono_set(tp, TCP_CHRONO_BUSY);
पूर्ण

/* This routine ग_लिखोs packets to the network.  It advances the
 * send_head.  This happens as incoming acks खोलो up the remote
 * winकरोw क्रम us.
 *
 * LARGESEND note: !tcp_urg_mode is overसमाप्त, only frames between
 * snd_up-64k-mss .. snd_up cannot be large. However, taking पूर्णांकo
 * account rare use of URG, this is not a big flaw.
 *
 * Send at most one packet when push_one > 0. Temporarily ignore
 * cwnd limit to क्रमce at most one packet out when push_one == 2.

 * Returns true, अगर no segments are in flight and we have queued segments,
 * but cannot send anything now because of SWS or another problem.
 */
अटल bool tcp_ग_लिखो_xmit(काष्ठा sock *sk, अचिन्हित पूर्णांक mss_now, पूर्णांक nonagle,
			   पूर्णांक push_one, gfp_t gfp)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक tso_segs, sent_pkts;
	पूर्णांक cwnd_quota;
	पूर्णांक result;
	bool is_cwnd_limited = false, is_rwnd_limited = false;
	u32 max_segs;

	sent_pkts = 0;

	tcp_mstamp_refresh(tp);
	अगर (!push_one) अणु
		/* Do MTU probing. */
		result = tcp_mtu_probe(sk);
		अगर (!result) अणु
			वापस false;
		पूर्ण अन्यथा अगर (result > 0) अणु
			sent_pkts = 1;
		पूर्ण
	पूर्ण

	max_segs = tcp_tso_segs(sk, mss_now);
	जबतक ((skb = tcp_send_head(sk))) अणु
		अचिन्हित पूर्णांक limit;

		अगर (unlikely(tp->repair) && tp->repair_queue == TCP_SEND_QUEUE) अणु
			/* "skb_mstamp_ns" is used as a start poपूर्णांक क्रम the retransmit समयr */
			skb->skb_mstamp_ns = tp->tcp_wstamp_ns = tp->tcp_घड़ी_cache;
			list_move_tail(&skb->tcp_tsorted_anchor, &tp->tsorted_sent_queue);
			tcp_init_tso_segs(skb, mss_now);
			जाओ repair; /* Skip network transmission */
		पूर्ण

		अगर (tcp_pacing_check(sk))
			अवरोध;

		tso_segs = tcp_init_tso_segs(skb, mss_now);
		BUG_ON(!tso_segs);

		cwnd_quota = tcp_cwnd_test(tp, skb);
		अगर (!cwnd_quota) अणु
			अगर (push_one == 2)
				/* Force out a loss probe pkt. */
				cwnd_quota = 1;
			अन्यथा
				अवरोध;
		पूर्ण

		अगर (unlikely(!tcp_snd_wnd_test(tp, skb, mss_now))) अणु
			is_rwnd_limited = true;
			अवरोध;
		पूर्ण

		अगर (tso_segs == 1) अणु
			अगर (unlikely(!tcp_nagle_test(tp, skb, mss_now,
						     (tcp_skb_is_last(sk, skb) ?
						      nonagle : TCP_NAGLE_PUSH))))
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (!push_one &&
			    tcp_tso_should_defer(sk, skb, &is_cwnd_limited,
						 &is_rwnd_limited, max_segs))
				अवरोध;
		पूर्ण

		limit = mss_now;
		अगर (tso_segs > 1 && !tcp_urg_mode(tp))
			limit = tcp_mss_split_poपूर्णांक(sk, skb, mss_now,
						    min_t(अचिन्हित पूर्णांक,
							  cwnd_quota,
							  max_segs),
						    nonagle);

		अगर (skb->len > limit &&
		    unlikely(tso_fragment(sk, skb, limit, mss_now, gfp)))
			अवरोध;

		अगर (tcp_small_queue_check(sk, skb, 0))
			अवरोध;

		/* Argh, we hit an empty skb(), presumably a thपढ़ो
		 * is sleeping in sendmsg()/sk_stream_रुको_memory().
		 * We करो not want to send a pure-ack packet and have
		 * a strange looking rtx queue with empty packet(s).
		 */
		अगर (TCP_SKB_CB(skb)->end_seq == TCP_SKB_CB(skb)->seq)
			अवरोध;

		अगर (unlikely(tcp_transmit_skb(sk, skb, 1, gfp)))
			अवरोध;

repair:
		/* Advance the send_head.  This one is sent out.
		 * This call will increment packets_out.
		 */
		tcp_event_new_data_sent(sk, skb);

		tcp_minshall_update(tp, mss_now, skb);
		sent_pkts += tcp_skb_pcount(skb);

		अगर (push_one)
			अवरोध;
	पूर्ण

	अगर (is_rwnd_limited)
		tcp_chrono_start(sk, TCP_CHRONO_RWND_LIMITED);
	अन्यथा
		tcp_chrono_stop(sk, TCP_CHRONO_RWND_LIMITED);

	is_cwnd_limited |= (tcp_packets_in_flight(tp) >= tp->snd_cwnd);
	अगर (likely(sent_pkts || is_cwnd_limited))
		tcp_cwnd_validate(sk, is_cwnd_limited);

	अगर (likely(sent_pkts)) अणु
		अगर (tcp_in_cwnd_reduction(sk))
			tp->prr_out += sent_pkts;

		/* Send one loss probe per tail loss episode. */
		अगर (push_one != 2)
			tcp_schedule_loss_probe(sk, false);
		वापस false;
	पूर्ण
	वापस !tp->packets_out && !tcp_ग_लिखो_queue_empty(sk);
पूर्ण

bool tcp_schedule_loss_probe(काष्ठा sock *sk, bool advancing_rto)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 समयout, rto_delta_us;
	पूर्णांक early_retrans;

	/* Don't करो any loss probe on a Fast Open connection beक्रमe 3WHS
	 * finishes.
	 */
	अगर (rcu_access_poपूर्णांकer(tp->fastखोलो_rsk))
		वापस false;

	early_retrans = sock_net(sk)->ipv4.sysctl_tcp_early_retrans;
	/* Schedule a loss probe in 2*RTT क्रम SACK capable connections
	 * not in loss recovery, that are either limited by cwnd or application.
	 */
	अगर ((early_retrans != 3 && early_retrans != 4) ||
	    !tp->packets_out || !tcp_is_sack(tp) ||
	    (icsk->icsk_ca_state != TCP_CA_Open &&
	     icsk->icsk_ca_state != TCP_CA_CWR))
		वापस false;

	/* Probe समयout is 2*rtt. Add minimum RTO to account
	 * क्रम delayed ack when there's one outstanding packet. If no RTT
	 * sample is available then probe after TCP_TIMEOUT_INIT.
	 */
	अगर (tp->srtt_us) अणु
		समयout = usecs_to_jअगरfies(tp->srtt_us >> 2);
		अगर (tp->packets_out == 1)
			समयout += TCP_RTO_MIN;
		अन्यथा
			समयout += TCP_TIMEOUT_MIN;
	पूर्ण अन्यथा अणु
		समयout = TCP_TIMEOUT_INIT;
	पूर्ण

	/* If the RTO क्रमmula yields an earlier समय, then use that समय. */
	rto_delta_us = advancing_rto ?
			jअगरfies_to_usecs(inet_csk(sk)->icsk_rto) :
			tcp_rto_delta_us(sk);  /* How far in future is RTO? */
	अगर (rto_delta_us > 0)
		समयout = min_t(u32, समयout, usecs_to_jअगरfies(rto_delta_us));

	tcp_reset_xmit_समयr(sk, ICSK_TIME_LOSS_PROBE, समयout, TCP_RTO_MAX);
	वापस true;
पूर्ण

/* Thanks to skb fast clones, we can detect अगर a prior transmit of
 * a packet is still in a qdisc or driver queue.
 * In this हाल, there is very little poपूर्णांक करोing a retransmit !
 */
अटल bool skb_still_in_host_queue(काष्ठा sock *sk,
				    स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (unlikely(skb_fclone_busy(sk, skb))) अणु
		set_bit(TSQ_THROTTLED, &sk->sk_tsq_flags);
		smp_mb__after_atomic();
		अगर (skb_fclone_busy(sk, skb)) अणु
			NET_INC_STATS(sock_net(sk),
				      LINUX_MIB_TCPSPURIOUS_RTX_HOSTQUEUES);
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

/* When probe समयout (PTO) fires, try send a new segment अगर possible, अन्यथा
 * retransmit the last segment.
 */
व्योम tcp_send_loss_probe(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *skb;
	पूर्णांक pcount;
	पूर्णांक mss = tcp_current_mss(sk);

	/* At most one outstanding TLP */
	अगर (tp->tlp_high_seq)
		जाओ rearm_समयr;

	tp->tlp_retrans = 0;
	skb = tcp_send_head(sk);
	अगर (skb && tcp_snd_wnd_test(tp, skb, mss)) अणु
		pcount = tp->packets_out;
		tcp_ग_लिखो_xmit(sk, mss, TCP_NAGLE_OFF, 2, GFP_ATOMIC);
		अगर (tp->packets_out > pcount)
			जाओ probe_sent;
		जाओ rearm_समयr;
	पूर्ण
	skb = skb_rb_last(&sk->tcp_rtx_queue);
	अगर (unlikely(!skb)) अणु
		WARN_ONCE(tp->packets_out,
			  "invalid inflight: %u state %u cwnd %u mss %d\n",
			  tp->packets_out, sk->sk_state, tp->snd_cwnd, mss);
		inet_csk(sk)->icsk_pending = 0;
		वापस;
	पूर्ण

	अगर (skb_still_in_host_queue(sk, skb))
		जाओ rearm_समयr;

	pcount = tcp_skb_pcount(skb);
	अगर (WARN_ON(!pcount))
		जाओ rearm_समयr;

	अगर ((pcount > 1) && (skb->len > (pcount - 1) * mss)) अणु
		अगर (unlikely(tcp_fragment(sk, TCP_FRAG_IN_RTX_QUEUE, skb,
					  (pcount - 1) * mss, mss,
					  GFP_ATOMIC)))
			जाओ rearm_समयr;
		skb = skb_rb_next(skb);
	पूर्ण

	अगर (WARN_ON(!skb || !tcp_skb_pcount(skb)))
		जाओ rearm_समयr;

	अगर (__tcp_retransmit_skb(sk, skb, 1))
		जाओ rearm_समयr;

	tp->tlp_retrans = 1;

probe_sent:
	/* Record snd_nxt क्रम loss detection. */
	tp->tlp_high_seq = tp->snd_nxt;

	NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPLOSSPROBES);
	/* Reset s.t. tcp_rearm_rto will restart समयr from now */
	inet_csk(sk)->icsk_pending = 0;
rearm_समयr:
	tcp_rearm_rto(sk);
पूर्ण

/* Push out any pending frames which were held back due to
 * TCP_CORK or attempt at coalescing tiny packets.
 * The socket must be locked by the caller.
 */
व्योम __tcp_push_pending_frames(काष्ठा sock *sk, अचिन्हित पूर्णांक cur_mss,
			       पूर्णांक nonagle)
अणु
	/* If we are बंदd, the bytes will have to reमुख्य here.
	 * In समय बंदकरोwn will finish, we empty the ग_लिखो queue and
	 * all will be happy.
	 */
	अगर (unlikely(sk->sk_state == TCP_CLOSE))
		वापस;

	अगर (tcp_ग_लिखो_xmit(sk, cur_mss, nonagle, 0,
			   sk_gfp_mask(sk, GFP_ATOMIC)))
		tcp_check_probe_समयr(sk);
पूर्ण

/* Send _single_ skb sitting at the send head. This function requires
 * true push pending frames to setup probe समयr etc.
 */
व्योम tcp_push_one(काष्ठा sock *sk, अचिन्हित पूर्णांक mss_now)
अणु
	काष्ठा sk_buff *skb = tcp_send_head(sk);

	BUG_ON(!skb || skb->len < mss_now);

	tcp_ग_लिखो_xmit(sk, mss_now, TCP_NAGLE_PUSH, 1, sk->sk_allocation);
पूर्ण

/* This function वापसs the amount that we can उठाओ the
 * usable winकरोw based on the following स्थिरraपूर्णांकs
 *
 * 1. The winकरोw can never be shrunk once it is offered (RFC 793)
 * 2. We limit memory per socket
 *
 * RFC 1122:
 * "the suggested [SWS] aव्योमance algorithm क्रम the receiver is to keep
 *  RECV.NEXT + RCV.WIN fixed until:
 *  RCV.BUFF - RCV.USER - RCV.WINDOW >= min(1/2 RCV.BUFF, MSS)"
 *
 * i.e. करोn't उठाओ the right edge of the winकरोw until you can उठाओ
 * it at least MSS bytes.
 *
 * Unक्रमtunately, the recommended algorithm अवरोधs header prediction,
 * since header prediction assumes th->winकरोw stays fixed.
 *
 * Strictly speaking, keeping th->winकरोw fixed violates the receiver
 * side SWS prevention criteria. The problem is that under this rule
 * a stream of single byte packets will cause the right side of the
 * winकरोw to always advance by a single byte.
 *
 * Of course, अगर the sender implements sender side SWS prevention
 * then this will not be a problem.
 *
 * BSD seems to make the following compromise:
 *
 *	If the मुक्त space is less than the 1/4 of the maximum
 *	space available and the मुक्त space is less than 1/2 mss,
 *	then set the winकरोw to 0.
 *	[ Actually, bsd uses MSS and 1/4 of maximal _winकरोw_ ]
 *	Otherwise, just prevent the winकरोw from shrinking
 *	and from being larger than the largest representable value.
 *
 * This prevents incremental खोलोing of the winकरोw in the regime
 * where TCP is limited by the speed of the पढ़ोer side taking
 * data out of the TCP receive queue. It करोes nothing about
 * those हालs where the winकरोw is स्थिरrained on the sender side
 * because the pipeline is full.
 *
 * BSD also seems to "accidentally" limit itself to winकरोws that are a
 * multiple of MSS, at least until the मुक्त space माला_लो quite small.
 * This would appear to be a side effect of the mbuf implementation.
 * Combining these two algorithms results in the observed behavior
 * of having a fixed winकरोw size at almost all बार.
 *
 * Below we obtain similar behavior by क्रमcing the offered winकरोw to
 * a multiple of the mss when it is feasible to करो so.
 *
 * Note, we करोn't "adjust" क्रम TIMESTAMP or SACK option bytes.
 * Regular options like TIMESTAMP are taken पूर्णांकo account.
 */
u32 __tcp_select_winकरोw(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	/* MSS क्रम the peer's data.  Previous versions used mss_clamp
	 * here.  I करोn't know अगर the value based on our guesses
	 * of peer's MSS is better for the performance.  It's more correct
	 * but may be worse क्रम the perक्रमmance because of rcv_mss
	 * fluctuations.  --SAW  1998/11/1
	 */
	पूर्णांक mss = icsk->icsk_ack.rcv_mss;
	पूर्णांक मुक्त_space = tcp_space(sk);
	पूर्णांक allowed_space = tcp_full_space(sk);
	पूर्णांक full_space, winकरोw;

	अगर (sk_is_mptcp(sk))
		mptcp_space(sk, &मुक्त_space, &allowed_space);

	full_space = min_t(पूर्णांक, tp->winकरोw_clamp, allowed_space);

	अगर (unlikely(mss > full_space)) अणु
		mss = full_space;
		अगर (mss <= 0)
			वापस 0;
	पूर्ण
	अगर (मुक्त_space < (full_space >> 1)) अणु
		icsk->icsk_ack.quick = 0;

		अगर (tcp_under_memory_pressure(sk))
			tp->rcv_ssthresh = min(tp->rcv_ssthresh,
					       4U * tp->advmss);

		/* मुक्त_space might become our new winकरोw, make sure we करोn't
		 * increase it due to wscale.
		 */
		मुक्त_space = round_करोwn(मुक्त_space, 1 << tp->rx_opt.rcv_wscale);

		/* अगर मुक्त space is less than mss estimate, or is below 1/16th
		 * of the maximum allowed, try to move to zero-winकरोw, अन्यथा
		 * tcp_clamp_winकरोw() will grow rcv buf up to tcp_rmem[2], and
		 * new incoming data is dropped due to memory limits.
		 * With large winकरोw, mss test triggers way too late in order
		 * to announce zero winकरोw in समय beक्रमe rmem limit kicks in.
		 */
		अगर (मुक्त_space < (allowed_space >> 4) || मुक्त_space < mss)
			वापस 0;
	पूर्ण

	अगर (मुक्त_space > tp->rcv_ssthresh)
		मुक्त_space = tp->rcv_ssthresh;

	/* Don't करो rounding अगर we are using winकरोw scaling, since the
	 * scaled winकरोw will not line up with the MSS boundary anyway.
	 */
	अगर (tp->rx_opt.rcv_wscale) अणु
		winकरोw = मुक्त_space;

		/* Advertise enough space so that it won't get scaled away.
		 * Import हाल: prevent zero winकरोw announcement अगर
		 * 1<<rcv_wscale > mss.
		 */
		winकरोw = ALIGN(winकरोw, (1 << tp->rx_opt.rcv_wscale));
	पूर्ण अन्यथा अणु
		winकरोw = tp->rcv_wnd;
		/* Get the largest winकरोw that is a nice multiple of mss.
		 * Winकरोw clamp alपढ़ोy applied above.
		 * If our current winकरोw offering is within 1 mss of the
		 * मुक्त space we just keep it. This prevents the भागide
		 * and multiply from happening most of the समय.
		 * We also करोn't करो any winकरोw rounding when the मुक्त space
		 * is too small.
		 */
		अगर (winकरोw <= मुक्त_space - mss || winकरोw > मुक्त_space)
			winकरोw = roundकरोwn(मुक्त_space, mss);
		अन्यथा अगर (mss == full_space &&
			 मुक्त_space > winकरोw + (full_space >> 1))
			winकरोw = मुक्त_space;
	पूर्ण

	वापस winकरोw;
पूर्ण

व्योम tcp_skb_collapse_tstamp(काष्ठा sk_buff *skb,
			     स्थिर काष्ठा sk_buff *next_skb)
अणु
	अगर (unlikely(tcp_has_tx_tstamp(next_skb))) अणु
		स्थिर काष्ठा skb_shared_info *next_shinfo =
			skb_shinfo(next_skb);
		काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);

		shinfo->tx_flags |= next_shinfo->tx_flags & SKBTX_ANY_TSTAMP;
		shinfo->tskey = next_shinfo->tskey;
		TCP_SKB_CB(skb)->txstamp_ack |=
			TCP_SKB_CB(next_skb)->txstamp_ack;
	पूर्ण
पूर्ण

/* Collapses two adjacent SKB's during retransmission. */
अटल bool tcp_collapse_retrans(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *next_skb = skb_rb_next(skb);
	पूर्णांक next_skb_size;

	next_skb_size = next_skb->len;

	BUG_ON(tcp_skb_pcount(skb) != 1 || tcp_skb_pcount(next_skb) != 1);

	अगर (next_skb_size) अणु
		अगर (next_skb_size <= skb_availroom(skb))
			skb_copy_bits(next_skb, 0, skb_put(skb, next_skb_size),
				      next_skb_size);
		अन्यथा अगर (!tcp_skb_shअगरt(skb, next_skb, 1, next_skb_size))
			वापस false;
	पूर्ण
	tcp_highest_sack_replace(sk, next_skb, skb);

	/* Update sequence range on original skb. */
	TCP_SKB_CB(skb)->end_seq = TCP_SKB_CB(next_skb)->end_seq;

	/* Merge over control inक्रमmation. This moves PSH/FIN etc. over */
	TCP_SKB_CB(skb)->tcp_flags |= TCP_SKB_CB(next_skb)->tcp_flags;

	/* All करोne, get rid of second SKB and account क्रम it so
	 * packet counting करोes not अवरोध.
	 */
	TCP_SKB_CB(skb)->sacked |= TCP_SKB_CB(next_skb)->sacked & TCPCB_EVER_RETRANS;
	TCP_SKB_CB(skb)->eor = TCP_SKB_CB(next_skb)->eor;

	/* changed transmit queue under us so clear hपूर्णांकs */
	tcp_clear_retrans_hपूर्णांकs_partial(tp);
	अगर (next_skb == tp->retransmit_skb_hपूर्णांक)
		tp->retransmit_skb_hपूर्णांक = skb;

	tcp_adjust_pcount(sk, next_skb, tcp_skb_pcount(next_skb));

	tcp_skb_collapse_tstamp(skb, next_skb);

	tcp_rtx_queue_unlink_and_मुक्त(next_skb, sk);
	वापस true;
पूर्ण

/* Check अगर coalescing SKBs is legal. */
अटल bool tcp_can_collapse(स्थिर काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (tcp_skb_pcount(skb) > 1)
		वापस false;
	अगर (skb_cloned(skb))
		वापस false;
	/* Some heuristics क्रम collapsing over SACK'd could be invented */
	अगर (TCP_SKB_CB(skb)->sacked & TCPCB_SACKED_ACKED)
		वापस false;

	वापस true;
पूर्ण

/* Collapse packets in the retransmit queue to make to create
 * less packets on the wire. This is only करोne on retransmission.
 */
अटल व्योम tcp_retrans_try_collapse(काष्ठा sock *sk, काष्ठा sk_buff *to,
				     पूर्णांक space)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *skb = to, *पंचांगp;
	bool first = true;

	अगर (!sock_net(sk)->ipv4.sysctl_tcp_retrans_collapse)
		वापस;
	अगर (TCP_SKB_CB(skb)->tcp_flags & TCPHDR_SYN)
		वापस;

	skb_rbtree_walk_from_safe(skb, पंचांगp) अणु
		अगर (!tcp_can_collapse(sk, skb))
			अवरोध;

		अगर (!tcp_skb_can_collapse(to, skb))
			अवरोध;

		space -= skb->len;

		अगर (first) अणु
			first = false;
			जारी;
		पूर्ण

		अगर (space < 0)
			अवरोध;

		अगर (after(TCP_SKB_CB(skb)->end_seq, tcp_wnd_end(tp)))
			अवरोध;

		अगर (!tcp_collapse_retrans(sk, to))
			अवरोध;
	पूर्ण
पूर्ण

/* This retransmits one SKB.  Policy decisions and retransmit queue
 * state updates are करोne by the caller.  Returns non-zero अगर an
 * error occurred which prevented the send.
 */
पूर्णांक __tcp_retransmit_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक segs)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	अचिन्हित पूर्णांक cur_mss;
	पूर्णांक dअगरf, len, err;


	/* Inconclusive MTU probe */
	अगर (icsk->icsk_mtup.probe_size)
		icsk->icsk_mtup.probe_size = 0;

	अगर (skb_still_in_host_queue(sk, skb))
		वापस -EBUSY;

	अगर (beक्रमe(TCP_SKB_CB(skb)->seq, tp->snd_una)) अणु
		अगर (unlikely(beक्रमe(TCP_SKB_CB(skb)->end_seq, tp->snd_una))) अणु
			WARN_ON_ONCE(1);
			वापस -EINVAL;
		पूर्ण
		अगर (tcp_trim_head(sk, skb, tp->snd_una - TCP_SKB_CB(skb)->seq))
			वापस -ENOMEM;
	पूर्ण

	अगर (inet_csk(sk)->icsk_af_ops->rebuild_header(sk))
		वापस -EHOSTUNREACH; /* Routing failure or similar. */

	cur_mss = tcp_current_mss(sk);

	/* If receiver has shrunk his winकरोw, and skb is out of
	 * new winकरोw, करो not retransmit it. The exception is the
	 * हाल, when winकरोw is shrunk to zero. In this हाल
	 * our retransmit serves as a zero winकरोw probe.
	 */
	अगर (!beक्रमe(TCP_SKB_CB(skb)->seq, tcp_wnd_end(tp)) &&
	    TCP_SKB_CB(skb)->seq != tp->snd_una)
		वापस -EAGAIN;

	len = cur_mss * segs;
	अगर (skb->len > len) अणु
		अगर (tcp_fragment(sk, TCP_FRAG_IN_RTX_QUEUE, skb, len,
				 cur_mss, GFP_ATOMIC))
			वापस -ENOMEM; /* We'll try again later. */
	पूर्ण अन्यथा अणु
		अगर (skb_unclone(skb, GFP_ATOMIC))
			वापस -ENOMEM;

		dअगरf = tcp_skb_pcount(skb);
		tcp_set_skb_tso_segs(skb, cur_mss);
		dअगरf -= tcp_skb_pcount(skb);
		अगर (dअगरf)
			tcp_adjust_pcount(sk, skb, dअगरf);
		अगर (skb->len < cur_mss)
			tcp_retrans_try_collapse(sk, skb, cur_mss);
	पूर्ण

	/* RFC3168, section 6.1.1.1. ECN fallback */
	अगर ((TCP_SKB_CB(skb)->tcp_flags & TCPHDR_SYN_ECN) == TCPHDR_SYN_ECN)
		tcp_ecn_clear_syn(sk, skb);

	/* Update global and local TCP statistics. */
	segs = tcp_skb_pcount(skb);
	TCP_ADD_STATS(sock_net(sk), TCP_MIB_RETRANSSEGS, segs);
	अगर (TCP_SKB_CB(skb)->tcp_flags & TCPHDR_SYN)
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPSYNRETRANS);
	tp->total_retrans += segs;
	tp->bytes_retrans += skb->len;

	/* make sure skb->data is aligned on arches that require it
	 * and check अगर ack-trimming & collapsing extended the headroom
	 * beyond what csum_start can cover.
	 */
	अगर (unlikely((NET_IP_ALIGN && ((अचिन्हित दीर्घ)skb->data & 3)) ||
		     skb_headroom(skb) >= 0xFFFF)) अणु
		काष्ठा sk_buff *nskb;

		tcp_skb_tsorted_save(skb) अणु
			nskb = __pskb_copy(skb, MAX_TCP_HEADER, GFP_ATOMIC);
			अगर (nskb) अणु
				nskb->dev = शून्य;
				err = tcp_transmit_skb(sk, nskb, 0, GFP_ATOMIC);
			पूर्ण अन्यथा अणु
				err = -ENOBUFS;
			पूर्ण
		पूर्ण tcp_skb_tsorted_restore(skb);

		अगर (!err) अणु
			tcp_update_skb_after_send(sk, skb, tp->tcp_wstamp_ns);
			tcp_rate_skb_sent(sk, skb);
		पूर्ण
	पूर्ण अन्यथा अणु
		err = tcp_transmit_skb(sk, skb, 1, GFP_ATOMIC);
	पूर्ण

	/* To aव्योम taking spuriously low RTT samples based on a बारtamp
	 * क्रम a transmit that never happened, always mark EVER_RETRANS
	 */
	TCP_SKB_CB(skb)->sacked |= TCPCB_EVER_RETRANS;

	अगर (BPF_SOCK_OPS_TEST_FLAG(tp, BPF_SOCK_OPS_RETRANS_CB_FLAG))
		tcp_call_bpf_3arg(sk, BPF_SOCK_OPS_RETRANS_CB,
				  TCP_SKB_CB(skb)->seq, segs, err);

	अगर (likely(!err)) अणु
		trace_tcp_retransmit_skb(sk, skb);
	पूर्ण अन्यथा अगर (err != -EBUSY) अणु
		NET_ADD_STATS(sock_net(sk), LINUX_MIB_TCPRETRANSFAIL, segs);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक tcp_retransmit_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक segs)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	पूर्णांक err = __tcp_retransmit_skb(sk, skb, segs);

	अगर (err == 0) अणु
#अगर FASTRETRANS_DEBUG > 0
		अगर (TCP_SKB_CB(skb)->sacked & TCPCB_SACKED_RETRANS) अणु
			net_dbg_ratelimited("retrans_out leaked\n");
		पूर्ण
#पूर्ण_अगर
		TCP_SKB_CB(skb)->sacked |= TCPCB_RETRANS;
		tp->retrans_out += tcp_skb_pcount(skb);
	पूर्ण

	/* Save stamp of the first (attempted) retransmit. */
	अगर (!tp->retrans_stamp)
		tp->retrans_stamp = tcp_skb_बारtamp(skb);

	अगर (tp->unकरो_retrans < 0)
		tp->unकरो_retrans = 0;
	tp->unकरो_retrans += tcp_skb_pcount(skb);
	वापस err;
पूर्ण

/* This माला_लो called after a retransmit समयout, and the initially
 * retransmitted data is acknowledged.  It tries to जारी
 * resending the rest of the retransmit queue, until either
 * we've sent it all or the congestion winकरोw limit is reached.
 */
व्योम tcp_xmit_retransmit_queue(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा sk_buff *skb, *rtx_head, *hole = शून्य;
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	bool rearm_समयr = false;
	u32 max_segs;
	पूर्णांक mib_idx;

	अगर (!tp->packets_out)
		वापस;

	rtx_head = tcp_rtx_queue_head(sk);
	skb = tp->retransmit_skb_hपूर्णांक ?: rtx_head;
	max_segs = tcp_tso_segs(sk, tcp_current_mss(sk));
	skb_rbtree_walk_from(skb) अणु
		__u8 sacked;
		पूर्णांक segs;

		अगर (tcp_pacing_check(sk))
			अवरोध;

		/* we could करो better than to assign each समय */
		अगर (!hole)
			tp->retransmit_skb_hपूर्णांक = skb;

		segs = tp->snd_cwnd - tcp_packets_in_flight(tp);
		अगर (segs <= 0)
			अवरोध;
		sacked = TCP_SKB_CB(skb)->sacked;
		/* In हाल tcp_shअगरt_skb_data() have aggregated large skbs,
		 * we need to make sure not sending too bigs TSO packets
		 */
		segs = min_t(पूर्णांक, segs, max_segs);

		अगर (tp->retrans_out >= tp->lost_out) अणु
			अवरोध;
		पूर्ण अन्यथा अगर (!(sacked & TCPCB_LOST)) अणु
			अगर (!hole && !(sacked & (TCPCB_SACKED_RETRANS|TCPCB_SACKED_ACKED)))
				hole = skb;
			जारी;

		पूर्ण अन्यथा अणु
			अगर (icsk->icsk_ca_state != TCP_CA_Loss)
				mib_idx = LINUX_MIB_TCPFASTRETRANS;
			अन्यथा
				mib_idx = LINUX_MIB_TCPSLOWSTARTRETRANS;
		पूर्ण

		अगर (sacked & (TCPCB_SACKED_ACKED|TCPCB_SACKED_RETRANS))
			जारी;

		अगर (tcp_small_queue_check(sk, skb, 1))
			अवरोध;

		अगर (tcp_retransmit_skb(sk, skb, segs))
			अवरोध;

		NET_ADD_STATS(sock_net(sk), mib_idx, tcp_skb_pcount(skb));

		अगर (tcp_in_cwnd_reduction(sk))
			tp->prr_out += tcp_skb_pcount(skb);

		अगर (skb == rtx_head &&
		    icsk->icsk_pending != ICSK_TIME_REO_TIMEOUT)
			rearm_समयr = true;

	पूर्ण
	अगर (rearm_समयr)
		tcp_reset_xmit_समयr(sk, ICSK_TIME_RETRANS,
				     inet_csk(sk)->icsk_rto,
				     TCP_RTO_MAX);
पूर्ण

/* We allow to exceed memory limits क्रम FIN packets to expedite
 * connection tear करोwn and (memory) recovery.
 * Otherwise tcp_send_fin() could be tempted to either delay FIN
 * or even be क्रमced to बंद flow without any FIN.
 * In general, we want to allow one skb per socket to aव्योम hangs
 * with edge trigger epoll()
 */
व्योम sk_क्रमced_mem_schedule(काष्ठा sock *sk, पूर्णांक size)
अणु
	पूर्णांक amt;

	अगर (size <= sk->sk_क्रमward_alloc)
		वापस;
	amt = sk_mem_pages(size);
	sk->sk_क्रमward_alloc += amt * SK_MEM_QUANTUM;
	sk_memory_allocated_add(sk, amt);

	अगर (mem_cgroup_sockets_enabled && sk->sk_memcg)
		mem_cgroup_अक्षरge_skmem(sk->sk_memcg, amt);
पूर्ण

/* Send a FIN. The caller locks the socket क्रम us.
 * We should try to send a FIN packet really hard, but eventually give up.
 */
व्योम tcp_send_fin(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb, *tskb, *tail = tcp_ग_लिखो_queue_tail(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	/* Optimization, tack on the FIN अगर we have one skb in ग_लिखो queue and
	 * this skb was not yet sent, or we are under memory pressure.
	 * Note: in the latter हाल, FIN packet will be sent after a समयout,
	 * as TCP stack thinks it has alपढ़ोy been transmitted.
	 */
	tskb = tail;
	अगर (!tskb && tcp_under_memory_pressure(sk))
		tskb = skb_rb_last(&sk->tcp_rtx_queue);

	अगर (tskb) अणु
		TCP_SKB_CB(tskb)->tcp_flags |= TCPHDR_FIN;
		TCP_SKB_CB(tskb)->end_seq++;
		tp->ग_लिखो_seq++;
		अगर (!tail) अणु
			/* This means tskb was alपढ़ोy sent.
			 * Pretend we included the FIN on previous transmit.
			 * We need to set tp->snd_nxt to the value it would have
			 * अगर FIN had been sent. This is because retransmit path
			 * करोes not change tp->snd_nxt.
			 */
			WRITE_ONCE(tp->snd_nxt, tp->snd_nxt + 1);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		skb = alloc_skb_fclone(MAX_TCP_HEADER, sk->sk_allocation);
		अगर (unlikely(!skb))
			वापस;

		INIT_LIST_HEAD(&skb->tcp_tsorted_anchor);
		skb_reserve(skb, MAX_TCP_HEADER);
		sk_क्रमced_mem_schedule(sk, skb->truesize);
		/* FIN eats a sequence byte, ग_लिखो_seq advanced by tcp_queue_skb(). */
		tcp_init_nondata_skb(skb, tp->ग_लिखो_seq,
				     TCPHDR_ACK | TCPHDR_FIN);
		tcp_queue_skb(sk, skb);
	पूर्ण
	__tcp_push_pending_frames(sk, tcp_current_mss(sk), TCP_NAGLE_OFF);
पूर्ण

/* We get here when a process बंदs a file descriptor (either due to
 * an explicit बंद() or as a byproduct of निकास()'ing) and there
 * was unपढ़ो data in the receive queue.  This behavior is recommended
 * by RFC 2525, section 2.17.  -DaveM
 */
व्योम tcp_send_active_reset(काष्ठा sock *sk, gfp_t priority)
अणु
	काष्ठा sk_buff *skb;

	TCP_INC_STATS(sock_net(sk), TCP_MIB_OUTRSTS);

	/* NOTE: No TCP options attached and we never retransmit this. */
	skb = alloc_skb(MAX_TCP_HEADER, priority);
	अगर (!skb) अणु
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPABORTFAILED);
		वापस;
	पूर्ण

	/* Reserve space क्रम headers and prepare control bits. */
	skb_reserve(skb, MAX_TCP_HEADER);
	tcp_init_nondata_skb(skb, tcp_acceptable_seq(sk),
			     TCPHDR_ACK | TCPHDR_RST);
	tcp_mstamp_refresh(tcp_sk(sk));
	/* Send it off. */
	अगर (tcp_transmit_skb(sk, skb, 0, priority))
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPABORTFAILED);

	/* skb of trace_tcp_send_reset() keeps the skb that caused RST,
	 * skb here is dअगरferent to the troublesome skb, so use शून्य
	 */
	trace_tcp_send_reset(sk, शून्य);
पूर्ण

/* Send a crossed SYN-ACK during socket establishment.
 * WARNING: This routine must only be called when we have alपढ़ोy sent
 * a SYN packet that crossed the incoming SYN that caused this routine
 * to get called. If this assumption fails then the initial rcv_wnd
 * and rcv_wscale values will not be correct.
 */
पूर्णांक tcp_send_synack(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb;

	skb = tcp_rtx_queue_head(sk);
	अगर (!skb || !(TCP_SKB_CB(skb)->tcp_flags & TCPHDR_SYN)) अणु
		pr_err("%s: wrong queue state\n", __func__);
		वापस -EFAULT;
	पूर्ण
	अगर (!(TCP_SKB_CB(skb)->tcp_flags & TCPHDR_ACK)) अणु
		अगर (skb_cloned(skb)) अणु
			काष्ठा sk_buff *nskb;

			tcp_skb_tsorted_save(skb) अणु
				nskb = skb_copy(skb, GFP_ATOMIC);
			पूर्ण tcp_skb_tsorted_restore(skb);
			अगर (!nskb)
				वापस -ENOMEM;
			INIT_LIST_HEAD(&nskb->tcp_tsorted_anchor);
			tcp_highest_sack_replace(sk, skb, nskb);
			tcp_rtx_queue_unlink_and_मुक्त(skb, sk);
			__skb_header_release(nskb);
			tcp_rbtree_insert(&sk->tcp_rtx_queue, nskb);
			sk_wmem_queued_add(sk, nskb->truesize);
			sk_mem_अक्षरge(sk, nskb->truesize);
			skb = nskb;
		पूर्ण

		TCP_SKB_CB(skb)->tcp_flags |= TCPHDR_ACK;
		tcp_ecn_send_synack(sk, skb);
	पूर्ण
	वापस tcp_transmit_skb(sk, skb, 1, GFP_ATOMIC);
पूर्ण

/**
 * tcp_make_synack - Allocate one skb and build a SYNACK packet.
 * @sk: listener socket
 * @dst: dst entry attached to the SYNACK. It is consumed and caller
 *       should not use it again.
 * @req: request_sock poपूर्णांकer
 * @foc: cookie क्रम tcp fast खोलो
 * @synack_type: Type of synack to prepare
 * @syn_skb: SYN packet just received.  It could be शून्य क्रम rtx हाल.
 */
काष्ठा sk_buff *tcp_make_synack(स्थिर काष्ठा sock *sk, काष्ठा dst_entry *dst,
				काष्ठा request_sock *req,
				काष्ठा tcp_fastखोलो_cookie *foc,
				क्रमागत tcp_synack_type synack_type,
				काष्ठा sk_buff *syn_skb)
अणु
	काष्ठा inet_request_sock *ireq = inet_rsk(req);
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा tcp_md5sig_key *md5 = शून्य;
	काष्ठा tcp_out_options opts;
	काष्ठा sk_buff *skb;
	पूर्णांक tcp_header_size;
	काष्ठा tcphdr *th;
	पूर्णांक mss;
	u64 now;

	skb = alloc_skb(MAX_TCP_HEADER, GFP_ATOMIC);
	अगर (unlikely(!skb)) अणु
		dst_release(dst);
		वापस शून्य;
	पूर्ण
	/* Reserve space क्रम headers. */
	skb_reserve(skb, MAX_TCP_HEADER);

	चयन (synack_type) अणु
	हाल TCP_SYNACK_NORMAL:
		skb_set_owner_w(skb, req_to_sk(req));
		अवरोध;
	हाल TCP_SYNACK_COOKIE:
		/* Under synflood, we करो not attach skb to a socket,
		 * to aव्योम false sharing.
		 */
		अवरोध;
	हाल TCP_SYNACK_FASTOPEN:
		/* sk is a स्थिर poपूर्णांकer, because we want to express multiple
		 * cpu might call us concurrently.
		 * sk->sk_wmem_alloc in an atomic, we can promote to rw.
		 */
		skb_set_owner_w(skb, (काष्ठा sock *)sk);
		अवरोध;
	पूर्ण
	skb_dst_set(skb, dst);

	mss = tcp_mss_clamp(tp, dst_metric_advmss(dst));

	स_रखो(&opts, 0, माप(opts));
	now = tcp_घड़ी_ns();
#अगर_घोषित CONFIG_SYN_COOKIES
	अगर (unlikely(synack_type == TCP_SYNACK_COOKIE && ireq->tstamp_ok))
		skb->skb_mstamp_ns = cookie_init_बारtamp(req, now);
	अन्यथा
#पूर्ण_अगर
	अणु
		skb->skb_mstamp_ns = now;
		अगर (!tcp_rsk(req)->snt_synack) /* Timestamp first SYNACK */
			tcp_rsk(req)->snt_synack = tcp_skb_बारtamp_us(skb);
	पूर्ण

#अगर_घोषित CONFIG_TCP_MD5SIG
	rcu_पढ़ो_lock();
	md5 = tcp_rsk(req)->af_specअगरic->req_md5_lookup(sk, req_to_sk(req));
#पूर्ण_अगर
	skb_set_hash(skb, tcp_rsk(req)->txhash, PKT_HASH_TYPE_L4);
	/* bpf program will be पूर्णांकerested in the tcp_flags */
	TCP_SKB_CB(skb)->tcp_flags = TCPHDR_SYN | TCPHDR_ACK;
	tcp_header_size = tcp_synack_options(sk, req, mss, skb, &opts, md5,
					     foc, synack_type,
					     syn_skb) + माप(*th);

	skb_push(skb, tcp_header_size);
	skb_reset_transport_header(skb);

	th = (काष्ठा tcphdr *)skb->data;
	स_रखो(th, 0, माप(काष्ठा tcphdr));
	th->syn = 1;
	th->ack = 1;
	tcp_ecn_make_synack(req, th);
	th->source = htons(ireq->ir_num);
	th->dest = ireq->ir_rmt_port;
	skb->mark = ireq->ir_mark;
	skb->ip_summed = CHECKSUM_PARTIAL;
	th->seq = htonl(tcp_rsk(req)->snt_isn);
	/* XXX data is queued and acked as is. No buffer/winकरोw check */
	th->ack_seq = htonl(tcp_rsk(req)->rcv_nxt);

	/* RFC1323: The winकरोw in SYN & SYN/ACK segments is never scaled. */
	th->winकरोw = htons(min(req->rsk_rcv_wnd, 65535U));
	tcp_options_ग_लिखो((__be32 *)(th + 1), शून्य, &opts);
	th->करोff = (tcp_header_size >> 2);
	__TCP_INC_STATS(sock_net(sk), TCP_MIB_OUTSEGS);

#अगर_घोषित CONFIG_TCP_MD5SIG
	/* Okay, we have all we need - करो the md5 hash अगर needed */
	अगर (md5)
		tcp_rsk(req)->af_specअगरic->calc_md5_hash(opts.hash_location,
					       md5, req_to_sk(req), skb);
	rcu_पढ़ो_unlock();
#पूर्ण_अगर

	bpf_skops_ग_लिखो_hdr_opt((काष्ठा sock *)sk, skb, req, syn_skb,
				synack_type, &opts);

	skb->skb_mstamp_ns = now;
	tcp_add_tx_delay(skb, tp);

	वापस skb;
पूर्ण
EXPORT_SYMBOL(tcp_make_synack);

अटल व्योम tcp_ca_dst_init(काष्ठा sock *sk, स्थिर काष्ठा dst_entry *dst)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	स्थिर काष्ठा tcp_congestion_ops *ca;
	u32 ca_key = dst_metric(dst, RTAX_CC_ALGO);

	अगर (ca_key == TCP_CA_UNSPEC)
		वापस;

	rcu_पढ़ो_lock();
	ca = tcp_ca_find_key(ca_key);
	अगर (likely(ca && bpf_try_module_get(ca, ca->owner))) अणु
		bpf_module_put(icsk->icsk_ca_ops, icsk->icsk_ca_ops->owner);
		icsk->icsk_ca_dst_locked = tcp_ca_dst_locked(dst);
		icsk->icsk_ca_ops = ca;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/* Do all connect socket setups that can be करोne AF independent. */
अटल व्योम tcp_connect_init(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा dst_entry *dst = __sk_dst_get(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	__u8 rcv_wscale;
	u32 rcv_wnd;

	/* We'll fix this up when we get a response from the other end.
	 * See tcp_input.c:tcp_rcv_state_process हाल TCP_SYN_SENT.
	 */
	tp->tcp_header_len = माप(काष्ठा tcphdr);
	अगर (sock_net(sk)->ipv4.sysctl_tcp_बारtamps)
		tp->tcp_header_len += TCPOLEN_TSTAMP_ALIGNED;

#अगर_घोषित CONFIG_TCP_MD5SIG
	अगर (tp->af_specअगरic->md5_lookup(sk, sk))
		tp->tcp_header_len += TCPOLEN_MD5SIG_ALIGNED;
#पूर्ण_अगर

	/* If user gave his TCP_MAXSEG, record it to clamp */
	अगर (tp->rx_opt.user_mss)
		tp->rx_opt.mss_clamp = tp->rx_opt.user_mss;
	tp->max_winकरोw = 0;
	tcp_mtup_init(sk);
	tcp_sync_mss(sk, dst_mtu(dst));

	tcp_ca_dst_init(sk, dst);

	अगर (!tp->winकरोw_clamp)
		tp->winकरोw_clamp = dst_metric(dst, RTAX_WINDOW);
	tp->advmss = tcp_mss_clamp(tp, dst_metric_advmss(dst));

	tcp_initialize_rcv_mss(sk);

	/* limit the winकरोw selection अगर the user enक्रमce a smaller rx buffer */
	अगर (sk->sk_userlocks & SOCK_RCVBUF_LOCK &&
	    (tp->winकरोw_clamp > tcp_full_space(sk) || tp->winकरोw_clamp == 0))
		tp->winकरोw_clamp = tcp_full_space(sk);

	rcv_wnd = tcp_rwnd_init_bpf(sk);
	अगर (rcv_wnd == 0)
		rcv_wnd = dst_metric(dst, RTAX_INITRWND);

	tcp_select_initial_winकरोw(sk, tcp_full_space(sk),
				  tp->advmss - (tp->rx_opt.ts_recent_stamp ? tp->tcp_header_len - माप(काष्ठा tcphdr) : 0),
				  &tp->rcv_wnd,
				  &tp->winकरोw_clamp,
				  sock_net(sk)->ipv4.sysctl_tcp_winकरोw_scaling,
				  &rcv_wscale,
				  rcv_wnd);

	tp->rx_opt.rcv_wscale = rcv_wscale;
	tp->rcv_ssthresh = tp->rcv_wnd;

	sk->sk_err = 0;
	sock_reset_flag(sk, SOCK_DONE);
	tp->snd_wnd = 0;
	tcp_init_wl(tp, 0);
	tcp_ग_लिखो_queue_purge(sk);
	tp->snd_una = tp->ग_लिखो_seq;
	tp->snd_sml = tp->ग_लिखो_seq;
	tp->snd_up = tp->ग_लिखो_seq;
	WRITE_ONCE(tp->snd_nxt, tp->ग_लिखो_seq);

	अगर (likely(!tp->repair))
		tp->rcv_nxt = 0;
	अन्यथा
		tp->rcv_tstamp = tcp_jअगरfies32;
	tp->rcv_wup = tp->rcv_nxt;
	WRITE_ONCE(tp->copied_seq, tp->rcv_nxt);

	inet_csk(sk)->icsk_rto = tcp_समयout_init(sk);
	inet_csk(sk)->icsk_retransmits = 0;
	tcp_clear_retrans(tp);
पूर्ण

अटल व्योम tcp_connect_queue_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा tcp_skb_cb *tcb = TCP_SKB_CB(skb);

	tcb->end_seq += skb->len;
	__skb_header_release(skb);
	sk_wmem_queued_add(sk, skb->truesize);
	sk_mem_अक्षरge(sk, skb->truesize);
	WRITE_ONCE(tp->ग_लिखो_seq, tcb->end_seq);
	tp->packets_out += tcp_skb_pcount(skb);
पूर्ण

/* Build and send a SYN with data and (cached) Fast Open cookie. However,
 * queue a data-only packet after the regular SYN, such that regular SYNs
 * are retransmitted on समयouts. Also अगर the remote SYN-ACK acknowledges
 * only the SYN sequence, the data are retransmitted in the first ACK.
 * If cookie is not cached or other error occurs, falls back to send a
 * regular SYN with Fast Open cookie request option.
 */
अटल पूर्णांक tcp_send_syn_data(काष्ठा sock *sk, काष्ठा sk_buff *syn)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा tcp_fastखोलो_request *fo = tp->fastखोलो_req;
	पूर्णांक space, err = 0;
	काष्ठा sk_buff *syn_data;

	tp->rx_opt.mss_clamp = tp->advmss;  /* If MSS is not cached */
	अगर (!tcp_fastखोलो_cookie_check(sk, &tp->rx_opt.mss_clamp, &fo->cookie))
		जाओ fallback;

	/* MSS क्रम SYN-data is based on cached MSS and bounded by PMTU and
	 * user-MSS. Reserve maximum option space क्रम middleboxes that add
	 * निजी TCP options. The cost is reduced data space in SYN :(
	 */
	tp->rx_opt.mss_clamp = tcp_mss_clamp(tp, tp->rx_opt.mss_clamp);

	space = __tcp_mtu_to_mss(sk, inet_csk(sk)->icsk_pmtu_cookie) -
		MAX_TCP_OPTION_SPACE;

	space = min_t(माप_प्रकार, space, fo->size);

	/* limit to order-0 allocations */
	space = min_t(माप_प्रकार, space, SKB_MAX_HEAD(MAX_TCP_HEADER));

	syn_data = sk_stream_alloc_skb(sk, space, sk->sk_allocation, false);
	अगर (!syn_data)
		जाओ fallback;
	syn_data->ip_summed = CHECKSUM_PARTIAL;
	स_नकल(syn_data->cb, syn->cb, माप(syn->cb));
	अगर (space) अणु
		पूर्णांक copied = copy_from_iter(skb_put(syn_data, space), space,
					    &fo->data->msg_iter);
		अगर (unlikely(!copied)) अणु
			tcp_skb_tsorted_anchor_cleanup(syn_data);
			kमुक्त_skb(syn_data);
			जाओ fallback;
		पूर्ण
		अगर (copied != space) अणु
			skb_trim(syn_data, copied);
			space = copied;
		पूर्ण
		skb_zcopy_set(syn_data, fo->uarg, शून्य);
	पूर्ण
	/* No more data pending in inet_रुको_क्रम_connect() */
	अगर (space == fo->size)
		fo->data = शून्य;
	fo->copied = space;

	tcp_connect_queue_skb(sk, syn_data);
	अगर (syn_data->len)
		tcp_chrono_start(sk, TCP_CHRONO_BUSY);

	err = tcp_transmit_skb(sk, syn_data, 1, sk->sk_allocation);

	syn->skb_mstamp_ns = syn_data->skb_mstamp_ns;

	/* Now full SYN+DATA was cloned and sent (or not),
	 * हटाओ the SYN from the original skb (syn_data)
	 * we keep in ग_लिखो queue in हाल of a retransmit, as we
	 * also have the SYN packet (with no data) in the same queue.
	 */
	TCP_SKB_CB(syn_data)->seq++;
	TCP_SKB_CB(syn_data)->tcp_flags = TCPHDR_ACK | TCPHDR_PSH;
	अगर (!err) अणु
		tp->syn_data = (fo->copied > 0);
		tcp_rbtree_insert(&sk->tcp_rtx_queue, syn_data);
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPORIGDATASENT);
		जाओ करोne;
	पूर्ण

	/* data was not sent, put it in ग_लिखो_queue */
	__skb_queue_tail(&sk->sk_ग_लिखो_queue, syn_data);
	tp->packets_out -= tcp_skb_pcount(syn_data);

fallback:
	/* Send a regular SYN with Fast Open cookie request option */
	अगर (fo->cookie.len > 0)
		fo->cookie.len = 0;
	err = tcp_transmit_skb(sk, syn, 1, sk->sk_allocation);
	अगर (err)
		tp->syn_fastखोलो = 0;
करोne:
	fo->cookie.len = -1;  /* Exclude Fast Open option क्रम SYN retries */
	वापस err;
पूर्ण

/* Build a SYN and send it off. */
पूर्णांक tcp_connect(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *buff;
	पूर्णांक err;

	tcp_call_bpf(sk, BPF_SOCK_OPS_TCP_CONNECT_CB, 0, शून्य);

	अगर (inet_csk(sk)->icsk_af_ops->rebuild_header(sk))
		वापस -EHOSTUNREACH; /* Routing failure or similar. */

	tcp_connect_init(sk);

	अगर (unlikely(tp->repair)) अणु
		tcp_finish_connect(sk, शून्य);
		वापस 0;
	पूर्ण

	buff = sk_stream_alloc_skb(sk, 0, sk->sk_allocation, true);
	अगर (unlikely(!buff))
		वापस -ENOBUFS;

	tcp_init_nondata_skb(buff, tp->ग_लिखो_seq++, TCPHDR_SYN);
	tcp_mstamp_refresh(tp);
	tp->retrans_stamp = tcp_समय_stamp(tp);
	tcp_connect_queue_skb(sk, buff);
	tcp_ecn_send_syn(sk, buff);
	tcp_rbtree_insert(&sk->tcp_rtx_queue, buff);

	/* Send off SYN; include data in Fast Open. */
	err = tp->fastखोलो_req ? tcp_send_syn_data(sk, buff) :
	      tcp_transmit_skb(sk, buff, 1, sk->sk_allocation);
	अगर (err == -ECONNREFUSED)
		वापस err;

	/* We change tp->snd_nxt after the tcp_transmit_skb() call
	 * in order to make this packet get counted in tcpOutSegs.
	 */
	WRITE_ONCE(tp->snd_nxt, tp->ग_लिखो_seq);
	tp->pushed_seq = tp->ग_लिखो_seq;
	buff = tcp_send_head(sk);
	अगर (unlikely(buff)) अणु
		WRITE_ONCE(tp->snd_nxt, TCP_SKB_CB(buff)->seq);
		tp->pushed_seq	= TCP_SKB_CB(buff)->seq;
	पूर्ण
	TCP_INC_STATS(sock_net(sk), TCP_MIB_ACTIVEOPENS);

	/* Timer क्रम repeating the SYN until an answer. */
	inet_csk_reset_xmit_समयr(sk, ICSK_TIME_RETRANS,
				  inet_csk(sk)->icsk_rto, TCP_RTO_MAX);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tcp_connect);

/* Send out a delayed ack, the caller करोes the policy checking
 * to see अगर we should even be here.  See tcp_input.c:tcp_ack_snd_check()
 * क्रम details.
 */
व्योम tcp_send_delayed_ack(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	पूर्णांक ato = icsk->icsk_ack.ato;
	अचिन्हित दीर्घ समयout;

	अगर (ato > TCP_DELACK_MIN) अणु
		स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
		पूर्णांक max_ato = HZ / 2;

		अगर (inet_csk_in_pingpong_mode(sk) ||
		    (icsk->icsk_ack.pending & ICSK_ACK_PUSHED))
			max_ato = TCP_DELACK_MAX;

		/* Slow path, पूर्णांकersegment पूर्णांकerval is "high". */

		/* If some rtt estimate is known, use it to bound delayed ack.
		 * Do not use inet_csk(sk)->icsk_rto here, use results of rtt measurements
		 * directly.
		 */
		अगर (tp->srtt_us) अणु
			पूर्णांक rtt = max_t(पूर्णांक, usecs_to_jअगरfies(tp->srtt_us >> 3),
					TCP_DELACK_MIN);

			अगर (rtt < max_ato)
				max_ato = rtt;
		पूर्ण

		ato = min(ato, max_ato);
	पूर्ण

	ato = min_t(u32, ato, inet_csk(sk)->icsk_delack_max);

	/* Stay within the limit we were given */
	समयout = jअगरfies + ato;

	/* Use new समयout only अगर there wasn't a older one earlier. */
	अगर (icsk->icsk_ack.pending & ICSK_ACK_TIMER) अणु
		/* If delack समयr is about to expire, send ACK now. */
		अगर (समय_beक्रमe_eq(icsk->icsk_ack.समयout, jअगरfies + (ato >> 2))) अणु
			tcp_send_ack(sk);
			वापस;
		पूर्ण

		अगर (!समय_beक्रमe(समयout, icsk->icsk_ack.समयout))
			समयout = icsk->icsk_ack.समयout;
	पूर्ण
	icsk->icsk_ack.pending |= ICSK_ACK_SCHED | ICSK_ACK_TIMER;
	icsk->icsk_ack.समयout = समयout;
	sk_reset_समयr(sk, &icsk->icsk_delack_समयr, समयout);
पूर्ण

/* This routine sends an ack and also updates the winकरोw. */
व्योम __tcp_send_ack(काष्ठा sock *sk, u32 rcv_nxt)
अणु
	काष्ठा sk_buff *buff;

	/* If we have been reset, we may not send again. */
	अगर (sk->sk_state == TCP_CLOSE)
		वापस;

	/* We are not putting this on the ग_लिखो queue, so
	 * tcp_transmit_skb() will set the ownership to this
	 * sock.
	 */
	buff = alloc_skb(MAX_TCP_HEADER,
			 sk_gfp_mask(sk, GFP_ATOMIC | __GFP_NOWARN));
	अगर (unlikely(!buff)) अणु
		काष्ठा inet_connection_sock *icsk = inet_csk(sk);
		अचिन्हित दीर्घ delay;

		delay = TCP_DELACK_MAX << icsk->icsk_ack.retry;
		अगर (delay < TCP_RTO_MAX)
			icsk->icsk_ack.retry++;
		inet_csk_schedule_ack(sk);
		icsk->icsk_ack.ato = TCP_ATO_MIN;
		inet_csk_reset_xmit_समयr(sk, ICSK_TIME_DACK, delay, TCP_RTO_MAX);
		वापस;
	पूर्ण

	/* Reserve space क्रम headers and prepare control bits. */
	skb_reserve(buff, MAX_TCP_HEADER);
	tcp_init_nondata_skb(buff, tcp_acceptable_seq(sk), TCPHDR_ACK);

	/* We करो not want pure acks influencing TCP Small Queues or fq/pacing
	 * too much.
	 * SKB_TRUESIZE(max(1 .. 66, MAX_TCP_HEADER)) is unक्रमtunately ~784
	 */
	skb_set_tcp_pure_ack(buff);

	/* Send it off, this clears delayed acks क्रम us. */
	__tcp_transmit_skb(sk, buff, 0, (__क्रमce gfp_t)0, rcv_nxt);
पूर्ण
EXPORT_SYMBOL_GPL(__tcp_send_ack);

व्योम tcp_send_ack(काष्ठा sock *sk)
अणु
	__tcp_send_ack(sk, tcp_sk(sk)->rcv_nxt);
पूर्ण

/* This routine sends a packet with an out of date sequence
 * number. It assumes the other end will try to ack it.
 *
 * Question: what should we make जबतक urgent mode?
 * 4.4BSD क्रमces sending single byte of data. We cannot send
 * out of winकरोw data, because we have SND.NXT==SND.MAX...
 *
 * Current solution: to send TWO zero-length segments in urgent mode:
 * one is with SEG.SEQ=SND.UNA to deliver urgent poपूर्णांकer, another is
 * out-of-date with SND.UNA-1 to probe winकरोw.
 */
अटल पूर्णांक tcp_xmit_probe_skb(काष्ठा sock *sk, पूर्णांक urgent, पूर्णांक mib)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *skb;

	/* We करोn't queue it, tcp_transmit_skb() sets ownership. */
	skb = alloc_skb(MAX_TCP_HEADER,
			sk_gfp_mask(sk, GFP_ATOMIC | __GFP_NOWARN));
	अगर (!skb)
		वापस -1;

	/* Reserve space क्रम headers and set control bits. */
	skb_reserve(skb, MAX_TCP_HEADER);
	/* Use a previous sequence.  This should cause the other
	 * end to send an ack.  Don't queue or clone SKB, just
	 * send it.
	 */
	tcp_init_nondata_skb(skb, tp->snd_una - !urgent, TCPHDR_ACK);
	NET_INC_STATS(sock_net(sk), mib);
	वापस tcp_transmit_skb(sk, skb, 0, (__क्रमce gfp_t)0);
पूर्ण

/* Called from setsockopt( ... TCP_REPAIR ) */
व्योम tcp_send_winकरोw_probe(काष्ठा sock *sk)
अणु
	अगर (sk->sk_state == TCP_ESTABLISHED) अणु
		tcp_sk(sk)->snd_wl1 = tcp_sk(sk)->rcv_nxt - 1;
		tcp_mstamp_refresh(tcp_sk(sk));
		tcp_xmit_probe_skb(sk, 0, LINUX_MIB_TCPWINPROBE);
	पूर्ण
पूर्ण

/* Initiate keepalive or winकरोw probe from समयr. */
पूर्णांक tcp_ग_लिखो_wakeup(काष्ठा sock *sk, पूर्णांक mib)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *skb;

	अगर (sk->sk_state == TCP_CLOSE)
		वापस -1;

	skb = tcp_send_head(sk);
	अगर (skb && beक्रमe(TCP_SKB_CB(skb)->seq, tcp_wnd_end(tp))) अणु
		पूर्णांक err;
		अचिन्हित पूर्णांक mss = tcp_current_mss(sk);
		अचिन्हित पूर्णांक seg_size = tcp_wnd_end(tp) - TCP_SKB_CB(skb)->seq;

		अगर (beक्रमe(tp->pushed_seq, TCP_SKB_CB(skb)->end_seq))
			tp->pushed_seq = TCP_SKB_CB(skb)->end_seq;

		/* We are probing the खोलोing of a winकरोw
		 * but the winकरोw size is != 0
		 * must have been a result SWS aव्योमance ( sender )
		 */
		अगर (seg_size < TCP_SKB_CB(skb)->end_seq - TCP_SKB_CB(skb)->seq ||
		    skb->len > mss) अणु
			seg_size = min(seg_size, mss);
			TCP_SKB_CB(skb)->tcp_flags |= TCPHDR_PSH;
			अगर (tcp_fragment(sk, TCP_FRAG_IN_WRITE_QUEUE,
					 skb, seg_size, mss, GFP_ATOMIC))
				वापस -1;
		पूर्ण अन्यथा अगर (!tcp_skb_pcount(skb))
			tcp_set_skb_tso_segs(skb, mss);

		TCP_SKB_CB(skb)->tcp_flags |= TCPHDR_PSH;
		err = tcp_transmit_skb(sk, skb, 1, GFP_ATOMIC);
		अगर (!err)
			tcp_event_new_data_sent(sk, skb);
		वापस err;
	पूर्ण अन्यथा अणु
		अगर (between(tp->snd_up, tp->snd_una + 1, tp->snd_una + 0xFFFF))
			tcp_xmit_probe_skb(sk, 1, mib);
		वापस tcp_xmit_probe_skb(sk, 0, mib);
	पूर्ण
पूर्ण

/* A winकरोw probe समयout has occurred.  If winकरोw is not बंदd send
 * a partial packet अन्यथा a zero probe.
 */
व्योम tcp_send_probe0(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा net *net = sock_net(sk);
	अचिन्हित दीर्घ समयout;
	पूर्णांक err;

	err = tcp_ग_लिखो_wakeup(sk, LINUX_MIB_TCPWINPROBE);

	अगर (tp->packets_out || tcp_ग_लिखो_queue_empty(sk)) अणु
		/* Cancel probe समयr, अगर it is not required. */
		icsk->icsk_probes_out = 0;
		icsk->icsk_backoff = 0;
		icsk->icsk_probes_tstamp = 0;
		वापस;
	पूर्ण

	icsk->icsk_probes_out++;
	अगर (err <= 0) अणु
		अगर (icsk->icsk_backoff < net->ipv4.sysctl_tcp_retries2)
			icsk->icsk_backoff++;
		समयout = tcp_probe0_when(sk, TCP_RTO_MAX);
	पूर्ण अन्यथा अणु
		/* If packet was not sent due to local congestion,
		 * Let senders fight क्रम local resources conservatively.
		 */
		समयout = TCP_RESOURCE_PROBE_INTERVAL;
	पूर्ण

	समयout = tcp_clamp_probe0_to_user_समयout(sk, समयout);
	tcp_reset_xmit_समयr(sk, ICSK_TIME_PROBE0, समयout, TCP_RTO_MAX);
पूर्ण

पूर्णांक tcp_rtx_synack(स्थिर काष्ठा sock *sk, काष्ठा request_sock *req)
अणु
	स्थिर काष्ठा tcp_request_sock_ops *af_ops = tcp_rsk(req)->af_specअगरic;
	काष्ठा flowi fl;
	पूर्णांक res;

	tcp_rsk(req)->txhash = net_tx_rndhash();
	res = af_ops->send_synack(sk, शून्य, &fl, req, शून्य, TCP_SYNACK_NORMAL,
				  शून्य);
	अगर (!res) अणु
		__TCP_INC_STATS(sock_net(sk), TCP_MIB_RETRANSSEGS);
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPSYNRETRANS);
		अगर (unlikely(tcp_passive_fastखोलो(sk)))
			tcp_sk(sk)->total_retrans++;
		trace_tcp_retransmit_synack(sk, req);
	पूर्ण
	वापस res;
पूर्ण
EXPORT_SYMBOL(tcp_rtx_synack);
