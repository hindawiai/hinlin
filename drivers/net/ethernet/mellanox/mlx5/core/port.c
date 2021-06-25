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

#समावेश <linux/mlx5/port.h>
#समावेश "mlx5_core.h"

पूर्णांक mlx5_core_access_reg(काष्ठा mlx5_core_dev *dev, व्योम *data_in,
			 पूर्णांक size_in, व्योम *data_out, पूर्णांक size_out,
			 u16 reg_id, पूर्णांक arg, पूर्णांक ग_लिखो)
अणु
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(access_रेजिस्टर_out) + size_out;
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(access_रेजिस्टर_in) + size_in;
	पूर्णांक err = -ENOMEM;
	u32 *out = शून्य;
	u32 *in = शून्य;
	व्योम *data;

	in = kvzalloc(inlen, GFP_KERNEL);
	out = kvzalloc(outlen, GFP_KERNEL);
	अगर (!in || !out)
		जाओ out;

	data = MLX5_ADDR_OF(access_रेजिस्टर_in, in, रेजिस्टर_data);
	स_नकल(data, data_in, size_in);

	MLX5_SET(access_रेजिस्टर_in, in, opcode, MLX5_CMD_OP_ACCESS_REG);
	MLX5_SET(access_रेजिस्टर_in, in, op_mod, !ग_लिखो);
	MLX5_SET(access_रेजिस्टर_in, in, argument, arg);
	MLX5_SET(access_रेजिस्टर_in, in, रेजिस्टर_id, reg_id);

	err = mlx5_cmd_exec(dev, in, inlen, out, outlen);
	अगर (err)
		जाओ out;

	data = MLX5_ADDR_OF(access_रेजिस्टर_out, out, रेजिस्टर_data);
	स_नकल(data_out, data, size_out);

out:
	kvमुक्त(out);
	kvमुक्त(in);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_core_access_reg);

पूर्णांक mlx5_query_pcam_reg(काष्ठा mlx5_core_dev *dev, u32 *pcam, u8 feature_group,
			u8 access_reg_group)
अणु
	u32 in[MLX5_ST_SZ_DW(pcam_reg)] = अणु0पूर्ण;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(pcam_reg);

	MLX5_SET(pcam_reg, in, feature_group, feature_group);
	MLX5_SET(pcam_reg, in, access_reg_group, access_reg_group);

	वापस mlx5_core_access_reg(dev, in, sz, pcam, sz, MLX5_REG_PCAM, 0, 0);
पूर्ण

पूर्णांक mlx5_query_mcam_reg(काष्ठा mlx5_core_dev *dev, u32 *mcam, u8 feature_group,
			u8 access_reg_group)
अणु
	u32 in[MLX5_ST_SZ_DW(mcam_reg)] = अणु0पूर्ण;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(mcam_reg);

	MLX5_SET(mcam_reg, in, feature_group, feature_group);
	MLX5_SET(mcam_reg, in, access_reg_group, access_reg_group);

	वापस mlx5_core_access_reg(dev, in, sz, mcam, sz, MLX5_REG_MCAM, 0, 0);
पूर्ण

पूर्णांक mlx5_query_qcam_reg(काष्ठा mlx5_core_dev *mdev, u32 *qcam,
			u8 feature_group, u8 access_reg_group)
अणु
	u32 in[MLX5_ST_SZ_DW(qcam_reg)] = अणुपूर्ण;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(qcam_reg);

	MLX5_SET(qcam_reg, in, feature_group, feature_group);
	MLX5_SET(qcam_reg, in, access_reg_group, access_reg_group);

	वापस mlx5_core_access_reg(mdev, in, sz, qcam, sz, MLX5_REG_QCAM, 0, 0);
पूर्ण

काष्ठा mlx5_reg_pcap अणु
	u8			rsvd0;
	u8			port_num;
	u8			rsvd1[2];
	__be32			caps_127_96;
	__be32			caps_95_64;
	__be32			caps_63_32;
	__be32			caps_31_0;
पूर्ण;

पूर्णांक mlx5_set_port_caps(काष्ठा mlx5_core_dev *dev, u8 port_num, u32 caps)
अणु
	काष्ठा mlx5_reg_pcap in;
	काष्ठा mlx5_reg_pcap out;

	स_रखो(&in, 0, माप(in));
	in.caps_127_96 = cpu_to_be32(caps);
	in.port_num = port_num;

	वापस mlx5_core_access_reg(dev, &in, माप(in), &out,
				    माप(out), MLX5_REG_PCAP, 0, 1);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_set_port_caps);

पूर्णांक mlx5_query_port_ptys(काष्ठा mlx5_core_dev *dev, u32 *ptys,
			 पूर्णांक ptys_size, पूर्णांक proto_mask, u8 local_port)
अणु
	u32 in[MLX5_ST_SZ_DW(ptys_reg)] = अणु0पूर्ण;

	MLX5_SET(ptys_reg, in, local_port, local_port);
	MLX5_SET(ptys_reg, in, proto_mask, proto_mask);
	वापस mlx5_core_access_reg(dev, in, माप(in), ptys,
				    ptys_size, MLX5_REG_PTYS, 0, 0);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_port_ptys);

पूर्णांक mlx5_set_port_beacon(काष्ठा mlx5_core_dev *dev, u16 beacon_duration)
अणु
	u32 in[MLX5_ST_SZ_DW(mlcr_reg)]  = अणु0पूर्ण;
	u32 out[MLX5_ST_SZ_DW(mlcr_reg)];

	MLX5_SET(mlcr_reg, in, local_port, 1);
	MLX5_SET(mlcr_reg, in, beacon_duration, beacon_duration);
	वापस mlx5_core_access_reg(dev, in, माप(in), out,
				    माप(out), MLX5_REG_MLCR, 0, 1);
पूर्ण

पूर्णांक mlx5_query_ib_port_oper(काष्ठा mlx5_core_dev *dev, u16 *link_width_oper,
			    u16 *proto_oper, u8 local_port)
अणु
	u32 out[MLX5_ST_SZ_DW(ptys_reg)];
	पूर्णांक err;

	err = mlx5_query_port_ptys(dev, out, माप(out), MLX5_PTYS_IB,
				   local_port);
	अगर (err)
		वापस err;

	*link_width_oper = MLX5_GET(ptys_reg, out, ib_link_width_oper);
	*proto_oper = MLX5_GET(ptys_reg, out, ib_proto_oper);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlx5_query_ib_port_oper);

/* This function should be used after setting a port रेजिस्टर only */
व्योम mlx5_toggle_port_link(काष्ठा mlx5_core_dev *dev)
अणु
	क्रमागत mlx5_port_status ps;

	mlx5_query_port_admin_status(dev, &ps);
	mlx5_set_port_admin_status(dev, MLX5_PORT_DOWN);
	अगर (ps == MLX5_PORT_UP)
		mlx5_set_port_admin_status(dev, MLX5_PORT_UP);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_toggle_port_link);

पूर्णांक mlx5_set_port_admin_status(काष्ठा mlx5_core_dev *dev,
			       क्रमागत mlx5_port_status status)
अणु
	u32 in[MLX5_ST_SZ_DW(paos_reg)] = अणु0पूर्ण;
	u32 out[MLX5_ST_SZ_DW(paos_reg)];

	MLX5_SET(paos_reg, in, local_port, 1);
	MLX5_SET(paos_reg, in, admin_status, status);
	MLX5_SET(paos_reg, in, ase, 1);
	वापस mlx5_core_access_reg(dev, in, माप(in), out,
				    माप(out), MLX5_REG_PAOS, 0, 1);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_set_port_admin_status);

पूर्णांक mlx5_query_port_admin_status(काष्ठा mlx5_core_dev *dev,
				 क्रमागत mlx5_port_status *status)
अणु
	u32 in[MLX5_ST_SZ_DW(paos_reg)] = अणु0पूर्ण;
	u32 out[MLX5_ST_SZ_DW(paos_reg)];
	पूर्णांक err;

	MLX5_SET(paos_reg, in, local_port, 1);
	err = mlx5_core_access_reg(dev, in, माप(in), out,
				   माप(out), MLX5_REG_PAOS, 0, 0);
	अगर (err)
		वापस err;
	*status = MLX5_GET(paos_reg, out, admin_status);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_port_admin_status);

अटल व्योम mlx5_query_port_mtu(काष्ठा mlx5_core_dev *dev, u16 *admin_mtu,
				u16 *max_mtu, u16 *oper_mtu, u8 port)
अणु
	u32 in[MLX5_ST_SZ_DW(pmtu_reg)] = अणु0पूर्ण;
	u32 out[MLX5_ST_SZ_DW(pmtu_reg)];

	MLX5_SET(pmtu_reg, in, local_port, port);
	mlx5_core_access_reg(dev, in, माप(in), out,
			     माप(out), MLX5_REG_PMTU, 0, 0);

	अगर (max_mtu)
		*max_mtu  = MLX5_GET(pmtu_reg, out, max_mtu);
	अगर (oper_mtu)
		*oper_mtu = MLX5_GET(pmtu_reg, out, oper_mtu);
	अगर (admin_mtu)
		*admin_mtu = MLX5_GET(pmtu_reg, out, admin_mtu);
पूर्ण

पूर्णांक mlx5_set_port_mtu(काष्ठा mlx5_core_dev *dev, u16 mtu, u8 port)
अणु
	u32 in[MLX5_ST_SZ_DW(pmtu_reg)] = अणु0पूर्ण;
	u32 out[MLX5_ST_SZ_DW(pmtu_reg)];

	MLX5_SET(pmtu_reg, in, admin_mtu, mtu);
	MLX5_SET(pmtu_reg, in, local_port, port);
	वापस mlx5_core_access_reg(dev, in, माप(in), out,
				   माप(out), MLX5_REG_PMTU, 0, 1);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_set_port_mtu);

व्योम mlx5_query_port_max_mtu(काष्ठा mlx5_core_dev *dev, u16 *max_mtu,
			     u8 port)
अणु
	mlx5_query_port_mtu(dev, शून्य, max_mtu, शून्य, port);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_port_max_mtu);

व्योम mlx5_query_port_oper_mtu(काष्ठा mlx5_core_dev *dev, u16 *oper_mtu,
			      u8 port)
अणु
	mlx5_query_port_mtu(dev, शून्य, शून्य, oper_mtu, port);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_port_oper_mtu);

अटल पूर्णांक mlx5_query_module_num(काष्ठा mlx5_core_dev *dev, पूर्णांक *module_num)
अणु
	u32 in[MLX5_ST_SZ_DW(pmlp_reg)] = अणु0पूर्ण;
	u32 out[MLX5_ST_SZ_DW(pmlp_reg)];
	पूर्णांक module_mapping;
	पूर्णांक err;

	MLX5_SET(pmlp_reg, in, local_port, 1);
	err = mlx5_core_access_reg(dev, in, माप(in), out, माप(out),
				   MLX5_REG_PMLP, 0, 0);
	अगर (err)
		वापस err;

	module_mapping = MLX5_GET(pmlp_reg, out, lane0_module_mapping);
	*module_num = module_mapping & MLX5_EEPROM_IDENTIFIER_BYTE_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_query_module_id(काष्ठा mlx5_core_dev *dev, पूर्णांक module_num,
				u8 *module_id)
अणु
	u32 in[MLX5_ST_SZ_DW(mcia_reg)] = अणुपूर्ण;
	u32 out[MLX5_ST_SZ_DW(mcia_reg)];
	पूर्णांक err, status;
	u8 *ptr;

	MLX5_SET(mcia_reg, in, i2c_device_address, MLX5_I2C_ADDR_LOW);
	MLX5_SET(mcia_reg, in, module, module_num);
	MLX5_SET(mcia_reg, in, device_address, 0);
	MLX5_SET(mcia_reg, in, page_number, 0);
	MLX5_SET(mcia_reg, in, size, 1);
	MLX5_SET(mcia_reg, in, l, 0);

	err = mlx5_core_access_reg(dev, in, माप(in), out,
				   माप(out), MLX5_REG_MCIA, 0, 0);
	अगर (err)
		वापस err;

	status = MLX5_GET(mcia_reg, out, status);
	अगर (status) अणु
		mlx5_core_err(dev, "query_mcia_reg failed: status: 0x%x\n",
			      status);
		वापस -EIO;
	पूर्ण
	ptr = MLX5_ADDR_OF(mcia_reg, out, dword_0);

	*module_id = ptr[0];

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_qsfp_eeprom_page(u16 offset)
अणु
	अगर (offset < MLX5_EEPROM_PAGE_LENGTH)
		/* Addresses between 0-255 - page 00 */
		वापस 0;

	/* Addresses between 256 - 639 beदीर्घs to pages 01, 02 and 03
	 * For example, offset = 400 beदीर्घs to page 02:
	 * 1 + ((400 - 256)/128) = 2
	 */
	वापस 1 + ((offset - MLX5_EEPROM_PAGE_LENGTH) /
		    MLX5_EEPROM_HIGH_PAGE_LENGTH);
पूर्ण

अटल पूर्णांक mlx5_qsfp_eeprom_high_page_offset(पूर्णांक page_num)
अणु
	अगर (!page_num) /* Page 0 always start from low page */
		वापस 0;

	/* High page */
	वापस page_num * MLX5_EEPROM_HIGH_PAGE_LENGTH;
पूर्ण

अटल व्योम mlx5_qsfp_eeprom_params_set(u16 *i2c_addr, पूर्णांक *page_num, u16 *offset)
अणु
	*i2c_addr = MLX5_I2C_ADDR_LOW;
	*page_num = mlx5_qsfp_eeprom_page(*offset);
	*offset -=  mlx5_qsfp_eeprom_high_page_offset(*page_num);
पूर्ण

अटल व्योम mlx5_sfp_eeprom_params_set(u16 *i2c_addr, पूर्णांक *page_num, u16 *offset)
अणु
	*i2c_addr = MLX5_I2C_ADDR_LOW;
	*page_num = 0;

	अगर (*offset < MLX5_EEPROM_PAGE_LENGTH)
		वापस;

	*i2c_addr = MLX5_I2C_ADDR_HIGH;
	*offset -= MLX5_EEPROM_PAGE_LENGTH;
पूर्ण

अटल पूर्णांक mlx5_query_mcia(काष्ठा mlx5_core_dev *dev,
			   काष्ठा mlx5_module_eeprom_query_params *params, u8 *data)
अणु
	u32 in[MLX5_ST_SZ_DW(mcia_reg)] = अणुपूर्ण;
	u32 out[MLX5_ST_SZ_DW(mcia_reg)];
	पूर्णांक status, err;
	व्योम *ptr;
	u16 size;

	size = min_t(पूर्णांक, params->size, MLX5_EEPROM_MAX_BYTES);

	MLX5_SET(mcia_reg, in, l, 0);
	MLX5_SET(mcia_reg, in, size, size);
	MLX5_SET(mcia_reg, in, module, params->module_number);
	MLX5_SET(mcia_reg, in, device_address, params->offset);
	MLX5_SET(mcia_reg, in, page_number, params->page);
	MLX5_SET(mcia_reg, in, i2c_device_address, params->i2c_address);

	err = mlx5_core_access_reg(dev, in, माप(in), out,
				   माप(out), MLX5_REG_MCIA, 0, 0);
	अगर (err)
		वापस err;

	status = MLX5_GET(mcia_reg, out, status);
	अगर (status) अणु
		mlx5_core_err(dev, "query_mcia_reg failed: status: 0x%x\n",
			      status);
		वापस -EIO;
	पूर्ण

	ptr = MLX5_ADDR_OF(mcia_reg, out, dword_0);
	स_नकल(data, ptr, size);

	वापस size;
पूर्ण

पूर्णांक mlx5_query_module_eeprom(काष्ठा mlx5_core_dev *dev,
			     u16 offset, u16 size, u8 *data)
अणु
	काष्ठा mlx5_module_eeprom_query_params query = अणु0पूर्ण;
	u8 module_id;
	पूर्णांक err;

	err = mlx5_query_module_num(dev, &query.module_number);
	अगर (err)
		वापस err;

	err = mlx5_query_module_id(dev, query.module_number, &module_id);
	अगर (err)
		वापस err;

	चयन (module_id) अणु
	हाल MLX5_MODULE_ID_SFP:
		mlx5_sfp_eeprom_params_set(&query.i2c_address, &query.page, &query.offset);
		अवरोध;
	हाल MLX5_MODULE_ID_QSFP:
	हाल MLX5_MODULE_ID_QSFP_PLUS:
	हाल MLX5_MODULE_ID_QSFP28:
		mlx5_qsfp_eeprom_params_set(&query.i2c_address, &query.page, &query.offset);
		अवरोध;
	शेष:
		mlx5_core_err(dev, "Module ID not recognized: 0x%x\n", module_id);
		वापस -EINVAL;
	पूर्ण

	अगर (query.offset + size > MLX5_EEPROM_PAGE_LENGTH)
		/* Cross pages पढ़ो, पढ़ो until offset 256 in low page */
		size -= offset + size - MLX5_EEPROM_PAGE_LENGTH;

	query.size = size;

	वापस mlx5_query_mcia(dev, &query, data);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_module_eeprom);

पूर्णांक mlx5_query_module_eeprom_by_page(काष्ठा mlx5_core_dev *dev,
				     काष्ठा mlx5_module_eeprom_query_params *params,
				     u8 *data)
अणु
	u8 module_id;
	पूर्णांक err;

	err = mlx5_query_module_num(dev, &params->module_number);
	अगर (err)
		वापस err;

	err = mlx5_query_module_id(dev, params->module_number, &module_id);
	अगर (err)
		वापस err;

	चयन (module_id) अणु
	हाल MLX5_MODULE_ID_SFP:
		अगर (params->page > 0)
			वापस -EINVAL;
		अवरोध;
	हाल MLX5_MODULE_ID_QSFP:
	हाल MLX5_MODULE_ID_QSFP28:
	हाल MLX5_MODULE_ID_QSFP_PLUS:
		अगर (params->page > 3)
			वापस -EINVAL;
		अवरोध;
	हाल MLX5_MODULE_ID_DSFP:
		अवरोध;
	शेष:
		mlx5_core_err(dev, "Module ID not recognized: 0x%x\n", module_id);
		वापस -EINVAL;
	पूर्ण

	अगर (params->i2c_address != MLX5_I2C_ADDR_HIGH &&
	    params->i2c_address != MLX5_I2C_ADDR_LOW) अणु
		mlx5_core_err(dev, "I2C address not recognized: 0x%x\n", params->i2c_address);
		वापस -EINVAL;
	पूर्ण

	वापस mlx5_query_mcia(dev, params, data);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_module_eeprom_by_page);

अटल पूर्णांक mlx5_query_port_pvlc(काष्ठा mlx5_core_dev *dev, u32 *pvlc,
				पूर्णांक pvlc_size,  u8 local_port)
अणु
	u32 in[MLX5_ST_SZ_DW(pvlc_reg)] = अणु0पूर्ण;

	MLX5_SET(pvlc_reg, in, local_port, local_port);
	वापस mlx5_core_access_reg(dev, in, माप(in), pvlc,
				    pvlc_size, MLX5_REG_PVLC, 0, 0);
पूर्ण

पूर्णांक mlx5_query_port_vl_hw_cap(काष्ठा mlx5_core_dev *dev,
			      u8 *vl_hw_cap, u8 local_port)
अणु
	u32 out[MLX5_ST_SZ_DW(pvlc_reg)];
	पूर्णांक err;

	err = mlx5_query_port_pvlc(dev, out, माप(out), local_port);
	अगर (err)
		वापस err;

	*vl_hw_cap = MLX5_GET(pvlc_reg, out, vl_hw_cap);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_port_vl_hw_cap);

पूर्णांक mlx5_core_query_ib_ppcnt(काष्ठा mlx5_core_dev *dev,
			     u8 port_num, व्योम *out, माप_प्रकार sz)
अणु
	u32 *in;
	पूर्णांक err;

	in  = kvzalloc(sz, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		वापस err;
	पूर्ण

	MLX5_SET(ppcnt_reg, in, local_port, port_num);

	MLX5_SET(ppcnt_reg, in, grp, MLX5_INFINIBAND_PORT_COUNTERS_GROUP);
	err = mlx5_core_access_reg(dev, in, sz, out,
				   sz, MLX5_REG_PPCNT, 0, 0);

	kvमुक्त(in);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_core_query_ib_ppcnt);

अटल पूर्णांक mlx5_query_pfcc_reg(काष्ठा mlx5_core_dev *dev, u32 *out,
			       u32 out_size)
अणु
	u32 in[MLX5_ST_SZ_DW(pfcc_reg)] = अणु0पूर्ण;

	MLX5_SET(pfcc_reg, in, local_port, 1);

	वापस mlx5_core_access_reg(dev, in, माप(in), out,
				    out_size, MLX5_REG_PFCC, 0, 0);
पूर्ण

पूर्णांक mlx5_set_port_छोड़ो(काष्ठा mlx5_core_dev *dev, u32 rx_छोड़ो, u32 tx_छोड़ो)
अणु
	u32 in[MLX5_ST_SZ_DW(pfcc_reg)] = अणु0पूर्ण;
	u32 out[MLX5_ST_SZ_DW(pfcc_reg)];

	MLX5_SET(pfcc_reg, in, local_port, 1);
	MLX5_SET(pfcc_reg, in, pptx, tx_छोड़ो);
	MLX5_SET(pfcc_reg, in, pprx, rx_छोड़ो);

	वापस mlx5_core_access_reg(dev, in, माप(in), out,
				    माप(out), MLX5_REG_PFCC, 0, 1);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_set_port_छोड़ो);

पूर्णांक mlx5_query_port_छोड़ो(काष्ठा mlx5_core_dev *dev,
			  u32 *rx_छोड़ो, u32 *tx_छोड़ो)
अणु
	u32 out[MLX5_ST_SZ_DW(pfcc_reg)];
	पूर्णांक err;

	err = mlx5_query_pfcc_reg(dev, out, माप(out));
	अगर (err)
		वापस err;

	अगर (rx_छोड़ो)
		*rx_छोड़ो = MLX5_GET(pfcc_reg, out, pprx);

	अगर (tx_छोड़ो)
		*tx_छोड़ो = MLX5_GET(pfcc_reg, out, pptx);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_port_छोड़ो);

पूर्णांक mlx5_set_port_stall_watermark(काष्ठा mlx5_core_dev *dev,
				  u16 stall_critical_watermark,
				  u16 stall_minor_watermark)
अणु
	u32 in[MLX5_ST_SZ_DW(pfcc_reg)] = अणु0पूर्ण;
	u32 out[MLX5_ST_SZ_DW(pfcc_reg)];

	MLX5_SET(pfcc_reg, in, local_port, 1);
	MLX5_SET(pfcc_reg, in, pptx_mask_n, 1);
	MLX5_SET(pfcc_reg, in, pprx_mask_n, 1);
	MLX5_SET(pfcc_reg, in, ppan_mask_n, 1);
	MLX5_SET(pfcc_reg, in, critical_stall_mask, 1);
	MLX5_SET(pfcc_reg, in, minor_stall_mask, 1);
	MLX5_SET(pfcc_reg, in, device_stall_critical_watermark,
		 stall_critical_watermark);
	MLX5_SET(pfcc_reg, in, device_stall_minor_watermark, stall_minor_watermark);

	वापस mlx5_core_access_reg(dev, in, माप(in), out,
				    माप(out), MLX5_REG_PFCC, 0, 1);
पूर्ण

पूर्णांक mlx5_query_port_stall_watermark(काष्ठा mlx5_core_dev *dev,
				    u16 *stall_critical_watermark,
				    u16 *stall_minor_watermark)
अणु
	u32 out[MLX5_ST_SZ_DW(pfcc_reg)];
	पूर्णांक err;

	err = mlx5_query_pfcc_reg(dev, out, माप(out));
	अगर (err)
		वापस err;

	अगर (stall_critical_watermark)
		*stall_critical_watermark = MLX5_GET(pfcc_reg, out,
						     device_stall_critical_watermark);

	अगर (stall_minor_watermark)
		*stall_minor_watermark = MLX5_GET(pfcc_reg, out,
						  device_stall_minor_watermark);

	वापस 0;
पूर्ण

पूर्णांक mlx5_set_port_pfc(काष्ठा mlx5_core_dev *dev, u8 pfc_en_tx, u8 pfc_en_rx)
अणु
	u32 in[MLX5_ST_SZ_DW(pfcc_reg)] = अणु0पूर्ण;
	u32 out[MLX5_ST_SZ_DW(pfcc_reg)];

	MLX5_SET(pfcc_reg, in, local_port, 1);
	MLX5_SET(pfcc_reg, in, pfctx, pfc_en_tx);
	MLX5_SET(pfcc_reg, in, pfcrx, pfc_en_rx);
	MLX5_SET_TO_ONES(pfcc_reg, in, prio_mask_tx);
	MLX5_SET_TO_ONES(pfcc_reg, in, prio_mask_rx);

	वापस mlx5_core_access_reg(dev, in, माप(in), out,
				    माप(out), MLX5_REG_PFCC, 0, 1);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_set_port_pfc);

पूर्णांक mlx5_query_port_pfc(काष्ठा mlx5_core_dev *dev, u8 *pfc_en_tx, u8 *pfc_en_rx)
अणु
	u32 out[MLX5_ST_SZ_DW(pfcc_reg)];
	पूर्णांक err;

	err = mlx5_query_pfcc_reg(dev, out, माप(out));
	अगर (err)
		वापस err;

	अगर (pfc_en_tx)
		*pfc_en_tx = MLX5_GET(pfcc_reg, out, pfctx);

	अगर (pfc_en_rx)
		*pfc_en_rx = MLX5_GET(pfcc_reg, out, pfcrx);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_port_pfc);

पूर्णांक mlx5_max_tc(काष्ठा mlx5_core_dev *mdev)
अणु
	u8 num_tc = MLX5_CAP_GEN(mdev, max_tc) ? : 8;

	वापस num_tc - 1;
पूर्ण

पूर्णांक mlx5_query_port_dcbx_param(काष्ठा mlx5_core_dev *mdev, u32 *out)
अणु
	u32 in[MLX5_ST_SZ_DW(dcbx_param)] = अणु0पूर्ण;

	MLX5_SET(dcbx_param, in, port_number, 1);

	वापस  mlx5_core_access_reg(mdev, in, माप(in), out,
				    माप(in), MLX5_REG_DCBX_PARAM, 0, 0);
पूर्ण

पूर्णांक mlx5_set_port_dcbx_param(काष्ठा mlx5_core_dev *mdev, u32 *in)
अणु
	u32 out[MLX5_ST_SZ_DW(dcbx_param)];

	MLX5_SET(dcbx_param, in, port_number, 1);

	वापस mlx5_core_access_reg(mdev, in, माप(out), out,
				    माप(out), MLX5_REG_DCBX_PARAM, 0, 1);
पूर्ण

पूर्णांक mlx5_set_port_prio_tc(काष्ठा mlx5_core_dev *mdev, u8 *prio_tc)
अणु
	u32 in[MLX5_ST_SZ_DW(qtct_reg)] = अणु0पूर्ण;
	u32 out[MLX5_ST_SZ_DW(qtct_reg)];
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		अगर (prio_tc[i] > mlx5_max_tc(mdev))
			वापस -EINVAL;

		MLX5_SET(qtct_reg, in, prio, i);
		MLX5_SET(qtct_reg, in, tclass, prio_tc[i]);

		err = mlx5_core_access_reg(mdev, in, माप(in), out,
					   माप(out), MLX5_REG_QTCT, 0, 1);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_set_port_prio_tc);

पूर्णांक mlx5_query_port_prio_tc(काष्ठा mlx5_core_dev *mdev,
			    u8 prio, u8 *tc)
अणु
	u32 in[MLX5_ST_SZ_DW(qtct_reg)];
	u32 out[MLX5_ST_SZ_DW(qtct_reg)];
	पूर्णांक err;

	स_रखो(in, 0, माप(in));
	स_रखो(out, 0, माप(out));

	MLX5_SET(qtct_reg, in, port_number, 1);
	MLX5_SET(qtct_reg, in, prio, prio);

	err = mlx5_core_access_reg(mdev, in, माप(in), out,
				   माप(out), MLX5_REG_QTCT, 0, 0);
	अगर (!err)
		*tc = MLX5_GET(qtct_reg, out, tclass);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_port_prio_tc);

अटल पूर्णांक mlx5_set_port_qetcr_reg(काष्ठा mlx5_core_dev *mdev, u32 *in,
				   पूर्णांक inlen)
अणु
	u32 out[MLX5_ST_SZ_DW(qetc_reg)];

	अगर (!MLX5_CAP_GEN(mdev, ets))
		वापस -EOPNOTSUPP;

	वापस mlx5_core_access_reg(mdev, in, inlen, out, माप(out),
				    MLX5_REG_QETCR, 0, 1);
पूर्ण

अटल पूर्णांक mlx5_query_port_qetcr_reg(काष्ठा mlx5_core_dev *mdev, u32 *out,
				     पूर्णांक outlen)
अणु
	u32 in[MLX5_ST_SZ_DW(qetc_reg)];

	अगर (!MLX5_CAP_GEN(mdev, ets))
		वापस -EOPNOTSUPP;

	स_रखो(in, 0, माप(in));
	वापस mlx5_core_access_reg(mdev, in, माप(in), out, outlen,
				    MLX5_REG_QETCR, 0, 0);
पूर्ण

पूर्णांक mlx5_set_port_tc_group(काष्ठा mlx5_core_dev *mdev, u8 *tc_group)
अणु
	u32 in[MLX5_ST_SZ_DW(qetc_reg)] = अणु0पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i <= mlx5_max_tc(mdev); i++) अणु
		MLX5_SET(qetc_reg, in, tc_configuration[i].g, 1);
		MLX5_SET(qetc_reg, in, tc_configuration[i].group, tc_group[i]);
	पूर्ण

	वापस mlx5_set_port_qetcr_reg(mdev, in, माप(in));
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_set_port_tc_group);

पूर्णांक mlx5_query_port_tc_group(काष्ठा mlx5_core_dev *mdev,
			     u8 tc, u8 *tc_group)
अणु
	u32 out[MLX5_ST_SZ_DW(qetc_reg)];
	व्योम *ets_tcn_conf;
	पूर्णांक err;

	err = mlx5_query_port_qetcr_reg(mdev, out, माप(out));
	अगर (err)
		वापस err;

	ets_tcn_conf = MLX5_ADDR_OF(qetc_reg, out,
				    tc_configuration[tc]);

	*tc_group = MLX5_GET(ets_tcn_config_reg, ets_tcn_conf,
			     group);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_port_tc_group);

पूर्णांक mlx5_set_port_tc_bw_alloc(काष्ठा mlx5_core_dev *mdev, u8 *tc_bw)
अणु
	u32 in[MLX5_ST_SZ_DW(qetc_reg)] = अणु0पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i <= mlx5_max_tc(mdev); i++) अणु
		MLX5_SET(qetc_reg, in, tc_configuration[i].b, 1);
		MLX5_SET(qetc_reg, in, tc_configuration[i].bw_allocation, tc_bw[i]);
	पूर्ण

	वापस mlx5_set_port_qetcr_reg(mdev, in, माप(in));
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_set_port_tc_bw_alloc);

पूर्णांक mlx5_query_port_tc_bw_alloc(काष्ठा mlx5_core_dev *mdev,
				u8 tc, u8 *bw_pct)
अणु
	u32 out[MLX5_ST_SZ_DW(qetc_reg)];
	व्योम *ets_tcn_conf;
	पूर्णांक err;

	err = mlx5_query_port_qetcr_reg(mdev, out, माप(out));
	अगर (err)
		वापस err;

	ets_tcn_conf = MLX5_ADDR_OF(qetc_reg, out,
				    tc_configuration[tc]);

	*bw_pct = MLX5_GET(ets_tcn_config_reg, ets_tcn_conf,
			   bw_allocation);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_port_tc_bw_alloc);

पूर्णांक mlx5_modअगरy_port_ets_rate_limit(काष्ठा mlx5_core_dev *mdev,
				    u8 *max_bw_value,
				    u8 *max_bw_units)
अणु
	u32 in[MLX5_ST_SZ_DW(qetc_reg)] = अणु0पूर्ण;
	व्योम *ets_tcn_conf;
	पूर्णांक i;

	MLX5_SET(qetc_reg, in, port_number, 1);

	क्रम (i = 0; i <= mlx5_max_tc(mdev); i++) अणु
		ets_tcn_conf = MLX5_ADDR_OF(qetc_reg, in, tc_configuration[i]);

		MLX5_SET(ets_tcn_config_reg, ets_tcn_conf, r, 1);
		MLX5_SET(ets_tcn_config_reg, ets_tcn_conf, max_bw_units,
			 max_bw_units[i]);
		MLX5_SET(ets_tcn_config_reg, ets_tcn_conf, max_bw_value,
			 max_bw_value[i]);
	पूर्ण

	वापस mlx5_set_port_qetcr_reg(mdev, in, माप(in));
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_modअगरy_port_ets_rate_limit);

पूर्णांक mlx5_query_port_ets_rate_limit(काष्ठा mlx5_core_dev *mdev,
				   u8 *max_bw_value,
				   u8 *max_bw_units)
अणु
	u32 out[MLX5_ST_SZ_DW(qetc_reg)];
	व्योम *ets_tcn_conf;
	पूर्णांक err;
	पूर्णांक i;

	err = mlx5_query_port_qetcr_reg(mdev, out, माप(out));
	अगर (err)
		वापस err;

	क्रम (i = 0; i <= mlx5_max_tc(mdev); i++) अणु
		ets_tcn_conf = MLX5_ADDR_OF(qetc_reg, out, tc_configuration[i]);

		max_bw_value[i] = MLX5_GET(ets_tcn_config_reg, ets_tcn_conf,
					   max_bw_value);
		max_bw_units[i] = MLX5_GET(ets_tcn_config_reg, ets_tcn_conf,
					   max_bw_units);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_port_ets_rate_limit);

पूर्णांक mlx5_set_port_wol(काष्ठा mlx5_core_dev *mdev, u8 wol_mode)
अणु
	u32 in[MLX5_ST_SZ_DW(set_wol_rol_in)] = अणुपूर्ण;

	MLX5_SET(set_wol_rol_in, in, opcode, MLX5_CMD_OP_SET_WOL_ROL);
	MLX5_SET(set_wol_rol_in, in, wol_mode_valid, 1);
	MLX5_SET(set_wol_rol_in, in, wol_mode, wol_mode);
	वापस mlx5_cmd_exec_in(mdev, set_wol_rol, in);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_set_port_wol);

पूर्णांक mlx5_query_port_wol(काष्ठा mlx5_core_dev *mdev, u8 *wol_mode)
अणु
	u32 out[MLX5_ST_SZ_DW(query_wol_rol_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(query_wol_rol_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(query_wol_rol_in, in, opcode, MLX5_CMD_OP_QUERY_WOL_ROL);
	err = mlx5_cmd_exec_inout(mdev, query_wol_rol, in, out);
	अगर (!err)
		*wol_mode = MLX5_GET(query_wol_rol_out, out, wol_mode);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_port_wol);

पूर्णांक mlx5_query_ports_check(काष्ठा mlx5_core_dev *mdev, u32 *out, पूर्णांक outlen)
अणु
	u32 in[MLX5_ST_SZ_DW(pcmr_reg)] = अणु0पूर्ण;

	MLX5_SET(pcmr_reg, in, local_port, 1);
	वापस mlx5_core_access_reg(mdev, in, माप(in), out,
				    outlen, MLX5_REG_PCMR, 0, 0);
पूर्ण

पूर्णांक mlx5_set_ports_check(काष्ठा mlx5_core_dev *mdev, u32 *in, पूर्णांक inlen)
अणु
	u32 out[MLX5_ST_SZ_DW(pcmr_reg)];

	वापस mlx5_core_access_reg(mdev, in, inlen, out,
				    माप(out), MLX5_REG_PCMR, 0, 1);
पूर्ण

पूर्णांक mlx5_set_port_fcs(काष्ठा mlx5_core_dev *mdev, u8 enable)
अणु
	u32 in[MLX5_ST_SZ_DW(pcmr_reg)] = अणु0पूर्ण;
	पूर्णांक err;

	err = mlx5_query_ports_check(mdev, in, माप(in));
	अगर (err)
		वापस err;
	MLX5_SET(pcmr_reg, in, local_port, 1);
	MLX5_SET(pcmr_reg, in, fcs_chk, enable);
	वापस mlx5_set_ports_check(mdev, in, माप(in));
पूर्ण

व्योम mlx5_query_port_fcs(काष्ठा mlx5_core_dev *mdev, bool *supported,
			 bool *enabled)
अणु
	u32 out[MLX5_ST_SZ_DW(pcmr_reg)];
	/* Default values क्रम FW which करो not support MLX5_REG_PCMR */
	*supported = false;
	*enabled = true;

	अगर (!MLX5_CAP_GEN(mdev, ports_check))
		वापस;

	अगर (mlx5_query_ports_check(mdev, out, माप(out)))
		वापस;

	*supported = !!(MLX5_GET(pcmr_reg, out, fcs_cap));
	*enabled = !!(MLX5_GET(pcmr_reg, out, fcs_chk));
पूर्ण

पूर्णांक mlx5_query_mtpps(काष्ठा mlx5_core_dev *mdev, u32 *mtpps, u32 mtpps_size)
अणु
	u32 in[MLX5_ST_SZ_DW(mtpps_reg)] = अणु0पूर्ण;

	वापस mlx5_core_access_reg(mdev, in, माप(in), mtpps,
				    mtpps_size, MLX5_REG_MTPPS, 0, 0);
पूर्ण

पूर्णांक mlx5_set_mtpps(काष्ठा mlx5_core_dev *mdev, u32 *mtpps, u32 mtpps_size)
अणु
	u32 out[MLX5_ST_SZ_DW(mtpps_reg)] = अणु0पूर्ण;

	वापस mlx5_core_access_reg(mdev, mtpps, mtpps_size, out,
				    माप(out), MLX5_REG_MTPPS, 0, 1);
पूर्ण

पूर्णांक mlx5_query_mtppse(काष्ठा mlx5_core_dev *mdev, u8 pin, u8 *arm, u8 *mode)
अणु
	u32 out[MLX5_ST_SZ_DW(mtppse_reg)] = अणु0पूर्ण;
	u32 in[MLX5_ST_SZ_DW(mtppse_reg)] = अणु0पूर्ण;
	पूर्णांक err = 0;

	MLX5_SET(mtppse_reg, in, pin, pin);

	err = mlx5_core_access_reg(mdev, in, माप(in), out,
				   माप(out), MLX5_REG_MTPPSE, 0, 0);
	अगर (err)
		वापस err;

	*arm = MLX5_GET(mtppse_reg, in, event_arm);
	*mode = MLX5_GET(mtppse_reg, in, event_generation_mode);

	वापस err;
पूर्ण

पूर्णांक mlx5_set_mtppse(काष्ठा mlx5_core_dev *mdev, u8 pin, u8 arm, u8 mode)
अणु
	u32 out[MLX5_ST_SZ_DW(mtppse_reg)] = अणु0पूर्ण;
	u32 in[MLX5_ST_SZ_DW(mtppse_reg)] = अणु0पूर्ण;

	MLX5_SET(mtppse_reg, in, pin, pin);
	MLX5_SET(mtppse_reg, in, event_arm, arm);
	MLX5_SET(mtppse_reg, in, event_generation_mode, mode);

	वापस mlx5_core_access_reg(mdev, in, माप(in), out,
				    माप(out), MLX5_REG_MTPPSE, 0, 1);
पूर्ण

पूर्णांक mlx5_set_trust_state(काष्ठा mlx5_core_dev *mdev, u8 trust_state)
अणु
	u32 out[MLX5_ST_SZ_DW(qpts_reg)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(qpts_reg)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(qpts_reg, in, local_port, 1);
	MLX5_SET(qpts_reg, in, trust_state, trust_state);

	err = mlx5_core_access_reg(mdev, in, माप(in), out,
				   माप(out), MLX5_REG_QPTS, 0, 1);
	वापस err;
पूर्ण

पूर्णांक mlx5_query_trust_state(काष्ठा mlx5_core_dev *mdev, u8 *trust_state)
अणु
	u32 out[MLX5_ST_SZ_DW(qpts_reg)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(qpts_reg)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(qpts_reg, in, local_port, 1);

	err = mlx5_core_access_reg(mdev, in, माप(in), out,
				   माप(out), MLX5_REG_QPTS, 0, 0);
	अगर (!err)
		*trust_state = MLX5_GET(qpts_reg, out, trust_state);

	वापस err;
पूर्ण

पूर्णांक mlx5_set_dscp2prio(काष्ठा mlx5_core_dev *mdev, u8 dscp, u8 prio)
अणु
	पूर्णांक sz = MLX5_ST_SZ_BYTES(qpdpm_reg);
	व्योम *qpdpm_dscp;
	व्योम *out;
	व्योम *in;
	पूर्णांक err;

	in = kzalloc(sz, GFP_KERNEL);
	out = kzalloc(sz, GFP_KERNEL);
	अगर (!in || !out) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	MLX5_SET(qpdpm_reg, in, local_port, 1);
	err = mlx5_core_access_reg(mdev, in, sz, out, sz, MLX5_REG_QPDPM, 0, 0);
	अगर (err)
		जाओ out;

	स_नकल(in, out, sz);
	MLX5_SET(qpdpm_reg, in, local_port, 1);

	/* Update the corresponding dscp entry */
	qpdpm_dscp = MLX5_ADDR_OF(qpdpm_reg, in, dscp[dscp]);
	MLX5_SET16(qpdpm_dscp_reg, qpdpm_dscp, prio, prio);
	MLX5_SET16(qpdpm_dscp_reg, qpdpm_dscp, e, 1);
	err = mlx5_core_access_reg(mdev, in, sz, out, sz, MLX5_REG_QPDPM, 0, 1);

out:
	kमुक्त(in);
	kमुक्त(out);
	वापस err;
पूर्ण

/* dscp2prio[i]: priority that dscp i mapped to */
#घोषणा MLX5E_SUPPORTED_DSCP 64
पूर्णांक mlx5_query_dscp2prio(काष्ठा mlx5_core_dev *mdev, u8 *dscp2prio)
अणु
	पूर्णांक sz = MLX5_ST_SZ_BYTES(qpdpm_reg);
	व्योम *qpdpm_dscp;
	व्योम *out;
	व्योम *in;
	पूर्णांक err;
	पूर्णांक i;

	in = kzalloc(sz, GFP_KERNEL);
	out = kzalloc(sz, GFP_KERNEL);
	अगर (!in || !out) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	MLX5_SET(qpdpm_reg, in, local_port, 1);
	err = mlx5_core_access_reg(mdev, in, sz, out, sz, MLX5_REG_QPDPM, 0, 0);
	अगर (err)
		जाओ out;

	क्रम (i = 0; i < (MLX5E_SUPPORTED_DSCP); i++) अणु
		qpdpm_dscp = MLX5_ADDR_OF(qpdpm_reg, out, dscp[i]);
		dscp2prio[i] = MLX5_GET16(qpdpm_dscp_reg, qpdpm_dscp, prio);
	पूर्ण

out:
	kमुक्त(in);
	kमुक्त(out);
	वापस err;
पूर्ण
