<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019, Mellanox Technologies */

#अगर_अघोषित __MLX5_DEVLINK_H__
#घोषणा __MLX5_DEVLINK_H__

#समावेश <net/devlink.h>

क्रमागत mlx5_devlink_param_id अणु
	MLX5_DEVLINK_PARAM_ID_BASE = DEVLINK_PARAM_GENERIC_ID_MAX,
	MLX5_DEVLINK_PARAM_ID_FLOW_STEERING_MODE,
	MLX5_DEVLINK_PARAM_ID_ESW_LARGE_GROUP_NUM,
	MLX5_DEVLINK_PARAM_ID_ESW_PORT_METADATA,
पूर्ण;

काष्ठा mlx5_trap_ctx अणु
	पूर्णांक id;
	पूर्णांक action;
पूर्ण;

काष्ठा mlx5_devlink_trap अणु
	काष्ठा mlx5_trap_ctx trap;
	व्योम *item;
	काष्ठा list_head list;
पूर्ण;

काष्ठा mlx5_core_dev;
व्योम mlx5_devlink_trap_report(काष्ठा mlx5_core_dev *dev, पूर्णांक trap_id, काष्ठा sk_buff *skb,
			      काष्ठा devlink_port *dl_port);
पूर्णांक mlx5_devlink_trap_get_num_active(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_devlink_traps_get_action(काष्ठा mlx5_core_dev *dev, पूर्णांक trap_id,
				  क्रमागत devlink_trap_action *action);

काष्ठा devlink *mlx5_devlink_alloc(व्योम);
व्योम mlx5_devlink_मुक्त(काष्ठा devlink *devlink);
पूर्णांक mlx5_devlink_रेजिस्टर(काष्ठा devlink *devlink, काष्ठा device *dev);
व्योम mlx5_devlink_unरेजिस्टर(काष्ठा devlink *devlink);

#पूर्ण_अगर /* __MLX5_DEVLINK_H__ */
