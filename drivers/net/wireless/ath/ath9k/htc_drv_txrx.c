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

/******/
/* TX */
/******/

अटल स्थिर पूर्णांक subtype_txq_to_hwq[] = अणु
	[IEEE80211_AC_BE] = ATH_TXQ_AC_BE,
	[IEEE80211_AC_BK] = ATH_TXQ_AC_BK,
	[IEEE80211_AC_VI] = ATH_TXQ_AC_VI,
	[IEEE80211_AC_VO] = ATH_TXQ_AC_VO,
पूर्ण;

#घोषणा ATH9K_HTC_INIT_TXQ(subtype) करो अणु			\
		qi.tqi_subtype = subtype_txq_to_hwq[subtype];	\
		qi.tqi_aअगरs = ATH9K_TXQ_USEDEFAULT;		\
		qi.tqi_cwmin = ATH9K_TXQ_USEDEFAULT;		\
		qi.tqi_cwmax = ATH9K_TXQ_USEDEFAULT;		\
		qi.tqi_physCompBuf = 0;				\
		qi.tqi_qflags = TXQ_FLAG_TXEOLINT_ENABLE |	\
			TXQ_FLAG_TXDESCINT_ENABLE;		\
	पूर्ण जबतक (0)

पूर्णांक get_hw_qnum(u16 queue, पूर्णांक *hwq_map)
अणु
	चयन (queue) अणु
	हाल 0:
		वापस hwq_map[IEEE80211_AC_VO];
	हाल 1:
		वापस hwq_map[IEEE80211_AC_VI];
	हाल 2:
		वापस hwq_map[IEEE80211_AC_BE];
	हाल 3:
		वापस hwq_map[IEEE80211_AC_BK];
	शेष:
		वापस hwq_map[IEEE80211_AC_BE];
	पूर्ण
पूर्ण

व्योम ath9k_htc_check_stop_queues(काष्ठा ath9k_htc_priv *priv)
अणु
	spin_lock_bh(&priv->tx.tx_lock);
	priv->tx.queued_cnt++;
	अगर ((priv->tx.queued_cnt >= ATH9K_HTC_TX_THRESHOLD) &&
	    !(priv->tx.flags & ATH9K_HTC_OP_TX_QUEUES_STOP)) अणु
		priv->tx.flags |= ATH9K_HTC_OP_TX_QUEUES_STOP;
		ieee80211_stop_queues(priv->hw);
	पूर्ण
	spin_unlock_bh(&priv->tx.tx_lock);
पूर्ण

व्योम ath9k_htc_check_wake_queues(काष्ठा ath9k_htc_priv *priv)
अणु
	spin_lock_bh(&priv->tx.tx_lock);
	अगर ((priv->tx.queued_cnt < ATH9K_HTC_TX_THRESHOLD) &&
	    (priv->tx.flags & ATH9K_HTC_OP_TX_QUEUES_STOP)) अणु
		priv->tx.flags &= ~ATH9K_HTC_OP_TX_QUEUES_STOP;
		ieee80211_wake_queues(priv->hw);
	पूर्ण
	spin_unlock_bh(&priv->tx.tx_lock);
पूर्ण

पूर्णांक ath9k_htc_tx_get_slot(काष्ठा ath9k_htc_priv *priv)
अणु
	पूर्णांक slot;

	spin_lock_bh(&priv->tx.tx_lock);
	slot = find_first_zero_bit(priv->tx.tx_slot, MAX_TX_BUF_NUM);
	अगर (slot >= MAX_TX_BUF_NUM) अणु
		spin_unlock_bh(&priv->tx.tx_lock);
		वापस -ENOBUFS;
	पूर्ण
	__set_bit(slot, priv->tx.tx_slot);
	spin_unlock_bh(&priv->tx.tx_lock);

	वापस slot;
पूर्ण

व्योम ath9k_htc_tx_clear_slot(काष्ठा ath9k_htc_priv *priv, पूर्णांक slot)
अणु
	spin_lock_bh(&priv->tx.tx_lock);
	__clear_bit(slot, priv->tx.tx_slot);
	spin_unlock_bh(&priv->tx.tx_lock);
पूर्ण

अटल अंतरभूत क्रमागत htc_endpoपूर्णांक_id get_htc_epid(काष्ठा ath9k_htc_priv *priv,
						u16 qnum)
अणु
	क्रमागत htc_endpoपूर्णांक_id epid;

	चयन (qnum) अणु
	हाल 0:
		TX_QSTAT_INC(IEEE80211_AC_VO);
		epid = priv->data_vo_ep;
		अवरोध;
	हाल 1:
		TX_QSTAT_INC(IEEE80211_AC_VI);
		epid = priv->data_vi_ep;
		अवरोध;
	हाल 2:
		TX_QSTAT_INC(IEEE80211_AC_BE);
		epid = priv->data_be_ep;
		अवरोध;
	हाल 3:
	शेष:
		TX_QSTAT_INC(IEEE80211_AC_BK);
		epid = priv->data_bk_ep;
		अवरोध;
	पूर्ण

	वापस epid;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff_head*
get_htc_epid_queue(काष्ठा ath9k_htc_priv *priv, u8 epid)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा sk_buff_head *epid_queue = शून्य;

	अगर (epid == priv->mgmt_ep)
		epid_queue = &priv->tx.mgmt_ep_queue;
	अन्यथा अगर (epid == priv->cab_ep)
		epid_queue = &priv->tx.cab_ep_queue;
	अन्यथा अगर (epid == priv->data_be_ep)
		epid_queue = &priv->tx.data_be_queue;
	अन्यथा अगर (epid == priv->data_bk_ep)
		epid_queue = &priv->tx.data_bk_queue;
	अन्यथा अगर (epid == priv->data_vi_ep)
		epid_queue = &priv->tx.data_vi_queue;
	अन्यथा अगर (epid == priv->data_vo_ep)
		epid_queue = &priv->tx.data_vo_queue;
	अन्यथा
		ath_err(common, "Invalid EPID: %d\n", epid);

	वापस epid_queue;
पूर्ण

/*
 * Removes the driver header and वापसs the TX slot number
 */
अटल अंतरभूत पूर्णांक strip_drv_header(काष्ठा ath9k_htc_priv *priv,
				   काष्ठा sk_buff *skb)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath9k_htc_tx_ctl *tx_ctl;
	पूर्णांक slot;

	tx_ctl = HTC_SKB_CB(skb);

	अगर (tx_ctl->epid == priv->mgmt_ep) अणु
		काष्ठा tx_mgmt_hdr *tx_mhdr =
			(काष्ठा tx_mgmt_hdr *)skb->data;
		slot = tx_mhdr->cookie;
		skb_pull(skb, माप(काष्ठा tx_mgmt_hdr));
	पूर्ण अन्यथा अगर ((tx_ctl->epid == priv->data_bk_ep) ||
		   (tx_ctl->epid == priv->data_be_ep) ||
		   (tx_ctl->epid == priv->data_vi_ep) ||
		   (tx_ctl->epid == priv->data_vo_ep) ||
		   (tx_ctl->epid == priv->cab_ep)) अणु
		काष्ठा tx_frame_hdr *tx_fhdr =
			(काष्ठा tx_frame_hdr *)skb->data;
		slot = tx_fhdr->cookie;
		skb_pull(skb, माप(काष्ठा tx_frame_hdr));
	पूर्ण अन्यथा अणु
		ath_err(common, "Unsupported EPID: %d\n", tx_ctl->epid);
		slot = -EINVAL;
	पूर्ण

	वापस slot;
पूर्ण

पूर्णांक ath_htc_txq_update(काष्ठा ath9k_htc_priv *priv, पूर्णांक qnum,
		       काष्ठा ath9k_tx_queue_info *qinfo)
अणु
	काष्ठा ath_hw *ah = priv->ah;
	पूर्णांक error = 0;
	काष्ठा ath9k_tx_queue_info qi;

	ath9k_hw_get_txq_props(ah, qnum, &qi);

	qi.tqi_aअगरs = qinfo->tqi_aअगरs;
	qi.tqi_cwmin = qinfo->tqi_cwmin / 2; /* XXX */
	qi.tqi_cwmax = qinfo->tqi_cwmax;
	qi.tqi_burstTime = qinfo->tqi_burstTime;
	qi.tqi_पढ़ोyTime = qinfo->tqi_पढ़ोyTime;

	अगर (!ath9k_hw_set_txq_props(ah, qnum, &qi)) अणु
		ath_err(ath9k_hw_common(ah),
			"Unable to update hardware queue %u!\n", qnum);
		error = -EIO;
	पूर्ण अन्यथा अणु
		ath9k_hw_resettxqueue(ah, qnum);
	पूर्ण

	वापस error;
पूर्ण

अटल व्योम ath9k_htc_tx_mgmt(काष्ठा ath9k_htc_priv *priv,
			      काष्ठा ath9k_htc_vअगर *avp,
			      काष्ठा sk_buff *skb,
			      u8 sta_idx, u8 vअगर_idx, u8 slot)
अणु
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_mgmt *mgmt;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा tx_mgmt_hdr mgmt_hdr;
	काष्ठा ath9k_htc_tx_ctl *tx_ctl;
	u8 *tx_fhdr;

	tx_ctl = HTC_SKB_CB(skb);
	hdr = (काष्ठा ieee80211_hdr *) skb->data;

	स_रखो(tx_ctl, 0, माप(*tx_ctl));
	स_रखो(&mgmt_hdr, 0, माप(काष्ठा tx_mgmt_hdr));

	/*
	 * Set the TSF adjust value क्रम probe response
	 * frame also.
	 */
	अगर (avp && unlikely(ieee80211_is_probe_resp(hdr->frame_control))) अणु
		mgmt = (काष्ठा ieee80211_mgmt *)skb->data;
		mgmt->u.probe_resp.बारtamp = avp->tsfadjust;
	पूर्ण

	tx_ctl->type = ATH9K_HTC_MGMT;

	mgmt_hdr.node_idx = sta_idx;
	mgmt_hdr.vअगर_idx = vअगर_idx;
	mgmt_hdr.tidno = 0;
	mgmt_hdr.flags = 0;
	mgmt_hdr.cookie = slot;

	mgmt_hdr.key_type = ath9k_cmn_get_hw_crypto_keytype(skb);
	अगर (mgmt_hdr.key_type == ATH9K_KEY_TYPE_CLEAR)
		mgmt_hdr.keyix = (u8) ATH9K_TXKEYIX_INVALID;
	अन्यथा
		mgmt_hdr.keyix = tx_info->control.hw_key->hw_key_idx;

	tx_fhdr = skb_push(skb, माप(mgmt_hdr));
	स_नकल(tx_fhdr, (u8 *) &mgmt_hdr, माप(mgmt_hdr));
	tx_ctl->epid = priv->mgmt_ep;
पूर्ण

अटल व्योम ath9k_htc_tx_data(काष्ठा ath9k_htc_priv *priv,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा sk_buff *skb,
			      u8 sta_idx, u8 vअगर_idx, u8 slot,
			      bool is_cab)
अणु
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ath9k_htc_tx_ctl *tx_ctl;
	काष्ठा tx_frame_hdr tx_hdr;
	u32 flags = 0;
	u8 *qc, *tx_fhdr;
	u16 qnum;

	tx_ctl = HTC_SKB_CB(skb);
	hdr = (काष्ठा ieee80211_hdr *) skb->data;

	स_रखो(tx_ctl, 0, माप(*tx_ctl));
	स_रखो(&tx_hdr, 0, माप(काष्ठा tx_frame_hdr));

	tx_hdr.node_idx = sta_idx;
	tx_hdr.vअगर_idx = vअगर_idx;
	tx_hdr.cookie = slot;

	/*
	 * This is a bit redundant but it helps to get
	 * the per-packet index quickly when draining the
	 * TX queue in the HIF layer. Otherwise we would
	 * have to parse the packet contents ...
	 */
	tx_ctl->sta_idx = sta_idx;

	अगर (tx_info->flags & IEEE80211_TX_CTL_AMPDU) अणु
		tx_ctl->type = ATH9K_HTC_AMPDU;
		tx_hdr.data_type = ATH9K_HTC_AMPDU;
	पूर्ण अन्यथा अणु
		tx_ctl->type = ATH9K_HTC_NORMAL;
		tx_hdr.data_type = ATH9K_HTC_NORMAL;
	पूर्ण

	/* Transmit all frames that should not be reordered relative
	 * to each other using the same priority. For other QoS data
	 * frames extract the priority from the header.
	 */
	अगर (!(tx_info->control.flags & IEEE80211_TX_CTRL_DONT_REORDER) &&
	    ieee80211_is_data_qos(hdr->frame_control)) अणु
		qc = ieee80211_get_qos_ctl(hdr);
		tx_hdr.tidno = qc[0] & IEEE80211_QOS_CTL_TID_MASK;
	पूर्ण

	/* Check क्रम RTS protection */
	अगर (priv->hw->wiphy->rts_threshold != (u32) -1)
		अगर (skb->len > priv->hw->wiphy->rts_threshold)
			flags |= ATH9K_HTC_TX_RTSCTS;

	/* CTS-to-self */
	अगर (!(flags & ATH9K_HTC_TX_RTSCTS) &&
	    (vअगर && vअगर->bss_conf.use_cts_prot))
		flags |= ATH9K_HTC_TX_CTSONLY;

	tx_hdr.flags = cpu_to_be32(flags);
	tx_hdr.key_type = ath9k_cmn_get_hw_crypto_keytype(skb);
	अगर (tx_hdr.key_type == ATH9K_KEY_TYPE_CLEAR)
		tx_hdr.keyix = (u8) ATH9K_TXKEYIX_INVALID;
	अन्यथा
		tx_hdr.keyix = tx_info->control.hw_key->hw_key_idx;

	tx_fhdr = skb_push(skb, माप(tx_hdr));
	स_नकल(tx_fhdr, (u8 *) &tx_hdr, माप(tx_hdr));

	अगर (is_cab) अणु
		CAB_STAT_INC;
		tx_ctl->epid = priv->cab_ep;
		वापस;
	पूर्ण

	qnum = skb_get_queue_mapping(skb);
	tx_ctl->epid = get_htc_epid(priv, qnum);
पूर्ण

पूर्णांक ath9k_htc_tx_start(काष्ठा ath9k_htc_priv *priv,
		       काष्ठा ieee80211_sta *sta,
		       काष्ठा sk_buff *skb,
		       u8 slot, bool is_cab)
अणु
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_vअगर *vअगर = tx_info->control.vअगर;
	काष्ठा ath9k_htc_sta *ista;
	काष्ठा ath9k_htc_vअगर *avp = शून्य;
	u8 sta_idx, vअगर_idx;

	hdr = (काष्ठा ieee80211_hdr *) skb->data;

	/*
	 * Find out on which पूर्णांकerface this packet has to be
	 * sent out.
	 */
	अगर (vअगर) अणु
		avp = (काष्ठा ath9k_htc_vअगर *) vअगर->drv_priv;
		vअगर_idx = avp->index;
	पूर्ण अन्यथा अणु
		अगर (!priv->ah->is_monitoring) अणु
			ath_dbg(ath9k_hw_common(priv->ah), XMIT,
				"VIF is null, but no monitor interface !\n");
			वापस -EINVAL;
		पूर्ण

		vअगर_idx = priv->mon_vअगर_idx;
	पूर्ण

	/*
	 * Find out which station this packet is destined क्रम.
	 */
	अगर (sta) अणु
		ista = (काष्ठा ath9k_htc_sta *) sta->drv_priv;
		sta_idx = ista->index;
	पूर्ण अन्यथा अणु
		sta_idx = priv->vअगर_sta_pos[vअगर_idx];
	पूर्ण

	अगर (ieee80211_is_data(hdr->frame_control))
		ath9k_htc_tx_data(priv, vअगर, skb,
				  sta_idx, vअगर_idx, slot, is_cab);
	अन्यथा
		ath9k_htc_tx_mgmt(priv, avp, skb,
				  sta_idx, vअगर_idx, slot);


	वापस htc_send(priv->htc, skb);
पूर्ण

अटल अंतरभूत bool __ath9k_htc_check_tx_aggr(काष्ठा ath9k_htc_priv *priv,
					     काष्ठा ath9k_htc_sta *ista, u8 tid)
अणु
	bool ret = false;

	spin_lock_bh(&priv->tx.tx_lock);
	अगर ((tid < ATH9K_HTC_MAX_TID) && (ista->tid_state[tid] == AGGR_STOP))
		ret = true;
	spin_unlock_bh(&priv->tx.tx_lock);

	वापस ret;
पूर्ण

अटल व्योम ath9k_htc_check_tx_aggr(काष्ठा ath9k_htc_priv *priv,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा ieee80211_hdr *hdr;
	__le16 fc;

	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	fc = hdr->frame_control;

	rcu_पढ़ो_lock();

	sta = ieee80211_find_sta(vअगर, hdr->addr1);
	अगर (!sta) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	अगर (sta && conf_is_ht(&priv->hw->conf) &&
	    !(skb->protocol == cpu_to_be16(ETH_P_PAE))) अणु
		अगर (ieee80211_is_data_qos(fc)) अणु
			u8 *qc, tid;
			काष्ठा ath9k_htc_sta *ista;

			qc = ieee80211_get_qos_ctl(hdr);
			tid = qc[0] & 0xf;
			ista = (काष्ठा ath9k_htc_sta *)sta->drv_priv;
			अगर (__ath9k_htc_check_tx_aggr(priv, ista, tid)) अणु
				ieee80211_start_tx_ba_session(sta, tid, 0);
				spin_lock_bh(&priv->tx.tx_lock);
				ista->tid_state[tid] = AGGR_PROGRESS;
				spin_unlock_bh(&priv->tx.tx_lock);
			पूर्ण
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम ath9k_htc_tx_process(काष्ठा ath9k_htc_priv *priv,
				 काष्ठा sk_buff *skb,
				 काष्ठा __wmi_event_txstatus *txs)
अणु
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा ath9k_htc_tx_ctl *tx_ctl;
	काष्ठा ieee80211_tx_info *tx_info;
	काष्ठा ieee80211_tx_rate *rate;
	काष्ठा ieee80211_conf *cur_conf = &priv->hw->conf;
	bool txok;
	पूर्णांक slot;
	पूर्णांक hdrlen, padsize;

	slot = strip_drv_header(priv, skb);
	अगर (slot < 0) अणु
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	tx_ctl = HTC_SKB_CB(skb);
	txok = tx_ctl->txok;
	tx_info = IEEE80211_SKB_CB(skb);
	vअगर = tx_info->control.vअगर;
	rate = &tx_info->status.rates[0];

	स_रखो(&tx_info->status, 0, माप(tx_info->status));

	/*
	 * URB submission failed क्रम this frame, it never reached
	 * the target.
	 */
	अगर (!txok || !vअगर || !txs)
		जाओ send_mac80211;

	अगर (txs->ts_flags & ATH9K_HTC_TXSTAT_ACK) अणु
		tx_info->flags |= IEEE80211_TX_STAT_ACK;
		अगर (tx_info->flags & IEEE80211_TX_CTL_AMPDU)
			tx_info->flags |= IEEE80211_TX_STAT_AMPDU;
	पूर्ण

	अगर (txs->ts_flags & ATH9K_HTC_TXSTAT_FILT)
		tx_info->flags |= IEEE80211_TX_STAT_TX_FILTERED;

	अगर (txs->ts_flags & ATH9K_HTC_TXSTAT_RTC_CTS)
		rate->flags |= IEEE80211_TX_RC_USE_RTS_CTS;

	rate->count = 1;
	rate->idx = MS(txs->ts_rate, ATH9K_HTC_TXSTAT_RATE);

	अगर (txs->ts_flags & ATH9K_HTC_TXSTAT_MCS) अणु
		rate->flags |= IEEE80211_TX_RC_MCS;

		अगर (txs->ts_flags & ATH9K_HTC_TXSTAT_CW40)
			rate->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;
		अगर (txs->ts_flags & ATH9K_HTC_TXSTAT_SGI)
			rate->flags |= IEEE80211_TX_RC_SHORT_GI;
	पूर्ण अन्यथा अणु
		अगर (cur_conf->chandef.chan->band == NL80211_BAND_5GHZ)
			rate->idx += 4; /* No CCK rates */
	पूर्ण

	ath9k_htc_check_tx_aggr(priv, vअगर, skb);

send_mac80211:
	spin_lock_bh(&priv->tx.tx_lock);
	अगर (WARN_ON(--priv->tx.queued_cnt < 0))
		priv->tx.queued_cnt = 0;
	spin_unlock_bh(&priv->tx.tx_lock);

	ath9k_htc_tx_clear_slot(priv, slot);

	/* Remove padding beक्रमe handing frame back to mac80211 */
	hdrlen = ieee80211_get_hdrlen_from_skb(skb);

	padsize = hdrlen & 3;
	अगर (padsize && skb->len > hdrlen + padsize) अणु
		स_हटाओ(skb->data + padsize, skb->data, hdrlen);
		skb_pull(skb, padsize);
	पूर्ण

	/* Send status to mac80211 */
	ieee80211_tx_status(priv->hw, skb);
पूर्ण

अटल अंतरभूत व्योम ath9k_htc_tx_drainq(काष्ठा ath9k_htc_priv *priv,
				       काष्ठा sk_buff_head *queue)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(queue)) != शून्य) अणु
		ath9k_htc_tx_process(priv, skb, शून्य);
	पूर्ण
पूर्ण

व्योम ath9k_htc_tx_drain(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath9k_htc_tx_event *event, *पंचांगp;

	spin_lock_bh(&priv->tx.tx_lock);
	priv->tx.flags |= ATH9K_HTC_OP_TX_DRAIN;
	spin_unlock_bh(&priv->tx.tx_lock);

	/*
	 * Ensure that all pending TX frames are flushed,
	 * and that the TX completion/failed tasklets is समाप्तed.
	 */
	htc_stop(priv->htc);
	tasklet_समाप्त(&priv->wmi->wmi_event_tasklet);
	tasklet_समाप्त(&priv->tx_failed_tasklet);

	ath9k_htc_tx_drainq(priv, &priv->tx.mgmt_ep_queue);
	ath9k_htc_tx_drainq(priv, &priv->tx.cab_ep_queue);
	ath9k_htc_tx_drainq(priv, &priv->tx.data_be_queue);
	ath9k_htc_tx_drainq(priv, &priv->tx.data_bk_queue);
	ath9k_htc_tx_drainq(priv, &priv->tx.data_vi_queue);
	ath9k_htc_tx_drainq(priv, &priv->tx.data_vo_queue);
	ath9k_htc_tx_drainq(priv, &priv->tx.tx_failed);

	/*
	 * The TX cleanup समयr has alपढ़ोy been समाप्तed.
	 */
	spin_lock_bh(&priv->wmi->event_lock);
	list_क्रम_each_entry_safe(event, पंचांगp, &priv->wmi->pending_tx_events, list) अणु
		list_del(&event->list);
		kमुक्त(event);
	पूर्ण
	spin_unlock_bh(&priv->wmi->event_lock);

	spin_lock_bh(&priv->tx.tx_lock);
	priv->tx.flags &= ~ATH9K_HTC_OP_TX_DRAIN;
	spin_unlock_bh(&priv->tx.tx_lock);
पूर्ण

व्योम ath9k_tx_failed_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ath9k_htc_priv *priv = from_tasklet(priv, t, tx_failed_tasklet);

	spin_lock(&priv->tx.tx_lock);
	अगर (priv->tx.flags & ATH9K_HTC_OP_TX_DRAIN) अणु
		spin_unlock(&priv->tx.tx_lock);
		वापस;
	पूर्ण
	spin_unlock(&priv->tx.tx_lock);

	ath9k_htc_tx_drainq(priv, &priv->tx.tx_failed);
पूर्ण

अटल अंतरभूत bool check_cookie(काष्ठा ath9k_htc_priv *priv,
				काष्ठा sk_buff *skb,
				u8 cookie, u8 epid)
अणु
	u8 fcookie = 0;

	अगर (epid == priv->mgmt_ep) अणु
		काष्ठा tx_mgmt_hdr *hdr;
		hdr = (काष्ठा tx_mgmt_hdr *) skb->data;
		fcookie = hdr->cookie;
	पूर्ण अन्यथा अगर ((epid == priv->data_bk_ep) ||
		   (epid == priv->data_be_ep) ||
		   (epid == priv->data_vi_ep) ||
		   (epid == priv->data_vo_ep) ||
		   (epid == priv->cab_ep)) अणु
		काष्ठा tx_frame_hdr *hdr;
		hdr = (काष्ठा tx_frame_hdr *) skb->data;
		fcookie = hdr->cookie;
	पूर्ण

	अगर (fcookie == cookie)
		वापस true;

	वापस false;
पूर्ण

अटल काष्ठा sk_buff* ath9k_htc_tx_get_packet(काष्ठा ath9k_htc_priv *priv,
					       काष्ठा __wmi_event_txstatus *txs)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा sk_buff_head *epid_queue;
	काष्ठा sk_buff *skb, *पंचांगp;
	अचिन्हित दीर्घ flags;
	u8 epid = MS(txs->ts_rate, ATH9K_HTC_TXSTAT_EPID);

	epid_queue = get_htc_epid_queue(priv, epid);
	अगर (!epid_queue)
		वापस शून्य;

	spin_lock_irqsave(&epid_queue->lock, flags);
	skb_queue_walk_safe(epid_queue, skb, पंचांगp) अणु
		अगर (check_cookie(priv, skb, txs->cookie, epid)) अणु
			__skb_unlink(skb, epid_queue);
			spin_unlock_irqrestore(&epid_queue->lock, flags);
			वापस skb;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&epid_queue->lock, flags);

	ath_dbg(common, XMIT, "No matching packet for cookie: %d, epid: %d\n",
		txs->cookie, epid);

	वापस शून्य;
पूर्ण

व्योम ath9k_htc_txstatus(काष्ठा ath9k_htc_priv *priv, व्योम *wmi_event)
अणु
	काष्ठा wmi_event_txstatus *txs = wmi_event;
	काष्ठा __wmi_event_txstatus *__txs;
	काष्ठा sk_buff *skb;
	काष्ठा ath9k_htc_tx_event *tx_pend;
	पूर्णांक i;

	क्रम (i = 0; i < txs->cnt; i++) अणु
		WARN_ON(txs->cnt > HTC_MAX_TX_STATUS);

		__txs = &txs->txstatus[i];

		skb = ath9k_htc_tx_get_packet(priv, __txs);
		अगर (!skb) अणु
			/*
			 * Store this event, so that the TX cleanup
			 * routine can check later क्रम the needed packet.
			 */
			tx_pend = kzalloc(माप(काष्ठा ath9k_htc_tx_event),
					  GFP_ATOMIC);
			अगर (!tx_pend)
				जारी;

			स_नकल(&tx_pend->txs, __txs,
			       माप(काष्ठा __wmi_event_txstatus));

			spin_lock(&priv->wmi->event_lock);
			list_add_tail(&tx_pend->list,
				      &priv->wmi->pending_tx_events);
			spin_unlock(&priv->wmi->event_lock);

			जारी;
		पूर्ण

		ath9k_htc_tx_process(priv, skb, __txs);
	पूर्ण

	/* Wake TX queues अगर needed */
	ath9k_htc_check_wake_queues(priv);
पूर्ण

व्योम ath9k_htc_txep(व्योम *drv_priv, काष्ठा sk_buff *skb,
		    क्रमागत htc_endpoपूर्णांक_id ep_id, bool txok)
अणु
	काष्ठा ath9k_htc_priv *priv = drv_priv;
	काष्ठा ath9k_htc_tx_ctl *tx_ctl;
	काष्ठा sk_buff_head *epid_queue;

	tx_ctl = HTC_SKB_CB(skb);
	tx_ctl->txok = txok;
	tx_ctl->बारtamp = jअगरfies;

	अगर (!txok) अणु
		skb_queue_tail(&priv->tx.tx_failed, skb);
		tasklet_schedule(&priv->tx_failed_tasklet);
		वापस;
	पूर्ण

	epid_queue = get_htc_epid_queue(priv, ep_id);
	अगर (!epid_queue) अणु
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	skb_queue_tail(epid_queue, skb);
पूर्ण

अटल अंतरभूत bool check_packet(काष्ठा ath9k_htc_priv *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath9k_htc_tx_ctl *tx_ctl;

	tx_ctl = HTC_SKB_CB(skb);

	अगर (समय_after(jअगरfies,
		       tx_ctl->बारtamp +
		       msecs_to_jअगरfies(ATH9K_HTC_TX_TIMEOUT_INTERVAL))) अणु
		ath_dbg(common, XMIT, "Dropping a packet due to TX timeout\n");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम ath9k_htc_tx_cleanup_queue(काष्ठा ath9k_htc_priv *priv,
				       काष्ठा sk_buff_head *epid_queue)
अणु
	bool process = false;
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *skb, *पंचांगp;
	काष्ठा sk_buff_head queue;

	skb_queue_head_init(&queue);

	spin_lock_irqsave(&epid_queue->lock, flags);
	skb_queue_walk_safe(epid_queue, skb, पंचांगp) अणु
		अगर (check_packet(priv, skb)) अणु
			__skb_unlink(skb, epid_queue);
			__skb_queue_tail(&queue, skb);
			process = true;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&epid_queue->lock, flags);

	अगर (process) अणु
		skb_queue_walk_safe(&queue, skb, पंचांगp) अणु
			__skb_unlink(skb, &queue);
			ath9k_htc_tx_process(priv, skb, शून्य);
		पूर्ण
	पूर्ण
पूर्ण

व्योम ath9k_htc_tx_cleanup_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ath9k_htc_priv *priv = from_समयr(priv, t, tx.cleanup_समयr);
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath9k_htc_tx_event *event, *पंचांगp;
	काष्ठा sk_buff *skb;

	spin_lock(&priv->wmi->event_lock);
	list_क्रम_each_entry_safe(event, पंचांगp, &priv->wmi->pending_tx_events, list) अणु

		skb = ath9k_htc_tx_get_packet(priv, &event->txs);
		अगर (skb) अणु
			ath_dbg(common, XMIT,
				"Found packet for cookie: %d, epid: %d\n",
				event->txs.cookie,
				MS(event->txs.ts_rate, ATH9K_HTC_TXSTAT_EPID));

			ath9k_htc_tx_process(priv, skb, &event->txs);
			list_del(&event->list);
			kमुक्त(event);
			जारी;
		पूर्ण

		अगर (++event->count >= ATH9K_HTC_TX_TIMEOUT_COUNT) अणु
			list_del(&event->list);
			kमुक्त(event);
		पूर्ण
	पूर्ण
	spin_unlock(&priv->wmi->event_lock);

	/*
	 * Check अगर status-pending packets have to be cleaned up.
	 */
	ath9k_htc_tx_cleanup_queue(priv, &priv->tx.mgmt_ep_queue);
	ath9k_htc_tx_cleanup_queue(priv, &priv->tx.cab_ep_queue);
	ath9k_htc_tx_cleanup_queue(priv, &priv->tx.data_be_queue);
	ath9k_htc_tx_cleanup_queue(priv, &priv->tx.data_bk_queue);
	ath9k_htc_tx_cleanup_queue(priv, &priv->tx.data_vi_queue);
	ath9k_htc_tx_cleanup_queue(priv, &priv->tx.data_vo_queue);

	/* Wake TX queues अगर needed */
	ath9k_htc_check_wake_queues(priv);

	mod_समयr(&priv->tx.cleanup_समयr,
		  jअगरfies + msecs_to_jअगरfies(ATH9K_HTC_TX_CLEANUP_INTERVAL));
पूर्ण

पूर्णांक ath9k_tx_init(काष्ठा ath9k_htc_priv *priv)
अणु
	skb_queue_head_init(&priv->tx.mgmt_ep_queue);
	skb_queue_head_init(&priv->tx.cab_ep_queue);
	skb_queue_head_init(&priv->tx.data_be_queue);
	skb_queue_head_init(&priv->tx.data_bk_queue);
	skb_queue_head_init(&priv->tx.data_vi_queue);
	skb_queue_head_init(&priv->tx.data_vo_queue);
	skb_queue_head_init(&priv->tx.tx_failed);
	वापस 0;
पूर्ण

व्योम ath9k_tx_cleanup(काष्ठा ath9k_htc_priv *priv)
अणु

पूर्ण

bool ath9k_htc_txq_setup(काष्ठा ath9k_htc_priv *priv, पूर्णांक subtype)
अणु
	काष्ठा ath_hw *ah = priv->ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_tx_queue_info qi;
	पूर्णांक qnum;

	स_रखो(&qi, 0, माप(qi));
	ATH9K_HTC_INIT_TXQ(subtype);

	qnum = ath9k_hw_setuptxqueue(priv->ah, ATH9K_TX_QUEUE_DATA, &qi);
	अगर (qnum == -1)
		वापस false;

	अगर (qnum >= ARRAY_SIZE(priv->hwq_map)) अणु
		ath_err(common, "qnum %u out of range, max %zu!\n",
			qnum, ARRAY_SIZE(priv->hwq_map));
		ath9k_hw_releasetxqueue(ah, qnum);
		वापस false;
	पूर्ण

	priv->hwq_map[subtype] = qnum;
	वापस true;
पूर्ण

पूर्णांक ath9k_htc_cabq_setup(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath9k_tx_queue_info qi;

	स_रखो(&qi, 0, माप(qi));
	ATH9K_HTC_INIT_TXQ(0);

	वापस ath9k_hw_setuptxqueue(priv->ah, ATH9K_TX_QUEUE_CAB, &qi);
पूर्ण

/******/
/* RX */
/******/

/*
 * Calculate the RX filter to be set in the HW.
 */
u32 ath9k_htc_calcrxfilter(काष्ठा ath9k_htc_priv *priv)
अणु
#घोषणा	RX_FILTER_PRESERVE (ATH9K_RX_FILTER_PHYERR | ATH9K_RX_FILTER_PHYRADAR)

	काष्ठा ath_hw *ah = priv->ah;
	u32 rfilt;

	rfilt = (ath9k_hw_getrxfilter(ah) & RX_FILTER_PRESERVE)
		| ATH9K_RX_FILTER_UCAST | ATH9K_RX_FILTER_BCAST
		| ATH9K_RX_FILTER_MCAST;

	अगर (priv->rxfilter & FIF_PROBE_REQ)
		rfilt |= ATH9K_RX_FILTER_PROBEREQ;

	अगर (ah->is_monitoring)
		rfilt |= ATH9K_RX_FILTER_PROM;

	अगर (priv->rxfilter & FIF_CONTROL)
		rfilt |= ATH9K_RX_FILTER_CONTROL;

	अगर ((ah->opmode == NL80211_IFTYPE_STATION) &&
	    (priv->nvअगरs <= 1) &&
	    !(priv->rxfilter & FIF_BCN_PRBRESP_PROMISC))
		rfilt |= ATH9K_RX_FILTER_MYBEACON;
	अन्यथा
		rfilt |= ATH9K_RX_FILTER_BEACON;

	अगर (conf_is_ht(&priv->hw->conf)) अणु
		rfilt |= ATH9K_RX_FILTER_COMP_BAR;
		rfilt |= ATH9K_RX_FILTER_UNCOMP_BA_BAR;
	पूर्ण

	अगर (priv->rxfilter & FIF_PSPOLL)
		rfilt |= ATH9K_RX_FILTER_PSPOLL;

	अगर (priv->nvअगरs > 1 ||
	    priv->rxfilter & (FIF_OTHER_BSS | FIF_MCAST_ACTION))
		rfilt |= ATH9K_RX_FILTER_MCAST_BCAST_ALL;

	वापस rfilt;

#अघोषित RX_FILTER_PRESERVE
पूर्ण

/*
 * Recv initialization क्रम opmode change.
 */
अटल व्योम ath9k_htc_opmode_init(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath_hw *ah = priv->ah;
	u32 rfilt, mfilt[2];

	/* configure rx filter */
	rfilt = ath9k_htc_calcrxfilter(priv);
	ath9k_hw_setrxfilter(ah, rfilt);

	/* calculate and install multicast filter */
	mfilt[0] = mfilt[1] = ~0;
	ath9k_hw_seपंचांगcastfilter(ah, mfilt[0], mfilt[1]);
पूर्ण

व्योम ath9k_host_rx_init(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	ath9k_hw_rxena(priv->ah);
	ath9k_htc_opmode_init(priv);
	ath9k_hw_startpcureceive(priv->ah, test_bit(ATH_OP_SCANNING, &common->op_flags));
पूर्ण

अटल अंतरभूत व्योम convert_htc_flag(काष्ठा ath_rx_status *rx_stats,
				   काष्ठा ath_htc_rx_status *rxstatus)
अणु
	rx_stats->enc_flags = 0;
	rx_stats->bw = RATE_INFO_BW_20;
	अगर (rxstatus->rs_flags & ATH9K_RX_2040)
		rx_stats->bw = RATE_INFO_BW_40;
	अगर (rxstatus->rs_flags & ATH9K_RX_GI)
		rx_stats->enc_flags |= RX_ENC_FLAG_SHORT_GI;
पूर्ण

अटल व्योम rx_status_htc_to_ath(काष्ठा ath_rx_status *rx_stats,
				 काष्ठा ath_htc_rx_status *rxstatus)
अणु
	rx_stats->rs_datalen	= be16_to_cpu(rxstatus->rs_datalen);
	rx_stats->rs_status	= rxstatus->rs_status;
	rx_stats->rs_phyerr	= rxstatus->rs_phyerr;
	rx_stats->rs_rssi	= rxstatus->rs_rssi;
	rx_stats->rs_keyix	= rxstatus->rs_keyix;
	rx_stats->rs_rate	= rxstatus->rs_rate;
	rx_stats->rs_antenna	= rxstatus->rs_antenna;
	rx_stats->rs_more	= rxstatus->rs_more;

	स_नकल(rx_stats->rs_rssi_ctl, rxstatus->rs_rssi_ctl,
		माप(rx_stats->rs_rssi_ctl));
	स_नकल(rx_stats->rs_rssi_ext, rxstatus->rs_rssi_ext,
		माप(rx_stats->rs_rssi_ext));

	rx_stats->rs_isaggr	= rxstatus->rs_isaggr;
	rx_stats->rs_moreaggr	= rxstatus->rs_moreaggr;
	rx_stats->rs_num_delims	= rxstatus->rs_num_delims;
	convert_htc_flag(rx_stats, rxstatus);
पूर्ण

अटल bool ath9k_rx_prepare(काष्ठा ath9k_htc_priv *priv,
			     काष्ठा ath9k_htc_rxbuf *rxbuf,
			     काष्ठा ieee80211_rx_status *rx_status)

अणु
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ieee80211_hw *hw = priv->hw;
	काष्ठा sk_buff *skb = rxbuf->skb;
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath_hw *ah = common->ah;
	काष्ठा ath_htc_rx_status *rxstatus;
	काष्ठा ath_rx_status rx_stats;
	bool decrypt_error = false;
	u16 rs_datalen;
	bool is_phyerr;

	अगर (skb->len < HTC_RX_FRAME_HEADER_SIZE) अणु
		ath_err(common, "Corrupted RX frame, dropping (len: %d)\n",
			skb->len);
		जाओ rx_next;
	पूर्ण

	rxstatus = (काष्ठा ath_htc_rx_status *)skb->data;

	rs_datalen = be16_to_cpu(rxstatus->rs_datalen);
	अगर (unlikely(rs_datalen -
	    (skb->len - HTC_RX_FRAME_HEADER_SIZE) != 0)) अणु
		ath_err(common,
			"Corrupted RX data len, dropping (dlen: %d, skblen: %d)\n",
			rs_datalen, skb->len);
		जाओ rx_next;
	पूर्ण

	is_phyerr = rxstatus->rs_status & ATH9K_RXERR_PHY;
	/*
	 * Discard zero-length packets and packets smaller than an ACK
	 * which are not PHY_ERROR (लघु radar pulses have a length of 3)
	 */
	अगर (unlikely(!rs_datalen || (rs_datalen < 10 && !is_phyerr))) अणु
		ath_dbg(common, ANY,
			"Short RX data len, dropping (dlen: %d)\n",
			rs_datalen);
		जाओ rx_next;
	पूर्ण

	/* Get the RX status inक्रमmation */

	स_रखो(rx_status, 0, माप(काष्ठा ieee80211_rx_status));

	/* Copy everything from ath_htc_rx_status (HTC_RX_FRAME_HEADER).
	 * After this, we can drop this part of skb. */
	rx_status_htc_to_ath(&rx_stats, rxstatus);
	ath9k_htc_err_stat_rx(priv, &rx_stats);
	rx_status->maस_समय = be64_to_cpu(rxstatus->rs_tstamp);
	skb_pull(skb, HTC_RX_FRAME_HEADER_SIZE);

	/*
	 * everything but the rate is checked here, the rate check is करोne
	 * separately to aव्योम करोing two lookups क्रम a rate क्रम each frame.
	 */
	hdr = (काष्ठा ieee80211_hdr *)skb->data;

	/*
	 * Process PHY errors and वापस so that the packet
	 * can be dropped.
	 */
	अगर (unlikely(is_phyerr)) अणु
		/* TODO: Not using DFS processing now. */
		अगर (ath_cmn_process_fft(&priv->spec_priv, hdr,
				    &rx_stats, rx_status->maस_समय)) अणु
			/* TODO: Code to collect spectral scan statistics */
		पूर्ण
		जाओ rx_next;
	पूर्ण

	अगर (!ath9k_cmn_rx_accept(common, hdr, rx_status, &rx_stats,
			&decrypt_error, priv->rxfilter))
		जाओ rx_next;

	ath9k_cmn_rx_skb_postprocess(common, skb, &rx_stats,
				     rx_status, decrypt_error);

	अगर (ath9k_cmn_process_rate(common, hw, &rx_stats, rx_status))
		जाओ rx_next;

	rx_stats.is_mybeacon = ath_is_mybeacon(common, hdr);
	ath9k_cmn_process_rssi(common, hw, &rx_stats, rx_status);

	rx_status->band = ah->curchan->chan->band;
	rx_status->freq = ah->curchan->chan->center_freq;
	rx_status->antenna = rx_stats.rs_antenna;
	rx_status->flag |= RX_FLAG_MACTIME_END;

	वापस true;
rx_next:
	वापस false;
पूर्ण

/*
 * FIXME: Handle FLUSH later on.
 */
व्योम ath9k_rx_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ath9k_htc_priv *priv = from_tasklet(priv, t, rx_tasklet);
	काष्ठा ath9k_htc_rxbuf *rxbuf = शून्य, *पंचांगp_buf = शून्य;
	काष्ठा ieee80211_rx_status rx_status;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	काष्ठा ieee80211_hdr *hdr;

	करो अणु
		spin_lock_irqsave(&priv->rx.rxbuflock, flags);
		list_क्रम_each_entry(पंचांगp_buf, &priv->rx.rxbuf, list) अणु
			अगर (पंचांगp_buf->in_process) अणु
				rxbuf = पंचांगp_buf;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (rxbuf == शून्य) अणु
			spin_unlock_irqrestore(&priv->rx.rxbuflock, flags);
			अवरोध;
		पूर्ण

		अगर (!rxbuf->skb)
			जाओ requeue;

		अगर (!ath9k_rx_prepare(priv, rxbuf, &rx_status)) अणु
			dev_kमुक्त_skb_any(rxbuf->skb);
			जाओ requeue;
		पूर्ण

		स_नकल(IEEE80211_SKB_RXCB(rxbuf->skb), &rx_status,
		       माप(काष्ठा ieee80211_rx_status));
		skb = rxbuf->skb;
		hdr = (काष्ठा ieee80211_hdr *) skb->data;

		अगर (ieee80211_is_beacon(hdr->frame_control) && priv->ps_enabled)
				ieee80211_queue_work(priv->hw, &priv->ps_work);

		spin_unlock_irqrestore(&priv->rx.rxbuflock, flags);

		ieee80211_rx(priv->hw, skb);

		spin_lock_irqsave(&priv->rx.rxbuflock, flags);
requeue:
		rxbuf->in_process = false;
		rxbuf->skb = शून्य;
		list_move_tail(&rxbuf->list, &priv->rx.rxbuf);
		rxbuf = शून्य;
		spin_unlock_irqrestore(&priv->rx.rxbuflock, flags);
	पूर्ण जबतक (1);

पूर्ण

व्योम ath9k_htc_rxep(व्योम *drv_priv, काष्ठा sk_buff *skb,
		    क्रमागत htc_endpoपूर्णांक_id ep_id)
अणु
	काष्ठा ath9k_htc_priv *priv = drv_priv;
	काष्ठा ath_hw *ah = priv->ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_htc_rxbuf *rxbuf = शून्य, *पंचांगp_buf = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->rx.rxbuflock, flags);
	list_क्रम_each_entry(पंचांगp_buf, &priv->rx.rxbuf, list) अणु
		अगर (!पंचांगp_buf->in_process) अणु
			rxbuf = पंचांगp_buf;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&priv->rx.rxbuflock, flags);

	अगर (rxbuf == शून्य) अणु
		ath_dbg(common, ANY, "No free RX buffer\n");
		जाओ err;
	पूर्ण

	spin_lock_irqsave(&priv->rx.rxbuflock, flags);
	rxbuf->skb = skb;
	rxbuf->in_process = true;
	spin_unlock_irqrestore(&priv->rx.rxbuflock, flags);

	tasklet_schedule(&priv->rx_tasklet);
	वापस;
err:
	dev_kमुक्त_skb_any(skb);
पूर्ण

/* FIXME: Locking क्रम cleanup/init */

व्योम ath9k_rx_cleanup(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath9k_htc_rxbuf *rxbuf, *tbuf;

	list_क्रम_each_entry_safe(rxbuf, tbuf, &priv->rx.rxbuf, list) अणु
		list_del(&rxbuf->list);
		अगर (rxbuf->skb)
			dev_kमुक्त_skb_any(rxbuf->skb);
		kमुक्त(rxbuf);
	पूर्ण
पूर्ण

पूर्णांक ath9k_rx_init(काष्ठा ath9k_htc_priv *priv)
अणु
	पूर्णांक i = 0;

	INIT_LIST_HEAD(&priv->rx.rxbuf);
	spin_lock_init(&priv->rx.rxbuflock);

	क्रम (i = 0; i < ATH9K_HTC_RXBUF; i++) अणु
		काष्ठा ath9k_htc_rxbuf *rxbuf =
			kzalloc(माप(काष्ठा ath9k_htc_rxbuf), GFP_KERNEL);
		अगर (rxbuf == शून्य)
			जाओ err;

		list_add_tail(&rxbuf->list, &priv->rx.rxbuf);
	पूर्ण

	वापस 0;

err:
	ath9k_rx_cleanup(priv);
	वापस -ENOMEM;
पूर्ण
