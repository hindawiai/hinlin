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

#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/eचयन.h>
#समावेश <linux/module.h>
#समावेश "mlx5_core.h"
#समावेश "../../mlxfw/mlxfw.h"
#समावेश "accel/tls.h"

क्रमागत अणु
	MCQS_IDENTIFIER_BOOT_IMG	= 0x1,
	MCQS_IDENTIFIER_OEM_NVCONFIG	= 0x4,
	MCQS_IDENTIFIER_MLNX_NVCONFIG	= 0x5,
	MCQS_IDENTIFIER_CS_TOKEN	= 0x6,
	MCQS_IDENTIFIER_DBG_TOKEN	= 0x7,
	MCQS_IDENTIFIER_GEARBOX		= 0xA,
पूर्ण;

क्रमागत अणु
	MCQS_UPDATE_STATE_IDLE,
	MCQS_UPDATE_STATE_IN_PROGRESS,
	MCQS_UPDATE_STATE_APPLIED,
	MCQS_UPDATE_STATE_ACTIVE,
	MCQS_UPDATE_STATE_ACTIVE_PENDING_RESET,
	MCQS_UPDATE_STATE_FAILED,
	MCQS_UPDATE_STATE_CANCELED,
	MCQS_UPDATE_STATE_BUSY,
पूर्ण;

क्रमागत अणु
	MCQI_INFO_TYPE_CAPABILITIES	  = 0x0,
	MCQI_INFO_TYPE_VERSION		  = 0x1,
	MCQI_INFO_TYPE_ACTIVATION_METHOD  = 0x5,
पूर्ण;

क्रमागत अणु
	MCQI_FW_RUNNING_VERSION = 0,
	MCQI_FW_STORED_VERSION  = 1,
पूर्ण;

पूर्णांक mlx5_query_board_id(काष्ठा mlx5_core_dev *dev)
अणु
	u32 *out;
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(query_adapter_out);
	u32 in[MLX5_ST_SZ_DW(query_adapter_in)] = अणुपूर्ण;
	पूर्णांक err;

	out = kzalloc(outlen, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	MLX5_SET(query_adapter_in, in, opcode, MLX5_CMD_OP_QUERY_ADAPTER);
	err = mlx5_cmd_exec_inout(dev, query_adapter, in, out);
	अगर (err)
		जाओ out;

	स_नकल(dev->board_id,
	       MLX5_ADDR_OF(query_adapter_out, out,
			    query_adapter_काष्ठा.vsd_contd_psid),
	       MLX5_FLD_SZ_BYTES(query_adapter_out,
				 query_adapter_काष्ठा.vsd_contd_psid));

out:
	kमुक्त(out);
	वापस err;
पूर्ण

पूर्णांक mlx5_core_query_venकरोr_id(काष्ठा mlx5_core_dev *mdev, u32 *venकरोr_id)
अणु
	u32 *out;
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(query_adapter_out);
	u32 in[MLX5_ST_SZ_DW(query_adapter_in)] = अणुपूर्ण;
	पूर्णांक err;

	out = kzalloc(outlen, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	MLX5_SET(query_adapter_in, in, opcode, MLX5_CMD_OP_QUERY_ADAPTER);
	err = mlx5_cmd_exec_inout(mdev, query_adapter, in, out);
	अगर (err)
		जाओ out;

	*venकरोr_id = MLX5_GET(query_adapter_out, out,
			      query_adapter_काष्ठा.ieee_venकरोr_id);
out:
	kमुक्त(out);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_core_query_venकरोr_id);

अटल पूर्णांक mlx5_get_pcam_reg(काष्ठा mlx5_core_dev *dev)
अणु
	वापस mlx5_query_pcam_reg(dev, dev->caps.pcam,
				   MLX5_PCAM_FEATURE_ENHANCED_FEATURES,
				   MLX5_PCAM_REGS_5000_TO_507F);
पूर्ण

अटल पूर्णांक mlx5_get_mcam_access_reg_group(काष्ठा mlx5_core_dev *dev,
					  क्रमागत mlx5_mcam_reg_groups group)
अणु
	वापस mlx5_query_mcam_reg(dev, dev->caps.mcam[group],
				   MLX5_MCAM_FEATURE_ENHANCED_FEATURES, group);
पूर्ण

अटल पूर्णांक mlx5_get_qcam_reg(काष्ठा mlx5_core_dev *dev)
अणु
	वापस mlx5_query_qcam_reg(dev, dev->caps.qcam,
				   MLX5_QCAM_FEATURE_ENHANCED_FEATURES,
				   MLX5_QCAM_REGS_FIRST_128);
पूर्ण

पूर्णांक mlx5_query_hca_caps(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक err;

	err = mlx5_core_get_caps(dev, MLX5_CAP_GENERAL);
	अगर (err)
		वापस err;

	अगर (MLX5_CAP_GEN(dev, eth_net_offloads)) अणु
		err = mlx5_core_get_caps(dev, MLX5_CAP_ETHERNET_OFFLOADS);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (MLX5_CAP_GEN(dev, ipoib_enhanced_offloads)) अणु
		err = mlx5_core_get_caps(dev, MLX5_CAP_IPOIB_ENHANCED_OFFLOADS);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (MLX5_CAP_GEN(dev, pg)) अणु
		err = mlx5_core_get_caps(dev, MLX5_CAP_ODP);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (MLX5_CAP_GEN(dev, atomic)) अणु
		err = mlx5_core_get_caps(dev, MLX5_CAP_ATOMIC);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (MLX5_CAP_GEN(dev, roce)) अणु
		err = mlx5_core_get_caps(dev, MLX5_CAP_ROCE);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (MLX5_CAP_GEN(dev, nic_flow_table) ||
	    MLX5_CAP_GEN(dev, ipoib_enhanced_offloads)) अणु
		err = mlx5_core_get_caps(dev, MLX5_CAP_FLOW_TABLE);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (MLX5_CAP_GEN(dev, vport_group_manager) &&
	    MLX5_ESWITCH_MANAGER(dev)) अणु
		err = mlx5_core_get_caps(dev, MLX5_CAP_ESWITCH_FLOW_TABLE);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (MLX5_ESWITCH_MANAGER(dev)) अणु
		err = mlx5_core_get_caps(dev, MLX5_CAP_ESWITCH);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (MLX5_CAP_GEN(dev, vector_calc)) अणु
		err = mlx5_core_get_caps(dev, MLX5_CAP_VECTOR_CALC);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (MLX5_CAP_GEN(dev, qos)) अणु
		err = mlx5_core_get_caps(dev, MLX5_CAP_QOS);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (MLX5_CAP_GEN(dev, debug))
		mlx5_core_get_caps(dev, MLX5_CAP_DEBUG);

	अगर (MLX5_CAP_GEN(dev, pcam_reg))
		mlx5_get_pcam_reg(dev);

	अगर (MLX5_CAP_GEN(dev, mcam_reg)) अणु
		mlx5_get_mcam_access_reg_group(dev, MLX5_MCAM_REGS_FIRST_128);
		mlx5_get_mcam_access_reg_group(dev, MLX5_MCAM_REGS_0x9080_0x90FF);
		mlx5_get_mcam_access_reg_group(dev, MLX5_MCAM_REGS_0x9100_0x917F);
	पूर्ण

	अगर (MLX5_CAP_GEN(dev, qcam_reg))
		mlx5_get_qcam_reg(dev);

	अगर (MLX5_CAP_GEN(dev, device_memory)) अणु
		err = mlx5_core_get_caps(dev, MLX5_CAP_DEV_MEM);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (MLX5_CAP_GEN(dev, event_cap)) अणु
		err = mlx5_core_get_caps(dev, MLX5_CAP_DEV_EVENT);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (mlx5_accel_is_ktls_tx(dev) || mlx5_accel_is_ktls_rx(dev)) अणु
		err = mlx5_core_get_caps(dev, MLX5_CAP_TLS);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (MLX5_CAP_GEN_64(dev, general_obj_types) &
		MLX5_GENERAL_OBJ_TYPES_CAP_VIRTIO_NET_Q) अणु
		err = mlx5_core_get_caps(dev, MLX5_CAP_VDPA_EMULATION);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (MLX5_CAP_GEN(dev, ipsec_offload)) अणु
		err = mlx5_core_get_caps(dev, MLX5_CAP_IPSEC);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mlx5_cmd_init_hca(काष्ठा mlx5_core_dev *dev, uपूर्णांक32_t *sw_owner_id)
अणु
	u32 in[MLX5_ST_SZ_DW(init_hca_in)] = अणुपूर्ण;
	पूर्णांक i;

	MLX5_SET(init_hca_in, in, opcode, MLX5_CMD_OP_INIT_HCA);

	अगर (MLX5_CAP_GEN(dev, sw_owner_id)) अणु
		क्रम (i = 0; i < 4; i++)
			MLX5_ARRAY_SET(init_hca_in, in, sw_owner_id, i,
				       sw_owner_id[i]);
	पूर्ण

	वापस mlx5_cmd_exec_in(dev, init_hca, in);
पूर्ण

पूर्णांक mlx5_cmd_tearकरोwn_hca(काष्ठा mlx5_core_dev *dev)
अणु
	u32 in[MLX5_ST_SZ_DW(tearकरोwn_hca_in)] = अणुपूर्ण;

	MLX5_SET(tearकरोwn_hca_in, in, opcode, MLX5_CMD_OP_TEARDOWN_HCA);
	वापस mlx5_cmd_exec_in(dev, tearकरोwn_hca, in);
पूर्ण

पूर्णांक mlx5_cmd_क्रमce_tearकरोwn_hca(काष्ठा mlx5_core_dev *dev)
अणु
	u32 out[MLX5_ST_SZ_DW(tearकरोwn_hca_out)] = अणु0पूर्ण;
	u32 in[MLX5_ST_SZ_DW(tearकरोwn_hca_in)] = अणु0पूर्ण;
	पूर्णांक क्रमce_state;
	पूर्णांक ret;

	अगर (!MLX5_CAP_GEN(dev, क्रमce_tearकरोwn)) अणु
		mlx5_core_dbg(dev, "force teardown is not supported in the firmware\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	MLX5_SET(tearकरोwn_hca_in, in, opcode, MLX5_CMD_OP_TEARDOWN_HCA);
	MLX5_SET(tearकरोwn_hca_in, in, profile, MLX5_TEARDOWN_HCA_IN_PROखाता_FORCE_CLOSE);

	ret = mlx5_cmd_exec_polling(dev, in, माप(in), out, माप(out));
	अगर (ret)
		वापस ret;

	क्रमce_state = MLX5_GET(tearकरोwn_hca_out, out, state);
	अगर (क्रमce_state == MLX5_TEARDOWN_HCA_OUT_FORCE_STATE_FAIL) अणु
		mlx5_core_warn(dev, "teardown with force mode failed, doing normal teardown\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा MLX5_FAST_TEARDOWN_WAIT_MS   3000
पूर्णांक mlx5_cmd_fast_tearकरोwn_hca(काष्ठा mlx5_core_dev *dev)
अणु
	अचिन्हित दीर्घ end, delay_ms = MLX5_FAST_TEARDOWN_WAIT_MS;
	u32 out[MLX5_ST_SZ_DW(tearकरोwn_hca_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(tearकरोwn_hca_in)] = अणुपूर्ण;
	पूर्णांक state;
	पूर्णांक ret;

	अगर (!MLX5_CAP_GEN(dev, fast_tearकरोwn)) अणु
		mlx5_core_dbg(dev, "fast teardown is not supported in the firmware\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	MLX5_SET(tearकरोwn_hca_in, in, opcode, MLX5_CMD_OP_TEARDOWN_HCA);
	MLX5_SET(tearकरोwn_hca_in, in, profile,
		 MLX5_TEARDOWN_HCA_IN_PROखाता_PREPARE_FAST_TEARDOWN);

	ret = mlx5_cmd_exec_inout(dev, tearकरोwn_hca, in, out);
	अगर (ret)
		वापस ret;

	state = MLX5_GET(tearकरोwn_hca_out, out, state);
	अगर (state == MLX5_TEARDOWN_HCA_OUT_FORCE_STATE_FAIL) अणु
		mlx5_core_warn(dev, "teardown with fast mode failed\n");
		वापस -EIO;
	पूर्ण

	mlx5_set_nic_state(dev, MLX5_NIC_IFC_DISABLED);

	/* Loop until device state turns to disable */
	end = jअगरfies + msecs_to_jअगरfies(delay_ms);
	करो अणु
		अगर (mlx5_get_nic_state(dev) == MLX5_NIC_IFC_DISABLED)
			अवरोध;

		cond_resched();
	पूर्ण जबतक (!समय_after(jअगरfies, end));

	अगर (mlx5_get_nic_state(dev) != MLX5_NIC_IFC_DISABLED) अणु
		dev_err(&dev->pdev->dev, "NIC IFC still %d after %lums.\n",
			mlx5_get_nic_state(dev), delay_ms);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

क्रमागत mlxsw_reg_mcc_inकाष्ठाion अणु
	MLX5_REG_MCC_INSTRUCTION_LOCK_UPDATE_HANDLE = 0x01,
	MLX5_REG_MCC_INSTRUCTION_RELEASE_UPDATE_HANDLE = 0x02,
	MLX5_REG_MCC_INSTRUCTION_UPDATE_COMPONENT = 0x03,
	MLX5_REG_MCC_INSTRUCTION_VERIFY_COMPONENT = 0x04,
	MLX5_REG_MCC_INSTRUCTION_ACTIVATE = 0x06,
	MLX5_REG_MCC_INSTRUCTION_CANCEL = 0x08,
पूर्ण;

अटल पूर्णांक mlx5_reg_mcc_set(काष्ठा mlx5_core_dev *dev,
			    क्रमागत mlxsw_reg_mcc_inकाष्ठाion instr,
			    u16 component_index, u32 update_handle,
			    u32 component_size)
अणु
	u32 out[MLX5_ST_SZ_DW(mcc_reg)];
	u32 in[MLX5_ST_SZ_DW(mcc_reg)];

	स_रखो(in, 0, माप(in));

	MLX5_SET(mcc_reg, in, inकाष्ठाion, instr);
	MLX5_SET(mcc_reg, in, component_index, component_index);
	MLX5_SET(mcc_reg, in, update_handle, update_handle);
	MLX5_SET(mcc_reg, in, component_size, component_size);

	वापस mlx5_core_access_reg(dev, in, माप(in), out,
				    माप(out), MLX5_REG_MCC, 0, 1);
पूर्ण

अटल पूर्णांक mlx5_reg_mcc_query(काष्ठा mlx5_core_dev *dev,
			      u32 *update_handle, u8 *error_code,
			      u8 *control_state)
अणु
	u32 out[MLX5_ST_SZ_DW(mcc_reg)];
	u32 in[MLX5_ST_SZ_DW(mcc_reg)];
	पूर्णांक err;

	स_रखो(in, 0, माप(in));
	स_रखो(out, 0, माप(out));
	MLX5_SET(mcc_reg, in, update_handle, *update_handle);

	err = mlx5_core_access_reg(dev, in, माप(in), out,
				   माप(out), MLX5_REG_MCC, 0, 0);
	अगर (err)
		जाओ out;

	*update_handle = MLX5_GET(mcc_reg, out, update_handle);
	*error_code = MLX5_GET(mcc_reg, out, error_code);
	*control_state = MLX5_GET(mcc_reg, out, control_state);

out:
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_reg_mcda_set(काष्ठा mlx5_core_dev *dev,
			     u32 update_handle,
			     u32 offset, u16 size,
			     u8 *data)
अणु
	पूर्णांक err, in_size = MLX5_ST_SZ_BYTES(mcda_reg) + size;
	u32 out[MLX5_ST_SZ_DW(mcda_reg)];
	पूर्णांक i, j, dw_size = size >> 2;
	__be32 data_element;
	u32 *in;

	in = kzalloc(in_size, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(mcda_reg, in, update_handle, update_handle);
	MLX5_SET(mcda_reg, in, offset, offset);
	MLX5_SET(mcda_reg, in, size, size);

	क्रम (i = 0; i < dw_size; i++) अणु
		j = i * 4;
		data_element = htonl(*(u32 *)&data[j]);
		स_नकल(MLX5_ADDR_OF(mcda_reg, in, data) + j, &data_element, 4);
	पूर्ण

	err = mlx5_core_access_reg(dev, in, in_size, out,
				   माप(out), MLX5_REG_MCDA, 0, 1);
	kमुक्त(in);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_reg_mcqi_query(काष्ठा mlx5_core_dev *dev,
			       u16 component_index, bool पढ़ो_pending,
			       u8 info_type, u16 data_size, व्योम *mcqi_data)
अणु
	u32 out[MLX5_ST_SZ_DW(mcqi_reg) + MLX5_UN_SZ_DW(mcqi_reg_data)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(mcqi_reg)] = अणुपूर्ण;
	व्योम *data;
	पूर्णांक err;

	MLX5_SET(mcqi_reg, in, component_index, component_index);
	MLX5_SET(mcqi_reg, in, पढ़ो_pending_component, पढ़ो_pending);
	MLX5_SET(mcqi_reg, in, info_type, info_type);
	MLX5_SET(mcqi_reg, in, data_size, data_size);

	err = mlx5_core_access_reg(dev, in, माप(in), out,
				   MLX5_ST_SZ_BYTES(mcqi_reg) + data_size,
				   MLX5_REG_MCQI, 0, 0);
	अगर (err)
		वापस err;

	data = MLX5_ADDR_OF(mcqi_reg, out, data);
	स_नकल(mcqi_data, data, data_size);

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_reg_mcqi_caps_query(काष्ठा mlx5_core_dev *dev, u16 component_index,
				    u32 *max_component_size, u8 *log_mcda_word_size,
				    u16 *mcda_max_ग_लिखो_size)
अणु
	u32 mcqi_reg[MLX5_ST_SZ_DW(mcqi_cap)] = अणुपूर्ण;
	पूर्णांक err;

	err = mlx5_reg_mcqi_query(dev, component_index, 0,
				  MCQI_INFO_TYPE_CAPABILITIES,
				  MLX5_ST_SZ_BYTES(mcqi_cap), mcqi_reg);
	अगर (err)
		वापस err;

	*max_component_size = MLX5_GET(mcqi_cap, mcqi_reg, max_component_size);
	*log_mcda_word_size = MLX5_GET(mcqi_cap, mcqi_reg, log_mcda_word_size);
	*mcda_max_ग_लिखो_size = MLX5_GET(mcqi_cap, mcqi_reg, mcda_max_ग_लिखो_size);

	वापस 0;
पूर्ण

काष्ठा mlx5_mlxfw_dev अणु
	काष्ठा mlxfw_dev mlxfw_dev;
	काष्ठा mlx5_core_dev *mlx5_core_dev;
पूर्ण;

अटल पूर्णांक mlx5_component_query(काष्ठा mlxfw_dev *mlxfw_dev,
				u16 component_index, u32 *p_max_size,
				u8 *p_align_bits, u16 *p_max_ग_लिखो_size)
अणु
	काष्ठा mlx5_mlxfw_dev *mlx5_mlxfw_dev =
		container_of(mlxfw_dev, काष्ठा mlx5_mlxfw_dev, mlxfw_dev);
	काष्ठा mlx5_core_dev *dev = mlx5_mlxfw_dev->mlx5_core_dev;

	अगर (!MLX5_CAP_GEN(dev, mcam_reg) || !MLX5_CAP_MCAM_REG(dev, mcqi)) अणु
		mlx5_core_warn(dev, "caps query isn't supported by running FW\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस mlx5_reg_mcqi_caps_query(dev, component_index, p_max_size,
					p_align_bits, p_max_ग_लिखो_size);
पूर्ण

अटल पूर्णांक mlx5_fsm_lock(काष्ठा mlxfw_dev *mlxfw_dev, u32 *fwhandle)
अणु
	काष्ठा mlx5_mlxfw_dev *mlx5_mlxfw_dev =
		container_of(mlxfw_dev, काष्ठा mlx5_mlxfw_dev, mlxfw_dev);
	काष्ठा mlx5_core_dev *dev = mlx5_mlxfw_dev->mlx5_core_dev;
	u8 control_state, error_code;
	पूर्णांक err;

	*fwhandle = 0;
	err = mlx5_reg_mcc_query(dev, fwhandle, &error_code, &control_state);
	अगर (err)
		वापस err;

	अगर (control_state != MLXFW_FSM_STATE_IDLE)
		वापस -EBUSY;

	वापस mlx5_reg_mcc_set(dev, MLX5_REG_MCC_INSTRUCTION_LOCK_UPDATE_HANDLE,
				0, *fwhandle, 0);
पूर्ण

अटल पूर्णांक mlx5_fsm_component_update(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle,
				     u16 component_index, u32 component_size)
अणु
	काष्ठा mlx5_mlxfw_dev *mlx5_mlxfw_dev =
		container_of(mlxfw_dev, काष्ठा mlx5_mlxfw_dev, mlxfw_dev);
	काष्ठा mlx5_core_dev *dev = mlx5_mlxfw_dev->mlx5_core_dev;

	वापस mlx5_reg_mcc_set(dev, MLX5_REG_MCC_INSTRUCTION_UPDATE_COMPONENT,
				component_index, fwhandle, component_size);
पूर्ण

अटल पूर्णांक mlx5_fsm_block_करोwnload(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle,
				   u8 *data, u16 size, u32 offset)
अणु
	काष्ठा mlx5_mlxfw_dev *mlx5_mlxfw_dev =
		container_of(mlxfw_dev, काष्ठा mlx5_mlxfw_dev, mlxfw_dev);
	काष्ठा mlx5_core_dev *dev = mlx5_mlxfw_dev->mlx5_core_dev;

	वापस mlx5_reg_mcda_set(dev, fwhandle, offset, size, data);
पूर्ण

अटल पूर्णांक mlx5_fsm_component_verअगरy(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle,
				     u16 component_index)
अणु
	काष्ठा mlx5_mlxfw_dev *mlx5_mlxfw_dev =
		container_of(mlxfw_dev, काष्ठा mlx5_mlxfw_dev, mlxfw_dev);
	काष्ठा mlx5_core_dev *dev = mlx5_mlxfw_dev->mlx5_core_dev;

	वापस mlx5_reg_mcc_set(dev, MLX5_REG_MCC_INSTRUCTION_VERIFY_COMPONENT,
				component_index, fwhandle, 0);
पूर्ण

अटल पूर्णांक mlx5_fsm_activate(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle)
अणु
	काष्ठा mlx5_mlxfw_dev *mlx5_mlxfw_dev =
		container_of(mlxfw_dev, काष्ठा mlx5_mlxfw_dev, mlxfw_dev);
	काष्ठा mlx5_core_dev *dev = mlx5_mlxfw_dev->mlx5_core_dev;

	वापस mlx5_reg_mcc_set(dev, MLX5_REG_MCC_INSTRUCTION_ACTIVATE,	0,
				fwhandle, 0);
पूर्ण

अटल पूर्णांक mlx5_fsm_query_state(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle,
				क्रमागत mlxfw_fsm_state *fsm_state,
				क्रमागत mlxfw_fsm_state_err *fsm_state_err)
अणु
	काष्ठा mlx5_mlxfw_dev *mlx5_mlxfw_dev =
		container_of(mlxfw_dev, काष्ठा mlx5_mlxfw_dev, mlxfw_dev);
	काष्ठा mlx5_core_dev *dev = mlx5_mlxfw_dev->mlx5_core_dev;
	u8 control_state, error_code;
	पूर्णांक err;

	err = mlx5_reg_mcc_query(dev, &fwhandle, &error_code, &control_state);
	अगर (err)
		वापस err;

	*fsm_state = control_state;
	*fsm_state_err = min_t(क्रमागत mlxfw_fsm_state_err, error_code,
			       MLXFW_FSM_STATE_ERR_MAX);
	वापस 0;
पूर्ण

अटल व्योम mlx5_fsm_cancel(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle)
अणु
	काष्ठा mlx5_mlxfw_dev *mlx5_mlxfw_dev =
		container_of(mlxfw_dev, काष्ठा mlx5_mlxfw_dev, mlxfw_dev);
	काष्ठा mlx5_core_dev *dev = mlx5_mlxfw_dev->mlx5_core_dev;

	mlx5_reg_mcc_set(dev, MLX5_REG_MCC_INSTRUCTION_CANCEL, 0, fwhandle, 0);
पूर्ण

अटल व्योम mlx5_fsm_release(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle)
अणु
	काष्ठा mlx5_mlxfw_dev *mlx5_mlxfw_dev =
		container_of(mlxfw_dev, काष्ठा mlx5_mlxfw_dev, mlxfw_dev);
	काष्ठा mlx5_core_dev *dev = mlx5_mlxfw_dev->mlx5_core_dev;

	mlx5_reg_mcc_set(dev, MLX5_REG_MCC_INSTRUCTION_RELEASE_UPDATE_HANDLE, 0,
			 fwhandle, 0);
पूर्ण

#घोषणा MLX5_FSM_REACTIVATE_TOUT 5000 /* msecs */
अटल पूर्णांक mlx5_fsm_reactivate(काष्ठा mlxfw_dev *mlxfw_dev, u8 *status)
अणु
	अचिन्हित दीर्घ exp_समय = jअगरfies + msecs_to_jअगरfies(MLX5_FSM_REACTIVATE_TOUT);
	काष्ठा mlx5_mlxfw_dev *mlx5_mlxfw_dev =
		container_of(mlxfw_dev, काष्ठा mlx5_mlxfw_dev, mlxfw_dev);
	काष्ठा mlx5_core_dev *dev = mlx5_mlxfw_dev->mlx5_core_dev;
	u32 out[MLX5_ST_SZ_DW(mirc_reg)];
	u32 in[MLX5_ST_SZ_DW(mirc_reg)];
	पूर्णांक err;

	अगर (!MLX5_CAP_MCAM_REG2(dev, mirc))
		वापस -EOPNOTSUPP;

	स_रखो(in, 0, माप(in));

	err = mlx5_core_access_reg(dev, in, माप(in), out,
				   माप(out), MLX5_REG_MIRC, 0, 1);
	अगर (err)
		वापस err;

	करो अणु
		स_रखो(out, 0, माप(out));
		err = mlx5_core_access_reg(dev, in, माप(in), out,
					   माप(out), MLX5_REG_MIRC, 0, 0);
		अगर (err)
			वापस err;

		*status = MLX5_GET(mirc_reg, out, status_code);
		अगर (*status != MLXFW_FSM_REACTIVATE_STATUS_BUSY)
			वापस 0;

		msleep(20);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, exp_समय));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mlxfw_dev_ops mlx5_mlxfw_dev_ops = अणु
	.component_query	= mlx5_component_query,
	.fsm_lock		= mlx5_fsm_lock,
	.fsm_component_update	= mlx5_fsm_component_update,
	.fsm_block_करोwnload	= mlx5_fsm_block_करोwnload,
	.fsm_component_verअगरy	= mlx5_fsm_component_verअगरy,
	.fsm_activate		= mlx5_fsm_activate,
	.fsm_reactivate		= mlx5_fsm_reactivate,
	.fsm_query_state	= mlx5_fsm_query_state,
	.fsm_cancel		= mlx5_fsm_cancel,
	.fsm_release		= mlx5_fsm_release
पूर्ण;

पूर्णांक mlx5_firmware_flash(काष्ठा mlx5_core_dev *dev,
			स्थिर काष्ठा firmware *firmware,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_mlxfw_dev mlx5_mlxfw_dev = अणु
		.mlxfw_dev = अणु
			.ops = &mlx5_mlxfw_dev_ops,
			.psid = dev->board_id,
			.psid_size = म_माप(dev->board_id),
			.devlink = priv_to_devlink(dev),
		पूर्ण,
		.mlx5_core_dev = dev
	पूर्ण;

	अगर (!MLX5_CAP_GEN(dev, mcam_reg)  ||
	    !MLX5_CAP_MCAM_REG(dev, mcqi) ||
	    !MLX5_CAP_MCAM_REG(dev, mcc)  ||
	    !MLX5_CAP_MCAM_REG(dev, mcda)) अणु
		pr_info("%s flashing isn't supported by the running FW\n", __func__);
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस mlxfw_firmware_flash(&mlx5_mlxfw_dev.mlxfw_dev,
				    firmware, extack);
पूर्ण

अटल पूर्णांक mlx5_reg_mcqi_version_query(काष्ठा mlx5_core_dev *dev,
				       u16 component_index, bool पढ़ो_pending,
				       u32 *mcqi_version_out)
अणु
	वापस mlx5_reg_mcqi_query(dev, component_index, पढ़ो_pending,
				   MCQI_INFO_TYPE_VERSION,
				   MLX5_ST_SZ_BYTES(mcqi_version),
				   mcqi_version_out);
पूर्ण

अटल पूर्णांक mlx5_reg_mcqs_query(काष्ठा mlx5_core_dev *dev, u32 *out,
			       u16 component_index)
अणु
	u8 out_sz = MLX5_ST_SZ_BYTES(mcqs_reg);
	u32 in[MLX5_ST_SZ_DW(mcqs_reg)] = अणुपूर्ण;
	पूर्णांक err;

	स_रखो(out, 0, out_sz);

	MLX5_SET(mcqs_reg, in, component_index, component_index);

	err = mlx5_core_access_reg(dev, in, माप(in), out,
				   out_sz, MLX5_REG_MCQS, 0, 0);
	वापस err;
पूर्ण

/* scans component index sequentially, to find the boot img index */
अटल पूर्णांक mlx5_get_boot_img_component_index(काष्ठा mlx5_core_dev *dev)
अणु
	u32 out[MLX5_ST_SZ_DW(mcqs_reg)] = अणुपूर्ण;
	u16 identअगरier, component_idx = 0;
	bool quit;
	पूर्णांक err;

	करो अणु
		err = mlx5_reg_mcqs_query(dev, out, component_idx);
		अगर (err)
			वापस err;

		identअगरier = MLX5_GET(mcqs_reg, out, identअगरier);
		quit = !!MLX5_GET(mcqs_reg, out, last_index_flag);
		quit |= identअगरier == MCQS_IDENTIFIER_BOOT_IMG;
	पूर्ण जबतक (!quit && ++component_idx);

	अगर (identअगरier != MCQS_IDENTIFIER_BOOT_IMG) अणु
		mlx5_core_warn(dev, "mcqs: can't find boot_img component ix, last scanned idx %d\n",
			       component_idx);
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस component_idx;
पूर्ण

अटल पूर्णांक
mlx5_fw_image_pending(काष्ठा mlx5_core_dev *dev,
		      पूर्णांक component_index,
		      bool *pending_version_exists)
अणु
	u32 out[MLX5_ST_SZ_DW(mcqs_reg)];
	u8 component_update_state;
	पूर्णांक err;

	err = mlx5_reg_mcqs_query(dev, out, component_index);
	अगर (err)
		वापस err;

	component_update_state = MLX5_GET(mcqs_reg, out, component_update_state);

	अगर (component_update_state == MCQS_UPDATE_STATE_IDLE) अणु
		*pending_version_exists = false;
	पूर्ण अन्यथा अगर (component_update_state == MCQS_UPDATE_STATE_ACTIVE_PENDING_RESET) अणु
		*pending_version_exists = true;
	पूर्ण अन्यथा अणु
		mlx5_core_warn(dev,
			       "mcqs: can't read pending fw version while fw state is %d\n",
			       component_update_state);
		वापस -ENODATA;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक mlx5_fw_version_query(काष्ठा mlx5_core_dev *dev,
			  u32 *running_ver, u32 *pending_ver)
अणु
	u32 reg_mcqi_version[MLX5_ST_SZ_DW(mcqi_version)] = अणुपूर्ण;
	bool pending_version_exists;
	पूर्णांक component_index;
	पूर्णांक err;

	अगर (!MLX5_CAP_GEN(dev, mcam_reg) || !MLX5_CAP_MCAM_REG(dev, mcqi) ||
	    !MLX5_CAP_MCAM_REG(dev, mcqs)) अणु
		mlx5_core_warn(dev, "fw query isn't supported by the FW\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	component_index = mlx5_get_boot_img_component_index(dev);
	अगर (component_index < 0)
		वापस component_index;

	err = mlx5_reg_mcqi_version_query(dev, component_index,
					  MCQI_FW_RUNNING_VERSION,
					  reg_mcqi_version);
	अगर (err)
		वापस err;

	*running_ver = MLX5_GET(mcqi_version, reg_mcqi_version, version);

	err = mlx5_fw_image_pending(dev, component_index, &pending_version_exists);
	अगर (err)
		वापस err;

	अगर (!pending_version_exists) अणु
		*pending_ver = 0;
		वापस 0;
	पूर्ण

	err = mlx5_reg_mcqi_version_query(dev, component_index,
					  MCQI_FW_STORED_VERSION,
					  reg_mcqi_version);
	अगर (err)
		वापस err;

	*pending_ver = MLX5_GET(mcqi_version, reg_mcqi_version, version);

	वापस 0;
पूर्ण
