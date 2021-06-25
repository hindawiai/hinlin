<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020, Mellanox Technologies inc. All rights reserved. */

#अगर_अघोषित __MLX5_IPSEC_STEERING_H__
#घोषणा __MLX5_IPSEC_STEERING_H__

#समावेश "en.h"
#समावेश "ipsec.h"
#समावेश "accel/ipsec_offload.h"
#समावेश "en/fs.h"

#अगर_घोषित CONFIG_MLX5_EN_IPSEC
व्योम mlx5e_accel_ipsec_fs_cleanup(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_accel_ipsec_fs_init(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_accel_ipsec_fs_add_rule(काष्ठा mlx5e_priv *priv,
				  काष्ठा mlx5_accel_esp_xfrm_attrs *attrs,
				  u32 ipsec_obj_id,
				  काष्ठा mlx5e_ipsec_rule *ipsec_rule);
व्योम mlx5e_accel_ipsec_fs_del_rule(काष्ठा mlx5e_priv *priv,
				   काष्ठा mlx5_accel_esp_xfrm_attrs *attrs,
				   काष्ठा mlx5e_ipsec_rule *ipsec_rule);
#अन्यथा
अटल अंतरभूत व्योम mlx5e_accel_ipsec_fs_cleanup(काष्ठा mlx5e_priv *priv) अणुपूर्ण
अटल अंतरभूत पूर्णांक mlx5e_accel_ipsec_fs_init(काष्ठा mlx5e_priv *priv) अणु वापस 0; पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* __MLX5_IPSEC_STEERING_H__ */
