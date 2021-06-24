<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश "tx.h"
#समावेश "pool.h"
#समावेश "en/xdp.h"
#समावेश "en/params.h"
#समावेश <net/xdp_sock_drv.h>

पूर्णांक mlx5e_xsk_wakeup(काष्ठा net_device *dev, u32 qid, u32 flags)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5e_params *params = &priv->channels.params;
	काष्ठा mlx5e_channel *c;
	u16 ix;

	अगर (unlikely(!mlx5e_xdp_is_active(priv)))
		वापस -ENETDOWN;

	अगर (unlikely(!mlx5e_qid_get_ch_अगर_in_group(params, qid, MLX5E_RQ_GROUP_XSK, &ix)))
		वापस -EINVAL;

	c = priv->channels.c[ix];

	अगर (unlikely(!test_bit(MLX5E_CHANNEL_STATE_XSK, c->state)))
		वापस -ENXIO;

	अगर (!napi_अगर_scheduled_mark_missed(&c->napi)) अणु
		/* To aव्योम WQE overrun, करोn't post a NOP अगर async_icosq is not
		 * active and not polled by NAPI. Return 0, because the upcoming
		 * activate will trigger the IRQ क्रम us.
		 */
		अगर (unlikely(!test_bit(MLX5E_SQ_STATE_ENABLED, &c->async_icosq.state)))
			वापस 0;

		अगर (test_and_set_bit(MLX5E_SQ_STATE_PENDING_XSK_TX, &c->async_icosq.state))
			वापस 0;

		spin_lock_bh(&c->async_icosq_lock);
		mlx5e_trigger_irq(&c->async_icosq);
		spin_unlock_bh(&c->async_icosq_lock);
	पूर्ण

	वापस 0;
पूर्ण

/* When TX fails (because of the size of the packet), we need to get completions
 * in order, so post a NOP to get a CQE. Since AF_XDP करोesn't distinguish
 * between successful TX and errors, handling in mlx5e_poll_xdpsq_cq is the
 * same.
 */
अटल व्योम mlx5e_xsk_tx_post_err(काष्ठा mlx5e_xdpsq *sq,
				  काष्ठा mlx5e_xdp_info *xdpi)
अणु
	u16 pi = mlx5_wq_cyc_ctr2ix(&sq->wq, sq->pc);
	काष्ठा mlx5e_xdp_wqe_info *wi = &sq->db.wqe_info[pi];
	काष्ठा mlx5e_tx_wqe *nopwqe;

	wi->num_wqebbs = 1;
	wi->num_pkts = 1;

	nopwqe = mlx5e_post_nop(&sq->wq, sq->sqn, &sq->pc);
	mlx5e_xdpi_fअगरo_push(&sq->db.xdpi_fअगरo, xdpi);
	sq->करोorbell_cseg = &nopwqe->ctrl;
पूर्ण

bool mlx5e_xsk_tx(काष्ठा mlx5e_xdpsq *sq, अचिन्हित पूर्णांक budget)
अणु
	काष्ठा xsk_buff_pool *pool = sq->xsk_pool;
	काष्ठा mlx5e_xmit_data xdptxd;
	काष्ठा mlx5e_xdp_info xdpi;
	bool work_करोne = true;
	bool flush = false;

	xdpi.mode = MLX5E_XDP_XMIT_MODE_XSK;

	क्रम (; budget; budget--) अणु
		पूर्णांक check_result = INसूचीECT_CALL_2(sq->xmit_xdp_frame_check,
						   mlx5e_xmit_xdp_frame_check_mpwqe,
						   mlx5e_xmit_xdp_frame_check,
						   sq);
		काष्ठा xdp_desc desc;
		bool ret;

		अगर (unlikely(check_result < 0)) अणु
			work_करोne = false;
			अवरोध;
		पूर्ण

		अगर (!xsk_tx_peek_desc(pool, &desc)) अणु
			/* TX will get stuck until something wakes it up by
			 * triggering NAPI. Currently it's expected that the
			 * application calls sendto() अगर there are consumed, but
			 * not completed frames.
			 */
			अवरोध;
		पूर्ण

		xdptxd.dma_addr = xsk_buff_raw_get_dma(pool, desc.addr);
		xdptxd.data = xsk_buff_raw_get_data(pool, desc.addr);
		xdptxd.len = desc.len;

		xsk_buff_raw_dma_sync_क्रम_device(pool, xdptxd.dma_addr, xdptxd.len);

		ret = INसूचीECT_CALL_2(sq->xmit_xdp_frame, mlx5e_xmit_xdp_frame_mpwqe,
				      mlx5e_xmit_xdp_frame, sq, &xdptxd, &xdpi, check_result);
		अगर (unlikely(!ret)) अणु
			अगर (sq->mpwqe.wqe)
				mlx5e_xdp_mpwqe_complete(sq);

			mlx5e_xsk_tx_post_err(sq, &xdpi);
		पूर्ण

		flush = true;
	पूर्ण

	अगर (flush) अणु
		अगर (sq->mpwqe.wqe)
			mlx5e_xdp_mpwqe_complete(sq);
		mlx5e_xmit_xdp_करोorbell(sq);

		xsk_tx_release(pool);
	पूर्ण

	वापस !(budget && work_करोne);
पूर्ण
