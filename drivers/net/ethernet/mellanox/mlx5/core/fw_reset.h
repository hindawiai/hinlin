<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020, Mellanox Technologies inc.  All rights reserved. */

#अगर_अघोषित __MLX5_FW_RESET_H
#घोषणा __MLX5_FW_RESET_H

#समावेश "mlx5_core.h"

व्योम mlx5_fw_reset_enable_remote_dev_reset_set(काष्ठा mlx5_core_dev *dev, bool enable);
bool mlx5_fw_reset_enable_remote_dev_reset_get(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_fw_reset_query(काष्ठा mlx5_core_dev *dev, u8 *reset_level, u8 *reset_type);
पूर्णांक mlx5_fw_reset_set_reset_sync(काष्ठा mlx5_core_dev *dev, u8 reset_type_sel);
पूर्णांक mlx5_fw_reset_set_live_patch(काष्ठा mlx5_core_dev *dev);

पूर्णांक mlx5_fw_reset_रुको_reset_करोne(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_fw_reset_events_start(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_fw_reset_events_stop(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_fw_reset_init(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_fw_reset_cleanup(काष्ठा mlx5_core_dev *dev);

#पूर्ण_अगर
