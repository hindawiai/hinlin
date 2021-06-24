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

#समावेश "htc.h"

अटल स्थिर अक्षर *wmi_cmd_to_name(क्रमागत wmi_cmd_id wmi_cmd)
अणु
	चयन (wmi_cmd) अणु
	हाल WMI_ECHO_CMDID:
		वापस "WMI_ECHO_CMDID";
	हाल WMI_ACCESS_MEMORY_CMDID:
		वापस "WMI_ACCESS_MEMORY_CMDID";
	हाल WMI_GET_FW_VERSION:
		वापस "WMI_GET_FW_VERSION";
	हाल WMI_DISABLE_INTR_CMDID:
		वापस "WMI_DISABLE_INTR_CMDID";
	हाल WMI_ENABLE_INTR_CMDID:
		वापस "WMI_ENABLE_INTR_CMDID";
	हाल WMI_ATH_INIT_CMDID:
		वापस "WMI_ATH_INIT_CMDID";
	हाल WMI_ABORT_TXQ_CMDID:
		वापस "WMI_ABORT_TXQ_CMDID";
	हाल WMI_STOP_TX_DMA_CMDID:
		वापस "WMI_STOP_TX_DMA_CMDID";
	हाल WMI_ABORT_TX_DMA_CMDID:
		वापस "WMI_ABORT_TX_DMA_CMDID";
	हाल WMI_DRAIN_TXQ_CMDID:
		वापस "WMI_DRAIN_TXQ_CMDID";
	हाल WMI_DRAIN_TXQ_ALL_CMDID:
		वापस "WMI_DRAIN_TXQ_ALL_CMDID";
	हाल WMI_START_RECV_CMDID:
		वापस "WMI_START_RECV_CMDID";
	हाल WMI_STOP_RECV_CMDID:
		वापस "WMI_STOP_RECV_CMDID";
	हाल WMI_FLUSH_RECV_CMDID:
		वापस "WMI_FLUSH_RECV_CMDID";
	हाल WMI_SET_MODE_CMDID:
		वापस "WMI_SET_MODE_CMDID";
	हाल WMI_NODE_CREATE_CMDID:
		वापस "WMI_NODE_CREATE_CMDID";
	हाल WMI_NODE_REMOVE_CMDID:
		वापस "WMI_NODE_REMOVE_CMDID";
	हाल WMI_VAP_REMOVE_CMDID:
		वापस "WMI_VAP_REMOVE_CMDID";
	हाल WMI_VAP_CREATE_CMDID:
		वापस "WMI_VAP_CREATE_CMDID";
	हाल WMI_REG_READ_CMDID:
		वापस "WMI_REG_READ_CMDID";
	हाल WMI_REG_WRITE_CMDID:
		वापस "WMI_REG_WRITE_CMDID";
	हाल WMI_REG_RMW_CMDID:
		वापस "WMI_REG_RMW_CMDID";
	हाल WMI_RC_STATE_CHANGE_CMDID:
		वापस "WMI_RC_STATE_CHANGE_CMDID";
	हाल WMI_RC_RATE_UPDATE_CMDID:
		वापस "WMI_RC_RATE_UPDATE_CMDID";
	हाल WMI_TARGET_IC_UPDATE_CMDID:
		वापस "WMI_TARGET_IC_UPDATE_CMDID";
	हाल WMI_TX_AGGR_ENABLE_CMDID:
		वापस "WMI_TX_AGGR_ENABLE_CMDID";
	हाल WMI_TGT_DETACH_CMDID:
		वापस "WMI_TGT_DETACH_CMDID";
	हाल WMI_NODE_UPDATE_CMDID:
		वापस "WMI_NODE_UPDATE_CMDID";
	हाल WMI_INT_STATS_CMDID:
		वापस "WMI_INT_STATS_CMDID";
	हाल WMI_TX_STATS_CMDID:
		वापस "WMI_TX_STATS_CMDID";
	हाल WMI_RX_STATS_CMDID:
		वापस "WMI_RX_STATS_CMDID";
	हाल WMI_BITRATE_MASK_CMDID:
		वापस "WMI_BITRATE_MASK_CMDID";
	पूर्ण

	वापस "Bogus";
पूर्ण

काष्ठा wmi *ath9k_init_wmi(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा wmi *wmi;

	wmi = kzalloc(माप(काष्ठा wmi), GFP_KERNEL);
	अगर (!wmi)
		वापस शून्य;

	wmi->drv_priv = priv;
	wmi->stopped = false;
	skb_queue_head_init(&wmi->wmi_event_queue);
	spin_lock_init(&wmi->wmi_lock);
	spin_lock_init(&wmi->event_lock);
	mutex_init(&wmi->op_mutex);
	mutex_init(&wmi->multi_ग_लिखो_mutex);
	mutex_init(&wmi->multi_rmw_mutex);
	init_completion(&wmi->cmd_रुको);
	INIT_LIST_HEAD(&wmi->pending_tx_events);
	tasklet_setup(&wmi->wmi_event_tasklet, ath9k_wmi_event_tasklet);

	वापस wmi;
पूर्ण

व्योम ath9k_stop_wmi(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा wmi *wmi = priv->wmi;

	mutex_lock(&wmi->op_mutex);
	wmi->stopped = true;
	mutex_unlock(&wmi->op_mutex);
पूर्ण

व्योम ath9k_destroy_wmi(काष्ठा ath9k_htc_priv *priv)
अणु
	kमुक्त(priv->wmi);
पूर्ण

व्योम ath9k_wmi_event_drain(काष्ठा ath9k_htc_priv *priv)
अणु
	अचिन्हित दीर्घ flags;

	tasklet_समाप्त(&priv->wmi->wmi_event_tasklet);
	spin_lock_irqsave(&priv->wmi->wmi_lock, flags);
	__skb_queue_purge(&priv->wmi->wmi_event_queue);
	spin_unlock_irqrestore(&priv->wmi->wmi_lock, flags);
पूर्ण

व्योम ath9k_wmi_event_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा wmi *wmi = from_tasklet(wmi, t, wmi_event_tasklet);
	काष्ठा ath9k_htc_priv *priv = wmi->drv_priv;
	काष्ठा wmi_cmd_hdr *hdr;
	व्योम *wmi_event;
	काष्ठा wmi_event_swba *swba;
	काष्ठा sk_buff *skb = शून्य;
	अचिन्हित दीर्घ flags;
	u16 cmd_id;

	करो अणु
		spin_lock_irqsave(&wmi->wmi_lock, flags);
		skb = __skb_dequeue(&wmi->wmi_event_queue);
		अगर (!skb) अणु
			spin_unlock_irqrestore(&wmi->wmi_lock, flags);
			वापस;
		पूर्ण
		spin_unlock_irqrestore(&wmi->wmi_lock, flags);

		hdr = (काष्ठा wmi_cmd_hdr *) skb->data;
		cmd_id = be16_to_cpu(hdr->command_id);
		wmi_event = skb_pull(skb, माप(काष्ठा wmi_cmd_hdr));

		चयन (cmd_id) अणु
		हाल WMI_SWBA_EVENTID:
			swba = wmi_event;
			ath9k_htc_swba(priv, swba);
			अवरोध;
		हाल WMI_FATAL_EVENTID:
			ieee80211_queue_work(wmi->drv_priv->hw,
					     &wmi->drv_priv->fatal_work);
			अवरोध;
		हाल WMI_TXSTATUS_EVENTID:
			spin_lock_bh(&priv->tx.tx_lock);
			अगर (priv->tx.flags & ATH9K_HTC_OP_TX_DRAIN) अणु
				spin_unlock_bh(&priv->tx.tx_lock);
				अवरोध;
			पूर्ण
			spin_unlock_bh(&priv->tx.tx_lock);

			ath9k_htc_txstatus(priv, wmi_event);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		kमुक्त_skb(skb);
	पूर्ण जबतक (1);
पूर्ण

व्योम ath9k_fatal_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath9k_htc_priv *priv = container_of(work, काष्ठा ath9k_htc_priv,
						   fatal_work);
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);

	ath_dbg(common, FATAL, "FATAL Event received, resetting device\n");
	ath9k_htc_reset(priv);
पूर्ण

अटल व्योम ath9k_wmi_rsp_callback(काष्ठा wmi *wmi, काष्ठा sk_buff *skb)
अणु
	skb_pull(skb, माप(काष्ठा wmi_cmd_hdr));

	अगर (wmi->cmd_rsp_buf != शून्य && wmi->cmd_rsp_len != 0)
		स_नकल(wmi->cmd_rsp_buf, skb->data, wmi->cmd_rsp_len);

	complete(&wmi->cmd_रुको);
पूर्ण

अटल व्योम ath9k_wmi_ctrl_rx(व्योम *priv, काष्ठा sk_buff *skb,
			      क्रमागत htc_endpoपूर्णांक_id epid)
अणु
	काष्ठा wmi *wmi = priv;
	काष्ठा wmi_cmd_hdr *hdr;
	अचिन्हित दीर्घ flags;
	u16 cmd_id;

	अगर (unlikely(wmi->stopped))
		जाओ मुक्त_skb;

	hdr = (काष्ठा wmi_cmd_hdr *) skb->data;
	cmd_id = be16_to_cpu(hdr->command_id);

	अगर (cmd_id & 0x1000) अणु
		spin_lock_irqsave(&wmi->wmi_lock, flags);
		__skb_queue_tail(&wmi->wmi_event_queue, skb);
		spin_unlock_irqrestore(&wmi->wmi_lock, flags);
		tasklet_schedule(&wmi->wmi_event_tasklet);
		वापस;
	पूर्ण

	/* Check अगर there has been a समयout. */
	spin_lock_irqsave(&wmi->wmi_lock, flags);
	अगर (be16_to_cpu(hdr->seq_no) != wmi->last_seq_id) अणु
		spin_unlock_irqrestore(&wmi->wmi_lock, flags);
		जाओ मुक्त_skb;
	पूर्ण
	spin_unlock_irqrestore(&wmi->wmi_lock, flags);

	/* WMI command response */
	ath9k_wmi_rsp_callback(wmi, skb);

मुक्त_skb:
	kमुक्त_skb(skb);
पूर्ण

अटल व्योम ath9k_wmi_ctrl_tx(व्योम *priv, काष्ठा sk_buff *skb,
			      क्रमागत htc_endpoपूर्णांक_id epid, bool txok)
अणु
	kमुक्त_skb(skb);
पूर्ण

पूर्णांक ath9k_wmi_connect(काष्ठा htc_target *htc, काष्ठा wmi *wmi,
		      क्रमागत htc_endpoपूर्णांक_id *wmi_ctrl_epid)
अणु
	काष्ठा htc_service_connreq connect;
	पूर्णांक ret;

	wmi->htc = htc;

	स_रखो(&connect, 0, माप(connect));

	connect.ep_callbacks.priv = wmi;
	connect.ep_callbacks.tx = ath9k_wmi_ctrl_tx;
	connect.ep_callbacks.rx = ath9k_wmi_ctrl_rx;
	connect.service_id = WMI_CONTROL_SVC;

	ret = htc_connect_service(htc, &connect, &wmi->ctrl_epid);
	अगर (ret)
		वापस ret;

	*wmi_ctrl_epid = wmi->ctrl_epid;

	वापस 0;
पूर्ण

अटल पूर्णांक ath9k_wmi_cmd_issue(काष्ठा wmi *wmi,
			       काष्ठा sk_buff *skb,
			       क्रमागत wmi_cmd_id cmd, u16 len)
अणु
	काष्ठा wmi_cmd_hdr *hdr;
	अचिन्हित दीर्घ flags;

	hdr = skb_push(skb, माप(काष्ठा wmi_cmd_hdr));
	hdr->command_id = cpu_to_be16(cmd);
	hdr->seq_no = cpu_to_be16(++wmi->tx_seq_id);

	spin_lock_irqsave(&wmi->wmi_lock, flags);
	wmi->last_seq_id = wmi->tx_seq_id;
	spin_unlock_irqrestore(&wmi->wmi_lock, flags);

	वापस htc_send_epid(wmi->htc, skb, wmi->ctrl_epid);
पूर्ण

पूर्णांक ath9k_wmi_cmd(काष्ठा wmi *wmi, क्रमागत wmi_cmd_id cmd_id,
		  u8 *cmd_buf, u32 cmd_len,
		  u8 *rsp_buf, u32 rsp_len,
		  u32 समयout)
अणु
	काष्ठा ath_hw *ah = wmi->drv_priv->ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u16 headroom = माप(काष्ठा htc_frame_hdr) +
		       माप(काष्ठा wmi_cmd_hdr);
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ समय_left;
	पूर्णांक ret = 0;

	अगर (ah->ah_flags & AH_UNPLUGGED)
		वापस 0;

	skb = alloc_skb(headroom + cmd_len, GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;

	skb_reserve(skb, headroom);

	अगर (cmd_len != 0 && cmd_buf != शून्य) अणु
		skb_put_data(skb, cmd_buf, cmd_len);
	पूर्ण

	mutex_lock(&wmi->op_mutex);

	/* check अगर wmi stopped flag is set */
	अगर (unlikely(wmi->stopped)) अणु
		ret = -EPROTO;
		जाओ out;
	पूर्ण

	/* record the rsp buffer and length */
	wmi->cmd_rsp_buf = rsp_buf;
	wmi->cmd_rsp_len = rsp_len;

	ret = ath9k_wmi_cmd_issue(wmi, skb, cmd_id, cmd_len);
	अगर (ret)
		जाओ out;

	समय_left = रुको_क्रम_completion_समयout(&wmi->cmd_रुको, समयout);
	अगर (!समय_left) अणु
		ath_dbg(common, WMI, "Timeout waiting for WMI command: %s\n",
			wmi_cmd_to_name(cmd_id));
		mutex_unlock(&wmi->op_mutex);
		वापस -ETIMEDOUT;
	पूर्ण

	mutex_unlock(&wmi->op_mutex);

	वापस 0;

out:
	ath_dbg(common, WMI, "WMI failure for: %s\n", wmi_cmd_to_name(cmd_id));
	mutex_unlock(&wmi->op_mutex);
	kमुक्त_skb(skb);

	वापस ret;
पूर्ण
