<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies, Ltd.  All rights reserved.
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

#समावेश <linux/export.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/vport.h>
#समावेश <linux/mlx5/eचयन.h>
#समावेश "mlx5_core.h"
#समावेश "sf/sf.h"

/* Mutex to hold जबतक enabling or disabling RoCE */
अटल DEFINE_MUTEX(mlx5_roce_en_lock);

u8 mlx5_query_vport_state(काष्ठा mlx5_core_dev *mdev, u8 opmod, u16 vport)
अणु
	u32 out[MLX5_ST_SZ_DW(query_vport_state_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(query_vport_state_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(query_vport_state_in, in, opcode,
		 MLX5_CMD_OP_QUERY_VPORT_STATE);
	MLX5_SET(query_vport_state_in, in, op_mod, opmod);
	MLX5_SET(query_vport_state_in, in, vport_number, vport);
	अगर (vport)
		MLX5_SET(query_vport_state_in, in, other_vport, 1);

	err = mlx5_cmd_exec_inout(mdev, query_vport_state, in, out);
	अगर (err)
		वापस 0;

	वापस MLX5_GET(query_vport_state_out, out, state);
पूर्ण

पूर्णांक mlx5_modअगरy_vport_admin_state(काष्ठा mlx5_core_dev *mdev, u8 opmod,
				  u16 vport, u8 other_vport, u8 state)
अणु
	u32 in[MLX5_ST_SZ_DW(modअगरy_vport_state_in)] = अणुपूर्ण;

	MLX5_SET(modअगरy_vport_state_in, in, opcode,
		 MLX5_CMD_OP_MODIFY_VPORT_STATE);
	MLX5_SET(modअगरy_vport_state_in, in, op_mod, opmod);
	MLX5_SET(modअगरy_vport_state_in, in, vport_number, vport);
	MLX5_SET(modअगरy_vport_state_in, in, other_vport, other_vport);
	MLX5_SET(modअगरy_vport_state_in, in, admin_state, state);

	वापस mlx5_cmd_exec_in(mdev, modअगरy_vport_state, in);
पूर्ण

अटल पूर्णांक mlx5_query_nic_vport_context(काष्ठा mlx5_core_dev *mdev, u16 vport,
					u32 *out)
अणु
	u32 in[MLX5_ST_SZ_DW(query_nic_vport_context_in)] = अणुपूर्ण;

	MLX5_SET(query_nic_vport_context_in, in, opcode,
		 MLX5_CMD_OP_QUERY_NIC_VPORT_CONTEXT);
	MLX5_SET(query_nic_vport_context_in, in, vport_number, vport);
	अगर (vport)
		MLX5_SET(query_nic_vport_context_in, in, other_vport, 1);

	वापस mlx5_cmd_exec_inout(mdev, query_nic_vport_context, in, out);
पूर्ण

पूर्णांक mlx5_query_nic_vport_min_अंतरभूत(काष्ठा mlx5_core_dev *mdev,
				    u16 vport, u8 *min_अंतरभूत)
अणु
	u32 out[MLX5_ST_SZ_DW(query_nic_vport_context_out)] = अणुपूर्ण;
	पूर्णांक err;

	err = mlx5_query_nic_vport_context(mdev, vport, out);
	अगर (!err)
		*min_अंतरभूत = MLX5_GET(query_nic_vport_context_out, out,
				       nic_vport_context.min_wqe_अंतरभूत_mode);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_nic_vport_min_अंतरभूत);

व्योम mlx5_query_min_अंतरभूत(काष्ठा mlx5_core_dev *mdev,
			   u8 *min_अंतरभूत_mode)
अणु
	चयन (MLX5_CAP_ETH(mdev, wqe_अंतरभूत_mode)) अणु
	हाल MLX5_CAP_INLINE_MODE_VPORT_CONTEXT:
		अगर (!mlx5_query_nic_vport_min_अंतरभूत(mdev, 0, min_अंतरभूत_mode))
			अवरोध;
		fallthrough;
	हाल MLX5_CAP_INLINE_MODE_L2:
		*min_अंतरभूत_mode = MLX5_INLINE_MODE_L2;
		अवरोध;
	हाल MLX5_CAP_INLINE_MODE_NOT_REQUIRED:
		*min_अंतरभूत_mode = MLX5_INLINE_MODE_NONE;
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_min_अंतरभूत);

पूर्णांक mlx5_modअगरy_nic_vport_min_अंतरभूत(काष्ठा mlx5_core_dev *mdev,
				     u16 vport, u8 min_अंतरभूत)
अणु
	u32 in[MLX5_ST_SZ_DW(modअगरy_nic_vport_context_in)] = अणुपूर्ण;
	व्योम *nic_vport_ctx;

	MLX5_SET(modअगरy_nic_vport_context_in, in,
		 field_select.min_अंतरभूत, 1);
	MLX5_SET(modअगरy_nic_vport_context_in, in, vport_number, vport);
	MLX5_SET(modअगरy_nic_vport_context_in, in, other_vport, 1);

	nic_vport_ctx = MLX5_ADDR_OF(modअगरy_nic_vport_context_in,
				     in, nic_vport_context);
	MLX5_SET(nic_vport_context, nic_vport_ctx,
		 min_wqe_अंतरभूत_mode, min_अंतरभूत);
	MLX5_SET(modअगरy_nic_vport_context_in, in, opcode,
		 MLX5_CMD_OP_MODIFY_NIC_VPORT_CONTEXT);

	वापस mlx5_cmd_exec_in(mdev, modअगरy_nic_vport_context, in);
पूर्ण

पूर्णांक mlx5_query_nic_vport_mac_address(काष्ठा mlx5_core_dev *mdev,
				     u16 vport, bool other, u8 *addr)
अणु
	u32 out[MLX5_ST_SZ_DW(query_nic_vport_context_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(query_nic_vport_context_in)] = अणुपूर्ण;
	u8 *out_addr;
	पूर्णांक err;

	out_addr = MLX5_ADDR_OF(query_nic_vport_context_out, out,
				nic_vport_context.permanent_address);

	MLX5_SET(query_nic_vport_context_in, in, opcode,
		 MLX5_CMD_OP_QUERY_NIC_VPORT_CONTEXT);
	MLX5_SET(query_nic_vport_context_in, in, vport_number, vport);
	MLX5_SET(query_nic_vport_context_in, in, other_vport, other);

	err = mlx5_cmd_exec_inout(mdev, query_nic_vport_context, in, out);
	अगर (!err)
		ether_addr_copy(addr, &out_addr[2]);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_nic_vport_mac_address);

पूर्णांक mlx5_query_mac_address(काष्ठा mlx5_core_dev *mdev, u8 *addr)
अणु
	वापस mlx5_query_nic_vport_mac_address(mdev, 0, false, addr);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_mac_address);

पूर्णांक mlx5_modअगरy_nic_vport_mac_address(काष्ठा mlx5_core_dev *mdev,
				      u16 vport, स्थिर u8 *addr)
अणु
	व्योम *in;
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(modअगरy_nic_vport_context_in);
	पूर्णांक err;
	व्योम *nic_vport_ctx;
	u8 *perm_mac;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(modअगरy_nic_vport_context_in, in,
		 field_select.permanent_address, 1);
	MLX5_SET(modअगरy_nic_vport_context_in, in, vport_number, vport);
	MLX5_SET(modअगरy_nic_vport_context_in, in, other_vport, 1);

	nic_vport_ctx = MLX5_ADDR_OF(modअगरy_nic_vport_context_in,
				     in, nic_vport_context);
	perm_mac = MLX5_ADDR_OF(nic_vport_context, nic_vport_ctx,
				permanent_address);

	ether_addr_copy(&perm_mac[2], addr);
	MLX5_SET(modअगरy_nic_vport_context_in, in, opcode,
		 MLX5_CMD_OP_MODIFY_NIC_VPORT_CONTEXT);

	err = mlx5_cmd_exec_in(mdev, modअगरy_nic_vport_context, in);

	kvमुक्त(in);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_modअगरy_nic_vport_mac_address);

पूर्णांक mlx5_query_nic_vport_mtu(काष्ठा mlx5_core_dev *mdev, u16 *mtu)
अणु
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(query_nic_vport_context_out);
	u32 *out;
	पूर्णांक err;

	out = kvzalloc(outlen, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	err = mlx5_query_nic_vport_context(mdev, 0, out);
	अगर (!err)
		*mtu = MLX5_GET(query_nic_vport_context_out, out,
				nic_vport_context.mtu);

	kvमुक्त(out);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_nic_vport_mtu);

पूर्णांक mlx5_modअगरy_nic_vport_mtu(काष्ठा mlx5_core_dev *mdev, u16 mtu)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(modअगरy_nic_vport_context_in);
	व्योम *in;
	पूर्णांक err;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(modअगरy_nic_vport_context_in, in, field_select.mtu, 1);
	MLX5_SET(modअगरy_nic_vport_context_in, in, nic_vport_context.mtu, mtu);
	MLX5_SET(modअगरy_nic_vport_context_in, in, opcode,
		 MLX5_CMD_OP_MODIFY_NIC_VPORT_CONTEXT);

	err = mlx5_cmd_exec_in(mdev, modअगरy_nic_vport_context, in);

	kvमुक्त(in);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_modअगरy_nic_vport_mtu);

पूर्णांक mlx5_query_nic_vport_mac_list(काष्ठा mlx5_core_dev *dev,
				  u16 vport,
				  क्रमागत mlx5_list_type list_type,
				  u8 addr_list[][ETH_ALEN],
				  पूर्णांक *list_size)
अणु
	u32 in[MLX5_ST_SZ_DW(query_nic_vport_context_in)] = अणु0पूर्ण;
	व्योम *nic_vport_ctx;
	पूर्णांक max_list_size;
	पूर्णांक req_list_size;
	पूर्णांक out_sz;
	व्योम *out;
	पूर्णांक err;
	पूर्णांक i;

	req_list_size = *list_size;

	max_list_size = list_type == MLX5_NVPRT_LIST_TYPE_UC ?
		1 << MLX5_CAP_GEN(dev, log_max_current_uc_list) :
		1 << MLX5_CAP_GEN(dev, log_max_current_mc_list);

	अगर (req_list_size > max_list_size) अणु
		mlx5_core_warn(dev, "Requested list size (%d) > (%d) max_list_size\n",
			       req_list_size, max_list_size);
		req_list_size = max_list_size;
	पूर्ण

	out_sz = MLX5_ST_SZ_BYTES(query_nic_vport_context_in) +
			req_list_size * MLX5_ST_SZ_BYTES(mac_address_layout);

	out = kzalloc(out_sz, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	MLX5_SET(query_nic_vport_context_in, in, opcode,
		 MLX5_CMD_OP_QUERY_NIC_VPORT_CONTEXT);
	MLX5_SET(query_nic_vport_context_in, in, allowed_list_type, list_type);
	MLX5_SET(query_nic_vport_context_in, in, vport_number, vport);
	MLX5_SET(query_nic_vport_context_in, in, other_vport, 1);

	err = mlx5_cmd_exec(dev, in, माप(in), out, out_sz);
	अगर (err)
		जाओ out;

	nic_vport_ctx = MLX5_ADDR_OF(query_nic_vport_context_out, out,
				     nic_vport_context);
	req_list_size = MLX5_GET(nic_vport_context, nic_vport_ctx,
				 allowed_list_size);

	*list_size = req_list_size;
	क्रम (i = 0; i < req_list_size; i++) अणु
		u8 *mac_addr = MLX5_ADDR_OF(nic_vport_context,
					nic_vport_ctx,
					current_uc_mac_address[i]) + 2;
		ether_addr_copy(addr_list[i], mac_addr);
	पूर्ण
out:
	kमुक्त(out);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_nic_vport_mac_list);

पूर्णांक mlx5_modअगरy_nic_vport_mac_list(काष्ठा mlx5_core_dev *dev,
				   क्रमागत mlx5_list_type list_type,
				   u8 addr_list[][ETH_ALEN],
				   पूर्णांक list_size)
अणु
	u32 out[MLX5_ST_SZ_DW(modअगरy_nic_vport_context_out)] = अणुपूर्ण;
	व्योम *nic_vport_ctx;
	पूर्णांक max_list_size;
	पूर्णांक in_sz;
	व्योम *in;
	पूर्णांक err;
	पूर्णांक i;

	max_list_size = list_type == MLX5_NVPRT_LIST_TYPE_UC ?
		 1 << MLX5_CAP_GEN(dev, log_max_current_uc_list) :
		 1 << MLX5_CAP_GEN(dev, log_max_current_mc_list);

	अगर (list_size > max_list_size)
		वापस -ENOSPC;

	in_sz = MLX5_ST_SZ_BYTES(modअगरy_nic_vport_context_in) +
		list_size * MLX5_ST_SZ_BYTES(mac_address_layout);

	in = kzalloc(in_sz, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(modअगरy_nic_vport_context_in, in, opcode,
		 MLX5_CMD_OP_MODIFY_NIC_VPORT_CONTEXT);
	MLX5_SET(modअगरy_nic_vport_context_in, in,
		 field_select.addresses_list, 1);

	nic_vport_ctx = MLX5_ADDR_OF(modअगरy_nic_vport_context_in, in,
				     nic_vport_context);

	MLX5_SET(nic_vport_context, nic_vport_ctx,
		 allowed_list_type, list_type);
	MLX5_SET(nic_vport_context, nic_vport_ctx,
		 allowed_list_size, list_size);

	क्रम (i = 0; i < list_size; i++) अणु
		u8 *curr_mac = MLX5_ADDR_OF(nic_vport_context,
					    nic_vport_ctx,
					    current_uc_mac_address[i]) + 2;
		ether_addr_copy(curr_mac, addr_list[i]);
	पूर्ण

	err = mlx5_cmd_exec(dev, in, in_sz, out, माप(out));
	kमुक्त(in);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_modअगरy_nic_vport_mac_list);

पूर्णांक mlx5_modअगरy_nic_vport_vlans(काष्ठा mlx5_core_dev *dev,
				u16 vlans[],
				पूर्णांक list_size)
अणु
	u32 out[MLX5_ST_SZ_DW(modअगरy_nic_vport_context_out)];
	व्योम *nic_vport_ctx;
	पूर्णांक max_list_size;
	पूर्णांक in_sz;
	व्योम *in;
	पूर्णांक err;
	पूर्णांक i;

	max_list_size = 1 << MLX5_CAP_GEN(dev, log_max_vlan_list);

	अगर (list_size > max_list_size)
		वापस -ENOSPC;

	in_sz = MLX5_ST_SZ_BYTES(modअगरy_nic_vport_context_in) +
		list_size * MLX5_ST_SZ_BYTES(vlan_layout);

	स_रखो(out, 0, माप(out));
	in = kzalloc(in_sz, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(modअगरy_nic_vport_context_in, in, opcode,
		 MLX5_CMD_OP_MODIFY_NIC_VPORT_CONTEXT);
	MLX5_SET(modअगरy_nic_vport_context_in, in,
		 field_select.addresses_list, 1);

	nic_vport_ctx = MLX5_ADDR_OF(modअगरy_nic_vport_context_in, in,
				     nic_vport_context);

	MLX5_SET(nic_vport_context, nic_vport_ctx,
		 allowed_list_type, MLX5_NVPRT_LIST_TYPE_VLAN);
	MLX5_SET(nic_vport_context, nic_vport_ctx,
		 allowed_list_size, list_size);

	क्रम (i = 0; i < list_size; i++) अणु
		व्योम *vlan_addr = MLX5_ADDR_OF(nic_vport_context,
					       nic_vport_ctx,
					       current_uc_mac_address[i]);
		MLX5_SET(vlan_layout, vlan_addr, vlan, vlans[i]);
	पूर्ण

	err = mlx5_cmd_exec(dev, in, in_sz, out, माप(out));
	kमुक्त(in);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_modअगरy_nic_vport_vlans);

पूर्णांक mlx5_query_nic_vport_प्रणाली_image_guid(काष्ठा mlx5_core_dev *mdev,
					   u64 *प्रणाली_image_guid)
अणु
	u32 *out;
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(query_nic_vport_context_out);

	out = kvzalloc(outlen, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	mlx5_query_nic_vport_context(mdev, 0, out);

	*प्रणाली_image_guid = MLX5_GET64(query_nic_vport_context_out, out,
					nic_vport_context.प्रणाली_image_guid);

	kvमुक्त(out);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_nic_vport_प्रणाली_image_guid);

पूर्णांक mlx5_query_nic_vport_node_guid(काष्ठा mlx5_core_dev *mdev, u64 *node_guid)
अणु
	u32 *out;
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(query_nic_vport_context_out);

	out = kvzalloc(outlen, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	mlx5_query_nic_vport_context(mdev, 0, out);

	*node_guid = MLX5_GET64(query_nic_vport_context_out, out,
				nic_vport_context.node_guid);

	kvमुक्त(out);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_nic_vport_node_guid);

पूर्णांक mlx5_modअगरy_nic_vport_node_guid(काष्ठा mlx5_core_dev *mdev,
				    u16 vport, u64 node_guid)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(modअगरy_nic_vport_context_in);
	व्योम *nic_vport_context;
	व्योम *in;
	पूर्णांक err;

	अगर (!MLX5_CAP_GEN(mdev, vport_group_manager))
		वापस -EACCES;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(modअगरy_nic_vport_context_in, in,
		 field_select.node_guid, 1);
	MLX5_SET(modअगरy_nic_vport_context_in, in, vport_number, vport);
	MLX5_SET(modअगरy_nic_vport_context_in, in, other_vport, 1);

	nic_vport_context = MLX5_ADDR_OF(modअगरy_nic_vport_context_in,
					 in, nic_vport_context);
	MLX5_SET64(nic_vport_context, nic_vport_context, node_guid, node_guid);
	MLX5_SET(modअगरy_nic_vport_context_in, in, opcode,
		 MLX5_CMD_OP_MODIFY_NIC_VPORT_CONTEXT);

	err = mlx5_cmd_exec_in(mdev, modअगरy_nic_vport_context, in);

	kvमुक्त(in);

	वापस err;
पूर्ण

पूर्णांक mlx5_query_nic_vport_qkey_viol_cntr(काष्ठा mlx5_core_dev *mdev,
					u16 *qkey_viol_cntr)
अणु
	u32 *out;
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(query_nic_vport_context_out);

	out = kvzalloc(outlen, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	mlx5_query_nic_vport_context(mdev, 0, out);

	*qkey_viol_cntr = MLX5_GET(query_nic_vport_context_out, out,
				   nic_vport_context.qkey_violation_counter);

	kvमुक्त(out);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_nic_vport_qkey_viol_cntr);

पूर्णांक mlx5_query_hca_vport_gid(काष्ठा mlx5_core_dev *dev, u8 other_vport,
			     u8 port_num, u16  vf_num, u16 gid_index,
			     जोड़ ib_gid *gid)
अणु
	पूर्णांक in_sz = MLX5_ST_SZ_BYTES(query_hca_vport_gid_in);
	पूर्णांक out_sz = MLX5_ST_SZ_BYTES(query_hca_vport_gid_out);
	पूर्णांक is_group_manager;
	व्योम *out = शून्य;
	व्योम *in = शून्य;
	जोड़ ib_gid *पंचांगp;
	पूर्णांक tbsz;
	पूर्णांक nout;
	पूर्णांक err;

	is_group_manager = MLX5_CAP_GEN(dev, vport_group_manager);
	tbsz = mlx5_get_gid_table_len(MLX5_CAP_GEN(dev, gid_table_size));
	mlx5_core_dbg(dev, "vf_num %d, index %d, gid_table_size %d\n",
		      vf_num, gid_index, tbsz);

	अगर (gid_index > tbsz && gid_index != 0xffff)
		वापस -EINVAL;

	अगर (gid_index == 0xffff)
		nout = tbsz;
	अन्यथा
		nout = 1;

	out_sz += nout * माप(*gid);

	in = kzalloc(in_sz, GFP_KERNEL);
	out = kzalloc(out_sz, GFP_KERNEL);
	अगर (!in || !out) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	MLX5_SET(query_hca_vport_gid_in, in, opcode, MLX5_CMD_OP_QUERY_HCA_VPORT_GID);
	अगर (other_vport) अणु
		अगर (is_group_manager) अणु
			MLX5_SET(query_hca_vport_gid_in, in, vport_number, vf_num);
			MLX5_SET(query_hca_vport_gid_in, in, other_vport, 1);
		पूर्ण अन्यथा अणु
			err = -EPERM;
			जाओ out;
		पूर्ण
	पूर्ण
	MLX5_SET(query_hca_vport_gid_in, in, gid_index, gid_index);

	अगर (MLX5_CAP_GEN(dev, num_ports) == 2)
		MLX5_SET(query_hca_vport_gid_in, in, port_num, port_num);

	err = mlx5_cmd_exec(dev, in, in_sz, out, out_sz);
	अगर (err)
		जाओ out;

	पंचांगp = out + MLX5_ST_SZ_BYTES(query_hca_vport_gid_out);
	gid->global.subnet_prefix = पंचांगp->global.subnet_prefix;
	gid->global.पूर्णांकerface_id = पंचांगp->global.पूर्णांकerface_id;

out:
	kमुक्त(in);
	kमुक्त(out);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_hca_vport_gid);

पूर्णांक mlx5_query_hca_vport_pkey(काष्ठा mlx5_core_dev *dev, u8 other_vport,
			      u8 port_num, u16 vf_num, u16 pkey_index,
			      u16 *pkey)
अणु
	पूर्णांक in_sz = MLX5_ST_SZ_BYTES(query_hca_vport_pkey_in);
	पूर्णांक out_sz = MLX5_ST_SZ_BYTES(query_hca_vport_pkey_out);
	पूर्णांक is_group_manager;
	व्योम *out = शून्य;
	व्योम *in = शून्य;
	व्योम *pkarr;
	पूर्णांक nout;
	पूर्णांक tbsz;
	पूर्णांक err;
	पूर्णांक i;

	is_group_manager = MLX5_CAP_GEN(dev, vport_group_manager);

	tbsz = mlx5_to_sw_pkey_sz(MLX5_CAP_GEN(dev, pkey_table_size));
	अगर (pkey_index > tbsz && pkey_index != 0xffff)
		वापस -EINVAL;

	अगर (pkey_index == 0xffff)
		nout = tbsz;
	अन्यथा
		nout = 1;

	out_sz += nout * MLX5_ST_SZ_BYTES(pkey);

	in = kzalloc(in_sz, GFP_KERNEL);
	out = kzalloc(out_sz, GFP_KERNEL);
	अगर (!in || !out) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	MLX5_SET(query_hca_vport_pkey_in, in, opcode, MLX5_CMD_OP_QUERY_HCA_VPORT_PKEY);
	अगर (other_vport) अणु
		अगर (is_group_manager) अणु
			MLX5_SET(query_hca_vport_pkey_in, in, vport_number, vf_num);
			MLX5_SET(query_hca_vport_pkey_in, in, other_vport, 1);
		पूर्ण अन्यथा अणु
			err = -EPERM;
			जाओ out;
		पूर्ण
	पूर्ण
	MLX5_SET(query_hca_vport_pkey_in, in, pkey_index, pkey_index);

	अगर (MLX5_CAP_GEN(dev, num_ports) == 2)
		MLX5_SET(query_hca_vport_pkey_in, in, port_num, port_num);

	err = mlx5_cmd_exec(dev, in, in_sz, out, out_sz);
	अगर (err)
		जाओ out;

	pkarr = MLX5_ADDR_OF(query_hca_vport_pkey_out, out, pkey);
	क्रम (i = 0; i < nout; i++, pkey++, pkarr += MLX5_ST_SZ_BYTES(pkey))
		*pkey = MLX5_GET_PR(pkey, pkarr, pkey);

out:
	kमुक्त(in);
	kमुक्त(out);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_hca_vport_pkey);

पूर्णांक mlx5_query_hca_vport_context(काष्ठा mlx5_core_dev *dev,
				 u8 other_vport, u8 port_num,
				 u16 vf_num,
				 काष्ठा mlx5_hca_vport_context *rep)
अणु
	पूर्णांक out_sz = MLX5_ST_SZ_BYTES(query_hca_vport_context_out);
	पूर्णांक in[MLX5_ST_SZ_DW(query_hca_vport_context_in)] = अणुपूर्ण;
	पूर्णांक is_group_manager;
	व्योम *out;
	व्योम *ctx;
	पूर्णांक err;

	is_group_manager = MLX5_CAP_GEN(dev, vport_group_manager);

	out = kzalloc(out_sz, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	MLX5_SET(query_hca_vport_context_in, in, opcode, MLX5_CMD_OP_QUERY_HCA_VPORT_CONTEXT);

	अगर (other_vport) अणु
		अगर (is_group_manager) अणु
			MLX5_SET(query_hca_vport_context_in, in, other_vport, 1);
			MLX5_SET(query_hca_vport_context_in, in, vport_number, vf_num);
		पूर्ण अन्यथा अणु
			err = -EPERM;
			जाओ ex;
		पूर्ण
	पूर्ण

	अगर (MLX5_CAP_GEN(dev, num_ports) == 2)
		MLX5_SET(query_hca_vport_context_in, in, port_num, port_num);

	err = mlx5_cmd_exec_inout(dev, query_hca_vport_context, in, out);
	अगर (err)
		जाओ ex;

	ctx = MLX5_ADDR_OF(query_hca_vport_context_out, out, hca_vport_context);
	rep->field_select = MLX5_GET_PR(hca_vport_context, ctx, field_select);
	rep->sm_virt_aware = MLX5_GET_PR(hca_vport_context, ctx, sm_virt_aware);
	rep->has_smi = MLX5_GET_PR(hca_vport_context, ctx, has_smi);
	rep->has_raw = MLX5_GET_PR(hca_vport_context, ctx, has_raw);
	rep->policy = MLX5_GET_PR(hca_vport_context, ctx, vport_state_policy);
	rep->phys_state = MLX5_GET_PR(hca_vport_context, ctx,
				      port_physical_state);
	rep->vport_state = MLX5_GET_PR(hca_vport_context, ctx, vport_state);
	rep->port_physical_state = MLX5_GET_PR(hca_vport_context, ctx,
					       port_physical_state);
	rep->port_guid = MLX5_GET64_PR(hca_vport_context, ctx, port_guid);
	rep->node_guid = MLX5_GET64_PR(hca_vport_context, ctx, node_guid);
	rep->cap_mask1 = MLX5_GET_PR(hca_vport_context, ctx, cap_mask1);
	rep->cap_mask1_perm = MLX5_GET_PR(hca_vport_context, ctx,
					  cap_mask1_field_select);
	rep->cap_mask2 = MLX5_GET_PR(hca_vport_context, ctx, cap_mask2);
	rep->cap_mask2_perm = MLX5_GET_PR(hca_vport_context, ctx,
					  cap_mask2_field_select);
	rep->lid = MLX5_GET_PR(hca_vport_context, ctx, lid);
	rep->init_type_reply = MLX5_GET_PR(hca_vport_context, ctx,
					   init_type_reply);
	rep->lmc = MLX5_GET_PR(hca_vport_context, ctx, lmc);
	rep->subnet_समयout = MLX5_GET_PR(hca_vport_context, ctx,
					  subnet_समयout);
	rep->sm_lid = MLX5_GET_PR(hca_vport_context, ctx, sm_lid);
	rep->sm_sl = MLX5_GET_PR(hca_vport_context, ctx, sm_sl);
	rep->qkey_violation_counter = MLX5_GET_PR(hca_vport_context, ctx,
						  qkey_violation_counter);
	rep->pkey_violation_counter = MLX5_GET_PR(hca_vport_context, ctx,
						  pkey_violation_counter);
	rep->grh_required = MLX5_GET_PR(hca_vport_context, ctx, grh_required);
	rep->sys_image_guid = MLX5_GET64_PR(hca_vport_context, ctx,
					    प्रणाली_image_guid);

ex:
	kमुक्त(out);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_hca_vport_context);

पूर्णांक mlx5_query_hca_vport_प्रणाली_image_guid(काष्ठा mlx5_core_dev *dev,
					   u64 *sys_image_guid)
अणु
	काष्ठा mlx5_hca_vport_context *rep;
	पूर्णांक err;

	rep = kzalloc(माप(*rep), GFP_KERNEL);
	अगर (!rep)
		वापस -ENOMEM;

	err = mlx5_query_hca_vport_context(dev, 0, 1, 0, rep);
	अगर (!err)
		*sys_image_guid = rep->sys_image_guid;

	kमुक्त(rep);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_hca_vport_प्रणाली_image_guid);

पूर्णांक mlx5_query_hca_vport_node_guid(काष्ठा mlx5_core_dev *dev,
				   u64 *node_guid)
अणु
	काष्ठा mlx5_hca_vport_context *rep;
	पूर्णांक err;

	rep = kzalloc(माप(*rep), GFP_KERNEL);
	अगर (!rep)
		वापस -ENOMEM;

	err = mlx5_query_hca_vport_context(dev, 0, 1, 0, rep);
	अगर (!err)
		*node_guid = rep->node_guid;

	kमुक्त(rep);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_hca_vport_node_guid);

पूर्णांक mlx5_query_nic_vport_promisc(काष्ठा mlx5_core_dev *mdev,
				 u16 vport,
				 पूर्णांक *promisc_uc,
				 पूर्णांक *promisc_mc,
				 पूर्णांक *promisc_all)
अणु
	u32 *out;
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(query_nic_vport_context_out);
	पूर्णांक err;

	out = kzalloc(outlen, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	err = mlx5_query_nic_vport_context(mdev, vport, out);
	अगर (err)
		जाओ out;

	*promisc_uc = MLX5_GET(query_nic_vport_context_out, out,
			       nic_vport_context.promisc_uc);
	*promisc_mc = MLX5_GET(query_nic_vport_context_out, out,
			       nic_vport_context.promisc_mc);
	*promisc_all = MLX5_GET(query_nic_vport_context_out, out,
				nic_vport_context.promisc_all);

out:
	kमुक्त(out);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_nic_vport_promisc);

पूर्णांक mlx5_modअगरy_nic_vport_promisc(काष्ठा mlx5_core_dev *mdev,
				  पूर्णांक promisc_uc,
				  पूर्णांक promisc_mc,
				  पूर्णांक promisc_all)
अणु
	व्योम *in;
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(modअगरy_nic_vport_context_in);
	पूर्णांक err;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(modअगरy_nic_vport_context_in, in, field_select.promisc, 1);
	MLX5_SET(modअगरy_nic_vport_context_in, in,
		 nic_vport_context.promisc_uc, promisc_uc);
	MLX5_SET(modअगरy_nic_vport_context_in, in,
		 nic_vport_context.promisc_mc, promisc_mc);
	MLX5_SET(modअगरy_nic_vport_context_in, in,
		 nic_vport_context.promisc_all, promisc_all);
	MLX5_SET(modअगरy_nic_vport_context_in, in, opcode,
		 MLX5_CMD_OP_MODIFY_NIC_VPORT_CONTEXT);

	err = mlx5_cmd_exec_in(mdev, modअगरy_nic_vport_context, in);

	kvमुक्त(in);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_modअगरy_nic_vport_promisc);

क्रमागत अणु
	UC_LOCAL_LB,
	MC_LOCAL_LB
पूर्ण;

पूर्णांक mlx5_nic_vport_update_local_lb(काष्ठा mlx5_core_dev *mdev, bool enable)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(modअगरy_nic_vport_context_in);
	व्योम *in;
	पूर्णांक err;

	अगर (!MLX5_CAP_GEN(mdev, disable_local_lb_mc) &&
	    !MLX5_CAP_GEN(mdev, disable_local_lb_uc))
		वापस 0;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(modअगरy_nic_vport_context_in, in,
		 nic_vport_context.disable_mc_local_lb, !enable);
	MLX5_SET(modअगरy_nic_vport_context_in, in,
		 nic_vport_context.disable_uc_local_lb, !enable);

	अगर (MLX5_CAP_GEN(mdev, disable_local_lb_mc))
		MLX5_SET(modअगरy_nic_vport_context_in, in,
			 field_select.disable_mc_local_lb, 1);

	अगर (MLX5_CAP_GEN(mdev, disable_local_lb_uc))
		MLX5_SET(modअगरy_nic_vport_context_in, in,
			 field_select.disable_uc_local_lb, 1);
	MLX5_SET(modअगरy_nic_vport_context_in, in, opcode,
		 MLX5_CMD_OP_MODIFY_NIC_VPORT_CONTEXT);

	err = mlx5_cmd_exec_in(mdev, modअगरy_nic_vport_context, in);

	अगर (!err)
		mlx5_core_dbg(mdev, "%s local_lb\n",
			      enable ? "enable" : "disable");

	kvमुक्त(in);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_nic_vport_update_local_lb);

पूर्णांक mlx5_nic_vport_query_local_lb(काष्ठा mlx5_core_dev *mdev, bool *status)
अणु
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(query_nic_vport_context_out);
	u32 *out;
	पूर्णांक value;
	पूर्णांक err;

	out = kzalloc(outlen, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	err = mlx5_query_nic_vport_context(mdev, 0, out);
	अगर (err)
		जाओ out;

	value = MLX5_GET(query_nic_vport_context_out, out,
			 nic_vport_context.disable_mc_local_lb) << MC_LOCAL_LB;

	value |= MLX5_GET(query_nic_vport_context_out, out,
			  nic_vport_context.disable_uc_local_lb) << UC_LOCAL_LB;

	*status = !value;

out:
	kमुक्त(out);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_nic_vport_query_local_lb);

क्रमागत mlx5_vport_roce_state अणु
	MLX5_VPORT_ROCE_DISABLED = 0,
	MLX5_VPORT_ROCE_ENABLED  = 1,
पूर्ण;

अटल पूर्णांक mlx5_nic_vport_update_roce_state(काष्ठा mlx5_core_dev *mdev,
					    क्रमागत mlx5_vport_roce_state state)
अणु
	व्योम *in;
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(modअगरy_nic_vport_context_in);
	पूर्णांक err;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(modअगरy_nic_vport_context_in, in, field_select.roce_en, 1);
	MLX5_SET(modअगरy_nic_vport_context_in, in, nic_vport_context.roce_en,
		 state);
	MLX5_SET(modअगरy_nic_vport_context_in, in, opcode,
		 MLX5_CMD_OP_MODIFY_NIC_VPORT_CONTEXT);

	err = mlx5_cmd_exec_in(mdev, modअगरy_nic_vport_context, in);

	kvमुक्त(in);

	वापस err;
पूर्ण

पूर्णांक mlx5_nic_vport_enable_roce(काष्ठा mlx5_core_dev *mdev)
अणु
	पूर्णांक err = 0;

	mutex_lock(&mlx5_roce_en_lock);
	अगर (!mdev->roce.roce_en)
		err = mlx5_nic_vport_update_roce_state(mdev, MLX5_VPORT_ROCE_ENABLED);

	अगर (!err)
		mdev->roce.roce_en++;
	mutex_unlock(&mlx5_roce_en_lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_nic_vport_enable_roce);

पूर्णांक mlx5_nic_vport_disable_roce(काष्ठा mlx5_core_dev *mdev)
अणु
	पूर्णांक err = 0;

	mutex_lock(&mlx5_roce_en_lock);
	अगर (mdev->roce.roce_en) अणु
		mdev->roce.roce_en--;
		अगर (mdev->roce.roce_en == 0)
			err = mlx5_nic_vport_update_roce_state(mdev, MLX5_VPORT_ROCE_DISABLED);

		अगर (err)
			mdev->roce.roce_en++;
	पूर्ण
	mutex_unlock(&mlx5_roce_en_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_nic_vport_disable_roce);

पूर्णांक mlx5_core_query_vport_counter(काष्ठा mlx5_core_dev *dev, u8 other_vport,
				  पूर्णांक vf, u8 port_num, व्योम *out)
अणु
	पूर्णांक in_sz = MLX5_ST_SZ_BYTES(query_vport_counter_in);
	पूर्णांक is_group_manager;
	व्योम *in;
	पूर्णांक err;

	is_group_manager = MLX5_CAP_GEN(dev, vport_group_manager);
	in = kvzalloc(in_sz, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		वापस err;
	पूर्ण

	MLX5_SET(query_vport_counter_in, in, opcode,
		 MLX5_CMD_OP_QUERY_VPORT_COUNTER);
	अगर (other_vport) अणु
		अगर (is_group_manager) अणु
			MLX5_SET(query_vport_counter_in, in, other_vport, 1);
			MLX5_SET(query_vport_counter_in, in, vport_number, vf + 1);
		पूर्ण अन्यथा अणु
			err = -EPERM;
			जाओ मुक्त;
		पूर्ण
	पूर्ण
	अगर (MLX5_CAP_GEN(dev, num_ports) == 2)
		MLX5_SET(query_vport_counter_in, in, port_num, port_num);

	err = mlx5_cmd_exec_inout(dev, query_vport_counter, in, out);
मुक्त:
	kvमुक्त(in);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_core_query_vport_counter);

पूर्णांक mlx5_query_vport_करोwn_stats(काष्ठा mlx5_core_dev *mdev, u16 vport,
				u8 other_vport, u64 *rx_discard_vport_करोwn,
				u64 *tx_discard_vport_करोwn)
अणु
	u32 out[MLX5_ST_SZ_DW(query_vnic_env_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(query_vnic_env_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(query_vnic_env_in, in, opcode,
		 MLX5_CMD_OP_QUERY_VNIC_ENV);
	MLX5_SET(query_vnic_env_in, in, op_mod, 0);
	MLX5_SET(query_vnic_env_in, in, vport_number, vport);
	MLX5_SET(query_vnic_env_in, in, other_vport, other_vport);

	err = mlx5_cmd_exec_inout(mdev, query_vnic_env, in, out);
	अगर (err)
		वापस err;

	*rx_discard_vport_करोwn = MLX5_GET64(query_vnic_env_out, out,
					    vport_env.receive_discard_vport_करोwn);
	*tx_discard_vport_करोwn = MLX5_GET64(query_vnic_env_out, out,
					    vport_env.transmit_discard_vport_करोwn);
	वापस 0;
पूर्ण

पूर्णांक mlx5_core_modअगरy_hca_vport_context(काष्ठा mlx5_core_dev *dev,
				       u8 other_vport, u8 port_num,
				       पूर्णांक vf,
				       काष्ठा mlx5_hca_vport_context *req)
अणु
	पूर्णांक in_sz = MLX5_ST_SZ_BYTES(modअगरy_hca_vport_context_in);
	पूर्णांक is_group_manager;
	व्योम *ctx;
	व्योम *in;
	पूर्णांक err;

	mlx5_core_dbg(dev, "vf %d\n", vf);
	is_group_manager = MLX5_CAP_GEN(dev, vport_group_manager);
	in = kzalloc(in_sz, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(modअगरy_hca_vport_context_in, in, opcode, MLX5_CMD_OP_MODIFY_HCA_VPORT_CONTEXT);
	अगर (other_vport) अणु
		अगर (is_group_manager) अणु
			MLX5_SET(modअगरy_hca_vport_context_in, in, other_vport, 1);
			MLX5_SET(modअगरy_hca_vport_context_in, in, vport_number, vf);
		पूर्ण अन्यथा अणु
			err = -EPERM;
			जाओ ex;
		पूर्ण
	पूर्ण

	अगर (MLX5_CAP_GEN(dev, num_ports) > 1)
		MLX5_SET(modअगरy_hca_vport_context_in, in, port_num, port_num);

	ctx = MLX5_ADDR_OF(modअगरy_hca_vport_context_in, in, hca_vport_context);
	MLX5_SET(hca_vport_context, ctx, field_select, req->field_select);
	अगर (req->field_select & MLX5_HCA_VPORT_SEL_STATE_POLICY)
		MLX5_SET(hca_vport_context, ctx, vport_state_policy,
			 req->policy);
	अगर (req->field_select & MLX5_HCA_VPORT_SEL_PORT_GUID)
		MLX5_SET64(hca_vport_context, ctx, port_guid, req->port_guid);
	अगर (req->field_select & MLX5_HCA_VPORT_SEL_NODE_GUID)
		MLX5_SET64(hca_vport_context, ctx, node_guid, req->node_guid);
	MLX5_SET(hca_vport_context, ctx, cap_mask1, req->cap_mask1);
	MLX5_SET(hca_vport_context, ctx, cap_mask1_field_select,
		 req->cap_mask1_perm);
	err = mlx5_cmd_exec_in(dev, modअगरy_hca_vport_context, in);
ex:
	kमुक्त(in);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_core_modअगरy_hca_vport_context);

पूर्णांक mlx5_nic_vport_affiliate_multiport(काष्ठा mlx5_core_dev *master_mdev,
				       काष्ठा mlx5_core_dev *port_mdev)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(modअगरy_nic_vport_context_in);
	व्योम *in;
	पूर्णांक err;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	err = mlx5_nic_vport_enable_roce(port_mdev);
	अगर (err)
		जाओ मुक्त;

	MLX5_SET(modअगरy_nic_vport_context_in, in, field_select.affiliation, 1);
	MLX5_SET(modअगरy_nic_vport_context_in, in,
		 nic_vport_context.affiliated_vhca_id,
		 MLX5_CAP_GEN(master_mdev, vhca_id));
	MLX5_SET(modअगरy_nic_vport_context_in, in,
		 nic_vport_context.affiliation_criteria,
		 MLX5_CAP_GEN(port_mdev, affiliate_nic_vport_criteria));
	MLX5_SET(modअगरy_nic_vport_context_in, in, opcode,
		 MLX5_CMD_OP_MODIFY_NIC_VPORT_CONTEXT);

	err = mlx5_cmd_exec_in(port_mdev, modअगरy_nic_vport_context, in);
	अगर (err)
		mlx5_nic_vport_disable_roce(port_mdev);

मुक्त:
	kvमुक्त(in);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_nic_vport_affiliate_multiport);

पूर्णांक mlx5_nic_vport_unaffiliate_multiport(काष्ठा mlx5_core_dev *port_mdev)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(modअगरy_nic_vport_context_in);
	व्योम *in;
	पूर्णांक err;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(modअगरy_nic_vport_context_in, in, field_select.affiliation, 1);
	MLX5_SET(modअगरy_nic_vport_context_in, in,
		 nic_vport_context.affiliated_vhca_id, 0);
	MLX5_SET(modअगरy_nic_vport_context_in, in,
		 nic_vport_context.affiliation_criteria, 0);
	MLX5_SET(modअगरy_nic_vport_context_in, in, opcode,
		 MLX5_CMD_OP_MODIFY_NIC_VPORT_CONTEXT);

	err = mlx5_cmd_exec_in(port_mdev, modअगरy_nic_vport_context, in);
	अगर (!err)
		mlx5_nic_vport_disable_roce(port_mdev);

	kvमुक्त(in);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_nic_vport_unaffiliate_multiport);

u64 mlx5_query_nic_प्रणाली_image_guid(काष्ठा mlx5_core_dev *mdev)
अणु
	पूर्णांक port_type_cap = MLX5_CAP_GEN(mdev, port_type);
	u64 पंचांगp = 0;

	अगर (mdev->sys_image_guid)
		वापस mdev->sys_image_guid;

	अगर (port_type_cap == MLX5_CAP_PORT_TYPE_ETH)
		mlx5_query_nic_vport_प्रणाली_image_guid(mdev, &पंचांगp);
	अन्यथा
		mlx5_query_hca_vport_प्रणाली_image_guid(mdev, &पंचांगp);

	mdev->sys_image_guid = पंचांगp;

	वापस पंचांगp;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_query_nic_प्रणाली_image_guid);

पूर्णांक mlx5_vport_get_other_func_cap(काष्ठा mlx5_core_dev *dev, u16 function_id, व्योम *out)
अणु
	u16 opmod = (MLX5_CAP_GENERAL << 1) | (HCA_CAP_OPMOD_GET_MAX & 0x01);
	u8 in[MLX5_ST_SZ_BYTES(query_hca_cap_in)] = अणुपूर्ण;

	MLX5_SET(query_hca_cap_in, in, opcode, MLX5_CMD_OP_QUERY_HCA_CAP);
	MLX5_SET(query_hca_cap_in, in, op_mod, opmod);
	MLX5_SET(query_hca_cap_in, in, function_id, function_id);
	MLX5_SET(query_hca_cap_in, in, other_function, true);
	वापस mlx5_cmd_exec_inout(dev, query_hca_cap, in, out);
पूर्ण
