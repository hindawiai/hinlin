<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2021 Mellanox Technologies. */

#अगर_अघोषित __MLX5E_FS_TT_REसूचीECT_H__
#घोषणा __MLX5E_FS_TT_REसूचीECT_H__

#समावेश "en.h"
#समावेश "en/fs.h"

व्योम mlx5e_fs_tt_redirect_del_rule(काष्ठा mlx5_flow_handle *rule);

/* UDP traffic type redirect */
काष्ठा mlx5_flow_handle *
mlx5e_fs_tt_redirect_udp_add_rule(काष्ठा mlx5e_priv *priv,
				  क्रमागत mlx5e_traffic_types ttc_type,
				  u32 tir_num, u16 d_port);
व्योम mlx5e_fs_tt_redirect_udp_destroy(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_fs_tt_redirect_udp_create(काष्ठा mlx5e_priv *priv);

/* ANY traffic type redirect*/
काष्ठा mlx5_flow_handle *
mlx5e_fs_tt_redirect_any_add_rule(काष्ठा mlx5e_priv *priv,
				  u32 tir_num, u16 ether_type);
व्योम mlx5e_fs_tt_redirect_any_destroy(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_fs_tt_redirect_any_create(काष्ठा mlx5e_priv *priv);
#पूर्ण_अगर
