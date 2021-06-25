<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020, Mellanox Technologies inc. All rights reserved. */

#अगर_अघोषित __MLX5E_ACCEL_FS_TCP_H__
#घोषणा __MLX5E_ACCEL_FS_TCP_H__

#समावेश "en.h"

#अगर_घोषित CONFIG_MLX5_EN_TLS
पूर्णांक mlx5e_accel_fs_tcp_create(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_accel_fs_tcp_destroy(काष्ठा mlx5e_priv *priv);
काष्ठा mlx5_flow_handle *mlx5e_accel_fs_add_sk(काष्ठा mlx5e_priv *priv,
					       काष्ठा sock *sk, u32 tirn,
					       uपूर्णांक32_t flow_tag);
व्योम mlx5e_accel_fs_del_sk(काष्ठा mlx5_flow_handle *rule);
#अन्यथा
अटल अंतरभूत पूर्णांक mlx5e_accel_fs_tcp_create(काष्ठा mlx5e_priv *priv) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम mlx5e_accel_fs_tcp_destroy(काष्ठा mlx5e_priv *priv) अणुपूर्ण
अटल अंतरभूत काष्ठा mlx5_flow_handle *mlx5e_accel_fs_add_sk(काष्ठा mlx5e_priv *priv,
							     काष्ठा sock *sk, u32 tirn,
							     uपूर्णांक32_t flow_tag)
अणु वापस ERR_PTR(-EOPNOTSUPP); पूर्ण
अटल अंतरभूत व्योम mlx5e_accel_fs_del_sk(काष्ठा mlx5_flow_handle *rule) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __MLX5E_ACCEL_FS_TCP_H__ */

