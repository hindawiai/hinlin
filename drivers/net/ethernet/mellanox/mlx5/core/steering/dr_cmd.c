<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश "dr_types.h"

पूर्णांक mlx5dr_cmd_query_esw_vport_context(काष्ठा mlx5_core_dev *mdev,
				       bool other_vport,
				       u16 vport_number,
				       u64 *icm_address_rx,
				       u64 *icm_address_tx)
अणु
	u32 out[MLX5_ST_SZ_DW(query_esw_vport_context_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(query_esw_vport_context_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(query_esw_vport_context_in, in, opcode,
		 MLX5_CMD_OP_QUERY_ESW_VPORT_CONTEXT);
	MLX5_SET(query_esw_vport_context_in, in, other_vport, other_vport);
	MLX5_SET(query_esw_vport_context_in, in, vport_number, vport_number);

	err = mlx5_cmd_exec_inout(mdev, query_esw_vport_context, in, out);
	अगर (err)
		वापस err;

	*icm_address_rx =
		MLX5_GET64(query_esw_vport_context_out, out,
			   esw_vport_context.sw_steering_vport_icm_address_rx);
	*icm_address_tx =
		MLX5_GET64(query_esw_vport_context_out, out,
			   esw_vport_context.sw_steering_vport_icm_address_tx);
	वापस 0;
पूर्ण

पूर्णांक mlx5dr_cmd_query_gvmi(काष्ठा mlx5_core_dev *mdev, bool other_vport,
			  u16 vport_number, u16 *gvmi)
अणु
	u32 in[MLX5_ST_SZ_DW(query_hca_cap_in)] = अणुपूर्ण;
	पूर्णांक out_size;
	व्योम *out;
	पूर्णांक err;

	out_size = MLX5_ST_SZ_BYTES(query_hca_cap_out);
	out = kzalloc(out_size, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	MLX5_SET(query_hca_cap_in, in, opcode, MLX5_CMD_OP_QUERY_HCA_CAP);
	MLX5_SET(query_hca_cap_in, in, other_function, other_vport);
	MLX5_SET(query_hca_cap_in, in, function_id, vport_number);
	MLX5_SET(query_hca_cap_in, in, op_mod,
		 MLX5_SET_HCA_CAP_OP_MOD_GENERAL_DEVICE << 1 |
		 HCA_CAP_OPMOD_GET_CUR);

	err = mlx5_cmd_exec_inout(mdev, query_hca_cap, in, out);
	अगर (err) अणु
		kमुक्त(out);
		वापस err;
	पूर्ण

	*gvmi = MLX5_GET(query_hca_cap_out, out, capability.cmd_hca_cap.vhca_id);

	kमुक्त(out);
	वापस 0;
पूर्ण

पूर्णांक mlx5dr_cmd_query_esw_caps(काष्ठा mlx5_core_dev *mdev,
			      काष्ठा mlx5dr_esw_caps *caps)
अणु
	caps->drop_icm_address_rx =
		MLX5_CAP64_ESW_FLOWTABLE(mdev,
					 sw_steering_fdb_action_drop_icm_address_rx);
	caps->drop_icm_address_tx =
		MLX5_CAP64_ESW_FLOWTABLE(mdev,
					 sw_steering_fdb_action_drop_icm_address_tx);
	caps->uplink_icm_address_rx =
		MLX5_CAP64_ESW_FLOWTABLE(mdev,
					 sw_steering_uplink_icm_address_rx);
	caps->uplink_icm_address_tx =
		MLX5_CAP64_ESW_FLOWTABLE(mdev,
					 sw_steering_uplink_icm_address_tx);
	caps->sw_owner_v2 = MLX5_CAP_ESW_FLOWTABLE_FDB(mdev, sw_owner_v2);
	अगर (!caps->sw_owner_v2)
		caps->sw_owner = MLX5_CAP_ESW_FLOWTABLE_FDB(mdev, sw_owner);

	वापस 0;
पूर्ण

अटल पूर्णांक dr_cmd_query_nic_vport_roce_en(काष्ठा mlx5_core_dev *mdev,
					  u16 vport, bool *roce_en)
अणु
	u32 out[MLX5_ST_SZ_DW(query_nic_vport_context_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(query_nic_vport_context_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(query_nic_vport_context_in, in, opcode,
		 MLX5_CMD_OP_QUERY_NIC_VPORT_CONTEXT);
	MLX5_SET(query_nic_vport_context_in, in, vport_number, vport);
	MLX5_SET(query_nic_vport_context_in, in, other_vport, !!vport);

	err = mlx5_cmd_exec(mdev, in, माप(in), out, माप(out));
	अगर (err)
		वापस err;

	*roce_en = MLX5_GET(query_nic_vport_context_out, out,
			    nic_vport_context.roce_en);
	वापस 0;
पूर्ण

पूर्णांक mlx5dr_cmd_query_device(काष्ठा mlx5_core_dev *mdev,
			    काष्ठा mlx5dr_cmd_caps *caps)
अणु
	bool roce_en;
	पूर्णांक err;

	caps->prio_tag_required	= MLX5_CAP_GEN(mdev, prio_tag_required);
	caps->eचयन_manager	= MLX5_CAP_GEN(mdev, eचयन_manager);
	caps->gvmi		= MLX5_CAP_GEN(mdev, vhca_id);
	caps->flex_protocols	= MLX5_CAP_GEN(mdev, flex_parser_protocols);
	caps->sw_क्रमmat_ver	= MLX5_CAP_GEN(mdev, steering_क्रमmat_version);

	अगर (MLX5_CAP_GEN(mdev, roce)) अणु
		err = dr_cmd_query_nic_vport_roce_en(mdev, 0, &roce_en);
		अगर (err)
			वापस err;

		caps->roce_caps.roce_en = roce_en;
		caps->roce_caps.fl_rc_qp_when_roce_disabled =
			MLX5_CAP_ROCE(mdev, fl_rc_qp_when_roce_disabled);
		caps->roce_caps.fl_rc_qp_when_roce_enabled =
			MLX5_CAP_ROCE(mdev, fl_rc_qp_when_roce_enabled);
	पूर्ण

	caps->isolate_vl_tc = MLX5_CAP_GEN(mdev, isolate_vl_tc_new);

	अगर (caps->flex_protocols & MLX5_FLEX_PARSER_ICMP_V4_ENABLED) अणु
		caps->flex_parser_id_icmp_dw0 = MLX5_CAP_GEN(mdev, flex_parser_id_icmp_dw0);
		caps->flex_parser_id_icmp_dw1 = MLX5_CAP_GEN(mdev, flex_parser_id_icmp_dw1);
	पूर्ण

	अगर (caps->flex_protocols & MLX5_FLEX_PARSER_ICMP_V6_ENABLED) अणु
		caps->flex_parser_id_icmpv6_dw0 =
			MLX5_CAP_GEN(mdev, flex_parser_id_icmpv6_dw0);
		caps->flex_parser_id_icmpv6_dw1 =
			MLX5_CAP_GEN(mdev, flex_parser_id_icmpv6_dw1);
	पूर्ण

	अगर (caps->flex_protocols & MLX5_FLEX_PARSER_GENEVE_TLV_OPTION_0_ENABLED)
		caps->flex_parser_id_geneve_tlv_option_0 =
			MLX5_CAP_GEN(mdev, flex_parser_id_geneve_tlv_option_0);

	अगर (caps->flex_protocols & MLX5_FLEX_PARSER_MPLS_OVER_GRE_ENABLED)
		caps->flex_parser_id_mpls_over_gre =
			MLX5_CAP_GEN(mdev, flex_parser_id_outer_first_mpls_over_gre);

	अगर (caps->flex_protocols & mlx5_FLEX_PARSER_MPLS_OVER_UDP_ENABLED)
		caps->flex_parser_id_mpls_over_udp =
			MLX5_CAP_GEN(mdev, flex_parser_id_outer_first_mpls_over_udp_label);

	अगर (caps->flex_protocols & MLX5_FLEX_PARSER_GTPU_DW_0_ENABLED)
		caps->flex_parser_id_gtpu_dw_0 =
			MLX5_CAP_GEN(mdev, flex_parser_id_gtpu_dw_0);

	अगर (caps->flex_protocols & MLX5_FLEX_PARSER_GTPU_TEID_ENABLED)
		caps->flex_parser_id_gtpu_teid =
			MLX5_CAP_GEN(mdev, flex_parser_id_gtpu_teid);

	अगर (caps->flex_protocols & MLX5_FLEX_PARSER_GTPU_DW_2_ENABLED)
		caps->flex_parser_id_gtpu_dw_2 =
			MLX5_CAP_GEN(mdev, flex_parser_id_gtpu_dw_2);

	अगर (caps->flex_protocols & MLX5_FLEX_PARSER_GTPU_FIRST_EXT_DW_0_ENABLED)
		caps->flex_parser_id_gtpu_first_ext_dw_0 =
			MLX5_CAP_GEN(mdev, flex_parser_id_gtpu_first_ext_dw_0);

	caps->nic_rx_drop_address =
		MLX5_CAP64_FLOWTABLE(mdev, sw_steering_nic_rx_action_drop_icm_address);
	caps->nic_tx_drop_address =
		MLX5_CAP64_FLOWTABLE(mdev, sw_steering_nic_tx_action_drop_icm_address);
	caps->nic_tx_allow_address =
		MLX5_CAP64_FLOWTABLE(mdev, sw_steering_nic_tx_action_allow_icm_address);

	caps->rx_sw_owner_v2 = MLX5_CAP_FLOWTABLE_NIC_RX(mdev, sw_owner_v2);
	caps->tx_sw_owner_v2 = MLX5_CAP_FLOWTABLE_NIC_TX(mdev, sw_owner_v2);

	अगर (!caps->rx_sw_owner_v2)
		caps->rx_sw_owner = MLX5_CAP_FLOWTABLE_NIC_RX(mdev, sw_owner);
	अगर (!caps->tx_sw_owner_v2)
		caps->tx_sw_owner = MLX5_CAP_FLOWTABLE_NIC_TX(mdev, sw_owner);

	caps->max_ft_level = MLX5_CAP_FLOWTABLE_NIC_RX(mdev, max_ft_level);

	caps->log_icm_size = MLX5_CAP_DEV_MEM(mdev, log_steering_sw_icm_size);
	caps->hdr_modअगरy_icm_addr =
		MLX5_CAP64_DEV_MEM(mdev, header_modअगरy_sw_icm_start_address);

	caps->roce_min_src_udp = MLX5_CAP_ROCE(mdev, r_roce_min_src_udp_port);

	वापस 0;
पूर्ण

पूर्णांक mlx5dr_cmd_query_flow_table(काष्ठा mlx5_core_dev *dev,
				क्रमागत fs_flow_table_type type,
				u32 table_id,
				काष्ठा mlx5dr_cmd_query_flow_table_details *output)
अणु
	u32 out[MLX5_ST_SZ_DW(query_flow_table_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(query_flow_table_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(query_flow_table_in, in, opcode,
		 MLX5_CMD_OP_QUERY_FLOW_TABLE);

	MLX5_SET(query_flow_table_in, in, table_type, type);
	MLX5_SET(query_flow_table_in, in, table_id, table_id);

	err = mlx5_cmd_exec_inout(dev, query_flow_table, in, out);
	अगर (err)
		वापस err;

	output->status = MLX5_GET(query_flow_table_out, out, status);
	output->level = MLX5_GET(query_flow_table_out, out, flow_table_context.level);

	output->sw_owner_icm_root_1 = MLX5_GET64(query_flow_table_out, out,
						 flow_table_context.sw_owner_icm_root_1);
	output->sw_owner_icm_root_0 = MLX5_GET64(query_flow_table_out, out,
						 flow_table_context.sw_owner_icm_root_0);

	वापस 0;
पूर्ण

पूर्णांक mlx5dr_cmd_sync_steering(काष्ठा mlx5_core_dev *mdev)
अणु
	u32 in[MLX5_ST_SZ_DW(sync_steering_in)] = अणुपूर्ण;

	MLX5_SET(sync_steering_in, in, opcode, MLX5_CMD_OP_SYNC_STEERING);

	वापस mlx5_cmd_exec_in(mdev, sync_steering, in);
पूर्ण

पूर्णांक mlx5dr_cmd_set_fte_modअगरy_and_vport(काष्ठा mlx5_core_dev *mdev,
					u32 table_type,
					u32 table_id,
					u32 group_id,
					u32 modअगरy_header_id,
					u32 vport_id)
अणु
	u32 out[MLX5_ST_SZ_DW(set_fte_out)] = अणुपूर्ण;
	व्योम *in_flow_context;
	अचिन्हित पूर्णांक inlen;
	व्योम *in_dests;
	u32 *in;
	पूर्णांक err;

	inlen = MLX5_ST_SZ_BYTES(set_fte_in) +
		1 * MLX5_ST_SZ_BYTES(dest_क्रमmat_काष्ठा); /* One destination only */

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(set_fte_in, in, opcode, MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY);
	MLX5_SET(set_fte_in, in, table_type, table_type);
	MLX5_SET(set_fte_in, in, table_id, table_id);

	in_flow_context = MLX5_ADDR_OF(set_fte_in, in, flow_context);
	MLX5_SET(flow_context, in_flow_context, group_id, group_id);
	MLX5_SET(flow_context, in_flow_context, modअगरy_header_id, modअगरy_header_id);
	MLX5_SET(flow_context, in_flow_context, destination_list_size, 1);
	MLX5_SET(flow_context, in_flow_context, action,
		 MLX5_FLOW_CONTEXT_ACTION_FWD_DEST |
		 MLX5_FLOW_CONTEXT_ACTION_MOD_HDR);

	in_dests = MLX5_ADDR_OF(flow_context, in_flow_context, destination);
	MLX5_SET(dest_क्रमmat_काष्ठा, in_dests, destination_type,
		 MLX5_FLOW_DESTINATION_TYPE_VPORT);
	MLX5_SET(dest_क्रमmat_काष्ठा, in_dests, destination_id, vport_id);

	err = mlx5_cmd_exec(mdev, in, inlen, out, माप(out));
	kvमुक्त(in);

	वापस err;
पूर्ण

पूर्णांक mlx5dr_cmd_del_flow_table_entry(काष्ठा mlx5_core_dev *mdev,
				    u32 table_type,
				    u32 table_id)
अणु
	u32 in[MLX5_ST_SZ_DW(delete_fte_in)] = अणुपूर्ण;

	MLX5_SET(delete_fte_in, in, opcode, MLX5_CMD_OP_DELETE_FLOW_TABLE_ENTRY);
	MLX5_SET(delete_fte_in, in, table_type, table_type);
	MLX5_SET(delete_fte_in, in, table_id, table_id);

	वापस mlx5_cmd_exec_in(mdev, delete_fte, in);
पूर्ण

पूर्णांक mlx5dr_cmd_alloc_modअगरy_header(काष्ठा mlx5_core_dev *mdev,
				   u32 table_type,
				   u8 num_of_actions,
				   u64 *actions,
				   u32 *modअगरy_header_id)
अणु
	u32 out[MLX5_ST_SZ_DW(alloc_modअगरy_header_context_out)] = अणुपूर्ण;
	व्योम *p_actions;
	u32 inlen;
	u32 *in;
	पूर्णांक err;

	inlen = MLX5_ST_SZ_BYTES(alloc_modअगरy_header_context_in) +
		 num_of_actions * माप(u64);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(alloc_modअगरy_header_context_in, in, opcode,
		 MLX5_CMD_OP_ALLOC_MODIFY_HEADER_CONTEXT);
	MLX5_SET(alloc_modअगरy_header_context_in, in, table_type, table_type);
	MLX5_SET(alloc_modअगरy_header_context_in, in, num_of_actions, num_of_actions);
	p_actions = MLX5_ADDR_OF(alloc_modअगरy_header_context_in, in, actions);
	स_नकल(p_actions, actions, num_of_actions * माप(u64));

	err = mlx5_cmd_exec(mdev, in, inlen, out, माप(out));
	अगर (err)
		जाओ out;

	*modअगरy_header_id = MLX5_GET(alloc_modअगरy_header_context_out, out,
				     modअगरy_header_id);
out:
	kvमुक्त(in);
	वापस err;
पूर्ण

पूर्णांक mlx5dr_cmd_dealloc_modअगरy_header(काष्ठा mlx5_core_dev *mdev,
				     u32 modअगरy_header_id)
अणु
	u32 in[MLX5_ST_SZ_DW(dealloc_modअगरy_header_context_in)] = अणुपूर्ण;

	MLX5_SET(dealloc_modअगरy_header_context_in, in, opcode,
		 MLX5_CMD_OP_DEALLOC_MODIFY_HEADER_CONTEXT);
	MLX5_SET(dealloc_modअगरy_header_context_in, in, modअगरy_header_id,
		 modअगरy_header_id);

	वापस mlx5_cmd_exec_in(mdev, dealloc_modअगरy_header_context, in);
पूर्ण

पूर्णांक mlx5dr_cmd_create_empty_flow_group(काष्ठा mlx5_core_dev *mdev,
				       u32 table_type,
				       u32 table_id,
				       u32 *group_id)
अणु
	u32 out[MLX5_ST_SZ_DW(create_flow_group_out)] = अणुपूर्ण;
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	u32 *in;
	पूर्णांक err;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(create_flow_group_in, in, opcode, MLX5_CMD_OP_CREATE_FLOW_GROUP);
	MLX5_SET(create_flow_group_in, in, table_type, table_type);
	MLX5_SET(create_flow_group_in, in, table_id, table_id);

	err = mlx5_cmd_exec_inout(mdev, create_flow_group, in, out);
	अगर (err)
		जाओ out;

	*group_id = MLX5_GET(create_flow_group_out, out, group_id);

out:
	kvमुक्त(in);
	वापस err;
पूर्ण

पूर्णांक mlx5dr_cmd_destroy_flow_group(काष्ठा mlx5_core_dev *mdev,
				  u32 table_type,
				  u32 table_id,
				  u32 group_id)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_flow_group_in)] = अणुपूर्ण;

	MLX5_SET(destroy_flow_group_in, in, opcode,
		 MLX5_CMD_OP_DESTROY_FLOW_GROUP);
	MLX5_SET(destroy_flow_group_in, in, table_type, table_type);
	MLX5_SET(destroy_flow_group_in, in, table_id, table_id);
	MLX5_SET(destroy_flow_group_in, in, group_id, group_id);

	वापस mlx5_cmd_exec_in(mdev, destroy_flow_group, in);
पूर्ण

पूर्णांक mlx5dr_cmd_create_flow_table(काष्ठा mlx5_core_dev *mdev,
				 काष्ठा mlx5dr_cmd_create_flow_table_attr *attr,
				 u64 *fdb_rx_icm_addr,
				 u32 *table_id)
अणु
	u32 out[MLX5_ST_SZ_DW(create_flow_table_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(create_flow_table_in)] = अणुपूर्ण;
	व्योम *ft_mdev;
	पूर्णांक err;

	MLX5_SET(create_flow_table_in, in, opcode, MLX5_CMD_OP_CREATE_FLOW_TABLE);
	MLX5_SET(create_flow_table_in, in, table_type, attr->table_type);

	ft_mdev = MLX5_ADDR_OF(create_flow_table_in, in, flow_table_context);
	MLX5_SET(flow_table_context, ft_mdev, termination_table, attr->term_tbl);
	MLX5_SET(flow_table_context, ft_mdev, sw_owner, attr->sw_owner);
	MLX5_SET(flow_table_context, ft_mdev, level, attr->level);

	अगर (attr->sw_owner) अणु
		/* icm_addr_0 used क्रम FDB RX / NIC TX / NIC_RX
		 * icm_addr_1 used क्रम FDB TX
		 */
		अगर (attr->table_type == MLX5_FLOW_TABLE_TYPE_NIC_RX) अणु
			MLX5_SET64(flow_table_context, ft_mdev,
				   sw_owner_icm_root_0, attr->icm_addr_rx);
		पूर्ण अन्यथा अगर (attr->table_type == MLX5_FLOW_TABLE_TYPE_NIC_TX) अणु
			MLX5_SET64(flow_table_context, ft_mdev,
				   sw_owner_icm_root_0, attr->icm_addr_tx);
		पूर्ण अन्यथा अगर (attr->table_type == MLX5_FLOW_TABLE_TYPE_FDB) अणु
			MLX5_SET64(flow_table_context, ft_mdev,
				   sw_owner_icm_root_0, attr->icm_addr_rx);
			MLX5_SET64(flow_table_context, ft_mdev,
				   sw_owner_icm_root_1, attr->icm_addr_tx);
		पूर्ण
	पूर्ण

	MLX5_SET(create_flow_table_in, in, flow_table_context.decap_en,
		 attr->decap_en);
	MLX5_SET(create_flow_table_in, in, flow_table_context.reक्रमmat_en,
		 attr->reक्रमmat_en);

	err = mlx5_cmd_exec_inout(mdev, create_flow_table, in, out);
	अगर (err)
		वापस err;

	*table_id = MLX5_GET(create_flow_table_out, out, table_id);
	अगर (!attr->sw_owner && attr->table_type == MLX5_FLOW_TABLE_TYPE_FDB &&
	    fdb_rx_icm_addr)
		*fdb_rx_icm_addr =
		(u64)MLX5_GET(create_flow_table_out, out, icm_address_31_0) |
		(u64)MLX5_GET(create_flow_table_out, out, icm_address_39_32) << 32 |
		(u64)MLX5_GET(create_flow_table_out, out, icm_address_63_40) << 40;

	वापस 0;
पूर्ण

पूर्णांक mlx5dr_cmd_destroy_flow_table(काष्ठा mlx5_core_dev *mdev,
				  u32 table_id,
				  u32 table_type)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_flow_table_in)] = अणुपूर्ण;

	MLX5_SET(destroy_flow_table_in, in, opcode,
		 MLX5_CMD_OP_DESTROY_FLOW_TABLE);
	MLX5_SET(destroy_flow_table_in, in, table_type, table_type);
	MLX5_SET(destroy_flow_table_in, in, table_id, table_id);

	वापस mlx5_cmd_exec_in(mdev, destroy_flow_table, in);
पूर्ण

पूर्णांक mlx5dr_cmd_create_reक्रमmat_ctx(काष्ठा mlx5_core_dev *mdev,
				   क्रमागत mlx5_reक्रमmat_ctx_type rt,
				   माप_प्रकार reक्रमmat_size,
				   व्योम *reक्रमmat_data,
				   u32 *reक्रमmat_id)
अणु
	u32 out[MLX5_ST_SZ_DW(alloc_packet_reक्रमmat_context_out)] = अणुपूर्ण;
	माप_प्रकार inlen, cmd_data_sz, cmd_total_sz;
	व्योम *prctx;
	व्योम *pdata;
	व्योम *in;
	पूर्णांक err;

	cmd_total_sz = MLX5_ST_SZ_BYTES(alloc_packet_reक्रमmat_context_in);
	cmd_data_sz = MLX5_FLD_SZ_BYTES(alloc_packet_reक्रमmat_context_in,
					packet_reक्रमmat_context.reक्रमmat_data);
	inlen = ALIGN(cmd_total_sz + reक्रमmat_size - cmd_data_sz, 4);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(alloc_packet_reक्रमmat_context_in, in, opcode,
		 MLX5_CMD_OP_ALLOC_PACKET_REFORMAT_CONTEXT);

	prctx = MLX5_ADDR_OF(alloc_packet_reक्रमmat_context_in, in, packet_reक्रमmat_context);
	pdata = MLX5_ADDR_OF(packet_reक्रमmat_context_in, prctx, reक्रमmat_data);

	MLX5_SET(packet_reक्रमmat_context_in, prctx, reक्रमmat_type, rt);
	MLX5_SET(packet_reक्रमmat_context_in, prctx, reक्रमmat_data_size, reक्रमmat_size);
	स_नकल(pdata, reक्रमmat_data, reक्रमmat_size);

	err = mlx5_cmd_exec(mdev, in, inlen, out, माप(out));
	अगर (err)
		वापस err;

	*reक्रमmat_id = MLX5_GET(alloc_packet_reक्रमmat_context_out, out, packet_reक्रमmat_id);
	kvमुक्त(in);

	वापस err;
पूर्ण

व्योम mlx5dr_cmd_destroy_reक्रमmat_ctx(काष्ठा mlx5_core_dev *mdev,
				     u32 reक्रमmat_id)
अणु
	u32 in[MLX5_ST_SZ_DW(dealloc_packet_reक्रमmat_context_in)] = अणुपूर्ण;

	MLX5_SET(dealloc_packet_reक्रमmat_context_in, in, opcode,
		 MLX5_CMD_OP_DEALLOC_PACKET_REFORMAT_CONTEXT);
	MLX5_SET(dealloc_packet_reक्रमmat_context_in, in, packet_reक्रमmat_id,
		 reक्रमmat_id);

	mlx5_cmd_exec_in(mdev, dealloc_packet_reक्रमmat_context, in);
पूर्ण

पूर्णांक mlx5dr_cmd_query_gid(काष्ठा mlx5_core_dev *mdev, u8 vhca_port_num,
			 u16 index, काष्ठा mlx5dr_cmd_gid_attr *attr)
अणु
	u32 out[MLX5_ST_SZ_DW(query_roce_address_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(query_roce_address_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(query_roce_address_in, in, opcode,
		 MLX5_CMD_OP_QUERY_ROCE_ADDRESS);

	MLX5_SET(query_roce_address_in, in, roce_address_index, index);
	MLX5_SET(query_roce_address_in, in, vhca_port_num, vhca_port_num);

	err = mlx5_cmd_exec_inout(mdev, query_roce_address, in, out);
	अगर (err)
		वापस err;

	स_नकल(&attr->gid,
	       MLX5_ADDR_OF(query_roce_address_out,
			    out, roce_address.source_l3_address),
	       माप(attr->gid));
	स_नकल(attr->mac,
	       MLX5_ADDR_OF(query_roce_address_out, out,
			    roce_address.source_mac_47_32),
	       माप(attr->mac));

	अगर (MLX5_GET(query_roce_address_out, out,
		     roce_address.roce_version) == MLX5_ROCE_VERSION_2)
		attr->roce_ver = MLX5_ROCE_VERSION_2;
	अन्यथा
		attr->roce_ver = MLX5_ROCE_VERSION_1;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5dr_cmd_set_extended_dest(काष्ठा mlx5_core_dev *dev,
					काष्ठा mlx5dr_cmd_fte_info *fte,
					bool *extended_dest)
अणु
	पूर्णांक fw_log_max_fdb_encap_uplink = MLX5_CAP_ESW(dev, log_max_fdb_encap_uplink);
	पूर्णांक num_fwd_destinations = 0;
	पूर्णांक num_encap = 0;
	पूर्णांक i;

	*extended_dest = false;
	अगर (!(fte->action.action & MLX5_FLOW_CONTEXT_ACTION_FWD_DEST))
		वापस 0;
	क्रम (i = 0; i < fte->dests_size; i++) अणु
		अगर (fte->dest_arr[i].type == MLX5_FLOW_DESTINATION_TYPE_COUNTER)
			जारी;
		अगर (fte->dest_arr[i].type == MLX5_FLOW_DESTINATION_TYPE_VPORT &&
		    fte->dest_arr[i].vport.flags & MLX5_FLOW_DEST_VPORT_REFORMAT_ID)
			num_encap++;
		num_fwd_destinations++;
	पूर्ण

	अगर (num_fwd_destinations > 1 && num_encap > 0)
		*extended_dest = true;

	अगर (*extended_dest && !fw_log_max_fdb_encap_uplink) अणु
		mlx5_core_warn(dev, "FW does not support extended destination");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (num_encap > (1 << fw_log_max_fdb_encap_uplink)) अणु
		mlx5_core_warn(dev, "FW does not support more than %d encaps",
			       1 << fw_log_max_fdb_encap_uplink);
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mlx5dr_cmd_set_fte(काष्ठा mlx5_core_dev *dev,
		       पूर्णांक opmod, पूर्णांक modअगरy_mask,
		       काष्ठा mlx5dr_cmd_ft_info *ft,
		       u32 group_id,
		       काष्ठा mlx5dr_cmd_fte_info *fte)
अणु
	u32 out[MLX5_ST_SZ_DW(set_fte_out)] = अणुपूर्ण;
	व्योम *in_flow_context, *vlan;
	bool extended_dest = false;
	व्योम *in_match_value;
	अचिन्हित पूर्णांक inlen;
	पूर्णांक dst_cnt_size;
	व्योम *in_dests;
	u32 *in;
	पूर्णांक err;
	पूर्णांक i;

	अगर (mlx5dr_cmd_set_extended_dest(dev, fte, &extended_dest))
		वापस -EOPNOTSUPP;

	अगर (!extended_dest)
		dst_cnt_size = MLX5_ST_SZ_BYTES(dest_क्रमmat_काष्ठा);
	अन्यथा
		dst_cnt_size = MLX5_ST_SZ_BYTES(extended_dest_क्रमmat);

	inlen = MLX5_ST_SZ_BYTES(set_fte_in) + fte->dests_size * dst_cnt_size;
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(set_fte_in, in, opcode, MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY);
	MLX5_SET(set_fte_in, in, op_mod, opmod);
	MLX5_SET(set_fte_in, in, modअगरy_enable_mask, modअगरy_mask);
	MLX5_SET(set_fte_in, in, table_type, ft->type);
	MLX5_SET(set_fte_in, in, table_id, ft->id);
	MLX5_SET(set_fte_in, in, flow_index, fte->index);
	अगर (ft->vport) अणु
		MLX5_SET(set_fte_in, in, vport_number, ft->vport);
		MLX5_SET(set_fte_in, in, other_vport, 1);
	पूर्ण

	in_flow_context = MLX5_ADDR_OF(set_fte_in, in, flow_context);
	MLX5_SET(flow_context, in_flow_context, group_id, group_id);

	MLX5_SET(flow_context, in_flow_context, flow_tag,
		 fte->flow_context.flow_tag);
	MLX5_SET(flow_context, in_flow_context, flow_source,
		 fte->flow_context.flow_source);

	MLX5_SET(flow_context, in_flow_context, extended_destination,
		 extended_dest);
	अगर (extended_dest) अणु
		u32 action;

		action = fte->action.action &
			~MLX5_FLOW_CONTEXT_ACTION_PACKET_REFORMAT;
		MLX5_SET(flow_context, in_flow_context, action, action);
	पूर्ण अन्यथा अणु
		MLX5_SET(flow_context, in_flow_context, action,
			 fte->action.action);
		अगर (fte->action.pkt_reक्रमmat)
			MLX5_SET(flow_context, in_flow_context, packet_reक्रमmat_id,
				 fte->action.pkt_reक्रमmat->id);
	पूर्ण
	अगर (fte->action.modअगरy_hdr)
		MLX5_SET(flow_context, in_flow_context, modअगरy_header_id,
			 fte->action.modअगरy_hdr->id);

	vlan = MLX5_ADDR_OF(flow_context, in_flow_context, push_vlan);

	MLX5_SET(vlan, vlan, ethtype, fte->action.vlan[0].ethtype);
	MLX5_SET(vlan, vlan, vid, fte->action.vlan[0].vid);
	MLX5_SET(vlan, vlan, prio, fte->action.vlan[0].prio);

	vlan = MLX5_ADDR_OF(flow_context, in_flow_context, push_vlan_2);

	MLX5_SET(vlan, vlan, ethtype, fte->action.vlan[1].ethtype);
	MLX5_SET(vlan, vlan, vid, fte->action.vlan[1].vid);
	MLX5_SET(vlan, vlan, prio, fte->action.vlan[1].prio);

	in_match_value = MLX5_ADDR_OF(flow_context, in_flow_context,
				      match_value);
	स_नकल(in_match_value, fte->val, माप(u32) * MLX5_ST_SZ_DW_MATCH_PARAM);

	in_dests = MLX5_ADDR_OF(flow_context, in_flow_context, destination);
	अगर (fte->action.action & MLX5_FLOW_CONTEXT_ACTION_FWD_DEST) अणु
		पूर्णांक list_size = 0;

		क्रम (i = 0; i < fte->dests_size; i++) अणु
			अचिन्हित पूर्णांक id, type = fte->dest_arr[i].type;

			अगर (type == MLX5_FLOW_DESTINATION_TYPE_COUNTER)
				जारी;

			चयन (type) अणु
			हाल MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE_NUM:
				id = fte->dest_arr[i].ft_num;
				type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
				अवरोध;
			हाल MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE:
				id = fte->dest_arr[i].ft_id;
				अवरोध;
			हाल MLX5_FLOW_DESTINATION_TYPE_VPORT:
				id = fte->dest_arr[i].vport.num;
				MLX5_SET(dest_क्रमmat_काष्ठा, in_dests,
					 destination_eचयन_owner_vhca_id_valid,
					 !!(fte->dest_arr[i].vport.flags &
					    MLX5_FLOW_DEST_VPORT_VHCA_ID));
				MLX5_SET(dest_क्रमmat_काष्ठा, in_dests,
					 destination_eचयन_owner_vhca_id,
					 fte->dest_arr[i].vport.vhca_id);
				अगर (extended_dest && (fte->dest_arr[i].vport.flags &
						    MLX5_FLOW_DEST_VPORT_REFORMAT_ID)) अणु
					MLX5_SET(dest_क्रमmat_काष्ठा, in_dests,
						 packet_reक्रमmat,
						 !!(fte->dest_arr[i].vport.flags &
						    MLX5_FLOW_DEST_VPORT_REFORMAT_ID));
					MLX5_SET(extended_dest_क्रमmat, in_dests,
						 packet_reक्रमmat_id,
						 fte->dest_arr[i].vport.reक्रमmat_id);
				पूर्ण
				अवरोध;
			शेष:
				id = fte->dest_arr[i].tir_num;
			पूर्ण

			MLX5_SET(dest_क्रमmat_काष्ठा, in_dests, destination_type,
				 type);
			MLX5_SET(dest_क्रमmat_काष्ठा, in_dests, destination_id, id);
			in_dests += dst_cnt_size;
			list_size++;
		पूर्ण

		MLX5_SET(flow_context, in_flow_context, destination_list_size,
			 list_size);
	पूर्ण

	अगर (fte->action.action & MLX5_FLOW_CONTEXT_ACTION_COUNT) अणु
		पूर्णांक max_list_size = BIT(MLX5_CAP_FLOWTABLE_TYPE(dev,
					log_max_flow_counter,
					ft->type));
		पूर्णांक list_size = 0;

		क्रम (i = 0; i < fte->dests_size; i++) अणु
			अगर (fte->dest_arr[i].type !=
			    MLX5_FLOW_DESTINATION_TYPE_COUNTER)
				जारी;

			MLX5_SET(flow_counter_list, in_dests, flow_counter_id,
				 fte->dest_arr[i].counter_id);
			in_dests += dst_cnt_size;
			list_size++;
		पूर्ण
		अगर (list_size > max_list_size) अणु
			err = -EINVAL;
			जाओ err_out;
		पूर्ण

		MLX5_SET(flow_context, in_flow_context, flow_counter_list_size,
			 list_size);
	पूर्ण

	err = mlx5_cmd_exec(dev, in, inlen, out, माप(out));
err_out:
	kvमुक्त(in);
	वापस err;
पूर्ण
