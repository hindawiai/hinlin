<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश <linux/kernel.h>

#समावेश "mt76x02.h"

व्योम mt76x02_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_tx_control *control,
		काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा mt76x02_dev *dev = hw->priv;
	काष्ठा ieee80211_vअगर *vअगर = info->control.vअगर;
	काष्ठा mt76_wcid *wcid = &dev->mt76.global_wcid;

	अगर (control->sta) अणु
		काष्ठा mt76x02_sta *msta;

		msta = (काष्ठा mt76x02_sta *)control->sta->drv_priv;
		wcid = &msta->wcid;
	पूर्ण अन्यथा अगर (vअगर) अणु
		काष्ठा mt76x02_vअगर *mvअगर;

		mvअगर = (काष्ठा mt76x02_vअगर *)vअगर->drv_priv;
		wcid = &mvअगर->group_wcid;
	पूर्ण

	mt76_tx(&dev->mphy, control->sta, wcid, skb);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_tx);

व्योम mt76x02_queue_rx_skb(काष्ठा mt76_dev *mdev, क्रमागत mt76_rxq_id q,
			  काष्ठा sk_buff *skb)
अणु
	काष्ठा mt76x02_dev *dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);
	व्योम *rxwi = skb->data;

	अगर (q == MT_RXQ_MCU) अणु
		mt76_mcu_rx_event(&dev->mt76, skb);
		वापस;
	पूर्ण

	skb_pull(skb, माप(काष्ठा mt76x02_rxwi));
	अगर (mt76x02_mac_process_rx(dev, skb, rxwi)) अणु
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	mt76_rx(mdev, q, skb);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_queue_rx_skb);

s8 mt76x02_tx_get_max_txpwr_adj(काष्ठा mt76x02_dev *dev,
				स्थिर काष्ठा ieee80211_tx_rate *rate)
अणु
	s8 max_txpwr;

	अगर (rate->flags & IEEE80211_TX_RC_VHT_MCS) अणु
		u8 mcs = ieee80211_rate_get_vht_mcs(rate);

		अगर (mcs == 8 || mcs == 9) अणु
			max_txpwr = dev->mt76.rate_घातer.vht[8];
		पूर्ण अन्यथा अणु
			u8 nss, idx;

			nss = ieee80211_rate_get_vht_nss(rate);
			idx = ((nss - 1) << 3) + mcs;
			max_txpwr = dev->mt76.rate_घातer.ht[idx & 0xf];
		पूर्ण
	पूर्ण अन्यथा अगर (rate->flags & IEEE80211_TX_RC_MCS) अणु
		max_txpwr = dev->mt76.rate_घातer.ht[rate->idx & 0xf];
	पूर्ण अन्यथा अणु
		क्रमागत nl80211_band band = dev->mphy.chandef.chan->band;

		अगर (band == NL80211_BAND_2GHZ) अणु
			स्थिर काष्ठा ieee80211_rate *r;
			काष्ठा wiphy *wiphy = dev->mt76.hw->wiphy;
			काष्ठा mt76_rate_घातer *rp = &dev->mt76.rate_घातer;

			r = &wiphy->bands[band]->bitrates[rate->idx];
			अगर (r->flags & IEEE80211_RATE_SHORT_PREAMBLE)
				max_txpwr = rp->cck[r->hw_value & 0x3];
			अन्यथा
				max_txpwr = rp->ofdm[r->hw_value & 0x7];
		पूर्ण अन्यथा अणु
			max_txpwr = dev->mt76.rate_घातer.ofdm[rate->idx & 0x7];
		पूर्ण
	पूर्ण

	वापस max_txpwr;
पूर्ण

s8 mt76x02_tx_get_txpwr_adj(काष्ठा mt76x02_dev *dev, s8 txpwr, s8 max_txpwr_adj)
अणु
	txpwr = min_t(s8, txpwr, dev->txघातer_conf);
	txpwr -= (dev->target_घातer + dev->target_घातer_delta[0]);
	txpwr = min_t(s8, txpwr, max_txpwr_adj);

	अगर (!dev->enable_tpc)
		वापस 0;
	अन्यथा अगर (txpwr >= 0)
		वापस min_t(s8, txpwr, 7);
	अन्यथा
		वापस (txpwr < -16) ? 8 : (txpwr + 32) / 2;
पूर्ण

व्योम mt76x02_tx_set_txpwr_स्वतः(काष्ठा mt76x02_dev *dev, s8 txpwr)
अणु
	s8 txpwr_adj;

	txpwr_adj = mt76x02_tx_get_txpwr_adj(dev, txpwr,
					     dev->mt76.rate_घातer.ofdm[4]);
	mt76_rmw_field(dev, MT_PROT_AUTO_TX_CFG,
		       MT_PROT_AUTO_TX_CFG_PROT_PADJ, txpwr_adj);
	mt76_rmw_field(dev, MT_PROT_AUTO_TX_CFG,
		       MT_PROT_AUTO_TX_CFG_AUTO_PADJ, txpwr_adj);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_tx_set_txpwr_स्वतः);

bool mt76x02_tx_status_data(काष्ठा mt76_dev *mdev, u8 *update)
अणु
	काष्ठा mt76x02_dev *dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);
	काष्ठा mt76x02_tx_status stat;

	अगर (!mt76x02_mac_load_tx_status(dev, &stat))
		वापस false;

	mt76x02_send_tx_status(dev, &stat, update);

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_tx_status_data);

पूर्णांक mt76x02_tx_prepare_skb(काष्ठा mt76_dev *mdev, व्योम *txwi_ptr,
			   क्रमागत mt76_txq_id qid, काष्ठा mt76_wcid *wcid,
			   काष्ठा ieee80211_sta *sta,
			   काष्ठा mt76_tx_info *tx_info)
अणु
	काष्ठा mt76x02_dev *dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)tx_info->skb->data;
	काष्ठा mt76x02_txwi *txwi = txwi_ptr;
	bool ampdu = IEEE80211_SKB_CB(tx_info->skb)->flags & IEEE80211_TX_CTL_AMPDU;
	पूर्णांक hdrlen, len, pid, qsel = MT_QSEL_EDCA;

	अगर (qid == MT_TXQ_PSD && wcid && wcid->idx < 128)
		mt76x02_mac_wcid_set_drop(dev, wcid->idx, false);

	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	len = tx_info->skb->len - (hdrlen & 2);
	mt76x02_mac_ग_लिखो_txwi(dev, txwi, tx_info->skb, wcid, sta, len);

	pid = mt76_tx_status_skb_add(mdev, wcid, tx_info->skb);

	/* encode packet rate क्रम no-skb packet id to fix up status reporting */
	अगर (pid == MT_PACKET_ID_NO_SKB)
		pid = MT_PACKET_ID_HAS_RATE |
		      (le16_to_cpu(txwi->rate) & MT_RXWI_RATE_INDEX) |
		      FIELD_PREP(MT_PKTID_AC,
				 skb_get_queue_mapping(tx_info->skb));

	txwi->pktid = pid;

	अगर (mt76_is_skb_pktid(pid) && ampdu)
		qsel = MT_QSEL_MGMT;

	tx_info->info = FIELD_PREP(MT_TXD_INFO_QSEL, qsel) |
			MT_TXD_INFO_80211;

	अगर (!wcid || wcid->hw_key_idx == 0xff || wcid->sw_iv)
		tx_info->info |= MT_TXD_INFO_WIV;

	अगर (sta) अणु
		काष्ठा mt76x02_sta *msta = (काष्ठा mt76x02_sta *)sta->drv_priv;

		ewma_pktlen_add(&msta->pktlen, tx_info->skb->len);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_tx_prepare_skb);
