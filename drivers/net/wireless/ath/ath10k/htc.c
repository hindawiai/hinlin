<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2017 Qualcomm Atheros, Inc.
 */

#समावेश "core.h"
#समावेश "hif.h"
#समावेश "debug.h"

/********/
/* Send */
/********/

अटल व्योम ath10k_htc_control_tx_complete(काष्ठा ath10k *ar,
					   काष्ठा sk_buff *skb)
अणु
	kमुक्त_skb(skb);
पूर्ण

अटल काष्ठा sk_buff *ath10k_htc_build_tx_ctrl_skb(व्योम *ar)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ath10k_skb_cb *skb_cb;

	skb = dev_alloc_skb(ATH10K_HTC_CONTROL_BUFFER_SIZE);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, 20); /* FIXME: why 20 bytes? */
	WARN_ONCE((अचिन्हित दीर्घ)skb->data & 3, "unaligned skb");

	skb_cb = ATH10K_SKB_CB(skb);
	स_रखो(skb_cb, 0, माप(*skb_cb));

	ath10k_dbg(ar, ATH10K_DBG_HTC, "%s: skb %pK\n", __func__, skb);
	वापस skb;
पूर्ण

अटल अंतरभूत व्योम ath10k_htc_restore_tx_skb(काष्ठा ath10k_htc *htc,
					     काष्ठा sk_buff *skb)
अणु
	काष्ठा ath10k_skb_cb *skb_cb = ATH10K_SKB_CB(skb);

	अगर (htc->ar->bus_param.dev_type != ATH10K_DEV_TYPE_HL)
		dma_unmap_single(htc->ar->dev, skb_cb->paddr, skb->len, DMA_TO_DEVICE);
	skb_pull(skb, माप(काष्ठा ath10k_htc_hdr));
पूर्ण

व्योम ath10k_htc_notअगरy_tx_completion(काष्ठा ath10k_htc_ep *ep,
				     काष्ठा sk_buff *skb)
अणु
	काष्ठा ath10k *ar = ep->htc->ar;
	काष्ठा ath10k_htc_hdr *hdr;

	ath10k_dbg(ar, ATH10K_DBG_HTC, "%s: ep %d skb %pK\n", __func__,
		   ep->eid, skb);

	hdr = (काष्ठा ath10k_htc_hdr *)skb->data;
	ath10k_htc_restore_tx_skb(ep->htc, skb);

	अगर (!ep->ep_ops.ep_tx_complete) अणु
		ath10k_warn(ar, "no tx handler for eid %d\n", ep->eid);
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	अगर (hdr->flags & ATH10K_HTC_FLAG_SEND_BUNDLE) अणु
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	ep->ep_ops.ep_tx_complete(ep->htc->ar, skb);
पूर्ण
EXPORT_SYMBOL(ath10k_htc_notअगरy_tx_completion);

अटल व्योम ath10k_htc_prepare_tx_skb(काष्ठा ath10k_htc_ep *ep,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा ath10k_htc_hdr *hdr;

	hdr = (काष्ठा ath10k_htc_hdr *)skb->data;
	स_रखो(hdr, 0, माप(काष्ठा ath10k_htc_hdr));

	hdr->eid = ep->eid;
	hdr->len = __cpu_to_le16(skb->len - माप(*hdr));
	hdr->flags = 0;
	अगर (ep->tx_credit_flow_enabled && !ep->bundle_tx)
		hdr->flags |= ATH10K_HTC_FLAG_NEED_CREDIT_UPDATE;

	spin_lock_bh(&ep->htc->tx_lock);
	hdr->seq_no = ep->seq_no++;
	spin_unlock_bh(&ep->htc->tx_lock);
पूर्ण

अटल पूर्णांक ath10k_htc_consume_credit(काष्ठा ath10k_htc_ep *ep,
				     अचिन्हित पूर्णांक len,
				     bool consume)
अणु
	काष्ठा ath10k_htc *htc = ep->htc;
	काष्ठा ath10k *ar = htc->ar;
	क्रमागत ath10k_htc_ep_id eid = ep->eid;
	पूर्णांक credits, ret = 0;

	अगर (!ep->tx_credit_flow_enabled)
		वापस 0;

	credits = DIV_ROUND_UP(len, ep->tx_credit_size);
	spin_lock_bh(&htc->tx_lock);

	अगर (ep->tx_credits < credits) अणु
		ath10k_dbg(ar, ATH10K_DBG_HTC,
			   "htc insufficient credits ep %d required %d available %d consume %d\n",
			   eid, credits, ep->tx_credits, consume);
		ret = -EAGAIN;
		जाओ unlock;
	पूर्ण

	अगर (consume) अणु
		ep->tx_credits -= credits;
		ath10k_dbg(ar, ATH10K_DBG_HTC,
			   "htc ep %d consumed %d credits total %d\n",
			   eid, credits, ep->tx_credits);
	पूर्ण

unlock:
	spin_unlock_bh(&htc->tx_lock);
	वापस ret;
पूर्ण

अटल व्योम ath10k_htc_release_credit(काष्ठा ath10k_htc_ep *ep, अचिन्हित पूर्णांक len)
अणु
	काष्ठा ath10k_htc *htc = ep->htc;
	काष्ठा ath10k *ar = htc->ar;
	क्रमागत ath10k_htc_ep_id eid = ep->eid;
	पूर्णांक credits;

	अगर (!ep->tx_credit_flow_enabled)
		वापस;

	credits = DIV_ROUND_UP(len, ep->tx_credit_size);
	spin_lock_bh(&htc->tx_lock);
	ep->tx_credits += credits;
	ath10k_dbg(ar, ATH10K_DBG_HTC,
		   "htc ep %d reverted %d credits back total %d\n",
		   eid, credits, ep->tx_credits);
	spin_unlock_bh(&htc->tx_lock);

	अगर (ep->ep_ops.ep_tx_credits)
		ep->ep_ops.ep_tx_credits(htc->ar);
पूर्ण

पूर्णांक ath10k_htc_send(काष्ठा ath10k_htc *htc,
		    क्रमागत ath10k_htc_ep_id eid,
		    काष्ठा sk_buff *skb)
अणु
	काष्ठा ath10k *ar = htc->ar;
	काष्ठा ath10k_htc_ep *ep = &htc->endpoपूर्णांक[eid];
	काष्ठा ath10k_skb_cb *skb_cb = ATH10K_SKB_CB(skb);
	काष्ठा ath10k_hअगर_sg_item sg_item;
	काष्ठा device *dev = htc->ar->dev;
	पूर्णांक ret;
	अचिन्हित पूर्णांक skb_len;

	अगर (htc->ar->state == ATH10K_STATE_WEDGED)
		वापस -ECOMM;

	अगर (eid >= ATH10K_HTC_EP_COUNT) अणु
		ath10k_warn(ar, "Invalid endpoint id: %d\n", eid);
		वापस -ENOENT;
	पूर्ण

	skb_push(skb, माप(काष्ठा ath10k_htc_hdr));

	skb_len = skb->len;
	ret = ath10k_htc_consume_credit(ep, skb_len, true);
	अगर (ret)
		जाओ err_pull;

	ath10k_htc_prepare_tx_skb(ep, skb);

	skb_cb->eid = eid;
	अगर (ar->bus_param.dev_type != ATH10K_DEV_TYPE_HL) अणु
		skb_cb->paddr = dma_map_single(dev, skb->data, skb->len,
					       DMA_TO_DEVICE);
		ret = dma_mapping_error(dev, skb_cb->paddr);
		अगर (ret) अणु
			ret = -EIO;
			जाओ err_credits;
		पूर्ण
	पूर्ण

	sg_item.transfer_id = ep->eid;
	sg_item.transfer_context = skb;
	sg_item.vaddr = skb->data;
	sg_item.paddr = skb_cb->paddr;
	sg_item.len = skb->len;

	ret = ath10k_hअगर_tx_sg(htc->ar, ep->ul_pipe_id, &sg_item, 1);
	अगर (ret)
		जाओ err_unmap;

	वापस 0;

err_unmap:
	अगर (ar->bus_param.dev_type != ATH10K_DEV_TYPE_HL)
		dma_unmap_single(dev, skb_cb->paddr, skb->len, DMA_TO_DEVICE);
err_credits:
	ath10k_htc_release_credit(ep, skb_len);
err_pull:
	skb_pull(skb, माप(काष्ठा ath10k_htc_hdr));
	वापस ret;
पूर्ण

व्योम ath10k_htc_tx_completion_handler(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा ath10k_htc *htc = &ar->htc;
	काष्ठा ath10k_skb_cb *skb_cb;
	काष्ठा ath10k_htc_ep *ep;

	अगर (WARN_ON_ONCE(!skb))
		वापस;

	skb_cb = ATH10K_SKB_CB(skb);
	ep = &htc->endpoपूर्णांक[skb_cb->eid];

	ath10k_htc_notअगरy_tx_completion(ep, skb);
	/* the skb now beदीर्घs to the completion handler */
पूर्ण
EXPORT_SYMBOL(ath10k_htc_tx_completion_handler);

/***********/
/* Receive */
/***********/

अटल व्योम
ath10k_htc_process_credit_report(काष्ठा ath10k_htc *htc,
				 स्थिर काष्ठा ath10k_htc_credit_report *report,
				 पूर्णांक len,
				 क्रमागत ath10k_htc_ep_id eid)
अणु
	काष्ठा ath10k *ar = htc->ar;
	काष्ठा ath10k_htc_ep *ep;
	पूर्णांक i, n_reports;

	अगर (len % माप(*report))
		ath10k_warn(ar, "Uneven credit report len %d", len);

	n_reports = len / माप(*report);

	spin_lock_bh(&htc->tx_lock);
	क्रम (i = 0; i < n_reports; i++, report++) अणु
		अगर (report->eid >= ATH10K_HTC_EP_COUNT)
			अवरोध;

		ep = &htc->endpoपूर्णांक[report->eid];
		ep->tx_credits += report->credits;

		ath10k_dbg(ar, ATH10K_DBG_HTC, "htc ep %d got %d credits (total %d)\n",
			   report->eid, report->credits, ep->tx_credits);

		अगर (ep->ep_ops.ep_tx_credits) अणु
			spin_unlock_bh(&htc->tx_lock);
			ep->ep_ops.ep_tx_credits(htc->ar);
			spin_lock_bh(&htc->tx_lock);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&htc->tx_lock);
पूर्ण

अटल पूर्णांक
ath10k_htc_process_lookahead(काष्ठा ath10k_htc *htc,
			     स्थिर काष्ठा ath10k_htc_lookahead_report *report,
			     पूर्णांक len,
			     क्रमागत ath10k_htc_ep_id eid,
			     व्योम *next_lookaheads,
			     पूर्णांक *next_lookaheads_len)
अणु
	काष्ठा ath10k *ar = htc->ar;

	/* Invalid lookahead flags are actually transmitted by
	 * the target in the HTC control message.
	 * Since this will happen at every boot we silently ignore
	 * the lookahead in this हाल
	 */
	अगर (report->pre_valid != ((~report->post_valid) & 0xFF))
		वापस 0;

	अगर (next_lookaheads && next_lookaheads_len) अणु
		ath10k_dbg(ar, ATH10K_DBG_HTC,
			   "htc rx lookahead found pre_valid 0x%x post_valid 0x%x\n",
			   report->pre_valid, report->post_valid);

		/* look ahead bytes are valid, copy them over */
		स_नकल((u8 *)next_lookaheads, report->lookahead, 4);

		*next_lookaheads_len = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
ath10k_htc_process_lookahead_bundle(काष्ठा ath10k_htc *htc,
				    स्थिर काष्ठा ath10k_htc_lookahead_bundle *report,
				    पूर्णांक len,
				    क्रमागत ath10k_htc_ep_id eid,
				    व्योम *next_lookaheads,
				    पूर्णांक *next_lookaheads_len)
अणु
	काष्ठा ath10k *ar = htc->ar;
	पूर्णांक bundle_cnt = len / माप(*report);

	अगर (!bundle_cnt || (bundle_cnt > htc->max_msgs_per_htc_bundle)) अणु
		ath10k_warn(ar, "Invalid lookahead bundle count: %d\n",
			    bundle_cnt);
		वापस -EINVAL;
	पूर्ण

	अगर (next_lookaheads && next_lookaheads_len) अणु
		पूर्णांक i;

		क्रम (i = 0; i < bundle_cnt; i++) अणु
			स_नकल(((u8 *)next_lookaheads) + 4 * i,
			       report->lookahead, 4);
			report++;
		पूर्ण

		*next_lookaheads_len = bundle_cnt;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath10k_htc_process_trailer(काष्ठा ath10k_htc *htc,
			       u8 *buffer,
			       पूर्णांक length,
			       क्रमागत ath10k_htc_ep_id src_eid,
			       व्योम *next_lookaheads,
			       पूर्णांक *next_lookaheads_len)
अणु
	काष्ठा ath10k_htc_lookahead_bundle *bundle;
	काष्ठा ath10k *ar = htc->ar;
	पूर्णांक status = 0;
	काष्ठा ath10k_htc_record *record;
	u8 *orig_buffer;
	पूर्णांक orig_length;
	माप_प्रकार len;

	orig_buffer = buffer;
	orig_length = length;

	जबतक (length > 0) अणु
		record = (काष्ठा ath10k_htc_record *)buffer;

		अगर (length < माप(record->hdr)) अणु
			status = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (record->hdr.len > length) अणु
			/* no room left in buffer क्रम record */
			ath10k_warn(ar, "Invalid record length: %d\n",
				    record->hdr.len);
			status = -EINVAL;
			अवरोध;
		पूर्ण

		चयन (record->hdr.id) अणु
		हाल ATH10K_HTC_RECORD_CREDITS:
			len = माप(काष्ठा ath10k_htc_credit_report);
			अगर (record->hdr.len < len) अणु
				ath10k_warn(ar, "Credit report too long\n");
				status = -EINVAL;
				अवरोध;
			पूर्ण
			ath10k_htc_process_credit_report(htc,
							 record->credit_report,
							 record->hdr.len,
							 src_eid);
			अवरोध;
		हाल ATH10K_HTC_RECORD_LOOKAHEAD:
			len = माप(काष्ठा ath10k_htc_lookahead_report);
			अगर (record->hdr.len < len) अणु
				ath10k_warn(ar, "Lookahead report too long\n");
				status = -EINVAL;
				अवरोध;
			पूर्ण
			status = ath10k_htc_process_lookahead(htc,
							      record->lookahead_report,
							      record->hdr.len,
							      src_eid,
							      next_lookaheads,
							      next_lookaheads_len);
			अवरोध;
		हाल ATH10K_HTC_RECORD_LOOKAHEAD_BUNDLE:
			bundle = record->lookahead_bundle;
			status = ath10k_htc_process_lookahead_bundle(htc,
								     bundle,
								     record->hdr.len,
								     src_eid,
								     next_lookaheads,
								     next_lookaheads_len);
			अवरोध;
		शेष:
			ath10k_warn(ar, "Unhandled record: id:%d length:%d\n",
				    record->hdr.id, record->hdr.len);
			अवरोध;
		पूर्ण

		अगर (status)
			अवरोध;

		/* multiple records may be present in a trailer */
		buffer += माप(record->hdr) + record->hdr.len;
		length -= माप(record->hdr) + record->hdr.len;
	पूर्ण

	अगर (status)
		ath10k_dbg_dump(ar, ATH10K_DBG_HTC, "htc rx bad trailer", "",
				orig_buffer, orig_length);

	वापस status;
पूर्ण
EXPORT_SYMBOL(ath10k_htc_process_trailer);

व्योम ath10k_htc_rx_completion_handler(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	पूर्णांक status = 0;
	काष्ठा ath10k_htc *htc = &ar->htc;
	काष्ठा ath10k_htc_hdr *hdr;
	काष्ठा ath10k_htc_ep *ep;
	u16 payload_len;
	u32 trailer_len = 0;
	माप_प्रकार min_len;
	u8 eid;
	bool trailer_present;

	hdr = (काष्ठा ath10k_htc_hdr *)skb->data;
	skb_pull(skb, माप(*hdr));

	eid = hdr->eid;

	अगर (eid >= ATH10K_HTC_EP_COUNT) अणु
		ath10k_warn(ar, "HTC Rx: invalid eid %d\n", eid);
		ath10k_dbg_dump(ar, ATH10K_DBG_HTC, "htc bad header", "",
				hdr, माप(*hdr));
		जाओ out;
	पूर्ण

	ep = &htc->endpoपूर्णांक[eid];
	अगर (ep->service_id == ATH10K_HTC_SVC_ID_UNUSED) अणु
		ath10k_warn(ar, "htc rx endpoint %d is not connected\n", eid);
		जाओ out;
	पूर्ण

	payload_len = __le16_to_cpu(hdr->len);

	अगर (payload_len + माप(*hdr) > ATH10K_HTC_MAX_LEN) अणु
		ath10k_warn(ar, "HTC rx frame too long, len: %zu\n",
			    payload_len + माप(*hdr));
		ath10k_dbg_dump(ar, ATH10K_DBG_HTC, "htc bad rx pkt len", "",
				hdr, माप(*hdr));
		जाओ out;
	पूर्ण

	अगर (skb->len < payload_len) अणु
		ath10k_dbg(ar, ATH10K_DBG_HTC,
			   "HTC Rx: insufficient length, got %d, expected %d\n",
			   skb->len, payload_len);
		ath10k_dbg_dump(ar, ATH10K_DBG_HTC, "htc bad rx pkt len",
				"", hdr, माप(*hdr));
		जाओ out;
	पूर्ण

	/* get flags to check क्रम trailer */
	trailer_present = hdr->flags & ATH10K_HTC_FLAG_TRAILER_PRESENT;
	अगर (trailer_present) अणु
		u8 *trailer;

		trailer_len = hdr->trailer_len;
		min_len = माप(काष्ठा ath10k_ath10k_htc_record_hdr);

		अगर ((trailer_len < min_len) ||
		    (trailer_len > payload_len)) अणु
			ath10k_warn(ar, "Invalid trailer length: %d\n",
				    trailer_len);
			जाओ out;
		पूर्ण

		trailer = (u8 *)hdr;
		trailer += माप(*hdr);
		trailer += payload_len;
		trailer -= trailer_len;
		status = ath10k_htc_process_trailer(htc, trailer,
						    trailer_len, hdr->eid,
						    शून्य, शून्य);
		अगर (status)
			जाओ out;

		skb_trim(skb, skb->len - trailer_len);
	पूर्ण

	अगर (((पूर्णांक)payload_len - (पूर्णांक)trailer_len) <= 0)
		/* zero length packet with trailer data, just drop these */
		जाओ out;

	ath10k_dbg(ar, ATH10K_DBG_HTC, "htc rx completion ep %d skb %pK\n",
		   eid, skb);
	ep->ep_ops.ep_rx_complete(ar, skb);

	/* skb is now owned by the rx completion handler */
	skb = शून्य;
out:
	kमुक्त_skb(skb);
पूर्ण
EXPORT_SYMBOL(ath10k_htc_rx_completion_handler);

अटल व्योम ath10k_htc_control_rx_complete(काष्ठा ath10k *ar,
					   काष्ठा sk_buff *skb)
अणु
	काष्ठा ath10k_htc *htc = &ar->htc;
	काष्ठा ath10k_htc_msg *msg = (काष्ठा ath10k_htc_msg *)skb->data;

	चयन (__le16_to_cpu(msg->hdr.message_id)) अणु
	हाल ATH10K_HTC_MSG_READY_ID:
	हाल ATH10K_HTC_MSG_CONNECT_SERVICE_RESP_ID:
		/* handle HTC control message */
		अगर (completion_करोne(&htc->ctl_resp)) अणु
			/* this is a fatal error, target should not be
			 * sending unsolicited messages on the ep 0
			 */
			ath10k_warn(ar, "HTC rx ctrl still processing\n");
			complete(&htc->ctl_resp);
			जाओ out;
		पूर्ण

		htc->control_resp_len =
			min_t(पूर्णांक, skb->len,
			      ATH10K_HTC_MAX_CTRL_MSG_LEN);

		स_नकल(htc->control_resp_buffer, skb->data,
		       htc->control_resp_len);

		complete(&htc->ctl_resp);
		अवरोध;
	हाल ATH10K_HTC_MSG_SEND_SUSPEND_COMPLETE:
		htc->htc_ops.target_send_suspend_complete(ar);
		अवरोध;
	शेष:
		ath10k_warn(ar, "ignoring unsolicited htc ep0 event\n");
		अवरोध;
	पूर्ण

out:
	kमुक्त_skb(skb);
पूर्ण

/***************/
/* Init/Deinit */
/***************/

अटल स्थिर अक्षर *htc_service_name(क्रमागत ath10k_htc_svc_id id)
अणु
	चयन (id) अणु
	हाल ATH10K_HTC_SVC_ID_RESERVED:
		वापस "Reserved";
	हाल ATH10K_HTC_SVC_ID_RSVD_CTRL:
		वापस "Control";
	हाल ATH10K_HTC_SVC_ID_WMI_CONTROL:
		वापस "WMI";
	हाल ATH10K_HTC_SVC_ID_WMI_DATA_BE:
		वापस "DATA BE";
	हाल ATH10K_HTC_SVC_ID_WMI_DATA_BK:
		वापस "DATA BK";
	हाल ATH10K_HTC_SVC_ID_WMI_DATA_VI:
		वापस "DATA VI";
	हाल ATH10K_HTC_SVC_ID_WMI_DATA_VO:
		वापस "DATA VO";
	हाल ATH10K_HTC_SVC_ID_NMI_CONTROL:
		वापस "NMI Control";
	हाल ATH10K_HTC_SVC_ID_NMI_DATA:
		वापस "NMI Data";
	हाल ATH10K_HTC_SVC_ID_HTT_DATA_MSG:
		वापस "HTT Data";
	हाल ATH10K_HTC_SVC_ID_HTT_DATA2_MSG:
		वापस "HTT Data";
	हाल ATH10K_HTC_SVC_ID_HTT_DATA3_MSG:
		वापस "HTT Data";
	हाल ATH10K_HTC_SVC_ID_TEST_RAW_STREAMS:
		वापस "RAW";
	हाल ATH10K_HTC_SVC_ID_HTT_LOG_MSG:
		वापस "PKTLOG";
	पूर्ण

	वापस "Unknown";
पूर्ण

अटल व्योम ath10k_htc_reset_endpoपूर्णांक_states(काष्ठा ath10k_htc *htc)
अणु
	काष्ठा ath10k_htc_ep *ep;
	पूर्णांक i;

	क्रम (i = ATH10K_HTC_EP_0; i < ATH10K_HTC_EP_COUNT; i++) अणु
		ep = &htc->endpoपूर्णांक[i];
		ep->service_id = ATH10K_HTC_SVC_ID_UNUSED;
		ep->max_ep_message_len = 0;
		ep->max_tx_queue_depth = 0;
		ep->eid = i;
		ep->htc = htc;
		ep->tx_credit_flow_enabled = true;
	पूर्ण
पूर्ण

अटल u8 ath10k_htc_get_credit_allocation(काष्ठा ath10k_htc *htc,
					   u16 service_id)
अणु
	u8 allocation = 0;

	/* The WMI control service is the only service with flow control.
	 * Let it have all transmit credits.
	 */
	अगर (service_id == ATH10K_HTC_SVC_ID_WMI_CONTROL)
		allocation = htc->total_transmit_credits;

	वापस allocation;
पूर्ण

अटल पूर्णांक ath10k_htc_send_bundle(काष्ठा ath10k_htc_ep *ep,
				  काष्ठा sk_buff *bundle_skb,
				  काष्ठा sk_buff_head *tx_save_head)
अणु
	काष्ठा ath10k_hअगर_sg_item sg_item;
	काष्ठा ath10k_htc *htc = ep->htc;
	काष्ठा ath10k *ar = htc->ar;
	काष्ठा sk_buff *skb;
	पूर्णांक ret, cn = 0;
	अचिन्हित पूर्णांक skb_len;

	ath10k_dbg(ar, ATH10K_DBG_HTC, "bundle skb len %d\n", bundle_skb->len);
	skb_len = bundle_skb->len;
	ret = ath10k_htc_consume_credit(ep, skb_len, true);

	अगर (!ret) अणु
		sg_item.transfer_id = ep->eid;
		sg_item.transfer_context = bundle_skb;
		sg_item.vaddr = bundle_skb->data;
		sg_item.len = bundle_skb->len;

		ret = ath10k_hअगर_tx_sg(htc->ar, ep->ul_pipe_id, &sg_item, 1);
		अगर (ret)
			ath10k_htc_release_credit(ep, skb_len);
	पूर्ण

	अगर (ret)
		dev_kमुक्त_skb_any(bundle_skb);

	क्रम (cn = 0; (skb = skb_dequeue_tail(tx_save_head)); cn++) अणु
		अगर (ret) अणु
			skb_pull(skb, माप(काष्ठा ath10k_htc_hdr));
			skb_queue_head(&ep->tx_req_head, skb);
		पूर्ण अन्यथा अणु
			skb_queue_tail(&ep->tx_complete_head, skb);
		पूर्ण
	पूर्ण

	अगर (!ret)
		queue_work(ar->workqueue_tx_complete, &ar->tx_complete_work);

	ath10k_dbg(ar, ATH10K_DBG_HTC,
		   "bundle tx status %d eid %d req count %d count %d len %d\n",
		   ret, ep->eid, skb_queue_len(&ep->tx_req_head), cn, skb_len);
	वापस ret;
पूर्ण

अटल व्योम ath10k_htc_send_one_skb(काष्ठा ath10k_htc_ep *ep, काष्ठा sk_buff *skb)
अणु
	काष्ठा ath10k_htc *htc = ep->htc;
	काष्ठा ath10k *ar = htc->ar;
	पूर्णांक ret;

	ret = ath10k_htc_send(htc, ep->eid, skb);

	अगर (ret)
		skb_queue_head(&ep->tx_req_head, skb);

	ath10k_dbg(ar, ATH10K_DBG_HTC, "tx one status %d eid %d len %d pending count %d\n",
		   ret, ep->eid, skb->len, skb_queue_len(&ep->tx_req_head));
पूर्ण

अटल पूर्णांक ath10k_htc_send_bundle_skbs(काष्ठा ath10k_htc_ep *ep)
अणु
	काष्ठा ath10k_htc *htc = ep->htc;
	काष्ठा sk_buff *bundle_skb, *skb;
	काष्ठा sk_buff_head tx_save_head;
	काष्ठा ath10k_htc_hdr *hdr;
	u8 *bundle_buf;
	पूर्णांक ret = 0, credit_pad, credit_reमुख्यder, trans_len, bundles_left = 0;

	अगर (htc->ar->state == ATH10K_STATE_WEDGED)
		वापस -ECOMM;

	अगर (ep->tx_credit_flow_enabled &&
	    ep->tx_credits < ATH10K_MIN_CREDIT_PER_HTC_TX_BUNDLE)
		वापस 0;

	bundles_left = ATH10K_MAX_MSG_PER_HTC_TX_BUNDLE * ep->tx_credit_size;
	bundle_skb = dev_alloc_skb(bundles_left);

	अगर (!bundle_skb)
		वापस -ENOMEM;

	bundle_buf = bundle_skb->data;
	skb_queue_head_init(&tx_save_head);

	जबतक (true) अणु
		skb = skb_dequeue(&ep->tx_req_head);
		अगर (!skb)
			अवरोध;

		credit_pad = 0;
		trans_len = skb->len + माप(*hdr);
		credit_reमुख्यder = trans_len % ep->tx_credit_size;

		अगर (credit_reमुख्यder != 0) अणु
			credit_pad = ep->tx_credit_size - credit_reमुख्यder;
			trans_len += credit_pad;
		पूर्ण

		ret = ath10k_htc_consume_credit(ep,
						bundle_buf + trans_len - bundle_skb->data,
						false);
		अगर (ret) अणु
			skb_queue_head(&ep->tx_req_head, skb);
			अवरोध;
		पूर्ण

		अगर (bundles_left < trans_len) अणु
			bundle_skb->len = bundle_buf - bundle_skb->data;
			ret = ath10k_htc_send_bundle(ep, bundle_skb, &tx_save_head);

			अगर (ret) अणु
				skb_queue_head(&ep->tx_req_head, skb);
				वापस ret;
			पूर्ण

			अगर (skb_queue_len(&ep->tx_req_head) == 0) अणु
				ath10k_htc_send_one_skb(ep, skb);
				वापस ret;
			पूर्ण

			अगर (ep->tx_credit_flow_enabled &&
			    ep->tx_credits < ATH10K_MIN_CREDIT_PER_HTC_TX_BUNDLE) अणु
				skb_queue_head(&ep->tx_req_head, skb);
				वापस 0;
			पूर्ण

			bundles_left =
				ATH10K_MAX_MSG_PER_HTC_TX_BUNDLE * ep->tx_credit_size;
			bundle_skb = dev_alloc_skb(bundles_left);

			अगर (!bundle_skb) अणु
				skb_queue_head(&ep->tx_req_head, skb);
				वापस -ENOMEM;
			पूर्ण
			bundle_buf = bundle_skb->data;
			skb_queue_head_init(&tx_save_head);
		पूर्ण

		skb_push(skb, माप(काष्ठा ath10k_htc_hdr));
		ath10k_htc_prepare_tx_skb(ep, skb);

		स_नकल(bundle_buf, skb->data, skb->len);
		hdr = (काष्ठा ath10k_htc_hdr *)bundle_buf;
		hdr->flags |= ATH10K_HTC_FLAG_SEND_BUNDLE;
		hdr->pad_len = __cpu_to_le16(credit_pad);
		bundle_buf += trans_len;
		bundles_left -= trans_len;
		skb_queue_tail(&tx_save_head, skb);
	पूर्ण

	अगर (bundle_buf != bundle_skb->data) अणु
		bundle_skb->len = bundle_buf - bundle_skb->data;
		ret = ath10k_htc_send_bundle(ep, bundle_skb, &tx_save_head);
	पूर्ण अन्यथा अणु
		dev_kमुक्त_skb_any(bundle_skb);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ath10k_htc_bundle_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath10k *ar = container_of(work, काष्ठा ath10k, bundle_tx_work);
	काष्ठा ath10k_htc_ep *ep;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ar->htc.endpoपूर्णांक); i++) अणु
		ep = &ar->htc.endpoपूर्णांक[i];

		अगर (!ep->bundle_tx)
			जारी;

		ath10k_dbg(ar, ATH10K_DBG_HTC, "bundle tx work eid %d count %d\n",
			   ep->eid, skb_queue_len(&ep->tx_req_head));

		अगर (skb_queue_len(&ep->tx_req_head) >=
		    ATH10K_MIN_MSG_PER_HTC_TX_BUNDLE) अणु
			ath10k_htc_send_bundle_skbs(ep);
		पूर्ण अन्यथा अणु
			skb = skb_dequeue(&ep->tx_req_head);

			अगर (!skb)
				जारी;
			ath10k_htc_send_one_skb(ep, skb);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ath10k_htc_tx_complete_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath10k *ar = container_of(work, काष्ठा ath10k, tx_complete_work);
	काष्ठा ath10k_htc_ep *ep;
	क्रमागत ath10k_htc_ep_id eid;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ar->htc.endpoपूर्णांक); i++) अणु
		ep = &ar->htc.endpoपूर्णांक[i];
		eid = ep->eid;
		अगर (ep->bundle_tx && eid == ar->htt.eid) अणु
			ath10k_dbg(ar, ATH10K_DBG_HTC, "bundle tx complete eid %d pending complete count%d\n",
				   ep->eid, skb_queue_len(&ep->tx_complete_head));

			जबतक (true) अणु
				skb = skb_dequeue(&ep->tx_complete_head);
				अगर (!skb)
					अवरोध;
				ath10k_htc_notअगरy_tx_completion(ep, skb);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक ath10k_htc_send_hl(काष्ठा ath10k_htc *htc,
		       क्रमागत ath10k_htc_ep_id eid,
		       काष्ठा sk_buff *skb)
अणु
	काष्ठा ath10k_htc_ep *ep = &htc->endpoपूर्णांक[eid];
	काष्ठा ath10k *ar = htc->ar;

	अगर (माप(काष्ठा ath10k_htc_hdr) + skb->len > ep->tx_credit_size) अणु
		ath10k_dbg(ar, ATH10K_DBG_HTC, "tx exceed max len %d\n", skb->len);
		वापस -ENOMEM;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_HTC, "htc send hl eid %d bundle %d tx count %d len %d\n",
		   eid, ep->bundle_tx, skb_queue_len(&ep->tx_req_head), skb->len);

	अगर (ep->bundle_tx) अणु
		skb_queue_tail(&ep->tx_req_head, skb);
		queue_work(ar->workqueue, &ar->bundle_tx_work);
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस ath10k_htc_send(htc, eid, skb);
	पूर्ण
पूर्ण

व्योम ath10k_htc_setup_tx_req(काष्ठा ath10k_htc_ep *ep)
अणु
	अगर (ep->htc->max_msgs_per_htc_bundle >= ATH10K_MIN_MSG_PER_HTC_TX_BUNDLE &&
	    !ep->bundle_tx) अणु
		ep->bundle_tx = true;
		skb_queue_head_init(&ep->tx_req_head);
		skb_queue_head_init(&ep->tx_complete_head);
	पूर्ण
पूर्ण

व्योम ath10k_htc_stop_hl(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_htc_ep *ep;
	पूर्णांक i;

	cancel_work_sync(&ar->bundle_tx_work);
	cancel_work_sync(&ar->tx_complete_work);

	क्रम (i = 0; i < ARRAY_SIZE(ar->htc.endpoपूर्णांक); i++) अणु
		ep = &ar->htc.endpoपूर्णांक[i];

		अगर (!ep->bundle_tx)
			जारी;

		ath10k_dbg(ar, ATH10K_DBG_HTC, "stop tx work eid %d count %d\n",
			   ep->eid, skb_queue_len(&ep->tx_req_head));

		skb_queue_purge(&ep->tx_req_head);
	पूर्ण
पूर्ण

पूर्णांक ath10k_htc_रुको_target(काष्ठा ath10k_htc *htc)
अणु
	काष्ठा ath10k *ar = htc->ar;
	पूर्णांक i, status = 0;
	अचिन्हित दीर्घ समय_left;
	काष्ठा ath10k_htc_msg *msg;
	u16 message_id;

	समय_left = रुको_क्रम_completion_समयout(&htc->ctl_resp,
						ATH10K_HTC_WAIT_TIMEOUT_HZ);
	अगर (!समय_left) अणु
		/* Workaround: In some हालs the PCI HIF करोesn't
		 * receive पूर्णांकerrupt क्रम the control response message
		 * even अगर the buffer was completed. It is suspected
		 * iomap ग_लिखोs unmasking PCI CE irqs aren't propagated
		 * properly in KVM PCI-passthrough someबार.
		 */
		ath10k_warn(ar, "failed to receive control response completion, polling..\n");

		क्रम (i = 0; i < CE_COUNT; i++)
			ath10k_hअगर_send_complete_check(htc->ar, i, 1);

		समय_left =
		रुको_क्रम_completion_समयout(&htc->ctl_resp,
					    ATH10K_HTC_WAIT_TIMEOUT_HZ);

		अगर (!समय_left)
			status = -ETIMEDOUT;
	पूर्ण

	अगर (status < 0) अणु
		ath10k_err(ar, "ctl_resp never came in (%d)\n", status);
		वापस status;
	पूर्ण

	अगर (htc->control_resp_len < माप(msg->hdr) + माप(msg->पढ़ोy)) अणु
		ath10k_err(ar, "Invalid HTC ready msg len:%d\n",
			   htc->control_resp_len);
		वापस -ECOMM;
	पूर्ण

	msg = (काष्ठा ath10k_htc_msg *)htc->control_resp_buffer;
	message_id   = __le16_to_cpu(msg->hdr.message_id);

	अगर (message_id != ATH10K_HTC_MSG_READY_ID) अणु
		ath10k_err(ar, "Invalid HTC ready msg: 0x%x\n", message_id);
		वापस -ECOMM;
	पूर्ण

	htc->total_transmit_credits = __le16_to_cpu(msg->पढ़ोy.credit_count);
	htc->target_credit_size = __le16_to_cpu(msg->पढ़ोy.credit_size);

	ath10k_dbg(ar, ATH10K_DBG_HTC,
		   "Target ready! transmit resources: %d size:%d\n",
		   htc->total_transmit_credits,
		   htc->target_credit_size);

	अगर ((htc->total_transmit_credits == 0) ||
	    (htc->target_credit_size == 0)) अणु
		ath10k_err(ar, "Invalid credit size received\n");
		वापस -ECOMM;
	पूर्ण

	/* The only way to determine अगर the पढ़ोy message is an extended
	 * message is from the size.
	 */
	अगर (htc->control_resp_len >=
	    माप(msg->hdr) + माप(msg->पढ़ोy_ext)) अणु
		htc->alt_data_credit_size =
			__le16_to_cpu(msg->पढ़ोy_ext.reserved) &
			ATH10K_HTC_MSG_READY_EXT_ALT_DATA_MASK;
		htc->max_msgs_per_htc_bundle =
			min_t(u8, msg->पढ़ोy_ext.max_msgs_per_htc_bundle,
			      HTC_HOST_MAX_MSG_PER_RX_BUNDLE);
		ath10k_dbg(ar, ATH10K_DBG_HTC,
			   "Extended ready message RX bundle size %d alt size %d\n",
			   htc->max_msgs_per_htc_bundle,
			   htc->alt_data_credit_size);
	पूर्ण

	INIT_WORK(&ar->bundle_tx_work, ath10k_htc_bundle_tx_work);
	INIT_WORK(&ar->tx_complete_work, ath10k_htc_tx_complete_work);

	वापस 0;
पूर्ण

व्योम ath10k_htc_change_tx_credit_flow(काष्ठा ath10k_htc *htc,
				      क्रमागत ath10k_htc_ep_id eid,
				      bool enable)
अणु
	काष्ठा ath10k *ar = htc->ar;
	काष्ठा ath10k_htc_ep *ep = &ar->htc.endpoपूर्णांक[eid];

	ep->tx_credit_flow_enabled = enable;
पूर्ण

पूर्णांक ath10k_htc_connect_service(काष्ठा ath10k_htc *htc,
			       काष्ठा ath10k_htc_svc_conn_req *conn_req,
			       काष्ठा ath10k_htc_svc_conn_resp *conn_resp)
अणु
	काष्ठा ath10k *ar = htc->ar;
	काष्ठा ath10k_htc_msg *msg;
	काष्ठा ath10k_htc_conn_svc *req_msg;
	काष्ठा ath10k_htc_conn_svc_response resp_msg_dummy;
	काष्ठा ath10k_htc_conn_svc_response *resp_msg = &resp_msg_dummy;
	क्रमागत ath10k_htc_ep_id asचिन्हित_eid = ATH10K_HTC_EP_COUNT;
	काष्ठा ath10k_htc_ep *ep;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक max_msg_size = 0;
	पूर्णांक length, status;
	अचिन्हित दीर्घ समय_left;
	bool disable_credit_flow_ctrl = false;
	u16 message_id, service_id, flags = 0;
	u8 tx_alloc = 0;

	/* special हाल क्रम HTC pseuकरो control service */
	अगर (conn_req->service_id == ATH10K_HTC_SVC_ID_RSVD_CTRL) अणु
		disable_credit_flow_ctrl = true;
		asचिन्हित_eid = ATH10K_HTC_EP_0;
		max_msg_size = ATH10K_HTC_MAX_CTRL_MSG_LEN;
		स_रखो(&resp_msg_dummy, 0, माप(resp_msg_dummy));
		जाओ setup;
	पूर्ण

	tx_alloc = ath10k_htc_get_credit_allocation(htc,
						    conn_req->service_id);
	अगर (!tx_alloc)
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "boot htc service %s does not allocate target credits\n",
			   htc_service_name(conn_req->service_id));

	skb = ath10k_htc_build_tx_ctrl_skb(htc->ar);
	अगर (!skb) अणु
		ath10k_err(ar, "Failed to allocate HTC packet\n");
		वापस -ENOMEM;
	पूर्ण

	length = माप(msg->hdr) + माप(msg->connect_service);
	skb_put(skb, length);
	स_रखो(skb->data, 0, length);

	msg = (काष्ठा ath10k_htc_msg *)skb->data;
	msg->hdr.message_id =
		__cpu_to_le16(ATH10K_HTC_MSG_CONNECT_SERVICE_ID);

	flags |= SM(tx_alloc, ATH10K_HTC_CONN_FLAGS_RECV_ALLOC);

	/* Only enable credit flow control क्रम WMI ctrl service */
	अगर (conn_req->service_id != ATH10K_HTC_SVC_ID_WMI_CONTROL) अणु
		flags |= ATH10K_HTC_CONN_FLAGS_DISABLE_CREDIT_FLOW_CTRL;
		disable_credit_flow_ctrl = true;
	पूर्ण

	req_msg = &msg->connect_service;
	req_msg->flags = __cpu_to_le16(flags);
	req_msg->service_id = __cpu_to_le16(conn_req->service_id);

	reinit_completion(&htc->ctl_resp);

	status = ath10k_htc_send(htc, ATH10K_HTC_EP_0, skb);
	अगर (status) अणु
		kमुक्त_skb(skb);
		वापस status;
	पूर्ण

	/* रुको क्रम response */
	समय_left = रुको_क्रम_completion_समयout(&htc->ctl_resp,
						ATH10K_HTC_CONN_SVC_TIMEOUT_HZ);
	अगर (!समय_left) अणु
		ath10k_err(ar, "Service connect timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	/* we controlled the buffer creation, it's aligned */
	msg = (काष्ठा ath10k_htc_msg *)htc->control_resp_buffer;
	resp_msg = &msg->connect_service_response;
	message_id = __le16_to_cpu(msg->hdr.message_id);
	service_id = __le16_to_cpu(resp_msg->service_id);

	अगर ((message_id != ATH10K_HTC_MSG_CONNECT_SERVICE_RESP_ID) ||
	    (htc->control_resp_len < माप(msg->hdr) +
	     माप(msg->connect_service_response))) अणु
		ath10k_err(ar, "Invalid resp message ID 0x%x", message_id);
		वापस -EPROTO;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_HTC,
		   "HTC Service %s connect response: status: 0x%x, assigned ep: 0x%x\n",
		   htc_service_name(service_id),
		   resp_msg->status, resp_msg->eid);

	conn_resp->connect_resp_code = resp_msg->status;

	/* check response status */
	अगर (resp_msg->status != ATH10K_HTC_CONN_SVC_STATUS_SUCCESS) अणु
		ath10k_err(ar, "HTC Service %s connect request failed: 0x%x)\n",
			   htc_service_name(service_id),
			   resp_msg->status);
		वापस -EPROTO;
	पूर्ण

	asचिन्हित_eid = (क्रमागत ath10k_htc_ep_id)resp_msg->eid;
	max_msg_size = __le16_to_cpu(resp_msg->max_msg_size);

setup:

	अगर (asचिन्हित_eid >= ATH10K_HTC_EP_COUNT)
		वापस -EPROTO;

	अगर (max_msg_size == 0)
		वापस -EPROTO;

	ep = &htc->endpoपूर्णांक[asचिन्हित_eid];
	ep->eid = asचिन्हित_eid;

	अगर (ep->service_id != ATH10K_HTC_SVC_ID_UNUSED)
		वापस -EPROTO;

	/* वापस asचिन्हित endpoपूर्णांक to caller */
	conn_resp->eid = asचिन्हित_eid;
	conn_resp->max_msg_len = __le16_to_cpu(resp_msg->max_msg_size);

	/* setup the endpoपूर्णांक */
	ep->service_id = conn_req->service_id;
	ep->max_tx_queue_depth = conn_req->max_send_queue_depth;
	ep->max_ep_message_len = __le16_to_cpu(resp_msg->max_msg_size);
	ep->tx_credits = tx_alloc;
	ep->tx_credit_size = htc->target_credit_size;

	अगर (conn_req->service_id == ATH10K_HTC_SVC_ID_HTT_DATA_MSG &&
	    htc->alt_data_credit_size != 0)
		ep->tx_credit_size = htc->alt_data_credit_size;

	/* copy all the callbacks */
	ep->ep_ops = conn_req->ep_ops;

	status = ath10k_hअगर_map_service_to_pipe(htc->ar,
						ep->service_id,
						&ep->ul_pipe_id,
						&ep->dl_pipe_id);
	अगर (status) अणु
		ath10k_dbg(ar, ATH10K_DBG_BOOT, "unsupported HTC service id: %d\n",
			   ep->service_id);
		वापस status;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "boot htc service '%s' ul pipe %d dl pipe %d eid %d ready\n",
		   htc_service_name(ep->service_id), ep->ul_pipe_id,
		   ep->dl_pipe_id, ep->eid);

	अगर (disable_credit_flow_ctrl && ep->tx_credit_flow_enabled) अणु
		ep->tx_credit_flow_enabled = false;
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "boot htc service '%s' eid %d TX flow control disabled\n",
			   htc_service_name(ep->service_id), asचिन्हित_eid);
	पूर्ण

	वापस status;
पूर्ण

काष्ठा sk_buff *ath10k_htc_alloc_skb(काष्ठा ath10k *ar, पूर्णांक size)
अणु
	काष्ठा sk_buff *skb;

	skb = dev_alloc_skb(size + माप(काष्ठा ath10k_htc_hdr));
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, माप(काष्ठा ath10k_htc_hdr));

	/* FW/HTC requires 4-byte aligned streams */
	अगर (!IS_ALIGNED((अचिन्हित दीर्घ)skb->data, 4))
		ath10k_warn(ar, "Unaligned HTC tx skb\n");

	वापस skb;
पूर्ण

अटल व्योम ath10k_htc_pktlog_process_rx(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	trace_ath10k_htt_pktlog(ar, skb->data, skb->len);
	dev_kमुक्त_skb_any(skb);
पूर्ण

अटल पूर्णांक ath10k_htc_pktlog_connect(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_htc_svc_conn_resp conn_resp;
	काष्ठा ath10k_htc_svc_conn_req conn_req;
	पूर्णांक status;

	स_रखो(&conn_req, 0, माप(conn_req));
	स_रखो(&conn_resp, 0, माप(conn_resp));

	conn_req.ep_ops.ep_tx_complete = शून्य;
	conn_req.ep_ops.ep_rx_complete = ath10k_htc_pktlog_process_rx;
	conn_req.ep_ops.ep_tx_credits = शून्य;

	/* connect to control service */
	conn_req.service_id = ATH10K_HTC_SVC_ID_HTT_LOG_MSG;
	status = ath10k_htc_connect_service(&ar->htc, &conn_req, &conn_resp);
	अगर (status) अणु
		ath10k_warn(ar, "failed to connect to PKTLOG service: %d\n",
			    status);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool ath10k_htc_pktlog_svc_supported(काष्ठा ath10k *ar)
अणु
	u8 ul_pipe_id;
	u8 dl_pipe_id;
	पूर्णांक status;

	status = ath10k_hअगर_map_service_to_pipe(ar, ATH10K_HTC_SVC_ID_HTT_LOG_MSG,
						&ul_pipe_id,
						&dl_pipe_id);
	अगर (status) अणु
		ath10k_dbg(ar, ATH10K_DBG_BOOT, "unsupported HTC pktlog service id: %d\n",
			   ATH10K_HTC_SVC_ID_HTT_LOG_MSG);

		वापस false;
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक ath10k_htc_start(काष्ठा ath10k_htc *htc)
अणु
	काष्ठा ath10k *ar = htc->ar;
	काष्ठा sk_buff *skb;
	पूर्णांक status = 0;
	काष्ठा ath10k_htc_msg *msg;

	skb = ath10k_htc_build_tx_ctrl_skb(htc->ar);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, माप(msg->hdr) + माप(msg->setup_complete_ext));
	स_रखो(skb->data, 0, skb->len);

	msg = (काष्ठा ath10k_htc_msg *)skb->data;
	msg->hdr.message_id =
		__cpu_to_le16(ATH10K_HTC_MSG_SETUP_COMPLETE_EX_ID);

	अगर (ar->hअगर.bus == ATH10K_BUS_SDIO) अणु
		/* Extra setup params used by SDIO */
		msg->setup_complete_ext.flags =
			__cpu_to_le32(ATH10K_HTC_SETUP_COMPLETE_FLAGS_RX_BNDL_EN);
		msg->setup_complete_ext.max_msgs_per_bundled_recv =
			htc->max_msgs_per_htc_bundle;
	पूर्ण
	ath10k_dbg(ar, ATH10K_DBG_HTC, "HTC is using TX credit flow control\n");

	status = ath10k_htc_send(htc, ATH10K_HTC_EP_0, skb);
	अगर (status) अणु
		kमुक्त_skb(skb);
		वापस status;
	पूर्ण

	अगर (ath10k_htc_pktlog_svc_supported(ar)) अणु
		status = ath10k_htc_pktlog_connect(ar);
		अगर (status) अणु
			ath10k_err(ar, "failed to connect to pktlog: %d\n", status);
			वापस status;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* रेजिस्टरed target arrival callback from the HIF layer */
पूर्णांक ath10k_htc_init(काष्ठा ath10k *ar)
अणु
	पूर्णांक status;
	काष्ठा ath10k_htc *htc = &ar->htc;
	काष्ठा ath10k_htc_svc_conn_req conn_req;
	काष्ठा ath10k_htc_svc_conn_resp conn_resp;

	spin_lock_init(&htc->tx_lock);

	ath10k_htc_reset_endpoपूर्णांक_states(htc);

	htc->ar = ar;

	/* setup our pseuकरो HTC control endpoपूर्णांक connection */
	स_रखो(&conn_req, 0, माप(conn_req));
	स_रखो(&conn_resp, 0, माप(conn_resp));
	conn_req.ep_ops.ep_tx_complete = ath10k_htc_control_tx_complete;
	conn_req.ep_ops.ep_rx_complete = ath10k_htc_control_rx_complete;
	conn_req.max_send_queue_depth = ATH10K_NUM_CONTROL_TX_BUFFERS;
	conn_req.service_id = ATH10K_HTC_SVC_ID_RSVD_CTRL;

	/* connect fake service */
	status = ath10k_htc_connect_service(htc, &conn_req, &conn_resp);
	अगर (status) अणु
		ath10k_err(ar, "could not connect to htc service (%d)\n",
			   status);
		वापस status;
	पूर्ण

	init_completion(&htc->ctl_resp);

	वापस 0;
पूर्ण
