<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2018, Mellanox Technologies inc.  All rights reserved.
 */

#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/uverbs_types.h>
#समावेश <rdma/uverbs_ioctl.h>
#समावेश <rdma/mlx5_user_ioctl_cmds.h>
#समावेश <rdma/mlx5_user_ioctl_verbs.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/uverbs_std_types.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/fs.h>
#समावेश "mlx5_ib.h"
#समावेश "devx.h"
#समावेश "qp.h"
#समावेश <linux/xarray.h>

#घोषणा UVERBS_MODULE_NAME mlx5_ib
#समावेश <rdma/uverbs_named_ioctl.h>

अटल व्योम dispatch_event_fd(काष्ठा list_head *fd_list, स्थिर व्योम *data);

क्रमागत devx_obj_flags अणु
	DEVX_OBJ_FLAGS_INसूचीECT_MKEY = 1 << 0,
	DEVX_OBJ_FLAGS_DCT = 1 << 1,
	DEVX_OBJ_FLAGS_CQ = 1 << 2,
पूर्ण;

काष्ठा devx_async_data अणु
	काष्ठा mlx5_ib_dev *mdev;
	काष्ठा list_head list;
	काष्ठा devx_async_cmd_event_file *ev_file;
	काष्ठा mlx5_async_work cb_work;
	u16 cmd_out_len;
	/* must be last field in this काष्ठाure */
	काष्ठा mlx5_ib_uapi_devx_async_cmd_hdr hdr;
पूर्ण;

काष्ठा devx_async_event_data अणु
	काष्ठा list_head list; /* headed in ev_file->event_list */
	काष्ठा mlx5_ib_uapi_devx_async_event_hdr hdr;
पूर्ण;

/* first level XA value data काष्ठाure */
काष्ठा devx_event अणु
	काष्ठा xarray object_ids; /* second XA level, Key = object id */
	काष्ठा list_head unaffiliated_list;
पूर्ण;

/* second level XA value data काष्ठाure */
काष्ठा devx_obj_event अणु
	काष्ठा rcu_head rcu;
	काष्ठा list_head obj_sub_list;
पूर्ण;

काष्ठा devx_event_subscription अणु
	काष्ठा list_head file_list; /* headed in ev_file->
				     * subscribed_events_list
				     */
	काष्ठा list_head xa_list; /* headed in devx_event->unaffiliated_list or
				   * devx_obj_event->obj_sub_list
				   */
	काष्ठा list_head obj_list; /* headed in devx_object */
	काष्ठा list_head event_list; /* headed in ev_file->event_list or in
				      * temp list via subscription
				      */

	u8 is_cleaned:1;
	u32 xa_key_level1;
	u32 xa_key_level2;
	काष्ठा rcu_head	rcu;
	u64 cookie;
	काष्ठा devx_async_event_file *ev_file;
	काष्ठा eventfd_ctx *eventfd;
पूर्ण;

काष्ठा devx_async_event_file अणु
	काष्ठा ib_uobject uobj;
	/* Head of events that are subscribed to this FD */
	काष्ठा list_head subscribed_events_list;
	spinlock_t lock;
	रुको_queue_head_t poll_रुको;
	काष्ठा list_head event_list;
	काष्ठा mlx5_ib_dev *dev;
	u8 omit_data:1;
	u8 is_overflow_err:1;
	u8 is_destroyed:1;
पूर्ण;

काष्ठा devx_umem अणु
	काष्ठा mlx5_core_dev		*mdev;
	काष्ठा ib_umem			*umem;
	u32				dinlen;
	u32				dinbox[MLX5_ST_SZ_DW(destroy_umem_in)];
पूर्ण;

काष्ठा devx_umem_reg_cmd अणु
	व्योम				*in;
	u32				inlen;
	u32				out[MLX5_ST_SZ_DW(create_umem_out)];
पूर्ण;

अटल काष्ठा mlx5_ib_ucontext *
devx_ufile2uctx(स्थिर काष्ठा uverbs_attr_bundle *attrs)
अणु
	वापस to_mucontext(ib_uverbs_get_ucontext(attrs));
पूर्ण

पूर्णांक mlx5_ib_devx_create(काष्ठा mlx5_ib_dev *dev, bool is_user)
अणु
	u32 in[MLX5_ST_SZ_DW(create_uctx_in)] = अणुपूर्ण;
	u32 out[MLX5_ST_SZ_DW(create_uctx_out)] = अणुपूर्ण;
	व्योम *uctx;
	पूर्णांक err;
	u16 uid;
	u32 cap = 0;

	/* 0 means not supported */
	अगर (!MLX5_CAP_GEN(dev->mdev, log_max_uctx))
		वापस -EINVAL;

	uctx = MLX5_ADDR_OF(create_uctx_in, in, uctx);
	अगर (is_user && capable(CAP_NET_RAW) &&
	    (MLX5_CAP_GEN(dev->mdev, uctx_cap) & MLX5_UCTX_CAP_RAW_TX))
		cap |= MLX5_UCTX_CAP_RAW_TX;
	अगर (is_user && capable(CAP_SYS_RAWIO) &&
	    (MLX5_CAP_GEN(dev->mdev, uctx_cap) &
	     MLX5_UCTX_CAP_INTERNAL_DEV_RES))
		cap |= MLX5_UCTX_CAP_INTERNAL_DEV_RES;

	MLX5_SET(create_uctx_in, in, opcode, MLX5_CMD_OP_CREATE_UCTX);
	MLX5_SET(uctx, uctx, cap, cap);

	err = mlx5_cmd_exec(dev->mdev, in, माप(in), out, माप(out));
	अगर (err)
		वापस err;

	uid = MLX5_GET(create_uctx_out, out, uid);
	वापस uid;
पूर्ण

व्योम mlx5_ib_devx_destroy(काष्ठा mlx5_ib_dev *dev, u16 uid)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_uctx_in)] = अणुपूर्ण;
	u32 out[MLX5_ST_SZ_DW(destroy_uctx_out)] = अणुपूर्ण;

	MLX5_SET(destroy_uctx_in, in, opcode, MLX5_CMD_OP_DESTROY_UCTX);
	MLX5_SET(destroy_uctx_in, in, uid, uid);

	mlx5_cmd_exec(dev->mdev, in, माप(in), out, माप(out));
पूर्ण

अटल bool is_legacy_unaffiliated_event_num(u16 event_num)
अणु
	चयन (event_num) अणु
	हाल MLX5_EVENT_TYPE_PORT_CHANGE:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool is_legacy_obj_event_num(u16 event_num)
अणु
	चयन (event_num) अणु
	हाल MLX5_EVENT_TYPE_PATH_MIG:
	हाल MLX5_EVENT_TYPE_COMM_EST:
	हाल MLX5_EVENT_TYPE_SQ_DRAINED:
	हाल MLX5_EVENT_TYPE_SRQ_LAST_WQE:
	हाल MLX5_EVENT_TYPE_SRQ_RQ_LIMIT:
	हाल MLX5_EVENT_TYPE_CQ_ERROR:
	हाल MLX5_EVENT_TYPE_WQ_CATAS_ERROR:
	हाल MLX5_EVENT_TYPE_PATH_MIG_FAILED:
	हाल MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR:
	हाल MLX5_EVENT_TYPE_WQ_ACCESS_ERROR:
	हाल MLX5_EVENT_TYPE_SRQ_CATAS_ERROR:
	हाल MLX5_EVENT_TYPE_DCT_DRAINED:
	हाल MLX5_EVENT_TYPE_COMP:
	हाल MLX5_EVENT_TYPE_DCT_KEY_VIOLATION:
	हाल MLX5_EVENT_TYPE_XRQ_ERROR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल u16 get_legacy_obj_type(u16 opcode)
अणु
	चयन (opcode) अणु
	हाल MLX5_CMD_OP_CREATE_RQ:
		वापस MLX5_EVENT_QUEUE_TYPE_RQ;
	हाल MLX5_CMD_OP_CREATE_QP:
		वापस MLX5_EVENT_QUEUE_TYPE_QP;
	हाल MLX5_CMD_OP_CREATE_SQ:
		वापस MLX5_EVENT_QUEUE_TYPE_SQ;
	हाल MLX5_CMD_OP_CREATE_DCT:
		वापस MLX5_EVENT_QUEUE_TYPE_DCT;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल u16 get_dec_obj_type(काष्ठा devx_obj *obj, u16 event_num)
अणु
	u16 opcode;

	opcode = (obj->obj_id >> 32) & 0xffff;

	अगर (is_legacy_obj_event_num(event_num))
		वापस get_legacy_obj_type(opcode);

	चयन (opcode) अणु
	हाल MLX5_CMD_OP_CREATE_GENERAL_OBJECT:
		वापस (obj->obj_id >> 48);
	हाल MLX5_CMD_OP_CREATE_RQ:
		वापस MLX5_OBJ_TYPE_RQ;
	हाल MLX5_CMD_OP_CREATE_QP:
		वापस MLX5_OBJ_TYPE_QP;
	हाल MLX5_CMD_OP_CREATE_SQ:
		वापस MLX5_OBJ_TYPE_SQ;
	हाल MLX5_CMD_OP_CREATE_DCT:
		वापस MLX5_OBJ_TYPE_DCT;
	हाल MLX5_CMD_OP_CREATE_TIR:
		वापस MLX5_OBJ_TYPE_TIR;
	हाल MLX5_CMD_OP_CREATE_TIS:
		वापस MLX5_OBJ_TYPE_TIS;
	हाल MLX5_CMD_OP_CREATE_PSV:
		वापस MLX5_OBJ_TYPE_PSV;
	हाल MLX5_OBJ_TYPE_MKEY:
		वापस MLX5_OBJ_TYPE_MKEY;
	हाल MLX5_CMD_OP_CREATE_RMP:
		वापस MLX5_OBJ_TYPE_RMP;
	हाल MLX5_CMD_OP_CREATE_XRC_SRQ:
		वापस MLX5_OBJ_TYPE_XRC_SRQ;
	हाल MLX5_CMD_OP_CREATE_XRQ:
		वापस MLX5_OBJ_TYPE_XRQ;
	हाल MLX5_CMD_OP_CREATE_RQT:
		वापस MLX5_OBJ_TYPE_RQT;
	हाल MLX5_CMD_OP_ALLOC_FLOW_COUNTER:
		वापस MLX5_OBJ_TYPE_FLOW_COUNTER;
	हाल MLX5_CMD_OP_CREATE_CQ:
		वापस MLX5_OBJ_TYPE_CQ;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल u16 get_event_obj_type(अचिन्हित दीर्घ event_type, काष्ठा mlx5_eqe *eqe)
अणु
	चयन (event_type) अणु
	हाल MLX5_EVENT_TYPE_WQ_CATAS_ERROR:
	हाल MLX5_EVENT_TYPE_WQ_ACCESS_ERROR:
	हाल MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR:
	हाल MLX5_EVENT_TYPE_SRQ_LAST_WQE:
	हाल MLX5_EVENT_TYPE_PATH_MIG:
	हाल MLX5_EVENT_TYPE_PATH_MIG_FAILED:
	हाल MLX5_EVENT_TYPE_COMM_EST:
	हाल MLX5_EVENT_TYPE_SQ_DRAINED:
	हाल MLX5_EVENT_TYPE_SRQ_RQ_LIMIT:
	हाल MLX5_EVENT_TYPE_SRQ_CATAS_ERROR:
		वापस eqe->data.qp_srq.type;
	हाल MLX5_EVENT_TYPE_CQ_ERROR:
	हाल MLX5_EVENT_TYPE_XRQ_ERROR:
		वापस 0;
	हाल MLX5_EVENT_TYPE_DCT_DRAINED:
	हाल MLX5_EVENT_TYPE_DCT_KEY_VIOLATION:
		वापस MLX5_EVENT_QUEUE_TYPE_DCT;
	शेष:
		वापस MLX5_GET(affiliated_event_header, &eqe->data, obj_type);
	पूर्ण
पूर्ण

अटल u32 get_dec_obj_id(u64 obj_id)
अणु
	वापस (obj_id & 0xffffffff);
पूर्ण

/*
 * As the obj_id in the firmware is not globally unique the object type
 * must be considered upon checking क्रम a valid object id.
 * For that the opcode of the creator command is encoded as part of the obj_id.
 */
अटल u64 get_enc_obj_id(u32 opcode, u32 obj_id)
अणु
	वापस ((u64)opcode << 32) | obj_id;
पूर्ण

अटल u32 devx_get_created_obj_id(स्थिर व्योम *in, स्थिर व्योम *out, u16 opcode)
अणु
	चयन (opcode) अणु
	हाल MLX5_CMD_OP_CREATE_GENERAL_OBJECT:
		वापस MLX5_GET(general_obj_out_cmd_hdr, out, obj_id);
	हाल MLX5_CMD_OP_CREATE_UMEM:
		वापस MLX5_GET(create_umem_out, out, umem_id);
	हाल MLX5_CMD_OP_CREATE_MKEY:
		वापस MLX5_GET(create_mkey_out, out, mkey_index);
	हाल MLX5_CMD_OP_CREATE_CQ:
		वापस MLX5_GET(create_cq_out, out, cqn);
	हाल MLX5_CMD_OP_ALLOC_PD:
		वापस MLX5_GET(alloc_pd_out, out, pd);
	हाल MLX5_CMD_OP_ALLOC_TRANSPORT_DOMAIN:
		वापस MLX5_GET(alloc_transport_करोमुख्य_out, out,
				transport_करोमुख्य);
	हाल MLX5_CMD_OP_CREATE_RMP:
		वापस MLX5_GET(create_rmp_out, out, rmpn);
	हाल MLX5_CMD_OP_CREATE_SQ:
		वापस MLX5_GET(create_sq_out, out, sqn);
	हाल MLX5_CMD_OP_CREATE_RQ:
		वापस MLX5_GET(create_rq_out, out, rqn);
	हाल MLX5_CMD_OP_CREATE_RQT:
		वापस MLX5_GET(create_rqt_out, out, rqtn);
	हाल MLX5_CMD_OP_CREATE_TIR:
		वापस MLX5_GET(create_tir_out, out, tirn);
	हाल MLX5_CMD_OP_CREATE_TIS:
		वापस MLX5_GET(create_tis_out, out, tisn);
	हाल MLX5_CMD_OP_ALLOC_Q_COUNTER:
		वापस MLX5_GET(alloc_q_counter_out, out, counter_set_id);
	हाल MLX5_CMD_OP_CREATE_FLOW_TABLE:
		वापस MLX5_GET(create_flow_table_out, out, table_id);
	हाल MLX5_CMD_OP_CREATE_FLOW_GROUP:
		वापस MLX5_GET(create_flow_group_out, out, group_id);
	हाल MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY:
		वापस MLX5_GET(set_fte_in, in, flow_index);
	हाल MLX5_CMD_OP_ALLOC_FLOW_COUNTER:
		वापस MLX5_GET(alloc_flow_counter_out, out, flow_counter_id);
	हाल MLX5_CMD_OP_ALLOC_PACKET_REFORMAT_CONTEXT:
		वापस MLX5_GET(alloc_packet_reक्रमmat_context_out, out,
				packet_reक्रमmat_id);
	हाल MLX5_CMD_OP_ALLOC_MODIFY_HEADER_CONTEXT:
		वापस MLX5_GET(alloc_modअगरy_header_context_out, out,
				modअगरy_header_id);
	हाल MLX5_CMD_OP_CREATE_SCHEDULING_ELEMENT:
		वापस MLX5_GET(create_scheduling_element_out, out,
				scheduling_element_id);
	हाल MLX5_CMD_OP_ADD_VXLAN_UDP_DPORT:
		वापस MLX5_GET(add_vxlan_udp_dport_in, in, vxlan_udp_port);
	हाल MLX5_CMD_OP_SET_L2_TABLE_ENTRY:
		वापस MLX5_GET(set_l2_table_entry_in, in, table_index);
	हाल MLX5_CMD_OP_CREATE_QP:
		वापस MLX5_GET(create_qp_out, out, qpn);
	हाल MLX5_CMD_OP_CREATE_SRQ:
		वापस MLX5_GET(create_srq_out, out, srqn);
	हाल MLX5_CMD_OP_CREATE_XRC_SRQ:
		वापस MLX5_GET(create_xrc_srq_out, out, xrc_srqn);
	हाल MLX5_CMD_OP_CREATE_DCT:
		वापस MLX5_GET(create_dct_out, out, dctn);
	हाल MLX5_CMD_OP_CREATE_XRQ:
		वापस MLX5_GET(create_xrq_out, out, xrqn);
	हाल MLX5_CMD_OP_ATTACH_TO_MCG:
		वापस MLX5_GET(attach_to_mcg_in, in, qpn);
	हाल MLX5_CMD_OP_ALLOC_XRCD:
		वापस MLX5_GET(alloc_xrcd_out, out, xrcd);
	हाल MLX5_CMD_OP_CREATE_PSV:
		वापस MLX5_GET(create_psv_out, out, psv0_index);
	शेष:
		/* The entry must match to one of the devx_is_obj_create_cmd */
		WARN_ON(true);
		वापस 0;
	पूर्ण
पूर्ण

अटल u64 devx_get_obj_id(स्थिर व्योम *in)
अणु
	u16 opcode = MLX5_GET(general_obj_in_cmd_hdr, in, opcode);
	u64 obj_id;

	चयन (opcode) अणु
	हाल MLX5_CMD_OP_MODIFY_GENERAL_OBJECT:
	हाल MLX5_CMD_OP_QUERY_GENERAL_OBJECT:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_GENERAL_OBJECT |
					MLX5_GET(general_obj_in_cmd_hdr, in,
						 obj_type) << 16,
					MLX5_GET(general_obj_in_cmd_hdr, in,
						 obj_id));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_MKEY:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_MKEY,
					MLX5_GET(query_mkey_in, in,
						 mkey_index));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_CQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_CQ,
					MLX5_GET(query_cq_in, in, cqn));
		अवरोध;
	हाल MLX5_CMD_OP_MODIFY_CQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_CQ,
					MLX5_GET(modअगरy_cq_in, in, cqn));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_SQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_SQ,
					MLX5_GET(query_sq_in, in, sqn));
		अवरोध;
	हाल MLX5_CMD_OP_MODIFY_SQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_SQ,
					MLX5_GET(modअगरy_sq_in, in, sqn));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_RQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_RQ,
					MLX5_GET(query_rq_in, in, rqn));
		अवरोध;
	हाल MLX5_CMD_OP_MODIFY_RQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_RQ,
					MLX5_GET(modअगरy_rq_in, in, rqn));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_RMP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_RMP,
					MLX5_GET(query_rmp_in, in, rmpn));
		अवरोध;
	हाल MLX5_CMD_OP_MODIFY_RMP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_RMP,
					MLX5_GET(modअगरy_rmp_in, in, rmpn));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_RQT:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_RQT,
					MLX5_GET(query_rqt_in, in, rqtn));
		अवरोध;
	हाल MLX5_CMD_OP_MODIFY_RQT:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_RQT,
					MLX5_GET(modअगरy_rqt_in, in, rqtn));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_TIR:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_TIR,
					MLX5_GET(query_tir_in, in, tirn));
		अवरोध;
	हाल MLX5_CMD_OP_MODIFY_TIR:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_TIR,
					MLX5_GET(modअगरy_tir_in, in, tirn));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_TIS:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_TIS,
					MLX5_GET(query_tis_in, in, tisn));
		अवरोध;
	हाल MLX5_CMD_OP_MODIFY_TIS:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_TIS,
					MLX5_GET(modअगरy_tis_in, in, tisn));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_FLOW_TABLE:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_FLOW_TABLE,
					MLX5_GET(query_flow_table_in, in,
						 table_id));
		अवरोध;
	हाल MLX5_CMD_OP_MODIFY_FLOW_TABLE:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_FLOW_TABLE,
					MLX5_GET(modअगरy_flow_table_in, in,
						 table_id));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_FLOW_GROUP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_FLOW_GROUP,
					MLX5_GET(query_flow_group_in, in,
						 group_id));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_FLOW_TABLE_ENTRY:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY,
					MLX5_GET(query_fte_in, in,
						 flow_index));
		अवरोध;
	हाल MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY,
					MLX5_GET(set_fte_in, in, flow_index));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_Q_COUNTER:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_ALLOC_Q_COUNTER,
					MLX5_GET(query_q_counter_in, in,
						 counter_set_id));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_FLOW_COUNTER:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_ALLOC_FLOW_COUNTER,
					MLX5_GET(query_flow_counter_in, in,
						 flow_counter_id));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_MODIFY_HEADER_CONTEXT:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_ALLOC_MODIFY_HEADER_CONTEXT,
					MLX5_GET(query_modअगरy_header_context_in,
						 in, modअगरy_header_id));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_SCHEDULING_ELEMENT:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_SCHEDULING_ELEMENT,
					MLX5_GET(query_scheduling_element_in,
						 in, scheduling_element_id));
		अवरोध;
	हाल MLX5_CMD_OP_MODIFY_SCHEDULING_ELEMENT:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_SCHEDULING_ELEMENT,
					MLX5_GET(modअगरy_scheduling_element_in,
						 in, scheduling_element_id));
		अवरोध;
	हाल MLX5_CMD_OP_ADD_VXLAN_UDP_DPORT:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_ADD_VXLAN_UDP_DPORT,
					MLX5_GET(add_vxlan_udp_dport_in, in,
						 vxlan_udp_port));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_L2_TABLE_ENTRY:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_SET_L2_TABLE_ENTRY,
					MLX5_GET(query_l2_table_entry_in, in,
						 table_index));
		अवरोध;
	हाल MLX5_CMD_OP_SET_L2_TABLE_ENTRY:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_SET_L2_TABLE_ENTRY,
					MLX5_GET(set_l2_table_entry_in, in,
						 table_index));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_QP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_QP,
					MLX5_GET(query_qp_in, in, qpn));
		अवरोध;
	हाल MLX5_CMD_OP_RST2INIT_QP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_QP,
					MLX5_GET(rst2init_qp_in, in, qpn));
		अवरोध;
	हाल MLX5_CMD_OP_INIT2INIT_QP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_QP,
					MLX5_GET(init2init_qp_in, in, qpn));
		अवरोध;
	हाल MLX5_CMD_OP_INIT2RTR_QP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_QP,
					MLX5_GET(init2rtr_qp_in, in, qpn));
		अवरोध;
	हाल MLX5_CMD_OP_RTR2RTS_QP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_QP,
					MLX5_GET(rtr2rts_qp_in, in, qpn));
		अवरोध;
	हाल MLX5_CMD_OP_RTS2RTS_QP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_QP,
					MLX5_GET(rts2rts_qp_in, in, qpn));
		अवरोध;
	हाल MLX5_CMD_OP_SQERR2RTS_QP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_QP,
					MLX5_GET(sqerr2rts_qp_in, in, qpn));
		अवरोध;
	हाल MLX5_CMD_OP_2ERR_QP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_QP,
					MLX5_GET(qp_2err_in, in, qpn));
		अवरोध;
	हाल MLX5_CMD_OP_2RST_QP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_QP,
					MLX5_GET(qp_2rst_in, in, qpn));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_DCT:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_DCT,
					MLX5_GET(query_dct_in, in, dctn));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_XRQ:
	हाल MLX5_CMD_OP_QUERY_XRQ_DC_PARAMS_ENTRY:
	हाल MLX5_CMD_OP_QUERY_XRQ_ERROR_PARAMS:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_XRQ,
					MLX5_GET(query_xrq_in, in, xrqn));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_XRC_SRQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_XRC_SRQ,
					MLX5_GET(query_xrc_srq_in, in,
						 xrc_srqn));
		अवरोध;
	हाल MLX5_CMD_OP_ARM_XRC_SRQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_XRC_SRQ,
					MLX5_GET(arm_xrc_srq_in, in, xrc_srqn));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_SRQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_SRQ,
					MLX5_GET(query_srq_in, in, srqn));
		अवरोध;
	हाल MLX5_CMD_OP_ARM_RQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_RQ,
					MLX5_GET(arm_rq_in, in, srq_number));
		अवरोध;
	हाल MLX5_CMD_OP_ARM_DCT_FOR_KEY_VIOLATION:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_DCT,
					MLX5_GET(drain_dct_in, in, dctn));
		अवरोध;
	हाल MLX5_CMD_OP_ARM_XRQ:
	हाल MLX5_CMD_OP_SET_XRQ_DC_PARAMS_ENTRY:
	हाल MLX5_CMD_OP_RELEASE_XRQ_ERROR:
	हाल MLX5_CMD_OP_MODIFY_XRQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_XRQ,
					MLX5_GET(arm_xrq_in, in, xrqn));
		अवरोध;
	हाल MLX5_CMD_OP_QUERY_PACKET_REFORMAT_CONTEXT:
		obj_id = get_enc_obj_id
				(MLX5_CMD_OP_ALLOC_PACKET_REFORMAT_CONTEXT,
				 MLX5_GET(query_packet_reक्रमmat_context_in,
					  in, packet_reक्रमmat_id));
		अवरोध;
	शेष:
		obj_id = 0;
	पूर्ण

	वापस obj_id;
पूर्ण

अटल bool devx_is_valid_obj_id(काष्ठा uverbs_attr_bundle *attrs,
				 काष्ठा ib_uobject *uobj, स्थिर व्योम *in)
अणु
	काष्ठा mlx5_ib_dev *dev = mlx5_udata_to_mdev(&attrs->driver_udata);
	u64 obj_id = devx_get_obj_id(in);

	अगर (!obj_id)
		वापस false;

	चयन (uobj_get_object_id(uobj)) अणु
	हाल UVERBS_OBJECT_CQ:
		वापस get_enc_obj_id(MLX5_CMD_OP_CREATE_CQ,
				      to_mcq(uobj->object)->mcq.cqn) ==
				      obj_id;

	हाल UVERBS_OBJECT_SRQ:
	अणु
		काष्ठा mlx5_core_srq *srq = &(to_msrq(uobj->object)->msrq);
		u16 opcode;

		चयन (srq->common.res) अणु
		हाल MLX5_RES_XSRQ:
			opcode = MLX5_CMD_OP_CREATE_XRC_SRQ;
			अवरोध;
		हाल MLX5_RES_XRQ:
			opcode = MLX5_CMD_OP_CREATE_XRQ;
			अवरोध;
		शेष:
			अगर (!dev->mdev->issi)
				opcode = MLX5_CMD_OP_CREATE_SRQ;
			अन्यथा
				opcode = MLX5_CMD_OP_CREATE_RMP;
		पूर्ण

		वापस get_enc_obj_id(opcode,
				      to_msrq(uobj->object)->msrq.srqn) ==
				      obj_id;
	पूर्ण

	हाल UVERBS_OBJECT_QP:
	अणु
		काष्ठा mlx5_ib_qp *qp = to_mqp(uobj->object);

		अगर (qp->type == IB_QPT_RAW_PACKET ||
		    (qp->flags & IB_QP_CREATE_SOURCE_QPN)) अणु
			काष्ठा mlx5_ib_raw_packet_qp *raw_packet_qp =
							 &qp->raw_packet_qp;
			काष्ठा mlx5_ib_rq *rq = &raw_packet_qp->rq;
			काष्ठा mlx5_ib_sq *sq = &raw_packet_qp->sq;

			वापस (get_enc_obj_id(MLX5_CMD_OP_CREATE_RQ,
					       rq->base.mqp.qpn) == obj_id ||
				get_enc_obj_id(MLX5_CMD_OP_CREATE_SQ,
					       sq->base.mqp.qpn) == obj_id ||
				get_enc_obj_id(MLX5_CMD_OP_CREATE_TIR,
					       rq->tirn) == obj_id ||
				get_enc_obj_id(MLX5_CMD_OP_CREATE_TIS,
					       sq->tisn) == obj_id);
		पूर्ण

		अगर (qp->type == MLX5_IB_QPT_DCT)
			वापस get_enc_obj_id(MLX5_CMD_OP_CREATE_DCT,
					      qp->dct.mdct.mqp.qpn) == obj_id;
		वापस get_enc_obj_id(MLX5_CMD_OP_CREATE_QP,
				      qp->ibqp.qp_num) == obj_id;
	पूर्ण

	हाल UVERBS_OBJECT_WQ:
		वापस get_enc_obj_id(MLX5_CMD_OP_CREATE_RQ,
				      to_mrwq(uobj->object)->core_qp.qpn) ==
				      obj_id;

	हाल UVERBS_OBJECT_RWQ_IND_TBL:
		वापस get_enc_obj_id(MLX5_CMD_OP_CREATE_RQT,
				      to_mrwq_ind_table(uobj->object)->rqtn) ==
				      obj_id;

	हाल MLX5_IB_OBJECT_DEVX_OBJ:
		वापस ((काष्ठा devx_obj *)uobj->object)->obj_id == obj_id;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम devx_set_umem_valid(स्थिर व्योम *in)
अणु
	u16 opcode = MLX5_GET(general_obj_in_cmd_hdr, in, opcode);

	चयन (opcode) अणु
	हाल MLX5_CMD_OP_CREATE_MKEY:
		MLX5_SET(create_mkey_in, in, mkey_umem_valid, 1);
		अवरोध;
	हाल MLX5_CMD_OP_CREATE_CQ:
	अणु
		व्योम *cqc;

		MLX5_SET(create_cq_in, in, cq_umem_valid, 1);
		cqc = MLX5_ADDR_OF(create_cq_in, in, cq_context);
		MLX5_SET(cqc, cqc, dbr_umem_valid, 1);
		अवरोध;
	पूर्ण
	हाल MLX5_CMD_OP_CREATE_QP:
	अणु
		व्योम *qpc;

		qpc = MLX5_ADDR_OF(create_qp_in, in, qpc);
		MLX5_SET(qpc, qpc, dbr_umem_valid, 1);
		MLX5_SET(create_qp_in, in, wq_umem_valid, 1);
		अवरोध;
	पूर्ण

	हाल MLX5_CMD_OP_CREATE_RQ:
	अणु
		व्योम *rqc, *wq;

		rqc = MLX5_ADDR_OF(create_rq_in, in, ctx);
		wq  = MLX5_ADDR_OF(rqc, rqc, wq);
		MLX5_SET(wq, wq, dbr_umem_valid, 1);
		MLX5_SET(wq, wq, wq_umem_valid, 1);
		अवरोध;
	पूर्ण

	हाल MLX5_CMD_OP_CREATE_SQ:
	अणु
		व्योम *sqc, *wq;

		sqc = MLX5_ADDR_OF(create_sq_in, in, ctx);
		wq = MLX5_ADDR_OF(sqc, sqc, wq);
		MLX5_SET(wq, wq, dbr_umem_valid, 1);
		MLX5_SET(wq, wq, wq_umem_valid, 1);
		अवरोध;
	पूर्ण

	हाल MLX5_CMD_OP_MODIFY_CQ:
		MLX5_SET(modअगरy_cq_in, in, cq_umem_valid, 1);
		अवरोध;

	हाल MLX5_CMD_OP_CREATE_RMP:
	अणु
		व्योम *rmpc, *wq;

		rmpc = MLX5_ADDR_OF(create_rmp_in, in, ctx);
		wq = MLX5_ADDR_OF(rmpc, rmpc, wq);
		MLX5_SET(wq, wq, dbr_umem_valid, 1);
		MLX5_SET(wq, wq, wq_umem_valid, 1);
		अवरोध;
	पूर्ण

	हाल MLX5_CMD_OP_CREATE_XRQ:
	अणु
		व्योम *xrqc, *wq;

		xrqc = MLX5_ADDR_OF(create_xrq_in, in, xrq_context);
		wq = MLX5_ADDR_OF(xrqc, xrqc, wq);
		MLX5_SET(wq, wq, dbr_umem_valid, 1);
		MLX5_SET(wq, wq, wq_umem_valid, 1);
		अवरोध;
	पूर्ण

	हाल MLX5_CMD_OP_CREATE_XRC_SRQ:
	अणु
		व्योम *xrc_srqc;

		MLX5_SET(create_xrc_srq_in, in, xrc_srq_umem_valid, 1);
		xrc_srqc = MLX5_ADDR_OF(create_xrc_srq_in, in,
					xrc_srq_context_entry);
		MLX5_SET(xrc_srqc, xrc_srqc, dbr_umem_valid, 1);
		अवरोध;
	पूर्ण

	शेष:
		वापस;
	पूर्ण
पूर्ण

अटल bool devx_is_obj_create_cmd(स्थिर व्योम *in, u16 *opcode)
अणु
	*opcode = MLX5_GET(general_obj_in_cmd_hdr, in, opcode);

	चयन (*opcode) अणु
	हाल MLX5_CMD_OP_CREATE_GENERAL_OBJECT:
	हाल MLX5_CMD_OP_CREATE_MKEY:
	हाल MLX5_CMD_OP_CREATE_CQ:
	हाल MLX5_CMD_OP_ALLOC_PD:
	हाल MLX5_CMD_OP_ALLOC_TRANSPORT_DOMAIN:
	हाल MLX5_CMD_OP_CREATE_RMP:
	हाल MLX5_CMD_OP_CREATE_SQ:
	हाल MLX5_CMD_OP_CREATE_RQ:
	हाल MLX5_CMD_OP_CREATE_RQT:
	हाल MLX5_CMD_OP_CREATE_TIR:
	हाल MLX5_CMD_OP_CREATE_TIS:
	हाल MLX5_CMD_OP_ALLOC_Q_COUNTER:
	हाल MLX5_CMD_OP_CREATE_FLOW_TABLE:
	हाल MLX5_CMD_OP_CREATE_FLOW_GROUP:
	हाल MLX5_CMD_OP_ALLOC_FLOW_COUNTER:
	हाल MLX5_CMD_OP_ALLOC_PACKET_REFORMAT_CONTEXT:
	हाल MLX5_CMD_OP_ALLOC_MODIFY_HEADER_CONTEXT:
	हाल MLX5_CMD_OP_CREATE_SCHEDULING_ELEMENT:
	हाल MLX5_CMD_OP_ADD_VXLAN_UDP_DPORT:
	हाल MLX5_CMD_OP_SET_L2_TABLE_ENTRY:
	हाल MLX5_CMD_OP_CREATE_QP:
	हाल MLX5_CMD_OP_CREATE_SRQ:
	हाल MLX5_CMD_OP_CREATE_XRC_SRQ:
	हाल MLX5_CMD_OP_CREATE_DCT:
	हाल MLX5_CMD_OP_CREATE_XRQ:
	हाल MLX5_CMD_OP_ATTACH_TO_MCG:
	हाल MLX5_CMD_OP_ALLOC_XRCD:
		वापस true;
	हाल MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY:
	अणु
		u16 op_mod = MLX5_GET(set_fte_in, in, op_mod);
		अगर (op_mod == 0)
			वापस true;
		वापस false;
	पूर्ण
	हाल MLX5_CMD_OP_CREATE_PSV:
	अणु
		u8 num_psv = MLX5_GET(create_psv_in, in, num_psv);

		अगर (num_psv == 1)
			वापस true;
		वापस false;
	पूर्ण
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool devx_is_obj_modअगरy_cmd(स्थिर व्योम *in)
अणु
	u16 opcode = MLX5_GET(general_obj_in_cmd_hdr, in, opcode);

	चयन (opcode) अणु
	हाल MLX5_CMD_OP_MODIFY_GENERAL_OBJECT:
	हाल MLX5_CMD_OP_MODIFY_CQ:
	हाल MLX5_CMD_OP_MODIFY_RMP:
	हाल MLX5_CMD_OP_MODIFY_SQ:
	हाल MLX5_CMD_OP_MODIFY_RQ:
	हाल MLX5_CMD_OP_MODIFY_RQT:
	हाल MLX5_CMD_OP_MODIFY_TIR:
	हाल MLX5_CMD_OP_MODIFY_TIS:
	हाल MLX5_CMD_OP_MODIFY_FLOW_TABLE:
	हाल MLX5_CMD_OP_MODIFY_SCHEDULING_ELEMENT:
	हाल MLX5_CMD_OP_ADD_VXLAN_UDP_DPORT:
	हाल MLX5_CMD_OP_SET_L2_TABLE_ENTRY:
	हाल MLX5_CMD_OP_RST2INIT_QP:
	हाल MLX5_CMD_OP_INIT2RTR_QP:
	हाल MLX5_CMD_OP_INIT2INIT_QP:
	हाल MLX5_CMD_OP_RTR2RTS_QP:
	हाल MLX5_CMD_OP_RTS2RTS_QP:
	हाल MLX5_CMD_OP_SQERR2RTS_QP:
	हाल MLX5_CMD_OP_2ERR_QP:
	हाल MLX5_CMD_OP_2RST_QP:
	हाल MLX5_CMD_OP_ARM_XRC_SRQ:
	हाल MLX5_CMD_OP_ARM_RQ:
	हाल MLX5_CMD_OP_ARM_DCT_FOR_KEY_VIOLATION:
	हाल MLX5_CMD_OP_ARM_XRQ:
	हाल MLX5_CMD_OP_SET_XRQ_DC_PARAMS_ENTRY:
	हाल MLX5_CMD_OP_RELEASE_XRQ_ERROR:
	हाल MLX5_CMD_OP_MODIFY_XRQ:
		वापस true;
	हाल MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY:
	अणु
		u16 op_mod = MLX5_GET(set_fte_in, in, op_mod);

		अगर (op_mod == 1)
			वापस true;
		वापस false;
	पूर्ण
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool devx_is_obj_query_cmd(स्थिर व्योम *in)
अणु
	u16 opcode = MLX5_GET(general_obj_in_cmd_hdr, in, opcode);

	चयन (opcode) अणु
	हाल MLX5_CMD_OP_QUERY_GENERAL_OBJECT:
	हाल MLX5_CMD_OP_QUERY_MKEY:
	हाल MLX5_CMD_OP_QUERY_CQ:
	हाल MLX5_CMD_OP_QUERY_RMP:
	हाल MLX5_CMD_OP_QUERY_SQ:
	हाल MLX5_CMD_OP_QUERY_RQ:
	हाल MLX5_CMD_OP_QUERY_RQT:
	हाल MLX5_CMD_OP_QUERY_TIR:
	हाल MLX5_CMD_OP_QUERY_TIS:
	हाल MLX5_CMD_OP_QUERY_Q_COUNTER:
	हाल MLX5_CMD_OP_QUERY_FLOW_TABLE:
	हाल MLX5_CMD_OP_QUERY_FLOW_GROUP:
	हाल MLX5_CMD_OP_QUERY_FLOW_TABLE_ENTRY:
	हाल MLX5_CMD_OP_QUERY_FLOW_COUNTER:
	हाल MLX5_CMD_OP_QUERY_MODIFY_HEADER_CONTEXT:
	हाल MLX5_CMD_OP_QUERY_SCHEDULING_ELEMENT:
	हाल MLX5_CMD_OP_QUERY_L2_TABLE_ENTRY:
	हाल MLX5_CMD_OP_QUERY_QP:
	हाल MLX5_CMD_OP_QUERY_SRQ:
	हाल MLX5_CMD_OP_QUERY_XRC_SRQ:
	हाल MLX5_CMD_OP_QUERY_DCT:
	हाल MLX5_CMD_OP_QUERY_XRQ:
	हाल MLX5_CMD_OP_QUERY_XRQ_DC_PARAMS_ENTRY:
	हाल MLX5_CMD_OP_QUERY_XRQ_ERROR_PARAMS:
	हाल MLX5_CMD_OP_QUERY_PACKET_REFORMAT_CONTEXT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool devx_is_whitelist_cmd(व्योम *in)
अणु
	u16 opcode = MLX5_GET(general_obj_in_cmd_hdr, in, opcode);

	चयन (opcode) अणु
	हाल MLX5_CMD_OP_QUERY_HCA_CAP:
	हाल MLX5_CMD_OP_QUERY_HCA_VPORT_CONTEXT:
	हाल MLX5_CMD_OP_QUERY_ESW_VPORT_CONTEXT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक devx_get_uid(काष्ठा mlx5_ib_ucontext *c, व्योम *cmd_in)
अणु
	अगर (devx_is_whitelist_cmd(cmd_in)) अणु
		काष्ठा mlx5_ib_dev *dev;

		अगर (c->devx_uid)
			वापस c->devx_uid;

		dev = to_mdev(c->ibucontext.device);
		अगर (dev->devx_whitelist_uid)
			वापस dev->devx_whitelist_uid;

		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!c->devx_uid)
		वापस -EINVAL;

	वापस c->devx_uid;
पूर्ण

अटल bool devx_is_general_cmd(व्योम *in, काष्ठा mlx5_ib_dev *dev)
अणु
	u16 opcode = MLX5_GET(general_obj_in_cmd_hdr, in, opcode);

	/* Pass all cmds क्रम vhca_tunnel as general, tracking is करोne in FW */
	अगर ((MLX5_CAP_GEN_64(dev->mdev, vhca_tunnel_commands) &&
	     MLX5_GET(general_obj_in_cmd_hdr, in, vhca_tunnel_id)) ||
	    (opcode >= MLX5_CMD_OP_GENERAL_START &&
	     opcode < MLX5_CMD_OP_GENERAL_END))
		वापस true;

	चयन (opcode) अणु
	हाल MLX5_CMD_OP_QUERY_HCA_CAP:
	हाल MLX5_CMD_OP_QUERY_HCA_VPORT_CONTEXT:
	हाल MLX5_CMD_OP_QUERY_ESW_VPORT_CONTEXT:
	हाल MLX5_CMD_OP_QUERY_VPORT_STATE:
	हाल MLX5_CMD_OP_QUERY_ADAPTER:
	हाल MLX5_CMD_OP_QUERY_ISSI:
	हाल MLX5_CMD_OP_QUERY_NIC_VPORT_CONTEXT:
	हाल MLX5_CMD_OP_QUERY_ROCE_ADDRESS:
	हाल MLX5_CMD_OP_QUERY_VNIC_ENV:
	हाल MLX5_CMD_OP_QUERY_VPORT_COUNTER:
	हाल MLX5_CMD_OP_GET_DROPPED_PACKET_LOG:
	हाल MLX5_CMD_OP_NOP:
	हाल MLX5_CMD_OP_QUERY_CONG_STATUS:
	हाल MLX5_CMD_OP_QUERY_CONG_PARAMS:
	हाल MLX5_CMD_OP_QUERY_CONG_STATISTICS:
	हाल MLX5_CMD_OP_QUERY_LAG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_DEVX_QUERY_EQN)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा mlx5_ib_ucontext *c;
	काष्ठा mlx5_ib_dev *dev;
	पूर्णांक user_vector;
	पूर्णांक dev_eqn;
	अचिन्हित पूर्णांक irqn;
	पूर्णांक err;

	अगर (uverbs_copy_from(&user_vector, attrs,
			     MLX5_IB_ATTR_DEVX_QUERY_EQN_USER_VEC))
		वापस -EFAULT;

	c = devx_ufile2uctx(attrs);
	अगर (IS_ERR(c))
		वापस PTR_ERR(c);
	dev = to_mdev(c->ibucontext.device);

	err = mlx5_vector2eqn(dev->mdev, user_vector, &dev_eqn, &irqn);
	अगर (err < 0)
		वापस err;

	अगर (uverbs_copy_to(attrs, MLX5_IB_ATTR_DEVX_QUERY_EQN_DEV_EQN,
			   &dev_eqn, माप(dev_eqn)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 *Security note:
 * The hardware protection mechanism works like this: Each device object that
 * is subject to UAR करोorbells (QP/SQ/CQ) माला_लो a UAR ID (called uar_page in
 * the device specअगरication manual) upon its creation. Then upon करोorbell,
 * hardware fetches the object context क्रम which the करोorbell was rang, and
 * validates that the UAR through which the DB was rang matches the UAR ID
 * of the object.
 * If no match the करोorbell is silently ignored by the hardware. Of course,
 * the user cannot ring a करोorbell on a UAR that was not mapped to it.
 * Now in devx, as the devx kernel करोes not manipulate the QP/SQ/CQ command
 * mailboxes (except tagging them with UID), we expose to the user its UAR
 * ID, so it can embed it in these objects in the expected specअगरication
 * क्रमmat. So the only thing the user can करो is hurt itself by creating a
 * QP/SQ/CQ with a UAR ID other than his, and then in this हाल other users
 * may ring a करोorbell on its objects.
 * The consequence of that will be that another user can schedule a QP/SQ
 * of the buggy user क्रम execution (just insert it to the hardware schedule
 * queue or arm its CQ क्रम event generation), no further harm is expected.
 */
अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_DEVX_QUERY_UAR)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा mlx5_ib_ucontext *c;
	काष्ठा mlx5_ib_dev *dev;
	u32 user_idx;
	s32 dev_idx;

	c = devx_ufile2uctx(attrs);
	अगर (IS_ERR(c))
		वापस PTR_ERR(c);
	dev = to_mdev(c->ibucontext.device);

	अगर (uverbs_copy_from(&user_idx, attrs,
			     MLX5_IB_ATTR_DEVX_QUERY_UAR_USER_IDX))
		वापस -EFAULT;

	dev_idx = bfregn_to_uar_index(dev, &c->bfregi, user_idx, true);
	अगर (dev_idx < 0)
		वापस dev_idx;

	अगर (uverbs_copy_to(attrs, MLX5_IB_ATTR_DEVX_QUERY_UAR_DEV_IDX,
			   &dev_idx, माप(dev_idx)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_DEVX_OTHER)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा mlx5_ib_ucontext *c;
	काष्ठा mlx5_ib_dev *dev;
	व्योम *cmd_in = uverbs_attr_get_alloced_ptr(
		attrs, MLX5_IB_ATTR_DEVX_OTHER_CMD_IN);
	पूर्णांक cmd_out_len = uverbs_attr_get_len(attrs,
					MLX5_IB_ATTR_DEVX_OTHER_CMD_OUT);
	व्योम *cmd_out;
	पूर्णांक err;
	पूर्णांक uid;

	c = devx_ufile2uctx(attrs);
	अगर (IS_ERR(c))
		वापस PTR_ERR(c);
	dev = to_mdev(c->ibucontext.device);

	uid = devx_get_uid(c, cmd_in);
	अगर (uid < 0)
		वापस uid;

	/* Only white list of some general HCA commands are allowed क्रम this method. */
	अगर (!devx_is_general_cmd(cmd_in, dev))
		वापस -EINVAL;

	cmd_out = uverbs_zalloc(attrs, cmd_out_len);
	अगर (IS_ERR(cmd_out))
		वापस PTR_ERR(cmd_out);

	MLX5_SET(general_obj_in_cmd_hdr, cmd_in, uid, uid);
	err = mlx5_cmd_exec(dev->mdev, cmd_in,
			    uverbs_attr_get_len(attrs, MLX5_IB_ATTR_DEVX_OTHER_CMD_IN),
			    cmd_out, cmd_out_len);
	अगर (err)
		वापस err;

	वापस uverbs_copy_to(attrs, MLX5_IB_ATTR_DEVX_OTHER_CMD_OUT, cmd_out,
			      cmd_out_len);
पूर्ण

अटल व्योम devx_obj_build_destroy_cmd(व्योम *in, व्योम *out, व्योम *din,
				       u32 *dinlen,
				       u32 *obj_id)
अणु
	u16 opcode = MLX5_GET(general_obj_in_cmd_hdr, in, opcode);
	u16 uid = MLX5_GET(general_obj_in_cmd_hdr, in, uid);

	*obj_id = devx_get_created_obj_id(in, out, opcode);
	*dinlen = MLX5_ST_SZ_BYTES(general_obj_in_cmd_hdr);
	MLX5_SET(general_obj_in_cmd_hdr, din, uid, uid);

	चयन (opcode) अणु
	हाल MLX5_CMD_OP_CREATE_GENERAL_OBJECT:
		MLX5_SET(general_obj_in_cmd_hdr, din, opcode, MLX5_CMD_OP_DESTROY_GENERAL_OBJECT);
		MLX5_SET(general_obj_in_cmd_hdr, din, obj_id, *obj_id);
		MLX5_SET(general_obj_in_cmd_hdr, din, obj_type,
			 MLX5_GET(general_obj_in_cmd_hdr, in, obj_type));
		अवरोध;

	हाल MLX5_CMD_OP_CREATE_UMEM:
		MLX5_SET(destroy_umem_in, din, opcode,
			 MLX5_CMD_OP_DESTROY_UMEM);
		MLX5_SET(destroy_umem_in, din, umem_id, *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_CREATE_MKEY:
		MLX5_SET(destroy_mkey_in, din, opcode,
			 MLX5_CMD_OP_DESTROY_MKEY);
		MLX5_SET(destroy_mkey_in, din, mkey_index, *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_CREATE_CQ:
		MLX5_SET(destroy_cq_in, din, opcode, MLX5_CMD_OP_DESTROY_CQ);
		MLX5_SET(destroy_cq_in, din, cqn, *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_ALLOC_PD:
		MLX5_SET(dealloc_pd_in, din, opcode, MLX5_CMD_OP_DEALLOC_PD);
		MLX5_SET(dealloc_pd_in, din, pd, *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_ALLOC_TRANSPORT_DOMAIN:
		MLX5_SET(dealloc_transport_करोमुख्य_in, din, opcode,
			 MLX5_CMD_OP_DEALLOC_TRANSPORT_DOMAIN);
		MLX5_SET(dealloc_transport_करोमुख्य_in, din, transport_करोमुख्य,
			 *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_CREATE_RMP:
		MLX5_SET(destroy_rmp_in, din, opcode, MLX5_CMD_OP_DESTROY_RMP);
		MLX5_SET(destroy_rmp_in, din, rmpn, *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_CREATE_SQ:
		MLX5_SET(destroy_sq_in, din, opcode, MLX5_CMD_OP_DESTROY_SQ);
		MLX5_SET(destroy_sq_in, din, sqn, *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_CREATE_RQ:
		MLX5_SET(destroy_rq_in, din, opcode, MLX5_CMD_OP_DESTROY_RQ);
		MLX5_SET(destroy_rq_in, din, rqn, *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_CREATE_RQT:
		MLX5_SET(destroy_rqt_in, din, opcode, MLX5_CMD_OP_DESTROY_RQT);
		MLX5_SET(destroy_rqt_in, din, rqtn, *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_CREATE_TIR:
		MLX5_SET(destroy_tir_in, din, opcode, MLX5_CMD_OP_DESTROY_TIR);
		MLX5_SET(destroy_tir_in, din, tirn, *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_CREATE_TIS:
		MLX5_SET(destroy_tis_in, din, opcode, MLX5_CMD_OP_DESTROY_TIS);
		MLX5_SET(destroy_tis_in, din, tisn, *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_ALLOC_Q_COUNTER:
		MLX5_SET(dealloc_q_counter_in, din, opcode,
			 MLX5_CMD_OP_DEALLOC_Q_COUNTER);
		MLX5_SET(dealloc_q_counter_in, din, counter_set_id, *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_CREATE_FLOW_TABLE:
		*dinlen = MLX5_ST_SZ_BYTES(destroy_flow_table_in);
		MLX5_SET(destroy_flow_table_in, din, other_vport,
			 MLX5_GET(create_flow_table_in,  in, other_vport));
		MLX5_SET(destroy_flow_table_in, din, vport_number,
			 MLX5_GET(create_flow_table_in,  in, vport_number));
		MLX5_SET(destroy_flow_table_in, din, table_type,
			 MLX5_GET(create_flow_table_in,  in, table_type));
		MLX5_SET(destroy_flow_table_in, din, table_id, *obj_id);
		MLX5_SET(destroy_flow_table_in, din, opcode,
			 MLX5_CMD_OP_DESTROY_FLOW_TABLE);
		अवरोध;
	हाल MLX5_CMD_OP_CREATE_FLOW_GROUP:
		*dinlen = MLX5_ST_SZ_BYTES(destroy_flow_group_in);
		MLX5_SET(destroy_flow_group_in, din, other_vport,
			 MLX5_GET(create_flow_group_in, in, other_vport));
		MLX5_SET(destroy_flow_group_in, din, vport_number,
			 MLX5_GET(create_flow_group_in, in, vport_number));
		MLX5_SET(destroy_flow_group_in, din, table_type,
			 MLX5_GET(create_flow_group_in, in, table_type));
		MLX5_SET(destroy_flow_group_in, din, table_id,
			 MLX5_GET(create_flow_group_in, in, table_id));
		MLX5_SET(destroy_flow_group_in, din, group_id, *obj_id);
		MLX5_SET(destroy_flow_group_in, din, opcode,
			 MLX5_CMD_OP_DESTROY_FLOW_GROUP);
		अवरोध;
	हाल MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY:
		*dinlen = MLX5_ST_SZ_BYTES(delete_fte_in);
		MLX5_SET(delete_fte_in, din, other_vport,
			 MLX5_GET(set_fte_in,  in, other_vport));
		MLX5_SET(delete_fte_in, din, vport_number,
			 MLX5_GET(set_fte_in, in, vport_number));
		MLX5_SET(delete_fte_in, din, table_type,
			 MLX5_GET(set_fte_in, in, table_type));
		MLX5_SET(delete_fte_in, din, table_id,
			 MLX5_GET(set_fte_in, in, table_id));
		MLX5_SET(delete_fte_in, din, flow_index, *obj_id);
		MLX5_SET(delete_fte_in, din, opcode,
			 MLX5_CMD_OP_DELETE_FLOW_TABLE_ENTRY);
		अवरोध;
	हाल MLX5_CMD_OP_ALLOC_FLOW_COUNTER:
		MLX5_SET(dealloc_flow_counter_in, din, opcode,
			 MLX5_CMD_OP_DEALLOC_FLOW_COUNTER);
		MLX5_SET(dealloc_flow_counter_in, din, flow_counter_id,
			 *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_ALLOC_PACKET_REFORMAT_CONTEXT:
		MLX5_SET(dealloc_packet_reक्रमmat_context_in, din, opcode,
			 MLX5_CMD_OP_DEALLOC_PACKET_REFORMAT_CONTEXT);
		MLX5_SET(dealloc_packet_reक्रमmat_context_in, din,
			 packet_reक्रमmat_id, *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_ALLOC_MODIFY_HEADER_CONTEXT:
		MLX5_SET(dealloc_modअगरy_header_context_in, din, opcode,
			 MLX5_CMD_OP_DEALLOC_MODIFY_HEADER_CONTEXT);
		MLX5_SET(dealloc_modअगरy_header_context_in, din,
			 modअगरy_header_id, *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_CREATE_SCHEDULING_ELEMENT:
		*dinlen = MLX5_ST_SZ_BYTES(destroy_scheduling_element_in);
		MLX5_SET(destroy_scheduling_element_in, din,
			 scheduling_hierarchy,
			 MLX5_GET(create_scheduling_element_in, in,
				  scheduling_hierarchy));
		MLX5_SET(destroy_scheduling_element_in, din,
			 scheduling_element_id, *obj_id);
		MLX5_SET(destroy_scheduling_element_in, din, opcode,
			 MLX5_CMD_OP_DESTROY_SCHEDULING_ELEMENT);
		अवरोध;
	हाल MLX5_CMD_OP_ADD_VXLAN_UDP_DPORT:
		*dinlen = MLX5_ST_SZ_BYTES(delete_vxlan_udp_dport_in);
		MLX5_SET(delete_vxlan_udp_dport_in, din, vxlan_udp_port, *obj_id);
		MLX5_SET(delete_vxlan_udp_dport_in, din, opcode,
			 MLX5_CMD_OP_DELETE_VXLAN_UDP_DPORT);
		अवरोध;
	हाल MLX5_CMD_OP_SET_L2_TABLE_ENTRY:
		*dinlen = MLX5_ST_SZ_BYTES(delete_l2_table_entry_in);
		MLX5_SET(delete_l2_table_entry_in, din, table_index, *obj_id);
		MLX5_SET(delete_l2_table_entry_in, din, opcode,
			 MLX5_CMD_OP_DELETE_L2_TABLE_ENTRY);
		अवरोध;
	हाल MLX5_CMD_OP_CREATE_QP:
		MLX5_SET(destroy_qp_in, din, opcode, MLX5_CMD_OP_DESTROY_QP);
		MLX5_SET(destroy_qp_in, din, qpn, *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_CREATE_SRQ:
		MLX5_SET(destroy_srq_in, din, opcode, MLX5_CMD_OP_DESTROY_SRQ);
		MLX5_SET(destroy_srq_in, din, srqn, *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_CREATE_XRC_SRQ:
		MLX5_SET(destroy_xrc_srq_in, din, opcode,
			 MLX5_CMD_OP_DESTROY_XRC_SRQ);
		MLX5_SET(destroy_xrc_srq_in, din, xrc_srqn, *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_CREATE_DCT:
		MLX5_SET(destroy_dct_in, din, opcode, MLX5_CMD_OP_DESTROY_DCT);
		MLX5_SET(destroy_dct_in, din, dctn, *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_CREATE_XRQ:
		MLX5_SET(destroy_xrq_in, din, opcode, MLX5_CMD_OP_DESTROY_XRQ);
		MLX5_SET(destroy_xrq_in, din, xrqn, *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_ATTACH_TO_MCG:
		*dinlen = MLX5_ST_SZ_BYTES(detach_from_mcg_in);
		MLX5_SET(detach_from_mcg_in, din, qpn,
			 MLX5_GET(attach_to_mcg_in, in, qpn));
		स_नकल(MLX5_ADDR_OF(detach_from_mcg_in, din, multicast_gid),
		       MLX5_ADDR_OF(attach_to_mcg_in, in, multicast_gid),
		       MLX5_FLD_SZ_BYTES(attach_to_mcg_in, multicast_gid));
		MLX5_SET(detach_from_mcg_in, din, opcode,
			 MLX5_CMD_OP_DETACH_FROM_MCG);
		MLX5_SET(detach_from_mcg_in, din, qpn, *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_ALLOC_XRCD:
		MLX5_SET(dealloc_xrcd_in, din, opcode,
			 MLX5_CMD_OP_DEALLOC_XRCD);
		MLX5_SET(dealloc_xrcd_in, din, xrcd, *obj_id);
		अवरोध;
	हाल MLX5_CMD_OP_CREATE_PSV:
		MLX5_SET(destroy_psv_in, din, opcode,
			 MLX5_CMD_OP_DESTROY_PSV);
		MLX5_SET(destroy_psv_in, din, psvn, *obj_id);
		अवरोध;
	शेष:
		/* The entry must match to one of the devx_is_obj_create_cmd */
		WARN_ON(true);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक devx_handle_mkey_indirect(काष्ठा devx_obj *obj,
				     काष्ठा mlx5_ib_dev *dev,
				     व्योम *in, व्योम *out)
अणु
	काष्ठा mlx5_ib_devx_mr *devx_mr = &obj->devx_mr;
	काष्ठा mlx5_core_mkey *mkey;
	व्योम *mkc;
	u8 key;

	mkey = &devx_mr->mmkey;
	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
	key = MLX5_GET(mkc, mkc, mkey_7_0);
	mkey->key = mlx5_idx_to_mkey(
			MLX5_GET(create_mkey_out, out, mkey_index)) | key;
	mkey->type = MLX5_MKEY_INसूचीECT_DEVX;
	mkey->iova = MLX5_GET64(mkc, mkc, start_addr);
	mkey->size = MLX5_GET64(mkc, mkc, len);
	mkey->pd = MLX5_GET(mkc, mkc, pd);
	devx_mr->ndescs = MLX5_GET(mkc, mkc, translations_octword_size);
	init_रुकोqueue_head(&mkey->रुको);

	वापस mlx5r_store_odp_mkey(dev, mkey);
पूर्ण

अटल पूर्णांक devx_handle_mkey_create(काष्ठा mlx5_ib_dev *dev,
				   काष्ठा devx_obj *obj,
				   व्योम *in, पूर्णांक in_len)
अणु
	पूर्णांक min_len = MLX5_BYTE_OFF(create_mkey_in, memory_key_mkey_entry) +
			MLX5_FLD_SZ_BYTES(create_mkey_in,
			memory_key_mkey_entry);
	व्योम *mkc;
	u8 access_mode;

	अगर (in_len < min_len)
		वापस -EINVAL;

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);

	access_mode = MLX5_GET(mkc, mkc, access_mode_1_0);
	access_mode |= MLX5_GET(mkc, mkc, access_mode_4_2) << 2;

	अगर (access_mode == MLX5_MKC_ACCESS_MODE_KLMS ||
		access_mode == MLX5_MKC_ACCESS_MODE_KSM) अणु
		अगर (IS_ENABLED(CONFIG_INFINIBAND_ON_DEMAND_PAGING))
			obj->flags |= DEVX_OBJ_FLAGS_INसूचीECT_MKEY;
		वापस 0;
	पूर्ण

	MLX5_SET(create_mkey_in, in, mkey_umem_valid, 1);
	वापस 0;
पूर्ण

अटल व्योम devx_cleanup_subscription(काष्ठा mlx5_ib_dev *dev,
				      काष्ठा devx_event_subscription *sub)
अणु
	काष्ठा devx_event *event;
	काष्ठा devx_obj_event *xa_val_level2;

	अगर (sub->is_cleaned)
		वापस;

	sub->is_cleaned = 1;
	list_del_rcu(&sub->xa_list);

	अगर (list_empty(&sub->obj_list))
		वापस;

	list_del_rcu(&sub->obj_list);
	/* check whether key level 1 क्रम this obj_sub_list is empty */
	event = xa_load(&dev->devx_event_table.event_xa,
			sub->xa_key_level1);
	WARN_ON(!event);

	xa_val_level2 = xa_load(&event->object_ids, sub->xa_key_level2);
	अगर (list_empty(&xa_val_level2->obj_sub_list)) अणु
		xa_erase(&event->object_ids,
			 sub->xa_key_level2);
		kमुक्त_rcu(xa_val_level2, rcu);
	पूर्ण
पूर्ण

अटल पूर्णांक devx_obj_cleanup(काष्ठा ib_uobject *uobject,
			    क्रमागत rdma_हटाओ_reason why,
			    काष्ठा uverbs_attr_bundle *attrs)
अणु
	u32 out[MLX5_ST_SZ_DW(general_obj_out_cmd_hdr)];
	काष्ठा mlx5_devx_event_table *devx_event_table;
	काष्ठा devx_obj *obj = uobject->object;
	काष्ठा devx_event_subscription *sub_entry, *पंचांगp;
	काष्ठा mlx5_ib_dev *dev;
	पूर्णांक ret;

	dev = mlx5_udata_to_mdev(&attrs->driver_udata);
	अगर (obj->flags & DEVX_OBJ_FLAGS_INसूचीECT_MKEY &&
	    xa_erase(&obj->ib_dev->odp_mkeys,
		     mlx5_base_mkey(obj->devx_mr.mmkey.key)))
		/*
		 * The pagefault_single_data_segment() करोes commands against
		 * the mmkey, we must रुको क्रम that to stop beक्रमe मुक्तing the
		 * mkey, as another allocation could get the same mkey #.
		 */
		mlx5r_deref_रुको_odp_mkey(&obj->devx_mr.mmkey);

	अगर (obj->flags & DEVX_OBJ_FLAGS_DCT)
		ret = mlx5_core_destroy_dct(obj->ib_dev, &obj->core_dct);
	अन्यथा अगर (obj->flags & DEVX_OBJ_FLAGS_CQ)
		ret = mlx5_core_destroy_cq(obj->ib_dev->mdev, &obj->core_cq);
	अन्यथा
		ret = mlx5_cmd_exec(obj->ib_dev->mdev, obj->dinbox,
				    obj->dinlen, out, माप(out));
	अगर (ret)
		वापस ret;

	devx_event_table = &dev->devx_event_table;

	mutex_lock(&devx_event_table->event_xa_lock);
	list_क्रम_each_entry_safe(sub_entry, पंचांगp, &obj->event_sub, obj_list)
		devx_cleanup_subscription(dev, sub_entry);
	mutex_unlock(&devx_event_table->event_xa_lock);

	kमुक्त(obj);
	वापस ret;
पूर्ण

अटल व्योम devx_cq_comp(काष्ठा mlx5_core_cq *mcq, काष्ठा mlx5_eqe *eqe)
अणु
	काष्ठा devx_obj *obj = container_of(mcq, काष्ठा devx_obj, core_cq);
	काष्ठा mlx5_devx_event_table *table;
	काष्ठा devx_event *event;
	काष्ठा devx_obj_event *obj_event;
	u32 obj_id = mcq->cqn;

	table = &obj->ib_dev->devx_event_table;
	rcu_पढ़ो_lock();
	event = xa_load(&table->event_xa, MLX5_EVENT_TYPE_COMP);
	अगर (!event)
		जाओ out;

	obj_event = xa_load(&event->object_ids, obj_id);
	अगर (!obj_event)
		जाओ out;

	dispatch_event_fd(&obj_event->obj_sub_list, eqe);
out:
	rcu_पढ़ो_unlock();
पूर्ण

अटल bool is_apu_thपढ़ो_cq(काष्ठा mlx5_ib_dev *dev, स्थिर व्योम *in)
अणु
	अगर (!MLX5_CAP_GEN(dev->mdev, apu) ||
	    !MLX5_GET(cqc, MLX5_ADDR_OF(create_cq_in, in, cq_context),
		      apu_thपढ़ो_cq))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_DEVX_OBJ_CREATE)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	व्योम *cmd_in = uverbs_attr_get_alloced_ptr(attrs, MLX5_IB_ATTR_DEVX_OBJ_CREATE_CMD_IN);
	पूर्णांक cmd_out_len =  uverbs_attr_get_len(attrs,
					MLX5_IB_ATTR_DEVX_OBJ_CREATE_CMD_OUT);
	पूर्णांक cmd_in_len = uverbs_attr_get_len(attrs,
					MLX5_IB_ATTR_DEVX_OBJ_CREATE_CMD_IN);
	व्योम *cmd_out;
	काष्ठा ib_uobject *uobj = uverbs_attr_get_uobject(
		attrs, MLX5_IB_ATTR_DEVX_OBJ_CREATE_HANDLE);
	काष्ठा mlx5_ib_ucontext *c = rdma_udata_to_drv_context(
		&attrs->driver_udata, काष्ठा mlx5_ib_ucontext, ibucontext);
	काष्ठा mlx5_ib_dev *dev = to_mdev(c->ibucontext.device);
	u32 out[MLX5_ST_SZ_DW(general_obj_out_cmd_hdr)];
	काष्ठा devx_obj *obj;
	u16 obj_type = 0;
	पूर्णांक err;
	पूर्णांक uid;
	u32 obj_id;
	u16 opcode;

	अगर (MLX5_GET(general_obj_in_cmd_hdr, cmd_in, vhca_tunnel_id))
		वापस -EINVAL;

	uid = devx_get_uid(c, cmd_in);
	अगर (uid < 0)
		वापस uid;

	अगर (!devx_is_obj_create_cmd(cmd_in, &opcode))
		वापस -EINVAL;

	cmd_out = uverbs_zalloc(attrs, cmd_out_len);
	अगर (IS_ERR(cmd_out))
		वापस PTR_ERR(cmd_out);

	obj = kzalloc(माप(काष्ठा devx_obj), GFP_KERNEL);
	अगर (!obj)
		वापस -ENOMEM;

	MLX5_SET(general_obj_in_cmd_hdr, cmd_in, uid, uid);
	अगर (opcode == MLX5_CMD_OP_CREATE_MKEY) अणु
		err = devx_handle_mkey_create(dev, obj, cmd_in, cmd_in_len);
		अगर (err)
			जाओ obj_मुक्त;
	पूर्ण अन्यथा अणु
		devx_set_umem_valid(cmd_in);
	पूर्ण

	अगर (opcode == MLX5_CMD_OP_CREATE_DCT) अणु
		obj->flags |= DEVX_OBJ_FLAGS_DCT;
		err = mlx5_core_create_dct(dev, &obj->core_dct, cmd_in,
					   cmd_in_len, cmd_out, cmd_out_len);
	पूर्ण अन्यथा अगर (opcode == MLX5_CMD_OP_CREATE_CQ &&
		   !is_apu_thपढ़ो_cq(dev, cmd_in)) अणु
		obj->flags |= DEVX_OBJ_FLAGS_CQ;
		obj->core_cq.comp = devx_cq_comp;
		err = mlx5_core_create_cq(dev->mdev, &obj->core_cq,
					  cmd_in, cmd_in_len, cmd_out,
					  cmd_out_len);
	पूर्ण अन्यथा अणु
		err = mlx5_cmd_exec(dev->mdev, cmd_in,
				    cmd_in_len,
				    cmd_out, cmd_out_len);
	पूर्ण

	अगर (err)
		जाओ obj_मुक्त;

	अगर (opcode == MLX5_CMD_OP_ALLOC_FLOW_COUNTER) अणु
		u8 bulk = MLX5_GET(alloc_flow_counter_in,
				   cmd_in,
				   flow_counter_bulk);
		obj->flow_counter_bulk_size = 128UL * bulk;
	पूर्ण

	uobj->object = obj;
	INIT_LIST_HEAD(&obj->event_sub);
	obj->ib_dev = dev;
	devx_obj_build_destroy_cmd(cmd_in, cmd_out, obj->dinbox, &obj->dinlen,
				   &obj_id);
	WARN_ON(obj->dinlen > MLX5_MAX_DESTROY_INBOX_SIZE_DW * माप(u32));

	err = uverbs_copy_to(attrs, MLX5_IB_ATTR_DEVX_OBJ_CREATE_CMD_OUT, cmd_out, cmd_out_len);
	अगर (err)
		जाओ obj_destroy;

	अगर (opcode == MLX5_CMD_OP_CREATE_GENERAL_OBJECT)
		obj_type = MLX5_GET(general_obj_in_cmd_hdr, cmd_in, obj_type);
	obj->obj_id = get_enc_obj_id(opcode | obj_type << 16, obj_id);

	अगर (obj->flags & DEVX_OBJ_FLAGS_INसूचीECT_MKEY) अणु
		err = devx_handle_mkey_indirect(obj, dev, cmd_in, cmd_out);
		अगर (err)
			जाओ obj_destroy;
	पूर्ण
	वापस 0;

obj_destroy:
	अगर (obj->flags & DEVX_OBJ_FLAGS_DCT)
		mlx5_core_destroy_dct(obj->ib_dev, &obj->core_dct);
	अन्यथा अगर (obj->flags & DEVX_OBJ_FLAGS_CQ)
		mlx5_core_destroy_cq(obj->ib_dev->mdev, &obj->core_cq);
	अन्यथा
		mlx5_cmd_exec(obj->ib_dev->mdev, obj->dinbox, obj->dinlen, out,
			      माप(out));
obj_मुक्त:
	kमुक्त(obj);
	वापस err;
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_DEVX_OBJ_MODIFY)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	व्योम *cmd_in = uverbs_attr_get_alloced_ptr(attrs, MLX5_IB_ATTR_DEVX_OBJ_MODIFY_CMD_IN);
	पूर्णांक cmd_out_len = uverbs_attr_get_len(attrs,
					MLX5_IB_ATTR_DEVX_OBJ_MODIFY_CMD_OUT);
	काष्ठा ib_uobject *uobj = uverbs_attr_get_uobject(attrs,
							  MLX5_IB_ATTR_DEVX_OBJ_MODIFY_HANDLE);
	काष्ठा mlx5_ib_ucontext *c = rdma_udata_to_drv_context(
		&attrs->driver_udata, काष्ठा mlx5_ib_ucontext, ibucontext);
	काष्ठा mlx5_ib_dev *mdev = to_mdev(c->ibucontext.device);
	व्योम *cmd_out;
	पूर्णांक err;
	पूर्णांक uid;

	अगर (MLX5_GET(general_obj_in_cmd_hdr, cmd_in, vhca_tunnel_id))
		वापस -EINVAL;

	uid = devx_get_uid(c, cmd_in);
	अगर (uid < 0)
		वापस uid;

	अगर (!devx_is_obj_modअगरy_cmd(cmd_in))
		वापस -EINVAL;

	अगर (!devx_is_valid_obj_id(attrs, uobj, cmd_in))
		वापस -EINVAL;

	cmd_out = uverbs_zalloc(attrs, cmd_out_len);
	अगर (IS_ERR(cmd_out))
		वापस PTR_ERR(cmd_out);

	MLX5_SET(general_obj_in_cmd_hdr, cmd_in, uid, uid);
	devx_set_umem_valid(cmd_in);

	err = mlx5_cmd_exec(mdev->mdev, cmd_in,
			    uverbs_attr_get_len(attrs, MLX5_IB_ATTR_DEVX_OBJ_MODIFY_CMD_IN),
			    cmd_out, cmd_out_len);
	अगर (err)
		वापस err;

	वापस uverbs_copy_to(attrs, MLX5_IB_ATTR_DEVX_OBJ_MODIFY_CMD_OUT,
			      cmd_out, cmd_out_len);
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_DEVX_OBJ_QUERY)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	व्योम *cmd_in = uverbs_attr_get_alloced_ptr(attrs, MLX5_IB_ATTR_DEVX_OBJ_QUERY_CMD_IN);
	पूर्णांक cmd_out_len = uverbs_attr_get_len(attrs,
					      MLX5_IB_ATTR_DEVX_OBJ_QUERY_CMD_OUT);
	काष्ठा ib_uobject *uobj = uverbs_attr_get_uobject(attrs,
							  MLX5_IB_ATTR_DEVX_OBJ_QUERY_HANDLE);
	काष्ठा mlx5_ib_ucontext *c = rdma_udata_to_drv_context(
		&attrs->driver_udata, काष्ठा mlx5_ib_ucontext, ibucontext);
	व्योम *cmd_out;
	पूर्णांक err;
	पूर्णांक uid;
	काष्ठा mlx5_ib_dev *mdev = to_mdev(c->ibucontext.device);

	अगर (MLX5_GET(general_obj_in_cmd_hdr, cmd_in, vhca_tunnel_id))
		वापस -EINVAL;

	uid = devx_get_uid(c, cmd_in);
	अगर (uid < 0)
		वापस uid;

	अगर (!devx_is_obj_query_cmd(cmd_in))
		वापस -EINVAL;

	अगर (!devx_is_valid_obj_id(attrs, uobj, cmd_in))
		वापस -EINVAL;

	cmd_out = uverbs_zalloc(attrs, cmd_out_len);
	अगर (IS_ERR(cmd_out))
		वापस PTR_ERR(cmd_out);

	MLX5_SET(general_obj_in_cmd_hdr, cmd_in, uid, uid);
	err = mlx5_cmd_exec(mdev->mdev, cmd_in,
			    uverbs_attr_get_len(attrs, MLX5_IB_ATTR_DEVX_OBJ_QUERY_CMD_IN),
			    cmd_out, cmd_out_len);
	अगर (err)
		वापस err;

	वापस uverbs_copy_to(attrs, MLX5_IB_ATTR_DEVX_OBJ_QUERY_CMD_OUT,
			      cmd_out, cmd_out_len);
पूर्ण

काष्ठा devx_async_event_queue अणु
	spinlock_t		lock;
	रुको_queue_head_t	poll_रुको;
	काष्ठा list_head	event_list;
	atomic_t		bytes_in_use;
	u8			is_destroyed:1;
पूर्ण;

काष्ठा devx_async_cmd_event_file अणु
	काष्ठा ib_uobject		uobj;
	काष्ठा devx_async_event_queue	ev_queue;
	काष्ठा mlx5_async_ctx		async_ctx;
पूर्ण;

अटल व्योम devx_init_event_queue(काष्ठा devx_async_event_queue *ev_queue)
अणु
	spin_lock_init(&ev_queue->lock);
	INIT_LIST_HEAD(&ev_queue->event_list);
	init_रुकोqueue_head(&ev_queue->poll_रुको);
	atomic_set(&ev_queue->bytes_in_use, 0);
	ev_queue->is_destroyed = 0;
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_DEVX_ASYNC_CMD_FD_ALLOC)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा devx_async_cmd_event_file *ev_file;

	काष्ठा ib_uobject *uobj = uverbs_attr_get_uobject(
		attrs, MLX5_IB_ATTR_DEVX_ASYNC_CMD_FD_ALLOC_HANDLE);
	काष्ठा mlx5_ib_dev *mdev = mlx5_udata_to_mdev(&attrs->driver_udata);

	ev_file = container_of(uobj, काष्ठा devx_async_cmd_event_file,
			       uobj);
	devx_init_event_queue(&ev_file->ev_queue);
	mlx5_cmd_init_async_ctx(mdev->mdev, &ev_file->async_ctx);
	वापस 0;
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_DEVX_ASYNC_EVENT_FD_ALLOC)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uobject *uobj = uverbs_attr_get_uobject(
		attrs, MLX5_IB_ATTR_DEVX_ASYNC_EVENT_FD_ALLOC_HANDLE);
	काष्ठा devx_async_event_file *ev_file;
	काष्ठा mlx5_ib_ucontext *c = rdma_udata_to_drv_context(
		&attrs->driver_udata, काष्ठा mlx5_ib_ucontext, ibucontext);
	काष्ठा mlx5_ib_dev *dev = to_mdev(c->ibucontext.device);
	u32 flags;
	पूर्णांक err;

	err = uverbs_get_flags32(&flags, attrs,
		MLX5_IB_ATTR_DEVX_ASYNC_EVENT_FD_ALLOC_FLAGS,
		MLX5_IB_UAPI_DEVX_CR_EV_CH_FLAGS_OMIT_DATA);

	अगर (err)
		वापस err;

	ev_file = container_of(uobj, काष्ठा devx_async_event_file,
			       uobj);
	spin_lock_init(&ev_file->lock);
	INIT_LIST_HEAD(&ev_file->event_list);
	init_रुकोqueue_head(&ev_file->poll_रुको);
	अगर (flags & MLX5_IB_UAPI_DEVX_CR_EV_CH_FLAGS_OMIT_DATA)
		ev_file->omit_data = 1;
	INIT_LIST_HEAD(&ev_file->subscribed_events_list);
	ev_file->dev = dev;
	get_device(&dev->ib_dev.dev);
	वापस 0;
पूर्ण

अटल व्योम devx_query_callback(पूर्णांक status, काष्ठा mlx5_async_work *context)
अणु
	काष्ठा devx_async_data *async_data =
		container_of(context, काष्ठा devx_async_data, cb_work);
	काष्ठा devx_async_cmd_event_file *ev_file = async_data->ev_file;
	काष्ठा devx_async_event_queue *ev_queue = &ev_file->ev_queue;
	अचिन्हित दीर्घ flags;

	/*
	 * Note that अगर the काष्ठा devx_async_cmd_event_file uobj begins to be
	 * destroyed it will block at mlx5_cmd_cleanup_async_ctx() until this
	 * routine वापसs, ensuring that it always reमुख्यs valid here.
	 */
	spin_lock_irqsave(&ev_queue->lock, flags);
	list_add_tail(&async_data->list, &ev_queue->event_list);
	spin_unlock_irqrestore(&ev_queue->lock, flags);

	wake_up_पूर्णांकerruptible(&ev_queue->poll_रुको);
पूर्ण

#घोषणा MAX_ASYNC_BYTES_IN_USE (1024 * 1024) /* 1MB */

अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_DEVX_OBJ_ASYNC_QUERY)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	व्योम *cmd_in = uverbs_attr_get_alloced_ptr(attrs,
				MLX5_IB_ATTR_DEVX_OBJ_QUERY_ASYNC_CMD_IN);
	काष्ठा ib_uobject *uobj = uverbs_attr_get_uobject(
				attrs,
				MLX5_IB_ATTR_DEVX_OBJ_QUERY_ASYNC_HANDLE);
	u16 cmd_out_len;
	काष्ठा mlx5_ib_ucontext *c = rdma_udata_to_drv_context(
		&attrs->driver_udata, काष्ठा mlx5_ib_ucontext, ibucontext);
	काष्ठा ib_uobject *fd_uobj;
	पूर्णांक err;
	पूर्णांक uid;
	काष्ठा mlx5_ib_dev *mdev = to_mdev(c->ibucontext.device);
	काष्ठा devx_async_cmd_event_file *ev_file;
	काष्ठा devx_async_data *async_data;

	अगर (MLX5_GET(general_obj_in_cmd_hdr, cmd_in, vhca_tunnel_id))
		वापस -EINVAL;

	uid = devx_get_uid(c, cmd_in);
	अगर (uid < 0)
		वापस uid;

	अगर (!devx_is_obj_query_cmd(cmd_in))
		वापस -EINVAL;

	err = uverbs_get_स्थिर(&cmd_out_len, attrs,
			       MLX5_IB_ATTR_DEVX_OBJ_QUERY_ASYNC_OUT_LEN);
	अगर (err)
		वापस err;

	अगर (!devx_is_valid_obj_id(attrs, uobj, cmd_in))
		वापस -EINVAL;

	fd_uobj = uverbs_attr_get_uobject(attrs,
				MLX5_IB_ATTR_DEVX_OBJ_QUERY_ASYNC_FD);
	अगर (IS_ERR(fd_uobj))
		वापस PTR_ERR(fd_uobj);

	ev_file = container_of(fd_uobj, काष्ठा devx_async_cmd_event_file,
			       uobj);

	अगर (atomic_add_वापस(cmd_out_len, &ev_file->ev_queue.bytes_in_use) >
			MAX_ASYNC_BYTES_IN_USE) अणु
		atomic_sub(cmd_out_len, &ev_file->ev_queue.bytes_in_use);
		वापस -EAGAIN;
	पूर्ण

	async_data = kvzalloc(काष्ठा_size(async_data, hdr.out_data,
					  cmd_out_len), GFP_KERNEL);
	अगर (!async_data) अणु
		err = -ENOMEM;
		जाओ sub_bytes;
	पूर्ण

	err = uverbs_copy_from(&async_data->hdr.wr_id, attrs,
			       MLX5_IB_ATTR_DEVX_OBJ_QUERY_ASYNC_WR_ID);
	अगर (err)
		जाओ मुक्त_async;

	async_data->cmd_out_len = cmd_out_len;
	async_data->mdev = mdev;
	async_data->ev_file = ev_file;

	MLX5_SET(general_obj_in_cmd_hdr, cmd_in, uid, uid);
	err = mlx5_cmd_exec_cb(&ev_file->async_ctx, cmd_in,
		    uverbs_attr_get_len(attrs,
				MLX5_IB_ATTR_DEVX_OBJ_QUERY_ASYNC_CMD_IN),
		    async_data->hdr.out_data,
		    async_data->cmd_out_len,
		    devx_query_callback, &async_data->cb_work);

	अगर (err)
		जाओ मुक्त_async;

	वापस 0;

मुक्त_async:
	kvमुक्त(async_data);
sub_bytes:
	atomic_sub(cmd_out_len, &ev_file->ev_queue.bytes_in_use);
	वापस err;
पूर्ण

अटल व्योम
subscribe_event_xa_dealloc(काष्ठा mlx5_devx_event_table *devx_event_table,
			   u32 key_level1,
			   bool is_level2,
			   u32 key_level2)
अणु
	काष्ठा devx_event *event;
	काष्ठा devx_obj_event *xa_val_level2;

	/* Level 1 is valid क्रम future use, no need to मुक्त */
	अगर (!is_level2)
		वापस;

	event = xa_load(&devx_event_table->event_xa, key_level1);
	WARN_ON(!event);

	xa_val_level2 = xa_load(&event->object_ids,
				key_level2);
	अगर (list_empty(&xa_val_level2->obj_sub_list)) अणु
		xa_erase(&event->object_ids,
			 key_level2);
		kमुक्त_rcu(xa_val_level2, rcu);
	पूर्ण
पूर्ण

अटल पूर्णांक
subscribe_event_xa_alloc(काष्ठा mlx5_devx_event_table *devx_event_table,
			 u32 key_level1,
			 bool is_level2,
			 u32 key_level2)
अणु
	काष्ठा devx_obj_event *obj_event;
	काष्ठा devx_event *event;
	पूर्णांक err;

	event = xa_load(&devx_event_table->event_xa, key_level1);
	अगर (!event) अणु
		event = kzalloc(माप(*event), GFP_KERNEL);
		अगर (!event)
			वापस -ENOMEM;

		INIT_LIST_HEAD(&event->unaffiliated_list);
		xa_init(&event->object_ids);

		err = xa_insert(&devx_event_table->event_xa,
				key_level1,
				event,
				GFP_KERNEL);
		अगर (err) अणु
			kमुक्त(event);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (!is_level2)
		वापस 0;

	obj_event = xa_load(&event->object_ids, key_level2);
	अगर (!obj_event) अणु
		obj_event = kzalloc(माप(*obj_event), GFP_KERNEL);
		अगर (!obj_event)
			/* Level1 is valid क्रम future use, no need to मुक्त */
			वापस -ENOMEM;

		err = xa_insert(&event->object_ids,
				key_level2,
				obj_event,
				GFP_KERNEL);
		अगर (err)
			वापस err;
		INIT_LIST_HEAD(&obj_event->obj_sub_list);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool is_valid_events_legacy(पूर्णांक num_events, u16 *event_type_num_list,
				   काष्ठा devx_obj *obj)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_events; i++) अणु
		अगर (obj) अणु
			अगर (!is_legacy_obj_event_num(event_type_num_list[i]))
				वापस false;
		पूर्ण अन्यथा अगर (!is_legacy_unaffiliated_event_num(
				event_type_num_list[i])) अणु
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

#घोषणा MAX_SUPP_EVENT_NUM 255
अटल bool is_valid_events(काष्ठा mlx5_core_dev *dev,
			    पूर्णांक num_events, u16 *event_type_num_list,
			    काष्ठा devx_obj *obj)
अणु
	__be64 *aff_events;
	__be64 *unaff_events;
	पूर्णांक mask_entry;
	पूर्णांक mask_bit;
	पूर्णांक i;

	अगर (MLX5_CAP_GEN(dev, event_cap)) अणु
		aff_events = MLX5_CAP_DEV_EVENT(dev,
						user_affiliated_events);
		unaff_events = MLX5_CAP_DEV_EVENT(dev,
						  user_unaffiliated_events);
	पूर्ण अन्यथा अणु
		वापस is_valid_events_legacy(num_events, event_type_num_list,
					      obj);
	पूर्ण

	क्रम (i = 0; i < num_events; i++) अणु
		अगर (event_type_num_list[i] > MAX_SUPP_EVENT_NUM)
			वापस false;

		mask_entry = event_type_num_list[i] / 64;
		mask_bit = event_type_num_list[i] % 64;

		अगर (obj) अणु
			/* CQ completion */
			अगर (event_type_num_list[i] == 0)
				जारी;

			अगर (!(be64_to_cpu(aff_events[mask_entry]) &
					(1ull << mask_bit)))
				वापस false;

			जारी;
		पूर्ण

		अगर (!(be64_to_cpu(unaff_events[mask_entry]) &
				(1ull << mask_bit)))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

#घोषणा MAX_NUM_EVENTS 16
अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_DEVX_SUBSCRIBE_EVENT)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uobject *devx_uobj = uverbs_attr_get_uobject(
				attrs,
				MLX5_IB_ATTR_DEVX_SUBSCRIBE_EVENT_OBJ_HANDLE);
	काष्ठा mlx5_ib_ucontext *c = rdma_udata_to_drv_context(
		&attrs->driver_udata, काष्ठा mlx5_ib_ucontext, ibucontext);
	काष्ठा mlx5_ib_dev *dev = to_mdev(c->ibucontext.device);
	काष्ठा ib_uobject *fd_uobj;
	काष्ठा devx_obj *obj = शून्य;
	काष्ठा devx_async_event_file *ev_file;
	काष्ठा mlx5_devx_event_table *devx_event_table = &dev->devx_event_table;
	u16 *event_type_num_list;
	काष्ठा devx_event_subscription *event_sub, *पंचांगp_sub;
	काष्ठा list_head sub_list;
	पूर्णांक redirect_fd;
	bool use_eventfd = false;
	पूर्णांक num_events;
	पूर्णांक num_alloc_xa_entries = 0;
	u16 obj_type = 0;
	u64 cookie = 0;
	u32 obj_id = 0;
	पूर्णांक err;
	पूर्णांक i;

	अगर (!c->devx_uid)
		वापस -EINVAL;

	अगर (!IS_ERR(devx_uobj)) अणु
		obj = (काष्ठा devx_obj *)devx_uobj->object;
		अगर (obj)
			obj_id = get_dec_obj_id(obj->obj_id);
	पूर्ण

	fd_uobj = uverbs_attr_get_uobject(attrs,
				MLX5_IB_ATTR_DEVX_SUBSCRIBE_EVENT_FD_HANDLE);
	अगर (IS_ERR(fd_uobj))
		वापस PTR_ERR(fd_uobj);

	ev_file = container_of(fd_uobj, काष्ठा devx_async_event_file,
			       uobj);

	अगर (uverbs_attr_is_valid(attrs,
				 MLX5_IB_ATTR_DEVX_SUBSCRIBE_EVENT_FD_NUM)) अणु
		err = uverbs_copy_from(&redirect_fd, attrs,
			       MLX5_IB_ATTR_DEVX_SUBSCRIBE_EVENT_FD_NUM);
		अगर (err)
			वापस err;

		use_eventfd = true;
	पूर्ण

	अगर (uverbs_attr_is_valid(attrs,
				 MLX5_IB_ATTR_DEVX_SUBSCRIBE_EVENT_COOKIE)) अणु
		अगर (use_eventfd)
			वापस -EINVAL;

		err = uverbs_copy_from(&cookie, attrs,
				MLX5_IB_ATTR_DEVX_SUBSCRIBE_EVENT_COOKIE);
		अगर (err)
			वापस err;
	पूर्ण

	num_events = uverbs_attr_ptr_get_array_size(
		attrs, MLX5_IB_ATTR_DEVX_SUBSCRIBE_EVENT_TYPE_NUM_LIST,
		माप(u16));

	अगर (num_events < 0)
		वापस num_events;

	अगर (num_events > MAX_NUM_EVENTS)
		वापस -EINVAL;

	event_type_num_list = uverbs_attr_get_alloced_ptr(attrs,
			MLX5_IB_ATTR_DEVX_SUBSCRIBE_EVENT_TYPE_NUM_LIST);

	अगर (!is_valid_events(dev->mdev, num_events, event_type_num_list, obj))
		वापस -EINVAL;

	INIT_LIST_HEAD(&sub_list);

	/* Protect from concurrent subscriptions to same XA entries to allow
	 * both to succeed
	 */
	mutex_lock(&devx_event_table->event_xa_lock);
	क्रम (i = 0; i < num_events; i++) अणु
		u32 key_level1;

		अगर (obj)
			obj_type = get_dec_obj_type(obj,
						    event_type_num_list[i]);
		key_level1 = event_type_num_list[i] | obj_type << 16;

		err = subscribe_event_xa_alloc(devx_event_table,
					       key_level1,
					       obj,
					       obj_id);
		अगर (err)
			जाओ err;

		num_alloc_xa_entries++;
		event_sub = kzalloc(माप(*event_sub), GFP_KERNEL);
		अगर (!event_sub) अणु
			err = -ENOMEM;
			जाओ err;
		पूर्ण

		list_add_tail(&event_sub->event_list, &sub_list);
		uverbs_uobject_get(&ev_file->uobj);
		अगर (use_eventfd) अणु
			event_sub->eventfd =
				eventfd_ctx_fdget(redirect_fd);

			अगर (IS_ERR(event_sub->eventfd)) अणु
				err = PTR_ERR(event_sub->eventfd);
				event_sub->eventfd = शून्य;
				जाओ err;
			पूर्ण
		पूर्ण

		event_sub->cookie = cookie;
		event_sub->ev_file = ev_file;
		/* May be needed upon cleanup the devx object/subscription */
		event_sub->xa_key_level1 = key_level1;
		event_sub->xa_key_level2 = obj_id;
		INIT_LIST_HEAD(&event_sub->obj_list);
	पूर्ण

	/* Once all the allocations and the XA data insertions were करोne we
	 * can go ahead and add all the subscriptions to the relevant lists
	 * without concern of a failure.
	 */
	list_क्रम_each_entry_safe(event_sub, पंचांगp_sub, &sub_list, event_list) अणु
		काष्ठा devx_event *event;
		काष्ठा devx_obj_event *obj_event;

		list_del_init(&event_sub->event_list);

		spin_lock_irq(&ev_file->lock);
		list_add_tail_rcu(&event_sub->file_list,
				  &ev_file->subscribed_events_list);
		spin_unlock_irq(&ev_file->lock);

		event = xa_load(&devx_event_table->event_xa,
				event_sub->xa_key_level1);
		WARN_ON(!event);

		अगर (!obj) अणु
			list_add_tail_rcu(&event_sub->xa_list,
					  &event->unaffiliated_list);
			जारी;
		पूर्ण

		obj_event = xa_load(&event->object_ids, obj_id);
		WARN_ON(!obj_event);
		list_add_tail_rcu(&event_sub->xa_list,
				  &obj_event->obj_sub_list);
		list_add_tail_rcu(&event_sub->obj_list,
				  &obj->event_sub);
	पूर्ण

	mutex_unlock(&devx_event_table->event_xa_lock);
	वापस 0;

err:
	list_क्रम_each_entry_safe(event_sub, पंचांगp_sub, &sub_list, event_list) अणु
		list_del(&event_sub->event_list);

		subscribe_event_xa_dealloc(devx_event_table,
					   event_sub->xa_key_level1,
					   obj,
					   obj_id);

		अगर (event_sub->eventfd)
			eventfd_ctx_put(event_sub->eventfd);
		uverbs_uobject_put(&event_sub->ev_file->uobj);
		kमुक्त(event_sub);
	पूर्ण

	mutex_unlock(&devx_event_table->event_xa_lock);
	वापस err;
पूर्ण

अटल पूर्णांक devx_umem_get(काष्ठा mlx5_ib_dev *dev, काष्ठा ib_ucontext *ucontext,
			 काष्ठा uverbs_attr_bundle *attrs,
			 काष्ठा devx_umem *obj)
अणु
	u64 addr;
	माप_प्रकार size;
	u32 access;
	पूर्णांक err;

	अगर (uverbs_copy_from(&addr, attrs, MLX5_IB_ATTR_DEVX_UMEM_REG_ADDR) ||
	    uverbs_copy_from(&size, attrs, MLX5_IB_ATTR_DEVX_UMEM_REG_LEN))
		वापस -EFAULT;

	err = uverbs_get_flags32(&access, attrs,
				 MLX5_IB_ATTR_DEVX_UMEM_REG_ACCESS,
				 IB_ACCESS_LOCAL_WRITE |
				 IB_ACCESS_REMOTE_WRITE |
				 IB_ACCESS_REMOTE_READ);
	अगर (err)
		वापस err;

	err = ib_check_mr_access(&dev->ib_dev, access);
	अगर (err)
		वापस err;

	obj->umem = ib_umem_get(&dev->ib_dev, addr, size, access);
	अगर (IS_ERR(obj->umem))
		वापस PTR_ERR(obj->umem);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक devx_umem_find_best_pgsize(काष्ठा ib_umem *umem,
					       अचिन्हित दीर्घ pgsz_biपंचांगap)
अणु
	अचिन्हित दीर्घ page_size;

	/* Don't bother checking larger page sizes as offset must be zero and
	 * total DEVX umem length must be equal to total umem length.
	 */
	pgsz_biपंचांगap &= GENMASK_ULL(max_t(u64, order_base_2(umem->length),
					 PAGE_SHIFT),
				   MLX5_ADAPTER_PAGE_SHIFT);
	अगर (!pgsz_biपंचांगap)
		वापस 0;

	page_size = ib_umem_find_best_pgoff(umem, pgsz_biपंचांगap, U64_MAX);
	अगर (!page_size)
		वापस 0;

	/* If the page_size is less than the CPU page size then we can use the
	 * offset and create a umem which is a subset of the page list.
	 * For larger page sizes we can't be sure the DMA  list reflects the
	 * VA so we must ensure that the umem extent is exactly equal to the
	 * page list. Reduce the page size until one of these हालs is true.
	 */
	जबतक ((ib_umem_dma_offset(umem, page_size) != 0 ||
		(umem->length % page_size) != 0) &&
		page_size > PAGE_SIZE)
		page_size /= 2;

	वापस page_size;
पूर्ण

अटल पूर्णांक devx_umem_reg_cmd_alloc(काष्ठा mlx5_ib_dev *dev,
				   काष्ठा uverbs_attr_bundle *attrs,
				   काष्ठा devx_umem *obj,
				   काष्ठा devx_umem_reg_cmd *cmd)
अणु
	अचिन्हित दीर्घ pgsz_biपंचांगap;
	अचिन्हित पूर्णांक page_size;
	__be64 *mtt;
	व्योम *umem;
	पूर्णांक ret;

	/*
	 * If the user करोes not pass in pgsz_biपंचांगap then the user promises not
	 * to use umem_offset!=0 in any commands that allocate on top of the
	 * umem.
	 *
	 * If the user wants to use a umem_offset then it must pass in
	 * pgsz_biपंचांगap which guides the maximum page size and thus maximum
	 * object alignment inside the umem. See the PRM.
	 *
	 * Users are not allowed to use IOVA here, mkeys are not supported on
	 * umem.
	 */
	ret = uverbs_get_स्थिर_शेष(&pgsz_biपंचांगap, attrs,
			MLX5_IB_ATTR_DEVX_UMEM_REG_PGSZ_BITMAP,
			GENMASK_ULL(63,
				    min(PAGE_SHIFT, MLX5_ADAPTER_PAGE_SHIFT)));
	अगर (ret)
		वापस ret;

	page_size = devx_umem_find_best_pgsize(obj->umem, pgsz_biपंचांगap);
	अगर (!page_size)
		वापस -EINVAL;

	cmd->inlen = MLX5_ST_SZ_BYTES(create_umem_in) +
		     (MLX5_ST_SZ_BYTES(mtt) *
		      ib_umem_num_dma_blocks(obj->umem, page_size));
	cmd->in = uverbs_zalloc(attrs, cmd->inlen);
	अगर (IS_ERR(cmd->in))
		वापस PTR_ERR(cmd->in);

	umem = MLX5_ADDR_OF(create_umem_in, cmd->in, umem);
	mtt = (__be64 *)MLX5_ADDR_OF(umem, umem, mtt);

	MLX5_SET(create_umem_in, cmd->in, opcode, MLX5_CMD_OP_CREATE_UMEM);
	MLX5_SET64(umem, umem, num_of_mtt,
		   ib_umem_num_dma_blocks(obj->umem, page_size));
	MLX5_SET(umem, umem, log_page_size,
		 order_base_2(page_size) - MLX5_ADAPTER_PAGE_SHIFT);
	MLX5_SET(umem, umem, page_offset,
		 ib_umem_dma_offset(obj->umem, page_size));

	mlx5_ib_populate_pas(obj->umem, page_size, mtt,
			     (obj->umem->writable ? MLX5_IB_MTT_WRITE : 0) |
				     MLX5_IB_MTT_READ);
	वापस 0;
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_DEVX_UMEM_REG)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा devx_umem_reg_cmd cmd;
	काष्ठा devx_umem *obj;
	काष्ठा ib_uobject *uobj = uverbs_attr_get_uobject(
		attrs, MLX5_IB_ATTR_DEVX_UMEM_REG_HANDLE);
	u32 obj_id;
	काष्ठा mlx5_ib_ucontext *c = rdma_udata_to_drv_context(
		&attrs->driver_udata, काष्ठा mlx5_ib_ucontext, ibucontext);
	काष्ठा mlx5_ib_dev *dev = to_mdev(c->ibucontext.device);
	पूर्णांक err;

	अगर (!c->devx_uid)
		वापस -EINVAL;

	obj = kzalloc(माप(काष्ठा devx_umem), GFP_KERNEL);
	अगर (!obj)
		वापस -ENOMEM;

	err = devx_umem_get(dev, &c->ibucontext, attrs, obj);
	अगर (err)
		जाओ err_obj_मुक्त;

	err = devx_umem_reg_cmd_alloc(dev, attrs, obj, &cmd);
	अगर (err)
		जाओ err_umem_release;

	MLX5_SET(create_umem_in, cmd.in, uid, c->devx_uid);
	err = mlx5_cmd_exec(dev->mdev, cmd.in, cmd.inlen, cmd.out,
			    माप(cmd.out));
	अगर (err)
		जाओ err_umem_release;

	obj->mdev = dev->mdev;
	uobj->object = obj;
	devx_obj_build_destroy_cmd(cmd.in, cmd.out, obj->dinbox, &obj->dinlen, &obj_id);
	uverbs_finalize_uobj_create(attrs, MLX5_IB_ATTR_DEVX_UMEM_REG_HANDLE);

	err = uverbs_copy_to(attrs, MLX5_IB_ATTR_DEVX_UMEM_REG_OUT_ID, &obj_id,
			     माप(obj_id));
	वापस err;

err_umem_release:
	ib_umem_release(obj->umem);
err_obj_मुक्त:
	kमुक्त(obj);
	वापस err;
पूर्ण

अटल पूर्णांक devx_umem_cleanup(काष्ठा ib_uobject *uobject,
			     क्रमागत rdma_हटाओ_reason why,
			     काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा devx_umem *obj = uobject->object;
	u32 out[MLX5_ST_SZ_DW(general_obj_out_cmd_hdr)];
	पूर्णांक err;

	err = mlx5_cmd_exec(obj->mdev, obj->dinbox, obj->dinlen, out, माप(out));
	अगर (err)
		वापस err;

	ib_umem_release(obj->umem);
	kमुक्त(obj);
	वापस 0;
पूर्ण

अटल bool is_unaffiliated_event(काष्ठा mlx5_core_dev *dev,
				  अचिन्हित दीर्घ event_type)
अणु
	__be64 *unaff_events;
	पूर्णांक mask_entry;
	पूर्णांक mask_bit;

	अगर (!MLX5_CAP_GEN(dev, event_cap))
		वापस is_legacy_unaffiliated_event_num(event_type);

	unaff_events = MLX5_CAP_DEV_EVENT(dev,
					  user_unaffiliated_events);
	WARN_ON(event_type > MAX_SUPP_EVENT_NUM);

	mask_entry = event_type / 64;
	mask_bit = event_type % 64;

	अगर (!(be64_to_cpu(unaff_events[mask_entry]) & (1ull << mask_bit)))
		वापस false;

	वापस true;
पूर्ण

अटल u32 devx_get_obj_id_from_event(अचिन्हित दीर्घ event_type, व्योम *data)
अणु
	काष्ठा mlx5_eqe *eqe = data;
	u32 obj_id = 0;

	चयन (event_type) अणु
	हाल MLX5_EVENT_TYPE_SRQ_CATAS_ERROR:
	हाल MLX5_EVENT_TYPE_SRQ_RQ_LIMIT:
	हाल MLX5_EVENT_TYPE_PATH_MIG:
	हाल MLX5_EVENT_TYPE_COMM_EST:
	हाल MLX5_EVENT_TYPE_SQ_DRAINED:
	हाल MLX5_EVENT_TYPE_SRQ_LAST_WQE:
	हाल MLX5_EVENT_TYPE_WQ_CATAS_ERROR:
	हाल MLX5_EVENT_TYPE_PATH_MIG_FAILED:
	हाल MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR:
	हाल MLX5_EVENT_TYPE_WQ_ACCESS_ERROR:
		obj_id = be32_to_cpu(eqe->data.qp_srq.qp_srq_n) & 0xffffff;
		अवरोध;
	हाल MLX5_EVENT_TYPE_XRQ_ERROR:
		obj_id = be32_to_cpu(eqe->data.xrq_err.type_xrqn) & 0xffffff;
		अवरोध;
	हाल MLX5_EVENT_TYPE_DCT_DRAINED:
	हाल MLX5_EVENT_TYPE_DCT_KEY_VIOLATION:
		obj_id = be32_to_cpu(eqe->data.dct.dctn) & 0xffffff;
		अवरोध;
	हाल MLX5_EVENT_TYPE_CQ_ERROR:
		obj_id = be32_to_cpu(eqe->data.cq_err.cqn) & 0xffffff;
		अवरोध;
	शेष:
		obj_id = MLX5_GET(affiliated_event_header, &eqe->data, obj_id);
		अवरोध;
	पूर्ण

	वापस obj_id;
पूर्ण

अटल पूर्णांक deliver_event(काष्ठा devx_event_subscription *event_sub,
			 स्थिर व्योम *data)
अणु
	काष्ठा devx_async_event_file *ev_file;
	काष्ठा devx_async_event_data *event_data;
	अचिन्हित दीर्घ flags;

	ev_file = event_sub->ev_file;

	अगर (ev_file->omit_data) अणु
		spin_lock_irqsave(&ev_file->lock, flags);
		अगर (!list_empty(&event_sub->event_list) ||
		    ev_file->is_destroyed) अणु
			spin_unlock_irqrestore(&ev_file->lock, flags);
			वापस 0;
		पूर्ण

		list_add_tail(&event_sub->event_list, &ev_file->event_list);
		spin_unlock_irqrestore(&ev_file->lock, flags);
		wake_up_पूर्णांकerruptible(&ev_file->poll_रुको);
		वापस 0;
	पूर्ण

	event_data = kzalloc(माप(*event_data) + माप(काष्ठा mlx5_eqe),
			     GFP_ATOMIC);
	अगर (!event_data) अणु
		spin_lock_irqsave(&ev_file->lock, flags);
		ev_file->is_overflow_err = 1;
		spin_unlock_irqrestore(&ev_file->lock, flags);
		वापस -ENOMEM;
	पूर्ण

	event_data->hdr.cookie = event_sub->cookie;
	स_नकल(event_data->hdr.out_data, data, माप(काष्ठा mlx5_eqe));

	spin_lock_irqsave(&ev_file->lock, flags);
	अगर (!ev_file->is_destroyed)
		list_add_tail(&event_data->list, &ev_file->event_list);
	अन्यथा
		kमुक्त(event_data);
	spin_unlock_irqrestore(&ev_file->lock, flags);
	wake_up_पूर्णांकerruptible(&ev_file->poll_रुको);

	वापस 0;
पूर्ण

अटल व्योम dispatch_event_fd(काष्ठा list_head *fd_list,
			      स्थिर व्योम *data)
अणु
	काष्ठा devx_event_subscription *item;

	list_क्रम_each_entry_rcu(item, fd_list, xa_list) अणु
		अगर (item->eventfd)
			eventfd_संकेत(item->eventfd, 1);
		अन्यथा
			deliver_event(item, data);
	पूर्ण
पूर्ण

अटल पूर्णांक devx_event_notअगरier(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ event_type, व्योम *data)
अणु
	काष्ठा mlx5_devx_event_table *table;
	काष्ठा mlx5_ib_dev *dev;
	काष्ठा devx_event *event;
	काष्ठा devx_obj_event *obj_event;
	u16 obj_type = 0;
	bool is_unaffiliated;
	u32 obj_id;

	/* Explicit filtering to kernel events which may occur frequently */
	अगर (event_type == MLX5_EVENT_TYPE_CMD ||
	    event_type == MLX5_EVENT_TYPE_PAGE_REQUEST)
		वापस NOTIFY_OK;

	table = container_of(nb, काष्ठा mlx5_devx_event_table, devx_nb.nb);
	dev = container_of(table, काष्ठा mlx5_ib_dev, devx_event_table);
	is_unaffiliated = is_unaffiliated_event(dev->mdev, event_type);

	अगर (!is_unaffiliated)
		obj_type = get_event_obj_type(event_type, data);

	rcu_पढ़ो_lock();
	event = xa_load(&table->event_xa, event_type | (obj_type << 16));
	अगर (!event) अणु
		rcu_पढ़ो_unlock();
		वापस NOTIFY_DONE;
	पूर्ण

	अगर (is_unaffiliated) अणु
		dispatch_event_fd(&event->unaffiliated_list, data);
		rcu_पढ़ो_unlock();
		वापस NOTIFY_OK;
	पूर्ण

	obj_id = devx_get_obj_id_from_event(event_type, data);
	obj_event = xa_load(&event->object_ids, obj_id);
	अगर (!obj_event) अणु
		rcu_पढ़ो_unlock();
		वापस NOTIFY_DONE;
	पूर्ण

	dispatch_event_fd(&obj_event->obj_sub_list, data);

	rcu_पढ़ो_unlock();
	वापस NOTIFY_OK;
पूर्ण

पूर्णांक mlx5_ib_devx_init(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा mlx5_devx_event_table *table = &dev->devx_event_table;
	पूर्णांक uid;

	uid = mlx5_ib_devx_create(dev, false);
	अगर (uid > 0) अणु
		dev->devx_whitelist_uid = uid;
		xa_init(&table->event_xa);
		mutex_init(&table->event_xa_lock);
		MLX5_NB_INIT(&table->devx_nb, devx_event_notअगरier, NOTIFY_ANY);
		mlx5_eq_notअगरier_रेजिस्टर(dev->mdev, &table->devx_nb);
	पूर्ण

	वापस 0;
पूर्ण

व्योम mlx5_ib_devx_cleanup(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा mlx5_devx_event_table *table = &dev->devx_event_table;
	काष्ठा devx_event_subscription *sub, *पंचांगp;
	काष्ठा devx_event *event;
	व्योम *entry;
	अचिन्हित दीर्घ id;

	अगर (dev->devx_whitelist_uid) अणु
		mlx5_eq_notअगरier_unरेजिस्टर(dev->mdev, &table->devx_nb);
		mutex_lock(&dev->devx_event_table.event_xa_lock);
		xa_क्रम_each(&table->event_xa, id, entry) अणु
			event = entry;
			list_क्रम_each_entry_safe(
				sub, पंचांगp, &event->unaffiliated_list, xa_list)
				devx_cleanup_subscription(dev, sub);
			kमुक्त(entry);
		पूर्ण
		mutex_unlock(&dev->devx_event_table.event_xa_lock);
		xa_destroy(&table->event_xa);

		mlx5_ib_devx_destroy(dev, dev->devx_whitelist_uid);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार devx_async_cmd_event_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
					 माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा devx_async_cmd_event_file *comp_ev_file = filp->निजी_data;
	काष्ठा devx_async_event_queue *ev_queue = &comp_ev_file->ev_queue;
	काष्ठा devx_async_data *event;
	पूर्णांक ret = 0;
	माप_प्रकार eventsz;

	spin_lock_irq(&ev_queue->lock);

	जबतक (list_empty(&ev_queue->event_list)) अणु
		spin_unlock_irq(&ev_queue->lock);

		अगर (filp->f_flags & O_NONBLOCK)
			वापस -EAGAIN;

		अगर (रुको_event_पूर्णांकerruptible(
			    ev_queue->poll_रुको,
			    (!list_empty(&ev_queue->event_list) ||
			     ev_queue->is_destroyed))) अणु
			वापस -ERESTARTSYS;
		पूर्ण

		spin_lock_irq(&ev_queue->lock);
		अगर (ev_queue->is_destroyed) अणु
			spin_unlock_irq(&ev_queue->lock);
			वापस -EIO;
		पूर्ण
	पूर्ण

	event = list_entry(ev_queue->event_list.next,
			   काष्ठा devx_async_data, list);
	eventsz = event->cmd_out_len +
			माप(काष्ठा mlx5_ib_uapi_devx_async_cmd_hdr);

	अगर (eventsz > count) अणु
		spin_unlock_irq(&ev_queue->lock);
		वापस -ENOSPC;
	पूर्ण

	list_del(ev_queue->event_list.next);
	spin_unlock_irq(&ev_queue->lock);

	अगर (copy_to_user(buf, &event->hdr, eventsz))
		ret = -EFAULT;
	अन्यथा
		ret = eventsz;

	atomic_sub(event->cmd_out_len, &ev_queue->bytes_in_use);
	kvमुक्त(event);
	वापस ret;
पूर्ण

अटल __poll_t devx_async_cmd_event_poll(काष्ठा file *filp,
					      काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा devx_async_cmd_event_file *comp_ev_file = filp->निजी_data;
	काष्ठा devx_async_event_queue *ev_queue = &comp_ev_file->ev_queue;
	__poll_t pollflags = 0;

	poll_रुको(filp, &ev_queue->poll_रुको, रुको);

	spin_lock_irq(&ev_queue->lock);
	अगर (ev_queue->is_destroyed)
		pollflags = EPOLLIN | EPOLLRDNORM | EPOLLRDHUP;
	अन्यथा अगर (!list_empty(&ev_queue->event_list))
		pollflags = EPOLLIN | EPOLLRDNORM;
	spin_unlock_irq(&ev_queue->lock);

	वापस pollflags;
पूर्ण

अटल स्थिर काष्ठा file_operations devx_async_cmd_event_fops = अणु
	.owner	 = THIS_MODULE,
	.पढ़ो	 = devx_async_cmd_event_पढ़ो,
	.poll    = devx_async_cmd_event_poll,
	.release = uverbs_uobject_fd_release,
	.llseek	 = no_llseek,
पूर्ण;

अटल sमाप_प्रकार devx_async_event_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
				     माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा devx_async_event_file *ev_file = filp->निजी_data;
	काष्ठा devx_event_subscription *event_sub;
	काष्ठा devx_async_event_data *event;
	पूर्णांक ret = 0;
	माप_प्रकार eventsz;
	bool omit_data;
	व्योम *event_data;

	omit_data = ev_file->omit_data;

	spin_lock_irq(&ev_file->lock);

	अगर (ev_file->is_overflow_err) अणु
		ev_file->is_overflow_err = 0;
		spin_unlock_irq(&ev_file->lock);
		वापस -EOVERFLOW;
	पूर्ण


	जबतक (list_empty(&ev_file->event_list)) अणु
		spin_unlock_irq(&ev_file->lock);

		अगर (filp->f_flags & O_NONBLOCK)
			वापस -EAGAIN;

		अगर (रुको_event_पूर्णांकerruptible(ev_file->poll_रुको,
			    (!list_empty(&ev_file->event_list) ||
			     ev_file->is_destroyed))) अणु
			वापस -ERESTARTSYS;
		पूर्ण

		spin_lock_irq(&ev_file->lock);
		अगर (ev_file->is_destroyed) अणु
			spin_unlock_irq(&ev_file->lock);
			वापस -EIO;
		पूर्ण
	पूर्ण

	अगर (omit_data) अणु
		event_sub = list_first_entry(&ev_file->event_list,
					काष्ठा devx_event_subscription,
					event_list);
		eventsz = माप(event_sub->cookie);
		event_data = &event_sub->cookie;
	पूर्ण अन्यथा अणु
		event = list_first_entry(&ev_file->event_list,
				      काष्ठा devx_async_event_data, list);
		eventsz = माप(काष्ठा mlx5_eqe) +
			माप(काष्ठा mlx5_ib_uapi_devx_async_event_hdr);
		event_data = &event->hdr;
	पूर्ण

	अगर (eventsz > count) अणु
		spin_unlock_irq(&ev_file->lock);
		वापस -EINVAL;
	पूर्ण

	अगर (omit_data)
		list_del_init(&event_sub->event_list);
	अन्यथा
		list_del(&event->list);

	spin_unlock_irq(&ev_file->lock);

	अगर (copy_to_user(buf, event_data, eventsz))
		/* This poपूर्णांकs to an application issue, not a kernel concern */
		ret = -EFAULT;
	अन्यथा
		ret = eventsz;

	अगर (!omit_data)
		kमुक्त(event);
	वापस ret;
पूर्ण

अटल __poll_t devx_async_event_poll(काष्ठा file *filp,
				      काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा devx_async_event_file *ev_file = filp->निजी_data;
	__poll_t pollflags = 0;

	poll_रुको(filp, &ev_file->poll_रुको, रुको);

	spin_lock_irq(&ev_file->lock);
	अगर (ev_file->is_destroyed)
		pollflags = EPOLLIN | EPOLLRDNORM | EPOLLRDHUP;
	अन्यथा अगर (!list_empty(&ev_file->event_list))
		pollflags = EPOLLIN | EPOLLRDNORM;
	spin_unlock_irq(&ev_file->lock);

	वापस pollflags;
पूर्ण

अटल व्योम devx_मुक्त_subscription(काष्ठा rcu_head *rcu)
अणु
	काष्ठा devx_event_subscription *event_sub =
		container_of(rcu, काष्ठा devx_event_subscription, rcu);

	अगर (event_sub->eventfd)
		eventfd_ctx_put(event_sub->eventfd);
	uverbs_uobject_put(&event_sub->ev_file->uobj);
	kमुक्त(event_sub);
पूर्ण

अटल स्थिर काष्ठा file_operations devx_async_event_fops = अणु
	.owner	 = THIS_MODULE,
	.पढ़ो	 = devx_async_event_पढ़ो,
	.poll    = devx_async_event_poll,
	.release = uverbs_uobject_fd_release,
	.llseek	 = no_llseek,
पूर्ण;

अटल व्योम devx_async_cmd_event_destroy_uobj(काष्ठा ib_uobject *uobj,
					      क्रमागत rdma_हटाओ_reason why)
अणु
	काष्ठा devx_async_cmd_event_file *comp_ev_file =
		container_of(uobj, काष्ठा devx_async_cmd_event_file,
			     uobj);
	काष्ठा devx_async_event_queue *ev_queue = &comp_ev_file->ev_queue;
	काष्ठा devx_async_data *entry, *पंचांगp;

	spin_lock_irq(&ev_queue->lock);
	ev_queue->is_destroyed = 1;
	spin_unlock_irq(&ev_queue->lock);
	wake_up_पूर्णांकerruptible(&ev_queue->poll_रुको);

	mlx5_cmd_cleanup_async_ctx(&comp_ev_file->async_ctx);

	spin_lock_irq(&comp_ev_file->ev_queue.lock);
	list_क्रम_each_entry_safe(entry, पंचांगp,
				 &comp_ev_file->ev_queue.event_list, list) अणु
		list_del(&entry->list);
		kvमुक्त(entry);
	पूर्ण
	spin_unlock_irq(&comp_ev_file->ev_queue.lock);
पूर्ण;

अटल व्योम devx_async_event_destroy_uobj(काष्ठा ib_uobject *uobj,
					  क्रमागत rdma_हटाओ_reason why)
अणु
	काष्ठा devx_async_event_file *ev_file =
		container_of(uobj, काष्ठा devx_async_event_file,
			     uobj);
	काष्ठा devx_event_subscription *event_sub, *event_sub_पंचांगp;
	काष्ठा mlx5_ib_dev *dev = ev_file->dev;

	spin_lock_irq(&ev_file->lock);
	ev_file->is_destroyed = 1;

	/* मुक्त the pending events allocation */
	अगर (ev_file->omit_data) अणु
		काष्ठा devx_event_subscription *event_sub, *पंचांगp;

		list_क्रम_each_entry_safe(event_sub, पंचांगp, &ev_file->event_list,
					 event_list)
			list_del_init(&event_sub->event_list);

	पूर्ण अन्यथा अणु
		काष्ठा devx_async_event_data *entry, *पंचांगp;

		list_क्रम_each_entry_safe(entry, पंचांगp, &ev_file->event_list,
					 list) अणु
			list_del(&entry->list);
			kमुक्त(entry);
		पूर्ण
	पूर्ण

	spin_unlock_irq(&ev_file->lock);
	wake_up_पूर्णांकerruptible(&ev_file->poll_रुको);

	mutex_lock(&dev->devx_event_table.event_xa_lock);
	/* delete the subscriptions which are related to this FD */
	list_क्रम_each_entry_safe(event_sub, event_sub_पंचांगp,
				 &ev_file->subscribed_events_list, file_list) अणु
		devx_cleanup_subscription(dev, event_sub);
		list_del_rcu(&event_sub->file_list);
		/* subscription may not be used by the पढ़ो API any more */
		call_rcu(&event_sub->rcu, devx_मुक्त_subscription);
	पूर्ण
	mutex_unlock(&dev->devx_event_table.event_xa_lock);

	put_device(&dev->ib_dev.dev);
पूर्ण;

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_DEVX_UMEM_REG,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_DEVX_UMEM_REG_HANDLE,
			MLX5_IB_OBJECT_DEVX_UMEM,
			UVERBS_ACCESS_NEW,
			UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(MLX5_IB_ATTR_DEVX_UMEM_REG_ADDR,
			   UVERBS_ATTR_TYPE(u64),
			   UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(MLX5_IB_ATTR_DEVX_UMEM_REG_LEN,
			   UVERBS_ATTR_TYPE(u64),
			   UA_MANDATORY),
	UVERBS_ATTR_FLAGS_IN(MLX5_IB_ATTR_DEVX_UMEM_REG_ACCESS,
			     क्रमागत ib_access_flags),
	UVERBS_ATTR_CONST_IN(MLX5_IB_ATTR_DEVX_UMEM_REG_PGSZ_BITMAP,
			     u64),
	UVERBS_ATTR_PTR_OUT(MLX5_IB_ATTR_DEVX_UMEM_REG_OUT_ID,
			    UVERBS_ATTR_TYPE(u32),
			    UA_MANDATORY));

DECLARE_UVERBS_NAMED_METHOD_DESTROY(
	MLX5_IB_METHOD_DEVX_UMEM_DEREG,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_DEVX_UMEM_DEREG_HANDLE,
			MLX5_IB_OBJECT_DEVX_UMEM,
			UVERBS_ACCESS_DESTROY,
			UA_MANDATORY));

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_DEVX_QUERY_EQN,
	UVERBS_ATTR_PTR_IN(MLX5_IB_ATTR_DEVX_QUERY_EQN_USER_VEC,
			   UVERBS_ATTR_TYPE(u32),
			   UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(MLX5_IB_ATTR_DEVX_QUERY_EQN_DEV_EQN,
			    UVERBS_ATTR_TYPE(u32),
			    UA_MANDATORY));

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_DEVX_QUERY_UAR,
	UVERBS_ATTR_PTR_IN(MLX5_IB_ATTR_DEVX_QUERY_UAR_USER_IDX,
			   UVERBS_ATTR_TYPE(u32),
			   UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(MLX5_IB_ATTR_DEVX_QUERY_UAR_DEV_IDX,
			    UVERBS_ATTR_TYPE(u32),
			    UA_MANDATORY));

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_DEVX_OTHER,
	UVERBS_ATTR_PTR_IN(
		MLX5_IB_ATTR_DEVX_OTHER_CMD_IN,
		UVERBS_ATTR_MIN_SIZE(MLX5_ST_SZ_BYTES(general_obj_in_cmd_hdr)),
		UA_MANDATORY,
		UA_ALLOC_AND_COPY),
	UVERBS_ATTR_PTR_OUT(
		MLX5_IB_ATTR_DEVX_OTHER_CMD_OUT,
		UVERBS_ATTR_MIN_SIZE(MLX5_ST_SZ_BYTES(general_obj_out_cmd_hdr)),
		UA_MANDATORY));

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_DEVX_OBJ_CREATE,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_DEVX_OBJ_CREATE_HANDLE,
			MLX5_IB_OBJECT_DEVX_OBJ,
			UVERBS_ACCESS_NEW,
			UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(
		MLX5_IB_ATTR_DEVX_OBJ_CREATE_CMD_IN,
		UVERBS_ATTR_MIN_SIZE(MLX5_ST_SZ_BYTES(general_obj_in_cmd_hdr)),
		UA_MANDATORY,
		UA_ALLOC_AND_COPY),
	UVERBS_ATTR_PTR_OUT(
		MLX5_IB_ATTR_DEVX_OBJ_CREATE_CMD_OUT,
		UVERBS_ATTR_MIN_SIZE(MLX5_ST_SZ_BYTES(general_obj_out_cmd_hdr)),
		UA_MANDATORY));

DECLARE_UVERBS_NAMED_METHOD_DESTROY(
	MLX5_IB_METHOD_DEVX_OBJ_DESTROY,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_DEVX_OBJ_DESTROY_HANDLE,
			MLX5_IB_OBJECT_DEVX_OBJ,
			UVERBS_ACCESS_DESTROY,
			UA_MANDATORY));

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_DEVX_OBJ_MODIFY,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_DEVX_OBJ_MODIFY_HANDLE,
			UVERBS_IDR_ANY_OBJECT,
			UVERBS_ACCESS_WRITE,
			UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(
		MLX5_IB_ATTR_DEVX_OBJ_MODIFY_CMD_IN,
		UVERBS_ATTR_MIN_SIZE(MLX5_ST_SZ_BYTES(general_obj_in_cmd_hdr)),
		UA_MANDATORY,
		UA_ALLOC_AND_COPY),
	UVERBS_ATTR_PTR_OUT(
		MLX5_IB_ATTR_DEVX_OBJ_MODIFY_CMD_OUT,
		UVERBS_ATTR_MIN_SIZE(MLX5_ST_SZ_BYTES(general_obj_out_cmd_hdr)),
		UA_MANDATORY));

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_DEVX_OBJ_QUERY,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_DEVX_OBJ_QUERY_HANDLE,
			UVERBS_IDR_ANY_OBJECT,
			UVERBS_ACCESS_READ,
			UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(
		MLX5_IB_ATTR_DEVX_OBJ_QUERY_CMD_IN,
		UVERBS_ATTR_MIN_SIZE(MLX5_ST_SZ_BYTES(general_obj_in_cmd_hdr)),
		UA_MANDATORY,
		UA_ALLOC_AND_COPY),
	UVERBS_ATTR_PTR_OUT(
		MLX5_IB_ATTR_DEVX_OBJ_QUERY_CMD_OUT,
		UVERBS_ATTR_MIN_SIZE(MLX5_ST_SZ_BYTES(general_obj_out_cmd_hdr)),
		UA_MANDATORY));

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_DEVX_OBJ_ASYNC_QUERY,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_DEVX_OBJ_QUERY_HANDLE,
			UVERBS_IDR_ANY_OBJECT,
			UVERBS_ACCESS_READ,
			UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(
		MLX5_IB_ATTR_DEVX_OBJ_QUERY_CMD_IN,
		UVERBS_ATTR_MIN_SIZE(MLX5_ST_SZ_BYTES(general_obj_in_cmd_hdr)),
		UA_MANDATORY,
		UA_ALLOC_AND_COPY),
	UVERBS_ATTR_CONST_IN(MLX5_IB_ATTR_DEVX_OBJ_QUERY_ASYNC_OUT_LEN,
		u16, UA_MANDATORY),
	UVERBS_ATTR_FD(MLX5_IB_ATTR_DEVX_OBJ_QUERY_ASYNC_FD,
		MLX5_IB_OBJECT_DEVX_ASYNC_CMD_FD,
		UVERBS_ACCESS_READ,
		UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(MLX5_IB_ATTR_DEVX_OBJ_QUERY_ASYNC_WR_ID,
		UVERBS_ATTR_TYPE(u64),
		UA_MANDATORY));

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_DEVX_SUBSCRIBE_EVENT,
	UVERBS_ATTR_FD(MLX5_IB_ATTR_DEVX_SUBSCRIBE_EVENT_FD_HANDLE,
		MLX5_IB_OBJECT_DEVX_ASYNC_EVENT_FD,
		UVERBS_ACCESS_READ,
		UA_MANDATORY),
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_DEVX_SUBSCRIBE_EVENT_OBJ_HANDLE,
		MLX5_IB_OBJECT_DEVX_OBJ,
		UVERBS_ACCESS_READ,
		UA_OPTIONAL),
	UVERBS_ATTR_PTR_IN(MLX5_IB_ATTR_DEVX_SUBSCRIBE_EVENT_TYPE_NUM_LIST,
		UVERBS_ATTR_MIN_SIZE(माप(u16)),
		UA_MANDATORY,
		UA_ALLOC_AND_COPY),
	UVERBS_ATTR_PTR_IN(MLX5_IB_ATTR_DEVX_SUBSCRIBE_EVENT_COOKIE,
		UVERBS_ATTR_TYPE(u64),
		UA_OPTIONAL),
	UVERBS_ATTR_PTR_IN(MLX5_IB_ATTR_DEVX_SUBSCRIBE_EVENT_FD_NUM,
		UVERBS_ATTR_TYPE(u32),
		UA_OPTIONAL));

DECLARE_UVERBS_GLOBAL_METHODS(MLX5_IB_OBJECT_DEVX,
			      &UVERBS_METHOD(MLX5_IB_METHOD_DEVX_OTHER),
			      &UVERBS_METHOD(MLX5_IB_METHOD_DEVX_QUERY_UAR),
			      &UVERBS_METHOD(MLX5_IB_METHOD_DEVX_QUERY_EQN),
			      &UVERBS_METHOD(MLX5_IB_METHOD_DEVX_SUBSCRIBE_EVENT));

DECLARE_UVERBS_NAMED_OBJECT(MLX5_IB_OBJECT_DEVX_OBJ,
			    UVERBS_TYPE_ALLOC_IDR(devx_obj_cleanup),
			    &UVERBS_METHOD(MLX5_IB_METHOD_DEVX_OBJ_CREATE),
			    &UVERBS_METHOD(MLX5_IB_METHOD_DEVX_OBJ_DESTROY),
			    &UVERBS_METHOD(MLX5_IB_METHOD_DEVX_OBJ_MODIFY),
			    &UVERBS_METHOD(MLX5_IB_METHOD_DEVX_OBJ_QUERY),
			    &UVERBS_METHOD(MLX5_IB_METHOD_DEVX_OBJ_ASYNC_QUERY));

DECLARE_UVERBS_NAMED_OBJECT(MLX5_IB_OBJECT_DEVX_UMEM,
			    UVERBS_TYPE_ALLOC_IDR(devx_umem_cleanup),
			    &UVERBS_METHOD(MLX5_IB_METHOD_DEVX_UMEM_REG),
			    &UVERBS_METHOD(MLX5_IB_METHOD_DEVX_UMEM_DEREG));


DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_DEVX_ASYNC_CMD_FD_ALLOC,
	UVERBS_ATTR_FD(MLX5_IB_ATTR_DEVX_ASYNC_CMD_FD_ALLOC_HANDLE,
			MLX5_IB_OBJECT_DEVX_ASYNC_CMD_FD,
			UVERBS_ACCESS_NEW,
			UA_MANDATORY));

DECLARE_UVERBS_NAMED_OBJECT(
	MLX5_IB_OBJECT_DEVX_ASYNC_CMD_FD,
	UVERBS_TYPE_ALLOC_FD(माप(काष्ठा devx_async_cmd_event_file),
			     devx_async_cmd_event_destroy_uobj,
			     &devx_async_cmd_event_fops, "[devx_async_cmd]",
			     O_RDONLY),
	&UVERBS_METHOD(MLX5_IB_METHOD_DEVX_ASYNC_CMD_FD_ALLOC));

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_DEVX_ASYNC_EVENT_FD_ALLOC,
	UVERBS_ATTR_FD(MLX5_IB_ATTR_DEVX_ASYNC_EVENT_FD_ALLOC_HANDLE,
			MLX5_IB_OBJECT_DEVX_ASYNC_EVENT_FD,
			UVERBS_ACCESS_NEW,
			UA_MANDATORY),
	UVERBS_ATTR_FLAGS_IN(MLX5_IB_ATTR_DEVX_ASYNC_EVENT_FD_ALLOC_FLAGS,
			क्रमागत mlx5_ib_uapi_devx_create_event_channel_flags,
			UA_MANDATORY));

DECLARE_UVERBS_NAMED_OBJECT(
	MLX5_IB_OBJECT_DEVX_ASYNC_EVENT_FD,
	UVERBS_TYPE_ALLOC_FD(माप(काष्ठा devx_async_event_file),
			     devx_async_event_destroy_uobj,
			     &devx_async_event_fops, "[devx_async_event]",
			     O_RDONLY),
	&UVERBS_METHOD(MLX5_IB_METHOD_DEVX_ASYNC_EVENT_FD_ALLOC));

अटल bool devx_is_supported(काष्ठा ib_device *device)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(device);

	वापस MLX5_CAP_GEN(dev->mdev, log_max_uctx);
पूर्ण

स्थिर काष्ठा uapi_definition mlx5_ib_devx_defs[] = अणु
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(
		MLX5_IB_OBJECT_DEVX,
		UAPI_DEF_IS_OBJ_SUPPORTED(devx_is_supported)),
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(
		MLX5_IB_OBJECT_DEVX_OBJ,
		UAPI_DEF_IS_OBJ_SUPPORTED(devx_is_supported)),
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(
		MLX5_IB_OBJECT_DEVX_UMEM,
		UAPI_DEF_IS_OBJ_SUPPORTED(devx_is_supported)),
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(
		MLX5_IB_OBJECT_DEVX_ASYNC_CMD_FD,
		UAPI_DEF_IS_OBJ_SUPPORTED(devx_is_supported)),
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(
		MLX5_IB_OBJECT_DEVX_ASYNC_EVENT_FD,
		UAPI_DEF_IS_OBJ_SUPPORTED(devx_is_supported)),
	अणुपूर्ण,
पूर्ण;
