<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TCP Low Priority (TCP-LP)
 *
 * TCP Low Priority is a distributed algorithm whose goal is to utilize only
 *   the excess network bandwidth as compared to the ``fair share`` of
 *   bandwidth as targeted by TCP.
 *
 * As of 2.6.13, Linux supports pluggable congestion control algorithms.
 * Due to the limitation of the API, we take the following changes from
 * the original TCP-LP implementation:
 *   o We use newReno in most core CA handling. Only add some checking
 *     within cong_aव्योम.
 *   o Error correcting in remote HZ, thereक्रमe remote HZ will be keeped
 *     on checking and updating.
 *   o Handling calculation of One-Way-Delay (OWD) within rtt_sample, since
 *     OWD have a similar meaning as RTT. Also correct the buggy क्रमmular.
 *   o Handle reaction क्रम Early Congestion Indication (ECI) within
 *     pkts_acked, as mentioned within pseuकरो code.
 *   o OWD is handled in relative क्रमmat, where local समय stamp will in
 *     tcp_समय_stamp क्रमmat.
 *
 * Original Author:
 *   Aleksandar Kuzmanovic <akuzma@northwestern.edu>
 * Available from:
 *   http://www.ece.rice.edu/~akuzma/Doc/akuzma/TCP-LP.pdf
 * Original implementation क्रम 2.4.19:
 *   http://www-ece.rice.edu/networks/TCP-LP/
 *
 * 2.6.x module Authors:
 *   Wong Hoi Sing, Edison <hswong3i@gmail.com>
 *   Hung Hing Lun, Mike <hlhung3i@gmail.com>
 * SourceForge project page:
 *   http://tcp-lp-mod.sourceक्रमge.net/
 */

#समावेश <linux/module.h>
#समावेश <net/tcp.h>

/* resolution of owd */
#घोषणा LP_RESOL       TCP_TS_HZ

/**
 * क्रमागत tcp_lp_state
 * @LP_VALID_RHZ: is remote HZ valid?
 * @LP_VALID_OWD: is OWD valid?
 * @LP_WITHIN_THR: are we within threshold?
 * @LP_WITHIN_INF: are we within inference?
 *
 * TCP-LP's state flags.
 * We create this set of state flag मुख्यly क्रम debugging.
 */
क्रमागत tcp_lp_state अणु
	LP_VALID_RHZ = (1 << 0),
	LP_VALID_OWD = (1 << 1),
	LP_WITHIN_THR = (1 << 3),
	LP_WITHIN_INF = (1 << 4),
पूर्ण;

/**
 * काष्ठा lp
 * @flag: TCP-LP state flag
 * @sowd: smoothed OWD << 3
 * @owd_min: min OWD
 * @owd_max: max OWD
 * @owd_max_rsv: reserved max owd
 * @remote_hz: estimated remote HZ
 * @remote_ref_समय: remote reference समय
 * @local_ref_समय: local reference समय
 * @last_drop: समय क्रम last active drop
 * @inference: current inference
 *
 * TCP-LP's निजी काष्ठा.
 * We get the idea from original TCP-LP implementation where only left those we
 * found are really useful.
 */
काष्ठा lp अणु
	u32 flag;
	u32 sowd;
	u32 owd_min;
	u32 owd_max;
	u32 owd_max_rsv;
	u32 remote_hz;
	u32 remote_ref_समय;
	u32 local_ref_समय;
	u32 last_drop;
	u32 inference;
पूर्ण;

/**
 * tcp_lp_init
 * @sk: socket to initialize congestion control algorithm क्रम
 *
 * Init all required variables.
 * Clone the handling from Vegas module implementation.
 */
अटल व्योम tcp_lp_init(काष्ठा sock *sk)
अणु
	काष्ठा lp *lp = inet_csk_ca(sk);

	lp->flag = 0;
	lp->sowd = 0;
	lp->owd_min = 0xffffffff;
	lp->owd_max = 0;
	lp->owd_max_rsv = 0;
	lp->remote_hz = 0;
	lp->remote_ref_समय = 0;
	lp->local_ref_समय = 0;
	lp->last_drop = 0;
	lp->inference = 0;
पूर्ण

/**
 * tcp_lp_cong_aव्योम
 * @sk: socket to aव्योम congesting
 *
 * Implementation of cong_aव्योम.
 * Will only call newReno CA when away from inference.
 * From TCP-LP's paper, this will be handled in additive increasement.
 */
अटल व्योम tcp_lp_cong_aव्योम(काष्ठा sock *sk, u32 ack, u32 acked)
अणु
	काष्ठा lp *lp = inet_csk_ca(sk);

	अगर (!(lp->flag & LP_WITHIN_INF))
		tcp_reno_cong_aव्योम(sk, ack, acked);
पूर्ण

/**
 * tcp_lp_remote_hz_estimator
 * @sk: socket which needs an estimate क्रम the remote HZs
 *
 * Estimate remote HZ.
 * We keep on updating the estimated value, where original TCP-LP
 * implementation only guest it क्रम once and use क्रमever.
 */
अटल u32 tcp_lp_remote_hz_estimator(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा lp *lp = inet_csk_ca(sk);
	s64 rhz = lp->remote_hz << 6;	/* remote HZ << 6 */
	s64 m = 0;

	/* not yet record reference समय
	 * go away!! record it beक्रमe come back!! */
	अगर (lp->remote_ref_समय == 0 || lp->local_ref_समय == 0)
		जाओ out;

	/* we can't calc remote HZ with no dअगरferent!! */
	अगर (tp->rx_opt.rcv_tsval == lp->remote_ref_समय ||
	    tp->rx_opt.rcv_tsecr == lp->local_ref_समय)
		जाओ out;

	m = TCP_TS_HZ *
	    (tp->rx_opt.rcv_tsval - lp->remote_ref_समय) /
	    (tp->rx_opt.rcv_tsecr - lp->local_ref_समय);
	अगर (m < 0)
		m = -m;

	अगर (rhz > 0) अणु
		m -= rhz >> 6;	/* m is now error in remote HZ est */
		rhz += m;	/* 63/64 old + 1/64 new */
	पूर्ण अन्यथा
		rhz = m << 6;

 out:
	/* record समय क्रम successful remote HZ calc */
	अगर ((rhz >> 6) > 0)
		lp->flag |= LP_VALID_RHZ;
	अन्यथा
		lp->flag &= ~LP_VALID_RHZ;

	/* record reference समय stamp */
	lp->remote_ref_समय = tp->rx_opt.rcv_tsval;
	lp->local_ref_समय = tp->rx_opt.rcv_tsecr;

	वापस rhz >> 6;
पूर्ण

/**
 * tcp_lp_owd_calculator
 * @sk: socket to calculate one way delay क्रम
 *
 * Calculate one way delay (in relative क्रमmat).
 * Original implement OWD as minus of remote समय dअगरference to local समय
 * dअगरference directly. As this समय dअगरference just simply equal to RTT, when
 * the network status is stable, remote RTT will equal to local RTT, and result
 * OWD पूर्णांकo zero.
 * It seems to be a bug and so we fixed it.
 */
अटल u32 tcp_lp_owd_calculator(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा lp *lp = inet_csk_ca(sk);
	s64 owd = 0;

	lp->remote_hz = tcp_lp_remote_hz_estimator(sk);

	अगर (lp->flag & LP_VALID_RHZ) अणु
		owd =
		    tp->rx_opt.rcv_tsval * (LP_RESOL / lp->remote_hz) -
		    tp->rx_opt.rcv_tsecr * (LP_RESOL / TCP_TS_HZ);
		अगर (owd < 0)
			owd = -owd;
	पूर्ण

	अगर (owd > 0)
		lp->flag |= LP_VALID_OWD;
	अन्यथा
		lp->flag &= ~LP_VALID_OWD;

	वापस owd;
पूर्ण

/**
 * tcp_lp_rtt_sample
 * @sk: socket to add a rtt sample to
 * @rtt: round trip समय, which is ignored!
 *
 * Implementation or rtt_sample.
 * Will take the following action,
 *   1. calc OWD,
 *   2. record the min/max OWD,
 *   3. calc smoothed OWD (SOWD).
 * Most ideas come from the original TCP-LP implementation.
 */
अटल व्योम tcp_lp_rtt_sample(काष्ठा sock *sk, u32 rtt)
अणु
	काष्ठा lp *lp = inet_csk_ca(sk);
	s64 mowd = tcp_lp_owd_calculator(sk);

	/* sorry that we करोn't have valid data */
	अगर (!(lp->flag & LP_VALID_RHZ) || !(lp->flag & LP_VALID_OWD))
		वापस;

	/* record the next min owd */
	अगर (mowd < lp->owd_min)
		lp->owd_min = mowd;

	/* always क्रमget the max of the max
	 * we just set owd_max as one below it */
	अगर (mowd > lp->owd_max) अणु
		अगर (mowd > lp->owd_max_rsv) अणु
			अगर (lp->owd_max_rsv == 0)
				lp->owd_max = mowd;
			अन्यथा
				lp->owd_max = lp->owd_max_rsv;
			lp->owd_max_rsv = mowd;
		पूर्ण अन्यथा
			lp->owd_max = mowd;
	पूर्ण

	/* calc क्रम smoothed owd */
	अगर (lp->sowd != 0) अणु
		mowd -= lp->sowd >> 3;	/* m is now error in owd est */
		lp->sowd += mowd;	/* owd = 7/8 owd + 1/8 new */
	पूर्ण अन्यथा
		lp->sowd = mowd << 3;	/* take the measured समय be owd */
पूर्ण

/**
 * tcp_lp_pkts_acked
 * @sk: socket requiring congestion aव्योमance calculations
 *
 * Implementation of pkts_acked.
 * Deal with active drop under Early Congestion Indication.
 * Only drop to half and 1 will be handle, because we hope to use back
 * newReno in increase हाल.
 * We work it out by following the idea from TCP-LP's paper directly
 */
अटल व्योम tcp_lp_pkts_acked(काष्ठा sock *sk, स्थिर काष्ठा ack_sample *sample)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा lp *lp = inet_csk_ca(sk);
	u32 now = tcp_समय_stamp(tp);
	u32 delta;

	अगर (sample->rtt_us > 0)
		tcp_lp_rtt_sample(sk, sample->rtt_us);

	/* calc inference */
	delta = now - tp->rx_opt.rcv_tsecr;
	अगर ((s32)delta > 0)
		lp->inference = 3 * delta;

	/* test अगर within inference */
	अगर (lp->last_drop && (now - lp->last_drop < lp->inference))
		lp->flag |= LP_WITHIN_INF;
	अन्यथा
		lp->flag &= ~LP_WITHIN_INF;

	/* test अगर within threshold */
	अगर (lp->sowd >> 3 <
	    lp->owd_min + 15 * (lp->owd_max - lp->owd_min) / 100)
		lp->flag |= LP_WITHIN_THR;
	अन्यथा
		lp->flag &= ~LP_WITHIN_THR;

	pr_debug("TCP-LP: %05o|%5u|%5u|%15u|%15u|%15u\n", lp->flag,
		 tp->snd_cwnd, lp->remote_hz, lp->owd_min, lp->owd_max,
		 lp->sowd >> 3);

	अगर (lp->flag & LP_WITHIN_THR)
		वापस;

	/* FIXME: try to reset owd_min and owd_max here
	 * so decrease the chance the min/max is no दीर्घer suitable
	 * and will usually within threshold when within inference */
	lp->owd_min = lp->sowd >> 3;
	lp->owd_max = lp->sowd >> 2;
	lp->owd_max_rsv = lp->sowd >> 2;

	/* happened within inference
	 * drop snd_cwnd पूर्णांकo 1 */
	अगर (lp->flag & LP_WITHIN_INF)
		tp->snd_cwnd = 1U;

	/* happened after inference
	 * cut snd_cwnd पूर्णांकo half */
	अन्यथा
		tp->snd_cwnd = max(tp->snd_cwnd >> 1U, 1U);

	/* record this drop समय */
	lp->last_drop = now;
पूर्ण

अटल काष्ठा tcp_congestion_ops tcp_lp __पढ़ो_mostly = अणु
	.init = tcp_lp_init,
	.ssthresh = tcp_reno_ssthresh,
	.unकरो_cwnd = tcp_reno_unकरो_cwnd,
	.cong_aव्योम = tcp_lp_cong_aव्योम,
	.pkts_acked = tcp_lp_pkts_acked,

	.owner = THIS_MODULE,
	.name = "lp"
पूर्ण;

अटल पूर्णांक __init tcp_lp_रेजिस्टर(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा lp) > ICSK_CA_PRIV_SIZE);
	वापस tcp_रेजिस्टर_congestion_control(&tcp_lp);
पूर्ण

अटल व्योम __निकास tcp_lp_unरेजिस्टर(व्योम)
अणु
	tcp_unरेजिस्टर_congestion_control(&tcp_lp);
पूर्ण

module_init(tcp_lp_रेजिस्टर);
module_निकास(tcp_lp_unरेजिस्टर);

MODULE_AUTHOR("Wong Hoi Sing Edison, Hung Hing Lun Mike");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TCP Low Priority");
