<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश "setup.h"
#समावेश "en/params.h"
#समावेश "en/txrx.h"

/* It matches XDP_UMEM_MIN_CHUNK_SIZE, but as this स्थिरant is निजी and may
 * change unexpectedly, and mlx5e has a minimum valid stride size क्रम striding
 * RQ, keep this check in the driver.
 */
#घोषणा MLX5E_MIN_XSK_CHUNK_SIZE 2048

bool mlx5e_validate_xsk_param(काष्ठा mlx5e_params *params,
			      काष्ठा mlx5e_xsk_param *xsk,
			      काष्ठा mlx5_core_dev *mdev)
अणु
	/* AF_XDP करोesn't support frames larger than PAGE_SIZE. */
	अगर (xsk->chunk_size > PAGE_SIZE ||
			xsk->chunk_size < MLX5E_MIN_XSK_CHUNK_SIZE)
		वापस false;

	/* Current MTU and XSK headroom करोn't allow packets to fit the frames. */
	अगर (mlx5e_rx_get_min_frag_sz(params, xsk) > xsk->chunk_size)
		वापस false;

	/* frag_sz is dअगरferent क्रम regular and XSK RQs, so ensure that linear
	 * SKB mode is possible.
	 */
	चयन (params->rq_wq_type) अणु
	हाल MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ:
		वापस mlx5e_rx_mpwqe_is_linear_skb(mdev, params, xsk);
	शेष: /* MLX5_WQ_TYPE_CYCLIC */
		वापस mlx5e_rx_is_linear_skb(params, xsk);
	पूर्ण
पूर्ण

अटल व्योम mlx5e_build_xsk_cparam(काष्ठा mlx5_core_dev *mdev,
				   काष्ठा mlx5e_params *params,
				   काष्ठा mlx5e_xsk_param *xsk,
				   u16 q_counter,
				   काष्ठा mlx5e_channel_param *cparam)
अणु
	mlx5e_build_rq_param(mdev, params, xsk, q_counter, &cparam->rq);
	mlx5e_build_xdpsq_param(mdev, params, &cparam->xdp_sq);
पूर्ण

अटल पूर्णांक mlx5e_init_xsk_rq(काष्ठा mlx5e_channel *c,
			     काष्ठा mlx5e_params *params,
			     काष्ठा xsk_buff_pool *pool,
			     काष्ठा mlx5e_xsk_param *xsk,
			     काष्ठा mlx5e_rq *rq)
अणु
	काष्ठा mlx5_core_dev *mdev = c->mdev;
	पूर्णांक rq_xdp_ix;
	पूर्णांक err;

	rq->wq_type      = params->rq_wq_type;
	rq->pdev         = c->pdev;
	rq->netdev       = c->netdev;
	rq->priv         = c->priv;
	rq->tstamp       = c->tstamp;
	rq->घड़ी        = &mdev->घड़ी;
	rq->icosq        = &c->icosq;
	rq->ix           = c->ix;
	rq->mdev         = mdev;
	rq->hw_mtu       = MLX5E_SW2HW_MTU(params, params->sw_mtu);
	rq->xdpsq        = &c->rq_xdpsq;
	rq->xsk_pool     = pool;
	rq->stats        = &c->priv->channel_stats[c->ix].xskrq;
	rq->ptp_cyc2समय = mlx5_rq_ts_translator(mdev);
	rq_xdp_ix        = c->ix + params->num_channels * MLX5E_RQ_GROUP_XSK;
	err = mlx5e_rq_set_handlers(rq, params, xsk);
	अगर (err)
		वापस err;

	वापस  xdp_rxq_info_reg(&rq->xdp_rxq, rq->netdev, rq_xdp_ix, 0);
पूर्ण

अटल पूर्णांक mlx5e_खोलो_xsk_rq(काष्ठा mlx5e_channel *c, काष्ठा mlx5e_params *params,
			     काष्ठा mlx5e_rq_param *rq_params, काष्ठा xsk_buff_pool *pool,
			     काष्ठा mlx5e_xsk_param *xsk)
अणु
	पूर्णांक err;

	err = mlx5e_init_xsk_rq(c, params, pool, xsk, &c->xskrq);
	अगर (err)
		वापस err;

	वापस mlx5e_खोलो_rq(params, rq_params, xsk, cpu_to_node(c->cpu), &c->xskrq);
पूर्ण

पूर्णांक mlx5e_खोलो_xsk(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_params *params,
		   काष्ठा mlx5e_xsk_param *xsk, काष्ठा xsk_buff_pool *pool,
		   काष्ठा mlx5e_channel *c)
अणु
	काष्ठा mlx5e_channel_param *cparam;
	काष्ठा mlx5e_create_cq_param ccp;
	पूर्णांक err;

	mlx5e_build_create_cq_param(&ccp, c);

	अगर (!mlx5e_validate_xsk_param(params, xsk, priv->mdev))
		वापस -EINVAL;

	cparam = kvzalloc(माप(*cparam), GFP_KERNEL);
	अगर (!cparam)
		वापस -ENOMEM;

	mlx5e_build_xsk_cparam(priv->mdev, params, xsk, priv->q_counter, cparam);

	err = mlx5e_खोलो_cq(c->priv, params->rx_cq_moderation, &cparam->rq.cqp, &ccp,
			    &c->xskrq.cq);
	अगर (unlikely(err))
		जाओ err_मुक्त_cparam;

	err = mlx5e_खोलो_xsk_rq(c, params, &cparam->rq, pool, xsk);
	अगर (unlikely(err))
		जाओ err_बंद_rx_cq;

	err = mlx5e_खोलो_cq(c->priv, params->tx_cq_moderation, &cparam->xdp_sq.cqp, &ccp,
			    &c->xsksq.cq);
	अगर (unlikely(err))
		जाओ err_बंद_rq;

	/* Create a separate SQ, so that when the buff pool is disabled, we could
	 * बंद this SQ safely and stop receiving CQEs. In other हाल, e.g., अगर
	 * the XDPSQ was used instead, we might run पूर्णांकo trouble when the buff pool
	 * is disabled and then reenabled, but the SQ जारीs receiving CQEs
	 * from the old buff pool.
	 */
	err = mlx5e_खोलो_xdpsq(c, params, &cparam->xdp_sq, pool, &c->xsksq, true);
	अगर (unlikely(err))
		जाओ err_बंद_tx_cq;

	kvमुक्त(cparam);

	set_bit(MLX5E_CHANNEL_STATE_XSK, c->state);

	वापस 0;

err_बंद_tx_cq:
	mlx5e_बंद_cq(&c->xsksq.cq);

err_बंद_rq:
	mlx5e_बंद_rq(&c->xskrq);

err_बंद_rx_cq:
	mlx5e_बंद_cq(&c->xskrq.cq);

err_मुक्त_cparam:
	kvमुक्त(cparam);

	वापस err;
पूर्ण

व्योम mlx5e_बंद_xsk(काष्ठा mlx5e_channel *c)
अणु
	clear_bit(MLX5E_CHANNEL_STATE_XSK, c->state);
	synchronize_net(); /* Sync with the XSK wakeup and with NAPI. */

	mlx5e_बंद_rq(&c->xskrq);
	mlx5e_बंद_cq(&c->xskrq.cq);
	mlx5e_बंद_xdpsq(&c->xsksq);
	mlx5e_बंद_cq(&c->xsksq.cq);

	स_रखो(&c->xskrq, 0, माप(c->xskrq));
	स_रखो(&c->xsksq, 0, माप(c->xsksq));
पूर्ण

व्योम mlx5e_activate_xsk(काष्ठा mlx5e_channel *c)
अणु
	set_bit(MLX5E_RQ_STATE_ENABLED, &c->xskrq.state);
	/* TX queue is created active. */

	spin_lock_bh(&c->async_icosq_lock);
	mlx5e_trigger_irq(&c->async_icosq);
	spin_unlock_bh(&c->async_icosq_lock);
पूर्ण

व्योम mlx5e_deactivate_xsk(काष्ठा mlx5e_channel *c)
अणु
	mlx5e_deactivate_rq(&c->xskrq);
	/* TX queue is disabled on बंद. */
पूर्ण

अटल पूर्णांक mlx5e_redirect_xsk_rqt(काष्ठा mlx5e_priv *priv, u16 ix, u32 rqn)
अणु
	काष्ठा mlx5e_redirect_rqt_param direct_rrp = अणु
		.is_rss = false,
		अणु
			.rqn = rqn,
		पूर्ण,
	पूर्ण;

	u32 rqtn = priv->xsk_tir[ix].rqt.rqtn;

	वापस mlx5e_redirect_rqt(priv, rqtn, 1, direct_rrp);
पूर्ण

पूर्णांक mlx5e_xsk_redirect_rqt_to_channel(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_channel *c)
अणु
	वापस mlx5e_redirect_xsk_rqt(priv, c->ix, c->xskrq.rqn);
पूर्ण

पूर्णांक mlx5e_xsk_redirect_rqt_to_drop(काष्ठा mlx5e_priv *priv, u16 ix)
अणु
	वापस mlx5e_redirect_xsk_rqt(priv, ix, priv->drop_rq.rqn);
पूर्ण

पूर्णांक mlx5e_xsk_redirect_rqts_to_channels(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_channels *chs)
अणु
	पूर्णांक err, i;

	अगर (!priv->xsk.refcnt)
		वापस 0;

	क्रम (i = 0; i < chs->num; i++) अणु
		काष्ठा mlx5e_channel *c = chs->c[i];

		अगर (!test_bit(MLX5E_CHANNEL_STATE_XSK, c->state))
			जारी;

		err = mlx5e_xsk_redirect_rqt_to_channel(priv, c);
		अगर (unlikely(err))
			जाओ err_stop;
	पूर्ण

	वापस 0;

err_stop:
	क्रम (i--; i >= 0; i--) अणु
		अगर (!test_bit(MLX5E_CHANNEL_STATE_XSK, chs->c[i]->state))
			जारी;

		mlx5e_xsk_redirect_rqt_to_drop(priv, i);
	पूर्ण

	वापस err;
पूर्ण

व्योम mlx5e_xsk_redirect_rqts_to_drop(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_channels *chs)
अणु
	पूर्णांक i;

	अगर (!priv->xsk.refcnt)
		वापस;

	क्रम (i = 0; i < chs->num; i++) अणु
		अगर (!test_bit(MLX5E_CHANNEL_STATE_XSK, chs->c[i]->state))
			जारी;

		mlx5e_xsk_redirect_rqt_to_drop(priv, i);
	पूर्ण
पूर्ण
