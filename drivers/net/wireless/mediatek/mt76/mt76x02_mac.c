<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 * Copyright (C) 2018 Stanislaw Gruszka <stf_xl@wp.pl>
 */

#समावेश "mt76x02.h"
#समावेश "mt76x02_trace.h"
#समावेश "trace.h"

व्योम mt76x02_mac_reset_counters(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक i;

	mt76_rr(dev, MT_RX_STAT_0);
	mt76_rr(dev, MT_RX_STAT_1);
	mt76_rr(dev, MT_RX_STAT_2);
	mt76_rr(dev, MT_TX_STA_0);
	mt76_rr(dev, MT_TX_STA_1);
	mt76_rr(dev, MT_TX_STA_2);

	क्रम (i = 0; i < 16; i++)
		mt76_rr(dev, MT_TX_AGG_CNT(i));

	क्रम (i = 0; i < 16; i++)
		mt76_rr(dev, MT_TX_STAT_FIFO);

	स_रखो(dev->mt76.aggr_stats, 0, माप(dev->mt76.aggr_stats));
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_mac_reset_counters);

अटल क्रमागत mt76x02_cipher_type
mt76x02_mac_get_key_info(काष्ठा ieee80211_key_conf *key, u8 *key_data)
अणु
	स_रखो(key_data, 0, 32);
	अगर (!key)
		वापस MT_CIPHER_NONE;

	अगर (key->keylen > 32)
		वापस MT_CIPHER_NONE;

	स_नकल(key_data, key->key, key->keylen);

	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
		वापस MT_CIPHER_WEP40;
	हाल WLAN_CIPHER_SUITE_WEP104:
		वापस MT_CIPHER_WEP104;
	हाल WLAN_CIPHER_SUITE_TKIP:
		वापस MT_CIPHER_TKIP;
	हाल WLAN_CIPHER_SUITE_CCMP:
		वापस MT_CIPHER_AES_CCMP;
	शेष:
		वापस MT_CIPHER_NONE;
	पूर्ण
पूर्ण

पूर्णांक mt76x02_mac_shared_key_setup(काष्ठा mt76x02_dev *dev, u8 vअगर_idx,
				 u8 key_idx, काष्ठा ieee80211_key_conf *key)
अणु
	क्रमागत mt76x02_cipher_type cipher;
	u8 key_data[32];
	u32 val;

	cipher = mt76x02_mac_get_key_info(key, key_data);
	अगर (cipher == MT_CIPHER_NONE && key)
		वापस -EOPNOTSUPP;

	val = mt76_rr(dev, MT_SKEY_MODE(vअगर_idx));
	val &= ~(MT_SKEY_MODE_MASK << MT_SKEY_MODE_SHIFT(vअगर_idx, key_idx));
	val |= cipher << MT_SKEY_MODE_SHIFT(vअगर_idx, key_idx);
	mt76_wr(dev, MT_SKEY_MODE(vअगर_idx), val);

	mt76_wr_copy(dev, MT_SKEY(vअगर_idx, key_idx), key_data,
		     माप(key_data));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_mac_shared_key_setup);

व्योम mt76x02_mac_wcid_sync_pn(काष्ठा mt76x02_dev *dev, u8 idx,
			      काष्ठा ieee80211_key_conf *key)
अणु
	क्रमागत mt76x02_cipher_type cipher;
	u8 key_data[32];
	u32 iv, eiv;
	u64 pn;

	cipher = mt76x02_mac_get_key_info(key, key_data);
	iv = mt76_rr(dev, MT_WCID_IV(idx));
	eiv = mt76_rr(dev, MT_WCID_IV(idx) + 4);

	pn = (u64)eiv << 16;
	अगर (cipher == MT_CIPHER_TKIP) अणु
		pn |= (iv >> 16) & 0xff;
		pn |= (iv & 0xff) << 8;
	पूर्ण अन्यथा अगर (cipher >= MT_CIPHER_AES_CCMP) अणु
		pn |= iv & 0xffff;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	atomic64_set(&key->tx_pn, pn);
पूर्ण

पूर्णांक mt76x02_mac_wcid_set_key(काष्ठा mt76x02_dev *dev, u8 idx,
			     काष्ठा ieee80211_key_conf *key)
अणु
	क्रमागत mt76x02_cipher_type cipher;
	u8 key_data[32];
	u8 iv_data[8];
	u64 pn;

	cipher = mt76x02_mac_get_key_info(key, key_data);
	अगर (cipher == MT_CIPHER_NONE && key)
		वापस -EOPNOTSUPP;

	mt76_wr_copy(dev, MT_WCID_KEY(idx), key_data, माप(key_data));
	mt76_rmw_field(dev, MT_WCID_ATTR(idx), MT_WCID_ATTR_PKEY_MODE, cipher);

	स_रखो(iv_data, 0, माप(iv_data));
	अगर (key) अणु
		mt76_rmw_field(dev, MT_WCID_ATTR(idx), MT_WCID_ATTR_PAIRWISE,
			       !!(key->flags & IEEE80211_KEY_FLAG_PAIRWISE));

		pn = atomic64_पढ़ो(&key->tx_pn);

		iv_data[3] = key->keyidx << 6;
		अगर (cipher >= MT_CIPHER_TKIP) अणु
			iv_data[3] |= 0x20;
			put_unaligned_le32(pn >> 16, &iv_data[4]);
		पूर्ण

		अगर (cipher == MT_CIPHER_TKIP) अणु
			iv_data[0] = (pn >> 8) & 0xff;
			iv_data[1] = (iv_data[0] | 0x20) & 0x7f;
			iv_data[2] = pn & 0xff;
		पूर्ण अन्यथा अगर (cipher >= MT_CIPHER_AES_CCMP) अणु
			put_unaligned_le16((pn & 0xffff), &iv_data[0]);
		पूर्ण
	पूर्ण

	mt76_wr_copy(dev, MT_WCID_IV(idx), iv_data, माप(iv_data));

	वापस 0;
पूर्ण

व्योम mt76x02_mac_wcid_setup(काष्ठा mt76x02_dev *dev, u8 idx,
			    u8 vअगर_idx, u8 *mac)
अणु
	काष्ठा mt76_wcid_addr addr = अणुपूर्ण;
	u32 attr;

	attr = FIELD_PREP(MT_WCID_ATTR_BSS_IDX, vअगर_idx & 7) |
	       FIELD_PREP(MT_WCID_ATTR_BSS_IDX_EXT, !!(vअगर_idx & 8));

	mt76_wr(dev, MT_WCID_ATTR(idx), attr);

	अगर (idx >= 128)
		वापस;

	अगर (mac)
		स_नकल(addr.macaddr, mac, ETH_ALEN);

	mt76_wr_copy(dev, MT_WCID_ADDR(idx), &addr, माप(addr));
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_mac_wcid_setup);

व्योम mt76x02_mac_wcid_set_drop(काष्ठा mt76x02_dev *dev, u8 idx, bool drop)
अणु
	u32 val = mt76_rr(dev, MT_WCID_DROP(idx));
	u32 bit = MT_WCID_DROP_MASK(idx);

	/* prevent unnecessary ग_लिखोs */
	अगर ((val & bit) != (bit * drop))
		mt76_wr(dev, MT_WCID_DROP(idx), (val & ~bit) | (bit * drop));
पूर्ण

अटल __le16
mt76x02_mac_tx_rate_val(काष्ठा mt76x02_dev *dev,
			स्थिर काष्ठा ieee80211_tx_rate *rate, u8 *nss_val)
अणु
	u8 phy, rate_idx, nss, bw = 0;
	u16 rateval;

	अगर (rate->flags & IEEE80211_TX_RC_VHT_MCS) अणु
		rate_idx = rate->idx;
		nss = 1 + (rate->idx >> 4);
		phy = MT_PHY_TYPE_VHT;
		अगर (rate->flags & IEEE80211_TX_RC_80_MHZ_WIDTH)
			bw = 2;
		अन्यथा अगर (rate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
			bw = 1;
	पूर्ण अन्यथा अगर (rate->flags & IEEE80211_TX_RC_MCS) अणु
		rate_idx = rate->idx;
		nss = 1 + (rate->idx >> 3);
		phy = MT_PHY_TYPE_HT;
		अगर (rate->flags & IEEE80211_TX_RC_GREEN_FIELD)
			phy = MT_PHY_TYPE_HT_GF;
		अगर (rate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
			bw = 1;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा ieee80211_rate *r;
		पूर्णांक band = dev->mphy.chandef.chan->band;
		u16 val;

		r = &dev->mt76.hw->wiphy->bands[band]->bitrates[rate->idx];
		अगर (rate->flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE)
			val = r->hw_value_लघु;
		अन्यथा
			val = r->hw_value;

		phy = val >> 8;
		rate_idx = val & 0xff;
		nss = 1;
	पूर्ण

	rateval = FIELD_PREP(MT_RXWI_RATE_INDEX, rate_idx);
	rateval |= FIELD_PREP(MT_RXWI_RATE_PHY, phy);
	rateval |= FIELD_PREP(MT_RXWI_RATE_BW, bw);
	अगर (rate->flags & IEEE80211_TX_RC_SHORT_GI)
		rateval |= MT_RXWI_RATE_SGI;

	*nss_val = nss;
	वापस cpu_to_le16(rateval);
पूर्ण

व्योम mt76x02_mac_wcid_set_rate(काष्ठा mt76x02_dev *dev, काष्ठा mt76_wcid *wcid,
			       स्थिर काष्ठा ieee80211_tx_rate *rate)
अणु
	s8 max_txpwr_adj = mt76x02_tx_get_max_txpwr_adj(dev, rate);
	__le16 rateval;
	u32 tx_info;
	s8 nss;

	rateval = mt76x02_mac_tx_rate_val(dev, rate, &nss);
	tx_info = FIELD_PREP(MT_WCID_TX_INFO_RATE, rateval) |
		  FIELD_PREP(MT_WCID_TX_INFO_NSS, nss) |
		  FIELD_PREP(MT_WCID_TX_INFO_TXPWR_ADJ, max_txpwr_adj) |
		  MT_WCID_TX_INFO_SET;
	wcid->tx_info = tx_info;
पूर्ण

व्योम mt76x02_mac_set_लघु_preamble(काष्ठा mt76x02_dev *dev, bool enable)
अणु
	अगर (enable)
		mt76_set(dev, MT_AUTO_RSP_CFG, MT_AUTO_RSP_PREAMB_SHORT);
	अन्यथा
		mt76_clear(dev, MT_AUTO_RSP_CFG, MT_AUTO_RSP_PREAMB_SHORT);
पूर्ण

bool mt76x02_mac_load_tx_status(काष्ठा mt76x02_dev *dev,
				काष्ठा mt76x02_tx_status *stat)
अणु
	u32 stat1, stat2;

	stat2 = mt76_rr(dev, MT_TX_STAT_FIFO_EXT);
	stat1 = mt76_rr(dev, MT_TX_STAT_FIFO);

	stat->valid = !!(stat1 & MT_TX_STAT_FIFO_VALID);
	अगर (!stat->valid)
		वापस false;

	stat->success = !!(stat1 & MT_TX_STAT_FIFO_SUCCESS);
	stat->aggr = !!(stat1 & MT_TX_STAT_FIFO_AGGR);
	stat->ack_req = !!(stat1 & MT_TX_STAT_FIFO_ACKREQ);
	stat->wcid = FIELD_GET(MT_TX_STAT_FIFO_WCID, stat1);
	stat->rate = FIELD_GET(MT_TX_STAT_FIFO_RATE, stat1);

	stat->retry = FIELD_GET(MT_TX_STAT_FIFO_EXT_RETRY, stat2);
	stat->pktid = FIELD_GET(MT_TX_STAT_FIFO_EXT_PKTID, stat2);

	trace_mac_txstat_fetch(dev, stat);

	वापस true;
पूर्ण

अटल पूर्णांक
mt76x02_mac_process_tx_rate(काष्ठा ieee80211_tx_rate *txrate, u16 rate,
			    क्रमागत nl80211_band band)
अणु
	u8 idx = FIELD_GET(MT_RXWI_RATE_INDEX, rate);

	txrate->idx = 0;
	txrate->flags = 0;
	txrate->count = 1;

	चयन (FIELD_GET(MT_RXWI_RATE_PHY, rate)) अणु
	हाल MT_PHY_TYPE_OFDM:
		अगर (band == NL80211_BAND_2GHZ)
			idx += 4;

		txrate->idx = idx;
		वापस 0;
	हाल MT_PHY_TYPE_CCK:
		अगर (idx >= 8)
			idx -= 8;

		txrate->idx = idx;
		वापस 0;
	हाल MT_PHY_TYPE_HT_GF:
		txrate->flags |= IEEE80211_TX_RC_GREEN_FIELD;
		fallthrough;
	हाल MT_PHY_TYPE_HT:
		txrate->flags |= IEEE80211_TX_RC_MCS;
		txrate->idx = idx;
		अवरोध;
	हाल MT_PHY_TYPE_VHT:
		txrate->flags |= IEEE80211_TX_RC_VHT_MCS;
		txrate->idx = idx;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (FIELD_GET(MT_RXWI_RATE_BW, rate)) अणु
	हाल MT_PHY_BW_20:
		अवरोध;
	हाल MT_PHY_BW_40:
		txrate->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;
		अवरोध;
	हाल MT_PHY_BW_80:
		txrate->flags |= IEEE80211_TX_RC_80_MHZ_WIDTH;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (rate & MT_RXWI_RATE_SGI)
		txrate->flags |= IEEE80211_TX_RC_SHORT_GI;

	वापस 0;
पूर्ण

व्योम mt76x02_mac_ग_लिखो_txwi(काष्ठा mt76x02_dev *dev, काष्ठा mt76x02_txwi *txwi,
			    काष्ठा sk_buff *skb, काष्ठा mt76_wcid *wcid,
			    काष्ठा ieee80211_sta *sta, पूर्णांक len)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_tx_rate *rate = &info->control.rates[0];
	काष्ठा ieee80211_key_conf *key = info->control.hw_key;
	u32 wcid_tx_info;
	u16 rate_ht_mask = FIELD_PREP(MT_RXWI_RATE_PHY, BIT(1) | BIT(2));
	u16 txwi_flags = 0;
	u8 nss;
	s8 txpwr_adj, max_txpwr_adj;
	u8 ccmp_pn[8], nstreams = dev->mphy.chainmask & 0xf;

	स_रखो(txwi, 0, माप(*txwi));

	mt76_tx_check_agg_ssn(sta, skb);

	अगर (!info->control.hw_key && wcid && wcid->hw_key_idx != 0xff &&
	    ieee80211_has_रक्षित(hdr->frame_control)) अणु
		wcid = शून्य;
		ieee80211_get_tx_rates(info->control.vअगर, sta, skb,
				       info->control.rates, 1);
	पूर्ण

	अगर (wcid)
		txwi->wcid = wcid->idx;
	अन्यथा
		txwi->wcid = 0xff;

	अगर (wcid && wcid->sw_iv && key) अणु
		u64 pn = atomic64_inc_वापस(&key->tx_pn);

		ccmp_pn[0] = pn;
		ccmp_pn[1] = pn >> 8;
		ccmp_pn[2] = 0;
		ccmp_pn[3] = 0x20 | (key->keyidx << 6);
		ccmp_pn[4] = pn >> 16;
		ccmp_pn[5] = pn >> 24;
		ccmp_pn[6] = pn >> 32;
		ccmp_pn[7] = pn >> 40;
		txwi->iv = *((__le32 *)&ccmp_pn[0]);
		txwi->eiv = *((__le32 *)&ccmp_pn[4]);
	पूर्ण

	अगर (wcid && (rate->idx < 0 || !rate->count)) अणु
		wcid_tx_info = wcid->tx_info;
		txwi->rate = FIELD_GET(MT_WCID_TX_INFO_RATE, wcid_tx_info);
		max_txpwr_adj = FIELD_GET(MT_WCID_TX_INFO_TXPWR_ADJ,
					  wcid_tx_info);
		nss = FIELD_GET(MT_WCID_TX_INFO_NSS, wcid_tx_info);
	पूर्ण अन्यथा अणु
		txwi->rate = mt76x02_mac_tx_rate_val(dev, rate, &nss);
		max_txpwr_adj = mt76x02_tx_get_max_txpwr_adj(dev, rate);
	पूर्ण

	txpwr_adj = mt76x02_tx_get_txpwr_adj(dev, dev->txघातer_conf,
					     max_txpwr_adj);
	txwi->ctl2 = FIELD_PREP(MT_TX_PWR_ADJ, txpwr_adj);

	अगर (nstreams > 1 && mt76_rev(&dev->mt76) >= MT76XX_REV_E4)
		txwi->txstream = 0x13;
	अन्यथा अगर (nstreams > 1 && mt76_rev(&dev->mt76) >= MT76XX_REV_E3 &&
		 !(txwi->rate & cpu_to_le16(rate_ht_mask)))
		txwi->txstream = 0x93;

	अगर (is_mt76x2(dev) && (info->flags & IEEE80211_TX_CTL_LDPC))
		txwi->rate |= cpu_to_le16(MT_RXWI_RATE_LDPC);
	अगर ((info->flags & IEEE80211_TX_CTL_STBC) && nss == 1)
		txwi->rate |= cpu_to_le16(MT_RXWI_RATE_STBC);
	अगर (nss > 1 && sta && sta->smps_mode == IEEE80211_SMPS_DYNAMIC)
		txwi_flags |= MT_TXWI_FLAGS_MMPS;
	अगर (!(info->flags & IEEE80211_TX_CTL_NO_ACK))
		txwi->ack_ctl |= MT_TXWI_ACK_CTL_REQ;
	अगर (info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ)
		txwi->ack_ctl |= MT_TXWI_ACK_CTL_NSEQ;
	अगर ((info->flags & IEEE80211_TX_CTL_AMPDU) && sta) अणु
		u8 ba_size = IEEE80211_MIN_AMPDU_BUF;
		u8 ampdu_density = sta->ht_cap.ampdu_density;

		ba_size <<= sta->ht_cap.ampdu_factor;
		ba_size = min_t(पूर्णांक, 63, ba_size - 1);
		अगर (info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE)
			ba_size = 0;
		txwi->ack_ctl |= FIELD_PREP(MT_TXWI_ACK_CTL_BA_WINDOW, ba_size);

		अगर (ampdu_density < IEEE80211_HT_MPDU_DENSITY_4)
			ampdu_density = IEEE80211_HT_MPDU_DENSITY_4;

		txwi_flags |= MT_TXWI_FLAGS_AMPDU |
			 FIELD_PREP(MT_TXWI_FLAGS_MPDU_DENSITY, ampdu_density);
	पूर्ण

	अगर (ieee80211_is_probe_resp(hdr->frame_control) ||
	    ieee80211_is_beacon(hdr->frame_control))
		txwi_flags |= MT_TXWI_FLAGS_TS;

	txwi->flags |= cpu_to_le16(txwi_flags);
	txwi->len_ctl = cpu_to_le16(len);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_mac_ग_लिखो_txwi);

अटल व्योम
mt76x02_tx_rate_fallback(काष्ठा ieee80211_tx_rate *rates, पूर्णांक idx, पूर्णांक phy)
अणु
	u8 mcs, nss;

	अगर (!idx)
		वापस;

	rates += idx - 1;
	rates[1] = rates[0];
	चयन (phy) अणु
	हाल MT_PHY_TYPE_VHT:
		mcs = ieee80211_rate_get_vht_mcs(rates);
		nss = ieee80211_rate_get_vht_nss(rates);

		अगर (mcs == 0)
			nss = max_t(पूर्णांक, nss - 1, 1);
		अन्यथा
			mcs--;

		ieee80211_rate_set_vht(rates + 1, mcs, nss);
		अवरोध;
	हाल MT_PHY_TYPE_HT_GF:
	हाल MT_PHY_TYPE_HT:
		/* MCS 8 falls back to MCS 0 */
		अगर (rates[0].idx == 8) अणु
			rates[1].idx = 0;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		rates[1].idx = max_t(पूर्णांक, rates[0].idx - 1, 0);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
mt76x02_mac_fill_tx_status(काष्ठा mt76x02_dev *dev, काष्ठा mt76x02_sta *msta,
			   काष्ठा ieee80211_tx_info *info,
			   काष्ठा mt76x02_tx_status *st, पूर्णांक n_frames)
अणु
	काष्ठा ieee80211_tx_rate *rate = info->status.rates;
	काष्ठा ieee80211_tx_rate last_rate;
	u16 first_rate;
	पूर्णांक retry = st->retry;
	पूर्णांक phy;
	पूर्णांक i;

	अगर (!n_frames)
		वापस;

	phy = FIELD_GET(MT_RXWI_RATE_PHY, st->rate);

	अगर (st->pktid & MT_PACKET_ID_HAS_RATE) अणु
		first_rate = st->rate & ~MT_PKTID_RATE;
		first_rate |= st->pktid & MT_PKTID_RATE;

		mt76x02_mac_process_tx_rate(&rate[0], first_rate,
					    dev->mphy.chandef.chan->band);
	पूर्ण अन्यथा अगर (rate[0].idx < 0) अणु
		अगर (!msta)
			वापस;

		mt76x02_mac_process_tx_rate(&rate[0], msta->wcid.tx_info,
					    dev->mphy.chandef.chan->band);
	पूर्ण

	mt76x02_mac_process_tx_rate(&last_rate, st->rate,
				    dev->mphy.chandef.chan->band);

	क्रम (i = 0; i < ARRAY_SIZE(info->status.rates); i++) अणु
		retry--;
		अगर (i + 1 == ARRAY_SIZE(info->status.rates)) अणु
			info->status.rates[i] = last_rate;
			info->status.rates[i].count = max_t(पूर्णांक, retry, 1);
			अवरोध;
		पूर्ण

		mt76x02_tx_rate_fallback(info->status.rates, i, phy);
		अगर (info->status.rates[i].idx == last_rate.idx)
			अवरोध;
	पूर्ण

	अगर (i + 1 < ARRAY_SIZE(info->status.rates)) अणु
		info->status.rates[i + 1].idx = -1;
		info->status.rates[i + 1].count = 0;
	पूर्ण

	info->status.ampdu_len = n_frames;
	info->status.ampdu_ack_len = st->success ? n_frames : 0;

	अगर (st->aggr)
		info->flags |= IEEE80211_TX_CTL_AMPDU |
			       IEEE80211_TX_STAT_AMPDU;

	अगर (!st->ack_req)
		info->flags |= IEEE80211_TX_CTL_NO_ACK;
	अन्यथा अगर (st->success)
		info->flags |= IEEE80211_TX_STAT_ACK;
पूर्ण

व्योम mt76x02_send_tx_status(काष्ठा mt76x02_dev *dev,
			    काष्ठा mt76x02_tx_status *stat, u8 *update)
अणु
	काष्ठा ieee80211_tx_info info = अणुपूर्ण;
	काष्ठा ieee80211_tx_status status = अणु
		.info = &info
	पूर्ण;
	अटल स्थिर u8 ac_to_tid[4] = अणु
		[IEEE80211_AC_BE] = 0,
		[IEEE80211_AC_BK] = 1,
		[IEEE80211_AC_VI] = 4,
		[IEEE80211_AC_VO] = 6
	पूर्ण;
	काष्ठा mt76_wcid *wcid = शून्य;
	काष्ठा mt76x02_sta *msta = शून्य;
	काष्ठा mt76_dev *mdev = &dev->mt76;
	काष्ठा sk_buff_head list;
	u32 duration = 0;
	u8 cur_pktid;
	u32 ac = 0;
	पूर्णांक len = 0;

	अगर (stat->pktid == MT_PACKET_ID_NO_ACK)
		वापस;

	rcu_पढ़ो_lock();

	अगर (stat->wcid < MT76x02_N_WCIDS)
		wcid = rcu_dereference(dev->mt76.wcid[stat->wcid]);

	अगर (wcid && wcid->sta) अणु
		व्योम *priv;

		priv = msta = container_of(wcid, काष्ठा mt76x02_sta, wcid);
		status.sta = container_of(priv, काष्ठा ieee80211_sta,
					  drv_priv);
	पूर्ण

	mt76_tx_status_lock(mdev, &list);

	अगर (wcid) अणु
		अगर (mt76_is_skb_pktid(stat->pktid))
			status.skb = mt76_tx_status_skb_get(mdev, wcid,
							    stat->pktid, &list);
		अगर (status.skb)
			status.info = IEEE80211_SKB_CB(status.skb);
	पूर्ण

	अगर (!status.skb && !(stat->pktid & MT_PACKET_ID_HAS_RATE)) अणु
		mt76_tx_status_unlock(mdev, &list);
		जाओ out;
	पूर्ण


	अगर (msta && stat->aggr && !status.skb) अणु
		u32 stat_val, stat_cache;

		stat_val = stat->rate;
		stat_val |= ((u32)stat->retry) << 16;
		stat_cache = msta->status.rate;
		stat_cache |= ((u32)msta->status.retry) << 16;

		अगर (*update == 0 && stat_val == stat_cache &&
		    stat->wcid == msta->status.wcid && msta->n_frames < 32) अणु
			msta->n_frames++;
			mt76_tx_status_unlock(mdev, &list);
			जाओ out;
		पूर्ण

		cur_pktid = msta->status.pktid;
		mt76x02_mac_fill_tx_status(dev, msta, status.info,
					   &msta->status, msta->n_frames);

		msta->status = *stat;
		msta->n_frames = 1;
		*update = 0;
	पूर्ण अन्यथा अणु
		cur_pktid = stat->pktid;
		mt76x02_mac_fill_tx_status(dev, msta, status.info, stat, 1);
		*update = 1;
	पूर्ण

	अगर (status.skb) अणु
		info = *status.info;
		len = status.skb->len;
		ac = skb_get_queue_mapping(status.skb);
		mt76_tx_status_skb_करोne(mdev, status.skb, &list);
	पूर्ण अन्यथा अगर (msta) अणु
		len = status.info->status.ampdu_len * ewma_pktlen_पढ़ो(&msta->pktlen);
		ac = FIELD_GET(MT_PKTID_AC, cur_pktid);
	पूर्ण

	mt76_tx_status_unlock(mdev, &list);

	अगर (!status.skb)
		ieee80211_tx_status_ext(mt76_hw(dev), &status);

	अगर (!len)
		जाओ out;

	duration = ieee80211_calc_tx_airसमय(mt76_hw(dev), &info, len);

	spin_lock_bh(&dev->mt76.cc_lock);
	dev->tx_airसमय += duration;
	spin_unlock_bh(&dev->mt76.cc_lock);

	अगर (msta)
		ieee80211_sta_रेजिस्टर_airसमय(status.sta, ac_to_tid[ac], duration, 0);

out:
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक
mt76x02_mac_process_rate(काष्ठा mt76x02_dev *dev,
			 काष्ठा mt76_rx_status *status,
			 u16 rate)
अणु
	u8 idx = FIELD_GET(MT_RXWI_RATE_INDEX, rate);

	चयन (FIELD_GET(MT_RXWI_RATE_PHY, rate)) अणु
	हाल MT_PHY_TYPE_OFDM:
		अगर (idx >= 8)
			idx = 0;

		अगर (status->band == NL80211_BAND_2GHZ)
			idx += 4;

		status->rate_idx = idx;
		वापस 0;
	हाल MT_PHY_TYPE_CCK:
		अगर (idx >= 8) अणु
			idx -= 8;
			status->enc_flags |= RX_ENC_FLAG_SHORTPRE;
		पूर्ण

		अगर (idx >= 4)
			idx = 0;

		status->rate_idx = idx;
		वापस 0;
	हाल MT_PHY_TYPE_HT_GF:
		status->enc_flags |= RX_ENC_FLAG_HT_GF;
		fallthrough;
	हाल MT_PHY_TYPE_HT:
		status->encoding = RX_ENC_HT;
		status->rate_idx = idx;
		अवरोध;
	हाल MT_PHY_TYPE_VHT: अणु
		u8 n_rxstream = dev->mphy.chainmask & 0xf;

		status->encoding = RX_ENC_VHT;
		status->rate_idx = FIELD_GET(MT_RATE_INDEX_VHT_IDX, idx);
		status->nss = min_t(u8, n_rxstream,
				    FIELD_GET(MT_RATE_INDEX_VHT_NSS, idx) + 1);
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (rate & MT_RXWI_RATE_LDPC)
		status->enc_flags |= RX_ENC_FLAG_LDPC;

	अगर (rate & MT_RXWI_RATE_SGI)
		status->enc_flags |= RX_ENC_FLAG_SHORT_GI;

	अगर (rate & MT_RXWI_RATE_STBC)
		status->enc_flags |= 1 << RX_ENC_FLAG_STBC_SHIFT;

	चयन (FIELD_GET(MT_RXWI_RATE_BW, rate)) अणु
	हाल MT_PHY_BW_20:
		अवरोध;
	हाल MT_PHY_BW_40:
		status->bw = RATE_INFO_BW_40;
		अवरोध;
	हाल MT_PHY_BW_80:
		status->bw = RATE_INFO_BW_80;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

व्योम mt76x02_mac_setaddr(काष्ठा mt76x02_dev *dev, स्थिर u8 *addr)
अणु
	अटल स्थिर u8 null_addr[ETH_ALEN] = अणुपूर्ण;
	पूर्णांक i;

	ether_addr_copy(dev->mphy.macaddr, addr);

	अगर (!is_valid_ether_addr(dev->mphy.macaddr)) अणु
		eth_अक्रमom_addr(dev->mphy.macaddr);
		dev_info(dev->mt76.dev,
			 "Invalid MAC address, using random address %pM\n",
			 dev->mphy.macaddr);
	पूर्ण

	mt76_wr(dev, MT_MAC_ADDR_DW0, get_unaligned_le32(dev->mphy.macaddr));
	mt76_wr(dev, MT_MAC_ADDR_DW1,
		get_unaligned_le16(dev->mphy.macaddr + 4) |
		FIELD_PREP(MT_MAC_ADDR_DW1_U2ME_MASK, 0xff));

	mt76_wr(dev, MT_MAC_BSSID_DW0,
		get_unaligned_le32(dev->mphy.macaddr));
	mt76_wr(dev, MT_MAC_BSSID_DW1,
		get_unaligned_le16(dev->mphy.macaddr + 4) |
		FIELD_PREP(MT_MAC_BSSID_DW1_MBSS_MODE, 3) | /* 8 APs + 8 STAs */
		MT_MAC_BSSID_DW1_MBSS_LOCAL_BIT);
	/* enable 7 additional beacon slots and control them with bypass mask */
	mt76_rmw_field(dev, MT_MAC_BSSID_DW1, MT_MAC_BSSID_DW1_MBEACON_N, 7);

	क्रम (i = 0; i < 16; i++)
		mt76x02_mac_set_bssid(dev, i, null_addr);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_mac_setaddr);

अटल पूर्णांक
mt76x02_mac_get_rssi(काष्ठा mt76x02_dev *dev, s8 rssi, पूर्णांक chain)
अणु
	काष्ठा mt76x02_rx_freq_cal *cal = &dev->cal.rx;

	rssi += cal->rssi_offset[chain];
	rssi -= cal->lna_gain;

	वापस rssi;
पूर्ण

पूर्णांक mt76x02_mac_process_rx(काष्ठा mt76x02_dev *dev, काष्ठा sk_buff *skb,
			   व्योम *rxi)
अणु
	काष्ठा mt76_rx_status *status = (काष्ठा mt76_rx_status *)skb->cb;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा mt76x02_rxwi *rxwi = rxi;
	काष्ठा mt76x02_sta *sta;
	u32 rxinfo = le32_to_cpu(rxwi->rxinfo);
	u32 ctl = le32_to_cpu(rxwi->ctl);
	u16 rate = le16_to_cpu(rxwi->rate);
	u16 tid_sn = le16_to_cpu(rxwi->tid_sn);
	bool unicast = rxwi->rxinfo & cpu_to_le32(MT_RXINFO_UNICAST);
	पूर्णांक pad_len = 0, nstreams = dev->mphy.chainmask & 0xf;
	s8 संकेत;
	u8 pn_len;
	u8 wcid;
	पूर्णांक len;

	अगर (!test_bit(MT76_STATE_RUNNING, &dev->mphy.state))
		वापस -EINVAL;

	अगर (rxinfo & MT_RXINFO_L2PAD)
		pad_len += 2;

	अगर (rxinfo & MT_RXINFO_DECRYPT) अणु
		status->flag |= RX_FLAG_DECRYPTED;
		status->flag |= RX_FLAG_MMIC_STRIPPED;
		status->flag |= RX_FLAG_MIC_STRIPPED;
		status->flag |= RX_FLAG_IV_STRIPPED;
	पूर्ण

	wcid = FIELD_GET(MT_RXWI_CTL_WCID, ctl);
	sta = mt76x02_rx_get_sta(&dev->mt76, wcid);
	status->wcid = mt76x02_rx_get_sta_wcid(sta, unicast);

	len = FIELD_GET(MT_RXWI_CTL_MPDU_LEN, ctl);
	pn_len = FIELD_GET(MT_RXINFO_PN_LEN, rxinfo);
	अगर (pn_len) अणु
		पूर्णांक offset = ieee80211_get_hdrlen_from_skb(skb) + pad_len;
		u8 *data = skb->data + offset;

		status->iv[0] = data[7];
		status->iv[1] = data[6];
		status->iv[2] = data[5];
		status->iv[3] = data[4];
		status->iv[4] = data[1];
		status->iv[5] = data[0];

		/*
		 * Driver CCMP validation can't deal with fragments.
		 * Let mac80211 take care of it.
		 */
		अगर (rxinfo & MT_RXINFO_FRAG) अणु
			status->flag &= ~RX_FLAG_IV_STRIPPED;
		पूर्ण अन्यथा अणु
			pad_len += pn_len << 2;
			len -= pn_len << 2;
		पूर्ण
	पूर्ण

	mt76x02_हटाओ_hdr_pad(skb, pad_len);

	अगर ((rxinfo & MT_RXINFO_BA) && !(rxinfo & MT_RXINFO_शून्य))
		status->aggr = true;

	अगर (rxinfo & MT_RXINFO_AMPDU) अणु
		status->flag |= RX_FLAG_AMPDU_DETAILS;
		status->ampdu_ref = dev->ampdu_ref;

		/*
		 * When receiving an A-MPDU subframe and RSSI info is not valid,
		 * we can assume that more subframes beदीर्घing to the same A-MPDU
		 * are coming. The last one will have valid RSSI info
		 */
		अगर (rxinfo & MT_RXINFO_RSSI) अणु
			अगर (!++dev->ampdu_ref)
				dev->ampdu_ref++;
		पूर्ण
	पूर्ण

	अगर (WARN_ON_ONCE(len > skb->len))
		वापस -EINVAL;

	pskb_trim(skb, len);

	status->chains = BIT(0);
	संकेत = mt76x02_mac_get_rssi(dev, rxwi->rssi[0], 0);
	status->chain_संकेत[0] = संकेत;
	अगर (nstreams > 1) अणु
		status->chains |= BIT(1);
		status->chain_संकेत[1] = mt76x02_mac_get_rssi(dev,
							       rxwi->rssi[1],
							       1);
		संकेत = max_t(s8, संकेत, status->chain_संकेत[1]);
	पूर्ण
	status->संकेत = संकेत;
	status->freq = dev->mphy.chandef.chan->center_freq;
	status->band = dev->mphy.chandef.chan->band;

	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	status->qos_ctl = *ieee80211_get_qos_ctl(hdr);
	status->seqno = FIELD_GET(MT_RXWI_SN, tid_sn);

	वापस mt76x02_mac_process_rate(dev, status, rate);
पूर्ण

व्योम mt76x02_mac_poll_tx_status(काष्ठा mt76x02_dev *dev, bool irq)
अणु
	काष्ठा mt76x02_tx_status stat = अणुपूर्ण;
	u8 update = 1;
	bool ret;

	अगर (!test_bit(MT76_STATE_RUNNING, &dev->mphy.state))
		वापस;

	trace_mac_txstat_poll(dev);

	जबतक (!irq || !kfअगरo_is_full(&dev->txstatus_fअगरo)) अणु
		अगर (!spin_trylock(&dev->txstatus_fअगरo_lock))
			अवरोध;

		ret = mt76x02_mac_load_tx_status(dev, &stat);
		spin_unlock(&dev->txstatus_fअगरo_lock);

		अगर (!ret)
			अवरोध;

		अगर (!irq) अणु
			mt76x02_send_tx_status(dev, &stat, &update);
			जारी;
		पूर्ण

		kfअगरo_put(&dev->txstatus_fअगरo, stat);
	पूर्ण
पूर्ण

व्योम mt76x02_tx_complete_skb(काष्ठा mt76_dev *mdev, काष्ठा mt76_queue_entry *e)
अणु
	काष्ठा mt76x02_dev *dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);
	काष्ठा mt76x02_txwi *txwi;
	u8 *txwi_ptr;

	अगर (!e->txwi) अणु
		dev_kमुक्त_skb_any(e->skb);
		वापस;
	पूर्ण

	mt76x02_mac_poll_tx_status(dev, false);

	txwi_ptr = mt76_get_txwi_ptr(mdev, e->txwi);
	txwi = (काष्ठा mt76x02_txwi *)txwi_ptr;
	trace_mac_txकरोne(mdev, txwi->wcid, txwi->pktid);

	mt76_tx_complete_skb(mdev, e->wcid, e->skb);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_tx_complete_skb);

व्योम mt76x02_mac_set_rts_thresh(काष्ठा mt76x02_dev *dev, u32 val)
अणु
	u32 data = 0;

	अगर (val != ~0)
		data = FIELD_PREP(MT_PROT_CFG_CTRL, 1) |
		       MT_PROT_CFG_RTS_THRESH;

	mt76_rmw_field(dev, MT_TX_RTS_CFG, MT_TX_RTS_CFG_THRESH, val);

	mt76_rmw(dev, MT_CCK_PROT_CFG,
		 MT_PROT_CFG_CTRL | MT_PROT_CFG_RTS_THRESH, data);
	mt76_rmw(dev, MT_OFDM_PROT_CFG,
		 MT_PROT_CFG_CTRL | MT_PROT_CFG_RTS_THRESH, data);
पूर्ण

व्योम mt76x02_mac_set_tx_protection(काष्ठा mt76x02_dev *dev, bool legacy_prot,
				   पूर्णांक ht_mode)
अणु
	पूर्णांक mode = ht_mode & IEEE80211_HT_OP_MODE_PROTECTION;
	bool non_gf = !!(ht_mode & IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT);
	u32 prot[6];
	u32 vht_prot[3];
	पूर्णांक i;
	u16 rts_thr;

	क्रम (i = 0; i < ARRAY_SIZE(prot); i++) अणु
		prot[i] = mt76_rr(dev, MT_CCK_PROT_CFG + i * 4);
		prot[i] &= ~MT_PROT_CFG_CTRL;
		अगर (i >= 2)
			prot[i] &= ~MT_PROT_CFG_RATE;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(vht_prot); i++) अणु
		vht_prot[i] = mt76_rr(dev, MT_TX_PROT_CFG6 + i * 4);
		vht_prot[i] &= ~(MT_PROT_CFG_CTRL | MT_PROT_CFG_RATE);
	पूर्ण

	rts_thr = mt76_get_field(dev, MT_TX_RTS_CFG, MT_TX_RTS_CFG_THRESH);

	अगर (rts_thr != 0xffff)
		prot[0] |= MT_PROT_CTRL_RTS_CTS;

	अगर (legacy_prot) अणु
		prot[1] |= MT_PROT_CTRL_CTS2SELF;

		prot[2] |= MT_PROT_RATE_CCK_11;
		prot[3] |= MT_PROT_RATE_CCK_11;
		prot[4] |= MT_PROT_RATE_CCK_11;
		prot[5] |= MT_PROT_RATE_CCK_11;

		vht_prot[0] |= MT_PROT_RATE_CCK_11;
		vht_prot[1] |= MT_PROT_RATE_CCK_11;
		vht_prot[2] |= MT_PROT_RATE_CCK_11;
	पूर्ण अन्यथा अणु
		अगर (rts_thr != 0xffff)
			prot[1] |= MT_PROT_CTRL_RTS_CTS;

		prot[2] |= MT_PROT_RATE_OFDM_24;
		prot[3] |= MT_PROT_RATE_DUP_OFDM_24;
		prot[4] |= MT_PROT_RATE_OFDM_24;
		prot[5] |= MT_PROT_RATE_DUP_OFDM_24;

		vht_prot[0] |= MT_PROT_RATE_OFDM_24;
		vht_prot[1] |= MT_PROT_RATE_DUP_OFDM_24;
		vht_prot[2] |= MT_PROT_RATE_SGI_OFDM_24;
	पूर्ण

	चयन (mode) अणु
	हाल IEEE80211_HT_OP_MODE_PROTECTION_NONMEMBER:
	हाल IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED:
		prot[2] |= MT_PROT_CTRL_RTS_CTS;
		prot[3] |= MT_PROT_CTRL_RTS_CTS;
		prot[4] |= MT_PROT_CTRL_RTS_CTS;
		prot[5] |= MT_PROT_CTRL_RTS_CTS;
		vht_prot[0] |= MT_PROT_CTRL_RTS_CTS;
		vht_prot[1] |= MT_PROT_CTRL_RTS_CTS;
		vht_prot[2] |= MT_PROT_CTRL_RTS_CTS;
		अवरोध;
	हाल IEEE80211_HT_OP_MODE_PROTECTION_20MHZ:
		prot[3] |= MT_PROT_CTRL_RTS_CTS;
		prot[5] |= MT_PROT_CTRL_RTS_CTS;
		vht_prot[1] |= MT_PROT_CTRL_RTS_CTS;
		vht_prot[2] |= MT_PROT_CTRL_RTS_CTS;
		अवरोध;
	पूर्ण

	अगर (non_gf) अणु
		prot[4] |= MT_PROT_CTRL_RTS_CTS;
		prot[5] |= MT_PROT_CTRL_RTS_CTS;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(prot); i++)
		mt76_wr(dev, MT_CCK_PROT_CFG + i * 4, prot[i]);

	क्रम (i = 0; i < ARRAY_SIZE(vht_prot); i++)
		mt76_wr(dev, MT_TX_PROT_CFG6 + i * 4, vht_prot[i]);
पूर्ण

व्योम mt76x02_update_channel(काष्ठा mt76_dev *mdev)
अणु
	काष्ठा mt76x02_dev *dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);
	काष्ठा mt76_channel_state *state;

	state = mdev->phy.chan_state;
	state->cc_busy += mt76_rr(dev, MT_CH_BUSY);

	spin_lock_bh(&dev->mt76.cc_lock);
	state->cc_tx += dev->tx_airसमय;
	dev->tx_airसमय = 0;
	spin_unlock_bh(&dev->mt76.cc_lock);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_update_channel);

अटल व्योम mt76x02_check_mac_err(काष्ठा mt76x02_dev *dev)
अणु
	u32 val = mt76_rr(dev, 0x10f4);

	अगर (!(val & BIT(29)) || !(val & (BIT(7) | BIT(5))))
		वापस;

	dev_err(dev->mt76.dev, "mac specific condition occurred\n");

	mt76_set(dev, MT_MAC_SYS_CTRL, MT_MAC_SYS_CTRL_RESET_CSR);
	udelay(10);
	mt76_wr(dev, MT_MAC_SYS_CTRL,
		MT_MAC_SYS_CTRL_ENABLE_TX | MT_MAC_SYS_CTRL_ENABLE_RX);
पूर्ण

अटल व्योम
mt76x02_edcca_tx_enable(काष्ठा mt76x02_dev *dev, bool enable)
अणु
	अगर (enable) अणु
		u32 data;

		mt76_set(dev, MT_MAC_SYS_CTRL, MT_MAC_SYS_CTRL_ENABLE_TX);
		mt76_set(dev, MT_AUTO_RSP_CFG, MT_AUTO_RSP_EN);
		/* enable pa-lna */
		data = mt76_rr(dev, MT_TX_PIN_CFG);
		data |= MT_TX_PIN_CFG_TXANT |
			MT_TX_PIN_CFG_RXANT |
			MT_TX_PIN_RFTR_EN |
			MT_TX_PIN_TRSW_EN;
		mt76_wr(dev, MT_TX_PIN_CFG, data);
	पूर्ण अन्यथा अणु
		mt76_clear(dev, MT_MAC_SYS_CTRL, MT_MAC_SYS_CTRL_ENABLE_TX);
		mt76_clear(dev, MT_AUTO_RSP_CFG, MT_AUTO_RSP_EN);
		/* disable pa-lna */
		mt76_clear(dev, MT_TX_PIN_CFG, MT_TX_PIN_CFG_TXANT);
		mt76_clear(dev, MT_TX_PIN_CFG, MT_TX_PIN_CFG_RXANT);
	पूर्ण
	dev->ed_tx_blocked = !enable;
पूर्ण

व्योम mt76x02_edcca_init(काष्ठा mt76x02_dev *dev)
अणु
	dev->ed_trigger = 0;
	dev->ed_silent = 0;

	अगर (dev->ed_monitor) अणु
		काष्ठा ieee80211_channel *chan = dev->mphy.chandef.chan;
		u8 ed_th = chan->band == NL80211_BAND_5GHZ ? 0x0e : 0x20;

		mt76_clear(dev, MT_TX_LINK_CFG, MT_TX_CFACK_EN);
		mt76_set(dev, MT_TXOP_CTRL_CFG, MT_TXOP_ED_CCA_EN);
		mt76_rmw(dev, MT_BBP(AGC, 2), GENMASK(15, 0),
			 ed_th << 8 | ed_th);
		mt76_set(dev, MT_TXOP_HLDR_ET, MT_TXOP_HLDR_TX40M_BLK_EN);
	पूर्ण अन्यथा अणु
		mt76_set(dev, MT_TX_LINK_CFG, MT_TX_CFACK_EN);
		mt76_clear(dev, MT_TXOP_CTRL_CFG, MT_TXOP_ED_CCA_EN);
		अगर (is_mt76x2(dev)) अणु
			mt76_wr(dev, MT_BBP(AGC, 2), 0x00007070);
			mt76_set(dev, MT_TXOP_HLDR_ET,
				 MT_TXOP_HLDR_TX40M_BLK_EN);
		पूर्ण अन्यथा अणु
			mt76_wr(dev, MT_BBP(AGC, 2), 0x003a6464);
			mt76_clear(dev, MT_TXOP_HLDR_ET,
				   MT_TXOP_HLDR_TX40M_BLK_EN);
		पूर्ण
	पूर्ण
	mt76x02_edcca_tx_enable(dev, true);
	dev->ed_monitor_learning = true;

	/* clear previous CCA समयr value */
	mt76_rr(dev, MT_ED_CCA_TIMER);
	dev->ed_समय = kसमय_get_bootसमय();
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_edcca_init);

#घोषणा MT_EDCCA_TH		92
#घोषणा MT_EDCCA_BLOCK_TH	2
#घोषणा MT_EDCCA_LEARN_TH	50
#घोषणा MT_EDCCA_LEARN_CCA	180
#घोषणा MT_EDCCA_LEARN_TIMEOUT	(20 * HZ)

अटल व्योम mt76x02_edcca_check(काष्ठा mt76x02_dev *dev)
अणु
	kसमय_प्रकार cur_समय;
	u32 active, val, busy;

	cur_समय = kसमय_get_bootसमय();
	val = mt76_rr(dev, MT_ED_CCA_TIMER);

	active = kसमय_प्रकारo_us(kसमय_sub(cur_समय, dev->ed_समय));
	dev->ed_समय = cur_समय;

	busy = (val * 100) / active;
	busy = min_t(u32, busy, 100);

	अगर (busy > MT_EDCCA_TH) अणु
		dev->ed_trigger++;
		dev->ed_silent = 0;
	पूर्ण अन्यथा अणु
		dev->ed_silent++;
		dev->ed_trigger = 0;
	पूर्ण

	अगर (dev->cal.agc_lowest_gain &&
	    dev->cal.false_cca > MT_EDCCA_LEARN_CCA &&
	    dev->ed_trigger > MT_EDCCA_LEARN_TH) अणु
		dev->ed_monitor_learning = false;
		dev->ed_trigger_समयout = jअगरfies + 20 * HZ;
	पूर्ण अन्यथा अगर (!dev->ed_monitor_learning &&
		   समय_is_after_jअगरfies(dev->ed_trigger_समयout)) अणु
		dev->ed_monitor_learning = true;
		mt76x02_edcca_tx_enable(dev, true);
	पूर्ण

	अगर (dev->ed_monitor_learning)
		वापस;

	अगर (dev->ed_trigger > MT_EDCCA_BLOCK_TH && !dev->ed_tx_blocked)
		mt76x02_edcca_tx_enable(dev, false);
	अन्यथा अगर (dev->ed_silent > MT_EDCCA_BLOCK_TH && dev->ed_tx_blocked)
		mt76x02_edcca_tx_enable(dev, true);
पूर्ण

व्योम mt76x02_mac_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt76x02_dev *dev = container_of(work, काष्ठा mt76x02_dev,
					       mphy.mac_work.work);
	पूर्णांक i, idx;

	mutex_lock(&dev->mt76.mutex);

	mt76_update_survey(&dev->mt76);
	क्रम (i = 0, idx = 0; i < 16; i++) अणु
		u32 val = mt76_rr(dev, MT_TX_AGG_CNT(i));

		dev->mt76.aggr_stats[idx++] += val & 0xffff;
		dev->mt76.aggr_stats[idx++] += val >> 16;
	पूर्ण

	अगर (!dev->mt76.beacon_mask)
		mt76x02_check_mac_err(dev);

	अगर (dev->ed_monitor)
		mt76x02_edcca_check(dev);

	mutex_unlock(&dev->mt76.mutex);

	mt76_tx_status_check(&dev->mt76, शून्य, false);

	ieee80211_queue_delayed_work(mt76_hw(dev), &dev->mphy.mac_work,
				     MT_MAC_WORK_INTERVAL);
पूर्ण

व्योम mt76x02_mac_cc_reset(काष्ठा mt76x02_dev *dev)
अणु
	dev->mphy.survey_समय = kसमय_get_bootसमय();

	mt76_wr(dev, MT_CH_TIME_CFG,
		MT_CH_TIME_CFG_TIMER_EN |
		MT_CH_TIME_CFG_TX_AS_BUSY |
		MT_CH_TIME_CFG_RX_AS_BUSY |
		MT_CH_TIME_CFG_NAV_AS_BUSY |
		MT_CH_TIME_CFG_EIFS_AS_BUSY |
		MT_CH_CCA_RC_EN |
		FIELD_PREP(MT_CH_TIME_CFG_CH_TIMER_CLR, 1));

	/* channel cycle counters पढ़ो-and-clear */
	mt76_rr(dev, MT_CH_BUSY);
	mt76_rr(dev, MT_CH_IDLE);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_mac_cc_reset);

व्योम mt76x02_mac_set_bssid(काष्ठा mt76x02_dev *dev, u8 idx, स्थिर u8 *addr)
अणु
	idx &= 7;
	mt76_wr(dev, MT_MAC_APC_BSSID_L(idx), get_unaligned_le32(addr));
	mt76_rmw_field(dev, MT_MAC_APC_BSSID_H(idx), MT_MAC_APC_BSSID_H_ADDR,
		       get_unaligned_le16(addr + 4));
पूर्ण
