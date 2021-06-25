<शैली गुरु>
/* bnx2x_vfpf.c: QLogic Everest network driver.
 *
 * Copyright 2009-2013 Broadcom Corporation
 * Copyright 2014 QLogic Corporation
 * All rights reserved
 *
 * Unless you and QLogic execute a separate written software license
 * agreement governing use of this software, this software is licensed to you
 * under the terms of the GNU General Public License version 2, available
 * at http://www.gnu.org/licenses/old-licenses/gpl-2.0.hपंचांगl (the "GPL").
 *
 * Notwithstanding the above, under no circumstances may you combine this
 * software in any way with any other QLogic software provided under a
 * license other than the GPL, without QLogic's express prior written
 * consent.
 *
 * Maपूर्णांकained by: Ariel Elior <ariel.elior@qlogic.com>
 * Written by: Shmulik Ravid
 *	       Ariel Elior <ariel.elior@qlogic.com>
 */

#समावेश "bnx2x.h"
#समावेश "bnx2x_cmn.h"
#समावेश <linux/crc32.h>

अटल पूर्णांक bnx2x_vfpf_tearकरोwn_queue(काष्ठा bnx2x *bp, पूर्णांक qidx);

/* place a given tlv on the tlv buffer at a given offset */
अटल व्योम bnx2x_add_tlv(काष्ठा bnx2x *bp, व्योम *tlvs_list,
			  u16 offset, u16 type, u16 length)
अणु
	काष्ठा channel_tlv *tl =
		(काष्ठा channel_tlv *)(tlvs_list + offset);

	tl->type = type;
	tl->length = length;
पूर्ण

/* Clear the mailbox and init the header of the first tlv */
अटल व्योम bnx2x_vfpf_prep(काष्ठा bnx2x *bp, काष्ठा vfpf_first_tlv *first_tlv,
			    u16 type, u16 length)
अणु
	mutex_lock(&bp->vf2pf_mutex);

	DP(BNX2X_MSG_IOV, "preparing to send %d tlv over vf pf channel\n",
	   type);

	/* Clear mailbox */
	स_रखो(bp->vf2pf_mbox, 0, माप(काष्ठा bnx2x_vf_mbx_msg));

	/* init type and length */
	bnx2x_add_tlv(bp, &first_tlv->tl, 0, type, length);

	/* init first tlv header */
	first_tlv->resp_msg_offset = माप(bp->vf2pf_mbox->req);
पूर्ण

/* releases the mailbox */
अटल व्योम bnx2x_vfpf_finalize(काष्ठा bnx2x *bp,
				काष्ठा vfpf_first_tlv *first_tlv)
अणु
	DP(BNX2X_MSG_IOV, "done sending [%d] tlv over vf pf channel\n",
	   first_tlv->tl.type);

	mutex_unlock(&bp->vf2pf_mutex);
पूर्ण

/* Finds a TLV by type in a TLV buffer; If found, वापसs poपूर्णांकer to the TLV */
अटल व्योम *bnx2x_search_tlv_list(काष्ठा bnx2x *bp, व्योम *tlvs_list,
				   क्रमागत channel_tlvs req_tlv)
अणु
	काष्ठा channel_tlv *tlv = (काष्ठा channel_tlv *)tlvs_list;

	करो अणु
		अगर (tlv->type == req_tlv)
			वापस tlv;

		अगर (!tlv->length) अणु
			BNX2X_ERR("Found TLV with length 0\n");
			वापस शून्य;
		पूर्ण

		tlvs_list += tlv->length;
		tlv = (काष्ठा channel_tlv *)tlvs_list;
	पूर्ण जबतक (tlv->type != CHANNEL_TLV_LIST_END);

	DP(BNX2X_MSG_IOV, "TLV list does not contain %d TLV\n", req_tlv);

	वापस शून्य;
पूर्ण

/* list the types and lengths of the tlvs on the buffer */
अटल व्योम bnx2x_dp_tlv_list(काष्ठा bnx2x *bp, व्योम *tlvs_list)
अणु
	पूर्णांक i = 1;
	काष्ठा channel_tlv *tlv = (काष्ठा channel_tlv *)tlvs_list;

	जबतक (tlv->type != CHANNEL_TLV_LIST_END) अणु
		/* output tlv */
		DP(BNX2X_MSG_IOV, "TLV number %d: type %d, length %d\n", i,
		   tlv->type, tlv->length);

		/* advance to next tlv */
		tlvs_list += tlv->length;

		/* cast general tlv list poपूर्णांकer to channel tlv header*/
		tlv = (काष्ठा channel_tlv *)tlvs_list;

		i++;

		/* अवरोध condition क्रम this loop */
		अगर (i > MAX_TLVS_IN_LIST) अणु
			WARN(true, "corrupt tlvs");
			वापस;
		पूर्ण
	पूर्ण

	/* output last tlv */
	DP(BNX2X_MSG_IOV, "TLV number %d: type %d, length %d\n", i,
	   tlv->type, tlv->length);
पूर्ण

/* test whether we support a tlv type */
bool bnx2x_tlv_supported(u16 tlvtype)
अणु
	वापस CHANNEL_TLV_NONE < tlvtype && tlvtype < CHANNEL_TLV_MAX;
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_pfvf_status_codes(पूर्णांक rc)
अणु
	चयन (rc) अणु
	हाल 0:
		वापस PFVF_STATUS_SUCCESS;
	हाल -ENOMEM:
		वापस PFVF_STATUS_NO_RESOURCE;
	शेष:
		वापस PFVF_STATUS_FAILURE;
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_send_msg2pf(काष्ठा bnx2x *bp, u8 *करोne, dma_addr_t msg_mapping)
अणु
	काष्ठा cstorm_vf_zone_data __iomem *zone_data =
		REG_ADDR(bp, PXP_VF_ADDR_CSDM_GLOBAL_START);
	पूर्णांक tout = 100, पूर्णांकerval = 100; /* रुको क्रम 10 seconds */

	अगर (*करोne) अणु
		BNX2X_ERR("done was non zero before message to pf was sent\n");
		WARN_ON(true);
		वापस -EINVAL;
	पूर्ण

	/* अगर PF indicated channel is करोwn aव्योम sending message. Return success
	 * so calling flow can जारी
	 */
	bnx2x_sample_bulletin(bp);
	अगर (bp->old_bulletin.valid_biपंचांगap & 1 << CHANNEL_DOWN) अणु
		DP(BNX2X_MSG_IOV, "detecting channel down. Aborting message\n");
		*करोne = PFVF_STATUS_SUCCESS;
		वापस -EINVAL;
	पूर्ण

	/* Write message address */
	ग_लिखोl(U64_LO(msg_mapping),
	       &zone_data->non_trigger.vf_pf_channel.msg_addr_lo);
	ग_लिखोl(U64_HI(msg_mapping),
	       &zone_data->non_trigger.vf_pf_channel.msg_addr_hi);

	/* make sure the address is written beक्रमe FW accesses it */
	wmb();

	/* Trigger the PF FW */
	ग_लिखोb_relaxed(1, &zone_data->trigger.vf_pf_channel.addr_valid);

	/* Wait क्रम PF to complete */
	जबतक ((tout >= 0) && (!*करोne)) अणु
		msleep(पूर्णांकerval);
		tout -= 1;

		/* progress indicator - HV can take its own sweet समय in
		 * answering VFs...
		 */
		DP_CONT(BNX2X_MSG_IOV, ".");
	पूर्ण

	अगर (!*करोne) अणु
		BNX2X_ERR("PF response has timed out\n");
		वापस -EAGAIN;
	पूर्ण
	DP(BNX2X_MSG_SP, "Got a response from PF\n");
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_get_vf_id(काष्ठा bnx2x *bp, u32 *vf_id)
अणु
	u32 me_reg;
	पूर्णांक tout = 10, पूर्णांकerval = 100; /* Wait क्रम 1 sec */

	करो अणु
		/* pxp traps vf पढ़ो of करोorbells and वापसs me reg value */
		me_reg = पढ़ोl(bp->करोorbells);
		अगर (GOOD_ME_REG(me_reg))
			अवरोध;

		msleep(पूर्णांकerval);

		BNX2X_ERR("Invalid ME register value: 0x%08x\n. Is pf driver up?",
			  me_reg);
	पूर्ण जबतक (tout-- > 0);

	अगर (!GOOD_ME_REG(me_reg)) अणु
		BNX2X_ERR("Invalid ME register value: 0x%08x\n", me_reg);
		वापस -EINVAL;
	पूर्ण

	DP(BNX2X_MSG_IOV, "valid ME register value: 0x%08x\n", me_reg);

	*vf_id = (me_reg & ME_REG_VF_NUM_MASK) >> ME_REG_VF_NUM_SHIFT;

	वापस 0;
पूर्ण

पूर्णांक bnx2x_vfpf_acquire(काष्ठा bnx2x *bp, u8 tx_count, u8 rx_count)
अणु
	पूर्णांक rc = 0, attempts = 0;
	काष्ठा vfpf_acquire_tlv *req = &bp->vf2pf_mbox->req.acquire;
	काष्ठा pfvf_acquire_resp_tlv *resp = &bp->vf2pf_mbox->resp.acquire_resp;
	काष्ठा vfpf_port_phys_id_resp_tlv *phys_port_resp;
	काष्ठा vfpf_fp_hsi_resp_tlv *fp_hsi_resp;
	u32 vf_id;
	bool resources_acquired = false;

	/* clear mailbox and prep first tlv */
	bnx2x_vfpf_prep(bp, &req->first_tlv, CHANNEL_TLV_ACQUIRE, माप(*req));

	अगर (bnx2x_get_vf_id(bp, &vf_id)) अणु
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	req->vfdev_info.vf_id = vf_id;
	req->vfdev_info.vf_os = 0;
	req->vfdev_info.fp_hsi_ver = ETH_FP_HSI_VERSION;

	req->resc_request.num_rxqs = rx_count;
	req->resc_request.num_txqs = tx_count;
	req->resc_request.num_sbs = bp->igu_sb_cnt;
	req->resc_request.num_mac_filters = VF_ACQUIRE_MAC_FILTERS;
	req->resc_request.num_mc_filters = VF_ACQUIRE_MC_FILTERS;
	req->resc_request.num_vlan_filters = VF_ACQUIRE_VLAN_FILTERS;

	/* pf 2 vf bulletin board address */
	req->bulletin_addr = bp->pf2vf_bulletin_mapping;

	/* Request physical port identअगरier */
	bnx2x_add_tlv(bp, req, req->first_tlv.tl.length,
		      CHANNEL_TLV_PHYS_PORT_ID, माप(काष्ठा channel_tlv));

	/* Bulletin support क्रम bulletin board with length > legacy length */
	req->vfdev_info.caps |= VF_CAP_SUPPORT_EXT_BULLETIN;
	/* vlan filtering is supported */
	req->vfdev_info.caps |= VF_CAP_SUPPORT_VLAN_FILTER;

	/* add list termination tlv */
	bnx2x_add_tlv(bp, req,
		      req->first_tlv.tl.length + माप(काष्ठा channel_tlv),
		      CHANNEL_TLV_LIST_END,
		      माप(काष्ठा channel_list_end_tlv));

	/* output tlvs list */
	bnx2x_dp_tlv_list(bp, req);

	जबतक (!resources_acquired) अणु
		DP(BNX2X_MSG_SP, "attempting to acquire resources\n");

		/* send acquire request */
		rc = bnx2x_send_msg2pf(bp,
				       &resp->hdr.status,
				       bp->vf2pf_mbox_mapping);

		/* PF समयout */
		अगर (rc)
			जाओ out;

		/* copy acquire response from buffer to bp */
		स_नकल(&bp->acquire_resp, resp, माप(bp->acquire_resp));

		attempts++;

		/* test whether the PF accepted our request. If not, humble
		 * the request and try again.
		 */
		अगर (bp->acquire_resp.hdr.status == PFVF_STATUS_SUCCESS) अणु
			DP(BNX2X_MSG_SP, "resources acquired\n");
			resources_acquired = true;
		पूर्ण अन्यथा अगर (bp->acquire_resp.hdr.status ==
			   PFVF_STATUS_NO_RESOURCE &&
			   attempts < VF_ACQUIRE_THRESH) अणु
			DP(BNX2X_MSG_SP,
			   "PF unwilling to fulfill resource request. Try PF recommended amount\n");

			/* humble our request */
			req->resc_request.num_txqs =
				min(req->resc_request.num_txqs,
				    bp->acquire_resp.resc.num_txqs);
			req->resc_request.num_rxqs =
				min(req->resc_request.num_rxqs,
				    bp->acquire_resp.resc.num_rxqs);
			req->resc_request.num_sbs =
				min(req->resc_request.num_sbs,
				    bp->acquire_resp.resc.num_sbs);
			req->resc_request.num_mac_filters =
				min(req->resc_request.num_mac_filters,
				    bp->acquire_resp.resc.num_mac_filters);
			req->resc_request.num_vlan_filters =
				min(req->resc_request.num_vlan_filters,
				    bp->acquire_resp.resc.num_vlan_filters);
			req->resc_request.num_mc_filters =
				min(req->resc_request.num_mc_filters,
				    bp->acquire_resp.resc.num_mc_filters);

			/* Clear response buffer */
			स_रखो(&bp->vf2pf_mbox->resp, 0,
			       माप(जोड़ pfvf_tlvs));
		पूर्ण अन्यथा अणु
			/* Determine reason of PF failure of acquire process */
			fp_hsi_resp = bnx2x_search_tlv_list(bp, resp,
							    CHANNEL_TLV_FP_HSI_SUPPORT);
			अगर (fp_hsi_resp && !fp_hsi_resp->is_supported)
				BNX2X_ERR("Old hypervisor - doesn't support current fastpath HSI version; Need to downgrade VF driver [or upgrade hypervisor]\n");
			अन्यथा
				BNX2X_ERR("Failed to get the requested amount of resources: %d. Breaking...\n",
					  bp->acquire_resp.hdr.status);
			rc = -EAGAIN;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Retrieve physical port id (अगर possible) */
	phys_port_resp = (काष्ठा vfpf_port_phys_id_resp_tlv *)
			 bnx2x_search_tlv_list(bp, resp,
					       CHANNEL_TLV_PHYS_PORT_ID);
	अगर (phys_port_resp) अणु
		स_नकल(bp->phys_port_id, phys_port_resp->id, ETH_ALEN);
		bp->flags |= HAS_PHYS_PORT_ID;
	पूर्ण

	/* Old Hypevisors might not even support the FP_HSI_SUPPORT TLV.
	 * If that's the हाल, we need to make certain required FW was
	 * supported by such a hypervisor [i.e., v0-v2].
	 */
	fp_hsi_resp = bnx2x_search_tlv_list(bp, resp,
					    CHANNEL_TLV_FP_HSI_SUPPORT);
	अगर (!fp_hsi_resp && (ETH_FP_HSI_VERSION > ETH_FP_HSI_VER_2)) अणु
		BNX2X_ERR("Old hypervisor - need to downgrade VF's driver\n");

		/* Since acquire succeeded on the PF side, we need to send a
		 * release message in order to allow future probes.
		 */
		bnx2x_vfpf_finalize(bp, &req->first_tlv);
		bnx2x_vfpf_release(bp);

		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/* get HW info */
	bp->common.chip_id |= (bp->acquire_resp.pfdev_info.chip_num & 0xffff);
	bp->link_params.chip_id = bp->common.chip_id;
	bp->db_size = bp->acquire_resp.pfdev_info.db_size;
	bp->common.पूर्णांक_block = INT_BLOCK_IGU;
	bp->common.chip_port_mode = CHIP_2_PORT_MODE;
	bp->igu_dsb_id = -1;
	bp->mf_ov = 0;
	bp->mf_mode = 0;
	bp->common.flash_size = 0;
	bp->flags |=
		NO_WOL_FLAG | NO_ISCSI_OOO_FLAG | NO_ISCSI_FLAG | NO_FCOE_FLAG;
	bp->igu_sb_cnt = bp->acquire_resp.resc.num_sbs;
	bp->igu_base_sb = bp->acquire_resp.resc.hw_sbs[0].hw_sb_id;
	bp->vlan_credit = bp->acquire_resp.resc.num_vlan_filters;

	strlcpy(bp->fw_ver, bp->acquire_resp.pfdev_info.fw_ver,
		माप(bp->fw_ver));

	अगर (is_valid_ether_addr(bp->acquire_resp.resc.current_mac_addr))
		स_नकल(bp->dev->dev_addr,
		       bp->acquire_resp.resc.current_mac_addr,
		       ETH_ALEN);

out:
	bnx2x_vfpf_finalize(bp, &req->first_tlv);
	वापस rc;
पूर्ण

पूर्णांक bnx2x_vfpf_release(काष्ठा bnx2x *bp)
अणु
	काष्ठा vfpf_release_tlv *req = &bp->vf2pf_mbox->req.release;
	काष्ठा pfvf_general_resp_tlv *resp = &bp->vf2pf_mbox->resp.general_resp;
	u32 rc, vf_id;

	/* clear mailbox and prep first tlv */
	bnx2x_vfpf_prep(bp, &req->first_tlv, CHANNEL_TLV_RELEASE, माप(*req));

	अगर (bnx2x_get_vf_id(bp, &vf_id)) अणु
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	req->vf_id = vf_id;

	/* add list termination tlv */
	bnx2x_add_tlv(bp, req, req->first_tlv.tl.length, CHANNEL_TLV_LIST_END,
		      माप(काष्ठा channel_list_end_tlv));

	/* output tlvs list */
	bnx2x_dp_tlv_list(bp, req);

	/* send release request */
	rc = bnx2x_send_msg2pf(bp, &resp->hdr.status, bp->vf2pf_mbox_mapping);

	अगर (rc)
		/* PF समयout */
		जाओ out;

	अगर (resp->hdr.status == PFVF_STATUS_SUCCESS) अणु
		/* PF released us */
		DP(BNX2X_MSG_SP, "vf released\n");
	पूर्ण अन्यथा अणु
		/* PF reports error */
		BNX2X_ERR("PF failed our release request - are we out of sync? Response status: %d\n",
			  resp->hdr.status);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण
out:
	bnx2x_vfpf_finalize(bp, &req->first_tlv);

	वापस rc;
पूर्ण

/* Tell PF about SB addresses */
पूर्णांक bnx2x_vfpf_init(काष्ठा bnx2x *bp)
अणु
	काष्ठा vfpf_init_tlv *req = &bp->vf2pf_mbox->req.init;
	काष्ठा pfvf_general_resp_tlv *resp = &bp->vf2pf_mbox->resp.general_resp;
	पूर्णांक rc, i;

	/* clear mailbox and prep first tlv */
	bnx2x_vfpf_prep(bp, &req->first_tlv, CHANNEL_TLV_INIT, माप(*req));

	/* status blocks */
	क्रम_each_eth_queue(bp, i)
		req->sb_addr[i] = (dma_addr_t)bnx2x_fp(bp, i,
						       status_blk_mapping);

	/* statistics - requests only supports single queue क्रम now */
	req->stats_addr = bp->fw_stats_data_mapping +
			  दुरत्व(काष्ठा bnx2x_fw_stats_data, queue_stats);

	req->stats_stride = माप(काष्ठा per_queue_stats);

	/* add list termination tlv */
	bnx2x_add_tlv(bp, req, req->first_tlv.tl.length, CHANNEL_TLV_LIST_END,
		      माप(काष्ठा channel_list_end_tlv));

	/* output tlvs list */
	bnx2x_dp_tlv_list(bp, req);

	rc = bnx2x_send_msg2pf(bp, &resp->hdr.status, bp->vf2pf_mbox_mapping);
	अगर (rc)
		जाओ out;

	अगर (resp->hdr.status != PFVF_STATUS_SUCCESS) अणु
		BNX2X_ERR("INIT VF failed: %d. Breaking...\n",
			  resp->hdr.status);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	DP(BNX2X_MSG_SP, "INIT VF Succeeded\n");
out:
	bnx2x_vfpf_finalize(bp, &req->first_tlv);

	वापस rc;
पूर्ण

/* CLOSE VF - opposite to INIT_VF */
व्योम bnx2x_vfpf_बंद_vf(काष्ठा bnx2x *bp)
अणु
	काष्ठा vfpf_बंद_tlv *req = &bp->vf2pf_mbox->req.बंद;
	काष्ठा pfvf_general_resp_tlv *resp = &bp->vf2pf_mbox->resp.general_resp;
	पूर्णांक i, rc;
	u32 vf_id;

	/* If we haven't got a valid VF id, there is no sense to
	 * जारी with sending messages
	 */
	अगर (bnx2x_get_vf_id(bp, &vf_id))
		जाओ मुक्त_irq;

	/* Close the queues */
	क्रम_each_queue(bp, i)
		bnx2x_vfpf_tearकरोwn_queue(bp, i);

	/* हटाओ mac */
	bnx2x_vfpf_config_mac(bp, bp->dev->dev_addr, bp->fp->index, false);

	/* clear mailbox and prep first tlv */
	bnx2x_vfpf_prep(bp, &req->first_tlv, CHANNEL_TLV_CLOSE, माप(*req));

	req->vf_id = vf_id;

	/* add list termination tlv */
	bnx2x_add_tlv(bp, req, req->first_tlv.tl.length, CHANNEL_TLV_LIST_END,
		      माप(काष्ठा channel_list_end_tlv));

	/* output tlvs list */
	bnx2x_dp_tlv_list(bp, req);

	rc = bnx2x_send_msg2pf(bp, &resp->hdr.status, bp->vf2pf_mbox_mapping);

	अगर (rc)
		BNX2X_ERR("Sending CLOSE failed. rc was: %d\n", rc);

	अन्यथा अगर (resp->hdr.status != PFVF_STATUS_SUCCESS)
		BNX2X_ERR("Sending CLOSE failed: pf response was %d\n",
			  resp->hdr.status);

	bnx2x_vfpf_finalize(bp, &req->first_tlv);

मुक्त_irq:
	/* Disable HW पूर्णांकerrupts, NAPI */
	bnx2x_netअगर_stop(bp, 0);
	/* Delete all NAPI objects */
	bnx2x_del_all_napi(bp);

	/* Release IRQs */
	bnx2x_मुक्त_irq(bp);
पूर्ण

अटल व्योम bnx2x_leading_vfq_init(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
				   काष्ठा bnx2x_vf_queue *q)
अणु
	u8 cl_id = vfq_cl_id(vf, q);
	u8 func_id = FW_VF_HANDLE(vf->असल_vfid);

	/* mac */
	bnx2x_init_mac_obj(bp, &q->mac_obj,
			   cl_id, q->cid, func_id,
			   bnx2x_vf_sp(bp, vf, mac_rdata),
			   bnx2x_vf_sp_map(bp, vf, mac_rdata),
			   BNX2X_FILTER_MAC_PENDING,
			   &vf->filter_state,
			   BNX2X_OBJ_TYPE_RX_TX,
			   &vf->vf_macs_pool);
	/* vlan */
	bnx2x_init_vlan_obj(bp, &q->vlan_obj,
			    cl_id, q->cid, func_id,
			    bnx2x_vf_sp(bp, vf, vlan_rdata),
			    bnx2x_vf_sp_map(bp, vf, vlan_rdata),
			    BNX2X_FILTER_VLAN_PENDING,
			    &vf->filter_state,
			    BNX2X_OBJ_TYPE_RX_TX,
			    &vf->vf_vlans_pool);
	/* vlan-mac */
	bnx2x_init_vlan_mac_obj(bp, &q->vlan_mac_obj,
				cl_id, q->cid, func_id,
				bnx2x_vf_sp(bp, vf, vlan_mac_rdata),
				bnx2x_vf_sp_map(bp, vf, vlan_mac_rdata),
				BNX2X_FILTER_VLAN_MAC_PENDING,
				&vf->filter_state,
				BNX2X_OBJ_TYPE_RX_TX,
				&vf->vf_macs_pool,
				&vf->vf_vlans_pool);
	/* mcast */
	bnx2x_init_mcast_obj(bp, &vf->mcast_obj, cl_id,
			     q->cid, func_id, func_id,
			     bnx2x_vf_sp(bp, vf, mcast_rdata),
			     bnx2x_vf_sp_map(bp, vf, mcast_rdata),
			     BNX2X_FILTER_MCAST_PENDING,
			     &vf->filter_state,
			     BNX2X_OBJ_TYPE_RX_TX);

	/* rss */
	bnx2x_init_rss_config_obj(bp, &vf->rss_conf_obj, cl_id, q->cid,
				  func_id, func_id,
				  bnx2x_vf_sp(bp, vf, rss_rdata),
				  bnx2x_vf_sp_map(bp, vf, rss_rdata),
				  BNX2X_FILTER_RSS_CONF_PENDING,
				  &vf->filter_state,
				  BNX2X_OBJ_TYPE_RX_TX);

	vf->leading_rss = cl_id;
	q->is_leading = true;
	q->sp_initialized = true;
पूर्ण

/* ask the pf to खोलो a queue क्रम the vf */
पूर्णांक bnx2x_vfpf_setup_q(काष्ठा bnx2x *bp, काष्ठा bnx2x_fastpath *fp,
		       bool is_leading)
अणु
	काष्ठा vfpf_setup_q_tlv *req = &bp->vf2pf_mbox->req.setup_q;
	काष्ठा pfvf_general_resp_tlv *resp = &bp->vf2pf_mbox->resp.general_resp;
	u8 fp_idx = fp->index;
	u16 tpa_agg_size = 0, flags = 0;
	पूर्णांक rc;

	/* clear mailbox and prep first tlv */
	bnx2x_vfpf_prep(bp, &req->first_tlv, CHANNEL_TLV_SETUP_Q, माप(*req));

	/* select tpa mode to request */
	अगर (fp->mode != TPA_MODE_DISABLED) अणु
		flags |= VFPF_QUEUE_FLG_TPA;
		flags |= VFPF_QUEUE_FLG_TPA_IPV6;
		अगर (fp->mode == TPA_MODE_GRO)
			flags |= VFPF_QUEUE_FLG_TPA_GRO;
		tpa_agg_size = TPA_AGG_SIZE;
	पूर्ण

	अगर (is_leading)
		flags |= VFPF_QUEUE_FLG_LEADING_RSS;

	/* calculate queue flags */
	flags |= VFPF_QUEUE_FLG_STATS;
	flags |= VFPF_QUEUE_FLG_CACHE_ALIGN;
	flags |= VFPF_QUEUE_FLG_VLAN;

	/* Common */
	req->vf_qid = fp_idx;
	req->param_valid = VFPF_RXQ_VALID | VFPF_TXQ_VALID;

	/* Rx */
	req->rxq.rcq_addr = fp->rx_comp_mapping;
	req->rxq.rcq_np_addr = fp->rx_comp_mapping + BCM_PAGE_SIZE;
	req->rxq.rxq_addr = fp->rx_desc_mapping;
	req->rxq.sge_addr = fp->rx_sge_mapping;
	req->rxq.vf_sb = fp_idx;
	req->rxq.sb_index = HC_INDEX_ETH_RX_CQ_CONS;
	req->rxq.hc_rate = bp->rx_ticks ? 1000000/bp->rx_ticks : 0;
	req->rxq.mtu = bp->dev->mtu;
	req->rxq.buf_sz = fp->rx_buf_size;
	req->rxq.sge_buf_sz = BCM_PAGE_SIZE * PAGES_PER_SGE;
	req->rxq.tpa_agg_sz = tpa_agg_size;
	req->rxq.max_sge_pkt = SGE_PAGE_ALIGN(bp->dev->mtu) >> SGE_PAGE_SHIFT;
	req->rxq.max_sge_pkt = ((req->rxq.max_sge_pkt + PAGES_PER_SGE - 1) &
			  (~(PAGES_PER_SGE-1))) >> PAGES_PER_SGE_SHIFT;
	req->rxq.flags = flags;
	req->rxq.drop_flags = 0;
	req->rxq.cache_line_log = BNX2X_RX_ALIGN_SHIFT;
	req->rxq.stat_id = -1; /* No stats at the moment */

	/* Tx */
	req->txq.txq_addr = fp->txdata_ptr[FIRST_TX_COS_INDEX]->tx_desc_mapping;
	req->txq.vf_sb = fp_idx;
	req->txq.sb_index = HC_INDEX_ETH_TX_CQ_CONS_COS0;
	req->txq.hc_rate = bp->tx_ticks ? 1000000/bp->tx_ticks : 0;
	req->txq.flags = flags;
	req->txq.traffic_type = LLFC_TRAFFIC_TYPE_NW;

	/* add list termination tlv */
	bnx2x_add_tlv(bp, req, req->first_tlv.tl.length, CHANNEL_TLV_LIST_END,
		      माप(काष्ठा channel_list_end_tlv));

	/* output tlvs list */
	bnx2x_dp_tlv_list(bp, req);

	rc = bnx2x_send_msg2pf(bp, &resp->hdr.status, bp->vf2pf_mbox_mapping);
	अगर (rc)
		BNX2X_ERR("Sending SETUP_Q message for queue[%d] failed!\n",
			  fp_idx);

	अगर (resp->hdr.status != PFVF_STATUS_SUCCESS) अणु
		BNX2X_ERR("Status of SETUP_Q for queue[%d] is %d\n",
			  fp_idx, resp->hdr.status);
		rc = -EINVAL;
	पूर्ण

	bnx2x_vfpf_finalize(bp, &req->first_tlv);

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_vfpf_tearकरोwn_queue(काष्ठा bnx2x *bp, पूर्णांक qidx)
अणु
	काष्ठा vfpf_q_op_tlv *req = &bp->vf2pf_mbox->req.q_op;
	काष्ठा pfvf_general_resp_tlv *resp = &bp->vf2pf_mbox->resp.general_resp;
	पूर्णांक rc;

	/* clear mailbox and prep first tlv */
	bnx2x_vfpf_prep(bp, &req->first_tlv, CHANNEL_TLV_TEARDOWN_Q,
			माप(*req));

	req->vf_qid = qidx;

	/* add list termination tlv */
	bnx2x_add_tlv(bp, req, req->first_tlv.tl.length, CHANNEL_TLV_LIST_END,
		      माप(काष्ठा channel_list_end_tlv));

	/* output tlvs list */
	bnx2x_dp_tlv_list(bp, req);

	rc = bnx2x_send_msg2pf(bp, &resp->hdr.status, bp->vf2pf_mbox_mapping);

	अगर (rc) अणु
		BNX2X_ERR("Sending TEARDOWN for queue %d failed: %d\n", qidx,
			  rc);
		जाओ out;
	पूर्ण

	/* PF failed the transaction */
	अगर (resp->hdr.status != PFVF_STATUS_SUCCESS) अणु
		BNX2X_ERR("TEARDOWN for queue %d failed: %d\n", qidx,
			  resp->hdr.status);
		rc = -EINVAL;
	पूर्ण

out:
	bnx2x_vfpf_finalize(bp, &req->first_tlv);

	वापस rc;
पूर्ण

/* request pf to add a mac क्रम the vf */
पूर्णांक bnx2x_vfpf_config_mac(काष्ठा bnx2x *bp, u8 *addr, u8 vf_qid, bool set)
अणु
	काष्ठा vfpf_set_q_filters_tlv *req = &bp->vf2pf_mbox->req.set_q_filters;
	काष्ठा pfvf_general_resp_tlv *resp = &bp->vf2pf_mbox->resp.general_resp;
	काष्ठा pf_vf_bulletin_content bulletin = bp->pf2vf_bulletin->content;
	पूर्णांक rc = 0;

	/* clear mailbox and prep first tlv */
	bnx2x_vfpf_prep(bp, &req->first_tlv, CHANNEL_TLV_SET_Q_FILTERS,
			माप(*req));

	req->flags = VFPF_SET_Q_FILTERS_MAC_VLAN_CHANGED;
	req->vf_qid = vf_qid;
	req->n_mac_vlan_filters = 1;

	req->filters[0].flags = VFPF_Q_FILTER_DEST_MAC_VALID;
	अगर (set)
		req->filters[0].flags |= VFPF_Q_FILTER_SET;

	/* sample bulletin board क्रम new mac */
	bnx2x_sample_bulletin(bp);

	/* copy mac from device to request */
	स_नकल(req->filters[0].mac, addr, ETH_ALEN);

	/* add list termination tlv */
	bnx2x_add_tlv(bp, req, req->first_tlv.tl.length, CHANNEL_TLV_LIST_END,
		      माप(काष्ठा channel_list_end_tlv));

	/* output tlvs list */
	bnx2x_dp_tlv_list(bp, req);

	/* send message to pf */
	rc = bnx2x_send_msg2pf(bp, &resp->hdr.status, bp->vf2pf_mbox_mapping);
	अगर (rc) अणु
		BNX2X_ERR("failed to send message to pf. rc was %d\n", rc);
		जाओ out;
	पूर्ण

	/* failure may mean PF was configured with a new mac क्रम us */
	जबतक (resp->hdr.status == PFVF_STATUS_FAILURE) अणु
		DP(BNX2X_MSG_IOV,
		   "vfpf SET MAC failed. Check bulletin board for new posts\n");

		/* copy mac from bulletin to device */
		स_नकल(bp->dev->dev_addr, bulletin.mac, ETH_ALEN);

		/* check अगर bulletin board was updated */
		अगर (bnx2x_sample_bulletin(bp) == PFVF_BULLETIN_UPDATED) अणु
			/* copy mac from device to request */
			स_नकल(req->filters[0].mac, bp->dev->dev_addr,
			       ETH_ALEN);

			/* send message to pf */
			rc = bnx2x_send_msg2pf(bp, &resp->hdr.status,
					       bp->vf2pf_mbox_mapping);
		पूर्ण अन्यथा अणु
			/* no new info in bulletin */
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (resp->hdr.status != PFVF_STATUS_SUCCESS) अणु
		BNX2X_ERR("vfpf SET MAC failed: %d\n", resp->hdr.status);
		rc = -EINVAL;
	पूर्ण
out:
	bnx2x_vfpf_finalize(bp, &req->first_tlv);

	वापस rc;
पूर्ण

/* request pf to config rss table क्रम vf queues*/
पूर्णांक bnx2x_vfpf_config_rss(काष्ठा bnx2x *bp,
			  काष्ठा bnx2x_config_rss_params *params)
अणु
	काष्ठा pfvf_general_resp_tlv *resp = &bp->vf2pf_mbox->resp.general_resp;
	काष्ठा vfpf_rss_tlv *req = &bp->vf2pf_mbox->req.update_rss;
	पूर्णांक rc = 0;

	/* clear mailbox and prep first tlv */
	bnx2x_vfpf_prep(bp, &req->first_tlv, CHANNEL_TLV_UPDATE_RSS,
			माप(*req));

	/* add list termination tlv */
	bnx2x_add_tlv(bp, req, req->first_tlv.tl.length, CHANNEL_TLV_LIST_END,
		      माप(काष्ठा channel_list_end_tlv));

	स_नकल(req->ind_table, params->ind_table, T_ETH_INसूचीECTION_TABLE_SIZE);
	स_नकल(req->rss_key, params->rss_key, माप(params->rss_key));
	req->ind_table_size = T_ETH_INसूचीECTION_TABLE_SIZE;
	req->rss_key_size = T_ETH_RSS_KEY;
	req->rss_result_mask = params->rss_result_mask;

	/* flags handled inभागidually क्रम backward/क्रमward compatibility */
	अगर (params->rss_flags & (1 << BNX2X_RSS_MODE_DISABLED))
		req->rss_flags |= VFPF_RSS_MODE_DISABLED;
	अगर (params->rss_flags & (1 << BNX2X_RSS_MODE_REGULAR))
		req->rss_flags |= VFPF_RSS_MODE_REGULAR;
	अगर (params->rss_flags & (1 << BNX2X_RSS_SET_SRCH))
		req->rss_flags |= VFPF_RSS_SET_SRCH;
	अगर (params->rss_flags & (1 << BNX2X_RSS_IPV4))
		req->rss_flags |= VFPF_RSS_IPV4;
	अगर (params->rss_flags & (1 << BNX2X_RSS_IPV4_TCP))
		req->rss_flags |= VFPF_RSS_IPV4_TCP;
	अगर (params->rss_flags & (1 << BNX2X_RSS_IPV4_UDP))
		req->rss_flags |= VFPF_RSS_IPV4_UDP;
	अगर (params->rss_flags & (1 << BNX2X_RSS_IPV6))
		req->rss_flags |= VFPF_RSS_IPV6;
	अगर (params->rss_flags & (1 << BNX2X_RSS_IPV6_TCP))
		req->rss_flags |= VFPF_RSS_IPV6_TCP;
	अगर (params->rss_flags & (1 << BNX2X_RSS_IPV6_UDP))
		req->rss_flags |= VFPF_RSS_IPV6_UDP;

	DP(BNX2X_MSG_IOV, "rss flags %x\n", req->rss_flags);

	/* output tlvs list */
	bnx2x_dp_tlv_list(bp, req);

	/* send message to pf */
	rc = bnx2x_send_msg2pf(bp, &resp->hdr.status, bp->vf2pf_mbox_mapping);
	अगर (rc) अणु
		BNX2X_ERR("failed to send message to pf. rc was %d\n", rc);
		जाओ out;
	पूर्ण

	अगर (resp->hdr.status != PFVF_STATUS_SUCCESS) अणु
		/* Since older drivers करोn't support this feature (and VF has
		 * no way of knowing other than failing this), करोn't propagate
		 * an error in this हाल.
		 */
		DP(BNX2X_MSG_IOV,
		   "Failed to send rss message to PF over VF-PF channel [%d]\n",
		   resp->hdr.status);
	पूर्ण
out:
	bnx2x_vfpf_finalize(bp, &req->first_tlv);

	वापस rc;
पूर्ण

पूर्णांक bnx2x_vfpf_set_mcast(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	काष्ठा vfpf_set_q_filters_tlv *req = &bp->vf2pf_mbox->req.set_q_filters;
	काष्ठा pfvf_general_resp_tlv *resp = &bp->vf2pf_mbox->resp.general_resp;
	पूर्णांक rc = 0, i = 0;
	काष्ठा netdev_hw_addr *ha;

	अगर (bp->state != BNX2X_STATE_OPEN) अणु
		DP(NETIF_MSG_IFUP, "state is %x, returning\n", bp->state);
		वापस -EINVAL;
	पूर्ण

	/* clear mailbox and prep first tlv */
	bnx2x_vfpf_prep(bp, &req->first_tlv, CHANNEL_TLV_SET_Q_FILTERS,
			माप(*req));

	/* Get Rx mode requested */
	DP(NETIF_MSG_IFUP, "dev->flags = %x\n", dev->flags);

	/* We support PFVF_MAX_MULTICAST_PER_VF mcast addresses tops */
	अगर (netdev_mc_count(dev) > PFVF_MAX_MULTICAST_PER_VF) अणु
		DP(NETIF_MSG_IFUP,
		   "VF supports not more than %d multicast MAC addresses\n",
		   PFVF_MAX_MULTICAST_PER_VF);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	netdev_क्रम_each_mc_addr(ha, dev) अणु
		DP(NETIF_MSG_IFUP, "Adding mcast MAC: %pM\n",
		   bnx2x_mc_addr(ha));
		स_नकल(req->multicast[i], bnx2x_mc_addr(ha), ETH_ALEN);
		i++;
	पूर्ण

	req->n_multicast = i;
	req->flags |= VFPF_SET_Q_FILTERS_MULTICAST_CHANGED;
	req->vf_qid = 0;

	/* add list termination tlv */
	bnx2x_add_tlv(bp, req, req->first_tlv.tl.length, CHANNEL_TLV_LIST_END,
		      माप(काष्ठा channel_list_end_tlv));

	/* output tlvs list */
	bnx2x_dp_tlv_list(bp, req);
	rc = bnx2x_send_msg2pf(bp, &resp->hdr.status, bp->vf2pf_mbox_mapping);
	अगर (rc) अणु
		BNX2X_ERR("Sending a message failed: %d\n", rc);
		जाओ out;
	पूर्ण

	अगर (resp->hdr.status != PFVF_STATUS_SUCCESS) अणु
		BNX2X_ERR("Set Rx mode/multicast failed: %d\n",
			  resp->hdr.status);
		rc = -EINVAL;
	पूर्ण
out:
	bnx2x_vfpf_finalize(bp, &req->first_tlv);

	वापस rc;
पूर्ण

/* request pf to add a vlan क्रम the vf */
पूर्णांक bnx2x_vfpf_update_vlan(काष्ठा bnx2x *bp, u16 vid, u8 vf_qid, bool add)
अणु
	काष्ठा vfpf_set_q_filters_tlv *req = &bp->vf2pf_mbox->req.set_q_filters;
	काष्ठा pfvf_general_resp_tlv *resp = &bp->vf2pf_mbox->resp.general_resp;
	पूर्णांक rc = 0;

	अगर (!(bp->acquire_resp.pfdev_info.pf_cap & PFVF_CAP_VLAN_FILTER)) अणु
		DP(BNX2X_MSG_IOV, "HV does not support vlan filtering\n");
		वापस 0;
	पूर्ण

	/* clear mailbox and prep first tlv */
	bnx2x_vfpf_prep(bp, &req->first_tlv, CHANNEL_TLV_SET_Q_FILTERS,
			माप(*req));

	req->flags = VFPF_SET_Q_FILTERS_MAC_VLAN_CHANGED;
	req->vf_qid = vf_qid;
	req->n_mac_vlan_filters = 1;

	req->filters[0].flags = VFPF_Q_FILTER_VLAN_TAG_VALID;

	अगर (add)
		req->filters[0].flags |= VFPF_Q_FILTER_SET;

	/* sample bulletin board क्रम hypervisor vlan */
	bnx2x_sample_bulletin(bp);

	अगर (bp->shaकरोw_bulletin.content.valid_biपंचांगap & 1 << VLAN_VALID) अणु
		BNX2X_ERR("Hypervisor will decline the request, avoiding\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	req->filters[0].vlan_tag = vid;

	/* add list termination tlv */
	bnx2x_add_tlv(bp, req, req->first_tlv.tl.length, CHANNEL_TLV_LIST_END,
		      माप(काष्ठा channel_list_end_tlv));

	/* output tlvs list */
	bnx2x_dp_tlv_list(bp, req);

	/* send message to pf */
	rc = bnx2x_send_msg2pf(bp, &resp->hdr.status, bp->vf2pf_mbox_mapping);
	अगर (rc) अणु
		BNX2X_ERR("failed to send message to pf. rc was %d\n", rc);
		जाओ out;
	पूर्ण

	अगर (resp->hdr.status != PFVF_STATUS_SUCCESS) अणु
		BNX2X_ERR("vfpf %s VLAN %d failed\n", add ? "add" : "del",
			  vid);
		rc = -EINVAL;
	पूर्ण
out:
	bnx2x_vfpf_finalize(bp, &req->first_tlv);

	वापस rc;
पूर्ण

पूर्णांक bnx2x_vfpf_storm_rx_mode(काष्ठा bnx2x *bp)
अणु
	पूर्णांक mode = bp->rx_mode;
	काष्ठा vfpf_set_q_filters_tlv *req = &bp->vf2pf_mbox->req.set_q_filters;
	काष्ठा pfvf_general_resp_tlv *resp = &bp->vf2pf_mbox->resp.general_resp;
	पूर्णांक rc;

	/* clear mailbox and prep first tlv */
	bnx2x_vfpf_prep(bp, &req->first_tlv, CHANNEL_TLV_SET_Q_FILTERS,
			माप(*req));

	DP(NETIF_MSG_IFUP, "Rx mode is %d\n", mode);

	/* Ignore everything accept MODE_NONE */
	अगर (mode  == BNX2X_RX_MODE_NONE) अणु
		req->rx_mask = VFPF_RX_MASK_ACCEPT_NONE;
	पूर्ण अन्यथा अणु
		/* Current PF driver will not look at the specअगरic flags,
		 * but they are required when working with older drivers on hv.
		 */
		req->rx_mask = VFPF_RX_MASK_ACCEPT_MATCHED_MULTICAST;
		req->rx_mask |= VFPF_RX_MASK_ACCEPT_MATCHED_UNICAST;
		req->rx_mask |= VFPF_RX_MASK_ACCEPT_BROADCAST;
		अगर (mode == BNX2X_RX_MODE_PROMISC)
			req->rx_mask |= VFPF_RX_MASK_ACCEPT_ANY_VLAN;
	पूर्ण

	अगर (bp->accept_any_vlan)
		req->rx_mask |= VFPF_RX_MASK_ACCEPT_ANY_VLAN;

	req->flags |= VFPF_SET_Q_FILTERS_RX_MASK_CHANGED;
	req->vf_qid = 0;

	/* add list termination tlv */
	bnx2x_add_tlv(bp, req, req->first_tlv.tl.length, CHANNEL_TLV_LIST_END,
		      माप(काष्ठा channel_list_end_tlv));

	/* output tlvs list */
	bnx2x_dp_tlv_list(bp, req);

	rc = bnx2x_send_msg2pf(bp, &resp->hdr.status, bp->vf2pf_mbox_mapping);
	अगर (rc)
		BNX2X_ERR("Sending a message failed: %d\n", rc);

	अगर (resp->hdr.status != PFVF_STATUS_SUCCESS) अणु
		BNX2X_ERR("Set Rx mode failed: %d\n", resp->hdr.status);
		rc = -EINVAL;
	पूर्ण

	bnx2x_vfpf_finalize(bp, &req->first_tlv);

	वापस rc;
पूर्ण

/* General service functions */
अटल व्योम storm_स_रखो_vf_mbx_ack(काष्ठा bnx2x *bp, u16 असल_fid)
अणु
	u32 addr = BAR_CSTRORM_INTMEM +
		   CSTORM_VF_PF_CHANNEL_STATE_OFFSET(असल_fid);

	REG_WR8(bp, addr, VF_PF_CHANNEL_STATE_READY);
पूर्ण

अटल व्योम storm_स_रखो_vf_mbx_valid(काष्ठा bnx2x *bp, u16 असल_fid)
अणु
	u32 addr = BAR_CSTRORM_INTMEM +
		   CSTORM_VF_PF_CHANNEL_VALID_OFFSET(असल_fid);

	REG_WR8(bp, addr, 1);
पूर्ण

/* enable vf_pf mailbox (aka vf-pf-channel) */
व्योम bnx2x_vf_enable_mbx(काष्ठा bnx2x *bp, u8 असल_vfid)
अणु
	bnx2x_vf_flr_clnup_epilog(bp, असल_vfid);

	/* enable the mailbox in the FW */
	storm_स_रखो_vf_mbx_ack(bp, असल_vfid);
	storm_स_रखो_vf_mbx_valid(bp, असल_vfid);

	/* enable the VF access to the mailbox */
	bnx2x_vf_enable_access(bp, असल_vfid);
पूर्ण

/* this works only on !E1h */
अटल पूर्णांक bnx2x_copy32_vf_dmae(काष्ठा bnx2x *bp, u8 from_vf,
				dma_addr_t pf_addr, u8 vfid, u32 vf_addr_hi,
				u32 vf_addr_lo, u32 len32)
अणु
	काष्ठा dmae_command dmae;

	अगर (CHIP_IS_E1x(bp)) अणु
		BNX2X_ERR("Chip revision does not support VFs\n");
		वापस DMAE_NOT_RDY;
	पूर्ण

	अगर (!bp->dmae_पढ़ोy) अणु
		BNX2X_ERR("DMAE is not ready, can not copy\n");
		वापस DMAE_NOT_RDY;
	पूर्ण

	/* set opcode and fixed command fields */
	bnx2x_prep_dmae_with_comp(bp, &dmae, DMAE_SRC_PCI, DMAE_DST_PCI);

	अगर (from_vf) अणु
		dmae.opcode_iov = (vfid << DMAE_COMMAND_SRC_VFID_SHIFT) |
			(DMAE_SRC_VF << DMAE_COMMAND_SRC_VFPF_SHIFT) |
			(DMAE_DST_PF << DMAE_COMMAND_DST_VFPF_SHIFT);

		dmae.opcode |= (DMAE_C_DST << DMAE_COMMAND_C_FUNC_SHIFT);

		dmae.src_addr_lo = vf_addr_lo;
		dmae.src_addr_hi = vf_addr_hi;
		dmae.dst_addr_lo = U64_LO(pf_addr);
		dmae.dst_addr_hi = U64_HI(pf_addr);
	पूर्ण अन्यथा अणु
		dmae.opcode_iov = (vfid << DMAE_COMMAND_DST_VFID_SHIFT) |
			(DMAE_DST_VF << DMAE_COMMAND_DST_VFPF_SHIFT) |
			(DMAE_SRC_PF << DMAE_COMMAND_SRC_VFPF_SHIFT);

		dmae.opcode |= (DMAE_C_SRC << DMAE_COMMAND_C_FUNC_SHIFT);

		dmae.src_addr_lo = U64_LO(pf_addr);
		dmae.src_addr_hi = U64_HI(pf_addr);
		dmae.dst_addr_lo = vf_addr_lo;
		dmae.dst_addr_hi = vf_addr_hi;
	पूर्ण
	dmae.len = len32;

	/* issue the command and रुको क्रम completion */
	वापस bnx2x_issue_dmae_with_comp(bp, &dmae, bnx2x_sp(bp, wb_comp));
पूर्ण

अटल व्योम bnx2x_vf_mbx_resp_single_tlv(काष्ठा bnx2x *bp,
					 काष्ठा bnx2x_virtf *vf)
अणु
	काष्ठा bnx2x_vf_mbx *mbx = BP_VF_MBX(bp, vf->index);
	u16 length, type;

	/* prepare response */
	type = mbx->first_tlv.tl.type;
	length = type == CHANNEL_TLV_ACQUIRE ?
		माप(काष्ठा pfvf_acquire_resp_tlv) :
		माप(काष्ठा pfvf_general_resp_tlv);
	bnx2x_add_tlv(bp, &mbx->msg->resp, 0, type, length);
	bnx2x_add_tlv(bp, &mbx->msg->resp, length, CHANNEL_TLV_LIST_END,
		      माप(काष्ठा channel_list_end_tlv));
पूर्ण

अटल व्योम bnx2x_vf_mbx_resp_send_msg(काष्ठा bnx2x *bp,
				       काष्ठा bnx2x_virtf *vf,
				       पूर्णांक vf_rc)
अणु
	काष्ठा bnx2x_vf_mbx *mbx = BP_VF_MBX(bp, vf->index);
	काष्ठा pfvf_general_resp_tlv *resp = &mbx->msg->resp.general_resp;
	dma_addr_t pf_addr;
	u64 vf_addr;
	पूर्णांक rc;

	bnx2x_dp_tlv_list(bp, resp);
	DP(BNX2X_MSG_IOV, "mailbox vf address hi 0x%x, lo 0x%x, offset 0x%x\n",
	   mbx->vf_addr_hi, mbx->vf_addr_lo, mbx->first_tlv.resp_msg_offset);

	resp->hdr.status = bnx2x_pfvf_status_codes(vf_rc);

	/* send response */
	vf_addr = HILO_U64(mbx->vf_addr_hi, mbx->vf_addr_lo) +
		  mbx->first_tlv.resp_msg_offset;
	pf_addr = mbx->msg_mapping +
		  दुरत्व(काष्ठा bnx2x_vf_mbx_msg, resp);

	/* Copy the response buffer. The first u64 is written afterwards, as
	 * the vf is sensitive to the header being written
	 */
	vf_addr += माप(u64);
	pf_addr += माप(u64);
	rc = bnx2x_copy32_vf_dmae(bp, false, pf_addr, vf->असल_vfid,
				  U64_HI(vf_addr),
				  U64_LO(vf_addr),
				  (माप(जोड़ pfvf_tlvs) - माप(u64))/4);
	अगर (rc) अणु
		BNX2X_ERR("Failed to copy response body to VF %d\n",
			  vf->असल_vfid);
		जाओ mbx_error;
	पूर्ण
	vf_addr -= माप(u64);
	pf_addr -= माप(u64);

	/* ack the FW */
	storm_स_रखो_vf_mbx_ack(bp, vf->असल_vfid);

	/* copy the response header including status-करोne field,
	 * must be last dmae, must be after FW is acked
	 */
	rc = bnx2x_copy32_vf_dmae(bp, false, pf_addr, vf->असल_vfid,
				  U64_HI(vf_addr),
				  U64_LO(vf_addr),
				  माप(u64)/4);

	/* unlock channel mutex */
	bnx2x_unlock_vf_pf_channel(bp, vf, mbx->first_tlv.tl.type);

	अगर (rc) अणु
		BNX2X_ERR("Failed to copy response status to VF %d\n",
			  vf->असल_vfid);
		जाओ mbx_error;
	पूर्ण
	वापस;

mbx_error:
	bnx2x_vf_release(bp, vf);
पूर्ण

अटल व्योम bnx2x_vf_mbx_resp(काष्ठा bnx2x *bp,
			      काष्ठा bnx2x_virtf *vf,
			      पूर्णांक rc)
अणु
	bnx2x_vf_mbx_resp_single_tlv(bp, vf);
	bnx2x_vf_mbx_resp_send_msg(bp, vf, rc);
पूर्ण

अटल व्योम bnx2x_vf_mbx_resp_phys_port(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_virtf *vf,
					व्योम *buffer,
					u16 *offset)
अणु
	काष्ठा vfpf_port_phys_id_resp_tlv *port_id;

	अगर (!(bp->flags & HAS_PHYS_PORT_ID))
		वापस;

	bnx2x_add_tlv(bp, buffer, *offset, CHANNEL_TLV_PHYS_PORT_ID,
		      माप(काष्ठा vfpf_port_phys_id_resp_tlv));

	port_id = (काष्ठा vfpf_port_phys_id_resp_tlv *)
		  (((u8 *)buffer) + *offset);
	स_नकल(port_id->id, bp->phys_port_id, ETH_ALEN);

	/* Offset should जारी representing the offset to the tail
	 * of TLV data (outside this function scope)
	 */
	*offset += माप(काष्ठा vfpf_port_phys_id_resp_tlv);
पूर्ण

अटल व्योम bnx2x_vf_mbx_resp_fp_hsi_ver(काष्ठा bnx2x *bp,
					 काष्ठा bnx2x_virtf *vf,
					 व्योम *buffer,
					 u16 *offset)
अणु
	काष्ठा vfpf_fp_hsi_resp_tlv *fp_hsi;

	bnx2x_add_tlv(bp, buffer, *offset, CHANNEL_TLV_FP_HSI_SUPPORT,
		      माप(काष्ठा vfpf_fp_hsi_resp_tlv));

	fp_hsi = (काष्ठा vfpf_fp_hsi_resp_tlv *)
		 (((u8 *)buffer) + *offset);
	fp_hsi->is_supported = (vf->fp_hsi > ETH_FP_HSI_VERSION) ? 0 : 1;

	/* Offset should जारी representing the offset to the tail
	 * of TLV data (outside this function scope)
	 */
	*offset += माप(काष्ठा vfpf_fp_hsi_resp_tlv);
पूर्ण

अटल व्योम bnx2x_vf_mbx_acquire_resp(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
				      काष्ठा bnx2x_vf_mbx *mbx, पूर्णांक vfop_status)
अणु
	पूर्णांक i;
	काष्ठा pfvf_acquire_resp_tlv *resp = &mbx->msg->resp.acquire_resp;
	काष्ठा pf_vf_resc *resc = &resp->resc;
	u8 status = bnx2x_pfvf_status_codes(vfop_status);
	u16 length;

	स_रखो(resp, 0, माप(*resp));

	/* fill in pfdev info */
	resp->pfdev_info.chip_num = bp->common.chip_id;
	resp->pfdev_info.db_size = bp->db_size;
	resp->pfdev_info.indices_per_sb = HC_SB_MAX_INDICES_E2;
	resp->pfdev_info.pf_cap = (PFVF_CAP_RSS |
				   PFVF_CAP_TPA |
				   PFVF_CAP_TPA_UPDATE |
				   PFVF_CAP_VLAN_FILTER);
	bnx2x_fill_fw_str(bp, resp->pfdev_info.fw_ver,
			  माप(resp->pfdev_info.fw_ver));

	अगर (status == PFVF_STATUS_NO_RESOURCE ||
	    status == PFVF_STATUS_SUCCESS) अणु
		/* set resources numbers, अगर status equals NO_RESOURCE these
		 * are max possible numbers
		 */
		resc->num_rxqs = vf_rxq_count(vf) ? :
			bnx2x_vf_max_queue_cnt(bp, vf);
		resc->num_txqs = vf_txq_count(vf) ? :
			bnx2x_vf_max_queue_cnt(bp, vf);
		resc->num_sbs = vf_sb_count(vf);
		resc->num_mac_filters = vf_mac_rules_cnt(vf);
		resc->num_vlan_filters = vf_vlan_rules_cnt(vf);
		resc->num_mc_filters = 0;

		अगर (status == PFVF_STATUS_SUCCESS) अणु
			/* fill in the allocated resources */
			काष्ठा pf_vf_bulletin_content *bulletin =
				BP_VF_BULLETIN(bp, vf->index);

			क्रम_each_vfq(vf, i)
				resc->hw_qid[i] =
					vfq_qzone_id(vf, vfq_get(vf, i));

			क्रम_each_vf_sb(vf, i) अणु
				resc->hw_sbs[i].hw_sb_id = vf_igu_sb(vf, i);
				resc->hw_sbs[i].sb_qid = vf_hc_qzone(vf, i);
			पूर्ण

			/* अगर a mac has been set क्रम this vf, supply it */
			अगर (bulletin->valid_biपंचांगap & 1 << MAC_ADDR_VALID) अणु
				स_नकल(resc->current_mac_addr, bulletin->mac,
				       ETH_ALEN);
			पूर्ण
		पूर्ण
	पूर्ण

	DP(BNX2X_MSG_IOV, "VF[%d] ACQUIRE_RESPONSE: pfdev_info- chip_num=0x%x, db_size=%d, idx_per_sb=%d, pf_cap=0x%x\n"
	   "resources- n_rxq-%d, n_txq-%d, n_sbs-%d, n_macs-%d, n_vlans-%d, n_mcs-%d, fw_ver: '%s'\n",
	   vf->असल_vfid,
	   resp->pfdev_info.chip_num,
	   resp->pfdev_info.db_size,
	   resp->pfdev_info.indices_per_sb,
	   resp->pfdev_info.pf_cap,
	   resc->num_rxqs,
	   resc->num_txqs,
	   resc->num_sbs,
	   resc->num_mac_filters,
	   resc->num_vlan_filters,
	   resc->num_mc_filters,
	   resp->pfdev_info.fw_ver);

	DP_CONT(BNX2X_MSG_IOV, "hw_qids- [ ");
	क्रम (i = 0; i < vf_rxq_count(vf); i++)
		DP_CONT(BNX2X_MSG_IOV, "%d ", resc->hw_qid[i]);
	DP_CONT(BNX2X_MSG_IOV, "], sb_info- [ ");
	क्रम (i = 0; i < vf_sb_count(vf); i++)
		DP_CONT(BNX2X_MSG_IOV, "%d:%d ",
			resc->hw_sbs[i].hw_sb_id,
			resc->hw_sbs[i].sb_qid);
	DP_CONT(BNX2X_MSG_IOV, "]\n");

	/* prepare response */
	length = माप(काष्ठा pfvf_acquire_resp_tlv);
	bnx2x_add_tlv(bp, &mbx->msg->resp, 0, CHANNEL_TLV_ACQUIRE, length);

	/* Handle possible VF requests क्रम physical port identअगरiers.
	 * 'length' should जारी to indicate the offset of the first empty
	 * place in the buffer (i.e., where next TLV should be inserted)
	 */
	अगर (bnx2x_search_tlv_list(bp, &mbx->msg->req,
				  CHANNEL_TLV_PHYS_PORT_ID))
		bnx2x_vf_mbx_resp_phys_port(bp, vf, &mbx->msg->resp, &length);

	/* `New' vfs will want to know अगर fastpath HSI is supported, since
	 * अगर that's not the हाल they could prपूर्णांक पूर्णांकo प्रणाली log the fact
	 * the driver version must be updated.
	 */
	bnx2x_vf_mbx_resp_fp_hsi_ver(bp, vf, &mbx->msg->resp, &length);

	bnx2x_add_tlv(bp, &mbx->msg->resp, length, CHANNEL_TLV_LIST_END,
		      माप(काष्ठा channel_list_end_tlv));

	/* send the response */
	bnx2x_vf_mbx_resp_send_msg(bp, vf, vfop_status);
पूर्ण

अटल bool bnx2x_vf_mbx_is_winकरोws_vm(काष्ठा bnx2x *bp,
				       काष्ठा vfpf_acquire_tlv *acquire)
अणु
	/* Winकरोws driver करोes one of three things:
	 * 1. Old driver करोesn't have bulletin board address set.
	 * 2. 'Middle' driver sends mc_num == 32.
	 * 3. New driver sets the OS field.
	 */
	अगर (!acquire->bulletin_addr ||
	    acquire->resc_request.num_mc_filters == 32 ||
	    ((acquire->vfdev_info.vf_os & VF_OS_MASK) ==
	     VF_OS_WINDOWS))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक bnx2x_vf_mbx_acquire_chk_करोrq(काष्ठा bnx2x *bp,
					 काष्ठा bnx2x_virtf *vf,
					 काष्ठा bnx2x_vf_mbx *mbx)
अणु
	/* Linux drivers which correctly set the करोorbell size also
	 * send a physical port request
	 */
	अगर (bnx2x_search_tlv_list(bp, &mbx->msg->req,
				  CHANNEL_TLV_PHYS_PORT_ID))
		वापस 0;

	/* Issue करोes not exist in winकरोws VMs */
	अगर (bnx2x_vf_mbx_is_winकरोws_vm(bp, &mbx->msg->req.acquire))
		वापस 0;

	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम bnx2x_vf_mbx_acquire(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
				 काष्ठा bnx2x_vf_mbx *mbx)
अणु
	पूर्णांक rc;
	काष्ठा vfpf_acquire_tlv *acquire = &mbx->msg->req.acquire;

	/* log vfdef info */
	DP(BNX2X_MSG_IOV,
	   "VF[%d] ACQUIRE: vfdev_info- vf_id %d, vf_os %d resources- n_rxq-%d, n_txq-%d, n_sbs-%d, n_macs-%d, n_vlans-%d, n_mcs-%d\n",
	   vf->असल_vfid, acquire->vfdev_info.vf_id, acquire->vfdev_info.vf_os,
	   acquire->resc_request.num_rxqs, acquire->resc_request.num_txqs,
	   acquire->resc_request.num_sbs, acquire->resc_request.num_mac_filters,
	   acquire->resc_request.num_vlan_filters,
	   acquire->resc_request.num_mc_filters);

	/* Prevent VFs with old drivers from loading, since they calculate
	 * CIDs incorrectly requiring a VF-flr [VM reboot] in order to recover
	 * जबतक being upgraded.
	 */
	rc = bnx2x_vf_mbx_acquire_chk_करोrq(bp, vf, mbx);
	अगर (rc) अणु
		DP(BNX2X_MSG_IOV,
		   "VF [%d] - Can't support acquire request due to doorbell mismatch. Please update VM driver\n",
		   vf->असल_vfid);
		जाओ out;
	पूर्ण

	/* Verअगरy the VF fastpath HSI can be supported by the loaded FW.
	 * Linux vfs should be oblivious to changes between v0 and v2.
	 */
	अगर (bnx2x_vf_mbx_is_winकरोws_vm(bp, &mbx->msg->req.acquire))
		vf->fp_hsi = acquire->vfdev_info.fp_hsi_ver;
	अन्यथा
		vf->fp_hsi = max_t(u8, acquire->vfdev_info.fp_hsi_ver,
				   ETH_FP_HSI_VER_2);
	अगर (vf->fp_hsi > ETH_FP_HSI_VERSION) अणु
		DP(BNX2X_MSG_IOV,
		   "VF [%d] - Can't support acquire request since VF requests a FW version which is too new [%02x > %02x]\n",
		   vf->असल_vfid, acquire->vfdev_info.fp_hsi_ver,
		   ETH_FP_HSI_VERSION);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/* acquire the resources */
	rc = bnx2x_vf_acquire(bp, vf, &acquire->resc_request);

	/* store address of vf's bulletin board */
	vf->bulletin_map = acquire->bulletin_addr;
	अगर (acquire->vfdev_info.caps & VF_CAP_SUPPORT_EXT_BULLETIN) अणु
		DP(BNX2X_MSG_IOV, "VF[%d] supports long bulletin boards\n",
		   vf->असल_vfid);
		vf->cfg_flags |= VF_CFG_EXT_BULLETIN;
	पूर्ण अन्यथा अणु
		vf->cfg_flags &= ~VF_CFG_EXT_BULLETIN;
	पूर्ण

	अगर (acquire->vfdev_info.caps & VF_CAP_SUPPORT_VLAN_FILTER) अणु
		DP(BNX2X_MSG_IOV, "VF[%d] supports vlan filtering\n",
		   vf->असल_vfid);
		vf->cfg_flags |= VF_CFG_VLAN_FILTER;
	पूर्ण अन्यथा अणु
		vf->cfg_flags &= ~VF_CFG_VLAN_FILTER;
	पूर्ण

out:
	/* response */
	bnx2x_vf_mbx_acquire_resp(bp, vf, mbx, rc);
पूर्ण

अटल व्योम bnx2x_vf_mbx_init_vf(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
			      काष्ठा bnx2x_vf_mbx *mbx)
अणु
	काष्ठा vfpf_init_tlv *init = &mbx->msg->req.init;
	पूर्णांक rc;

	/* record ghost addresses from vf message */
	vf->fw_stat_map = init->stats_addr;
	vf->stats_stride = init->stats_stride;
	rc = bnx2x_vf_init(bp, vf, (dma_addr_t *)init->sb_addr);

	/* set VF multiqueue statistics collection mode */
	अगर (init->flags & VFPF_INIT_FLG_STATS_COALESCE)
		vf->cfg_flags |= VF_CFG_STATS_COALESCE;

	/* Update VF's view of link state */
	अगर (vf->cfg_flags & VF_CFG_EXT_BULLETIN)
		bnx2x_iov_link_update_vf(bp, vf->index);

	/* response */
	bnx2x_vf_mbx_resp(bp, vf, rc);
पूर्ण

/* convert MBX queue-flags to standard SP queue-flags */
अटल व्योम bnx2x_vf_mbx_set_q_flags(काष्ठा bnx2x *bp, u32 mbx_q_flags,
				     अचिन्हित दीर्घ *sp_q_flags)
अणु
	अगर (mbx_q_flags & VFPF_QUEUE_FLG_TPA)
		__set_bit(BNX2X_Q_FLG_TPA, sp_q_flags);
	अगर (mbx_q_flags & VFPF_QUEUE_FLG_TPA_IPV6)
		__set_bit(BNX2X_Q_FLG_TPA_IPV6, sp_q_flags);
	अगर (mbx_q_flags & VFPF_QUEUE_FLG_TPA_GRO)
		__set_bit(BNX2X_Q_FLG_TPA_GRO, sp_q_flags);
	अगर (mbx_q_flags & VFPF_QUEUE_FLG_STATS)
		__set_bit(BNX2X_Q_FLG_STATS, sp_q_flags);
	अगर (mbx_q_flags & VFPF_QUEUE_FLG_VLAN)
		__set_bit(BNX2X_Q_FLG_VLAN, sp_q_flags);
	अगर (mbx_q_flags & VFPF_QUEUE_FLG_COS)
		__set_bit(BNX2X_Q_FLG_COS, sp_q_flags);
	अगर (mbx_q_flags & VFPF_QUEUE_FLG_HC)
		__set_bit(BNX2X_Q_FLG_HC, sp_q_flags);
	अगर (mbx_q_flags & VFPF_QUEUE_FLG_DHC)
		__set_bit(BNX2X_Q_FLG_DHC, sp_q_flags);
	अगर (mbx_q_flags & VFPF_QUEUE_FLG_LEADING_RSS)
		__set_bit(BNX2X_Q_FLG_LEADING_RSS, sp_q_flags);

	/* outer vlan removal is set according to PF's multi function mode */
	अगर (IS_MF_SD(bp))
		__set_bit(BNX2X_Q_FLG_OV, sp_q_flags);
पूर्ण

अटल व्योम bnx2x_vf_mbx_setup_q(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
				 काष्ठा bnx2x_vf_mbx *mbx)
अणु
	काष्ठा vfpf_setup_q_tlv *setup_q = &mbx->msg->req.setup_q;
	काष्ठा bnx2x_vf_queue_स्थिरruct_params qctor;
	पूर्णांक rc = 0;

	/* verअगरy vf_qid */
	अगर (setup_q->vf_qid >= vf_rxq_count(vf)) अणु
		BNX2X_ERR("vf_qid %d invalid, max queue count is %d\n",
			  setup_q->vf_qid, vf_rxq_count(vf));
		rc = -EINVAL;
		जाओ response;
	पूर्ण

	/* tx queues must be setup aदीर्घside rx queues thus अगर the rx queue
	 * is not marked as valid there's nothing to करो.
	 */
	अगर (setup_q->param_valid & (VFPF_RXQ_VALID|VFPF_TXQ_VALID)) अणु
		काष्ठा bnx2x_vf_queue *q = vfq_get(vf, setup_q->vf_qid);
		अचिन्हित दीर्घ q_type = 0;

		काष्ठा bnx2x_queue_init_params *init_p;
		काष्ठा bnx2x_queue_setup_params *setup_p;

		अगर (bnx2x_vfq_is_leading(q))
			bnx2x_leading_vfq_init(bp, vf, q);

		/* re-init the VF operation context */
		स_रखो(&qctor, 0 ,
		       माप(काष्ठा bnx2x_vf_queue_स्थिरruct_params));
		setup_p = &qctor.prep_qsetup;
		init_p =  &qctor.qstate.params.init;

		/* activate immediately */
		__set_bit(BNX2X_Q_FLG_ACTIVE, &setup_p->flags);

		अगर (setup_q->param_valid & VFPF_TXQ_VALID) अणु
			काष्ठा bnx2x_txq_setup_params *txq_params =
				&setup_p->txq_params;

			__set_bit(BNX2X_Q_TYPE_HAS_TX, &q_type);

			/* save sb resource index */
			q->sb_idx = setup_q->txq.vf_sb;

			/* tx init */
			init_p->tx.hc_rate = setup_q->txq.hc_rate;
			init_p->tx.sb_cq_index = setup_q->txq.sb_index;

			bnx2x_vf_mbx_set_q_flags(bp, setup_q->txq.flags,
						 &init_p->tx.flags);

			/* tx setup - flags */
			bnx2x_vf_mbx_set_q_flags(bp, setup_q->txq.flags,
						 &setup_p->flags);

			/* tx setup - general, nothing */

			/* tx setup - tx */
			txq_params->dscr_map = setup_q->txq.txq_addr;
			txq_params->sb_cq_index = setup_q->txq.sb_index;
			txq_params->traffic_type = setup_q->txq.traffic_type;

			bnx2x_vfop_qctor_dump_tx(bp, vf, init_p, setup_p,
						 q->index, q->sb_idx);
		पूर्ण

		अगर (setup_q->param_valid & VFPF_RXQ_VALID) अणु
			काष्ठा bnx2x_rxq_setup_params *rxq_params =
							&setup_p->rxq_params;

			__set_bit(BNX2X_Q_TYPE_HAS_RX, &q_type);

			/* Note: there is no support क्रम dअगरferent SBs
			 * क्रम TX and RX
			 */
			q->sb_idx = setup_q->rxq.vf_sb;

			/* rx init */
			init_p->rx.hc_rate = setup_q->rxq.hc_rate;
			init_p->rx.sb_cq_index = setup_q->rxq.sb_index;
			bnx2x_vf_mbx_set_q_flags(bp, setup_q->rxq.flags,
						 &init_p->rx.flags);

			/* rx setup - flags */
			bnx2x_vf_mbx_set_q_flags(bp, setup_q->rxq.flags,
						 &setup_p->flags);

			/* rx setup - general */
			setup_p->gen_params.mtu = setup_q->rxq.mtu;

			/* rx setup - rx */
			rxq_params->drop_flags = setup_q->rxq.drop_flags;
			rxq_params->dscr_map = setup_q->rxq.rxq_addr;
			rxq_params->sge_map = setup_q->rxq.sge_addr;
			rxq_params->rcq_map = setup_q->rxq.rcq_addr;
			rxq_params->rcq_np_map = setup_q->rxq.rcq_np_addr;
			rxq_params->buf_sz = setup_q->rxq.buf_sz;
			rxq_params->tpa_agg_sz = setup_q->rxq.tpa_agg_sz;
			rxq_params->max_sges_pkt = setup_q->rxq.max_sge_pkt;
			rxq_params->sge_buf_sz = setup_q->rxq.sge_buf_sz;
			rxq_params->cache_line_log =
				setup_q->rxq.cache_line_log;
			rxq_params->sb_cq_index = setup_q->rxq.sb_index;

			/* rx setup - multicast engine */
			अगर (bnx2x_vfq_is_leading(q)) अणु
				u8 mcast_id = FW_VF_HANDLE(vf->असल_vfid);

				rxq_params->mcast_engine_id = mcast_id;
				__set_bit(BNX2X_Q_FLG_MCAST, &setup_p->flags);
			पूर्ण

			bnx2x_vfop_qctor_dump_rx(bp, vf, init_p, setup_p,
						 q->index, q->sb_idx);
		पूर्ण
		/* complete the preparations */
		bnx2x_vfop_qctor_prep(bp, vf, q, &qctor, q_type);

		rc = bnx2x_vf_queue_setup(bp, vf, q->index, &qctor);
		अगर (rc)
			जाओ response;
	पूर्ण
response:
	bnx2x_vf_mbx_resp(bp, vf, rc);
पूर्ण

अटल पूर्णांक bnx2x_vf_mbx_macvlan_list(काष्ठा bnx2x *bp,
				     काष्ठा bnx2x_virtf *vf,
				     काष्ठा vfpf_set_q_filters_tlv *tlv,
				     काष्ठा bnx2x_vf_mac_vlan_filters **pfl,
				     u32 type_flag)
अणु
	पूर्णांक i, j;
	काष्ठा bnx2x_vf_mac_vlan_filters *fl = शून्य;

	fl = kzalloc(काष्ठा_size(fl, filters, tlv->n_mac_vlan_filters),
		     GFP_KERNEL);
	अगर (!fl)
		वापस -ENOMEM;

	क्रम (i = 0, j = 0; i < tlv->n_mac_vlan_filters; i++) अणु
		काष्ठा vfpf_q_mac_vlan_filter *msg_filter = &tlv->filters[i];

		अगर ((msg_filter->flags & type_flag) != type_flag)
			जारी;
		स_रखो(&fl->filters[j], 0, माप(fl->filters[j]));
		अगर (type_flag & VFPF_Q_FILTER_DEST_MAC_VALID) अणु
			fl->filters[j].mac = msg_filter->mac;
			fl->filters[j].type |= BNX2X_VF_FILTER_MAC;
		पूर्ण
		अगर (type_flag & VFPF_Q_FILTER_VLAN_TAG_VALID) अणु
			fl->filters[j].vid = msg_filter->vlan_tag;
			fl->filters[j].type |= BNX2X_VF_FILTER_VLAN;
		पूर्ण
		fl->filters[j].add = !!(msg_filter->flags & VFPF_Q_FILTER_SET);
		fl->count++;
		j++;
	पूर्ण
	अगर (!fl->count)
		kमुक्त(fl);
	अन्यथा
		*pfl = fl;

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_vf_filters_contain(काष्ठा vfpf_set_q_filters_tlv *filters,
				    u32 flags)
अणु
	पूर्णांक i, cnt = 0;

	क्रम (i = 0; i < filters->n_mac_vlan_filters; i++)
		अगर  ((filters->filters[i].flags & flags) == flags)
			cnt++;

	वापस cnt;
पूर्ण

अटल व्योम bnx2x_vf_mbx_dp_q_filter(काष्ठा bnx2x *bp, पूर्णांक msglvl, पूर्णांक idx,
				       काष्ठा vfpf_q_mac_vlan_filter *filter)
अणु
	DP(msglvl, "MAC-VLAN[%d] -- flags=0x%x\n", idx, filter->flags);
	अगर (filter->flags & VFPF_Q_FILTER_VLAN_TAG_VALID)
		DP_CONT(msglvl, ", vlan=%d", filter->vlan_tag);
	अगर (filter->flags & VFPF_Q_FILTER_DEST_MAC_VALID)
		DP_CONT(msglvl, ", MAC=%pM", filter->mac);
	DP_CONT(msglvl, "\n");
पूर्ण

अटल व्योम bnx2x_vf_mbx_dp_q_filters(काष्ठा bnx2x *bp, पूर्णांक msglvl,
				       काष्ठा vfpf_set_q_filters_tlv *filters)
अणु
	पूर्णांक i;

	अगर (filters->flags & VFPF_SET_Q_FILTERS_MAC_VLAN_CHANGED)
		क्रम (i = 0; i < filters->n_mac_vlan_filters; i++)
			bnx2x_vf_mbx_dp_q_filter(bp, msglvl, i,
						 &filters->filters[i]);

	अगर (filters->flags & VFPF_SET_Q_FILTERS_RX_MASK_CHANGED)
		DP(msglvl, "RX-MASK=0x%x\n", filters->rx_mask);

	अगर (filters->flags & VFPF_SET_Q_FILTERS_MULTICAST_CHANGED)
		क्रम (i = 0; i < filters->n_multicast; i++)
			DP(msglvl, "MULTICAST=%pM\n", filters->multicast[i]);
पूर्ण

#घोषणा VFPF_MAC_FILTER		VFPF_Q_FILTER_DEST_MAC_VALID
#घोषणा VFPF_VLAN_FILTER	VFPF_Q_FILTER_VLAN_TAG_VALID
#घोषणा VFPF_VLAN_MAC_FILTER	(VFPF_VLAN_FILTER | VFPF_MAC_FILTER)

अटल पूर्णांक bnx2x_vf_mbx_qfilters(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf)
अणु
	पूर्णांक rc = 0;

	काष्ठा vfpf_set_q_filters_tlv *msg =
		&BP_VF_MBX(bp, vf->index)->msg->req.set_q_filters;

	/* check क्रम any mac/vlan changes */
	अगर (msg->flags & VFPF_SET_Q_FILTERS_MAC_VLAN_CHANGED) अणु
		काष्ठा bnx2x_vf_mac_vlan_filters *fl = शून्य;

		/* build vlan-mac list */
		rc = bnx2x_vf_mbx_macvlan_list(bp, vf, msg, &fl,
					       VFPF_VLAN_MAC_FILTER);
		अगर (rc)
			जाओ op_err;

		अगर (fl) अणु

			/* set vlan-mac list */
			rc = bnx2x_vf_mac_vlan_config_list(bp, vf, fl,
							   msg->vf_qid,
							   false);
			अगर (rc)
				जाओ op_err;
		पूर्ण

		/* build mac list */
		fl = शून्य;

		rc = bnx2x_vf_mbx_macvlan_list(bp, vf, msg, &fl,
					       VFPF_MAC_FILTER);
		अगर (rc)
			जाओ op_err;

		अगर (fl) अणु
			/* set mac list */
			rc = bnx2x_vf_mac_vlan_config_list(bp, vf, fl,
							   msg->vf_qid,
							   false);
			अगर (rc)
				जाओ op_err;
		पूर्ण

		/* build vlan list */
		fl = शून्य;

		rc = bnx2x_vf_mbx_macvlan_list(bp, vf, msg, &fl,
					       VFPF_VLAN_FILTER);
		अगर (rc)
			जाओ op_err;

		अगर (fl) अणु
			/* set vlan list */
			rc = bnx2x_vf_mac_vlan_config_list(bp, vf, fl,
							   msg->vf_qid,
							   false);
			अगर (rc)
				जाओ op_err;
		पूर्ण

	पूर्ण

	अगर (msg->flags & VFPF_SET_Q_FILTERS_RX_MASK_CHANGED) अणु
		अचिन्हित दीर्घ accept = 0;
		काष्ठा pf_vf_bulletin_content *bulletin =
					BP_VF_BULLETIN(bp, vf->index);

		/* Ignore VF requested mode; instead set a regular mode */
		अगर (msg->rx_mask !=  VFPF_RX_MASK_ACCEPT_NONE) अणु
			__set_bit(BNX2X_ACCEPT_UNICAST, &accept);
			__set_bit(BNX2X_ACCEPT_MULTICAST, &accept);
			__set_bit(BNX2X_ACCEPT_BROADCAST, &accept);
		पूर्ण

		/* any_vlan is not configured अगर HV is क्रमcing VLAN
		 * any_vlan is configured अगर
		 *   1. VF करोes not support vlan filtering
		 *   OR
		 *   2. VF supports vlan filtering and explicitly requested it
		 */
		अगर (!(bulletin->valid_biपंचांगap & (1 << VLAN_VALID)) &&
		    (!(vf->cfg_flags & VF_CFG_VLAN_FILTER) ||
		     msg->rx_mask & VFPF_RX_MASK_ACCEPT_ANY_VLAN))
			__set_bit(BNX2X_ACCEPT_ANY_VLAN, &accept);

		/* set rx-mode */
		rc = bnx2x_vf_rxmode(bp, vf, msg->vf_qid, accept);
		अगर (rc)
			जाओ op_err;
	पूर्ण

	अगर (msg->flags & VFPF_SET_Q_FILTERS_MULTICAST_CHANGED) अणु
		/* set mcasts */
		rc = bnx2x_vf_mcast(bp, vf, msg->multicast,
				    msg->n_multicast, false);
		अगर (rc)
			जाओ op_err;
	पूर्ण
op_err:
	अगर (rc)
		BNX2X_ERR("QFILTERS[%d:%d] error: rc %d\n",
			  vf->असल_vfid, msg->vf_qid, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_filters_validate_mac(काष्ठा bnx2x *bp,
				      काष्ठा bnx2x_virtf *vf,
				      काष्ठा vfpf_set_q_filters_tlv *filters)
अणु
	काष्ठा pf_vf_bulletin_content *bulletin = BP_VF_BULLETIN(bp, vf->index);
	पूर्णांक rc = 0;

	/* अगर a mac was alपढ़ोy set क्रम this VF via the set vf mac nकरो, we only
	 * accept mac configurations of that mac. Why accept them at all?
	 * because PF may have been unable to configure the mac at the समय
	 * since queue was not set up.
	 */
	अगर (bulletin->valid_biपंचांगap & 1 << MAC_ADDR_VALID) अणु
		काष्ठा vfpf_q_mac_vlan_filter *filter = शून्य;
		पूर्णांक i;

		क्रम (i = 0; i < filters->n_mac_vlan_filters; i++) अणु
			अगर (!(filters->filters[i].flags &
			      VFPF_Q_FILTER_DEST_MAC_VALID))
				जारी;

			/* once a mac was set by nकरो can only accept
			 * a single mac...
			 */
			अगर (filter) अणु
				BNX2X_ERR("VF[%d] requested the addition of multiple macs after set_vf_mac ndo was called [%d filters]\n",
					  vf->असल_vfid,
					  filters->n_mac_vlan_filters);
				rc = -EPERM;
				जाओ response;
			पूर्ण

			filter = &filters->filters[i];
		पूर्ण

		/* ...and only the mac set by the nकरो */
		अगर (filter &&
		    !ether_addr_equal(filter->mac, bulletin->mac)) अणु
			BNX2X_ERR("VF[%d] requested the addition of a mac address not matching the one configured by set_vf_mac ndo\n",
				  vf->असल_vfid);

			rc = -EPERM;
			जाओ response;
		पूर्ण
	पूर्ण

response:
	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_filters_validate_vlan(काष्ठा bnx2x *bp,
				       काष्ठा bnx2x_virtf *vf,
				       काष्ठा vfpf_set_q_filters_tlv *filters)
अणु
	काष्ठा pf_vf_bulletin_content *bulletin = BP_VF_BULLETIN(bp, vf->index);
	पूर्णांक rc = 0;

	/* अगर vlan was set by hypervisor we करोn't allow guest to config vlan */
	अगर (bulletin->valid_biपंचांगap & 1 << VLAN_VALID) अणु
		/* search क्रम vlan filters */

		अगर (bnx2x_vf_filters_contain(filters,
					     VFPF_Q_FILTER_VLAN_TAG_VALID)) अणु
			BNX2X_ERR("VF[%d] attempted to configure vlan but one was already set by Hypervisor. Aborting request\n",
				  vf->असल_vfid);
			rc = -EPERM;
			जाओ response;
		पूर्ण
	पूर्ण

	/* verअगरy vf_qid */
	अगर (filters->vf_qid > vf_rxq_count(vf)) अणु
		rc = -EPERM;
		जाओ response;
	पूर्ण

response:
	वापस rc;
पूर्ण

अटल व्योम bnx2x_vf_mbx_set_q_filters(काष्ठा bnx2x *bp,
				       काष्ठा bnx2x_virtf *vf,
				       काष्ठा bnx2x_vf_mbx *mbx)
अणु
	काष्ठा vfpf_set_q_filters_tlv *filters = &mbx->msg->req.set_q_filters;
	पूर्णांक rc;

	rc = bnx2x_filters_validate_mac(bp, vf, filters);
	अगर (rc)
		जाओ response;

	rc = bnx2x_filters_validate_vlan(bp, vf, filters);
	अगर (rc)
		जाओ response;

	DP(BNX2X_MSG_IOV, "VF[%d] Q_FILTERS: queue[%d]\n",
	   vf->असल_vfid,
	   filters->vf_qid);

	/* prपूर्णांक q_filter message */
	bnx2x_vf_mbx_dp_q_filters(bp, BNX2X_MSG_IOV, filters);

	rc = bnx2x_vf_mbx_qfilters(bp, vf);
response:
	bnx2x_vf_mbx_resp(bp, vf, rc);
पूर्ण

अटल व्योम bnx2x_vf_mbx_tearकरोwn_q(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
				    काष्ठा bnx2x_vf_mbx *mbx)
अणु
	पूर्णांक qid = mbx->msg->req.q_op.vf_qid;
	पूर्णांक rc;

	DP(BNX2X_MSG_IOV, "VF[%d] Q_TEARDOWN: vf_qid=%d\n",
	   vf->असल_vfid, qid);

	rc = bnx2x_vf_queue_tearकरोwn(bp, vf, qid);
	bnx2x_vf_mbx_resp(bp, vf, rc);
पूर्ण

अटल व्योम bnx2x_vf_mbx_बंद_vf(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
				  काष्ठा bnx2x_vf_mbx *mbx)
अणु
	पूर्णांक rc;

	DP(BNX2X_MSG_IOV, "VF[%d] VF_CLOSE\n", vf->असल_vfid);

	rc = bnx2x_vf_बंद(bp, vf);
	bnx2x_vf_mbx_resp(bp, vf, rc);
पूर्ण

अटल व्योम bnx2x_vf_mbx_release_vf(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
				    काष्ठा bnx2x_vf_mbx *mbx)
अणु
	पूर्णांक rc;

	DP(BNX2X_MSG_IOV, "VF[%d] VF_RELEASE\n", vf->असल_vfid);

	rc = bnx2x_vf_मुक्त(bp, vf);
	bnx2x_vf_mbx_resp(bp, vf, rc);
पूर्ण

अटल व्योम bnx2x_vf_mbx_update_rss(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
				    काष्ठा bnx2x_vf_mbx *mbx)
अणु
	काष्ठा bnx2x_config_rss_params rss;
	काष्ठा vfpf_rss_tlv *rss_tlv = &mbx->msg->req.update_rss;
	पूर्णांक rc = 0;

	अगर (rss_tlv->ind_table_size != T_ETH_INसूचीECTION_TABLE_SIZE ||
	    rss_tlv->rss_key_size != T_ETH_RSS_KEY) अणु
		BNX2X_ERR("failing rss configuration of vf %d due to size mismatch\n",
			  vf->index);
		rc = -EINVAL;
		जाओ mbx_resp;
	पूर्ण

	स_रखो(&rss, 0, माप(काष्ठा bnx2x_config_rss_params));

	/* set vfop params according to rss tlv */
	स_नकल(rss.ind_table, rss_tlv->ind_table,
	       T_ETH_INसूचीECTION_TABLE_SIZE);
	स_नकल(rss.rss_key, rss_tlv->rss_key, माप(rss_tlv->rss_key));
	rss.rss_obj = &vf->rss_conf_obj;
	rss.rss_result_mask = rss_tlv->rss_result_mask;

	/* flags handled inभागidually क्रम backward/क्रमward compatibility */
	rss.rss_flags = 0;
	rss.ramrod_flags = 0;

	अगर (rss_tlv->rss_flags & VFPF_RSS_MODE_DISABLED)
		__set_bit(BNX2X_RSS_MODE_DISABLED, &rss.rss_flags);
	अगर (rss_tlv->rss_flags & VFPF_RSS_MODE_REGULAR)
		__set_bit(BNX2X_RSS_MODE_REGULAR, &rss.rss_flags);
	अगर (rss_tlv->rss_flags & VFPF_RSS_SET_SRCH)
		__set_bit(BNX2X_RSS_SET_SRCH, &rss.rss_flags);
	अगर (rss_tlv->rss_flags & VFPF_RSS_IPV4)
		__set_bit(BNX2X_RSS_IPV4, &rss.rss_flags);
	अगर (rss_tlv->rss_flags & VFPF_RSS_IPV4_TCP)
		__set_bit(BNX2X_RSS_IPV4_TCP, &rss.rss_flags);
	अगर (rss_tlv->rss_flags & VFPF_RSS_IPV4_UDP)
		__set_bit(BNX2X_RSS_IPV4_UDP, &rss.rss_flags);
	अगर (rss_tlv->rss_flags & VFPF_RSS_IPV6)
		__set_bit(BNX2X_RSS_IPV6, &rss.rss_flags);
	अगर (rss_tlv->rss_flags & VFPF_RSS_IPV6_TCP)
		__set_bit(BNX2X_RSS_IPV6_TCP, &rss.rss_flags);
	अगर (rss_tlv->rss_flags & VFPF_RSS_IPV6_UDP)
		__set_bit(BNX2X_RSS_IPV6_UDP, &rss.rss_flags);

	अगर ((!(rss_tlv->rss_flags & VFPF_RSS_IPV4_TCP) &&
	     rss_tlv->rss_flags & VFPF_RSS_IPV4_UDP) ||
	    (!(rss_tlv->rss_flags & VFPF_RSS_IPV6_TCP) &&
	     rss_tlv->rss_flags & VFPF_RSS_IPV6_UDP)) अणु
		BNX2X_ERR("about to hit a FW assert. aborting...\n");
		rc = -EINVAL;
		जाओ mbx_resp;
	पूर्ण

	rc = bnx2x_vf_rss_update(bp, vf, &rss);
mbx_resp:
	bnx2x_vf_mbx_resp(bp, vf, rc);
पूर्ण

अटल पूर्णांक bnx2x_validate_tpa_params(काष्ठा bnx2x *bp,
				       काष्ठा vfpf_tpa_tlv *tpa_tlv)
अणु
	पूर्णांक rc = 0;

	अगर (tpa_tlv->tpa_client_info.max_sges_क्रम_packet >
	    U_ETH_MAX_SGES_FOR_PACKET) अणु
		rc = -EINVAL;
		BNX2X_ERR("TPA update: max_sges received %d, max is %d\n",
			  tpa_tlv->tpa_client_info.max_sges_क्रम_packet,
			  U_ETH_MAX_SGES_FOR_PACKET);
	पूर्ण

	अगर (tpa_tlv->tpa_client_info.max_tpa_queues > MAX_AGG_QS(bp)) अणु
		rc = -EINVAL;
		BNX2X_ERR("TPA update: max_tpa_queues received %d, max is %d\n",
			  tpa_tlv->tpa_client_info.max_tpa_queues,
			  MAX_AGG_QS(bp));
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम bnx2x_vf_mbx_update_tpa(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
				    काष्ठा bnx2x_vf_mbx *mbx)
अणु
	काष्ठा bnx2x_queue_update_tpa_params vf_op_params;
	काष्ठा vfpf_tpa_tlv *tpa_tlv = &mbx->msg->req.update_tpa;
	पूर्णांक rc = 0;

	स_रखो(&vf_op_params, 0, माप(vf_op_params));

	अगर (bnx2x_validate_tpa_params(bp, tpa_tlv))
		जाओ mbx_resp;

	vf_op_params.complete_on_both_clients =
		tpa_tlv->tpa_client_info.complete_on_both_clients;
	vf_op_params.करोnt_verअगरy_thr =
		tpa_tlv->tpa_client_info.करोnt_verअगरy_thr;
	vf_op_params.max_agg_sz =
		tpa_tlv->tpa_client_info.max_agg_size;
	vf_op_params.max_sges_pkt =
		tpa_tlv->tpa_client_info.max_sges_क्रम_packet;
	vf_op_params.max_tpa_queues =
		tpa_tlv->tpa_client_info.max_tpa_queues;
	vf_op_params.sge_buff_sz =
		tpa_tlv->tpa_client_info.sge_buff_size;
	vf_op_params.sge_छोड़ो_thr_high =
		tpa_tlv->tpa_client_info.sge_छोड़ो_thr_high;
	vf_op_params.sge_छोड़ो_thr_low =
		tpa_tlv->tpa_client_info.sge_छोड़ो_thr_low;
	vf_op_params.tpa_mode =
		tpa_tlv->tpa_client_info.tpa_mode;
	vf_op_params.update_ipv4 =
		tpa_tlv->tpa_client_info.update_ipv4;
	vf_op_params.update_ipv6 =
		tpa_tlv->tpa_client_info.update_ipv6;

	rc = bnx2x_vf_tpa_update(bp, vf, tpa_tlv, &vf_op_params);

mbx_resp:
	bnx2x_vf_mbx_resp(bp, vf, rc);
पूर्ण

/* dispatch request */
अटल व्योम bnx2x_vf_mbx_request(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
				  काष्ठा bnx2x_vf_mbx *mbx)
अणु
	पूर्णांक i;

	अगर (vf->state == VF_LOST) अणु
		/* Just ack the FW and वापस अगर VFs are lost
		 * in हाल of parity error. VFs are supposed to be समयकरोut
		 * on रुकोing क्रम PF response.
		 */
		DP(BNX2X_MSG_IOV,
		   "VF 0x%x lost, not handling the request\n", vf->असल_vfid);

		storm_स_रखो_vf_mbx_ack(bp, vf->असल_vfid);
		वापस;
	पूर्ण

	/* check अगर tlv type is known */
	अगर (bnx2x_tlv_supported(mbx->first_tlv.tl.type)) अणु
		/* Lock the per vf op mutex and note the locker's identity.
		 * The unlock will take place in mbx response.
		 */
		bnx2x_lock_vf_pf_channel(bp, vf, mbx->first_tlv.tl.type);

		/* चयन on the opcode */
		चयन (mbx->first_tlv.tl.type) अणु
		हाल CHANNEL_TLV_ACQUIRE:
			bnx2x_vf_mbx_acquire(bp, vf, mbx);
			वापस;
		हाल CHANNEL_TLV_INIT:
			bnx2x_vf_mbx_init_vf(bp, vf, mbx);
			वापस;
		हाल CHANNEL_TLV_SETUP_Q:
			bnx2x_vf_mbx_setup_q(bp, vf, mbx);
			वापस;
		हाल CHANNEL_TLV_SET_Q_FILTERS:
			bnx2x_vf_mbx_set_q_filters(bp, vf, mbx);
			वापस;
		हाल CHANNEL_TLV_TEARDOWN_Q:
			bnx2x_vf_mbx_tearकरोwn_q(bp, vf, mbx);
			वापस;
		हाल CHANNEL_TLV_CLOSE:
			bnx2x_vf_mbx_बंद_vf(bp, vf, mbx);
			वापस;
		हाल CHANNEL_TLV_RELEASE:
			bnx2x_vf_mbx_release_vf(bp, vf, mbx);
			वापस;
		हाल CHANNEL_TLV_UPDATE_RSS:
			bnx2x_vf_mbx_update_rss(bp, vf, mbx);
			वापस;
		हाल CHANNEL_TLV_UPDATE_TPA:
			bnx2x_vf_mbx_update_tpa(bp, vf, mbx);
			वापस;
		पूर्ण

	पूर्ण अन्यथा अणु
		/* unknown TLV - this may beदीर्घ to a VF driver from the future
		 * - a version written after this PF driver was written, which
		 * supports features unknown as of yet. Too bad since we करोn't
		 * support them. Or this may be because someone wrote a crappy
		 * VF driver and is sending garbage over the channel.
		 */
		BNX2X_ERR("unknown TLV. type %d length %d vf->state was %d. first 20 bytes of mailbox buffer:\n",
			  mbx->first_tlv.tl.type, mbx->first_tlv.tl.length,
			  vf->state);
		क्रम (i = 0; i < 20; i++)
			DP_CONT(BNX2X_MSG_IOV, "%x ",
				mbx->msg->req.tlv_buf_size.tlv_buffer[i]);
	पूर्ण

	/* can we respond to VF (करो we have an address क्रम it?) */
	अगर (vf->state == VF_ACQUIRED || vf->state == VF_ENABLED) अणु
		/* notअगरy the VF that we करो not support this request */
		bnx2x_vf_mbx_resp(bp, vf, PFVF_STATUS_NOT_SUPPORTED);
	पूर्ण अन्यथा अणु
		/* can't send a response since this VF is unknown to us
		 * just ack the FW to release the mailbox and unlock
		 * the channel.
		 */
		storm_स_रखो_vf_mbx_ack(bp, vf->असल_vfid);
		/* Firmware ack should be written beक्रमe unlocking channel */
		bnx2x_unlock_vf_pf_channel(bp, vf, mbx->first_tlv.tl.type);
	पूर्ण
पूर्ण

व्योम bnx2x_vf_mbx_schedule(काष्ठा bnx2x *bp,
			   काष्ठा vf_pf_event_data *vfpf_event)
अणु
	u8 vf_idx;

	DP(BNX2X_MSG_IOV,
	   "vf pf event received: vfid %d, address_hi %x, address lo %x",
	   vfpf_event->vf_id, vfpf_event->msg_addr_hi, vfpf_event->msg_addr_lo);
	/* Sanity checks consider removing later */

	/* check अगर the vf_id is valid */
	अगर (vfpf_event->vf_id - BP_VFDB(bp)->sriov.first_vf_in_pf >
	    BNX2X_NR_VIRTFN(bp)) अणु
		BNX2X_ERR("Illegal vf_id %d max allowed: %d\n",
			  vfpf_event->vf_id, BNX2X_NR_VIRTFN(bp));
		वापस;
	पूर्ण

	vf_idx = bnx2x_vf_idx_by_असल_fid(bp, vfpf_event->vf_id);

	/* Update VFDB with current message and schedule its handling */
	mutex_lock(&BP_VFDB(bp)->event_mutex);
	BP_VF_MBX(bp, vf_idx)->vf_addr_hi =
		le32_to_cpu(vfpf_event->msg_addr_hi);
	BP_VF_MBX(bp, vf_idx)->vf_addr_lo =
		le32_to_cpu(vfpf_event->msg_addr_lo);
	BP_VFDB(bp)->event_occur |= (1ULL << vf_idx);
	mutex_unlock(&BP_VFDB(bp)->event_mutex);

	bnx2x_schedule_iov_task(bp, BNX2X_IOV_HANDLE_VF_MSG);
पूर्ण

/* handle new vf-pf messages */
व्योम bnx2x_vf_mbx(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_vfdb *vfdb = BP_VFDB(bp);
	u64 events;
	u8 vf_idx;
	पूर्णांक rc;

	अगर (!vfdb)
		वापस;

	mutex_lock(&vfdb->event_mutex);
	events = vfdb->event_occur;
	vfdb->event_occur = 0;
	mutex_unlock(&vfdb->event_mutex);

	क्रम_each_vf(bp, vf_idx) अणु
		काष्ठा bnx2x_vf_mbx *mbx = BP_VF_MBX(bp, vf_idx);
		काष्ठा bnx2x_virtf *vf = BP_VF(bp, vf_idx);

		/* Handle VFs which have pending events */
		अगर (!(events & (1ULL << vf_idx)))
			जारी;

		DP(BNX2X_MSG_IOV,
		   "Handling vf pf event vfid %d, address: [%x:%x], resp_offset 0x%x\n",
		   vf_idx, mbx->vf_addr_hi, mbx->vf_addr_lo,
		   mbx->first_tlv.resp_msg_offset);

		/* dmae to get the VF request */
		rc = bnx2x_copy32_vf_dmae(bp, true, mbx->msg_mapping,
					  vf->असल_vfid, mbx->vf_addr_hi,
					  mbx->vf_addr_lo,
					  माप(जोड़ vfpf_tlvs)/4);
		अगर (rc) अणु
			BNX2X_ERR("Failed to copy request VF %d\n",
				  vf->असल_vfid);
			bnx2x_vf_release(bp, vf);
			वापस;
		पूर्ण

		/* process the VF message header */
		mbx->first_tlv = mbx->msg->req.first_tlv;

		/* Clean response buffer to refrain from falsely
		 * seeing chains.
		 */
		स_रखो(&mbx->msg->resp, 0, माप(जोड़ pfvf_tlvs));

		/* dispatch the request (will prepare the response) */
		bnx2x_vf_mbx_request(bp, vf, mbx);
	पूर्ण
पूर्ण

व्योम bnx2x_vf_bulletin_finalize(काष्ठा pf_vf_bulletin_content *bulletin,
				bool support_दीर्घ)
अणु
	/* Older VFs contain a bug where they can't check CRC क्रम bulletin
	 * boards of length greater than legacy size.
	 */
	bulletin->length = support_दीर्घ ? BULLETIN_CONTENT_SIZE :
					  BULLETIN_CONTENT_LEGACY_SIZE;
	bulletin->crc = bnx2x_crc_vf_bulletin(bulletin);
पूर्ण

/* propagate local bulletin board to vf */
पूर्णांक bnx2x_post_vf_bulletin(काष्ठा bnx2x *bp, पूर्णांक vf)
अणु
	काष्ठा pf_vf_bulletin_content *bulletin = BP_VF_BULLETIN(bp, vf);
	dma_addr_t pf_addr = BP_VF_BULLETIN_DMA(bp)->mapping +
		vf * BULLETIN_CONTENT_SIZE;
	dma_addr_t vf_addr = bnx2x_vf(bp, vf, bulletin_map);
	पूर्णांक rc;

	/* can only update vf after init took place */
	अगर (bnx2x_vf(bp, vf, state) != VF_ENABLED &&
	    bnx2x_vf(bp, vf, state) != VF_ACQUIRED)
		वापस 0;

	/* increment bulletin board version and compute crc */
	bulletin->version++;
	bnx2x_vf_bulletin_finalize(bulletin,
				   (bnx2x_vf(bp, vf, cfg_flags) &
				    VF_CFG_EXT_BULLETIN) ? true : false);

	/* propagate bulletin board via dmae to vm memory */
	rc = bnx2x_copy32_vf_dmae(bp, false, pf_addr,
				  bnx2x_vf(bp, vf, असल_vfid), U64_HI(vf_addr),
				  U64_LO(vf_addr), bulletin->length / 4);
	वापस rc;
पूर्ण
