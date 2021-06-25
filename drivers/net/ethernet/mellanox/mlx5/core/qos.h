<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020, Mellanox Technologies inc. All rights reserved. */

#अगर_अघोषित __MLX5_QOS_H
#घोषणा __MLX5_QOS_H

#समावेश "mlx5_core.h"

#घोषणा MLX5_DEBUG_QOS_MASK BIT(4)

#घोषणा qos_err(mdev, fmt, ...) \
	mlx5_core_err(mdev, "QoS: " fmt, ##__VA_ARGS__)
#घोषणा qos_warn(mdev, fmt, ...) \
	mlx5_core_warn(mdev, "QoS: " fmt, ##__VA_ARGS__)
#घोषणा qos_dbg(mdev, fmt, ...) \
	mlx5_core_dbg_mask(mdev, MLX5_DEBUG_QOS_MASK, "QoS: " fmt, ##__VA_ARGS__)

bool mlx5_qos_is_supported(काष्ठा mlx5_core_dev *mdev);
पूर्णांक mlx5_qos_max_leaf_nodes(काष्ठा mlx5_core_dev *mdev);

पूर्णांक mlx5_qos_create_leaf_node(काष्ठा mlx5_core_dev *mdev, u32 parent_id,
			      u32 bw_share, u32 max_avg_bw, u32 *id);
पूर्णांक mlx5_qos_create_inner_node(काष्ठा mlx5_core_dev *mdev, u32 parent_id,
			       u32 bw_share, u32 max_avg_bw, u32 *id);
पूर्णांक mlx5_qos_create_root_node(काष्ठा mlx5_core_dev *mdev, u32 *id);
पूर्णांक mlx5_qos_update_node(काष्ठा mlx5_core_dev *mdev, u32 parent_id, u32 bw_share,
			 u32 max_avg_bw, u32 id);
पूर्णांक mlx5_qos_destroy_node(काष्ठा mlx5_core_dev *mdev, u32 id);

#पूर्ण_अगर
