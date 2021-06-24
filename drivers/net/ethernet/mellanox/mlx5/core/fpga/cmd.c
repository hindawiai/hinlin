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

#समावेश <linux/etherdevice.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/device.h>

#समावेश "mlx5_core.h"
#समावेश "fpga/cmd.h"

#घोषणा MLX5_FPGA_ACCESS_REG_SZ (MLX5_ST_SZ_DW(fpga_access_reg) + \
				 MLX5_FPGA_ACCESS_REG_SIZE_MAX)

पूर्णांक mlx5_fpga_access_reg(काष्ठा mlx5_core_dev *dev, u8 size, u64 addr,
			 व्योम *buf, bool ग_लिखो)
अणु
	u32 in[MLX5_FPGA_ACCESS_REG_SZ] = अणु0पूर्ण;
	u32 out[MLX5_FPGA_ACCESS_REG_SZ];
	पूर्णांक err;

	अगर (size & 3)
		वापस -EINVAL;
	अगर (addr & 3)
		वापस -EINVAL;
	अगर (size > MLX5_FPGA_ACCESS_REG_SIZE_MAX)
		वापस -EINVAL;

	MLX5_SET(fpga_access_reg, in, size, size);
	MLX5_SET64(fpga_access_reg, in, address, addr);
	अगर (ग_लिखो)
		स_नकल(MLX5_ADDR_OF(fpga_access_reg, in, data), buf, size);

	err = mlx5_core_access_reg(dev, in, माप(in), out, माप(out),
				   MLX5_REG_FPGA_ACCESS_REG, 0, ग_लिखो);
	अगर (err)
		वापस err;

	अगर (!ग_लिखो)
		स_नकल(buf, MLX5_ADDR_OF(fpga_access_reg, out, data), size);

	वापस 0;
पूर्ण

पूर्णांक mlx5_fpga_caps(काष्ठा mlx5_core_dev *dev)
अणु
	u32 in[MLX5_ST_SZ_DW(fpga_cap)] = अणु0पूर्ण;

	वापस mlx5_core_access_reg(dev, in, माप(in), dev->caps.fpga,
				    MLX5_ST_SZ_BYTES(fpga_cap),
				    MLX5_REG_FPGA_CAP, 0, 0);
पूर्ण

पूर्णांक mlx5_fpga_ctrl_op(काष्ठा mlx5_core_dev *dev, u8 op)
अणु
	u32 in[MLX5_ST_SZ_DW(fpga_ctrl)] = अणु0पूर्ण;
	u32 out[MLX5_ST_SZ_DW(fpga_ctrl)];

	MLX5_SET(fpga_ctrl, in, operation, op);

	वापस mlx5_core_access_reg(dev, in, माप(in), out, माप(out),
				    MLX5_REG_FPGA_CTRL, 0, true);
पूर्ण

पूर्णांक mlx5_fpga_sbu_caps(काष्ठा mlx5_core_dev *dev, व्योम *caps, पूर्णांक size)
अणु
	अचिन्हित पूर्णांक cap_size = MLX5_CAP_FPGA(dev, sandbox_extended_caps_len);
	u64 addr = MLX5_CAP64_FPGA(dev, sandbox_extended_caps_addr);
	अचिन्हित पूर्णांक पढ़ो;
	पूर्णांक ret = 0;

	अगर (cap_size > size) अणु
		mlx5_core_warn(dev, "Not enough buffer %u for FPGA SBU caps %u",
			       size, cap_size);
		वापस -EINVAL;
	पूर्ण

	जबतक (cap_size > 0) अणु
		पढ़ो = min_t(अचिन्हित पूर्णांक, cap_size,
			     MLX5_FPGA_ACCESS_REG_SIZE_MAX);

		ret = mlx5_fpga_access_reg(dev, पढ़ो, addr, caps, false);
		अगर (ret) अणु
			mlx5_core_warn(dev, "Error reading FPGA SBU caps %u bytes at address 0x%llx: %d",
				       पढ़ो, addr, ret);
			वापस ret;
		पूर्ण

		cap_size -= पढ़ो;
		addr += पढ़ो;
		caps += पढ़ो;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक mlx5_fpga_query(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_fpga_query *query)
अणु
	u32 in[MLX5_ST_SZ_DW(fpga_ctrl)] = अणु0पूर्ण;
	u32 out[MLX5_ST_SZ_DW(fpga_ctrl)];
	पूर्णांक err;

	err = mlx5_core_access_reg(dev, in, माप(in), out, माप(out),
				   MLX5_REG_FPGA_CTRL, 0, false);
	अगर (err)
		वापस err;

	query->status = MLX5_GET(fpga_ctrl, out, status);
	query->admin_image = MLX5_GET(fpga_ctrl, out, flash_select_admin);
	query->oper_image = MLX5_GET(fpga_ctrl, out, flash_select_oper);
	वापस 0;
पूर्ण

पूर्णांक mlx5_fpga_create_qp(काष्ठा mlx5_core_dev *dev, व्योम *fpga_qpc,
			u32 *fpga_qpn)
अणु
	u32 out[MLX5_ST_SZ_DW(fpga_create_qp_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(fpga_create_qp_in)] = अणुपूर्ण;
	पूर्णांक ret;

	MLX5_SET(fpga_create_qp_in, in, opcode, MLX5_CMD_OP_FPGA_CREATE_QP);
	स_नकल(MLX5_ADDR_OF(fpga_create_qp_in, in, fpga_qpc), fpga_qpc,
	       MLX5_FLD_SZ_BYTES(fpga_create_qp_in, fpga_qpc));

	ret = mlx5_cmd_exec_inout(dev, fpga_create_qp, in, out);
	अगर (ret)
		वापस ret;

	स_नकल(fpga_qpc, MLX5_ADDR_OF(fpga_create_qp_out, out, fpga_qpc),
	       MLX5_FLD_SZ_BYTES(fpga_create_qp_out, fpga_qpc));
	*fpga_qpn = MLX5_GET(fpga_create_qp_out, out, fpga_qpn);
	वापस ret;
पूर्ण

पूर्णांक mlx5_fpga_modअगरy_qp(काष्ठा mlx5_core_dev *dev, u32 fpga_qpn,
			क्रमागत mlx5_fpga_qpc_field_select fields,
			व्योम *fpga_qpc)
अणु
	u32 in[MLX5_ST_SZ_DW(fpga_modअगरy_qp_in)] = अणुपूर्ण;

	MLX5_SET(fpga_modअगरy_qp_in, in, opcode, MLX5_CMD_OP_FPGA_MODIFY_QP);
	MLX5_SET(fpga_modअगरy_qp_in, in, field_select, fields);
	MLX5_SET(fpga_modअगरy_qp_in, in, fpga_qpn, fpga_qpn);
	स_नकल(MLX5_ADDR_OF(fpga_modअगरy_qp_in, in, fpga_qpc), fpga_qpc,
	       MLX5_FLD_SZ_BYTES(fpga_modअगरy_qp_in, fpga_qpc));

	वापस mlx5_cmd_exec_in(dev, fpga_modअगरy_qp, in);
पूर्ण

पूर्णांक mlx5_fpga_query_qp(काष्ठा mlx5_core_dev *dev,
		       u32 fpga_qpn, व्योम *fpga_qpc)
अणु
	u32 out[MLX5_ST_SZ_DW(fpga_query_qp_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(fpga_query_qp_in)] = अणुपूर्ण;
	पूर्णांक ret;

	MLX5_SET(fpga_query_qp_in, in, opcode, MLX5_CMD_OP_FPGA_QUERY_QP);
	MLX5_SET(fpga_query_qp_in, in, fpga_qpn, fpga_qpn);

	ret = mlx5_cmd_exec_inout(dev, fpga_query_qp, in, out);
	अगर (ret)
		वापस ret;

	स_नकल(fpga_qpc, MLX5_ADDR_OF(fpga_query_qp_out, out, fpga_qpc),
	       MLX5_FLD_SZ_BYTES(fpga_query_qp_out, fpga_qpc));
	वापस ret;
पूर्ण

पूर्णांक mlx5_fpga_destroy_qp(काष्ठा mlx5_core_dev *dev, u32 fpga_qpn)
अणु
	u32 in[MLX5_ST_SZ_DW(fpga_destroy_qp_in)] = अणुपूर्ण;

	MLX5_SET(fpga_destroy_qp_in, in, opcode, MLX5_CMD_OP_FPGA_DESTROY_QP);
	MLX5_SET(fpga_destroy_qp_in, in, fpga_qpn, fpga_qpn);

	वापस mlx5_cmd_exec_in(dev, fpga_destroy_qp, in);
पूर्ण

पूर्णांक mlx5_fpga_query_qp_counters(काष्ठा mlx5_core_dev *dev, u32 fpga_qpn,
				bool clear, काष्ठा mlx5_fpga_qp_counters *data)
अणु
	u32 out[MLX5_ST_SZ_DW(fpga_query_qp_counters_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(fpga_query_qp_counters_in)] = अणुपूर्ण;
	पूर्णांक ret;

	MLX5_SET(fpga_query_qp_counters_in, in, opcode,
		 MLX5_CMD_OP_FPGA_QUERY_QP_COUNTERS);
	MLX5_SET(fpga_query_qp_counters_in, in, clear, clear);
	MLX5_SET(fpga_query_qp_counters_in, in, fpga_qpn, fpga_qpn);

	ret = mlx5_cmd_exec_inout(dev, fpga_query_qp_counters, in, out);
	अगर (ret)
		वापस ret;

	data->rx_ack_packets = MLX5_GET64(fpga_query_qp_counters_out, out,
					  rx_ack_packets);
	data->rx_send_packets = MLX5_GET64(fpga_query_qp_counters_out, out,
					   rx_send_packets);
	data->tx_ack_packets = MLX5_GET64(fpga_query_qp_counters_out, out,
					  tx_ack_packets);
	data->tx_send_packets = MLX5_GET64(fpga_query_qp_counters_out, out,
					   tx_send_packets);
	data->rx_total_drop = MLX5_GET64(fpga_query_qp_counters_out, out,
					 rx_total_drop);

	वापस ret;
पूर्ण
