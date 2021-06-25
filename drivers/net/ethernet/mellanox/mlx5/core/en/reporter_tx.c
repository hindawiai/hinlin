<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश "health.h"
#समावेश "en/ptp.h"
#समावेश "en/devlink.h"

अटल पूर्णांक mlx5e_रुको_क्रम_sq_flush(काष्ठा mlx5e_txqsq *sq)
अणु
	अचिन्हित दीर्घ exp_समय = jअगरfies +
				 msecs_to_jअगरfies(MLX5E_REPORTER_FLUSH_TIMEOUT_MSEC);

	जबतक (समय_beक्रमe(jअगरfies, exp_समय)) अणु
		अगर (sq->cc == sq->pc)
			वापस 0;

		msleep(20);
	पूर्ण

	netdev_err(sq->netdev,
		   "Wait for SQ 0x%x flush timeout (sq cc = 0x%x, sq pc = 0x%x)\n",
		   sq->sqn, sq->cc, sq->pc);

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम mlx5e_reset_txqsq_cc_pc(काष्ठा mlx5e_txqsq *sq)
अणु
	WARN_ONCE(sq->cc != sq->pc,
		  "SQ 0x%x: cc (0x%x) != pc (0x%x)\n",
		  sq->sqn, sq->cc, sq->pc);
	sq->cc = 0;
	sq->dma_fअगरo_cc = 0;
	sq->pc = 0;
पूर्ण

अटल पूर्णांक mlx5e_tx_reporter_err_cqe_recover(व्योम *ctx)
अणु
	काष्ठा mlx5_core_dev *mdev;
	काष्ठा net_device *dev;
	काष्ठा mlx5e_txqsq *sq;
	u8 state;
	पूर्णांक err;

	sq = ctx;
	mdev = sq->mdev;
	dev = sq->netdev;

	अगर (!test_bit(MLX5E_SQ_STATE_RECOVERING, &sq->state))
		वापस 0;

	err = mlx5_core_query_sq_state(mdev, sq->sqn, &state);
	अगर (err) अणु
		netdev_err(dev, "Failed to query SQ 0x%x state. err = %d\n",
			   sq->sqn, err);
		जाओ out;
	पूर्ण

	अगर (state != MLX5_SQC_STATE_ERR)
		जाओ out;

	mlx5e_tx_disable_queue(sq->txq);

	err = mlx5e_रुको_क्रम_sq_flush(sq);
	अगर (err)
		जाओ out;

	/* At this poपूर्णांक, no new packets will arrive from the stack as TXQ is
	 * marked with QUEUE_STATE_DRV_XOFF. In addition, NAPI cleared all
	 * pending WQEs. SQ can safely reset the SQ.
	 */

	err = mlx5e_health_sq_to_पढ़ोy(mdev, dev, sq->sqn);
	अगर (err)
		जाओ out;

	mlx5e_reset_txqsq_cc_pc(sq);
	sq->stats->recover++;
	clear_bit(MLX5E_SQ_STATE_RECOVERING, &sq->state);
	mlx5e_activate_txqsq(sq);

	वापस 0;
out:
	clear_bit(MLX5E_SQ_STATE_RECOVERING, &sq->state);
	वापस err;
पूर्ण

काष्ठा mlx5e_tx_समयout_ctx अणु
	काष्ठा mlx5e_txqsq *sq;
	चिन्हित पूर्णांक status;
पूर्ण;

अटल पूर्णांक mlx5e_tx_reporter_समयout_recover(व्योम *ctx)
अणु
	काष्ठा mlx5e_tx_समयout_ctx *to_ctx;
	काष्ठा mlx5e_priv *priv;
	काष्ठा mlx5_eq_comp *eq;
	काष्ठा mlx5e_txqsq *sq;
	पूर्णांक err;

	to_ctx = ctx;
	sq = to_ctx->sq;
	eq = sq->cq.mcq.eq;
	priv = sq->priv;
	err = mlx5e_health_channel_eq_recover(sq->netdev, eq, sq->cq.ch_stats);
	अगर (!err) अणु
		to_ctx->status = 0; /* this sq recovered */
		वापस err;
	पूर्ण

	err = mlx5e_safe_reखोलो_channels(priv);
	अगर (!err) अणु
		to_ctx->status = 1; /* all channels recovered */
		वापस err;
	पूर्ण

	to_ctx->status = err;
	clear_bit(MLX5E_SQ_STATE_ENABLED, &sq->state);
	netdev_err(priv->netdev,
		   "mlx5e_safe_reopen_channels failed recovering from a tx_timeout, err(%d).\n",
		   err);

	वापस err;
पूर्ण

/* state lock cannot be grabbed within this function.
 * It can cause a dead lock or a पढ़ो-after-मुक्त.
 */
अटल पूर्णांक mlx5e_tx_reporter_recover_from_ctx(काष्ठा mlx5e_err_ctx *err_ctx)
अणु
	वापस err_ctx->recover(err_ctx->ctx);
पूर्ण

अटल पूर्णांक mlx5e_tx_reporter_recover(काष्ठा devlink_health_reporter *reporter,
				     व्योम *context,
				     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5e_priv *priv = devlink_health_reporter_priv(reporter);
	काष्ठा mlx5e_err_ctx *err_ctx = context;

	वापस err_ctx ? mlx5e_tx_reporter_recover_from_ctx(err_ctx) :
			 mlx5e_health_recover_channels(priv);
पूर्ण

अटल पूर्णांक
mlx5e_tx_reporter_build_diagnose_output_sq_common(काष्ठा devlink_fmsg *fmsg,
						  काष्ठा mlx5e_txqsq *sq, पूर्णांक tc)
अणु
	bool stopped = netअगर_xmit_stopped(sq->txq);
	काष्ठा mlx5e_priv *priv = sq->priv;
	u8 state;
	पूर्णांक err;

	err = mlx5_core_query_sq_state(priv->mdev, sq->sqn, &state);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "tc", tc);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "txq ix", sq->txq_ix);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "sqn", sq->sqn);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u8_pair_put(fmsg, "HW state", state);
	अगर (err)
		वापस err;

	err = devlink_fmsg_bool_pair_put(fmsg, "stopped", stopped);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "cc", sq->cc);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "pc", sq->pc);
	अगर (err)
		वापस err;

	err = mlx5e_health_cq_diag_fmsg(&sq->cq, fmsg);
	अगर (err)
		वापस err;

	वापस mlx5e_health_eq_diag_fmsg(sq->cq.mcq.eq, fmsg);
पूर्ण

अटल पूर्णांक
mlx5e_tx_reporter_build_diagnose_output(काष्ठा devlink_fmsg *fmsg,
					काष्ठा mlx5e_txqsq *sq, पूर्णांक tc)
अणु
	पूर्णांक err;

	err = devlink_fmsg_obj_nest_start(fmsg);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "channel ix", sq->ch_ix);
	अगर (err)
		वापस err;

	err = mlx5e_tx_reporter_build_diagnose_output_sq_common(fmsg, sq, tc);
	अगर (err)
		वापस err;

	err = devlink_fmsg_obj_nest_end(fmsg);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक
mlx5e_tx_reporter_build_diagnose_output_ptpsq(काष्ठा devlink_fmsg *fmsg,
					      काष्ठा mlx5e_ptpsq *ptpsq, पूर्णांक tc)
अणु
	पूर्णांक err;

	err = devlink_fmsg_obj_nest_start(fmsg);
	अगर (err)
		वापस err;

	err = devlink_fmsg_string_pair_put(fmsg, "channel", "ptp");
	अगर (err)
		वापस err;

	err = mlx5e_tx_reporter_build_diagnose_output_sq_common(fmsg, &ptpsq->txqsq, tc);
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "Port TS");
	अगर (err)
		वापस err;

	err = mlx5e_health_cq_diag_fmsg(&ptpsq->ts_cq, fmsg);
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_end(fmsg);
	अगर (err)
		वापस err;

	err = devlink_fmsg_obj_nest_end(fmsg);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक
mlx5e_tx_reporter_diagnose_generic_txqsq(काष्ठा devlink_fmsg *fmsg,
					 काष्ठा mlx5e_txqsq *txqsq)
अणु
	u32 sq_stride, sq_sz;
	bool real_समय;
	पूर्णांक err;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "SQ");
	अगर (err)
		वापस err;

	real_समय =  mlx5_is_real_समय_sq(txqsq->mdev);
	sq_sz = mlx5_wq_cyc_get_size(&txqsq->wq);
	sq_stride = MLX5_SEND_WQE_BB;

	err = devlink_fmsg_u64_pair_put(fmsg, "stride size", sq_stride);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "size", sq_sz);
	अगर (err)
		वापस err;

	err = devlink_fmsg_string_pair_put(fmsg, "ts_format", real_समय ? "RT" : "FRC");
	अगर (err)
		वापस err;

	err = mlx5e_health_cq_common_diag_fmsg(&txqsq->cq, fmsg);
	अगर (err)
		वापस err;

	वापस mlx5e_health_fmsg_named_obj_nest_end(fmsg);
पूर्ण

अटल पूर्णांक
mlx5e_tx_reporter_diagnose_generic_tx_port_ts(काष्ठा devlink_fmsg *fmsg,
					      काष्ठा mlx5e_ptpsq *ptpsq)
अणु
	पूर्णांक err;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "Port TS");
	अगर (err)
		वापस err;

	err = mlx5e_health_cq_common_diag_fmsg(&ptpsq->ts_cq, fmsg);
	अगर (err)
		वापस err;

	वापस mlx5e_health_fmsg_named_obj_nest_end(fmsg);
पूर्ण

अटल पूर्णांक
mlx5e_tx_reporter_diagnose_common_config(काष्ठा devlink_health_reporter *reporter,
					 काष्ठा devlink_fmsg *fmsg)
अणु
	काष्ठा mlx5e_priv *priv = devlink_health_reporter_priv(reporter);
	काष्ठा mlx5e_txqsq *generic_sq = priv->txq2sq[0];
	काष्ठा mlx5e_ptp *ptp_ch = priv->channels.ptp;
	काष्ठा mlx5e_ptpsq *generic_ptpsq;
	पूर्णांक err;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "Common Config");
	अगर (err)
		वापस err;

	err = mlx5e_tx_reporter_diagnose_generic_txqsq(fmsg, generic_sq);
	अगर (err)
		वापस err;

	अगर (!ptp_ch || !test_bit(MLX5E_PTP_STATE_TX, ptp_ch->state))
		जाओ out;

	generic_ptpsq = &ptp_ch->ptpsq[0];

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "PTP");
	अगर (err)
		वापस err;

	err = mlx5e_tx_reporter_diagnose_generic_txqsq(fmsg, &generic_ptpsq->txqsq);
	अगर (err)
		वापस err;

	err = mlx5e_tx_reporter_diagnose_generic_tx_port_ts(fmsg, generic_ptpsq);
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_end(fmsg);
	अगर (err)
		वापस err;

out:
	वापस mlx5e_health_fmsg_named_obj_nest_end(fmsg);
पूर्ण

अटल पूर्णांक mlx5e_tx_reporter_diagnose(काष्ठा devlink_health_reporter *reporter,
				      काष्ठा devlink_fmsg *fmsg,
				      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5e_priv *priv = devlink_health_reporter_priv(reporter);
	काष्ठा mlx5e_ptp *ptp_ch = priv->channels.ptp;

	पूर्णांक i, tc, err = 0;

	mutex_lock(&priv->state_lock);

	अगर (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		जाओ unlock;

	err = mlx5e_tx_reporter_diagnose_common_config(reporter, fmsg);
	अगर (err)
		जाओ unlock;

	err = devlink_fmsg_arr_pair_nest_start(fmsg, "SQs");
	अगर (err)
		जाओ unlock;

	क्रम (i = 0; i < priv->channels.num; i++) अणु
		काष्ठा mlx5e_channel *c = priv->channels.c[i];

		क्रम (tc = 0; tc < priv->channels.params.num_tc; tc++) अणु
			काष्ठा mlx5e_txqsq *sq = &c->sq[tc];

			err = mlx5e_tx_reporter_build_diagnose_output(fmsg, sq, tc);
			अगर (err)
				जाओ unlock;
		पूर्ण
	पूर्ण

	अगर (!ptp_ch || !test_bit(MLX5E_PTP_STATE_TX, ptp_ch->state))
		जाओ बंद_sqs_nest;

	क्रम (tc = 0; tc < priv->channels.params.num_tc; tc++) अणु
		err = mlx5e_tx_reporter_build_diagnose_output_ptpsq(fmsg,
								    &ptp_ch->ptpsq[tc],
								    tc);
		अगर (err)
			जाओ unlock;
	पूर्ण

बंद_sqs_nest:
	err = devlink_fmsg_arr_pair_nest_end(fmsg);
	अगर (err)
		जाओ unlock;

unlock:
	mutex_unlock(&priv->state_lock);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_tx_reporter_dump_sq(काष्ठा mlx5e_priv *priv, काष्ठा devlink_fmsg *fmsg,
				     व्योम *ctx)
अणु
	काष्ठा mlx5_rsc_key key = अणुपूर्ण;
	काष्ठा mlx5e_txqsq *sq = ctx;
	पूर्णांक err;

	अगर (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		वापस 0;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "SX Slice");
	अगर (err)
		वापस err;

	key.size = PAGE_SIZE;
	key.rsc = MLX5_SGMT_TYPE_SX_SLICE_ALL;
	err = mlx5e_health_rsc_fmsg_dump(priv, &key, fmsg);
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_end(fmsg);
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "SQ");
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "QPC");
	अगर (err)
		वापस err;

	key.rsc = MLX5_SGMT_TYPE_FULL_QPC;
	key.index1 = sq->sqn;
	key.num_of_obj1 = 1;

	err = mlx5e_health_rsc_fmsg_dump(priv, &key, fmsg);
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_end(fmsg);
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "send_buff");
	अगर (err)
		वापस err;

	key.rsc = MLX5_SGMT_TYPE_SND_BUFF;
	key.num_of_obj2 = MLX5_RSC_DUMP_ALL;
	err = mlx5e_health_rsc_fmsg_dump(priv, &key, fmsg);
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_end(fmsg);
	अगर (err)
		वापस err;

	वापस mlx5e_health_fmsg_named_obj_nest_end(fmsg);
पूर्ण

अटल पूर्णांक mlx5e_tx_reporter_dump_all_sqs(काष्ठा mlx5e_priv *priv,
					  काष्ठा devlink_fmsg *fmsg)
अणु
	काष्ठा mlx5e_ptp *ptp_ch = priv->channels.ptp;
	काष्ठा mlx5_rsc_key key = अणुपूर्ण;
	पूर्णांक i, tc, err;

	अगर (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		वापस 0;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "SX Slice");
	अगर (err)
		वापस err;

	key.size = PAGE_SIZE;
	key.rsc = MLX5_SGMT_TYPE_SX_SLICE_ALL;
	err = mlx5e_health_rsc_fmsg_dump(priv, &key, fmsg);
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_end(fmsg);
	अगर (err)
		वापस err;

	err = devlink_fmsg_arr_pair_nest_start(fmsg, "SQs");
	अगर (err)
		वापस err;

	क्रम (i = 0; i < priv->channels.num; i++) अणु
		काष्ठा mlx5e_channel *c = priv->channels.c[i];

		क्रम (tc = 0; tc < priv->channels.params.num_tc; tc++) अणु
			काष्ठा mlx5e_txqsq *sq = &c->sq[tc];

			err = mlx5e_health_queue_dump(priv, fmsg, sq->sqn, "SQ");
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (ptp_ch && test_bit(MLX5E_PTP_STATE_TX, ptp_ch->state)) अणु
		क्रम (tc = 0; tc < priv->channels.params.num_tc; tc++) अणु
			काष्ठा mlx5e_txqsq *sq = &ptp_ch->ptpsq[tc].txqsq;

			err = mlx5e_health_queue_dump(priv, fmsg, sq->sqn, "PTP SQ");
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस devlink_fmsg_arr_pair_nest_end(fmsg);
पूर्ण

अटल पूर्णांक mlx5e_tx_reporter_dump_from_ctx(काष्ठा mlx5e_priv *priv,
					   काष्ठा mlx5e_err_ctx *err_ctx,
					   काष्ठा devlink_fmsg *fmsg)
अणु
	वापस err_ctx->dump(priv, fmsg, err_ctx->ctx);
पूर्ण

अटल पूर्णांक mlx5e_tx_reporter_dump(काष्ठा devlink_health_reporter *reporter,
				  काष्ठा devlink_fmsg *fmsg, व्योम *context,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5e_priv *priv = devlink_health_reporter_priv(reporter);
	काष्ठा mlx5e_err_ctx *err_ctx = context;

	वापस err_ctx ? mlx5e_tx_reporter_dump_from_ctx(priv, err_ctx, fmsg) :
			 mlx5e_tx_reporter_dump_all_sqs(priv, fmsg);
पूर्ण

व्योम mlx5e_reporter_tx_err_cqe(काष्ठा mlx5e_txqsq *sq)
अणु
	अक्षर err_str[MLX5E_REPORTER_PER_Q_MAX_LEN];
	काष्ठा mlx5e_priv *priv = sq->priv;
	काष्ठा mlx5e_err_ctx err_ctx = अणुपूर्ण;

	err_ctx.ctx = sq;
	err_ctx.recover = mlx5e_tx_reporter_err_cqe_recover;
	err_ctx.dump = mlx5e_tx_reporter_dump_sq;
	snम_लिखो(err_str, माप(err_str), "ERR CQE on SQ: 0x%x", sq->sqn);

	mlx5e_health_report(priv, priv->tx_reporter, err_str, &err_ctx);
पूर्ण

पूर्णांक mlx5e_reporter_tx_समयout(काष्ठा mlx5e_txqsq *sq)
अणु
	अक्षर err_str[MLX5E_REPORTER_PER_Q_MAX_LEN];
	काष्ठा mlx5e_tx_समयout_ctx to_ctx = अणुपूर्ण;
	काष्ठा mlx5e_priv *priv = sq->priv;
	काष्ठा mlx5e_err_ctx err_ctx = अणुपूर्ण;

	to_ctx.sq = sq;
	err_ctx.ctx = &to_ctx;
	err_ctx.recover = mlx5e_tx_reporter_समयout_recover;
	err_ctx.dump = mlx5e_tx_reporter_dump_sq;
	snम_लिखो(err_str, माप(err_str),
		 "TX timeout on queue: %d, SQ: 0x%x, CQ: 0x%x, SQ Cons: 0x%x SQ Prod: 0x%x, usecs since last trans: %u",
		 sq->ch_ix, sq->sqn, sq->cq.mcq.cqn, sq->cc, sq->pc,
		 jअगरfies_to_usecs(jअगरfies - sq->txq->trans_start));

	mlx5e_health_report(priv, priv->tx_reporter, err_str, &err_ctx);
	वापस to_ctx.status;
पूर्ण

अटल स्थिर काष्ठा devlink_health_reporter_ops mlx5_tx_reporter_ops = अणु
		.name = "tx",
		.recover = mlx5e_tx_reporter_recover,
		.diagnose = mlx5e_tx_reporter_diagnose,
		.dump = mlx5e_tx_reporter_dump,
पूर्ण;

#घोषणा MLX5_REPORTER_TX_GRACEFUL_PERIOD 500

व्योम mlx5e_reporter_tx_create(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा devlink_port *dl_port = mlx5e_devlink_get_dl_port(priv);
	काष्ठा devlink_health_reporter *reporter;

	reporter = devlink_port_health_reporter_create(dl_port, &mlx5_tx_reporter_ops,
						       MLX5_REPORTER_TX_GRACEFUL_PERIOD, priv);
	अगर (IS_ERR(reporter)) अणु
		netdev_warn(priv->netdev,
			    "Failed to create tx reporter, err = %ld\n",
			    PTR_ERR(reporter));
		वापस;
	पूर्ण
	priv->tx_reporter = reporter;
पूर्ण

व्योम mlx5e_reporter_tx_destroy(काष्ठा mlx5e_priv *priv)
अणु
	अगर (!priv->tx_reporter)
		वापस;

	devlink_port_health_reporter_destroy(priv->tx_reporter);
	priv->tx_reporter = शून्य;
पूर्ण
