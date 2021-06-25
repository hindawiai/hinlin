<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mlx5/driver.h>
#समावेश "mlx5_core.h"

पूर्णांक mlx5_core_alloc_pd(काष्ठा mlx5_core_dev *dev, u32 *pdn)
अणु
	u32 out[MLX5_ST_SZ_DW(alloc_pd_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(alloc_pd_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(alloc_pd_in, in, opcode, MLX5_CMD_OP_ALLOC_PD);
	err = mlx5_cmd_exec_inout(dev, alloc_pd, in, out);
	अगर (!err)
		*pdn = MLX5_GET(alloc_pd_out, out, pd);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_core_alloc_pd);

पूर्णांक mlx5_core_dealloc_pd(काष्ठा mlx5_core_dev *dev, u32 pdn)
अणु
	u32 in[MLX5_ST_SZ_DW(dealloc_pd_in)] = अणुपूर्ण;

	MLX5_SET(dealloc_pd_in, in, opcode, MLX5_CMD_OP_DEALLOC_PD);
	MLX5_SET(dealloc_pd_in, in, pd, pdn);
	वापस mlx5_cmd_exec_in(dev, dealloc_pd, in);
पूर्ण
EXPORT_SYMBOL(mlx5_core_dealloc_pd);
