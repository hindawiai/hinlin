<शैली गुरु>
/*
 * Copyright (c) 2017 Mellanox Technologies. All rights reserved.
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
 *
 */

#अगर_अघोषित __MLX5_FPGA_CONN_H__
#घोषणा __MLX5_FPGA_CONN_H__

#समावेश <linux/mlx5/cq.h>
#समावेश <linux/mlx5/qp.h>

#समावेश "fpga/core.h"
#समावेश "fpga/sdk.h"
#समावेश "wq.h"

काष्ठा mlx5_fpga_conn अणु
	काष्ठा mlx5_fpga_device *fdev;

	व्योम (*recv_cb)(व्योम *cb_arg, काष्ठा mlx5_fpga_dma_buf *buf);
	व्योम *cb_arg;

	/* FPGA QP */
	u32 fpga_qpc[MLX5_ST_SZ_DW(fpga_qpc)];
	u32 fpga_qpn;

	/* CQ */
	काष्ठा अणु
		काष्ठा mlx5_cqwq wq;
		काष्ठा mlx5_wq_ctrl wq_ctrl;
		काष्ठा mlx5_core_cq mcq;
		काष्ठा tasklet_काष्ठा tasklet;
	पूर्ण cq;

	/* QP */
	काष्ठा अणु
		bool active;
		पूर्णांक sgid_index;
		काष्ठा mlx5_wq_qp wq;
		काष्ठा mlx5_wq_ctrl wq_ctrl;
		u32 qpn;
		काष्ठा अणु
			spinlock_t lock; /* Protects all SQ state */
			अचिन्हित पूर्णांक pc;
			अचिन्हित पूर्णांक cc;
			अचिन्हित पूर्णांक size;
			काष्ठा mlx5_fpga_dma_buf **bufs;
			काष्ठा list_head backlog;
		पूर्ण sq;
		काष्ठा अणु
			अचिन्हित पूर्णांक pc;
			अचिन्हित पूर्णांक cc;
			अचिन्हित पूर्णांक size;
			काष्ठा mlx5_fpga_dma_buf **bufs;
		पूर्ण rq;
	पूर्ण qp;
पूर्ण;

पूर्णांक mlx5_fpga_conn_device_init(काष्ठा mlx5_fpga_device *fdev);
व्योम mlx5_fpga_conn_device_cleanup(काष्ठा mlx5_fpga_device *fdev);
काष्ठा mlx5_fpga_conn *
mlx5_fpga_conn_create(काष्ठा mlx5_fpga_device *fdev,
		      काष्ठा mlx5_fpga_conn_attr *attr,
		      क्रमागत mlx5_अगरc_fpga_qp_type qp_type);
व्योम mlx5_fpga_conn_destroy(काष्ठा mlx5_fpga_conn *conn);
पूर्णांक mlx5_fpga_conn_send(काष्ठा mlx5_fpga_conn *conn,
			काष्ठा mlx5_fpga_dma_buf *buf);

#पूर्ण_अगर /* __MLX5_FPGA_CONN_H__ */
