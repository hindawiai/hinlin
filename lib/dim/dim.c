<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2019, Mellanox Technologies inc.  All rights reserved.
 */

#समावेश <linux/dim.h>

bool dim_on_top(काष्ठा dim *dim)
अणु
	चयन (dim->tune_state) अणु
	हाल DIM_PARKING_ON_TOP:
	हाल DIM_PARKING_TIRED:
		वापस true;
	हाल DIM_GOING_RIGHT:
		वापस (dim->steps_left > 1) && (dim->steps_right == 1);
	शेष: /* DIM_GOING_LEFT */
		वापस (dim->steps_right > 1) && (dim->steps_left == 1);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dim_on_top);

व्योम dim_turn(काष्ठा dim *dim)
अणु
	चयन (dim->tune_state) अणु
	हाल DIM_PARKING_ON_TOP:
	हाल DIM_PARKING_TIRED:
		अवरोध;
	हाल DIM_GOING_RIGHT:
		dim->tune_state = DIM_GOING_LEFT;
		dim->steps_left = 0;
		अवरोध;
	हाल DIM_GOING_LEFT:
		dim->tune_state = DIM_GOING_RIGHT;
		dim->steps_right = 0;
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dim_turn);

व्योम dim_park_on_top(काष्ठा dim *dim)
अणु
	dim->steps_right  = 0;
	dim->steps_left   = 0;
	dim->tired        = 0;
	dim->tune_state   = DIM_PARKING_ON_TOP;
पूर्ण
EXPORT_SYMBOL(dim_park_on_top);

व्योम dim_park_tired(काष्ठा dim *dim)
अणु
	dim->steps_right  = 0;
	dim->steps_left   = 0;
	dim->tune_state   = DIM_PARKING_TIRED;
पूर्ण
EXPORT_SYMBOL(dim_park_tired);

व्योम dim_calc_stats(काष्ठा dim_sample *start, काष्ठा dim_sample *end,
		    काष्ठा dim_stats *curr_stats)
अणु
	/* u32 holds up to 71 minutes, should be enough */
	u32 delta_us = kसमय_us_delta(end->समय, start->समय);
	u32 npkts = BIT_GAP(BITS_PER_TYPE(u32), end->pkt_ctr, start->pkt_ctr);
	u32 nbytes = BIT_GAP(BITS_PER_TYPE(u32), end->byte_ctr,
			     start->byte_ctr);
	u32 ncomps = BIT_GAP(BITS_PER_TYPE(u32), end->comp_ctr,
			     start->comp_ctr);

	अगर (!delta_us)
		वापस;

	curr_stats->ppms = DIV_ROUND_UP(npkts * USEC_PER_MSEC, delta_us);
	curr_stats->bpms = DIV_ROUND_UP(nbytes * USEC_PER_MSEC, delta_us);
	curr_stats->epms = DIV_ROUND_UP(DIM_NEVENTS * USEC_PER_MSEC,
					delta_us);
	curr_stats->cpms = DIV_ROUND_UP(ncomps * USEC_PER_MSEC, delta_us);
	अगर (curr_stats->epms != 0)
		curr_stats->cpe_ratio = DIV_ROUND_DOWN_ULL(
			curr_stats->cpms * 100, curr_stats->epms);
	अन्यथा
		curr_stats->cpe_ratio = 0;

पूर्ण
EXPORT_SYMBOL(dim_calc_stats);
