<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Mellanox Technologies.

#समावेश "health.h"
#समावेश "lib/eq.h"
#समावेश "lib/mlx5.h"

पूर्णांक mlx5e_health_fmsg_named_obj_nest_start(काष्ठा devlink_fmsg *fmsg, अक्षर *name)
अणु
	पूर्णांक err;

	err = devlink_fmsg_pair_nest_start(fmsg, name);
	अगर (err)
		वापस err;

	err = devlink_fmsg_obj_nest_start(fmsg);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

पूर्णांक mlx5e_health_fmsg_named_obj_nest_end(काष्ठा devlink_fmsg *fmsg)
अणु
	पूर्णांक err;

	err = devlink_fmsg_obj_nest_end(fmsg);
	अगर (err)
		वापस err;

	err = devlink_fmsg_pair_nest_end(fmsg);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

पूर्णांक mlx5e_health_cq_diag_fmsg(काष्ठा mlx5e_cq *cq, काष्ठा devlink_fmsg *fmsg)
अणु
	u32 out[MLX5_ST_SZ_DW(query_cq_out)] = अणुपूर्ण;
	u8 hw_status;
	व्योम *cqc;
	पूर्णांक err;

	err = mlx5_core_query_cq(cq->mdev, &cq->mcq, out);
	अगर (err)
		वापस err;

	cqc = MLX5_ADDR_OF(query_cq_out, out, cq_context);
	hw_status = MLX5_GET(cqc, cqc, status);

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "CQ");
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "cqn", cq->mcq.cqn);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u8_pair_put(fmsg, "HW status", hw_status);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "ci", mlx5_cqwq_get_ci(&cq->wq));
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "size", mlx5_cqwq_get_size(&cq->wq));
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_end(fmsg);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

पूर्णांक mlx5e_health_cq_common_diag_fmsg(काष्ठा mlx5e_cq *cq, काष्ठा devlink_fmsg *fmsg)
अणु
	u8 cq_log_stride;
	u32 cq_sz;
	पूर्णांक err;

	cq_sz = mlx5_cqwq_get_size(&cq->wq);
	cq_log_stride = mlx5_cqwq_get_log_stride_size(&cq->wq);

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "CQ");
	अगर (err)
		वापस err;

	err = devlink_fmsg_u64_pair_put(fmsg, "stride size", BIT(cq_log_stride));
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "size", cq_sz);
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_end(fmsg);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

पूर्णांक mlx5e_health_eq_diag_fmsg(काष्ठा mlx5_eq_comp *eq, काष्ठा devlink_fmsg *fmsg)
अणु
	पूर्णांक err;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, "EQ");
	अगर (err)
		वापस err;

	err = devlink_fmsg_u8_pair_put(fmsg, "eqn", eq->core.eqn);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "irqn", eq->core.irqn);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "vecidx", eq->core.vecidx);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "ci", eq->core.cons_index);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "size", eq_get_size(&eq->core));
	अगर (err)
		वापस err;

	वापस mlx5e_health_fmsg_named_obj_nest_end(fmsg);
पूर्ण

व्योम mlx5e_health_create_reporters(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_reporter_tx_create(priv);
	mlx5e_reporter_rx_create(priv);
पूर्ण

व्योम mlx5e_health_destroy_reporters(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_reporter_rx_destroy(priv);
	mlx5e_reporter_tx_destroy(priv);
पूर्ण

व्योम mlx5e_health_channels_update(काष्ठा mlx5e_priv *priv)
अणु
	अगर (priv->tx_reporter)
		devlink_health_reporter_state_update(priv->tx_reporter,
						     DEVLINK_HEALTH_REPORTER_STATE_HEALTHY);
	अगर (priv->rx_reporter)
		devlink_health_reporter_state_update(priv->rx_reporter,
						     DEVLINK_HEALTH_REPORTER_STATE_HEALTHY);
पूर्ण

पूर्णांक mlx5e_health_sq_to_पढ़ोy(काष्ठा mlx5_core_dev *mdev, काष्ठा net_device *dev, u32 sqn)
अणु
	काष्ठा mlx5e_modअगरy_sq_param msp = अणुपूर्ण;
	पूर्णांक err;

	msp.curr_state = MLX5_SQC_STATE_ERR;
	msp.next_state = MLX5_SQC_STATE_RST;

	err = mlx5e_modअगरy_sq(mdev, sqn, &msp);
	अगर (err) अणु
		netdev_err(dev, "Failed to move sq 0x%x to reset\n", sqn);
		वापस err;
	पूर्ण

	स_रखो(&msp, 0, माप(msp));
	msp.curr_state = MLX5_SQC_STATE_RST;
	msp.next_state = MLX5_SQC_STATE_RDY;

	err = mlx5e_modअगरy_sq(mdev, sqn, &msp);
	अगर (err) अणु
		netdev_err(dev, "Failed to move sq 0x%x to ready\n", sqn);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mlx5e_health_recover_channels(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक err = 0;

	rtnl_lock();
	mutex_lock(&priv->state_lock);

	अगर (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		जाओ out;

	err = mlx5e_safe_reखोलो_channels(priv);

out:
	mutex_unlock(&priv->state_lock);
	rtnl_unlock();

	वापस err;
पूर्ण

पूर्णांक mlx5e_health_channel_eq_recover(काष्ठा net_device *dev, काष्ठा mlx5_eq_comp *eq,
				    काष्ठा mlx5e_ch_stats *stats)
अणु
	u32 eqe_count;

	netdev_err(dev, "EQ 0x%x: Cons = 0x%x, irqn = 0x%x\n",
		   eq->core.eqn, eq->core.cons_index, eq->core.irqn);

	eqe_count = mlx5_eq_poll_irq_disabled(eq);
	अगर (!eqe_count)
		वापस -EIO;

	netdev_err(dev, "Recovered %d eqes on EQ 0x%x\n",
		   eqe_count, eq->core.eqn);

	stats->eq_rearm++;
	वापस 0;
पूर्ण

पूर्णांक mlx5e_health_report(काष्ठा mlx5e_priv *priv,
			काष्ठा devlink_health_reporter *reporter, अक्षर *err_str,
			काष्ठा mlx5e_err_ctx *err_ctx)
अणु
	netdev_err(priv->netdev, "%s\n", err_str);

	अगर (!reporter)
		वापस err_ctx->recover(err_ctx->ctx);

	वापस devlink_health_report(reporter, err_str, err_ctx);
पूर्ण

#घोषणा MLX5_HEALTH_DEVLINK_MAX_SIZE 1024
अटल पूर्णांक mlx5e_health_rsc_fmsg_binary(काष्ठा devlink_fmsg *fmsg,
					स्थिर व्योम *value, u32 value_len)

अणु
	u32 data_size;
	पूर्णांक err = 0;
	u32 offset;

	क्रम (offset = 0; offset < value_len; offset += data_size) अणु
		data_size = value_len - offset;
		अगर (data_size > MLX5_HEALTH_DEVLINK_MAX_SIZE)
			data_size = MLX5_HEALTH_DEVLINK_MAX_SIZE;
		err = devlink_fmsg_binary_put(fmsg, value + offset, data_size);
		अगर (err)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक mlx5e_health_rsc_fmsg_dump(काष्ठा mlx5e_priv *priv, काष्ठा mlx5_rsc_key *key,
			       काष्ठा devlink_fmsg *fmsg)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5_rsc_dump_cmd *cmd;
	काष्ठा page *page;
	पूर्णांक cmd_err, err;
	पूर्णांक end_err;
	पूर्णांक size;

	अगर (IS_ERR_OR_शून्य(mdev->rsc_dump))
		वापस -EOPNOTSUPP;

	page = alloc_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	err = devlink_fmsg_binary_pair_nest_start(fmsg, "data");
	अगर (err)
		जाओ मुक्त_page;

	cmd = mlx5_rsc_dump_cmd_create(mdev, key);
	अगर (IS_ERR(cmd)) अणु
		err = PTR_ERR(cmd);
		जाओ मुक्त_page;
	पूर्ण

	करो अणु
		cmd_err = mlx5_rsc_dump_next(mdev, cmd, page, &size);
		अगर (cmd_err < 0) अणु
			err = cmd_err;
			जाओ destroy_cmd;
		पूर्ण

		err = mlx5e_health_rsc_fmsg_binary(fmsg, page_address(page), size);
		अगर (err)
			जाओ destroy_cmd;

	पूर्ण जबतक (cmd_err > 0);

destroy_cmd:
	mlx5_rsc_dump_cmd_destroy(cmd);
	end_err = devlink_fmsg_binary_pair_nest_end(fmsg);
	अगर (end_err)
		err = end_err;
मुक्त_page:
	__मुक्त_page(page);
	वापस err;
पूर्ण

पूर्णांक mlx5e_health_queue_dump(काष्ठा mlx5e_priv *priv, काष्ठा devlink_fmsg *fmsg,
			    पूर्णांक queue_idx, अक्षर *lbl)
अणु
	काष्ठा mlx5_rsc_key key = अणुपूर्ण;
	पूर्णांक err;

	key.rsc = MLX5_SGMT_TYPE_FULL_QPC;
	key.index1 = queue_idx;
	key.size = PAGE_SIZE;
	key.num_of_obj1 = 1;

	err = devlink_fmsg_obj_nest_start(fmsg);
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_start(fmsg, lbl);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "index", queue_idx);
	अगर (err)
		वापस err;

	err = mlx5e_health_rsc_fmsg_dump(priv, &key, fmsg);
	अगर (err)
		वापस err;

	err = mlx5e_health_fmsg_named_obj_nest_end(fmsg);
	अगर (err)
		वापस err;

	वापस devlink_fmsg_obj_nest_end(fmsg);
पूर्ण
