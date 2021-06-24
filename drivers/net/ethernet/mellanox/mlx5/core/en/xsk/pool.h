<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019-2020, Mellanox Technologies inc. All rights reserved. */

#अगर_अघोषित __MLX5_EN_XSK_POOL_H__
#घोषणा __MLX5_EN_XSK_POOL_H__

#समावेश "en.h"

अटल अंतरभूत काष्ठा xsk_buff_pool *mlx5e_xsk_get_pool(काष्ठा mlx5e_params *params,
						       काष्ठा mlx5e_xsk *xsk, u16 ix)
अणु
	अगर (!xsk || !xsk->pools)
		वापस शून्य;

	अगर (unlikely(ix >= params->num_channels))
		वापस शून्य;

	वापस xsk->pools[ix];
पूर्ण

काष्ठा mlx5e_xsk_param;
व्योम mlx5e_build_xsk_param(काष्ठा xsk_buff_pool *pool, काष्ठा mlx5e_xsk_param *xsk);

/* .nकरो_bpf callback. */
पूर्णांक mlx5e_xsk_setup_pool(काष्ठा net_device *dev, काष्ठा xsk_buff_pool *pool, u16 qid);

#पूर्ण_अगर /* __MLX5_EN_XSK_POOL_H__ */
