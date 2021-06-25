<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश "dr_types.h"

क्रमागत dr_action_करोमुख्य अणु
	DR_ACTION_DOMAIN_NIC_INGRESS,
	DR_ACTION_DOMAIN_NIC_EGRESS,
	DR_ACTION_DOMAIN_FDB_INGRESS,
	DR_ACTION_DOMAIN_FDB_EGRESS,
	DR_ACTION_DOMAIN_MAX,
पूर्ण;

क्रमागत dr_action_valid_state अणु
	DR_ACTION_STATE_ERR,
	DR_ACTION_STATE_NO_ACTION,
	DR_ACTION_STATE_REFORMAT,
	DR_ACTION_STATE_MODIFY_HDR,
	DR_ACTION_STATE_MODIFY_VLAN,
	DR_ACTION_STATE_NON_TERM,
	DR_ACTION_STATE_TERM,
	DR_ACTION_STATE_MAX,
पूर्ण;

अटल स्थिर क्रमागत dr_action_valid_state
next_action_state[DR_ACTION_DOMAIN_MAX][DR_ACTION_STATE_MAX][DR_ACTION_TYP_MAX] = अणु
	[DR_ACTION_DOMAIN_NIC_INGRESS] = अणु
		[DR_ACTION_STATE_NO_ACTION] = अणु
			[DR_ACTION_TYP_DROP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_QP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_FT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_TAG]		= DR_ACTION_STATE_NON_TERM,
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_NON_TERM,
			[DR_ACTION_TYP_TNL_L2_TO_L2]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_TNL_L3_TO_L2]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_MODIFY_HDR]	= DR_ACTION_STATE_MODIFY_HDR,
			[DR_ACTION_TYP_POP_VLAN]	= DR_ACTION_STATE_MODIFY_VLAN,
		पूर्ण,
		[DR_ACTION_STATE_REFORMAT] = अणु
			[DR_ACTION_TYP_DROP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_QP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_FT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_TAG]		= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_MODIFY_HDR]	= DR_ACTION_STATE_MODIFY_HDR,
			[DR_ACTION_TYP_POP_VLAN]	= DR_ACTION_STATE_MODIFY_VLAN,
		पूर्ण,
		[DR_ACTION_STATE_MODIFY_HDR] = अणु
			[DR_ACTION_TYP_DROP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_QP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_FT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_TAG]		= DR_ACTION_STATE_MODIFY_HDR,
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_MODIFY_HDR,
		पूर्ण,
		[DR_ACTION_STATE_MODIFY_VLAN] = अणु
			[DR_ACTION_TYP_DROP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_QP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_FT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_TAG]		= DR_ACTION_STATE_MODIFY_VLAN,
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_MODIFY_VLAN,
			[DR_ACTION_TYP_POP_VLAN]	= DR_ACTION_STATE_MODIFY_VLAN,
			[DR_ACTION_TYP_MODIFY_HDR]	= DR_ACTION_STATE_MODIFY_HDR,
		पूर्ण,
		[DR_ACTION_STATE_NON_TERM] = अणु
			[DR_ACTION_TYP_DROP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_QP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_FT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_TAG]		= DR_ACTION_STATE_NON_TERM,
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_NON_TERM,
			[DR_ACTION_TYP_TNL_L2_TO_L2]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_TNL_L3_TO_L2]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_MODIFY_HDR]	= DR_ACTION_STATE_MODIFY_HDR,
			[DR_ACTION_TYP_POP_VLAN]	= DR_ACTION_STATE_MODIFY_VLAN,
		पूर्ण,
		[DR_ACTION_STATE_TERM] = अणु
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_TERM,
		पूर्ण,
	पूर्ण,
	[DR_ACTION_DOMAIN_NIC_EGRESS] = अणु
		[DR_ACTION_STATE_NO_ACTION] = अणु
			[DR_ACTION_TYP_DROP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_FT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_NON_TERM,
			[DR_ACTION_TYP_L2_TO_TNL_L2]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_L2_TO_TNL_L3]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_MODIFY_HDR]	= DR_ACTION_STATE_MODIFY_HDR,
			[DR_ACTION_TYP_PUSH_VLAN]	= DR_ACTION_STATE_MODIFY_VLAN,
		पूर्ण,
		[DR_ACTION_STATE_REFORMAT] = अणु
			[DR_ACTION_TYP_DROP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_FT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_REFORMAT,
		पूर्ण,
		[DR_ACTION_STATE_MODIFY_HDR] = अणु
			[DR_ACTION_TYP_DROP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_FT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_MODIFY_HDR,
			[DR_ACTION_TYP_L2_TO_TNL_L2]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_L2_TO_TNL_L3]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_PUSH_VLAN]	= DR_ACTION_STATE_MODIFY_VLAN,
		पूर्ण,
		[DR_ACTION_STATE_MODIFY_VLAN] = अणु
			[DR_ACTION_TYP_DROP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_FT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_MODIFY_VLAN,
			[DR_ACTION_TYP_PUSH_VLAN]	= DR_ACTION_STATE_MODIFY_VLAN,
			[DR_ACTION_TYP_L2_TO_TNL_L2]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_L2_TO_TNL_L3]	= DR_ACTION_STATE_REFORMAT,
		पूर्ण,
		[DR_ACTION_STATE_NON_TERM] = अणु
			[DR_ACTION_TYP_DROP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_FT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_NON_TERM,
			[DR_ACTION_TYP_L2_TO_TNL_L2]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_L2_TO_TNL_L3]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_MODIFY_HDR]	= DR_ACTION_STATE_MODIFY_HDR,
			[DR_ACTION_TYP_PUSH_VLAN]	= DR_ACTION_STATE_MODIFY_VLAN,
		पूर्ण,
		[DR_ACTION_STATE_TERM] = अणु
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_TERM,
		पूर्ण,
	पूर्ण,
	[DR_ACTION_DOMAIN_FDB_INGRESS] = अणु
		[DR_ACTION_STATE_NO_ACTION] = अणु
			[DR_ACTION_TYP_DROP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_FT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_NON_TERM,
			[DR_ACTION_TYP_TNL_L2_TO_L2]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_TNL_L3_TO_L2]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_MODIFY_HDR]	= DR_ACTION_STATE_MODIFY_HDR,
			[DR_ACTION_TYP_POP_VLAN]	= DR_ACTION_STATE_MODIFY_VLAN,
			[DR_ACTION_TYP_VPORT]		= DR_ACTION_STATE_TERM,
		पूर्ण,
		[DR_ACTION_STATE_REFORMAT] = अणु
			[DR_ACTION_TYP_DROP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_FT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_MODIFY_HDR]	= DR_ACTION_STATE_MODIFY_HDR,
			[DR_ACTION_TYP_POP_VLAN]	= DR_ACTION_STATE_MODIFY_VLAN,
			[DR_ACTION_TYP_VPORT]		= DR_ACTION_STATE_TERM,
		पूर्ण,
		[DR_ACTION_STATE_MODIFY_HDR] = अणु
			[DR_ACTION_TYP_DROP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_FT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_MODIFY_HDR,
			[DR_ACTION_TYP_VPORT]		= DR_ACTION_STATE_TERM,
		पूर्ण,
		[DR_ACTION_STATE_MODIFY_VLAN] = अणु
			[DR_ACTION_TYP_DROP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_FT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_POP_VLAN]	= DR_ACTION_STATE_MODIFY_VLAN,
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_MODIFY_VLAN,
			[DR_ACTION_TYP_VPORT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_MODIFY_HDR]	= DR_ACTION_STATE_MODIFY_HDR,
		पूर्ण,
		[DR_ACTION_STATE_NON_TERM] = अणु
			[DR_ACTION_TYP_DROP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_FT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_NON_TERM,
			[DR_ACTION_TYP_TNL_L2_TO_L2]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_TNL_L3_TO_L2]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_MODIFY_HDR]	= DR_ACTION_STATE_MODIFY_HDR,
			[DR_ACTION_TYP_POP_VLAN]	= DR_ACTION_STATE_MODIFY_VLAN,
			[DR_ACTION_TYP_VPORT]		= DR_ACTION_STATE_TERM,
		पूर्ण,
		[DR_ACTION_STATE_TERM] = अणु
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_TERM,
		पूर्ण,
	पूर्ण,
	[DR_ACTION_DOMAIN_FDB_EGRESS] = अणु
		[DR_ACTION_STATE_NO_ACTION] = अणु
			[DR_ACTION_TYP_DROP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_FT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_NON_TERM,
			[DR_ACTION_TYP_MODIFY_HDR]	= DR_ACTION_STATE_MODIFY_HDR,
			[DR_ACTION_TYP_L2_TO_TNL_L2]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_L2_TO_TNL_L3]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_PUSH_VLAN]	= DR_ACTION_STATE_MODIFY_VLAN,
			[DR_ACTION_TYP_VPORT]		= DR_ACTION_STATE_TERM,
		पूर्ण,
		[DR_ACTION_STATE_REFORMAT] = अणु
			[DR_ACTION_TYP_DROP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_FT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_VPORT]		= DR_ACTION_STATE_TERM,
		पूर्ण,
		[DR_ACTION_STATE_MODIFY_HDR] = अणु
			[DR_ACTION_TYP_DROP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_FT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_MODIFY_HDR,
			[DR_ACTION_TYP_L2_TO_TNL_L2]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_L2_TO_TNL_L3]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_PUSH_VLAN]	= DR_ACTION_STATE_MODIFY_VLAN,
			[DR_ACTION_TYP_VPORT]		= DR_ACTION_STATE_TERM,
		पूर्ण,
		[DR_ACTION_STATE_MODIFY_VLAN] = अणु
			[DR_ACTION_TYP_DROP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_FT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_PUSH_VLAN]	= DR_ACTION_STATE_MODIFY_VLAN,
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_MODIFY_VLAN,
			[DR_ACTION_TYP_L2_TO_TNL_L2]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_L2_TO_TNL_L3]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_VPORT]		= DR_ACTION_STATE_TERM,
		पूर्ण,
		[DR_ACTION_STATE_NON_TERM] = अणु
			[DR_ACTION_TYP_DROP]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_FT]		= DR_ACTION_STATE_TERM,
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_NON_TERM,
			[DR_ACTION_TYP_MODIFY_HDR]	= DR_ACTION_STATE_MODIFY_HDR,
			[DR_ACTION_TYP_L2_TO_TNL_L2]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_L2_TO_TNL_L3]	= DR_ACTION_STATE_REFORMAT,
			[DR_ACTION_TYP_PUSH_VLAN]	= DR_ACTION_STATE_MODIFY_VLAN,
			[DR_ACTION_TYP_VPORT]		= DR_ACTION_STATE_TERM,
		पूर्ण,
		[DR_ACTION_STATE_TERM] = अणु
			[DR_ACTION_TYP_CTR]		= DR_ACTION_STATE_TERM,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक
dr_action_reक्रमmat_to_action_type(क्रमागत mlx5dr_action_reक्रमmat_type reक्रमmat_type,
				  क्रमागत mlx5dr_action_type *action_type)
अणु
	चयन (reक्रमmat_type) अणु
	हाल DR_ACTION_REFORMAT_TYP_TNL_L2_TO_L2:
		*action_type = DR_ACTION_TYP_TNL_L2_TO_L2;
		अवरोध;
	हाल DR_ACTION_REFORMAT_TYP_L2_TO_TNL_L2:
		*action_type = DR_ACTION_TYP_L2_TO_TNL_L2;
		अवरोध;
	हाल DR_ACTION_REFORMAT_TYP_TNL_L3_TO_L2:
		*action_type = DR_ACTION_TYP_TNL_L3_TO_L2;
		अवरोध;
	हाल DR_ACTION_REFORMAT_TYP_L2_TO_TNL_L3:
		*action_type = DR_ACTION_TYP_L2_TO_TNL_L3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Apply the actions on the rule STE array starting from the last_ste.
 * Actions might require more than one STE, new_num_stes will वापस
 * the new size of the STEs array, rule with actions.
 */
अटल व्योम dr_actions_apply(काष्ठा mlx5dr_करोमुख्य *dmn,
			     क्रमागत mlx5dr_ste_entry_type ste_type,
			     u8 *action_type_set,
			     u8 *last_ste,
			     काष्ठा mlx5dr_ste_actions_attr *attr,
			     u32 *new_num_stes)
अणु
	काष्ठा mlx5dr_ste_ctx *ste_ctx = dmn->ste_ctx;
	u32 added_stes = 0;

	अगर (ste_type == MLX5DR_STE_TYPE_RX)
		mlx5dr_ste_set_actions_rx(ste_ctx, dmn, action_type_set,
					  last_ste, attr, &added_stes);
	अन्यथा
		mlx5dr_ste_set_actions_tx(ste_ctx, dmn, action_type_set,
					  last_ste, attr, &added_stes);

	*new_num_stes += added_stes;
पूर्ण

अटल क्रमागत dr_action_करोमुख्य
dr_action_get_action_करोमुख्य(क्रमागत mlx5dr_करोमुख्य_type करोमुख्य,
			    क्रमागत mlx5dr_ste_entry_type ste_type)
अणु
	चयन (करोमुख्य) अणु
	हाल MLX5DR_DOMAIN_TYPE_NIC_RX:
		वापस DR_ACTION_DOMAIN_NIC_INGRESS;
	हाल MLX5DR_DOMAIN_TYPE_NIC_TX:
		वापस DR_ACTION_DOMAIN_NIC_EGRESS;
	हाल MLX5DR_DOMAIN_TYPE_FDB:
		अगर (ste_type == MLX5DR_STE_TYPE_RX)
			वापस DR_ACTION_DOMAIN_FDB_INGRESS;
		वापस DR_ACTION_DOMAIN_FDB_EGRESS;
	शेष:
		WARN_ON(true);
		वापस DR_ACTION_DOMAIN_MAX;
	पूर्ण
पूर्ण

अटल
पूर्णांक dr_action_validate_and_get_next_state(क्रमागत dr_action_करोमुख्य action_करोमुख्य,
					  u32 action_type,
					  u32 *state)
अणु
	u32 cur_state = *state;

	/* Check action state machine is valid */
	*state = next_action_state[action_करोमुख्य][cur_state][action_type];

	अगर (*state == DR_ACTION_STATE_ERR)
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल पूर्णांक dr_action_handle_cs_recalc(काष्ठा mlx5dr_करोमुख्य *dmn,
				      काष्ठा mlx5dr_action *dest_action,
				      u64 *final_icm_addr)
अणु
	पूर्णांक ret;

	चयन (dest_action->action_type) अणु
	हाल DR_ACTION_TYP_FT:
		/* Allow destination flow table only अगर table is a terminating
		 * table, since there is an *assumption* that in such हाल FW
		 * will recalculate the CS.
		 */
		अगर (dest_action->dest_tbl->is_fw_tbl) अणु
			*final_icm_addr = dest_action->dest_tbl->fw_tbl.rx_icm_addr;
		पूर्ण अन्यथा अणु
			mlx5dr_dbg(dmn,
				   "Destination FT should be terminating when modify TTL is used\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	हाल DR_ACTION_TYP_VPORT:
		/* If destination is vport we will get the FW flow table
		 * that recalculates the CS and क्रमwards to the vport.
		 */
		ret = mlx5dr_करोमुख्य_cache_get_recalc_cs_ft_addr(dest_action->vport->dmn,
								dest_action->vport->caps->num,
								final_icm_addr);
		अगर (ret) अणु
			mlx5dr_err(dmn, "Failed to get FW cs recalc flow table\n");
			वापस ret;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा WITH_VLAN_NUM_HW_ACTIONS 6

पूर्णांक mlx5dr_actions_build_ste_arr(काष्ठा mlx5dr_matcher *matcher,
				 काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
				 काष्ठा mlx5dr_action *actions[],
				 u32 num_actions,
				 u8 *ste_arr,
				 u32 *new_hw_ste_arr_sz)
अणु
	काष्ठा mlx5dr_करोमुख्य_rx_tx *nic_dmn = nic_matcher->nic_tbl->nic_dmn;
	bool rx_rule = nic_dmn->ste_type == MLX5DR_STE_TYPE_RX;
	काष्ठा mlx5dr_करोमुख्य *dmn = matcher->tbl->dmn;
	u8 action_type_set[DR_ACTION_TYP_MAX] = अणुपूर्ण;
	काष्ठा mlx5dr_ste_actions_attr attr = अणुपूर्ण;
	काष्ठा mlx5dr_action *dest_action = शून्य;
	u32 state = DR_ACTION_STATE_NO_ACTION;
	क्रमागत dr_action_करोमुख्य action_करोमुख्य;
	bool recalc_cs_required = false;
	u8 *last_ste;
	पूर्णांक i, ret;

	attr.gvmi = dmn->info.caps.gvmi;
	attr.hit_gvmi = dmn->info.caps.gvmi;
	attr.final_icm_addr = nic_dmn->शेष_icm_addr;
	action_करोमुख्य = dr_action_get_action_करोमुख्य(dmn->type, nic_dmn->ste_type);

	क्रम (i = 0; i < num_actions; i++) अणु
		काष्ठा mlx5dr_action_dest_tbl *dest_tbl;
		काष्ठा mlx5dr_action *action;
		पूर्णांक max_actions_type = 1;
		u32 action_type;

		action = actions[i];
		action_type = action->action_type;

		चयन (action_type) अणु
		हाल DR_ACTION_TYP_DROP:
			attr.final_icm_addr = nic_dmn->drop_icm_addr;
			अवरोध;
		हाल DR_ACTION_TYP_FT:
			dest_action = action;
			dest_tbl = action->dest_tbl;
			अगर (!dest_tbl->is_fw_tbl) अणु
				अगर (dest_tbl->tbl->dmn != dmn) अणु
					mlx5dr_err(dmn,
						   "Destination table belongs to a different domain\n");
					जाओ out_invalid_arg;
				पूर्ण
				अगर (dest_tbl->tbl->level <= matcher->tbl->level) अणु
					mlx5_core_warn_once(dmn->mdev,
							    "Connecting table to a lower/same level destination table\n");
					mlx5dr_dbg(dmn,
						   "Connecting table at level %d to a destination table at level %d\n",
						   matcher->tbl->level,
						   dest_tbl->tbl->level);
				पूर्ण
				attr.final_icm_addr = rx_rule ?
					dest_tbl->tbl->rx.s_anchor->chunk->icm_addr :
					dest_tbl->tbl->tx.s_anchor->chunk->icm_addr;
			पूर्ण अन्यथा अणु
				काष्ठा mlx5dr_cmd_query_flow_table_details output;
				पूर्णांक ret;

				/* get the relevant addresses */
				अगर (!action->dest_tbl->fw_tbl.rx_icm_addr) अणु
					ret = mlx5dr_cmd_query_flow_table(dmn->mdev,
									  dest_tbl->fw_tbl.type,
									  dest_tbl->fw_tbl.id,
									  &output);
					अगर (!ret) अणु
						dest_tbl->fw_tbl.tx_icm_addr =
							output.sw_owner_icm_root_1;
						dest_tbl->fw_tbl.rx_icm_addr =
							output.sw_owner_icm_root_0;
					पूर्ण अन्यथा अणु
						mlx5dr_err(dmn,
							   "Failed mlx5_cmd_query_flow_table ret: %d\n",
							   ret);
						वापस ret;
					पूर्ण
				पूर्ण
				attr.final_icm_addr = rx_rule ?
					dest_tbl->fw_tbl.rx_icm_addr :
					dest_tbl->fw_tbl.tx_icm_addr;
			पूर्ण
			अवरोध;
		हाल DR_ACTION_TYP_QP:
			mlx5dr_info(dmn, "Domain doesn't support QP\n");
			जाओ out_invalid_arg;
		हाल DR_ACTION_TYP_CTR:
			attr.ctr_id = action->ctr->ctr_id +
				action->ctr->offeset;
			अवरोध;
		हाल DR_ACTION_TYP_TAG:
			attr.flow_tag = action->flow_tag->flow_tag;
			अवरोध;
		हाल DR_ACTION_TYP_TNL_L2_TO_L2:
			अवरोध;
		हाल DR_ACTION_TYP_TNL_L3_TO_L2:
			attr.decap_index = action->reग_लिखो->index;
			attr.decap_actions = action->reग_लिखो->num_of_actions;
			attr.decap_with_vlan =
				attr.decap_actions == WITH_VLAN_NUM_HW_ACTIONS;
			अवरोध;
		हाल DR_ACTION_TYP_MODIFY_HDR:
			attr.modअगरy_index = action->reग_लिखो->index;
			attr.modअगरy_actions = action->reग_लिखो->num_of_actions;
			recalc_cs_required = action->reग_लिखो->modअगरy_ttl &&
					     !mlx5dr_ste_supp_ttl_cs_recalc(&dmn->info.caps);
			अवरोध;
		हाल DR_ACTION_TYP_L2_TO_TNL_L2:
		हाल DR_ACTION_TYP_L2_TO_TNL_L3:
			attr.reक्रमmat_size = action->reक्रमmat->reक्रमmat_size;
			attr.reक्रमmat_id = action->reक्रमmat->reक्रमmat_id;
			अवरोध;
		हाल DR_ACTION_TYP_VPORT:
			attr.hit_gvmi = action->vport->caps->vhca_gvmi;
			dest_action = action;
			अगर (rx_rule) अणु
				/* Loopback on WIRE vport is not supported */
				अगर (action->vport->caps->num == WIRE_PORT)
					जाओ out_invalid_arg;

				attr.final_icm_addr = action->vport->caps->icm_address_rx;
			पूर्ण अन्यथा अणु
				attr.final_icm_addr = action->vport->caps->icm_address_tx;
			पूर्ण
			अवरोध;
		हाल DR_ACTION_TYP_POP_VLAN:
			max_actions_type = MLX5DR_MAX_VLANS;
			attr.vlans.count++;
			अवरोध;
		हाल DR_ACTION_TYP_PUSH_VLAN:
			max_actions_type = MLX5DR_MAX_VLANS;
			अगर (attr.vlans.count == MLX5DR_MAX_VLANS)
				वापस -EINVAL;

			attr.vlans.headers[attr.vlans.count++] = action->push_vlan->vlan_hdr;
			अवरोध;
		शेष:
			जाओ out_invalid_arg;
		पूर्ण

		/* Check action duplication */
		अगर (++action_type_set[action_type] > max_actions_type) अणु
			mlx5dr_err(dmn, "Action type %d supports only max %d time(s)\n",
				   action_type, max_actions_type);
			जाओ out_invalid_arg;
		पूर्ण

		/* Check action state machine is valid */
		अगर (dr_action_validate_and_get_next_state(action_करोमुख्य,
							  action_type,
							  &state)) अणु
			mlx5dr_err(dmn, "Invalid action sequence provided\n");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	*new_hw_ste_arr_sz = nic_matcher->num_of_builders;
	last_ste = ste_arr + DR_STE_SIZE * (nic_matcher->num_of_builders - 1);

	/* Due to a HW bug in some devices, modअगरying TTL on RX flows will
	 * cause an incorrect checksum calculation. In this हाल we will
	 * use a FW table to recalculate.
	 */
	अगर (dmn->type == MLX5DR_DOMAIN_TYPE_FDB &&
	    rx_rule && recalc_cs_required && dest_action) अणु
		ret = dr_action_handle_cs_recalc(dmn, dest_action, &attr.final_icm_addr);
		अगर (ret) अणु
			mlx5dr_err(dmn,
				   "Failed to handle checksum recalculation err %d\n",
				   ret);
			वापस ret;
		पूर्ण
	पूर्ण

	dr_actions_apply(dmn,
			 nic_dmn->ste_type,
			 action_type_set,
			 last_ste,
			 &attr,
			 new_hw_ste_arr_sz);

	वापस 0;

out_invalid_arg:
	वापस -EINVAL;
पूर्ण

अटल अचिन्हित पूर्णांक action_size[DR_ACTION_TYP_MAX] = अणु
	[DR_ACTION_TYP_TNL_L2_TO_L2] = माप(काष्ठा mlx5dr_action_reक्रमmat),
	[DR_ACTION_TYP_L2_TO_TNL_L2] = माप(काष्ठा mlx5dr_action_reक्रमmat),
	[DR_ACTION_TYP_TNL_L3_TO_L2] = माप(काष्ठा mlx5dr_action_reग_लिखो),
	[DR_ACTION_TYP_L2_TO_TNL_L3] = माप(काष्ठा mlx5dr_action_reक्रमmat),
	[DR_ACTION_TYP_FT]           = माप(काष्ठा mlx5dr_action_dest_tbl),
	[DR_ACTION_TYP_CTR]          = माप(काष्ठा mlx5dr_action_ctr),
	[DR_ACTION_TYP_TAG]          = माप(काष्ठा mlx5dr_action_flow_tag),
	[DR_ACTION_TYP_MODIFY_HDR]   = माप(काष्ठा mlx5dr_action_reग_लिखो),
	[DR_ACTION_TYP_VPORT]        = माप(काष्ठा mlx5dr_action_vport),
	[DR_ACTION_TYP_PUSH_VLAN]    = माप(काष्ठा mlx5dr_action_push_vlan),
पूर्ण;

अटल काष्ठा mlx5dr_action *
dr_action_create_generic(क्रमागत mlx5dr_action_type action_type)
अणु
	काष्ठा mlx5dr_action *action;
	पूर्णांक extra_size;

	अगर (action_type < DR_ACTION_TYP_MAX)
		extra_size = action_size[action_type];
	अन्यथा
		वापस शून्य;

	action = kzalloc(माप(*action) + extra_size, GFP_KERNEL);
	अगर (!action)
		वापस शून्य;

	action->action_type = action_type;
	refcount_set(&action->refcount, 1);
	action->data = action + 1;

	वापस action;
पूर्ण

काष्ठा mlx5dr_action *mlx5dr_action_create_drop(व्योम)
अणु
	वापस dr_action_create_generic(DR_ACTION_TYP_DROP);
पूर्ण

काष्ठा mlx5dr_action *
mlx5dr_action_create_dest_table_num(काष्ठा mlx5dr_करोमुख्य *dmn, u32 table_num)
अणु
	काष्ठा mlx5dr_action *action;

	action = dr_action_create_generic(DR_ACTION_TYP_FT);
	अगर (!action)
		वापस शून्य;

	action->dest_tbl->is_fw_tbl = true;
	action->dest_tbl->fw_tbl.dmn = dmn;
	action->dest_tbl->fw_tbl.id = table_num;
	action->dest_tbl->fw_tbl.type = FS_FT_FDB;
	refcount_inc(&dmn->refcount);

	वापस action;
पूर्ण

काष्ठा mlx5dr_action *
mlx5dr_action_create_dest_table(काष्ठा mlx5dr_table *tbl)
अणु
	काष्ठा mlx5dr_action *action;

	refcount_inc(&tbl->refcount);

	action = dr_action_create_generic(DR_ACTION_TYP_FT);
	अगर (!action)
		जाओ dec_ref;

	action->dest_tbl->tbl = tbl;

	वापस action;

dec_ref:
	refcount_dec(&tbl->refcount);
	वापस शून्य;
पूर्ण

काष्ठा mlx5dr_action *
mlx5dr_action_create_mult_dest_tbl(काष्ठा mlx5dr_करोमुख्य *dmn,
				   काष्ठा mlx5dr_action_dest *dests,
				   u32 num_of_dests)
अणु
	काष्ठा mlx5dr_cmd_flow_destination_hw_info *hw_dests;
	काष्ठा mlx5dr_action **ref_actions;
	काष्ठा mlx5dr_action *action;
	bool reक्रमmat_req = false;
	u32 num_of_ref = 0;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (dmn->type != MLX5DR_DOMAIN_TYPE_FDB) अणु
		mlx5dr_err(dmn, "Multiple destination support is for FDB only\n");
		वापस शून्य;
	पूर्ण

	hw_dests = kzalloc(माप(*hw_dests) * num_of_dests, GFP_KERNEL);
	अगर (!hw_dests)
		वापस शून्य;

	ref_actions = kzalloc(माप(*ref_actions) * num_of_dests * 2, GFP_KERNEL);
	अगर (!ref_actions)
		जाओ मुक्त_hw_dests;

	क्रम (i = 0; i < num_of_dests; i++) अणु
		काष्ठा mlx5dr_action *reक्रमmat_action = dests[i].reक्रमmat;
		काष्ठा mlx5dr_action *dest_action = dests[i].dest;

		ref_actions[num_of_ref++] = dest_action;

		चयन (dest_action->action_type) अणु
		हाल DR_ACTION_TYP_VPORT:
			hw_dests[i].vport.flags = MLX5_FLOW_DEST_VPORT_VHCA_ID;
			hw_dests[i].type = MLX5_FLOW_DESTINATION_TYPE_VPORT;
			hw_dests[i].vport.num = dest_action->vport->caps->num;
			hw_dests[i].vport.vhca_id = dest_action->vport->caps->vhca_gvmi;
			अगर (reक्रमmat_action) अणु
				reक्रमmat_req = true;
				hw_dests[i].vport.reक्रमmat_id =
					reक्रमmat_action->reक्रमmat->reक्रमmat_id;
				ref_actions[num_of_ref++] = reक्रमmat_action;
				hw_dests[i].vport.flags |= MLX5_FLOW_DEST_VPORT_REFORMAT_ID;
			पूर्ण
			अवरोध;

		हाल DR_ACTION_TYP_FT:
			hw_dests[i].type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
			अगर (dest_action->dest_tbl->is_fw_tbl)
				hw_dests[i].ft_id = dest_action->dest_tbl->fw_tbl.id;
			अन्यथा
				hw_dests[i].ft_id = dest_action->dest_tbl->tbl->table_id;
			अवरोध;

		शेष:
			mlx5dr_dbg(dmn, "Invalid multiple destinations action\n");
			जाओ मुक्त_ref_actions;
		पूर्ण
	पूर्ण

	action = dr_action_create_generic(DR_ACTION_TYP_FT);
	अगर (!action)
		जाओ मुक्त_ref_actions;

	ret = mlx5dr_fw_create_md_tbl(dmn,
				      hw_dests,
				      num_of_dests,
				      reक्रमmat_req,
				      &action->dest_tbl->fw_tbl.id,
				      &action->dest_tbl->fw_tbl.group_id);
	अगर (ret)
		जाओ मुक्त_action;

	refcount_inc(&dmn->refcount);

	क्रम (i = 0; i < num_of_ref; i++)
		refcount_inc(&ref_actions[i]->refcount);

	action->dest_tbl->is_fw_tbl = true;
	action->dest_tbl->fw_tbl.dmn = dmn;
	action->dest_tbl->fw_tbl.type = FS_FT_FDB;
	action->dest_tbl->fw_tbl.ref_actions = ref_actions;
	action->dest_tbl->fw_tbl.num_of_ref_actions = num_of_ref;

	kमुक्त(hw_dests);

	वापस action;

मुक्त_action:
	kमुक्त(action);
मुक्त_ref_actions:
	kमुक्त(ref_actions);
मुक्त_hw_dests:
	kमुक्त(hw_dests);
	वापस शून्य;
पूर्ण

काष्ठा mlx5dr_action *
mlx5dr_action_create_dest_flow_fw_table(काष्ठा mlx5dr_करोमुख्य *dmn,
					काष्ठा mlx5_flow_table *ft)
अणु
	काष्ठा mlx5dr_action *action;

	action = dr_action_create_generic(DR_ACTION_TYP_FT);
	अगर (!action)
		वापस शून्य;

	action->dest_tbl->is_fw_tbl = 1;
	action->dest_tbl->fw_tbl.type = ft->type;
	action->dest_tbl->fw_tbl.id = ft->id;
	action->dest_tbl->fw_tbl.dmn = dmn;

	refcount_inc(&dmn->refcount);

	वापस action;
पूर्ण

काष्ठा mlx5dr_action *
mlx5dr_action_create_flow_counter(u32 counter_id)
अणु
	काष्ठा mlx5dr_action *action;

	action = dr_action_create_generic(DR_ACTION_TYP_CTR);
	अगर (!action)
		वापस शून्य;

	action->ctr->ctr_id = counter_id;

	वापस action;
पूर्ण

काष्ठा mlx5dr_action *mlx5dr_action_create_tag(u32 tag_value)
अणु
	काष्ठा mlx5dr_action *action;

	action = dr_action_create_generic(DR_ACTION_TYP_TAG);
	अगर (!action)
		वापस शून्य;

	action->flow_tag->flow_tag = tag_value & 0xffffff;

	वापस action;
पूर्ण

अटल पूर्णांक
dr_action_verअगरy_reक्रमmat_params(क्रमागत mlx5dr_action_type reक्रमmat_type,
				 काष्ठा mlx5dr_करोमुख्य *dmn,
				 माप_प्रकार data_sz,
				 व्योम *data)
अणु
	अगर ((!data && data_sz) || (data && !data_sz) || reक्रमmat_type >
		DR_ACTION_TYP_L2_TO_TNL_L3) अणु
		mlx5dr_dbg(dmn, "Invalid reformat parameter!\n");
		जाओ out_err;
	पूर्ण

	अगर (dmn->type == MLX5DR_DOMAIN_TYPE_FDB)
		वापस 0;

	अगर (dmn->type == MLX5DR_DOMAIN_TYPE_NIC_RX) अणु
		अगर (reक्रमmat_type != DR_ACTION_TYP_TNL_L2_TO_L2 &&
		    reक्रमmat_type != DR_ACTION_TYP_TNL_L3_TO_L2) अणु
			mlx5dr_dbg(dmn, "Action reformat type not support on RX domain\n");
			जाओ out_err;
		पूर्ण
	पूर्ण अन्यथा अगर (dmn->type == MLX5DR_DOMAIN_TYPE_NIC_TX) अणु
		अगर (reक्रमmat_type != DR_ACTION_TYP_L2_TO_TNL_L2 &&
		    reक्रमmat_type != DR_ACTION_TYP_L2_TO_TNL_L3) अणु
			mlx5dr_dbg(dmn, "Action reformat type not support on TX domain\n");
			जाओ out_err;
		पूर्ण
	पूर्ण

	वापस 0;

out_err:
	वापस -EINVAL;
पूर्ण

#घोषणा ACTION_CACHE_LINE_SIZE 64

अटल पूर्णांक
dr_action_create_reक्रमmat_action(काष्ठा mlx5dr_करोमुख्य *dmn,
				 माप_प्रकार data_sz, व्योम *data,
				 काष्ठा mlx5dr_action *action)
अणु
	u32 reक्रमmat_id;
	पूर्णांक ret;

	चयन (action->action_type) अणु
	हाल DR_ACTION_TYP_L2_TO_TNL_L2:
	हाल DR_ACTION_TYP_L2_TO_TNL_L3:
	अणु
		क्रमागत mlx5_reक्रमmat_ctx_type rt;

		अगर (action->action_type == DR_ACTION_TYP_L2_TO_TNL_L2)
			rt = MLX5_REFORMAT_TYPE_L2_TO_L2_TUNNEL;
		अन्यथा
			rt = MLX5_REFORMAT_TYPE_L2_TO_L3_TUNNEL;

		ret = mlx5dr_cmd_create_reक्रमmat_ctx(dmn->mdev, rt, data_sz, data,
						     &reक्रमmat_id);
		अगर (ret)
			वापस ret;

		action->reक्रमmat->reक्रमmat_id = reक्रमmat_id;
		action->reक्रमmat->reक्रमmat_size = data_sz;
		वापस 0;
	पूर्ण
	हाल DR_ACTION_TYP_TNL_L2_TO_L2:
	अणु
		वापस 0;
	पूर्ण
	हाल DR_ACTION_TYP_TNL_L3_TO_L2:
	अणु
		u8 hw_actions[ACTION_CACHE_LINE_SIZE] = अणुपूर्ण;
		पूर्णांक ret;

		ret = mlx5dr_ste_set_action_decap_l3_list(dmn->ste_ctx,
							  data, data_sz,
							  hw_actions,
							  ACTION_CACHE_LINE_SIZE,
							  &action->reग_लिखो->num_of_actions);
		अगर (ret) अणु
			mlx5dr_dbg(dmn, "Failed creating decap l3 action list\n");
			वापस ret;
		पूर्ण

		action->reग_लिखो->chunk = mlx5dr_icm_alloc_chunk(dmn->action_icm_pool,
								DR_CHUNK_SIZE_8);
		अगर (!action->reग_लिखो->chunk) अणु
			mlx5dr_dbg(dmn, "Failed allocating modify header chunk\n");
			वापस -ENOMEM;
		पूर्ण

		action->reग_लिखो->data = (व्योम *)hw_actions;
		action->reग_लिखो->index = (action->reग_लिखो->chunk->icm_addr -
					 dmn->info.caps.hdr_modअगरy_icm_addr) /
					 ACTION_CACHE_LINE_SIZE;

		ret = mlx5dr_send_postsend_action(dmn, action);
		अगर (ret) अणु
			mlx5dr_dbg(dmn, "Writing decap l3 actions to ICM failed\n");
			mlx5dr_icm_मुक्त_chunk(action->reग_लिखो->chunk);
			वापस ret;
		पूर्ण
		वापस 0;
	पूर्ण
	शेष:
		mlx5dr_info(dmn, "Reformat type is not supported %d\n", action->action_type);
		वापस -EINVAL;
	पूर्ण
पूर्ण

#घोषणा CVLAN_ETHERTYPE 0x8100
#घोषणा SVLAN_ETHERTYPE 0x88a8

काष्ठा mlx5dr_action *mlx5dr_action_create_pop_vlan(व्योम)
अणु
	वापस dr_action_create_generic(DR_ACTION_TYP_POP_VLAN);
पूर्ण

काष्ठा mlx5dr_action *mlx5dr_action_create_push_vlan(काष्ठा mlx5dr_करोमुख्य *dmn,
						     __be32 vlan_hdr)
अणु
	u32 vlan_hdr_h = ntohl(vlan_hdr);
	u16 ethertype = vlan_hdr_h >> 16;
	काष्ठा mlx5dr_action *action;

	अगर (ethertype != SVLAN_ETHERTYPE && ethertype != CVLAN_ETHERTYPE) अणु
		mlx5dr_dbg(dmn, "Invalid vlan ethertype\n");
		वापस शून्य;
	पूर्ण

	action = dr_action_create_generic(DR_ACTION_TYP_PUSH_VLAN);
	अगर (!action)
		वापस शून्य;

	action->push_vlan->vlan_hdr = vlan_hdr_h;
	वापस action;
पूर्ण

काष्ठा mlx5dr_action *
mlx5dr_action_create_packet_reक्रमmat(काष्ठा mlx5dr_करोमुख्य *dmn,
				     क्रमागत mlx5dr_action_reक्रमmat_type reक्रमmat_type,
				     माप_प्रकार data_sz,
				     व्योम *data)
अणु
	क्रमागत mlx5dr_action_type action_type;
	काष्ठा mlx5dr_action *action;
	पूर्णांक ret;

	refcount_inc(&dmn->refcount);

	/* General checks */
	ret = dr_action_reक्रमmat_to_action_type(reक्रमmat_type, &action_type);
	अगर (ret) अणु
		mlx5dr_dbg(dmn, "Invalid reformat_type provided\n");
		जाओ dec_ref;
	पूर्ण

	ret = dr_action_verअगरy_reक्रमmat_params(action_type, dmn, data_sz, data);
	अगर (ret)
		जाओ dec_ref;

	action = dr_action_create_generic(action_type);
	अगर (!action)
		जाओ dec_ref;

	action->reक्रमmat->dmn = dmn;

	ret = dr_action_create_reक्रमmat_action(dmn,
					       data_sz,
					       data,
					       action);
	अगर (ret) अणु
		mlx5dr_dbg(dmn, "Failed creating reformat action %d\n", ret);
		जाओ मुक्त_action;
	पूर्ण

	वापस action;

मुक्त_action:
	kमुक्त(action);
dec_ref:
	refcount_dec(&dmn->refcount);
	वापस शून्य;
पूर्ण

अटल पूर्णांक
dr_action_modअगरy_sw_to_hw_add(काष्ठा mlx5dr_करोमुख्य *dmn,
			      __be64 *sw_action,
			      __be64 *hw_action,
			      स्थिर काष्ठा mlx5dr_ste_action_modअगरy_field **ret_hw_info)
अणु
	स्थिर काष्ठा mlx5dr_ste_action_modअगरy_field *hw_action_info;
	u8 max_length;
	u16 sw_field;
	u32 data;

	/* Get SW modअगरy action data */
	sw_field = MLX5_GET(set_action_in, sw_action, field);
	data = MLX5_GET(set_action_in, sw_action, data);

	/* Convert SW data to HW modअगरy action क्रमmat */
	hw_action_info = mlx5dr_ste_conv_modअगरy_hdr_sw_field(dmn->ste_ctx, sw_field);
	अगर (!hw_action_info) अणु
		mlx5dr_dbg(dmn, "Modify add action invalid field given\n");
		वापस -EINVAL;
	पूर्ण

	max_length = hw_action_info->end - hw_action_info->start + 1;

	mlx5dr_ste_set_action_add(dmn->ste_ctx,
				  hw_action,
				  hw_action_info->hw_field,
				  hw_action_info->start,
				  max_length,
				  data);

	*ret_hw_info = hw_action_info;

	वापस 0;
पूर्ण

अटल पूर्णांक
dr_action_modअगरy_sw_to_hw_set(काष्ठा mlx5dr_करोमुख्य *dmn,
			      __be64 *sw_action,
			      __be64 *hw_action,
			      स्थिर काष्ठा mlx5dr_ste_action_modअगरy_field **ret_hw_info)
अणु
	स्थिर काष्ठा mlx5dr_ste_action_modअगरy_field *hw_action_info;
	u8 offset, length, max_length;
	u16 sw_field;
	u32 data;

	/* Get SW modअगरy action data */
	length = MLX5_GET(set_action_in, sw_action, length);
	offset = MLX5_GET(set_action_in, sw_action, offset);
	sw_field = MLX5_GET(set_action_in, sw_action, field);
	data = MLX5_GET(set_action_in, sw_action, data);

	/* Convert SW data to HW modअगरy action क्रमmat */
	hw_action_info = mlx5dr_ste_conv_modअगरy_hdr_sw_field(dmn->ste_ctx, sw_field);
	अगर (!hw_action_info) अणु
		mlx5dr_dbg(dmn, "Modify set action invalid field given\n");
		वापस -EINVAL;
	पूर्ण

	/* PRM defines that length zero specअगरic length of 32bits */
	length = length ? length : 32;

	max_length = hw_action_info->end - hw_action_info->start + 1;

	अगर (length + offset > max_length) अणु
		mlx5dr_dbg(dmn, "Modify action length + offset exceeds limit\n");
		वापस -EINVAL;
	पूर्ण

	mlx5dr_ste_set_action_set(dmn->ste_ctx,
				  hw_action,
				  hw_action_info->hw_field,
				  hw_action_info->start + offset,
				  length,
				  data);

	*ret_hw_info = hw_action_info;

	वापस 0;
पूर्ण

अटल पूर्णांक
dr_action_modअगरy_sw_to_hw_copy(काष्ठा mlx5dr_करोमुख्य *dmn,
			       __be64 *sw_action,
			       __be64 *hw_action,
			       स्थिर काष्ठा mlx5dr_ste_action_modअगरy_field **ret_dst_hw_info,
			       स्थिर काष्ठा mlx5dr_ste_action_modअगरy_field **ret_src_hw_info)
अणु
	u8 src_offset, dst_offset, src_max_length, dst_max_length, length;
	स्थिर काष्ठा mlx5dr_ste_action_modअगरy_field *hw_dst_action_info;
	स्थिर काष्ठा mlx5dr_ste_action_modअगरy_field *hw_src_action_info;
	u16 src_field, dst_field;

	/* Get SW modअगरy action data */
	src_field = MLX5_GET(copy_action_in, sw_action, src_field);
	dst_field = MLX5_GET(copy_action_in, sw_action, dst_field);
	src_offset = MLX5_GET(copy_action_in, sw_action, src_offset);
	dst_offset = MLX5_GET(copy_action_in, sw_action, dst_offset);
	length = MLX5_GET(copy_action_in, sw_action, length);

	/* Convert SW data to HW modअगरy action क्रमmat */
	hw_src_action_info = mlx5dr_ste_conv_modअगरy_hdr_sw_field(dmn->ste_ctx, src_field);
	hw_dst_action_info = mlx5dr_ste_conv_modअगरy_hdr_sw_field(dmn->ste_ctx, dst_field);
	अगर (!hw_src_action_info || !hw_dst_action_info) अणु
		mlx5dr_dbg(dmn, "Modify copy action invalid field given\n");
		वापस -EINVAL;
	पूर्ण

	/* PRM defines that length zero specअगरic length of 32bits */
	length = length ? length : 32;

	src_max_length = hw_src_action_info->end -
			 hw_src_action_info->start + 1;
	dst_max_length = hw_dst_action_info->end -
			 hw_dst_action_info->start + 1;

	अगर (length + src_offset > src_max_length ||
	    length + dst_offset > dst_max_length) अणु
		mlx5dr_dbg(dmn, "Modify action length + offset exceeds limit\n");
		वापस -EINVAL;
	पूर्ण

	mlx5dr_ste_set_action_copy(dmn->ste_ctx,
				   hw_action,
				   hw_dst_action_info->hw_field,
				   hw_dst_action_info->start + dst_offset,
				   length,
				   hw_src_action_info->hw_field,
				   hw_src_action_info->start + src_offset);

	*ret_dst_hw_info = hw_dst_action_info;
	*ret_src_hw_info = hw_src_action_info;

	वापस 0;
पूर्ण

अटल पूर्णांक
dr_action_modअगरy_sw_to_hw(काष्ठा mlx5dr_करोमुख्य *dmn,
			  __be64 *sw_action,
			  __be64 *hw_action,
			  स्थिर काष्ठा mlx5dr_ste_action_modअगरy_field **ret_dst_hw_info,
			  स्थिर काष्ठा mlx5dr_ste_action_modअगरy_field **ret_src_hw_info)
अणु
	u8 action;
	पूर्णांक ret;

	*hw_action = 0;
	*ret_src_hw_info = शून्य;

	/* Get SW modअगरy action type */
	action = MLX5_GET(set_action_in, sw_action, action_type);

	चयन (action) अणु
	हाल MLX5_ACTION_TYPE_SET:
		ret = dr_action_modअगरy_sw_to_hw_set(dmn, sw_action,
						    hw_action,
						    ret_dst_hw_info);
		अवरोध;

	हाल MLX5_ACTION_TYPE_ADD:
		ret = dr_action_modअगरy_sw_to_hw_add(dmn, sw_action,
						    hw_action,
						    ret_dst_hw_info);
		अवरोध;

	हाल MLX5_ACTION_TYPE_COPY:
		ret = dr_action_modअगरy_sw_to_hw_copy(dmn, sw_action,
						     hw_action,
						     ret_dst_hw_info,
						     ret_src_hw_info);
		अवरोध;

	शेष:
		mlx5dr_info(dmn, "Unsupported action_type for modify action\n");
		ret = -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
dr_action_modअगरy_check_set_field_limitation(काष्ठा mlx5dr_action *action,
					    स्थिर __be64 *sw_action)
अणु
	u16 sw_field = MLX5_GET(set_action_in, sw_action, field);
	काष्ठा mlx5dr_करोमुख्य *dmn = action->reग_लिखो->dmn;

	अगर (sw_field == MLX5_ACTION_IN_FIELD_METADATA_REG_A) अणु
		action->reग_लिखो->allow_rx = 0;
		अगर (dmn->type != MLX5DR_DOMAIN_TYPE_NIC_TX) अणु
			mlx5dr_dbg(dmn, "Unsupported field %d for RX/FDB set action\n",
				   sw_field);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (sw_field == MLX5_ACTION_IN_FIELD_METADATA_REG_B) अणु
		action->reग_लिखो->allow_tx = 0;
		अगर (dmn->type != MLX5DR_DOMAIN_TYPE_NIC_RX) अणु
			mlx5dr_dbg(dmn, "Unsupported field %d for TX/FDB set action\n",
				   sw_field);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!action->reग_लिखो->allow_rx && !action->reग_लिखो->allow_tx) अणु
		mlx5dr_dbg(dmn, "Modify SET actions not supported on both RX and TX\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
dr_action_modअगरy_check_add_field_limitation(काष्ठा mlx5dr_action *action,
					    स्थिर __be64 *sw_action)
अणु
	u16 sw_field = MLX5_GET(set_action_in, sw_action, field);
	काष्ठा mlx5dr_करोमुख्य *dmn = action->reग_लिखो->dmn;

	अगर (sw_field != MLX5_ACTION_IN_FIELD_OUT_IP_TTL &&
	    sw_field != MLX5_ACTION_IN_FIELD_OUT_IPV6_HOPLIMIT &&
	    sw_field != MLX5_ACTION_IN_FIELD_OUT_TCP_SEQ_NUM &&
	    sw_field != MLX5_ACTION_IN_FIELD_OUT_TCP_ACK_NUM) अणु
		mlx5dr_dbg(dmn, "Unsupported field %d for add action\n",
			   sw_field);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
dr_action_modअगरy_check_copy_field_limitation(काष्ठा mlx5dr_action *action,
					     स्थिर __be64 *sw_action)
अणु
	काष्ठा mlx5dr_करोमुख्य *dmn = action->reग_लिखो->dmn;
	u16 sw_fields[2];
	पूर्णांक i;

	sw_fields[0] = MLX5_GET(copy_action_in, sw_action, src_field);
	sw_fields[1] = MLX5_GET(copy_action_in, sw_action, dst_field);

	क्रम (i = 0; i < 2; i++) अणु
		अगर (sw_fields[i] == MLX5_ACTION_IN_FIELD_METADATA_REG_A) अणु
			action->reग_लिखो->allow_rx = 0;
			अगर (dmn->type != MLX5DR_DOMAIN_TYPE_NIC_TX) अणु
				mlx5dr_dbg(dmn, "Unsupported field %d for RX/FDB set action\n",
					   sw_fields[i]);
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अगर (sw_fields[i] == MLX5_ACTION_IN_FIELD_METADATA_REG_B) अणु
			action->reग_लिखो->allow_tx = 0;
			अगर (dmn->type != MLX5DR_DOMAIN_TYPE_NIC_RX) अणु
				mlx5dr_dbg(dmn, "Unsupported field %d for TX/FDB set action\n",
					   sw_fields[i]);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!action->reग_लिखो->allow_rx && !action->reग_लिखो->allow_tx) अणु
		mlx5dr_dbg(dmn, "Modify copy actions not supported on both RX and TX\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
dr_action_modअगरy_check_field_limitation(काष्ठा mlx5dr_action *action,
					स्थिर __be64 *sw_action)
अणु
	काष्ठा mlx5dr_करोमुख्य *dmn = action->reग_लिखो->dmn;
	u8 action_type;
	पूर्णांक ret;

	action_type = MLX5_GET(set_action_in, sw_action, action_type);

	चयन (action_type) अणु
	हाल MLX5_ACTION_TYPE_SET:
		ret = dr_action_modअगरy_check_set_field_limitation(action,
								  sw_action);
		अवरोध;

	हाल MLX5_ACTION_TYPE_ADD:
		ret = dr_action_modअगरy_check_add_field_limitation(action,
								  sw_action);
		अवरोध;

	हाल MLX5_ACTION_TYPE_COPY:
		ret = dr_action_modअगरy_check_copy_field_limitation(action,
								   sw_action);
		अवरोध;

	शेष:
		mlx5dr_info(dmn, "Unsupported action %d modify action\n",
			    action_type);
		ret = -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool
dr_action_modअगरy_check_is_ttl_modअगरy(स्थिर व्योम *sw_action)
अणु
	u16 sw_field = MLX5_GET(set_action_in, sw_action, field);

	वापस sw_field == MLX5_ACTION_IN_FIELD_OUT_IP_TTL;
पूर्ण

अटल पूर्णांक dr_actions_convert_modअगरy_header(काष्ठा mlx5dr_action *action,
					    u32 max_hw_actions,
					    u32 num_sw_actions,
					    __be64 sw_actions[],
					    __be64 hw_actions[],
					    u32 *num_hw_actions,
					    bool *modअगरy_ttl)
अणु
	स्थिर काष्ठा mlx5dr_ste_action_modअगरy_field *hw_dst_action_info;
	स्थिर काष्ठा mlx5dr_ste_action_modअगरy_field *hw_src_action_info;
	काष्ठा mlx5dr_करोमुख्य *dmn = action->reग_लिखो->dmn;
	पूर्णांक ret, i, hw_idx = 0;
	__be64 *sw_action;
	__be64 hw_action;
	u16 hw_field = 0;
	u32 l3_type = 0;
	u32 l4_type = 0;

	*modअगरy_ttl = false;

	action->reग_लिखो->allow_rx = 1;
	action->reग_लिखो->allow_tx = 1;

	क्रम (i = 0; i < num_sw_actions; i++) अणु
		sw_action = &sw_actions[i];

		ret = dr_action_modअगरy_check_field_limitation(action,
							      sw_action);
		अगर (ret)
			वापस ret;

		अगर (!(*modअगरy_ttl))
			*modअगरy_ttl = dr_action_modअगरy_check_is_ttl_modअगरy(sw_action);

		/* Convert SW action to HW action */
		ret = dr_action_modअगरy_sw_to_hw(dmn,
						sw_action,
						&hw_action,
						&hw_dst_action_info,
						&hw_src_action_info);
		अगर (ret)
			वापस ret;

		/* Due to a HW limitation we cannot modअगरy 2 dअगरferent L3 types */
		अगर (l3_type && hw_dst_action_info->l3_type &&
		    hw_dst_action_info->l3_type != l3_type) अणु
			mlx5dr_dbg(dmn, "Action list can't support two different L3 types\n");
			वापस -EINVAL;
		पूर्ण
		अगर (hw_dst_action_info->l3_type)
			l3_type = hw_dst_action_info->l3_type;

		/* Due to a HW limitation we cannot modअगरy two dअगरferent L4 types */
		अगर (l4_type && hw_dst_action_info->l4_type &&
		    hw_dst_action_info->l4_type != l4_type) अणु
			mlx5dr_dbg(dmn, "Action list can't support two different L4 types\n");
			वापस -EINVAL;
		पूर्ण
		अगर (hw_dst_action_info->l4_type)
			l4_type = hw_dst_action_info->l4_type;

		/* HW पढ़ोs and executes two actions at once this means we
		 * need to create a gap अगर two actions access the same field
		 */
		अगर ((hw_idx % 2) && (hw_field == hw_dst_action_info->hw_field ||
				     (hw_src_action_info &&
				      hw_field == hw_src_action_info->hw_field))) अणु
			/* Check अगर after gap insertion the total number of HW
			 * modअगरy actions करोesn't exceeds the limit
			 */
			hw_idx++;
			अगर ((num_sw_actions + hw_idx - i) >= max_hw_actions) अणु
				mlx5dr_dbg(dmn, "Modify header action number exceeds HW limit\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		hw_field = hw_dst_action_info->hw_field;

		hw_actions[hw_idx] = hw_action;
		hw_idx++;
	पूर्ण

	*num_hw_actions = hw_idx;

	वापस 0;
पूर्ण

अटल पूर्णांक dr_action_create_modअगरy_action(काष्ठा mlx5dr_करोमुख्य *dmn,
					  माप_प्रकार actions_sz,
					  __be64 actions[],
					  काष्ठा mlx5dr_action *action)
अणु
	काष्ठा mlx5dr_icm_chunk *chunk;
	u32 max_hw_actions;
	u32 num_hw_actions;
	u32 num_sw_actions;
	__be64 *hw_actions;
	bool modअगरy_ttl;
	पूर्णांक ret;

	num_sw_actions = actions_sz / DR_MODIFY_ACTION_SIZE;
	max_hw_actions = mlx5dr_icm_pool_chunk_माप_प्रकारo_entries(DR_CHUNK_SIZE_16);

	अगर (num_sw_actions > max_hw_actions) अणु
		mlx5dr_dbg(dmn, "Max number of actions %d exceeds limit %d\n",
			   num_sw_actions, max_hw_actions);
		वापस -EINVAL;
	पूर्ण

	chunk = mlx5dr_icm_alloc_chunk(dmn->action_icm_pool, DR_CHUNK_SIZE_16);
	अगर (!chunk)
		वापस -ENOMEM;

	hw_actions = kसुस्मृति(1, max_hw_actions * DR_MODIFY_ACTION_SIZE, GFP_KERNEL);
	अगर (!hw_actions) अणु
		ret = -ENOMEM;
		जाओ मुक्त_chunk;
	पूर्ण

	ret = dr_actions_convert_modअगरy_header(action,
					       max_hw_actions,
					       num_sw_actions,
					       actions,
					       hw_actions,
					       &num_hw_actions,
					       &modअगरy_ttl);
	अगर (ret)
		जाओ मुक्त_hw_actions;

	action->reग_लिखो->chunk = chunk;
	action->reग_लिखो->modअगरy_ttl = modअगरy_ttl;
	action->reग_लिखो->data = (u8 *)hw_actions;
	action->reग_लिखो->num_of_actions = num_hw_actions;
	action->reग_लिखो->index = (chunk->icm_addr -
				  dmn->info.caps.hdr_modअगरy_icm_addr) /
				  ACTION_CACHE_LINE_SIZE;

	ret = mlx5dr_send_postsend_action(dmn, action);
	अगर (ret)
		जाओ मुक्त_hw_actions;

	वापस 0;

मुक्त_hw_actions:
	kमुक्त(hw_actions);
मुक्त_chunk:
	mlx5dr_icm_मुक्त_chunk(chunk);
	वापस ret;
पूर्ण

काष्ठा mlx5dr_action *
mlx5dr_action_create_modअगरy_header(काष्ठा mlx5dr_करोमुख्य *dmn,
				   u32 flags,
				   माप_प्रकार actions_sz,
				   __be64 actions[])
अणु
	काष्ठा mlx5dr_action *action;
	पूर्णांक ret = 0;

	refcount_inc(&dmn->refcount);

	अगर (actions_sz % DR_MODIFY_ACTION_SIZE) अणु
		mlx5dr_dbg(dmn, "Invalid modify actions size provided\n");
		जाओ dec_ref;
	पूर्ण

	action = dr_action_create_generic(DR_ACTION_TYP_MODIFY_HDR);
	अगर (!action)
		जाओ dec_ref;

	action->reग_लिखो->dmn = dmn;

	ret = dr_action_create_modअगरy_action(dmn,
					     actions_sz,
					     actions,
					     action);
	अगर (ret) अणु
		mlx5dr_dbg(dmn, "Failed creating modify header action %d\n", ret);
		जाओ मुक्त_action;
	पूर्ण

	वापस action;

मुक्त_action:
	kमुक्त(action);
dec_ref:
	refcount_dec(&dmn->refcount);
	वापस शून्य;
पूर्ण

काष्ठा mlx5dr_action *
mlx5dr_action_create_dest_vport(काष्ठा mlx5dr_करोमुख्य *dmn,
				u32 vport, u8 vhca_id_valid,
				u16 vhca_id)
अणु
	काष्ठा mlx5dr_cmd_vport_cap *vport_cap;
	काष्ठा mlx5dr_करोमुख्य *vport_dmn;
	काष्ठा mlx5dr_action *action;
	u8 peer_vport;

	peer_vport = vhca_id_valid && (vhca_id != dmn->info.caps.gvmi);
	vport_dmn = peer_vport ? dmn->peer_dmn : dmn;
	अगर (!vport_dmn) अणु
		mlx5dr_dbg(dmn, "No peer vport domain for given vhca_id\n");
		वापस शून्य;
	पूर्ण

	अगर (vport_dmn->type != MLX5DR_DOMAIN_TYPE_FDB) अणु
		mlx5dr_dbg(dmn, "Domain doesn't support vport actions\n");
		वापस शून्य;
	पूर्ण

	vport_cap = mlx5dr_get_vport_cap(&vport_dmn->info.caps, vport);
	अगर (!vport_cap) अणु
		mlx5dr_dbg(dmn, "Failed to get vport %d caps\n", vport);
		वापस शून्य;
	पूर्ण

	action = dr_action_create_generic(DR_ACTION_TYP_VPORT);
	अगर (!action)
		वापस शून्य;

	action->vport->dmn = vport_dmn;
	action->vport->caps = vport_cap;

	वापस action;
पूर्ण

पूर्णांक mlx5dr_action_destroy(काष्ठा mlx5dr_action *action)
अणु
	अगर (refcount_पढ़ो(&action->refcount) > 1)
		वापस -EBUSY;

	चयन (action->action_type) अणु
	हाल DR_ACTION_TYP_FT:
		अगर (action->dest_tbl->is_fw_tbl)
			refcount_dec(&action->dest_tbl->fw_tbl.dmn->refcount);
		अन्यथा
			refcount_dec(&action->dest_tbl->tbl->refcount);

		अगर (action->dest_tbl->is_fw_tbl &&
		    action->dest_tbl->fw_tbl.num_of_ref_actions) अणु
			काष्ठा mlx5dr_action **ref_actions;
			पूर्णांक i;

			ref_actions = action->dest_tbl->fw_tbl.ref_actions;
			क्रम (i = 0; i < action->dest_tbl->fw_tbl.num_of_ref_actions; i++)
				refcount_dec(&ref_actions[i]->refcount);

			kमुक्त(ref_actions);

			mlx5dr_fw_destroy_md_tbl(action->dest_tbl->fw_tbl.dmn,
						 action->dest_tbl->fw_tbl.id,
						 action->dest_tbl->fw_tbl.group_id);
		पूर्ण
		अवरोध;
	हाल DR_ACTION_TYP_TNL_L2_TO_L2:
		refcount_dec(&action->reक्रमmat->dmn->refcount);
		अवरोध;
	हाल DR_ACTION_TYP_TNL_L3_TO_L2:
		mlx5dr_icm_मुक्त_chunk(action->reग_लिखो->chunk);
		refcount_dec(&action->reग_लिखो->dmn->refcount);
		अवरोध;
	हाल DR_ACTION_TYP_L2_TO_TNL_L2:
	हाल DR_ACTION_TYP_L2_TO_TNL_L3:
		mlx5dr_cmd_destroy_reक्रमmat_ctx((action->reक्रमmat->dmn)->mdev,
						action->reक्रमmat->reक्रमmat_id);
		refcount_dec(&action->reक्रमmat->dmn->refcount);
		अवरोध;
	हाल DR_ACTION_TYP_MODIFY_HDR:
		mlx5dr_icm_मुक्त_chunk(action->reग_लिखो->chunk);
		kमुक्त(action->reग_लिखो->data);
		refcount_dec(&action->reग_लिखो->dmn->refcount);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	kमुक्त(action);
	वापस 0;
पूर्ण
