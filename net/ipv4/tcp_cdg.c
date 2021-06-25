<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CAIA Delay-Gradient (CDG) congestion control
 *
 * This implementation is based on the paper:
 *   D.A. Hayes and G. Armitage. "Revisiting TCP congestion control using
 *   delay gradients." In IFIP Networking, pages 328-341. Springer, 2011.
 *
 * Scavenger traffic (Less-than-Best-Efक्रमt) should disable coexistence
 * heuristics using parameters use_shaकरोw=0 and use_ineff=0.
 *
 * Parameters winकरोw, backoff_beta, and backoff_factor are crucial क्रम
 * throughput and delay. Future work is needed to determine better शेषs,
 * and to provide guidelines क्रम use in dअगरferent environments/contexts.
 *
 * Except क्रम winकरोw, knobs are configured via /sys/module/tcp_cdg/parameters/.
 * Parameter winकरोw is only configurable when loading tcp_cdg as a module.
 *
 * Notable dअगरferences from paper/FreeBSD:
 *   o Using Hybrid Slow start and Proportional Rate Reduction.
 *   o Add toggle क्रम shaकरोw winकरोw mechanism. Suggested by David Hayes.
 *   o Add toggle क्रम non-congestion loss tolerance.
 *   o Scaling parameter G is changed to a backoff factor;
 *     conversion is given by: backoff_factor = 1000/(G * winकरोw).
 *   o Limit shaकरोw winकरोw to 2 * cwnd, or to cwnd when application limited.
 *   o More accurate e^-x.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/घड़ी.h>

#समावेश <net/tcp.h>

#घोषणा HYSTART_ACK_TRAIN	1
#घोषणा HYSTART_DELAY		2

अटल पूर्णांक winकरोw __पढ़ो_mostly = 8;
अटल अचिन्हित पूर्णांक backoff_beta __पढ़ो_mostly = 0.7071 * 1024; /* वर्ग_मूल 0.5 */
अटल अचिन्हित पूर्णांक backoff_factor __पढ़ो_mostly = 42;
अटल अचिन्हित पूर्णांक hystart_detect __पढ़ो_mostly = 3;
अटल अचिन्हित पूर्णांक use_ineff __पढ़ो_mostly = 5;
अटल bool use_shaकरोw __पढ़ो_mostly = true;
अटल bool use_tolerance __पढ़ो_mostly;

module_param(winकरोw, पूर्णांक, 0444);
MODULE_PARM_DESC(winकरोw, "gradient window size (power of two <= 256)");
module_param(backoff_beta, uपूर्णांक, 0644);
MODULE_PARM_DESC(backoff_beta, "backoff beta (0-1024)");
module_param(backoff_factor, uपूर्णांक, 0644);
MODULE_PARM_DESC(backoff_factor, "backoff probability scale factor");
module_param(hystart_detect, uपूर्णांक, 0644);
MODULE_PARM_DESC(hystart_detect, "use Hybrid Slow start "
		 "(0: disabled, 1: ACK train, 2: delay threshold, 3: both)");
module_param(use_ineff, uपूर्णांक, 0644);
MODULE_PARM_DESC(use_ineff, "use ineffectual backoff detection (threshold)");
module_param(use_shaकरोw, bool, 0644);
MODULE_PARM_DESC(use_shaकरोw, "use shadow window heuristic");
module_param(use_tolerance, bool, 0644);
MODULE_PARM_DESC(use_tolerance, "use loss tolerance heuristic");

काष्ठा cdg_minmax अणु
	जोड़ अणु
		काष्ठा अणु
			s32 min;
			s32 max;
		पूर्ण;
		u64 v64;
	पूर्ण;
पूर्ण;

क्रमागत cdg_state अणु
	CDG_UNKNOWN = 0,
	CDG_NONFULL = 1,
	CDG_FULL    = 2,
	CDG_BACKOFF = 3,
पूर्ण;

काष्ठा cdg अणु
	काष्ठा cdg_minmax rtt;
	काष्ठा cdg_minmax rtt_prev;
	काष्ठा cdg_minmax *gradients;
	काष्ठा cdg_minmax gsum;
	bool gfilled;
	u8  tail;
	u8  state;
	u8  delack;
	u32 rtt_seq;
	u32 shaकरोw_wnd;
	u16 backoff_cnt;
	u16 sample_cnt;
	s32 delay_min;
	u32 last_ack;
	u32 round_start;
पूर्ण;

/**
 * nexp_u32 - negative base-e exponential
 * @ux: x in units of micro
 *
 * Returns exp(ux * -1e-6) * U32_MAX.
 */
अटल u32 __pure nexp_u32(u32 ux)
अणु
	अटल स्थिर u16 v[] = अणु
		/* exp(-x)*65536-1 क्रम x = 0, 0.000256, 0.000512, ... */
		65535,
		65518, 65501, 65468, 65401, 65267, 65001, 64470, 63422,
		61378, 57484, 50423, 38795, 22965, 8047,  987,   14,
	पूर्ण;
	u32 msb = ux >> 8;
	u32 res;
	पूर्णांक i;

	/* Cut off when ux >= 2^24 (actual result is <= 222/U32_MAX). */
	अगर (msb > U16_MAX)
		वापस 0;

	/* Scale first eight bits linearly: */
	res = U32_MAX - (ux & 0xff) * (U32_MAX / 1000000);

	/* Obtain e^(x + y + ...) by computing e^x * e^y * ...: */
	क्रम (i = 1; msb; i++, msb >>= 1) अणु
		u32 y = v[i & -(msb & 1)] + U32_C(1);

		res = ((u64)res * y) >> 16;
	पूर्ण

	वापस res;
पूर्ण

/* Based on the HyStart algorithm (by Ha et al.) that is implemented in
 * tcp_cubic. Dअगरferences/experimental changes:
 *   o Using Hayes' delayed ACK filter.
 *   o Using a usec घड़ी क्रम the ACK train.
 *   o Reset ACK train when application limited.
 *   o Invoked at any cwnd (i.e. also when cwnd < 16).
 *   o Invoked only when cwnd < ssthresh (i.e. not when cwnd == ssthresh).
 */
अटल व्योम tcp_cdg_hystart_update(काष्ठा sock *sk)
अणु
	काष्ठा cdg *ca = inet_csk_ca(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	ca->delay_min = min_not_zero(ca->delay_min, ca->rtt.min);
	अगर (ca->delay_min == 0)
		वापस;

	अगर (hystart_detect & HYSTART_ACK_TRAIN) अणु
		u32 now_us = tp->tcp_mstamp;

		अगर (ca->last_ack == 0 || !tcp_is_cwnd_limited(sk)) अणु
			ca->last_ack = now_us;
			ca->round_start = now_us;
		पूर्ण अन्यथा अगर (beक्रमe(now_us, ca->last_ack + 3000)) अणु
			u32 base_owd = max(ca->delay_min / 2U, 125U);

			ca->last_ack = now_us;
			अगर (after(now_us, ca->round_start + base_owd)) अणु
				NET_INC_STATS(sock_net(sk),
					      LINUX_MIB_TCPHYSTARTTRAINDETECT);
				NET_ADD_STATS(sock_net(sk),
					      LINUX_MIB_TCPHYSTARTTRAINCWND,
					      tp->snd_cwnd);
				tp->snd_ssthresh = tp->snd_cwnd;
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (hystart_detect & HYSTART_DELAY) अणु
		अगर (ca->sample_cnt < 8) अणु
			ca->sample_cnt++;
		पूर्ण अन्यथा अणु
			s32 thresh = max(ca->delay_min + ca->delay_min / 8U,
					 125U);

			अगर (ca->rtt.min > thresh) अणु
				NET_INC_STATS(sock_net(sk),
					      LINUX_MIB_TCPHYSTARTDELAYDETECT);
				NET_ADD_STATS(sock_net(sk),
					      LINUX_MIB_TCPHYSTARTDELAYCWND,
					      tp->snd_cwnd);
				tp->snd_ssthresh = tp->snd_cwnd;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल s32 tcp_cdg_grad(काष्ठा cdg *ca)
अणु
	s32 gmin = ca->rtt.min - ca->rtt_prev.min;
	s32 gmax = ca->rtt.max - ca->rtt_prev.max;
	s32 grad;

	अगर (ca->gradients) अणु
		ca->gsum.min += gmin - ca->gradients[ca->tail].min;
		ca->gsum.max += gmax - ca->gradients[ca->tail].max;
		ca->gradients[ca->tail].min = gmin;
		ca->gradients[ca->tail].max = gmax;
		ca->tail = (ca->tail + 1) & (winकरोw - 1);
		gmin = ca->gsum.min;
		gmax = ca->gsum.max;
	पूर्ण

	/* We keep sums to ignore gradients during cwnd reductions;
	 * the paper's smoothed gradients otherwise simplअगरy to:
	 * (rtt_latest - rtt_oldest) / winकरोw.
	 *
	 * We also drop भागision by winकरोw here.
	 */
	grad = gmin > 0 ? gmin : gmax;

	/* Extrapolate missing values in gradient winकरोw: */
	अगर (!ca->gfilled) अणु
		अगर (!ca->gradients && winकरोw > 1)
			grad *= winकरोw; /* Memory allocation failed. */
		अन्यथा अगर (ca->tail == 0)
			ca->gfilled = true;
		अन्यथा
			grad = (grad * winकरोw) / (पूर्णांक)ca->tail;
	पूर्ण

	/* Backoff was effectual: */
	अगर (gmin <= -32 || gmax <= -32)
		ca->backoff_cnt = 0;

	अगर (use_tolerance) अणु
		/* Reduce small variations to zero: */
		gmin = DIV_ROUND_CLOSEST(gmin, 64);
		gmax = DIV_ROUND_CLOSEST(gmax, 64);

		अगर (gmin > 0 && gmax <= 0)
			ca->state = CDG_FULL;
		अन्यथा अगर ((gmin > 0 && gmax > 0) || gmax < 0)
			ca->state = CDG_NONFULL;
	पूर्ण
	वापस grad;
पूर्ण

अटल bool tcp_cdg_backoff(काष्ठा sock *sk, u32 grad)
अणु
	काष्ठा cdg *ca = inet_csk_ca(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (pअक्रमom_u32() <= nexp_u32(grad * backoff_factor))
		वापस false;

	अगर (use_ineff) अणु
		ca->backoff_cnt++;
		अगर (ca->backoff_cnt > use_ineff)
			वापस false;
	पूर्ण

	ca->shaकरोw_wnd = max(ca->shaकरोw_wnd, tp->snd_cwnd);
	ca->state = CDG_BACKOFF;
	tcp_enter_cwr(sk);
	वापस true;
पूर्ण

/* Not called in CWR or Recovery state. */
अटल व्योम tcp_cdg_cong_aव्योम(काष्ठा sock *sk, u32 ack, u32 acked)
अणु
	काष्ठा cdg *ca = inet_csk_ca(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 prior_snd_cwnd;
	u32 incr;

	अगर (tcp_in_slow_start(tp) && hystart_detect)
		tcp_cdg_hystart_update(sk);

	अगर (after(ack, ca->rtt_seq) && ca->rtt.v64) अणु
		s32 grad = 0;

		अगर (ca->rtt_prev.v64)
			grad = tcp_cdg_grad(ca);
		ca->rtt_seq = tp->snd_nxt;
		ca->rtt_prev = ca->rtt;
		ca->rtt.v64 = 0;
		ca->last_ack = 0;
		ca->sample_cnt = 0;

		अगर (grad > 0 && tcp_cdg_backoff(sk, grad))
			वापस;
	पूर्ण

	अगर (!tcp_is_cwnd_limited(sk)) अणु
		ca->shaकरोw_wnd = min(ca->shaकरोw_wnd, tp->snd_cwnd);
		वापस;
	पूर्ण

	prior_snd_cwnd = tp->snd_cwnd;
	tcp_reno_cong_aव्योम(sk, ack, acked);

	incr = tp->snd_cwnd - prior_snd_cwnd;
	ca->shaकरोw_wnd = max(ca->shaकरोw_wnd, ca->shaकरोw_wnd + incr);
पूर्ण

अटल व्योम tcp_cdg_acked(काष्ठा sock *sk, स्थिर काष्ठा ack_sample *sample)
अणु
	काष्ठा cdg *ca = inet_csk_ca(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (sample->rtt_us <= 0)
		वापस;

	/* A heuristic क्रम filtering delayed ACKs, adapted from:
	 * D.A. Hayes. "Timing enhancements to the FreeBSD kernel to support
	 * delay and rate based TCP mechanisms." TR 100219A. CAIA, 2010.
	 */
	अगर (tp->sacked_out == 0) अणु
		अगर (sample->pkts_acked == 1 && ca->delack) अणु
			/* A delayed ACK is only used क्रम the minimum अगर it is
			 * provenly lower than an existing non-zero minimum.
			 */
			ca->rtt.min = min(ca->rtt.min, sample->rtt_us);
			ca->delack--;
			वापस;
		पूर्ण अन्यथा अगर (sample->pkts_acked > 1 && ca->delack < 5) अणु
			ca->delack++;
		पूर्ण
	पूर्ण

	ca->rtt.min = min_not_zero(ca->rtt.min, sample->rtt_us);
	ca->rtt.max = max(ca->rtt.max, sample->rtt_us);
पूर्ण

अटल u32 tcp_cdg_ssthresh(काष्ठा sock *sk)
अणु
	काष्ठा cdg *ca = inet_csk_ca(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (ca->state == CDG_BACKOFF)
		वापस max(2U, (tp->snd_cwnd * min(1024U, backoff_beta)) >> 10);

	अगर (ca->state == CDG_NONFULL && use_tolerance)
		वापस tp->snd_cwnd;

	ca->shaकरोw_wnd = min(ca->shaकरोw_wnd >> 1, tp->snd_cwnd);
	अगर (use_shaकरोw)
		वापस max3(2U, ca->shaकरोw_wnd, tp->snd_cwnd >> 1);
	वापस max(2U, tp->snd_cwnd >> 1);
पूर्ण

अटल व्योम tcp_cdg_cwnd_event(काष्ठा sock *sk, स्थिर क्रमागत tcp_ca_event ev)
अणु
	काष्ठा cdg *ca = inet_csk_ca(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा cdg_minmax *gradients;

	चयन (ev) अणु
	हाल CA_EVENT_CWND_RESTART:
		gradients = ca->gradients;
		अगर (gradients)
			स_रखो(gradients, 0, winकरोw * माप(gradients[0]));
		स_रखो(ca, 0, माप(*ca));

		ca->gradients = gradients;
		ca->rtt_seq = tp->snd_nxt;
		ca->shaकरोw_wnd = tp->snd_cwnd;
		अवरोध;
	हाल CA_EVENT_COMPLETE_CWR:
		ca->state = CDG_UNKNOWN;
		ca->rtt_seq = tp->snd_nxt;
		ca->rtt_prev = ca->rtt;
		ca->rtt.v64 = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम tcp_cdg_init(काष्ठा sock *sk)
अणु
	काष्ठा cdg *ca = inet_csk_ca(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	/* We silently fall back to winकरोw = 1 अगर allocation fails. */
	अगर (winकरोw > 1)
		ca->gradients = kसुस्मृति(winकरोw, माप(ca->gradients[0]),
					GFP_NOWAIT | __GFP_NOWARN);
	ca->rtt_seq = tp->snd_nxt;
	ca->shaकरोw_wnd = tp->snd_cwnd;
पूर्ण

अटल व्योम tcp_cdg_release(काष्ठा sock *sk)
अणु
	काष्ठा cdg *ca = inet_csk_ca(sk);

	kमुक्त(ca->gradients);
पूर्ण

अटल काष्ठा tcp_congestion_ops tcp_cdg __पढ़ो_mostly = अणु
	.cong_aव्योम = tcp_cdg_cong_aव्योम,
	.cwnd_event = tcp_cdg_cwnd_event,
	.pkts_acked = tcp_cdg_acked,
	.unकरो_cwnd = tcp_reno_unकरो_cwnd,
	.ssthresh = tcp_cdg_ssthresh,
	.release = tcp_cdg_release,
	.init = tcp_cdg_init,
	.owner = THIS_MODULE,
	.name = "cdg",
पूर्ण;

अटल पूर्णांक __init tcp_cdg_रेजिस्टर(व्योम)
अणु
	अगर (backoff_beta > 1024 || winकरोw < 1 || winकरोw > 256)
		वापस -दुस्फल;
	अगर (!is_घातer_of_2(winकरोw))
		वापस -EINVAL;

	BUILD_BUG_ON(माप(काष्ठा cdg) > ICSK_CA_PRIV_SIZE);
	tcp_रेजिस्टर_congestion_control(&tcp_cdg);
	वापस 0;
पूर्ण

अटल व्योम __निकास tcp_cdg_unरेजिस्टर(व्योम)
अणु
	tcp_unरेजिस्टर_congestion_control(&tcp_cdg);
पूर्ण

module_init(tcp_cdg_रेजिस्टर);
module_निकास(tcp_cdg_unरेजिस्टर);
MODULE_AUTHOR("Kenneth Klette Jonassen");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TCP CDG");
