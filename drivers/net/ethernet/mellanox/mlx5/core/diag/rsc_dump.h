<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019 Mellanox Technologies. */

#अगर_अघोषित __MLX5_RSC_DUMP_H
#घोषणा __MLX5_RSC_DUMP_H

#समावेश <linux/mlx5/rsc_dump.h>
#समावेश <linux/mlx5/driver.h>
#समावेश "mlx5_core.h"

#घोषणा MLX5_RSC_DUMP_ALL 0xFFFF
काष्ठा mlx5_rsc_dump_cmd;
काष्ठा mlx5_rsc_dump;

काष्ठा mlx5_rsc_dump *mlx5_rsc_dump_create(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_rsc_dump_destroy(काष्ठा mlx5_core_dev *dev);

पूर्णांक mlx5_rsc_dump_init(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_rsc_dump_cleanup(काष्ठा mlx5_core_dev *dev);

काष्ठा mlx5_rsc_dump_cmd *mlx5_rsc_dump_cmd_create(काष्ठा mlx5_core_dev *dev,
						   काष्ठा mlx5_rsc_key *key);
व्योम mlx5_rsc_dump_cmd_destroy(काष्ठा mlx5_rsc_dump_cmd *cmd);

पूर्णांक mlx5_rsc_dump_next(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_rsc_dump_cmd *cmd,
		       काष्ठा page *page, पूर्णांक *size);
#पूर्ण_अगर
