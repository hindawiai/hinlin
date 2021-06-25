<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/tcp.h>
#समावेश "qed_cxt.h"
#समावेश "qed_hw.h"
#समावेश "qed_ll2.h"
#समावेश "qed_rdma.h"
#समावेश "qed_reg_addr.h"
#समावेश "qed_sp.h"
#समावेश "qed_ooo.h"

#घोषणा QED_IWARP_ORD_DEFAULT		32
#घोषणा QED_IWARP_IRD_DEFAULT		32
#घोषणा QED_IWARP_MAX_FW_MSS		4120

#घोषणा QED_EP_SIG 0xecabcdef

काष्ठा mpa_v2_hdr अणु
	__be16 ird;
	__be16 ord;
पूर्ण;

#घोषणा MPA_V2_PEER2PEER_MODEL  0x8000
#घोषणा MPA_V2_SEND_RTR         0x4000	/* on ird */
#घोषणा MPA_V2_READ_RTR         0x4000	/* on ord */
#घोषणा MPA_V2_WRITE_RTR        0x8000
#घोषणा MPA_V2_IRD_ORD_MASK     0x3FFF

#घोषणा MPA_REV2(_mpa_rev) ((_mpa_rev) == MPA_NEGOTIATION_TYPE_ENHANCED)

#घोषणा QED_IWARP_INVALID_TCP_CID	0xffffffff

#घोषणा QED_IWARP_RCV_WND_SIZE_DEF_BB_2P (200 * 1024)
#घोषणा QED_IWARP_RCV_WND_SIZE_DEF_BB_4P (100 * 1024)
#घोषणा QED_IWARP_RCV_WND_SIZE_DEF_AH_2P (150 * 1024)
#घोषणा QED_IWARP_RCV_WND_SIZE_DEF_AH_4P (90 * 1024)

#घोषणा QED_IWARP_RCV_WND_SIZE_MIN	(0xffff)
#घोषणा TIMESTAMP_HEADER_SIZE		(12)
#घोषणा QED_IWARP_MAX_FIN_RT_DEFAULT	(2)

#घोषणा QED_IWARP_TS_EN			BIT(0)
#घोषणा QED_IWARP_DA_EN			BIT(1)
#घोषणा QED_IWARP_PARAM_CRC_NEEDED	(1)
#घोषणा QED_IWARP_PARAM_P2P		(1)

#घोषणा QED_IWARP_DEF_MAX_RT_TIME	(0)
#घोषणा QED_IWARP_DEF_CWND_FACTOR	(4)
#घोषणा QED_IWARP_DEF_KA_MAX_PROBE_CNT	(5)
#घोषणा QED_IWARP_DEF_KA_TIMEOUT	(1200000)	/* 20 min */
#घोषणा QED_IWARP_DEF_KA_INTERVAL	(1000)		/* 1 sec */

अटल पूर्णांक qed_iwarp_async_event(काष्ठा qed_hwfn *p_hwfn, u8 fw_event_code,
				 __le16 echo, जोड़ event_ring_data *data,
				 u8 fw_वापस_code);

/* Override devinfo with iWARP specअगरic values */
व्योम qed_iwarp_init_devinfo(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_rdma_device *dev = p_hwfn->p_rdma_info->dev;

	dev->max_अंतरभूत = IWARP_REQ_MAX_INLINE_DATA_SIZE;
	dev->max_qp = min_t(u32,
			    IWARP_MAX_QPS,
			    p_hwfn->p_rdma_info->num_qps) -
		      QED_IWARP_PREALLOC_CNT;

	dev->max_cq = dev->max_qp;

	dev->max_qp_resp_rd_atomic_resc = QED_IWARP_IRD_DEFAULT;
	dev->max_qp_req_rd_atomic_resc = QED_IWARP_ORD_DEFAULT;
पूर्ण

व्योम qed_iwarp_init_hw(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	p_hwfn->rdma_prs_search_reg = PRS_REG_SEARCH_TCP;
	qed_wr(p_hwfn, p_ptt, p_hwfn->rdma_prs_search_reg, 1);
	p_hwfn->b_rdma_enabled_in_prs = true;
पूर्ण

/* We have two cid maps, one क्रम tcp which should be used only from passive
 * syn processing and replacing a pre-allocated ep in the list. The second
 * क्रम active tcp and क्रम QPs.
 */
अटल व्योम qed_iwarp_cid_cleaned(काष्ठा qed_hwfn *p_hwfn, u32 cid)
अणु
	cid -= qed_cxt_get_proto_cid_start(p_hwfn, p_hwfn->p_rdma_info->proto);

	spin_lock_bh(&p_hwfn->p_rdma_info->lock);

	अगर (cid < QED_IWARP_PREALLOC_CNT)
		qed_bmap_release_id(p_hwfn, &p_hwfn->p_rdma_info->tcp_cid_map,
				    cid);
	अन्यथा
		qed_bmap_release_id(p_hwfn, &p_hwfn->p_rdma_info->cid_map, cid);

	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);
पूर्ण

व्योम
qed_iwarp_init_fw_ramrod(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा iwarp_init_func_ramrod_data *p_ramrod)
अणु
	p_ramrod->iwarp.ll2_ooo_q_index =
	    RESC_START(p_hwfn, QED_LL2_RAM_QUEUE) +
	    p_hwfn->p_rdma_info->iwarp.ll2_ooo_handle;

	p_ramrod->tcp.max_fin_rt = QED_IWARP_MAX_FIN_RT_DEFAULT;

	वापस;
पूर्ण

अटल पूर्णांक qed_iwarp_alloc_cid(काष्ठा qed_hwfn *p_hwfn, u32 *cid)
अणु
	पूर्णांक rc;

	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	rc = qed_rdma_bmap_alloc_id(p_hwfn, &p_hwfn->p_rdma_info->cid_map, cid);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn, "Failed in allocating iwarp cid\n");
		वापस rc;
	पूर्ण
	*cid += qed_cxt_get_proto_cid_start(p_hwfn, p_hwfn->p_rdma_info->proto);

	rc = qed_cxt_dynamic_ilt_alloc(p_hwfn, QED_ELEM_CXT, *cid);
	अगर (rc)
		qed_iwarp_cid_cleaned(p_hwfn, *cid);

	वापस rc;
पूर्ण

अटल व्योम qed_iwarp_set_tcp_cid(काष्ठा qed_hwfn *p_hwfn, u32 cid)
अणु
	cid -= qed_cxt_get_proto_cid_start(p_hwfn, p_hwfn->p_rdma_info->proto);

	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	qed_bmap_set_id(p_hwfn, &p_hwfn->p_rdma_info->tcp_cid_map, cid);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);
पूर्ण

/* This function allocates a cid क्रम passive tcp (called from syn receive)
 * the reason it's separate from the regular cid allocation is because it
 * is assured that these cids alपढ़ोy have ilt allocated. They are pपुनः_स्मृतिated
 * to ensure that we won't need to allocate memory during syn processing
 */
अटल पूर्णांक qed_iwarp_alloc_tcp_cid(काष्ठा qed_hwfn *p_hwfn, u32 *cid)
अणु
	पूर्णांक rc;

	spin_lock_bh(&p_hwfn->p_rdma_info->lock);

	rc = qed_rdma_bmap_alloc_id(p_hwfn,
				    &p_hwfn->p_rdma_info->tcp_cid_map, cid);

	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);

	अगर (rc) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "can't allocate iwarp tcp cid max-count=%d\n",
			   p_hwfn->p_rdma_info->tcp_cid_map.max_count);

		*cid = QED_IWARP_INVALID_TCP_CID;
		वापस rc;
	पूर्ण

	*cid += qed_cxt_get_proto_cid_start(p_hwfn,
					    p_hwfn->p_rdma_info->proto);
	वापस 0;
पूर्ण

पूर्णांक qed_iwarp_create_qp(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_rdma_qp *qp,
			काष्ठा qed_rdma_create_qp_out_params *out_params)
अणु
	काष्ठा iwarp_create_qp_ramrod_data *p_ramrod;
	काष्ठा qed_sp_init_data init_data;
	काष्ठा qed_spq_entry *p_ent;
	u16 physical_queue;
	u32 cid;
	पूर्णांक rc;

	qp->shared_queue = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
					      IWARP_SHARED_QUEUE_PAGE_SIZE,
					      &qp->shared_queue_phys_addr,
					      GFP_KERNEL);
	अगर (!qp->shared_queue)
		वापस -ENOMEM;

	out_params->sq_pbl_virt = (u8 *)qp->shared_queue +
	    IWARP_SHARED_QUEUE_PAGE_SQ_PBL_OFFSET;
	out_params->sq_pbl_phys = qp->shared_queue_phys_addr +
	    IWARP_SHARED_QUEUE_PAGE_SQ_PBL_OFFSET;
	out_params->rq_pbl_virt = (u8 *)qp->shared_queue +
	    IWARP_SHARED_QUEUE_PAGE_RQ_PBL_OFFSET;
	out_params->rq_pbl_phys = qp->shared_queue_phys_addr +
	    IWARP_SHARED_QUEUE_PAGE_RQ_PBL_OFFSET;

	rc = qed_iwarp_alloc_cid(p_hwfn, &cid);
	अगर (rc)
		जाओ err1;

	qp->icid = (u16)cid;

	स_रखो(&init_data, 0, माप(init_data));
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.cid = qp->icid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 IWARP_RAMROD_CMD_ID_CREATE_QP,
				 PROTOCOLID_IWARP, &init_data);
	अगर (rc)
		जाओ err2;

	p_ramrod = &p_ent->ramrod.iwarp_create_qp;

	SET_FIELD(p_ramrod->flags,
		  IWARP_CREATE_QP_RAMROD_DATA_FMR_AND_RESERVED_EN,
		  qp->fmr_and_reserved_lkey);

	SET_FIELD(p_ramrod->flags,
		  IWARP_CREATE_QP_RAMROD_DATA_SIGNALED_COMP, qp->संकेत_all);

	SET_FIELD(p_ramrod->flags,
		  IWARP_CREATE_QP_RAMROD_DATA_RDMA_RD_EN,
		  qp->incoming_rdma_पढ़ो_en);

	SET_FIELD(p_ramrod->flags,
		  IWARP_CREATE_QP_RAMROD_DATA_RDMA_WR_EN,
		  qp->incoming_rdma_ग_लिखो_en);

	SET_FIELD(p_ramrod->flags,
		  IWARP_CREATE_QP_RAMROD_DATA_ATOMIC_EN,
		  qp->incoming_atomic_en);

	SET_FIELD(p_ramrod->flags,
		  IWARP_CREATE_QP_RAMROD_DATA_SRQ_FLG, qp->use_srq);

	p_ramrod->pd = cpu_to_le16(qp->pd);
	p_ramrod->sq_num_pages = cpu_to_le16(qp->sq_num_pages);
	p_ramrod->rq_num_pages = cpu_to_le16(qp->rq_num_pages);

	p_ramrod->srq_id.srq_idx = cpu_to_le16(qp->srq_id);
	p_ramrod->srq_id.opaque_fid = cpu_to_le16(p_hwfn->hw_info.opaque_fid);
	p_ramrod->qp_handle_क्रम_cqe.hi = qp->qp_handle.hi;
	p_ramrod->qp_handle_क्रम_cqe.lo = qp->qp_handle.lo;

	p_ramrod->cq_cid_क्रम_sq =
	    cpu_to_le32((p_hwfn->hw_info.opaque_fid << 16) | qp->sq_cq_id);
	p_ramrod->cq_cid_क्रम_rq =
	    cpu_to_le32((p_hwfn->hw_info.opaque_fid << 16) | qp->rq_cq_id);

	p_ramrod->dpi = cpu_to_le16(qp->dpi);

	physical_queue = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_OFLD);
	p_ramrod->physical_q0 = cpu_to_le16(physical_queue);
	physical_queue = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_ACK);
	p_ramrod->physical_q1 = cpu_to_le16(physical_queue);

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);
	अगर (rc)
		जाओ err2;

	वापस rc;

err2:
	qed_iwarp_cid_cleaned(p_hwfn, cid);
err1:
	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
			  IWARP_SHARED_QUEUE_PAGE_SIZE,
			  qp->shared_queue, qp->shared_queue_phys_addr);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_iwarp_modअगरy_fw(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_rdma_qp *qp)
अणु
	काष्ठा iwarp_modअगरy_qp_ramrod_data *p_ramrod;
	काष्ठा qed_sp_init_data init_data;
	काष्ठा qed_spq_entry *p_ent;
	u16 flags, trans_to_state;
	पूर्णांक rc;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 IWARP_RAMROD_CMD_ID_MODIFY_QP,
				 p_hwfn->p_rdma_info->proto, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.iwarp_modअगरy_qp;

	flags = le16_to_cpu(p_ramrod->flags);
	SET_FIELD(flags, IWARP_MODIFY_QP_RAMROD_DATA_STATE_TRANS_EN, 0x1);
	p_ramrod->flags = cpu_to_le16(flags);

	अगर (qp->iwarp_state == QED_IWARP_QP_STATE_CLOSING)
		trans_to_state = IWARP_MODIFY_QP_STATE_CLOSING;
	अन्यथा
		trans_to_state = IWARP_MODIFY_QP_STATE_ERROR;

	p_ramrod->transition_to_state = cpu_to_le16(trans_to_state);

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "QP(0x%x)rc=%d\n", qp->icid, rc);

	वापस rc;
पूर्ण

क्रमागत qed_iwarp_qp_state qed_roce2iwarp_state(क्रमागत qed_roce_qp_state state)
अणु
	चयन (state) अणु
	हाल QED_ROCE_QP_STATE_RESET:
	हाल QED_ROCE_QP_STATE_INIT:
	हाल QED_ROCE_QP_STATE_RTR:
		वापस QED_IWARP_QP_STATE_IDLE;
	हाल QED_ROCE_QP_STATE_RTS:
		वापस QED_IWARP_QP_STATE_RTS;
	हाल QED_ROCE_QP_STATE_SQD:
		वापस QED_IWARP_QP_STATE_CLOSING;
	हाल QED_ROCE_QP_STATE_ERR:
		वापस QED_IWARP_QP_STATE_ERROR;
	हाल QED_ROCE_QP_STATE_SQE:
		वापस QED_IWARP_QP_STATE_TERMINATE;
	शेष:
		वापस QED_IWARP_QP_STATE_ERROR;
	पूर्ण
पूर्ण

अटल क्रमागत qed_roce_qp_state
qed_iwarp2roce_state(क्रमागत qed_iwarp_qp_state state)
अणु
	चयन (state) अणु
	हाल QED_IWARP_QP_STATE_IDLE:
		वापस QED_ROCE_QP_STATE_INIT;
	हाल QED_IWARP_QP_STATE_RTS:
		वापस QED_ROCE_QP_STATE_RTS;
	हाल QED_IWARP_QP_STATE_TERMINATE:
		वापस QED_ROCE_QP_STATE_SQE;
	हाल QED_IWARP_QP_STATE_CLOSING:
		वापस QED_ROCE_QP_STATE_SQD;
	हाल QED_IWARP_QP_STATE_ERROR:
		वापस QED_ROCE_QP_STATE_ERR;
	शेष:
		वापस QED_ROCE_QP_STATE_ERR;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर * स्थिर iwarp_state_names[] = अणु
	"IDLE",
	"RTS",
	"TERMINATE",
	"CLOSING",
	"ERROR",
पूर्ण;

पूर्णांक
qed_iwarp_modअगरy_qp(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_rdma_qp *qp,
		    क्रमागत qed_iwarp_qp_state new_state, bool पूर्णांकernal)
अणु
	क्रमागत qed_iwarp_qp_state prev_iw_state;
	bool modअगरy_fw = false;
	पूर्णांक rc = 0;

	/* modअगरy QP can be called from upper-layer or as a result of async
	 * RST/FIN... thereक्रमe need to protect
	 */
	spin_lock_bh(&p_hwfn->p_rdma_info->iwarp.qp_lock);
	prev_iw_state = qp->iwarp_state;

	अगर (prev_iw_state == new_state) अणु
		spin_unlock_bh(&p_hwfn->p_rdma_info->iwarp.qp_lock);
		वापस 0;
	पूर्ण

	चयन (prev_iw_state) अणु
	हाल QED_IWARP_QP_STATE_IDLE:
		चयन (new_state) अणु
		हाल QED_IWARP_QP_STATE_RTS:
			qp->iwarp_state = QED_IWARP_QP_STATE_RTS;
			अवरोध;
		हाल QED_IWARP_QP_STATE_ERROR:
			qp->iwarp_state = QED_IWARP_QP_STATE_ERROR;
			अगर (!पूर्णांकernal)
				modअगरy_fw = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल QED_IWARP_QP_STATE_RTS:
		चयन (new_state) अणु
		हाल QED_IWARP_QP_STATE_CLOSING:
			अगर (!पूर्णांकernal)
				modअगरy_fw = true;

			qp->iwarp_state = QED_IWARP_QP_STATE_CLOSING;
			अवरोध;
		हाल QED_IWARP_QP_STATE_ERROR:
			अगर (!पूर्णांकernal)
				modअगरy_fw = true;
			qp->iwarp_state = QED_IWARP_QP_STATE_ERROR;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल QED_IWARP_QP_STATE_ERROR:
		चयन (new_state) अणु
		हाल QED_IWARP_QP_STATE_IDLE:

			qp->iwarp_state = new_state;
			अवरोध;
		हाल QED_IWARP_QP_STATE_CLOSING:
			/* could happen due to race... करो nothing.... */
			अवरोध;
		शेष:
			rc = -EINVAL;
		पूर्ण
		अवरोध;
	हाल QED_IWARP_QP_STATE_TERMINATE:
	हाल QED_IWARP_QP_STATE_CLOSING:
		qp->iwarp_state = new_state;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "QP(0x%x) %s --> %s%s\n",
		   qp->icid,
		   iwarp_state_names[prev_iw_state],
		   iwarp_state_names[qp->iwarp_state],
		   पूर्णांकernal ? "internal" : "");

	spin_unlock_bh(&p_hwfn->p_rdma_info->iwarp.qp_lock);

	अगर (modअगरy_fw)
		rc = qed_iwarp_modअगरy_fw(p_hwfn, qp);

	वापस rc;
पूर्ण

पूर्णांक qed_iwarp_fw_destroy(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_rdma_qp *qp)
अणु
	काष्ठा qed_sp_init_data init_data;
	काष्ठा qed_spq_entry *p_ent;
	पूर्णांक rc;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 IWARP_RAMROD_CMD_ID_DESTROY_QP,
				 p_hwfn->p_rdma_info->proto, &init_data);
	अगर (rc)
		वापस rc;

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "QP(0x%x) rc = %d\n", qp->icid, rc);

	वापस rc;
पूर्ण

अटल व्योम qed_iwarp_destroy_ep(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_iwarp_ep *ep,
				 bool हटाओ_from_active_list)
अणु
	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
			  माप(*ep->ep_buffer_virt),
			  ep->ep_buffer_virt, ep->ep_buffer_phys);

	अगर (हटाओ_from_active_list) अणु
		spin_lock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);
		list_del(&ep->list_entry);
		spin_unlock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);
	पूर्ण

	अगर (ep->qp)
		ep->qp->ep = शून्य;

	kमुक्त(ep);
पूर्ण

पूर्णांक qed_iwarp_destroy_qp(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_rdma_qp *qp)
अणु
	काष्ठा qed_iwarp_ep *ep = qp->ep;
	पूर्णांक रुको_count = 0;
	पूर्णांक rc = 0;

	अगर (qp->iwarp_state != QED_IWARP_QP_STATE_ERROR) अणु
		rc = qed_iwarp_modअगरy_qp(p_hwfn, qp,
					 QED_IWARP_QP_STATE_ERROR, false);
		अगर (rc)
			वापस rc;
	पूर्ण

	/* Make sure ep is बंदd beक्रमe वापसing and मुक्तing memory. */
	अगर (ep) अणु
		जबतक (READ_ONCE(ep->state) != QED_IWARP_EP_CLOSED &&
		       रुको_count++ < 200)
			msleep(100);

		अगर (ep->state != QED_IWARP_EP_CLOSED)
			DP_NOTICE(p_hwfn, "ep state close timeout state=%x\n",
				  ep->state);

		qed_iwarp_destroy_ep(p_hwfn, ep, false);
	पूर्ण

	rc = qed_iwarp_fw_destroy(p_hwfn, qp);

	अगर (qp->shared_queue)
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  IWARP_SHARED_QUEUE_PAGE_SIZE,
				  qp->shared_queue, qp->shared_queue_phys_addr);

	वापस rc;
पूर्ण

अटल पूर्णांक
qed_iwarp_create_ep(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_iwarp_ep **ep_out)
अणु
	काष्ठा qed_iwarp_ep *ep;
	पूर्णांक rc;

	ep = kzalloc(माप(*ep), GFP_KERNEL);
	अगर (!ep)
		वापस -ENOMEM;

	ep->state = QED_IWARP_EP_INIT;

	ep->ep_buffer_virt = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
						माप(*ep->ep_buffer_virt),
						&ep->ep_buffer_phys,
						GFP_KERNEL);
	अगर (!ep->ep_buffer_virt) अणु
		rc = -ENOMEM;
		जाओ err;
	पूर्ण

	ep->sig = QED_EP_SIG;

	*ep_out = ep;

	वापस 0;

err:
	kमुक्त(ep);
	वापस rc;
पूर्ण

अटल व्योम
qed_iwarp_prपूर्णांक_tcp_ramrod(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा iwarp_tcp_offload_ramrod_data *p_tcp_ramrod)
अणु
	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "local_mac=%x %x %x, remote_mac=%x %x %x\n",
		   p_tcp_ramrod->tcp.local_mac_addr_lo,
		   p_tcp_ramrod->tcp.local_mac_addr_mid,
		   p_tcp_ramrod->tcp.local_mac_addr_hi,
		   p_tcp_ramrod->tcp.remote_mac_addr_lo,
		   p_tcp_ramrod->tcp.remote_mac_addr_mid,
		   p_tcp_ramrod->tcp.remote_mac_addr_hi);

	अगर (p_tcp_ramrod->tcp.ip_version == TCP_IPV4) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "local_ip=%pI4h:%x, remote_ip=%pI4h:%x, vlan=%x\n",
			   p_tcp_ramrod->tcp.local_ip,
			   p_tcp_ramrod->tcp.local_port,
			   p_tcp_ramrod->tcp.remote_ip,
			   p_tcp_ramrod->tcp.remote_port,
			   p_tcp_ramrod->tcp.vlan_id);
	पूर्ण अन्यथा अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "local_ip=%pI6:%x, remote_ip=%pI6:%x, vlan=%x\n",
			   p_tcp_ramrod->tcp.local_ip,
			   p_tcp_ramrod->tcp.local_port,
			   p_tcp_ramrod->tcp.remote_ip,
			   p_tcp_ramrod->tcp.remote_port,
			   p_tcp_ramrod->tcp.vlan_id);
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
		   "flow_label=%x, ttl=%x, tos_or_tc=%x, mss=%x, rcv_wnd_scale=%x, connect_mode=%x, flags=%x\n",
		   p_tcp_ramrod->tcp.flow_label,
		   p_tcp_ramrod->tcp.ttl,
		   p_tcp_ramrod->tcp.tos_or_tc,
		   p_tcp_ramrod->tcp.mss,
		   p_tcp_ramrod->tcp.rcv_wnd_scale,
		   p_tcp_ramrod->tcp.connect_mode,
		   p_tcp_ramrod->tcp.flags);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "syn_ip_payload_length=%x, lo=%x, hi=%x\n",
		   p_tcp_ramrod->tcp.syn_ip_payload_length,
		   p_tcp_ramrod->tcp.syn_phy_addr_lo,
		   p_tcp_ramrod->tcp.syn_phy_addr_hi);
पूर्ण

अटल पूर्णांक
qed_iwarp_tcp_offload(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_iwarp_ep *ep)
अणु
	काष्ठा qed_iwarp_info *iwarp_info = &p_hwfn->p_rdma_info->iwarp;
	काष्ठा iwarp_tcp_offload_ramrod_data *p_tcp_ramrod;
	काष्ठा tcp_offload_params_opt2 *tcp;
	काष्ठा qed_sp_init_data init_data;
	काष्ठा qed_spq_entry *p_ent;
	dma_addr_t async_output_phys;
	dma_addr_t in_pdata_phys;
	u16 physical_q;
	u16 flags = 0;
	u8 tcp_flags;
	पूर्णांक rc;
	पूर्णांक i;

	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = ep->tcp_cid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	अगर (ep->connect_mode == TCP_CONNECT_PASSIVE)
		init_data.comp_mode = QED_SPQ_MODE_CB;
	अन्यथा
		init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 IWARP_RAMROD_CMD_ID_TCP_OFFLOAD,
				 PROTOCOLID_IWARP, &init_data);
	अगर (rc)
		वापस rc;

	p_tcp_ramrod = &p_ent->ramrod.iwarp_tcp_offload;

	in_pdata_phys = ep->ep_buffer_phys +
			दुरत्व(काष्ठा qed_iwarp_ep_memory, in_pdata);
	DMA_REGPAIR_LE(p_tcp_ramrod->iwarp.incoming_ulp_buffer.addr,
		       in_pdata_phys);

	p_tcp_ramrod->iwarp.incoming_ulp_buffer.len =
	    cpu_to_le16(माप(ep->ep_buffer_virt->in_pdata));

	async_output_phys = ep->ep_buffer_phys +
			    दुरत्व(काष्ठा qed_iwarp_ep_memory, async_output);
	DMA_REGPAIR_LE(p_tcp_ramrod->iwarp.async_eqe_output_buf,
		       async_output_phys);

	p_tcp_ramrod->iwarp.handle_क्रम_async.hi = cpu_to_le32(PTR_HI(ep));
	p_tcp_ramrod->iwarp.handle_क्रम_async.lo = cpu_to_le32(PTR_LO(ep));

	physical_q = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_OFLD);
	p_tcp_ramrod->iwarp.physical_q0 = cpu_to_le16(physical_q);
	physical_q = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_ACK);
	p_tcp_ramrod->iwarp.physical_q1 = cpu_to_le16(physical_q);
	p_tcp_ramrod->iwarp.mpa_mode = iwarp_info->mpa_rev;

	tcp = &p_tcp_ramrod->tcp;
	qed_set_fw_mac_addr(&tcp->remote_mac_addr_hi,
			    &tcp->remote_mac_addr_mid,
			    &tcp->remote_mac_addr_lo, ep->remote_mac_addr);
	qed_set_fw_mac_addr(&tcp->local_mac_addr_hi, &tcp->local_mac_addr_mid,
			    &tcp->local_mac_addr_lo, ep->local_mac_addr);

	tcp->vlan_id = cpu_to_le16(ep->cm_info.vlan);

	tcp_flags = p_hwfn->p_rdma_info->iwarp.tcp_flags;

	SET_FIELD(flags, TCP_OFFLOAD_PARAMS_OPT2_TS_EN,
		  !!(tcp_flags & QED_IWARP_TS_EN));

	SET_FIELD(flags, TCP_OFFLOAD_PARAMS_OPT2_DA_EN,
		  !!(tcp_flags & QED_IWARP_DA_EN));

	tcp->flags = cpu_to_le16(flags);
	tcp->ip_version = ep->cm_info.ip_version;

	क्रम (i = 0; i < 4; i++) अणु
		tcp->remote_ip[i] = cpu_to_le32(ep->cm_info.remote_ip[i]);
		tcp->local_ip[i] = cpu_to_le32(ep->cm_info.local_ip[i]);
	पूर्ण

	tcp->remote_port = cpu_to_le16(ep->cm_info.remote_port);
	tcp->local_port = cpu_to_le16(ep->cm_info.local_port);
	tcp->mss = cpu_to_le16(ep->mss);
	tcp->flow_label = 0;
	tcp->ttl = 0x40;
	tcp->tos_or_tc = 0;

	tcp->max_rt_समय = QED_IWARP_DEF_MAX_RT_TIME;
	tcp->cwnd = cpu_to_le32(QED_IWARP_DEF_CWND_FACTOR * ep->mss);
	tcp->ka_max_probe_cnt = QED_IWARP_DEF_KA_MAX_PROBE_CNT;
	tcp->ka_समयout = cpu_to_le32(QED_IWARP_DEF_KA_TIMEOUT);
	tcp->ka_पूर्णांकerval = cpu_to_le32(QED_IWARP_DEF_KA_INTERVAL);

	tcp->rcv_wnd_scale = (u8)p_hwfn->p_rdma_info->iwarp.rcv_wnd_scale;
	tcp->connect_mode = ep->connect_mode;

	अगर (ep->connect_mode == TCP_CONNECT_PASSIVE) अणु
		tcp->syn_ip_payload_length =
			cpu_to_le16(ep->syn_ip_payload_length);
		tcp->syn_phy_addr_hi = DMA_HI_LE(ep->syn_phy_addr);
		tcp->syn_phy_addr_lo = DMA_LO_LE(ep->syn_phy_addr);
	पूर्ण

	qed_iwarp_prपूर्णांक_tcp_ramrod(p_hwfn, p_tcp_ramrod);

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
		   "EP(0x%x) Offload completed rc=%d\n", ep->tcp_cid, rc);

	वापस rc;
पूर्ण

अटल व्योम
qed_iwarp_mpa_received(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_iwarp_ep *ep)
अणु
	काष्ठा qed_iwarp_info *iwarp_info = &p_hwfn->p_rdma_info->iwarp;
	काष्ठा qed_iwarp_cm_event_params params;
	काष्ठा mpa_v2_hdr *mpa_v2;
	जोड़ async_output *async_data;
	u16 mpa_ord, mpa_ird;
	u8 mpa_hdr_size = 0;
	u16 ulp_data_len;
	u8 mpa_rev;

	async_data = &ep->ep_buffer_virt->async_output;

	mpa_rev = async_data->mpa_request.mpa_handshake_mode;
	DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
		   "private_data_len=%x handshake_mode=%x private_data=(%x)\n",
		   async_data->mpa_request.ulp_data_len,
		   mpa_rev, *((u32 *)(ep->ep_buffer_virt->in_pdata)));

	अगर (mpa_rev == MPA_NEGOTIATION_TYPE_ENHANCED) अणु
		/* Read ord/ird values from निजी data buffer */
		mpa_v2 = (काष्ठा mpa_v2_hdr *)ep->ep_buffer_virt->in_pdata;
		mpa_hdr_size = माप(*mpa_v2);

		mpa_ord = ntohs(mpa_v2->ord);
		mpa_ird = ntohs(mpa_v2->ird);

		/* Temprary store in cm_info incoming ord/ird requested, later
		 * replace with negotiated value during accept
		 */
		ep->cm_info.ord = (u8)min_t(u16,
					    (mpa_ord & MPA_V2_IRD_ORD_MASK),
					    QED_IWARP_ORD_DEFAULT);

		ep->cm_info.ird = (u8)min_t(u16,
					    (mpa_ird & MPA_V2_IRD_ORD_MASK),
					    QED_IWARP_IRD_DEFAULT);

		/* Peer2Peer negotiation */
		ep->rtr_type = MPA_RTR_TYPE_NONE;
		अगर (mpa_ird & MPA_V2_PEER2PEER_MODEL) अणु
			अगर (mpa_ord & MPA_V2_WRITE_RTR)
				ep->rtr_type |= MPA_RTR_TYPE_ZERO_WRITE;

			अगर (mpa_ord & MPA_V2_READ_RTR)
				ep->rtr_type |= MPA_RTR_TYPE_ZERO_READ;

			अगर (mpa_ird & MPA_V2_SEND_RTR)
				ep->rtr_type |= MPA_RTR_TYPE_ZERO_SEND;

			ep->rtr_type &= iwarp_info->rtr_type;

			/* अगर we're left with no match send our capabilities */
			अगर (ep->rtr_type == MPA_RTR_TYPE_NONE)
				ep->rtr_type = iwarp_info->rtr_type;
		पूर्ण

		ep->mpa_rev = MPA_NEGOTIATION_TYPE_ENHANCED;
	पूर्ण अन्यथा अणु
		ep->cm_info.ord = QED_IWARP_ORD_DEFAULT;
		ep->cm_info.ird = QED_IWARP_IRD_DEFAULT;
		ep->mpa_rev = MPA_NEGOTIATION_TYPE_BASIC;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
		   "MPA_NEGOTIATE (v%d): ORD: 0x%x IRD: 0x%x rtr:0x%x ulp_data_len = %x mpa_hdr_size = %x\n",
		   mpa_rev, ep->cm_info.ord, ep->cm_info.ird, ep->rtr_type,
		   async_data->mpa_request.ulp_data_len, mpa_hdr_size);

	/* Strip mpa v2 hdr from निजी data beक्रमe sending to upper layer */
	ep->cm_info.निजी_data = ep->ep_buffer_virt->in_pdata + mpa_hdr_size;

	ulp_data_len = le16_to_cpu(async_data->mpa_request.ulp_data_len);
	ep->cm_info.निजी_data_len = ulp_data_len - mpa_hdr_size;

	params.event = QED_IWARP_EVENT_MPA_REQUEST;
	params.cm_info = &ep->cm_info;
	params.ep_context = ep;
	params.status = 0;

	ep->state = QED_IWARP_EP_MPA_REQ_RCVD;
	ep->event_cb(ep->cb_context, &params);
पूर्ण

अटल पूर्णांक
qed_iwarp_mpa_offload(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_iwarp_ep *ep)
अणु
	काष्ठा iwarp_mpa_offload_ramrod_data *p_mpa_ramrod;
	काष्ठा mpa_outgoing_params *common;
	काष्ठा qed_iwarp_info *iwarp_info;
	काष्ठा qed_sp_init_data init_data;
	dma_addr_t async_output_phys;
	काष्ठा qed_spq_entry *p_ent;
	dma_addr_t out_pdata_phys;
	dma_addr_t in_pdata_phys;
	काष्ठा qed_rdma_qp *qp;
	bool reject;
	u32 val;
	पूर्णांक rc;

	अगर (!ep)
		वापस -EINVAL;

	qp = ep->qp;
	reject = !qp;

	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = reject ? ep->tcp_cid : qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;

	अगर (ep->connect_mode == TCP_CONNECT_ACTIVE)
		init_data.comp_mode = QED_SPQ_MODE_CB;
	अन्यथा
		init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 IWARP_RAMROD_CMD_ID_MPA_OFFLOAD,
				 PROTOCOLID_IWARP, &init_data);
	अगर (rc)
		वापस rc;

	p_mpa_ramrod = &p_ent->ramrod.iwarp_mpa_offload;
	common = &p_mpa_ramrod->common;

	out_pdata_phys = ep->ep_buffer_phys +
			 दुरत्व(काष्ठा qed_iwarp_ep_memory, out_pdata);
	DMA_REGPAIR_LE(common->outgoing_ulp_buffer.addr, out_pdata_phys);

	val = ep->cm_info.निजी_data_len;
	common->outgoing_ulp_buffer.len = cpu_to_le16(val);
	common->crc_needed = p_hwfn->p_rdma_info->iwarp.crc_needed;

	common->out_rq.ord = cpu_to_le32(ep->cm_info.ord);
	common->out_rq.ird = cpu_to_le32(ep->cm_info.ird);

	val = p_hwfn->hw_info.opaque_fid << 16 | ep->tcp_cid;
	p_mpa_ramrod->tcp_cid = cpu_to_le32(val);

	in_pdata_phys = ep->ep_buffer_phys +
			दुरत्व(काष्ठा qed_iwarp_ep_memory, in_pdata);
	p_mpa_ramrod->tcp_connect_side = ep->connect_mode;
	DMA_REGPAIR_LE(p_mpa_ramrod->incoming_ulp_buffer.addr,
		       in_pdata_phys);
	p_mpa_ramrod->incoming_ulp_buffer.len =
	    cpu_to_le16(माप(ep->ep_buffer_virt->in_pdata));
	async_output_phys = ep->ep_buffer_phys +
			    दुरत्व(काष्ठा qed_iwarp_ep_memory, async_output);
	DMA_REGPAIR_LE(p_mpa_ramrod->async_eqe_output_buf,
		       async_output_phys);
	p_mpa_ramrod->handle_क्रम_async.hi = cpu_to_le32(PTR_HI(ep));
	p_mpa_ramrod->handle_क्रम_async.lo = cpu_to_le32(PTR_LO(ep));

	अगर (!reject) अणु
		DMA_REGPAIR_LE(p_mpa_ramrod->shared_queue_addr,
			       qp->shared_queue_phys_addr);
		p_mpa_ramrod->stats_counter_id =
		    RESC_START(p_hwfn, QED_RDMA_STATS_QUEUE) + qp->stats_queue;
	पूर्ण अन्यथा अणु
		common->reject = 1;
	पूर्ण

	iwarp_info = &p_hwfn->p_rdma_info->iwarp;
	p_mpa_ramrod->rcv_wnd = cpu_to_le16(iwarp_info->rcv_wnd_size);
	p_mpa_ramrod->mode = ep->mpa_rev;
	SET_FIELD(p_mpa_ramrod->rtr_pref,
		  IWARP_MPA_OFFLOAD_RAMROD_DATA_RTR_SUPPORTED, ep->rtr_type);

	ep->state = QED_IWARP_EP_MPA_OFFLOADED;
	rc = qed_spq_post(p_hwfn, p_ent, शून्य);
	अगर (!reject)
		ep->cid = qp->icid;	/* Now they're migrated. */

	DP_VERBOSE(p_hwfn,
		   QED_MSG_RDMA,
		   "QP(0x%x) EP(0x%x) MPA Offload rc = %d IRD=0x%x ORD=0x%x rtr_type=%d mpa_rev=%d reject=%d\n",
		   reject ? 0xffff : qp->icid,
		   ep->tcp_cid,
		   rc,
		   ep->cm_info.ird,
		   ep->cm_info.ord, ep->rtr_type, ep->mpa_rev, reject);
	वापस rc;
पूर्ण

अटल व्योम
qed_iwarp_वापस_ep(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_iwarp_ep *ep)
अणु
	ep->state = QED_IWARP_EP_INIT;
	अगर (ep->qp)
		ep->qp->ep = शून्य;
	ep->qp = शून्य;
	स_रखो(&ep->cm_info, 0, माप(ep->cm_info));

	अगर (ep->tcp_cid == QED_IWARP_INVALID_TCP_CID) अणु
		/* We करोn't care about the return code, it's ok अगर tcp_cid
		 * reमुख्यs invalid...in this हाल we'll defer allocation
		 */
		qed_iwarp_alloc_tcp_cid(p_hwfn, &ep->tcp_cid);
	पूर्ण
	spin_lock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);

	list_move_tail(&ep->list_entry,
		       &p_hwfn->p_rdma_info->iwarp.ep_मुक्त_list);

	spin_unlock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);
पूर्ण

अटल व्योम
qed_iwarp_parse_निजी_data(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_iwarp_ep *ep)
अणु
	काष्ठा mpa_v2_hdr *mpa_v2_params;
	जोड़ async_output *async_data;
	u16 mpa_ird, mpa_ord;
	u8 mpa_data_size = 0;
	u16 ulp_data_len;

	अगर (MPA_REV2(p_hwfn->p_rdma_info->iwarp.mpa_rev)) अणु
		mpa_v2_params =
			(काष्ठा mpa_v2_hdr *)(ep->ep_buffer_virt->in_pdata);
		mpa_data_size = माप(*mpa_v2_params);
		mpa_ird = ntohs(mpa_v2_params->ird);
		mpa_ord = ntohs(mpa_v2_params->ord);

		ep->cm_info.ird = (u8)(mpa_ord & MPA_V2_IRD_ORD_MASK);
		ep->cm_info.ord = (u8)(mpa_ird & MPA_V2_IRD_ORD_MASK);
	पूर्ण

	async_data = &ep->ep_buffer_virt->async_output;
	ep->cm_info.निजी_data = ep->ep_buffer_virt->in_pdata + mpa_data_size;

	ulp_data_len = le16_to_cpu(async_data->mpa_response.ulp_data_len);
	ep->cm_info.निजी_data_len = ulp_data_len - mpa_data_size;
पूर्ण

अटल व्योम
qed_iwarp_mpa_reply_arrived(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_iwarp_ep *ep)
अणु
	काष्ठा qed_iwarp_cm_event_params params;

	अगर (ep->connect_mode == TCP_CONNECT_PASSIVE) अणु
		DP_NOTICE(p_hwfn,
			  "MPA reply event not expected on passive side!\n");
		वापस;
	पूर्ण

	params.event = QED_IWARP_EVENT_ACTIVE_MPA_REPLY;

	qed_iwarp_parse_निजी_data(p_hwfn, ep);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
		   "MPA_NEGOTIATE (v%d): ORD: 0x%x IRD: 0x%x\n",
		   ep->mpa_rev, ep->cm_info.ord, ep->cm_info.ird);

	params.cm_info = &ep->cm_info;
	params.ep_context = ep;
	params.status = 0;

	ep->mpa_reply_processed = true;

	ep->event_cb(ep->cb_context, &params);
पूर्ण

#घोषणा QED_IWARP_CONNECT_MODE_STRING(ep) \
	((ep)->connect_mode == TCP_CONNECT_PASSIVE) ? "Passive" : "Active"

/* Called as a result of the event:
 * IWARP_EVENT_TYPE_ASYNC_MPA_HANDSHAKE_COMPLETE
 */
अटल व्योम
qed_iwarp_mpa_complete(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_iwarp_ep *ep, u8 fw_वापस_code)
अणु
	काष्ठा qed_iwarp_cm_event_params params;

	अगर (ep->connect_mode == TCP_CONNECT_ACTIVE)
		params.event = QED_IWARP_EVENT_ACTIVE_COMPLETE;
	अन्यथा
		params.event = QED_IWARP_EVENT_PASSIVE_COMPLETE;

	अगर (ep->connect_mode == TCP_CONNECT_ACTIVE && !ep->mpa_reply_processed)
		qed_iwarp_parse_निजी_data(p_hwfn, ep);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
		   "MPA_NEGOTIATE (v%d): ORD: 0x%x IRD: 0x%x\n",
		   ep->mpa_rev, ep->cm_info.ord, ep->cm_info.ird);

	params.cm_info = &ep->cm_info;

	params.ep_context = ep;

	चयन (fw_वापस_code) अणु
	हाल RDMA_RETURN_OK:
		ep->qp->max_rd_atomic_req = ep->cm_info.ord;
		ep->qp->max_rd_atomic_resp = ep->cm_info.ird;
		qed_iwarp_modअगरy_qp(p_hwfn, ep->qp, QED_IWARP_QP_STATE_RTS, 1);
		ep->state = QED_IWARP_EP_ESTABLISHED;
		params.status = 0;
		अवरोध;
	हाल IWARP_CONN_ERROR_MPA_TIMEOUT:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA timeout\n",
			  QED_IWARP_CONNECT_MODE_STRING(ep), ep->cid);
		params.status = -EBUSY;
		अवरोध;
	हाल IWARP_CONN_ERROR_MPA_ERROR_REJECT:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA Reject\n",
			  QED_IWARP_CONNECT_MODE_STRING(ep), ep->cid);
		params.status = -ECONNREFUSED;
		अवरोध;
	हाल IWARP_CONN_ERROR_MPA_RST:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA reset(tcp cid: 0x%x)\n",
			  QED_IWARP_CONNECT_MODE_STRING(ep), ep->cid,
			  ep->tcp_cid);
		params.status = -ECONNRESET;
		अवरोध;
	हाल IWARP_CONN_ERROR_MPA_FIN:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA received FIN\n",
			  QED_IWARP_CONNECT_MODE_STRING(ep), ep->cid);
		params.status = -ECONNREFUSED;
		अवरोध;
	हाल IWARP_CONN_ERROR_MPA_INSUF_IRD:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA insufficient ird\n",
			  QED_IWARP_CONNECT_MODE_STRING(ep), ep->cid);
		params.status = -ECONNREFUSED;
		अवरोध;
	हाल IWARP_CONN_ERROR_MPA_RTR_MISMATCH:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA RTR MISMATCH\n",
			  QED_IWARP_CONNECT_MODE_STRING(ep), ep->cid);
		params.status = -ECONNREFUSED;
		अवरोध;
	हाल IWARP_CONN_ERROR_MPA_INVALID_PACKET:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA Invalid Packet\n",
			  QED_IWARP_CONNECT_MODE_STRING(ep), ep->cid);
		params.status = -ECONNREFUSED;
		अवरोध;
	हाल IWARP_CONN_ERROR_MPA_LOCAL_ERROR:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA Local Error\n",
			  QED_IWARP_CONNECT_MODE_STRING(ep), ep->cid);
		params.status = -ECONNREFUSED;
		अवरोध;
	हाल IWARP_CONN_ERROR_MPA_TERMINATE:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA TERMINATE\n",
			  QED_IWARP_CONNECT_MODE_STRING(ep), ep->cid);
		params.status = -ECONNREFUSED;
		अवरोध;
	शेष:
		params.status = -ECONNRESET;
		अवरोध;
	पूर्ण

	अगर (fw_वापस_code != RDMA_RETURN_OK)
		/* paired with READ_ONCE in destroy_qp */
		smp_store_release(&ep->state, QED_IWARP_EP_CLOSED);

	ep->event_cb(ep->cb_context, &params);

	/* on passive side, अगर there is no associated QP (REJECT) we need to
	 * वापस the ep to the pool, (in the regular हाल we add an element
	 * in accept instead of this one.
	 * In both हालs we need to हटाओ it from the ep_list.
	 */
	अगर (fw_वापस_code != RDMA_RETURN_OK) अणु
		ep->tcp_cid = QED_IWARP_INVALID_TCP_CID;
		अगर ((ep->connect_mode == TCP_CONNECT_PASSIVE) &&
		    (!ep->qp)) अणु	/* Rejected */
			qed_iwarp_वापस_ep(p_hwfn, ep);
		पूर्ण अन्यथा अणु
			spin_lock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);
			list_del(&ep->list_entry);
			spin_unlock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
qed_iwarp_mpa_v2_set_निजी(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_iwarp_ep *ep, u8 *mpa_data_size)
अणु
	काष्ठा mpa_v2_hdr *mpa_v2_params;
	u16 mpa_ird, mpa_ord;

	*mpa_data_size = 0;
	अगर (MPA_REV2(ep->mpa_rev)) अणु
		mpa_v2_params =
		    (काष्ठा mpa_v2_hdr *)ep->ep_buffer_virt->out_pdata;
		*mpa_data_size = माप(*mpa_v2_params);

		mpa_ird = (u16)ep->cm_info.ird;
		mpa_ord = (u16)ep->cm_info.ord;

		अगर (ep->rtr_type != MPA_RTR_TYPE_NONE) अणु
			mpa_ird |= MPA_V2_PEER2PEER_MODEL;

			अगर (ep->rtr_type & MPA_RTR_TYPE_ZERO_SEND)
				mpa_ird |= MPA_V2_SEND_RTR;

			अगर (ep->rtr_type & MPA_RTR_TYPE_ZERO_WRITE)
				mpa_ord |= MPA_V2_WRITE_RTR;

			अगर (ep->rtr_type & MPA_RTR_TYPE_ZERO_READ)
				mpa_ord |= MPA_V2_READ_RTR;
		पूर्ण

		mpa_v2_params->ird = htons(mpa_ird);
		mpa_v2_params->ord = htons(mpa_ord);

		DP_VERBOSE(p_hwfn,
			   QED_MSG_RDMA,
			   "MPA_NEGOTIATE Header: [%x ord:%x ird] %x ord:%x ird:%x peer2peer:%x rtr_send:%x rtr_write:%x rtr_read:%x\n",
			   mpa_v2_params->ird,
			   mpa_v2_params->ord,
			   *((u32 *)mpa_v2_params),
			   mpa_ord & MPA_V2_IRD_ORD_MASK,
			   mpa_ird & MPA_V2_IRD_ORD_MASK,
			   !!(mpa_ird & MPA_V2_PEER2PEER_MODEL),
			   !!(mpa_ird & MPA_V2_SEND_RTR),
			   !!(mpa_ord & MPA_V2_WRITE_RTR),
			   !!(mpa_ord & MPA_V2_READ_RTR));
	पूर्ण
पूर्ण

पूर्णांक qed_iwarp_connect(व्योम *rdma_cxt,
		      काष्ठा qed_iwarp_connect_in *iparams,
		      काष्ठा qed_iwarp_connect_out *oparams)
अणु
	काष्ठा qed_hwfn *p_hwfn = rdma_cxt;
	काष्ठा qed_iwarp_info *iwarp_info;
	काष्ठा qed_iwarp_ep *ep;
	u8 mpa_data_size = 0;
	u32 cid;
	पूर्णांक rc;

	अगर ((iparams->cm_info.ord > QED_IWARP_ORD_DEFAULT) ||
	    (iparams->cm_info.ird > QED_IWARP_IRD_DEFAULT)) अणु
		DP_NOTICE(p_hwfn,
			  "QP(0x%x) ERROR: Invalid ord(0x%x)/ird(0x%x)\n",
			  iparams->qp->icid, iparams->cm_info.ord,
			  iparams->cm_info.ird);

		वापस -EINVAL;
	पूर्ण

	iwarp_info = &p_hwfn->p_rdma_info->iwarp;

	/* Allocate ep object */
	rc = qed_iwarp_alloc_cid(p_hwfn, &cid);
	अगर (rc)
		वापस rc;

	rc = qed_iwarp_create_ep(p_hwfn, &ep);
	अगर (rc)
		जाओ err;

	ep->tcp_cid = cid;

	spin_lock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);
	list_add_tail(&ep->list_entry, &p_hwfn->p_rdma_info->iwarp.ep_list);
	spin_unlock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);

	ep->qp = iparams->qp;
	ep->qp->ep = ep;
	ether_addr_copy(ep->remote_mac_addr, iparams->remote_mac_addr);
	ether_addr_copy(ep->local_mac_addr, iparams->local_mac_addr);
	स_नकल(&ep->cm_info, &iparams->cm_info, माप(ep->cm_info));

	ep->cm_info.ord = iparams->cm_info.ord;
	ep->cm_info.ird = iparams->cm_info.ird;

	ep->rtr_type = iwarp_info->rtr_type;
	अगर (!iwarp_info->peer2peer)
		ep->rtr_type = MPA_RTR_TYPE_NONE;

	अगर ((ep->rtr_type & MPA_RTR_TYPE_ZERO_READ) && (ep->cm_info.ord == 0))
		ep->cm_info.ord = 1;

	ep->mpa_rev = iwarp_info->mpa_rev;

	qed_iwarp_mpa_v2_set_निजी(p_hwfn, ep, &mpa_data_size);

	ep->cm_info.निजी_data = ep->ep_buffer_virt->out_pdata;
	ep->cm_info.निजी_data_len = iparams->cm_info.निजी_data_len +
				       mpa_data_size;

	स_नकल((u8 *)ep->ep_buffer_virt->out_pdata + mpa_data_size,
	       iparams->cm_info.निजी_data,
	       iparams->cm_info.निजी_data_len);

	ep->mss = iparams->mss;
	ep->mss = min_t(u16, QED_IWARP_MAX_FW_MSS, ep->mss);

	ep->event_cb = iparams->event_cb;
	ep->cb_context = iparams->cb_context;
	ep->connect_mode = TCP_CONNECT_ACTIVE;

	oparams->ep_context = ep;

	rc = qed_iwarp_tcp_offload(p_hwfn, ep);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "QP(0x%x) EP(0x%x) rc = %d\n",
		   iparams->qp->icid, ep->tcp_cid, rc);

	अगर (rc) अणु
		qed_iwarp_destroy_ep(p_hwfn, ep, true);
		जाओ err;
	पूर्ण

	वापस rc;
err:
	qed_iwarp_cid_cleaned(p_hwfn, cid);

	वापस rc;
पूर्ण

अटल काष्ठा qed_iwarp_ep *qed_iwarp_get_मुक्त_ep(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_iwarp_ep *ep = शून्य;
	पूर्णांक rc;

	spin_lock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);

	अगर (list_empty(&p_hwfn->p_rdma_info->iwarp.ep_मुक्त_list)) अणु
		DP_ERR(p_hwfn, "Ep list is empty\n");
		जाओ out;
	पूर्ण

	ep = list_first_entry(&p_hwfn->p_rdma_info->iwarp.ep_मुक्त_list,
			      काष्ठा qed_iwarp_ep, list_entry);

	/* in some हालs we could have failed allocating a tcp cid when added
	 * from accept / failure... retry now..this is not the common हाल.
	 */
	अगर (ep->tcp_cid == QED_IWARP_INVALID_TCP_CID) अणु
		rc = qed_iwarp_alloc_tcp_cid(p_hwfn, &ep->tcp_cid);

		/* अगर we fail we could look क्रम another entry with a valid
		 * tcp_cid, but since we करोn't expect to reach this anyway
		 * it's not worth the handling
		 */
		अगर (rc) अणु
			ep->tcp_cid = QED_IWARP_INVALID_TCP_CID;
			ep = शून्य;
			जाओ out;
		पूर्ण
	पूर्ण

	list_del(&ep->list_entry);

out:
	spin_unlock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);
	वापस ep;
पूर्ण

#घोषणा QED_IWARP_MAX_CID_CLEAN_TIME  100
#घोषणा QED_IWARP_MAX_NO_PROGRESS_CNT 5

/* This function रुकोs क्रम all the bits of a bmap to be cleared, as दीर्घ as
 * there is progress ( i.e. the number of bits left to be cleared decreases )
 * the function जारीs.
 */
अटल पूर्णांक
qed_iwarp_रुको_cid_map_cleared(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_bmap *bmap)
अणु
	पूर्णांक prev_weight = 0;
	पूर्णांक रुको_count = 0;
	पूर्णांक weight = 0;

	weight = biपंचांगap_weight(bmap->biपंचांगap, bmap->max_count);
	prev_weight = weight;

	जबतक (weight) अणु
		msleep(QED_IWARP_MAX_CID_CLEAN_TIME);

		weight = biपंचांगap_weight(bmap->biपंचांगap, bmap->max_count);

		अगर (prev_weight == weight) अणु
			रुको_count++;
		पूर्ण अन्यथा अणु
			prev_weight = weight;
			रुको_count = 0;
		पूर्ण

		अगर (रुको_count > QED_IWARP_MAX_NO_PROGRESS_CNT) अणु
			DP_NOTICE(p_hwfn,
				  "%s bitmap wait timed out (%d cids pending)\n",
				  bmap->name, weight);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qed_iwarp_रुको_क्रम_all_cids(काष्ठा qed_hwfn *p_hwfn)
अणु
	पूर्णांक rc;
	पूर्णांक i;

	rc = qed_iwarp_रुको_cid_map_cleared(p_hwfn,
					    &p_hwfn->p_rdma_info->tcp_cid_map);
	अगर (rc)
		वापस rc;

	/* Now मुक्त the tcp cids from the मुख्य cid map */
	क्रम (i = 0; i < QED_IWARP_PREALLOC_CNT; i++)
		qed_bmap_release_id(p_hwfn, &p_hwfn->p_rdma_info->cid_map, i);

	/* Now रुको क्रम all cids to be completed */
	वापस qed_iwarp_रुको_cid_map_cleared(p_hwfn,
					      &p_hwfn->p_rdma_info->cid_map);
पूर्ण

अटल व्योम qed_iwarp_मुक्त_pपुनः_स्मृति_ep(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_iwarp_ep *ep;

	जबतक (!list_empty(&p_hwfn->p_rdma_info->iwarp.ep_मुक्त_list)) अणु
		spin_lock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);

		ep = list_first_entry(&p_hwfn->p_rdma_info->iwarp.ep_मुक्त_list,
				      काष्ठा qed_iwarp_ep, list_entry);

		अगर (!ep) अणु
			spin_unlock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);
			अवरोध;
		पूर्ण
		list_del(&ep->list_entry);

		spin_unlock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);

		अगर (ep->tcp_cid != QED_IWARP_INVALID_TCP_CID)
			qed_iwarp_cid_cleaned(p_hwfn, ep->tcp_cid);

		qed_iwarp_destroy_ep(p_hwfn, ep, false);
	पूर्ण
पूर्ण

अटल पूर्णांक qed_iwarp_pपुनः_स्मृति_ep(काष्ठा qed_hwfn *p_hwfn, bool init)
अणु
	काष्ठा qed_iwarp_ep *ep;
	पूर्णांक rc = 0;
	पूर्णांक count;
	u32 cid;
	पूर्णांक i;

	count = init ? QED_IWARP_PREALLOC_CNT : 1;
	क्रम (i = 0; i < count; i++) अणु
		rc = qed_iwarp_create_ep(p_hwfn, &ep);
		अगर (rc)
			वापस rc;

		/* During initialization we allocate from the मुख्य pool,
		 * afterwards we allocate only from the tcp_cid.
		 */
		अगर (init) अणु
			rc = qed_iwarp_alloc_cid(p_hwfn, &cid);
			अगर (rc)
				जाओ err;
			qed_iwarp_set_tcp_cid(p_hwfn, cid);
		पूर्ण अन्यथा अणु
			/* We करोn't care about the return code, it's ok अगर
			 * tcp_cid reमुख्यs invalid...in this हाल we'll
			 * defer allocation
			 */
			qed_iwarp_alloc_tcp_cid(p_hwfn, &cid);
		पूर्ण

		ep->tcp_cid = cid;

		spin_lock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);
		list_add_tail(&ep->list_entry,
			      &p_hwfn->p_rdma_info->iwarp.ep_मुक्त_list);
		spin_unlock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);
	पूर्ण

	वापस rc;

err:
	qed_iwarp_destroy_ep(p_hwfn, ep, false);

	वापस rc;
पूर्ण

पूर्णांक qed_iwarp_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	पूर्णांक rc;

	/* Allocate biपंचांगap क्रम tcp cid. These are used by passive side
	 * to ensure it can allocate a tcp cid during dpc that was
	 * pre-acquired and करोesn't require dynamic allocation of ilt
	 */
	rc = qed_rdma_bmap_alloc(p_hwfn, &p_hwfn->p_rdma_info->tcp_cid_map,
				 QED_IWARP_PREALLOC_CNT, "TCP_CID");
	अगर (rc) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "Failed to allocate tcp cid, rc = %d\n", rc);
		वापस rc;
	पूर्ण

	INIT_LIST_HEAD(&p_hwfn->p_rdma_info->iwarp.ep_मुक्त_list);
	spin_lock_init(&p_hwfn->p_rdma_info->iwarp.iw_lock);

	rc = qed_iwarp_pपुनः_स्मृति_ep(p_hwfn, true);
	अगर (rc)
		वापस rc;

	वापस qed_ooo_alloc(p_hwfn);
पूर्ण

व्योम qed_iwarp_resc_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_iwarp_info *iwarp_info = &p_hwfn->p_rdma_info->iwarp;

	qed_ooo_मुक्त(p_hwfn);
	qed_rdma_bmap_मुक्त(p_hwfn, &p_hwfn->p_rdma_info->tcp_cid_map, 1);
	kमुक्त(iwarp_info->mpa_bufs);
	kमुक्त(iwarp_info->partial_fpdus);
	kमुक्त(iwarp_info->mpa_पूर्णांकermediate_buf);
पूर्ण

पूर्णांक qed_iwarp_accept(व्योम *rdma_cxt, काष्ठा qed_iwarp_accept_in *iparams)
अणु
	काष्ठा qed_hwfn *p_hwfn = rdma_cxt;
	काष्ठा qed_iwarp_ep *ep;
	u8 mpa_data_size = 0;
	पूर्णांक rc;

	ep = iparams->ep_context;
	अगर (!ep) अणु
		DP_ERR(p_hwfn, "Ep Context receive in accept is NULL\n");
		वापस -EINVAL;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "QP(0x%x) EP(0x%x)\n",
		   iparams->qp->icid, ep->tcp_cid);

	अगर ((iparams->ord > QED_IWARP_ORD_DEFAULT) ||
	    (iparams->ird > QED_IWARP_IRD_DEFAULT)) अणु
		DP_VERBOSE(p_hwfn,
			   QED_MSG_RDMA,
			   "QP(0x%x) EP(0x%x) ERROR: Invalid ord(0x%x)/ird(0x%x)\n",
			   iparams->qp->icid,
			   ep->tcp_cid, iparams->ord, iparams->ord);
		वापस -EINVAL;
	पूर्ण

	qed_iwarp_pपुनः_स्मृति_ep(p_hwfn, false);

	ep->cb_context = iparams->cb_context;
	ep->qp = iparams->qp;
	ep->qp->ep = ep;

	अगर (ep->mpa_rev == MPA_NEGOTIATION_TYPE_ENHANCED) अणु
		/* Negotiate ord/ird: अगर upperlayer requested ord larger than
		 * ird advertised by remote, we need to decrease our ord
		 */
		अगर (iparams->ord > ep->cm_info.ird)
			iparams->ord = ep->cm_info.ird;

		अगर ((ep->rtr_type & MPA_RTR_TYPE_ZERO_READ) &&
		    (iparams->ird == 0))
			iparams->ird = 1;
	पूर्ण

	/* Update cm_info ord/ird to be negotiated values */
	ep->cm_info.ord = iparams->ord;
	ep->cm_info.ird = iparams->ird;

	qed_iwarp_mpa_v2_set_निजी(p_hwfn, ep, &mpa_data_size);

	ep->cm_info.निजी_data = ep->ep_buffer_virt->out_pdata;
	ep->cm_info.निजी_data_len = iparams->निजी_data_len +
				       mpa_data_size;

	स_नकल((u8 *)ep->ep_buffer_virt->out_pdata + mpa_data_size,
	       iparams->निजी_data, iparams->निजी_data_len);

	rc = qed_iwarp_mpa_offload(p_hwfn, ep);
	अगर (rc)
		qed_iwarp_modअगरy_qp(p_hwfn,
				    iparams->qp, QED_IWARP_QP_STATE_ERROR, 1);

	वापस rc;
पूर्ण

पूर्णांक qed_iwarp_reject(व्योम *rdma_cxt, काष्ठा qed_iwarp_reject_in *iparams)
अणु
	काष्ठा qed_hwfn *p_hwfn = rdma_cxt;
	काष्ठा qed_iwarp_ep *ep;
	u8 mpa_data_size = 0;

	ep = iparams->ep_context;
	अगर (!ep) अणु
		DP_ERR(p_hwfn, "Ep Context receive in reject is NULL\n");
		वापस -EINVAL;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "EP(0x%x)\n", ep->tcp_cid);

	ep->cb_context = iparams->cb_context;
	ep->qp = शून्य;

	qed_iwarp_mpa_v2_set_निजी(p_hwfn, ep, &mpa_data_size);

	ep->cm_info.निजी_data = ep->ep_buffer_virt->out_pdata;
	ep->cm_info.निजी_data_len = iparams->निजी_data_len +
				       mpa_data_size;

	स_नकल((u8 *)ep->ep_buffer_virt->out_pdata + mpa_data_size,
	       iparams->निजी_data, iparams->निजी_data_len);

	वापस qed_iwarp_mpa_offload(p_hwfn, ep);
पूर्ण

अटल व्योम
qed_iwarp_prपूर्णांक_cm_info(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_iwarp_cm_info *cm_info)
अणु
	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "ip_version = %d\n",
		   cm_info->ip_version);

	अगर (cm_info->ip_version == QED_TCP_IPV4)
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "remote_ip %pI4h:%x, local_ip %pI4h:%x vlan=%x\n",
			   cm_info->remote_ip, cm_info->remote_port,
			   cm_info->local_ip, cm_info->local_port,
			   cm_info->vlan);
	अन्यथा
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "remote_ip %pI6:%x, local_ip %pI6:%x vlan=%x\n",
			   cm_info->remote_ip, cm_info->remote_port,
			   cm_info->local_ip, cm_info->local_port,
			   cm_info->vlan);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
		   "private_data_len = %x ord = %d, ird = %d\n",
		   cm_info->निजी_data_len, cm_info->ord, cm_info->ird);
पूर्ण

अटल पूर्णांक
qed_iwarp_ll2_post_rx(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_iwarp_ll2_buff *buf, u8 handle)
अणु
	पूर्णांक rc;

	rc = qed_ll2_post_rx_buffer(p_hwfn, handle, buf->data_phys_addr,
				    (u16)buf->buff_size, buf, 1);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn,
			  "Failed to repost rx buffer to ll2 rc = %d, handle=%d\n",
			  rc, handle);
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev, buf->buff_size,
				  buf->data, buf->data_phys_addr);
		kमुक्त(buf);
	पूर्ण

	वापस rc;
पूर्ण

अटल bool
qed_iwarp_ep_exists(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_iwarp_cm_info *cm_info)
अणु
	काष्ठा qed_iwarp_ep *ep = शून्य;
	bool found = false;

	list_क्रम_each_entry(ep,
			    &p_hwfn->p_rdma_info->iwarp.ep_list,
			    list_entry) अणु
		अगर ((ep->cm_info.local_port == cm_info->local_port) &&
		    (ep->cm_info.remote_port == cm_info->remote_port) &&
		    (ep->cm_info.vlan == cm_info->vlan) &&
		    !स_भेद(&ep->cm_info.local_ip, cm_info->local_ip,
			    माप(cm_info->local_ip)) &&
		    !स_भेद(&ep->cm_info.remote_ip, cm_info->remote_ip,
			    माप(cm_info->remote_ip))) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found) अणु
		DP_NOTICE(p_hwfn,
			  "SYN received on active connection - dropping\n");
		qed_iwarp_prपूर्णांक_cm_info(p_hwfn, cm_info);

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल काष्ठा qed_iwarp_listener *
qed_iwarp_get_listener(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_iwarp_cm_info *cm_info)
अणु
	काष्ठा qed_iwarp_listener *listener = शून्य;
	अटल स्थिर u32 ip_zero[4] = अणु 0, 0, 0, 0 पूर्ण;
	bool found = false;

	qed_iwarp_prपूर्णांक_cm_info(p_hwfn, cm_info);

	list_क्रम_each_entry(listener,
			    &p_hwfn->p_rdma_info->iwarp.listen_list,
			    list_entry) अणु
		अगर (listener->port == cm_info->local_port) अणु
			अगर (!स_भेद(listener->ip_addr,
				    ip_zero, माप(ip_zero))) अणु
				found = true;
				अवरोध;
			पूर्ण

			अगर (!स_भेद(listener->ip_addr,
				    cm_info->local_ip,
				    माप(cm_info->local_ip)) &&
			    (listener->vlan == cm_info->vlan)) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (found) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "listener found = %p\n",
			   listener);
		वापस listener;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "listener not found\n");
	वापस शून्य;
पूर्ण

अटल पूर्णांक
qed_iwarp_parse_rx_pkt(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_iwarp_cm_info *cm_info,
		       व्योम *buf,
		       u8 *remote_mac_addr,
		       u8 *local_mac_addr,
		       पूर्णांक *payload_len, पूर्णांक *tcp_start_offset)
अणु
	काष्ठा vlan_ethhdr *vethh;
	bool vlan_valid = false;
	काष्ठा ipv6hdr *ip6h;
	काष्ठा ethhdr *ethh;
	काष्ठा tcphdr *tcph;
	काष्ठा iphdr *iph;
	पूर्णांक eth_hlen;
	पूर्णांक ip_hlen;
	पूर्णांक eth_type;
	पूर्णांक i;

	ethh = buf;
	eth_type = ntohs(ethh->h_proto);
	अगर (eth_type == ETH_P_8021Q) अणु
		vlan_valid = true;
		vethh = (काष्ठा vlan_ethhdr *)ethh;
		cm_info->vlan = ntohs(vethh->h_vlan_TCI) & VLAN_VID_MASK;
		eth_type = ntohs(vethh->h_vlan_encapsulated_proto);
	पूर्ण

	eth_hlen = ETH_HLEN + (vlan_valid ? माप(u32) : 0);

	अगर (!ether_addr_equal(ethh->h_dest,
			      p_hwfn->p_rdma_info->iwarp.mac_addr)) अणु
		DP_VERBOSE(p_hwfn,
			   QED_MSG_RDMA,
			   "Got unexpected mac %pM instead of %pM\n",
			   ethh->h_dest, p_hwfn->p_rdma_info->iwarp.mac_addr);
		वापस -EINVAL;
	पूर्ण

	ether_addr_copy(remote_mac_addr, ethh->h_source);
	ether_addr_copy(local_mac_addr, ethh->h_dest);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "eth_type =%d source mac: %pM\n",
		   eth_type, ethh->h_source);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "eth_hlen=%d destination mac: %pM\n",
		   eth_hlen, ethh->h_dest);

	iph = (काष्ठा iphdr *)((u8 *)(ethh) + eth_hlen);

	अगर (eth_type == ETH_P_IP) अणु
		अगर (iph->protocol != IPPROTO_TCP) अणु
			DP_NOTICE(p_hwfn,
				  "Unexpected ip protocol on ll2 %x\n",
				  iph->protocol);
			वापस -EINVAL;
		पूर्ण

		cm_info->local_ip[0] = ntohl(iph->daddr);
		cm_info->remote_ip[0] = ntohl(iph->saddr);
		cm_info->ip_version = QED_TCP_IPV4;

		ip_hlen = (iph->ihl) * माप(u32);
		*payload_len = ntohs(iph->tot_len) - ip_hlen;
	पूर्ण अन्यथा अगर (eth_type == ETH_P_IPV6) अणु
		ip6h = (काष्ठा ipv6hdr *)iph;

		अगर (ip6h->nexthdr != IPPROTO_TCP) अणु
			DP_NOTICE(p_hwfn,
				  "Unexpected ip protocol on ll2 %x\n",
				  iph->protocol);
			वापस -EINVAL;
		पूर्ण

		क्रम (i = 0; i < 4; i++) अणु
			cm_info->local_ip[i] =
			    ntohl(ip6h->daddr.in6_u.u6_addr32[i]);
			cm_info->remote_ip[i] =
			    ntohl(ip6h->saddr.in6_u.u6_addr32[i]);
		पूर्ण
		cm_info->ip_version = QED_TCP_IPV6;

		ip_hlen = माप(*ip6h);
		*payload_len = ntohs(ip6h->payload_len);
	पूर्ण अन्यथा अणु
		DP_NOTICE(p_hwfn, "Unexpected ethertype on ll2 %x\n", eth_type);
		वापस -EINVAL;
	पूर्ण

	tcph = (काष्ठा tcphdr *)((u8 *)iph + ip_hlen);

	अगर (!tcph->syn) अणु
		DP_NOTICE(p_hwfn,
			  "Only SYN type packet expected on this ll2 conn, iph->ihl=%d source=%d dest=%d\n",
			  iph->ihl, tcph->source, tcph->dest);
		वापस -EINVAL;
	पूर्ण

	cm_info->local_port = ntohs(tcph->dest);
	cm_info->remote_port = ntohs(tcph->source);

	qed_iwarp_prपूर्णांक_cm_info(p_hwfn, cm_info);

	*tcp_start_offset = eth_hlen + ip_hlen;

	वापस 0;
पूर्ण

अटल काष्ठा qed_iwarp_fpdu *qed_iwarp_get_curr_fpdu(काष्ठा qed_hwfn *p_hwfn,
						      u16 cid)
अणु
	काष्ठा qed_iwarp_info *iwarp_info = &p_hwfn->p_rdma_info->iwarp;
	काष्ठा qed_iwarp_fpdu *partial_fpdu;
	u32 idx;

	idx = cid - qed_cxt_get_proto_cid_start(p_hwfn, PROTOCOLID_IWARP);
	अगर (idx >= iwarp_info->max_num_partial_fpdus) अणु
		DP_ERR(p_hwfn, "Invalid cid %x max_num_partial_fpdus=%x\n", cid,
		       iwarp_info->max_num_partial_fpdus);
		वापस शून्य;
	पूर्ण

	partial_fpdu = &iwarp_info->partial_fpdus[idx];

	वापस partial_fpdu;
पूर्ण

क्रमागत qed_iwarp_mpa_pkt_type अणु
	QED_IWARP_MPA_PKT_PACKED,
	QED_IWARP_MPA_PKT_PARTIAL,
	QED_IWARP_MPA_PKT_UNALIGNED
पूर्ण;

#घोषणा QED_IWARP_INVALID_FPDU_LENGTH 0xffff
#घोषणा QED_IWARP_MPA_FPDU_LENGTH_SIZE (2)
#घोषणा QED_IWARP_MPA_CRC32_DIGEST_SIZE (4)

/* Pad to multiple of 4 */
#घोषणा QED_IWARP_PDU_DATA_LEN_WITH_PAD(data_len) ALIGN(data_len, 4)
#घोषणा QED_IWARP_FPDU_LEN_WITH_PAD(_mpa_len)				   \
	(QED_IWARP_PDU_DATA_LEN_WITH_PAD((_mpa_len) +			   \
					 QED_IWARP_MPA_FPDU_LENGTH_SIZE) + \
					 QED_IWARP_MPA_CRC32_DIGEST_SIZE)

/* fpdu can be fragmented over maximum 3 bds: header, partial mpa, unaligned */
#घोषणा QED_IWARP_MAX_BDS_PER_FPDU 3

अटल स्थिर अक्षर * स्थिर pkt_type_str[] = अणु
	"QED_IWARP_MPA_PKT_PACKED",
	"QED_IWARP_MPA_PKT_PARTIAL",
	"QED_IWARP_MPA_PKT_UNALIGNED"
पूर्ण;

अटल पूर्णांक
qed_iwarp_recycle_pkt(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_iwarp_fpdu *fpdu,
		      काष्ठा qed_iwarp_ll2_buff *buf);

अटल क्रमागत qed_iwarp_mpa_pkt_type
qed_iwarp_mpa_classअगरy(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_iwarp_fpdu *fpdu,
		       u16 tcp_payload_len, u8 *mpa_data)
अणु
	क्रमागत qed_iwarp_mpa_pkt_type pkt_type;
	u16 mpa_len;

	अगर (fpdu->incomplete_bytes) अणु
		pkt_type = QED_IWARP_MPA_PKT_UNALIGNED;
		जाओ out;
	पूर्ण

	/* special हाल of one byte reमुख्यing...
	 * lower byte will be पढ़ो next packet
	 */
	अगर (tcp_payload_len == 1) अणु
		fpdu->fpdu_length = *mpa_data << BITS_PER_BYTE;
		pkt_type = QED_IWARP_MPA_PKT_PARTIAL;
		जाओ out;
	पूर्ण

	mpa_len = ntohs(*(__क्रमce __be16 *)mpa_data);
	fpdu->fpdu_length = QED_IWARP_FPDU_LEN_WITH_PAD(mpa_len);

	अगर (fpdu->fpdu_length <= tcp_payload_len)
		pkt_type = QED_IWARP_MPA_PKT_PACKED;
	अन्यथा
		pkt_type = QED_IWARP_MPA_PKT_PARTIAL;

out:
	DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
		   "MPA_ALIGN: %s: fpdu_length=0x%x tcp_payload_len:0x%x\n",
		   pkt_type_str[pkt_type], fpdu->fpdu_length, tcp_payload_len);

	वापस pkt_type;
पूर्ण

अटल व्योम
qed_iwarp_init_fpdu(काष्ठा qed_iwarp_ll2_buff *buf,
		    काष्ठा qed_iwarp_fpdu *fpdu,
		    काष्ठा unaligned_opaque_data *pkt_data,
		    u16 tcp_payload_size, u8 placement_offset)
अणु
	u16 first_mpa_offset = le16_to_cpu(pkt_data->first_mpa_offset);

	fpdu->mpa_buf = buf;
	fpdu->pkt_hdr = buf->data_phys_addr + placement_offset;
	fpdu->pkt_hdr_size = pkt_data->tcp_payload_offset;
	fpdu->mpa_frag = buf->data_phys_addr + first_mpa_offset;
	fpdu->mpa_frag_virt = (u8 *)(buf->data) + first_mpa_offset;

	अगर (tcp_payload_size == 1)
		fpdu->incomplete_bytes = QED_IWARP_INVALID_FPDU_LENGTH;
	अन्यथा अगर (tcp_payload_size < fpdu->fpdu_length)
		fpdu->incomplete_bytes = fpdu->fpdu_length - tcp_payload_size;
	अन्यथा
		fpdu->incomplete_bytes = 0;	/* complete fpdu */

	fpdu->mpa_frag_len = fpdu->fpdu_length - fpdu->incomplete_bytes;
पूर्ण

अटल पूर्णांक
qed_iwarp_cp_pkt(काष्ठा qed_hwfn *p_hwfn,
		 काष्ठा qed_iwarp_fpdu *fpdu,
		 काष्ठा unaligned_opaque_data *pkt_data,
		 काष्ठा qed_iwarp_ll2_buff *buf, u16 tcp_payload_size)
अणु
	u16 first_mpa_offset = le16_to_cpu(pkt_data->first_mpa_offset);
	u8 *पंचांगp_buf = p_hwfn->p_rdma_info->iwarp.mpa_पूर्णांकermediate_buf;
	पूर्णांक rc;

	/* need to copy the data from the partial packet stored in fpdu
	 * to the new buf, क्रम this we also need to move the data currently
	 * placed on the buf. The assumption is that the buffer is big enough
	 * since fpdu_length <= mss, we use an पूर्णांकermediate buffer since
	 * we may need to copy the new data to an overlapping location
	 */
	अगर ((fpdu->mpa_frag_len + tcp_payload_size) > (u16)buf->buff_size) अणु
		DP_ERR(p_hwfn,
		       "MPA ALIGN: Unexpected: buffer is not large enough for split fpdu buff_size = %d mpa_frag_len = %d, tcp_payload_size = %d, incomplete_bytes = %d\n",
		       buf->buff_size, fpdu->mpa_frag_len,
		       tcp_payload_size, fpdu->incomplete_bytes);
		वापस -EINVAL;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
		   "MPA ALIGN Copying fpdu: [%p, %d] [%p, %d]\n",
		   fpdu->mpa_frag_virt, fpdu->mpa_frag_len,
		   (u8 *)(buf->data) + first_mpa_offset, tcp_payload_size);

	स_नकल(पंचांगp_buf, fpdu->mpa_frag_virt, fpdu->mpa_frag_len);
	स_नकल(पंचांगp_buf + fpdu->mpa_frag_len,
	       (u8 *)(buf->data) + first_mpa_offset, tcp_payload_size);

	rc = qed_iwarp_recycle_pkt(p_hwfn, fpdu, fpdu->mpa_buf);
	अगर (rc)
		वापस rc;

	/* If we managed to post the buffer copy the data to the new buffer
	 * o/w this will occur in the next round...
	 */
	स_नकल((u8 *)(buf->data), पंचांगp_buf,
	       fpdu->mpa_frag_len + tcp_payload_size);

	fpdu->mpa_buf = buf;
	/* fpdu->pkt_hdr reमुख्यs as is */
	/* fpdu->mpa_frag is overridden with new buf */
	fpdu->mpa_frag = buf->data_phys_addr;
	fpdu->mpa_frag_virt = buf->data;
	fpdu->mpa_frag_len += tcp_payload_size;

	fpdu->incomplete_bytes -= tcp_payload_size;

	DP_VERBOSE(p_hwfn,
		   QED_MSG_RDMA,
		   "MPA ALIGN: split fpdu buff_size = %d mpa_frag_len = %d, tcp_payload_size = %d, incomplete_bytes = %d\n",
		   buf->buff_size, fpdu->mpa_frag_len, tcp_payload_size,
		   fpdu->incomplete_bytes);

	वापस 0;
पूर्ण

अटल व्योम
qed_iwarp_update_fpdu_length(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_iwarp_fpdu *fpdu, u8 *mpa_data)
अणु
	u16 mpa_len;

	/* Update incomplete packets अगर needed */
	अगर (fpdu->incomplete_bytes == QED_IWARP_INVALID_FPDU_LENGTH) अणु
		/* Missing lower byte is now available */
		mpa_len = fpdu->fpdu_length | *mpa_data;
		fpdu->fpdu_length = QED_IWARP_FPDU_LEN_WITH_PAD(mpa_len);
		/* one byte of hdr */
		fpdu->mpa_frag_len = 1;
		fpdu->incomplete_bytes = fpdu->fpdu_length - 1;
		DP_VERBOSE(p_hwfn,
			   QED_MSG_RDMA,
			   "MPA_ALIGN: Partial header mpa_len=%x fpdu_length=%x incomplete_bytes=%x\n",
			   mpa_len, fpdu->fpdu_length, fpdu->incomplete_bytes);
	पूर्ण
पूर्ण

#घोषणा QED_IWARP_IS_RIGHT_EDGE(_curr_pkt) \
	(GET_FIELD((_curr_pkt)->flags,	   \
		   UNALIGNED_OPAQUE_DATA_PKT_REACHED_WIN_RIGHT_EDGE))

/* This function is used to recycle a buffer using the ll2 drop option. It
 * uses the mechanism to ensure that all buffers posted to tx beक्रमe this one
 * were completed. The buffer sent here will be sent as a cookie in the tx
 * completion function and can then be reposted to rx chain when करोne. The flow
 * that requires this is the flow where a FPDU splits over more than 3 tcp
 * segments. In this हाल the driver needs to re-post a rx buffer instead of
 * the one received, but driver can't simply repost a buffer it copied from
 * as there is a हाल where the buffer was originally a packed FPDU, and is
 * partially posted to FW. Driver needs to ensure FW is करोne with it.
 */
अटल पूर्णांक
qed_iwarp_recycle_pkt(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_iwarp_fpdu *fpdu,
		      काष्ठा qed_iwarp_ll2_buff *buf)
अणु
	काष्ठा qed_ll2_tx_pkt_info tx_pkt;
	u8 ll2_handle;
	पूर्णांक rc;

	स_रखो(&tx_pkt, 0, माप(tx_pkt));
	tx_pkt.num_of_bds = 1;
	tx_pkt.tx_dest = QED_LL2_TX_DEST_DROP;
	tx_pkt.l4_hdr_offset_w = fpdu->pkt_hdr_size >> 2;
	tx_pkt.first_frag = fpdu->pkt_hdr;
	tx_pkt.first_frag_len = fpdu->pkt_hdr_size;
	buf->piggy_buf = शून्य;
	tx_pkt.cookie = buf;

	ll2_handle = p_hwfn->p_rdma_info->iwarp.ll2_mpa_handle;

	rc = qed_ll2_prepare_tx_packet(p_hwfn, ll2_handle, &tx_pkt, true);
	अगर (rc)
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "Can't drop packet rc=%d\n", rc);

	DP_VERBOSE(p_hwfn,
		   QED_MSG_RDMA,
		   "MPA_ALIGN: send drop tx packet [%lx, 0x%x], buf=%p, rc=%d\n",
		   (अचिन्हित दीर्घ पूर्णांक)tx_pkt.first_frag,
		   tx_pkt.first_frag_len, buf, rc);

	वापस rc;
पूर्ण

अटल पूर्णांक
qed_iwarp_win_right_edge(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_iwarp_fpdu *fpdu)
अणु
	काष्ठा qed_ll2_tx_pkt_info tx_pkt;
	u8 ll2_handle;
	पूर्णांक rc;

	स_रखो(&tx_pkt, 0, माप(tx_pkt));
	tx_pkt.num_of_bds = 1;
	tx_pkt.tx_dest = QED_LL2_TX_DEST_LB;
	tx_pkt.l4_hdr_offset_w = fpdu->pkt_hdr_size >> 2;

	tx_pkt.first_frag = fpdu->pkt_hdr;
	tx_pkt.first_frag_len = fpdu->pkt_hdr_size;
	tx_pkt.enable_ip_cksum = true;
	tx_pkt.enable_l4_cksum = true;
	tx_pkt.calc_ip_len = true;
	/* vlan overload with क्रमागत iwarp_ll2_tx_queues */
	tx_pkt.vlan = IWARP_LL2_ALIGNED_RIGHT_TRIMMED_TX_QUEUE;

	ll2_handle = p_hwfn->p_rdma_info->iwarp.ll2_mpa_handle;

	rc = qed_ll2_prepare_tx_packet(p_hwfn, ll2_handle, &tx_pkt, true);
	अगर (rc)
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "Can't send right edge rc=%d\n", rc);
	DP_VERBOSE(p_hwfn,
		   QED_MSG_RDMA,
		   "MPA_ALIGN: Sent right edge FPDU num_bds=%d [%lx, 0x%x], rc=%d\n",
		   tx_pkt.num_of_bds,
		   (अचिन्हित दीर्घ पूर्णांक)tx_pkt.first_frag,
		   tx_pkt.first_frag_len, rc);

	वापस rc;
पूर्ण

अटल पूर्णांक
qed_iwarp_send_fpdu(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_iwarp_fpdu *fpdu,
		    काष्ठा unaligned_opaque_data *curr_pkt,
		    काष्ठा qed_iwarp_ll2_buff *buf,
		    u16 tcp_payload_size, क्रमागत qed_iwarp_mpa_pkt_type pkt_type)
अणु
	काष्ठा qed_ll2_tx_pkt_info tx_pkt;
	u16 first_mpa_offset;
	u8 ll2_handle;
	पूर्णांक rc;

	स_रखो(&tx_pkt, 0, माप(tx_pkt));

	/* An unaligned packet means it's split over two tcp segments. So the
	 * complete packet requires 3 bds, one क्रम the header, one क्रम the
	 * part of the fpdu of the first tcp segment, and the last fragment
	 * will poपूर्णांक to the reमुख्यder of the fpdu. A packed pdu, requires only
	 * two bds, one क्रम the header and one क्रम the data.
	 */
	tx_pkt.num_of_bds = (pkt_type == QED_IWARP_MPA_PKT_UNALIGNED) ? 3 : 2;
	tx_pkt.tx_dest = QED_LL2_TX_DEST_LB;
	tx_pkt.l4_hdr_offset_w = fpdu->pkt_hdr_size >> 2; /* offset in words */

	/* Send the mpa_buf only with the last fpdu (in हाल of packed) */
	अगर (pkt_type == QED_IWARP_MPA_PKT_UNALIGNED ||
	    tcp_payload_size <= fpdu->fpdu_length)
		tx_pkt.cookie = fpdu->mpa_buf;

	tx_pkt.first_frag = fpdu->pkt_hdr;
	tx_pkt.first_frag_len = fpdu->pkt_hdr_size;
	tx_pkt.enable_ip_cksum = true;
	tx_pkt.enable_l4_cksum = true;
	tx_pkt.calc_ip_len = true;
	/* vlan overload with क्रमागत iwarp_ll2_tx_queues */
	tx_pkt.vlan = IWARP_LL2_ALIGNED_TX_QUEUE;

	/* special हाल of unaligned packet and not packed, need to send
	 * both buffers as cookie to release.
	 */
	अगर (tcp_payload_size == fpdu->incomplete_bytes)
		fpdu->mpa_buf->piggy_buf = buf;

	ll2_handle = p_hwfn->p_rdma_info->iwarp.ll2_mpa_handle;

	/* Set first fragment to header */
	rc = qed_ll2_prepare_tx_packet(p_hwfn, ll2_handle, &tx_pkt, true);
	अगर (rc)
		जाओ out;

	/* Set second fragment to first part of packet */
	rc = qed_ll2_set_fragment_of_tx_packet(p_hwfn, ll2_handle,
					       fpdu->mpa_frag,
					       fpdu->mpa_frag_len);
	अगर (rc)
		जाओ out;

	अगर (!fpdu->incomplete_bytes)
		जाओ out;

	first_mpa_offset = le16_to_cpu(curr_pkt->first_mpa_offset);

	/* Set third fragment to second part of the packet */
	rc = qed_ll2_set_fragment_of_tx_packet(p_hwfn,
					       ll2_handle,
					       buf->data_phys_addr +
					       first_mpa_offset,
					       fpdu->incomplete_bytes);
out:
	DP_VERBOSE(p_hwfn,
		   QED_MSG_RDMA,
		   "MPA_ALIGN: Sent FPDU num_bds=%d first_frag_len=%x, mpa_frag_len=0x%x, incomplete_bytes:0x%x rc=%d\n",
		   tx_pkt.num_of_bds,
		   tx_pkt.first_frag_len,
		   fpdu->mpa_frag_len,
		   fpdu->incomplete_bytes, rc);

	वापस rc;
पूर्ण

अटल व्योम
qed_iwarp_mpa_get_data(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा unaligned_opaque_data *curr_pkt,
		       u32 opaque_data0, u32 opaque_data1)
अणु
	u64 opaque_data;

	opaque_data = HILO_64(cpu_to_le32(opaque_data1),
			      cpu_to_le32(opaque_data0));
	*curr_pkt = *((काष्ठा unaligned_opaque_data *)&opaque_data);

	le16_add_cpu(&curr_pkt->first_mpa_offset,
		     curr_pkt->tcp_payload_offset);
पूर्ण

/* This function is called when an unaligned or incomplete MPA packet arrives
 * driver needs to align the packet, perhaps using previous data and send
 * it करोwn to FW once it is aligned.
 */
अटल पूर्णांक
qed_iwarp_process_mpa_pkt(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_iwarp_ll2_mpa_buf *mpa_buf)
अणु
	काष्ठा unaligned_opaque_data *curr_pkt = &mpa_buf->data;
	काष्ठा qed_iwarp_ll2_buff *buf = mpa_buf->ll2_buf;
	क्रमागत qed_iwarp_mpa_pkt_type pkt_type;
	काष्ठा qed_iwarp_fpdu *fpdu;
	u16 cid, first_mpa_offset;
	पूर्णांक rc = -EINVAL;
	u8 *mpa_data;

	cid = le32_to_cpu(curr_pkt->cid);

	fpdu = qed_iwarp_get_curr_fpdu(p_hwfn, (u16)cid);
	अगर (!fpdu) अणु /* something corrupt with cid, post rx back */
		DP_ERR(p_hwfn, "Invalid cid, drop and post back to rx cid=%x\n",
		       cid);
		जाओ err;
	पूर्ण

	करो अणु
		first_mpa_offset = le16_to_cpu(curr_pkt->first_mpa_offset);
		mpa_data = ((u8 *)(buf->data) + first_mpa_offset);

		pkt_type = qed_iwarp_mpa_classअगरy(p_hwfn, fpdu,
						  mpa_buf->tcp_payload_len,
						  mpa_data);

		चयन (pkt_type) अणु
		हाल QED_IWARP_MPA_PKT_PARTIAL:
			qed_iwarp_init_fpdu(buf, fpdu,
					    curr_pkt,
					    mpa_buf->tcp_payload_len,
					    mpa_buf->placement_offset);

			अगर (!QED_IWARP_IS_RIGHT_EDGE(curr_pkt)) अणु
				mpa_buf->tcp_payload_len = 0;
				अवरोध;
			पूर्ण

			rc = qed_iwarp_win_right_edge(p_hwfn, fpdu);

			अगर (rc) अणु
				DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
					   "Can't send FPDU:reset rc=%d\n", rc);
				स_रखो(fpdu, 0, माप(*fpdu));
				अवरोध;
			पूर्ण

			mpa_buf->tcp_payload_len = 0;
			अवरोध;
		हाल QED_IWARP_MPA_PKT_PACKED:
			qed_iwarp_init_fpdu(buf, fpdu,
					    curr_pkt,
					    mpa_buf->tcp_payload_len,
					    mpa_buf->placement_offset);

			rc = qed_iwarp_send_fpdu(p_hwfn, fpdu, curr_pkt, buf,
						 mpa_buf->tcp_payload_len,
						 pkt_type);
			अगर (rc) अणु
				DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
					   "Can't send FPDU:reset rc=%d\n", rc);
				स_रखो(fpdu, 0, माप(*fpdu));
				अवरोध;
			पूर्ण

			mpa_buf->tcp_payload_len -= fpdu->fpdu_length;
			le16_add_cpu(&curr_pkt->first_mpa_offset,
				     fpdu->fpdu_length);
			अवरोध;
		हाल QED_IWARP_MPA_PKT_UNALIGNED:
			qed_iwarp_update_fpdu_length(p_hwfn, fpdu, mpa_data);
			अगर (mpa_buf->tcp_payload_len < fpdu->incomplete_bytes) अणु
				/* special handling of fpdu split over more
				 * than 2 segments
				 */
				अगर (QED_IWARP_IS_RIGHT_EDGE(curr_pkt)) अणु
					rc = qed_iwarp_win_right_edge(p_hwfn,
								      fpdu);
					/* packet will be re-processed later */
					अगर (rc)
						वापस rc;
				पूर्ण

				rc = qed_iwarp_cp_pkt(p_hwfn, fpdu, curr_pkt,
						      buf,
						      mpa_buf->tcp_payload_len);
				अगर (rc) /* packet will be re-processed later */
					वापस rc;

				mpa_buf->tcp_payload_len = 0;
				अवरोध;
			पूर्ण

			rc = qed_iwarp_send_fpdu(p_hwfn, fpdu, curr_pkt, buf,
						 mpa_buf->tcp_payload_len,
						 pkt_type);
			अगर (rc) अणु
				DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
					   "Can't send FPDU:delay rc=%d\n", rc);
				/* करोn't reset fpdu -> we need it क्रम next
				 * classअगरy
				 */
				अवरोध;
			पूर्ण

			mpa_buf->tcp_payload_len -= fpdu->incomplete_bytes;
			le16_add_cpu(&curr_pkt->first_mpa_offset,
				     fpdu->incomplete_bytes);

			/* The framed PDU was sent - no more incomplete bytes */
			fpdu->incomplete_bytes = 0;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (mpa_buf->tcp_payload_len && !rc);

	वापस rc;

err:
	qed_iwarp_ll2_post_rx(p_hwfn,
			      buf,
			      p_hwfn->p_rdma_info->iwarp.ll2_mpa_handle);
	वापस rc;
पूर्ण

अटल व्योम qed_iwarp_process_pending_pkts(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_iwarp_info *iwarp_info = &p_hwfn->p_rdma_info->iwarp;
	काष्ठा qed_iwarp_ll2_mpa_buf *mpa_buf = शून्य;
	पूर्णांक rc;

	जबतक (!list_empty(&iwarp_info->mpa_buf_pending_list)) अणु
		mpa_buf = list_first_entry(&iwarp_info->mpa_buf_pending_list,
					   काष्ठा qed_iwarp_ll2_mpa_buf,
					   list_entry);

		rc = qed_iwarp_process_mpa_pkt(p_hwfn, mpa_buf);

		/* busy means अवरोध and जारी processing later, करोn't
		 * हटाओ the buf from the pending list.
		 */
		अगर (rc == -EBUSY)
			अवरोध;

		list_move_tail(&mpa_buf->list_entry,
			       &iwarp_info->mpa_buf_list);

		अगर (rc) अणु	/* dअगरferent error, करोn't जारी */
			DP_NOTICE(p_hwfn, "process pkts failed rc=%d\n", rc);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
qed_iwarp_ll2_comp_mpa_pkt(व्योम *cxt, काष्ठा qed_ll2_comp_rx_data *data)
अणु
	काष्ठा qed_iwarp_ll2_mpa_buf *mpa_buf;
	काष्ठा qed_iwarp_info *iwarp_info;
	काष्ठा qed_hwfn *p_hwfn = cxt;
	u16 first_mpa_offset;

	iwarp_info = &p_hwfn->p_rdma_info->iwarp;
	mpa_buf = list_first_entry(&iwarp_info->mpa_buf_list,
				   काष्ठा qed_iwarp_ll2_mpa_buf, list_entry);
	अगर (!mpa_buf) अणु
		DP_ERR(p_hwfn, "No free mpa buf\n");
		जाओ err;
	पूर्ण

	list_del(&mpa_buf->list_entry);
	qed_iwarp_mpa_get_data(p_hwfn, &mpa_buf->data,
			       data->opaque_data_0, data->opaque_data_1);

	first_mpa_offset = le16_to_cpu(mpa_buf->data.first_mpa_offset);

	DP_VERBOSE(p_hwfn,
		   QED_MSG_RDMA,
		   "LL2 MPA CompRx payload_len:0x%x\tfirst_mpa_offset:0x%x\ttcp_payload_offset:0x%x\tflags:0x%x\tcid:0x%x\n",
		   data->length.packet_length, first_mpa_offset,
		   mpa_buf->data.tcp_payload_offset, mpa_buf->data.flags,
		   mpa_buf->data.cid);

	mpa_buf->ll2_buf = data->cookie;
	mpa_buf->tcp_payload_len = data->length.packet_length -
				   first_mpa_offset;

	first_mpa_offset += data->u.placement_offset;
	mpa_buf->data.first_mpa_offset = cpu_to_le16(first_mpa_offset);
	mpa_buf->placement_offset = data->u.placement_offset;

	list_add_tail(&mpa_buf->list_entry, &iwarp_info->mpa_buf_pending_list);

	qed_iwarp_process_pending_pkts(p_hwfn);
	वापस;
err:
	qed_iwarp_ll2_post_rx(p_hwfn, data->cookie,
			      iwarp_info->ll2_mpa_handle);
पूर्ण

अटल व्योम
qed_iwarp_ll2_comp_syn_pkt(व्योम *cxt, काष्ठा qed_ll2_comp_rx_data *data)
अणु
	काष्ठा qed_iwarp_ll2_buff *buf = data->cookie;
	काष्ठा qed_iwarp_listener *listener;
	काष्ठा qed_ll2_tx_pkt_info tx_pkt;
	काष्ठा qed_iwarp_cm_info cm_info;
	काष्ठा qed_hwfn *p_hwfn = cxt;
	u8 remote_mac_addr[ETH_ALEN];
	u8 local_mac_addr[ETH_ALEN];
	काष्ठा qed_iwarp_ep *ep;
	पूर्णांक tcp_start_offset;
	u8 ll2_syn_handle;
	पूर्णांक payload_len;
	u32 hdr_size;
	पूर्णांक rc;

	स_रखो(&cm_info, 0, माप(cm_info));
	ll2_syn_handle = p_hwfn->p_rdma_info->iwarp.ll2_syn_handle;

	/* Check अगर packet was received with errors... */
	अगर (data->err_flags) अणु
		DP_NOTICE(p_hwfn, "Error received on SYN packet: 0x%x\n",
			  data->err_flags);
		जाओ err;
	पूर्ण

	अगर (GET_FIELD(data->parse_flags,
		      PARSING_AND_ERR_FLAGS_L4CHKSMWASCALCULATED) &&
	    GET_FIELD(data->parse_flags, PARSING_AND_ERR_FLAGS_L4CHKSMERROR)) अणु
		DP_NOTICE(p_hwfn, "Syn packet received with checksum error\n");
		जाओ err;
	पूर्ण

	rc = qed_iwarp_parse_rx_pkt(p_hwfn, &cm_info, (u8 *)(buf->data) +
				    data->u.placement_offset, remote_mac_addr,
				    local_mac_addr, &payload_len,
				    &tcp_start_offset);
	अगर (rc)
		जाओ err;

	/* Check अगर there is a listener क्रम this 4-tuple+vlan */
	listener = qed_iwarp_get_listener(p_hwfn, &cm_info);
	अगर (!listener) अणु
		DP_VERBOSE(p_hwfn,
			   QED_MSG_RDMA,
			   "SYN received on tuple not listened on parse_flags=%d packet len=%d\n",
			   data->parse_flags, data->length.packet_length);

		स_रखो(&tx_pkt, 0, माप(tx_pkt));
		tx_pkt.num_of_bds = 1;
		tx_pkt.l4_hdr_offset_w = (data->length.packet_length) >> 2;
		tx_pkt.tx_dest = QED_LL2_TX_DEST_LB;
		tx_pkt.first_frag = buf->data_phys_addr +
				    data->u.placement_offset;
		tx_pkt.first_frag_len = data->length.packet_length;
		tx_pkt.cookie = buf;

		rc = qed_ll2_prepare_tx_packet(p_hwfn, ll2_syn_handle,
					       &tx_pkt, true);

		अगर (rc) अणु
			DP_NOTICE(p_hwfn,
				  "Can't post SYN back to chip rc=%d\n", rc);
			जाओ err;
		पूर्ण
		वापस;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Received syn on listening port\n");
	/* There may be an खोलो ep on this connection अगर this is a syn
	 * retrasnmit... need to make sure there isn't...
	 */
	अगर (qed_iwarp_ep_exists(p_hwfn, &cm_info))
		जाओ err;

	ep = qed_iwarp_get_मुक्त_ep(p_hwfn);
	अगर (!ep)
		जाओ err;

	spin_lock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);
	list_add_tail(&ep->list_entry, &p_hwfn->p_rdma_info->iwarp.ep_list);
	spin_unlock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);

	ether_addr_copy(ep->remote_mac_addr, remote_mac_addr);
	ether_addr_copy(ep->local_mac_addr, local_mac_addr);

	स_नकल(&ep->cm_info, &cm_info, माप(ep->cm_info));

	hdr_size = ((cm_info.ip_version == QED_TCP_IPV4) ? 40 : 60);
	ep->mss = p_hwfn->p_rdma_info->iwarp.max_mtu - hdr_size;
	ep->mss = min_t(u16, QED_IWARP_MAX_FW_MSS, ep->mss);

	ep->event_cb = listener->event_cb;
	ep->cb_context = listener->cb_context;
	ep->connect_mode = TCP_CONNECT_PASSIVE;

	ep->syn = buf;
	ep->syn_ip_payload_length = (u16)payload_len;
	ep->syn_phy_addr = buf->data_phys_addr + data->u.placement_offset +
			   tcp_start_offset;

	rc = qed_iwarp_tcp_offload(p_hwfn, ep);
	अगर (rc) अणु
		qed_iwarp_वापस_ep(p_hwfn, ep);
		जाओ err;
	पूर्ण

	वापस;
err:
	qed_iwarp_ll2_post_rx(p_hwfn, buf, ll2_syn_handle);
पूर्ण

अटल व्योम qed_iwarp_ll2_rel_rx_pkt(व्योम *cxt, u8 connection_handle,
				     व्योम *cookie, dma_addr_t rx_buf_addr,
				     bool b_last_packet)
अणु
	काष्ठा qed_iwarp_ll2_buff *buffer = cookie;
	काष्ठा qed_hwfn *p_hwfn = cxt;

	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev, buffer->buff_size,
			  buffer->data, buffer->data_phys_addr);
	kमुक्त(buffer);
पूर्ण

अटल व्योम qed_iwarp_ll2_comp_tx_pkt(व्योम *cxt, u8 connection_handle,
				      व्योम *cookie, dma_addr_t first_frag_addr,
				      bool b_last_fragment, bool b_last_packet)
अणु
	काष्ठा qed_iwarp_ll2_buff *buffer = cookie;
	काष्ठा qed_iwarp_ll2_buff *piggy;
	काष्ठा qed_hwfn *p_hwfn = cxt;

	अगर (!buffer)		/* can happen in packed mpa unaligned... */
		वापस;

	/* this was originally an rx packet, post it back */
	piggy = buffer->piggy_buf;
	अगर (piggy) अणु
		buffer->piggy_buf = शून्य;
		qed_iwarp_ll2_post_rx(p_hwfn, piggy, connection_handle);
	पूर्ण

	qed_iwarp_ll2_post_rx(p_hwfn, buffer, connection_handle);

	अगर (connection_handle == p_hwfn->p_rdma_info->iwarp.ll2_mpa_handle)
		qed_iwarp_process_pending_pkts(p_hwfn);

	वापस;
पूर्ण

अटल व्योम qed_iwarp_ll2_rel_tx_pkt(व्योम *cxt, u8 connection_handle,
				     व्योम *cookie, dma_addr_t first_frag_addr,
				     bool b_last_fragment, bool b_last_packet)
अणु
	काष्ठा qed_iwarp_ll2_buff *buffer = cookie;
	काष्ठा qed_hwfn *p_hwfn = cxt;

	अगर (!buffer)
		वापस;

	अगर (buffer->piggy_buf) अणु
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  buffer->piggy_buf->buff_size,
				  buffer->piggy_buf->data,
				  buffer->piggy_buf->data_phys_addr);

		kमुक्त(buffer->piggy_buf);
	पूर्ण

	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev, buffer->buff_size,
			  buffer->data, buffer->data_phys_addr);

	kमुक्त(buffer);
पूर्ण

/* The only slowpath क्रम iwarp ll2 is unalign flush. When this completion
 * is received, need to reset the FPDU.
 */
अटल व्योम
qed_iwarp_ll2_slowpath(व्योम *cxt,
		       u8 connection_handle,
		       u32 opaque_data_0, u32 opaque_data_1)
अणु
	काष्ठा unaligned_opaque_data unalign_data;
	काष्ठा qed_hwfn *p_hwfn = cxt;
	काष्ठा qed_iwarp_fpdu *fpdu;
	u32 cid;

	qed_iwarp_mpa_get_data(p_hwfn, &unalign_data,
			       opaque_data_0, opaque_data_1);

	cid = le32_to_cpu(unalign_data.cid);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "(0x%x) Flush fpdu\n", cid);

	fpdu = qed_iwarp_get_curr_fpdu(p_hwfn, (u16)cid);
	अगर (fpdu)
		स_रखो(fpdu, 0, माप(*fpdu));
पूर्ण

अटल पूर्णांक qed_iwarp_ll2_stop(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_iwarp_info *iwarp_info = &p_hwfn->p_rdma_info->iwarp;
	पूर्णांक rc = 0;

	अगर (iwarp_info->ll2_syn_handle != QED_IWARP_HANDLE_INVAL) अणु
		rc = qed_ll2_terminate_connection(p_hwfn,
						  iwarp_info->ll2_syn_handle);
		अगर (rc)
			DP_INFO(p_hwfn, "Failed to terminate syn connection\n");

		qed_ll2_release_connection(p_hwfn, iwarp_info->ll2_syn_handle);
		iwarp_info->ll2_syn_handle = QED_IWARP_HANDLE_INVAL;
	पूर्ण

	अगर (iwarp_info->ll2_ooo_handle != QED_IWARP_HANDLE_INVAL) अणु
		rc = qed_ll2_terminate_connection(p_hwfn,
						  iwarp_info->ll2_ooo_handle);
		अगर (rc)
			DP_INFO(p_hwfn, "Failed to terminate ooo connection\n");

		qed_ll2_release_connection(p_hwfn, iwarp_info->ll2_ooo_handle);
		iwarp_info->ll2_ooo_handle = QED_IWARP_HANDLE_INVAL;
	पूर्ण

	अगर (iwarp_info->ll2_mpa_handle != QED_IWARP_HANDLE_INVAL) अणु
		rc = qed_ll2_terminate_connection(p_hwfn,
						  iwarp_info->ll2_mpa_handle);
		अगर (rc)
			DP_INFO(p_hwfn, "Failed to terminate mpa connection\n");

		qed_ll2_release_connection(p_hwfn, iwarp_info->ll2_mpa_handle);
		iwarp_info->ll2_mpa_handle = QED_IWARP_HANDLE_INVAL;
	पूर्ण

	qed_llh_हटाओ_mac_filter(p_hwfn->cdev, 0,
				  p_hwfn->p_rdma_info->iwarp.mac_addr);

	वापस rc;
पूर्ण

अटल पूर्णांक
qed_iwarp_ll2_alloc_buffers(काष्ठा qed_hwfn *p_hwfn,
			    पूर्णांक num_rx_bufs, पूर्णांक buff_size, u8 ll2_handle)
अणु
	काष्ठा qed_iwarp_ll2_buff *buffer;
	पूर्णांक rc = 0;
	पूर्णांक i;

	क्रम (i = 0; i < num_rx_bufs; i++) अणु
		buffer = kzalloc(माप(*buffer), GFP_KERNEL);
		अगर (!buffer) अणु
			rc = -ENOMEM;
			अवरोध;
		पूर्ण

		buffer->data = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
						  buff_size,
						  &buffer->data_phys_addr,
						  GFP_KERNEL);
		अगर (!buffer->data) अणु
			kमुक्त(buffer);
			rc = -ENOMEM;
			अवरोध;
		पूर्ण

		buffer->buff_size = buff_size;
		rc = qed_iwarp_ll2_post_rx(p_hwfn, buffer, ll2_handle);
		अगर (rc)
			/* buffers will be deallocated by qed_ll2 */
			अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

#घोषणा QED_IWARP_MAX_BUF_SIZE(mtu)				     \
	ALIGN((mtu) + ETH_HLEN + 2 * VLAN_HLEN + 2 + ETH_CACHE_LINE_SIZE, \
		ETH_CACHE_LINE_SIZE)

अटल पूर्णांक
qed_iwarp_ll2_start(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_rdma_start_in_params *params,
		    u32 rcv_wnd_size)
अणु
	काष्ठा qed_iwarp_info *iwarp_info;
	काष्ठा qed_ll2_acquire_data data;
	काष्ठा qed_ll2_cbs cbs;
	u32 buff_size;
	u16 n_ooo_bufs;
	पूर्णांक rc = 0;
	पूर्णांक i;

	iwarp_info = &p_hwfn->p_rdma_info->iwarp;
	iwarp_info->ll2_syn_handle = QED_IWARP_HANDLE_INVAL;
	iwarp_info->ll2_ooo_handle = QED_IWARP_HANDLE_INVAL;
	iwarp_info->ll2_mpa_handle = QED_IWARP_HANDLE_INVAL;

	iwarp_info->max_mtu = params->max_mtu;

	ether_addr_copy(p_hwfn->p_rdma_info->iwarp.mac_addr, params->mac_addr);

	rc = qed_llh_add_mac_filter(p_hwfn->cdev, 0, params->mac_addr);
	अगर (rc)
		वापस rc;

	/* Start SYN connection */
	cbs.rx_comp_cb = qed_iwarp_ll2_comp_syn_pkt;
	cbs.rx_release_cb = qed_iwarp_ll2_rel_rx_pkt;
	cbs.tx_comp_cb = qed_iwarp_ll2_comp_tx_pkt;
	cbs.tx_release_cb = qed_iwarp_ll2_rel_tx_pkt;
	cbs.slowpath_cb = शून्य;
	cbs.cookie = p_hwfn;

	स_रखो(&data, 0, माप(data));
	data.input.conn_type = QED_LL2_TYPE_IWARP;
	/* SYN will use ctx based queues */
	data.input.rx_conn_type = QED_LL2_RX_TYPE_CTX;
	data.input.mtu = params->max_mtu;
	data.input.rx_num_desc = QED_IWARP_LL2_SYN_RX_SIZE;
	data.input.tx_num_desc = QED_IWARP_LL2_SYN_TX_SIZE;
	data.input.tx_max_bds_per_packet = 1;	/* will never be fragmented */
	data.input.tx_tc = PKT_LB_TC;
	data.input.tx_dest = QED_LL2_TX_DEST_LB;
	data.p_connection_handle = &iwarp_info->ll2_syn_handle;
	data.cbs = &cbs;

	rc = qed_ll2_acquire_connection(p_hwfn, &data);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn, "Failed to acquire LL2 connection\n");
		qed_llh_हटाओ_mac_filter(p_hwfn->cdev, 0, params->mac_addr);
		वापस rc;
	पूर्ण

	rc = qed_ll2_establish_connection(p_hwfn, iwarp_info->ll2_syn_handle);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn, "Failed to establish LL2 connection\n");
		जाओ err;
	पूर्ण

	buff_size = QED_IWARP_MAX_BUF_SIZE(params->max_mtu);
	rc = qed_iwarp_ll2_alloc_buffers(p_hwfn,
					 QED_IWARP_LL2_SYN_RX_SIZE,
					 buff_size,
					 iwarp_info->ll2_syn_handle);
	अगर (rc)
		जाओ err;

	/* Start OOO connection */
	data.input.conn_type = QED_LL2_TYPE_OOO;
	/* OOO/unaligned will use legacy ll2 queues (ram based) */
	data.input.rx_conn_type = QED_LL2_RX_TYPE_LEGACY;
	data.input.mtu = params->max_mtu;

	n_ooo_bufs = (QED_IWARP_MAX_OOO * rcv_wnd_size) /
		     iwarp_info->max_mtu;
	n_ooo_bufs = min_t(u32, n_ooo_bufs, QED_IWARP_LL2_OOO_MAX_RX_SIZE);

	data.input.rx_num_desc = n_ooo_bufs;
	data.input.rx_num_ooo_buffers = n_ooo_bufs;

	data.input.tx_max_bds_per_packet = 1;	/* will never be fragmented */
	data.input.tx_num_desc = QED_IWARP_LL2_OOO_DEF_TX_SIZE;
	data.p_connection_handle = &iwarp_info->ll2_ooo_handle;

	rc = qed_ll2_acquire_connection(p_hwfn, &data);
	अगर (rc)
		जाओ err;

	rc = qed_ll2_establish_connection(p_hwfn, iwarp_info->ll2_ooo_handle);
	अगर (rc)
		जाओ err;

	/* Start Unaligned MPA connection */
	cbs.rx_comp_cb = qed_iwarp_ll2_comp_mpa_pkt;
	cbs.slowpath_cb = qed_iwarp_ll2_slowpath;

	स_रखो(&data, 0, माप(data));
	data.input.conn_type = QED_LL2_TYPE_IWARP;
	data.input.mtu = params->max_mtu;
	/* FW requires that once a packet arrives OOO, it must have at
	 * least 2 rx buffers available on the unaligned connection
	 * क्रम handling the हाल that it is a partial fpdu.
	 */
	data.input.rx_num_desc = n_ooo_bufs * 2;
	data.input.tx_num_desc = data.input.rx_num_desc;
	data.input.tx_max_bds_per_packet = QED_IWARP_MAX_BDS_PER_FPDU;
	data.input.tx_tc = PKT_LB_TC;
	data.input.tx_dest = QED_LL2_TX_DEST_LB;
	data.p_connection_handle = &iwarp_info->ll2_mpa_handle;
	data.input.secondary_queue = true;
	data.cbs = &cbs;

	rc = qed_ll2_acquire_connection(p_hwfn, &data);
	अगर (rc)
		जाओ err;

	rc = qed_ll2_establish_connection(p_hwfn, iwarp_info->ll2_mpa_handle);
	अगर (rc)
		जाओ err;

	rc = qed_iwarp_ll2_alloc_buffers(p_hwfn,
					 data.input.rx_num_desc,
					 buff_size,
					 iwarp_info->ll2_mpa_handle);
	अगर (rc)
		जाओ err;

	iwarp_info->partial_fpdus = kसुस्मृति((u16)p_hwfn->p_rdma_info->num_qps,
					    माप(*iwarp_info->partial_fpdus),
					    GFP_KERNEL);
	अगर (!iwarp_info->partial_fpdus) अणु
		rc = -ENOMEM;
		जाओ err;
	पूर्ण

	iwarp_info->max_num_partial_fpdus = (u16)p_hwfn->p_rdma_info->num_qps;

	iwarp_info->mpa_पूर्णांकermediate_buf = kzalloc(buff_size, GFP_KERNEL);
	अगर (!iwarp_info->mpa_पूर्णांकermediate_buf) अणु
		rc = -ENOMEM;
		जाओ err;
	पूर्ण

	/* The mpa_bufs array serves क्रम pending RX packets received on the
	 * mpa ll2 that करोn't have place on the tx ring and require later
	 * processing. We can't fail on allocation of such a काष्ठा thereक्रमe
	 * we allocate enough to take care of all rx packets
	 */
	iwarp_info->mpa_bufs = kसुस्मृति(data.input.rx_num_desc,
				       माप(*iwarp_info->mpa_bufs),
				       GFP_KERNEL);
	अगर (!iwarp_info->mpa_bufs) अणु
		rc = -ENOMEM;
		जाओ err;
	पूर्ण

	INIT_LIST_HEAD(&iwarp_info->mpa_buf_pending_list);
	INIT_LIST_HEAD(&iwarp_info->mpa_buf_list);
	क्रम (i = 0; i < data.input.rx_num_desc; i++)
		list_add_tail(&iwarp_info->mpa_bufs[i].list_entry,
			      &iwarp_info->mpa_buf_list);
	वापस rc;
err:
	qed_iwarp_ll2_stop(p_hwfn);

	वापस rc;
पूर्ण

अटल काष्ठा अणु
	u32 two_ports;
	u32 four_ports;
पूर्ण qed_iwarp_rcv_wnd_size[MAX_CHIP_IDS] = अणु
	अणुQED_IWARP_RCV_WND_SIZE_DEF_BB_2P, QED_IWARP_RCV_WND_SIZE_DEF_BB_4Pपूर्ण,
	अणुQED_IWARP_RCV_WND_SIZE_DEF_AH_2P, QED_IWARP_RCV_WND_SIZE_DEF_AH_4Pपूर्ण
पूर्ण;

पूर्णांक qed_iwarp_setup(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_rdma_start_in_params *params)
अणु
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	काष्ठा qed_iwarp_info *iwarp_info;
	क्रमागत chip_ids chip_id;
	u32 rcv_wnd_size;

	iwarp_info = &p_hwfn->p_rdma_info->iwarp;

	iwarp_info->tcp_flags = QED_IWARP_TS_EN;

	chip_id = QED_IS_BB(cdev) ? CHIP_BB : CHIP_K2;
	rcv_wnd_size = (qed_device_num_ports(cdev) == 4) ?
		qed_iwarp_rcv_wnd_size[chip_id].four_ports :
		qed_iwarp_rcv_wnd_size[chip_id].two_ports;

	/* value 0 is used क्रम ilog2(QED_IWARP_RCV_WND_SIZE_MIN) */
	iwarp_info->rcv_wnd_scale = ilog2(rcv_wnd_size) -
	    ilog2(QED_IWARP_RCV_WND_SIZE_MIN);
	iwarp_info->rcv_wnd_size = rcv_wnd_size >> iwarp_info->rcv_wnd_scale;
	iwarp_info->crc_needed = QED_IWARP_PARAM_CRC_NEEDED;
	iwarp_info->mpa_rev = MPA_NEGOTIATION_TYPE_ENHANCED;

	iwarp_info->peer2peer = QED_IWARP_PARAM_P2P;

	iwarp_info->rtr_type =  MPA_RTR_TYPE_ZERO_SEND |
				MPA_RTR_TYPE_ZERO_WRITE |
				MPA_RTR_TYPE_ZERO_READ;

	spin_lock_init(&p_hwfn->p_rdma_info->iwarp.qp_lock);
	INIT_LIST_HEAD(&p_hwfn->p_rdma_info->iwarp.ep_list);
	INIT_LIST_HEAD(&p_hwfn->p_rdma_info->iwarp.listen_list);

	qed_spq_रेजिस्टर_async_cb(p_hwfn, PROTOCOLID_IWARP,
				  qed_iwarp_async_event);
	qed_ooo_setup(p_hwfn);

	वापस qed_iwarp_ll2_start(p_hwfn, params, rcv_wnd_size);
पूर्ण

पूर्णांक qed_iwarp_stop(काष्ठा qed_hwfn *p_hwfn)
अणु
	पूर्णांक rc;

	qed_iwarp_मुक्त_pपुनः_स्मृति_ep(p_hwfn);
	rc = qed_iwarp_रुको_क्रम_all_cids(p_hwfn);
	अगर (rc)
		वापस rc;

	वापस qed_iwarp_ll2_stop(p_hwfn);
पूर्ण

अटल व्योम qed_iwarp_qp_in_error(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_iwarp_ep *ep,
				  u8 fw_वापस_code)
अणु
	काष्ठा qed_iwarp_cm_event_params params;

	qed_iwarp_modअगरy_qp(p_hwfn, ep->qp, QED_IWARP_QP_STATE_ERROR, true);

	params.event = QED_IWARP_EVENT_CLOSE;
	params.ep_context = ep;
	params.cm_info = &ep->cm_info;
	params.status = (fw_वापस_code == IWARP_QP_IN_ERROR_GOOD_CLOSE) ?
			 0 : -ECONNRESET;

	/* paired with READ_ONCE in destroy_qp */
	smp_store_release(&ep->state, QED_IWARP_EP_CLOSED);

	spin_lock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);
	list_del(&ep->list_entry);
	spin_unlock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);

	ep->event_cb(ep->cb_context, &params);
पूर्ण

अटल व्योम qed_iwarp_exception_received(काष्ठा qed_hwfn *p_hwfn,
					 काष्ठा qed_iwarp_ep *ep,
					 पूर्णांक fw_ret_code)
अणु
	काष्ठा qed_iwarp_cm_event_params params;
	bool event_cb = false;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "EP(0x%x) fw_ret_code=%d\n",
		   ep->cid, fw_ret_code);

	चयन (fw_ret_code) अणु
	हाल IWARP_EXCEPTION_DETECTED_LLP_CLOSED:
		params.status = 0;
		params.event = QED_IWARP_EVENT_DISCONNECT;
		event_cb = true;
		अवरोध;
	हाल IWARP_EXCEPTION_DETECTED_LLP_RESET:
		params.status = -ECONNRESET;
		params.event = QED_IWARP_EVENT_DISCONNECT;
		event_cb = true;
		अवरोध;
	हाल IWARP_EXCEPTION_DETECTED_RQ_EMPTY:
		params.event = QED_IWARP_EVENT_RQ_EMPTY;
		event_cb = true;
		अवरोध;
	हाल IWARP_EXCEPTION_DETECTED_IRQ_FULL:
		params.event = QED_IWARP_EVENT_IRQ_FULL;
		event_cb = true;
		अवरोध;
	हाल IWARP_EXCEPTION_DETECTED_LLP_TIMEOUT:
		params.event = QED_IWARP_EVENT_LLP_TIMEOUT;
		event_cb = true;
		अवरोध;
	हाल IWARP_EXCEPTION_DETECTED_REMOTE_PROTECTION_ERROR:
		params.event = QED_IWARP_EVENT_REMOTE_PROTECTION_ERROR;
		event_cb = true;
		अवरोध;
	हाल IWARP_EXCEPTION_DETECTED_CQ_OVERFLOW:
		params.event = QED_IWARP_EVENT_CQ_OVERFLOW;
		event_cb = true;
		अवरोध;
	हाल IWARP_EXCEPTION_DETECTED_LOCAL_CATASTROPHIC:
		params.event = QED_IWARP_EVENT_QP_CATASTROPHIC;
		event_cb = true;
		अवरोध;
	हाल IWARP_EXCEPTION_DETECTED_LOCAL_ACCESS_ERROR:
		params.event = QED_IWARP_EVENT_LOCAL_ACCESS_ERROR;
		event_cb = true;
		अवरोध;
	हाल IWARP_EXCEPTION_DETECTED_REMOTE_OPERATION_ERROR:
		params.event = QED_IWARP_EVENT_REMOTE_OPERATION_ERROR;
		event_cb = true;
		अवरोध;
	हाल IWARP_EXCEPTION_DETECTED_TERMINATE_RECEIVED:
		params.event = QED_IWARP_EVENT_TERMINATE_RECEIVED;
		event_cb = true;
		अवरोध;
	शेष:
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "Unhandled exception received...fw_ret_code=%d\n",
			   fw_ret_code);
		अवरोध;
	पूर्ण

	अगर (event_cb) अणु
		params.ep_context = ep;
		params.cm_info = &ep->cm_info;
		ep->event_cb(ep->cb_context, &params);
	पूर्ण
पूर्ण

अटल व्योम
qed_iwarp_tcp_connect_unsuccessful(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_iwarp_ep *ep, u8 fw_वापस_code)
अणु
	काष्ठा qed_iwarp_cm_event_params params;

	स_रखो(&params, 0, माप(params));
	params.event = QED_IWARP_EVENT_ACTIVE_COMPLETE;
	params.ep_context = ep;
	params.cm_info = &ep->cm_info;
	/* paired with READ_ONCE in destroy_qp */
	smp_store_release(&ep->state, QED_IWARP_EP_CLOSED);

	चयन (fw_वापस_code) अणु
	हाल IWARP_CONN_ERROR_TCP_CONNECT_INVALID_PACKET:
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "%s(0x%x) TCP connect got invalid packet\n",
			   QED_IWARP_CONNECT_MODE_STRING(ep), ep->tcp_cid);
		params.status = -ECONNRESET;
		अवरोध;
	हाल IWARP_CONN_ERROR_TCP_CONNECTION_RST:
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "%s(0x%x) TCP Connection Reset\n",
			   QED_IWARP_CONNECT_MODE_STRING(ep), ep->tcp_cid);
		params.status = -ECONNRESET;
		अवरोध;
	हाल IWARP_CONN_ERROR_TCP_CONNECT_TIMEOUT:
		DP_NOTICE(p_hwfn, "%s(0x%x) TCP timeout\n",
			  QED_IWARP_CONNECT_MODE_STRING(ep), ep->tcp_cid);
		params.status = -EBUSY;
		अवरोध;
	हाल IWARP_CONN_ERROR_MPA_NOT_SUPPORTED_VER:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA not supported VER\n",
			  QED_IWARP_CONNECT_MODE_STRING(ep), ep->tcp_cid);
		params.status = -ECONNREFUSED;
		अवरोध;
	हाल IWARP_CONN_ERROR_MPA_INVALID_PACKET:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA Invalid Packet\n",
			  QED_IWARP_CONNECT_MODE_STRING(ep), ep->tcp_cid);
		params.status = -ECONNRESET;
		अवरोध;
	शेष:
		DP_ERR(p_hwfn,
		       "%s(0x%x) Unexpected return code tcp connect: %d\n",
		       QED_IWARP_CONNECT_MODE_STRING(ep),
		       ep->tcp_cid, fw_वापस_code);
		params.status = -ECONNRESET;
		अवरोध;
	पूर्ण

	अगर (ep->connect_mode == TCP_CONNECT_PASSIVE) अणु
		ep->tcp_cid = QED_IWARP_INVALID_TCP_CID;
		qed_iwarp_वापस_ep(p_hwfn, ep);
	पूर्ण अन्यथा अणु
		ep->event_cb(ep->cb_context, &params);
		spin_lock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);
		list_del(&ep->list_entry);
		spin_unlock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);
	पूर्ण
पूर्ण

अटल व्योम
qed_iwarp_connect_complete(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_iwarp_ep *ep, u8 fw_वापस_code)
अणु
	u8 ll2_syn_handle = p_hwfn->p_rdma_info->iwarp.ll2_syn_handle;

	अगर (ep->connect_mode == TCP_CONNECT_PASSIVE) अणु
		/* Done with the SYN packet, post back to ll2 rx */
		qed_iwarp_ll2_post_rx(p_hwfn, ep->syn, ll2_syn_handle);

		ep->syn = शून्य;

		/* If connect failed - upper layer करोesn't know about it */
		अगर (fw_वापस_code == RDMA_RETURN_OK)
			qed_iwarp_mpa_received(p_hwfn, ep);
		अन्यथा
			qed_iwarp_tcp_connect_unsuccessful(p_hwfn, ep,
							   fw_वापस_code);
	पूर्ण अन्यथा अणु
		अगर (fw_वापस_code == RDMA_RETURN_OK)
			qed_iwarp_mpa_offload(p_hwfn, ep);
		अन्यथा
			qed_iwarp_tcp_connect_unsuccessful(p_hwfn, ep,
							   fw_वापस_code);
	पूर्ण
पूर्ण

अटल अंतरभूत bool
qed_iwarp_check_ep_ok(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_iwarp_ep *ep)
अणु
	अगर (!ep || (ep->sig != QED_EP_SIG)) अणु
		DP_ERR(p_hwfn, "ERROR ON ASYNC ep=%p\n", ep);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक qed_iwarp_async_event(काष्ठा qed_hwfn *p_hwfn, u8 fw_event_code,
				 __le16 echo, जोड़ event_ring_data *data,
				 u8 fw_वापस_code)
अणु
	काष्ठा qed_rdma_events events = p_hwfn->p_rdma_info->events;
	काष्ठा regpair *fw_handle = &data->rdma_data.async_handle;
	काष्ठा qed_iwarp_ep *ep = शून्य;
	u16 srq_offset;
	u16 srq_id;
	u16 cid;

	ep = (काष्ठा qed_iwarp_ep *)(uपूर्णांकptr_t)HILO_64(fw_handle->hi,
						       fw_handle->lo);

	चयन (fw_event_code) अणु
	हाल IWARP_EVENT_TYPE_ASYNC_CONNECT_COMPLETE:
		/* Async completion after TCP 3-way handshake */
		अगर (!qed_iwarp_check_ep_ok(p_hwfn, ep))
			वापस -EINVAL;
		DP_VERBOSE(p_hwfn,
			   QED_MSG_RDMA,
			   "EP(0x%x) IWARP_EVENT_TYPE_ASYNC_CONNECT_COMPLETE fw_ret_code=%d\n",
			   ep->tcp_cid, fw_वापस_code);
		qed_iwarp_connect_complete(p_hwfn, ep, fw_वापस_code);
		अवरोध;
	हाल IWARP_EVENT_TYPE_ASYNC_EXCEPTION_DETECTED:
		अगर (!qed_iwarp_check_ep_ok(p_hwfn, ep))
			वापस -EINVAL;
		DP_VERBOSE(p_hwfn,
			   QED_MSG_RDMA,
			   "QP(0x%x) IWARP_EVENT_TYPE_ASYNC_EXCEPTION_DETECTED fw_ret_code=%d\n",
			   ep->cid, fw_वापस_code);
		qed_iwarp_exception_received(p_hwfn, ep, fw_वापस_code);
		अवरोध;
	हाल IWARP_EVENT_TYPE_ASYNC_QP_IN_ERROR_STATE:
		/* Async completion क्रम Close Connection ramrod */
		अगर (!qed_iwarp_check_ep_ok(p_hwfn, ep))
			वापस -EINVAL;
		DP_VERBOSE(p_hwfn,
			   QED_MSG_RDMA,
			   "QP(0x%x) IWARP_EVENT_TYPE_ASYNC_QP_IN_ERROR_STATE fw_ret_code=%d\n",
			   ep->cid, fw_वापस_code);
		qed_iwarp_qp_in_error(p_hwfn, ep, fw_वापस_code);
		अवरोध;
	हाल IWARP_EVENT_TYPE_ASYNC_ENHANCED_MPA_REPLY_ARRIVED:
		/* Async event क्रम active side only */
		अगर (!qed_iwarp_check_ep_ok(p_hwfn, ep))
			वापस -EINVAL;
		DP_VERBOSE(p_hwfn,
			   QED_MSG_RDMA,
			   "QP(0x%x) IWARP_EVENT_TYPE_ASYNC_MPA_HANDSHAKE_MPA_REPLY_ARRIVED fw_ret_code=%d\n",
			   ep->cid, fw_वापस_code);
		qed_iwarp_mpa_reply_arrived(p_hwfn, ep);
		अवरोध;
	हाल IWARP_EVENT_TYPE_ASYNC_MPA_HANDSHAKE_COMPLETE:
		अगर (!qed_iwarp_check_ep_ok(p_hwfn, ep))
			वापस -EINVAL;
		DP_VERBOSE(p_hwfn,
			   QED_MSG_RDMA,
			   "QP(0x%x) IWARP_EVENT_TYPE_ASYNC_MPA_HANDSHAKE_COMPLETE fw_ret_code=%d\n",
			   ep->cid, fw_वापस_code);
		qed_iwarp_mpa_complete(p_hwfn, ep, fw_वापस_code);
		अवरोध;
	हाल IWARP_EVENT_TYPE_ASYNC_CID_CLEANED:
		cid = (u16)le32_to_cpu(fw_handle->lo);
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "(0x%x)IWARP_EVENT_TYPE_ASYNC_CID_CLEANED\n", cid);
		qed_iwarp_cid_cleaned(p_hwfn, cid);

		अवरोध;
	हाल IWARP_EVENT_TYPE_ASYNC_SRQ_EMPTY:
		DP_NOTICE(p_hwfn, "IWARP_EVENT_TYPE_ASYNC_SRQ_EMPTY\n");
		srq_offset = p_hwfn->p_rdma_info->srq_id_offset;
		/* FW assigns value that is no greater than u16 */
		srq_id = ((u16)le32_to_cpu(fw_handle->lo)) - srq_offset;
		events.affiliated_event(events.context,
					QED_IWARP_EVENT_SRQ_EMPTY,
					&srq_id);
		अवरोध;
	हाल IWARP_EVENT_TYPE_ASYNC_SRQ_LIMIT:
		DP_NOTICE(p_hwfn, "IWARP_EVENT_TYPE_ASYNC_SRQ_LIMIT\n");
		srq_offset = p_hwfn->p_rdma_info->srq_id_offset;
		/* FW assigns value that is no greater than u16 */
		srq_id = ((u16)le32_to_cpu(fw_handle->lo)) - srq_offset;
		events.affiliated_event(events.context,
					QED_IWARP_EVENT_SRQ_LIMIT,
					&srq_id);
		अवरोध;
	हाल IWARP_EVENT_TYPE_ASYNC_CQ_OVERFLOW:
		DP_NOTICE(p_hwfn, "IWARP_EVENT_TYPE_ASYNC_CQ_OVERFLOW\n");

		p_hwfn->p_rdma_info->events.affiliated_event(
			p_hwfn->p_rdma_info->events.context,
			QED_IWARP_EVENT_CQ_OVERFLOW,
			(व्योम *)fw_handle);
		अवरोध;
	शेष:
		DP_ERR(p_hwfn, "Received unexpected async iwarp event %d\n",
		       fw_event_code);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
qed_iwarp_create_listen(व्योम *rdma_cxt,
			काष्ठा qed_iwarp_listen_in *iparams,
			काष्ठा qed_iwarp_listen_out *oparams)
अणु
	काष्ठा qed_hwfn *p_hwfn = rdma_cxt;
	काष्ठा qed_iwarp_listener *listener;

	listener = kzalloc(माप(*listener), GFP_KERNEL);
	अगर (!listener)
		वापस -ENOMEM;

	listener->ip_version = iparams->ip_version;
	स_नकल(listener->ip_addr, iparams->ip_addr, माप(listener->ip_addr));
	listener->port = iparams->port;
	listener->vlan = iparams->vlan;

	listener->event_cb = iparams->event_cb;
	listener->cb_context = iparams->cb_context;
	listener->max_backlog = iparams->max_backlog;
	oparams->handle = listener;

	spin_lock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);
	list_add_tail(&listener->list_entry,
		      &p_hwfn->p_rdma_info->iwarp.listen_list);
	spin_unlock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);

	DP_VERBOSE(p_hwfn,
		   QED_MSG_RDMA,
		   "callback=%p handle=%p ip=%x:%x:%x:%x port=0x%x vlan=0x%x\n",
		   listener->event_cb,
		   listener,
		   listener->ip_addr[0],
		   listener->ip_addr[1],
		   listener->ip_addr[2],
		   listener->ip_addr[3], listener->port, listener->vlan);

	वापस 0;
पूर्ण

पूर्णांक qed_iwarp_destroy_listen(व्योम *rdma_cxt, व्योम *handle)
अणु
	काष्ठा qed_iwarp_listener *listener = handle;
	काष्ठा qed_hwfn *p_hwfn = rdma_cxt;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "handle=%p\n", handle);

	spin_lock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);
	list_del(&listener->list_entry);
	spin_unlock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);

	kमुक्त(listener);

	वापस 0;
पूर्ण

पूर्णांक qed_iwarp_send_rtr(व्योम *rdma_cxt, काष्ठा qed_iwarp_send_rtr_in *iparams)
अणु
	काष्ठा qed_hwfn *p_hwfn = rdma_cxt;
	काष्ठा qed_sp_init_data init_data;
	काष्ठा qed_spq_entry *p_ent;
	काष्ठा qed_iwarp_ep *ep;
	काष्ठा qed_rdma_qp *qp;
	पूर्णांक rc;

	ep = iparams->ep_context;
	अगर (!ep) अणु
		DP_ERR(p_hwfn, "Ep Context receive in send_rtr is NULL\n");
		वापस -EINVAL;
	पूर्ण

	qp = ep->qp;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "QP(0x%x) EP(0x%x)\n",
		   qp->icid, ep->tcp_cid);

	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_CB;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 IWARP_RAMROD_CMD_ID_MPA_OFFLOAD_SEND_RTR,
				 PROTOCOLID_IWARP, &init_data);

	अगर (rc)
		वापस rc;

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "rc = 0x%x\n", rc);

	वापस rc;
पूर्ण

व्योम
qed_iwarp_query_qp(काष्ठा qed_rdma_qp *qp,
		   काष्ठा qed_rdma_query_qp_out_params *out_params)
अणु
	out_params->state = qed_iwarp2roce_state(qp->iwarp_state);
पूर्ण
