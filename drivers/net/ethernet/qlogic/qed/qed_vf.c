<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/crc32.h>
#समावेश <linux/etherdevice.h>
#समावेश "qed.h"
#समावेश "qed_sriov.h"
#समावेश "qed_vf.h"

अटल व्योम *qed_vf_pf_prep(काष्ठा qed_hwfn *p_hwfn, u16 type, u16 length)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	व्योम *p_tlv;

	/* This lock is released when we receive PF's response
	 * in qed_send_msg2pf().
	 * So, qed_vf_pf_prep() and qed_send_msg2pf()
	 * must come in sequence.
	 */
	mutex_lock(&(p_iov->mutex));

	DP_VERBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "preparing to send 0x%04x tlv over vf pf channel\n",
		   type);

	/* Reset Requst offset */
	p_iov->offset = (u8 *)p_iov->vf2pf_request;

	/* Clear mailbox - both request and reply */
	स_रखो(p_iov->vf2pf_request, 0, माप(जोड़ vfpf_tlvs));
	स_रखो(p_iov->pf2vf_reply, 0, माप(जोड़ pfvf_tlvs));

	/* Init type and length */
	p_tlv = qed_add_tlv(p_hwfn, &p_iov->offset, type, length);

	/* Init first tlv header */
	((काष्ठा vfpf_first_tlv *)p_tlv)->reply_address =
	    (u64)p_iov->pf2vf_reply_phys;

	वापस p_tlv;
पूर्ण

अटल व्योम qed_vf_pf_req_end(काष्ठा qed_hwfn *p_hwfn, पूर्णांक req_status)
अणु
	जोड़ pfvf_tlvs *resp = p_hwfn->vf_iov_info->pf2vf_reply;

	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "VF request status = 0x%x, PF reply status = 0x%x\n",
		   req_status, resp->शेष_resp.hdr.status);

	mutex_unlock(&(p_hwfn->vf_iov_info->mutex));
पूर्ण

#घोषणा QED_VF_CHANNEL_USLEEP_ITERATIONS	90
#घोषणा QED_VF_CHANNEL_USLEEP_DELAY		100
#घोषणा QED_VF_CHANNEL_MSLEEP_ITERATIONS	10
#घोषणा QED_VF_CHANNEL_MSLEEP_DELAY		25

अटल पूर्णांक qed_send_msg2pf(काष्ठा qed_hwfn *p_hwfn, u8 *करोne, u32 resp_size)
अणु
	जोड़ vfpf_tlvs *p_req = p_hwfn->vf_iov_info->vf2pf_request;
	काष्ठा ustorm_trigger_vf_zone trigger;
	काष्ठा ustorm_vf_zone *zone_data;
	पूर्णांक iter, rc = 0;

	zone_data = (काष्ठा ustorm_vf_zone *)PXP_VF_BAR0_START_USDM_ZONE_B;

	/* output tlvs list */
	qed_dp_tlv_list(p_hwfn, p_req);

	/* need to add the END TLV to the message size */
	resp_size += माप(काष्ठा channel_list_end_tlv);

	/* Send TLVs over HW channel */
	स_रखो(&trigger, 0, माप(काष्ठा ustorm_trigger_vf_zone));
	trigger.vf_pf_msg_valid = 1;

	DP_VERBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "VF -> PF [%02x] message: [%08x, %08x] --> %p, %08x --> %p\n",
		   GET_FIELD(p_hwfn->hw_info.concrete_fid,
			     PXP_CONCRETE_FID_PFID),
		   upper_32_bits(p_hwfn->vf_iov_info->vf2pf_request_phys),
		   lower_32_bits(p_hwfn->vf_iov_info->vf2pf_request_phys),
		   &zone_data->non_trigger.vf_pf_msg_addr,
		   *((u32 *)&trigger), &zone_data->trigger);

	REG_WR(p_hwfn,
	       (uपूर्णांकptr_t)&zone_data->non_trigger.vf_pf_msg_addr.lo,
	       lower_32_bits(p_hwfn->vf_iov_info->vf2pf_request_phys));

	REG_WR(p_hwfn,
	       (uपूर्णांकptr_t)&zone_data->non_trigger.vf_pf_msg_addr.hi,
	       upper_32_bits(p_hwfn->vf_iov_info->vf2pf_request_phys));

	/* The message data must be written first, to prevent trigger beक्रमe
	 * data is written.
	 */
	wmb();

	REG_WR(p_hwfn, (uपूर्णांकptr_t)&zone_data->trigger, *((u32 *)&trigger));

	/* When PF would be करोne with the response, it would ग_लिखो back to the
	 * `करोne' address from a coherent DMA zone. Poll until then.
	 */

	iter = QED_VF_CHANNEL_USLEEP_ITERATIONS;
	जबतक (!*करोne && iter--) अणु
		udelay(QED_VF_CHANNEL_USLEEP_DELAY);
		dma_rmb();
	पूर्ण

	iter = QED_VF_CHANNEL_MSLEEP_ITERATIONS;
	जबतक (!*करोne && iter--) अणु
		msleep(QED_VF_CHANNEL_MSLEEP_DELAY);
		dma_rmb();
	पूर्ण

	अगर (!*करोne) अणु
		DP_NOTICE(p_hwfn,
			  "VF <-- PF Timeout [Type %d]\n",
			  p_req->first_tlv.tl.type);
		rc = -EBUSY;
	पूर्ण अन्यथा अणु
		अगर ((*करोne != PFVF_STATUS_SUCCESS) &&
		    (*करोne != PFVF_STATUS_NO_RESOURCE))
			DP_NOTICE(p_hwfn,
				  "PF response: %d [Type %d]\n",
				  *करोne, p_req->first_tlv.tl.type);
		अन्यथा
			DP_VERBOSE(p_hwfn, QED_MSG_IOV,
				   "PF response: %d [Type %d]\n",
				   *करोne, p_req->first_tlv.tl.type);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम qed_vf_pf_add_qid(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_queue_cid *p_cid)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	काष्ठा vfpf_qid_tlv *p_qid_tlv;

	/* Only add QIDs क्रम the queue अगर it was negotiated with PF */
	अगर (!(p_iov->acquire_resp.pfdev_info.capabilities &
	      PFVF_ACQUIRE_CAP_QUEUE_QIDS))
		वापस;

	p_qid_tlv = qed_add_tlv(p_hwfn, &p_iov->offset,
				CHANNEL_TLV_QID, माप(*p_qid_tlv));
	p_qid_tlv->qid = p_cid->qid_usage_idx;
पूर्ण

अटल पूर्णांक _qed_vf_pf_release(काष्ठा qed_hwfn *p_hwfn, bool b_final)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	काष्ठा pfvf_def_resp_tlv *resp;
	काष्ठा vfpf_first_tlv *req;
	u32 size;
	पूर्णांक rc;

	/* clear mailbox and prep first tlv */
	req = qed_vf_pf_prep(p_hwfn, CHANNEL_TLV_RELEASE, माप(*req));

	/* add list termination tlv */
	qed_add_tlv(p_hwfn, &p_iov->offset,
		    CHANNEL_TLV_LIST_END, माप(काष्ठा channel_list_end_tlv));

	resp = &p_iov->pf2vf_reply->शेष_resp;
	rc = qed_send_msg2pf(p_hwfn, &resp->hdr.status, माप(*resp));

	अगर (!rc && resp->hdr.status != PFVF_STATUS_SUCCESS)
		rc = -EAGAIN;

	qed_vf_pf_req_end(p_hwfn, rc);
	अगर (!b_final)
		वापस rc;

	p_hwfn->b_पूर्णांक_enabled = 0;

	अगर (p_iov->vf2pf_request)
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  माप(जोड़ vfpf_tlvs),
				  p_iov->vf2pf_request,
				  p_iov->vf2pf_request_phys);
	अगर (p_iov->pf2vf_reply)
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  माप(जोड़ pfvf_tlvs),
				  p_iov->pf2vf_reply, p_iov->pf2vf_reply_phys);

	अगर (p_iov->bulletin.p_virt) अणु
		size = माप(काष्ठा qed_bulletin_content);
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  size,
				  p_iov->bulletin.p_virt, p_iov->bulletin.phys);
	पूर्ण

	kमुक्त(p_hwfn->vf_iov_info);
	p_hwfn->vf_iov_info = शून्य;

	वापस rc;
पूर्ण

पूर्णांक qed_vf_pf_release(काष्ठा qed_hwfn *p_hwfn)
अणु
	वापस _qed_vf_pf_release(p_hwfn, true);
पूर्ण

#घोषणा VF_ACQUIRE_THRESH 3
अटल व्योम qed_vf_pf_acquire_reduce_resc(काष्ठा qed_hwfn *p_hwfn,
					  काष्ठा vf_pf_resc_request *p_req,
					  काष्ठा pf_vf_resc *p_resp)
अणु
	DP_VERBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "PF unwilling to fulfill resource request: rxq [%02x/%02x] txq [%02x/%02x] sbs [%02x/%02x] mac [%02x/%02x] vlan [%02x/%02x] mc [%02x/%02x] cids [%02x/%02x]. Try PF recommended amount\n",
		   p_req->num_rxqs,
		   p_resp->num_rxqs,
		   p_req->num_rxqs,
		   p_resp->num_txqs,
		   p_req->num_sbs,
		   p_resp->num_sbs,
		   p_req->num_mac_filters,
		   p_resp->num_mac_filters,
		   p_req->num_vlan_filters,
		   p_resp->num_vlan_filters,
		   p_req->num_mc_filters,
		   p_resp->num_mc_filters, p_req->num_cids, p_resp->num_cids);

	/* humble our request */
	p_req->num_txqs = p_resp->num_txqs;
	p_req->num_rxqs = p_resp->num_rxqs;
	p_req->num_sbs = p_resp->num_sbs;
	p_req->num_mac_filters = p_resp->num_mac_filters;
	p_req->num_vlan_filters = p_resp->num_vlan_filters;
	p_req->num_mc_filters = p_resp->num_mc_filters;
	p_req->num_cids = p_resp->num_cids;
पूर्ण

अटल पूर्णांक qed_vf_pf_acquire(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	काष्ठा pfvf_acquire_resp_tlv *resp = &p_iov->pf2vf_reply->acquire_resp;
	काष्ठा pf_vf_pfdev_info *pfdev_info = &resp->pfdev_info;
	काष्ठा vf_pf_resc_request *p_resc;
	u8 retry_cnt = VF_ACQUIRE_THRESH;
	bool resources_acquired = false;
	काष्ठा vfpf_acquire_tlv *req;
	पूर्णांक rc = 0, attempts = 0;

	/* clear mailbox and prep first tlv */
	req = qed_vf_pf_prep(p_hwfn, CHANNEL_TLV_ACQUIRE, माप(*req));
	p_resc = &req->resc_request;

	/* starting filling the request */
	req->vfdev_info.opaque_fid = p_hwfn->hw_info.opaque_fid;

	p_resc->num_rxqs = QED_MAX_VF_CHAINS_PER_PF;
	p_resc->num_txqs = QED_MAX_VF_CHAINS_PER_PF;
	p_resc->num_sbs = QED_MAX_VF_CHAINS_PER_PF;
	p_resc->num_mac_filters = QED_ETH_VF_NUM_MAC_FILTERS;
	p_resc->num_vlan_filters = QED_ETH_VF_NUM_VLAN_FILTERS;
	p_resc->num_cids = QED_ETH_VF_DEFAULT_NUM_CIDS;

	req->vfdev_info.os_type = VFPF_ACQUIRE_OS_LINUX;
	req->vfdev_info.fw_major = FW_MAJOR_VERSION;
	req->vfdev_info.fw_minor = FW_MINOR_VERSION;
	req->vfdev_info.fw_revision = FW_REVISION_VERSION;
	req->vfdev_info.fw_engineering = FW_ENGINEERING_VERSION;
	req->vfdev_info.eth_fp_hsi_major = ETH_HSI_VER_MAJOR;
	req->vfdev_info.eth_fp_hsi_minor = ETH_HSI_VER_MINOR;

	/* Fill capability field with any non-deprecated config we support */
	req->vfdev_info.capabilities |= VFPF_ACQUIRE_CAP_100G;

	/* If we've mapped the करोorbell bar, try using queue qids */
	अगर (p_iov->b_करोorbell_bar) अणु
		req->vfdev_info.capabilities |= VFPF_ACQUIRE_CAP_PHYSICAL_BAR |
						VFPF_ACQUIRE_CAP_QUEUE_QIDS;
		p_resc->num_cids = QED_ETH_VF_MAX_NUM_CIDS;
	पूर्ण

	/* pf 2 vf bulletin board address */
	req->bulletin_addr = p_iov->bulletin.phys;
	req->bulletin_size = p_iov->bulletin.size;

	/* add list termination tlv */
	qed_add_tlv(p_hwfn, &p_iov->offset,
		    CHANNEL_TLV_LIST_END, माप(काष्ठा channel_list_end_tlv));

	जबतक (!resources_acquired) अणु
		DP_VERBOSE(p_hwfn,
			   QED_MSG_IOV, "attempting to acquire resources\n");

		/* Clear response buffer, as this might be a re-send */
		स_रखो(p_iov->pf2vf_reply, 0, माप(जोड़ pfvf_tlvs));

		/* send acquire request */
		rc = qed_send_msg2pf(p_hwfn, &resp->hdr.status, माप(*resp));

		/* Re-try acquire in हाल of vf-pf hw channel समयout */
		अगर (retry_cnt && rc == -EBUSY) अणु
			DP_VERBOSE(p_hwfn, QED_MSG_IOV,
				   "VF retrying to acquire due to VPC timeout\n");
			retry_cnt--;
			जारी;
		पूर्ण

		अगर (rc)
			जाओ निकास;

		/* copy acquire response from buffer to p_hwfn */
		स_नकल(&p_iov->acquire_resp, resp, माप(p_iov->acquire_resp));

		attempts++;

		अगर (resp->hdr.status == PFVF_STATUS_SUCCESS) अणु
			/* PF agrees to allocate our resources */
			अगर (!(resp->pfdev_info.capabilities &
			      PFVF_ACQUIRE_CAP_POST_FW_OVERRIDE)) अणु
				/* It's possible legacy PF mistakenly accepted;
				 * but we करोn't care - simply mark it as
				 * legacy and जारी.
				 */
				req->vfdev_info.capabilities |=
				    VFPF_ACQUIRE_CAP_PRE_FP_HSI;
			पूर्ण
			DP_VERBOSE(p_hwfn, QED_MSG_IOV, "resources acquired\n");
			resources_acquired = true;
		पूर्ण अन्यथा अगर (resp->hdr.status == PFVF_STATUS_NO_RESOURCE &&
			   attempts < VF_ACQUIRE_THRESH) अणु
			qed_vf_pf_acquire_reduce_resc(p_hwfn, p_resc,
						      &resp->resc);
		पूर्ण अन्यथा अगर (resp->hdr.status == PFVF_STATUS_NOT_SUPPORTED) अणु
			अगर (pfdev_info->major_fp_hsi &&
			    (pfdev_info->major_fp_hsi != ETH_HSI_VER_MAJOR)) अणु
				DP_NOTICE(p_hwfn,
					  "PF uses an incompatible fastpath HSI %02x.%02x [VF requires %02x.%02x]. Please change to a VF driver using %02x.xx.\n",
					  pfdev_info->major_fp_hsi,
					  pfdev_info->minor_fp_hsi,
					  ETH_HSI_VER_MAJOR,
					  ETH_HSI_VER_MINOR,
					  pfdev_info->major_fp_hsi);
				rc = -EINVAL;
				जाओ निकास;
			पूर्ण

			अगर (!pfdev_info->major_fp_hsi) अणु
				अगर (req->vfdev_info.capabilities &
				    VFPF_ACQUIRE_CAP_PRE_FP_HSI) अणु
					DP_NOTICE(p_hwfn,
						  "PF uses very old drivers. Please change to a VF driver using no later than 8.8.x.x.\n");
					rc = -EINVAL;
					जाओ निकास;
				पूर्ण अन्यथा अणु
					DP_INFO(p_hwfn,
						"PF is old - try re-acquire to see if it supports FW-version override\n");
					req->vfdev_info.capabilities |=
					    VFPF_ACQUIRE_CAP_PRE_FP_HSI;
					जारी;
				पूर्ण
			पूर्ण

			/* If PF/VF are using same Major, PF must have had
			 * it's reasons. Simply fail.
			 */
			DP_NOTICE(p_hwfn, "PF rejected acquisition by VF\n");
			rc = -EINVAL;
			जाओ निकास;
		पूर्ण अन्यथा अणु
			DP_ERR(p_hwfn,
			       "PF returned error %d to VF acquisition request\n",
			       resp->hdr.status);
			rc = -EAGAIN;
			जाओ निकास;
		पूर्ण
	पूर्ण

	/* Mark the PF as legacy, अगर needed */
	अगर (req->vfdev_info.capabilities & VFPF_ACQUIRE_CAP_PRE_FP_HSI)
		p_iov->b_pre_fp_hsi = true;

	/* In हाल PF करोesn't support multi-queue Tx, update the number of
	 * CIDs to reflect the number of queues [older PFs didn't fill that
	 * field].
	 */
	अगर (!(resp->pfdev_info.capabilities & PFVF_ACQUIRE_CAP_QUEUE_QIDS))
		resp->resc.num_cids = resp->resc.num_rxqs + resp->resc.num_txqs;

	/* Update bulletin board size with response from PF */
	p_iov->bulletin.size = resp->bulletin_size;

	/* get HW info */
	p_hwfn->cdev->type = resp->pfdev_info.dev_type;
	p_hwfn->cdev->chip_rev = resp->pfdev_info.chip_rev;

	p_hwfn->cdev->chip_num = pfdev_info->chip_num & 0xffff;

	/* Learn of the possibility of CMT */
	अगर (IS_LEAD_HWFN(p_hwfn)) अणु
		अगर (resp->pfdev_info.capabilities & PFVF_ACQUIRE_CAP_100G) अणु
			DP_NOTICE(p_hwfn, "100g VF\n");
			p_hwfn->cdev->num_hwfns = 2;
		पूर्ण
	पूर्ण

	अगर (!p_iov->b_pre_fp_hsi &&
	    (resp->pfdev_info.minor_fp_hsi < ETH_HSI_VER_MINOR)) अणु
		DP_INFO(p_hwfn,
			"PF is using older fastpath HSI; %02x.%02x is configured\n",
			ETH_HSI_VER_MAJOR, resp->pfdev_info.minor_fp_hsi);
	पूर्ण

निकास:
	qed_vf_pf_req_end(p_hwfn, rc);

	वापस rc;
पूर्ण

u32 qed_vf_hw_bar_size(काष्ठा qed_hwfn *p_hwfn, क्रमागत BAR_ID bar_id)
अणु
	u32 bar_size;

	/* Regview size is fixed */
	अगर (bar_id == BAR_ID_0)
		वापस 1 << 17;

	/* Doorbell is received from PF */
	bar_size = p_hwfn->vf_iov_info->acquire_resp.pfdev_info.bar_size;
	अगर (bar_size)
		वापस 1 << bar_size;
	वापस 0;
पूर्ण

पूर्णांक qed_vf_hw_prepare(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_hwfn *p_lead = QED_LEADING_HWFN(p_hwfn->cdev);
	काष्ठा qed_vf_iov *p_iov;
	u32 reg;
	पूर्णांक rc;

	/* Set number of hwfns - might be overriden once leading hwfn learns
	 * actual configuration from PF.
	 */
	अगर (IS_LEAD_HWFN(p_hwfn))
		p_hwfn->cdev->num_hwfns = 1;

	reg = PXP_VF_BAR0_ME_OPAQUE_ADDRESS;
	p_hwfn->hw_info.opaque_fid = (u16)REG_RD(p_hwfn, reg);

	reg = PXP_VF_BAR0_ME_CONCRETE_ADDRESS;
	p_hwfn->hw_info.concrete_fid = REG_RD(p_hwfn, reg);

	/* Allocate vf sriov info */
	p_iov = kzalloc(माप(*p_iov), GFP_KERNEL);
	अगर (!p_iov)
		वापस -ENOMEM;

	/* Doorbells are tricky; Upper-layer has alreday set the hwfn करोorbell
	 * value, but there are several incompatibily scenarios where that
	 * would be incorrect and we'd need to override it.
	 */
	अगर (!p_hwfn->करोorbells) अणु
		p_hwfn->करोorbells = (u8 __iomem *)p_hwfn->regview +
						  PXP_VF_BAR0_START_DQ;
	पूर्ण अन्यथा अगर (p_hwfn == p_lead) अणु
		/* For leading hw-function, value is always correct, but need
		 * to handle scenario where legacy PF would not support 100g
		 * mapped bars later.
		 */
		p_iov->b_करोorbell_bar = true;
	पूर्ण अन्यथा अणु
		/* here, value would be correct ONLY अगर the leading hwfn
		 * received indication that mapped-bars are supported.
		 */
		अगर (p_lead->vf_iov_info->b_करोorbell_bar)
			p_iov->b_करोorbell_bar = true;
		अन्यथा
			p_hwfn->करोorbells = (u8 __iomem *)
			    p_hwfn->regview + PXP_VF_BAR0_START_DQ;
	पूर्ण

	/* Allocate vf2pf msg */
	p_iov->vf2pf_request = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
						  माप(जोड़ vfpf_tlvs),
						  &p_iov->vf2pf_request_phys,
						  GFP_KERNEL);
	अगर (!p_iov->vf2pf_request)
		जाओ मुक्त_p_iov;

	p_iov->pf2vf_reply = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
						माप(जोड़ pfvf_tlvs),
						&p_iov->pf2vf_reply_phys,
						GFP_KERNEL);
	अगर (!p_iov->pf2vf_reply)
		जाओ मुक्त_vf2pf_request;

	DP_VERBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "VF's Request mailbox [%p virt 0x%llx phys], Response mailbox [%p virt 0x%llx phys]\n",
		   p_iov->vf2pf_request,
		   (u64) p_iov->vf2pf_request_phys,
		   p_iov->pf2vf_reply, (u64)p_iov->pf2vf_reply_phys);

	/* Allocate Bulletin board */
	p_iov->bulletin.size = माप(काष्ठा qed_bulletin_content);
	p_iov->bulletin.p_virt = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
						    p_iov->bulletin.size,
						    &p_iov->bulletin.phys,
						    GFP_KERNEL);
	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "VF's bulletin Board [%p virt 0x%llx phys 0x%08x bytes]\n",
		   p_iov->bulletin.p_virt,
		   (u64)p_iov->bulletin.phys, p_iov->bulletin.size);

	mutex_init(&p_iov->mutex);

	p_hwfn->vf_iov_info = p_iov;

	p_hwfn->hw_info.personality = QED_PCI_ETH;

	rc = qed_vf_pf_acquire(p_hwfn);

	/* If VF is 100g using a mapped bar and PF is too old to support that,
	 * acquisition would succeed - but the VF would have no way knowing
	 * the size of the करोorbell bar configured in HW and thus will not
	 * know how to split it क्रम 2nd hw-function.
	 * In this हाल we re-try without the indication of the mapped
	 * करोorbell.
	 */
	अगर (!rc && p_iov->b_करोorbell_bar &&
	    !qed_vf_hw_bar_size(p_hwfn, BAR_ID_1) &&
	    (p_hwfn->cdev->num_hwfns > 1)) अणु
		rc = _qed_vf_pf_release(p_hwfn, false);
		अगर (rc)
			वापस rc;

		p_iov->b_करोorbell_bar = false;
		p_hwfn->करोorbells = (u8 __iomem *)p_hwfn->regview +
						  PXP_VF_BAR0_START_DQ;
		rc = qed_vf_pf_acquire(p_hwfn);
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "Regview [%p], Doorbell [%p], Device-doorbell [%p]\n",
		   p_hwfn->regview, p_hwfn->करोorbells, p_hwfn->cdev->करोorbells);

	वापस rc;

मुक्त_vf2pf_request:
	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
			  माप(जोड़ vfpf_tlvs),
			  p_iov->vf2pf_request, p_iov->vf2pf_request_phys);
मुक्त_p_iov:
	kमुक्त(p_iov);

	वापस -ENOMEM;
पूर्ण
#घोषणा TSTORM_QZONE_START   PXP_VF_BAR0_START_SDM_ZONE_A
#घोषणा MSTORM_QZONE_START(dev)   (TSTORM_QZONE_START +	\
				   (TSTORM_QZONE_SIZE * NUM_OF_L2_QUEUES(dev)))

अटल व्योम
__qed_vf_prep_tunn_req_tlv(काष्ठा vfpf_update_tunn_param_tlv *p_req,
			   काष्ठा qed_tunn_update_type *p_src,
			   क्रमागत qed_tunn_mode mask, u8 *p_cls)
अणु
	अगर (p_src->b_update_mode) अणु
		p_req->tun_mode_update_mask |= BIT(mask);

		अगर (p_src->b_mode_enabled)
			p_req->tunn_mode |= BIT(mask);
	पूर्ण

	*p_cls = p_src->tun_cls;
पूर्ण

अटल व्योम
qed_vf_prep_tunn_req_tlv(काष्ठा vfpf_update_tunn_param_tlv *p_req,
			 काष्ठा qed_tunn_update_type *p_src,
			 क्रमागत qed_tunn_mode mask,
			 u8 *p_cls, काष्ठा qed_tunn_update_udp_port *p_port,
			 u8 *p_update_port, u16 *p_udp_port)
अणु
	अगर (p_port->b_update_port) अणु
		*p_update_port = 1;
		*p_udp_port = p_port->port;
	पूर्ण

	__qed_vf_prep_tunn_req_tlv(p_req, p_src, mask, p_cls);
पूर्ण

व्योम qed_vf_set_vf_start_tunn_update_param(काष्ठा qed_tunnel_info *p_tun)
अणु
	अगर (p_tun->vxlan.b_mode_enabled)
		p_tun->vxlan.b_update_mode = true;
	अगर (p_tun->l2_geneve.b_mode_enabled)
		p_tun->l2_geneve.b_update_mode = true;
	अगर (p_tun->ip_geneve.b_mode_enabled)
		p_tun->ip_geneve.b_update_mode = true;
	अगर (p_tun->l2_gre.b_mode_enabled)
		p_tun->l2_gre.b_update_mode = true;
	अगर (p_tun->ip_gre.b_mode_enabled)
		p_tun->ip_gre.b_update_mode = true;

	p_tun->b_update_rx_cls = true;
	p_tun->b_update_tx_cls = true;
पूर्ण

अटल व्योम
__qed_vf_update_tunn_param(काष्ठा qed_tunn_update_type *p_tun,
			   u16 feature_mask, u8 tunn_mode,
			   u8 tunn_cls, क्रमागत qed_tunn_mode val)
अणु
	अगर (feature_mask & BIT(val)) अणु
		p_tun->b_mode_enabled = tunn_mode;
		p_tun->tun_cls = tunn_cls;
	पूर्ण अन्यथा अणु
		p_tun->b_mode_enabled = false;
	पूर्ण
पूर्ण

अटल व्योम qed_vf_update_tunn_param(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_tunnel_info *p_tun,
				     काष्ठा pfvf_update_tunn_param_tlv *p_resp)
अणु
	/* Update mode and classes provided by PF */
	u16 feat_mask = p_resp->tunn_feature_mask;

	__qed_vf_update_tunn_param(&p_tun->vxlan, feat_mask,
				   p_resp->vxlan_mode, p_resp->vxlan_clss,
				   QED_MODE_VXLAN_TUNN);
	__qed_vf_update_tunn_param(&p_tun->l2_geneve, feat_mask,
				   p_resp->l2geneve_mode,
				   p_resp->l2geneve_clss,
				   QED_MODE_L2GENEVE_TUNN);
	__qed_vf_update_tunn_param(&p_tun->ip_geneve, feat_mask,
				   p_resp->ipgeneve_mode,
				   p_resp->ipgeneve_clss,
				   QED_MODE_IPGENEVE_TUNN);
	__qed_vf_update_tunn_param(&p_tun->l2_gre, feat_mask,
				   p_resp->l2gre_mode, p_resp->l2gre_clss,
				   QED_MODE_L2GRE_TUNN);
	__qed_vf_update_tunn_param(&p_tun->ip_gre, feat_mask,
				   p_resp->ipgre_mode, p_resp->ipgre_clss,
				   QED_MODE_IPGRE_TUNN);
	p_tun->geneve_port.port = p_resp->geneve_udp_port;
	p_tun->vxlan_port.port = p_resp->vxlan_udp_port;

	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "tunn mode: vxlan=0x%x, l2geneve=0x%x, ipgeneve=0x%x, l2gre=0x%x, ipgre=0x%x",
		   p_tun->vxlan.b_mode_enabled, p_tun->l2_geneve.b_mode_enabled,
		   p_tun->ip_geneve.b_mode_enabled,
		   p_tun->l2_gre.b_mode_enabled, p_tun->ip_gre.b_mode_enabled);
पूर्ण

पूर्णांक qed_vf_pf_tunnel_param_update(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_tunnel_info *p_src)
अणु
	काष्ठा qed_tunnel_info *p_tun = &p_hwfn->cdev->tunnel;
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	काष्ठा pfvf_update_tunn_param_tlv *p_resp;
	काष्ठा vfpf_update_tunn_param_tlv *p_req;
	पूर्णांक rc;

	p_req = qed_vf_pf_prep(p_hwfn, CHANNEL_TLV_UPDATE_TUNN_PARAM,
			       माप(*p_req));

	अगर (p_src->b_update_rx_cls && p_src->b_update_tx_cls)
		p_req->update_tun_cls = 1;

	qed_vf_prep_tunn_req_tlv(p_req, &p_src->vxlan, QED_MODE_VXLAN_TUNN,
				 &p_req->vxlan_clss, &p_src->vxlan_port,
				 &p_req->update_vxlan_port,
				 &p_req->vxlan_port);
	qed_vf_prep_tunn_req_tlv(p_req, &p_src->l2_geneve,
				 QED_MODE_L2GENEVE_TUNN,
				 &p_req->l2geneve_clss, &p_src->geneve_port,
				 &p_req->update_geneve_port,
				 &p_req->geneve_port);
	__qed_vf_prep_tunn_req_tlv(p_req, &p_src->ip_geneve,
				   QED_MODE_IPGENEVE_TUNN,
				   &p_req->ipgeneve_clss);
	__qed_vf_prep_tunn_req_tlv(p_req, &p_src->l2_gre,
				   QED_MODE_L2GRE_TUNN, &p_req->l2gre_clss);
	__qed_vf_prep_tunn_req_tlv(p_req, &p_src->ip_gre,
				   QED_MODE_IPGRE_TUNN, &p_req->ipgre_clss);

	/* add list termination tlv */
	qed_add_tlv(p_hwfn, &p_iov->offset,
		    CHANNEL_TLV_LIST_END,
		    माप(काष्ठा channel_list_end_tlv));

	p_resp = &p_iov->pf2vf_reply->tunn_param_resp;
	rc = qed_send_msg2pf(p_hwfn, &p_resp->hdr.status, माप(*p_resp));

	अगर (rc)
		जाओ निकास;

	अगर (p_resp->hdr.status != PFVF_STATUS_SUCCESS) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "Failed to update tunnel parameters\n");
		rc = -EINVAL;
	पूर्ण

	qed_vf_update_tunn_param(p_hwfn, p_tun, p_resp);
निकास:
	qed_vf_pf_req_end(p_hwfn, rc);
	वापस rc;
पूर्ण

पूर्णांक
qed_vf_pf_rxq_start(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_queue_cid *p_cid,
		    u16 bd_max_bytes,
		    dma_addr_t bd_chain_phys_addr,
		    dma_addr_t cqe_pbl_addr,
		    u16 cqe_pbl_size, व्योम __iomem **pp_prod)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	काष्ठा pfvf_start_queue_resp_tlv *resp;
	काष्ठा vfpf_start_rxq_tlv *req;
	u8 rx_qid = p_cid->rel.queue_id;
	पूर्णांक rc;

	/* clear mailbox and prep first tlv */
	req = qed_vf_pf_prep(p_hwfn, CHANNEL_TLV_START_RXQ, माप(*req));

	req->rx_qid = rx_qid;
	req->cqe_pbl_addr = cqe_pbl_addr;
	req->cqe_pbl_size = cqe_pbl_size;
	req->rxq_addr = bd_chain_phys_addr;
	req->hw_sb = p_cid->sb_igu_id;
	req->sb_index = p_cid->sb_idx;
	req->bd_max_bytes = bd_max_bytes;
	req->stat_id = -1;

	/* If PF is legacy, we'll need to calculate producers ourselves
	 * as well as clean them.
	 */
	अगर (p_iov->b_pre_fp_hsi) अणु
		u8 hw_qid = p_iov->acquire_resp.resc.hw_qid[rx_qid];
		u32 init_prod_val = 0;

		*pp_prod = (u8 __iomem *)
		    p_hwfn->regview +
		    MSTORM_QZONE_START(p_hwfn->cdev) +
		    hw_qid * MSTORM_QZONE_SIZE;

		/* Init the rcq, rx bd and rx sge (अगर valid) producers to 0 */
		__पूर्णांकernal_ram_wr(p_hwfn, *pp_prod, माप(u32),
				  (u32 *)(&init_prod_val));
	पूर्ण

	qed_vf_pf_add_qid(p_hwfn, p_cid);

	/* add list termination tlv */
	qed_add_tlv(p_hwfn, &p_iov->offset,
		    CHANNEL_TLV_LIST_END, माप(काष्ठा channel_list_end_tlv));

	resp = &p_iov->pf2vf_reply->queue_start;
	rc = qed_send_msg2pf(p_hwfn, &resp->hdr.status, माप(*resp));
	अगर (rc)
		जाओ निकास;

	अगर (resp->hdr.status != PFVF_STATUS_SUCCESS) अणु
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

	/* Learn the address of the producer from the response */
	अगर (!p_iov->b_pre_fp_hsi) अणु
		u32 init_prod_val = 0;

		*pp_prod = (u8 __iomem *)p_hwfn->regview + resp->offset;
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "Rxq[0x%02x]: producer at %p [offset 0x%08x]\n",
			   rx_qid, *pp_prod, resp->offset);

		/* Init the rcq, rx bd and rx sge (अगर valid) producers to 0 */
		__पूर्णांकernal_ram_wr(p_hwfn, *pp_prod, माप(u32),
				  (u32 *)&init_prod_val);
	पूर्ण
निकास:
	qed_vf_pf_req_end(p_hwfn, rc);

	वापस rc;
पूर्ण

पूर्णांक qed_vf_pf_rxq_stop(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_queue_cid *p_cid, bool cqe_completion)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	काष्ठा vfpf_stop_rxqs_tlv *req;
	काष्ठा pfvf_def_resp_tlv *resp;
	पूर्णांक rc;

	/* clear mailbox and prep first tlv */
	req = qed_vf_pf_prep(p_hwfn, CHANNEL_TLV_STOP_RXQS, माप(*req));

	req->rx_qid = p_cid->rel.queue_id;
	req->num_rxqs = 1;
	req->cqe_completion = cqe_completion;

	qed_vf_pf_add_qid(p_hwfn, p_cid);

	/* add list termination tlv */
	qed_add_tlv(p_hwfn, &p_iov->offset,
		    CHANNEL_TLV_LIST_END, माप(काष्ठा channel_list_end_tlv));

	resp = &p_iov->pf2vf_reply->शेष_resp;
	rc = qed_send_msg2pf(p_hwfn, &resp->hdr.status, माप(*resp));
	अगर (rc)
		जाओ निकास;

	अगर (resp->hdr.status != PFVF_STATUS_SUCCESS) अणु
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

निकास:
	qed_vf_pf_req_end(p_hwfn, rc);

	वापस rc;
पूर्ण

पूर्णांक
qed_vf_pf_txq_start(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_queue_cid *p_cid,
		    dma_addr_t pbl_addr,
		    u16 pbl_size, व्योम __iomem **pp_करोorbell)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	काष्ठा pfvf_start_queue_resp_tlv *resp;
	काष्ठा vfpf_start_txq_tlv *req;
	u16 qid = p_cid->rel.queue_id;
	पूर्णांक rc;

	/* clear mailbox and prep first tlv */
	req = qed_vf_pf_prep(p_hwfn, CHANNEL_TLV_START_TXQ, माप(*req));

	req->tx_qid = qid;

	/* Tx */
	req->pbl_addr = pbl_addr;
	req->pbl_size = pbl_size;
	req->hw_sb = p_cid->sb_igu_id;
	req->sb_index = p_cid->sb_idx;

	qed_vf_pf_add_qid(p_hwfn, p_cid);

	/* add list termination tlv */
	qed_add_tlv(p_hwfn, &p_iov->offset,
		    CHANNEL_TLV_LIST_END, माप(काष्ठा channel_list_end_tlv));

	resp = &p_iov->pf2vf_reply->queue_start;
	rc = qed_send_msg2pf(p_hwfn, &resp->hdr.status, माप(*resp));
	अगर (rc)
		जाओ निकास;

	अगर (resp->hdr.status != PFVF_STATUS_SUCCESS) अणु
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

	/* Modern PFs provide the actual offsets, जबतक legacy
	 * provided only the queue id.
	 */
	अगर (!p_iov->b_pre_fp_hsi) अणु
		*pp_करोorbell = (u8 __iomem *)p_hwfn->करोorbells + resp->offset;
	पूर्ण अन्यथा अणु
		u8 cid = p_iov->acquire_resp.resc.cid[qid];

		*pp_करोorbell = (u8 __iomem *)p_hwfn->करोorbells +
					     qed_db_addr_vf(cid,
							    DQ_DEMS_LEGACY);
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "Txq[0x%02x.%02x]: doorbell at %p [offset 0x%08x]\n",
		   qid, p_cid->qid_usage_idx, *pp_करोorbell, resp->offset);
निकास:
	qed_vf_pf_req_end(p_hwfn, rc);

	वापस rc;
पूर्ण

पूर्णांक qed_vf_pf_txq_stop(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_queue_cid *p_cid)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	काष्ठा vfpf_stop_txqs_tlv *req;
	काष्ठा pfvf_def_resp_tlv *resp;
	पूर्णांक rc;

	/* clear mailbox and prep first tlv */
	req = qed_vf_pf_prep(p_hwfn, CHANNEL_TLV_STOP_TXQS, माप(*req));

	req->tx_qid = p_cid->rel.queue_id;
	req->num_txqs = 1;

	qed_vf_pf_add_qid(p_hwfn, p_cid);

	/* add list termination tlv */
	qed_add_tlv(p_hwfn, &p_iov->offset,
		    CHANNEL_TLV_LIST_END, माप(काष्ठा channel_list_end_tlv));

	resp = &p_iov->pf2vf_reply->शेष_resp;
	rc = qed_send_msg2pf(p_hwfn, &resp->hdr.status, माप(*resp));
	अगर (rc)
		जाओ निकास;

	अगर (resp->hdr.status != PFVF_STATUS_SUCCESS) अणु
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

निकास:
	qed_vf_pf_req_end(p_hwfn, rc);

	वापस rc;
पूर्ण

पूर्णांक qed_vf_pf_vport_start(काष्ठा qed_hwfn *p_hwfn,
			  u8 vport_id,
			  u16 mtu,
			  u8 inner_vlan_removal,
			  क्रमागत qed_tpa_mode tpa_mode,
			  u8 max_buffers_per_cqe, u8 only_untagged)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	काष्ठा vfpf_vport_start_tlv *req;
	काष्ठा pfvf_def_resp_tlv *resp;
	पूर्णांक rc, i;

	/* clear mailbox and prep first tlv */
	req = qed_vf_pf_prep(p_hwfn, CHANNEL_TLV_VPORT_START, माप(*req));

	req->mtu = mtu;
	req->vport_id = vport_id;
	req->inner_vlan_removal = inner_vlan_removal;
	req->tpa_mode = tpa_mode;
	req->max_buffers_per_cqe = max_buffers_per_cqe;
	req->only_untagged = only_untagged;

	/* status blocks */
	क्रम (i = 0; i < p_hwfn->vf_iov_info->acquire_resp.resc.num_sbs; i++) अणु
		काष्ठा qed_sb_info *p_sb = p_hwfn->vf_iov_info->sbs_info[i];

		अगर (p_sb)
			req->sb_addr[i] = p_sb->sb_phys;
	पूर्ण

	/* add list termination tlv */
	qed_add_tlv(p_hwfn, &p_iov->offset,
		    CHANNEL_TLV_LIST_END, माप(काष्ठा channel_list_end_tlv));

	resp = &p_iov->pf2vf_reply->शेष_resp;
	rc = qed_send_msg2pf(p_hwfn, &resp->hdr.status, माप(*resp));
	अगर (rc)
		जाओ निकास;

	अगर (resp->hdr.status != PFVF_STATUS_SUCCESS) अणु
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

निकास:
	qed_vf_pf_req_end(p_hwfn, rc);

	वापस rc;
पूर्ण

पूर्णांक qed_vf_pf_vport_stop(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	काष्ठा pfvf_def_resp_tlv *resp = &p_iov->pf2vf_reply->शेष_resp;
	पूर्णांक rc;

	/* clear mailbox and prep first tlv */
	qed_vf_pf_prep(p_hwfn, CHANNEL_TLV_VPORT_TEARDOWN,
		       माप(काष्ठा vfpf_first_tlv));

	/* add list termination tlv */
	qed_add_tlv(p_hwfn, &p_iov->offset,
		    CHANNEL_TLV_LIST_END, माप(काष्ठा channel_list_end_tlv));

	rc = qed_send_msg2pf(p_hwfn, &resp->hdr.status, माप(*resp));
	अगर (rc)
		जाओ निकास;

	अगर (resp->hdr.status != PFVF_STATUS_SUCCESS) अणु
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

निकास:
	qed_vf_pf_req_end(p_hwfn, rc);

	वापस rc;
पूर्ण

अटल bool
qed_vf_handle_vp_update_is_needed(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_sp_vport_update_params *p_data,
				  u16 tlv)
अणु
	चयन (tlv) अणु
	हाल CHANNEL_TLV_VPORT_UPDATE_ACTIVATE:
		वापस !!(p_data->update_vport_active_rx_flg ||
			  p_data->update_vport_active_tx_flg);
	हाल CHANNEL_TLV_VPORT_UPDATE_TX_SWITCH:
		वापस !!p_data->update_tx_चयनing_flg;
	हाल CHANNEL_TLV_VPORT_UPDATE_VLAN_STRIP:
		वापस !!p_data->update_inner_vlan_removal_flg;
	हाल CHANNEL_TLV_VPORT_UPDATE_ACCEPT_ANY_VLAN:
		वापस !!p_data->update_accept_any_vlan_flg;
	हाल CHANNEL_TLV_VPORT_UPDATE_MCAST:
		वापस !!p_data->update_approx_mcast_flg;
	हाल CHANNEL_TLV_VPORT_UPDATE_ACCEPT_PARAM:
		वापस !!(p_data->accept_flags.update_rx_mode_config ||
			  p_data->accept_flags.update_tx_mode_config);
	हाल CHANNEL_TLV_VPORT_UPDATE_RSS:
		वापस !!p_data->rss_params;
	हाल CHANNEL_TLV_VPORT_UPDATE_SGE_TPA:
		वापस !!p_data->sge_tpa_params;
	शेष:
		DP_INFO(p_hwfn, "Unexpected vport-update TLV[%d]\n",
			tlv);
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम
qed_vf_handle_vp_update_tlvs_resp(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_sp_vport_update_params *p_data)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	काष्ठा pfvf_def_resp_tlv *p_resp;
	u16 tlv;

	क्रम (tlv = CHANNEL_TLV_VPORT_UPDATE_ACTIVATE;
	     tlv < CHANNEL_TLV_VPORT_UPDATE_MAX; tlv++) अणु
		अगर (!qed_vf_handle_vp_update_is_needed(p_hwfn, p_data, tlv))
			जारी;

		p_resp = (काष्ठा pfvf_def_resp_tlv *)
			 qed_iov_search_list_tlvs(p_hwfn, p_iov->pf2vf_reply,
						  tlv);
		अगर (p_resp && p_resp->hdr.status)
			DP_VERBOSE(p_hwfn, QED_MSG_IOV,
				   "TLV[%d] Configuration %s\n",
				   tlv,
				   (p_resp && p_resp->hdr.status) ? "succeeded"
								  : "failed");
	पूर्ण
पूर्ण

पूर्णांक qed_vf_pf_vport_update(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_sp_vport_update_params *p_params)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	काष्ठा vfpf_vport_update_tlv *req;
	काष्ठा pfvf_def_resp_tlv *resp;
	u8 update_rx, update_tx;
	u32 resp_size = 0;
	u16 size, tlv;
	पूर्णांक rc;

	resp = &p_iov->pf2vf_reply->शेष_resp;
	resp_size = माप(*resp);

	update_rx = p_params->update_vport_active_rx_flg;
	update_tx = p_params->update_vport_active_tx_flg;

	/* clear mailbox and prep header tlv */
	qed_vf_pf_prep(p_hwfn, CHANNEL_TLV_VPORT_UPDATE, माप(*req));

	/* Prepare extended tlvs */
	अगर (update_rx || update_tx) अणु
		काष्ठा vfpf_vport_update_activate_tlv *p_act_tlv;

		size = माप(काष्ठा vfpf_vport_update_activate_tlv);
		p_act_tlv = qed_add_tlv(p_hwfn, &p_iov->offset,
					CHANNEL_TLV_VPORT_UPDATE_ACTIVATE,
					size);
		resp_size += माप(काष्ठा pfvf_def_resp_tlv);

		अगर (update_rx) अणु
			p_act_tlv->update_rx = update_rx;
			p_act_tlv->active_rx = p_params->vport_active_rx_flg;
		पूर्ण

		अगर (update_tx) अणु
			p_act_tlv->update_tx = update_tx;
			p_act_tlv->active_tx = p_params->vport_active_tx_flg;
		पूर्ण
	पूर्ण

	अगर (p_params->update_tx_चयनing_flg) अणु
		काष्ठा vfpf_vport_update_tx_चयन_tlv *p_tx_चयन_tlv;

		size = माप(काष्ठा vfpf_vport_update_tx_चयन_tlv);
		tlv = CHANNEL_TLV_VPORT_UPDATE_TX_SWITCH;
		p_tx_चयन_tlv = qed_add_tlv(p_hwfn, &p_iov->offset,
					      tlv, size);
		resp_size += माप(काष्ठा pfvf_def_resp_tlv);

		p_tx_चयन_tlv->tx_चयनing = p_params->tx_चयनing_flg;
	पूर्ण

	अगर (p_params->update_approx_mcast_flg) अणु
		काष्ठा vfpf_vport_update_mcast_bin_tlv *p_mcast_tlv;

		size = माप(काष्ठा vfpf_vport_update_mcast_bin_tlv);
		p_mcast_tlv = qed_add_tlv(p_hwfn, &p_iov->offset,
					  CHANNEL_TLV_VPORT_UPDATE_MCAST, size);
		resp_size += माप(काष्ठा pfvf_def_resp_tlv);

		स_नकल(p_mcast_tlv->bins, p_params->bins,
		       माप(u32) * ETH_MULTICAST_MAC_BINS_IN_REGS);
	पूर्ण

	update_rx = p_params->accept_flags.update_rx_mode_config;
	update_tx = p_params->accept_flags.update_tx_mode_config;

	अगर (update_rx || update_tx) अणु
		काष्ठा vfpf_vport_update_accept_param_tlv *p_accept_tlv;

		tlv = CHANNEL_TLV_VPORT_UPDATE_ACCEPT_PARAM;
		size = माप(काष्ठा vfpf_vport_update_accept_param_tlv);
		p_accept_tlv = qed_add_tlv(p_hwfn, &p_iov->offset, tlv, size);
		resp_size += माप(काष्ठा pfvf_def_resp_tlv);

		अगर (update_rx) अणु
			p_accept_tlv->update_rx_mode = update_rx;
			p_accept_tlv->rx_accept_filter =
			    p_params->accept_flags.rx_accept_filter;
		पूर्ण

		अगर (update_tx) अणु
			p_accept_tlv->update_tx_mode = update_tx;
			p_accept_tlv->tx_accept_filter =
			    p_params->accept_flags.tx_accept_filter;
		पूर्ण
	पूर्ण

	अगर (p_params->rss_params) अणु
		काष्ठा qed_rss_params *rss_params = p_params->rss_params;
		काष्ठा vfpf_vport_update_rss_tlv *p_rss_tlv;
		पूर्णांक i, table_size;

		size = माप(काष्ठा vfpf_vport_update_rss_tlv);
		p_rss_tlv = qed_add_tlv(p_hwfn,
					&p_iov->offset,
					CHANNEL_TLV_VPORT_UPDATE_RSS, size);
		resp_size += माप(काष्ठा pfvf_def_resp_tlv);

		अगर (rss_params->update_rss_config)
			p_rss_tlv->update_rss_flags |=
			    VFPF_UPDATE_RSS_CONFIG_FLAG;
		अगर (rss_params->update_rss_capabilities)
			p_rss_tlv->update_rss_flags |=
			    VFPF_UPDATE_RSS_CAPS_FLAG;
		अगर (rss_params->update_rss_ind_table)
			p_rss_tlv->update_rss_flags |=
			    VFPF_UPDATE_RSS_IND_TABLE_FLAG;
		अगर (rss_params->update_rss_key)
			p_rss_tlv->update_rss_flags |= VFPF_UPDATE_RSS_KEY_FLAG;

		p_rss_tlv->rss_enable = rss_params->rss_enable;
		p_rss_tlv->rss_caps = rss_params->rss_caps;
		p_rss_tlv->rss_table_size_log = rss_params->rss_table_size_log;

		table_size = min_t(पूर्णांक, T_ETH_INसूचीECTION_TABLE_SIZE,
				   1 << p_rss_tlv->rss_table_size_log);
		क्रम (i = 0; i < table_size; i++) अणु
			काष्ठा qed_queue_cid *p_queue;

			p_queue = rss_params->rss_ind_table[i];
			p_rss_tlv->rss_ind_table[i] = p_queue->rel.queue_id;
		पूर्ण
		स_नकल(p_rss_tlv->rss_key, rss_params->rss_key,
		       माप(rss_params->rss_key));
	पूर्ण

	अगर (p_params->update_accept_any_vlan_flg) अणु
		काष्ठा vfpf_vport_update_accept_any_vlan_tlv *p_any_vlan_tlv;

		size = माप(काष्ठा vfpf_vport_update_accept_any_vlan_tlv);
		tlv = CHANNEL_TLV_VPORT_UPDATE_ACCEPT_ANY_VLAN;
		p_any_vlan_tlv = qed_add_tlv(p_hwfn, &p_iov->offset, tlv, size);

		resp_size += माप(काष्ठा pfvf_def_resp_tlv);
		p_any_vlan_tlv->accept_any_vlan = p_params->accept_any_vlan;
		p_any_vlan_tlv->update_accept_any_vlan_flg =
		    p_params->update_accept_any_vlan_flg;
	पूर्ण

	/* add list termination tlv */
	qed_add_tlv(p_hwfn, &p_iov->offset,
		    CHANNEL_TLV_LIST_END, माप(काष्ठा channel_list_end_tlv));

	rc = qed_send_msg2pf(p_hwfn, &resp->hdr.status, resp_size);
	अगर (rc)
		जाओ निकास;

	अगर (resp->hdr.status != PFVF_STATUS_SUCCESS) अणु
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

	qed_vf_handle_vp_update_tlvs_resp(p_hwfn, p_params);

निकास:
	qed_vf_pf_req_end(p_hwfn, rc);

	वापस rc;
पूर्ण

पूर्णांक qed_vf_pf_reset(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	काष्ठा pfvf_def_resp_tlv *resp;
	काष्ठा vfpf_first_tlv *req;
	पूर्णांक rc;

	/* clear mailbox and prep first tlv */
	req = qed_vf_pf_prep(p_hwfn, CHANNEL_TLV_CLOSE, माप(*req));

	/* add list termination tlv */
	qed_add_tlv(p_hwfn, &p_iov->offset,
		    CHANNEL_TLV_LIST_END, माप(काष्ठा channel_list_end_tlv));

	resp = &p_iov->pf2vf_reply->शेष_resp;
	rc = qed_send_msg2pf(p_hwfn, &resp->hdr.status, माप(*resp));
	अगर (rc)
		जाओ निकास;

	अगर (resp->hdr.status != PFVF_STATUS_SUCCESS) अणु
		rc = -EAGAIN;
		जाओ निकास;
	पूर्ण

	p_hwfn->b_पूर्णांक_enabled = 0;

निकास:
	qed_vf_pf_req_end(p_hwfn, rc);

	वापस rc;
पूर्ण

व्योम qed_vf_pf_filter_mcast(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_filter_mcast *p_filter_cmd)
अणु
	काष्ठा qed_sp_vport_update_params sp_params;
	पूर्णांक i;

	स_रखो(&sp_params, 0, माप(sp_params));
	sp_params.update_approx_mcast_flg = 1;

	अगर (p_filter_cmd->opcode == QED_FILTER_ADD) अणु
		क्रम (i = 0; i < p_filter_cmd->num_mc_addrs; i++) अणु
			u32 bit;

			bit = qed_mcast_bin_from_mac(p_filter_cmd->mac[i]);
			sp_params.bins[bit / 32] |= 1 << (bit % 32);
		पूर्ण
	पूर्ण

	qed_vf_pf_vport_update(p_hwfn, &sp_params);
पूर्ण

पूर्णांक qed_vf_pf_filter_ucast(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_filter_ucast *p_ucast)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	काष्ठा vfpf_ucast_filter_tlv *req;
	काष्ठा pfvf_def_resp_tlv *resp;
	पूर्णांक rc;

	/* clear mailbox and prep first tlv */
	req = qed_vf_pf_prep(p_hwfn, CHANNEL_TLV_UCAST_FILTER, माप(*req));
	req->opcode = (u8) p_ucast->opcode;
	req->type = (u8) p_ucast->type;
	स_नकल(req->mac, p_ucast->mac, ETH_ALEN);
	req->vlan = p_ucast->vlan;

	/* add list termination tlv */
	qed_add_tlv(p_hwfn, &p_iov->offset,
		    CHANNEL_TLV_LIST_END, माप(काष्ठा channel_list_end_tlv));

	resp = &p_iov->pf2vf_reply->शेष_resp;
	rc = qed_send_msg2pf(p_hwfn, &resp->hdr.status, माप(*resp));
	अगर (rc)
		जाओ निकास;

	अगर (resp->hdr.status != PFVF_STATUS_SUCCESS) अणु
		rc = -EAGAIN;
		जाओ निकास;
	पूर्ण

निकास:
	qed_vf_pf_req_end(p_hwfn, rc);

	वापस rc;
पूर्ण

पूर्णांक qed_vf_pf_पूर्णांक_cleanup(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	काष्ठा pfvf_def_resp_tlv *resp = &p_iov->pf2vf_reply->शेष_resp;
	पूर्णांक rc;

	/* clear mailbox and prep first tlv */
	qed_vf_pf_prep(p_hwfn, CHANNEL_TLV_INT_CLEANUP,
		       माप(काष्ठा vfpf_first_tlv));

	/* add list termination tlv */
	qed_add_tlv(p_hwfn, &p_iov->offset,
		    CHANNEL_TLV_LIST_END, माप(काष्ठा channel_list_end_tlv));

	rc = qed_send_msg2pf(p_hwfn, &resp->hdr.status, माप(*resp));
	अगर (rc)
		जाओ निकास;

	अगर (resp->hdr.status != PFVF_STATUS_SUCCESS) अणु
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

निकास:
	qed_vf_pf_req_end(p_hwfn, rc);

	वापस rc;
पूर्ण

पूर्णांक qed_vf_pf_get_coalesce(काष्ठा qed_hwfn *p_hwfn,
			   u16 *p_coal, काष्ठा qed_queue_cid *p_cid)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	काष्ठा pfvf_पढ़ो_coal_resp_tlv *resp;
	काष्ठा vfpf_पढ़ो_coal_req_tlv *req;
	पूर्णांक rc;

	/* clear mailbox and prep header tlv */
	req = qed_vf_pf_prep(p_hwfn, CHANNEL_TLV_COALESCE_READ, माप(*req));
	req->qid = p_cid->rel.queue_id;
	req->is_rx = p_cid->b_is_rx ? 1 : 0;

	qed_add_tlv(p_hwfn, &p_iov->offset, CHANNEL_TLV_LIST_END,
		    माप(काष्ठा channel_list_end_tlv));
	resp = &p_iov->pf2vf_reply->पढ़ो_coal_resp;

	rc = qed_send_msg2pf(p_hwfn, &resp->hdr.status, माप(*resp));
	अगर (rc)
		जाओ निकास;

	अगर (resp->hdr.status != PFVF_STATUS_SUCCESS)
		जाओ निकास;

	*p_coal = resp->coal;
निकास:
	qed_vf_pf_req_end(p_hwfn, rc);

	वापस rc;
पूर्ण

पूर्णांक
qed_vf_pf_bulletin_update_mac(काष्ठा qed_hwfn *p_hwfn,
			      u8 *p_mac)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	काष्ठा vfpf_bulletin_update_mac_tlv *p_req;
	काष्ठा pfvf_def_resp_tlv *p_resp;
	पूर्णांक rc;

	अगर (!p_mac)
		वापस -EINVAL;

	/* clear mailbox and prep header tlv */
	p_req = qed_vf_pf_prep(p_hwfn, CHANNEL_TLV_BULLETIN_UPDATE_MAC,
			       माप(*p_req));
	ether_addr_copy(p_req->mac, p_mac);
	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "Requesting bulletin update for MAC[%pM]\n", p_mac);

	/* add list termination tlv */
	qed_add_tlv(p_hwfn, &p_iov->offset, CHANNEL_TLV_LIST_END,
		    माप(काष्ठा channel_list_end_tlv));

	p_resp = &p_iov->pf2vf_reply->शेष_resp;
	rc = qed_send_msg2pf(p_hwfn, &p_resp->hdr.status, माप(*p_resp));
	qed_vf_pf_req_end(p_hwfn, rc);
	वापस rc;
पूर्ण

पूर्णांक
qed_vf_pf_set_coalesce(काष्ठा qed_hwfn *p_hwfn,
		       u16 rx_coal, u16 tx_coal, काष्ठा qed_queue_cid *p_cid)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	काष्ठा vfpf_update_coalesce *req;
	काष्ठा pfvf_def_resp_tlv *resp;
	पूर्णांक rc;

	/* clear mailbox and prep header tlv */
	req = qed_vf_pf_prep(p_hwfn, CHANNEL_TLV_COALESCE_UPDATE, माप(*req));

	req->rx_coal = rx_coal;
	req->tx_coal = tx_coal;
	req->qid = p_cid->rel.queue_id;

	DP_VERBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "Setting coalesce rx_coal = %d, tx_coal = %d at queue = %d\n",
		   rx_coal, tx_coal, req->qid);

	/* add list termination tlv */
	qed_add_tlv(p_hwfn, &p_iov->offset, CHANNEL_TLV_LIST_END,
		    माप(काष्ठा channel_list_end_tlv));

	resp = &p_iov->pf2vf_reply->शेष_resp;
	rc = qed_send_msg2pf(p_hwfn, &resp->hdr.status, माप(*resp));
	अगर (rc)
		जाओ निकास;

	अगर (resp->hdr.status != PFVF_STATUS_SUCCESS)
		जाओ निकास;

	अगर (rx_coal)
		p_hwfn->cdev->rx_coalesce_usecs = rx_coal;

	अगर (tx_coal)
		p_hwfn->cdev->tx_coalesce_usecs = tx_coal;

निकास:
	qed_vf_pf_req_end(p_hwfn, rc);
	वापस rc;
पूर्ण

u16 qed_vf_get_igu_sb_id(काष्ठा qed_hwfn *p_hwfn, u16 sb_id)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;

	अगर (!p_iov) अणु
		DP_NOTICE(p_hwfn, "vf_sriov_info isn't initialized\n");
		वापस 0;
	पूर्ण

	वापस p_iov->acquire_resp.resc.hw_sbs[sb_id].hw_sb_id;
पूर्ण

व्योम qed_vf_set_sb_info(काष्ठा qed_hwfn *p_hwfn,
			u16 sb_id, काष्ठा qed_sb_info *p_sb)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;

	अगर (!p_iov) अणु
		DP_NOTICE(p_hwfn, "vf_sriov_info isn't initialized\n");
		वापस;
	पूर्ण

	अगर (sb_id >= PFVF_MAX_SBS_PER_VF) अणु
		DP_NOTICE(p_hwfn, "Can't configure SB %04x\n", sb_id);
		वापस;
	पूर्ण

	p_iov->sbs_info[sb_id] = p_sb;
पूर्ण

पूर्णांक qed_vf_पढ़ो_bulletin(काष्ठा qed_hwfn *p_hwfn, u8 *p_change)
अणु
	काष्ठा qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	काष्ठा qed_bulletin_content shaकरोw;
	u32 crc, crc_size;

	crc_size = माप(p_iov->bulletin.p_virt->crc);
	*p_change = 0;

	/* Need to guarantee PF is not in the middle of writing it */
	स_नकल(&shaकरोw, p_iov->bulletin.p_virt, p_iov->bulletin.size);

	/* If version did not update, no need to करो anything */
	अगर (shaकरोw.version == p_iov->bulletin_shaकरोw.version)
		वापस 0;

	/* Verअगरy the bulletin we see is valid */
	crc = crc32(0, (u8 *)&shaकरोw + crc_size,
		    p_iov->bulletin.size - crc_size);
	अगर (crc != shaकरोw.crc)
		वापस -EAGAIN;

	/* Set the shaकरोw bulletin and process it */
	स_नकल(&p_iov->bulletin_shaकरोw, &shaकरोw, p_iov->bulletin.size);

	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "Read a bulletin update %08x\n", shaकरोw.version);

	*p_change = 1;

	वापस 0;
पूर्ण

व्योम __qed_vf_get_link_params(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_mcp_link_params *p_params,
			      काष्ठा qed_bulletin_content *p_bulletin)
अणु
	स_रखो(p_params, 0, माप(*p_params));

	p_params->speed.स्वतःneg = p_bulletin->req_स्वतःneg;
	p_params->speed.advertised_speeds = p_bulletin->req_adv_speed;
	p_params->speed.क्रमced_speed = p_bulletin->req_क्रमced_speed;
	p_params->छोड़ो.स्वतःneg = p_bulletin->req_स्वतःneg_छोड़ो;
	p_params->छोड़ो.क्रमced_rx = p_bulletin->req_क्रमced_rx;
	p_params->छोड़ो.क्रमced_tx = p_bulletin->req_क्रमced_tx;
	p_params->loopback_mode = p_bulletin->req_loopback;
पूर्ण

व्योम qed_vf_get_link_params(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_mcp_link_params *params)
अणु
	__qed_vf_get_link_params(p_hwfn, params,
				 &(p_hwfn->vf_iov_info->bulletin_shaकरोw));
पूर्ण

व्योम __qed_vf_get_link_state(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_mcp_link_state *p_link,
			     काष्ठा qed_bulletin_content *p_bulletin)
अणु
	स_रखो(p_link, 0, माप(*p_link));

	p_link->link_up = p_bulletin->link_up;
	p_link->speed = p_bulletin->speed;
	p_link->full_duplex = p_bulletin->full_duplex;
	p_link->an = p_bulletin->स्वतःneg;
	p_link->an_complete = p_bulletin->स्वतःneg_complete;
	p_link->parallel_detection = p_bulletin->parallel_detection;
	p_link->pfc_enabled = p_bulletin->pfc_enabled;
	p_link->partner_adv_speed = p_bulletin->partner_adv_speed;
	p_link->partner_tx_flow_ctrl_en = p_bulletin->partner_tx_flow_ctrl_en;
	p_link->partner_rx_flow_ctrl_en = p_bulletin->partner_rx_flow_ctrl_en;
	p_link->partner_adv_छोड़ो = p_bulletin->partner_adv_छोड़ो;
	p_link->sfp_tx_fault = p_bulletin->sfp_tx_fault;
पूर्ण

व्योम qed_vf_get_link_state(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_mcp_link_state *link)
अणु
	__qed_vf_get_link_state(p_hwfn, link,
				&(p_hwfn->vf_iov_info->bulletin_shaकरोw));
पूर्ण

व्योम __qed_vf_get_link_caps(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_mcp_link_capabilities *p_link_caps,
			    काष्ठा qed_bulletin_content *p_bulletin)
अणु
	स_रखो(p_link_caps, 0, माप(*p_link_caps));
	p_link_caps->speed_capabilities = p_bulletin->capability_speed;
पूर्ण

व्योम qed_vf_get_link_caps(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_mcp_link_capabilities *p_link_caps)
अणु
	__qed_vf_get_link_caps(p_hwfn, p_link_caps,
			       &(p_hwfn->vf_iov_info->bulletin_shaकरोw));
पूर्ण

व्योम qed_vf_get_num_rxqs(काष्ठा qed_hwfn *p_hwfn, u8 *num_rxqs)
अणु
	*num_rxqs = p_hwfn->vf_iov_info->acquire_resp.resc.num_rxqs;
पूर्ण

व्योम qed_vf_get_num_txqs(काष्ठा qed_hwfn *p_hwfn, u8 *num_txqs)
अणु
	*num_txqs = p_hwfn->vf_iov_info->acquire_resp.resc.num_txqs;
पूर्ण

व्योम qed_vf_get_num_cids(काष्ठा qed_hwfn *p_hwfn, u8 *num_cids)
अणु
	*num_cids = p_hwfn->vf_iov_info->acquire_resp.resc.num_cids;
पूर्ण

व्योम qed_vf_get_port_mac(काष्ठा qed_hwfn *p_hwfn, u8 *port_mac)
अणु
	स_नकल(port_mac,
	       p_hwfn->vf_iov_info->acquire_resp.pfdev_info.port_mac, ETH_ALEN);
पूर्ण

व्योम qed_vf_get_num_vlan_filters(काष्ठा qed_hwfn *p_hwfn, u8 *num_vlan_filters)
अणु
	काष्ठा qed_vf_iov *p_vf;

	p_vf = p_hwfn->vf_iov_info;
	*num_vlan_filters = p_vf->acquire_resp.resc.num_vlan_filters;
पूर्ण

व्योम qed_vf_get_num_mac_filters(काष्ठा qed_hwfn *p_hwfn, u8 *num_mac_filters)
अणु
	काष्ठा qed_vf_iov *p_vf = p_hwfn->vf_iov_info;

	*num_mac_filters = p_vf->acquire_resp.resc.num_mac_filters;
पूर्ण

bool qed_vf_check_mac(काष्ठा qed_hwfn *p_hwfn, u8 *mac)
अणु
	काष्ठा qed_bulletin_content *bulletin;

	bulletin = &p_hwfn->vf_iov_info->bulletin_shaकरोw;
	अगर (!(bulletin->valid_biपंचांगap & (1 << MAC_ADDR_FORCED)))
		वापस true;

	/* Forbid VF from changing a MAC enक्रमced by PF */
	अगर (ether_addr_equal(bulletin->mac, mac))
		वापस false;

	वापस false;
पूर्ण

अटल bool qed_vf_bulletin_get_क्रमced_mac(काष्ठा qed_hwfn *hwfn,
					   u8 *dst_mac, u8 *p_is_क्रमced)
अणु
	काष्ठा qed_bulletin_content *bulletin;

	bulletin = &hwfn->vf_iov_info->bulletin_shaकरोw;

	अगर (bulletin->valid_biपंचांगap & (1 << MAC_ADDR_FORCED)) अणु
		अगर (p_is_क्रमced)
			*p_is_क्रमced = 1;
	पूर्ण अन्यथा अगर (bulletin->valid_biपंचांगap & (1 << VFPF_BULLETIN_MAC_ADDR)) अणु
		अगर (p_is_क्रमced)
			*p_is_क्रमced = 0;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण

	ether_addr_copy(dst_mac, bulletin->mac);

	वापस true;
पूर्ण

अटल व्योम
qed_vf_bulletin_get_udp_ports(काष्ठा qed_hwfn *p_hwfn,
			      u16 *p_vxlan_port, u16 *p_geneve_port)
अणु
	काष्ठा qed_bulletin_content *p_bulletin;

	p_bulletin = &p_hwfn->vf_iov_info->bulletin_shaकरोw;

	*p_vxlan_port = p_bulletin->vxlan_udp_port;
	*p_geneve_port = p_bulletin->geneve_udp_port;
पूर्ण

व्योम qed_vf_get_fw_version(काष्ठा qed_hwfn *p_hwfn,
			   u16 *fw_major, u16 *fw_minor,
			   u16 *fw_rev, u16 *fw_eng)
अणु
	काष्ठा pf_vf_pfdev_info *info;

	info = &p_hwfn->vf_iov_info->acquire_resp.pfdev_info;

	*fw_major = info->fw_major;
	*fw_minor = info->fw_minor;
	*fw_rev = info->fw_rev;
	*fw_eng = info->fw_eng;
पूर्ण

अटल व्योम qed_handle_bulletin_change(काष्ठा qed_hwfn *hwfn)
अणु
	काष्ठा qed_eth_cb_ops *ops = hwfn->cdev->protocol_ops.eth;
	u8 mac[ETH_ALEN], is_mac_exist, is_mac_क्रमced;
	व्योम *cookie = hwfn->cdev->ops_cookie;
	u16 vxlan_port, geneve_port;

	qed_vf_bulletin_get_udp_ports(hwfn, &vxlan_port, &geneve_port);
	is_mac_exist = qed_vf_bulletin_get_क्रमced_mac(hwfn, mac,
						      &is_mac_क्रमced);
	अगर (is_mac_exist && cookie)
		ops->क्रमce_mac(cookie, mac, !!is_mac_क्रमced);

	ops->ports_update(cookie, vxlan_port, geneve_port);

	/* Always update link configuration according to bulletin */
	qed_link_update(hwfn, शून्य);
पूर्ण

व्योम qed_iov_vf_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qed_hwfn *hwfn = container_of(work, काष्ठा qed_hwfn,
					     iov_task.work);
	u8 change = 0;

	अगर (test_and_clear_bit(QED_IOV_WQ_STOP_WQ_FLAG, &hwfn->iov_task_flags))
		वापस;

	/* Handle bulletin board changes */
	qed_vf_पढ़ो_bulletin(hwfn, &change);
	अगर (test_and_clear_bit(QED_IOV_WQ_VF_FORCE_LINK_QUERY_FLAG,
			       &hwfn->iov_task_flags))
		change = 1;
	अगर (change)
		qed_handle_bulletin_change(hwfn);

	/* As VF is polling bulletin board, need to स्थिरantly re-schedule */
	queue_delayed_work(hwfn->iov_wq, &hwfn->iov_task, HZ);
पूर्ण
