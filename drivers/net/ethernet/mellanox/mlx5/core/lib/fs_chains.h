<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020 Mellanox Technologies. */

#अगर_अघोषित __ML5_ESW_CHAINS_H__
#घोषणा __ML5_ESW_CHAINS_H__

#समावेश <linux/mlx5/fs.h>

काष्ठा mlx5_fs_chains;
काष्ठा mlx5_mapped_obj;

क्रमागत mlx5_chains_flags अणु
	MLX5_CHAINS_AND_PRIOS_SUPPORTED = BIT(0),
	MLX5_CHAINS_IGNORE_FLOW_LEVEL_SUPPORTED = BIT(1),
	MLX5_CHAINS_FT_TUNNEL_SUPPORTED = BIT(2),
पूर्ण;

काष्ठा mlx5_chains_attr अणु
	क्रमागत mlx5_flow_namespace_type ns;
	u32 flags;
	u32 max_ft_sz;
	u32 max_grp_num;
	काष्ठा mlx5_flow_table *शेष_ft;
	काष्ठा mapping_ctx *mapping;
पूर्ण;

#अगर IS_ENABLED(CONFIG_MLX5_CLS_ACT)

bool
mlx5_chains_prios_supported(काष्ठा mlx5_fs_chains *chains);
bool mlx5_chains_ignore_flow_level_supported(काष्ठा mlx5_fs_chains *chains);
bool
mlx5_chains_backwards_supported(काष्ठा mlx5_fs_chains *chains);
u32
mlx5_chains_get_prio_range(काष्ठा mlx5_fs_chains *chains);
u32
mlx5_chains_get_chain_range(काष्ठा mlx5_fs_chains *chains);
u32
mlx5_chains_get_nf_ft_chain(काष्ठा mlx5_fs_chains *chains);

काष्ठा mlx5_flow_table *
mlx5_chains_get_table(काष्ठा mlx5_fs_chains *chains, u32 chain, u32 prio,
		      u32 level);
व्योम
mlx5_chains_put_table(काष्ठा mlx5_fs_chains *chains, u32 chain, u32 prio,
		      u32 level);

काष्ठा mlx5_flow_table *
mlx5_chains_get_tc_end_ft(काष्ठा mlx5_fs_chains *chains);

काष्ठा mlx5_flow_table *
mlx5_chains_create_global_table(काष्ठा mlx5_fs_chains *chains);
व्योम
mlx5_chains_destroy_global_table(काष्ठा mlx5_fs_chains *chains,
				 काष्ठा mlx5_flow_table *ft);

पूर्णांक
mlx5_chains_get_chain_mapping(काष्ठा mlx5_fs_chains *chains, u32 chain,
			      u32 *chain_mapping);
पूर्णांक
mlx5_chains_put_chain_mapping(काष्ठा mlx5_fs_chains *chains,
			      u32 chain_mapping);

काष्ठा mlx5_fs_chains *
mlx5_chains_create(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_chains_attr *attr);
व्योम mlx5_chains_destroy(काष्ठा mlx5_fs_chains *chains);

व्योम
mlx5_chains_set_end_ft(काष्ठा mlx5_fs_chains *chains,
		       काष्ठा mlx5_flow_table *ft);

#अन्यथा /* CONFIG_MLX5_CLS_ACT */

अटल अंतरभूत bool
mlx5_chains_ignore_flow_level_supported(काष्ठा mlx5_fs_chains *chains)
अणु वापस false; पूर्ण

अटल अंतरभूत काष्ठा mlx5_flow_table *
mlx5_chains_get_table(काष्ठा mlx5_fs_chains *chains, u32 chain, u32 prio,
		      u32 level) अणु वापस ERR_PTR(-EOPNOTSUPP); पूर्ण
अटल अंतरभूत व्योम
mlx5_chains_put_table(काष्ठा mlx5_fs_chains *chains, u32 chain, u32 prio,
		      u32 level) अणुपूर्ण;

अटल अंतरभूत काष्ठा mlx5_flow_table *
mlx5_chains_get_tc_end_ft(काष्ठा mlx5_fs_chains *chains) अणु वापस ERR_PTR(-EOPNOTSUPP); पूर्ण

अटल अंतरभूत काष्ठा mlx5_fs_chains *
mlx5_chains_create(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_chains_attr *attr)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम
mlx5_chains_destroy(काष्ठा mlx5_fs_chains *chains) अणुपूर्ण;

#पूर्ण_अगर /* CONFIG_MLX5_CLS_ACT */

#पूर्ण_अगर /* __ML5_ESW_CHAINS_H__ */
