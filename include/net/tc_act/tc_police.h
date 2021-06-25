<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_TC_POLICE_H
#घोषणा __NET_TC_POLICE_H

#समावेश <net/act_api.h>

काष्ठा tcf_police_params अणु
	पूर्णांक			tcfp_result;
	u32			tcfp_ewma_rate;
	s64			tcfp_burst;
	u32			tcfp_mtu;
	s64			tcfp_mtu_ptoks;
	s64			tcfp_pkt_burst;
	काष्ठा psched_ratecfg	rate;
	bool			rate_present;
	काष्ठा psched_ratecfg	peak;
	bool			peak_present;
	काष्ठा psched_pktrate	ppsrate;
	bool			pps_present;
	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा tcf_police अणु
	काष्ठा tc_action	common;
	काष्ठा tcf_police_params __rcu *params;

	spinlock_t		tcfp_lock ____cacheline_aligned_in_smp;
	s64			tcfp_toks;
	s64			tcfp_ptoks;
	s64			tcfp_pkttoks;
	s64			tcfp_t_c;
पूर्ण;

#घोषणा to_police(pc) ((काष्ठा tcf_police *)pc)

/* old policer काष्ठाure from beक्रमe tc actions */
काष्ठा tc_police_compat अणु
	u32			index;
	पूर्णांक			action;
	u32			limit;
	u32			burst;
	u32			mtu;
	काष्ठा tc_ratespec	rate;
	काष्ठा tc_ratespec	peakrate;
पूर्ण;

अटल अंतरभूत bool is_tcf_police(स्थिर काष्ठा tc_action *act)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	अगर (act->ops && act->ops->id == TCA_ID_POLICE)
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल अंतरभूत u64 tcf_police_rate_bytes_ps(स्थिर काष्ठा tc_action *act)
अणु
	काष्ठा tcf_police *police = to_police(act);
	काष्ठा tcf_police_params *params;

	params = rcu_dereference_रक्षित(police->params,
					   lockdep_is_held(&police->tcf_lock));
	वापस params->rate.rate_bytes_ps;
पूर्ण

अटल अंतरभूत u32 tcf_police_burst(स्थिर काष्ठा tc_action *act)
अणु
	काष्ठा tcf_police *police = to_police(act);
	काष्ठा tcf_police_params *params;
	u32 burst;

	params = rcu_dereference_रक्षित(police->params,
					   lockdep_is_held(&police->tcf_lock));

	/*
	 *  "rate" bytes   "burst" nanoseconds
	 *  ------------ * -------------------
	 *    1 second          2^6 ticks
	 *
	 * ------------------------------------
	 *        NSEC_PER_SEC nanoseconds
	 *        ------------------------
	 *              2^6 ticks
	 *
	 *    "rate" bytes   "burst" nanoseconds            2^6 ticks
	 *  = ------------ * ------------------- * ------------------------
	 *      1 second          2^6 ticks        NSEC_PER_SEC nanoseconds
	 *
	 *   "rate" * "burst"
	 * = ---------------- bytes/nanosecond
	 *    NSEC_PER_SEC^2
	 *
	 *
	 *   "rate" * "burst"
	 * = ---------------- bytes/second
	 *     NSEC_PER_SEC
	 */
	burst = भाग_u64(params->tcfp_burst * params->rate.rate_bytes_ps,
			NSEC_PER_SEC);

	वापस burst;
पूर्ण

अटल अंतरभूत u64 tcf_police_rate_pkt_ps(स्थिर काष्ठा tc_action *act)
अणु
	काष्ठा tcf_police *police = to_police(act);
	काष्ठा tcf_police_params *params;

	params = rcu_dereference_रक्षित(police->params,
					   lockdep_is_held(&police->tcf_lock));
	वापस params->ppsrate.rate_pkts_ps;
पूर्ण

अटल अंतरभूत u32 tcf_police_burst_pkt(स्थिर काष्ठा tc_action *act)
अणु
	काष्ठा tcf_police *police = to_police(act);
	काष्ठा tcf_police_params *params;
	u32 burst;

	params = rcu_dereference_रक्षित(police->params,
					   lockdep_is_held(&police->tcf_lock));

	/*
	 *  "rate" pkts     "burst" nanoseconds
	 *  ------------ *  -------------------
	 *    1 second          2^6 ticks
	 *
	 * ------------------------------------
	 *        NSEC_PER_SEC nanoseconds
	 *        ------------------------
	 *              2^6 ticks
	 *
	 *    "rate" pkts    "burst" nanoseconds            2^6 ticks
	 *  = ------------ * ------------------- * ------------------------
	 *      1 second          2^6 ticks        NSEC_PER_SEC nanoseconds
	 *
	 *   "rate" * "burst"
	 * = ---------------- pkts/nanosecond
	 *    NSEC_PER_SEC^2
	 *
	 *
	 *   "rate" * "burst"
	 * = ---------------- pkts/second
	 *     NSEC_PER_SEC
	 */
	burst = भाग_u64(params->tcfp_pkt_burst * params->ppsrate.rate_pkts_ps,
			NSEC_PER_SEC);

	वापस burst;
पूर्ण

अटल अंतरभूत u32 tcf_police_tcfp_mtu(स्थिर काष्ठा tc_action *act)
अणु
	काष्ठा tcf_police *police = to_police(act);
	काष्ठा tcf_police_params *params;

	params = rcu_dereference_रक्षित(police->params,
					   lockdep_is_held(&police->tcf_lock));
	वापस params->tcfp_mtu;
पूर्ण

#पूर्ण_अगर /* __NET_TC_POLICE_H */
