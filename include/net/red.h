<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_SCHED_RED_H
#घोषणा __NET_SCHED_RED_H

#समावेश <linux/types.h>
#समावेश <linux/bug.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/dsfield.h>
#समावेश <linux/reciprocal_भाग.h>

/*	Ranकरोm Early Detection (RED) algorithm.
	=======================================

	Source: Sally Floyd and Van Jacobson, "Ranकरोm Early Detection Gateways
	क्रम Congestion Aव्योमance", 1993, IEEE/ACM Transactions on Networking.

	This file codes a "divisionless" version of RED algorithm
	as written करोwn in Fig.17 of the paper.

	Short description.
	------------------

	When a new packet arrives we calculate the average queue length:

	avg = (1-W)*avg + W*current_queue_len,

	W is the filter समय स्थिरant (chosen as 2^(-Wlog)), it controls
	the inertia of the algorithm. To allow larger bursts, W should be
	decreased.

	अगर (avg > th_max) -> packet marked (dropped).
	अगर (avg < th_min) -> packet passes.
	अगर (th_min < avg < th_max) we calculate probability:

	Pb = max_P * (avg - th_min)/(th_max-th_min)

	and mark (drop) packet with this probability.
	Pb changes from 0 (at avg==th_min) to max_P (avg==th_max).
	max_P should be small (not 1), usually 0.01..0.02 is good value.

	max_P is chosen as a number, so that max_P/(th_max-th_min)
	is a negative घातer of two in order arithmetics to contain
	only shअगरts.


	Parameters, settable by user:
	-----------------------------

	qth_min		- bytes (should be < qth_max/2)
	qth_max		- bytes (should be at least 2*qth_min and less limit)
	Wlog	       	- bits (<32) log(1/W).
	Plog	       	- bits (<32)

	Plog is related to max_P by क्रमmula:

	max_P = (qth_max-qth_min)/2^Plog;

	F.e. अगर qth_max=128K and qth_min=32K, then Plog=22
	corresponds to max_P=0.02

	Scell_log
	Stab

	Lookup table क्रम log((1-W)^(t/t_ave).


	NOTES:

	Upper bound on W.
	-----------------

	If you want to allow bursts of L packets of size S,
	you should choose W:

	L + 1 - th_min/S < (1-(1-W)^L)/W

	th_min/S = 32         th_min/S = 4

	log(W)	L
	-1	33
	-2	35
	-3	39
	-4	46
	-5	57
	-6	75
	-7	101
	-8	135
	-9	190
	etc.
 */

/*
 * Adaptative RED : An Algorithm क्रम Increasing the Robustness of RED's AQM
 * (Sally FLoyd, Ramakrishna Gummadi, and Scott Shenker) August 2001
 *
 * Every 500 ms:
 *  अगर (avg > target and max_p <= 0.5)
 *   increase max_p : max_p += alpha;
 *  अन्यथा अगर (avg < target and max_p >= 0.01)
 *   decrease max_p : max_p *= beta;
 *
 * target :[qth_min + 0.4*(qth_min - qth_max),
 *          qth_min + 0.6*(qth_min - qth_max)].
 * alpha : min(0.01, max_p / 4)
 * beta : 0.9
 * max_P is a Q0.32 fixed poपूर्णांक number (with 32 bits mantissa)
 * max_P between 0.01 and 0.5 (1% - 50%) [ Its no दीर्घer a negative घातer of two ]
 */
#घोषणा RED_ONE_PERCENT ((u32)DIV_ROUND_CLOSEST(1ULL<<32, 100))

#घोषणा MAX_P_MIN (1 * RED_ONE_PERCENT)
#घोषणा MAX_P_MAX (50 * RED_ONE_PERCENT)
#घोषणा MAX_P_ALPHA(val) min(MAX_P_MIN, val / 4)

#घोषणा RED_STAB_SIZE	256
#घोषणा RED_STAB_MASK	(RED_STAB_SIZE - 1)

काष्ठा red_stats अणु
	u32		prob_drop;	/* Early probability drops */
	u32		prob_mark;	/* Early probability marks */
	u32		क्रमced_drop;	/* Forced drops, qavg > max_thresh */
	u32		क्रमced_mark;	/* Forced marks, qavg > max_thresh */
	u32		pdrop;          /* Drops due to queue limits */
	u32		other;          /* Drops due to drop() calls */
पूर्ण;

काष्ठा red_parms अणु
	/* Parameters */
	u32		qth_min;	/* Min avg length threshold: Wlog scaled */
	u32		qth_max;	/* Max avg length threshold: Wlog scaled */
	u32		Scell_max;
	u32		max_P;		/* probability, [0 .. 1.0] 32 scaled */
	/* reciprocal_value(max_P / qth_delta) */
	काष्ठा reciprocal_value	max_P_reciprocal;
	u32		qth_delta;	/* max_th - min_th */
	u32		target_min;	/* min_th + 0.4*(max_th - min_th) */
	u32		target_max;	/* min_th + 0.6*(max_th - min_th) */
	u8		Scell_log;
	u8		Wlog;		/* log(W)		*/
	u8		Plog;		/* अक्रमom number bits	*/
	u8		Stab[RED_STAB_SIZE];
पूर्ण;

काष्ठा red_vars अणु
	/* Variables */
	पूर्णांक		qcount;		/* Number of packets since last अक्रमom
					   number generation */
	u32		qR;		/* Cached अक्रमom number */

	अचिन्हित दीर्घ	qavg;		/* Average queue length: Wlog scaled */
	kसमय_प्रकार		qidlestart;	/* Start of current idle period */
पूर्ण;

अटल अंतरभूत u32 red_maxp(u8 Plog)
अणु
	वापस Plog < 32 ? (~0U >> Plog) : ~0U;
पूर्ण

अटल अंतरभूत व्योम red_set_vars(काष्ठा red_vars *v)
अणु
	/* Reset average queue length, the value is strictly bound
	 * to the parameters below, reseting hurts a bit but leaving
	 * it might result in an unreasonable qavg क्रम a जबतक. --TGR
	 */
	v->qavg		= 0;

	v->qcount	= -1;
पूर्ण

अटल अंतरभूत bool red_check_params(u32 qth_min, u32 qth_max, u8 Wlog,
				    u8 Scell_log, u8 *stab)
अणु
	अगर (fls(qth_min) + Wlog >= 32)
		वापस false;
	अगर (fls(qth_max) + Wlog >= 32)
		वापस false;
	अगर (Scell_log >= 32)
		वापस false;
	अगर (qth_max < qth_min)
		वापस false;
	अगर (stab) अणु
		पूर्णांक i;

		क्रम (i = 0; i < RED_STAB_SIZE; i++)
			अगर (stab[i] >= 32)
				वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक red_get_flags(अचिन्हित अक्षर qopt_flags,
				अचिन्हित अक्षर historic_mask,
				काष्ठा nlattr *flags_attr,
				अचिन्हित अक्षर supported_mask,
				काष्ठा nla_bitfield32 *p_flags,
				अचिन्हित अक्षर *p_userbits,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nla_bitfield32 flags;

	अगर (qopt_flags && flags_attr) अणु
		NL_SET_ERR_MSG_MOD(extack, "flags should be passed either through qopt, or through a dedicated attribute");
		वापस -EINVAL;
	पूर्ण

	अगर (flags_attr) अणु
		flags = nla_get_bitfield32(flags_attr);
	पूर्ण अन्यथा अणु
		flags.selector = historic_mask;
		flags.value = qopt_flags & historic_mask;
	पूर्ण

	*p_flags = flags;
	*p_userbits = qopt_flags & ~historic_mask;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक red_validate_flags(अचिन्हित अक्षर flags,
				     काष्ठा netlink_ext_ack *extack)
अणु
	अगर ((flags & TC_RED_NODROP) && !(flags & TC_RED_ECN)) अणु
		NL_SET_ERR_MSG_MOD(extack, "nodrop mode is only meaningful with ECN");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम red_set_parms(काष्ठा red_parms *p,
				 u32 qth_min, u32 qth_max, u8 Wlog, u8 Plog,
				 u8 Scell_log, u8 *stab, u32 max_P)
अणु
	पूर्णांक delta = qth_max - qth_min;
	u32 max_p_delta;

	p->qth_min	= qth_min << Wlog;
	p->qth_max	= qth_max << Wlog;
	p->Wlog		= Wlog;
	p->Plog		= Plog;
	अगर (delta <= 0)
		delta = 1;
	p->qth_delta	= delta;
	अगर (!max_P) अणु
		max_P = red_maxp(Plog);
		max_P *= delta; /* max_P = (qth_max - qth_min)/2^Plog */
	पूर्ण
	p->max_P = max_P;
	max_p_delta = max_P / delta;
	max_p_delta = max(max_p_delta, 1U);
	p->max_P_reciprocal  = reciprocal_value(max_p_delta);

	/* RED Adaptative target :
	 * [min_th + 0.4*(min_th - max_th),
	 *  min_th + 0.6*(min_th - max_th)].
	 */
	delta /= 5;
	p->target_min = qth_min + 2*delta;
	p->target_max = qth_min + 3*delta;

	p->Scell_log	= Scell_log;
	p->Scell_max	= (255 << Scell_log);

	अगर (stab)
		स_नकल(p->Stab, stab, माप(p->Stab));
पूर्ण

अटल अंतरभूत पूर्णांक red_is_idling(स्थिर काष्ठा red_vars *v)
अणु
	वापस v->qidlestart != 0;
पूर्ण

अटल अंतरभूत व्योम red_start_of_idle_period(काष्ठा red_vars *v)
अणु
	v->qidlestart = kसमय_get();
पूर्ण

अटल अंतरभूत व्योम red_end_of_idle_period(काष्ठा red_vars *v)
अणु
	v->qidlestart = 0;
पूर्ण

अटल अंतरभूत व्योम red_restart(काष्ठा red_vars *v)
अणु
	red_end_of_idle_period(v);
	v->qavg = 0;
	v->qcount = -1;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ red_calc_qavg_from_idle_समय(स्थिर काष्ठा red_parms *p,
							 स्थिर काष्ठा red_vars *v)
अणु
	s64 delta = kसमय_us_delta(kसमय_get(), v->qidlestart);
	दीर्घ us_idle = min_t(s64, delta, p->Scell_max);
	पूर्णांक  shअगरt;

	/*
	 * The problem: ideally, average length queue recalculation should
	 * be करोne over स्थिरant घड़ी पूर्णांकervals. This is too expensive, so
	 * that the calculation is driven by outgoing packets.
	 * When the queue is idle we have to model this घड़ी by hand.
	 *
	 * SF+VJ proposed to "generate":
	 *
	 *	m = idleसमय / (average_pkt_size / bandwidth)
	 *
	 * dummy packets as a burst after idle समय, i.e.
	 *
	 * 	v->qavg *= (1-W)^m
	 *
	 * This is an apparently overcomplicated solution (f.e. we have to
	 * precompute a table to make this calculation in reasonable समय)
	 * I believe that a simpler model may be used here,
	 * but it is field क्रम experiments.
	 */

	shअगरt = p->Stab[(us_idle >> p->Scell_log) & RED_STAB_MASK];

	अगर (shअगरt)
		वापस v->qavg >> shअगरt;
	अन्यथा अणु
		/* Approximate initial part of exponent with linear function:
		 *
		 * 	(1-W)^m ~= 1-mW + ...
		 *
		 * Seems, it is the best solution to
		 * problem of too coarse exponent tabulation.
		 */
		us_idle = (v->qavg * (u64)us_idle) >> p->Scell_log;

		अगर (us_idle < (v->qavg >> 1))
			वापस v->qavg - us_idle;
		अन्यथा
			वापस v->qavg >> 1;
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ red_calc_qavg_no_idle_समय(स्थिर काष्ठा red_parms *p,
						       स्थिर काष्ठा red_vars *v,
						       अचिन्हित पूर्णांक backlog)
अणु
	/*
	 * NOTE: v->qavg is fixed poपूर्णांक number with poपूर्णांक at Wlog.
	 * The क्रमmula below is equvalent to भग्नing poपूर्णांक
	 * version:
	 *
	 * 	qavg = qavg*(1-W) + backlog*W;
	 *
	 * --ANK (980924)
	 */
	वापस v->qavg + (backlog - (v->qavg >> p->Wlog));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ red_calc_qavg(स्थिर काष्ठा red_parms *p,
					  स्थिर काष्ठा red_vars *v,
					  अचिन्हित पूर्णांक backlog)
अणु
	अगर (!red_is_idling(v))
		वापस red_calc_qavg_no_idle_समय(p, v, backlog);
	अन्यथा
		वापस red_calc_qavg_from_idle_समय(p, v);
पूर्ण


अटल अंतरभूत u32 red_अक्रमom(स्थिर काष्ठा red_parms *p)
अणु
	वापस reciprocal_भागide(pअक्रमom_u32(), p->max_P_reciprocal);
पूर्ण

अटल अंतरभूत पूर्णांक red_mark_probability(स्थिर काष्ठा red_parms *p,
				       स्थिर काष्ठा red_vars *v,
				       अचिन्हित दीर्घ qavg)
अणु
	/* The क्रमmula used below causes questions.

	   OK. qR is अक्रमom number in the पूर्णांकerval
		(0..1/max_P)*(qth_max-qth_min)
	   i.e. 0..(2^Plog). If we used भग्नing poपूर्णांक
	   arithmetics, it would be: (2^Plog)*rnd_num,
	   where rnd_num is less 1.

	   Taking पूर्णांकo account, that qavg have fixed
	   poपूर्णांक at Wlog, two lines
	   below have the following भग्नing poपूर्णांक equivalent:

	   max_P*(qavg - qth_min)/(qth_max-qth_min) < rnd/qcount

	   Any questions? --ANK (980924)
	 */
	वापस !(((qavg - p->qth_min) >> p->Wlog) * v->qcount < v->qR);
पूर्ण

क्रमागत अणु
	RED_BELOW_MIN_THRESH,
	RED_BETWEEN_TRESH,
	RED_ABOVE_MAX_TRESH,
पूर्ण;

अटल अंतरभूत पूर्णांक red_cmp_thresh(स्थिर काष्ठा red_parms *p, अचिन्हित दीर्घ qavg)
अणु
	अगर (qavg < p->qth_min)
		वापस RED_BELOW_MIN_THRESH;
	अन्यथा अगर (qavg >= p->qth_max)
		वापस RED_ABOVE_MAX_TRESH;
	अन्यथा
		वापस RED_BETWEEN_TRESH;
पूर्ण

क्रमागत अणु
	RED_DONT_MARK,
	RED_PROB_MARK,
	RED_HARD_MARK,
पूर्ण;

अटल अंतरभूत पूर्णांक red_action(स्थिर काष्ठा red_parms *p,
			     काष्ठा red_vars *v,
			     अचिन्हित दीर्घ qavg)
अणु
	चयन (red_cmp_thresh(p, qavg)) अणु
		हाल RED_BELOW_MIN_THRESH:
			v->qcount = -1;
			वापस RED_DONT_MARK;

		हाल RED_BETWEEN_TRESH:
			अगर (++v->qcount) अणु
				अगर (red_mark_probability(p, v, qavg)) अणु
					v->qcount = 0;
					v->qR = red_अक्रमom(p);
					वापस RED_PROB_MARK;
				पूर्ण
			पूर्ण अन्यथा
				v->qR = red_अक्रमom(p);

			वापस RED_DONT_MARK;

		हाल RED_ABOVE_MAX_TRESH:
			v->qcount = -1;
			वापस RED_HARD_MARK;
	पूर्ण

	BUG();
	वापस RED_DONT_MARK;
पूर्ण

अटल अंतरभूत व्योम red_adaptative_algo(काष्ठा red_parms *p, काष्ठा red_vars *v)
अणु
	अचिन्हित दीर्घ qavg;
	u32 max_p_delta;

	qavg = v->qavg;
	अगर (red_is_idling(v))
		qavg = red_calc_qavg_from_idle_समय(p, v);

	/* v->qavg is fixed poपूर्णांक number with poपूर्णांक at Wlog */
	qavg >>= p->Wlog;

	अगर (qavg > p->target_max && p->max_P <= MAX_P_MAX)
		p->max_P += MAX_P_ALPHA(p->max_P); /* maxp = maxp + alpha */
	अन्यथा अगर (qavg < p->target_min && p->max_P >= MAX_P_MIN)
		p->max_P = (p->max_P/10)*9; /* maxp = maxp * Beta */

	max_p_delta = DIV_ROUND_CLOSEST(p->max_P, p->qth_delta);
	max_p_delta = max(max_p_delta, 1U);
	p->max_P_reciprocal = reciprocal_value(max_p_delta);
पूर्ण
#पूर्ण_अगर
