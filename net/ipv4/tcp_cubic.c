<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TCP CUBIC: Binary Increase Congestion control क्रम TCP v2.3
 * Home page:
 *      http://netsrv.csc.ncsu.edu/twiki/bin/view/Main/BIC
 * This is from the implementation of CUBIC TCP in
 * Sangtae Ha, Injong Rhee and Lisong Xu,
 *  "CUBIC: A New TCP-Friendly High-Speed TCP Variant"
 *  in ACM SIGOPS Operating System Review, July 2008.
 * Available from:
 *  http://netsrv.csc.ncsu.edu/export/cubic_a_new_tcp_2008.pdf
 *
 * CUBIC पूर्णांकegrates a new slow start algorithm, called HyStart.
 * The details of HyStart are presented in
 *  Sangtae Ha and Injong Rhee,
 *  "Taming the Elephants: New TCP Slow Start", NCSU TechReport 2008.
 * Available from:
 *  http://netsrv.csc.ncsu.edu/export/hystart_techreport_2008.pdf
 *
 * All testing results are available from:
 * http://netsrv.csc.ncsu.edu/wiki/index.php/TCP_Testing
 *
 * Unless CUBIC is enabled and congestion winकरोw is large
 * this behaves the same as the original Reno.
 */

#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/math64.h>
#समावेश <net/tcp.h>

#घोषणा BICTCP_BETA_SCALE    1024	/* Scale factor beta calculation
					 * max_cwnd = snd_cwnd * beta
					 */
#घोषणा	BICTCP_HZ		10	/* BIC HZ 2^10 = 1024 */

/* Two methods of hybrid slow start */
#घोषणा HYSTART_ACK_TRAIN	0x1
#घोषणा HYSTART_DELAY		0x2

/* Number of delay samples क्रम detecting the increase of delay */
#घोषणा HYSTART_MIN_SAMPLES	8
#घोषणा HYSTART_DELAY_MIN	(4000U)	/* 4 ms */
#घोषणा HYSTART_DELAY_MAX	(16000U)	/* 16 ms */
#घोषणा HYSTART_DELAY_THRESH(x)	clamp(x, HYSTART_DELAY_MIN, HYSTART_DELAY_MAX)

अटल पूर्णांक fast_convergence __पढ़ो_mostly = 1;
अटल पूर्णांक beta __पढ़ो_mostly = 717;	/* = 717/1024 (BICTCP_BETA_SCALE) */
अटल पूर्णांक initial_ssthresh __पढ़ो_mostly;
अटल पूर्णांक bic_scale __पढ़ो_mostly = 41;
अटल पूर्णांक tcp_मित्रliness __पढ़ो_mostly = 1;

अटल पूर्णांक hystart __पढ़ो_mostly = 1;
अटल पूर्णांक hystart_detect __पढ़ो_mostly = HYSTART_ACK_TRAIN | HYSTART_DELAY;
अटल पूर्णांक hystart_low_winकरोw __पढ़ो_mostly = 16;
अटल पूर्णांक hystart_ack_delta_us __पढ़ो_mostly = 2000;

अटल u32 cube_rtt_scale __पढ़ो_mostly;
अटल u32 beta_scale __पढ़ो_mostly;
अटल u64 cube_factor __पढ़ो_mostly;

/* Note parameters that are used क्रम precomputing scale factors are पढ़ो-only */
module_param(fast_convergence, पूर्णांक, 0644);
MODULE_PARM_DESC(fast_convergence, "turn on/off fast convergence");
module_param(beta, पूर्णांक, 0644);
MODULE_PARM_DESC(beta, "beta for multiplicative increase");
module_param(initial_ssthresh, पूर्णांक, 0644);
MODULE_PARM_DESC(initial_ssthresh, "initial value of slow start threshold");
module_param(bic_scale, पूर्णांक, 0444);
MODULE_PARM_DESC(bic_scale, "scale (scaled by 1024) value for bic function (bic_scale/1024)");
module_param(tcp_मित्रliness, पूर्णांक, 0644);
MODULE_PARM_DESC(tcp_मित्रliness, "turn on/off tcp friendliness");
module_param(hystart, पूर्णांक, 0644);
MODULE_PARM_DESC(hystart, "turn on/off hybrid slow start algorithm");
module_param(hystart_detect, पूर्णांक, 0644);
MODULE_PARM_DESC(hystart_detect, "hybrid slow start detection mechanisms"
		 " 1: packet-train 2: delay 3: both packet-train and delay");
module_param(hystart_low_winकरोw, पूर्णांक, 0644);
MODULE_PARM_DESC(hystart_low_winकरोw, "lower bound cwnd for hybrid slow start");
module_param(hystart_ack_delta_us, पूर्णांक, 0644);
MODULE_PARM_DESC(hystart_ack_delta_us, "spacing between ack's indicating train (usecs)");

/* BIC TCP Parameters */
काष्ठा bictcp अणु
	u32	cnt;		/* increase cwnd by 1 after ACKs */
	u32	last_max_cwnd;	/* last maximum snd_cwnd */
	u32	last_cwnd;	/* the last snd_cwnd */
	u32	last_समय;	/* समय when updated last_cwnd */
	u32	bic_origin_poपूर्णांक;/* origin poपूर्णांक of bic function */
	u32	bic_K;		/* समय to origin poपूर्णांक
				   from the beginning of the current epoch */
	u32	delay_min;	/* min delay (usec) */
	u32	epoch_start;	/* beginning of an epoch */
	u32	ack_cnt;	/* number of acks */
	u32	tcp_cwnd;	/* estimated tcp cwnd */
	u16	unused;
	u8	sample_cnt;	/* number of samples to decide curr_rtt */
	u8	found;		/* the निकास poपूर्णांक is found? */
	u32	round_start;	/* beginning of each round */
	u32	end_seq;	/* end_seq of the round */
	u32	last_ack;	/* last समय when the ACK spacing is बंद */
	u32	curr_rtt;	/* the minimum rtt of current round */
पूर्ण;

अटल अंतरभूत व्योम bictcp_reset(काष्ठा bictcp *ca)
अणु
	स_रखो(ca, 0, दुरत्व(काष्ठा bictcp, unused));
	ca->found = 0;
पूर्ण

अटल अंतरभूत u32 bictcp_घड़ी_us(स्थिर काष्ठा sock *sk)
अणु
	वापस tcp_sk(sk)->tcp_mstamp;
पूर्ण

अटल अंतरभूत व्योम bictcp_hystart_reset(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bictcp *ca = inet_csk_ca(sk);

	ca->round_start = ca->last_ack = bictcp_घड़ी_us(sk);
	ca->end_seq = tp->snd_nxt;
	ca->curr_rtt = ~0U;
	ca->sample_cnt = 0;
पूर्ण

अटल व्योम cubictcp_init(काष्ठा sock *sk)
अणु
	काष्ठा bictcp *ca = inet_csk_ca(sk);

	bictcp_reset(ca);

	अगर (hystart)
		bictcp_hystart_reset(sk);

	अगर (!hystart && initial_ssthresh)
		tcp_sk(sk)->snd_ssthresh = initial_ssthresh;
पूर्ण

अटल व्योम cubictcp_cwnd_event(काष्ठा sock *sk, क्रमागत tcp_ca_event event)
अणु
	अगर (event == CA_EVENT_TX_START) अणु
		काष्ठा bictcp *ca = inet_csk_ca(sk);
		u32 now = tcp_jअगरfies32;
		s32 delta;

		delta = now - tcp_sk(sk)->lsndसमय;

		/* We were application limited (idle) क्रम a जबतक.
		 * Shअगरt epoch_start to keep cwnd growth to cubic curve.
		 */
		अगर (ca->epoch_start && delta > 0) अणु
			ca->epoch_start += delta;
			अगर (after(ca->epoch_start, now))
				ca->epoch_start = now;
		पूर्ण
		वापस;
	पूर्ण
पूर्ण

/* calculate the cubic root of x using a table lookup followed by one
 * Newton-Raphson iteration.
 * Avg err ~= 0.195%
 */
अटल u32 cubic_root(u64 a)
अणु
	u32 x, b, shअगरt;
	/*
	 * cbrt(x) MSB values क्रम x MSB values in [0..63].
	 * Precomputed then refined by hand - Willy Tarreau
	 *
	 * For x in [0..63],
	 *   v = cbrt(x << 18) - 1
	 *   cbrt(x) = (v[x] + 10) >> 6
	 */
	अटल स्थिर u8 v[] = अणु
		/* 0x00 */    0,   54,   54,   54,  118,  118,  118,  118,
		/* 0x08 */  123,  129,  134,  138,  143,  147,  151,  156,
		/* 0x10 */  157,  161,  164,  168,  170,  173,  176,  179,
		/* 0x18 */  181,  185,  187,  190,  192,  194,  197,  199,
		/* 0x20 */  200,  202,  204,  206,  209,  211,  213,  215,
		/* 0x28 */  217,  219,  221,  222,  224,  225,  227,  229,
		/* 0x30 */  231,  232,  234,  236,  237,  239,  240,  242,
		/* 0x38 */  244,  245,  246,  248,  250,  251,  252,  254,
	पूर्ण;

	b = fls64(a);
	अगर (b < 7) अणु
		/* a in [0..63] */
		वापस ((u32)v[(u32)a] + 35) >> 6;
	पूर्ण

	b = ((b * 84) >> 8) - 1;
	shअगरt = (a >> (b * 3));

	x = ((u32)(((u32)v[shअगरt] + 10) << b)) >> 6;

	/*
	 * Newton-Raphson iteration
	 *                         2
	 * x    = ( 2 * x  +  a / x  ) / 3
	 *  k+1          k         k
	 */
	x = (2 * x + (u32)भाग64_u64(a, (u64)x * (u64)(x - 1)));
	x = ((x * 341) >> 10);
	वापस x;
पूर्ण

/*
 * Compute congestion winकरोw to use.
 */
अटल अंतरभूत व्योम bictcp_update(काष्ठा bictcp *ca, u32 cwnd, u32 acked)
अणु
	u32 delta, bic_target, max_cnt;
	u64 offs, t;

	ca->ack_cnt += acked;	/* count the number of ACKed packets */

	अगर (ca->last_cwnd == cwnd &&
	    (s32)(tcp_jअगरfies32 - ca->last_समय) <= HZ / 32)
		वापस;

	/* The CUBIC function can update ca->cnt at most once per jअगरfy.
	 * On all cwnd reduction events, ca->epoch_start is set to 0,
	 * which will क्रमce a recalculation of ca->cnt.
	 */
	अगर (ca->epoch_start && tcp_jअगरfies32 == ca->last_समय)
		जाओ tcp_मित्रliness;

	ca->last_cwnd = cwnd;
	ca->last_समय = tcp_jअगरfies32;

	अगर (ca->epoch_start == 0) अणु
		ca->epoch_start = tcp_jअगरfies32;	/* record beginning */
		ca->ack_cnt = acked;			/* start counting */
		ca->tcp_cwnd = cwnd;			/* syn with cubic */

		अगर (ca->last_max_cwnd <= cwnd) अणु
			ca->bic_K = 0;
			ca->bic_origin_poपूर्णांक = cwnd;
		पूर्ण अन्यथा अणु
			/* Compute new K based on
			 * (wmax-cwnd) * (srtt>>3 / HZ) / c * 2^(3*bictcp_HZ)
			 */
			ca->bic_K = cubic_root(cube_factor
					       * (ca->last_max_cwnd - cwnd));
			ca->bic_origin_poपूर्णांक = ca->last_max_cwnd;
		पूर्ण
	पूर्ण

	/* cubic function - calc*/
	/* calculate c * समय^3 / rtt,
	 *  जबतक considering overflow in calculation of समय^3
	 * (so समय^3 is करोne by using 64 bit)
	 * and without the support of भागision of 64bit numbers
	 * (so all भागisions are करोne by using 32 bit)
	 *  also NOTE the unit of those veriables
	 *	  समय  = (t - K) / 2^bictcp_HZ
	 *	  c = bic_scale >> 10
	 * rtt  = (srtt >> 3) / HZ
	 * !!! The following code करोes not have overflow problems,
	 * अगर the cwnd < 1 million packets !!!
	 */

	t = (s32)(tcp_jअगरfies32 - ca->epoch_start);
	t += usecs_to_jअगरfies(ca->delay_min);
	/* change the unit from HZ to bictcp_HZ */
	t <<= BICTCP_HZ;
	करो_भाग(t, HZ);

	अगर (t < ca->bic_K)		/* t - K */
		offs = ca->bic_K - t;
	अन्यथा
		offs = t - ca->bic_K;

	/* c/rtt * (t-K)^3 */
	delta = (cube_rtt_scale * offs * offs * offs) >> (10+3*BICTCP_HZ);
	अगर (t < ca->bic_K)                            /* below origin*/
		bic_target = ca->bic_origin_poपूर्णांक - delta;
	अन्यथा                                          /* above origin*/
		bic_target = ca->bic_origin_poपूर्णांक + delta;

	/* cubic function - calc bictcp_cnt*/
	अगर (bic_target > cwnd) अणु
		ca->cnt = cwnd / (bic_target - cwnd);
	पूर्ण अन्यथा अणु
		ca->cnt = 100 * cwnd;              /* very small increment*/
	पूर्ण

	/*
	 * The initial growth of cubic function may be too conservative
	 * when the available bandwidth is still unknown.
	 */
	अगर (ca->last_max_cwnd == 0 && ca->cnt > 20)
		ca->cnt = 20;	/* increase cwnd 5% per RTT */

tcp_मित्रliness:
	/* TCP Friendly */
	अगर (tcp_मित्रliness) अणु
		u32 scale = beta_scale;

		delta = (cwnd * scale) >> 3;
		जबतक (ca->ack_cnt > delta) अणु		/* update tcp cwnd */
			ca->ack_cnt -= delta;
			ca->tcp_cwnd++;
		पूर्ण

		अगर (ca->tcp_cwnd > cwnd) अणु	/* अगर bic is slower than tcp */
			delta = ca->tcp_cwnd - cwnd;
			max_cnt = cwnd / delta;
			अगर (ca->cnt > max_cnt)
				ca->cnt = max_cnt;
		पूर्ण
	पूर्ण

	/* The maximum rate of cwnd increase CUBIC allows is 1 packet per
	 * 2 packets ACKed, meaning cwnd grows at 1.5x per RTT.
	 */
	ca->cnt = max(ca->cnt, 2U);
पूर्ण

अटल व्योम cubictcp_cong_aव्योम(काष्ठा sock *sk, u32 ack, u32 acked)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bictcp *ca = inet_csk_ca(sk);

	अगर (!tcp_is_cwnd_limited(sk))
		वापस;

	अगर (tcp_in_slow_start(tp)) अणु
		अगर (hystart && after(ack, ca->end_seq))
			bictcp_hystart_reset(sk);
		acked = tcp_slow_start(tp, acked);
		अगर (!acked)
			वापस;
	पूर्ण
	bictcp_update(ca, tp->snd_cwnd, acked);
	tcp_cong_aव्योम_ai(tp, ca->cnt, acked);
पूर्ण

अटल u32 cubictcp_recalc_ssthresh(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bictcp *ca = inet_csk_ca(sk);

	ca->epoch_start = 0;	/* end of epoch */

	/* Wmax and fast convergence */
	अगर (tp->snd_cwnd < ca->last_max_cwnd && fast_convergence)
		ca->last_max_cwnd = (tp->snd_cwnd * (BICTCP_BETA_SCALE + beta))
			/ (2 * BICTCP_BETA_SCALE);
	अन्यथा
		ca->last_max_cwnd = tp->snd_cwnd;

	वापस max((tp->snd_cwnd * beta) / BICTCP_BETA_SCALE, 2U);
पूर्ण

अटल व्योम cubictcp_state(काष्ठा sock *sk, u8 new_state)
अणु
	अगर (new_state == TCP_CA_Loss) अणु
		bictcp_reset(inet_csk_ca(sk));
		bictcp_hystart_reset(sk);
	पूर्ण
पूर्ण

/* Account क्रम TSO/GRO delays.
 * Otherwise लघु RTT flows could get too small ssthresh, since during
 * slow start we begin with small TSO packets and ca->delay_min would
 * not account क्रम दीर्घ aggregation delay when TSO packets get bigger.
 * Ideally even with a very small RTT we would like to have at least one
 * TSO packet being sent and received by GRO, and another one in qdisc layer.
 * We apply another 100% factor because @rate is द्विगुनd at this poपूर्णांक.
 * We cap the cushion to 1ms.
 */
अटल u32 hystart_ack_delay(काष्ठा sock *sk)
अणु
	अचिन्हित दीर्घ rate;

	rate = READ_ONCE(sk->sk_pacing_rate);
	अगर (!rate)
		वापस 0;
	वापस min_t(u64, USEC_PER_MSEC,
		     भाग64_ul((u64)GSO_MAX_SIZE * 4 * USEC_PER_SEC, rate));
पूर्ण

अटल व्योम hystart_update(काष्ठा sock *sk, u32 delay)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bictcp *ca = inet_csk_ca(sk);
	u32 threshold;

	अगर (hystart_detect & HYSTART_ACK_TRAIN) अणु
		u32 now = bictcp_घड़ी_us(sk);

		/* first detection parameter - ack-train detection */
		अगर ((s32)(now - ca->last_ack) <= hystart_ack_delta_us) अणु
			ca->last_ack = now;

			threshold = ca->delay_min + hystart_ack_delay(sk);

			/* Hystart ack train triggers अगर we get ack past
			 * ca->delay_min/2.
			 * Pacing might have delayed packets up to RTT/2
			 * during slow start.
			 */
			अगर (sk->sk_pacing_status == SK_PACING_NONE)
				threshold >>= 1;

			अगर ((s32)(now - ca->round_start) > threshold) अणु
				ca->found = 1;
				pr_debug("hystart_ack_train (%u > %u) delay_min %u (+ ack_delay %u) cwnd %u\n",
					 now - ca->round_start, threshold,
					 ca->delay_min, hystart_ack_delay(sk), tp->snd_cwnd);
				NET_INC_STATS(sock_net(sk),
					      LINUX_MIB_TCPHYSTARTTRAINDETECT);
				NET_ADD_STATS(sock_net(sk),
					      LINUX_MIB_TCPHYSTARTTRAINCWND,
					      tp->snd_cwnd);
				tp->snd_ssthresh = tp->snd_cwnd;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (hystart_detect & HYSTART_DELAY) अणु
		/* obtain the minimum delay of more than sampling packets */
		अगर (ca->curr_rtt > delay)
			ca->curr_rtt = delay;
		अगर (ca->sample_cnt < HYSTART_MIN_SAMPLES) अणु
			ca->sample_cnt++;
		पूर्ण अन्यथा अणु
			अगर (ca->curr_rtt > ca->delay_min +
			    HYSTART_DELAY_THRESH(ca->delay_min >> 3)) अणु
				ca->found = 1;
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

अटल व्योम cubictcp_acked(काष्ठा sock *sk, स्थिर काष्ठा ack_sample *sample)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bictcp *ca = inet_csk_ca(sk);
	u32 delay;

	/* Some calls are क्रम duplicates without समयtamps */
	अगर (sample->rtt_us < 0)
		वापस;

	/* Discard delay samples right after fast recovery */
	अगर (ca->epoch_start && (s32)(tcp_jअगरfies32 - ca->epoch_start) < HZ)
		वापस;

	delay = sample->rtt_us;
	अगर (delay == 0)
		delay = 1;

	/* first समय call or link delay decreases */
	अगर (ca->delay_min == 0 || ca->delay_min > delay)
		ca->delay_min = delay;

	/* hystart triggers when cwnd is larger than some threshold */
	अगर (!ca->found && tcp_in_slow_start(tp) && hystart &&
	    tp->snd_cwnd >= hystart_low_winकरोw)
		hystart_update(sk, delay);
पूर्ण

अटल काष्ठा tcp_congestion_ops cubictcp __पढ़ो_mostly = अणु
	.init		= cubictcp_init,
	.ssthresh	= cubictcp_recalc_ssthresh,
	.cong_aव्योम	= cubictcp_cong_aव्योम,
	.set_state	= cubictcp_state,
	.unकरो_cwnd	= tcp_reno_unकरो_cwnd,
	.cwnd_event	= cubictcp_cwnd_event,
	.pkts_acked     = cubictcp_acked,
	.owner		= THIS_MODULE,
	.name		= "cubic",
पूर्ण;

अटल पूर्णांक __init cubictcp_रेजिस्टर(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा bictcp) > ICSK_CA_PRIV_SIZE);

	/* Precompute a bunch of the scaling factors that are used per-packet
	 * based on SRTT of 100ms
	 */

	beta_scale = 8*(BICTCP_BETA_SCALE+beta) / 3
		/ (BICTCP_BETA_SCALE - beta);

	cube_rtt_scale = (bic_scale * 10);	/* 1024*c/rtt */

	/* calculate the "K" क्रम (wmax-cwnd) = c/rtt * K^3
	 *  so K = cubic_root( (wmax-cwnd)*rtt/c )
	 * the unit of K is bictcp_HZ=2^10, not HZ
	 *
	 *  c = bic_scale >> 10
	 *  rtt = 100ms
	 *
	 * the following code has been deचिन्हित and tested क्रम
	 * cwnd < 1 million packets
	 * RTT < 100 seconds
	 * HZ < 1,000,00  (corresponding to 10 nano-second)
	 */

	/* 1/c * 2^2*bictcp_HZ * srtt */
	cube_factor = 1ull << (10+3*BICTCP_HZ); /* 2^40 */

	/* भागide by bic_scale and by स्थिरant Srtt (100ms) */
	करो_भाग(cube_factor, bic_scale * 10);

	वापस tcp_रेजिस्टर_congestion_control(&cubictcp);
पूर्ण

अटल व्योम __निकास cubictcp_unरेजिस्टर(व्योम)
अणु
	tcp_unरेजिस्टर_congestion_control(&cubictcp);
पूर्ण

module_init(cubictcp_रेजिस्टर);
module_निकास(cubictcp_unरेजिस्टर);

MODULE_AUTHOR("Sangtae Ha, Stephen Hemminger");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("CUBIC TCP");
MODULE_VERSION("2.3");
