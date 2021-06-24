<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2019, Mellanox Technologies inc.  All rights reserved.
 */

#समावेश <linux/dim.h>

अटल पूर्णांक rdma_dim_step(काष्ठा dim *dim)
अणु
	अगर (dim->tune_state == DIM_GOING_RIGHT) अणु
		अगर (dim->profile_ix == (RDMA_DIM_PARAMS_NUM_PROखाताS - 1))
			वापस DIM_ON_EDGE;
		dim->profile_ix++;
		dim->steps_right++;
	पूर्ण
	अगर (dim->tune_state == DIM_GOING_LEFT) अणु
		अगर (dim->profile_ix == 0)
			वापस DIM_ON_EDGE;
		dim->profile_ix--;
		dim->steps_left++;
	पूर्ण

	वापस DIM_STEPPED;
पूर्ण

अटल पूर्णांक rdma_dim_stats_compare(काष्ठा dim_stats *curr,
				  काष्ठा dim_stats *prev)
अणु
	/* first stat */
	अगर (!prev->cpms)
		वापस DIM_STATS_SAME;

	अगर (IS_SIGNIFICANT_DIFF(curr->cpms, prev->cpms))
		वापस (curr->cpms > prev->cpms) ? DIM_STATS_BETTER :
						DIM_STATS_WORSE;

	अगर (IS_SIGNIFICANT_DIFF(curr->cpe_ratio, prev->cpe_ratio))
		वापस (curr->cpe_ratio > prev->cpe_ratio) ? DIM_STATS_BETTER :
						DIM_STATS_WORSE;

	वापस DIM_STATS_SAME;
पूर्ण

अटल bool rdma_dim_decision(काष्ठा dim_stats *curr_stats, काष्ठा dim *dim)
अणु
	पूर्णांक prev_ix = dim->profile_ix;
	u8 state = dim->tune_state;
	पूर्णांक stats_res;
	पूर्णांक step_res;

	अगर (state != DIM_PARKING_ON_TOP && state != DIM_PARKING_TIRED) अणु
		stats_res = rdma_dim_stats_compare(curr_stats,
						   &dim->prev_stats);

		चयन (stats_res) अणु
		हाल DIM_STATS_SAME:
			अगर (curr_stats->cpe_ratio <= 50 * prev_ix)
				dim->profile_ix = 0;
			अवरोध;
		हाल DIM_STATS_WORSE:
			dim_turn(dim);
			fallthrough;
		हाल DIM_STATS_BETTER:
			step_res = rdma_dim_step(dim);
			अगर (step_res == DIM_ON_EDGE)
				dim_turn(dim);
			अवरोध;
		पूर्ण
	पूर्ण

	dim->prev_stats = *curr_stats;

	वापस dim->profile_ix != prev_ix;
पूर्ण

व्योम rdma_dim(काष्ठा dim *dim, u64 completions)
अणु
	काष्ठा dim_sample *curr_sample = &dim->measuring_sample;
	काष्ठा dim_stats curr_stats;
	u32 nevents;

	dim_update_sample_with_comps(curr_sample->event_ctr + 1, 0, 0,
				     curr_sample->comp_ctr + completions,
				     &dim->measuring_sample);

	चयन (dim->state) अणु
	हाल DIM_MEASURE_IN_PROGRESS:
		nevents = curr_sample->event_ctr - dim->start_sample.event_ctr;
		अगर (nevents < DIM_NEVENTS)
			अवरोध;
		dim_calc_stats(&dim->start_sample, curr_sample, &curr_stats);
		अगर (rdma_dim_decision(&curr_stats, dim)) अणु
			dim->state = DIM_APPLY_NEW_PROखाता;
			schedule_work(&dim->work);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल DIM_START_MEASURE:
		dim->state = DIM_MEASURE_IN_PROGRESS;
		dim_update_sample_with_comps(curr_sample->event_ctr, 0, 0,
					     curr_sample->comp_ctr,
					     &dim->start_sample);
		अवरोध;
	हाल DIM_APPLY_NEW_PROखाता:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rdma_dim);
