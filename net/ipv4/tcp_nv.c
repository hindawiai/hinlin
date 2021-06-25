<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TCP NV: TCP with Congestion Aव्योमance
 *
 * TCP-NV is a successor of TCP-Vegas that has been developed to
 * deal with the issues that occur in modern networks.
 * Like TCP-Vegas, TCP-NV supports true congestion aव्योमance,
 * the ability to detect congestion beक्रमe packet losses occur.
 * When congestion (queue buildup) starts to occur, TCP-NV
 * predicts what the cwnd size should be क्रम the current
 * throughput and it reduces the cwnd proportionally to
 * the dअगरference between the current cwnd and the predicted cwnd.
 *
 * NV is only recommeneded क्रम traffic within a data center, and when
 * all the flows are NV (at least those within the data center). This
 * is due to the inherent unfairness between flows using losses to
 * detect congestion (congestion control) and those that use queue
 * buildup to detect congestion (congestion aव्योमance).
 *
 * Note: High NIC coalescence values may lower the perक्रमmance of NV
 * due to the increased noise in RTT values. In particular, we have
 * seen issues with rx-frames values greater than 8.
 *
 * TODO:
 * 1) Add mechanism to deal with reverse congestion.
 */

#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/math64.h>
#समावेश <net/tcp.h>
#समावेश <linux/inet_diag.h>

/* TCP NV parameters
 *
 * nv_pad		Max number of queued packets allowed in network
 * nv_pad_buffer	Do not grow cwnd अगर this बंदd to nv_pad
 * nv_reset_period	How often (in) seconds)to reset min_rtt
 * nv_min_cwnd		Don't decrease cwnd below this अगर there are no losses
 * nv_cong_dec_mult	Decrease cwnd by X% (30%) of congestion when detected
 * nv_ssthresh_factor	On congestion set ssthresh to this * <desired cwnd> / 8
 * nv_rtt_factor	RTT averaging factor
 * nv_loss_dec_factor	Decrease cwnd to this (80%) when losses occur
 * nv_dec_eval_min_calls	Wait this many RTT measurements beक्रमe dec cwnd
 * nv_inc_eval_min_calls	Wait this many RTT measurements beक्रमe inc cwnd
 * nv_ssthresh_eval_min_calls	Wait this many RTT measurements beक्रमe stopping
 *				slow-start due to congestion
 * nv_stop_rtt_cnt	Only grow cwnd क्रम this many RTTs after non-congestion
 * nv_rtt_min_cnt	Wait these many RTTs beक्रमe making congesion decision
 * nv_cwnd_growth_rate_neg
 * nv_cwnd_growth_rate_pos
 *	How quickly to द्विगुन growth rate (not rate) of cwnd when not
 *	congested. One value (nv_cwnd_growth_rate_neg) क्रम when
 *	rate < 1 pkt/RTT (after losses). The other (nv_cwnd_growth_rate_pos)
 *	otherwise.
 */

अटल पूर्णांक nv_pad __पढ़ो_mostly = 10;
अटल पूर्णांक nv_pad_buffer __पढ़ो_mostly = 2;
अटल पूर्णांक nv_reset_period __पढ़ो_mostly = 5; /* in seconds */
अटल पूर्णांक nv_min_cwnd __पढ़ो_mostly = 2;
अटल पूर्णांक nv_cong_dec_mult __पढ़ो_mostly = 30 * 128 / 100; /* = 30% */
अटल पूर्णांक nv_ssthresh_factor __पढ़ो_mostly = 8; /* = 1 */
अटल पूर्णांक nv_rtt_factor __पढ़ो_mostly = 128; /* = 1/2*old + 1/2*new */
अटल पूर्णांक nv_loss_dec_factor __पढ़ो_mostly = 819; /* => 80% */
अटल पूर्णांक nv_cwnd_growth_rate_neg __पढ़ो_mostly = 8;
अटल पूर्णांक nv_cwnd_growth_rate_pos __पढ़ो_mostly; /* 0 => fixed like Reno */
अटल पूर्णांक nv_dec_eval_min_calls __पढ़ो_mostly = 60;
अटल पूर्णांक nv_inc_eval_min_calls __पढ़ो_mostly = 20;
अटल पूर्णांक nv_ssthresh_eval_min_calls __पढ़ो_mostly = 30;
अटल पूर्णांक nv_stop_rtt_cnt __पढ़ो_mostly = 10;
अटल पूर्णांक nv_rtt_min_cnt __पढ़ो_mostly = 2;

module_param(nv_pad, पूर्णांक, 0644);
MODULE_PARM_DESC(nv_pad, "max queued packets allowed in network");
module_param(nv_reset_period, पूर्णांक, 0644);
MODULE_PARM_DESC(nv_reset_period, "nv_min_rtt reset period (secs)");
module_param(nv_min_cwnd, पूर्णांक, 0644);
MODULE_PARM_DESC(nv_min_cwnd, "NV will not decrease cwnd below this value"
		 " without losses");

/* TCP NV Parameters */
काष्ठा tcpnv अणु
	अचिन्हित दीर्घ nv_min_rtt_reset_jअगरfies;  /* when to चयन to
						  * nv_min_rtt_new */
	s8  cwnd_growth_factor;	/* Current cwnd growth factor,
				 * < 0 => less than 1 packet/RTT */
	u8  available8;
	u16 available16;
	u8  nv_allow_cwnd_growth:1, /* whether cwnd can grow */
		nv_reset:1,	    /* whether to reset values */
		nv_catchup:1;	    /* whether we are growing because
				     * of temporary cwnd decrease */
	u8  nv_eval_call_cnt;	/* call count since last eval */
	u8  nv_min_cwnd;	/* nv won't make a ca decision अगर cwnd is
				 * smaller than this. It may grow to handle
				 * TSO, LRO and पूर्णांकerrupt coalescence because
				 * with these a small cwnd cannot saturate
				 * the link. Note that this is dअगरferent from
				 * the file local nv_min_cwnd */
	u8  nv_rtt_cnt;		/* RTTs without making ca decision */;
	u32 nv_last_rtt;	/* last rtt */
	u32 nv_min_rtt;		/* active min rtt. Used to determine slope */
	u32 nv_min_rtt_new;	/* min rtt क्रम future use */
	u32 nv_base_rtt;        /* If non-zero it represents the threshold क्रम
				 * congestion */
	u32 nv_lower_bound_rtt; /* Used in conjunction with nv_base_rtt. It is
				 * set to 80% of nv_base_rtt. It helps reduce
				 * unfairness between flows */
	u32 nv_rtt_max_rate;	/* max rate seen during current RTT */
	u32 nv_rtt_start_seq;	/* current RTT ends when packet arrives
				 * acking beyond nv_rtt_start_seq */
	u32 nv_last_snd_una;	/* Previous value of tp->snd_una. It is
				 * used to determine bytes acked since last
				 * call to bictcp_acked */
	u32 nv_no_cong_cnt;	/* Consecutive no congestion decisions */
पूर्ण;

#घोषणा NV_INIT_RTT	  U32_MAX
#घोषणा NV_MIN_CWND	  4
#घोषणा NV_MIN_CWND_GROW  2
#घोषणा NV_TSO_CWND_BOUND 80

अटल अंतरभूत व्योम tcpnv_reset(काष्ठा tcpnv *ca, काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	ca->nv_reset = 0;
	ca->nv_no_cong_cnt = 0;
	ca->nv_rtt_cnt = 0;
	ca->nv_last_rtt = 0;
	ca->nv_rtt_max_rate = 0;
	ca->nv_rtt_start_seq = tp->snd_una;
	ca->nv_eval_call_cnt = 0;
	ca->nv_last_snd_una = tp->snd_una;
पूर्ण

अटल व्योम tcpnv_init(काष्ठा sock *sk)
अणु
	काष्ठा tcpnv *ca = inet_csk_ca(sk);
	पूर्णांक base_rtt;

	tcpnv_reset(ca, sk);

	/* See अगर base_rtt is available from socket_ops bpf program.
	 * It is meant to be used in environments, such as communication
	 * within a datacenter, where we have reasonable estimates of
	 * RTTs
	 */
	base_rtt = tcp_call_bpf(sk, BPF_SOCK_OPS_BASE_RTT, 0, शून्य);
	अगर (base_rtt > 0) अणु
		ca->nv_base_rtt = base_rtt;
		ca->nv_lower_bound_rtt = (base_rtt * 205) >> 8; /* 80% */
	पूर्ण अन्यथा अणु
		ca->nv_base_rtt = 0;
		ca->nv_lower_bound_rtt = 0;
	पूर्ण

	ca->nv_allow_cwnd_growth = 1;
	ca->nv_min_rtt_reset_jअगरfies = jअगरfies + 2 * HZ;
	ca->nv_min_rtt = NV_INIT_RTT;
	ca->nv_min_rtt_new = NV_INIT_RTT;
	ca->nv_min_cwnd = NV_MIN_CWND;
	ca->nv_catchup = 0;
	ca->cwnd_growth_factor = 0;
पूर्ण

/* If provided, apply upper (base_rtt) and lower (lower_bound_rtt)
 * bounds to RTT.
 */
अंतरभूत u32 nv_get_bounded_rtt(काष्ठा tcpnv *ca, u32 val)
अणु
	अगर (ca->nv_lower_bound_rtt > 0 && val < ca->nv_lower_bound_rtt)
		वापस ca->nv_lower_bound_rtt;
	अन्यथा अगर (ca->nv_base_rtt > 0 && val > ca->nv_base_rtt)
		वापस ca->nv_base_rtt;
	अन्यथा
		वापस val;
पूर्ण

अटल व्योम tcpnv_cong_aव्योम(काष्ठा sock *sk, u32 ack, u32 acked)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा tcpnv *ca = inet_csk_ca(sk);
	u32 cnt;

	अगर (!tcp_is_cwnd_limited(sk))
		वापस;

	/* Only grow cwnd अगर NV has not detected congestion */
	अगर (!ca->nv_allow_cwnd_growth)
		वापस;

	अगर (tcp_in_slow_start(tp)) अणु
		acked = tcp_slow_start(tp, acked);
		अगर (!acked)
			वापस;
	पूर्ण

	अगर (ca->cwnd_growth_factor < 0) अणु
		cnt = tp->snd_cwnd << -ca->cwnd_growth_factor;
		tcp_cong_aव्योम_ai(tp, cnt, acked);
	पूर्ण अन्यथा अणु
		cnt = max(4U, tp->snd_cwnd >> ca->cwnd_growth_factor);
		tcp_cong_aव्योम_ai(tp, cnt, acked);
	पूर्ण
पूर्ण

अटल u32 tcpnv_recalc_ssthresh(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);

	वापस max((tp->snd_cwnd * nv_loss_dec_factor) >> 10, 2U);
पूर्ण

अटल व्योम tcpnv_state(काष्ठा sock *sk, u8 new_state)
अणु
	काष्ठा tcpnv *ca = inet_csk_ca(sk);

	अगर (new_state == TCP_CA_Open && ca->nv_reset) अणु
		tcpnv_reset(ca, sk);
	पूर्ण अन्यथा अगर (new_state == TCP_CA_Loss || new_state == TCP_CA_CWR ||
		new_state == TCP_CA_Recovery) अणु
		ca->nv_reset = 1;
		ca->nv_allow_cwnd_growth = 0;
		अगर (new_state == TCP_CA_Loss) अणु
			/* Reset cwnd growth factor to Reno value */
			अगर (ca->cwnd_growth_factor > 0)
				ca->cwnd_growth_factor = 0;
			/* Decrease growth rate अगर allowed */
			अगर (nv_cwnd_growth_rate_neg > 0 &&
			    ca->cwnd_growth_factor > -8)
				ca->cwnd_growth_factor--;
		पूर्ण
	पूर्ण
पूर्ण

/* Do congestion aव्योमance calculations क्रम TCP-NV
 */
अटल व्योम tcpnv_acked(काष्ठा sock *sk, स्थिर काष्ठा ack_sample *sample)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा tcpnv *ca = inet_csk_ca(sk);
	अचिन्हित दीर्घ now = jअगरfies;
	u64 rate64;
	u32 rate, max_win, cwnd_by_slope;
	u32 avg_rtt;
	u32 bytes_acked = 0;

	/* Some calls are क्रम duplicates without समयtamps */
	अगर (sample->rtt_us < 0)
		वापस;

	/* If not in TCP_CA_Open or TCP_CA_Disorder states, skip. */
	अगर (icsk->icsk_ca_state != TCP_CA_Open &&
	    icsk->icsk_ca_state != TCP_CA_Disorder)
		वापस;

	/* Stop cwnd growth अगर we were in catch up mode */
	अगर (ca->nv_catchup && tp->snd_cwnd >= nv_min_cwnd) अणु
		ca->nv_catchup = 0;
		ca->nv_allow_cwnd_growth = 0;
	पूर्ण

	bytes_acked = tp->snd_una - ca->nv_last_snd_una;
	ca->nv_last_snd_una = tp->snd_una;

	अगर (sample->in_flight == 0)
		वापस;

	/* Calculate moving average of RTT */
	अगर (nv_rtt_factor > 0) अणु
		अगर (ca->nv_last_rtt > 0) अणु
			avg_rtt = (((u64)sample->rtt_us) * nv_rtt_factor +
				   ((u64)ca->nv_last_rtt)
				   * (256 - nv_rtt_factor)) >> 8;
		पूर्ण अन्यथा अणु
			avg_rtt = sample->rtt_us;
			ca->nv_min_rtt = avg_rtt << 1;
		पूर्ण
		ca->nv_last_rtt = avg_rtt;
	पूर्ण अन्यथा अणु
		avg_rtt = sample->rtt_us;
	पूर्ण

	/* rate in 100's bits per second */
	rate64 = ((u64)sample->in_flight) * 80000;
	करो_भाग(rate64, avg_rtt ?: 1);
	rate = (u32)rate64;

	/* Remember the maximum rate seen during this RTT
	 * Note: It may be more than one RTT. This function should be
	 *       called at least nv_dec_eval_min_calls बार.
	 */
	अगर (ca->nv_rtt_max_rate < rate)
		ca->nv_rtt_max_rate = rate;

	/* We have valid inक्रमmation, increment counter */
	अगर (ca->nv_eval_call_cnt < 255)
		ca->nv_eval_call_cnt++;

	/* Apply bounds to rtt. Only used to update min_rtt */
	avg_rtt = nv_get_bounded_rtt(ca, avg_rtt);

	/* update min rtt अगर necessary */
	अगर (avg_rtt < ca->nv_min_rtt)
		ca->nv_min_rtt = avg_rtt;

	/* update future min_rtt अगर necessary */
	अगर (avg_rtt < ca->nv_min_rtt_new)
		ca->nv_min_rtt_new = avg_rtt;

	/* nv_min_rtt is updated with the minimum (possibley averaged) rtt
	 * seen in the last sysctl_tcp_nv_reset_period seconds (i.e. a
	 * warm reset). This new nv_min_rtt will be जारीd to be updated
	 * and be used क्रम another sysctl_tcp_nv_reset_period seconds,
	 * when it will be updated again.
	 * In practice we पूर्णांकroduce some अक्रमomness, so the actual period used
	 * is chosen अक्रमomly from the range:
	 *   [sysctl_tcp_nv_reset_period*3/4, sysctl_tcp_nv_reset_period*5/4)
	 */
	अगर (समय_after_eq(now, ca->nv_min_rtt_reset_jअगरfies)) अणु
		अचिन्हित अक्षर अक्रम;

		ca->nv_min_rtt = ca->nv_min_rtt_new;
		ca->nv_min_rtt_new = NV_INIT_RTT;
		get_अक्रमom_bytes(&अक्रम, 1);
		ca->nv_min_rtt_reset_jअगरfies =
			now + ((nv_reset_period * (384 + अक्रम) * HZ) >> 9);
		/* Every so often we decrease ca->nv_min_cwnd in हाल previous
		 *  value is no दीर्घer accurate.
		 */
		ca->nv_min_cwnd = max(ca->nv_min_cwnd / 2, NV_MIN_CWND);
	पूर्ण

	/* Once per RTT check अगर we need to करो congestion aव्योमance */
	अगर (beक्रमe(ca->nv_rtt_start_seq, tp->snd_una)) अणु
		ca->nv_rtt_start_seq = tp->snd_nxt;
		अगर (ca->nv_rtt_cnt < 0xff)
			/* Increase counter क्रम RTTs without CA decision */
			ca->nv_rtt_cnt++;

		/* If this function is only called once within an RTT
		 * the cwnd is probably too small (in some हालs due to
		 * tso, lro or पूर्णांकerrupt coalescence), so we increase
		 * ca->nv_min_cwnd.
		 */
		अगर (ca->nv_eval_call_cnt == 1 &&
		    bytes_acked >= (ca->nv_min_cwnd - 1) * tp->mss_cache &&
		    ca->nv_min_cwnd < (NV_TSO_CWND_BOUND + 1)) अणु
			ca->nv_min_cwnd = min(ca->nv_min_cwnd
					      + NV_MIN_CWND_GROW,
					      NV_TSO_CWND_BOUND + 1);
			ca->nv_rtt_start_seq = tp->snd_nxt +
				ca->nv_min_cwnd * tp->mss_cache;
			ca->nv_eval_call_cnt = 0;
			ca->nv_allow_cwnd_growth = 1;
			वापस;
		पूर्ण

		/* Find the ideal cwnd क्रम current rate from slope
		 * slope = 80000.0 * mss / nv_min_rtt
		 * cwnd_by_slope = nv_rtt_max_rate / slope
		 */
		cwnd_by_slope = (u32)
			भाग64_u64(((u64)ca->nv_rtt_max_rate) * ca->nv_min_rtt,
				  80000ULL * tp->mss_cache);
		max_win = cwnd_by_slope + nv_pad;

		/* If cwnd > max_win, decrease cwnd
		 * अगर cwnd < max_win, grow cwnd
		 * अन्यथा leave the same
		 */
		अगर (tp->snd_cwnd > max_win) अणु
			/* there is congestion, check that it is ok
			 * to make a CA decision
			 * 1. We should have at least nv_dec_eval_min_calls
			 *    data poपूर्णांकs beक्रमe making a CA  decision
			 * 2. We only make a congesion decision after
			 *    nv_rtt_min_cnt RTTs
			 */
			अगर (ca->nv_rtt_cnt < nv_rtt_min_cnt) अणु
				वापस;
			पूर्ण अन्यथा अगर (tp->snd_ssthresh == TCP_INFINITE_SSTHRESH) अणु
				अगर (ca->nv_eval_call_cnt <
				    nv_ssthresh_eval_min_calls)
					वापस;
				/* otherwise we will decrease cwnd */
			पूर्ण अन्यथा अगर (ca->nv_eval_call_cnt <
				   nv_dec_eval_min_calls) अणु
				अगर (ca->nv_allow_cwnd_growth &&
				    ca->nv_rtt_cnt > nv_stop_rtt_cnt)
					ca->nv_allow_cwnd_growth = 0;
				वापस;
			पूर्ण

			/* We have enough data to determine we are congested */
			ca->nv_allow_cwnd_growth = 0;
			tp->snd_ssthresh =
				(nv_ssthresh_factor * max_win) >> 3;
			अगर (tp->snd_cwnd - max_win > 2) अणु
				/* gap > 2, we करो exponential cwnd decrease */
				पूर्णांक dec;

				dec = max(2U, ((tp->snd_cwnd - max_win) *
					       nv_cong_dec_mult) >> 7);
				tp->snd_cwnd -= dec;
			पूर्ण अन्यथा अगर (nv_cong_dec_mult > 0) अणु
				tp->snd_cwnd = max_win;
			पूर्ण
			अगर (ca->cwnd_growth_factor > 0)
				ca->cwnd_growth_factor = 0;
			ca->nv_no_cong_cnt = 0;
		पूर्ण अन्यथा अगर (tp->snd_cwnd <= max_win - nv_pad_buffer) अणु
			/* There is no congestion, grow cwnd अगर allowed*/
			अगर (ca->nv_eval_call_cnt < nv_inc_eval_min_calls)
				वापस;

			ca->nv_allow_cwnd_growth = 1;
			ca->nv_no_cong_cnt++;
			अगर (ca->cwnd_growth_factor < 0 &&
			    nv_cwnd_growth_rate_neg > 0 &&
			    ca->nv_no_cong_cnt > nv_cwnd_growth_rate_neg) अणु
				ca->cwnd_growth_factor++;
				ca->nv_no_cong_cnt = 0;
			पूर्ण अन्यथा अगर (ca->cwnd_growth_factor >= 0 &&
				   nv_cwnd_growth_rate_pos > 0 &&
				   ca->nv_no_cong_cnt >
				   nv_cwnd_growth_rate_pos) अणु
				ca->cwnd_growth_factor++;
				ca->nv_no_cong_cnt = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* cwnd is in-between, so करो nothing */
			वापस;
		पूर्ण

		/* update state */
		ca->nv_eval_call_cnt = 0;
		ca->nv_rtt_cnt = 0;
		ca->nv_rtt_max_rate = 0;

		/* Don't want to make cwnd < nv_min_cwnd
		 * (it wasn't beक्रमe, अगर it is now is because nv
		 *  decreased it).
		 */
		अगर (tp->snd_cwnd < nv_min_cwnd)
			tp->snd_cwnd = nv_min_cwnd;
	पूर्ण
पूर्ण

/* Extract info क्रम Tcp socket info provided via netlink */
अटल माप_प्रकार tcpnv_get_info(काष्ठा sock *sk, u32 ext, पूर्णांक *attr,
			     जोड़ tcp_cc_info *info)
अणु
	स्थिर काष्ठा tcpnv *ca = inet_csk_ca(sk);

	अगर (ext & (1 << (INET_DIAG_VEGASINFO - 1))) अणु
		info->vegas.tcpv_enabled = 1;
		info->vegas.tcpv_rttcnt = ca->nv_rtt_cnt;
		info->vegas.tcpv_rtt = ca->nv_last_rtt;
		info->vegas.tcpv_minrtt = ca->nv_min_rtt;

		*attr = INET_DIAG_VEGASINFO;
		वापस माप(काष्ठा tcpvegas_info);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा tcp_congestion_ops tcpnv __पढ़ो_mostly = अणु
	.init		= tcpnv_init,
	.ssthresh	= tcpnv_recalc_ssthresh,
	.cong_aव्योम	= tcpnv_cong_aव्योम,
	.set_state	= tcpnv_state,
	.unकरो_cwnd	= tcp_reno_unकरो_cwnd,
	.pkts_acked     = tcpnv_acked,
	.get_info	= tcpnv_get_info,

	.owner		= THIS_MODULE,
	.name		= "nv",
पूर्ण;

अटल पूर्णांक __init tcpnv_रेजिस्टर(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा tcpnv) > ICSK_CA_PRIV_SIZE);

	वापस tcp_रेजिस्टर_congestion_control(&tcpnv);
पूर्ण

अटल व्योम __निकास tcpnv_unरेजिस्टर(व्योम)
अणु
	tcp_unरेजिस्टर_congestion_control(&tcpnv);
पूर्ण

module_init(tcpnv_रेजिस्टर);
module_निकास(tcpnv_unरेजिस्टर);

MODULE_AUTHOR("Lawrence Brakmo");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TCP NV");
MODULE_VERSION("1.0");
