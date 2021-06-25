<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */

#समावेश "wil6210.h"
#समावेश "txrx.h"

#घोषणा SEQ_MODULO 0x1000
#घोषणा SEQ_MASK   0xfff

अटल अंतरभूत पूर्णांक seq_less(u16 sq1, u16 sq2)
अणु
	वापस ((sq1 - sq2) & SEQ_MASK) > (SEQ_MODULO >> 1);
पूर्ण

अटल अंतरभूत u16 seq_inc(u16 sq)
अणु
	वापस (sq + 1) & SEQ_MASK;
पूर्ण

अटल अंतरभूत u16 seq_sub(u16 sq1, u16 sq2)
अणु
	वापस (sq1 - sq2) & SEQ_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक reorder_index(काष्ठा wil_tid_ampdu_rx *r, u16 seq)
अणु
	वापस seq_sub(seq, r->ssn) % r->buf_size;
पूर्ण

अटल व्योम wil_release_reorder_frame(काष्ठा net_device *ndev,
				      काष्ठा wil_tid_ampdu_rx *r,
				      पूर्णांक index)
अणु
	काष्ठा sk_buff *skb = r->reorder_buf[index];

	अगर (!skb)
		जाओ no_frame;

	/* release the frame from the reorder ring buffer */
	r->stored_mpdu_num--;
	r->reorder_buf[index] = शून्य;
	wil_netअगर_rx_any(skb, ndev);

no_frame:
	r->head_seq_num = seq_inc(r->head_seq_num);
पूर्ण

अटल व्योम wil_release_reorder_frames(काष्ठा net_device *ndev,
				       काष्ठा wil_tid_ampdu_rx *r,
				       u16 hseq)
अणु
	पूर्णांक index;

	/* note: this function is never called with
	 * hseq preceding r->head_seq_num, i.e it is always true
	 * !seq_less(hseq, r->head_seq_num)
	 * and thus on loop निकास it should be
	 * r->head_seq_num == hseq
	 */
	जबतक (seq_less(r->head_seq_num, hseq) && r->stored_mpdu_num) अणु
		index = reorder_index(r, r->head_seq_num);
		wil_release_reorder_frame(ndev, r, index);
	पूर्ण
	r->head_seq_num = hseq;
पूर्ण

अटल व्योम wil_reorder_release(काष्ठा net_device *ndev,
				काष्ठा wil_tid_ampdu_rx *r)
अणु
	पूर्णांक index = reorder_index(r, r->head_seq_num);

	जबतक (r->reorder_buf[index]) अणु
		wil_release_reorder_frame(ndev, r, index);
		index = reorder_index(r, r->head_seq_num);
	पूर्ण
पूर्ण

/* called in NAPI context */
व्योम wil_rx_reorder(काष्ठा wil6210_priv *wil, काष्ठा sk_buff *skb)
__acquires(&sta->tid_rx_lock) __releases(&sta->tid_rx_lock)
अणु
	काष्ठा wil6210_vअगर *vअगर;
	काष्ठा net_device *ndev;
	पूर्णांक tid, cid, mid, mcast, retry;
	u16 seq;
	काष्ठा wil_sta_info *sta;
	काष्ठा wil_tid_ampdu_rx *r;
	u16 hseq;
	पूर्णांक index;

	wil->txrx_ops.get_reorder_params(wil, skb, &tid, &cid, &mid, &seq,
					 &mcast, &retry);
	sta = &wil->sta[cid];

	wil_dbg_txrx(wil, "MID %d CID %d TID %d Seq 0x%03x mcast %01x\n",
		     mid, cid, tid, seq, mcast);

	vअगर = wil->vअगरs[mid];
	अगर (unlikely(!vअगर)) अणु
		wil_dbg_txrx(wil, "invalid VIF, mid %d\n", mid);
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण
	ndev = vअगर_to_ndev(vअगर);

	spin_lock(&sta->tid_rx_lock);

	r = sta->tid_rx[tid];
	अगर (!r) अणु
		wil_netअगर_rx_any(skb, ndev);
		जाओ out;
	पूर्ण

	अगर (unlikely(mcast)) अणु
		अगर (retry && seq == r->mcast_last_seq) अणु
			r->drop_dup_mcast++;
			wil_dbg_txrx(wil, "Rx drop: dup mcast seq 0x%03x\n",
				     seq);
			dev_kमुक्त_skb(skb);
			जाओ out;
		पूर्ण
		r->mcast_last_seq = seq;
		wil_netअगर_rx_any(skb, ndev);
		जाओ out;
	पूर्ण

	r->total++;
	hseq = r->head_seq_num;

	/** Due to the race between WMI events, where BACK establishment
	 * reported, and data Rx, few packets may be pass up beक्रमe reorder
	 * buffer get allocated. Catch up by pretending SSN is what we
	 * see in the 1-st Rx packet
	 *
	 * Another scenario, Rx get delayed and we got packet from beक्रमe
	 * BACK. Pass it to the stack and रुको.
	 */
	अगर (r->first_समय) अणु
		r->first_समय = false;
		अगर (seq != r->head_seq_num) अणु
			अगर (seq_less(seq, r->head_seq_num)) अणु
				wil_err(wil,
					"Error: frame with early sequence 0x%03x, should be 0x%03x. Waiting...\n",
					seq, r->head_seq_num);
				r->first_समय = true;
				wil_netअगर_rx_any(skb, ndev);
				जाओ out;
			पूर्ण
			wil_err(wil,
				"Error: 1-st frame with wrong sequence 0x%03x, should be 0x%03x. Fixing...\n",
				seq, r->head_seq_num);
			r->head_seq_num = seq;
			r->ssn = seq;
		पूर्ण
	पूर्ण

	/* frame with out of date sequence number */
	अगर (seq_less(seq, r->head_seq_num)) अणु
		r->ssn_last_drop = seq;
		r->drop_old++;
		wil_dbg_txrx(wil, "Rx drop: old seq 0x%03x head 0x%03x\n",
			     seq, r->head_seq_num);
		dev_kमुक्त_skb(skb);
		जाओ out;
	पूर्ण

	/*
	 * If frame the sequence number exceeds our buffering winकरोw
	 * size release some previous frames to make room क्रम this one.
	 */
	अगर (!seq_less(seq, r->head_seq_num + r->buf_size)) अणु
		hseq = seq_inc(seq_sub(seq, r->buf_size));
		/* release stored frames up to new head to stack */
		wil_release_reorder_frames(ndev, r, hseq);
	पूर्ण

	/* Now the new frame is always in the range of the reordering buffer */

	index = reorder_index(r, seq);

	/* check अगर we alपढ़ोy stored this frame */
	अगर (r->reorder_buf[index]) अणु
		r->drop_dup++;
		wil_dbg_txrx(wil, "Rx drop: dup seq 0x%03x\n", seq);
		dev_kमुक्त_skb(skb);
		जाओ out;
	पूर्ण

	/*
	 * If the current MPDU is in the right order and nothing अन्यथा
	 * is stored we can process it directly, no need to buffer it.
	 * If it is first but there's something stored, we may be able
	 * to release frames after this one.
	 */
	अगर (seq == r->head_seq_num && r->stored_mpdu_num == 0) अणु
		r->head_seq_num = seq_inc(r->head_seq_num);
		wil_netअगर_rx_any(skb, ndev);
		जाओ out;
	पूर्ण

	/* put the frame in the reordering buffer */
	r->reorder_buf[index] = skb;
	r->stored_mpdu_num++;
	wil_reorder_release(ndev, r);

out:
	spin_unlock(&sta->tid_rx_lock);
पूर्ण

/* process BAR frame, called in NAPI context */
व्योम wil_rx_bar(काष्ठा wil6210_priv *wil, काष्ठा wil6210_vअगर *vअगर,
		u8 cid, u8 tid, u16 seq)
अणु
	काष्ठा wil_sta_info *sta = &wil->sta[cid];
	काष्ठा net_device *ndev = vअगर_to_ndev(vअगर);
	काष्ठा wil_tid_ampdu_rx *r;

	spin_lock(&sta->tid_rx_lock);

	r = sta->tid_rx[tid];
	अगर (!r) अणु
		wil_err(wil, "BAR for non-existing CID %d TID %d\n", cid, tid);
		जाओ out;
	पूर्ण
	अगर (seq_less(seq, r->head_seq_num)) अणु
		wil_err(wil, "BAR Seq 0x%03x preceding head 0x%03x\n",
			seq, r->head_seq_num);
		जाओ out;
	पूर्ण
	wil_dbg_txrx(wil, "BAR: CID %d MID %d TID %d Seq 0x%03x head 0x%03x\n",
		     cid, vअगर->mid, tid, seq, r->head_seq_num);
	wil_release_reorder_frames(ndev, r, seq);

out:
	spin_unlock(&sta->tid_rx_lock);
पूर्ण

काष्ठा wil_tid_ampdu_rx *wil_tid_ampdu_rx_alloc(काष्ठा wil6210_priv *wil,
						पूर्णांक size, u16 ssn)
अणु
	काष्ठा wil_tid_ampdu_rx *r = kzalloc(माप(*r), GFP_KERNEL);

	अगर (!r)
		वापस शून्य;

	r->reorder_buf =
		kसुस्मृति(size, माप(काष्ठा sk_buff *), GFP_KERNEL);
	अगर (!r->reorder_buf) अणु
		kमुक्त(r);
		वापस शून्य;
	पूर्ण

	r->ssn = ssn;
	r->head_seq_num = ssn;
	r->buf_size = size;
	r->stored_mpdu_num = 0;
	r->first_समय = true;
	r->mcast_last_seq = U16_MAX;
	वापस r;
पूर्ण

व्योम wil_tid_ampdu_rx_मुक्त(काष्ठा wil6210_priv *wil,
			   काष्ठा wil_tid_ampdu_rx *r)
अणु
	पूर्णांक i;

	अगर (!r)
		वापस;

	/* Do not pass reमुख्यing frames to the network stack - it may be
	 * not expecting to get any more Rx. Rx from here may lead to
	 * kernel OOPS since some per-socket accounting info was alपढ़ोy
	 * released.
	 */
	क्रम (i = 0; i < r->buf_size; i++)
		kमुक्त_skb(r->reorder_buf[i]);

	kमुक्त(r->reorder_buf);
	kमुक्त(r);
पूर्ण

/* ADDBA processing */
अटल u16 wil_agg_size(काष्ठा wil6210_priv *wil, u16 req_agg_wsize)
अणु
	u16 max_agg_size = min_t(u16, wil->max_agg_wsize, wil->max_ampdu_size /
				 (mtu_max + WIL_MAX_MPDU_OVERHEAD));

	अगर (!req_agg_wsize)
		वापस max_agg_size;

	वापस min(max_agg_size, req_agg_wsize);
पूर्ण

/* Block Ack - Rx side (recipient) */
पूर्णांक wil_addba_rx_request(काष्ठा wil6210_priv *wil, u8 mid, u8 cid, u8 tid,
			 u8 dialog_token, __le16 ba_param_set,
			 __le16 ba_समयout, __le16 ba_seq_ctrl)
__acquires(&sta->tid_rx_lock) __releases(&sta->tid_rx_lock)
अणु
	u16 param_set = le16_to_cpu(ba_param_set);
	u16 agg_समयout = le16_to_cpu(ba_समयout);
	u16 seq_ctrl = le16_to_cpu(ba_seq_ctrl);
	काष्ठा wil_sta_info *sta;
	u16 agg_wsize;
	/* bit 0: A-MSDU supported
	 * bit 1: policy (should be 0 क्रम us)
	 * bits 2..5: TID
	 * bits 6..15: buffer size
	 */
	u16 req_agg_wsize = WIL_GET_BITS(param_set, 6, 15);
	bool agg_amsdu = wil->use_enhanced_dma_hw &&
		wil->use_rx_hw_reordering &&
		test_bit(WMI_FW_CAPABILITY_AMSDU, wil->fw_capabilities) &&
		wil->amsdu_en && (param_set & BIT(0));
	पूर्णांक ba_policy = param_set & BIT(1);
	u16 ssn = seq_ctrl >> 4;
	काष्ठा wil_tid_ampdu_rx *r;
	पूर्णांक rc = 0;

	might_sleep();

	/* sanity checks */
	अगर (cid >= wil->max_assoc_sta) अणु
		wil_err(wil, "BACK: invalid CID %d\n", cid);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	sta = &wil->sta[cid];
	अगर (sta->status != wil_sta_connected) अणु
		wil_err(wil, "BACK: CID %d not connected\n", cid);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	wil_dbg_wmi(wil,
		    "ADDBA request for CID %d %pM TID %d size %d timeout %d AMSDU%s policy %d token %d SSN 0x%03x\n",
		    cid, sta->addr, tid, req_agg_wsize, agg_समयout,
		    agg_amsdu ? "+" : "-", !!ba_policy, dialog_token, ssn);

	/* apply policies */
	अगर (req_agg_wsize == 0) अणु
		wil_dbg_misc(wil, "Suggest BACK wsize %d\n",
			     wil->max_agg_wsize);
		agg_wsize = wil->max_agg_wsize;
	पूर्ण अन्यथा अणु
		agg_wsize = min_t(u16, wil->max_agg_wsize, req_agg_wsize);
	पूर्ण

	rc = wil->txrx_ops.wmi_addba_rx_resp(wil, mid, cid, tid, dialog_token,
					     WLAN_STATUS_SUCCESS, agg_amsdu,
					     agg_wsize, agg_समयout);
	अगर (rc) अणु
		wil_err(wil, "do not apply ba, rc(%d)\n", rc);
		जाओ out;
	पूर्ण

	/* apply */
	अगर (!wil->use_rx_hw_reordering) अणु
		r = wil_tid_ampdu_rx_alloc(wil, agg_wsize, ssn);
		spin_lock_bh(&sta->tid_rx_lock);
		wil_tid_ampdu_rx_मुक्त(wil, sta->tid_rx[tid]);
		sta->tid_rx[tid] = r;
		spin_unlock_bh(&sta->tid_rx_lock);
	पूर्ण

out:
	वापस rc;
पूर्ण

/* BACK - Tx side (originator) */
पूर्णांक wil_addba_tx_request(काष्ठा wil6210_priv *wil, u8 ringid, u16 wsize)
अणु
	u8 agg_wsize = wil_agg_size(wil, wsize);
	u16 agg_समयout = 0;
	काष्ठा wil_ring_tx_data *txdata = &wil->ring_tx_data[ringid];
	पूर्णांक rc = 0;

	अगर (txdata->addba_in_progress) अणु
		wil_dbg_misc(wil, "ADDBA for vring[%d] already in progress\n",
			     ringid);
		जाओ out;
	पूर्ण
	अगर (txdata->agg_wsize) अणु
		wil_dbg_misc(wil,
			     "ADDBA for vring[%d] already done for wsize %d\n",
			     ringid, txdata->agg_wsize);
		जाओ out;
	पूर्ण
	txdata->addba_in_progress = true;
	rc = wmi_addba(wil, txdata->mid, ringid, agg_wsize, agg_समयout);
	अगर (rc) अणु
		wil_err(wil, "wmi_addba failed, rc (%d)", rc);
		txdata->addba_in_progress = false;
	पूर्ण

out:
	वापस rc;
पूर्ण
