<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020, Mellanox Technologies inc. All rights reserved. */

#समावेश "qos.h"

#घोषणा MLX5_QOS_DEFAULT_DWRR_UID 0

bool mlx5_qos_is_supported(काष्ठा mlx5_core_dev *mdev)
अणु
	अगर (!MLX5_CAP_GEN(mdev, qos))
		वापस false;
	अगर (!MLX5_CAP_QOS(mdev, nic_sq_scheduling))
		वापस false;
	अगर (!MLX5_CAP_QOS(mdev, nic_bw_share))
		वापस false;
	अगर (!MLX5_CAP_QOS(mdev, nic_rate_limit))
		वापस false;
	वापस true;
पूर्ण

पूर्णांक mlx5_qos_max_leaf_nodes(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस 1 << MLX5_CAP_QOS(mdev, log_max_qos_nic_queue_group);
पूर्ण

पूर्णांक mlx5_qos_create_leaf_node(काष्ठा mlx5_core_dev *mdev, u32 parent_id,
			      u32 bw_share, u32 max_avg_bw, u32 *id)
अणु
	u32 sched_ctx[MLX5_ST_SZ_DW(scheduling_context)] = अणु0पूर्ण;

	MLX5_SET(scheduling_context, sched_ctx, parent_element_id, parent_id);
	MLX5_SET(scheduling_context, sched_ctx, element_type,
		 SCHEDULING_CONTEXT_ELEMENT_TYPE_QUEUE_GROUP);
	MLX5_SET(scheduling_context, sched_ctx, bw_share, bw_share);
	MLX5_SET(scheduling_context, sched_ctx, max_average_bw, max_avg_bw);

	वापस mlx5_create_scheduling_element_cmd(mdev, SCHEDULING_HIERARCHY_NIC,
						  sched_ctx, id);
पूर्ण

पूर्णांक mlx5_qos_create_inner_node(काष्ठा mlx5_core_dev *mdev, u32 parent_id,
			       u32 bw_share, u32 max_avg_bw, u32 *id)
अणु
	u32 sched_ctx[MLX5_ST_SZ_DW(scheduling_context)] = अणु0पूर्ण;
	व्योम *attr;

	MLX5_SET(scheduling_context, sched_ctx, parent_element_id, parent_id);
	MLX5_SET(scheduling_context, sched_ctx, element_type,
		 SCHEDULING_CONTEXT_ELEMENT_TYPE_TSAR);
	MLX5_SET(scheduling_context, sched_ctx, bw_share, bw_share);
	MLX5_SET(scheduling_context, sched_ctx, max_average_bw, max_avg_bw);

	attr = MLX5_ADDR_OF(scheduling_context, sched_ctx, element_attributes);
	MLX5_SET(tsar_element, attr, tsar_type, TSAR_ELEMENT_TSAR_TYPE_DWRR);

	वापस mlx5_create_scheduling_element_cmd(mdev, SCHEDULING_HIERARCHY_NIC,
						  sched_ctx, id);
पूर्ण

पूर्णांक mlx5_qos_create_root_node(काष्ठा mlx5_core_dev *mdev, u32 *id)
अणु
	वापस mlx5_qos_create_inner_node(mdev, MLX5_QOS_DEFAULT_DWRR_UID, 0, 0, id);
पूर्ण

पूर्णांक mlx5_qos_update_node(काष्ठा mlx5_core_dev *mdev, u32 parent_id,
			 u32 bw_share, u32 max_avg_bw, u32 id)
अणु
	u32 sched_ctx[MLX5_ST_SZ_DW(scheduling_context)] = अणु0पूर्ण;
	u32 biपंचांगask = 0;

	MLX5_SET(scheduling_context, sched_ctx, parent_element_id, parent_id);
	MLX5_SET(scheduling_context, sched_ctx, bw_share, bw_share);
	MLX5_SET(scheduling_context, sched_ctx, max_average_bw, max_avg_bw);

	biपंचांगask |= MODIFY_SCHEDULING_ELEMENT_IN_MODIFY_BITMASK_BW_SHARE;
	biपंचांगask |= MODIFY_SCHEDULING_ELEMENT_IN_MODIFY_BITMASK_MAX_AVERAGE_BW;

	वापस mlx5_modअगरy_scheduling_element_cmd(mdev, SCHEDULING_HIERARCHY_NIC,
						  sched_ctx, id, biपंचांगask);
पूर्ण

पूर्णांक mlx5_qos_destroy_node(काष्ठा mlx5_core_dev *mdev, u32 id)
अणु
	वापस mlx5_destroy_scheduling_element_cmd(mdev, SCHEDULING_HIERARCHY_NIC, id);
पूर्ण
