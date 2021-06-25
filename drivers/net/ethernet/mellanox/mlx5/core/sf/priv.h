<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020 Mellanox Technologies Ltd */

#अगर_अघोषित __MLX5_SF_PRIV_H__
#घोषणा __MLX5_SF_PRIV_H__

#समावेश <linux/mlx5/driver.h>

पूर्णांक mlx5_cmd_alloc_sf(काष्ठा mlx5_core_dev *dev, u16 function_id);
पूर्णांक mlx5_cmd_dealloc_sf(काष्ठा mlx5_core_dev *dev, u16 function_id);

पूर्णांक mlx5_cmd_sf_enable_hca(काष्ठा mlx5_core_dev *dev, u16 func_id);
पूर्णांक mlx5_cmd_sf_disable_hca(काष्ठा mlx5_core_dev *dev, u16 func_id);

u16 mlx5_sf_sw_to_hw_id(काष्ठा mlx5_core_dev *dev, u32 controller, u16 sw_id);

पूर्णांक mlx5_sf_hw_table_sf_alloc(काष्ठा mlx5_core_dev *dev, u32 controller, u32 usr_sfnum);
व्योम mlx5_sf_hw_table_sf_मुक्त(काष्ठा mlx5_core_dev *dev, u32 controller, u16 id);
व्योम mlx5_sf_hw_table_sf_deferred_मुक्त(काष्ठा mlx5_core_dev *dev, u32 controller, u16 id);
bool mlx5_sf_hw_table_supported(स्थिर काष्ठा mlx5_core_dev *dev);

#पूर्ण_अगर
