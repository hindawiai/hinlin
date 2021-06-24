<शैली गुरु>
/*
 * Copyright (c) 2016 Hisilicon Limited.
 * Copyright (c) 2007, 2008 Mellanox Technologies. All rights reserved.
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
#समावेश <linux/acpi.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_smi.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_cache.h>
#समावेश "hns_roce_common.h"
#समावेश "hns_roce_device.h"
#समावेश "hns_roce_hem.h"

अटल पूर्णांक hns_roce_set_mac(काष्ठा hns_roce_dev *hr_dev, u32 port, u8 *addr)
अणु
	u8 phy_port;
	u32 i;

	अगर (hr_dev->pci_dev->revision >= PCI_REVISION_ID_HIP09)
		वापस 0;

	अगर (!स_भेद(hr_dev->dev_addr[port], addr, ETH_ALEN))
		वापस 0;

	क्रम (i = 0; i < ETH_ALEN; i++)
		hr_dev->dev_addr[port][i] = addr[i];

	phy_port = hr_dev->iboe.phy_port[port];
	वापस hr_dev->hw->set_mac(hr_dev, phy_port, addr);
पूर्ण

अटल पूर्णांक hns_roce_add_gid(स्थिर काष्ठा ib_gid_attr *attr, व्योम **context)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(attr->device);
	u32 port = attr->port_num - 1;
	पूर्णांक ret;

	अगर (port >= hr_dev->caps.num_ports)
		वापस -EINVAL;

	ret = hr_dev->hw->set_gid(hr_dev, port, attr->index, &attr->gid, attr);

	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_del_gid(स्थिर काष्ठा ib_gid_attr *attr, व्योम **context)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(attr->device);
	u32 port = attr->port_num - 1;
	पूर्णांक ret;

	अगर (port >= hr_dev->caps.num_ports)
		वापस -EINVAL;

	ret = hr_dev->hw->set_gid(hr_dev, port, attr->index, शून्य, शून्य);

	वापस ret;
पूर्ण

अटल पूर्णांक handle_en_event(काष्ठा hns_roce_dev *hr_dev, u32 port,
			   अचिन्हित दीर्घ event)
अणु
	काष्ठा device *dev = hr_dev->dev;
	काष्ठा net_device *netdev;
	पूर्णांक ret = 0;

	netdev = hr_dev->iboe.netdevs[port];
	अगर (!netdev) अणु
		dev_err(dev, "Can't find netdev on port(%u)!\n", port);
		वापस -ENODEV;
	पूर्ण

	चयन (event) अणु
	हाल NETDEV_UP:
	हाल NETDEV_CHANGE:
	हाल NETDEV_REGISTER:
	हाल NETDEV_CHANGEADDR:
		ret = hns_roce_set_mac(hr_dev, port, netdev->dev_addr);
		अवरोध;
	हाल NETDEV_DOWN:
		/*
		 * In v1 engine, only support all ports बंदd together.
		 */
		अवरोध;
	शेष:
		dev_dbg(dev, "NETDEV event = 0x%x!\n", (u32)(event));
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_netdev_event(काष्ठा notअगरier_block *self,
				 अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा hns_roce_ib_iboe *iboe = शून्य;
	काष्ठा hns_roce_dev *hr_dev = शून्य;
	पूर्णांक ret;
	u32 port;

	hr_dev = container_of(self, काष्ठा hns_roce_dev, iboe.nb);
	iboe = &hr_dev->iboe;

	क्रम (port = 0; port < hr_dev->caps.num_ports; port++) अणु
		अगर (dev == iboe->netdevs[port]) अणु
			ret = handle_en_event(hr_dev, port, event);
			अगर (ret)
				वापस NOTIFY_DONE;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक hns_roce_setup_mtu_mac(काष्ठा hns_roce_dev *hr_dev)
अणु
	पूर्णांक ret;
	u8 i;

	क्रम (i = 0; i < hr_dev->caps.num_ports; i++) अणु
		अगर (hr_dev->hw->set_mtu)
			hr_dev->hw->set_mtu(hr_dev, hr_dev->iboe.phy_port[i],
					    hr_dev->caps.max_mtu);
		ret = hns_roce_set_mac(hr_dev, i,
				       hr_dev->iboe.netdevs[i]->dev_addr);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_query_device(काष्ठा ib_device *ib_dev,
				 काष्ठा ib_device_attr *props,
				 काष्ठा ib_udata *uhw)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ib_dev);

	स_रखो(props, 0, माप(*props));

	props->fw_ver = hr_dev->caps.fw_ver;
	props->sys_image_guid = cpu_to_be64(hr_dev->sys_image_guid);
	props->max_mr_size = (u64)(~(0ULL));
	props->page_size_cap = hr_dev->caps.page_size_cap;
	props->venकरोr_id = hr_dev->venकरोr_id;
	props->venकरोr_part_id = hr_dev->venकरोr_part_id;
	props->hw_ver = hr_dev->hw_rev;
	props->max_qp = hr_dev->caps.num_qps;
	props->max_qp_wr = hr_dev->caps.max_wqes;
	props->device_cap_flags = IB_DEVICE_PORT_ACTIVE_EVENT |
				  IB_DEVICE_RC_RNR_NAK_GEN;
	props->max_send_sge = hr_dev->caps.max_sq_sg;
	props->max_recv_sge = hr_dev->caps.max_rq_sg;
	props->max_sge_rd = 1;
	props->max_cq = hr_dev->caps.num_cqs;
	props->max_cqe = hr_dev->caps.max_cqes;
	props->max_mr = hr_dev->caps.num_mtpts;
	props->max_pd = hr_dev->caps.num_pds;
	props->max_qp_rd_atom = hr_dev->caps.max_qp_dest_rdma;
	props->max_qp_init_rd_atom = hr_dev->caps.max_qp_init_rdma;
	props->atomic_cap = hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_ATOMIC ?
			    IB_ATOMIC_HCA : IB_ATOMIC_NONE;
	props->max_pkeys = 1;
	props->local_ca_ack_delay = hr_dev->caps.local_ca_ack_delay;
	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_SRQ) अणु
		props->max_srq = hr_dev->caps.num_srqs;
		props->max_srq_wr = hr_dev->caps.max_srq_wrs;
		props->max_srq_sge = hr_dev->caps.max_srq_sges;
	पूर्ण

	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_FRMR &&
	    hr_dev->pci_dev->revision >= PCI_REVISION_ID_HIP09) अणु
		props->device_cap_flags |= IB_DEVICE_MEM_MGT_EXTENSIONS;
		props->max_fast_reg_page_list_len = HNS_ROCE_FRMR_MAX_PA;
	पूर्ण

	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_XRC)
		props->device_cap_flags |= IB_DEVICE_XRC;

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_query_port(काष्ठा ib_device *ib_dev, u32 port_num,
			       काष्ठा ib_port_attr *props)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ib_dev);
	काष्ठा device *dev = hr_dev->dev;
	काष्ठा net_device *net_dev;
	अचिन्हित दीर्घ flags;
	क्रमागत ib_mtu mtu;
	u32 port;

	port = port_num - 1;

	/* props being zeroed by the caller, aव्योम zeroing it here */

	props->max_mtu = hr_dev->caps.max_mtu;
	props->gid_tbl_len = hr_dev->caps.gid_table_len[port];
	props->port_cap_flags = IB_PORT_CM_SUP | IB_PORT_REINIT_SUP |
				IB_PORT_VENDOR_CLASS_SUP |
				IB_PORT_BOOT_MGMT_SUP;
	props->max_msg_sz = HNS_ROCE_MAX_MSG_LEN;
	props->pkey_tbl_len = 1;
	props->active_width = IB_WIDTH_4X;
	props->active_speed = 1;

	spin_lock_irqsave(&hr_dev->iboe.lock, flags);

	net_dev = hr_dev->iboe.netdevs[port];
	अगर (!net_dev) अणु
		spin_unlock_irqrestore(&hr_dev->iboe.lock, flags);
		dev_err(dev, "Find netdev %u failed!\n", port);
		वापस -EINVAL;
	पूर्ण

	mtu = iboe_get_mtu(net_dev->mtu);
	props->active_mtu = mtu ? min(props->max_mtu, mtu) : IB_MTU_256;
	props->state = netअगर_running(net_dev) && netअगर_carrier_ok(net_dev) ?
			       IB_PORT_ACTIVE :
			       IB_PORT_DOWN;
	props->phys_state = props->state == IB_PORT_ACTIVE ?
				    IB_PORT_PHYS_STATE_LINK_UP :
				    IB_PORT_PHYS_STATE_DISABLED;

	spin_unlock_irqrestore(&hr_dev->iboe.lock, flags);

	वापस 0;
पूर्ण

अटल क्रमागत rdma_link_layer hns_roce_get_link_layer(काष्ठा ib_device *device,
						    u32 port_num)
अणु
	वापस IB_LINK_LAYER_ETHERNET;
पूर्ण

अटल पूर्णांक hns_roce_query_pkey(काष्ठा ib_device *ib_dev, u32 port, u16 index,
			       u16 *pkey)
अणु
	*pkey = PKEY_ID;

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_modअगरy_device(काष्ठा ib_device *ib_dev, पूर्णांक mask,
				  काष्ठा ib_device_modअगरy *props)
अणु
	अचिन्हित दीर्घ flags;

	अगर (mask & ~IB_DEVICE_MODIFY_NODE_DESC)
		वापस -EOPNOTSUPP;

	अगर (mask & IB_DEVICE_MODIFY_NODE_DESC) अणु
		spin_lock_irqsave(&to_hr_dev(ib_dev)->sm_lock, flags);
		स_नकल(ib_dev->node_desc, props->node_desc, NODE_DESC_SIZE);
		spin_unlock_irqrestore(&to_hr_dev(ib_dev)->sm_lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_alloc_ucontext(काष्ठा ib_ucontext *uctx,
				   काष्ठा ib_udata *udata)
अणु
	पूर्णांक ret;
	काष्ठा hns_roce_ucontext *context = to_hr_ucontext(uctx);
	काष्ठा hns_roce_ib_alloc_ucontext_resp resp = अणुपूर्ण;
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(uctx->device);

	अगर (!hr_dev->active)
		वापस -EAGAIN;

	resp.qp_tab_size = hr_dev->caps.num_qps;
	resp.srq_tab_size = hr_dev->caps.num_srqs;

	ret = hns_roce_uar_alloc(hr_dev, &context->uar);
	अगर (ret)
		जाओ error_fail_uar_alloc;

	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_CQ_RECORD_DB ||
	    hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_QP_RECORD_DB) अणु
		INIT_LIST_HEAD(&context->page_list);
		mutex_init(&context->page_mutex);
	पूर्ण

	resp.cqe_size = hr_dev->caps.cqe_sz;

	ret = ib_copy_to_udata(udata, &resp,
			       min(udata->outlen, माप(resp)));
	अगर (ret)
		जाओ error_fail_copy_to_udata;

	वापस 0;

error_fail_copy_to_udata:
	hns_roce_uar_मुक्त(hr_dev, &context->uar);

error_fail_uar_alloc:
	वापस ret;
पूर्ण

अटल व्योम hns_roce_dealloc_ucontext(काष्ठा ib_ucontext *ibcontext)
अणु
	काष्ठा hns_roce_ucontext *context = to_hr_ucontext(ibcontext);

	hns_roce_uar_मुक्त(to_hr_dev(ibcontext->device), &context->uar);
पूर्ण

अटल पूर्णांक hns_roce_mmap(काष्ठा ib_ucontext *context,
			 काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(context->device);

	चयन (vma->vm_pgoff) अणु
	हाल 0:
		वापस rdma_user_mmap_io(context, vma,
					 to_hr_ucontext(context)->uar.pfn,
					 PAGE_SIZE,
					 pgprot_noncached(vma->vm_page_prot),
					 शून्य);

	/* vm_pgoff: 1 -- TPTR */
	हाल 1:
		अगर (!hr_dev->tptr_dma_addr || !hr_dev->tptr_size)
			वापस -EINVAL;
		/*
		 * FIXME: using io_remap_pfn_range on the dma address वापसed
		 * by dma_alloc_coherent is totally wrong.
		 */
		वापस rdma_user_mmap_io(context, vma,
					 hr_dev->tptr_dma_addr >> PAGE_SHIFT,
					 hr_dev->tptr_size,
					 vma->vm_page_prot,
					 शून्य);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक hns_roce_port_immutable(काष्ठा ib_device *ib_dev, u32 port_num,
				   काष्ठा ib_port_immutable *immutable)
अणु
	काष्ठा ib_port_attr attr;
	पूर्णांक ret;

	ret = ib_query_port(ib_dev, port_num, &attr);
	अगर (ret)
		वापस ret;

	immutable->pkey_tbl_len = attr.pkey_tbl_len;
	immutable->gid_tbl_len = attr.gid_tbl_len;

	immutable->max_mad_size = IB_MGMT_MAD_SIZE;
	immutable->core_cap_flags = RDMA_CORE_PORT_IBA_ROCE;
	अगर (to_hr_dev(ib_dev)->caps.flags & HNS_ROCE_CAP_FLAG_ROCE_V1_V2)
		immutable->core_cap_flags |= RDMA_CORE_PORT_IBA_ROCE_UDP_ENCAP;

	वापस 0;
पूर्ण

अटल व्योम hns_roce_disassociate_ucontext(काष्ठा ib_ucontext *ibcontext)
अणु
पूर्ण

अटल व्योम hns_roce_get_fw_ver(काष्ठा ib_device *device, अक्षर *str)
अणु
	u64 fw_ver = to_hr_dev(device)->caps.fw_ver;
	अचिन्हित पूर्णांक major, minor, sub_minor;

	major = upper_32_bits(fw_ver);
	minor = high_16_bits(lower_32_bits(fw_ver));
	sub_minor = low_16_bits(fw_ver);

	snम_लिखो(str, IB_FW_VERSION_NAME_MAX, "%u.%u.%04u", major, minor,
		 sub_minor);
पूर्ण

अटल व्योम hns_roce_unरेजिस्टर_device(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_ib_iboe *iboe = &hr_dev->iboe;

	hr_dev->active = false;
	unरेजिस्टर_netdevice_notअगरier(&iboe->nb);
	ib_unरेजिस्टर_device(&hr_dev->ib_dev);
पूर्ण

अटल स्थिर काष्ठा ib_device_ops hns_roce_dev_ops = अणु
	.owner = THIS_MODULE,
	.driver_id = RDMA_DRIVER_HNS,
	.uverbs_abi_ver = 1,
	.uverbs_no_driver_id_binding = 1,

	.get_dev_fw_str = hns_roce_get_fw_ver,
	.add_gid = hns_roce_add_gid,
	.alloc_pd = hns_roce_alloc_pd,
	.alloc_ucontext = hns_roce_alloc_ucontext,
	.create_ah = hns_roce_create_ah,
	.create_user_ah = hns_roce_create_ah,
	.create_cq = hns_roce_create_cq,
	.create_qp = hns_roce_create_qp,
	.dealloc_pd = hns_roce_dealloc_pd,
	.dealloc_ucontext = hns_roce_dealloc_ucontext,
	.del_gid = hns_roce_del_gid,
	.dereg_mr = hns_roce_dereg_mr,
	.destroy_ah = hns_roce_destroy_ah,
	.destroy_cq = hns_roce_destroy_cq,
	.disassociate_ucontext = hns_roce_disassociate_ucontext,
	.fill_res_cq_entry = hns_roce_fill_res_cq_entry,
	.get_dma_mr = hns_roce_get_dma_mr,
	.get_link_layer = hns_roce_get_link_layer,
	.get_port_immutable = hns_roce_port_immutable,
	.mmap = hns_roce_mmap,
	.modअगरy_device = hns_roce_modअगरy_device,
	.modअगरy_qp = hns_roce_modअगरy_qp,
	.query_ah = hns_roce_query_ah,
	.query_device = hns_roce_query_device,
	.query_pkey = hns_roce_query_pkey,
	.query_port = hns_roce_query_port,
	.reg_user_mr = hns_roce_reg_user_mr,

	INIT_RDMA_OBJ_SIZE(ib_ah, hns_roce_ah, ibah),
	INIT_RDMA_OBJ_SIZE(ib_cq, hns_roce_cq, ib_cq),
	INIT_RDMA_OBJ_SIZE(ib_pd, hns_roce_pd, ibpd),
	INIT_RDMA_OBJ_SIZE(ib_ucontext, hns_roce_ucontext, ibucontext),
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops hns_roce_dev_mr_ops = अणु
	.rereg_user_mr = hns_roce_rereg_user_mr,
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops hns_roce_dev_mw_ops = अणु
	.alloc_mw = hns_roce_alloc_mw,
	.dealloc_mw = hns_roce_dealloc_mw,

	INIT_RDMA_OBJ_SIZE(ib_mw, hns_roce_mw, ibmw),
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops hns_roce_dev_frmr_ops = अणु
	.alloc_mr = hns_roce_alloc_mr,
	.map_mr_sg = hns_roce_map_mr_sg,
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops hns_roce_dev_srq_ops = अणु
	.create_srq = hns_roce_create_srq,
	.destroy_srq = hns_roce_destroy_srq,

	INIT_RDMA_OBJ_SIZE(ib_srq, hns_roce_srq, ibsrq),
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops hns_roce_dev_xrcd_ops = अणु
	.alloc_xrcd = hns_roce_alloc_xrcd,
	.dealloc_xrcd = hns_roce_dealloc_xrcd,

	INIT_RDMA_OBJ_SIZE(ib_xrcd, hns_roce_xrcd, ibxrcd),
पूर्ण;

अटल पूर्णांक hns_roce_रेजिस्टर_device(काष्ठा hns_roce_dev *hr_dev)
अणु
	पूर्णांक ret;
	काष्ठा hns_roce_ib_iboe *iboe = शून्य;
	काष्ठा ib_device *ib_dev = शून्य;
	काष्ठा device *dev = hr_dev->dev;
	अचिन्हित पूर्णांक i;

	iboe = &hr_dev->iboe;
	spin_lock_init(&iboe->lock);

	ib_dev = &hr_dev->ib_dev;

	ib_dev->node_type = RDMA_NODE_IB_CA;
	ib_dev->dev.parent = dev;

	ib_dev->phys_port_cnt = hr_dev->caps.num_ports;
	ib_dev->local_dma_lkey = hr_dev->caps.reserved_lkey;
	ib_dev->num_comp_vectors = hr_dev->caps.num_comp_vectors;

	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_REREG_MR)
		ib_set_device_ops(ib_dev, &hns_roce_dev_mr_ops);

	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_MW)
		ib_set_device_ops(ib_dev, &hns_roce_dev_mw_ops);

	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_FRMR)
		ib_set_device_ops(ib_dev, &hns_roce_dev_frmr_ops);

	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_SRQ) अणु
		ib_set_device_ops(ib_dev, &hns_roce_dev_srq_ops);
		ib_set_device_ops(ib_dev, hr_dev->hw->hns_roce_dev_srq_ops);
	पूर्ण

	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_XRC)
		ib_set_device_ops(ib_dev, &hns_roce_dev_xrcd_ops);

	ib_set_device_ops(ib_dev, hr_dev->hw->hns_roce_dev_ops);
	ib_set_device_ops(ib_dev, &hns_roce_dev_ops);
	क्रम (i = 0; i < hr_dev->caps.num_ports; i++) अणु
		अगर (!hr_dev->iboe.netdevs[i])
			जारी;

		ret = ib_device_set_netdev(ib_dev, hr_dev->iboe.netdevs[i],
					   i + 1);
		अगर (ret)
			वापस ret;
	पूर्ण
	dma_set_max_seg_size(dev, अच_पूर्णांक_उच्च);
	ret = ib_रेजिस्टर_device(ib_dev, "hns_%d", dev);
	अगर (ret) अणु
		dev_err(dev, "ib_register_device failed!\n");
		वापस ret;
	पूर्ण

	ret = hns_roce_setup_mtu_mac(hr_dev);
	अगर (ret) अणु
		dev_err(dev, "setup_mtu_mac failed!\n");
		जाओ error_failed_setup_mtu_mac;
	पूर्ण

	iboe->nb.notअगरier_call = hns_roce_netdev_event;
	ret = रेजिस्टर_netdevice_notअगरier(&iboe->nb);
	अगर (ret) अणु
		dev_err(dev, "register_netdevice_notifier failed!\n");
		जाओ error_failed_setup_mtu_mac;
	पूर्ण

	hr_dev->active = true;
	वापस 0;

error_failed_setup_mtu_mac:
	ib_unरेजिस्टर_device(ib_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_init_hem(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा device *dev = hr_dev->dev;
	पूर्णांक ret;

	ret = hns_roce_init_hem_table(hr_dev, &hr_dev->mr_table.mtpt_table,
				      HEM_TYPE_MTPT, hr_dev->caps.mtpt_entry_sz,
				      hr_dev->caps.num_mtpts, 1);
	अगर (ret) अणु
		dev_err(dev, "Failed to init MTPT context memory, aborting.\n");
		वापस ret;
	पूर्ण

	ret = hns_roce_init_hem_table(hr_dev, &hr_dev->qp_table.qp_table,
				      HEM_TYPE_QPC, hr_dev->caps.qpc_sz,
				      hr_dev->caps.num_qps, 1);
	अगर (ret) अणु
		dev_err(dev, "Failed to init QP context memory, aborting.\n");
		जाओ err_unmap_dmpt;
	पूर्ण

	ret = hns_roce_init_hem_table(hr_dev, &hr_dev->qp_table.irrl_table,
				      HEM_TYPE_IRRL,
				      hr_dev->caps.irrl_entry_sz *
				      hr_dev->caps.max_qp_init_rdma,
				      hr_dev->caps.num_qps, 1);
	अगर (ret) अणु
		dev_err(dev, "Failed to init irrl_table memory, aborting.\n");
		जाओ err_unmap_qp;
	पूर्ण

	अगर (hr_dev->caps.trrl_entry_sz) अणु
		ret = hns_roce_init_hem_table(hr_dev,
					      &hr_dev->qp_table.trrl_table,
					      HEM_TYPE_TRRL,
					      hr_dev->caps.trrl_entry_sz *
					      hr_dev->caps.max_qp_dest_rdma,
					      hr_dev->caps.num_qps, 1);
		अगर (ret) अणु
			dev_err(dev,
				"Failed to init trrl_table memory, aborting.\n");
			जाओ err_unmap_irrl;
		पूर्ण
	पूर्ण

	ret = hns_roce_init_hem_table(hr_dev, &hr_dev->cq_table.table,
				      HEM_TYPE_CQC, hr_dev->caps.cqc_entry_sz,
				      hr_dev->caps.num_cqs, 1);
	अगर (ret) अणु
		dev_err(dev, "Failed to init CQ context memory, aborting.\n");
		जाओ err_unmap_trrl;
	पूर्ण

	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_SRQ) अणु
		ret = hns_roce_init_hem_table(hr_dev, &hr_dev->srq_table.table,
					      HEM_TYPE_SRQC,
					      hr_dev->caps.srqc_entry_sz,
					      hr_dev->caps.num_srqs, 1);
		अगर (ret) अणु
			dev_err(dev,
				"Failed to init SRQ context memory, aborting.\n");
			जाओ err_unmap_cq;
		पूर्ण
	पूर्ण

	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_QP_FLOW_CTRL) अणु
		ret = hns_roce_init_hem_table(hr_dev,
					      &hr_dev->qp_table.sccc_table,
					      HEM_TYPE_SCCC,
					      hr_dev->caps.sccc_sz,
					      hr_dev->caps.num_qps, 1);
		अगर (ret) अणु
			dev_err(dev,
				"Failed to init SCC context memory, aborting.\n");
			जाओ err_unmap_srq;
		पूर्ण
	पूर्ण

	अगर (hr_dev->caps.qpc_समयr_entry_sz) अणु
		ret = hns_roce_init_hem_table(hr_dev, &hr_dev->qpc_समयr_table,
					      HEM_TYPE_QPC_TIMER,
					      hr_dev->caps.qpc_समयr_entry_sz,
					      hr_dev->caps.num_qpc_समयr, 1);
		अगर (ret) अणु
			dev_err(dev,
				"Failed to init QPC timer memory, aborting.\n");
			जाओ err_unmap_ctx;
		पूर्ण
	पूर्ण

	अगर (hr_dev->caps.cqc_समयr_entry_sz) अणु
		ret = hns_roce_init_hem_table(hr_dev, &hr_dev->cqc_समयr_table,
					      HEM_TYPE_CQC_TIMER,
					      hr_dev->caps.cqc_समयr_entry_sz,
					      hr_dev->caps.num_cqc_समयr, 1);
		अगर (ret) अणु
			dev_err(dev,
				"Failed to init CQC timer memory, aborting.\n");
			जाओ err_unmap_qpc_समयr;
		पूर्ण
	पूर्ण

	अगर (hr_dev->caps.gmv_entry_sz) अणु
		ret = hns_roce_init_hem_table(hr_dev, &hr_dev->gmv_table,
					      HEM_TYPE_GMV,
					      hr_dev->caps.gmv_entry_sz,
					      hr_dev->caps.gmv_entry_num, 1);
		अगर (ret) अणु
			dev_err(dev,
				"failed to init gmv table memory, ret = %d\n",
				ret);
			जाओ err_unmap_cqc_समयr;
		पूर्ण
	पूर्ण

	वापस 0;

err_unmap_cqc_समयr:
	अगर (hr_dev->caps.cqc_समयr_entry_sz)
		hns_roce_cleanup_hem_table(hr_dev, &hr_dev->cqc_समयr_table);

err_unmap_qpc_समयr:
	अगर (hr_dev->caps.qpc_समयr_entry_sz)
		hns_roce_cleanup_hem_table(hr_dev, &hr_dev->qpc_समयr_table);

err_unmap_ctx:
	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_QP_FLOW_CTRL)
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->qp_table.sccc_table);
err_unmap_srq:
	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_SRQ)
		hns_roce_cleanup_hem_table(hr_dev, &hr_dev->srq_table.table);

err_unmap_cq:
	hns_roce_cleanup_hem_table(hr_dev, &hr_dev->cq_table.table);

err_unmap_trrl:
	अगर (hr_dev->caps.trrl_entry_sz)
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->qp_table.trrl_table);

err_unmap_irrl:
	hns_roce_cleanup_hem_table(hr_dev, &hr_dev->qp_table.irrl_table);

err_unmap_qp:
	hns_roce_cleanup_hem_table(hr_dev, &hr_dev->qp_table.qp_table);

err_unmap_dmpt:
	hns_roce_cleanup_hem_table(hr_dev, &hr_dev->mr_table.mtpt_table);

	वापस ret;
पूर्ण

/**
 * hns_roce_setup_hca - setup host channel adapter
 * @hr_dev: poपूर्णांकer to hns roce device
 * Return : पूर्णांक
 */
अटल पूर्णांक hns_roce_setup_hca(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा device *dev = hr_dev->dev;
	पूर्णांक ret;

	spin_lock_init(&hr_dev->sm_lock);
	spin_lock_init(&hr_dev->bt_cmd_lock);

	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_CQ_RECORD_DB ||
	    hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_QP_RECORD_DB) अणु
		INIT_LIST_HEAD(&hr_dev->pgdir_list);
		mutex_init(&hr_dev->pgdir_mutex);
	पूर्ण

	ret = hns_roce_init_uar_table(hr_dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to initialize uar table. aborting\n");
		वापस ret;
	पूर्ण

	ret = hns_roce_uar_alloc(hr_dev, &hr_dev->priv_uar);
	अगर (ret) अणु
		dev_err(dev, "Failed to allocate priv_uar.\n");
		जाओ err_uar_table_मुक्त;
	पूर्ण

	ret = hns_roce_init_pd_table(hr_dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to init protected domain table.\n");
		जाओ err_uar_alloc_मुक्त;
	पूर्ण

	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_XRC) अणु
		ret = hns_roce_init_xrcd_table(hr_dev);
		अगर (ret) अणु
			dev_err(dev, "failed to init xrcd table, ret = %d.\n",
				ret);
			जाओ err_pd_table_मुक्त;
		पूर्ण
	पूर्ण

	ret = hns_roce_init_mr_table(hr_dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to init memory region table.\n");
		जाओ err_xrcd_table_मुक्त;
	पूर्ण

	hns_roce_init_cq_table(hr_dev);

	ret = hns_roce_init_qp_table(hr_dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to init queue pair table.\n");
		जाओ err_cq_table_मुक्त;
	पूर्ण

	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_SRQ) अणु
		ret = hns_roce_init_srq_table(hr_dev);
		अगर (ret) अणु
			dev_err(dev,
				"Failed to init share receive queue table.\n");
			जाओ err_qp_table_मुक्त;
		पूर्ण
	पूर्ण

	वापस 0;

err_qp_table_मुक्त:
	hns_roce_cleanup_qp_table(hr_dev);

err_cq_table_मुक्त:
	hns_roce_cleanup_cq_table(hr_dev);
	hns_roce_cleanup_mr_table(hr_dev);

err_xrcd_table_मुक्त:
	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_XRC)
		hns_roce_cleanup_xrcd_table(hr_dev);

err_pd_table_मुक्त:
	hns_roce_cleanup_pd_table(hr_dev);

err_uar_alloc_मुक्त:
	hns_roce_uar_मुक्त(hr_dev, &hr_dev->priv_uar);

err_uar_table_मुक्त:
	hns_roce_cleanup_uar_table(hr_dev);
	वापस ret;
पूर्ण

अटल व्योम check_and_get_armed_cq(काष्ठा list_head *cq_list, काष्ठा ib_cq *cq)
अणु
	काष्ठा hns_roce_cq *hr_cq = to_hr_cq(cq);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hr_cq->lock, flags);
	अगर (cq->comp_handler) अणु
		अगर (!hr_cq->is_armed) अणु
			hr_cq->is_armed = 1;
			list_add_tail(&hr_cq->node, cq_list);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&hr_cq->lock, flags);
पूर्ण

व्योम hns_roce_handle_device_err(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_qp *hr_qp;
	काष्ठा hns_roce_cq *hr_cq;
	काष्ठा list_head cq_list;
	अचिन्हित दीर्घ flags_qp;
	अचिन्हित दीर्घ flags;

	INIT_LIST_HEAD(&cq_list);

	spin_lock_irqsave(&hr_dev->qp_list_lock, flags);
	list_क्रम_each_entry(hr_qp, &hr_dev->qp_list, node) अणु
		spin_lock_irqsave(&hr_qp->sq.lock, flags_qp);
		अगर (hr_qp->sq.tail != hr_qp->sq.head)
			check_and_get_armed_cq(&cq_list, hr_qp->ibqp.send_cq);
		spin_unlock_irqrestore(&hr_qp->sq.lock, flags_qp);

		spin_lock_irqsave(&hr_qp->rq.lock, flags_qp);
		अगर ((!hr_qp->ibqp.srq) && (hr_qp->rq.tail != hr_qp->rq.head))
			check_and_get_armed_cq(&cq_list, hr_qp->ibqp.recv_cq);
		spin_unlock_irqrestore(&hr_qp->rq.lock, flags_qp);
	पूर्ण

	list_क्रम_each_entry(hr_cq, &cq_list, node)
		hns_roce_cq_completion(hr_dev, hr_cq->cqn);

	spin_unlock_irqrestore(&hr_dev->qp_list_lock, flags);
पूर्ण

पूर्णांक hns_roce_init(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा device *dev = hr_dev->dev;
	पूर्णांक ret;

	अगर (hr_dev->hw->reset) अणु
		ret = hr_dev->hw->reset(hr_dev, true);
		अगर (ret) अणु
			dev_err(dev, "Reset RoCE engine failed!\n");
			वापस ret;
		पूर्ण
	पूर्ण
	hr_dev->is_reset = false;

	अगर (hr_dev->hw->cmq_init) अणु
		ret = hr_dev->hw->cmq_init(hr_dev);
		अगर (ret) अणु
			dev_err(dev, "Init RoCE Command Queue failed!\n");
			जाओ error_failed_cmq_init;
		पूर्ण
	पूर्ण

	ret = hr_dev->hw->hw_profile(hr_dev);
	अगर (ret) अणु
		dev_err(dev, "Get RoCE engine profile failed!\n");
		जाओ error_failed_cmd_init;
	पूर्ण

	ret = hns_roce_cmd_init(hr_dev);
	अगर (ret) अणु
		dev_err(dev, "cmd init failed!\n");
		जाओ error_failed_cmd_init;
	पूर्ण

	/* EQ depends on poll mode, event mode depends on EQ */
	ret = hr_dev->hw->init_eq(hr_dev);
	अगर (ret) अणु
		dev_err(dev, "eq init failed!\n");
		जाओ error_failed_eq_table;
	पूर्ण

	अगर (hr_dev->cmd_mod) अणु
		ret = hns_roce_cmd_use_events(hr_dev);
		अगर (ret) अणु
			dev_warn(dev,
				 "Cmd event  mode failed, set back to poll!\n");
			hns_roce_cmd_use_polling(hr_dev);
		पूर्ण
	पूर्ण

	ret = hns_roce_init_hem(hr_dev);
	अगर (ret) अणु
		dev_err(dev, "init HEM(Hardware Entry Memory) failed!\n");
		जाओ error_failed_init_hem;
	पूर्ण

	ret = hns_roce_setup_hca(hr_dev);
	अगर (ret) अणु
		dev_err(dev, "setup hca failed!\n");
		जाओ error_failed_setup_hca;
	पूर्ण

	अगर (hr_dev->hw->hw_init) अणु
		ret = hr_dev->hw->hw_init(hr_dev);
		अगर (ret) अणु
			dev_err(dev, "hw_init failed!\n");
			जाओ error_failed_engine_init;
		पूर्ण
	पूर्ण

	INIT_LIST_HEAD(&hr_dev->qp_list);
	spin_lock_init(&hr_dev->qp_list_lock);
	INIT_LIST_HEAD(&hr_dev->dip_list);
	spin_lock_init(&hr_dev->dip_list_lock);

	ret = hns_roce_रेजिस्टर_device(hr_dev);
	अगर (ret)
		जाओ error_failed_रेजिस्टर_device;

	वापस 0;

error_failed_रेजिस्टर_device:
	अगर (hr_dev->hw->hw_निकास)
		hr_dev->hw->hw_निकास(hr_dev);

error_failed_engine_init:
	hns_roce_cleanup_biपंचांगap(hr_dev);

error_failed_setup_hca:
	hns_roce_cleanup_hem(hr_dev);

error_failed_init_hem:
	अगर (hr_dev->cmd_mod)
		hns_roce_cmd_use_polling(hr_dev);
	hr_dev->hw->cleanup_eq(hr_dev);

error_failed_eq_table:
	hns_roce_cmd_cleanup(hr_dev);

error_failed_cmd_init:
	अगर (hr_dev->hw->cmq_निकास)
		hr_dev->hw->cmq_निकास(hr_dev);

error_failed_cmq_init:
	अगर (hr_dev->hw->reset) अणु
		अगर (hr_dev->hw->reset(hr_dev, false))
			dev_err(dev, "Dereset RoCE engine failed!\n");
	पूर्ण

	वापस ret;
पूर्ण

व्योम hns_roce_निकास(काष्ठा hns_roce_dev *hr_dev)
अणु
	hns_roce_unरेजिस्टर_device(hr_dev);

	अगर (hr_dev->hw->hw_निकास)
		hr_dev->hw->hw_निकास(hr_dev);
	hns_roce_cleanup_biपंचांगap(hr_dev);
	hns_roce_cleanup_hem(hr_dev);

	अगर (hr_dev->cmd_mod)
		hns_roce_cmd_use_polling(hr_dev);

	hr_dev->hw->cleanup_eq(hr_dev);
	hns_roce_cmd_cleanup(hr_dev);
	अगर (hr_dev->hw->cmq_निकास)
		hr_dev->hw->cmq_निकास(hr_dev);
	अगर (hr_dev->hw->reset)
		hr_dev->hw->reset(hr_dev, false);
पूर्ण

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Wei Hu <xavier.huwei@huawei.com>");
MODULE_AUTHOR("Nenglong Zhao <zhaonenglong@hisilicon.com>");
MODULE_AUTHOR("Lijun Ou <oulijun@huawei.com>");
MODULE_DESCRIPTION("HNS RoCE Driver");
