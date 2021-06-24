<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2021, Mellanox Technologies inc. All rights reserved. */

#समावेश <linux/netdevice.h>
#समावेश "en/fs_tt_redirect.h"
#समावेश "fs_core.h"

क्रमागत fs_udp_type अणु
	FS_IPV4_UDP,
	FS_IPV6_UDP,
	FS_UDP_NUM_TYPES,
पूर्ण;

काष्ठा mlx5e_fs_udp अणु
	काष्ठा mlx5e_flow_table tables[FS_UDP_NUM_TYPES];
	काष्ठा mlx5_flow_handle *शेष_rules[FS_UDP_NUM_TYPES];
	पूर्णांक ref_cnt;
पूर्ण;

काष्ठा mlx5e_fs_any अणु
	काष्ठा mlx5e_flow_table table;
	काष्ठा mlx5_flow_handle *शेष_rule;
	पूर्णांक ref_cnt;
पूर्ण;

अटल अक्षर *fs_udp_type2str(क्रमागत fs_udp_type i)
अणु
	चयन (i) अणु
	हाल FS_IPV4_UDP:
		वापस "UDP v4";
	शेष: /* FS_IPV6_UDP */
		वापस "UDP v6";
	पूर्ण
पूर्ण

अटल क्रमागत mlx5e_traffic_types fs_udp2tt(क्रमागत fs_udp_type i)
अणु
	चयन (i) अणु
	हाल FS_IPV4_UDP:
		वापस MLX5E_TT_IPV4_UDP;
	शेष: /* FS_IPV6_UDP */
		वापस MLX5E_TT_IPV6_UDP;
	पूर्ण
पूर्ण

अटल क्रमागत fs_udp_type tt2fs_udp(क्रमागत mlx5e_traffic_types i)
अणु
	चयन (i) अणु
	हाल MLX5E_TT_IPV4_UDP:
		वापस FS_IPV4_UDP;
	हाल MLX5E_TT_IPV6_UDP:
		वापस FS_IPV6_UDP;
	शेष:
		वापस FS_UDP_NUM_TYPES;
	पूर्ण
पूर्ण

व्योम mlx5e_fs_tt_redirect_del_rule(काष्ठा mlx5_flow_handle *rule)
अणु
	mlx5_del_flow_rules(rule);
पूर्ण

अटल व्योम fs_udp_set_dport_flow(काष्ठा mlx5_flow_spec *spec, क्रमागत fs_udp_type type,
				  u16 udp_dport)
अणु
	spec->match_criteria_enable = MLX5_MATCH_OUTER_HEADERS;
	MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, outer_headers.ip_protocol);
	MLX5_SET(fte_match_param, spec->match_value, outer_headers.ip_protocol, IPPROTO_UDP);
	MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, outer_headers.ip_version);
	MLX5_SET(fte_match_param, spec->match_value, outer_headers.ip_version,
		 type == FS_IPV4_UDP ? 4 : 6);
	MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, outer_headers.udp_dport);
	MLX5_SET(fte_match_param, spec->match_value, outer_headers.udp_dport, udp_dport);
पूर्ण

काष्ठा mlx5_flow_handle *
mlx5e_fs_tt_redirect_udp_add_rule(काष्ठा mlx5e_priv *priv,
				  क्रमागत mlx5e_traffic_types ttc_type,
				  u32 tir_num, u16 d_port)
अणु
	क्रमागत fs_udp_type type = tt2fs_udp(ttc_type);
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	काष्ठा mlx5_flow_table *ft = शून्य;
	MLX5_DECLARE_FLOW_ACT(flow_act);
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा mlx5_flow_spec *spec;
	काष्ठा mlx5e_fs_udp *fs_udp;
	पूर्णांक err;

	अगर (type == FS_UDP_NUM_TYPES)
		वापस ERR_PTR(-EINVAL);

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस ERR_PTR(-ENOMEM);

	fs_udp = priv->fs.udp;
	ft = fs_udp->tables[type].t;

	fs_udp_set_dport_flow(spec, type, d_port);
	dest.type = MLX5_FLOW_DESTINATION_TYPE_TIR;
	dest.tir_num = tir_num;

	rule = mlx5_add_flow_rules(ft, spec, &flow_act, &dest, 1);
	kvमुक्त(spec);

	अगर (IS_ERR(rule)) अणु
		err = PTR_ERR(rule);
		netdev_err(priv->netdev, "%s: add %s rule failed, err %d\n",
			   __func__, fs_udp_type2str(type), err);
	पूर्ण
	वापस rule;
पूर्ण

अटल पूर्णांक fs_udp_add_शेष_rule(काष्ठा mlx5e_priv *priv, क्रमागत fs_udp_type type)
अणु
	काष्ठा mlx5e_flow_table *fs_udp_t;
	काष्ठा mlx5_flow_destination dest;
	MLX5_DECLARE_FLOW_ACT(flow_act);
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा mlx5e_fs_udp *fs_udp;
	पूर्णांक err;

	fs_udp = priv->fs.udp;
	fs_udp_t = &fs_udp->tables[type];

	dest = mlx5e_ttc_get_शेष_dest(priv, fs_udp2tt(type));
	rule = mlx5_add_flow_rules(fs_udp_t->t, शून्य, &flow_act, &dest, 1);
	अगर (IS_ERR(rule)) अणु
		err = PTR_ERR(rule);
		netdev_err(priv->netdev,
			   "%s: add default rule failed, fs type=%d, err %d\n",
			   __func__, type, err);
		वापस err;
	पूर्ण

	fs_udp->शेष_rules[type] = rule;
	वापस 0;
पूर्ण

#घोषणा MLX5E_FS_UDP_NUM_GROUPS	(2)
#घोषणा MLX5E_FS_UDP_GROUP1_SIZE	(BIT(16))
#घोषणा MLX5E_FS_UDP_GROUP2_SIZE	(BIT(0))
#घोषणा MLX5E_FS_UDP_TABLE_SIZE		(MLX5E_FS_UDP_GROUP1_SIZE +\
					 MLX5E_FS_UDP_GROUP2_SIZE)
अटल पूर्णांक fs_udp_create_groups(काष्ठा mlx5e_flow_table *ft, क्रमागत fs_udp_type type)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	व्योम *outer_headers_c;
	पूर्णांक ix = 0;
	u32 *in;
	पूर्णांक err;
	u8 *mc;

	ft->g = kसुस्मृति(MLX5E_FS_UDP_NUM_GROUPS, माप(*ft->g), GFP_KERNEL);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर  (!in || !ft->g) अणु
		kमुक्त(ft->g);
		kvमुक्त(in);
		वापस -ENOMEM;
	पूर्ण

	mc = MLX5_ADDR_OF(create_flow_group_in, in, match_criteria);
	outer_headers_c = MLX5_ADDR_OF(fte_match_param, mc, outer_headers);
	MLX5_SET_TO_ONES(fte_match_set_lyr_2_4, outer_headers_c, ip_protocol);
	MLX5_SET_TO_ONES(fte_match_set_lyr_2_4, outer_headers_c, ip_version);

	चयन (type) अणु
	हाल FS_IPV4_UDP:
	हाल FS_IPV6_UDP:
		MLX5_SET_TO_ONES(fte_match_set_lyr_2_4, outer_headers_c, udp_dport);
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ out;
	पूर्ण
	/* Match on udp protocol, Ipv4/6 and dport */
	MLX5_SET_CFG(in, match_criteria_enable, MLX5_MATCH_OUTER_HEADERS);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_FS_UDP_GROUP1_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	अगर (IS_ERR(ft->g[ft->num_groups]))
		जाओ err;
	ft->num_groups++;

	/* Default Flow Group */
	स_रखो(in, 0, inlen);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_FS_UDP_GROUP2_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	अगर (IS_ERR(ft->g[ft->num_groups]))
		जाओ err;
	ft->num_groups++;

	kvमुक्त(in);
	वापस 0;

err:
	err = PTR_ERR(ft->g[ft->num_groups]);
	ft->g[ft->num_groups] = शून्य;
out:
	kvमुक्त(in);

	वापस err;
पूर्ण

अटल पूर्णांक fs_udp_create_table(काष्ठा mlx5e_priv *priv, क्रमागत fs_udp_type type)
अणु
	काष्ठा mlx5e_flow_table *ft = &priv->fs.udp->tables[type];
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	पूर्णांक err;

	ft->num_groups = 0;

	ft_attr.max_fte = MLX5E_FS_UDP_TABLE_SIZE;
	ft_attr.level = MLX5E_FS_TT_UDP_FT_LEVEL;
	ft_attr.prio = MLX5E_NIC_PRIO;

	ft->t = mlx5_create_flow_table(priv->fs.ns, &ft_attr);
	अगर (IS_ERR(ft->t)) अणु
		err = PTR_ERR(ft->t);
		ft->t = शून्य;
		वापस err;
	पूर्ण

	netdev_dbg(priv->netdev, "Created fs %s table id %u level %u\n",
		   fs_udp_type2str(type), ft->t->id, ft->t->level);

	err = fs_udp_create_groups(ft, type);
	अगर (err)
		जाओ err;

	err = fs_udp_add_शेष_rule(priv, type);
	अगर (err)
		जाओ err;

	वापस 0;

err:
	mlx5e_destroy_flow_table(ft);
	वापस err;
पूर्ण

अटल व्योम fs_udp_destroy_table(काष्ठा mlx5e_fs_udp *fs_udp, पूर्णांक i)
अणु
	अगर (IS_ERR_OR_शून्य(fs_udp->tables[i].t))
		वापस;

	mlx5_del_flow_rules(fs_udp->शेष_rules[i]);
	mlx5e_destroy_flow_table(&fs_udp->tables[i]);
	fs_udp->tables[i].t = शून्य;
पूर्ण

अटल पूर्णांक fs_udp_disable(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक err, i;

	क्रम (i = 0; i < FS_UDP_NUM_TYPES; i++) अणु
		/* Modअगरy ttc rules destination to poपूर्णांक back to the indir TIRs */
		err = mlx5e_ttc_fwd_शेष_dest(priv, fs_udp2tt(i));
		अगर (err) अणु
			netdev_err(priv->netdev,
				   "%s: modify ttc[%d] default destination failed, err(%d)\n",
				   __func__, fs_udp2tt(i), err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fs_udp_enable(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	पूर्णांक err, i;

	dest.type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	क्रम (i = 0; i < FS_UDP_NUM_TYPES; i++) अणु
		dest.ft = priv->fs.udp->tables[i].t;

		/* Modअगरy ttc rules destination to poपूर्णांक on the accel_fs FTs */
		err = mlx5e_ttc_fwd_dest(priv, fs_udp2tt(i), &dest);
		अगर (err) अणु
			netdev_err(priv->netdev,
				   "%s: modify ttc[%d] destination to accel failed, err(%d)\n",
				   __func__, fs_udp2tt(i), err);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम mlx5e_fs_tt_redirect_udp_destroy(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_fs_udp *fs_udp = priv->fs.udp;
	पूर्णांक i;

	अगर (!fs_udp)
		वापस;

	अगर (--fs_udp->ref_cnt)
		वापस;

	fs_udp_disable(priv);

	क्रम (i = 0; i < FS_UDP_NUM_TYPES; i++)
		fs_udp_destroy_table(fs_udp, i);

	kमुक्त(fs_udp);
	priv->fs.udp = शून्य;
पूर्ण

पूर्णांक mlx5e_fs_tt_redirect_udp_create(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक i, err;

	अगर (priv->fs.udp) अणु
		priv->fs.udp->ref_cnt++;
		वापस 0;
	पूर्ण

	priv->fs.udp = kzalloc(माप(*priv->fs.udp), GFP_KERNEL);
	अगर (!priv->fs.udp)
		वापस -ENOMEM;

	क्रम (i = 0; i < FS_UDP_NUM_TYPES; i++) अणु
		err = fs_udp_create_table(priv, i);
		अगर (err)
			जाओ err_destroy_tables;
	पूर्ण

	err = fs_udp_enable(priv);
	अगर (err)
		जाओ err_destroy_tables;

	priv->fs.udp->ref_cnt = 1;

	वापस 0;

err_destroy_tables:
	जबतक (--i >= 0)
		fs_udp_destroy_table(priv->fs.udp, i);

	kमुक्त(priv->fs.udp);
	priv->fs.udp = शून्य;
	वापस err;
पूर्ण

अटल व्योम fs_any_set_ethertype_flow(काष्ठा mlx5_flow_spec *spec, u16 ether_type)
अणु
	spec->match_criteria_enable = MLX5_MATCH_OUTER_HEADERS;
	MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, outer_headers.ethertype);
	MLX5_SET(fte_match_param, spec->match_value, outer_headers.ethertype, ether_type);
पूर्ण

काष्ठा mlx5_flow_handle *
mlx5e_fs_tt_redirect_any_add_rule(काष्ठा mlx5e_priv *priv,
				  u32 tir_num, u16 ether_type)
अणु
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	काष्ठा mlx5_flow_table *ft = शून्य;
	MLX5_DECLARE_FLOW_ACT(flow_act);
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा mlx5_flow_spec *spec;
	काष्ठा mlx5e_fs_any *fs_any;
	पूर्णांक err;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस ERR_PTR(-ENOMEM);

	fs_any = priv->fs.any;
	ft = fs_any->table.t;

	fs_any_set_ethertype_flow(spec, ether_type);
	dest.type = MLX5_FLOW_DESTINATION_TYPE_TIR;
	dest.tir_num = tir_num;

	rule = mlx5_add_flow_rules(ft, spec, &flow_act, &dest, 1);
	kvमुक्त(spec);

	अगर (IS_ERR(rule)) अणु
		err = PTR_ERR(rule);
		netdev_err(priv->netdev, "%s: add ANY rule failed, err %d\n",
			   __func__, err);
	पूर्ण
	वापस rule;
पूर्ण

अटल पूर्णांक fs_any_add_शेष_rule(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_flow_table *fs_any_t;
	काष्ठा mlx5_flow_destination dest;
	MLX5_DECLARE_FLOW_ACT(flow_act);
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा mlx5e_fs_any *fs_any;
	पूर्णांक err;

	fs_any = priv->fs.any;
	fs_any_t = &fs_any->table;

	dest = mlx5e_ttc_get_शेष_dest(priv, MLX5E_TT_ANY);
	rule = mlx5_add_flow_rules(fs_any_t->t, शून्य, &flow_act, &dest, 1);
	अगर (IS_ERR(rule)) अणु
		err = PTR_ERR(rule);
		netdev_err(priv->netdev,
			   "%s: add default rule failed, fs type=ANY, err %d\n",
			   __func__, err);
		वापस err;
	पूर्ण

	fs_any->शेष_rule = rule;
	वापस 0;
पूर्ण

#घोषणा MLX5E_FS_ANY_NUM_GROUPS	(2)
#घोषणा MLX5E_FS_ANY_GROUP1_SIZE	(BIT(16))
#घोषणा MLX5E_FS_ANY_GROUP2_SIZE	(BIT(0))
#घोषणा MLX5E_FS_ANY_TABLE_SIZE		(MLX5E_FS_ANY_GROUP1_SIZE +\
					 MLX5E_FS_ANY_GROUP2_SIZE)

अटल पूर्णांक fs_any_create_groups(काष्ठा mlx5e_flow_table *ft)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	व्योम *outer_headers_c;
	पूर्णांक ix = 0;
	u32 *in;
	पूर्णांक err;
	u8 *mc;

	ft->g = kसुस्मृति(MLX5E_FS_UDP_NUM_GROUPS, माप(*ft->g), GFP_KERNEL);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर  (!in || !ft->g) अणु
		kमुक्त(ft->g);
		kvमुक्त(in);
		वापस -ENOMEM;
	पूर्ण

	/* Match on ethertype */
	mc = MLX5_ADDR_OF(create_flow_group_in, in, match_criteria);
	outer_headers_c = MLX5_ADDR_OF(fte_match_param, mc, outer_headers);
	MLX5_SET_TO_ONES(fte_match_set_lyr_2_4, outer_headers_c, ethertype);
	MLX5_SET_CFG(in, match_criteria_enable, MLX5_MATCH_OUTER_HEADERS);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_FS_ANY_GROUP1_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	अगर (IS_ERR(ft->g[ft->num_groups]))
		जाओ err;
	ft->num_groups++;

	/* Default Flow Group */
	स_रखो(in, 0, inlen);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_FS_ANY_GROUP2_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	अगर (IS_ERR(ft->g[ft->num_groups]))
		जाओ err;
	ft->num_groups++;

	kvमुक्त(in);
	वापस 0;

err:
	err = PTR_ERR(ft->g[ft->num_groups]);
	ft->g[ft->num_groups] = शून्य;
	kvमुक्त(in);

	वापस err;
पूर्ण

अटल पूर्णांक fs_any_create_table(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_flow_table *ft = &priv->fs.any->table;
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	पूर्णांक err;

	ft->num_groups = 0;

	ft_attr.max_fte = MLX5E_FS_UDP_TABLE_SIZE;
	ft_attr.level = MLX5E_FS_TT_ANY_FT_LEVEL;
	ft_attr.prio = MLX5E_NIC_PRIO;

	ft->t = mlx5_create_flow_table(priv->fs.ns, &ft_attr);
	अगर (IS_ERR(ft->t)) अणु
		err = PTR_ERR(ft->t);
		ft->t = शून्य;
		वापस err;
	पूर्ण

	netdev_dbg(priv->netdev, "Created fs ANY table id %u level %u\n",
		   ft->t->id, ft->t->level);

	err = fs_any_create_groups(ft);
	अगर (err)
		जाओ err;

	err = fs_any_add_शेष_rule(priv);
	अगर (err)
		जाओ err;

	वापस 0;

err:
	mlx5e_destroy_flow_table(ft);
	वापस err;
पूर्ण

अटल पूर्णांक fs_any_disable(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक err;

	/* Modअगरy ttc rules destination to poपूर्णांक back to the indir TIRs */
	err = mlx5e_ttc_fwd_शेष_dest(priv, MLX5E_TT_ANY);
	अगर (err) अणु
		netdev_err(priv->netdev,
			   "%s: modify ttc[%d] default destination failed, err(%d)\n",
			   __func__, MLX5E_TT_ANY, err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fs_any_enable(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	पूर्णांक err;

	dest.type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	dest.ft = priv->fs.any->table.t;

	/* Modअगरy ttc rules destination to poपूर्णांक on the accel_fs FTs */
	err = mlx5e_ttc_fwd_dest(priv, MLX5E_TT_ANY, &dest);
	अगर (err) अणु
		netdev_err(priv->netdev,
			   "%s: modify ttc[%d] destination to accel failed, err(%d)\n",
			   __func__, MLX5E_TT_ANY, err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम fs_any_destroy_table(काष्ठा mlx5e_fs_any *fs_any)
अणु
	अगर (IS_ERR_OR_शून्य(fs_any->table.t))
		वापस;

	mlx5_del_flow_rules(fs_any->शेष_rule);
	mlx5e_destroy_flow_table(&fs_any->table);
	fs_any->table.t = शून्य;
पूर्ण

व्योम mlx5e_fs_tt_redirect_any_destroy(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_fs_any *fs_any = priv->fs.any;

	अगर (!fs_any)
		वापस;

	अगर (--fs_any->ref_cnt)
		वापस;

	fs_any_disable(priv);

	fs_any_destroy_table(fs_any);

	kमुक्त(fs_any);
	priv->fs.any = शून्य;
पूर्ण

पूर्णांक mlx5e_fs_tt_redirect_any_create(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक err;

	अगर (priv->fs.any) अणु
		priv->fs.any->ref_cnt++;
		वापस 0;
	पूर्ण

	priv->fs.any = kzalloc(माप(*priv->fs.any), GFP_KERNEL);
	अगर (!priv->fs.any)
		वापस -ENOMEM;

	err = fs_any_create_table(priv);
	अगर (err)
		वापस err;

	err = fs_any_enable(priv);
	अगर (err)
		जाओ err_destroy_table;

	priv->fs.any->ref_cnt = 1;

	वापस 0;

err_destroy_table:
	fs_any_destroy_table(priv->fs.any);

	kमुक्त(priv->fs.any);
	priv->fs.any = शून्य;
	वापस err;
पूर्ण
