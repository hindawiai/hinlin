<शैली गुरु>
/*
 * Copyright (c) 2014 Redpine Signals Inc.
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

#समावेश "rsi_mgmt.h"
#समावेश "rsi_common.h"
#समावेश "rsi_hal.h"
#समावेश "rsi_coex.h"

/**
 * rsi_determine_min_weight_queue() - This function determines the queue with
 *				      the min weight.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 *
 * Return: q_num: Corresponding queue number.
 */
अटल u8 rsi_determine_min_weight_queue(काष्ठा rsi_common *common)
अणु
	काष्ठा wmm_qinfo *tx_qinfo = common->tx_qinfo;
	u32 q_len = 0;
	u8 ii = 0;

	क्रम (ii = 0; ii < NUM_EDCA_QUEUES; ii++) अणु
		q_len = skb_queue_len(&common->tx_queue[ii]);
		अगर ((tx_qinfo[ii].pkt_contended) && q_len) अणु
			common->min_weight = tx_qinfo[ii].weight;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ii;
पूर्ण

/**
 * rsi_recalculate_weights() - This function recalculates the weights
 *			       corresponding to each queue.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 *
 * Return: recontend_queue bool variable
 */
अटल bool rsi_recalculate_weights(काष्ठा rsi_common *common)
अणु
	काष्ठा wmm_qinfo *tx_qinfo = common->tx_qinfo;
	bool recontend_queue = false;
	u8 ii = 0;
	u32 q_len = 0;

	क्रम (ii = 0; ii < NUM_EDCA_QUEUES; ii++) अणु
		q_len = skb_queue_len(&common->tx_queue[ii]);
		/* Check क्रम the need of contention */
		अगर (q_len) अणु
			अगर (tx_qinfo[ii].pkt_contended) अणु
				tx_qinfo[ii].weight =
				((tx_qinfo[ii].weight > common->min_weight) ?
				 tx_qinfo[ii].weight - common->min_weight : 0);
			पूर्ण अन्यथा अणु
				tx_qinfo[ii].pkt_contended = 1;
				tx_qinfo[ii].weight = tx_qinfo[ii].wme_params;
				recontend_queue = true;
			पूर्ण
		पूर्ण अन्यथा अणु /* No packets so no contention */
			tx_qinfo[ii].weight = 0;
			tx_qinfo[ii].pkt_contended = 0;
		पूर्ण
	पूर्ण

	वापस recontend_queue;
पूर्ण

/**
 * rsi_get_num_pkts_dequeue() - This function determines the number of
 *		                packets to be dequeued based on the number
 *			        of bytes calculated using txop.
 *
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @q_num: the queue from which pkts have to be dequeued
 *
 * Return: pkt_num: Number of pkts to be dequeued.
 */
अटल u32 rsi_get_num_pkts_dequeue(काष्ठा rsi_common *common, u8 q_num)
अणु
	काष्ठा rsi_hw *adapter = common->priv;
	काष्ठा sk_buff *skb;
	u32 pkt_cnt = 0;
	s16 txop = common->tx_qinfo[q_num].txop * 32;
	__le16 r_txop;
	काष्ठा ieee80211_rate rate;
	काष्ठा ieee80211_hdr *wh;
	काष्ठा ieee80211_vअगर *vअगर;

	rate.bitrate = RSI_RATE_MCS0 * 5 * 10; /* Convert to Kbps */
	अगर (q_num == VI_Q)
		txop = ((txop << 5) / 80);

	अगर (skb_queue_len(&common->tx_queue[q_num]))
		skb = skb_peek(&common->tx_queue[q_num]);
	अन्यथा
		वापस 0;

	करो अणु
		wh = (काष्ठा ieee80211_hdr *)skb->data;
		vअगर = rsi_get_vअगर(adapter, wh->addr2);
		r_txop = ieee80211_generic_frame_duration(adapter->hw,
							  vअगर,
							  common->band,
							  skb->len, &rate);
		txop -= le16_to_cpu(r_txop);
		pkt_cnt += 1;
		/*checking अगर pkts are still there*/
		अगर (skb_queue_len(&common->tx_queue[q_num]) - pkt_cnt)
			skb = skb->next;
		अन्यथा
			अवरोध;

	पूर्ण जबतक (txop > 0);

	वापस pkt_cnt;
पूर्ण

/**
 * rsi_core_determine_hal_queue() - This function determines the queue from
 *				    which packet has to be dequeued.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 *
 * Return: q_num: Corresponding queue number on success.
 */
अटल u8 rsi_core_determine_hal_queue(काष्ठा rsi_common *common)
अणु
	bool recontend_queue = false;
	u32 q_len = 0;
	u8 q_num = INVALID_QUEUE;
	u8 ii = 0;

	अगर (skb_queue_len(&common->tx_queue[MGMT_BEACON_Q])) अणु
		q_num = MGMT_BEACON_Q;
		वापस q_num;
	पूर्ण
	अगर (skb_queue_len(&common->tx_queue[MGMT_SOFT_Q])) अणु
		अगर (!common->mgmt_q_block)
			q_num = MGMT_SOFT_Q;
		वापस q_num;
	पूर्ण

	अगर (common->hw_data_qs_blocked)
		वापस q_num;

	अगर (common->pkt_cnt != 0) अणु
		--common->pkt_cnt;
		वापस common->selected_qnum;
	पूर्ण

get_queue_num:
	recontend_queue = false;

	q_num = rsi_determine_min_weight_queue(common);

	ii = q_num;

	/* Selecting the queue with least back off */
	क्रम (; ii < NUM_EDCA_QUEUES; ii++) अणु
		q_len = skb_queue_len(&common->tx_queue[ii]);
		अगर (((common->tx_qinfo[ii].pkt_contended) &&
		     (common->tx_qinfo[ii].weight < common->min_weight)) &&
		      q_len) अणु
			common->min_weight = common->tx_qinfo[ii].weight;
			q_num = ii;
		पूर्ण
	पूर्ण

	अगर (q_num < NUM_EDCA_QUEUES)
		common->tx_qinfo[q_num].pkt_contended = 0;

	/* Adjust the back off values क्रम all queues again */
	recontend_queue = rsi_recalculate_weights(common);

	q_len = skb_queue_len(&common->tx_queue[q_num]);
	अगर (!q_len) अणु
		/* If any queues are freshly contended and the selected queue
		 * करोesn't have any packets
		 * then get the queue number again with fresh values
		 */
		अगर (recontend_queue)
			जाओ get_queue_num;

		वापस INVALID_QUEUE;
	पूर्ण

	common->selected_qnum = q_num;
	q_len = skb_queue_len(&common->tx_queue[q_num]);

	अगर (q_num == VO_Q || q_num == VI_Q) अणु
		common->pkt_cnt = rsi_get_num_pkts_dequeue(common, q_num);
		common->pkt_cnt -= 1;
	पूर्ण

	वापस q_num;
पूर्ण

/**
 * rsi_core_queue_pkt() - This functions enqueues the packet to the queue
 *			  specअगरied by the queue number.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @skb: Poपूर्णांकer to the socket buffer काष्ठाure.
 *
 * Return: None.
 */
अटल व्योम rsi_core_queue_pkt(काष्ठा rsi_common *common,
			       काष्ठा sk_buff *skb)
अणु
	u8 q_num = skb->priority;
	अगर (q_num >= NUM_SOFT_QUEUES) अणु
		rsi_dbg(ERR_ZONE, "%s: Invalid Queue Number: q_num = %d\n",
			__func__, q_num);
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	skb_queue_tail(&common->tx_queue[q_num], skb);
पूर्ण

/**
 * rsi_core_dequeue_pkt() - This functions dequeues the packet from the queue
 *			    specअगरied by the queue number.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @q_num: Queue number.
 *
 * Return: Poपूर्णांकer to sk_buff काष्ठाure.
 */
अटल काष्ठा sk_buff *rsi_core_dequeue_pkt(काष्ठा rsi_common *common,
					    u8 q_num)
अणु
	अगर (q_num >= NUM_SOFT_QUEUES) अणु
		rsi_dbg(ERR_ZONE, "%s: Invalid Queue Number: q_num = %d\n",
			__func__, q_num);
		वापस शून्य;
	पूर्ण

	वापस skb_dequeue(&common->tx_queue[q_num]);
पूर्ण

/**
 * rsi_core_qos_processor() - This function is used to determine the wmm queue
 *			      based on the backoff procedure. Data packets are
 *			      dequeued from the selected hal queue and sent to
 *			      the below layers.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 *
 * Return: None.
 */
व्योम rsi_core_qos_processor(काष्ठा rsi_common *common)
अणु
	काष्ठा rsi_hw *adapter = common->priv;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ tstamp_1, tstamp_2;
	u8 q_num;
	पूर्णांक status;

	tstamp_1 = jअगरfies;
	जबतक (1) अणु
		q_num = rsi_core_determine_hal_queue(common);
		rsi_dbg(DATA_TX_ZONE,
			"%s: Queue number = %d\n", __func__, q_num);

		अगर (q_num == INVALID_QUEUE) अणु
			rsi_dbg(DATA_TX_ZONE, "%s: No More Pkt\n", __func__);
			अवरोध;
		पूर्ण
		अगर (common->hibernate_resume)
			अवरोध;

		mutex_lock(&common->tx_lock);

		status = adapter->check_hw_queue_status(adapter, q_num);
		अगर ((status <= 0)) अणु
			mutex_unlock(&common->tx_lock);
			अवरोध;
		पूर्ण

		अगर ((q_num < MGMT_SOFT_Q) &&
		    ((skb_queue_len(&common->tx_queue[q_num])) <=
		      MIN_DATA_QUEUE_WATER_MARK)) अणु
			अगर (ieee80211_queue_stopped(adapter->hw, WME_AC(q_num)))
				ieee80211_wake_queue(adapter->hw,
						     WME_AC(q_num));
		पूर्ण

		skb = rsi_core_dequeue_pkt(common, q_num);
		अगर (skb == शून्य) अणु
			rsi_dbg(ERR_ZONE, "skb null\n");
			mutex_unlock(&common->tx_lock);
			अवरोध;
		पूर्ण
		अगर (q_num == MGMT_BEACON_Q) अणु
			status = rsi_send_pkt_to_bus(common, skb);
			dev_kमुक्त_skb(skb);
		पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_RSI_COEX
			अगर (common->coex_mode > 1) अणु
				status = rsi_coex_send_pkt(common, skb,
							   RSI_WLAN_Q);
			पूर्ण अन्यथा अणु
#पूर्ण_अगर
				अगर (q_num == MGMT_SOFT_Q)
					status = rsi_send_mgmt_pkt(common, skb);
				अन्यथा
					status = rsi_send_data_pkt(common, skb);
#अगर_घोषित CONFIG_RSI_COEX
			पूर्ण
#पूर्ण_अगर
		पूर्ण

		अगर (status) अणु
			mutex_unlock(&common->tx_lock);
			अवरोध;
		पूर्ण

		common->tx_stats.total_tx_pkt_send[q_num]++;

		tstamp_2 = jअगरfies;
		mutex_unlock(&common->tx_lock);

		अगर (समय_after(tstamp_2, tstamp_1 + (300 * HZ) / 1000))
			schedule();
	पूर्ण
पूर्ण

काष्ठा rsi_sta *rsi_find_sta(काष्ठा rsi_common *common, u8 *mac_addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < common->max_stations; i++) अणु
		अगर (!common->stations[i].sta)
			जारी;
		अगर (!(स_भेद(common->stations[i].sta->addr,
			     mac_addr, ETH_ALEN)))
			वापस &common->stations[i];
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा ieee80211_vअगर *rsi_get_vअगर(काष्ठा rsi_hw *adapter, u8 *mac)
अणु
	काष्ठा ieee80211_vअगर *vअगर;
	पूर्णांक i;

	क्रम (i = 0; i < RSI_MAX_VIFS; i++) अणु
		vअगर = adapter->vअगरs[i];
		अगर (!vअगर)
			जारी;
		अगर (!स_भेद(vअगर->addr, mac, ETH_ALEN))
			वापस vअगर;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * rsi_core_xmit() - This function transmits the packets received from mac80211
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @skb: Poपूर्णांकer to the socket buffer काष्ठाure.
 *
 * Return: None.
 */
व्योम rsi_core_xmit(काष्ठा rsi_common *common, काष्ठा sk_buff *skb)
अणु
	काष्ठा rsi_hw *adapter = common->priv;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा skb_info *tx_params;
	काष्ठा ieee80211_hdr *wh = शून्य;
	काष्ठा ieee80211_vअगर *vअगर;
	u8 q_num, tid = 0;
	काष्ठा rsi_sta *rsta = शून्य;

	अगर ((!skb) || (!skb->len)) अणु
		rsi_dbg(ERR_ZONE, "%s: Null skb/zero Length packet\n",
			__func__);
		जाओ xmit_fail;
	पूर्ण
	अगर (common->fsm_state != FSM_MAC_INIT_DONE) अणु
		rsi_dbg(ERR_ZONE, "%s: FSM state not open\n", __func__);
		जाओ xmit_fail;
	पूर्ण
	अगर (common->wow_flags & RSI_WOW_ENABLED) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Blocking Tx_packets when WOWLAN is enabled\n",
			__func__);
		जाओ xmit_fail;
	पूर्ण

	info = IEEE80211_SKB_CB(skb);
	tx_params = (काष्ठा skb_info *)info->driver_data;
	wh = (काष्ठा ieee80211_hdr *)&skb->data[0];
	tx_params->sta_id = 0;

	vअगर = rsi_get_vअगर(adapter, wh->addr2);
	अगर (!vअगर)
		जाओ xmit_fail;
	tx_params->vअगर = vअगर;
	tx_params->vap_id = ((काष्ठा vअगर_priv *)vअगर->drv_priv)->vap_id;
	अगर ((ieee80211_is_mgmt(wh->frame_control)) ||
	    (ieee80211_is_ctl(wh->frame_control)) ||
	    (ieee80211_is_qos_nullfunc(wh->frame_control))) अणु
		अगर (ieee80211_is_assoc_req(wh->frame_control) ||
		    ieee80211_is_reassoc_req(wh->frame_control)) अणु
			काष्ठा ieee80211_bss_conf *bss = &vअगर->bss_conf;

			common->eapol4_confirm = false;
			rsi_hal_send_sta_notअगरy_frame(common,
						      RSI_IFTYPE_STATION,
						      STA_CONNECTED, bss->bssid,
						      bss->qos, bss->aid, 0,
						      vअगर);
		पूर्ण

		q_num = MGMT_SOFT_Q;
		skb->priority = q_num;

		अगर (rsi_prepare_mgmt_desc(common, skb)) अणु
			rsi_dbg(ERR_ZONE, "Failed to prepare desc\n");
			जाओ xmit_fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ieee80211_is_data_qos(wh->frame_control)) अणु
			u8 *qos = ieee80211_get_qos_ctl(wh);

			tid = *qos & IEEE80211_QOS_CTL_TID_MASK;
			skb->priority = TID_TO_WME_AC(tid);
		पूर्ण अन्यथा अणु
			tid = IEEE80211_NONQOS_TID;
			skb->priority = BE_Q;
		पूर्ण

		q_num = skb->priority;
		tx_params->tid = tid;

		अगर (((vअगर->type == NL80211_IFTYPE_AP) ||
		     (vअगर->type == NL80211_IFTYPE_P2P_GO)) &&
		    (!is_broadcast_ether_addr(wh->addr1)) &&
		    (!is_multicast_ether_addr(wh->addr1))) अणु
			rsta = rsi_find_sta(common, wh->addr1);
			अगर (!rsta)
				जाओ xmit_fail;
			tx_params->sta_id = rsta->sta_id;
		पूर्ण अन्यथा अणु
			tx_params->sta_id = 0;
		पूर्ण

		अगर (rsta) अणु
			/* Start aggregation अगर not करोne क्रम this tid */
			अगर (!rsta->start_tx_aggr[tid]) अणु
				rsta->start_tx_aggr[tid] = true;
				ieee80211_start_tx_ba_session(rsta->sta,
							      tid, 0);
			पूर्ण
		पूर्ण
		अगर (skb->protocol == cpu_to_be16(ETH_P_PAE)) अणु
			q_num = MGMT_SOFT_Q;
			skb->priority = q_num;
		पूर्ण
		अगर (rsi_prepare_data_desc(common, skb)) अणु
			rsi_dbg(ERR_ZONE, "Failed to prepare data desc\n");
			जाओ xmit_fail;
		पूर्ण
	पूर्ण

	अगर ((q_num < MGMT_SOFT_Q) &&
	    ((skb_queue_len(&common->tx_queue[q_num]) + 1) >=
	     DATA_QUEUE_WATER_MARK)) अणु
		rsi_dbg(ERR_ZONE, "%s: sw queue full\n", __func__);
		अगर (!ieee80211_queue_stopped(adapter->hw, WME_AC(q_num)))
			ieee80211_stop_queue(adapter->hw, WME_AC(q_num));
		rsi_set_event(&common->tx_thपढ़ो.event);
		जाओ xmit_fail;
	पूर्ण

	rsi_core_queue_pkt(common, skb);
	rsi_dbg(DATA_TX_ZONE, "%s: ===> Scheduling TX thread <===\n", __func__);
	rsi_set_event(&common->tx_thपढ़ो.event);

	वापस;

xmit_fail:
	rsi_dbg(ERR_ZONE, "%s: Failed to queue packet\n", __func__);
	/* Dropping pkt here */
	ieee80211_मुक्त_txskb(common->priv->hw, skb);
पूर्ण
