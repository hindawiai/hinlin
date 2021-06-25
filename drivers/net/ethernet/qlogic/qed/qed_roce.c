<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/अगर_vlan.h>
#समावेश "qed.h"
#समावेश "qed_cxt.h"
#समावेश "qed_dcbx.h"
#समावेश "qed_hsi.h"
#समावेश "qed_hw.h"
#समावेश "qed_init_ops.h"
#समावेश "qed_int.h"
#समावेश "qed_ll2.h"
#समावेश "qed_mcp.h"
#समावेश "qed_reg_addr.h"
#समावेश <linux/qed/qed_rdma_अगर.h>
#समावेश "qed_rdma.h"
#समावेश "qed_roce.h"
#समावेश "qed_sp.h"

अटल व्योम qed_roce_मुक्त_real_icid(काष्ठा qed_hwfn *p_hwfn, u16 icid);

अटल पूर्णांक qed_roce_async_event(काष्ठा qed_hwfn *p_hwfn, u8 fw_event_code,
				__le16 echo, जोड़ event_ring_data *data,
				u8 fw_वापस_code)
अणु
	काष्ठा qed_rdma_events events = p_hwfn->p_rdma_info->events;
	जोड़ rdma_eqe_data *rdata = &data->rdma_data;

	अगर (fw_event_code == ROCE_ASYNC_EVENT_DESTROY_QP_DONE) अणु
		u16 icid = (u16)le32_to_cpu(rdata->rdma_destroy_qp_data.cid);

		/* icid release in this async event can occur only अगर the icid
		 * was offloaded to the FW. In हाल it wasn't offloaded this is
		 * handled in qed_roce_sp_destroy_qp.
		 */
		qed_roce_मुक्त_real_icid(p_hwfn, icid);
	पूर्ण अन्यथा अगर (fw_event_code == ROCE_ASYNC_EVENT_SRQ_EMPTY ||
		   fw_event_code == ROCE_ASYNC_EVENT_SRQ_LIMIT) अणु
		u16 srq_id = (u16)le32_to_cpu(rdata->async_handle.lo);

		events.affiliated_event(events.context, fw_event_code,
					&srq_id);
	पूर्ण अन्यथा अणु
		events.affiliated_event(events.context, fw_event_code,
					(व्योम *)&rdata->async_handle);
	पूर्ण

	वापस 0;
पूर्ण

व्योम qed_roce_stop(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_bmap *rcid_map = &p_hwfn->p_rdma_info->real_cid_map;
	पूर्णांक रुको_count = 0;

	/* when destroying a_RoCE QP the control is वापसed to the user after
	 * the synchronous part. The asynchronous part may take a little दीर्घer.
	 * We delay क्रम a लघु जबतक अगर an async destroy QP is still expected.
	 * Beyond the added delay we clear the biपंचांगap anyway.
	 */
	जबतक (biपंचांगap_weight(rcid_map->biपंचांगap, rcid_map->max_count)) अणु
		msleep(100);
		अगर (रुको_count++ > 20) अणु
			DP_NOTICE(p_hwfn, "cid bitmap wait timed out\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qed_rdma_copy_gids(काष्ठा qed_rdma_qp *qp, __le32 *src_gid,
			       __le32 *dst_gid)
अणु
	u32 i;

	अगर (qp->roce_mode == ROCE_V2_IPV4) अणु
		/* The IPv4 addresses shall be aligned to the highest word.
		 * The lower words must be zero.
		 */
		स_रखो(src_gid, 0, माप(जोड़ qed_gid));
		स_रखो(dst_gid, 0, माप(जोड़ qed_gid));
		src_gid[3] = cpu_to_le32(qp->sgid.ipv4_addr);
		dst_gid[3] = cpu_to_le32(qp->dgid.ipv4_addr);
	पूर्ण अन्यथा अणु
		/* GIDs and IPv6 addresses coincide in location and size */
		क्रम (i = 0; i < ARRAY_SIZE(qp->sgid.dwords); i++) अणु
			src_gid[i] = cpu_to_le32(qp->sgid.dwords[i]);
			dst_gid[i] = cpu_to_le32(qp->dgid.dwords[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल क्रमागत roce_flavor qed_roce_mode_to_flavor(क्रमागत roce_mode roce_mode)
अणु
	चयन (roce_mode) अणु
	हाल ROCE_V1:
		वापस PLAIN_ROCE;
	हाल ROCE_V2_IPV4:
		वापस RROCE_IPV4;
	हाल ROCE_V2_IPV6:
		वापस RROCE_IPV6;
	शेष:
		वापस MAX_ROCE_FLAVOR;
	पूर्ण
पूर्ण

अटल व्योम qed_roce_मुक्त_cid_pair(काष्ठा qed_hwfn *p_hwfn, u16 cid)
अणु
	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	qed_bmap_release_id(p_hwfn, &p_hwfn->p_rdma_info->cid_map, cid);
	qed_bmap_release_id(p_hwfn, &p_hwfn->p_rdma_info->cid_map, cid + 1);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);
पूर्ण

पूर्णांक qed_roce_alloc_cid(काष्ठा qed_hwfn *p_hwfn, u16 *cid)
अणु
	काष्ठा qed_rdma_info *p_rdma_info = p_hwfn->p_rdma_info;
	u32 responder_icid;
	u32 requester_icid;
	पूर्णांक rc;

	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	rc = qed_rdma_bmap_alloc_id(p_hwfn, &p_rdma_info->cid_map,
				    &responder_icid);
	अगर (rc) अणु
		spin_unlock_bh(&p_rdma_info->lock);
		वापस rc;
	पूर्ण

	rc = qed_rdma_bmap_alloc_id(p_hwfn, &p_rdma_info->cid_map,
				    &requester_icid);

	spin_unlock_bh(&p_rdma_info->lock);
	अगर (rc)
		जाओ err;

	/* the two icid's should be adjacent */
	अगर ((requester_icid - responder_icid) != 1) अणु
		DP_NOTICE(p_hwfn, "Failed to allocate two adjacent qp's'\n");
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	responder_icid += qed_cxt_get_proto_cid_start(p_hwfn,
						      p_rdma_info->proto);
	requester_icid += qed_cxt_get_proto_cid_start(p_hwfn,
						      p_rdma_info->proto);

	/* If these icids require a new ILT line allocate DMA-able context क्रम
	 * an ILT page
	 */
	rc = qed_cxt_dynamic_ilt_alloc(p_hwfn, QED_ELEM_CXT, responder_icid);
	अगर (rc)
		जाओ err;

	rc = qed_cxt_dynamic_ilt_alloc(p_hwfn, QED_ELEM_CXT, requester_icid);
	अगर (rc)
		जाओ err;

	*cid = (u16)responder_icid;
	वापस rc;

err:
	spin_lock_bh(&p_rdma_info->lock);
	qed_bmap_release_id(p_hwfn, &p_rdma_info->cid_map, responder_icid);
	qed_bmap_release_id(p_hwfn, &p_rdma_info->cid_map, requester_icid);

	spin_unlock_bh(&p_rdma_info->lock);
	DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
		   "Allocate CID - failed, rc = %d\n", rc);
	वापस rc;
पूर्ण

अटल व्योम qed_roce_set_real_cid(काष्ठा qed_hwfn *p_hwfn, u32 cid)
अणु
	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	qed_bmap_set_id(p_hwfn, &p_hwfn->p_rdma_info->real_cid_map, cid);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);
पूर्ण

अटल u8 qed_roce_get_qp_tc(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_rdma_qp *qp)
अणु
	u8 pri, tc = 0;

	अगर (qp->vlan_id) अणु
		pri = (qp->vlan_id & VLAN_PRIO_MASK) >> VLAN_PRIO_SHIFT;
		tc = qed_dcbx_get_priority_tc(p_hwfn, pri);
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_SP,
		   "qp icid %u tc: %u (vlan priority %s)\n",
		   qp->icid, tc, qp->vlan_id ? "enabled" : "disabled");

	वापस tc;
पूर्ण

अटल पूर्णांक qed_roce_sp_create_responder(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_rdma_qp *qp)
अणु
	काष्ठा roce_create_qp_resp_ramrod_data *p_ramrod;
	u16 regular_latency_queue, low_latency_queue;
	काष्ठा qed_sp_init_data init_data;
	काष्ठा qed_spq_entry *p_ent;
	क्रमागत protocol_type proto;
	u32 flags = 0;
	पूर्णांक rc;
	u8 tc;

	अगर (!qp->has_resp)
		वापस 0;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "icid = %08x\n", qp->icid);

	/* Allocate DMA-able memory क्रम IRQ */
	qp->irq_num_pages = 1;
	qp->irq = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				     RDMA_RING_PAGE_SIZE,
				     &qp->irq_phys_addr, GFP_KERNEL);
	अगर (!qp->irq) अणु
		rc = -ENOMEM;
		DP_NOTICE(p_hwfn,
			  "qed create responder failed: cannot allocate memory (irq). rc = %d\n",
			  rc);
		वापस rc;
	पूर्ण

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent, ROCE_RAMROD_CREATE_QP,
				 PROTOCOLID_ROCE, &init_data);
	अगर (rc)
		जाओ err;

	SET_FIELD(flags, ROCE_CREATE_QP_RESP_RAMROD_DATA_ROCE_FLAVOR,
		  qed_roce_mode_to_flavor(qp->roce_mode));

	SET_FIELD(flags, ROCE_CREATE_QP_RESP_RAMROD_DATA_RDMA_RD_EN,
		  qp->incoming_rdma_पढ़ो_en);

	SET_FIELD(flags, ROCE_CREATE_QP_RESP_RAMROD_DATA_RDMA_WR_EN,
		  qp->incoming_rdma_ग_लिखो_en);

	SET_FIELD(flags, ROCE_CREATE_QP_RESP_RAMROD_DATA_ATOMIC_EN,
		  qp->incoming_atomic_en);

	SET_FIELD(flags, ROCE_CREATE_QP_RESP_RAMROD_DATA_E2E_FLOW_CONTROL_EN,
		  qp->e2e_flow_control_en);

	SET_FIELD(flags, ROCE_CREATE_QP_RESP_RAMROD_DATA_SRQ_FLG, qp->use_srq);

	SET_FIELD(flags, ROCE_CREATE_QP_RESP_RAMROD_DATA_RESERVED_KEY_EN,
		  qp->fmr_and_reserved_lkey);

	SET_FIELD(flags, ROCE_CREATE_QP_RESP_RAMROD_DATA_MIN_RNR_NAK_TIMER,
		  qp->min_rnr_nak_समयr);

	SET_FIELD(flags, ROCE_CREATE_QP_RESP_RAMROD_DATA_XRC_FLAG,
		  qed_rdma_is_xrc_qp(qp));

	p_ramrod = &p_ent->ramrod.roce_create_qp_resp;
	p_ramrod->flags = cpu_to_le32(flags);
	p_ramrod->max_ird = qp->max_rd_atomic_resp;
	p_ramrod->traffic_class = qp->traffic_class_tos;
	p_ramrod->hop_limit = qp->hop_limit_ttl;
	p_ramrod->irq_num_pages = qp->irq_num_pages;
	p_ramrod->p_key = cpu_to_le16(qp->pkey);
	p_ramrod->flow_label = cpu_to_le32(qp->flow_label);
	p_ramrod->dst_qp_id = cpu_to_le32(qp->dest_qp);
	p_ramrod->mtu = cpu_to_le16(qp->mtu);
	p_ramrod->initial_psn = cpu_to_le32(qp->rq_psn);
	p_ramrod->pd = cpu_to_le16(qp->pd);
	p_ramrod->rq_num_pages = cpu_to_le16(qp->rq_num_pages);
	DMA_REGPAIR_LE(p_ramrod->rq_pbl_addr, qp->rq_pbl_ptr);
	DMA_REGPAIR_LE(p_ramrod->irq_pbl_addr, qp->irq_phys_addr);
	qed_rdma_copy_gids(qp, p_ramrod->src_gid, p_ramrod->dst_gid);
	p_ramrod->qp_handle_क्रम_async.hi = qp->qp_handle_async.hi;
	p_ramrod->qp_handle_क्रम_async.lo = qp->qp_handle_async.lo;
	p_ramrod->qp_handle_क्रम_cqe.hi = qp->qp_handle.hi;
	p_ramrod->qp_handle_क्रम_cqe.lo = qp->qp_handle.lo;
	p_ramrod->cq_cid = cpu_to_le32((p_hwfn->hw_info.opaque_fid << 16) |
				       qp->rq_cq_id);
	p_ramrod->xrc_करोमुख्य = cpu_to_le16(qp->xrcd_id);

	tc = qed_roce_get_qp_tc(p_hwfn, qp);
	regular_latency_queue = qed_get_cm_pq_idx_ofld_mtc(p_hwfn, tc);
	low_latency_queue = qed_get_cm_pq_idx_llt_mtc(p_hwfn, tc);
	DP_VERBOSE(p_hwfn, QED_MSG_SP,
		   "qp icid %u pqs: regular_latency %u low_latency %u\n",
		   qp->icid, regular_latency_queue - CM_TX_PQ_BASE,
		   low_latency_queue - CM_TX_PQ_BASE);
	p_ramrod->regular_latency_phy_queue =
	    cpu_to_le16(regular_latency_queue);
	p_ramrod->low_latency_phy_queue =
	    cpu_to_le16(low_latency_queue);

	p_ramrod->dpi = cpu_to_le16(qp->dpi);

	qed_rdma_set_fw_mac(p_ramrod->remote_mac_addr, qp->remote_mac_addr);
	qed_rdma_set_fw_mac(p_ramrod->local_mac_addr, qp->local_mac_addr);

	p_ramrod->udp_src_port = cpu_to_le16(qp->udp_src_port);
	p_ramrod->vlan_id = cpu_to_le16(qp->vlan_id);
	p_ramrod->srq_id.srq_idx = cpu_to_le16(qp->srq_id);
	p_ramrod->srq_id.opaque_fid = cpu_to_le16(p_hwfn->hw_info.opaque_fid);

	p_ramrod->stats_counter_id = RESC_START(p_hwfn, QED_RDMA_STATS_QUEUE) +
				     qp->stats_queue;

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);
	अगर (rc)
		जाओ err;

	qp->resp_offloaded = true;
	qp->cq_prod = 0;

	proto = p_hwfn->p_rdma_info->proto;
	qed_roce_set_real_cid(p_hwfn, qp->icid -
			      qed_cxt_get_proto_cid_start(p_hwfn, proto));

	वापस rc;

err:
	DP_NOTICE(p_hwfn, "create responder - failed, rc = %d\n", rc);
	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
			  qp->irq_num_pages * RDMA_RING_PAGE_SIZE,
			  qp->irq, qp->irq_phys_addr);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_roce_sp_create_requester(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_rdma_qp *qp)
अणु
	काष्ठा roce_create_qp_req_ramrod_data *p_ramrod;
	u16 regular_latency_queue, low_latency_queue;
	काष्ठा qed_sp_init_data init_data;
	काष्ठा qed_spq_entry *p_ent;
	क्रमागत protocol_type proto;
	u16 flags = 0;
	पूर्णांक rc;
	u8 tc;

	अगर (!qp->has_req)
		वापस 0;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "icid = %08x\n", qp->icid);

	/* Allocate DMA-able memory क्रम ORQ */
	qp->orq_num_pages = 1;
	qp->orq = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				     RDMA_RING_PAGE_SIZE,
				     &qp->orq_phys_addr, GFP_KERNEL);
	अगर (!qp->orq) अणु
		rc = -ENOMEM;
		DP_NOTICE(p_hwfn,
			  "qed create requester failed: cannot allocate memory (orq). rc = %d\n",
			  rc);
		वापस rc;
	पूर्ण

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qp->icid + 1;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ROCE_RAMROD_CREATE_QP,
				 PROTOCOLID_ROCE, &init_data);
	अगर (rc)
		जाओ err;

	SET_FIELD(flags, ROCE_CREATE_QP_REQ_RAMROD_DATA_ROCE_FLAVOR,
		  qed_roce_mode_to_flavor(qp->roce_mode));

	SET_FIELD(flags, ROCE_CREATE_QP_REQ_RAMROD_DATA_FMR_AND_RESERVED_EN,
		  qp->fmr_and_reserved_lkey);

	SET_FIELD(flags, ROCE_CREATE_QP_REQ_RAMROD_DATA_SIGNALED_COMP,
		  qp->संकेत_all);

	SET_FIELD(flags, ROCE_CREATE_QP_REQ_RAMROD_DATA_ERR_RETRY_CNT,
		  qp->retry_cnt);

	SET_FIELD(flags, ROCE_CREATE_QP_REQ_RAMROD_DATA_RNR_NAK_CNT,
		  qp->rnr_retry_cnt);

	SET_FIELD(flags, ROCE_CREATE_QP_REQ_RAMROD_DATA_XRC_FLAG,
		  qed_rdma_is_xrc_qp(qp));

	p_ramrod = &p_ent->ramrod.roce_create_qp_req;
	p_ramrod->flags = cpu_to_le16(flags);

	SET_FIELD(p_ramrod->flags2, ROCE_CREATE_QP_REQ_RAMROD_DATA_EDPM_MODE,
		  qp->edpm_mode);

	p_ramrod->max_ord = qp->max_rd_atomic_req;
	p_ramrod->traffic_class = qp->traffic_class_tos;
	p_ramrod->hop_limit = qp->hop_limit_ttl;
	p_ramrod->orq_num_pages = qp->orq_num_pages;
	p_ramrod->p_key = cpu_to_le16(qp->pkey);
	p_ramrod->flow_label = cpu_to_le32(qp->flow_label);
	p_ramrod->dst_qp_id = cpu_to_le32(qp->dest_qp);
	p_ramrod->ack_समयout_val = cpu_to_le32(qp->ack_समयout);
	p_ramrod->mtu = cpu_to_le16(qp->mtu);
	p_ramrod->initial_psn = cpu_to_le32(qp->sq_psn);
	p_ramrod->pd = cpu_to_le16(qp->pd);
	p_ramrod->sq_num_pages = cpu_to_le16(qp->sq_num_pages);
	DMA_REGPAIR_LE(p_ramrod->sq_pbl_addr, qp->sq_pbl_ptr);
	DMA_REGPAIR_LE(p_ramrod->orq_pbl_addr, qp->orq_phys_addr);
	qed_rdma_copy_gids(qp, p_ramrod->src_gid, p_ramrod->dst_gid);
	p_ramrod->qp_handle_क्रम_async.hi = qp->qp_handle_async.hi;
	p_ramrod->qp_handle_क्रम_async.lo = qp->qp_handle_async.lo;
	p_ramrod->qp_handle_क्रम_cqe.hi = qp->qp_handle.hi;
	p_ramrod->qp_handle_क्रम_cqe.lo = qp->qp_handle.lo;
	p_ramrod->cq_cid =
	    cpu_to_le32((p_hwfn->hw_info.opaque_fid << 16) | qp->sq_cq_id);

	tc = qed_roce_get_qp_tc(p_hwfn, qp);
	regular_latency_queue = qed_get_cm_pq_idx_ofld_mtc(p_hwfn, tc);
	low_latency_queue = qed_get_cm_pq_idx_llt_mtc(p_hwfn, tc);
	DP_VERBOSE(p_hwfn, QED_MSG_SP,
		   "qp icid %u pqs: regular_latency %u low_latency %u\n",
		   qp->icid, regular_latency_queue - CM_TX_PQ_BASE,
		   low_latency_queue - CM_TX_PQ_BASE);
	p_ramrod->regular_latency_phy_queue =
	    cpu_to_le16(regular_latency_queue);
	p_ramrod->low_latency_phy_queue =
	    cpu_to_le16(low_latency_queue);

	p_ramrod->dpi = cpu_to_le16(qp->dpi);

	qed_rdma_set_fw_mac(p_ramrod->remote_mac_addr, qp->remote_mac_addr);
	qed_rdma_set_fw_mac(p_ramrod->local_mac_addr, qp->local_mac_addr);

	p_ramrod->udp_src_port = cpu_to_le16(qp->udp_src_port);
	p_ramrod->vlan_id = cpu_to_le16(qp->vlan_id);
	p_ramrod->stats_counter_id = RESC_START(p_hwfn, QED_RDMA_STATS_QUEUE) +
				     qp->stats_queue;

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);
	अगर (rc)
		जाओ err;

	qp->req_offloaded = true;
	proto = p_hwfn->p_rdma_info->proto;
	qed_roce_set_real_cid(p_hwfn,
			      qp->icid + 1 -
			      qed_cxt_get_proto_cid_start(p_hwfn, proto));

	वापस rc;

err:
	DP_NOTICE(p_hwfn, "Create requested - failed, rc = %d\n", rc);
	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
			  qp->orq_num_pages * RDMA_RING_PAGE_SIZE,
			  qp->orq, qp->orq_phys_addr);
	वापस rc;
पूर्ण

अटल पूर्णांक qed_roce_sp_modअगरy_responder(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_rdma_qp *qp,
					bool move_to_err, u32 modअगरy_flags)
अणु
	काष्ठा roce_modअगरy_qp_resp_ramrod_data *p_ramrod;
	काष्ठा qed_sp_init_data init_data;
	काष्ठा qed_spq_entry *p_ent;
	u16 flags = 0;
	पूर्णांक rc;

	अगर (!qp->has_resp)
		वापस 0;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "icid = %08x\n", qp->icid);

	अगर (move_to_err && !qp->resp_offloaded)
		वापस 0;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ROCE_EVENT_MODIFY_QP,
				 PROTOCOLID_ROCE, &init_data);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn, "rc = %d\n", rc);
		वापस rc;
	पूर्ण

	SET_FIELD(flags, ROCE_MODIFY_QP_RESP_RAMROD_DATA_MOVE_TO_ERR_FLG,
		  !!move_to_err);

	SET_FIELD(flags, ROCE_MODIFY_QP_RESP_RAMROD_DATA_RDMA_RD_EN,
		  qp->incoming_rdma_पढ़ो_en);

	SET_FIELD(flags, ROCE_MODIFY_QP_RESP_RAMROD_DATA_RDMA_WR_EN,
		  qp->incoming_rdma_ग_लिखो_en);

	SET_FIELD(flags, ROCE_MODIFY_QP_RESP_RAMROD_DATA_ATOMIC_EN,
		  qp->incoming_atomic_en);

	SET_FIELD(flags, ROCE_CREATE_QP_RESP_RAMROD_DATA_E2E_FLOW_CONTROL_EN,
		  qp->e2e_flow_control_en);

	SET_FIELD(flags, ROCE_MODIFY_QP_RESP_RAMROD_DATA_RDMA_OPS_EN_FLG,
		  GET_FIELD(modअगरy_flags,
			    QED_RDMA_MODIFY_QP_VALID_RDMA_OPS_EN));

	SET_FIELD(flags, ROCE_MODIFY_QP_RESP_RAMROD_DATA_P_KEY_FLG,
		  GET_FIELD(modअगरy_flags, QED_ROCE_MODIFY_QP_VALID_PKEY));

	SET_FIELD(flags, ROCE_MODIFY_QP_RESP_RAMROD_DATA_ADDRESS_VECTOR_FLG,
		  GET_FIELD(modअगरy_flags,
			    QED_ROCE_MODIFY_QP_VALID_ADDRESS_VECTOR));

	SET_FIELD(flags, ROCE_MODIFY_QP_RESP_RAMROD_DATA_MAX_IRD_FLG,
		  GET_FIELD(modअगरy_flags,
			    QED_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_RESP));

	SET_FIELD(flags, ROCE_MODIFY_QP_RESP_RAMROD_DATA_MIN_RNR_NAK_TIMER_FLG,
		  GET_FIELD(modअगरy_flags,
			    QED_ROCE_MODIFY_QP_VALID_MIN_RNR_NAK_TIMER));

	p_ramrod = &p_ent->ramrod.roce_modअगरy_qp_resp;
	p_ramrod->flags = cpu_to_le16(flags);

	p_ramrod->fields = 0;
	SET_FIELD(p_ramrod->fields,
		  ROCE_MODIFY_QP_RESP_RAMROD_DATA_MIN_RNR_NAK_TIMER,
		  qp->min_rnr_nak_समयr);

	p_ramrod->max_ird = qp->max_rd_atomic_resp;
	p_ramrod->traffic_class = qp->traffic_class_tos;
	p_ramrod->hop_limit = qp->hop_limit_ttl;
	p_ramrod->p_key = cpu_to_le16(qp->pkey);
	p_ramrod->flow_label = cpu_to_le32(qp->flow_label);
	p_ramrod->mtu = cpu_to_le16(qp->mtu);
	qed_rdma_copy_gids(qp, p_ramrod->src_gid, p_ramrod->dst_gid);
	rc = qed_spq_post(p_hwfn, p_ent, शून्य);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Modify responder, rc = %d\n", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक qed_roce_sp_modअगरy_requester(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_rdma_qp *qp,
					bool move_to_sqd,
					bool move_to_err, u32 modअगरy_flags)
अणु
	काष्ठा roce_modअगरy_qp_req_ramrod_data *p_ramrod;
	काष्ठा qed_sp_init_data init_data;
	काष्ठा qed_spq_entry *p_ent;
	u16 flags = 0;
	पूर्णांक rc;

	अगर (!qp->has_req)
		वापस 0;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "icid = %08x\n", qp->icid);

	अगर (move_to_err && !(qp->req_offloaded))
		वापस 0;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qp->icid + 1;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ROCE_EVENT_MODIFY_QP,
				 PROTOCOLID_ROCE, &init_data);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn, "rc = %d\n", rc);
		वापस rc;
	पूर्ण

	SET_FIELD(flags, ROCE_MODIFY_QP_REQ_RAMROD_DATA_MOVE_TO_ERR_FLG,
		  !!move_to_err);

	SET_FIELD(flags, ROCE_MODIFY_QP_REQ_RAMROD_DATA_MOVE_TO_SQD_FLG,
		  !!move_to_sqd);

	SET_FIELD(flags, ROCE_MODIFY_QP_REQ_RAMROD_DATA_EN_SQD_ASYNC_NOTIFY,
		  qp->sqd_async);

	SET_FIELD(flags, ROCE_MODIFY_QP_REQ_RAMROD_DATA_P_KEY_FLG,
		  GET_FIELD(modअगरy_flags, QED_ROCE_MODIFY_QP_VALID_PKEY));

	SET_FIELD(flags, ROCE_MODIFY_QP_REQ_RAMROD_DATA_ADDRESS_VECTOR_FLG,
		  GET_FIELD(modअगरy_flags,
			    QED_ROCE_MODIFY_QP_VALID_ADDRESS_VECTOR));

	SET_FIELD(flags, ROCE_MODIFY_QP_REQ_RAMROD_DATA_MAX_ORD_FLG,
		  GET_FIELD(modअगरy_flags,
			    QED_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_REQ));

	SET_FIELD(flags, ROCE_MODIFY_QP_REQ_RAMROD_DATA_RNR_NAK_CNT_FLG,
		  GET_FIELD(modअगरy_flags,
			    QED_ROCE_MODIFY_QP_VALID_RNR_RETRY_CNT));

	SET_FIELD(flags, ROCE_MODIFY_QP_REQ_RAMROD_DATA_ERR_RETRY_CNT_FLG,
		  GET_FIELD(modअगरy_flags, QED_ROCE_MODIFY_QP_VALID_RETRY_CNT));

	SET_FIELD(flags, ROCE_MODIFY_QP_REQ_RAMROD_DATA_ACK_TIMEOUT_FLG,
		  GET_FIELD(modअगरy_flags,
			    QED_ROCE_MODIFY_QP_VALID_ACK_TIMEOUT));

	p_ramrod = &p_ent->ramrod.roce_modअगरy_qp_req;
	p_ramrod->flags = cpu_to_le16(flags);

	p_ramrod->fields = 0;
	SET_FIELD(p_ramrod->fields,
		  ROCE_MODIFY_QP_REQ_RAMROD_DATA_ERR_RETRY_CNT, qp->retry_cnt);
	SET_FIELD(p_ramrod->fields, ROCE_MODIFY_QP_REQ_RAMROD_DATA_RNR_NAK_CNT,
		  qp->rnr_retry_cnt);

	p_ramrod->max_ord = qp->max_rd_atomic_req;
	p_ramrod->traffic_class = qp->traffic_class_tos;
	p_ramrod->hop_limit = qp->hop_limit_ttl;
	p_ramrod->p_key = cpu_to_le16(qp->pkey);
	p_ramrod->flow_label = cpu_to_le32(qp->flow_label);
	p_ramrod->ack_समयout_val = cpu_to_le32(qp->ack_समयout);
	p_ramrod->mtu = cpu_to_le16(qp->mtu);
	qed_rdma_copy_gids(qp, p_ramrod->src_gid, p_ramrod->dst_gid);
	rc = qed_spq_post(p_hwfn, p_ent, शून्य);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Modify requester, rc = %d\n", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक qed_roce_sp_destroy_qp_responder(काष्ठा qed_hwfn *p_hwfn,
					    काष्ठा qed_rdma_qp *qp,
					    u32 *cq_prod)
अणु
	काष्ठा roce_destroy_qp_resp_output_params *p_ramrod_res;
	काष्ठा roce_destroy_qp_resp_ramrod_data *p_ramrod;
	काष्ठा qed_sp_init_data init_data;
	काष्ठा qed_spq_entry *p_ent;
	dma_addr_t ramrod_res_phys;
	पूर्णांक rc;

	अगर (!qp->has_resp) अणु
		*cq_prod = 0;
		वापस 0;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "icid = %08x\n", qp->icid);
	*cq_prod = qp->cq_prod;

	अगर (!qp->resp_offloaded) अणु
		/* If a responder was never offload, we need to मुक्त the cids
		 * allocated in create_qp as a FW async event will never arrive
		 */
		u32 cid;

		cid = qp->icid -
		      qed_cxt_get_proto_cid_start(p_hwfn,
						  p_hwfn->p_rdma_info->proto);
		qed_roce_मुक्त_cid_pair(p_hwfn, (u16)cid);

		वापस 0;
	पूर्ण

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ROCE_RAMROD_DESTROY_QP,
				 PROTOCOLID_ROCE, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.roce_destroy_qp_resp;

	p_ramrod_res = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
					  माप(*p_ramrod_res),
					  &ramrod_res_phys, GFP_KERNEL);

	अगर (!p_ramrod_res) अणु
		rc = -ENOMEM;
		DP_NOTICE(p_hwfn,
			  "qed destroy responder failed: cannot allocate memory (ramrod). rc = %d\n",
			  rc);
		qed_sp_destroy_request(p_hwfn, p_ent);
		वापस rc;
	पूर्ण

	DMA_REGPAIR_LE(p_ramrod->output_params_addr, ramrod_res_phys);

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);
	अगर (rc)
		जाओ err;

	*cq_prod = le32_to_cpu(p_ramrod_res->cq_prod);
	qp->cq_prod = *cq_prod;

	/* Free IRQ - only अगर ramrod succeeded, in हाल FW is still using it */
	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
			  qp->irq_num_pages * RDMA_RING_PAGE_SIZE,
			  qp->irq, qp->irq_phys_addr);

	qp->resp_offloaded = false;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Destroy responder, rc = %d\n", rc);

err:
	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
			  माप(काष्ठा roce_destroy_qp_resp_output_params),
			  p_ramrod_res, ramrod_res_phys);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_roce_sp_destroy_qp_requester(काष्ठा qed_hwfn *p_hwfn,
					    काष्ठा qed_rdma_qp *qp)
अणु
	काष्ठा roce_destroy_qp_req_output_params *p_ramrod_res;
	काष्ठा roce_destroy_qp_req_ramrod_data *p_ramrod;
	काष्ठा qed_sp_init_data init_data;
	काष्ठा qed_spq_entry *p_ent;
	dma_addr_t ramrod_res_phys;
	पूर्णांक rc = -ENOMEM;

	अगर (!qp->has_req)
		वापस 0;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "icid = %08x\n", qp->icid);

	अगर (!qp->req_offloaded)
		वापस 0;

	p_ramrod_res = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
					  माप(*p_ramrod_res),
					  &ramrod_res_phys, GFP_KERNEL);
	अगर (!p_ramrod_res) अणु
		DP_NOTICE(p_hwfn,
			  "qed destroy requester failed: cannot allocate memory (ramrod)\n");
		वापस rc;
	पूर्ण

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qp->icid + 1;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent, ROCE_RAMROD_DESTROY_QP,
				 PROTOCOLID_ROCE, &init_data);
	अगर (rc)
		जाओ err;

	p_ramrod = &p_ent->ramrod.roce_destroy_qp_req;
	DMA_REGPAIR_LE(p_ramrod->output_params_addr, ramrod_res_phys);

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);
	अगर (rc)
		जाओ err;


	/* Free ORQ - only अगर ramrod succeeded, in हाल FW is still using it */
	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
			  qp->orq_num_pages * RDMA_RING_PAGE_SIZE,
			  qp->orq, qp->orq_phys_addr);

	qp->req_offloaded = false;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Destroy requester, rc = %d\n", rc);

err:
	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev, माप(*p_ramrod_res),
			  p_ramrod_res, ramrod_res_phys);

	वापस rc;
पूर्ण

पूर्णांक qed_roce_query_qp(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_rdma_qp *qp,
		      काष्ठा qed_rdma_query_qp_out_params *out_params)
अणु
	काष्ठा roce_query_qp_resp_output_params *p_resp_ramrod_res;
	काष्ठा roce_query_qp_req_output_params *p_req_ramrod_res;
	काष्ठा roce_query_qp_resp_ramrod_data *p_resp_ramrod;
	काष्ठा roce_query_qp_req_ramrod_data *p_req_ramrod;
	काष्ठा qed_sp_init_data init_data;
	dma_addr_t resp_ramrod_res_phys;
	dma_addr_t req_ramrod_res_phys;
	काष्ठा qed_spq_entry *p_ent;
	bool rq_err_state;
	bool sq_err_state;
	bool sq_draining;
	पूर्णांक rc = -ENOMEM;

	अगर ((!(qp->resp_offloaded)) && (!(qp->req_offloaded))) अणु
		/* We can't send ramrod to the fw since this qp wasn't offloaded
		 * to the fw yet
		 */
		out_params->draining = false;
		out_params->rq_psn = qp->rq_psn;
		out_params->sq_psn = qp->sq_psn;
		out_params->state = qp->cur_state;

		DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "No QPs as no offload\n");
		वापस 0;
	पूर्ण

	अगर (!(qp->resp_offloaded)) अणु
		DP_NOTICE(p_hwfn,
			  "The responder's qp should be offloaded before requester's\n");
		वापस -EINVAL;
	पूर्ण

	/* Send a query responder ramrod to FW to get RQ-PSN and state */
	p_resp_ramrod_res =
		dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				   माप(*p_resp_ramrod_res),
				   &resp_ramrod_res_phys, GFP_KERNEL);
	अगर (!p_resp_ramrod_res) अणु
		DP_NOTICE(p_hwfn,
			  "qed query qp failed: cannot allocate memory (ramrod)\n");
		वापस rc;
	पूर्ण

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;
	rc = qed_sp_init_request(p_hwfn, &p_ent, ROCE_RAMROD_QUERY_QP,
				 PROTOCOLID_ROCE, &init_data);
	अगर (rc)
		जाओ err_resp;

	p_resp_ramrod = &p_ent->ramrod.roce_query_qp_resp;
	DMA_REGPAIR_LE(p_resp_ramrod->output_params_addr, resp_ramrod_res_phys);

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);
	अगर (rc)
		जाओ err_resp;

	out_params->rq_psn = le32_to_cpu(p_resp_ramrod_res->psn);
	rq_err_state = GET_FIELD(le32_to_cpu(p_resp_ramrod_res->flags),
				 ROCE_QUERY_QP_RESP_OUTPUT_PARAMS_ERROR_FLG);

	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev, माप(*p_resp_ramrod_res),
			  p_resp_ramrod_res, resp_ramrod_res_phys);

	अगर (!(qp->req_offloaded)) अणु
		/* Don't send query qp क्रम the requester */
		out_params->sq_psn = qp->sq_psn;
		out_params->draining = false;

		अगर (rq_err_state)
			qp->cur_state = QED_ROCE_QP_STATE_ERR;

		out_params->state = qp->cur_state;

		वापस 0;
	पूर्ण

	/* Send a query requester ramrod to FW to get SQ-PSN and state */
	p_req_ramrod_res = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
					      माप(*p_req_ramrod_res),
					      &req_ramrod_res_phys,
					      GFP_KERNEL);
	अगर (!p_req_ramrod_res) अणु
		rc = -ENOMEM;
		DP_NOTICE(p_hwfn,
			  "qed query qp failed: cannot allocate memory (ramrod)\n");
		वापस rc;
	पूर्ण

	/* Get SPQ entry */
	init_data.cid = qp->icid + 1;
	rc = qed_sp_init_request(p_hwfn, &p_ent, ROCE_RAMROD_QUERY_QP,
				 PROTOCOLID_ROCE, &init_data);
	अगर (rc)
		जाओ err_req;

	p_req_ramrod = &p_ent->ramrod.roce_query_qp_req;
	DMA_REGPAIR_LE(p_req_ramrod->output_params_addr, req_ramrod_res_phys);

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);
	अगर (rc)
		जाओ err_req;

	out_params->sq_psn = le32_to_cpu(p_req_ramrod_res->psn);
	sq_err_state = GET_FIELD(le32_to_cpu(p_req_ramrod_res->flags),
				 ROCE_QUERY_QP_REQ_OUTPUT_PARAMS_ERR_FLG);
	sq_draining =
		GET_FIELD(le32_to_cpu(p_req_ramrod_res->flags),
			  ROCE_QUERY_QP_REQ_OUTPUT_PARAMS_SQ_DRAINING_FLG);

	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev, माप(*p_req_ramrod_res),
			  p_req_ramrod_res, req_ramrod_res_phys);

	out_params->draining = false;

	अगर (rq_err_state || sq_err_state)
		qp->cur_state = QED_ROCE_QP_STATE_ERR;
	अन्यथा अगर (sq_draining)
		out_params->draining = true;
	out_params->state = qp->cur_state;

	वापस 0;

err_req:
	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev, माप(*p_req_ramrod_res),
			  p_req_ramrod_res, req_ramrod_res_phys);
	वापस rc;
err_resp:
	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev, माप(*p_resp_ramrod_res),
			  p_resp_ramrod_res, resp_ramrod_res_phys);
	वापस rc;
पूर्ण

पूर्णांक qed_roce_destroy_qp(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_rdma_qp *qp)
अणु
	u32 cq_prod;
	पूर्णांक rc;

	/* Destroys the specअगरied QP */
	अगर ((qp->cur_state != QED_ROCE_QP_STATE_RESET) &&
	    (qp->cur_state != QED_ROCE_QP_STATE_ERR) &&
	    (qp->cur_state != QED_ROCE_QP_STATE_INIT)) अणु
		DP_NOTICE(p_hwfn,
			  "QP must be in error, reset or init state before destroying it\n");
		वापस -EINVAL;
	पूर्ण

	अगर (qp->cur_state != QED_ROCE_QP_STATE_RESET) अणु
		rc = qed_roce_sp_destroy_qp_responder(p_hwfn, qp,
						      &cq_prod);
		अगर (rc)
			वापस rc;

		/* Send destroy requester ramrod */
		rc = qed_roce_sp_destroy_qp_requester(p_hwfn, qp);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qed_roce_modअगरy_qp(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_rdma_qp *qp,
		       क्रमागत qed_roce_qp_state prev_state,
		       काष्ठा qed_rdma_modअगरy_qp_in_params *params)
अणु
	पूर्णांक rc = 0;

	/* Perक्रमm additional operations according to the current state and the
	 * next state
	 */
	अगर (((prev_state == QED_ROCE_QP_STATE_INIT) ||
	     (prev_state == QED_ROCE_QP_STATE_RESET)) &&
	    (qp->cur_state == QED_ROCE_QP_STATE_RTR)) अणु
		/* Init->RTR or Reset->RTR */
		rc = qed_roce_sp_create_responder(p_hwfn, qp);
		वापस rc;
	पूर्ण अन्यथा अगर ((prev_state == QED_ROCE_QP_STATE_RTR) &&
		   (qp->cur_state == QED_ROCE_QP_STATE_RTS)) अणु
		/* RTR-> RTS */
		rc = qed_roce_sp_create_requester(p_hwfn, qp);
		अगर (rc)
			वापस rc;

		/* Send modअगरy responder ramrod */
		rc = qed_roce_sp_modअगरy_responder(p_hwfn, qp, false,
						  params->modअगरy_flags);
		वापस rc;
	पूर्ण अन्यथा अगर ((prev_state == QED_ROCE_QP_STATE_RTS) &&
		   (qp->cur_state == QED_ROCE_QP_STATE_RTS)) अणु
		/* RTS->RTS */
		rc = qed_roce_sp_modअगरy_responder(p_hwfn, qp, false,
						  params->modअगरy_flags);
		अगर (rc)
			वापस rc;

		rc = qed_roce_sp_modअगरy_requester(p_hwfn, qp, false, false,
						  params->modअगरy_flags);
		वापस rc;
	पूर्ण अन्यथा अगर ((prev_state == QED_ROCE_QP_STATE_RTS) &&
		   (qp->cur_state == QED_ROCE_QP_STATE_SQD)) अणु
		/* RTS->SQD */
		rc = qed_roce_sp_modअगरy_requester(p_hwfn, qp, true, false,
						  params->modअगरy_flags);
		वापस rc;
	पूर्ण अन्यथा अगर ((prev_state == QED_ROCE_QP_STATE_SQD) &&
		   (qp->cur_state == QED_ROCE_QP_STATE_SQD)) अणु
		/* SQD->SQD */
		rc = qed_roce_sp_modअगरy_responder(p_hwfn, qp, false,
						  params->modअगरy_flags);
		अगर (rc)
			वापस rc;

		rc = qed_roce_sp_modअगरy_requester(p_hwfn, qp, false, false,
						  params->modअगरy_flags);
		वापस rc;
	पूर्ण अन्यथा अगर ((prev_state == QED_ROCE_QP_STATE_SQD) &&
		   (qp->cur_state == QED_ROCE_QP_STATE_RTS)) अणु
		/* SQD->RTS */
		rc = qed_roce_sp_modअगरy_responder(p_hwfn, qp, false,
						  params->modअगरy_flags);
		अगर (rc)
			वापस rc;

		rc = qed_roce_sp_modअगरy_requester(p_hwfn, qp, false, false,
						  params->modअगरy_flags);

		वापस rc;
	पूर्ण अन्यथा अगर (qp->cur_state == QED_ROCE_QP_STATE_ERR) अणु
		/* ->ERR */
		rc = qed_roce_sp_modअगरy_responder(p_hwfn, qp, true,
						  params->modअगरy_flags);
		अगर (rc)
			वापस rc;

		rc = qed_roce_sp_modअगरy_requester(p_hwfn, qp, false, true,
						  params->modअगरy_flags);
		वापस rc;
	पूर्ण अन्यथा अगर (qp->cur_state == QED_ROCE_QP_STATE_RESET) अणु
		/* Any state -> RESET */
		u32 cq_prod;

		/* Send destroy responder ramrod */
		rc = qed_roce_sp_destroy_qp_responder(p_hwfn,
						      qp,
						      &cq_prod);

		अगर (rc)
			वापस rc;

		qp->cq_prod = cq_prod;

		rc = qed_roce_sp_destroy_qp_requester(p_hwfn, qp);
	पूर्ण अन्यथा अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "0\n");
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम qed_roce_मुक्त_real_icid(काष्ठा qed_hwfn *p_hwfn, u16 icid)
अणु
	काष्ठा qed_rdma_info *p_rdma_info = p_hwfn->p_rdma_info;
	u32 start_cid, cid, xcid;

	/* an even icid beदीर्घs to a responder जबतक an odd icid beदीर्घs to a
	 * requester. The 'cid' received as an input can be either. We calculate
	 * the "partner" icid and call it xcid. Only अगर both are मुक्त then the
	 * "cid" map can be cleared.
	 */
	start_cid = qed_cxt_get_proto_cid_start(p_hwfn, p_rdma_info->proto);
	cid = icid - start_cid;
	xcid = cid ^ 1;

	spin_lock_bh(&p_rdma_info->lock);

	qed_bmap_release_id(p_hwfn, &p_rdma_info->real_cid_map, cid);
	अगर (qed_bmap_test_id(p_hwfn, &p_rdma_info->real_cid_map, xcid) == 0) अणु
		qed_bmap_release_id(p_hwfn, &p_rdma_info->cid_map, cid);
		qed_bmap_release_id(p_hwfn, &p_rdma_info->cid_map, xcid);
	पूर्ण

	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);
पूर्ण

व्योम qed_roce_dpm_dcbx(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u8 val;

	/* अगर any QPs are alपढ़ोy active, we want to disable DPM, since their
	 * context inक्रमmation contains inक्रमmation from beक्रमe the latest DCBx
	 * update. Otherwise enable it.
	 */
	val = qed_rdma_allocated_qps(p_hwfn) ? true : false;
	p_hwfn->dcbx_no_edpm = (u8)val;

	qed_rdma_dpm_conf(p_hwfn, p_ptt);
पूर्ण

पूर्णांक qed_roce_setup(काष्ठा qed_hwfn *p_hwfn)
अणु
	वापस qed_spq_रेजिस्टर_async_cb(p_hwfn, PROTOCOLID_ROCE,
					 qed_roce_async_event);
पूर्ण

पूर्णांक qed_roce_init_hw(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 ll2_ethertype_en;

	qed_wr(p_hwfn, p_ptt, PRS_REG_ROCE_DEST_QP_MAX_PF, 0);

	p_hwfn->rdma_prs_search_reg = PRS_REG_SEARCH_ROCE;

	ll2_ethertype_en = qed_rd(p_hwfn, p_ptt, PRS_REG_LIGHT_L2_ETHERTYPE_EN);
	qed_wr(p_hwfn, p_ptt, PRS_REG_LIGHT_L2_ETHERTYPE_EN,
	       (ll2_ethertype_en | 0x01));

	अगर (qed_cxt_get_proto_cid_start(p_hwfn, PROTOCOLID_ROCE) % 2) अणु
		DP_NOTICE(p_hwfn, "The first RoCE's cid should be even\n");
		वापस -EINVAL;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Initializing HW - Done\n");
	वापस 0;
पूर्ण
