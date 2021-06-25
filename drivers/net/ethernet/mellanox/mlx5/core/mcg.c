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
#समावेश <rdma/ib_verbs.h>
#समावेश "mlx5_core.h"

पूर्णांक mlx5_core_attach_mcg(काष्ठा mlx5_core_dev *dev, जोड़ ib_gid *mgid, u32 qpn)
अणु
	u32 in[MLX5_ST_SZ_DW(attach_to_mcg_in)] = अणुपूर्ण;
	व्योम *gid;

	MLX5_SET(attach_to_mcg_in, in, opcode, MLX5_CMD_OP_ATTACH_TO_MCG);
	MLX5_SET(attach_to_mcg_in, in, qpn, qpn);
	gid = MLX5_ADDR_OF(attach_to_mcg_in, in, multicast_gid);
	स_नकल(gid, mgid, माप(*mgid));
	वापस mlx5_cmd_exec_in(dev, attach_to_mcg, in);
पूर्ण
EXPORT_SYMBOL(mlx5_core_attach_mcg);

पूर्णांक mlx5_core_detach_mcg(काष्ठा mlx5_core_dev *dev, जोड़ ib_gid *mgid, u32 qpn)
अणु
	u32 in[MLX5_ST_SZ_DW(detach_from_mcg_in)] = अणुपूर्ण;
	व्योम *gid;

	MLX5_SET(detach_from_mcg_in, in, opcode, MLX5_CMD_OP_DETACH_FROM_MCG);
	MLX5_SET(detach_from_mcg_in, in, qpn, qpn);
	gid = MLX5_ADDR_OF(detach_from_mcg_in, in, multicast_gid);
	स_नकल(gid, mgid, माप(*mgid));
	वापस mlx5_cmd_exec_in(dev, detach_from_mcg, in);
पूर्ण
EXPORT_SYMBOL(mlx5_core_detach_mcg);
