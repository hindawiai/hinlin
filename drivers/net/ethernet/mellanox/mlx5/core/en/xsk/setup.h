<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies. */

#अगर_अघोषित __MLX5_EN_XSK_SETUP_H__
#घोषणा __MLX5_EN_XSK_SETUP_H__

#समावेश "en.h"

काष्ठा mlx5e_xsk_param;

bool mlx5e_validate_xsk_param(काष्ठा mlx5e_params *params,
			      काष्ठा mlx5e_xsk_param *xsk,
			      काष्ठा mlx5_core_dev *mdev);
पूर्णांक mlx5e_खोलो_xsk(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_params *params,
		   काष्ठा mlx5e_xsk_param *xsk, काष्ठा xsk_buff_pool *pool,
		   काष्ठा mlx5e_channel *c);
व्योम mlx5e_बंद_xsk(काष्ठा mlx5e_channel *c);
व्योम mlx5e_activate_xsk(काष्ठा mlx5e_channel *c);
व्योम mlx5e_deactivate_xsk(काष्ठा mlx5e_channel *c);
पूर्णांक mlx5e_xsk_redirect_rqt_to_channel(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_channel *c);
पूर्णांक mlx5e_xsk_redirect_rqt_to_drop(काष्ठा mlx5e_priv *priv, u16 ix);
पूर्णांक mlx5e_xsk_redirect_rqts_to_channels(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_channels *chs);
व्योम mlx5e_xsk_redirect_rqts_to_drop(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_channels *chs);

#पूर्ण_अगर /* __MLX5_EN_XSK_SETUP_H__ */
