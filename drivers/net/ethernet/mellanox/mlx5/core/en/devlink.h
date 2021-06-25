<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020, Mellanox Technologies inc.  All rights reserved. */

#अगर_अघोषित __MLX5E_EN_DEVLINK_H
#घोषणा __MLX5E_EN_DEVLINK_H

#समावेश <net/devlink.h>
#समावेश "en.h"

पूर्णांक mlx5e_devlink_port_रेजिस्टर(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_devlink_port_unरेजिस्टर(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_devlink_port_type_eth_set(काष्ठा mlx5e_priv *priv);
काष्ठा devlink_port *mlx5e_get_devlink_port(काष्ठा net_device *dev);

अटल अंतरभूत काष्ठा devlink_port *
mlx5e_devlink_get_dl_port(काष्ठा mlx5e_priv *priv)
अणु
	वापस &priv->mdev->mlx5e_res.dl_port;
पूर्ण

#पूर्ण_अगर
