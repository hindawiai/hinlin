<शैली गुरु>
/*
 * Broadcom NetXtreme-E RoCE driver.
 *
 * Copyright (c) 2016 - 2017, Broadcom. All rights reserved.  The term
 * Broadcom refers to Broadcom Limited and/or its subsidiaries.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS
 * BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Description: IB Verbs पूर्णांकerpreter
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_ether.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_mad.h>
#समावेश <rdma/ib_cache.h>
#समावेश <rdma/uverbs_ioctl.h>

#समावेश "bnxt_ulp.h"

#समावेश "roce_hsi.h"
#समावेश "qplib_res.h"
#समावेश "qplib_sp.h"
#समावेश "qplib_fp.h"
#समावेश "qplib_rcfw.h"

#समावेश "bnxt_re.h"
#समावेश "ib_verbs.h"
#समावेश <rdma/bnxt_re-abi.h>

अटल पूर्णांक __from_ib_access_flags(पूर्णांक अगरlags)
अणु
	पूर्णांक qflags = 0;

	अगर (अगरlags & IB_ACCESS_LOCAL_WRITE)
		qflags |= BNXT_QPLIB_ACCESS_LOCAL_WRITE;
	अगर (अगरlags & IB_ACCESS_REMOTE_READ)
		qflags |= BNXT_QPLIB_ACCESS_REMOTE_READ;
	अगर (अगरlags & IB_ACCESS_REMOTE_WRITE)
		qflags |= BNXT_QPLIB_ACCESS_REMOTE_WRITE;
	अगर (अगरlags & IB_ACCESS_REMOTE_ATOMIC)
		qflags |= BNXT_QPLIB_ACCESS_REMOTE_ATOMIC;
	अगर (अगरlags & IB_ACCESS_MW_BIND)
		qflags |= BNXT_QPLIB_ACCESS_MW_BIND;
	अगर (अगरlags & IB_ZERO_BASED)
		qflags |= BNXT_QPLIB_ACCESS_ZERO_BASED;
	अगर (अगरlags & IB_ACCESS_ON_DEMAND)
		qflags |= BNXT_QPLIB_ACCESS_ON_DEMAND;
	वापस qflags;
पूर्ण;

अटल क्रमागत ib_access_flags __to_ib_access_flags(पूर्णांक qflags)
अणु
	क्रमागत ib_access_flags अगरlags = 0;

	अगर (qflags & BNXT_QPLIB_ACCESS_LOCAL_WRITE)
		अगरlags |= IB_ACCESS_LOCAL_WRITE;
	अगर (qflags & BNXT_QPLIB_ACCESS_REMOTE_WRITE)
		अगरlags |= IB_ACCESS_REMOTE_WRITE;
	अगर (qflags & BNXT_QPLIB_ACCESS_REMOTE_READ)
		अगरlags |= IB_ACCESS_REMOTE_READ;
	अगर (qflags & BNXT_QPLIB_ACCESS_REMOTE_ATOMIC)
		अगरlags |= IB_ACCESS_REMOTE_ATOMIC;
	अगर (qflags & BNXT_QPLIB_ACCESS_MW_BIND)
		अगरlags |= IB_ACCESS_MW_BIND;
	अगर (qflags & BNXT_QPLIB_ACCESS_ZERO_BASED)
		अगरlags |= IB_ZERO_BASED;
	अगर (qflags & BNXT_QPLIB_ACCESS_ON_DEMAND)
		अगरlags |= IB_ACCESS_ON_DEMAND;
	वापस अगरlags;
पूर्ण;

अटल पूर्णांक bnxt_re_build_sgl(काष्ठा ib_sge *ib_sg_list,
			     काष्ठा bnxt_qplib_sge *sg_list, पूर्णांक num)
अणु
	पूर्णांक i, total = 0;

	क्रम (i = 0; i < num; i++) अणु
		sg_list[i].addr = ib_sg_list[i].addr;
		sg_list[i].lkey = ib_sg_list[i].lkey;
		sg_list[i].size = ib_sg_list[i].length;
		total += sg_list[i].size;
	पूर्ण
	वापस total;
पूर्ण

/* Device */
पूर्णांक bnxt_re_query_device(काष्ठा ib_device *ibdev,
			 काष्ठा ib_device_attr *ib_attr,
			 काष्ठा ib_udata *udata)
अणु
	काष्ठा bnxt_re_dev *rdev = to_bnxt_re_dev(ibdev, ibdev);
	काष्ठा bnxt_qplib_dev_attr *dev_attr = &rdev->dev_attr;

	स_रखो(ib_attr, 0, माप(*ib_attr));
	स_नकल(&ib_attr->fw_ver, dev_attr->fw_ver,
	       min(माप(dev_attr->fw_ver),
		   माप(ib_attr->fw_ver)));
	bnxt_qplib_get_guid(rdev->netdev->dev_addr,
			    (u8 *)&ib_attr->sys_image_guid);
	ib_attr->max_mr_size = BNXT_RE_MAX_MR_SIZE;
	ib_attr->page_size_cap = BNXT_RE_PAGE_SIZE_4K | BNXT_RE_PAGE_SIZE_2M;

	ib_attr->venकरोr_id = rdev->en_dev->pdev->venकरोr;
	ib_attr->venकरोr_part_id = rdev->en_dev->pdev->device;
	ib_attr->hw_ver = rdev->en_dev->pdev->subप्रणाली_device;
	ib_attr->max_qp = dev_attr->max_qp;
	ib_attr->max_qp_wr = dev_attr->max_qp_wqes;
	ib_attr->device_cap_flags =
				    IB_DEVICE_CURR_QP_STATE_MOD
				    | IB_DEVICE_RC_RNR_NAK_GEN
				    | IB_DEVICE_SHUTDOWN_PORT
				    | IB_DEVICE_SYS_IMAGE_GUID
				    | IB_DEVICE_LOCAL_DMA_LKEY
				    | IB_DEVICE_RESIZE_MAX_WR
				    | IB_DEVICE_PORT_ACTIVE_EVENT
				    | IB_DEVICE_N_NOTIFY_CQ
				    | IB_DEVICE_MEM_WINDOW
				    | IB_DEVICE_MEM_WINDOW_TYPE_2B
				    | IB_DEVICE_MEM_MGT_EXTENSIONS;
	ib_attr->max_send_sge = dev_attr->max_qp_sges;
	ib_attr->max_recv_sge = dev_attr->max_qp_sges;
	ib_attr->max_sge_rd = dev_attr->max_qp_sges;
	ib_attr->max_cq = dev_attr->max_cq;
	ib_attr->max_cqe = dev_attr->max_cq_wqes;
	ib_attr->max_mr = dev_attr->max_mr;
	ib_attr->max_pd = dev_attr->max_pd;
	ib_attr->max_qp_rd_atom = dev_attr->max_qp_rd_atom;
	ib_attr->max_qp_init_rd_atom = dev_attr->max_qp_init_rd_atom;
	ib_attr->atomic_cap = IB_ATOMIC_NONE;
	ib_attr->masked_atomic_cap = IB_ATOMIC_NONE;

	ib_attr->max_ee_rd_atom = 0;
	ib_attr->max_res_rd_atom = 0;
	ib_attr->max_ee_init_rd_atom = 0;
	ib_attr->max_ee = 0;
	ib_attr->max_rdd = 0;
	ib_attr->max_mw = dev_attr->max_mw;
	ib_attr->max_raw_ipv6_qp = 0;
	ib_attr->max_raw_ethy_qp = dev_attr->max_raw_ethy_qp;
	ib_attr->max_mcast_grp = 0;
	ib_attr->max_mcast_qp_attach = 0;
	ib_attr->max_total_mcast_qp_attach = 0;
	ib_attr->max_ah = dev_attr->max_ah;

	ib_attr->max_srq = dev_attr->max_srq;
	ib_attr->max_srq_wr = dev_attr->max_srq_wqes;
	ib_attr->max_srq_sge = dev_attr->max_srq_sges;

	ib_attr->max_fast_reg_page_list_len = MAX_PBL_LVL_1_PGS;

	ib_attr->max_pkeys = 1;
	ib_attr->local_ca_ack_delay = BNXT_RE_DEFAULT_ACK_DELAY;
	वापस 0;
पूर्ण

/* Port */
पूर्णांक bnxt_re_query_port(काष्ठा ib_device *ibdev, u32 port_num,
		       काष्ठा ib_port_attr *port_attr)
अणु
	काष्ठा bnxt_re_dev *rdev = to_bnxt_re_dev(ibdev, ibdev);
	काष्ठा bnxt_qplib_dev_attr *dev_attr = &rdev->dev_attr;

	स_रखो(port_attr, 0, माप(*port_attr));

	अगर (netअगर_running(rdev->netdev) && netअगर_carrier_ok(rdev->netdev)) अणु
		port_attr->state = IB_PORT_ACTIVE;
		port_attr->phys_state = IB_PORT_PHYS_STATE_LINK_UP;
	पूर्ण अन्यथा अणु
		port_attr->state = IB_PORT_DOWN;
		port_attr->phys_state = IB_PORT_PHYS_STATE_DISABLED;
	पूर्ण
	port_attr->max_mtu = IB_MTU_4096;
	port_attr->active_mtu = iboe_get_mtu(rdev->netdev->mtu);
	port_attr->gid_tbl_len = dev_attr->max_sgid;
	port_attr->port_cap_flags = IB_PORT_CM_SUP | IB_PORT_REINIT_SUP |
				    IB_PORT_DEVICE_MGMT_SUP |
				    IB_PORT_VENDOR_CLASS_SUP;
	port_attr->ip_gids = true;

	port_attr->max_msg_sz = (u32)BNXT_RE_MAX_MR_SIZE_LOW;
	port_attr->bad_pkey_cntr = 0;
	port_attr->qkey_viol_cntr = 0;
	port_attr->pkey_tbl_len = dev_attr->max_pkey;
	port_attr->lid = 0;
	port_attr->sm_lid = 0;
	port_attr->lmc = 0;
	port_attr->max_vl_num = 4;
	port_attr->sm_sl = 0;
	port_attr->subnet_समयout = 0;
	port_attr->init_type_reply = 0;
	port_attr->active_speed = rdev->active_speed;
	port_attr->active_width = rdev->active_width;

	वापस 0;
पूर्ण

पूर्णांक bnxt_re_get_port_immutable(काष्ठा ib_device *ibdev, u32 port_num,
			       काष्ठा ib_port_immutable *immutable)
अणु
	काष्ठा ib_port_attr port_attr;

	अगर (bnxt_re_query_port(ibdev, port_num, &port_attr))
		वापस -EINVAL;

	immutable->pkey_tbl_len = port_attr.pkey_tbl_len;
	immutable->gid_tbl_len = port_attr.gid_tbl_len;
	immutable->core_cap_flags = RDMA_CORE_PORT_IBA_ROCE;
	immutable->core_cap_flags |= RDMA_CORE_CAP_PROT_ROCE_UDP_ENCAP;
	immutable->max_mad_size = IB_MGMT_MAD_SIZE;
	वापस 0;
पूर्ण

व्योम bnxt_re_query_fw_str(काष्ठा ib_device *ibdev, अक्षर *str)
अणु
	काष्ठा bnxt_re_dev *rdev = to_bnxt_re_dev(ibdev, ibdev);

	snम_लिखो(str, IB_FW_VERSION_NAME_MAX, "%d.%d.%d.%d",
		 rdev->dev_attr.fw_ver[0], rdev->dev_attr.fw_ver[1],
		 rdev->dev_attr.fw_ver[2], rdev->dev_attr.fw_ver[3]);
पूर्ण

पूर्णांक bnxt_re_query_pkey(काष्ठा ib_device *ibdev, u32 port_num,
		       u16 index, u16 *pkey)
अणु
	काष्ठा bnxt_re_dev *rdev = to_bnxt_re_dev(ibdev, ibdev);

	/* Ignore port_num */

	स_रखो(pkey, 0, माप(*pkey));
	वापस bnxt_qplib_get_pkey(&rdev->qplib_res,
				   &rdev->qplib_res.pkey_tbl, index, pkey);
पूर्ण

पूर्णांक bnxt_re_query_gid(काष्ठा ib_device *ibdev, u32 port_num,
		      पूर्णांक index, जोड़ ib_gid *gid)
अणु
	काष्ठा bnxt_re_dev *rdev = to_bnxt_re_dev(ibdev, ibdev);
	पूर्णांक rc = 0;

	/* Ignore port_num */
	स_रखो(gid, 0, माप(*gid));
	rc = bnxt_qplib_get_sgid(&rdev->qplib_res,
				 &rdev->qplib_res.sgid_tbl, index,
				 (काष्ठा bnxt_qplib_gid *)gid);
	वापस rc;
पूर्ण

पूर्णांक bnxt_re_del_gid(स्थिर काष्ठा ib_gid_attr *attr, व्योम **context)
अणु
	पूर्णांक rc = 0;
	काष्ठा bnxt_re_gid_ctx *ctx, **ctx_tbl;
	काष्ठा bnxt_re_dev *rdev = to_bnxt_re_dev(attr->device, ibdev);
	काष्ठा bnxt_qplib_sgid_tbl *sgid_tbl = &rdev->qplib_res.sgid_tbl;
	काष्ठा bnxt_qplib_gid *gid_to_del;
	u16 vlan_id = 0xFFFF;

	/* Delete the entry from the hardware */
	ctx = *context;
	अगर (!ctx)
		वापस -EINVAL;

	अगर (sgid_tbl && sgid_tbl->active) अणु
		अगर (ctx->idx >= sgid_tbl->max)
			वापस -EINVAL;
		gid_to_del = &sgid_tbl->tbl[ctx->idx].gid;
		vlan_id = sgid_tbl->tbl[ctx->idx].vlan_id;
		/* DEL_GID is called in WQ context(netdevice_event_work_handler)
		 * or via the ib_unरेजिस्टर_device path. In the क्रमmer हाल QP1
		 * may not be destroyed yet, in which हाल just वापस as FW
		 * needs that entry to be present and will fail it's deletion.
		 * We could get invoked again after QP1 is destroyed OR get an
		 * ADD_GID call with a dअगरferent GID value क्रम the same index
		 * where we issue MODIFY_GID cmd to update the GID entry -- TBD
		 */
		अगर (ctx->idx == 0 &&
		    rdma_link_local_addr((काष्ठा in6_addr *)gid_to_del) &&
		    ctx->refcnt == 1 && rdev->gsi_ctx.gsi_sqp) अणु
			ibdev_dbg(&rdev->ibdev,
				  "Trying to delete GID0 while QP1 is alive\n");
			वापस -EFAULT;
		पूर्ण
		ctx->refcnt--;
		अगर (!ctx->refcnt) अणु
			rc = bnxt_qplib_del_sgid(sgid_tbl, gid_to_del,
						 vlan_id,  true);
			अगर (rc) अणु
				ibdev_err(&rdev->ibdev,
					  "Failed to remove GID: %#x", rc);
			पूर्ण अन्यथा अणु
				ctx_tbl = sgid_tbl->ctx;
				ctx_tbl[ctx->idx] = शून्य;
				kमुक्त(ctx);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक bnxt_re_add_gid(स्थिर काष्ठा ib_gid_attr *attr, व्योम **context)
अणु
	पूर्णांक rc;
	u32 tbl_idx = 0;
	u16 vlan_id = 0xFFFF;
	काष्ठा bnxt_re_gid_ctx *ctx, **ctx_tbl;
	काष्ठा bnxt_re_dev *rdev = to_bnxt_re_dev(attr->device, ibdev);
	काष्ठा bnxt_qplib_sgid_tbl *sgid_tbl = &rdev->qplib_res.sgid_tbl;

	rc = rdma_पढ़ो_gid_l2_fields(attr, &vlan_id, शून्य);
	अगर (rc)
		वापस rc;

	rc = bnxt_qplib_add_sgid(sgid_tbl, (काष्ठा bnxt_qplib_gid *)&attr->gid,
				 rdev->qplib_res.netdev->dev_addr,
				 vlan_id, true, &tbl_idx);
	अगर (rc == -EALREADY) अणु
		ctx_tbl = sgid_tbl->ctx;
		ctx_tbl[tbl_idx]->refcnt++;
		*context = ctx_tbl[tbl_idx];
		वापस 0;
	पूर्ण

	अगर (rc < 0) अणु
		ibdev_err(&rdev->ibdev, "Failed to add GID: %#x", rc);
		वापस rc;
	पूर्ण

	ctx = kदो_स्मृति(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;
	ctx_tbl = sgid_tbl->ctx;
	ctx->idx = tbl_idx;
	ctx->refcnt = 1;
	ctx_tbl[tbl_idx] = ctx;
	*context = ctx;

	वापस rc;
पूर्ण

क्रमागत rdma_link_layer bnxt_re_get_link_layer(काष्ठा ib_device *ibdev,
					    u32 port_num)
अणु
	वापस IB_LINK_LAYER_ETHERNET;
पूर्ण

#घोषणा	BNXT_RE_FENCE_PBL_SIZE	DIV_ROUND_UP(BNXT_RE_FENCE_BYTES, PAGE_SIZE)

अटल व्योम bnxt_re_create_fence_wqe(काष्ठा bnxt_re_pd *pd)
अणु
	काष्ठा bnxt_re_fence_data *fence = &pd->fence;
	काष्ठा ib_mr *ib_mr = &fence->mr->ib_mr;
	काष्ठा bnxt_qplib_swqe *wqe = &fence->bind_wqe;

	स_रखो(wqe, 0, माप(*wqe));
	wqe->type = BNXT_QPLIB_SWQE_TYPE_BIND_MW;
	wqe->wr_id = BNXT_QPLIB_FENCE_WRID;
	wqe->flags |= BNXT_QPLIB_SWQE_FLAGS_SIGNAL_COMP;
	wqe->flags |= BNXT_QPLIB_SWQE_FLAGS_UC_FENCE;
	wqe->bind.zero_based = false;
	wqe->bind.parent_l_key = ib_mr->lkey;
	wqe->bind.va = (u64)(अचिन्हित दीर्घ)fence->va;
	wqe->bind.length = fence->size;
	wqe->bind.access_cntl = __from_ib_access_flags(IB_ACCESS_REMOTE_READ);
	wqe->bind.mw_type = SQ_BIND_MW_TYPE_TYPE1;

	/* Save the initial rkey in fence काष्ठाure क्रम now;
	 * wqe->bind.r_key will be set at (re)bind समय.
	 */
	fence->bind_rkey = ib_inc_rkey(fence->mw->rkey);
पूर्ण

अटल पूर्णांक bnxt_re_bind_fence_mw(काष्ठा bnxt_qplib_qp *qplib_qp)
अणु
	काष्ठा bnxt_re_qp *qp = container_of(qplib_qp, काष्ठा bnxt_re_qp,
					     qplib_qp);
	काष्ठा ib_pd *ib_pd = qp->ib_qp.pd;
	काष्ठा bnxt_re_pd *pd = container_of(ib_pd, काष्ठा bnxt_re_pd, ib_pd);
	काष्ठा bnxt_re_fence_data *fence = &pd->fence;
	काष्ठा bnxt_qplib_swqe *fence_wqe = &fence->bind_wqe;
	काष्ठा bnxt_qplib_swqe wqe;
	पूर्णांक rc;

	स_नकल(&wqe, fence_wqe, माप(wqe));
	wqe.bind.r_key = fence->bind_rkey;
	fence->bind_rkey = ib_inc_rkey(fence->bind_rkey);

	ibdev_dbg(&qp->rdev->ibdev,
		  "Posting bind fence-WQE: rkey: %#x QP: %d PD: %p\n",
		wqe.bind.r_key, qp->qplib_qp.id, pd);
	rc = bnxt_qplib_post_send(&qp->qplib_qp, &wqe);
	अगर (rc) अणु
		ibdev_err(&qp->rdev->ibdev, "Failed to bind fence-WQE\n");
		वापस rc;
	पूर्ण
	bnxt_qplib_post_send_db(&qp->qplib_qp);

	वापस rc;
पूर्ण

अटल व्योम bnxt_re_destroy_fence_mr(काष्ठा bnxt_re_pd *pd)
अणु
	काष्ठा bnxt_re_fence_data *fence = &pd->fence;
	काष्ठा bnxt_re_dev *rdev = pd->rdev;
	काष्ठा device *dev = &rdev->en_dev->pdev->dev;
	काष्ठा bnxt_re_mr *mr = fence->mr;

	अगर (fence->mw) अणु
		bnxt_re_dealloc_mw(fence->mw);
		fence->mw = शून्य;
	पूर्ण
	अगर (mr) अणु
		अगर (mr->ib_mr.rkey)
			bnxt_qplib_dereg_mrw(&rdev->qplib_res, &mr->qplib_mr,
					     true);
		अगर (mr->ib_mr.lkey)
			bnxt_qplib_मुक्त_mrw(&rdev->qplib_res, &mr->qplib_mr);
		kमुक्त(mr);
		fence->mr = शून्य;
	पूर्ण
	अगर (fence->dma_addr) अणु
		dma_unmap_single(dev, fence->dma_addr, BNXT_RE_FENCE_BYTES,
				 DMA_BIसूचीECTIONAL);
		fence->dma_addr = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_re_create_fence_mr(काष्ठा bnxt_re_pd *pd)
अणु
	पूर्णांक mr_access_flags = IB_ACCESS_LOCAL_WRITE | IB_ACCESS_MW_BIND;
	काष्ठा bnxt_re_fence_data *fence = &pd->fence;
	काष्ठा bnxt_re_dev *rdev = pd->rdev;
	काष्ठा device *dev = &rdev->en_dev->pdev->dev;
	काष्ठा bnxt_re_mr *mr = शून्य;
	dma_addr_t dma_addr = 0;
	काष्ठा ib_mw *mw;
	पूर्णांक rc;

	dma_addr = dma_map_single(dev, fence->va, BNXT_RE_FENCE_BYTES,
				  DMA_BIसूचीECTIONAL);
	rc = dma_mapping_error(dev, dma_addr);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "Failed to dma-map fence-MR-mem\n");
		rc = -EIO;
		fence->dma_addr = 0;
		जाओ fail;
	पूर्ण
	fence->dma_addr = dma_addr;

	/* Allocate a MR */
	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr) अणु
		rc = -ENOMEM;
		जाओ fail;
	पूर्ण
	fence->mr = mr;
	mr->rdev = rdev;
	mr->qplib_mr.pd = &pd->qplib_pd;
	mr->qplib_mr.type = CMDQ_ALLOCATE_MRW_MRW_FLAGS_PMR;
	mr->qplib_mr.flags = __from_ib_access_flags(mr_access_flags);
	rc = bnxt_qplib_alloc_mrw(&rdev->qplib_res, &mr->qplib_mr);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "Failed to alloc fence-HW-MR\n");
		जाओ fail;
	पूर्ण

	/* Register MR */
	mr->ib_mr.lkey = mr->qplib_mr.lkey;
	mr->qplib_mr.va = (u64)(अचिन्हित दीर्घ)fence->va;
	mr->qplib_mr.total_size = BNXT_RE_FENCE_BYTES;
	rc = bnxt_qplib_reg_mr(&rdev->qplib_res, &mr->qplib_mr, शून्य,
			       BNXT_RE_FENCE_PBL_SIZE, PAGE_SIZE);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "Failed to register fence-MR\n");
		जाओ fail;
	पूर्ण
	mr->ib_mr.rkey = mr->qplib_mr.rkey;

	/* Create a fence MW only क्रम kernel consumers */
	mw = bnxt_re_alloc_mw(&pd->ib_pd, IB_MW_TYPE_1, शून्य);
	अगर (IS_ERR(mw)) अणु
		ibdev_err(&rdev->ibdev,
			  "Failed to create fence-MW for PD: %p\n", pd);
		rc = PTR_ERR(mw);
		जाओ fail;
	पूर्ण
	fence->mw = mw;

	bnxt_re_create_fence_wqe(pd);
	वापस 0;

fail:
	bnxt_re_destroy_fence_mr(pd);
	वापस rc;
पूर्ण

/* Protection Doमुख्यs */
पूर्णांक bnxt_re_dealloc_pd(काष्ठा ib_pd *ib_pd, काष्ठा ib_udata *udata)
अणु
	काष्ठा bnxt_re_pd *pd = container_of(ib_pd, काष्ठा bnxt_re_pd, ib_pd);
	काष्ठा bnxt_re_dev *rdev = pd->rdev;

	bnxt_re_destroy_fence_mr(pd);

	अगर (pd->qplib_pd.id)
		bnxt_qplib_dealloc_pd(&rdev->qplib_res, &rdev->qplib_res.pd_tbl,
				      &pd->qplib_pd);
	वापस 0;
पूर्ण

पूर्णांक bnxt_re_alloc_pd(काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = ibpd->device;
	काष्ठा bnxt_re_dev *rdev = to_bnxt_re_dev(ibdev, ibdev);
	काष्ठा bnxt_re_ucontext *ucntx = rdma_udata_to_drv_context(
		udata, काष्ठा bnxt_re_ucontext, ib_uctx);
	काष्ठा bnxt_re_pd *pd = container_of(ibpd, काष्ठा bnxt_re_pd, ib_pd);
	पूर्णांक rc;

	pd->rdev = rdev;
	अगर (bnxt_qplib_alloc_pd(&rdev->qplib_res.pd_tbl, &pd->qplib_pd)) अणु
		ibdev_err(&rdev->ibdev, "Failed to allocate HW PD");
		rc = -ENOMEM;
		जाओ fail;
	पूर्ण

	अगर (udata) अणु
		काष्ठा bnxt_re_pd_resp resp;

		अगर (!ucntx->dpi.dbr) अणु
			/* Allocate DPI in alloc_pd to aव्योम failing of
			 * ibv_devinfo and family of application when DPIs
			 * are depleted.
			 */
			अगर (bnxt_qplib_alloc_dpi(&rdev->qplib_res.dpi_tbl,
						 &ucntx->dpi, ucntx)) अणु
				rc = -ENOMEM;
				जाओ dbfail;
			पूर्ण
		पूर्ण

		resp.pdid = pd->qplib_pd.id;
		/* Still allow mapping this DBR to the new user PD. */
		resp.dpi = ucntx->dpi.dpi;
		resp.dbr = (u64)ucntx->dpi.umdbr;

		rc = ib_copy_to_udata(udata, &resp, माप(resp));
		अगर (rc) अणु
			ibdev_err(&rdev->ibdev,
				  "Failed to copy user response\n");
			जाओ dbfail;
		पूर्ण
	पूर्ण

	अगर (!udata)
		अगर (bnxt_re_create_fence_mr(pd))
			ibdev_warn(&rdev->ibdev,
				   "Failed to create Fence-MR\n");
	वापस 0;
dbfail:
	bnxt_qplib_dealloc_pd(&rdev->qplib_res, &rdev->qplib_res.pd_tbl,
			      &pd->qplib_pd);
fail:
	वापस rc;
पूर्ण

/* Address Handles */
पूर्णांक bnxt_re_destroy_ah(काष्ठा ib_ah *ib_ah, u32 flags)
अणु
	काष्ठा bnxt_re_ah *ah = container_of(ib_ah, काष्ठा bnxt_re_ah, ib_ah);
	काष्ठा bnxt_re_dev *rdev = ah->rdev;

	bnxt_qplib_destroy_ah(&rdev->qplib_res, &ah->qplib_ah,
			      !(flags & RDMA_DESTROY_AH_SLEEPABLE));
	वापस 0;
पूर्ण

अटल u8 bnxt_re_stack_to_dev_nw_type(क्रमागत rdma_network_type ntype)
अणु
	u8 nw_type;

	चयन (ntype) अणु
	हाल RDMA_NETWORK_IPV4:
		nw_type = CMDQ_CREATE_AH_TYPE_V2IPV4;
		अवरोध;
	हाल RDMA_NETWORK_IPV6:
		nw_type = CMDQ_CREATE_AH_TYPE_V2IPV6;
		अवरोध;
	शेष:
		nw_type = CMDQ_CREATE_AH_TYPE_V1;
		अवरोध;
	पूर्ण
	वापस nw_type;
पूर्ण

पूर्णांक bnxt_re_create_ah(काष्ठा ib_ah *ib_ah, काष्ठा rdma_ah_init_attr *init_attr,
		      काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_pd *ib_pd = ib_ah->pd;
	काष्ठा bnxt_re_pd *pd = container_of(ib_pd, काष्ठा bnxt_re_pd, ib_pd);
	काष्ठा rdma_ah_attr *ah_attr = init_attr->ah_attr;
	स्थिर काष्ठा ib_global_route *grh = rdma_ah_पढ़ो_grh(ah_attr);
	काष्ठा bnxt_re_dev *rdev = pd->rdev;
	स्थिर काष्ठा ib_gid_attr *sgid_attr;
	काष्ठा bnxt_re_gid_ctx *ctx;
	काष्ठा bnxt_re_ah *ah = container_of(ib_ah, काष्ठा bnxt_re_ah, ib_ah);
	u8 nw_type;
	पूर्णांक rc;

	अगर (!(rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH)) अणु
		ibdev_err(&rdev->ibdev, "Failed to alloc AH: GRH not set");
		वापस -EINVAL;
	पूर्ण

	ah->rdev = rdev;
	ah->qplib_ah.pd = &pd->qplib_pd;

	/* Supply the configuration क्रम the HW */
	स_नकल(ah->qplib_ah.dgid.data, grh->dgid.raw,
	       माप(जोड़ ib_gid));
	sgid_attr = grh->sgid_attr;
	/* Get the HW context of the GID. The reference
	 * of GID table entry is alपढ़ोy taken by the caller.
	 */
	ctx = rdma_पढ़ो_gid_hw_context(sgid_attr);
	ah->qplib_ah.sgid_index = ctx->idx;
	ah->qplib_ah.host_sgid_index = grh->sgid_index;
	ah->qplib_ah.traffic_class = grh->traffic_class;
	ah->qplib_ah.flow_label = grh->flow_label;
	ah->qplib_ah.hop_limit = grh->hop_limit;
	ah->qplib_ah.sl = rdma_ah_get_sl(ah_attr);

	/* Get network header type क्रम this GID */
	nw_type = rdma_gid_attr_network_type(sgid_attr);
	ah->qplib_ah.nw_type = bnxt_re_stack_to_dev_nw_type(nw_type);

	स_नकल(ah->qplib_ah.dmac, ah_attr->roce.dmac, ETH_ALEN);
	rc = bnxt_qplib_create_ah(&rdev->qplib_res, &ah->qplib_ah,
				  !(init_attr->flags &
				    RDMA_CREATE_AH_SLEEPABLE));
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "Failed to allocate HW AH");
		वापस rc;
	पूर्ण

	/* Write AVID to shared page. */
	अगर (udata) अणु
		काष्ठा bnxt_re_ucontext *uctx = rdma_udata_to_drv_context(
			udata, काष्ठा bnxt_re_ucontext, ib_uctx);
		अचिन्हित दीर्घ flag;
		u32 *wrptr;

		spin_lock_irqsave(&uctx->sh_lock, flag);
		wrptr = (u32 *)(uctx->shpg + BNXT_RE_AVID_OFFT);
		*wrptr = ah->qplib_ah.id;
		wmb(); /* make sure cache is updated. */
		spin_unlock_irqrestore(&uctx->sh_lock, flag);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक bnxt_re_modअगरy_ah(काष्ठा ib_ah *ib_ah, काष्ठा rdma_ah_attr *ah_attr)
अणु
	वापस 0;
पूर्ण

पूर्णांक bnxt_re_query_ah(काष्ठा ib_ah *ib_ah, काष्ठा rdma_ah_attr *ah_attr)
अणु
	काष्ठा bnxt_re_ah *ah = container_of(ib_ah, काष्ठा bnxt_re_ah, ib_ah);

	ah_attr->type = ib_ah->type;
	rdma_ah_set_sl(ah_attr, ah->qplib_ah.sl);
	स_नकल(ah_attr->roce.dmac, ah->qplib_ah.dmac, ETH_ALEN);
	rdma_ah_set_grh(ah_attr, शून्य, 0,
			ah->qplib_ah.host_sgid_index,
			0, ah->qplib_ah.traffic_class);
	rdma_ah_set_dgid_raw(ah_attr, ah->qplib_ah.dgid.data);
	rdma_ah_set_port_num(ah_attr, 1);
	rdma_ah_set_अटल_rate(ah_attr, 0);
	वापस 0;
पूर्ण

अचिन्हित दीर्घ bnxt_re_lock_cqs(काष्ठा bnxt_re_qp *qp)
	__acquires(&qp->scq->cq_lock) __acquires(&qp->rcq->cq_lock)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qp->scq->cq_lock, flags);
	अगर (qp->rcq != qp->scq)
		spin_lock(&qp->rcq->cq_lock);
	अन्यथा
		__acquire(&qp->rcq->cq_lock);

	वापस flags;
पूर्ण

व्योम bnxt_re_unlock_cqs(काष्ठा bnxt_re_qp *qp,
			अचिन्हित दीर्घ flags)
	__releases(&qp->scq->cq_lock) __releases(&qp->rcq->cq_lock)
अणु
	अगर (qp->rcq != qp->scq)
		spin_unlock(&qp->rcq->cq_lock);
	अन्यथा
		__release(&qp->rcq->cq_lock);
	spin_unlock_irqrestore(&qp->scq->cq_lock, flags);
पूर्ण

अटल पूर्णांक bnxt_re_destroy_gsi_sqp(काष्ठा bnxt_re_qp *qp)
अणु
	काष्ठा bnxt_re_qp *gsi_sqp;
	काष्ठा bnxt_re_ah *gsi_sah;
	काष्ठा bnxt_re_dev *rdev;
	पूर्णांक rc = 0;

	rdev = qp->rdev;
	gsi_sqp = rdev->gsi_ctx.gsi_sqp;
	gsi_sah = rdev->gsi_ctx.gsi_sah;

	ibdev_dbg(&rdev->ibdev, "Destroy the shadow AH\n");
	bnxt_qplib_destroy_ah(&rdev->qplib_res,
			      &gsi_sah->qplib_ah,
			      true);
	bnxt_qplib_clean_qp(&qp->qplib_qp);

	ibdev_dbg(&rdev->ibdev, "Destroy the shadow QP\n");
	rc = bnxt_qplib_destroy_qp(&rdev->qplib_res, &gsi_sqp->qplib_qp);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "Destroy Shadow QP failed");
		जाओ fail;
	पूर्ण
	bnxt_qplib_मुक्त_qp_res(&rdev->qplib_res, &gsi_sqp->qplib_qp);

	/* हटाओ from active qp list */
	mutex_lock(&rdev->qp_lock);
	list_del(&gsi_sqp->list);
	mutex_unlock(&rdev->qp_lock);
	atomic_dec(&rdev->qp_count);

	kमुक्त(rdev->gsi_ctx.sqp_tbl);
	kमुक्त(gsi_sah);
	kमुक्त(gsi_sqp);
	rdev->gsi_ctx.gsi_sqp = शून्य;
	rdev->gsi_ctx.gsi_sah = शून्य;
	rdev->gsi_ctx.sqp_tbl = शून्य;

	वापस 0;
fail:
	वापस rc;
पूर्ण

/* Queue Pairs */
पूर्णांक bnxt_re_destroy_qp(काष्ठा ib_qp *ib_qp, काष्ठा ib_udata *udata)
अणु
	काष्ठा bnxt_re_qp *qp = container_of(ib_qp, काष्ठा bnxt_re_qp, ib_qp);
	काष्ठा bnxt_re_dev *rdev = qp->rdev;
	अचिन्हित पूर्णांक flags;
	पूर्णांक rc;

	bnxt_qplib_flush_cqn_wq(&qp->qplib_qp);

	rc = bnxt_qplib_destroy_qp(&rdev->qplib_res, &qp->qplib_qp);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "Failed to destroy HW QP");
		वापस rc;
	पूर्ण

	अगर (rdma_is_kernel_res(&qp->ib_qp.res)) अणु
		flags = bnxt_re_lock_cqs(qp);
		bnxt_qplib_clean_qp(&qp->qplib_qp);
		bnxt_re_unlock_cqs(qp, flags);
	पूर्ण

	bnxt_qplib_मुक्त_qp_res(&rdev->qplib_res, &qp->qplib_qp);

	अगर (ib_qp->qp_type == IB_QPT_GSI && rdev->gsi_ctx.gsi_sqp) अणु
		rc = bnxt_re_destroy_gsi_sqp(qp);
		अगर (rc)
			जाओ sh_fail;
	पूर्ण

	mutex_lock(&rdev->qp_lock);
	list_del(&qp->list);
	mutex_unlock(&rdev->qp_lock);
	atomic_dec(&rdev->qp_count);

	ib_umem_release(qp->rumem);
	ib_umem_release(qp->sumem);

	kमुक्त(qp);
	वापस 0;
sh_fail:
	वापस rc;
पूर्ण

अटल u8 __from_ib_qp_type(क्रमागत ib_qp_type type)
अणु
	चयन (type) अणु
	हाल IB_QPT_GSI:
		वापस CMDQ_CREATE_QP1_TYPE_GSI;
	हाल IB_QPT_RC:
		वापस CMDQ_CREATE_QP_TYPE_RC;
	हाल IB_QPT_UD:
		वापस CMDQ_CREATE_QP_TYPE_UD;
	शेष:
		वापस IB_QPT_MAX;
	पूर्ण
पूर्ण

अटल u16 bnxt_re_setup_rwqe_size(काष्ठा bnxt_qplib_qp *qplqp,
				   पूर्णांक rsge, पूर्णांक max)
अणु
	अगर (qplqp->wqe_mode == BNXT_QPLIB_WQE_MODE_STATIC)
		rsge = max;
	वापस bnxt_re_get_rwqe_size(rsge);
पूर्ण

अटल u16 bnxt_re_get_wqe_size(पूर्णांक ilsize, पूर्णांक nsge)
अणु
	u16 wqe_size, calc_ils;

	wqe_size = bnxt_re_get_swqe_size(nsge);
	अगर (ilsize) अणु
		calc_ils = माप(काष्ठा sq_send_hdr) + ilsize;
		wqe_size = max_t(u16, calc_ils, wqe_size);
		wqe_size = ALIGN(wqe_size, माप(काष्ठा sq_send_hdr));
	पूर्ण
	वापस wqe_size;
पूर्ण

अटल पूर्णांक bnxt_re_setup_swqe_size(काष्ठा bnxt_re_qp *qp,
				   काष्ठा ib_qp_init_attr *init_attr)
अणु
	काष्ठा bnxt_qplib_dev_attr *dev_attr;
	काष्ठा bnxt_qplib_qp *qplqp;
	काष्ठा bnxt_re_dev *rdev;
	काष्ठा bnxt_qplib_q *sq;
	पूर्णांक align, ilsize;

	rdev = qp->rdev;
	qplqp = &qp->qplib_qp;
	sq = &qplqp->sq;
	dev_attr = &rdev->dev_attr;

	align = माप(काष्ठा sq_send_hdr);
	ilsize = ALIGN(init_attr->cap.max_अंतरभूत_data, align);

	sq->wqe_size = bnxt_re_get_wqe_size(ilsize, sq->max_sge);
	अगर (sq->wqe_size > bnxt_re_get_swqe_size(dev_attr->max_qp_sges))
		वापस -EINVAL;
	/* For gen p4 and gen p5 backward compatibility mode
	 * wqe size is fixed to 128 bytes
	 */
	अगर (sq->wqe_size < bnxt_re_get_swqe_size(dev_attr->max_qp_sges) &&
			qplqp->wqe_mode == BNXT_QPLIB_WQE_MODE_STATIC)
		sq->wqe_size = bnxt_re_get_swqe_size(dev_attr->max_qp_sges);

	अगर (init_attr->cap.max_अंतरभूत_data) अणु
		qplqp->max_अंतरभूत_data = sq->wqe_size -
			माप(काष्ठा sq_send_hdr);
		init_attr->cap.max_अंतरभूत_data = qplqp->max_अंतरभूत_data;
		अगर (qplqp->wqe_mode == BNXT_QPLIB_WQE_MODE_STATIC)
			sq->max_sge = qplqp->max_अंतरभूत_data /
				माप(काष्ठा sq_sge);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_re_init_user_qp(काष्ठा bnxt_re_dev *rdev, काष्ठा bnxt_re_pd *pd,
				काष्ठा bnxt_re_qp *qp, काष्ठा ib_udata *udata)
अणु
	काष्ठा bnxt_qplib_qp *qplib_qp;
	काष्ठा bnxt_re_ucontext *cntx;
	काष्ठा bnxt_re_qp_req ureq;
	पूर्णांक bytes = 0, psn_sz;
	काष्ठा ib_umem *umem;
	पूर्णांक psn_nume;

	qplib_qp = &qp->qplib_qp;
	cntx = rdma_udata_to_drv_context(udata, काष्ठा bnxt_re_ucontext,
					 ib_uctx);
	अगर (ib_copy_from_udata(&ureq, udata, माप(ureq)))
		वापस -EFAULT;

	bytes = (qplib_qp->sq.max_wqe * qplib_qp->sq.wqe_size);
	/* Consider mapping PSN search memory only क्रम RC QPs. */
	अगर (qplib_qp->type == CMDQ_CREATE_QP_TYPE_RC) अणु
		psn_sz = bnxt_qplib_is_chip_gen_p5(rdev->chip_ctx) ?
						   माप(काष्ठा sq_psn_search_ext) :
						   माप(काष्ठा sq_psn_search);
		psn_nume = (qplib_qp->wqe_mode == BNXT_QPLIB_WQE_MODE_STATIC) ?
			    qplib_qp->sq.max_wqe :
			    ((qplib_qp->sq.max_wqe * qplib_qp->sq.wqe_size) /
			      माप(काष्ठा bnxt_qplib_sge));
		bytes += (psn_nume * psn_sz);
	पूर्ण

	bytes = PAGE_ALIGN(bytes);
	umem = ib_umem_get(&rdev->ibdev, ureq.qpsva, bytes,
			   IB_ACCESS_LOCAL_WRITE);
	अगर (IS_ERR(umem))
		वापस PTR_ERR(umem);

	qp->sumem = umem;
	qplib_qp->sq.sg_info.umem = umem;
	qplib_qp->sq.sg_info.pgsize = PAGE_SIZE;
	qplib_qp->sq.sg_info.pgshft = PAGE_SHIFT;
	qplib_qp->qp_handle = ureq.qp_handle;

	अगर (!qp->qplib_qp.srq) अणु
		bytes = (qplib_qp->rq.max_wqe * qplib_qp->rq.wqe_size);
		bytes = PAGE_ALIGN(bytes);
		umem = ib_umem_get(&rdev->ibdev, ureq.qprva, bytes,
				   IB_ACCESS_LOCAL_WRITE);
		अगर (IS_ERR(umem))
			जाओ rqfail;
		qp->rumem = umem;
		qplib_qp->rq.sg_info.umem = umem;
		qplib_qp->rq.sg_info.pgsize = PAGE_SIZE;
		qplib_qp->rq.sg_info.pgshft = PAGE_SHIFT;
	पूर्ण

	qplib_qp->dpi = &cntx->dpi;
	वापस 0;
rqfail:
	ib_umem_release(qp->sumem);
	qp->sumem = शून्य;
	स_रखो(&qplib_qp->sq.sg_info, 0, माप(qplib_qp->sq.sg_info));

	वापस PTR_ERR(umem);
पूर्ण

अटल काष्ठा bnxt_re_ah *bnxt_re_create_shaकरोw_qp_ah
				(काष्ठा bnxt_re_pd *pd,
				 काष्ठा bnxt_qplib_res *qp1_res,
				 काष्ठा bnxt_qplib_qp *qp1_qp)
अणु
	काष्ठा bnxt_re_dev *rdev = pd->rdev;
	काष्ठा bnxt_re_ah *ah;
	जोड़ ib_gid sgid;
	पूर्णांक rc;

	ah = kzalloc(माप(*ah), GFP_KERNEL);
	अगर (!ah)
		वापस शून्य;

	ah->rdev = rdev;
	ah->qplib_ah.pd = &pd->qplib_pd;

	rc = bnxt_re_query_gid(&rdev->ibdev, 1, 0, &sgid);
	अगर (rc)
		जाओ fail;

	/* supply the dgid data same as sgid */
	स_नकल(ah->qplib_ah.dgid.data, &sgid.raw,
	       माप(जोड़ ib_gid));
	ah->qplib_ah.sgid_index = 0;

	ah->qplib_ah.traffic_class = 0;
	ah->qplib_ah.flow_label = 0;
	ah->qplib_ah.hop_limit = 1;
	ah->qplib_ah.sl = 0;
	/* Have DMAC same as SMAC */
	ether_addr_copy(ah->qplib_ah.dmac, rdev->netdev->dev_addr);

	rc = bnxt_qplib_create_ah(&rdev->qplib_res, &ah->qplib_ah, false);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev,
			  "Failed to allocate HW AH for Shadow QP");
		जाओ fail;
	पूर्ण

	वापस ah;

fail:
	kमुक्त(ah);
	वापस शून्य;
पूर्ण

अटल काष्ठा bnxt_re_qp *bnxt_re_create_shaकरोw_qp
				(काष्ठा bnxt_re_pd *pd,
				 काष्ठा bnxt_qplib_res *qp1_res,
				 काष्ठा bnxt_qplib_qp *qp1_qp)
अणु
	काष्ठा bnxt_re_dev *rdev = pd->rdev;
	काष्ठा bnxt_re_qp *qp;
	पूर्णांक rc;

	qp = kzalloc(माप(*qp), GFP_KERNEL);
	अगर (!qp)
		वापस शून्य;

	qp->rdev = rdev;

	/* Initialize the shaकरोw QP काष्ठाure from the QP1 values */
	ether_addr_copy(qp->qplib_qp.smac, rdev->netdev->dev_addr);

	qp->qplib_qp.pd = &pd->qplib_pd;
	qp->qplib_qp.qp_handle = (u64)(अचिन्हित दीर्घ)(&qp->qplib_qp);
	qp->qplib_qp.type = IB_QPT_UD;

	qp->qplib_qp.max_अंतरभूत_data = 0;
	qp->qplib_qp.sig_type = true;

	/* Shaकरोw QP SQ depth should be same as QP1 RQ depth */
	qp->qplib_qp.sq.wqe_size = bnxt_re_get_wqe_size(0, 6);
	qp->qplib_qp.sq.max_wqe = qp1_qp->rq.max_wqe;
	qp->qplib_qp.sq.max_sge = 2;
	/* Q full delta can be 1 since it is पूर्णांकernal QP */
	qp->qplib_qp.sq.q_full_delta = 1;
	qp->qplib_qp.sq.sg_info.pgsize = PAGE_SIZE;
	qp->qplib_qp.sq.sg_info.pgshft = PAGE_SHIFT;

	qp->qplib_qp.scq = qp1_qp->scq;
	qp->qplib_qp.rcq = qp1_qp->rcq;

	qp->qplib_qp.rq.wqe_size = bnxt_re_get_rwqe_size(6);
	qp->qplib_qp.rq.max_wqe = qp1_qp->rq.max_wqe;
	qp->qplib_qp.rq.max_sge = qp1_qp->rq.max_sge;
	/* Q full delta can be 1 since it is पूर्णांकernal QP */
	qp->qplib_qp.rq.q_full_delta = 1;
	qp->qplib_qp.rq.sg_info.pgsize = PAGE_SIZE;
	qp->qplib_qp.rq.sg_info.pgshft = PAGE_SHIFT;

	qp->qplib_qp.mtu = qp1_qp->mtu;

	qp->qplib_qp.sq_hdr_buf_size = 0;
	qp->qplib_qp.rq_hdr_buf_size = BNXT_QPLIB_MAX_GRH_HDR_SIZE_IPV6;
	qp->qplib_qp.dpi = &rdev->dpi_privileged;

	rc = bnxt_qplib_create_qp(qp1_res, &qp->qplib_qp);
	अगर (rc)
		जाओ fail;

	spin_lock_init(&qp->sq_lock);
	INIT_LIST_HEAD(&qp->list);
	mutex_lock(&rdev->qp_lock);
	list_add_tail(&qp->list, &rdev->qp_list);
	atomic_inc(&rdev->qp_count);
	mutex_unlock(&rdev->qp_lock);
	वापस qp;
fail:
	kमुक्त(qp);
	वापस शून्य;
पूर्ण

अटल पूर्णांक bnxt_re_init_rq_attr(काष्ठा bnxt_re_qp *qp,
				काष्ठा ib_qp_init_attr *init_attr)
अणु
	काष्ठा bnxt_qplib_dev_attr *dev_attr;
	काष्ठा bnxt_qplib_qp *qplqp;
	काष्ठा bnxt_re_dev *rdev;
	काष्ठा bnxt_qplib_q *rq;
	पूर्णांक entries;

	rdev = qp->rdev;
	qplqp = &qp->qplib_qp;
	rq = &qplqp->rq;
	dev_attr = &rdev->dev_attr;

	अगर (init_attr->srq) अणु
		काष्ठा bnxt_re_srq *srq;

		srq = container_of(init_attr->srq, काष्ठा bnxt_re_srq, ib_srq);
		अगर (!srq) अणु
			ibdev_err(&rdev->ibdev, "SRQ not found");
			वापस -EINVAL;
		पूर्ण
		qplqp->srq = &srq->qplib_srq;
		rq->max_wqe = 0;
	पूर्ण अन्यथा अणु
		rq->max_sge = init_attr->cap.max_recv_sge;
		अगर (rq->max_sge > dev_attr->max_qp_sges)
			rq->max_sge = dev_attr->max_qp_sges;
		init_attr->cap.max_recv_sge = rq->max_sge;
		rq->wqe_size = bnxt_re_setup_rwqe_size(qplqp, rq->max_sge,
						       dev_attr->max_qp_sges);
		/* Allocate 1 more than what's provided so posting max doesn't
		 * mean empty.
		 */
		entries = roundup_घात_of_two(init_attr->cap.max_recv_wr + 1);
		rq->max_wqe = min_t(u32, entries, dev_attr->max_qp_wqes + 1);
		rq->q_full_delta = 0;
		rq->sg_info.pgsize = PAGE_SIZE;
		rq->sg_info.pgshft = PAGE_SHIFT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bnxt_re_adjust_gsi_rq_attr(काष्ठा bnxt_re_qp *qp)
अणु
	काष्ठा bnxt_qplib_dev_attr *dev_attr;
	काष्ठा bnxt_qplib_qp *qplqp;
	काष्ठा bnxt_re_dev *rdev;

	rdev = qp->rdev;
	qplqp = &qp->qplib_qp;
	dev_attr = &rdev->dev_attr;

	अगर (!bnxt_qplib_is_chip_gen_p5(rdev->chip_ctx)) अणु
		qplqp->rq.max_sge = dev_attr->max_qp_sges;
		अगर (qplqp->rq.max_sge > dev_attr->max_qp_sges)
			qplqp->rq.max_sge = dev_attr->max_qp_sges;
		qplqp->rq.max_sge = 6;
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_re_init_sq_attr(काष्ठा bnxt_re_qp *qp,
				काष्ठा ib_qp_init_attr *init_attr,
				काष्ठा ib_udata *udata)
अणु
	काष्ठा bnxt_qplib_dev_attr *dev_attr;
	काष्ठा bnxt_qplib_qp *qplqp;
	काष्ठा bnxt_re_dev *rdev;
	काष्ठा bnxt_qplib_q *sq;
	पूर्णांक entries;
	पूर्णांक dअगरf;
	पूर्णांक rc;

	rdev = qp->rdev;
	qplqp = &qp->qplib_qp;
	sq = &qplqp->sq;
	dev_attr = &rdev->dev_attr;

	sq->max_sge = init_attr->cap.max_send_sge;
	अगर (sq->max_sge > dev_attr->max_qp_sges) अणु
		sq->max_sge = dev_attr->max_qp_sges;
		init_attr->cap.max_send_sge = sq->max_sge;
	पूर्ण

	rc = bnxt_re_setup_swqe_size(qp, init_attr);
	अगर (rc)
		वापस rc;

	entries = init_attr->cap.max_send_wr;
	/* Allocate 128 + 1 more than what's provided */
	dअगरf = (qplqp->wqe_mode == BNXT_QPLIB_WQE_MODE_VARIABLE) ?
		0 : BNXT_QPLIB_RESERVED_QP_WRS;
	entries = roundup_घात_of_two(entries + dअगरf + 1);
	sq->max_wqe = min_t(u32, entries, dev_attr->max_qp_wqes + dअगरf + 1);
	sq->q_full_delta = dअगरf + 1;
	/*
	 * Reserving one slot क्रम Phantom WQE. Application can
	 * post one extra entry in this हाल. But allowing this to aव्योम
	 * unexpected Queue full condition
	 */
	qplqp->sq.q_full_delta -= 1;
	qplqp->sq.sg_info.pgsize = PAGE_SIZE;
	qplqp->sq.sg_info.pgshft = PAGE_SHIFT;

	वापस 0;
पूर्ण

अटल व्योम bnxt_re_adjust_gsi_sq_attr(काष्ठा bnxt_re_qp *qp,
				       काष्ठा ib_qp_init_attr *init_attr)
अणु
	काष्ठा bnxt_qplib_dev_attr *dev_attr;
	काष्ठा bnxt_qplib_qp *qplqp;
	काष्ठा bnxt_re_dev *rdev;
	पूर्णांक entries;

	rdev = qp->rdev;
	qplqp = &qp->qplib_qp;
	dev_attr = &rdev->dev_attr;

	अगर (!bnxt_qplib_is_chip_gen_p5(rdev->chip_ctx)) अणु
		entries = roundup_घात_of_two(init_attr->cap.max_send_wr + 1);
		qplqp->sq.max_wqe = min_t(u32, entries,
					  dev_attr->max_qp_wqes + 1);
		qplqp->sq.q_full_delta = qplqp->sq.max_wqe -
			init_attr->cap.max_send_wr;
		qplqp->sq.max_sge++; /* Need one extra sge to put UD header */
		अगर (qplqp->sq.max_sge > dev_attr->max_qp_sges)
			qplqp->sq.max_sge = dev_attr->max_qp_sges;
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_re_init_qp_type(काष्ठा bnxt_re_dev *rdev,
				काष्ठा ib_qp_init_attr *init_attr)
अणु
	काष्ठा bnxt_qplib_chip_ctx *chip_ctx;
	पूर्णांक qptype;

	chip_ctx = rdev->chip_ctx;

	qptype = __from_ib_qp_type(init_attr->qp_type);
	अगर (qptype == IB_QPT_MAX) अणु
		ibdev_err(&rdev->ibdev, "QP type 0x%x not supported", qptype);
		qptype = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (bnxt_qplib_is_chip_gen_p5(chip_ctx) &&
	    init_attr->qp_type == IB_QPT_GSI)
		qptype = CMDQ_CREATE_QP_TYPE_GSI;
out:
	वापस qptype;
पूर्ण

अटल पूर्णांक bnxt_re_init_qp_attr(काष्ठा bnxt_re_qp *qp, काष्ठा bnxt_re_pd *pd,
				काष्ठा ib_qp_init_attr *init_attr,
				काष्ठा ib_udata *udata)
अणु
	काष्ठा bnxt_qplib_dev_attr *dev_attr;
	काष्ठा bnxt_qplib_qp *qplqp;
	काष्ठा bnxt_re_dev *rdev;
	काष्ठा bnxt_re_cq *cq;
	पूर्णांक rc = 0, qptype;

	rdev = qp->rdev;
	qplqp = &qp->qplib_qp;
	dev_attr = &rdev->dev_attr;

	/* Setup misc params */
	ether_addr_copy(qplqp->smac, rdev->netdev->dev_addr);
	qplqp->pd = &pd->qplib_pd;
	qplqp->qp_handle = (u64)qplqp;
	qplqp->max_अंतरभूत_data = init_attr->cap.max_अंतरभूत_data;
	qplqp->sig_type = ((init_attr->sq_sig_type == IB_SIGNAL_ALL_WR) ?
			    true : false);
	qptype = bnxt_re_init_qp_type(rdev, init_attr);
	अगर (qptype < 0) अणु
		rc = qptype;
		जाओ out;
	पूर्ण
	qplqp->type = (u8)qptype;
	qplqp->wqe_mode = rdev->chip_ctx->modes.wqe_mode;

	अगर (init_attr->qp_type == IB_QPT_RC) अणु
		qplqp->max_rd_atomic = dev_attr->max_qp_rd_atom;
		qplqp->max_dest_rd_atomic = dev_attr->max_qp_init_rd_atom;
	पूर्ण
	qplqp->mtu = ib_mtu_क्रमागत_to_पूर्णांक(iboe_get_mtu(rdev->netdev->mtu));
	qplqp->dpi = &rdev->dpi_privileged; /* Doorbell page */
	अगर (init_attr->create_flags) अणु
		ibdev_dbg(&rdev->ibdev,
			  "QP create flags 0x%x not supported",
			  init_attr->create_flags);
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Setup CQs */
	अगर (init_attr->send_cq) अणु
		cq = container_of(init_attr->send_cq, काष्ठा bnxt_re_cq, ib_cq);
		अगर (!cq) अणु
			ibdev_err(&rdev->ibdev, "Send CQ not found");
			rc = -EINVAL;
			जाओ out;
		पूर्ण
		qplqp->scq = &cq->qplib_cq;
		qp->scq = cq;
	पूर्ण

	अगर (init_attr->recv_cq) अणु
		cq = container_of(init_attr->recv_cq, काष्ठा bnxt_re_cq, ib_cq);
		अगर (!cq) अणु
			ibdev_err(&rdev->ibdev, "Receive CQ not found");
			rc = -EINVAL;
			जाओ out;
		पूर्ण
		qplqp->rcq = &cq->qplib_cq;
		qp->rcq = cq;
	पूर्ण

	/* Setup RQ/SRQ */
	rc = bnxt_re_init_rq_attr(qp, init_attr);
	अगर (rc)
		जाओ out;
	अगर (init_attr->qp_type == IB_QPT_GSI)
		bnxt_re_adjust_gsi_rq_attr(qp);

	/* Setup SQ */
	rc = bnxt_re_init_sq_attr(qp, init_attr, udata);
	अगर (rc)
		जाओ out;
	अगर (init_attr->qp_type == IB_QPT_GSI)
		bnxt_re_adjust_gsi_sq_attr(qp, init_attr);

	अगर (udata) /* This will update DPI and qp_handle */
		rc = bnxt_re_init_user_qp(rdev, pd, qp, udata);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_re_create_shaकरोw_gsi(काष्ठा bnxt_re_qp *qp,
				     काष्ठा bnxt_re_pd *pd)
अणु
	काष्ठा bnxt_re_sqp_entries *sqp_tbl = शून्य;
	काष्ठा bnxt_re_dev *rdev;
	काष्ठा bnxt_re_qp *sqp;
	काष्ठा bnxt_re_ah *sah;
	पूर्णांक rc = 0;

	rdev = qp->rdev;
	/* Create a shaकरोw QP to handle the QP1 traffic */
	sqp_tbl = kzalloc(माप(*sqp_tbl) * BNXT_RE_MAX_GSI_SQP_ENTRIES,
			  GFP_KERNEL);
	अगर (!sqp_tbl)
		वापस -ENOMEM;
	rdev->gsi_ctx.sqp_tbl = sqp_tbl;

	sqp = bnxt_re_create_shaकरोw_qp(pd, &rdev->qplib_res, &qp->qplib_qp);
	अगर (!sqp) अणु
		rc = -ENODEV;
		ibdev_err(&rdev->ibdev, "Failed to create Shadow QP for QP1");
		जाओ out;
	पूर्ण
	rdev->gsi_ctx.gsi_sqp = sqp;

	sqp->rcq = qp->rcq;
	sqp->scq = qp->scq;
	sah = bnxt_re_create_shaकरोw_qp_ah(pd, &rdev->qplib_res,
					  &qp->qplib_qp);
	अगर (!sah) अणु
		bnxt_qplib_destroy_qp(&rdev->qplib_res,
				      &sqp->qplib_qp);
		rc = -ENODEV;
		ibdev_err(&rdev->ibdev,
			  "Failed to create AH entry for ShadowQP");
		जाओ out;
	पूर्ण
	rdev->gsi_ctx.gsi_sah = sah;

	वापस 0;
out:
	kमुक्त(sqp_tbl);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_re_create_gsi_qp(काष्ठा bnxt_re_qp *qp, काष्ठा bnxt_re_pd *pd,
				 काष्ठा ib_qp_init_attr *init_attr)
अणु
	काष्ठा bnxt_re_dev *rdev;
	काष्ठा bnxt_qplib_qp *qplqp;
	पूर्णांक rc = 0;

	rdev = qp->rdev;
	qplqp = &qp->qplib_qp;

	qplqp->rq_hdr_buf_size = BNXT_QPLIB_MAX_QP1_RQ_HDR_SIZE_V2;
	qplqp->sq_hdr_buf_size = BNXT_QPLIB_MAX_QP1_SQ_HDR_SIZE_V2;

	rc = bnxt_qplib_create_qp1(&rdev->qplib_res, qplqp);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "create HW QP1 failed!");
		जाओ out;
	पूर्ण

	rc = bnxt_re_create_shaकरोw_gsi(qp, pd);
out:
	वापस rc;
पूर्ण

अटल bool bnxt_re_test_qp_limits(काष्ठा bnxt_re_dev *rdev,
				   काष्ठा ib_qp_init_attr *init_attr,
				   काष्ठा bnxt_qplib_dev_attr *dev_attr)
अणु
	bool rc = true;

	अगर (init_attr->cap.max_send_wr > dev_attr->max_qp_wqes ||
	    init_attr->cap.max_recv_wr > dev_attr->max_qp_wqes ||
	    init_attr->cap.max_send_sge > dev_attr->max_qp_sges ||
	    init_attr->cap.max_recv_sge > dev_attr->max_qp_sges ||
	    init_attr->cap.max_अंतरभूत_data > dev_attr->max_अंतरभूत_data) अणु
		ibdev_err(&rdev->ibdev,
			  "Create QP failed - max exceeded! 0x%x/0x%x 0x%x/0x%x 0x%x/0x%x 0x%x/0x%x 0x%x/0x%x",
			  init_attr->cap.max_send_wr, dev_attr->max_qp_wqes,
			  init_attr->cap.max_recv_wr, dev_attr->max_qp_wqes,
			  init_attr->cap.max_send_sge, dev_attr->max_qp_sges,
			  init_attr->cap.max_recv_sge, dev_attr->max_qp_sges,
			  init_attr->cap.max_अंतरभूत_data,
			  dev_attr->max_अंतरभूत_data);
		rc = false;
	पूर्ण
	वापस rc;
पूर्ण

काष्ठा ib_qp *bnxt_re_create_qp(काष्ठा ib_pd *ib_pd,
				काष्ठा ib_qp_init_attr *qp_init_attr,
				काष्ठा ib_udata *udata)
अणु
	काष्ठा bnxt_re_pd *pd = container_of(ib_pd, काष्ठा bnxt_re_pd, ib_pd);
	काष्ठा bnxt_re_dev *rdev = pd->rdev;
	काष्ठा bnxt_qplib_dev_attr *dev_attr = &rdev->dev_attr;
	काष्ठा bnxt_re_qp *qp;
	पूर्णांक rc;

	rc = bnxt_re_test_qp_limits(rdev, qp_init_attr, dev_attr);
	अगर (!rc) अणु
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

	qp = kzalloc(माप(*qp), GFP_KERNEL);
	अगर (!qp) अणु
		rc = -ENOMEM;
		जाओ निकास;
	पूर्ण
	qp->rdev = rdev;
	rc = bnxt_re_init_qp_attr(qp, pd, qp_init_attr, udata);
	अगर (rc)
		जाओ fail;

	अगर (qp_init_attr->qp_type == IB_QPT_GSI &&
	    !(bnxt_qplib_is_chip_gen_p5(rdev->chip_ctx))) अणु
		rc = bnxt_re_create_gsi_qp(qp, pd, qp_init_attr);
		अगर (rc == -ENODEV)
			जाओ qp_destroy;
		अगर (rc)
			जाओ fail;
	पूर्ण अन्यथा अणु
		rc = bnxt_qplib_create_qp(&rdev->qplib_res, &qp->qplib_qp);
		अगर (rc) अणु
			ibdev_err(&rdev->ibdev, "Failed to create HW QP");
			जाओ मुक्त_umem;
		पूर्ण
		अगर (udata) अणु
			काष्ठा bnxt_re_qp_resp resp;

			resp.qpid = qp->qplib_qp.id;
			resp.rsvd = 0;
			rc = ib_copy_to_udata(udata, &resp, माप(resp));
			अगर (rc) अणु
				ibdev_err(&rdev->ibdev, "Failed to copy QP udata");
				जाओ qp_destroy;
			पूर्ण
		पूर्ण
	पूर्ण

	qp->ib_qp.qp_num = qp->qplib_qp.id;
	अगर (qp_init_attr->qp_type == IB_QPT_GSI)
		rdev->gsi_ctx.gsi_qp = qp;
	spin_lock_init(&qp->sq_lock);
	spin_lock_init(&qp->rq_lock);
	INIT_LIST_HEAD(&qp->list);
	mutex_lock(&rdev->qp_lock);
	list_add_tail(&qp->list, &rdev->qp_list);
	mutex_unlock(&rdev->qp_lock);
	atomic_inc(&rdev->qp_count);

	वापस &qp->ib_qp;
qp_destroy:
	bnxt_qplib_destroy_qp(&rdev->qplib_res, &qp->qplib_qp);
मुक्त_umem:
	ib_umem_release(qp->rumem);
	ib_umem_release(qp->sumem);
fail:
	kमुक्त(qp);
निकास:
	वापस ERR_PTR(rc);
पूर्ण

अटल u8 __from_ib_qp_state(क्रमागत ib_qp_state state)
अणु
	चयन (state) अणु
	हाल IB_QPS_RESET:
		वापस CMDQ_MODIFY_QP_NEW_STATE_RESET;
	हाल IB_QPS_INIT:
		वापस CMDQ_MODIFY_QP_NEW_STATE_INIT;
	हाल IB_QPS_RTR:
		वापस CMDQ_MODIFY_QP_NEW_STATE_RTR;
	हाल IB_QPS_RTS:
		वापस CMDQ_MODIFY_QP_NEW_STATE_RTS;
	हाल IB_QPS_SQD:
		वापस CMDQ_MODIFY_QP_NEW_STATE_SQD;
	हाल IB_QPS_SQE:
		वापस CMDQ_MODIFY_QP_NEW_STATE_SQE;
	हाल IB_QPS_ERR:
	शेष:
		वापस CMDQ_MODIFY_QP_NEW_STATE_ERR;
	पूर्ण
पूर्ण

अटल क्रमागत ib_qp_state __to_ib_qp_state(u8 state)
अणु
	चयन (state) अणु
	हाल CMDQ_MODIFY_QP_NEW_STATE_RESET:
		वापस IB_QPS_RESET;
	हाल CMDQ_MODIFY_QP_NEW_STATE_INIT:
		वापस IB_QPS_INIT;
	हाल CMDQ_MODIFY_QP_NEW_STATE_RTR:
		वापस IB_QPS_RTR;
	हाल CMDQ_MODIFY_QP_NEW_STATE_RTS:
		वापस IB_QPS_RTS;
	हाल CMDQ_MODIFY_QP_NEW_STATE_SQD:
		वापस IB_QPS_SQD;
	हाल CMDQ_MODIFY_QP_NEW_STATE_SQE:
		वापस IB_QPS_SQE;
	हाल CMDQ_MODIFY_QP_NEW_STATE_ERR:
	शेष:
		वापस IB_QPS_ERR;
	पूर्ण
पूर्ण

अटल u32 __from_ib_mtu(क्रमागत ib_mtu mtu)
अणु
	चयन (mtu) अणु
	हाल IB_MTU_256:
		वापस CMDQ_MODIFY_QP_PATH_MTU_MTU_256;
	हाल IB_MTU_512:
		वापस CMDQ_MODIFY_QP_PATH_MTU_MTU_512;
	हाल IB_MTU_1024:
		वापस CMDQ_MODIFY_QP_PATH_MTU_MTU_1024;
	हाल IB_MTU_2048:
		वापस CMDQ_MODIFY_QP_PATH_MTU_MTU_2048;
	हाल IB_MTU_4096:
		वापस CMDQ_MODIFY_QP_PATH_MTU_MTU_4096;
	शेष:
		वापस CMDQ_MODIFY_QP_PATH_MTU_MTU_2048;
	पूर्ण
पूर्ण

अटल क्रमागत ib_mtu __to_ib_mtu(u32 mtu)
अणु
	चयन (mtu & CREQ_QUERY_QP_RESP_SB_PATH_MTU_MASK) अणु
	हाल CMDQ_MODIFY_QP_PATH_MTU_MTU_256:
		वापस IB_MTU_256;
	हाल CMDQ_MODIFY_QP_PATH_MTU_MTU_512:
		वापस IB_MTU_512;
	हाल CMDQ_MODIFY_QP_PATH_MTU_MTU_1024:
		वापस IB_MTU_1024;
	हाल CMDQ_MODIFY_QP_PATH_MTU_MTU_2048:
		वापस IB_MTU_2048;
	हाल CMDQ_MODIFY_QP_PATH_MTU_MTU_4096:
		वापस IB_MTU_4096;
	शेष:
		वापस IB_MTU_2048;
	पूर्ण
पूर्ण

/* Shared Receive Queues */
पूर्णांक bnxt_re_destroy_srq(काष्ठा ib_srq *ib_srq, काष्ठा ib_udata *udata)
अणु
	काष्ठा bnxt_re_srq *srq = container_of(ib_srq, काष्ठा bnxt_re_srq,
					       ib_srq);
	काष्ठा bnxt_re_dev *rdev = srq->rdev;
	काष्ठा bnxt_qplib_srq *qplib_srq = &srq->qplib_srq;
	काष्ठा bnxt_qplib_nq *nq = शून्य;

	अगर (qplib_srq->cq)
		nq = qplib_srq->cq->nq;
	bnxt_qplib_destroy_srq(&rdev->qplib_res, qplib_srq);
	ib_umem_release(srq->umem);
	atomic_dec(&rdev->srq_count);
	अगर (nq)
		nq->budget--;
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_re_init_user_srq(काष्ठा bnxt_re_dev *rdev,
				 काष्ठा bnxt_re_pd *pd,
				 काष्ठा bnxt_re_srq *srq,
				 काष्ठा ib_udata *udata)
अणु
	काष्ठा bnxt_re_srq_req ureq;
	काष्ठा bnxt_qplib_srq *qplib_srq = &srq->qplib_srq;
	काष्ठा ib_umem *umem;
	पूर्णांक bytes = 0;
	काष्ठा bnxt_re_ucontext *cntx = rdma_udata_to_drv_context(
		udata, काष्ठा bnxt_re_ucontext, ib_uctx);

	अगर (ib_copy_from_udata(&ureq, udata, माप(ureq)))
		वापस -EFAULT;

	bytes = (qplib_srq->max_wqe * qplib_srq->wqe_size);
	bytes = PAGE_ALIGN(bytes);
	umem = ib_umem_get(&rdev->ibdev, ureq.srqva, bytes,
			   IB_ACCESS_LOCAL_WRITE);
	अगर (IS_ERR(umem))
		वापस PTR_ERR(umem);

	srq->umem = umem;
	qplib_srq->sg_info.umem = umem;
	qplib_srq->sg_info.pgsize = PAGE_SIZE;
	qplib_srq->sg_info.pgshft = PAGE_SHIFT;
	qplib_srq->srq_handle = ureq.srq_handle;
	qplib_srq->dpi = &cntx->dpi;

	वापस 0;
पूर्ण

पूर्णांक bnxt_re_create_srq(काष्ठा ib_srq *ib_srq,
		       काष्ठा ib_srq_init_attr *srq_init_attr,
		       काष्ठा ib_udata *udata)
अणु
	काष्ठा bnxt_qplib_dev_attr *dev_attr;
	काष्ठा bnxt_qplib_nq *nq = शून्य;
	काष्ठा bnxt_re_dev *rdev;
	काष्ठा bnxt_re_srq *srq;
	काष्ठा bnxt_re_pd *pd;
	काष्ठा ib_pd *ib_pd;
	पूर्णांक rc, entries;

	ib_pd = ib_srq->pd;
	pd = container_of(ib_pd, काष्ठा bnxt_re_pd, ib_pd);
	rdev = pd->rdev;
	dev_attr = &rdev->dev_attr;
	srq = container_of(ib_srq, काष्ठा bnxt_re_srq, ib_srq);

	अगर (srq_init_attr->attr.max_wr >= dev_attr->max_srq_wqes) अणु
		ibdev_err(&rdev->ibdev, "Create CQ failed - max exceeded");
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (srq_init_attr->srq_type != IB_SRQT_BASIC) अणु
		rc = -EOPNOTSUPP;
		जाओ निकास;
	पूर्ण

	srq->rdev = rdev;
	srq->qplib_srq.pd = &pd->qplib_pd;
	srq->qplib_srq.dpi = &rdev->dpi_privileged;
	/* Allocate 1 more than what's provided so posting max doesn't
	 * mean empty
	 */
	entries = roundup_घात_of_two(srq_init_attr->attr.max_wr + 1);
	अगर (entries > dev_attr->max_srq_wqes + 1)
		entries = dev_attr->max_srq_wqes + 1;
	srq->qplib_srq.max_wqe = entries;

	srq->qplib_srq.max_sge = srq_init_attr->attr.max_sge;
	 /* 128 byte wqe size क्रम SRQ . So use max sges */
	srq->qplib_srq.wqe_size = bnxt_re_get_rwqe_size(dev_attr->max_srq_sges);
	srq->qplib_srq.threshold = srq_init_attr->attr.srq_limit;
	srq->srq_limit = srq_init_attr->attr.srq_limit;
	srq->qplib_srq.eventq_hw_ring_id = rdev->nq[0].ring_id;
	nq = &rdev->nq[0];

	अगर (udata) अणु
		rc = bnxt_re_init_user_srq(rdev, pd, srq, udata);
		अगर (rc)
			जाओ fail;
	पूर्ण

	rc = bnxt_qplib_create_srq(&rdev->qplib_res, &srq->qplib_srq);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "Create HW SRQ failed!");
		जाओ fail;
	पूर्ण

	अगर (udata) अणु
		काष्ठा bnxt_re_srq_resp resp;

		resp.srqid = srq->qplib_srq.id;
		rc = ib_copy_to_udata(udata, &resp, माप(resp));
		अगर (rc) अणु
			ibdev_err(&rdev->ibdev, "SRQ copy to udata failed!");
			bnxt_qplib_destroy_srq(&rdev->qplib_res,
					       &srq->qplib_srq);
			जाओ fail;
		पूर्ण
	पूर्ण
	अगर (nq)
		nq->budget++;
	atomic_inc(&rdev->srq_count);

	वापस 0;

fail:
	ib_umem_release(srq->umem);
निकास:
	वापस rc;
पूर्ण

पूर्णांक bnxt_re_modअगरy_srq(काष्ठा ib_srq *ib_srq, काष्ठा ib_srq_attr *srq_attr,
		       क्रमागत ib_srq_attr_mask srq_attr_mask,
		       काष्ठा ib_udata *udata)
अणु
	काष्ठा bnxt_re_srq *srq = container_of(ib_srq, काष्ठा bnxt_re_srq,
					       ib_srq);
	काष्ठा bnxt_re_dev *rdev = srq->rdev;
	पूर्णांक rc;

	चयन (srq_attr_mask) अणु
	हाल IB_SRQ_MAX_WR:
		/* SRQ resize is not supported */
		अवरोध;
	हाल IB_SRQ_LIMIT:
		/* Change the SRQ threshold */
		अगर (srq_attr->srq_limit > srq->qplib_srq.max_wqe)
			वापस -EINVAL;

		srq->qplib_srq.threshold = srq_attr->srq_limit;
		rc = bnxt_qplib_modअगरy_srq(&rdev->qplib_res, &srq->qplib_srq);
		अगर (rc) अणु
			ibdev_err(&rdev->ibdev, "Modify HW SRQ failed!");
			वापस rc;
		पूर्ण
		/* On success, update the shaकरोw */
		srq->srq_limit = srq_attr->srq_limit;
		/* No need to Build and send response back to udata */
		अवरोध;
	शेष:
		ibdev_err(&rdev->ibdev,
			  "Unsupported srq_attr_mask 0x%x", srq_attr_mask);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक bnxt_re_query_srq(काष्ठा ib_srq *ib_srq, काष्ठा ib_srq_attr *srq_attr)
अणु
	काष्ठा bnxt_re_srq *srq = container_of(ib_srq, काष्ठा bnxt_re_srq,
					       ib_srq);
	काष्ठा bnxt_re_srq tsrq;
	काष्ठा bnxt_re_dev *rdev = srq->rdev;
	पूर्णांक rc;

	/* Get live SRQ attr */
	tsrq.qplib_srq.id = srq->qplib_srq.id;
	rc = bnxt_qplib_query_srq(&rdev->qplib_res, &tsrq.qplib_srq);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "Query HW SRQ failed!");
		वापस rc;
	पूर्ण
	srq_attr->max_wr = srq->qplib_srq.max_wqe;
	srq_attr->max_sge = srq->qplib_srq.max_sge;
	srq_attr->srq_limit = tsrq.qplib_srq.threshold;

	वापस 0;
पूर्ण

पूर्णांक bnxt_re_post_srq_recv(काष्ठा ib_srq *ib_srq, स्थिर काष्ठा ib_recv_wr *wr,
			  स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा bnxt_re_srq *srq = container_of(ib_srq, काष्ठा bnxt_re_srq,
					       ib_srq);
	काष्ठा bnxt_qplib_swqe wqe;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	spin_lock_irqsave(&srq->lock, flags);
	जबतक (wr) अणु
		/* Transcribe each ib_recv_wr to qplib_swqe */
		wqe.num_sge = wr->num_sge;
		bnxt_re_build_sgl(wr->sg_list, wqe.sg_list, wr->num_sge);
		wqe.wr_id = wr->wr_id;
		wqe.type = BNXT_QPLIB_SWQE_TYPE_RECV;

		rc = bnxt_qplib_post_srq_recv(&srq->qplib_srq, &wqe);
		अगर (rc) अणु
			*bad_wr = wr;
			अवरोध;
		पूर्ण
		wr = wr->next;
	पूर्ण
	spin_unlock_irqrestore(&srq->lock, flags);

	वापस rc;
पूर्ण
अटल पूर्णांक bnxt_re_modअगरy_shaकरोw_qp(काष्ठा bnxt_re_dev *rdev,
				    काष्ठा bnxt_re_qp *qp1_qp,
				    पूर्णांक qp_attr_mask)
अणु
	काष्ठा bnxt_re_qp *qp = rdev->gsi_ctx.gsi_sqp;
	पूर्णांक rc = 0;

	अगर (qp_attr_mask & IB_QP_STATE) अणु
		qp->qplib_qp.modअगरy_flags |= CMDQ_MODIFY_QP_MODIFY_MASK_STATE;
		qp->qplib_qp.state = qp1_qp->qplib_qp.state;
	पूर्ण
	अगर (qp_attr_mask & IB_QP_PKEY_INDEX) अणु
		qp->qplib_qp.modअगरy_flags |= CMDQ_MODIFY_QP_MODIFY_MASK_PKEY;
		qp->qplib_qp.pkey_index = qp1_qp->qplib_qp.pkey_index;
	पूर्ण

	अगर (qp_attr_mask & IB_QP_QKEY) अणु
		qp->qplib_qp.modअगरy_flags |= CMDQ_MODIFY_QP_MODIFY_MASK_QKEY;
		/* Using a Ranकरोm  QKEY */
		qp->qplib_qp.qkey = 0x81818181;
	पूर्ण
	अगर (qp_attr_mask & IB_QP_SQ_PSN) अणु
		qp->qplib_qp.modअगरy_flags |= CMDQ_MODIFY_QP_MODIFY_MASK_SQ_PSN;
		qp->qplib_qp.sq.psn = qp1_qp->qplib_qp.sq.psn;
	पूर्ण

	rc = bnxt_qplib_modअगरy_qp(&rdev->qplib_res, &qp->qplib_qp);
	अगर (rc)
		ibdev_err(&rdev->ibdev, "Failed to modify Shadow QP for QP1");
	वापस rc;
पूर्ण

पूर्णांक bnxt_re_modअगरy_qp(काष्ठा ib_qp *ib_qp, काष्ठा ib_qp_attr *qp_attr,
		      पूर्णांक qp_attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा bnxt_re_qp *qp = container_of(ib_qp, काष्ठा bnxt_re_qp, ib_qp);
	काष्ठा bnxt_re_dev *rdev = qp->rdev;
	काष्ठा bnxt_qplib_dev_attr *dev_attr = &rdev->dev_attr;
	क्रमागत ib_qp_state curr_qp_state, new_qp_state;
	पूर्णांक rc, entries;
	अचिन्हित पूर्णांक flags;
	u8 nw_type;

	अगर (qp_attr_mask & ~IB_QP_ATTR_STANDARD_BITS)
		वापस -EOPNOTSUPP;

	qp->qplib_qp.modअगरy_flags = 0;
	अगर (qp_attr_mask & IB_QP_STATE) अणु
		curr_qp_state = __to_ib_qp_state(qp->qplib_qp.cur_qp_state);
		new_qp_state = qp_attr->qp_state;
		अगर (!ib_modअगरy_qp_is_ok(curr_qp_state, new_qp_state,
					ib_qp->qp_type, qp_attr_mask)) अणु
			ibdev_err(&rdev->ibdev,
				  "Invalid attribute mask: %#x specified ",
				  qp_attr_mask);
			ibdev_err(&rdev->ibdev,
				  "for qpn: %#x type: %#x",
				  ib_qp->qp_num, ib_qp->qp_type);
			ibdev_err(&rdev->ibdev,
				  "curr_qp_state=0x%x, new_qp_state=0x%x\n",
				  curr_qp_state, new_qp_state);
			वापस -EINVAL;
		पूर्ण
		qp->qplib_qp.modअगरy_flags |= CMDQ_MODIFY_QP_MODIFY_MASK_STATE;
		qp->qplib_qp.state = __from_ib_qp_state(qp_attr->qp_state);

		अगर (!qp->sumem &&
		    qp->qplib_qp.state == CMDQ_MODIFY_QP_NEW_STATE_ERR) अणु
			ibdev_dbg(&rdev->ibdev,
				  "Move QP = %p to flush list\n", qp);
			flags = bnxt_re_lock_cqs(qp);
			bnxt_qplib_add_flush_qp(&qp->qplib_qp);
			bnxt_re_unlock_cqs(qp, flags);
		पूर्ण
		अगर (!qp->sumem &&
		    qp->qplib_qp.state == CMDQ_MODIFY_QP_NEW_STATE_RESET) अणु
			ibdev_dbg(&rdev->ibdev,
				  "Move QP = %p out of flush list\n", qp);
			flags = bnxt_re_lock_cqs(qp);
			bnxt_qplib_clean_qp(&qp->qplib_qp);
			bnxt_re_unlock_cqs(qp, flags);
		पूर्ण
	पूर्ण
	अगर (qp_attr_mask & IB_QP_EN_SQD_ASYNC_NOTIFY) अणु
		qp->qplib_qp.modअगरy_flags |=
				CMDQ_MODIFY_QP_MODIFY_MASK_EN_SQD_ASYNC_NOTIFY;
		qp->qplib_qp.en_sqd_async_notअगरy = true;
	पूर्ण
	अगर (qp_attr_mask & IB_QP_ACCESS_FLAGS) अणु
		qp->qplib_qp.modअगरy_flags |= CMDQ_MODIFY_QP_MODIFY_MASK_ACCESS;
		qp->qplib_qp.access =
			__from_ib_access_flags(qp_attr->qp_access_flags);
		/* LOCAL_WRITE access must be set to allow RC receive */
		qp->qplib_qp.access |= BNXT_QPLIB_ACCESS_LOCAL_WRITE;
		/* Temp: Set all params on QP as of now */
		qp->qplib_qp.access |= CMDQ_MODIFY_QP_ACCESS_REMOTE_WRITE;
		qp->qplib_qp.access |= CMDQ_MODIFY_QP_ACCESS_REMOTE_READ;
	पूर्ण
	अगर (qp_attr_mask & IB_QP_PKEY_INDEX) अणु
		qp->qplib_qp.modअगरy_flags |= CMDQ_MODIFY_QP_MODIFY_MASK_PKEY;
		qp->qplib_qp.pkey_index = qp_attr->pkey_index;
	पूर्ण
	अगर (qp_attr_mask & IB_QP_QKEY) अणु
		qp->qplib_qp.modअगरy_flags |= CMDQ_MODIFY_QP_MODIFY_MASK_QKEY;
		qp->qplib_qp.qkey = qp_attr->qkey;
	पूर्ण
	अगर (qp_attr_mask & IB_QP_AV) अणु
		स्थिर काष्ठा ib_global_route *grh =
			rdma_ah_पढ़ो_grh(&qp_attr->ah_attr);
		स्थिर काष्ठा ib_gid_attr *sgid_attr;
		काष्ठा bnxt_re_gid_ctx *ctx;

		qp->qplib_qp.modअगरy_flags |= CMDQ_MODIFY_QP_MODIFY_MASK_DGID |
				     CMDQ_MODIFY_QP_MODIFY_MASK_FLOW_LABEL |
				     CMDQ_MODIFY_QP_MODIFY_MASK_SGID_INDEX |
				     CMDQ_MODIFY_QP_MODIFY_MASK_HOP_LIMIT |
				     CMDQ_MODIFY_QP_MODIFY_MASK_TRAFFIC_CLASS |
				     CMDQ_MODIFY_QP_MODIFY_MASK_DEST_MAC |
				     CMDQ_MODIFY_QP_MODIFY_MASK_VLAN_ID;
		स_नकल(qp->qplib_qp.ah.dgid.data, grh->dgid.raw,
		       माप(qp->qplib_qp.ah.dgid.data));
		qp->qplib_qp.ah.flow_label = grh->flow_label;
		sgid_attr = grh->sgid_attr;
		/* Get the HW context of the GID. The reference
		 * of GID table entry is alपढ़ोy taken by the caller.
		 */
		ctx = rdma_पढ़ो_gid_hw_context(sgid_attr);
		qp->qplib_qp.ah.sgid_index = ctx->idx;
		qp->qplib_qp.ah.host_sgid_index = grh->sgid_index;
		qp->qplib_qp.ah.hop_limit = grh->hop_limit;
		qp->qplib_qp.ah.traffic_class = grh->traffic_class;
		qp->qplib_qp.ah.sl = rdma_ah_get_sl(&qp_attr->ah_attr);
		ether_addr_copy(qp->qplib_qp.ah.dmac,
				qp_attr->ah_attr.roce.dmac);

		rc = rdma_पढ़ो_gid_l2_fields(sgid_attr, शून्य,
					     &qp->qplib_qp.smac[0]);
		अगर (rc)
			वापस rc;

		nw_type = rdma_gid_attr_network_type(sgid_attr);
		चयन (nw_type) अणु
		हाल RDMA_NETWORK_IPV4:
			qp->qplib_qp.nw_type =
				CMDQ_MODIFY_QP_NETWORK_TYPE_ROCEV2_IPV4;
			अवरोध;
		हाल RDMA_NETWORK_IPV6:
			qp->qplib_qp.nw_type =
				CMDQ_MODIFY_QP_NETWORK_TYPE_ROCEV2_IPV6;
			अवरोध;
		शेष:
			qp->qplib_qp.nw_type =
				CMDQ_MODIFY_QP_NETWORK_TYPE_ROCEV1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (qp_attr_mask & IB_QP_PATH_MTU) अणु
		qp->qplib_qp.modअगरy_flags |=
				CMDQ_MODIFY_QP_MODIFY_MASK_PATH_MTU;
		qp->qplib_qp.path_mtu = __from_ib_mtu(qp_attr->path_mtu);
		qp->qplib_qp.mtu = ib_mtu_क्रमागत_to_पूर्णांक(qp_attr->path_mtu);
	पूर्ण अन्यथा अगर (qp_attr->qp_state == IB_QPS_RTR) अणु
		qp->qplib_qp.modअगरy_flags |=
			CMDQ_MODIFY_QP_MODIFY_MASK_PATH_MTU;
		qp->qplib_qp.path_mtu =
			__from_ib_mtu(iboe_get_mtu(rdev->netdev->mtu));
		qp->qplib_qp.mtu =
			ib_mtu_क्रमागत_to_पूर्णांक(iboe_get_mtu(rdev->netdev->mtu));
	पूर्ण

	अगर (qp_attr_mask & IB_QP_TIMEOUT) अणु
		qp->qplib_qp.modअगरy_flags |= CMDQ_MODIFY_QP_MODIFY_MASK_TIMEOUT;
		qp->qplib_qp.समयout = qp_attr->समयout;
	पूर्ण
	अगर (qp_attr_mask & IB_QP_RETRY_CNT) अणु
		qp->qplib_qp.modअगरy_flags |=
				CMDQ_MODIFY_QP_MODIFY_MASK_RETRY_CNT;
		qp->qplib_qp.retry_cnt = qp_attr->retry_cnt;
	पूर्ण
	अगर (qp_attr_mask & IB_QP_RNR_RETRY) अणु
		qp->qplib_qp.modअगरy_flags |=
				CMDQ_MODIFY_QP_MODIFY_MASK_RNR_RETRY;
		qp->qplib_qp.rnr_retry = qp_attr->rnr_retry;
	पूर्ण
	अगर (qp_attr_mask & IB_QP_MIN_RNR_TIMER) अणु
		qp->qplib_qp.modअगरy_flags |=
				CMDQ_MODIFY_QP_MODIFY_MASK_MIN_RNR_TIMER;
		qp->qplib_qp.min_rnr_समयr = qp_attr->min_rnr_समयr;
	पूर्ण
	अगर (qp_attr_mask & IB_QP_RQ_PSN) अणु
		qp->qplib_qp.modअगरy_flags |= CMDQ_MODIFY_QP_MODIFY_MASK_RQ_PSN;
		qp->qplib_qp.rq.psn = qp_attr->rq_psn;
	पूर्ण
	अगर (qp_attr_mask & IB_QP_MAX_QP_RD_ATOMIC) अणु
		qp->qplib_qp.modअगरy_flags |=
				CMDQ_MODIFY_QP_MODIFY_MASK_MAX_RD_ATOMIC;
		/* Cap the max_rd_atomic to device max */
		qp->qplib_qp.max_rd_atomic = min_t(u32, qp_attr->max_rd_atomic,
						   dev_attr->max_qp_rd_atom);
	पूर्ण
	अगर (qp_attr_mask & IB_QP_SQ_PSN) अणु
		qp->qplib_qp.modअगरy_flags |= CMDQ_MODIFY_QP_MODIFY_MASK_SQ_PSN;
		qp->qplib_qp.sq.psn = qp_attr->sq_psn;
	पूर्ण
	अगर (qp_attr_mask & IB_QP_MAX_DEST_RD_ATOMIC) अणु
		अगर (qp_attr->max_dest_rd_atomic >
		    dev_attr->max_qp_init_rd_atom) अणु
			ibdev_err(&rdev->ibdev,
				  "max_dest_rd_atomic requested%d is > dev_max%d",
				  qp_attr->max_dest_rd_atomic,
				  dev_attr->max_qp_init_rd_atom);
			वापस -EINVAL;
		पूर्ण

		qp->qplib_qp.modअगरy_flags |=
				CMDQ_MODIFY_QP_MODIFY_MASK_MAX_DEST_RD_ATOMIC;
		qp->qplib_qp.max_dest_rd_atomic = qp_attr->max_dest_rd_atomic;
	पूर्ण
	अगर (qp_attr_mask & IB_QP_CAP) अणु
		qp->qplib_qp.modअगरy_flags |=
				CMDQ_MODIFY_QP_MODIFY_MASK_SQ_SIZE |
				CMDQ_MODIFY_QP_MODIFY_MASK_RQ_SIZE |
				CMDQ_MODIFY_QP_MODIFY_MASK_SQ_SGE |
				CMDQ_MODIFY_QP_MODIFY_MASK_RQ_SGE |
				CMDQ_MODIFY_QP_MODIFY_MASK_MAX_INLINE_DATA;
		अगर ((qp_attr->cap.max_send_wr >= dev_attr->max_qp_wqes) ||
		    (qp_attr->cap.max_recv_wr >= dev_attr->max_qp_wqes) ||
		    (qp_attr->cap.max_send_sge >= dev_attr->max_qp_sges) ||
		    (qp_attr->cap.max_recv_sge >= dev_attr->max_qp_sges) ||
		    (qp_attr->cap.max_अंतरभूत_data >=
						dev_attr->max_अंतरभूत_data)) अणु
			ibdev_err(&rdev->ibdev,
				  "Create QP failed - max exceeded");
			वापस -EINVAL;
		पूर्ण
		entries = roundup_घात_of_two(qp_attr->cap.max_send_wr);
		qp->qplib_qp.sq.max_wqe = min_t(u32, entries,
						dev_attr->max_qp_wqes + 1);
		qp->qplib_qp.sq.q_full_delta = qp->qplib_qp.sq.max_wqe -
						qp_attr->cap.max_send_wr;
		/*
		 * Reserving one slot क्रम Phantom WQE. Some application can
		 * post one extra entry in this हाल. Allowing this to aव्योम
		 * unexpected Queue full condition
		 */
		qp->qplib_qp.sq.q_full_delta -= 1;
		qp->qplib_qp.sq.max_sge = qp_attr->cap.max_send_sge;
		अगर (qp->qplib_qp.rq.max_wqe) अणु
			entries = roundup_घात_of_two(qp_attr->cap.max_recv_wr);
			qp->qplib_qp.rq.max_wqe =
				min_t(u32, entries, dev_attr->max_qp_wqes + 1);
			qp->qplib_qp.rq.q_full_delta = qp->qplib_qp.rq.max_wqe -
						       qp_attr->cap.max_recv_wr;
			qp->qplib_qp.rq.max_sge = qp_attr->cap.max_recv_sge;
		पूर्ण अन्यथा अणु
			/* SRQ was used prior, just ignore the RQ caps */
		पूर्ण
	पूर्ण
	अगर (qp_attr_mask & IB_QP_DEST_QPN) अणु
		qp->qplib_qp.modअगरy_flags |=
				CMDQ_MODIFY_QP_MODIFY_MASK_DEST_QP_ID;
		qp->qplib_qp.dest_qpn = qp_attr->dest_qp_num;
	पूर्ण
	rc = bnxt_qplib_modअगरy_qp(&rdev->qplib_res, &qp->qplib_qp);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "Failed to modify HW QP");
		वापस rc;
	पूर्ण
	अगर (ib_qp->qp_type == IB_QPT_GSI && rdev->gsi_ctx.gsi_sqp)
		rc = bnxt_re_modअगरy_shaकरोw_qp(rdev, qp, qp_attr_mask);
	वापस rc;
पूर्ण

पूर्णांक bnxt_re_query_qp(काष्ठा ib_qp *ib_qp, काष्ठा ib_qp_attr *qp_attr,
		     पूर्णांक qp_attr_mask, काष्ठा ib_qp_init_attr *qp_init_attr)
अणु
	काष्ठा bnxt_re_qp *qp = container_of(ib_qp, काष्ठा bnxt_re_qp, ib_qp);
	काष्ठा bnxt_re_dev *rdev = qp->rdev;
	काष्ठा bnxt_qplib_qp *qplib_qp;
	पूर्णांक rc;

	qplib_qp = kzalloc(माप(*qplib_qp), GFP_KERNEL);
	अगर (!qplib_qp)
		वापस -ENOMEM;

	qplib_qp->id = qp->qplib_qp.id;
	qplib_qp->ah.host_sgid_index = qp->qplib_qp.ah.host_sgid_index;

	rc = bnxt_qplib_query_qp(&rdev->qplib_res, qplib_qp);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "Failed to query HW QP");
		जाओ out;
	पूर्ण
	qp_attr->qp_state = __to_ib_qp_state(qplib_qp->state);
	qp_attr->cur_qp_state = __to_ib_qp_state(qplib_qp->cur_qp_state);
	qp_attr->en_sqd_async_notअगरy = qplib_qp->en_sqd_async_notअगरy ? 1 : 0;
	qp_attr->qp_access_flags = __to_ib_access_flags(qplib_qp->access);
	qp_attr->pkey_index = qplib_qp->pkey_index;
	qp_attr->qkey = qplib_qp->qkey;
	qp_attr->ah_attr.type = RDMA_AH_ATTR_TYPE_ROCE;
	rdma_ah_set_grh(&qp_attr->ah_attr, शून्य, qplib_qp->ah.flow_label,
			qplib_qp->ah.host_sgid_index,
			qplib_qp->ah.hop_limit,
			qplib_qp->ah.traffic_class);
	rdma_ah_set_dgid_raw(&qp_attr->ah_attr, qplib_qp->ah.dgid.data);
	rdma_ah_set_sl(&qp_attr->ah_attr, qplib_qp->ah.sl);
	ether_addr_copy(qp_attr->ah_attr.roce.dmac, qplib_qp->ah.dmac);
	qp_attr->path_mtu = __to_ib_mtu(qplib_qp->path_mtu);
	qp_attr->समयout = qplib_qp->समयout;
	qp_attr->retry_cnt = qplib_qp->retry_cnt;
	qp_attr->rnr_retry = qplib_qp->rnr_retry;
	qp_attr->min_rnr_समयr = qplib_qp->min_rnr_समयr;
	qp_attr->rq_psn = qplib_qp->rq.psn;
	qp_attr->max_rd_atomic = qplib_qp->max_rd_atomic;
	qp_attr->sq_psn = qplib_qp->sq.psn;
	qp_attr->max_dest_rd_atomic = qplib_qp->max_dest_rd_atomic;
	qp_init_attr->sq_sig_type = qplib_qp->sig_type ? IB_SIGNAL_ALL_WR :
							 IB_SIGNAL_REQ_WR;
	qp_attr->dest_qp_num = qplib_qp->dest_qpn;

	qp_attr->cap.max_send_wr = qp->qplib_qp.sq.max_wqe;
	qp_attr->cap.max_send_sge = qp->qplib_qp.sq.max_sge;
	qp_attr->cap.max_recv_wr = qp->qplib_qp.rq.max_wqe;
	qp_attr->cap.max_recv_sge = qp->qplib_qp.rq.max_sge;
	qp_attr->cap.max_अंतरभूत_data = qp->qplib_qp.max_अंतरभूत_data;
	qp_init_attr->cap = qp_attr->cap;

out:
	kमुक्त(qplib_qp);
	वापस rc;
पूर्ण

/* Routine क्रम sending QP1 packets क्रम RoCE V1 an V2
 */
अटल पूर्णांक bnxt_re_build_qp1_send_v2(काष्ठा bnxt_re_qp *qp,
				     स्थिर काष्ठा ib_send_wr *wr,
				     काष्ठा bnxt_qplib_swqe *wqe,
				     पूर्णांक payload_size)
अणु
	काष्ठा bnxt_re_ah *ah = container_of(ud_wr(wr)->ah, काष्ठा bnxt_re_ah,
					     ib_ah);
	काष्ठा bnxt_qplib_ah *qplib_ah = &ah->qplib_ah;
	स्थिर काष्ठा ib_gid_attr *sgid_attr = ah->ib_ah.sgid_attr;
	काष्ठा bnxt_qplib_sge sge;
	u8 nw_type;
	u16 ether_type;
	जोड़ ib_gid dgid;
	bool is_eth = false;
	bool is_vlan = false;
	bool is_grh = false;
	bool is_udp = false;
	u8 ip_version = 0;
	u16 vlan_id = 0xFFFF;
	व्योम *buf;
	पूर्णांक i, rc = 0;

	स_रखो(&qp->qp1_hdr, 0, माप(qp->qp1_hdr));

	rc = rdma_पढ़ो_gid_l2_fields(sgid_attr, &vlan_id, शून्य);
	अगर (rc)
		वापस rc;

	/* Get network header type क्रम this GID */
	nw_type = rdma_gid_attr_network_type(sgid_attr);
	चयन (nw_type) अणु
	हाल RDMA_NETWORK_IPV4:
		nw_type = BNXT_RE_ROCEV2_IPV4_PACKET;
		अवरोध;
	हाल RDMA_NETWORK_IPV6:
		nw_type = BNXT_RE_ROCEV2_IPV6_PACKET;
		अवरोध;
	शेष:
		nw_type = BNXT_RE_ROCE_V1_PACKET;
		अवरोध;
	पूर्ण
	स_नकल(&dgid.raw, &qplib_ah->dgid, 16);
	is_udp = sgid_attr->gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP;
	अगर (is_udp) अणु
		अगर (ipv6_addr_v4mapped((काष्ठा in6_addr *)&sgid_attr->gid)) अणु
			ip_version = 4;
			ether_type = ETH_P_IP;
		पूर्ण अन्यथा अणु
			ip_version = 6;
			ether_type = ETH_P_IPV6;
		पूर्ण
		is_grh = false;
	पूर्ण अन्यथा अणु
		ether_type = ETH_P_IBOE;
		is_grh = true;
	पूर्ण

	is_eth = true;
	is_vlan = (vlan_id && (vlan_id < 0x1000)) ? true : false;

	ib_ud_header_init(payload_size, !is_eth, is_eth, is_vlan, is_grh,
			  ip_version, is_udp, 0, &qp->qp1_hdr);

	/* ETH */
	ether_addr_copy(qp->qp1_hdr.eth.dmac_h, ah->qplib_ah.dmac);
	ether_addr_copy(qp->qp1_hdr.eth.smac_h, qp->qplib_qp.smac);

	/* For vlan, check the sgid क्रम vlan existence */

	अगर (!is_vlan) अणु
		qp->qp1_hdr.eth.type = cpu_to_be16(ether_type);
	पूर्ण अन्यथा अणु
		qp->qp1_hdr.vlan.type = cpu_to_be16(ether_type);
		qp->qp1_hdr.vlan.tag = cpu_to_be16(vlan_id);
	पूर्ण

	अगर (is_grh || (ip_version == 6)) अणु
		स_नकल(qp->qp1_hdr.grh.source_gid.raw, sgid_attr->gid.raw,
		       माप(sgid_attr->gid));
		स_नकल(qp->qp1_hdr.grh.destination_gid.raw, qplib_ah->dgid.data,
		       माप(sgid_attr->gid));
		qp->qp1_hdr.grh.hop_limit     = qplib_ah->hop_limit;
	पूर्ण

	अगर (ip_version == 4) अणु
		qp->qp1_hdr.ip4.tos = 0;
		qp->qp1_hdr.ip4.id = 0;
		qp->qp1_hdr.ip4.frag_off = htons(IP_DF);
		qp->qp1_hdr.ip4.ttl = qplib_ah->hop_limit;

		स_नकल(&qp->qp1_hdr.ip4.saddr, sgid_attr->gid.raw + 12, 4);
		स_नकल(&qp->qp1_hdr.ip4.daddr, qplib_ah->dgid.data + 12, 4);
		qp->qp1_hdr.ip4.check = ib_ud_ip4_csum(&qp->qp1_hdr);
	पूर्ण

	अगर (is_udp) अणु
		qp->qp1_hdr.udp.dport = htons(ROCE_V2_UDP_DPORT);
		qp->qp1_hdr.udp.sport = htons(0x8CD1);
		qp->qp1_hdr.udp.csum = 0;
	पूर्ण

	/* BTH */
	अगर (wr->opcode == IB_WR_SEND_WITH_IMM) अणु
		qp->qp1_hdr.bth.opcode = IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE;
		qp->qp1_hdr.immediate_present = 1;
	पूर्ण अन्यथा अणु
		qp->qp1_hdr.bth.opcode = IB_OPCODE_UD_SEND_ONLY;
	पूर्ण
	अगर (wr->send_flags & IB_SEND_SOLICITED)
		qp->qp1_hdr.bth.solicited_event = 1;
	/* pad_count */
	qp->qp1_hdr.bth.pad_count = (4 - payload_size) & 3;

	/* P_key क्रम QP1 is क्रम all members */
	qp->qp1_hdr.bth.pkey = cpu_to_be16(0xFFFF);
	qp->qp1_hdr.bth.destination_qpn = IB_QP1;
	qp->qp1_hdr.bth.ack_req = 0;
	qp->send_psn++;
	qp->send_psn &= BTH_PSN_MASK;
	qp->qp1_hdr.bth.psn = cpu_to_be32(qp->send_psn);
	/* DETH */
	/* Use the priviledged Q_Key क्रम QP1 */
	qp->qp1_hdr.deth.qkey = cpu_to_be32(IB_QP1_QKEY);
	qp->qp1_hdr.deth.source_qpn = IB_QP1;

	/* Pack the QP1 to the transmit buffer */
	buf = bnxt_qplib_get_qp1_sq_buf(&qp->qplib_qp, &sge);
	अगर (buf) अणु
		ib_ud_header_pack(&qp->qp1_hdr, buf);
		क्रम (i = wqe->num_sge; i; i--) अणु
			wqe->sg_list[i].addr = wqe->sg_list[i - 1].addr;
			wqe->sg_list[i].lkey = wqe->sg_list[i - 1].lkey;
			wqe->sg_list[i].size = wqe->sg_list[i - 1].size;
		पूर्ण

		/*
		 * Max Header buf size क्रम IPV6 RoCE V2 is 86,
		 * which is same as the QP1 SQ header buffer.
		 * Header buf size क्रम IPV4 RoCE V2 can be 66.
		 * ETH(14) + VLAN(4)+ IP(20) + UDP (8) + BTH(20).
		 * Subtract 20 bytes from QP1 SQ header buf size
		 */
		अगर (is_udp && ip_version == 4)
			sge.size -= 20;
		/*
		 * Max Header buf size क्रम RoCE V1 is 78.
		 * ETH(14) + VLAN(4) + GRH(40) + BTH(20).
		 * Subtract 8 bytes from QP1 SQ header buf size
		 */
		अगर (!is_udp)
			sge.size -= 8;

		/* Subtract 4 bytes क्रम non vlan packets */
		अगर (!is_vlan)
			sge.size -= 4;

		wqe->sg_list[0].addr = sge.addr;
		wqe->sg_list[0].lkey = sge.lkey;
		wqe->sg_list[0].size = sge.size;
		wqe->num_sge++;

	पूर्ण अन्यथा अणु
		ibdev_err(&qp->rdev->ibdev, "QP1 buffer is empty!");
		rc = -ENOMEM;
	पूर्ण
	वापस rc;
पूर्ण

/* For the MAD layer, it only provides the recv SGE the size of
 * ib_grh + MAD datagram.  No Ethernet headers, Ethertype, BTH, DETH,
 * nor RoCE iCRC.  The Cu+ solution must provide buffer क्रम the entire
 * receive packet (334 bytes) with no VLAN and then copy the GRH
 * and the MAD datagram out to the provided SGE.
 */
अटल पूर्णांक bnxt_re_build_qp1_shaकरोw_qp_recv(काष्ठा bnxt_re_qp *qp,
					    स्थिर काष्ठा ib_recv_wr *wr,
					    काष्ठा bnxt_qplib_swqe *wqe,
					    पूर्णांक payload_size)
अणु
	काष्ठा bnxt_re_sqp_entries *sqp_entry;
	काष्ठा bnxt_qplib_sge ref, sge;
	काष्ठा bnxt_re_dev *rdev;
	u32 rq_prod_index;

	rdev = qp->rdev;

	rq_prod_index = bnxt_qplib_get_rq_prod_index(&qp->qplib_qp);

	अगर (!bnxt_qplib_get_qp1_rq_buf(&qp->qplib_qp, &sge))
		वापस -ENOMEM;

	/* Create 1 SGE to receive the entire
	 * ethernet packet
	 */
	/* Save the reference from ULP */
	ref.addr = wqe->sg_list[0].addr;
	ref.lkey = wqe->sg_list[0].lkey;
	ref.size = wqe->sg_list[0].size;

	sqp_entry = &rdev->gsi_ctx.sqp_tbl[rq_prod_index];

	/* SGE 1 */
	wqe->sg_list[0].addr = sge.addr;
	wqe->sg_list[0].lkey = sge.lkey;
	wqe->sg_list[0].size = BNXT_QPLIB_MAX_QP1_RQ_HDR_SIZE_V2;
	sge.size -= wqe->sg_list[0].size;

	sqp_entry->sge.addr = ref.addr;
	sqp_entry->sge.lkey = ref.lkey;
	sqp_entry->sge.size = ref.size;
	/* Store the wrid क्रम reporting completion */
	sqp_entry->wrid = wqe->wr_id;
	/* change the wqe->wrid to table index */
	wqe->wr_id = rq_prod_index;
	वापस 0;
पूर्ण

अटल पूर्णांक is_ud_qp(काष्ठा bnxt_re_qp *qp)
अणु
	वापस (qp->qplib_qp.type == CMDQ_CREATE_QP_TYPE_UD ||
		qp->qplib_qp.type == CMDQ_CREATE_QP_TYPE_GSI);
पूर्ण

अटल पूर्णांक bnxt_re_build_send_wqe(काष्ठा bnxt_re_qp *qp,
				  स्थिर काष्ठा ib_send_wr *wr,
				  काष्ठा bnxt_qplib_swqe *wqe)
अणु
	काष्ठा bnxt_re_ah *ah = शून्य;

	अगर (is_ud_qp(qp)) अणु
		ah = container_of(ud_wr(wr)->ah, काष्ठा bnxt_re_ah, ib_ah);
		wqe->send.q_key = ud_wr(wr)->remote_qkey;
		wqe->send.dst_qp = ud_wr(wr)->remote_qpn;
		wqe->send.avid = ah->qplib_ah.id;
	पूर्ण
	चयन (wr->opcode) अणु
	हाल IB_WR_SEND:
		wqe->type = BNXT_QPLIB_SWQE_TYPE_SEND;
		अवरोध;
	हाल IB_WR_SEND_WITH_IMM:
		wqe->type = BNXT_QPLIB_SWQE_TYPE_SEND_WITH_IMM;
		wqe->send.imm_data = wr->ex.imm_data;
		अवरोध;
	हाल IB_WR_SEND_WITH_INV:
		wqe->type = BNXT_QPLIB_SWQE_TYPE_SEND_WITH_INV;
		wqe->send.inv_key = wr->ex.invalidate_rkey;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (wr->send_flags & IB_SEND_SIGNALED)
		wqe->flags |= BNXT_QPLIB_SWQE_FLAGS_SIGNAL_COMP;
	अगर (wr->send_flags & IB_SEND_FENCE)
		wqe->flags |= BNXT_QPLIB_SWQE_FLAGS_UC_FENCE;
	अगर (wr->send_flags & IB_SEND_SOLICITED)
		wqe->flags |= BNXT_QPLIB_SWQE_FLAGS_SOLICIT_EVENT;
	अगर (wr->send_flags & IB_SEND_INLINE)
		wqe->flags |= BNXT_QPLIB_SWQE_FLAGS_INLINE;

	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_re_build_rdma_wqe(स्थिर काष्ठा ib_send_wr *wr,
				  काष्ठा bnxt_qplib_swqe *wqe)
अणु
	चयन (wr->opcode) अणु
	हाल IB_WR_RDMA_WRITE:
		wqe->type = BNXT_QPLIB_SWQE_TYPE_RDMA_WRITE;
		अवरोध;
	हाल IB_WR_RDMA_WRITE_WITH_IMM:
		wqe->type = BNXT_QPLIB_SWQE_TYPE_RDMA_WRITE_WITH_IMM;
		wqe->rdma.imm_data = wr->ex.imm_data;
		अवरोध;
	हाल IB_WR_RDMA_READ:
		wqe->type = BNXT_QPLIB_SWQE_TYPE_RDMA_READ;
		wqe->rdma.inv_key = wr->ex.invalidate_rkey;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	wqe->rdma.remote_va = rdma_wr(wr)->remote_addr;
	wqe->rdma.r_key = rdma_wr(wr)->rkey;
	अगर (wr->send_flags & IB_SEND_SIGNALED)
		wqe->flags |= BNXT_QPLIB_SWQE_FLAGS_SIGNAL_COMP;
	अगर (wr->send_flags & IB_SEND_FENCE)
		wqe->flags |= BNXT_QPLIB_SWQE_FLAGS_UC_FENCE;
	अगर (wr->send_flags & IB_SEND_SOLICITED)
		wqe->flags |= BNXT_QPLIB_SWQE_FLAGS_SOLICIT_EVENT;
	अगर (wr->send_flags & IB_SEND_INLINE)
		wqe->flags |= BNXT_QPLIB_SWQE_FLAGS_INLINE;

	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_re_build_atomic_wqe(स्थिर काष्ठा ib_send_wr *wr,
				    काष्ठा bnxt_qplib_swqe *wqe)
अणु
	चयन (wr->opcode) अणु
	हाल IB_WR_ATOMIC_CMP_AND_SWP:
		wqe->type = BNXT_QPLIB_SWQE_TYPE_ATOMIC_CMP_AND_SWP;
		wqe->atomic.cmp_data = atomic_wr(wr)->compare_add;
		wqe->atomic.swap_data = atomic_wr(wr)->swap;
		अवरोध;
	हाल IB_WR_ATOMIC_FETCH_AND_ADD:
		wqe->type = BNXT_QPLIB_SWQE_TYPE_ATOMIC_FETCH_AND_ADD;
		wqe->atomic.cmp_data = atomic_wr(wr)->compare_add;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	wqe->atomic.remote_va = atomic_wr(wr)->remote_addr;
	wqe->atomic.r_key = atomic_wr(wr)->rkey;
	अगर (wr->send_flags & IB_SEND_SIGNALED)
		wqe->flags |= BNXT_QPLIB_SWQE_FLAGS_SIGNAL_COMP;
	अगर (wr->send_flags & IB_SEND_FENCE)
		wqe->flags |= BNXT_QPLIB_SWQE_FLAGS_UC_FENCE;
	अगर (wr->send_flags & IB_SEND_SOLICITED)
		wqe->flags |= BNXT_QPLIB_SWQE_FLAGS_SOLICIT_EVENT;
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_re_build_inv_wqe(स्थिर काष्ठा ib_send_wr *wr,
				 काष्ठा bnxt_qplib_swqe *wqe)
अणु
	wqe->type = BNXT_QPLIB_SWQE_TYPE_LOCAL_INV;
	wqe->local_inv.inv_l_key = wr->ex.invalidate_rkey;

	/* Need unconditional fence क्रम local invalidate
	 * opcode to work as expected.
	 */
	wqe->flags |= BNXT_QPLIB_SWQE_FLAGS_UC_FENCE;

	अगर (wr->send_flags & IB_SEND_SIGNALED)
		wqe->flags |= BNXT_QPLIB_SWQE_FLAGS_SIGNAL_COMP;
	अगर (wr->send_flags & IB_SEND_SOLICITED)
		wqe->flags |= BNXT_QPLIB_SWQE_FLAGS_SOLICIT_EVENT;

	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_re_build_reg_wqe(स्थिर काष्ठा ib_reg_wr *wr,
				 काष्ठा bnxt_qplib_swqe *wqe)
अणु
	काष्ठा bnxt_re_mr *mr = container_of(wr->mr, काष्ठा bnxt_re_mr, ib_mr);
	काष्ठा bnxt_qplib_frpl *qplib_frpl = &mr->qplib_frpl;
	पूर्णांक access = wr->access;

	wqe->frmr.pbl_ptr = (__le64 *)qplib_frpl->hwq.pbl_ptr[0];
	wqe->frmr.pbl_dma_ptr = qplib_frpl->hwq.pbl_dma_ptr[0];
	wqe->frmr.page_list = mr->pages;
	wqe->frmr.page_list_len = mr->npages;
	wqe->frmr.levels = qplib_frpl->hwq.level;
	wqe->type = BNXT_QPLIB_SWQE_TYPE_REG_MR;

	/* Need unconditional fence क्रम reg_mr
	 * opcode to function as expected.
	 */

	wqe->flags |= BNXT_QPLIB_SWQE_FLAGS_UC_FENCE;

	अगर (wr->wr.send_flags & IB_SEND_SIGNALED)
		wqe->flags |= BNXT_QPLIB_SWQE_FLAGS_SIGNAL_COMP;

	अगर (access & IB_ACCESS_LOCAL_WRITE)
		wqe->frmr.access_cntl |= SQ_FR_PMR_ACCESS_CNTL_LOCAL_WRITE;
	अगर (access & IB_ACCESS_REMOTE_READ)
		wqe->frmr.access_cntl |= SQ_FR_PMR_ACCESS_CNTL_REMOTE_READ;
	अगर (access & IB_ACCESS_REMOTE_WRITE)
		wqe->frmr.access_cntl |= SQ_FR_PMR_ACCESS_CNTL_REMOTE_WRITE;
	अगर (access & IB_ACCESS_REMOTE_ATOMIC)
		wqe->frmr.access_cntl |= SQ_FR_PMR_ACCESS_CNTL_REMOTE_ATOMIC;
	अगर (access & IB_ACCESS_MW_BIND)
		wqe->frmr.access_cntl |= SQ_FR_PMR_ACCESS_CNTL_WINDOW_BIND;

	wqe->frmr.l_key = wr->key;
	wqe->frmr.length = wr->mr->length;
	wqe->frmr.pbl_pg_sz_log = (wr->mr->page_size >> PAGE_SHIFT_4K) - 1;
	wqe->frmr.va = wr->mr->iova;
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_re_copy_अंतरभूत_data(काष्ठा bnxt_re_dev *rdev,
				    स्थिर काष्ठा ib_send_wr *wr,
				    काष्ठा bnxt_qplib_swqe *wqe)
अणु
	/*  Copy the अंतरभूत data to the data  field */
	u8 *in_data;
	u32 i, sge_len;
	व्योम *sge_addr;

	in_data = wqe->अंतरभूत_data;
	क्रम (i = 0; i < wr->num_sge; i++) अणु
		sge_addr = (व्योम *)(अचिन्हित दीर्घ)
				wr->sg_list[i].addr;
		sge_len = wr->sg_list[i].length;

		अगर ((sge_len + wqe->अंतरभूत_len) >
		    BNXT_QPLIB_SWQE_MAX_INLINE_LENGTH) अणु
			ibdev_err(&rdev->ibdev,
				  "Inline data size requested > supported value");
			वापस -EINVAL;
		पूर्ण
		sge_len = wr->sg_list[i].length;

		स_नकल(in_data, sge_addr, sge_len);
		in_data += wr->sg_list[i].length;
		wqe->अंतरभूत_len += wr->sg_list[i].length;
	पूर्ण
	वापस wqe->अंतरभूत_len;
पूर्ण

अटल पूर्णांक bnxt_re_copy_wr_payload(काष्ठा bnxt_re_dev *rdev,
				   स्थिर काष्ठा ib_send_wr *wr,
				   काष्ठा bnxt_qplib_swqe *wqe)
अणु
	पूर्णांक payload_sz = 0;

	अगर (wr->send_flags & IB_SEND_INLINE)
		payload_sz = bnxt_re_copy_अंतरभूत_data(rdev, wr, wqe);
	अन्यथा
		payload_sz = bnxt_re_build_sgl(wr->sg_list, wqe->sg_list,
					       wqe->num_sge);

	वापस payload_sz;
पूर्ण

अटल व्योम bnxt_ud_qp_hw_stall_workaround(काष्ठा bnxt_re_qp *qp)
अणु
	अगर ((qp->ib_qp.qp_type == IB_QPT_UD ||
	     qp->ib_qp.qp_type == IB_QPT_GSI ||
	     qp->ib_qp.qp_type == IB_QPT_RAW_ETHERTYPE) &&
	     qp->qplib_qp.wqe_cnt == BNXT_RE_UD_QP_HW_STALL) अणु
		पूर्णांक qp_attr_mask;
		काष्ठा ib_qp_attr qp_attr;

		qp_attr_mask = IB_QP_STATE;
		qp_attr.qp_state = IB_QPS_RTS;
		bnxt_re_modअगरy_qp(&qp->ib_qp, &qp_attr, qp_attr_mask, शून्य);
		qp->qplib_qp.wqe_cnt = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_re_post_send_shaकरोw_qp(काष्ठा bnxt_re_dev *rdev,
				       काष्ठा bnxt_re_qp *qp,
				       स्थिर काष्ठा ib_send_wr *wr)
अणु
	पूर्णांक rc = 0, payload_sz = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qp->sq_lock, flags);
	जबतक (wr) अणु
		काष्ठा bnxt_qplib_swqe wqe = अणुपूर्ण;

		/* Common */
		wqe.num_sge = wr->num_sge;
		अगर (wr->num_sge > qp->qplib_qp.sq.max_sge) अणु
			ibdev_err(&rdev->ibdev,
				  "Limit exceeded for Send SGEs");
			rc = -EINVAL;
			जाओ bad;
		पूर्ण

		payload_sz = bnxt_re_copy_wr_payload(qp->rdev, wr, &wqe);
		अगर (payload_sz < 0) अणु
			rc = -EINVAL;
			जाओ bad;
		पूर्ण
		wqe.wr_id = wr->wr_id;

		wqe.type = BNXT_QPLIB_SWQE_TYPE_SEND;

		rc = bnxt_re_build_send_wqe(qp, wr, &wqe);
		अगर (!rc)
			rc = bnxt_qplib_post_send(&qp->qplib_qp, &wqe);
bad:
		अगर (rc) अणु
			ibdev_err(&rdev->ibdev,
				  "Post send failed opcode = %#x rc = %d",
				  wr->opcode, rc);
			अवरोध;
		पूर्ण
		wr = wr->next;
	पूर्ण
	bnxt_qplib_post_send_db(&qp->qplib_qp);
	bnxt_ud_qp_hw_stall_workaround(qp);
	spin_unlock_irqrestore(&qp->sq_lock, flags);
	वापस rc;
पूर्ण

पूर्णांक bnxt_re_post_send(काष्ठा ib_qp *ib_qp, स्थिर काष्ठा ib_send_wr *wr,
		      स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	काष्ठा bnxt_re_qp *qp = container_of(ib_qp, काष्ठा bnxt_re_qp, ib_qp);
	काष्ठा bnxt_qplib_swqe wqe;
	पूर्णांक rc = 0, payload_sz = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qp->sq_lock, flags);
	जबतक (wr) अणु
		/* House keeping */
		स_रखो(&wqe, 0, माप(wqe));

		/* Common */
		wqe.num_sge = wr->num_sge;
		अगर (wr->num_sge > qp->qplib_qp.sq.max_sge) अणु
			ibdev_err(&qp->rdev->ibdev,
				  "Limit exceeded for Send SGEs");
			rc = -EINVAL;
			जाओ bad;
		पूर्ण

		payload_sz = bnxt_re_copy_wr_payload(qp->rdev, wr, &wqe);
		अगर (payload_sz < 0) अणु
			rc = -EINVAL;
			जाओ bad;
		पूर्ण
		wqe.wr_id = wr->wr_id;

		चयन (wr->opcode) अणु
		हाल IB_WR_SEND:
		हाल IB_WR_SEND_WITH_IMM:
			अगर (qp->qplib_qp.type == CMDQ_CREATE_QP1_TYPE_GSI) अणु
				rc = bnxt_re_build_qp1_send_v2(qp, wr, &wqe,
							       payload_sz);
				अगर (rc)
					जाओ bad;
				wqe.rawqp1.lflags |=
					SQ_SEND_RAWETH_QP1_LFLAGS_ROCE_CRC;
			पूर्ण
			चयन (wr->send_flags) अणु
			हाल IB_SEND_IP_CSUM:
				wqe.rawqp1.lflags |=
					SQ_SEND_RAWETH_QP1_LFLAGS_IP_CHKSUM;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			fallthrough;
		हाल IB_WR_SEND_WITH_INV:
			rc = bnxt_re_build_send_wqe(qp, wr, &wqe);
			अवरोध;
		हाल IB_WR_RDMA_WRITE:
		हाल IB_WR_RDMA_WRITE_WITH_IMM:
		हाल IB_WR_RDMA_READ:
			rc = bnxt_re_build_rdma_wqe(wr, &wqe);
			अवरोध;
		हाल IB_WR_ATOMIC_CMP_AND_SWP:
		हाल IB_WR_ATOMIC_FETCH_AND_ADD:
			rc = bnxt_re_build_atomic_wqe(wr, &wqe);
			अवरोध;
		हाल IB_WR_RDMA_READ_WITH_INV:
			ibdev_err(&qp->rdev->ibdev,
				  "RDMA Read with Invalidate is not supported");
			rc = -EINVAL;
			जाओ bad;
		हाल IB_WR_LOCAL_INV:
			rc = bnxt_re_build_inv_wqe(wr, &wqe);
			अवरोध;
		हाल IB_WR_REG_MR:
			rc = bnxt_re_build_reg_wqe(reg_wr(wr), &wqe);
			अवरोध;
		शेष:
			/* Unsupported WRs */
			ibdev_err(&qp->rdev->ibdev,
				  "WR (%#x) is not supported", wr->opcode);
			rc = -EINVAL;
			जाओ bad;
		पूर्ण
		अगर (!rc)
			rc = bnxt_qplib_post_send(&qp->qplib_qp, &wqe);
bad:
		अगर (rc) अणु
			ibdev_err(&qp->rdev->ibdev,
				  "post_send failed op:%#x qps = %#x rc = %d\n",
				  wr->opcode, qp->qplib_qp.state, rc);
			*bad_wr = wr;
			अवरोध;
		पूर्ण
		wr = wr->next;
	पूर्ण
	bnxt_qplib_post_send_db(&qp->qplib_qp);
	bnxt_ud_qp_hw_stall_workaround(qp);
	spin_unlock_irqrestore(&qp->sq_lock, flags);

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_re_post_recv_shaकरोw_qp(काष्ठा bnxt_re_dev *rdev,
				       काष्ठा bnxt_re_qp *qp,
				       स्थिर काष्ठा ib_recv_wr *wr)
अणु
	काष्ठा bnxt_qplib_swqe wqe;
	पूर्णांक rc = 0;

	स_रखो(&wqe, 0, माप(wqe));
	जबतक (wr) अणु
		/* House keeping */
		स_रखो(&wqe, 0, माप(wqe));

		/* Common */
		wqe.num_sge = wr->num_sge;
		अगर (wr->num_sge > qp->qplib_qp.rq.max_sge) अणु
			ibdev_err(&rdev->ibdev,
				  "Limit exceeded for Receive SGEs");
			rc = -EINVAL;
			अवरोध;
		पूर्ण
		bnxt_re_build_sgl(wr->sg_list, wqe.sg_list, wr->num_sge);
		wqe.wr_id = wr->wr_id;
		wqe.type = BNXT_QPLIB_SWQE_TYPE_RECV;

		rc = bnxt_qplib_post_recv(&qp->qplib_qp, &wqe);
		अगर (rc)
			अवरोध;

		wr = wr->next;
	पूर्ण
	अगर (!rc)
		bnxt_qplib_post_recv_db(&qp->qplib_qp);
	वापस rc;
पूर्ण

पूर्णांक bnxt_re_post_recv(काष्ठा ib_qp *ib_qp, स्थिर काष्ठा ib_recv_wr *wr,
		      स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा bnxt_re_qp *qp = container_of(ib_qp, काष्ठा bnxt_re_qp, ib_qp);
	काष्ठा bnxt_qplib_swqe wqe;
	पूर्णांक rc = 0, payload_sz = 0;
	अचिन्हित दीर्घ flags;
	u32 count = 0;

	spin_lock_irqsave(&qp->rq_lock, flags);
	जबतक (wr) अणु
		/* House keeping */
		स_रखो(&wqe, 0, माप(wqe));

		/* Common */
		wqe.num_sge = wr->num_sge;
		अगर (wr->num_sge > qp->qplib_qp.rq.max_sge) अणु
			ibdev_err(&qp->rdev->ibdev,
				  "Limit exceeded for Receive SGEs");
			rc = -EINVAL;
			*bad_wr = wr;
			अवरोध;
		पूर्ण

		payload_sz = bnxt_re_build_sgl(wr->sg_list, wqe.sg_list,
					       wr->num_sge);
		wqe.wr_id = wr->wr_id;
		wqe.type = BNXT_QPLIB_SWQE_TYPE_RECV;

		अगर (ib_qp->qp_type == IB_QPT_GSI &&
		    qp->qplib_qp.type != CMDQ_CREATE_QP_TYPE_GSI)
			rc = bnxt_re_build_qp1_shaकरोw_qp_recv(qp, wr, &wqe,
							      payload_sz);
		अगर (!rc)
			rc = bnxt_qplib_post_recv(&qp->qplib_qp, &wqe);
		अगर (rc) अणु
			*bad_wr = wr;
			अवरोध;
		पूर्ण

		/* Ring DB अगर the RQEs posted reaches a threshold value */
		अगर (++count >= BNXT_RE_RQ_WQE_THRESHOLD) अणु
			bnxt_qplib_post_recv_db(&qp->qplib_qp);
			count = 0;
		पूर्ण

		wr = wr->next;
	पूर्ण

	अगर (count)
		bnxt_qplib_post_recv_db(&qp->qplib_qp);

	spin_unlock_irqrestore(&qp->rq_lock, flags);

	वापस rc;
पूर्ण

/* Completion Queues */
पूर्णांक bnxt_re_destroy_cq(काष्ठा ib_cq *ib_cq, काष्ठा ib_udata *udata)
अणु
	काष्ठा bnxt_re_cq *cq;
	काष्ठा bnxt_qplib_nq *nq;
	काष्ठा bnxt_re_dev *rdev;

	cq = container_of(ib_cq, काष्ठा bnxt_re_cq, ib_cq);
	rdev = cq->rdev;
	nq = cq->qplib_cq.nq;

	bnxt_qplib_destroy_cq(&rdev->qplib_res, &cq->qplib_cq);
	ib_umem_release(cq->umem);

	atomic_dec(&rdev->cq_count);
	nq->budget--;
	kमुक्त(cq->cql);
	वापस 0;
पूर्ण

पूर्णांक bnxt_re_create_cq(काष्ठा ib_cq *ibcq, स्थिर काष्ठा ib_cq_init_attr *attr,
		      काष्ठा ib_udata *udata)
अणु
	काष्ठा bnxt_re_dev *rdev = to_bnxt_re_dev(ibcq->device, ibdev);
	काष्ठा bnxt_qplib_dev_attr *dev_attr = &rdev->dev_attr;
	काष्ठा bnxt_re_cq *cq = container_of(ibcq, काष्ठा bnxt_re_cq, ib_cq);
	पूर्णांक rc, entries;
	पूर्णांक cqe = attr->cqe;
	काष्ठा bnxt_qplib_nq *nq = शून्य;
	अचिन्हित पूर्णांक nq_alloc_cnt;

	अगर (attr->flags)
		वापस -EOPNOTSUPP;

	/* Validate CQ fields */
	अगर (cqe < 1 || cqe > dev_attr->max_cq_wqes) अणु
		ibdev_err(&rdev->ibdev, "Failed to create CQ -max exceeded");
		वापस -EINVAL;
	पूर्ण

	cq->rdev = rdev;
	cq->qplib_cq.cq_handle = (u64)(अचिन्हित दीर्घ)(&cq->qplib_cq);

	entries = roundup_घात_of_two(cqe + 1);
	अगर (entries > dev_attr->max_cq_wqes + 1)
		entries = dev_attr->max_cq_wqes + 1;

	cq->qplib_cq.sg_info.pgsize = PAGE_SIZE;
	cq->qplib_cq.sg_info.pgshft = PAGE_SHIFT;
	अगर (udata) अणु
		काष्ठा bnxt_re_cq_req req;
		काष्ठा bnxt_re_ucontext *uctx = rdma_udata_to_drv_context(
			udata, काष्ठा bnxt_re_ucontext, ib_uctx);
		अगर (ib_copy_from_udata(&req, udata, माप(req))) अणु
			rc = -EFAULT;
			जाओ fail;
		पूर्ण

		cq->umem = ib_umem_get(&rdev->ibdev, req.cq_va,
				       entries * माप(काष्ठा cq_base),
				       IB_ACCESS_LOCAL_WRITE);
		अगर (IS_ERR(cq->umem)) अणु
			rc = PTR_ERR(cq->umem);
			जाओ fail;
		पूर्ण
		cq->qplib_cq.sg_info.umem = cq->umem;
		cq->qplib_cq.dpi = &uctx->dpi;
	पूर्ण अन्यथा अणु
		cq->max_cql = min_t(u32, entries, MAX_CQL_PER_POLL);
		cq->cql = kसुस्मृति(cq->max_cql, माप(काष्ठा bnxt_qplib_cqe),
				  GFP_KERNEL);
		अगर (!cq->cql) अणु
			rc = -ENOMEM;
			जाओ fail;
		पूर्ण

		cq->qplib_cq.dpi = &rdev->dpi_privileged;
	पूर्ण
	/*
	 * Allocating the NQ in a round robin fashion. nq_alloc_cnt is a
	 * used क्रम getting the NQ index.
	 */
	nq_alloc_cnt = atomic_inc_वापस(&rdev->nq_alloc_cnt);
	nq = &rdev->nq[nq_alloc_cnt % (rdev->num_msix - 1)];
	cq->qplib_cq.max_wqe = entries;
	cq->qplib_cq.cnq_hw_ring_id = nq->ring_id;
	cq->qplib_cq.nq	= nq;

	rc = bnxt_qplib_create_cq(&rdev->qplib_res, &cq->qplib_cq);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "Failed to create HW CQ");
		जाओ fail;
	पूर्ण

	cq->ib_cq.cqe = entries;
	cq->cq_period = cq->qplib_cq.period;
	nq->budget++;

	atomic_inc(&rdev->cq_count);
	spin_lock_init(&cq->cq_lock);

	अगर (udata) अणु
		काष्ठा bnxt_re_cq_resp resp;

		resp.cqid = cq->qplib_cq.id;
		resp.tail = cq->qplib_cq.hwq.cons;
		resp.phase = cq->qplib_cq.period;
		resp.rsvd = 0;
		rc = ib_copy_to_udata(udata, &resp, माप(resp));
		अगर (rc) अणु
			ibdev_err(&rdev->ibdev, "Failed to copy CQ udata");
			bnxt_qplib_destroy_cq(&rdev->qplib_res, &cq->qplib_cq);
			जाओ c2fail;
		पूर्ण
	पूर्ण

	वापस 0;

c2fail:
	ib_umem_release(cq->umem);
fail:
	kमुक्त(cq->cql);
	वापस rc;
पूर्ण

अटल u8 __req_to_ib_wc_status(u8 qstatus)
अणु
	चयन (qstatus) अणु
	हाल CQ_REQ_STATUS_OK:
		वापस IB_WC_SUCCESS;
	हाल CQ_REQ_STATUS_BAD_RESPONSE_ERR:
		वापस IB_WC_BAD_RESP_ERR;
	हाल CQ_REQ_STATUS_LOCAL_LENGTH_ERR:
		वापस IB_WC_LOC_LEN_ERR;
	हाल CQ_REQ_STATUS_LOCAL_QP_OPERATION_ERR:
		वापस IB_WC_LOC_QP_OP_ERR;
	हाल CQ_REQ_STATUS_LOCAL_PROTECTION_ERR:
		वापस IB_WC_LOC_PROT_ERR;
	हाल CQ_REQ_STATUS_MEMORY_MGT_OPERATION_ERR:
		वापस IB_WC_GENERAL_ERR;
	हाल CQ_REQ_STATUS_REMOTE_INVALID_REQUEST_ERR:
		वापस IB_WC_REM_INV_REQ_ERR;
	हाल CQ_REQ_STATUS_REMOTE_ACCESS_ERR:
		वापस IB_WC_REM_ACCESS_ERR;
	हाल CQ_REQ_STATUS_REMOTE_OPERATION_ERR:
		वापस IB_WC_REM_OP_ERR;
	हाल CQ_REQ_STATUS_RNR_NAK_RETRY_CNT_ERR:
		वापस IB_WC_RNR_RETRY_EXC_ERR;
	हाल CQ_REQ_STATUS_TRANSPORT_RETRY_CNT_ERR:
		वापस IB_WC_RETRY_EXC_ERR;
	हाल CQ_REQ_STATUS_WORK_REQUEST_FLUSHED_ERR:
		वापस IB_WC_WR_FLUSH_ERR;
	शेष:
		वापस IB_WC_GENERAL_ERR;
	पूर्ण
	वापस 0;
पूर्ण

अटल u8 __rawqp1_to_ib_wc_status(u8 qstatus)
अणु
	चयन (qstatus) अणु
	हाल CQ_RES_RAWETH_QP1_STATUS_OK:
		वापस IB_WC_SUCCESS;
	हाल CQ_RES_RAWETH_QP1_STATUS_LOCAL_ACCESS_ERROR:
		वापस IB_WC_LOC_ACCESS_ERR;
	हाल CQ_RES_RAWETH_QP1_STATUS_HW_LOCAL_LENGTH_ERR:
		वापस IB_WC_LOC_LEN_ERR;
	हाल CQ_RES_RAWETH_QP1_STATUS_LOCAL_PROTECTION_ERR:
		वापस IB_WC_LOC_PROT_ERR;
	हाल CQ_RES_RAWETH_QP1_STATUS_LOCAL_QP_OPERATION_ERR:
		वापस IB_WC_LOC_QP_OP_ERR;
	हाल CQ_RES_RAWETH_QP1_STATUS_MEMORY_MGT_OPERATION_ERR:
		वापस IB_WC_GENERAL_ERR;
	हाल CQ_RES_RAWETH_QP1_STATUS_WORK_REQUEST_FLUSHED_ERR:
		वापस IB_WC_WR_FLUSH_ERR;
	हाल CQ_RES_RAWETH_QP1_STATUS_HW_FLUSH_ERR:
		वापस IB_WC_WR_FLUSH_ERR;
	शेष:
		वापस IB_WC_GENERAL_ERR;
	पूर्ण
पूर्ण

अटल u8 __rc_to_ib_wc_status(u8 qstatus)
अणु
	चयन (qstatus) अणु
	हाल CQ_RES_RC_STATUS_OK:
		वापस IB_WC_SUCCESS;
	हाल CQ_RES_RC_STATUS_LOCAL_ACCESS_ERROR:
		वापस IB_WC_LOC_ACCESS_ERR;
	हाल CQ_RES_RC_STATUS_LOCAL_LENGTH_ERR:
		वापस IB_WC_LOC_LEN_ERR;
	हाल CQ_RES_RC_STATUS_LOCAL_PROTECTION_ERR:
		वापस IB_WC_LOC_PROT_ERR;
	हाल CQ_RES_RC_STATUS_LOCAL_QP_OPERATION_ERR:
		वापस IB_WC_LOC_QP_OP_ERR;
	हाल CQ_RES_RC_STATUS_MEMORY_MGT_OPERATION_ERR:
		वापस IB_WC_GENERAL_ERR;
	हाल CQ_RES_RC_STATUS_REMOTE_INVALID_REQUEST_ERR:
		वापस IB_WC_REM_INV_REQ_ERR;
	हाल CQ_RES_RC_STATUS_WORK_REQUEST_FLUSHED_ERR:
		वापस IB_WC_WR_FLUSH_ERR;
	हाल CQ_RES_RC_STATUS_HW_FLUSH_ERR:
		वापस IB_WC_WR_FLUSH_ERR;
	शेष:
		वापस IB_WC_GENERAL_ERR;
	पूर्ण
पूर्ण

अटल व्योम bnxt_re_process_req_wc(काष्ठा ib_wc *wc, काष्ठा bnxt_qplib_cqe *cqe)
अणु
	चयन (cqe->type) अणु
	हाल BNXT_QPLIB_SWQE_TYPE_SEND:
		wc->opcode = IB_WC_SEND;
		अवरोध;
	हाल BNXT_QPLIB_SWQE_TYPE_SEND_WITH_IMM:
		wc->opcode = IB_WC_SEND;
		wc->wc_flags |= IB_WC_WITH_IMM;
		अवरोध;
	हाल BNXT_QPLIB_SWQE_TYPE_SEND_WITH_INV:
		wc->opcode = IB_WC_SEND;
		wc->wc_flags |= IB_WC_WITH_INVALIDATE;
		अवरोध;
	हाल BNXT_QPLIB_SWQE_TYPE_RDMA_WRITE:
		wc->opcode = IB_WC_RDMA_WRITE;
		अवरोध;
	हाल BNXT_QPLIB_SWQE_TYPE_RDMA_WRITE_WITH_IMM:
		wc->opcode = IB_WC_RDMA_WRITE;
		wc->wc_flags |= IB_WC_WITH_IMM;
		अवरोध;
	हाल BNXT_QPLIB_SWQE_TYPE_RDMA_READ:
		wc->opcode = IB_WC_RDMA_READ;
		अवरोध;
	हाल BNXT_QPLIB_SWQE_TYPE_ATOMIC_CMP_AND_SWP:
		wc->opcode = IB_WC_COMP_SWAP;
		अवरोध;
	हाल BNXT_QPLIB_SWQE_TYPE_ATOMIC_FETCH_AND_ADD:
		wc->opcode = IB_WC_FETCH_ADD;
		अवरोध;
	हाल BNXT_QPLIB_SWQE_TYPE_LOCAL_INV:
		wc->opcode = IB_WC_LOCAL_INV;
		अवरोध;
	हाल BNXT_QPLIB_SWQE_TYPE_REG_MR:
		wc->opcode = IB_WC_REG_MR;
		अवरोध;
	शेष:
		wc->opcode = IB_WC_SEND;
		अवरोध;
	पूर्ण

	wc->status = __req_to_ib_wc_status(cqe->status);
पूर्ण

अटल पूर्णांक bnxt_re_check_packet_type(u16 raweth_qp1_flags,
				     u16 raweth_qp1_flags2)
अणु
	bool is_ipv6 = false, is_ipv4 = false;

	/* raweth_qp1_flags Bit 9-6 indicates itype */
	अगर ((raweth_qp1_flags & CQ_RES_RAWETH_QP1_RAWETH_QP1_FLAGS_ITYPE_ROCE)
	    != CQ_RES_RAWETH_QP1_RAWETH_QP1_FLAGS_ITYPE_ROCE)
		वापस -1;

	अगर (raweth_qp1_flags2 &
	    CQ_RES_RAWETH_QP1_RAWETH_QP1_FLAGS2_IP_CS_CALC &&
	    raweth_qp1_flags2 &
	    CQ_RES_RAWETH_QP1_RAWETH_QP1_FLAGS2_L4_CS_CALC) अणु
		/* raweth_qp1_flags2 Bit 8 indicates ip_type. 0-v4 1 - v6 */
		(raweth_qp1_flags2 &
		 CQ_RES_RAWETH_QP1_RAWETH_QP1_FLAGS2_IP_TYPE) ?
			(is_ipv6 = true) : (is_ipv4 = true);
		वापस ((is_ipv6) ?
			 BNXT_RE_ROCEV2_IPV6_PACKET :
			 BNXT_RE_ROCEV2_IPV4_PACKET);
	पूर्ण अन्यथा अणु
		वापस BNXT_RE_ROCE_V1_PACKET;
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_re_to_ib_nw_type(पूर्णांक nw_type)
अणु
	u8 nw_hdr_type = 0xFF;

	चयन (nw_type) अणु
	हाल BNXT_RE_ROCE_V1_PACKET:
		nw_hdr_type = RDMA_NETWORK_ROCE_V1;
		अवरोध;
	हाल BNXT_RE_ROCEV2_IPV4_PACKET:
		nw_hdr_type = RDMA_NETWORK_IPV4;
		अवरोध;
	हाल BNXT_RE_ROCEV2_IPV6_PACKET:
		nw_hdr_type = RDMA_NETWORK_IPV6;
		अवरोध;
	पूर्ण
	वापस nw_hdr_type;
पूर्ण

अटल bool bnxt_re_is_loopback_packet(काष्ठा bnxt_re_dev *rdev,
				       व्योम *rq_hdr_buf)
अणु
	u8 *पंचांगp_buf = शून्य;
	काष्ठा ethhdr *eth_hdr;
	u16 eth_type;
	bool rc = false;

	पंचांगp_buf = (u8 *)rq_hdr_buf;
	/*
	 * If dest mac is not same as I/F mac, this could be a
	 * loopback address or multicast address, check whether
	 * it is a loopback packet
	 */
	अगर (!ether_addr_equal(पंचांगp_buf, rdev->netdev->dev_addr)) अणु
		पंचांगp_buf += 4;
		/* Check the  ether type */
		eth_hdr = (काष्ठा ethhdr *)पंचांगp_buf;
		eth_type = ntohs(eth_hdr->h_proto);
		चयन (eth_type) अणु
		हाल ETH_P_IBOE:
			rc = true;
			अवरोध;
		हाल ETH_P_IP:
		हाल ETH_P_IPV6: अणु
			u32 len;
			काष्ठा udphdr *udp_hdr;

			len = (eth_type == ETH_P_IP ? माप(काष्ठा iphdr) :
						      माप(काष्ठा ipv6hdr));
			पंचांगp_buf += माप(काष्ठा ethhdr) + len;
			udp_hdr = (काष्ठा udphdr *)पंचांगp_buf;
			अगर (ntohs(udp_hdr->dest) ==
				    ROCE_V2_UDP_DPORT)
				rc = true;
			अवरोध;
			पूर्ण
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_re_process_raw_qp_pkt_rx(काष्ठा bnxt_re_qp *gsi_qp,
					 काष्ठा bnxt_qplib_cqe *cqe)
अणु
	काष्ठा bnxt_re_dev *rdev = gsi_qp->rdev;
	काष्ठा bnxt_re_sqp_entries *sqp_entry = शून्य;
	काष्ठा bnxt_re_qp *gsi_sqp = rdev->gsi_ctx.gsi_sqp;
	काष्ठा bnxt_re_ah *gsi_sah;
	काष्ठा ib_send_wr *swr;
	काष्ठा ib_ud_wr udwr;
	काष्ठा ib_recv_wr rwr;
	पूर्णांक pkt_type = 0;
	u32 tbl_idx;
	व्योम *rq_hdr_buf;
	dma_addr_t rq_hdr_buf_map;
	dma_addr_t shrq_hdr_buf_map;
	u32 offset = 0;
	u32 skip_bytes = 0;
	काष्ठा ib_sge s_sge[2];
	काष्ठा ib_sge r_sge[2];
	पूर्णांक rc;

	स_रखो(&udwr, 0, माप(udwr));
	स_रखो(&rwr, 0, माप(rwr));
	स_रखो(&s_sge, 0, माप(s_sge));
	स_रखो(&r_sge, 0, माप(r_sge));

	swr = &udwr.wr;
	tbl_idx = cqe->wr_id;

	rq_hdr_buf = gsi_qp->qplib_qp.rq_hdr_buf +
			(tbl_idx * gsi_qp->qplib_qp.rq_hdr_buf_size);
	rq_hdr_buf_map = bnxt_qplib_get_qp_buf_from_index(&gsi_qp->qplib_qp,
							  tbl_idx);

	/* Shaकरोw QP header buffer */
	shrq_hdr_buf_map = bnxt_qplib_get_qp_buf_from_index(&gsi_qp->qplib_qp,
							    tbl_idx);
	sqp_entry = &rdev->gsi_ctx.sqp_tbl[tbl_idx];

	/* Store this cqe */
	स_नकल(&sqp_entry->cqe, cqe, माप(काष्ठा bnxt_qplib_cqe));
	sqp_entry->qp1_qp = gsi_qp;

	/* Find packet type from the cqe */

	pkt_type = bnxt_re_check_packet_type(cqe->raweth_qp1_flags,
					     cqe->raweth_qp1_flags2);
	अगर (pkt_type < 0) अणु
		ibdev_err(&rdev->ibdev, "Invalid packet\n");
		वापस -EINVAL;
	पूर्ण

	/* Adjust the offset क्रम the user buffer and post in the rq */

	अगर (pkt_type == BNXT_RE_ROCEV2_IPV4_PACKET)
		offset = 20;

	/*
	 * QP1 loopback packet has 4 bytes of पूर्णांकernal header beक्रमe
	 * ether header. Skip these four bytes.
	 */
	अगर (bnxt_re_is_loopback_packet(rdev, rq_hdr_buf))
		skip_bytes = 4;

	/* First send SGE . Skip the ether header*/
	s_sge[0].addr = rq_hdr_buf_map + BNXT_QPLIB_MAX_QP1_RQ_ETH_HDR_SIZE
			+ skip_bytes;
	s_sge[0].lkey = 0xFFFFFFFF;
	s_sge[0].length = offset ? BNXT_QPLIB_MAX_GRH_HDR_SIZE_IPV4 :
				BNXT_QPLIB_MAX_GRH_HDR_SIZE_IPV6;

	/* Second Send SGE */
	s_sge[1].addr = s_sge[0].addr + s_sge[0].length +
			BNXT_QPLIB_MAX_QP1_RQ_BDETH_HDR_SIZE;
	अगर (pkt_type != BNXT_RE_ROCE_V1_PACKET)
		s_sge[1].addr += 8;
	s_sge[1].lkey = 0xFFFFFFFF;
	s_sge[1].length = 256;

	/* First recv SGE */

	r_sge[0].addr = shrq_hdr_buf_map;
	r_sge[0].lkey = 0xFFFFFFFF;
	r_sge[0].length = 40;

	r_sge[1].addr = sqp_entry->sge.addr + offset;
	r_sge[1].lkey = sqp_entry->sge.lkey;
	r_sge[1].length = BNXT_QPLIB_MAX_GRH_HDR_SIZE_IPV6 + 256 - offset;

	/* Create receive work request */
	rwr.num_sge = 2;
	rwr.sg_list = r_sge;
	rwr.wr_id = tbl_idx;
	rwr.next = शून्य;

	rc = bnxt_re_post_recv_shaकरोw_qp(rdev, gsi_sqp, &rwr);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev,
			  "Failed to post Rx buffers to shadow QP");
		वापस -ENOMEM;
	पूर्ण

	swr->num_sge = 2;
	swr->sg_list = s_sge;
	swr->wr_id = tbl_idx;
	swr->opcode = IB_WR_SEND;
	swr->next = शून्य;
	gsi_sah = rdev->gsi_ctx.gsi_sah;
	udwr.ah = &gsi_sah->ib_ah;
	udwr.remote_qpn = gsi_sqp->qplib_qp.id;
	udwr.remote_qkey = gsi_sqp->qplib_qp.qkey;

	/* post data received  in the send queue */
	rc = bnxt_re_post_send_shaकरोw_qp(rdev, gsi_sqp, swr);

	वापस 0;
पूर्ण

अटल व्योम bnxt_re_process_res_rawqp1_wc(काष्ठा ib_wc *wc,
					  काष्ठा bnxt_qplib_cqe *cqe)
अणु
	wc->opcode = IB_WC_RECV;
	wc->status = __rawqp1_to_ib_wc_status(cqe->status);
	wc->wc_flags |= IB_WC_GRH;
पूर्ण

अटल bool bnxt_re_check_अगर_vlan_valid(काष्ठा bnxt_re_dev *rdev,
					u16 vlan_id)
अणु
	/*
	 * Check अगर the vlan is configured in the host.  If not configured, it
	 * can be a transparent VLAN. So करोnt report the vlan id.
	 */
	अगर (!__vlan_find_dev_deep_rcu(rdev->netdev,
				      htons(ETH_P_8021Q), vlan_id))
		वापस false;
	वापस true;
पूर्ण

अटल bool bnxt_re_is_vlan_pkt(काष्ठा bnxt_qplib_cqe *orig_cqe,
				u16 *vid, u8 *sl)
अणु
	bool ret = false;
	u32 metadata;
	u16 tpid;

	metadata = orig_cqe->raweth_qp1_metadata;
	अगर (orig_cqe->raweth_qp1_flags2 &
		CQ_RES_RAWETH_QP1_RAWETH_QP1_FLAGS2_META_FORMAT_VLAN) अणु
		tpid = ((metadata &
			 CQ_RES_RAWETH_QP1_RAWETH_QP1_METADATA_TPID_MASK) >>
			 CQ_RES_RAWETH_QP1_RAWETH_QP1_METADATA_TPID_SFT);
		अगर (tpid == ETH_P_8021Q) अणु
			*vid = metadata &
			       CQ_RES_RAWETH_QP1_RAWETH_QP1_METADATA_VID_MASK;
			*sl = (metadata &
			       CQ_RES_RAWETH_QP1_RAWETH_QP1_METADATA_PRI_MASK) >>
			       CQ_RES_RAWETH_QP1_RAWETH_QP1_METADATA_PRI_SFT;
			ret = true;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम bnxt_re_process_res_rc_wc(काष्ठा ib_wc *wc,
				      काष्ठा bnxt_qplib_cqe *cqe)
अणु
	wc->opcode = IB_WC_RECV;
	wc->status = __rc_to_ib_wc_status(cqe->status);

	अगर (cqe->flags & CQ_RES_RC_FLAGS_IMM)
		wc->wc_flags |= IB_WC_WITH_IMM;
	अगर (cqe->flags & CQ_RES_RC_FLAGS_INV)
		wc->wc_flags |= IB_WC_WITH_INVALIDATE;
	अगर ((cqe->flags & (CQ_RES_RC_FLAGS_RDMA | CQ_RES_RC_FLAGS_IMM)) ==
	    (CQ_RES_RC_FLAGS_RDMA | CQ_RES_RC_FLAGS_IMM))
		wc->opcode = IB_WC_RECV_RDMA_WITH_IMM;
पूर्ण

अटल व्योम bnxt_re_process_res_shaकरोw_qp_wc(काष्ठा bnxt_re_qp *gsi_sqp,
					     काष्ठा ib_wc *wc,
					     काष्ठा bnxt_qplib_cqe *cqe)
अणु
	काष्ठा bnxt_re_dev *rdev = gsi_sqp->rdev;
	काष्ठा bnxt_re_qp *gsi_qp = शून्य;
	काष्ठा bnxt_qplib_cqe *orig_cqe = शून्य;
	काष्ठा bnxt_re_sqp_entries *sqp_entry = शून्य;
	पूर्णांक nw_type;
	u32 tbl_idx;
	u16 vlan_id;
	u8 sl;

	tbl_idx = cqe->wr_id;

	sqp_entry = &rdev->gsi_ctx.sqp_tbl[tbl_idx];
	gsi_qp = sqp_entry->qp1_qp;
	orig_cqe = &sqp_entry->cqe;

	wc->wr_id = sqp_entry->wrid;
	wc->byte_len = orig_cqe->length;
	wc->qp = &gsi_qp->ib_qp;

	wc->ex.imm_data = orig_cqe->immdata;
	wc->src_qp = orig_cqe->src_qp;
	स_नकल(wc->smac, orig_cqe->smac, ETH_ALEN);
	अगर (bnxt_re_is_vlan_pkt(orig_cqe, &vlan_id, &sl)) अणु
		अगर (bnxt_re_check_अगर_vlan_valid(rdev, vlan_id)) अणु
			wc->vlan_id = vlan_id;
			wc->sl = sl;
			wc->wc_flags |= IB_WC_WITH_VLAN;
		पूर्ण
	पूर्ण
	wc->port_num = 1;
	wc->venकरोr_err = orig_cqe->status;

	wc->opcode = IB_WC_RECV;
	wc->status = __rawqp1_to_ib_wc_status(orig_cqe->status);
	wc->wc_flags |= IB_WC_GRH;

	nw_type = bnxt_re_check_packet_type(orig_cqe->raweth_qp1_flags,
					    orig_cqe->raweth_qp1_flags2);
	अगर (nw_type >= 0) अणु
		wc->network_hdr_type = bnxt_re_to_ib_nw_type(nw_type);
		wc->wc_flags |= IB_WC_WITH_NETWORK_HDR_TYPE;
	पूर्ण
पूर्ण

अटल व्योम bnxt_re_process_res_ud_wc(काष्ठा bnxt_re_qp *qp,
				      काष्ठा ib_wc *wc,
				      काष्ठा bnxt_qplib_cqe *cqe)
अणु
	u8 nw_type;

	wc->opcode = IB_WC_RECV;
	wc->status = __rc_to_ib_wc_status(cqe->status);

	अगर (cqe->flags & CQ_RES_UD_FLAGS_IMM)
		wc->wc_flags |= IB_WC_WITH_IMM;
	/* report only on GSI QP क्रम Thor */
	अगर (qp->qplib_qp.type == CMDQ_CREATE_QP_TYPE_GSI) अणु
		wc->wc_flags |= IB_WC_GRH;
		स_नकल(wc->smac, cqe->smac, ETH_ALEN);
		wc->wc_flags |= IB_WC_WITH_SMAC;
		अगर (cqe->flags & CQ_RES_UD_FLAGS_META_FORMAT_VLAN) अणु
			wc->vlan_id = (cqe->cfa_meta & 0xFFF);
			अगर (wc->vlan_id < 0x1000)
				wc->wc_flags |= IB_WC_WITH_VLAN;
		पूर्ण
		nw_type = (cqe->flags & CQ_RES_UD_FLAGS_ROCE_IP_VER_MASK) >>
			   CQ_RES_UD_FLAGS_ROCE_IP_VER_SFT;
		wc->network_hdr_type = bnxt_re_to_ib_nw_type(nw_type);
		wc->wc_flags |= IB_WC_WITH_NETWORK_HDR_TYPE;
	पूर्ण

पूर्ण

अटल पूर्णांक send_phantom_wqe(काष्ठा bnxt_re_qp *qp)
अणु
	काष्ठा bnxt_qplib_qp *lib_qp = &qp->qplib_qp;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	spin_lock_irqsave(&qp->sq_lock, flags);

	rc = bnxt_re_bind_fence_mw(lib_qp);
	अगर (!rc) अणु
		lib_qp->sq.phantom_wqe_cnt++;
		ibdev_dbg(&qp->rdev->ibdev,
			  "qp %#x sq->prod %#x sw_prod %#x phantom_wqe_cnt %d\n",
			  lib_qp->id, lib_qp->sq.hwq.prod,
			  HWQ_CMP(lib_qp->sq.hwq.prod, &lib_qp->sq.hwq),
			  lib_qp->sq.phantom_wqe_cnt);
	पूर्ण

	spin_unlock_irqrestore(&qp->sq_lock, flags);
	वापस rc;
पूर्ण

पूर्णांक bnxt_re_poll_cq(काष्ठा ib_cq *ib_cq, पूर्णांक num_entries, काष्ठा ib_wc *wc)
अणु
	काष्ठा bnxt_re_cq *cq = container_of(ib_cq, काष्ठा bnxt_re_cq, ib_cq);
	काष्ठा bnxt_re_qp *qp, *sh_qp;
	काष्ठा bnxt_qplib_cqe *cqe;
	पूर्णांक i, ncqe, budget;
	काष्ठा bnxt_qplib_q *sq;
	काष्ठा bnxt_qplib_qp *lib_qp;
	u32 tbl_idx;
	काष्ठा bnxt_re_sqp_entries *sqp_entry = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cq->cq_lock, flags);
	budget = min_t(u32, num_entries, cq->max_cql);
	num_entries = budget;
	अगर (!cq->cql) अणु
		ibdev_err(&cq->rdev->ibdev, "POLL CQ : no CQL to use");
		जाओ निकास;
	पूर्ण
	cqe = &cq->cql[0];
	जबतक (budget) अणु
		lib_qp = शून्य;
		ncqe = bnxt_qplib_poll_cq(&cq->qplib_cq, cqe, budget, &lib_qp);
		अगर (lib_qp) अणु
			sq = &lib_qp->sq;
			अगर (sq->send_phantom) अणु
				qp = container_of(lib_qp,
						  काष्ठा bnxt_re_qp, qplib_qp);
				अगर (send_phantom_wqe(qp) == -ENOMEM)
					ibdev_err(&cq->rdev->ibdev,
						  "Phantom failed! Scheduled to send again\n");
				अन्यथा
					sq->send_phantom = false;
			पूर्ण
		पूर्ण
		अगर (ncqe < budget)
			ncqe += bnxt_qplib_process_flush_list(&cq->qplib_cq,
							      cqe + ncqe,
							      budget - ncqe);

		अगर (!ncqe)
			अवरोध;

		क्रम (i = 0; i < ncqe; i++, cqe++) अणु
			/* Transcribe each qplib_wqe back to ib_wc */
			स_रखो(wc, 0, माप(*wc));

			wc->wr_id = cqe->wr_id;
			wc->byte_len = cqe->length;
			qp = container_of
				((काष्ठा bnxt_qplib_qp *)
				 (अचिन्हित दीर्घ)(cqe->qp_handle),
				 काष्ठा bnxt_re_qp, qplib_qp);
			अगर (!qp) अणु
				ibdev_err(&cq->rdev->ibdev, "POLL CQ : bad QP handle");
				जारी;
			पूर्ण
			wc->qp = &qp->ib_qp;
			wc->ex.imm_data = cqe->immdata;
			wc->src_qp = cqe->src_qp;
			स_नकल(wc->smac, cqe->smac, ETH_ALEN);
			wc->port_num = 1;
			wc->venकरोr_err = cqe->status;

			चयन (cqe->opcode) अणु
			हाल CQ_BASE_CQE_TYPE_REQ:
				sh_qp = qp->rdev->gsi_ctx.gsi_sqp;
				अगर (sh_qp &&
				    qp->qplib_qp.id == sh_qp->qplib_qp.id) अणु
					/* Handle this completion with
					 * the stored completion
					 */
					स_रखो(wc, 0, माप(*wc));
					जारी;
				पूर्ण
				bnxt_re_process_req_wc(wc, cqe);
				अवरोध;
			हाल CQ_BASE_CQE_TYPE_RES_RAWETH_QP1:
				अगर (!cqe->status) अणु
					पूर्णांक rc = 0;

					rc = bnxt_re_process_raw_qp_pkt_rx
								(qp, cqe);
					अगर (!rc) अणु
						स_रखो(wc, 0, माप(*wc));
						जारी;
					पूर्ण
					cqe->status = -1;
				पूर्ण
				/* Errors need not be looped back.
				 * But change the wr_id to the one
				 * stored in the table
				 */
				tbl_idx = cqe->wr_id;
				sqp_entry = &cq->rdev->gsi_ctx.sqp_tbl[tbl_idx];
				wc->wr_id = sqp_entry->wrid;
				bnxt_re_process_res_rawqp1_wc(wc, cqe);
				अवरोध;
			हाल CQ_BASE_CQE_TYPE_RES_RC:
				bnxt_re_process_res_rc_wc(wc, cqe);
				अवरोध;
			हाल CQ_BASE_CQE_TYPE_RES_UD:
				sh_qp = qp->rdev->gsi_ctx.gsi_sqp;
				अगर (sh_qp &&
				    qp->qplib_qp.id == sh_qp->qplib_qp.id) अणु
					/* Handle this completion with
					 * the stored completion
					 */
					अगर (cqe->status) अणु
						जारी;
					पूर्ण अन्यथा अणु
						bnxt_re_process_res_shaकरोw_qp_wc
								(qp, wc, cqe);
						अवरोध;
					पूर्ण
				पूर्ण
				bnxt_re_process_res_ud_wc(qp, wc, cqe);
				अवरोध;
			शेष:
				ibdev_err(&cq->rdev->ibdev,
					  "POLL CQ : type 0x%x not handled",
					  cqe->opcode);
				जारी;
			पूर्ण
			wc++;
			budget--;
		पूर्ण
	पूर्ण
निकास:
	spin_unlock_irqrestore(&cq->cq_lock, flags);
	वापस num_entries - budget;
पूर्ण

पूर्णांक bnxt_re_req_notअगरy_cq(काष्ठा ib_cq *ib_cq,
			  क्रमागत ib_cq_notअगरy_flags ib_cqn_flags)
अणु
	काष्ठा bnxt_re_cq *cq = container_of(ib_cq, काष्ठा bnxt_re_cq, ib_cq);
	पूर्णांक type = 0, rc = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cq->cq_lock, flags);
	/* Trigger on the very next completion */
	अगर (ib_cqn_flags & IB_CQ_NEXT_COMP)
		type = DBC_DBC_TYPE_CQ_ARMALL;
	/* Trigger on the next solicited completion */
	अन्यथा अगर (ib_cqn_flags & IB_CQ_SOLICITED)
		type = DBC_DBC_TYPE_CQ_ARMSE;

	/* Poll to see अगर there are missed events */
	अगर ((ib_cqn_flags & IB_CQ_REPORT_MISSED_EVENTS) &&
	    !(bnxt_qplib_is_cq_empty(&cq->qplib_cq))) अणु
		rc = 1;
		जाओ निकास;
	पूर्ण
	bnxt_qplib_req_notअगरy_cq(&cq->qplib_cq, type);

निकास:
	spin_unlock_irqrestore(&cq->cq_lock, flags);
	वापस rc;
पूर्ण

/* Memory Regions */
काष्ठा ib_mr *bnxt_re_get_dma_mr(काष्ठा ib_pd *ib_pd, पूर्णांक mr_access_flags)
अणु
	काष्ठा bnxt_re_pd *pd = container_of(ib_pd, काष्ठा bnxt_re_pd, ib_pd);
	काष्ठा bnxt_re_dev *rdev = pd->rdev;
	काष्ठा bnxt_re_mr *mr;
	पूर्णांक rc;

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	mr->rdev = rdev;
	mr->qplib_mr.pd = &pd->qplib_pd;
	mr->qplib_mr.flags = __from_ib_access_flags(mr_access_flags);
	mr->qplib_mr.type = CMDQ_ALLOCATE_MRW_MRW_FLAGS_PMR;

	/* Allocate and रेजिस्टर 0 as the address */
	rc = bnxt_qplib_alloc_mrw(&rdev->qplib_res, &mr->qplib_mr);
	अगर (rc)
		जाओ fail;

	mr->qplib_mr.hwq.level = PBL_LVL_MAX;
	mr->qplib_mr.total_size = -1; /* Infपूर्णांकe length */
	rc = bnxt_qplib_reg_mr(&rdev->qplib_res, &mr->qplib_mr, शून्य, 0,
			       PAGE_SIZE);
	अगर (rc)
		जाओ fail_mr;

	mr->ib_mr.lkey = mr->qplib_mr.lkey;
	अगर (mr_access_flags & (IB_ACCESS_REMOTE_WRITE | IB_ACCESS_REMOTE_READ |
			       IB_ACCESS_REMOTE_ATOMIC))
		mr->ib_mr.rkey = mr->ib_mr.lkey;
	atomic_inc(&rdev->mr_count);

	वापस &mr->ib_mr;

fail_mr:
	bnxt_qplib_मुक्त_mrw(&rdev->qplib_res, &mr->qplib_mr);
fail:
	kमुक्त(mr);
	वापस ERR_PTR(rc);
पूर्ण

पूर्णांक bnxt_re_dereg_mr(काष्ठा ib_mr *ib_mr, काष्ठा ib_udata *udata)
अणु
	काष्ठा bnxt_re_mr *mr = container_of(ib_mr, काष्ठा bnxt_re_mr, ib_mr);
	काष्ठा bnxt_re_dev *rdev = mr->rdev;
	पूर्णांक rc;

	rc = bnxt_qplib_मुक्त_mrw(&rdev->qplib_res, &mr->qplib_mr);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "Dereg MR failed: %#x\n", rc);
		वापस rc;
	पूर्ण

	अगर (mr->pages) अणु
		rc = bnxt_qplib_मुक्त_fast_reg_page_list(&rdev->qplib_res,
							&mr->qplib_frpl);
		kमुक्त(mr->pages);
		mr->npages = 0;
		mr->pages = शून्य;
	पूर्ण
	ib_umem_release(mr->ib_umem);

	kमुक्त(mr);
	atomic_dec(&rdev->mr_count);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_re_set_page(काष्ठा ib_mr *ib_mr, u64 addr)
अणु
	काष्ठा bnxt_re_mr *mr = container_of(ib_mr, काष्ठा bnxt_re_mr, ib_mr);

	अगर (unlikely(mr->npages == mr->qplib_frpl.max_pg_ptrs))
		वापस -ENOMEM;

	mr->pages[mr->npages++] = addr;
	वापस 0;
पूर्ण

पूर्णांक bnxt_re_map_mr_sg(काष्ठा ib_mr *ib_mr, काष्ठा scatterlist *sg, पूर्णांक sg_nents,
		      अचिन्हित पूर्णांक *sg_offset)
अणु
	काष्ठा bnxt_re_mr *mr = container_of(ib_mr, काष्ठा bnxt_re_mr, ib_mr);

	mr->npages = 0;
	वापस ib_sg_to_pages(ib_mr, sg, sg_nents, sg_offset, bnxt_re_set_page);
पूर्ण

काष्ठा ib_mr *bnxt_re_alloc_mr(काष्ठा ib_pd *ib_pd, क्रमागत ib_mr_type type,
			       u32 max_num_sg)
अणु
	काष्ठा bnxt_re_pd *pd = container_of(ib_pd, काष्ठा bnxt_re_pd, ib_pd);
	काष्ठा bnxt_re_dev *rdev = pd->rdev;
	काष्ठा bnxt_re_mr *mr = शून्य;
	पूर्णांक rc;

	अगर (type != IB_MR_TYPE_MEM_REG) अणु
		ibdev_dbg(&rdev->ibdev, "MR type 0x%x not supported", type);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	अगर (max_num_sg > MAX_PBL_LVL_1_PGS)
		वापस ERR_PTR(-EINVAL);

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	mr->rdev = rdev;
	mr->qplib_mr.pd = &pd->qplib_pd;
	mr->qplib_mr.flags = BNXT_QPLIB_FR_PMR;
	mr->qplib_mr.type = CMDQ_ALLOCATE_MRW_MRW_FLAGS_PMR;

	rc = bnxt_qplib_alloc_mrw(&rdev->qplib_res, &mr->qplib_mr);
	अगर (rc)
		जाओ bail;

	mr->ib_mr.lkey = mr->qplib_mr.lkey;
	mr->ib_mr.rkey = mr->ib_mr.lkey;

	mr->pages = kसुस्मृति(max_num_sg, माप(u64), GFP_KERNEL);
	अगर (!mr->pages) अणु
		rc = -ENOMEM;
		जाओ fail;
	पूर्ण
	rc = bnxt_qplib_alloc_fast_reg_page_list(&rdev->qplib_res,
						 &mr->qplib_frpl, max_num_sg);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev,
			  "Failed to allocate HW FR page list");
		जाओ fail_mr;
	पूर्ण

	atomic_inc(&rdev->mr_count);
	वापस &mr->ib_mr;

fail_mr:
	kमुक्त(mr->pages);
fail:
	bnxt_qplib_मुक्त_mrw(&rdev->qplib_res, &mr->qplib_mr);
bail:
	kमुक्त(mr);
	वापस ERR_PTR(rc);
पूर्ण

काष्ठा ib_mw *bnxt_re_alloc_mw(काष्ठा ib_pd *ib_pd, क्रमागत ib_mw_type type,
			       काष्ठा ib_udata *udata)
अणु
	काष्ठा bnxt_re_pd *pd = container_of(ib_pd, काष्ठा bnxt_re_pd, ib_pd);
	काष्ठा bnxt_re_dev *rdev = pd->rdev;
	काष्ठा bnxt_re_mw *mw;
	पूर्णांक rc;

	mw = kzalloc(माप(*mw), GFP_KERNEL);
	अगर (!mw)
		वापस ERR_PTR(-ENOMEM);
	mw->rdev = rdev;
	mw->qplib_mw.pd = &pd->qplib_pd;

	mw->qplib_mw.type = (type == IB_MW_TYPE_1 ?
			       CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE1 :
			       CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE2B);
	rc = bnxt_qplib_alloc_mrw(&rdev->qplib_res, &mw->qplib_mw);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "Allocate MW failed!");
		जाओ fail;
	पूर्ण
	mw->ib_mw.rkey = mw->qplib_mw.rkey;

	atomic_inc(&rdev->mw_count);
	वापस &mw->ib_mw;

fail:
	kमुक्त(mw);
	वापस ERR_PTR(rc);
पूर्ण

पूर्णांक bnxt_re_dealloc_mw(काष्ठा ib_mw *ib_mw)
अणु
	काष्ठा bnxt_re_mw *mw = container_of(ib_mw, काष्ठा bnxt_re_mw, ib_mw);
	काष्ठा bnxt_re_dev *rdev = mw->rdev;
	पूर्णांक rc;

	rc = bnxt_qplib_मुक्त_mrw(&rdev->qplib_res, &mw->qplib_mw);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "Free MW failed: %#x\n", rc);
		वापस rc;
	पूर्ण

	kमुक्त(mw);
	atomic_dec(&rdev->mw_count);
	वापस rc;
पूर्ण

/* uverbs */
काष्ठा ib_mr *bnxt_re_reg_user_mr(काष्ठा ib_pd *ib_pd, u64 start, u64 length,
				  u64 virt_addr, पूर्णांक mr_access_flags,
				  काष्ठा ib_udata *udata)
अणु
	काष्ठा bnxt_re_pd *pd = container_of(ib_pd, काष्ठा bnxt_re_pd, ib_pd);
	काष्ठा bnxt_re_dev *rdev = pd->rdev;
	काष्ठा bnxt_re_mr *mr;
	काष्ठा ib_umem *umem;
	अचिन्हित दीर्घ page_size;
	पूर्णांक umem_pgs, rc;

	अगर (length > BNXT_RE_MAX_MR_SIZE) अणु
		ibdev_err(&rdev->ibdev, "MR Size: %lld > Max supported:%lld\n",
			  length, BNXT_RE_MAX_MR_SIZE);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	mr->rdev = rdev;
	mr->qplib_mr.pd = &pd->qplib_pd;
	mr->qplib_mr.flags = __from_ib_access_flags(mr_access_flags);
	mr->qplib_mr.type = CMDQ_ALLOCATE_MRW_MRW_FLAGS_MR;

	rc = bnxt_qplib_alloc_mrw(&rdev->qplib_res, &mr->qplib_mr);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "Failed to allocate MR");
		जाओ मुक्त_mr;
	पूर्ण
	/* The fixed portion of the rkey is the same as the lkey */
	mr->ib_mr.rkey = mr->qplib_mr.rkey;

	umem = ib_umem_get(&rdev->ibdev, start, length, mr_access_flags);
	अगर (IS_ERR(umem)) अणु
		ibdev_err(&rdev->ibdev, "Failed to get umem");
		rc = -EFAULT;
		जाओ मुक्त_mrw;
	पूर्ण
	mr->ib_umem = umem;

	mr->qplib_mr.va = virt_addr;
	page_size = ib_umem_find_best_pgsz(
		umem, BNXT_RE_PAGE_SIZE_4K | BNXT_RE_PAGE_SIZE_2M, virt_addr);
	अगर (!page_size) अणु
		ibdev_err(&rdev->ibdev, "umem page size unsupported!");
		rc = -EFAULT;
		जाओ मुक्त_umem;
	पूर्ण
	mr->qplib_mr.total_size = length;

	umem_pgs = ib_umem_num_dma_blocks(umem, page_size);
	rc = bnxt_qplib_reg_mr(&rdev->qplib_res, &mr->qplib_mr, umem,
			       umem_pgs, page_size);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "Failed to register user MR");
		जाओ मुक्त_umem;
	पूर्ण

	mr->ib_mr.lkey = mr->qplib_mr.lkey;
	mr->ib_mr.rkey = mr->qplib_mr.lkey;
	atomic_inc(&rdev->mr_count);

	वापस &mr->ib_mr;
मुक्त_umem:
	ib_umem_release(umem);
मुक्त_mrw:
	bnxt_qplib_मुक्त_mrw(&rdev->qplib_res, &mr->qplib_mr);
मुक्त_mr:
	kमुक्त(mr);
	वापस ERR_PTR(rc);
पूर्ण

पूर्णांक bnxt_re_alloc_ucontext(काष्ठा ib_ucontext *ctx, काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = ctx->device;
	काष्ठा bnxt_re_ucontext *uctx =
		container_of(ctx, काष्ठा bnxt_re_ucontext, ib_uctx);
	काष्ठा bnxt_re_dev *rdev = to_bnxt_re_dev(ibdev, ibdev);
	काष्ठा bnxt_qplib_dev_attr *dev_attr = &rdev->dev_attr;
	काष्ठा bnxt_re_uctx_resp resp;
	u32 chip_met_rev_num = 0;
	पूर्णांक rc;

	ibdev_dbg(ibdev, "ABI version requested %u", ibdev->ops.uverbs_abi_ver);

	अगर (ibdev->ops.uverbs_abi_ver != BNXT_RE_ABI_VERSION) अणु
		ibdev_dbg(ibdev, " is different from the device %d ",
			  BNXT_RE_ABI_VERSION);
		वापस -EPERM;
	पूर्ण

	uctx->rdev = rdev;

	uctx->shpg = (व्योम *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!uctx->shpg) अणु
		rc = -ENOMEM;
		जाओ fail;
	पूर्ण
	spin_lock_init(&uctx->sh_lock);

	resp.comp_mask = BNXT_RE_UCNTX_CMASK_HAVE_CCTX;
	chip_met_rev_num = rdev->chip_ctx->chip_num;
	chip_met_rev_num |= ((u32)rdev->chip_ctx->chip_rev & 0xFF) <<
			     BNXT_RE_CHIP_ID0_CHIP_REV_SFT;
	chip_met_rev_num |= ((u32)rdev->chip_ctx->chip_metal & 0xFF) <<
			     BNXT_RE_CHIP_ID0_CHIP_MET_SFT;
	resp.chip_id0 = chip_met_rev_num;
	/* Future extension of chip info */
	resp.chip_id1 = 0;
	/*Temp, Use xa_alloc instead */
	resp.dev_id = rdev->en_dev->pdev->devfn;
	resp.max_qp = rdev->qplib_ctx.qpc_count;
	resp.pg_size = PAGE_SIZE;
	resp.cqe_sz = माप(काष्ठा cq_base);
	resp.max_cqd = dev_attr->max_cq_wqes;
	resp.rsvd    = 0;

	rc = ib_copy_to_udata(udata, &resp, min(udata->outlen, माप(resp)));
	अगर (rc) अणु
		ibdev_err(ibdev, "Failed to copy user context");
		rc = -EFAULT;
		जाओ cfail;
	पूर्ण

	वापस 0;
cfail:
	मुक्त_page((अचिन्हित दीर्घ)uctx->shpg);
	uctx->shpg = शून्य;
fail:
	वापस rc;
पूर्ण

व्योम bnxt_re_dealloc_ucontext(काष्ठा ib_ucontext *ib_uctx)
अणु
	काष्ठा bnxt_re_ucontext *uctx = container_of(ib_uctx,
						   काष्ठा bnxt_re_ucontext,
						   ib_uctx);

	काष्ठा bnxt_re_dev *rdev = uctx->rdev;

	अगर (uctx->shpg)
		मुक्त_page((अचिन्हित दीर्घ)uctx->shpg);

	अगर (uctx->dpi.dbr) अणु
		/* Free DPI only अगर this is the first PD allocated by the
		 * application and mark the context dpi as शून्य
		 */
		bnxt_qplib_dealloc_dpi(&rdev->qplib_res,
				       &rdev->qplib_res.dpi_tbl, &uctx->dpi);
		uctx->dpi.dbr = शून्य;
	पूर्ण
पूर्ण

/* Helper function to mmap the भव memory from user app */
पूर्णांक bnxt_re_mmap(काष्ठा ib_ucontext *ib_uctx, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा bnxt_re_ucontext *uctx = container_of(ib_uctx,
						   काष्ठा bnxt_re_ucontext,
						   ib_uctx);
	काष्ठा bnxt_re_dev *rdev = uctx->rdev;
	u64 pfn;

	अगर (vma->vm_end - vma->vm_start != PAGE_SIZE)
		वापस -EINVAL;

	अगर (vma->vm_pgoff) अणु
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
		अगर (io_remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
				       PAGE_SIZE, vma->vm_page_prot)) अणु
			ibdev_err(&rdev->ibdev, "Failed to map DPI");
			वापस -EAGAIN;
		पूर्ण
	पूर्ण अन्यथा अणु
		pfn = virt_to_phys(uctx->shpg) >> PAGE_SHIFT;
		अगर (remap_pfn_range(vma, vma->vm_start,
				    pfn, PAGE_SIZE, vma->vm_page_prot)) अणु
			ibdev_err(&rdev->ibdev, "Failed to map shared page");
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
