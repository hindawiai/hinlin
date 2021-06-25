<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 */

#समावेश "mt7601u.h"
#समावेश "trace.h"
#समावेश <linux/etherdevice.h>

व्योम mt7601u_set_macaddr(काष्ठा mt7601u_dev *dev, स्थिर u8 *addr)
अणु
	ether_addr_copy(dev->macaddr, addr);

	अगर (!is_valid_ether_addr(dev->macaddr)) अणु
		eth_अक्रमom_addr(dev->macaddr);
		dev_info(dev->dev,
			 "Invalid MAC address, using random address %pM\n",
			 dev->macaddr);
	पूर्ण

	mt76_wr(dev, MT_MAC_ADDR_DW0, get_unaligned_le32(dev->macaddr));
	mt76_wr(dev, MT_MAC_ADDR_DW1, get_unaligned_le16(dev->macaddr + 4) |
		FIELD_PREP(MT_MAC_ADDR_DW1_U2ME_MASK, 0xff));
पूर्ण

अटल व्योम
mt76_mac_process_tx_rate(काष्ठा ieee80211_tx_rate *txrate, u16 rate)
अणु
	u8 idx = FIELD_GET(MT_TXWI_RATE_MCS, rate);

	txrate->idx = 0;
	txrate->flags = 0;
	txrate->count = 1;

	चयन (FIELD_GET(MT_TXWI_RATE_PHY_MODE, rate)) अणु
	हाल MT_PHY_TYPE_OFDM:
		txrate->idx = idx + 4;
		वापस;
	हाल MT_PHY_TYPE_CCK:
		अगर (idx >= 8)
			idx -= 8;

		txrate->idx = idx;
		वापस;
	हाल MT_PHY_TYPE_HT_GF:
		txrate->flags |= IEEE80211_TX_RC_GREEN_FIELD;
		fallthrough;
	हाल MT_PHY_TYPE_HT:
		txrate->flags |= IEEE80211_TX_RC_MCS;
		txrate->idx = idx;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण

	अगर (FIELD_GET(MT_TXWI_RATE_BW, rate) == MT_PHY_BW_40)
		txrate->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;

	अगर (rate & MT_TXWI_RATE_SGI)
		txrate->flags |= IEEE80211_TX_RC_SHORT_GI;
पूर्ण

अटल व्योम
mt76_mac_fill_tx_status(काष्ठा mt7601u_dev *dev, काष्ठा ieee80211_tx_info *info,
			काष्ठा mt76_tx_status *st)
अणु
	काष्ठा ieee80211_tx_rate *rate = info->status.rates;
	पूर्णांक cur_idx, last_rate;
	पूर्णांक i;

	last_rate = min_t(पूर्णांक, st->retry, IEEE80211_TX_MAX_RATES - 1);
	mt76_mac_process_tx_rate(&rate[last_rate], st->rate);
	अगर (last_rate < IEEE80211_TX_MAX_RATES - 1)
		rate[last_rate + 1].idx = -1;

	cur_idx = rate[last_rate].idx + st->retry;
	क्रम (i = 0; i <= last_rate; i++) अणु
		rate[i].flags = rate[last_rate].flags;
		rate[i].idx = max_t(पूर्णांक, 0, cur_idx - i);
		rate[i].count = 1;
	पूर्ण

	अगर (last_rate > 0)
		rate[last_rate - 1].count = st->retry + 1 - last_rate;

	info->status.ampdu_len = 1;
	info->status.ampdu_ack_len = st->success;

	अगर (st->is_probe)
		info->flags |= IEEE80211_TX_CTL_RATE_CTRL_PROBE;

	अगर (st->aggr)
		info->flags |= IEEE80211_TX_CTL_AMPDU |
			       IEEE80211_TX_STAT_AMPDU;

	अगर (!st->ack_req)
		info->flags |= IEEE80211_TX_CTL_NO_ACK;
	अन्यथा अगर (st->success)
		info->flags |= IEEE80211_TX_STAT_ACK;
पूर्ण

u16 mt76_mac_tx_rate_val(काष्ठा mt7601u_dev *dev,
			 स्थिर काष्ठा ieee80211_tx_rate *rate, u8 *nss_val)
अणु
	u16 rateval;
	u8 phy, rate_idx;
	u8 nss = 1;
	u8 bw = 0;

	अगर (rate->flags & IEEE80211_TX_RC_MCS) अणु
		rate_idx = rate->idx;
		nss = 1 + (rate->idx >> 3);
		phy = MT_PHY_TYPE_HT;
		अगर (rate->flags & IEEE80211_TX_RC_GREEN_FIELD)
			phy = MT_PHY_TYPE_HT_GF;
		अगर (rate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
			bw = 1;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा ieee80211_rate *r;
		पूर्णांक band = dev->chandef.chan->band;
		u16 val;

		r = &dev->hw->wiphy->bands[band]->bitrates[rate->idx];
		अगर (rate->flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE)
			val = r->hw_value_लघु;
		अन्यथा
			val = r->hw_value;

		phy = val >> 8;
		rate_idx = val & 0xff;
		bw = 0;
	पूर्ण

	rateval = FIELD_PREP(MT_RXWI_RATE_MCS, rate_idx);
	rateval |= FIELD_PREP(MT_RXWI_RATE_PHY, phy);
	rateval |= FIELD_PREP(MT_RXWI_RATE_BW, bw);
	अगर (rate->flags & IEEE80211_TX_RC_SHORT_GI)
		rateval |= MT_RXWI_RATE_SGI;

	*nss_val = nss;
	वापस rateval;
पूर्ण

व्योम mt76_mac_wcid_set_rate(काष्ठा mt7601u_dev *dev, काष्ठा mt76_wcid *wcid,
			    स्थिर काष्ठा ieee80211_tx_rate *rate)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);
	wcid->tx_rate = mt76_mac_tx_rate_val(dev, rate, &wcid->tx_rate_nss);
	wcid->tx_rate_set = true;
	spin_unlock_irqrestore(&dev->lock, flags);
पूर्ण

काष्ठा mt76_tx_status mt7601u_mac_fetch_tx_status(काष्ठा mt7601u_dev *dev)
अणु
	काष्ठा mt76_tx_status stat = अणुपूर्ण;
	u32 val;

	val = mt7601u_rr(dev, MT_TX_STAT_FIFO);
	stat.valid = !!(val & MT_TX_STAT_FIFO_VALID);
	stat.success = !!(val & MT_TX_STAT_FIFO_SUCCESS);
	stat.aggr = !!(val & MT_TX_STAT_FIFO_AGGR);
	stat.ack_req = !!(val & MT_TX_STAT_FIFO_ACKREQ);
	stat.pktid = FIELD_GET(MT_TX_STAT_FIFO_PID_TYPE, val);
	stat.wcid = FIELD_GET(MT_TX_STAT_FIFO_WCID, val);
	stat.rate = FIELD_GET(MT_TX_STAT_FIFO_RATE, val);

	वापस stat;
पूर्ण

व्योम mt76_send_tx_status(काष्ठा mt7601u_dev *dev, काष्ठा mt76_tx_status *stat)
अणु
	काष्ठा ieee80211_tx_info info = अणुपूर्ण;
	काष्ठा ieee80211_sta *sta = शून्य;
	काष्ठा mt76_wcid *wcid = शून्य;
	व्योम *msta;

	rcu_पढ़ो_lock();
	अगर (stat->wcid < ARRAY_SIZE(dev->wcid))
		wcid = rcu_dereference(dev->wcid[stat->wcid]);

	अगर (wcid) अणु
		msta = container_of(wcid, काष्ठा mt76_sta, wcid);
		sta = container_of(msta, काष्ठा ieee80211_sta,
				   drv_priv);
	पूर्ण

	mt76_mac_fill_tx_status(dev, &info, stat);

	spin_lock_bh(&dev->mac_lock);
	ieee80211_tx_status_noskb(dev->hw, sta, &info);
	spin_unlock_bh(&dev->mac_lock);

	rcu_पढ़ो_unlock();
पूर्ण

व्योम mt7601u_mac_set_protection(काष्ठा mt7601u_dev *dev, bool legacy_prot,
				पूर्णांक ht_mode)
अणु
	पूर्णांक mode = ht_mode & IEEE80211_HT_OP_MODE_PROTECTION;
	bool non_gf = !!(ht_mode & IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT);
	u32 prot[6];
	bool ht_rts[4] = अणुपूर्ण;
	पूर्णांक i;

	prot[0] = MT_PROT_NAV_SHORT |
		  MT_PROT_TXOP_ALLOW_ALL |
		  MT_PROT_RTS_THR_EN;
	prot[1] = prot[0];
	अगर (legacy_prot)
		prot[1] |= MT_PROT_CTRL_CTS2SELF;

	prot[2] = prot[4] = MT_PROT_NAV_SHORT | MT_PROT_TXOP_ALLOW_BW20;
	prot[3] = prot[5] = MT_PROT_NAV_SHORT | MT_PROT_TXOP_ALLOW_ALL;

	अगर (legacy_prot) अणु
		prot[2] |= MT_PROT_RATE_CCK_11;
		prot[3] |= MT_PROT_RATE_CCK_11;
		prot[4] |= MT_PROT_RATE_CCK_11;
		prot[5] |= MT_PROT_RATE_CCK_11;
	पूर्ण अन्यथा अणु
		prot[2] |= MT_PROT_RATE_OFDM_24;
		prot[3] |= MT_PROT_RATE_DUP_OFDM_24;
		prot[4] |= MT_PROT_RATE_OFDM_24;
		prot[5] |= MT_PROT_RATE_DUP_OFDM_24;
	पूर्ण

	चयन (mode) अणु
	हाल IEEE80211_HT_OP_MODE_PROTECTION_NONE:
		अवरोध;

	हाल IEEE80211_HT_OP_MODE_PROTECTION_NONMEMBER:
		ht_rts[0] = ht_rts[1] = ht_rts[2] = ht_rts[3] = true;
		अवरोध;

	हाल IEEE80211_HT_OP_MODE_PROTECTION_20MHZ:
		ht_rts[1] = ht_rts[3] = true;
		अवरोध;

	हाल IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED:
		ht_rts[0] = ht_rts[1] = ht_rts[2] = ht_rts[3] = true;
		अवरोध;
	पूर्ण

	अगर (non_gf)
		ht_rts[2] = ht_rts[3] = true;

	क्रम (i = 0; i < 4; i++)
		अगर (ht_rts[i])
			prot[i + 2] |= MT_PROT_CTRL_RTS_CTS;

	क्रम (i = 0; i < 6; i++)
		mt7601u_wr(dev, MT_CCK_PROT_CFG + i * 4, prot[i]);
पूर्ण

व्योम mt7601u_mac_set_लघु_preamble(काष्ठा mt7601u_dev *dev, bool लघु_preamb)
अणु
	अगर (लघु_preamb)
		mt76_set(dev, MT_AUTO_RSP_CFG, MT_AUTO_RSP_PREAMB_SHORT);
	अन्यथा
		mt76_clear(dev, MT_AUTO_RSP_CFG, MT_AUTO_RSP_PREAMB_SHORT);
पूर्ण

व्योम mt7601u_mac_config_tsf(काष्ठा mt7601u_dev *dev, bool enable, पूर्णांक पूर्णांकerval)
अणु
	u32 val = mt7601u_rr(dev, MT_BEACON_TIME_CFG);

	val &= ~(MT_BEACON_TIME_CFG_TIMER_EN |
		 MT_BEACON_TIME_CFG_SYNC_MODE |
		 MT_BEACON_TIME_CFG_TBTT_EN);

	अगर (!enable) अणु
		mt7601u_wr(dev, MT_BEACON_TIME_CFG, val);
		वापस;
	पूर्ण

	val &= ~MT_BEACON_TIME_CFG_INTVAL;
	val |= FIELD_PREP(MT_BEACON_TIME_CFG_INTVAL, पूर्णांकerval << 4) |
		MT_BEACON_TIME_CFG_TIMER_EN |
		MT_BEACON_TIME_CFG_SYNC_MODE |
		MT_BEACON_TIME_CFG_TBTT_EN;
पूर्ण

अटल व्योम mt7601u_check_mac_err(काष्ठा mt7601u_dev *dev)
अणु
	u32 val = mt7601u_rr(dev, 0x10f4);

	अगर (!(val & BIT(29)) || !(val & (BIT(7) | BIT(5))))
		वापस;

	dev_err(dev->dev, "Error: MAC specific condition occurred\n");

	mt76_set(dev, MT_MAC_SYS_CTRL, MT_MAC_SYS_CTRL_RESET_CSR);
	udelay(10);
	mt76_clear(dev, MT_MAC_SYS_CTRL, MT_MAC_SYS_CTRL_RESET_CSR);
पूर्ण

व्योम mt7601u_mac_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7601u_dev *dev = container_of(work, काष्ठा mt7601u_dev,
					       mac_work.work);
	काष्ठा अणु
		u32 addr_base;
		u32 span;
		u64 *stat_base;
	पूर्ण spans[] = अणु
		अणु MT_RX_STA_CNT0,	3,	dev->stats.rx_stat पूर्ण,
		अणु MT_TX_STA_CNT0,	3,	dev->stats.tx_stat पूर्ण,
		अणु MT_TX_AGG_STAT,	1,	dev->stats.aggr_stat पूर्ण,
		अणु MT_MPDU_DENSITY_CNT,	1,	dev->stats.zero_len_del पूर्ण,
		अणु MT_TX_AGG_CNT_BASE0,	8,	&dev->stats.aggr_n[0] पूर्ण,
		अणु MT_TX_AGG_CNT_BASE1,	8,	&dev->stats.aggr_n[16] पूर्ण,
	पूर्ण;
	u32 sum, n;
	पूर्णांक i, j, k;

	/* Note: using MCU_RANDOM_READ is actually slower then पढ़ोing all the
	 *	 रेजिस्टरs by hand.  MCU takes ca. 20ms to complete पढ़ो of 24
	 *	 रेजिस्टरs जबतक पढ़ोing them one by one will takes roughly
	 *	 24*200us =~ 5ms.
	 */

	k = 0;
	n = 0;
	sum = 0;
	क्रम (i = 0; i < ARRAY_SIZE(spans); i++)
		क्रम (j = 0; j < spans[i].span; j++) अणु
			u32 val = mt7601u_rr(dev, spans[i].addr_base + j * 4);

			spans[i].stat_base[j * 2] += val & 0xffff;
			spans[i].stat_base[j * 2 + 1] += val >> 16;

			/* Calculate average AMPDU length */
			अगर (spans[i].addr_base != MT_TX_AGG_CNT_BASE0 &&
			    spans[i].addr_base != MT_TX_AGG_CNT_BASE1)
				जारी;

			n += (val >> 16) + (val & 0xffff);
			sum += (val & 0xffff) * (1 + k * 2) +
				(val >> 16) * (2 + k * 2);
			k++;
		पूर्ण

	atomic_set(&dev->avg_ampdu_len, n ? DIV_ROUND_CLOSEST(sum, n) : 1);

	mt7601u_check_mac_err(dev);

	ieee80211_queue_delayed_work(dev->hw, &dev->mac_work, 10 * HZ);
पूर्ण

व्योम
mt7601u_mac_wcid_setup(काष्ठा mt7601u_dev *dev, u8 idx, u8 vअगर_idx, u8 *mac)
अणु
	u8 zmac[ETH_ALEN] = अणुपूर्ण;
	u32 attr;

	attr = FIELD_PREP(MT_WCID_ATTR_BSS_IDX, vअगर_idx & 7) |
	       FIELD_PREP(MT_WCID_ATTR_BSS_IDX_EXT, !!(vअगर_idx & 8));

	mt76_wr(dev, MT_WCID_ATTR(idx), attr);

	अगर (mac)
		स_नकल(zmac, mac, माप(zmac));

	mt7601u_addr_wr(dev, MT_WCID_ADDR(idx), zmac);
पूर्ण

व्योम mt7601u_mac_set_ampdu_factor(काष्ठा mt7601u_dev *dev)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा mt76_wcid *wcid;
	व्योम *msta;
	u8 min_factor = 3;
	पूर्णांक i;

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < ARRAY_SIZE(dev->wcid); i++) अणु
		wcid = rcu_dereference(dev->wcid[i]);
		अगर (!wcid)
			जारी;

		msta = container_of(wcid, काष्ठा mt76_sta, wcid);
		sta = container_of(msta, काष्ठा ieee80211_sta, drv_priv);

		min_factor = min(min_factor, sta->ht_cap.ampdu_factor);
	पूर्ण
	rcu_पढ़ो_unlock();

	mt7601u_wr(dev, MT_MAX_LEN_CFG, 0xa0fff |
		   FIELD_PREP(MT_MAX_LEN_CFG_AMPDU, min_factor));
पूर्ण

अटल व्योम
mt76_mac_process_rate(काष्ठा ieee80211_rx_status *status, u16 rate)
अणु
	u8 idx = FIELD_GET(MT_RXWI_RATE_MCS, rate);

	चयन (FIELD_GET(MT_RXWI_RATE_PHY, rate)) अणु
	हाल MT_PHY_TYPE_OFDM:
		अगर (WARN_ON(idx >= 8))
			idx = 0;
		idx += 4;

		status->rate_idx = idx;
		वापस;
	हाल MT_PHY_TYPE_CCK:
		अगर (idx >= 8) अणु
			idx -= 8;
			status->enc_flags |= RX_ENC_FLAG_SHORTPRE;
		पूर्ण

		अगर (WARN_ON(idx >= 4))
			idx = 0;

		status->rate_idx = idx;
		वापस;
	हाल MT_PHY_TYPE_HT_GF:
		status->enc_flags |= RX_ENC_FLAG_HT_GF;
		fallthrough;
	हाल MT_PHY_TYPE_HT:
		status->encoding = RX_ENC_HT;
		status->rate_idx = idx;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण

	अगर (rate & MT_RXWI_RATE_SGI)
		status->enc_flags |= RX_ENC_FLAG_SHORT_GI;

	अगर (rate & MT_RXWI_RATE_STBC)
		status->enc_flags |= 1 << RX_ENC_FLAG_STBC_SHIFT;

	अगर (rate & MT_RXWI_RATE_BW)
		status->bw = RATE_INFO_BW_40;
पूर्ण

अटल व्योम
mt7601u_rx_monitor_beacon(काष्ठा mt7601u_dev *dev, काष्ठा mt7601u_rxwi *rxwi,
			  u16 rate, पूर्णांक rssi)
अणु
	dev->bcn_freq_off = rxwi->freq_off;
	dev->bcn_phy_mode = FIELD_GET(MT_RXWI_RATE_PHY, rate);
	ewma_rssi_add(&dev->avg_rssi, -rssi);
पूर्ण

अटल पूर्णांक
mt7601u_rx_is_our_beacon(काष्ठा mt7601u_dev *dev, u8 *data)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)data;

	वापस ieee80211_is_beacon(hdr->frame_control) &&
		ether_addr_equal(hdr->addr2, dev->ap_bssid);
पूर्ण

u32 mt76_mac_process_rx(काष्ठा mt7601u_dev *dev, काष्ठा sk_buff *skb,
			u8 *data, व्योम *rxi)
अणु
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	काष्ठा mt7601u_rxwi *rxwi = rxi;
	u32 len, ctl = le32_to_cpu(rxwi->ctl);
	u16 rate = le16_to_cpu(rxwi->rate);
	पूर्णांक rssi;

	len = FIELD_GET(MT_RXWI_CTL_MPDU_LEN, ctl);
	अगर (len < 10)
		वापस 0;

	अगर (rxwi->rxinfo & cpu_to_le32(MT_RXINFO_DECRYPT)) अणु
		status->flag |= RX_FLAG_DECRYPTED;
		status->flag |= RX_FLAG_MMIC_STRIPPED;
		status->flag |= RX_FLAG_MIC_STRIPPED;
		status->flag |= RX_FLAG_ICV_STRIPPED;
		status->flag |= RX_FLAG_IV_STRIPPED;
	पूर्ण
	/* let mac80211 take care of PN validation since apparently
	 * the hardware करोes not support it
	 */
	अगर (rxwi->rxinfo & cpu_to_le32(MT_RXINFO_PN_LEN))
		status->flag &= ~RX_FLAG_IV_STRIPPED;

	status->chains = BIT(0);
	rssi = mt7601u_phy_get_rssi(dev, rxwi, rate);
	status->chain_संकेत[0] = status->संकेत = rssi;
	status->freq = dev->chandef.chan->center_freq;
	status->band = dev->chandef.chan->band;

	mt76_mac_process_rate(status, rate);

	spin_lock_bh(&dev->con_mon_lock);
	अगर (mt7601u_rx_is_our_beacon(dev, data))
		mt7601u_rx_monitor_beacon(dev, rxwi, rate, rssi);
	अन्यथा अगर (rxwi->rxinfo & cpu_to_le32(MT_RXINFO_U2M))
		ewma_rssi_add(&dev->avg_rssi, -rssi);
	spin_unlock_bh(&dev->con_mon_lock);

	वापस len;
पूर्ण

अटल क्रमागत mt76_cipher_type
mt76_mac_get_key_info(काष्ठा ieee80211_key_conf *key, u8 *key_data)
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

पूर्णांक mt76_mac_wcid_set_key(काष्ठा mt7601u_dev *dev, u8 idx,
			  काष्ठा ieee80211_key_conf *key)
अणु
	क्रमागत mt76_cipher_type cipher;
	u8 key_data[32];
	u8 iv_data[8];
	u32 val;

	cipher = mt76_mac_get_key_info(key, key_data);
	अगर (cipher == MT_CIPHER_NONE && key)
		वापस -EINVAL;

	trace_set_key(dev, idx);

	mt7601u_wr_copy(dev, MT_WCID_KEY(idx), key_data, माप(key_data));

	स_रखो(iv_data, 0, माप(iv_data));
	अगर (key) अणु
		iv_data[3] = key->keyidx << 6;
		अगर (cipher >= MT_CIPHER_TKIP) अणु
			/* Note: start with 1 to comply with spec,
			 *	 (see comment on common/cmm_wpa.c:4291).
			 */
			iv_data[0] |= 1;
			iv_data[3] |= 0x20;
		पूर्ण
	पूर्ण
	mt7601u_wr_copy(dev, MT_WCID_IV(idx), iv_data, माप(iv_data));

	val = mt7601u_rr(dev, MT_WCID_ATTR(idx));
	val &= ~MT_WCID_ATTR_PKEY_MODE & ~MT_WCID_ATTR_PKEY_MODE_EXT;
	val |= FIELD_PREP(MT_WCID_ATTR_PKEY_MODE, cipher & 7) |
	       FIELD_PREP(MT_WCID_ATTR_PKEY_MODE_EXT, cipher >> 3);
	val &= ~MT_WCID_ATTR_PAIRWISE;
	val |= MT_WCID_ATTR_PAIRWISE *
		!!(key && key->flags & IEEE80211_KEY_FLAG_PAIRWISE);
	mt7601u_wr(dev, MT_WCID_ATTR(idx), val);

	वापस 0;
पूर्ण

पूर्णांक mt76_mac_shared_key_setup(काष्ठा mt7601u_dev *dev, u8 vअगर_idx, u8 key_idx,
			      काष्ठा ieee80211_key_conf *key)
अणु
	क्रमागत mt76_cipher_type cipher;
	u8 key_data[32];
	u32 val;

	cipher = mt76_mac_get_key_info(key, key_data);
	अगर (cipher == MT_CIPHER_NONE && key)
		वापस -EINVAL;

	trace_set_shared_key(dev, vअगर_idx, key_idx);

	mt7601u_wr_copy(dev, MT_SKEY(vअगर_idx, key_idx),
			key_data, माप(key_data));

	val = mt76_rr(dev, MT_SKEY_MODE(vअगर_idx));
	val &= ~(MT_SKEY_MODE_MASK << MT_SKEY_MODE_SHIFT(vअगर_idx, key_idx));
	val |= cipher << MT_SKEY_MODE_SHIFT(vअगर_idx, key_idx);
	mt76_wr(dev, MT_SKEY_MODE(vअगर_idx), val);

	वापस 0;
पूर्ण
