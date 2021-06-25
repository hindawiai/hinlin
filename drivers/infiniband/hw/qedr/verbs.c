<शैली गुरु>
/* QLogic qedr NIC Driver
 * Copyright (c) 2015-2016  QLogic Corporation
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
 *        disclaimer in the करोcumentation and /or other materials
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
#समावेश <linux/dma-mapping.h>
#समावेश <linux/crc32.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/udp.h>
#समावेश <linux/iommu.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/iw_cm.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_cache.h>
#समावेश <rdma/uverbs_ioctl.h>

#समावेश <linux/qed/common_hsi.h>
#समावेश "qedr_hsi_rdma.h"
#समावेश <linux/qed/qed_अगर.h>
#समावेश "qedr.h"
#समावेश "verbs.h"
#समावेश <rdma/qedr-abi.h>
#समावेश "qedr_roce_cm.h"
#समावेश "qedr_iw_cm.h"

#घोषणा QEDR_SRQ_WQE_ELEM_SIZE	माप(जोड़ rdma_srq_elm)
#घोषणा	RDMA_MAX_SGE_PER_SRQ	(4)
#घोषणा RDMA_MAX_SRQ_WQE_SIZE	(RDMA_MAX_SGE_PER_SRQ + 1)

#घोषणा DB_ADDR_SHIFT(addr)		((addr) << DB_PWM_ADDR_OFFSET_SHIFT)

क्रमागत अणु
	QEDR_USER_MMAP_IO_WC = 0,
	QEDR_USER_MMAP_PHYS_PAGE,
पूर्ण;

अटल अंतरभूत पूर्णांक qedr_ib_copy_to_udata(काष्ठा ib_udata *udata, व्योम *src,
					माप_प्रकार len)
अणु
	माप_प्रकार min_len = min_t(माप_प्रकार, len, udata->outlen);

	वापस ib_copy_to_udata(udata, src, min_len);
पूर्ण

पूर्णांक qedr_query_pkey(काष्ठा ib_device *ibdev, u32 port, u16 index, u16 *pkey)
अणु
	अगर (index >= QEDR_ROCE_PKEY_TABLE_LEN)
		वापस -EINVAL;

	*pkey = QEDR_ROCE_PKEY_DEFAULT;
	वापस 0;
पूर्ण

पूर्णांक qedr_iw_query_gid(काष्ठा ib_device *ibdev, u32 port,
		      पूर्णांक index, जोड़ ib_gid *sgid)
अणु
	काष्ठा qedr_dev *dev = get_qedr_dev(ibdev);

	स_रखो(sgid->raw, 0, माप(sgid->raw));
	ether_addr_copy(sgid->raw, dev->ndev->dev_addr);

	DP_DEBUG(dev, QEDR_MSG_INIT, "QUERY sgid[%d]=%llx:%llx\n", index,
		 sgid->global.पूर्णांकerface_id, sgid->global.subnet_prefix);

	वापस 0;
पूर्ण

पूर्णांक qedr_query_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *srq_attr)
अणु
	काष्ठा qedr_dev *dev = get_qedr_dev(ibsrq->device);
	काष्ठा qedr_device_attr *qattr = &dev->attr;
	काष्ठा qedr_srq *srq = get_qedr_srq(ibsrq);

	srq_attr->srq_limit = srq->srq_limit;
	srq_attr->max_wr = qattr->max_srq_wr;
	srq_attr->max_sge = qattr->max_sge;

	वापस 0;
पूर्ण

पूर्णांक qedr_query_device(काष्ठा ib_device *ibdev,
		      काष्ठा ib_device_attr *attr, काष्ठा ib_udata *udata)
अणु
	काष्ठा qedr_dev *dev = get_qedr_dev(ibdev);
	काष्ठा qedr_device_attr *qattr = &dev->attr;

	अगर (!dev->rdma_ctx) अणु
		DP_ERR(dev,
		       "qedr_query_device called with invalid params rdma_ctx=%p\n",
		       dev->rdma_ctx);
		वापस -EINVAL;
	पूर्ण

	स_रखो(attr, 0, माप(*attr));

	attr->fw_ver = qattr->fw_ver;
	attr->sys_image_guid = qattr->sys_image_guid;
	attr->max_mr_size = qattr->max_mr_size;
	attr->page_size_cap = qattr->page_size_caps;
	attr->venकरोr_id = qattr->venकरोr_id;
	attr->venकरोr_part_id = qattr->venकरोr_part_id;
	attr->hw_ver = qattr->hw_ver;
	attr->max_qp = qattr->max_qp;
	attr->max_qp_wr = max_t(u32, qattr->max_sqe, qattr->max_rqe);
	attr->device_cap_flags = IB_DEVICE_CURR_QP_STATE_MOD |
	    IB_DEVICE_RC_RNR_NAK_GEN |
	    IB_DEVICE_LOCAL_DMA_LKEY | IB_DEVICE_MEM_MGT_EXTENSIONS;

	अगर (!rdma_protocol_iwarp(&dev->ibdev, 1))
		attr->device_cap_flags |= IB_DEVICE_XRC;
	attr->max_send_sge = qattr->max_sge;
	attr->max_recv_sge = qattr->max_sge;
	attr->max_sge_rd = qattr->max_sge;
	attr->max_cq = qattr->max_cq;
	attr->max_cqe = qattr->max_cqe;
	attr->max_mr = qattr->max_mr;
	attr->max_mw = qattr->max_mw;
	attr->max_pd = qattr->max_pd;
	attr->atomic_cap = dev->atomic_cap;
	attr->max_qp_init_rd_atom =
	    1 << (fls(qattr->max_qp_req_rd_atomic_resc) - 1);
	attr->max_qp_rd_atom =
	    min(1 << (fls(qattr->max_qp_resp_rd_atomic_resc) - 1),
		attr->max_qp_init_rd_atom);

	attr->max_srq = qattr->max_srq;
	attr->max_srq_sge = qattr->max_srq_sge;
	attr->max_srq_wr = qattr->max_srq_wr;

	attr->local_ca_ack_delay = qattr->dev_ack_delay;
	attr->max_fast_reg_page_list_len = qattr->max_mr / 8;
	attr->max_pkeys = qattr->max_pkey;
	attr->max_ah = qattr->max_ah;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम get_link_speed_and_width(पूर्णांक speed, u16 *ib_speed,
					    u8 *ib_width)
अणु
	चयन (speed) अणु
	हाल 1000:
		*ib_speed = IB_SPEED_SDR;
		*ib_width = IB_WIDTH_1X;
		अवरोध;
	हाल 10000:
		*ib_speed = IB_SPEED_QDR;
		*ib_width = IB_WIDTH_1X;
		अवरोध;

	हाल 20000:
		*ib_speed = IB_SPEED_DDR;
		*ib_width = IB_WIDTH_4X;
		अवरोध;

	हाल 25000:
		*ib_speed = IB_SPEED_EDR;
		*ib_width = IB_WIDTH_1X;
		अवरोध;

	हाल 40000:
		*ib_speed = IB_SPEED_QDR;
		*ib_width = IB_WIDTH_4X;
		अवरोध;

	हाल 50000:
		*ib_speed = IB_SPEED_HDR;
		*ib_width = IB_WIDTH_1X;
		अवरोध;

	हाल 100000:
		*ib_speed = IB_SPEED_EDR;
		*ib_width = IB_WIDTH_4X;
		अवरोध;

	शेष:
		/* Unsupported */
		*ib_speed = IB_SPEED_SDR;
		*ib_width = IB_WIDTH_1X;
	पूर्ण
पूर्ण

पूर्णांक qedr_query_port(काष्ठा ib_device *ibdev, u32 port,
		    काष्ठा ib_port_attr *attr)
अणु
	काष्ठा qedr_dev *dev;
	काष्ठा qed_rdma_port *rdma_port;

	dev = get_qedr_dev(ibdev);

	अगर (!dev->rdma_ctx) अणु
		DP_ERR(dev, "rdma_ctx is NULL\n");
		वापस -EINVAL;
	पूर्ण

	rdma_port = dev->ops->rdma_query_port(dev->rdma_ctx);

	/* *attr being zeroed by the caller, aव्योम zeroing it here */
	अगर (rdma_port->port_state == QED_RDMA_PORT_UP) अणु
		attr->state = IB_PORT_ACTIVE;
		attr->phys_state = IB_PORT_PHYS_STATE_LINK_UP;
	पूर्ण अन्यथा अणु
		attr->state = IB_PORT_DOWN;
		attr->phys_state = IB_PORT_PHYS_STATE_DISABLED;
	पूर्ण
	attr->max_mtu = IB_MTU_4096;
	attr->lid = 0;
	attr->lmc = 0;
	attr->sm_lid = 0;
	attr->sm_sl = 0;
	attr->ip_gids = true;
	अगर (rdma_protocol_iwarp(&dev->ibdev, 1)) अणु
		attr->active_mtu = iboe_get_mtu(dev->iwarp_max_mtu);
		attr->gid_tbl_len = 1;
	पूर्ण अन्यथा अणु
		attr->active_mtu = iboe_get_mtu(dev->ndev->mtu);
		attr->gid_tbl_len = QEDR_MAX_SGID;
		attr->pkey_tbl_len = QEDR_ROCE_PKEY_TABLE_LEN;
	पूर्ण
	attr->bad_pkey_cntr = rdma_port->pkey_bad_counter;
	attr->qkey_viol_cntr = 0;
	get_link_speed_and_width(rdma_port->link_speed,
				 &attr->active_speed, &attr->active_width);
	attr->max_msg_sz = rdma_port->max_msg_size;
	attr->max_vl_num = 4;

	वापस 0;
पूर्ण

पूर्णांक qedr_alloc_ucontext(काष्ठा ib_ucontext *uctx, काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = uctx->device;
	पूर्णांक rc;
	काष्ठा qedr_ucontext *ctx = get_qedr_ucontext(uctx);
	काष्ठा qedr_alloc_ucontext_resp uresp = अणुपूर्ण;
	काष्ठा qedr_alloc_ucontext_req ureq = अणुपूर्ण;
	काष्ठा qedr_dev *dev = get_qedr_dev(ibdev);
	काष्ठा qed_rdma_add_user_out_params oparams;
	काष्ठा qedr_user_mmap_entry *entry;

	अगर (!udata)
		वापस -EFAULT;

	अगर (udata->inlen) अणु
		rc = ib_copy_from_udata(&ureq, udata,
					min(माप(ureq), udata->inlen));
		अगर (rc) अणु
			DP_ERR(dev, "Problem copying data from user space\n");
			वापस -EFAULT;
		पूर्ण
		ctx->edpm_mode = !!(ureq.context_flags &
				    QEDR_ALLOC_UCTX_EDPM_MODE);
		ctx->db_rec = !!(ureq.context_flags & QEDR_ALLOC_UCTX_DB_REC);
	पूर्ण

	rc = dev->ops->rdma_add_user(dev->rdma_ctx, &oparams);
	अगर (rc) अणु
		DP_ERR(dev,
		       "failed to allocate a DPI for a new RoCE application, rc=%d. To overcome this consider to increase the number of DPIs, increase the doorbell BAR size or just close unnecessary RoCE applications. In order to increase the number of DPIs consult the qedr readme\n",
		       rc);
		वापस rc;
	पूर्ण

	ctx->dpi = oparams.dpi;
	ctx->dpi_addr = oparams.dpi_addr;
	ctx->dpi_phys_addr = oparams.dpi_phys_addr;
	ctx->dpi_size = oparams.dpi_size;
	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry) अणु
		rc = -ENOMEM;
		जाओ err;
	पूर्ण

	entry->io_address = ctx->dpi_phys_addr;
	entry->length = ctx->dpi_size;
	entry->mmap_flag = QEDR_USER_MMAP_IO_WC;
	entry->dpi = ctx->dpi;
	entry->dev = dev;
	rc = rdma_user_mmap_entry_insert(uctx, &entry->rdma_entry,
					 ctx->dpi_size);
	अगर (rc) अणु
		kमुक्त(entry);
		जाओ err;
	पूर्ण
	ctx->db_mmap_entry = &entry->rdma_entry;

	अगर (!dev->user_dpm_enabled)
		uresp.dpm_flags = 0;
	अन्यथा अगर (rdma_protocol_iwarp(&dev->ibdev, 1))
		uresp.dpm_flags = QEDR_DPM_TYPE_IWARP_LEGACY;
	अन्यथा
		uresp.dpm_flags = QEDR_DPM_TYPE_ROCE_ENHANCED |
				  QEDR_DPM_TYPE_ROCE_LEGACY |
				  QEDR_DPM_TYPE_ROCE_EDPM_MODE;

	अगर (ureq.context_flags & QEDR_SUPPORT_DPM_SIZES) अणु
		uresp.dpm_flags |= QEDR_DPM_SIZES_SET;
		uresp.ldpm_limit_size = QEDR_LDPM_MAX_SIZE;
		uresp.edpm_trans_size = QEDR_EDPM_TRANS_SIZE;
		uresp.edpm_limit_size = QEDR_EDPM_MAX_SIZE;
	पूर्ण

	uresp.wids_enabled = 1;
	uresp.wid_count = oparams.wid_count;
	uresp.db_pa = rdma_user_mmap_get_offset(ctx->db_mmap_entry);
	uresp.db_size = ctx->dpi_size;
	uresp.max_send_wr = dev->attr.max_sqe;
	uresp.max_recv_wr = dev->attr.max_rqe;
	uresp.max_srq_wr = dev->attr.max_srq_wr;
	uresp.sges_per_send_wr = QEDR_MAX_SQE_ELEMENTS_PER_SQE;
	uresp.sges_per_recv_wr = QEDR_MAX_RQE_ELEMENTS_PER_RQE;
	uresp.sges_per_srq_wr = dev->attr.max_srq_sge;
	uresp.max_cqes = QEDR_MAX_CQES;

	rc = qedr_ib_copy_to_udata(udata, &uresp, माप(uresp));
	अगर (rc)
		जाओ err;

	ctx->dev = dev;

	DP_DEBUG(dev, QEDR_MSG_INIT, "Allocating user context %p\n",
		 &ctx->ibucontext);
	वापस 0;

err:
	अगर (!ctx->db_mmap_entry)
		dev->ops->rdma_हटाओ_user(dev->rdma_ctx, ctx->dpi);
	अन्यथा
		rdma_user_mmap_entry_हटाओ(ctx->db_mmap_entry);

	वापस rc;
पूर्ण

व्योम qedr_dealloc_ucontext(काष्ठा ib_ucontext *ibctx)
अणु
	काष्ठा qedr_ucontext *uctx = get_qedr_ucontext(ibctx);

	DP_DEBUG(uctx->dev, QEDR_MSG_INIT, "Deallocating user context %p\n",
		 uctx);

	rdma_user_mmap_entry_हटाओ(uctx->db_mmap_entry);
पूर्ण

व्योम qedr_mmap_मुक्त(काष्ठा rdma_user_mmap_entry *rdma_entry)
अणु
	काष्ठा qedr_user_mmap_entry *entry = get_qedr_mmap_entry(rdma_entry);
	काष्ठा qedr_dev *dev = entry->dev;

	अगर (entry->mmap_flag == QEDR_USER_MMAP_PHYS_PAGE)
		मुक्त_page((अचिन्हित दीर्घ)entry->address);
	अन्यथा अगर (entry->mmap_flag == QEDR_USER_MMAP_IO_WC)
		dev->ops->rdma_हटाओ_user(dev->rdma_ctx, entry->dpi);

	kमुक्त(entry);
पूर्ण

पूर्णांक qedr_mmap(काष्ठा ib_ucontext *ucontext, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा ib_device *dev = ucontext->device;
	माप_प्रकार length = vma->vm_end - vma->vm_start;
	काष्ठा rdma_user_mmap_entry *rdma_entry;
	काष्ठा qedr_user_mmap_entry *entry;
	पूर्णांक rc = 0;
	u64 pfn;

	ibdev_dbg(dev,
		  "start %#lx, end %#lx, length = %#zx, pgoff = %#lx\n",
		  vma->vm_start, vma->vm_end, length, vma->vm_pgoff);

	rdma_entry = rdma_user_mmap_entry_get(ucontext, vma);
	अगर (!rdma_entry) अणु
		ibdev_dbg(dev, "pgoff[%#lx] does not have valid entry\n",
			  vma->vm_pgoff);
		वापस -EINVAL;
	पूर्ण
	entry = get_qedr_mmap_entry(rdma_entry);
	ibdev_dbg(dev,
		  "Mapping address[%#llx], length[%#zx], mmap_flag[%d]\n",
		  entry->io_address, length, entry->mmap_flag);

	चयन (entry->mmap_flag) अणु
	हाल QEDR_USER_MMAP_IO_WC:
		pfn = entry->io_address >> PAGE_SHIFT;
		rc = rdma_user_mmap_io(ucontext, vma, pfn, length,
				       pgprot_ग_लिखोcombine(vma->vm_page_prot),
				       rdma_entry);
		अवरोध;
	हाल QEDR_USER_MMAP_PHYS_PAGE:
		rc = vm_insert_page(vma, vma->vm_start,
				    virt_to_page(entry->address));
		अवरोध;
	शेष:
		rc = -EINVAL;
	पूर्ण

	अगर (rc)
		ibdev_dbg(dev,
			  "Couldn't mmap address[%#llx] length[%#zx] mmap_flag[%d] err[%d]\n",
			  entry->io_address, length, entry->mmap_flag, rc);

	rdma_user_mmap_entry_put(rdma_entry);
	वापस rc;
पूर्ण

पूर्णांक qedr_alloc_pd(काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = ibpd->device;
	काष्ठा qedr_dev *dev = get_qedr_dev(ibdev);
	काष्ठा qedr_pd *pd = get_qedr_pd(ibpd);
	u16 pd_id;
	पूर्णांक rc;

	DP_DEBUG(dev, QEDR_MSG_INIT, "Function called from: %s\n",
		 udata ? "User Lib" : "Kernel");

	अगर (!dev->rdma_ctx) अणु
		DP_ERR(dev, "invalid RDMA context\n");
		वापस -EINVAL;
	पूर्ण

	rc = dev->ops->rdma_alloc_pd(dev->rdma_ctx, &pd_id);
	अगर (rc)
		वापस rc;

	pd->pd_id = pd_id;

	अगर (udata) अणु
		काष्ठा qedr_alloc_pd_uresp uresp = अणु
			.pd_id = pd_id,
		पूर्ण;
		काष्ठा qedr_ucontext *context = rdma_udata_to_drv_context(
			udata, काष्ठा qedr_ucontext, ibucontext);

		rc = qedr_ib_copy_to_udata(udata, &uresp, माप(uresp));
		अगर (rc) अणु
			DP_ERR(dev, "copy error pd_id=0x%x.\n", pd_id);
			dev->ops->rdma_dealloc_pd(dev->rdma_ctx, pd_id);
			वापस rc;
		पूर्ण

		pd->uctx = context;
		pd->uctx->pd = pd;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qedr_dealloc_pd(काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata)
अणु
	काष्ठा qedr_dev *dev = get_qedr_dev(ibpd->device);
	काष्ठा qedr_pd *pd = get_qedr_pd(ibpd);

	DP_DEBUG(dev, QEDR_MSG_INIT, "Deallocating PD %d\n", pd->pd_id);
	dev->ops->rdma_dealloc_pd(dev->rdma_ctx, pd->pd_id);
	वापस 0;
पूर्ण


पूर्णांक qedr_alloc_xrcd(काष्ठा ib_xrcd *ibxrcd, काष्ठा ib_udata *udata)
अणु
	काष्ठा qedr_dev *dev = get_qedr_dev(ibxrcd->device);
	काष्ठा qedr_xrcd *xrcd = get_qedr_xrcd(ibxrcd);

	वापस dev->ops->rdma_alloc_xrcd(dev->rdma_ctx, &xrcd->xrcd_id);
पूर्ण

पूर्णांक qedr_dealloc_xrcd(काष्ठा ib_xrcd *ibxrcd, काष्ठा ib_udata *udata)
अणु
	काष्ठा qedr_dev *dev = get_qedr_dev(ibxrcd->device);
	u16 xrcd_id = get_qedr_xrcd(ibxrcd)->xrcd_id;

	dev->ops->rdma_dealloc_xrcd(dev->rdma_ctx, xrcd_id);
	वापस 0;
पूर्ण
अटल व्योम qedr_मुक्त_pbl(काष्ठा qedr_dev *dev,
			  काष्ठा qedr_pbl_info *pbl_info, काष्ठा qedr_pbl *pbl)
अणु
	काष्ठा pci_dev *pdev = dev->pdev;
	पूर्णांक i;

	क्रम (i = 0; i < pbl_info->num_pbls; i++) अणु
		अगर (!pbl[i].va)
			जारी;
		dma_मुक्त_coherent(&pdev->dev, pbl_info->pbl_size,
				  pbl[i].va, pbl[i].pa);
	पूर्ण

	kमुक्त(pbl);
पूर्ण

#घोषणा MIN_FW_PBL_PAGE_SIZE (4 * 1024)
#घोषणा MAX_FW_PBL_PAGE_SIZE (64 * 1024)

#घोषणा NUM_PBES_ON_PAGE(_page_size) (_page_size / माप(u64))
#घोषणा MAX_PBES_ON_PAGE NUM_PBES_ON_PAGE(MAX_FW_PBL_PAGE_SIZE)
#घोषणा MAX_PBES_TWO_LAYER (MAX_PBES_ON_PAGE * MAX_PBES_ON_PAGE)

अटल काष्ठा qedr_pbl *qedr_alloc_pbl_tbl(काष्ठा qedr_dev *dev,
					   काष्ठा qedr_pbl_info *pbl_info,
					   gfp_t flags)
अणु
	काष्ठा pci_dev *pdev = dev->pdev;
	काष्ठा qedr_pbl *pbl_table;
	dma_addr_t *pbl_मुख्य_tbl;
	dma_addr_t pa;
	व्योम *va;
	पूर्णांक i;

	pbl_table = kसुस्मृति(pbl_info->num_pbls, माप(*pbl_table), flags);
	अगर (!pbl_table)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < pbl_info->num_pbls; i++) अणु
		va = dma_alloc_coherent(&pdev->dev, pbl_info->pbl_size, &pa,
					flags);
		अगर (!va)
			जाओ err;

		pbl_table[i].va = va;
		pbl_table[i].pa = pa;
	पूर्ण

	/* Two-Layer PBLs, अगर we have more than one pbl we need to initialize
	 * the first one with physical poपूर्णांकers to all of the rest
	 */
	pbl_मुख्य_tbl = (dma_addr_t *)pbl_table[0].va;
	क्रम (i = 0; i < pbl_info->num_pbls - 1; i++)
		pbl_मुख्य_tbl[i] = pbl_table[i + 1].pa;

	वापस pbl_table;

err:
	क्रम (i--; i >= 0; i--)
		dma_मुक्त_coherent(&pdev->dev, pbl_info->pbl_size,
				  pbl_table[i].va, pbl_table[i].pa);

	qedr_मुक्त_pbl(dev, pbl_info, pbl_table);

	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल पूर्णांक qedr_prepare_pbl_tbl(काष्ठा qedr_dev *dev,
				काष्ठा qedr_pbl_info *pbl_info,
				u32 num_pbes, पूर्णांक two_layer_capable)
अणु
	u32 pbl_capacity;
	u32 pbl_size;
	u32 num_pbls;

	अगर ((num_pbes > MAX_PBES_ON_PAGE) && two_layer_capable) अणु
		अगर (num_pbes > MAX_PBES_TWO_LAYER) अणु
			DP_ERR(dev, "prepare pbl table: too many pages %d\n",
			       num_pbes);
			वापस -EINVAL;
		पूर्ण

		/* calculate required pbl page size */
		pbl_size = MIN_FW_PBL_PAGE_SIZE;
		pbl_capacity = NUM_PBES_ON_PAGE(pbl_size) *
			       NUM_PBES_ON_PAGE(pbl_size);

		जबतक (pbl_capacity < num_pbes) अणु
			pbl_size *= 2;
			pbl_capacity = pbl_size / माप(u64);
			pbl_capacity = pbl_capacity * pbl_capacity;
		पूर्ण

		num_pbls = DIV_ROUND_UP(num_pbes, NUM_PBES_ON_PAGE(pbl_size));
		num_pbls++;	/* One क्रम the layer0 ( poपूर्णांकs to the pbls) */
		pbl_info->two_layered = true;
	पूर्ण अन्यथा अणु
		/* One layered PBL */
		num_pbls = 1;
		pbl_size = max_t(u32, MIN_FW_PBL_PAGE_SIZE,
				 roundup_घात_of_two((num_pbes * माप(u64))));
		pbl_info->two_layered = false;
	पूर्ण

	pbl_info->num_pbls = num_pbls;
	pbl_info->pbl_size = pbl_size;
	pbl_info->num_pbes = num_pbes;

	DP_DEBUG(dev, QEDR_MSG_MR,
		 "prepare pbl table: num_pbes=%d, num_pbls=%d, pbl_size=%d\n",
		 pbl_info->num_pbes, pbl_info->num_pbls, pbl_info->pbl_size);

	वापस 0;
पूर्ण

अटल व्योम qedr_populate_pbls(काष्ठा qedr_dev *dev, काष्ठा ib_umem *umem,
			       काष्ठा qedr_pbl *pbl,
			       काष्ठा qedr_pbl_info *pbl_info, u32 pg_shअगरt)
अणु
	पूर्णांक pbe_cnt, total_num_pbes = 0;
	काष्ठा qedr_pbl *pbl_tbl;
	काष्ठा ib_block_iter biter;
	काष्ठा regpair *pbe;

	अगर (!pbl_info->num_pbes)
		वापस;

	/* If we have a two layered pbl, the first pbl poपूर्णांकs to the rest
	 * of the pbls and the first entry lays on the second pbl in the table
	 */
	अगर (pbl_info->two_layered)
		pbl_tbl = &pbl[1];
	अन्यथा
		pbl_tbl = pbl;

	pbe = (काष्ठा regpair *)pbl_tbl->va;
	अगर (!pbe) अणु
		DP_ERR(dev, "cannot populate PBL due to a NULL PBE\n");
		वापस;
	पूर्ण

	pbe_cnt = 0;

	rdma_umem_क्रम_each_dma_block (umem, &biter, BIT(pg_shअगरt)) अणु
		u64 pg_addr = rdma_block_iter_dma_address(&biter);

		pbe->lo = cpu_to_le32(pg_addr);
		pbe->hi = cpu_to_le32(upper_32_bits(pg_addr));

		pbe_cnt++;
		total_num_pbes++;
		pbe++;

		अगर (total_num_pbes == pbl_info->num_pbes)
			वापस;

		/* If the given pbl is full storing the pbes, move to next pbl.
		 */
		अगर (pbe_cnt == (pbl_info->pbl_size / माप(u64))) अणु
			pbl_tbl++;
			pbe = (काष्ठा regpair *)pbl_tbl->va;
			pbe_cnt = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक qedr_db_recovery_add(काष्ठा qedr_dev *dev,
				व्योम __iomem *db_addr,
				व्योम *db_data,
				क्रमागत qed_db_rec_width db_width,
				क्रमागत qed_db_rec_space db_space)
अणु
	अगर (!db_data) अणु
		DP_DEBUG(dev, QEDR_MSG_INIT, "avoiding db rec since old lib\n");
		वापस 0;
	पूर्ण

	वापस dev->ops->common->db_recovery_add(dev->cdev, db_addr, db_data,
						 db_width, db_space);
पूर्ण

अटल व्योम qedr_db_recovery_del(काष्ठा qedr_dev *dev,
				 व्योम __iomem *db_addr,
				 व्योम *db_data)
अणु
	अगर (!db_data) अणु
		DP_DEBUG(dev, QEDR_MSG_INIT, "avoiding db rec since old lib\n");
		वापस;
	पूर्ण

	/* Ignore वापस code as there is not much we can करो about it. Error
	 * log will be prपूर्णांकed inside.
	 */
	dev->ops->common->db_recovery_del(dev->cdev, db_addr, db_data);
पूर्ण

अटल पूर्णांक qedr_copy_cq_uresp(काष्ठा qedr_dev *dev,
			      काष्ठा qedr_cq *cq, काष्ठा ib_udata *udata,
			      u32 db_offset)
अणु
	काष्ठा qedr_create_cq_uresp uresp;
	पूर्णांक rc;

	स_रखो(&uresp, 0, माप(uresp));

	uresp.db_offset = db_offset;
	uresp.icid = cq->icid;
	अगर (cq->q.db_mmap_entry)
		uresp.db_rec_addr =
			rdma_user_mmap_get_offset(cq->q.db_mmap_entry);

	rc = qedr_ib_copy_to_udata(udata, &uresp, माप(uresp));
	अगर (rc)
		DP_ERR(dev, "copy error cqid=0x%x.\n", cq->icid);

	वापस rc;
पूर्ण

अटल व्योम consume_cqe(काष्ठा qedr_cq *cq)
अणु
	अगर (cq->latest_cqe == cq->toggle_cqe)
		cq->pbl_toggle ^= RDMA_CQE_REQUESTER_TOGGLE_BIT_MASK;

	cq->latest_cqe = qed_chain_consume(&cq->pbl);
पूर्ण

अटल अंतरभूत पूर्णांक qedr_align_cq_entries(पूर्णांक entries)
अणु
	u64 size, aligned_size;

	/* We allocate an extra entry that we करोn't report to the FW. */
	size = (entries + 1) * QEDR_CQE_SIZE;
	aligned_size = ALIGN(size, PAGE_SIZE);

	वापस aligned_size / QEDR_CQE_SIZE;
पूर्ण

अटल पूर्णांक qedr_init_user_db_rec(काष्ठा ib_udata *udata,
				 काष्ठा qedr_dev *dev, काष्ठा qedr_userq *q,
				 bool requires_db_rec)
अणु
	काष्ठा qedr_ucontext *uctx =
		rdma_udata_to_drv_context(udata, काष्ठा qedr_ucontext,
					  ibucontext);
	काष्ठा qedr_user_mmap_entry *entry;
	पूर्णांक rc;

	/* Aborting क्रम non करोorbell userqueue (SRQ) or non-supporting lib */
	अगर (requires_db_rec == 0 || !uctx->db_rec)
		वापस 0;

	/* Allocate a page क्रम करोorbell recovery, add to mmap */
	q->db_rec_data = (व्योम *)get_zeroed_page(GFP_USER);
	अगर (!q->db_rec_data) अणु
		DP_ERR(dev, "get_zeroed_page failed\n");
		वापस -ENOMEM;
	पूर्ण

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		जाओ err_मुक्त_db_data;

	entry->address = q->db_rec_data;
	entry->length = PAGE_SIZE;
	entry->mmap_flag = QEDR_USER_MMAP_PHYS_PAGE;
	rc = rdma_user_mmap_entry_insert(&uctx->ibucontext,
					 &entry->rdma_entry,
					 PAGE_SIZE);
	अगर (rc)
		जाओ err_मुक्त_entry;

	q->db_mmap_entry = &entry->rdma_entry;

	वापस 0;

err_मुक्त_entry:
	kमुक्त(entry);

err_मुक्त_db_data:
	मुक्त_page((अचिन्हित दीर्घ)q->db_rec_data);
	q->db_rec_data = शून्य;
	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत पूर्णांक qedr_init_user_queue(काष्ठा ib_udata *udata,
				       काष्ठा qedr_dev *dev,
				       काष्ठा qedr_userq *q, u64 buf_addr,
				       माप_प्रकार buf_len, bool requires_db_rec,
				       पूर्णांक access,
				       पूर्णांक alloc_and_init)
अणु
	u32 fw_pages;
	पूर्णांक rc;

	q->buf_addr = buf_addr;
	q->buf_len = buf_len;
	q->umem = ib_umem_get(&dev->ibdev, q->buf_addr, q->buf_len, access);
	अगर (IS_ERR(q->umem)) अणु
		DP_ERR(dev, "create user queue: failed ib_umem_get, got %ld\n",
		       PTR_ERR(q->umem));
		वापस PTR_ERR(q->umem);
	पूर्ण

	fw_pages = ib_umem_num_dma_blocks(q->umem, 1 << FW_PAGE_SHIFT);
	rc = qedr_prepare_pbl_tbl(dev, &q->pbl_info, fw_pages, 0);
	अगर (rc)
		जाओ err0;

	अगर (alloc_and_init) अणु
		q->pbl_tbl = qedr_alloc_pbl_tbl(dev, &q->pbl_info, GFP_KERNEL);
		अगर (IS_ERR(q->pbl_tbl)) अणु
			rc = PTR_ERR(q->pbl_tbl);
			जाओ err0;
		पूर्ण
		qedr_populate_pbls(dev, q->umem, q->pbl_tbl, &q->pbl_info,
				   FW_PAGE_SHIFT);
	पूर्ण अन्यथा अणु
		q->pbl_tbl = kzalloc(माप(*q->pbl_tbl), GFP_KERNEL);
		अगर (!q->pbl_tbl) अणु
			rc = -ENOMEM;
			जाओ err0;
		पूर्ण
	पूर्ण

	/* mmap the user address used to store करोorbell data क्रम recovery */
	वापस qedr_init_user_db_rec(udata, dev, q, requires_db_rec);

err0:
	ib_umem_release(q->umem);
	q->umem = शून्य;

	वापस rc;
पूर्ण

अटल अंतरभूत व्योम qedr_init_cq_params(काष्ठा qedr_cq *cq,
				       काष्ठा qedr_ucontext *ctx,
				       काष्ठा qedr_dev *dev, पूर्णांक vector,
				       पूर्णांक chain_entries, पूर्णांक page_cnt,
				       u64 pbl_ptr,
				       काष्ठा qed_rdma_create_cq_in_params
				       *params)
अणु
	स_रखो(params, 0, माप(*params));
	params->cq_handle_hi = upper_32_bits((uपूर्णांकptr_t)cq);
	params->cq_handle_lo = lower_32_bits((uपूर्णांकptr_t)cq);
	params->cnq_id = vector;
	params->cq_size = chain_entries - 1;
	params->dpi = (ctx) ? ctx->dpi : dev->dpi;
	params->pbl_num_pages = page_cnt;
	params->pbl_ptr = pbl_ptr;
	params->pbl_two_level = 0;
पूर्ण

अटल व्योम करोorbell_cq(काष्ठा qedr_cq *cq, u32 cons, u8 flags)
अणु
	cq->db.data.agg_flags = flags;
	cq->db.data.value = cpu_to_le32(cons);
	ग_लिखोq(cq->db.raw, cq->db_addr);
पूर्ण

पूर्णांक qedr_arm_cq(काष्ठा ib_cq *ibcq, क्रमागत ib_cq_notअगरy_flags flags)
अणु
	काष्ठा qedr_cq *cq = get_qedr_cq(ibcq);
	अचिन्हित दीर्घ sflags;
	काष्ठा qedr_dev *dev;

	dev = get_qedr_dev(ibcq->device);

	अगर (cq->destroyed) अणु
		DP_ERR(dev,
		       "warning: arm was invoked after destroy for cq %p (icid=%d)\n",
		       cq, cq->icid);
		वापस -EINVAL;
	पूर्ण


	अगर (cq->cq_type == QEDR_CQ_TYPE_GSI)
		वापस 0;

	spin_lock_irqsave(&cq->cq_lock, sflags);

	cq->arm_flags = 0;

	अगर (flags & IB_CQ_SOLICITED)
		cq->arm_flags |= DQ_UCM_ROCE_CQ_ARM_SE_CF_CMD;

	अगर (flags & IB_CQ_NEXT_COMP)
		cq->arm_flags |= DQ_UCM_ROCE_CQ_ARM_CF_CMD;

	करोorbell_cq(cq, cq->cq_cons - 1, cq->arm_flags);

	spin_unlock_irqrestore(&cq->cq_lock, sflags);

	वापस 0;
पूर्ण

पूर्णांक qedr_create_cq(काष्ठा ib_cq *ibcq, स्थिर काष्ठा ib_cq_init_attr *attr,
		   काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = ibcq->device;
	काष्ठा qedr_ucontext *ctx = rdma_udata_to_drv_context(
		udata, काष्ठा qedr_ucontext, ibucontext);
	काष्ठा qed_rdma_destroy_cq_out_params destroy_oparams;
	काष्ठा qed_rdma_destroy_cq_in_params destroy_iparams;
	काष्ठा qed_chain_init_params chain_params = अणु
		.mode		= QED_CHAIN_MODE_PBL,
		.पूर्णांकended_use	= QED_CHAIN_USE_TO_CONSUME,
		.cnt_type	= QED_CHAIN_CNT_TYPE_U32,
		.elem_size	= माप(जोड़ rdma_cqe),
	पूर्ण;
	काष्ठा qedr_dev *dev = get_qedr_dev(ibdev);
	काष्ठा qed_rdma_create_cq_in_params params;
	काष्ठा qedr_create_cq_ureq ureq = अणुपूर्ण;
	पूर्णांक vector = attr->comp_vector;
	पूर्णांक entries = attr->cqe;
	काष्ठा qedr_cq *cq = get_qedr_cq(ibcq);
	पूर्णांक chain_entries;
	u32 db_offset;
	पूर्णांक page_cnt;
	u64 pbl_ptr;
	u16 icid;
	पूर्णांक rc;

	DP_DEBUG(dev, QEDR_MSG_INIT,
		 "create_cq: called from %s. entries=%d, vector=%d\n",
		 udata ? "User Lib" : "Kernel", entries, vector);

	अगर (attr->flags)
		वापस -EOPNOTSUPP;

	अगर (entries > QEDR_MAX_CQES) अणु
		DP_ERR(dev,
		       "create cq: the number of entries %d is too high. Must be equal or below %d.\n",
		       entries, QEDR_MAX_CQES);
		वापस -EINVAL;
	पूर्ण

	chain_entries = qedr_align_cq_entries(entries);
	chain_entries = min_t(पूर्णांक, chain_entries, QEDR_MAX_CQES);
	chain_params.num_elems = chain_entries;

	/* calc db offset. user will add DPI base, kernel will add db addr */
	db_offset = DB_ADDR_SHIFT(DQ_PWM_OFFSET_UCM_RDMA_CQ_CONS_32BIT);

	अगर (udata) अणु
		अगर (ib_copy_from_udata(&ureq, udata, min(माप(ureq),
							 udata->inlen))) अणु
			DP_ERR(dev,
			       "create cq: problem copying data from user space\n");
			जाओ err0;
		पूर्ण

		अगर (!ureq.len) अणु
			DP_ERR(dev,
			       "create cq: cannot create a cq with 0 entries\n");
			जाओ err0;
		पूर्ण

		cq->cq_type = QEDR_CQ_TYPE_USER;

		rc = qedr_init_user_queue(udata, dev, &cq->q, ureq.addr,
					  ureq.len, true, IB_ACCESS_LOCAL_WRITE,
					  1);
		अगर (rc)
			जाओ err0;

		pbl_ptr = cq->q.pbl_tbl->pa;
		page_cnt = cq->q.pbl_info.num_pbes;

		cq->ibcq.cqe = chain_entries;
		cq->q.db_addr = ctx->dpi_addr + db_offset;
	पूर्ण अन्यथा अणु
		cq->cq_type = QEDR_CQ_TYPE_KERNEL;

		rc = dev->ops->common->chain_alloc(dev->cdev, &cq->pbl,
						   &chain_params);
		अगर (rc)
			जाओ err0;

		page_cnt = qed_chain_get_page_cnt(&cq->pbl);
		pbl_ptr = qed_chain_get_pbl_phys(&cq->pbl);
		cq->ibcq.cqe = cq->pbl.capacity;
	पूर्ण

	qedr_init_cq_params(cq, ctx, dev, vector, chain_entries, page_cnt,
			    pbl_ptr, &params);

	rc = dev->ops->rdma_create_cq(dev->rdma_ctx, &params, &icid);
	अगर (rc)
		जाओ err1;

	cq->icid = icid;
	cq->sig = QEDR_CQ_MAGIC_NUMBER;
	spin_lock_init(&cq->cq_lock);

	अगर (udata) अणु
		rc = qedr_copy_cq_uresp(dev, cq, udata, db_offset);
		अगर (rc)
			जाओ err2;

		rc = qedr_db_recovery_add(dev, cq->q.db_addr,
					  &cq->q.db_rec_data->db_data,
					  DB_REC_WIDTH_64B,
					  DB_REC_USER);
		अगर (rc)
			जाओ err2;

	पूर्ण अन्यथा अणु
		/* Generate करोorbell address. */
		cq->db.data.icid = cq->icid;
		cq->db_addr = dev->db_addr + db_offset;
		cq->db.data.params = DB_AGG_CMD_MAX <<
		    RDMA_PWM_VAL32_DATA_AGG_CMD_SHIFT;

		/* poपूर्णांक to the very last element, passing it we will toggle */
		cq->toggle_cqe = qed_chain_get_last_elem(&cq->pbl);
		cq->pbl_toggle = RDMA_CQE_REQUESTER_TOGGLE_BIT_MASK;
		cq->latest_cqe = शून्य;
		consume_cqe(cq);
		cq->cq_cons = qed_chain_get_cons_idx_u32(&cq->pbl);

		rc = qedr_db_recovery_add(dev, cq->db_addr, &cq->db.data,
					  DB_REC_WIDTH_64B, DB_REC_KERNEL);
		अगर (rc)
			जाओ err2;
	पूर्ण

	DP_DEBUG(dev, QEDR_MSG_CQ,
		 "create cq: icid=0x%0x, addr=%p, size(entries)=0x%0x\n",
		 cq->icid, cq, params.cq_size);

	वापस 0;

err2:
	destroy_iparams.icid = cq->icid;
	dev->ops->rdma_destroy_cq(dev->rdma_ctx, &destroy_iparams,
				  &destroy_oparams);
err1:
	अगर (udata) अणु
		qedr_मुक्त_pbl(dev, &cq->q.pbl_info, cq->q.pbl_tbl);
		ib_umem_release(cq->q.umem);
		अगर (cq->q.db_mmap_entry)
			rdma_user_mmap_entry_हटाओ(cq->q.db_mmap_entry);
	पूर्ण अन्यथा अणु
		dev->ops->common->chain_मुक्त(dev->cdev, &cq->pbl);
	पूर्ण
err0:
	वापस -EINVAL;
पूर्ण

पूर्णांक qedr_resize_cq(काष्ठा ib_cq *ibcq, पूर्णांक new_cnt, काष्ठा ib_udata *udata)
अणु
	काष्ठा qedr_dev *dev = get_qedr_dev(ibcq->device);
	काष्ठा qedr_cq *cq = get_qedr_cq(ibcq);

	DP_ERR(dev, "cq %p RESIZE NOT SUPPORTED\n", cq);

	वापस 0;
पूर्ण

#घोषणा QEDR_DESTROY_CQ_MAX_ITERATIONS		(10)
#घोषणा QEDR_DESTROY_CQ_ITER_DURATION		(10)

पूर्णांक qedr_destroy_cq(काष्ठा ib_cq *ibcq, काष्ठा ib_udata *udata)
अणु
	काष्ठा qedr_dev *dev = get_qedr_dev(ibcq->device);
	काष्ठा qed_rdma_destroy_cq_out_params oparams;
	काष्ठा qed_rdma_destroy_cq_in_params iparams;
	काष्ठा qedr_cq *cq = get_qedr_cq(ibcq);
	पूर्णांक iter;

	DP_DEBUG(dev, QEDR_MSG_CQ, "destroy cq %p (icid=%d)\n", cq, cq->icid);

	cq->destroyed = 1;

	/* GSIs CQs are handled by driver, so they करोn't exist in the FW */
	अगर (cq->cq_type == QEDR_CQ_TYPE_GSI) अणु
		qedr_db_recovery_del(dev, cq->db_addr, &cq->db.data);
		वापस 0;
	पूर्ण

	iparams.icid = cq->icid;
	dev->ops->rdma_destroy_cq(dev->rdma_ctx, &iparams, &oparams);
	dev->ops->common->chain_मुक्त(dev->cdev, &cq->pbl);

	अगर (udata) अणु
		qedr_मुक्त_pbl(dev, &cq->q.pbl_info, cq->q.pbl_tbl);
		ib_umem_release(cq->q.umem);

		अगर (cq->q.db_rec_data) अणु
			qedr_db_recovery_del(dev, cq->q.db_addr,
					     &cq->q.db_rec_data->db_data);
			rdma_user_mmap_entry_हटाओ(cq->q.db_mmap_entry);
		पूर्ण
	पूर्ण अन्यथा अणु
		qedr_db_recovery_del(dev, cq->db_addr, &cq->db.data);
	पूर्ण

	/* We करोn't want the IRQ handler to handle a non-existing CQ so we
	 * रुको until all CNQ पूर्णांकerrupts, अगर any, are received. This will always
	 * happen and will always happen very fast. If not, then a serious error
	 * has occured. That is why we can use a दीर्घ delay.
	 * We spin क्रम a लघु समय so we करोnै t lose समय on context चयनing
	 * in हाल all the completions are handled in that span. Otherwise
	 * we sleep क्रम a जबतक and check again. Since the CNQ may be
	 * associated with (only) the current CPU we use msleep to allow the
	 * current CPU to be मुक्तd.
	 * The CNQ notअगरication is increased in qedr_irq_handler().
	 */
	iter = QEDR_DESTROY_CQ_MAX_ITERATIONS;
	जबतक (oparams.num_cq_notअगर != READ_ONCE(cq->cnq_notअगर) && iter) अणु
		udelay(QEDR_DESTROY_CQ_ITER_DURATION);
		iter--;
	पूर्ण

	iter = QEDR_DESTROY_CQ_MAX_ITERATIONS;
	जबतक (oparams.num_cq_notअगर != READ_ONCE(cq->cnq_notअगर) && iter) अणु
		msleep(QEDR_DESTROY_CQ_ITER_DURATION);
		iter--;
	पूर्ण

	/* Note that we करोn't need to have explicit code to रुको क्रम the
	 * completion of the event handler because it is invoked from the EQ.
	 * Since the destroy CQ ramrod has also been received on the EQ we can
	 * be certain that there's no event handler in process.
	 */
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक get_gid_info_from_table(काष्ठा ib_qp *ibqp,
					  काष्ठा ib_qp_attr *attr,
					  पूर्णांक attr_mask,
					  काष्ठा qed_rdma_modअगरy_qp_in_params
					  *qp_params)
अणु
	स्थिर काष्ठा ib_gid_attr *gid_attr;
	क्रमागत rdma_network_type nw_type;
	स्थिर काष्ठा ib_global_route *grh = rdma_ah_पढ़ो_grh(&attr->ah_attr);
	u32 ipv4_addr;
	पूर्णांक ret;
	पूर्णांक i;

	gid_attr = grh->sgid_attr;
	ret = rdma_पढ़ो_gid_l2_fields(gid_attr, &qp_params->vlan_id, शून्य);
	अगर (ret)
		वापस ret;

	nw_type = rdma_gid_attr_network_type(gid_attr);
	चयन (nw_type) अणु
	हाल RDMA_NETWORK_IPV6:
		स_नकल(&qp_params->sgid.bytes[0], &gid_attr->gid.raw[0],
		       माप(qp_params->sgid));
		स_नकल(&qp_params->dgid.bytes[0],
		       &grh->dgid,
		       माप(qp_params->dgid));
		qp_params->roce_mode = ROCE_V2_IPV6;
		SET_FIELD(qp_params->modअगरy_flags,
			  QED_ROCE_MODIFY_QP_VALID_ROCE_MODE, 1);
		अवरोध;
	हाल RDMA_NETWORK_ROCE_V1:
		स_नकल(&qp_params->sgid.bytes[0], &gid_attr->gid.raw[0],
		       माप(qp_params->sgid));
		स_नकल(&qp_params->dgid.bytes[0],
		       &grh->dgid,
		       माप(qp_params->dgid));
		qp_params->roce_mode = ROCE_V1;
		अवरोध;
	हाल RDMA_NETWORK_IPV4:
		स_रखो(&qp_params->sgid, 0, माप(qp_params->sgid));
		स_रखो(&qp_params->dgid, 0, माप(qp_params->dgid));
		ipv4_addr = qedr_get_ipv4_from_gid(gid_attr->gid.raw);
		qp_params->sgid.ipv4_addr = ipv4_addr;
		ipv4_addr =
		    qedr_get_ipv4_from_gid(grh->dgid.raw);
		qp_params->dgid.ipv4_addr = ipv4_addr;
		SET_FIELD(qp_params->modअगरy_flags,
			  QED_ROCE_MODIFY_QP_VALID_ROCE_MODE, 1);
		qp_params->roce_mode = ROCE_V2_IPV4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		qp_params->sgid.dwords[i] = ntohl(qp_params->sgid.dwords[i]);
		qp_params->dgid.dwords[i] = ntohl(qp_params->dgid.dwords[i]);
	पूर्ण

	अगर (qp_params->vlan_id >= VLAN_CFI_MASK)
		qp_params->vlan_id = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक qedr_check_qp_attrs(काष्ठा ib_pd *ibpd, काष्ठा qedr_dev *dev,
			       काष्ठा ib_qp_init_attr *attrs,
			       काष्ठा ib_udata *udata)
अणु
	काष्ठा qedr_device_attr *qattr = &dev->attr;

	/* QP0... attrs->qp_type == IB_QPT_GSI */
	अगर (attrs->qp_type != IB_QPT_RC &&
	    attrs->qp_type != IB_QPT_GSI &&
	    attrs->qp_type != IB_QPT_XRC_INI &&
	    attrs->qp_type != IB_QPT_XRC_TGT) अणु
		DP_DEBUG(dev, QEDR_MSG_QP,
			 "create qp: unsupported qp type=0x%x requested\n",
			 attrs->qp_type);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (attrs->cap.max_send_wr > qattr->max_sqe) अणु
		DP_ERR(dev,
		       "create qp: cannot create a SQ with %d elements (max_send_wr=0x%x)\n",
		       attrs->cap.max_send_wr, qattr->max_sqe);
		वापस -EINVAL;
	पूर्ण

	अगर (attrs->cap.max_अंतरभूत_data > qattr->max_अंतरभूत) अणु
		DP_ERR(dev,
		       "create qp: unsupported inline data size=0x%x requested (max_inline=0x%x)\n",
		       attrs->cap.max_अंतरभूत_data, qattr->max_अंतरभूत);
		वापस -EINVAL;
	पूर्ण

	अगर (attrs->cap.max_send_sge > qattr->max_sge) अणु
		DP_ERR(dev,
		       "create qp: unsupported send_sge=0x%x requested (max_send_sge=0x%x)\n",
		       attrs->cap.max_send_sge, qattr->max_sge);
		वापस -EINVAL;
	पूर्ण

	अगर (attrs->cap.max_recv_sge > qattr->max_sge) अणु
		DP_ERR(dev,
		       "create qp: unsupported recv_sge=0x%x requested (max_recv_sge=0x%x)\n",
		       attrs->cap.max_recv_sge, qattr->max_sge);
		वापस -EINVAL;
	पूर्ण

	/* verअगरy consumer QPs are not trying to use GSI QP's CQ.
	 * TGT QP isn't associated with RQ/SQ
	 */
	अगर ((attrs->qp_type != IB_QPT_GSI) && (dev->gsi_qp_created) &&
	    (attrs->qp_type != IB_QPT_XRC_TGT) &&
	    (attrs->qp_type != IB_QPT_XRC_INI)) अणु
		काष्ठा qedr_cq *send_cq = get_qedr_cq(attrs->send_cq);
		काष्ठा qedr_cq *recv_cq = get_qedr_cq(attrs->recv_cq);

		अगर ((send_cq->cq_type == QEDR_CQ_TYPE_GSI) ||
		    (recv_cq->cq_type == QEDR_CQ_TYPE_GSI)) अणु
			DP_ERR(dev,
			       "create qp: consumer QP cannot use GSI CQs.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qedr_copy_srq_uresp(काष्ठा qedr_dev *dev,
			       काष्ठा qedr_srq *srq, काष्ठा ib_udata *udata)
अणु
	काष्ठा qedr_create_srq_uresp uresp = अणुपूर्ण;
	पूर्णांक rc;

	uresp.srq_id = srq->srq_id;

	rc = ib_copy_to_udata(udata, &uresp, माप(uresp));
	अगर (rc)
		DP_ERR(dev, "create srq: problem copying data to user space\n");

	वापस rc;
पूर्ण

अटल व्योम qedr_copy_rq_uresp(काष्ठा qedr_dev *dev,
			       काष्ठा qedr_create_qp_uresp *uresp,
			       काष्ठा qedr_qp *qp)
अणु
	/* iWARP requires two करोorbells per RQ. */
	अगर (rdma_protocol_iwarp(&dev->ibdev, 1)) अणु
		uresp->rq_db_offset =
		    DB_ADDR_SHIFT(DQ_PWM_OFFSET_TCM_IWARP_RQ_PROD);
		uresp->rq_db2_offset = DB_ADDR_SHIFT(DQ_PWM_OFFSET_TCM_FLAGS);
	पूर्ण अन्यथा अणु
		uresp->rq_db_offset =
		    DB_ADDR_SHIFT(DQ_PWM_OFFSET_TCM_ROCE_RQ_PROD);
	पूर्ण

	uresp->rq_icid = qp->icid;
	अगर (qp->urq.db_mmap_entry)
		uresp->rq_db_rec_addr =
			rdma_user_mmap_get_offset(qp->urq.db_mmap_entry);
पूर्ण

अटल व्योम qedr_copy_sq_uresp(काष्ठा qedr_dev *dev,
			       काष्ठा qedr_create_qp_uresp *uresp,
			       काष्ठा qedr_qp *qp)
अणु
	uresp->sq_db_offset = DB_ADDR_SHIFT(DQ_PWM_OFFSET_XCM_RDMA_SQ_PROD);

	/* iWARP uses the same cid क्रम rq and sq */
	अगर (rdma_protocol_iwarp(&dev->ibdev, 1))
		uresp->sq_icid = qp->icid;
	अन्यथा
		uresp->sq_icid = qp->icid + 1;

	अगर (qp->usq.db_mmap_entry)
		uresp->sq_db_rec_addr =
			rdma_user_mmap_get_offset(qp->usq.db_mmap_entry);
पूर्ण

अटल पूर्णांक qedr_copy_qp_uresp(काष्ठा qedr_dev *dev,
			      काष्ठा qedr_qp *qp, काष्ठा ib_udata *udata,
			      काष्ठा qedr_create_qp_uresp *uresp)
अणु
	पूर्णांक rc;

	स_रखो(uresp, 0, माप(*uresp));

	अगर (qedr_qp_has_sq(qp))
		qedr_copy_sq_uresp(dev, uresp, qp);

	अगर (qedr_qp_has_rq(qp))
		qedr_copy_rq_uresp(dev, uresp, qp);

	uresp->atomic_supported = dev->atomic_cap != IB_ATOMIC_NONE;
	uresp->qp_id = qp->qp_id;

	rc = qedr_ib_copy_to_udata(udata, uresp, माप(*uresp));
	अगर (rc)
		DP_ERR(dev,
		       "create qp: failed a copy to user space with qp icid=0x%x.\n",
		       qp->icid);

	वापस rc;
पूर्ण

अटल व्योम qedr_set_common_qp_params(काष्ठा qedr_dev *dev,
				      काष्ठा qedr_qp *qp,
				      काष्ठा qedr_pd *pd,
				      काष्ठा ib_qp_init_attr *attrs)
अणु
	spin_lock_init(&qp->q_lock);
	अगर (rdma_protocol_iwarp(&dev->ibdev, 1)) अणु
		kref_init(&qp->refcnt);
		init_completion(&qp->iwarp_cm_comp);
	पूर्ण

	qp->pd = pd;
	qp->qp_type = attrs->qp_type;
	qp->max_अंतरभूत_data = attrs->cap.max_अंतरभूत_data;
	qp->state = QED_ROCE_QP_STATE_RESET;
	qp->संकेतed = (attrs->sq_sig_type == IB_SIGNAL_ALL_WR) ? true : false;
	qp->dev = dev;
	अगर (qedr_qp_has_sq(qp)) अणु
		qp->sq.max_sges = attrs->cap.max_send_sge;
		qp->sq_cq = get_qedr_cq(attrs->send_cq);
		DP_DEBUG(dev, QEDR_MSG_QP,
			 "SQ params:\tsq_max_sges = %d, sq_cq_id = %d\n",
			 qp->sq.max_sges, qp->sq_cq->icid);
	पूर्ण

	अगर (attrs->srq)
		qp->srq = get_qedr_srq(attrs->srq);

	अगर (qedr_qp_has_rq(qp)) अणु
		qp->rq_cq = get_qedr_cq(attrs->recv_cq);
		qp->rq.max_sges = attrs->cap.max_recv_sge;
		DP_DEBUG(dev, QEDR_MSG_QP,
			 "RQ params:\trq_max_sges = %d, rq_cq_id = %d\n",
			 qp->rq.max_sges, qp->rq_cq->icid);
	पूर्ण

	DP_DEBUG(dev, QEDR_MSG_QP,
		 "QP params:\tpd = %d, qp_type = %d, max_inline_data = %d, state = %d, signaled = %d, use_srq=%d\n",
		 pd->pd_id, qp->qp_type, qp->max_अंतरभूत_data,
		 qp->state, qp->संकेतed, (attrs->srq) ? 1 : 0);
	DP_DEBUG(dev, QEDR_MSG_QP,
		 "SQ params:\tsq_max_sges = %d, sq_cq_id = %d\n",
		 qp->sq.max_sges, qp->sq_cq->icid);
पूर्ण

अटल पूर्णांक qedr_set_roce_db_info(काष्ठा qedr_dev *dev, काष्ठा qedr_qp *qp)
अणु
	पूर्णांक rc = 0;

	अगर (qedr_qp_has_sq(qp)) अणु
		qp->sq.db = dev->db_addr +
			    DB_ADDR_SHIFT(DQ_PWM_OFFSET_XCM_RDMA_SQ_PROD);
		qp->sq.db_data.data.icid = qp->icid + 1;
		rc = qedr_db_recovery_add(dev, qp->sq.db, &qp->sq.db_data,
					  DB_REC_WIDTH_32B, DB_REC_KERNEL);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (qedr_qp_has_rq(qp)) अणु
		qp->rq.db = dev->db_addr +
			    DB_ADDR_SHIFT(DQ_PWM_OFFSET_TCM_ROCE_RQ_PROD);
		qp->rq.db_data.data.icid = qp->icid;
		rc = qedr_db_recovery_add(dev, qp->rq.db, &qp->rq.db_data,
					  DB_REC_WIDTH_32B, DB_REC_KERNEL);
		अगर (rc && qedr_qp_has_sq(qp))
			qedr_db_recovery_del(dev, qp->sq.db, &qp->sq.db_data);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक qedr_check_srq_params(काष्ठा qedr_dev *dev,
				 काष्ठा ib_srq_init_attr *attrs,
				 काष्ठा ib_udata *udata)
अणु
	काष्ठा qedr_device_attr *qattr = &dev->attr;

	अगर (attrs->attr.max_wr > qattr->max_srq_wr) अणु
		DP_ERR(dev,
		       "create srq: unsupported srq_wr=0x%x requested (max_srq_wr=0x%x)\n",
		       attrs->attr.max_wr, qattr->max_srq_wr);
		वापस -EINVAL;
	पूर्ण

	अगर (attrs->attr.max_sge > qattr->max_sge) अणु
		DP_ERR(dev,
		       "create srq: unsupported sge=0x%x requested (max_srq_sge=0x%x)\n",
		       attrs->attr.max_sge, qattr->max_sge);
	पूर्ण

	अगर (!udata && attrs->srq_type == IB_SRQT_XRC) अणु
		DP_ERR(dev, "XRC SRQs are not supported in kernel-space\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qedr_मुक्त_srq_user_params(काष्ठा qedr_srq *srq)
अणु
	qedr_मुक्त_pbl(srq->dev, &srq->usrq.pbl_info, srq->usrq.pbl_tbl);
	ib_umem_release(srq->usrq.umem);
	ib_umem_release(srq->prod_umem);
पूर्ण

अटल व्योम qedr_मुक्त_srq_kernel_params(काष्ठा qedr_srq *srq)
अणु
	काष्ठा qedr_srq_hwq_info *hw_srq = &srq->hw_srq;
	काष्ठा qedr_dev *dev = srq->dev;

	dev->ops->common->chain_मुक्त(dev->cdev, &hw_srq->pbl);

	dma_मुक्त_coherent(&dev->pdev->dev, माप(काष्ठा rdma_srq_producers),
			  hw_srq->virt_prod_pair_addr,
			  hw_srq->phy_prod_pair_addr);
पूर्ण

अटल पूर्णांक qedr_init_srq_user_params(काष्ठा ib_udata *udata,
				     काष्ठा qedr_srq *srq,
				     काष्ठा qedr_create_srq_ureq *ureq,
				     पूर्णांक access)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक rc;

	rc = qedr_init_user_queue(udata, srq->dev, &srq->usrq, ureq->srq_addr,
				  ureq->srq_len, false, access, 1);
	अगर (rc)
		वापस rc;

	srq->prod_umem = ib_umem_get(srq->ibsrq.device, ureq->prod_pair_addr,
				     माप(काष्ठा rdma_srq_producers), access);
	अगर (IS_ERR(srq->prod_umem)) अणु
		qedr_मुक्त_pbl(srq->dev, &srq->usrq.pbl_info, srq->usrq.pbl_tbl);
		ib_umem_release(srq->usrq.umem);
		DP_ERR(srq->dev,
		       "create srq: failed ib_umem_get for producer, got %ld\n",
		       PTR_ERR(srq->prod_umem));
		वापस PTR_ERR(srq->prod_umem);
	पूर्ण

	sg = srq->prod_umem->sg_head.sgl;
	srq->hw_srq.phy_prod_pair_addr = sg_dma_address(sg);

	वापस 0;
पूर्ण

अटल पूर्णांक qedr_alloc_srq_kernel_params(काष्ठा qedr_srq *srq,
					काष्ठा qedr_dev *dev,
					काष्ठा ib_srq_init_attr *init_attr)
अणु
	काष्ठा qedr_srq_hwq_info *hw_srq = &srq->hw_srq;
	काष्ठा qed_chain_init_params params = अणु
		.mode		= QED_CHAIN_MODE_PBL,
		.पूर्णांकended_use	= QED_CHAIN_USE_TO_CONSUME_PRODUCE,
		.cnt_type	= QED_CHAIN_CNT_TYPE_U32,
		.elem_size	= QEDR_SRQ_WQE_ELEM_SIZE,
	पूर्ण;
	dma_addr_t phy_prod_pair_addr;
	u32 num_elems;
	व्योम *va;
	पूर्णांक rc;

	va = dma_alloc_coherent(&dev->pdev->dev,
				माप(काष्ठा rdma_srq_producers),
				&phy_prod_pair_addr, GFP_KERNEL);
	अगर (!va) अणु
		DP_ERR(dev,
		       "create srq: failed to allocate dma memory for producer\n");
		वापस -ENOMEM;
	पूर्ण

	hw_srq->phy_prod_pair_addr = phy_prod_pair_addr;
	hw_srq->virt_prod_pair_addr = va;

	num_elems = init_attr->attr.max_wr * RDMA_MAX_SRQ_WQE_SIZE;
	params.num_elems = num_elems;

	rc = dev->ops->common->chain_alloc(dev->cdev, &hw_srq->pbl, &params);
	अगर (rc)
		जाओ err0;

	hw_srq->num_elems = num_elems;

	वापस 0;

err0:
	dma_मुक्त_coherent(&dev->pdev->dev, माप(काष्ठा rdma_srq_producers),
			  va, phy_prod_pair_addr);
	वापस rc;
पूर्ण

पूर्णांक qedr_create_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_init_attr *init_attr,
		    काष्ठा ib_udata *udata)
अणु
	काष्ठा qed_rdma_destroy_srq_in_params destroy_in_params;
	काष्ठा qed_rdma_create_srq_in_params in_params = अणुपूर्ण;
	काष्ठा qedr_dev *dev = get_qedr_dev(ibsrq->device);
	काष्ठा qed_rdma_create_srq_out_params out_params;
	काष्ठा qedr_pd *pd = get_qedr_pd(ibsrq->pd);
	काष्ठा qedr_create_srq_ureq ureq = अणुपूर्ण;
	u64 pbl_base_addr, phy_prod_pair_addr;
	काष्ठा qedr_srq_hwq_info *hw_srq;
	u32 page_cnt, page_size;
	काष्ठा qedr_srq *srq = get_qedr_srq(ibsrq);
	पूर्णांक rc = 0;

	DP_DEBUG(dev, QEDR_MSG_QP,
		 "create SRQ called from %s (pd %p)\n",
		 (udata) ? "User lib" : "kernel", pd);

	अगर (init_attr->srq_type != IB_SRQT_BASIC &&
	    init_attr->srq_type != IB_SRQT_XRC)
		वापस -EOPNOTSUPP;

	rc = qedr_check_srq_params(dev, init_attr, udata);
	अगर (rc)
		वापस -EINVAL;

	srq->dev = dev;
	srq->is_xrc = (init_attr->srq_type == IB_SRQT_XRC);
	hw_srq = &srq->hw_srq;
	spin_lock_init(&srq->lock);

	hw_srq->max_wr = init_attr->attr.max_wr;
	hw_srq->max_sges = init_attr->attr.max_sge;

	अगर (udata) अणु
		अगर (ib_copy_from_udata(&ureq, udata, min(माप(ureq),
							 udata->inlen))) अणु
			DP_ERR(dev,
			       "create srq: problem copying data from user space\n");
			जाओ err0;
		पूर्ण

		rc = qedr_init_srq_user_params(udata, srq, &ureq, 0);
		अगर (rc)
			जाओ err0;

		page_cnt = srq->usrq.pbl_info.num_pbes;
		pbl_base_addr = srq->usrq.pbl_tbl->pa;
		phy_prod_pair_addr = hw_srq->phy_prod_pair_addr;
		page_size = PAGE_SIZE;
	पूर्ण अन्यथा अणु
		काष्ठा qed_chain *pbl;

		rc = qedr_alloc_srq_kernel_params(srq, dev, init_attr);
		अगर (rc)
			जाओ err0;

		pbl = &hw_srq->pbl;
		page_cnt = qed_chain_get_page_cnt(pbl);
		pbl_base_addr = qed_chain_get_pbl_phys(pbl);
		phy_prod_pair_addr = hw_srq->phy_prod_pair_addr;
		page_size = QED_CHAIN_PAGE_SIZE;
	पूर्ण

	in_params.pd_id = pd->pd_id;
	in_params.pbl_base_addr = pbl_base_addr;
	in_params.prod_pair_addr = phy_prod_pair_addr;
	in_params.num_pages = page_cnt;
	in_params.page_size = page_size;
	अगर (srq->is_xrc) अणु
		काष्ठा qedr_xrcd *xrcd = get_qedr_xrcd(init_attr->ext.xrc.xrcd);
		काष्ठा qedr_cq *cq = get_qedr_cq(init_attr->ext.cq);

		in_params.is_xrc = 1;
		in_params.xrcd_id = xrcd->xrcd_id;
		in_params.cq_cid = cq->icid;
	पूर्ण

	rc = dev->ops->rdma_create_srq(dev->rdma_ctx, &in_params, &out_params);
	अगर (rc)
		जाओ err1;

	srq->srq_id = out_params.srq_id;

	अगर (udata) अणु
		rc = qedr_copy_srq_uresp(dev, srq, udata);
		अगर (rc)
			जाओ err2;
	पूर्ण

	rc = xa_insert_irq(&dev->srqs, srq->srq_id, srq, GFP_KERNEL);
	अगर (rc)
		जाओ err2;

	DP_DEBUG(dev, QEDR_MSG_SRQ,
		 "create srq: created srq with srq_id=0x%0x\n", srq->srq_id);
	वापस 0;

err2:
	destroy_in_params.srq_id = srq->srq_id;

	dev->ops->rdma_destroy_srq(dev->rdma_ctx, &destroy_in_params);
err1:
	अगर (udata)
		qedr_मुक्त_srq_user_params(srq);
	अन्यथा
		qedr_मुक्त_srq_kernel_params(srq);
err0:
	वापस -EFAULT;
पूर्ण

पूर्णांक qedr_destroy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_udata *udata)
अणु
	काष्ठा qed_rdma_destroy_srq_in_params in_params = अणुपूर्ण;
	काष्ठा qedr_dev *dev = get_qedr_dev(ibsrq->device);
	काष्ठा qedr_srq *srq = get_qedr_srq(ibsrq);

	xa_erase_irq(&dev->srqs, srq->srq_id);
	in_params.srq_id = srq->srq_id;
	in_params.is_xrc = srq->is_xrc;
	dev->ops->rdma_destroy_srq(dev->rdma_ctx, &in_params);

	अगर (ibsrq->uobject)
		qedr_मुक्त_srq_user_params(srq);
	अन्यथा
		qedr_मुक्त_srq_kernel_params(srq);

	DP_DEBUG(dev, QEDR_MSG_SRQ,
		 "destroy srq: destroyed srq with srq_id=0x%0x\n",
		 srq->srq_id);
	वापस 0;
पूर्ण

पूर्णांक qedr_modअगरy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *attr,
		    क्रमागत ib_srq_attr_mask attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा qed_rdma_modअगरy_srq_in_params in_params = अणुपूर्ण;
	काष्ठा qedr_dev *dev = get_qedr_dev(ibsrq->device);
	काष्ठा qedr_srq *srq = get_qedr_srq(ibsrq);
	पूर्णांक rc;

	अगर (attr_mask & IB_SRQ_MAX_WR) अणु
		DP_ERR(dev,
		       "modify srq: invalid attribute mask=0x%x specified for %p\n",
		       attr_mask, srq);
		वापस -EINVAL;
	पूर्ण

	अगर (attr_mask & IB_SRQ_LIMIT) अणु
		अगर (attr->srq_limit >= srq->hw_srq.max_wr) अणु
			DP_ERR(dev,
			       "modify srq: invalid srq_limit=0x%x (max_srq_limit=0x%x)\n",
			       attr->srq_limit, srq->hw_srq.max_wr);
			वापस -EINVAL;
		पूर्ण

		in_params.srq_id = srq->srq_id;
		in_params.wqe_limit = attr->srq_limit;
		rc = dev->ops->rdma_modअगरy_srq(dev->rdma_ctx, &in_params);
		अगर (rc)
			वापस rc;
	पूर्ण

	srq->srq_limit = attr->srq_limit;

	DP_DEBUG(dev, QEDR_MSG_SRQ,
		 "modify srq: modified srq with srq_id=0x%0x\n", srq->srq_id);

	वापस 0;
पूर्ण

अटल क्रमागत qed_rdma_qp_type qedr_ib_to_qed_qp_type(क्रमागत ib_qp_type ib_qp_type)
अणु
	चयन (ib_qp_type) अणु
	हाल IB_QPT_RC:
		वापस QED_RDMA_QP_TYPE_RC;
	हाल IB_QPT_XRC_INI:
		वापस QED_RDMA_QP_TYPE_XRC_INI;
	हाल IB_QPT_XRC_TGT:
		वापस QED_RDMA_QP_TYPE_XRC_TGT;
	शेष:
		वापस QED_RDMA_QP_TYPE_INVAL;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
qedr_init_common_qp_in_params(काष्ठा qedr_dev *dev,
			      काष्ठा qedr_pd *pd,
			      काष्ठा qedr_qp *qp,
			      काष्ठा ib_qp_init_attr *attrs,
			      bool fmr_and_reserved_lkey,
			      काष्ठा qed_rdma_create_qp_in_params *params)
अणु
	/* QP handle to be written in an async event */
	params->qp_handle_async_lo = lower_32_bits((uपूर्णांकptr_t) qp);
	params->qp_handle_async_hi = upper_32_bits((uपूर्णांकptr_t) qp);

	params->संकेत_all = (attrs->sq_sig_type == IB_SIGNAL_ALL_WR);
	params->fmr_and_reserved_lkey = fmr_and_reserved_lkey;
	params->qp_type = qedr_ib_to_qed_qp_type(attrs->qp_type);
	params->stats_queue = 0;

	अगर (pd) अणु
		params->pd = pd->pd_id;
		params->dpi = pd->uctx ? pd->uctx->dpi : dev->dpi;
	पूर्ण

	अगर (qedr_qp_has_sq(qp))
		params->sq_cq_id = get_qedr_cq(attrs->send_cq)->icid;

	अगर (qedr_qp_has_rq(qp))
		params->rq_cq_id = get_qedr_cq(attrs->recv_cq)->icid;

	अगर (qedr_qp_has_srq(qp)) अणु
		params->rq_cq_id = get_qedr_cq(attrs->recv_cq)->icid;
		params->srq_id = qp->srq->srq_id;
		params->use_srq = true;
	पूर्ण अन्यथा अणु
		params->srq_id = 0;
		params->use_srq = false;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम qedr_qp_user_prपूर्णांक(काष्ठा qedr_dev *dev, काष्ठा qedr_qp *qp)
अणु
	DP_DEBUG(dev, QEDR_MSG_QP, "create qp: successfully created user QP. "
		 "qp=%p. "
		 "sq_addr=0x%llx, "
		 "sq_len=%zd, "
		 "rq_addr=0x%llx, "
		 "rq_len=%zd"
		 "\n",
		 qp,
		 qedr_qp_has_sq(qp) ? qp->usq.buf_addr : 0x0,
		 qedr_qp_has_sq(qp) ? qp->usq.buf_len : 0,
		 qedr_qp_has_rq(qp) ? qp->urq.buf_addr : 0x0,
		 qedr_qp_has_sq(qp) ? qp->urq.buf_len : 0);
पूर्ण

अटल अंतरभूत व्योम
qedr_iwarp_populate_user_qp(काष्ठा qedr_dev *dev,
			    काष्ठा qedr_qp *qp,
			    काष्ठा qed_rdma_create_qp_out_params *out_params)
अणु
	qp->usq.pbl_tbl->va = out_params->sq_pbl_virt;
	qp->usq.pbl_tbl->pa = out_params->sq_pbl_phys;

	qedr_populate_pbls(dev, qp->usq.umem, qp->usq.pbl_tbl,
			   &qp->usq.pbl_info, FW_PAGE_SHIFT);
	अगर (!qp->srq) अणु
		qp->urq.pbl_tbl->va = out_params->rq_pbl_virt;
		qp->urq.pbl_tbl->pa = out_params->rq_pbl_phys;
	पूर्ण

	qedr_populate_pbls(dev, qp->urq.umem, qp->urq.pbl_tbl,
			   &qp->urq.pbl_info, FW_PAGE_SHIFT);
पूर्ण

अटल व्योम qedr_cleanup_user(काष्ठा qedr_dev *dev,
			      काष्ठा qedr_ucontext *ctx,
			      काष्ठा qedr_qp *qp)
अणु
	अगर (qedr_qp_has_sq(qp)) अणु
		ib_umem_release(qp->usq.umem);
		qp->usq.umem = शून्य;
	पूर्ण

	अगर (qedr_qp_has_rq(qp)) अणु
		ib_umem_release(qp->urq.umem);
		qp->urq.umem = शून्य;
	पूर्ण

	अगर (rdma_protocol_roce(&dev->ibdev, 1)) अणु
		qedr_मुक्त_pbl(dev, &qp->usq.pbl_info, qp->usq.pbl_tbl);
		qedr_मुक्त_pbl(dev, &qp->urq.pbl_info, qp->urq.pbl_tbl);
	पूर्ण अन्यथा अणु
		kमुक्त(qp->usq.pbl_tbl);
		kमुक्त(qp->urq.pbl_tbl);
	पूर्ण

	अगर (qp->usq.db_rec_data) अणु
		qedr_db_recovery_del(dev, qp->usq.db_addr,
				     &qp->usq.db_rec_data->db_data);
		rdma_user_mmap_entry_हटाओ(qp->usq.db_mmap_entry);
	पूर्ण

	अगर (qp->urq.db_rec_data) अणु
		qedr_db_recovery_del(dev, qp->urq.db_addr,
				     &qp->urq.db_rec_data->db_data);
		rdma_user_mmap_entry_हटाओ(qp->urq.db_mmap_entry);
	पूर्ण

	अगर (rdma_protocol_iwarp(&dev->ibdev, 1))
		qedr_db_recovery_del(dev, qp->urq.db_rec_db2_addr,
				     &qp->urq.db_rec_db2_data);
पूर्ण

अटल पूर्णांक qedr_create_user_qp(काष्ठा qedr_dev *dev,
			       काष्ठा qedr_qp *qp,
			       काष्ठा ib_pd *ibpd,
			       काष्ठा ib_udata *udata,
			       काष्ठा ib_qp_init_attr *attrs)
अणु
	काष्ठा qed_rdma_create_qp_in_params in_params;
	काष्ठा qed_rdma_create_qp_out_params out_params;
	काष्ठा qedr_create_qp_uresp uresp = अणुपूर्ण;
	काष्ठा qedr_create_qp_ureq ureq = अणुपूर्ण;
	पूर्णांक alloc_and_init = rdma_protocol_roce(&dev->ibdev, 1);
	काष्ठा qedr_ucontext *ctx = शून्य;
	काष्ठा qedr_pd *pd = शून्य;
	पूर्णांक rc = 0;

	qp->create_type = QEDR_QP_CREATE_USER;

	अगर (ibpd) अणु
		pd = get_qedr_pd(ibpd);
		ctx = pd->uctx;
	पूर्ण

	अगर (udata) अणु
		rc = ib_copy_from_udata(&ureq, udata, min(माप(ureq),
					udata->inlen));
		अगर (rc) अणु
			DP_ERR(dev, "Problem copying data from user space\n");
			वापस rc;
		पूर्ण
	पूर्ण

	अगर (qedr_qp_has_sq(qp)) अणु
		/* SQ - पढ़ो access only (0) */
		rc = qedr_init_user_queue(udata, dev, &qp->usq, ureq.sq_addr,
					  ureq.sq_len, true, 0, alloc_and_init);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (qedr_qp_has_rq(qp)) अणु
		/* RQ - पढ़ो access only (0) */
		rc = qedr_init_user_queue(udata, dev, &qp->urq, ureq.rq_addr,
					  ureq.rq_len, true, 0, alloc_and_init);
		अगर (rc)
			वापस rc;
	पूर्ण

	स_रखो(&in_params, 0, माप(in_params));
	qedr_init_common_qp_in_params(dev, pd, qp, attrs, false, &in_params);
	in_params.qp_handle_lo = ureq.qp_handle_lo;
	in_params.qp_handle_hi = ureq.qp_handle_hi;

	अगर (qp->qp_type == IB_QPT_XRC_TGT) अणु
		काष्ठा qedr_xrcd *xrcd = get_qedr_xrcd(attrs->xrcd);

		in_params.xrcd_id = xrcd->xrcd_id;
		in_params.qp_handle_lo = qp->qp_id;
		in_params.use_srq = 1;
	पूर्ण

	अगर (qedr_qp_has_sq(qp)) अणु
		in_params.sq_num_pages = qp->usq.pbl_info.num_pbes;
		in_params.sq_pbl_ptr = qp->usq.pbl_tbl->pa;
	पूर्ण

	अगर (qedr_qp_has_rq(qp)) अणु
		in_params.rq_num_pages = qp->urq.pbl_info.num_pbes;
		in_params.rq_pbl_ptr = qp->urq.pbl_tbl->pa;
	पूर्ण

	अगर (ctx)
		SET_FIELD(in_params.flags, QED_ROCE_EDPM_MODE, ctx->edpm_mode);

	qp->qed_qp = dev->ops->rdma_create_qp(dev->rdma_ctx,
					      &in_params, &out_params);

	अगर (!qp->qed_qp) अणु
		rc = -ENOMEM;
		जाओ err1;
	पूर्ण

	अगर (rdma_protocol_iwarp(&dev->ibdev, 1))
		qedr_iwarp_populate_user_qp(dev, qp, &out_params);

	qp->qp_id = out_params.qp_id;
	qp->icid = out_params.icid;

	अगर (udata) अणु
		rc = qedr_copy_qp_uresp(dev, qp, udata, &uresp);
		अगर (rc)
			जाओ err;
	पूर्ण

	/* db offset was calculated in copy_qp_uresp, now set in the user q */
	अगर (qedr_qp_has_sq(qp)) अणु
		qp->usq.db_addr = ctx->dpi_addr + uresp.sq_db_offset;
		rc = qedr_db_recovery_add(dev, qp->usq.db_addr,
					  &qp->usq.db_rec_data->db_data,
					  DB_REC_WIDTH_32B,
					  DB_REC_USER);
		अगर (rc)
			जाओ err;
	पूर्ण

	अगर (qedr_qp_has_rq(qp)) अणु
		qp->urq.db_addr = ctx->dpi_addr + uresp.rq_db_offset;
		rc = qedr_db_recovery_add(dev, qp->urq.db_addr,
					  &qp->urq.db_rec_data->db_data,
					  DB_REC_WIDTH_32B,
					  DB_REC_USER);
		अगर (rc)
			जाओ err;
	पूर्ण

	अगर (rdma_protocol_iwarp(&dev->ibdev, 1)) अणु
		qp->urq.db_rec_db2_addr = ctx->dpi_addr + uresp.rq_db2_offset;

		/* calculate the db_rec_db2 data since it is स्थिरant so no
		 * need to reflect from user
		 */
		qp->urq.db_rec_db2_data.data.icid = cpu_to_le16(qp->icid);
		qp->urq.db_rec_db2_data.data.value =
			cpu_to_le16(DQ_TCM_IWARP_POST_RQ_CF_CMD);

		rc = qedr_db_recovery_add(dev, qp->urq.db_rec_db2_addr,
					  &qp->urq.db_rec_db2_data,
					  DB_REC_WIDTH_32B,
					  DB_REC_USER);
		अगर (rc)
			जाओ err;
	पूर्ण
	qedr_qp_user_prपूर्णांक(dev, qp);
	वापस rc;
err:
	rc = dev->ops->rdma_destroy_qp(dev->rdma_ctx, qp->qed_qp);
	अगर (rc)
		DP_ERR(dev, "create qp: fatal fault. rc=%d", rc);

err1:
	qedr_cleanup_user(dev, ctx, qp);
	वापस rc;
पूर्ण

अटल पूर्णांक qedr_set_iwarp_db_info(काष्ठा qedr_dev *dev, काष्ठा qedr_qp *qp)
अणु
	पूर्णांक rc;

	qp->sq.db = dev->db_addr +
	    DB_ADDR_SHIFT(DQ_PWM_OFFSET_XCM_RDMA_SQ_PROD);
	qp->sq.db_data.data.icid = qp->icid;

	rc = qedr_db_recovery_add(dev, qp->sq.db,
				  &qp->sq.db_data,
				  DB_REC_WIDTH_32B,
				  DB_REC_KERNEL);
	अगर (rc)
		वापस rc;

	qp->rq.db = dev->db_addr +
		    DB_ADDR_SHIFT(DQ_PWM_OFFSET_TCM_IWARP_RQ_PROD);
	qp->rq.db_data.data.icid = qp->icid;
	qp->rq.iwarp_db2 = dev->db_addr +
			   DB_ADDR_SHIFT(DQ_PWM_OFFSET_TCM_FLAGS);
	qp->rq.iwarp_db2_data.data.icid = qp->icid;
	qp->rq.iwarp_db2_data.data.value = DQ_TCM_IWARP_POST_RQ_CF_CMD;

	rc = qedr_db_recovery_add(dev, qp->rq.db,
				  &qp->rq.db_data,
				  DB_REC_WIDTH_32B,
				  DB_REC_KERNEL);
	अगर (rc)
		वापस rc;

	rc = qedr_db_recovery_add(dev, qp->rq.iwarp_db2,
				  &qp->rq.iwarp_db2_data,
				  DB_REC_WIDTH_32B,
				  DB_REC_KERNEL);
	वापस rc;
पूर्ण

अटल पूर्णांक
qedr_roce_create_kernel_qp(काष्ठा qedr_dev *dev,
			   काष्ठा qedr_qp *qp,
			   काष्ठा qed_rdma_create_qp_in_params *in_params,
			   u32 n_sq_elems, u32 n_rq_elems)
अणु
	काष्ठा qed_rdma_create_qp_out_params out_params;
	काष्ठा qed_chain_init_params params = अणु
		.mode		= QED_CHAIN_MODE_PBL,
		.cnt_type	= QED_CHAIN_CNT_TYPE_U32,
	पूर्ण;
	पूर्णांक rc;

	params.पूर्णांकended_use = QED_CHAIN_USE_TO_PRODUCE;
	params.num_elems = n_sq_elems;
	params.elem_size = QEDR_SQE_ELEMENT_SIZE;

	rc = dev->ops->common->chain_alloc(dev->cdev, &qp->sq.pbl, &params);
	अगर (rc)
		वापस rc;

	in_params->sq_num_pages = qed_chain_get_page_cnt(&qp->sq.pbl);
	in_params->sq_pbl_ptr = qed_chain_get_pbl_phys(&qp->sq.pbl);

	params.पूर्णांकended_use = QED_CHAIN_USE_TO_CONSUME_PRODUCE;
	params.num_elems = n_rq_elems;
	params.elem_size = QEDR_RQE_ELEMENT_SIZE;

	rc = dev->ops->common->chain_alloc(dev->cdev, &qp->rq.pbl, &params);
	अगर (rc)
		वापस rc;

	in_params->rq_num_pages = qed_chain_get_page_cnt(&qp->rq.pbl);
	in_params->rq_pbl_ptr = qed_chain_get_pbl_phys(&qp->rq.pbl);

	qp->qed_qp = dev->ops->rdma_create_qp(dev->rdma_ctx,
					      in_params, &out_params);

	अगर (!qp->qed_qp)
		वापस -EINVAL;

	qp->qp_id = out_params.qp_id;
	qp->icid = out_params.icid;

	वापस qedr_set_roce_db_info(dev, qp);
पूर्ण

अटल पूर्णांक
qedr_iwarp_create_kernel_qp(काष्ठा qedr_dev *dev,
			    काष्ठा qedr_qp *qp,
			    काष्ठा qed_rdma_create_qp_in_params *in_params,
			    u32 n_sq_elems, u32 n_rq_elems)
अणु
	काष्ठा qed_rdma_create_qp_out_params out_params;
	काष्ठा qed_chain_init_params params = अणु
		.mode		= QED_CHAIN_MODE_PBL,
		.cnt_type	= QED_CHAIN_CNT_TYPE_U32,
	पूर्ण;
	पूर्णांक rc;

	in_params->sq_num_pages = QED_CHAIN_PAGE_CNT(n_sq_elems,
						     QEDR_SQE_ELEMENT_SIZE,
						     QED_CHAIN_PAGE_SIZE,
						     QED_CHAIN_MODE_PBL);
	in_params->rq_num_pages = QED_CHAIN_PAGE_CNT(n_rq_elems,
						     QEDR_RQE_ELEMENT_SIZE,
						     QED_CHAIN_PAGE_SIZE,
						     QED_CHAIN_MODE_PBL);

	qp->qed_qp = dev->ops->rdma_create_qp(dev->rdma_ctx,
					      in_params, &out_params);

	अगर (!qp->qed_qp)
		वापस -EINVAL;

	/* Now we allocate the chain */

	params.पूर्णांकended_use = QED_CHAIN_USE_TO_PRODUCE;
	params.num_elems = n_sq_elems;
	params.elem_size = QEDR_SQE_ELEMENT_SIZE;
	params.ext_pbl_virt = out_params.sq_pbl_virt;
	params.ext_pbl_phys = out_params.sq_pbl_phys;

	rc = dev->ops->common->chain_alloc(dev->cdev, &qp->sq.pbl, &params);
	अगर (rc)
		जाओ err;

	params.पूर्णांकended_use = QED_CHAIN_USE_TO_CONSUME_PRODUCE;
	params.num_elems = n_rq_elems;
	params.elem_size = QEDR_RQE_ELEMENT_SIZE;
	params.ext_pbl_virt = out_params.rq_pbl_virt;
	params.ext_pbl_phys = out_params.rq_pbl_phys;

	rc = dev->ops->common->chain_alloc(dev->cdev, &qp->rq.pbl, &params);
	अगर (rc)
		जाओ err;

	qp->qp_id = out_params.qp_id;
	qp->icid = out_params.icid;

	वापस qedr_set_iwarp_db_info(dev, qp);

err:
	dev->ops->rdma_destroy_qp(dev->rdma_ctx, qp->qed_qp);

	वापस rc;
पूर्ण

अटल व्योम qedr_cleanup_kernel(काष्ठा qedr_dev *dev, काष्ठा qedr_qp *qp)
अणु
	dev->ops->common->chain_मुक्त(dev->cdev, &qp->sq.pbl);
	kमुक्त(qp->wqe_wr_id);

	dev->ops->common->chain_मुक्त(dev->cdev, &qp->rq.pbl);
	kमुक्त(qp->rqe_wr_id);

	/* GSI qp is not रेजिस्टरed to db mechanism so no need to delete */
	अगर (qp->qp_type == IB_QPT_GSI)
		वापस;

	qedr_db_recovery_del(dev, qp->sq.db, &qp->sq.db_data);

	अगर (!qp->srq) अणु
		qedr_db_recovery_del(dev, qp->rq.db, &qp->rq.db_data);

		अगर (rdma_protocol_iwarp(&dev->ibdev, 1))
			qedr_db_recovery_del(dev, qp->rq.iwarp_db2,
					     &qp->rq.iwarp_db2_data);
	पूर्ण
पूर्ण

अटल पूर्णांक qedr_create_kernel_qp(काष्ठा qedr_dev *dev,
				 काष्ठा qedr_qp *qp,
				 काष्ठा ib_pd *ibpd,
				 काष्ठा ib_qp_init_attr *attrs)
अणु
	काष्ठा qed_rdma_create_qp_in_params in_params;
	काष्ठा qedr_pd *pd = get_qedr_pd(ibpd);
	पूर्णांक rc = -EINVAL;
	u32 n_rq_elems;
	u32 n_sq_elems;
	u32 n_sq_entries;

	स_रखो(&in_params, 0, माप(in_params));
	qp->create_type = QEDR_QP_CREATE_KERNEL;

	/* A single work request may take up to QEDR_MAX_SQ_WQE_SIZE elements in
	 * the ring. The ring should allow at least a single WR, even अगर the
	 * user requested none, due to allocation issues.
	 * We should add an extra WR since the prod and cons indices of
	 * wqe_wr_id are managed in such a way that the WQ is considered full
	 * when (prod+1)%max_wr==cons. We currently करोn't करो that because we
	 * द्विगुन the number of entries due an iSER issue that pushes far more
	 * WRs than indicated. If we decline its ib_post_send() then we get
	 * error prपूर्णांकs in the dmesg we'd like to aव्योम.
	 */
	qp->sq.max_wr = min_t(u32, attrs->cap.max_send_wr * dev->wq_multiplier,
			      dev->attr.max_sqe);

	qp->wqe_wr_id = kसुस्मृति(qp->sq.max_wr, माप(*qp->wqe_wr_id),
				GFP_KERNEL);
	अगर (!qp->wqe_wr_id) अणु
		DP_ERR(dev, "create qp: failed SQ shadow memory allocation\n");
		वापस -ENOMEM;
	पूर्ण

	/* QP handle to be written in CQE */
	in_params.qp_handle_lo = lower_32_bits((uपूर्णांकptr_t) qp);
	in_params.qp_handle_hi = upper_32_bits((uपूर्णांकptr_t) qp);

	/* A single work request may take up to QEDR_MAX_RQ_WQE_SIZE elements in
	 * the ring. There ring should allow at least a single WR, even अगर the
	 * user requested none, due to allocation issues.
	 */
	qp->rq.max_wr = (u16) max_t(u32, attrs->cap.max_recv_wr, 1);

	/* Allocate driver पूर्णांकernal RQ array */
	qp->rqe_wr_id = kसुस्मृति(qp->rq.max_wr, माप(*qp->rqe_wr_id),
				GFP_KERNEL);
	अगर (!qp->rqe_wr_id) अणु
		DP_ERR(dev,
		       "create qp: failed RQ shadow memory allocation\n");
		kमुक्त(qp->wqe_wr_id);
		वापस -ENOMEM;
	पूर्ण

	qedr_init_common_qp_in_params(dev, pd, qp, attrs, true, &in_params);

	n_sq_entries = attrs->cap.max_send_wr;
	n_sq_entries = min_t(u32, n_sq_entries, dev->attr.max_sqe);
	n_sq_entries = max_t(u32, n_sq_entries, 1);
	n_sq_elems = n_sq_entries * QEDR_MAX_SQE_ELEMENTS_PER_SQE;

	n_rq_elems = qp->rq.max_wr * QEDR_MAX_RQE_ELEMENTS_PER_RQE;

	अगर (rdma_protocol_iwarp(&dev->ibdev, 1))
		rc = qedr_iwarp_create_kernel_qp(dev, qp, &in_params,
						 n_sq_elems, n_rq_elems);
	अन्यथा
		rc = qedr_roce_create_kernel_qp(dev, qp, &in_params,
						n_sq_elems, n_rq_elems);
	अगर (rc)
		qedr_cleanup_kernel(dev, qp);

	वापस rc;
पूर्ण

अटल पूर्णांक qedr_मुक्त_qp_resources(काष्ठा qedr_dev *dev, काष्ठा qedr_qp *qp,
				  काष्ठा ib_udata *udata)
अणु
	काष्ठा qedr_ucontext *ctx =
		rdma_udata_to_drv_context(udata, काष्ठा qedr_ucontext,
					  ibucontext);
	पूर्णांक rc;

	अगर (qp->qp_type != IB_QPT_GSI) अणु
		rc = dev->ops->rdma_destroy_qp(dev->rdma_ctx, qp->qed_qp);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (qp->create_type == QEDR_QP_CREATE_USER)
		qedr_cleanup_user(dev, ctx, qp);
	अन्यथा
		qedr_cleanup_kernel(dev, qp);

	वापस 0;
पूर्ण

काष्ठा ib_qp *qedr_create_qp(काष्ठा ib_pd *ibpd,
			     काष्ठा ib_qp_init_attr *attrs,
			     काष्ठा ib_udata *udata)
अणु
	काष्ठा qedr_xrcd *xrcd = शून्य;
	काष्ठा qedr_pd *pd = शून्य;
	काष्ठा qedr_dev *dev;
	काष्ठा qedr_qp *qp;
	काष्ठा ib_qp *ibqp;
	पूर्णांक rc = 0;

	अगर (attrs->create_flags)
		वापस ERR_PTR(-EOPNOTSUPP);

	अगर (attrs->qp_type == IB_QPT_XRC_TGT) अणु
		xrcd = get_qedr_xrcd(attrs->xrcd);
		dev = get_qedr_dev(xrcd->ibxrcd.device);
	पूर्ण अन्यथा अणु
		pd = get_qedr_pd(ibpd);
		dev = get_qedr_dev(ibpd->device);
	पूर्ण

	DP_DEBUG(dev, QEDR_MSG_QP, "create qp: called from %s, pd=%p\n",
		 udata ? "user library" : "kernel", pd);

	rc = qedr_check_qp_attrs(ibpd, dev, attrs, udata);
	अगर (rc)
		वापस ERR_PTR(rc);

	DP_DEBUG(dev, QEDR_MSG_QP,
		 "create qp: called from %s, event_handler=%p, eepd=%p sq_cq=%p, sq_icid=%d, rq_cq=%p, rq_icid=%d\n",
		 udata ? "user library" : "kernel", attrs->event_handler, pd,
		 get_qedr_cq(attrs->send_cq),
		 get_qedr_cq(attrs->send_cq)->icid,
		 get_qedr_cq(attrs->recv_cq),
		 attrs->recv_cq ? get_qedr_cq(attrs->recv_cq)->icid : 0);

	qp = kzalloc(माप(*qp), GFP_KERNEL);
	अगर (!qp) अणु
		DP_ERR(dev, "create qp: failed allocating memory\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	qedr_set_common_qp_params(dev, qp, pd, attrs);

	अगर (attrs->qp_type == IB_QPT_GSI) अणु
		ibqp = qedr_create_gsi_qp(dev, attrs, qp);
		अगर (IS_ERR(ibqp))
			kमुक्त(qp);
		वापस ibqp;
	पूर्ण

	अगर (udata || xrcd)
		rc = qedr_create_user_qp(dev, qp, ibpd, udata, attrs);
	अन्यथा
		rc = qedr_create_kernel_qp(dev, qp, ibpd, attrs);

	अगर (rc)
		जाओ out_मुक्त_qp;

	qp->ibqp.qp_num = qp->qp_id;

	अगर (rdma_protocol_iwarp(&dev->ibdev, 1)) अणु
		rc = xa_insert(&dev->qps, qp->qp_id, qp, GFP_KERNEL);
		अगर (rc)
			जाओ out_मुक्त_qp_resources;
	पूर्ण

	वापस &qp->ibqp;

out_मुक्त_qp_resources:
	qedr_मुक्त_qp_resources(dev, qp, udata);
out_मुक्त_qp:
	kमुक्त(qp);

	वापस ERR_PTR(-EFAULT);
पूर्ण

अटल क्रमागत ib_qp_state qedr_get_ibqp_state(क्रमागत qed_roce_qp_state qp_state)
अणु
	चयन (qp_state) अणु
	हाल QED_ROCE_QP_STATE_RESET:
		वापस IB_QPS_RESET;
	हाल QED_ROCE_QP_STATE_INIT:
		वापस IB_QPS_INIT;
	हाल QED_ROCE_QP_STATE_RTR:
		वापस IB_QPS_RTR;
	हाल QED_ROCE_QP_STATE_RTS:
		वापस IB_QPS_RTS;
	हाल QED_ROCE_QP_STATE_SQD:
		वापस IB_QPS_SQD;
	हाल QED_ROCE_QP_STATE_ERR:
		वापस IB_QPS_ERR;
	हाल QED_ROCE_QP_STATE_SQE:
		वापस IB_QPS_SQE;
	पूर्ण
	वापस IB_QPS_ERR;
पूर्ण

अटल क्रमागत qed_roce_qp_state qedr_get_state_from_ibqp(
					क्रमागत ib_qp_state qp_state)
अणु
	चयन (qp_state) अणु
	हाल IB_QPS_RESET:
		वापस QED_ROCE_QP_STATE_RESET;
	हाल IB_QPS_INIT:
		वापस QED_ROCE_QP_STATE_INIT;
	हाल IB_QPS_RTR:
		वापस QED_ROCE_QP_STATE_RTR;
	हाल IB_QPS_RTS:
		वापस QED_ROCE_QP_STATE_RTS;
	हाल IB_QPS_SQD:
		वापस QED_ROCE_QP_STATE_SQD;
	हाल IB_QPS_ERR:
		वापस QED_ROCE_QP_STATE_ERR;
	शेष:
		वापस QED_ROCE_QP_STATE_ERR;
	पूर्ण
पूर्ण

अटल व्योम qedr_reset_qp_hwq_info(काष्ठा qedr_qp_hwq_info *qph)
अणु
	qed_chain_reset(&qph->pbl);
	qph->prod = 0;
	qph->cons = 0;
	qph->wqe_cons = 0;
	qph->db_data.data.value = cpu_to_le16(0);
पूर्ण

अटल पूर्णांक qedr_update_qp_state(काष्ठा qedr_dev *dev,
				काष्ठा qedr_qp *qp,
				क्रमागत qed_roce_qp_state cur_state,
				क्रमागत qed_roce_qp_state new_state)
अणु
	पूर्णांक status = 0;

	अगर (new_state == cur_state)
		वापस 0;

	चयन (cur_state) अणु
	हाल QED_ROCE_QP_STATE_RESET:
		चयन (new_state) अणु
		हाल QED_ROCE_QP_STATE_INIT:
			qp->prev_wqe_size = 0;
			qedr_reset_qp_hwq_info(&qp->sq);
			qedr_reset_qp_hwq_info(&qp->rq);
			अवरोध;
		शेष:
			status = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल QED_ROCE_QP_STATE_INIT:
		चयन (new_state) अणु
		हाल QED_ROCE_QP_STATE_RTR:
			/* Update करोorbell (in हाल post_recv was
			 * करोne beक्रमe move to RTR)
			 */

			अगर (rdma_protocol_roce(&dev->ibdev, 1)) अणु
				ग_लिखोl(qp->rq.db_data.raw, qp->rq.db);
			पूर्ण
			अवरोध;
		हाल QED_ROCE_QP_STATE_ERR:
			अवरोध;
		शेष:
			/* Invalid state change. */
			status = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल QED_ROCE_QP_STATE_RTR:
		/* RTR->XXX */
		चयन (new_state) अणु
		हाल QED_ROCE_QP_STATE_RTS:
			अवरोध;
		हाल QED_ROCE_QP_STATE_ERR:
			अवरोध;
		शेष:
			/* Invalid state change. */
			status = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल QED_ROCE_QP_STATE_RTS:
		/* RTS->XXX */
		चयन (new_state) अणु
		हाल QED_ROCE_QP_STATE_SQD:
			अवरोध;
		हाल QED_ROCE_QP_STATE_ERR:
			अवरोध;
		शेष:
			/* Invalid state change. */
			status = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल QED_ROCE_QP_STATE_SQD:
		/* SQD->XXX */
		चयन (new_state) अणु
		हाल QED_ROCE_QP_STATE_RTS:
		हाल QED_ROCE_QP_STATE_ERR:
			अवरोध;
		शेष:
			/* Invalid state change. */
			status = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल QED_ROCE_QP_STATE_ERR:
		/* ERR->XXX */
		चयन (new_state) अणु
		हाल QED_ROCE_QP_STATE_RESET:
			अगर ((qp->rq.prod != qp->rq.cons) ||
			    (qp->sq.prod != qp->sq.cons)) अणु
				DP_NOTICE(dev,
					  "Error->Reset with rq/sq not empty rq.prod=%x rq.cons=%x sq.prod=%x sq.cons=%x\n",
					  qp->rq.prod, qp->rq.cons, qp->sq.prod,
					  qp->sq.cons);
				status = -EINVAL;
			पूर्ण
			अवरोध;
		शेष:
			status = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		status = -EINVAL;
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक qedr_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
		   पूर्णांक attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा qedr_qp *qp = get_qedr_qp(ibqp);
	काष्ठा qed_rdma_modअगरy_qp_in_params qp_params = अणु 0 पूर्ण;
	काष्ठा qedr_dev *dev = get_qedr_dev(&qp->dev->ibdev);
	स्थिर काष्ठा ib_global_route *grh = rdma_ah_पढ़ो_grh(&attr->ah_attr);
	क्रमागत ib_qp_state old_qp_state, new_qp_state;
	क्रमागत qed_roce_qp_state cur_state;
	पूर्णांक rc = 0;

	DP_DEBUG(dev, QEDR_MSG_QP,
		 "modify qp: qp %p attr_mask=0x%x, state=%d", qp, attr_mask,
		 attr->qp_state);

	अगर (attr_mask & ~IB_QP_ATTR_STANDARD_BITS)
		वापस -EOPNOTSUPP;

	old_qp_state = qedr_get_ibqp_state(qp->state);
	अगर (attr_mask & IB_QP_STATE)
		new_qp_state = attr->qp_state;
	अन्यथा
		new_qp_state = old_qp_state;

	अगर (rdma_protocol_roce(&dev->ibdev, 1)) अणु
		अगर (!ib_modअगरy_qp_is_ok(old_qp_state, new_qp_state,
					ibqp->qp_type, attr_mask)) अणु
			DP_ERR(dev,
			       "modify qp: invalid attribute mask=0x%x specified for\n"
			       "qpn=0x%x of type=0x%x old_qp_state=0x%x, new_qp_state=0x%x\n",
			       attr_mask, qp->qp_id, ibqp->qp_type,
			       old_qp_state, new_qp_state);
			rc = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण

	/* Translate the masks... */
	अगर (attr_mask & IB_QP_STATE) अणु
		SET_FIELD(qp_params.modअगरy_flags,
			  QED_RDMA_MODIFY_QP_VALID_NEW_STATE, 1);
		qp_params.new_state = qedr_get_state_from_ibqp(attr->qp_state);
	पूर्ण

	अगर (attr_mask & IB_QP_EN_SQD_ASYNC_NOTIFY)
		qp_params.sqd_async = true;

	अगर (attr_mask & IB_QP_PKEY_INDEX) अणु
		SET_FIELD(qp_params.modअगरy_flags,
			  QED_ROCE_MODIFY_QP_VALID_PKEY, 1);
		अगर (attr->pkey_index >= QEDR_ROCE_PKEY_TABLE_LEN) अणु
			rc = -EINVAL;
			जाओ err;
		पूर्ण

		qp_params.pkey = QEDR_ROCE_PKEY_DEFAULT;
	पूर्ण

	अगर (attr_mask & IB_QP_QKEY)
		qp->qkey = attr->qkey;

	अगर (attr_mask & IB_QP_ACCESS_FLAGS) अणु
		SET_FIELD(qp_params.modअगरy_flags,
			  QED_RDMA_MODIFY_QP_VALID_RDMA_OPS_EN, 1);
		qp_params.incoming_rdma_पढ़ो_en = attr->qp_access_flags &
						  IB_ACCESS_REMOTE_READ;
		qp_params.incoming_rdma_ग_लिखो_en = attr->qp_access_flags &
						   IB_ACCESS_REMOTE_WRITE;
		qp_params.incoming_atomic_en = attr->qp_access_flags &
					       IB_ACCESS_REMOTE_ATOMIC;
	पूर्ण

	अगर (attr_mask & (IB_QP_AV | IB_QP_PATH_MTU)) अणु
		अगर (rdma_protocol_iwarp(&dev->ibdev, 1))
			वापस -EINVAL;

		अगर (attr_mask & IB_QP_PATH_MTU) अणु
			अगर (attr->path_mtu < IB_MTU_256 ||
			    attr->path_mtu > IB_MTU_4096) अणु
				pr_err("error: Only MTU sizes of 256, 512, 1024, 2048 and 4096 are supported by RoCE\n");
				rc = -EINVAL;
				जाओ err;
			पूर्ण
			qp->mtu = min(ib_mtu_क्रमागत_to_पूर्णांक(attr->path_mtu),
				      ib_mtu_क्रमागत_to_पूर्णांक(iboe_get_mtu
							 (dev->ndev->mtu)));
		पूर्ण

		अगर (!qp->mtu) अणु
			qp->mtu =
			ib_mtu_क्रमागत_to_पूर्णांक(iboe_get_mtu(dev->ndev->mtu));
			pr_err("Fixing zeroed MTU to qp->mtu = %d\n", qp->mtu);
		पूर्ण

		SET_FIELD(qp_params.modअगरy_flags,
			  QED_ROCE_MODIFY_QP_VALID_ADDRESS_VECTOR, 1);

		qp_params.traffic_class_tos = grh->traffic_class;
		qp_params.flow_label = grh->flow_label;
		qp_params.hop_limit_ttl = grh->hop_limit;

		qp->sgid_idx = grh->sgid_index;

		rc = get_gid_info_from_table(ibqp, attr, attr_mask, &qp_params);
		अगर (rc) अणु
			DP_ERR(dev,
			       "modify qp: problems with GID index %d (rc=%d)\n",
			       grh->sgid_index, rc);
			वापस rc;
		पूर्ण

		rc = qedr_get_dmac(dev, &attr->ah_attr,
				   qp_params.remote_mac_addr);
		अगर (rc)
			वापस rc;

		qp_params.use_local_mac = true;
		ether_addr_copy(qp_params.local_mac_addr, dev->ndev->dev_addr);

		DP_DEBUG(dev, QEDR_MSG_QP, "dgid=%x:%x:%x:%x\n",
			 qp_params.dgid.dwords[0], qp_params.dgid.dwords[1],
			 qp_params.dgid.dwords[2], qp_params.dgid.dwords[3]);
		DP_DEBUG(dev, QEDR_MSG_QP, "sgid=%x:%x:%x:%x\n",
			 qp_params.sgid.dwords[0], qp_params.sgid.dwords[1],
			 qp_params.sgid.dwords[2], qp_params.sgid.dwords[3]);
		DP_DEBUG(dev, QEDR_MSG_QP, "remote_mac=[%pM]\n",
			 qp_params.remote_mac_addr);

		qp_params.mtu = qp->mtu;
		qp_params.lb_indication = false;
	पूर्ण

	अगर (!qp_params.mtu) अणु
		/* Stay with current MTU */
		अगर (qp->mtu)
			qp_params.mtu = qp->mtu;
		अन्यथा
			qp_params.mtu =
			    ib_mtu_क्रमागत_to_पूर्णांक(iboe_get_mtu(dev->ndev->mtu));
	पूर्ण

	अगर (attr_mask & IB_QP_TIMEOUT) अणु
		SET_FIELD(qp_params.modअगरy_flags,
			  QED_ROCE_MODIFY_QP_VALID_ACK_TIMEOUT, 1);

		/* The received समयout value is an exponent used like this:
		 *    "12.7.34 LOCAL ACK TIMEOUT
		 *    Value representing the transport (ACK) समयout क्रम use by
		 *    the remote, expressed as: 4.096 * 2^समयout [usec]"
		 * The FW expects समयout in msec so we need to भागide the usec
		 * result by 1000. We'll approximate 1000~2^10, and 4.096 ~ 2^2,
		 * so we get: 2^2 * 2^समयout / 2^10 = 2^(समयout - 8).
		 * The value of zero means infinite so we use a 'max_t' to make
		 * sure that sub 1 msec values will be configured as 1 msec.
		 */
		अगर (attr->समयout)
			qp_params.ack_समयout =
					1 << max_t(पूर्णांक, attr->समयout - 8, 0);
		अन्यथा
			qp_params.ack_समयout = 0;
	पूर्ण

	अगर (attr_mask & IB_QP_RETRY_CNT) अणु
		SET_FIELD(qp_params.modअगरy_flags,
			  QED_ROCE_MODIFY_QP_VALID_RETRY_CNT, 1);
		qp_params.retry_cnt = attr->retry_cnt;
	पूर्ण

	अगर (attr_mask & IB_QP_RNR_RETRY) अणु
		SET_FIELD(qp_params.modअगरy_flags,
			  QED_ROCE_MODIFY_QP_VALID_RNR_RETRY_CNT, 1);
		qp_params.rnr_retry_cnt = attr->rnr_retry;
	पूर्ण

	अगर (attr_mask & IB_QP_RQ_PSN) अणु
		SET_FIELD(qp_params.modअगरy_flags,
			  QED_ROCE_MODIFY_QP_VALID_RQ_PSN, 1);
		qp_params.rq_psn = attr->rq_psn;
		qp->rq_psn = attr->rq_psn;
	पूर्ण

	अगर (attr_mask & IB_QP_MAX_QP_RD_ATOMIC) अणु
		अगर (attr->max_rd_atomic > dev->attr.max_qp_req_rd_atomic_resc) अणु
			rc = -EINVAL;
			DP_ERR(dev,
			       "unsupported max_rd_atomic=%d, supported=%d\n",
			       attr->max_rd_atomic,
			       dev->attr.max_qp_req_rd_atomic_resc);
			जाओ err;
		पूर्ण

		SET_FIELD(qp_params.modअगरy_flags,
			  QED_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_REQ, 1);
		qp_params.max_rd_atomic_req = attr->max_rd_atomic;
	पूर्ण

	अगर (attr_mask & IB_QP_MIN_RNR_TIMER) अणु
		SET_FIELD(qp_params.modअगरy_flags,
			  QED_ROCE_MODIFY_QP_VALID_MIN_RNR_NAK_TIMER, 1);
		qp_params.min_rnr_nak_समयr = attr->min_rnr_समयr;
	पूर्ण

	अगर (attr_mask & IB_QP_SQ_PSN) अणु
		SET_FIELD(qp_params.modअगरy_flags,
			  QED_ROCE_MODIFY_QP_VALID_SQ_PSN, 1);
		qp_params.sq_psn = attr->sq_psn;
		qp->sq_psn = attr->sq_psn;
	पूर्ण

	अगर (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC) अणु
		अगर (attr->max_dest_rd_atomic >
		    dev->attr.max_qp_resp_rd_atomic_resc) अणु
			DP_ERR(dev,
			       "unsupported max_dest_rd_atomic=%d, supported=%d\n",
			       attr->max_dest_rd_atomic,
			       dev->attr.max_qp_resp_rd_atomic_resc);

			rc = -EINVAL;
			जाओ err;
		पूर्ण

		SET_FIELD(qp_params.modअगरy_flags,
			  QED_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_RESP, 1);
		qp_params.max_rd_atomic_resp = attr->max_dest_rd_atomic;
	पूर्ण

	अगर (attr_mask & IB_QP_DEST_QPN) अणु
		SET_FIELD(qp_params.modअगरy_flags,
			  QED_ROCE_MODIFY_QP_VALID_DEST_QP, 1);

		qp_params.dest_qp = attr->dest_qp_num;
		qp->dest_qp_num = attr->dest_qp_num;
	पूर्ण

	cur_state = qp->state;

	/* Update the QP state beक्रमe the actual ramrod to prevent a race with
	 * fast path. Modअगरying the QP state to error will cause the device to
	 * flush the CQEs and जबतक polling the flushed CQEs will considered as
	 * a potential issue अगर the QP isn't in error state.
	 */
	अगर ((attr_mask & IB_QP_STATE) && qp->qp_type != IB_QPT_GSI &&
	    !udata && qp_params.new_state == QED_ROCE_QP_STATE_ERR)
		qp->state = QED_ROCE_QP_STATE_ERR;

	अगर (qp->qp_type != IB_QPT_GSI)
		rc = dev->ops->rdma_modअगरy_qp(dev->rdma_ctx,
					      qp->qed_qp, &qp_params);

	अगर (attr_mask & IB_QP_STATE) अणु
		अगर ((qp->qp_type != IB_QPT_GSI) && (!udata))
			rc = qedr_update_qp_state(dev, qp, cur_state,
						  qp_params.new_state);
		qp->state = qp_params.new_state;
	पूर्ण

err:
	वापस rc;
पूर्ण

अटल पूर्णांक qedr_to_ib_qp_acc_flags(काष्ठा qed_rdma_query_qp_out_params *params)
अणु
	पूर्णांक ib_qp_acc_flags = 0;

	अगर (params->incoming_rdma_ग_लिखो_en)
		ib_qp_acc_flags |= IB_ACCESS_REMOTE_WRITE;
	अगर (params->incoming_rdma_पढ़ो_en)
		ib_qp_acc_flags |= IB_ACCESS_REMOTE_READ;
	अगर (params->incoming_atomic_en)
		ib_qp_acc_flags |= IB_ACCESS_REMOTE_ATOMIC;
	ib_qp_acc_flags |= IB_ACCESS_LOCAL_WRITE;
	वापस ib_qp_acc_flags;
पूर्ण

पूर्णांक qedr_query_qp(काष्ठा ib_qp *ibqp,
		  काष्ठा ib_qp_attr *qp_attr,
		  पूर्णांक attr_mask, काष्ठा ib_qp_init_attr *qp_init_attr)
अणु
	काष्ठा qed_rdma_query_qp_out_params params;
	काष्ठा qedr_qp *qp = get_qedr_qp(ibqp);
	काष्ठा qedr_dev *dev = qp->dev;
	पूर्णांक rc = 0;

	स_रखो(&params, 0, माप(params));

	rc = dev->ops->rdma_query_qp(dev->rdma_ctx, qp->qed_qp, &params);
	अगर (rc)
		जाओ err;

	स_रखो(qp_attr, 0, माप(*qp_attr));
	स_रखो(qp_init_attr, 0, माप(*qp_init_attr));

	qp_attr->qp_state = qedr_get_ibqp_state(params.state);
	qp_attr->cur_qp_state = qedr_get_ibqp_state(params.state);
	qp_attr->path_mtu = ib_mtu_पूर्णांक_to_क्रमागत(params.mtu);
	qp_attr->path_mig_state = IB_MIG_MIGRATED;
	qp_attr->rq_psn = params.rq_psn;
	qp_attr->sq_psn = params.sq_psn;
	qp_attr->dest_qp_num = params.dest_qp;

	qp_attr->qp_access_flags = qedr_to_ib_qp_acc_flags(&params);

	qp_attr->cap.max_send_wr = qp->sq.max_wr;
	qp_attr->cap.max_recv_wr = qp->rq.max_wr;
	qp_attr->cap.max_send_sge = qp->sq.max_sges;
	qp_attr->cap.max_recv_sge = qp->rq.max_sges;
	qp_attr->cap.max_अंतरभूत_data = dev->attr.max_अंतरभूत;
	qp_init_attr->cap = qp_attr->cap;

	qp_attr->ah_attr.type = RDMA_AH_ATTR_TYPE_ROCE;
	rdma_ah_set_grh(&qp_attr->ah_attr, शून्य,
			params.flow_label, qp->sgid_idx,
			params.hop_limit_ttl, params.traffic_class_tos);
	rdma_ah_set_dgid_raw(&qp_attr->ah_attr, &params.dgid.bytes[0]);
	rdma_ah_set_port_num(&qp_attr->ah_attr, 1);
	rdma_ah_set_sl(&qp_attr->ah_attr, 0);
	qp_attr->समयout = params.समयout;
	qp_attr->rnr_retry = params.rnr_retry;
	qp_attr->retry_cnt = params.retry_cnt;
	qp_attr->min_rnr_समयr = params.min_rnr_nak_समयr;
	qp_attr->pkey_index = params.pkey_index;
	qp_attr->port_num = 1;
	rdma_ah_set_path_bits(&qp_attr->ah_attr, 0);
	rdma_ah_set_अटल_rate(&qp_attr->ah_attr, 0);
	qp_attr->alt_pkey_index = 0;
	qp_attr->alt_port_num = 0;
	qp_attr->alt_समयout = 0;
	स_रखो(&qp_attr->alt_ah_attr, 0, माप(qp_attr->alt_ah_attr));

	qp_attr->sq_draining = (params.state == QED_ROCE_QP_STATE_SQD) ? 1 : 0;
	qp_attr->max_dest_rd_atomic = params.max_dest_rd_atomic;
	qp_attr->max_rd_atomic = params.max_rd_atomic;
	qp_attr->en_sqd_async_notअगरy = (params.sqd_async) ? 1 : 0;

	DP_DEBUG(dev, QEDR_MSG_QP, "QEDR_QUERY_QP: max_inline_data=%d\n",
		 qp_attr->cap.max_अंतरभूत_data);

err:
	वापस rc;
पूर्ण

पूर्णांक qedr_destroy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_udata *udata)
अणु
	काष्ठा qedr_qp *qp = get_qedr_qp(ibqp);
	काष्ठा qedr_dev *dev = qp->dev;
	काष्ठा ib_qp_attr attr;
	पूर्णांक attr_mask = 0;

	DP_DEBUG(dev, QEDR_MSG_QP, "destroy qp: destroying %p, qp type=%d\n",
		 qp, qp->qp_type);

	अगर (rdma_protocol_roce(&dev->ibdev, 1)) अणु
		अगर ((qp->state != QED_ROCE_QP_STATE_RESET) &&
		    (qp->state != QED_ROCE_QP_STATE_ERR) &&
		    (qp->state != QED_ROCE_QP_STATE_INIT)) अणु

			attr.qp_state = IB_QPS_ERR;
			attr_mask |= IB_QP_STATE;

			/* Change the QP state to ERROR */
			qedr_modअगरy_qp(ibqp, &attr, attr_mask, शून्य);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* If connection establishment started the WAIT_FOR_CONNECT
		 * bit will be on and we need to Wait क्रम the establishment
		 * to complete beक्रमe destroying the qp.
		 */
		अगर (test_and_set_bit(QEDR_IWARP_CM_WAIT_FOR_CONNECT,
				     &qp->iwarp_cm_flags))
			रुको_क्रम_completion(&qp->iwarp_cm_comp);

		/* If graceful disconnect started, the WAIT_FOR_DISCONNECT
		 * bit will be on, and we need to रुको क्रम the disconnect to
		 * complete beक्रमe continuing. We can use the same completion,
		 * iwarp_cm_comp, since this is the only place that रुकोs क्रम
		 * this completion and it is sequential. In addition,
		 * disconnect can't occur beक्रमe the connection is fully
		 * established, thereक्रमe अगर WAIT_FOR_DISCONNECT is on it
		 * means WAIT_FOR_CONNECT is also on and the completion क्रम
		 * CONNECT alपढ़ोy occurred.
		 */
		अगर (test_and_set_bit(QEDR_IWARP_CM_WAIT_FOR_DISCONNECT,
				     &qp->iwarp_cm_flags))
			रुको_क्रम_completion(&qp->iwarp_cm_comp);
	पूर्ण

	अगर (qp->qp_type == IB_QPT_GSI)
		qedr_destroy_gsi_qp(dev);

	/* We need to हटाओ the entry from the xarray beक्रमe we release the
	 * qp_id to aव्योम a race of the qp_id being पुनः_स्मृतिated and failing
	 * on xa_insert
	 */
	अगर (rdma_protocol_iwarp(&dev->ibdev, 1))
		xa_erase(&dev->qps, qp->qp_id);

	qedr_मुक्त_qp_resources(dev, qp, udata);

	अगर (rdma_protocol_iwarp(&dev->ibdev, 1))
		qedr_iw_qp_rem_ref(&qp->ibqp);
	अन्यथा
		kमुक्त(qp);

	वापस 0;
पूर्ण

पूर्णांक qedr_create_ah(काष्ठा ib_ah *ibah, काष्ठा rdma_ah_init_attr *init_attr,
		   काष्ठा ib_udata *udata)
अणु
	काष्ठा qedr_ah *ah = get_qedr_ah(ibah);

	rdma_copy_ah_attr(&ah->attr, init_attr->ah_attr);

	वापस 0;
पूर्ण

पूर्णांक qedr_destroy_ah(काष्ठा ib_ah *ibah, u32 flags)
अणु
	काष्ठा qedr_ah *ah = get_qedr_ah(ibah);

	rdma_destroy_ah_attr(&ah->attr);
	वापस 0;
पूर्ण

अटल व्योम मुक्त_mr_info(काष्ठा qedr_dev *dev, काष्ठा mr_info *info)
अणु
	काष्ठा qedr_pbl *pbl, *पंचांगp;

	अगर (info->pbl_table)
		list_add_tail(&info->pbl_table->list_entry,
			      &info->मुक्त_pbl_list);

	अगर (!list_empty(&info->inuse_pbl_list))
		list_splice(&info->inuse_pbl_list, &info->मुक्त_pbl_list);

	list_क्रम_each_entry_safe(pbl, पंचांगp, &info->मुक्त_pbl_list, list_entry) अणु
		list_del(&pbl->list_entry);
		qedr_मुक्त_pbl(dev, &info->pbl_info, pbl);
	पूर्ण
पूर्ण

अटल पूर्णांक init_mr_info(काष्ठा qedr_dev *dev, काष्ठा mr_info *info,
			माप_प्रकार page_list_len, bool two_layered)
अणु
	काष्ठा qedr_pbl *पंचांगp;
	पूर्णांक rc;

	INIT_LIST_HEAD(&info->मुक्त_pbl_list);
	INIT_LIST_HEAD(&info->inuse_pbl_list);

	rc = qedr_prepare_pbl_tbl(dev, &info->pbl_info,
				  page_list_len, two_layered);
	अगर (rc)
		जाओ करोne;

	info->pbl_table = qedr_alloc_pbl_tbl(dev, &info->pbl_info, GFP_KERNEL);
	अगर (IS_ERR(info->pbl_table)) अणु
		rc = PTR_ERR(info->pbl_table);
		जाओ करोne;
	पूर्ण

	DP_DEBUG(dev, QEDR_MSG_MR, "pbl_table_pa = %pa\n",
		 &info->pbl_table->pa);

	/* in usual हाल we use 2 PBLs, so we add one to मुक्त
	 * list and allocating another one
	 */
	पंचांगp = qedr_alloc_pbl_tbl(dev, &info->pbl_info, GFP_KERNEL);
	अगर (IS_ERR(पंचांगp)) अणु
		DP_DEBUG(dev, QEDR_MSG_MR, "Extra PBL is not allocated\n");
		जाओ करोne;
	पूर्ण

	list_add_tail(&पंचांगp->list_entry, &info->मुक्त_pbl_list);

	DP_DEBUG(dev, QEDR_MSG_MR, "extra pbl_table_pa = %pa\n", &पंचांगp->pa);

करोne:
	अगर (rc)
		मुक्त_mr_info(dev, info);

	वापस rc;
पूर्ण

काष्ठा ib_mr *qedr_reg_user_mr(काष्ठा ib_pd *ibpd, u64 start, u64 len,
			       u64 usr_addr, पूर्णांक acc, काष्ठा ib_udata *udata)
अणु
	काष्ठा qedr_dev *dev = get_qedr_dev(ibpd->device);
	काष्ठा qedr_mr *mr;
	काष्ठा qedr_pd *pd;
	पूर्णांक rc = -ENOMEM;

	pd = get_qedr_pd(ibpd);
	DP_DEBUG(dev, QEDR_MSG_MR,
		 "qedr_register user mr pd = %d start = %lld, len = %lld, usr_addr = %lld, acc = %d\n",
		 pd->pd_id, start, len, usr_addr, acc);

	अगर (acc & IB_ACCESS_REMOTE_WRITE && !(acc & IB_ACCESS_LOCAL_WRITE))
		वापस ERR_PTR(-EINVAL);

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(rc);

	mr->type = QEDR_MR_USER;

	mr->umem = ib_umem_get(ibpd->device, start, len, acc);
	अगर (IS_ERR(mr->umem)) अणु
		rc = -EFAULT;
		जाओ err0;
	पूर्ण

	rc = init_mr_info(dev, &mr->info,
			  ib_umem_num_dma_blocks(mr->umem, PAGE_SIZE), 1);
	अगर (rc)
		जाओ err1;

	qedr_populate_pbls(dev, mr->umem, mr->info.pbl_table,
			   &mr->info.pbl_info, PAGE_SHIFT);

	rc = dev->ops->rdma_alloc_tid(dev->rdma_ctx, &mr->hw_mr.itid);
	अगर (rc) अणु
		DP_ERR(dev, "roce alloc tid returned an error %d\n", rc);
		जाओ err1;
	पूर्ण

	/* Index only, 18 bit दीर्घ, lkey = itid << 8 | key */
	mr->hw_mr.tid_type = QED_RDMA_TID_REGISTERED_MR;
	mr->hw_mr.key = 0;
	mr->hw_mr.pd = pd->pd_id;
	mr->hw_mr.local_पढ़ो = 1;
	mr->hw_mr.local_ग_लिखो = (acc & IB_ACCESS_LOCAL_WRITE) ? 1 : 0;
	mr->hw_mr.remote_पढ़ो = (acc & IB_ACCESS_REMOTE_READ) ? 1 : 0;
	mr->hw_mr.remote_ग_लिखो = (acc & IB_ACCESS_REMOTE_WRITE) ? 1 : 0;
	mr->hw_mr.remote_atomic = (acc & IB_ACCESS_REMOTE_ATOMIC) ? 1 : 0;
	mr->hw_mr.mw_bind = false;
	mr->hw_mr.pbl_ptr = mr->info.pbl_table[0].pa;
	mr->hw_mr.pbl_two_level = mr->info.pbl_info.two_layered;
	mr->hw_mr.pbl_page_size_log = ilog2(mr->info.pbl_info.pbl_size);
	mr->hw_mr.page_size_log = PAGE_SHIFT;
	mr->hw_mr.length = len;
	mr->hw_mr.vaddr = usr_addr;
	mr->hw_mr.phy_mr = false;
	mr->hw_mr.dma_mr = false;

	rc = dev->ops->rdma_रेजिस्टर_tid(dev->rdma_ctx, &mr->hw_mr);
	अगर (rc) अणु
		DP_ERR(dev, "roce register tid returned an error %d\n", rc);
		जाओ err2;
	पूर्ण

	mr->ibmr.lkey = mr->hw_mr.itid << 8 | mr->hw_mr.key;
	अगर (mr->hw_mr.remote_ग_लिखो || mr->hw_mr.remote_पढ़ो ||
	    mr->hw_mr.remote_atomic)
		mr->ibmr.rkey = mr->hw_mr.itid << 8 | mr->hw_mr.key;

	DP_DEBUG(dev, QEDR_MSG_MR, "register user mr lkey: %x\n",
		 mr->ibmr.lkey);
	वापस &mr->ibmr;

err2:
	dev->ops->rdma_मुक्त_tid(dev->rdma_ctx, mr->hw_mr.itid);
err1:
	qedr_मुक्त_pbl(dev, &mr->info.pbl_info, mr->info.pbl_table);
err0:
	kमुक्त(mr);
	वापस ERR_PTR(rc);
पूर्ण

पूर्णांक qedr_dereg_mr(काष्ठा ib_mr *ib_mr, काष्ठा ib_udata *udata)
अणु
	काष्ठा qedr_mr *mr = get_qedr_mr(ib_mr);
	काष्ठा qedr_dev *dev = get_qedr_dev(ib_mr->device);
	पूर्णांक rc = 0;

	rc = dev->ops->rdma_deरेजिस्टर_tid(dev->rdma_ctx, mr->hw_mr.itid);
	अगर (rc)
		वापस rc;

	dev->ops->rdma_मुक्त_tid(dev->rdma_ctx, mr->hw_mr.itid);

	अगर (mr->type != QEDR_MR_DMA)
		मुक्त_mr_info(dev, &mr->info);

	/* it could be user रेजिस्टरed memory. */
	ib_umem_release(mr->umem);

	kमुक्त(mr);

	वापस rc;
पूर्ण

अटल काष्ठा qedr_mr *__qedr_alloc_mr(काष्ठा ib_pd *ibpd,
				       पूर्णांक max_page_list_len)
अणु
	काष्ठा qedr_pd *pd = get_qedr_pd(ibpd);
	काष्ठा qedr_dev *dev = get_qedr_dev(ibpd->device);
	काष्ठा qedr_mr *mr;
	पूर्णांक rc = -ENOMEM;

	DP_DEBUG(dev, QEDR_MSG_MR,
		 "qedr_alloc_frmr pd = %d max_page_list_len= %d\n", pd->pd_id,
		 max_page_list_len);

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(rc);

	mr->dev = dev;
	mr->type = QEDR_MR_FRMR;

	rc = init_mr_info(dev, &mr->info, max_page_list_len, 1);
	अगर (rc)
		जाओ err0;

	rc = dev->ops->rdma_alloc_tid(dev->rdma_ctx, &mr->hw_mr.itid);
	अगर (rc) अणु
		DP_ERR(dev, "roce alloc tid returned an error %d\n", rc);
		जाओ err0;
	पूर्ण

	/* Index only, 18 bit दीर्घ, lkey = itid << 8 | key */
	mr->hw_mr.tid_type = QED_RDMA_TID_FMR;
	mr->hw_mr.key = 0;
	mr->hw_mr.pd = pd->pd_id;
	mr->hw_mr.local_पढ़ो = 1;
	mr->hw_mr.local_ग_लिखो = 0;
	mr->hw_mr.remote_पढ़ो = 0;
	mr->hw_mr.remote_ग_लिखो = 0;
	mr->hw_mr.remote_atomic = 0;
	mr->hw_mr.mw_bind = false;
	mr->hw_mr.pbl_ptr = 0;
	mr->hw_mr.pbl_two_level = mr->info.pbl_info.two_layered;
	mr->hw_mr.pbl_page_size_log = ilog2(mr->info.pbl_info.pbl_size);
	mr->hw_mr.length = 0;
	mr->hw_mr.vaddr = 0;
	mr->hw_mr.phy_mr = true;
	mr->hw_mr.dma_mr = false;

	rc = dev->ops->rdma_रेजिस्टर_tid(dev->rdma_ctx, &mr->hw_mr);
	अगर (rc) अणु
		DP_ERR(dev, "roce register tid returned an error %d\n", rc);
		जाओ err1;
	पूर्ण

	mr->ibmr.lkey = mr->hw_mr.itid << 8 | mr->hw_mr.key;
	mr->ibmr.rkey = mr->ibmr.lkey;

	DP_DEBUG(dev, QEDR_MSG_MR, "alloc frmr: %x\n", mr->ibmr.lkey);
	वापस mr;

err1:
	dev->ops->rdma_मुक्त_tid(dev->rdma_ctx, mr->hw_mr.itid);
err0:
	kमुक्त(mr);
	वापस ERR_PTR(rc);
पूर्ण

काष्ठा ib_mr *qedr_alloc_mr(काष्ठा ib_pd *ibpd, क्रमागत ib_mr_type mr_type,
			    u32 max_num_sg)
अणु
	काष्ठा qedr_mr *mr;

	अगर (mr_type != IB_MR_TYPE_MEM_REG)
		वापस ERR_PTR(-EINVAL);

	mr = __qedr_alloc_mr(ibpd, max_num_sg);

	अगर (IS_ERR(mr))
		वापस ERR_PTR(-EINVAL);

	वापस &mr->ibmr;
पूर्ण

अटल पूर्णांक qedr_set_page(काष्ठा ib_mr *ibmr, u64 addr)
अणु
	काष्ठा qedr_mr *mr = get_qedr_mr(ibmr);
	काष्ठा qedr_pbl *pbl_table;
	काष्ठा regpair *pbe;
	u32 pbes_in_page;

	अगर (unlikely(mr->npages == mr->info.pbl_info.num_pbes)) अणु
		DP_ERR(mr->dev, "qedr_set_page fails when %d\n", mr->npages);
		वापस -ENOMEM;
	पूर्ण

	DP_DEBUG(mr->dev, QEDR_MSG_MR, "qedr_set_page pages[%d] = 0x%llx\n",
		 mr->npages, addr);

	pbes_in_page = mr->info.pbl_info.pbl_size / माप(u64);
	pbl_table = mr->info.pbl_table + (mr->npages / pbes_in_page);
	pbe = (काष्ठा regpair *)pbl_table->va;
	pbe +=  mr->npages % pbes_in_page;
	pbe->lo = cpu_to_le32((u32)addr);
	pbe->hi = cpu_to_le32((u32)upper_32_bits(addr));

	mr->npages++;

	वापस 0;
पूर्ण

अटल व्योम handle_completed_mrs(काष्ठा qedr_dev *dev, काष्ठा mr_info *info)
अणु
	पूर्णांक work = info->completed - info->completed_handled - 1;

	DP_DEBUG(dev, QEDR_MSG_MR, "Special FMR work = %d\n", work);
	जबतक (work-- > 0 && !list_empty(&info->inuse_pbl_list)) अणु
		काष्ठा qedr_pbl *pbl;

		/* Free all the page list that are possible to be मुक्तd
		 * (all the ones that were invalidated), under the assumption
		 * that अगर an FMR was completed successfully that means that
		 * अगर there was an invalidate operation beक्रमe it also ended
		 */
		pbl = list_first_entry(&info->inuse_pbl_list,
				       काष्ठा qedr_pbl, list_entry);
		list_move_tail(&pbl->list_entry, &info->मुक्त_pbl_list);
		info->completed_handled++;
	पूर्ण
पूर्ण

पूर्णांक qedr_map_mr_sg(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *sg,
		   पूर्णांक sg_nents, अचिन्हित पूर्णांक *sg_offset)
अणु
	काष्ठा qedr_mr *mr = get_qedr_mr(ibmr);

	mr->npages = 0;

	handle_completed_mrs(mr->dev, &mr->info);
	वापस ib_sg_to_pages(ibmr, sg, sg_nents, शून्य, qedr_set_page);
पूर्ण

काष्ठा ib_mr *qedr_get_dma_mr(काष्ठा ib_pd *ibpd, पूर्णांक acc)
अणु
	काष्ठा qedr_dev *dev = get_qedr_dev(ibpd->device);
	काष्ठा qedr_pd *pd = get_qedr_pd(ibpd);
	काष्ठा qedr_mr *mr;
	पूर्णांक rc;

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	mr->type = QEDR_MR_DMA;

	rc = dev->ops->rdma_alloc_tid(dev->rdma_ctx, &mr->hw_mr.itid);
	अगर (rc) अणु
		DP_ERR(dev, "roce alloc tid returned an error %d\n", rc);
		जाओ err1;
	पूर्ण

	/* index only, 18 bit दीर्घ, lkey = itid << 8 | key */
	mr->hw_mr.tid_type = QED_RDMA_TID_REGISTERED_MR;
	mr->hw_mr.pd = pd->pd_id;
	mr->hw_mr.local_पढ़ो = 1;
	mr->hw_mr.local_ग_लिखो = (acc & IB_ACCESS_LOCAL_WRITE) ? 1 : 0;
	mr->hw_mr.remote_पढ़ो = (acc & IB_ACCESS_REMOTE_READ) ? 1 : 0;
	mr->hw_mr.remote_ग_लिखो = (acc & IB_ACCESS_REMOTE_WRITE) ? 1 : 0;
	mr->hw_mr.remote_atomic = (acc & IB_ACCESS_REMOTE_ATOMIC) ? 1 : 0;
	mr->hw_mr.dma_mr = true;

	rc = dev->ops->rdma_रेजिस्टर_tid(dev->rdma_ctx, &mr->hw_mr);
	अगर (rc) अणु
		DP_ERR(dev, "roce register tid returned an error %d\n", rc);
		जाओ err2;
	पूर्ण

	mr->ibmr.lkey = mr->hw_mr.itid << 8 | mr->hw_mr.key;
	अगर (mr->hw_mr.remote_ग_लिखो || mr->hw_mr.remote_पढ़ो ||
	    mr->hw_mr.remote_atomic)
		mr->ibmr.rkey = mr->hw_mr.itid << 8 | mr->hw_mr.key;

	DP_DEBUG(dev, QEDR_MSG_MR, "get dma mr: lkey = %x\n", mr->ibmr.lkey);
	वापस &mr->ibmr;

err2:
	dev->ops->rdma_मुक्त_tid(dev->rdma_ctx, mr->hw_mr.itid);
err1:
	kमुक्त(mr);
	वापस ERR_PTR(rc);
पूर्ण

अटल अंतरभूत पूर्णांक qedr_wq_is_full(काष्ठा qedr_qp_hwq_info *wq)
अणु
	वापस (((wq->prod + 1) % wq->max_wr) == wq->cons);
पूर्ण

अटल पूर्णांक sge_data_len(काष्ठा ib_sge *sg_list, पूर्णांक num_sge)
अणु
	पूर्णांक i, len = 0;

	क्रम (i = 0; i < num_sge; i++)
		len += sg_list[i].length;

	वापस len;
पूर्ण

अटल व्योम swap_wqe_data64(u64 *p)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < QEDR_SQE_ELEMENT_SIZE / माप(u64); i++, p++)
		*p = cpu_to_be64(cpu_to_le64(*p));
पूर्ण

अटल u32 qedr_prepare_sq_अंतरभूत_data(काष्ठा qedr_dev *dev,
				       काष्ठा qedr_qp *qp, u8 *wqe_size,
				       स्थिर काष्ठा ib_send_wr *wr,
				       स्थिर काष्ठा ib_send_wr **bad_wr,
				       u8 *bits, u8 bit)
अणु
	u32 data_size = sge_data_len(wr->sg_list, wr->num_sge);
	अक्षर *seg_prt, *wqe;
	पूर्णांक i, seg_siz;

	अगर (data_size > ROCE_REQ_MAX_INLINE_DATA_SIZE) अणु
		DP_ERR(dev, "Too much inline data in WR: %d\n", data_size);
		*bad_wr = wr;
		वापस 0;
	पूर्ण

	अगर (!data_size)
		वापस data_size;

	*bits |= bit;

	seg_prt = शून्य;
	wqe = शून्य;
	seg_siz = 0;

	/* Copy data अंतरभूत */
	क्रम (i = 0; i < wr->num_sge; i++) अणु
		u32 len = wr->sg_list[i].length;
		व्योम *src = (व्योम *)(uपूर्णांकptr_t)wr->sg_list[i].addr;

		जबतक (len > 0) अणु
			u32 cur;

			/* New segment required */
			अगर (!seg_siz) अणु
				wqe = (अक्षर *)qed_chain_produce(&qp->sq.pbl);
				seg_prt = wqe;
				seg_siz = माप(काष्ठा rdma_sq_common_wqe);
				(*wqe_size)++;
			पूर्ण

			/* Calculate currently allowed length */
			cur = min_t(u32, len, seg_siz);
			स_नकल(seg_prt, src, cur);

			/* Update segment variables */
			seg_prt += cur;
			seg_siz -= cur;

			/* Update sge variables */
			src += cur;
			len -= cur;

			/* Swap fully-completed segments */
			अगर (!seg_siz)
				swap_wqe_data64((u64 *)wqe);
		पूर्ण
	पूर्ण

	/* swap last not completed segment */
	अगर (seg_siz)
		swap_wqe_data64((u64 *)wqe);

	वापस data_size;
पूर्ण

#घोषणा RQ_SGE_SET(sge, vaddr, vlength, vflags)			\
	करो अणु							\
		DMA_REGPAIR_LE(sge->addr, vaddr);		\
		(sge)->length = cpu_to_le32(vlength);		\
		(sge)->flags = cpu_to_le32(vflags);		\
	पूर्ण जबतक (0)

#घोषणा SRQ_HDR_SET(hdr, vwr_id, num_sge)			\
	करो अणु							\
		DMA_REGPAIR_LE(hdr->wr_id, vwr_id);		\
		(hdr)->num_sges = num_sge;			\
	पूर्ण जबतक (0)

#घोषणा SRQ_SGE_SET(sge, vaddr, vlength, vlkey)			\
	करो अणु							\
		DMA_REGPAIR_LE(sge->addr, vaddr);		\
		(sge)->length = cpu_to_le32(vlength);		\
		(sge)->l_key = cpu_to_le32(vlkey);		\
	पूर्ण जबतक (0)

अटल u32 qedr_prepare_sq_sges(काष्ठा qedr_qp *qp, u8 *wqe_size,
				स्थिर काष्ठा ib_send_wr *wr)
अणु
	u32 data_size = 0;
	पूर्णांक i;

	क्रम (i = 0; i < wr->num_sge; i++) अणु
		काष्ठा rdma_sq_sge *sge = qed_chain_produce(&qp->sq.pbl);

		DMA_REGPAIR_LE(sge->addr, wr->sg_list[i].addr);
		sge->l_key = cpu_to_le32(wr->sg_list[i].lkey);
		sge->length = cpu_to_le32(wr->sg_list[i].length);
		data_size += wr->sg_list[i].length;
	पूर्ण

	अगर (wqe_size)
		*wqe_size += wr->num_sge;

	वापस data_size;
पूर्ण

अटल u32 qedr_prepare_sq_rdma_data(काष्ठा qedr_dev *dev,
				     काष्ठा qedr_qp *qp,
				     काष्ठा rdma_sq_rdma_wqe_1st *rwqe,
				     काष्ठा rdma_sq_rdma_wqe_2nd *rwqe2,
				     स्थिर काष्ठा ib_send_wr *wr,
				     स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	rwqe2->r_key = cpu_to_le32(rdma_wr(wr)->rkey);
	DMA_REGPAIR_LE(rwqe2->remote_va, rdma_wr(wr)->remote_addr);

	अगर (wr->send_flags & IB_SEND_INLINE &&
	    (wr->opcode == IB_WR_RDMA_WRITE_WITH_IMM ||
	     wr->opcode == IB_WR_RDMA_WRITE)) अणु
		u8 flags = 0;

		SET_FIELD2(flags, RDMA_SQ_RDMA_WQE_1ST_INLINE_FLG, 1);
		वापस qedr_prepare_sq_अंतरभूत_data(dev, qp, &rwqe->wqe_size, wr,
						   bad_wr, &rwqe->flags, flags);
	पूर्ण

	वापस qedr_prepare_sq_sges(qp, &rwqe->wqe_size, wr);
पूर्ण

अटल u32 qedr_prepare_sq_send_data(काष्ठा qedr_dev *dev,
				     काष्ठा qedr_qp *qp,
				     काष्ठा rdma_sq_send_wqe_1st *swqe,
				     काष्ठा rdma_sq_send_wqe_2st *swqe2,
				     स्थिर काष्ठा ib_send_wr *wr,
				     स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	स_रखो(swqe2, 0, माप(*swqe2));
	अगर (wr->send_flags & IB_SEND_INLINE) अणु
		u8 flags = 0;

		SET_FIELD2(flags, RDMA_SQ_SEND_WQE_INLINE_FLG, 1);
		वापस qedr_prepare_sq_अंतरभूत_data(dev, qp, &swqe->wqe_size, wr,
						   bad_wr, &swqe->flags, flags);
	पूर्ण

	वापस qedr_prepare_sq_sges(qp, &swqe->wqe_size, wr);
पूर्ण

अटल पूर्णांक qedr_prepare_reg(काष्ठा qedr_qp *qp,
			    काष्ठा rdma_sq_fmr_wqe_1st *fwqe1,
			    स्थिर काष्ठा ib_reg_wr *wr)
अणु
	काष्ठा qedr_mr *mr = get_qedr_mr(wr->mr);
	काष्ठा rdma_sq_fmr_wqe_2nd *fwqe2;

	fwqe2 = (काष्ठा rdma_sq_fmr_wqe_2nd *)qed_chain_produce(&qp->sq.pbl);
	fwqe1->addr.hi = upper_32_bits(mr->ibmr.iova);
	fwqe1->addr.lo = lower_32_bits(mr->ibmr.iova);
	fwqe1->l_key = wr->key;

	fwqe2->access_ctrl = 0;

	SET_FIELD2(fwqe2->access_ctrl, RDMA_SQ_FMR_WQE_2ND_REMOTE_READ,
		   !!(wr->access & IB_ACCESS_REMOTE_READ));
	SET_FIELD2(fwqe2->access_ctrl, RDMA_SQ_FMR_WQE_2ND_REMOTE_WRITE,
		   !!(wr->access & IB_ACCESS_REMOTE_WRITE));
	SET_FIELD2(fwqe2->access_ctrl, RDMA_SQ_FMR_WQE_2ND_ENABLE_ATOMIC,
		   !!(wr->access & IB_ACCESS_REMOTE_ATOMIC));
	SET_FIELD2(fwqe2->access_ctrl, RDMA_SQ_FMR_WQE_2ND_LOCAL_READ, 1);
	SET_FIELD2(fwqe2->access_ctrl, RDMA_SQ_FMR_WQE_2ND_LOCAL_WRITE,
		   !!(wr->access & IB_ACCESS_LOCAL_WRITE));
	fwqe2->fmr_ctrl = 0;

	SET_FIELD2(fwqe2->fmr_ctrl, RDMA_SQ_FMR_WQE_2ND_PAGE_SIZE_LOG,
		   ilog2(mr->ibmr.page_size) - 12);

	fwqe2->length_hi = 0;
	fwqe2->length_lo = mr->ibmr.length;
	fwqe2->pbl_addr.hi = upper_32_bits(mr->info.pbl_table->pa);
	fwqe2->pbl_addr.lo = lower_32_bits(mr->info.pbl_table->pa);

	qp->wqe_wr_id[qp->sq.prod].mr = mr;

	वापस 0;
पूर्ण

अटल क्रमागत ib_wc_opcode qedr_ib_to_wc_opcode(क्रमागत ib_wr_opcode opcode)
अणु
	चयन (opcode) अणु
	हाल IB_WR_RDMA_WRITE:
	हाल IB_WR_RDMA_WRITE_WITH_IMM:
		वापस IB_WC_RDMA_WRITE;
	हाल IB_WR_SEND_WITH_IMM:
	हाल IB_WR_SEND:
	हाल IB_WR_SEND_WITH_INV:
		वापस IB_WC_SEND;
	हाल IB_WR_RDMA_READ:
	हाल IB_WR_RDMA_READ_WITH_INV:
		वापस IB_WC_RDMA_READ;
	हाल IB_WR_ATOMIC_CMP_AND_SWP:
		वापस IB_WC_COMP_SWAP;
	हाल IB_WR_ATOMIC_FETCH_AND_ADD:
		वापस IB_WC_FETCH_ADD;
	हाल IB_WR_REG_MR:
		वापस IB_WC_REG_MR;
	हाल IB_WR_LOCAL_INV:
		वापस IB_WC_LOCAL_INV;
	शेष:
		वापस IB_WC_SEND;
	पूर्ण
पूर्ण

अटल अंतरभूत bool qedr_can_post_send(काष्ठा qedr_qp *qp,
				      स्थिर काष्ठा ib_send_wr *wr)
अणु
	पूर्णांक wq_is_full, err_wr, pbl_is_full;
	काष्ठा qedr_dev *dev = qp->dev;

	/* prevent SQ overflow and/or processing of a bad WR */
	err_wr = wr->num_sge > qp->sq.max_sges;
	wq_is_full = qedr_wq_is_full(&qp->sq);
	pbl_is_full = qed_chain_get_elem_left_u32(&qp->sq.pbl) <
		      QEDR_MAX_SQE_ELEMENTS_PER_SQE;
	अगर (wq_is_full || err_wr || pbl_is_full) अणु
		अगर (wq_is_full && !(qp->err_biपंचांगap & QEDR_QP_ERR_SQ_FULL)) अणु
			DP_ERR(dev,
			       "error: WQ is full. Post send on QP %p failed (this error appears only once)\n",
			       qp);
			qp->err_biपंचांगap |= QEDR_QP_ERR_SQ_FULL;
		पूर्ण

		अगर (err_wr && !(qp->err_biपंचांगap & QEDR_QP_ERR_BAD_SR)) अणु
			DP_ERR(dev,
			       "error: WR is bad. Post send on QP %p failed (this error appears only once)\n",
			       qp);
			qp->err_biपंचांगap |= QEDR_QP_ERR_BAD_SR;
		पूर्ण

		अगर (pbl_is_full &&
		    !(qp->err_biपंचांगap & QEDR_QP_ERR_SQ_PBL_FULL)) अणु
			DP_ERR(dev,
			       "error: WQ PBL is full. Post send on QP %p failed (this error appears only once)\n",
			       qp);
			qp->err_biपंचांगap |= QEDR_QP_ERR_SQ_PBL_FULL;
		पूर्ण
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक __qedr_post_send(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
			    स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	काष्ठा qedr_dev *dev = get_qedr_dev(ibqp->device);
	काष्ठा qedr_qp *qp = get_qedr_qp(ibqp);
	काष्ठा rdma_sq_atomic_wqe_1st *awqe1;
	काष्ठा rdma_sq_atomic_wqe_2nd *awqe2;
	काष्ठा rdma_sq_atomic_wqe_3rd *awqe3;
	काष्ठा rdma_sq_send_wqe_2st *swqe2;
	काष्ठा rdma_sq_local_inv_wqe *iwqe;
	काष्ठा rdma_sq_rdma_wqe_2nd *rwqe2;
	काष्ठा rdma_sq_send_wqe_1st *swqe;
	काष्ठा rdma_sq_rdma_wqe_1st *rwqe;
	काष्ठा rdma_sq_fmr_wqe_1st *fwqe1;
	काष्ठा rdma_sq_common_wqe *wqe;
	u32 length;
	पूर्णांक rc = 0;
	bool comp;

	अगर (!qedr_can_post_send(qp, wr)) अणु
		*bad_wr = wr;
		वापस -ENOMEM;
	पूर्ण

	wqe = qed_chain_produce(&qp->sq.pbl);
	qp->wqe_wr_id[qp->sq.prod].संकेतed =
		!!(wr->send_flags & IB_SEND_SIGNALED) || qp->संकेतed;

	wqe->flags = 0;
	SET_FIELD2(wqe->flags, RDMA_SQ_SEND_WQE_SE_FLG,
		   !!(wr->send_flags & IB_SEND_SOLICITED));
	comp = (!!(wr->send_flags & IB_SEND_SIGNALED)) || qp->संकेतed;
	SET_FIELD2(wqe->flags, RDMA_SQ_SEND_WQE_COMP_FLG, comp);
	SET_FIELD2(wqe->flags, RDMA_SQ_SEND_WQE_RD_FENCE_FLG,
		   !!(wr->send_flags & IB_SEND_FENCE));
	wqe->prev_wqe_size = qp->prev_wqe_size;

	qp->wqe_wr_id[qp->sq.prod].opcode = qedr_ib_to_wc_opcode(wr->opcode);

	चयन (wr->opcode) अणु
	हाल IB_WR_SEND_WITH_IMM:
		अगर (unlikely(rdma_protocol_iwarp(&dev->ibdev, 1))) अणु
			rc = -EINVAL;
			*bad_wr = wr;
			अवरोध;
		पूर्ण
		wqe->req_type = RDMA_SQ_REQ_TYPE_SEND_WITH_IMM;
		swqe = (काष्ठा rdma_sq_send_wqe_1st *)wqe;
		swqe->wqe_size = 2;
		swqe2 = qed_chain_produce(&qp->sq.pbl);

		swqe->inv_key_or_imm_data = cpu_to_le32(be32_to_cpu(wr->ex.imm_data));
		length = qedr_prepare_sq_send_data(dev, qp, swqe, swqe2,
						   wr, bad_wr);
		swqe->length = cpu_to_le32(length);
		qp->wqe_wr_id[qp->sq.prod].wqe_size = swqe->wqe_size;
		qp->prev_wqe_size = swqe->wqe_size;
		qp->wqe_wr_id[qp->sq.prod].bytes_len = swqe->length;
		अवरोध;
	हाल IB_WR_SEND:
		wqe->req_type = RDMA_SQ_REQ_TYPE_SEND;
		swqe = (काष्ठा rdma_sq_send_wqe_1st *)wqe;

		swqe->wqe_size = 2;
		swqe2 = qed_chain_produce(&qp->sq.pbl);
		length = qedr_prepare_sq_send_data(dev, qp, swqe, swqe2,
						   wr, bad_wr);
		swqe->length = cpu_to_le32(length);
		qp->wqe_wr_id[qp->sq.prod].wqe_size = swqe->wqe_size;
		qp->prev_wqe_size = swqe->wqe_size;
		qp->wqe_wr_id[qp->sq.prod].bytes_len = swqe->length;
		अवरोध;
	हाल IB_WR_SEND_WITH_INV:
		wqe->req_type = RDMA_SQ_REQ_TYPE_SEND_WITH_INVALIDATE;
		swqe = (काष्ठा rdma_sq_send_wqe_1st *)wqe;
		swqe2 = qed_chain_produce(&qp->sq.pbl);
		swqe->wqe_size = 2;
		swqe->inv_key_or_imm_data = cpu_to_le32(wr->ex.invalidate_rkey);
		length = qedr_prepare_sq_send_data(dev, qp, swqe, swqe2,
						   wr, bad_wr);
		swqe->length = cpu_to_le32(length);
		qp->wqe_wr_id[qp->sq.prod].wqe_size = swqe->wqe_size;
		qp->prev_wqe_size = swqe->wqe_size;
		qp->wqe_wr_id[qp->sq.prod].bytes_len = swqe->length;
		अवरोध;

	हाल IB_WR_RDMA_WRITE_WITH_IMM:
		अगर (unlikely(rdma_protocol_iwarp(&dev->ibdev, 1))) अणु
			rc = -EINVAL;
			*bad_wr = wr;
			अवरोध;
		पूर्ण
		wqe->req_type = RDMA_SQ_REQ_TYPE_RDMA_WR_WITH_IMM;
		rwqe = (काष्ठा rdma_sq_rdma_wqe_1st *)wqe;

		rwqe->wqe_size = 2;
		rwqe->imm_data = htonl(cpu_to_le32(wr->ex.imm_data));
		rwqe2 = qed_chain_produce(&qp->sq.pbl);
		length = qedr_prepare_sq_rdma_data(dev, qp, rwqe, rwqe2,
						   wr, bad_wr);
		rwqe->length = cpu_to_le32(length);
		qp->wqe_wr_id[qp->sq.prod].wqe_size = rwqe->wqe_size;
		qp->prev_wqe_size = rwqe->wqe_size;
		qp->wqe_wr_id[qp->sq.prod].bytes_len = rwqe->length;
		अवरोध;
	हाल IB_WR_RDMA_WRITE:
		wqe->req_type = RDMA_SQ_REQ_TYPE_RDMA_WR;
		rwqe = (काष्ठा rdma_sq_rdma_wqe_1st *)wqe;

		rwqe->wqe_size = 2;
		rwqe2 = qed_chain_produce(&qp->sq.pbl);
		length = qedr_prepare_sq_rdma_data(dev, qp, rwqe, rwqe2,
						   wr, bad_wr);
		rwqe->length = cpu_to_le32(length);
		qp->wqe_wr_id[qp->sq.prod].wqe_size = rwqe->wqe_size;
		qp->prev_wqe_size = rwqe->wqe_size;
		qp->wqe_wr_id[qp->sq.prod].bytes_len = rwqe->length;
		अवरोध;
	हाल IB_WR_RDMA_READ_WITH_INV:
		SET_FIELD2(wqe->flags, RDMA_SQ_RDMA_WQE_1ST_READ_INV_FLG, 1);
		fallthrough;	/* same is identical to RDMA READ */

	हाल IB_WR_RDMA_READ:
		wqe->req_type = RDMA_SQ_REQ_TYPE_RDMA_RD;
		rwqe = (काष्ठा rdma_sq_rdma_wqe_1st *)wqe;

		rwqe->wqe_size = 2;
		rwqe2 = qed_chain_produce(&qp->sq.pbl);
		length = qedr_prepare_sq_rdma_data(dev, qp, rwqe, rwqe2,
						   wr, bad_wr);
		rwqe->length = cpu_to_le32(length);
		qp->wqe_wr_id[qp->sq.prod].wqe_size = rwqe->wqe_size;
		qp->prev_wqe_size = rwqe->wqe_size;
		qp->wqe_wr_id[qp->sq.prod].bytes_len = rwqe->length;
		अवरोध;

	हाल IB_WR_ATOMIC_CMP_AND_SWP:
	हाल IB_WR_ATOMIC_FETCH_AND_ADD:
		awqe1 = (काष्ठा rdma_sq_atomic_wqe_1st *)wqe;
		awqe1->wqe_size = 4;

		awqe2 = qed_chain_produce(&qp->sq.pbl);
		DMA_REGPAIR_LE(awqe2->remote_va, atomic_wr(wr)->remote_addr);
		awqe2->r_key = cpu_to_le32(atomic_wr(wr)->rkey);

		awqe3 = qed_chain_produce(&qp->sq.pbl);

		अगर (wr->opcode == IB_WR_ATOMIC_FETCH_AND_ADD) अणु
			wqe->req_type = RDMA_SQ_REQ_TYPE_ATOMIC_ADD;
			DMA_REGPAIR_LE(awqe3->swap_data,
				       atomic_wr(wr)->compare_add);
		पूर्ण अन्यथा अणु
			wqe->req_type = RDMA_SQ_REQ_TYPE_ATOMIC_CMP_AND_SWAP;
			DMA_REGPAIR_LE(awqe3->swap_data,
				       atomic_wr(wr)->swap);
			DMA_REGPAIR_LE(awqe3->cmp_data,
				       atomic_wr(wr)->compare_add);
		पूर्ण

		qedr_prepare_sq_sges(qp, शून्य, wr);

		qp->wqe_wr_id[qp->sq.prod].wqe_size = awqe1->wqe_size;
		qp->prev_wqe_size = awqe1->wqe_size;
		अवरोध;

	हाल IB_WR_LOCAL_INV:
		iwqe = (काष्ठा rdma_sq_local_inv_wqe *)wqe;
		iwqe->wqe_size = 1;

		iwqe->req_type = RDMA_SQ_REQ_TYPE_LOCAL_INVALIDATE;
		iwqe->inv_l_key = wr->ex.invalidate_rkey;
		qp->wqe_wr_id[qp->sq.prod].wqe_size = iwqe->wqe_size;
		qp->prev_wqe_size = iwqe->wqe_size;
		अवरोध;
	हाल IB_WR_REG_MR:
		DP_DEBUG(dev, QEDR_MSG_CQ, "REG_MR\n");
		wqe->req_type = RDMA_SQ_REQ_TYPE_FAST_MR;
		fwqe1 = (काष्ठा rdma_sq_fmr_wqe_1st *)wqe;
		fwqe1->wqe_size = 2;

		rc = qedr_prepare_reg(qp, fwqe1, reg_wr(wr));
		अगर (rc) अणु
			DP_ERR(dev, "IB_REG_MR failed rc=%d\n", rc);
			*bad_wr = wr;
			अवरोध;
		पूर्ण

		qp->wqe_wr_id[qp->sq.prod].wqe_size = fwqe1->wqe_size;
		qp->prev_wqe_size = fwqe1->wqe_size;
		अवरोध;
	शेष:
		DP_ERR(dev, "invalid opcode 0x%x!\n", wr->opcode);
		rc = -EINVAL;
		*bad_wr = wr;
		अवरोध;
	पूर्ण

	अगर (*bad_wr) अणु
		u16 value;

		/* Restore prod to its position beक्रमe
		 * this WR was processed
		 */
		value = le16_to_cpu(qp->sq.db_data.data.value);
		qed_chain_set_prod(&qp->sq.pbl, value, wqe);

		/* Restore prev_wqe_size */
		qp->prev_wqe_size = wqe->prev_wqe_size;
		rc = -EINVAL;
		DP_ERR(dev, "POST SEND FAILED\n");
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक qedr_post_send(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
		   स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	काष्ठा qedr_dev *dev = get_qedr_dev(ibqp->device);
	काष्ठा qedr_qp *qp = get_qedr_qp(ibqp);
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	*bad_wr = शून्य;

	अगर (qp->qp_type == IB_QPT_GSI)
		वापस qedr_gsi_post_send(ibqp, wr, bad_wr);

	spin_lock_irqsave(&qp->q_lock, flags);

	अगर (rdma_protocol_roce(&dev->ibdev, 1)) अणु
		अगर ((qp->state != QED_ROCE_QP_STATE_RTS) &&
		    (qp->state != QED_ROCE_QP_STATE_ERR) &&
		    (qp->state != QED_ROCE_QP_STATE_SQD)) अणु
			spin_unlock_irqrestore(&qp->q_lock, flags);
			*bad_wr = wr;
			DP_DEBUG(dev, QEDR_MSG_CQ,
				 "QP in wrong state! QP icid=0x%x state %d\n",
				 qp->icid, qp->state);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	जबतक (wr) अणु
		rc = __qedr_post_send(ibqp, wr, bad_wr);
		अगर (rc)
			अवरोध;

		qp->wqe_wr_id[qp->sq.prod].wr_id = wr->wr_id;

		qedr_inc_sw_prod(&qp->sq);

		qp->sq.db_data.data.value++;

		wr = wr->next;
	पूर्ण

	/* Trigger करोorbell
	 * If there was a failure in the first WR then it will be triggered in
	 * vane. However this is not harmful (as दीर्घ as the producer value is
	 * unchanged). For perक्रमmance reasons we aव्योम checking क्रम this
	 * redundant करोorbell.
	 *
	 * qp->wqe_wr_id is accessed during qedr_poll_cq, as
	 * soon as we give the करोorbell, we could get a completion
	 * क्रम this wr, thereक्रमe we need to make sure that the
	 * memory is updated beक्रमe giving the करोorbell.
	 * During qedr_poll_cq, rmb is called beक्रमe accessing the
	 * cqe. This covers क्रम the smp_rmb as well.
	 */
	smp_wmb();
	ग_लिखोl(qp->sq.db_data.raw, qp->sq.db);

	spin_unlock_irqrestore(&qp->q_lock, flags);

	वापस rc;
पूर्ण

अटल u32 qedr_srq_elem_left(काष्ठा qedr_srq_hwq_info *hw_srq)
अणु
	u32 used;

	/* Calculate number of elements used based on producer
	 * count and consumer count and subtract it from max
	 * work request supported so that we get elements left.
	 */
	used = hw_srq->wr_prod_cnt - (u32)atomic_पढ़ो(&hw_srq->wr_cons_cnt);

	वापस hw_srq->max_wr - used;
पूर्ण

पूर्णांक qedr_post_srq_recv(काष्ठा ib_srq *ibsrq, स्थिर काष्ठा ib_recv_wr *wr,
		       स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा qedr_srq *srq = get_qedr_srq(ibsrq);
	काष्ठा qedr_srq_hwq_info *hw_srq;
	काष्ठा qedr_dev *dev = srq->dev;
	काष्ठा qed_chain *pbl;
	अचिन्हित दीर्घ flags;
	पूर्णांक status = 0;
	u32 num_sge;

	spin_lock_irqsave(&srq->lock, flags);

	hw_srq = &srq->hw_srq;
	pbl = &srq->hw_srq.pbl;
	जबतक (wr) अणु
		काष्ठा rdma_srq_wqe_header *hdr;
		पूर्णांक i;

		अगर (!qedr_srq_elem_left(hw_srq) ||
		    wr->num_sge > srq->hw_srq.max_sges) अणु
			DP_ERR(dev, "Can't post WR  (%d,%d) || (%d > %d)\n",
			       hw_srq->wr_prod_cnt,
			       atomic_पढ़ो(&hw_srq->wr_cons_cnt),
			       wr->num_sge, srq->hw_srq.max_sges);
			status = -ENOMEM;
			*bad_wr = wr;
			अवरोध;
		पूर्ण

		hdr = qed_chain_produce(pbl);
		num_sge = wr->num_sge;
		/* Set number of sge and work request id in header */
		SRQ_HDR_SET(hdr, wr->wr_id, num_sge);

		srq->hw_srq.wr_prod_cnt++;
		hw_srq->wqe_prod++;
		hw_srq->sge_prod++;

		DP_DEBUG(dev, QEDR_MSG_SRQ,
			 "SRQ WR: SGEs: %d with wr_id[%d] = %llx\n",
			 wr->num_sge, hw_srq->wqe_prod, wr->wr_id);

		क्रम (i = 0; i < wr->num_sge; i++) अणु
			काष्ठा rdma_srq_sge *srq_sge = qed_chain_produce(pbl);

			/* Set SGE length, lkey and address */
			SRQ_SGE_SET(srq_sge, wr->sg_list[i].addr,
				    wr->sg_list[i].length, wr->sg_list[i].lkey);

			DP_DEBUG(dev, QEDR_MSG_SRQ,
				 "[%d]: len %d key %x addr %x:%x\n",
				 i, srq_sge->length, srq_sge->l_key,
				 srq_sge->addr.hi, srq_sge->addr.lo);
			hw_srq->sge_prod++;
		पूर्ण

		/* Update WQE and SGE inक्रमmation beक्रमe
		 * updating producer.
		 */
		dma_wmb();

		/* SRQ producer is 8 bytes. Need to update SGE producer index
		 * in first 4 bytes and need to update WQE producer in
		 * next 4 bytes.
		 */
		srq->hw_srq.virt_prod_pair_addr->sge_prod = cpu_to_le32(hw_srq->sge_prod);
		/* Make sure sge producer is updated first */
		dma_wmb();
		srq->hw_srq.virt_prod_pair_addr->wqe_prod = cpu_to_le32(hw_srq->wqe_prod);

		wr = wr->next;
	पूर्ण

	DP_DEBUG(dev, QEDR_MSG_SRQ, "POST: Elements in S-RQ: %d\n",
		 qed_chain_get_elem_left(pbl));
	spin_unlock_irqrestore(&srq->lock, flags);

	वापस status;
पूर्ण

पूर्णांक qedr_post_recv(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_recv_wr *wr,
		   स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा qedr_qp *qp = get_qedr_qp(ibqp);
	काष्ठा qedr_dev *dev = qp->dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक status = 0;

	अगर (qp->qp_type == IB_QPT_GSI)
		वापस qedr_gsi_post_recv(ibqp, wr, bad_wr);

	spin_lock_irqsave(&qp->q_lock, flags);

	अगर (qp->state == QED_ROCE_QP_STATE_RESET) अणु
		spin_unlock_irqrestore(&qp->q_lock, flags);
		*bad_wr = wr;
		वापस -EINVAL;
	पूर्ण

	जबतक (wr) अणु
		पूर्णांक i;

		अगर (qed_chain_get_elem_left_u32(&qp->rq.pbl) <
		    QEDR_MAX_RQE_ELEMENTS_PER_RQE ||
		    wr->num_sge > qp->rq.max_sges) अणु
			DP_ERR(dev, "Can't post WR  (%d < %d) || (%d > %d)\n",
			       qed_chain_get_elem_left_u32(&qp->rq.pbl),
			       QEDR_MAX_RQE_ELEMENTS_PER_RQE, wr->num_sge,
			       qp->rq.max_sges);
			status = -ENOMEM;
			*bad_wr = wr;
			अवरोध;
		पूर्ण
		क्रम (i = 0; i < wr->num_sge; i++) अणु
			u32 flags = 0;
			काष्ठा rdma_rq_sge *rqe =
			    qed_chain_produce(&qp->rq.pbl);

			/* First one must include the number
			 * of SGE in the list
			 */
			अगर (!i)
				SET_FIELD(flags, RDMA_RQ_SGE_NUM_SGES,
					  wr->num_sge);

			SET_FIELD(flags, RDMA_RQ_SGE_L_KEY_LO,
				  wr->sg_list[i].lkey);

			RQ_SGE_SET(rqe, wr->sg_list[i].addr,
				   wr->sg_list[i].length, flags);
		पूर्ण

		/* Special हाल of no sges. FW requires between 1-4 sges...
		 * in this हाल we need to post 1 sge with length zero. this is
		 * because rdma ग_लिखो with immediate consumes an RQ.
		 */
		अगर (!wr->num_sge) अणु
			u32 flags = 0;
			काष्ठा rdma_rq_sge *rqe =
			    qed_chain_produce(&qp->rq.pbl);

			/* First one must include the number
			 * of SGE in the list
			 */
			SET_FIELD(flags, RDMA_RQ_SGE_L_KEY_LO, 0);
			SET_FIELD(flags, RDMA_RQ_SGE_NUM_SGES, 1);

			RQ_SGE_SET(rqe, 0, 0, flags);
			i = 1;
		पूर्ण

		qp->rqe_wr_id[qp->rq.prod].wr_id = wr->wr_id;
		qp->rqe_wr_id[qp->rq.prod].wqe_size = i;

		qedr_inc_sw_prod(&qp->rq);

		/* qp->rqe_wr_id is accessed during qedr_poll_cq, as
		 * soon as we give the करोorbell, we could get a completion
		 * क्रम this wr, thereक्रमe we need to make sure that the
		 * memory is update beक्रमe giving the करोorbell.
		 * During qedr_poll_cq, rmb is called beक्रमe accessing the
		 * cqe. This covers क्रम the smp_rmb as well.
		 */
		smp_wmb();

		qp->rq.db_data.data.value++;

		ग_लिखोl(qp->rq.db_data.raw, qp->rq.db);

		अगर (rdma_protocol_iwarp(&dev->ibdev, 1)) अणु
			ग_लिखोl(qp->rq.iwarp_db2_data.raw, qp->rq.iwarp_db2);
		पूर्ण

		wr = wr->next;
	पूर्ण

	spin_unlock_irqrestore(&qp->q_lock, flags);

	वापस status;
पूर्ण

अटल पूर्णांक is_valid_cqe(काष्ठा qedr_cq *cq, जोड़ rdma_cqe *cqe)
अणु
	काष्ठा rdma_cqe_requester *resp_cqe = &cqe->req;

	वापस (resp_cqe->flags & RDMA_CQE_REQUESTER_TOGGLE_BIT_MASK) ==
		cq->pbl_toggle;
पूर्ण

अटल काष्ठा qedr_qp *cqe_get_qp(जोड़ rdma_cqe *cqe)
अणु
	काष्ठा rdma_cqe_requester *resp_cqe = &cqe->req;
	काष्ठा qedr_qp *qp;

	qp = (काष्ठा qedr_qp *)(uपूर्णांकptr_t)HILO_GEN(resp_cqe->qp_handle.hi,
						   resp_cqe->qp_handle.lo,
						   u64);
	वापस qp;
पूर्ण

अटल क्रमागत rdma_cqe_type cqe_get_type(जोड़ rdma_cqe *cqe)
अणु
	काष्ठा rdma_cqe_requester *resp_cqe = &cqe->req;

	वापस GET_FIELD(resp_cqe->flags, RDMA_CQE_REQUESTER_TYPE);
पूर्ण

/* Return latest CQE (needs processing) */
अटल जोड़ rdma_cqe *get_cqe(काष्ठा qedr_cq *cq)
अणु
	वापस cq->latest_cqe;
पूर्ण

/* In fmr we need to increase the number of fmr completed counter क्रम the fmr
 * algorithm determining whether we can मुक्त a pbl or not.
 * we need to perक्रमm this whether the work request was संकेतed or not. क्रम
 * this purpose we call this function from the condition that checks अगर a wr
 * should be skipped, to make sure we करोn't miss it ( possibly this fmr
 * operation was not संकेतted)
 */
अटल अंतरभूत व्योम qedr_chk_अगर_fmr(काष्ठा qedr_qp *qp)
अणु
	अगर (qp->wqe_wr_id[qp->sq.cons].opcode == IB_WC_REG_MR)
		qp->wqe_wr_id[qp->sq.cons].mr->info.completed++;
पूर्ण

अटल पूर्णांक process_req(काष्ठा qedr_dev *dev, काष्ठा qedr_qp *qp,
		       काष्ठा qedr_cq *cq, पूर्णांक num_entries,
		       काष्ठा ib_wc *wc, u16 hw_cons, क्रमागत ib_wc_status status,
		       पूर्णांक क्रमce)
अणु
	u16 cnt = 0;

	जबतक (num_entries && qp->sq.wqe_cons != hw_cons) अणु
		अगर (!qp->wqe_wr_id[qp->sq.cons].संकेतed && !क्रमce) अणु
			qedr_chk_अगर_fmr(qp);
			/* skip WC */
			जाओ next_cqe;
		पूर्ण

		/* fill WC */
		wc->status = status;
		wc->venकरोr_err = 0;
		wc->wc_flags = 0;
		wc->src_qp = qp->id;
		wc->qp = &qp->ibqp;

		wc->wr_id = qp->wqe_wr_id[qp->sq.cons].wr_id;
		wc->opcode = qp->wqe_wr_id[qp->sq.cons].opcode;

		चयन (wc->opcode) अणु
		हाल IB_WC_RDMA_WRITE:
			wc->byte_len = qp->wqe_wr_id[qp->sq.cons].bytes_len;
			अवरोध;
		हाल IB_WC_COMP_SWAP:
		हाल IB_WC_FETCH_ADD:
			wc->byte_len = 8;
			अवरोध;
		हाल IB_WC_REG_MR:
			qp->wqe_wr_id[qp->sq.cons].mr->info.completed++;
			अवरोध;
		हाल IB_WC_RDMA_READ:
		हाल IB_WC_SEND:
			wc->byte_len = qp->wqe_wr_id[qp->sq.cons].bytes_len;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		num_entries--;
		wc++;
		cnt++;
next_cqe:
		जबतक (qp->wqe_wr_id[qp->sq.cons].wqe_size--)
			qed_chain_consume(&qp->sq.pbl);
		qedr_inc_sw_cons(&qp->sq);
	पूर्ण

	वापस cnt;
पूर्ण

अटल पूर्णांक qedr_poll_cq_req(काष्ठा qedr_dev *dev,
			    काष्ठा qedr_qp *qp, काष्ठा qedr_cq *cq,
			    पूर्णांक num_entries, काष्ठा ib_wc *wc,
			    काष्ठा rdma_cqe_requester *req)
अणु
	पूर्णांक cnt = 0;

	चयन (req->status) अणु
	हाल RDMA_CQE_REQ_STS_OK:
		cnt = process_req(dev, qp, cq, num_entries, wc, req->sq_cons,
				  IB_WC_SUCCESS, 0);
		अवरोध;
	हाल RDMA_CQE_REQ_STS_WORK_REQUEST_FLUSHED_ERR:
		अगर (qp->state != QED_ROCE_QP_STATE_ERR)
			DP_DEBUG(dev, QEDR_MSG_CQ,
				 "Error: POLL CQ with RDMA_CQE_REQ_STS_WORK_REQUEST_FLUSHED_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				 cq->icid, qp->icid);
		cnt = process_req(dev, qp, cq, num_entries, wc, req->sq_cons,
				  IB_WC_WR_FLUSH_ERR, 1);
		अवरोध;
	शेष:
		/* process all WQE beक्रमe the cosumer */
		qp->state = QED_ROCE_QP_STATE_ERR;
		cnt = process_req(dev, qp, cq, num_entries, wc,
				  req->sq_cons - 1, IB_WC_SUCCESS, 0);
		wc += cnt;
		/* अगर we have extra WC fill it with actual error info */
		अगर (cnt < num_entries) अणु
			क्रमागत ib_wc_status wc_status;

			चयन (req->status) अणु
			हाल RDMA_CQE_REQ_STS_BAD_RESPONSE_ERR:
				DP_ERR(dev,
				       "Error: POLL CQ with RDMA_CQE_REQ_STS_BAD_RESPONSE_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_BAD_RESP_ERR;
				अवरोध;
			हाल RDMA_CQE_REQ_STS_LOCAL_LENGTH_ERR:
				DP_ERR(dev,
				       "Error: POLL CQ with RDMA_CQE_REQ_STS_LOCAL_LENGTH_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_LOC_LEN_ERR;
				अवरोध;
			हाल RDMA_CQE_REQ_STS_LOCAL_QP_OPERATION_ERR:
				DP_ERR(dev,
				       "Error: POLL CQ with RDMA_CQE_REQ_STS_LOCAL_QP_OPERATION_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_LOC_QP_OP_ERR;
				अवरोध;
			हाल RDMA_CQE_REQ_STS_LOCAL_PROTECTION_ERR:
				DP_ERR(dev,
				       "Error: POLL CQ with RDMA_CQE_REQ_STS_LOCAL_PROTECTION_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_LOC_PROT_ERR;
				अवरोध;
			हाल RDMA_CQE_REQ_STS_MEMORY_MGT_OPERATION_ERR:
				DP_ERR(dev,
				       "Error: POLL CQ with RDMA_CQE_REQ_STS_MEMORY_MGT_OPERATION_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_MW_BIND_ERR;
				अवरोध;
			हाल RDMA_CQE_REQ_STS_REMOTE_INVALID_REQUEST_ERR:
				DP_ERR(dev,
				       "Error: POLL CQ with RDMA_CQE_REQ_STS_REMOTE_INVALID_REQUEST_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_REM_INV_REQ_ERR;
				अवरोध;
			हाल RDMA_CQE_REQ_STS_REMOTE_ACCESS_ERR:
				DP_ERR(dev,
				       "Error: POLL CQ with RDMA_CQE_REQ_STS_REMOTE_ACCESS_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_REM_ACCESS_ERR;
				अवरोध;
			हाल RDMA_CQE_REQ_STS_REMOTE_OPERATION_ERR:
				DP_ERR(dev,
				       "Error: POLL CQ with RDMA_CQE_REQ_STS_REMOTE_OPERATION_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_REM_OP_ERR;
				अवरोध;
			हाल RDMA_CQE_REQ_STS_RNR_NAK_RETRY_CNT_ERR:
				DP_ERR(dev,
				       "Error: POLL CQ with RDMA_CQE_REQ_STS_RNR_NAK_RETRY_CNT_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_RNR_RETRY_EXC_ERR;
				अवरोध;
			हाल RDMA_CQE_REQ_STS_TRANSPORT_RETRY_CNT_ERR:
				DP_ERR(dev,
				       "Error: POLL CQ with ROCE_CQE_REQ_STS_TRANSPORT_RETRY_CNT_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_RETRY_EXC_ERR;
				अवरोध;
			शेष:
				DP_ERR(dev,
				       "Error: POLL CQ with IB_WC_GENERAL_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_GENERAL_ERR;
			पूर्ण
			cnt += process_req(dev, qp, cq, 1, wc, req->sq_cons,
					   wc_status, 1);
		पूर्ण
	पूर्ण

	वापस cnt;
पूर्ण

अटल अंतरभूत पूर्णांक qedr_cqe_resp_status_to_ib(u8 status)
अणु
	चयन (status) अणु
	हाल RDMA_CQE_RESP_STS_LOCAL_ACCESS_ERR:
		वापस IB_WC_LOC_ACCESS_ERR;
	हाल RDMA_CQE_RESP_STS_LOCAL_LENGTH_ERR:
		वापस IB_WC_LOC_LEN_ERR;
	हाल RDMA_CQE_RESP_STS_LOCAL_QP_OPERATION_ERR:
		वापस IB_WC_LOC_QP_OP_ERR;
	हाल RDMA_CQE_RESP_STS_LOCAL_PROTECTION_ERR:
		वापस IB_WC_LOC_PROT_ERR;
	हाल RDMA_CQE_RESP_STS_MEMORY_MGT_OPERATION_ERR:
		वापस IB_WC_MW_BIND_ERR;
	हाल RDMA_CQE_RESP_STS_REMOTE_INVALID_REQUEST_ERR:
		वापस IB_WC_REM_INV_RD_REQ_ERR;
	हाल RDMA_CQE_RESP_STS_OK:
		वापस IB_WC_SUCCESS;
	शेष:
		वापस IB_WC_GENERAL_ERR;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक qedr_set_ok_cqe_resp_wc(काष्ठा rdma_cqe_responder *resp,
					  काष्ठा ib_wc *wc)
अणु
	wc->status = IB_WC_SUCCESS;
	wc->byte_len = le32_to_cpu(resp->length);

	अगर (resp->flags & QEDR_RESP_IMM) अणु
		wc->ex.imm_data = cpu_to_be32(le32_to_cpu(resp->imm_data_or_inv_r_Key));
		wc->wc_flags |= IB_WC_WITH_IMM;

		अगर (resp->flags & QEDR_RESP_RDMA)
			wc->opcode = IB_WC_RECV_RDMA_WITH_IMM;

		अगर (resp->flags & QEDR_RESP_INV)
			वापस -EINVAL;

	पूर्ण अन्यथा अगर (resp->flags & QEDR_RESP_INV) अणु
		wc->ex.imm_data = le32_to_cpu(resp->imm_data_or_inv_r_Key);
		wc->wc_flags |= IB_WC_WITH_INVALIDATE;

		अगर (resp->flags & QEDR_RESP_RDMA)
			वापस -EINVAL;

	पूर्ण अन्यथा अगर (resp->flags & QEDR_RESP_RDMA) अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __process_resp_one(काष्ठा qedr_dev *dev, काष्ठा qedr_qp *qp,
			       काष्ठा qedr_cq *cq, काष्ठा ib_wc *wc,
			       काष्ठा rdma_cqe_responder *resp, u64 wr_id)
अणु
	/* Must fill fields beक्रमe qedr_set_ok_cqe_resp_wc() */
	wc->opcode = IB_WC_RECV;
	wc->wc_flags = 0;

	अगर (likely(resp->status == RDMA_CQE_RESP_STS_OK)) अणु
		अगर (qedr_set_ok_cqe_resp_wc(resp, wc))
			DP_ERR(dev,
			       "CQ %p (icid=%d) has invalid CQE responder flags=0x%x\n",
			       cq, cq->icid, resp->flags);

	पूर्ण अन्यथा अणु
		wc->status = qedr_cqe_resp_status_to_ib(resp->status);
		अगर (wc->status == IB_WC_GENERAL_ERR)
			DP_ERR(dev,
			       "CQ %p (icid=%d) contains an invalid CQE status %d\n",
			       cq, cq->icid, resp->status);
	पूर्ण

	/* Fill the rest of the WC */
	wc->venकरोr_err = 0;
	wc->src_qp = qp->id;
	wc->qp = &qp->ibqp;
	wc->wr_id = wr_id;
पूर्ण

अटल पूर्णांक process_resp_one_srq(काष्ठा qedr_dev *dev, काष्ठा qedr_qp *qp,
				काष्ठा qedr_cq *cq, काष्ठा ib_wc *wc,
				काष्ठा rdma_cqe_responder *resp)
अणु
	काष्ठा qedr_srq *srq = qp->srq;
	u64 wr_id;

	wr_id = HILO_GEN(le32_to_cpu(resp->srq_wr_id.hi),
			 le32_to_cpu(resp->srq_wr_id.lo), u64);

	अगर (resp->status == RDMA_CQE_RESP_STS_WORK_REQUEST_FLUSHED_ERR) अणु
		wc->status = IB_WC_WR_FLUSH_ERR;
		wc->venकरोr_err = 0;
		wc->wr_id = wr_id;
		wc->byte_len = 0;
		wc->src_qp = qp->id;
		wc->qp = &qp->ibqp;
		wc->wr_id = wr_id;
	पूर्ण अन्यथा अणु
		__process_resp_one(dev, qp, cq, wc, resp, wr_id);
	पूर्ण
	atomic_inc(&srq->hw_srq.wr_cons_cnt);

	वापस 1;
पूर्ण
अटल पूर्णांक process_resp_one(काष्ठा qedr_dev *dev, काष्ठा qedr_qp *qp,
			    काष्ठा qedr_cq *cq, काष्ठा ib_wc *wc,
			    काष्ठा rdma_cqe_responder *resp)
अणु
	u64 wr_id = qp->rqe_wr_id[qp->rq.cons].wr_id;

	__process_resp_one(dev, qp, cq, wc, resp, wr_id);

	जबतक (qp->rqe_wr_id[qp->rq.cons].wqe_size--)
		qed_chain_consume(&qp->rq.pbl);
	qedr_inc_sw_cons(&qp->rq);

	वापस 1;
पूर्ण

अटल पूर्णांक process_resp_flush(काष्ठा qedr_qp *qp, काष्ठा qedr_cq *cq,
			      पूर्णांक num_entries, काष्ठा ib_wc *wc, u16 hw_cons)
अणु
	u16 cnt = 0;

	जबतक (num_entries && qp->rq.wqe_cons != hw_cons) अणु
		/* fill WC */
		wc->status = IB_WC_WR_FLUSH_ERR;
		wc->venकरोr_err = 0;
		wc->wc_flags = 0;
		wc->src_qp = qp->id;
		wc->byte_len = 0;
		wc->wr_id = qp->rqe_wr_id[qp->rq.cons].wr_id;
		wc->qp = &qp->ibqp;
		num_entries--;
		wc++;
		cnt++;
		जबतक (qp->rqe_wr_id[qp->rq.cons].wqe_size--)
			qed_chain_consume(&qp->rq.pbl);
		qedr_inc_sw_cons(&qp->rq);
	पूर्ण

	वापस cnt;
पूर्ण

अटल व्योम try_consume_resp_cqe(काष्ठा qedr_cq *cq, काष्ठा qedr_qp *qp,
				 काष्ठा rdma_cqe_responder *resp, पूर्णांक *update)
अणु
	अगर (le16_to_cpu(resp->rq_cons_or_srq_id) == qp->rq.wqe_cons) अणु
		consume_cqe(cq);
		*update |= 1;
	पूर्ण
पूर्ण

अटल पूर्णांक qedr_poll_cq_resp_srq(काष्ठा qedr_dev *dev, काष्ठा qedr_qp *qp,
				 काष्ठा qedr_cq *cq, पूर्णांक num_entries,
				 काष्ठा ib_wc *wc,
				 काष्ठा rdma_cqe_responder *resp)
अणु
	पूर्णांक cnt;

	cnt = process_resp_one_srq(dev, qp, cq, wc, resp);
	consume_cqe(cq);

	वापस cnt;
पूर्ण

अटल पूर्णांक qedr_poll_cq_resp(काष्ठा qedr_dev *dev, काष्ठा qedr_qp *qp,
			     काष्ठा qedr_cq *cq, पूर्णांक num_entries,
			     काष्ठा ib_wc *wc, काष्ठा rdma_cqe_responder *resp,
			     पूर्णांक *update)
अणु
	पूर्णांक cnt;

	अगर (resp->status == RDMA_CQE_RESP_STS_WORK_REQUEST_FLUSHED_ERR) अणु
		cnt = process_resp_flush(qp, cq, num_entries, wc,
					 resp->rq_cons_or_srq_id);
		try_consume_resp_cqe(cq, qp, resp, update);
	पूर्ण अन्यथा अणु
		cnt = process_resp_one(dev, qp, cq, wc, resp);
		consume_cqe(cq);
		*update |= 1;
	पूर्ण

	वापस cnt;
पूर्ण

अटल व्योम try_consume_req_cqe(काष्ठा qedr_cq *cq, काष्ठा qedr_qp *qp,
				काष्ठा rdma_cqe_requester *req, पूर्णांक *update)
अणु
	अगर (le16_to_cpu(req->sq_cons) == qp->sq.wqe_cons) अणु
		consume_cqe(cq);
		*update |= 1;
	पूर्ण
पूर्ण

पूर्णांक qedr_poll_cq(काष्ठा ib_cq *ibcq, पूर्णांक num_entries, काष्ठा ib_wc *wc)
अणु
	काष्ठा qedr_dev *dev = get_qedr_dev(ibcq->device);
	काष्ठा qedr_cq *cq = get_qedr_cq(ibcq);
	जोड़ rdma_cqe *cqe;
	u32 old_cons, new_cons;
	अचिन्हित दीर्घ flags;
	पूर्णांक update = 0;
	पूर्णांक करोne = 0;

	अगर (cq->destroyed) अणु
		DP_ERR(dev,
		       "warning: poll was invoked after destroy for cq %p (icid=%d)\n",
		       cq, cq->icid);
		वापस 0;
	पूर्ण

	अगर (cq->cq_type == QEDR_CQ_TYPE_GSI)
		वापस qedr_gsi_poll_cq(ibcq, num_entries, wc);

	spin_lock_irqsave(&cq->cq_lock, flags);
	cqe = cq->latest_cqe;
	old_cons = qed_chain_get_cons_idx_u32(&cq->pbl);
	जबतक (num_entries && is_valid_cqe(cq, cqe)) अणु
		काष्ठा qedr_qp *qp;
		पूर्णांक cnt = 0;

		/* prevent speculative पढ़ोs of any field of CQE */
		rmb();

		qp = cqe_get_qp(cqe);
		अगर (!qp) अणु
			WARN(1, "Error: CQE QP pointer is NULL. CQE=%p\n", cqe);
			अवरोध;
		पूर्ण

		wc->qp = &qp->ibqp;

		चयन (cqe_get_type(cqe)) अणु
		हाल RDMA_CQE_TYPE_REQUESTER:
			cnt = qedr_poll_cq_req(dev, qp, cq, num_entries, wc,
					       &cqe->req);
			try_consume_req_cqe(cq, qp, &cqe->req, &update);
			अवरोध;
		हाल RDMA_CQE_TYPE_RESPONDER_RQ:
			cnt = qedr_poll_cq_resp(dev, qp, cq, num_entries, wc,
						&cqe->resp, &update);
			अवरोध;
		हाल RDMA_CQE_TYPE_RESPONDER_SRQ:
			cnt = qedr_poll_cq_resp_srq(dev, qp, cq, num_entries,
						    wc, &cqe->resp);
			update = 1;
			अवरोध;
		हाल RDMA_CQE_TYPE_INVALID:
		शेष:
			DP_ERR(dev, "Error: invalid CQE type = %d\n",
			       cqe_get_type(cqe));
		पूर्ण
		num_entries -= cnt;
		wc += cnt;
		करोne += cnt;

		cqe = get_cqe(cq);
	पूर्ण
	new_cons = qed_chain_get_cons_idx_u32(&cq->pbl);

	cq->cq_cons += new_cons - old_cons;

	अगर (update)
		/* करोorbell notअगरies abount latest VALID entry,
		 * but chain alपढ़ोy poपूर्णांक to the next INVALID one
		 */
		करोorbell_cq(cq, cq->cq_cons - 1, cq->arm_flags);

	spin_unlock_irqrestore(&cq->cq_lock, flags);
	वापस करोne;
पूर्ण

पूर्णांक qedr_process_mad(काष्ठा ib_device *ibdev, पूर्णांक process_mad_flags,
		     u32 port_num, स्थिर काष्ठा ib_wc *in_wc,
		     स्थिर काष्ठा ib_grh *in_grh, स्थिर काष्ठा ib_mad *in,
		     काष्ठा ib_mad *out_mad, माप_प्रकार *out_mad_size,
		     u16 *out_mad_pkey_index)
अणु
	वापस IB_MAD_RESULT_SUCCESS;
पूर्ण
