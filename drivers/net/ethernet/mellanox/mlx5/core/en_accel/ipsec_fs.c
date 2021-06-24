<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020, Mellanox Technologies inc. All rights reserved. */

#समावेश <linux/netdevice.h>
#समावेश "accel/ipsec_offload.h"
#समावेश "ipsec_fs.h"
#समावेश "fs_core.h"

#घोषणा NUM_IPSEC_FTE BIT(15)

क्रमागत accel_fs_esp_type अणु
	ACCEL_FS_ESP4,
	ACCEL_FS_ESP6,
	ACCEL_FS_ESP_NUM_TYPES,
पूर्ण;

काष्ठा mlx5e_ipsec_rx_err अणु
	काष्ठा mlx5_flow_table *ft;
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा mlx5_modअगरy_hdr *copy_modअगरy_hdr;
पूर्ण;

काष्ठा mlx5e_accel_fs_esp_prot अणु
	काष्ठा mlx5_flow_table *ft;
	काष्ठा mlx5_flow_group *miss_group;
	काष्ठा mlx5_flow_handle *miss_rule;
	काष्ठा mlx5_flow_destination शेष_dest;
	काष्ठा mlx5e_ipsec_rx_err rx_err;
	u32 refcnt;
	काष्ठा mutex prot_mutex; /* protect ESP4/ESP6 protocol */
पूर्ण;

काष्ठा mlx5e_accel_fs_esp अणु
	काष्ठा mlx5e_accel_fs_esp_prot fs_prot[ACCEL_FS_ESP_NUM_TYPES];
पूर्ण;

काष्ठा mlx5e_ipsec_tx अणु
	काष्ठा mlx5_flow_table *ft;
	काष्ठा mutex mutex; /* Protect IPsec TX steering */
	u32 refcnt;
पूर्ण;

/* IPsec RX flow steering */
अटल क्रमागत mlx5e_traffic_types fs_esp2tt(क्रमागत accel_fs_esp_type i)
अणु
	अगर (i == ACCEL_FS_ESP4)
		वापस MLX5E_TT_IPV4_IPSEC_ESP;
	वापस MLX5E_TT_IPV6_IPSEC_ESP;
पूर्ण

अटल पूर्णांक rx_err_add_rule(काष्ठा mlx5e_priv *priv,
			   काष्ठा mlx5e_accel_fs_esp_prot *fs_prot,
			   काष्ठा mlx5e_ipsec_rx_err *rx_err)
अणु
	u8 action[MLX5_UN_SZ_BYTES(set_add_copy_action_in_स्वतः)] = अणुपूर्ण;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5_flow_act flow_act = अणुपूर्ण;
	काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr;
	काष्ठा mlx5_flow_handle *fte;
	काष्ठा mlx5_flow_spec *spec;
	पूर्णांक err = 0;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;

	/* Action to copy 7 bit ipsec_syndrome to regB[24:30] */
	MLX5_SET(copy_action_in, action, action_type, MLX5_ACTION_TYPE_COPY);
	MLX5_SET(copy_action_in, action, src_field, MLX5_ACTION_IN_FIELD_IPSEC_SYNDROME);
	MLX5_SET(copy_action_in, action, src_offset, 0);
	MLX5_SET(copy_action_in, action, length, 7);
	MLX5_SET(copy_action_in, action, dst_field, MLX5_ACTION_IN_FIELD_METADATA_REG_B);
	MLX5_SET(copy_action_in, action, dst_offset, 24);

	modअगरy_hdr = mlx5_modअगरy_header_alloc(mdev, MLX5_FLOW_NAMESPACE_KERNEL,
					      1, action);

	अगर (IS_ERR(modअगरy_hdr)) अणु
		err = PTR_ERR(modअगरy_hdr);
		netdev_err(priv->netdev,
			   "fail to alloc ipsec copy modify_header_id err=%d\n", err);
		जाओ out_spec;
	पूर्ण

	/* create fte */
	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_MOD_HDR |
			  MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	flow_act.modअगरy_hdr = modअगरy_hdr;
	fte = mlx5_add_flow_rules(rx_err->ft, spec, &flow_act,
				  &fs_prot->शेष_dest, 1);
	अगर (IS_ERR(fte)) अणु
		err = PTR_ERR(fte);
		netdev_err(priv->netdev, "fail to add ipsec rx err copy rule err=%d\n", err);
		जाओ out;
	पूर्ण

	rx_err->rule = fte;
	rx_err->copy_modअगरy_hdr = modअगरy_hdr;

out:
	अगर (err)
		mlx5_modअगरy_header_dealloc(mdev, modअगरy_hdr);
out_spec:
	kvमुक्त(spec);
	वापस err;
पूर्ण

अटल व्योम rx_err_del_rule(काष्ठा mlx5e_priv *priv,
			    काष्ठा mlx5e_ipsec_rx_err *rx_err)
अणु
	अगर (rx_err->rule) अणु
		mlx5_del_flow_rules(rx_err->rule);
		rx_err->rule = शून्य;
	पूर्ण

	अगर (rx_err->copy_modअगरy_hdr) अणु
		mlx5_modअगरy_header_dealloc(priv->mdev, rx_err->copy_modअगरy_hdr);
		rx_err->copy_modअगरy_hdr = शून्य;
	पूर्ण
पूर्ण

अटल व्योम rx_err_destroy_ft(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_ipsec_rx_err *rx_err)
अणु
	rx_err_del_rule(priv, rx_err);

	अगर (rx_err->ft) अणु
		mlx5_destroy_flow_table(rx_err->ft);
		rx_err->ft = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक rx_err_create_ft(काष्ठा mlx5e_priv *priv,
			    काष्ठा mlx5e_accel_fs_esp_prot *fs_prot,
			    काष्ठा mlx5e_ipsec_rx_err *rx_err)
अणु
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5_flow_table *ft;
	पूर्णांक err;

	ft_attr.max_fte = 1;
	ft_attr.स्वतःgroup.max_num_groups = 1;
	ft_attr.level = MLX5E_ACCEL_FS_ESP_FT_ERR_LEVEL;
	ft_attr.prio = MLX5E_NIC_PRIO;
	ft = mlx5_create_स्वतः_grouped_flow_table(priv->fs.ns, &ft_attr);
	अगर (IS_ERR(ft)) अणु
		err = PTR_ERR(ft);
		netdev_err(priv->netdev, "fail to create ipsec rx inline ft err=%d\n", err);
		वापस err;
	पूर्ण

	rx_err->ft = ft;
	err = rx_err_add_rule(priv, fs_prot, rx_err);
	अगर (err)
		जाओ out_err;

	वापस 0;

out_err:
	mlx5_destroy_flow_table(ft);
	rx_err->ft = शून्य;
	वापस err;
पूर्ण

अटल व्योम rx_fs_destroy(काष्ठा mlx5e_accel_fs_esp_prot *fs_prot)
अणु
	अगर (fs_prot->miss_rule) अणु
		mlx5_del_flow_rules(fs_prot->miss_rule);
		fs_prot->miss_rule = शून्य;
	पूर्ण

	अगर (fs_prot->miss_group) अणु
		mlx5_destroy_flow_group(fs_prot->miss_group);
		fs_prot->miss_group = शून्य;
	पूर्ण

	अगर (fs_prot->ft) अणु
		mlx5_destroy_flow_table(fs_prot->ft);
		fs_prot->ft = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक rx_fs_create(काष्ठा mlx5e_priv *priv,
			काष्ठा mlx5e_accel_fs_esp_prot *fs_prot)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5_flow_group *miss_group;
	काष्ठा mlx5_flow_handle *miss_rule;
	MLX5_DECLARE_FLOW_ACT(flow_act);
	काष्ठा mlx5_flow_spec *spec;
	काष्ठा mlx5_flow_table *ft;
	u32 *flow_group_in;
	पूर्णांक err = 0;

	flow_group_in = kvzalloc(inlen, GFP_KERNEL);
	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!flow_group_in || !spec) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Create FT */
	ft_attr.max_fte = NUM_IPSEC_FTE;
	ft_attr.level = MLX5E_ACCEL_FS_ESP_FT_LEVEL;
	ft_attr.prio = MLX5E_NIC_PRIO;
	ft_attr.स्वतःgroup.num_reserved_entries = 1;
	ft_attr.स्वतःgroup.max_num_groups = 1;
	ft = mlx5_create_स्वतः_grouped_flow_table(priv->fs.ns, &ft_attr);
	अगर (IS_ERR(ft)) अणु
		err = PTR_ERR(ft);
		netdev_err(priv->netdev, "fail to create ipsec rx ft err=%d\n", err);
		जाओ out;
	पूर्ण
	fs_prot->ft = ft;

	/* Create miss_group */
	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, ft->max_fte - 1);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, ft->max_fte - 1);
	miss_group = mlx5_create_flow_group(ft, flow_group_in);
	अगर (IS_ERR(miss_group)) अणु
		err = PTR_ERR(miss_group);
		netdev_err(priv->netdev, "fail to create ipsec rx miss_group err=%d\n", err);
		जाओ out;
	पूर्ण
	fs_prot->miss_group = miss_group;

	/* Create miss rule */
	miss_rule = mlx5_add_flow_rules(ft, spec, &flow_act, &fs_prot->शेष_dest, 1);
	अगर (IS_ERR(miss_rule)) अणु
		err = PTR_ERR(miss_rule);
		netdev_err(priv->netdev, "fail to create ipsec rx miss_rule err=%d\n", err);
		जाओ out;
	पूर्ण
	fs_prot->miss_rule = miss_rule;

out:
	kvमुक्त(flow_group_in);
	kvमुक्त(spec);
	वापस err;
पूर्ण

अटल पूर्णांक rx_destroy(काष्ठा mlx5e_priv *priv, क्रमागत accel_fs_esp_type type)
अणु
	काष्ठा mlx5e_accel_fs_esp_prot *fs_prot;
	काष्ठा mlx5e_accel_fs_esp *accel_esp;

	accel_esp = priv->ipsec->rx_fs;

	/* The netdev unreg alपढ़ोy happened, so all offloaded rule are alपढ़ोy हटाओd */
	fs_prot = &accel_esp->fs_prot[type];

	rx_fs_destroy(fs_prot);

	rx_err_destroy_ft(priv, &fs_prot->rx_err);

	वापस 0;
पूर्ण

अटल पूर्णांक rx_create(काष्ठा mlx5e_priv *priv, क्रमागत accel_fs_esp_type type)
अणु
	काष्ठा mlx5e_accel_fs_esp_prot *fs_prot;
	काष्ठा mlx5e_accel_fs_esp *accel_esp;
	पूर्णांक err;

	accel_esp = priv->ipsec->rx_fs;
	fs_prot = &accel_esp->fs_prot[type];

	fs_prot->शेष_dest = mlx5e_ttc_get_शेष_dest(priv, fs_esp2tt(type));

	err = rx_err_create_ft(priv, fs_prot, &fs_prot->rx_err);
	अगर (err)
		वापस err;

	err = rx_fs_create(priv, fs_prot);
	अगर (err)
		rx_destroy(priv, type);

	वापस err;
पूर्ण

अटल पूर्णांक rx_ft_get(काष्ठा mlx5e_priv *priv, क्रमागत accel_fs_esp_type type)
अणु
	काष्ठा mlx5e_accel_fs_esp_prot *fs_prot;
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	काष्ठा mlx5e_accel_fs_esp *accel_esp;
	पूर्णांक err = 0;

	accel_esp = priv->ipsec->rx_fs;
	fs_prot = &accel_esp->fs_prot[type];
	mutex_lock(&fs_prot->prot_mutex);
	अगर (fs_prot->refcnt++)
		जाओ out;

	/* create FT */
	err = rx_create(priv, type);
	अगर (err) अणु
		fs_prot->refcnt--;
		जाओ out;
	पूर्ण

	/* connect */
	dest.type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	dest.ft = fs_prot->ft;
	mlx5e_ttc_fwd_dest(priv, fs_esp2tt(type), &dest);

out:
	mutex_unlock(&fs_prot->prot_mutex);
	वापस err;
पूर्ण

अटल व्योम rx_ft_put(काष्ठा mlx5e_priv *priv, क्रमागत accel_fs_esp_type type)
अणु
	काष्ठा mlx5e_accel_fs_esp_prot *fs_prot;
	काष्ठा mlx5e_accel_fs_esp *accel_esp;

	accel_esp = priv->ipsec->rx_fs;
	fs_prot = &accel_esp->fs_prot[type];
	mutex_lock(&fs_prot->prot_mutex);
	अगर (--fs_prot->refcnt)
		जाओ out;

	/* disconnect */
	mlx5e_ttc_fwd_शेष_dest(priv, fs_esp2tt(type));

	/* हटाओ FT */
	rx_destroy(priv, type);

out:
	mutex_unlock(&fs_prot->prot_mutex);
पूर्ण

/* IPsec TX flow steering */
अटल पूर्णांक tx_create(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5e_ipsec *ipsec = priv->ipsec;
	काष्ठा mlx5_flow_table *ft;
	पूर्णांक err;

	priv->fs.egress_ns =
		mlx5_get_flow_namespace(priv->mdev,
					MLX5_FLOW_NAMESPACE_EGRESS_KERNEL);
	अगर (!priv->fs.egress_ns)
		वापस -EOPNOTSUPP;

	ft_attr.max_fte = NUM_IPSEC_FTE;
	ft_attr.स्वतःgroup.max_num_groups = 1;
	ft = mlx5_create_स्वतः_grouped_flow_table(priv->fs.egress_ns, &ft_attr);
	अगर (IS_ERR(ft)) अणु
		err = PTR_ERR(ft);
		netdev_err(priv->netdev, "fail to create ipsec tx ft err=%d\n", err);
		वापस err;
	पूर्ण
	ipsec->tx_fs->ft = ft;
	वापस 0;
पूर्ण

अटल व्योम tx_destroy(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_ipsec *ipsec = priv->ipsec;

	अगर (IS_ERR_OR_शून्य(ipsec->tx_fs->ft))
		वापस;

	mlx5_destroy_flow_table(ipsec->tx_fs->ft);
	ipsec->tx_fs->ft = शून्य;
पूर्ण

अटल पूर्णांक tx_ft_get(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_ipsec_tx *tx_fs = priv->ipsec->tx_fs;
	पूर्णांक err = 0;

	mutex_lock(&tx_fs->mutex);
	अगर (tx_fs->refcnt++)
		जाओ out;

	err = tx_create(priv);
	अगर (err) अणु
		tx_fs->refcnt--;
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&tx_fs->mutex);
	वापस err;
पूर्ण

अटल व्योम tx_ft_put(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_ipsec_tx *tx_fs = priv->ipsec->tx_fs;

	mutex_lock(&tx_fs->mutex);
	अगर (--tx_fs->refcnt)
		जाओ out;

	tx_destroy(priv);

out:
	mutex_unlock(&tx_fs->mutex);
पूर्ण

अटल व्योम setup_fte_common(काष्ठा mlx5_accel_esp_xfrm_attrs *attrs,
			     u32 ipsec_obj_id,
			     काष्ठा mlx5_flow_spec *spec,
			     काष्ठा mlx5_flow_act *flow_act)
अणु
	u8 ip_version = attrs->is_ipv6 ? 6 : 4;

	spec->match_criteria_enable = MLX5_MATCH_OUTER_HEADERS | MLX5_MATCH_MISC_PARAMETERS;

	/* ip_version */
	MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, outer_headers.ip_version);
	MLX5_SET(fte_match_param, spec->match_value, outer_headers.ip_version, ip_version);

	/* Non fragmented */
	MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, outer_headers.frag);
	MLX5_SET(fte_match_param, spec->match_value, outer_headers.frag, 0);

	/* ESP header */
	MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, outer_headers.ip_protocol);
	MLX5_SET(fte_match_param, spec->match_value, outer_headers.ip_protocol, IPPROTO_ESP);

	/* SPI number */
	MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, misc_parameters.outer_esp_spi);
	MLX5_SET(fte_match_param, spec->match_value, misc_parameters.outer_esp_spi,
		 be32_to_cpu(attrs->spi));

	अगर (ip_version == 4) अणु
		स_नकल(MLX5_ADDR_OF(fte_match_param, spec->match_value,
				    outer_headers.src_ipv4_src_ipv6.ipv4_layout.ipv4),
		       &attrs->saddr.a4, 4);
		स_नकल(MLX5_ADDR_OF(fte_match_param, spec->match_value,
				    outer_headers.dst_ipv4_dst_ipv6.ipv4_layout.ipv4),
		       &attrs->daddr.a4, 4);
		MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria,
				 outer_headers.src_ipv4_src_ipv6.ipv4_layout.ipv4);
		MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria,
				 outer_headers.dst_ipv4_dst_ipv6.ipv4_layout.ipv4);
	पूर्ण अन्यथा अणु
		स_नकल(MLX5_ADDR_OF(fte_match_param, spec->match_value,
				    outer_headers.src_ipv4_src_ipv6.ipv6_layout.ipv6),
		       &attrs->saddr.a6, 16);
		स_नकल(MLX5_ADDR_OF(fte_match_param, spec->match_value,
				    outer_headers.dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       &attrs->daddr.a6, 16);
		स_रखो(MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
				    outer_headers.src_ipv4_src_ipv6.ipv6_layout.ipv6),
		       0xff, 16);
		स_रखो(MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
				    outer_headers.dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       0xff, 16);
	पूर्ण

	flow_act->ipsec_obj_id = ipsec_obj_id;
	flow_act->flags |= FLOW_ACT_NO_APPEND;
पूर्ण

अटल पूर्णांक rx_add_rule(काष्ठा mlx5e_priv *priv,
		       काष्ठा mlx5_accel_esp_xfrm_attrs *attrs,
		       u32 ipsec_obj_id,
		       काष्ठा mlx5e_ipsec_rule *ipsec_rule)
अणु
	u8 action[MLX5_UN_SZ_BYTES(set_add_copy_action_in_स्वतः)] = अणुपूर्ण;
	काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr = शून्य;
	काष्ठा mlx5e_accel_fs_esp_prot *fs_prot;
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	काष्ठा mlx5e_accel_fs_esp *accel_esp;
	काष्ठा mlx5_flow_act flow_act = अणुपूर्ण;
	काष्ठा mlx5_flow_handle *rule;
	क्रमागत accel_fs_esp_type type;
	काष्ठा mlx5_flow_spec *spec;
	पूर्णांक err = 0;

	accel_esp = priv->ipsec->rx_fs;
	type = attrs->is_ipv6 ? ACCEL_FS_ESP6 : ACCEL_FS_ESP4;
	fs_prot = &accel_esp->fs_prot[type];

	err = rx_ft_get(priv, type);
	अगर (err)
		वापस err;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec) अणु
		err = -ENOMEM;
		जाओ out_err;
	पूर्ण

	setup_fte_common(attrs, ipsec_obj_id, spec, &flow_act);

	/* Set bit[31] ipsec marker */
	/* Set bit[23-0] ipsec_obj_id */
	MLX5_SET(set_action_in, action, action_type, MLX5_ACTION_TYPE_SET);
	MLX5_SET(set_action_in, action, field, MLX5_ACTION_IN_FIELD_METADATA_REG_B);
	MLX5_SET(set_action_in, action, data, (ipsec_obj_id | BIT(31)));
	MLX5_SET(set_action_in, action, offset, 0);
	MLX5_SET(set_action_in, action, length, 32);

	modअगरy_hdr = mlx5_modअगरy_header_alloc(priv->mdev, MLX5_FLOW_NAMESPACE_KERNEL,
					      1, action);
	अगर (IS_ERR(modअगरy_hdr)) अणु
		err = PTR_ERR(modअगरy_hdr);
		netdev_err(priv->netdev,
			   "fail to alloc ipsec set modify_header_id err=%d\n", err);
		modअगरy_hdr = शून्य;
		जाओ out_err;
	पूर्ण

	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST |
			  MLX5_FLOW_CONTEXT_ACTION_IPSEC_DECRYPT |
			  MLX5_FLOW_CONTEXT_ACTION_MOD_HDR;
	dest.type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	flow_act.modअगरy_hdr = modअगरy_hdr;
	dest.ft = fs_prot->rx_err.ft;
	rule = mlx5_add_flow_rules(fs_prot->ft, spec, &flow_act, &dest, 1);
	अगर (IS_ERR(rule)) अणु
		err = PTR_ERR(rule);
		netdev_err(priv->netdev, "fail to add ipsec rule attrs->action=0x%x, err=%d\n",
			   attrs->action, err);
		जाओ out_err;
	पूर्ण

	ipsec_rule->rule = rule;
	ipsec_rule->set_modअगरy_hdr = modअगरy_hdr;
	जाओ out;

out_err:
	अगर (modअगरy_hdr)
		mlx5_modअगरy_header_dealloc(priv->mdev, modअगरy_hdr);
	rx_ft_put(priv, type);

out:
	kvमुक्त(spec);
	वापस err;
पूर्ण

अटल पूर्णांक tx_add_rule(काष्ठा mlx5e_priv *priv,
		       काष्ठा mlx5_accel_esp_xfrm_attrs *attrs,
		       u32 ipsec_obj_id,
		       काष्ठा mlx5e_ipsec_rule *ipsec_rule)
अणु
	काष्ठा mlx5_flow_act flow_act = अणुपूर्ण;
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा mlx5_flow_spec *spec;
	पूर्णांक err = 0;

	err = tx_ft_get(priv);
	अगर (err)
		वापस err;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	setup_fte_common(attrs, ipsec_obj_id, spec, &flow_act);

	/* Add IPsec indicator in metadata_reg_a */
	spec->match_criteria_enable |= MLX5_MATCH_MISC_PARAMETERS_2;
	MLX5_SET(fte_match_param, spec->match_criteria, misc_parameters_2.metadata_reg_a,
		 MLX5_ETH_WQE_FT_META_IPSEC);
	MLX5_SET(fte_match_param, spec->match_value, misc_parameters_2.metadata_reg_a,
		 MLX5_ETH_WQE_FT_META_IPSEC);

	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_ALLOW |
			  MLX5_FLOW_CONTEXT_ACTION_IPSEC_ENCRYPT;
	rule = mlx5_add_flow_rules(priv->ipsec->tx_fs->ft, spec, &flow_act, शून्य, 0);
	अगर (IS_ERR(rule)) अणु
		err = PTR_ERR(rule);
		netdev_err(priv->netdev, "fail to add ipsec rule attrs->action=0x%x, err=%d\n",
			   attrs->action, err);
		जाओ out;
	पूर्ण

	ipsec_rule->rule = rule;

out:
	kvमुक्त(spec);
	अगर (err)
		tx_ft_put(priv);
	वापस err;
पूर्ण

अटल व्योम rx_del_rule(काष्ठा mlx5e_priv *priv,
			काष्ठा mlx5_accel_esp_xfrm_attrs *attrs,
			काष्ठा mlx5e_ipsec_rule *ipsec_rule)
अणु
	mlx5_del_flow_rules(ipsec_rule->rule);
	ipsec_rule->rule = शून्य;

	mlx5_modअगरy_header_dealloc(priv->mdev, ipsec_rule->set_modअगरy_hdr);
	ipsec_rule->set_modअगरy_hdr = शून्य;

	rx_ft_put(priv, attrs->is_ipv6 ? ACCEL_FS_ESP6 : ACCEL_FS_ESP4);
पूर्ण

अटल व्योम tx_del_rule(काष्ठा mlx5e_priv *priv,
			काष्ठा mlx5e_ipsec_rule *ipsec_rule)
अणु
	mlx5_del_flow_rules(ipsec_rule->rule);
	ipsec_rule->rule = शून्य;

	tx_ft_put(priv);
पूर्ण

पूर्णांक mlx5e_accel_ipsec_fs_add_rule(काष्ठा mlx5e_priv *priv,
				  काष्ठा mlx5_accel_esp_xfrm_attrs *attrs,
				  u32 ipsec_obj_id,
				  काष्ठा mlx5e_ipsec_rule *ipsec_rule)
अणु
	अगर (!priv->ipsec->rx_fs)
		वापस -EOPNOTSUPP;

	अगर (attrs->action == MLX5_ACCEL_ESP_ACTION_DECRYPT)
		वापस rx_add_rule(priv, attrs, ipsec_obj_id, ipsec_rule);
	अन्यथा
		वापस tx_add_rule(priv, attrs, ipsec_obj_id, ipsec_rule);
पूर्ण

व्योम mlx5e_accel_ipsec_fs_del_rule(काष्ठा mlx5e_priv *priv,
				   काष्ठा mlx5_accel_esp_xfrm_attrs *attrs,
				   काष्ठा mlx5e_ipsec_rule *ipsec_rule)
अणु
	अगर (!priv->ipsec->rx_fs)
		वापस;

	अगर (attrs->action == MLX5_ACCEL_ESP_ACTION_DECRYPT)
		rx_del_rule(priv, attrs, ipsec_rule);
	अन्यथा
		tx_del_rule(priv, ipsec_rule);
पूर्ण

अटल व्योम fs_cleanup_tx(काष्ठा mlx5e_priv *priv)
अणु
	mutex_destroy(&priv->ipsec->tx_fs->mutex);
	WARN_ON(priv->ipsec->tx_fs->refcnt);
	kमुक्त(priv->ipsec->tx_fs);
	priv->ipsec->tx_fs = शून्य;
पूर्ण

अटल व्योम fs_cleanup_rx(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_accel_fs_esp_prot *fs_prot;
	काष्ठा mlx5e_accel_fs_esp *accel_esp;
	क्रमागत accel_fs_esp_type i;

	accel_esp = priv->ipsec->rx_fs;
	क्रम (i = 0; i < ACCEL_FS_ESP_NUM_TYPES; i++) अणु
		fs_prot = &accel_esp->fs_prot[i];
		mutex_destroy(&fs_prot->prot_mutex);
		WARN_ON(fs_prot->refcnt);
	पूर्ण
	kमुक्त(priv->ipsec->rx_fs);
	priv->ipsec->rx_fs = शून्य;
पूर्ण

अटल पूर्णांक fs_init_tx(काष्ठा mlx5e_priv *priv)
अणु
	priv->ipsec->tx_fs =
		kzalloc(माप(काष्ठा mlx5e_ipsec_tx), GFP_KERNEL);
	अगर (!priv->ipsec->tx_fs)
		वापस -ENOMEM;

	mutex_init(&priv->ipsec->tx_fs->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक fs_init_rx(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_accel_fs_esp_prot *fs_prot;
	काष्ठा mlx5e_accel_fs_esp *accel_esp;
	क्रमागत accel_fs_esp_type i;

	priv->ipsec->rx_fs =
		kzalloc(माप(काष्ठा mlx5e_accel_fs_esp), GFP_KERNEL);
	अगर (!priv->ipsec->rx_fs)
		वापस -ENOMEM;

	accel_esp = priv->ipsec->rx_fs;
	क्रम (i = 0; i < ACCEL_FS_ESP_NUM_TYPES; i++) अणु
		fs_prot = &accel_esp->fs_prot[i];
		mutex_init(&fs_prot->prot_mutex);
	पूर्ण

	वापस 0;
पूर्ण

व्योम mlx5e_accel_ipsec_fs_cleanup(काष्ठा mlx5e_priv *priv)
अणु
	अगर (!priv->ipsec->rx_fs)
		वापस;

	fs_cleanup_tx(priv);
	fs_cleanup_rx(priv);
पूर्ण

पूर्णांक mlx5e_accel_ipsec_fs_init(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक err;

	अगर (!mlx5_is_ipsec_device(priv->mdev) || !priv->ipsec)
		वापस -EOPNOTSUPP;

	err = fs_init_tx(priv);
	अगर (err)
		वापस err;

	err = fs_init_rx(priv);
	अगर (err)
		fs_cleanup_tx(priv);

	वापस err;
पूर्ण
