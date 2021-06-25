<शैली गुरु>
/*
 * Copyright (c) 2015, Mellanox Technologies. All rights reserved.
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

#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/device.h>
#समावेश <linux/mlx5/mlx5_अगरc.h>

#समावेश "fs_core.h"
#समावेश "fs_cmd.h"
#समावेश "mlx5_core.h"
#समावेश "eswitch.h"

अटल पूर्णांक mlx5_cmd_stub_update_root_ft(काष्ठा mlx5_flow_root_namespace *ns,
					काष्ठा mlx5_flow_table *ft,
					u32 underlay_qpn,
					bool disconnect)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_cmd_stub_create_flow_table(काष्ठा mlx5_flow_root_namespace *ns,
					   काष्ठा mlx5_flow_table *ft,
					   अचिन्हित पूर्णांक log_size,
					   काष्ठा mlx5_flow_table *next_ft)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_cmd_stub_destroy_flow_table(काष्ठा mlx5_flow_root_namespace *ns,
					    काष्ठा mlx5_flow_table *ft)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_cmd_stub_modअगरy_flow_table(काष्ठा mlx5_flow_root_namespace *ns,
					   काष्ठा mlx5_flow_table *ft,
					   काष्ठा mlx5_flow_table *next_ft)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_cmd_stub_create_flow_group(काष्ठा mlx5_flow_root_namespace *ns,
					   काष्ठा mlx5_flow_table *ft,
					   u32 *in,
					   काष्ठा mlx5_flow_group *fg)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_cmd_stub_destroy_flow_group(काष्ठा mlx5_flow_root_namespace *ns,
					    काष्ठा mlx5_flow_table *ft,
					    काष्ठा mlx5_flow_group *fg)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_cmd_stub_create_fte(काष्ठा mlx5_flow_root_namespace *ns,
				    काष्ठा mlx5_flow_table *ft,
				    काष्ठा mlx5_flow_group *group,
				    काष्ठा fs_fte *fte)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_cmd_stub_update_fte(काष्ठा mlx5_flow_root_namespace *ns,
				    काष्ठा mlx5_flow_table *ft,
				    काष्ठा mlx5_flow_group *group,
				    पूर्णांक modअगरy_mask,
				    काष्ठा fs_fte *fte)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक mlx5_cmd_stub_delete_fte(काष्ठा mlx5_flow_root_namespace *ns,
				    काष्ठा mlx5_flow_table *ft,
				    काष्ठा fs_fte *fte)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_cmd_stub_packet_reक्रमmat_alloc(काष्ठा mlx5_flow_root_namespace *ns,
					       पूर्णांक reक्रमmat_type,
					       माप_प्रकार size,
					       व्योम *reक्रमmat_data,
					       क्रमागत mlx5_flow_namespace_type namespace,
					       काष्ठा mlx5_pkt_reक्रमmat *pkt_reक्रमmat)
अणु
	वापस 0;
पूर्ण

अटल व्योम mlx5_cmd_stub_packet_reक्रमmat_dealloc(काष्ठा mlx5_flow_root_namespace *ns,
						  काष्ठा mlx5_pkt_reक्रमmat *pkt_reक्रमmat)
अणु
पूर्ण

अटल पूर्णांक mlx5_cmd_stub_modअगरy_header_alloc(काष्ठा mlx5_flow_root_namespace *ns,
					     u8 namespace, u8 num_actions,
					     व्योम *modअगरy_actions,
					     काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr)
अणु
	वापस 0;
पूर्ण

अटल व्योम mlx5_cmd_stub_modअगरy_header_dealloc(काष्ठा mlx5_flow_root_namespace *ns,
						काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr)
अणु
पूर्ण

अटल पूर्णांक mlx5_cmd_stub_set_peer(काष्ठा mlx5_flow_root_namespace *ns,
				  काष्ठा mlx5_flow_root_namespace *peer_ns)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_cmd_stub_create_ns(काष्ठा mlx5_flow_root_namespace *ns)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_cmd_stub_destroy_ns(काष्ठा mlx5_flow_root_namespace *ns)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_cmd_update_root_ft(काष्ठा mlx5_flow_root_namespace *ns,
				   काष्ठा mlx5_flow_table *ft, u32 underlay_qpn,
				   bool disconnect)
अणु
	u32 in[MLX5_ST_SZ_DW(set_flow_table_root_in)] = अणुपूर्ण;
	काष्ठा mlx5_core_dev *dev = ns->dev;

	अगर ((MLX5_CAP_GEN(dev, port_type) == MLX5_CAP_PORT_TYPE_IB) &&
	    underlay_qpn == 0)
		वापस 0;

	MLX5_SET(set_flow_table_root_in, in, opcode,
		 MLX5_CMD_OP_SET_FLOW_TABLE_ROOT);
	MLX5_SET(set_flow_table_root_in, in, table_type, ft->type);

	अगर (disconnect)
		MLX5_SET(set_flow_table_root_in, in, op_mod, 1);
	अन्यथा
		MLX5_SET(set_flow_table_root_in, in, table_id, ft->id);

	MLX5_SET(set_flow_table_root_in, in, underlay_qpn, underlay_qpn);
	MLX5_SET(set_flow_table_root_in, in, vport_number, ft->vport);
	MLX5_SET(set_flow_table_root_in, in, other_vport,
		 !!(ft->flags & MLX5_FLOW_TABLE_OTHER_VPORT));

	वापस mlx5_cmd_exec_in(dev, set_flow_table_root, in);
पूर्ण

अटल पूर्णांक mlx5_cmd_create_flow_table(काष्ठा mlx5_flow_root_namespace *ns,
				      काष्ठा mlx5_flow_table *ft,
				      अचिन्हित पूर्णांक log_size,
				      काष्ठा mlx5_flow_table *next_ft)
अणु
	पूर्णांक en_encap = !!(ft->flags & MLX5_FLOW_TABLE_TUNNEL_EN_REFORMAT);
	पूर्णांक en_decap = !!(ft->flags & MLX5_FLOW_TABLE_TUNNEL_EN_DECAP);
	पूर्णांक term = !!(ft->flags & MLX5_FLOW_TABLE_TERMINATION);
	u32 out[MLX5_ST_SZ_DW(create_flow_table_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(create_flow_table_in)] = अणुपूर्ण;
	काष्ठा mlx5_core_dev *dev = ns->dev;
	पूर्णांक err;

	MLX5_SET(create_flow_table_in, in, opcode,
		 MLX5_CMD_OP_CREATE_FLOW_TABLE);

	MLX5_SET(create_flow_table_in, in, table_type, ft->type);
	MLX5_SET(create_flow_table_in, in, flow_table_context.level, ft->level);
	MLX5_SET(create_flow_table_in, in, flow_table_context.log_size, log_size);
	MLX5_SET(create_flow_table_in, in, vport_number, ft->vport);
	MLX5_SET(create_flow_table_in, in, other_vport,
		 !!(ft->flags & MLX5_FLOW_TABLE_OTHER_VPORT));

	MLX5_SET(create_flow_table_in, in, flow_table_context.decap_en,
		 en_decap);
	MLX5_SET(create_flow_table_in, in, flow_table_context.reक्रमmat_en,
		 en_encap);
	MLX5_SET(create_flow_table_in, in, flow_table_context.termination_table,
		 term);

	चयन (ft->op_mod) अणु
	हाल FS_FT_OP_MOD_NORMAL:
		अगर (next_ft) अणु
			MLX5_SET(create_flow_table_in, in,
				 flow_table_context.table_miss_action,
				 MLX5_FLOW_TABLE_MISS_ACTION_FWD);
			MLX5_SET(create_flow_table_in, in,
				 flow_table_context.table_miss_id, next_ft->id);
		पूर्ण अन्यथा अणु
			MLX5_SET(create_flow_table_in, in,
				 flow_table_context.table_miss_action,
				 ft->def_miss_action);
		पूर्ण
		अवरोध;

	हाल FS_FT_OP_MOD_LAG_DEMUX:
		MLX5_SET(create_flow_table_in, in, op_mod, 0x1);
		अगर (next_ft)
			MLX5_SET(create_flow_table_in, in,
				 flow_table_context.lag_master_next_table_id,
				 next_ft->id);
		अवरोध;
	पूर्ण

	err = mlx5_cmd_exec_inout(dev, create_flow_table, in, out);
	अगर (!err)
		ft->id = MLX5_GET(create_flow_table_out, out,
				  table_id);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_cmd_destroy_flow_table(काष्ठा mlx5_flow_root_namespace *ns,
				       काष्ठा mlx5_flow_table *ft)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_flow_table_in)] = अणुपूर्ण;
	काष्ठा mlx5_core_dev *dev = ns->dev;

	MLX5_SET(destroy_flow_table_in, in, opcode,
		 MLX5_CMD_OP_DESTROY_FLOW_TABLE);
	MLX5_SET(destroy_flow_table_in, in, table_type, ft->type);
	MLX5_SET(destroy_flow_table_in, in, table_id, ft->id);
	MLX5_SET(destroy_flow_table_in, in, vport_number, ft->vport);
	MLX5_SET(destroy_flow_table_in, in, other_vport,
		 !!(ft->flags & MLX5_FLOW_TABLE_OTHER_VPORT));

	वापस mlx5_cmd_exec_in(dev, destroy_flow_table, in);
पूर्ण

अटल पूर्णांक mlx5_cmd_modअगरy_flow_table(काष्ठा mlx5_flow_root_namespace *ns,
				      काष्ठा mlx5_flow_table *ft,
				      काष्ठा mlx5_flow_table *next_ft)
अणु
	u32 in[MLX5_ST_SZ_DW(modअगरy_flow_table_in)] = अणुपूर्ण;
	काष्ठा mlx5_core_dev *dev = ns->dev;

	MLX5_SET(modअगरy_flow_table_in, in, opcode,
		 MLX5_CMD_OP_MODIFY_FLOW_TABLE);
	MLX5_SET(modअगरy_flow_table_in, in, table_type, ft->type);
	MLX5_SET(modअगरy_flow_table_in, in, table_id, ft->id);

	अगर (ft->op_mod == FS_FT_OP_MOD_LAG_DEMUX) अणु
		MLX5_SET(modअगरy_flow_table_in, in, modअगरy_field_select,
			 MLX5_MODIFY_FLOW_TABLE_LAG_NEXT_TABLE_ID);
		अगर (next_ft) अणु
			MLX5_SET(modअगरy_flow_table_in, in,
				 flow_table_context.lag_master_next_table_id, next_ft->id);
		पूर्ण अन्यथा अणु
			MLX5_SET(modअगरy_flow_table_in, in,
				 flow_table_context.lag_master_next_table_id, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		MLX5_SET(modअगरy_flow_table_in, in, vport_number, ft->vport);
		MLX5_SET(modअगरy_flow_table_in, in, other_vport,
			 !!(ft->flags & MLX5_FLOW_TABLE_OTHER_VPORT));
		MLX5_SET(modअगरy_flow_table_in, in, modअगरy_field_select,
			 MLX5_MODIFY_FLOW_TABLE_MISS_TABLE_ID);
		अगर (next_ft) अणु
			MLX5_SET(modअगरy_flow_table_in, in,
				 flow_table_context.table_miss_action,
				 MLX5_FLOW_TABLE_MISS_ACTION_FWD);
			MLX5_SET(modअगरy_flow_table_in, in,
				 flow_table_context.table_miss_id,
				 next_ft->id);
		पूर्ण अन्यथा अणु
			MLX5_SET(modअगरy_flow_table_in, in,
				 flow_table_context.table_miss_action,
				 ft->def_miss_action);
		पूर्ण
	पूर्ण

	वापस mlx5_cmd_exec_in(dev, modअगरy_flow_table, in);
पूर्ण

अटल पूर्णांक mlx5_cmd_create_flow_group(काष्ठा mlx5_flow_root_namespace *ns,
				      काष्ठा mlx5_flow_table *ft,
				      u32 *in,
				      काष्ठा mlx5_flow_group *fg)
अणु
	u32 out[MLX5_ST_SZ_DW(create_flow_group_out)] = अणुपूर्ण;
	काष्ठा mlx5_core_dev *dev = ns->dev;
	पूर्णांक err;

	MLX5_SET(create_flow_group_in, in, opcode,
		 MLX5_CMD_OP_CREATE_FLOW_GROUP);
	MLX5_SET(create_flow_group_in, in, table_type, ft->type);
	MLX5_SET(create_flow_group_in, in, table_id, ft->id);
	अगर (ft->vport) अणु
		MLX5_SET(create_flow_group_in, in, vport_number, ft->vport);
		MLX5_SET(create_flow_group_in, in, other_vport, 1);
	पूर्ण

	MLX5_SET(create_flow_group_in, in, vport_number, ft->vport);
	MLX5_SET(create_flow_group_in, in, other_vport,
		 !!(ft->flags & MLX5_FLOW_TABLE_OTHER_VPORT));
	err = mlx5_cmd_exec_inout(dev, create_flow_group, in, out);
	अगर (!err)
		fg->id = MLX5_GET(create_flow_group_out, out,
				  group_id);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_cmd_destroy_flow_group(काष्ठा mlx5_flow_root_namespace *ns,
				       काष्ठा mlx5_flow_table *ft,
				       काष्ठा mlx5_flow_group *fg)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_flow_group_in)] = अणुपूर्ण;
	काष्ठा mlx5_core_dev *dev = ns->dev;

	MLX5_SET(destroy_flow_group_in, in, opcode,
		 MLX5_CMD_OP_DESTROY_FLOW_GROUP);
	MLX5_SET(destroy_flow_group_in, in, table_type, ft->type);
	MLX5_SET(destroy_flow_group_in, in, table_id, ft->id);
	MLX5_SET(destroy_flow_group_in, in, group_id, fg->id);
	MLX5_SET(destroy_flow_group_in, in, vport_number, ft->vport);
	MLX5_SET(destroy_flow_group_in, in, other_vport,
		 !!(ft->flags & MLX5_FLOW_TABLE_OTHER_VPORT));
	वापस mlx5_cmd_exec_in(dev, destroy_flow_group, in);
पूर्ण

अटल पूर्णांक mlx5_set_extended_dest(काष्ठा mlx5_core_dev *dev,
				  काष्ठा fs_fte *fte, bool *extended_dest)
अणु
	पूर्णांक fw_log_max_fdb_encap_uplink =
		MLX5_CAP_ESW(dev, log_max_fdb_encap_uplink);
	पूर्णांक num_fwd_destinations = 0;
	काष्ठा mlx5_flow_rule *dst;
	पूर्णांक num_encap = 0;

	*extended_dest = false;
	अगर (!(fte->action.action & MLX5_FLOW_CONTEXT_ACTION_FWD_DEST))
		वापस 0;

	list_क्रम_each_entry(dst, &fte->node.children, node.list) अणु
		अगर (dst->dest_attr.type == MLX5_FLOW_DESTINATION_TYPE_COUNTER)
			जारी;
		अगर (dst->dest_attr.type == MLX5_FLOW_DESTINATION_TYPE_VPORT &&
		    dst->dest_attr.vport.flags & MLX5_FLOW_DEST_VPORT_REFORMAT_ID)
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
अटल पूर्णांक mlx5_cmd_set_fte(काष्ठा mlx5_core_dev *dev,
			    पूर्णांक opmod, पूर्णांक modअगरy_mask,
			    काष्ठा mlx5_flow_table *ft,
			    अचिन्हित group_id,
			    काष्ठा fs_fte *fte)
अणु
	u32 out[MLX5_ST_SZ_DW(set_fte_out)] = अणु0पूर्ण;
	bool extended_dest = false;
	काष्ठा mlx5_flow_rule *dst;
	व्योम *in_flow_context, *vlan;
	व्योम *in_match_value;
	अचिन्हित पूर्णांक inlen;
	पूर्णांक dst_cnt_size;
	व्योम *in_dests;
	u32 *in;
	पूर्णांक err;

	अगर (mlx5_set_extended_dest(dev, fte, &extended_dest))
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
	MLX5_SET(set_fte_in, in, table_id,   ft->id);
	MLX5_SET(set_fte_in, in, flow_index, fte->index);
	MLX5_SET(set_fte_in, in, ignore_flow_level,
		 !!(fte->action.flags & FLOW_ACT_IGNORE_FLOW_LEVEL));

	MLX5_SET(set_fte_in, in, vport_number, ft->vport);
	MLX5_SET(set_fte_in, in, other_vport,
		 !!(ft->flags & MLX5_FLOW_TABLE_OTHER_VPORT));

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

	MLX5_SET(flow_context, in_flow_context, ipsec_obj_id, fte->action.ipsec_obj_id);

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
	स_नकल(in_match_value, &fte->val, माप(fte->val));

	in_dests = MLX5_ADDR_OF(flow_context, in_flow_context, destination);
	अगर (fte->action.action & MLX5_FLOW_CONTEXT_ACTION_FWD_DEST) अणु
		पूर्णांक list_size = 0;

		list_क्रम_each_entry(dst, &fte->node.children, node.list) अणु
			अचिन्हित पूर्णांक id, type = dst->dest_attr.type;

			अगर (type == MLX5_FLOW_DESTINATION_TYPE_COUNTER)
				जारी;

			चयन (type) अणु
			हाल MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE_NUM:
				id = dst->dest_attr.ft_num;
				type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
				अवरोध;
			हाल MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE:
				id = dst->dest_attr.ft->id;
				अवरोध;
			हाल MLX5_FLOW_DESTINATION_TYPE_VPORT:
				id = dst->dest_attr.vport.num;
				MLX5_SET(dest_क्रमmat_काष्ठा, in_dests,
					 destination_eचयन_owner_vhca_id_valid,
					 !!(dst->dest_attr.vport.flags &
					    MLX5_FLOW_DEST_VPORT_VHCA_ID));
				MLX5_SET(dest_क्रमmat_काष्ठा, in_dests,
					 destination_eचयन_owner_vhca_id,
					 dst->dest_attr.vport.vhca_id);
				अगर (extended_dest &&
				    dst->dest_attr.vport.pkt_reक्रमmat) अणु
					MLX5_SET(dest_क्रमmat_काष्ठा, in_dests,
						 packet_reक्रमmat,
						 !!(dst->dest_attr.vport.flags &
						    MLX5_FLOW_DEST_VPORT_REFORMAT_ID));
					MLX5_SET(extended_dest_क्रमmat, in_dests,
						 packet_reक्रमmat_id,
						 dst->dest_attr.vport.pkt_reक्रमmat->id);
				पूर्ण
				अवरोध;
			हाल MLX5_FLOW_DESTINATION_TYPE_FLOW_SAMPLER:
				id = dst->dest_attr.sampler_id;
				अवरोध;
			शेष:
				id = dst->dest_attr.tir_num;
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

		list_क्रम_each_entry(dst, &fte->node.children, node.list) अणु
			अगर (dst->dest_attr.type !=
			    MLX5_FLOW_DESTINATION_TYPE_COUNTER)
				जारी;

			MLX5_SET(flow_counter_list, in_dests, flow_counter_id,
				 dst->dest_attr.counter_id);
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

अटल पूर्णांक mlx5_cmd_create_fte(काष्ठा mlx5_flow_root_namespace *ns,
			       काष्ठा mlx5_flow_table *ft,
			       काष्ठा mlx5_flow_group *group,
			       काष्ठा fs_fte *fte)
अणु
	काष्ठा mlx5_core_dev *dev = ns->dev;
	अचिन्हित पूर्णांक group_id = group->id;

	वापस mlx5_cmd_set_fte(dev, 0, 0, ft, group_id, fte);
पूर्ण

अटल पूर्णांक mlx5_cmd_update_fte(काष्ठा mlx5_flow_root_namespace *ns,
			       काष्ठा mlx5_flow_table *ft,
			       काष्ठा mlx5_flow_group *fg,
			       पूर्णांक modअगरy_mask,
			       काष्ठा fs_fte *fte)
अणु
	पूर्णांक opmod;
	काष्ठा mlx5_core_dev *dev = ns->dev;
	पूर्णांक atomic_mod_cap = MLX5_CAP_FLOWTABLE(dev,
						flow_table_properties_nic_receive.
						flow_modअगरy_en);
	अगर (!atomic_mod_cap)
		वापस -EOPNOTSUPP;
	opmod = 1;

	वापस	mlx5_cmd_set_fte(dev, opmod, modअगरy_mask, ft, fg->id, fte);
पूर्ण

अटल पूर्णांक mlx5_cmd_delete_fte(काष्ठा mlx5_flow_root_namespace *ns,
			       काष्ठा mlx5_flow_table *ft,
			       काष्ठा fs_fte *fte)
अणु
	u32 in[MLX5_ST_SZ_DW(delete_fte_in)] = अणुपूर्ण;
	काष्ठा mlx5_core_dev *dev = ns->dev;

	MLX5_SET(delete_fte_in, in, opcode, MLX5_CMD_OP_DELETE_FLOW_TABLE_ENTRY);
	MLX5_SET(delete_fte_in, in, table_type, ft->type);
	MLX5_SET(delete_fte_in, in, table_id, ft->id);
	MLX5_SET(delete_fte_in, in, flow_index, fte->index);
	MLX5_SET(delete_fte_in, in, vport_number, ft->vport);
	MLX5_SET(delete_fte_in, in, other_vport,
		 !!(ft->flags & MLX5_FLOW_TABLE_OTHER_VPORT));

	वापस mlx5_cmd_exec_in(dev, delete_fte, in);
पूर्ण

पूर्णांक mlx5_cmd_fc_bulk_alloc(काष्ठा mlx5_core_dev *dev,
			   क्रमागत mlx5_fc_bulk_alloc_biपंचांगask alloc_biपंचांगask,
			   u32 *id)
अणु
	u32 out[MLX5_ST_SZ_DW(alloc_flow_counter_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(alloc_flow_counter_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(alloc_flow_counter_in, in, opcode,
		 MLX5_CMD_OP_ALLOC_FLOW_COUNTER);
	MLX5_SET(alloc_flow_counter_in, in, flow_counter_bulk, alloc_biपंचांगask);

	err = mlx5_cmd_exec_inout(dev, alloc_flow_counter, in, out);
	अगर (!err)
		*id = MLX5_GET(alloc_flow_counter_out, out, flow_counter_id);
	वापस err;
पूर्ण

पूर्णांक mlx5_cmd_fc_alloc(काष्ठा mlx5_core_dev *dev, u32 *id)
अणु
	वापस mlx5_cmd_fc_bulk_alloc(dev, 0, id);
पूर्ण

पूर्णांक mlx5_cmd_fc_मुक्त(काष्ठा mlx5_core_dev *dev, u32 id)
अणु
	u32 in[MLX5_ST_SZ_DW(dealloc_flow_counter_in)] = अणुपूर्ण;

	MLX5_SET(dealloc_flow_counter_in, in, opcode,
		 MLX5_CMD_OP_DEALLOC_FLOW_COUNTER);
	MLX5_SET(dealloc_flow_counter_in, in, flow_counter_id, id);
	वापस mlx5_cmd_exec_in(dev, dealloc_flow_counter, in);
पूर्ण

पूर्णांक mlx5_cmd_fc_query(काष्ठा mlx5_core_dev *dev, u32 id,
		      u64 *packets, u64 *bytes)
अणु
	u32 out[MLX5_ST_SZ_BYTES(query_flow_counter_out) +
		MLX5_ST_SZ_BYTES(traffic_counter)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(query_flow_counter_in)] = अणुपूर्ण;
	व्योम *stats;
	पूर्णांक err = 0;

	MLX5_SET(query_flow_counter_in, in, opcode,
		 MLX5_CMD_OP_QUERY_FLOW_COUNTER);
	MLX5_SET(query_flow_counter_in, in, op_mod, 0);
	MLX5_SET(query_flow_counter_in, in, flow_counter_id, id);
	err = mlx5_cmd_exec(dev, in, माप(in), out, माप(out));
	अगर (err)
		वापस err;

	stats = MLX5_ADDR_OF(query_flow_counter_out, out, flow_statistics);
	*packets = MLX5_GET64(traffic_counter, stats, packets);
	*bytes = MLX5_GET64(traffic_counter, stats, octets);
	वापस 0;
पूर्ण

पूर्णांक mlx5_cmd_fc_get_bulk_query_out_len(पूर्णांक bulk_len)
अणु
	वापस MLX5_ST_SZ_BYTES(query_flow_counter_out) +
		MLX5_ST_SZ_BYTES(traffic_counter) * bulk_len;
पूर्ण

पूर्णांक mlx5_cmd_fc_bulk_query(काष्ठा mlx5_core_dev *dev, u32 base_id, पूर्णांक bulk_len,
			   u32 *out)
अणु
	पूर्णांक outlen = mlx5_cmd_fc_get_bulk_query_out_len(bulk_len);
	u32 in[MLX5_ST_SZ_DW(query_flow_counter_in)] = अणुपूर्ण;

	MLX5_SET(query_flow_counter_in, in, opcode,
		 MLX5_CMD_OP_QUERY_FLOW_COUNTER);
	MLX5_SET(query_flow_counter_in, in, flow_counter_id, base_id);
	MLX5_SET(query_flow_counter_in, in, num_of_counters, bulk_len);
	वापस mlx5_cmd_exec(dev, in, माप(in), out, outlen);
पूर्ण

अटल पूर्णांक mlx5_cmd_packet_reक्रमmat_alloc(काष्ठा mlx5_flow_root_namespace *ns,
					  पूर्णांक reक्रमmat_type,
					  माप_प्रकार size,
					  व्योम *reक्रमmat_data,
					  क्रमागत mlx5_flow_namespace_type namespace,
					  काष्ठा mlx5_pkt_reक्रमmat *pkt_reक्रमmat)
अणु
	u32 out[MLX5_ST_SZ_DW(alloc_packet_reक्रमmat_context_out)] = अणुपूर्ण;
	काष्ठा mlx5_core_dev *dev = ns->dev;
	व्योम *packet_reक्रमmat_context_in;
	पूर्णांक max_encap_size;
	व्योम *reक्रमmat;
	पूर्णांक inlen;
	पूर्णांक err;
	u32 *in;

	अगर (namespace == MLX5_FLOW_NAMESPACE_FDB)
		max_encap_size = MLX5_CAP_ESW(dev, max_encap_header_size);
	अन्यथा
		max_encap_size = MLX5_CAP_FLOWTABLE(dev, max_encap_header_size);

	अगर (size > max_encap_size) अणु
		mlx5_core_warn(dev, "encap size %zd too big, max supported is %d\n",
			       size, max_encap_size);
		वापस -EINVAL;
	पूर्ण

	in = kzalloc(MLX5_ST_SZ_BYTES(alloc_packet_reक्रमmat_context_in) + size,
		     GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	packet_reक्रमmat_context_in = MLX5_ADDR_OF(alloc_packet_reक्रमmat_context_in,
						  in, packet_reक्रमmat_context);
	reक्रमmat = MLX5_ADDR_OF(packet_reक्रमmat_context_in,
				packet_reक्रमmat_context_in,
				reक्रमmat_data);
	inlen = reक्रमmat - (व्योम *)in  + size;

	MLX5_SET(alloc_packet_reक्रमmat_context_in, in, opcode,
		 MLX5_CMD_OP_ALLOC_PACKET_REFORMAT_CONTEXT);
	MLX5_SET(packet_reक्रमmat_context_in, packet_reक्रमmat_context_in,
		 reक्रमmat_data_size, size);
	MLX5_SET(packet_reक्रमmat_context_in, packet_reक्रमmat_context_in,
		 reक्रमmat_type, reक्रमmat_type);
	स_नकल(reक्रमmat, reक्रमmat_data, size);

	err = mlx5_cmd_exec(dev, in, inlen, out, माप(out));

	pkt_reक्रमmat->id = MLX5_GET(alloc_packet_reक्रमmat_context_out,
				    out, packet_reक्रमmat_id);
	kमुक्त(in);
	वापस err;
पूर्ण

अटल व्योम mlx5_cmd_packet_reक्रमmat_dealloc(काष्ठा mlx5_flow_root_namespace *ns,
					     काष्ठा mlx5_pkt_reक्रमmat *pkt_reक्रमmat)
अणु
	u32 in[MLX5_ST_SZ_DW(dealloc_packet_reक्रमmat_context_in)] = अणुपूर्ण;
	काष्ठा mlx5_core_dev *dev = ns->dev;

	MLX5_SET(dealloc_packet_reक्रमmat_context_in, in, opcode,
		 MLX5_CMD_OP_DEALLOC_PACKET_REFORMAT_CONTEXT);
	MLX5_SET(dealloc_packet_reक्रमmat_context_in, in, packet_reक्रमmat_id,
		 pkt_reक्रमmat->id);

	mlx5_cmd_exec_in(dev, dealloc_packet_reक्रमmat_context, in);
पूर्ण

अटल पूर्णांक mlx5_cmd_modअगरy_header_alloc(काष्ठा mlx5_flow_root_namespace *ns,
					u8 namespace, u8 num_actions,
					व्योम *modअगरy_actions,
					काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr)
अणु
	u32 out[MLX5_ST_SZ_DW(alloc_modअगरy_header_context_out)] = अणुपूर्ण;
	पूर्णांक max_actions, actions_size, inlen, err;
	काष्ठा mlx5_core_dev *dev = ns->dev;
	व्योम *actions_in;
	u8 table_type;
	u32 *in;

	चयन (namespace) अणु
	हाल MLX5_FLOW_NAMESPACE_FDB:
		max_actions = MLX5_CAP_ESW_FLOWTABLE_FDB(dev, max_modअगरy_header_actions);
		table_type = FS_FT_FDB;
		अवरोध;
	हाल MLX5_FLOW_NAMESPACE_KERNEL:
	हाल MLX5_FLOW_NAMESPACE_BYPASS:
		max_actions = MLX5_CAP_FLOWTABLE_NIC_RX(dev, max_modअगरy_header_actions);
		table_type = FS_FT_NIC_RX;
		अवरोध;
	हाल MLX5_FLOW_NAMESPACE_EGRESS:
#अगर_घोषित CONFIG_MLX5_IPSEC
	हाल MLX5_FLOW_NAMESPACE_EGRESS_KERNEL:
#पूर्ण_अगर
		max_actions = MLX5_CAP_FLOWTABLE_NIC_TX(dev, max_modअगरy_header_actions);
		table_type = FS_FT_NIC_TX;
		अवरोध;
	हाल MLX5_FLOW_NAMESPACE_ESW_INGRESS:
		max_actions = MLX5_CAP_ESW_INGRESS_ACL(dev, max_modअगरy_header_actions);
		table_type = FS_FT_ESW_INGRESS_ACL;
		अवरोध;
	हाल MLX5_FLOW_NAMESPACE_RDMA_TX:
		max_actions = MLX5_CAP_FLOWTABLE_RDMA_TX(dev, max_modअगरy_header_actions);
		table_type = FS_FT_RDMA_TX;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (num_actions > max_actions) अणु
		mlx5_core_warn(dev, "too many modify header actions %d, max supported %d\n",
			       num_actions, max_actions);
		वापस -EOPNOTSUPP;
	पूर्ण

	actions_size = MLX5_UN_SZ_BYTES(set_add_copy_action_in_स्वतः) * num_actions;
	inlen = MLX5_ST_SZ_BYTES(alloc_modअगरy_header_context_in) + actions_size;

	in = kzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(alloc_modअगरy_header_context_in, in, opcode,
		 MLX5_CMD_OP_ALLOC_MODIFY_HEADER_CONTEXT);
	MLX5_SET(alloc_modअगरy_header_context_in, in, table_type, table_type);
	MLX5_SET(alloc_modअगरy_header_context_in, in, num_of_actions, num_actions);

	actions_in = MLX5_ADDR_OF(alloc_modअगरy_header_context_in, in, actions);
	स_नकल(actions_in, modअगरy_actions, actions_size);

	err = mlx5_cmd_exec(dev, in, inlen, out, माप(out));

	modअगरy_hdr->id = MLX5_GET(alloc_modअगरy_header_context_out, out, modअगरy_header_id);
	kमुक्त(in);
	वापस err;
पूर्ण

अटल व्योम mlx5_cmd_modअगरy_header_dealloc(काष्ठा mlx5_flow_root_namespace *ns,
					   काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr)
अणु
	u32 in[MLX5_ST_SZ_DW(dealloc_modअगरy_header_context_in)] = अणुपूर्ण;
	काष्ठा mlx5_core_dev *dev = ns->dev;

	MLX5_SET(dealloc_modअगरy_header_context_in, in, opcode,
		 MLX5_CMD_OP_DEALLOC_MODIFY_HEADER_CONTEXT);
	MLX5_SET(dealloc_modअगरy_header_context_in, in, modअगरy_header_id,
		 modअगरy_hdr->id);

	mlx5_cmd_exec_in(dev, dealloc_modअगरy_header_context, in);
पूर्ण

अटल स्थिर काष्ठा mlx5_flow_cmds mlx5_flow_cmds = अणु
	.create_flow_table = mlx5_cmd_create_flow_table,
	.destroy_flow_table = mlx5_cmd_destroy_flow_table,
	.modअगरy_flow_table = mlx5_cmd_modअगरy_flow_table,
	.create_flow_group = mlx5_cmd_create_flow_group,
	.destroy_flow_group = mlx5_cmd_destroy_flow_group,
	.create_fte = mlx5_cmd_create_fte,
	.update_fte = mlx5_cmd_update_fte,
	.delete_fte = mlx5_cmd_delete_fte,
	.update_root_ft = mlx5_cmd_update_root_ft,
	.packet_reक्रमmat_alloc = mlx5_cmd_packet_reक्रमmat_alloc,
	.packet_reक्रमmat_dealloc = mlx5_cmd_packet_reक्रमmat_dealloc,
	.modअगरy_header_alloc = mlx5_cmd_modअगरy_header_alloc,
	.modअगरy_header_dealloc = mlx5_cmd_modअगरy_header_dealloc,
	.set_peer = mlx5_cmd_stub_set_peer,
	.create_ns = mlx5_cmd_stub_create_ns,
	.destroy_ns = mlx5_cmd_stub_destroy_ns,
पूर्ण;

अटल स्थिर काष्ठा mlx5_flow_cmds mlx5_flow_cmd_stubs = अणु
	.create_flow_table = mlx5_cmd_stub_create_flow_table,
	.destroy_flow_table = mlx5_cmd_stub_destroy_flow_table,
	.modअगरy_flow_table = mlx5_cmd_stub_modअगरy_flow_table,
	.create_flow_group = mlx5_cmd_stub_create_flow_group,
	.destroy_flow_group = mlx5_cmd_stub_destroy_flow_group,
	.create_fte = mlx5_cmd_stub_create_fte,
	.update_fte = mlx5_cmd_stub_update_fte,
	.delete_fte = mlx5_cmd_stub_delete_fte,
	.update_root_ft = mlx5_cmd_stub_update_root_ft,
	.packet_reक्रमmat_alloc = mlx5_cmd_stub_packet_reक्रमmat_alloc,
	.packet_reक्रमmat_dealloc = mlx5_cmd_stub_packet_reक्रमmat_dealloc,
	.modअगरy_header_alloc = mlx5_cmd_stub_modअगरy_header_alloc,
	.modअगरy_header_dealloc = mlx5_cmd_stub_modअगरy_header_dealloc,
	.set_peer = mlx5_cmd_stub_set_peer,
	.create_ns = mlx5_cmd_stub_create_ns,
	.destroy_ns = mlx5_cmd_stub_destroy_ns,
पूर्ण;

स्थिर काष्ठा mlx5_flow_cmds *mlx5_fs_cmd_get_fw_cmds(व्योम)
अणु
	वापस &mlx5_flow_cmds;
पूर्ण

अटल स्थिर काष्ठा mlx5_flow_cmds *mlx5_fs_cmd_get_stub_cmds(व्योम)
अणु
	वापस &mlx5_flow_cmd_stubs;
पूर्ण

स्थिर काष्ठा mlx5_flow_cmds *mlx5_fs_cmd_get_शेष(क्रमागत fs_flow_table_type type)
अणु
	चयन (type) अणु
	हाल FS_FT_NIC_RX:
	हाल FS_FT_ESW_EGRESS_ACL:
	हाल FS_FT_ESW_INGRESS_ACL:
	हाल FS_FT_FDB:
	हाल FS_FT_SNIFFER_RX:
	हाल FS_FT_SNIFFER_TX:
	हाल FS_FT_NIC_TX:
	हाल FS_FT_RDMA_RX:
	हाल FS_FT_RDMA_TX:
		वापस mlx5_fs_cmd_get_fw_cmds();
	शेष:
		वापस mlx5_fs_cmd_get_stub_cmds();
	पूर्ण
पूर्ण
