<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005, 2006, 2007 Cisco Systems, Inc. All rights reserved.
 * Copyright (c) 2005, 2006, 2007, 2008 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2004 Voltaire, Inc. All rights reserved.
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

#समावेश <linux/gfp.h>
#समावेश <linux/export.h>

#समावेश <linux/mlx4/cmd.h>
#समावेश <linux/mlx4/qp.h>

#समावेश "mlx4.h"
#समावेश "icm.h"

/* QP to support BF should have bits 6,7 cleared */
#घोषणा MLX4_BF_QP_SKIP_MASK	0xc0
#घोषणा MLX4_MAX_BF_QP_RANGE	0x40

व्योम mlx4_qp_event(काष्ठा mlx4_dev *dev, u32 qpn, पूर्णांक event_type)
अणु
	काष्ठा mlx4_qp_table *qp_table = &mlx4_priv(dev)->qp_table;
	काष्ठा mlx4_qp *qp;

	spin_lock(&qp_table->lock);

	qp = __mlx4_qp_lookup(dev, qpn);
	अगर (qp)
		refcount_inc(&qp->refcount);

	spin_unlock(&qp_table->lock);

	अगर (!qp) अणु
		mlx4_dbg(dev, "Async event for none existent QP %08x\n", qpn);
		वापस;
	पूर्ण

	qp->event(qp, event_type);

	अगर (refcount_dec_and_test(&qp->refcount))
		complete(&qp->मुक्त);
पूर्ण

/* used क्रम INIT/CLOSE port logic */
अटल पूर्णांक is_master_qp0(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp, पूर्णांक *real_qp0, पूर्णांक *proxy_qp0)
अणु
	/* this procedure is called after we alपढ़ोy know we are on the master */
	/* qp0 is either the proxy qp0, or the real qp0 */
	u32 pf_proxy_offset = dev->phys_caps.base_proxy_sqpn + 8 * mlx4_master_func_num(dev);
	*proxy_qp0 = qp->qpn >= pf_proxy_offset && qp->qpn <= pf_proxy_offset + 1;

	*real_qp0 = qp->qpn >= dev->phys_caps.base_sqpn &&
		qp->qpn <= dev->phys_caps.base_sqpn + 1;

	वापस *real_qp0 || *proxy_qp0;
पूर्ण

अटल पूर्णांक __mlx4_qp_modअगरy(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mtt *mtt,
		     क्रमागत mlx4_qp_state cur_state, क्रमागत mlx4_qp_state new_state,
		     काष्ठा mlx4_qp_context *context,
		     क्रमागत mlx4_qp_optpar optpar,
		     पूर्णांक sqd_event, काष्ठा mlx4_qp *qp, पूर्णांक native)
अणु
	अटल स्थिर u16 op[MLX4_QP_NUM_STATE][MLX4_QP_NUM_STATE] = अणु
		[MLX4_QP_STATE_RST] = अणु
			[MLX4_QP_STATE_RST]	= MLX4_CMD_2RST_QP,
			[MLX4_QP_STATE_ERR]	= MLX4_CMD_2ERR_QP,
			[MLX4_QP_STATE_INIT]	= MLX4_CMD_RST2INIT_QP,
		पूर्ण,
		[MLX4_QP_STATE_INIT]  = अणु
			[MLX4_QP_STATE_RST]	= MLX4_CMD_2RST_QP,
			[MLX4_QP_STATE_ERR]	= MLX4_CMD_2ERR_QP,
			[MLX4_QP_STATE_INIT]	= MLX4_CMD_INIT2INIT_QP,
			[MLX4_QP_STATE_RTR]	= MLX4_CMD_INIT2RTR_QP,
		पूर्ण,
		[MLX4_QP_STATE_RTR]   = अणु
			[MLX4_QP_STATE_RST]	= MLX4_CMD_2RST_QP,
			[MLX4_QP_STATE_ERR]	= MLX4_CMD_2ERR_QP,
			[MLX4_QP_STATE_RTS]	= MLX4_CMD_RTR2RTS_QP,
		पूर्ण,
		[MLX4_QP_STATE_RTS]   = अणु
			[MLX4_QP_STATE_RST]	= MLX4_CMD_2RST_QP,
			[MLX4_QP_STATE_ERR]	= MLX4_CMD_2ERR_QP,
			[MLX4_QP_STATE_RTS]	= MLX4_CMD_RTS2RTS_QP,
			[MLX4_QP_STATE_SQD]	= MLX4_CMD_RTS2SQD_QP,
		पूर्ण,
		[MLX4_QP_STATE_SQD] = अणु
			[MLX4_QP_STATE_RST]	= MLX4_CMD_2RST_QP,
			[MLX4_QP_STATE_ERR]	= MLX4_CMD_2ERR_QP,
			[MLX4_QP_STATE_RTS]	= MLX4_CMD_SQD2RTS_QP,
			[MLX4_QP_STATE_SQD]	= MLX4_CMD_SQD2SQD_QP,
		पूर्ण,
		[MLX4_QP_STATE_SQER] = अणु
			[MLX4_QP_STATE_RST]	= MLX4_CMD_2RST_QP,
			[MLX4_QP_STATE_ERR]	= MLX4_CMD_2ERR_QP,
			[MLX4_QP_STATE_RTS]	= MLX4_CMD_SQERR2RTS_QP,
		पूर्ण,
		[MLX4_QP_STATE_ERR] = अणु
			[MLX4_QP_STATE_RST]	= MLX4_CMD_2RST_QP,
			[MLX4_QP_STATE_ERR]	= MLX4_CMD_2ERR_QP,
		पूर्ण
	पूर्ण;

	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_cmd_mailbox *mailbox;
	पूर्णांक ret = 0;
	पूर्णांक real_qp0 = 0;
	पूर्णांक proxy_qp0 = 0;
	u8 port;

	अगर (cur_state >= MLX4_QP_NUM_STATE || new_state >= MLX4_QP_NUM_STATE ||
	    !op[cur_state][new_state])
		वापस -EINVAL;

	अगर (op[cur_state][new_state] == MLX4_CMD_2RST_QP) अणु
		ret = mlx4_cmd(dev, 0, qp->qpn, 2,
			MLX4_CMD_2RST_QP, MLX4_CMD_TIME_CLASS_A, native);
		अगर (mlx4_is_master(dev) && cur_state != MLX4_QP_STATE_ERR &&
		    cur_state != MLX4_QP_STATE_RST &&
		    is_master_qp0(dev, qp, &real_qp0, &proxy_qp0)) अणु
			port = (qp->qpn & 1) + 1;
			अगर (proxy_qp0)
				priv->mfunc.master.qp0_state[port].proxy_qp0_active = 0;
			अन्यथा
				priv->mfunc.master.qp0_state[port].qp0_active = 0;
		पूर्ण
		वापस ret;
	पूर्ण

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	अगर (cur_state == MLX4_QP_STATE_RST && new_state == MLX4_QP_STATE_INIT) अणु
		u64 mtt_addr = mlx4_mtt_addr(dev, mtt);
		context->mtt_base_addr_h = mtt_addr >> 32;
		context->mtt_base_addr_l = cpu_to_be32(mtt_addr & 0xffffffff);
		context->log_page_size   = mtt->page_shअगरt - MLX4_ICM_PAGE_SHIFT;
	पूर्ण

	अगर ((cur_state == MLX4_QP_STATE_RTR) &&
	    (new_state == MLX4_QP_STATE_RTS) &&
	    dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_ROCE_V1_V2)
		context->roce_entropy =
			cpu_to_be16(mlx4_qp_roce_entropy(dev, qp->qpn));

	*(__be32 *) mailbox->buf = cpu_to_be32(optpar);
	स_नकल(mailbox->buf + 8, context, माप(*context));

	((काष्ठा mlx4_qp_context *) (mailbox->buf + 8))->local_qpn =
		cpu_to_be32(qp->qpn);

	ret = mlx4_cmd(dev, mailbox->dma,
		       qp->qpn | (!!sqd_event << 31),
		       new_state == MLX4_QP_STATE_RST ? 2 : 0,
		       op[cur_state][new_state], MLX4_CMD_TIME_CLASS_C, native);

	अगर (mlx4_is_master(dev) && is_master_qp0(dev, qp, &real_qp0, &proxy_qp0)) अणु
		port = (qp->qpn & 1) + 1;
		अगर (cur_state != MLX4_QP_STATE_ERR &&
		    cur_state != MLX4_QP_STATE_RST &&
		    new_state == MLX4_QP_STATE_ERR) अणु
			अगर (proxy_qp0)
				priv->mfunc.master.qp0_state[port].proxy_qp0_active = 0;
			अन्यथा
				priv->mfunc.master.qp0_state[port].qp0_active = 0;
		पूर्ण अन्यथा अगर (new_state == MLX4_QP_STATE_RTR) अणु
			अगर (proxy_qp0)
				priv->mfunc.master.qp0_state[port].proxy_qp0_active = 1;
			अन्यथा
				priv->mfunc.master.qp0_state[port].qp0_active = 1;
		पूर्ण
	पूर्ण

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस ret;
पूर्ण

पूर्णांक mlx4_qp_modअगरy(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mtt *mtt,
		   क्रमागत mlx4_qp_state cur_state, क्रमागत mlx4_qp_state new_state,
		   काष्ठा mlx4_qp_context *context,
		   क्रमागत mlx4_qp_optpar optpar,
		   पूर्णांक sqd_event, काष्ठा mlx4_qp *qp)
अणु
	वापस __mlx4_qp_modअगरy(dev, mtt, cur_state, new_state, context,
				optpar, sqd_event, qp, 0);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_qp_modअगरy);

पूर्णांक __mlx4_qp_reserve_range(काष्ठा mlx4_dev *dev, पूर्णांक cnt, पूर्णांक align,
			    पूर्णांक *base, u8 flags)
अणु
	u32 uid;
	पूर्णांक bf_qp = !!(flags & (u8)MLX4_RESERVE_ETH_BF_QP);

	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_qp_table *qp_table = &priv->qp_table;

	अगर (cnt > MLX4_MAX_BF_QP_RANGE && bf_qp)
		वापस -ENOMEM;

	uid = MLX4_QP_TABLE_ZONE_GENERAL;
	अगर (flags & (u8)MLX4_RESERVE_A0_QP) अणु
		अगर (bf_qp)
			uid = MLX4_QP_TABLE_ZONE_RAW_ETH;
		अन्यथा
			uid = MLX4_QP_TABLE_ZONE_RSS;
	पूर्ण

	*base = mlx4_zone_alloc_entries(qp_table->zones, uid, cnt, align,
					bf_qp ? MLX4_BF_QP_SKIP_MASK : 0, शून्य);
	अगर (*base == -1)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

पूर्णांक mlx4_qp_reserve_range(काष्ठा mlx4_dev *dev, पूर्णांक cnt, पूर्णांक align,
			  पूर्णांक *base, u8 flags, u8 usage)
अणु
	u32 in_modअगरier = RES_QP | (((u32)usage & 3) << 30);
	u64 in_param = 0;
	u64 out_param;
	पूर्णांक err;

	/* Turn off all unsupported QP allocation flags */
	flags &= dev->caps.alloc_res_qp_mask;

	अगर (mlx4_is_mfunc(dev)) अणु
		set_param_l(&in_param, (((u32)flags) << 24) | (u32)cnt);
		set_param_h(&in_param, align);
		err = mlx4_cmd_imm(dev, in_param, &out_param,
				   in_modअगरier, RES_OP_RESERVE,
				   MLX4_CMD_ALLOC_RES,
				   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
		अगर (err)
			वापस err;

		*base = get_param_l(&out_param);
		वापस 0;
	पूर्ण
	वापस __mlx4_qp_reserve_range(dev, cnt, align, base, flags);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_qp_reserve_range);

व्योम __mlx4_qp_release_range(काष्ठा mlx4_dev *dev, पूर्णांक base_qpn, पूर्णांक cnt)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_qp_table *qp_table = &priv->qp_table;

	अगर (mlx4_is_qp_reserved(dev, (u32) base_qpn))
		वापस;
	mlx4_zone_मुक्त_entries_unique(qp_table->zones, base_qpn, cnt);
पूर्ण

व्योम mlx4_qp_release_range(काष्ठा mlx4_dev *dev, पूर्णांक base_qpn, पूर्णांक cnt)
अणु
	u64 in_param = 0;
	पूर्णांक err;

	अगर (!cnt)
		वापस;

	अगर (mlx4_is_mfunc(dev)) अणु
		set_param_l(&in_param, base_qpn);
		set_param_h(&in_param, cnt);
		err = mlx4_cmd(dev, in_param, RES_QP, RES_OP_RESERVE,
			       MLX4_CMD_FREE_RES,
			       MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
		अगर (err) अणु
			mlx4_warn(dev, "Failed to release qp range base:%d cnt:%d\n",
				  base_qpn, cnt);
		पूर्ण
	पूर्ण अन्यथा
		 __mlx4_qp_release_range(dev, base_qpn, cnt);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_qp_release_range);

पूर्णांक __mlx4_qp_alloc_icm(काष्ठा mlx4_dev *dev, पूर्णांक qpn)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_qp_table *qp_table = &priv->qp_table;
	पूर्णांक err;

	err = mlx4_table_get(dev, &qp_table->qp_table, qpn);
	अगर (err)
		जाओ err_out;

	err = mlx4_table_get(dev, &qp_table->auxc_table, qpn);
	अगर (err)
		जाओ err_put_qp;

	err = mlx4_table_get(dev, &qp_table->altc_table, qpn);
	अगर (err)
		जाओ err_put_auxc;

	err = mlx4_table_get(dev, &qp_table->rdmarc_table, qpn);
	अगर (err)
		जाओ err_put_altc;

	err = mlx4_table_get(dev, &qp_table->cmpt_table, qpn);
	अगर (err)
		जाओ err_put_rdmarc;

	वापस 0;

err_put_rdmarc:
	mlx4_table_put(dev, &qp_table->rdmarc_table, qpn);

err_put_altc:
	mlx4_table_put(dev, &qp_table->altc_table, qpn);

err_put_auxc:
	mlx4_table_put(dev, &qp_table->auxc_table, qpn);

err_put_qp:
	mlx4_table_put(dev, &qp_table->qp_table, qpn);

err_out:
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_qp_alloc_icm(काष्ठा mlx4_dev *dev, पूर्णांक qpn)
अणु
	u64 param = 0;

	अगर (mlx4_is_mfunc(dev)) अणु
		set_param_l(&param, qpn);
		वापस mlx4_cmd_imm(dev, param, &param, RES_QP, RES_OP_MAP_ICM,
				    MLX4_CMD_ALLOC_RES, MLX4_CMD_TIME_CLASS_A,
				    MLX4_CMD_WRAPPED);
	पूर्ण
	वापस __mlx4_qp_alloc_icm(dev, qpn);
पूर्ण

व्योम __mlx4_qp_मुक्त_icm(काष्ठा mlx4_dev *dev, पूर्णांक qpn)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_qp_table *qp_table = &priv->qp_table;

	mlx4_table_put(dev, &qp_table->cmpt_table, qpn);
	mlx4_table_put(dev, &qp_table->rdmarc_table, qpn);
	mlx4_table_put(dev, &qp_table->altc_table, qpn);
	mlx4_table_put(dev, &qp_table->auxc_table, qpn);
	mlx4_table_put(dev, &qp_table->qp_table, qpn);
पूर्ण

अटल व्योम mlx4_qp_मुक्त_icm(काष्ठा mlx4_dev *dev, पूर्णांक qpn)
अणु
	u64 in_param = 0;

	अगर (mlx4_is_mfunc(dev)) अणु
		set_param_l(&in_param, qpn);
		अगर (mlx4_cmd(dev, in_param, RES_QP, RES_OP_MAP_ICM,
			     MLX4_CMD_FREE_RES, MLX4_CMD_TIME_CLASS_A,
			     MLX4_CMD_WRAPPED))
			mlx4_warn(dev, "Failed to free icm of qp:%d\n", qpn);
	पूर्ण अन्यथा
		__mlx4_qp_मुक्त_icm(dev, qpn);
पूर्ण

काष्ठा mlx4_qp *mlx4_qp_lookup(काष्ठा mlx4_dev *dev, u32 qpn)
अणु
	काष्ठा mlx4_qp_table *qp_table = &mlx4_priv(dev)->qp_table;
	काष्ठा mlx4_qp *qp;

	spin_lock_irq(&qp_table->lock);

	qp = __mlx4_qp_lookup(dev, qpn);

	spin_unlock_irq(&qp_table->lock);
	वापस qp;
पूर्ण

पूर्णांक mlx4_qp_alloc(काष्ठा mlx4_dev *dev, पूर्णांक qpn, काष्ठा mlx4_qp *qp)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_qp_table *qp_table = &priv->qp_table;
	पूर्णांक err;

	अगर (!qpn)
		वापस -EINVAL;

	qp->qpn = qpn;

	err = mlx4_qp_alloc_icm(dev, qpn);
	अगर (err)
		वापस err;

	spin_lock_irq(&qp_table->lock);
	err = radix_tree_insert(&dev->qp_table_tree, qp->qpn &
				(dev->caps.num_qps - 1), qp);
	spin_unlock_irq(&qp_table->lock);
	अगर (err)
		जाओ err_icm;

	refcount_set(&qp->refcount, 1);
	init_completion(&qp->मुक्त);

	वापस 0;

err_icm:
	mlx4_qp_मुक्त_icm(dev, qpn);
	वापस err;
पूर्ण

EXPORT_SYMBOL_GPL(mlx4_qp_alloc);

पूर्णांक mlx4_update_qp(काष्ठा mlx4_dev *dev, u32 qpn,
		   क्रमागत mlx4_update_qp_attr attr,
		   काष्ठा mlx4_update_qp_params *params)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_update_qp_context *cmd;
	u64 pri_addr_path_mask = 0;
	u64 qp_mask = 0;
	पूर्णांक err = 0;

	अगर (!attr || (attr & ~MLX4_UPDATE_QP_SUPPORTED_ATTRS))
		वापस -EINVAL;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	cmd = (काष्ठा mlx4_update_qp_context *)mailbox->buf;

	अगर (attr & MLX4_UPDATE_QP_SMAC) अणु
		pri_addr_path_mask |= 1ULL << MLX4_UPD_QP_PATH_MASK_MAC_INDEX;
		cmd->qp_context.pri_path.grh_mylmc = params->smac_index;
	पूर्ण

	अगर (attr & MLX4_UPDATE_QP_ETH_SRC_CHECK_MC_LB) अणु
		अगर (!(dev->caps.flags2
		      & MLX4_DEV_CAP_FLAG2_UPDATE_QP_SRC_CHECK_LB)) अणु
			mlx4_warn(dev,
				  "Trying to set src check LB, but it isn't supported\n");
			err = -EOPNOTSUPP;
			जाओ out;
		पूर्ण
		pri_addr_path_mask |=
			1ULL << MLX4_UPD_QP_PATH_MASK_ETH_SRC_CHECK_MC_LB;
		अगर (params->flags &
		    MLX4_UPDATE_QP_PARAMS_FLAGS_ETH_CHECK_MC_LB) अणु
			cmd->qp_context.pri_path.fl |=
				MLX4_FL_ETH_SRC_CHECK_MC_LB;
		पूर्ण
	पूर्ण

	अगर (attr & MLX4_UPDATE_QP_VSD) अणु
		qp_mask |= 1ULL << MLX4_UPD_QP_MASK_VSD;
		अगर (params->flags & MLX4_UPDATE_QP_PARAMS_FLAGS_VSD_ENABLE)
			cmd->qp_context.param3 |= cpu_to_be32(MLX4_STRIP_VLAN);
	पूर्ण

	अगर (attr & MLX4_UPDATE_QP_RATE_LIMIT) अणु
		qp_mask |= 1ULL << MLX4_UPD_QP_MASK_RATE_LIMIT;
		cmd->qp_context.rate_limit_params = cpu_to_be16((params->rate_unit << 14) | params->rate_val);
	पूर्ण

	अगर (attr & MLX4_UPDATE_QP_QOS_VPORT) अणु
		अगर (!(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_QOS_VPP)) अणु
			mlx4_warn(dev, "Granular QoS per VF is not enabled\n");
			err = -EOPNOTSUPP;
			जाओ out;
		पूर्ण

		qp_mask |= 1ULL << MLX4_UPD_QP_MASK_QOS_VPP;
		cmd->qp_context.qos_vport = params->qos_vport;
	पूर्ण

	cmd->primary_addr_path_mask = cpu_to_be64(pri_addr_path_mask);
	cmd->qp_mask = cpu_to_be64(qp_mask);

	err = mlx4_cmd(dev, mailbox->dma, qpn & 0xffffff, 0,
		       MLX4_CMD_UPDATE_QP, MLX4_CMD_TIME_CLASS_A,
		       MLX4_CMD_NATIVE);
out:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_update_qp);

व्योम mlx4_qp_हटाओ(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp)
अणु
	काष्ठा mlx4_qp_table *qp_table = &mlx4_priv(dev)->qp_table;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qp_table->lock, flags);
	radix_tree_delete(&dev->qp_table_tree, qp->qpn & (dev->caps.num_qps - 1));
	spin_unlock_irqrestore(&qp_table->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_qp_हटाओ);

व्योम mlx4_qp_मुक्त(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp)
अणु
	अगर (refcount_dec_and_test(&qp->refcount))
		complete(&qp->मुक्त);
	रुको_क्रम_completion(&qp->मुक्त);

	mlx4_qp_मुक्त_icm(dev, qp->qpn);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_qp_मुक्त);

अटल पूर्णांक mlx4_CONF_SPECIAL_QP(काष्ठा mlx4_dev *dev, u32 base_qpn)
अणु
	वापस mlx4_cmd(dev, 0, base_qpn, 0, MLX4_CMD_CONF_SPECIAL_QP,
			MLX4_CMD_TIME_CLASS_B, MLX4_CMD_NATIVE);
पूर्ण

#घोषणा MLX4_QP_TABLE_RSS_ETH_PRIORITY 2
#घोषणा MLX4_QP_TABLE_RAW_ETH_PRIORITY 1
#घोषणा MLX4_QP_TABLE_RAW_ETH_SIZE     256

अटल पूर्णांक mlx4_create_zones(काष्ठा mlx4_dev *dev,
			     u32 reserved_bottom_general,
			     u32 reserved_top_general,
			     u32 reserved_bottom_rss,
			     u32 start_offset_rss,
			     u32 max_table_offset)
अणु
	काष्ठा mlx4_qp_table *qp_table = &mlx4_priv(dev)->qp_table;
	काष्ठा mlx4_biपंचांगap (*biपंचांगap)[MLX4_QP_TABLE_ZONE_NUM] = शून्य;
	पूर्णांक biपंचांगap_initialized = 0;
	u32 last_offset;
	पूर्णांक k;
	पूर्णांक err;

	qp_table->zones = mlx4_zone_allocator_create(MLX4_ZONE_ALLOC_FLAGS_NO_OVERLAP);

	अगर (शून्य == qp_table->zones)
		वापस -ENOMEM;

	biपंचांगap = kदो_स्मृति(माप(*biपंचांगap), GFP_KERNEL);

	अगर (शून्य == biपंचांगap) अणु
		err = -ENOMEM;
		जाओ मुक्त_zone;
	पूर्ण

	err = mlx4_biपंचांगap_init(*biपंचांगap + MLX4_QP_TABLE_ZONE_GENERAL, dev->caps.num_qps,
			       (1 << 23) - 1, reserved_bottom_general,
			       reserved_top_general);

	अगर (err)
		जाओ मुक्त_biपंचांगap;

	++biपंचांगap_initialized;

	err = mlx4_zone_add_one(qp_table->zones, *biपंचांगap + MLX4_QP_TABLE_ZONE_GENERAL,
				MLX4_ZONE_FALLBACK_TO_HIGHER_PRIO |
				MLX4_ZONE_USE_RR, 0,
				0, qp_table->zones_uids + MLX4_QP_TABLE_ZONE_GENERAL);

	अगर (err)
		जाओ मुक्त_biपंचांगap;

	err = mlx4_biपंचांगap_init(*biपंचांगap + MLX4_QP_TABLE_ZONE_RSS,
			       reserved_bottom_rss,
			       reserved_bottom_rss - 1,
			       dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FW],
			       reserved_bottom_rss - start_offset_rss);

	अगर (err)
		जाओ मुक्त_biपंचांगap;

	++biपंचांगap_initialized;

	err = mlx4_zone_add_one(qp_table->zones, *biपंचांगap + MLX4_QP_TABLE_ZONE_RSS,
				MLX4_ZONE_ALLOW_ALLOC_FROM_LOWER_PRIO |
				MLX4_ZONE_ALLOW_ALLOC_FROM_EQ_PRIO |
				MLX4_ZONE_USE_RR, MLX4_QP_TABLE_RSS_ETH_PRIORITY,
				0, qp_table->zones_uids + MLX4_QP_TABLE_ZONE_RSS);

	अगर (err)
		जाओ मुक्त_biपंचांगap;

	last_offset = dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FW];
	/*  We have a single zone क्रम the A0 steering QPs area of the FW. This area
	 *  needs to be split पूर्णांकo subareas. One set of subareas is क्रम RSS QPs
	 *  (in which qp number bits 6 and/or 7 are set); the other set of subareas
	 *  is क्रम RAW_ETH QPs, which require that both bits 6 and 7 are zero.
	 *  Currently, the values वापसed by the FW (A0 steering area starting qp number
	 *  and A0 steering area size) are such that there are only two subareas -- one
	 *  क्रम RSS and one क्रम RAW_ETH.
	 */
	क्रम (k = MLX4_QP_TABLE_ZONE_RSS + 1; k < माप(*biपंचांगap)/माप((*biपंचांगap)[0]);
	     k++) अणु
		पूर्णांक size;
		u32 offset = start_offset_rss;
		u32 bf_mask;
		u32 requested_size;

		/* Assuming MLX4_BF_QP_SKIP_MASK is consecutive ones, this calculates
		 * a mask of all LSB bits set until (and not including) the first
		 * set bit of  MLX4_BF_QP_SKIP_MASK. For example, अगर MLX4_BF_QP_SKIP_MASK
		 * is 0xc0, bf_mask will be 0x3f.
		 */
		bf_mask = (MLX4_BF_QP_SKIP_MASK & ~(MLX4_BF_QP_SKIP_MASK - 1)) - 1;
		requested_size = min((u32)MLX4_QP_TABLE_RAW_ETH_SIZE, bf_mask + 1);

		अगर (((last_offset & MLX4_BF_QP_SKIP_MASK) &&
		     ((पूर्णांक)(max_table_offset - last_offset)) >=
		     roundup_घात_of_two(MLX4_BF_QP_SKIP_MASK)) ||
		    (!(last_offset & MLX4_BF_QP_SKIP_MASK) &&
		     !((last_offset + requested_size - 1) &
		       MLX4_BF_QP_SKIP_MASK)))
			size = requested_size;
		अन्यथा अणु
			u32 candidate_offset =
				(last_offset | MLX4_BF_QP_SKIP_MASK | bf_mask) + 1;

			अगर (last_offset & MLX4_BF_QP_SKIP_MASK)
				last_offset = candidate_offset;

			/* From this poपूर्णांक, the BF bits are 0 */

			अगर (last_offset > max_table_offset) अणु
				/* need to skip */
				size = -1;
			पूर्ण अन्यथा अणु
				size = min3(max_table_offset - last_offset,
					    bf_mask - (last_offset & bf_mask),
					    requested_size);
				अगर (size < requested_size) अणु
					पूर्णांक candidate_size;

					candidate_size = min3(
						max_table_offset - candidate_offset,
						bf_mask - (last_offset & bf_mask),
						requested_size);

					/*  We will not take this path अगर last_offset was
					 *  alपढ़ोy set above to candidate_offset
					 */
					अगर (candidate_size > size) अणु
						last_offset = candidate_offset;
						size = candidate_size;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (size > 0) अणु
			/* mlx4_biपंचांगap_alloc_range will find a contiguous range of "size"
			 * QPs in which both bits 6 and 7 are zero, because we pass it the
			 * MLX4_BF_SKIP_MASK).
			 */
			offset = mlx4_biपंचांगap_alloc_range(
					*biपंचांगap + MLX4_QP_TABLE_ZONE_RSS,
					size, 1,
					MLX4_BF_QP_SKIP_MASK);

			अगर (offset == (u32)-1) अणु
				err = -ENOMEM;
				अवरोध;
			पूर्ण

			last_offset = offset + size;

			err = mlx4_biपंचांगap_init(*biपंचांगap + k, roundup_घात_of_two(size),
					       roundup_घात_of_two(size) - 1, 0,
					       roundup_घात_of_two(size) - size);
		पूर्ण अन्यथा अणु
			/* Add an empty biपंचांगap, we'll allocate from dअगरferent zones (since
			 * at least one is reserved)
			 */
			err = mlx4_biपंचांगap_init(*biपंचांगap + k, 1,
					       MLX4_QP_TABLE_RAW_ETH_SIZE - 1, 0,
					       0);
			mlx4_biपंचांगap_alloc_range(*biपंचांगap + k, 1, 1, 0);
		पूर्ण

		अगर (err)
			अवरोध;

		++biपंचांगap_initialized;

		err = mlx4_zone_add_one(qp_table->zones, *biपंचांगap + k,
					MLX4_ZONE_ALLOW_ALLOC_FROM_LOWER_PRIO |
					MLX4_ZONE_ALLOW_ALLOC_FROM_EQ_PRIO |
					MLX4_ZONE_USE_RR, MLX4_QP_TABLE_RAW_ETH_PRIORITY,
					offset, qp_table->zones_uids + k);

		अगर (err)
			अवरोध;
	पूर्ण

	अगर (err)
		जाओ मुक्त_biपंचांगap;

	qp_table->biपंचांगap_gen = *biपंचांगap;

	वापस err;

मुक्त_biपंचांगap:
	क्रम (k = 0; k < biपंचांगap_initialized; k++)
		mlx4_biपंचांगap_cleanup(*biपंचांगap + k);
	kमुक्त(biपंचांगap);
मुक्त_zone:
	mlx4_zone_allocator_destroy(qp_table->zones);
	वापस err;
पूर्ण

अटल व्योम mlx4_cleanup_qp_zones(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_qp_table *qp_table = &mlx4_priv(dev)->qp_table;

	अगर (qp_table->zones) अणु
		पूर्णांक i;

		क्रम (i = 0;
		     i < माप(qp_table->zones_uids)/माप(qp_table->zones_uids[0]);
		     i++) अणु
			काष्ठा mlx4_biपंचांगap *biपंचांगap =
				mlx4_zone_get_biपंचांगap(qp_table->zones,
						     qp_table->zones_uids[i]);

			mlx4_zone_हटाओ_one(qp_table->zones, qp_table->zones_uids[i]);
			अगर (शून्य == biपंचांगap)
				जारी;

			mlx4_biपंचांगap_cleanup(biपंचांगap);
		पूर्ण
		mlx4_zone_allocator_destroy(qp_table->zones);
		kमुक्त(qp_table->biपंचांगap_gen);
		qp_table->biपंचांगap_gen = शून्य;
		qp_table->zones = शून्य;
	पूर्ण
पूर्ण

पूर्णांक mlx4_init_qp_table(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_qp_table *qp_table = &mlx4_priv(dev)->qp_table;
	पूर्णांक err;
	पूर्णांक reserved_from_top = 0;
	पूर्णांक reserved_from_bot;
	पूर्णांक k;
	पूर्णांक fixed_reserved_from_bot_rv = 0;
	पूर्णांक bottom_reserved_क्रम_rss_biपंचांगap;
	u32 max_table_offset = dev->caps.dmfs_high_rate_qpn_base +
			dev->caps.dmfs_high_rate_qpn_range;

	spin_lock_init(&qp_table->lock);
	INIT_RADIX_TREE(&dev->qp_table_tree, GFP_ATOMIC);
	अगर (mlx4_is_slave(dev))
		वापस 0;

	/* We reserve 2 extra QPs per port क्रम the special QPs.  The
	 * block of special QPs must be aligned to a multiple of 8, so
	 * round up.
	 *
	 * We also reserve the MSB of the 24-bit QP number to indicate
	 * that a QP is an XRC QP.
	 */
	क्रम (k = 0; k <= MLX4_QP_REGION_BOTTOM; k++)
		fixed_reserved_from_bot_rv += dev->caps.reserved_qps_cnt[k];

	अगर (fixed_reserved_from_bot_rv < max_table_offset)
		fixed_reserved_from_bot_rv = max_table_offset;

	/* We reserve at least 1 extra क्रम biपंचांगaps that we करोn't have enough space क्रम*/
	bottom_reserved_क्रम_rss_biपंचांगap =
		roundup_घात_of_two(fixed_reserved_from_bot_rv + 1);
	dev->phys_caps.base_sqpn = ALIGN(bottom_reserved_क्रम_rss_biपंचांगap, 8);

	अणु
		पूर्णांक sort[MLX4_NUM_QP_REGION];
		पूर्णांक i, j;
		पूर्णांक last_base = dev->caps.num_qps;

		क्रम (i = 1; i < MLX4_NUM_QP_REGION; ++i)
			sort[i] = i;

		क्रम (i = MLX4_NUM_QP_REGION; i > MLX4_QP_REGION_BOTTOM; --i) अणु
			क्रम (j = MLX4_QP_REGION_BOTTOM + 2; j < i; ++j) अणु
				अगर (dev->caps.reserved_qps_cnt[sort[j]] >
				    dev->caps.reserved_qps_cnt[sort[j - 1]])
					swap(sort[j], sort[j - 1]);
			पूर्ण
		पूर्ण

		क्रम (i = MLX4_QP_REGION_BOTTOM + 1; i < MLX4_NUM_QP_REGION; ++i) अणु
			last_base -= dev->caps.reserved_qps_cnt[sort[i]];
			dev->caps.reserved_qps_base[sort[i]] = last_base;
			reserved_from_top +=
				dev->caps.reserved_qps_cnt[sort[i]];
		पूर्ण
	पूर्ण

       /* Reserve 8 real SQPs in both native and SRIOV modes.
	* In addition, in SRIOV mode, reserve 8 proxy SQPs per function
	* (क्रम all PFs and VFs), and 8 corresponding tunnel QPs.
	* Each proxy SQP works opposite its own tunnel QP.
	*
	* The QPs are arranged as follows:
	* a. 8 real SQPs
	* b. All the proxy SQPs (8 per function)
	* c. All the tunnel QPs (8 per function)
	*/
	reserved_from_bot = mlx4_num_reserved_sqps(dev);
	अगर (reserved_from_bot + reserved_from_top > dev->caps.num_qps) अणु
		mlx4_err(dev, "Number of reserved QPs is higher than number of QPs\n");
		वापस -EINVAL;
	पूर्ण

	err = mlx4_create_zones(dev, reserved_from_bot, reserved_from_bot,
				bottom_reserved_क्रम_rss_biपंचांगap,
				fixed_reserved_from_bot_rv,
				max_table_offset);

	अगर (err)
		वापस err;

	अगर (mlx4_is_mfunc(dev)) अणु
		/* क्रम PPF use */
		dev->phys_caps.base_proxy_sqpn = dev->phys_caps.base_sqpn + 8;
		dev->phys_caps.base_tunnel_sqpn = dev->phys_caps.base_sqpn + 8 + 8 * MLX4_MFUNC_MAX;

		/* In mfunc, calculate proxy and tunnel qp offsets क्रम the PF here,
		 * since the PF करोes not call mlx4_slave_caps */
		dev->caps.spec_qps = kसुस्मृति(dev->caps.num_ports,
					     माप(*dev->caps.spec_qps),
					     GFP_KERNEL);
		अगर (!dev->caps.spec_qps) अणु
			err = -ENOMEM;
			जाओ err_mem;
		पूर्ण

		क्रम (k = 0; k < dev->caps.num_ports; k++) अणु
			dev->caps.spec_qps[k].qp0_proxy = dev->phys_caps.base_proxy_sqpn +
				8 * mlx4_master_func_num(dev) + k;
			dev->caps.spec_qps[k].qp0_tunnel = dev->caps.spec_qps[k].qp0_proxy + 8 * MLX4_MFUNC_MAX;
			dev->caps.spec_qps[k].qp1_proxy = dev->phys_caps.base_proxy_sqpn +
				8 * mlx4_master_func_num(dev) + MLX4_MAX_PORTS + k;
			dev->caps.spec_qps[k].qp1_tunnel = dev->caps.spec_qps[k].qp1_proxy + 8 * MLX4_MFUNC_MAX;
		पूर्ण
	पूर्ण


	err = mlx4_CONF_SPECIAL_QP(dev, dev->phys_caps.base_sqpn);
	अगर (err)
		जाओ err_mem;

	वापस err;

err_mem:
	kमुक्त(dev->caps.spec_qps);
	dev->caps.spec_qps = शून्य;
	mlx4_cleanup_qp_zones(dev);
	वापस err;
पूर्ण

व्योम mlx4_cleanup_qp_table(काष्ठा mlx4_dev *dev)
अणु
	अगर (mlx4_is_slave(dev))
		वापस;

	mlx4_CONF_SPECIAL_QP(dev, 0);

	mlx4_cleanup_qp_zones(dev);
पूर्ण

पूर्णांक mlx4_qp_query(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp,
		  काष्ठा mlx4_qp_context *context)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	पूर्णांक err;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	err = mlx4_cmd_box(dev, 0, mailbox->dma, qp->qpn, 0,
			   MLX4_CMD_QUERY_QP, MLX4_CMD_TIME_CLASS_A,
			   MLX4_CMD_WRAPPED);
	अगर (!err)
		स_नकल(context, mailbox->buf + 8, माप(*context));

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_qp_query);

पूर्णांक mlx4_qp_to_पढ़ोy(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mtt *mtt,
		     काष्ठा mlx4_qp_context *context,
		     काष्ठा mlx4_qp *qp, क्रमागत mlx4_qp_state *qp_state)
अणु
	पूर्णांक err;
	पूर्णांक i;
	क्रमागत mlx4_qp_state states[] = अणु
		MLX4_QP_STATE_RST,
		MLX4_QP_STATE_INIT,
		MLX4_QP_STATE_RTR,
		MLX4_QP_STATE_RTS
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(states) - 1; i++) अणु
		context->flags &= cpu_to_be32(~(0xf << 28));
		context->flags |= cpu_to_be32(states[i + 1] << 28);
		अगर (states[i + 1] != MLX4_QP_STATE_RTR)
			context->params2 &= ~cpu_to_be32(MLX4_QP_BIT_FPP);
		err = mlx4_qp_modअगरy(dev, mtt, states[i], states[i + 1],
				     context, 0, 0, qp);
		अगर (err) अणु
			mlx4_err(dev, "Failed to bring QP to state: %d with error: %d\n",
				 states[i + 1], err);
			वापस err;
		पूर्ण

		*qp_state = states[i + 1];
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_qp_to_पढ़ोy);

u16 mlx4_qp_roce_entropy(काष्ठा mlx4_dev *dev, u32 qpn)
अणु
	काष्ठा mlx4_qp_context context;
	काष्ठा mlx4_qp qp;
	पूर्णांक err;

	qp.qpn = qpn;
	err = mlx4_qp_query(dev, &qp, &context);
	अगर (!err) अणु
		u32 dest_qpn = be32_to_cpu(context.remote_qpn) & 0xffffff;
		u16 folded_dst = folded_qp(dest_qpn);
		u16 folded_src = folded_qp(qpn);

		वापस (dest_qpn != qpn) ?
			((folded_dst ^ folded_src) | 0xC000) :
			folded_src | 0xC000;
	पूर्ण
	वापस 0xdead;
पूर्ण
