<शैली गुरु>
/*
 * Copyright (c) 2012-2016 VMware, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of EITHER the GNU General Public License
 * version 2 as published by the Free Software Foundation or the BSD
 * 2-Clause License. This program is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; WITHOUT EVEN THE IMPLIED
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License version 2 क्रम more details at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.en.hपंचांगl.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program available in the file COPYING in the मुख्य
 * directory of this source tree.
 *
 * The BSD 2-Clause License
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT,
 * INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <यंत्र/page.h>
#समावेश <linux/inet.h>
#समावेश <linux/पन.स>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_smi.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/vmw_pvrdma-abi.h>
#समावेश <rdma/uverbs_ioctl.h>

#समावेश "pvrdma.h"

/**
 * pvrdma_query_device - query device
 * @ibdev: the device to query
 * @props: the device properties
 * @uhw: user data
 *
 * @वापस: 0 on success, otherwise negative त्रुटि_सं
 */
पूर्णांक pvrdma_query_device(काष्ठा ib_device *ibdev,
			काष्ठा ib_device_attr *props,
			काष्ठा ib_udata *uhw)
अणु
	काष्ठा pvrdma_dev *dev = to_vdev(ibdev);

	अगर (uhw->inlen || uhw->outlen)
		वापस -EINVAL;

	props->fw_ver = dev->dsr->caps.fw_ver;
	props->sys_image_guid = dev->dsr->caps.sys_image_guid;
	props->max_mr_size = dev->dsr->caps.max_mr_size;
	props->page_size_cap = dev->dsr->caps.page_size_cap;
	props->venकरोr_id = dev->dsr->caps.venकरोr_id;
	props->venकरोr_part_id = dev->pdev->device;
	props->hw_ver = dev->dsr->caps.hw_ver;
	props->max_qp = dev->dsr->caps.max_qp;
	props->max_qp_wr = dev->dsr->caps.max_qp_wr;
	props->device_cap_flags = dev->dsr->caps.device_cap_flags;
	props->max_send_sge = dev->dsr->caps.max_sge;
	props->max_recv_sge = dev->dsr->caps.max_sge;
	props->max_sge_rd = PVRDMA_GET_CAP(dev, dev->dsr->caps.max_sge,
					   dev->dsr->caps.max_sge_rd);
	props->max_srq = dev->dsr->caps.max_srq;
	props->max_srq_wr = dev->dsr->caps.max_srq_wr;
	props->max_srq_sge = dev->dsr->caps.max_srq_sge;
	props->max_cq = dev->dsr->caps.max_cq;
	props->max_cqe = dev->dsr->caps.max_cqe;
	props->max_mr = dev->dsr->caps.max_mr;
	props->max_pd = dev->dsr->caps.max_pd;
	props->max_qp_rd_atom = dev->dsr->caps.max_qp_rd_atom;
	props->max_qp_init_rd_atom = dev->dsr->caps.max_qp_init_rd_atom;
	props->atomic_cap =
		dev->dsr->caps.atomic_ops &
		(PVRDMA_ATOMIC_OP_COMP_SWAP | PVRDMA_ATOMIC_OP_FETCH_ADD) ?
		IB_ATOMIC_HCA : IB_ATOMIC_NONE;
	props->masked_atomic_cap = props->atomic_cap;
	props->max_ah = dev->dsr->caps.max_ah;
	props->max_pkeys = dev->dsr->caps.max_pkeys;
	props->local_ca_ack_delay = dev->dsr->caps.local_ca_ack_delay;
	अगर ((dev->dsr->caps.bmme_flags & PVRDMA_BMME_FLAG_LOCAL_INV) &&
	    (dev->dsr->caps.bmme_flags & PVRDMA_BMME_FLAG_REMOTE_INV) &&
	    (dev->dsr->caps.bmme_flags & PVRDMA_BMME_FLAG_FAST_REG_WR)) अणु
		props->device_cap_flags |= IB_DEVICE_MEM_MGT_EXTENSIONS;
		props->max_fast_reg_page_list_len = PVRDMA_GET_CAP(dev,
				PVRDMA_MAX_FAST_REG_PAGES,
				dev->dsr->caps.max_fast_reg_page_list_len);
	पूर्ण

	props->device_cap_flags |= IB_DEVICE_PORT_ACTIVE_EVENT |
				   IB_DEVICE_RC_RNR_NAK_GEN;

	वापस 0;
पूर्ण

/**
 * pvrdma_query_port - query device port attributes
 * @ibdev: the device to query
 * @port: the port number
 * @props: the device properties
 *
 * @वापस: 0 on success, otherwise negative त्रुटि_सं
 */
पूर्णांक pvrdma_query_port(काष्ठा ib_device *ibdev, u32 port,
		      काष्ठा ib_port_attr *props)
अणु
	काष्ठा pvrdma_dev *dev = to_vdev(ibdev);
	जोड़ pvrdma_cmd_req req;
	जोड़ pvrdma_cmd_resp rsp;
	काष्ठा pvrdma_cmd_query_port *cmd = &req.query_port;
	काष्ठा pvrdma_cmd_query_port_resp *resp = &rsp.query_port_resp;
	पूर्णांक err;

	स_रखो(cmd, 0, माप(*cmd));
	cmd->hdr.cmd = PVRDMA_CMD_QUERY_PORT;
	cmd->port_num = port;

	err = pvrdma_cmd_post(dev, &req, &rsp, PVRDMA_CMD_QUERY_PORT_RESP);
	अगर (err < 0) अणु
		dev_warn(&dev->pdev->dev,
			 "could not query port, error: %d\n", err);
		वापस err;
	पूर्ण

	/* props being zeroed by the caller, aव्योम zeroing it here */

	props->state = pvrdma_port_state_to_ib(resp->attrs.state);
	props->max_mtu = pvrdma_mtu_to_ib(resp->attrs.max_mtu);
	props->active_mtu = pvrdma_mtu_to_ib(resp->attrs.active_mtu);
	props->gid_tbl_len = resp->attrs.gid_tbl_len;
	props->port_cap_flags =
		pvrdma_port_cap_flags_to_ib(resp->attrs.port_cap_flags);
	props->port_cap_flags |= IB_PORT_CM_SUP;
	props->ip_gids = true;
	props->max_msg_sz = resp->attrs.max_msg_sz;
	props->bad_pkey_cntr = resp->attrs.bad_pkey_cntr;
	props->qkey_viol_cntr = resp->attrs.qkey_viol_cntr;
	props->pkey_tbl_len = resp->attrs.pkey_tbl_len;
	props->lid = resp->attrs.lid;
	props->sm_lid = resp->attrs.sm_lid;
	props->lmc = resp->attrs.lmc;
	props->max_vl_num = resp->attrs.max_vl_num;
	props->sm_sl = resp->attrs.sm_sl;
	props->subnet_समयout = resp->attrs.subnet_समयout;
	props->init_type_reply = resp->attrs.init_type_reply;
	props->active_width = pvrdma_port_width_to_ib(resp->attrs.active_width);
	props->active_speed = pvrdma_port_speed_to_ib(resp->attrs.active_speed);
	props->phys_state = resp->attrs.phys_state;

	वापस 0;
पूर्ण

/**
 * pvrdma_query_gid - query device gid
 * @ibdev: the device to query
 * @port: the port number
 * @index: the index
 * @gid: the device gid value
 *
 * @वापस: 0 on success, otherwise negative त्रुटि_सं
 */
पूर्णांक pvrdma_query_gid(काष्ठा ib_device *ibdev, u32 port, पूर्णांक index,
		     जोड़ ib_gid *gid)
अणु
	काष्ठा pvrdma_dev *dev = to_vdev(ibdev);

	अगर (index >= dev->dsr->caps.gid_tbl_len)
		वापस -EINVAL;

	स_नकल(gid, &dev->sgid_tbl[index], माप(जोड़ ib_gid));

	वापस 0;
पूर्ण

/**
 * pvrdma_query_pkey - query device port's P_Key table
 * @ibdev: the device to query
 * @port: the port number
 * @index: the index
 * @pkey: the device P_Key value
 *
 * @वापस: 0 on success, otherwise negative त्रुटि_सं
 */
पूर्णांक pvrdma_query_pkey(काष्ठा ib_device *ibdev, u32 port, u16 index,
		      u16 *pkey)
अणु
	पूर्णांक err = 0;
	जोड़ pvrdma_cmd_req req;
	जोड़ pvrdma_cmd_resp rsp;
	काष्ठा pvrdma_cmd_query_pkey *cmd = &req.query_pkey;

	स_रखो(cmd, 0, माप(*cmd));
	cmd->hdr.cmd = PVRDMA_CMD_QUERY_PKEY;
	cmd->port_num = port;
	cmd->index = index;

	err = pvrdma_cmd_post(to_vdev(ibdev), &req, &rsp,
			      PVRDMA_CMD_QUERY_PKEY_RESP);
	अगर (err < 0) अणु
		dev_warn(&to_vdev(ibdev)->pdev->dev,
			 "could not query pkey, error: %d\n", err);
		वापस err;
	पूर्ण

	*pkey = rsp.query_pkey_resp.pkey;

	वापस 0;
पूर्ण

क्रमागत rdma_link_layer pvrdma_port_link_layer(काष्ठा ib_device *ibdev,
					    u32 port)
अणु
	वापस IB_LINK_LAYER_ETHERNET;
पूर्ण

पूर्णांक pvrdma_modअगरy_device(काष्ठा ib_device *ibdev, पूर्णांक mask,
			 काष्ठा ib_device_modअगरy *props)
अणु
	अचिन्हित दीर्घ flags;

	अगर (mask & ~(IB_DEVICE_MODIFY_SYS_IMAGE_GUID |
		     IB_DEVICE_MODIFY_NODE_DESC)) अणु
		dev_warn(&to_vdev(ibdev)->pdev->dev,
			 "unsupported device modify mask %#x\n", mask);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (mask & IB_DEVICE_MODIFY_NODE_DESC) अणु
		spin_lock_irqsave(&to_vdev(ibdev)->desc_lock, flags);
		स_नकल(ibdev->node_desc, props->node_desc, 64);
		spin_unlock_irqrestore(&to_vdev(ibdev)->desc_lock, flags);
	पूर्ण

	अगर (mask & IB_DEVICE_MODIFY_SYS_IMAGE_GUID) अणु
		mutex_lock(&to_vdev(ibdev)->port_mutex);
		to_vdev(ibdev)->sys_image_guid =
			cpu_to_be64(props->sys_image_guid);
		mutex_unlock(&to_vdev(ibdev)->port_mutex);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pvrdma_modअगरy_port - modअगरy device port attributes
 * @ibdev: the device to modअगरy
 * @port: the port number
 * @mask: attributes to modअगरy
 * @props: the device properties
 *
 * @वापस: 0 on success, otherwise negative त्रुटि_सं
 */
पूर्णांक pvrdma_modअगरy_port(काष्ठा ib_device *ibdev, u32 port, पूर्णांक mask,
		       काष्ठा ib_port_modअगरy *props)
अणु
	काष्ठा ib_port_attr attr;
	काष्ठा pvrdma_dev *vdev = to_vdev(ibdev);
	पूर्णांक ret;

	अगर (mask & ~IB_PORT_SHUTDOWN) अणु
		dev_warn(&vdev->pdev->dev,
			 "unsupported port modify mask %#x\n", mask);
		वापस -EOPNOTSUPP;
	पूर्ण

	mutex_lock(&vdev->port_mutex);
	ret = ib_query_port(ibdev, port, &attr);
	अगर (ret)
		जाओ out;

	vdev->port_cap_mask |= props->set_port_cap_mask;
	vdev->port_cap_mask &= ~props->clr_port_cap_mask;

	अगर (mask & IB_PORT_SHUTDOWN)
		vdev->ib_active = false;

out:
	mutex_unlock(&vdev->port_mutex);
	वापस ret;
पूर्ण

/**
 * pvrdma_alloc_ucontext - allocate ucontext
 * @uctx: the uverbs countext
 * @udata: user data
 *
 * @वापस:  zero on success, otherwise त्रुटि_सं.
 */
पूर्णांक pvrdma_alloc_ucontext(काष्ठा ib_ucontext *uctx, काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = uctx->device;
	काष्ठा pvrdma_dev *vdev = to_vdev(ibdev);
	काष्ठा pvrdma_ucontext *context = to_vucontext(uctx);
	जोड़ pvrdma_cmd_req req = अणुपूर्ण;
	जोड़ pvrdma_cmd_resp rsp = अणुपूर्ण;
	काष्ठा pvrdma_cmd_create_uc *cmd = &req.create_uc;
	काष्ठा pvrdma_cmd_create_uc_resp *resp = &rsp.create_uc_resp;
	काष्ठा pvrdma_alloc_ucontext_resp uresp = अणुपूर्ण;
	पूर्णांक ret;

	अगर (!vdev->ib_active)
		वापस -EAGAIN;

	context->dev = vdev;
	ret = pvrdma_uar_alloc(vdev, &context->uar);
	अगर (ret)
		वापस -ENOMEM;

	/* get ctx_handle from host */
	अगर (vdev->dsr_version < PVRDMA_PPN64_VERSION)
		cmd->pfn = context->uar.pfn;
	अन्यथा
		cmd->pfn64 = context->uar.pfn;

	cmd->hdr.cmd = PVRDMA_CMD_CREATE_UC;
	ret = pvrdma_cmd_post(vdev, &req, &rsp, PVRDMA_CMD_CREATE_UC_RESP);
	अगर (ret < 0) अणु
		dev_warn(&vdev->pdev->dev,
			 "could not create ucontext, error: %d\n", ret);
		जाओ err;
	पूर्ण

	context->ctx_handle = resp->ctx_handle;

	/* copy back to user */
	uresp.qp_tab_size = vdev->dsr->caps.max_qp;
	ret = ib_copy_to_udata(udata, &uresp, माप(uresp));
	अगर (ret) अणु
		pvrdma_uar_मुक्त(vdev, &context->uar);
		pvrdma_dealloc_ucontext(&context->ibucontext);
		वापस -EFAULT;
	पूर्ण

	वापस 0;

err:
	pvrdma_uar_मुक्त(vdev, &context->uar);
	वापस ret;
पूर्ण

/**
 * pvrdma_dealloc_ucontext - deallocate ucontext
 * @ibcontext: the ucontext
 */
व्योम pvrdma_dealloc_ucontext(काष्ठा ib_ucontext *ibcontext)
अणु
	काष्ठा pvrdma_ucontext *context = to_vucontext(ibcontext);
	जोड़ pvrdma_cmd_req req = अणुपूर्ण;
	काष्ठा pvrdma_cmd_destroy_uc *cmd = &req.destroy_uc;
	पूर्णांक ret;

	cmd->hdr.cmd = PVRDMA_CMD_DESTROY_UC;
	cmd->ctx_handle = context->ctx_handle;

	ret = pvrdma_cmd_post(context->dev, &req, शून्य, 0);
	अगर (ret < 0)
		dev_warn(&context->dev->pdev->dev,
			 "destroy ucontext failed, error: %d\n", ret);

	/* Free the UAR even अगर the device command failed */
	pvrdma_uar_मुक्त(to_vdev(ibcontext->device), &context->uar);
पूर्ण

/**
 * pvrdma_mmap - create mmap region
 * @ibcontext: the user context
 * @vma: the VMA
 *
 * @वापस: 0 on success, otherwise त्रुटि_सं.
 */
पूर्णांक pvrdma_mmap(काष्ठा ib_ucontext *ibcontext, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा pvrdma_ucontext *context = to_vucontext(ibcontext);
	अचिन्हित दीर्घ start = vma->vm_start;
	अचिन्हित दीर्घ size = vma->vm_end - vma->vm_start;
	अचिन्हित दीर्घ offset = vma->vm_pgoff << PAGE_SHIFT;

	dev_dbg(&context->dev->pdev->dev, "create mmap region\n");

	अगर ((size != PAGE_SIZE) || (offset & ~PAGE_MASK)) अणु
		dev_warn(&context->dev->pdev->dev,
			 "invalid params for mmap region\n");
		वापस -EINVAL;
	पूर्ण

	/* Map UAR to kernel space, VM_LOCKED? */
	vma->vm_flags |= VM_DONTCOPY | VM_DONTEXPAND;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	अगर (io_remap_pfn_range(vma, start, context->uar.pfn, size,
			       vma->vm_page_prot))
		वापस -EAGAIN;

	वापस 0;
पूर्ण

/**
 * pvrdma_alloc_pd - allocate protection करोमुख्य
 * @ibpd: PD poपूर्णांकer
 * @udata: user data
 *
 * @वापस: the ib_pd protection करोमुख्य poपूर्णांकer on success, otherwise त्रुटि_सं.
 */
पूर्णांक pvrdma_alloc_pd(काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = ibpd->device;
	काष्ठा pvrdma_pd *pd = to_vpd(ibpd);
	काष्ठा pvrdma_dev *dev = to_vdev(ibdev);
	जोड़ pvrdma_cmd_req req = अणुपूर्ण;
	जोड़ pvrdma_cmd_resp rsp = अणुपूर्ण;
	काष्ठा pvrdma_cmd_create_pd *cmd = &req.create_pd;
	काष्ठा pvrdma_cmd_create_pd_resp *resp = &rsp.create_pd_resp;
	काष्ठा pvrdma_alloc_pd_resp pd_resp = अणु0पूर्ण;
	पूर्णांक ret;
	काष्ठा pvrdma_ucontext *context = rdma_udata_to_drv_context(
		udata, काष्ठा pvrdma_ucontext, ibucontext);

	/* Check allowed max pds */
	अगर (!atomic_add_unless(&dev->num_pds, 1, dev->dsr->caps.max_pd))
		वापस -ENOMEM;

	cmd->hdr.cmd = PVRDMA_CMD_CREATE_PD;
	cmd->ctx_handle = context ? context->ctx_handle : 0;
	ret = pvrdma_cmd_post(dev, &req, &rsp, PVRDMA_CMD_CREATE_PD_RESP);
	अगर (ret < 0) अणु
		dev_warn(&dev->pdev->dev,
			 "failed to allocate protection domain, error: %d\n",
			 ret);
		जाओ err;
	पूर्ण

	pd->privileged = !udata;
	pd->pd_handle = resp->pd_handle;
	pd->pdn = resp->pd_handle;
	pd_resp.pdn = resp->pd_handle;

	अगर (udata) अणु
		अगर (ib_copy_to_udata(udata, &pd_resp, माप(pd_resp))) अणु
			dev_warn(&dev->pdev->dev,
				 "failed to copy back protection domain\n");
			pvrdma_dealloc_pd(&pd->ibpd, udata);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	/* u32 pd handle */
	वापस 0;

err:
	atomic_dec(&dev->num_pds);
	वापस ret;
पूर्ण

/**
 * pvrdma_dealloc_pd - deallocate protection करोमुख्य
 * @pd: the protection करोमुख्य to be released
 * @udata: user data or null क्रम kernel object
 *
 * @वापस: Always 0
 */
पूर्णांक pvrdma_dealloc_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata)
अणु
	काष्ठा pvrdma_dev *dev = to_vdev(pd->device);
	जोड़ pvrdma_cmd_req req = अणुपूर्ण;
	काष्ठा pvrdma_cmd_destroy_pd *cmd = &req.destroy_pd;
	पूर्णांक ret;

	cmd->hdr.cmd = PVRDMA_CMD_DESTROY_PD;
	cmd->pd_handle = to_vpd(pd)->pd_handle;

	ret = pvrdma_cmd_post(dev, &req, शून्य, 0);
	अगर (ret)
		dev_warn(&dev->pdev->dev,
			 "could not dealloc protection domain, error: %d\n",
			 ret);

	atomic_dec(&dev->num_pds);
	वापस 0;
पूर्ण

/**
 * pvrdma_create_ah - create an address handle
 * @ibah: the IB address handle
 * @init_attr: the attributes of the AH
 * @udata: poपूर्णांकer to user data
 *
 * @वापस: 0 on success, otherwise त्रुटि_सं.
 */
पूर्णांक pvrdma_create_ah(काष्ठा ib_ah *ibah, काष्ठा rdma_ah_init_attr *init_attr,
		     काष्ठा ib_udata *udata)
अणु
	काष्ठा rdma_ah_attr *ah_attr = init_attr->ah_attr;
	काष्ठा pvrdma_dev *dev = to_vdev(ibah->device);
	काष्ठा pvrdma_ah *ah = to_vah(ibah);
	स्थिर काष्ठा ib_global_route *grh;
	u32 port_num = rdma_ah_get_port_num(ah_attr);

	अगर (!(rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH))
		वापस -EINVAL;

	grh = rdma_ah_पढ़ो_grh(ah_attr);
	अगर ((ah_attr->type != RDMA_AH_ATTR_TYPE_ROCE)  ||
	    rdma_is_multicast_addr((काष्ठा in6_addr *)grh->dgid.raw))
		वापस -EINVAL;

	अगर (!atomic_add_unless(&dev->num_ahs, 1, dev->dsr->caps.max_ah))
		वापस -ENOMEM;

	ah->av.port_pd = to_vpd(ibah->pd)->pd_handle | (port_num << 24);
	ah->av.src_path_bits = rdma_ah_get_path_bits(ah_attr);
	ah->av.src_path_bits |= 0x80;
	ah->av.gid_index = grh->sgid_index;
	ah->av.hop_limit = grh->hop_limit;
	ah->av.sl_tclass_flowlabel = (grh->traffic_class << 20) |
				      grh->flow_label;
	स_नकल(ah->av.dgid, grh->dgid.raw, 16);
	स_नकल(ah->av.dmac, ah_attr->roce.dmac, ETH_ALEN);

	वापस 0;
पूर्ण

/**
 * pvrdma_destroy_ah - destroy an address handle
 * @ah: the address handle to destroyed
 * @flags: destroy address handle flags (see क्रमागत rdma_destroy_ah_flags)
 *
 */
पूर्णांक pvrdma_destroy_ah(काष्ठा ib_ah *ah, u32 flags)
अणु
	काष्ठा pvrdma_dev *dev = to_vdev(ah->device);

	atomic_dec(&dev->num_ahs);
	वापस 0;
पूर्ण
