<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
// Copyright (c) 2019 Mellanox Technologies.

#समावेश <linux/mlx5/fs.h>
#समावेश "eswitch.h"
#समावेश "en_tc.h"
#समावेश "fs_core.h"

काष्ठा mlx5_termtbl_handle अणु
	काष्ठा hlist_node termtbl_hlist;

	काष्ठा mlx5_flow_table *termtbl;
	काष्ठा mlx5_flow_act flow_act;
	काष्ठा mlx5_flow_destination dest;

	काष्ठा mlx5_flow_handle *rule;
	पूर्णांक ref_count;
पूर्ण;

अटल u32
mlx5_eचयन_termtbl_hash(काष्ठा mlx5_flow_act *flow_act,
			  काष्ठा mlx5_flow_destination *dest)
अणु
	u32 hash;

	hash = jhash_1word(flow_act->action, 0);
	hash = jhash((स्थिर व्योम *)&flow_act->vlan,
		     माप(flow_act->vlan), hash);
	hash = jhash((स्थिर व्योम *)&dest->vport.num,
		     माप(dest->vport.num), hash);
	hash = jhash((स्थिर व्योम *)&dest->vport.vhca_id,
		     माप(dest->vport.num), hash);
	अगर (dest->vport.pkt_reक्रमmat)
		hash = jhash(dest->vport.pkt_reक्रमmat,
			     माप(*dest->vport.pkt_reक्रमmat),
			     hash);
	वापस hash;
पूर्ण

अटल पूर्णांक
mlx5_eचयन_termtbl_cmp(काष्ठा mlx5_flow_act *flow_act1,
			 काष्ठा mlx5_flow_destination *dest1,
			 काष्ठा mlx5_flow_act *flow_act2,
			 काष्ठा mlx5_flow_destination *dest2)
अणु
	पूर्णांक ret;

	ret = flow_act1->action != flow_act2->action ||
	      dest1->vport.num != dest2->vport.num ||
	      dest1->vport.vhca_id != dest2->vport.vhca_id ||
	      स_भेद(&flow_act1->vlan, &flow_act2->vlan,
		     माप(flow_act1->vlan));
	अगर (ret)
		वापस ret;

	वापस dest1->vport.pkt_reक्रमmat && dest2->vport.pkt_reक्रमmat ?
	       स_भेद(dest1->vport.pkt_reक्रमmat, dest2->vport.pkt_reक्रमmat,
		      माप(*dest1->vport.pkt_reक्रमmat)) : 0;
पूर्ण

अटल पूर्णांक
mlx5_eचयन_termtbl_create(काष्ठा mlx5_core_dev *dev,
			    काष्ठा mlx5_termtbl_handle *tt,
			    काष्ठा mlx5_flow_act *flow_act)
अणु
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5_flow_namespace *root_ns;
	पूर्णांक err, err2;

	root_ns = mlx5_get_flow_namespace(dev, MLX5_FLOW_NAMESPACE_FDB);
	अगर (!root_ns) अणु
		esw_warn(dev, "Failed to get FDB flow namespace\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* As this is the terminating action then the termination table is the
	 * same prio as the slow path
	 */
	ft_attr.flags = MLX5_FLOW_TABLE_TERMINATION | MLX5_FLOW_TABLE_UNMANAGED |
			MLX5_FLOW_TABLE_TUNNEL_EN_REFORMAT;
	ft_attr.prio = FDB_TC_OFFLOAD;
	ft_attr.max_fte = 1;
	ft_attr.level = 1;
	ft_attr.स्वतःgroup.max_num_groups = 1;
	tt->termtbl = mlx5_create_स्वतः_grouped_flow_table(root_ns, &ft_attr);
	अगर (IS_ERR(tt->termtbl)) अणु
		err = PTR_ERR(tt->termtbl);
		esw_warn(dev, "Failed to create termination table, err %pe\n", tt->termtbl);
		वापस err;
	पूर्ण

	tt->rule = mlx5_add_flow_rules(tt->termtbl, शून्य, flow_act,
				       &tt->dest, 1);
	अगर (IS_ERR(tt->rule)) अणु
		err = PTR_ERR(tt->rule);
		esw_warn(dev, "Failed to create termination table rule, err %pe\n", tt->rule);
		जाओ add_flow_err;
	पूर्ण
	वापस 0;

add_flow_err:
	err2 = mlx5_destroy_flow_table(tt->termtbl);
	अगर (err2)
		esw_warn(dev, "Failed to destroy termination table, err %d\n", err2);

	वापस err;
पूर्ण

अटल काष्ठा mlx5_termtbl_handle *
mlx5_eचयन_termtbl_get_create(काष्ठा mlx5_eचयन *esw,
				काष्ठा mlx5_flow_act *flow_act,
				काष्ठा mlx5_flow_destination *dest,
				काष्ठा mlx5_esw_flow_attr *attr)
अणु
	काष्ठा mlx5_termtbl_handle *tt;
	bool found = false;
	u32 hash_key;
	पूर्णांक err;

	mutex_lock(&esw->offloads.termtbl_mutex);
	hash_key = mlx5_eचयन_termtbl_hash(flow_act, dest);
	hash_क्रम_each_possible(esw->offloads.termtbl_tbl, tt,
			       termtbl_hlist, hash_key) अणु
		अगर (!mlx5_eचयन_termtbl_cmp(&tt->flow_act, &tt->dest,
					      flow_act, dest)) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (found)
		जाओ tt_add_ref;

	tt = kzalloc(माप(*tt), GFP_KERNEL);
	अगर (!tt) अणु
		err = -ENOMEM;
		जाओ tt_create_err;
	पूर्ण

	tt->dest.type = MLX5_FLOW_DESTINATION_TYPE_VPORT;
	tt->dest.vport.num = dest->vport.num;
	tt->dest.vport.vhca_id = dest->vport.vhca_id;
	tt->dest.vport.flags = dest->vport.flags;
	स_नकल(&tt->flow_act, flow_act, माप(*flow_act));

	err = mlx5_eचयन_termtbl_create(esw->dev, tt, flow_act);
	अगर (err)
		जाओ tt_create_err;

	hash_add(esw->offloads.termtbl_tbl, &tt->termtbl_hlist, hash_key);
tt_add_ref:
	tt->ref_count++;
	mutex_unlock(&esw->offloads.termtbl_mutex);
	वापस tt;
tt_create_err:
	kमुक्त(tt);
	mutex_unlock(&esw->offloads.termtbl_mutex);
	वापस ERR_PTR(err);
पूर्ण

व्योम
mlx5_eचयन_termtbl_put(काष्ठा mlx5_eचयन *esw,
			 काष्ठा mlx5_termtbl_handle *tt)
अणु
	mutex_lock(&esw->offloads.termtbl_mutex);
	अगर (--tt->ref_count == 0)
		hash_del(&tt->termtbl_hlist);
	mutex_unlock(&esw->offloads.termtbl_mutex);

	अगर (!tt->ref_count) अणु
		mlx5_del_flow_rules(tt->rule);
		mlx5_destroy_flow_table(tt->termtbl);
		kमुक्त(tt);
	पूर्ण
पूर्ण

अटल व्योम
mlx5_eचयन_termtbl_actions_move(काष्ठा mlx5_flow_act *src,
				  काष्ठा mlx5_flow_act *dst)
अणु
	अगर (src->action & MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH) अणु
		src->action &= ~MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH;
		dst->action |= MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH;
		स_नकल(&dst->vlan[0], &src->vlan[0], माप(src->vlan[0]));
		स_रखो(&src->vlan[0], 0, माप(src->vlan[0]));

		अगर (src->action & MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH_2) अणु
			src->action &= ~MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH_2;
			dst->action |= MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH_2;
			स_नकल(&dst->vlan[1], &src->vlan[1], माप(src->vlan[1]));
			स_रखो(&src->vlan[1], 0, माप(src->vlan[1]));
		पूर्ण
	पूर्ण
पूर्ण

अटल bool mlx5_eचयन_offload_is_uplink_port(स्थिर काष्ठा mlx5_eचयन *esw,
						स्थिर काष्ठा mlx5_flow_spec *spec)
अणु
	u16 port_mask, port_value;

	अगर (MLX5_CAP_ESW_FLOWTABLE(esw->dev, flow_source))
		वापस spec->flow_context.flow_source ==
					MLX5_FLOW_CONTEXT_FLOW_SOURCE_UPLINK;

	port_mask = MLX5_GET(fte_match_param, spec->match_criteria,
			     misc_parameters.source_port);
	port_value = MLX5_GET(fte_match_param, spec->match_value,
			      misc_parameters.source_port);
	वापस (port_mask & port_value) == MLX5_VPORT_UPLINK;
पूर्ण

bool
mlx5_eचयन_termtbl_required(काष्ठा mlx5_eचयन *esw,
			      काष्ठा mlx5_flow_attr *attr,
			      काष्ठा mlx5_flow_act *flow_act,
			      काष्ठा mlx5_flow_spec *spec)
अणु
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;
	पूर्णांक i;

	अगर (!MLX5_CAP_ESW_FLOWTABLE_FDB(esw->dev, termination_table) ||
	    !MLX5_CAP_ESW_FLOWTABLE_FDB(esw->dev, ignore_flow_level) ||
	    attr->flags & MLX5_ESW_ATTR_FLAG_SLOW_PATH ||
	    !mlx5_eचयन_offload_is_uplink_port(esw, spec))
		वापस false;

	/* push vlan on RX */
	अगर (flow_act->action & MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH)
		वापस true;

	/* hairpin */
	क्रम (i = esw_attr->split_count; i < esw_attr->out_count; i++)
		अगर (esw_attr->dests[i].rep->vport == MLX5_VPORT_UPLINK)
			वापस true;

	वापस false;
पूर्ण

काष्ठा mlx5_flow_handle *
mlx5_eचयन_add_termtbl_rule(काष्ठा mlx5_eचयन *esw,
			      काष्ठा mlx5_flow_table *fdb,
			      काष्ठा mlx5_flow_spec *spec,
			      काष्ठा mlx5_esw_flow_attr *attr,
			      काष्ठा mlx5_flow_act *flow_act,
			      काष्ठा mlx5_flow_destination *dest,
			      पूर्णांक num_dest)
अणु
	काष्ठा mlx5_flow_act term_tbl_act = अणुपूर्ण;
	काष्ठा mlx5_flow_handle *rule = शून्य;
	bool term_table_created = false;
	पूर्णांक num_vport_dests = 0;
	पूर्णांक i, curr_dest;

	mlx5_eचयन_termtbl_actions_move(flow_act, &term_tbl_act);
	term_tbl_act.action |= MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;

	क्रम (i = 0; i < num_dest; i++) अणु
		काष्ठा mlx5_termtbl_handle *tt;

		/* only vport destinations can be terminated */
		अगर (dest[i].type != MLX5_FLOW_DESTINATION_TYPE_VPORT)
			जारी;

		अगर (attr->dests[num_vport_dests].flags & MLX5_ESW_DEST_ENCAP) अणु
			term_tbl_act.action |= MLX5_FLOW_CONTEXT_ACTION_PACKET_REFORMAT;
			term_tbl_act.pkt_reक्रमmat = attr->dests[num_vport_dests].pkt_reक्रमmat;
		पूर्ण अन्यथा अणु
			term_tbl_act.action &= ~MLX5_FLOW_CONTEXT_ACTION_PACKET_REFORMAT;
			term_tbl_act.pkt_reक्रमmat = शून्य;
		पूर्ण

		/* get the terminating table क्रम the action list */
		tt = mlx5_eचयन_termtbl_get_create(esw, &term_tbl_act,
						     &dest[i], attr);
		अगर (IS_ERR(tt)) अणु
			esw_warn(esw->dev, "Failed to get termination table, err %pe\n", tt);
			जाओ revert_changes;
		पूर्ण
		attr->dests[num_vport_dests].termtbl = tt;
		num_vport_dests++;

		/* link the destination with the termination table */
		dest[i].type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
		dest[i].ft = tt->termtbl;
		term_table_created = true;
	पूर्ण

	/* at least one destination should reference a termination table */
	अगर (!term_table_created)
		जाओ revert_changes;

	/* create the FTE */
	flow_act->action &= ~MLX5_FLOW_CONTEXT_ACTION_PACKET_REFORMAT;
	flow_act->pkt_reक्रमmat = शून्य;
	flow_act->flags |= FLOW_ACT_IGNORE_FLOW_LEVEL;
	rule = mlx5_add_flow_rules(fdb, spec, flow_act, dest, num_dest);
	अगर (IS_ERR(rule))
		जाओ revert_changes;

	जाओ out;

revert_changes:
	/* revert the changes that were made to the original flow_act
	 * and fall-back to the original rule actions
	 */
	mlx5_eचयन_termtbl_actions_move(&term_tbl_act, flow_act);

	क्रम (curr_dest = 0; curr_dest < num_vport_dests; curr_dest++) अणु
		काष्ठा mlx5_termtbl_handle *tt = attr->dests[curr_dest].termtbl;

		/* search क्रम the destination associated with the
		 * current term table
		 */
		क्रम (i = 0; i < num_dest; i++) अणु
			अगर (dest[i].ft != tt->termtbl)
				जारी;

			स_रखो(&dest[i], 0, माप(dest[i]));
			dest[i].type = MLX5_FLOW_DESTINATION_TYPE_VPORT;
			dest[i].vport.num = tt->dest.vport.num;
			dest[i].vport.vhca_id = tt->dest.vport.vhca_id;
			mlx5_eचयन_termtbl_put(esw, tt);
			अवरोध;
		पूर्ण
	पूर्ण
	rule = mlx5_add_flow_rules(fdb, spec, flow_act, dest, num_dest);
out:
	वापस rule;
पूर्ण
