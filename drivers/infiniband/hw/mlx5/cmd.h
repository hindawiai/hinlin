<शैली गुरु>
/*
 * Copyright (c) 2017, Mellanox Technologies. All rights reserved.
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

#अगर_अघोषित MLX5_IB_CMD_H
#घोषणा MLX5_IB_CMD_H

#समावेश "mlx5_ib.h"
#समावेश <linux/kernel.h>
#समावेश <linux/mlx5/driver.h>

पूर्णांक mlx5_cmd_dump_fill_mkey(काष्ठा mlx5_core_dev *dev, u32 *mkey);
पूर्णांक mlx5_cmd_null_mkey(काष्ठा mlx5_core_dev *dev, u32 *null_mkey);
पूर्णांक mlx5_cmd_query_cong_params(काष्ठा mlx5_core_dev *dev, पूर्णांक cong_poपूर्णांक,
			       व्योम *out);
पूर्णांक mlx5_cmd_dealloc_pd(काष्ठा mlx5_core_dev *dev, u32 pdn, u16 uid);
व्योम mlx5_cmd_destroy_tir(काष्ठा mlx5_core_dev *dev, u32 tirn, u16 uid);
व्योम mlx5_cmd_destroy_tis(काष्ठा mlx5_core_dev *dev, u32 tisn, u16 uid);
पूर्णांक mlx5_cmd_destroy_rqt(काष्ठा mlx5_core_dev *dev, u32 rqtn, u16 uid);
पूर्णांक mlx5_cmd_alloc_transport_करोमुख्य(काष्ठा mlx5_core_dev *dev, u32 *tdn,
				    u16 uid);
व्योम mlx5_cmd_dealloc_transport_करोमुख्य(काष्ठा mlx5_core_dev *dev, u32 tdn,
				       u16 uid);
पूर्णांक mlx5_cmd_attach_mcg(काष्ठा mlx5_core_dev *dev, जोड़ ib_gid *mgid,
			u32 qpn, u16 uid);
पूर्णांक mlx5_cmd_detach_mcg(काष्ठा mlx5_core_dev *dev, जोड़ ib_gid *mgid,
			u32 qpn, u16 uid);
पूर्णांक mlx5_cmd_xrcd_alloc(काष्ठा mlx5_core_dev *dev, u32 *xrcdn, u16 uid);
पूर्णांक mlx5_cmd_xrcd_dealloc(काष्ठा mlx5_core_dev *dev, u32 xrcdn, u16 uid);
पूर्णांक mlx5_cmd_mad_अगरc(काष्ठा mlx5_core_dev *dev, स्थिर व्योम *inb, व्योम *outb,
		     u16 opmod, u8 port);
#पूर्ण_अगर /* MLX5_IB_CMD_H */
