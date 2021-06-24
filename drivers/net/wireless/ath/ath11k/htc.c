<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */
#समावेश <linux/skbuff.h>
#समावेश <linux/प्रकार.स>

#समावेश "debug.h"
#समावेश "hif.h"

काष्ठा sk_buff *ath11k_htc_alloc_skb(काष्ठा ath11k_base *ab, पूर्णांक size)
अणु
	काष्ठा sk_buff *skb;

	skb = dev_alloc_skb(size + माप(काष्ठा ath11k_htc_hdr));
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, माप(काष्ठा ath11k_htc_hdr));

	/* FW/HTC requires 4-byte aligned streams */
	अगर (!IS_ALIGNED((अचिन्हित दीर्घ)skb->data, 4))
		ath11k_warn(ab, "Unaligned HTC tx skb\n");

	वापस skb;
पूर्ण

अटल व्योम ath11k_htc_control_tx_complete(काष्ठा ath11k_base *ab,
					   काष्ठा sk_buff *skb)
अणु
	kमुक्त_skb(skb);
पूर्ण

अटल काष्ठा sk_buff *ath11k_htc_build_tx_ctrl_skb(व्योम *ab)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ath11k_skb_cb *skb_cb;

	skb = dev_alloc_skb(ATH11K_HTC_CONTROL_BUFFER_SIZE);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, माप(काष्ठा ath11k_htc_hdr));
	WARN_ON_ONCE(!IS_ALIGNED((अचिन्हित दीर्घ)skb->data, 4));

	skb_cb = ATH11K_SKB_CB(skb);
	स_रखो(skb_cb, 0, माप(*skb_cb));

	ath11k_dbg(ab, ATH11K_DBG_HTC, "%s: skb %pK\n", __func__, skb);
	वापस skb;
पूर्ण

अटल व्योम ath11k_htc_prepare_tx_skb(काष्ठा ath11k_htc_ep *ep,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा ath11k_htc_hdr *hdr;

	hdr = (काष्ठा ath11k_htc_hdr *)skb->data;

	स_रखो(hdr, 0, माप(*hdr));
	hdr->htc_info = FIELD_PREP(HTC_HDR_ENDPOINTID, ep->eid) |
			FIELD_PREP(HTC_HDR_PAYLOADLEN,
				   (skb->len - माप(*hdr)));

	अगर (ep->tx_credit_flow_enabled)
		hdr->htc_info |= FIELD_PREP(HTC_HDR_FLAGS,
					    ATH11K_HTC_FLAG_NEED_CREDIT_UPDATE);

	spin_lock_bh(&ep->htc->tx_lock);
	hdr->ctrl_info = FIELD_PREP(HTC_HDR_CONTROLBYTES1, ep->seq_no++);
	spin_unlock_bh(&ep->htc->tx_lock);
पूर्ण

पूर्णांक ath11k_htc_send(काष्ठा ath11k_htc *htc,
		    क्रमागत ath11k_htc_ep_id eid,
		    काष्ठा sk_buff *skb)
अणु
	काष्ठा ath11k_htc_ep *ep = &htc->endpoपूर्णांक[eid];
	काष्ठा ath11k_skb_cb *skb_cb = ATH11K_SKB_CB(skb);
	काष्ठा device *dev = htc->ab->dev;
	काष्ठा ath11k_base *ab = htc->ab;
	पूर्णांक credits = 0;
	पूर्णांक ret;

	अगर (eid >= ATH11K_HTC_EP_COUNT) अणु
		ath11k_warn(ab, "Invalid endpoint id: %d\n", eid);
		वापस -ENOENT;
	पूर्ण

	skb_push(skb, माप(काष्ठा ath11k_htc_hdr));

	अगर (ep->tx_credit_flow_enabled) अणु
		credits = DIV_ROUND_UP(skb->len, htc->target_credit_size);
		spin_lock_bh(&htc->tx_lock);
		अगर (ep->tx_credits < credits) अणु
			ath11k_dbg(ab, ATH11K_DBG_HTC,
				   "htc insufficient credits ep %d required %d available %d\n",
				   eid, credits, ep->tx_credits);
			spin_unlock_bh(&htc->tx_lock);
			ret = -EAGAIN;
			जाओ err_pull;
		पूर्ण
		ep->tx_credits -= credits;
		ath11k_dbg(ab, ATH11K_DBG_HTC,
			   "htc ep %d consumed %d credits (total %d)\n",
			   eid, credits, ep->tx_credits);
		spin_unlock_bh(&htc->tx_lock);
	पूर्ण

	ath11k_htc_prepare_tx_skb(ep, skb);

	skb_cb->eid = eid;
	skb_cb->paddr = dma_map_single(dev, skb->data, skb->len, DMA_TO_DEVICE);
	ret = dma_mapping_error(dev, skb_cb->paddr);
	अगर (ret) अणु
		ret = -EIO;
		जाओ err_credits;
	पूर्ण

	ret = ath11k_ce_send(htc->ab, skb, ep->ul_pipe_id, ep->eid);
	अगर (ret)
		जाओ err_unmap;

	वापस 0;

err_unmap:
	dma_unmap_single(dev, skb_cb->paddr, skb->len, DMA_TO_DEVICE);
err_credits:
	अगर (ep->tx_credit_flow_enabled) अणु
		spin_lock_bh(&htc->tx_lock);
		ep->tx_credits += credits;
		ath11k_dbg(ab, ATH11K_DBG_HTC,
			   "htc ep %d reverted %d credits back (total %d)\n",
			   eid, credits, ep->tx_credits);
		spin_unlock_bh(&htc->tx_lock);

		अगर (ep->ep_ops.ep_tx_credits)
			ep->ep_ops.ep_tx_credits(htc->ab);
	पूर्ण
err_pull:
	skb_pull(skb, माप(काष्ठा ath11k_htc_hdr));
	वापस ret;
पूर्ण

अटल व्योम
ath11k_htc_process_credit_report(काष्ठा ath11k_htc *htc,
				 स्थिर काष्ठा ath11k_htc_credit_report *report,
				 पूर्णांक len,
				 क्रमागत ath11k_htc_ep_id eid)
अणु
	काष्ठा ath11k_base *ab = htc->ab;
	काष्ठा ath11k_htc_ep *ep;
	पूर्णांक i, n_reports;

	अगर (len % माप(*report))
		ath11k_warn(ab, "Uneven credit report len %d", len);

	n_reports = len / माप(*report);

	spin_lock_bh(&htc->tx_lock);
	क्रम (i = 0; i < n_reports; i++, report++) अणु
		अगर (report->eid >= ATH11K_HTC_EP_COUNT)
			अवरोध;

		ep = &htc->endpoपूर्णांक[report->eid];
		ep->tx_credits += report->credits;

		ath11k_dbg(ab, ATH11K_DBG_HTC, "htc ep %d got %d credits (total %d)\n",
			   report->eid, report->credits, ep->tx_credits);

		अगर (ep->ep_ops.ep_tx_credits) अणु
			spin_unlock_bh(&htc->tx_lock);
			ep->ep_ops.ep_tx_credits(htc->ab);
			spin_lock_bh(&htc->tx_lock);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&htc->tx_lock);
पूर्ण

अटल पूर्णांक ath11k_htc_process_trailer(काष्ठा ath11k_htc *htc,
				      u8 *buffer,
				      पूर्णांक length,
				      क्रमागत ath11k_htc_ep_id src_eid)
अणु
	काष्ठा ath11k_base *ab = htc->ab;
	पूर्णांक status = 0;
	काष्ठा ath11k_htc_record *record;
	माप_प्रकार len;

	जबतक (length > 0) अणु
		record = (काष्ठा ath11k_htc_record *)buffer;

		अगर (length < माप(record->hdr)) अणु
			status = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (record->hdr.len > length) अणु
			/* no room left in buffer क्रम record */
			ath11k_warn(ab, "Invalid record length: %d\n",
				    record->hdr.len);
			status = -EINVAL;
			अवरोध;
		पूर्ण

		चयन (record->hdr.id) अणु
		हाल ATH11K_HTC_RECORD_CREDITS:
			len = माप(काष्ठा ath11k_htc_credit_report);
			अगर (record->hdr.len < len) अणु
				ath11k_warn(ab, "Credit report too long\n");
				status = -EINVAL;
				अवरोध;
			पूर्ण
			ath11k_htc_process_credit_report(htc,
							 record->credit_report,
							 record->hdr.len,
							 src_eid);
			अवरोध;
		शेष:
			ath11k_warn(ab, "Unhandled record: id:%d length:%d\n",
				    record->hdr.id, record->hdr.len);
			अवरोध;
		पूर्ण

		अगर (status)
			अवरोध;

		/* multiple records may be present in a trailer */
		buffer += माप(record->hdr) + record->hdr.len;
		length -= माप(record->hdr) + record->hdr.len;
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम ath11k_htc_suspend_complete(काष्ठा ath11k_base *ab, bool ack)
अणु
	ath11k_dbg(ab, ATH11K_DBG_BOOT, "boot suspend complete %d\n", ack);

	अगर (ack)
		set_bit(ATH11K_FLAG_HTC_SUSPEND_COMPLETE, &ab->dev_flags);
	अन्यथा
		clear_bit(ATH11K_FLAG_HTC_SUSPEND_COMPLETE, &ab->dev_flags);

	complete(&ab->htc_suspend);
पूर्ण

व्योम ath11k_htc_rx_completion_handler(काष्ठा ath11k_base *ab,
				      काष्ठा sk_buff *skb)
अणु
	पूर्णांक status = 0;
	काष्ठा ath11k_htc *htc = &ab->htc;
	काष्ठा ath11k_htc_hdr *hdr;
	काष्ठा ath11k_htc_ep *ep;
	u16 payload_len;
	u32 trailer_len = 0;
	माप_प्रकार min_len;
	u8 eid;
	bool trailer_present;

	hdr = (काष्ठा ath11k_htc_hdr *)skb->data;
	skb_pull(skb, माप(*hdr));

	eid = FIELD_GET(HTC_HDR_ENDPOINTID, hdr->htc_info);

	अगर (eid >= ATH11K_HTC_EP_COUNT) अणु
		ath11k_warn(ab, "HTC Rx: invalid eid %d\n", eid);
		जाओ out;
	पूर्ण

	ep = &htc->endpoपूर्णांक[eid];

	payload_len = FIELD_GET(HTC_HDR_PAYLOADLEN, hdr->htc_info);

	अगर (payload_len + माप(*hdr) > ATH11K_HTC_MAX_LEN) अणु
		ath11k_warn(ab, "HTC rx frame too long, len: %zu\n",
			    payload_len + माप(*hdr));
		जाओ out;
	पूर्ण

	अगर (skb->len < payload_len) अणु
		ath11k_warn(ab, "HTC Rx: insufficient length, got %d, expected %d\n",
			    skb->len, payload_len);
		जाओ out;
	पूर्ण

	/* get flags to check क्रम trailer */
	trailer_present = (FIELD_GET(HTC_HDR_FLAGS, hdr->htc_info)) &
			  ATH11K_HTC_FLAG_TRAILER_PRESENT;

	अगर (trailer_present) अणु
		u8 *trailer;

		trailer_len = FIELD_GET(HTC_HDR_CONTROLBYTES0, hdr->ctrl_info);
		min_len = माप(काष्ठा ath11k_htc_record_hdr);

		अगर ((trailer_len < min_len) ||
		    (trailer_len > payload_len)) अणु
			ath11k_warn(ab, "Invalid trailer length: %d\n",
				    trailer_len);
			जाओ out;
		पूर्ण

		trailer = (u8 *)hdr;
		trailer += माप(*hdr);
		trailer += payload_len;
		trailer -= trailer_len;
		status = ath11k_htc_process_trailer(htc, trailer,
						    trailer_len, eid);
		अगर (status)
			जाओ out;

		skb_trim(skb, skb->len - trailer_len);
	पूर्ण

	अगर (trailer_len >= payload_len)
		/* zero length packet with trailer data, just drop these */
		जाओ out;

	अगर (eid == ATH11K_HTC_EP_0) अणु
		काष्ठा ath11k_htc_msg *msg = (काष्ठा ath11k_htc_msg *)skb->data;

		चयन (FIELD_GET(HTC_MSG_MESSAGEID, msg->msg_svc_id)) अणु
		हाल ATH11K_HTC_MSG_READY_ID:
		हाल ATH11K_HTC_MSG_CONNECT_SERVICE_RESP_ID:
			/* handle HTC control message */
			अगर (completion_करोne(&htc->ctl_resp)) अणु
				/* this is a fatal error, target should not be
				 * sending unsolicited messages on the ep 0
				 */
				ath11k_warn(ab, "HTC rx ctrl still processing\n");
				complete(&htc->ctl_resp);
				जाओ out;
			पूर्ण

			htc->control_resp_len =
				min_t(पूर्णांक, skb->len,
				      ATH11K_HTC_MAX_CTRL_MSG_LEN);

			स_नकल(htc->control_resp_buffer, skb->data,
			       htc->control_resp_len);

			complete(&htc->ctl_resp);
			अवरोध;
		हाल ATH11K_HTC_MSG_SEND_SUSPEND_COMPLETE:
			ath11k_htc_suspend_complete(ab, true);
			अवरोध;
		हाल ATH11K_HTC_MSG_NACK_SUSPEND:
			ath11k_htc_suspend_complete(ab, false);
			अवरोध;
		हाल ATH11K_HTC_MSG_WAKEUP_FROM_SUSPEND_ID:
			अवरोध;
		शेष:
			ath11k_warn(ab, "ignoring unsolicited htc ep0 event %ld\n",
				    FIELD_GET(HTC_MSG_MESSAGEID, msg->msg_svc_id));
			अवरोध;
		पूर्ण
		जाओ out;
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_HTC, "htc rx completion ep %d skb %pK\n",
		   eid, skb);
	ep->ep_ops.ep_rx_complete(ab, skb);

	/* poll tx completion क्रम पूर्णांकerrupt disabled CE's */
	ath11k_ce_poll_send_completed(ab, ep->ul_pipe_id);

	/* skb is now owned by the rx completion handler */
	skb = शून्य;
out:
	kमुक्त_skb(skb);
पूर्ण

अटल व्योम ath11k_htc_control_rx_complete(काष्ठा ath11k_base *ab,
					   काष्ठा sk_buff *skb)
अणु
	/* This is unexpected. FW is not supposed to send regular rx on this
	 * endpoपूर्णांक.
	 */
	ath11k_warn(ab, "unexpected htc rx\n");
	kमुक्त_skb(skb);
पूर्ण

अटल स्थिर अक्षर *htc_service_name(क्रमागत ath11k_htc_svc_id id)
अणु
	चयन (id) अणु
	हाल ATH11K_HTC_SVC_ID_RESERVED:
		वापस "Reserved";
	हाल ATH11K_HTC_SVC_ID_RSVD_CTRL:
		वापस "Control";
	हाल ATH11K_HTC_SVC_ID_WMI_CONTROL:
		वापस "WMI";
	हाल ATH11K_HTC_SVC_ID_WMI_DATA_BE:
		वापस "DATA BE";
	हाल ATH11K_HTC_SVC_ID_WMI_DATA_BK:
		वापस "DATA BK";
	हाल ATH11K_HTC_SVC_ID_WMI_DATA_VI:
		वापस "DATA VI";
	हाल ATH11K_HTC_SVC_ID_WMI_DATA_VO:
		वापस "DATA VO";
	हाल ATH11K_HTC_SVC_ID_WMI_CONTROL_MAC1:
		वापस "WMI MAC1";
	हाल ATH11K_HTC_SVC_ID_WMI_CONTROL_MAC2:
		वापस "WMI MAC2";
	हाल ATH11K_HTC_SVC_ID_NMI_CONTROL:
		वापस "NMI Control";
	हाल ATH11K_HTC_SVC_ID_NMI_DATA:
		वापस "NMI Data";
	हाल ATH11K_HTC_SVC_ID_HTT_DATA_MSG:
		वापस "HTT Data";
	हाल ATH11K_HTC_SVC_ID_TEST_RAW_STREAMS:
		वापस "RAW";
	हाल ATH11K_HTC_SVC_ID_IPA_TX:
		वापस "IPA TX";
	हाल ATH11K_HTC_SVC_ID_PKT_LOG:
		वापस "PKT LOG";
	पूर्ण

	वापस "Unknown";
पूर्ण

अटल व्योम ath11k_htc_reset_endpoपूर्णांक_states(काष्ठा ath11k_htc *htc)
अणु
	काष्ठा ath11k_htc_ep *ep;
	पूर्णांक i;

	क्रम (i = ATH11K_HTC_EP_0; i < ATH11K_HTC_EP_COUNT; i++) अणु
		ep = &htc->endpoपूर्णांक[i];
		ep->service_id = ATH11K_HTC_SVC_ID_UNUSED;
		ep->max_ep_message_len = 0;
		ep->max_tx_queue_depth = 0;
		ep->eid = i;
		ep->htc = htc;
		ep->tx_credit_flow_enabled = true;
	पूर्ण
पूर्ण

अटल u8 ath11k_htc_get_credit_allocation(काष्ठा ath11k_htc *htc,
					   u16 service_id)
अणु
	u8 i, allocation = 0;

	क्रम (i = 0; i < ATH11K_HTC_MAX_SERVICE_ALLOC_ENTRIES; i++) अणु
		अगर (htc->service_alloc_table[i].service_id == service_id) अणु
			allocation =
				htc->service_alloc_table[i].credit_allocation;
		पूर्ण
	पूर्ण

	वापस allocation;
पूर्ण

अटल पूर्णांक ath11k_htc_setup_target_buffer_assignments(काष्ठा ath11k_htc *htc)
अणु
	काष्ठा ath11k_htc_svc_tx_credits *serv_entry;
	u32 svc_id[] = अणु
		ATH11K_HTC_SVC_ID_WMI_CONTROL,
		ATH11K_HTC_SVC_ID_WMI_CONTROL_MAC1,
		ATH11K_HTC_SVC_ID_WMI_CONTROL_MAC2,
	पूर्ण;
	पूर्णांक i, credits;

	credits =  htc->total_transmit_credits;
	serv_entry = htc->service_alloc_table;

	अगर ((htc->wmi_ep_count == 0) ||
	    (htc->wmi_ep_count > ARRAY_SIZE(svc_id)))
		वापस -EINVAL;

	/* Divide credits among number of endpoपूर्णांकs क्रम WMI */
	credits = credits / htc->wmi_ep_count;
	क्रम (i = 0; i < htc->wmi_ep_count; i++) अणु
		serv_entry[i].service_id = svc_id[i];
		serv_entry[i].credit_allocation = credits;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath11k_htc_रुको_target(काष्ठा ath11k_htc *htc)
अणु
	पूर्णांक i, status = 0;
	काष्ठा ath11k_base *ab = htc->ab;
	अचिन्हित दीर्घ समय_left;
	काष्ठा ath11k_htc_पढ़ोy *पढ़ोy;
	u16 message_id;
	u16 credit_count;
	u16 credit_size;

	समय_left = रुको_क्रम_completion_समयout(&htc->ctl_resp,
						ATH11K_HTC_WAIT_TIMEOUT_HZ);
	अगर (!समय_left) अणु
		ath11k_warn(ab, "failed to receive control response completion, polling..\n");

		क्रम (i = 0; i < ab->hw_params.ce_count; i++)
			ath11k_ce_per_engine_service(htc->ab, i);

		समय_left =
			रुको_क्रम_completion_समयout(&htc->ctl_resp,
						    ATH11K_HTC_WAIT_TIMEOUT_HZ);

		अगर (!समय_left)
			status = -ETIMEDOUT;
	पूर्ण

	अगर (status < 0) अणु
		ath11k_warn(ab, "ctl_resp never came in (%d)\n", status);
		वापस status;
	पूर्ण

	अगर (htc->control_resp_len < माप(*पढ़ोy)) अणु
		ath11k_warn(ab, "Invalid HTC ready msg len:%d\n",
			    htc->control_resp_len);
		वापस -ECOMM;
	पूर्ण

	पढ़ोy = (काष्ठा ath11k_htc_पढ़ोy *)htc->control_resp_buffer;
	message_id   = FIELD_GET(HTC_MSG_MESSAGEID, पढ़ोy->id_credit_count);
	credit_count = FIELD_GET(HTC_READY_MSG_CREDITCOUNT,
				 पढ़ोy->id_credit_count);
	credit_size  = FIELD_GET(HTC_READY_MSG_CREDITSIZE, पढ़ोy->size_ep);

	अगर (message_id != ATH11K_HTC_MSG_READY_ID) अणु
		ath11k_warn(ab, "Invalid HTC ready msg: 0x%x\n", message_id);
		वापस -ECOMM;
	पूर्ण

	htc->total_transmit_credits = credit_count;
	htc->target_credit_size = credit_size;

	ath11k_dbg(ab, ATH11K_DBG_HTC,
		   "Target ready! transmit resources: %d size:%d\n",
		   htc->total_transmit_credits, htc->target_credit_size);

	अगर ((htc->total_transmit_credits == 0) ||
	    (htc->target_credit_size == 0)) अणु
		ath11k_warn(ab, "Invalid credit size received\n");
		वापस -ECOMM;
	पूर्ण

	/* For QCA6390, wmi endpoपूर्णांक uses 1 credit to aव्योम
	 * back-to-back ग_लिखो.
	 */
	अगर (ab->hw_params.supports_shaकरोw_regs)
		htc->total_transmit_credits = 1;

	ath11k_htc_setup_target_buffer_assignments(htc);

	वापस 0;
पूर्ण

पूर्णांक ath11k_htc_connect_service(काष्ठा ath11k_htc *htc,
			       काष्ठा ath11k_htc_svc_conn_req *conn_req,
			       काष्ठा ath11k_htc_svc_conn_resp *conn_resp)
अणु
	काष्ठा ath11k_base *ab = htc->ab;
	काष्ठा ath11k_htc_conn_svc *req_msg;
	काष्ठा ath11k_htc_conn_svc_resp resp_msg_dummy;
	काष्ठा ath11k_htc_conn_svc_resp *resp_msg = &resp_msg_dummy;
	क्रमागत ath11k_htc_ep_id asचिन्हित_eid = ATH11K_HTC_EP_COUNT;
	काष्ठा ath11k_htc_ep *ep;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक max_msg_size = 0;
	पूर्णांक length, status;
	अचिन्हित दीर्घ समय_left;
	bool disable_credit_flow_ctrl = false;
	u16 message_id, service_id, flags = 0;
	u8 tx_alloc = 0;

	/* special हाल क्रम HTC pseuकरो control service */
	अगर (conn_req->service_id == ATH11K_HTC_SVC_ID_RSVD_CTRL) अणु
		disable_credit_flow_ctrl = true;
		asचिन्हित_eid = ATH11K_HTC_EP_0;
		max_msg_size = ATH11K_HTC_MAX_CTRL_MSG_LEN;
		स_रखो(&resp_msg_dummy, 0, माप(resp_msg_dummy));
		जाओ setup;
	पूर्ण

	tx_alloc = ath11k_htc_get_credit_allocation(htc,
						    conn_req->service_id);
	अगर (!tx_alloc)
		ath11k_dbg(ab, ATH11K_DBG_BOOT,
			   "boot htc service %s does not allocate target credits\n",
			   htc_service_name(conn_req->service_id));

	skb = ath11k_htc_build_tx_ctrl_skb(htc->ab);
	अगर (!skb) अणु
		ath11k_warn(ab, "Failed to allocate HTC packet\n");
		वापस -ENOMEM;
	पूर्ण

	length = माप(*req_msg);
	skb_put(skb, length);
	स_रखो(skb->data, 0, length);

	req_msg = (काष्ठा ath11k_htc_conn_svc *)skb->data;
	req_msg->msg_svc_id = FIELD_PREP(HTC_MSG_MESSAGEID,
					 ATH11K_HTC_MSG_CONNECT_SERVICE_ID);

	flags |= FIELD_PREP(ATH11K_HTC_CONN_FLAGS_RECV_ALLOC, tx_alloc);

	/* Only enable credit flow control क्रम WMI ctrl service */
	अगर (!(conn_req->service_id == ATH11K_HTC_SVC_ID_WMI_CONTROL ||
	      conn_req->service_id == ATH11K_HTC_SVC_ID_WMI_CONTROL_MAC1 ||
	      conn_req->service_id == ATH11K_HTC_SVC_ID_WMI_CONTROL_MAC2)) अणु
		flags |= ATH11K_HTC_CONN_FLAGS_DISABLE_CREDIT_FLOW_CTRL;
		disable_credit_flow_ctrl = true;
	पूर्ण

	req_msg->flags_len = FIELD_PREP(HTC_SVC_MSG_CONNECTIONFLAGS, flags);
	req_msg->msg_svc_id |= FIELD_PREP(HTC_SVC_MSG_SERVICE_ID,
					  conn_req->service_id);

	reinit_completion(&htc->ctl_resp);

	status = ath11k_htc_send(htc, ATH11K_HTC_EP_0, skb);
	अगर (status) अणु
		kमुक्त_skb(skb);
		वापस status;
	पूर्ण

	/* रुको क्रम response */
	समय_left = रुको_क्रम_completion_समयout(&htc->ctl_resp,
						ATH11K_HTC_CONN_SVC_TIMEOUT_HZ);
	अगर (!समय_left) अणु
		ath11k_err(ab, "Service connect timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	/* we controlled the buffer creation, it's aligned */
	resp_msg = (काष्ठा ath11k_htc_conn_svc_resp *)htc->control_resp_buffer;
	message_id = FIELD_GET(HTC_MSG_MESSAGEID, resp_msg->msg_svc_id);
	service_id = FIELD_GET(HTC_SVC_RESP_MSG_SERVICEID,
			       resp_msg->msg_svc_id);

	अगर ((message_id != ATH11K_HTC_MSG_CONNECT_SERVICE_RESP_ID) ||
	    (htc->control_resp_len < माप(*resp_msg))) अणु
		ath11k_err(ab, "Invalid resp message ID 0x%x", message_id);
		वापस -EPROTO;
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_HTC,
		   "HTC Service %s connect response: status: 0x%lx, assigned ep: 0x%lx\n",
		   htc_service_name(service_id),
		   FIELD_GET(HTC_SVC_RESP_MSG_STATUS, resp_msg->flags_len),
		   FIELD_GET(HTC_SVC_RESP_MSG_ENDPOINTID, resp_msg->flags_len));

	conn_resp->connect_resp_code = FIELD_GET(HTC_SVC_RESP_MSG_STATUS,
						 resp_msg->flags_len);

	/* check response status */
	अगर (conn_resp->connect_resp_code != ATH11K_HTC_CONN_SVC_STATUS_SUCCESS) अणु
		ath11k_err(ab, "HTC Service %s connect request failed: 0x%x)\n",
			   htc_service_name(service_id),
		       conn_resp->connect_resp_code);
		वापस -EPROTO;
	पूर्ण

	asचिन्हित_eid = (क्रमागत ath11k_htc_ep_id)FIELD_GET(
						HTC_SVC_RESP_MSG_ENDPOINTID,
						resp_msg->flags_len);

	max_msg_size = FIELD_GET(HTC_SVC_RESP_MSG_MAXMSGSIZE,
				 resp_msg->flags_len);

setup:

	अगर (asचिन्हित_eid >= ATH11K_HTC_EP_COUNT)
		वापस -EPROTO;

	अगर (max_msg_size == 0)
		वापस -EPROTO;

	ep = &htc->endpoपूर्णांक[asचिन्हित_eid];
	ep->eid = asचिन्हित_eid;

	अगर (ep->service_id != ATH11K_HTC_SVC_ID_UNUSED)
		वापस -EPROTO;

	/* वापस asचिन्हित endpoपूर्णांक to caller */
	conn_resp->eid = asचिन्हित_eid;
	conn_resp->max_msg_len = FIELD_GET(HTC_SVC_RESP_MSG_MAXMSGSIZE,
					   resp_msg->flags_len);

	/* setup the endpoपूर्णांक */
	ep->service_id = conn_req->service_id;
	ep->max_tx_queue_depth = conn_req->max_send_queue_depth;
	ep->max_ep_message_len = FIELD_GET(HTC_SVC_RESP_MSG_MAXMSGSIZE,
					   resp_msg->flags_len);
	ep->tx_credits = tx_alloc;

	/* copy all the callbacks */
	ep->ep_ops = conn_req->ep_ops;

	status = ath11k_hअगर_map_service_to_pipe(htc->ab,
						ep->service_id,
						&ep->ul_pipe_id,
						&ep->dl_pipe_id);
	अगर (status)
		वापस status;

	ath11k_dbg(ab, ATH11K_DBG_BOOT,
		   "boot htc service '%s' ul pipe %d dl pipe %d eid %d ready\n",
		   htc_service_name(ep->service_id), ep->ul_pipe_id,
		   ep->dl_pipe_id, ep->eid);

	अगर (disable_credit_flow_ctrl && ep->tx_credit_flow_enabled) अणु
		ep->tx_credit_flow_enabled = false;
		ath11k_dbg(ab, ATH11K_DBG_BOOT,
			   "boot htc service '%s' eid %d TX flow control disabled\n",
			   htc_service_name(ep->service_id), asचिन्हित_eid);
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक ath11k_htc_start(काष्ठा ath11k_htc *htc)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक status = 0;
	काष्ठा ath11k_base *ab = htc->ab;
	काष्ठा ath11k_htc_setup_complete_extended *msg;

	skb = ath11k_htc_build_tx_ctrl_skb(htc->ab);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, माप(*msg));
	स_रखो(skb->data, 0, skb->len);

	msg = (काष्ठा ath11k_htc_setup_complete_extended *)skb->data;
	msg->msg_id = FIELD_PREP(HTC_MSG_MESSAGEID,
				 ATH11K_HTC_MSG_SETUP_COMPLETE_EX_ID);

	ath11k_dbg(ab, ATH11K_DBG_HTC, "HTC is using TX credit flow control\n");

	status = ath11k_htc_send(htc, ATH11K_HTC_EP_0, skb);
	अगर (status) अणु
		kमुक्त_skb(skb);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath11k_htc_init(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_htc *htc = &ab->htc;
	काष्ठा ath11k_htc_svc_conn_req conn_req;
	काष्ठा ath11k_htc_svc_conn_resp conn_resp;
	पूर्णांक ret;

	spin_lock_init(&htc->tx_lock);

	ath11k_htc_reset_endpoपूर्णांक_states(htc);

	htc->ab = ab;

	चयन (ab->wmi_ab.preferred_hw_mode) अणु
	हाल WMI_HOST_HW_MODE_SINGLE:
		htc->wmi_ep_count = 1;
		अवरोध;
	हाल WMI_HOST_HW_MODE_DBS:
	हाल WMI_HOST_HW_MODE_DBS_OR_SBS:
		htc->wmi_ep_count = 2;
		अवरोध;
	हाल WMI_HOST_HW_MODE_DBS_SBS:
		htc->wmi_ep_count = 3;
		अवरोध;
	शेष:
		htc->wmi_ep_count = ab->hw_params.max_radios;
		अवरोध;
	पूर्ण

	/* setup our pseuकरो HTC control endpoपूर्णांक connection */
	स_रखो(&conn_req, 0, माप(conn_req));
	स_रखो(&conn_resp, 0, माप(conn_resp));
	conn_req.ep_ops.ep_tx_complete = ath11k_htc_control_tx_complete;
	conn_req.ep_ops.ep_rx_complete = ath11k_htc_control_rx_complete;
	conn_req.max_send_queue_depth = ATH11K_NUM_CONTROL_TX_BUFFERS;
	conn_req.service_id = ATH11K_HTC_SVC_ID_RSVD_CTRL;

	/* connect fake service */
	ret = ath11k_htc_connect_service(htc, &conn_req, &conn_resp);
	अगर (ret) अणु
		ath11k_err(ab, "could not connect to htc service (%d)\n", ret);
		वापस ret;
	पूर्ण

	init_completion(&htc->ctl_resp);

	वापस 0;
पूर्ण
