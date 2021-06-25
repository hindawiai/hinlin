<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020, Mellanox Technologies */

#अगर_अघोषित __MLX5E_TRAP_H__
#घोषणा __MLX5E_TRAP_H__

#समावेश "../en.h"
#समावेश "../devlink.h"

काष्ठा mlx5e_trap अणु
	/* data path */
	काष्ठा mlx5e_rq            rq;
	काष्ठा mlx5e_tir           tir;
	काष्ठा napi_काष्ठा         napi;
	काष्ठा device             *pdev;
	काष्ठा net_device         *netdev;
	__be32                     mkey_be;

	/* data path - accessed per napi poll */
	काष्ठा mlx5e_ch_stats     *stats;

	/* control */
	काष्ठा mlx5e_priv         *priv;
	काष्ठा mlx5_core_dev      *mdev;
	काष्ठा hwtstamp_config    *tstamp;
	DECLARE_BITMAP(state, MLX5E_CHANNEL_NUM_STATES);

	काष्ठा mlx5e_params        params;
	काष्ठा mlx5e_rq_param      rq_param;
पूर्ण;

व्योम mlx5e_बंद_trap(काष्ठा mlx5e_trap *trap);
व्योम mlx5e_deactivate_trap(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_handle_trap_event(काष्ठा mlx5e_priv *priv, काष्ठा mlx5_trap_ctx *trap_ctx);
पूर्णांक mlx5e_apply_traps(काष्ठा mlx5e_priv *priv, bool enable);

#पूर्ण_अगर
