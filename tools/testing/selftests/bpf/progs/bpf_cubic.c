<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/* WARNING: This implemenation is not necessarily the same
 * as the tcp_cubic.c.  The purpose is मुख्यly क्रम testing
 * the kernel BPF logic.
 *
 * Highlights:
 * 1. CONFIG_HZ .kconfig map is used.
 * 2. In bictcp_update(), calculation is changed to use usec
 *    resolution (i.e. USEC_PER_JIFFY) instead of using jअगरfies.
 *    Thus, usecs_to_jअगरfies() is not used in the bpf_cubic.c.
 * 3. In bitctcp_update() [under tcp_मित्रliness], the original
 *    "while (ca->ack_cnt > delta)" loop is changed to the equivalent
 *    "ca->ack_cnt / delta" operation.
 */

#समावेश <linux/bpf.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/tcp.h>
#समावेश "bpf_tcp_helpers.h"

अक्षर _license[] SEC("license") = "GPL";

#घोषणा clamp(val, lo, hi) min((typeof(val))max(val, lo), hi)

#घोषणा BICTCP_BETA_SCALE    1024	/* Scale factor beta calculation
					 * max_cwnd = snd_cwnd * beta
					 */
#घोषणा	BICTCP_HZ		10	/* BIC HZ 2^10 = 1024 */

/* Two methods of hybrid slow start */
#घोषणा HYSTART_ACK_TRAIN	0x1
#घोषणा HYSTART_DELAY		0x2

/* Number of delay samples क्रम detecting the increase of delay */
#घोषणा HYSTART_MIN_SAMPLES	8
#घोषणा HYSTART_DELAY_MIN	(4000U)	/* 4ms */
#घोषणा HYSTART_DELAY_MAX	(16000U)	/* 16 ms */
#घोषणा HYSTART_DELAY_THRESH(x)	clamp(x, HYSTART_DELAY_MIN, HYSTART_DELAY_MAX)

अटल पूर्णांक fast_convergence = 1;
अटल स्थिर पूर्णांक beta = 717;	/* = 717/1024 (BICTCP_BETA_SCALE) */
अटल पूर्णांक initial_ssthresh;
अटल स्थिर पूर्णांक bic_scale = 41;
अटल पूर्णांक tcp_मित्रliness = 1;

अटल पूर्णांक hystart = 1;
अटल पूर्णांक hystart_detect = HYSTART_ACK_TRAIN | HYSTART_DELAY;
अटल पूर्णांक hystart_low_winकरोw = 16;
अटल पूर्णांक hystart_ack_delta_us = 2000;

अटल स्थिर __u32 cube_rtt_scale = (bic_scale * 10);	/* 1024*c/rtt */
अटल स्थिर __u32 beta_scale = 8*(BICTCP_BETA_SCALE+beta) / 3
				/ (BICTCP_BETA_SCALE - beta);
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

/* 1/c * 2^2*bictcp_HZ * srtt, 2^40 */
अटल स्थिर __u64 cube_factor = (__u64)(1ull << (10+3*BICTCP_HZ))
				/ (bic_scale * 10);

/* BIC TCP Parameters */
काष्ठा bictcp अणु
	__u32	cnt;		/* increase cwnd by 1 after ACKs */
	__u32	last_max_cwnd;	/* last maximum snd_cwnd */
	__u32	last_cwnd;	/* the last snd_cwnd */
	__u32	last_समय;	/* समय when updated last_cwnd */
	__u32	bic_origin_poपूर्णांक;/* origin poपूर्णांक of bic function */
	__u32	bic_K;		/* समय to origin poपूर्णांक
				   from the beginning of the current epoch */
	__u32	delay_min;	/* min delay (usec) */
	__u32	epoch_start;	/* beginning of an epoch */
	__u32	ack_cnt;	/* number of acks */
	__u32	tcp_cwnd;	/* estimated tcp cwnd */
	__u16	unused;
	__u8	sample_cnt;	/* number of samples to decide curr_rtt */
	__u8	found;		/* the निकास poपूर्णांक is found? */
	__u32	round_start;	/* beginning of each round */
	__u32	end_seq;	/* end_seq of the round */
	__u32	last_ack;	/* last समय when the ACK spacing is बंद */
	__u32	curr_rtt;	/* the minimum rtt of current round */
पूर्ण;

अटल अंतरभूत व्योम bictcp_reset(काष्ठा bictcp *ca)
अणु
	ca->cnt = 0;
	ca->last_max_cwnd = 0;
	ca->last_cwnd = 0;
	ca->last_समय = 0;
	ca->bic_origin_poपूर्णांक = 0;
	ca->bic_K = 0;
	ca->delay_min = 0;
	ca->epoch_start = 0;
	ca->ack_cnt = 0;
	ca->tcp_cwnd = 0;
	ca->found = 0;
पूर्ण

बाह्य अचिन्हित दीर्घ CONFIG_HZ __kconfig;
#घोषणा HZ CONFIG_HZ
#घोषणा USEC_PER_MSEC	1000UL
#घोषणा USEC_PER_SEC	1000000UL
#घोषणा USEC_PER_JIFFY	(USEC_PER_SEC / HZ)

अटल __always_अंतरभूत __u64 भाग64_u64(__u64 भागidend, __u64 भागisor)
अणु
	वापस भागidend / भागisor;
पूर्ण

#घोषणा भाग64_ul भाग64_u64

#घोषणा BITS_PER_U64 (माप(__u64) * 8)
अटल __always_अंतरभूत पूर्णांक fls64(__u64 x)
अणु
	पूर्णांक num = BITS_PER_U64 - 1;

	अगर (x == 0)
		वापस 0;

	अगर (!(x & (~0ull << (BITS_PER_U64-32)))) अणु
		num -= 32;
		x <<= 32;
	पूर्ण
	अगर (!(x & (~0ull << (BITS_PER_U64-16)))) अणु
		num -= 16;
		x <<= 16;
	पूर्ण
	अगर (!(x & (~0ull << (BITS_PER_U64-8)))) अणु
		num -= 8;
		x <<= 8;
	पूर्ण
	अगर (!(x & (~0ull << (BITS_PER_U64-4)))) अणु
		num -= 4;
		x <<= 4;
	पूर्ण
	अगर (!(x & (~0ull << (BITS_PER_U64-2)))) अणु
		num -= 2;
		x <<= 2;
	पूर्ण
	अगर (!(x & (~0ull << (BITS_PER_U64-1))))
		num -= 1;

	वापस num + 1;
पूर्ण

अटल __always_अंतरभूत __u32 bictcp_घड़ी_us(स्थिर काष्ठा sock *sk)
अणु
	वापस tcp_sk(sk)->tcp_mstamp;
पूर्ण

अटल __always_अंतरभूत व्योम bictcp_hystart_reset(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bictcp *ca = inet_csk_ca(sk);

	ca->round_start = ca->last_ack = bictcp_घड़ी_us(sk);
	ca->end_seq = tp->snd_nxt;
	ca->curr_rtt = ~0U;
	ca->sample_cnt = 0;
पूर्ण

/* "struct_ops/" prefix is not a requirement
 * It will be recognized as BPF_PROG_TYPE_STRUCT_OPS
 * as दीर्घ as it is used in one of the func ptr
 * under SEC(".struct_ops").
 */
SEC("struct_ops/bpf_cubic_init")
व्योम BPF_PROG(bpf_cubic_init, काष्ठा sock *sk)
अणु
	काष्ठा bictcp *ca = inet_csk_ca(sk);

	bictcp_reset(ca);

	अगर (hystart)
		bictcp_hystart_reset(sk);

	अगर (!hystart && initial_ssthresh)
		tcp_sk(sk)->snd_ssthresh = initial_ssthresh;
पूर्ण

/* No prefix in SEC will also work.
 * The reमुख्यing tcp-cubic functions have an easier way.
 */
SEC("no-sec-prefix-bictcp_cwnd_event")
व्योम BPF_PROG(bpf_cubic_cwnd_event, काष्ठा sock *sk, क्रमागत tcp_ca_event event)
अणु
	अगर (event == CA_EVENT_TX_START) अणु
		काष्ठा bictcp *ca = inet_csk_ca(sk);
		__u32 now = tcp_jअगरfies32;
		__s32 delta;

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

/*
 * cbrt(x) MSB values क्रम x MSB values in [0..63].
 * Precomputed then refined by hand - Willy Tarreau
 *
 * For x in [0..63],
 *   v = cbrt(x << 18) - 1
 *   cbrt(x) = (v[x] + 10) >> 6
 */
अटल स्थिर __u8 v[] = अणु
	/* 0x00 */    0,   54,   54,   54,  118,  118,  118,  118,
	/* 0x08 */  123,  129,  134,  138,  143,  147,  151,  156,
	/* 0x10 */  157,  161,  164,  168,  170,  173,  176,  179,
	/* 0x18 */  181,  185,  187,  190,  192,  194,  197,  199,
	/* 0x20 */  200,  202,  204,  206,  209,  211,  213,  215,
	/* 0x28 */  217,  219,  221,  222,  224,  225,  227,  229,
	/* 0x30 */  231,  232,  234,  236,  237,  239,  240,  242,
	/* 0x38 */  244,  245,  246,  248,  250,  251,  252,  254,
पूर्ण;

/* calculate the cubic root of x using a table lookup followed by one
 * Newton-Raphson iteration.
 * Avg err ~= 0.195%
 */
अटल __always_अंतरभूत __u32 cubic_root(__u64 a)
अणु
	__u32 x, b, shअगरt;

	अगर (a < 64) अणु
		/* a in [0..63] */
		वापस ((__u32)v[(__u32)a] + 35) >> 6;
	पूर्ण

	b = fls64(a);
	b = ((b * 84) >> 8) - 1;
	shअगरt = (a >> (b * 3));

	/* it is needed क्रम verअगरier's bound check on v */
	अगर (shअगरt >= 64)
		वापस 0;

	x = ((__u32)(((__u32)v[shअगरt] + 10) << b)) >> 6;

	/*
	 * Newton-Raphson iteration
	 *                         2
	 * x    = ( 2 * x  +  a / x  ) / 3
	 *  k+1          k         k
	 */
	x = (2 * x + (__u32)भाग64_u64(a, (__u64)x * (__u64)(x - 1)));
	x = ((x * 341) >> 10);
	वापस x;
पूर्ण

/*
 * Compute congestion winकरोw to use.
 */
अटल __always_अंतरभूत व्योम bictcp_update(काष्ठा bictcp *ca, __u32 cwnd,
					  __u32 acked)
अणु
	__u32 delta, bic_target, max_cnt;
	__u64 offs, t;

	ca->ack_cnt += acked;	/* count the number of ACKed packets */

	अगर (ca->last_cwnd == cwnd &&
	    (__s32)(tcp_jअगरfies32 - ca->last_समय) <= HZ / 32)
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

	t = (__s32)(tcp_jअगरfies32 - ca->epoch_start) * USEC_PER_JIFFY;
	t += ca->delay_min;
	/* change the unit from usec to bictcp_HZ */
	t <<= BICTCP_HZ;
	t /= USEC_PER_SEC;

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
		__u32 scale = beta_scale;
		__u32 n;

		/* update tcp cwnd */
		delta = (cwnd * scale) >> 3;
		अगर (ca->ack_cnt > delta && delta) अणु
			n = ca->ack_cnt / delta;
			ca->ack_cnt -= n * delta;
			ca->tcp_cwnd += n;
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

/* Or simply use the BPF_STRUCT_OPS to aव्योम the SEC boiler plate. */
व्योम BPF_STRUCT_OPS(bpf_cubic_cong_aव्योम, काष्ठा sock *sk, __u32 ack, __u32 acked)
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

__u32 BPF_STRUCT_OPS(bpf_cubic_recalc_ssthresh, काष्ठा sock *sk)
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

व्योम BPF_STRUCT_OPS(bpf_cubic_state, काष्ठा sock *sk, __u8 new_state)
अणु
	अगर (new_state == TCP_CA_Loss) अणु
		bictcp_reset(inet_csk_ca(sk));
		bictcp_hystart_reset(sk);
	पूर्ण
पूर्ण

#घोषणा GSO_MAX_SIZE		65536

/* Account क्रम TSO/GRO delays.
 * Otherwise लघु RTT flows could get too small ssthresh, since during
 * slow start we begin with small TSO packets and ca->delay_min would
 * not account क्रम दीर्घ aggregation delay when TSO packets get bigger.
 * Ideally even with a very small RTT we would like to have at least one
 * TSO packet being sent and received by GRO, and another one in qdisc layer.
 * We apply another 100% factor because @rate is द्विगुनd at this poपूर्णांक.
 * We cap the cushion to 1ms.
 */
अटल __always_अंतरभूत __u32 hystart_ack_delay(काष्ठा sock *sk)
अणु
	अचिन्हित दीर्घ rate;

	rate = sk->sk_pacing_rate;
	अगर (!rate)
		वापस 0;
	वापस min((__u64)USEC_PER_MSEC,
		   भाग64_ul((__u64)GSO_MAX_SIZE * 4 * USEC_PER_SEC, rate));
पूर्ण

अटल __always_अंतरभूत व्योम hystart_update(काष्ठा sock *sk, __u32 delay)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bictcp *ca = inet_csk_ca(sk);
	__u32 threshold;

	अगर (hystart_detect & HYSTART_ACK_TRAIN) अणु
		__u32 now = bictcp_घड़ी_us(sk);

		/* first detection parameter - ack-train detection */
		अगर ((__s32)(now - ca->last_ack) <= hystart_ack_delta_us) अणु
			ca->last_ack = now;

			threshold = ca->delay_min + hystart_ack_delay(sk);

			/* Hystart ack train triggers अगर we get ack past
			 * ca->delay_min/2.
			 * Pacing might have delayed packets up to RTT/2
			 * during slow start.
			 */
			अगर (sk->sk_pacing_status == SK_PACING_NONE)
				threshold >>= 1;

			अगर ((__s32)(now - ca->round_start) > threshold) अणु
				ca->found = 1;
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
				tp->snd_ssthresh = tp->snd_cwnd;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम BPF_STRUCT_OPS(bpf_cubic_acked, काष्ठा sock *sk,
		    स्थिर काष्ठा ack_sample *sample)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bictcp *ca = inet_csk_ca(sk);
	__u32 delay;

	/* Some calls are क्रम duplicates without समयtamps */
	अगर (sample->rtt_us < 0)
		वापस;

	/* Discard delay samples right after fast recovery */
	अगर (ca->epoch_start && (__s32)(tcp_jअगरfies32 - ca->epoch_start) < HZ)
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

बाह्य __u32 tcp_reno_unकरो_cwnd(काष्ठा sock *sk) __ksym;

__u32 BPF_STRUCT_OPS(bpf_cubic_unकरो_cwnd, काष्ठा sock *sk)
अणु
	वापस tcp_reno_unकरो_cwnd(sk);
पूर्ण

SEC(".struct_ops")
काष्ठा tcp_congestion_ops cubic = अणु
	.init		= (व्योम *)bpf_cubic_init,
	.ssthresh	= (व्योम *)bpf_cubic_recalc_ssthresh,
	.cong_aव्योम	= (व्योम *)bpf_cubic_cong_aव्योम,
	.set_state	= (व्योम *)bpf_cubic_state,
	.unकरो_cwnd	= (व्योम *)bpf_cubic_unकरो_cwnd,
	.cwnd_event	= (व्योम *)bpf_cubic_cwnd_event,
	.pkts_acked     = (व्योम *)bpf_cubic_acked,
	.name		= "bpf_cubic",
पूर्ण;
