<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
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
 * Changes:
 *		Pedro Roque	:	Fast Retransmit/Recovery.
 *					Two receive queues.
 *					Retransmit queue handled by TCP.
 *					Better retransmit समयr handling.
 *					New congestion aव्योमance.
 *					Header prediction.
 *					Variable renaming.
 *
 *		Eric		:	Fast Retransmit.
 *		Randy Scott	:	MSS option defines.
 *		Eric Schenk	:	Fixes to slow start algorithm.
 *		Eric Schenk	:	Yet another द्विगुन ACK bug.
 *		Eric Schenk	:	Delayed ACK bug fixes.
 *		Eric Schenk	:	Floyd style fast retrans war aव्योमance.
 *		David S. Miller	:	Don't allow zero congestion winकरोw.
 *		Eric Schenk	:	Fix retransmitter so that it sends
 *					next packet on ack of previous packet.
 *		Andi Kleen	:	Moved खोलो_request checking here
 *					and process RSTs क्रम खोलो_requests.
 *		Andi Kleen	:	Better prune_queue, and other fixes.
 *		Andrey Savochkin:	Fix RTT measurements in the presence of
 *					बारtamps.
 *		Andrey Savochkin:	Check sequence numbers correctly when
 *					removing SACKs due to in sequence incoming
 *					data segments.
 *		Andi Kleen:		Make sure we never ack data there is not
 *					enough room क्रम. Also make this condition
 *					a fatal error अगर it might still happen.
 *		Andi Kleen:		Add tcp_measure_rcv_mss to make
 *					connections with MSS<min(MTU,ann. MSS)
 *					work without delayed acks.
 *		Andi Kleen:		Process packets with PSH set in the
 *					fast path.
 *		J Hadi Salim:		ECN support
 *	 	Andrei Gurtov,
 *		Pasi Sarolahti,
 *		Panu Kuhlberg:		Experimental audit of TCP (re)transmission
 *					engine. Lots of bugs are found.
 *		Pasi Sarolahti:		F-RTO क्रम dealing with spurious RTOs
 */

#घोषणा pr_fmt(fmt) "TCP: " fmt

#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/kernel.h>
#समावेश <linux/prefetch.h>
#समावेश <net/dst.h>
#समावेश <net/tcp.h>
#समावेश <net/inet_common.h>
#समावेश <linux/ipsec.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/errqueue.h>
#समावेश <trace/events/tcp.h>
#समावेश <linux/jump_label_ratelimit.h>
#समावेश <net/busy_poll.h>
#समावेश <net/mptcp.h>

पूर्णांक sysctl_tcp_max_orphans __पढ़ो_mostly = NR_खाता;

#घोषणा FLAG_DATA		0x01 /* Incoming frame contained data.		*/
#घोषणा FLAG_WIN_UPDATE		0x02 /* Incoming ACK was a winकरोw update.	*/
#घोषणा FLAG_DATA_ACKED		0x04 /* This ACK acknowledged new data.		*/
#घोषणा FLAG_RETRANS_DATA_ACKED	0x08 /* "" "" some of which was retransmitted.	*/
#घोषणा FLAG_SYN_ACKED		0x10 /* This ACK acknowledged SYN.		*/
#घोषणा FLAG_DATA_SACKED	0x20 /* New SACK.				*/
#घोषणा FLAG_ECE		0x40 /* ECE in this ACK				*/
#घोषणा FLAG_LOST_RETRANS	0x80 /* This ACK marks some retransmission lost */
#घोषणा FLAG_SLOWPATH		0x100 /* Do not skip RFC checks क्रम winकरोw update.*/
#घोषणा FLAG_ORIG_SACK_ACKED	0x200 /* Never retransmitted data are (s)acked	*/
#घोषणा FLAG_SND_UNA_ADVANCED	0x400 /* Snd_una was changed (!= FLAG_DATA_ACKED) */
#घोषणा FLAG_DSACKING_ACK	0x800 /* SACK blocks contained D-SACK info */
#घोषणा FLAG_SET_XMIT_TIMER	0x1000 /* Set TLP or RTO समयr */
#घोषणा FLAG_SACK_RENEGING	0x2000 /* snd_una advanced to a sacked seq */
#घोषणा FLAG_UPDATE_TS_RECENT	0x4000 /* tcp_replace_ts_recent() */
#घोषणा FLAG_NO_CHALLENGE_ACK	0x8000 /* करो not call tcp_send_challenge_ack()	*/
#घोषणा FLAG_ACK_MAYBE_DELAYED	0x10000 /* Likely a delayed ACK */

#घोषणा FLAG_ACKED		(FLAG_DATA_ACKED|FLAG_SYN_ACKED)
#घोषणा FLAG_NOT_DUP		(FLAG_DATA|FLAG_WIN_UPDATE|FLAG_ACKED)
#घोषणा FLAG_CA_ALERT		(FLAG_DATA_SACKED|FLAG_ECE|FLAG_DSACKING_ACK)
#घोषणा FLAG_FORWARD_PROGRESS	(FLAG_ACKED|FLAG_DATA_SACKED)

#घोषणा TCP_REMन_अंकT (TCP_FLAG_FIN|TCP_FLAG_URG|TCP_FLAG_SYN|TCP_FLAG_PSH)
#घोषणा TCP_HP_BITS (~(TCP_RESERVED_BITS|TCP_FLAG_PSH))

#घोषणा REXMIT_NONE	0 /* no loss recovery to करो */
#घोषणा REXMIT_LOST	1 /* retransmit packets marked lost */
#घोषणा REXMIT_NEW	2 /* FRTO-style transmit of unsent/new packets */

#अगर IS_ENABLED(CONFIG_TLS_DEVICE)
अटल DEFINE_STATIC_KEY_DEFERRED_FALSE(clean_acked_data_enabled, HZ);

व्योम clean_acked_data_enable(काष्ठा inet_connection_sock *icsk,
			     व्योम (*cad)(काष्ठा sock *sk, u32 ack_seq))
अणु
	icsk->icsk_clean_acked = cad;
	अटल_branch_deferred_inc(&clean_acked_data_enabled);
पूर्ण
EXPORT_SYMBOL_GPL(clean_acked_data_enable);

व्योम clean_acked_data_disable(काष्ठा inet_connection_sock *icsk)
अणु
	अटल_branch_slow_dec_deferred(&clean_acked_data_enabled);
	icsk->icsk_clean_acked = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(clean_acked_data_disable);

व्योम clean_acked_data_flush(व्योम)
अणु
	अटल_key_deferred_flush(&clean_acked_data_enabled);
पूर्ण
EXPORT_SYMBOL_GPL(clean_acked_data_flush);
#पूर्ण_अगर

#अगर_घोषित CONFIG_CGROUP_BPF
अटल व्योम bpf_skops_parse_hdr(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	bool unknown_opt = tcp_sk(sk)->rx_opt.saw_unknown &&
		BPF_SOCK_OPS_TEST_FLAG(tcp_sk(sk),
				       BPF_SOCK_OPS_PARSE_UNKNOWN_HDR_OPT_CB_FLAG);
	bool parse_all_opt = BPF_SOCK_OPS_TEST_FLAG(tcp_sk(sk),
						    BPF_SOCK_OPS_PARSE_ALL_HDR_OPT_CB_FLAG);
	काष्ठा bpf_sock_ops_kern sock_ops;

	अगर (likely(!unknown_opt && !parse_all_opt))
		वापस;

	/* The skb will be handled in the
	 * bpf_skops_established() or
	 * bpf_skops_ग_लिखो_hdr_opt().
	 */
	चयन (sk->sk_state) अणु
	हाल TCP_SYN_RECV:
	हाल TCP_SYN_SENT:
	हाल TCP_LISTEN:
		वापस;
	पूर्ण

	sock_owned_by_me(sk);

	स_रखो(&sock_ops, 0, दुरत्व(काष्ठा bpf_sock_ops_kern, temp));
	sock_ops.op = BPF_SOCK_OPS_PARSE_HDR_OPT_CB;
	sock_ops.is_fullsock = 1;
	sock_ops.sk = sk;
	bpf_skops_init_skb(&sock_ops, skb, tcp_hdrlen(skb));

	BPF_CGROUP_RUN_PROG_SOCK_OPS(&sock_ops);
पूर्ण

अटल व्योम bpf_skops_established(काष्ठा sock *sk, पूर्णांक bpf_op,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा bpf_sock_ops_kern sock_ops;

	sock_owned_by_me(sk);

	स_रखो(&sock_ops, 0, दुरत्व(काष्ठा bpf_sock_ops_kern, temp));
	sock_ops.op = bpf_op;
	sock_ops.is_fullsock = 1;
	sock_ops.sk = sk;
	/* sk with TCP_REPAIR_ON करोes not have skb in tcp_finish_connect */
	अगर (skb)
		bpf_skops_init_skb(&sock_ops, skb, tcp_hdrlen(skb));

	BPF_CGROUP_RUN_PROG_SOCK_OPS(&sock_ops);
पूर्ण
#अन्यथा
अटल व्योम bpf_skops_parse_hdr(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
पूर्ण

अटल व्योम bpf_skops_established(काष्ठा sock *sk, पूर्णांक bpf_op,
				  काष्ठा sk_buff *skb)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम tcp_gro_dev_warn(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb,
			     अचिन्हित पूर्णांक len)
अणु
	अटल bool __once __पढ़ो_mostly;

	अगर (!__once) अणु
		काष्ठा net_device *dev;

		__once = true;

		rcu_पढ़ो_lock();
		dev = dev_get_by_index_rcu(sock_net(sk), skb->skb_iअगर);
		अगर (!dev || len >= dev->mtu)
			pr_warn("%s: Driver has suspect GRO implementation, TCP performance may be compromised.\n",
				dev ? dev->name : "Unknown driver");
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

/* Adapt the MSS value used to make delayed ack decision to the
 * real world.
 */
अटल व्योम tcp_measure_rcv_mss(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	स्थिर अचिन्हित पूर्णांक lss = icsk->icsk_ack.last_seg_size;
	अचिन्हित पूर्णांक len;

	icsk->icsk_ack.last_seg_size = 0;

	/* skb->len may jitter because of SACKs, even अगर peer
	 * sends good full-sized frames.
	 */
	len = skb_shinfo(skb)->gso_size ? : skb->len;
	अगर (len >= icsk->icsk_ack.rcv_mss) अणु
		icsk->icsk_ack.rcv_mss = min_t(अचिन्हित पूर्णांक, len,
					       tcp_sk(sk)->advmss);
		/* Account क्रम possibly-हटाओd options */
		अगर (unlikely(len > icsk->icsk_ack.rcv_mss +
				   MAX_TCP_OPTION_SPACE))
			tcp_gro_dev_warn(sk, skb, len);
	पूर्ण अन्यथा अणु
		/* Otherwise, we make more careful check taking पूर्णांकo account,
		 * that SACKs block is variable.
		 *
		 * "len" is invariant segment length, including TCP header.
		 */
		len += skb->data - skb_transport_header(skb);
		अगर (len >= TCP_MSS_DEFAULT + माप(काष्ठा tcphdr) ||
		    /* If PSH is not set, packet should be
		     * full sized, provided peer TCP is not badly broken.
		     * This observation (अगर it is correct 8)) allows
		     * to handle super-low mtu links fairly.
		     */
		    (len >= TCP_MIN_MSS + माप(काष्ठा tcphdr) &&
		     !(tcp_flag_word(tcp_hdr(skb)) & TCP_REMन_अंकT))) अणु
			/* Subtract also invariant (अगर peer is RFC compliant),
			 * tcp header plus fixed बारtamp option length.
			 * Resulting "len" is MSS मुक्त of SACK jitter.
			 */
			len -= tcp_sk(sk)->tcp_header_len;
			icsk->icsk_ack.last_seg_size = len;
			अगर (len == lss) अणु
				icsk->icsk_ack.rcv_mss = len;
				वापस;
			पूर्ण
		पूर्ण
		अगर (icsk->icsk_ack.pending & ICSK_ACK_PUSHED)
			icsk->icsk_ack.pending |= ICSK_ACK_PUSHED2;
		icsk->icsk_ack.pending |= ICSK_ACK_PUSHED;
	पूर्ण
पूर्ण

अटल व्योम tcp_incr_quickack(काष्ठा sock *sk, अचिन्हित पूर्णांक max_quickacks)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	अचिन्हित पूर्णांक quickacks = tcp_sk(sk)->rcv_wnd / (2 * icsk->icsk_ack.rcv_mss);

	अगर (quickacks == 0)
		quickacks = 2;
	quickacks = min(quickacks, max_quickacks);
	अगर (quickacks > icsk->icsk_ack.quick)
		icsk->icsk_ack.quick = quickacks;
पूर्ण

व्योम tcp_enter_quickack_mode(काष्ठा sock *sk, अचिन्हित पूर्णांक max_quickacks)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	tcp_incr_quickack(sk, max_quickacks);
	inet_csk_निकास_pingpong_mode(sk);
	icsk->icsk_ack.ato = TCP_ATO_MIN;
पूर्ण
EXPORT_SYMBOL(tcp_enter_quickack_mode);

/* Send ACKs quickly, अगर "quick" count is not exhausted
 * and the session is not पूर्णांकeractive.
 */

अटल bool tcp_in_quickack_mode(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	स्थिर काष्ठा dst_entry *dst = __sk_dst_get(sk);

	वापस (dst && dst_metric(dst, RTAX_QUICKACK)) ||
		(icsk->icsk_ack.quick && !inet_csk_in_pingpong_mode(sk));
पूर्ण

अटल व्योम tcp_ecn_queue_cwr(काष्ठा tcp_sock *tp)
अणु
	अगर (tp->ecn_flags & TCP_ECN_OK)
		tp->ecn_flags |= TCP_ECN_QUEUE_CWR;
पूर्ण

अटल व्योम tcp_ecn_accept_cwr(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (tcp_hdr(skb)->cwr) अणु
		tcp_sk(sk)->ecn_flags &= ~TCP_ECN_DEMAND_CWR;

		/* If the sender is telling us it has entered CWR, then its
		 * cwnd may be very low (even just 1 packet), so we should ACK
		 * immediately.
		 */
		अगर (TCP_SKB_CB(skb)->seq != TCP_SKB_CB(skb)->end_seq)
			inet_csk(sk)->icsk_ack.pending |= ICSK_ACK_NOW;
	पूर्ण
पूर्ण

अटल व्योम tcp_ecn_withdraw_cwr(काष्ठा tcp_sock *tp)
अणु
	tp->ecn_flags &= ~TCP_ECN_QUEUE_CWR;
पूर्ण

अटल व्योम __tcp_ecn_check_ce(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	चयन (TCP_SKB_CB(skb)->ip_dsfield & INET_ECN_MASK) अणु
	हाल INET_ECN_NOT_ECT:
		/* Funny extension: अगर ECT is not set on a segment,
		 * and we alपढ़ोy seen ECT on a previous segment,
		 * it is probably a retransmit.
		 */
		अगर (tp->ecn_flags & TCP_ECN_SEEN)
			tcp_enter_quickack_mode(sk, 2);
		अवरोध;
	हाल INET_ECN_CE:
		अगर (tcp_ca_needs_ecn(sk))
			tcp_ca_event(sk, CA_EVENT_ECN_IS_CE);

		अगर (!(tp->ecn_flags & TCP_ECN_DEMAND_CWR)) अणु
			/* Better not delay acks, sender can have a very low cwnd */
			tcp_enter_quickack_mode(sk, 2);
			tp->ecn_flags |= TCP_ECN_DEMAND_CWR;
		पूर्ण
		tp->ecn_flags |= TCP_ECN_SEEN;
		अवरोध;
	शेष:
		अगर (tcp_ca_needs_ecn(sk))
			tcp_ca_event(sk, CA_EVENT_ECN_NO_CE);
		tp->ecn_flags |= TCP_ECN_SEEN;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम tcp_ecn_check_ce(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (tcp_sk(sk)->ecn_flags & TCP_ECN_OK)
		__tcp_ecn_check_ce(sk, skb);
पूर्ण

अटल व्योम tcp_ecn_rcv_synack(काष्ठा tcp_sock *tp, स्थिर काष्ठा tcphdr *th)
अणु
	अगर ((tp->ecn_flags & TCP_ECN_OK) && (!th->ece || th->cwr))
		tp->ecn_flags &= ~TCP_ECN_OK;
पूर्ण

अटल व्योम tcp_ecn_rcv_syn(काष्ठा tcp_sock *tp, स्थिर काष्ठा tcphdr *th)
अणु
	अगर ((tp->ecn_flags & TCP_ECN_OK) && (!th->ece || !th->cwr))
		tp->ecn_flags &= ~TCP_ECN_OK;
पूर्ण

अटल bool tcp_ecn_rcv_ecn_echo(स्थिर काष्ठा tcp_sock *tp, स्थिर काष्ठा tcphdr *th)
अणु
	अगर (th->ece && !th->syn && (tp->ecn_flags & TCP_ECN_OK))
		वापस true;
	वापस false;
पूर्ण

/* Buffer size and advertised winकरोw tuning.
 *
 * 1. Tuning sk->sk_sndbuf, when connection enters established state.
 */

अटल व्योम tcp_sndbuf_expand(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	स्थिर काष्ठा tcp_congestion_ops *ca_ops = inet_csk(sk)->icsk_ca_ops;
	पूर्णांक sndmem, per_mss;
	u32 nr_segs;

	/* Worst हाल is non GSO/TSO : each frame consumes one skb
	 * and skb->head is kदो_स्मृतिed using घातer of two area of memory
	 */
	per_mss = max_t(u32, tp->rx_opt.mss_clamp, tp->mss_cache) +
		  MAX_TCP_HEADER +
		  SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));

	per_mss = roundup_घात_of_two(per_mss) +
		  SKB_DATA_ALIGN(माप(काष्ठा sk_buff));

	nr_segs = max_t(u32, TCP_INIT_CWND, tp->snd_cwnd);
	nr_segs = max_t(u32, nr_segs, tp->reordering + 1);

	/* Fast Recovery (RFC 5681 3.2) :
	 * Cubic needs 1.7 factor, rounded to 2 to include
	 * extra cushion (application might react slowly to EPOLLOUT)
	 */
	sndmem = ca_ops->sndbuf_expand ? ca_ops->sndbuf_expand(sk) : 2;
	sndmem *= nr_segs * per_mss;

	अगर (sk->sk_sndbuf < sndmem)
		WRITE_ONCE(sk->sk_sndbuf,
			   min(sndmem, sock_net(sk)->ipv4.sysctl_tcp_wmem[2]));
पूर्ण

/* 2. Tuning advertised winकरोw (winकरोw_clamp, rcv_ssthresh)
 *
 * All tcp_full_space() is split to two parts: "network" buffer, allocated
 * क्रमward and advertised in receiver winकरोw (tp->rcv_wnd) and
 * "application buffer", required to isolate scheduling/application
 * latencies from network.
 * winकरोw_clamp is maximal advertised winकरोw. It can be less than
 * tcp_full_space(), in this हाल tcp_full_space() - winकरोw_clamp
 * is reserved क्रम "application" buffer. The less winकरोw_clamp is
 * the smoother our behaviour from viewpoपूर्णांक of network, but the lower
 * throughput and the higher sensitivity of the connection to losses. 8)
 *
 * rcv_ssthresh is more strict winकरोw_clamp used at "slow start"
 * phase to predict further behaviour of this connection.
 * It is used क्रम two goals:
 * - to enक्रमce header prediction at sender, even when application
 *   requires some signअगरicant "application buffer". It is check #1.
 * - to prevent pruning of receive queue because of misprediction
 *   of receiver winकरोw. Check #2.
 *
 * The scheme करोes not work when sender sends good segments खोलोing
 * winकरोw and then starts to feed us spaghetti. But it should work
 * in common situations. Otherwise, we have to rely on queue collapsing.
 */

/* Slow part of check#2. */
अटल पूर्णांक __tcp_grow_winकरोw(स्थिर काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	/* Optimize this! */
	पूर्णांक truesize = tcp_win_from_space(sk, skb->truesize) >> 1;
	पूर्णांक winकरोw = tcp_win_from_space(sk, sock_net(sk)->ipv4.sysctl_tcp_rmem[2]) >> 1;

	जबतक (tp->rcv_ssthresh <= winकरोw) अणु
		अगर (truesize <= skb->len)
			वापस 2 * inet_csk(sk)->icsk_ack.rcv_mss;

		truesize >>= 1;
		winकरोw >>= 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम tcp_grow_winकरोw(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	पूर्णांक room;

	room = min_t(पूर्णांक, tp->winकरोw_clamp, tcp_space(sk)) - tp->rcv_ssthresh;

	/* Check #1 */
	अगर (room > 0 && !tcp_under_memory_pressure(sk)) अणु
		पूर्णांक incr;

		/* Check #2. Increase winकरोw, अगर skb with such overhead
		 * will fit to rcvbuf in future.
		 */
		अगर (tcp_win_from_space(sk, skb->truesize) <= skb->len)
			incr = 2 * tp->advmss;
		अन्यथा
			incr = __tcp_grow_winकरोw(sk, skb);

		अगर (incr) अणु
			incr = max_t(पूर्णांक, incr, 2 * skb->len);
			tp->rcv_ssthresh += min(room, incr);
			inet_csk(sk)->icsk_ack.quick |= 1;
		पूर्ण
	पूर्ण
पूर्ण

/* 3. Try to fixup all. It is made immediately after connection enters
 *    established state.
 */
अटल व्योम tcp_init_buffer_space(काष्ठा sock *sk)
अणु
	पूर्णांक tcp_app_win = sock_net(sk)->ipv4.sysctl_tcp_app_win;
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	पूर्णांक maxwin;

	अगर (!(sk->sk_userlocks & SOCK_SNDBUF_LOCK))
		tcp_sndbuf_expand(sk);

	tcp_mstamp_refresh(tp);
	tp->rcvq_space.समय = tp->tcp_mstamp;
	tp->rcvq_space.seq = tp->copied_seq;

	maxwin = tcp_full_space(sk);

	अगर (tp->winकरोw_clamp >= maxwin) अणु
		tp->winकरोw_clamp = maxwin;

		अगर (tcp_app_win && maxwin > 4 * tp->advmss)
			tp->winकरोw_clamp = max(maxwin -
					       (maxwin >> tcp_app_win),
					       4 * tp->advmss);
	पूर्ण

	/* Force reservation of one segment. */
	अगर (tcp_app_win &&
	    tp->winकरोw_clamp > 2 * tp->advmss &&
	    tp->winकरोw_clamp + tp->advmss > maxwin)
		tp->winकरोw_clamp = max(2 * tp->advmss, maxwin - tp->advmss);

	tp->rcv_ssthresh = min(tp->rcv_ssthresh, tp->winकरोw_clamp);
	tp->snd_cwnd_stamp = tcp_jअगरfies32;
	tp->rcvq_space.space = min3(tp->rcv_ssthresh, tp->rcv_wnd,
				    (u32)TCP_INIT_CWND * tp->advmss);
पूर्ण

/* 4. Recalculate winकरोw clamp after socket hit its memory bounds. */
अटल व्योम tcp_clamp_winकरोw(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा net *net = sock_net(sk);

	icsk->icsk_ack.quick = 0;

	अगर (sk->sk_rcvbuf < net->ipv4.sysctl_tcp_rmem[2] &&
	    !(sk->sk_userlocks & SOCK_RCVBUF_LOCK) &&
	    !tcp_under_memory_pressure(sk) &&
	    sk_memory_allocated(sk) < sk_prot_mem_limits(sk, 0)) अणु
		WRITE_ONCE(sk->sk_rcvbuf,
			   min(atomic_पढ़ो(&sk->sk_rmem_alloc),
			       net->ipv4.sysctl_tcp_rmem[2]));
	पूर्ण
	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) > sk->sk_rcvbuf)
		tp->rcv_ssthresh = min(tp->winकरोw_clamp, 2U * tp->advmss);
पूर्ण

/* Initialize RCV_MSS value.
 * RCV_MSS is an our guess about MSS used by the peer.
 * We haven't any direct inक्रमmation about the MSS.
 * It's better to underestimate the RCV_MSS rather than overestimate.
 * Overestimations make us ACKing less frequently than needed.
 * Underestimations are more easy to detect and fix by tcp_measure_rcv_mss().
 */
व्योम tcp_initialize_rcv_mss(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	अचिन्हित पूर्णांक hपूर्णांक = min_t(अचिन्हित पूर्णांक, tp->advmss, tp->mss_cache);

	hपूर्णांक = min(hपूर्णांक, tp->rcv_wnd / 2);
	hपूर्णांक = min(hपूर्णांक, TCP_MSS_DEFAULT);
	hपूर्णांक = max(hपूर्णांक, TCP_MIN_MSS);

	inet_csk(sk)->icsk_ack.rcv_mss = hपूर्णांक;
पूर्ण
EXPORT_SYMBOL(tcp_initialize_rcv_mss);

/* Receiver "autotuning" code.
 *
 * The algorithm क्रम RTT estimation w/o बारtamps is based on
 * Dynamic Right-Sizing (DRS) by Wu Feng and Mike Fisk of LANL.
 * <https://खुला.lanl.gov/radiant/pubs.hपंचांगl#DRS>
 *
 * More detail on this code can be found at
 * <http://staff.psc.edu/jheffner/>,
 * though this reference is out of date.  A new paper
 * is pending.
 */
अटल व्योम tcp_rcv_rtt_update(काष्ठा tcp_sock *tp, u32 sample, पूर्णांक win_dep)
अणु
	u32 new_sample = tp->rcv_rtt_est.rtt_us;
	दीर्घ m = sample;

	अगर (new_sample != 0) अणु
		/* If we sample in larger samples in the non-बारtamp
		 * हाल, we could grossly overestimate the RTT especially
		 * with chatty applications or bulk transfer apps which
		 * are stalled on fileप्रणाली I/O.
		 *
		 * Also, since we are only going क्रम a minimum in the
		 * non-बारtamp हाल, we करो not smooth things out
		 * अन्यथा with बारtamps disabled convergence takes too
		 * दीर्घ.
		 */
		अगर (!win_dep) अणु
			m -= (new_sample >> 3);
			new_sample += m;
		पूर्ण अन्यथा अणु
			m <<= 3;
			अगर (m < new_sample)
				new_sample = m;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* No previous measure. */
		new_sample = m << 3;
	पूर्ण

	tp->rcv_rtt_est.rtt_us = new_sample;
पूर्ण

अटल अंतरभूत व्योम tcp_rcv_rtt_measure(काष्ठा tcp_sock *tp)
अणु
	u32 delta_us;

	अगर (tp->rcv_rtt_est.समय == 0)
		जाओ new_measure;
	अगर (beक्रमe(tp->rcv_nxt, tp->rcv_rtt_est.seq))
		वापस;
	delta_us = tcp_stamp_us_delta(tp->tcp_mstamp, tp->rcv_rtt_est.समय);
	अगर (!delta_us)
		delta_us = 1;
	tcp_rcv_rtt_update(tp, delta_us, 1);

new_measure:
	tp->rcv_rtt_est.seq = tp->rcv_nxt + tp->rcv_wnd;
	tp->rcv_rtt_est.समय = tp->tcp_mstamp;
पूर्ण

अटल अंतरभूत व्योम tcp_rcv_rtt_measure_ts(काष्ठा sock *sk,
					  स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (tp->rx_opt.rcv_tsecr == tp->rcv_rtt_last_tsecr)
		वापस;
	tp->rcv_rtt_last_tsecr = tp->rx_opt.rcv_tsecr;

	अगर (TCP_SKB_CB(skb)->end_seq -
	    TCP_SKB_CB(skb)->seq >= inet_csk(sk)->icsk_ack.rcv_mss) अणु
		u32 delta = tcp_समय_stamp(tp) - tp->rx_opt.rcv_tsecr;
		u32 delta_us;

		अगर (likely(delta < पूर्णांक_उच्च / (USEC_PER_SEC / TCP_TS_HZ))) अणु
			अगर (!delta)
				delta = 1;
			delta_us = delta * (USEC_PER_SEC / TCP_TS_HZ);
			tcp_rcv_rtt_update(tp, delta_us, 0);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * This function should be called every समय data is copied to user space.
 * It calculates the appropriate TCP receive buffer space.
 */
व्योम tcp_rcv_space_adjust(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 copied;
	पूर्णांक समय;

	trace_tcp_rcv_space_adjust(sk);

	tcp_mstamp_refresh(tp);
	समय = tcp_stamp_us_delta(tp->tcp_mstamp, tp->rcvq_space.समय);
	अगर (समय < (tp->rcv_rtt_est.rtt_us >> 3) || tp->rcv_rtt_est.rtt_us == 0)
		वापस;

	/* Number of bytes copied to user in last RTT */
	copied = tp->copied_seq - tp->rcvq_space.seq;
	अगर (copied <= tp->rcvq_space.space)
		जाओ new_measure;

	/* A bit of theory :
	 * copied = bytes received in previous RTT, our base winकरोw
	 * To cope with packet losses, we need a 2x factor
	 * To cope with slow start, and sender growing its cwin by 100 %
	 * every RTT, we need a 4x factor, because the ACK we are sending
	 * now is क्रम the next RTT, not the current one :
	 * <prev RTT . ><current RTT .. ><next RTT .... >
	 */

	अगर (sock_net(sk)->ipv4.sysctl_tcp_moderate_rcvbuf &&
	    !(sk->sk_userlocks & SOCK_RCVBUF_LOCK)) अणु
		पूर्णांक rcvmem, rcvbuf;
		u64 rcvwin, grow;

		/* minimal winकरोw to cope with packet losses, assuming
		 * steady state. Add some cushion because of small variations.
		 */
		rcvwin = ((u64)copied << 1) + 16 * tp->advmss;

		/* Accommodate क्रम sender rate increase (eg. slow start) */
		grow = rcvwin * (copied - tp->rcvq_space.space);
		करो_भाग(grow, tp->rcvq_space.space);
		rcvwin += (grow << 1);

		rcvmem = SKB_TRUESIZE(tp->advmss + MAX_TCP_HEADER);
		जबतक (tcp_win_from_space(sk, rcvmem) < tp->advmss)
			rcvmem += 128;

		करो_भाग(rcvwin, tp->advmss);
		rcvbuf = min_t(u64, rcvwin * rcvmem,
			       sock_net(sk)->ipv4.sysctl_tcp_rmem[2]);
		अगर (rcvbuf > sk->sk_rcvbuf) अणु
			WRITE_ONCE(sk->sk_rcvbuf, rcvbuf);

			/* Make the winकरोw clamp follow aदीर्घ.  */
			tp->winकरोw_clamp = tcp_win_from_space(sk, rcvbuf);
		पूर्ण
	पूर्ण
	tp->rcvq_space.space = copied;

new_measure:
	tp->rcvq_space.seq = tp->copied_seq;
	tp->rcvq_space.समय = tp->tcp_mstamp;
पूर्ण

/* There is something which you must keep in mind when you analyze the
 * behavior of the tp->ato delayed ack समयout पूर्णांकerval.  When a
 * connection starts up, we want to ack as quickly as possible.  The
 * problem is that "good" TCP's करो slow start at the beginning of data
 * transmission.  The means that until we send the first few ACK's the
 * sender will sit on his end and only queue most of his data, because
 * he can only send snd_cwnd unacked packets at any given समय.  For
 * each ACK we send, he increments snd_cwnd and transmits more of his
 * queue.  -DaveM
 */
अटल व्योम tcp_event_data_recv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	u32 now;

	inet_csk_schedule_ack(sk);

	tcp_measure_rcv_mss(sk, skb);

	tcp_rcv_rtt_measure(tp);

	now = tcp_jअगरfies32;

	अगर (!icsk->icsk_ack.ato) अणु
		/* The _first_ data packet received, initialize
		 * delayed ACK engine.
		 */
		tcp_incr_quickack(sk, TCP_MAX_QUICKACKS);
		icsk->icsk_ack.ato = TCP_ATO_MIN;
	पूर्ण अन्यथा अणु
		पूर्णांक m = now - icsk->icsk_ack.lrcvसमय;

		अगर (m <= TCP_ATO_MIN / 2) अणु
			/* The fastest हाल is the first. */
			icsk->icsk_ack.ato = (icsk->icsk_ack.ato >> 1) + TCP_ATO_MIN / 2;
		पूर्ण अन्यथा अगर (m < icsk->icsk_ack.ato) अणु
			icsk->icsk_ack.ato = (icsk->icsk_ack.ato >> 1) + m;
			अगर (icsk->icsk_ack.ato > icsk->icsk_rto)
				icsk->icsk_ack.ato = icsk->icsk_rto;
		पूर्ण अन्यथा अगर (m > icsk->icsk_rto) अणु
			/* Too दीर्घ gap. Apparently sender failed to
			 * restart winकरोw, so that we send ACKs quickly.
			 */
			tcp_incr_quickack(sk, TCP_MAX_QUICKACKS);
			sk_mem_reclaim(sk);
		पूर्ण
	पूर्ण
	icsk->icsk_ack.lrcvसमय = now;

	tcp_ecn_check_ce(sk, skb);

	अगर (skb->len >= 128)
		tcp_grow_winकरोw(sk, skb);
पूर्ण

/* Called to compute a smoothed rtt estimate. The data fed to this
 * routine either comes from बारtamps, or from segments that were
 * known _not_ to have been retransmitted [see Karn/Partridge
 * Proceedings SIGCOMM 87]. The algorithm is from the SIGCOMM 88
 * piece by Van Jacobson.
 * NOTE: the next three routines used to be one big routine.
 * To save cycles in the RFC 1323 implementation it was better to अवरोध
 * it up पूर्णांकo three procedures. -- erics
 */
अटल व्योम tcp_rtt_estimator(काष्ठा sock *sk, दीर्घ mrtt_us)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	दीर्घ m = mrtt_us; /* RTT */
	u32 srtt = tp->srtt_us;

	/*	The following amusing code comes from Jacobson's
	 *	article in SIGCOMM '88.  Note that rtt and mdev
	 *	are scaled versions of rtt and mean deviation.
	 *	This is deचिन्हित to be as fast as possible
	 *	m stands क्रम "measurement".
	 *
	 *	On a 1990 paper the rto value is changed to:
	 *	RTO = rtt + 4 * mdev
	 *
	 * Funny. This algorithm seems to be very broken.
	 * These क्रमmulae increase RTO, when it should be decreased, increase
	 * too slowly, when it should be increased quickly, decrease too quickly
	 * etc. I guess in BSD RTO takes ONE value, so that it is असलolutely
	 * करोes not matter how to _calculate_ it. Seems, it was trap
	 * that VJ failed to aव्योम. 8)
	 */
	अगर (srtt != 0) अणु
		m -= (srtt >> 3);	/* m is now error in rtt est */
		srtt += m;		/* rtt = 7/8 rtt + 1/8 new */
		अगर (m < 0) अणु
			m = -m;		/* m is now असल(error) */
			m -= (tp->mdev_us >> 2);   /* similar update on mdev */
			/* This is similar to one of Eअगरel findings.
			 * Eअगरel blocks mdev updates when rtt decreases.
			 * This solution is a bit dअगरferent: we use finer gain
			 * क्रम mdev in this हाल (alpha*beta).
			 * Like Eअगरel it also prevents growth of rto,
			 * but also it limits too fast rto decreases,
			 * happening in pure Eअगरel.
			 */
			अगर (m > 0)
				m >>= 3;
		पूर्ण अन्यथा अणु
			m -= (tp->mdev_us >> 2);   /* similar update on mdev */
		पूर्ण
		tp->mdev_us += m;		/* mdev = 3/4 mdev + 1/4 new */
		अगर (tp->mdev_us > tp->mdev_max_us) अणु
			tp->mdev_max_us = tp->mdev_us;
			अगर (tp->mdev_max_us > tp->rttvar_us)
				tp->rttvar_us = tp->mdev_max_us;
		पूर्ण
		अगर (after(tp->snd_una, tp->rtt_seq)) अणु
			अगर (tp->mdev_max_us < tp->rttvar_us)
				tp->rttvar_us -= (tp->rttvar_us - tp->mdev_max_us) >> 2;
			tp->rtt_seq = tp->snd_nxt;
			tp->mdev_max_us = tcp_rto_min_us(sk);

			tcp_bpf_rtt(sk);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* no previous measure. */
		srtt = m << 3;		/* take the measured समय to be rtt */
		tp->mdev_us = m << 1;	/* make sure rto = 3*rtt */
		tp->rttvar_us = max(tp->mdev_us, tcp_rto_min_us(sk));
		tp->mdev_max_us = tp->rttvar_us;
		tp->rtt_seq = tp->snd_nxt;

		tcp_bpf_rtt(sk);
	पूर्ण
	tp->srtt_us = max(1U, srtt);
पूर्ण

अटल व्योम tcp_update_pacing_rate(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	u64 rate;

	/* set sk_pacing_rate to 200 % of current rate (mss * cwnd / srtt) */
	rate = (u64)tp->mss_cache * ((USEC_PER_SEC / 100) << 3);

	/* current rate is (cwnd * mss) / srtt
	 * In Slow Start [1], set sk_pacing_rate to 200 % the current rate.
	 * In Congestion Aव्योमance phase, set it to 120 % the current rate.
	 *
	 * [1] : Normal Slow Start condition is (tp->snd_cwnd < tp->snd_ssthresh)
	 *	 If snd_cwnd >= (tp->snd_ssthresh / 2), we are approaching
	 *	 end of slow start and should slow करोwn.
	 */
	अगर (tp->snd_cwnd < tp->snd_ssthresh / 2)
		rate *= sock_net(sk)->ipv4.sysctl_tcp_pacing_ss_ratio;
	अन्यथा
		rate *= sock_net(sk)->ipv4.sysctl_tcp_pacing_ca_ratio;

	rate *= max(tp->snd_cwnd, tp->packets_out);

	अगर (likely(tp->srtt_us))
		करो_भाग(rate, tp->srtt_us);

	/* WRITE_ONCE() is needed because sch_fq fetches sk_pacing_rate
	 * without any lock. We want to make sure compiler wont store
	 * पूर्णांकermediate values in this location.
	 */
	WRITE_ONCE(sk->sk_pacing_rate, min_t(u64, rate,
					     sk->sk_max_pacing_rate));
पूर्ण

/* Calculate rto without backoff.  This is the second half of Van Jacobson's
 * routine referred to above.
 */
अटल व्योम tcp_set_rto(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	/* Old crap is replaced with new one. 8)
	 *
	 * More seriously:
	 * 1. If rtt variance happened to be less 50msec, it is hallucination.
	 *    It cannot be less due to utterly erratic ACK generation made
	 *    at least by solaris and मुक्तbsd. "Erratic ACKs" has _nothing_
	 *    to करो with delayed acks, because at cwnd>2 true delack समयout
	 *    is invisible. Actually, Linux-2.4 also generates erratic
	 *    ACKs in some circumstances.
	 */
	inet_csk(sk)->icsk_rto = __tcp_set_rto(tp);

	/* 2. Fixups made earlier cannot be right.
	 *    If we करो not estimate RTO correctly without them,
	 *    all the algo is pure shit and should be replaced
	 *    with correct one. It is exactly, which we pretend to करो.
	 */

	/* NOTE: clamping at TCP_RTO_MIN is not required, current algo
	 * guarantees that rto is higher.
	 */
	tcp_bound_rto(sk);
पूर्ण

__u32 tcp_init_cwnd(स्थिर काष्ठा tcp_sock *tp, स्थिर काष्ठा dst_entry *dst)
अणु
	__u32 cwnd = (dst ? dst_metric(dst, RTAX_INITCWND) : 0);

	अगर (!cwnd)
		cwnd = TCP_INIT_CWND;
	वापस min_t(__u32, cwnd, tp->snd_cwnd_clamp);
पूर्ण

काष्ठा tcp_sacktag_state अणु
	/* Timestamps क्रम earliest and latest never-retransmitted segment
	 * that was SACKed. RTO needs the earliest RTT to stay conservative,
	 * but congestion control should still get an accurate delay संकेत.
	 */
	u64	first_sackt;
	u64	last_sackt;
	u32	reord;
	u32	sack_delivered;
	पूर्णांक	flag;
	अचिन्हित पूर्णांक mss_now;
	काष्ठा rate_sample *rate;
पूर्ण;

/* Take a notice that peer is sending D-SACKs. Skip update of data delivery
 * and spurious retransmission inक्रमmation अगर this DSACK is unlikely caused by
 * sender's action:
 * - DSACKed sequence range is larger than maximum receiver's winकरोw.
 * - Total no. of DSACKed segments exceed the total no. of retransmitted segs.
 */
अटल u32 tcp_dsack_seen(काष्ठा tcp_sock *tp, u32 start_seq,
			  u32 end_seq, काष्ठा tcp_sacktag_state *state)
अणु
	u32 seq_len, dup_segs = 1;

	अगर (!beक्रमe(start_seq, end_seq))
		वापस 0;

	seq_len = end_seq - start_seq;
	/* Dubious DSACK: DSACKed range greater than maximum advertised rwnd */
	अगर (seq_len > tp->max_winकरोw)
		वापस 0;
	अगर (seq_len > tp->mss_cache)
		dup_segs = DIV_ROUND_UP(seq_len, tp->mss_cache);

	tp->dsack_dups += dup_segs;
	/* Skip the DSACK अगर dup segs weren't retransmitted by sender */
	अगर (tp->dsack_dups > tp->total_retrans)
		वापस 0;

	tp->rx_opt.sack_ok |= TCP_DSACK_SEEN;
	tp->rack.dsack_seen = 1;

	state->flag |= FLAG_DSACKING_ACK;
	/* A spurious retransmission is delivered */
	state->sack_delivered += dup_segs;

	वापस dup_segs;
पूर्ण

/* It's reordering when higher sequence was delivered (i.e. sacked) beक्रमe
 * some lower never-retransmitted sequence ("low_seq"). The maximum reordering
 * distance is approximated in full-mss packet distance ("reordering").
 */
अटल व्योम tcp_check_sack_reordering(काष्ठा sock *sk, स्थिर u32 low_seq,
				      स्थिर पूर्णांक ts)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	स्थिर u32 mss = tp->mss_cache;
	u32 fack, metric;

	fack = tcp_highest_sack_seq(tp);
	अगर (!beक्रमe(low_seq, fack))
		वापस;

	metric = fack - low_seq;
	अगर ((metric > tp->reordering * mss) && mss) अणु
#अगर FASTRETRANS_DEBUG > 1
		pr_debug("Disorder%d %d %u f%u s%u rr%d\n",
			 tp->rx_opt.sack_ok, inet_csk(sk)->icsk_ca_state,
			 tp->reordering,
			 0,
			 tp->sacked_out,
			 tp->unकरो_marker ? tp->unकरो_retrans : 0);
#पूर्ण_अगर
		tp->reordering = min_t(u32, (metric + mss - 1) / mss,
				       sock_net(sk)->ipv4.sysctl_tcp_max_reordering);
	पूर्ण

	/* This exciting event is worth to be remembered. 8) */
	tp->reord_seen++;
	NET_INC_STATS(sock_net(sk),
		      ts ? LINUX_MIB_TCPTSREORDER : LINUX_MIB_TCPSACKREORDER);
पूर्ण

 /* This must be called beक्रमe lost_out or retrans_out are updated
  * on a new loss, because we want to know अगर all skbs previously
  * known to be lost have alपढ़ोy been retransmitted, indicating
  * that this newly lost skb is our next skb to retransmit.
  */
अटल व्योम tcp_verअगरy_retransmit_hपूर्णांक(काष्ठा tcp_sock *tp, काष्ठा sk_buff *skb)
अणु
	अगर ((!tp->retransmit_skb_hपूर्णांक && tp->retrans_out >= tp->lost_out) ||
	    (tp->retransmit_skb_hपूर्णांक &&
	     beक्रमe(TCP_SKB_CB(skb)->seq,
		    TCP_SKB_CB(tp->retransmit_skb_hपूर्णांक)->seq)))
		tp->retransmit_skb_hपूर्णांक = skb;
पूर्ण

/* Sum the number of packets on the wire we have marked as lost, and
 * notअगरy the congestion control module that the given skb was marked lost.
 */
अटल व्योम tcp_notअगरy_skb_loss_event(काष्ठा tcp_sock *tp, स्थिर काष्ठा sk_buff *skb)
अणु
	tp->lost += tcp_skb_pcount(skb);
पूर्ण

व्योम tcp_mark_skb_lost(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	__u8 sacked = TCP_SKB_CB(skb)->sacked;
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (sacked & TCPCB_SACKED_ACKED)
		वापस;

	tcp_verअगरy_retransmit_hपूर्णांक(tp, skb);
	अगर (sacked & TCPCB_LOST) अणु
		अगर (sacked & TCPCB_SACKED_RETRANS) अणु
			/* Account क्रम retransmits that are lost again */
			TCP_SKB_CB(skb)->sacked &= ~TCPCB_SACKED_RETRANS;
			tp->retrans_out -= tcp_skb_pcount(skb);
			NET_ADD_STATS(sock_net(sk), LINUX_MIB_TCPLOSTRETRANSMIT,
				      tcp_skb_pcount(skb));
			tcp_notअगरy_skb_loss_event(tp, skb);
		पूर्ण
	पूर्ण अन्यथा अणु
		tp->lost_out += tcp_skb_pcount(skb);
		TCP_SKB_CB(skb)->sacked |= TCPCB_LOST;
		tcp_notअगरy_skb_loss_event(tp, skb);
	पूर्ण
पूर्ण

/* Updates the delivered and delivered_ce counts */
अटल व्योम tcp_count_delivered(काष्ठा tcp_sock *tp, u32 delivered,
				bool ece_ack)
अणु
	tp->delivered += delivered;
	अगर (ece_ack)
		tp->delivered_ce += delivered;
पूर्ण

/* This procedure tags the retransmission queue when SACKs arrive.
 *
 * We have three tag bits: SACKED(S), RETRANS(R) and LOST(L).
 * Packets in queue with these bits set are counted in variables
 * sacked_out, retrans_out and lost_out, correspondingly.
 *
 * Valid combinations are:
 * Tag  InFlight	Description
 * 0	1		- orig segment is in flight.
 * S	0		- nothing flies, orig reached receiver.
 * L	0		- nothing flies, orig lost by net.
 * R	2		- both orig and retransmit are in flight.
 * L|R	1		- orig is lost, retransmit is in flight.
 * S|R  1		- orig reached receiver, retrans is still in flight.
 * (L|S|R is logically valid, it could occur when L|R is sacked,
 *  but it is equivalent to plain S and code लघु-curcuits it to S.
 *  L|S is logically invalid, it would mean -1 packet in flight 8))
 *
 * These 6 states क्रमm finite state machine, controlled by the following events:
 * 1. New ACK (+SACK) arrives. (tcp_sacktag_ग_लिखो_queue())
 * 2. Retransmission. (tcp_retransmit_skb(), tcp_xmit_retransmit_queue())
 * 3. Loss detection event of two flavors:
 *	A. Scoreboard estimator decided the packet is lost.
 *	   A'. Reno "three dupacks" marks head of queue lost.
 *	B. SACK arrives sacking SND.NXT at the moment, when the
 *	   segment was retransmitted.
 * 4. D-SACK added new rule: D-SACK changes any tag to S.
 *
 * It is pleasant to note, that state diagram turns out to be commutative,
 * so that we are allowed not to be bothered by order of our actions,
 * when multiple events arrive simultaneously. (see the function below).
 *
 * Reordering detection.
 * --------------------
 * Reordering metric is maximal distance, which a packet can be displaced
 * in packet stream. With SACKs we can estimate it:
 *
 * 1. SACK fills old hole and the corresponding segment was not
 *    ever retransmitted -> reordering. Alas, we cannot use it
 *    when segment was retransmitted.
 * 2. The last flaw is solved with D-SACK. D-SACK arrives
 *    क्रम retransmitted and alपढ़ोy SACKed segment -> reordering..
 * Both of these heuristics are not used in Loss state, when we cannot
 * account क्रम retransmits accurately.
 *
 * SACK block validation.
 * ----------------------
 *
 * SACK block range validation checks that the received SACK block fits to
 * the expected sequence limits, i.e., it is between SND.UNA and SND.NXT.
 * Note that SND.UNA is not included to the range though being valid because
 * it means that the receiver is rather inconsistent with itself reporting
 * SACK reneging when it should advance SND.UNA. Such SACK block this is
 * perfectly valid, however, in light of RFC2018 which explicitly states
 * that "SACK block MUST reflect the newest segment.  Even अगर the newest
 * segment is going to be discarded ...", not that it looks very clever
 * in हाल of head skb. Due to potentional receiver driven attacks, we
 * choose to aव्योम immediate execution of a walk in ग_लिखो queue due to
 * reneging and defer head skb's loss recovery to standard loss recovery
 * procedure that will eventually trigger (nothing क्रमbids us करोing this).
 *
 * Implements also blockage to start_seq wrap-around. Problem lies in the
 * fact that though start_seq (s) is beक्रमe end_seq (i.e., not reversed),
 * there's no guarantee that it will be beक्रमe snd_nxt (n). The problem
 * happens when start_seq resides between end_seq wrap (e_w) and snd_nxt
 * wrap (s_w):
 *
 *         <- outs wnd ->                          <- wrapzone ->
 *         u     e      n                         u_w   e_w  s n_w
 *         |     |      |                          |     |   |  |
 * |<------------+------+----- TCP seqno space --------------+---------->|
 * ...-- <2^31 ->|                                           |<--------...
 * ...---- >2^31 ------>|                                    |<--------...
 *
 * Current code wouldn't be vulnerable but it's better still to discard such
 * crazy SACK blocks. Doing this check क्रम start_seq alone बंदs somewhat
 * similar हाल (end_seq after snd_nxt wrap) as earlier reversed check in
 * snd_nxt wrap -> snd_una region will then become "well defined", i.e.,
 * equal to the ideal हाल (infinite seqno space without wrap caused issues).
 *
 * With D-SACK the lower bound is extended to cover sequence space below
 * SND.UNA करोwn to unकरो_marker, which is the last poपूर्णांक of पूर्णांकerest. Yet
 * again, D-SACK block must not to go across snd_una (क्रम the same reason as
 * क्रम the normal SACK blocks, explained above). But there all simplicity
 * ends, TCP might receive valid D-SACKs below that. As दीर्घ as they reside
 * fully below unकरो_marker they करो not affect behavior in anyway and can
 * thereक्रमe be safely ignored. In rare हालs (which are more or less
 * theoretical ones), the D-SACK will nicely cross that boundary due to skb
 * fragmentation and packet reordering past skb's retransmission. To consider
 * them correctly, the acceptable range must be extended even more though
 * the exact amount is rather hard to quantअगरy. However, tp->max_winकरोw can
 * be used as an exaggerated estimate.
 */
अटल bool tcp_is_sackblock_valid(काष्ठा tcp_sock *tp, bool is_dsack,
				   u32 start_seq, u32 end_seq)
अणु
	/* Too far in future, or reversed (पूर्णांकerpretation is ambiguous) */
	अगर (after(end_seq, tp->snd_nxt) || !beक्रमe(start_seq, end_seq))
		वापस false;

	/* Nasty start_seq wrap-around check (see comments above) */
	अगर (!beक्रमe(start_seq, tp->snd_nxt))
		वापस false;

	/* In outstanding winकरोw? ...This is valid निकास क्रम D-SACKs too.
	 * start_seq == snd_una is non-sensical (see comments above)
	 */
	अगर (after(start_seq, tp->snd_una))
		वापस true;

	अगर (!is_dsack || !tp->unकरो_marker)
		वापस false;

	/* ...Then it's D-SACK, and must reside below snd_una completely */
	अगर (after(end_seq, tp->snd_una))
		वापस false;

	अगर (!beक्रमe(start_seq, tp->unकरो_marker))
		वापस true;

	/* Too old */
	अगर (!after(end_seq, tp->unकरो_marker))
		वापस false;

	/* Unकरो_marker boundary crossing (overestimates a lot). Known alपढ़ोy:
	 *   start_seq < unकरो_marker and end_seq >= unकरो_marker.
	 */
	वापस !beक्रमe(start_seq, end_seq - tp->max_winकरोw);
पूर्ण

अटल bool tcp_check_dsack(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *ack_skb,
			    काष्ठा tcp_sack_block_wire *sp, पूर्णांक num_sacks,
			    u32 prior_snd_una, काष्ठा tcp_sacktag_state *state)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 start_seq_0 = get_unaligned_be32(&sp[0].start_seq);
	u32 end_seq_0 = get_unaligned_be32(&sp[0].end_seq);
	u32 dup_segs;

	अगर (beक्रमe(start_seq_0, TCP_SKB_CB(ack_skb)->ack_seq)) अणु
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPDSACKRECV);
	पूर्ण अन्यथा अगर (num_sacks > 1) अणु
		u32 end_seq_1 = get_unaligned_be32(&sp[1].end_seq);
		u32 start_seq_1 = get_unaligned_be32(&sp[1].start_seq);

		अगर (after(end_seq_0, end_seq_1) || beक्रमe(start_seq_0, start_seq_1))
			वापस false;
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPDSACKOFORECV);
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण

	dup_segs = tcp_dsack_seen(tp, start_seq_0, end_seq_0, state);
	अगर (!dup_segs) अणु	/* Skip dubious DSACK */
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPDSACKIGNOREDDUBIOUS);
		वापस false;
	पूर्ण

	NET_ADD_STATS(sock_net(sk), LINUX_MIB_TCPDSACKRECVSEGS, dup_segs);

	/* D-SACK क्रम alपढ़ोy क्रमgotten data... Do dumb counting. */
	अगर (tp->unकरो_marker && tp->unकरो_retrans > 0 &&
	    !after(end_seq_0, prior_snd_una) &&
	    after(end_seq_0, tp->unकरो_marker))
		tp->unकरो_retrans = max_t(पूर्णांक, 0, tp->unकरो_retrans - dup_segs);

	वापस true;
पूर्ण

/* Check अगर skb is fully within the SACK block. In presence of GSO skbs,
 * the incoming SACK may not exactly match but we can find smaller MSS
 * aligned portion of it that matches. Thereक्रमe we might need to fragment
 * which may fail and creates some hassle (caller must handle error हाल
 * वापसs).
 *
 * FIXME: this could be merged to shअगरt decision code
 */
अटल पूर्णांक tcp_match_skb_to_sack(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				  u32 start_seq, u32 end_seq)
अणु
	पूर्णांक err;
	bool in_sack;
	अचिन्हित पूर्णांक pkt_len;
	अचिन्हित पूर्णांक mss;

	in_sack = !after(start_seq, TCP_SKB_CB(skb)->seq) &&
		  !beक्रमe(end_seq, TCP_SKB_CB(skb)->end_seq);

	अगर (tcp_skb_pcount(skb) > 1 && !in_sack &&
	    after(TCP_SKB_CB(skb)->end_seq, start_seq)) अणु
		mss = tcp_skb_mss(skb);
		in_sack = !after(start_seq, TCP_SKB_CB(skb)->seq);

		अगर (!in_sack) अणु
			pkt_len = start_seq - TCP_SKB_CB(skb)->seq;
			अगर (pkt_len < mss)
				pkt_len = mss;
		पूर्ण अन्यथा अणु
			pkt_len = end_seq - TCP_SKB_CB(skb)->seq;
			अगर (pkt_len < mss)
				वापस -EINVAL;
		पूर्ण

		/* Round अगर necessary so that SACKs cover only full MSSes
		 * and/or the reमुख्यing small portion (अगर present)
		 */
		अगर (pkt_len > mss) अणु
			अचिन्हित पूर्णांक new_len = (pkt_len / mss) * mss;
			अगर (!in_sack && new_len < pkt_len)
				new_len += mss;
			pkt_len = new_len;
		पूर्ण

		अगर (pkt_len >= skb->len && !in_sack)
			वापस 0;

		err = tcp_fragment(sk, TCP_FRAG_IN_RTX_QUEUE, skb,
				   pkt_len, mss, GFP_ATOMIC);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस in_sack;
पूर्ण

/* Mark the given newly-SACKed range as such, adjusting counters and hपूर्णांकs. */
अटल u8 tcp_sacktag_one(काष्ठा sock *sk,
			  काष्ठा tcp_sacktag_state *state, u8 sacked,
			  u32 start_seq, u32 end_seq,
			  पूर्णांक dup_sack, पूर्णांक pcount,
			  u64 xmit_समय)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	/* Account D-SACK क्रम retransmitted packet. */
	अगर (dup_sack && (sacked & TCPCB_RETRANS)) अणु
		अगर (tp->unकरो_marker && tp->unकरो_retrans > 0 &&
		    after(end_seq, tp->unकरो_marker))
			tp->unकरो_retrans--;
		अगर ((sacked & TCPCB_SACKED_ACKED) &&
		    beक्रमe(start_seq, state->reord))
				state->reord = start_seq;
	पूर्ण

	/* Nothing to करो; acked frame is about to be dropped (was ACKed). */
	अगर (!after(end_seq, tp->snd_una))
		वापस sacked;

	अगर (!(sacked & TCPCB_SACKED_ACKED)) अणु
		tcp_rack_advance(tp, sacked, end_seq, xmit_समय);

		अगर (sacked & TCPCB_SACKED_RETRANS) अणु
			/* If the segment is not tagged as lost,
			 * we करो not clear RETRANS, believing
			 * that retransmission is still in flight.
			 */
			अगर (sacked & TCPCB_LOST) अणु
				sacked &= ~(TCPCB_LOST|TCPCB_SACKED_RETRANS);
				tp->lost_out -= pcount;
				tp->retrans_out -= pcount;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!(sacked & TCPCB_RETRANS)) अणु
				/* New sack क्रम not retransmitted frame,
				 * which was in hole. It is reordering.
				 */
				अगर (beक्रमe(start_seq,
					   tcp_highest_sack_seq(tp)) &&
				    beक्रमe(start_seq, state->reord))
					state->reord = start_seq;

				अगर (!after(end_seq, tp->high_seq))
					state->flag |= FLAG_ORIG_SACK_ACKED;
				अगर (state->first_sackt == 0)
					state->first_sackt = xmit_समय;
				state->last_sackt = xmit_समय;
			पूर्ण

			अगर (sacked & TCPCB_LOST) अणु
				sacked &= ~TCPCB_LOST;
				tp->lost_out -= pcount;
			पूर्ण
		पूर्ण

		sacked |= TCPCB_SACKED_ACKED;
		state->flag |= FLAG_DATA_SACKED;
		tp->sacked_out += pcount;
		/* Out-of-order packets delivered */
		state->sack_delivered += pcount;

		/* Lost marker hपूर्णांक past SACKed? Tweak RFC3517 cnt */
		अगर (tp->lost_skb_hपूर्णांक &&
		    beक्रमe(start_seq, TCP_SKB_CB(tp->lost_skb_hपूर्णांक)->seq))
			tp->lost_cnt_hपूर्णांक += pcount;
	पूर्ण

	/* D-SACK. We can detect redundant retransmission in S|R and plain R
	 * frames and clear it. unकरो_retrans is decreased above, L|R frames
	 * are accounted above as well.
	 */
	अगर (dup_sack && (sacked & TCPCB_SACKED_RETRANS)) अणु
		sacked &= ~TCPCB_SACKED_RETRANS;
		tp->retrans_out -= pcount;
	पूर्ण

	वापस sacked;
पूर्ण

/* Shअगरt newly-SACKed bytes from this skb to the immediately previous
 * alपढ़ोy-SACKed sk_buff. Mark the newly-SACKed bytes as such.
 */
अटल bool tcp_shअगरted_skb(काष्ठा sock *sk, काष्ठा sk_buff *prev,
			    काष्ठा sk_buff *skb,
			    काष्ठा tcp_sacktag_state *state,
			    अचिन्हित पूर्णांक pcount, पूर्णांक shअगरted, पूर्णांक mss,
			    bool dup_sack)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 start_seq = TCP_SKB_CB(skb)->seq;	/* start of newly-SACKed */
	u32 end_seq = start_seq + shअगरted;	/* end of newly-SACKed */

	BUG_ON(!pcount);

	/* Adjust counters and hपूर्णांकs क्रम the newly sacked sequence
	 * range but discard the वापस value since prev is alपढ़ोy
	 * marked. We must tag the range first because the seq
	 * advancement below implicitly advances
	 * tcp_highest_sack_seq() when skb is highest_sack.
	 */
	tcp_sacktag_one(sk, state, TCP_SKB_CB(skb)->sacked,
			start_seq, end_seq, dup_sack, pcount,
			tcp_skb_बारtamp_us(skb));
	tcp_rate_skb_delivered(sk, skb, state->rate);

	अगर (skb == tp->lost_skb_hपूर्णांक)
		tp->lost_cnt_hपूर्णांक += pcount;

	TCP_SKB_CB(prev)->end_seq += shअगरted;
	TCP_SKB_CB(skb)->seq += shअगरted;

	tcp_skb_pcount_add(prev, pcount);
	WARN_ON_ONCE(tcp_skb_pcount(skb) < pcount);
	tcp_skb_pcount_add(skb, -pcount);

	/* When we're adding to gso_segs == 1, gso_size will be zero,
	 * in theory this shouldn't be necessary but as दीर्घ as DSACK
	 * code can come after this skb later on it's better to keep
	 * setting gso_size to something.
	 */
	अगर (!TCP_SKB_CB(prev)->tcp_gso_size)
		TCP_SKB_CB(prev)->tcp_gso_size = mss;

	/* CHECKME: To clear or not to clear? Mimics normal skb currently */
	अगर (tcp_skb_pcount(skb) <= 1)
		TCP_SKB_CB(skb)->tcp_gso_size = 0;

	/* Dअगरference in this won't matter, both ACKed by the same cumul. ACK */
	TCP_SKB_CB(prev)->sacked |= (TCP_SKB_CB(skb)->sacked & TCPCB_EVER_RETRANS);

	अगर (skb->len > 0) अणु
		BUG_ON(!tcp_skb_pcount(skb));
		NET_INC_STATS(sock_net(sk), LINUX_MIB_SACKSHIFTED);
		वापस false;
	पूर्ण

	/* Whole SKB was eaten :-) */

	अगर (skb == tp->retransmit_skb_hपूर्णांक)
		tp->retransmit_skb_hपूर्णांक = prev;
	अगर (skb == tp->lost_skb_hपूर्णांक) अणु
		tp->lost_skb_hपूर्णांक = prev;
		tp->lost_cnt_hपूर्णांक -= tcp_skb_pcount(prev);
	पूर्ण

	TCP_SKB_CB(prev)->tcp_flags |= TCP_SKB_CB(skb)->tcp_flags;
	TCP_SKB_CB(prev)->eor = TCP_SKB_CB(skb)->eor;
	अगर (TCP_SKB_CB(skb)->tcp_flags & TCPHDR_FIN)
		TCP_SKB_CB(prev)->end_seq++;

	अगर (skb == tcp_highest_sack(sk))
		tcp_advance_highest_sack(sk, skb);

	tcp_skb_collapse_tstamp(prev, skb);
	अगर (unlikely(TCP_SKB_CB(prev)->tx.delivered_mstamp))
		TCP_SKB_CB(prev)->tx.delivered_mstamp = 0;

	tcp_rtx_queue_unlink_and_मुक्त(skb, sk);

	NET_INC_STATS(sock_net(sk), LINUX_MIB_SACKMERGED);

	वापस true;
पूर्ण

/* I wish gso_size would have a bit more sane initialization than
 * something-or-zero which complicates things
 */
अटल पूर्णांक tcp_skb_seglen(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस tcp_skb_pcount(skb) == 1 ? skb->len : tcp_skb_mss(skb);
पूर्ण

/* Shअगरting pages past head area करोesn't work */
अटल पूर्णांक skb_can_shअगरt(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस !skb_headlen(skb) && skb_is_nonlinear(skb);
पूर्ण

पूर्णांक tcp_skb_shअगरt(काष्ठा sk_buff *to, काष्ठा sk_buff *from,
		  पूर्णांक pcount, पूर्णांक shअगरtlen)
अणु
	/* TCP min gso_size is 8 bytes (TCP_MIN_GSO_SIZE)
	 * Since TCP_SKB_CB(skb)->tcp_gso_segs is 16 bits, we need
	 * to make sure not storing more than 65535 * 8 bytes per skb,
	 * even अगर current MSS is bigger.
	 */
	अगर (unlikely(to->len + shअगरtlen >= 65535 * TCP_MIN_GSO_SIZE))
		वापस 0;
	अगर (unlikely(tcp_skb_pcount(to) + pcount > 65535))
		वापस 0;
	वापस skb_shअगरt(to, from, shअगरtlen);
पूर्ण

/* Try collapsing SACK blocks spanning across multiple skbs to a single
 * skb.
 */
अटल काष्ठा sk_buff *tcp_shअगरt_skb_data(काष्ठा sock *sk, काष्ठा sk_buff *skb,
					  काष्ठा tcp_sacktag_state *state,
					  u32 start_seq, u32 end_seq,
					  bool dup_sack)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *prev;
	पूर्णांक mss;
	पूर्णांक pcount = 0;
	पूर्णांक len;
	पूर्णांक in_sack;

	/* Normally R but no L won't result in plain S */
	अगर (!dup_sack &&
	    (TCP_SKB_CB(skb)->sacked & (TCPCB_LOST|TCPCB_SACKED_RETRANS)) == TCPCB_SACKED_RETRANS)
		जाओ fallback;
	अगर (!skb_can_shअगरt(skb))
		जाओ fallback;
	/* This frame is about to be dropped (was ACKed). */
	अगर (!after(TCP_SKB_CB(skb)->end_seq, tp->snd_una))
		जाओ fallback;

	/* Can only happen with delayed DSACK + discard craziness */
	prev = skb_rb_prev(skb);
	अगर (!prev)
		जाओ fallback;

	अगर ((TCP_SKB_CB(prev)->sacked & TCPCB_TAGBITS) != TCPCB_SACKED_ACKED)
		जाओ fallback;

	अगर (!tcp_skb_can_collapse(prev, skb))
		जाओ fallback;

	in_sack = !after(start_seq, TCP_SKB_CB(skb)->seq) &&
		  !beक्रमe(end_seq, TCP_SKB_CB(skb)->end_seq);

	अगर (in_sack) अणु
		len = skb->len;
		pcount = tcp_skb_pcount(skb);
		mss = tcp_skb_seglen(skb);

		/* TODO: Fix DSACKs to not fragment alपढ़ोy SACKed and we can
		 * drop this restriction as unnecessary
		 */
		अगर (mss != tcp_skb_seglen(prev))
			जाओ fallback;
	पूर्ण अन्यथा अणु
		अगर (!after(TCP_SKB_CB(skb)->end_seq, start_seq))
			जाओ noop;
		/* CHECKME: This is non-MSS split हाल only?, this will
		 * cause skipped skbs due to advancing loop btw, original
		 * has that feature too
		 */
		अगर (tcp_skb_pcount(skb) <= 1)
			जाओ noop;

		in_sack = !after(start_seq, TCP_SKB_CB(skb)->seq);
		अगर (!in_sack) अणु
			/* TODO: head merge to next could be attempted here
			 * अगर (!after(TCP_SKB_CB(skb)->end_seq, end_seq)),
			 * though it might not be worth of the additional hassle
			 *
			 * ...we can probably just fallback to what was करोne
			 * previously. We could try merging non-SACKed ones
			 * as well but it probably isn't going to buy off
			 * because later SACKs might again split them, and
			 * it would make skb बारtamp tracking considerably
			 * harder problem.
			 */
			जाओ fallback;
		पूर्ण

		len = end_seq - TCP_SKB_CB(skb)->seq;
		BUG_ON(len < 0);
		BUG_ON(len > skb->len);

		/* MSS boundaries should be honoured or अन्यथा pcount will
		 * severely अवरोध even though it makes things bit trickier.
		 * Optimize common हाल to aव्योम most of the भागides
		 */
		mss = tcp_skb_mss(skb);

		/* TODO: Fix DSACKs to not fragment alपढ़ोy SACKed and we can
		 * drop this restriction as unnecessary
		 */
		अगर (mss != tcp_skb_seglen(prev))
			जाओ fallback;

		अगर (len == mss) अणु
			pcount = 1;
		पूर्ण अन्यथा अगर (len < mss) अणु
			जाओ noop;
		पूर्ण अन्यथा अणु
			pcount = len / mss;
			len = pcount * mss;
		पूर्ण
	पूर्ण

	/* tcp_sacktag_one() won't SACK-tag ranges below snd_una */
	अगर (!after(TCP_SKB_CB(skb)->seq + len, tp->snd_una))
		जाओ fallback;

	अगर (!tcp_skb_shअगरt(prev, skb, pcount, len))
		जाओ fallback;
	अगर (!tcp_shअगरted_skb(sk, prev, skb, state, pcount, len, mss, dup_sack))
		जाओ out;

	/* Hole filled allows collapsing with the next as well, this is very
	 * useful when hole on every nth skb pattern happens
	 */
	skb = skb_rb_next(prev);
	अगर (!skb)
		जाओ out;

	अगर (!skb_can_shअगरt(skb) ||
	    ((TCP_SKB_CB(skb)->sacked & TCPCB_TAGBITS) != TCPCB_SACKED_ACKED) ||
	    (mss != tcp_skb_seglen(skb)))
		जाओ out;

	len = skb->len;
	pcount = tcp_skb_pcount(skb);
	अगर (tcp_skb_shअगरt(prev, skb, pcount, len))
		tcp_shअगरted_skb(sk, prev, skb, state, pcount,
				len, mss, 0);

out:
	वापस prev;

noop:
	वापस skb;

fallback:
	NET_INC_STATS(sock_net(sk), LINUX_MIB_SACKSHIFTFALLBACK);
	वापस शून्य;
पूर्ण

अटल काष्ठा sk_buff *tcp_sacktag_walk(काष्ठा sk_buff *skb, काष्ठा sock *sk,
					काष्ठा tcp_sack_block *next_dup,
					काष्ठा tcp_sacktag_state *state,
					u32 start_seq, u32 end_seq,
					bool dup_sack_in)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *पंचांगp;

	skb_rbtree_walk_from(skb) अणु
		पूर्णांक in_sack = 0;
		bool dup_sack = dup_sack_in;

		/* queue is in-order => we can लघु-circuit the walk early */
		अगर (!beक्रमe(TCP_SKB_CB(skb)->seq, end_seq))
			अवरोध;

		अगर (next_dup  &&
		    beक्रमe(TCP_SKB_CB(skb)->seq, next_dup->end_seq)) अणु
			in_sack = tcp_match_skb_to_sack(sk, skb,
							next_dup->start_seq,
							next_dup->end_seq);
			अगर (in_sack > 0)
				dup_sack = true;
		पूर्ण

		/* skb reference here is a bit tricky to get right, since
		 * shअगरting can eat and मुक्त both this skb and the next,
		 * so not even _safe variant of the loop is enough.
		 */
		अगर (in_sack <= 0) अणु
			पंचांगp = tcp_shअगरt_skb_data(sk, skb, state,
						 start_seq, end_seq, dup_sack);
			अगर (पंचांगp) अणु
				अगर (पंचांगp != skb) अणु
					skb = पंचांगp;
					जारी;
				पूर्ण

				in_sack = 0;
			पूर्ण अन्यथा अणु
				in_sack = tcp_match_skb_to_sack(sk, skb,
								start_seq,
								end_seq);
			पूर्ण
		पूर्ण

		अगर (unlikely(in_sack < 0))
			अवरोध;

		अगर (in_sack) अणु
			TCP_SKB_CB(skb)->sacked =
				tcp_sacktag_one(sk,
						state,
						TCP_SKB_CB(skb)->sacked,
						TCP_SKB_CB(skb)->seq,
						TCP_SKB_CB(skb)->end_seq,
						dup_sack,
						tcp_skb_pcount(skb),
						tcp_skb_बारtamp_us(skb));
			tcp_rate_skb_delivered(sk, skb, state->rate);
			अगर (TCP_SKB_CB(skb)->sacked & TCPCB_SACKED_ACKED)
				list_del_init(&skb->tcp_tsorted_anchor);

			अगर (!beक्रमe(TCP_SKB_CB(skb)->seq,
				    tcp_highest_sack_seq(tp)))
				tcp_advance_highest_sack(sk, skb);
		पूर्ण
	पूर्ण
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *tcp_sacktag_द्वा_खोज(काष्ठा sock *sk, u32 seq)
अणु
	काष्ठा rb_node *parent, **p = &sk->tcp_rtx_queue.rb_node;
	काष्ठा sk_buff *skb;

	जबतक (*p) अणु
		parent = *p;
		skb = rb_to_skb(parent);
		अगर (beक्रमe(seq, TCP_SKB_CB(skb)->seq)) अणु
			p = &parent->rb_left;
			जारी;
		पूर्ण
		अगर (!beक्रमe(seq, TCP_SKB_CB(skb)->end_seq)) अणु
			p = &parent->rb_right;
			जारी;
		पूर्ण
		वापस skb;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा sk_buff *tcp_sacktag_skip(काष्ठा sk_buff *skb, काष्ठा sock *sk,
					u32 skip_to_seq)
अणु
	अगर (skb && after(TCP_SKB_CB(skb)->seq, skip_to_seq))
		वापस skb;

	वापस tcp_sacktag_द्वा_खोज(sk, skip_to_seq);
पूर्ण

अटल काष्ठा sk_buff *tcp_maybe_skipping_dsack(काष्ठा sk_buff *skb,
						काष्ठा sock *sk,
						काष्ठा tcp_sack_block *next_dup,
						काष्ठा tcp_sacktag_state *state,
						u32 skip_to_seq)
अणु
	अगर (!next_dup)
		वापस skb;

	अगर (beक्रमe(next_dup->start_seq, skip_to_seq)) अणु
		skb = tcp_sacktag_skip(skb, sk, next_dup->start_seq);
		skb = tcp_sacktag_walk(skb, sk, शून्य, state,
				       next_dup->start_seq, next_dup->end_seq,
				       1);
	पूर्ण

	वापस skb;
पूर्ण

अटल पूर्णांक tcp_sack_cache_ok(स्थिर काष्ठा tcp_sock *tp, स्थिर काष्ठा tcp_sack_block *cache)
अणु
	वापस cache < tp->recv_sack_cache + ARRAY_SIZE(tp->recv_sack_cache);
पूर्ण

अटल पूर्णांक
tcp_sacktag_ग_लिखो_queue(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *ack_skb,
			u32 prior_snd_una, काष्ठा tcp_sacktag_state *state)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	स्थिर अचिन्हित अक्षर *ptr = (skb_transport_header(ack_skb) +
				    TCP_SKB_CB(ack_skb)->sacked);
	काष्ठा tcp_sack_block_wire *sp_wire = (काष्ठा tcp_sack_block_wire *)(ptr+2);
	काष्ठा tcp_sack_block sp[TCP_NUM_SACKS];
	काष्ठा tcp_sack_block *cache;
	काष्ठा sk_buff *skb;
	पूर्णांक num_sacks = min(TCP_NUM_SACKS, (ptr[1] - TCPOLEN_SACK_BASE) >> 3);
	पूर्णांक used_sacks;
	bool found_dup_sack = false;
	पूर्णांक i, j;
	पूर्णांक first_sack_index;

	state->flag = 0;
	state->reord = tp->snd_nxt;

	अगर (!tp->sacked_out)
		tcp_highest_sack_reset(sk);

	found_dup_sack = tcp_check_dsack(sk, ack_skb, sp_wire,
					 num_sacks, prior_snd_una, state);

	/* Eliminate too old ACKs, but take पूर्णांकo
	 * account more or less fresh ones, they can
	 * contain valid SACK info.
	 */
	अगर (beक्रमe(TCP_SKB_CB(ack_skb)->ack_seq, prior_snd_una - tp->max_winकरोw))
		वापस 0;

	अगर (!tp->packets_out)
		जाओ out;

	used_sacks = 0;
	first_sack_index = 0;
	क्रम (i = 0; i < num_sacks; i++) अणु
		bool dup_sack = !i && found_dup_sack;

		sp[used_sacks].start_seq = get_unaligned_be32(&sp_wire[i].start_seq);
		sp[used_sacks].end_seq = get_unaligned_be32(&sp_wire[i].end_seq);

		अगर (!tcp_is_sackblock_valid(tp, dup_sack,
					    sp[used_sacks].start_seq,
					    sp[used_sacks].end_seq)) अणु
			पूर्णांक mib_idx;

			अगर (dup_sack) अणु
				अगर (!tp->unकरो_marker)
					mib_idx = LINUX_MIB_TCPDSACKIGNOREDNOUNDO;
				अन्यथा
					mib_idx = LINUX_MIB_TCPDSACKIGNOREDOLD;
			पूर्ण अन्यथा अणु
				/* Don't count olds caused by ACK reordering */
				अगर ((TCP_SKB_CB(ack_skb)->ack_seq != tp->snd_una) &&
				    !after(sp[used_sacks].end_seq, tp->snd_una))
					जारी;
				mib_idx = LINUX_MIB_TCPSACKDISCARD;
			पूर्ण

			NET_INC_STATS(sock_net(sk), mib_idx);
			अगर (i == 0)
				first_sack_index = -1;
			जारी;
		पूर्ण

		/* Ignore very old stuff early */
		अगर (!after(sp[used_sacks].end_seq, prior_snd_una)) अणु
			अगर (i == 0)
				first_sack_index = -1;
			जारी;
		पूर्ण

		used_sacks++;
	पूर्ण

	/* order SACK blocks to allow in order walk of the retrans queue */
	क्रम (i = used_sacks - 1; i > 0; i--) अणु
		क्रम (j = 0; j < i; j++) अणु
			अगर (after(sp[j].start_seq, sp[j + 1].start_seq)) अणु
				swap(sp[j], sp[j + 1]);

				/* Track where the first SACK block goes to */
				अगर (j == first_sack_index)
					first_sack_index = j + 1;
			पूर्ण
		पूर्ण
	पूर्ण

	state->mss_now = tcp_current_mss(sk);
	skb = शून्य;
	i = 0;

	अगर (!tp->sacked_out) अणु
		/* It's alपढ़ोy past, so skip checking against it */
		cache = tp->recv_sack_cache + ARRAY_SIZE(tp->recv_sack_cache);
	पूर्ण अन्यथा अणु
		cache = tp->recv_sack_cache;
		/* Skip empty blocks in at head of the cache */
		जबतक (tcp_sack_cache_ok(tp, cache) && !cache->start_seq &&
		       !cache->end_seq)
			cache++;
	पूर्ण

	जबतक (i < used_sacks) अणु
		u32 start_seq = sp[i].start_seq;
		u32 end_seq = sp[i].end_seq;
		bool dup_sack = (found_dup_sack && (i == first_sack_index));
		काष्ठा tcp_sack_block *next_dup = शून्य;

		अगर (found_dup_sack && ((i + 1) == first_sack_index))
			next_dup = &sp[i + 1];

		/* Skip too early cached blocks */
		जबतक (tcp_sack_cache_ok(tp, cache) &&
		       !beक्रमe(start_seq, cache->end_seq))
			cache++;

		/* Can skip some work by looking recv_sack_cache? */
		अगर (tcp_sack_cache_ok(tp, cache) && !dup_sack &&
		    after(end_seq, cache->start_seq)) अणु

			/* Head toकरो? */
			अगर (beक्रमe(start_seq, cache->start_seq)) अणु
				skb = tcp_sacktag_skip(skb, sk, start_seq);
				skb = tcp_sacktag_walk(skb, sk, next_dup,
						       state,
						       start_seq,
						       cache->start_seq,
						       dup_sack);
			पूर्ण

			/* Rest of the block alपढ़ोy fully processed? */
			अगर (!after(end_seq, cache->end_seq))
				जाओ advance_sp;

			skb = tcp_maybe_skipping_dsack(skb, sk, next_dup,
						       state,
						       cache->end_seq);

			/* ...tail reमुख्यs toकरो... */
			अगर (tcp_highest_sack_seq(tp) == cache->end_seq) अणु
				/* ...but better entrypoपूर्णांक exists! */
				skb = tcp_highest_sack(sk);
				अगर (!skb)
					अवरोध;
				cache++;
				जाओ walk;
			पूर्ण

			skb = tcp_sacktag_skip(skb, sk, cache->end_seq);
			/* Check overlap against next cached too (past this one alपढ़ोy) */
			cache++;
			जारी;
		पूर्ण

		अगर (!beक्रमe(start_seq, tcp_highest_sack_seq(tp))) अणु
			skb = tcp_highest_sack(sk);
			अगर (!skb)
				अवरोध;
		पूर्ण
		skb = tcp_sacktag_skip(skb, sk, start_seq);

walk:
		skb = tcp_sacktag_walk(skb, sk, next_dup, state,
				       start_seq, end_seq, dup_sack);

advance_sp:
		i++;
	पूर्ण

	/* Clear the head of the cache sack blocks so we can skip it next समय */
	क्रम (i = 0; i < ARRAY_SIZE(tp->recv_sack_cache) - used_sacks; i++) अणु
		tp->recv_sack_cache[i].start_seq = 0;
		tp->recv_sack_cache[i].end_seq = 0;
	पूर्ण
	क्रम (j = 0; j < used_sacks; j++)
		tp->recv_sack_cache[i++] = sp[j];

	अगर (inet_csk(sk)->icsk_ca_state != TCP_CA_Loss || tp->unकरो_marker)
		tcp_check_sack_reordering(sk, state->reord, 0);

	tcp_verअगरy_left_out(tp);
out:

#अगर FASTRETRANS_DEBUG > 0
	WARN_ON((पूर्णांक)tp->sacked_out < 0);
	WARN_ON((पूर्णांक)tp->lost_out < 0);
	WARN_ON((पूर्णांक)tp->retrans_out < 0);
	WARN_ON((पूर्णांक)tcp_packets_in_flight(tp) < 0);
#पूर्ण_अगर
	वापस state->flag;
पूर्ण

/* Limits sacked_out so that sum with lost_out isn't ever larger than
 * packets_out. Returns false अगर sacked_out adjustement wasn't necessary.
 */
अटल bool tcp_limit_reno_sacked(काष्ठा tcp_sock *tp)
अणु
	u32 holes;

	holes = max(tp->lost_out, 1U);
	holes = min(holes, tp->packets_out);

	अगर ((tp->sacked_out + holes) > tp->packets_out) अणु
		tp->sacked_out = tp->packets_out - holes;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* If we receive more dupacks than we expected counting segments
 * in assumption of असलent reordering, पूर्णांकerpret this as reordering.
 * The only another reason could be bug in receiver TCP.
 */
अटल व्योम tcp_check_reno_reordering(काष्ठा sock *sk, स्थिर पूर्णांक addend)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (!tcp_limit_reno_sacked(tp))
		वापस;

	tp->reordering = min_t(u32, tp->packets_out + addend,
			       sock_net(sk)->ipv4.sysctl_tcp_max_reordering);
	tp->reord_seen++;
	NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPRENOREORDER);
पूर्ण

/* Emulate SACKs क्रम SACKless connection: account क्रम a new dupack. */

अटल व्योम tcp_add_reno_sack(काष्ठा sock *sk, पूर्णांक num_dupack, bool ece_ack)
अणु
	अगर (num_dupack) अणु
		काष्ठा tcp_sock *tp = tcp_sk(sk);
		u32 prior_sacked = tp->sacked_out;
		s32 delivered;

		tp->sacked_out += num_dupack;
		tcp_check_reno_reordering(sk, 0);
		delivered = tp->sacked_out - prior_sacked;
		अगर (delivered > 0)
			tcp_count_delivered(tp, delivered, ece_ack);
		tcp_verअगरy_left_out(tp);
	पूर्ण
पूर्ण

/* Account क्रम ACK, ACKing some data in Reno Recovery phase. */

अटल व्योम tcp_हटाओ_reno_sacks(काष्ठा sock *sk, पूर्णांक acked, bool ece_ack)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (acked > 0) अणु
		/* One ACK acked hole. The rest eat duplicate ACKs. */
		tcp_count_delivered(tp, max_t(पूर्णांक, acked - tp->sacked_out, 1),
				    ece_ack);
		अगर (acked - 1 >= tp->sacked_out)
			tp->sacked_out = 0;
		अन्यथा
			tp->sacked_out -= acked - 1;
	पूर्ण
	tcp_check_reno_reordering(sk, acked);
	tcp_verअगरy_left_out(tp);
पूर्ण

अटल अंतरभूत व्योम tcp_reset_reno_sack(काष्ठा tcp_sock *tp)
अणु
	tp->sacked_out = 0;
पूर्ण

व्योम tcp_clear_retrans(काष्ठा tcp_sock *tp)
अणु
	tp->retrans_out = 0;
	tp->lost_out = 0;
	tp->unकरो_marker = 0;
	tp->unकरो_retrans = -1;
	tp->sacked_out = 0;
पूर्ण

अटल अंतरभूत व्योम tcp_init_unकरो(काष्ठा tcp_sock *tp)
अणु
	tp->unकरो_marker = tp->snd_una;
	/* Retransmission still in flight may cause DSACKs later. */
	tp->unकरो_retrans = tp->retrans_out ? : -1;
पूर्ण

अटल bool tcp_is_rack(स्थिर काष्ठा sock *sk)
अणु
	वापस sock_net(sk)->ipv4.sysctl_tcp_recovery & TCP_RACK_LOSS_DETECTION;
पूर्ण

/* If we detect SACK reneging, क्रमget all SACK inक्रमmation
 * and reset tags completely, otherwise preserve SACKs. If receiver
 * dropped its ofo queue, we will know this due to reneging detection.
 */
अटल व्योम tcp_समयout_mark_lost(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *skb, *head;
	bool is_reneg;			/* is receiver reneging on SACKs? */

	head = tcp_rtx_queue_head(sk);
	is_reneg = head && (TCP_SKB_CB(head)->sacked & TCPCB_SACKED_ACKED);
	अगर (is_reneg) अणु
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPSACKRENEGING);
		tp->sacked_out = 0;
		/* Mark SACK reneging until we recover from this loss event. */
		tp->is_sack_reneg = 1;
	पूर्ण अन्यथा अगर (tcp_is_reno(tp)) अणु
		tcp_reset_reno_sack(tp);
	पूर्ण

	skb = head;
	skb_rbtree_walk_from(skb) अणु
		अगर (is_reneg)
			TCP_SKB_CB(skb)->sacked &= ~TCPCB_SACKED_ACKED;
		अन्यथा अगर (tcp_is_rack(sk) && skb != head &&
			 tcp_rack_skb_समयout(tp, skb, 0) > 0)
			जारी; /* Don't mark recently sent ones lost yet */
		tcp_mark_skb_lost(sk, skb);
	पूर्ण
	tcp_verअगरy_left_out(tp);
	tcp_clear_all_retrans_hपूर्णांकs(tp);
पूर्ण

/* Enter Loss state. */
व्योम tcp_enter_loss(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा net *net = sock_net(sk);
	bool new_recovery = icsk->icsk_ca_state < TCP_CA_Recovery;

	tcp_समयout_mark_lost(sk);

	/* Reduce ssthresh अगर it has not yet been made inside this winकरोw. */
	अगर (icsk->icsk_ca_state <= TCP_CA_Disorder ||
	    !after(tp->high_seq, tp->snd_una) ||
	    (icsk->icsk_ca_state == TCP_CA_Loss && !icsk->icsk_retransmits)) अणु
		tp->prior_ssthresh = tcp_current_ssthresh(sk);
		tp->prior_cwnd = tp->snd_cwnd;
		tp->snd_ssthresh = icsk->icsk_ca_ops->ssthresh(sk);
		tcp_ca_event(sk, CA_EVENT_LOSS);
		tcp_init_unकरो(tp);
	पूर्ण
	tp->snd_cwnd	   = tcp_packets_in_flight(tp) + 1;
	tp->snd_cwnd_cnt   = 0;
	tp->snd_cwnd_stamp = tcp_jअगरfies32;

	/* Timeout in disordered state after receiving substantial DUPACKs
	 * suggests that the degree of reordering is over-estimated.
	 */
	अगर (icsk->icsk_ca_state <= TCP_CA_Disorder &&
	    tp->sacked_out >= net->ipv4.sysctl_tcp_reordering)
		tp->reordering = min_t(अचिन्हित पूर्णांक, tp->reordering,
				       net->ipv4.sysctl_tcp_reordering);
	tcp_set_ca_state(sk, TCP_CA_Loss);
	tp->high_seq = tp->snd_nxt;
	tcp_ecn_queue_cwr(tp);

	/* F-RTO RFC5682 sec 3.1 step 1: retransmit SND.UNA अगर no previous
	 * loss recovery is underway except recurring समयout(s) on
	 * the same SND.UNA (sec 3.2). Disable F-RTO on path MTU probing
	 */
	tp->frto = net->ipv4.sysctl_tcp_frto &&
		   (new_recovery || icsk->icsk_retransmits) &&
		   !inet_csk(sk)->icsk_mtup.probe_size;
पूर्ण

/* If ACK arrived poपूर्णांकing to a remembered SACK, it means that our
 * remembered SACKs करो not reflect real state of receiver i.e.
 * receiver _host_ is heavily congested (or buggy).
 *
 * To aव्योम big spurious retransmission bursts due to transient SACK
 * scoreboard oddities that look like reneging, we give the receiver a
 * little समय (max(RTT/2, 10ms)) to send us some more ACKs that will
 * restore sanity to the SACK scoreboard. If the apparent reneging
 * persists until this RTO then we'll clear the SACK scoreboard.
 */
अटल bool tcp_check_sack_reneging(काष्ठा sock *sk, पूर्णांक flag)
अणु
	अगर (flag & FLAG_SACK_RENEGING) अणु
		काष्ठा tcp_sock *tp = tcp_sk(sk);
		अचिन्हित दीर्घ delay = max(usecs_to_jअगरfies(tp->srtt_us >> 4),
					  msecs_to_jअगरfies(10));

		inet_csk_reset_xmit_समयr(sk, ICSK_TIME_RETRANS,
					  delay, TCP_RTO_MAX);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* Heurestics to calculate number of duplicate ACKs. There's no dupACKs
 * counter when SACK is enabled (without SACK, sacked_out is used क्रम
 * that purpose).
 *
 * With reordering, holes may still be in flight, so RFC3517 recovery
 * uses pure sacked_out (total number of SACKed segments) even though
 * it violates the RFC that uses duplicate ACKs, often these are equal
 * but when e.g. out-of-winकरोw ACKs or packet duplication occurs,
 * they dअगरfer. Since neither occurs due to loss, TCP should really
 * ignore them.
 */
अटल अंतरभूत पूर्णांक tcp_dupack_heuristics(स्थिर काष्ठा tcp_sock *tp)
अणु
	वापस tp->sacked_out + 1;
पूर्ण

/* Linux NewReno/SACK/ECN state machine.
 * --------------------------------------
 *
 * "Open"	Normal state, no dubious events, fast path.
 * "Disorder"   In all the respects it is "Open",
 *		but requires a bit more attention. It is entered when
 *		we see some SACKs or dupacks. It is split of "Open"
 *		मुख्यly to move some processing from fast path to slow one.
 * "CWR"	CWND was reduced due to some Congestion Notअगरication event.
 *		It can be ECN, ICMP source quench, local device congestion.
 * "Recovery"	CWND was reduced, we are fast-retransmitting.
 * "Loss"	CWND was reduced due to RTO समयout or SACK reneging.
 *
 * tcp_fastretrans_alert() is entered:
 * - each incoming ACK, अगर state is not "Open"
 * - when arrived ACK is unusual, namely:
 *	* SACK
 *	* Duplicate ACK.
 *	* ECN ECE.
 *
 * Counting packets in flight is pretty simple.
 *
 *	in_flight = packets_out - left_out + retrans_out
 *
 *	packets_out is SND.NXT-SND.UNA counted in packets.
 *
 *	retrans_out is number of retransmitted segments.
 *
 *	left_out is number of segments left network, but not ACKed yet.
 *
 *		left_out = sacked_out + lost_out
 *
 *     sacked_out: Packets, which arrived to receiver out of order
 *		   and hence not ACKed. With SACKs this number is simply
 *		   amount of SACKed data. Even without SACKs
 *		   it is easy to give pretty reliable estimate of this number,
 *		   counting duplicate ACKs.
 *
 *       lost_out: Packets lost by network. TCP has no explicit
 *		   "loss notification" feedback from network (क्रम now).
 *		   It means that this number can be only _guessed_.
 *		   Actually, it is the heuristics to predict lossage that
 *		   distinguishes dअगरferent algorithms.
 *
 *	F.e. after RTO, when all the queue is considered as lost,
 *	lost_out = packets_out and in_flight = retrans_out.
 *
 *		Essentially, we have now a few algorithms detecting
 *		lost packets.
 *
 *		If the receiver supports SACK:
 *
 *		RFC6675/3517: It is the conventional algorithm. A packet is
 *		considered lost अगर the number of higher sequence packets
 *		SACKed is greater than or equal the DUPACK thoreshold
 *		(reordering). This is implemented in tcp_mark_head_lost and
 *		tcp_update_scoreboard.
 *
 *		RACK (draft-ietf-tcpm-rack-01): it is a newer algorithm
 *		(2017-) that checks timing instead of counting DUPACKs.
 *		Essentially a packet is considered lost अगर it's not S/ACKed
 *		after RTT + reordering_winकरोw, where both metrics are
 *		dynamically measured and adjusted. This is implemented in
 *		tcp_rack_mark_lost.
 *
 *		If the receiver करोes not support SACK:
 *
 *		NewReno (RFC6582): in Recovery we assume that one segment
 *		is lost (classic Reno). While we are in Recovery and
 *		a partial ACK arrives, we assume that one more packet
 *		is lost (NewReno). This heuristics are the same in NewReno
 *		and SACK.
 *
 * Really tricky (and requiring careful tuning) part of algorithm
 * is hidden in functions tcp_समय_प्रकारo_recover() and tcp_xmit_retransmit_queue().
 * The first determines the moment _when_ we should reduce CWND and,
 * hence, slow करोwn क्रमward transmission. In fact, it determines the moment
 * when we decide that hole is caused by loss, rather than by a reorder.
 *
 * tcp_xmit_retransmit_queue() decides, _what_ we should retransmit to fill
 * holes, caused by lost packets.
 *
 * And the most logically complicated part of algorithm is unकरो
 * heuristics. We detect false retransmits due to both too early
 * fast retransmit (reordering) and underestimated RTO, analyzing
 * बारtamps and D-SACKs. When we detect that some segments were
 * retransmitted by mistake and CWND reduction was wrong, we unकरो
 * winकरोw reduction and पात recovery phase. This logic is hidden
 * inside several functions named tcp_try_unकरो_<something>.
 */

/* This function decides, when we should leave Disordered state
 * and enter Recovery phase, reducing congestion winकरोw.
 *
 * Main question: may we further जारी क्रमward transmission
 * with the same cwnd?
 */
अटल bool tcp_समय_प्रकारo_recover(काष्ठा sock *sk, पूर्णांक flag)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	/* Trick#1: The loss is proven. */
	अगर (tp->lost_out)
		वापस true;

	/* Not-A-Trick#2 : Classic rule... */
	अगर (!tcp_is_rack(sk) && tcp_dupack_heuristics(tp) > tp->reordering)
		वापस true;

	वापस false;
पूर्ण

/* Detect loss in event "A" above by marking head of queue up as lost.
 * For RFC3517 SACK, a segment is considered lost अगर it
 * has at least tp->reordering SACKed seqments above it; "packets" refers to
 * the maximum SACKed segments to pass beक्रमe reaching this limit.
 */
अटल व्योम tcp_mark_head_lost(काष्ठा sock *sk, पूर्णांक packets, पूर्णांक mark_head)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *skb;
	पूर्णांक cnt;
	/* Use SACK to deduce losses of new sequences sent during recovery */
	स्थिर u32 loss_high = tp->snd_nxt;

	WARN_ON(packets > tp->packets_out);
	skb = tp->lost_skb_hपूर्णांक;
	अगर (skb) अणु
		/* Head alपढ़ोy handled? */
		अगर (mark_head && after(TCP_SKB_CB(skb)->seq, tp->snd_una))
			वापस;
		cnt = tp->lost_cnt_hपूर्णांक;
	पूर्ण अन्यथा अणु
		skb = tcp_rtx_queue_head(sk);
		cnt = 0;
	पूर्ण

	skb_rbtree_walk_from(skb) अणु
		/* TODO: करो this better */
		/* this is not the most efficient way to करो this... */
		tp->lost_skb_hपूर्णांक = skb;
		tp->lost_cnt_hपूर्णांक = cnt;

		अगर (after(TCP_SKB_CB(skb)->end_seq, loss_high))
			अवरोध;

		अगर (TCP_SKB_CB(skb)->sacked & TCPCB_SACKED_ACKED)
			cnt += tcp_skb_pcount(skb);

		अगर (cnt > packets)
			अवरोध;

		अगर (!(TCP_SKB_CB(skb)->sacked & TCPCB_LOST))
			tcp_mark_skb_lost(sk, skb);

		अगर (mark_head)
			अवरोध;
	पूर्ण
	tcp_verअगरy_left_out(tp);
पूर्ण

/* Account newly detected lost packet(s) */

अटल व्योम tcp_update_scoreboard(काष्ठा sock *sk, पूर्णांक fast_rexmit)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (tcp_is_sack(tp)) अणु
		पूर्णांक sacked_upto = tp->sacked_out - tp->reordering;
		अगर (sacked_upto >= 0)
			tcp_mark_head_lost(sk, sacked_upto, 0);
		अन्यथा अगर (fast_rexmit)
			tcp_mark_head_lost(sk, 1, 1);
	पूर्ण
पूर्ण

अटल bool tcp_tsopt_ecr_beक्रमe(स्थिर काष्ठा tcp_sock *tp, u32 when)
अणु
	वापस tp->rx_opt.saw_tstamp && tp->rx_opt.rcv_tsecr &&
	       beक्रमe(tp->rx_opt.rcv_tsecr, when);
पूर्ण

/* skb is spurious retransmitted अगर the वापसed बारtamp echo
 * reply is prior to the skb transmission समय
 */
अटल bool tcp_skb_spurious_retrans(स्थिर काष्ठा tcp_sock *tp,
				     स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (TCP_SKB_CB(skb)->sacked & TCPCB_RETRANS) &&
	       tcp_tsopt_ecr_beक्रमe(tp, tcp_skb_बारtamp(skb));
पूर्ण

/* Nothing was retransmitted or वापसed बारtamp is less
 * than बारtamp of the first retransmission.
 */
अटल अंतरभूत bool tcp_packet_delayed(स्थिर काष्ठा tcp_sock *tp)
अणु
	वापस tp->retrans_stamp &&
	       tcp_tsopt_ecr_beक्रमe(tp, tp->retrans_stamp);
पूर्ण

/* Unकरो procedures. */

/* We can clear retrans_stamp when there are no retransmissions in the
 * winकरोw. It would seem that it is trivially available क्रम us in
 * tp->retrans_out, however, that kind of assumptions करोesn't consider
 * what will happen अगर errors occur when sending retransmission क्रम the
 * second समय. ...It could the that such segment has only
 * TCPCB_EVER_RETRANS set at the present समय. It seems that checking
 * the head skb is enough except क्रम some reneging corner हालs that
 * are not worth the efक्रमt.
 *
 * Main reason क्रम all this complनिकासy is the fact that connection dying
 * समय now depends on the validity of the retrans_stamp, in particular,
 * that successive retransmissions of a segment must not advance
 * retrans_stamp under any conditions.
 */
अटल bool tcp_any_retrans_करोne(स्थिर काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *skb;

	अगर (tp->retrans_out)
		वापस true;

	skb = tcp_rtx_queue_head(sk);
	अगर (unlikely(skb && TCP_SKB_CB(skb)->sacked & TCPCB_EVER_RETRANS))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम DBGUNDO(काष्ठा sock *sk, स्थिर अक्षर *msg)
अणु
#अगर FASTRETRANS_DEBUG > 1
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा inet_sock *inet = inet_sk(sk);

	अगर (sk->sk_family == AF_INET) अणु
		pr_debug("Undo %s %pI4/%u c%u l%u ss%u/%u p%u\n",
			 msg,
			 &inet->inet_daddr, ntohs(inet->inet_dport),
			 tp->snd_cwnd, tcp_left_out(tp),
			 tp->snd_ssthresh, tp->prior_ssthresh,
			 tp->packets_out);
	पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा अगर (sk->sk_family == AF_INET6) अणु
		pr_debug("Undo %s %pI6/%u c%u l%u ss%u/%u p%u\n",
			 msg,
			 &sk->sk_v6_daddr, ntohs(inet->inet_dport),
			 tp->snd_cwnd, tcp_left_out(tp),
			 tp->snd_ssthresh, tp->prior_ssthresh,
			 tp->packets_out);
	पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण

अटल व्योम tcp_unकरो_cwnd_reduction(काष्ठा sock *sk, bool unmark_loss)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (unmark_loss) अणु
		काष्ठा sk_buff *skb;

		skb_rbtree_walk(skb, &sk->tcp_rtx_queue) अणु
			TCP_SKB_CB(skb)->sacked &= ~TCPCB_LOST;
		पूर्ण
		tp->lost_out = 0;
		tcp_clear_all_retrans_hपूर्णांकs(tp);
	पूर्ण

	अगर (tp->prior_ssthresh) अणु
		स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);

		tp->snd_cwnd = icsk->icsk_ca_ops->unकरो_cwnd(sk);

		अगर (tp->prior_ssthresh > tp->snd_ssthresh) अणु
			tp->snd_ssthresh = tp->prior_ssthresh;
			tcp_ecn_withdraw_cwr(tp);
		पूर्ण
	पूर्ण
	tp->snd_cwnd_stamp = tcp_jअगरfies32;
	tp->unकरो_marker = 0;
	tp->rack.advanced = 1; /* Force RACK to re-exam losses */
पूर्ण

अटल अंतरभूत bool tcp_may_unकरो(स्थिर काष्ठा tcp_sock *tp)
अणु
	वापस tp->unकरो_marker && (!tp->unकरो_retrans || tcp_packet_delayed(tp));
पूर्ण

/* People celebrate: "We love our President!" */
अटल bool tcp_try_unकरो_recovery(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (tcp_may_unकरो(tp)) अणु
		पूर्णांक mib_idx;

		/* Happy end! We did not retransmit anything
		 * or our original transmission succeeded.
		 */
		DBGUNDO(sk, inet_csk(sk)->icsk_ca_state == TCP_CA_Loss ? "loss" : "retrans");
		tcp_unकरो_cwnd_reduction(sk, false);
		अगर (inet_csk(sk)->icsk_ca_state == TCP_CA_Loss)
			mib_idx = LINUX_MIB_TCPLOSSUNDO;
		अन्यथा
			mib_idx = LINUX_MIB_TCPFULLUNDO;

		NET_INC_STATS(sock_net(sk), mib_idx);
	पूर्ण अन्यथा अगर (tp->rack.reo_wnd_persist) अणु
		tp->rack.reo_wnd_persist--;
	पूर्ण
	अगर (tp->snd_una == tp->high_seq && tcp_is_reno(tp)) अणु
		/* Hold old state until something *above* high_seq
		 * is ACKed. For Reno it is MUST to prevent false
		 * fast retransmits (RFC2582). SACK TCP is safe. */
		अगर (!tcp_any_retrans_करोne(sk))
			tp->retrans_stamp = 0;
		वापस true;
	पूर्ण
	tcp_set_ca_state(sk, TCP_CA_Open);
	tp->is_sack_reneg = 0;
	वापस false;
पूर्ण

/* Try to unकरो cwnd reduction, because D-SACKs acked all retransmitted data */
अटल bool tcp_try_unकरो_dsack(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (tp->unकरो_marker && !tp->unकरो_retrans) अणु
		tp->rack.reo_wnd_persist = min(TCP_RACK_RECOVERY_THRESH,
					       tp->rack.reo_wnd_persist + 1);
		DBGUNDO(sk, "D-SACK");
		tcp_unकरो_cwnd_reduction(sk, false);
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPDSACKUNDO);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* Unकरो during loss recovery after partial ACK or using F-RTO. */
अटल bool tcp_try_unकरो_loss(काष्ठा sock *sk, bool frto_unकरो)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (frto_unकरो || tcp_may_unकरो(tp)) अणु
		tcp_unकरो_cwnd_reduction(sk, true);

		DBGUNDO(sk, "partial loss");
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPLOSSUNDO);
		अगर (frto_unकरो)
			NET_INC_STATS(sock_net(sk),
					LINUX_MIB_TCPSPURIOUSRTOS);
		inet_csk(sk)->icsk_retransmits = 0;
		अगर (frto_unकरो || tcp_is_sack(tp)) अणु
			tcp_set_ca_state(sk, TCP_CA_Open);
			tp->is_sack_reneg = 0;
		पूर्ण
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* The cwnd reduction in CWR and Recovery uses the PRR algorithm in RFC 6937.
 * It computes the number of packets to send (sndcnt) based on packets newly
 * delivered:
 *   1) If the packets in flight is larger than ssthresh, PRR spपढ़ोs the
 *	cwnd reductions across a full RTT.
 *   2) Otherwise PRR uses packet conservation to send as much as delivered.
 *      But when SND_UNA is acked without further losses,
 *      slow starts cwnd up to ssthresh to speed up the recovery.
 */
अटल व्योम tcp_init_cwnd_reduction(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	tp->high_seq = tp->snd_nxt;
	tp->tlp_high_seq = 0;
	tp->snd_cwnd_cnt = 0;
	tp->prior_cwnd = tp->snd_cwnd;
	tp->prr_delivered = 0;
	tp->prr_out = 0;
	tp->snd_ssthresh = inet_csk(sk)->icsk_ca_ops->ssthresh(sk);
	tcp_ecn_queue_cwr(tp);
पूर्ण

व्योम tcp_cwnd_reduction(काष्ठा sock *sk, पूर्णांक newly_acked_sacked, पूर्णांक newly_lost, पूर्णांक flag)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	पूर्णांक sndcnt = 0;
	पूर्णांक delta = tp->snd_ssthresh - tcp_packets_in_flight(tp);

	अगर (newly_acked_sacked <= 0 || WARN_ON_ONCE(!tp->prior_cwnd))
		वापस;

	tp->prr_delivered += newly_acked_sacked;
	अगर (delta < 0) अणु
		u64 भागidend = (u64)tp->snd_ssthresh * tp->prr_delivered +
			       tp->prior_cwnd - 1;
		sndcnt = भाग_u64(भागidend, tp->prior_cwnd) - tp->prr_out;
	पूर्ण अन्यथा अगर (flag & FLAG_SND_UNA_ADVANCED && !newly_lost) अणु
		sndcnt = min_t(पूर्णांक, delta,
			       max_t(पूर्णांक, tp->prr_delivered - tp->prr_out,
				     newly_acked_sacked) + 1);
	पूर्ण अन्यथा अणु
		sndcnt = min(delta, newly_acked_sacked);
	पूर्ण
	/* Force a fast retransmit upon entering fast recovery */
	sndcnt = max(sndcnt, (tp->prr_out ? 0 : 1));
	tp->snd_cwnd = tcp_packets_in_flight(tp) + sndcnt;
पूर्ण

अटल अंतरभूत व्योम tcp_end_cwnd_reduction(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (inet_csk(sk)->icsk_ca_ops->cong_control)
		वापस;

	/* Reset cwnd to ssthresh in CWR or Recovery (unless it's unकरोne) */
	अगर (tp->snd_ssthresh < TCP_INFINITE_SSTHRESH &&
	    (inet_csk(sk)->icsk_ca_state == TCP_CA_CWR || tp->unकरो_marker)) अणु
		tp->snd_cwnd = tp->snd_ssthresh;
		tp->snd_cwnd_stamp = tcp_jअगरfies32;
	पूर्ण
	tcp_ca_event(sk, CA_EVENT_COMPLETE_CWR);
पूर्ण

/* Enter CWR state. Disable cwnd unकरो since congestion is proven with ECN */
व्योम tcp_enter_cwr(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	tp->prior_ssthresh = 0;
	अगर (inet_csk(sk)->icsk_ca_state < TCP_CA_CWR) अणु
		tp->unकरो_marker = 0;
		tcp_init_cwnd_reduction(sk);
		tcp_set_ca_state(sk, TCP_CA_CWR);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(tcp_enter_cwr);

अटल व्योम tcp_try_keep_खोलो(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	पूर्णांक state = TCP_CA_Open;

	अगर (tcp_left_out(tp) || tcp_any_retrans_करोne(sk))
		state = TCP_CA_Disorder;

	अगर (inet_csk(sk)->icsk_ca_state != state) अणु
		tcp_set_ca_state(sk, state);
		tp->high_seq = tp->snd_nxt;
	पूर्ण
पूर्ण

अटल व्योम tcp_try_to_खोलो(काष्ठा sock *sk, पूर्णांक flag)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	tcp_verअगरy_left_out(tp);

	अगर (!tcp_any_retrans_करोne(sk))
		tp->retrans_stamp = 0;

	अगर (flag & FLAG_ECE)
		tcp_enter_cwr(sk);

	अगर (inet_csk(sk)->icsk_ca_state != TCP_CA_CWR) अणु
		tcp_try_keep_खोलो(sk);
	पूर्ण
पूर्ण

अटल व्योम tcp_mtup_probe_failed(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	icsk->icsk_mtup.search_high = icsk->icsk_mtup.probe_size - 1;
	icsk->icsk_mtup.probe_size = 0;
	NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPMTUPFAIL);
पूर्ण

अटल व्योम tcp_mtup_probe_success(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	/* FIXME: अवरोधs with very large cwnd */
	tp->prior_ssthresh = tcp_current_ssthresh(sk);
	tp->snd_cwnd = tp->snd_cwnd *
		       tcp_mss_to_mtu(sk, tp->mss_cache) /
		       icsk->icsk_mtup.probe_size;
	tp->snd_cwnd_cnt = 0;
	tp->snd_cwnd_stamp = tcp_jअगरfies32;
	tp->snd_ssthresh = tcp_current_ssthresh(sk);

	icsk->icsk_mtup.search_low = icsk->icsk_mtup.probe_size;
	icsk->icsk_mtup.probe_size = 0;
	tcp_sync_mss(sk, icsk->icsk_pmtu_cookie);
	NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPMTUPSUCCESS);
पूर्ण

/* Do a simple retransmit without using the backoff mechanisms in
 * tcp_समयr. This is used क्रम path mtu discovery.
 * The socket is alपढ़ोy locked here.
 */
व्योम tcp_simple_retransmit(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *skb;
	पूर्णांक mss;

	/* A fastखोलो SYN request is stored as two separate packets within
	 * the retransmit queue, this is करोne by tcp_send_syn_data().
	 * As a result simply checking the MSS of the frames in the queue
	 * will not work क्रम the SYN packet.
	 *
	 * Us being here is an indication of a path MTU issue so we can
	 * assume that the fastखोलो SYN was lost and just mark all the
	 * frames in the retransmit queue as lost. We will use an MSS of
	 * -1 to mark all frames as lost, otherwise compute the current MSS.
	 */
	अगर (tp->syn_data && sk->sk_state == TCP_SYN_SENT)
		mss = -1;
	अन्यथा
		mss = tcp_current_mss(sk);

	skb_rbtree_walk(skb, &sk->tcp_rtx_queue) अणु
		अगर (tcp_skb_seglen(skb) > mss)
			tcp_mark_skb_lost(sk, skb);
	पूर्ण

	tcp_clear_retrans_hपूर्णांकs_partial(tp);

	अगर (!tp->lost_out)
		वापस;

	अगर (tcp_is_reno(tp))
		tcp_limit_reno_sacked(tp);

	tcp_verअगरy_left_out(tp);

	/* Don't muck with the congestion winकरोw here.
	 * Reason is that we करो not increase amount of _data_
	 * in network, but units changed and effective
	 * cwnd/ssthresh really reduced now.
	 */
	अगर (icsk->icsk_ca_state != TCP_CA_Loss) अणु
		tp->high_seq = tp->snd_nxt;
		tp->snd_ssthresh = tcp_current_ssthresh(sk);
		tp->prior_ssthresh = 0;
		tp->unकरो_marker = 0;
		tcp_set_ca_state(sk, TCP_CA_Loss);
	पूर्ण
	tcp_xmit_retransmit_queue(sk);
पूर्ण
EXPORT_SYMBOL(tcp_simple_retransmit);

व्योम tcp_enter_recovery(काष्ठा sock *sk, bool ece_ack)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	पूर्णांक mib_idx;

	अगर (tcp_is_reno(tp))
		mib_idx = LINUX_MIB_TCPRENORECOVERY;
	अन्यथा
		mib_idx = LINUX_MIB_TCPSACKRECOVERY;

	NET_INC_STATS(sock_net(sk), mib_idx);

	tp->prior_ssthresh = 0;
	tcp_init_unकरो(tp);

	अगर (!tcp_in_cwnd_reduction(sk)) अणु
		अगर (!ece_ack)
			tp->prior_ssthresh = tcp_current_ssthresh(sk);
		tcp_init_cwnd_reduction(sk);
	पूर्ण
	tcp_set_ca_state(sk, TCP_CA_Recovery);
पूर्ण

/* Process an ACK in CA_Loss state. Move to CA_Open अगर lost data are
 * recovered or spurious. Otherwise retransmits more on partial ACKs.
 */
अटल व्योम tcp_process_loss(काष्ठा sock *sk, पूर्णांक flag, पूर्णांक num_dupack,
			     पूर्णांक *rexmit)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	bool recovered = !beक्रमe(tp->snd_una, tp->high_seq);

	अगर ((flag & FLAG_SND_UNA_ADVANCED || rcu_access_poपूर्णांकer(tp->fastखोलो_rsk)) &&
	    tcp_try_unकरो_loss(sk, false))
		वापस;

	अगर (tp->frto) अणु /* F-RTO RFC5682 sec 3.1 (sack enhanced version). */
		/* Step 3.b. A समयout is spurious अगर not all data are
		 * lost, i.e., never-retransmitted data are (s)acked.
		 */
		अगर ((flag & FLAG_ORIG_SACK_ACKED) &&
		    tcp_try_unकरो_loss(sk, true))
			वापस;

		अगर (after(tp->snd_nxt, tp->high_seq)) अणु
			अगर (flag & FLAG_DATA_SACKED || num_dupack)
				tp->frto = 0; /* Step 3.a. loss was real */
		पूर्ण अन्यथा अगर (flag & FLAG_SND_UNA_ADVANCED && !recovered) अणु
			tp->high_seq = tp->snd_nxt;
			/* Step 2.b. Try send new data (but deferred until cwnd
			 * is updated in tcp_ack()). Otherwise fall back to
			 * the conventional recovery.
			 */
			अगर (!tcp_ग_लिखो_queue_empty(sk) &&
			    after(tcp_wnd_end(tp), tp->snd_nxt)) अणु
				*rexmit = REXMIT_NEW;
				वापस;
			पूर्ण
			tp->frto = 0;
		पूर्ण
	पूर्ण

	अगर (recovered) अणु
		/* F-RTO RFC5682 sec 3.1 step 2.a and 1st part of step 3.a */
		tcp_try_unकरो_recovery(sk);
		वापस;
	पूर्ण
	अगर (tcp_is_reno(tp)) अणु
		/* A Reno DUPACK means new data in F-RTO step 2.b above are
		 * delivered. Lower inflight to घड़ी out (re)tranmissions.
		 */
		अगर (after(tp->snd_nxt, tp->high_seq) && num_dupack)
			tcp_add_reno_sack(sk, num_dupack, flag & FLAG_ECE);
		अन्यथा अगर (flag & FLAG_SND_UNA_ADVANCED)
			tcp_reset_reno_sack(tp);
	पूर्ण
	*rexmit = REXMIT_LOST;
पूर्ण

/* Unकरो during fast recovery after partial ACK. */
अटल bool tcp_try_unकरो_partial(काष्ठा sock *sk, u32 prior_snd_una)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (tp->unकरो_marker && tcp_packet_delayed(tp)) अणु
		/* Plain luck! Hole अगर filled with delayed
		 * packet, rather than with a retransmit. Check reordering.
		 */
		tcp_check_sack_reordering(sk, prior_snd_una, 1);

		/* We are getting evidence that the reordering degree is higher
		 * than we realized. If there are no retransmits out then we
		 * can unकरो. Otherwise we घड़ी out new packets but करो not
		 * mark more packets lost or retransmit more.
		 */
		अगर (tp->retrans_out)
			वापस true;

		अगर (!tcp_any_retrans_करोne(sk))
			tp->retrans_stamp = 0;

		DBGUNDO(sk, "partial recovery");
		tcp_unकरो_cwnd_reduction(sk, true);
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPPARTIALUNDO);
		tcp_try_keep_खोलो(sk);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम tcp_identअगरy_packet_loss(काष्ठा sock *sk, पूर्णांक *ack_flag)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (tcp_rtx_queue_empty(sk))
		वापस;

	अगर (unlikely(tcp_is_reno(tp))) अणु
		tcp_newreno_mark_lost(sk, *ack_flag & FLAG_SND_UNA_ADVANCED);
	पूर्ण अन्यथा अगर (tcp_is_rack(sk)) अणु
		u32 prior_retrans = tp->retrans_out;

		अगर (tcp_rack_mark_lost(sk))
			*ack_flag &= ~FLAG_SET_XMIT_TIMER;
		अगर (prior_retrans > tp->retrans_out)
			*ack_flag |= FLAG_LOST_RETRANS;
	पूर्ण
पूर्ण

अटल bool tcp_क्रमce_fast_retransmit(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	वापस after(tcp_highest_sack_seq(tp),
		     tp->snd_una + tp->reordering * tp->mss_cache);
पूर्ण

/* Process an event, which can update packets-in-flight not trivially.
 * Main goal of this function is to calculate new estimate क्रम left_out,
 * taking पूर्णांकo account both packets sitting in receiver's buffer and
 * packets lost by network.
 *
 * Besides that it updates the congestion state when packet loss or ECN
 * is detected. But it करोes not reduce the cwnd, it is करोne by the
 * congestion control later.
 *
 * It करोes _not_ decide what to send, it is made in function
 * tcp_xmit_retransmit_queue().
 */
अटल व्योम tcp_fastretrans_alert(काष्ठा sock *sk, स्थिर u32 prior_snd_una,
				  पूर्णांक num_dupack, पूर्णांक *ack_flag, पूर्णांक *rexmit)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	पूर्णांक fast_rexmit = 0, flag = *ack_flag;
	bool ece_ack = flag & FLAG_ECE;
	bool करो_lost = num_dupack || ((flag & FLAG_DATA_SACKED) &&
				      tcp_क्रमce_fast_retransmit(sk));

	अगर (!tp->packets_out && tp->sacked_out)
		tp->sacked_out = 0;

	/* Now state machine starts.
	 * A. ECE, hence prohibit cwnd unकरोing, the reduction is required. */
	अगर (ece_ack)
		tp->prior_ssthresh = 0;

	/* B. In all the states check क्रम reneging SACKs. */
	अगर (tcp_check_sack_reneging(sk, flag))
		वापस;

	/* C. Check consistency of the current state. */
	tcp_verअगरy_left_out(tp);

	/* D. Check state निकास conditions. State can be terminated
	 *    when high_seq is ACKed. */
	अगर (icsk->icsk_ca_state == TCP_CA_Open) अणु
		WARN_ON(tp->retrans_out != 0 && !tp->syn_data);
		tp->retrans_stamp = 0;
	पूर्ण अन्यथा अगर (!beक्रमe(tp->snd_una, tp->high_seq)) अणु
		चयन (icsk->icsk_ca_state) अणु
		हाल TCP_CA_CWR:
			/* CWR is to be held something *above* high_seq
			 * is ACKed क्रम CWR bit to reach receiver. */
			अगर (tp->snd_una != tp->high_seq) अणु
				tcp_end_cwnd_reduction(sk);
				tcp_set_ca_state(sk, TCP_CA_Open);
			पूर्ण
			अवरोध;

		हाल TCP_CA_Recovery:
			अगर (tcp_is_reno(tp))
				tcp_reset_reno_sack(tp);
			अगर (tcp_try_unकरो_recovery(sk))
				वापस;
			tcp_end_cwnd_reduction(sk);
			अवरोध;
		पूर्ण
	पूर्ण

	/* E. Process state. */
	चयन (icsk->icsk_ca_state) अणु
	हाल TCP_CA_Recovery:
		अगर (!(flag & FLAG_SND_UNA_ADVANCED)) अणु
			अगर (tcp_is_reno(tp))
				tcp_add_reno_sack(sk, num_dupack, ece_ack);
		पूर्ण अन्यथा अणु
			अगर (tcp_try_unकरो_partial(sk, prior_snd_una))
				वापस;
			/* Partial ACK arrived. Force fast retransmit. */
			करो_lost = tcp_क्रमce_fast_retransmit(sk);
		पूर्ण
		अगर (tcp_try_unकरो_dsack(sk)) अणु
			tcp_try_keep_खोलो(sk);
			वापस;
		पूर्ण
		tcp_identअगरy_packet_loss(sk, ack_flag);
		अवरोध;
	हाल TCP_CA_Loss:
		tcp_process_loss(sk, flag, num_dupack, rexmit);
		tcp_identअगरy_packet_loss(sk, ack_flag);
		अगर (!(icsk->icsk_ca_state == TCP_CA_Open ||
		      (*ack_flag & FLAG_LOST_RETRANS)))
			वापस;
		/* Change state अगर cwnd is unकरोne or retransmits are lost */
		fallthrough;
	शेष:
		अगर (tcp_is_reno(tp)) अणु
			अगर (flag & FLAG_SND_UNA_ADVANCED)
				tcp_reset_reno_sack(tp);
			tcp_add_reno_sack(sk, num_dupack, ece_ack);
		पूर्ण

		अगर (icsk->icsk_ca_state <= TCP_CA_Disorder)
			tcp_try_unकरो_dsack(sk);

		tcp_identअगरy_packet_loss(sk, ack_flag);
		अगर (!tcp_समय_प्रकारo_recover(sk, flag)) अणु
			tcp_try_to_खोलो(sk, flag);
			वापस;
		पूर्ण

		/* MTU probe failure: करोn't reduce cwnd */
		अगर (icsk->icsk_ca_state < TCP_CA_CWR &&
		    icsk->icsk_mtup.probe_size &&
		    tp->snd_una == tp->mtu_probe.probe_seq_start) अणु
			tcp_mtup_probe_failed(sk);
			/* Restores the reduction we did in tcp_mtup_probe() */
			tp->snd_cwnd++;
			tcp_simple_retransmit(sk);
			वापस;
		पूर्ण

		/* Otherwise enter Recovery state */
		tcp_enter_recovery(sk, ece_ack);
		fast_rexmit = 1;
	पूर्ण

	अगर (!tcp_is_rack(sk) && करो_lost)
		tcp_update_scoreboard(sk, fast_rexmit);
	*rexmit = REXMIT_LOST;
पूर्ण

अटल व्योम tcp_update_rtt_min(काष्ठा sock *sk, u32 rtt_us, स्थिर पूर्णांक flag)
अणु
	u32 wlen = sock_net(sk)->ipv4.sysctl_tcp_min_rtt_wlen * HZ;
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर ((flag & FLAG_ACK_MAYBE_DELAYED) && rtt_us > tcp_min_rtt(tp)) अणु
		/* If the remote keeps वापसing delayed ACKs, eventually
		 * the min filter would pick it up and overestimate the
		 * prop. delay when it expires. Skip suspected delayed ACKs.
		 */
		वापस;
	पूर्ण
	minmax_running_min(&tp->rtt_min, wlen, tcp_jअगरfies32,
			   rtt_us ? : jअगरfies_to_usecs(1));
पूर्ण

अटल bool tcp_ack_update_rtt(काष्ठा sock *sk, स्थिर पूर्णांक flag,
			       दीर्घ seq_rtt_us, दीर्घ sack_rtt_us,
			       दीर्घ ca_rtt_us, काष्ठा rate_sample *rs)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);

	/* Prefer RTT measured from ACK's timing to TS-ECR. This is because
	 * broken middle-boxes or peers may corrupt TS-ECR fields. But
	 * Karn's algorithm क्रमbids taking RTT अगर some retransmitted data
	 * is acked (RFC6298).
	 */
	अगर (seq_rtt_us < 0)
		seq_rtt_us = sack_rtt_us;

	/* RTTM Rule: A TSecr value received in a segment is used to
	 * update the averaged RTT measurement only अगर the segment
	 * acknowledges some new data, i.e., only अगर it advances the
	 * left edge of the send winकरोw.
	 * See draft-ietf-tcplw-high-perक्रमmance-00, section 3.3.
	 */
	अगर (seq_rtt_us < 0 && tp->rx_opt.saw_tstamp && tp->rx_opt.rcv_tsecr &&
	    flag & FLAG_ACKED) अणु
		u32 delta = tcp_समय_stamp(tp) - tp->rx_opt.rcv_tsecr;

		अगर (likely(delta < पूर्णांक_उच्च / (USEC_PER_SEC / TCP_TS_HZ))) अणु
			अगर (!delta)
				delta = 1;
			seq_rtt_us = delta * (USEC_PER_SEC / TCP_TS_HZ);
			ca_rtt_us = seq_rtt_us;
		पूर्ण
	पूर्ण
	rs->rtt_us = ca_rtt_us; /* RTT of last (S)ACKed packet (or -1) */
	अगर (seq_rtt_us < 0)
		वापस false;

	/* ca_rtt_us >= 0 is counting on the invariant that ca_rtt_us is
	 * always taken together with ACK, SACK, or TS-opts. Any negative
	 * values will be skipped with the seq_rtt_us < 0 check above.
	 */
	tcp_update_rtt_min(sk, ca_rtt_us, flag);
	tcp_rtt_estimator(sk, seq_rtt_us);
	tcp_set_rto(sk);

	/* RFC6298: only reset backoff on valid RTT measurement. */
	inet_csk(sk)->icsk_backoff = 0;
	वापस true;
पूर्ण

/* Compute समय elapsed between (last) SYNACK and the ACK completing 3WHS. */
व्योम tcp_synack_rtt_meas(काष्ठा sock *sk, काष्ठा request_sock *req)
अणु
	काष्ठा rate_sample rs;
	दीर्घ rtt_us = -1L;

	अगर (req && !req->num_retrans && tcp_rsk(req)->snt_synack)
		rtt_us = tcp_stamp_us_delta(tcp_घड़ी_us(), tcp_rsk(req)->snt_synack);

	tcp_ack_update_rtt(sk, FLAG_SYN_ACKED, rtt_us, -1L, rtt_us, &rs);
पूर्ण


अटल व्योम tcp_cong_aव्योम(काष्ठा sock *sk, u32 ack, u32 acked)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	icsk->icsk_ca_ops->cong_aव्योम(sk, ack, acked);
	tcp_sk(sk)->snd_cwnd_stamp = tcp_jअगरfies32;
पूर्ण

/* Restart समयr after क्रमward progress on connection.
 * RFC2988 recommends to restart समयr to now+rto.
 */
व्योम tcp_rearm_rto(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	/* If the retrans समयr is currently being used by Fast Open
	 * क्रम SYN-ACK retrans purpose, stay put.
	 */
	अगर (rcu_access_poपूर्णांकer(tp->fastखोलो_rsk))
		वापस;

	अगर (!tp->packets_out) अणु
		inet_csk_clear_xmit_समयr(sk, ICSK_TIME_RETRANS);
	पूर्ण अन्यथा अणु
		u32 rto = inet_csk(sk)->icsk_rto;
		/* Offset the समय elapsed after installing regular RTO */
		अगर (icsk->icsk_pending == ICSK_TIME_REO_TIMEOUT ||
		    icsk->icsk_pending == ICSK_TIME_LOSS_PROBE) अणु
			s64 delta_us = tcp_rto_delta_us(sk);
			/* delta_us may not be positive अगर the socket is locked
			 * when the retrans समयr fires and is rescheduled.
			 */
			rto = usecs_to_jअगरfies(max_t(पूर्णांक, delta_us, 1));
		पूर्ण
		tcp_reset_xmit_समयr(sk, ICSK_TIME_RETRANS, rto,
				     TCP_RTO_MAX);
	पूर्ण
पूर्ण

/* Try to schedule a loss probe; अगर that करोesn't work, then schedule an RTO. */
अटल व्योम tcp_set_xmit_समयr(काष्ठा sock *sk)
अणु
	अगर (!tcp_schedule_loss_probe(sk, true))
		tcp_rearm_rto(sk);
पूर्ण

/* If we get here, the whole TSO packet has not been acked. */
अटल u32 tcp_tso_acked(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 packets_acked;

	BUG_ON(!after(TCP_SKB_CB(skb)->end_seq, tp->snd_una));

	packets_acked = tcp_skb_pcount(skb);
	अगर (tcp_trim_head(sk, skb, tp->snd_una - TCP_SKB_CB(skb)->seq))
		वापस 0;
	packets_acked -= tcp_skb_pcount(skb);

	अगर (packets_acked) अणु
		BUG_ON(tcp_skb_pcount(skb) == 0);
		BUG_ON(!beक्रमe(TCP_SKB_CB(skb)->seq, TCP_SKB_CB(skb)->end_seq));
	पूर्ण

	वापस packets_acked;
पूर्ण

अटल व्योम tcp_ack_tstamp(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			   स्थिर काष्ठा sk_buff *ack_skb, u32 prior_snd_una)
अणु
	स्थिर काष्ठा skb_shared_info *shinfo;

	/* Aव्योम cache line misses to get skb_shinfo() and shinfo->tx_flags */
	अगर (likely(!TCP_SKB_CB(skb)->txstamp_ack))
		वापस;

	shinfo = skb_shinfo(skb);
	अगर (!beक्रमe(shinfo->tskey, prior_snd_una) &&
	    beक्रमe(shinfo->tskey, tcp_sk(sk)->snd_una)) अणु
		tcp_skb_tsorted_save(skb) अणु
			__skb_tstamp_tx(skb, ack_skb, शून्य, sk, SCM_TSTAMP_ACK);
		पूर्ण tcp_skb_tsorted_restore(skb);
	पूर्ण
पूर्ण

/* Remove acknowledged frames from the retransmission queue. If our packet
 * is beक्रमe the ack sequence we can discard it as it's confirmed to have
 * arrived at the other end.
 */
अटल पूर्णांक tcp_clean_rtx_queue(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *ack_skb,
			       u32 prior_fack, u32 prior_snd_una,
			       काष्ठा tcp_sacktag_state *sack, bool ece_ack)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	u64 first_ackt, last_ackt;
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 prior_sacked = tp->sacked_out;
	u32 reord = tp->snd_nxt; /* lowest acked un-retx un-sacked seq */
	काष्ठा sk_buff *skb, *next;
	bool fully_acked = true;
	दीर्घ sack_rtt_us = -1L;
	दीर्घ seq_rtt_us = -1L;
	दीर्घ ca_rtt_us = -1L;
	u32 pkts_acked = 0;
	u32 last_in_flight = 0;
	bool rtt_update;
	पूर्णांक flag = 0;

	first_ackt = 0;

	क्रम (skb = skb_rb_first(&sk->tcp_rtx_queue); skb; skb = next) अणु
		काष्ठा tcp_skb_cb *scb = TCP_SKB_CB(skb);
		स्थिर u32 start_seq = scb->seq;
		u8 sacked = scb->sacked;
		u32 acked_pcount;

		/* Determine how many packets and what bytes were acked, tso and अन्यथा */
		अगर (after(scb->end_seq, tp->snd_una)) अणु
			अगर (tcp_skb_pcount(skb) == 1 ||
			    !after(tp->snd_una, scb->seq))
				अवरोध;

			acked_pcount = tcp_tso_acked(sk, skb);
			अगर (!acked_pcount)
				अवरोध;
			fully_acked = false;
		पूर्ण अन्यथा अणु
			acked_pcount = tcp_skb_pcount(skb);
		पूर्ण

		अगर (unlikely(sacked & TCPCB_RETRANS)) अणु
			अगर (sacked & TCPCB_SACKED_RETRANS)
				tp->retrans_out -= acked_pcount;
			flag |= FLAG_RETRANS_DATA_ACKED;
		पूर्ण अन्यथा अगर (!(sacked & TCPCB_SACKED_ACKED)) अणु
			last_ackt = tcp_skb_बारtamp_us(skb);
			WARN_ON_ONCE(last_ackt == 0);
			अगर (!first_ackt)
				first_ackt = last_ackt;

			last_in_flight = TCP_SKB_CB(skb)->tx.in_flight;
			अगर (beक्रमe(start_seq, reord))
				reord = start_seq;
			अगर (!after(scb->end_seq, tp->high_seq))
				flag |= FLAG_ORIG_SACK_ACKED;
		पूर्ण

		अगर (sacked & TCPCB_SACKED_ACKED) अणु
			tp->sacked_out -= acked_pcount;
		पूर्ण अन्यथा अगर (tcp_is_sack(tp)) अणु
			tcp_count_delivered(tp, acked_pcount, ece_ack);
			अगर (!tcp_skb_spurious_retrans(tp, skb))
				tcp_rack_advance(tp, sacked, scb->end_seq,
						 tcp_skb_बारtamp_us(skb));
		पूर्ण
		अगर (sacked & TCPCB_LOST)
			tp->lost_out -= acked_pcount;

		tp->packets_out -= acked_pcount;
		pkts_acked += acked_pcount;
		tcp_rate_skb_delivered(sk, skb, sack->rate);

		/* Initial outgoing SYN's get put onto the ग_लिखो_queue
		 * just like anything अन्यथा we transmit.  It is not
		 * true data, and अगर we misinक्रमm our callers that
		 * this ACK acks real data, we will erroneously निकास
		 * connection startup slow start one packet too
		 * quickly.  This is severely frowned upon behavior.
		 */
		अगर (likely(!(scb->tcp_flags & TCPHDR_SYN))) अणु
			flag |= FLAG_DATA_ACKED;
		पूर्ण अन्यथा अणु
			flag |= FLAG_SYN_ACKED;
			tp->retrans_stamp = 0;
		पूर्ण

		अगर (!fully_acked)
			अवरोध;

		tcp_ack_tstamp(sk, skb, ack_skb, prior_snd_una);

		next = skb_rb_next(skb);
		अगर (unlikely(skb == tp->retransmit_skb_hपूर्णांक))
			tp->retransmit_skb_hपूर्णांक = शून्य;
		अगर (unlikely(skb == tp->lost_skb_hपूर्णांक))
			tp->lost_skb_hपूर्णांक = शून्य;
		tcp_highest_sack_replace(sk, skb, next);
		tcp_rtx_queue_unlink_and_मुक्त(skb, sk);
	पूर्ण

	अगर (!skb)
		tcp_chrono_stop(sk, TCP_CHRONO_BUSY);

	अगर (likely(between(tp->snd_up, prior_snd_una, tp->snd_una)))
		tp->snd_up = tp->snd_una;

	अगर (skb) अणु
		tcp_ack_tstamp(sk, skb, ack_skb, prior_snd_una);
		अगर (TCP_SKB_CB(skb)->sacked & TCPCB_SACKED_ACKED)
			flag |= FLAG_SACK_RENEGING;
	पूर्ण

	अगर (likely(first_ackt) && !(flag & FLAG_RETRANS_DATA_ACKED)) अणु
		seq_rtt_us = tcp_stamp_us_delta(tp->tcp_mstamp, first_ackt);
		ca_rtt_us = tcp_stamp_us_delta(tp->tcp_mstamp, last_ackt);

		अगर (pkts_acked == 1 && last_in_flight < tp->mss_cache &&
		    last_in_flight && !prior_sacked && fully_acked &&
		    sack->rate->prior_delivered + 1 == tp->delivered &&
		    !(flag & (FLAG_CA_ALERT | FLAG_SYN_ACKED))) अणु
			/* Conservatively mark a delayed ACK. It's typically
			 * from a lone runt packet over the round trip to
			 * a receiver w/o out-of-order or CE events.
			 */
			flag |= FLAG_ACK_MAYBE_DELAYED;
		पूर्ण
	पूर्ण
	अगर (sack->first_sackt) अणु
		sack_rtt_us = tcp_stamp_us_delta(tp->tcp_mstamp, sack->first_sackt);
		ca_rtt_us = tcp_stamp_us_delta(tp->tcp_mstamp, sack->last_sackt);
	पूर्ण
	rtt_update = tcp_ack_update_rtt(sk, flag, seq_rtt_us, sack_rtt_us,
					ca_rtt_us, sack->rate);

	अगर (flag & FLAG_ACKED) अणु
		flag |= FLAG_SET_XMIT_TIMER;  /* set TLP or RTO समयr */
		अगर (unlikely(icsk->icsk_mtup.probe_size &&
			     !after(tp->mtu_probe.probe_seq_end, tp->snd_una))) अणु
			tcp_mtup_probe_success(sk);
		पूर्ण

		अगर (tcp_is_reno(tp)) अणु
			tcp_हटाओ_reno_sacks(sk, pkts_acked, ece_ack);

			/* If any of the cumulatively ACKed segments was
			 * retransmitted, non-SACK हाल cannot confirm that
			 * progress was due to original transmission due to
			 * lack of TCPCB_SACKED_ACKED bits even अगर some of
			 * the packets may have been never retransmitted.
			 */
			अगर (flag & FLAG_RETRANS_DATA_ACKED)
				flag &= ~FLAG_ORIG_SACK_ACKED;
		पूर्ण अन्यथा अणु
			पूर्णांक delta;

			/* Non-retransmitted hole got filled? That's reordering */
			अगर (beक्रमe(reord, prior_fack))
				tcp_check_sack_reordering(sk, reord, 0);

			delta = prior_sacked - tp->sacked_out;
			tp->lost_cnt_hपूर्णांक -= min(tp->lost_cnt_hपूर्णांक, delta);
		पूर्ण
	पूर्ण अन्यथा अगर (skb && rtt_update && sack_rtt_us >= 0 &&
		   sack_rtt_us > tcp_stamp_us_delta(tp->tcp_mstamp,
						    tcp_skb_बारtamp_us(skb))) अणु
		/* Do not re-arm RTO अगर the sack RTT is measured from data sent
		 * after when the head was last (re)transmitted. Otherwise the
		 * समयout may जारी to extend in loss recovery.
		 */
		flag |= FLAG_SET_XMIT_TIMER;  /* set TLP or RTO समयr */
	पूर्ण

	अगर (icsk->icsk_ca_ops->pkts_acked) अणु
		काष्ठा ack_sample sample = अणु .pkts_acked = pkts_acked,
					     .rtt_us = sack->rate->rtt_us,
					     .in_flight = last_in_flight पूर्ण;

		icsk->icsk_ca_ops->pkts_acked(sk, &sample);
	पूर्ण

#अगर FASTRETRANS_DEBUG > 0
	WARN_ON((पूर्णांक)tp->sacked_out < 0);
	WARN_ON((पूर्णांक)tp->lost_out < 0);
	WARN_ON((पूर्णांक)tp->retrans_out < 0);
	अगर (!tp->packets_out && tcp_is_sack(tp)) अणु
		icsk = inet_csk(sk);
		अगर (tp->lost_out) अणु
			pr_debug("Leak l=%u %d\n",
				 tp->lost_out, icsk->icsk_ca_state);
			tp->lost_out = 0;
		पूर्ण
		अगर (tp->sacked_out) अणु
			pr_debug("Leak s=%u %d\n",
				 tp->sacked_out, icsk->icsk_ca_state);
			tp->sacked_out = 0;
		पूर्ण
		अगर (tp->retrans_out) अणु
			pr_debug("Leak r=%u %d\n",
				 tp->retrans_out, icsk->icsk_ca_state);
			tp->retrans_out = 0;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस flag;
पूर्ण

अटल व्योम tcp_ack_probe(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा sk_buff *head = tcp_send_head(sk);
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);

	/* Was it a usable winकरोw खोलो? */
	अगर (!head)
		वापस;
	अगर (!after(TCP_SKB_CB(head)->end_seq, tcp_wnd_end(tp))) अणु
		icsk->icsk_backoff = 0;
		icsk->icsk_probes_tstamp = 0;
		inet_csk_clear_xmit_समयr(sk, ICSK_TIME_PROBE0);
		/* Socket must be waked up by subsequent tcp_data_snd_check().
		 * This function is not क्रम अक्रमom using!
		 */
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ when = tcp_probe0_when(sk, TCP_RTO_MAX);

		when = tcp_clamp_probe0_to_user_समयout(sk, when);
		tcp_reset_xmit_समयr(sk, ICSK_TIME_PROBE0, when, TCP_RTO_MAX);
	पूर्ण
पूर्ण

अटल अंतरभूत bool tcp_ack_is_dubious(स्थिर काष्ठा sock *sk, स्थिर पूर्णांक flag)
अणु
	वापस !(flag & FLAG_NOT_DUP) || (flag & FLAG_CA_ALERT) ||
		inet_csk(sk)->icsk_ca_state != TCP_CA_Open;
पूर्ण

/* Decide wheather to run the increase function of congestion control. */
अटल अंतरभूत bool tcp_may_उठाओ_cwnd(स्थिर काष्ठा sock *sk, स्थिर पूर्णांक flag)
अणु
	/* If reordering is high then always grow cwnd whenever data is
	 * delivered regardless of its ordering. Otherwise stay conservative
	 * and only grow cwnd on in-order delivery (RFC5681). A stretched ACK w/
	 * new SACK or ECE mark may first advance cwnd here and later reduce
	 * cwnd in tcp_fastretrans_alert() based on more states.
	 */
	अगर (tcp_sk(sk)->reordering > sock_net(sk)->ipv4.sysctl_tcp_reordering)
		वापस flag & FLAG_FORWARD_PROGRESS;

	वापस flag & FLAG_DATA_ACKED;
पूर्ण

/* The "ultimate" congestion control function that aims to replace the rigid
 * cwnd increase and decrease control (tcp_cong_aव्योम,tcp_*cwnd_reduction).
 * It's called toward the end of processing an ACK with precise rate
 * inक्रमmation. All transmission or retransmission are delayed afterwards.
 */
अटल व्योम tcp_cong_control(काष्ठा sock *sk, u32 ack, u32 acked_sacked,
			     पूर्णांक flag, स्थिर काष्ठा rate_sample *rs)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	अगर (icsk->icsk_ca_ops->cong_control) अणु
		icsk->icsk_ca_ops->cong_control(sk, rs);
		वापस;
	पूर्ण

	अगर (tcp_in_cwnd_reduction(sk)) अणु
		/* Reduce cwnd अगर state mandates */
		tcp_cwnd_reduction(sk, acked_sacked, rs->losses, flag);
	पूर्ण अन्यथा अगर (tcp_may_उठाओ_cwnd(sk, flag)) अणु
		/* Advance cwnd अगर state allows */
		tcp_cong_aव्योम(sk, ack, acked_sacked);
	पूर्ण
	tcp_update_pacing_rate(sk);
पूर्ण

/* Check that winकरोw update is acceptable.
 * The function assumes that snd_una<=ack<=snd_next.
 */
अटल अंतरभूत bool tcp_may_update_winकरोw(स्थिर काष्ठा tcp_sock *tp,
					स्थिर u32 ack, स्थिर u32 ack_seq,
					स्थिर u32 nwin)
अणु
	वापस	after(ack, tp->snd_una) ||
		after(ack_seq, tp->snd_wl1) ||
		(ack_seq == tp->snd_wl1 && nwin > tp->snd_wnd);
पूर्ण

/* If we update tp->snd_una, also update tp->bytes_acked */
अटल व्योम tcp_snd_una_update(काष्ठा tcp_sock *tp, u32 ack)
अणु
	u32 delta = ack - tp->snd_una;

	sock_owned_by_me((काष्ठा sock *)tp);
	tp->bytes_acked += delta;
	tp->snd_una = ack;
पूर्ण

/* If we update tp->rcv_nxt, also update tp->bytes_received */
अटल व्योम tcp_rcv_nxt_update(काष्ठा tcp_sock *tp, u32 seq)
अणु
	u32 delta = seq - tp->rcv_nxt;

	sock_owned_by_me((काष्ठा sock *)tp);
	tp->bytes_received += delta;
	WRITE_ONCE(tp->rcv_nxt, seq);
पूर्ण

/* Update our send winकरोw.
 *
 * Winकरोw update algorithm, described in RFC793/RFC1122 (used in linux-2.2
 * and in FreeBSD. NetBSD's one is even worse.) is wrong.
 */
अटल पूर्णांक tcp_ack_update_winकरोw(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb, u32 ack,
				 u32 ack_seq)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	पूर्णांक flag = 0;
	u32 nwin = ntohs(tcp_hdr(skb)->winकरोw);

	अगर (likely(!tcp_hdr(skb)->syn))
		nwin <<= tp->rx_opt.snd_wscale;

	अगर (tcp_may_update_winकरोw(tp, ack, ack_seq, nwin)) अणु
		flag |= FLAG_WIN_UPDATE;
		tcp_update_wl(tp, ack_seq);

		अगर (tp->snd_wnd != nwin) अणु
			tp->snd_wnd = nwin;

			/* Note, it is the only place, where
			 * fast path is recovered क्रम sending TCP.
			 */
			tp->pred_flags = 0;
			tcp_fast_path_check(sk);

			अगर (!tcp_ग_लिखो_queue_empty(sk))
				tcp_slow_start_after_idle_check(sk);

			अगर (nwin > tp->max_winकरोw) अणु
				tp->max_winकरोw = nwin;
				tcp_sync_mss(sk, inet_csk(sk)->icsk_pmtu_cookie);
			पूर्ण
		पूर्ण
	पूर्ण

	tcp_snd_una_update(tp, ack);

	वापस flag;
पूर्ण

अटल bool __tcp_oow_rate_limited(काष्ठा net *net, पूर्णांक mib_idx,
				   u32 *last_oow_ack_समय)
अणु
	अगर (*last_oow_ack_समय) अणु
		s32 elapsed = (s32)(tcp_jअगरfies32 - *last_oow_ack_समय);

		अगर (0 <= elapsed && elapsed < net->ipv4.sysctl_tcp_invalid_ratelimit) अणु
			NET_INC_STATS(net, mib_idx);
			वापस true;	/* rate-limited: करोn't send yet! */
		पूर्ण
	पूर्ण

	*last_oow_ack_समय = tcp_jअगरfies32;

	वापस false;	/* not rate-limited: go ahead, send dupack now! */
पूर्ण

/* Return true अगर we're currently rate-limiting out-of-winकरोw ACKs and
 * thus shouldn't send a dupack right now. We rate-limit dupacks in
 * response to out-of-winकरोw SYNs or ACKs to mitigate ACK loops or DoS
 * attacks that send repeated SYNs or ACKs क्रम the same connection. To
 * करो this, we करो not send a duplicate SYNACK or ACK अगर the remote
 * endpoपूर्णांक is sending out-of-winकरोw SYNs or pure ACKs at a high rate.
 */
bool tcp_oow_rate_limited(काष्ठा net *net, स्थिर काष्ठा sk_buff *skb,
			  पूर्णांक mib_idx, u32 *last_oow_ack_समय)
अणु
	/* Data packets without SYNs are not likely part of an ACK loop. */
	अगर ((TCP_SKB_CB(skb)->seq != TCP_SKB_CB(skb)->end_seq) &&
	    !tcp_hdr(skb)->syn)
		वापस false;

	वापस __tcp_oow_rate_limited(net, mib_idx, last_oow_ack_समय);
पूर्ण

/* RFC 5961 7 [ACK Throttling] */
अटल व्योम tcp_send_challenge_ack(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
	/* unरक्षित vars, we करोnt care of overग_लिखोs */
	अटल u32 challenge_बारtamp;
	अटल अचिन्हित पूर्णांक challenge_count;
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा net *net = sock_net(sk);
	u32 count, now;

	/* First check our per-socket dupack rate limit. */
	अगर (__tcp_oow_rate_limited(net,
				   LINUX_MIB_TCPACKSKIPPEDCHALLENGE,
				   &tp->last_oow_ack_समय))
		वापस;

	/* Then check host-wide RFC 5961 rate limit. */
	now = jअगरfies / HZ;
	अगर (now != challenge_बारtamp) अणु
		u32 ack_limit = net->ipv4.sysctl_tcp_challenge_ack_limit;
		u32 half = (ack_limit + 1) >> 1;

		challenge_बारtamp = now;
		WRITE_ONCE(challenge_count, half + pअक्रमom_u32_max(ack_limit));
	पूर्ण
	count = READ_ONCE(challenge_count);
	अगर (count > 0) अणु
		WRITE_ONCE(challenge_count, count - 1);
		NET_INC_STATS(net, LINUX_MIB_TCPCHALLENGEACK);
		tcp_send_ack(sk);
	पूर्ण
पूर्ण

अटल व्योम tcp_store_ts_recent(काष्ठा tcp_sock *tp)
अणु
	tp->rx_opt.ts_recent = tp->rx_opt.rcv_tsval;
	tp->rx_opt.ts_recent_stamp = kसमय_get_seconds();
पूर्ण

अटल व्योम tcp_replace_ts_recent(काष्ठा tcp_sock *tp, u32 seq)
अणु
	अगर (tp->rx_opt.saw_tstamp && !after(seq, tp->rcv_wup)) अणु
		/* PAWS bug workaround wrt. ACK frames, the PAWS discard
		 * extra check below makes sure this can only happen
		 * क्रम pure ACK frames.  -DaveM
		 *
		 * Not only, also it occurs क्रम expired बारtamps.
		 */

		अगर (tcp_paws_check(&tp->rx_opt, 0))
			tcp_store_ts_recent(tp);
	पूर्ण
पूर्ण

/* This routine deals with acks during a TLP episode and ends an episode by
 * resetting tlp_high_seq. Ref: TLP algorithm in draft-ietf-tcpm-rack
 */
अटल व्योम tcp_process_tlp_ack(काष्ठा sock *sk, u32 ack, पूर्णांक flag)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (beक्रमe(ack, tp->tlp_high_seq))
		वापस;

	अगर (!tp->tlp_retrans) अणु
		/* TLP of new data has been acknowledged */
		tp->tlp_high_seq = 0;
	पूर्ण अन्यथा अगर (flag & FLAG_DSACKING_ACK) अणु
		/* This DSACK means original and TLP probe arrived; no loss */
		tp->tlp_high_seq = 0;
	पूर्ण अन्यथा अगर (after(ack, tp->tlp_high_seq)) अणु
		/* ACK advances: there was a loss, so reduce cwnd. Reset
		 * tlp_high_seq in tcp_init_cwnd_reduction()
		 */
		tcp_init_cwnd_reduction(sk);
		tcp_set_ca_state(sk, TCP_CA_CWR);
		tcp_end_cwnd_reduction(sk);
		tcp_try_keep_खोलो(sk);
		NET_INC_STATS(sock_net(sk),
				LINUX_MIB_TCPLOSSPROBERECOVERY);
	पूर्ण अन्यथा अगर (!(flag & (FLAG_SND_UNA_ADVANCED |
			     FLAG_NOT_DUP | FLAG_DATA_SACKED))) अणु
		/* Pure dupack: original and TLP probe arrived; no loss */
		tp->tlp_high_seq = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम tcp_in_ack_event(काष्ठा sock *sk, u32 flags)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	अगर (icsk->icsk_ca_ops->in_ack_event)
		icsk->icsk_ca_ops->in_ack_event(sk, flags);
पूर्ण

/* Congestion control has updated the cwnd alपढ़ोy. So अगर we're in
 * loss recovery then now we करो any new sends (क्रम FRTO) or
 * retransmits (क्रम CA_Loss or CA_recovery) that make sense.
 */
अटल व्योम tcp_xmit_recovery(काष्ठा sock *sk, पूर्णांक rexmit)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (rexmit == REXMIT_NONE || sk->sk_state == TCP_SYN_SENT)
		वापस;

	अगर (unlikely(rexmit == REXMIT_NEW)) अणु
		__tcp_push_pending_frames(sk, tcp_current_mss(sk),
					  TCP_NAGLE_OFF);
		अगर (after(tp->snd_nxt, tp->high_seq))
			वापस;
		tp->frto = 0;
	पूर्ण
	tcp_xmit_retransmit_queue(sk);
पूर्ण

/* Returns the number of packets newly acked or sacked by the current ACK */
अटल u32 tcp_newly_delivered(काष्ठा sock *sk, u32 prior_delivered, पूर्णांक flag)
अणु
	स्थिर काष्ठा net *net = sock_net(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 delivered;

	delivered = tp->delivered - prior_delivered;
	NET_ADD_STATS(net, LINUX_MIB_TCPDELIVERED, delivered);
	अगर (flag & FLAG_ECE)
		NET_ADD_STATS(net, LINUX_MIB_TCPDELIVEREDCE, delivered);

	वापस delivered;
पूर्ण

/* This routine deals with incoming acks, but not outgoing ones. */
अटल पूर्णांक tcp_ack(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb, पूर्णांक flag)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा tcp_sacktag_state sack_state;
	काष्ठा rate_sample rs = अणु .prior_delivered = 0 पूर्ण;
	u32 prior_snd_una = tp->snd_una;
	bool is_sack_reneg = tp->is_sack_reneg;
	u32 ack_seq = TCP_SKB_CB(skb)->seq;
	u32 ack = TCP_SKB_CB(skb)->ack_seq;
	पूर्णांक num_dupack = 0;
	पूर्णांक prior_packets = tp->packets_out;
	u32 delivered = tp->delivered;
	u32 lost = tp->lost;
	पूर्णांक rexmit = REXMIT_NONE; /* Flag to (re)transmit to recover losses */
	u32 prior_fack;

	sack_state.first_sackt = 0;
	sack_state.rate = &rs;
	sack_state.sack_delivered = 0;

	/* We very likely will need to access rtx queue. */
	prefetch(sk->tcp_rtx_queue.rb_node);

	/* If the ack is older than previous acks
	 * then we can probably ignore it.
	 */
	अगर (beक्रमe(ack, prior_snd_una)) अणु
		/* RFC 5961 5.2 [Blind Data Injection Attack].[Mitigation] */
		अगर (beक्रमe(ack, prior_snd_una - tp->max_winकरोw)) अणु
			अगर (!(flag & FLAG_NO_CHALLENGE_ACK))
				tcp_send_challenge_ack(sk, skb);
			वापस -1;
		पूर्ण
		जाओ old_ack;
	पूर्ण

	/* If the ack includes data we haven't sent yet, discard
	 * this segment (RFC793 Section 3.9).
	 */
	अगर (after(ack, tp->snd_nxt))
		वापस -1;

	अगर (after(ack, prior_snd_una)) अणु
		flag |= FLAG_SND_UNA_ADVANCED;
		icsk->icsk_retransmits = 0;

#अगर IS_ENABLED(CONFIG_TLS_DEVICE)
		अगर (अटल_branch_unlikely(&clean_acked_data_enabled.key))
			अगर (icsk->icsk_clean_acked)
				icsk->icsk_clean_acked(sk, ack);
#पूर्ण_अगर
	पूर्ण

	prior_fack = tcp_is_sack(tp) ? tcp_highest_sack_seq(tp) : tp->snd_una;
	rs.prior_in_flight = tcp_packets_in_flight(tp);

	/* ts_recent update must be made after we are sure that the packet
	 * is in winकरोw.
	 */
	अगर (flag & FLAG_UPDATE_TS_RECENT)
		tcp_replace_ts_recent(tp, TCP_SKB_CB(skb)->seq);

	अगर ((flag & (FLAG_SLOWPATH | FLAG_SND_UNA_ADVANCED)) ==
	    FLAG_SND_UNA_ADVANCED) अणु
		/* Winकरोw is स्थिरant, pure क्रमward advance.
		 * No more checks are required.
		 * Note, we use the fact that SND.UNA>=SND.WL2.
		 */
		tcp_update_wl(tp, ack_seq);
		tcp_snd_una_update(tp, ack);
		flag |= FLAG_WIN_UPDATE;

		tcp_in_ack_event(sk, CA_ACK_WIN_UPDATE);

		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPHPACKS);
	पूर्ण अन्यथा अणु
		u32 ack_ev_flags = CA_ACK_SLOWPATH;

		अगर (ack_seq != TCP_SKB_CB(skb)->end_seq)
			flag |= FLAG_DATA;
		अन्यथा
			NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPPUREACKS);

		flag |= tcp_ack_update_winकरोw(sk, skb, ack, ack_seq);

		अगर (TCP_SKB_CB(skb)->sacked)
			flag |= tcp_sacktag_ग_लिखो_queue(sk, skb, prior_snd_una,
							&sack_state);

		अगर (tcp_ecn_rcv_ecn_echo(tp, tcp_hdr(skb))) अणु
			flag |= FLAG_ECE;
			ack_ev_flags |= CA_ACK_ECE;
		पूर्ण

		अगर (sack_state.sack_delivered)
			tcp_count_delivered(tp, sack_state.sack_delivered,
					    flag & FLAG_ECE);

		अगर (flag & FLAG_WIN_UPDATE)
			ack_ev_flags |= CA_ACK_WIN_UPDATE;

		tcp_in_ack_event(sk, ack_ev_flags);
	पूर्ण

	/* This is a deviation from RFC3168 since it states that:
	 * "When the TCP data sender is पढ़ोy to set the CWR bit after reducing
	 * the congestion winकरोw, it SHOULD set the CWR bit only on the first
	 * new data packet that it transmits."
	 * We accept CWR on pure ACKs to be more robust
	 * with widely-deployed TCP implementations that करो this.
	 */
	tcp_ecn_accept_cwr(sk, skb);

	/* We passed data and got it acked, हटाओ any soft error
	 * log. Something worked...
	 */
	sk->sk_err_soft = 0;
	icsk->icsk_probes_out = 0;
	tp->rcv_tstamp = tcp_jअगरfies32;
	अगर (!prior_packets)
		जाओ no_queue;

	/* See अगर we can take anything off of the retransmit queue. */
	flag |= tcp_clean_rtx_queue(sk, skb, prior_fack, prior_snd_una,
				    &sack_state, flag & FLAG_ECE);

	tcp_rack_update_reo_wnd(sk, &rs);

	अगर (tp->tlp_high_seq)
		tcp_process_tlp_ack(sk, ack, flag);

	अगर (tcp_ack_is_dubious(sk, flag)) अणु
		अगर (!(flag & (FLAG_SND_UNA_ADVANCED | FLAG_NOT_DUP))) अणु
			num_dupack = 1;
			/* Consider अगर pure acks were aggregated in tcp_add_backlog() */
			अगर (!(flag & FLAG_DATA))
				num_dupack = max_t(u16, 1, skb_shinfo(skb)->gso_segs);
		पूर्ण
		tcp_fastretrans_alert(sk, prior_snd_una, num_dupack, &flag,
				      &rexmit);
	पूर्ण

	/* If needed, reset TLP/RTO समयr when RACK करोesn't set. */
	अगर (flag & FLAG_SET_XMIT_TIMER)
		tcp_set_xmit_समयr(sk);

	अगर ((flag & FLAG_FORWARD_PROGRESS) || !(flag & FLAG_NOT_DUP))
		sk_dst_confirm(sk);

	delivered = tcp_newly_delivered(sk, delivered, flag);
	lost = tp->lost - lost;			/* freshly marked lost */
	rs.is_ack_delayed = !!(flag & FLAG_ACK_MAYBE_DELAYED);
	tcp_rate_gen(sk, delivered, lost, is_sack_reneg, sack_state.rate);
	tcp_cong_control(sk, ack, delivered, flag, sack_state.rate);
	tcp_xmit_recovery(sk, rexmit);
	वापस 1;

no_queue:
	/* If data was DSACKed, see अगर we can unकरो a cwnd reduction. */
	अगर (flag & FLAG_DSACKING_ACK) अणु
		tcp_fastretrans_alert(sk, prior_snd_una, num_dupack, &flag,
				      &rexmit);
		tcp_newly_delivered(sk, delivered, flag);
	पूर्ण
	/* If this ack खोलोs up a zero winकरोw, clear backoff.  It was
	 * being used to समय the probes, and is probably far higher than
	 * it needs to be क्रम normal retransmission.
	 */
	tcp_ack_probe(sk);

	अगर (tp->tlp_high_seq)
		tcp_process_tlp_ack(sk, ack, flag);
	वापस 1;

old_ack:
	/* If data was SACKed, tag it and see अगर we should send more data.
	 * If data was DSACKed, see अगर we can unकरो a cwnd reduction.
	 */
	अगर (TCP_SKB_CB(skb)->sacked) अणु
		flag |= tcp_sacktag_ग_लिखो_queue(sk, skb, prior_snd_una,
						&sack_state);
		tcp_fastretrans_alert(sk, prior_snd_una, num_dupack, &flag,
				      &rexmit);
		tcp_newly_delivered(sk, delivered, flag);
		tcp_xmit_recovery(sk, rexmit);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tcp_parse_fastखोलो_option(पूर्णांक len, स्थिर अचिन्हित अक्षर *cookie,
				      bool syn, काष्ठा tcp_fastखोलो_cookie *foc,
				      bool exp_opt)
अणु
	/* Valid only in SYN or SYN-ACK with an even length.  */
	अगर (!foc || !syn || len < 0 || (len & 1))
		वापस;

	अगर (len >= TCP_FASTOPEN_COOKIE_MIN &&
	    len <= TCP_FASTOPEN_COOKIE_MAX)
		स_नकल(foc->val, cookie, len);
	अन्यथा अगर (len != 0)
		len = -1;
	foc->len = len;
	foc->exp = exp_opt;
पूर्ण

अटल bool smc_parse_options(स्थिर काष्ठा tcphdr *th,
			      काष्ठा tcp_options_received *opt_rx,
			      स्थिर अचिन्हित अक्षर *ptr,
			      पूर्णांक opsize)
अणु
#अगर IS_ENABLED(CONFIG_SMC)
	अगर (अटल_branch_unlikely(&tcp_have_smc)) अणु
		अगर (th->syn && !(opsize & 1) &&
		    opsize >= TCPOLEN_EXP_SMC_BASE &&
		    get_unaligned_be32(ptr) == TCPOPT_SMC_MAGIC) अणु
			opt_rx->smc_ok = 1;
			वापस true;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस false;
पूर्ण

/* Try to parse the MSS option from the TCP header. Return 0 on failure, clamped
 * value on success.
 */
अटल u16 tcp_parse_mss_option(स्थिर काष्ठा tcphdr *th, u16 user_mss)
अणु
	स्थिर अचिन्हित अक्षर *ptr = (स्थिर अचिन्हित अक्षर *)(th + 1);
	पूर्णांक length = (th->करोff * 4) - माप(काष्ठा tcphdr);
	u16 mss = 0;

	जबतक (length > 0) अणु
		पूर्णांक opcode = *ptr++;
		पूर्णांक opsize;

		चयन (opcode) अणु
		हाल TCPOPT_EOL:
			वापस mss;
		हाल TCPOPT_NOP:	/* Ref: RFC 793 section 3.1 */
			length--;
			जारी;
		शेष:
			अगर (length < 2)
				वापस mss;
			opsize = *ptr++;
			अगर (opsize < 2) /* "silly options" */
				वापस mss;
			अगर (opsize > length)
				वापस mss;	/* fail on partial options */
			अगर (opcode == TCPOPT_MSS && opsize == TCPOLEN_MSS) अणु
				u16 in_mss = get_unaligned_be16(ptr);

				अगर (in_mss) अणु
					अगर (user_mss && user_mss < in_mss)
						in_mss = user_mss;
					mss = in_mss;
				पूर्ण
			पूर्ण
			ptr += opsize - 2;
			length -= opsize;
		पूर्ण
	पूर्ण
	वापस mss;
पूर्ण

/* Look क्रम tcp options. Normally only called on SYN and SYNACK packets.
 * But, this can also be called on packets in the established flow when
 * the fast version below fails.
 */
व्योम tcp_parse_options(स्थिर काष्ठा net *net,
		       स्थिर काष्ठा sk_buff *skb,
		       काष्ठा tcp_options_received *opt_rx, पूर्णांक estab,
		       काष्ठा tcp_fastखोलो_cookie *foc)
अणु
	स्थिर अचिन्हित अक्षर *ptr;
	स्थिर काष्ठा tcphdr *th = tcp_hdr(skb);
	पूर्णांक length = (th->करोff * 4) - माप(काष्ठा tcphdr);

	ptr = (स्थिर अचिन्हित अक्षर *)(th + 1);
	opt_rx->saw_tstamp = 0;
	opt_rx->saw_unknown = 0;

	जबतक (length > 0) अणु
		पूर्णांक opcode = *ptr++;
		पूर्णांक opsize;

		चयन (opcode) अणु
		हाल TCPOPT_EOL:
			वापस;
		हाल TCPOPT_NOP:	/* Ref: RFC 793 section 3.1 */
			length--;
			जारी;
		शेष:
			अगर (length < 2)
				वापस;
			opsize = *ptr++;
			अगर (opsize < 2) /* "silly options" */
				वापस;
			अगर (opsize > length)
				वापस;	/* करोn't parse partial options */
			चयन (opcode) अणु
			हाल TCPOPT_MSS:
				अगर (opsize == TCPOLEN_MSS && th->syn && !estab) अणु
					u16 in_mss = get_unaligned_be16(ptr);
					अगर (in_mss) अणु
						अगर (opt_rx->user_mss &&
						    opt_rx->user_mss < in_mss)
							in_mss = opt_rx->user_mss;
						opt_rx->mss_clamp = in_mss;
					पूर्ण
				पूर्ण
				अवरोध;
			हाल TCPOPT_WINDOW:
				अगर (opsize == TCPOLEN_WINDOW && th->syn &&
				    !estab && net->ipv4.sysctl_tcp_winकरोw_scaling) अणु
					__u8 snd_wscale = *(__u8 *)ptr;
					opt_rx->wscale_ok = 1;
					अगर (snd_wscale > TCP_MAX_WSCALE) अणु
						net_info_ratelimited("%s: Illegal window scaling value %d > %u received\n",
								     __func__,
								     snd_wscale,
								     TCP_MAX_WSCALE);
						snd_wscale = TCP_MAX_WSCALE;
					पूर्ण
					opt_rx->snd_wscale = snd_wscale;
				पूर्ण
				अवरोध;
			हाल TCPOPT_TIMESTAMP:
				अगर ((opsize == TCPOLEN_TIMESTAMP) &&
				    ((estab && opt_rx->tstamp_ok) ||
				     (!estab && net->ipv4.sysctl_tcp_बारtamps))) अणु
					opt_rx->saw_tstamp = 1;
					opt_rx->rcv_tsval = get_unaligned_be32(ptr);
					opt_rx->rcv_tsecr = get_unaligned_be32(ptr + 4);
				पूर्ण
				अवरोध;
			हाल TCPOPT_SACK_PERM:
				अगर (opsize == TCPOLEN_SACK_PERM && th->syn &&
				    !estab && net->ipv4.sysctl_tcp_sack) अणु
					opt_rx->sack_ok = TCP_SACK_SEEN;
					tcp_sack_reset(opt_rx);
				पूर्ण
				अवरोध;

			हाल TCPOPT_SACK:
				अगर ((opsize >= (TCPOLEN_SACK_BASE + TCPOLEN_SACK_PERBLOCK)) &&
				   !((opsize - TCPOLEN_SACK_BASE) % TCPOLEN_SACK_PERBLOCK) &&
				   opt_rx->sack_ok) अणु
					TCP_SKB_CB(skb)->sacked = (ptr - 2) - (अचिन्हित अक्षर *)th;
				पूर्ण
				अवरोध;
#अगर_घोषित CONFIG_TCP_MD5SIG
			हाल TCPOPT_MD5SIG:
				/*
				 * The MD5 Hash has alपढ़ोy been
				 * checked (see tcp_vअणु4,6पूर्ण_करो_rcv()).
				 */
				अवरोध;
#पूर्ण_अगर
			हाल TCPOPT_FASTOPEN:
				tcp_parse_fastखोलो_option(
					opsize - TCPOLEN_FASTOPEN_BASE,
					ptr, th->syn, foc, false);
				अवरोध;

			हाल TCPOPT_EXP:
				/* Fast Open option shares code 254 using a
				 * 16 bits magic number.
				 */
				अगर (opsize >= TCPOLEN_EXP_FASTOPEN_BASE &&
				    get_unaligned_be16(ptr) ==
				    TCPOPT_FASTOPEN_MAGIC) अणु
					tcp_parse_fastखोलो_option(opsize -
						TCPOLEN_EXP_FASTOPEN_BASE,
						ptr + 2, th->syn, foc, true);
					अवरोध;
				पूर्ण

				अगर (smc_parse_options(th, opt_rx, ptr, opsize))
					अवरोध;

				opt_rx->saw_unknown = 1;
				अवरोध;

			शेष:
				opt_rx->saw_unknown = 1;
			पूर्ण
			ptr += opsize-2;
			length -= opsize;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(tcp_parse_options);

अटल bool tcp_parse_aligned_बारtamp(काष्ठा tcp_sock *tp, स्थिर काष्ठा tcphdr *th)
अणु
	स्थिर __be32 *ptr = (स्थिर __be32 *)(th + 1);

	अगर (*ptr == htonl((TCPOPT_NOP << 24) | (TCPOPT_NOP << 16)
			  | (TCPOPT_TIMESTAMP << 8) | TCPOLEN_TIMESTAMP)) अणु
		tp->rx_opt.saw_tstamp = 1;
		++ptr;
		tp->rx_opt.rcv_tsval = ntohl(*ptr);
		++ptr;
		अगर (*ptr)
			tp->rx_opt.rcv_tsecr = ntohl(*ptr) - tp->tsoffset;
		अन्यथा
			tp->rx_opt.rcv_tsecr = 0;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* Fast parse options. This hopes to only see बारtamps.
 * If it is wrong it falls back on tcp_parse_options().
 */
अटल bool tcp_fast_parse_options(स्थिर काष्ठा net *net,
				   स्थिर काष्ठा sk_buff *skb,
				   स्थिर काष्ठा tcphdr *th, काष्ठा tcp_sock *tp)
अणु
	/* In the spirit of fast parsing, compare करोff directly to स्थिरant
	 * values.  Because equality is used, लघु करोff can be ignored here.
	 */
	अगर (th->करोff == (माप(*th) / 4)) अणु
		tp->rx_opt.saw_tstamp = 0;
		वापस false;
	पूर्ण अन्यथा अगर (tp->rx_opt.tstamp_ok &&
		   th->करोff == ((माप(*th) + TCPOLEN_TSTAMP_ALIGNED) / 4)) अणु
		अगर (tcp_parse_aligned_बारtamp(tp, th))
			वापस true;
	पूर्ण

	tcp_parse_options(net, skb, &tp->rx_opt, 1, शून्य);
	अगर (tp->rx_opt.saw_tstamp && tp->rx_opt.rcv_tsecr)
		tp->rx_opt.rcv_tsecr -= tp->tsoffset;

	वापस true;
पूर्ण

#अगर_घोषित CONFIG_TCP_MD5SIG
/*
 * Parse MD5 Signature option
 */
स्थिर u8 *tcp_parse_md5sig_option(स्थिर काष्ठा tcphdr *th)
अणु
	पूर्णांक length = (th->करोff << 2) - माप(*th);
	स्थिर u8 *ptr = (स्थिर u8 *)(th + 1);

	/* If not enough data reमुख्यing, we can लघु cut */
	जबतक (length >= TCPOLEN_MD5SIG) अणु
		पूर्णांक opcode = *ptr++;
		पूर्णांक opsize;

		चयन (opcode) अणु
		हाल TCPOPT_EOL:
			वापस शून्य;
		हाल TCPOPT_NOP:
			length--;
			जारी;
		शेष:
			opsize = *ptr++;
			अगर (opsize < 2 || opsize > length)
				वापस शून्य;
			अगर (opcode == TCPOPT_MD5SIG)
				वापस opsize == TCPOLEN_MD5SIG ? ptr : शून्य;
		पूर्ण
		ptr += opsize - 2;
		length -= opsize;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(tcp_parse_md5sig_option);
#पूर्ण_अगर

/* Sorry, PAWS as specअगरied is broken wrt. pure-ACKs -DaveM
 *
 * It is not fatal. If this ACK करोes _not_ change critical state (seqs, winकरोw)
 * it can pass through stack. So, the following predicate verअगरies that
 * this segment is not used क्रम anything but congestion aव्योमance or
 * fast retransmit. Moreover, we even are able to eliminate most of such
 * second order effects, अगर we apply some small "replay" winकरोw (~RTO)
 * to बारtamp space.
 *
 * All these measures still करो not guarantee that we reject wrapped ACKs
 * on networks with high bandwidth, when sequence space is recycled fastly,
 * but it guarantees that such events will be very rare and करो not affect
 * connection seriously. This करोesn't look nice, but alas, PAWS is really
 * buggy extension.
 *
 * [ Later note. Even worse! It is buggy क्रम segments _with_ data. RFC
 * states that events when retransmit arrives after original data are rare.
 * It is a blatant lie. VJ क्रमgot about fast retransmit! 8)8) It is
 * the biggest problem on large घातer networks even with minor reordering.
 * OK, let's give it small replay winकरोw. If peer घड़ी is even 1hz, it is safe
 * up to bandwidth of 18Gigabit/sec. 8) ]
 */

अटल पूर्णांक tcp_disordered_ack(स्थिर काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	स्थिर काष्ठा tcphdr *th = tcp_hdr(skb);
	u32 seq = TCP_SKB_CB(skb)->seq;
	u32 ack = TCP_SKB_CB(skb)->ack_seq;

	वापस (/* 1. Pure ACK with correct sequence number. */
		(th->ack && seq == TCP_SKB_CB(skb)->end_seq && seq == tp->rcv_nxt) &&

		/* 2. ... and duplicate ACK. */
		ack == tp->snd_una &&

		/* 3. ... and करोes not update winकरोw. */
		!tcp_may_update_winकरोw(tp, ack, seq, ntohs(th->winकरोw) << tp->rx_opt.snd_wscale) &&

		/* 4. ... and sits in replay winकरोw. */
		(s32)(tp->rx_opt.ts_recent - tp->rx_opt.rcv_tsval) <= (inet_csk(sk)->icsk_rto * 1024) / HZ);
पूर्ण

अटल अंतरभूत bool tcp_paws_discard(स्थिर काष्ठा sock *sk,
				   स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);

	वापस !tcp_paws_check(&tp->rx_opt, TCP_PAWS_WINDOW) &&
	       !tcp_disordered_ack(sk, skb);
पूर्ण

/* Check segment sequence number क्रम validity.
 *
 * Segment controls are considered valid, अगर the segment
 * fits to the winकरोw after truncation to the winकरोw. Acceptability
 * of data (and SYN, FIN, of course) is checked separately.
 * See tcp_data_queue(), क्रम example.
 *
 * Also, controls (RST is मुख्य one) are accepted using RCV.WUP instead
 * of RCV.NXT. Peer still did not advance his SND.UNA when we
 * delayed ACK, so that hisSND.UNA<=ourRCV.WUP.
 * (borrowed from मुक्तbsd)
 */

अटल अंतरभूत bool tcp_sequence(स्थिर काष्ठा tcp_sock *tp, u32 seq, u32 end_seq)
अणु
	वापस	!beक्रमe(end_seq, tp->rcv_wup) &&
		!after(seq, tp->rcv_nxt + tcp_receive_winकरोw(tp));
पूर्ण

/* When we get a reset we करो this. */
व्योम tcp_reset(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	trace_tcp_receive_reset(sk);

	अगर (sk_is_mptcp(sk))
		mptcp_incoming_options(sk, skb);

	/* We want the right error as BSD sees it (and indeed as we करो). */
	चयन (sk->sk_state) अणु
	हाल TCP_SYN_SENT:
		sk->sk_err = ECONNREFUSED;
		अवरोध;
	हाल TCP_CLOSE_WAIT:
		sk->sk_err = EPIPE;
		अवरोध;
	हाल TCP_CLOSE:
		वापस;
	शेष:
		sk->sk_err = ECONNRESET;
	पूर्ण
	/* This barrier is coupled with smp_rmb() in tcp_poll() */
	smp_wmb();

	tcp_ग_लिखो_queue_purge(sk);
	tcp_करोne(sk);

	अगर (!sock_flag(sk, SOCK_DEAD))
		sk->sk_error_report(sk);
पूर्ण

/*
 * 	Process the FIN bit. This now behaves as it is supposed to work
 *	and the FIN takes effect when it is validly part of sequence
 *	space. Not beक्रमe when we get holes.
 *
 *	If we are ESTABLISHED, a received fin moves us to CLOSE-WAIT
 *	(and thence onto LAST-ACK and finally, CLOSE, we never enter
 *	TIME-WAIT)
 *
 *	If we are in FINWAIT-1, a received FIN indicates simultaneous
 *	बंद and we go पूर्णांकo CLOSING (and later onto TIME-WAIT)
 *
 *	If we are in FINWAIT-2, a received FIN moves us to TIME-WAIT.
 */
व्योम tcp_fin(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	inet_csk_schedule_ack(sk);

	sk->sk_shutकरोwn |= RCV_SHUTDOWN;
	sock_set_flag(sk, SOCK_DONE);

	चयन (sk->sk_state) अणु
	हाल TCP_SYN_RECV:
	हाल TCP_ESTABLISHED:
		/* Move to CLOSE_WAIT */
		tcp_set_state(sk, TCP_CLOSE_WAIT);
		inet_csk_enter_pingpong_mode(sk);
		अवरोध;

	हाल TCP_CLOSE_WAIT:
	हाल TCP_CLOSING:
		/* Received a retransmission of the FIN, करो
		 * nothing.
		 */
		अवरोध;
	हाल TCP_LAST_ACK:
		/* RFC793: Reमुख्य in the LAST-ACK state. */
		अवरोध;

	हाल TCP_FIN_WAIT1:
		/* This हाल occurs when a simultaneous बंद
		 * happens, we must ack the received FIN and
		 * enter the CLOSING state.
		 */
		tcp_send_ack(sk);
		tcp_set_state(sk, TCP_CLOSING);
		अवरोध;
	हाल TCP_FIN_WAIT2:
		/* Received a FIN -- send ACK and enter TIME_WAIT. */
		tcp_send_ack(sk);
		tcp_समय_रुको(sk, TCP_TIME_WAIT, 0);
		अवरोध;
	शेष:
		/* Only TCP_LISTEN and TCP_CLOSE are left, in these
		 * हालs we should never reach this piece of code.
		 */
		pr_err("%s: Impossible, sk->sk_state=%d\n",
		       __func__, sk->sk_state);
		अवरोध;
	पूर्ण

	/* It _is_ possible, that we have something out-of-order _after_ FIN.
	 * Probably, we should reset in this हाल. For now drop them.
	 */
	skb_rbtree_purge(&tp->out_of_order_queue);
	अगर (tcp_is_sack(tp))
		tcp_sack_reset(&tp->rx_opt);
	sk_mem_reclaim(sk);

	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		sk->sk_state_change(sk);

		/* Do not send POLL_HUP क्रम half duplex बंद. */
		अगर (sk->sk_shutकरोwn == SHUTDOWN_MASK ||
		    sk->sk_state == TCP_CLOSE)
			sk_wake_async(sk, SOCK_WAKE_WAITD, POLL_HUP);
		अन्यथा
			sk_wake_async(sk, SOCK_WAKE_WAITD, POLL_IN);
	पूर्ण
पूर्ण

अटल अंतरभूत bool tcp_sack_extend(काष्ठा tcp_sack_block *sp, u32 seq,
				  u32 end_seq)
अणु
	अगर (!after(seq, sp->end_seq) && !after(sp->start_seq, end_seq)) अणु
		अगर (beक्रमe(seq, sp->start_seq))
			sp->start_seq = seq;
		अगर (after(end_seq, sp->end_seq))
			sp->end_seq = end_seq;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम tcp_dsack_set(काष्ठा sock *sk, u32 seq, u32 end_seq)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (tcp_is_sack(tp) && sock_net(sk)->ipv4.sysctl_tcp_dsack) अणु
		पूर्णांक mib_idx;

		अगर (beक्रमe(seq, tp->rcv_nxt))
			mib_idx = LINUX_MIB_TCPDSACKOLDSENT;
		अन्यथा
			mib_idx = LINUX_MIB_TCPDSACKOFOSENT;

		NET_INC_STATS(sock_net(sk), mib_idx);

		tp->rx_opt.dsack = 1;
		tp->duplicate_sack[0].start_seq = seq;
		tp->duplicate_sack[0].end_seq = end_seq;
	पूर्ण
पूर्ण

अटल व्योम tcp_dsack_extend(काष्ठा sock *sk, u32 seq, u32 end_seq)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (!tp->rx_opt.dsack)
		tcp_dsack_set(sk, seq, end_seq);
	अन्यथा
		tcp_sack_extend(tp->duplicate_sack, seq, end_seq);
पूर्ण

अटल व्योम tcp_rcv_spurious_retrans(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
	/* When the ACK path fails or drops most ACKs, the sender would
	 * समयout and spuriously retransmit the same segment repeatedly.
	 * The receiver remembers and reflects via DSACKs. Leverage the
	 * DSACK state and change the txhash to re-route speculatively.
	 */
	अगर (TCP_SKB_CB(skb)->seq == tcp_sk(sk)->duplicate_sack[0].start_seq &&
	    sk_rethink_txhash(sk))
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPDUPLICATEDATAREHASH);
पूर्ण

अटल व्योम tcp_send_dupack(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (TCP_SKB_CB(skb)->end_seq != TCP_SKB_CB(skb)->seq &&
	    beक्रमe(TCP_SKB_CB(skb)->seq, tp->rcv_nxt)) अणु
		NET_INC_STATS(sock_net(sk), LINUX_MIB_DELAYEDACKLOST);
		tcp_enter_quickack_mode(sk, TCP_MAX_QUICKACKS);

		अगर (tcp_is_sack(tp) && sock_net(sk)->ipv4.sysctl_tcp_dsack) अणु
			u32 end_seq = TCP_SKB_CB(skb)->end_seq;

			tcp_rcv_spurious_retrans(sk, skb);
			अगर (after(TCP_SKB_CB(skb)->end_seq, tp->rcv_nxt))
				end_seq = tp->rcv_nxt;
			tcp_dsack_set(sk, TCP_SKB_CB(skb)->seq, end_seq);
		पूर्ण
	पूर्ण

	tcp_send_ack(sk);
पूर्ण

/* These routines update the SACK block as out-of-order packets arrive or
 * in-order packets बंद up the sequence space.
 */
अटल व्योम tcp_sack_maybe_coalesce(काष्ठा tcp_sock *tp)
अणु
	पूर्णांक this_sack;
	काष्ठा tcp_sack_block *sp = &tp->selective_acks[0];
	काष्ठा tcp_sack_block *swalk = sp + 1;

	/* See अगर the recent change to the first SACK eats पूर्णांकo
	 * or hits the sequence space of other SACK blocks, अगर so coalesce.
	 */
	क्रम (this_sack = 1; this_sack < tp->rx_opt.num_sacks;) अणु
		अगर (tcp_sack_extend(sp, swalk->start_seq, swalk->end_seq)) अणु
			पूर्णांक i;

			/* Zap SWALK, by moving every further SACK up by one slot.
			 * Decrease num_sacks.
			 */
			tp->rx_opt.num_sacks--;
			क्रम (i = this_sack; i < tp->rx_opt.num_sacks; i++)
				sp[i] = sp[i + 1];
			जारी;
		पूर्ण
		this_sack++;
		swalk++;
	पूर्ण
पूर्ण

अटल व्योम tcp_sack_compress_send_ack(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (!tp->compressed_ack)
		वापस;

	अगर (hrसमयr_try_to_cancel(&tp->compressed_ack_समयr) == 1)
		__sock_put(sk);

	/* Since we have to send one ack finally,
	 * substract one from tp->compressed_ack to keep
	 * LINUX_MIB_TCPACKCOMPRESSED accurate.
	 */
	NET_ADD_STATS(sock_net(sk), LINUX_MIB_TCPACKCOMPRESSED,
		      tp->compressed_ack - 1);

	tp->compressed_ack = 0;
	tcp_send_ack(sk);
पूर्ण

/* Reasonable amount of sack blocks included in TCP SACK option
 * The max is 4, but this becomes 3 अगर TCP बारtamps are there.
 * Given that SACK packets might be lost, be conservative and use 2.
 */
#घोषणा TCP_SACK_BLOCKS_EXPECTED 2

अटल व्योम tcp_sack_new_ofo_skb(काष्ठा sock *sk, u32 seq, u32 end_seq)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा tcp_sack_block *sp = &tp->selective_acks[0];
	पूर्णांक cur_sacks = tp->rx_opt.num_sacks;
	पूर्णांक this_sack;

	अगर (!cur_sacks)
		जाओ new_sack;

	क्रम (this_sack = 0; this_sack < cur_sacks; this_sack++, sp++) अणु
		अगर (tcp_sack_extend(sp, seq, end_seq)) अणु
			अगर (this_sack >= TCP_SACK_BLOCKS_EXPECTED)
				tcp_sack_compress_send_ack(sk);
			/* Rotate this_sack to the first one. */
			क्रम (; this_sack > 0; this_sack--, sp--)
				swap(*sp, *(sp - 1));
			अगर (cur_sacks > 1)
				tcp_sack_maybe_coalesce(tp);
			वापस;
		पूर्ण
	पूर्ण

	अगर (this_sack >= TCP_SACK_BLOCKS_EXPECTED)
		tcp_sack_compress_send_ack(sk);

	/* Could not find an adjacent existing SACK, build a new one,
	 * put it at the front, and shअगरt everyone अन्यथा करोwn.  We
	 * always know there is at least one SACK present alपढ़ोy here.
	 *
	 * If the sack array is full, क्रमget about the last one.
	 */
	अगर (this_sack >= TCP_NUM_SACKS) अणु
		this_sack--;
		tp->rx_opt.num_sacks--;
		sp--;
	पूर्ण
	क्रम (; this_sack > 0; this_sack--, sp--)
		*sp = *(sp - 1);

new_sack:
	/* Build the new head SACK, and we're करोne. */
	sp->start_seq = seq;
	sp->end_seq = end_seq;
	tp->rx_opt.num_sacks++;
पूर्ण

/* RCV.NXT advances, some SACKs should be eaten. */

अटल व्योम tcp_sack_हटाओ(काष्ठा tcp_sock *tp)
अणु
	काष्ठा tcp_sack_block *sp = &tp->selective_acks[0];
	पूर्णांक num_sacks = tp->rx_opt.num_sacks;
	पूर्णांक this_sack;

	/* Empty ofo queue, hence, all the SACKs are eaten. Clear. */
	अगर (RB_EMPTY_ROOT(&tp->out_of_order_queue)) अणु
		tp->rx_opt.num_sacks = 0;
		वापस;
	पूर्ण

	क्रम (this_sack = 0; this_sack < num_sacks;) अणु
		/* Check अगर the start of the sack is covered by RCV.NXT. */
		अगर (!beक्रमe(tp->rcv_nxt, sp->start_seq)) अणु
			पूर्णांक i;

			/* RCV.NXT must cover all the block! */
			WARN_ON(beक्रमe(tp->rcv_nxt, sp->end_seq));

			/* Zap this SACK, by moving क्रमward any other SACKS. */
			क्रम (i = this_sack+1; i < num_sacks; i++)
				tp->selective_acks[i-1] = tp->selective_acks[i];
			num_sacks--;
			जारी;
		पूर्ण
		this_sack++;
		sp++;
	पूर्ण
	tp->rx_opt.num_sacks = num_sacks;
पूर्ण

/**
 * tcp_try_coalesce - try to merge skb to prior one
 * @sk: socket
 * @to: prior buffer
 * @from: buffer to add in queue
 * @fragstolen: poपूर्णांकer to boolean
 *
 * Beक्रमe queueing skb @from after @to, try to merge them
 * to reduce overall memory use and queue lengths, अगर cost is small.
 * Packets in ofo or receive queues can stay a दीर्घ समय.
 * Better try to coalesce them right now to aव्योम future collapses.
 * Returns true अगर caller should मुक्त @from instead of queueing it
 */
अटल bool tcp_try_coalesce(काष्ठा sock *sk,
			     काष्ठा sk_buff *to,
			     काष्ठा sk_buff *from,
			     bool *fragstolen)
अणु
	पूर्णांक delta;

	*fragstolen = false;

	/* Its possible this segment overlaps with prior segment in queue */
	अगर (TCP_SKB_CB(from)->seq != TCP_SKB_CB(to)->end_seq)
		वापस false;

	अगर (!mptcp_skb_can_collapse(to, from))
		वापस false;

#अगर_घोषित CONFIG_TLS_DEVICE
	अगर (from->decrypted != to->decrypted)
		वापस false;
#पूर्ण_अगर

	अगर (!skb_try_coalesce(to, from, fragstolen, &delta))
		वापस false;

	atomic_add(delta, &sk->sk_rmem_alloc);
	sk_mem_अक्षरge(sk, delta);
	NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPRCVCOALESCE);
	TCP_SKB_CB(to)->end_seq = TCP_SKB_CB(from)->end_seq;
	TCP_SKB_CB(to)->ack_seq = TCP_SKB_CB(from)->ack_seq;
	TCP_SKB_CB(to)->tcp_flags |= TCP_SKB_CB(from)->tcp_flags;

	अगर (TCP_SKB_CB(from)->has_rxtstamp) अणु
		TCP_SKB_CB(to)->has_rxtstamp = true;
		to->tstamp = from->tstamp;
		skb_hwtstamps(to)->hwtstamp = skb_hwtstamps(from)->hwtstamp;
	पूर्ण

	वापस true;
पूर्ण

अटल bool tcp_ooo_try_coalesce(काष्ठा sock *sk,
			     काष्ठा sk_buff *to,
			     काष्ठा sk_buff *from,
			     bool *fragstolen)
अणु
	bool res = tcp_try_coalesce(sk, to, from, fragstolen);

	/* In हाल tcp_drop() is called later, update to->gso_segs */
	अगर (res) अणु
		u32 gso_segs = max_t(u16, 1, skb_shinfo(to)->gso_segs) +
			       max_t(u16, 1, skb_shinfo(from)->gso_segs);

		skb_shinfo(to)->gso_segs = min_t(u32, gso_segs, 0xFFFF);
	पूर्ण
	वापस res;
पूर्ण

अटल व्योम tcp_drop(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	sk_drops_add(sk, skb);
	__kमुक्त_skb(skb);
पूर्ण

/* This one checks to see अगर we can put data from the
 * out_of_order queue पूर्णांकo the receive_queue.
 */
अटल व्योम tcp_ofo_queue(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	__u32 dsack_high = tp->rcv_nxt;
	bool fin, fragstolen, eaten;
	काष्ठा sk_buff *skb, *tail;
	काष्ठा rb_node *p;

	p = rb_first(&tp->out_of_order_queue);
	जबतक (p) अणु
		skb = rb_to_skb(p);
		अगर (after(TCP_SKB_CB(skb)->seq, tp->rcv_nxt))
			अवरोध;

		अगर (beक्रमe(TCP_SKB_CB(skb)->seq, dsack_high)) अणु
			__u32 dsack = dsack_high;
			अगर (beक्रमe(TCP_SKB_CB(skb)->end_seq, dsack_high))
				dsack_high = TCP_SKB_CB(skb)->end_seq;
			tcp_dsack_extend(sk, TCP_SKB_CB(skb)->seq, dsack);
		पूर्ण
		p = rb_next(p);
		rb_erase(&skb->rbnode, &tp->out_of_order_queue);

		अगर (unlikely(!after(TCP_SKB_CB(skb)->end_seq, tp->rcv_nxt))) अणु
			tcp_drop(sk, skb);
			जारी;
		पूर्ण

		tail = skb_peek_tail(&sk->sk_receive_queue);
		eaten = tail && tcp_try_coalesce(sk, tail, skb, &fragstolen);
		tcp_rcv_nxt_update(tp, TCP_SKB_CB(skb)->end_seq);
		fin = TCP_SKB_CB(skb)->tcp_flags & TCPHDR_FIN;
		अगर (!eaten)
			__skb_queue_tail(&sk->sk_receive_queue, skb);
		अन्यथा
			kमुक्त_skb_partial(skb, fragstolen);

		अगर (unlikely(fin)) अणु
			tcp_fin(sk);
			/* tcp_fin() purges tp->out_of_order_queue,
			 * so we must end this loop right now.
			 */
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool tcp_prune_ofo_queue(काष्ठा sock *sk);
अटल पूर्णांक tcp_prune_queue(काष्ठा sock *sk);

अटल पूर्णांक tcp_try_rmem_schedule(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				 अचिन्हित पूर्णांक size)
अणु
	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) > sk->sk_rcvbuf ||
	    !sk_rmem_schedule(sk, skb, size)) अणु

		अगर (tcp_prune_queue(sk) < 0)
			वापस -1;

		जबतक (!sk_rmem_schedule(sk, skb, size)) अणु
			अगर (!tcp_prune_ofo_queue(sk))
				वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम tcp_data_queue_ofo(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा rb_node **p, *parent;
	काष्ठा sk_buff *skb1;
	u32 seq, end_seq;
	bool fragstolen;

	tcp_ecn_check_ce(sk, skb);

	अगर (unlikely(tcp_try_rmem_schedule(sk, skb, skb->truesize))) अणु
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPOFODROP);
		sk->sk_data_पढ़ोy(sk);
		tcp_drop(sk, skb);
		वापस;
	पूर्ण

	/* Disable header prediction. */
	tp->pred_flags = 0;
	inet_csk_schedule_ack(sk);

	tp->rcv_ooopack += max_t(u16, 1, skb_shinfo(skb)->gso_segs);
	NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPOFOQUEUE);
	seq = TCP_SKB_CB(skb)->seq;
	end_seq = TCP_SKB_CB(skb)->end_seq;

	p = &tp->out_of_order_queue.rb_node;
	अगर (RB_EMPTY_ROOT(&tp->out_of_order_queue)) अणु
		/* Initial out of order segment, build 1 SACK. */
		अगर (tcp_is_sack(tp)) अणु
			tp->rx_opt.num_sacks = 1;
			tp->selective_acks[0].start_seq = seq;
			tp->selective_acks[0].end_seq = end_seq;
		पूर्ण
		rb_link_node(&skb->rbnode, शून्य, p);
		rb_insert_color(&skb->rbnode, &tp->out_of_order_queue);
		tp->ooo_last_skb = skb;
		जाओ end;
	पूर्ण

	/* In the typical हाल, we are adding an skb to the end of the list.
	 * Use of ooo_last_skb aव्योमs the O(Log(N)) rbtree lookup.
	 */
	अगर (tcp_ooo_try_coalesce(sk, tp->ooo_last_skb,
				 skb, &fragstolen)) अणु
coalesce_करोne:
		/* For non sack flows, करो not grow winकरोw to क्रमce DUPACK
		 * and trigger fast retransmit.
		 */
		अगर (tcp_is_sack(tp))
			tcp_grow_winकरोw(sk, skb);
		kमुक्त_skb_partial(skb, fragstolen);
		skb = शून्य;
		जाओ add_sack;
	पूर्ण
	/* Can aव्योम an rbtree lookup अगर we are adding skb after ooo_last_skb */
	अगर (!beक्रमe(seq, TCP_SKB_CB(tp->ooo_last_skb)->end_seq)) अणु
		parent = &tp->ooo_last_skb->rbnode;
		p = &parent->rb_right;
		जाओ insert;
	पूर्ण

	/* Find place to insert this segment. Handle overlaps on the way. */
	parent = शून्य;
	जबतक (*p) अणु
		parent = *p;
		skb1 = rb_to_skb(parent);
		अगर (beक्रमe(seq, TCP_SKB_CB(skb1)->seq)) अणु
			p = &parent->rb_left;
			जारी;
		पूर्ण
		अगर (beक्रमe(seq, TCP_SKB_CB(skb1)->end_seq)) अणु
			अगर (!after(end_seq, TCP_SKB_CB(skb1)->end_seq)) अणु
				/* All the bits are present. Drop. */
				NET_INC_STATS(sock_net(sk),
					      LINUX_MIB_TCPOFOMERGE);
				tcp_drop(sk, skb);
				skb = शून्य;
				tcp_dsack_set(sk, seq, end_seq);
				जाओ add_sack;
			पूर्ण
			अगर (after(seq, TCP_SKB_CB(skb1)->seq)) अणु
				/* Partial overlap. */
				tcp_dsack_set(sk, seq, TCP_SKB_CB(skb1)->end_seq);
			पूर्ण अन्यथा अणु
				/* skb's seq == skb1's seq and skb covers skb1.
				 * Replace skb1 with skb.
				 */
				rb_replace_node(&skb1->rbnode, &skb->rbnode,
						&tp->out_of_order_queue);
				tcp_dsack_extend(sk,
						 TCP_SKB_CB(skb1)->seq,
						 TCP_SKB_CB(skb1)->end_seq);
				NET_INC_STATS(sock_net(sk),
					      LINUX_MIB_TCPOFOMERGE);
				tcp_drop(sk, skb1);
				जाओ merge_right;
			पूर्ण
		पूर्ण अन्यथा अगर (tcp_ooo_try_coalesce(sk, skb1,
						skb, &fragstolen)) अणु
			जाओ coalesce_करोne;
		पूर्ण
		p = &parent->rb_right;
	पूर्ण
insert:
	/* Insert segment पूर्णांकo RB tree. */
	rb_link_node(&skb->rbnode, parent, p);
	rb_insert_color(&skb->rbnode, &tp->out_of_order_queue);

merge_right:
	/* Remove other segments covered by skb. */
	जबतक ((skb1 = skb_rb_next(skb)) != शून्य) अणु
		अगर (!after(end_seq, TCP_SKB_CB(skb1)->seq))
			अवरोध;
		अगर (beक्रमe(end_seq, TCP_SKB_CB(skb1)->end_seq)) अणु
			tcp_dsack_extend(sk, TCP_SKB_CB(skb1)->seq,
					 end_seq);
			अवरोध;
		पूर्ण
		rb_erase(&skb1->rbnode, &tp->out_of_order_queue);
		tcp_dsack_extend(sk, TCP_SKB_CB(skb1)->seq,
				 TCP_SKB_CB(skb1)->end_seq);
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPOFOMERGE);
		tcp_drop(sk, skb1);
	पूर्ण
	/* If there is no skb after us, we are the last_skb ! */
	अगर (!skb1)
		tp->ooo_last_skb = skb;

add_sack:
	अगर (tcp_is_sack(tp))
		tcp_sack_new_ofo_skb(sk, seq, end_seq);
end:
	अगर (skb) अणु
		/* For non sack flows, करो not grow winकरोw to क्रमce DUPACK
		 * and trigger fast retransmit.
		 */
		अगर (tcp_is_sack(tp))
			tcp_grow_winकरोw(sk, skb);
		skb_condense(skb);
		skb_set_owner_r(skb, sk);
	पूर्ण
पूर्ण

अटल पूर्णांक __must_check tcp_queue_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				      bool *fragstolen)
अणु
	पूर्णांक eaten;
	काष्ठा sk_buff *tail = skb_peek_tail(&sk->sk_receive_queue);

	eaten = (tail &&
		 tcp_try_coalesce(sk, tail,
				  skb, fragstolen)) ? 1 : 0;
	tcp_rcv_nxt_update(tcp_sk(sk), TCP_SKB_CB(skb)->end_seq);
	अगर (!eaten) अणु
		__skb_queue_tail(&sk->sk_receive_queue, skb);
		skb_set_owner_r(skb, sk);
	पूर्ण
	वापस eaten;
पूर्ण

पूर्णांक tcp_send_rcvq(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार size)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOMEM;
	पूर्णांक data_len = 0;
	bool fragstolen;

	अगर (size == 0)
		वापस 0;

	अगर (size > PAGE_SIZE) अणु
		पूर्णांक npages = min_t(माप_प्रकार, size >> PAGE_SHIFT, MAX_SKB_FRAGS);

		data_len = npages << PAGE_SHIFT;
		size = data_len + (size & ~PAGE_MASK);
	पूर्ण
	skb = alloc_skb_with_frags(size - data_len, data_len,
				   PAGE_ALLOC_COSTLY_ORDER,
				   &err, sk->sk_allocation);
	अगर (!skb)
		जाओ err;

	skb_put(skb, size - data_len);
	skb->data_len = data_len;
	skb->len = size;

	अगर (tcp_try_rmem_schedule(sk, skb, skb->truesize)) अणु
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPRCVQDROP);
		जाओ err_मुक्त;
	पूर्ण

	err = skb_copy_datagram_from_iter(skb, 0, &msg->msg_iter, size);
	अगर (err)
		जाओ err_मुक्त;

	TCP_SKB_CB(skb)->seq = tcp_sk(sk)->rcv_nxt;
	TCP_SKB_CB(skb)->end_seq = TCP_SKB_CB(skb)->seq + size;
	TCP_SKB_CB(skb)->ack_seq = tcp_sk(sk)->snd_una - 1;

	अगर (tcp_queue_rcv(sk, skb, &fragstolen)) अणु
		WARN_ON_ONCE(fragstolen); /* should not happen */
		__kमुक्त_skb(skb);
	पूर्ण
	वापस size;

err_मुक्त:
	kमुक्त_skb(skb);
err:
	वापस err;

पूर्ण

व्योम tcp_data_पढ़ोy(काष्ठा sock *sk)
अणु
	अगर (tcp_epollin_पढ़ोy(sk, sk->sk_rcvlowat) || sock_flag(sk, SOCK_DONE))
		sk->sk_data_पढ़ोy(sk);
पूर्ण

अटल व्योम tcp_data_queue(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	bool fragstolen;
	पूर्णांक eaten;

	अगर (sk_is_mptcp(sk))
		mptcp_incoming_options(sk, skb);

	अगर (TCP_SKB_CB(skb)->seq == TCP_SKB_CB(skb)->end_seq) अणु
		__kमुक्त_skb(skb);
		वापस;
	पूर्ण
	skb_dst_drop(skb);
	__skb_pull(skb, tcp_hdr(skb)->करोff * 4);

	tp->rx_opt.dsack = 0;

	/*  Queue data क्रम delivery to the user.
	 *  Packets in sequence go to the receive queue.
	 *  Out of sequence packets to the out_of_order_queue.
	 */
	अगर (TCP_SKB_CB(skb)->seq == tp->rcv_nxt) अणु
		अगर (tcp_receive_winकरोw(tp) == 0) अणु
			NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPZEROWINDOWDROP);
			जाओ out_of_winकरोw;
		पूर्ण

		/* Ok. In sequence. In winकरोw. */
queue_and_out:
		अगर (skb_queue_len(&sk->sk_receive_queue) == 0)
			sk_क्रमced_mem_schedule(sk, skb->truesize);
		अन्यथा अगर (tcp_try_rmem_schedule(sk, skb, skb->truesize)) अणु
			NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPRCVQDROP);
			sk->sk_data_पढ़ोy(sk);
			जाओ drop;
		पूर्ण

		eaten = tcp_queue_rcv(sk, skb, &fragstolen);
		अगर (skb->len)
			tcp_event_data_recv(sk, skb);
		अगर (TCP_SKB_CB(skb)->tcp_flags & TCPHDR_FIN)
			tcp_fin(sk);

		अगर (!RB_EMPTY_ROOT(&tp->out_of_order_queue)) अणु
			tcp_ofo_queue(sk);

			/* RFC5681. 4.2. SHOULD send immediate ACK, when
			 * gap in queue is filled.
			 */
			अगर (RB_EMPTY_ROOT(&tp->out_of_order_queue))
				inet_csk(sk)->icsk_ack.pending |= ICSK_ACK_NOW;
		पूर्ण

		अगर (tp->rx_opt.num_sacks)
			tcp_sack_हटाओ(tp);

		tcp_fast_path_check(sk);

		अगर (eaten > 0)
			kमुक्त_skb_partial(skb, fragstolen);
		अगर (!sock_flag(sk, SOCK_DEAD))
			tcp_data_पढ़ोy(sk);
		वापस;
	पूर्ण

	अगर (!after(TCP_SKB_CB(skb)->end_seq, tp->rcv_nxt)) अणु
		tcp_rcv_spurious_retrans(sk, skb);
		/* A retransmit, 2nd most common हाल.  Force an immediate ack. */
		NET_INC_STATS(sock_net(sk), LINUX_MIB_DELAYEDACKLOST);
		tcp_dsack_set(sk, TCP_SKB_CB(skb)->seq, TCP_SKB_CB(skb)->end_seq);

out_of_winकरोw:
		tcp_enter_quickack_mode(sk, TCP_MAX_QUICKACKS);
		inet_csk_schedule_ack(sk);
drop:
		tcp_drop(sk, skb);
		वापस;
	पूर्ण

	/* Out of winकरोw. F.e. zero winकरोw probe. */
	अगर (!beक्रमe(TCP_SKB_CB(skb)->seq, tp->rcv_nxt + tcp_receive_winकरोw(tp)))
		जाओ out_of_winकरोw;

	अगर (beक्रमe(TCP_SKB_CB(skb)->seq, tp->rcv_nxt)) अणु
		/* Partial packet, seq < rcv_next < end_seq */
		tcp_dsack_set(sk, TCP_SKB_CB(skb)->seq, tp->rcv_nxt);

		/* If winकरोw is बंदd, drop tail of packet. But after
		 * remembering D-SACK क्रम its head made in previous line.
		 */
		अगर (!tcp_receive_winकरोw(tp)) अणु
			NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPZEROWINDOWDROP);
			जाओ out_of_winकरोw;
		पूर्ण
		जाओ queue_and_out;
	पूर्ण

	tcp_data_queue_ofo(sk, skb);
पूर्ण

अटल काष्ठा sk_buff *tcp_skb_next(काष्ठा sk_buff *skb, काष्ठा sk_buff_head *list)
अणु
	अगर (list)
		वापस !skb_queue_is_last(list, skb) ? skb->next : शून्य;

	वापस skb_rb_next(skb);
पूर्ण

अटल काष्ठा sk_buff *tcp_collapse_one(काष्ठा sock *sk, काष्ठा sk_buff *skb,
					काष्ठा sk_buff_head *list,
					काष्ठा rb_root *root)
अणु
	काष्ठा sk_buff *next = tcp_skb_next(skb, list);

	अगर (list)
		__skb_unlink(skb, list);
	अन्यथा
		rb_erase(&skb->rbnode, root);

	__kमुक्त_skb(skb);
	NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPRCVCOLLAPSED);

	वापस next;
पूर्ण

/* Insert skb पूर्णांकo rb tree, ordered by TCP_SKB_CB(skb)->seq */
व्योम tcp_rbtree_insert(काष्ठा rb_root *root, काष्ठा sk_buff *skb)
अणु
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा sk_buff *skb1;

	जबतक (*p) अणु
		parent = *p;
		skb1 = rb_to_skb(parent);
		अगर (beक्रमe(TCP_SKB_CB(skb)->seq, TCP_SKB_CB(skb1)->seq))
			p = &parent->rb_left;
		अन्यथा
			p = &parent->rb_right;
	पूर्ण
	rb_link_node(&skb->rbnode, parent, p);
	rb_insert_color(&skb->rbnode, root);
पूर्ण

/* Collapse contiguous sequence of skbs head..tail with
 * sequence numbers start..end.
 *
 * If tail is शून्य, this means until the end of the queue.
 *
 * Segments with FIN/SYN are not collapsed (only because this
 * simplअगरies code)
 */
अटल व्योम
tcp_collapse(काष्ठा sock *sk, काष्ठा sk_buff_head *list, काष्ठा rb_root *root,
	     काष्ठा sk_buff *head, काष्ठा sk_buff *tail, u32 start, u32 end)
अणु
	काष्ठा sk_buff *skb = head, *n;
	काष्ठा sk_buff_head पंचांगp;
	bool end_of_skbs;

	/* First, check that queue is collapsible and find
	 * the poपूर्णांक where collapsing can be useful.
	 */
restart:
	क्रम (end_of_skbs = true; skb != शून्य && skb != tail; skb = n) अणु
		n = tcp_skb_next(skb, list);

		/* No new bits? It is possible on ofo queue. */
		अगर (!beक्रमe(start, TCP_SKB_CB(skb)->end_seq)) अणु
			skb = tcp_collapse_one(sk, skb, list, root);
			अगर (!skb)
				अवरोध;
			जाओ restart;
		पूर्ण

		/* The first skb to collapse is:
		 * - not SYN/FIN and
		 * - bloated or contains data beक्रमe "start" or
		 *   overlaps to the next one and mptcp allow collapsing.
		 */
		अगर (!(TCP_SKB_CB(skb)->tcp_flags & (TCPHDR_SYN | TCPHDR_FIN)) &&
		    (tcp_win_from_space(sk, skb->truesize) > skb->len ||
		     beक्रमe(TCP_SKB_CB(skb)->seq, start))) अणु
			end_of_skbs = false;
			अवरोध;
		पूर्ण

		अगर (n && n != tail && mptcp_skb_can_collapse(skb, n) &&
		    TCP_SKB_CB(skb)->end_seq != TCP_SKB_CB(n)->seq) अणु
			end_of_skbs = false;
			अवरोध;
		पूर्ण

		/* Decided to skip this, advance start seq. */
		start = TCP_SKB_CB(skb)->end_seq;
	पूर्ण
	अगर (end_of_skbs ||
	    (TCP_SKB_CB(skb)->tcp_flags & (TCPHDR_SYN | TCPHDR_FIN)))
		वापस;

	__skb_queue_head_init(&पंचांगp);

	जबतक (beक्रमe(start, end)) अणु
		पूर्णांक copy = min_t(पूर्णांक, SKB_MAX_ORDER(0, 0), end - start);
		काष्ठा sk_buff *nskb;

		nskb = alloc_skb(copy, GFP_ATOMIC);
		अगर (!nskb)
			अवरोध;

		स_नकल(nskb->cb, skb->cb, माप(skb->cb));
#अगर_घोषित CONFIG_TLS_DEVICE
		nskb->decrypted = skb->decrypted;
#पूर्ण_अगर
		TCP_SKB_CB(nskb)->seq = TCP_SKB_CB(nskb)->end_seq = start;
		अगर (list)
			__skb_queue_beक्रमe(list, skb, nskb);
		अन्यथा
			__skb_queue_tail(&पंचांगp, nskb); /* defer rbtree insertion */
		skb_set_owner_r(nskb, sk);
		mptcp_skb_ext_move(nskb, skb);

		/* Copy data, releasing collapsed skbs. */
		जबतक (copy > 0) अणु
			पूर्णांक offset = start - TCP_SKB_CB(skb)->seq;
			पूर्णांक size = TCP_SKB_CB(skb)->end_seq - start;

			BUG_ON(offset < 0);
			अगर (size > 0) अणु
				size = min(copy, size);
				अगर (skb_copy_bits(skb, offset, skb_put(nskb, size), size))
					BUG();
				TCP_SKB_CB(nskb)->end_seq += size;
				copy -= size;
				start += size;
			पूर्ण
			अगर (!beक्रमe(start, TCP_SKB_CB(skb)->end_seq)) अणु
				skb = tcp_collapse_one(sk, skb, list, root);
				अगर (!skb ||
				    skb == tail ||
				    !mptcp_skb_can_collapse(nskb, skb) ||
				    (TCP_SKB_CB(skb)->tcp_flags & (TCPHDR_SYN | TCPHDR_FIN)))
					जाओ end;
#अगर_घोषित CONFIG_TLS_DEVICE
				अगर (skb->decrypted != nskb->decrypted)
					जाओ end;
#पूर्ण_अगर
			पूर्ण
		पूर्ण
	पूर्ण
end:
	skb_queue_walk_safe(&पंचांगp, skb, n)
		tcp_rbtree_insert(root, skb);
पूर्ण

/* Collapse ofo queue. Algorithm: select contiguous sequence of skbs
 * and tcp_collapse() them until all the queue is collapsed.
 */
अटल व्योम tcp_collapse_ofo_queue(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 range_truesize, sum_tiny = 0;
	काष्ठा sk_buff *skb, *head;
	u32 start, end;

	skb = skb_rb_first(&tp->out_of_order_queue);
new_range:
	अगर (!skb) अणु
		tp->ooo_last_skb = skb_rb_last(&tp->out_of_order_queue);
		वापस;
	पूर्ण
	start = TCP_SKB_CB(skb)->seq;
	end = TCP_SKB_CB(skb)->end_seq;
	range_truesize = skb->truesize;

	क्रम (head = skb;;) अणु
		skb = skb_rb_next(skb);

		/* Range is terminated when we see a gap or when
		 * we are at the queue end.
		 */
		अगर (!skb ||
		    after(TCP_SKB_CB(skb)->seq, end) ||
		    beक्रमe(TCP_SKB_CB(skb)->end_seq, start)) अणु
			/* Do not attempt collapsing tiny skbs */
			अगर (range_truesize != head->truesize ||
			    end - start >= SKB_WITH_OVERHEAD(SK_MEM_QUANTUM)) अणु
				tcp_collapse(sk, शून्य, &tp->out_of_order_queue,
					     head, skb, start, end);
			पूर्ण अन्यथा अणु
				sum_tiny += range_truesize;
				अगर (sum_tiny > sk->sk_rcvbuf >> 3)
					वापस;
			पूर्ण
			जाओ new_range;
		पूर्ण

		range_truesize += skb->truesize;
		अगर (unlikely(beक्रमe(TCP_SKB_CB(skb)->seq, start)))
			start = TCP_SKB_CB(skb)->seq;
		अगर (after(TCP_SKB_CB(skb)->end_seq, end))
			end = TCP_SKB_CB(skb)->end_seq;
	पूर्ण
पूर्ण

/*
 * Clean the out-of-order queue to make room.
 * We drop high sequences packets to :
 * 1) Let a chance क्रम holes to be filled.
 * 2) not add too big latencies अगर thousands of packets sit there.
 *    (But अगर application shrinks SO_RCVBUF, we could still end up
 *     मुक्तing whole queue here)
 * 3) Drop at least 12.5 % of sk_rcvbuf to aव्योम malicious attacks.
 *
 * Return true अगर queue has shrunk.
 */
अटल bool tcp_prune_ofo_queue(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा rb_node *node, *prev;
	पूर्णांक goal;

	अगर (RB_EMPTY_ROOT(&tp->out_of_order_queue))
		वापस false;

	NET_INC_STATS(sock_net(sk), LINUX_MIB_OFOPRUNED);
	goal = sk->sk_rcvbuf >> 3;
	node = &tp->ooo_last_skb->rbnode;
	करो अणु
		prev = rb_prev(node);
		rb_erase(node, &tp->out_of_order_queue);
		goal -= rb_to_skb(node)->truesize;
		tcp_drop(sk, rb_to_skb(node));
		अगर (!prev || goal <= 0) अणु
			sk_mem_reclaim(sk);
			अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) <= sk->sk_rcvbuf &&
			    !tcp_under_memory_pressure(sk))
				अवरोध;
			goal = sk->sk_rcvbuf >> 3;
		पूर्ण
		node = prev;
	पूर्ण जबतक (node);
	tp->ooo_last_skb = rb_to_skb(prev);

	/* Reset SACK state.  A conक्रमming SACK implementation will
	 * करो the same at a समयout based retransmit.  When a connection
	 * is in a sad state like this, we care only about पूर्णांकegrity
	 * of the connection not perक्रमmance.
	 */
	अगर (tp->rx_opt.sack_ok)
		tcp_sack_reset(&tp->rx_opt);
	वापस true;
पूर्ण

/* Reduce allocated memory अगर we can, trying to get
 * the socket within its memory limits again.
 *
 * Return less than zero अगर we should start dropping frames
 * until the socket owning process पढ़ोs some of the data
 * to stabilize the situation.
 */
अटल पूर्णांक tcp_prune_queue(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	NET_INC_STATS(sock_net(sk), LINUX_MIB_PRUNECALLED);

	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) >= sk->sk_rcvbuf)
		tcp_clamp_winकरोw(sk);
	अन्यथा अगर (tcp_under_memory_pressure(sk))
		tp->rcv_ssthresh = min(tp->rcv_ssthresh, 4U * tp->advmss);

	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) <= sk->sk_rcvbuf)
		वापस 0;

	tcp_collapse_ofo_queue(sk);
	अगर (!skb_queue_empty(&sk->sk_receive_queue))
		tcp_collapse(sk, &sk->sk_receive_queue, शून्य,
			     skb_peek(&sk->sk_receive_queue),
			     शून्य,
			     tp->copied_seq, tp->rcv_nxt);
	sk_mem_reclaim(sk);

	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) <= sk->sk_rcvbuf)
		वापस 0;

	/* Collapsing did not help, deकाष्ठाive actions follow.
	 * This must not ever occur. */

	tcp_prune_ofo_queue(sk);

	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) <= sk->sk_rcvbuf)
		वापस 0;

	/* If we are really being abused, tell the caller to silently
	 * drop receive data on the न्यूनमान.  It will get retransmitted
	 * and hopefully then we'll have sufficient space.
	 */
	NET_INC_STATS(sock_net(sk), LINUX_MIB_RCVPRUNED);

	/* Massive buffer overcommit. */
	tp->pred_flags = 0;
	वापस -1;
पूर्ण

अटल bool tcp_should_expand_sndbuf(स्थिर काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);

	/* If the user specअगरied a specअगरic send buffer setting, करो
	 * not modअगरy it.
	 */
	अगर (sk->sk_userlocks & SOCK_SNDBUF_LOCK)
		वापस false;

	/* If we are under global TCP memory pressure, करो not expand.  */
	अगर (tcp_under_memory_pressure(sk))
		वापस false;

	/* If we are under soft global TCP memory pressure, करो not expand.  */
	अगर (sk_memory_allocated(sk) >= sk_prot_mem_limits(sk, 0))
		वापस false;

	/* If we filled the congestion winकरोw, करो not expand.  */
	अगर (tcp_packets_in_flight(tp) >= tp->snd_cwnd)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम tcp_new_space(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (tcp_should_expand_sndbuf(sk)) अणु
		tcp_sndbuf_expand(sk);
		tp->snd_cwnd_stamp = tcp_jअगरfies32;
	पूर्ण

	sk->sk_ग_लिखो_space(sk);
पूर्ण

अटल व्योम tcp_check_space(काष्ठा sock *sk)
अणु
	/* pairs with tcp_poll() */
	smp_mb();
	अगर (sk->sk_socket &&
	    test_bit(SOCK_NOSPACE, &sk->sk_socket->flags)) अणु
		tcp_new_space(sk);
		अगर (!test_bit(SOCK_NOSPACE, &sk->sk_socket->flags))
			tcp_chrono_stop(sk, TCP_CHRONO_SNDBUF_LIMITED);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम tcp_data_snd_check(काष्ठा sock *sk)
अणु
	tcp_push_pending_frames(sk);
	tcp_check_space(sk);
पूर्ण

/*
 * Check अगर sending an ack is needed.
 */
अटल व्योम __tcp_ack_snd_check(काष्ठा sock *sk, पूर्णांक ofo_possible)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	अचिन्हित दीर्घ rtt, delay;

	    /* More than one full frame received... */
	अगर (((tp->rcv_nxt - tp->rcv_wup) > inet_csk(sk)->icsk_ack.rcv_mss &&
	     /* ... and right edge of winकरोw advances far enough.
	      * (tcp_recvmsg() will send ACK otherwise).
	      * If application uses SO_RCVLOWAT, we want send ack now अगर
	      * we have not received enough bytes to satisfy the condition.
	      */
	    (tp->rcv_nxt - tp->copied_seq < sk->sk_rcvlowat ||
	     __tcp_select_winकरोw(sk) >= tp->rcv_wnd)) ||
	    /* We ACK each frame or... */
	    tcp_in_quickack_mode(sk) ||
	    /* Protocol state mandates a one-समय immediate ACK */
	    inet_csk(sk)->icsk_ack.pending & ICSK_ACK_NOW) अणु
send_now:
		tcp_send_ack(sk);
		वापस;
	पूर्ण

	अगर (!ofo_possible || RB_EMPTY_ROOT(&tp->out_of_order_queue)) अणु
		tcp_send_delayed_ack(sk);
		वापस;
	पूर्ण

	अगर (!tcp_is_sack(tp) ||
	    tp->compressed_ack >= sock_net(sk)->ipv4.sysctl_tcp_comp_sack_nr)
		जाओ send_now;

	अगर (tp->compressed_ack_rcv_nxt != tp->rcv_nxt) अणु
		tp->compressed_ack_rcv_nxt = tp->rcv_nxt;
		tp->dup_ack_counter = 0;
	पूर्ण
	अगर (tp->dup_ack_counter < TCP_FASTRETRANS_THRESH) अणु
		tp->dup_ack_counter++;
		जाओ send_now;
	पूर्ण
	tp->compressed_ack++;
	अगर (hrसमयr_is_queued(&tp->compressed_ack_समयr))
		वापस;

	/* compress ack समयr : 5 % of rtt, but no more than tcp_comp_sack_delay_ns */

	rtt = tp->rcv_rtt_est.rtt_us;
	अगर (tp->srtt_us && tp->srtt_us < rtt)
		rtt = tp->srtt_us;

	delay = min_t(अचिन्हित दीर्घ, sock_net(sk)->ipv4.sysctl_tcp_comp_sack_delay_ns,
		      rtt * (NSEC_PER_USEC >> 3)/20);
	sock_hold(sk);
	hrसमयr_start_range_ns(&tp->compressed_ack_समयr, ns_to_kसमय(delay),
			       sock_net(sk)->ipv4.sysctl_tcp_comp_sack_slack_ns,
			       HRTIMER_MODE_REL_PINNED_SOFT);
पूर्ण

अटल अंतरभूत व्योम tcp_ack_snd_check(काष्ठा sock *sk)
अणु
	अगर (!inet_csk_ack_scheduled(sk)) अणु
		/* We sent a data segment alपढ़ोy. */
		वापस;
	पूर्ण
	__tcp_ack_snd_check(sk, 1);
पूर्ण

/*
 *	This routine is only called when we have urgent data
 *	संकेतed. Its the 'slow' part of tcp_urg. It could be
 *	moved अंतरभूत now as tcp_urg is only called from one
 *	place. We handle URGent data wrong. We have to - as
 *	BSD still करोesn't use the correction from RFC961.
 *	For 1003.1g we should support a new option TCP_STDURG to permit
 *	either क्रमm (or just set the sysctl tcp_stdurg).
 */

अटल व्योम tcp_check_urg(काष्ठा sock *sk, स्थिर काष्ठा tcphdr *th)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 ptr = ntohs(th->urg_ptr);

	अगर (ptr && !sock_net(sk)->ipv4.sysctl_tcp_stdurg)
		ptr--;
	ptr += ntohl(th->seq);

	/* Ignore urgent data that we've alपढ़ोy seen and पढ़ो. */
	अगर (after(tp->copied_seq, ptr))
		वापस;

	/* Do not replay urg ptr.
	 *
	 * NOTE: पूर्णांकeresting situation not covered by specs.
	 * Misbehaving sender may send urg ptr, poपूर्णांकing to segment,
	 * which we alपढ़ोy have in ofo queue. We are not able to fetch
	 * such data and will stay in TCP_URG_NOTYET until will be eaten
	 * by recvmsg(). Seems, we are not obliged to handle such wicked
	 * situations. But it is worth to think about possibility of some
	 * DoSes using some hypothetical application level deadlock.
	 */
	अगर (beक्रमe(ptr, tp->rcv_nxt))
		वापस;

	/* Do we alपढ़ोy have a newer (or duplicate) urgent poपूर्णांकer? */
	अगर (tp->urg_data && !after(ptr, tp->urg_seq))
		वापस;

	/* Tell the world about our new urgent poपूर्णांकer. */
	sk_send_sigurg(sk);

	/* We may be adding urgent data when the last byte पढ़ो was
	 * urgent. To करो this requires some care. We cannot just ignore
	 * tp->copied_seq since we would पढ़ो the last urgent byte again
	 * as data, nor can we alter copied_seq until this data arrives
	 * or we अवरोध the semantics of SIOCATMARK (and thus sockaपंचांगark())
	 *
	 * NOTE. Double Dutch. Rendering to plain English: author of comment
	 * above did something sort of 	send("A", MSG_OOB); send("B", MSG_OOB);
	 * and expect that both A and B disappear from stream. This is _wrong_.
	 * Though this happens in BSD with high probability, this is occasional.
	 * Any application relying on this is buggy. Note also, that fix "works"
	 * only in this artअगरicial test. Insert some normal data between A and B and we will
	 * decline of BSD again. Verdict: it is better to हटाओ to trap
	 * buggy users.
	 */
	अगर (tp->urg_seq == tp->copied_seq && tp->urg_data &&
	    !sock_flag(sk, SOCK_URGINLINE) && tp->copied_seq != tp->rcv_nxt) अणु
		काष्ठा sk_buff *skb = skb_peek(&sk->sk_receive_queue);
		tp->copied_seq++;
		अगर (skb && !beक्रमe(tp->copied_seq, TCP_SKB_CB(skb)->end_seq)) अणु
			__skb_unlink(skb, &sk->sk_receive_queue);
			__kमुक्त_skb(skb);
		पूर्ण
	पूर्ण

	tp->urg_data = TCP_URG_NOTYET;
	WRITE_ONCE(tp->urg_seq, ptr);

	/* Disable header prediction. */
	tp->pred_flags = 0;
पूर्ण

/* This is the 'fast' part of urgent handling. */
अटल व्योम tcp_urg(काष्ठा sock *sk, काष्ठा sk_buff *skb, स्थिर काष्ठा tcphdr *th)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	/* Check अगर we get a new urgent poपूर्णांकer - normally not. */
	अगर (th->urg)
		tcp_check_urg(sk, th);

	/* Do we रुको क्रम any urgent data? - normally not... */
	अगर (tp->urg_data == TCP_URG_NOTYET) अणु
		u32 ptr = tp->urg_seq - ntohl(th->seq) + (th->करोff * 4) -
			  th->syn;

		/* Is the urgent poपूर्णांकer poपूर्णांकing पूर्णांकo this packet? */
		अगर (ptr < skb->len) अणु
			u8 पंचांगp;
			अगर (skb_copy_bits(skb, ptr, &पंचांगp, 1))
				BUG();
			tp->urg_data = TCP_URG_VALID | पंचांगp;
			अगर (!sock_flag(sk, SOCK_DEAD))
				sk->sk_data_पढ़ोy(sk);
		पूर्ण
	पूर्ण
पूर्ण

/* Accept RST क्रम rcv_nxt - 1 after a FIN.
 * When tcp connections are abruptly terminated from Mac OSX (via ^C), a
 * FIN is sent followed by a RST packet. The RST is sent with the same
 * sequence number as the FIN, and thus according to RFC 5961 a challenge
 * ACK should be sent. However, Mac OSX rate limits replies to challenge
 * ACKs on the बंदd socket. In addition middleboxes can drop either the
 * challenge ACK or a subsequent RST.
 */
अटल bool tcp_reset_check(स्थिर काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	वापस unlikely(TCP_SKB_CB(skb)->seq == (tp->rcv_nxt - 1) &&
			(1 << sk->sk_state) & (TCPF_CLOSE_WAIT | TCPF_LAST_ACK |
					       TCPF_CLOSING));
पूर्ण

/* Does PAWS and seqno based validation of an incoming segment, flags will
 * play signअगरicant role here.
 */
अटल bool tcp_validate_incoming(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				  स्थिर काष्ठा tcphdr *th, पूर्णांक syn_inerr)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	bool rst_seq_match = false;

	/* RFC1323: H1. Apply PAWS check first. */
	अगर (tcp_fast_parse_options(sock_net(sk), skb, th, tp) &&
	    tp->rx_opt.saw_tstamp &&
	    tcp_paws_discard(sk, skb)) अणु
		अगर (!th->rst) अणु
			NET_INC_STATS(sock_net(sk), LINUX_MIB_PAWSESTABREJECTED);
			अगर (!tcp_oow_rate_limited(sock_net(sk), skb,
						  LINUX_MIB_TCPACKSKIPPEDPAWS,
						  &tp->last_oow_ack_समय))
				tcp_send_dupack(sk, skb);
			जाओ discard;
		पूर्ण
		/* Reset is accepted even अगर it did not pass PAWS. */
	पूर्ण

	/* Step 1: check sequence number */
	अगर (!tcp_sequence(tp, TCP_SKB_CB(skb)->seq, TCP_SKB_CB(skb)->end_seq)) अणु
		/* RFC793, page 37: "In all states except SYN-SENT, all reset
		 * (RST) segments are validated by checking their SEQ-fields."
		 * And page 69: "If an incoming segment is not acceptable,
		 * an acknowledgment should be sent in reply (unless the RST
		 * bit is set, अगर so drop the segment and वापस)".
		 */
		अगर (!th->rst) अणु
			अगर (th->syn)
				जाओ syn_challenge;
			अगर (!tcp_oow_rate_limited(sock_net(sk), skb,
						  LINUX_MIB_TCPACKSKIPPEDSEQ,
						  &tp->last_oow_ack_समय))
				tcp_send_dupack(sk, skb);
		पूर्ण अन्यथा अगर (tcp_reset_check(sk, skb)) अणु
			tcp_reset(sk, skb);
		पूर्ण
		जाओ discard;
	पूर्ण

	/* Step 2: check RST bit */
	अगर (th->rst) अणु
		/* RFC 5961 3.2 (extend to match against (RCV.NXT - 1) after a
		 * FIN and SACK too अगर available):
		 * If seq num matches RCV.NXT or (RCV.NXT - 1) after a FIN, or
		 * the right-most SACK block,
		 * then
		 *     RESET the connection
		 * अन्यथा
		 *     Send a challenge ACK
		 */
		अगर (TCP_SKB_CB(skb)->seq == tp->rcv_nxt ||
		    tcp_reset_check(sk, skb)) अणु
			rst_seq_match = true;
		पूर्ण अन्यथा अगर (tcp_is_sack(tp) && tp->rx_opt.num_sacks > 0) अणु
			काष्ठा tcp_sack_block *sp = &tp->selective_acks[0];
			पूर्णांक max_sack = sp[0].end_seq;
			पूर्णांक this_sack;

			क्रम (this_sack = 1; this_sack < tp->rx_opt.num_sacks;
			     ++this_sack) अणु
				max_sack = after(sp[this_sack].end_seq,
						 max_sack) ?
					sp[this_sack].end_seq : max_sack;
			पूर्ण

			अगर (TCP_SKB_CB(skb)->seq == max_sack)
				rst_seq_match = true;
		पूर्ण

		अगर (rst_seq_match)
			tcp_reset(sk, skb);
		अन्यथा अणु
			/* Disable TFO अगर RST is out-of-order
			 * and no data has been received
			 * क्रम current active TFO socket
			 */
			अगर (tp->syn_fastखोलो && !tp->data_segs_in &&
			    sk->sk_state == TCP_ESTABLISHED)
				tcp_fastखोलो_active_disable(sk);
			tcp_send_challenge_ack(sk, skb);
		पूर्ण
		जाओ discard;
	पूर्ण

	/* step 3: check security and precedence [ignored] */

	/* step 4: Check क्रम a SYN
	 * RFC 5961 4.2 : Send a challenge ack
	 */
	अगर (th->syn) अणु
syn_challenge:
		अगर (syn_inerr)
			TCP_INC_STATS(sock_net(sk), TCP_MIB_INERRS);
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPSYNCHALLENGE);
		tcp_send_challenge_ack(sk, skb);
		जाओ discard;
	पूर्ण

	bpf_skops_parse_hdr(sk, skb);

	वापस true;

discard:
	tcp_drop(sk, skb);
	वापस false;
पूर्ण

/*
 *	TCP receive function क्रम the ESTABLISHED state.
 *
 *	It is split पूर्णांकo a fast path and a slow path. The fast path is
 * 	disabled when:
 *	- A zero winकरोw was announced from us - zero winकरोw probing
 *        is only handled properly in the slow path.
 *	- Out of order segments arrived.
 *	- Urgent data is expected.
 *	- There is no buffer space left
 *	- Unexpected TCP flags/winकरोw values/header lengths are received
 *	  (detected by checking the TCP header against pred_flags)
 *	- Data is sent in both directions. Fast path only supports pure senders
 *	  or pure receivers (this means either the sequence number or the ack
 *	  value must stay स्थिरant)
 *	- Unexpected TCP option.
 *
 *	When these conditions are not satisfied it drops पूर्णांकo a standard
 *	receive procedure patterned after RFC793 to handle all हालs.
 *	The first three हालs are guaranteed by proper pred_flags setting,
 *	the rest is checked अंतरभूत. Fast processing is turned on in
 *	tcp_data_queue when everything is OK.
 */
व्योम tcp_rcv_established(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा tcphdr *th = (स्थिर काष्ठा tcphdr *)skb->data;
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	अचिन्हित पूर्णांक len = skb->len;

	/* TCP congestion winकरोw tracking */
	trace_tcp_probe(sk, skb);

	tcp_mstamp_refresh(tp);
	अगर (unlikely(!sk->sk_rx_dst))
		inet_csk(sk)->icsk_af_ops->sk_rx_dst_set(sk, skb);
	/*
	 *	Header prediction.
	 *	The code loosely follows the one in the famous
	 *	"30 instruction TCP receive" Van Jacobson mail.
	 *
	 *	Van's trick is to deposit buffers पूर्णांकo socket queue
	 *	on a device पूर्णांकerrupt, to call tcp_recv function
	 *	on the receive process context and checksum and copy
	 *	the buffer to user space. smart...
	 *
	 *	Our current scheme is not silly either but we take the
	 *	extra cost of the net_bh soft पूर्णांकerrupt processing...
	 *	We करो checksum and copy also but from device to kernel.
	 */

	tp->rx_opt.saw_tstamp = 0;

	/*	pred_flags is 0xS?10 << 16 + snd_wnd
	 *	अगर header_prediction is to be made
	 *	'S' will always be tp->tcp_header_len >> 2
	 *	'?' will be 0 क्रम the fast path, otherwise pred_flags is 0 to
	 *  turn it off	(when there are holes in the receive
	 *	 space क्रम instance)
	 *	PSH flag is ignored.
	 */

	अगर ((tcp_flag_word(th) & TCP_HP_BITS) == tp->pred_flags &&
	    TCP_SKB_CB(skb)->seq == tp->rcv_nxt &&
	    !after(TCP_SKB_CB(skb)->ack_seq, tp->snd_nxt)) अणु
		पूर्णांक tcp_header_len = tp->tcp_header_len;

		/* Timestamp header prediction: tcp_header_len
		 * is स्वतःmatically equal to th->करोff*4 due to pred_flags
		 * match.
		 */

		/* Check बारtamp */
		अगर (tcp_header_len == माप(काष्ठा tcphdr) + TCPOLEN_TSTAMP_ALIGNED) अणु
			/* No? Slow path! */
			अगर (!tcp_parse_aligned_बारtamp(tp, th))
				जाओ slow_path;

			/* If PAWS failed, check it more carefully in slow path */
			अगर ((s32)(tp->rx_opt.rcv_tsval - tp->rx_opt.ts_recent) < 0)
				जाओ slow_path;

			/* DO NOT update ts_recent here, अगर checksum fails
			 * and बारtamp was corrupted part, it will result
			 * in a hung connection since we will drop all
			 * future packets due to the PAWS test.
			 */
		पूर्ण

		अगर (len <= tcp_header_len) अणु
			/* Bulk data transfer: sender */
			अगर (len == tcp_header_len) अणु
				/* Predicted packet is in winकरोw by definition.
				 * seq == rcv_nxt and rcv_wup <= rcv_nxt.
				 * Hence, check seq<=rcv_wup reduces to:
				 */
				अगर (tcp_header_len ==
				    (माप(काष्ठा tcphdr) + TCPOLEN_TSTAMP_ALIGNED) &&
				    tp->rcv_nxt == tp->rcv_wup)
					tcp_store_ts_recent(tp);

				/* We know that such packets are checksummed
				 * on entry.
				 */
				tcp_ack(sk, skb, 0);
				__kमुक्त_skb(skb);
				tcp_data_snd_check(sk);
				/* When receiving pure ack in fast path, update
				 * last ts ecr directly instead of calling
				 * tcp_rcv_rtt_measure_ts()
				 */
				tp->rcv_rtt_last_tsecr = tp->rx_opt.rcv_tsecr;
				वापस;
			पूर्ण अन्यथा अणु /* Header too small */
				TCP_INC_STATS(sock_net(sk), TCP_MIB_INERRS);
				जाओ discard;
			पूर्ण
		पूर्ण अन्यथा अणु
			पूर्णांक eaten = 0;
			bool fragstolen = false;

			अगर (tcp_checksum_complete(skb))
				जाओ csum_error;

			अगर ((पूर्णांक)skb->truesize > sk->sk_क्रमward_alloc)
				जाओ step5;

			/* Predicted packet is in winकरोw by definition.
			 * seq == rcv_nxt and rcv_wup <= rcv_nxt.
			 * Hence, check seq<=rcv_wup reduces to:
			 */
			अगर (tcp_header_len ==
			    (माप(काष्ठा tcphdr) + TCPOLEN_TSTAMP_ALIGNED) &&
			    tp->rcv_nxt == tp->rcv_wup)
				tcp_store_ts_recent(tp);

			tcp_rcv_rtt_measure_ts(sk, skb);

			NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPHPHITS);

			/* Bulk data transfer: receiver */
			__skb_pull(skb, tcp_header_len);
			eaten = tcp_queue_rcv(sk, skb, &fragstolen);

			tcp_event_data_recv(sk, skb);

			अगर (TCP_SKB_CB(skb)->ack_seq != tp->snd_una) अणु
				/* Well, only one small jumplet in fast path... */
				tcp_ack(sk, skb, FLAG_DATA);
				tcp_data_snd_check(sk);
				अगर (!inet_csk_ack_scheduled(sk))
					जाओ no_ack;
			पूर्ण अन्यथा अणु
				tcp_update_wl(tp, TCP_SKB_CB(skb)->seq);
			पूर्ण

			__tcp_ack_snd_check(sk, 0);
no_ack:
			अगर (eaten)
				kमुक्त_skb_partial(skb, fragstolen);
			tcp_data_पढ़ोy(sk);
			वापस;
		पूर्ण
	पूर्ण

slow_path:
	अगर (len < (th->करोff << 2) || tcp_checksum_complete(skb))
		जाओ csum_error;

	अगर (!th->ack && !th->rst && !th->syn)
		जाओ discard;

	/*
	 *	Standard slow path.
	 */

	अगर (!tcp_validate_incoming(sk, skb, th, 1))
		वापस;

step5:
	अगर (tcp_ack(sk, skb, FLAG_SLOWPATH | FLAG_UPDATE_TS_RECENT) < 0)
		जाओ discard;

	tcp_rcv_rtt_measure_ts(sk, skb);

	/* Process urgent data. */
	tcp_urg(sk, skb, th);

	/* step 7: process the segment text */
	tcp_data_queue(sk, skb);

	tcp_data_snd_check(sk);
	tcp_ack_snd_check(sk);
	वापस;

csum_error:
	TCP_INC_STATS(sock_net(sk), TCP_MIB_CSUMERRORS);
	TCP_INC_STATS(sock_net(sk), TCP_MIB_INERRS);

discard:
	tcp_drop(sk, skb);
पूर्ण
EXPORT_SYMBOL(tcp_rcv_established);

व्योम tcp_init_transfer(काष्ठा sock *sk, पूर्णांक bpf_op, काष्ठा sk_buff *skb)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	tcp_mtup_init(sk);
	icsk->icsk_af_ops->rebuild_header(sk);
	tcp_init_metrics(sk);

	/* Initialize the congestion winकरोw to start the transfer.
	 * Cut cwnd करोwn to 1 per RFC5681 अगर SYN or SYN-ACK has been
	 * retransmitted. In light of RFC6298 more aggressive 1sec
	 * initRTO, we only reset cwnd when more than 1 SYN/SYN-ACK
	 * retransmission has occurred.
	 */
	अगर (tp->total_retrans > 1 && tp->unकरो_marker)
		tp->snd_cwnd = 1;
	अन्यथा
		tp->snd_cwnd = tcp_init_cwnd(tp, __sk_dst_get(sk));
	tp->snd_cwnd_stamp = tcp_jअगरfies32;

	icsk->icsk_ca_initialized = 0;
	bpf_skops_established(sk, bpf_op, skb);
	अगर (!icsk->icsk_ca_initialized)
		tcp_init_congestion_control(sk);
	tcp_init_buffer_space(sk);
पूर्ण

व्योम tcp_finish_connect(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	tcp_set_state(sk, TCP_ESTABLISHED);
	icsk->icsk_ack.lrcvसमय = tcp_jअगरfies32;

	अगर (skb) अणु
		icsk->icsk_af_ops->sk_rx_dst_set(sk, skb);
		security_inet_conn_established(sk, skb);
		sk_mark_napi_id(sk, skb);
	पूर्ण

	tcp_init_transfer(sk, BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB, skb);

	/* Prevent spurious tcp_cwnd_restart() on first data
	 * packet.
	 */
	tp->lsndसमय = tcp_jअगरfies32;

	अगर (sock_flag(sk, SOCK_KEEPOPEN))
		inet_csk_reset_keepalive_समयr(sk, keepalive_समय_when(tp));

	अगर (!tp->rx_opt.snd_wscale)
		__tcp_fast_path_on(tp, tp->snd_wnd);
	अन्यथा
		tp->pred_flags = 0;
पूर्ण

अटल bool tcp_rcv_fastखोलो_synack(काष्ठा sock *sk, काष्ठा sk_buff *synack,
				    काष्ठा tcp_fastखोलो_cookie *cookie)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *data = tp->syn_data ? tcp_rtx_queue_head(sk) : शून्य;
	u16 mss = tp->rx_opt.mss_clamp, try_exp = 0;
	bool syn_drop = false;

	अगर (mss == tp->rx_opt.user_mss) अणु
		काष्ठा tcp_options_received opt;

		/* Get original SYNACK MSS value अगर user MSS sets mss_clamp */
		tcp_clear_options(&opt);
		opt.user_mss = opt.mss_clamp = 0;
		tcp_parse_options(sock_net(sk), synack, &opt, 0, शून्य);
		mss = opt.mss_clamp;
	पूर्ण

	अगर (!tp->syn_fastखोलो) अणु
		/* Ignore an unsolicited cookie */
		cookie->len = -1;
	पूर्ण अन्यथा अगर (tp->total_retrans) अणु
		/* SYN समयd out and the SYN-ACK neither has a cookie nor
		 * acknowledges data. Presumably the remote received only
		 * the retransmitted (regular) SYNs: either the original
		 * SYN-data or the corresponding SYN-ACK was dropped.
		 */
		syn_drop = (cookie->len < 0 && data);
	पूर्ण अन्यथा अगर (cookie->len < 0 && !tp->syn_data) अणु
		/* We requested a cookie but didn't get it. If we did not use
		 * the (old) exp opt क्रमmat then try so next समय (try_exp=1).
		 * Otherwise we go back to use the RFC7413 opt (try_exp=2).
		 */
		try_exp = tp->syn_fastखोलो_exp ? 2 : 1;
	पूर्ण

	tcp_fastखोलो_cache_set(sk, mss, cookie, syn_drop, try_exp);

	अगर (data) अणु /* Retransmit unacked data in SYN */
		अगर (tp->total_retrans)
			tp->fastखोलो_client_fail = TFO_SYN_RETRANSMITTED;
		अन्यथा
			tp->fastखोलो_client_fail = TFO_DATA_NOT_ACKED;
		skb_rbtree_walk_from(data)
			 tcp_mark_skb_lost(sk, data);
		tcp_xmit_retransmit_queue(sk);
		NET_INC_STATS(sock_net(sk),
				LINUX_MIB_TCPFASTOPENACTIVEFAIL);
		वापस true;
	पूर्ण
	tp->syn_data_acked = tp->syn_data;
	अगर (tp->syn_data_acked) अणु
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPFASTOPENACTIVE);
		/* SYN-data is counted as two separate packets in tcp_ack() */
		अगर (tp->delivered > 1)
			--tp->delivered;
	पूर्ण

	tcp_fastखोलो_add_skb(sk, synack);

	वापस false;
पूर्ण

अटल व्योम smc_check_reset_syn(काष्ठा tcp_sock *tp)
अणु
#अगर IS_ENABLED(CONFIG_SMC)
	अगर (अटल_branch_unlikely(&tcp_have_smc)) अणु
		अगर (tp->syn_smc && !tp->rx_opt.smc_ok)
			tp->syn_smc = 0;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम tcp_try_unकरो_spurious_syn(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 syn_stamp;

	/* unकरो_marker is set when SYN or SYNACK बार out. The समयout is
	 * spurious अगर the ACK's बारtamp option echo value matches the
	 * original SYN बारtamp.
	 */
	syn_stamp = tp->retrans_stamp;
	अगर (tp->unकरो_marker && syn_stamp && tp->rx_opt.saw_tstamp &&
	    syn_stamp == tp->rx_opt.rcv_tsecr)
		tp->unकरो_marker = 0;
पूर्ण

अटल पूर्णांक tcp_rcv_synsent_state_process(काष्ठा sock *sk, काष्ठा sk_buff *skb,
					 स्थिर काष्ठा tcphdr *th)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा tcp_fastखोलो_cookie foc = अणु .len = -1 पूर्ण;
	पूर्णांक saved_clamp = tp->rx_opt.mss_clamp;
	bool fastखोलो_fail;

	tcp_parse_options(sock_net(sk), skb, &tp->rx_opt, 0, &foc);
	अगर (tp->rx_opt.saw_tstamp && tp->rx_opt.rcv_tsecr)
		tp->rx_opt.rcv_tsecr -= tp->tsoffset;

	अगर (th->ack) अणु
		/* rfc793:
		 * "If the state is SYN-SENT then
		 *    first check the ACK bit
		 *      If the ACK bit is set
		 *	  If SEG.ACK =< ISS, or SEG.ACK > SND.NXT, send
		 *        a reset (unless the RST bit is set, अगर so drop
		 *        the segment and वापस)"
		 */
		अगर (!after(TCP_SKB_CB(skb)->ack_seq, tp->snd_una) ||
		    after(TCP_SKB_CB(skb)->ack_seq, tp->snd_nxt)) अणु
			/* Previous FIN/ACK or RST/ACK might be ignored. */
			अगर (icsk->icsk_retransmits == 0)
				inet_csk_reset_xmit_समयr(sk,
						ICSK_TIME_RETRANS,
						TCP_TIMEOUT_MIN, TCP_RTO_MAX);
			जाओ reset_and_unकरो;
		पूर्ण

		अगर (tp->rx_opt.saw_tstamp && tp->rx_opt.rcv_tsecr &&
		    !between(tp->rx_opt.rcv_tsecr, tp->retrans_stamp,
			     tcp_समय_stamp(tp))) अणु
			NET_INC_STATS(sock_net(sk),
					LINUX_MIB_PAWSACTIVEREJECTED);
			जाओ reset_and_unकरो;
		पूर्ण

		/* Now ACK is acceptable.
		 *
		 * "If the RST bit is set
		 *    If the ACK was acceptable then संकेत the user "error:
		 *    connection reset", drop the segment, enter CLOSED state,
		 *    delete TCB, and वापस."
		 */

		अगर (th->rst) अणु
			tcp_reset(sk, skb);
			जाओ discard;
		पूर्ण

		/* rfc793:
		 *   "fअगरth, अगर neither of the SYN or RST bits is set then
		 *    drop the segment and वापस."
		 *
		 *    See note below!
		 *                                        --ANK(990513)
		 */
		अगर (!th->syn)
			जाओ discard_and_unकरो;

		/* rfc793:
		 *   "If the SYN bit is on ...
		 *    are acceptable then ...
		 *    (our SYN has been ACKed), change the connection
		 *    state to ESTABLISHED..."
		 */

		tcp_ecn_rcv_synack(tp, th);

		tcp_init_wl(tp, TCP_SKB_CB(skb)->seq);
		tcp_try_unकरो_spurious_syn(sk);
		tcp_ack(sk, skb, FLAG_SLOWPATH);

		/* Ok.. it's good. Set up sequence numbers and
		 * move to established.
		 */
		WRITE_ONCE(tp->rcv_nxt, TCP_SKB_CB(skb)->seq + 1);
		tp->rcv_wup = TCP_SKB_CB(skb)->seq + 1;

		/* RFC1323: The winकरोw in SYN & SYN/ACK segments is
		 * never scaled.
		 */
		tp->snd_wnd = ntohs(th->winकरोw);

		अगर (!tp->rx_opt.wscale_ok) अणु
			tp->rx_opt.snd_wscale = tp->rx_opt.rcv_wscale = 0;
			tp->winकरोw_clamp = min(tp->winकरोw_clamp, 65535U);
		पूर्ण

		अगर (tp->rx_opt.saw_tstamp) अणु
			tp->rx_opt.tstamp_ok	   = 1;
			tp->tcp_header_len =
				माप(काष्ठा tcphdr) + TCPOLEN_TSTAMP_ALIGNED;
			tp->advmss	    -= TCPOLEN_TSTAMP_ALIGNED;
			tcp_store_ts_recent(tp);
		पूर्ण अन्यथा अणु
			tp->tcp_header_len = माप(काष्ठा tcphdr);
		पूर्ण

		tcp_sync_mss(sk, icsk->icsk_pmtu_cookie);
		tcp_initialize_rcv_mss(sk);

		/* Remember, tcp_poll() करोes not lock socket!
		 * Change state from SYN-SENT only after copied_seq
		 * is initialized. */
		WRITE_ONCE(tp->copied_seq, tp->rcv_nxt);

		smc_check_reset_syn(tp);

		smp_mb();

		tcp_finish_connect(sk, skb);

		fastखोलो_fail = (tp->syn_fastखोलो || tp->syn_data) &&
				tcp_rcv_fastखोलो_synack(sk, skb, &foc);

		अगर (!sock_flag(sk, SOCK_DEAD)) अणु
			sk->sk_state_change(sk);
			sk_wake_async(sk, SOCK_WAKE_IO, POLL_OUT);
		पूर्ण
		अगर (fastखोलो_fail)
			वापस -1;
		अगर (sk->sk_ग_लिखो_pending ||
		    icsk->icsk_accept_queue.rskq_defer_accept ||
		    inet_csk_in_pingpong_mode(sk)) अणु
			/* Save one ACK. Data will be पढ़ोy after
			 * several ticks, अगर ग_लिखो_pending is set.
			 *
			 * It may be deleted, but with this feature tcpdumps
			 * look so _wonderfully_ clever, that I was not able
			 * to stand against the temptation 8)     --ANK
			 */
			inet_csk_schedule_ack(sk);
			tcp_enter_quickack_mode(sk, TCP_MAX_QUICKACKS);
			inet_csk_reset_xmit_समयr(sk, ICSK_TIME_DACK,
						  TCP_DELACK_MAX, TCP_RTO_MAX);

discard:
			tcp_drop(sk, skb);
			वापस 0;
		पूर्ण अन्यथा अणु
			tcp_send_ack(sk);
		पूर्ण
		वापस -1;
	पूर्ण

	/* No ACK in the segment */

	अगर (th->rst) अणु
		/* rfc793:
		 * "If the RST bit is set
		 *
		 *      Otherwise (no ACK) drop the segment and वापस."
		 */

		जाओ discard_and_unकरो;
	पूर्ण

	/* PAWS check. */
	अगर (tp->rx_opt.ts_recent_stamp && tp->rx_opt.saw_tstamp &&
	    tcp_paws_reject(&tp->rx_opt, 0))
		जाओ discard_and_unकरो;

	अगर (th->syn) अणु
		/* We see SYN without ACK. It is attempt of
		 * simultaneous connect with crossed SYNs.
		 * Particularly, it can be connect to self.
		 */
		tcp_set_state(sk, TCP_SYN_RECV);

		अगर (tp->rx_opt.saw_tstamp) अणु
			tp->rx_opt.tstamp_ok = 1;
			tcp_store_ts_recent(tp);
			tp->tcp_header_len =
				माप(काष्ठा tcphdr) + TCPOLEN_TSTAMP_ALIGNED;
		पूर्ण अन्यथा अणु
			tp->tcp_header_len = माप(काष्ठा tcphdr);
		पूर्ण

		WRITE_ONCE(tp->rcv_nxt, TCP_SKB_CB(skb)->seq + 1);
		WRITE_ONCE(tp->copied_seq, tp->rcv_nxt);
		tp->rcv_wup = TCP_SKB_CB(skb)->seq + 1;

		/* RFC1323: The winकरोw in SYN & SYN/ACK segments is
		 * never scaled.
		 */
		tp->snd_wnd    = ntohs(th->winकरोw);
		tp->snd_wl1    = TCP_SKB_CB(skb)->seq;
		tp->max_winकरोw = tp->snd_wnd;

		tcp_ecn_rcv_syn(tp, th);

		tcp_mtup_init(sk);
		tcp_sync_mss(sk, icsk->icsk_pmtu_cookie);
		tcp_initialize_rcv_mss(sk);

		tcp_send_synack(sk);
#अगर 0
		/* Note, we could accept data and URG from this segment.
		 * There are no obstacles to make this (except that we must
		 * either change tcp_recvmsg() to prevent it from वापसing data
		 * beक्रमe 3WHS completes per RFC793, or employ TCP Fast Open).
		 *
		 * However, अगर we ignore data in ACKless segments someबार,
		 * we have no reasons to accept it someबार.
		 * Also, seems the code करोing it in step6 of tcp_rcv_state_process
		 * is not flawless. So, discard packet क्रम sanity.
		 * Uncomment this वापस to process the data.
		 */
		वापस -1;
#अन्यथा
		जाओ discard;
#पूर्ण_अगर
	पूर्ण
	/* "fअगरth, अगर neither of the SYN or RST bits is set then
	 * drop the segment and वापस."
	 */

discard_and_unकरो:
	tcp_clear_options(&tp->rx_opt);
	tp->rx_opt.mss_clamp = saved_clamp;
	जाओ discard;

reset_and_unकरो:
	tcp_clear_options(&tp->rx_opt);
	tp->rx_opt.mss_clamp = saved_clamp;
	वापस 1;
पूर्ण

अटल व्योम tcp_rcv_synrecv_state_fastखोलो(काष्ठा sock *sk)
अणु
	काष्ठा request_sock *req;

	/* If we are still handling the SYNACK RTO, see अगर बारtamp ECR allows
	 * unकरो. If peer SACKs triggered fast recovery, we can't unकरो here.
	 */
	अगर (inet_csk(sk)->icsk_ca_state == TCP_CA_Loss)
		tcp_try_unकरो_loss(sk, false);

	/* Reset rtx states to prevent spurious retransmits_समयd_out() */
	tcp_sk(sk)->retrans_stamp = 0;
	inet_csk(sk)->icsk_retransmits = 0;

	/* Once we leave TCP_SYN_RECV or TCP_FIN_WAIT_1,
	 * we no दीर्घer need req so release it.
	 */
	req = rcu_dereference_रक्षित(tcp_sk(sk)->fastखोलो_rsk,
					lockdep_sock_is_held(sk));
	reqsk_fastखोलो_हटाओ(sk, req, false);

	/* Re-arm the समयr because data may have been sent out.
	 * This is similar to the regular data transmission हाल
	 * when new data has just been ack'ed.
	 *
	 * (TFO) - we could try to be more aggressive and
	 * retransmitting any data sooner based on when they
	 * are sent out.
	 */
	tcp_rearm_rto(sk);
पूर्ण

/*
 *	This function implements the receiving procedure of RFC 793 क्रम
 *	all states except ESTABLISHED and TIME_WAIT.
 *	It's called from both tcp_v4_rcv and tcp_v6_rcv and should be
 *	address independent.
 */

पूर्णांक tcp_rcv_state_process(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	स्थिर काष्ठा tcphdr *th = tcp_hdr(skb);
	काष्ठा request_sock *req;
	पूर्णांक queued = 0;
	bool acceptable;

	चयन (sk->sk_state) अणु
	हाल TCP_CLOSE:
		जाओ discard;

	हाल TCP_LISTEN:
		अगर (th->ack)
			वापस 1;

		अगर (th->rst)
			जाओ discard;

		अगर (th->syn) अणु
			अगर (th->fin)
				जाओ discard;
			/* It is possible that we process SYN packets from backlog,
			 * so we need to make sure to disable BH and RCU right there.
			 */
			rcu_पढ़ो_lock();
			local_bh_disable();
			acceptable = icsk->icsk_af_ops->conn_request(sk, skb) >= 0;
			local_bh_enable();
			rcu_पढ़ो_unlock();

			अगर (!acceptable)
				वापस 1;
			consume_skb(skb);
			वापस 0;
		पूर्ण
		जाओ discard;

	हाल TCP_SYN_SENT:
		tp->rx_opt.saw_tstamp = 0;
		tcp_mstamp_refresh(tp);
		queued = tcp_rcv_synsent_state_process(sk, skb, th);
		अगर (queued >= 0)
			वापस queued;

		/* Do step6 onward by hand. */
		tcp_urg(sk, skb, th);
		__kमुक्त_skb(skb);
		tcp_data_snd_check(sk);
		वापस 0;
	पूर्ण

	tcp_mstamp_refresh(tp);
	tp->rx_opt.saw_tstamp = 0;
	req = rcu_dereference_रक्षित(tp->fastखोलो_rsk,
					lockdep_sock_is_held(sk));
	अगर (req) अणु
		bool req_stolen;

		WARN_ON_ONCE(sk->sk_state != TCP_SYN_RECV &&
		    sk->sk_state != TCP_FIN_WAIT1);

		अगर (!tcp_check_req(sk, skb, req, true, &req_stolen))
			जाओ discard;
	पूर्ण

	अगर (!th->ack && !th->rst && !th->syn)
		जाओ discard;

	अगर (!tcp_validate_incoming(sk, skb, th, 0))
		वापस 0;

	/* step 5: check the ACK field */
	acceptable = tcp_ack(sk, skb, FLAG_SLOWPATH |
				      FLAG_UPDATE_TS_RECENT |
				      FLAG_NO_CHALLENGE_ACK) > 0;

	अगर (!acceptable) अणु
		अगर (sk->sk_state == TCP_SYN_RECV)
			वापस 1;	/* send one RST */
		tcp_send_challenge_ack(sk, skb);
		जाओ discard;
	पूर्ण
	चयन (sk->sk_state) अणु
	हाल TCP_SYN_RECV:
		tp->delivered++; /* SYN-ACK delivery isn't tracked in tcp_ack */
		अगर (!tp->srtt_us)
			tcp_synack_rtt_meas(sk, req);

		अगर (req) अणु
			tcp_rcv_synrecv_state_fastखोलो(sk);
		पूर्ण अन्यथा अणु
			tcp_try_unकरो_spurious_syn(sk);
			tp->retrans_stamp = 0;
			tcp_init_transfer(sk, BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB,
					  skb);
			WRITE_ONCE(tp->copied_seq, tp->rcv_nxt);
		पूर्ण
		smp_mb();
		tcp_set_state(sk, TCP_ESTABLISHED);
		sk->sk_state_change(sk);

		/* Note, that this wakeup is only क्रम marginal crossed SYN हाल.
		 * Passively खोलो sockets are not waked up, because
		 * sk->sk_sleep == शून्य and sk->sk_socket == शून्य.
		 */
		अगर (sk->sk_socket)
			sk_wake_async(sk, SOCK_WAKE_IO, POLL_OUT);

		tp->snd_una = TCP_SKB_CB(skb)->ack_seq;
		tp->snd_wnd = ntohs(th->winकरोw) << tp->rx_opt.snd_wscale;
		tcp_init_wl(tp, TCP_SKB_CB(skb)->seq);

		अगर (tp->rx_opt.tstamp_ok)
			tp->advmss -= TCPOLEN_TSTAMP_ALIGNED;

		अगर (!inet_csk(sk)->icsk_ca_ops->cong_control)
			tcp_update_pacing_rate(sk);

		/* Prevent spurious tcp_cwnd_restart() on first data packet */
		tp->lsndसमय = tcp_jअगरfies32;

		tcp_initialize_rcv_mss(sk);
		tcp_fast_path_on(tp);
		अवरोध;

	हाल TCP_FIN_WAIT1: अणु
		पूर्णांक पंचांगo;

		अगर (req)
			tcp_rcv_synrecv_state_fastखोलो(sk);

		अगर (tp->snd_una != tp->ग_लिखो_seq)
			अवरोध;

		tcp_set_state(sk, TCP_FIN_WAIT2);
		sk->sk_shutकरोwn |= SEND_SHUTDOWN;

		sk_dst_confirm(sk);

		अगर (!sock_flag(sk, SOCK_DEAD)) अणु
			/* Wake up lingering बंद() */
			sk->sk_state_change(sk);
			अवरोध;
		पूर्ण

		अगर (tp->linger2 < 0) अणु
			tcp_करोne(sk);
			NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPABORTONDATA);
			वापस 1;
		पूर्ण
		अगर (TCP_SKB_CB(skb)->end_seq != TCP_SKB_CB(skb)->seq &&
		    after(TCP_SKB_CB(skb)->end_seq - th->fin, tp->rcv_nxt)) अणु
			/* Receive out of order FIN after बंद() */
			अगर (tp->syn_fastखोलो && th->fin)
				tcp_fastखोलो_active_disable(sk);
			tcp_करोne(sk);
			NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPABORTONDATA);
			वापस 1;
		पूर्ण

		पंचांगo = tcp_fin_समय(sk);
		अगर (पंचांगo > TCP_TIMEWAIT_LEN) अणु
			inet_csk_reset_keepalive_समयr(sk, पंचांगo - TCP_TIMEWAIT_LEN);
		पूर्ण अन्यथा अगर (th->fin || sock_owned_by_user(sk)) अणु
			/* Bad हाल. We could lose such FIN otherwise.
			 * It is not a big problem, but it looks confusing
			 * and not so rare event. We still can lose it now,
			 * अगर it spins in bh_lock_sock(), but it is really
			 * marginal हाल.
			 */
			inet_csk_reset_keepalive_समयr(sk, पंचांगo);
		पूर्ण अन्यथा अणु
			tcp_समय_रुको(sk, TCP_FIN_WAIT2, पंचांगo);
			जाओ discard;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल TCP_CLOSING:
		अगर (tp->snd_una == tp->ग_लिखो_seq) अणु
			tcp_समय_रुको(sk, TCP_TIME_WAIT, 0);
			जाओ discard;
		पूर्ण
		अवरोध;

	हाल TCP_LAST_ACK:
		अगर (tp->snd_una == tp->ग_लिखो_seq) अणु
			tcp_update_metrics(sk);
			tcp_करोne(sk);
			जाओ discard;
		पूर्ण
		अवरोध;
	पूर्ण

	/* step 6: check the URG bit */
	tcp_urg(sk, skb, th);

	/* step 7: process the segment text */
	चयन (sk->sk_state) अणु
	हाल TCP_CLOSE_WAIT:
	हाल TCP_CLOSING:
	हाल TCP_LAST_ACK:
		अगर (!beक्रमe(TCP_SKB_CB(skb)->seq, tp->rcv_nxt)) अणु
			अगर (sk_is_mptcp(sk))
				mptcp_incoming_options(sk, skb);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल TCP_FIN_WAIT1:
	हाल TCP_FIN_WAIT2:
		/* RFC 793 says to queue data in these states,
		 * RFC 1122 says we MUST send a reset.
		 * BSD 4.4 also करोes reset.
		 */
		अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN) अणु
			अगर (TCP_SKB_CB(skb)->end_seq != TCP_SKB_CB(skb)->seq &&
			    after(TCP_SKB_CB(skb)->end_seq - th->fin, tp->rcv_nxt)) अणु
				NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPABORTONDATA);
				tcp_reset(sk, skb);
				वापस 1;
			पूर्ण
		पूर्ण
		fallthrough;
	हाल TCP_ESTABLISHED:
		tcp_data_queue(sk, skb);
		queued = 1;
		अवरोध;
	पूर्ण

	/* tcp_data could move socket to TIME-WAIT */
	अगर (sk->sk_state != TCP_CLOSE) अणु
		tcp_data_snd_check(sk);
		tcp_ack_snd_check(sk);
	पूर्ण

	अगर (!queued) अणु
discard:
		tcp_drop(sk, skb);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tcp_rcv_state_process);

अटल अंतरभूत व्योम pr_drop_req(काष्ठा request_sock *req, __u16 port, पूर्णांक family)
अणु
	काष्ठा inet_request_sock *ireq = inet_rsk(req);

	अगर (family == AF_INET)
		net_dbg_ratelimited("drop open request from %pI4/%u\n",
				    &ireq->ir_rmt_addr, port);
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा अगर (family == AF_INET6)
		net_dbg_ratelimited("drop open request from %pI6/%u\n",
				    &ireq->ir_v6_rmt_addr, port);
#पूर्ण_अगर
पूर्ण

/* RFC3168 : 6.1.1 SYN packets must not have ECT/ECN bits set
 *
 * If we receive a SYN packet with these bits set, it means a
 * network is playing bad games with TOS bits. In order to
 * aव्योम possible false congestion notअगरications, we disable
 * TCP ECN negotiation.
 *
 * Exception: tcp_ca wants ECN. This is required क्रम DCTCP
 * congestion control: Linux DCTCP निश्चितs ECT on all packets,
 * including SYN, which is most optimal solution; however,
 * others, such as FreeBSD करो not.
 *
 * Exception: At least one of the reserved bits of the TCP header (th->res1) is
 * set, indicating the use of a future TCP extension (such as AccECN). See
 * RFC8311 तई4.3 which updates RFC3168 to allow the development of such
 * extensions.
 */
अटल व्योम tcp_ecn_create_request(काष्ठा request_sock *req,
				   स्थिर काष्ठा sk_buff *skb,
				   स्थिर काष्ठा sock *listen_sk,
				   स्थिर काष्ठा dst_entry *dst)
अणु
	स्थिर काष्ठा tcphdr *th = tcp_hdr(skb);
	स्थिर काष्ठा net *net = sock_net(listen_sk);
	bool th_ecn = th->ece && th->cwr;
	bool ect, ecn_ok;
	u32 ecn_ok_dst;

	अगर (!th_ecn)
		वापस;

	ect = !INET_ECN_is_not_ect(TCP_SKB_CB(skb)->ip_dsfield);
	ecn_ok_dst = dst_feature(dst, DST_FEATURE_ECN_MASK);
	ecn_ok = net->ipv4.sysctl_tcp_ecn || ecn_ok_dst;

	अगर (((!ect || th->res1) && ecn_ok) || tcp_ca_needs_ecn(listen_sk) ||
	    (ecn_ok_dst & DST_FEATURE_ECN_CA) ||
	    tcp_bpf_ca_needs_ecn((काष्ठा sock *)req))
		inet_rsk(req)->ecn_ok = 1;
पूर्ण

अटल व्योम tcp_खोलोreq_init(काष्ठा request_sock *req,
			     स्थिर काष्ठा tcp_options_received *rx_opt,
			     काष्ठा sk_buff *skb, स्थिर काष्ठा sock *sk)
अणु
	काष्ठा inet_request_sock *ireq = inet_rsk(req);

	req->rsk_rcv_wnd = 0;		/* So that tcp_send_synack() knows! */
	tcp_rsk(req)->rcv_isn = TCP_SKB_CB(skb)->seq;
	tcp_rsk(req)->rcv_nxt = TCP_SKB_CB(skb)->seq + 1;
	tcp_rsk(req)->snt_synack = 0;
	tcp_rsk(req)->last_oow_ack_समय = 0;
	req->mss = rx_opt->mss_clamp;
	req->ts_recent = rx_opt->saw_tstamp ? rx_opt->rcv_tsval : 0;
	ireq->tstamp_ok = rx_opt->tstamp_ok;
	ireq->sack_ok = rx_opt->sack_ok;
	ireq->snd_wscale = rx_opt->snd_wscale;
	ireq->wscale_ok = rx_opt->wscale_ok;
	ireq->acked = 0;
	ireq->ecn_ok = 0;
	ireq->ir_rmt_port = tcp_hdr(skb)->source;
	ireq->ir_num = ntohs(tcp_hdr(skb)->dest);
	ireq->ir_mark = inet_request_mark(sk, skb);
#अगर IS_ENABLED(CONFIG_SMC)
	ireq->smc_ok = rx_opt->smc_ok;
#पूर्ण_अगर
पूर्ण

काष्ठा request_sock *inet_reqsk_alloc(स्थिर काष्ठा request_sock_ops *ops,
				      काष्ठा sock *sk_listener,
				      bool attach_listener)
अणु
	काष्ठा request_sock *req = reqsk_alloc(ops, sk_listener,
					       attach_listener);

	अगर (req) अणु
		काष्ठा inet_request_sock *ireq = inet_rsk(req);

		ireq->ireq_opt = शून्य;
#अगर IS_ENABLED(CONFIG_IPV6)
		ireq->pktopts = शून्य;
#पूर्ण_अगर
		atomic64_set(&ireq->ir_cookie, 0);
		ireq->ireq_state = TCP_NEW_SYN_RECV;
		ग_लिखो_pnet(&ireq->ireq_net, sock_net(sk_listener));
		ireq->ireq_family = sk_listener->sk_family;
	पूर्ण

	वापस req;
पूर्ण
EXPORT_SYMBOL(inet_reqsk_alloc);

/*
 * Return true अगर a syncookie should be sent
 */
अटल bool tcp_syn_flood_action(स्थिर काष्ठा sock *sk, स्थिर अक्षर *proto)
अणु
	काष्ठा request_sock_queue *queue = &inet_csk(sk)->icsk_accept_queue;
	स्थिर अक्षर *msg = "Dropping request";
	bool want_cookie = false;
	काष्ठा net *net = sock_net(sk);

#अगर_घोषित CONFIG_SYN_COOKIES
	अगर (net->ipv4.sysctl_tcp_syncookies) अणु
		msg = "Sending cookies";
		want_cookie = true;
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPREQQFULLDOCOOKIES);
	पूर्ण अन्यथा
#पूर्ण_अगर
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPREQQFULLDROP);

	अगर (!queue->synflood_warned &&
	    net->ipv4.sysctl_tcp_syncookies != 2 &&
	    xchg(&queue->synflood_warned, 1) == 0)
		net_info_ratelimited("%s: Possible SYN flooding on port %d. %s.  Check SNMP counters.\n",
				     proto, sk->sk_num, msg);

	वापस want_cookie;
पूर्ण

अटल व्योम tcp_reqsk_record_syn(स्थिर काष्ठा sock *sk,
				 काष्ठा request_sock *req,
				 स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (tcp_sk(sk)->save_syn) अणु
		u32 len = skb_network_header_len(skb) + tcp_hdrlen(skb);
		काष्ठा saved_syn *saved_syn;
		u32 mac_hdrlen;
		व्योम *base;

		अगर (tcp_sk(sk)->save_syn == 2) अणु  /* Save full header. */
			base = skb_mac_header(skb);
			mac_hdrlen = skb_mac_header_len(skb);
			len += mac_hdrlen;
		पूर्ण अन्यथा अणु
			base = skb_network_header(skb);
			mac_hdrlen = 0;
		पूर्ण

		saved_syn = kदो_स्मृति(काष्ठा_size(saved_syn, data, len),
				    GFP_ATOMIC);
		अगर (saved_syn) अणु
			saved_syn->mac_hdrlen = mac_hdrlen;
			saved_syn->network_hdrlen = skb_network_header_len(skb);
			saved_syn->tcp_hdrlen = tcp_hdrlen(skb);
			स_नकल(saved_syn->data, base, len);
			req->saved_syn = saved_syn;
		पूर्ण
	पूर्ण
पूर्ण

/* If a SYN cookie is required and supported, वापसs a clamped MSS value to be
 * used क्रम SYN cookie generation.
 */
u16 tcp_get_syncookie_mss(काष्ठा request_sock_ops *rsk_ops,
			  स्थिर काष्ठा tcp_request_sock_ops *af_ops,
			  काष्ठा sock *sk, काष्ठा tcphdr *th)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u16 mss;

	अगर (sock_net(sk)->ipv4.sysctl_tcp_syncookies != 2 &&
	    !inet_csk_reqsk_queue_is_full(sk))
		वापस 0;

	अगर (!tcp_syn_flood_action(sk, rsk_ops->slab_name))
		वापस 0;

	अगर (sk_acceptq_is_full(sk)) अणु
		NET_INC_STATS(sock_net(sk), LINUX_MIB_LISTENOVERFLOWS);
		वापस 0;
	पूर्ण

	mss = tcp_parse_mss_option(th, tp->rx_opt.user_mss);
	अगर (!mss)
		mss = af_ops->mss_clamp;

	वापस mss;
पूर्ण
EXPORT_SYMBOL_GPL(tcp_get_syncookie_mss);

पूर्णांक tcp_conn_request(काष्ठा request_sock_ops *rsk_ops,
		     स्थिर काष्ठा tcp_request_sock_ops *af_ops,
		     काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_fastखोलो_cookie foc = अणु .len = -1 पूर्ण;
	__u32 isn = TCP_SKB_CB(skb)->tcp_tw_isn;
	काष्ठा tcp_options_received पंचांगp_opt;
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा net *net = sock_net(sk);
	काष्ठा sock *fastखोलो_sk = शून्य;
	काष्ठा request_sock *req;
	bool want_cookie = false;
	काष्ठा dst_entry *dst;
	काष्ठा flowi fl;

	/* TW buckets are converted to खोलो requests without
	 * limitations, they conserve resources and peer is
	 * evidently real one.
	 */
	अगर ((net->ipv4.sysctl_tcp_syncookies == 2 ||
	     inet_csk_reqsk_queue_is_full(sk)) && !isn) अणु
		want_cookie = tcp_syn_flood_action(sk, rsk_ops->slab_name);
		अगर (!want_cookie)
			जाओ drop;
	पूर्ण

	अगर (sk_acceptq_is_full(sk)) अणु
		NET_INC_STATS(sock_net(sk), LINUX_MIB_LISTENOVERFLOWS);
		जाओ drop;
	पूर्ण

	req = inet_reqsk_alloc(rsk_ops, sk, !want_cookie);
	अगर (!req)
		जाओ drop;

	req->syncookie = want_cookie;
	tcp_rsk(req)->af_specअगरic = af_ops;
	tcp_rsk(req)->ts_off = 0;
#अगर IS_ENABLED(CONFIG_MPTCP)
	tcp_rsk(req)->is_mptcp = 0;
#पूर्ण_अगर

	tcp_clear_options(&पंचांगp_opt);
	पंचांगp_opt.mss_clamp = af_ops->mss_clamp;
	पंचांगp_opt.user_mss  = tp->rx_opt.user_mss;
	tcp_parse_options(sock_net(sk), skb, &पंचांगp_opt, 0,
			  want_cookie ? शून्य : &foc);

	अगर (want_cookie && !पंचांगp_opt.saw_tstamp)
		tcp_clear_options(&पंचांगp_opt);

	अगर (IS_ENABLED(CONFIG_SMC) && want_cookie)
		पंचांगp_opt.smc_ok = 0;

	पंचांगp_opt.tstamp_ok = पंचांगp_opt.saw_tstamp;
	tcp_खोलोreq_init(req, &पंचांगp_opt, skb, sk);
	inet_rsk(req)->no_srccheck = inet_sk(sk)->transparent;

	/* Note: tcp_v6_init_req() might override ir_iअगर क्रम link locals */
	inet_rsk(req)->ir_iअगर = inet_request_bound_dev_अगर(sk, skb);

	dst = af_ops->route_req(sk, skb, &fl, req);
	अगर (!dst)
		जाओ drop_and_मुक्त;

	अगर (पंचांगp_opt.tstamp_ok)
		tcp_rsk(req)->ts_off = af_ops->init_ts_off(net, skb);

	अगर (!want_cookie && !isn) अणु
		/* Kill the following clause, अगर you dislike this way. */
		अगर (!net->ipv4.sysctl_tcp_syncookies &&
		    (net->ipv4.sysctl_max_syn_backlog - inet_csk_reqsk_queue_len(sk) <
		     (net->ipv4.sysctl_max_syn_backlog >> 2)) &&
		    !tcp_peer_is_proven(req, dst)) अणु
			/* Without syncookies last quarter of
			 * backlog is filled with destinations,
			 * proven to be alive.
			 * It means that we जारी to communicate
			 * to destinations, alपढ़ोy remembered
			 * to the moment of synflood.
			 */
			pr_drop_req(req, ntohs(tcp_hdr(skb)->source),
				    rsk_ops->family);
			जाओ drop_and_release;
		पूर्ण

		isn = af_ops->init_seq(skb);
	पूर्ण

	tcp_ecn_create_request(req, skb, sk, dst);

	अगर (want_cookie) अणु
		isn = cookie_init_sequence(af_ops, sk, skb, &req->mss);
		अगर (!पंचांगp_opt.tstamp_ok)
			inet_rsk(req)->ecn_ok = 0;
	पूर्ण

	tcp_rsk(req)->snt_isn = isn;
	tcp_rsk(req)->txhash = net_tx_rndhash();
	tcp_rsk(req)->syn_tos = TCP_SKB_CB(skb)->ip_dsfield;
	tcp_खोलोreq_init_rwin(req, sk, dst);
	sk_rx_queue_set(req_to_sk(req), skb);
	अगर (!want_cookie) अणु
		tcp_reqsk_record_syn(sk, req, skb);
		fastखोलो_sk = tcp_try_fastखोलो(sk, skb, req, &foc, dst);
	पूर्ण
	अगर (fastखोलो_sk) अणु
		af_ops->send_synack(fastखोलो_sk, dst, &fl, req,
				    &foc, TCP_SYNACK_FASTOPEN, skb);
		/* Add the child socket directly पूर्णांकo the accept queue */
		अगर (!inet_csk_reqsk_queue_add(sk, req, fastखोलो_sk)) अणु
			reqsk_fastखोलो_हटाओ(fastखोलो_sk, req, false);
			bh_unlock_sock(fastखोलो_sk);
			sock_put(fastखोलो_sk);
			जाओ drop_and_मुक्त;
		पूर्ण
		sk->sk_data_पढ़ोy(sk);
		bh_unlock_sock(fastखोलो_sk);
		sock_put(fastखोलो_sk);
	पूर्ण अन्यथा अणु
		tcp_rsk(req)->tfo_listener = false;
		अगर (!want_cookie)
			inet_csk_reqsk_queue_hash_add(sk, req,
				tcp_समयout_init((काष्ठा sock *)req));
		af_ops->send_synack(sk, dst, &fl, req, &foc,
				    !want_cookie ? TCP_SYNACK_NORMAL :
						   TCP_SYNACK_COOKIE,
				    skb);
		अगर (want_cookie) अणु
			reqsk_मुक्त(req);
			वापस 0;
		पूर्ण
	पूर्ण
	reqsk_put(req);
	वापस 0;

drop_and_release:
	dst_release(dst);
drop_and_मुक्त:
	__reqsk_मुक्त(req);
drop:
	tcp_listendrop(sk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tcp_conn_request);
