<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies */

#समावेश <linux/mlx5/vport.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <net/addrconf.h>

#समावेश "lib/mlx5.h"
#समावेश "eswitch.h"
#समावेश "fs_core.h"
#समावेश "rdma.h"

अटल व्योम mlx5_rdma_disable_roce_steering(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_core_roce *roce = &dev->priv.roce;

	mlx5_del_flow_rules(roce->allow_rule);
	mlx5_destroy_flow_group(roce->fg);
	mlx5_destroy_flow_table(roce->ft);
पूर्ण

अटल पूर्णांक mlx5_rdma_enable_roce_steering(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	काष्ठा mlx5_core_roce *roce = &dev->priv.roce;
	काष्ठा mlx5_flow_handle *flow_rule = शून्य;
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5_flow_namespace *ns = शून्य;
	काष्ठा mlx5_flow_act flow_act = अणुपूर्ण;
	काष्ठा mlx5_flow_spec *spec;
	काष्ठा mlx5_flow_table *ft;
	काष्ठा mlx5_flow_group *fg;
	व्योम *match_criteria;
	u32 *flow_group_in;
	व्योम *misc;
	पूर्णांक err;

	अगर (!(MLX5_CAP_FLOWTABLE_RDMA_RX(dev, ft_support) &&
	      MLX5_CAP_FLOWTABLE_RDMA_RX(dev, table_miss_action_करोमुख्य)))
		वापस -EOPNOTSUPP;

	flow_group_in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!flow_group_in)
		वापस -ENOMEM;
	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec) अणु
		kvमुक्त(flow_group_in);
		वापस -ENOMEM;
	पूर्ण

	ns = mlx5_get_flow_namespace(dev, MLX5_FLOW_NAMESPACE_RDMA_RX_KERNEL);
	अगर (!ns) अणु
		mlx5_core_err(dev, "Failed to get RDMA RX namespace");
		err = -EOPNOTSUPP;
		जाओ मुक्त;
	पूर्ण

	ft_attr.max_fte = 1;
	ft = mlx5_create_flow_table(ns, &ft_attr);
	अगर (IS_ERR(ft)) अणु
		mlx5_core_err(dev, "Failed to create RDMA RX flow table");
		err = PTR_ERR(ft);
		जाओ मुक्त;
	पूर्ण

	MLX5_SET(create_flow_group_in, flow_group_in, match_criteria_enable,
		 MLX5_MATCH_MISC_PARAMETERS);
	match_criteria = MLX5_ADDR_OF(create_flow_group_in, flow_group_in,
				      match_criteria);
	MLX5_SET_TO_ONES(fte_match_param, match_criteria,
			 misc_parameters.source_port);

	fg = mlx5_create_flow_group(ft, flow_group_in);
	अगर (IS_ERR(fg)) अणु
		err = PTR_ERR(fg);
		mlx5_core_err(dev, "Failed to create RDMA RX flow group err(%d)\n", err);
		जाओ destroy_flow_table;
	पूर्ण

	spec->match_criteria_enable = MLX5_MATCH_MISC_PARAMETERS;
	misc = MLX5_ADDR_OF(fte_match_param, spec->match_value,
			    misc_parameters);
	MLX5_SET(fte_match_set_misc, misc, source_port,
		 dev->priv.eचयन->manager_vport);
	misc = MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
			    misc_parameters);
	MLX5_SET_TO_ONES(fte_match_set_misc, misc, source_port);

	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_ALLOW;
	flow_rule = mlx5_add_flow_rules(ft, spec, &flow_act, शून्य, 0);
	अगर (IS_ERR(flow_rule)) अणु
		err = PTR_ERR(flow_rule);
		mlx5_core_err(dev, "Failed to add RoCE allow rule, err=%d\n",
			      err);
		जाओ destroy_flow_group;
	पूर्ण

	kvमुक्त(spec);
	kvमुक्त(flow_group_in);
	roce->ft = ft;
	roce->fg = fg;
	roce->allow_rule = flow_rule;

	वापस 0;

destroy_flow_group:
	mlx5_destroy_flow_group(fg);
destroy_flow_table:
	mlx5_destroy_flow_table(ft);
मुक्त:
	kvमुक्त(spec);
	kvमुक्त(flow_group_in);
	वापस err;
पूर्ण

अटल व्योम mlx5_rdma_del_roce_addr(काष्ठा mlx5_core_dev *dev)
अणु
	mlx5_core_roce_gid_set(dev, 0, 0, 0,
			       शून्य, शून्य, false, 0, 1);
पूर्ण

अटल व्योम mlx5_rdma_make_शेष_gid(काष्ठा mlx5_core_dev *dev, जोड़ ib_gid *gid)
अणु
	u8 hw_id[ETH_ALEN];

	mlx5_query_mac_address(dev, hw_id);
	gid->global.subnet_prefix = cpu_to_be64(0xfe80000000000000LL);
	addrconf_addr_eui48(&gid->raw[8], hw_id);
पूर्ण

अटल पूर्णांक mlx5_rdma_add_roce_addr(काष्ठा mlx5_core_dev *dev)
अणु
	जोड़ ib_gid gid;
	u8 mac[ETH_ALEN];

	mlx5_rdma_make_शेष_gid(dev, &gid);
	वापस mlx5_core_roce_gid_set(dev, 0,
				      MLX5_ROCE_VERSION_1,
				      0, gid.raw, mac,
				      false, 0, 1);
पूर्ण

व्योम mlx5_rdma_disable_roce(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_core_roce *roce = &dev->priv.roce;

	अगर (!roce->ft)
		वापस;

	mlx5_rdma_disable_roce_steering(dev);
	mlx5_rdma_del_roce_addr(dev);
	mlx5_nic_vport_disable_roce(dev);
पूर्ण

व्योम mlx5_rdma_enable_roce(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक err;

	अगर (!MLX5_CAP_GEN(dev, roce))
		वापस;

	err = mlx5_nic_vport_enable_roce(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to enable RoCE: %d\n", err);
		वापस;
	पूर्ण

	err = mlx5_rdma_add_roce_addr(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to add RoCE address: %d\n", err);
		जाओ disable_roce;
	पूर्ण

	err = mlx5_rdma_enable_roce_steering(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to enable RoCE steering: %d\n", err);
		जाओ del_roce_addr;
	पूर्ण

	वापस;

del_roce_addr:
	mlx5_rdma_del_roce_addr(dev);
disable_roce:
	mlx5_nic_vport_disable_roce(dev);
पूर्ण
