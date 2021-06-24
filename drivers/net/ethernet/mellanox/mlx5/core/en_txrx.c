<शैली गुरु>
/*
 * Copyright (c) 2015, Mellanox Technologies. All rights reserved.
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

#समावेश <linux/irq.h>
#समावेश "en.h"
#समावेश "en/txrx.h"
#समावेश "en/xdp.h"
#समावेश "en/xsk/rx.h"
#समावेश "en/xsk/tx.h"
#समावेश "en_accel/ktls_txrx.h"

अटल अंतरभूत bool mlx5e_channel_no_affinity_change(काष्ठा mlx5e_channel *c)
अणु
	पूर्णांक current_cpu = smp_processor_id();

	वापस cpumask_test_cpu(current_cpu, c->aff_mask);
पूर्ण

अटल व्योम mlx5e_handle_tx_dim(काष्ठा mlx5e_txqsq *sq)
अणु
	काष्ठा mlx5e_sq_stats *stats = sq->stats;
	काष्ठा dim_sample dim_sample = अणुपूर्ण;

	अगर (unlikely(!test_bit(MLX5E_SQ_STATE_AM, &sq->state)))
		वापस;

	dim_update_sample(sq->cq.event_ctr, stats->packets, stats->bytes, &dim_sample);
	net_dim(&sq->dim, dim_sample);
पूर्ण

अटल व्योम mlx5e_handle_rx_dim(काष्ठा mlx5e_rq *rq)
अणु
	काष्ठा mlx5e_rq_stats *stats = rq->stats;
	काष्ठा dim_sample dim_sample = अणुपूर्ण;

	अगर (unlikely(!test_bit(MLX5E_RQ_STATE_AM, &rq->state)))
		वापस;

	dim_update_sample(rq->cq.event_ctr, stats->packets, stats->bytes, &dim_sample);
	net_dim(&rq->dim, dim_sample);
पूर्ण

व्योम mlx5e_trigger_irq(काष्ठा mlx5e_icosq *sq)
अणु
	काष्ठा mlx5_wq_cyc *wq = &sq->wq;
	काष्ठा mlx5e_tx_wqe *nopwqe;
	u16 pi = mlx5_wq_cyc_ctr2ix(wq, sq->pc);

	sq->db.wqe_info[pi] = (काष्ठा mlx5e_icosq_wqe_info) अणु
		.wqe_type   = MLX5E_ICOSQ_WQE_NOP,
		.num_wqebbs = 1,
	पूर्ण;

	nopwqe = mlx5e_post_nop(wq, sq->sqn, &sq->pc);
	mlx5e_notअगरy_hw(wq, sq->pc, sq->uar_map, &nopwqe->ctrl);
पूर्ण

अटल bool mlx5e_napi_xsk_post(काष्ठा mlx5e_xdpsq *xsksq, काष्ठा mlx5e_rq *xskrq)
अणु
	bool busy_xsk = false, xsk_rx_alloc_err;

	/* Handle the race between the application querying need_wakeup and the
	 * driver setting it:
	 * 1. Update need_wakeup both beक्रमe and after the TX. If it goes to
	 * "yes", it can only happen with the first update.
	 * 2. If the application queried need_wakeup beक्रमe we set it, the
	 * packets will be transmitted anyway, even w/o a wakeup.
	 * 3. Give a chance to clear need_wakeup after new packets were queued
	 * क्रम TX.
	 */
	mlx5e_xsk_update_tx_wakeup(xsksq);
	busy_xsk |= mlx5e_xsk_tx(xsksq, MLX5E_TX_XSK_POLL_BUDGET);
	mlx5e_xsk_update_tx_wakeup(xsksq);

	xsk_rx_alloc_err = INसूचीECT_CALL_2(xskrq->post_wqes,
					   mlx5e_post_rx_mpwqes,
					   mlx5e_post_rx_wqes,
					   xskrq);
	busy_xsk |= mlx5e_xsk_update_rx_wakeup(xskrq, xsk_rx_alloc_err);

	वापस busy_xsk;
पूर्ण

पूर्णांक mlx5e_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा mlx5e_channel *c = container_of(napi, काष्ठा mlx5e_channel,
					       napi);
	काष्ठा mlx5e_ch_stats *ch_stats = c->stats;
	काष्ठा mlx5e_xdpsq *xsksq = &c->xsksq;
	काष्ठा mlx5e_txqsq __rcu **qos_sqs;
	काष्ठा mlx5e_rq *xskrq = &c->xskrq;
	काष्ठा mlx5e_rq *rq = &c->rq;
	bool aff_change = false;
	bool busy_xsk = false;
	bool busy = false;
	पूर्णांक work_करोne = 0;
	u16 qos_sqs_size;
	bool xsk_खोलो;
	पूर्णांक i;

	rcu_पढ़ो_lock();

	qos_sqs = rcu_dereference(c->qos_sqs);

	xsk_खोलो = test_bit(MLX5E_CHANNEL_STATE_XSK, c->state);

	ch_stats->poll++;

	क्रम (i = 0; i < c->num_tc; i++)
		busy |= mlx5e_poll_tx_cq(&c->sq[i].cq, budget);

	अगर (unlikely(qos_sqs)) अणु
		smp_rmb(); /* Pairs with mlx5e_qos_alloc_queues. */
		qos_sqs_size = READ_ONCE(c->qos_sqs_size);

		क्रम (i = 0; i < qos_sqs_size; i++) अणु
			काष्ठा mlx5e_txqsq *sq = rcu_dereference(qos_sqs[i]);

			अगर (sq)
				busy |= mlx5e_poll_tx_cq(&sq->cq, budget);
		पूर्ण
	पूर्ण

	busy |= mlx5e_poll_xdpsq_cq(&c->xdpsq.cq);

	अगर (c->xdp)
		busy |= mlx5e_poll_xdpsq_cq(&c->rq_xdpsq.cq);

	अगर (likely(budget)) अणु /* budget=0 means: करोn't poll rx rings */
		अगर (xsk_खोलो)
			work_करोne = mlx5e_poll_rx_cq(&xskrq->cq, budget);

		अगर (likely(budget - work_करोne))
			work_करोne += mlx5e_poll_rx_cq(&rq->cq, budget - work_करोne);

		busy |= work_करोne == budget;
	पूर्ण

	mlx5e_poll_ico_cq(&c->icosq.cq);
	अगर (mlx5e_poll_ico_cq(&c->async_icosq.cq))
		/* Don't clear the flag अगर nothing was polled to prevent
		 * queueing more WQEs and overflowing the async ICOSQ.
		 */
		clear_bit(MLX5E_SQ_STATE_PENDING_XSK_TX, &c->async_icosq.state);

	/* Keep after async ICOSQ CQ poll */
	अगर (unlikely(mlx5e_ktls_rx_pending_resync_list(c, budget)))
		busy |= mlx5e_ktls_rx_handle_resync_list(c, budget);

	busy |= INसूचीECT_CALL_2(rq->post_wqes,
				mlx5e_post_rx_mpwqes,
				mlx5e_post_rx_wqes,
				rq);
	अगर (xsk_खोलो) अणु
		busy |= mlx5e_poll_xdpsq_cq(&xsksq->cq);
		busy_xsk |= mlx5e_napi_xsk_post(xsksq, xskrq);
	पूर्ण

	busy |= busy_xsk;

	अगर (busy) अणु
		अगर (likely(mlx5e_channel_no_affinity_change(c))) अणु
			work_करोne = budget;
			जाओ out;
		पूर्ण
		ch_stats->aff_change++;
		aff_change = true;
		अगर (budget && work_करोne == budget)
			work_करोne--;
	पूर्ण

	अगर (unlikely(!napi_complete_करोne(napi, work_करोne)))
		जाओ out;

	ch_stats->arm++;

	क्रम (i = 0; i < c->num_tc; i++) अणु
		mlx5e_handle_tx_dim(&c->sq[i]);
		mlx5e_cq_arm(&c->sq[i].cq);
	पूर्ण
	अगर (unlikely(qos_sqs)) अणु
		क्रम (i = 0; i < qos_sqs_size; i++) अणु
			काष्ठा mlx5e_txqsq *sq = rcu_dereference(qos_sqs[i]);

			अगर (sq) अणु
				mlx5e_handle_tx_dim(sq);
				mlx5e_cq_arm(&sq->cq);
			पूर्ण
		पूर्ण
	पूर्ण

	mlx5e_handle_rx_dim(rq);

	mlx5e_cq_arm(&rq->cq);
	mlx5e_cq_arm(&c->icosq.cq);
	mlx5e_cq_arm(&c->async_icosq.cq);
	mlx5e_cq_arm(&c->xdpsq.cq);

	अगर (xsk_खोलो) अणु
		mlx5e_handle_rx_dim(xskrq);
		mlx5e_cq_arm(&xsksq->cq);
		mlx5e_cq_arm(&xskrq->cq);
	पूर्ण

	अगर (unlikely(aff_change && busy_xsk)) अणु
		mlx5e_trigger_irq(&c->icosq);
		ch_stats->क्रमce_irq++;
	पूर्ण

out:
	rcu_पढ़ो_unlock();

	वापस work_करोne;
पूर्ण

व्योम mlx5e_completion_event(काष्ठा mlx5_core_cq *mcq, काष्ठा mlx5_eqe *eqe)
अणु
	काष्ठा mlx5e_cq *cq = container_of(mcq, काष्ठा mlx5e_cq, mcq);

	napi_schedule(cq->napi);
	cq->event_ctr++;
	cq->ch_stats->events++;
पूर्ण

व्योम mlx5e_cq_error_event(काष्ठा mlx5_core_cq *mcq, क्रमागत mlx5_event event)
अणु
	काष्ठा mlx5e_cq *cq = container_of(mcq, काष्ठा mlx5e_cq, mcq);
	काष्ठा net_device *netdev = cq->netdev;

	netdev_err(netdev, "%s: cqn=0x%.6x event=0x%.2x\n",
		   __func__, mcq->cqn, event);
पूर्ण
