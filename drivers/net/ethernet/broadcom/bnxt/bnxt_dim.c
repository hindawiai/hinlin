<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2017-2018 Broadcom Limited
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#समावेश <linux/dim.h>
#समावेश "bnxt_hsi.h"
#समावेश "bnxt.h"

व्योम bnxt_dim_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dim *dim = container_of(work, काष्ठा dim, work);
	काष्ठा bnxt_cp_ring_info *cpr = container_of(dim,
						     काष्ठा bnxt_cp_ring_info,
						     dim);
	काष्ठा bnxt_napi *bnapi = container_of(cpr,
					       काष्ठा bnxt_napi,
					       cp_ring);
	काष्ठा dim_cq_moder cur_moder =
		net_dim_get_rx_moderation(dim->mode, dim->profile_ix);

	cpr->rx_ring_coal.coal_ticks = cur_moder.usec;
	cpr->rx_ring_coal.coal_bufs = cur_moder.pkts;

	bnxt_hwrm_set_ring_coal(bnapi->bp, bnapi);
	dim->state = DIM_START_MEASURE;
पूर्ण
