<शैली गुरु>
/*
 * Copyright (c) 2016, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/dim.h>
#समावेश "en.h"

अटल व्योम
mlx5e_complete_dim_work(काष्ठा dim *dim, काष्ठा dim_cq_moder moder,
			काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5_core_cq *mcq)
अणु
	mlx5_core_modअगरy_cq_moderation(mdev, mcq, moder.usec, moder.pkts);
	dim->state = DIM_START_MEASURE;
पूर्ण

व्योम mlx5e_rx_dim_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dim *dim = container_of(work, काष्ठा dim, work);
	काष्ठा mlx5e_rq *rq = container_of(dim, काष्ठा mlx5e_rq, dim);
	काष्ठा dim_cq_moder cur_moder =
		net_dim_get_rx_moderation(dim->mode, dim->profile_ix);

	mlx5e_complete_dim_work(dim, cur_moder, rq->mdev, &rq->cq.mcq);
पूर्ण

व्योम mlx5e_tx_dim_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dim *dim = container_of(work, काष्ठा dim, work);
	काष्ठा mlx5e_txqsq *sq = container_of(dim, काष्ठा mlx5e_txqsq, dim);
	काष्ठा dim_cq_moder cur_moder =
		net_dim_get_tx_moderation(dim->mode, dim->profile_ix);

	mlx5e_complete_dim_work(dim, cur_moder, sq->cq.mdev, &sq->cq.mcq);
पूर्ण
