<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2020, Mellanox Technologies inc.  All rights reserved.
 */

#समावेश <rdma/uverbs_ioctl.h>
#समावेश <rdma/mlx5_user_ioctl_cmds.h>
#समावेश <rdma/mlx5_user_ioctl_verbs.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/eचयन.h>
#समावेश <linux/mlx5/vport.h>
#समावेश "mlx5_ib.h"

#घोषणा UVERBS_MODULE_NAME mlx5_ib
#समावेश <rdma/uverbs_named_ioctl.h>

अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_PD_QUERY)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_pd *pd =
		uverbs_attr_get_obj(attrs, MLX5_IB_ATTR_QUERY_PD_HANDLE);
	काष्ठा mlx5_ib_pd *mpd = to_mpd(pd);

	वापस uverbs_copy_to(attrs, MLX5_IB_ATTR_QUERY_PD_RESP_PDN,
			      &mpd->pdn, माप(mpd->pdn));
पूर्ण

अटल पूर्णांक fill_vport_icm_addr(काष्ठा mlx5_core_dev *mdev, u16 vport,
			       काष्ठा mlx5_ib_uapi_query_port *info)
अणु
	u32 out[MLX5_ST_SZ_DW(query_esw_vport_context_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(query_esw_vport_context_in)] = अणुपूर्ण;
	bool sw_owner_supp;
	u64 icm_rx;
	u64 icm_tx;
	पूर्णांक err;

	sw_owner_supp = MLX5_CAP_ESW_FLOWTABLE_FDB(mdev, sw_owner) ||
			MLX5_CAP_ESW_FLOWTABLE_FDB(mdev, sw_owner_v2);

	अगर (vport == MLX5_VPORT_UPLINK) अणु
		icm_rx = MLX5_CAP64_ESW_FLOWTABLE(mdev,
			sw_steering_uplink_icm_address_rx);
		icm_tx = MLX5_CAP64_ESW_FLOWTABLE(mdev,
			sw_steering_uplink_icm_address_tx);
	पूर्ण अन्यथा अणु
		MLX5_SET(query_esw_vport_context_in, in, opcode,
			 MLX5_CMD_OP_QUERY_ESW_VPORT_CONTEXT);
		MLX5_SET(query_esw_vport_context_in, in, vport_number, vport);
		MLX5_SET(query_esw_vport_context_in, in, other_vport, true);

		err = mlx5_cmd_exec_inout(mdev, query_esw_vport_context, in,
					  out);

		अगर (err)
			वापस err;

		icm_rx = MLX5_GET64(
			query_esw_vport_context_out, out,
			esw_vport_context.sw_steering_vport_icm_address_rx);

		icm_tx = MLX5_GET64(
			query_esw_vport_context_out, out,
			esw_vport_context.sw_steering_vport_icm_address_tx);
	पूर्ण

	अगर (sw_owner_supp && icm_rx) अणु
		info->vport_steering_icm_rx = icm_rx;
		info->flags |=
			MLX5_IB_UAPI_QUERY_PORT_VPORT_STEERING_ICM_RX;
	पूर्ण

	अगर (sw_owner_supp && icm_tx) अणु
		info->vport_steering_icm_tx = icm_tx;
		info->flags |=
			MLX5_IB_UAPI_QUERY_PORT_VPORT_STEERING_ICM_TX;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fill_vport_vhca_id(काष्ठा mlx5_core_dev *mdev, u16 vport,
			      काष्ठा mlx5_ib_uapi_query_port *info)
अणु
	माप_प्रकार out_sz = MLX5_ST_SZ_BYTES(query_hca_cap_out);
	u32 in[MLX5_ST_SZ_DW(query_hca_cap_in)] = अणुपूर्ण;
	व्योम *out;
	पूर्णांक err;

	out = kzalloc(out_sz, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	MLX5_SET(query_hca_cap_in, in, opcode, MLX5_CMD_OP_QUERY_HCA_CAP);
	MLX5_SET(query_hca_cap_in, in, other_function, true);
	MLX5_SET(query_hca_cap_in, in, function_id, vport);
	MLX5_SET(query_hca_cap_in, in, op_mod,
		 MLX5_SET_HCA_CAP_OP_MOD_GENERAL_DEVICE |
		 HCA_CAP_OPMOD_GET_CUR);

	err = mlx5_cmd_exec(mdev, in, माप(in), out, out_sz);
	अगर (err)
		जाओ out;

	info->vport_vhca_id = MLX5_GET(query_hca_cap_out, out,
				       capability.cmd_hca_cap.vhca_id);

	info->flags |= MLX5_IB_UAPI_QUERY_PORT_VPORT_VHCA_ID;
out:
	kमुक्त(out);
	वापस err;
पूर्ण

अटल पूर्णांक fill_चयनdev_info(काष्ठा mlx5_ib_dev *dev, u32 port_num,
			       काष्ठा mlx5_ib_uapi_query_port *info)
अणु
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	काष्ठा mlx5_eचयन_rep *rep;
	पूर्णांक err;

	rep = dev->port[port_num - 1].rep;
	अगर (!rep)
		वापस -EOPNOTSUPP;

	info->vport = rep->vport;
	info->flags |= MLX5_IB_UAPI_QUERY_PORT_VPORT;

	अगर (rep->vport != MLX5_VPORT_UPLINK) अणु
		err = fill_vport_vhca_id(mdev, rep->vport, info);
		अगर (err)
			वापस err;
	पूर्ण

	info->esw_owner_vhca_id = MLX5_CAP_GEN(mdev, vhca_id);
	info->flags |= MLX5_IB_UAPI_QUERY_PORT_ESW_OWNER_VHCA_ID;

	err = fill_vport_icm_addr(mdev, rep->vport, info);
	अगर (err)
		वापस err;

	अगर (mlx5_eचयन_vport_match_metadata_enabled(mdev->priv.eचयन)) अणु
		info->reg_c0.value = mlx5_eचयन_get_vport_metadata_क्रम_match(
			mdev->priv.eचयन, rep->vport);
		info->reg_c0.mask = mlx5_eचयन_get_vport_metadata_mask();
		info->flags |= MLX5_IB_UAPI_QUERY_PORT_VPORT_REG_C0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_QUERY_PORT)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा mlx5_ib_uapi_query_port info = अणुपूर्ण;
	काष्ठा mlx5_ib_ucontext *c;
	काष्ठा mlx5_ib_dev *dev;
	u32 port_num;
	पूर्णांक ret;

	अगर (uverbs_copy_from(&port_num, attrs,
			     MLX5_IB_ATTR_QUERY_PORT_PORT_NUM))
		वापस -EFAULT;

	c = to_mucontext(ib_uverbs_get_ucontext(attrs));
	अगर (IS_ERR(c))
		वापस PTR_ERR(c);
	dev = to_mdev(c->ibucontext.device);

	अगर (!rdma_is_port_valid(&dev->ib_dev, port_num))
		वापस -EINVAL;

	अगर (mlx5_eचयन_mode(dev->mdev) == MLX5_ESWITCH_OFFLOADS) अणु
		ret = fill_चयनdev_info(dev, port_num, &info);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस uverbs_copy_to_काष्ठा_or_zero(attrs, MLX5_IB_ATTR_QUERY_PORT, &info,
					     माप(info));
पूर्ण

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_QUERY_PORT,
	UVERBS_ATTR_PTR_IN(MLX5_IB_ATTR_QUERY_PORT_PORT_NUM,
			   UVERBS_ATTR_TYPE(u32), UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(
		MLX5_IB_ATTR_QUERY_PORT,
		UVERBS_ATTR_STRUCT(काष्ठा mlx5_ib_uapi_query_port,
				   reg_c0),
		UA_MANDATORY));

ADD_UVERBS_METHODS(mlx5_ib_device,
		   UVERBS_OBJECT_DEVICE,
		   &UVERBS_METHOD(MLX5_IB_METHOD_QUERY_PORT));

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_PD_QUERY,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_QUERY_PD_HANDLE,
			UVERBS_OBJECT_PD,
			UVERBS_ACCESS_READ,
			UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(MLX5_IB_ATTR_QUERY_PD_RESP_PDN,
			   UVERBS_ATTR_TYPE(u32),
			   UA_MANDATORY));

ADD_UVERBS_METHODS(mlx5_ib_pd,
		   UVERBS_OBJECT_PD,
		   &UVERBS_METHOD(MLX5_IB_METHOD_PD_QUERY));

स्थिर काष्ठा uapi_definition mlx5_ib_std_types_defs[] = अणु
	UAPI_DEF_CHAIN_OBJ_TREE(
		UVERBS_OBJECT_PD,
		&mlx5_ib_pd),
	UAPI_DEF_CHAIN_OBJ_TREE(
		UVERBS_OBJECT_DEVICE,
		&mlx5_ib_device),
	अणुपूर्ण,
पूर्ण;
