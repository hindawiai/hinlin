<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश "mt76x02_usb.h"

अटल व्योम mt76x02u_हटाओ_dma_hdr(काष्ठा sk_buff *skb)
अणु
	पूर्णांक hdr_len;

	skb_pull(skb, माप(काष्ठा mt76x02_txwi) + MT_DMA_HDR_LEN);
	hdr_len = ieee80211_get_hdrlen_from_skb(skb);
	अगर (hdr_len % 4)
		mt76x02_हटाओ_hdr_pad(skb, 2);
पूर्ण

व्योम mt76x02u_tx_complete_skb(काष्ठा mt76_dev *mdev, काष्ठा mt76_queue_entry *e)
अणु
	mt76x02u_हटाओ_dma_hdr(e->skb);
	mt76_tx_complete_skb(mdev, e->wcid, e->skb);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02u_tx_complete_skb);

पूर्णांक mt76x02u_mac_start(काष्ठा mt76x02_dev *dev)
अणु
	mt76x02_mac_reset_counters(dev);

	mt76_wr(dev, MT_MAC_SYS_CTRL, MT_MAC_SYS_CTRL_ENABLE_TX);
	अगर (!mt76x02_रुको_क्रम_wpdma(&dev->mt76, 200000))
		वापस -ETIMEDOUT;

	mt76_wr(dev, MT_RX_FILTR_CFG, dev->mt76.rxfilter);

	mt76_wr(dev, MT_MAC_SYS_CTRL,
		MT_MAC_SYS_CTRL_ENABLE_TX |
		MT_MAC_SYS_CTRL_ENABLE_RX);

	अगर (!mt76x02_रुको_क्रम_wpdma(&dev->mt76, 50))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02u_mac_start);

पूर्णांक mt76x02u_skb_dma_info(काष्ठा sk_buff *skb, पूर्णांक port, u32 flags)
अणु
	u32 info, pad;

	/* Buffer layout:
	 *	|   4B   | xfer len |      pad       |  4B  |
	 *	| TXINFO | pkt/cmd  | zero pad to 4B | zero |
	 *
	 * length field of TXINFO should be set to 'xfer len'.
	 */
	info = FIELD_PREP(MT_TXD_INFO_LEN, round_up(skb->len, 4)) |
	       FIELD_PREP(MT_TXD_INFO_DPORT, port) | flags;
	put_unaligned_le32(info, skb_push(skb, माप(info)));

	pad = round_up(skb->len, 4) + 4 - skb->len;
	वापस mt76_skb_adjust_pad(skb, pad);
पूर्ण

पूर्णांक mt76x02u_tx_prepare_skb(काष्ठा mt76_dev *mdev, व्योम *data,
			    क्रमागत mt76_txq_id qid, काष्ठा mt76_wcid *wcid,
			    काष्ठा ieee80211_sta *sta,
			    काष्ठा mt76_tx_info *tx_info)
अणु
	काष्ठा mt76x02_dev *dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);
	पूर्णांक pid, len = tx_info->skb->len, ep = q2ep(dev->mphy.q_tx[qid]->hw_idx);
	काष्ठा mt76x02_txwi *txwi;
	bool ampdu = IEEE80211_SKB_CB(tx_info->skb)->flags & IEEE80211_TX_CTL_AMPDU;
	क्रमागत mt76_qsel qsel;
	u32 flags;

	mt76_insert_hdr_pad(tx_info->skb);

	txwi = (काष्ठा mt76x02_txwi *)(tx_info->skb->data - माप(*txwi));
	mt76x02_mac_ग_लिखो_txwi(dev, txwi, tx_info->skb, wcid, sta, len);
	skb_push(tx_info->skb, माप(*txwi));

	pid = mt76_tx_status_skb_add(mdev, wcid, tx_info->skb);

	/* encode packet rate क्रम no-skb packet id to fix up status reporting */
	अगर (pid == MT_PACKET_ID_NO_SKB)
		pid = MT_PACKET_ID_HAS_RATE |
		      (le16_to_cpu(txwi->rate) & MT_PKTID_RATE) |
		      FIELD_PREP(MT_PKTID_AC,
				 skb_get_queue_mapping(tx_info->skb));

	txwi->pktid = pid;

	अगर ((mt76_is_skb_pktid(pid) && ampdu) || ep == MT_EP_OUT_HCCA)
		qsel = MT_QSEL_MGMT;
	अन्यथा
		qsel = MT_QSEL_EDCA;

	flags = FIELD_PREP(MT_TXD_INFO_QSEL, qsel) |
		MT_TXD_INFO_80211;
	अगर (!wcid || wcid->hw_key_idx == 0xff || wcid->sw_iv)
		flags |= MT_TXD_INFO_WIV;

	अगर (sta) अणु
		काष्ठा mt76x02_sta *msta = (काष्ठा mt76x02_sta *)sta->drv_priv;

		ewma_pktlen_add(&msta->pktlen, tx_info->skb->len);
	पूर्ण

	वापस mt76x02u_skb_dma_info(tx_info->skb, WLAN_PORT, flags);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02u_tx_prepare_skb);

/* Trigger pre-TBTT event 8 ms beक्रमe TBTT */
#घोषणा PRE_TBTT_USEC 8000

/* Beacon SRAM memory is limited to 8kB. We need to send PS buffered frames
 * (which can be 1500 bytes big) via beacon memory. That make limit of number
 * of slots to 5. TODO: dynamically calculate offsets in beacon SRAM.
 */
#घोषणा N_BCN_SLOTS 5

अटल व्योम mt76x02u_start_pre_tbtt_समयr(काष्ठा mt76x02_dev *dev)
अणु
	u64 समय;
	u32 tbtt;

	/* Get reमुख्यing TBTT in usec */
	tbtt = mt76_get_field(dev, MT_TBTT_TIMER, MT_TBTT_TIMER_VAL);
	tbtt *= 32;

	अगर (tbtt <= PRE_TBTT_USEC) अणु
		queue_work(प्रणाली_highpri_wq, &dev->pre_tbtt_work);
		वापस;
	पूर्ण

	समय = (tbtt - PRE_TBTT_USEC) * 1000ull;
	hrसमयr_start(&dev->pre_tbtt_समयr, समय, HRTIMER_MODE_REL);
पूर्ण

अटल व्योम mt76x02u_restart_pre_tbtt_समयr(काष्ठा mt76x02_dev *dev)
अणु
	u32 tbtt, dw0, dw1;
	u64 tsf, समय;

	/* Get reमुख्यing TBTT in usec */
	tbtt = mt76_get_field(dev, MT_TBTT_TIMER, MT_TBTT_TIMER_VAL);
	tbtt *= 32;

	dw0 = mt76_rr(dev, MT_TSF_TIMER_DW0);
	dw1 = mt76_rr(dev, MT_TSF_TIMER_DW1);
	tsf = (u64)dw0 << 32 | dw1;
	dev_dbg(dev->mt76.dev, "TSF: %llu us TBTT %u us\n", tsf, tbtt);

	/* Convert beacon पूर्णांकerval in TU (1024 usec) to nsec */
	समय = ((1000000000ull * dev->mt76.beacon_पूर्णांक) >> 10);

	/* Adjust समय to trigger hrसमयr 8ms beक्रमe TBTT */
	अगर (tbtt < PRE_TBTT_USEC)
		समय -= (PRE_TBTT_USEC - tbtt) * 1000ull;
	अन्यथा
		समय += (tbtt - PRE_TBTT_USEC) * 1000ull;

	hrसमयr_start(&dev->pre_tbtt_समयr, समय, HRTIMER_MODE_REL);
पूर्ण

अटल व्योम mt76x02u_stop_pre_tbtt_समयr(काष्ठा mt76x02_dev *dev)
अणु
	करो अणु
		hrसमयr_cancel(&dev->pre_tbtt_समयr);
		cancel_work_sync(&dev->pre_tbtt_work);
		/* Timer can be rearmed by work. */
	पूर्ण जबतक (hrसमयr_active(&dev->pre_tbtt_समयr));
पूर्ण

अटल व्योम mt76x02u_pre_tbtt_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt76x02_dev *dev =
		container_of(work, काष्ठा mt76x02_dev, pre_tbtt_work);
	काष्ठा beacon_bc_data data = अणुपूर्ण;
	काष्ठा sk_buff *skb;
	पूर्णांक nbeacons;

	अगर (!dev->mt76.beacon_mask)
		वापस;

	अगर (mt76_hw(dev)->conf.flags & IEEE80211_CONF_OFFCHANNEL)
		वापस;

	mt76x02_resync_beacon_समयr(dev);

	/* Prevent corrupt transmissions during update */
	mt76_set(dev, MT_BCN_BYPASS_MASK, 0xffff);
	dev->beacon_data_count = 0;

	ieee80211_iterate_active_पूर्णांकerfaces(mt76_hw(dev),
		IEEE80211_IFACE_ITER_RESUME_ALL,
		mt76x02_update_beacon_iter, dev);

	mt76_csa_check(&dev->mt76);

	अगर (dev->mt76.csa_complete) अणु
		mt76_csa_finish(&dev->mt76);
		जाओ out;
	पूर्ण

	nbeacons = hweight8(dev->mt76.beacon_mask);
	mt76x02_enqueue_buffered_bc(dev, &data, N_BCN_SLOTS - nbeacons);

	जबतक ((skb = __skb_dequeue(&data.q)) != शून्य)
		mt76x02_mac_set_beacon(dev, skb);

out:
	mt76_wr(dev, MT_BCN_BYPASS_MASK,
		0xff00 | ~(0xff00 >> dev->beacon_data_count));

	mt76x02u_restart_pre_tbtt_समयr(dev);
पूर्ण

अटल क्रमागत hrसमयr_restart mt76x02u_pre_tbtt_पूर्णांकerrupt(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा mt76x02_dev *dev =
	    container_of(समयr, काष्ठा mt76x02_dev, pre_tbtt_समयr);

	queue_work(प्रणाली_highpri_wq, &dev->pre_tbtt_work);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल व्योम mt76x02u_pre_tbtt_enable(काष्ठा mt76x02_dev *dev, bool en)
अणु
	अगर (en && dev->mt76.beacon_mask &&
	    !hrसमयr_active(&dev->pre_tbtt_समयr))
		mt76x02u_start_pre_tbtt_समयr(dev);
	अगर (!en)
		mt76x02u_stop_pre_tbtt_समयr(dev);
पूर्ण

अटल व्योम mt76x02u_beacon_enable(काष्ठा mt76x02_dev *dev, bool en)
अणु
	अगर (WARN_ON_ONCE(!dev->mt76.beacon_पूर्णांक))
		वापस;

	अगर (en)
		mt76x02u_start_pre_tbtt_समयr(dev);
पूर्ण

व्योम mt76x02u_init_beacon_config(काष्ठा mt76x02_dev *dev)
अणु
	अटल स्थिर काष्ठा mt76x02_beacon_ops beacon_ops = अणु
		.nslots = N_BCN_SLOTS,
		.slot_size = (8192 / N_BCN_SLOTS) & ~63,
		.pre_tbtt_enable = mt76x02u_pre_tbtt_enable,
		.beacon_enable = mt76x02u_beacon_enable,
	पूर्ण;
	dev->beacon_ops = &beacon_ops;

	hrसमयr_init(&dev->pre_tbtt_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	dev->pre_tbtt_समयr.function = mt76x02u_pre_tbtt_पूर्णांकerrupt;
	INIT_WORK(&dev->pre_tbtt_work, mt76x02u_pre_tbtt_work);

	mt76x02_init_beacon_config(dev);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02u_init_beacon_config);

व्योम mt76x02u_निकास_beacon_config(काष्ठा mt76x02_dev *dev)
अणु
	अगर (!test_bit(MT76_REMOVED, &dev->mphy.state))
		mt76_clear(dev, MT_BEACON_TIME_CFG,
			   MT_BEACON_TIME_CFG_TIMER_EN |
			   MT_BEACON_TIME_CFG_SYNC_MODE |
			   MT_BEACON_TIME_CFG_TBTT_EN |
			   MT_BEACON_TIME_CFG_BEACON_TX);

	mt76x02u_stop_pre_tbtt_समयr(dev);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02u_निकास_beacon_config);
