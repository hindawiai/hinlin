<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TCP HYBLA
 *
 * TCP-HYBLA Congestion control algorithm, based on:
 *   C.Caini, R.Firrincieli, "TCP-Hybla: A TCP Enhancement
 *   क्रम Heterogeneous Networks",
 *   International Journal on satellite Communications,
 *				       September 2004
 *    Daniele Lacamera
 *    root at danielinux.net
 */

#समावेश <linux/module.h>
#समावेश <net/tcp.h>

/* Tcp Hybla काष्ठाure. */
काष्ठा hybla अणु
	bool  hybla_en;
	u32   snd_cwnd_cents; /* Keeps increment values when it is <1, <<7 */
	u32   rho;	      /* Rho parameter, पूर्णांकeger part  */
	u32   rho2;	      /* Rho * Rho, पूर्णांकeger part */
	u32   rho_3ls;	      /* Rho parameter, <<3 */
	u32   rho2_7ls;	      /* Rho^2, <<7	*/
	u32   minrtt_us;      /* Minimum smoothed round trip समय value seen */
पूर्ण;

/* Hybla reference round trip समय (शेष= 1/40 sec = 25 ms), in ms */
अटल पूर्णांक rtt0 = 25;
module_param(rtt0, पूर्णांक, 0644);
MODULE_PARM_DESC(rtt0, "reference rout trip time (ms)");

/* This is called to refresh values क्रम hybla parameters */
अटल अंतरभूत व्योम hybla_recalc_param (काष्ठा sock *sk)
अणु
	काष्ठा hybla *ca = inet_csk_ca(sk);

	ca->rho_3ls = max_t(u32,
			    tcp_sk(sk)->srtt_us / (rtt0 * USEC_PER_MSEC),
			    8U);
	ca->rho = ca->rho_3ls >> 3;
	ca->rho2_7ls = (ca->rho_3ls * ca->rho_3ls) << 1;
	ca->rho2 = ca->rho2_7ls >> 7;
पूर्ण

अटल व्योम hybla_init(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा hybla *ca = inet_csk_ca(sk);

	ca->rho = 0;
	ca->rho2 = 0;
	ca->rho_3ls = 0;
	ca->rho2_7ls = 0;
	ca->snd_cwnd_cents = 0;
	ca->hybla_en = true;
	tp->snd_cwnd = 2;
	tp->snd_cwnd_clamp = 65535;

	/* 1st Rho measurement based on initial srtt */
	hybla_recalc_param(sk);

	/* set minimum rtt as this is the 1st ever seen */
	ca->minrtt_us = tp->srtt_us;
	tp->snd_cwnd = ca->rho;
पूर्ण

अटल व्योम hybla_state(काष्ठा sock *sk, u8 ca_state)
अणु
	काष्ठा hybla *ca = inet_csk_ca(sk);

	ca->hybla_en = (ca_state == TCP_CA_Open);
पूर्ण

अटल अंतरभूत u32 hybla_fraction(u32 odds)
अणु
	अटल स्थिर u32 fractions[] = अणु
		128, 139, 152, 165, 181, 197, 215, 234,
	पूर्ण;

	वापस (odds < ARRAY_SIZE(fractions)) ? fractions[odds] : 128;
पूर्ण

/* TCP Hybla मुख्य routine.
 * This is the algorithm behavior:
 *     o Recalc Hybla parameters अगर min_rtt has changed
 *     o Give cwnd a new value based on the model proposed
 *     o remember increments <1
 */
अटल व्योम hybla_cong_aव्योम(काष्ठा sock *sk, u32 ack, u32 acked)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा hybla *ca = inet_csk_ca(sk);
	u32 increment, odd, rho_fractions;
	पूर्णांक is_slowstart = 0;

	/*  Recalculate rho only अगर this srtt is the lowest */
	अगर (tp->srtt_us < ca->minrtt_us) अणु
		hybla_recalc_param(sk);
		ca->minrtt_us = tp->srtt_us;
	पूर्ण

	अगर (!tcp_is_cwnd_limited(sk))
		वापस;

	अगर (!ca->hybla_en) अणु
		tcp_reno_cong_aव्योम(sk, ack, acked);
		वापस;
	पूर्ण

	अगर (ca->rho == 0)
		hybla_recalc_param(sk);

	rho_fractions = ca->rho_3ls - (ca->rho << 3);

	अगर (tcp_in_slow_start(tp)) अणु
		/*
		 * slow start
		 *      INC = 2^RHO - 1
		 * This is करोne by splitting the rho parameter
		 * पूर्णांकo 2 parts: an पूर्णांकeger part and a fraction part.
		 * Inrement<<7 is estimated by करोing:
		 *	       [2^(पूर्णांक+fract)]<<7
		 * that is equal to:
		 *	       (2^पूर्णांक)	*  [(2^fract) <<7]
		 * 2^पूर्णांक is straightly computed as 1<<पूर्णांक,
		 * जबतक we will use hybla_slowstart_fraction_increment() to
		 * calculate 2^fract in a <<7 value.
		 */
		is_slowstart = 1;
		increment = ((1 << min(ca->rho, 16U)) *
			hybla_fraction(rho_fractions)) - 128;
	पूर्ण अन्यथा अणु
		/*
		 * congestion aव्योमance
		 * INC = RHO^2 / W
		 * as दीर्घ as increment is estimated as (rho<<7)/winकरोw
		 * it alपढ़ोy is <<7 and we can easily count its fractions.
		 */
		increment = ca->rho2_7ls / tp->snd_cwnd;
		अगर (increment < 128)
			tp->snd_cwnd_cnt++;
	पूर्ण

	odd = increment % 128;
	tp->snd_cwnd += increment >> 7;
	ca->snd_cwnd_cents += odd;

	/* check when fractions goes >=128 and increase cwnd by 1. */
	जबतक (ca->snd_cwnd_cents >= 128) अणु
		tp->snd_cwnd++;
		ca->snd_cwnd_cents -= 128;
		tp->snd_cwnd_cnt = 0;
	पूर्ण
	/* check when cwnd has not been incremented क्रम a जबतक */
	अगर (increment == 0 && odd == 0 && tp->snd_cwnd_cnt >= tp->snd_cwnd) अणु
		tp->snd_cwnd++;
		tp->snd_cwnd_cnt = 0;
	पूर्ण
	/* clamp करोwn slowstart cwnd to ssthresh value. */
	अगर (is_slowstart)
		tp->snd_cwnd = min(tp->snd_cwnd, tp->snd_ssthresh);

	tp->snd_cwnd = min_t(u32, tp->snd_cwnd, tp->snd_cwnd_clamp);
पूर्ण

अटल काष्ठा tcp_congestion_ops tcp_hybla __पढ़ो_mostly = अणु
	.init		= hybla_init,
	.ssthresh	= tcp_reno_ssthresh,
	.unकरो_cwnd	= tcp_reno_unकरो_cwnd,
	.cong_aव्योम	= hybla_cong_aव्योम,
	.set_state	= hybla_state,

	.owner		= THIS_MODULE,
	.name		= "hybla"
पूर्ण;

अटल पूर्णांक __init hybla_रेजिस्टर(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा hybla) > ICSK_CA_PRIV_SIZE);
	वापस tcp_रेजिस्टर_congestion_control(&tcp_hybla);
पूर्ण

अटल व्योम __निकास hybla_unरेजिस्टर(व्योम)
अणु
	tcp_unरेजिस्टर_congestion_control(&tcp_hybla);
पूर्ण

module_init(hybla_रेजिस्टर);
module_निकास(hybla_unरेजिस्टर);

MODULE_AUTHOR("Daniele Lacamera");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TCP Hybla");
