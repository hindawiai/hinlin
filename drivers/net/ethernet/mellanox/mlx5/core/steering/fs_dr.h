<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
 * Copyright (c) 2019 Mellanox Technologies
 */

#अगर_अघोषित _MLX5_FS_DR_
#घोषणा _MLX5_FS_DR_

#समावेश "mlx5dr.h"

काष्ठा mlx5_flow_root_namespace;
काष्ठा fs_fte;

काष्ठा mlx5_fs_dr_action अणु
	काष्ठा mlx5dr_action *dr_action;
पूर्ण;

काष्ठा mlx5_fs_dr_ns अणु
	काष्ठा mlx5_dr_ns *dr_ns;
पूर्ण;

काष्ठा mlx5_fs_dr_rule अणु
	काष्ठा mlx5dr_rule    *dr_rule;
	/* Only actions created by fs_dr */
	काष्ठा mlx5dr_action  **dr_actions;
	पूर्णांक                      num_actions;
पूर्ण;

काष्ठा mlx5_fs_dr_करोमुख्य अणु
	काष्ठा mlx5dr_करोमुख्य	*dr_करोमुख्य;
पूर्ण;

काष्ठा mlx5_fs_dr_matcher अणु
	काष्ठा mlx5dr_matcher *dr_matcher;
पूर्ण;

काष्ठा mlx5_fs_dr_table अणु
	काष्ठा mlx5dr_table  *dr_table;
	काष्ठा mlx5dr_action *miss_action;
पूर्ण;

#अगर_घोषित CONFIG_MLX5_SW_STEERING

bool mlx5_fs_dr_is_supported(काष्ठा mlx5_core_dev *dev);

स्थिर काष्ठा mlx5_flow_cmds *mlx5_fs_cmd_get_dr_cmds(व्योम);

#अन्यथा

अटल अंतरभूत स्थिर काष्ठा mlx5_flow_cmds *mlx5_fs_cmd_get_dr_cmds(व्योम)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool mlx5_fs_dr_is_supported(काष्ठा mlx5_core_dev *dev)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* CONFIG_MLX5_SW_STEERING */
#पूर्ण_अगर
