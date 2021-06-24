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

#समावेश <linux/mlx5/vport.h>
#समावेश <rdma/ib_mad.h>
#समावेश <rdma/ib_smi.h>
#समावेश <rdma/ib_pma.h>
#समावेश "mlx5_ib.h"
#समावेश "cmd.h"

क्रमागत अणु
	MLX5_IB_VENDOR_CLASS1 = 0x9,
	MLX5_IB_VENDOR_CLASS2 = 0xa
पूर्ण;

अटल bool can_करो_mad_अगरc(काष्ठा mlx5_ib_dev *dev, u32 port_num,
			   काष्ठा ib_mad *in_mad)
अणु
	अगर (in_mad->mad_hdr.mgmt_class != IB_MGMT_CLASS_SUBN_LID_ROUTED &&
	    in_mad->mad_hdr.mgmt_class != IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE)
		वापस true;
	वापस dev->port_caps[port_num - 1].has_smi;
पूर्ण

अटल पूर्णांक mlx5_MAD_IFC(काष्ठा mlx5_ib_dev *dev, पूर्णांक ignore_mkey,
			पूर्णांक ignore_bkey, u32 port, स्थिर काष्ठा ib_wc *in_wc,
			स्थिर काष्ठा ib_grh *in_grh, स्थिर व्योम *in_mad,
			व्योम *response_mad)
अणु
	u8 op_modअगरier = 0;

	अगर (!can_करो_mad_अगरc(dev, port, (काष्ठा ib_mad *)in_mad))
		वापस -EPERM;

	/* Key check traps can't be generated unless we have in_wc to
	 * tell us where to send the trap.
	 */
	अगर (ignore_mkey || !in_wc)
		op_modअगरier |= 0x1;
	अगर (ignore_bkey || !in_wc)
		op_modअगरier |= 0x2;

	वापस mlx5_cmd_mad_अगरc(dev->mdev, in_mad, response_mad, op_modअगरier,
				port);
पूर्ण

अटल व्योम pma_cnt_ext_assign(काष्ठा ib_pma_portcounters_ext *pma_cnt_ext,
			       व्योम *out)
अणु
#घोषणा MLX5_SUM_CNT(p, cntr1, cntr2)	\
	(MLX5_GET64(query_vport_counter_out, p, cntr1) + \
	MLX5_GET64(query_vport_counter_out, p, cntr2))

	pma_cnt_ext->port_xmit_data =
		cpu_to_be64(MLX5_SUM_CNT(out, transmitted_ib_unicast.octets,
					 transmitted_ib_multicast.octets) >> 2);
	pma_cnt_ext->port_rcv_data =
		cpu_to_be64(MLX5_SUM_CNT(out, received_ib_unicast.octets,
					 received_ib_multicast.octets) >> 2);
	pma_cnt_ext->port_xmit_packets =
		cpu_to_be64(MLX5_SUM_CNT(out, transmitted_ib_unicast.packets,
					 transmitted_ib_multicast.packets));
	pma_cnt_ext->port_rcv_packets =
		cpu_to_be64(MLX5_SUM_CNT(out, received_ib_unicast.packets,
					 received_ib_multicast.packets));
	pma_cnt_ext->port_unicast_xmit_packets =
		MLX5_GET64_BE(query_vport_counter_out,
			      out, transmitted_ib_unicast.packets);
	pma_cnt_ext->port_unicast_rcv_packets =
		MLX5_GET64_BE(query_vport_counter_out,
			      out, received_ib_unicast.packets);
	pma_cnt_ext->port_multicast_xmit_packets =
		MLX5_GET64_BE(query_vport_counter_out,
			      out, transmitted_ib_multicast.packets);
	pma_cnt_ext->port_multicast_rcv_packets =
		MLX5_GET64_BE(query_vport_counter_out,
			      out, received_ib_multicast.packets);
पूर्ण

अटल व्योम pma_cnt_assign(काष्ठा ib_pma_portcounters *pma_cnt,
			   व्योम *out)
अणु
	/* Traffic counters will be reported in
	 * their 64bit क्रमm via ib_pma_portcounters_ext by शेष.
	 */
	व्योम *out_pma = MLX5_ADDR_OF(ppcnt_reg, out,
				     counter_set);

#घोषणा MLX5_ASSIGN_PMA_CNTR(counter_var, counter_name)	अणु		\
	counter_var = MLX5_GET_BE(typeof(counter_var),			\
				  ib_port_cntrs_grp_data_layout,	\
				  out_pma, counter_name);		\
	पूर्ण

	MLX5_ASSIGN_PMA_CNTR(pma_cnt->symbol_error_counter,
			     symbol_error_counter);
	MLX5_ASSIGN_PMA_CNTR(pma_cnt->link_error_recovery_counter,
			     link_error_recovery_counter);
	MLX5_ASSIGN_PMA_CNTR(pma_cnt->link_करोwned_counter,
			     link_करोwned_counter);
	MLX5_ASSIGN_PMA_CNTR(pma_cnt->port_rcv_errors,
			     port_rcv_errors);
	MLX5_ASSIGN_PMA_CNTR(pma_cnt->port_rcv_remphys_errors,
			     port_rcv_remote_physical_errors);
	MLX5_ASSIGN_PMA_CNTR(pma_cnt->port_rcv_चयन_relay_errors,
			     port_rcv_चयन_relay_errors);
	MLX5_ASSIGN_PMA_CNTR(pma_cnt->port_xmit_discards,
			     port_xmit_discards);
	MLX5_ASSIGN_PMA_CNTR(pma_cnt->port_xmit_स्थिरraपूर्णांक_errors,
			     port_xmit_स्थिरraपूर्णांक_errors);
	MLX5_ASSIGN_PMA_CNTR(pma_cnt->port_xmit_रुको,
			     port_xmit_रुको);
	MLX5_ASSIGN_PMA_CNTR(pma_cnt->port_rcv_स्थिरraपूर्णांक_errors,
			     port_rcv_स्थिरraपूर्णांक_errors);
	MLX5_ASSIGN_PMA_CNTR(pma_cnt->link_overrun_errors,
			     link_overrun_errors);
	MLX5_ASSIGN_PMA_CNTR(pma_cnt->vl15_dropped,
			     vl_15_dropped);
पूर्ण

अटल पूर्णांक process_pma_cmd(काष्ठा mlx5_ib_dev *dev, u32 port_num,
			   स्थिर काष्ठा ib_mad *in_mad, काष्ठा ib_mad *out_mad)
अणु
	काष्ठा mlx5_core_dev *mdev;
	bool native_port = true;
	u32 mdev_port_num;
	व्योम *out_cnt;
	पूर्णांक err;

	mdev = mlx5_ib_get_native_port_mdev(dev, port_num, &mdev_port_num);
	अगर (!mdev) अणु
		/* Fail to get the native port, likely due to 2nd port is still
		 * unaffiliated. In such हाल शेष to 1st port and attached
		 * PF device.
		 */
		native_port = false;
		mdev = dev->mdev;
		mdev_port_num = 1;
	पूर्ण
	/* Declaring support of extended counters */
	अगर (in_mad->mad_hdr.attr_id == IB_PMA_CLASS_PORT_INFO) अणु
		काष्ठा ib_class_port_info cpi = अणुपूर्ण;

		cpi.capability_mask = IB_PMA_CLASS_CAP_EXT_WIDTH;
		स_नकल((out_mad->data + 40), &cpi, माप(cpi));
		err = IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_REPLY;
		जाओ करोne;
	पूर्ण

	अगर (in_mad->mad_hdr.attr_id == IB_PMA_PORT_COUNTERS_EXT) अणु
		काष्ठा ib_pma_portcounters_ext *pma_cnt_ext =
			(काष्ठा ib_pma_portcounters_ext *)(out_mad->data + 40);
		पूर्णांक sz = MLX5_ST_SZ_BYTES(query_vport_counter_out);

		out_cnt = kvzalloc(sz, GFP_KERNEL);
		अगर (!out_cnt) अणु
			err = IB_MAD_RESULT_FAILURE;
			जाओ करोne;
		पूर्ण

		err = mlx5_core_query_vport_counter(mdev, 0, 0, mdev_port_num,
						    out_cnt);
		अगर (!err)
			pma_cnt_ext_assign(pma_cnt_ext, out_cnt);
	पूर्ण अन्यथा अणु
		काष्ठा ib_pma_portcounters *pma_cnt =
			(काष्ठा ib_pma_portcounters *)(out_mad->data + 40);
		पूर्णांक sz = MLX5_ST_SZ_BYTES(ppcnt_reg);

		out_cnt = kvzalloc(sz, GFP_KERNEL);
		अगर (!out_cnt) अणु
			err = IB_MAD_RESULT_FAILURE;
			जाओ करोne;
		पूर्ण

		err = mlx5_core_query_ib_ppcnt(mdev, mdev_port_num,
					       out_cnt, sz);
		अगर (!err)
			pma_cnt_assign(pma_cnt, out_cnt);
	पूर्ण
	kvमुक्त(out_cnt);
	err = err ? IB_MAD_RESULT_FAILURE :
		    IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_REPLY;
करोne:
	अगर (native_port)
		mlx5_ib_put_native_port_mdev(dev, port_num);
	वापस err;
पूर्ण

पूर्णांक mlx5_ib_process_mad(काष्ठा ib_device *ibdev, पूर्णांक mad_flags, u32 port_num,
			स्थिर काष्ठा ib_wc *in_wc, स्थिर काष्ठा ib_grh *in_grh,
			स्थिर काष्ठा ib_mad *in, काष्ठा ib_mad *out,
			माप_प्रकार *out_mad_size, u16 *out_mad_pkey_index)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);
	u8 mgmt_class = in->mad_hdr.mgmt_class;
	u8 method = in->mad_hdr.method;
	u16 slid;
	पूर्णांक err;

	slid = in_wc ? ib_lid_cpu16(in_wc->slid) :
		       be16_to_cpu(IB_LID_PERMISSIVE);

	अगर (method == IB_MGMT_METHOD_TRAP && !slid)
		वापस IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_CONSUMED;

	चयन (mgmt_class) अणु
	हाल IB_MGMT_CLASS_SUBN_LID_ROUTED:
	हाल IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE: अणु
		अगर (method != IB_MGMT_METHOD_GET &&
		    method != IB_MGMT_METHOD_SET &&
		    method != IB_MGMT_METHOD_TRAP_REPRESS)
			वापस IB_MAD_RESULT_SUCCESS;

		/* Don't process SMInfo queries -- the SMA can't handle them.
		 */
		अगर (in->mad_hdr.attr_id == IB_SMP_ATTR_SM_INFO)
			वापस IB_MAD_RESULT_SUCCESS;
	पूर्ण अवरोध;
	हाल IB_MGMT_CLASS_PERF_MGMT:
		अगर (MLX5_CAP_GEN(dev->mdev, vport_counters) &&
		    method == IB_MGMT_METHOD_GET)
			वापस process_pma_cmd(dev, port_num, in, out);
		fallthrough;
	हाल MLX5_IB_VENDOR_CLASS1:
	हाल MLX5_IB_VENDOR_CLASS2:
	हाल IB_MGMT_CLASS_CONG_MGMT: अणु
		अगर (method != IB_MGMT_METHOD_GET &&
		    method != IB_MGMT_METHOD_SET)
			वापस IB_MAD_RESULT_SUCCESS;
	पूर्ण अवरोध;
	शेष:
		वापस IB_MAD_RESULT_SUCCESS;
	पूर्ण

	err = mlx5_MAD_IFC(to_mdev(ibdev), mad_flags & IB_MAD_IGNORE_MKEY,
			   mad_flags & IB_MAD_IGNORE_BKEY, port_num, in_wc,
			   in_grh, in, out);
	अगर (err)
		वापस IB_MAD_RESULT_FAILURE;

	/* set वापस bit in status of directed route responses */
	अगर (mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE)
		out->mad_hdr.status |= cpu_to_be16(1 << 15);

	अगर (method == IB_MGMT_METHOD_TRAP_REPRESS)
		/* no response क्रम trap repress */
		वापस IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_CONSUMED;

	वापस IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_REPLY;
पूर्ण

पूर्णांक mlx5_query_ext_port_caps(काष्ठा mlx5_ib_dev *dev, अचिन्हित पूर्णांक port)
अणु
	काष्ठा ib_smp *in_mad  = शून्य;
	काष्ठा ib_smp *out_mad = शून्य;
	पूर्णांक err = -ENOMEM;
	u16 packet_error;

	in_mad  = kzalloc(माप(*in_mad), GFP_KERNEL);
	out_mad = kदो_स्मृति(माप(*out_mad), GFP_KERNEL);
	अगर (!in_mad || !out_mad)
		जाओ out;

	init_query_mad(in_mad);
	in_mad->attr_id = MLX5_ATTR_EXTENDED_PORT_INFO;
	in_mad->attr_mod = cpu_to_be32(port);

	err = mlx5_MAD_IFC(dev, 1, 1, 1, शून्य, शून्य, in_mad, out_mad);

	packet_error = be16_to_cpu(out_mad->status);

	dev->port_caps[port - 1].ext_port_cap = (!err && !packet_error) ?
		MLX_EXT_PORT_CAP_FLAG_EXTENDED_PORT_INFO : 0;

out:
	kमुक्त(in_mad);
	kमुक्त(out_mad);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_query_mad_अगरc_smp_attr_node_info(काष्ठा ib_device *ibdev,
						 काष्ठा ib_smp *out_mad)
अणु
	काष्ठा ib_smp *in_mad = शून्य;
	पूर्णांक err = -ENOMEM;

	in_mad = kzalloc(माप(*in_mad), GFP_KERNEL);
	अगर (!in_mad)
		वापस -ENOMEM;

	init_query_mad(in_mad);
	in_mad->attr_id = IB_SMP_ATTR_NODE_INFO;

	err = mlx5_MAD_IFC(to_mdev(ibdev), 1, 1, 1, शून्य, शून्य, in_mad,
			   out_mad);

	kमुक्त(in_mad);
	वापस err;
पूर्ण

पूर्णांक mlx5_query_mad_अगरc_प्रणाली_image_guid(काष्ठा ib_device *ibdev,
					 __be64 *sys_image_guid)
अणु
	काष्ठा ib_smp *out_mad = शून्य;
	पूर्णांक err = -ENOMEM;

	out_mad = kदो_स्मृति(माप(*out_mad), GFP_KERNEL);
	अगर (!out_mad)
		वापस -ENOMEM;

	err = mlx5_query_mad_अगरc_smp_attr_node_info(ibdev, out_mad);
	अगर (err)
		जाओ out;

	स_नकल(sys_image_guid, out_mad->data + 4, 8);

out:
	kमुक्त(out_mad);

	वापस err;
पूर्ण

पूर्णांक mlx5_query_mad_अगरc_max_pkeys(काष्ठा ib_device *ibdev,
				 u16 *max_pkeys)
अणु
	काष्ठा ib_smp *out_mad = शून्य;
	पूर्णांक err = -ENOMEM;

	out_mad = kदो_स्मृति(माप(*out_mad), GFP_KERNEL);
	अगर (!out_mad)
		वापस -ENOMEM;

	err = mlx5_query_mad_अगरc_smp_attr_node_info(ibdev, out_mad);
	अगर (err)
		जाओ out;

	*max_pkeys = be16_to_cpup((__be16 *)(out_mad->data + 28));

out:
	kमुक्त(out_mad);

	वापस err;
पूर्ण

पूर्णांक mlx5_query_mad_अगरc_venकरोr_id(काष्ठा ib_device *ibdev,
				 u32 *venकरोr_id)
अणु
	काष्ठा ib_smp *out_mad = शून्य;
	पूर्णांक err = -ENOMEM;

	out_mad = kदो_स्मृति(माप(*out_mad), GFP_KERNEL);
	अगर (!out_mad)
		वापस -ENOMEM;

	err = mlx5_query_mad_अगरc_smp_attr_node_info(ibdev, out_mad);
	अगर (err)
		जाओ out;

	*venकरोr_id = be32_to_cpup((__be32 *)(out_mad->data + 36)) & 0xffff;

out:
	kमुक्त(out_mad);

	वापस err;
पूर्ण

पूर्णांक mlx5_query_mad_अगरc_node_desc(काष्ठा mlx5_ib_dev *dev, अक्षर *node_desc)
अणु
	काष्ठा ib_smp *in_mad  = शून्य;
	काष्ठा ib_smp *out_mad = शून्य;
	पूर्णांक err = -ENOMEM;

	in_mad  = kzalloc(माप(*in_mad), GFP_KERNEL);
	out_mad = kदो_स्मृति(माप(*out_mad), GFP_KERNEL);
	अगर (!in_mad || !out_mad)
		जाओ out;

	init_query_mad(in_mad);
	in_mad->attr_id = IB_SMP_ATTR_NODE_DESC;

	err = mlx5_MAD_IFC(dev, 1, 1, 1, शून्य, शून्य, in_mad, out_mad);
	अगर (err)
		जाओ out;

	स_नकल(node_desc, out_mad->data, IB_DEVICE_NODE_DESC_MAX);
out:
	kमुक्त(in_mad);
	kमुक्त(out_mad);
	वापस err;
पूर्ण

पूर्णांक mlx5_query_mad_अगरc_node_guid(काष्ठा mlx5_ib_dev *dev, __be64 *node_guid)
अणु
	काष्ठा ib_smp *in_mad  = शून्य;
	काष्ठा ib_smp *out_mad = शून्य;
	पूर्णांक err = -ENOMEM;

	in_mad  = kzalloc(माप(*in_mad), GFP_KERNEL);
	out_mad = kदो_स्मृति(माप(*out_mad), GFP_KERNEL);
	अगर (!in_mad || !out_mad)
		जाओ out;

	init_query_mad(in_mad);
	in_mad->attr_id = IB_SMP_ATTR_NODE_INFO;

	err = mlx5_MAD_IFC(dev, 1, 1, 1, शून्य, शून्य, in_mad, out_mad);
	अगर (err)
		जाओ out;

	स_नकल(node_guid, out_mad->data + 12, 8);
out:
	kमुक्त(in_mad);
	kमुक्त(out_mad);
	वापस err;
पूर्ण

पूर्णांक mlx5_query_mad_अगरc_pkey(काष्ठा ib_device *ibdev, u32 port, u16 index,
			    u16 *pkey)
अणु
	काष्ठा ib_smp *in_mad  = शून्य;
	काष्ठा ib_smp *out_mad = शून्य;
	पूर्णांक err = -ENOMEM;

	in_mad  = kzalloc(माप(*in_mad), GFP_KERNEL);
	out_mad = kदो_स्मृति(माप(*out_mad), GFP_KERNEL);
	अगर (!in_mad || !out_mad)
		जाओ out;

	init_query_mad(in_mad);
	in_mad->attr_id  = IB_SMP_ATTR_PKEY_TABLE;
	in_mad->attr_mod = cpu_to_be32(index / 32);

	err = mlx5_MAD_IFC(to_mdev(ibdev), 1, 1, port, शून्य, शून्य, in_mad,
			   out_mad);
	अगर (err)
		जाओ out;

	*pkey = be16_to_cpu(((__be16 *)out_mad->data)[index % 32]);

out:
	kमुक्त(in_mad);
	kमुक्त(out_mad);
	वापस err;
पूर्ण

पूर्णांक mlx5_query_mad_अगरc_gids(काष्ठा ib_device *ibdev, u32 port, पूर्णांक index,
			    जोड़ ib_gid *gid)
अणु
	काष्ठा ib_smp *in_mad  = शून्य;
	काष्ठा ib_smp *out_mad = शून्य;
	पूर्णांक err = -ENOMEM;

	in_mad  = kzalloc(माप(*in_mad), GFP_KERNEL);
	out_mad = kदो_स्मृति(माप(*out_mad), GFP_KERNEL);
	अगर (!in_mad || !out_mad)
		जाओ out;

	init_query_mad(in_mad);
	in_mad->attr_id  = IB_SMP_ATTR_PORT_INFO;
	in_mad->attr_mod = cpu_to_be32(port);

	err = mlx5_MAD_IFC(to_mdev(ibdev), 1, 1, port, शून्य, शून्य, in_mad,
			   out_mad);
	अगर (err)
		जाओ out;

	स_नकल(gid->raw, out_mad->data + 8, 8);

	init_query_mad(in_mad);
	in_mad->attr_id  = IB_SMP_ATTR_GUID_INFO;
	in_mad->attr_mod = cpu_to_be32(index / 8);

	err = mlx5_MAD_IFC(to_mdev(ibdev), 1, 1, port, शून्य, शून्य, in_mad,
			   out_mad);
	अगर (err)
		जाओ out;

	स_नकल(gid->raw + 8, out_mad->data + (index % 8) * 8, 8);

out:
	kमुक्त(in_mad);
	kमुक्त(out_mad);
	वापस err;
पूर्ण

पूर्णांक mlx5_query_mad_अगरc_port(काष्ठा ib_device *ibdev, u32 port,
			    काष्ठा ib_port_attr *props)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	काष्ठा ib_smp *in_mad  = शून्य;
	काष्ठा ib_smp *out_mad = शून्य;
	पूर्णांक ext_active_speed;
	पूर्णांक err = -ENOMEM;

	in_mad  = kzalloc(माप(*in_mad), GFP_KERNEL);
	out_mad = kदो_स्मृति(माप(*out_mad), GFP_KERNEL);
	अगर (!in_mad || !out_mad)
		जाओ out;

	/* props being zeroed by the caller, aव्योम zeroing it here */

	init_query_mad(in_mad);
	in_mad->attr_id  = IB_SMP_ATTR_PORT_INFO;
	in_mad->attr_mod = cpu_to_be32(port);

	err = mlx5_MAD_IFC(dev, 1, 1, port, शून्य, शून्य, in_mad, out_mad);
	अगर (err) अणु
		mlx5_ib_warn(dev, "err %d\n", err);
		जाओ out;
	पूर्ण

	props->lid		= be16_to_cpup((__be16 *)(out_mad->data + 16));
	props->lmc		= out_mad->data[34] & 0x7;
	props->sm_lid		= be16_to_cpup((__be16 *)(out_mad->data + 18));
	props->sm_sl		= out_mad->data[36] & 0xf;
	props->state		= out_mad->data[32] & 0xf;
	props->phys_state	= out_mad->data[33] >> 4;
	props->port_cap_flags	= be32_to_cpup((__be32 *)(out_mad->data + 20));
	props->gid_tbl_len	= out_mad->data[50];
	props->max_msg_sz	= 1 << MLX5_CAP_GEN(mdev, log_max_msg);
	props->pkey_tbl_len	= dev->pkey_table_len;
	props->bad_pkey_cntr	= be16_to_cpup((__be16 *)(out_mad->data + 46));
	props->qkey_viol_cntr	= be16_to_cpup((__be16 *)(out_mad->data + 48));
	props->active_width	= out_mad->data[31] & 0xf;
	props->active_speed	= out_mad->data[35] >> 4;
	props->max_mtu		= out_mad->data[41] & 0xf;
	props->active_mtu	= out_mad->data[36] >> 4;
	props->subnet_समयout	= out_mad->data[51] & 0x1f;
	props->max_vl_num	= out_mad->data[37] >> 4;
	props->init_type_reply	= out_mad->data[41] >> 4;

	अगर (props->port_cap_flags & IB_PORT_CAP_MASK2_SUP) अणु
		props->port_cap_flags2 =
			be16_to_cpup((__be16 *)(out_mad->data + 60));

		अगर (props->port_cap_flags2 & IB_PORT_LINK_WIDTH_2X_SUP)
			props->active_width = out_mad->data[31] & 0x1f;
	पूर्ण

	/* Check अगर extended speeds (EDR/FDR/...) are supported */
	अगर (props->port_cap_flags & IB_PORT_EXTENDED_SPEEDS_SUP) अणु
		ext_active_speed = out_mad->data[62] >> 4;

		चयन (ext_active_speed) अणु
		हाल 1:
			props->active_speed = 16; /* FDR */
			अवरोध;
		हाल 2:
			props->active_speed = 32; /* EDR */
			अवरोध;
		हाल 4:
			अगर (props->port_cap_flags & IB_PORT_CAP_MASK2_SUP &&
			    props->port_cap_flags2 & IB_PORT_LINK_SPEED_HDR_SUP)
				props->active_speed = IB_SPEED_HDR;
			अवरोध;
		पूर्ण
	पूर्ण

	/* If reported active speed is QDR, check अगर is FDR-10 */
	अगर (props->active_speed == 4) अणु
		अगर (dev->port_caps[port - 1].ext_port_cap &
		    MLX_EXT_PORT_CAP_FLAG_EXTENDED_PORT_INFO) अणु
			init_query_mad(in_mad);
			in_mad->attr_id = MLX5_ATTR_EXTENDED_PORT_INFO;
			in_mad->attr_mod = cpu_to_be32(port);

			err = mlx5_MAD_IFC(dev, 1, 1, port,
					   शून्य, शून्य, in_mad, out_mad);
			अगर (err)
				जाओ out;

			/* Checking LinkSpeedActive क्रम FDR-10 */
			अगर (out_mad->data[15] & 0x1)
				props->active_speed = 8;
		पूर्ण
	पूर्ण

out:
	kमुक्त(in_mad);
	kमुक्त(out_mad);

	वापस err;
पूर्ण
