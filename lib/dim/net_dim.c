<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2018, Mellanox Technologies inc.  All rights reserved.
 */

#समावेश <linux/dim.h>

/*
 * Net DIM profiles:
 *        There are dअगरferent set of profiles क्रम each CQ period mode.
 *        There are dअगरferent set of profiles क्रम RX/TX CQs.
 *        Each profile size must be of NET_DIM_PARAMS_NUM_PROखाताS
 */
#घोषणा NET_DIM_PARAMS_NUM_PROखाताS 5
#घोषणा NET_DIM_DEFAULT_RX_CQ_MODERATION_PKTS_FROM_EQE 256
#घोषणा NET_DIM_DEFAULT_TX_CQ_MODERATION_PKTS_FROM_EQE 128
#घोषणा NET_DIM_DEF_PROखाता_CQE 1
#घोषणा NET_DIM_DEF_PROखाता_EQE 1

#घोषणा NET_DIM_RX_EQE_PROखाताS अणु \
	अणु1,   NET_DIM_DEFAULT_RX_CQ_MODERATION_PKTS_FROM_EQEपूर्ण, \
	अणु8,   NET_DIM_DEFAULT_RX_CQ_MODERATION_PKTS_FROM_EQEपूर्ण, \
	अणु64,  NET_DIM_DEFAULT_RX_CQ_MODERATION_PKTS_FROM_EQEपूर्ण, \
	अणु128, NET_DIM_DEFAULT_RX_CQ_MODERATION_PKTS_FROM_EQEपूर्ण, \
	अणु256, NET_DIM_DEFAULT_RX_CQ_MODERATION_PKTS_FROM_EQEपूर्ण, \
पूर्ण

#घोषणा NET_DIM_RX_CQE_PROखाताS अणु \
	अणु2,  256पूर्ण,             \
	अणु8,  128पूर्ण,             \
	अणु16, 64पूर्ण,              \
	अणु32, 64पूर्ण,              \
	अणु64, 64पूर्ण               \
पूर्ण

#घोषणा NET_DIM_TX_EQE_PROखाताS अणु \
	अणु1,   NET_DIM_DEFAULT_TX_CQ_MODERATION_PKTS_FROM_EQEपूर्ण,  \
	अणु8,   NET_DIM_DEFAULT_TX_CQ_MODERATION_PKTS_FROM_EQEपूर्ण,  \
	अणु32,  NET_DIM_DEFAULT_TX_CQ_MODERATION_PKTS_FROM_EQEपूर्ण,  \
	अणु64,  NET_DIM_DEFAULT_TX_CQ_MODERATION_PKTS_FROM_EQEपूर्ण,  \
	अणु128, NET_DIM_DEFAULT_TX_CQ_MODERATION_PKTS_FROM_EQEपूर्ण   \
पूर्ण

#घोषणा NET_DIM_TX_CQE_PROखाताS अणु \
	अणु5,  128पूर्ण,  \
	अणु8,  64पूर्ण,  \
	अणु16, 32पूर्ण,  \
	अणु32, 32पूर्ण,  \
	अणु64, 32पूर्ण   \
पूर्ण

अटल स्थिर काष्ठा dim_cq_moder
rx_profile[DIM_CQ_PERIOD_NUM_MODES][NET_DIM_PARAMS_NUM_PROखाताS] = अणु
	NET_DIM_RX_EQE_PROखाताS,
	NET_DIM_RX_CQE_PROखाताS,
पूर्ण;

अटल स्थिर काष्ठा dim_cq_moder
tx_profile[DIM_CQ_PERIOD_NUM_MODES][NET_DIM_PARAMS_NUM_PROखाताS] = अणु
	NET_DIM_TX_EQE_PROखाताS,
	NET_DIM_TX_CQE_PROखाताS,
पूर्ण;

काष्ठा dim_cq_moder
net_dim_get_rx_moderation(u8 cq_period_mode, पूर्णांक ix)
अणु
	काष्ठा dim_cq_moder cq_moder = rx_profile[cq_period_mode][ix];

	cq_moder.cq_period_mode = cq_period_mode;
	वापस cq_moder;
पूर्ण
EXPORT_SYMBOL(net_dim_get_rx_moderation);

काष्ठा dim_cq_moder
net_dim_get_def_rx_moderation(u8 cq_period_mode)
अणु
	u8 profile_ix = cq_period_mode == DIM_CQ_PERIOD_MODE_START_FROM_CQE ?
			NET_DIM_DEF_PROखाता_CQE : NET_DIM_DEF_PROखाता_EQE;

	वापस net_dim_get_rx_moderation(cq_period_mode, profile_ix);
पूर्ण
EXPORT_SYMBOL(net_dim_get_def_rx_moderation);

काष्ठा dim_cq_moder
net_dim_get_tx_moderation(u8 cq_period_mode, पूर्णांक ix)
अणु
	काष्ठा dim_cq_moder cq_moder = tx_profile[cq_period_mode][ix];

	cq_moder.cq_period_mode = cq_period_mode;
	वापस cq_moder;
पूर्ण
EXPORT_SYMBOL(net_dim_get_tx_moderation);

काष्ठा dim_cq_moder
net_dim_get_def_tx_moderation(u8 cq_period_mode)
अणु
	u8 profile_ix = cq_period_mode == DIM_CQ_PERIOD_MODE_START_FROM_CQE ?
			NET_DIM_DEF_PROखाता_CQE : NET_DIM_DEF_PROखाता_EQE;

	वापस net_dim_get_tx_moderation(cq_period_mode, profile_ix);
पूर्ण
EXPORT_SYMBOL(net_dim_get_def_tx_moderation);

अटल पूर्णांक net_dim_step(काष्ठा dim *dim)
अणु
	अगर (dim->tired == (NET_DIM_PARAMS_NUM_PROखाताS * 2))
		वापस DIM_TOO_TIRED;

	चयन (dim->tune_state) अणु
	हाल DIM_PARKING_ON_TOP:
	हाल DIM_PARKING_TIRED:
		अवरोध;
	हाल DIM_GOING_RIGHT:
		अगर (dim->profile_ix == (NET_DIM_PARAMS_NUM_PROखाताS - 1))
			वापस DIM_ON_EDGE;
		dim->profile_ix++;
		dim->steps_right++;
		अवरोध;
	हाल DIM_GOING_LEFT:
		अगर (dim->profile_ix == 0)
			वापस DIM_ON_EDGE;
		dim->profile_ix--;
		dim->steps_left++;
		अवरोध;
	पूर्ण

	dim->tired++;
	वापस DIM_STEPPED;
पूर्ण

अटल व्योम net_dim_निकास_parking(काष्ठा dim *dim)
अणु
	dim->tune_state = dim->profile_ix ? DIM_GOING_LEFT : DIM_GOING_RIGHT;
	net_dim_step(dim);
पूर्ण

अटल पूर्णांक net_dim_stats_compare(काष्ठा dim_stats *curr,
				 काष्ठा dim_stats *prev)
अणु
	अगर (!prev->bpms)
		वापस curr->bpms ? DIM_STATS_BETTER : DIM_STATS_SAME;

	अगर (IS_SIGNIFICANT_DIFF(curr->bpms, prev->bpms))
		वापस (curr->bpms > prev->bpms) ? DIM_STATS_BETTER :
						   DIM_STATS_WORSE;

	अगर (!prev->ppms)
		वापस curr->ppms ? DIM_STATS_BETTER :
				    DIM_STATS_SAME;

	अगर (IS_SIGNIFICANT_DIFF(curr->ppms, prev->ppms))
		वापस (curr->ppms > prev->ppms) ? DIM_STATS_BETTER :
						   DIM_STATS_WORSE;

	अगर (!prev->epms)
		वापस DIM_STATS_SAME;

	अगर (IS_SIGNIFICANT_DIFF(curr->epms, prev->epms))
		वापस (curr->epms < prev->epms) ? DIM_STATS_BETTER :
						   DIM_STATS_WORSE;

	वापस DIM_STATS_SAME;
पूर्ण

अटल bool net_dim_decision(काष्ठा dim_stats *curr_stats, काष्ठा dim *dim)
अणु
	पूर्णांक prev_state = dim->tune_state;
	पूर्णांक prev_ix = dim->profile_ix;
	पूर्णांक stats_res;
	पूर्णांक step_res;

	चयन (dim->tune_state) अणु
	हाल DIM_PARKING_ON_TOP:
		stats_res = net_dim_stats_compare(curr_stats,
						  &dim->prev_stats);
		अगर (stats_res != DIM_STATS_SAME)
			net_dim_निकास_parking(dim);
		अवरोध;

	हाल DIM_PARKING_TIRED:
		dim->tired--;
		अगर (!dim->tired)
			net_dim_निकास_parking(dim);
		अवरोध;

	हाल DIM_GOING_RIGHT:
	हाल DIM_GOING_LEFT:
		stats_res = net_dim_stats_compare(curr_stats,
						  &dim->prev_stats);
		अगर (stats_res != DIM_STATS_BETTER)
			dim_turn(dim);

		अगर (dim_on_top(dim)) अणु
			dim_park_on_top(dim);
			अवरोध;
		पूर्ण

		step_res = net_dim_step(dim);
		चयन (step_res) अणु
		हाल DIM_ON_EDGE:
			dim_park_on_top(dim);
			अवरोध;
		हाल DIM_TOO_TIRED:
			dim_park_tired(dim);
			अवरोध;
		पूर्ण

		अवरोध;
	पूर्ण

	अगर (prev_state != DIM_PARKING_ON_TOP ||
	    dim->tune_state != DIM_PARKING_ON_TOP)
		dim->prev_stats = *curr_stats;

	वापस dim->profile_ix != prev_ix;
पूर्ण

व्योम net_dim(काष्ठा dim *dim, काष्ठा dim_sample end_sample)
अणु
	काष्ठा dim_stats curr_stats;
	u16 nevents;

	चयन (dim->state) अणु
	हाल DIM_MEASURE_IN_PROGRESS:
		nevents = BIT_GAP(BITS_PER_TYPE(u16),
				  end_sample.event_ctr,
				  dim->start_sample.event_ctr);
		अगर (nevents < DIM_NEVENTS)
			अवरोध;
		dim_calc_stats(&dim->start_sample, &end_sample, &curr_stats);
		अगर (net_dim_decision(&curr_stats, dim)) अणु
			dim->state = DIM_APPLY_NEW_PROखाता;
			schedule_work(&dim->work);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल DIM_START_MEASURE:
		dim_update_sample(end_sample.event_ctr, end_sample.pkt_ctr,
				  end_sample.byte_ctr, &dim->start_sample);
		dim->state = DIM_MEASURE_IN_PROGRESS;
		अवरोध;
	हाल DIM_APPLY_NEW_PROखाता:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(net_dim);
