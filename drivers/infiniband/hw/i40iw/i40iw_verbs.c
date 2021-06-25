<शैली गुरु>
/*******************************************************************************
*
* Copyright (c) 2015-2016 Intel Corporation.  All rights reserved.
*
* This software is available to you under a choice of one of two
* licenses.  You may choose to be licensed under the terms of the GNU
* General Public License (GPL) Version 2, available from the file
* COPYING in the मुख्य directory of this source tree, or the
* OpenFabrics.org BSD license below:
*
*   Redistribution and use in source and binary क्रमms, with or
*   without modअगरication, are permitted provided that the following
*   conditions are met:
*
*    - Redistributions of source code must retain the above
*	copyright notice, this list of conditions and the following
*	disclaimer.
*
*    - Redistributions in binary क्रमm must reproduce the above
*	copyright notice, this list of conditions and the following
*	disclaimer in the करोcumentation and/or other materials
*	provided with the distribution.
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
*******************************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/समय.स>
#समावेश <linux/hugetlb.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <net/ip.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/iw_cm.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/uverbs_ioctl.h>
#समावेश "i40iw.h"

/**
 * i40iw_query_device - get device attributes
 * @ibdev: device poपूर्णांकer from stack
 * @props: वापसing device attributes
 * @udata: user data
 */
अटल पूर्णांक i40iw_query_device(काष्ठा ib_device *ibdev,
			      काष्ठा ib_device_attr *props,
			      काष्ठा ib_udata *udata)
अणु
	काष्ठा i40iw_device *iwdev = to_iwdev(ibdev);

	अगर (udata->inlen || udata->outlen)
		वापस -EINVAL;
	स_रखो(props, 0, माप(*props));
	ether_addr_copy((u8 *)&props->sys_image_guid, iwdev->netdev->dev_addr);
	props->fw_ver = i40iw_fw_major_ver(&iwdev->sc_dev) << 32 |
			i40iw_fw_minor_ver(&iwdev->sc_dev);
	props->device_cap_flags = iwdev->device_cap_flags;
	props->venकरोr_id = iwdev->ldev->pcidev->venकरोr;
	props->venकरोr_part_id = iwdev->ldev->pcidev->device;
	props->hw_ver = (u32)iwdev->sc_dev.hw_rev;
	props->max_mr_size = I40IW_MAX_OUTBOUND_MESSAGE_SIZE;
	props->max_qp = iwdev->max_qp - iwdev->used_qps;
	props->max_qp_wr = I40IW_MAX_QP_WRS;
	props->max_send_sge = I40IW_MAX_WQ_FRAGMENT_COUNT;
	props->max_recv_sge = I40IW_MAX_WQ_FRAGMENT_COUNT;
	props->max_cq = iwdev->max_cq - iwdev->used_cqs;
	props->max_cqe = iwdev->max_cqe;
	props->max_mr = iwdev->max_mr - iwdev->used_mrs;
	props->max_pd = iwdev->max_pd - iwdev->used_pds;
	props->max_sge_rd = I40IW_MAX_SGE_RD;
	props->max_qp_rd_atom = I40IW_MAX_IRD_SIZE;
	props->max_qp_init_rd_atom = props->max_qp_rd_atom;
	props->atomic_cap = IB_ATOMIC_NONE;
	props->max_fast_reg_page_list_len = I40IW_MAX_PAGES_PER_FMR;
	वापस 0;
पूर्ण

/**
 * i40iw_query_port - get port attrubutes
 * @ibdev: device poपूर्णांकer from stack
 * @port: port number क्रम query
 * @props: वापसing device attributes
 */
अटल पूर्णांक i40iw_query_port(काष्ठा ib_device *ibdev,
			    u32 port,
			    काष्ठा ib_port_attr *props)
अणु
	props->lid = 1;
	props->port_cap_flags = IB_PORT_CM_SUP | IB_PORT_REINIT_SUP |
		IB_PORT_VENDOR_CLASS_SUP | IB_PORT_BOOT_MGMT_SUP;
	props->gid_tbl_len = 1;
	props->active_width = IB_WIDTH_4X;
	props->active_speed = 1;
	props->max_msg_sz = I40IW_MAX_OUTBOUND_MESSAGE_SIZE;
	वापस 0;
पूर्ण

/**
 * i40iw_alloc_ucontext - Allocate the user context data काष्ठाure
 * @uctx: Uverbs context poपूर्णांकer from stack
 * @udata: user data
 *
 * This keeps track of all objects associated with a particular
 * user-mode client.
 */
अटल पूर्णांक i40iw_alloc_ucontext(काष्ठा ib_ucontext *uctx,
				काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = uctx->device;
	काष्ठा i40iw_device *iwdev = to_iwdev(ibdev);
	काष्ठा i40iw_alloc_ucontext_req req;
	काष्ठा i40iw_alloc_ucontext_resp uresp = अणुपूर्ण;
	काष्ठा i40iw_ucontext *ucontext = to_ucontext(uctx);

	अगर (ib_copy_from_udata(&req, udata, माप(req)))
		वापस -EINVAL;

	अगर (req.userspace_ver < 4 || req.userspace_ver > I40IW_ABI_VER) अणु
		i40iw_pr_err("Unsupported provider library version %u.\n", req.userspace_ver);
		वापस -EINVAL;
	पूर्ण

	uresp.max_qps = iwdev->max_qp;
	uresp.max_pds = iwdev->max_pd;
	uresp.wq_size = iwdev->max_qp_wr * 2;
	uresp.kernel_ver = req.userspace_ver;

	ucontext->iwdev = iwdev;
	ucontext->abi_ver = req.userspace_ver;

	अगर (ib_copy_to_udata(udata, &uresp, माप(uresp)))
		वापस -EFAULT;

	INIT_LIST_HEAD(&ucontext->cq_reg_mem_list);
	spin_lock_init(&ucontext->cq_reg_mem_list_lock);
	INIT_LIST_HEAD(&ucontext->qp_reg_mem_list);
	spin_lock_init(&ucontext->qp_reg_mem_list_lock);

	वापस 0;
पूर्ण

/**
 * i40iw_dealloc_ucontext - deallocate the user context data काष्ठाure
 * @context: user context created during alloc
 */
अटल व्योम i40iw_dealloc_ucontext(काष्ठा ib_ucontext *context)
अणु
	वापस;
पूर्ण

/**
 * i40iw_mmap - user memory map
 * @context: context created during alloc
 * @vma: kernel info क्रम user memory map
 */
अटल पूर्णांक i40iw_mmap(काष्ठा ib_ucontext *context, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा i40iw_ucontext *ucontext = to_ucontext(context);
	u64 dbaddr;

	अगर (vma->vm_pgoff || vma->vm_end - vma->vm_start != PAGE_SIZE)
		वापस -EINVAL;

	dbaddr = I40IW_DB_ADDR_OFFSET + pci_resource_start(ucontext->iwdev->ldev->pcidev, 0);

	वापस rdma_user_mmap_io(context, vma, dbaddr >> PAGE_SHIFT, PAGE_SIZE,
				 pgprot_noncached(vma->vm_page_prot), शून्य);
पूर्ण

/**
 * i40iw_alloc_pd - allocate protection करोमुख्य
 * @pd: PD poपूर्णांकer
 * @udata: user data
 */
अटल पूर्णांक i40iw_alloc_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata)
अणु
	काष्ठा i40iw_pd *iwpd = to_iwpd(pd);
	काष्ठा i40iw_device *iwdev = to_iwdev(pd->device);
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	काष्ठा i40iw_alloc_pd_resp uresp;
	काष्ठा i40iw_sc_pd *sc_pd;
	u32 pd_id = 0;
	पूर्णांक err;

	अगर (iwdev->closing)
		वापस -ENODEV;

	err = i40iw_alloc_resource(iwdev, iwdev->allocated_pds,
				   iwdev->max_pd, &pd_id, &iwdev->next_pd);
	अगर (err) अणु
		i40iw_pr_err("alloc resource failed\n");
		वापस err;
	पूर्ण

	sc_pd = &iwpd->sc_pd;

	अगर (udata) अणु
		काष्ठा i40iw_ucontext *ucontext = rdma_udata_to_drv_context(
			udata, काष्ठा i40iw_ucontext, ibucontext);
		dev->iw_pd_ops->pd_init(dev, sc_pd, pd_id, ucontext->abi_ver);
		स_रखो(&uresp, 0, माप(uresp));
		uresp.pd_id = pd_id;
		अगर (ib_copy_to_udata(udata, &uresp, माप(uresp))) अणु
			err = -EFAULT;
			जाओ error;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev->iw_pd_ops->pd_init(dev, sc_pd, pd_id, -1);
	पूर्ण

	i40iw_add_pdusecount(iwpd);
	वापस 0;

error:
	i40iw_मुक्त_resource(iwdev, iwdev->allocated_pds, pd_id);
	वापस err;
पूर्ण

/**
 * i40iw_dealloc_pd - deallocate pd
 * @ibpd: ptr of pd to be deallocated
 * @udata: user data or null क्रम kernel object
 */
अटल पूर्णांक i40iw_dealloc_pd(काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata)
अणु
	काष्ठा i40iw_pd *iwpd = to_iwpd(ibpd);
	काष्ठा i40iw_device *iwdev = to_iwdev(ibpd->device);

	i40iw_rem_pdusecount(iwpd, iwdev);
	वापस 0;
पूर्ण

/**
 * i40iw_get_pbl - Retrieve pbl from a list given a भव
 * address
 * @va: user भव address
 * @pbl_list: pbl list to search in (QP's or CQ's)
 */
अटल काष्ठा i40iw_pbl *i40iw_get_pbl(अचिन्हित दीर्घ va,
				       काष्ठा list_head *pbl_list)
अणु
	काष्ठा i40iw_pbl *iwpbl;

	list_क्रम_each_entry(iwpbl, pbl_list, list) अणु
		अगर (iwpbl->user_base == va) अणु
			iwpbl->on_list = false;
			list_del(&iwpbl->list);
			वापस iwpbl;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * i40iw_मुक्त_qp_resources - मुक्त up memory resources क्रम qp
 * @iwqp: qp ptr (user or kernel)
 */
व्योम i40iw_मुक्त_qp_resources(काष्ठा i40iw_qp *iwqp)
अणु
	काष्ठा i40iw_pbl *iwpbl = &iwqp->iwpbl;
	काष्ठा i40iw_device *iwdev = iwqp->iwdev;
	u32 qp_num = iwqp->ibqp.qp_num;

	i40iw_ieq_cleanup_qp(iwdev->vsi.ieq, &iwqp->sc_qp);
	अगर (qp_num)
		i40iw_मुक्त_resource(iwdev, iwdev->allocated_qps, qp_num);
	अगर (iwpbl->pbl_allocated)
		i40iw_मुक्त_pble(iwdev->pble_rsrc, &iwpbl->pble_alloc);
	i40iw_मुक्त_dma_mem(iwdev->sc_dev.hw, &iwqp->q2_ctx_mem);
	i40iw_मुक्त_dma_mem(iwdev->sc_dev.hw, &iwqp->kqp.dma_mem);
	kमुक्त(iwqp->kqp.wrid_mem);
	iwqp->kqp.wrid_mem = शून्य;
	kमुक्त(iwqp);
पूर्ण

/**
 * i40iw_clean_cqes - clean cq entries क्रम qp
 * @iwqp: qp ptr (user or kernel)
 * @iwcq: cq ptr
 */
अटल व्योम i40iw_clean_cqes(काष्ठा i40iw_qp *iwqp, काष्ठा i40iw_cq *iwcq)
अणु
	काष्ठा i40iw_cq_uk *ukcq = &iwcq->sc_cq.cq_uk;

	ukcq->ops.iw_cq_clean(&iwqp->sc_qp.qp_uk, ukcq);
पूर्ण

/**
 * i40iw_destroy_qp - destroy qp
 * @ibqp: qp's ib pointer also to get to device's qp address
 * @udata: user data
 */
अटल पूर्णांक i40iw_destroy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_udata *udata)
अणु
	काष्ठा i40iw_qp *iwqp = to_iwqp(ibqp);
	काष्ठा ib_qp_attr attr;
	काष्ठा i40iw_device *iwdev = iwqp->iwdev;

	स_रखो(&attr, 0, माप(attr));

	iwqp->destroyed = 1;

	अगर (iwqp->ibqp_state >= IB_QPS_INIT && iwqp->ibqp_state < IB_QPS_RTS)
		i40iw_next_iw_state(iwqp, I40IW_QP_STATE_ERROR, 0, 0, 0);

	अगर (!iwqp->user_mode) अणु
		अगर (iwqp->iwscq) अणु
			i40iw_clean_cqes(iwqp, iwqp->iwscq);
			अगर (iwqp->iwrcq != iwqp->iwscq)
				i40iw_clean_cqes(iwqp, iwqp->iwrcq);
		पूर्ण
	पूर्ण

	attr.qp_state = IB_QPS_ERR;
	i40iw_modअगरy_qp(&iwqp->ibqp, &attr, IB_QP_STATE, शून्य);
	i40iw_qp_rem_ref(&iwqp->ibqp);
	रुको_क्रम_completion(&iwqp->मुक्त_qp);
	i40iw_cqp_qp_destroy_cmd(&iwdev->sc_dev, &iwqp->sc_qp);
	i40iw_rem_pdusecount(iwqp->iwpd, iwdev);
	i40iw_मुक्त_qp_resources(iwqp);
	i40iw_rem_devusecount(iwdev);

	वापस 0;
पूर्ण

/**
 * i40iw_setup_virt_qp - setup क्रम allocation of भव qp
 * @iwdev: iwarp device
 * @iwqp: qp ptr
 * @init_info: initialize info to वापस
 */
अटल पूर्णांक i40iw_setup_virt_qp(काष्ठा i40iw_device *iwdev,
			       काष्ठा i40iw_qp *iwqp,
			       काष्ठा i40iw_qp_init_info *init_info)
अणु
	काष्ठा i40iw_pbl *iwpbl = &iwqp->iwpbl;
	काष्ठा i40iw_qp_mr *qpmr = &iwpbl->qp_mr;

	iwqp->page = qpmr->sq_page;
	init_info->shaकरोw_area_pa = cpu_to_le64(qpmr->shaकरोw);
	अगर (iwpbl->pbl_allocated) अणु
		init_info->भव_map = true;
		init_info->sq_pa = qpmr->sq_pbl.idx;
		init_info->rq_pa = qpmr->rq_pbl.idx;
	पूर्ण अन्यथा अणु
		init_info->sq_pa = qpmr->sq_pbl.addr;
		init_info->rq_pa = qpmr->rq_pbl.addr;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * i40iw_setup_kmode_qp - setup initialization क्रम kernel mode qp
 * @iwdev: iwarp device
 * @iwqp: qp ptr (user or kernel)
 * @info: initialize info to वापस
 */
अटल पूर्णांक i40iw_setup_kmode_qp(काष्ठा i40iw_device *iwdev,
				काष्ठा i40iw_qp *iwqp,
				काष्ठा i40iw_qp_init_info *info)
अणु
	काष्ठा i40iw_dma_mem *mem = &iwqp->kqp.dma_mem;
	u32 sqdepth, rqdepth;
	u8 sqshअगरt;
	u32 size;
	क्रमागत i40iw_status_code status;
	काष्ठा i40iw_qp_uk_init_info *ukinfo = &info->qp_uk_init_info;

	i40iw_get_wqe_shअगरt(ukinfo->max_sq_frag_cnt, ukinfo->max_अंतरभूत_data, &sqshअगरt);
	status = i40iw_get_sqdepth(ukinfo->sq_size, sqshअगरt, &sqdepth);
	अगर (status)
		वापस -ENOMEM;

	status = i40iw_get_rqdepth(ukinfo->rq_size, I40IW_MAX_RQ_WQE_SHIFT, &rqdepth);
	अगर (status)
		वापस -ENOMEM;

	size = sqdepth * माप(काष्ठा i40iw_sq_uk_wr_trk_info) + (rqdepth << 3);
	iwqp->kqp.wrid_mem = kzalloc(size, GFP_KERNEL);

	ukinfo->sq_wrtrk_array = (काष्ठा i40iw_sq_uk_wr_trk_info *)iwqp->kqp.wrid_mem;
	अगर (!ukinfo->sq_wrtrk_array)
		वापस -ENOMEM;

	ukinfo->rq_wrid_array = (u64 *)&ukinfo->sq_wrtrk_array[sqdepth];

	size = (sqdepth + rqdepth) * I40IW_QP_WQE_MIN_SIZE;
	size += (I40IW_SHADOW_AREA_SIZE << 3);

	status = i40iw_allocate_dma_mem(iwdev->sc_dev.hw, mem, size, 256);
	अगर (status) अणु
		kमुक्त(ukinfo->sq_wrtrk_array);
		ukinfo->sq_wrtrk_array = शून्य;
		वापस -ENOMEM;
	पूर्ण

	ukinfo->sq = mem->va;
	info->sq_pa = mem->pa;

	ukinfo->rq = &ukinfo->sq[sqdepth];
	info->rq_pa = info->sq_pa + (sqdepth * I40IW_QP_WQE_MIN_SIZE);

	ukinfo->shaकरोw_area = ukinfo->rq[rqdepth].elem;
	info->shaकरोw_area_pa = info->rq_pa + (rqdepth * I40IW_QP_WQE_MIN_SIZE);

	ukinfo->sq_size = sqdepth >> sqshअगरt;
	ukinfo->rq_size = rqdepth >> I40IW_MAX_RQ_WQE_SHIFT;
	ukinfo->qp_id = iwqp->ibqp.qp_num;
	वापस 0;
पूर्ण

/**
 * i40iw_create_qp - create qp
 * @ibpd: ptr of pd
 * @init_attr: attributes क्रम qp
 * @udata: user data क्रम create qp
 */
अटल काष्ठा ib_qp *i40iw_create_qp(काष्ठा ib_pd *ibpd,
				     काष्ठा ib_qp_init_attr *init_attr,
				     काष्ठा ib_udata *udata)
अणु
	काष्ठा i40iw_pd *iwpd = to_iwpd(ibpd);
	काष्ठा i40iw_device *iwdev = to_iwdev(ibpd->device);
	काष्ठा i40iw_cqp *iwcqp = &iwdev->cqp;
	काष्ठा i40iw_qp *iwqp;
	काष्ठा i40iw_ucontext *ucontext = rdma_udata_to_drv_context(
		udata, काष्ठा i40iw_ucontext, ibucontext);
	काष्ठा i40iw_create_qp_req req;
	काष्ठा i40iw_create_qp_resp uresp;
	u32 qp_num = 0;
	क्रमागत i40iw_status_code ret;
	पूर्णांक err_code;
	पूर्णांक sq_size;
	पूर्णांक rq_size;
	काष्ठा i40iw_sc_qp *qp;
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	काष्ठा i40iw_qp_init_info init_info;
	काष्ठा i40iw_create_qp_info *qp_info;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;

	काष्ठा i40iw_qp_host_ctx_info *ctx_info;
	काष्ठा i40iwarp_offload_info *iwarp_info;
	अचिन्हित दीर्घ flags;

	अगर (iwdev->closing)
		वापस ERR_PTR(-ENODEV);

	अगर (init_attr->create_flags)
		वापस ERR_PTR(-EOPNOTSUPP);
	अगर (init_attr->cap.max_अंतरभूत_data > I40IW_MAX_INLINE_DATA_SIZE)
		init_attr->cap.max_अंतरभूत_data = I40IW_MAX_INLINE_DATA_SIZE;

	अगर (init_attr->cap.max_send_sge > I40IW_MAX_WQ_FRAGMENT_COUNT)
		init_attr->cap.max_send_sge = I40IW_MAX_WQ_FRAGMENT_COUNT;

	अगर (init_attr->cap.max_recv_sge > I40IW_MAX_WQ_FRAGMENT_COUNT)
		init_attr->cap.max_recv_sge = I40IW_MAX_WQ_FRAGMENT_COUNT;

	स_रखो(&init_info, 0, माप(init_info));

	sq_size = init_attr->cap.max_send_wr;
	rq_size = init_attr->cap.max_recv_wr;

	init_info.vsi = &iwdev->vsi;
	init_info.qp_uk_init_info.sq_size = sq_size;
	init_info.qp_uk_init_info.rq_size = rq_size;
	init_info.qp_uk_init_info.max_sq_frag_cnt = init_attr->cap.max_send_sge;
	init_info.qp_uk_init_info.max_rq_frag_cnt = init_attr->cap.max_recv_sge;
	init_info.qp_uk_init_info.max_अंतरभूत_data = init_attr->cap.max_अंतरभूत_data;

	iwqp = kzalloc(माप(*iwqp), GFP_KERNEL);
	अगर (!iwqp)
		वापस ERR_PTR(-ENOMEM);

	qp = &iwqp->sc_qp;
	qp->back_qp = (व्योम *)iwqp;
	iwqp->iwdev = iwdev;
	iwqp->ctx_info.iwarp_info = &iwqp->iwarp_info;

	अगर (i40iw_allocate_dma_mem(dev->hw,
				   &iwqp->q2_ctx_mem,
				   I40IW_Q2_BUFFER_SIZE + I40IW_QP_CTX_SIZE,
				   256)) अणु
		i40iw_pr_err("dma_mem failed\n");
		err_code = -ENOMEM;
		जाओ error;
	पूर्ण

	init_info.q2 = iwqp->q2_ctx_mem.va;
	init_info.q2_pa = iwqp->q2_ctx_mem.pa;

	init_info.host_ctx = (व्योम *)init_info.q2 + I40IW_Q2_BUFFER_SIZE;
	init_info.host_ctx_pa = init_info.q2_pa + I40IW_Q2_BUFFER_SIZE;

	err_code = i40iw_alloc_resource(iwdev, iwdev->allocated_qps, iwdev->max_qp,
					&qp_num, &iwdev->next_qp);
	अगर (err_code) अणु
		i40iw_pr_err("qp resource\n");
		जाओ error;
	पूर्ण

	iwqp->iwpd = iwpd;
	iwqp->ibqp.qp_num = qp_num;
	qp = &iwqp->sc_qp;
	iwqp->iwscq = to_iwcq(init_attr->send_cq);
	iwqp->iwrcq = to_iwcq(init_attr->recv_cq);

	iwqp->host_ctx.va = init_info.host_ctx;
	iwqp->host_ctx.pa = init_info.host_ctx_pa;
	iwqp->host_ctx.size = I40IW_QP_CTX_SIZE;

	init_info.pd = &iwpd->sc_pd;
	init_info.qp_uk_init_info.qp_id = iwqp->ibqp.qp_num;
	iwqp->ctx_info.qp_compl_ctx = (uपूर्णांकptr_t)qp;

	अगर (init_attr->qp_type != IB_QPT_RC) अणु
		err_code = -EOPNOTSUPP;
		जाओ error;
	पूर्ण
	अगर (udata) अणु
		err_code = ib_copy_from_udata(&req, udata, माप(req));
		अगर (err_code) अणु
			i40iw_pr_err("ib_copy_from_data\n");
			जाओ error;
		पूर्ण
		iwqp->ctx_info.qp_compl_ctx = req.user_compl_ctx;
		iwqp->user_mode = 1;

		अगर (req.user_wqe_buffers) अणु
			काष्ठा i40iw_pbl *iwpbl;

			spin_lock_irqsave(
			    &ucontext->qp_reg_mem_list_lock, flags);
			iwpbl = i40iw_get_pbl(
			    (अचिन्हित दीर्घ)req.user_wqe_buffers,
			    &ucontext->qp_reg_mem_list);
			spin_unlock_irqrestore(
			    &ucontext->qp_reg_mem_list_lock, flags);

			अगर (!iwpbl) अणु
				err_code = -ENODATA;
				i40iw_pr_err("no pbl info\n");
				जाओ error;
			पूर्ण
			स_नकल(&iwqp->iwpbl, iwpbl, माप(iwqp->iwpbl));
		पूर्ण
		err_code = i40iw_setup_virt_qp(iwdev, iwqp, &init_info);
	पूर्ण अन्यथा अणु
		err_code = i40iw_setup_kmode_qp(iwdev, iwqp, &init_info);
	पूर्ण

	अगर (err_code) अणु
		i40iw_pr_err("setup qp failed\n");
		जाओ error;
	पूर्ण

	init_info.type = I40IW_QP_TYPE_IWARP;
	ret = dev->iw_priv_qp_ops->qp_init(qp, &init_info);
	अगर (ret) अणु
		err_code = -EPROTO;
		i40iw_pr_err("qp_init fail\n");
		जाओ error;
	पूर्ण
	ctx_info = &iwqp->ctx_info;
	iwarp_info = &iwqp->iwarp_info;
	iwarp_info->rd_enable = true;
	iwarp_info->wr_rdresp_en = true;
	अगर (!iwqp->user_mode) अणु
		iwarp_info->fast_reg_en = true;
		iwarp_info->priv_mode_en = true;
	पूर्ण
	iwarp_info->ddp_ver = 1;
	iwarp_info->rdmap_ver = 1;

	ctx_info->iwarp_info_valid = true;
	ctx_info->send_cq_num = iwqp->iwscq->sc_cq.cq_uk.cq_id;
	ctx_info->rcv_cq_num = iwqp->iwrcq->sc_cq.cq_uk.cq_id;
	ret = dev->iw_priv_qp_ops->qp_setctx(&iwqp->sc_qp,
					     (u64 *)iwqp->host_ctx.va,
					     ctx_info);
	ctx_info->iwarp_info_valid = false;
	cqp_request = i40iw_get_cqp_request(iwcqp, true);
	अगर (!cqp_request) अणु
		err_code = -ENOMEM;
		जाओ error;
	पूर्ण
	cqp_info = &cqp_request->info;
	qp_info = &cqp_request->info.in.u.qp_create.info;

	स_रखो(qp_info, 0, माप(*qp_info));

	qp_info->cq_num_valid = true;
	qp_info->next_iwarp_state = I40IW_QP_STATE_IDLE;

	cqp_info->cqp_cmd = OP_QP_CREATE;
	cqp_info->post_sq = 1;
	cqp_info->in.u.qp_create.qp = qp;
	cqp_info->in.u.qp_create.scratch = (uपूर्णांकptr_t)cqp_request;
	ret = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (ret) अणु
		i40iw_pr_err("CQP-OP QP create fail");
		err_code = -EACCES;
		जाओ error;
	पूर्ण

	refcount_set(&iwqp->refcount, 1);
	spin_lock_init(&iwqp->lock);
	iwqp->sig_all = (init_attr->sq_sig_type == IB_SIGNAL_ALL_WR) ? 1 : 0;
	iwdev->qp_table[qp_num] = iwqp;
	i40iw_add_pdusecount(iwqp->iwpd);
	i40iw_add_devusecount(iwdev);
	अगर (udata) अणु
		स_रखो(&uresp, 0, माप(uresp));
		uresp.actual_sq_size = sq_size;
		uresp.actual_rq_size = rq_size;
		uresp.qp_id = qp_num;
		uresp.push_idx = I40IW_INVALID_PUSH_PAGE_INDEX;
		err_code = ib_copy_to_udata(udata, &uresp, माप(uresp));
		अगर (err_code) अणु
			i40iw_pr_err("copy_to_udata failed\n");
			i40iw_destroy_qp(&iwqp->ibqp, udata);
			/* let the completion of the qp destroy मुक्त the qp */
			वापस ERR_PTR(err_code);
		पूर्ण
	पूर्ण
	init_completion(&iwqp->sq_drained);
	init_completion(&iwqp->rq_drained);
	init_completion(&iwqp->मुक्त_qp);

	वापस &iwqp->ibqp;
error:
	i40iw_मुक्त_qp_resources(iwqp);
	वापस ERR_PTR(err_code);
पूर्ण

/**
 * i40iw_query_qp - query qp attributes
 * @ibqp: qp poपूर्णांकer
 * @attr: attributes poपूर्णांकer
 * @attr_mask: Not used
 * @init_attr: qp attributes to वापस
 */
अटल पूर्णांक i40iw_query_qp(काष्ठा ib_qp *ibqp,
			  काष्ठा ib_qp_attr *attr,
			  पूर्णांक attr_mask,
			  काष्ठा ib_qp_init_attr *init_attr)
अणु
	काष्ठा i40iw_qp *iwqp = to_iwqp(ibqp);
	काष्ठा i40iw_sc_qp *qp = &iwqp->sc_qp;

	attr->qp_state = iwqp->ibqp_state;
	attr->cur_qp_state = attr->qp_state;
	attr->qp_access_flags = 0;
	attr->cap.max_send_wr = qp->qp_uk.sq_size;
	attr->cap.max_recv_wr = qp->qp_uk.rq_size;
	attr->cap.max_अंतरभूत_data = I40IW_MAX_INLINE_DATA_SIZE;
	attr->cap.max_send_sge = I40IW_MAX_WQ_FRAGMENT_COUNT;
	attr->cap.max_recv_sge = I40IW_MAX_WQ_FRAGMENT_COUNT;
	attr->port_num = 1;
	init_attr->event_handler = iwqp->ibqp.event_handler;
	init_attr->qp_context = iwqp->ibqp.qp_context;
	init_attr->send_cq = iwqp->ibqp.send_cq;
	init_attr->recv_cq = iwqp->ibqp.recv_cq;
	init_attr->srq = iwqp->ibqp.srq;
	init_attr->cap = attr->cap;
	init_attr->port_num = 1;
	वापस 0;
पूर्ण

/**
 * i40iw_hw_modअगरy_qp - setup cqp क्रम modअगरy qp
 * @iwdev: iwarp device
 * @iwqp: qp ptr (user or kernel)
 * @info: info क्रम modअगरy qp
 * @रुको: flag to रुको or not क्रम modअगरy qp completion
 */
व्योम i40iw_hw_modअगरy_qp(काष्ठा i40iw_device *iwdev, काष्ठा i40iw_qp *iwqp,
			काष्ठा i40iw_modअगरy_qp_info *info, bool रुको)
अणु
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;
	काष्ठा i40iw_modअगरy_qp_info *m_info;
	काष्ठा i40iw_gen_ae_info ae_info;

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, रुको);
	अगर (!cqp_request)
		वापस;

	cqp_info = &cqp_request->info;
	m_info = &cqp_info->in.u.qp_modअगरy.info;
	स_नकल(m_info, info, माप(*m_info));
	cqp_info->cqp_cmd = OP_QP_MODIFY;
	cqp_info->post_sq = 1;
	cqp_info->in.u.qp_modअगरy.qp = &iwqp->sc_qp;
	cqp_info->in.u.qp_modअगरy.scratch = (uपूर्णांकptr_t)cqp_request;
	अगर (!i40iw_handle_cqp_op(iwdev, cqp_request))
		वापस;

	चयन (m_info->next_iwarp_state) अणु
	हाल I40IW_QP_STATE_RTS:
		अगर (iwqp->iwarp_state == I40IW_QP_STATE_IDLE)
			i40iw_send_reset(iwqp->cm_node);
		fallthrough;
	हाल I40IW_QP_STATE_IDLE:
	हाल I40IW_QP_STATE_TERMINATE:
	हाल I40IW_QP_STATE_CLOSING:
		ae_info.ae_code = I40IW_AE_BAD_CLOSE;
		ae_info.ae_source = 0;
		i40iw_gen_ae(iwdev, &iwqp->sc_qp, &ae_info, false);
		अवरोध;
	हाल I40IW_QP_STATE_ERROR:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * i40iw_modअगरy_qp - modअगरy qp request
 * @ibqp: qp's poपूर्णांकer क्रम modअगरy
 * @attr: access attributes
 * @attr_mask: state mask
 * @udata: user data
 */
पूर्णांक i40iw_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
		    पूर्णांक attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा i40iw_qp *iwqp = to_iwqp(ibqp);
	काष्ठा i40iw_device *iwdev = iwqp->iwdev;
	काष्ठा i40iw_qp_host_ctx_info *ctx_info;
	काष्ठा i40iwarp_offload_info *iwarp_info;
	काष्ठा i40iw_modअगरy_qp_info info;
	u8 issue_modअगरy_qp = 0;
	u8 करोnt_रुको = 0;
	u32 err;
	अचिन्हित दीर्घ flags;

	अगर (attr_mask & ~IB_QP_ATTR_STANDARD_BITS)
		वापस -EOPNOTSUPP;

	स_रखो(&info, 0, माप(info));
	ctx_info = &iwqp->ctx_info;
	iwarp_info = &iwqp->iwarp_info;

	spin_lock_irqsave(&iwqp->lock, flags);

	अगर (attr_mask & IB_QP_STATE) अणु
		अगर (iwdev->closing && attr->qp_state != IB_QPS_ERR) अणु
			err = -EINVAL;
			जाओ निकास;
		पूर्ण

		चयन (attr->qp_state) अणु
		हाल IB_QPS_INIT:
		हाल IB_QPS_RTR:
			अगर (iwqp->iwarp_state > (u32)I40IW_QP_STATE_IDLE) अणु
				err = -EINVAL;
				जाओ निकास;
			पूर्ण
			अगर (iwqp->iwarp_state == I40IW_QP_STATE_INVALID) अणु
				info.next_iwarp_state = I40IW_QP_STATE_IDLE;
				issue_modअगरy_qp = 1;
			पूर्ण
			अवरोध;
		हाल IB_QPS_RTS:
			अगर ((iwqp->iwarp_state > (u32)I40IW_QP_STATE_RTS) ||
			    (!iwqp->cm_id)) अणु
				err = -EINVAL;
				जाओ निकास;
			पूर्ण

			issue_modअगरy_qp = 1;
			iwqp->hw_tcp_state = I40IW_TCP_STATE_ESTABLISHED;
			iwqp->hte_added = 1;
			info.next_iwarp_state = I40IW_QP_STATE_RTS;
			info.tcp_ctx_valid = true;
			info.ord_valid = true;
			info.arp_cache_idx_valid = true;
			info.cq_num_valid = true;
			अवरोध;
		हाल IB_QPS_SQD:
			अगर (iwqp->hw_iwarp_state > (u32)I40IW_QP_STATE_RTS) अणु
				err = 0;
				जाओ निकास;
			पूर्ण
			अगर ((iwqp->iwarp_state == (u32)I40IW_QP_STATE_CLOSING) ||
			    (iwqp->iwarp_state < (u32)I40IW_QP_STATE_RTS)) अणु
				err = 0;
				जाओ निकास;
			पूर्ण
			अगर (iwqp->iwarp_state > (u32)I40IW_QP_STATE_CLOSING) अणु
				err = -EINVAL;
				जाओ निकास;
			पूर्ण
			info.next_iwarp_state = I40IW_QP_STATE_CLOSING;
			issue_modअगरy_qp = 1;
			अवरोध;
		हाल IB_QPS_SQE:
			अगर (iwqp->iwarp_state >= (u32)I40IW_QP_STATE_TERMINATE) अणु
				err = -EINVAL;
				जाओ निकास;
			पूर्ण
			info.next_iwarp_state = I40IW_QP_STATE_TERMINATE;
			issue_modअगरy_qp = 1;
			अवरोध;
		हाल IB_QPS_ERR:
		हाल IB_QPS_RESET:
			अगर (iwqp->iwarp_state == (u32)I40IW_QP_STATE_ERROR) अणु
				err = -EINVAL;
				जाओ निकास;
			पूर्ण
			अगर (iwqp->sc_qp.term_flags)
				i40iw_terminate_del_समयr(&iwqp->sc_qp);
			info.next_iwarp_state = I40IW_QP_STATE_ERROR;
			अगर ((iwqp->hw_tcp_state > I40IW_TCP_STATE_CLOSED) &&
			    iwdev->iw_status &&
			    (iwqp->hw_tcp_state != I40IW_TCP_STATE_TIME_WAIT))
				info.reset_tcp_conn = true;
			अन्यथा
				करोnt_रुको = 1;
			issue_modअगरy_qp = 1;
			info.next_iwarp_state = I40IW_QP_STATE_ERROR;
			अवरोध;
		शेष:
			err = -EINVAL;
			जाओ निकास;
		पूर्ण

		iwqp->ibqp_state = attr->qp_state;

	पूर्ण
	अगर (attr_mask & IB_QP_ACCESS_FLAGS) अणु
		ctx_info->iwarp_info_valid = true;
		अगर (attr->qp_access_flags & IB_ACCESS_LOCAL_WRITE)
			iwarp_info->wr_rdresp_en = true;
		अगर (attr->qp_access_flags & IB_ACCESS_REMOTE_WRITE)
			iwarp_info->wr_rdresp_en = true;
		अगर (attr->qp_access_flags & IB_ACCESS_REMOTE_READ)
			iwarp_info->rd_enable = true;
		अगर (attr->qp_access_flags & IB_ACCESS_MW_BIND)
			iwarp_info->bind_en = true;

		अगर (iwqp->user_mode) अणु
			iwarp_info->rd_enable = true;
			iwarp_info->wr_rdresp_en = true;
			iwarp_info->priv_mode_en = false;
		पूर्ण
	पूर्ण

	अगर (ctx_info->iwarp_info_valid) अणु
		काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
		पूर्णांक ret;

		ctx_info->send_cq_num = iwqp->iwscq->sc_cq.cq_uk.cq_id;
		ctx_info->rcv_cq_num = iwqp->iwrcq->sc_cq.cq_uk.cq_id;
		ret = dev->iw_priv_qp_ops->qp_setctx(&iwqp->sc_qp,
						     (u64 *)iwqp->host_ctx.va,
						     ctx_info);
		अगर (ret) अणु
			i40iw_pr_err("setting QP context\n");
			err = -EINVAL;
			जाओ निकास;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&iwqp->lock, flags);

	अगर (issue_modअगरy_qp) अणु
		i40iw_hw_modअगरy_qp(iwdev, iwqp, &info, true);

		spin_lock_irqsave(&iwqp->lock, flags);
		iwqp->iwarp_state = info.next_iwarp_state;
		spin_unlock_irqrestore(&iwqp->lock, flags);
	पूर्ण

	अगर (issue_modअगरy_qp && (iwqp->ibqp_state > IB_QPS_RTS)) अणु
		अगर (करोnt_रुको) अणु
			अगर (iwqp->cm_id && iwqp->hw_tcp_state) अणु
				spin_lock_irqsave(&iwqp->lock, flags);
				iwqp->hw_tcp_state = I40IW_TCP_STATE_CLOSED;
				iwqp->last_aeq = I40IW_AE_RESET_SENT;
				spin_unlock_irqrestore(&iwqp->lock, flags);
				i40iw_cm_disconn(iwqp);
			पूर्ण
		पूर्ण अन्यथा अणु
			spin_lock_irqsave(&iwqp->lock, flags);
			अगर (iwqp->cm_id) अणु
				अगर (atomic_inc_वापस(&iwqp->बंद_समयr_started) == 1) अणु
					iwqp->cm_id->add_ref(iwqp->cm_id);
					i40iw_schedule_cm_समयr(iwqp->cm_node,
								(काष्ठा i40iw_puda_buf *)iwqp,
								 I40IW_TIMER_TYPE_CLOSE, 1, 0);
				पूर्ण
			पूर्ण
			spin_unlock_irqrestore(&iwqp->lock, flags);
		पूर्ण
	पूर्ण
	वापस 0;
निकास:
	spin_unlock_irqrestore(&iwqp->lock, flags);
	वापस err;
पूर्ण

/**
 * cq_मुक्त_resources - मुक्त up recources क्रम cq
 * @iwdev: iwarp device
 * @iwcq: cq ptr
 */
अटल व्योम cq_मुक्त_resources(काष्ठा i40iw_device *iwdev, काष्ठा i40iw_cq *iwcq)
अणु
	काष्ठा i40iw_sc_cq *cq = &iwcq->sc_cq;

	अगर (!iwcq->user_mode)
		i40iw_मुक्त_dma_mem(iwdev->sc_dev.hw, &iwcq->kmem);
	i40iw_मुक्त_resource(iwdev, iwdev->allocated_cqs, cq->cq_uk.cq_id);
पूर्ण

/**
 * i40iw_cq_wq_destroy - send cq destroy cqp
 * @iwdev: iwarp device
 * @cq: hardware control cq
 */
व्योम i40iw_cq_wq_destroy(काष्ठा i40iw_device *iwdev, काष्ठा i40iw_sc_cq *cq)
अणु
	क्रमागत i40iw_status_code status;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, true);
	अगर (!cqp_request)
		वापस;

	cqp_info = &cqp_request->info;

	cqp_info->cqp_cmd = OP_CQ_DESTROY;
	cqp_info->post_sq = 1;
	cqp_info->in.u.cq_destroy.cq = cq;
	cqp_info->in.u.cq_destroy.scratch = (uपूर्णांकptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (status)
		i40iw_pr_err("CQP-OP Destroy QP fail");
पूर्ण

/**
 * i40iw_destroy_cq - destroy cq
 * @ib_cq: cq poपूर्णांकer
 * @udata: user data or शून्य क्रम kernel object
 */
अटल पूर्णांक i40iw_destroy_cq(काष्ठा ib_cq *ib_cq, काष्ठा ib_udata *udata)
अणु
	काष्ठा i40iw_cq *iwcq;
	काष्ठा i40iw_device *iwdev;
	काष्ठा i40iw_sc_cq *cq;

	iwcq = to_iwcq(ib_cq);
	iwdev = to_iwdev(ib_cq->device);
	cq = &iwcq->sc_cq;
	i40iw_cq_wq_destroy(iwdev, cq);
	cq_मुक्त_resources(iwdev, iwcq);
	i40iw_rem_devusecount(iwdev);
	वापस 0;
पूर्ण

/**
 * i40iw_create_cq - create cq
 * @ibcq: CQ allocated
 * @attr: attributes क्रम cq
 * @udata: user data
 */
अटल पूर्णांक i40iw_create_cq(काष्ठा ib_cq *ibcq,
			   स्थिर काष्ठा ib_cq_init_attr *attr,
			   काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = ibcq->device;
	काष्ठा i40iw_device *iwdev = to_iwdev(ibdev);
	काष्ठा i40iw_cq *iwcq = to_iwcq(ibcq);
	काष्ठा i40iw_pbl *iwpbl;
	u32 cq_num = 0;
	काष्ठा i40iw_sc_cq *cq;
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	काष्ठा i40iw_cq_init_info info = अणुपूर्ण;
	क्रमागत i40iw_status_code status;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;
	काष्ठा i40iw_cq_uk_init_info *ukinfo = &info.cq_uk_init_info;
	अचिन्हित दीर्घ flags;
	पूर्णांक err_code;
	पूर्णांक entries = attr->cqe;

	अगर (attr->flags)
		वापस -EOPNOTSUPP;

	अगर (iwdev->closing)
		वापस -ENODEV;

	अगर (entries > iwdev->max_cqe)
		वापस -EINVAL;

	err_code = i40iw_alloc_resource(iwdev, iwdev->allocated_cqs,
					iwdev->max_cq, &cq_num,
					&iwdev->next_cq);
	अगर (err_code)
		वापस err_code;

	cq = &iwcq->sc_cq;
	cq->back_cq = (व्योम *)iwcq;
	spin_lock_init(&iwcq->lock);

	info.dev = dev;
	ukinfo->cq_size = max(entries, 4);
	ukinfo->cq_id = cq_num;
	iwcq->ibcq.cqe = info.cq_uk_init_info.cq_size;
	info.ceqe_mask = 0;
	अगर (attr->comp_vector < iwdev->ceqs_count)
		info.ceq_id = attr->comp_vector;
	info.ceq_id_valid = true;
	info.ceqe_mask = 1;
	info.type = I40IW_CQ_TYPE_IWARP;
	अगर (udata) अणु
		काष्ठा i40iw_ucontext *ucontext = rdma_udata_to_drv_context(
			udata, काष्ठा i40iw_ucontext, ibucontext);
		काष्ठा i40iw_create_cq_req req;
		काष्ठा i40iw_cq_mr *cqmr;

		स_रखो(&req, 0, माप(req));
		iwcq->user_mode = true;
		अगर (ib_copy_from_udata(&req, udata, माप(काष्ठा i40iw_create_cq_req))) अणु
			err_code = -EFAULT;
			जाओ cq_मुक्त_resources;
		पूर्ण

		spin_lock_irqsave(&ucontext->cq_reg_mem_list_lock, flags);
		iwpbl = i40iw_get_pbl((अचिन्हित दीर्घ)req.user_cq_buffer,
				      &ucontext->cq_reg_mem_list);
		spin_unlock_irqrestore(&ucontext->cq_reg_mem_list_lock, flags);
		अगर (!iwpbl) अणु
			err_code = -EPROTO;
			जाओ cq_मुक्त_resources;
		पूर्ण

		iwcq->iwpbl = iwpbl;
		iwcq->cq_mem_size = 0;
		cqmr = &iwpbl->cq_mr;
		info.shaकरोw_area_pa = cpu_to_le64(cqmr->shaकरोw);
		अगर (iwpbl->pbl_allocated) अणु
			info.भव_map = true;
			info.pbl_chunk_size = 1;
			info.first_pm_pbl_idx = cqmr->cq_pbl.idx;
		पूर्ण अन्यथा अणु
			info.cq_base_pa = cqmr->cq_pbl.addr;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Kmode allocations */
		पूर्णांक rsize;
		पूर्णांक shaकरोw;

		rsize = info.cq_uk_init_info.cq_size * माप(काष्ठा i40iw_cqe);
		rsize = round_up(rsize, 256);
		shaकरोw = I40IW_SHADOW_AREA_SIZE << 3;
		status = i40iw_allocate_dma_mem(dev->hw, &iwcq->kmem,
						rsize + shaकरोw, 256);
		अगर (status) अणु
			err_code = -ENOMEM;
			जाओ cq_मुक्त_resources;
		पूर्ण
		ukinfo->cq_base = iwcq->kmem.va;
		info.cq_base_pa = iwcq->kmem.pa;
		info.shaकरोw_area_pa = info.cq_base_pa + rsize;
		ukinfo->shaकरोw_area = iwcq->kmem.va + rsize;
	पूर्ण

	अगर (dev->iw_priv_cq_ops->cq_init(cq, &info)) अणु
		i40iw_pr_err("init cq fail\n");
		err_code = -EPROTO;
		जाओ cq_मुक्त_resources;
	पूर्ण

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, true);
	अगर (!cqp_request) अणु
		err_code = -ENOMEM;
		जाओ cq_मुक्त_resources;
	पूर्ण

	cqp_info = &cqp_request->info;
	cqp_info->cqp_cmd = OP_CQ_CREATE;
	cqp_info->post_sq = 1;
	cqp_info->in.u.cq_create.cq = cq;
	cqp_info->in.u.cq_create.scratch = (uपूर्णांकptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (status) अणु
		i40iw_pr_err("CQP-OP Create QP fail");
		err_code = -EPROTO;
		जाओ cq_मुक्त_resources;
	पूर्ण

	अगर (udata) अणु
		काष्ठा i40iw_create_cq_resp resp;

		स_रखो(&resp, 0, माप(resp));
		resp.cq_id = info.cq_uk_init_info.cq_id;
		resp.cq_size = info.cq_uk_init_info.cq_size;
		अगर (ib_copy_to_udata(udata, &resp, माप(resp))) अणु
			i40iw_pr_err("copy to user data\n");
			err_code = -EPROTO;
			जाओ cq_destroy;
		पूर्ण
	पूर्ण

	i40iw_add_devusecount(iwdev);
	वापस 0;

cq_destroy:
	i40iw_cq_wq_destroy(iwdev, cq);
cq_मुक्त_resources:
	cq_मुक्त_resources(iwdev, iwcq);
	वापस err_code;
पूर्ण

/**
 * i40iw_get_user_access - get hw access from IB access
 * @acc: IB access to वापस hw access
 */
अटल अंतरभूत u16 i40iw_get_user_access(पूर्णांक acc)
अणु
	u16 access = 0;

	access |= (acc & IB_ACCESS_LOCAL_WRITE) ? I40IW_ACCESS_FLAGS_LOCALWRITE : 0;
	access |= (acc & IB_ACCESS_REMOTE_WRITE) ? I40IW_ACCESS_FLAGS_REMOTEWRITE : 0;
	access |= (acc & IB_ACCESS_REMOTE_READ) ? I40IW_ACCESS_FLAGS_REMOTEREAD : 0;
	access |= (acc & IB_ACCESS_MW_BIND) ? I40IW_ACCESS_FLAGS_BIND_WINDOW : 0;
	वापस access;
पूर्ण

/**
 * i40iw_मुक्त_stag - मुक्त stag resource
 * @iwdev: iwarp device
 * @stag: stag to मुक्त
 */
अटल व्योम i40iw_मुक्त_stag(काष्ठा i40iw_device *iwdev, u32 stag)
अणु
	u32 stag_idx;

	stag_idx = (stag & iwdev->mr_stagmask) >> I40IW_CQPSQ_STAG_IDX_SHIFT;
	i40iw_मुक्त_resource(iwdev, iwdev->allocated_mrs, stag_idx);
	i40iw_rem_devusecount(iwdev);
पूर्ण

/**
 * i40iw_create_stag - create अक्रमom stag
 * @iwdev: iwarp device
 */
अटल u32 i40iw_create_stag(काष्ठा i40iw_device *iwdev)
अणु
	u32 stag = 0;
	u32 stag_index = 0;
	u32 next_stag_index;
	u32 driver_key;
	u32 अक्रमom;
	u8 consumer_key;
	पूर्णांक ret;

	get_अक्रमom_bytes(&अक्रमom, माप(अक्रमom));
	consumer_key = (u8)अक्रमom;

	driver_key = अक्रमom & ~iwdev->mr_stagmask;
	next_stag_index = (अक्रमom & iwdev->mr_stagmask) >> 8;
	next_stag_index %= iwdev->max_mr;

	ret = i40iw_alloc_resource(iwdev,
				   iwdev->allocated_mrs, iwdev->max_mr,
				   &stag_index, &next_stag_index);
	अगर (!ret) अणु
		stag = stag_index << I40IW_CQPSQ_STAG_IDX_SHIFT;
		stag |= driver_key;
		stag += (u32)consumer_key;
		i40iw_add_devusecount(iwdev);
	पूर्ण
	वापस stag;
पूर्ण

/**
 * i40iw_next_pbl_addr - Get next pbl address
 * @pbl: poपूर्णांकer to a pble
 * @pinfo: info poपूर्णांकer
 * @idx: index
 */
अटल अंतरभूत u64 *i40iw_next_pbl_addr(u64 *pbl,
				       काष्ठा i40iw_pble_info **pinfo,
				       u32 *idx)
अणु
	*idx += 1;
	अगर ((!(*pinfo)) || (*idx != (*pinfo)->cnt))
		वापस ++pbl;
	*idx = 0;
	(*pinfo)++;
	वापस (u64 *)(*pinfo)->addr;
पूर्ण

/**
 * i40iw_copy_user_pgaddrs - copy user page address to pble's os locally
 * @iwmr: iwmr क्रम IB's user page addresses
 * @pbl: ple poपूर्णांकer to save 1 level or 0 level pble
 * @level: indicated level 0, 1 or 2
 */
अटल व्योम i40iw_copy_user_pgaddrs(काष्ठा i40iw_mr *iwmr,
				    u64 *pbl,
				    क्रमागत i40iw_pble_level level)
अणु
	काष्ठा ib_umem *region = iwmr->region;
	काष्ठा i40iw_pbl *iwpbl = &iwmr->iwpbl;
	काष्ठा i40iw_pble_alloc *palloc = &iwpbl->pble_alloc;
	काष्ठा i40iw_pble_info *pinfo;
	काष्ठा ib_block_iter biter;
	u32 idx = 0;

	pinfo = (level == I40IW_LEVEL_1) ? शून्य : palloc->level2.leaf;

	अगर (iwmr->type == IW_MEMREG_TYPE_QP)
		iwpbl->qp_mr.sq_page = sg_page(region->sg_head.sgl);

	rdma_umem_क्रम_each_dma_block(region, &biter, iwmr->page_size) अणु
		*pbl = rdma_block_iter_dma_address(&biter);
		pbl = i40iw_next_pbl_addr(pbl, &pinfo, &idx);
	पूर्ण
पूर्ण

/**
 * i40iw_check_mem_contiguous - check अगर pbls stored in arr are contiguous
 * @arr: lvl1 pbl array
 * @npages: page count
 * @pg_size: page size
 *
 */
अटल bool i40iw_check_mem_contiguous(u64 *arr, u32 npages, u32 pg_size)
अणु
	u32 pg_idx;

	क्रम (pg_idx = 0; pg_idx < npages; pg_idx++) अणु
		अगर ((*arr + (pg_size * pg_idx)) != arr[pg_idx])
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/**
 * i40iw_check_mr_contiguous - check अगर MR is physically contiguous
 * @palloc: pbl allocation काष्ठा
 * @pg_size: page size
 */
अटल bool i40iw_check_mr_contiguous(काष्ठा i40iw_pble_alloc *palloc, u32 pg_size)
अणु
	काष्ठा i40iw_pble_level2 *lvl2 = &palloc->level2;
	काष्ठा i40iw_pble_info *leaf = lvl2->leaf;
	u64 *arr = शून्य;
	u64 *start_addr = शून्य;
	पूर्णांक i;
	bool ret;

	अगर (palloc->level == I40IW_LEVEL_1) अणु
		arr = (u64 *)palloc->level1.addr;
		ret = i40iw_check_mem_contiguous(arr, palloc->total_cnt, pg_size);
		वापस ret;
	पूर्ण

	start_addr = (u64 *)leaf->addr;

	क्रम (i = 0; i < lvl2->leaf_cnt; i++, leaf++) अणु
		arr = (u64 *)leaf->addr;
		अगर ((*start_addr + (i * pg_size * PBLE_PER_PAGE)) != *arr)
			वापस false;
		ret = i40iw_check_mem_contiguous(arr, leaf->cnt, pg_size);
		अगर (!ret)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * i40iw_setup_pbles - copy user pg address to pble's
 * @iwdev: iwarp device
 * @iwmr: mr poपूर्णांकer क्रम this memory registration
 * @use_pbles: flag अगर to use pble's
 */
अटल पूर्णांक i40iw_setup_pbles(काष्ठा i40iw_device *iwdev,
			     काष्ठा i40iw_mr *iwmr,
			     bool use_pbles)
अणु
	काष्ठा i40iw_pbl *iwpbl = &iwmr->iwpbl;
	काष्ठा i40iw_pble_alloc *palloc = &iwpbl->pble_alloc;
	काष्ठा i40iw_pble_info *pinfo;
	u64 *pbl;
	क्रमागत i40iw_status_code status;
	क्रमागत i40iw_pble_level level = I40IW_LEVEL_1;

	अगर (use_pbles) अणु
		mutex_lock(&iwdev->pbl_mutex);
		status = i40iw_get_pble(&iwdev->sc_dev, iwdev->pble_rsrc, palloc, iwmr->page_cnt);
		mutex_unlock(&iwdev->pbl_mutex);
		अगर (status)
			वापस -ENOMEM;

		iwpbl->pbl_allocated = true;
		level = palloc->level;
		pinfo = (level == I40IW_LEVEL_1) ? &palloc->level1 : palloc->level2.leaf;
		pbl = (u64 *)pinfo->addr;
	पूर्ण अन्यथा अणु
		pbl = iwmr->pgaddrmem;
	पूर्ण

	i40iw_copy_user_pgaddrs(iwmr, pbl, level);

	अगर (use_pbles)
		iwmr->pgaddrmem[0] = *pbl;

	वापस 0;
पूर्ण

/**
 * i40iw_handle_q_mem - handle memory क्रम qp and cq
 * @iwdev: iwarp device
 * @req: inक्रमmation क्रम q memory management
 * @iwpbl: pble काष्ठा
 * @use_pbles: flag to use pble
 */
अटल पूर्णांक i40iw_handle_q_mem(काष्ठा i40iw_device *iwdev,
			      काष्ठा i40iw_mem_reg_req *req,
			      काष्ठा i40iw_pbl *iwpbl,
			      bool use_pbles)
अणु
	काष्ठा i40iw_pble_alloc *palloc = &iwpbl->pble_alloc;
	काष्ठा i40iw_mr *iwmr = iwpbl->iwmr;
	काष्ठा i40iw_qp_mr *qpmr = &iwpbl->qp_mr;
	काष्ठा i40iw_cq_mr *cqmr = &iwpbl->cq_mr;
	काष्ठा i40iw_hmc_pble *hmc_p;
	u64 *arr = iwmr->pgaddrmem;
	u32 pg_size;
	पूर्णांक err;
	पूर्णांक total;
	bool ret = true;

	total = req->sq_pages + req->rq_pages + req->cq_pages;
	pg_size = iwmr->page_size;

	err = i40iw_setup_pbles(iwdev, iwmr, use_pbles);
	अगर (err)
		वापस err;

	अगर (use_pbles && (palloc->level != I40IW_LEVEL_1)) अणु
		i40iw_मुक्त_pble(iwdev->pble_rsrc, palloc);
		iwpbl->pbl_allocated = false;
		वापस -ENOMEM;
	पूर्ण

	अगर (use_pbles)
		arr = (u64 *)palloc->level1.addr;

	अगर (iwmr->type == IW_MEMREG_TYPE_QP) अणु
		hmc_p = &qpmr->sq_pbl;
		qpmr->shaकरोw = (dma_addr_t)arr[total];

		अगर (use_pbles) अणु
			ret = i40iw_check_mem_contiguous(arr, req->sq_pages, pg_size);
			अगर (ret)
				ret = i40iw_check_mem_contiguous(&arr[req->sq_pages], req->rq_pages, pg_size);
		पूर्ण

		अगर (!ret) अणु
			hmc_p->idx = palloc->level1.idx;
			hmc_p = &qpmr->rq_pbl;
			hmc_p->idx = palloc->level1.idx + req->sq_pages;
		पूर्ण अन्यथा अणु
			hmc_p->addr = arr[0];
			hmc_p = &qpmr->rq_pbl;
			hmc_p->addr = arr[req->sq_pages];
		पूर्ण
	पूर्ण अन्यथा अणु		/* CQ */
		hmc_p = &cqmr->cq_pbl;
		cqmr->shaकरोw = (dma_addr_t)arr[total];

		अगर (use_pbles)
			ret = i40iw_check_mem_contiguous(arr, req->cq_pages, pg_size);

		अगर (!ret)
			hmc_p->idx = palloc->level1.idx;
		अन्यथा
			hmc_p->addr = arr[0];
	पूर्ण

	अगर (use_pbles && ret) अणु
		i40iw_मुक्त_pble(iwdev->pble_rsrc, palloc);
		iwpbl->pbl_allocated = false;
	पूर्ण

	वापस err;
पूर्ण

/**
 * i40iw_hw_alloc_stag - cqp command to allocate stag
 * @iwdev: iwarp device
 * @iwmr: iwarp mr poपूर्णांकer
 */
अटल पूर्णांक i40iw_hw_alloc_stag(काष्ठा i40iw_device *iwdev, काष्ठा i40iw_mr *iwmr)
अणु
	काष्ठा i40iw_allocate_stag_info *info;
	काष्ठा i40iw_pd *iwpd = to_iwpd(iwmr->ibmr.pd);
	क्रमागत i40iw_status_code status;
	पूर्णांक err = 0;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, true);
	अगर (!cqp_request)
		वापस -ENOMEM;

	cqp_info = &cqp_request->info;
	info = &cqp_info->in.u.alloc_stag.info;
	स_रखो(info, 0, माप(*info));
	info->page_size = PAGE_SIZE;
	info->stag_idx = iwmr->stag >> I40IW_CQPSQ_STAG_IDX_SHIFT;
	info->pd_id = iwpd->sc_pd.pd_id;
	info->total_len = iwmr->length;
	info->remote_access = true;
	cqp_info->cqp_cmd = OP_ALLOC_STAG;
	cqp_info->post_sq = 1;
	cqp_info->in.u.alloc_stag.dev = &iwdev->sc_dev;
	cqp_info->in.u.alloc_stag.scratch = (uपूर्णांकptr_t)cqp_request;

	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (status) अणु
		err = -ENOMEM;
		i40iw_pr_err("CQP-OP MR Reg fail");
	पूर्ण
	वापस err;
पूर्ण

/**
 * i40iw_alloc_mr - रेजिस्टर stag क्रम fast memory registration
 * @pd: ibpd poपूर्णांकer
 * @mr_type: memory क्रम stag registrion
 * @max_num_sg: man number of pages
 */
अटल काष्ठा ib_mr *i40iw_alloc_mr(काष्ठा ib_pd *pd, क्रमागत ib_mr_type mr_type,
				    u32 max_num_sg)
अणु
	काष्ठा i40iw_pd *iwpd = to_iwpd(pd);
	काष्ठा i40iw_device *iwdev = to_iwdev(pd->device);
	काष्ठा i40iw_pble_alloc *palloc;
	काष्ठा i40iw_pbl *iwpbl;
	काष्ठा i40iw_mr *iwmr;
	क्रमागत i40iw_status_code status;
	u32 stag;
	पूर्णांक err_code = -ENOMEM;

	iwmr = kzalloc(माप(*iwmr), GFP_KERNEL);
	अगर (!iwmr)
		वापस ERR_PTR(-ENOMEM);

	stag = i40iw_create_stag(iwdev);
	अगर (!stag) अणु
		err_code = -EOVERFLOW;
		जाओ err;
	पूर्ण
	stag &= ~I40IW_CQPSQ_STAG_KEY_MASK;
	iwmr->stag = stag;
	iwmr->ibmr.rkey = stag;
	iwmr->ibmr.lkey = stag;
	iwmr->ibmr.pd = pd;
	iwmr->ibmr.device = pd->device;
	iwpbl = &iwmr->iwpbl;
	iwpbl->iwmr = iwmr;
	iwmr->type = IW_MEMREG_TYPE_MEM;
	palloc = &iwpbl->pble_alloc;
	iwmr->page_cnt = max_num_sg;
	mutex_lock(&iwdev->pbl_mutex);
	status = i40iw_get_pble(&iwdev->sc_dev, iwdev->pble_rsrc, palloc, iwmr->page_cnt);
	mutex_unlock(&iwdev->pbl_mutex);
	अगर (status)
		जाओ err1;

	अगर (palloc->level != I40IW_LEVEL_1)
		जाओ err2;
	err_code = i40iw_hw_alloc_stag(iwdev, iwmr);
	अगर (err_code)
		जाओ err2;
	iwpbl->pbl_allocated = true;
	i40iw_add_pdusecount(iwpd);
	वापस &iwmr->ibmr;
err2:
	i40iw_मुक्त_pble(iwdev->pble_rsrc, palloc);
err1:
	i40iw_मुक्त_stag(iwdev, stag);
err:
	kमुक्त(iwmr);
	वापस ERR_PTR(err_code);
पूर्ण

/**
 * i40iw_set_page - populate pbl list क्रम fmr
 * @ibmr: ib mem to access iwarp mr poपूर्णांकer
 * @addr: page dma address fro pbl list
 */
अटल पूर्णांक i40iw_set_page(काष्ठा ib_mr *ibmr, u64 addr)
अणु
	काष्ठा i40iw_mr *iwmr = to_iwmr(ibmr);
	काष्ठा i40iw_pbl *iwpbl = &iwmr->iwpbl;
	काष्ठा i40iw_pble_alloc *palloc = &iwpbl->pble_alloc;
	u64 *pbl;

	अगर (unlikely(iwmr->npages == iwmr->page_cnt))
		वापस -ENOMEM;

	pbl = (u64 *)palloc->level1.addr;
	pbl[iwmr->npages++] = cpu_to_le64(addr);
	वापस 0;
पूर्ण

/**
 * i40iw_map_mr_sg - map of sg list क्रम fmr
 * @ibmr: ib mem to access iwarp mr poपूर्णांकer
 * @sg: scatter gather list क्रम fmr
 * @sg_nents: number of sg pages
 * @sg_offset: scatter gather offset
 */
अटल पूर्णांक i40iw_map_mr_sg(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *sg,
			   पूर्णांक sg_nents, अचिन्हित पूर्णांक *sg_offset)
अणु
	काष्ठा i40iw_mr *iwmr = to_iwmr(ibmr);

	iwmr->npages = 0;
	वापस ib_sg_to_pages(ibmr, sg, sg_nents, sg_offset, i40iw_set_page);
पूर्ण

/**
 * i40iw_drain_sq - drain the send queue
 * @ibqp: ib qp poपूर्णांकer
 */
अटल व्योम i40iw_drain_sq(काष्ठा ib_qp *ibqp)
अणु
	काष्ठा i40iw_qp *iwqp = to_iwqp(ibqp);
	काष्ठा i40iw_sc_qp *qp = &iwqp->sc_qp;

	अगर (I40IW_RING_MORE_WORK(qp->qp_uk.sq_ring))
		रुको_क्रम_completion(&iwqp->sq_drained);
पूर्ण

/**
 * i40iw_drain_rq - drain the receive queue
 * @ibqp: ib qp poपूर्णांकer
 */
अटल व्योम i40iw_drain_rq(काष्ठा ib_qp *ibqp)
अणु
	काष्ठा i40iw_qp *iwqp = to_iwqp(ibqp);
	काष्ठा i40iw_sc_qp *qp = &iwqp->sc_qp;

	अगर (I40IW_RING_MORE_WORK(qp->qp_uk.rq_ring))
		रुको_क्रम_completion(&iwqp->rq_drained);
पूर्ण

/**
 * i40iw_hwreg_mr - send cqp command क्रम memory registration
 * @iwdev: iwarp device
 * @iwmr: iwarp mr poपूर्णांकer
 * @access: access क्रम MR
 */
अटल पूर्णांक i40iw_hwreg_mr(काष्ठा i40iw_device *iwdev,
			  काष्ठा i40iw_mr *iwmr,
			  u16 access)
अणु
	काष्ठा i40iw_pbl *iwpbl = &iwmr->iwpbl;
	काष्ठा i40iw_reg_ns_stag_info *stag_info;
	काष्ठा i40iw_pd *iwpd = to_iwpd(iwmr->ibmr.pd);
	काष्ठा i40iw_pble_alloc *palloc = &iwpbl->pble_alloc;
	क्रमागत i40iw_status_code status;
	पूर्णांक err = 0;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, true);
	अगर (!cqp_request)
		वापस -ENOMEM;

	cqp_info = &cqp_request->info;
	stag_info = &cqp_info->in.u.mr_reg_non_shared.info;
	स_रखो(stag_info, 0, माप(*stag_info));
	stag_info->va = (व्योम *)(अचिन्हित दीर्घ)iwpbl->user_base;
	stag_info->stag_idx = iwmr->stag >> I40IW_CQPSQ_STAG_IDX_SHIFT;
	stag_info->stag_key = (u8)iwmr->stag;
	stag_info->total_len = iwmr->length;
	stag_info->access_rights = access;
	stag_info->pd_id = iwpd->sc_pd.pd_id;
	stag_info->addr_type = I40IW_ADDR_TYPE_VA_BASED;
	stag_info->page_size = iwmr->page_size;

	अगर (iwpbl->pbl_allocated) अणु
		अगर (palloc->level == I40IW_LEVEL_1) अणु
			stag_info->first_pm_pbl_index = palloc->level1.idx;
			stag_info->chunk_size = 1;
		पूर्ण अन्यथा अणु
			stag_info->first_pm_pbl_index = palloc->level2.root.idx;
			stag_info->chunk_size = 3;
		पूर्ण
	पूर्ण अन्यथा अणु
		stag_info->reg_addr_pa = iwmr->pgaddrmem[0];
	पूर्ण

	cqp_info->cqp_cmd = OP_MR_REG_NON_SHARED;
	cqp_info->post_sq = 1;
	cqp_info->in.u.mr_reg_non_shared.dev = &iwdev->sc_dev;
	cqp_info->in.u.mr_reg_non_shared.scratch = (uपूर्णांकptr_t)cqp_request;

	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (status) अणु
		err = -ENOMEM;
		i40iw_pr_err("CQP-OP MR Reg fail");
	पूर्ण
	वापस err;
पूर्ण

/**
 * i40iw_reg_user_mr - Register a user memory region
 * @pd: ptr of pd
 * @start: भव start address
 * @length: length of mr
 * @virt: भव address
 * @acc: access of mr
 * @udata: user data
 */
अटल काष्ठा ib_mr *i40iw_reg_user_mr(काष्ठा ib_pd *pd,
				       u64 start,
				       u64 length,
				       u64 virt,
				       पूर्णांक acc,
				       काष्ठा ib_udata *udata)
अणु
	काष्ठा i40iw_pd *iwpd = to_iwpd(pd);
	काष्ठा i40iw_device *iwdev = to_iwdev(pd->device);
	काष्ठा i40iw_ucontext *ucontext = rdma_udata_to_drv_context(
		udata, काष्ठा i40iw_ucontext, ibucontext);
	काष्ठा i40iw_pble_alloc *palloc;
	काष्ठा i40iw_pbl *iwpbl;
	काष्ठा i40iw_mr *iwmr;
	काष्ठा ib_umem *region;
	काष्ठा i40iw_mem_reg_req req;
	u32 stag = 0;
	u16 access;
	bool use_pbles = false;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = -ENOSYS;
	पूर्णांक ret;

	अगर (!udata)
		वापस ERR_PTR(-EOPNOTSUPP);

	अगर (iwdev->closing)
		वापस ERR_PTR(-ENODEV);

	अगर (length > I40IW_MAX_MR_SIZE)
		वापस ERR_PTR(-EINVAL);
	region = ib_umem_get(pd->device, start, length, acc);
	अगर (IS_ERR(region))
		वापस (काष्ठा ib_mr *)region;

	अगर (ib_copy_from_udata(&req, udata, माप(req))) अणु
		ib_umem_release(region);
		वापस ERR_PTR(-EFAULT);
	पूर्ण

	iwmr = kzalloc(माप(*iwmr), GFP_KERNEL);
	अगर (!iwmr) अणु
		ib_umem_release(region);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	iwpbl = &iwmr->iwpbl;
	iwpbl->iwmr = iwmr;
	iwmr->region = region;
	iwmr->ibmr.pd = pd;
	iwmr->ibmr.device = pd->device;

	iwmr->page_size = PAGE_SIZE;
	अगर (req.reg_type == IW_MEMREG_TYPE_MEM)
		iwmr->page_size = ib_umem_find_best_pgsz(region, SZ_4K | SZ_2M,
							 virt);
	iwmr->length = region->length;

	iwpbl->user_base = virt;
	palloc = &iwpbl->pble_alloc;

	iwmr->type = req.reg_type;
	iwmr->page_cnt = ib_umem_num_dma_blocks(region, iwmr->page_size);

	चयन (req.reg_type) अणु
	हाल IW_MEMREG_TYPE_QP:
		use_pbles = ((req.sq_pages + req.rq_pages) > 2);
		err = i40iw_handle_q_mem(iwdev, &req, iwpbl, use_pbles);
		अगर (err)
			जाओ error;
		spin_lock_irqsave(&ucontext->qp_reg_mem_list_lock, flags);
		list_add_tail(&iwpbl->list, &ucontext->qp_reg_mem_list);
		iwpbl->on_list = true;
		spin_unlock_irqrestore(&ucontext->qp_reg_mem_list_lock, flags);
		अवरोध;
	हाल IW_MEMREG_TYPE_CQ:
		use_pbles = (req.cq_pages > 1);
		err = i40iw_handle_q_mem(iwdev, &req, iwpbl, use_pbles);
		अगर (err)
			जाओ error;

		spin_lock_irqsave(&ucontext->cq_reg_mem_list_lock, flags);
		list_add_tail(&iwpbl->list, &ucontext->cq_reg_mem_list);
		iwpbl->on_list = true;
		spin_unlock_irqrestore(&ucontext->cq_reg_mem_list_lock, flags);
		अवरोध;
	हाल IW_MEMREG_TYPE_MEM:
		use_pbles = (iwmr->page_cnt != 1);
		access = I40IW_ACCESS_FLAGS_LOCALREAD;

		err = i40iw_setup_pbles(iwdev, iwmr, use_pbles);
		अगर (err)
			जाओ error;

		अगर (use_pbles) अणु
			ret = i40iw_check_mr_contiguous(palloc, iwmr->page_size);
			अगर (ret) अणु
				i40iw_मुक्त_pble(iwdev->pble_rsrc, palloc);
				iwpbl->pbl_allocated = false;
			पूर्ण
		पूर्ण

		access |= i40iw_get_user_access(acc);
		stag = i40iw_create_stag(iwdev);
		अगर (!stag) अणु
			err = -ENOMEM;
			जाओ error;
		पूर्ण

		iwmr->stag = stag;
		iwmr->ibmr.rkey = stag;
		iwmr->ibmr.lkey = stag;

		err = i40iw_hwreg_mr(iwdev, iwmr, access);
		अगर (err) अणु
			i40iw_मुक्त_stag(iwdev, stag);
			जाओ error;
		पूर्ण

		अवरोध;
	शेष:
		जाओ error;
	पूर्ण

	iwmr->type = req.reg_type;
	अगर (req.reg_type == IW_MEMREG_TYPE_MEM)
		i40iw_add_pdusecount(iwpd);
	वापस &iwmr->ibmr;

error:
	अगर (palloc->level != I40IW_LEVEL_0 && iwpbl->pbl_allocated)
		i40iw_मुक्त_pble(iwdev->pble_rsrc, palloc);
	ib_umem_release(region);
	kमुक्त(iwmr);
	वापस ERR_PTR(err);
पूर्ण

/**
 * i40iw_reg_phys_mr - रेजिस्टर kernel physical memory
 * @pd: ibpd poपूर्णांकer
 * @addr: physical address of memory to रेजिस्टर
 * @size: size of memory to रेजिस्टर
 * @acc: Access rights
 * @ioबहु_शुरू: start of भव address क्रम physical buffers
 */
काष्ठा ib_mr *i40iw_reg_phys_mr(काष्ठा ib_pd *pd,
				u64 addr,
				u64 size,
				पूर्णांक acc,
				u64 *ioबहु_शुरू)
अणु
	काष्ठा i40iw_pd *iwpd = to_iwpd(pd);
	काष्ठा i40iw_device *iwdev = to_iwdev(pd->device);
	काष्ठा i40iw_pbl *iwpbl;
	काष्ठा i40iw_mr *iwmr;
	क्रमागत i40iw_status_code status;
	u32 stag;
	u16 access = I40IW_ACCESS_FLAGS_LOCALREAD;
	पूर्णांक ret;

	iwmr = kzalloc(माप(*iwmr), GFP_KERNEL);
	अगर (!iwmr)
		वापस ERR_PTR(-ENOMEM);
	iwmr->ibmr.pd = pd;
	iwmr->ibmr.device = pd->device;
	iwpbl = &iwmr->iwpbl;
	iwpbl->iwmr = iwmr;
	iwmr->type = IW_MEMREG_TYPE_MEM;
	iwpbl->user_base = *ioबहु_शुरू;
	stag = i40iw_create_stag(iwdev);
	अगर (!stag) अणु
		ret = -EOVERFLOW;
		जाओ err;
	पूर्ण
	access |= i40iw_get_user_access(acc);
	iwmr->stag = stag;
	iwmr->ibmr.rkey = stag;
	iwmr->ibmr.lkey = stag;
	iwmr->page_cnt = 1;
	iwmr->pgaddrmem[0]  = addr;
	iwmr->length = size;
	status = i40iw_hwreg_mr(iwdev, iwmr, access);
	अगर (status) अणु
		i40iw_मुक्त_stag(iwdev, stag);
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	i40iw_add_pdusecount(iwpd);
	वापस &iwmr->ibmr;
 err:
	kमुक्त(iwmr);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * i40iw_get_dma_mr - रेजिस्टर physical mem
 * @pd: ptr of pd
 * @acc: access क्रम memory
 */
अटल काष्ठा ib_mr *i40iw_get_dma_mr(काष्ठा ib_pd *pd, पूर्णांक acc)
अणु
	u64 kva = 0;

	वापस i40iw_reg_phys_mr(pd, 0, 0, acc, &kva);
पूर्ण

/**
 * i40iw_del_memlist - Deleting pbl list entries क्रम CQ/QP
 * @iwmr: iwmr क्रम IB's user page addresses
 * @ucontext: ptr to user context
 */
अटल व्योम i40iw_del_memlist(काष्ठा i40iw_mr *iwmr,
			      काष्ठा i40iw_ucontext *ucontext)
अणु
	काष्ठा i40iw_pbl *iwpbl = &iwmr->iwpbl;
	अचिन्हित दीर्घ flags;

	चयन (iwmr->type) अणु
	हाल IW_MEMREG_TYPE_CQ:
		spin_lock_irqsave(&ucontext->cq_reg_mem_list_lock, flags);
		अगर (iwpbl->on_list) अणु
			iwpbl->on_list = false;
			list_del(&iwpbl->list);
		पूर्ण
		spin_unlock_irqrestore(&ucontext->cq_reg_mem_list_lock, flags);
		अवरोध;
	हाल IW_MEMREG_TYPE_QP:
		spin_lock_irqsave(&ucontext->qp_reg_mem_list_lock, flags);
		अगर (iwpbl->on_list) अणु
			iwpbl->on_list = false;
			list_del(&iwpbl->list);
		पूर्ण
		spin_unlock_irqrestore(&ucontext->qp_reg_mem_list_lock, flags);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * i40iw_dereg_mr - deरेजिस्टर mr
 * @ib_mr: mr ptr क्रम dereg
 * @udata: user data
 */
अटल पूर्णांक i40iw_dereg_mr(काष्ठा ib_mr *ib_mr, काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_pd *ibpd = ib_mr->pd;
	काष्ठा i40iw_pd *iwpd = to_iwpd(ibpd);
	काष्ठा i40iw_mr *iwmr = to_iwmr(ib_mr);
	काष्ठा i40iw_device *iwdev = to_iwdev(ib_mr->device);
	क्रमागत i40iw_status_code status;
	काष्ठा i40iw_dealloc_stag_info *info;
	काष्ठा i40iw_pbl *iwpbl = &iwmr->iwpbl;
	काष्ठा i40iw_pble_alloc *palloc = &iwpbl->pble_alloc;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;
	u32 stag_idx;

	ib_umem_release(iwmr->region);

	अगर (iwmr->type != IW_MEMREG_TYPE_MEM) अणु
		/* region is released. only test क्रम userness. */
		अगर (iwmr->region) अणु
			काष्ठा i40iw_ucontext *ucontext =
				rdma_udata_to_drv_context(
					udata,
					काष्ठा i40iw_ucontext,
					ibucontext);

			i40iw_del_memlist(iwmr, ucontext);
		पूर्ण
		अगर (iwpbl->pbl_allocated && iwmr->type != IW_MEMREG_TYPE_QP)
			i40iw_मुक्त_pble(iwdev->pble_rsrc, palloc);
		kमुक्त(iwmr);
		वापस 0;
	पूर्ण

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, true);
	अगर (!cqp_request)
		वापस -ENOMEM;

	cqp_info = &cqp_request->info;
	info = &cqp_info->in.u.dealloc_stag.info;
	स_रखो(info, 0, माप(*info));

	info->pd_id = cpu_to_le32(iwpd->sc_pd.pd_id & 0x00007fff);
	info->stag_idx = RS_64_1(ib_mr->rkey, I40IW_CQPSQ_STAG_IDX_SHIFT);
	stag_idx = info->stag_idx;
	info->mr = true;
	अगर (iwpbl->pbl_allocated)
		info->dealloc_pbl = true;

	cqp_info->cqp_cmd = OP_DEALLOC_STAG;
	cqp_info->post_sq = 1;
	cqp_info->in.u.dealloc_stag.dev = &iwdev->sc_dev;
	cqp_info->in.u.dealloc_stag.scratch = (uपूर्णांकptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (status)
		i40iw_pr_err("CQP-OP dealloc failed for stag_idx = 0x%x\n", stag_idx);
	i40iw_rem_pdusecount(iwpd, iwdev);
	i40iw_मुक्त_stag(iwdev, iwmr->stag);
	अगर (iwpbl->pbl_allocated)
		i40iw_मुक्त_pble(iwdev->pble_rsrc, palloc);
	kमुक्त(iwmr);
	वापस 0;
पूर्ण

/*
 * hw_rev_show
 */
अटल sमाप_प्रकार hw_rev_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i40iw_ib_device *iwibdev =
		rdma_device_to_drv_device(dev, काष्ठा i40iw_ib_device, ibdev);
	u32 hw_rev = iwibdev->iwdev->sc_dev.hw_rev;

	वापस sysfs_emit(buf, "%x\n", hw_rev);
पूर्ण
अटल DEVICE_ATTR_RO(hw_rev);

/*
 * hca_type_show
 */
अटल sमाप_प्रकार hca_type_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "I40IW\n");
पूर्ण
अटल DEVICE_ATTR_RO(hca_type);

/*
 * board_id_show
 */
अटल sमाप_प्रकार board_id_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%.*s\n", 32, "I40IW Board ID");
पूर्ण
अटल DEVICE_ATTR_RO(board_id);

अटल काष्ठा attribute *i40iw_dev_attributes[] = अणु
	&dev_attr_hw_rev.attr,
	&dev_attr_hca_type.attr,
	&dev_attr_board_id.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group i40iw_attr_group = अणु
	.attrs = i40iw_dev_attributes,
पूर्ण;

/**
 * i40iw_copy_sg_list - copy sg list क्रम qp
 * @sg_list: copied पूर्णांकo sg_list
 * @sgl: copy from sgl
 * @num_sges: count of sg entries
 */
अटल व्योम i40iw_copy_sg_list(काष्ठा i40iw_sge *sg_list, काष्ठा ib_sge *sgl, पूर्णांक num_sges)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; (i < num_sges) && (i < I40IW_MAX_WQ_FRAGMENT_COUNT); i++) अणु
		sg_list[i].tag_off = sgl[i].addr;
		sg_list[i].len = sgl[i].length;
		sg_list[i].stag = sgl[i].lkey;
	पूर्ण
पूर्ण

/**
 * i40iw_post_send -  kernel application wr
 * @ibqp: qp ptr क्रम wr
 * @ib_wr: work request ptr
 * @bad_wr: वापस of bad wr अगर err
 */
अटल पूर्णांक i40iw_post_send(काष्ठा ib_qp *ibqp,
			   स्थिर काष्ठा ib_send_wr *ib_wr,
			   स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	काष्ठा i40iw_qp *iwqp;
	काष्ठा i40iw_qp_uk *ukqp;
	काष्ठा i40iw_post_sq_info info;
	क्रमागत i40iw_status_code ret;
	पूर्णांक err = 0;
	अचिन्हित दीर्घ flags;
	bool inv_stag;

	iwqp = (काष्ठा i40iw_qp *)ibqp;
	ukqp = &iwqp->sc_qp.qp_uk;

	spin_lock_irqsave(&iwqp->lock, flags);

	अगर (iwqp->flush_issued) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	जबतक (ib_wr) अणु
		inv_stag = false;
		स_रखो(&info, 0, माप(info));
		info.wr_id = (u64)(ib_wr->wr_id);
		अगर ((ib_wr->send_flags & IB_SEND_SIGNALED) || iwqp->sig_all)
			info.संकेतed = true;
		अगर (ib_wr->send_flags & IB_SEND_FENCE)
			info.पढ़ो_fence = true;

		चयन (ib_wr->opcode) अणु
		हाल IB_WR_SEND:
		हाल IB_WR_SEND_WITH_INV:
			अगर (ib_wr->opcode == IB_WR_SEND) अणु
				अगर (ib_wr->send_flags & IB_SEND_SOLICITED)
					info.op_type = I40IW_OP_TYPE_SEND_SOL;
				अन्यथा
					info.op_type = I40IW_OP_TYPE_SEND;
			पूर्ण अन्यथा अणु
				अगर (ib_wr->send_flags & IB_SEND_SOLICITED)
					info.op_type = I40IW_OP_TYPE_SEND_SOL_INV;
				अन्यथा
					info.op_type = I40IW_OP_TYPE_SEND_INV;
			पूर्ण

			अगर (ib_wr->send_flags & IB_SEND_INLINE) अणु
				info.op.अंतरभूत_send.data = (व्योम *)(अचिन्हित दीर्घ)ib_wr->sg_list[0].addr;
				info.op.अंतरभूत_send.len = ib_wr->sg_list[0].length;
				ret = ukqp->ops.iw_अंतरभूत_send(ukqp, &info, ib_wr->ex.invalidate_rkey, false);
			पूर्ण अन्यथा अणु
				info.op.send.num_sges = ib_wr->num_sge;
				info.op.send.sg_list = (काष्ठा i40iw_sge *)ib_wr->sg_list;
				ret = ukqp->ops.iw_send(ukqp, &info, ib_wr->ex.invalidate_rkey, false);
			पूर्ण

			अगर (ret) अणु
				अगर (ret == I40IW_ERR_QP_TOOMANY_WRS_POSTED)
					err = -ENOMEM;
				अन्यथा
					err = -EINVAL;
			पूर्ण
			अवरोध;
		हाल IB_WR_RDMA_WRITE:
			info.op_type = I40IW_OP_TYPE_RDMA_WRITE;

			अगर (ib_wr->send_flags & IB_SEND_INLINE) अणु
				info.op.अंतरभूत_rdma_ग_लिखो.data = (व्योम *)(अचिन्हित दीर्घ)ib_wr->sg_list[0].addr;
				info.op.अंतरभूत_rdma_ग_लिखो.len = ib_wr->sg_list[0].length;
				info.op.अंतरभूत_rdma_ग_लिखो.rem_addr.tag_off = rdma_wr(ib_wr)->remote_addr;
				info.op.अंतरभूत_rdma_ग_लिखो.rem_addr.stag = rdma_wr(ib_wr)->rkey;
				ret = ukqp->ops.iw_अंतरभूत_rdma_ग_लिखो(ukqp, &info, false);
			पूर्ण अन्यथा अणु
				info.op.rdma_ग_लिखो.lo_sg_list = (व्योम *)ib_wr->sg_list;
				info.op.rdma_ग_लिखो.num_lo_sges = ib_wr->num_sge;
				info.op.rdma_ग_लिखो.rem_addr.tag_off = rdma_wr(ib_wr)->remote_addr;
				info.op.rdma_ग_लिखो.rem_addr.stag = rdma_wr(ib_wr)->rkey;
				ret = ukqp->ops.iw_rdma_ग_लिखो(ukqp, &info, false);
			पूर्ण

			अगर (ret) अणु
				अगर (ret == I40IW_ERR_QP_TOOMANY_WRS_POSTED)
					err = -ENOMEM;
				अन्यथा
					err = -EINVAL;
			पूर्ण
			अवरोध;
		हाल IB_WR_RDMA_READ_WITH_INV:
			inv_stag = true;
			fallthrough;
		हाल IB_WR_RDMA_READ:
			अगर (ib_wr->num_sge > I40IW_MAX_SGE_RD) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
			info.op_type = I40IW_OP_TYPE_RDMA_READ;
			info.op.rdma_पढ़ो.rem_addr.tag_off = rdma_wr(ib_wr)->remote_addr;
			info.op.rdma_पढ़ो.rem_addr.stag = rdma_wr(ib_wr)->rkey;
			info.op.rdma_पढ़ो.lo_addr.tag_off = ib_wr->sg_list->addr;
			info.op.rdma_पढ़ो.lo_addr.stag = ib_wr->sg_list->lkey;
			info.op.rdma_पढ़ो.lo_addr.len = ib_wr->sg_list->length;
			ret = ukqp->ops.iw_rdma_पढ़ो(ukqp, &info, inv_stag, false);
			अगर (ret) अणु
				अगर (ret == I40IW_ERR_QP_TOOMANY_WRS_POSTED)
					err = -ENOMEM;
				अन्यथा
					err = -EINVAL;
			पूर्ण
			अवरोध;
		हाल IB_WR_LOCAL_INV:
			info.op_type = I40IW_OP_TYPE_INV_STAG;
			info.op.inv_local_stag.target_stag = ib_wr->ex.invalidate_rkey;
			ret = ukqp->ops.iw_stag_local_invalidate(ukqp, &info, true);
			अगर (ret)
				err = -ENOMEM;
			अवरोध;
		हाल IB_WR_REG_MR:
		अणु
			काष्ठा i40iw_mr *iwmr = to_iwmr(reg_wr(ib_wr)->mr);
			पूर्णांक flags = reg_wr(ib_wr)->access;
			काष्ठा i40iw_pble_alloc *palloc = &iwmr->iwpbl.pble_alloc;
			काष्ठा i40iw_sc_dev *dev = &iwqp->iwdev->sc_dev;
			काष्ठा i40iw_fast_reg_stag_info info;

			स_रखो(&info, 0, माप(info));
			info.access_rights = I40IW_ACCESS_FLAGS_LOCALREAD;
			info.access_rights |= i40iw_get_user_access(flags);
			info.stag_key = reg_wr(ib_wr)->key & 0xff;
			info.stag_idx = reg_wr(ib_wr)->key >> 8;
			info.page_size = reg_wr(ib_wr)->mr->page_size;
			info.wr_id = ib_wr->wr_id;

			info.addr_type = I40IW_ADDR_TYPE_VA_BASED;
			info.va = (व्योम *)(uपूर्णांकptr_t)iwmr->ibmr.iova;
			info.total_len = iwmr->ibmr.length;
			info.reg_addr_pa = *(u64 *)palloc->level1.addr;
			info.first_pm_pbl_index = palloc->level1.idx;
			info.local_fence = ib_wr->send_flags & IB_SEND_FENCE;
			info.संकेतed = ib_wr->send_flags & IB_SEND_SIGNALED;

			अगर (iwmr->npages > I40IW_MIN_PAGES_PER_FMR)
				info.chunk_size = 1;

			ret = dev->iw_priv_qp_ops->iw_mr_fast_रेजिस्टर(&iwqp->sc_qp, &info, true);
			अगर (ret)
				err = -ENOMEM;
			अवरोध;
		पूर्ण
		शेष:
			err = -EINVAL;
			i40iw_pr_err(" upost_send bad opcode = 0x%x\n",
				     ib_wr->opcode);
			अवरोध;
		पूर्ण

		अगर (err)
			अवरोध;
		ib_wr = ib_wr->next;
	पूर्ण

out:
	अगर (err)
		*bad_wr = ib_wr;
	अन्यथा
		ukqp->ops.iw_qp_post_wr(ukqp);
	spin_unlock_irqrestore(&iwqp->lock, flags);

	वापस err;
पूर्ण

/**
 * i40iw_post_recv - post receive wr क्रम kernel application
 * @ibqp: ib qp poपूर्णांकer
 * @ib_wr: work request क्रम receive
 * @bad_wr: bad wr caused an error
 */
अटल पूर्णांक i40iw_post_recv(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_recv_wr *ib_wr,
			   स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा i40iw_qp *iwqp;
	काष्ठा i40iw_qp_uk *ukqp;
	काष्ठा i40iw_post_rq_info post_recv;
	काष्ठा i40iw_sge sg_list[I40IW_MAX_WQ_FRAGMENT_COUNT];
	क्रमागत i40iw_status_code ret = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	iwqp = (काष्ठा i40iw_qp *)ibqp;
	ukqp = &iwqp->sc_qp.qp_uk;

	स_रखो(&post_recv, 0, माप(post_recv));
	spin_lock_irqsave(&iwqp->lock, flags);

	अगर (iwqp->flush_issued) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	जबतक (ib_wr) अणु
		post_recv.num_sges = ib_wr->num_sge;
		post_recv.wr_id = ib_wr->wr_id;
		i40iw_copy_sg_list(sg_list, ib_wr->sg_list, ib_wr->num_sge);
		post_recv.sg_list = sg_list;
		ret = ukqp->ops.iw_post_receive(ukqp, &post_recv);
		अगर (ret) अणु
			i40iw_pr_err(" post_recv err %d\n", ret);
			अगर (ret == I40IW_ERR_QP_TOOMANY_WRS_POSTED)
				err = -ENOMEM;
			अन्यथा
				err = -EINVAL;
			*bad_wr = ib_wr;
			जाओ out;
		पूर्ण
		ib_wr = ib_wr->next;
	पूर्ण
 out:
	spin_unlock_irqrestore(&iwqp->lock, flags);
	वापस err;
पूर्ण

/**
 * i40iw_poll_cq - poll cq क्रम completion (kernel apps)
 * @ibcq: cq to poll
 * @num_entries: number of entries to poll
 * @entry: wr of entry completed
 */
अटल पूर्णांक i40iw_poll_cq(काष्ठा ib_cq *ibcq,
			 पूर्णांक num_entries,
			 काष्ठा ib_wc *entry)
अणु
	काष्ठा i40iw_cq *iwcq;
	पूर्णांक cqe_count = 0;
	काष्ठा i40iw_cq_poll_info cq_poll_info;
	क्रमागत i40iw_status_code ret;
	काष्ठा i40iw_cq_uk *ukcq;
	काष्ठा i40iw_sc_qp *qp;
	काष्ठा i40iw_qp *iwqp;
	अचिन्हित दीर्घ flags;

	iwcq = (काष्ठा i40iw_cq *)ibcq;
	ukcq = &iwcq->sc_cq.cq_uk;

	spin_lock_irqsave(&iwcq->lock, flags);
	जबतक (cqe_count < num_entries) अणु
		ret = ukcq->ops.iw_cq_poll_completion(ukcq, &cq_poll_info);
		अगर (ret == I40IW_ERR_QUEUE_EMPTY) अणु
			अवरोध;
		पूर्ण अन्यथा अगर (ret == I40IW_ERR_QUEUE_DESTROYED) अणु
			जारी;
		पूर्ण अन्यथा अगर (ret) अणु
			अगर (!cqe_count)
				cqe_count = -1;
			अवरोध;
		पूर्ण
		entry->wc_flags = 0;
		entry->wr_id = cq_poll_info.wr_id;
		अगर (cq_poll_info.error) अणु
			entry->status = IB_WC_WR_FLUSH_ERR;
			entry->venकरोr_err = cq_poll_info.major_err << 16 | cq_poll_info.minor_err;
		पूर्ण अन्यथा अणु
			entry->status = IB_WC_SUCCESS;
		पूर्ण

		चयन (cq_poll_info.op_type) अणु
		हाल I40IW_OP_TYPE_RDMA_WRITE:
			entry->opcode = IB_WC_RDMA_WRITE;
			अवरोध;
		हाल I40IW_OP_TYPE_RDMA_READ_INV_STAG:
		हाल I40IW_OP_TYPE_RDMA_READ:
			entry->opcode = IB_WC_RDMA_READ;
			अवरोध;
		हाल I40IW_OP_TYPE_SEND_SOL:
		हाल I40IW_OP_TYPE_SEND_SOL_INV:
		हाल I40IW_OP_TYPE_SEND_INV:
		हाल I40IW_OP_TYPE_SEND:
			entry->opcode = IB_WC_SEND;
			अवरोध;
		हाल I40IW_OP_TYPE_REC:
			entry->opcode = IB_WC_RECV;
			अवरोध;
		शेष:
			entry->opcode = IB_WC_RECV;
			अवरोध;
		पूर्ण

		entry->ex.imm_data = 0;
		qp = (काष्ठा i40iw_sc_qp *)cq_poll_info.qp_handle;
		entry->qp = (काष्ठा ib_qp *)qp->back_qp;
		entry->src_qp = cq_poll_info.qp_id;
		iwqp = (काष्ठा i40iw_qp *)qp->back_qp;
		अगर (iwqp->iwarp_state > I40IW_QP_STATE_RTS) अणु
			अगर (!I40IW_RING_MORE_WORK(qp->qp_uk.sq_ring))
				complete(&iwqp->sq_drained);
			अगर (!I40IW_RING_MORE_WORK(qp->qp_uk.rq_ring))
				complete(&iwqp->rq_drained);
		पूर्ण
		entry->byte_len = cq_poll_info.bytes_xfered;
		entry++;
		cqe_count++;
	पूर्ण
	spin_unlock_irqrestore(&iwcq->lock, flags);
	वापस cqe_count;
पूर्ण

/**
 * i40iw_req_notअगरy_cq - arm cq kernel application
 * @ibcq: cq to arm
 * @notअगरy_flags: notofication flags
 */
अटल पूर्णांक i40iw_req_notअगरy_cq(काष्ठा ib_cq *ibcq,
			       क्रमागत ib_cq_notअगरy_flags notअगरy_flags)
अणु
	काष्ठा i40iw_cq *iwcq;
	काष्ठा i40iw_cq_uk *ukcq;
	अचिन्हित दीर्घ flags;
	क्रमागत i40iw_completion_notअगरy cq_notअगरy = IW_CQ_COMPL_EVENT;

	iwcq = (काष्ठा i40iw_cq *)ibcq;
	ukcq = &iwcq->sc_cq.cq_uk;
	अगर (notअगरy_flags == IB_CQ_SOLICITED)
		cq_notअगरy = IW_CQ_COMPL_SOLICITED;
	spin_lock_irqsave(&iwcq->lock, flags);
	ukcq->ops.iw_cq_request_notअगरication(ukcq, cq_notअगरy);
	spin_unlock_irqrestore(&iwcq->lock, flags);
	वापस 0;
पूर्ण

/**
 * i40iw_port_immutable - वापस port's immutable data
 * @ibdev: ib dev काष्ठा
 * @port_num: port number
 * @immutable: immutable data क्रम the port वापस
 */
अटल पूर्णांक i40iw_port_immutable(काष्ठा ib_device *ibdev, u32 port_num,
				काष्ठा ib_port_immutable *immutable)
अणु
	काष्ठा ib_port_attr attr;
	पूर्णांक err;

	immutable->core_cap_flags = RDMA_CORE_PORT_IWARP;

	err = ib_query_port(ibdev, port_num, &attr);

	अगर (err)
		वापस err;

	immutable->gid_tbl_len = attr.gid_tbl_len;

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर i40iw_hw_stat_names[] = अणु
	// 32bit names
	[I40IW_HW_STAT_INDEX_IP4RXDISCARD] = "ip4InDiscards",
	[I40IW_HW_STAT_INDEX_IP4RXTRUNC] = "ip4InTruncatedPkts",
	[I40IW_HW_STAT_INDEX_IP4TXNOROUTE] = "ip4OutNoRoutes",
	[I40IW_HW_STAT_INDEX_IP6RXDISCARD] = "ip6InDiscards",
	[I40IW_HW_STAT_INDEX_IP6RXTRUNC] = "ip6InTruncatedPkts",
	[I40IW_HW_STAT_INDEX_IP6TXNOROUTE] = "ip6OutNoRoutes",
	[I40IW_HW_STAT_INDEX_TCPRTXSEG] = "tcpRetransSegs",
	[I40IW_HW_STAT_INDEX_TCPRXOPTERR] = "tcpInOptErrors",
	[I40IW_HW_STAT_INDEX_TCPRXPROTOERR] = "tcpInProtoErrors",
	// 64bit names
	[I40IW_HW_STAT_INDEX_IP4RXOCTS + I40IW_HW_STAT_INDEX_MAX_32] =
		"ip4InOctets",
	[I40IW_HW_STAT_INDEX_IP4RXPKTS + I40IW_HW_STAT_INDEX_MAX_32] =
		"ip4InPkts",
	[I40IW_HW_STAT_INDEX_IP4RXFRAGS + I40IW_HW_STAT_INDEX_MAX_32] =
		"ip4InReasmRqd",
	[I40IW_HW_STAT_INDEX_IP4RXMCPKTS + I40IW_HW_STAT_INDEX_MAX_32] =
		"ip4InMcastPkts",
	[I40IW_HW_STAT_INDEX_IP4TXOCTS + I40IW_HW_STAT_INDEX_MAX_32] =
		"ip4OutOctets",
	[I40IW_HW_STAT_INDEX_IP4TXPKTS + I40IW_HW_STAT_INDEX_MAX_32] =
		"ip4OutPkts",
	[I40IW_HW_STAT_INDEX_IP4TXFRAGS + I40IW_HW_STAT_INDEX_MAX_32] =
		"ip4OutSegRqd",
	[I40IW_HW_STAT_INDEX_IP4TXMCPKTS + I40IW_HW_STAT_INDEX_MAX_32] =
		"ip4OutMcastPkts",
	[I40IW_HW_STAT_INDEX_IP6RXOCTS + I40IW_HW_STAT_INDEX_MAX_32] =
		"ip6InOctets",
	[I40IW_HW_STAT_INDEX_IP6RXPKTS + I40IW_HW_STAT_INDEX_MAX_32] =
		"ip6InPkts",
	[I40IW_HW_STAT_INDEX_IP6RXFRAGS + I40IW_HW_STAT_INDEX_MAX_32] =
		"ip6InReasmRqd",
	[I40IW_HW_STAT_INDEX_IP6RXMCPKTS + I40IW_HW_STAT_INDEX_MAX_32] =
		"ip6InMcastPkts",
	[I40IW_HW_STAT_INDEX_IP6TXOCTS + I40IW_HW_STAT_INDEX_MAX_32] =
		"ip6OutOctets",
	[I40IW_HW_STAT_INDEX_IP6TXPKTS + I40IW_HW_STAT_INDEX_MAX_32] =
		"ip6OutPkts",
	[I40IW_HW_STAT_INDEX_IP6TXFRAGS + I40IW_HW_STAT_INDEX_MAX_32] =
		"ip6OutSegRqd",
	[I40IW_HW_STAT_INDEX_IP6TXMCPKTS + I40IW_HW_STAT_INDEX_MAX_32] =
		"ip6OutMcastPkts",
	[I40IW_HW_STAT_INDEX_TCPRXSEGS + I40IW_HW_STAT_INDEX_MAX_32] =
		"tcpInSegs",
	[I40IW_HW_STAT_INDEX_TCPTXSEG + I40IW_HW_STAT_INDEX_MAX_32] =
		"tcpOutSegs",
	[I40IW_HW_STAT_INDEX_RDMARXRDS + I40IW_HW_STAT_INDEX_MAX_32] =
		"iwInRdmaReads",
	[I40IW_HW_STAT_INDEX_RDMARXSNDS + I40IW_HW_STAT_INDEX_MAX_32] =
		"iwInRdmaSends",
	[I40IW_HW_STAT_INDEX_RDMARXWRS + I40IW_HW_STAT_INDEX_MAX_32] =
		"iwInRdmaWrites",
	[I40IW_HW_STAT_INDEX_RDMATXRDS + I40IW_HW_STAT_INDEX_MAX_32] =
		"iwOutRdmaReads",
	[I40IW_HW_STAT_INDEX_RDMATXSNDS + I40IW_HW_STAT_INDEX_MAX_32] =
		"iwOutRdmaSends",
	[I40IW_HW_STAT_INDEX_RDMATXWRS + I40IW_HW_STAT_INDEX_MAX_32] =
		"iwOutRdmaWrites",
	[I40IW_HW_STAT_INDEX_RDMAVBND + I40IW_HW_STAT_INDEX_MAX_32] =
		"iwRdmaBnd",
	[I40IW_HW_STAT_INDEX_RDMAVINV + I40IW_HW_STAT_INDEX_MAX_32] =
		"iwRdmaInv"
पूर्ण;

अटल व्योम i40iw_get_dev_fw_str(काष्ठा ib_device *dev, अक्षर *str)
अणु
	काष्ठा i40iw_device *iwdev = to_iwdev(dev);

	snम_लिखो(str, IB_FW_VERSION_NAME_MAX, "%llu.%llu",
		 i40iw_fw_major_ver(&iwdev->sc_dev),
		 i40iw_fw_minor_ver(&iwdev->sc_dev));
पूर्ण

/**
 * i40iw_alloc_hw_stats - Allocate a hw stats काष्ठाure
 * @ibdev: device poपूर्णांकer from stack
 * @port_num: port number
 */
अटल काष्ठा rdma_hw_stats *i40iw_alloc_hw_stats(काष्ठा ib_device *ibdev,
						  u32 port_num)
अणु
	काष्ठा i40iw_device *iwdev = to_iwdev(ibdev);
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	पूर्णांक num_counters = I40IW_HW_STAT_INDEX_MAX_32 +
		I40IW_HW_STAT_INDEX_MAX_64;
	अचिन्हित दीर्घ lअगरespan = RDMA_HW_STATS_DEFAULT_LIFESPAN;

	BUILD_BUG_ON(ARRAY_SIZE(i40iw_hw_stat_names) !=
		     (I40IW_HW_STAT_INDEX_MAX_32 +
		      I40IW_HW_STAT_INDEX_MAX_64));

	/*
	 * PFs get the शेष update lअगरespan, but VFs only update once
	 * per second
	 */
	अगर (!dev->is_pf)
		lअगरespan = 1000;
	वापस rdma_alloc_hw_stats_काष्ठा(i40iw_hw_stat_names, num_counters,
					  lअगरespan);
पूर्ण

/**
 * i40iw_get_hw_stats - Populates the rdma_hw_stats काष्ठाure
 * @ibdev: device poपूर्णांकer from stack
 * @stats: stats poपूर्णांकer from stack
 * @port_num: port number
 * @index: which hw counter the stack is requesting we update
 */
अटल पूर्णांक i40iw_get_hw_stats(काष्ठा ib_device *ibdev,
			      काष्ठा rdma_hw_stats *stats,
			      u32 port_num, पूर्णांक index)
अणु
	काष्ठा i40iw_device *iwdev = to_iwdev(ibdev);
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	काष्ठा i40iw_vsi_pestat *devstat = iwdev->vsi.pestat;
	काष्ठा i40iw_dev_hw_stats *hw_stats = &devstat->hw_stats;

	अगर (dev->is_pf) अणु
		i40iw_hw_stats_पढ़ो_all(devstat, &devstat->hw_stats);
	पूर्ण अन्यथा अणु
		अगर (i40iw_vchnl_vf_get_pe_stats(dev, &devstat->hw_stats))
			वापस -ENOSYS;
	पूर्ण

	स_नकल(&stats->value[0], hw_stats, माप(*hw_stats));

	वापस stats->num_counters;
पूर्ण

/**
 * i40iw_query_gid - Query port GID
 * @ibdev: device poपूर्णांकer from stack
 * @port: port number
 * @index: Entry index
 * @gid: Global ID
 */
अटल पूर्णांक i40iw_query_gid(काष्ठा ib_device *ibdev,
			   u32 port,
			   पूर्णांक index,
			   जोड़ ib_gid *gid)
अणु
	काष्ठा i40iw_device *iwdev = to_iwdev(ibdev);

	स_रखो(gid->raw, 0, माप(gid->raw));
	ether_addr_copy(gid->raw, iwdev->netdev->dev_addr);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ib_device_ops i40iw_dev_ops = अणु
	.owner = THIS_MODULE,
	.driver_id = RDMA_DRIVER_I40IW,
	/* NOTE: Older kernels wrongly use 0 क्रम the uverbs_abi_ver */
	.uverbs_abi_ver = I40IW_ABI_VER,

	.alloc_hw_stats = i40iw_alloc_hw_stats,
	.alloc_mr = i40iw_alloc_mr,
	.alloc_pd = i40iw_alloc_pd,
	.alloc_ucontext = i40iw_alloc_ucontext,
	.create_cq = i40iw_create_cq,
	.create_qp = i40iw_create_qp,
	.dealloc_pd = i40iw_dealloc_pd,
	.dealloc_ucontext = i40iw_dealloc_ucontext,
	.dereg_mr = i40iw_dereg_mr,
	.destroy_cq = i40iw_destroy_cq,
	.destroy_qp = i40iw_destroy_qp,
	.drain_rq = i40iw_drain_rq,
	.drain_sq = i40iw_drain_sq,
	.get_dev_fw_str = i40iw_get_dev_fw_str,
	.get_dma_mr = i40iw_get_dma_mr,
	.get_hw_stats = i40iw_get_hw_stats,
	.get_port_immutable = i40iw_port_immutable,
	.iw_accept = i40iw_accept,
	.iw_add_ref = i40iw_qp_add_ref,
	.iw_connect = i40iw_connect,
	.iw_create_listen = i40iw_create_listen,
	.iw_destroy_listen = i40iw_destroy_listen,
	.iw_get_qp = i40iw_get_qp,
	.iw_reject = i40iw_reject,
	.iw_rem_ref = i40iw_qp_rem_ref,
	.map_mr_sg = i40iw_map_mr_sg,
	.mmap = i40iw_mmap,
	.modअगरy_qp = i40iw_modअगरy_qp,
	.poll_cq = i40iw_poll_cq,
	.post_recv = i40iw_post_recv,
	.post_send = i40iw_post_send,
	.query_device = i40iw_query_device,
	.query_gid = i40iw_query_gid,
	.query_port = i40iw_query_port,
	.query_qp = i40iw_query_qp,
	.reg_user_mr = i40iw_reg_user_mr,
	.req_notअगरy_cq = i40iw_req_notअगरy_cq,
	INIT_RDMA_OBJ_SIZE(ib_pd, i40iw_pd, ibpd),
	INIT_RDMA_OBJ_SIZE(ib_cq, i40iw_cq, ibcq),
	INIT_RDMA_OBJ_SIZE(ib_ucontext, i40iw_ucontext, ibucontext),
पूर्ण;

/**
 * i40iw_init_rdma_device - initialization of iwarp device
 * @iwdev: iwarp device
 */
अटल काष्ठा i40iw_ib_device *i40iw_init_rdma_device(काष्ठा i40iw_device *iwdev)
अणु
	काष्ठा i40iw_ib_device *iwibdev;
	काष्ठा net_device *netdev = iwdev->netdev;
	काष्ठा pci_dev *pcidev = iwdev->hw.pcidev;

	iwibdev = ib_alloc_device(i40iw_ib_device, ibdev);
	अगर (!iwibdev) अणु
		i40iw_pr_err("iwdev == NULL\n");
		वापस शून्य;
	पूर्ण
	iwdev->iwibdev = iwibdev;
	iwibdev->iwdev = iwdev;

	iwibdev->ibdev.node_type = RDMA_NODE_RNIC;
	ether_addr_copy((u8 *)&iwibdev->ibdev.node_guid, netdev->dev_addr);

	iwibdev->ibdev.phys_port_cnt = 1;
	iwibdev->ibdev.num_comp_vectors = iwdev->ceqs_count;
	iwibdev->ibdev.dev.parent = &pcidev->dev;
	स_नकल(iwibdev->ibdev.iw_अगरname, netdev->name,
	       माप(iwibdev->ibdev.iw_अगरname));
	ib_set_device_ops(&iwibdev->ibdev, &i40iw_dev_ops);

	वापस iwibdev;
पूर्ण

/**
 * i40iw_port_ibevent - indicate port event
 * @iwdev: iwarp device
 */
व्योम i40iw_port_ibevent(काष्ठा i40iw_device *iwdev)
अणु
	काष्ठा i40iw_ib_device *iwibdev = iwdev->iwibdev;
	काष्ठा ib_event event;

	event.device = &iwibdev->ibdev;
	event.element.port_num = 1;
	event.event = iwdev->iw_status ? IB_EVENT_PORT_ACTIVE : IB_EVENT_PORT_ERR;
	ib_dispatch_event(&event);
पूर्ण

/**
 * i40iw_destroy_rdma_device - destroy rdma device and मुक्त resources
 * @iwibdev: IB device ptr
 */
व्योम i40iw_destroy_rdma_device(काष्ठा i40iw_ib_device *iwibdev)
अणु
	ib_unरेजिस्टर_device(&iwibdev->ibdev);
	रुको_event_समयout(iwibdev->iwdev->बंद_wq,
			   !atomic64_पढ़ो(&iwibdev->iwdev->use_count),
			   I40IW_EVENT_TIMEOUT);
	ib_dealloc_device(&iwibdev->ibdev);
पूर्ण

/**
 * i40iw_रेजिस्टर_rdma_device - रेजिस्टर iwarp device to IB
 * @iwdev: iwarp device
 */
पूर्णांक i40iw_रेजिस्टर_rdma_device(काष्ठा i40iw_device *iwdev)
अणु
	पूर्णांक ret;
	काष्ठा i40iw_ib_device *iwibdev;

	iwdev->iwibdev = i40iw_init_rdma_device(iwdev);
	अगर (!iwdev->iwibdev)
		वापस -ENOMEM;
	iwibdev = iwdev->iwibdev;
	rdma_set_device_sysfs_group(&iwibdev->ibdev, &i40iw_attr_group);
	ret = ib_device_set_netdev(&iwibdev->ibdev, iwdev->netdev, 1);
	अगर (ret)
		जाओ error;

	dma_set_max_seg_size(&iwdev->hw.pcidev->dev, अच_पूर्णांक_उच्च);
	ret = ib_रेजिस्टर_device(&iwibdev->ibdev, "i40iw%d", &iwdev->hw.pcidev->dev);
	अगर (ret)
		जाओ error;

	वापस 0;
error:
	ib_dealloc_device(&iwdev->iwibdev->ibdev);
	वापस ret;
पूर्ण
