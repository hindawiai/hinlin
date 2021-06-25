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
 * Description: Main component of the bnxt_re driver
 */

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/rculist.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci.h>
#समावेश <net/dcbnl.h>
#समावेश <net/ipv6.h>
#समावेश <net/addrconf.h>
#समावेश <linux/अगर_ether.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_addr.h>

#समावेश "bnxt_ulp.h"
#समावेश "roce_hsi.h"
#समावेश "qplib_res.h"
#समावेश "qplib_sp.h"
#समावेश "qplib_fp.h"
#समावेश "qplib_rcfw.h"
#समावेश "bnxt_re.h"
#समावेश "ib_verbs.h"
#समावेश <rdma/bnxt_re-abi.h>
#समावेश "bnxt.h"
#समावेश "hw_counters.h"

अटल अक्षर version[] =
		BNXT_RE_DESC "\n";

MODULE_AUTHOR("Eddie Wai <eddie.wai@broadcom.com>");
MODULE_DESCRIPTION(BNXT_RE_DESC " Driver");
MODULE_LICENSE("Dual BSD/GPL");

/* globals */
अटल काष्ठा list_head bnxt_re_dev_list = LIST_HEAD_INIT(bnxt_re_dev_list);
/* Mutex to protect the list of bnxt_re devices added */
अटल DEFINE_MUTEX(bnxt_re_dev_lock);
अटल काष्ठा workqueue_काष्ठा *bnxt_re_wq;
अटल व्योम bnxt_re_हटाओ_device(काष्ठा bnxt_re_dev *rdev);
अटल व्योम bnxt_re_dealloc_driver(काष्ठा ib_device *ib_dev);
अटल व्योम bnxt_re_stop_irq(व्योम *handle);
अटल व्योम bnxt_re_dev_stop(काष्ठा bnxt_re_dev *rdev);

अटल व्योम bnxt_re_set_drv_mode(काष्ठा bnxt_re_dev *rdev, u8 mode)
अणु
	काष्ठा bnxt_qplib_chip_ctx *cctx;

	cctx = rdev->chip_ctx;
	cctx->modes.wqe_mode = bnxt_qplib_is_chip_gen_p5(rdev->chip_ctx) ?
			       mode : BNXT_QPLIB_WQE_MODE_STATIC;
पूर्ण

अटल व्योम bnxt_re_destroy_chip_ctx(काष्ठा bnxt_re_dev *rdev)
अणु
	काष्ठा bnxt_qplib_chip_ctx *chip_ctx;

	अगर (!rdev->chip_ctx)
		वापस;
	chip_ctx = rdev->chip_ctx;
	rdev->chip_ctx = शून्य;
	rdev->rcfw.res = शून्य;
	rdev->qplib_res.cctx = शून्य;
	rdev->qplib_res.pdev = शून्य;
	rdev->qplib_res.netdev = शून्य;
	kमुक्त(chip_ctx);
पूर्ण

अटल पूर्णांक bnxt_re_setup_chip_ctx(काष्ठा bnxt_re_dev *rdev, u8 wqe_mode)
अणु
	काष्ठा bnxt_qplib_chip_ctx *chip_ctx;
	काष्ठा bnxt_en_dev *en_dev;
	काष्ठा bnxt *bp;

	en_dev = rdev->en_dev;
	bp = netdev_priv(en_dev->net);

	chip_ctx = kzalloc(माप(*chip_ctx), GFP_KERNEL);
	अगर (!chip_ctx)
		वापस -ENOMEM;
	chip_ctx->chip_num = bp->chip_num;

	rdev->chip_ctx = chip_ctx;
	/* rest members to follow eventually */

	rdev->qplib_res.cctx = rdev->chip_ctx;
	rdev->rcfw.res = &rdev->qplib_res;

	bnxt_re_set_drv_mode(rdev, wqe_mode);
	वापस 0;
पूर्ण

/* SR-IOV helper functions */

अटल व्योम bnxt_re_get_sriov_func_type(काष्ठा bnxt_re_dev *rdev)
अणु
	काष्ठा bnxt *bp;

	bp = netdev_priv(rdev->en_dev->net);
	अगर (BNXT_VF(bp))
		rdev->is_virtfn = 1;
पूर्ण

/* Set the maximum number of each resource that the driver actually wants
 * to allocate. This may be up to the maximum number the firmware has
 * reserved क्रम the function. The driver may choose to allocate fewer
 * resources than the firmware maximum.
 */
अटल व्योम bnxt_re_limit_pf_res(काष्ठा bnxt_re_dev *rdev)
अणु
	काष्ठा bnxt_qplib_dev_attr *attr;
	काष्ठा bnxt_qplib_ctx *ctx;
	पूर्णांक i;

	attr = &rdev->dev_attr;
	ctx = &rdev->qplib_ctx;

	ctx->qpc_count = min_t(u32, BNXT_RE_MAX_QPC_COUNT,
			       attr->max_qp);
	ctx->mrw_count = BNXT_RE_MAX_MRW_COUNT_256K;
	/* Use max_mr from fw since max_mrw करोes not get set */
	ctx->mrw_count = min_t(u32, ctx->mrw_count, attr->max_mr);
	ctx->srqc_count = min_t(u32, BNXT_RE_MAX_SRQC_COUNT,
				attr->max_srq);
	ctx->cq_count = min_t(u32, BNXT_RE_MAX_CQ_COUNT, attr->max_cq);
	अगर (!bnxt_qplib_is_chip_gen_p5(rdev->chip_ctx))
		क्रम (i = 0; i < MAX_TQM_ALLOC_REQ; i++)
			rdev->qplib_ctx.tqm_ctx.qcount[i] =
			rdev->dev_attr.tqm_alloc_reqs[i];
पूर्ण

अटल व्योम bnxt_re_limit_vf_res(काष्ठा bnxt_qplib_ctx *qplib_ctx, u32 num_vf)
अणु
	काष्ठा bnxt_qplib_vf_res *vf_res;
	u32 mrws = 0;
	u32 vf_pct;
	u32 nvfs;

	vf_res = &qplib_ctx->vf_res;
	/*
	 * Reserve a set of resources क्रम the PF. Divide the reमुख्यing
	 * resources among the VFs
	 */
	vf_pct = 100 - BNXT_RE_PCT_RSVD_FOR_PF;
	nvfs = num_vf;
	num_vf = 100 * num_vf;
	vf_res->max_qp_per_vf = (qplib_ctx->qpc_count * vf_pct) / num_vf;
	vf_res->max_srq_per_vf = (qplib_ctx->srqc_count * vf_pct) / num_vf;
	vf_res->max_cq_per_vf = (qplib_ctx->cq_count * vf_pct) / num_vf;
	/*
	 * The driver allows many more MRs than other resources. If the
	 * firmware करोes also, then reserve a fixed amount क्रम the PF and
	 * भागide the rest among VFs. VFs may use many MRs क्रम NFS
	 * mounts, ISER, NVME applications, etc. If the firmware severely
	 * restricts the number of MRs, then let PF have half and भागide
	 * the rest among VFs, as क्रम the other resource types.
	 */
	अगर (qplib_ctx->mrw_count < BNXT_RE_MAX_MRW_COUNT_64K) अणु
		mrws = qplib_ctx->mrw_count * vf_pct;
		nvfs = num_vf;
	पूर्ण अन्यथा अणु
		mrws = qplib_ctx->mrw_count - BNXT_RE_RESVD_MR_FOR_PF;
	पूर्ण
	vf_res->max_mrw_per_vf = (mrws / nvfs);
	vf_res->max_gid_per_vf = BNXT_RE_MAX_GID_PER_VF;
पूर्ण

अटल व्योम bnxt_re_set_resource_limits(काष्ठा bnxt_re_dev *rdev)
अणु
	u32 num_vfs;

	स_रखो(&rdev->qplib_ctx.vf_res, 0, माप(काष्ठा bnxt_qplib_vf_res));
	bnxt_re_limit_pf_res(rdev);

	num_vfs =  bnxt_qplib_is_chip_gen_p5(rdev->chip_ctx) ?
			BNXT_RE_GEN_P5_MAX_VF : rdev->num_vfs;
	अगर (num_vfs)
		bnxt_re_limit_vf_res(&rdev->qplib_ctx, num_vfs);
पूर्ण

/* क्रम handling bnxt_en callbacks later */
अटल व्योम bnxt_re_stop(व्योम *p)
अणु
	काष्ठा bnxt_re_dev *rdev = p;
	काष्ठा bnxt *bp;

	अगर (!rdev)
		वापस;
	ASSERT_RTNL();

	/* L2 driver invokes this callback during device error/crash or device
	 * reset. Current RoCE driver करोesn't recover the device in हाल of
	 * error. Handle the error by dispatching fatal events to all qps
	 * ie. by calling bnxt_re_dev_stop and release the MSIx vectors as
	 * L2 driver want to modअगरy the MSIx table.
	 */
	bp = netdev_priv(rdev->netdev);

	ibdev_info(&rdev->ibdev, "Handle device stop call from L2 driver");
	/* Check the current device state from L2 काष्ठाure and move the
	 * device to detached state अगर FW_FATAL_COND is set.
	 * This prevents more commands to HW during clean-up,
	 * in हाल the device is alपढ़ोy in error.
	 */
	अगर (test_bit(BNXT_STATE_FW_FATAL_COND, &bp->state))
		set_bit(ERR_DEVICE_DETACHED, &rdev->rcfw.cmdq.flags);

	bnxt_re_dev_stop(rdev);
	bnxt_re_stop_irq(rdev);
	/* Move the device states to detached and  aव्योम sending any more
	 * commands to HW
	 */
	set_bit(BNXT_RE_FLAG_ERR_DEVICE_DETACHED, &rdev->flags);
	set_bit(ERR_DEVICE_DETACHED, &rdev->rcfw.cmdq.flags);
पूर्ण

अटल व्योम bnxt_re_start(व्योम *p)
अणु
पूर्ण

अटल व्योम bnxt_re_sriov_config(व्योम *p, पूर्णांक num_vfs)
अणु
	काष्ठा bnxt_re_dev *rdev = p;

	अगर (!rdev)
		वापस;

	अगर (test_bit(BNXT_RE_FLAG_ERR_DEVICE_DETACHED, &rdev->flags))
		वापस;
	rdev->num_vfs = num_vfs;
	अगर (!bnxt_qplib_is_chip_gen_p5(rdev->chip_ctx)) अणु
		bnxt_re_set_resource_limits(rdev);
		bnxt_qplib_set_func_resources(&rdev->qplib_res, &rdev->rcfw,
					      &rdev->qplib_ctx);
	पूर्ण
पूर्ण

अटल व्योम bnxt_re_shutकरोwn(व्योम *p)
अणु
	काष्ठा bnxt_re_dev *rdev = p;

	अगर (!rdev)
		वापस;
	ASSERT_RTNL();
	/* Release the MSIx vectors beक्रमe queuing unरेजिस्टर */
	bnxt_re_stop_irq(rdev);
	ib_unरेजिस्टर_device_queued(&rdev->ibdev);
पूर्ण

अटल व्योम bnxt_re_stop_irq(व्योम *handle)
अणु
	काष्ठा bnxt_re_dev *rdev = (काष्ठा bnxt_re_dev *)handle;
	काष्ठा bnxt_qplib_rcfw *rcfw = &rdev->rcfw;
	काष्ठा bnxt_qplib_nq *nq;
	पूर्णांक indx;

	क्रम (indx = BNXT_RE_NQ_IDX; indx < rdev->num_msix; indx++) अणु
		nq = &rdev->nq[indx - 1];
		bnxt_qplib_nq_stop_irq(nq, false);
	पूर्ण

	bnxt_qplib_rcfw_stop_irq(rcfw, false);
पूर्ण

अटल व्योम bnxt_re_start_irq(व्योम *handle, काष्ठा bnxt_msix_entry *ent)
अणु
	काष्ठा bnxt_re_dev *rdev = (काष्ठा bnxt_re_dev *)handle;
	काष्ठा bnxt_msix_entry *msix_ent = rdev->msix_entries;
	काष्ठा bnxt_qplib_rcfw *rcfw = &rdev->rcfw;
	काष्ठा bnxt_qplib_nq *nq;
	पूर्णांक indx, rc;

	अगर (!ent) अणु
		/* Not setting the f/w समयout bit in rcfw.
		 * During the driver unload the first command
		 * to f/w will समयout and that will set the
		 * समयout bit.
		 */
		ibdev_err(&rdev->ibdev, "Failed to re-start IRQs\n");
		वापस;
	पूर्ण

	/* Vectors may change after restart, so update with new vectors
	 * in device sctructure.
	 */
	क्रम (indx = 0; indx < rdev->num_msix; indx++)
		rdev->msix_entries[indx].vector = ent[indx].vector;

	bnxt_qplib_rcfw_start_irq(rcfw, msix_ent[BNXT_RE_AEQ_IDX].vector,
				  false);
	क्रम (indx = BNXT_RE_NQ_IDX ; indx < rdev->num_msix; indx++) अणु
		nq = &rdev->nq[indx - 1];
		rc = bnxt_qplib_nq_start_irq(nq, indx - 1,
					     msix_ent[indx].vector, false);
		अगर (rc)
			ibdev_warn(&rdev->ibdev, "Failed to reinit NQ index %d\n",
				   indx - 1);
	पूर्ण
पूर्ण

अटल काष्ठा bnxt_ulp_ops bnxt_re_ulp_ops = अणु
	.ulp_async_notअगरier = शून्य,
	.ulp_stop = bnxt_re_stop,
	.ulp_start = bnxt_re_start,
	.ulp_sriov_config = bnxt_re_sriov_config,
	.ulp_shutकरोwn = bnxt_re_shutकरोwn,
	.ulp_irq_stop = bnxt_re_stop_irq,
	.ulp_irq_restart = bnxt_re_start_irq
पूर्ण;

/* RoCE -> Net driver */

/* Driver registration routines used to let the networking driver (bnxt_en)
 * to know that the RoCE driver is now installed
 */
अटल पूर्णांक bnxt_re_unरेजिस्टर_netdev(काष्ठा bnxt_re_dev *rdev)
अणु
	काष्ठा bnxt_en_dev *en_dev;
	पूर्णांक rc;

	अगर (!rdev)
		वापस -EINVAL;

	en_dev = rdev->en_dev;

	rc = en_dev->en_ops->bnxt_unरेजिस्टर_device(rdev->en_dev,
						    BNXT_ROCE_ULP);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_re_रेजिस्टर_netdev(काष्ठा bnxt_re_dev *rdev)
अणु
	काष्ठा bnxt_en_dev *en_dev;
	पूर्णांक rc = 0;

	अगर (!rdev)
		वापस -EINVAL;

	en_dev = rdev->en_dev;

	rc = en_dev->en_ops->bnxt_रेजिस्टर_device(en_dev, BNXT_ROCE_ULP,
						  &bnxt_re_ulp_ops, rdev);
	rdev->qplib_res.pdev = rdev->en_dev->pdev;
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_re_मुक्त_msix(काष्ठा bnxt_re_dev *rdev)
अणु
	काष्ठा bnxt_en_dev *en_dev;
	पूर्णांक rc;

	अगर (!rdev)
		वापस -EINVAL;

	en_dev = rdev->en_dev;


	rc = en_dev->en_ops->bnxt_मुक्त_msix(rdev->en_dev, BNXT_ROCE_ULP);

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_re_request_msix(काष्ठा bnxt_re_dev *rdev)
अणु
	पूर्णांक rc = 0, num_msix_want = BNXT_RE_MAX_MSIX, num_msix_got;
	काष्ठा bnxt_en_dev *en_dev;

	अगर (!rdev)
		वापस -EINVAL;

	en_dev = rdev->en_dev;

	num_msix_want = min_t(u32, BNXT_RE_MAX_MSIX, num_online_cpus());

	num_msix_got = en_dev->en_ops->bnxt_request_msix(en_dev, BNXT_ROCE_ULP,
							 rdev->msix_entries,
							 num_msix_want);
	अगर (num_msix_got < BNXT_RE_MIN_MSIX) अणु
		rc = -EINVAL;
		जाओ करोne;
	पूर्ण
	अगर (num_msix_got != num_msix_want) अणु
		ibdev_warn(&rdev->ibdev,
			   "Requested %d MSI-X vectors, got %d\n",
			   num_msix_want, num_msix_got);
	पूर्ण
	rdev->num_msix = num_msix_got;
करोne:
	वापस rc;
पूर्ण

अटल व्योम bnxt_re_init_hwrm_hdr(काष्ठा bnxt_re_dev *rdev, काष्ठा input *hdr,
				  u16 opcd, u16 crid, u16 trid)
अणु
	hdr->req_type = cpu_to_le16(opcd);
	hdr->cmpl_ring = cpu_to_le16(crid);
	hdr->target_id = cpu_to_le16(trid);
पूर्ण

अटल व्योम bnxt_re_fill_fw_msg(काष्ठा bnxt_fw_msg *fw_msg, व्योम *msg,
				पूर्णांक msg_len, व्योम *resp, पूर्णांक resp_max_len,
				पूर्णांक समयout)
अणु
	fw_msg->msg = msg;
	fw_msg->msg_len = msg_len;
	fw_msg->resp = resp;
	fw_msg->resp_max_len = resp_max_len;
	fw_msg->समयout = समयout;
पूर्ण

अटल पूर्णांक bnxt_re_net_ring_मुक्त(काष्ठा bnxt_re_dev *rdev,
				 u16 fw_ring_id, पूर्णांक type)
अणु
	काष्ठा bnxt_en_dev *en_dev = rdev->en_dev;
	काष्ठा hwrm_ring_मुक्त_input req = अणु0पूर्ण;
	काष्ठा hwrm_ring_मुक्त_output resp;
	काष्ठा bnxt_fw_msg fw_msg;
	पूर्णांक rc = -EINVAL;

	अगर (!en_dev)
		वापस rc;

	अगर (test_bit(BNXT_RE_FLAG_ERR_DEVICE_DETACHED, &rdev->flags))
		वापस 0;

	स_रखो(&fw_msg, 0, माप(fw_msg));

	bnxt_re_init_hwrm_hdr(rdev, (व्योम *)&req, HWRM_RING_FREE, -1, -1);
	req.ring_type = type;
	req.ring_id = cpu_to_le16(fw_ring_id);
	bnxt_re_fill_fw_msg(&fw_msg, (व्योम *)&req, माप(req), (व्योम *)&resp,
			    माप(resp), DFLT_HWRM_CMD_TIMEOUT);
	rc = en_dev->en_ops->bnxt_send_fw_msg(en_dev, BNXT_ROCE_ULP, &fw_msg);
	अगर (rc)
		ibdev_err(&rdev->ibdev, "Failed to free HW ring:%d :%#x",
			  req.ring_id, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_re_net_ring_alloc(काष्ठा bnxt_re_dev *rdev,
				  काष्ठा bnxt_re_ring_attr *ring_attr,
				  u16 *fw_ring_id)
अणु
	काष्ठा bnxt_en_dev *en_dev = rdev->en_dev;
	काष्ठा hwrm_ring_alloc_input req = अणु0पूर्ण;
	काष्ठा hwrm_ring_alloc_output resp;
	काष्ठा bnxt_fw_msg fw_msg;
	पूर्णांक rc = -EINVAL;

	अगर (!en_dev)
		वापस rc;

	स_रखो(&fw_msg, 0, माप(fw_msg));
	bnxt_re_init_hwrm_hdr(rdev, (व्योम *)&req, HWRM_RING_ALLOC, -1, -1);
	req.enables = 0;
	req.page_tbl_addr =  cpu_to_le64(ring_attr->dma_arr[0]);
	अगर (ring_attr->pages > 1) अणु
		/* Page size is in log2 units */
		req.page_size = BNXT_PAGE_SHIFT;
		req.page_tbl_depth = 1;
	पूर्ण
	req.fbo = 0;
	/* Association of ring index with करोorbell index and MSIX number */
	req.logical_id = cpu_to_le16(ring_attr->lrid);
	req.length = cpu_to_le32(ring_attr->depth + 1);
	req.ring_type = ring_attr->type;
	req.पूर्णांक_mode = ring_attr->mode;
	bnxt_re_fill_fw_msg(&fw_msg, (व्योम *)&req, माप(req), (व्योम *)&resp,
			    माप(resp), DFLT_HWRM_CMD_TIMEOUT);
	rc = en_dev->en_ops->bnxt_send_fw_msg(en_dev, BNXT_ROCE_ULP, &fw_msg);
	अगर (!rc)
		*fw_ring_id = le16_to_cpu(resp.ring_id);

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_re_net_stats_ctx_मुक्त(काष्ठा bnxt_re_dev *rdev,
				      u32 fw_stats_ctx_id)
अणु
	काष्ठा bnxt_en_dev *en_dev = rdev->en_dev;
	काष्ठा hwrm_stat_ctx_मुक्त_input req = अणु0पूर्ण;
	काष्ठा bnxt_fw_msg fw_msg;
	पूर्णांक rc = -EINVAL;

	अगर (!en_dev)
		वापस rc;

	अगर (test_bit(BNXT_RE_FLAG_ERR_DEVICE_DETACHED, &rdev->flags))
		वापस 0;

	स_रखो(&fw_msg, 0, माप(fw_msg));

	bnxt_re_init_hwrm_hdr(rdev, (व्योम *)&req, HWRM_STAT_CTX_FREE, -1, -1);
	req.stat_ctx_id = cpu_to_le32(fw_stats_ctx_id);
	bnxt_re_fill_fw_msg(&fw_msg, (व्योम *)&req, माप(req), (व्योम *)&req,
			    माप(req), DFLT_HWRM_CMD_TIMEOUT);
	rc = en_dev->en_ops->bnxt_send_fw_msg(en_dev, BNXT_ROCE_ULP, &fw_msg);
	अगर (rc)
		ibdev_err(&rdev->ibdev, "Failed to free HW stats context %#x",
			  rc);

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_re_net_stats_ctx_alloc(काष्ठा bnxt_re_dev *rdev,
				       dma_addr_t dma_map,
				       u32 *fw_stats_ctx_id)
अणु
	काष्ठा hwrm_stat_ctx_alloc_output resp = अणु0पूर्ण;
	काष्ठा hwrm_stat_ctx_alloc_input req = अणु0पूर्ण;
	काष्ठा bnxt_en_dev *en_dev = rdev->en_dev;
	काष्ठा bnxt_fw_msg fw_msg;
	पूर्णांक rc = -EINVAL;

	*fw_stats_ctx_id = INVALID_STATS_CTX_ID;

	अगर (!en_dev)
		वापस rc;

	स_रखो(&fw_msg, 0, माप(fw_msg));

	bnxt_re_init_hwrm_hdr(rdev, (व्योम *)&req, HWRM_STAT_CTX_ALLOC, -1, -1);
	req.update_period_ms = cpu_to_le32(1000);
	req.stats_dma_addr = cpu_to_le64(dma_map);
	req.stats_dma_length = cpu_to_le16(माप(काष्ठा ctx_hw_stats_ext));
	req.stat_ctx_flags = STAT_CTX_ALLOC_REQ_STAT_CTX_FLAGS_ROCE;
	bnxt_re_fill_fw_msg(&fw_msg, (व्योम *)&req, माप(req), (व्योम *)&resp,
			    माप(resp), DFLT_HWRM_CMD_TIMEOUT);
	rc = en_dev->en_ops->bnxt_send_fw_msg(en_dev, BNXT_ROCE_ULP, &fw_msg);
	अगर (!rc)
		*fw_stats_ctx_id = le32_to_cpu(resp.stat_ctx_id);

	वापस rc;
पूर्ण

/* Device */

अटल bool is_bnxt_re_dev(काष्ठा net_device *netdev)
अणु
	काष्ठा ethtool_drvinfo drvinfo;

	अगर (netdev->ethtool_ops && netdev->ethtool_ops->get_drvinfo) अणु
		स_रखो(&drvinfo, 0, माप(drvinfo));
		netdev->ethtool_ops->get_drvinfo(netdev, &drvinfo);

		अगर (म_भेद(drvinfo.driver, "bnxt_en"))
			वापस false;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल काष्ठा bnxt_re_dev *bnxt_re_from_netdev(काष्ठा net_device *netdev)
अणु
	काष्ठा ib_device *ibdev =
		ib_device_get_by_netdev(netdev, RDMA_DRIVER_BNXT_RE);
	अगर (!ibdev)
		वापस शून्य;

	वापस container_of(ibdev, काष्ठा bnxt_re_dev, ibdev);
पूर्ण

अटल काष्ठा bnxt_en_dev *bnxt_re_dev_probe(काष्ठा net_device *netdev)
अणु
	काष्ठा bnxt_en_dev *en_dev;
	काष्ठा pci_dev *pdev;

	en_dev = bnxt_ulp_probe(netdev);
	अगर (IS_ERR(en_dev))
		वापस en_dev;

	pdev = en_dev->pdev;
	अगर (!pdev)
		वापस ERR_PTR(-EINVAL);

	अगर (!(en_dev->flags & BNXT_EN_FLAG_ROCE_CAP)) अणु
		dev_info(&pdev->dev,
			"%s: probe error: RoCE is not supported on this device",
			ROCE_DRV_MODULE_NAME);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	dev_hold(netdev);

	वापस en_dev;
पूर्ण

अटल sमाप_प्रकार hw_rev_show(काष्ठा device *device, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा bnxt_re_dev *rdev =
		rdma_device_to_drv_device(device, काष्ठा bnxt_re_dev, ibdev);

	वापस sysfs_emit(buf, "0x%x\n", rdev->en_dev->pdev->venकरोr);
पूर्ण
अटल DEVICE_ATTR_RO(hw_rev);

अटल sमाप_प्रकार hca_type_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bnxt_re_dev *rdev =
		rdma_device_to_drv_device(device, काष्ठा bnxt_re_dev, ibdev);

	वापस sysfs_emit(buf, "%s\n", rdev->ibdev.node_desc);
पूर्ण
अटल DEVICE_ATTR_RO(hca_type);

अटल काष्ठा attribute *bnxt_re_attributes[] = अणु
	&dev_attr_hw_rev.attr,
	&dev_attr_hca_type.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group bnxt_re_dev_attr_group = अणु
	.attrs = bnxt_re_attributes,
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops bnxt_re_dev_ops = अणु
	.owner = THIS_MODULE,
	.driver_id = RDMA_DRIVER_BNXT_RE,
	.uverbs_abi_ver = BNXT_RE_ABI_VERSION,

	.add_gid = bnxt_re_add_gid,
	.alloc_hw_stats = bnxt_re_ib_alloc_hw_stats,
	.alloc_mr = bnxt_re_alloc_mr,
	.alloc_pd = bnxt_re_alloc_pd,
	.alloc_ucontext = bnxt_re_alloc_ucontext,
	.create_ah = bnxt_re_create_ah,
	.create_cq = bnxt_re_create_cq,
	.create_qp = bnxt_re_create_qp,
	.create_srq = bnxt_re_create_srq,
	.create_user_ah = bnxt_re_create_ah,
	.dealloc_driver = bnxt_re_dealloc_driver,
	.dealloc_pd = bnxt_re_dealloc_pd,
	.dealloc_ucontext = bnxt_re_dealloc_ucontext,
	.del_gid = bnxt_re_del_gid,
	.dereg_mr = bnxt_re_dereg_mr,
	.destroy_ah = bnxt_re_destroy_ah,
	.destroy_cq = bnxt_re_destroy_cq,
	.destroy_qp = bnxt_re_destroy_qp,
	.destroy_srq = bnxt_re_destroy_srq,
	.get_dev_fw_str = bnxt_re_query_fw_str,
	.get_dma_mr = bnxt_re_get_dma_mr,
	.get_hw_stats = bnxt_re_ib_get_hw_stats,
	.get_link_layer = bnxt_re_get_link_layer,
	.get_port_immutable = bnxt_re_get_port_immutable,
	.map_mr_sg = bnxt_re_map_mr_sg,
	.mmap = bnxt_re_mmap,
	.modअगरy_ah = bnxt_re_modअगरy_ah,
	.modअगरy_qp = bnxt_re_modअगरy_qp,
	.modअगरy_srq = bnxt_re_modअगरy_srq,
	.poll_cq = bnxt_re_poll_cq,
	.post_recv = bnxt_re_post_recv,
	.post_send = bnxt_re_post_send,
	.post_srq_recv = bnxt_re_post_srq_recv,
	.query_ah = bnxt_re_query_ah,
	.query_device = bnxt_re_query_device,
	.query_pkey = bnxt_re_query_pkey,
	.query_port = bnxt_re_query_port,
	.query_qp = bnxt_re_query_qp,
	.query_srq = bnxt_re_query_srq,
	.reg_user_mr = bnxt_re_reg_user_mr,
	.req_notअगरy_cq = bnxt_re_req_notअगरy_cq,
	INIT_RDMA_OBJ_SIZE(ib_ah, bnxt_re_ah, ib_ah),
	INIT_RDMA_OBJ_SIZE(ib_cq, bnxt_re_cq, ib_cq),
	INIT_RDMA_OBJ_SIZE(ib_pd, bnxt_re_pd, ib_pd),
	INIT_RDMA_OBJ_SIZE(ib_srq, bnxt_re_srq, ib_srq),
	INIT_RDMA_OBJ_SIZE(ib_ucontext, bnxt_re_ucontext, ib_uctx),
पूर्ण;

अटल पूर्णांक bnxt_re_रेजिस्टर_ib(काष्ठा bnxt_re_dev *rdev)
अणु
	काष्ठा ib_device *ibdev = &rdev->ibdev;
	पूर्णांक ret;

	/* ib device init */
	ibdev->node_type = RDMA_NODE_IB_CA;
	strlcpy(ibdev->node_desc, BNXT_RE_DESC " HCA",
		म_माप(BNXT_RE_DESC) + 5);
	ibdev->phys_port_cnt = 1;

	bnxt_qplib_get_guid(rdev->netdev->dev_addr, (u8 *)&ibdev->node_guid);

	ibdev->num_comp_vectors	= rdev->num_msix - 1;
	ibdev->dev.parent = &rdev->en_dev->pdev->dev;
	ibdev->local_dma_lkey = BNXT_QPLIB_RSVD_LKEY;

	rdma_set_device_sysfs_group(ibdev, &bnxt_re_dev_attr_group);
	ib_set_device_ops(ibdev, &bnxt_re_dev_ops);
	ret = ib_device_set_netdev(&rdev->ibdev, rdev->netdev, 1);
	अगर (ret)
		वापस ret;

	dma_set_max_seg_size(&rdev->en_dev->pdev->dev, अच_पूर्णांक_उच्च);
	वापस ib_रेजिस्टर_device(ibdev, "bnxt_re%d", &rdev->en_dev->pdev->dev);
पूर्ण

अटल व्योम bnxt_re_dev_हटाओ(काष्ठा bnxt_re_dev *rdev)
अणु
	dev_put(rdev->netdev);
	rdev->netdev = शून्य;
	mutex_lock(&bnxt_re_dev_lock);
	list_del_rcu(&rdev->list);
	mutex_unlock(&bnxt_re_dev_lock);

	synchronize_rcu();
पूर्ण

अटल काष्ठा bnxt_re_dev *bnxt_re_dev_add(काष्ठा net_device *netdev,
					   काष्ठा bnxt_en_dev *en_dev)
अणु
	काष्ठा bnxt_re_dev *rdev;

	/* Allocate bnxt_re_dev instance here */
	rdev = ib_alloc_device(bnxt_re_dev, ibdev);
	अगर (!rdev) अणु
		ibdev_err(शून्य, "%s: bnxt_re_dev allocation failure!",
			  ROCE_DRV_MODULE_NAME);
		वापस शून्य;
	पूर्ण
	/* Default values */
	rdev->netdev = netdev;
	dev_hold(rdev->netdev);
	rdev->en_dev = en_dev;
	rdev->id = rdev->en_dev->pdev->devfn;
	INIT_LIST_HEAD(&rdev->qp_list);
	mutex_init(&rdev->qp_lock);
	atomic_set(&rdev->qp_count, 0);
	atomic_set(&rdev->cq_count, 0);
	atomic_set(&rdev->srq_count, 0);
	atomic_set(&rdev->mr_count, 0);
	atomic_set(&rdev->mw_count, 0);
	rdev->cosq[0] = 0xFFFF;
	rdev->cosq[1] = 0xFFFF;

	mutex_lock(&bnxt_re_dev_lock);
	list_add_tail_rcu(&rdev->list, &bnxt_re_dev_list);
	mutex_unlock(&bnxt_re_dev_lock);
	वापस rdev;
पूर्ण

अटल पूर्णांक bnxt_re_handle_unaffi_async_event(काष्ठा creq_func_event
					     *unaffi_async)
अणु
	चयन (unaffi_async->event) अणु
	हाल CREQ_FUNC_EVENT_EVENT_TX_WQE_ERROR:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_TX_DATA_ERROR:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_RX_WQE_ERROR:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_RX_DATA_ERROR:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_CQ_ERROR:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_TQM_ERROR:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_CFCQ_ERROR:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_CFCS_ERROR:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_CFCC_ERROR:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_CFCM_ERROR:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_TIM_ERROR:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_re_handle_qp_async_event(काष्ठा creq_qp_event *qp_event,
					 काष्ठा bnxt_re_qp *qp)
अणु
	काष्ठा ib_event event;
	अचिन्हित पूर्णांक flags;

	अगर (qp->qplib_qp.state == CMDQ_MODIFY_QP_NEW_STATE_ERR &&
	    rdma_is_kernel_res(&qp->ib_qp.res)) अणु
		flags = bnxt_re_lock_cqs(qp);
		bnxt_qplib_add_flush_qp(&qp->qplib_qp);
		bnxt_re_unlock_cqs(qp, flags);
	पूर्ण

	स_रखो(&event, 0, माप(event));
	अगर (qp->qplib_qp.srq) अणु
		event.device = &qp->rdev->ibdev;
		event.element.qp = &qp->ib_qp;
		event.event = IB_EVENT_QP_LAST_WQE_REACHED;
	पूर्ण

	अगर (event.device && qp->ib_qp.event_handler)
		qp->ib_qp.event_handler(&event, qp->ib_qp.qp_context);

	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_re_handle_affi_async_event(काष्ठा creq_qp_event *affi_async,
					   व्योम *obj)
अणु
	पूर्णांक rc = 0;
	u8 event;

	अगर (!obj)
		वापस rc; /* QP was alपढ़ोy dead, still वापस success */

	event = affi_async->event;
	अगर (event == CREQ_QP_EVENT_EVENT_QP_ERROR_NOTIFICATION) अणु
		काष्ठा bnxt_qplib_qp *lib_qp = obj;
		काष्ठा bnxt_re_qp *qp = container_of(lib_qp, काष्ठा bnxt_re_qp,
						     qplib_qp);
		rc = bnxt_re_handle_qp_async_event(affi_async, qp);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_re_aeq_handler(काष्ठा bnxt_qplib_rcfw *rcfw,
			       व्योम *aeqe, व्योम *obj)
अणु
	काष्ठा creq_qp_event *affi_async;
	काष्ठा creq_func_event *unaffi_async;
	u8 type;
	पूर्णांक rc;

	type = ((काष्ठा creq_base *)aeqe)->type;
	अगर (type == CREQ_BASE_TYPE_FUNC_EVENT) अणु
		unaffi_async = aeqe;
		rc = bnxt_re_handle_unaffi_async_event(unaffi_async);
	पूर्ण अन्यथा अणु
		affi_async = aeqe;
		rc = bnxt_re_handle_affi_async_event(affi_async, obj);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_re_srqn_handler(काष्ठा bnxt_qplib_nq *nq,
				काष्ठा bnxt_qplib_srq *handle, u8 event)
अणु
	काष्ठा bnxt_re_srq *srq = container_of(handle, काष्ठा bnxt_re_srq,
					       qplib_srq);
	काष्ठा ib_event ib_event;
	पूर्णांक rc = 0;

	अगर (!srq) अणु
		ibdev_err(शून्य, "%s: SRQ is NULL, SRQN not handled",
			  ROCE_DRV_MODULE_NAME);
		rc = -EINVAL;
		जाओ करोne;
	पूर्ण
	ib_event.device = &srq->rdev->ibdev;
	ib_event.element.srq = &srq->ib_srq;
	अगर (event == NQ_SRQ_EVENT_EVENT_SRQ_THRESHOLD_EVENT)
		ib_event.event = IB_EVENT_SRQ_LIMIT_REACHED;
	अन्यथा
		ib_event.event = IB_EVENT_SRQ_ERR;

	अगर (srq->ib_srq.event_handler) अणु
		/* Lock event_handler? */
		(*srq->ib_srq.event_handler)(&ib_event,
					     srq->ib_srq.srq_context);
	पूर्ण
करोne:
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_re_cqn_handler(काष्ठा bnxt_qplib_nq *nq,
			       काष्ठा bnxt_qplib_cq *handle)
अणु
	काष्ठा bnxt_re_cq *cq = container_of(handle, काष्ठा bnxt_re_cq,
					     qplib_cq);

	अगर (!cq) अणु
		ibdev_err(शून्य, "%s: CQ is NULL, CQN not handled",
			  ROCE_DRV_MODULE_NAME);
		वापस -EINVAL;
	पूर्ण
	अगर (cq->ib_cq.comp_handler) अणु
		/* Lock comp_handler? */
		(*cq->ib_cq.comp_handler)(&cq->ib_cq, cq->ib_cq.cq_context);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा BNXT_RE_GEN_P5_PF_NQ_DB		0x10000
#घोषणा BNXT_RE_GEN_P5_VF_NQ_DB		0x4000
अटल u32 bnxt_re_get_nqdb_offset(काष्ठा bnxt_re_dev *rdev, u16 indx)
अणु
	वापस bnxt_qplib_is_chip_gen_p5(rdev->chip_ctx) ?
		(rdev->is_virtfn ? BNXT_RE_GEN_P5_VF_NQ_DB :
				   BNXT_RE_GEN_P5_PF_NQ_DB) :
				   rdev->msix_entries[indx].db_offset;
पूर्ण

अटल व्योम bnxt_re_cleanup_res(काष्ठा bnxt_re_dev *rdev)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < rdev->num_msix; i++)
		bnxt_qplib_disable_nq(&rdev->nq[i - 1]);

	अगर (rdev->qplib_res.rcfw)
		bnxt_qplib_cleanup_res(&rdev->qplib_res);
पूर्ण

अटल पूर्णांक bnxt_re_init_res(काष्ठा bnxt_re_dev *rdev)
अणु
	पूर्णांक num_vec_enabled = 0;
	पूर्णांक rc = 0, i;
	u32 db_offt;

	bnxt_qplib_init_res(&rdev->qplib_res);

	क्रम (i = 1; i < rdev->num_msix ; i++) अणु
		db_offt = bnxt_re_get_nqdb_offset(rdev, i);
		rc = bnxt_qplib_enable_nq(rdev->en_dev->pdev, &rdev->nq[i - 1],
					  i - 1, rdev->msix_entries[i].vector,
					  db_offt, &bnxt_re_cqn_handler,
					  &bnxt_re_srqn_handler);
		अगर (rc) अणु
			ibdev_err(&rdev->ibdev,
				  "Failed to enable NQ with rc = 0x%x", rc);
			जाओ fail;
		पूर्ण
		num_vec_enabled++;
	पूर्ण
	वापस 0;
fail:
	क्रम (i = num_vec_enabled; i >= 0; i--)
		bnxt_qplib_disable_nq(&rdev->nq[i]);
	वापस rc;
पूर्ण

अटल व्योम bnxt_re_मुक्त_nq_res(काष्ठा bnxt_re_dev *rdev)
अणु
	u8 type;
	पूर्णांक i;

	क्रम (i = 0; i < rdev->num_msix - 1; i++) अणु
		type = bnxt_qplib_get_ring_type(rdev->chip_ctx);
		bnxt_re_net_ring_मुक्त(rdev, rdev->nq[i].ring_id, type);
		bnxt_qplib_मुक्त_nq(&rdev->nq[i]);
		rdev->nq[i].res = शून्य;
	पूर्ण
पूर्ण

अटल व्योम bnxt_re_मुक्त_res(काष्ठा bnxt_re_dev *rdev)
अणु
	bnxt_re_मुक्त_nq_res(rdev);

	अगर (rdev->qplib_res.dpi_tbl.max) अणु
		bnxt_qplib_dealloc_dpi(&rdev->qplib_res,
				       &rdev->qplib_res.dpi_tbl,
				       &rdev->dpi_privileged);
	पूर्ण
	अगर (rdev->qplib_res.rcfw) अणु
		bnxt_qplib_मुक्त_res(&rdev->qplib_res);
		rdev->qplib_res.rcfw = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_re_alloc_res(काष्ठा bnxt_re_dev *rdev)
अणु
	काष्ठा bnxt_re_ring_attr rattr = अणुपूर्ण;
	पूर्णांक num_vec_created = 0;
	पूर्णांक rc = 0, i;
	u8 type;

	/* Configure and allocate resources क्रम qplib */
	rdev->qplib_res.rcfw = &rdev->rcfw;
	rc = bnxt_qplib_get_dev_attr(&rdev->rcfw, &rdev->dev_attr,
				     rdev->is_virtfn);
	अगर (rc)
		जाओ fail;

	rc = bnxt_qplib_alloc_res(&rdev->qplib_res, rdev->en_dev->pdev,
				  rdev->netdev, &rdev->dev_attr);
	अगर (rc)
		जाओ fail;

	rc = bnxt_qplib_alloc_dpi(&rdev->qplib_res.dpi_tbl,
				  &rdev->dpi_privileged,
				  rdev);
	अगर (rc)
		जाओ dealloc_res;

	क्रम (i = 0; i < rdev->num_msix - 1; i++) अणु
		काष्ठा bnxt_qplib_nq *nq;

		nq = &rdev->nq[i];
		nq->hwq.max_elements = BNXT_QPLIB_NQE_MAX_CNT;
		rc = bnxt_qplib_alloc_nq(&rdev->qplib_res, &rdev->nq[i]);
		अगर (rc) अणु
			ibdev_err(&rdev->ibdev, "Alloc Failed NQ%d rc:%#x",
				  i, rc);
			जाओ मुक्त_nq;
		पूर्ण
		type = bnxt_qplib_get_ring_type(rdev->chip_ctx);
		rattr.dma_arr = nq->hwq.pbl[PBL_LVL_0].pg_map_arr;
		rattr.pages = nq->hwq.pbl[rdev->nq[i].hwq.level].pg_count;
		rattr.type = type;
		rattr.mode = RING_ALLOC_REQ_INT_MODE_MSIX;
		rattr.depth = BNXT_QPLIB_NQE_MAX_CNT - 1;
		rattr.lrid = rdev->msix_entries[i + 1].ring_idx;
		rc = bnxt_re_net_ring_alloc(rdev, &rattr, &nq->ring_id);
		अगर (rc) अणु
			ibdev_err(&rdev->ibdev,
				  "Failed to allocate NQ fw id with rc = 0x%x",
				  rc);
			bnxt_qplib_मुक्त_nq(&rdev->nq[i]);
			जाओ मुक्त_nq;
		पूर्ण
		num_vec_created++;
	पूर्ण
	वापस 0;
मुक्त_nq:
	क्रम (i = num_vec_created - 1; i >= 0; i--) अणु
		type = bnxt_qplib_get_ring_type(rdev->chip_ctx);
		bnxt_re_net_ring_मुक्त(rdev, rdev->nq[i].ring_id, type);
		bnxt_qplib_मुक्त_nq(&rdev->nq[i]);
	पूर्ण
	bnxt_qplib_dealloc_dpi(&rdev->qplib_res,
			       &rdev->qplib_res.dpi_tbl,
			       &rdev->dpi_privileged);
dealloc_res:
	bnxt_qplib_मुक्त_res(&rdev->qplib_res);

fail:
	rdev->qplib_res.rcfw = शून्य;
	वापस rc;
पूर्ण

अटल व्योम bnxt_re_dispatch_event(काष्ठा ib_device *ibdev, काष्ठा ib_qp *qp,
				   u8 port_num, क्रमागत ib_event_type event)
अणु
	काष्ठा ib_event ib_event;

	ib_event.device = ibdev;
	अगर (qp) अणु
		ib_event.element.qp = qp;
		ib_event.event = event;
		अगर (qp->event_handler)
			qp->event_handler(&ib_event, qp->qp_context);

	पूर्ण अन्यथा अणु
		ib_event.element.port_num = port_num;
		ib_event.event = event;
		ib_dispatch_event(&ib_event);
	पूर्ण
पूर्ण

#घोषणा HWRM_QUEUE_PRI2COS_QCFG_INPUT_FLAGS_IVLAN      0x02
अटल पूर्णांक bnxt_re_query_hwrm_pri2cos(काष्ठा bnxt_re_dev *rdev, u8 dir,
				      u64 *cid_map)
अणु
	काष्ठा hwrm_queue_pri2cos_qcfg_input req = अणु0पूर्ण;
	काष्ठा bnxt *bp = netdev_priv(rdev->netdev);
	काष्ठा hwrm_queue_pri2cos_qcfg_output resp;
	काष्ठा bnxt_en_dev *en_dev = rdev->en_dev;
	काष्ठा bnxt_fw_msg fw_msg;
	u32 flags = 0;
	u8 *qcfgmap, *पंचांगp_map;
	पूर्णांक rc = 0, i;

	अगर (!cid_map)
		वापस -EINVAL;

	स_रखो(&fw_msg, 0, माप(fw_msg));
	bnxt_re_init_hwrm_hdr(rdev, (व्योम *)&req,
			      HWRM_QUEUE_PRI2COS_QCFG, -1, -1);
	flags |= (dir & 0x01);
	flags |= HWRM_QUEUE_PRI2COS_QCFG_INPUT_FLAGS_IVLAN;
	req.flags = cpu_to_le32(flags);
	req.port_id = bp->pf.port_id;

	bnxt_re_fill_fw_msg(&fw_msg, (व्योम *)&req, माप(req), (व्योम *)&resp,
			    माप(resp), DFLT_HWRM_CMD_TIMEOUT);
	rc = en_dev->en_ops->bnxt_send_fw_msg(en_dev, BNXT_ROCE_ULP, &fw_msg);
	अगर (rc)
		वापस rc;

	अगर (resp.queue_cfg_info) अणु
		ibdev_warn(&rdev->ibdev,
			   "Asymmetric cos queue configuration detected");
		ibdev_warn(&rdev->ibdev,
			   " on device, QoS may not be fully functional\n");
	पूर्ण
	qcfgmap = &resp.pri0_cos_queue_id;
	पंचांगp_map = (u8 *)cid_map;
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
		पंचांगp_map[i] = qcfgmap[i];

	वापस rc;
पूर्ण

अटल bool bnxt_re_is_qp1_or_shaकरोw_qp(काष्ठा bnxt_re_dev *rdev,
					काष्ठा bnxt_re_qp *qp)
अणु
	वापस (qp->ib_qp.qp_type == IB_QPT_GSI) ||
	       (qp == rdev->gsi_ctx.gsi_sqp);
पूर्ण

अटल व्योम bnxt_re_dev_stop(काष्ठा bnxt_re_dev *rdev)
अणु
	पूर्णांक mask = IB_QP_STATE;
	काष्ठा ib_qp_attr qp_attr;
	काष्ठा bnxt_re_qp *qp;

	qp_attr.qp_state = IB_QPS_ERR;
	mutex_lock(&rdev->qp_lock);
	list_क्रम_each_entry(qp, &rdev->qp_list, list) अणु
		/* Modअगरy the state of all QPs except QP1/Shaकरोw QP */
		अगर (!bnxt_re_is_qp1_or_shaकरोw_qp(rdev, qp)) अणु
			अगर (qp->qplib_qp.state !=
			    CMDQ_MODIFY_QP_NEW_STATE_RESET &&
			    qp->qplib_qp.state !=
			    CMDQ_MODIFY_QP_NEW_STATE_ERR) अणु
				bnxt_re_dispatch_event(&rdev->ibdev, &qp->ib_qp,
						       1, IB_EVENT_QP_FATAL);
				bnxt_re_modअगरy_qp(&qp->ib_qp, &qp_attr, mask,
						  शून्य);
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&rdev->qp_lock);
पूर्ण

अटल पूर्णांक bnxt_re_update_gid(काष्ठा bnxt_re_dev *rdev)
अणु
	काष्ठा bnxt_qplib_sgid_tbl *sgid_tbl = &rdev->qplib_res.sgid_tbl;
	काष्ठा bnxt_qplib_gid gid;
	u16 gid_idx, index;
	पूर्णांक rc = 0;

	अगर (!ib_device_try_get(&rdev->ibdev))
		वापस 0;

	अगर (!sgid_tbl) अणु
		ibdev_err(&rdev->ibdev, "QPLIB: SGID table not allocated");
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	क्रम (index = 0; index < sgid_tbl->active; index++) अणु
		gid_idx = sgid_tbl->hw_id[index];

		अगर (!स_भेद(&sgid_tbl->tbl[index], &bnxt_qplib_gid_zero,
			    माप(bnxt_qplib_gid_zero)))
			जारी;
		/* need to modअगरy the VLAN enable setting of non VLAN GID only
		 * as setting is करोne क्रम VLAN GID जबतक adding GID
		 */
		अगर (sgid_tbl->vlan[index])
			जारी;

		स_नकल(&gid, &sgid_tbl->tbl[index], माप(gid));

		rc = bnxt_qplib_update_sgid(sgid_tbl, &gid, gid_idx,
					    rdev->qplib_res.netdev->dev_addr);
	पूर्ण
out:
	ib_device_put(&rdev->ibdev);
	वापस rc;
पूर्ण

अटल u32 bnxt_re_get_priority_mask(काष्ठा bnxt_re_dev *rdev)
अणु
	u32 prio_map = 0, पंचांगp_map = 0;
	काष्ठा net_device *netdev;
	काष्ठा dcb_app app;

	netdev = rdev->netdev;

	स_रखो(&app, 0, माप(app));
	app.selector = IEEE_8021QAZ_APP_SEL_ETHERTYPE;
	app.protocol = ETH_P_IBOE;
	पंचांगp_map = dcb_ieee_getapp_mask(netdev, &app);
	prio_map = पंचांगp_map;

	app.selector = IEEE_8021QAZ_APP_SEL_DGRAM;
	app.protocol = ROCE_V2_UDP_DPORT;
	पंचांगp_map = dcb_ieee_getapp_mask(netdev, &app);
	prio_map |= पंचांगp_map;

	वापस prio_map;
पूर्ण

अटल व्योम bnxt_re_parse_cid_map(u8 prio_map, u8 *cid_map, u16 *cosq)
अणु
	u16 prio;
	u8 id;

	क्रम (prio = 0, id = 0; prio < 8; prio++) अणु
		अगर (prio_map & (1 << prio)) अणु
			cosq[id] = cid_map[prio];
			id++;
			अगर (id == 2) /* Max 2 tcs supported */
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_re_setup_qos(काष्ठा bnxt_re_dev *rdev)
अणु
	u8 prio_map = 0;
	u64 cid_map;
	पूर्णांक rc;

	/* Get priority क्रम roce */
	prio_map = bnxt_re_get_priority_mask(rdev);

	अगर (prio_map == rdev->cur_prio_map)
		वापस 0;
	rdev->cur_prio_map = prio_map;
	/* Get cosq id क्रम this priority */
	rc = bnxt_re_query_hwrm_pri2cos(rdev, 0, &cid_map);
	अगर (rc) अणु
		ibdev_warn(&rdev->ibdev, "no cos for p_mask %x\n", prio_map);
		वापस rc;
	पूर्ण
	/* Parse CoS IDs क्रम app priority */
	bnxt_re_parse_cid_map(prio_map, (u8 *)&cid_map, rdev->cosq);

	/* Config BONO. */
	rc = bnxt_qplib_map_tc2cos(&rdev->qplib_res, rdev->cosq);
	अगर (rc) अणु
		ibdev_warn(&rdev->ibdev, "no tc for cos{%x, %x}\n",
			   rdev->cosq[0], rdev->cosq[1]);
		वापस rc;
	पूर्ण

	/* Actual priorities are not programmed as they are alपढ़ोy
	 * करोne by L2 driver; just enable or disable priority vlan tagging
	 */
	अगर ((prio_map == 0 && rdev->qplib_res.prio) ||
	    (prio_map != 0 && !rdev->qplib_res.prio)) अणु
		rdev->qplib_res.prio = prio_map ? true : false;

		bnxt_re_update_gid(rdev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bnxt_re_query_hwrm_पूर्णांकf_version(काष्ठा bnxt_re_dev *rdev)
अणु
	काष्ठा bnxt_en_dev *en_dev = rdev->en_dev;
	काष्ठा hwrm_ver_get_output resp = अणु0पूर्ण;
	काष्ठा hwrm_ver_get_input req = अणु0पूर्ण;
	काष्ठा bnxt_fw_msg fw_msg;
	पूर्णांक rc = 0;

	स_रखो(&fw_msg, 0, माप(fw_msg));
	bnxt_re_init_hwrm_hdr(rdev, (व्योम *)&req,
			      HWRM_VER_GET, -1, -1);
	req.hwrm_पूर्णांकf_maj = HWRM_VERSION_MAJOR;
	req.hwrm_पूर्णांकf_min = HWRM_VERSION_MINOR;
	req.hwrm_पूर्णांकf_upd = HWRM_VERSION_UPDATE;
	bnxt_re_fill_fw_msg(&fw_msg, (व्योम *)&req, माप(req), (व्योम *)&resp,
			    माप(resp), DFLT_HWRM_CMD_TIMEOUT);
	rc = en_dev->en_ops->bnxt_send_fw_msg(en_dev, BNXT_ROCE_ULP, &fw_msg);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "Failed to query HW version, rc = 0x%x",
			  rc);
		वापस;
	पूर्ण
	rdev->qplib_ctx.hwrm_पूर्णांकf_ver =
		(u64)le16_to_cpu(resp.hwrm_पूर्णांकf_major) << 48 |
		(u64)le16_to_cpu(resp.hwrm_पूर्णांकf_minor) << 32 |
		(u64)le16_to_cpu(resp.hwrm_पूर्णांकf_build) << 16 |
		le16_to_cpu(resp.hwrm_पूर्णांकf_patch);
पूर्ण

अटल पूर्णांक bnxt_re_ib_init(काष्ठा bnxt_re_dev *rdev)
अणु
	पूर्णांक rc = 0;
	u32 event;

	/* Register ib dev */
	rc = bnxt_re_रेजिस्टर_ib(rdev);
	अगर (rc) अणु
		pr_err("Failed to register with IB: %#x\n", rc);
		वापस rc;
	पूर्ण
	dev_info(rdev_to_dev(rdev), "Device registered successfully");
	ib_get_eth_speed(&rdev->ibdev, 1, &rdev->active_speed,
			 &rdev->active_width);
	set_bit(BNXT_RE_FLAG_ISSUE_ROCE_STATS, &rdev->flags);

	event = netअगर_running(rdev->netdev) && netअगर_carrier_ok(rdev->netdev) ?
		IB_EVENT_PORT_ACTIVE : IB_EVENT_PORT_ERR;

	bnxt_re_dispatch_event(&rdev->ibdev, शून्य, 1, event);

	वापस rc;
पूर्ण

अटल व्योम bnxt_re_dev_uninit(काष्ठा bnxt_re_dev *rdev)
अणु
	u8 type;
	पूर्णांक rc;

	अगर (test_and_clear_bit(BNXT_RE_FLAG_QOS_WORK_REG, &rdev->flags))
		cancel_delayed_work_sync(&rdev->worker);

	अगर (test_and_clear_bit(BNXT_RE_FLAG_RESOURCES_INITIALIZED,
			       &rdev->flags))
		bnxt_re_cleanup_res(rdev);
	अगर (test_and_clear_bit(BNXT_RE_FLAG_RESOURCES_ALLOCATED, &rdev->flags))
		bnxt_re_मुक्त_res(rdev);

	अगर (test_and_clear_bit(BNXT_RE_FLAG_RCFW_CHANNEL_EN, &rdev->flags)) अणु
		rc = bnxt_qplib_deinit_rcfw(&rdev->rcfw);
		अगर (rc)
			ibdev_warn(&rdev->ibdev,
				   "Failed to deinitialize RCFW: %#x", rc);
		bnxt_re_net_stats_ctx_मुक्त(rdev, rdev->qplib_ctx.stats.fw_id);
		bnxt_qplib_मुक्त_ctx(&rdev->qplib_res, &rdev->qplib_ctx);
		bnxt_qplib_disable_rcfw_channel(&rdev->rcfw);
		type = bnxt_qplib_get_ring_type(rdev->chip_ctx);
		bnxt_re_net_ring_मुक्त(rdev, rdev->rcfw.creq.ring_id, type);
		bnxt_qplib_मुक्त_rcfw_channel(&rdev->rcfw);
	पूर्ण
	अगर (test_and_clear_bit(BNXT_RE_FLAG_GOT_MSIX, &rdev->flags)) अणु
		rc = bnxt_re_मुक्त_msix(rdev);
		अगर (rc)
			ibdev_warn(&rdev->ibdev,
				   "Failed to free MSI-X vectors: %#x", rc);
	पूर्ण

	bnxt_re_destroy_chip_ctx(rdev);
	अगर (test_and_clear_bit(BNXT_RE_FLAG_NETDEV_REGISTERED, &rdev->flags)) अणु
		rc = bnxt_re_unरेजिस्टर_netdev(rdev);
		अगर (rc)
			ibdev_warn(&rdev->ibdev,
				   "Failed to unregister with netdev: %#x", rc);
	पूर्ण
पूर्ण

/* worker thपढ़ो क्रम polling periodic events. Now used क्रम QoS programming*/
अटल व्योम bnxt_re_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bnxt_re_dev *rdev = container_of(work, काष्ठा bnxt_re_dev,
						worker.work);

	bnxt_re_setup_qos(rdev);
	schedule_delayed_work(&rdev->worker, msecs_to_jअगरfies(30000));
पूर्ण

अटल पूर्णांक bnxt_re_dev_init(काष्ठा bnxt_re_dev *rdev, u8 wqe_mode)
अणु
	काष्ठा bnxt_qplib_creq_ctx *creq;
	काष्ठा bnxt_re_ring_attr rattr;
	u32 db_offt;
	पूर्णांक vid;
	u8 type;
	पूर्णांक rc;

	/* Registered a new RoCE device instance to netdev */
	स_रखो(&rattr, 0, माप(rattr));
	rc = bnxt_re_रेजिस्टर_netdev(rdev);
	अगर (rc) अणु
		rtnl_unlock();
		ibdev_err(&rdev->ibdev,
			  "Failed to register with netedev: %#x\n", rc);
		वापस -EINVAL;
	पूर्ण
	set_bit(BNXT_RE_FLAG_NETDEV_REGISTERED, &rdev->flags);

	rc = bnxt_re_setup_chip_ctx(rdev, wqe_mode);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "Failed to get chip context\n");
		वापस -EINVAL;
	पूर्ण

	/* Check whether VF or PF */
	bnxt_re_get_sriov_func_type(rdev);

	rc = bnxt_re_request_msix(rdev);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev,
			  "Failed to get MSI-X vectors: %#x\n", rc);
		rc = -EINVAL;
		जाओ fail;
	पूर्ण
	set_bit(BNXT_RE_FLAG_GOT_MSIX, &rdev->flags);

	bnxt_re_query_hwrm_पूर्णांकf_version(rdev);

	/* Establish RCFW Communication Channel to initialize the context
	 * memory क्रम the function and all child VFs
	 */
	rc = bnxt_qplib_alloc_rcfw_channel(&rdev->qplib_res, &rdev->rcfw,
					   &rdev->qplib_ctx,
					   BNXT_RE_MAX_QPC_COUNT);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev,
			  "Failed to allocate RCFW Channel: %#x\n", rc);
		जाओ fail;
	पूर्ण

	type = bnxt_qplib_get_ring_type(rdev->chip_ctx);
	creq = &rdev->rcfw.creq;
	rattr.dma_arr = creq->hwq.pbl[PBL_LVL_0].pg_map_arr;
	rattr.pages = creq->hwq.pbl[creq->hwq.level].pg_count;
	rattr.type = type;
	rattr.mode = RING_ALLOC_REQ_INT_MODE_MSIX;
	rattr.depth = BNXT_QPLIB_CREQE_MAX_CNT - 1;
	rattr.lrid = rdev->msix_entries[BNXT_RE_AEQ_IDX].ring_idx;
	rc = bnxt_re_net_ring_alloc(rdev, &rattr, &creq->ring_id);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "Failed to allocate CREQ: %#x\n", rc);
		जाओ मुक्त_rcfw;
	पूर्ण
	db_offt = bnxt_re_get_nqdb_offset(rdev, BNXT_RE_AEQ_IDX);
	vid = rdev->msix_entries[BNXT_RE_AEQ_IDX].vector;
	rc = bnxt_qplib_enable_rcfw_channel(&rdev->rcfw,
					    vid, db_offt, rdev->is_virtfn,
					    &bnxt_re_aeq_handler);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev, "Failed to enable RCFW channel: %#x\n",
			  rc);
		जाओ मुक्त_ring;
	पूर्ण

	rc = bnxt_qplib_get_dev_attr(&rdev->rcfw, &rdev->dev_attr,
				     rdev->is_virtfn);
	अगर (rc)
		जाओ disable_rcfw;

	bnxt_re_set_resource_limits(rdev);

	rc = bnxt_qplib_alloc_ctx(&rdev->qplib_res, &rdev->qplib_ctx, 0,
				  bnxt_qplib_is_chip_gen_p5(rdev->chip_ctx));
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev,
			  "Failed to allocate QPLIB context: %#x\n", rc);
		जाओ disable_rcfw;
	पूर्ण
	rc = bnxt_re_net_stats_ctx_alloc(rdev,
					 rdev->qplib_ctx.stats.dma_map,
					 &rdev->qplib_ctx.stats.fw_id);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev,
			  "Failed to allocate stats context: %#x\n", rc);
		जाओ मुक्त_ctx;
	पूर्ण

	rc = bnxt_qplib_init_rcfw(&rdev->rcfw, &rdev->qplib_ctx,
				  rdev->is_virtfn);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev,
			  "Failed to initialize RCFW: %#x\n", rc);
		जाओ मुक्त_sctx;
	पूर्ण
	set_bit(BNXT_RE_FLAG_RCFW_CHANNEL_EN, &rdev->flags);

	/* Resources based on the 'new' device caps */
	rc = bnxt_re_alloc_res(rdev);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev,
			  "Failed to allocate resources: %#x\n", rc);
		जाओ fail;
	पूर्ण
	set_bit(BNXT_RE_FLAG_RESOURCES_ALLOCATED, &rdev->flags);
	rc = bnxt_re_init_res(rdev);
	अगर (rc) अणु
		ibdev_err(&rdev->ibdev,
			  "Failed to initialize resources: %#x\n", rc);
		जाओ fail;
	पूर्ण

	set_bit(BNXT_RE_FLAG_RESOURCES_INITIALIZED, &rdev->flags);

	अगर (!rdev->is_virtfn) अणु
		rc = bnxt_re_setup_qos(rdev);
		अगर (rc)
			ibdev_info(&rdev->ibdev,
				   "RoCE priority not yet configured\n");

		INIT_DELAYED_WORK(&rdev->worker, bnxt_re_worker);
		set_bit(BNXT_RE_FLAG_QOS_WORK_REG, &rdev->flags);
		schedule_delayed_work(&rdev->worker, msecs_to_jअगरfies(30000));
	पूर्ण

	वापस 0;
मुक्त_sctx:
	bnxt_re_net_stats_ctx_मुक्त(rdev, rdev->qplib_ctx.stats.fw_id);
मुक्त_ctx:
	bnxt_qplib_मुक्त_ctx(&rdev->qplib_res, &rdev->qplib_ctx);
disable_rcfw:
	bnxt_qplib_disable_rcfw_channel(&rdev->rcfw);
मुक्त_ring:
	type = bnxt_qplib_get_ring_type(rdev->chip_ctx);
	bnxt_re_net_ring_मुक्त(rdev, rdev->rcfw.creq.ring_id, type);
मुक्त_rcfw:
	bnxt_qplib_मुक्त_rcfw_channel(&rdev->rcfw);
fail:
	bnxt_re_dev_uninit(rdev);

	वापस rc;
पूर्ण

अटल व्योम bnxt_re_dev_unreg(काष्ठा bnxt_re_dev *rdev)
अणु
	काष्ठा net_device *netdev = rdev->netdev;

	bnxt_re_dev_हटाओ(rdev);

	अगर (netdev)
		dev_put(netdev);
पूर्ण

अटल पूर्णांक bnxt_re_dev_reg(काष्ठा bnxt_re_dev **rdev, काष्ठा net_device *netdev)
अणु
	काष्ठा bnxt_en_dev *en_dev;
	पूर्णांक rc = 0;

	अगर (!is_bnxt_re_dev(netdev))
		वापस -ENODEV;

	en_dev = bnxt_re_dev_probe(netdev);
	अगर (IS_ERR(en_dev)) अणु
		अगर (en_dev != ERR_PTR(-ENODEV))
			ibdev_err(&(*rdev)->ibdev, "%s: Failed to probe\n",
				  ROCE_DRV_MODULE_NAME);
		rc = PTR_ERR(en_dev);
		जाओ निकास;
	पूर्ण
	*rdev = bnxt_re_dev_add(netdev, en_dev);
	अगर (!*rdev) अणु
		rc = -ENOMEM;
		dev_put(netdev);
		जाओ निकास;
	पूर्ण
निकास:
	वापस rc;
पूर्ण

अटल व्योम bnxt_re_हटाओ_device(काष्ठा bnxt_re_dev *rdev)
अणु
	bnxt_re_dev_uninit(rdev);
	pci_dev_put(rdev->en_dev->pdev);
	bnxt_re_dev_unreg(rdev);
पूर्ण

अटल पूर्णांक bnxt_re_add_device(काष्ठा bnxt_re_dev **rdev,
			      काष्ठा net_device *netdev, u8 wqe_mode)
अणु
	पूर्णांक rc;

	rc = bnxt_re_dev_reg(rdev, netdev);
	अगर (rc == -ENODEV)
		वापस rc;
	अगर (rc) अणु
		pr_err("Failed to register with the device %s: %#x\n",
		       netdev->name, rc);
		वापस rc;
	पूर्ण

	pci_dev_get((*rdev)->en_dev->pdev);
	rc = bnxt_re_dev_init(*rdev, wqe_mode);
	अगर (rc) अणु
		pci_dev_put((*rdev)->en_dev->pdev);
		bnxt_re_dev_unreg(*rdev);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम bnxt_re_dealloc_driver(काष्ठा ib_device *ib_dev)
अणु
	काष्ठा bnxt_re_dev *rdev =
		container_of(ib_dev, काष्ठा bnxt_re_dev, ibdev);

	dev_info(rdev_to_dev(rdev), "Unregistering Device");

	rtnl_lock();
	bnxt_re_हटाओ_device(rdev);
	rtnl_unlock();
पूर्ण

/* Handle all deferred netevents tasks */
अटल व्योम bnxt_re_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bnxt_re_work *re_work;
	काष्ठा bnxt_re_dev *rdev;
	पूर्णांक rc = 0;

	re_work = container_of(work, काष्ठा bnxt_re_work, work);
	rdev = re_work->rdev;

	अगर (re_work->event == NETDEV_REGISTER) अणु
		rc = bnxt_re_ib_init(rdev);
		अगर (rc) अणु
			ibdev_err(&rdev->ibdev,
				  "Failed to register with IB: %#x", rc);
			rtnl_lock();
			bnxt_re_हटाओ_device(rdev);
			rtnl_unlock();
			जाओ निकास;
		पूर्ण
		जाओ निकास;
	पूर्ण

	अगर (!ib_device_try_get(&rdev->ibdev))
		जाओ निकास;

	चयन (re_work->event) अणु
	हाल NETDEV_UP:
		bnxt_re_dispatch_event(&rdev->ibdev, शून्य, 1,
				       IB_EVENT_PORT_ACTIVE);
		अवरोध;
	हाल NETDEV_DOWN:
		bnxt_re_dev_stop(rdev);
		अवरोध;
	हाल NETDEV_CHANGE:
		अगर (!netअगर_carrier_ok(rdev->netdev))
			bnxt_re_dev_stop(rdev);
		अन्यथा अगर (netअगर_carrier_ok(rdev->netdev))
			bnxt_re_dispatch_event(&rdev->ibdev, शून्य, 1,
					       IB_EVENT_PORT_ACTIVE);
		ib_get_eth_speed(&rdev->ibdev, 1, &rdev->active_speed,
				 &rdev->active_width);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	ib_device_put(&rdev->ibdev);
निकास:
	put_device(&rdev->ibdev.dev);
	kमुक्त(re_work);
पूर्ण

/*
 * "Notअगरier chain callback can be invoked क्रम the same chain from
 * dअगरferent CPUs at the same समय".
 *
 * For हालs when the netdev is alपढ़ोy present, our call to the
 * रेजिस्टर_netdevice_notअगरier() will actually get the rtnl_lock()
 * beक्रमe sending NETDEV_REGISTER and (अगर up) NETDEV_UP
 * events.
 *
 * But क्रम हालs when the netdev is not alपढ़ोy present, the notअगरier
 * chain is subjected to be invoked from dअगरferent CPUs simultaneously.
 *
 * This is रक्षित by the netdev_mutex.
 */
अटल पूर्णांक bnxt_re_netdev_event(काष्ठा notअगरier_block *notअगरier,
				अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *real_dev, *netdev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा bnxt_re_work *re_work;
	काष्ठा bnxt_re_dev *rdev;
	पूर्णांक rc = 0;
	bool sch_work = false;
	bool release = true;

	real_dev = rdma_vlan_dev_real_dev(netdev);
	अगर (!real_dev)
		real_dev = netdev;

	rdev = bnxt_re_from_netdev(real_dev);
	अगर (!rdev && event != NETDEV_REGISTER)
		वापस NOTIFY_OK;

	अगर (real_dev != netdev)
		जाओ निकास;

	चयन (event) अणु
	हाल NETDEV_REGISTER:
		अगर (rdev)
			अवरोध;
		rc = bnxt_re_add_device(&rdev, real_dev,
					BNXT_QPLIB_WQE_MODE_STATIC);
		अगर (!rc)
			sch_work = true;
		release = false;
		अवरोध;

	हाल NETDEV_UNREGISTER:
		ib_unरेजिस्टर_device_queued(&rdev->ibdev);
		अवरोध;

	शेष:
		sch_work = true;
		अवरोध;
	पूर्ण
	अगर (sch_work) अणु
		/* Allocate क्रम the deferred task */
		re_work = kzalloc(माप(*re_work), GFP_ATOMIC);
		अगर (re_work) अणु
			get_device(&rdev->ibdev.dev);
			re_work->rdev = rdev;
			re_work->event = event;
			re_work->vlan_dev = (real_dev == netdev ?
					     शून्य : netdev);
			INIT_WORK(&re_work->work, bnxt_re_task);
			queue_work(bnxt_re_wq, &re_work->work);
		पूर्ण
	पूर्ण

निकास:
	अगर (rdev && release)
		ib_device_put(&rdev->ibdev);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block bnxt_re_netdev_notअगरier = अणु
	.notअगरier_call = bnxt_re_netdev_event
पूर्ण;

अटल पूर्णांक __init bnxt_re_mod_init(व्योम)
अणु
	पूर्णांक rc = 0;

	pr_info("%s: %s", ROCE_DRV_MODULE_NAME, version);

	bnxt_re_wq = create_singlethपढ़ो_workqueue("bnxt_re");
	अगर (!bnxt_re_wq)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&bnxt_re_dev_list);

	rc = रेजिस्टर_netdevice_notअगरier(&bnxt_re_netdev_notअगरier);
	अगर (rc) अणु
		pr_err("%s: Cannot register to netdevice_notifier",
		       ROCE_DRV_MODULE_NAME);
		जाओ err_netdev;
	पूर्ण
	वापस 0;

err_netdev:
	destroy_workqueue(bnxt_re_wq);

	वापस rc;
पूर्ण

अटल व्योम __निकास bnxt_re_mod_निकास(व्योम)
अणु
	काष्ठा bnxt_re_dev *rdev;

	unरेजिस्टर_netdevice_notअगरier(&bnxt_re_netdev_notअगरier);
	अगर (bnxt_re_wq)
		destroy_workqueue(bnxt_re_wq);
	list_क्रम_each_entry(rdev, &bnxt_re_dev_list, list) अणु
		/* VF device removal should be called beक्रमe the removal
		 * of PF device. Queue VFs unरेजिस्टर first, so that VFs
		 * shall be हटाओd beक्रमe the PF during the call of
		 * ib_unरेजिस्टर_driver.
		 */
		अगर (rdev->is_virtfn)
			ib_unरेजिस्टर_device(&rdev->ibdev);
	पूर्ण
	ib_unरेजिस्टर_driver(RDMA_DRIVER_BNXT_RE);
पूर्ण

module_init(bnxt_re_mod_init);
module_निकास(bnxt_re_mod_निकास);
