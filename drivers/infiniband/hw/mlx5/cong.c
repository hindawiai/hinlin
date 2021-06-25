<शैली गुरु>
/*
 * Copyright (c) 2013-2017, Mellanox Technologies. All rights reserved.
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

#समावेश <linux/debugfs.h>

#समावेश "mlx5_ib.h"
#समावेश "cmd.h"

क्रमागत mlx5_ib_cong_node_type अणु
	MLX5_IB_RROCE_ECN_RP = 1,
	MLX5_IB_RROCE_ECN_NP = 2,
पूर्ण;

अटल स्थिर अक्षर * स्थिर mlx5_ib_dbg_cc_name[] = अणु
	"rp_clamp_tgt_rate",
	"rp_clamp_tgt_rate_ati",
	"rp_time_reset",
	"rp_byte_reset",
	"rp_threshold",
	"rp_ai_rate",
	"rp_max_rate",
	"rp_hai_rate",
	"rp_min_dec_fac",
	"rp_min_rate",
	"rp_rate_to_set_on_first_cnp",
	"rp_dce_tcp_g",
	"rp_dce_tcp_rtt",
	"rp_rate_reduce_monitor_period",
	"rp_initial_alpha_value",
	"rp_gd",
	"np_min_time_between_cnps",
	"np_cnp_dscp",
	"np_cnp_prio_mode",
	"np_cnp_prio",
पूर्ण;

#घोषणा MLX5_IB_RP_CLAMP_TGT_RATE_ATTR			BIT(1)
#घोषणा MLX5_IB_RP_CLAMP_TGT_RATE_ATI_ATTR		BIT(2)
#घोषणा MLX5_IB_RP_TIME_RESET_ATTR			BIT(3)
#घोषणा MLX5_IB_RP_BYTE_RESET_ATTR			BIT(4)
#घोषणा MLX5_IB_RP_THRESHOLD_ATTR			BIT(5)
#घोषणा MLX5_IB_RP_MAX_RATE_ATTR			BIT(6)
#घोषणा MLX5_IB_RP_AI_RATE_ATTR				BIT(7)
#घोषणा MLX5_IB_RP_HAI_RATE_ATTR			BIT(8)
#घोषणा MLX5_IB_RP_MIN_DEC_FAC_ATTR			BIT(9)
#घोषणा MLX5_IB_RP_MIN_RATE_ATTR			BIT(10)
#घोषणा MLX5_IB_RP_RATE_TO_SET_ON_FIRST_CNP_ATTR	BIT(11)
#घोषणा MLX5_IB_RP_DCE_TCP_G_ATTR			BIT(12)
#घोषणा MLX5_IB_RP_DCE_TCP_RTT_ATTR			BIT(13)
#घोषणा MLX5_IB_RP_RATE_REDUCE_MONITOR_PERIOD_ATTR	BIT(14)
#घोषणा MLX5_IB_RP_INITIAL_ALPHA_VALUE_ATTR		BIT(15)
#घोषणा MLX5_IB_RP_GD_ATTR				BIT(16)

#घोषणा MLX5_IB_NP_MIN_TIME_BETWEEN_CNPS_ATTR		BIT(2)
#घोषणा MLX5_IB_NP_CNP_DSCP_ATTR			BIT(3)
#घोषणा MLX5_IB_NP_CNP_PRIO_MODE_ATTR			BIT(4)

अटल क्रमागत mlx5_ib_cong_node_type
mlx5_ib_param_to_node(क्रमागत mlx5_ib_dbg_cc_types param_offset)
अणु
	अगर (param_offset >= MLX5_IB_DBG_CC_RP_CLAMP_TGT_RATE &&
	    param_offset <= MLX5_IB_DBG_CC_RP_GD)
		वापस MLX5_IB_RROCE_ECN_RP;
	अन्यथा
		वापस MLX5_IB_RROCE_ECN_NP;
पूर्ण

अटल u32 mlx5_get_cc_param_val(व्योम *field, पूर्णांक offset)
अणु
	चयन (offset) अणु
	हाल MLX5_IB_DBG_CC_RP_CLAMP_TGT_RATE:
		वापस MLX5_GET(cong_control_r_roce_ecn_rp, field,
				clamp_tgt_rate);
	हाल MLX5_IB_DBG_CC_RP_CLAMP_TGT_RATE_ATI:
		वापस MLX5_GET(cong_control_r_roce_ecn_rp, field,
				clamp_tgt_rate_after_समय_inc);
	हाल MLX5_IB_DBG_CC_RP_TIME_RESET:
		वापस MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rpg_समय_reset);
	हाल MLX5_IB_DBG_CC_RP_BYTE_RESET:
		वापस MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rpg_byte_reset);
	हाल MLX5_IB_DBG_CC_RP_THRESHOLD:
		वापस MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rpg_threshold);
	हाल MLX5_IB_DBG_CC_RP_AI_RATE:
		वापस MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rpg_ai_rate);
	हाल MLX5_IB_DBG_CC_RP_MAX_RATE:
		वापस MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rpg_max_rate);
	हाल MLX5_IB_DBG_CC_RP_HAI_RATE:
		वापस MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rpg_hai_rate);
	हाल MLX5_IB_DBG_CC_RP_MIN_DEC_FAC:
		वापस MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rpg_min_dec_fac);
	हाल MLX5_IB_DBG_CC_RP_MIN_RATE:
		वापस MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rpg_min_rate);
	हाल MLX5_IB_DBG_CC_RP_RATE_TO_SET_ON_FIRST_CNP:
		वापस MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rate_to_set_on_first_cnp);
	हाल MLX5_IB_DBG_CC_RP_DCE_TCP_G:
		वापस MLX5_GET(cong_control_r_roce_ecn_rp, field,
				dce_tcp_g);
	हाल MLX5_IB_DBG_CC_RP_DCE_TCP_RTT:
		वापस MLX5_GET(cong_control_r_roce_ecn_rp, field,
				dce_tcp_rtt);
	हाल MLX5_IB_DBG_CC_RP_RATE_REDUCE_MONITOR_PERIOD:
		वापस MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rate_reduce_monitor_period);
	हाल MLX5_IB_DBG_CC_RP_INITIAL_ALPHA_VALUE:
		वापस MLX5_GET(cong_control_r_roce_ecn_rp, field,
				initial_alpha_value);
	हाल MLX5_IB_DBG_CC_RP_GD:
		वापस MLX5_GET(cong_control_r_roce_ecn_rp, field,
				rpg_gd);
	हाल MLX5_IB_DBG_CC_NP_MIN_TIME_BETWEEN_CNPS:
		वापस MLX5_GET(cong_control_r_roce_ecn_np, field,
				min_समय_between_cnps);
	हाल MLX5_IB_DBG_CC_NP_CNP_DSCP:
		वापस MLX5_GET(cong_control_r_roce_ecn_np, field,
				cnp_dscp);
	हाल MLX5_IB_DBG_CC_NP_CNP_PRIO_MODE:
		वापस MLX5_GET(cong_control_r_roce_ecn_np, field,
				cnp_prio_mode);
	हाल MLX5_IB_DBG_CC_NP_CNP_PRIO:
		वापस MLX5_GET(cong_control_r_roce_ecn_np, field,
				cnp_802p_prio);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम mlx5_ib_set_cc_param_mask_val(व्योम *field, पूर्णांक offset,
					  u32 var, u32 *attr_mask)
अणु
	चयन (offset) अणु
	हाल MLX5_IB_DBG_CC_RP_CLAMP_TGT_RATE:
		*attr_mask |= MLX5_IB_RP_CLAMP_TGT_RATE_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 clamp_tgt_rate, var);
		अवरोध;
	हाल MLX5_IB_DBG_CC_RP_CLAMP_TGT_RATE_ATI:
		*attr_mask |= MLX5_IB_RP_CLAMP_TGT_RATE_ATI_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 clamp_tgt_rate_after_समय_inc, var);
		अवरोध;
	हाल MLX5_IB_DBG_CC_RP_TIME_RESET:
		*attr_mask |= MLX5_IB_RP_TIME_RESET_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rpg_समय_reset, var);
		अवरोध;
	हाल MLX5_IB_DBG_CC_RP_BYTE_RESET:
		*attr_mask |= MLX5_IB_RP_BYTE_RESET_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rpg_byte_reset, var);
		अवरोध;
	हाल MLX5_IB_DBG_CC_RP_THRESHOLD:
		*attr_mask |= MLX5_IB_RP_THRESHOLD_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rpg_threshold, var);
		अवरोध;
	हाल MLX5_IB_DBG_CC_RP_AI_RATE:
		*attr_mask |= MLX5_IB_RP_AI_RATE_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rpg_ai_rate, var);
		अवरोध;
	हाल MLX5_IB_DBG_CC_RP_MAX_RATE:
		*attr_mask |= MLX5_IB_RP_MAX_RATE_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rpg_max_rate, var);
		अवरोध;
	हाल MLX5_IB_DBG_CC_RP_HAI_RATE:
		*attr_mask |= MLX5_IB_RP_HAI_RATE_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rpg_hai_rate, var);
		अवरोध;
	हाल MLX5_IB_DBG_CC_RP_MIN_DEC_FAC:
		*attr_mask |= MLX5_IB_RP_MIN_DEC_FAC_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rpg_min_dec_fac, var);
		अवरोध;
	हाल MLX5_IB_DBG_CC_RP_MIN_RATE:
		*attr_mask |= MLX5_IB_RP_MIN_RATE_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rpg_min_rate, var);
		अवरोध;
	हाल MLX5_IB_DBG_CC_RP_RATE_TO_SET_ON_FIRST_CNP:
		*attr_mask |= MLX5_IB_RP_RATE_TO_SET_ON_FIRST_CNP_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rate_to_set_on_first_cnp, var);
		अवरोध;
	हाल MLX5_IB_DBG_CC_RP_DCE_TCP_G:
		*attr_mask |= MLX5_IB_RP_DCE_TCP_G_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 dce_tcp_g, var);
		अवरोध;
	हाल MLX5_IB_DBG_CC_RP_DCE_TCP_RTT:
		*attr_mask |= MLX5_IB_RP_DCE_TCP_RTT_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 dce_tcp_rtt, var);
		अवरोध;
	हाल MLX5_IB_DBG_CC_RP_RATE_REDUCE_MONITOR_PERIOD:
		*attr_mask |= MLX5_IB_RP_RATE_REDUCE_MONITOR_PERIOD_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rate_reduce_monitor_period, var);
		अवरोध;
	हाल MLX5_IB_DBG_CC_RP_INITIAL_ALPHA_VALUE:
		*attr_mask |= MLX5_IB_RP_INITIAL_ALPHA_VALUE_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 initial_alpha_value, var);
		अवरोध;
	हाल MLX5_IB_DBG_CC_RP_GD:
		*attr_mask |= MLX5_IB_RP_GD_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_rp, field,
			 rpg_gd, var);
		अवरोध;
	हाल MLX5_IB_DBG_CC_NP_MIN_TIME_BETWEEN_CNPS:
		*attr_mask |= MLX5_IB_NP_MIN_TIME_BETWEEN_CNPS_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_np, field,
			 min_समय_between_cnps, var);
		अवरोध;
	हाल MLX5_IB_DBG_CC_NP_CNP_DSCP:
		*attr_mask |= MLX5_IB_NP_CNP_DSCP_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_np, field, cnp_dscp, var);
		अवरोध;
	हाल MLX5_IB_DBG_CC_NP_CNP_PRIO_MODE:
		*attr_mask |= MLX5_IB_NP_CNP_PRIO_MODE_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_np, field, cnp_prio_mode, var);
		अवरोध;
	हाल MLX5_IB_DBG_CC_NP_CNP_PRIO:
		*attr_mask |= MLX5_IB_NP_CNP_PRIO_MODE_ATTR;
		MLX5_SET(cong_control_r_roce_ecn_np, field, cnp_prio_mode, 0);
		MLX5_SET(cong_control_r_roce_ecn_np, field, cnp_802p_prio, var);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_ib_get_cc_params(काष्ठा mlx5_ib_dev *dev, u32 port_num,
				 पूर्णांक offset, u32 *var)
अणु
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(query_cong_params_out);
	व्योम *out;
	व्योम *field;
	पूर्णांक err;
	क्रमागत mlx5_ib_cong_node_type node;
	काष्ठा mlx5_core_dev *mdev;

	/* Takes a 1-based port number */
	mdev = mlx5_ib_get_native_port_mdev(dev, port_num + 1, शून्य);
	अगर (!mdev)
		वापस -ENODEV;

	out = kvzalloc(outlen, GFP_KERNEL);
	अगर (!out) अणु
		err = -ENOMEM;
		जाओ alloc_err;
	पूर्ण

	node = mlx5_ib_param_to_node(offset);

	err = mlx5_cmd_query_cong_params(mdev, node, out);
	अगर (err)
		जाओ मुक्त;

	field = MLX5_ADDR_OF(query_cong_params_out, out, congestion_parameters);
	*var = mlx5_get_cc_param_val(field, offset);

मुक्त:
	kvमुक्त(out);
alloc_err:
	mlx5_ib_put_native_port_mdev(dev, port_num + 1);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_ib_set_cc_params(काष्ठा mlx5_ib_dev *dev, u32 port_num,
				 पूर्णांक offset, u32 var)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(modअगरy_cong_params_in);
	व्योम *in;
	व्योम *field;
	क्रमागत mlx5_ib_cong_node_type node;
	काष्ठा mlx5_core_dev *mdev;
	u32 attr_mask = 0;
	पूर्णांक err;

	/* Takes a 1-based port number */
	mdev = mlx5_ib_get_native_port_mdev(dev, port_num + 1, शून्य);
	अगर (!mdev)
		वापस -ENODEV;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		जाओ alloc_err;
	पूर्ण

	MLX5_SET(modअगरy_cong_params_in, in, opcode,
		 MLX5_CMD_OP_MODIFY_CONG_PARAMS);

	node = mlx5_ib_param_to_node(offset);
	MLX5_SET(modअगरy_cong_params_in, in, cong_protocol, node);

	field = MLX5_ADDR_OF(modअगरy_cong_params_in, in, congestion_parameters);
	mlx5_ib_set_cc_param_mask_val(field, offset, var, &attr_mask);

	field = MLX5_ADDR_OF(modअगरy_cong_params_in, in, field_select);
	MLX5_SET(field_select_r_roce_rp, field, field_select_r_roce_rp,
		 attr_mask);

	err = mlx5_cmd_exec_in(dev->mdev, modअगरy_cong_params, in);
	kvमुक्त(in);
alloc_err:
	mlx5_ib_put_native_port_mdev(dev, port_num + 1);
	वापस err;
पूर्ण

अटल sमाप_प्रकार set_param(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा mlx5_ib_dbg_param *param = filp->निजी_data;
	पूर्णांक offset = param->offset;
	अक्षर lbuf[11] = अणु पूर्ण;
	u32 var;
	पूर्णांक ret;

	अगर (count > माप(lbuf))
		वापस -EINVAL;

	अगर (copy_from_user(lbuf, buf, count))
		वापस -EFAULT;

	lbuf[माप(lbuf) - 1] = '\0';

	अगर (kstrtou32(lbuf, 0, &var))
		वापस -EINVAL;

	ret = mlx5_ib_set_cc_params(param->dev, param->port_num, offset, var);
	वापस ret ? ret : count;
पूर्ण

अटल sमाप_प्रकार get_param(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count,
			 loff_t *pos)
अणु
	काष्ठा mlx5_ib_dbg_param *param = filp->निजी_data;
	पूर्णांक offset = param->offset;
	u32 var = 0;
	पूर्णांक ret;
	अक्षर lbuf[11];

	ret = mlx5_ib_get_cc_params(param->dev, param->port_num, offset, &var);
	अगर (ret)
		वापस ret;

	ret = snम_लिखो(lbuf, माप(lbuf), "%d\n", var);
	अगर (ret < 0)
		वापस ret;

	वापस simple_पढ़ो_from_buffer(buf, count, pos, lbuf, ret);
पूर्ण

अटल स्थिर काष्ठा file_operations dbg_cc_fops = अणु
	.owner	= THIS_MODULE,
	.खोलो	= simple_खोलो,
	.ग_लिखो	= set_param,
	.पढ़ो	= get_param,
पूर्ण;

व्योम mlx5_ib_cleanup_cong_debugfs(काष्ठा mlx5_ib_dev *dev, u32 port_num)
अणु
	अगर (!mlx5_debugfs_root ||
	    !dev->port[port_num].dbg_cc_params ||
	    !dev->port[port_num].dbg_cc_params->root)
		वापस;

	debugfs_हटाओ_recursive(dev->port[port_num].dbg_cc_params->root);
	kमुक्त(dev->port[port_num].dbg_cc_params);
	dev->port[port_num].dbg_cc_params = शून्य;
पूर्ण

व्योम mlx5_ib_init_cong_debugfs(काष्ठा mlx5_ib_dev *dev, u32 port_num)
अणु
	काष्ठा mlx5_ib_dbg_cc_params *dbg_cc_params;
	काष्ठा mlx5_core_dev *mdev;
	पूर्णांक i;

	अगर (!mlx5_debugfs_root)
		वापस;

	/* Takes a 1-based port number */
	mdev = mlx5_ib_get_native_port_mdev(dev, port_num + 1, शून्य);
	अगर (!mdev)
		वापस;

	अगर (!MLX5_CAP_GEN(mdev, cc_query_allowed) ||
	    !MLX5_CAP_GEN(mdev, cc_modअगरy_allowed))
		जाओ put_mdev;

	dbg_cc_params = kzalloc(माप(*dbg_cc_params), GFP_KERNEL);
	अगर (!dbg_cc_params)
		जाओ err;

	dev->port[port_num].dbg_cc_params = dbg_cc_params;

	dbg_cc_params->root = debugfs_create_dir("cc_params",
						 mdev->priv.dbg_root);

	क्रम (i = 0; i < MLX5_IB_DBG_CC_MAX; i++) अणु
		dbg_cc_params->params[i].offset = i;
		dbg_cc_params->params[i].dev = dev;
		dbg_cc_params->params[i].port_num = port_num;
		dbg_cc_params->params[i].dentry =
			debugfs_create_file(mlx5_ib_dbg_cc_name[i],
					    0600, dbg_cc_params->root,
					    &dbg_cc_params->params[i],
					    &dbg_cc_fops);
	पूर्ण

put_mdev:
	mlx5_ib_put_native_port_mdev(dev, port_num + 1);
	वापस;

err:
	mlx5_ib_warn(dev, "cong debugfs failure\n");
	mlx5_ib_cleanup_cong_debugfs(dev, port_num);
	mlx5_ib_put_native_port_mdev(dev, port_num + 1);

	/*
	 * We करोn't want to fail driver अगर debugfs failed to initialize,
	 * so we are not क्रमwarding error to the user.
	 */
	वापस;
पूर्ण
