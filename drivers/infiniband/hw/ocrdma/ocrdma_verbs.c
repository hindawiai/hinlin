<शैली गुरु>
/* This file is part of the Emulex RoCE Device Driver क्रम
 * RoCE (RDMA over Converged Ethernet) adapters.
 * Copyright (C) 2012-2015 Emulex. All rights reserved.
 * EMULEX and SLI are trademarks of Emulex.
 * www.emulex.com
 *
 * This software is available to you under a choice of one of two licenses.
 * You may choose to be licensed under the terms of the GNU General Public
 * License (GPL) Version 2, available from the file COPYING in the मुख्य
 * directory of this source tree, or the BSD license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary क्रमm must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the करोcumentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Contact Inक्रमmation:
 * linux-drivers@emulex.com
 *
 * Emulex
 * 3333 Susan Street
 * Costa Mesa, CA 92626
 */

#समावेश <linux/dma-mapping.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/iw_cm.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_cache.h>
#समावेश <rdma/uverbs_ioctl.h>

#समावेश "ocrdma.h"
#समावेश "ocrdma_hw.h"
#समावेश "ocrdma_verbs.h"
#समावेश <rdma/ocrdma-abi.h>

पूर्णांक ocrdma_query_pkey(काष्ठा ib_device *ibdev, u32 port, u16 index, u16 *pkey)
अणु
	अगर (index > 0)
		वापस -EINVAL;

	*pkey = 0xffff;
	वापस 0;
पूर्ण

पूर्णांक ocrdma_query_device(काष्ठा ib_device *ibdev, काष्ठा ib_device_attr *attr,
			काष्ठा ib_udata *uhw)
अणु
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(ibdev);

	अगर (uhw->inlen || uhw->outlen)
		वापस -EINVAL;

	स_रखो(attr, 0, माप *attr);
	स_नकल(&attr->fw_ver, &dev->attr.fw_ver[0],
	       min(माप(dev->attr.fw_ver), माप(attr->fw_ver)));
	ocrdma_get_guid(dev, (u8 *)&attr->sys_image_guid);
	attr->max_mr_size = dev->attr.max_mr_size;
	attr->page_size_cap = 0xffff000;
	attr->venकरोr_id = dev->nic_info.pdev->venकरोr;
	attr->venकरोr_part_id = dev->nic_info.pdev->device;
	attr->hw_ver = dev->asic_id;
	attr->max_qp = dev->attr.max_qp;
	attr->max_ah = OCRDMA_MAX_AH;
	attr->max_qp_wr = dev->attr.max_wqe;

	attr->device_cap_flags = IB_DEVICE_CURR_QP_STATE_MOD |
					IB_DEVICE_RC_RNR_NAK_GEN |
					IB_DEVICE_SHUTDOWN_PORT |
					IB_DEVICE_SYS_IMAGE_GUID |
					IB_DEVICE_LOCAL_DMA_LKEY |
					IB_DEVICE_MEM_MGT_EXTENSIONS;
	attr->max_send_sge = dev->attr.max_send_sge;
	attr->max_recv_sge = dev->attr.max_recv_sge;
	attr->max_sge_rd = dev->attr.max_rdma_sge;
	attr->max_cq = dev->attr.max_cq;
	attr->max_cqe = dev->attr.max_cqe;
	attr->max_mr = dev->attr.max_mr;
	attr->max_mw = dev->attr.max_mw;
	attr->max_pd = dev->attr.max_pd;
	attr->atomic_cap = 0;
	attr->max_qp_rd_atom =
	    min(dev->attr.max_ord_per_qp, dev->attr.max_ird_per_qp);
	attr->max_qp_init_rd_atom = dev->attr.max_ord_per_qp;
	attr->max_srq = dev->attr.max_srq;
	attr->max_srq_sge = dev->attr.max_srq_sge;
	attr->max_srq_wr = dev->attr.max_rqe;
	attr->local_ca_ack_delay = dev->attr.local_ca_ack_delay;
	attr->max_fast_reg_page_list_len = dev->attr.max_pages_per_frmr;
	attr->max_pkeys = 1;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम get_link_speed_and_width(काष्ठा ocrdma_dev *dev,
					    u16 *ib_speed, u8 *ib_width)
अणु
	पूर्णांक status;
	u8 speed;

	status = ocrdma_mbx_get_link_speed(dev, &speed, शून्य);
	अगर (status)
		speed = OCRDMA_PHYS_LINK_SPEED_ZERO;

	चयन (speed) अणु
	हाल OCRDMA_PHYS_LINK_SPEED_1GBPS:
		*ib_speed = IB_SPEED_SDR;
		*ib_width = IB_WIDTH_1X;
		अवरोध;

	हाल OCRDMA_PHYS_LINK_SPEED_10GBPS:
		*ib_speed = IB_SPEED_QDR;
		*ib_width = IB_WIDTH_1X;
		अवरोध;

	हाल OCRDMA_PHYS_LINK_SPEED_20GBPS:
		*ib_speed = IB_SPEED_DDR;
		*ib_width = IB_WIDTH_4X;
		अवरोध;

	हाल OCRDMA_PHYS_LINK_SPEED_40GBPS:
		*ib_speed = IB_SPEED_QDR;
		*ib_width = IB_WIDTH_4X;
		अवरोध;

	शेष:
		/* Unsupported */
		*ib_speed = IB_SPEED_SDR;
		*ib_width = IB_WIDTH_1X;
	पूर्ण
पूर्ण

पूर्णांक ocrdma_query_port(काष्ठा ib_device *ibdev,
		      u32 port, काष्ठा ib_port_attr *props)
अणु
	क्रमागत ib_port_state port_state;
	काष्ठा ocrdma_dev *dev;
	काष्ठा net_device *netdev;

	/* props being zeroed by the caller, aव्योम zeroing it here */
	dev = get_ocrdma_dev(ibdev);
	netdev = dev->nic_info.netdev;
	अगर (netअगर_running(netdev) && netअगर_oper_up(netdev)) अणु
		port_state = IB_PORT_ACTIVE;
		props->phys_state = IB_PORT_PHYS_STATE_LINK_UP;
	पूर्ण अन्यथा अणु
		port_state = IB_PORT_DOWN;
		props->phys_state = IB_PORT_PHYS_STATE_DISABLED;
	पूर्ण
	props->max_mtu = IB_MTU_4096;
	props->active_mtu = iboe_get_mtu(netdev->mtu);
	props->lid = 0;
	props->lmc = 0;
	props->sm_lid = 0;
	props->sm_sl = 0;
	props->state = port_state;
	props->port_cap_flags = IB_PORT_CM_SUP | IB_PORT_REINIT_SUP |
				IB_PORT_DEVICE_MGMT_SUP |
				IB_PORT_VENDOR_CLASS_SUP;
	props->ip_gids = true;
	props->gid_tbl_len = OCRDMA_MAX_SGID;
	props->pkey_tbl_len = 1;
	props->bad_pkey_cntr = 0;
	props->qkey_viol_cntr = 0;
	get_link_speed_and_width(dev, &props->active_speed,
				 &props->active_width);
	props->max_msg_sz = 0x80000000;
	props->max_vl_num = 4;
	वापस 0;
पूर्ण

अटल पूर्णांक ocrdma_add_mmap(काष्ठा ocrdma_ucontext *uctx, u64 phy_addr,
			   अचिन्हित दीर्घ len)
अणु
	काष्ठा ocrdma_mm *mm;

	mm = kzalloc(माप(*mm), GFP_KERNEL);
	अगर (mm == शून्य)
		वापस -ENOMEM;
	mm->key.phy_addr = phy_addr;
	mm->key.len = len;
	INIT_LIST_HEAD(&mm->entry);

	mutex_lock(&uctx->mm_list_lock);
	list_add_tail(&mm->entry, &uctx->mm_head);
	mutex_unlock(&uctx->mm_list_lock);
	वापस 0;
पूर्ण

अटल व्योम ocrdma_del_mmap(काष्ठा ocrdma_ucontext *uctx, u64 phy_addr,
			    अचिन्हित दीर्घ len)
अणु
	काष्ठा ocrdma_mm *mm, *पंचांगp;

	mutex_lock(&uctx->mm_list_lock);
	list_क्रम_each_entry_safe(mm, पंचांगp, &uctx->mm_head, entry) अणु
		अगर (len != mm->key.len && phy_addr != mm->key.phy_addr)
			जारी;

		list_del(&mm->entry);
		kमुक्त(mm);
		अवरोध;
	पूर्ण
	mutex_unlock(&uctx->mm_list_lock);
पूर्ण

अटल bool ocrdma_search_mmap(काष्ठा ocrdma_ucontext *uctx, u64 phy_addr,
			      अचिन्हित दीर्घ len)
अणु
	bool found = false;
	काष्ठा ocrdma_mm *mm;

	mutex_lock(&uctx->mm_list_lock);
	list_क्रम_each_entry(mm, &uctx->mm_head, entry) अणु
		अगर (len != mm->key.len && phy_addr != mm->key.phy_addr)
			जारी;

		found = true;
		अवरोध;
	पूर्ण
	mutex_unlock(&uctx->mm_list_lock);
	वापस found;
पूर्ण


अटल u16 _ocrdma_pd_mgr_get_biपंचांगap(काष्ठा ocrdma_dev *dev, bool dpp_pool)
अणु
	u16 pd_biपंचांगap_idx = 0;
	स्थिर अचिन्हित दीर्घ *pd_biपंचांगap;

	अगर (dpp_pool) अणु
		pd_biपंचांगap = dev->pd_mgr->pd_dpp_biपंचांगap;
		pd_biपंचांगap_idx = find_first_zero_bit(pd_biपंचांगap,
						    dev->pd_mgr->max_dpp_pd);
		__set_bit(pd_biपंचांगap_idx, dev->pd_mgr->pd_dpp_biपंचांगap);
		dev->pd_mgr->pd_dpp_count++;
		अगर (dev->pd_mgr->pd_dpp_count > dev->pd_mgr->pd_dpp_thrsh)
			dev->pd_mgr->pd_dpp_thrsh = dev->pd_mgr->pd_dpp_count;
	पूर्ण अन्यथा अणु
		pd_biपंचांगap = dev->pd_mgr->pd_norm_biपंचांगap;
		pd_biपंचांगap_idx = find_first_zero_bit(pd_biपंचांगap,
						    dev->pd_mgr->max_normal_pd);
		__set_bit(pd_biपंचांगap_idx, dev->pd_mgr->pd_norm_biपंचांगap);
		dev->pd_mgr->pd_norm_count++;
		अगर (dev->pd_mgr->pd_norm_count > dev->pd_mgr->pd_norm_thrsh)
			dev->pd_mgr->pd_norm_thrsh = dev->pd_mgr->pd_norm_count;
	पूर्ण
	वापस pd_biपंचांगap_idx;
पूर्ण

अटल पूर्णांक _ocrdma_pd_mgr_put_biपंचांगap(काष्ठा ocrdma_dev *dev, u16 pd_id,
					bool dpp_pool)
अणु
	u16 pd_count;
	u16 pd_bit_index;

	pd_count = dpp_pool ? dev->pd_mgr->pd_dpp_count :
			      dev->pd_mgr->pd_norm_count;
	अगर (pd_count == 0)
		वापस -EINVAL;

	अगर (dpp_pool) अणु
		pd_bit_index = pd_id - dev->pd_mgr->pd_dpp_start;
		अगर (pd_bit_index >= dev->pd_mgr->max_dpp_pd) अणु
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			__clear_bit(pd_bit_index, dev->pd_mgr->pd_dpp_biपंचांगap);
			dev->pd_mgr->pd_dpp_count--;
		पूर्ण
	पूर्ण अन्यथा अणु
		pd_bit_index = pd_id - dev->pd_mgr->pd_norm_start;
		अगर (pd_bit_index >= dev->pd_mgr->max_normal_pd) अणु
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			__clear_bit(pd_bit_index, dev->pd_mgr->pd_norm_biपंचांगap);
			dev->pd_mgr->pd_norm_count--;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ocrdma_put_pd_num(काष्ठा ocrdma_dev *dev, u16 pd_id,
				   bool dpp_pool)
अणु
	पूर्णांक status;

	mutex_lock(&dev->dev_lock);
	status = _ocrdma_pd_mgr_put_biपंचांगap(dev, pd_id, dpp_pool);
	mutex_unlock(&dev->dev_lock);
	वापस status;
पूर्ण

अटल पूर्णांक ocrdma_get_pd_num(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_pd *pd)
अणु
	u16 pd_idx = 0;
	पूर्णांक status = 0;

	mutex_lock(&dev->dev_lock);
	अगर (pd->dpp_enabled) अणु
		/* try allocating DPP PD, अगर not available then normal PD */
		अगर (dev->pd_mgr->pd_dpp_count < dev->pd_mgr->max_dpp_pd) अणु
			pd_idx = _ocrdma_pd_mgr_get_biपंचांगap(dev, true);
			pd->id = dev->pd_mgr->pd_dpp_start + pd_idx;
			pd->dpp_page = dev->pd_mgr->dpp_page_index + pd_idx;
		पूर्ण अन्यथा अगर (dev->pd_mgr->pd_norm_count <
			   dev->pd_mgr->max_normal_pd) अणु
			pd_idx = _ocrdma_pd_mgr_get_biपंचांगap(dev, false);
			pd->id = dev->pd_mgr->pd_norm_start + pd_idx;
			pd->dpp_enabled = false;
		पूर्ण अन्यथा अणु
			status = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (dev->pd_mgr->pd_norm_count < dev->pd_mgr->max_normal_pd) अणु
			pd_idx = _ocrdma_pd_mgr_get_biपंचांगap(dev, false);
			pd->id = dev->pd_mgr->pd_norm_start + pd_idx;
		पूर्ण अन्यथा अणु
			status = -EINVAL;
		पूर्ण
	पूर्ण
	mutex_unlock(&dev->dev_lock);
	वापस status;
पूर्ण

/*
 * NOTE:
 *
 * ocrdma_ucontext must be used here because this function is also
 * called from ocrdma_alloc_ucontext where ib_udata करोes not have
 * valid ib_ucontext poपूर्णांकer. ib_uverbs_get_context करोes not call
 * uobj_अणुalloc|get_xxxपूर्ण helpers which are used to store the
 * ib_ucontext in uverbs_attr_bundle wrapping the ib_udata. so
 * ib_udata करोes NOT imply valid ib_ucontext here!
 */
अटल पूर्णांक _ocrdma_alloc_pd(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_pd *pd,
			    काष्ठा ocrdma_ucontext *uctx,
			    काष्ठा ib_udata *udata)
अणु
	पूर्णांक status;

	अगर (udata && uctx && dev->attr.max_dpp_pds) अणु
		pd->dpp_enabled =
			ocrdma_get_asic_type(dev) == OCRDMA_ASIC_GEN_SKH_R;
		pd->num_dpp_qp =
			pd->dpp_enabled ? (dev->nic_info.db_page_size /
					   dev->attr.wqe_size) : 0;
	पूर्ण

	अगर (dev->pd_mgr->pd_pपुनः_स्मृति_valid)
		वापस ocrdma_get_pd_num(dev, pd);

retry:
	status = ocrdma_mbx_alloc_pd(dev, pd);
	अगर (status) अणु
		अगर (pd->dpp_enabled) अणु
			pd->dpp_enabled = false;
			pd->num_dpp_qp = 0;
			जाओ retry;
		पूर्ण
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_ucontext_pd(काष्ठा ocrdma_ucontext *uctx,
				 काष्ठा ocrdma_pd *pd)
अणु
	वापस (uctx->cntxt_pd == pd);
पूर्ण

अटल व्योम _ocrdma_dealloc_pd(काष्ठा ocrdma_dev *dev,
			      काष्ठा ocrdma_pd *pd)
अणु
	अगर (dev->pd_mgr->pd_pपुनः_स्मृति_valid)
		ocrdma_put_pd_num(dev, pd->id, pd->dpp_enabled);
	अन्यथा
		ocrdma_mbx_dealloc_pd(dev, pd);
पूर्ण

अटल पूर्णांक ocrdma_alloc_ucontext_pd(काष्ठा ocrdma_dev *dev,
				    काष्ठा ocrdma_ucontext *uctx,
				    काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = &dev->ibdev;
	काष्ठा ib_pd *pd;
	पूर्णांक status;

	pd = rdma_zalloc_drv_obj(ibdev, ib_pd);
	अगर (!pd)
		वापस -ENOMEM;

	pd->device  = ibdev;
	uctx->cntxt_pd = get_ocrdma_pd(pd);

	status = _ocrdma_alloc_pd(dev, uctx->cntxt_pd, uctx, udata);
	अगर (status) अणु
		kमुक्त(uctx->cntxt_pd);
		जाओ err;
	पूर्ण

	uctx->cntxt_pd->uctx = uctx;
	uctx->cntxt_pd->ibpd.device = &dev->ibdev;
err:
	वापस status;
पूर्ण

अटल व्योम ocrdma_dealloc_ucontext_pd(काष्ठा ocrdma_ucontext *uctx)
अणु
	काष्ठा ocrdma_pd *pd = uctx->cntxt_pd;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(pd->ibpd.device);

	अगर (uctx->pd_in_use) अणु
		pr_err("%s(%d) Freeing in use pdid=0x%x.\n",
		       __func__, dev->id, pd->id);
	पूर्ण
	uctx->cntxt_pd = शून्य;
	_ocrdma_dealloc_pd(dev, pd);
	kमुक्त(pd);
पूर्ण

अटल काष्ठा ocrdma_pd *ocrdma_get_ucontext_pd(काष्ठा ocrdma_ucontext *uctx)
अणु
	काष्ठा ocrdma_pd *pd = शून्य;

	mutex_lock(&uctx->mm_list_lock);
	अगर (!uctx->pd_in_use) अणु
		uctx->pd_in_use = true;
		pd = uctx->cntxt_pd;
	पूर्ण
	mutex_unlock(&uctx->mm_list_lock);

	वापस pd;
पूर्ण

अटल व्योम ocrdma_release_ucontext_pd(काष्ठा ocrdma_ucontext *uctx)
अणु
	mutex_lock(&uctx->mm_list_lock);
	uctx->pd_in_use = false;
	mutex_unlock(&uctx->mm_list_lock);
पूर्ण

पूर्णांक ocrdma_alloc_ucontext(काष्ठा ib_ucontext *uctx, काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = uctx->device;
	पूर्णांक status;
	काष्ठा ocrdma_ucontext *ctx = get_ocrdma_ucontext(uctx);
	काष्ठा ocrdma_alloc_ucontext_resp resp = अणुपूर्ण;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(ibdev);
	काष्ठा pci_dev *pdev = dev->nic_info.pdev;
	u32 map_len = roundup(माप(u32) * 2048, PAGE_SIZE);

	अगर (!udata)
		वापस -EFAULT;
	INIT_LIST_HEAD(&ctx->mm_head);
	mutex_init(&ctx->mm_list_lock);

	ctx->ah_tbl.va = dma_alloc_coherent(&pdev->dev, map_len,
					    &ctx->ah_tbl.pa, GFP_KERNEL);
	अगर (!ctx->ah_tbl.va)
		वापस -ENOMEM;

	ctx->ah_tbl.len = map_len;

	resp.ah_tbl_len = ctx->ah_tbl.len;
	resp.ah_tbl_page = virt_to_phys(ctx->ah_tbl.va);

	status = ocrdma_add_mmap(ctx, resp.ah_tbl_page, resp.ah_tbl_len);
	अगर (status)
		जाओ map_err;

	status = ocrdma_alloc_ucontext_pd(dev, ctx, udata);
	अगर (status)
		जाओ pd_err;

	resp.dev_id = dev->id;
	resp.max_अंतरभूत_data = dev->attr.max_अंतरभूत_data;
	resp.wqe_size = dev->attr.wqe_size;
	resp.rqe_size = dev->attr.rqe_size;
	resp.dpp_wqe_size = dev->attr.wqe_size;

	स_नकल(resp.fw_ver, dev->attr.fw_ver, माप(resp.fw_ver));
	status = ib_copy_to_udata(udata, &resp, माप(resp));
	अगर (status)
		जाओ cpy_err;
	वापस 0;

cpy_err:
	ocrdma_dealloc_ucontext_pd(ctx);
pd_err:
	ocrdma_del_mmap(ctx, ctx->ah_tbl.pa, ctx->ah_tbl.len);
map_err:
	dma_मुक्त_coherent(&pdev->dev, ctx->ah_tbl.len, ctx->ah_tbl.va,
			  ctx->ah_tbl.pa);
	वापस status;
पूर्ण

व्योम ocrdma_dealloc_ucontext(काष्ठा ib_ucontext *ibctx)
अणु
	काष्ठा ocrdma_mm *mm, *पंचांगp;
	काष्ठा ocrdma_ucontext *uctx = get_ocrdma_ucontext(ibctx);
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(ibctx->device);
	काष्ठा pci_dev *pdev = dev->nic_info.pdev;

	ocrdma_dealloc_ucontext_pd(uctx);

	ocrdma_del_mmap(uctx, uctx->ah_tbl.pa, uctx->ah_tbl.len);
	dma_मुक्त_coherent(&pdev->dev, uctx->ah_tbl.len, uctx->ah_tbl.va,
			  uctx->ah_tbl.pa);

	list_क्रम_each_entry_safe(mm, पंचांगp, &uctx->mm_head, entry) अणु
		list_del(&mm->entry);
		kमुक्त(mm);
	पूर्ण
पूर्ण

पूर्णांक ocrdma_mmap(काष्ठा ib_ucontext *context, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा ocrdma_ucontext *ucontext = get_ocrdma_ucontext(context);
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(context->device);
	अचिन्हित दीर्घ vm_page = vma->vm_pgoff << PAGE_SHIFT;
	u64 unmapped_db = (u64) dev->nic_info.unmapped_db;
	अचिन्हित दीर्घ len = (vma->vm_end - vma->vm_start);
	पूर्णांक status;
	bool found;

	अगर (vma->vm_start & (PAGE_SIZE - 1))
		वापस -EINVAL;
	found = ocrdma_search_mmap(ucontext, vma->vm_pgoff << PAGE_SHIFT, len);
	अगर (!found)
		वापस -EINVAL;

	अगर ((vm_page >= unmapped_db) && (vm_page <= (unmapped_db +
		dev->nic_info.db_total_size)) &&
		(len <=	dev->nic_info.db_page_size)) अणु
		अगर (vma->vm_flags & VM_READ)
			वापस -EPERM;

		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
		status = io_remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
					    len, vma->vm_page_prot);
	पूर्ण अन्यथा अगर (dev->nic_info.dpp_unmapped_len &&
		(vm_page >= (u64) dev->nic_info.dpp_unmapped_addr) &&
		(vm_page <= (u64) (dev->nic_info.dpp_unmapped_addr +
			dev->nic_info.dpp_unmapped_len)) &&
		(len <= dev->nic_info.dpp_unmapped_len)) अणु
		अगर (vma->vm_flags & VM_READ)
			वापस -EPERM;

		vma->vm_page_prot = pgprot_ग_लिखोcombine(vma->vm_page_prot);
		status = io_remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
					    len, vma->vm_page_prot);
	पूर्ण अन्यथा अणु
		status = remap_pfn_range(vma, vma->vm_start,
					 vma->vm_pgoff, len, vma->vm_page_prot);
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक ocrdma_copy_pd_uresp(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_pd *pd,
				काष्ठा ib_udata *udata)
अणु
	पूर्णांक status;
	u64 db_page_addr;
	u64 dpp_page_addr = 0;
	u32 db_page_size;
	काष्ठा ocrdma_alloc_pd_uresp rsp;
	काष्ठा ocrdma_ucontext *uctx = rdma_udata_to_drv_context(
		udata, काष्ठा ocrdma_ucontext, ibucontext);

	स_रखो(&rsp, 0, माप(rsp));
	rsp.id = pd->id;
	rsp.dpp_enabled = pd->dpp_enabled;
	db_page_addr = ocrdma_get_db_addr(dev, pd->id);
	db_page_size = dev->nic_info.db_page_size;

	status = ocrdma_add_mmap(uctx, db_page_addr, db_page_size);
	अगर (status)
		वापस status;

	अगर (pd->dpp_enabled) अणु
		dpp_page_addr = dev->nic_info.dpp_unmapped_addr +
				(pd->id * PAGE_SIZE);
		status = ocrdma_add_mmap(uctx, dpp_page_addr,
				 PAGE_SIZE);
		अगर (status)
			जाओ dpp_map_err;
		rsp.dpp_page_addr_hi = upper_32_bits(dpp_page_addr);
		rsp.dpp_page_addr_lo = dpp_page_addr;
	पूर्ण

	status = ib_copy_to_udata(udata, &rsp, माप(rsp));
	अगर (status)
		जाओ ucopy_err;

	pd->uctx = uctx;
	वापस 0;

ucopy_err:
	अगर (pd->dpp_enabled)
		ocrdma_del_mmap(pd->uctx, dpp_page_addr, PAGE_SIZE);
dpp_map_err:
	ocrdma_del_mmap(pd->uctx, db_page_addr, db_page_size);
	वापस status;
पूर्ण

पूर्णांक ocrdma_alloc_pd(काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = ibpd->device;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(ibdev);
	काष्ठा ocrdma_pd *pd;
	पूर्णांक status;
	u8 is_uctx_pd = false;
	काष्ठा ocrdma_ucontext *uctx = rdma_udata_to_drv_context(
		udata, काष्ठा ocrdma_ucontext, ibucontext);

	अगर (udata) अणु
		pd = ocrdma_get_ucontext_pd(uctx);
		अगर (pd) अणु
			is_uctx_pd = true;
			जाओ pd_mapping;
		पूर्ण
	पूर्ण

	pd = get_ocrdma_pd(ibpd);
	status = _ocrdma_alloc_pd(dev, pd, uctx, udata);
	अगर (status)
		जाओ निकास;

pd_mapping:
	अगर (udata) अणु
		status = ocrdma_copy_pd_uresp(dev, pd, udata);
		अगर (status)
			जाओ err;
	पूर्ण
	वापस 0;

err:
	अगर (is_uctx_pd)
		ocrdma_release_ucontext_pd(uctx);
	अन्यथा
		_ocrdma_dealloc_pd(dev, pd);
निकास:
	वापस status;
पूर्ण

पूर्णांक ocrdma_dealloc_pd(काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata)
अणु
	काष्ठा ocrdma_pd *pd = get_ocrdma_pd(ibpd);
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(ibpd->device);
	काष्ठा ocrdma_ucontext *uctx = शून्य;
	u64 usr_db;

	uctx = pd->uctx;
	अगर (uctx) अणु
		u64 dpp_db = dev->nic_info.dpp_unmapped_addr +
			(pd->id * PAGE_SIZE);
		अगर (pd->dpp_enabled)
			ocrdma_del_mmap(pd->uctx, dpp_db, PAGE_SIZE);
		usr_db = ocrdma_get_db_addr(dev, pd->id);
		ocrdma_del_mmap(pd->uctx, usr_db, dev->nic_info.db_page_size);

		अगर (is_ucontext_pd(uctx, pd)) अणु
			ocrdma_release_ucontext_pd(uctx);
			वापस 0;
		पूर्ण
	पूर्ण
	_ocrdma_dealloc_pd(dev, pd);
	वापस 0;
पूर्ण

अटल पूर्णांक ocrdma_alloc_lkey(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_mr *mr,
			    u32 pdid, पूर्णांक acc, u32 num_pbls, u32 addr_check)
अणु
	पूर्णांक status;

	mr->hwmr.fr_mr = 0;
	mr->hwmr.local_rd = 1;
	mr->hwmr.remote_rd = (acc & IB_ACCESS_REMOTE_READ) ? 1 : 0;
	mr->hwmr.remote_wr = (acc & IB_ACCESS_REMOTE_WRITE) ? 1 : 0;
	mr->hwmr.local_wr = (acc & IB_ACCESS_LOCAL_WRITE) ? 1 : 0;
	mr->hwmr.mw_bind = (acc & IB_ACCESS_MW_BIND) ? 1 : 0;
	mr->hwmr.remote_atomic = (acc & IB_ACCESS_REMOTE_ATOMIC) ? 1 : 0;
	mr->hwmr.num_pbls = num_pbls;

	status = ocrdma_mbx_alloc_lkey(dev, &mr->hwmr, pdid, addr_check);
	अगर (status)
		वापस status;

	mr->ibmr.lkey = mr->hwmr.lkey;
	अगर (mr->hwmr.remote_wr || mr->hwmr.remote_rd)
		mr->ibmr.rkey = mr->hwmr.lkey;
	वापस 0;
पूर्ण

काष्ठा ib_mr *ocrdma_get_dma_mr(काष्ठा ib_pd *ibpd, पूर्णांक acc)
अणु
	पूर्णांक status;
	काष्ठा ocrdma_mr *mr;
	काष्ठा ocrdma_pd *pd = get_ocrdma_pd(ibpd);
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(ibpd->device);

	अगर (acc & IB_ACCESS_REMOTE_WRITE && !(acc & IB_ACCESS_LOCAL_WRITE)) अणु
		pr_err("%s err, invalid access rights\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	status = ocrdma_alloc_lkey(dev, mr, pd->id, acc, 0,
				   OCRDMA_ADDR_CHECK_DISABLE);
	अगर (status) अणु
		kमुक्त(mr);
		वापस ERR_PTR(status);
	पूर्ण

	वापस &mr->ibmr;
पूर्ण

अटल व्योम ocrdma_मुक्त_mr_pbl_tbl(काष्ठा ocrdma_dev *dev,
				   काष्ठा ocrdma_hw_mr *mr)
अणु
	काष्ठा pci_dev *pdev = dev->nic_info.pdev;
	पूर्णांक i = 0;

	अगर (mr->pbl_table) अणु
		क्रम (i = 0; i < mr->num_pbls; i++) अणु
			अगर (!mr->pbl_table[i].va)
				जारी;
			dma_मुक्त_coherent(&pdev->dev, mr->pbl_size,
					  mr->pbl_table[i].va,
					  mr->pbl_table[i].pa);
		पूर्ण
		kमुक्त(mr->pbl_table);
		mr->pbl_table = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक ocrdma_get_pbl_info(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_mr *mr,
			      u32 num_pbes)
अणु
	u32 num_pbls = 0;
	u32 idx = 0;
	पूर्णांक status = 0;
	u32 pbl_size;

	करो अणु
		pbl_size = OCRDMA_MIN_HPAGE_SIZE * (1 << idx);
		अगर (pbl_size > MAX_OCRDMA_PBL_SIZE) अणु
			status = -EFAULT;
			अवरोध;
		पूर्ण
		num_pbls = roundup(num_pbes, (pbl_size / माप(u64)));
		num_pbls = num_pbls / (pbl_size / माप(u64));
		idx++;
	पूर्ण जबतक (num_pbls >= dev->attr.max_num_mr_pbl);

	mr->hwmr.num_pbes = num_pbes;
	mr->hwmr.num_pbls = num_pbls;
	mr->hwmr.pbl_size = pbl_size;
	वापस status;
पूर्ण

अटल पूर्णांक ocrdma_build_pbl_tbl(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_hw_mr *mr)
अणु
	पूर्णांक status = 0;
	पूर्णांक i;
	u32 dma_len = mr->pbl_size;
	काष्ठा pci_dev *pdev = dev->nic_info.pdev;
	व्योम *va;
	dma_addr_t pa;

	mr->pbl_table = kसुस्मृति(mr->num_pbls, माप(काष्ठा ocrdma_pbl),
				GFP_KERNEL);

	अगर (!mr->pbl_table)
		वापस -ENOMEM;

	क्रम (i = 0; i < mr->num_pbls; i++) अणु
		va = dma_alloc_coherent(&pdev->dev, dma_len, &pa, GFP_KERNEL);
		अगर (!va) अणु
			ocrdma_मुक्त_mr_pbl_tbl(dev, mr);
			status = -ENOMEM;
			अवरोध;
		पूर्ण
		mr->pbl_table[i].va = va;
		mr->pbl_table[i].pa = pa;
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम build_user_pbes(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_mr *mr)
अणु
	काष्ठा ocrdma_pbe *pbe;
	काष्ठा ib_block_iter biter;
	काष्ठा ocrdma_pbl *pbl_tbl = mr->hwmr.pbl_table;
	पूर्णांक pbe_cnt;
	u64 pg_addr;

	अगर (!mr->hwmr.num_pbes)
		वापस;

	pbe = (काष्ठा ocrdma_pbe *)pbl_tbl->va;
	pbe_cnt = 0;

	rdma_umem_क्रम_each_dma_block (mr->umem, &biter, PAGE_SIZE) अणु
		/* store the page address in pbe */
		pg_addr = rdma_block_iter_dma_address(&biter);
		pbe->pa_lo = cpu_to_le32(pg_addr);
		pbe->pa_hi = cpu_to_le32(upper_32_bits(pg_addr));
		pbe_cnt += 1;
		pbe++;

		/* अगर the given pbl is full storing the pbes,
		 * move to next pbl.
		 */
		अगर (pbe_cnt == (mr->hwmr.pbl_size / माप(u64))) अणु
			pbl_tbl++;
			pbe = (काष्ठा ocrdma_pbe *)pbl_tbl->va;
			pbe_cnt = 0;
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा ib_mr *ocrdma_reg_user_mr(काष्ठा ib_pd *ibpd, u64 start, u64 len,
				 u64 usr_addr, पूर्णांक acc, काष्ठा ib_udata *udata)
अणु
	पूर्णांक status = -ENOMEM;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(ibpd->device);
	काष्ठा ocrdma_mr *mr;
	काष्ठा ocrdma_pd *pd;

	pd = get_ocrdma_pd(ibpd);

	अगर (acc & IB_ACCESS_REMOTE_WRITE && !(acc & IB_ACCESS_LOCAL_WRITE))
		वापस ERR_PTR(-EINVAL);

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(status);
	mr->umem = ib_umem_get(ibpd->device, start, len, acc);
	अगर (IS_ERR(mr->umem)) अणु
		status = -EFAULT;
		जाओ umem_err;
	पूर्ण
	status = ocrdma_get_pbl_info(
		dev, mr, ib_umem_num_dma_blocks(mr->umem, PAGE_SIZE));
	अगर (status)
		जाओ umem_err;

	mr->hwmr.pbe_size = PAGE_SIZE;
	mr->hwmr.va = usr_addr;
	mr->hwmr.len = len;
	mr->hwmr.remote_wr = (acc & IB_ACCESS_REMOTE_WRITE) ? 1 : 0;
	mr->hwmr.remote_rd = (acc & IB_ACCESS_REMOTE_READ) ? 1 : 0;
	mr->hwmr.local_wr = (acc & IB_ACCESS_LOCAL_WRITE) ? 1 : 0;
	mr->hwmr.local_rd = 1;
	mr->hwmr.remote_atomic = (acc & IB_ACCESS_REMOTE_ATOMIC) ? 1 : 0;
	status = ocrdma_build_pbl_tbl(dev, &mr->hwmr);
	अगर (status)
		जाओ umem_err;
	build_user_pbes(dev, mr);
	status = ocrdma_reg_mr(dev, &mr->hwmr, pd->id, acc);
	अगर (status)
		जाओ mbx_err;
	mr->ibmr.lkey = mr->hwmr.lkey;
	अगर (mr->hwmr.remote_wr || mr->hwmr.remote_rd)
		mr->ibmr.rkey = mr->hwmr.lkey;

	वापस &mr->ibmr;

mbx_err:
	ocrdma_मुक्त_mr_pbl_tbl(dev, &mr->hwmr);
umem_err:
	kमुक्त(mr);
	वापस ERR_PTR(status);
पूर्ण

पूर्णांक ocrdma_dereg_mr(काष्ठा ib_mr *ib_mr, काष्ठा ib_udata *udata)
अणु
	काष्ठा ocrdma_mr *mr = get_ocrdma_mr(ib_mr);
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(ib_mr->device);

	(व्योम) ocrdma_mbx_dealloc_lkey(dev, mr->hwmr.fr_mr, mr->hwmr.lkey);

	kमुक्त(mr->pages);
	ocrdma_मुक्त_mr_pbl_tbl(dev, &mr->hwmr);

	/* it could be user रेजिस्टरed memory. */
	ib_umem_release(mr->umem);
	kमुक्त(mr);

	/* Don't stop cleanup, in हाल FW is unresponsive */
	अगर (dev->mqe_ctx.fw_error_state) अणु
		pr_err("%s(%d) fw not responding.\n",
		       __func__, dev->id);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ocrdma_copy_cq_uresp(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_cq *cq,
				काष्ठा ib_udata *udata)
अणु
	पूर्णांक status;
	काष्ठा ocrdma_ucontext *uctx = rdma_udata_to_drv_context(
		udata, काष्ठा ocrdma_ucontext, ibucontext);
	काष्ठा ocrdma_create_cq_uresp uresp;

	/* this must be user flow! */
	अगर (!udata)
		वापस -EINVAL;

	स_रखो(&uresp, 0, माप(uresp));
	uresp.cq_id = cq->id;
	uresp.page_size = PAGE_ALIGN(cq->len);
	uresp.num_pages = 1;
	uresp.max_hw_cqe = cq->max_hw_cqe;
	uresp.page_addr[0] = virt_to_phys(cq->va);
	uresp.db_page_addr =  ocrdma_get_db_addr(dev, uctx->cntxt_pd->id);
	uresp.db_page_size = dev->nic_info.db_page_size;
	uresp.phase_change = cq->phase_change ? 1 : 0;
	status = ib_copy_to_udata(udata, &uresp, माप(uresp));
	अगर (status) अणु
		pr_err("%s(%d) copy error cqid=0x%x.\n",
		       __func__, dev->id, cq->id);
		जाओ err;
	पूर्ण
	status = ocrdma_add_mmap(uctx, uresp.db_page_addr, uresp.db_page_size);
	अगर (status)
		जाओ err;
	status = ocrdma_add_mmap(uctx, uresp.page_addr[0], uresp.page_size);
	अगर (status) अणु
		ocrdma_del_mmap(uctx, uresp.db_page_addr, uresp.db_page_size);
		जाओ err;
	पूर्ण
	cq->ucontext = uctx;
err:
	वापस status;
पूर्ण

पूर्णांक ocrdma_create_cq(काष्ठा ib_cq *ibcq, स्थिर काष्ठा ib_cq_init_attr *attr,
		     काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = ibcq->device;
	पूर्णांक entries = attr->cqe;
	काष्ठा ocrdma_cq *cq = get_ocrdma_cq(ibcq);
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(ibdev);
	काष्ठा ocrdma_ucontext *uctx = rdma_udata_to_drv_context(
		udata, काष्ठा ocrdma_ucontext, ibucontext);
	u16 pd_id = 0;
	पूर्णांक status;
	काष्ठा ocrdma_create_cq_ureq ureq;

	अगर (attr->flags)
		वापस -EOPNOTSUPP;

	अगर (udata) अणु
		अगर (ib_copy_from_udata(&ureq, udata, माप(ureq)))
			वापस -EFAULT;
	पूर्ण अन्यथा
		ureq.dpp_cq = 0;

	spin_lock_init(&cq->cq_lock);
	spin_lock_init(&cq->comp_handler_lock);
	INIT_LIST_HEAD(&cq->sq_head);
	INIT_LIST_HEAD(&cq->rq_head);

	अगर (udata)
		pd_id = uctx->cntxt_pd->id;

	status = ocrdma_mbx_create_cq(dev, cq, entries, ureq.dpp_cq, pd_id);
	अगर (status)
		वापस status;

	अगर (udata) अणु
		status = ocrdma_copy_cq_uresp(dev, cq, udata);
		अगर (status)
			जाओ ctx_err;
	पूर्ण
	cq->phase = OCRDMA_CQE_VALID;
	dev->cq_tbl[cq->id] = cq;
	वापस 0;

ctx_err:
	ocrdma_mbx_destroy_cq(dev, cq);
	वापस status;
पूर्ण

पूर्णांक ocrdma_resize_cq(काष्ठा ib_cq *ibcq, पूर्णांक new_cnt,
		     काष्ठा ib_udata *udata)
अणु
	पूर्णांक status = 0;
	काष्ठा ocrdma_cq *cq = get_ocrdma_cq(ibcq);

	अगर (new_cnt < 1 || new_cnt > cq->max_hw_cqe) अणु
		status = -EINVAL;
		वापस status;
	पूर्ण
	ibcq->cqe = new_cnt;
	वापस status;
पूर्ण

अटल व्योम ocrdma_flush_cq(काष्ठा ocrdma_cq *cq)
अणु
	पूर्णांक cqe_cnt;
	पूर्णांक valid_count = 0;
	अचिन्हित दीर्घ flags;

	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(cq->ibcq.device);
	काष्ठा ocrdma_cqe *cqe = शून्य;

	cqe = cq->va;
	cqe_cnt = cq->cqe_cnt;

	/* Last irq might have scheduled a polling thपढ़ो
	 * sync-up with it beक्रमe hard flushing.
	 */
	spin_lock_irqsave(&cq->cq_lock, flags);
	जबतक (cqe_cnt) अणु
		अगर (is_cqe_valid(cq, cqe))
			valid_count++;
		cqe++;
		cqe_cnt--;
	पूर्ण
	ocrdma_ring_cq_db(dev, cq->id, false, false, valid_count);
	spin_unlock_irqrestore(&cq->cq_lock, flags);
पूर्ण

पूर्णांक ocrdma_destroy_cq(काष्ठा ib_cq *ibcq, काष्ठा ib_udata *udata)
अणु
	काष्ठा ocrdma_cq *cq = get_ocrdma_cq(ibcq);
	काष्ठा ocrdma_eq *eq = शून्य;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(ibcq->device);
	पूर्णांक pdid = 0;
	u32 irq, indx;

	dev->cq_tbl[cq->id] = शून्य;
	indx = ocrdma_get_eq_table_index(dev, cq->eqn);

	eq = &dev->eq_tbl[indx];
	irq = ocrdma_get_irq(dev, eq);
	synchronize_irq(irq);
	ocrdma_flush_cq(cq);

	ocrdma_mbx_destroy_cq(dev, cq);
	अगर (cq->ucontext) अणु
		pdid = cq->ucontext->cntxt_pd->id;
		ocrdma_del_mmap(cq->ucontext, (u64) cq->pa,
				PAGE_ALIGN(cq->len));
		ocrdma_del_mmap(cq->ucontext,
				ocrdma_get_db_addr(dev, pdid),
				dev->nic_info.db_page_size);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ocrdma_add_qpn_map(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_qp *qp)
अणु
	पूर्णांक status = -EINVAL;

	अगर (qp->id < OCRDMA_MAX_QP && dev->qp_tbl[qp->id] == शून्य) अणु
		dev->qp_tbl[qp->id] = qp;
		status = 0;
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम ocrdma_del_qpn_map(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_qp *qp)
अणु
	dev->qp_tbl[qp->id] = शून्य;
पूर्ण

अटल पूर्णांक ocrdma_check_qp_params(काष्ठा ib_pd *ibpd, काष्ठा ocrdma_dev *dev,
				  काष्ठा ib_qp_init_attr *attrs,
				  काष्ठा ib_udata *udata)
अणु
	अगर ((attrs->qp_type != IB_QPT_GSI) &&
	    (attrs->qp_type != IB_QPT_RC) &&
	    (attrs->qp_type != IB_QPT_UC) &&
	    (attrs->qp_type != IB_QPT_UD)) अणु
		pr_err("%s(%d) unsupported qp type=0x%x requested\n",
		       __func__, dev->id, attrs->qp_type);
		वापस -EOPNOTSUPP;
	पूर्ण
	/* Skip the check क्रम QP1 to support CM size of 128 */
	अगर ((attrs->qp_type != IB_QPT_GSI) &&
	    (attrs->cap.max_send_wr > dev->attr.max_wqe)) अणु
		pr_err("%s(%d) unsupported send_wr=0x%x requested\n",
		       __func__, dev->id, attrs->cap.max_send_wr);
		pr_err("%s(%d) supported send_wr=0x%x\n",
		       __func__, dev->id, dev->attr.max_wqe);
		वापस -EINVAL;
	पूर्ण
	अगर (!attrs->srq && (attrs->cap.max_recv_wr > dev->attr.max_rqe)) अणु
		pr_err("%s(%d) unsupported recv_wr=0x%x requested\n",
		       __func__, dev->id, attrs->cap.max_recv_wr);
		pr_err("%s(%d) supported recv_wr=0x%x\n",
		       __func__, dev->id, dev->attr.max_rqe);
		वापस -EINVAL;
	पूर्ण
	अगर (attrs->cap.max_अंतरभूत_data > dev->attr.max_अंतरभूत_data) अणु
		pr_err("%s(%d) unsupported inline data size=0x%x requested\n",
		       __func__, dev->id, attrs->cap.max_अंतरभूत_data);
		pr_err("%s(%d) supported inline data size=0x%x\n",
		       __func__, dev->id, dev->attr.max_अंतरभूत_data);
		वापस -EINVAL;
	पूर्ण
	अगर (attrs->cap.max_send_sge > dev->attr.max_send_sge) अणु
		pr_err("%s(%d) unsupported send_sge=0x%x requested\n",
		       __func__, dev->id, attrs->cap.max_send_sge);
		pr_err("%s(%d) supported send_sge=0x%x\n",
		       __func__, dev->id, dev->attr.max_send_sge);
		वापस -EINVAL;
	पूर्ण
	अगर (attrs->cap.max_recv_sge > dev->attr.max_recv_sge) अणु
		pr_err("%s(%d) unsupported recv_sge=0x%x requested\n",
		       __func__, dev->id, attrs->cap.max_recv_sge);
		pr_err("%s(%d) supported recv_sge=0x%x\n",
		       __func__, dev->id, dev->attr.max_recv_sge);
		वापस -EINVAL;
	पूर्ण
	/* unprivileged user space cannot create special QP */
	अगर (udata && attrs->qp_type == IB_QPT_GSI) अणु
		pr_err
		    ("%s(%d) Userspace can't create special QPs of type=0x%x\n",
		     __func__, dev->id, attrs->qp_type);
		वापस -EINVAL;
	पूर्ण
	/* allow creating only one GSI type of QP */
	अगर (attrs->qp_type == IB_QPT_GSI && dev->gsi_qp_created) अणु
		pr_err("%s(%d) GSI special QPs already created.\n",
		       __func__, dev->id);
		वापस -EINVAL;
	पूर्ण
	/* verअगरy consumer QPs are not trying to use GSI QP's CQ */
	अगर ((attrs->qp_type != IB_QPT_GSI) && (dev->gsi_qp_created)) अणु
		अगर ((dev->gsi_sqcq == get_ocrdma_cq(attrs->send_cq)) ||
			(dev->gsi_rqcq == get_ocrdma_cq(attrs->recv_cq))) अणु
			pr_err("%s(%d) Consumer QP cannot use GSI CQs.\n",
				__func__, dev->id);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ocrdma_copy_qp_uresp(काष्ठा ocrdma_qp *qp,
				काष्ठा ib_udata *udata, पूर्णांक dpp_offset,
				पूर्णांक dpp_credit_lmt, पूर्णांक srq)
अणु
	पूर्णांक status;
	u64 usr_db;
	काष्ठा ocrdma_create_qp_uresp uresp;
	काष्ठा ocrdma_pd *pd = qp->pd;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(pd->ibpd.device);

	स_रखो(&uresp, 0, माप(uresp));
	usr_db = dev->nic_info.unmapped_db +
			(pd->id * dev->nic_info.db_page_size);
	uresp.qp_id = qp->id;
	uresp.sq_dbid = qp->sq.dbid;
	uresp.num_sq_pages = 1;
	uresp.sq_page_size = PAGE_ALIGN(qp->sq.len);
	uresp.sq_page_addr[0] = virt_to_phys(qp->sq.va);
	uresp.num_wqe_allocated = qp->sq.max_cnt;
	अगर (!srq) अणु
		uresp.rq_dbid = qp->rq.dbid;
		uresp.num_rq_pages = 1;
		uresp.rq_page_size = PAGE_ALIGN(qp->rq.len);
		uresp.rq_page_addr[0] = virt_to_phys(qp->rq.va);
		uresp.num_rqe_allocated = qp->rq.max_cnt;
	पूर्ण
	uresp.db_page_addr = usr_db;
	uresp.db_page_size = dev->nic_info.db_page_size;
	uresp.db_sq_offset = OCRDMA_DB_GEN2_SQ_OFFSET;
	uresp.db_rq_offset = OCRDMA_DB_GEN2_RQ_OFFSET;
	uresp.db_shअगरt = OCRDMA_DB_RQ_SHIFT;

	अगर (qp->dpp_enabled) अणु
		uresp.dpp_credit = dpp_credit_lmt;
		uresp.dpp_offset = dpp_offset;
	पूर्ण
	status = ib_copy_to_udata(udata, &uresp, माप(uresp));
	अगर (status) अणु
		pr_err("%s(%d) user copy error.\n", __func__, dev->id);
		जाओ err;
	पूर्ण
	status = ocrdma_add_mmap(pd->uctx, uresp.sq_page_addr[0],
				 uresp.sq_page_size);
	अगर (status)
		जाओ err;

	अगर (!srq) अणु
		status = ocrdma_add_mmap(pd->uctx, uresp.rq_page_addr[0],
					 uresp.rq_page_size);
		अगर (status)
			जाओ rq_map_err;
	पूर्ण
	वापस status;
rq_map_err:
	ocrdma_del_mmap(pd->uctx, uresp.sq_page_addr[0], uresp.sq_page_size);
err:
	वापस status;
पूर्ण

अटल व्योम ocrdma_set_qp_db(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_qp *qp,
			     काष्ठा ocrdma_pd *pd)
अणु
	अगर (ocrdma_get_asic_type(dev) == OCRDMA_ASIC_GEN_SKH_R) अणु
		qp->sq_db = dev->nic_info.db +
			(pd->id * dev->nic_info.db_page_size) +
			OCRDMA_DB_GEN2_SQ_OFFSET;
		qp->rq_db = dev->nic_info.db +
			(pd->id * dev->nic_info.db_page_size) +
			OCRDMA_DB_GEN2_RQ_OFFSET;
	पूर्ण अन्यथा अणु
		qp->sq_db = dev->nic_info.db +
			(pd->id * dev->nic_info.db_page_size) +
			OCRDMA_DB_SQ_OFFSET;
		qp->rq_db = dev->nic_info.db +
			(pd->id * dev->nic_info.db_page_size) +
			OCRDMA_DB_RQ_OFFSET;
	पूर्ण
पूर्ण

अटल पूर्णांक ocrdma_alloc_wr_id_tbl(काष्ठा ocrdma_qp *qp)
अणु
	qp->wqe_wr_id_tbl =
	    kसुस्मृति(qp->sq.max_cnt, माप(*(qp->wqe_wr_id_tbl)),
		    GFP_KERNEL);
	अगर (qp->wqe_wr_id_tbl == शून्य)
		वापस -ENOMEM;
	qp->rqe_wr_id_tbl =
	    kसुस्मृति(qp->rq.max_cnt, माप(u64), GFP_KERNEL);
	अगर (qp->rqe_wr_id_tbl == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम ocrdma_set_qp_init_params(काष्ठा ocrdma_qp *qp,
				      काष्ठा ocrdma_pd *pd,
				      काष्ठा ib_qp_init_attr *attrs)
अणु
	qp->pd = pd;
	spin_lock_init(&qp->q_lock);
	INIT_LIST_HEAD(&qp->sq_entry);
	INIT_LIST_HEAD(&qp->rq_entry);

	qp->qp_type = attrs->qp_type;
	qp->cap_flags = OCRDMA_QP_INB_RD | OCRDMA_QP_INB_WR;
	qp->max_अंतरभूत_data = attrs->cap.max_अंतरभूत_data;
	qp->sq.max_sges = attrs->cap.max_send_sge;
	qp->rq.max_sges = attrs->cap.max_recv_sge;
	qp->state = OCRDMA_QPS_RST;
	qp->संकेतed = (attrs->sq_sig_type == IB_SIGNAL_ALL_WR) ? true : false;
पूर्ण

अटल व्योम ocrdma_store_gsi_qp_cq(काष्ठा ocrdma_dev *dev,
				   काष्ठा ib_qp_init_attr *attrs)
अणु
	अगर (attrs->qp_type == IB_QPT_GSI) अणु
		dev->gsi_qp_created = 1;
		dev->gsi_sqcq = get_ocrdma_cq(attrs->send_cq);
		dev->gsi_rqcq = get_ocrdma_cq(attrs->recv_cq);
	पूर्ण
पूर्ण

काष्ठा ib_qp *ocrdma_create_qp(काष्ठा ib_pd *ibpd,
			       काष्ठा ib_qp_init_attr *attrs,
			       काष्ठा ib_udata *udata)
अणु
	पूर्णांक status;
	काष्ठा ocrdma_pd *pd = get_ocrdma_pd(ibpd);
	काष्ठा ocrdma_qp *qp;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(ibpd->device);
	काष्ठा ocrdma_create_qp_ureq ureq;
	u16 dpp_credit_lmt, dpp_offset;

	अगर (attrs->create_flags)
		वापस ERR_PTR(-EOPNOTSUPP);

	status = ocrdma_check_qp_params(ibpd, dev, attrs, udata);
	अगर (status)
		जाओ gen_err;

	स_रखो(&ureq, 0, माप(ureq));
	अगर (udata) अणु
		अगर (ib_copy_from_udata(&ureq, udata, माप(ureq)))
			वापस ERR_PTR(-EFAULT);
	पूर्ण
	qp = kzalloc(माप(*qp), GFP_KERNEL);
	अगर (!qp) अणु
		status = -ENOMEM;
		जाओ gen_err;
	पूर्ण
	ocrdma_set_qp_init_params(qp, pd, attrs);
	अगर (udata == शून्य)
		qp->cap_flags |= (OCRDMA_QP_MW_BIND | OCRDMA_QP_LKEY0 |
					OCRDMA_QP_FAST_REG);

	mutex_lock(&dev->dev_lock);
	status = ocrdma_mbx_create_qp(qp, attrs, ureq.enable_dpp_cq,
					ureq.dpp_cq_id,
					&dpp_offset, &dpp_credit_lmt);
	अगर (status)
		जाओ mbx_err;

	/* user space QP's wr_id table are managed in library */
	अगर (udata == शून्य) अणु
		status = ocrdma_alloc_wr_id_tbl(qp);
		अगर (status)
			जाओ map_err;
	पूर्ण

	status = ocrdma_add_qpn_map(dev, qp);
	अगर (status)
		जाओ map_err;
	ocrdma_set_qp_db(dev, qp, pd);
	अगर (udata) अणु
		status = ocrdma_copy_qp_uresp(qp, udata, dpp_offset,
					      dpp_credit_lmt,
					      (attrs->srq != शून्य));
		अगर (status)
			जाओ cpy_err;
	पूर्ण
	ocrdma_store_gsi_qp_cq(dev, attrs);
	qp->ibqp.qp_num = qp->id;
	mutex_unlock(&dev->dev_lock);
	वापस &qp->ibqp;

cpy_err:
	ocrdma_del_qpn_map(dev, qp);
map_err:
	ocrdma_mbx_destroy_qp(dev, qp);
mbx_err:
	mutex_unlock(&dev->dev_lock);
	kमुक्त(qp->wqe_wr_id_tbl);
	kमुक्त(qp->rqe_wr_id_tbl);
	kमुक्त(qp);
	pr_err("%s(%d) error=%d\n", __func__, dev->id, status);
gen_err:
	वापस ERR_PTR(status);
पूर्ण

पूर्णांक _ocrdma_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
		      पूर्णांक attr_mask)
अणु
	पूर्णांक status = 0;
	काष्ठा ocrdma_qp *qp;
	काष्ठा ocrdma_dev *dev;
	क्रमागत ib_qp_state old_qps;

	qp = get_ocrdma_qp(ibqp);
	dev = get_ocrdma_dev(ibqp->device);
	अगर (attr_mask & IB_QP_STATE)
		status = ocrdma_qp_state_change(qp, attr->qp_state, &old_qps);
	/* अगर new and previous states are same hw करोesn't need to
	 * know about it.
	 */
	अगर (status < 0)
		वापस status;
	वापस ocrdma_mbx_modअगरy_qp(dev, qp, attr, attr_mask);
पूर्ण

पूर्णांक ocrdma_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
		     पूर्णांक attr_mask, काष्ठा ib_udata *udata)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक status = -EINVAL;
	काष्ठा ocrdma_qp *qp;
	काष्ठा ocrdma_dev *dev;
	क्रमागत ib_qp_state old_qps, new_qps;

	अगर (attr_mask & ~IB_QP_ATTR_STANDARD_BITS)
		वापस -EOPNOTSUPP;

	qp = get_ocrdma_qp(ibqp);
	dev = get_ocrdma_dev(ibqp->device);

	/* syncronize with multiple context trying to change, retrive qps */
	mutex_lock(&dev->dev_lock);
	/* syncronize with wqe, rqe posting and cqe processing contexts */
	spin_lock_irqsave(&qp->q_lock, flags);
	old_qps = get_ibqp_state(qp->state);
	अगर (attr_mask & IB_QP_STATE)
		new_qps = attr->qp_state;
	अन्यथा
		new_qps = old_qps;
	spin_unlock_irqrestore(&qp->q_lock, flags);

	अगर (!ib_modअगरy_qp_is_ok(old_qps, new_qps, ibqp->qp_type, attr_mask)) अणु
		pr_err("%s(%d) invalid attribute mask=0x%x specified for\n"
		       "qpn=0x%x of type=0x%x old_qps=0x%x, new_qps=0x%x\n",
		       __func__, dev->id, attr_mask, qp->id, ibqp->qp_type,
		       old_qps, new_qps);
		जाओ param_err;
	पूर्ण

	status = _ocrdma_modअगरy_qp(ibqp, attr, attr_mask);
	अगर (status > 0)
		status = 0;
param_err:
	mutex_unlock(&dev->dev_lock);
	वापस status;
पूर्ण

अटल क्रमागत ib_mtu ocrdma_mtu_पूर्णांक_to_क्रमागत(u16 mtu)
अणु
	चयन (mtu) अणु
	हाल 256:
		वापस IB_MTU_256;
	हाल 512:
		वापस IB_MTU_512;
	हाल 1024:
		वापस IB_MTU_1024;
	हाल 2048:
		वापस IB_MTU_2048;
	हाल 4096:
		वापस IB_MTU_4096;
	शेष:
		वापस IB_MTU_1024;
	पूर्ण
पूर्ण

अटल पूर्णांक ocrdma_to_ib_qp_acc_flags(पूर्णांक qp_cap_flags)
अणु
	पूर्णांक ib_qp_acc_flags = 0;

	अगर (qp_cap_flags & OCRDMA_QP_INB_WR)
		ib_qp_acc_flags |= IB_ACCESS_REMOTE_WRITE;
	अगर (qp_cap_flags & OCRDMA_QP_INB_RD)
		ib_qp_acc_flags |= IB_ACCESS_LOCAL_WRITE;
	वापस ib_qp_acc_flags;
पूर्ण

पूर्णांक ocrdma_query_qp(काष्ठा ib_qp *ibqp,
		    काष्ठा ib_qp_attr *qp_attr,
		    पूर्णांक attr_mask, काष्ठा ib_qp_init_attr *qp_init_attr)
अणु
	पूर्णांक status;
	u32 qp_state;
	काष्ठा ocrdma_qp_params params;
	काष्ठा ocrdma_qp *qp = get_ocrdma_qp(ibqp);
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(ibqp->device);

	स_रखो(&params, 0, माप(params));
	mutex_lock(&dev->dev_lock);
	status = ocrdma_mbx_query_qp(dev, qp, &params);
	mutex_unlock(&dev->dev_lock);
	अगर (status)
		जाओ mbx_err;
	अगर (qp->qp_type == IB_QPT_UD)
		qp_attr->qkey = params.qkey;
	qp_attr->path_mtu =
		ocrdma_mtu_पूर्णांक_to_क्रमागत(params.path_mtu_pkey_indx &
				OCRDMA_QP_PARAMS_PATH_MTU_MASK) >>
				OCRDMA_QP_PARAMS_PATH_MTU_SHIFT;
	qp_attr->path_mig_state = IB_MIG_MIGRATED;
	qp_attr->rq_psn = params.hop_lmt_rq_psn & OCRDMA_QP_PARAMS_RQ_PSN_MASK;
	qp_attr->sq_psn = params.tclass_sq_psn & OCRDMA_QP_PARAMS_SQ_PSN_MASK;
	qp_attr->dest_qp_num =
	    params.ack_to_rnr_rtc_dest_qpn & OCRDMA_QP_PARAMS_DEST_QPN_MASK;

	qp_attr->qp_access_flags = ocrdma_to_ib_qp_acc_flags(qp->cap_flags);
	qp_attr->cap.max_send_wr = qp->sq.max_cnt - 1;
	qp_attr->cap.max_recv_wr = qp->rq.max_cnt - 1;
	qp_attr->cap.max_send_sge = qp->sq.max_sges;
	qp_attr->cap.max_recv_sge = qp->rq.max_sges;
	qp_attr->cap.max_अंतरभूत_data = qp->max_अंतरभूत_data;
	qp_init_attr->cap = qp_attr->cap;
	qp_attr->ah_attr.type = RDMA_AH_ATTR_TYPE_ROCE;

	rdma_ah_set_grh(&qp_attr->ah_attr, शून्य,
			params.rnt_rc_sl_fl &
			  OCRDMA_QP_PARAMS_FLOW_LABEL_MASK,
			qp->sgid_idx,
			(params.hop_lmt_rq_psn &
			 OCRDMA_QP_PARAMS_HOP_LMT_MASK) >>
			 OCRDMA_QP_PARAMS_HOP_LMT_SHIFT,
			(params.tclass_sq_psn &
			 OCRDMA_QP_PARAMS_TCLASS_MASK) >>
			 OCRDMA_QP_PARAMS_TCLASS_SHIFT);
	rdma_ah_set_dgid_raw(&qp_attr->ah_attr, &params.dgid[0]);

	rdma_ah_set_port_num(&qp_attr->ah_attr, 1);
	rdma_ah_set_sl(&qp_attr->ah_attr, (params.rnt_rc_sl_fl &
					   OCRDMA_QP_PARAMS_SL_MASK) >>
					   OCRDMA_QP_PARAMS_SL_SHIFT);
	qp_attr->समयout = (params.ack_to_rnr_rtc_dest_qpn &
			    OCRDMA_QP_PARAMS_ACK_TIMEOUT_MASK) >>
				OCRDMA_QP_PARAMS_ACK_TIMEOUT_SHIFT;
	qp_attr->rnr_retry = (params.ack_to_rnr_rtc_dest_qpn &
			      OCRDMA_QP_PARAMS_RNR_RETRY_CNT_MASK) >>
				OCRDMA_QP_PARAMS_RNR_RETRY_CNT_SHIFT;
	qp_attr->retry_cnt =
	    (params.rnt_rc_sl_fl & OCRDMA_QP_PARAMS_RETRY_CNT_MASK) >>
		OCRDMA_QP_PARAMS_RETRY_CNT_SHIFT;
	qp_attr->min_rnr_समयr = 0;
	qp_attr->pkey_index = 0;
	qp_attr->port_num = 1;
	rdma_ah_set_path_bits(&qp_attr->ah_attr, 0);
	rdma_ah_set_अटल_rate(&qp_attr->ah_attr, 0);
	qp_attr->alt_pkey_index = 0;
	qp_attr->alt_port_num = 0;
	qp_attr->alt_समयout = 0;
	स_रखो(&qp_attr->alt_ah_attr, 0, माप(qp_attr->alt_ah_attr));
	qp_state = (params.max_sge_recv_flags & OCRDMA_QP_PARAMS_STATE_MASK) >>
		    OCRDMA_QP_PARAMS_STATE_SHIFT;
	qp_attr->qp_state = get_ibqp_state(qp_state);
	qp_attr->cur_qp_state = qp_attr->qp_state;
	qp_attr->sq_draining = (qp_state == OCRDMA_QPS_SQ_DRAINING) ? 1 : 0;
	qp_attr->max_dest_rd_atomic =
	    params.max_ord_ird >> OCRDMA_QP_PARAMS_MAX_ORD_SHIFT;
	qp_attr->max_rd_atomic =
	    params.max_ord_ird & OCRDMA_QP_PARAMS_MAX_IRD_MASK;
	qp_attr->en_sqd_async_notअगरy = (params.max_sge_recv_flags &
				OCRDMA_QP_PARAMS_FLAGS_SQD_ASYNC) ? 1 : 0;
	/* Sync driver QP state with FW */
	ocrdma_qp_state_change(qp, qp_attr->qp_state, शून्य);
mbx_err:
	वापस status;
पूर्ण

अटल व्योम ocrdma_srq_toggle_bit(काष्ठा ocrdma_srq *srq, अचिन्हित पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक i = idx / 32;
	u32 mask = (1U << (idx % 32));

	srq->idx_bit_fields[i] ^= mask;
पूर्ण

अटल पूर्णांक ocrdma_hwq_मुक्त_cnt(काष्ठा ocrdma_qp_hwq_info *q)
अणु
	वापस ((q->max_wqe_idx - q->head) + q->tail) % q->max_cnt;
पूर्ण

अटल पूर्णांक is_hw_sq_empty(काष्ठा ocrdma_qp *qp)
अणु
	वापस (qp->sq.tail == qp->sq.head);
पूर्ण

अटल पूर्णांक is_hw_rq_empty(काष्ठा ocrdma_qp *qp)
अणु
	वापस (qp->rq.tail == qp->rq.head);
पूर्ण

अटल व्योम *ocrdma_hwq_head(काष्ठा ocrdma_qp_hwq_info *q)
अणु
	वापस q->va + (q->head * q->entry_size);
पूर्ण

अटल व्योम *ocrdma_hwq_head_from_idx(काष्ठा ocrdma_qp_hwq_info *q,
				      u32 idx)
अणु
	वापस q->va + (idx * q->entry_size);
पूर्ण

अटल व्योम ocrdma_hwq_inc_head(काष्ठा ocrdma_qp_hwq_info *q)
अणु
	q->head = (q->head + 1) & q->max_wqe_idx;
पूर्ण

अटल व्योम ocrdma_hwq_inc_tail(काष्ठा ocrdma_qp_hwq_info *q)
अणु
	q->tail = (q->tail + 1) & q->max_wqe_idx;
पूर्ण

/* discard the cqe क्रम a given QP */
अटल व्योम ocrdma_discard_cqes(काष्ठा ocrdma_qp *qp, काष्ठा ocrdma_cq *cq)
अणु
	अचिन्हित दीर्घ cq_flags;
	अचिन्हित दीर्घ flags;
	पूर्णांक discard_cnt = 0;
	u32 cur_getp, stop_getp;
	काष्ठा ocrdma_cqe *cqe;
	u32 qpn = 0, wqe_idx = 0;

	spin_lock_irqsave(&cq->cq_lock, cq_flags);

	/* traverse through the CQEs in the hw CQ,
	 * find the matching CQE क्रम a given qp,
	 * mark the matching one discarded by clearing qpn.
	 * ring the करोorbell in the poll_cq() as
	 * we करोn't complete out of order cqe.
	 */

	cur_getp = cq->getp;
	/* find upto when करो we reap the cq. */
	stop_getp = cur_getp;
	करो अणु
		अगर (is_hw_sq_empty(qp) && (!qp->srq && is_hw_rq_empty(qp)))
			अवरोध;

		cqe = cq->va + cur_getp;
		/* अगर (a) करोne reaping whole hw cq, or
		 *    (b) qp_xq becomes empty.
		 * then निकास
		 */
		qpn = cqe->cmn.qpn & OCRDMA_CQE_QPN_MASK;
		/* अगर previously discarded cqe found, skip that too. */
		/* check क्रम matching qp */
		अगर (qpn == 0 || qpn != qp->id)
			जाओ skip_cqe;

		अगर (is_cqe_क्रम_sq(cqe)) अणु
			ocrdma_hwq_inc_tail(&qp->sq);
		पूर्ण अन्यथा अणु
			अगर (qp->srq) अणु
				wqe_idx = (le32_to_cpu(cqe->rq.buftag_qpn) >>
					OCRDMA_CQE_BUFTAG_SHIFT) &
					qp->srq->rq.max_wqe_idx;
				BUG_ON(wqe_idx < 1);
				spin_lock_irqsave(&qp->srq->q_lock, flags);
				ocrdma_hwq_inc_tail(&qp->srq->rq);
				ocrdma_srq_toggle_bit(qp->srq, wqe_idx - 1);
				spin_unlock_irqrestore(&qp->srq->q_lock, flags);

			पूर्ण अन्यथा अणु
				ocrdma_hwq_inc_tail(&qp->rq);
			पूर्ण
		पूर्ण
		/* mark cqe discarded so that it is not picked up later
		 * in the poll_cq().
		 */
		discard_cnt += 1;
		cqe->cmn.qpn = 0;
skip_cqe:
		cur_getp = (cur_getp + 1) % cq->max_hw_cqe;
	पूर्ण जबतक (cur_getp != stop_getp);
	spin_unlock_irqrestore(&cq->cq_lock, cq_flags);
पूर्ण

व्योम ocrdma_del_flush_qp(काष्ठा ocrdma_qp *qp)
अणु
	पूर्णांक found = false;
	अचिन्हित दीर्घ flags;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(qp->ibqp.device);
	/* sync with any active CQ poll */

	spin_lock_irqsave(&dev->flush_q_lock, flags);
	found = ocrdma_is_qp_in_sq_flushlist(qp->sq_cq, qp);
	अगर (found)
		list_del(&qp->sq_entry);
	अगर (!qp->srq) अणु
		found = ocrdma_is_qp_in_rq_flushlist(qp->rq_cq, qp);
		अगर (found)
			list_del(&qp->rq_entry);
	पूर्ण
	spin_unlock_irqrestore(&dev->flush_q_lock, flags);
पूर्ण

पूर्णांक ocrdma_destroy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_udata *udata)
अणु
	काष्ठा ocrdma_pd *pd;
	काष्ठा ocrdma_qp *qp;
	काष्ठा ocrdma_dev *dev;
	काष्ठा ib_qp_attr attrs;
	पूर्णांक attr_mask;
	अचिन्हित दीर्घ flags;

	qp = get_ocrdma_qp(ibqp);
	dev = get_ocrdma_dev(ibqp->device);

	pd = qp->pd;

	/* change the QP state to ERROR */
	अगर (qp->state != OCRDMA_QPS_RST) अणु
		attrs.qp_state = IB_QPS_ERR;
		attr_mask = IB_QP_STATE;
		_ocrdma_modअगरy_qp(ibqp, &attrs, attr_mask);
	पूर्ण
	/* ensure that CQEs क्रम newly created QP (whose id may be same with
	 * one which just getting destroyed are same), करोnt get
	 * discarded until the old CQEs are discarded.
	 */
	mutex_lock(&dev->dev_lock);
	(व्योम) ocrdma_mbx_destroy_qp(dev, qp);

	/*
	 * acquire CQ lock जबतक destroy is in progress, in order to
	 * protect against proessing in-flight CQEs क्रम this QP.
	 */
	spin_lock_irqsave(&qp->sq_cq->cq_lock, flags);
	अगर (qp->rq_cq && (qp->rq_cq != qp->sq_cq)) अणु
		spin_lock(&qp->rq_cq->cq_lock);
		ocrdma_del_qpn_map(dev, qp);
		spin_unlock(&qp->rq_cq->cq_lock);
	पूर्ण अन्यथा अणु
		ocrdma_del_qpn_map(dev, qp);
	पूर्ण
	spin_unlock_irqrestore(&qp->sq_cq->cq_lock, flags);

	अगर (!pd->uctx) अणु
		ocrdma_discard_cqes(qp, qp->sq_cq);
		ocrdma_discard_cqes(qp, qp->rq_cq);
	पूर्ण
	mutex_unlock(&dev->dev_lock);

	अगर (pd->uctx) अणु
		ocrdma_del_mmap(pd->uctx, (u64) qp->sq.pa,
				PAGE_ALIGN(qp->sq.len));
		अगर (!qp->srq)
			ocrdma_del_mmap(pd->uctx, (u64) qp->rq.pa,
					PAGE_ALIGN(qp->rq.len));
	पूर्ण

	ocrdma_del_flush_qp(qp);

	kमुक्त(qp->wqe_wr_id_tbl);
	kमुक्त(qp->rqe_wr_id_tbl);
	kमुक्त(qp);
	वापस 0;
पूर्ण

अटल पूर्णांक ocrdma_copy_srq_uresp(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_srq *srq,
				काष्ठा ib_udata *udata)
अणु
	पूर्णांक status;
	काष्ठा ocrdma_create_srq_uresp uresp;

	स_रखो(&uresp, 0, माप(uresp));
	uresp.rq_dbid = srq->rq.dbid;
	uresp.num_rq_pages = 1;
	uresp.rq_page_addr[0] = virt_to_phys(srq->rq.va);
	uresp.rq_page_size = srq->rq.len;
	uresp.db_page_addr = dev->nic_info.unmapped_db +
	    (srq->pd->id * dev->nic_info.db_page_size);
	uresp.db_page_size = dev->nic_info.db_page_size;
	uresp.num_rqe_allocated = srq->rq.max_cnt;
	अगर (ocrdma_get_asic_type(dev) == OCRDMA_ASIC_GEN_SKH_R) अणु
		uresp.db_rq_offset = OCRDMA_DB_GEN2_RQ_OFFSET;
		uresp.db_shअगरt = 24;
	पूर्ण अन्यथा अणु
		uresp.db_rq_offset = OCRDMA_DB_RQ_OFFSET;
		uresp.db_shअगरt = 16;
	पूर्ण

	status = ib_copy_to_udata(udata, &uresp, माप(uresp));
	अगर (status)
		वापस status;
	status = ocrdma_add_mmap(srq->pd->uctx, uresp.rq_page_addr[0],
				 uresp.rq_page_size);
	अगर (status)
		वापस status;
	वापस status;
पूर्ण

पूर्णांक ocrdma_create_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_init_attr *init_attr,
		      काष्ठा ib_udata *udata)
अणु
	पूर्णांक status;
	काष्ठा ocrdma_pd *pd = get_ocrdma_pd(ibsrq->pd);
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(ibsrq->device);
	काष्ठा ocrdma_srq *srq = get_ocrdma_srq(ibsrq);

	अगर (init_attr->srq_type != IB_SRQT_BASIC)
		वापस -EOPNOTSUPP;

	अगर (init_attr->attr.max_sge > dev->attr.max_recv_sge)
		वापस -EINVAL;
	अगर (init_attr->attr.max_wr > dev->attr.max_rqe)
		वापस -EINVAL;

	spin_lock_init(&srq->q_lock);
	srq->pd = pd;
	srq->db = dev->nic_info.db + (pd->id * dev->nic_info.db_page_size);
	status = ocrdma_mbx_create_srq(dev, srq, init_attr, pd);
	अगर (status)
		वापस status;

	अगर (!udata) अणु
		srq->rqe_wr_id_tbl = kसुस्मृति(srq->rq.max_cnt, माप(u64),
					     GFP_KERNEL);
		अगर (!srq->rqe_wr_id_tbl) अणु
			status = -ENOMEM;
			जाओ arm_err;
		पूर्ण

		srq->bit_fields_len = (srq->rq.max_cnt / 32) +
		    (srq->rq.max_cnt % 32 ? 1 : 0);
		srq->idx_bit_fields =
		    kदो_स्मृति_array(srq->bit_fields_len, माप(u32),
				  GFP_KERNEL);
		अगर (!srq->idx_bit_fields) अणु
			status = -ENOMEM;
			जाओ arm_err;
		पूर्ण
		स_रखो(srq->idx_bit_fields, 0xff,
		       srq->bit_fields_len * माप(u32));
	पूर्ण

	अगर (init_attr->attr.srq_limit) अणु
		status = ocrdma_mbx_modअगरy_srq(srq, &init_attr->attr);
		अगर (status)
			जाओ arm_err;
	पूर्ण

	अगर (udata) अणु
		status = ocrdma_copy_srq_uresp(dev, srq, udata);
		अगर (status)
			जाओ arm_err;
	पूर्ण

	वापस 0;

arm_err:
	ocrdma_mbx_destroy_srq(dev, srq);
	kमुक्त(srq->rqe_wr_id_tbl);
	kमुक्त(srq->idx_bit_fields);
	वापस status;
पूर्ण

पूर्णांक ocrdma_modअगरy_srq(काष्ठा ib_srq *ibsrq,
		      काष्ठा ib_srq_attr *srq_attr,
		      क्रमागत ib_srq_attr_mask srq_attr_mask,
		      काष्ठा ib_udata *udata)
अणु
	पूर्णांक status;
	काष्ठा ocrdma_srq *srq;

	srq = get_ocrdma_srq(ibsrq);
	अगर (srq_attr_mask & IB_SRQ_MAX_WR)
		status = -EINVAL;
	अन्यथा
		status = ocrdma_mbx_modअगरy_srq(srq, srq_attr);
	वापस status;
पूर्ण

पूर्णांक ocrdma_query_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *srq_attr)
अणु
	पूर्णांक status;
	काष्ठा ocrdma_srq *srq;

	srq = get_ocrdma_srq(ibsrq);
	status = ocrdma_mbx_query_srq(srq, srq_attr);
	वापस status;
पूर्ण

पूर्णांक ocrdma_destroy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_udata *udata)
अणु
	काष्ठा ocrdma_srq *srq;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(ibsrq->device);

	srq = get_ocrdma_srq(ibsrq);

	ocrdma_mbx_destroy_srq(dev, srq);

	अगर (srq->pd->uctx)
		ocrdma_del_mmap(srq->pd->uctx, (u64) srq->rq.pa,
				PAGE_ALIGN(srq->rq.len));

	kमुक्त(srq->idx_bit_fields);
	kमुक्त(srq->rqe_wr_id_tbl);
	वापस 0;
पूर्ण

/* unprivileged verbs and their support functions. */
अटल व्योम ocrdma_build_ud_hdr(काष्ठा ocrdma_qp *qp,
				काष्ठा ocrdma_hdr_wqe *hdr,
				स्थिर काष्ठा ib_send_wr *wr)
अणु
	काष्ठा ocrdma_ewqe_ud_hdr *ud_hdr =
		(काष्ठा ocrdma_ewqe_ud_hdr *)(hdr + 1);
	काष्ठा ocrdma_ah *ah = get_ocrdma_ah(ud_wr(wr)->ah);

	ud_hdr->rsvd_dest_qpn = ud_wr(wr)->remote_qpn;
	अगर (qp->qp_type == IB_QPT_GSI)
		ud_hdr->qkey = qp->qkey;
	अन्यथा
		ud_hdr->qkey = ud_wr(wr)->remote_qkey;
	ud_hdr->rsvd_ahid = ah->id;
	ud_hdr->hdr_type = ah->hdr_type;
	अगर (ah->av->valid & OCRDMA_AV_VLAN_VALID)
		hdr->cw |= (OCRDMA_FLAG_AH_VLAN_PR << OCRDMA_WQE_FLAGS_SHIFT);
पूर्ण

अटल व्योम ocrdma_build_sges(काष्ठा ocrdma_hdr_wqe *hdr,
			      काष्ठा ocrdma_sge *sge, पूर्णांक num_sge,
			      काष्ठा ib_sge *sg_list)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_sge; i++) अणु
		sge[i].lrkey = sg_list[i].lkey;
		sge[i].addr_lo = sg_list[i].addr;
		sge[i].addr_hi = upper_32_bits(sg_list[i].addr);
		sge[i].len = sg_list[i].length;
		hdr->total_len += sg_list[i].length;
	पूर्ण
	अगर (num_sge == 0)
		स_रखो(sge, 0, माप(*sge));
पूर्ण

अटल अंतरभूत uपूर्णांक32_t ocrdma_sglist_len(काष्ठा ib_sge *sg_list, पूर्णांक num_sge)
अणु
	uपूर्णांक32_t total_len = 0, i;

	क्रम (i = 0; i < num_sge; i++)
		total_len += sg_list[i].length;
	वापस total_len;
पूर्ण


अटल पूर्णांक ocrdma_build_अंतरभूत_sges(काष्ठा ocrdma_qp *qp,
				    काष्ठा ocrdma_hdr_wqe *hdr,
				    काष्ठा ocrdma_sge *sge,
				    स्थिर काष्ठा ib_send_wr *wr, u32 wqe_size)
अणु
	पूर्णांक i;
	अक्षर *dpp_addr;

	अगर (wr->send_flags & IB_SEND_INLINE && qp->qp_type != IB_QPT_UD) अणु
		hdr->total_len = ocrdma_sglist_len(wr->sg_list, wr->num_sge);
		अगर (unlikely(hdr->total_len > qp->max_अंतरभूत_data)) अणु
			pr_err("%s() supported_len=0x%x,\n"
			       " unsupported len req=0x%x\n", __func__,
				qp->max_अंतरभूत_data, hdr->total_len);
			वापस -EINVAL;
		पूर्ण
		dpp_addr = (अक्षर *)sge;
		क्रम (i = 0; i < wr->num_sge; i++) अणु
			स_नकल(dpp_addr,
			       (व्योम *)(अचिन्हित दीर्घ)wr->sg_list[i].addr,
			       wr->sg_list[i].length);
			dpp_addr += wr->sg_list[i].length;
		पूर्ण

		wqe_size += roundup(hdr->total_len, OCRDMA_WQE_ALIGN_BYTES);
		अगर (0 == hdr->total_len)
			wqe_size += माप(काष्ठा ocrdma_sge);
		hdr->cw |= (OCRDMA_TYPE_INLINE << OCRDMA_WQE_TYPE_SHIFT);
	पूर्ण अन्यथा अणु
		ocrdma_build_sges(hdr, sge, wr->num_sge, wr->sg_list);
		अगर (wr->num_sge)
			wqe_size += (wr->num_sge * माप(काष्ठा ocrdma_sge));
		अन्यथा
			wqe_size += माप(काष्ठा ocrdma_sge);
		hdr->cw |= (OCRDMA_TYPE_LKEY << OCRDMA_WQE_TYPE_SHIFT);
	पूर्ण
	hdr->cw |= ((wqe_size / OCRDMA_WQE_STRIDE) << OCRDMA_WQE_SIZE_SHIFT);
	वापस 0;
पूर्ण

अटल पूर्णांक ocrdma_build_send(काष्ठा ocrdma_qp *qp, काष्ठा ocrdma_hdr_wqe *hdr,
			     स्थिर काष्ठा ib_send_wr *wr)
अणु
	पूर्णांक status;
	काष्ठा ocrdma_sge *sge;
	u32 wqe_size = माप(*hdr);

	अगर (qp->qp_type == IB_QPT_UD || qp->qp_type == IB_QPT_GSI) अणु
		ocrdma_build_ud_hdr(qp, hdr, wr);
		sge = (काष्ठा ocrdma_sge *)(hdr + 2);
		wqe_size += माप(काष्ठा ocrdma_ewqe_ud_hdr);
	पूर्ण अन्यथा अणु
		sge = (काष्ठा ocrdma_sge *)(hdr + 1);
	पूर्ण

	status = ocrdma_build_अंतरभूत_sges(qp, hdr, sge, wr, wqe_size);
	वापस status;
पूर्ण

अटल पूर्णांक ocrdma_build_ग_लिखो(काष्ठा ocrdma_qp *qp, काष्ठा ocrdma_hdr_wqe *hdr,
			      स्थिर काष्ठा ib_send_wr *wr)
अणु
	पूर्णांक status;
	काष्ठा ocrdma_sge *ext_rw = (काष्ठा ocrdma_sge *)(hdr + 1);
	काष्ठा ocrdma_sge *sge = ext_rw + 1;
	u32 wqe_size = माप(*hdr) + माप(*ext_rw);

	status = ocrdma_build_अंतरभूत_sges(qp, hdr, sge, wr, wqe_size);
	अगर (status)
		वापस status;
	ext_rw->addr_lo = rdma_wr(wr)->remote_addr;
	ext_rw->addr_hi = upper_32_bits(rdma_wr(wr)->remote_addr);
	ext_rw->lrkey = rdma_wr(wr)->rkey;
	ext_rw->len = hdr->total_len;
	वापस 0;
पूर्ण

अटल व्योम ocrdma_build_पढ़ो(काष्ठा ocrdma_qp *qp, काष्ठा ocrdma_hdr_wqe *hdr,
			      स्थिर काष्ठा ib_send_wr *wr)
अणु
	काष्ठा ocrdma_sge *ext_rw = (काष्ठा ocrdma_sge *)(hdr + 1);
	काष्ठा ocrdma_sge *sge = ext_rw + 1;
	u32 wqe_size = ((wr->num_sge + 1) * माप(काष्ठा ocrdma_sge)) +
	    माप(काष्ठा ocrdma_hdr_wqe);

	ocrdma_build_sges(hdr, sge, wr->num_sge, wr->sg_list);
	hdr->cw |= ((wqe_size / OCRDMA_WQE_STRIDE) << OCRDMA_WQE_SIZE_SHIFT);
	hdr->cw |= (OCRDMA_READ << OCRDMA_WQE_OPCODE_SHIFT);
	hdr->cw |= (OCRDMA_TYPE_LKEY << OCRDMA_WQE_TYPE_SHIFT);

	ext_rw->addr_lo = rdma_wr(wr)->remote_addr;
	ext_rw->addr_hi = upper_32_bits(rdma_wr(wr)->remote_addr);
	ext_rw->lrkey = rdma_wr(wr)->rkey;
	ext_rw->len = hdr->total_len;
पूर्ण

अटल पूर्णांक get_encoded_page_size(पूर्णांक pg_sz)
अणु
	/* Max size is 256M 4096 << 16 */
	पूर्णांक i = 0;
	क्रम (; i < 17; i++)
		अगर (pg_sz == (4096 << i))
			अवरोध;
	वापस i;
पूर्ण

अटल पूर्णांक ocrdma_build_reg(काष्ठा ocrdma_qp *qp,
			    काष्ठा ocrdma_hdr_wqe *hdr,
			    स्थिर काष्ठा ib_reg_wr *wr)
अणु
	u64 fbo;
	काष्ठा ocrdma_ewqe_fr *fast_reg = (काष्ठा ocrdma_ewqe_fr *)(hdr + 1);
	काष्ठा ocrdma_mr *mr = get_ocrdma_mr(wr->mr);
	काष्ठा ocrdma_pbl *pbl_tbl = mr->hwmr.pbl_table;
	काष्ठा ocrdma_pbe *pbe;
	u32 wqe_size = माप(*fast_reg) + माप(*hdr);
	पूर्णांक num_pbes = 0, i;

	wqe_size = roundup(wqe_size, OCRDMA_WQE_ALIGN_BYTES);

	hdr->cw |= (OCRDMA_FR_MR << OCRDMA_WQE_OPCODE_SHIFT);
	hdr->cw |= ((wqe_size / OCRDMA_WQE_STRIDE) << OCRDMA_WQE_SIZE_SHIFT);

	अगर (wr->access & IB_ACCESS_LOCAL_WRITE)
		hdr->rsvd_lkey_flags |= OCRDMA_LKEY_FLAG_LOCAL_WR;
	अगर (wr->access & IB_ACCESS_REMOTE_WRITE)
		hdr->rsvd_lkey_flags |= OCRDMA_LKEY_FLAG_REMOTE_WR;
	अगर (wr->access & IB_ACCESS_REMOTE_READ)
		hdr->rsvd_lkey_flags |= OCRDMA_LKEY_FLAG_REMOTE_RD;
	hdr->lkey = wr->key;
	hdr->total_len = mr->ibmr.length;

	fbo = mr->ibmr.iova - mr->pages[0];

	fast_reg->va_hi = upper_32_bits(mr->ibmr.iova);
	fast_reg->va_lo = (u32) (mr->ibmr.iova & 0xffffffff);
	fast_reg->fbo_hi = upper_32_bits(fbo);
	fast_reg->fbo_lo = (u32) fbo & 0xffffffff;
	fast_reg->num_sges = mr->npages;
	fast_reg->size_sge = get_encoded_page_size(mr->ibmr.page_size);

	pbe = pbl_tbl->va;
	क्रम (i = 0; i < mr->npages; i++) अणु
		u64 buf_addr = mr->pages[i];

		pbe->pa_lo = cpu_to_le32((u32) (buf_addr & PAGE_MASK));
		pbe->pa_hi = cpu_to_le32((u32) upper_32_bits(buf_addr));
		num_pbes += 1;
		pbe++;

		/* अगर the pbl is full storing the pbes,
		 * move to next pbl.
		*/
		अगर (num_pbes == (mr->hwmr.pbl_size/माप(u64))) अणु
			pbl_tbl++;
			pbe = (काष्ठा ocrdma_pbe *)pbl_tbl->va;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ocrdma_ring_sq_db(काष्ठा ocrdma_qp *qp)
अणु
	u32 val = qp->sq.dbid | (1 << OCRDMA_DB_SQ_SHIFT);

	ioग_लिखो32(val, qp->sq_db);
पूर्ण

पूर्णांक ocrdma_post_send(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
		     स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	पूर्णांक status = 0;
	काष्ठा ocrdma_qp *qp = get_ocrdma_qp(ibqp);
	काष्ठा ocrdma_hdr_wqe *hdr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qp->q_lock, flags);
	अगर (qp->state != OCRDMA_QPS_RTS && qp->state != OCRDMA_QPS_SQD) अणु
		spin_unlock_irqrestore(&qp->q_lock, flags);
		*bad_wr = wr;
		वापस -EINVAL;
	पूर्ण

	जबतक (wr) अणु
		अगर (qp->qp_type == IB_QPT_UD &&
		    (wr->opcode != IB_WR_SEND &&
		     wr->opcode != IB_WR_SEND_WITH_IMM)) अणु
			*bad_wr = wr;
			status = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (ocrdma_hwq_मुक्त_cnt(&qp->sq) == 0 ||
		    wr->num_sge > qp->sq.max_sges) अणु
			*bad_wr = wr;
			status = -ENOMEM;
			अवरोध;
		पूर्ण
		hdr = ocrdma_hwq_head(&qp->sq);
		hdr->cw = 0;
		अगर (wr->send_flags & IB_SEND_SIGNALED || qp->संकेतed)
			hdr->cw |= (OCRDMA_FLAG_SIG << OCRDMA_WQE_FLAGS_SHIFT);
		अगर (wr->send_flags & IB_SEND_FENCE)
			hdr->cw |=
			    (OCRDMA_FLAG_FENCE_L << OCRDMA_WQE_FLAGS_SHIFT);
		अगर (wr->send_flags & IB_SEND_SOLICITED)
			hdr->cw |=
			    (OCRDMA_FLAG_SOLICIT << OCRDMA_WQE_FLAGS_SHIFT);
		hdr->total_len = 0;
		चयन (wr->opcode) अणु
		हाल IB_WR_SEND_WITH_IMM:
			hdr->cw |= (OCRDMA_FLAG_IMM << OCRDMA_WQE_FLAGS_SHIFT);
			hdr->immdt = ntohl(wr->ex.imm_data);
			fallthrough;
		हाल IB_WR_SEND:
			hdr->cw |= (OCRDMA_SEND << OCRDMA_WQE_OPCODE_SHIFT);
			ocrdma_build_send(qp, hdr, wr);
			अवरोध;
		हाल IB_WR_SEND_WITH_INV:
			hdr->cw |= (OCRDMA_FLAG_INV << OCRDMA_WQE_FLAGS_SHIFT);
			hdr->cw |= (OCRDMA_SEND << OCRDMA_WQE_OPCODE_SHIFT);
			hdr->lkey = wr->ex.invalidate_rkey;
			status = ocrdma_build_send(qp, hdr, wr);
			अवरोध;
		हाल IB_WR_RDMA_WRITE_WITH_IMM:
			hdr->cw |= (OCRDMA_FLAG_IMM << OCRDMA_WQE_FLAGS_SHIFT);
			hdr->immdt = ntohl(wr->ex.imm_data);
			fallthrough;
		हाल IB_WR_RDMA_WRITE:
			hdr->cw |= (OCRDMA_WRITE << OCRDMA_WQE_OPCODE_SHIFT);
			status = ocrdma_build_ग_लिखो(qp, hdr, wr);
			अवरोध;
		हाल IB_WR_RDMA_READ:
			ocrdma_build_पढ़ो(qp, hdr, wr);
			अवरोध;
		हाल IB_WR_LOCAL_INV:
			hdr->cw |=
			    (OCRDMA_LKEY_INV << OCRDMA_WQE_OPCODE_SHIFT);
			hdr->cw |= ((माप(काष्ठा ocrdma_hdr_wqe) +
					माप(काष्ठा ocrdma_sge)) /
				OCRDMA_WQE_STRIDE) << OCRDMA_WQE_SIZE_SHIFT;
			hdr->lkey = wr->ex.invalidate_rkey;
			अवरोध;
		हाल IB_WR_REG_MR:
			status = ocrdma_build_reg(qp, hdr, reg_wr(wr));
			अवरोध;
		शेष:
			status = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (status) अणु
			*bad_wr = wr;
			अवरोध;
		पूर्ण
		अगर (wr->send_flags & IB_SEND_SIGNALED || qp->संकेतed)
			qp->wqe_wr_id_tbl[qp->sq.head].संकेतed = 1;
		अन्यथा
			qp->wqe_wr_id_tbl[qp->sq.head].संकेतed = 0;
		qp->wqe_wr_id_tbl[qp->sq.head].wrid = wr->wr_id;
		ocrdma_cpu_to_le32(hdr, ((hdr->cw >> OCRDMA_WQE_SIZE_SHIFT) &
				   OCRDMA_WQE_SIZE_MASK) * OCRDMA_WQE_STRIDE);
		/* make sure wqe is written beक्रमe adapter can access it */
		wmb();
		/* inक्रमm hw to start processing it */
		ocrdma_ring_sq_db(qp);

		/* update poपूर्णांकer, counter क्रम next wr */
		ocrdma_hwq_inc_head(&qp->sq);
		wr = wr->next;
	पूर्ण
	spin_unlock_irqrestore(&qp->q_lock, flags);
	वापस status;
पूर्ण

अटल व्योम ocrdma_ring_rq_db(काष्ठा ocrdma_qp *qp)
अणु
	u32 val = qp->rq.dbid | (1 << OCRDMA_DB_RQ_SHIFT);

	ioग_लिखो32(val, qp->rq_db);
पूर्ण

अटल व्योम ocrdma_build_rqe(काष्ठा ocrdma_hdr_wqe *rqe,
			     स्थिर काष्ठा ib_recv_wr *wr, u16 tag)
अणु
	u32 wqe_size = 0;
	काष्ठा ocrdma_sge *sge;
	अगर (wr->num_sge)
		wqe_size = (wr->num_sge * माप(*sge)) + माप(*rqe);
	अन्यथा
		wqe_size = माप(*sge) + माप(*rqe);

	rqe->cw = ((wqe_size / OCRDMA_WQE_STRIDE) <<
				OCRDMA_WQE_SIZE_SHIFT);
	rqe->cw |= (OCRDMA_FLAG_SIG << OCRDMA_WQE_FLAGS_SHIFT);
	rqe->cw |= (OCRDMA_TYPE_LKEY << OCRDMA_WQE_TYPE_SHIFT);
	rqe->total_len = 0;
	rqe->rsvd_tag = tag;
	sge = (काष्ठा ocrdma_sge *)(rqe + 1);
	ocrdma_build_sges(rqe, sge, wr->num_sge, wr->sg_list);
	ocrdma_cpu_to_le32(rqe, wqe_size);
पूर्ण

पूर्णांक ocrdma_post_recv(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_recv_wr *wr,
		     स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	पूर्णांक status = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा ocrdma_qp *qp = get_ocrdma_qp(ibqp);
	काष्ठा ocrdma_hdr_wqe *rqe;

	spin_lock_irqsave(&qp->q_lock, flags);
	अगर (qp->state == OCRDMA_QPS_RST || qp->state == OCRDMA_QPS_ERR) अणु
		spin_unlock_irqrestore(&qp->q_lock, flags);
		*bad_wr = wr;
		वापस -EINVAL;
	पूर्ण
	जबतक (wr) अणु
		अगर (ocrdma_hwq_मुक्त_cnt(&qp->rq) == 0 ||
		    wr->num_sge > qp->rq.max_sges) अणु
			*bad_wr = wr;
			status = -ENOMEM;
			अवरोध;
		पूर्ण
		rqe = ocrdma_hwq_head(&qp->rq);
		ocrdma_build_rqe(rqe, wr, 0);

		qp->rqe_wr_id_tbl[qp->rq.head] = wr->wr_id;
		/* make sure rqe is written beक्रमe adapter can access it */
		wmb();

		/* inक्रमm hw to start processing it */
		ocrdma_ring_rq_db(qp);

		/* update poपूर्णांकer, counter क्रम next wr */
		ocrdma_hwq_inc_head(&qp->rq);
		wr = wr->next;
	पूर्ण
	spin_unlock_irqrestore(&qp->q_lock, flags);
	वापस status;
पूर्ण

/* cqe क्रम srq's rqe can potentially arrive out of order.
 * index gives the entry in the shaकरोw table where to store
 * the wr_id. tag/index is वापसed in cqe to reference back
 * क्रम a given rqe.
 */
अटल पूर्णांक ocrdma_srq_get_idx(काष्ठा ocrdma_srq *srq)
अणु
	पूर्णांक row = 0;
	पूर्णांक indx = 0;

	क्रम (row = 0; row < srq->bit_fields_len; row++) अणु
		अगर (srq->idx_bit_fields[row]) अणु
			indx = ffs(srq->idx_bit_fields[row]);
			indx = (row * 32) + (indx - 1);
			BUG_ON(indx >= srq->rq.max_cnt);
			ocrdma_srq_toggle_bit(srq, indx);
			अवरोध;
		पूर्ण
	पूर्ण

	BUG_ON(row == srq->bit_fields_len);
	वापस indx + 1; /* Use from index 1 */
पूर्ण

अटल व्योम ocrdma_ring_srq_db(काष्ठा ocrdma_srq *srq)
अणु
	u32 val = srq->rq.dbid | (1 << 16);

	ioग_लिखो32(val, srq->db + OCRDMA_DB_GEN2_SRQ_OFFSET);
पूर्ण

पूर्णांक ocrdma_post_srq_recv(काष्ठा ib_srq *ibsrq, स्थिर काष्ठा ib_recv_wr *wr,
			 स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	पूर्णांक status = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा ocrdma_srq *srq;
	काष्ठा ocrdma_hdr_wqe *rqe;
	u16 tag;

	srq = get_ocrdma_srq(ibsrq);

	spin_lock_irqsave(&srq->q_lock, flags);
	जबतक (wr) अणु
		अगर (ocrdma_hwq_मुक्त_cnt(&srq->rq) == 0 ||
		    wr->num_sge > srq->rq.max_sges) अणु
			status = -ENOMEM;
			*bad_wr = wr;
			अवरोध;
		पूर्ण
		tag = ocrdma_srq_get_idx(srq);
		rqe = ocrdma_hwq_head(&srq->rq);
		ocrdma_build_rqe(rqe, wr, tag);

		srq->rqe_wr_id_tbl[tag] = wr->wr_id;
		/* make sure rqe is written beक्रमe adapter can perक्रमm DMA */
		wmb();
		/* inक्रमm hw to start processing it */
		ocrdma_ring_srq_db(srq);
		/* update poपूर्णांकer, counter क्रम next wr */
		ocrdma_hwq_inc_head(&srq->rq);
		wr = wr->next;
	पूर्ण
	spin_unlock_irqrestore(&srq->q_lock, flags);
	वापस status;
पूर्ण

अटल क्रमागत ib_wc_status ocrdma_to_ibwc_err(u16 status)
अणु
	क्रमागत ib_wc_status ibwc_status;

	चयन (status) अणु
	हाल OCRDMA_CQE_GENERAL_ERR:
		ibwc_status = IB_WC_GENERAL_ERR;
		अवरोध;
	हाल OCRDMA_CQE_LOC_LEN_ERR:
		ibwc_status = IB_WC_LOC_LEN_ERR;
		अवरोध;
	हाल OCRDMA_CQE_LOC_QP_OP_ERR:
		ibwc_status = IB_WC_LOC_QP_OP_ERR;
		अवरोध;
	हाल OCRDMA_CQE_LOC_EEC_OP_ERR:
		ibwc_status = IB_WC_LOC_EEC_OP_ERR;
		अवरोध;
	हाल OCRDMA_CQE_LOC_PROT_ERR:
		ibwc_status = IB_WC_LOC_PROT_ERR;
		अवरोध;
	हाल OCRDMA_CQE_WR_FLUSH_ERR:
		ibwc_status = IB_WC_WR_FLUSH_ERR;
		अवरोध;
	हाल OCRDMA_CQE_MW_BIND_ERR:
		ibwc_status = IB_WC_MW_BIND_ERR;
		अवरोध;
	हाल OCRDMA_CQE_BAD_RESP_ERR:
		ibwc_status = IB_WC_BAD_RESP_ERR;
		अवरोध;
	हाल OCRDMA_CQE_LOC_ACCESS_ERR:
		ibwc_status = IB_WC_LOC_ACCESS_ERR;
		अवरोध;
	हाल OCRDMA_CQE_REM_INV_REQ_ERR:
		ibwc_status = IB_WC_REM_INV_REQ_ERR;
		अवरोध;
	हाल OCRDMA_CQE_REM_ACCESS_ERR:
		ibwc_status = IB_WC_REM_ACCESS_ERR;
		अवरोध;
	हाल OCRDMA_CQE_REM_OP_ERR:
		ibwc_status = IB_WC_REM_OP_ERR;
		अवरोध;
	हाल OCRDMA_CQE_RETRY_EXC_ERR:
		ibwc_status = IB_WC_RETRY_EXC_ERR;
		अवरोध;
	हाल OCRDMA_CQE_RNR_RETRY_EXC_ERR:
		ibwc_status = IB_WC_RNR_RETRY_EXC_ERR;
		अवरोध;
	हाल OCRDMA_CQE_LOC_RDD_VIOL_ERR:
		ibwc_status = IB_WC_LOC_RDD_VIOL_ERR;
		अवरोध;
	हाल OCRDMA_CQE_REM_INV_RD_REQ_ERR:
		ibwc_status = IB_WC_REM_INV_RD_REQ_ERR;
		अवरोध;
	हाल OCRDMA_CQE_REM_ABORT_ERR:
		ibwc_status = IB_WC_REM_ABORT_ERR;
		अवरोध;
	हाल OCRDMA_CQE_INV_EECN_ERR:
		ibwc_status = IB_WC_INV_EECN_ERR;
		अवरोध;
	हाल OCRDMA_CQE_INV_EEC_STATE_ERR:
		ibwc_status = IB_WC_INV_EEC_STATE_ERR;
		अवरोध;
	हाल OCRDMA_CQE_FATAL_ERR:
		ibwc_status = IB_WC_FATAL_ERR;
		अवरोध;
	हाल OCRDMA_CQE_RESP_TIMEOUT_ERR:
		ibwc_status = IB_WC_RESP_TIMEOUT_ERR;
		अवरोध;
	शेष:
		ibwc_status = IB_WC_GENERAL_ERR;
		अवरोध;
	पूर्ण
	वापस ibwc_status;
पूर्ण

अटल व्योम ocrdma_update_wc(काष्ठा ocrdma_qp *qp, काष्ठा ib_wc *ibwc,
		      u32 wqe_idx)
अणु
	काष्ठा ocrdma_hdr_wqe *hdr;
	काष्ठा ocrdma_sge *rw;
	पूर्णांक opcode;

	hdr = ocrdma_hwq_head_from_idx(&qp->sq, wqe_idx);

	ibwc->wr_id = qp->wqe_wr_id_tbl[wqe_idx].wrid;
	/* Unकरो the hdr->cw swap */
	opcode = le32_to_cpu(hdr->cw) & OCRDMA_WQE_OPCODE_MASK;
	चयन (opcode) अणु
	हाल OCRDMA_WRITE:
		ibwc->opcode = IB_WC_RDMA_WRITE;
		अवरोध;
	हाल OCRDMA_READ:
		rw = (काष्ठा ocrdma_sge *)(hdr + 1);
		ibwc->opcode = IB_WC_RDMA_READ;
		ibwc->byte_len = rw->len;
		अवरोध;
	हाल OCRDMA_SEND:
		ibwc->opcode = IB_WC_SEND;
		अवरोध;
	हाल OCRDMA_FR_MR:
		ibwc->opcode = IB_WC_REG_MR;
		अवरोध;
	हाल OCRDMA_LKEY_INV:
		ibwc->opcode = IB_WC_LOCAL_INV;
		अवरोध;
	शेष:
		ibwc->status = IB_WC_GENERAL_ERR;
		pr_err("%s() invalid opcode received = 0x%x\n",
		       __func__, hdr->cw & OCRDMA_WQE_OPCODE_MASK);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ocrdma_set_cqe_status_flushed(काष्ठा ocrdma_qp *qp,
						काष्ठा ocrdma_cqe *cqe)
अणु
	अगर (is_cqe_क्रम_sq(cqe)) अणु
		cqe->flags_status_srcqpn = cpu_to_le32(le32_to_cpu(
				cqe->flags_status_srcqpn) &
					~OCRDMA_CQE_STATUS_MASK);
		cqe->flags_status_srcqpn = cpu_to_le32(le32_to_cpu(
				cqe->flags_status_srcqpn) |
				(OCRDMA_CQE_WR_FLUSH_ERR <<
					OCRDMA_CQE_STATUS_SHIFT));
	पूर्ण अन्यथा अणु
		अगर (qp->qp_type == IB_QPT_UD || qp->qp_type == IB_QPT_GSI) अणु
			cqe->flags_status_srcqpn = cpu_to_le32(le32_to_cpu(
					cqe->flags_status_srcqpn) &
						~OCRDMA_CQE_UD_STATUS_MASK);
			cqe->flags_status_srcqpn = cpu_to_le32(le32_to_cpu(
					cqe->flags_status_srcqpn) |
					(OCRDMA_CQE_WR_FLUSH_ERR <<
						OCRDMA_CQE_UD_STATUS_SHIFT));
		पूर्ण अन्यथा अणु
			cqe->flags_status_srcqpn = cpu_to_le32(le32_to_cpu(
					cqe->flags_status_srcqpn) &
						~OCRDMA_CQE_STATUS_MASK);
			cqe->flags_status_srcqpn = cpu_to_le32(le32_to_cpu(
					cqe->flags_status_srcqpn) |
					(OCRDMA_CQE_WR_FLUSH_ERR <<
						OCRDMA_CQE_STATUS_SHIFT));
		पूर्ण
	पूर्ण
पूर्ण

अटल bool ocrdma_update_err_cqe(काष्ठा ib_wc *ibwc, काष्ठा ocrdma_cqe *cqe,
				  काष्ठा ocrdma_qp *qp, पूर्णांक status)
अणु
	bool expand = false;

	ibwc->byte_len = 0;
	ibwc->qp = &qp->ibqp;
	ibwc->status = ocrdma_to_ibwc_err(status);

	ocrdma_flush_qp(qp);
	ocrdma_qp_state_change(qp, IB_QPS_ERR, शून्य);

	/* अगर wqe/rqe pending क्रम which cqe needs to be वापसed,
	 * trigger inflating it.
	 */
	अगर (!is_hw_rq_empty(qp) || !is_hw_sq_empty(qp)) अणु
		expand = true;
		ocrdma_set_cqe_status_flushed(qp, cqe);
	पूर्ण
	वापस expand;
पूर्ण

अटल पूर्णांक ocrdma_update_err_rcqe(काष्ठा ib_wc *ibwc, काष्ठा ocrdma_cqe *cqe,
				  काष्ठा ocrdma_qp *qp, पूर्णांक status)
अणु
	ibwc->opcode = IB_WC_RECV;
	ibwc->wr_id = qp->rqe_wr_id_tbl[qp->rq.tail];
	ocrdma_hwq_inc_tail(&qp->rq);

	वापस ocrdma_update_err_cqe(ibwc, cqe, qp, status);
पूर्ण

अटल पूर्णांक ocrdma_update_err_scqe(काष्ठा ib_wc *ibwc, काष्ठा ocrdma_cqe *cqe,
				  काष्ठा ocrdma_qp *qp, पूर्णांक status)
अणु
	ocrdma_update_wc(qp, ibwc, qp->sq.tail);
	ocrdma_hwq_inc_tail(&qp->sq);

	वापस ocrdma_update_err_cqe(ibwc, cqe, qp, status);
पूर्ण


अटल bool ocrdma_poll_err_scqe(काष्ठा ocrdma_qp *qp,
				 काष्ठा ocrdma_cqe *cqe, काष्ठा ib_wc *ibwc,
				 bool *polled, bool *stop)
अणु
	bool expand;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(qp->ibqp.device);
	पूर्णांक status = (le32_to_cpu(cqe->flags_status_srcqpn) &
		OCRDMA_CQE_STATUS_MASK) >> OCRDMA_CQE_STATUS_SHIFT;
	अगर (status < OCRDMA_MAX_CQE_ERR)
		atomic_inc(&dev->cqe_err_stats[status]);

	/* when hw sq is empty, but rq is not empty, so we जारी
	 * to keep the cqe in order to get the cq event again.
	 */
	अगर (is_hw_sq_empty(qp) && !is_hw_rq_empty(qp)) अणु
		/* when cq क्रम rq and sq is same, it is safe to वापस
		 * flush cqe क्रम RQEs.
		 */
		अगर (!qp->srq && (qp->sq_cq == qp->rq_cq)) अणु
			*polled = true;
			status = OCRDMA_CQE_WR_FLUSH_ERR;
			expand = ocrdma_update_err_rcqe(ibwc, cqe, qp, status);
		पूर्ण अन्यथा अणु
			/* stop processing further cqe as this cqe is used क्रम
			 * triggering cq event on buddy cq of RQ.
			 * When QP is destroyed, this cqe will be हटाओd
			 * from the cq's hardware q.
			 */
			*polled = false;
			*stop = true;
			expand = false;
		पूर्ण
	पूर्ण अन्यथा अगर (is_hw_sq_empty(qp)) अणु
		/* Do nothing */
		expand = false;
		*polled = false;
		*stop = false;
	पूर्ण अन्यथा अणु
		*polled = true;
		expand = ocrdma_update_err_scqe(ibwc, cqe, qp, status);
	पूर्ण
	वापस expand;
पूर्ण

अटल bool ocrdma_poll_success_scqe(काष्ठा ocrdma_qp *qp,
				     काष्ठा ocrdma_cqe *cqe,
				     काष्ठा ib_wc *ibwc, bool *polled)
अणु
	bool expand = false;
	पूर्णांक tail = qp->sq.tail;
	u32 wqe_idx;

	अगर (!qp->wqe_wr_id_tbl[tail].संकेतed) अणु
		*polled = false;    /* WC cannot be consumed yet */
	पूर्ण अन्यथा अणु
		ibwc->status = IB_WC_SUCCESS;
		ibwc->wc_flags = 0;
		ibwc->qp = &qp->ibqp;
		ocrdma_update_wc(qp, ibwc, tail);
		*polled = true;
	पूर्ण
	wqe_idx = (le32_to_cpu(cqe->wq.wqeidx) &
			OCRDMA_CQE_WQEIDX_MASK) & qp->sq.max_wqe_idx;
	अगर (tail != wqe_idx)
		expand = true; /* Coalesced CQE can't be consumed yet */

	ocrdma_hwq_inc_tail(&qp->sq);
	वापस expand;
पूर्ण

अटल bool ocrdma_poll_scqe(काष्ठा ocrdma_qp *qp, काष्ठा ocrdma_cqe *cqe,
			     काष्ठा ib_wc *ibwc, bool *polled, bool *stop)
अणु
	पूर्णांक status;
	bool expand;

	status = (le32_to_cpu(cqe->flags_status_srcqpn) &
		OCRDMA_CQE_STATUS_MASK) >> OCRDMA_CQE_STATUS_SHIFT;

	अगर (status == OCRDMA_CQE_SUCCESS)
		expand = ocrdma_poll_success_scqe(qp, cqe, ibwc, polled);
	अन्यथा
		expand = ocrdma_poll_err_scqe(qp, cqe, ibwc, polled, stop);
	वापस expand;
पूर्ण

अटल पूर्णांक ocrdma_update_ud_rcqe(काष्ठा ocrdma_dev *dev, काष्ठा ib_wc *ibwc,
				 काष्ठा ocrdma_cqe *cqe)
अणु
	पूर्णांक status;
	u16 hdr_type = 0;

	status = (le32_to_cpu(cqe->flags_status_srcqpn) &
		OCRDMA_CQE_UD_STATUS_MASK) >> OCRDMA_CQE_UD_STATUS_SHIFT;
	ibwc->src_qp = le32_to_cpu(cqe->flags_status_srcqpn) &
						OCRDMA_CQE_SRCQP_MASK;
	ibwc->pkey_index = 0;
	ibwc->wc_flags = IB_WC_GRH;
	ibwc->byte_len = (le32_to_cpu(cqe->ud.rxlen_pkey) >>
			  OCRDMA_CQE_UD_XFER_LEN_SHIFT) &
			  OCRDMA_CQE_UD_XFER_LEN_MASK;

	अगर (ocrdma_is_udp_encap_supported(dev)) अणु
		hdr_type = (le32_to_cpu(cqe->ud.rxlen_pkey) >>
			    OCRDMA_CQE_UD_L3TYPE_SHIFT) &
			    OCRDMA_CQE_UD_L3TYPE_MASK;
		ibwc->wc_flags |= IB_WC_WITH_NETWORK_HDR_TYPE;
		ibwc->network_hdr_type = hdr_type;
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम ocrdma_update_मुक्त_srq_cqe(काष्ठा ib_wc *ibwc,
				       काष्ठा ocrdma_cqe *cqe,
				       काष्ठा ocrdma_qp *qp)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ocrdma_srq *srq;
	u32 wqe_idx;

	srq = get_ocrdma_srq(qp->ibqp.srq);
	wqe_idx = (le32_to_cpu(cqe->rq.buftag_qpn) >>
		OCRDMA_CQE_BUFTAG_SHIFT) & srq->rq.max_wqe_idx;
	BUG_ON(wqe_idx < 1);

	ibwc->wr_id = srq->rqe_wr_id_tbl[wqe_idx];
	spin_lock_irqsave(&srq->q_lock, flags);
	ocrdma_srq_toggle_bit(srq, wqe_idx - 1);
	spin_unlock_irqrestore(&srq->q_lock, flags);
	ocrdma_hwq_inc_tail(&srq->rq);
पूर्ण

अटल bool ocrdma_poll_err_rcqe(काष्ठा ocrdma_qp *qp, काष्ठा ocrdma_cqe *cqe,
				काष्ठा ib_wc *ibwc, bool *polled, bool *stop,
				पूर्णांक status)
अणु
	bool expand;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(qp->ibqp.device);

	अगर (status < OCRDMA_MAX_CQE_ERR)
		atomic_inc(&dev->cqe_err_stats[status]);

	/* when hw_rq is empty, but wq is not empty, so जारी
	 * to keep the cqe to get the cq event again.
	 */
	अगर (is_hw_rq_empty(qp) && !is_hw_sq_empty(qp)) अणु
		अगर (!qp->srq && (qp->sq_cq == qp->rq_cq)) अणु
			*polled = true;
			status = OCRDMA_CQE_WR_FLUSH_ERR;
			expand = ocrdma_update_err_scqe(ibwc, cqe, qp, status);
		पूर्ण अन्यथा अणु
			*polled = false;
			*stop = true;
			expand = false;
		पूर्ण
	पूर्ण अन्यथा अगर (is_hw_rq_empty(qp)) अणु
		/* Do nothing */
		expand = false;
		*polled = false;
		*stop = false;
	पूर्ण अन्यथा अणु
		*polled = true;
		expand = ocrdma_update_err_rcqe(ibwc, cqe, qp, status);
	पूर्ण
	वापस expand;
पूर्ण

अटल व्योम ocrdma_poll_success_rcqe(काष्ठा ocrdma_qp *qp,
				     काष्ठा ocrdma_cqe *cqe, काष्ठा ib_wc *ibwc)
अणु
	काष्ठा ocrdma_dev *dev;

	dev = get_ocrdma_dev(qp->ibqp.device);
	ibwc->opcode = IB_WC_RECV;
	ibwc->qp = &qp->ibqp;
	ibwc->status = IB_WC_SUCCESS;

	अगर (qp->qp_type == IB_QPT_UD || qp->qp_type == IB_QPT_GSI)
		ocrdma_update_ud_rcqe(dev, ibwc, cqe);
	अन्यथा
		ibwc->byte_len = le32_to_cpu(cqe->rq.rxlen);

	अगर (is_cqe_imm(cqe)) अणु
		ibwc->ex.imm_data = htonl(le32_to_cpu(cqe->rq.lkey_immdt));
		ibwc->wc_flags |= IB_WC_WITH_IMM;
	पूर्ण अन्यथा अगर (is_cqe_wr_imm(cqe)) अणु
		ibwc->opcode = IB_WC_RECV_RDMA_WITH_IMM;
		ibwc->ex.imm_data = htonl(le32_to_cpu(cqe->rq.lkey_immdt));
		ibwc->wc_flags |= IB_WC_WITH_IMM;
	पूर्ण अन्यथा अगर (is_cqe_invalidated(cqe)) अणु
		ibwc->ex.invalidate_rkey = le32_to_cpu(cqe->rq.lkey_immdt);
		ibwc->wc_flags |= IB_WC_WITH_INVALIDATE;
	पूर्ण
	अगर (qp->ibqp.srq) अणु
		ocrdma_update_मुक्त_srq_cqe(ibwc, cqe, qp);
	पूर्ण अन्यथा अणु
		ibwc->wr_id = qp->rqe_wr_id_tbl[qp->rq.tail];
		ocrdma_hwq_inc_tail(&qp->rq);
	पूर्ण
पूर्ण

अटल bool ocrdma_poll_rcqe(काष्ठा ocrdma_qp *qp, काष्ठा ocrdma_cqe *cqe,
			     काष्ठा ib_wc *ibwc, bool *polled, bool *stop)
अणु
	पूर्णांक status;
	bool expand = false;

	ibwc->wc_flags = 0;
	अगर (qp->qp_type == IB_QPT_UD || qp->qp_type == IB_QPT_GSI) अणु
		status = (le32_to_cpu(cqe->flags_status_srcqpn) &
					OCRDMA_CQE_UD_STATUS_MASK) >>
					OCRDMA_CQE_UD_STATUS_SHIFT;
	पूर्ण अन्यथा अणु
		status = (le32_to_cpu(cqe->flags_status_srcqpn) &
			     OCRDMA_CQE_STATUS_MASK) >> OCRDMA_CQE_STATUS_SHIFT;
	पूर्ण

	अगर (status == OCRDMA_CQE_SUCCESS) अणु
		*polled = true;
		ocrdma_poll_success_rcqe(qp, cqe, ibwc);
	पूर्ण अन्यथा अणु
		expand = ocrdma_poll_err_rcqe(qp, cqe, ibwc, polled, stop,
					      status);
	पूर्ण
	वापस expand;
पूर्ण

अटल व्योम ocrdma_change_cq_phase(काष्ठा ocrdma_cq *cq, काष्ठा ocrdma_cqe *cqe,
				   u16 cur_getp)
अणु
	अगर (cq->phase_change) अणु
		अगर (cur_getp == 0)
			cq->phase = (~cq->phase & OCRDMA_CQE_VALID);
	पूर्ण अन्यथा अणु
		/* clear valid bit */
		cqe->flags_status_srcqpn = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ocrdma_poll_hwcq(काष्ठा ocrdma_cq *cq, पूर्णांक num_entries,
			    काष्ठा ib_wc *ibwc)
अणु
	u16 qpn = 0;
	पूर्णांक i = 0;
	bool expand = false;
	पूर्णांक polled_hw_cqes = 0;
	काष्ठा ocrdma_qp *qp = शून्य;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(cq->ibcq.device);
	काष्ठा ocrdma_cqe *cqe;
	u16 cur_getp; bool polled = false; bool stop = false;

	cur_getp = cq->getp;
	जबतक (num_entries) अणु
		cqe = cq->va + cur_getp;
		/* check whether valid cqe or not */
		अगर (!is_cqe_valid(cq, cqe))
			अवरोध;
		qpn = (le32_to_cpu(cqe->cmn.qpn) & OCRDMA_CQE_QPN_MASK);
		/* ignore discarded cqe */
		अगर (qpn == 0)
			जाओ skip_cqe;
		qp = dev->qp_tbl[qpn];
		BUG_ON(qp == शून्य);

		अगर (is_cqe_क्रम_sq(cqe)) अणु
			expand = ocrdma_poll_scqe(qp, cqe, ibwc, &polled,
						  &stop);
		पूर्ण अन्यथा अणु
			expand = ocrdma_poll_rcqe(qp, cqe, ibwc, &polled,
						  &stop);
		पूर्ण
		अगर (expand)
			जाओ expand_cqe;
		अगर (stop)
			जाओ stop_cqe;
		/* clear qpn to aव्योम duplicate processing by discard_cqe() */
		cqe->cmn.qpn = 0;
skip_cqe:
		polled_hw_cqes += 1;
		cur_getp = (cur_getp + 1) % cq->max_hw_cqe;
		ocrdma_change_cq_phase(cq, cqe, cur_getp);
expand_cqe:
		अगर (polled) अणु
			num_entries -= 1;
			i += 1;
			ibwc = ibwc + 1;
			polled = false;
		पूर्ण
	पूर्ण
stop_cqe:
	cq->getp = cur_getp;

	अगर (polled_hw_cqes)
		ocrdma_ring_cq_db(dev, cq->id, false, false, polled_hw_cqes);

	वापस i;
पूर्ण

/* insert error cqe अगर the QP's SQ or RQ's CQ matches the CQ under poll. */
अटल पूर्णांक ocrdma_add_err_cqe(काष्ठा ocrdma_cq *cq, पूर्णांक num_entries,
			      काष्ठा ocrdma_qp *qp, काष्ठा ib_wc *ibwc)
अणु
	पूर्णांक err_cqes = 0;

	जबतक (num_entries) अणु
		अगर (is_hw_sq_empty(qp) && is_hw_rq_empty(qp))
			अवरोध;
		अगर (!is_hw_sq_empty(qp) && qp->sq_cq == cq) अणु
			ocrdma_update_wc(qp, ibwc, qp->sq.tail);
			ocrdma_hwq_inc_tail(&qp->sq);
		पूर्ण अन्यथा अगर (!is_hw_rq_empty(qp) && qp->rq_cq == cq) अणु
			ibwc->wr_id = qp->rqe_wr_id_tbl[qp->rq.tail];
			ocrdma_hwq_inc_tail(&qp->rq);
		पूर्ण अन्यथा अणु
			वापस err_cqes;
		पूर्ण
		ibwc->byte_len = 0;
		ibwc->status = IB_WC_WR_FLUSH_ERR;
		ibwc = ibwc + 1;
		err_cqes += 1;
		num_entries -= 1;
	पूर्ण
	वापस err_cqes;
पूर्ण

पूर्णांक ocrdma_poll_cq(काष्ठा ib_cq *ibcq, पूर्णांक num_entries, काष्ठा ib_wc *wc)
अणु
	पूर्णांक cqes_to_poll = num_entries;
	काष्ठा ocrdma_cq *cq = get_ocrdma_cq(ibcq);
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(ibcq->device);
	पूर्णांक num_os_cqe = 0, err_cqes = 0;
	काष्ठा ocrdma_qp *qp;
	अचिन्हित दीर्घ flags;

	/* poll cqes from adapter CQ */
	spin_lock_irqsave(&cq->cq_lock, flags);
	num_os_cqe = ocrdma_poll_hwcq(cq, cqes_to_poll, wc);
	spin_unlock_irqrestore(&cq->cq_lock, flags);
	cqes_to_poll -= num_os_cqe;

	अगर (cqes_to_poll) अणु
		wc = wc + num_os_cqe;
		/* adapter वापसs single error cqe when qp moves to
		 * error state. So insert error cqes with wc_status as
		 * FLUSHED क्रम pending WQEs and RQEs of QP's SQ and RQ
		 * respectively which uses this CQ.
		 */
		spin_lock_irqsave(&dev->flush_q_lock, flags);
		list_क्रम_each_entry(qp, &cq->sq_head, sq_entry) अणु
			अगर (cqes_to_poll == 0)
				अवरोध;
			err_cqes = ocrdma_add_err_cqe(cq, cqes_to_poll, qp, wc);
			cqes_to_poll -= err_cqes;
			num_os_cqe += err_cqes;
			wc = wc + err_cqes;
		पूर्ण
		spin_unlock_irqrestore(&dev->flush_q_lock, flags);
	पूर्ण
	वापस num_os_cqe;
पूर्ण

पूर्णांक ocrdma_arm_cq(काष्ठा ib_cq *ibcq, क्रमागत ib_cq_notअगरy_flags cq_flags)
अणु
	काष्ठा ocrdma_cq *cq = get_ocrdma_cq(ibcq);
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(ibcq->device);
	u16 cq_id;
	अचिन्हित दीर्घ flags;
	bool arm_needed = false, sol_needed = false;

	cq_id = cq->id;

	spin_lock_irqsave(&cq->cq_lock, flags);
	अगर (cq_flags & IB_CQ_NEXT_COMP || cq_flags & IB_CQ_SOLICITED)
		arm_needed = true;
	अगर (cq_flags & IB_CQ_SOLICITED)
		sol_needed = true;

	ocrdma_ring_cq_db(dev, cq_id, arm_needed, sol_needed, 0);
	spin_unlock_irqrestore(&cq->cq_lock, flags);

	वापस 0;
पूर्ण

काष्ठा ib_mr *ocrdma_alloc_mr(काष्ठा ib_pd *ibpd, क्रमागत ib_mr_type mr_type,
			      u32 max_num_sg)
अणु
	पूर्णांक status;
	काष्ठा ocrdma_mr *mr;
	काष्ठा ocrdma_pd *pd = get_ocrdma_pd(ibpd);
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(ibpd->device);

	अगर (mr_type != IB_MR_TYPE_MEM_REG)
		वापस ERR_PTR(-EINVAL);

	अगर (max_num_sg > dev->attr.max_pages_per_frmr)
		वापस ERR_PTR(-EINVAL);

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	mr->pages = kसुस्मृति(max_num_sg, माप(u64), GFP_KERNEL);
	अगर (!mr->pages) अणु
		status = -ENOMEM;
		जाओ pl_err;
	पूर्ण

	status = ocrdma_get_pbl_info(dev, mr, max_num_sg);
	अगर (status)
		जाओ pbl_err;
	mr->hwmr.fr_mr = 1;
	mr->hwmr.remote_rd = 0;
	mr->hwmr.remote_wr = 0;
	mr->hwmr.local_rd = 0;
	mr->hwmr.local_wr = 0;
	mr->hwmr.mw_bind = 0;
	status = ocrdma_build_pbl_tbl(dev, &mr->hwmr);
	अगर (status)
		जाओ pbl_err;
	status = ocrdma_reg_mr(dev, &mr->hwmr, pd->id, 0);
	अगर (status)
		जाओ mbx_err;
	mr->ibmr.rkey = mr->hwmr.lkey;
	mr->ibmr.lkey = mr->hwmr.lkey;
	dev->stag_arr[(mr->hwmr.lkey >> 8) & (OCRDMA_MAX_STAG - 1)] =
		(अचिन्हित दीर्घ) mr;
	वापस &mr->ibmr;
mbx_err:
	ocrdma_मुक्त_mr_pbl_tbl(dev, &mr->hwmr);
pbl_err:
	kमुक्त(mr->pages);
pl_err:
	kमुक्त(mr);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल पूर्णांक ocrdma_set_page(काष्ठा ib_mr *ibmr, u64 addr)
अणु
	काष्ठा ocrdma_mr *mr = get_ocrdma_mr(ibmr);

	अगर (unlikely(mr->npages == mr->hwmr.num_pbes))
		वापस -ENOMEM;

	mr->pages[mr->npages++] = addr;

	वापस 0;
पूर्ण

पूर्णांक ocrdma_map_mr_sg(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *sg, पूर्णांक sg_nents,
		     अचिन्हित पूर्णांक *sg_offset)
अणु
	काष्ठा ocrdma_mr *mr = get_ocrdma_mr(ibmr);

	mr->npages = 0;

	वापस ib_sg_to_pages(ibmr, sg, sg_nents, sg_offset, ocrdma_set_page);
पूर्ण
