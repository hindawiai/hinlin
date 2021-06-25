<शैली गुरु>
/*
 * NXP Wireless LAN device driver: generic TX/RX data handling
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#समावेश "decl.h"
#समावेश "ioctl.h"
#समावेश "util.h"
#समावेश "fw.h"
#समावेश "main.h"
#समावेश "wmm.h"

/*
 * This function processes the received buffer.
 *
 * Main responsibility of this function is to parse the RxPD to
 * identअगरy the correct पूर्णांकerface this packet is headed क्रम and
 * क्रमwarding it to the associated handling function, where the
 * packet will be further processed and sent to kernel/upper layer
 * अगर required.
 */
पूर्णांक mwअगरiex_handle_rx_packet(काष्ठा mwअगरiex_adapter *adapter,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा mwअगरiex_निजी *priv =
		mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);
	काष्ठा rxpd *local_rx_pd;
	काष्ठा mwअगरiex_rxinfo *rx_info = MWIFIEX_SKB_RXCB(skb);
	पूर्णांक ret;

	local_rx_pd = (काष्ठा rxpd *) (skb->data);
	/* Get the BSS number from rxpd, get corresponding priv */
	priv = mwअगरiex_get_priv_by_id(adapter, local_rx_pd->bss_num &
				      BSS_NUM_MASK, local_rx_pd->bss_type);
	अगर (!priv)
		priv = mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);

	अगर (!priv) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "data: priv not found. Drop RX packet\n");
		dev_kमुक्त_skb_any(skb);
		वापस -1;
	पूर्ण

	mwअगरiex_dbg_dump(adapter, DAT_D, "rx pkt:", skb->data,
			 min_t(माप_प्रकार, skb->len, DEBUG_DUMP_DATA_MAX_LEN));

	स_रखो(rx_info, 0, माप(*rx_info));
	rx_info->bss_num = priv->bss_num;
	rx_info->bss_type = priv->bss_type;

	अगर (priv->bss_role == MWIFIEX_BSS_ROLE_UAP)
		ret = mwअगरiex_process_uap_rx_packet(priv, skb);
	अन्यथा
		ret = mwअगरiex_process_sta_rx_packet(priv, skb);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_handle_rx_packet);

/*
 * This function sends a packet to device.
 *
 * It processes the packet to add the TxPD, checks condition and
 * sends the processed packet to firmware क्रम transmission.
 *
 * On successful completion, the function calls the completion callback
 * and logs the समय.
 */
पूर्णांक mwअगरiex_process_tx(काष्ठा mwअगरiex_निजी *priv, काष्ठा sk_buff *skb,
		       काष्ठा mwअगरiex_tx_param *tx_param)
अणु
	पूर्णांक hroom, ret = -1;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	u8 *head_ptr;
	काष्ठा txpd *local_tx_pd = शून्य;
	काष्ठा mwअगरiex_sta_node *dest_node;
	काष्ठा ethhdr *hdr = (व्योम *)skb->data;

	hroom = adapter->पूर्णांकf_hdr_len;

	अगर (priv->bss_role == MWIFIEX_BSS_ROLE_UAP) अणु
		dest_node = mwअगरiex_get_sta_entry(priv, hdr->h_dest);
		अगर (dest_node) अणु
			dest_node->stats.tx_bytes += skb->len;
			dest_node->stats.tx_packets++;
		पूर्ण

		head_ptr = mwअगरiex_process_uap_txpd(priv, skb);
	पूर्ण अन्यथा अणु
		head_ptr = mwअगरiex_process_sta_txpd(priv, skb);
	पूर्ण

	अगर ((adapter->data_sent || adapter->tx_lock_flag) && head_ptr) अणु
		skb_queue_tail(&adapter->tx_data_q, skb);
		atomic_inc(&adapter->tx_queued);
		वापस 0;
	पूर्ण

	अगर (head_ptr) अणु
		अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA)
			local_tx_pd = (काष्ठा txpd *)(head_ptr + hroom);
		अगर (adapter->अगरace_type == MWIFIEX_USB) अणु
			ret = adapter->अगर_ops.host_to_card(adapter,
							   priv->usb_port,
							   skb, tx_param);
		पूर्ण अन्यथा अणु
			ret = adapter->अगर_ops.host_to_card(adapter,
							   MWIFIEX_TYPE_DATA,
							   skb, tx_param);
		पूर्ण
	पूर्ण
	mwअगरiex_dbg_dump(adapter, DAT_D, "tx pkt:", skb->data,
			 min_t(माप_प्रकार, skb->len, DEBUG_DUMP_DATA_MAX_LEN));

	चयन (ret) अणु
	हाल -ENOSR:
		mwअगरiex_dbg(adapter, DATA, "data: -ENOSR is returned\n");
		अवरोध;
	हाल -EBUSY:
		अगर ((GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA) &&
		    (adapter->pps_uapsd_mode) && (adapter->tx_lock_flag)) अणु
				priv->adapter->tx_lock_flag = false;
				अगर (local_tx_pd)
					local_tx_pd->flags = 0;
		पूर्ण
		mwअगरiex_dbg(adapter, ERROR, "data: -EBUSY is returned\n");
		अवरोध;
	हाल -1:
		mwअगरiex_dbg(adapter, ERROR,
			    "mwifiex_write_data_async failed: 0x%X\n",
			    ret);
		adapter->dbg.num_tx_host_to_card_failure++;
		mwअगरiex_ग_लिखो_data_complete(adapter, skb, 0, ret);
		अवरोध;
	हाल -EINPROGRESS:
		अवरोध;
	हाल 0:
		mwअगरiex_ग_लिखो_data_complete(adapter, skb, 0, ret);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mwअगरiex_host_to_card(काष्ठा mwअगरiex_adapter *adapter,
				काष्ठा sk_buff *skb,
				काष्ठा mwअगरiex_tx_param *tx_param)
अणु
	काष्ठा txpd *local_tx_pd = शून्य;
	u8 *head_ptr = skb->data;
	पूर्णांक ret = 0;
	काष्ठा mwअगरiex_निजी *priv;
	काष्ठा mwअगरiex_txinfo *tx_info;

	tx_info = MWIFIEX_SKB_TXCB(skb);
	priv = mwअगरiex_get_priv_by_id(adapter, tx_info->bss_num,
				      tx_info->bss_type);
	अगर (!priv) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "data: priv not found. Drop TX packet\n");
		adapter->dbg.num_tx_host_to_card_failure++;
		mwअगरiex_ग_लिखो_data_complete(adapter, skb, 0, 0);
		वापस ret;
	पूर्ण
	अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA)
		local_tx_pd = (काष्ठा txpd *)(head_ptr + adapter->पूर्णांकf_hdr_len);

	अगर (adapter->अगरace_type == MWIFIEX_USB) अणु
		ret = adapter->अगर_ops.host_to_card(adapter,
						   priv->usb_port,
						   skb, tx_param);
	पूर्ण अन्यथा अणु
		ret = adapter->अगर_ops.host_to_card(adapter,
						   MWIFIEX_TYPE_DATA,
						   skb, tx_param);
	पूर्ण
	चयन (ret) अणु
	हाल -ENOSR:
		mwअगरiex_dbg(adapter, ERROR, "data: -ENOSR is returned\n");
		अवरोध;
	हाल -EBUSY:
		अगर ((GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA) &&
		    (adapter->pps_uapsd_mode) &&
		    (adapter->tx_lock_flag)) अणु
			priv->adapter->tx_lock_flag = false;
			अगर (local_tx_pd)
				local_tx_pd->flags = 0;
		पूर्ण
		skb_queue_head(&adapter->tx_data_q, skb);
		अगर (tx_info->flags & MWIFIEX_BUF_FLAG_AGGR_PKT)
			atomic_add(tx_info->aggr_num, &adapter->tx_queued);
		अन्यथा
			atomic_inc(&adapter->tx_queued);
		mwअगरiex_dbg(adapter, ERROR, "data: -EBUSY is returned\n");
		अवरोध;
	हाल -1:
		mwअगरiex_dbg(adapter, ERROR,
			    "mwifiex_write_data_async failed: 0x%X\n", ret);
		adapter->dbg.num_tx_host_to_card_failure++;
		mwअगरiex_ग_लिखो_data_complete(adapter, skb, 0, ret);
		अवरोध;
	हाल -EINPROGRESS:
		अवरोध;
	हाल 0:
		mwअगरiex_ग_लिखो_data_complete(adapter, skb, 0, ret);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
mwअगरiex_dequeue_tx_queue(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा sk_buff *skb, *skb_next;
	काष्ठा mwअगरiex_txinfo *tx_info;
	काष्ठा mwअगरiex_tx_param tx_param;

	skb = skb_dequeue(&adapter->tx_data_q);
	अगर (!skb)
		वापस -1;

	tx_info = MWIFIEX_SKB_TXCB(skb);
	अगर (tx_info->flags & MWIFIEX_BUF_FLAG_AGGR_PKT)
		atomic_sub(tx_info->aggr_num, &adapter->tx_queued);
	अन्यथा
		atomic_dec(&adapter->tx_queued);

	अगर (!skb_queue_empty(&adapter->tx_data_q))
		skb_next = skb_peek(&adapter->tx_data_q);
	अन्यथा
		skb_next = शून्य;
	tx_param.next_pkt_len = ((skb_next) ? skb_next->len : 0);
	अगर (!tx_param.next_pkt_len) अणु
		अगर (!mwअगरiex_wmm_lists_empty(adapter))
			tx_param.next_pkt_len = 1;
	पूर्ण
	वापस mwअगरiex_host_to_card(adapter, skb, &tx_param);
पूर्ण

व्योम
mwअगरiex_process_tx_queue(काष्ठा mwअगरiex_adapter *adapter)
अणु
	करो अणु
		अगर (adapter->data_sent || adapter->tx_lock_flag)
			अवरोध;
		अगर (mwअगरiex_dequeue_tx_queue(adapter))
			अवरोध;
	पूर्ण जबतक (!skb_queue_empty(&adapter->tx_data_q));
पूर्ण

/*
 * Packet send completion callback handler.
 *
 * It either मुक्तs the buffer directly or क्रमwards it to another
 * completion callback which checks conditions, updates statistics,
 * wakes up stalled traffic queue अगर required, and then मुक्तs the buffer.
 */
पूर्णांक mwअगरiex_ग_लिखो_data_complete(काष्ठा mwअगरiex_adapter *adapter,
				काष्ठा sk_buff *skb, पूर्णांक aggr, पूर्णांक status)
अणु
	काष्ठा mwअगरiex_निजी *priv;
	काष्ठा mwअगरiex_txinfo *tx_info;
	काष्ठा netdev_queue *txq;
	पूर्णांक index;

	अगर (!skb)
		वापस 0;

	tx_info = MWIFIEX_SKB_TXCB(skb);
	priv = mwअगरiex_get_priv_by_id(adapter, tx_info->bss_num,
				      tx_info->bss_type);
	अगर (!priv)
		जाओ करोne;

	mwअगरiex_set_trans_start(priv->netdev);

	अगर (tx_info->flags & MWIFIEX_BUF_FLAG_BRIDGED_PKT)
		atomic_dec_वापस(&adapter->pending_bridged_pkts);

	अगर (tx_info->flags & MWIFIEX_BUF_FLAG_AGGR_PKT)
		जाओ करोne;

	अगर (!status) अणु
		priv->stats.tx_packets++;
		priv->stats.tx_bytes += tx_info->pkt_len;
		अगर (priv->tx_समयout_cnt)
			priv->tx_समयout_cnt = 0;
	पूर्ण अन्यथा अणु
		priv->stats.tx_errors++;
	पूर्ण

	अगर (aggr)
		/* For skb_aggr, करो not wake up tx queue */
		जाओ करोne;

	atomic_dec(&adapter->tx_pending);

	index = mwअगरiex_1d_to_wmm_queue[skb->priority];
	अगर (atomic_dec_वापस(&priv->wmm_tx_pending[index]) < LOW_TX_PENDING) अणु
		txq = netdev_get_tx_queue(priv->netdev, index);
		अगर (netअगर_tx_queue_stopped(txq)) अणु
			netअगर_tx_wake_queue(txq);
			mwअगरiex_dbg(adapter, DATA, "wake queue: %d\n", index);
		पूर्ण
	पूर्ण
करोne:
	dev_kमुक्त_skb_any(skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_ग_लिखो_data_complete);

व्योम mwअगरiex_parse_tx_status_event(काष्ठा mwअगरiex_निजी *priv,
				   व्योम *event_body)
अणु
	काष्ठा tx_status_event *tx_status = (व्योम *)priv->adapter->event_body;
	काष्ठा sk_buff *ack_skb;
	काष्ठा mwअगरiex_txinfo *tx_info;

	अगर (!tx_status->tx_token_id)
		वापस;

	spin_lock_bh(&priv->ack_status_lock);
	ack_skb = idr_हटाओ(&priv->ack_status_frames, tx_status->tx_token_id);
	spin_unlock_bh(&priv->ack_status_lock);

	अगर (ack_skb) अणु
		tx_info = MWIFIEX_SKB_TXCB(ack_skb);

		अगर (tx_info->flags & MWIFIEX_BUF_FLAG_EAPOL_TX_STATUS) अणु
			/* consumes ack_skb */
			skb_complete_wअगरi_ack(ack_skb, !tx_status->status);
		पूर्ण अन्यथा अणु
			/* Remove broadcast address which was added by driver */
			स_हटाओ(ack_skb->data +
				माप(काष्ठा ieee80211_hdr_3addr) +
				MWIFIEX_MGMT_FRAME_HEADER_SIZE + माप(u16),
				ack_skb->data +
				माप(काष्ठा ieee80211_hdr_3addr) +
				MWIFIEX_MGMT_FRAME_HEADER_SIZE + माप(u16) +
				ETH_ALEN, ack_skb->len -
				(माप(काष्ठा ieee80211_hdr_3addr) +
				MWIFIEX_MGMT_FRAME_HEADER_SIZE + माप(u16) +
				ETH_ALEN));
			ack_skb->len = ack_skb->len - ETH_ALEN;
			/* Remove driver's proprietary header including 2 bytes
			 * of packet length and pass actual management frame buffer
			 * to cfg80211.
			 */
			cfg80211_mgmt_tx_status(&priv->wdev, tx_info->cookie,
						ack_skb->data +
						MWIFIEX_MGMT_FRAME_HEADER_SIZE +
						माप(u16), ack_skb->len -
						(MWIFIEX_MGMT_FRAME_HEADER_SIZE
						 + माप(u16)),
						!tx_status->status, GFP_ATOMIC);
			dev_kमुक्त_skb_any(ack_skb);
		पूर्ण
	पूर्ण
पूर्ण
