<शैली गुरु>
/*
 * Copyright (c) 2018 Redpine Signals Inc.
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

#समावेश "rsi_main.h"
#समावेश "rsi_coex.h"
#समावेश "rsi_mgmt.h"
#समावेश "rsi_hal.h"

अटल क्रमागत rsi_coex_queues rsi_coex_determine_coex_q
			(काष्ठा rsi_coex_ctrl_block *coex_cb)
अणु
	क्रमागत rsi_coex_queues q_num = RSI_COEX_Q_INVALID;

	अगर (skb_queue_len(&coex_cb->coex_tx_qs[RSI_COEX_Q_COMMON]) > 0)
		q_num = RSI_COEX_Q_COMMON;
	अगर (skb_queue_len(&coex_cb->coex_tx_qs[RSI_COEX_Q_BT]) > 0)
		q_num = RSI_COEX_Q_BT;
	अगर (skb_queue_len(&coex_cb->coex_tx_qs[RSI_COEX_Q_WLAN]) > 0)
		q_num = RSI_COEX_Q_WLAN;

	वापस q_num;
पूर्ण

अटल व्योम rsi_coex_sched_tx_pkts(काष्ठा rsi_coex_ctrl_block *coex_cb)
अणु
	क्रमागत rsi_coex_queues coex_q = RSI_COEX_Q_INVALID;
	काष्ठा sk_buff *skb;

	करो अणु
		coex_q = rsi_coex_determine_coex_q(coex_cb);
		rsi_dbg(INFO_ZONE, "queue = %d\n", coex_q);

		अगर (coex_q == RSI_COEX_Q_BT) अणु
			skb = skb_dequeue(&coex_cb->coex_tx_qs[RSI_COEX_Q_BT]);
			rsi_send_bt_pkt(coex_cb->priv, skb);
		पूर्ण
	पूर्ण जबतक (coex_q != RSI_COEX_Q_INVALID);
पूर्ण

अटल व्योम rsi_coex_scheduler_thपढ़ो(काष्ठा rsi_common *common)
अणु
	काष्ठा rsi_coex_ctrl_block *coex_cb =
		(काष्ठा rsi_coex_ctrl_block *)common->coex_cb;
	u32 समयout = EVENT_WAIT_FOREVER;

	करो अणु
		rsi_रुको_event(&coex_cb->coex_tx_thपढ़ो.event, समयout);
		rsi_reset_event(&coex_cb->coex_tx_thपढ़ो.event);

		rsi_coex_sched_tx_pkts(coex_cb);
	पूर्ण जबतक (atomic_पढ़ो(&coex_cb->coex_tx_thपढ़ो.thपढ़ो_करोne) == 0);

	complete_and_निकास(&coex_cb->coex_tx_thपढ़ो.completion, 0);
पूर्ण

पूर्णांक rsi_coex_recv_pkt(काष्ठा rsi_common *common, u8 *msg)
अणु
	u8 msg_type = msg[RSI_RX_DESC_MSG_TYPE_OFFSET];

	चयन (msg_type) अणु
	हाल COMMON_CARD_READY_IND:
		rsi_dbg(INFO_ZONE, "common card ready received\n");
		common->hibernate_resume = false;
		rsi_handle_card_पढ़ोy(common, msg);
		अवरोध;
	हाल SLEEP_NOTIFY_IND:
		rsi_dbg(INFO_ZONE, "sleep notify received\n");
		rsi_mgmt_pkt_recv(common, msg);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक rsi_map_coex_q(u8 hal_queue)
अणु
	चयन (hal_queue) अणु
	हाल RSI_COEX_Q:
		वापस RSI_COEX_Q_COMMON;
	हाल RSI_WLAN_Q:
		वापस RSI_COEX_Q_WLAN;
	हाल RSI_BT_Q:
		वापस RSI_COEX_Q_BT;
	पूर्ण
	वापस RSI_COEX_Q_INVALID;
पूर्ण

पूर्णांक rsi_coex_send_pkt(व्योम *priv, काष्ठा sk_buff *skb, u8 hal_queue)
अणु
	काष्ठा rsi_common *common = (काष्ठा rsi_common *)priv;
	काष्ठा rsi_coex_ctrl_block *coex_cb =
		(काष्ठा rsi_coex_ctrl_block *)common->coex_cb;
	काष्ठा skb_info *tx_params = शून्य;
	क्रमागत rsi_coex_queues coex_q;
	पूर्णांक status;

	coex_q = rsi_map_coex_q(hal_queue);
	अगर (coex_q == RSI_COEX_Q_INVALID) अणु
		rsi_dbg(ERR_ZONE, "Invalid coex queue\n");
		वापस -EINVAL;
	पूर्ण
	अगर (coex_q != RSI_COEX_Q_COMMON &&
	    coex_q != RSI_COEX_Q_WLAN) अणु
		skb_queue_tail(&coex_cb->coex_tx_qs[coex_q], skb);
		rsi_set_event(&coex_cb->coex_tx_thपढ़ो.event);
		वापस 0;
	पूर्ण
	अगर (common->अगरace_करोwn) अणु
		tx_params =
			(काष्ठा skb_info *)&IEEE80211_SKB_CB(skb)->driver_data;

		अगर (!(tx_params->flags & INTERNAL_MGMT_PKT)) अणु
			rsi_indicate_tx_status(common->priv, skb, -EINVAL);
			वापस 0;
		पूर्ण
	पूर्ण

	/* Send packet to hal */
	अगर (skb->priority == MGMT_SOFT_Q)
		status = rsi_send_mgmt_pkt(common, skb);
	अन्यथा
		status = rsi_send_data_pkt(common, skb);

	वापस status;
पूर्ण

पूर्णांक rsi_coex_attach(काष्ठा rsi_common *common)
अणु
	काष्ठा rsi_coex_ctrl_block *coex_cb;
	पूर्णांक cnt;

	coex_cb = kzalloc(माप(*coex_cb), GFP_KERNEL);
	अगर (!coex_cb)
		वापस -ENOMEM;

	common->coex_cb = (व्योम *)coex_cb;
	coex_cb->priv = common;

	/* Initialize co-ex queues */
	क्रम (cnt = 0; cnt < NUM_COEX_TX_QUEUES; cnt++)
		skb_queue_head_init(&coex_cb->coex_tx_qs[cnt]);
	rsi_init_event(&coex_cb->coex_tx_thपढ़ो.event);

	/* Initialize co-ex thपढ़ो */
	अगर (rsi_create_kthपढ़ो(common,
			       &coex_cb->coex_tx_thपढ़ो,
			       rsi_coex_scheduler_thपढ़ो,
			       "Coex-Tx-Thread")) अणु
		rsi_dbg(ERR_ZONE, "%s: Unable to init tx thrd\n", __func__);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

व्योम rsi_coex_detach(काष्ठा rsi_common *common)
अणु
	काष्ठा rsi_coex_ctrl_block *coex_cb =
		(काष्ठा rsi_coex_ctrl_block *)common->coex_cb;
	पूर्णांक cnt;

	rsi_समाप्त_thपढ़ो(&coex_cb->coex_tx_thपढ़ो);

	क्रम (cnt = 0; cnt < NUM_COEX_TX_QUEUES; cnt++)
		skb_queue_purge(&coex_cb->coex_tx_qs[cnt]);

	kमुक्त(coex_cb);
पूर्ण
