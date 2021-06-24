<शैली गुरु>
/*
 * Copyright (c) 2010-2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "htc.h"

अटल पूर्णांक htc_issue_send(काष्ठा htc_target *target, काष्ठा sk_buff* skb,
			  u16 len, u8 flags, u8 epid)

अणु
	काष्ठा htc_frame_hdr *hdr;
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक = &target->endpoपूर्णांक[epid];
	पूर्णांक status;

	hdr = skb_push(skb, माप(काष्ठा htc_frame_hdr));
	hdr->endpoपूर्णांक_id = epid;
	hdr->flags = flags;
	hdr->payload_len = cpu_to_be16(len);

	status = target->hअगर->send(target->hअगर_dev, endpoपूर्णांक->ul_pipeid, skb);

	वापस status;
पूर्ण

अटल काष्ठा htc_endpoपूर्णांक *get_next_avail_ep(काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक)
अणु
	क्रमागत htc_endpoपूर्णांक_id avail_epid;

	क्रम (avail_epid = (ENDPOपूर्णांक_उच्च - 1); avail_epid > ENDPOINT0; avail_epid--)
		अगर (endpoपूर्णांक[avail_epid].service_id == 0)
			वापस &endpoपूर्णांक[avail_epid];
	वापस शून्य;
पूर्ण

अटल u8 service_to_ulpipe(u16 service_id)
अणु
	चयन (service_id) अणु
	हाल WMI_CONTROL_SVC:
		वापस 4;
	हाल WMI_BEACON_SVC:
	हाल WMI_CAB_SVC:
	हाल WMI_UAPSD_SVC:
	हाल WMI_MGMT_SVC:
	हाल WMI_DATA_VO_SVC:
	हाल WMI_DATA_VI_SVC:
	हाल WMI_DATA_BE_SVC:
	हाल WMI_DATA_BK_SVC:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल u8 service_to_dlpipe(u16 service_id)
अणु
	चयन (service_id) अणु
	हाल WMI_CONTROL_SVC:
		वापस 3;
	हाल WMI_BEACON_SVC:
	हाल WMI_CAB_SVC:
	हाल WMI_UAPSD_SVC:
	हाल WMI_MGMT_SVC:
	हाल WMI_DATA_VO_SVC:
	हाल WMI_DATA_VI_SVC:
	हाल WMI_DATA_BE_SVC:
	हाल WMI_DATA_BK_SVC:
		वापस 2;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम htc_process_target_rdy(काष्ठा htc_target *target,
				   व्योम *buf)
अणु
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक;
	काष्ठा htc_पढ़ोy_msg *htc_पढ़ोy_msg = (काष्ठा htc_पढ़ोy_msg *) buf;

	target->credit_size = be16_to_cpu(htc_पढ़ोy_msg->credit_size);

	endpoपूर्णांक = &target->endpoपूर्णांक[ENDPOINT0];
	endpoपूर्णांक->service_id = HTC_CTRL_RSVD_SVC;
	endpoपूर्णांक->max_msglen = HTC_MAX_CONTROL_MESSAGE_LENGTH;
	atomic_inc(&target->tgt_पढ़ोy);
	complete(&target->target_रुको);
पूर्ण

अटल व्योम htc_process_conn_rsp(काष्ठा htc_target *target,
				 काष्ठा htc_frame_hdr *htc_hdr)
अणु
	काष्ठा htc_conn_svc_rspmsg *svc_rspmsg;
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक, *पंचांगp_endpoपूर्णांक = शून्य;
	u16 service_id;
	u16 max_msglen;
	क्रमागत htc_endpoपूर्णांक_id epid, tepid;

	svc_rspmsg = (काष्ठा htc_conn_svc_rspmsg *)
		((व्योम *) htc_hdr + माप(काष्ठा htc_frame_hdr));

	अगर (svc_rspmsg->status == HTC_SERVICE_SUCCESS) अणु
		epid = svc_rspmsg->endpoपूर्णांक_id;
		अगर (epid < 0 || epid >= ENDPOपूर्णांक_उच्च)
			वापस;

		service_id = be16_to_cpu(svc_rspmsg->service_id);
		max_msglen = be16_to_cpu(svc_rspmsg->max_msg_len);
		endpoपूर्णांक = &target->endpoपूर्णांक[epid];

		क्रम (tepid = (ENDPOपूर्णांक_उच्च - 1); tepid > ENDPOINT0; tepid--) अणु
			पंचांगp_endpoपूर्णांक = &target->endpoपूर्णांक[tepid];
			अगर (पंचांगp_endpoपूर्णांक->service_id == service_id) अणु
				पंचांगp_endpoपूर्णांक->service_id = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (tepid == ENDPOINT0)
			वापस;

		endpoपूर्णांक->service_id = service_id;
		endpoपूर्णांक->max_txqdepth = पंचांगp_endpoपूर्णांक->max_txqdepth;
		endpoपूर्णांक->ep_callbacks = पंचांगp_endpoपूर्णांक->ep_callbacks;
		endpoपूर्णांक->ul_pipeid = पंचांगp_endpoपूर्णांक->ul_pipeid;
		endpoपूर्णांक->dl_pipeid = पंचांगp_endpoपूर्णांक->dl_pipeid;
		endpoपूर्णांक->max_msglen = max_msglen;
		target->conn_rsp_epid = epid;
		complete(&target->cmd_रुको);
	पूर्ण अन्यथा अणु
		target->conn_rsp_epid = ENDPOINT_UNUSED;
	पूर्ण
पूर्ण

अटल पूर्णांक htc_config_pipe_credits(काष्ठा htc_target *target)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा htc_config_pipe_msg *cp_msg;
	पूर्णांक ret;
	अचिन्हित दीर्घ समय_left;

	skb = alloc_skb(50 + माप(काष्ठा htc_frame_hdr), GFP_ATOMIC);
	अगर (!skb) अणु
		dev_err(target->dev, "failed to allocate send buffer\n");
		वापस -ENOMEM;
	पूर्ण
	skb_reserve(skb, माप(काष्ठा htc_frame_hdr));

	cp_msg = skb_put(skb, माप(काष्ठा htc_config_pipe_msg));

	cp_msg->message_id = cpu_to_be16(HTC_MSG_CONFIG_PIPE_ID);
	cp_msg->pipe_id = USB_WLAN_TX_PIPE;
	cp_msg->credits = target->credits;

	target->htc_flags |= HTC_OP_CONFIG_PIPE_CREDITS;

	ret = htc_issue_send(target, skb, skb->len, 0, ENDPOINT0);
	अगर (ret)
		जाओ err;

	समय_left = रुको_क्रम_completion_समयout(&target->cmd_रुको, HZ);
	अगर (!समय_left) अणु
		dev_err(target->dev, "HTC credit config timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
err:
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक htc_setup_complete(काष्ठा htc_target *target)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा htc_comp_msg *comp_msg;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ समय_left;

	skb = alloc_skb(50 + माप(काष्ठा htc_frame_hdr), GFP_ATOMIC);
	अगर (!skb) अणु
		dev_err(target->dev, "failed to allocate send buffer\n");
		वापस -ENOMEM;
	पूर्ण
	skb_reserve(skb, माप(काष्ठा htc_frame_hdr));

	comp_msg = skb_put(skb, माप(काष्ठा htc_comp_msg));
	comp_msg->msg_id = cpu_to_be16(HTC_MSG_SETUP_COMPLETE_ID);

	target->htc_flags |= HTC_OP_START_WAIT;

	ret = htc_issue_send(target, skb, skb->len, 0, ENDPOINT0);
	अगर (ret)
		जाओ err;

	समय_left = रुको_क्रम_completion_समयout(&target->cmd_रुको, HZ);
	अगर (!समय_left) अणु
		dev_err(target->dev, "HTC start timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;

err:
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

/* HTC APIs */

पूर्णांक htc_init(काष्ठा htc_target *target)
अणु
	पूर्णांक ret;

	ret = htc_config_pipe_credits(target);
	अगर (ret)
		वापस ret;

	वापस htc_setup_complete(target);
पूर्ण

पूर्णांक htc_connect_service(काष्ठा htc_target *target,
		     काष्ठा htc_service_connreq *service_connreq,
		     क्रमागत htc_endpoपूर्णांक_id *conn_rsp_epid)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक;
	काष्ठा htc_conn_svc_msg *conn_msg;
	पूर्णांक ret;
	अचिन्हित दीर्घ समय_left;

	/* Find an available endpoपूर्णांक */
	endpoपूर्णांक = get_next_avail_ep(target->endpoपूर्णांक);
	अगर (!endpoपूर्णांक) अणु
		dev_err(target->dev, "Endpoint is not available for service %d\n",
			service_connreq->service_id);
		वापस -EINVAL;
	पूर्ण

	endpoपूर्णांक->service_id = service_connreq->service_id;
	endpoपूर्णांक->max_txqdepth = service_connreq->max_send_qdepth;
	endpoपूर्णांक->ul_pipeid = service_to_ulpipe(service_connreq->service_id);
	endpoपूर्णांक->dl_pipeid = service_to_dlpipe(service_connreq->service_id);
	endpoपूर्णांक->ep_callbacks = service_connreq->ep_callbacks;

	skb = alloc_skb(माप(काष्ठा htc_conn_svc_msg) +
			    माप(काष्ठा htc_frame_hdr), GFP_ATOMIC);
	अगर (!skb) अणु
		dev_err(target->dev, "Failed to allocate buf to send"
			"service connect req\n");
		वापस -ENOMEM;
	पूर्ण

	skb_reserve(skb, माप(काष्ठा htc_frame_hdr));

	conn_msg = skb_put(skb, माप(काष्ठा htc_conn_svc_msg));
	conn_msg->service_id = cpu_to_be16(service_connreq->service_id);
	conn_msg->msg_id = cpu_to_be16(HTC_MSG_CONNECT_SERVICE_ID);
	conn_msg->con_flags = cpu_to_be16(service_connreq->con_flags);
	conn_msg->dl_pipeid = endpoपूर्णांक->dl_pipeid;
	conn_msg->ul_pipeid = endpoपूर्णांक->ul_pipeid;

	ret = htc_issue_send(target, skb, skb->len, 0, ENDPOINT0);
	अगर (ret)
		जाओ err;

	समय_left = रुको_क्रम_completion_समयout(&target->cmd_रुको, HZ);
	अगर (!समय_left) अणु
		dev_err(target->dev, "Service connection timeout for: %d\n",
			service_connreq->service_id);
		वापस -ETIMEDOUT;
	पूर्ण

	*conn_rsp_epid = target->conn_rsp_epid;
	वापस 0;
err:
	kमुक्त_skb(skb);
	वापस ret;
पूर्ण

पूर्णांक htc_send(काष्ठा htc_target *target, काष्ठा sk_buff *skb)
अणु
	काष्ठा ath9k_htc_tx_ctl *tx_ctl;

	tx_ctl = HTC_SKB_CB(skb);
	वापस htc_issue_send(target, skb, skb->len, 0, tx_ctl->epid);
पूर्ण

पूर्णांक htc_send_epid(काष्ठा htc_target *target, काष्ठा sk_buff *skb,
		  क्रमागत htc_endpoपूर्णांक_id epid)
अणु
	वापस htc_issue_send(target, skb, skb->len, 0, epid);
पूर्ण

व्योम htc_stop(काष्ठा htc_target *target)
अणु
	target->hअगर->stop(target->hअगर_dev);
पूर्ण

व्योम htc_start(काष्ठा htc_target *target)
अणु
	target->hअगर->start(target->hअगर_dev);
पूर्ण

व्योम htc_sta_drain(काष्ठा htc_target *target, u8 idx)
अणु
	target->hअगर->sta_drain(target->hअगर_dev, idx);
पूर्ण

व्योम ath9k_htc_txcompletion_cb(काष्ठा htc_target *htc_handle,
			       काष्ठा sk_buff *skb, bool txok)
अणु
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक;
	काष्ठा htc_frame_hdr *htc_hdr = शून्य;

	अगर (htc_handle->htc_flags & HTC_OP_CONFIG_PIPE_CREDITS) अणु
		complete(&htc_handle->cmd_रुको);
		htc_handle->htc_flags &= ~HTC_OP_CONFIG_PIPE_CREDITS;
		जाओ ret;
	पूर्ण

	अगर (htc_handle->htc_flags & HTC_OP_START_WAIT) अणु
		complete(&htc_handle->cmd_रुको);
		htc_handle->htc_flags &= ~HTC_OP_START_WAIT;
		जाओ ret;
	पूर्ण

	अगर (skb) अणु
		htc_hdr = (काष्ठा htc_frame_hdr *) skb->data;
		अगर (htc_hdr->endpoपूर्णांक_id >= ARRAY_SIZE(htc_handle->endpoपूर्णांक))
			जाओ ret;
		endpoपूर्णांक = &htc_handle->endpoपूर्णांक[htc_hdr->endpoपूर्णांक_id];
		skb_pull(skb, माप(काष्ठा htc_frame_hdr));

		अगर (endpoपूर्णांक->ep_callbacks.tx) अणु
			endpoपूर्णांक->ep_callbacks.tx(endpoपूर्णांक->ep_callbacks.priv,
						  skb, htc_hdr->endpoपूर्णांक_id,
						  txok);
		पूर्ण अन्यथा अणु
			kमुक्त_skb(skb);
		पूर्ण
	पूर्ण

	वापस;
ret:
	kमुक्त_skb(skb);
पूर्ण

अटल व्योम ath9k_htc_fw_panic_report(काष्ठा htc_target *htc_handle,
				      काष्ठा sk_buff *skb)
अणु
	uपूर्णांक32_t *pattern = (uपूर्णांक32_t *)skb->data;

	चयन (*pattern) अणु
	हाल 0x33221199:
		अणु
		काष्ठा htc_panic_bad_vaddr *htc_panic;
		htc_panic = (काष्ठा htc_panic_bad_vaddr *) skb->data;
		dev_err(htc_handle->dev, "ath: firmware panic! "
			"exccause: 0x%08x; pc: 0x%08x; badvaddr: 0x%08x.\n",
			htc_panic->exccause, htc_panic->pc,
			htc_panic->badvaddr);
		अवरोध;
		पूर्ण
	हाल 0x33221299:
		अणु
		काष्ठा htc_panic_bad_epid *htc_panic;
		htc_panic = (काष्ठा htc_panic_bad_epid *) skb->data;
		dev_err(htc_handle->dev, "ath: firmware panic! "
			"bad epid: 0x%08x\n", htc_panic->epid);
		अवरोध;
		पूर्ण
	शेष:
		dev_err(htc_handle->dev, "ath: unknown panic pattern!\n");
		अवरोध;
	पूर्ण
पूर्ण

/*
 * HTC Messages are handled directly here and the obtained SKB
 * is मुक्तd.
 *
 * Service messages (Data, WMI) passed to the corresponding
 * endpoपूर्णांक RX handlers, which have to मुक्त the SKB.
 */
व्योम ath9k_htc_rx_msg(काष्ठा htc_target *htc_handle,
		      काष्ठा sk_buff *skb, u32 len, u8 pipe_id)
अणु
	काष्ठा htc_frame_hdr *htc_hdr;
	क्रमागत htc_endpoपूर्णांक_id epid;
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक;
	__be16 *msg_id;

	अगर (!htc_handle || !skb)
		वापस;

	htc_hdr = (काष्ठा htc_frame_hdr *) skb->data;
	epid = htc_hdr->endpoपूर्णांक_id;

	अगर (epid == 0x99) अणु
		ath9k_htc_fw_panic_report(htc_handle, skb);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	अगर (epid < 0 || epid >= ENDPOपूर्णांक_उच्च) अणु
		अगर (pipe_id != USB_REG_IN_PIPE)
			dev_kमुक्त_skb_any(skb);
		अन्यथा
			kमुक्त_skb(skb);
		वापस;
	पूर्ण

	अगर (epid == ENDPOINT0) अणु

		/* Handle trailer */
		अगर (htc_hdr->flags & HTC_FLAGS_RECV_TRAILER) अणु
			अगर (be32_to_cpu(*(__be32 *) skb->data) == 0x00C60000)
				/* Move past the Watchकरोg pattern */
				htc_hdr = (काष्ठा htc_frame_hdr *)(skb->data + 4);
		पूर्ण

		/* Get the message ID */
		msg_id = (__be16 *) ((व्योम *) htc_hdr +
				     माप(काष्ठा htc_frame_hdr));

		/* Now process HTC messages */
		चयन (be16_to_cpu(*msg_id)) अणु
		हाल HTC_MSG_READY_ID:
			htc_process_target_rdy(htc_handle, htc_hdr);
			अवरोध;
		हाल HTC_MSG_CONNECT_SERVICE_RESPONSE_ID:
			htc_process_conn_rsp(htc_handle, htc_hdr);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		kमुक्त_skb(skb);

	पूर्ण अन्यथा अणु
		अगर (htc_hdr->flags & HTC_FLAGS_RECV_TRAILER)
			skb_trim(skb, len - htc_hdr->control[0]);

		skb_pull(skb, माप(काष्ठा htc_frame_hdr));

		endpoपूर्णांक = &htc_handle->endpoपूर्णांक[epid];
		अगर (endpoपूर्णांक->ep_callbacks.rx)
			endpoपूर्णांक->ep_callbacks.rx(endpoपूर्णांक->ep_callbacks.priv,
						  skb, epid);
	पूर्ण
पूर्ण

काष्ठा htc_target *ath9k_htc_hw_alloc(व्योम *hअगर_handle,
				      काष्ठा ath9k_htc_hअगर *hअगर,
				      काष्ठा device *dev)
अणु
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक;
	काष्ठा htc_target *target;

	target = kzalloc(माप(काष्ठा htc_target), GFP_KERNEL);
	अगर (!target)
		वापस शून्य;

	init_completion(&target->target_रुको);
	init_completion(&target->cmd_रुको);

	target->hअगर = hअगर;
	target->hअगर_dev = hअगर_handle;
	target->dev = dev;

	/* Assign control endpoपूर्णांक pipe IDs */
	endpoपूर्णांक = &target->endpoपूर्णांक[ENDPOINT0];
	endpoपूर्णांक->ul_pipeid = hअगर->control_ul_pipe;
	endpoपूर्णांक->dl_pipeid = hअगर->control_dl_pipe;

	atomic_set(&target->tgt_पढ़ोy, 0);

	वापस target;
पूर्ण

व्योम ath9k_htc_hw_मुक्त(काष्ठा htc_target *htc)
अणु
	kमुक्त(htc);
पूर्ण

पूर्णांक ath9k_htc_hw_init(काष्ठा htc_target *target,
		      काष्ठा device *dev, u16 devid,
		      अक्षर *product, u32 drv_info)
अणु
	अगर (ath9k_htc_probe_device(target, dev, devid, product, drv_info)) अणु
		pr_err("Failed to initialize the device\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ath9k_htc_hw_deinit(काष्ठा htc_target *target, bool hot_unplug)
अणु
	अगर (target)
		ath9k_htc_disconnect_device(target, hot_unplug);
पूर्ण
