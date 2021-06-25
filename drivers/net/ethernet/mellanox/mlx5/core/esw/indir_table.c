<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2021 Mellanox Technologies. */

#समावेश <linux/etherdevice.h>
#समावेश <linux/idr.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/mlx5_अगरc.h>
#समावेश <linux/mlx5/vport.h>
#समावेश <linux/mlx5/fs.h>
#समावेश "mlx5_core.h"
#समावेश "eswitch.h"
#समावेश "en.h"
#समावेश "en_tc.h"
#समावेश "fs_core.h"
#समावेश "esw/indir_table.h"
#समावेश "lib/fs_chains.h"

#घोषणा MLX5_ESW_INसूची_TABLE_SIZE 128
#घोषणा MLX5_ESW_INसूची_TABLE_RECIRC_IDX_MAX (MLX5_ESW_INसूची_TABLE_SIZE - 2)
#घोषणा MLX5_ESW_INसूची_TABLE_FWD_IDX (MLX5_ESW_INसूची_TABLE_SIZE - 1)

काष्ठा mlx5_esw_indir_table_rule अणु
	काष्ठा list_head list;
	काष्ठा mlx5_flow_handle *handle;
	जोड़ अणु
		__be32 v4;
		काष्ठा in6_addr v6;
	पूर्ण dst_ip;
	u32 vni;
	काष्ठा mlx5_modअगरy_hdr *mh;
	refcount_t refcnt;
पूर्ण;

काष्ठा mlx5_esw_indir_table_entry अणु
	काष्ठा hlist_node hlist;
	काष्ठा mlx5_flow_table *ft;
	काष्ठा mlx5_flow_group *recirc_grp;
	काष्ठा mlx5_flow_group *fwd_grp;
	काष्ठा mlx5_flow_handle *fwd_rule;
	काष्ठा list_head recirc_rules;
	पूर्णांक recirc_cnt;
	पूर्णांक fwd_ref;

	u16 vport;
	u8 ip_version;
पूर्ण;

काष्ठा mlx5_esw_indir_table अणु
	काष्ठा mutex lock; /* protects table */
	DECLARE_HASHTABLE(table, 8);
पूर्ण;

काष्ठा mlx5_esw_indir_table *
mlx5_esw_indir_table_init(व्योम)
अणु
	काष्ठा mlx5_esw_indir_table *indir = kvzalloc(माप(*indir), GFP_KERNEL);

	अगर (!indir)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&indir->lock);
	hash_init(indir->table);
	वापस indir;
पूर्ण

व्योम
mlx5_esw_indir_table_destroy(काष्ठा mlx5_esw_indir_table *indir)
अणु
	mutex_destroy(&indir->lock);
	kvमुक्त(indir);
पूर्ण

bool
mlx5_esw_indir_table_needed(काष्ठा mlx5_eचयन *esw,
			    काष्ठा mlx5_flow_attr *attr,
			    u16 vport_num,
			    काष्ठा mlx5_core_dev *dest_mdev)
अणु
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;

	/* Use indirect table क्रम all IP traffic from UL to VF with vport
	 * destination when source reग_लिखो flag is set.
	 */
	वापस esw_attr->in_rep->vport == MLX5_VPORT_UPLINK &&
		mlx5_eचयन_is_vf_vport(esw, vport_num) &&
		esw->dev == dest_mdev &&
		attr->ip_version &&
		attr->flags & MLX5_ESW_ATTR_FLAG_SRC_REWRITE;
पूर्ण

u16
mlx5_esw_indir_table_decap_vport(काष्ठा mlx5_flow_attr *attr)
अणु
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;

	वापस esw_attr->rx_tun_attr ? esw_attr->rx_tun_attr->decap_vport : 0;
पूर्ण

अटल काष्ठा mlx5_esw_indir_table_rule *
mlx5_esw_indir_table_rule_lookup(काष्ठा mlx5_esw_indir_table_entry *e,
				 काष्ठा mlx5_esw_flow_attr *attr)
अणु
	काष्ठा mlx5_esw_indir_table_rule *rule;

	list_क्रम_each_entry(rule, &e->recirc_rules, list)
		अगर (rule->vni == attr->rx_tun_attr->vni &&
		    !स_भेद(&rule->dst_ip, &attr->rx_tun_attr->dst_ip,
			    माप(attr->rx_tun_attr->dst_ip)))
			जाओ found;
	वापस शून्य;

found:
	refcount_inc(&rule->refcnt);
	वापस rule;
पूर्ण

अटल पूर्णांक mlx5_esw_indir_table_rule_get(काष्ठा mlx5_eचयन *esw,
					 काष्ठा mlx5_flow_attr *attr,
					 काष्ठा mlx5_flow_spec *spec,
					 काष्ठा mlx5_esw_indir_table_entry *e)
अणु
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;
	काष्ठा mlx5_fs_chains *chains = esw_chains(esw);
	काष्ठा mlx5e_tc_mod_hdr_acts mod_acts = अणुपूर्ण;
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	काष्ठा mlx5_esw_indir_table_rule *rule;
	काष्ठा mlx5_flow_act flow_act = अणुपूर्ण;
	काष्ठा mlx5_flow_spec *rule_spec;
	काष्ठा mlx5_flow_handle *handle;
	पूर्णांक err = 0;
	u32 data;

	rule = mlx5_esw_indir_table_rule_lookup(e, esw_attr);
	अगर (rule)
		वापस 0;

	अगर (e->recirc_cnt == MLX5_ESW_INसूची_TABLE_RECIRC_IDX_MAX)
		वापस -EINVAL;

	rule_spec = kvzalloc(माप(*rule_spec), GFP_KERNEL);
	अगर (!rule_spec)
		वापस -ENOMEM;

	rule = kzalloc(माप(*rule), GFP_KERNEL);
	अगर (!rule) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	rule_spec->match_criteria_enable = MLX5_MATCH_OUTER_HEADERS |
					   MLX5_MATCH_MISC_PARAMETERS |
					   MLX5_MATCH_MISC_PARAMETERS_2;
	अगर (MLX5_CAP_FLOWTABLE_NIC_RX(esw->dev, ft_field_support.outer_ip_version)) अणु
		MLX5_SET(fte_match_param, rule_spec->match_criteria,
			 outer_headers.ip_version, 0xf);
		MLX5_SET(fte_match_param, rule_spec->match_value, outer_headers.ip_version,
			 attr->ip_version);
	पूर्ण अन्यथा अगर (attr->ip_version) अणु
		MLX5_SET_TO_ONES(fte_match_param, rule_spec->match_criteria,
				 outer_headers.ethertype);
		MLX5_SET(fte_match_param, rule_spec->match_value, outer_headers.ethertype,
			 (attr->ip_version == 4 ? ETH_P_IP : ETH_P_IPV6));
	पूर्ण अन्यथा अणु
		err = -EOPNOTSUPP;
		जाओ err_ethertype;
	पूर्ण

	अगर (attr->ip_version == 4) अणु
		MLX5_SET_TO_ONES(fte_match_param, rule_spec->match_criteria,
				 outer_headers.dst_ipv4_dst_ipv6.ipv4_layout.ipv4);
		MLX5_SET(fte_match_param, rule_spec->match_value,
			 outer_headers.dst_ipv4_dst_ipv6.ipv4_layout.ipv4,
			 ntohl(esw_attr->rx_tun_attr->dst_ip.v4));
	पूर्ण अन्यथा अगर (attr->ip_version == 6) अणु
		पूर्णांक len = माप(काष्ठा in6_addr);

		स_रखो(MLX5_ADDR_OF(fte_match_param, rule_spec->match_criteria,
				    outer_headers.dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       0xff, len);
		स_नकल(MLX5_ADDR_OF(fte_match_param, rule_spec->match_value,
				    outer_headers.dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       &esw_attr->rx_tun_attr->dst_ip.v6, len);
	पूर्ण

	MLX5_SET_TO_ONES(fte_match_param, rule_spec->match_criteria,
			 misc_parameters.vxlan_vni);
	MLX5_SET(fte_match_param, rule_spec->match_value, misc_parameters.vxlan_vni,
		 MLX5_GET(fte_match_param, spec->match_value, misc_parameters.vxlan_vni));

	MLX5_SET(fte_match_param, rule_spec->match_criteria,
		 misc_parameters_2.metadata_reg_c_0, mlx5_eचयन_get_vport_metadata_mask());
	MLX5_SET(fte_match_param, rule_spec->match_value, misc_parameters_2.metadata_reg_c_0,
		 mlx5_eचयन_get_vport_metadata_क्रम_match(esw_attr->in_mdev->priv.eचयन,
							   MLX5_VPORT_UPLINK));

	/* Modअगरy flow source to recirculate packet */
	data = mlx5_eचयन_get_vport_metadata_क्रम_set(esw, esw_attr->rx_tun_attr->decap_vport);
	err = mlx5e_tc_match_to_reg_set(esw->dev, &mod_acts, MLX5_FLOW_NAMESPACE_FDB,
					VPORT_TO_REG, data);
	अगर (err)
		जाओ err_mod_hdr_regc0;

	err = mlx5e_tc_match_to_reg_set(esw->dev, &mod_acts, MLX5_FLOW_NAMESPACE_FDB,
					TUNNEL_TO_REG, ESW_TUN_SLOW_TABLE_GOTO_VPORT);
	अगर (err)
		जाओ err_mod_hdr_regc1;

	flow_act.modअगरy_hdr = mlx5_modअगरy_header_alloc(esw->dev, MLX5_FLOW_NAMESPACE_FDB,
						       mod_acts.num_actions, mod_acts.actions);
	अगर (IS_ERR(flow_act.modअगरy_hdr)) अणु
		err = PTR_ERR(flow_act.modअगरy_hdr);
		जाओ err_mod_hdr_alloc;
	पूर्ण

	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST | MLX5_FLOW_CONTEXT_ACTION_MOD_HDR;
	flow_act.flags = FLOW_ACT_IGNORE_FLOW_LEVEL | FLOW_ACT_NO_APPEND;
	dest.type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	dest.ft = mlx5_chains_get_table(chains, 0, 1, 0);
	अगर (IS_ERR(dest.ft)) अणु
		err = PTR_ERR(dest.ft);
		जाओ err_table;
	पूर्ण
	handle = mlx5_add_flow_rules(e->ft, rule_spec, &flow_act, &dest, 1);
	अगर (IS_ERR(handle)) अणु
		err = PTR_ERR(handle);
		जाओ err_handle;
	पूर्ण

	dealloc_mod_hdr_actions(&mod_acts);
	rule->handle = handle;
	rule->vni = esw_attr->rx_tun_attr->vni;
	rule->mh = flow_act.modअगरy_hdr;
	स_नकल(&rule->dst_ip, &esw_attr->rx_tun_attr->dst_ip,
	       माप(esw_attr->rx_tun_attr->dst_ip));
	refcount_set(&rule->refcnt, 1);
	list_add(&rule->list, &e->recirc_rules);
	e->recirc_cnt++;
	जाओ out;

err_handle:
	mlx5_chains_put_table(chains, 0, 1, 0);
err_table:
	mlx5_modअगरy_header_dealloc(esw->dev, flow_act.modअगरy_hdr);
err_mod_hdr_alloc:
err_mod_hdr_regc1:
	dealloc_mod_hdr_actions(&mod_acts);
err_mod_hdr_regc0:
err_ethertype:
	kमुक्त(rule);
out:
	kvमुक्त(rule_spec);
	वापस err;
पूर्ण

अटल व्योम mlx5_esw_indir_table_rule_put(काष्ठा mlx5_eचयन *esw,
					  काष्ठा mlx5_flow_attr *attr,
					  काष्ठा mlx5_esw_indir_table_entry *e)
अणु
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;
	काष्ठा mlx5_fs_chains *chains = esw_chains(esw);
	काष्ठा mlx5_esw_indir_table_rule *rule;

	list_क्रम_each_entry(rule, &e->recirc_rules, list)
		अगर (rule->vni == esw_attr->rx_tun_attr->vni &&
		    !स_भेद(&rule->dst_ip, &esw_attr->rx_tun_attr->dst_ip,
			    माप(esw_attr->rx_tun_attr->dst_ip)))
			जाओ found;

	वापस;

found:
	अगर (!refcount_dec_and_test(&rule->refcnt))
		वापस;

	mlx5_del_flow_rules(rule->handle);
	mlx5_chains_put_table(chains, 0, 1, 0);
	mlx5_modअगरy_header_dealloc(esw->dev, rule->mh);
	list_del(&rule->list);
	kमुक्त(rule);
	e->recirc_cnt--;
पूर्ण

अटल पूर्णांक mlx5_create_indir_recirc_group(काष्ठा mlx5_eचयन *esw,
					  काष्ठा mlx5_flow_attr *attr,
					  काष्ठा mlx5_flow_spec *spec,
					  काष्ठा mlx5_esw_indir_table_entry *e)
अणु
	पूर्णांक err = 0, inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	u32 *in, *match;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(create_flow_group_in, in, match_criteria_enable, MLX5_MATCH_OUTER_HEADERS |
		 MLX5_MATCH_MISC_PARAMETERS | MLX5_MATCH_MISC_PARAMETERS_2);
	match = MLX5_ADDR_OF(create_flow_group_in, in, match_criteria);

	अगर (MLX5_CAP_FLOWTABLE_NIC_RX(esw->dev, ft_field_support.outer_ip_version))
		MLX5_SET(fte_match_param, match, outer_headers.ip_version, 0xf);
	अन्यथा
		MLX5_SET_TO_ONES(fte_match_param, match, outer_headers.ethertype);

	अगर (attr->ip_version == 4) अणु
		MLX5_SET_TO_ONES(fte_match_param, match,
				 outer_headers.dst_ipv4_dst_ipv6.ipv4_layout.ipv4);
	पूर्ण अन्यथा अगर (attr->ip_version == 6) अणु
		स_रखो(MLX5_ADDR_OF(fte_match_param, match,
				    outer_headers.dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       0xff, माप(काष्ठा in6_addr));
	पूर्ण अन्यथा अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	MLX5_SET_TO_ONES(fte_match_param, match, misc_parameters.vxlan_vni);
	MLX5_SET(fte_match_param, match, misc_parameters_2.metadata_reg_c_0,
		 mlx5_eचयन_get_vport_metadata_mask());
	MLX5_SET(create_flow_group_in, in, start_flow_index, 0);
	MLX5_SET(create_flow_group_in, in, end_flow_index, MLX5_ESW_INसूची_TABLE_RECIRC_IDX_MAX);
	e->recirc_grp = mlx5_create_flow_group(e->ft, in);
	अगर (IS_ERR(e->recirc_grp)) अणु
		err = PTR_ERR(e->recirc_grp);
		जाओ out;
	पूर्ण

	INIT_LIST_HEAD(&e->recirc_rules);
	e->recirc_cnt = 0;

out:
	kvमुक्त(in);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_create_indir_fwd_group(काष्ठा mlx5_eचयन *esw,
				       काष्ठा mlx5_esw_indir_table_entry *e)
अणु
	पूर्णांक err = 0, inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	काष्ठा mlx5_flow_act flow_act = अणुपूर्ण;
	काष्ठा mlx5_flow_spec *spec;
	u32 *in;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec) अणु
		kvमुक्त(in);
		वापस -ENOMEM;
	पूर्ण

	/* Hold one entry */
	MLX5_SET(create_flow_group_in, in, start_flow_index, MLX5_ESW_INसूची_TABLE_FWD_IDX);
	MLX5_SET(create_flow_group_in, in, end_flow_index, MLX5_ESW_INसूची_TABLE_FWD_IDX);
	e->fwd_grp = mlx5_create_flow_group(e->ft, in);
	अगर (IS_ERR(e->fwd_grp)) अणु
		err = PTR_ERR(e->fwd_grp);
		जाओ err_out;
	पूर्ण

	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	dest.type = MLX5_FLOW_DESTINATION_TYPE_VPORT;
	dest.vport.num = e->vport;
	dest.vport.vhca_id = MLX5_CAP_GEN(esw->dev, vhca_id);
	e->fwd_rule = mlx5_add_flow_rules(e->ft, spec, &flow_act, &dest, 1);
	अगर (IS_ERR(e->fwd_rule)) अणु
		mlx5_destroy_flow_group(e->fwd_grp);
		err = PTR_ERR(e->fwd_rule);
	पूर्ण

err_out:
	kvमुक्त(spec);
	kvमुक्त(in);
	वापस err;
पूर्ण

अटल काष्ठा mlx5_esw_indir_table_entry *
mlx5_esw_indir_table_entry_create(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_flow_attr *attr,
				  काष्ठा mlx5_flow_spec *spec, u16 vport, bool decap)
अणु
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5_flow_namespace *root_ns;
	काष्ठा mlx5_esw_indir_table_entry *e;
	काष्ठा mlx5_flow_table *ft;
	पूर्णांक err = 0;

	root_ns = mlx5_get_flow_namespace(esw->dev, MLX5_FLOW_NAMESPACE_FDB);
	अगर (!root_ns)
		वापस ERR_PTR(-ENOENT);

	e = kzalloc(माप(*e), GFP_KERNEL);
	अगर (!e)
		वापस ERR_PTR(-ENOMEM);

	ft_attr.prio = FDB_TC_OFFLOAD;
	ft_attr.max_fte = MLX5_ESW_INसूची_TABLE_SIZE;
	ft_attr.flags = MLX5_FLOW_TABLE_UNMANAGED;
	ft_attr.level = 1;

	ft = mlx5_create_flow_table(root_ns, &ft_attr);
	अगर (IS_ERR(ft)) अणु
		err = PTR_ERR(ft);
		जाओ tbl_err;
	पूर्ण
	e->ft = ft;
	e->vport = vport;
	e->ip_version = attr->ip_version;
	e->fwd_ref = !decap;

	err = mlx5_create_indir_recirc_group(esw, attr, spec, e);
	अगर (err)
		जाओ recirc_grp_err;

	अगर (decap) अणु
		err = mlx5_esw_indir_table_rule_get(esw, attr, spec, e);
		अगर (err)
			जाओ recirc_rule_err;
	पूर्ण

	err = mlx5_create_indir_fwd_group(esw, e);
	अगर (err)
		जाओ fwd_grp_err;

	hash_add(esw->fdb_table.offloads.indir->table, &e->hlist,
		 vport << 16 | attr->ip_version);

	वापस e;

fwd_grp_err:
	अगर (decap)
		mlx5_esw_indir_table_rule_put(esw, attr, e);
recirc_rule_err:
	mlx5_destroy_flow_group(e->recirc_grp);
recirc_grp_err:
	mlx5_destroy_flow_table(e->ft);
tbl_err:
	kमुक्त(e);
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा mlx5_esw_indir_table_entry *
mlx5_esw_indir_table_entry_lookup(काष्ठा mlx5_eचयन *esw, u16 vport, u8 ip_version)
अणु
	काष्ठा mlx5_esw_indir_table_entry *e;
	u32 key = vport << 16 | ip_version;

	hash_क्रम_each_possible(esw->fdb_table.offloads.indir->table, e, hlist, key)
		अगर (e->vport == vport && e->ip_version == ip_version)
			वापस e;

	वापस शून्य;
पूर्ण

काष्ठा mlx5_flow_table *mlx5_esw_indir_table_get(काष्ठा mlx5_eचयन *esw,
						 काष्ठा mlx5_flow_attr *attr,
						 काष्ठा mlx5_flow_spec *spec,
						 u16 vport, bool decap)
अणु
	काष्ठा mlx5_esw_indir_table_entry *e;
	पूर्णांक err;

	mutex_lock(&esw->fdb_table.offloads.indir->lock);
	e = mlx5_esw_indir_table_entry_lookup(esw, vport, attr->ip_version);
	अगर (e) अणु
		अगर (!decap) अणु
			e->fwd_ref++;
		पूर्ण अन्यथा अणु
			err = mlx5_esw_indir_table_rule_get(esw, attr, spec, e);
			अगर (err)
				जाओ out_err;
		पूर्ण
	पूर्ण अन्यथा अणु
		e = mlx5_esw_indir_table_entry_create(esw, attr, spec, vport, decap);
		अगर (IS_ERR(e)) अणु
			err = PTR_ERR(e);
			esw_warn(esw->dev, "Failed to create indirection table, err %d.\n", err);
			जाओ out_err;
		पूर्ण
	पूर्ण
	mutex_unlock(&esw->fdb_table.offloads.indir->lock);
	वापस e->ft;

out_err:
	mutex_unlock(&esw->fdb_table.offloads.indir->lock);
	वापस ERR_PTR(err);
पूर्ण

व्योम mlx5_esw_indir_table_put(काष्ठा mlx5_eचयन *esw,
			      काष्ठा mlx5_flow_attr *attr,
			      u16 vport, bool decap)
अणु
	काष्ठा mlx5_esw_indir_table_entry *e;

	mutex_lock(&esw->fdb_table.offloads.indir->lock);
	e = mlx5_esw_indir_table_entry_lookup(esw, vport, attr->ip_version);
	अगर (!e)
		जाओ out;

	अगर (!decap)
		e->fwd_ref--;
	अन्यथा
		mlx5_esw_indir_table_rule_put(esw, attr, e);

	अगर (e->fwd_ref || e->recirc_cnt)
		जाओ out;

	hash_del(&e->hlist);
	mlx5_destroy_flow_group(e->recirc_grp);
	mlx5_del_flow_rules(e->fwd_rule);
	mlx5_destroy_flow_group(e->fwd_grp);
	mlx5_destroy_flow_table(e->ft);
	kमुक्त(e);
out:
	mutex_unlock(&esw->fdb_table.offloads.indir->lock);
पूर्ण
