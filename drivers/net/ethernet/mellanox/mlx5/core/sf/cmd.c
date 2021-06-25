<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020 Mellanox Technologies Ltd */

#समावेश <linux/mlx5/driver.h>
#समावेश "priv.h"

पूर्णांक mlx5_cmd_alloc_sf(काष्ठा mlx5_core_dev *dev, u16 function_id)
अणु
	u32 out[MLX5_ST_SZ_DW(alloc_sf_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(alloc_sf_in)] = अणुपूर्ण;

	MLX5_SET(alloc_sf_in, in, opcode, MLX5_CMD_OP_ALLOC_SF);
	MLX5_SET(alloc_sf_in, in, function_id, function_id);

	वापस mlx5_cmd_exec(dev, in, माप(in), out, माप(out));
पूर्ण

पूर्णांक mlx5_cmd_dealloc_sf(काष्ठा mlx5_core_dev *dev, u16 function_id)
अणु
	u32 out[MLX5_ST_SZ_DW(dealloc_sf_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(dealloc_sf_in)] = अणुपूर्ण;

	MLX5_SET(dealloc_sf_in, in, opcode, MLX5_CMD_OP_DEALLOC_SF);
	MLX5_SET(dealloc_sf_in, in, function_id, function_id);

	वापस mlx5_cmd_exec(dev, in, माप(in), out, माप(out));
पूर्ण

पूर्णांक mlx5_cmd_sf_enable_hca(काष्ठा mlx5_core_dev *dev, u16 func_id)
अणु
	u32 out[MLX5_ST_SZ_DW(enable_hca_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(enable_hca_in)] = अणुपूर्ण;

	MLX5_SET(enable_hca_in, in, opcode, MLX5_CMD_OP_ENABLE_HCA);
	MLX5_SET(enable_hca_in, in, function_id, func_id);
	MLX5_SET(enable_hca_in, in, embedded_cpu_function, 0);
	वापस mlx5_cmd_exec(dev, &in, माप(in), &out, माप(out));
पूर्ण

पूर्णांक mlx5_cmd_sf_disable_hca(काष्ठा mlx5_core_dev *dev, u16 func_id)
अणु
	u32 out[MLX5_ST_SZ_DW(disable_hca_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(disable_hca_in)] = अणुपूर्ण;

	MLX5_SET(disable_hca_in, in, opcode, MLX5_CMD_OP_DISABLE_HCA);
	MLX5_SET(disable_hca_in, in, function_id, func_id);
	MLX5_SET(enable_hca_in, in, embedded_cpu_function, 0);
	वापस mlx5_cmd_exec(dev, in, माप(in), out, माप(out));
पूर्ण
