<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies */

#समावेश "mlx5_core.h"
#समावेश "fs_core.h"
#समावेश "fs_cmd.h"
#समावेश "mlx5dr.h"
#समावेश "fs_dr.h"

अटल bool mlx5_dr_is_fw_table(u32 flags)
अणु
	अगर (flags & MLX5_FLOW_TABLE_TERMINATION)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक mlx5_cmd_dr_update_root_ft(काष्ठा mlx5_flow_root_namespace *ns,
				      काष्ठा mlx5_flow_table *ft,
				      u32 underlay_qpn,
				      bool disconnect)
अणु
	वापस mlx5_fs_cmd_get_fw_cmds()->update_root_ft(ns, ft, underlay_qpn,
							 disconnect);
पूर्ण

अटल पूर्णांक set_miss_action(काष्ठा mlx5_flow_root_namespace *ns,
			   काष्ठा mlx5_flow_table *ft,
			   काष्ठा mlx5_flow_table *next_ft)
अणु
	काष्ठा mlx5dr_action *old_miss_action;
	काष्ठा mlx5dr_action *action = शून्य;
	काष्ठा mlx5dr_table *next_tbl;
	पूर्णांक err;

	next_tbl = next_ft ? next_ft->fs_dr_table.dr_table : शून्य;
	अगर (next_tbl) अणु
		action = mlx5dr_action_create_dest_table(next_tbl);
		अगर (!action)
			वापस -EINVAL;
	पूर्ण
	old_miss_action = ft->fs_dr_table.miss_action;
	err = mlx5dr_table_set_miss_action(ft->fs_dr_table.dr_table, action);
	अगर (err && action) अणु
		err = mlx5dr_action_destroy(action);
		अगर (err) अणु
			action = शून्य;
			mlx5_core_err(ns->dev, "Failed to destroy action (%d)\n",
				      err);
		पूर्ण
	पूर्ण
	ft->fs_dr_table.miss_action = action;
	अगर (old_miss_action) अणु
		err = mlx5dr_action_destroy(old_miss_action);
		अगर (err)
			mlx5_core_err(ns->dev, "Failed to destroy action (%d)\n",
				      err);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlx5_cmd_dr_create_flow_table(काष्ठा mlx5_flow_root_namespace *ns,
					 काष्ठा mlx5_flow_table *ft,
					 अचिन्हित पूर्णांक log_size,
					 काष्ठा mlx5_flow_table *next_ft)
अणु
	काष्ठा mlx5dr_table *tbl;
	u32 flags;
	पूर्णांक err;

	अगर (mlx5_dr_is_fw_table(ft->flags))
		वापस mlx5_fs_cmd_get_fw_cmds()->create_flow_table(ns, ft,
								    log_size,
								    next_ft);
	flags = ft->flags;
	/* turn off encap/decap अगर not supported क्रम sw-str by fw */
	अगर (!MLX5_CAP_FLOWTABLE(ns->dev, sw_owner_reक्रमmat_supported))
		flags = ft->flags & ~(MLX5_FLOW_TABLE_TUNNEL_EN_REFORMAT |
				      MLX5_FLOW_TABLE_TUNNEL_EN_DECAP);

	tbl = mlx5dr_table_create(ns->fs_dr_करोमुख्य.dr_करोमुख्य, ft->level, flags);
	अगर (!tbl) अणु
		mlx5_core_err(ns->dev, "Failed creating dr flow_table\n");
		वापस -EINVAL;
	पूर्ण

	ft->fs_dr_table.dr_table = tbl;
	ft->id = mlx5dr_table_get_id(tbl);

	अगर (next_ft) अणु
		err = set_miss_action(ns, ft, next_ft);
		अगर (err) अणु
			mlx5dr_table_destroy(tbl);
			ft->fs_dr_table.dr_table = शून्य;
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_cmd_dr_destroy_flow_table(काष्ठा mlx5_flow_root_namespace *ns,
					  काष्ठा mlx5_flow_table *ft)
अणु
	काष्ठा mlx5dr_action *action = ft->fs_dr_table.miss_action;
	पूर्णांक err;

	अगर (mlx5_dr_is_fw_table(ft->flags))
		वापस mlx5_fs_cmd_get_fw_cmds()->destroy_flow_table(ns, ft);

	err = mlx5dr_table_destroy(ft->fs_dr_table.dr_table);
	अगर (err) अणु
		mlx5_core_err(ns->dev, "Failed to destroy flow_table (%d)\n",
			      err);
		वापस err;
	पूर्ण
	अगर (action) अणु
		err = mlx5dr_action_destroy(action);
		अगर (err) अणु
			mlx5_core_err(ns->dev, "Failed to destroy action(%d)\n",
				      err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlx5_cmd_dr_modअगरy_flow_table(काष्ठा mlx5_flow_root_namespace *ns,
					 काष्ठा mlx5_flow_table *ft,
					 काष्ठा mlx5_flow_table *next_ft)
अणु
	वापस set_miss_action(ns, ft, next_ft);
पूर्ण

अटल पूर्णांक mlx5_cmd_dr_create_flow_group(काष्ठा mlx5_flow_root_namespace *ns,
					 काष्ठा mlx5_flow_table *ft,
					 u32 *in,
					 काष्ठा mlx5_flow_group *fg)
अणु
	काष्ठा mlx5dr_matcher *matcher;
	u32 priority = MLX5_GET(create_flow_group_in, in,
				start_flow_index);
	u8 match_criteria_enable = MLX5_GET(create_flow_group_in,
					    in,
					    match_criteria_enable);
	काष्ठा mlx5dr_match_parameters mask;

	अगर (mlx5_dr_is_fw_table(ft->flags))
		वापस mlx5_fs_cmd_get_fw_cmds()->create_flow_group(ns, ft, in,
								    fg);

	mask.match_buf = MLX5_ADDR_OF(create_flow_group_in,
				      in, match_criteria);
	mask.match_sz = माप(fg->mask.match_criteria);

	matcher = mlx5dr_matcher_create(ft->fs_dr_table.dr_table,
					priority,
					match_criteria_enable,
					&mask);
	अगर (!matcher) अणु
		mlx5_core_err(ns->dev, "Failed creating matcher\n");
		वापस -EINVAL;
	पूर्ण

	fg->fs_dr_matcher.dr_matcher = matcher;
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_cmd_dr_destroy_flow_group(काष्ठा mlx5_flow_root_namespace *ns,
					  काष्ठा mlx5_flow_table *ft,
					  काष्ठा mlx5_flow_group *fg)
अणु
	अगर (mlx5_dr_is_fw_table(ft->flags))
		वापस mlx5_fs_cmd_get_fw_cmds()->destroy_flow_group(ns, ft, fg);

	वापस mlx5dr_matcher_destroy(fg->fs_dr_matcher.dr_matcher);
पूर्ण

अटल काष्ठा mlx5dr_action *create_vport_action(काष्ठा mlx5dr_करोमुख्य *करोमुख्य,
						 काष्ठा mlx5_flow_rule *dst)
अणु
	काष्ठा mlx5_flow_destination *dest_attr = &dst->dest_attr;

	वापस mlx5dr_action_create_dest_vport(करोमुख्य, dest_attr->vport.num,
					       dest_attr->vport.flags &
					       MLX5_FLOW_DEST_VPORT_VHCA_ID,
					       dest_attr->vport.vhca_id);
पूर्ण

अटल काष्ठा mlx5dr_action *create_ft_action(काष्ठा mlx5dr_करोमुख्य *करोमुख्य,
					      काष्ठा mlx5_flow_rule *dst)
अणु
	काष्ठा mlx5_flow_table *dest_ft = dst->dest_attr.ft;

	अगर (mlx5_dr_is_fw_table(dest_ft->flags))
		वापस mlx5dr_action_create_dest_flow_fw_table(करोमुख्य, dest_ft);
	वापस mlx5dr_action_create_dest_table(dest_ft->fs_dr_table.dr_table);
पूर्ण

अटल काष्ठा mlx5dr_action *create_action_push_vlan(काष्ठा mlx5dr_करोमुख्य *करोमुख्य,
						     काष्ठा mlx5_fs_vlan *vlan)
अणु
	u16 n_ethtype = vlan->ethtype;
	u8  prio = vlan->prio;
	u16 vid = vlan->vid;
	u32 vlan_hdr;

	vlan_hdr = (u32)n_ethtype << 16 | (u32)(prio) << 12 |  (u32)vid;
	वापस mlx5dr_action_create_push_vlan(करोमुख्य, htonl(vlan_hdr));
पूर्ण

अटल bool contain_vport_reक्रमmat_action(काष्ठा mlx5_flow_rule *dst)
अणु
	वापस dst->dest_attr.type == MLX5_FLOW_DESTINATION_TYPE_VPORT &&
		dst->dest_attr.vport.flags & MLX5_FLOW_DEST_VPORT_REFORMAT_ID;
पूर्ण

#घोषणा MLX5_FLOW_CONTEXT_ACTION_MAX  20
अटल पूर्णांक mlx5_cmd_dr_create_fte(काष्ठा mlx5_flow_root_namespace *ns,
				  काष्ठा mlx5_flow_table *ft,
				  काष्ठा mlx5_flow_group *group,
				  काष्ठा fs_fte *fte)
अणु
	काष्ठा mlx5dr_करोमुख्य *करोमुख्य = ns->fs_dr_करोमुख्य.dr_करोमुख्य;
	काष्ठा mlx5dr_action_dest *term_actions;
	काष्ठा mlx5dr_match_parameters params;
	काष्ठा mlx5_core_dev *dev = ns->dev;
	काष्ठा mlx5dr_action **fs_dr_actions;
	काष्ठा mlx5dr_action *पंचांगp_action;
	काष्ठा mlx5dr_action **actions;
	bool delay_encap_set = false;
	काष्ठा mlx5dr_rule *rule;
	काष्ठा mlx5_flow_rule *dst;
	पूर्णांक fs_dr_num_actions = 0;
	पूर्णांक num_term_actions = 0;
	पूर्णांक num_actions = 0;
	माप_प्रकार match_sz;
	पूर्णांक err = 0;
	पूर्णांक i;

	अगर (mlx5_dr_is_fw_table(ft->flags))
		वापस mlx5_fs_cmd_get_fw_cmds()->create_fte(ns, ft, group, fte);

	actions = kसुस्मृति(MLX5_FLOW_CONTEXT_ACTION_MAX, माप(*actions),
			  GFP_KERNEL);
	अगर (!actions) अणु
		err = -ENOMEM;
		जाओ out_err;
	पूर्ण

	fs_dr_actions = kसुस्मृति(MLX5_FLOW_CONTEXT_ACTION_MAX,
				माप(*fs_dr_actions), GFP_KERNEL);
	अगर (!fs_dr_actions) अणु
		err = -ENOMEM;
		जाओ मुक्त_actions_alloc;
	पूर्ण

	term_actions = kसुस्मृति(MLX5_FLOW_CONTEXT_ACTION_MAX,
			       माप(*term_actions), GFP_KERNEL);
	अगर (!term_actions) अणु
		err = -ENOMEM;
		जाओ मुक्त_fs_dr_actions_alloc;
	पूर्ण

	match_sz = माप(fte->val);

	/* Drop reक्रमmat action bit अगर destination vport set with reक्रमmat */
	अगर (fte->action.action & MLX5_FLOW_CONTEXT_ACTION_FWD_DEST) अणु
		list_क्रम_each_entry(dst, &fte->node.children, node.list) अणु
			अगर (!contain_vport_reक्रमmat_action(dst))
				जारी;

			fte->action.action &= ~MLX5_FLOW_CONTEXT_ACTION_PACKET_REFORMAT;
			अवरोध;
		पूर्ण
	पूर्ण

	/* The order of the actions are must to be keep, only the following
	 * order is supported by SW steering:
	 * TX: modअगरy header -> push vlan -> encap
	 * RX: decap -> pop vlan -> modअगरy header
	 */
	अगर (fte->action.action & MLX5_FLOW_CONTEXT_ACTION_DECAP) अणु
		क्रमागत mlx5dr_action_reक्रमmat_type decap_type =
			DR_ACTION_REFORMAT_TYP_TNL_L2_TO_L2;

		पंचांगp_action = mlx5dr_action_create_packet_reक्रमmat(करोमुख्य,
								  decap_type, 0,
								  शून्य);
		अगर (!पंचांगp_action) अणु
			err = -ENOMEM;
			जाओ मुक्त_actions;
		पूर्ण
		fs_dr_actions[fs_dr_num_actions++] = पंचांगp_action;
		actions[num_actions++] = पंचांगp_action;
	पूर्ण

	अगर (fte->action.action & MLX5_FLOW_CONTEXT_ACTION_PACKET_REFORMAT) अणु
		bool is_decap = fte->action.pkt_reक्रमmat->reक्रमmat_type ==
			MLX5_REFORMAT_TYPE_L3_TUNNEL_TO_L2;

		अगर (is_decap)
			actions[num_actions++] =
				fte->action.pkt_reक्रमmat->action.dr_action;
		अन्यथा
			delay_encap_set = true;
	पूर्ण

	अगर (fte->action.action & MLX5_FLOW_CONTEXT_ACTION_VLAN_POP) अणु
		पंचांगp_action =
			mlx5dr_action_create_pop_vlan();
		अगर (!पंचांगp_action) अणु
			err = -ENOMEM;
			जाओ मुक्त_actions;
		पूर्ण
		fs_dr_actions[fs_dr_num_actions++] = पंचांगp_action;
		actions[num_actions++] = पंचांगp_action;
	पूर्ण

	अगर (fte->action.action & MLX5_FLOW_CONTEXT_ACTION_VLAN_POP_2) अणु
		पंचांगp_action =
			mlx5dr_action_create_pop_vlan();
		अगर (!पंचांगp_action) अणु
			err = -ENOMEM;
			जाओ मुक्त_actions;
		पूर्ण
		fs_dr_actions[fs_dr_num_actions++] = पंचांगp_action;
		actions[num_actions++] = पंचांगp_action;
	पूर्ण

	अगर (fte->action.action & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR)
		actions[num_actions++] =
			fte->action.modअगरy_hdr->action.dr_action;

	अगर (fte->action.action & MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH) अणु
		पंचांगp_action = create_action_push_vlan(करोमुख्य, &fte->action.vlan[0]);
		अगर (!पंचांगp_action) अणु
			err = -ENOMEM;
			जाओ मुक्त_actions;
		पूर्ण
		fs_dr_actions[fs_dr_num_actions++] = पंचांगp_action;
		actions[num_actions++] = पंचांगp_action;
	पूर्ण

	अगर (fte->action.action & MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH_2) अणु
		पंचांगp_action = create_action_push_vlan(करोमुख्य, &fte->action.vlan[1]);
		अगर (!पंचांगp_action) अणु
			err = -ENOMEM;
			जाओ मुक्त_actions;
		पूर्ण
		fs_dr_actions[fs_dr_num_actions++] = पंचांगp_action;
		actions[num_actions++] = पंचांगp_action;
	पूर्ण

	अगर (delay_encap_set)
		actions[num_actions++] =
			fte->action.pkt_reक्रमmat->action.dr_action;

	/* The order of the actions below is not important */

	अगर (fte->action.action & MLX5_FLOW_CONTEXT_ACTION_DROP) अणु
		पंचांगp_action = mlx5dr_action_create_drop();
		अगर (!पंचांगp_action) अणु
			err = -ENOMEM;
			जाओ मुक्त_actions;
		पूर्ण
		fs_dr_actions[fs_dr_num_actions++] = पंचांगp_action;
		term_actions[num_term_actions++].dest = पंचांगp_action;
	पूर्ण

	अगर (fte->flow_context.flow_tag) अणु
		पंचांगp_action =
			mlx5dr_action_create_tag(fte->flow_context.flow_tag);
		अगर (!पंचांगp_action) अणु
			err = -ENOMEM;
			जाओ मुक्त_actions;
		पूर्ण
		fs_dr_actions[fs_dr_num_actions++] = पंचांगp_action;
		actions[num_actions++] = पंचांगp_action;
	पूर्ण

	अगर (fte->action.action & MLX5_FLOW_CONTEXT_ACTION_FWD_DEST) अणु
		list_क्रम_each_entry(dst, &fte->node.children, node.list) अणु
			क्रमागत mlx5_flow_destination_type type = dst->dest_attr.type;
			u32 ft_id;

			अगर (num_actions == MLX5_FLOW_CONTEXT_ACTION_MAX ||
			    num_term_actions >= MLX5_FLOW_CONTEXT_ACTION_MAX) अणु
				err = -ENOSPC;
				जाओ मुक्त_actions;
			पूर्ण

			अगर (type == MLX5_FLOW_DESTINATION_TYPE_COUNTER)
				जारी;

			चयन (type) अणु
			हाल MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE:
				पंचांगp_action = create_ft_action(करोमुख्य, dst);
				अगर (!पंचांगp_action) अणु
					err = -ENOMEM;
					जाओ मुक्त_actions;
				पूर्ण
				fs_dr_actions[fs_dr_num_actions++] = पंचांगp_action;
				term_actions[num_term_actions++].dest = पंचांगp_action;
				अवरोध;
			हाल MLX5_FLOW_DESTINATION_TYPE_VPORT:
				पंचांगp_action = create_vport_action(करोमुख्य, dst);
				अगर (!पंचांगp_action) अणु
					err = -ENOMEM;
					जाओ मुक्त_actions;
				पूर्ण
				fs_dr_actions[fs_dr_num_actions++] = पंचांगp_action;
				term_actions[num_term_actions].dest = पंचांगp_action;

				अगर (dst->dest_attr.vport.flags &
				    MLX5_FLOW_DEST_VPORT_REFORMAT_ID)
					term_actions[num_term_actions].reक्रमmat =
						dst->dest_attr.vport.pkt_reक्रमmat->action.dr_action;

				num_term_actions++;
				अवरोध;
			हाल MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE_NUM:
				ft_id = dst->dest_attr.ft_num;
				पंचांगp_action = mlx5dr_action_create_dest_table_num(करोमुख्य,
										 ft_id);
				अगर (!पंचांगp_action) अणु
					err = -ENOMEM;
					जाओ मुक्त_actions;
				पूर्ण
				fs_dr_actions[fs_dr_num_actions++] = पंचांगp_action;
				term_actions[num_term_actions++].dest = पंचांगp_action;
				अवरोध;
			शेष:
				err = -EOPNOTSUPP;
				जाओ मुक्त_actions;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (fte->action.action & MLX5_FLOW_CONTEXT_ACTION_COUNT) अणु
		list_क्रम_each_entry(dst, &fte->node.children, node.list) अणु
			u32 id;

			अगर (dst->dest_attr.type !=
			    MLX5_FLOW_DESTINATION_TYPE_COUNTER)
				जारी;

			अगर (num_actions == MLX5_FLOW_CONTEXT_ACTION_MAX) अणु
				err = -ENOSPC;
				जाओ मुक्त_actions;
			पूर्ण

			id = dst->dest_attr.counter_id;
			पंचांगp_action =
				mlx5dr_action_create_flow_counter(id);
			अगर (!पंचांगp_action) अणु
				err = -ENOMEM;
				जाओ मुक्त_actions;
			पूर्ण

			fs_dr_actions[fs_dr_num_actions++] = पंचांगp_action;
			actions[num_actions++] = पंचांगp_action;
		पूर्ण
	पूर्ण

	params.match_sz = match_sz;
	params.match_buf = (u64 *)fte->val;
	अगर (num_term_actions == 1) अणु
		अगर (term_actions->reक्रमmat)
			actions[num_actions++] = term_actions->reक्रमmat;

		actions[num_actions++] = term_actions->dest;
	पूर्ण अन्यथा अगर (num_term_actions > 1) अणु
		पंचांगp_action = mlx5dr_action_create_mult_dest_tbl(करोमुख्य,
								term_actions,
								num_term_actions);
		अगर (!पंचांगp_action) अणु
			err = -EOPNOTSUPP;
			जाओ मुक्त_actions;
		पूर्ण
		fs_dr_actions[fs_dr_num_actions++] = पंचांगp_action;
		actions[num_actions++] = पंचांगp_action;
	पूर्ण

	rule = mlx5dr_rule_create(group->fs_dr_matcher.dr_matcher,
				  &params,
				  num_actions,
				  actions,
				  fte->flow_context.flow_source);
	अगर (!rule) अणु
		err = -EINVAL;
		जाओ मुक्त_actions;
	पूर्ण

	kमुक्त(term_actions);
	kमुक्त(actions);

	fte->fs_dr_rule.dr_rule = rule;
	fte->fs_dr_rule.num_actions = fs_dr_num_actions;
	fte->fs_dr_rule.dr_actions = fs_dr_actions;

	वापस 0;

मुक्त_actions:
	/* Free in reverse order to handle action dependencies */
	क्रम (i = fs_dr_num_actions - 1; i >= 0; i--)
		अगर (!IS_ERR_OR_शून्य(fs_dr_actions[i]))
			mlx5dr_action_destroy(fs_dr_actions[i]);

	kमुक्त(term_actions);
मुक्त_fs_dr_actions_alloc:
	kमुक्त(fs_dr_actions);
मुक्त_actions_alloc:
	kमुक्त(actions);
out_err:
	mlx5_core_err(dev, "Failed to create dr rule err(%d)\n", err);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_cmd_dr_packet_reक्रमmat_alloc(काष्ठा mlx5_flow_root_namespace *ns,
					     पूर्णांक reक्रमmat_type,
					     माप_प्रकार size,
					     व्योम *reक्रमmat_data,
					     क्रमागत mlx5_flow_namespace_type namespace,
					     काष्ठा mlx5_pkt_reक्रमmat *pkt_reक्रमmat)
अणु
	काष्ठा mlx5dr_करोमुख्य *dr_करोमुख्य = ns->fs_dr_करोमुख्य.dr_करोमुख्य;
	काष्ठा mlx5dr_action *action;
	पूर्णांक dr_reक्रमmat;

	चयन (reक्रमmat_type) अणु
	हाल MLX5_REFORMAT_TYPE_L2_TO_VXLAN:
	हाल MLX5_REFORMAT_TYPE_L2_TO_NVGRE:
	हाल MLX5_REFORMAT_TYPE_L2_TO_L2_TUNNEL:
		dr_reक्रमmat = DR_ACTION_REFORMAT_TYP_L2_TO_TNL_L2;
		अवरोध;
	हाल MLX5_REFORMAT_TYPE_L3_TUNNEL_TO_L2:
		dr_reक्रमmat = DR_ACTION_REFORMAT_TYP_TNL_L3_TO_L2;
		अवरोध;
	हाल MLX5_REFORMAT_TYPE_L2_TO_L3_TUNNEL:
		dr_reक्रमmat = DR_ACTION_REFORMAT_TYP_L2_TO_TNL_L3;
		अवरोध;
	शेष:
		mlx5_core_err(ns->dev, "Packet-reformat not supported(%d)\n",
			      reक्रमmat_type);
		वापस -EOPNOTSUPP;
	पूर्ण

	action = mlx5dr_action_create_packet_reक्रमmat(dr_करोमुख्य,
						      dr_reक्रमmat,
						      size,
						      reक्रमmat_data);
	अगर (!action) अणु
		mlx5_core_err(ns->dev, "Failed allocating packet-reformat action\n");
		वापस -EINVAL;
	पूर्ण

	pkt_reक्रमmat->action.dr_action = action;

	वापस 0;
पूर्ण

अटल व्योम mlx5_cmd_dr_packet_reक्रमmat_dealloc(काष्ठा mlx5_flow_root_namespace *ns,
						काष्ठा mlx5_pkt_reक्रमmat *pkt_reक्रमmat)
अणु
	mlx5dr_action_destroy(pkt_reक्रमmat->action.dr_action);
पूर्ण

अटल पूर्णांक mlx5_cmd_dr_modअगरy_header_alloc(काष्ठा mlx5_flow_root_namespace *ns,
					   u8 namespace, u8 num_actions,
					   व्योम *modअगरy_actions,
					   काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr)
अणु
	काष्ठा mlx5dr_करोमुख्य *dr_करोमुख्य = ns->fs_dr_करोमुख्य.dr_करोमुख्य;
	काष्ठा mlx5dr_action *action;
	माप_प्रकार actions_sz;

	actions_sz = MLX5_UN_SZ_BYTES(set_add_copy_action_in_स्वतः) *
		num_actions;
	action = mlx5dr_action_create_modअगरy_header(dr_करोमुख्य, 0,
						    actions_sz,
						    modअगरy_actions);
	अगर (!action) अणु
		mlx5_core_err(ns->dev, "Failed allocating modify-header action\n");
		वापस -EINVAL;
	पूर्ण

	modअगरy_hdr->action.dr_action = action;

	वापस 0;
पूर्ण

अटल व्योम mlx5_cmd_dr_modअगरy_header_dealloc(काष्ठा mlx5_flow_root_namespace *ns,
					      काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr)
अणु
	mlx5dr_action_destroy(modअगरy_hdr->action.dr_action);
पूर्ण

अटल पूर्णांक mlx5_cmd_dr_update_fte(काष्ठा mlx5_flow_root_namespace *ns,
				  काष्ठा mlx5_flow_table *ft,
				  काष्ठा mlx5_flow_group *group,
				  पूर्णांक modअगरy_mask,
				  काष्ठा fs_fte *fte)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक mlx5_cmd_dr_delete_fte(काष्ठा mlx5_flow_root_namespace *ns,
				  काष्ठा mlx5_flow_table *ft,
				  काष्ठा fs_fte *fte)
अणु
	काष्ठा mlx5_fs_dr_rule *rule = &fte->fs_dr_rule;
	पूर्णांक err;
	पूर्णांक i;

	अगर (mlx5_dr_is_fw_table(ft->flags))
		वापस mlx5_fs_cmd_get_fw_cmds()->delete_fte(ns, ft, fte);

	err = mlx5dr_rule_destroy(rule->dr_rule);
	अगर (err)
		वापस err;

	/* Free in reverse order to handle action dependencies */
	क्रम (i = rule->num_actions - 1; i >= 0; i--)
		अगर (!IS_ERR_OR_शून्य(rule->dr_actions[i]))
			mlx5dr_action_destroy(rule->dr_actions[i]);

	kमुक्त(rule->dr_actions);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_cmd_dr_set_peer(काष्ठा mlx5_flow_root_namespace *ns,
				काष्ठा mlx5_flow_root_namespace *peer_ns)
अणु
	काष्ठा mlx5dr_करोमुख्य *peer_करोमुख्य = शून्य;

	अगर (peer_ns)
		peer_करोमुख्य = peer_ns->fs_dr_करोमुख्य.dr_करोमुख्य;
	mlx5dr_करोमुख्य_set_peer(ns->fs_dr_करोमुख्य.dr_करोमुख्य,
			       peer_करोमुख्य);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_cmd_dr_create_ns(काष्ठा mlx5_flow_root_namespace *ns)
अणु
	ns->fs_dr_करोमुख्य.dr_करोमुख्य =
		mlx5dr_करोमुख्य_create(ns->dev,
				     MLX5DR_DOMAIN_TYPE_FDB);
	अगर (!ns->fs_dr_करोमुख्य.dr_करोमुख्य) अणु
		mlx5_core_err(ns->dev, "Failed to create dr flow namespace\n");
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_cmd_dr_destroy_ns(काष्ठा mlx5_flow_root_namespace *ns)
अणु
	वापस mlx5dr_करोमुख्य_destroy(ns->fs_dr_करोमुख्य.dr_करोमुख्य);
पूर्ण

bool mlx5_fs_dr_is_supported(काष्ठा mlx5_core_dev *dev)
अणु
	वापस mlx5dr_is_supported(dev);
पूर्ण

अटल स्थिर काष्ठा mlx5_flow_cmds mlx5_flow_cmds_dr = अणु
	.create_flow_table = mlx5_cmd_dr_create_flow_table,
	.destroy_flow_table = mlx5_cmd_dr_destroy_flow_table,
	.modअगरy_flow_table = mlx5_cmd_dr_modअगरy_flow_table,
	.create_flow_group = mlx5_cmd_dr_create_flow_group,
	.destroy_flow_group = mlx5_cmd_dr_destroy_flow_group,
	.create_fte = mlx5_cmd_dr_create_fte,
	.update_fte = mlx5_cmd_dr_update_fte,
	.delete_fte = mlx5_cmd_dr_delete_fte,
	.update_root_ft = mlx5_cmd_dr_update_root_ft,
	.packet_reक्रमmat_alloc = mlx5_cmd_dr_packet_reक्रमmat_alloc,
	.packet_reक्रमmat_dealloc = mlx5_cmd_dr_packet_reक्रमmat_dealloc,
	.modअगरy_header_alloc = mlx5_cmd_dr_modअगरy_header_alloc,
	.modअगरy_header_dealloc = mlx5_cmd_dr_modअगरy_header_dealloc,
	.set_peer = mlx5_cmd_dr_set_peer,
	.create_ns = mlx5_cmd_dr_create_ns,
	.destroy_ns = mlx5_cmd_dr_destroy_ns,
पूर्ण;

स्थिर काष्ठा mlx5_flow_cmds *mlx5_fs_cmd_get_dr_cmds(व्योम)
अणु
		वापस &mlx5_flow_cmds_dr;
पूर्ण
