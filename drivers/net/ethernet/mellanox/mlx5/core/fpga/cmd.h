<शैली गुरु>
/*
 * Copyright (c) 2017, Mellanox Technologies, Ltd.  All rights reserved.
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

#अगर_अघोषित __MLX5_FPGA_H__
#घोषणा __MLX5_FPGA_H__

#समावेश <linux/mlx5/driver.h>

क्रमागत mlx5_fpga_id अणु
	MLX5_FPGA_NEWTON = 0,
	MLX5_FPGA_EDISON = 1,
	MLX5_FPGA_MORSE = 2,
	MLX5_FPGA_MORSEQ = 3,
पूर्ण;

क्रमागत mlx5_fpga_image अणु
	MLX5_FPGA_IMAGE_USER = 0,
	MLX5_FPGA_IMAGE_FACTORY,
पूर्ण;

क्रमागत mlx5_fpga_status अणु
	MLX5_FPGA_STATUS_SUCCESS = 0,
	MLX5_FPGA_STATUS_FAILURE = 1,
	MLX5_FPGA_STATUS_IN_PROGRESS = 2,
	MLX5_FPGA_STATUS_NONE = 0xFFFF,
पूर्ण;

काष्ठा mlx5_fpga_query अणु
	क्रमागत mlx5_fpga_image admin_image;
	क्रमागत mlx5_fpga_image oper_image;
	क्रमागत mlx5_fpga_status status;
पूर्ण;

क्रमागत mlx5_fpga_qpc_field_select अणु
	MLX5_FPGA_QPC_STATE = BIT(0),
पूर्ण;

काष्ठा mlx5_fpga_qp_counters अणु
	u64 rx_ack_packets;
	u64 rx_send_packets;
	u64 tx_ack_packets;
	u64 tx_send_packets;
	u64 rx_total_drop;
पूर्ण;

पूर्णांक mlx5_fpga_caps(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_fpga_query(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_fpga_query *query);
पूर्णांक mlx5_fpga_ctrl_op(काष्ठा mlx5_core_dev *dev, u8 op);
पूर्णांक mlx5_fpga_access_reg(काष्ठा mlx5_core_dev *dev, u8 size, u64 addr,
			 व्योम *buf, bool ग_लिखो);
पूर्णांक mlx5_fpga_sbu_caps(काष्ठा mlx5_core_dev *dev, व्योम *caps, पूर्णांक size);

पूर्णांक mlx5_fpga_create_qp(काष्ठा mlx5_core_dev *dev, व्योम *fpga_qpc,
			u32 *fpga_qpn);
पूर्णांक mlx5_fpga_modअगरy_qp(काष्ठा mlx5_core_dev *dev, u32 fpga_qpn,
			क्रमागत mlx5_fpga_qpc_field_select fields, व्योम *fpga_qpc);
पूर्णांक mlx5_fpga_query_qp(काष्ठा mlx5_core_dev *dev, u32 fpga_qpn, व्योम *fpga_qpc);
पूर्णांक mlx5_fpga_query_qp_counters(काष्ठा mlx5_core_dev *dev, u32 fpga_qpn,
				bool clear, काष्ठा mlx5_fpga_qp_counters *data);
पूर्णांक mlx5_fpga_destroy_qp(काष्ठा mlx5_core_dev *dev, u32 fpga_qpn);

#पूर्ण_अगर /* __MLX5_FPGA_H__ */
