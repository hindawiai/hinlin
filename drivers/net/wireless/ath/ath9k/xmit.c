<शैली गुरु>
/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
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

#समावेश <linux/dma-mapping.h>
#समावेश "ath9k.h"
#समावेश "ar9003_mac.h"

#घोषणा BITS_PER_BYTE           8
#घोषणा OFDM_PLCP_BITS          22
#घोषणा HT_RC_2_STREAMS(_rc)    ((((_rc) & 0x78) >> 3) + 1)
#घोषणा L_STF                   8
#घोषणा L_LTF                   8
#घोषणा L_SIG                   4
#घोषणा HT_SIG                  8
#घोषणा HT_STF                  4
#घोषणा HT_LTF(_ns)             (4 * (_ns))
#घोषणा SYMBOL_TIME(_ns)        ((_ns) << 2) /* ns * 4 us */
#घोषणा SYMBOL_TIME_HALFGI(_ns) (((_ns) * 18 + 4) / 5)  /* ns * 3.6 us */
#घोषणा TIME_SYMBOLS(t)         ((t) >> 2)
#घोषणा TIME_SYMBOLS_HALFGI(t)  (((t) * 5 - 4) / 18)
#घोषणा NUM_SYMBOLS_PER_USEC(_usec) (_usec >> 2)
#घोषणा NUM_SYMBOLS_PER_USEC_HALFGI(_usec) (((_usec*5)-4)/18)


अटल u16 bits_per_symbol[][2] = अणु
	/* 20MHz 40MHz */
	अणु    26,   54 पूर्ण,     /*  0: BPSK */
	अणु    52,  108 पूर्ण,     /*  1: QPSK 1/2 */
	अणु    78,  162 पूर्ण,     /*  2: QPSK 3/4 */
	अणु   104,  216 पूर्ण,     /*  3: 16-QAM 1/2 */
	अणु   156,  324 पूर्ण,     /*  4: 16-QAM 3/4 */
	अणु   208,  432 पूर्ण,     /*  5: 64-QAM 2/3 */
	अणु   234,  486 पूर्ण,     /*  6: 64-QAM 3/4 */
	अणु   260,  540 पूर्ण,     /*  7: 64-QAM 5/6 */
पूर्ण;

अटल व्योम ath_tx_send_normal(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq,
			       काष्ठा ath_atx_tid *tid, काष्ठा sk_buff *skb);
अटल व्योम ath_tx_complete(काष्ठा ath_softc *sc, काष्ठा sk_buff *skb,
			    पूर्णांक tx_flags, काष्ठा ath_txq *txq,
			    काष्ठा ieee80211_sta *sta);
अटल व्योम ath_tx_complete_buf(काष्ठा ath_softc *sc, काष्ठा ath_buf *bf,
				काष्ठा ath_txq *txq, काष्ठा list_head *bf_q,
				काष्ठा ieee80211_sta *sta,
				काष्ठा ath_tx_status *ts, पूर्णांक txok);
अटल व्योम ath_tx_txqaddbuf(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq,
			     काष्ठा list_head *head, bool पूर्णांकernal);
अटल व्योम ath_tx_rc_status(काष्ठा ath_softc *sc, काष्ठा ath_buf *bf,
			     काष्ठा ath_tx_status *ts, पूर्णांक nframes, पूर्णांक nbad,
			     पूर्णांक txok);
अटल व्योम ath_tx_update_baw(काष्ठा ath_softc *sc, काष्ठा ath_atx_tid *tid,
			      काष्ठा ath_buf *bf);
अटल काष्ठा ath_buf *ath_tx_setup_buffer(काष्ठा ath_softc *sc,
					   काष्ठा ath_txq *txq,
					   काष्ठा ath_atx_tid *tid,
					   काष्ठा sk_buff *skb);
अटल पूर्णांक ath_tx_prepare(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb,
			  काष्ठा ath_tx_control *txctl);

क्रमागत अणु
	MCS_HT20,
	MCS_HT20_SGI,
	MCS_HT40,
	MCS_HT40_SGI,
पूर्ण;

/*********************/
/* Aggregation logic */
/*********************/

अटल व्योम ath_tx_status(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_sta *sta = info->status.status_driver_data[0];

	अगर (info->flags & (IEEE80211_TX_CTL_REQ_TX_STATUS |
			   IEEE80211_TX_STATUS_EOSP)) अणु
		ieee80211_tx_status(hw, skb);
		वापस;
	पूर्ण

	अगर (sta)
		ieee80211_tx_status_noskb(hw, sta, info);

	dev_kमुक्त_skb(skb);
पूर्ण

व्योम ath_txq_unlock_complete(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq)
	__releases(&txq->axq_lock)
अणु
	काष्ठा ieee80211_hw *hw = sc->hw;
	काष्ठा sk_buff_head q;
	काष्ठा sk_buff *skb;

	__skb_queue_head_init(&q);
	skb_queue_splice_init(&txq->complete_q, &q);
	spin_unlock_bh(&txq->axq_lock);

	जबतक ((skb = __skb_dequeue(&q)))
		ath_tx_status(hw, skb);
पूर्ण

व्योम ath_tx_queue_tid(काष्ठा ath_softc *sc, काष्ठा ath_atx_tid *tid)
अणु
	काष्ठा ieee80211_txq *queue =
		container_of((व्योम *)tid, काष्ठा ieee80211_txq, drv_priv);

	ieee80211_schedule_txq(sc->hw, queue);
पूर्ण

व्योम ath9k_wake_tx_queue(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_txq *queue)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_atx_tid *tid = (काष्ठा ath_atx_tid *) queue->drv_priv;
	काष्ठा ath_txq *txq = tid->txq;

	ath_dbg(common, QUEUE, "Waking TX queue: %pM (%d)\n",
		queue->sta ? queue->sta->addr : queue->vअगर->addr,
		tid->tidno);

	ath_txq_lock(sc, txq);
	ath_txq_schedule(sc, txq);
	ath_txq_unlock(sc, txq);
पूर्ण

अटल काष्ठा ath_frame_info *get_frame_info(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	BUILD_BUG_ON(माप(काष्ठा ath_frame_info) >
		     माप(tx_info->rate_driver_data));
	वापस (काष्ठा ath_frame_info *) &tx_info->rate_driver_data[0];
पूर्ण

अटल व्योम ath_send_bar(काष्ठा ath_atx_tid *tid, u16 seqno)
अणु
	अगर (!tid->an->sta)
		वापस;

	ieee80211_send_bar(tid->an->vअगर, tid->an->sta->addr, tid->tidno,
			   seqno << IEEE80211_SEQ_SEQ_SHIFT);
पूर्ण

अटल व्योम ath_set_rates(काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
			  काष्ठा ath_buf *bf)
अणु
	ieee80211_get_tx_rates(vअगर, sta, bf->bf_mpdu, bf->rates,
			       ARRAY_SIZE(bf->rates));
पूर्ण

अटल व्योम ath_txq_skb_करोne(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा ath_frame_info *fi = get_frame_info(skb);
	पूर्णांक q = fi->txq;

	अगर (q < 0)
		वापस;

	txq = sc->tx.txq_map[q];
	अगर (WARN_ON(--txq->pending_frames < 0))
		txq->pending_frames = 0;

पूर्ण

अटल काष्ठा ath_atx_tid *
ath_get_skb_tid(काष्ठा ath_softc *sc, काष्ठा ath_node *an, काष्ठा sk_buff *skb)
अणु
	u8 tidno = skb->priority & IEEE80211_QOS_CTL_TID_MASK;
	वापस ATH_AN_2_TID(an, tidno);
पूर्ण

अटल पूर्णांक
ath_tid_pull(काष्ठा ath_atx_tid *tid, काष्ठा sk_buff **skbuf)
अणु
	काष्ठा ieee80211_txq *txq = container_of((व्योम*)tid, काष्ठा ieee80211_txq, drv_priv);
	काष्ठा ath_softc *sc = tid->an->sc;
	काष्ठा ieee80211_hw *hw = sc->hw;
	काष्ठा ath_tx_control txctl = अणु
		.txq = tid->txq,
		.sta = tid->an->sta,
	पूर्ण;
	काष्ठा sk_buff *skb;
	काष्ठा ath_frame_info *fi;
	पूर्णांक q, ret;

	skb = ieee80211_tx_dequeue(hw, txq);
	अगर (!skb)
		वापस -ENOENT;

	ret = ath_tx_prepare(hw, skb, &txctl);
	अगर (ret) अणु
		ieee80211_मुक्त_txskb(hw, skb);
		वापस ret;
	पूर्ण

	q = skb_get_queue_mapping(skb);
	अगर (tid->txq == sc->tx.txq_map[q]) अणु
		fi = get_frame_info(skb);
		fi->txq = q;
		++tid->txq->pending_frames;
	पूर्ण

	*skbuf = skb;
	वापस 0;
पूर्ण

अटल पूर्णांक ath_tid_dequeue(काष्ठा ath_atx_tid *tid,
			   काष्ठा sk_buff **skb)
अणु
	पूर्णांक ret = 0;
	*skb = __skb_dequeue(&tid->retry_q);
	अगर (!*skb)
		ret = ath_tid_pull(tid, skb);

	वापस ret;
पूर्ण

अटल व्योम ath_tx_flush_tid(काष्ठा ath_softc *sc, काष्ठा ath_atx_tid *tid)
अणु
	काष्ठा ath_txq *txq = tid->txq;
	काष्ठा sk_buff *skb;
	काष्ठा ath_buf *bf;
	काष्ठा list_head bf_head;
	काष्ठा ath_tx_status ts;
	काष्ठा ath_frame_info *fi;
	bool sendbar = false;

	INIT_LIST_HEAD(&bf_head);

	स_रखो(&ts, 0, माप(ts));

	जबतक ((skb = __skb_dequeue(&tid->retry_q))) अणु
		fi = get_frame_info(skb);
		bf = fi->bf;
		अगर (!bf) अणु
			ath_txq_skb_करोne(sc, txq, skb);
			ieee80211_मुक्त_txskb(sc->hw, skb);
			जारी;
		पूर्ण

		अगर (fi->baw_tracked) अणु
			ath_tx_update_baw(sc, tid, bf);
			sendbar = true;
		पूर्ण

		list_add_tail(&bf->list, &bf_head);
		ath_tx_complete_buf(sc, bf, txq, &bf_head, शून्य, &ts, 0);
	पूर्ण

	अगर (sendbar) अणु
		ath_txq_unlock(sc, txq);
		ath_send_bar(tid, tid->seq_start);
		ath_txq_lock(sc, txq);
	पूर्ण
पूर्ण

अटल व्योम ath_tx_update_baw(काष्ठा ath_softc *sc, काष्ठा ath_atx_tid *tid,
			      काष्ठा ath_buf *bf)
अणु
	काष्ठा ath_frame_info *fi = get_frame_info(bf->bf_mpdu);
	u16 seqno = bf->bf_state.seqno;
	पूर्णांक index, cindex;

	अगर (!fi->baw_tracked)
		वापस;

	index  = ATH_BA_INDEX(tid->seq_start, seqno);
	cindex = (tid->baw_head + index) & (ATH_TID_MAX_BUFS - 1);

	__clear_bit(cindex, tid->tx_buf);

	जबतक (tid->baw_head != tid->baw_tail && !test_bit(tid->baw_head, tid->tx_buf)) अणु
		INCR(tid->seq_start, IEEE80211_SEQ_MAX);
		INCR(tid->baw_head, ATH_TID_MAX_BUFS);
		अगर (tid->bar_index >= 0)
			tid->bar_index--;
	पूर्ण
पूर्ण

अटल व्योम ath_tx_addto_baw(काष्ठा ath_softc *sc, काष्ठा ath_atx_tid *tid,
			     काष्ठा ath_buf *bf)
अणु
	काष्ठा ath_frame_info *fi = get_frame_info(bf->bf_mpdu);
	u16 seqno = bf->bf_state.seqno;
	पूर्णांक index, cindex;

	अगर (fi->baw_tracked)
		वापस;

	index  = ATH_BA_INDEX(tid->seq_start, seqno);
	cindex = (tid->baw_head + index) & (ATH_TID_MAX_BUFS - 1);
	__set_bit(cindex, tid->tx_buf);
	fi->baw_tracked = 1;

	अगर (index >= ((tid->baw_tail - tid->baw_head) &
		(ATH_TID_MAX_BUFS - 1))) अणु
		tid->baw_tail = cindex;
		INCR(tid->baw_tail, ATH_TID_MAX_BUFS);
	पूर्ण
पूर्ण

अटल व्योम ath_tid_drain(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq,
			  काष्ठा ath_atx_tid *tid)

अणु
	काष्ठा sk_buff *skb;
	काष्ठा ath_buf *bf;
	काष्ठा list_head bf_head;
	काष्ठा ath_tx_status ts;
	काष्ठा ath_frame_info *fi;
	पूर्णांक ret;

	स_रखो(&ts, 0, माप(ts));
	INIT_LIST_HEAD(&bf_head);

	जबतक ((ret = ath_tid_dequeue(tid, &skb)) == 0) अणु
		fi = get_frame_info(skb);
		bf = fi->bf;

		अगर (!bf) अणु
			ath_tx_complete(sc, skb, ATH_TX_ERROR, txq, शून्य);
			जारी;
		पूर्ण

		list_add_tail(&bf->list, &bf_head);
		ath_tx_complete_buf(sc, bf, txq, &bf_head, शून्य, &ts, 0);
	पूर्ण
पूर्ण

अटल व्योम ath_tx_set_retry(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq,
			     काष्ठा sk_buff *skb, पूर्णांक count)
अणु
	काष्ठा ath_frame_info *fi = get_frame_info(skb);
	काष्ठा ath_buf *bf = fi->bf;
	काष्ठा ieee80211_hdr *hdr;
	पूर्णांक prev = fi->retries;

	TX_STAT_INC(sc, txq->axq_qnum, a_retries);
	fi->retries += count;

	अगर (prev > 0)
		वापस;

	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	hdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_RETRY);
	dma_sync_single_क्रम_device(sc->dev, bf->bf_buf_addr,
		माप(*hdr), DMA_TO_DEVICE);
पूर्ण

अटल काष्ठा ath_buf *ath_tx_get_buffer(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_buf *bf = शून्य;

	spin_lock_bh(&sc->tx.txbuflock);

	अगर (unlikely(list_empty(&sc->tx.txbuf))) अणु
		spin_unlock_bh(&sc->tx.txbuflock);
		वापस शून्य;
	पूर्ण

	bf = list_first_entry(&sc->tx.txbuf, काष्ठा ath_buf, list);
	list_del(&bf->list);

	spin_unlock_bh(&sc->tx.txbuflock);

	वापस bf;
पूर्ण

अटल व्योम ath_tx_वापस_buffer(काष्ठा ath_softc *sc, काष्ठा ath_buf *bf)
अणु
	spin_lock_bh(&sc->tx.txbuflock);
	list_add_tail(&bf->list, &sc->tx.txbuf);
	spin_unlock_bh(&sc->tx.txbuflock);
पूर्ण

अटल काष्ठा ath_buf* ath_clone_txbuf(काष्ठा ath_softc *sc, काष्ठा ath_buf *bf)
अणु
	काष्ठा ath_buf *tbf;

	tbf = ath_tx_get_buffer(sc);
	अगर (WARN_ON(!tbf))
		वापस शून्य;

	ATH_TXBUF_RESET(tbf);

	tbf->bf_mpdu = bf->bf_mpdu;
	tbf->bf_buf_addr = bf->bf_buf_addr;
	स_नकल(tbf->bf_desc, bf->bf_desc, sc->sc_ah->caps.tx_desc_len);
	tbf->bf_state = bf->bf_state;
	tbf->bf_state.stale = false;

	वापस tbf;
पूर्ण

अटल व्योम ath_tx_count_frames(काष्ठा ath_softc *sc, काष्ठा ath_buf *bf,
			        काष्ठा ath_tx_status *ts, पूर्णांक txok,
			        पूर्णांक *nframes, पूर्णांक *nbad)
अणु
	u16 seq_st = 0;
	u32 ba[WME_BA_BMP_SIZE >> 5];
	पूर्णांक ba_index;
	पूर्णांक isaggr = 0;

	*nbad = 0;
	*nframes = 0;

	isaggr = bf_isaggr(bf);
	अगर (isaggr) अणु
		seq_st = ts->ts_seqnum;
		स_नकल(ba, &ts->ba_low, WME_BA_BMP_SIZE >> 3);
	पूर्ण

	जबतक (bf) अणु
		ba_index = ATH_BA_INDEX(seq_st, bf->bf_state.seqno);

		(*nframes)++;
		अगर (!txok || (isaggr && !ATH_BA_ISSET(ba, ba_index)))
			(*nbad)++;

		bf = bf->bf_next;
	पूर्ण
पूर्ण


अटल व्योम ath_tx_complete_aggr(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq,
				 काष्ठा ath_buf *bf, काष्ठा list_head *bf_q,
				 काष्ठा ieee80211_sta *sta,
				 काष्ठा ath_atx_tid *tid,
				 काष्ठा ath_tx_status *ts, पूर्णांक txok)
अणु
	काष्ठा ath_node *an = शून्य;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_info *tx_info;
	काष्ठा ath_buf *bf_next, *bf_last = bf->bf_lastbf;
	काष्ठा list_head bf_head;
	काष्ठा sk_buff_head bf_pending;
	u16 seq_st = 0, acked_cnt = 0, txfail_cnt = 0, seq_first;
	u32 ba[WME_BA_BMP_SIZE >> 5];
	पूर्णांक isaggr, txfail, txpending, sendbar = 0, needreset = 0, nbad = 0;
	bool rc_update = true, isba;
	काष्ठा ieee80211_tx_rate rates[4];
	काष्ठा ath_frame_info *fi;
	पूर्णांक nframes;
	bool flush = !!(ts->ts_status & ATH9K_TX_FLUSH);
	पूर्णांक i, retries;
	पूर्णांक bar_index = -1;

	skb = bf->bf_mpdu;
	tx_info = IEEE80211_SKB_CB(skb);

	स_नकल(rates, bf->rates, माप(rates));

	retries = ts->ts_दीर्घretry + 1;
	क्रम (i = 0; i < ts->ts_rateindex; i++)
		retries += rates[i].count;

	अगर (!sta) अणु
		INIT_LIST_HEAD(&bf_head);
		जबतक (bf) अणु
			bf_next = bf->bf_next;

			अगर (!bf->bf_state.stale || bf_next != शून्य)
				list_move_tail(&bf->list, &bf_head);

			ath_tx_complete_buf(sc, bf, txq, &bf_head, शून्य, ts, 0);

			bf = bf_next;
		पूर्ण
		वापस;
	पूर्ण

	an = (काष्ठा ath_node *)sta->drv_priv;
	seq_first = tid->seq_start;
	isba = ts->ts_flags & ATH9K_TX_BA;

	/*
	 * The hardware occasionally sends a tx status क्रम the wrong TID.
	 * In this हाल, the BA status cannot be considered valid and all
	 * subframes need to be retransmitted
	 *
	 * Only BlockAcks have a TID and thereक्रमe normal Acks cannot be
	 * checked
	 */
	अगर (isba && tid->tidno != ts->tid)
		txok = false;

	isaggr = bf_isaggr(bf);
	स_रखो(ba, 0, WME_BA_BMP_SIZE >> 3);

	अगर (isaggr && txok) अणु
		अगर (ts->ts_flags & ATH9K_TX_BA) अणु
			seq_st = ts->ts_seqnum;
			स_नकल(ba, &ts->ba_low, WME_BA_BMP_SIZE >> 3);
		पूर्ण अन्यथा अणु
			/*
			 * AR5416 can become deaf/mute when BA
			 * issue happens. Chip needs to be reset.
			 * But AP code may have sychronization issues
			 * when perक्रमm पूर्णांकernal reset in this routine.
			 * Only enable reset in STA mode क्रम now.
			 */
			अगर (sc->sc_ah->opmode == NL80211_IFTYPE_STATION)
				needreset = 1;
		पूर्ण
	पूर्ण

	__skb_queue_head_init(&bf_pending);

	ath_tx_count_frames(sc, bf, ts, txok, &nframes, &nbad);
	जबतक (bf) अणु
		u16 seqno = bf->bf_state.seqno;

		txfail = txpending = sendbar = 0;
		bf_next = bf->bf_next;

		skb = bf->bf_mpdu;
		tx_info = IEEE80211_SKB_CB(skb);
		fi = get_frame_info(skb);

		अगर (!BAW_WITHIN(tid->seq_start, tid->baw_size, seqno) ||
		    !tid->active) अणु
			/*
			 * Outside of the current BlockAck winकरोw,
			 * maybe part of a previous session
			 */
			txfail = 1;
		पूर्ण अन्यथा अगर (ATH_BA_ISSET(ba, ATH_BA_INDEX(seq_st, seqno))) अणु
			/* transmit completion, subframe is
			 * acked by block ack */
			acked_cnt++;
		पूर्ण अन्यथा अगर (!isaggr && txok) अणु
			/* transmit completion */
			acked_cnt++;
		पूर्ण अन्यथा अगर (flush) अणु
			txpending = 1;
		पूर्ण अन्यथा अगर (fi->retries < ATH_MAX_SW_RETRIES) अणु
			अगर (txok || !an->sleeping)
				ath_tx_set_retry(sc, txq, bf->bf_mpdu,
						 retries);

			txpending = 1;
		पूर्ण अन्यथा अणु
			txfail = 1;
			txfail_cnt++;
			bar_index = max_t(पूर्णांक, bar_index,
				ATH_BA_INDEX(seq_first, seqno));
		पूर्ण

		/*
		 * Make sure the last desc is reclaimed अगर it
		 * not a holding desc.
		 */
		INIT_LIST_HEAD(&bf_head);
		अगर (bf_next != शून्य || !bf_last->bf_state.stale)
			list_move_tail(&bf->list, &bf_head);

		अगर (!txpending) अणु
			/*
			 * complete the acked-ones/xretried ones; update
			 * block-ack winकरोw
			 */
			ath_tx_update_baw(sc, tid, bf);

			अगर (rc_update && (acked_cnt == 1 || txfail_cnt == 1)) अणु
				स_नकल(tx_info->control.rates, rates, माप(rates));
				ath_tx_rc_status(sc, bf, ts, nframes, nbad, txok);
				rc_update = false;
				अगर (bf == bf->bf_lastbf)
					ath_dynack_sample_tx_ts(sc->sc_ah,
								bf->bf_mpdu,
								ts, sta);
			पूर्ण

			ath_tx_complete_buf(sc, bf, txq, &bf_head, sta, ts,
				!txfail);
		पूर्ण अन्यथा अणु
			अगर (tx_info->flags & IEEE80211_TX_STATUS_EOSP) अणु
				tx_info->flags &= ~IEEE80211_TX_STATUS_EOSP;
				ieee80211_sta_eosp(sta);
			पूर्ण
			/* retry the un-acked ones */
			अगर (bf->bf_next == शून्य && bf_last->bf_state.stale) अणु
				काष्ठा ath_buf *tbf;

				tbf = ath_clone_txbuf(sc, bf_last);
				/*
				 * Update tx baw and complete the
				 * frame with failed status अगर we
				 * run out of tx buf.
				 */
				अगर (!tbf) अणु
					ath_tx_update_baw(sc, tid, bf);

					ath_tx_complete_buf(sc, bf, txq,
							    &bf_head, शून्य, ts,
							    0);
					bar_index = max_t(पूर्णांक, bar_index,
						ATH_BA_INDEX(seq_first, seqno));
					अवरोध;
				पूर्ण

				fi->bf = tbf;
			पूर्ण

			/*
			 * Put this buffer to the temporary pending
			 * queue to retain ordering
			 */
			__skb_queue_tail(&bf_pending, skb);
		पूर्ण

		bf = bf_next;
	पूर्ण

	/* prepend un-acked frames to the beginning of the pending frame queue */
	अगर (!skb_queue_empty(&bf_pending)) अणु
		अगर (an->sleeping)
			ieee80211_sta_set_buffered(sta, tid->tidno, true);

		skb_queue_splice_tail(&bf_pending, &tid->retry_q);
		अगर (!an->sleeping) अणु
			ath_tx_queue_tid(sc, tid);
			अगर (ts->ts_status & (ATH9K_TXERR_FILT | ATH9K_TXERR_XRETRY))
				tid->clear_ps_filter = true;
		पूर्ण
	पूर्ण

	अगर (bar_index >= 0) अणु
		u16 bar_seq = ATH_BA_INDEX2SEQ(seq_first, bar_index);

		अगर (BAW_WITHIN(tid->seq_start, tid->baw_size, bar_seq))
			tid->bar_index = ATH_BA_INDEX(tid->seq_start, bar_seq);

		ath_txq_unlock(sc, txq);
		ath_send_bar(tid, ATH_BA_INDEX2SEQ(seq_first, bar_index + 1));
		ath_txq_lock(sc, txq);
	पूर्ण

	अगर (needreset)
		ath9k_queue_reset(sc, RESET_TYPE_TX_ERROR);
पूर्ण

अटल bool bf_is_ampdu_not_probing(काष्ठा ath_buf *bf)
अणु
    काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(bf->bf_mpdu);
    वापस bf_isampdu(bf) && !(info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE);
पूर्ण

अटल व्योम ath_tx_count_airसमय(काष्ठा ath_softc *sc,
				 काष्ठा ieee80211_sta *sta,
				 काष्ठा ath_buf *bf,
				 काष्ठा ath_tx_status *ts,
				 u8 tid)
अणु
	u32 airसमय = 0;
	पूर्णांक i;

	airसमय += ts->duration * (ts->ts_दीर्घretry + 1);
	क्रम(i = 0; i < ts->ts_rateindex; i++) अणु
		पूर्णांक rate_dur = ath9k_hw_get_duration(sc->sc_ah, bf->bf_desc, i);
		airसमय += rate_dur * bf->rates[i].count;
	पूर्ण

	ieee80211_sta_रेजिस्टर_airसमय(sta, tid, airसमय, 0);
पूर्ण

अटल व्योम ath_tx_process_buffer(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq,
				  काष्ठा ath_tx_status *ts, काष्ठा ath_buf *bf,
				  काष्ठा list_head *bf_head)
अणु
	काष्ठा ieee80211_hw *hw = sc->hw;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_sta *sta;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ath_atx_tid *tid = शून्य;
	bool txok, flush;

	txok = !(ts->ts_status & ATH9K_TXERR_MASK);
	flush = !!(ts->ts_status & ATH9K_TX_FLUSH);
	txq->axq_tx_inprogress = false;

	txq->axq_depth--;
	अगर (bf_is_ampdu_not_probing(bf))
		txq->axq_ampdu_depth--;

	ts->duration = ath9k_hw_get_duration(sc->sc_ah, bf->bf_desc,
					     ts->ts_rateindex);

	hdr = (काष्ठा ieee80211_hdr *) bf->bf_mpdu->data;
	sta = ieee80211_find_sta_by_अगरaddr(hw, hdr->addr1, hdr->addr2);
	अगर (sta) अणु
		काष्ठा ath_node *an = (काष्ठा ath_node *)sta->drv_priv;
		tid = ath_get_skb_tid(sc, an, bf->bf_mpdu);
		ath_tx_count_airसमय(sc, sta, bf, ts, tid->tidno);
		अगर (ts->ts_status & (ATH9K_TXERR_FILT | ATH9K_TXERR_XRETRY))
			tid->clear_ps_filter = true;
	पूर्ण

	अगर (!bf_isampdu(bf)) अणु
		अगर (!flush) अणु
			info = IEEE80211_SKB_CB(bf->bf_mpdu);
			स_नकल(info->control.rates, bf->rates,
			       माप(info->control.rates));
			ath_tx_rc_status(sc, bf, ts, 1, txok ? 0 : 1, txok);
			ath_dynack_sample_tx_ts(sc->sc_ah, bf->bf_mpdu, ts,
						sta);
		पूर्ण
		ath_tx_complete_buf(sc, bf, txq, bf_head, sta, ts, txok);
	पूर्ण अन्यथा
		ath_tx_complete_aggr(sc, txq, bf, bf_head, sta, tid, ts, txok);

	अगर (!flush)
		ath_txq_schedule(sc, txq);
पूर्ण

अटल bool ath_lookup_legacy(काष्ठा ath_buf *bf)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_info *tx_info;
	काष्ठा ieee80211_tx_rate *rates;
	पूर्णांक i;

	skb = bf->bf_mpdu;
	tx_info = IEEE80211_SKB_CB(skb);
	rates = tx_info->control.rates;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (!rates[i].count || rates[i].idx < 0)
			अवरोध;

		अगर (!(rates[i].flags & IEEE80211_TX_RC_MCS))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल u32 ath_lookup_rate(काष्ठा ath_softc *sc, काष्ठा ath_buf *bf,
			   काष्ठा ath_atx_tid *tid)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_info *tx_info;
	काष्ठा ieee80211_tx_rate *rates;
	u32 max_4ms_framelen, frmlen;
	u16 aggr_limit, bt_aggr_limit, legacy = 0;
	पूर्णांक q = tid->txq->mac80211_qnum;
	पूर्णांक i;

	skb = bf->bf_mpdu;
	tx_info = IEEE80211_SKB_CB(skb);
	rates = bf->rates;

	/*
	 * Find the lowest frame length among the rate series that will have a
	 * 4ms (or TXOP limited) transmit duration.
	 */
	max_4ms_framelen = ATH_AMPDU_LIMIT_MAX;

	क्रम (i = 0; i < 4; i++) अणु
		पूर्णांक modeidx;

		अगर (!rates[i].count)
			जारी;

		अगर (!(rates[i].flags & IEEE80211_TX_RC_MCS)) अणु
			legacy = 1;
			अवरोध;
		पूर्ण

		अगर (rates[i].flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
			modeidx = MCS_HT40;
		अन्यथा
			modeidx = MCS_HT20;

		अगर (rates[i].flags & IEEE80211_TX_RC_SHORT_GI)
			modeidx++;

		frmlen = sc->tx.max_aggr_framelen[q][modeidx][rates[i].idx];
		max_4ms_framelen = min(max_4ms_framelen, frmlen);
	पूर्ण

	/*
	 * limit aggregate size by the minimum rate अगर rate selected is
	 * not a probe rate, अगर rate selected is a probe rate then
	 * aव्योम aggregation of this packet.
	 */
	अगर (tx_info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE || legacy)
		वापस 0;

	aggr_limit = min(max_4ms_framelen, (u32)ATH_AMPDU_LIMIT_MAX);

	/*
	 * Override the शेष aggregation limit क्रम BTCOEX.
	 */
	bt_aggr_limit = ath9k_btcoex_aggr_limit(sc, max_4ms_framelen);
	अगर (bt_aggr_limit)
		aggr_limit = bt_aggr_limit;

	अगर (tid->an->maxampdu)
		aggr_limit = min(aggr_limit, tid->an->maxampdu);

	वापस aggr_limit;
पूर्ण

/*
 * Returns the number of delimiters to be added to
 * meet the minimum required mpdudensity.
 */
अटल पूर्णांक ath_compute_num_delims(काष्ठा ath_softc *sc, काष्ठा ath_atx_tid *tid,
				  काष्ठा ath_buf *bf, u16 frmlen,
				  bool first_subfrm)
अणु
#घोषणा FIRST_DESC_NDELIMS 60
	u32 nsymbits, nsymbols;
	u16 minlen;
	u8 flags, rix;
	पूर्णांक width, streams, half_gi, ndelim, mindelim;
	काष्ठा ath_frame_info *fi = get_frame_info(bf->bf_mpdu);

	/* Select standard number of delimiters based on frame length alone */
	ndelim = ATH_AGGR_GET_NDELIM(frmlen);

	/*
	 * If encryption enabled, hardware requires some more padding between
	 * subframes.
	 * TODO - this could be improved to be dependent on the rate.
	 *      The hardware can keep up at lower rates, but not higher rates
	 */
	अगर ((fi->keyix != ATH9K_TXKEYIX_INVALID) &&
	    !(sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA))
		ndelim += ATH_AGGR_ENCRYPTDELIM;

	/*
	 * Add delimiter when using RTS/CTS with aggregation
	 * and non enterprise AR9003 card
	 */
	अगर (first_subfrm && !AR_SREV_9580_10_OR_LATER(sc->sc_ah) &&
	    (sc->sc_ah->ent_mode & AR_ENT_OTP_MIN_PKT_SIZE_DISABLE))
		ndelim = max(ndelim, FIRST_DESC_NDELIMS);

	/*
	 * Convert desired mpdu density from microeconds to bytes based
	 * on highest rate in rate series (i.e. first rate) to determine
	 * required minimum length क्रम subframe. Take पूर्णांकo account
	 * whether high rate is 20 or 40Mhz and half or full GI.
	 *
	 * If there is no mpdu density restriction, no further calculation
	 * is needed.
	 */

	अगर (tid->an->mpdudensity == 0)
		वापस ndelim;

	rix = bf->rates[0].idx;
	flags = bf->rates[0].flags;
	width = (flags & IEEE80211_TX_RC_40_MHZ_WIDTH) ? 1 : 0;
	half_gi = (flags & IEEE80211_TX_RC_SHORT_GI) ? 1 : 0;

	अगर (half_gi)
		nsymbols = NUM_SYMBOLS_PER_USEC_HALFGI(tid->an->mpdudensity);
	अन्यथा
		nsymbols = NUM_SYMBOLS_PER_USEC(tid->an->mpdudensity);

	अगर (nsymbols == 0)
		nsymbols = 1;

	streams = HT_RC_2_STREAMS(rix);
	nsymbits = bits_per_symbol[rix % 8][width] * streams;
	minlen = (nsymbols * nsymbits) / BITS_PER_BYTE;

	अगर (frmlen < minlen) अणु
		mindelim = (minlen - frmlen) / ATH_AGGR_DELIM_SZ;
		ndelim = max(mindelim, ndelim);
	पूर्ण

	वापस ndelim;
पूर्ण

अटल पूर्णांक
ath_tx_get_tid_subframe(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq,
			काष्ठा ath_atx_tid *tid, काष्ठा ath_buf **buf)
अणु
	काष्ठा ieee80211_tx_info *tx_info;
	काष्ठा ath_frame_info *fi;
	काष्ठा ath_buf *bf;
	काष्ठा sk_buff *skb, *first_skb = शून्य;
	u16 seqno;
	पूर्णांक ret;

	जबतक (1) अणु
		ret = ath_tid_dequeue(tid, &skb);
		अगर (ret < 0)
			वापस ret;

		fi = get_frame_info(skb);
		bf = fi->bf;
		अगर (!fi->bf)
			bf = ath_tx_setup_buffer(sc, txq, tid, skb);
		अन्यथा
			bf->bf_state.stale = false;

		अगर (!bf) अणु
			ath_txq_skb_करोne(sc, txq, skb);
			ieee80211_मुक्त_txskb(sc->hw, skb);
			जारी;
		पूर्ण

		bf->bf_next = शून्य;
		bf->bf_lastbf = bf;

		tx_info = IEEE80211_SKB_CB(skb);
		tx_info->flags &= ~(IEEE80211_TX_CTL_CLEAR_PS_FILT |
				    IEEE80211_TX_STATUS_EOSP);

		/*
		 * No aggregation session is running, but there may be frames
		 * from a previous session or a failed attempt in the queue.
		 * Send them out as normal data frames
		 */
		अगर (!tid->active)
			tx_info->flags &= ~IEEE80211_TX_CTL_AMPDU;

		अगर (!(tx_info->flags & IEEE80211_TX_CTL_AMPDU)) अणु
			bf->bf_state.bf_type = 0;
			अवरोध;
		पूर्ण

		bf->bf_state.bf_type = BUF_AMPDU | BUF_AGGR;
		seqno = bf->bf_state.seqno;

		/* करो not step over block-ack winकरोw */
		अगर (!BAW_WITHIN(tid->seq_start, tid->baw_size, seqno)) अणु
			__skb_queue_tail(&tid->retry_q, skb);

			/* If there are other skbs in the retry q, they are
			 * probably within the BAW, so loop immediately to get
			 * one of them. Otherwise the queue can get stuck. */
			अगर (!skb_queue_is_first(&tid->retry_q, skb) &&
			    !WARN_ON(skb == first_skb)) अणु
				अगर(!first_skb) /* infinite loop prevention */
					first_skb = skb;
				जारी;
			पूर्ण
			वापस -EINPROGRESS;
		पूर्ण

		अगर (tid->bar_index > ATH_BA_INDEX(tid->seq_start, seqno)) अणु
			काष्ठा ath_tx_status ts = अणुपूर्ण;
			काष्ठा list_head bf_head;

			INIT_LIST_HEAD(&bf_head);
			list_add(&bf->list, &bf_head);
			ath_tx_update_baw(sc, tid, bf);
			ath_tx_complete_buf(sc, bf, txq, &bf_head, शून्य, &ts, 0);
			जारी;
		पूर्ण

		अगर (bf_isampdu(bf))
			ath_tx_addto_baw(sc, tid, bf);

		अवरोध;
	पूर्ण

	*buf = bf;
	वापस 0;
पूर्ण

अटल पूर्णांक
ath_tx_क्रमm_aggr(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq,
		 काष्ठा ath_atx_tid *tid, काष्ठा list_head *bf_q,
		 काष्ठा ath_buf *bf_first)
अणु
#घोषणा PADBYTES(_len) ((4 - ((_len) % 4)) % 4)
	काष्ठा ath_buf *bf = bf_first, *bf_prev = शून्य;
	पूर्णांक nframes = 0, ndelim, ret;
	u16 aggr_limit = 0, al = 0, bpad = 0,
	    al_delta, h_baw = tid->baw_size / 2;
	काष्ठा ieee80211_tx_info *tx_info;
	काष्ठा ath_frame_info *fi;
	काष्ठा sk_buff *skb;


	bf = bf_first;
	aggr_limit = ath_lookup_rate(sc, bf, tid);

	जबतक (bf)
	अणु
		skb = bf->bf_mpdu;
		fi = get_frame_info(skb);

		/* करो not exceed aggregation limit */
		al_delta = ATH_AGGR_DELIM_SZ + fi->framelen;
		अगर (nframes) अणु
			अगर (aggr_limit < al + bpad + al_delta ||
			    ath_lookup_legacy(bf) || nframes >= h_baw)
				जाओ stop;

			tx_info = IEEE80211_SKB_CB(bf->bf_mpdu);
			अगर ((tx_info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE) ||
			    !(tx_info->flags & IEEE80211_TX_CTL_AMPDU))
				जाओ stop;
		पूर्ण

		/* add padding क्रम previous frame to aggregation length */
		al += bpad + al_delta;

		/*
		 * Get the delimiters needed to meet the MPDU
		 * density क्रम this node.
		 */
		ndelim = ath_compute_num_delims(sc, tid, bf_first, fi->framelen,
						!nframes);
		bpad = PADBYTES(al_delta) + (ndelim << 2);

		nframes++;
		bf->bf_next = शून्य;

		/* link buffers of this frame to the aggregate */
		bf->bf_state.ndelim = ndelim;

		list_add_tail(&bf->list, bf_q);
		अगर (bf_prev)
			bf_prev->bf_next = bf;

		bf_prev = bf;

		ret = ath_tx_get_tid_subframe(sc, txq, tid, &bf);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	जाओ finish;
stop:
	__skb_queue_tail(&tid->retry_q, bf->bf_mpdu);
finish:
	bf = bf_first;
	bf->bf_lastbf = bf_prev;

	अगर (bf == bf_prev) अणु
		al = get_frame_info(bf->bf_mpdu)->framelen;
		bf->bf_state.bf_type = BUF_AMPDU;
	पूर्ण अन्यथा अणु
		TX_STAT_INC(sc, txq->axq_qnum, a_aggr);
	पूर्ण

	वापस al;
#अघोषित PADBYTES
पूर्ण

/*
 * rix - rate index
 * pktlen - total bytes (delims + data + fcs + pads + pad delims)
 * width  - 0 क्रम 20 MHz, 1 क्रम 40 MHz
 * half_gi - to use 4us v/s 3.6 us क्रम symbol समय
 */
u32 ath_pkt_duration(काष्ठा ath_softc *sc, u8 rix, पूर्णांक pktlen,
		     पूर्णांक width, पूर्णांक half_gi, bool लघुPreamble)
अणु
	u32 nbits, nsymbits, duration, nsymbols;
	पूर्णांक streams;

	/* find number of symbols: PLCP + data */
	streams = HT_RC_2_STREAMS(rix);
	nbits = (pktlen << 3) + OFDM_PLCP_BITS;
	nsymbits = bits_per_symbol[rix % 8][width] * streams;
	nsymbols = (nbits + nsymbits - 1) / nsymbits;

	अगर (!half_gi)
		duration = SYMBOL_TIME(nsymbols);
	अन्यथा
		duration = SYMBOL_TIME_HALFGI(nsymbols);

	/* addup duration क्रम legacy/ht training and संकेत fields */
	duration += L_STF + L_LTF + L_SIG + HT_SIG + HT_STF + HT_LTF(streams);

	वापस duration;
पूर्ण

अटल पूर्णांक ath_max_framelen(पूर्णांक usec, पूर्णांक mcs, bool ht40, bool sgi)
अणु
	पूर्णांक streams = HT_RC_2_STREAMS(mcs);
	पूर्णांक symbols, bits;
	पूर्णांक bytes = 0;

	usec -= L_STF + L_LTF + L_SIG + HT_SIG + HT_STF + HT_LTF(streams);
	symbols = sgi ? TIME_SYMBOLS_HALFGI(usec) : TIME_SYMBOLS(usec);
	bits = symbols * bits_per_symbol[mcs % 8][ht40] * streams;
	bits -= OFDM_PLCP_BITS;
	bytes = bits / 8;
	अगर (bytes > 65532)
		bytes = 65532;

	वापस bytes;
पूर्ण

व्योम ath_update_max_aggr_framelen(काष्ठा ath_softc *sc, पूर्णांक queue, पूर्णांक txop)
अणु
	u16 *cur_ht20, *cur_ht20_sgi, *cur_ht40, *cur_ht40_sgi;
	पूर्णांक mcs;

	/* 4ms is the शेष (and maximum) duration */
	अगर (!txop || txop > 4096)
		txop = 4096;

	cur_ht20 = sc->tx.max_aggr_framelen[queue][MCS_HT20];
	cur_ht20_sgi = sc->tx.max_aggr_framelen[queue][MCS_HT20_SGI];
	cur_ht40 = sc->tx.max_aggr_framelen[queue][MCS_HT40];
	cur_ht40_sgi = sc->tx.max_aggr_framelen[queue][MCS_HT40_SGI];
	क्रम (mcs = 0; mcs < 32; mcs++) अणु
		cur_ht20[mcs] = ath_max_framelen(txop, mcs, false, false);
		cur_ht20_sgi[mcs] = ath_max_framelen(txop, mcs, false, true);
		cur_ht40[mcs] = ath_max_framelen(txop, mcs, true, false);
		cur_ht40_sgi[mcs] = ath_max_framelen(txop, mcs, true, true);
	पूर्ण
पूर्ण

अटल u8 ath_get_rate_txघातer(काष्ठा ath_softc *sc, काष्ठा ath_buf *bf,
			       u8 rateidx, bool is_40, bool is_cck)
अणु
	u8 max_घातer;
	काष्ठा sk_buff *skb;
	काष्ठा ath_frame_info *fi;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ath_hw *ah = sc->sc_ah;

	अगर (sc->tx99_state || !ah->tpc_enabled)
		वापस MAX_RATE_POWER;

	skb = bf->bf_mpdu;
	fi = get_frame_info(skb);
	info = IEEE80211_SKB_CB(skb);

	अगर (!AR_SREV_9300_20_OR_LATER(ah)) अणु
		पूर्णांक txघातer = fi->tx_घातer;

		अगर (is_40) अणु
			u8 घातer_ht40delta;
			काष्ठा ar5416_eeprom_def *eep = &ah->eeprom.def;
			u16 eeprom_rev = ah->eep_ops->get_eeprom_rev(ah);

			अगर (eeprom_rev >= AR5416_EEP_MINOR_VER_2) अणु
				bool is_2ghz;
				काष्ठा modal_eep_header *pmodal;

				is_2ghz = info->band == NL80211_BAND_2GHZ;
				pmodal = &eep->modalHeader[is_2ghz];
				घातer_ht40delta = pmodal->ht40PowerIncForPdadc;
			पूर्ण अन्यथा अणु
				घातer_ht40delta = 2;
			पूर्ण
			txघातer += घातer_ht40delta;
		पूर्ण

		अगर (AR_SREV_9287(ah) || AR_SREV_9285(ah) ||
		    AR_SREV_9271(ah)) अणु
			txघातer -= 2 * AR9287_PWR_TABLE_OFFSET_DB;
		पूर्ण अन्यथा अगर (AR_SREV_9280_20_OR_LATER(ah)) अणु
			s8 घातer_offset;

			घातer_offset = ah->eep_ops->get_eeprom(ah,
							EEP_PWR_TABLE_OFFSET);
			txघातer -= 2 * घातer_offset;
		पूर्ण

		अगर (OLC_FOR_AR9280_20_LATER && is_cck)
			txघातer -= 2;

		txघातer = max(txघातer, 0);
		max_घातer = min_t(u8, ah->tx_घातer[rateidx], txघातer);

		/* XXX: clamp minimum TX घातer at 1 क्रम AR9160 since अगर
		 * max_घातer is set to 0, frames are transmitted at max
		 * TX घातer
		 */
		अगर (!max_घातer && !AR_SREV_9280_20_OR_LATER(ah))
			max_घातer = 1;
	पूर्ण अन्यथा अगर (!bf->bf_state.bfs_paprd) अणु
		अगर (rateidx < 8 && (info->flags & IEEE80211_TX_CTL_STBC))
			max_घातer = min_t(u8, ah->tx_घातer_stbc[rateidx],
					  fi->tx_घातer);
		अन्यथा
			max_घातer = min_t(u8, ah->tx_घातer[rateidx],
					  fi->tx_घातer);
	पूर्ण अन्यथा अणु
		max_घातer = ah->paprd_training_घातer;
	पूर्ण

	वापस max_घातer;
पूर्ण

अटल व्योम ath_buf_set_rate(काष्ठा ath_softc *sc, काष्ठा ath_buf *bf,
			     काष्ठा ath_tx_info *info, पूर्णांक len, bool rts)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_info *tx_info;
	काष्ठा ieee80211_tx_rate *rates;
	स्थिर काष्ठा ieee80211_rate *rate;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ath_frame_info *fi = get_frame_info(bf->bf_mpdu);
	u32 rts_thresh = sc->hw->wiphy->rts_threshold;
	पूर्णांक i;
	u8 rix = 0;

	skb = bf->bf_mpdu;
	tx_info = IEEE80211_SKB_CB(skb);
	rates = bf->rates;
	hdr = (काष्ठा ieee80211_hdr *)skb->data;

	/* set dur_update_en क्रम l-sig computation except क्रम PS-Poll frames */
	info->dur_update = !ieee80211_is_pspoll(hdr->frame_control);
	info->rtscts_rate = fi->rtscts_rate;

	क्रम (i = 0; i < ARRAY_SIZE(bf->rates); i++) अणु
		bool is_40, is_sgi, is_sp, is_cck;
		पूर्णांक phy;

		अगर (!rates[i].count || (rates[i].idx < 0))
			जारी;

		rix = rates[i].idx;
		info->rates[i].Tries = rates[i].count;

		/*
		 * Handle RTS threshold क्रम unaggregated HT frames.
		 */
		अगर (bf_isampdu(bf) && !bf_isaggr(bf) &&
		    (rates[i].flags & IEEE80211_TX_RC_MCS) &&
		    unlikely(rts_thresh != (u32) -1)) अणु
			अगर (!rts_thresh || (len > rts_thresh))
				rts = true;
		पूर्ण

		अगर (rts || rates[i].flags & IEEE80211_TX_RC_USE_RTS_CTS) अणु
			info->rates[i].RateFlags |= ATH9K_RATESERIES_RTS_CTS;
			info->flags |= ATH9K_TXDESC_RTSENA;
		पूर्ण अन्यथा अगर (rates[i].flags & IEEE80211_TX_RC_USE_CTS_PROTECT) अणु
			info->rates[i].RateFlags |= ATH9K_RATESERIES_RTS_CTS;
			info->flags |= ATH9K_TXDESC_CTSENA;
		पूर्ण

		अगर (rates[i].flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
			info->rates[i].RateFlags |= ATH9K_RATESERIES_2040;
		अगर (rates[i].flags & IEEE80211_TX_RC_SHORT_GI)
			info->rates[i].RateFlags |= ATH9K_RATESERIES_HALFGI;

		is_sgi = !!(rates[i].flags & IEEE80211_TX_RC_SHORT_GI);
		is_40 = !!(rates[i].flags & IEEE80211_TX_RC_40_MHZ_WIDTH);
		is_sp = !!(rates[i].flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE);

		अगर (rates[i].flags & IEEE80211_TX_RC_MCS) अणु
			/* MCS rates */
			info->rates[i].Rate = rix | 0x80;
			info->rates[i].ChSel = ath_txchainmask_reduction(sc,
					ah->txchainmask, info->rates[i].Rate);
			info->rates[i].PktDuration = ath_pkt_duration(sc, rix, len,
				 is_40, is_sgi, is_sp);
			अगर (rix < 8 && (tx_info->flags & IEEE80211_TX_CTL_STBC))
				info->rates[i].RateFlags |= ATH9K_RATESERIES_STBC;
			अगर (rix >= 8 && fi->dyn_smps) अणु
				info->rates[i].RateFlags |=
					ATH9K_RATESERIES_RTS_CTS;
				info->flags |= ATH9K_TXDESC_CTSENA;
			पूर्ण

			info->txघातer[i] = ath_get_rate_txघातer(sc, bf, rix,
								is_40, false);
			जारी;
		पूर्ण

		/* legacy rates */
		rate = &common->sbands[tx_info->band].bitrates[rates[i].idx];
		अगर ((tx_info->band == NL80211_BAND_2GHZ) &&
		    !(rate->flags & IEEE80211_RATE_ERP_G))
			phy = WLAN_RC_PHY_CCK;
		अन्यथा
			phy = WLAN_RC_PHY_OFDM;

		info->rates[i].Rate = rate->hw_value;
		अगर (rate->hw_value_लघु) अणु
			अगर (rates[i].flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE)
				info->rates[i].Rate |= rate->hw_value_लघु;
		पूर्ण अन्यथा अणु
			is_sp = false;
		पूर्ण

		अगर (bf->bf_state.bfs_paprd)
			info->rates[i].ChSel = ah->txchainmask;
		अन्यथा
			info->rates[i].ChSel = ath_txchainmask_reduction(sc,
					ah->txchainmask, info->rates[i].Rate);

		info->rates[i].PktDuration = ath9k_hw_computetxसमय(sc->sc_ah,
			phy, rate->bitrate * 100, len, rix, is_sp);

		is_cck = IS_CCK_RATE(info->rates[i].Rate);
		info->txघातer[i] = ath_get_rate_txघातer(sc, bf, rix, false,
							is_cck);
	पूर्ण

	/* For AR5416 - RTS cannot be followed by a frame larger than 8K */
	अगर (bf_isaggr(bf) && (len > sc->sc_ah->caps.rts_aggr_limit))
		info->flags &= ~ATH9K_TXDESC_RTSENA;

	/* ATH9K_TXDESC_RTSENA and ATH9K_TXDESC_CTSENA are mutually exclusive. */
	अगर (info->flags & ATH9K_TXDESC_RTSENA)
		info->flags &= ~ATH9K_TXDESC_CTSENA;
पूर्ण

अटल क्रमागत ath9k_pkt_type get_hw_packet_type(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr;
	क्रमागत ath9k_pkt_type htype;
	__le16 fc;

	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	fc = hdr->frame_control;

	अगर (ieee80211_is_beacon(fc))
		htype = ATH9K_PKT_TYPE_BEACON;
	अन्यथा अगर (ieee80211_is_probe_resp(fc))
		htype = ATH9K_PKT_TYPE_PROBE_RESP;
	अन्यथा अगर (ieee80211_is_atim(fc))
		htype = ATH9K_PKT_TYPE_ATIM;
	अन्यथा अगर (ieee80211_is_pspoll(fc))
		htype = ATH9K_PKT_TYPE_PSPOLL;
	अन्यथा
		htype = ATH9K_PKT_TYPE_NORMAL;

	वापस htype;
पूर्ण

अटल व्योम ath_tx_fill_desc(काष्ठा ath_softc *sc, काष्ठा ath_buf *bf,
			     काष्ठा ath_txq *txq, पूर्णांक len)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_buf *bf_first = शून्य;
	काष्ठा ath_tx_info info;
	u32 rts_thresh = sc->hw->wiphy->rts_threshold;
	bool rts = false;

	स_रखो(&info, 0, माप(info));
	info.is_first = true;
	info.is_last = true;
	info.qcu = txq->axq_qnum;

	जबतक (bf) अणु
		काष्ठा sk_buff *skb = bf->bf_mpdu;
		काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
		काष्ठा ath_frame_info *fi = get_frame_info(skb);
		bool aggr = !!(bf->bf_state.bf_type & BUF_AGGR);

		info.type = get_hw_packet_type(skb);
		अगर (bf->bf_next)
			info.link = bf->bf_next->bf_daddr;
		अन्यथा
			info.link = (sc->tx99_state) ? bf->bf_daddr : 0;

		अगर (!bf_first) अणु
			bf_first = bf;

			अगर (!sc->tx99_state)
				info.flags = ATH9K_TXDESC_INTREQ;
			अगर ((tx_info->flags & IEEE80211_TX_CTL_CLEAR_PS_FILT) ||
			    txq == sc->tx.uapsdq)
				info.flags |= ATH9K_TXDESC_CLRDMASK;

			अगर (tx_info->flags & IEEE80211_TX_CTL_NO_ACK)
				info.flags |= ATH9K_TXDESC_NOACK;
			अगर (tx_info->flags & IEEE80211_TX_CTL_LDPC)
				info.flags |= ATH9K_TXDESC_LDPC;

			अगर (bf->bf_state.bfs_paprd)
				info.flags |= (u32) bf->bf_state.bfs_paprd <<
					      ATH9K_TXDESC_PAPRD_S;

			/*
			 * mac80211 करोesn't handle RTS threshold क्रम HT because
			 * the decision has to be taken based on AMPDU length
			 * and aggregation is करोne entirely inside ath9k.
			 * Set the RTS/CTS flag क्रम the first subframe based
			 * on the threshold.
			 */
			अगर (aggr && (bf == bf_first) &&
			    unlikely(rts_thresh != (u32) -1)) अणु
				/*
				 * "len" is the size of the entire AMPDU.
				 */
				अगर (!rts_thresh || (len > rts_thresh))
					rts = true;
			पूर्ण

			अगर (!aggr)
				len = fi->framelen;

			ath_buf_set_rate(sc, bf, &info, len, rts);
		पूर्ण

		info.buf_addr[0] = bf->bf_buf_addr;
		info.buf_len[0] = skb->len;
		info.pkt_len = fi->framelen;
		info.keyix = fi->keyix;
		info.keytype = fi->keytype;

		अगर (aggr) अणु
			अगर (bf == bf_first)
				info.aggr = AGGR_BUF_FIRST;
			अन्यथा अगर (bf == bf_first->bf_lastbf)
				info.aggr = AGGR_BUF_LAST;
			अन्यथा
				info.aggr = AGGR_BUF_MIDDLE;

			info.ndelim = bf->bf_state.ndelim;
			info.aggr_len = len;
		पूर्ण

		अगर (bf == bf_first->bf_lastbf)
			bf_first = शून्य;

		ath9k_hw_set_txdesc(ah, bf->bf_desc, &info);
		bf = bf->bf_next;
	पूर्ण
पूर्ण

अटल व्योम
ath_tx_क्रमm_burst(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq,
		  काष्ठा ath_atx_tid *tid, काष्ठा list_head *bf_q,
		  काष्ठा ath_buf *bf_first)
अणु
	काष्ठा ath_buf *bf = bf_first, *bf_prev = शून्य;
	पूर्णांक nframes = 0, ret;

	करो अणु
		काष्ठा ieee80211_tx_info *tx_info;

		nframes++;
		list_add_tail(&bf->list, bf_q);
		अगर (bf_prev)
			bf_prev->bf_next = bf;
		bf_prev = bf;

		अगर (nframes >= 2)
			अवरोध;

		ret = ath_tx_get_tid_subframe(sc, txq, tid, &bf);
		अगर (ret < 0)
			अवरोध;

		tx_info = IEEE80211_SKB_CB(bf->bf_mpdu);
		अगर (tx_info->flags & IEEE80211_TX_CTL_AMPDU) अणु
			__skb_queue_tail(&tid->retry_q, bf->bf_mpdu);
			अवरोध;
		पूर्ण

		ath_set_rates(tid->an->vअगर, tid->an->sta, bf);
	पूर्ण जबतक (1);
पूर्ण

अटल पूर्णांक ath_tx_sched_aggr(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq,
			     काष्ठा ath_atx_tid *tid)
अणु
	काष्ठा ath_buf *bf = शून्य;
	काष्ठा ieee80211_tx_info *tx_info;
	काष्ठा list_head bf_q;
	पूर्णांक aggr_len = 0, ret;
	bool aggr;

	INIT_LIST_HEAD(&bf_q);

	ret = ath_tx_get_tid_subframe(sc, txq, tid, &bf);
	अगर (ret < 0)
		वापस ret;

	tx_info = IEEE80211_SKB_CB(bf->bf_mpdu);
	aggr = !!(tx_info->flags & IEEE80211_TX_CTL_AMPDU);
	अगर ((aggr && txq->axq_ampdu_depth >= ATH_AGGR_MIN_QDEPTH) ||
	    (!aggr && txq->axq_depth >= ATH_NON_AGGR_MIN_QDEPTH)) अणु
		__skb_queue_tail(&tid->retry_q, bf->bf_mpdu);
		वापस -EBUSY;
	पूर्ण

	ath_set_rates(tid->an->vअगर, tid->an->sta, bf);
	अगर (aggr)
		aggr_len = ath_tx_क्रमm_aggr(sc, txq, tid, &bf_q, bf);
	अन्यथा
		ath_tx_क्रमm_burst(sc, txq, tid, &bf_q, bf);

	अगर (list_empty(&bf_q))
		वापस -EAGAIN;

	अगर (tid->clear_ps_filter || tid->an->no_ps_filter) अणु
		tid->clear_ps_filter = false;
		tx_info->flags |= IEEE80211_TX_CTL_CLEAR_PS_FILT;
	पूर्ण

	ath_tx_fill_desc(sc, bf, txq, aggr_len);
	ath_tx_txqaddbuf(sc, txq, &bf_q, false);
	वापस 0;
पूर्ण

पूर्णांक ath_tx_aggr_start(काष्ठा ath_softc *sc, काष्ठा ieee80211_sta *sta,
		      u16 tid, u16 *ssn)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_atx_tid *txtid;
	काष्ठा ath_txq *txq;
	काष्ठा ath_node *an;
	u8 density;

	ath_dbg(common, XMIT, "%s called\n", __func__);

	an = (काष्ठा ath_node *)sta->drv_priv;
	txtid = ATH_AN_2_TID(an, tid);
	txq = txtid->txq;

	ath_txq_lock(sc, txq);

	/* update ampdu factor/density, they may have changed. This may happen
	 * in HT IBSS when a beacon with HT-info is received after the station
	 * has alपढ़ोy been added.
	 */
	अगर (sta->ht_cap.ht_supported) अणु
		an->maxampdu = (1 << (IEEE80211_HT_MAX_AMPDU_FACTOR +
				      sta->ht_cap.ampdu_factor)) - 1;
		density = ath9k_parse_mpdudensity(sta->ht_cap.ampdu_density);
		an->mpdudensity = density;
	पूर्ण

	txtid->active = true;
	*ssn = txtid->seq_start = txtid->seq_next;
	txtid->bar_index = -1;

	स_रखो(txtid->tx_buf, 0, माप(txtid->tx_buf));
	txtid->baw_head = txtid->baw_tail = 0;

	ath_txq_unlock_complete(sc, txq);

	वापस 0;
पूर्ण

व्योम ath_tx_aggr_stop(काष्ठा ath_softc *sc, काष्ठा ieee80211_sta *sta, u16 tid)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_node *an = (काष्ठा ath_node *)sta->drv_priv;
	काष्ठा ath_atx_tid *txtid = ATH_AN_2_TID(an, tid);
	काष्ठा ath_txq *txq = txtid->txq;

	ath_dbg(common, XMIT, "%s called\n", __func__);

	ath_txq_lock(sc, txq);
	txtid->active = false;
	ath_tx_flush_tid(sc, txtid);
	ath_txq_unlock_complete(sc, txq);
पूर्ण

व्योम ath_tx_aggr_sleep(काष्ठा ieee80211_sta *sta, काष्ठा ath_softc *sc,
		       काष्ठा ath_node *an)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_atx_tid *tid;
	पूर्णांक tidno;

	ath_dbg(common, XMIT, "%s called\n", __func__);

	क्रम (tidno = 0; tidno < IEEE80211_NUM_TIDS; tidno++) अणु
		tid = ath_node_to_tid(an, tidno);

		अगर (!skb_queue_empty(&tid->retry_q))
			ieee80211_sta_set_buffered(sta, tid->tidno, true);

	पूर्ण
पूर्ण

व्योम ath_tx_aggr_wakeup(काष्ठा ath_softc *sc, काष्ठा ath_node *an)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_atx_tid *tid;
	काष्ठा ath_txq *txq;
	पूर्णांक tidno;

	ath_dbg(common, XMIT, "%s called\n", __func__);

	क्रम (tidno = 0; tidno < IEEE80211_NUM_TIDS; tidno++) अणु
		tid = ath_node_to_tid(an, tidno);
		txq = tid->txq;

		ath_txq_lock(sc, txq);
		tid->clear_ps_filter = true;
		अगर (!skb_queue_empty(&tid->retry_q)) अणु
			ath_tx_queue_tid(sc, tid);
			ath_txq_schedule(sc, txq);
		पूर्ण
		ath_txq_unlock_complete(sc, txq);

	पूर्ण
पूर्ण


अटल व्योम
ath9k_set_moredata(काष्ठा ath_softc *sc, काष्ठा ath_buf *bf, bool val)
अणु
	काष्ठा ieee80211_hdr *hdr;
	u16 mask = cpu_to_le16(IEEE80211_FCTL_MOREDATA);
	u16 mask_val = mask * val;

	hdr = (काष्ठा ieee80211_hdr *) bf->bf_mpdu->data;
	अगर ((hdr->frame_control & mask) != mask_val) अणु
		hdr->frame_control = (hdr->frame_control & ~mask) | mask_val;
		dma_sync_single_क्रम_device(sc->dev, bf->bf_buf_addr,
			माप(*hdr), DMA_TO_DEVICE);
	पूर्ण
पूर्ण

व्योम ath9k_release_buffered_frames(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_sta *sta,
				   u16 tids, पूर्णांक nframes,
				   क्रमागत ieee80211_frame_release_type reason,
				   bool more_data)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_node *an = (काष्ठा ath_node *)sta->drv_priv;
	काष्ठा ath_txq *txq = sc->tx.uapsdq;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा list_head bf_q;
	काष्ठा ath_buf *bf_tail = शून्य, *bf = शून्य;
	पूर्णांक sent = 0;
	पूर्णांक i, ret;

	INIT_LIST_HEAD(&bf_q);
	क्रम (i = 0; tids && nframes; i++, tids >>= 1) अणु
		काष्ठा ath_atx_tid *tid;

		अगर (!(tids & 1))
			जारी;

		tid = ATH_AN_2_TID(an, i);

		ath_txq_lock(sc, tid->txq);
		जबतक (nframes > 0) अणु
			ret = ath_tx_get_tid_subframe(sc, sc->tx.uapsdq,
						      tid, &bf);
			अगर (ret < 0)
				अवरोध;

			ath9k_set_moredata(sc, bf, true);
			list_add_tail(&bf->list, &bf_q);
			ath_set_rates(tid->an->vअगर, tid->an->sta, bf);
			अगर (bf_isampdu(bf))
				bf->bf_state.bf_type &= ~BUF_AGGR;
			अगर (bf_tail)
				bf_tail->bf_next = bf;

			bf_tail = bf;
			nframes--;
			sent++;
			TX_STAT_INC(sc, txq->axq_qnum, a_queued_hw);

			अगर (an->sta && skb_queue_empty(&tid->retry_q))
				ieee80211_sta_set_buffered(an->sta, i, false);
		पूर्ण
		ath_txq_unlock_complete(sc, tid->txq);
	पूर्ण

	अगर (list_empty(&bf_q))
		वापस;

	अगर (!more_data)
		ath9k_set_moredata(sc, bf_tail, false);

	info = IEEE80211_SKB_CB(bf_tail->bf_mpdu);
	info->flags |= IEEE80211_TX_STATUS_EOSP;

	bf = list_first_entry(&bf_q, काष्ठा ath_buf, list);
	ath_txq_lock(sc, txq);
	ath_tx_fill_desc(sc, bf, txq, 0);
	ath_tx_txqaddbuf(sc, txq, &bf_q, false);
	ath_txq_unlock(sc, txq);
पूर्ण

/********************/
/* Queue Management */
/********************/

काष्ठा ath_txq *ath_txq_setup(काष्ठा ath_softc *sc, पूर्णांक qtype, पूर्णांक subtype)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath9k_tx_queue_info qi;
	अटल स्थिर पूर्णांक subtype_txq_to_hwq[] = अणु
		[IEEE80211_AC_BE] = ATH_TXQ_AC_BE,
		[IEEE80211_AC_BK] = ATH_TXQ_AC_BK,
		[IEEE80211_AC_VI] = ATH_TXQ_AC_VI,
		[IEEE80211_AC_VO] = ATH_TXQ_AC_VO,
	पूर्ण;
	पूर्णांक axq_qnum, i;

	स_रखो(&qi, 0, माप(qi));
	qi.tqi_subtype = subtype_txq_to_hwq[subtype];
	qi.tqi_aअगरs = ATH9K_TXQ_USEDEFAULT;
	qi.tqi_cwmin = ATH9K_TXQ_USEDEFAULT;
	qi.tqi_cwmax = ATH9K_TXQ_USEDEFAULT;
	qi.tqi_physCompBuf = 0;

	/*
	 * Enable पूर्णांकerrupts only क्रम EOL and DESC conditions.
	 * We mark tx descriptors to receive a DESC पूर्णांकerrupt
	 * when a tx queue माला_लो deep; otherwise रुकोing क्रम the
	 * EOL to reap descriptors.  Note that this is करोne to
	 * reduce पूर्णांकerrupt load and this only defers reaping
	 * descriptors, never transmitting frames.  Aside from
	 * reducing पूर्णांकerrupts this also permits more concurrency.
	 * The only potential करोwnside is अगर the tx queue backs
	 * up in which हाल the top half of the kernel may backup
	 * due to a lack of tx descriptors.
	 *
	 * The UAPSD queue is an exception, since we take a desc-
	 * based पूर्णांकr on the EOSP frames.
	 */
	अगर (ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) अणु
		qi.tqi_qflags = TXQ_FLAG_TXINT_ENABLE;
	पूर्ण अन्यथा अणु
		अगर (qtype == ATH9K_TX_QUEUE_UAPSD)
			qi.tqi_qflags = TXQ_FLAG_TXDESCINT_ENABLE;
		अन्यथा
			qi.tqi_qflags = TXQ_FLAG_TXEOLINT_ENABLE |
					TXQ_FLAG_TXDESCINT_ENABLE;
	पूर्ण
	axq_qnum = ath9k_hw_setuptxqueue(ah, qtype, &qi);
	अगर (axq_qnum == -1) अणु
		/*
		 * NB: करोn't prपूर्णांक a message, this happens
		 * normally on parts with too few tx queues
		 */
		वापस शून्य;
	पूर्ण
	अगर (!ATH_TXQ_SETUP(sc, axq_qnum)) अणु
		काष्ठा ath_txq *txq = &sc->tx.txq[axq_qnum];

		txq->axq_qnum = axq_qnum;
		txq->mac80211_qnum = -1;
		txq->axq_link = शून्य;
		__skb_queue_head_init(&txq->complete_q);
		INIT_LIST_HEAD(&txq->axq_q);
		spin_lock_init(&txq->axq_lock);
		txq->axq_depth = 0;
		txq->axq_ampdu_depth = 0;
		txq->axq_tx_inprogress = false;
		sc->tx.txqsetup |= 1<<axq_qnum;

		txq->txq_headidx = txq->txq_tailidx = 0;
		क्रम (i = 0; i < ATH_TXFIFO_DEPTH; i++)
			INIT_LIST_HEAD(&txq->txq_fअगरo[i]);
	पूर्ण
	वापस &sc->tx.txq[axq_qnum];
पूर्ण

पूर्णांक ath_txq_update(काष्ठा ath_softc *sc, पूर्णांक qnum,
		   काष्ठा ath9k_tx_queue_info *qinfo)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	पूर्णांक error = 0;
	काष्ठा ath9k_tx_queue_info qi;

	BUG_ON(sc->tx.txq[qnum].axq_qnum != qnum);

	ath9k_hw_get_txq_props(ah, qnum, &qi);
	qi.tqi_aअगरs = qinfo->tqi_aअगरs;
	qi.tqi_cwmin = qinfo->tqi_cwmin;
	qi.tqi_cwmax = qinfo->tqi_cwmax;
	qi.tqi_burstTime = qinfo->tqi_burstTime;
	qi.tqi_पढ़ोyTime = qinfo->tqi_पढ़ोyTime;

	अगर (!ath9k_hw_set_txq_props(ah, qnum, &qi)) अणु
		ath_err(ath9k_hw_common(sc->sc_ah),
			"Unable to update hardware queue %u!\n", qnum);
		error = -EIO;
	पूर्ण अन्यथा अणु
		ath9k_hw_resettxqueue(ah, qnum);
	पूर्ण

	वापस error;
पूर्ण

पूर्णांक ath_cabq_update(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath9k_tx_queue_info qi;
	काष्ठा ath_beacon_config *cur_conf = &sc->cur_chan->beacon;
	पूर्णांक qnum = sc->beacon.cabq->axq_qnum;

	ath9k_hw_get_txq_props(sc->sc_ah, qnum, &qi);

	qi.tqi_पढ़ोyTime = (TU_TO_USEC(cur_conf->beacon_पूर्णांकerval) *
			    ATH_CABQ_READY_TIME) / 100;
	ath_txq_update(sc, qnum, &qi);

	वापस 0;
पूर्ण

अटल व्योम ath_drain_txq_list(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq,
			       काष्ठा list_head *list)
अणु
	काष्ठा ath_buf *bf, *lastbf;
	काष्ठा list_head bf_head;
	काष्ठा ath_tx_status ts;

	स_रखो(&ts, 0, माप(ts));
	ts.ts_status = ATH9K_TX_FLUSH;
	INIT_LIST_HEAD(&bf_head);

	जबतक (!list_empty(list)) अणु
		bf = list_first_entry(list, काष्ठा ath_buf, list);

		अगर (bf->bf_state.stale) अणु
			list_del(&bf->list);

			ath_tx_वापस_buffer(sc, bf);
			जारी;
		पूर्ण

		lastbf = bf->bf_lastbf;
		list_cut_position(&bf_head, list, &lastbf->list);
		ath_tx_process_buffer(sc, txq, &ts, bf, &bf_head);
	पूर्ण
पूर्ण

/*
 * Drain a given TX queue (could be Beacon or Data)
 *
 * This assumes output has been stopped and
 * we करो not need to block ath_tx_tasklet.
 */
व्योम ath_draपूर्णांकxq(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq)
अणु
	rcu_पढ़ो_lock();
	ath_txq_lock(sc, txq);

	अगर (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) अणु
		पूर्णांक idx = txq->txq_tailidx;

		जबतक (!list_empty(&txq->txq_fअगरo[idx])) अणु
			ath_drain_txq_list(sc, txq, &txq->txq_fअगरo[idx]);

			INCR(idx, ATH_TXFIFO_DEPTH);
		पूर्ण
		txq->txq_tailidx = idx;
	पूर्ण

	txq->axq_link = शून्य;
	txq->axq_tx_inprogress = false;
	ath_drain_txq_list(sc, txq, &txq->axq_q);

	ath_txq_unlock_complete(sc, txq);
	rcu_पढ़ो_unlock();
पूर्ण

bool ath_drain_all_txq(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_txq *txq;
	पूर्णांक i;
	u32 npend = 0;

	अगर (test_bit(ATH_OP_INVALID, &common->op_flags))
		वापस true;

	ath9k_hw_पात_tx_dma(ah);

	/* Check अगर any queue reमुख्यs active */
	क्रम (i = 0; i < ATH9K_NUM_TX_QUEUES; i++) अणु
		अगर (!ATH_TXQ_SETUP(sc, i))
			जारी;

		अगर (!sc->tx.txq[i].axq_depth)
			जारी;

		अगर (ath9k_hw_numtxpending(ah, sc->tx.txq[i].axq_qnum))
			npend |= BIT(i);
	पूर्ण

	अगर (npend) अणु
		RESET_STAT_INC(sc, RESET_TX_DMA_ERROR);
		ath_dbg(common, RESET,
			"Failed to stop TX DMA, queues=0x%03x!\n", npend);
	पूर्ण

	क्रम (i = 0; i < ATH9K_NUM_TX_QUEUES; i++) अणु
		अगर (!ATH_TXQ_SETUP(sc, i))
			जारी;

		txq = &sc->tx.txq[i];
		ath_draपूर्णांकxq(sc, txq);
	पूर्ण

	वापस !npend;
पूर्ण

व्योम ath_tx_cleanupq(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq)
अणु
	ath9k_hw_releasetxqueue(sc->sc_ah, txq->axq_qnum);
	sc->tx.txqsetup &= ~(1<<txq->axq_qnum);
पूर्ण

/* For each acq entry, क्रम each tid, try to schedule packets
 * क्रम transmit until ampdu_depth has reached min Q depth.
 */
व्योम ath_txq_schedule(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq)
अणु
	काष्ठा ieee80211_hw *hw = sc->hw;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ieee80211_txq *queue;
	काष्ठा ath_atx_tid *tid;
	पूर्णांक ret;

	अगर (txq->mac80211_qnum < 0)
		वापस;

	अगर (test_bit(ATH_OP_HW_RESET, &common->op_flags))
		वापस;

	ieee80211_txq_schedule_start(hw, txq->mac80211_qnum);
	spin_lock_bh(&sc->chan_lock);
	rcu_पढ़ो_lock();

	अगर (sc->cur_chan->stopped)
		जाओ out;

	जबतक ((queue = ieee80211_next_txq(hw, txq->mac80211_qnum))) अणु
		bool क्रमce;

		tid = (काष्ठा ath_atx_tid *)queue->drv_priv;

		ret = ath_tx_sched_aggr(sc, txq, tid);
		ath_dbg(common, QUEUE, "ath_tx_sched_aggr returned %d\n", ret);

		क्रमce = !skb_queue_empty(&tid->retry_q);
		ieee80211_वापस_txq(hw, queue, क्रमce);
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	spin_unlock_bh(&sc->chan_lock);
	ieee80211_txq_schedule_end(hw, txq->mac80211_qnum);
पूर्ण

व्योम ath_txq_schedule_all(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_txq *txq;
	पूर्णांक i;

	क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
		txq = sc->tx.txq_map[i];

		spin_lock_bh(&txq->axq_lock);
		ath_txq_schedule(sc, txq);
		spin_unlock_bh(&txq->axq_lock);
	पूर्ण
पूर्ण

/***********/
/* TX, DMA */
/***********/

/*
 * Insert a chain of ath_buf (descriptors) on a txq and
 * assume the descriptors are alपढ़ोy chained together by caller.
 */
अटल व्योम ath_tx_txqaddbuf(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq,
			     काष्ठा list_head *head, bool पूर्णांकernal)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath_buf *bf, *bf_last;
	bool puttxbuf = false;
	bool edma;

	/*
	 * Insert the frame on the outbound list and
	 * pass it on to the hardware.
	 */

	अगर (list_empty(head))
		वापस;

	edma = !!(ah->caps.hw_caps & ATH9K_HW_CAP_EDMA);
	bf = list_first_entry(head, काष्ठा ath_buf, list);
	bf_last = list_entry(head->prev, काष्ठा ath_buf, list);

	ath_dbg(common, QUEUE, "qnum: %d, txq depth: %d\n",
		txq->axq_qnum, txq->axq_depth);

	अगर (edma && list_empty(&txq->txq_fअगरo[txq->txq_headidx])) अणु
		list_splice_tail_init(head, &txq->txq_fअगरo[txq->txq_headidx]);
		INCR(txq->txq_headidx, ATH_TXFIFO_DEPTH);
		puttxbuf = true;
	पूर्ण अन्यथा अणु
		list_splice_tail_init(head, &txq->axq_q);

		अगर (txq->axq_link) अणु
			ath9k_hw_set_desc_link(ah, txq->axq_link, bf->bf_daddr);
			ath_dbg(common, XMIT, "link[%u] (%p)=%llx (%p)\n",
				txq->axq_qnum, txq->axq_link,
				ito64(bf->bf_daddr), bf->bf_desc);
		पूर्ण अन्यथा अगर (!edma)
			puttxbuf = true;

		txq->axq_link = bf_last->bf_desc;
	पूर्ण

	अगर (puttxbuf) अणु
		TX_STAT_INC(sc, txq->axq_qnum, puttxbuf);
		ath9k_hw_puttxbuf(ah, txq->axq_qnum, bf->bf_daddr);
		ath_dbg(common, XMIT, "TXDP[%u] = %llx (%p)\n",
			txq->axq_qnum, ito64(bf->bf_daddr), bf->bf_desc);
	पूर्ण

	अगर (!edma || sc->tx99_state) अणु
		TX_STAT_INC(sc, txq->axq_qnum, txstart);
		ath9k_hw_txstart(ah, txq->axq_qnum);
	पूर्ण

	अगर (!पूर्णांकernal) अणु
		जबतक (bf) अणु
			txq->axq_depth++;
			अगर (bf_is_ampdu_not_probing(bf))
				txq->axq_ampdu_depth++;

			bf_last = bf->bf_lastbf;
			bf = bf_last->bf_next;
			bf_last->bf_next = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ath_tx_send_normal(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq,
			       काष्ठा ath_atx_tid *tid, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	काष्ठा ath_frame_info *fi = get_frame_info(skb);
	काष्ठा list_head bf_head;
	काष्ठा ath_buf *bf = fi->bf;

	INIT_LIST_HEAD(&bf_head);
	list_add_tail(&bf->list, &bf_head);
	bf->bf_state.bf_type = 0;
	अगर (tid && (tx_info->flags & IEEE80211_TX_CTL_AMPDU)) अणु
		bf->bf_state.bf_type = BUF_AMPDU;
		ath_tx_addto_baw(sc, tid, bf);
	पूर्ण

	bf->bf_next = शून्य;
	bf->bf_lastbf = bf;
	ath_tx_fill_desc(sc, bf, txq, fi->framelen);
	ath_tx_txqaddbuf(sc, txq, &bf_head, false);
	TX_STAT_INC(sc, txq->axq_qnum, queued);
पूर्ण

अटल व्योम setup_frame_info(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_sta *sta,
			     काष्ठा sk_buff *skb,
			     पूर्णांक framelen)
अणु
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_key_conf *hw_key = tx_info->control.hw_key;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	स्थिर काष्ठा ieee80211_rate *rate;
	काष्ठा ath_frame_info *fi = get_frame_info(skb);
	काष्ठा ath_node *an = शून्य;
	क्रमागत ath9k_key_type keytype;
	bool लघु_preamble = false;
	u8 txघातer;

	/*
	 * We check अगर Short Preamble is needed क्रम the CTS rate by
	 * checking the BSS's global flag.
	 * But क्रम the rate series, IEEE80211_TX_RC_USE_SHORT_PREAMBLE is used.
	 */
	अगर (tx_info->control.vअगर &&
	    tx_info->control.vअगर->bss_conf.use_लघु_preamble)
		लघु_preamble = true;

	rate = ieee80211_get_rts_cts_rate(hw, tx_info);
	keytype = ath9k_cmn_get_hw_crypto_keytype(skb);

	अगर (sta)
		an = (काष्ठा ath_node *) sta->drv_priv;

	अगर (tx_info->control.vअगर) अणु
		काष्ठा ieee80211_vअगर *vअगर = tx_info->control.vअगर;
		अगर (vअगर->bss_conf.txघातer == पूर्णांक_न्यून)
			जाओ nonvअगरघातer;
		txघातer = 2 * vअगर->bss_conf.txघातer;
	पूर्ण अन्यथा अणु
		काष्ठा ath_softc *sc;
	nonvअगरघातer:
		sc = hw->priv;

		txघातer = sc->cur_chan->cur_txघातer;
	पूर्ण

	स_रखो(fi, 0, माप(*fi));
	fi->txq = -1;
	अगर (hw_key)
		fi->keyix = hw_key->hw_key_idx;
	अन्यथा अगर (an && ieee80211_is_data(hdr->frame_control) && an->ps_key > 0)
		fi->keyix = an->ps_key;
	अन्यथा
		fi->keyix = ATH9K_TXKEYIX_INVALID;
	fi->dyn_smps = sta && sta->smps_mode == IEEE80211_SMPS_DYNAMIC;
	fi->keytype = keytype;
	fi->framelen = framelen;
	fi->tx_घातer = txघातer;

	अगर (!rate)
		वापस;
	fi->rtscts_rate = rate->hw_value;
	अगर (लघु_preamble)
		fi->rtscts_rate |= rate->hw_value_लघु;
पूर्ण

u8 ath_txchainmask_reduction(काष्ठा ath_softc *sc, u8 chainmask, u32 rate)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath9k_channel *curchan = ah->curchan;

	अगर ((ah->caps.hw_caps & ATH9K_HW_CAP_APM) && IS_CHAN_5GHZ(curchan) &&
	    (chainmask == 0x7) && (rate < 0x90))
		वापस 0x3;
	अन्यथा अगर (AR_SREV_9462(ah) && ath9k_hw_btcoex_is_enabled(ah) &&
		 IS_CCK_RATE(rate))
		वापस 0x2;
	अन्यथा
		वापस chainmask;
पूर्ण

/*
 * Assign a descriptor (and sequence number अगर necessary,
 * and map buffer क्रम DMA. Frees skb on error
 */
अटल काष्ठा ath_buf *ath_tx_setup_buffer(काष्ठा ath_softc *sc,
					   काष्ठा ath_txq *txq,
					   काष्ठा ath_atx_tid *tid,
					   काष्ठा sk_buff *skb)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_frame_info *fi = get_frame_info(skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ath_buf *bf;
	पूर्णांक fragno;
	u16 seqno;

	bf = ath_tx_get_buffer(sc);
	अगर (!bf) अणु
		ath_dbg(common, XMIT, "TX buffers are full\n");
		वापस शून्य;
	पूर्ण

	ATH_TXBUF_RESET(bf);

	अगर (tid && ieee80211_is_data_present(hdr->frame_control)) अणु
		fragno = le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_FRAG;
		seqno = tid->seq_next;
		hdr->seq_ctrl = cpu_to_le16(tid->seq_next << IEEE80211_SEQ_SEQ_SHIFT);

		अगर (fragno)
			hdr->seq_ctrl |= cpu_to_le16(fragno);

		अगर (!ieee80211_has_morefrags(hdr->frame_control))
			INCR(tid->seq_next, IEEE80211_SEQ_MAX);

		bf->bf_state.seqno = seqno;
	पूर्ण

	bf->bf_mpdu = skb;

	bf->bf_buf_addr = dma_map_single(sc->dev, skb->data,
					 skb->len, DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(sc->dev, bf->bf_buf_addr))) अणु
		bf->bf_mpdu = शून्य;
		bf->bf_buf_addr = 0;
		ath_err(ath9k_hw_common(sc->sc_ah),
			"dma_mapping_error() on TX\n");
		ath_tx_वापस_buffer(sc, bf);
		वापस शून्य;
	पूर्ण

	fi->bf = bf;

	वापस bf;
पूर्ण

व्योम ath_assign_seq(काष्ठा ath_common *common, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_vअगर *vअगर = info->control.vअगर;
	काष्ठा ath_vअगर *avp;

	अगर (!(info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ))
		वापस;

	अगर (!vअगर)
		वापस;

	avp = (काष्ठा ath_vअगर *)vअगर->drv_priv;

	अगर (info->flags & IEEE80211_TX_CTL_FIRST_FRAGMENT)
		avp->seq_no += 0x10;

	hdr->seq_ctrl &= cpu_to_le16(IEEE80211_SCTL_FRAG);
	hdr->seq_ctrl |= cpu_to_le16(avp->seq_no);
पूर्ण

अटल पूर्णांक ath_tx_prepare(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb,
			  काष्ठा ath_tx_control *txctl)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_sta *sta = txctl->sta;
	काष्ठा ieee80211_vअगर *vअगर = info->control.vअगर;
	काष्ठा ath_vअगर *avp;
	काष्ठा ath_softc *sc = hw->priv;
	पूर्णांक frmlen = skb->len + FCS_LEN;
	पूर्णांक padpos, padsize;

	/* NOTE:  sta can be शून्य according to net/mac80211.h */
	अगर (sta)
		txctl->an = (काष्ठा ath_node *)sta->drv_priv;
	अन्यथा अगर (vअगर && ieee80211_is_data(hdr->frame_control)) अणु
		avp = (व्योम *)vअगर->drv_priv;
		txctl->an = &avp->mcast_node;
	पूर्ण

	अगर (info->control.hw_key)
		frmlen += info->control.hw_key->icv_len;

	ath_assign_seq(ath9k_hw_common(sc->sc_ah), skb);

	अगर ((vअगर && vअगर->type != NL80211_IFTYPE_AP &&
	            vअगर->type != NL80211_IFTYPE_AP_VLAN) ||
	    !ieee80211_is_data(hdr->frame_control))
		info->flags |= IEEE80211_TX_CTL_CLEAR_PS_FILT;

	/* Add the padding after the header अगर this is not alपढ़ोy करोne */
	padpos = ieee80211_hdrlen(hdr->frame_control);
	padsize = padpos & 3;
	अगर (padsize && skb->len > padpos) अणु
		अगर (skb_headroom(skb) < padsize)
			वापस -ENOMEM;

		skb_push(skb, padsize);
		स_हटाओ(skb->data, skb->data + padsize, padpos);
	पूर्ण

	setup_frame_info(hw, sta, skb, frmlen);
	वापस 0;
पूर्ण


/* Upon failure caller should मुक्त skb */
पूर्णांक ath_tx_start(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb,
		 काष्ठा ath_tx_control *txctl)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_sta *sta = txctl->sta;
	काष्ठा ieee80211_vअगर *vअगर = info->control.vअगर;
	काष्ठा ath_frame_info *fi = get_frame_info(skb);
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_txq *txq = txctl->txq;
	काष्ठा ath_atx_tid *tid = शून्य;
	काष्ठा ath_node *an = शून्य;
	काष्ठा ath_buf *bf;
	bool ps_resp;
	पूर्णांक q, ret;

	ps_resp = !!(info->control.flags & IEEE80211_TX_CTRL_PS_RESPONSE);

	ret = ath_tx_prepare(hw, skb, txctl);
	अगर (ret)
	    वापस ret;

	/*
	 * At this poपूर्णांक, the vअगर, hw_key and sta poपूर्णांकers in the tx control
	 * info are no दीर्घer valid (overwritten by the ath_frame_info data.
	 */

	q = skb_get_queue_mapping(skb);

	अगर (ps_resp)
		txq = sc->tx.uapsdq;

	अगर (txctl->sta) अणु
		an = (काष्ठा ath_node *) sta->drv_priv;
		tid = ath_get_skb_tid(sc, an, skb);
	पूर्ण

	ath_txq_lock(sc, txq);
	अगर (txq == sc->tx.txq_map[q]) अणु
		fi->txq = q;
		++txq->pending_frames;
	पूर्ण

	bf = ath_tx_setup_buffer(sc, txq, tid, skb);
	अगर (!bf) अणु
		ath_txq_skb_करोne(sc, txq, skb);
		अगर (txctl->paprd)
			dev_kमुक्त_skb_any(skb);
		अन्यथा
			ieee80211_मुक्त_txskb(sc->hw, skb);
		जाओ out;
	पूर्ण

	bf->bf_state.bfs_paprd = txctl->paprd;

	अगर (txctl->paprd)
		bf->bf_state.bfs_paprd_बारtamp = jअगरfies;

	ath_set_rates(vअगर, sta, bf);
	ath_tx_send_normal(sc, txq, tid, skb);

out:
	ath_txq_unlock(sc, txq);

	वापस 0;
पूर्ण

व्योम ath_tx_cabq(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		 काष्ठा sk_buff *skb)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_tx_control txctl = अणु
		.txq = sc->beacon.cabq
	पूर्ण;
	काष्ठा ath_tx_info info = अणुपूर्ण;
	काष्ठा ath_buf *bf_tail = शून्य;
	काष्ठा ath_buf *bf;
	LIST_HEAD(bf_q);
	पूर्णांक duration = 0;
	पूर्णांक max_duration;

	max_duration =
		sc->cur_chan->beacon.beacon_पूर्णांकerval * 1000 *
		sc->cur_chan->beacon.dtim_period / ATH_BCBUF;

	करो अणु
		काष्ठा ath_frame_info *fi = get_frame_info(skb);

		अगर (ath_tx_prepare(hw, skb, &txctl))
			अवरोध;

		bf = ath_tx_setup_buffer(sc, txctl.txq, शून्य, skb);
		अगर (!bf)
			अवरोध;

		bf->bf_lastbf = bf;
		ath_set_rates(vअगर, शून्य, bf);
		ath_buf_set_rate(sc, bf, &info, fi->framelen, false);
		duration += info.rates[0].PktDuration;
		अगर (bf_tail)
			bf_tail->bf_next = bf;

		list_add_tail(&bf->list, &bf_q);
		bf_tail = bf;
		skb = शून्य;

		अगर (duration > max_duration)
			अवरोध;

		skb = ieee80211_get_buffered_bc(hw, vअगर);
	पूर्ण जबतक(skb);

	अगर (skb)
		ieee80211_मुक्त_txskb(hw, skb);

	अगर (list_empty(&bf_q))
		वापस;

	bf = list_last_entry(&bf_q, काष्ठा ath_buf, list);
	ath9k_set_moredata(sc, bf, false);

	bf = list_first_entry(&bf_q, काष्ठा ath_buf, list);
	ath_txq_lock(sc, txctl.txq);
	ath_tx_fill_desc(sc, bf, txctl.txq, 0);
	ath_tx_txqaddbuf(sc, txctl.txq, &bf_q, false);
	TX_STAT_INC(sc, txctl.txq->axq_qnum, queued);
	ath_txq_unlock(sc, txctl.txq);
पूर्ण

/*****************/
/* TX Completion */
/*****************/

अटल व्योम ath_tx_complete(काष्ठा ath_softc *sc, काष्ठा sk_buff *skb,
			    पूर्णांक tx_flags, काष्ठा ath_txq *txq,
			    काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ieee80211_hdr * hdr = (काष्ठा ieee80211_hdr *)skb->data;
	पूर्णांक padpos, padsize;
	अचिन्हित दीर्घ flags;

	ath_dbg(common, XMIT, "TX complete: skb: %p\n", skb);

	अगर (sc->sc_ah->caldata)
		set_bit(PAPRD_PACKET_SENT, &sc->sc_ah->caldata->cal_flags);

	अगर (!(tx_flags & ATH_TX_ERROR)) अणु
		अगर (tx_info->flags & IEEE80211_TX_CTL_NO_ACK)
			tx_info->flags |= IEEE80211_TX_STAT_NOACK_TRANSMITTED;
		अन्यथा
			tx_info->flags |= IEEE80211_TX_STAT_ACK;
	पूर्ण

	अगर (tx_info->flags & IEEE80211_TX_CTL_REQ_TX_STATUS) अणु
		padpos = ieee80211_hdrlen(hdr->frame_control);
		padsize = padpos & 3;
		अगर (padsize && skb->len>padpos+padsize) अणु
			/*
			 * Remove MAC header padding beक्रमe giving the frame back to
			 * mac80211.
			 */
			स_हटाओ(skb->data + padsize, skb->data, padpos);
			skb_pull(skb, padsize);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&sc->sc_pm_lock, flags);
	अगर ((sc->ps_flags & PS_WAIT_FOR_TX_ACK) && !txq->axq_depth) अणु
		sc->ps_flags &= ~PS_WAIT_FOR_TX_ACK;
		ath_dbg(common, PS,
			"Going back to sleep after having received TX status (0x%lx)\n",
			sc->ps_flags & (PS_WAIT_FOR_BEACON |
					PS_WAIT_FOR_CAB |
					PS_WAIT_FOR_PSPOLL_DATA |
					PS_WAIT_FOR_TX_ACK));
	पूर्ण
	spin_unlock_irqrestore(&sc->sc_pm_lock, flags);

	ath_txq_skb_करोne(sc, txq, skb);
	tx_info->status.status_driver_data[0] = sta;
	__skb_queue_tail(&txq->complete_q, skb);
पूर्ण

अटल व्योम ath_tx_complete_buf(काष्ठा ath_softc *sc, काष्ठा ath_buf *bf,
				काष्ठा ath_txq *txq, काष्ठा list_head *bf_q,
				काष्ठा ieee80211_sta *sta,
				काष्ठा ath_tx_status *ts, पूर्णांक txok)
अणु
	काष्ठा sk_buff *skb = bf->bf_mpdu;
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	अचिन्हित दीर्घ flags;
	पूर्णांक tx_flags = 0;

	अगर (!txok)
		tx_flags |= ATH_TX_ERROR;

	अगर (ts->ts_status & ATH9K_TXERR_FILT)
		tx_info->flags |= IEEE80211_TX_STAT_TX_FILTERED;

	dma_unmap_single(sc->dev, bf->bf_buf_addr, skb->len, DMA_TO_DEVICE);
	bf->bf_buf_addr = 0;
	अगर (sc->tx99_state)
		जाओ skip_tx_complete;

	अगर (bf->bf_state.bfs_paprd) अणु
		अगर (समय_after(jअगरfies,
				bf->bf_state.bfs_paprd_बारtamp +
				msecs_to_jअगरfies(ATH_PAPRD_TIMEOUT)))
			dev_kमुक्त_skb_any(skb);
		अन्यथा
			complete(&sc->paprd_complete);
	पूर्ण अन्यथा अणु
		ath_debug_stat_tx(sc, bf, ts, txq, tx_flags);
		ath_tx_complete(sc, skb, tx_flags, txq, sta);
	पूर्ण
skip_tx_complete:
	/* At this poपूर्णांक, skb (bf->bf_mpdu) is consumed...make sure we करोn't
	 * accidentally reference it later.
	 */
	bf->bf_mpdu = शून्य;

	/*
	 * Return the list of ath_buf of this mpdu to मुक्त queue
	 */
	spin_lock_irqsave(&sc->tx.txbuflock, flags);
	list_splice_tail_init(bf_q, &sc->tx.txbuf);
	spin_unlock_irqrestore(&sc->tx.txbuflock, flags);
पूर्ण

अटल व्योम ath_tx_rc_status(काष्ठा ath_softc *sc, काष्ठा ath_buf *bf,
			     काष्ठा ath_tx_status *ts, पूर्णांक nframes, पूर्णांक nbad,
			     पूर्णांक txok)
अणु
	काष्ठा sk_buff *skb = bf->bf_mpdu;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hw *hw = sc->hw;
	काष्ठा ath_hw *ah = sc->sc_ah;
	u8 i, tx_rateindex;

	अगर (txok)
		tx_info->status.ack_संकेत = ts->ts_rssi;

	tx_rateindex = ts->ts_rateindex;
	WARN_ON(tx_rateindex >= hw->max_rates);

	अगर (tx_info->flags & IEEE80211_TX_CTL_AMPDU) अणु
		tx_info->flags |= IEEE80211_TX_STAT_AMPDU;

		BUG_ON(nbad > nframes);
	पूर्ण
	tx_info->status.ampdu_len = nframes;
	tx_info->status.ampdu_ack_len = nframes - nbad;

	अगर ((ts->ts_status & ATH9K_TXERR_FILT) == 0 &&
	    (tx_info->flags & IEEE80211_TX_CTL_NO_ACK) == 0) अणु
		/*
		 * If an underrun error is seen assume it as an excessive
		 * retry only अगर max frame trigger level has been reached
		 * (2 KB क्रम single stream, and 4 KB क्रम dual stream).
		 * Adjust the दीर्घ retry as अगर the frame was tried
		 * hw->max_rate_tries बार to affect how rate control updates
		 * PER क्रम the failed rate.
		 * In हाल of congestion on the bus penalizing this type of
		 * underruns should help hardware actually transmit new frames
		 * successfully by eventually preferring slower rates.
		 * This itself should also alleviate congestion on the bus.
		 */
		अगर (unlikely(ts->ts_flags & (ATH9K_TX_DATA_UNDERRUN |
		                             ATH9K_TX_DELIM_UNDERRUN)) &&
		    ieee80211_is_data(hdr->frame_control) &&
		    ah->tx_trig_level >= sc->sc_ah->config.max_txtrig_level)
			tx_info->status.rates[tx_rateindex].count =
				hw->max_rate_tries;
	पूर्ण

	क्रम (i = tx_rateindex + 1; i < hw->max_rates; i++) अणु
		tx_info->status.rates[i].count = 0;
		tx_info->status.rates[i].idx = -1;
	पूर्ण

	tx_info->status.rates[tx_rateindex].count = ts->ts_दीर्घretry + 1;

	/* we report airसमय in ath_tx_count_airसमय(), करोn't report twice */
	tx_info->status.tx_समय = 0;
पूर्ण

अटल व्योम ath_tx_processq(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath_buf *bf, *lastbf, *bf_held = शून्य;
	काष्ठा list_head bf_head;
	काष्ठा ath_desc *ds;
	काष्ठा ath_tx_status ts;
	पूर्णांक status;

	ath_dbg(common, QUEUE, "tx queue %d (%x), link %p\n",
		txq->axq_qnum, ath9k_hw_gettxbuf(sc->sc_ah, txq->axq_qnum),
		txq->axq_link);

	ath_txq_lock(sc, txq);
	क्रम (;;) अणु
		अगर (test_bit(ATH_OP_HW_RESET, &common->op_flags))
			अवरोध;

		अगर (list_empty(&txq->axq_q)) अणु
			txq->axq_link = शून्य;
			ath_txq_schedule(sc, txq);
			अवरोध;
		पूर्ण
		bf = list_first_entry(&txq->axq_q, काष्ठा ath_buf, list);

		/*
		 * There is a race condition that a BH माला_लो scheduled
		 * after sw ग_लिखोs TxE and beक्रमe hw re-load the last
		 * descriptor to get the newly chained one.
		 * Software must keep the last DONE descriptor as a
		 * holding descriptor - software करोes so by marking
		 * it with the STALE flag.
		 */
		bf_held = शून्य;
		अगर (bf->bf_state.stale) अणु
			bf_held = bf;
			अगर (list_is_last(&bf_held->list, &txq->axq_q))
				अवरोध;

			bf = list_entry(bf_held->list.next, काष्ठा ath_buf,
					list);
		पूर्ण

		lastbf = bf->bf_lastbf;
		ds = lastbf->bf_desc;

		स_रखो(&ts, 0, माप(ts));
		status = ath9k_hw_txprocdesc(ah, ds, &ts);
		अगर (status == -EINPROGRESS)
			अवरोध;

		TX_STAT_INC(sc, txq->axq_qnum, txprocdesc);

		/*
		 * Remove ath_buf's of the same transmit unit from txq,
		 * however leave the last descriptor back as the holding
		 * descriptor क्रम hw.
		 */
		lastbf->bf_state.stale = true;
		INIT_LIST_HEAD(&bf_head);
		अगर (!list_is_singular(&lastbf->list))
			list_cut_position(&bf_head,
				&txq->axq_q, lastbf->list.prev);

		अगर (bf_held) अणु
			list_del(&bf_held->list);
			ath_tx_वापस_buffer(sc, bf_held);
		पूर्ण

		ath_tx_process_buffer(sc, txq, &ts, bf, &bf_head);
	पूर्ण
	ath_txq_unlock_complete(sc, txq);
पूर्ण

व्योम ath_tx_tasklet(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	u32 qcumask = ((1 << ATH9K_NUM_TX_QUEUES) - 1) & ah->पूर्णांकr_txqs;
	पूर्णांक i;

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < ATH9K_NUM_TX_QUEUES; i++) अणु
		अगर (ATH_TXQ_SETUP(sc, i) && (qcumask & (1 << i)))
			ath_tx_processq(sc, &sc->tx.txq[i]);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

व्योम ath_tx_edma_tasklet(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_tx_status ts;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_txq *txq;
	काष्ठा ath_buf *bf, *lastbf;
	काष्ठा list_head bf_head;
	काष्ठा list_head *fअगरo_list;
	पूर्णांक status;

	rcu_पढ़ो_lock();
	क्रम (;;) अणु
		अगर (test_bit(ATH_OP_HW_RESET, &common->op_flags))
			अवरोध;

		status = ath9k_hw_txprocdesc(ah, शून्य, (व्योम *)&ts);
		अगर (status == -EINPROGRESS)
			अवरोध;
		अगर (status == -EIO) अणु
			ath_dbg(common, XMIT, "Error processing tx status\n");
			अवरोध;
		पूर्ण

		/* Process beacon completions separately */
		अगर (ts.qid == sc->beacon.beaconq) अणु
			sc->beacon.tx_processed = true;
			sc->beacon.tx_last = !(ts.ts_status & ATH9K_TXERR_MASK);

			अगर (ath9k_is_chanctx_enabled()) अणु
				ath_chanctx_event(sc, शून्य,
						  ATH_CHANCTX_EVENT_BEACON_SENT);
			पूर्ण

			ath9k_csa_update(sc);
			जारी;
		पूर्ण

		txq = &sc->tx.txq[ts.qid];

		ath_txq_lock(sc, txq);

		TX_STAT_INC(sc, txq->axq_qnum, txprocdesc);

		fअगरo_list = &txq->txq_fअगरo[txq->txq_tailidx];
		अगर (list_empty(fअगरo_list)) अणु
			ath_txq_unlock(sc, txq);
			अवरोध;
		पूर्ण

		bf = list_first_entry(fअगरo_list, काष्ठा ath_buf, list);
		अगर (bf->bf_state.stale) अणु
			list_del(&bf->list);
			ath_tx_वापस_buffer(sc, bf);
			bf = list_first_entry(fअगरo_list, काष्ठा ath_buf, list);
		पूर्ण

		lastbf = bf->bf_lastbf;

		INIT_LIST_HEAD(&bf_head);
		अगर (list_is_last(&lastbf->list, fअगरo_list)) अणु
			list_splice_tail_init(fअगरo_list, &bf_head);
			INCR(txq->txq_tailidx, ATH_TXFIFO_DEPTH);

			अगर (!list_empty(&txq->axq_q)) अणु
				काष्ठा list_head bf_q;

				INIT_LIST_HEAD(&bf_q);
				txq->axq_link = शून्य;
				list_splice_tail_init(&txq->axq_q, &bf_q);
				ath_tx_txqaddbuf(sc, txq, &bf_q, true);
			पूर्ण
		पूर्ण अन्यथा अणु
			lastbf->bf_state.stale = true;
			अगर (bf != lastbf)
				list_cut_position(&bf_head, fअगरo_list,
						  lastbf->list.prev);
		पूर्ण

		ath_tx_process_buffer(sc, txq, &ts, bf, &bf_head);
		ath_txq_unlock_complete(sc, txq);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/*****************/
/* Init, Cleanup */
/*****************/

अटल पूर्णांक ath_txstatus_setup(काष्ठा ath_softc *sc, पूर्णांक size)
अणु
	काष्ठा ath_descdma *dd = &sc->txsdma;
	u8 txs_len = sc->sc_ah->caps.txs_len;

	dd->dd_desc_len = size * txs_len;
	dd->dd_desc = dmam_alloc_coherent(sc->dev, dd->dd_desc_len,
					  &dd->dd_desc_paddr, GFP_KERNEL);
	अगर (!dd->dd_desc)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक ath_tx_edma_init(काष्ठा ath_softc *sc)
अणु
	पूर्णांक err;

	err = ath_txstatus_setup(sc, ATH_TXSTATUS_RING_SIZE);
	अगर (!err)
		ath9k_hw_setup_statusring(sc->sc_ah, sc->txsdma.dd_desc,
					  sc->txsdma.dd_desc_paddr,
					  ATH_TXSTATUS_RING_SIZE);

	वापस err;
पूर्ण

पूर्णांक ath_tx_init(काष्ठा ath_softc *sc, पूर्णांक nbufs)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	पूर्णांक error = 0;

	spin_lock_init(&sc->tx.txbuflock);

	error = ath_descdma_setup(sc, &sc->tx.txdma, &sc->tx.txbuf,
				  "tx", nbufs, 1, 1);
	अगर (error != 0) अणु
		ath_err(common,
			"Failed to allocate tx descriptors: %d\n", error);
		वापस error;
	पूर्ण

	error = ath_descdma_setup(sc, &sc->beacon.bdma, &sc->beacon.bbuf,
				  "beacon", ATH_BCBUF, 1, 1);
	अगर (error != 0) अणु
		ath_err(common,
			"Failed to allocate beacon descriptors: %d\n", error);
		वापस error;
	पूर्ण

	अगर (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA)
		error = ath_tx_edma_init(sc);

	वापस error;
पूर्ण

व्योम ath_tx_node_init(काष्ठा ath_softc *sc, काष्ठा ath_node *an)
अणु
	काष्ठा ath_atx_tid *tid;
	पूर्णांक tidno, acno;

	क्रम (tidno = 0; tidno < IEEE80211_NUM_TIDS; tidno++) अणु
		tid = ath_node_to_tid(an, tidno);
		tid->an        = an;
		tid->tidno     = tidno;
		tid->seq_start = tid->seq_next = 0;
		tid->baw_size  = WME_MAX_BA;
		tid->baw_head  = tid->baw_tail = 0;
		tid->active	   = false;
		tid->clear_ps_filter = true;
		__skb_queue_head_init(&tid->retry_q);
		INIT_LIST_HEAD(&tid->list);
		acno = TID_TO_WME_AC(tidno);
		tid->txq = sc->tx.txq_map[acno];

		अगर (!an->sta)
			अवरोध; /* just one multicast ath_atx_tid */
	पूर्ण
पूर्ण

व्योम ath_tx_node_cleanup(काष्ठा ath_softc *sc, काष्ठा ath_node *an)
अणु
	काष्ठा ath_atx_tid *tid;
	काष्ठा ath_txq *txq;
	पूर्णांक tidno;

	rcu_पढ़ो_lock();

	क्रम (tidno = 0; tidno < IEEE80211_NUM_TIDS; tidno++) अणु
		tid = ath_node_to_tid(an, tidno);
		txq = tid->txq;

		ath_txq_lock(sc, txq);

		अगर (!list_empty(&tid->list))
			list_del_init(&tid->list);

		ath_tid_drain(sc, txq, tid);
		tid->active = false;

		ath_txq_unlock(sc, txq);

		अगर (!an->sta)
			अवरोध; /* just one multicast ath_atx_tid */
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

#अगर_घोषित CONFIG_ATH9K_TX99

पूर्णांक ath9k_tx99_send(काष्ठा ath_softc *sc, काष्ठा sk_buff *skb,
		    काष्ठा ath_tx_control *txctl)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	काष्ठा ath_frame_info *fi = get_frame_info(skb);
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_buf *bf;
	पूर्णांक padpos, padsize;

	padpos = ieee80211_hdrlen(hdr->frame_control);
	padsize = padpos & 3;

	अगर (padsize && skb->len > padpos) अणु
		अगर (skb_headroom(skb) < padsize) अणु
			ath_dbg(common, XMIT,
				"tx99 padding failed\n");
			वापस -EINVAL;
		पूर्ण

		skb_push(skb, padsize);
		स_हटाओ(skb->data, skb->data + padsize, padpos);
	पूर्ण

	fi->keyix = ATH9K_TXKEYIX_INVALID;
	fi->framelen = skb->len + FCS_LEN;
	fi->keytype = ATH9K_KEY_TYPE_CLEAR;

	bf = ath_tx_setup_buffer(sc, txctl->txq, शून्य, skb);
	अगर (!bf) अणु
		ath_dbg(common, XMIT, "tx99 buffer setup failed\n");
		वापस -EINVAL;
	पूर्ण

	ath_set_rates(sc->tx99_vअगर, शून्य, bf);

	ath9k_hw_set_desc_link(sc->sc_ah, bf->bf_desc, bf->bf_daddr);
	ath9k_hw_tx99_start(sc->sc_ah, txctl->txq->axq_qnum);

	ath_tx_send_normal(sc, txctl->txq, शून्य, skb);

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_ATH9K_TX99 */
