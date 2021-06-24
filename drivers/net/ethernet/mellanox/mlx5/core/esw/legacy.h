<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2021 Mellanox Technologies Ltd */

#अगर_अघोषित __MLX5_ESW_LEGACY_H__
#घोषणा __MLX5_ESW_LEGACY_H__

#घोषणा MLX5_LEGACY_SRIOV_VPORT_EVENTS (MLX5_VPORT_UC_ADDR_CHANGE | \
					MLX5_VPORT_MC_ADDR_CHANGE | \
					MLX5_VPORT_PROMISC_CHANGE)

काष्ठा mlx5_eचयन;

पूर्णांक esw_legacy_enable(काष्ठा mlx5_eचयन *esw);
व्योम esw_legacy_disable(काष्ठा mlx5_eचयन *esw);

पूर्णांक esw_legacy_vport_acl_setup(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport *vport);
व्योम esw_legacy_vport_acl_cleanup(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport *vport);

पूर्णांक mlx5_esw_query_vport_drop_stats(काष्ठा mlx5_core_dev *dev,
				    काष्ठा mlx5_vport *vport,
				    काष्ठा mlx5_vport_drop_stats *stats);
#पूर्ण_अगर
