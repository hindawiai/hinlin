<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
// Copyright (c) 2020 Mellanox Technologies

#समावेश "en/ptp.h"
#समावेश "en/txrx.h"
#समावेश "en/params.h"
#समावेश "en/fs_tt_redirect.h"

काष्ठा mlx5e_ptp_fs अणु
	काष्ठा mlx5_flow_handle *l2_rule;
	काष्ठा mlx5_flow_handle *udp_v4_rule;
	काष्ठा mlx5_flow_handle *udp_v6_rule;
	bool valid;
पूर्ण;

#घोषणा MLX5E_PTP_CHANNEL_IX 0

काष्ठा mlx5e_ptp_params अणु
	काष्ठा mlx5e_params params;
	काष्ठा mlx5e_sq_param txq_sq_param;
	काष्ठा mlx5e_rq_param rq_param;
पूर्ण;

काष्ठा mlx5e_skb_cb_hwtstamp अणु
	kसमय_प्रकार cqe_hwtstamp;
	kसमय_प्रकार port_hwtstamp;
पूर्ण;

व्योम mlx5e_skb_cb_hwtstamp_init(काष्ठा sk_buff *skb)
अणु
	स_रखो(skb->cb, 0, माप(काष्ठा mlx5e_skb_cb_hwtstamp));
पूर्ण

अटल काष्ठा mlx5e_skb_cb_hwtstamp *mlx5e_skb_cb_get_hwts(काष्ठा sk_buff *skb)
अणु
	BUILD_BUG_ON(माप(काष्ठा mlx5e_skb_cb_hwtstamp) > माप(skb->cb));
	वापस (काष्ठा mlx5e_skb_cb_hwtstamp *)skb->cb;
पूर्ण

अटल व्योम mlx5e_skb_cb_hwtstamp_tx(काष्ठा sk_buff *skb,
				     काष्ठा mlx5e_ptp_cq_stats *cq_stats)
अणु
	काष्ठा skb_shared_hwtstamps hwts = अणुपूर्ण;
	kसमय_प्रकार dअगरf;

	dअगरf = असल(mlx5e_skb_cb_get_hwts(skb)->port_hwtstamp -
		   mlx5e_skb_cb_get_hwts(skb)->cqe_hwtstamp);

	/* Maximal allowed dअगरf is 1 / 128 second */
	अगर (dअगरf > (NSEC_PER_SEC >> 7)) अणु
		cq_stats->पात++;
		cq_stats->पात_असल_dअगरf_ns += dअगरf;
		वापस;
	पूर्ण

	hwts.hwtstamp = mlx5e_skb_cb_get_hwts(skb)->port_hwtstamp;
	skb_tstamp_tx(skb, &hwts);
पूर्ण

व्योम mlx5e_skb_cb_hwtstamp_handler(काष्ठा sk_buff *skb, पूर्णांक hwtstamp_type,
				   kसमय_प्रकार hwtstamp,
				   काष्ठा mlx5e_ptp_cq_stats *cq_stats)
अणु
	चयन (hwtstamp_type) अणु
	हाल (MLX5E_SKB_CB_CQE_HWTSTAMP):
		mlx5e_skb_cb_get_hwts(skb)->cqe_hwtstamp = hwtstamp;
		अवरोध;
	हाल (MLX5E_SKB_CB_PORT_HWTSTAMP):
		mlx5e_skb_cb_get_hwts(skb)->port_hwtstamp = hwtstamp;
		अवरोध;
	पूर्ण

	/* If both CQEs arrive, check and report the port tstamp, and clear skb cb as
	 * skb soon to be released.
	 */
	अगर (!mlx5e_skb_cb_get_hwts(skb)->cqe_hwtstamp ||
	    !mlx5e_skb_cb_get_hwts(skb)->port_hwtstamp)
		वापस;

	mlx5e_skb_cb_hwtstamp_tx(skb, cq_stats);
	स_रखो(skb->cb, 0, माप(काष्ठा mlx5e_skb_cb_hwtstamp));
पूर्ण

अटल व्योम mlx5e_ptp_handle_ts_cqe(काष्ठा mlx5e_ptpsq *ptpsq,
				    काष्ठा mlx5_cqe64 *cqe,
				    पूर्णांक budget)
अणु
	काष्ठा sk_buff *skb = mlx5e_skb_fअगरo_pop(&ptpsq->skb_fअगरo);
	काष्ठा mlx5e_txqsq *sq = &ptpsq->txqsq;
	kसमय_प्रकार hwtstamp;

	अगर (unlikely(MLX5E_RX_ERR_CQE(cqe))) अणु
		ptpsq->cq_stats->err_cqe++;
		जाओ out;
	पूर्ण

	hwtstamp = mlx5e_cqe_ts_to_ns(sq->ptp_cyc2समय, sq->घड़ी, get_cqe_ts(cqe));
	mlx5e_skb_cb_hwtstamp_handler(skb, MLX5E_SKB_CB_PORT_HWTSTAMP,
				      hwtstamp, ptpsq->cq_stats);
	ptpsq->cq_stats->cqe++;

out:
	napi_consume_skb(skb, budget);
पूर्ण

अटल bool mlx5e_ptp_poll_ts_cq(काष्ठा mlx5e_cq *cq, पूर्णांक budget)
अणु
	काष्ठा mlx5e_ptpsq *ptpsq = container_of(cq, काष्ठा mlx5e_ptpsq, ts_cq);
	काष्ठा mlx5_cqwq *cqwq = &cq->wq;
	काष्ठा mlx5_cqe64 *cqe;
	पूर्णांक work_करोne = 0;

	अगर (unlikely(!test_bit(MLX5E_SQ_STATE_ENABLED, &ptpsq->txqsq.state)))
		वापस false;

	cqe = mlx5_cqwq_get_cqe(cqwq);
	अगर (!cqe)
		वापस false;

	करो अणु
		mlx5_cqwq_pop(cqwq);

		mlx5e_ptp_handle_ts_cqe(ptpsq, cqe, budget);
	पूर्ण जबतक ((++work_करोne < budget) && (cqe = mlx5_cqwq_get_cqe(cqwq)));

	mlx5_cqwq_update_db_record(cqwq);

	/* ensure cq space is मुक्तd beक्रमe enabling more cqes */
	wmb();

	वापस work_करोne == budget;
पूर्ण

अटल पूर्णांक mlx5e_ptp_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा mlx5e_ptp *c = container_of(napi, काष्ठा mlx5e_ptp, napi);
	काष्ठा mlx5e_ch_stats *ch_stats = c->stats;
	काष्ठा mlx5e_rq *rq = &c->rq;
	bool busy = false;
	पूर्णांक work_करोne = 0;
	पूर्णांक i;

	rcu_पढ़ो_lock();

	ch_stats->poll++;

	अगर (test_bit(MLX5E_PTP_STATE_TX, c->state)) अणु
		क्रम (i = 0; i < c->num_tc; i++) अणु
			busy |= mlx5e_poll_tx_cq(&c->ptpsq[i].txqsq.cq, budget);
			busy |= mlx5e_ptp_poll_ts_cq(&c->ptpsq[i].ts_cq, budget);
		पूर्ण
	पूर्ण
	अगर (test_bit(MLX5E_PTP_STATE_RX, c->state) && likely(budget)) अणु
		work_करोne = mlx5e_poll_rx_cq(&rq->cq, budget);
		busy |= work_करोne == budget;
		busy |= INसूचीECT_CALL_2(rq->post_wqes,
					mlx5e_post_rx_mpwqes,
					mlx5e_post_rx_wqes,
					rq);
	पूर्ण

	अगर (busy) अणु
		work_करोne = budget;
		जाओ out;
	पूर्ण

	अगर (unlikely(!napi_complete_करोne(napi, work_करोne)))
		जाओ out;

	ch_stats->arm++;

	अगर (test_bit(MLX5E_PTP_STATE_TX, c->state)) अणु
		क्रम (i = 0; i < c->num_tc; i++) अणु
			mlx5e_cq_arm(&c->ptpsq[i].txqsq.cq);
			mlx5e_cq_arm(&c->ptpsq[i].ts_cq);
		पूर्ण
	पूर्ण
	अगर (test_bit(MLX5E_PTP_STATE_RX, c->state))
		mlx5e_cq_arm(&rq->cq);

out:
	rcu_पढ़ो_unlock();

	वापस work_करोne;
पूर्ण

अटल पूर्णांक mlx5e_ptp_alloc_txqsq(काष्ठा mlx5e_ptp *c, पूर्णांक txq_ix,
				 काष्ठा mlx5e_params *params,
				 काष्ठा mlx5e_sq_param *param,
				 काष्ठा mlx5e_txqsq *sq, पूर्णांक tc,
				 काष्ठा mlx5e_ptpsq *ptpsq)
अणु
	व्योम *sqc_wq               = MLX5_ADDR_OF(sqc, param->sqc, wq);
	काष्ठा mlx5_core_dev *mdev = c->mdev;
	काष्ठा mlx5_wq_cyc *wq = &sq->wq;
	पूर्णांक err;
	पूर्णांक node;

	sq->pdev      = c->pdev;
	sq->tstamp    = c->tstamp;
	sq->घड़ी     = &mdev->घड़ी;
	sq->mkey_be   = c->mkey_be;
	sq->netdev    = c->netdev;
	sq->priv      = c->priv;
	sq->mdev      = mdev;
	sq->ch_ix     = MLX5E_PTP_CHANNEL_IX;
	sq->txq_ix    = txq_ix;
	sq->uar_map   = mdev->mlx5e_res.hw_objs.bfreg.map;
	sq->min_अंतरभूत_mode = params->tx_min_अंतरभूत_mode;
	sq->hw_mtu    = MLX5E_SW2HW_MTU(params, params->sw_mtu);
	sq->stats     = &c->priv->ptp_stats.sq[tc];
	sq->ptpsq     = ptpsq;
	INIT_WORK(&sq->recover_work, mlx5e_tx_err_cqe_work);
	अगर (!MLX5_CAP_ETH(mdev, wqe_vlan_insert))
		set_bit(MLX5E_SQ_STATE_VLAN_NEED_L2_INLINE, &sq->state);
	sq->stop_room = param->stop_room;
	sq->ptp_cyc2समय = mlx5_sq_ts_translator(mdev);

	node = dev_to_node(mlx5_core_dma_dev(mdev));

	param->wq.db_numa_node = node;
	err = mlx5_wq_cyc_create(mdev, &param->wq, sqc_wq, wq, &sq->wq_ctrl);
	अगर (err)
		वापस err;
	wq->db    = &wq->db[MLX5_SND_DBR];

	err = mlx5e_alloc_txqsq_db(sq, node);
	अगर (err)
		जाओ err_sq_wq_destroy;

	वापस 0;

err_sq_wq_destroy:
	mlx5_wq_destroy(&sq->wq_ctrl);

	वापस err;
पूर्ण

अटल व्योम mlx5e_ptp_destroy_sq(काष्ठा mlx5_core_dev *mdev, u32 sqn)
अणु
	mlx5_core_destroy_sq(mdev, sqn);
पूर्ण

अटल पूर्णांक mlx5e_ptp_alloc_traffic_db(काष्ठा mlx5e_ptpsq *ptpsq, पूर्णांक numa)
अणु
	पूर्णांक wq_sz = mlx5_wq_cyc_get_size(&ptpsq->txqsq.wq);

	ptpsq->skb_fअगरo.fअगरo = kvzalloc_node(array_size(wq_sz, माप(*ptpsq->skb_fअगरo.fअगरo)),
					     GFP_KERNEL, numa);
	अगर (!ptpsq->skb_fअगरo.fअगरo)
		वापस -ENOMEM;

	ptpsq->skb_fअगरo.pc   = &ptpsq->skb_fअगरo_pc;
	ptpsq->skb_fअगरo.cc   = &ptpsq->skb_fअगरo_cc;
	ptpsq->skb_fअगरo.mask = wq_sz - 1;

	वापस 0;
पूर्ण

अटल व्योम mlx5e_ptp_drain_skb_fअगरo(काष्ठा mlx5e_skb_fअगरo *skb_fअगरo)
अणु
	जबतक (*skb_fअगरo->pc != *skb_fअगरo->cc) अणु
		काष्ठा sk_buff *skb = mlx5e_skb_fअगरo_pop(skb_fअगरo);

		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण

अटल व्योम mlx5e_ptp_मुक्त_traffic_db(काष्ठा mlx5e_skb_fअगरo *skb_fअगरo)
अणु
	mlx5e_ptp_drain_skb_fअगरo(skb_fअगरo);
	kvमुक्त(skb_fअगरo->fअगरo);
पूर्ण

अटल पूर्णांक mlx5e_ptp_खोलो_txqsq(काष्ठा mlx5e_ptp *c, u32 tisn,
				पूर्णांक txq_ix, काष्ठा mlx5e_ptp_params *cparams,
				पूर्णांक tc, काष्ठा mlx5e_ptpsq *ptpsq)
अणु
	काष्ठा mlx5e_sq_param *sqp = &cparams->txq_sq_param;
	काष्ठा mlx5e_txqsq *txqsq = &ptpsq->txqsq;
	काष्ठा mlx5e_create_sq_param csp = अणुपूर्ण;
	पूर्णांक err;

	err = mlx5e_ptp_alloc_txqsq(c, txq_ix, &cparams->params, sqp,
				    txqsq, tc, ptpsq);
	अगर (err)
		वापस err;

	csp.tisn            = tisn;
	csp.tis_lst_sz      = 1;
	csp.cqn             = txqsq->cq.mcq.cqn;
	csp.wq_ctrl         = &txqsq->wq_ctrl;
	csp.min_अंतरभूत_mode = txqsq->min_अंतरभूत_mode;
	csp.ts_cqe_to_dest_cqn = ptpsq->ts_cq.mcq.cqn;

	err = mlx5e_create_sq_rdy(c->mdev, sqp, &csp, 0, &txqsq->sqn);
	अगर (err)
		जाओ err_मुक्त_txqsq;

	err = mlx5e_ptp_alloc_traffic_db(ptpsq,
					 dev_to_node(mlx5_core_dma_dev(c->mdev)));
	अगर (err)
		जाओ err_मुक्त_txqsq;

	वापस 0;

err_मुक्त_txqsq:
	mlx5e_मुक्त_txqsq(txqsq);

	वापस err;
पूर्ण

अटल व्योम mlx5e_ptp_बंद_txqsq(काष्ठा mlx5e_ptpsq *ptpsq)
अणु
	काष्ठा mlx5e_txqsq *sq = &ptpsq->txqsq;
	काष्ठा mlx5_core_dev *mdev = sq->mdev;

	mlx5e_ptp_मुक्त_traffic_db(&ptpsq->skb_fअगरo);
	cancel_work_sync(&sq->recover_work);
	mlx5e_ptp_destroy_sq(mdev, sq->sqn);
	mlx5e_मुक्त_txqsq_descs(sq);
	mlx5e_मुक्त_txqsq(sq);
पूर्ण

अटल पूर्णांक mlx5e_ptp_खोलो_txqsqs(काष्ठा mlx5e_ptp *c,
				 काष्ठा mlx5e_ptp_params *cparams)
अणु
	काष्ठा mlx5e_params *params = &cparams->params;
	पूर्णांक ix_base;
	पूर्णांक err;
	पूर्णांक tc;

	ix_base = params->num_tc * params->num_channels;

	क्रम (tc = 0; tc < params->num_tc; tc++) अणु
		पूर्णांक txq_ix = ix_base + tc;

		err = mlx5e_ptp_खोलो_txqsq(c, c->priv->tisn[c->lag_port][tc], txq_ix,
					   cparams, tc, &c->ptpsq[tc]);
		अगर (err)
			जाओ बंद_txqsq;
	पूर्ण

	वापस 0;

बंद_txqsq:
	क्रम (--tc; tc >= 0; tc--)
		mlx5e_ptp_बंद_txqsq(&c->ptpsq[tc]);

	वापस err;
पूर्ण

अटल व्योम mlx5e_ptp_बंद_txqsqs(काष्ठा mlx5e_ptp *c)
अणु
	पूर्णांक tc;

	क्रम (tc = 0; tc < c->num_tc; tc++)
		mlx5e_ptp_बंद_txqsq(&c->ptpsq[tc]);
पूर्ण

अटल पूर्णांक mlx5e_ptp_खोलो_tx_cqs(काष्ठा mlx5e_ptp *c,
				 काष्ठा mlx5e_ptp_params *cparams)
अणु
	काष्ठा mlx5e_params *params = &cparams->params;
	काष्ठा mlx5e_create_cq_param ccp = अणुपूर्ण;
	काष्ठा dim_cq_moder ptp_moder = अणुपूर्ण;
	काष्ठा mlx5e_cq_param *cq_param;
	पूर्णांक err;
	पूर्णांक tc;

	ccp.node     = dev_to_node(mlx5_core_dma_dev(c->mdev));
	ccp.ch_stats = c->stats;
	ccp.napi     = &c->napi;
	ccp.ix       = MLX5E_PTP_CHANNEL_IX;

	cq_param = &cparams->txq_sq_param.cqp;

	क्रम (tc = 0; tc < params->num_tc; tc++) अणु
		काष्ठा mlx5e_cq *cq = &c->ptpsq[tc].txqsq.cq;

		err = mlx5e_खोलो_cq(c->priv, ptp_moder, cq_param, &ccp, cq);
		अगर (err)
			जाओ out_err_txqsq_cq;
	पूर्ण

	क्रम (tc = 0; tc < params->num_tc; tc++) अणु
		काष्ठा mlx5e_cq *cq = &c->ptpsq[tc].ts_cq;
		काष्ठा mlx5e_ptpsq *ptpsq = &c->ptpsq[tc];

		err = mlx5e_खोलो_cq(c->priv, ptp_moder, cq_param, &ccp, cq);
		अगर (err)
			जाओ out_err_ts_cq;

		ptpsq->cq_stats = &c->priv->ptp_stats.cq[tc];
	पूर्ण

	वापस 0;

out_err_ts_cq:
	क्रम (--tc; tc >= 0; tc--)
		mlx5e_बंद_cq(&c->ptpsq[tc].ts_cq);
	tc = params->num_tc;
out_err_txqsq_cq:
	क्रम (--tc; tc >= 0; tc--)
		mlx5e_बंद_cq(&c->ptpsq[tc].txqsq.cq);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_ptp_खोलो_rx_cq(काष्ठा mlx5e_ptp *c,
				काष्ठा mlx5e_ptp_params *cparams)
अणु
	काष्ठा mlx5e_create_cq_param ccp = अणुपूर्ण;
	काष्ठा dim_cq_moder ptp_moder = अणुपूर्ण;
	काष्ठा mlx5e_cq_param *cq_param;
	काष्ठा mlx5e_cq *cq = &c->rq.cq;

	ccp.node     = dev_to_node(mlx5_core_dma_dev(c->mdev));
	ccp.ch_stats = c->stats;
	ccp.napi     = &c->napi;
	ccp.ix       = MLX5E_PTP_CHANNEL_IX;

	cq_param = &cparams->rq_param.cqp;

	वापस mlx5e_खोलो_cq(c->priv, ptp_moder, cq_param, &ccp, cq);
पूर्ण

अटल व्योम mlx5e_ptp_बंद_tx_cqs(काष्ठा mlx5e_ptp *c)
अणु
	पूर्णांक tc;

	क्रम (tc = 0; tc < c->num_tc; tc++)
		mlx5e_बंद_cq(&c->ptpsq[tc].ts_cq);

	क्रम (tc = 0; tc < c->num_tc; tc++)
		mlx5e_बंद_cq(&c->ptpsq[tc].txqsq.cq);
पूर्ण

अटल व्योम mlx5e_ptp_build_sq_param(काष्ठा mlx5_core_dev *mdev,
				     काष्ठा mlx5e_params *params,
				     काष्ठा mlx5e_sq_param *param)
अणु
	व्योम *sqc = param->sqc;
	व्योम *wq;

	mlx5e_build_sq_param_common(mdev, param);

	wq = MLX5_ADDR_OF(sqc, sqc, wq);
	MLX5_SET(wq, wq, log_wq_sz, params->log_sq_size);
	param->stop_room = mlx5e_stop_room_क्रम_wqe(MLX5_SEND_WQE_MAX_WQEBBS);
	mlx5e_build_tx_cq_param(mdev, params, &param->cqp);
पूर्ण

अटल व्योम mlx5e_ptp_build_rq_param(काष्ठा mlx5_core_dev *mdev,
				     काष्ठा net_device *netdev,
				     u16 q_counter,
				     काष्ठा mlx5e_ptp_params *ptp_params)
अणु
	काष्ठा mlx5e_rq_param *rq_params = &ptp_params->rq_param;
	काष्ठा mlx5e_params *params = &ptp_params->params;

	params->rq_wq_type = MLX5_WQ_TYPE_CYCLIC;
	mlx5e_init_rq_type_params(mdev, params);
	params->sw_mtu = netdev->max_mtu;
	mlx5e_build_rq_param(mdev, params, शून्य, q_counter, rq_params);
पूर्ण

अटल व्योम mlx5e_ptp_build_params(काष्ठा mlx5e_ptp *c,
				   काष्ठा mlx5e_ptp_params *cparams,
				   काष्ठा mlx5e_params *orig)
अणु
	काष्ठा mlx5e_params *params = &cparams->params;

	params->tx_min_अंतरभूत_mode = orig->tx_min_अंतरभूत_mode;
	params->num_channels = orig->num_channels;
	params->hard_mtu = orig->hard_mtu;
	params->sw_mtu = orig->sw_mtu;
	params->num_tc = orig->num_tc;

	/* SQ */
	अगर (test_bit(MLX5E_PTP_STATE_TX, c->state)) अणु
		params->log_sq_size = orig->log_sq_size;
		mlx5e_ptp_build_sq_param(c->mdev, params, &cparams->txq_sq_param);
	पूर्ण
	अगर (test_bit(MLX5E_PTP_STATE_RX, c->state))
		mlx5e_ptp_build_rq_param(c->mdev, c->netdev, c->priv->q_counter, cparams);
पूर्ण

अटल पूर्णांक mlx5e_init_ptp_rq(काष्ठा mlx5e_ptp *c, काष्ठा mlx5e_params *params,
			     काष्ठा mlx5e_rq *rq)
अणु
	काष्ठा mlx5_core_dev *mdev = c->mdev;
	काष्ठा mlx5e_priv *priv = c->priv;
	पूर्णांक err;

	rq->wq_type      = params->rq_wq_type;
	rq->pdev         = mdev->device;
	rq->netdev       = priv->netdev;
	rq->priv         = priv;
	rq->घड़ी        = &mdev->घड़ी;
	rq->tstamp       = &priv->tstamp;
	rq->mdev         = mdev;
	rq->hw_mtu       = MLX5E_SW2HW_MTU(params, params->sw_mtu);
	rq->stats        = &c->priv->ptp_stats.rq;
	rq->ptp_cyc2समय = mlx5_rq_ts_translator(mdev);
	err = mlx5e_rq_set_handlers(rq, params, false);
	अगर (err)
		वापस err;

	वापस xdp_rxq_info_reg(&rq->xdp_rxq, rq->netdev, rq->ix, 0);
पूर्ण

अटल पूर्णांक mlx5e_ptp_खोलो_rq(काष्ठा mlx5e_ptp *c, काष्ठा mlx5e_params *params,
			     काष्ठा mlx5e_rq_param *rq_param)
अणु
	पूर्णांक node = dev_to_node(c->mdev->device);
	पूर्णांक err;

	err = mlx5e_init_ptp_rq(c, params, &c->rq);
	अगर (err)
		वापस err;

	वापस mlx5e_खोलो_rq(params, rq_param, शून्य, node, &c->rq);
पूर्ण

अटल पूर्णांक mlx5e_ptp_खोलो_queues(काष्ठा mlx5e_ptp *c,
				 काष्ठा mlx5e_ptp_params *cparams)
अणु
	पूर्णांक err;

	अगर (test_bit(MLX5E_PTP_STATE_TX, c->state)) अणु
		err = mlx5e_ptp_खोलो_tx_cqs(c, cparams);
		अगर (err)
			वापस err;

		err = mlx5e_ptp_खोलो_txqsqs(c, cparams);
		अगर (err)
			जाओ बंद_tx_cqs;
	पूर्ण
	अगर (test_bit(MLX5E_PTP_STATE_RX, c->state)) अणु
		err = mlx5e_ptp_खोलो_rx_cq(c, cparams);
		अगर (err)
			जाओ बंद_txqsq;

		err = mlx5e_ptp_खोलो_rq(c, &cparams->params, &cparams->rq_param);
		अगर (err)
			जाओ बंद_rx_cq;
	पूर्ण
	वापस 0;

बंद_rx_cq:
	अगर (test_bit(MLX5E_PTP_STATE_RX, c->state))
		mlx5e_बंद_cq(&c->rq.cq);
बंद_txqsq:
	अगर (test_bit(MLX5E_PTP_STATE_TX, c->state))
		mlx5e_ptp_बंद_txqsqs(c);
बंद_tx_cqs:
	अगर (test_bit(MLX5E_PTP_STATE_TX, c->state))
		mlx5e_ptp_बंद_tx_cqs(c);

	वापस err;
पूर्ण

अटल व्योम mlx5e_ptp_बंद_queues(काष्ठा mlx5e_ptp *c)
अणु
	अगर (test_bit(MLX5E_PTP_STATE_RX, c->state)) अणु
		mlx5e_बंद_rq(&c->rq);
		mlx5e_बंद_cq(&c->rq.cq);
	पूर्ण
	अगर (test_bit(MLX5E_PTP_STATE_TX, c->state)) अणु
		mlx5e_ptp_बंद_txqsqs(c);
		mlx5e_ptp_बंद_tx_cqs(c);
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5e_ptp_set_state(काष्ठा mlx5e_ptp *c, काष्ठा mlx5e_params *params)
अणु
	अगर (MLX5E_GET_PFLAG(params, MLX5E_PFLAG_TX_PORT_TS))
		__set_bit(MLX5E_PTP_STATE_TX, c->state);

	अगर (params->ptp_rx)
		__set_bit(MLX5E_PTP_STATE_RX, c->state);

	वापस biपंचांगap_empty(c->state, MLX5E_PTP_STATE_NUM_STATES) ? -EINVAL : 0;
पूर्ण

अटल व्योम mlx5e_ptp_rx_unset_fs(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_ptp_fs *ptp_fs = priv->fs.ptp_fs;

	अगर (!ptp_fs->valid)
		वापस;

	mlx5e_fs_tt_redirect_del_rule(ptp_fs->l2_rule);
	mlx5e_fs_tt_redirect_any_destroy(priv);

	mlx5e_fs_tt_redirect_del_rule(ptp_fs->udp_v6_rule);
	mlx5e_fs_tt_redirect_del_rule(ptp_fs->udp_v4_rule);
	mlx5e_fs_tt_redirect_udp_destroy(priv);
	ptp_fs->valid = false;
पूर्ण

अटल पूर्णांक mlx5e_ptp_rx_set_fs(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_ptp_fs *ptp_fs = priv->fs.ptp_fs;
	काष्ठा mlx5_flow_handle *rule;
	u32 tirn = priv->ptp_tir.tirn;
	पूर्णांक err;

	अगर (ptp_fs->valid)
		वापस 0;

	err = mlx5e_fs_tt_redirect_udp_create(priv);
	अगर (err)
		जाओ out_मुक्त;

	rule = mlx5e_fs_tt_redirect_udp_add_rule(priv, MLX5E_TT_IPV4_UDP,
						 tirn, PTP_EV_PORT);
	अगर (IS_ERR(rule)) अणु
		err = PTR_ERR(rule);
		जाओ out_destroy_fs_udp;
	पूर्ण
	ptp_fs->udp_v4_rule = rule;

	rule = mlx5e_fs_tt_redirect_udp_add_rule(priv, MLX5E_TT_IPV6_UDP,
						 tirn, PTP_EV_PORT);
	अगर (IS_ERR(rule)) अणु
		err = PTR_ERR(rule);
		जाओ out_destroy_udp_v4_rule;
	पूर्ण
	ptp_fs->udp_v6_rule = rule;

	err = mlx5e_fs_tt_redirect_any_create(priv);
	अगर (err)
		जाओ out_destroy_udp_v6_rule;

	rule = mlx5e_fs_tt_redirect_any_add_rule(priv, tirn, ETH_P_1588);
	अगर (IS_ERR(rule)) अणु
		err = PTR_ERR(rule);
		जाओ out_destroy_fs_any;
	पूर्ण
	ptp_fs->l2_rule = rule;
	ptp_fs->valid = true;

	वापस 0;

out_destroy_fs_any:
	mlx5e_fs_tt_redirect_any_destroy(priv);
out_destroy_udp_v6_rule:
	mlx5e_fs_tt_redirect_del_rule(ptp_fs->udp_v6_rule);
out_destroy_udp_v4_rule:
	mlx5e_fs_tt_redirect_del_rule(ptp_fs->udp_v4_rule);
out_destroy_fs_udp:
	mlx5e_fs_tt_redirect_udp_destroy(priv);
out_मुक्त:
	वापस err;
पूर्ण

पूर्णांक mlx5e_ptp_खोलो(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_params *params,
		   u8 lag_port, काष्ठा mlx5e_ptp **cp)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5e_ptp_params *cparams;
	काष्ठा mlx5e_ptp *c;
	पूर्णांक err;


	c = kvzalloc_node(माप(*c), GFP_KERNEL, dev_to_node(mlx5_core_dma_dev(mdev)));
	cparams = kvzalloc(माप(*cparams), GFP_KERNEL);
	अगर (!c || !cparams)
		वापस -ENOMEM;

	c->priv     = priv;
	c->mdev     = priv->mdev;
	c->tstamp   = &priv->tstamp;
	c->pdev     = mlx5_core_dma_dev(priv->mdev);
	c->netdev   = priv->netdev;
	c->mkey_be  = cpu_to_be32(priv->mdev->mlx5e_res.hw_objs.mkey.key);
	c->num_tc   = params->num_tc;
	c->stats    = &priv->ptp_stats.ch;
	c->lag_port = lag_port;

	err = mlx5e_ptp_set_state(c, params);
	अगर (err)
		जाओ err_मुक्त;

	netअगर_napi_add(netdev, &c->napi, mlx5e_ptp_napi_poll, 64);

	mlx5e_ptp_build_params(c, cparams, params);

	err = mlx5e_ptp_खोलो_queues(c, cparams);
	अगर (unlikely(err))
		जाओ err_napi_del;

	अगर (test_bit(MLX5E_PTP_STATE_RX, c->state))
		priv->rx_ptp_खोलोed = true;

	*cp = c;

	kvमुक्त(cparams);

	वापस 0;

err_napi_del:
	netअगर_napi_del(&c->napi);
err_मुक्त:
	kvमुक्त(cparams);
	kvमुक्त(c);
	वापस err;
पूर्ण

व्योम mlx5e_ptp_बंद(काष्ठा mlx5e_ptp *c)
अणु
	mlx5e_ptp_बंद_queues(c);
	netअगर_napi_del(&c->napi);

	kvमुक्त(c);
पूर्ण

व्योम mlx5e_ptp_activate_channel(काष्ठा mlx5e_ptp *c)
अणु
	पूर्णांक tc;

	napi_enable(&c->napi);

	अगर (test_bit(MLX5E_PTP_STATE_TX, c->state)) अणु
		क्रम (tc = 0; tc < c->num_tc; tc++)
			mlx5e_activate_txqsq(&c->ptpsq[tc].txqsq);
	पूर्ण
	अगर (test_bit(MLX5E_PTP_STATE_RX, c->state)) अणु
		mlx5e_ptp_rx_set_fs(c->priv);
		mlx5e_activate_rq(&c->rq);
	पूर्ण
पूर्ण

व्योम mlx5e_ptp_deactivate_channel(काष्ठा mlx5e_ptp *c)
अणु
	पूर्णांक tc;

	अगर (test_bit(MLX5E_PTP_STATE_RX, c->state))
		mlx5e_deactivate_rq(&c->rq);

	अगर (test_bit(MLX5E_PTP_STATE_TX, c->state)) अणु
		क्रम (tc = 0; tc < c->num_tc; tc++)
			mlx5e_deactivate_txqsq(&c->ptpsq[tc].txqsq);
	पूर्ण

	napi_disable(&c->napi);
पूर्ण

पूर्णांक mlx5e_ptp_get_rqn(काष्ठा mlx5e_ptp *c, u32 *rqn)
अणु
	अगर (!c || !test_bit(MLX5E_PTP_STATE_RX, c->state))
		वापस -EINVAL;

	*rqn = c->rq.rqn;
	वापस 0;
पूर्ण

पूर्णांक mlx5e_ptp_alloc_rx_fs(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_ptp_fs *ptp_fs;

	अगर (!priv->profile->rx_ptp_support)
		वापस 0;

	ptp_fs = kzalloc(माप(*ptp_fs), GFP_KERNEL);
	अगर (!ptp_fs)
		वापस -ENOMEM;

	priv->fs.ptp_fs = ptp_fs;
	वापस 0;
पूर्ण

व्योम mlx5e_ptp_मुक्त_rx_fs(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_ptp_fs *ptp_fs = priv->fs.ptp_fs;

	अगर (!priv->profile->rx_ptp_support)
		वापस;

	mlx5e_ptp_rx_unset_fs(priv);
	kमुक्त(ptp_fs);
पूर्ण

पूर्णांक mlx5e_ptp_rx_manage_fs(काष्ठा mlx5e_priv *priv, bool set)
अणु
	काष्ठा mlx5e_ptp *c = priv->channels.ptp;

	अगर (!priv->profile->rx_ptp_support)
		वापस 0;

	अगर (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		वापस 0;

	अगर (set) अणु
		अगर (!c || !test_bit(MLX5E_PTP_STATE_RX, c->state)) अणु
			netdev_WARN_ONCE(priv->netdev, "Don't try to add PTP RX-FS rules");
			वापस -EINVAL;
		पूर्ण
		वापस mlx5e_ptp_rx_set_fs(priv);
	पूर्ण
	/* set == false */
	अगर (c && test_bit(MLX5E_PTP_STATE_RX, c->state)) अणु
		netdev_WARN_ONCE(priv->netdev, "Don't try to remove PTP RX-FS rules");
		वापस -EINVAL;
	पूर्ण
	mlx5e_ptp_rx_unset_fs(priv);
	वापस 0;
पूर्ण
