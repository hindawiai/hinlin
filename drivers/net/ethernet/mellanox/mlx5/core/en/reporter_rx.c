<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Mellanox Technologies.

#समावेश "health.h"
#समावेश "params.h"
#समावेश "txrx.h"
#समावेश "devlink.h"
#समावेश "ptp.h"

अटल पूर्णांक mlx5e_query_rq_state(काष्ठा mlx5_core_dev *dev, u32 rqn, u8 *state)
अणु
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(query_rq_out);
	व्योम *out;
	व्योम *rqc;
	पूर्णांक err;

	out = kvzalloc(outlen, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	err = mlx5_core_query_rq(dev, rqn, out);
	अगर (err)
		जाओ out;

	rqc = MLX5_ADDR_OF(query_rq_out, out, rq_context);
	*state = MLX5_GET(rqc, rqc, state);

out:
	kvमुक्त(out);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_रुको_क्रम_icosq_flush(काष्ठा mlx5e_icosq *icosq)
अणु
	अचिन्हित दीर्घ exp_समय = jअगरfies +
				 msecs_to_jअगरfies(MLX5E_REPORTER_FLUSH_TIMEOUT_MSEC);

	जबतक (समय_beक्रमe(jअगरfies, exp_समय)) अणु
		अगर (icosq->cc == icosq->pc)
			वापस 0;

		msleep(20);
	पूर्ण

	netdev_err(icosq->channel->netdev,
		   "Wait for ICOSQ 0x%x flush timeout (cc = 0x%x, pc = 0x%x)\n",
		   icosq->sqn, icosq->cc, icosq->pc);

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम mlx5e_reset_icosq_cc_pc(काष्ठा mlx5e_icosq *icosq)
अणु
	WARN_ONCE(icosq->cc != icosq->pc, "ICOSQ 0x%x: cc (0x%x) != pc (0x%x)\n",
		  icosq->sqn, icosq->cc, icosq->pc);
	icosq->cc = 0;
	icosq->pc = 0;
पूर्ण

अटल पूर्णांक mlx5e_rx_reporter_err_icosq_cqe_recover(व्योम *ctx)
अणु
	काष्ठा mlx5_core_dev *mdev;
	काष्ठा mlx5e_icosq *icosq;
	काष्ठा net_device *dev;
	काष्ठा mlx5e_rq *rq;
	u8 state;
	पूर्णांक err;

	icosq = ctx;
	rq = &icosq->channel->rq;
	mdev = icosq->channel->mdev;
	dev = icosq->channel->netdev;
	err = mlx5_core_query_sq_state(mdev, icosq->sqn, &state);
	अगर (err) अणु
		netdev_err(dev, "Failed to query ICOSQ 0x%x state. err = %d\n",
			   icosq->sqn, err);
		जाओ out;
	पूर्ण

	अगर (state != MLX5_SQC_STATE_ERR)
		जाओ out;

	mlx5e_deactivate_rq(rq);
	err = mlx5e_रुको_क्रम_icosq_flush(icosq);
	अगर (err)
		जाओ out;

	mlx5e_deactivate_icosq(icosq);

	/* At this poपूर्णांक, both the rq and the icosq are disabled */

	err = mlx5e_health_sq_to_पढ़ोy(mdev, dev, icosq->sqn);
	अगर (err)
		जाओ out;

	mlx5e_reset_icosq_cc_pc(icosq);
	mlx5e_मुक्त_rx_in_progress_descs(rq);
	clear_bit(MLX5E_SQ_STATE_RECOVERING, &icosq->state);
	mlx5e_activate_icosq(icosq);
	mlx5e_activate_rq(rq);

	rq->stats->recover++;
	वापस 0;
out:
	clear_bit(MLX5E_SQ_STATE_RECOVERING, &icosq->state);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_rq_to_पढ़ोy(काष्ठा mlx5e_rq *rq, पूर्णांक curr_state)
अणु
	काष्ठा net_device *dev = rq->netdev;
	पूर्णांक err;

	err = mlx5e_modअगरy_rq_state(rq, curr_state, MLX5_RQC_STATE_RST);
	अगर (err) अणु
		netdev_err(dev, "Failed to move rq 0x%x to reset\n", rq->rqn);
		वापस err;
	पूर्ण
	err = mlx5e_modअगरy_rq_state(rq, MLX5_RQC_STATE_RST, MLX5_RQC_STATE_RDY);
	अगर (err) अणु
		netdev_err(dev, "Failed to move rq 0x%x to ready\n", rq->rqn);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_rx_reporter_err_rq_cqe_recover(व्योम *ctx)
अणु
	काष्ठा mlx5e_rq *rq = ctx;
	पूर्णांक err;

	mlx5e_deactivate_rq(rq);
	mlx5e_मुक्त_rx_descs(rq);

	err = mlx5e_rq_to_पढ़ोy(rq, MLX5_RQC_STATE_ERR);
	अगर (err)
		जाओ out;

	clear_bit(MLX5E_RQ_STATE_RECOVERING, &rq->state);
	mlx5e_activate_rq(rq);
	rq->stats->recover++;
	वापस 0;
out:
	clear_bit(MLX5E_RQ_STATE_RECOVERING, &rq->state);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_rx_reporter_समयout_recover(व्योम *ctx)
अणु
	काष्ठा mlx5_eq_comp *eq;
	काष्ठा mlx5e_rq *rq;
	पूर्णांक err;

	rq = ctx;
	eq = rq->cq.mcq.eq;

	err = mlx5e_health_channel_eq_recover(rq->netdev, eq, rq->cq.ch_stats);
	अगर (err && rq->icosq)
		clear_bit(MLX5E_SQ_STATE_ENABLED, &rq->icosq->state);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_rx_reporter_recover_from_ctx(काष्ठा mlx5e_err_ctx *err_ctx)
अणु
	वापस err_ctx->recover(err_ctx->ctx);
पूर्ण

अटल पूर्णांक mlx5e_rx_reporter_recover(काष्ठा devlink_health_reporter *reporter,
				     व्योम *context,
				     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5e_priv *priv = devlink_health_reporter_priv(reporter);
	काष्ठा mlx5e_err_ctx *err_ctx = context;

	वापस err_ctx ? mlx5e_rx_reporter_recover_from_ctx(err_ctx) :
			 mlx5e_health_recover_channels(priv);
पूर्ण

अटल पूर्णांक mlx5e_reporter_icosq_diagnose(काष्ठा mlx5e_icosq *icosq, u8 hw_state,
					 काष्ठा devlink_fmsg *fmsg)
अणु
	पूर्णांक err;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "ICOSQ");
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "sqn", icosq->sqn);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u8_pair_put(fmsg, "HW state", hw_state);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "cc", icosq->cc);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "pc", icosq->pc);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "WQE size",
					mlx5_wq_cyc_get_size(&icosq->wq));
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "CQ");
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "cqn", icosq->cq.mcq.cqn);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "cc", icosq->cq.wq.cc);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "size", mlx5_cqwq_get_size(&icosq->cq.wq));
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_end(fmsg);
	अगर (err)
		वापस err;

	वापस mlx5e_health_fmsg_named_obj_nest_end(fmsg);
पूर्ण

अटल पूर्णांक
mlx5e_rx_reporter_build_diagnose_output_rq_common(काष्ठा mlx5e_rq *rq,
						  काष्ठा devlink_fmsg *fmsg)
अणु
	u16 wqe_counter;
	पूर्णांक wqes_sz;
	u8 hw_state;
	u16 wq_head;
	पूर्णांक err;

	err = mlx5e_query_rq_state(rq->mdev, rq->rqn, &hw_state);
	अगर (err)
		वापस err;

	wqes_sz = mlx5e_rqwq_get_cur_sz(rq);
	wq_head = mlx5e_rqwq_get_head(rq);
	wqe_counter = mlx5e_rqwq_get_wqe_counter(rq);

	err = devlink_fmsg_u32_pair_put(fmsg, "rqn", rq->rqn);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u8_pair_put(fmsg, "HW state", hw_state);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u8_pair_put(fmsg, "SW state", rq->state);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "WQE counter", wqe_counter);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "posted WQEs", wqes_sz);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "cc", wq_head);
	अगर (err)
		वापस err;

	err = mlx5e_health_cq_diag_fmsg(&rq->cq, fmsg);
	अगर (err)
		वापस err;

	err = mlx5e_health_eq_diag_fmsg(rq->cq.mcq.eq, fmsg);
	अगर (err)
		वापस err;

	अगर (rq->icosq) अणु
		काष्ठा mlx5e_icosq *icosq = rq->icosq;
		u8 icosq_hw_state;

		err = mlx5_core_query_sq_state(rq->mdev, icosq->sqn, &icosq_hw_state);
		अगर (err)
			वापस err;

		err = mlx5e_reporter_icosq_diagnose(icosq, icosq_hw_state, fmsg);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_rx_reporter_build_diagnose_output(काष्ठा mlx5e_rq *rq,
						   काष्ठा devlink_fmsg *fmsg)
अणु
	पूर्णांक err;

	err = devlink_fmsg_obj_nest_start(fmsg);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "channel ix", rq->ix);
	अगर (err)
		वापस err;

	err = mlx5e_rx_reporter_build_diagnose_output_rq_common(rq, fmsg);
	अगर (err)
		वापस err;

	वापस devlink_fmsg_obj_nest_end(fmsg);
पूर्ण

अटल पूर्णांक mlx5e_rx_reporter_diagnose_generic_rq(काष्ठा mlx5e_rq *rq,
						 काष्ठा devlink_fmsg *fmsg)
अणु
	काष्ठा mlx5e_priv *priv = rq->priv;
	काष्ठा mlx5e_params *params;
	u32 rq_stride, rq_sz;
	bool real_समय;
	पूर्णांक err;

	params = &priv->channels.params;
	rq_sz = mlx5e_rqwq_get_size(rq);
	real_समय =  mlx5_is_real_समय_rq(priv->mdev);
	rq_stride = BIT(mlx5e_mpwqe_get_log_stride_size(priv->mdev, params, शून्य));

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "RQ");
	अगर (err)
		वापस err;

	err = devlink_fmsg_u8_pair_put(fmsg, "type", params->rq_wq_type);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u64_pair_put(fmsg, "stride size", rq_stride);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "size", rq_sz);
	अगर (err)
		वापस err;

	err = devlink_fmsg_string_pair_put(fmsg, "ts_format", real_समय ? "RT" : "FRC");
	अगर (err)
		वापस err;

	err = mlx5e_health_cq_common_diag_fmsg(&rq->cq, fmsg);
	अगर (err)
		वापस err;

	वापस mlx5e_health_fmsg_named_obj_nest_end(fmsg);
पूर्ण

अटल पूर्णांक
mlx5e_rx_reporter_diagnose_common_ptp_config(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_ptp *ptp_ch,
					     काष्ठा devlink_fmsg *fmsg)
अणु
	पूर्णांक err;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "PTP");
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "filter_type", priv->tstamp.rx_filter);
	अगर (err)
		वापस err;

	err = mlx5e_rx_reporter_diagnose_generic_rq(&ptp_ch->rq, fmsg);
	अगर (err)
		वापस err;

	वापस mlx5e_health_fmsg_named_obj_nest_end(fmsg);
पूर्ण

अटल पूर्णांक
mlx5e_rx_reporter_diagnose_common_config(काष्ठा devlink_health_reporter *reporter,
					 काष्ठा devlink_fmsg *fmsg)
अणु
	काष्ठा mlx5e_priv *priv = devlink_health_reporter_priv(reporter);
	काष्ठा mlx5e_rq *generic_rq = &priv->channels.c[0]->rq;
	काष्ठा mlx5e_ptp *ptp_ch = priv->channels.ptp;
	पूर्णांक err;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "Common config");
	अगर (err)
		वापस err;

	err = mlx5e_rx_reporter_diagnose_generic_rq(generic_rq, fmsg);
	अगर (err)
		वापस err;

	अगर (ptp_ch && test_bit(MLX5E_PTP_STATE_RX, ptp_ch->state)) अणु
		err = mlx5e_rx_reporter_diagnose_common_ptp_config(priv, ptp_ch, fmsg);
		अगर (err)
			वापस err;
	पूर्ण

	वापस mlx5e_health_fmsg_named_obj_nest_end(fmsg);
पूर्ण

अटल पूर्णांक mlx5e_rx_reporter_build_diagnose_output_ptp_rq(काष्ठा mlx5e_rq *rq,
							  काष्ठा devlink_fmsg *fmsg)
अणु
	पूर्णांक err;

	err = devlink_fmsg_obj_nest_start(fmsg);
	अगर (err)
		वापस err;

	err = devlink_fmsg_string_pair_put(fmsg, "channel", "ptp");
	अगर (err)
		वापस err;

	err = mlx5e_rx_reporter_build_diagnose_output_rq_common(rq, fmsg);
	अगर (err)
		वापस err;

	err = devlink_fmsg_obj_nest_end(fmsg);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_rx_reporter_diagnose(काष्ठा devlink_health_reporter *reporter,
				      काष्ठा devlink_fmsg *fmsg,
				      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5e_priv *priv = devlink_health_reporter_priv(reporter);
	काष्ठा mlx5e_ptp *ptp_ch = priv->channels.ptp;
	पूर्णांक i, err = 0;

	mutex_lock(&priv->state_lock);

	अगर (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		जाओ unlock;

	err = mlx5e_rx_reporter_diagnose_common_config(reporter, fmsg);
	अगर (err)
		जाओ unlock;

	err = devlink_fmsg_arr_pair_nest_start(fmsg, "RQs");
	अगर (err)
		जाओ unlock;

	क्रम (i = 0; i < priv->channels.num; i++) अणु
		काष्ठा mlx5e_rq *rq = &priv->channels.c[i]->rq;

		err = mlx5e_rx_reporter_build_diagnose_output(rq, fmsg);
		अगर (err)
			जाओ unlock;
	पूर्ण
	अगर (ptp_ch && test_bit(MLX5E_PTP_STATE_RX, ptp_ch->state)) अणु
		err = mlx5e_rx_reporter_build_diagnose_output_ptp_rq(&ptp_ch->rq, fmsg);
		अगर (err)
			जाओ unlock;
	पूर्ण
	err = devlink_fmsg_arr_pair_nest_end(fmsg);
unlock:
	mutex_unlock(&priv->state_lock);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_rx_reporter_dump_icosq(काष्ठा mlx5e_priv *priv, काष्ठा devlink_fmsg *fmsg,
					व्योम *ctx)
अणु
	काष्ठा mlx5e_txqsq *icosq = ctx;
	काष्ठा mlx5_rsc_key key = अणुपूर्ण;
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

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "ICOSQ");
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "QPC");
	अगर (err)
		वापस err;

	key.rsc = MLX5_SGMT_TYPE_FULL_QPC;
	key.index1 = icosq->sqn;
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

अटल पूर्णांक mlx5e_rx_reporter_dump_rq(काष्ठा mlx5e_priv *priv, काष्ठा devlink_fmsg *fmsg,
				     व्योम *ctx)
अणु
	काष्ठा mlx5_rsc_key key = अणुपूर्ण;
	काष्ठा mlx5e_rq *rq = ctx;
	पूर्णांक err;

	अगर (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		वापस 0;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "RX Slice");
	अगर (err)
		वापस err;

	key.size = PAGE_SIZE;
	key.rsc = MLX5_SGMT_TYPE_RX_SLICE_ALL;
	err = mlx5e_health_rsc_fmsg_dump(priv, &key, fmsg);
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_end(fmsg);
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "RQ");
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "QPC");
	अगर (err)
		वापस err;

	key.rsc = MLX5_SGMT_TYPE_FULL_QPC;
	key.index1 = rq->rqn;
	key.num_of_obj1 = 1;

	err = mlx5e_health_rsc_fmsg_dump(priv, &key, fmsg);
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_end(fmsg);
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "receive_buff");
	अगर (err)
		वापस err;

	key.rsc = MLX5_SGMT_TYPE_RCV_BUFF;
	key.num_of_obj2 = MLX5_RSC_DUMP_ALL;
	err = mlx5e_health_rsc_fmsg_dump(priv, &key, fmsg);
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_end(fmsg);
	अगर (err)
		वापस err;

	वापस mlx5e_health_fmsg_named_obj_nest_end(fmsg);
पूर्ण

अटल पूर्णांक mlx5e_rx_reporter_dump_all_rqs(काष्ठा mlx5e_priv *priv,
					  काष्ठा devlink_fmsg *fmsg)
अणु
	काष्ठा mlx5e_ptp *ptp_ch = priv->channels.ptp;
	काष्ठा mlx5_rsc_key key = अणुपूर्ण;
	पूर्णांक i, err;

	अगर (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		वापस 0;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "RX Slice");
	अगर (err)
		वापस err;

	key.size = PAGE_SIZE;
	key.rsc = MLX5_SGMT_TYPE_RX_SLICE_ALL;
	err = mlx5e_health_rsc_fmsg_dump(priv, &key, fmsg);
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_end(fmsg);
	अगर (err)
		वापस err;

	err = devlink_fmsg_arr_pair_nest_start(fmsg, "RQs");
	अगर (err)
		वापस err;

	क्रम (i = 0; i < priv->channels.num; i++) अणु
		काष्ठा mlx5e_rq *rq = &priv->channels.c[i]->rq;

		err = mlx5e_health_queue_dump(priv, fmsg, rq->rqn, "RQ");
		अगर (err)
			वापस err;
	पूर्ण

	अगर (ptp_ch && test_bit(MLX5E_PTP_STATE_RX, ptp_ch->state)) अणु
		err = mlx5e_health_queue_dump(priv, fmsg, ptp_ch->rq.rqn, "PTP RQ");
		अगर (err)
			वापस err;
	पूर्ण

	वापस devlink_fmsg_arr_pair_nest_end(fmsg);
पूर्ण

अटल पूर्णांक mlx5e_rx_reporter_dump_from_ctx(काष्ठा mlx5e_priv *priv,
					   काष्ठा mlx5e_err_ctx *err_ctx,
					   काष्ठा devlink_fmsg *fmsg)
अणु
	वापस err_ctx->dump(priv, fmsg, err_ctx->ctx);
पूर्ण

अटल पूर्णांक mlx5e_rx_reporter_dump(काष्ठा devlink_health_reporter *reporter,
				  काष्ठा devlink_fmsg *fmsg, व्योम *context,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5e_priv *priv = devlink_health_reporter_priv(reporter);
	काष्ठा mlx5e_err_ctx *err_ctx = context;

	वापस err_ctx ? mlx5e_rx_reporter_dump_from_ctx(priv, err_ctx, fmsg) :
			 mlx5e_rx_reporter_dump_all_rqs(priv, fmsg);
पूर्ण

व्योम mlx5e_reporter_rx_समयout(काष्ठा mlx5e_rq *rq)
अणु
	अक्षर icosq_str[MLX5E_REPORTER_PER_Q_MAX_LEN] = अणुपूर्ण;
	अक्षर err_str[MLX5E_REPORTER_PER_Q_MAX_LEN];
	काष्ठा mlx5e_icosq *icosq = rq->icosq;
	काष्ठा mlx5e_priv *priv = rq->priv;
	काष्ठा mlx5e_err_ctx err_ctx = अणुपूर्ण;

	err_ctx.ctx = rq;
	err_ctx.recover = mlx5e_rx_reporter_समयout_recover;
	err_ctx.dump = mlx5e_rx_reporter_dump_rq;

	अगर (icosq)
		snम_लिखो(icosq_str, माप(icosq_str), "ICOSQ: 0x%x, ", icosq->sqn);
	snम_लिखो(err_str, माप(err_str),
		 "RX timeout on channel: %d, %sRQ: 0x%x, CQ: 0x%x",
		 rq->ix, icosq_str, rq->rqn, rq->cq.mcq.cqn);

	mlx5e_health_report(priv, priv->rx_reporter, err_str, &err_ctx);
पूर्ण

व्योम mlx5e_reporter_rq_cqe_err(काष्ठा mlx5e_rq *rq)
अणु
	अक्षर err_str[MLX5E_REPORTER_PER_Q_MAX_LEN];
	काष्ठा mlx5e_priv *priv = rq->priv;
	काष्ठा mlx5e_err_ctx err_ctx = अणुपूर्ण;

	err_ctx.ctx = rq;
	err_ctx.recover = mlx5e_rx_reporter_err_rq_cqe_recover;
	err_ctx.dump = mlx5e_rx_reporter_dump_rq;
	snम_लिखो(err_str, माप(err_str), "ERR CQE on RQ: 0x%x", rq->rqn);

	mlx5e_health_report(priv, priv->rx_reporter, err_str, &err_ctx);
पूर्ण

व्योम mlx5e_reporter_icosq_cqe_err(काष्ठा mlx5e_icosq *icosq)
अणु
	काष्ठा mlx5e_priv *priv = icosq->channel->priv;
	अक्षर err_str[MLX5E_REPORTER_PER_Q_MAX_LEN];
	काष्ठा mlx5e_err_ctx err_ctx = अणुपूर्ण;

	err_ctx.ctx = icosq;
	err_ctx.recover = mlx5e_rx_reporter_err_icosq_cqe_recover;
	err_ctx.dump = mlx5e_rx_reporter_dump_icosq;
	snम_लिखो(err_str, माप(err_str), "ERR CQE on ICOSQ: 0x%x", icosq->sqn);

	mlx5e_health_report(priv, priv->rx_reporter, err_str, &err_ctx);
पूर्ण

अटल स्थिर काष्ठा devlink_health_reporter_ops mlx5_rx_reporter_ops = अणु
	.name = "rx",
	.recover = mlx5e_rx_reporter_recover,
	.diagnose = mlx5e_rx_reporter_diagnose,
	.dump = mlx5e_rx_reporter_dump,
पूर्ण;

#घोषणा MLX5E_REPORTER_RX_GRACEFUL_PERIOD 500

व्योम mlx5e_reporter_rx_create(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा devlink_port *dl_port = mlx5e_devlink_get_dl_port(priv);
	काष्ठा devlink_health_reporter *reporter;

	reporter = devlink_port_health_reporter_create(dl_port, &mlx5_rx_reporter_ops,
						       MLX5E_REPORTER_RX_GRACEFUL_PERIOD, priv);
	अगर (IS_ERR(reporter)) अणु
		netdev_warn(priv->netdev, "Failed to create rx reporter, err = %ld\n",
			    PTR_ERR(reporter));
		वापस;
	पूर्ण
	priv->rx_reporter = reporter;
पूर्ण

व्योम mlx5e_reporter_rx_destroy(काष्ठा mlx5e_priv *priv)
अणु
	अगर (!priv->rx_reporter)
		वापस;

	devlink_port_health_reporter_destroy(priv->rx_reporter);
	priv->rx_reporter = शून्य;
पूर्ण
