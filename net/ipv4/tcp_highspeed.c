<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Sally Floyd's High Speed TCP (RFC 3649) congestion control
 *
 * See https://www.icir.org/floyd/hstcp.hपंचांगl
 *
 * John Heffner <jheffner@psc.edu>
 */

#समावेश <linux/module.h>
#समावेश <net/tcp.h>

/* From AIMD tables from RFC 3649 appendix B,
 * with fixed-poपूर्णांक MD scaled <<8.
 */
अटल स्थिर काष्ठा hstcp_aimd_val अणु
	अचिन्हित पूर्णांक cwnd;
	अचिन्हित पूर्णांक md;
पूर्ण hstcp_aimd_vals[] = अणु
	अणु     38,  128, /*  0.50 */ पूर्ण,
	अणु    118,  112, /*  0.44 */ पूर्ण,
	अणु    221,  104, /*  0.41 */ पूर्ण,
	अणु    347,   98, /*  0.38 */ पूर्ण,
	अणु    495,   93, /*  0.37 */ पूर्ण,
	अणु    663,   89, /*  0.35 */ पूर्ण,
	अणु    851,   86, /*  0.34 */ पूर्ण,
	अणु   1058,   83, /*  0.33 */ पूर्ण,
	अणु   1284,   81, /*  0.32 */ पूर्ण,
	अणु   1529,   78, /*  0.31 */ पूर्ण,
	अणु   1793,   76, /*  0.30 */ पूर्ण,
	अणु   2076,   74, /*  0.29 */ पूर्ण,
	अणु   2378,   72, /*  0.28 */ पूर्ण,
	अणु   2699,   71, /*  0.28 */ पूर्ण,
	अणु   3039,   69, /*  0.27 */ पूर्ण,
	अणु   3399,   68, /*  0.27 */ पूर्ण,
	अणु   3778,   66, /*  0.26 */ पूर्ण,
	अणु   4177,   65, /*  0.26 */ पूर्ण,
	अणु   4596,   64, /*  0.25 */ पूर्ण,
	अणु   5036,   62, /*  0.25 */ पूर्ण,
	अणु   5497,   61, /*  0.24 */ पूर्ण,
	अणु   5979,   60, /*  0.24 */ पूर्ण,
	अणु   6483,   59, /*  0.23 */ पूर्ण,
	अणु   7009,   58, /*  0.23 */ पूर्ण,
	अणु   7558,   57, /*  0.22 */ पूर्ण,
	अणु   8130,   56, /*  0.22 */ पूर्ण,
	अणु   8726,   55, /*  0.22 */ पूर्ण,
	अणु   9346,   54, /*  0.21 */ पूर्ण,
	अणु   9991,   53, /*  0.21 */ पूर्ण,
	अणु  10661,   52, /*  0.21 */ पूर्ण,
	अणु  11358,   52, /*  0.20 */ पूर्ण,
	अणु  12082,   51, /*  0.20 */ पूर्ण,
	अणु  12834,   50, /*  0.20 */ पूर्ण,
	अणु  13614,   49, /*  0.19 */ पूर्ण,
	अणु  14424,   48, /*  0.19 */ पूर्ण,
	अणु  15265,   48, /*  0.19 */ पूर्ण,
	अणु  16137,   47, /*  0.19 */ पूर्ण,
	अणु  17042,   46, /*  0.18 */ पूर्ण,
	अणु  17981,   45, /*  0.18 */ पूर्ण,
	अणु  18955,   45, /*  0.18 */ पूर्ण,
	अणु  19965,   44, /*  0.17 */ पूर्ण,
	अणु  21013,   43, /*  0.17 */ पूर्ण,
	अणु  22101,   43, /*  0.17 */ पूर्ण,
	अणु  23230,   42, /*  0.17 */ पूर्ण,
	अणु  24402,   41, /*  0.16 */ पूर्ण,
	अणु  25618,   41, /*  0.16 */ पूर्ण,
	अणु  26881,   40, /*  0.16 */ पूर्ण,
	अणु  28193,   39, /*  0.16 */ पूर्ण,
	अणु  29557,   39, /*  0.15 */ पूर्ण,
	अणु  30975,   38, /*  0.15 */ पूर्ण,
	अणु  32450,   38, /*  0.15 */ पूर्ण,
	अणु  33986,   37, /*  0.15 */ पूर्ण,
	अणु  35586,   36, /*  0.14 */ पूर्ण,
	अणु  37253,   36, /*  0.14 */ पूर्ण,
	अणु  38992,   35, /*  0.14 */ पूर्ण,
	अणु  40808,   35, /*  0.14 */ पूर्ण,
	अणु  42707,   34, /*  0.13 */ पूर्ण,
	अणु  44694,   33, /*  0.13 */ पूर्ण,
	अणु  46776,   33, /*  0.13 */ पूर्ण,
	अणु  48961,   32, /*  0.13 */ पूर्ण,
	अणु  51258,   32, /*  0.13 */ पूर्ण,
	अणु  53677,   31, /*  0.12 */ पूर्ण,
	अणु  56230,   30, /*  0.12 */ पूर्ण,
	अणु  58932,   30, /*  0.12 */ पूर्ण,
	अणु  61799,   29, /*  0.12 */ पूर्ण,
	अणु  64851,   28, /*  0.11 */ पूर्ण,
	अणु  68113,   28, /*  0.11 */ पूर्ण,
	अणु  71617,   27, /*  0.11 */ पूर्ण,
	अणु  75401,   26, /*  0.10 */ पूर्ण,
	अणु  79517,   26, /*  0.10 */ पूर्ण,
	अणु  84035,   25, /*  0.10 */ पूर्ण,
	अणु  89053,   24, /*  0.10 */ पूर्ण,
पूर्ण;

#घोषणा HSTCP_AIMD_MAX	ARRAY_SIZE(hstcp_aimd_vals)

काष्ठा hstcp अणु
	u32	ai;
पूर्ण;

अटल व्योम hstcp_init(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा hstcp *ca = inet_csk_ca(sk);

	ca->ai = 0;

	/* Ensure the MD arithmetic works.  This is somewhat pedantic,
	 * since I करोn't think we will see a cwnd this large. :) */
	tp->snd_cwnd_clamp = min_t(u32, tp->snd_cwnd_clamp, 0xffffffff/128);
पूर्ण

अटल व्योम hstcp_cong_aव्योम(काष्ठा sock *sk, u32 ack, u32 acked)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा hstcp *ca = inet_csk_ca(sk);

	अगर (!tcp_is_cwnd_limited(sk))
		वापस;

	अगर (tcp_in_slow_start(tp))
		tcp_slow_start(tp, acked);
	अन्यथा अणु
		/* Update AIMD parameters.
		 *
		 * We want to guarantee that:
		 *     hstcp_aimd_vals[ca->ai-1].cwnd <
		 *     snd_cwnd <=
		 *     hstcp_aimd_vals[ca->ai].cwnd
		 */
		अगर (tp->snd_cwnd > hstcp_aimd_vals[ca->ai].cwnd) अणु
			जबतक (tp->snd_cwnd > hstcp_aimd_vals[ca->ai].cwnd &&
			       ca->ai < HSTCP_AIMD_MAX - 1)
				ca->ai++;
		पूर्ण अन्यथा अगर (ca->ai && tp->snd_cwnd <= hstcp_aimd_vals[ca->ai-1].cwnd) अणु
			जबतक (ca->ai && tp->snd_cwnd <= hstcp_aimd_vals[ca->ai-1].cwnd)
				ca->ai--;
		पूर्ण

		/* Do additive increase */
		अगर (tp->snd_cwnd < tp->snd_cwnd_clamp) अणु
			/* cwnd = cwnd + a(w) / cwnd */
			tp->snd_cwnd_cnt += ca->ai + 1;
			अगर (tp->snd_cwnd_cnt >= tp->snd_cwnd) अणु
				tp->snd_cwnd_cnt -= tp->snd_cwnd;
				tp->snd_cwnd++;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल u32 hstcp_ssthresh(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा hstcp *ca = inet_csk_ca(sk);

	/* Do multiplicative decrease */
	वापस max(tp->snd_cwnd - ((tp->snd_cwnd * hstcp_aimd_vals[ca->ai].md) >> 8), 2U);
पूर्ण

अटल काष्ठा tcp_congestion_ops tcp_highspeed __पढ़ो_mostly = अणु
	.init		= hstcp_init,
	.ssthresh	= hstcp_ssthresh,
	.unकरो_cwnd	= tcp_reno_unकरो_cwnd,
	.cong_aव्योम	= hstcp_cong_aव्योम,

	.owner		= THIS_MODULE,
	.name		= "highspeed"
पूर्ण;

अटल पूर्णांक __init hstcp_रेजिस्टर(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा hstcp) > ICSK_CA_PRIV_SIZE);
	वापस tcp_रेजिस्टर_congestion_control(&tcp_highspeed);
पूर्ण

अटल व्योम __निकास hstcp_unरेजिस्टर(व्योम)
अणु
	tcp_unरेजिस्टर_congestion_control(&tcp_highspeed);
पूर्ण

module_init(hstcp_रेजिस्टर);
module_निकास(hstcp_unरेजिस्टर);

MODULE_AUTHOR("John Heffner");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("High Speed TCP");
