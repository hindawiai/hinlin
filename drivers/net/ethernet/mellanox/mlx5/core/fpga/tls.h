<शैली गुरु>
/*
 * Copyright (c) 2018 Mellanox Technologies. All rights reserved.
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

#अगर_अघोषित __MLX5_FPGA_TLS_H__
#घोषणा __MLX5_FPGA_TLS_H__

#समावेश <linux/mlx5/driver.h>

#समावेश <net/tls.h>
#समावेश "fpga/core.h"

काष्ठा mlx5_fpga_tls अणु
	काष्ठा list_head pending_cmds;
	spinlock_t pending_cmds_lock; /* Protects pending_cmds */
	u32 caps;
	काष्ठा mlx5_fpga_conn *conn;

	काष्ठा idr tx_idr;
	काष्ठा idr rx_idr;
	spinlock_t tx_idr_spinlock; /* protects the IDR */
	spinlock_t rx_idr_spinlock; /* protects the IDR */
पूर्ण;

पूर्णांक mlx5_fpga_tls_add_flow(काष्ठा mlx5_core_dev *mdev, व्योम *flow,
			   काष्ठा tls_crypto_info *crypto_info,
			   u32 start_offload_tcp_sn, u32 *p_swid,
			   bool direction_sx);

व्योम mlx5_fpga_tls_del_flow(काष्ठा mlx5_core_dev *mdev, u32 swid,
			    gfp_t flags, bool direction_sx);

bool mlx5_fpga_is_tls_device(काष्ठा mlx5_core_dev *mdev);
पूर्णांक mlx5_fpga_tls_init(काष्ठा mlx5_core_dev *mdev);
व्योम mlx5_fpga_tls_cleanup(काष्ठा mlx5_core_dev *mdev);

अटल अंतरभूत u32 mlx5_fpga_tls_device_caps(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस mdev->fpga->tls->caps;
पूर्ण

पूर्णांक mlx5_fpga_tls_resync_rx(काष्ठा mlx5_core_dev *mdev, __be32 handle,
			    u32 seq, __be64 rcd_sn);

#पूर्ण_अगर /* __MLX5_FPGA_TLS_H__ */
