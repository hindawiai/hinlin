<शैली गुरु>
// SPDX-License-Identअगरier: ISC

#समावेश <linux/etherdevice.h>
#समावेश <linux/समयkeeping.h>
#समावेश "mt7603.h"
#समावेश "mac.h"
#समावेश "../trace.h"

#घोषणा MT_PSE_PAGE_SIZE	128

अटल u32
mt7603_ac_queue_mask0(u32 mask)
अणु
	u32 ret = 0;

	ret |= GENMASK(3, 0) * !!(mask & BIT(0));
	ret |= GENMASK(8, 5) * !!(mask & BIT(1));
	ret |= GENMASK(13, 10) * !!(mask & BIT(2));
	ret |= GENMASK(19, 16) * !!(mask & BIT(3));
	वापस ret;
पूर्ण

अटल व्योम
mt76_stop_tx_ac(काष्ठा mt7603_dev *dev, u32 mask)
अणु
	mt76_set(dev, MT_WF_ARB_TX_STOP_0, mt7603_ac_queue_mask0(mask));
पूर्ण

अटल व्योम
mt76_start_tx_ac(काष्ठा mt7603_dev *dev, u32 mask)
अणु
	mt76_set(dev, MT_WF_ARB_TX_START_0, mt7603_ac_queue_mask0(mask));
पूर्ण

व्योम mt7603_mac_reset_counters(काष्ठा mt7603_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++)
		mt76_rr(dev, MT_TX_AGG_CNT(i));

	स_रखो(dev->mt76.aggr_stats, 0, माप(dev->mt76.aggr_stats));
पूर्ण

व्योम mt7603_mac_set_timing(काष्ठा mt7603_dev *dev)
अणु
	u32 cck = FIELD_PREP(MT_TIMEOUT_VAL_PLCP, 231) |
		  FIELD_PREP(MT_TIMEOUT_VAL_CCA, 48);
	u32 ofdm = FIELD_PREP(MT_TIMEOUT_VAL_PLCP, 60) |
		   FIELD_PREP(MT_TIMEOUT_VAL_CCA, 24);
	पूर्णांक offset = 3 * dev->coverage_class;
	u32 reg_offset = FIELD_PREP(MT_TIMEOUT_VAL_PLCP, offset) |
			 FIELD_PREP(MT_TIMEOUT_VAL_CCA, offset);
	bool is_5ghz = dev->mphy.chandef.chan->band == NL80211_BAND_5GHZ;
	पूर्णांक sअगरs;
	u32 val;

	अगर (is_5ghz)
		sअगरs = 16;
	अन्यथा
		sअगरs = 10;

	mt76_set(dev, MT_ARB_SCR,
		 MT_ARB_SCR_TX_DISABLE | MT_ARB_SCR_RX_DISABLE);
	udelay(1);

	mt76_wr(dev, MT_TIMEOUT_CCK, cck + reg_offset);
	mt76_wr(dev, MT_TIMEOUT_OFDM, ofdm + reg_offset);
	mt76_wr(dev, MT_IFS,
		FIELD_PREP(MT_IFS_EIFS, 360) |
		FIELD_PREP(MT_IFS_RIFS, 2) |
		FIELD_PREP(MT_IFS_SIFS, sअगरs) |
		FIELD_PREP(MT_IFS_SLOT, dev->slotसमय));

	अगर (dev->slotसमय < 20 || is_5ghz)
		val = MT7603_CFEND_RATE_DEFAULT;
	अन्यथा
		val = MT7603_CFEND_RATE_11B;

	mt76_rmw_field(dev, MT_AGG_CONTROL, MT_AGG_CONTROL_CFEND_RATE, val);

	mt76_clear(dev, MT_ARB_SCR,
		   MT_ARB_SCR_TX_DISABLE | MT_ARB_SCR_RX_DISABLE);
पूर्ण

अटल व्योम
mt7603_wtbl_update(काष्ठा mt7603_dev *dev, पूर्णांक idx, u32 mask)
अणु
	mt76_rmw(dev, MT_WTBL_UPDATE, MT_WTBL_UPDATE_WLAN_IDX,
		 FIELD_PREP(MT_WTBL_UPDATE_WLAN_IDX, idx) | mask);

	mt76_poll(dev, MT_WTBL_UPDATE, MT_WTBL_UPDATE_BUSY, 0, 5000);
पूर्ण

अटल u32
mt7603_wtbl1_addr(पूर्णांक idx)
अणु
	वापस MT_WTBL1_BASE + idx * MT_WTBL1_SIZE;
पूर्ण

अटल u32
mt7603_wtbl2_addr(पूर्णांक idx)
अणु
	/* Mapped to WTBL2 */
	वापस MT_PCIE_REMAP_BASE_1 + idx * MT_WTBL2_SIZE;
पूर्ण

अटल u32
mt7603_wtbl3_addr(पूर्णांक idx)
अणु
	u32 base = mt7603_wtbl2_addr(MT7603_WTBL_SIZE);

	वापस base + idx * MT_WTBL3_SIZE;
पूर्ण

अटल u32
mt7603_wtbl4_addr(पूर्णांक idx)
अणु
	u32 base = mt7603_wtbl3_addr(MT7603_WTBL_SIZE);

	वापस base + idx * MT_WTBL4_SIZE;
पूर्ण

व्योम mt7603_wtbl_init(काष्ठा mt7603_dev *dev, पूर्णांक idx, पूर्णांक vअगर,
		      स्थिर u8 *mac_addr)
अणु
	स्थिर व्योम *_mac = mac_addr;
	u32 addr = mt7603_wtbl1_addr(idx);
	u32 w0 = 0, w1 = 0;
	पूर्णांक i;

	अगर (_mac) अणु
		w0 = FIELD_PREP(MT_WTBL1_W0_ADDR_HI,
				get_unaligned_le16(_mac + 4));
		w1 = FIELD_PREP(MT_WTBL1_W1_ADDR_LO,
				get_unaligned_le32(_mac));
	पूर्ण

	अगर (vअगर < 0)
		vअगर = 0;
	अन्यथा
		w0 |= MT_WTBL1_W0_RX_CHECK_A1;
	w0 |= FIELD_PREP(MT_WTBL1_W0_MUAR_IDX, vअगर);

	mt76_poll(dev, MT_WTBL_UPDATE, MT_WTBL_UPDATE_BUSY, 0, 5000);

	mt76_set(dev, addr + 0 * 4, w0);
	mt76_set(dev, addr + 1 * 4, w1);
	mt76_set(dev, addr + 2 * 4, MT_WTBL1_W2_ADMISSION_CONTROL);

	mt76_stop_tx_ac(dev, GENMASK(3, 0));
	addr = mt7603_wtbl2_addr(idx);
	क्रम (i = 0; i < MT_WTBL2_SIZE; i += 4)
		mt76_wr(dev, addr + i, 0);
	mt7603_wtbl_update(dev, idx, MT_WTBL_UPDATE_WTBL2);
	mt76_start_tx_ac(dev, GENMASK(3, 0));

	addr = mt7603_wtbl3_addr(idx);
	क्रम (i = 0; i < MT_WTBL3_SIZE; i += 4)
		mt76_wr(dev, addr + i, 0);

	addr = mt7603_wtbl4_addr(idx);
	क्रम (i = 0; i < MT_WTBL4_SIZE; i += 4)
		mt76_wr(dev, addr + i, 0);

	mt7603_wtbl_update(dev, idx, MT_WTBL_UPDATE_ADM_COUNT_CLEAR);
पूर्ण

अटल व्योम
mt7603_wtbl_set_skip_tx(काष्ठा mt7603_dev *dev, पूर्णांक idx, bool enabled)
अणु
	u32 addr = mt7603_wtbl1_addr(idx);
	u32 val = mt76_rr(dev, addr + 3 * 4);

	val &= ~MT_WTBL1_W3_SKIP_TX;
	val |= enabled * MT_WTBL1_W3_SKIP_TX;

	mt76_wr(dev, addr + 3 * 4, val);
पूर्ण

व्योम mt7603_filter_tx(काष्ठा mt7603_dev *dev, पूर्णांक idx, bool पात)
अणु
	पूर्णांक i, port, queue;

	अगर (पात) अणु
		port = 3; /* PSE */
		queue = 8; /* मुक्त queue */
	पूर्ण अन्यथा अणु
		port = 0; /* HIF */
		queue = 1; /* MCU queue */
	पूर्ण

	mt7603_wtbl_set_skip_tx(dev, idx, true);

	mt76_wr(dev, MT_TX_ABORT, MT_TX_ABORT_EN |
			FIELD_PREP(MT_TX_ABORT_WCID, idx));

	क्रम (i = 0; i < 4; i++) अणु
		mt76_wr(dev, MT_DMA_FQCR0, MT_DMA_FQCR0_BUSY |
			FIELD_PREP(MT_DMA_FQCR0_TARGET_WCID, idx) |
			FIELD_PREP(MT_DMA_FQCR0_TARGET_QID, i) |
			FIELD_PREP(MT_DMA_FQCR0_DEST_PORT_ID, port) |
			FIELD_PREP(MT_DMA_FQCR0_DEST_QUEUE_ID, queue));

		WARN_ON_ONCE(!mt76_poll(dev, MT_DMA_FQCR0, MT_DMA_FQCR0_BUSY,
					0, 5000));
	पूर्ण

	mt76_wr(dev, MT_TX_ABORT, 0);

	mt7603_wtbl_set_skip_tx(dev, idx, false);
पूर्ण

व्योम mt7603_wtbl_set_smps(काष्ठा mt7603_dev *dev, काष्ठा mt7603_sta *sta,
			  bool enabled)
अणु
	u32 addr = mt7603_wtbl1_addr(sta->wcid.idx);

	अगर (sta->smps == enabled)
		वापस;

	mt76_rmw_field(dev, addr + 2 * 4, MT_WTBL1_W2_SMPS, enabled);
	sta->smps = enabled;
पूर्ण

व्योम mt7603_wtbl_set_ps(काष्ठा mt7603_dev *dev, काष्ठा mt7603_sta *sta,
			bool enabled)
अणु
	पूर्णांक idx = sta->wcid.idx;
	u32 addr;

	spin_lock_bh(&dev->ps_lock);

	अगर (sta->ps == enabled)
		जाओ out;

	mt76_wr(dev, MT_PSE_RTA,
		FIELD_PREP(MT_PSE_RTA_TAG_ID, idx) |
		FIELD_PREP(MT_PSE_RTA_PORT_ID, 0) |
		FIELD_PREP(MT_PSE_RTA_QUEUE_ID, 1) |
		FIELD_PREP(MT_PSE_RTA_REसूचीECT_EN, enabled) |
		MT_PSE_RTA_WRITE | MT_PSE_RTA_BUSY);

	mt76_poll(dev, MT_PSE_RTA, MT_PSE_RTA_BUSY, 0, 5000);

	अगर (enabled)
		mt7603_filter_tx(dev, idx, false);

	addr = mt7603_wtbl1_addr(idx);
	mt76_set(dev, MT_WTBL1_OR, MT_WTBL1_OR_PSM_WRITE);
	mt76_rmw(dev, addr + 3 * 4, MT_WTBL1_W3_POWER_SAVE,
		 enabled * MT_WTBL1_W3_POWER_SAVE);
	mt76_clear(dev, MT_WTBL1_OR, MT_WTBL1_OR_PSM_WRITE);
	sta->ps = enabled;

out:
	spin_unlock_bh(&dev->ps_lock);
पूर्ण

व्योम mt7603_wtbl_clear(काष्ठा mt7603_dev *dev, पूर्णांक idx)
अणु
	पूर्णांक wtbl2_frame_size = MT_PSE_PAGE_SIZE / MT_WTBL2_SIZE;
	पूर्णांक wtbl2_frame = idx / wtbl2_frame_size;
	पूर्णांक wtbl2_entry = idx % wtbl2_frame_size;

	पूर्णांक wtbl3_base_frame = MT_WTBL3_OFFSET / MT_PSE_PAGE_SIZE;
	पूर्णांक wtbl3_frame_size = MT_PSE_PAGE_SIZE / MT_WTBL3_SIZE;
	पूर्णांक wtbl3_frame = wtbl3_base_frame + idx / wtbl3_frame_size;
	पूर्णांक wtbl3_entry = (idx % wtbl3_frame_size) * 2;

	पूर्णांक wtbl4_base_frame = MT_WTBL4_OFFSET / MT_PSE_PAGE_SIZE;
	पूर्णांक wtbl4_frame_size = MT_PSE_PAGE_SIZE / MT_WTBL4_SIZE;
	पूर्णांक wtbl4_frame = wtbl4_base_frame + idx / wtbl4_frame_size;
	पूर्णांक wtbl4_entry = idx % wtbl4_frame_size;

	u32 addr = MT_WTBL1_BASE + idx * MT_WTBL1_SIZE;
	पूर्णांक i;

	mt76_poll(dev, MT_WTBL_UPDATE, MT_WTBL_UPDATE_BUSY, 0, 5000);

	mt76_wr(dev, addr + 0 * 4,
		MT_WTBL1_W0_RX_CHECK_A1 |
		MT_WTBL1_W0_RX_CHECK_A2 |
		MT_WTBL1_W0_RX_VALID);
	mt76_wr(dev, addr + 1 * 4, 0);
	mt76_wr(dev, addr + 2 * 4, 0);

	mt76_set(dev, MT_WTBL1_OR, MT_WTBL1_OR_PSM_WRITE);

	mt76_wr(dev, addr + 3 * 4,
		FIELD_PREP(MT_WTBL1_W3_WTBL2_FRAME_ID, wtbl2_frame) |
		FIELD_PREP(MT_WTBL1_W3_WTBL2_ENTRY_ID, wtbl2_entry) |
		FIELD_PREP(MT_WTBL1_W3_WTBL4_FRAME_ID, wtbl4_frame) |
		MT_WTBL1_W3_I_PSM | MT_WTBL1_W3_KEEP_I_PSM);
	mt76_wr(dev, addr + 4 * 4,
		FIELD_PREP(MT_WTBL1_W4_WTBL3_FRAME_ID, wtbl3_frame) |
		FIELD_PREP(MT_WTBL1_W4_WTBL3_ENTRY_ID, wtbl3_entry) |
		FIELD_PREP(MT_WTBL1_W4_WTBL4_ENTRY_ID, wtbl4_entry));

	mt76_clear(dev, MT_WTBL1_OR, MT_WTBL1_OR_PSM_WRITE);

	addr = mt7603_wtbl2_addr(idx);

	/* Clear BA inक्रमmation */
	mt76_wr(dev, addr + (15 * 4), 0);

	mt76_stop_tx_ac(dev, GENMASK(3, 0));
	क्रम (i = 2; i <= 4; i++)
		mt76_wr(dev, addr + (i * 4), 0);
	mt7603_wtbl_update(dev, idx, MT_WTBL_UPDATE_WTBL2);
	mt76_start_tx_ac(dev, GENMASK(3, 0));

	mt7603_wtbl_update(dev, idx, MT_WTBL_UPDATE_RX_COUNT_CLEAR);
	mt7603_wtbl_update(dev, idx, MT_WTBL_UPDATE_TX_COUNT_CLEAR);
	mt7603_wtbl_update(dev, idx, MT_WTBL_UPDATE_ADM_COUNT_CLEAR);
पूर्ण

व्योम mt7603_wtbl_update_cap(काष्ठा mt7603_dev *dev, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7603_sta *msta = (काष्ठा mt7603_sta *)sta->drv_priv;
	पूर्णांक idx = msta->wcid.idx;
	u8 ampdu_density;
	u32 addr;
	u32 val;

	addr = mt7603_wtbl1_addr(idx);

	ampdu_density = sta->ht_cap.ampdu_density;
	अगर (ampdu_density < IEEE80211_HT_MPDU_DENSITY_4)
		ampdu_density = IEEE80211_HT_MPDU_DENSITY_4;

	val = mt76_rr(dev, addr + 2 * 4);
	val &= MT_WTBL1_W2_KEY_TYPE | MT_WTBL1_W2_ADMISSION_CONTROL;
	val |= FIELD_PREP(MT_WTBL1_W2_AMPDU_FACTOR, sta->ht_cap.ampdu_factor) |
	       FIELD_PREP(MT_WTBL1_W2_MPDU_DENSITY, sta->ht_cap.ampdu_density) |
	       MT_WTBL1_W2_TXS_BAF_REPORT;

	अगर (sta->ht_cap.cap)
		val |= MT_WTBL1_W2_HT;
	अगर (sta->vht_cap.cap)
		val |= MT_WTBL1_W2_VHT;

	mt76_wr(dev, addr + 2 * 4, val);

	addr = mt7603_wtbl2_addr(idx);
	val = mt76_rr(dev, addr + 9 * 4);
	val &= ~(MT_WTBL2_W9_SHORT_GI_20 | MT_WTBL2_W9_SHORT_GI_40 |
		 MT_WTBL2_W9_SHORT_GI_80);
	अगर (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20)
		val |= MT_WTBL2_W9_SHORT_GI_20;
	अगर (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40)
		val |= MT_WTBL2_W9_SHORT_GI_40;
	mt76_wr(dev, addr + 9 * 4, val);
पूर्ण

व्योम mt7603_mac_rx_ba_reset(काष्ठा mt7603_dev *dev, व्योम *addr, u8 tid)
अणु
	mt76_wr(dev, MT_BA_CONTROL_0, get_unaligned_le32(addr));
	mt76_wr(dev, MT_BA_CONTROL_1,
		(get_unaligned_le16(addr + 4) |
		 FIELD_PREP(MT_BA_CONTROL_1_TID, tid) |
		 MT_BA_CONTROL_1_RESET));
पूर्ण

व्योम mt7603_mac_tx_ba_reset(काष्ठा mt7603_dev *dev, पूर्णांक wcid, पूर्णांक tid,
			    पूर्णांक ba_size)
अणु
	u32 addr = mt7603_wtbl2_addr(wcid);
	u32 tid_mask = FIELD_PREP(MT_WTBL2_W15_BA_EN_TIDS, BIT(tid)) |
		       (MT_WTBL2_W15_BA_WIN_SIZE <<
			(tid * MT_WTBL2_W15_BA_WIN_SIZE_SHIFT));
	u32 tid_val;
	पूर्णांक i;

	अगर (ba_size < 0) अणु
		/* disable */
		mt76_clear(dev, addr + (15 * 4), tid_mask);
		वापस;
	पूर्ण

	क्रम (i = 7; i > 0; i--) अणु
		अगर (ba_size >= MT_AGG_SIZE_LIMIT(i))
			अवरोध;
	पूर्ण

	tid_val = FIELD_PREP(MT_WTBL2_W15_BA_EN_TIDS, BIT(tid)) |
		  i << (tid * MT_WTBL2_W15_BA_WIN_SIZE_SHIFT);

	mt76_rmw(dev, addr + (15 * 4), tid_mask, tid_val);
पूर्ण

व्योम mt7603_mac_sta_poll(काष्ठा mt7603_dev *dev)
अणु
	अटल स्थिर u8 ac_to_tid[4] = अणु
		[IEEE80211_AC_BE] = 0,
		[IEEE80211_AC_BK] = 1,
		[IEEE80211_AC_VI] = 4,
		[IEEE80211_AC_VO] = 6
	पूर्ण;
	काष्ठा ieee80211_sta *sta;
	काष्ठा mt7603_sta *msta;
	u32 total_airसमय = 0;
	u32 airसमय[4];
	u32 addr;
	पूर्णांक i;

	rcu_पढ़ो_lock();

	जबतक (1) अणु
		bool clear = false;

		spin_lock_bh(&dev->sta_poll_lock);
		अगर (list_empty(&dev->sta_poll_list)) अणु
			spin_unlock_bh(&dev->sta_poll_lock);
			अवरोध;
		पूर्ण

		msta = list_first_entry(&dev->sta_poll_list, काष्ठा mt7603_sta,
					poll_list);
		list_del_init(&msta->poll_list);
		spin_unlock_bh(&dev->sta_poll_lock);

		addr = mt7603_wtbl4_addr(msta->wcid.idx);
		क्रम (i = 0; i < 4; i++) अणु
			u32 airसमय_last = msta->tx_airसमय_ac[i];

			msta->tx_airसमय_ac[i] = mt76_rr(dev, addr + i * 8);
			airसमय[i] = msta->tx_airसमय_ac[i] - airसमय_last;
			airसमय[i] *= 32;
			total_airसमय += airसमय[i];

			अगर (msta->tx_airसमय_ac[i] & BIT(22))
				clear = true;
		पूर्ण

		अगर (clear) अणु
			mt7603_wtbl_update(dev, msta->wcid.idx,
					   MT_WTBL_UPDATE_ADM_COUNT_CLEAR);
			स_रखो(msta->tx_airसमय_ac, 0,
			       माप(msta->tx_airसमय_ac));
		पूर्ण

		अगर (!msta->wcid.sta)
			जारी;

		sta = container_of((व्योम *)msta, काष्ठा ieee80211_sta, drv_priv);
		क्रम (i = 0; i < 4; i++) अणु
			काष्ठा mt76_queue *q = dev->mphy.q_tx[i];
			u8 qidx = q->hw_idx;
			u8 tid = ac_to_tid[i];
			u32 txसमय = airसमय[qidx];

			अगर (!txसमय)
				जारी;

			ieee80211_sta_रेजिस्टर_airसमय(sta, tid, txसमय, 0);
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	अगर (!total_airसमय)
		वापस;

	spin_lock_bh(&dev->mt76.cc_lock);
	dev->mphy.chan_state->cc_tx += total_airसमय;
	spin_unlock_bh(&dev->mt76.cc_lock);
पूर्ण

अटल काष्ठा mt76_wcid *
mt7603_rx_get_wcid(काष्ठा mt7603_dev *dev, u8 idx, bool unicast)
अणु
	काष्ठा mt7603_sta *sta;
	काष्ठा mt76_wcid *wcid;

	अगर (idx >= MT7603_WTBL_SIZE)
		वापस शून्य;

	wcid = rcu_dereference(dev->mt76.wcid[idx]);
	अगर (unicast || !wcid)
		वापस wcid;

	अगर (!wcid->sta)
		वापस शून्य;

	sta = container_of(wcid, काष्ठा mt7603_sta, wcid);
	अगर (!sta->vअगर)
		वापस शून्य;

	वापस &sta->vअगर->sta.wcid;
पूर्ण

पूर्णांक
mt7603_mac_fill_rx(काष्ठा mt7603_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt76_rx_status *status = (काष्ठा mt76_rx_status *)skb->cb;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_hdr *hdr;
	__le32 *rxd = (__le32 *)skb->data;
	u32 rxd0 = le32_to_cpu(rxd[0]);
	u32 rxd1 = le32_to_cpu(rxd[1]);
	u32 rxd2 = le32_to_cpu(rxd[2]);
	bool unicast = rxd1 & MT_RXD1_NORMAL_U2M;
	bool insert_ccmp_hdr = false;
	bool हटाओ_pad;
	पूर्णांक idx;
	पूर्णांक i;

	स_रखो(status, 0, माप(*status));

	i = FIELD_GET(MT_RXD1_NORMAL_CH_FREQ, rxd1);
	sband = (i & 1) ? &dev->mphy.sband_5g.sband : &dev->mphy.sband_2g.sband;
	i >>= 1;

	idx = FIELD_GET(MT_RXD2_NORMAL_WLAN_IDX, rxd2);
	status->wcid = mt7603_rx_get_wcid(dev, idx, unicast);

	status->band = sband->band;
	अगर (i < sband->n_channels)
		status->freq = sband->channels[i].center_freq;

	अगर (rxd2 & MT_RXD2_NORMAL_FCS_ERR)
		status->flag |= RX_FLAG_FAILED_FCS_CRC;

	अगर (rxd2 & MT_RXD2_NORMAL_TKIP_MIC_ERR)
		status->flag |= RX_FLAG_MMIC_ERROR;

	अगर (FIELD_GET(MT_RXD2_NORMAL_SEC_MODE, rxd2) != 0 &&
	    !(rxd2 & (MT_RXD2_NORMAL_CLM | MT_RXD2_NORMAL_CM))) अणु
		status->flag |= RX_FLAG_DECRYPTED;
		status->flag |= RX_FLAG_IV_STRIPPED;
		status->flag |= RX_FLAG_MMIC_STRIPPED | RX_FLAG_MIC_STRIPPED;
	पूर्ण

	हटाओ_pad = rxd1 & MT_RXD1_NORMAL_HDR_OFFSET;

	अगर (rxd2 & MT_RXD2_NORMAL_MAX_LEN_ERROR)
		वापस -EINVAL;

	अगर (!sband->channels)
		वापस -EINVAL;

	rxd += 4;
	अगर (rxd0 & MT_RXD0_NORMAL_GROUP_4) अणु
		rxd += 4;
		अगर ((u8 *)rxd - skb->data >= skb->len)
			वापस -EINVAL;
	पूर्ण
	अगर (rxd0 & MT_RXD0_NORMAL_GROUP_1) अणु
		u8 *data = (u8 *)rxd;

		अगर (status->flag & RX_FLAG_DECRYPTED) अणु
			status->iv[0] = data[5];
			status->iv[1] = data[4];
			status->iv[2] = data[3];
			status->iv[3] = data[2];
			status->iv[4] = data[1];
			status->iv[5] = data[0];

			insert_ccmp_hdr = FIELD_GET(MT_RXD2_NORMAL_FRAG, rxd2);
		पूर्ण

		rxd += 4;
		अगर ((u8 *)rxd - skb->data >= skb->len)
			वापस -EINVAL;
	पूर्ण
	अगर (rxd0 & MT_RXD0_NORMAL_GROUP_2) अणु
		status->बारtamp = le32_to_cpu(rxd[0]);
		status->flag |= RX_FLAG_MACTIME_START;

		अगर (!(rxd2 & (MT_RXD2_NORMAL_NON_AMPDU_SUB |
			      MT_RXD2_NORMAL_NON_AMPDU))) अणु
			status->flag |= RX_FLAG_AMPDU_DETAILS;

			/* all subframes of an A-MPDU have the same बारtamp */
			अगर (dev->rx_ampdu_ts != status->बारtamp) अणु
				अगर (!++dev->ampdu_ref)
					dev->ampdu_ref++;
			पूर्ण
			dev->rx_ampdu_ts = status->बारtamp;

			status->ampdu_ref = dev->ampdu_ref;
		पूर्ण

		rxd += 2;
		अगर ((u8 *)rxd - skb->data >= skb->len)
			वापस -EINVAL;
	पूर्ण
	अगर (rxd0 & MT_RXD0_NORMAL_GROUP_3) अणु
		u32 rxdg0 = le32_to_cpu(rxd[0]);
		u32 rxdg3 = le32_to_cpu(rxd[3]);
		bool cck = false;

		i = FIELD_GET(MT_RXV1_TX_RATE, rxdg0);
		चयन (FIELD_GET(MT_RXV1_TX_MODE, rxdg0)) अणु
		हाल MT_PHY_TYPE_CCK:
			cck = true;
			fallthrough;
		हाल MT_PHY_TYPE_OFDM:
			i = mt76_get_rate(&dev->mt76, sband, i, cck);
			अवरोध;
		हाल MT_PHY_TYPE_HT_GF:
		हाल MT_PHY_TYPE_HT:
			status->encoding = RX_ENC_HT;
			अगर (i > 15)
				वापस -EINVAL;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अगर (rxdg0 & MT_RXV1_HT_SHORT_GI)
			status->enc_flags |= RX_ENC_FLAG_SHORT_GI;
		अगर (rxdg0 & MT_RXV1_HT_AD_CODE)
			status->enc_flags |= RX_ENC_FLAG_LDPC;

		status->enc_flags |= RX_ENC_FLAG_STBC_MASK *
				    FIELD_GET(MT_RXV1_HT_STBC, rxdg0);

		status->rate_idx = i;

		status->chains = dev->mphy.antenna_mask;
		status->chain_संकेत[0] = FIELD_GET(MT_RXV4_IB_RSSI0, rxdg3) +
					  dev->rssi_offset[0];
		status->chain_संकेत[1] = FIELD_GET(MT_RXV4_IB_RSSI1, rxdg3) +
					  dev->rssi_offset[1];

		status->संकेत = status->chain_संकेत[0];
		अगर (status->chains & BIT(1))
			status->संकेत = max(status->संकेत,
					     status->chain_संकेत[1]);

		अगर (FIELD_GET(MT_RXV1_FRAME_MODE, rxdg0) == 1)
			status->bw = RATE_INFO_BW_40;

		rxd += 6;
		अगर ((u8 *)rxd - skb->data >= skb->len)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	skb_pull(skb, (u8 *)rxd - skb->data + 2 * हटाओ_pad);

	अगर (insert_ccmp_hdr) अणु
		u8 key_id = FIELD_GET(MT_RXD1_NORMAL_KEY_ID, rxd1);

		mt76_insert_ccmp_hdr(skb, key_id);
	पूर्ण

	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	अगर (!status->wcid || !ieee80211_is_data_qos(hdr->frame_control))
		वापस 0;

	status->aggr = unicast &&
		       !ieee80211_is_qos_nullfunc(hdr->frame_control);
	status->qos_ctl = *ieee80211_get_qos_ctl(hdr);
	status->seqno = IEEE80211_SEQ_TO_SN(le16_to_cpu(hdr->seq_ctrl));

	वापस 0;
पूर्ण

अटल u16
mt7603_mac_tx_rate_val(काष्ठा mt7603_dev *dev,
		       स्थिर काष्ठा ieee80211_tx_rate *rate, bool stbc, u8 *bw)
अणु
	u8 phy, nss, rate_idx;
	u16 rateval;

	*bw = 0;
	अगर (rate->flags & IEEE80211_TX_RC_MCS) अणु
		rate_idx = rate->idx;
		nss = 1 + (rate->idx >> 3);
		phy = MT_PHY_TYPE_HT;
		अगर (rate->flags & IEEE80211_TX_RC_GREEN_FIELD)
			phy = MT_PHY_TYPE_HT_GF;
		अगर (rate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
			*bw = 1;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा ieee80211_rate *r;
		पूर्णांक band = dev->mphy.chandef.chan->band;
		u16 val;

		nss = 1;
		r = &mt76_hw(dev)->wiphy->bands[band]->bitrates[rate->idx];
		अगर (rate->flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE)
			val = r->hw_value_लघु;
		अन्यथा
			val = r->hw_value;

		phy = val >> 8;
		rate_idx = val & 0xff;
	पूर्ण

	rateval = (FIELD_PREP(MT_TX_RATE_IDX, rate_idx) |
		   FIELD_PREP(MT_TX_RATE_MODE, phy));

	अगर (stbc && nss == 1)
		rateval |= MT_TX_RATE_STBC;

	वापस rateval;
पूर्ण

व्योम mt7603_wtbl_set_rates(काष्ठा mt7603_dev *dev, काष्ठा mt7603_sta *sta,
			   काष्ठा ieee80211_tx_rate *probe_rate,
			   काष्ठा ieee80211_tx_rate *rates)
अणु
	काष्ठा ieee80211_tx_rate *ref;
	पूर्णांक wcid = sta->wcid.idx;
	u32 addr = mt7603_wtbl2_addr(wcid);
	bool stbc = false;
	पूर्णांक n_rates = sta->n_rates;
	u8 bw, bw_prev, bw_idx = 0;
	u16 val[4];
	u16 probe_val;
	u32 w9 = mt76_rr(dev, addr + 9 * 4);
	bool rateset;
	पूर्णांक i, k;

	अगर (!mt76_poll(dev, MT_WTBL_UPDATE, MT_WTBL_UPDATE_BUSY, 0, 5000))
		वापस;

	क्रम (i = n_rates; i < 4; i++)
		rates[i] = rates[n_rates - 1];

	rateset = !(sta->rate_set_tsf & BIT(0));
	स_नकल(sta->rateset[rateset].rates, rates,
	       माप(sta->rateset[rateset].rates));
	अगर (probe_rate) अणु
		sta->rateset[rateset].probe_rate = *probe_rate;
		ref = &sta->rateset[rateset].probe_rate;
	पूर्ण अन्यथा अणु
		sta->rateset[rateset].probe_rate.idx = -1;
		ref = &sta->rateset[rateset].rates[0];
	पूर्ण

	rates = sta->rateset[rateset].rates;
	क्रम (i = 0; i < ARRAY_SIZE(sta->rateset[rateset].rates); i++) अणु
		/*
		 * We करोn't support चयनing between लघु and दीर्घ GI
		 * within the rate set. For accurate tx status reporting, we
		 * need to make sure that flags match.
		 * For improved perक्रमmance, aव्योम duplicate entries by
		 * decrementing the MCS index अगर necessary
		 */
		अगर ((ref->flags ^ rates[i].flags) & IEEE80211_TX_RC_SHORT_GI)
			rates[i].flags ^= IEEE80211_TX_RC_SHORT_GI;

		क्रम (k = 0; k < i; k++) अणु
			अगर (rates[i].idx != rates[k].idx)
				जारी;
			अगर ((rates[i].flags ^ rates[k].flags) &
			    IEEE80211_TX_RC_40_MHZ_WIDTH)
				जारी;

			अगर (!rates[i].idx)
				जारी;

			rates[i].idx--;
		पूर्ण
	पूर्ण

	w9 &= MT_WTBL2_W9_SHORT_GI_20 | MT_WTBL2_W9_SHORT_GI_40 |
	      MT_WTBL2_W9_SHORT_GI_80;

	val[0] = mt7603_mac_tx_rate_val(dev, &rates[0], stbc, &bw);
	bw_prev = bw;

	अगर (probe_rate) अणु
		probe_val = mt7603_mac_tx_rate_val(dev, probe_rate, stbc, &bw);
		अगर (bw)
			bw_idx = 1;
		अन्यथा
			bw_prev = 0;
	पूर्ण अन्यथा अणु
		probe_val = val[0];
	पूर्ण

	w9 |= FIELD_PREP(MT_WTBL2_W9_CC_BW_SEL, bw);
	w9 |= FIELD_PREP(MT_WTBL2_W9_BW_CAP, bw);

	val[1] = mt7603_mac_tx_rate_val(dev, &rates[1], stbc, &bw);
	अगर (bw_prev) अणु
		bw_idx = 3;
		bw_prev = bw;
	पूर्ण

	val[2] = mt7603_mac_tx_rate_val(dev, &rates[2], stbc, &bw);
	अगर (bw_prev) अणु
		bw_idx = 5;
		bw_prev = bw;
	पूर्ण

	val[3] = mt7603_mac_tx_rate_val(dev, &rates[3], stbc, &bw);
	अगर (bw_prev)
		bw_idx = 7;

	w9 |= FIELD_PREP(MT_WTBL2_W9_CHANGE_BW_RATE,
		       bw_idx ? bw_idx - 1 : 7);

	mt76_wr(dev, MT_WTBL_RIUCR0, w9);

	mt76_wr(dev, MT_WTBL_RIUCR1,
		FIELD_PREP(MT_WTBL_RIUCR1_RATE0, probe_val) |
		FIELD_PREP(MT_WTBL_RIUCR1_RATE1, val[0]) |
		FIELD_PREP(MT_WTBL_RIUCR1_RATE2_LO, val[1]));

	mt76_wr(dev, MT_WTBL_RIUCR2,
		FIELD_PREP(MT_WTBL_RIUCR2_RATE2_HI, val[1] >> 8) |
		FIELD_PREP(MT_WTBL_RIUCR2_RATE3, val[1]) |
		FIELD_PREP(MT_WTBL_RIUCR2_RATE4, val[2]) |
		FIELD_PREP(MT_WTBL_RIUCR2_RATE5_LO, val[2]));

	mt76_wr(dev, MT_WTBL_RIUCR3,
		FIELD_PREP(MT_WTBL_RIUCR3_RATE5_HI, val[2] >> 4) |
		FIELD_PREP(MT_WTBL_RIUCR3_RATE6, val[3]) |
		FIELD_PREP(MT_WTBL_RIUCR3_RATE7, val[3]));

	mt76_set(dev, MT_LPON_T0CR, MT_LPON_T0CR_MODE); /* TSF पढ़ो */
	sta->rate_set_tsf = (mt76_rr(dev, MT_LPON_UTTR0) & ~BIT(0)) | rateset;

	mt76_wr(dev, MT_WTBL_UPDATE,
		FIELD_PREP(MT_WTBL_UPDATE_WLAN_IDX, wcid) |
		MT_WTBL_UPDATE_RATE_UPDATE |
		MT_WTBL_UPDATE_TX_COUNT_CLEAR);

	अगर (!(sta->wcid.tx_info & MT_WCID_TX_INFO_SET))
		mt76_poll(dev, MT_WTBL_UPDATE, MT_WTBL_UPDATE_BUSY, 0, 5000);

	sta->rate_count = 2 * MT7603_RATE_RETRY * n_rates;
	sta->wcid.tx_info |= MT_WCID_TX_INFO_SET;
पूर्ण

अटल क्रमागत mt7603_cipher_type
mt7603_mac_get_key_info(काष्ठा ieee80211_key_conf *key, u8 *key_data)
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
		/* Rx/Tx MIC keys are swapped */
		स_नकल(key_data + 16, key->key + 24, 8);
		स_नकल(key_data + 24, key->key + 16, 8);
		वापस MT_CIPHER_TKIP;
	हाल WLAN_CIPHER_SUITE_CCMP:
		वापस MT_CIPHER_AES_CCMP;
	शेष:
		वापस MT_CIPHER_NONE;
	पूर्ण
पूर्ण

पूर्णांक mt7603_wtbl_set_key(काष्ठा mt7603_dev *dev, पूर्णांक wcid,
			काष्ठा ieee80211_key_conf *key)
अणु
	क्रमागत mt7603_cipher_type cipher;
	u32 addr = mt7603_wtbl3_addr(wcid);
	u8 key_data[32];
	पूर्णांक key_len = माप(key_data);

	cipher = mt7603_mac_get_key_info(key, key_data);
	अगर (cipher == MT_CIPHER_NONE && key)
		वापस -EOPNOTSUPP;

	अगर (key && (cipher == MT_CIPHER_WEP40 || cipher == MT_CIPHER_WEP104)) अणु
		addr += key->keyidx * 16;
		key_len = 16;
	पूर्ण

	mt76_wr_copy(dev, addr, key_data, key_len);

	addr = mt7603_wtbl1_addr(wcid);
	mt76_rmw_field(dev, addr + 2 * 4, MT_WTBL1_W2_KEY_TYPE, cipher);
	अगर (key)
		mt76_rmw_field(dev, addr, MT_WTBL1_W0_KEY_IDX, key->keyidx);
	mt76_rmw_field(dev, addr, MT_WTBL1_W0_RX_KEY_VALID, !!key);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7603_mac_ग_लिखो_txwi(काष्ठा mt7603_dev *dev, __le32 *txwi,
		      काष्ठा sk_buff *skb, क्रमागत mt76_txq_id qid,
		      काष्ठा mt76_wcid *wcid, काष्ठा ieee80211_sta *sta,
		      पूर्णांक pid, काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_tx_rate *rate = &info->control.rates[0];
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_bar *bar = (काष्ठा ieee80211_bar *)skb->data;
	काष्ठा ieee80211_vअगर *vअगर = info->control.vअगर;
	काष्ठा mt76_queue *q = dev->mphy.q_tx[qid];
	काष्ठा mt7603_vअगर *mvअगर;
	पूर्णांक wlan_idx;
	पूर्णांक hdr_len = ieee80211_get_hdrlen_from_skb(skb);
	पूर्णांक tx_count = 8;
	u8 frame_type, frame_subtype;
	u16 fc = le16_to_cpu(hdr->frame_control);
	u16 seqno = 0;
	u8 vअगर_idx = 0;
	u32 val;
	u8 bw;

	अगर (vअगर) अणु
		mvअगर = (काष्ठा mt7603_vअगर *)vअगर->drv_priv;
		vअगर_idx = mvअगर->idx;
		अगर (vअगर_idx && qid >= MT_TXQ_BEACON)
			vअगर_idx += 0x10;
	पूर्ण

	अगर (sta) अणु
		काष्ठा mt7603_sta *msta = (काष्ठा mt7603_sta *)sta->drv_priv;

		tx_count = msta->rate_count;
	पूर्ण

	अगर (wcid)
		wlan_idx = wcid->idx;
	अन्यथा
		wlan_idx = MT7603_WTBL_RESERVED;

	frame_type = (fc & IEEE80211_FCTL_FTYPE) >> 2;
	frame_subtype = (fc & IEEE80211_FCTL_STYPE) >> 4;

	val = FIELD_PREP(MT_TXD0_TX_BYTES, skb->len + MT_TXD_SIZE) |
	      FIELD_PREP(MT_TXD0_Q_IDX, q->hw_idx);
	txwi[0] = cpu_to_le32(val);

	val = MT_TXD1_LONG_FORMAT |
	      FIELD_PREP(MT_TXD1_OWN_MAC, vअगर_idx) |
	      FIELD_PREP(MT_TXD1_TID,
			 skb->priority & IEEE80211_QOS_CTL_TID_MASK) |
	      FIELD_PREP(MT_TXD1_HDR_FORMAT, MT_HDR_FORMAT_802_11) |
	      FIELD_PREP(MT_TXD1_HDR_INFO, hdr_len / 2) |
	      FIELD_PREP(MT_TXD1_WLAN_IDX, wlan_idx) |
	      FIELD_PREP(MT_TXD1_PROTECTED, !!key);
	txwi[1] = cpu_to_le32(val);

	अगर (info->flags & IEEE80211_TX_CTL_NO_ACK)
		txwi[1] |= cpu_to_le32(MT_TXD1_NO_ACK);

	val = FIELD_PREP(MT_TXD2_FRAME_TYPE, frame_type) |
	      FIELD_PREP(MT_TXD2_SUB_TYPE, frame_subtype) |
	      FIELD_PREP(MT_TXD2_MULTICAST,
			 is_multicast_ether_addr(hdr->addr1));
	txwi[2] = cpu_to_le32(val);

	अगर (!(info->flags & IEEE80211_TX_CTL_AMPDU))
		txwi[2] |= cpu_to_le32(MT_TXD2_BA_DISABLE);

	txwi[4] = 0;

	val = MT_TXD5_TX_STATUS_HOST | MT_TXD5_SW_POWER_MGMT |
	      FIELD_PREP(MT_TXD5_PID, pid);
	txwi[5] = cpu_to_le32(val);

	txwi[6] = 0;

	अगर (rate->idx >= 0 && rate->count &&
	    !(info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE)) अणु
		bool stbc = info->flags & IEEE80211_TX_CTL_STBC;
		u16 rateval = mt7603_mac_tx_rate_val(dev, rate, stbc, &bw);

		txwi[2] |= cpu_to_le32(MT_TXD2_FIX_RATE);

		val = MT_TXD6_FIXED_BW |
		      FIELD_PREP(MT_TXD6_BW, bw) |
		      FIELD_PREP(MT_TXD6_TX_RATE, rateval);
		txwi[6] |= cpu_to_le32(val);

		अगर (rate->flags & IEEE80211_TX_RC_SHORT_GI)
			txwi[6] |= cpu_to_le32(MT_TXD6_SGI);

		अगर (!(rate->flags & IEEE80211_TX_RC_MCS))
			txwi[2] |= cpu_to_le32(MT_TXD2_BA_DISABLE);

		tx_count = rate->count;
	पूर्ण

	/* use maximum tx count क्रम beacons and buffered multicast */
	अगर (qid >= MT_TXQ_BEACON)
		tx_count = 0x1f;

	val = FIELD_PREP(MT_TXD3_REM_TX_COUNT, tx_count) |
		  MT_TXD3_SN_VALID;

	अगर (ieee80211_is_data_qos(hdr->frame_control))
		seqno = le16_to_cpu(hdr->seq_ctrl);
	अन्यथा अगर (ieee80211_is_back_req(hdr->frame_control))
		seqno = le16_to_cpu(bar->start_seq_num);
	अन्यथा
		val &= ~MT_TXD3_SN_VALID;

	val |= FIELD_PREP(MT_TXD3_SEQ, seqno >> 4);

	txwi[3] = cpu_to_le32(val);

	अगर (key) अणु
		u64 pn = atomic64_inc_वापस(&key->tx_pn);

		txwi[3] |= cpu_to_le32(MT_TXD3_PN_VALID);
		txwi[4] = cpu_to_le32(pn & GENMASK(31, 0));
		txwi[5] |= cpu_to_le32(FIELD_PREP(MT_TXD5_PN_HIGH, pn >> 32));
	पूर्ण

	txwi[7] = 0;

	वापस 0;
पूर्ण

पूर्णांक mt7603_tx_prepare_skb(काष्ठा mt76_dev *mdev, व्योम *txwi_ptr,
			  क्रमागत mt76_txq_id qid, काष्ठा mt76_wcid *wcid,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा mt76_tx_info *tx_info)
अणु
	काष्ठा mt7603_dev *dev = container_of(mdev, काष्ठा mt7603_dev, mt76);
	काष्ठा mt7603_sta *msta = container_of(wcid, काष्ठा mt7603_sta, wcid);
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(tx_info->skb);
	काष्ठा ieee80211_key_conf *key = info->control.hw_key;
	पूर्णांक pid;

	अगर (!wcid)
		wcid = &dev->global_sta.wcid;

	अगर (sta) अणु
		msta = (काष्ठा mt7603_sta *)sta->drv_priv;

		अगर ((info->flags & (IEEE80211_TX_CTL_NO_PS_BUFFER |
				    IEEE80211_TX_CTL_CLEAR_PS_FILT)) ||
		    (info->control.flags & IEEE80211_TX_CTRL_PS_RESPONSE))
			mt7603_wtbl_set_ps(dev, msta, false);

		mt76_tx_check_agg_ssn(sta, tx_info->skb);
	पूर्ण

	pid = mt76_tx_status_skb_add(mdev, wcid, tx_info->skb);

	अगर (info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE) अणु
		spin_lock_bh(&dev->mt76.lock);
		mt7603_wtbl_set_rates(dev, msta, &info->control.rates[0],
				      msta->rates);
		msta->rate_probe = true;
		spin_unlock_bh(&dev->mt76.lock);
	पूर्ण

	mt7603_mac_ग_लिखो_txwi(dev, txwi_ptr, tx_info->skb, qid, wcid,
			      sta, pid, key);

	वापस 0;
पूर्ण

अटल bool
mt7603_fill_txs(काष्ठा mt7603_dev *dev, काष्ठा mt7603_sta *sta,
		काष्ठा ieee80211_tx_info *info, __le32 *txs_data)
अणु
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा mt7603_rate_set *rs;
	पूर्णांक first_idx = 0, last_idx;
	u32 rate_set_tsf;
	u32 final_rate;
	u32 final_rate_flags;
	bool rs_idx;
	bool ack_समयout;
	bool fixed_rate;
	bool probe;
	bool ampdu;
	bool cck = false;
	पूर्णांक count;
	u32 txs;
	पूर्णांक idx;
	पूर्णांक i;

	fixed_rate = info->status.rates[0].count;
	probe = !!(info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE);

	txs = le32_to_cpu(txs_data[4]);
	ampdu = !fixed_rate && (txs & MT_TXS4_AMPDU);
	count = FIELD_GET(MT_TXS4_TX_COUNT, txs);
	last_idx = FIELD_GET(MT_TXS4_LAST_TX_RATE, txs);

	txs = le32_to_cpu(txs_data[0]);
	final_rate = FIELD_GET(MT_TXS0_TX_RATE, txs);
	ack_समयout = txs & MT_TXS0_ACK_TIMEOUT;

	अगर (!ampdu && (txs & MT_TXS0_RTS_TIMEOUT))
		वापस false;

	अगर (txs & MT_TXS0_QUEUE_TIMEOUT)
		वापस false;

	अगर (!ack_समयout)
		info->flags |= IEEE80211_TX_STAT_ACK;

	info->status.ampdu_len = 1;
	info->status.ampdu_ack_len = !!(info->flags &
					IEEE80211_TX_STAT_ACK);

	अगर (ampdu || (info->flags & IEEE80211_TX_CTL_AMPDU))
		info->flags |= IEEE80211_TX_STAT_AMPDU | IEEE80211_TX_CTL_AMPDU;

	first_idx = max_t(पूर्णांक, 0, last_idx - (count - 1) / MT7603_RATE_RETRY);

	अगर (fixed_rate && !probe) अणु
		info->status.rates[0].count = count;
		i = 0;
		जाओ out;
	पूर्ण

	rate_set_tsf = READ_ONCE(sta->rate_set_tsf);
	rs_idx = !((u32)(FIELD_GET(MT_TXS1_F0_TIMESTAMP, le32_to_cpu(txs_data[1])) -
			 rate_set_tsf) < 1000000);
	rs_idx ^= rate_set_tsf & BIT(0);
	rs = &sta->rateset[rs_idx];

	अगर (!first_idx && rs->probe_rate.idx >= 0) अणु
		info->status.rates[0] = rs->probe_rate;

		spin_lock_bh(&dev->mt76.lock);
		अगर (sta->rate_probe) अणु
			mt7603_wtbl_set_rates(dev, sta, शून्य,
					      sta->rates);
			sta->rate_probe = false;
		पूर्ण
		spin_unlock_bh(&dev->mt76.lock);
	पूर्ण अन्यथा अणु
		info->status.rates[0] = rs->rates[first_idx / 2];
	पूर्ण
	info->status.rates[0].count = 0;

	क्रम (i = 0, idx = first_idx; count && idx <= last_idx; idx++) अणु
		काष्ठा ieee80211_tx_rate *cur_rate;
		पूर्णांक cur_count;

		cur_rate = &rs->rates[idx / 2];
		cur_count = min_t(पूर्णांक, MT7603_RATE_RETRY, count);
		count -= cur_count;

		अगर (idx && (cur_rate->idx != info->status.rates[i].idx ||
			    cur_rate->flags != info->status.rates[i].flags)) अणु
			i++;
			अगर (i == ARRAY_SIZE(info->status.rates)) अणु
				i--;
				अवरोध;
			पूर्ण

			info->status.rates[i] = *cur_rate;
			info->status.rates[i].count = 0;
		पूर्ण

		info->status.rates[i].count += cur_count;
	पूर्ण

out:
	final_rate_flags = info->status.rates[i].flags;

	चयन (FIELD_GET(MT_TX_RATE_MODE, final_rate)) अणु
	हाल MT_PHY_TYPE_CCK:
		cck = true;
		fallthrough;
	हाल MT_PHY_TYPE_OFDM:
		अगर (dev->mphy.chandef.chan->band == NL80211_BAND_5GHZ)
			sband = &dev->mphy.sband_5g.sband;
		अन्यथा
			sband = &dev->mphy.sband_2g.sband;
		final_rate &= GENMASK(5, 0);
		final_rate = mt76_get_rate(&dev->mt76, sband, final_rate,
					   cck);
		final_rate_flags = 0;
		अवरोध;
	हाल MT_PHY_TYPE_HT_GF:
	हाल MT_PHY_TYPE_HT:
		final_rate_flags |= IEEE80211_TX_RC_MCS;
		final_rate &= GENMASK(5, 0);
		अगर (final_rate > 15)
			वापस false;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	info->status.rates[i].idx = final_rate;
	info->status.rates[i].flags = final_rate_flags;

	वापस true;
पूर्ण

अटल bool
mt7603_mac_add_txs_skb(काष्ठा mt7603_dev *dev, काष्ठा mt7603_sta *sta, पूर्णांक pid,
		       __le32 *txs_data)
अणु
	काष्ठा mt76_dev *mdev = &dev->mt76;
	काष्ठा sk_buff_head list;
	काष्ठा sk_buff *skb;

	अगर (pid < MT_PACKET_ID_FIRST)
		वापस false;

	trace_mac_txकरोne(mdev, sta->wcid.idx, pid);

	mt76_tx_status_lock(mdev, &list);
	skb = mt76_tx_status_skb_get(mdev, &sta->wcid, pid, &list);
	अगर (skb) अणु
		काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

		अगर (!mt7603_fill_txs(dev, sta, info, txs_data)) अणु
			ieee80211_tx_info_clear_status(info);
			info->status.rates[0].idx = -1;
		पूर्ण

		mt76_tx_status_skb_करोne(mdev, skb, &list);
	पूर्ण
	mt76_tx_status_unlock(mdev, &list);

	वापस !!skb;
पूर्ण

व्योम mt7603_mac_add_txs(काष्ठा mt7603_dev *dev, व्योम *data)
अणु
	काष्ठा ieee80211_tx_info info = अणुपूर्ण;
	काष्ठा ieee80211_sta *sta = शून्य;
	काष्ठा mt7603_sta *msta = शून्य;
	काष्ठा mt76_wcid *wcid;
	__le32 *txs_data = data;
	u32 txs;
	u8 wcidx;
	u8 pid;

	txs = le32_to_cpu(txs_data[4]);
	pid = FIELD_GET(MT_TXS4_PID, txs);
	txs = le32_to_cpu(txs_data[3]);
	wcidx = FIELD_GET(MT_TXS3_WCID, txs);

	अगर (pid == MT_PACKET_ID_NO_ACK)
		वापस;

	अगर (wcidx >= MT7603_WTBL_SIZE)
		वापस;

	rcu_पढ़ो_lock();

	wcid = rcu_dereference(dev->mt76.wcid[wcidx]);
	अगर (!wcid)
		जाओ out;

	msta = container_of(wcid, काष्ठा mt7603_sta, wcid);
	sta = wcid_to_sta(wcid);

	अगर (list_empty(&msta->poll_list)) अणु
		spin_lock_bh(&dev->sta_poll_lock);
		list_add_tail(&msta->poll_list, &dev->sta_poll_list);
		spin_unlock_bh(&dev->sta_poll_lock);
	पूर्ण

	अगर (mt7603_mac_add_txs_skb(dev, msta, pid, txs_data))
		जाओ out;

	अगर (wcidx >= MT7603_WTBL_STA || !sta)
		जाओ out;

	अगर (mt7603_fill_txs(dev, msta, &info, txs_data))
		ieee80211_tx_status_noskb(mt76_hw(dev), sta, &info);

out:
	rcu_पढ़ो_unlock();
पूर्ण

व्योम mt7603_tx_complete_skb(काष्ठा mt76_dev *mdev, काष्ठा mt76_queue_entry *e)
अणु
	काष्ठा mt7603_dev *dev = container_of(mdev, काष्ठा mt7603_dev, mt76);
	काष्ठा sk_buff *skb = e->skb;

	अगर (!e->txwi) अणु
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	dev->tx_hang_check = 0;
	mt76_tx_complete_skb(mdev, e->wcid, skb);
पूर्ण

अटल bool
रुको_क्रम_wpdma(काष्ठा mt7603_dev *dev)
अणु
	वापस mt76_poll(dev, MT_WPDMA_GLO_CFG,
			 MT_WPDMA_GLO_CFG_TX_DMA_BUSY |
			 MT_WPDMA_GLO_CFG_RX_DMA_BUSY,
			 0, 1000);
पूर्ण

अटल व्योम mt7603_pse_reset(काष्ठा mt7603_dev *dev)
अणु
	/* Clear previous reset result */
	अगर (!dev->reset_cause[RESET_CAUSE_RESET_FAILED])
		mt76_clear(dev, MT_MCU_DEBUG_RESET, MT_MCU_DEBUG_RESET_PSE_S);

	/* Reset PSE */
	mt76_set(dev, MT_MCU_DEBUG_RESET, MT_MCU_DEBUG_RESET_PSE);

	अगर (!mt76_poll_msec(dev, MT_MCU_DEBUG_RESET,
			    MT_MCU_DEBUG_RESET_PSE_S,
			    MT_MCU_DEBUG_RESET_PSE_S, 500)) अणु
		dev->reset_cause[RESET_CAUSE_RESET_FAILED]++;
		mt76_clear(dev, MT_MCU_DEBUG_RESET, MT_MCU_DEBUG_RESET_PSE);
	पूर्ण अन्यथा अणु
		dev->reset_cause[RESET_CAUSE_RESET_FAILED] = 0;
		mt76_clear(dev, MT_MCU_DEBUG_RESET, MT_MCU_DEBUG_RESET_QUEUES);
	पूर्ण

	अगर (dev->reset_cause[RESET_CAUSE_RESET_FAILED] >= 3)
		dev->reset_cause[RESET_CAUSE_RESET_FAILED] = 0;
पूर्ण

व्योम mt7603_mac_dma_start(काष्ठा mt7603_dev *dev)
अणु
	mt7603_mac_start(dev);

	रुको_क्रम_wpdma(dev);
	usleep_range(50, 100);

	mt76_set(dev, MT_WPDMA_GLO_CFG,
		 (MT_WPDMA_GLO_CFG_TX_DMA_EN |
		  MT_WPDMA_GLO_CFG_RX_DMA_EN |
		  FIELD_PREP(MT_WPDMA_GLO_CFG_DMA_BURST_SIZE, 3) |
		  MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE));

	mt7603_irq_enable(dev, MT_INT_RX_DONE_ALL | MT_INT_TX_DONE_ALL);
पूर्ण

व्योम mt7603_mac_start(काष्ठा mt7603_dev *dev)
अणु
	mt76_clear(dev, MT_ARB_SCR,
		   MT_ARB_SCR_TX_DISABLE | MT_ARB_SCR_RX_DISABLE);
	mt76_wr(dev, MT_WF_ARB_TX_START_0, ~0);
	mt76_set(dev, MT_WF_ARB_RQCR, MT_WF_ARB_RQCR_RX_START);
पूर्ण

व्योम mt7603_mac_stop(काष्ठा mt7603_dev *dev)
अणु
	mt76_set(dev, MT_ARB_SCR,
		 MT_ARB_SCR_TX_DISABLE | MT_ARB_SCR_RX_DISABLE);
	mt76_wr(dev, MT_WF_ARB_TX_START_0, 0);
	mt76_clear(dev, MT_WF_ARB_RQCR, MT_WF_ARB_RQCR_RX_START);
पूर्ण

व्योम mt7603_pse_client_reset(काष्ठा mt7603_dev *dev)
अणु
	u32 addr;

	addr = mt7603_reg_map(dev, MT_CLIENT_BASE_PHYS_ADDR +
				   MT_CLIENT_RESET_TX);

	/* Clear previous reset state */
	mt76_clear(dev, addr,
		   MT_CLIENT_RESET_TX_R_E_1 |
		   MT_CLIENT_RESET_TX_R_E_2 |
		   MT_CLIENT_RESET_TX_R_E_1_S |
		   MT_CLIENT_RESET_TX_R_E_2_S);

	/* Start PSE client TX पात */
	mt76_set(dev, addr, MT_CLIENT_RESET_TX_R_E_1);
	mt76_poll_msec(dev, addr, MT_CLIENT_RESET_TX_R_E_1_S,
		       MT_CLIENT_RESET_TX_R_E_1_S, 500);

	mt76_set(dev, addr, MT_CLIENT_RESET_TX_R_E_2);
	mt76_set(dev, MT_WPDMA_GLO_CFG, MT_WPDMA_GLO_CFG_SW_RESET);

	/* Wait क्रम PSE client to clear TX FIFO */
	mt76_poll_msec(dev, addr, MT_CLIENT_RESET_TX_R_E_2_S,
		       MT_CLIENT_RESET_TX_R_E_2_S, 500);

	/* Clear PSE client TX पात state */
	mt76_clear(dev, addr,
		   MT_CLIENT_RESET_TX_R_E_1 |
		   MT_CLIENT_RESET_TX_R_E_2);
पूर्ण

अटल व्योम mt7603_dma_sched_reset(काष्ठा mt7603_dev *dev)
अणु
	अगर (!is_mt7628(dev))
		वापस;

	mt76_set(dev, MT_SCH_4, MT_SCH_4_RESET);
	mt76_clear(dev, MT_SCH_4, MT_SCH_4_RESET);
पूर्ण

अटल व्योम mt7603_mac_watchकरोg_reset(काष्ठा mt7603_dev *dev)
अणु
	पूर्णांक beacon_पूर्णांक = dev->mt76.beacon_पूर्णांक;
	u32 mask = dev->mt76.mmio.irqmask;
	पूर्णांक i;

	ieee80211_stop_queues(dev->mt76.hw);
	set_bit(MT76_RESET, &dev->mphy.state);

	/* lock/unlock all queues to ensure that no tx is pending */
	mt76_txq_schedule_all(&dev->mphy);

	mt76_worker_disable(&dev->mt76.tx_worker);
	tasklet_disable(&dev->mt76.pre_tbtt_tasklet);
	napi_disable(&dev->mt76.napi[0]);
	napi_disable(&dev->mt76.napi[1]);
	napi_disable(&dev->mt76.tx_napi);

	mutex_lock(&dev->mt76.mutex);

	mt7603_beacon_set_समयr(dev, -1, 0);

	अगर (dev->reset_cause[RESET_CAUSE_RESET_FAILED] ||
	    dev->cur_reset_cause == RESET_CAUSE_RX_PSE_BUSY ||
	    dev->cur_reset_cause == RESET_CAUSE_BEACON_STUCK ||
	    dev->cur_reset_cause == RESET_CAUSE_TX_HANG)
		mt7603_pse_reset(dev);

	अगर (dev->reset_cause[RESET_CAUSE_RESET_FAILED])
		जाओ skip_dma_reset;

	mt7603_mac_stop(dev);

	mt76_clear(dev, MT_WPDMA_GLO_CFG,
		   MT_WPDMA_GLO_CFG_RX_DMA_EN | MT_WPDMA_GLO_CFG_TX_DMA_EN |
		   MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE);
	usleep_range(1000, 2000);

	mt7603_irq_disable(dev, mask);

	mt76_set(dev, MT_WPDMA_GLO_CFG, MT_WPDMA_GLO_CFG_FORCE_TX_खातापूर्ण);

	mt7603_pse_client_reset(dev);

	mt76_queue_tx_cleanup(dev, dev->mt76.q_mcu[MT_MCUQ_WM], true);
	क्रम (i = 0; i < __MT_TXQ_MAX; i++)
		mt76_queue_tx_cleanup(dev, dev->mphy.q_tx[i], true);

	mt76_क्रम_each_q_rx(&dev->mt76, i) अणु
		mt76_queue_rx_reset(dev, i);
	पूर्ण

	mt76_tx_status_check(&dev->mt76, शून्य, true);

	mt7603_dma_sched_reset(dev);

	mt7603_mac_dma_start(dev);

	mt7603_irq_enable(dev, mask);

skip_dma_reset:
	clear_bit(MT76_RESET, &dev->mphy.state);
	mutex_unlock(&dev->mt76.mutex);

	mt76_worker_enable(&dev->mt76.tx_worker);
	napi_enable(&dev->mt76.tx_napi);
	napi_schedule(&dev->mt76.tx_napi);

	tasklet_enable(&dev->mt76.pre_tbtt_tasklet);
	mt7603_beacon_set_समयr(dev, -1, beacon_पूर्णांक);

	napi_enable(&dev->mt76.napi[0]);
	napi_schedule(&dev->mt76.napi[0]);

	napi_enable(&dev->mt76.napi[1]);
	napi_schedule(&dev->mt76.napi[1]);

	ieee80211_wake_queues(dev->mt76.hw);
	mt76_txq_schedule_all(&dev->mphy);
पूर्ण

अटल u32 mt7603_dma_debug(काष्ठा mt7603_dev *dev, u8 index)
अणु
	u32 val;

	mt76_wr(dev, MT_WPDMA_DEBUG,
		FIELD_PREP(MT_WPDMA_DEBUG_IDX, index) |
		MT_WPDMA_DEBUG_SEL);

	val = mt76_rr(dev, MT_WPDMA_DEBUG);
	वापस FIELD_GET(MT_WPDMA_DEBUG_VALUE, val);
पूर्ण

अटल bool mt7603_rx_fअगरo_busy(काष्ठा mt7603_dev *dev)
अणु
	अगर (is_mt7628(dev))
		वापस mt7603_dma_debug(dev, 9) & BIT(9);

	वापस mt7603_dma_debug(dev, 2) & BIT(8);
पूर्ण

अटल bool mt7603_rx_dma_busy(काष्ठा mt7603_dev *dev)
अणु
	अगर (!(mt76_rr(dev, MT_WPDMA_GLO_CFG) & MT_WPDMA_GLO_CFG_RX_DMA_BUSY))
		वापस false;

	वापस mt7603_rx_fअगरo_busy(dev);
पूर्ण

अटल bool mt7603_tx_dma_busy(काष्ठा mt7603_dev *dev)
अणु
	u32 val;

	अगर (!(mt76_rr(dev, MT_WPDMA_GLO_CFG) & MT_WPDMA_GLO_CFG_TX_DMA_BUSY))
		वापस false;

	val = mt7603_dma_debug(dev, 9);
	वापस (val & BIT(8)) && (val & 0xf) != 0xf;
पूर्ण

अटल bool mt7603_tx_hang(काष्ठा mt7603_dev *dev)
अणु
	काष्ठा mt76_queue *q;
	u32 dma_idx, prev_dma_idx;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		q = dev->mphy.q_tx[i];

		अगर (!q->queued)
			जारी;

		prev_dma_idx = dev->tx_dma_idx[i];
		dma_idx = पढ़ोl(&q->regs->dma_idx);
		dev->tx_dma_idx[i] = dma_idx;

		अगर (dma_idx == prev_dma_idx &&
		    dma_idx != पढ़ोl(&q->regs->cpu_idx))
			अवरोध;
	पूर्ण

	वापस i < 4;
पूर्ण

अटल bool mt7603_rx_pse_busy(काष्ठा mt7603_dev *dev)
अणु
	u32 addr, val;

	अगर (mt76_rr(dev, MT_MCU_DEBUG_RESET) & MT_MCU_DEBUG_RESET_QUEUES)
		वापस true;

	अगर (mt7603_rx_fअगरo_busy(dev))
		वापस false;

	addr = mt7603_reg_map(dev, MT_CLIENT_BASE_PHYS_ADDR + MT_CLIENT_STATUS);
	mt76_wr(dev, addr, 3);
	val = mt76_rr(dev, addr) >> 16;

	अगर (is_mt7628(dev) && (val & 0x4001) == 0x4001)
		वापस true;

	वापस (val & 0x8001) == 0x8001 || (val & 0xe001) == 0xe001;
पूर्ण

अटल bool
mt7603_watchकरोg_check(काष्ठा mt7603_dev *dev, u8 *counter,
		      क्रमागत mt7603_reset_cause cause,
		      bool (*check)(काष्ठा mt7603_dev *dev))
अणु
	अगर (dev->reset_test == cause + 1) अणु
		dev->reset_test = 0;
		जाओ trigger;
	पूर्ण

	अगर (check) अणु
		अगर (!check(dev) && *counter < MT7603_WATCHDOG_TIMEOUT) अणु
			*counter = 0;
			वापस false;
		पूर्ण

		(*counter)++;
	पूर्ण

	अगर (*counter < MT7603_WATCHDOG_TIMEOUT)
		वापस false;
trigger:
	dev->cur_reset_cause = cause;
	dev->reset_cause[cause]++;
	वापस true;
पूर्ण

व्योम mt7603_update_channel(काष्ठा mt76_dev *mdev)
अणु
	काष्ठा mt7603_dev *dev = container_of(mdev, काष्ठा mt7603_dev, mt76);
	काष्ठा mt76_channel_state *state;

	state = mdev->phy.chan_state;
	state->cc_busy += mt76_rr(dev, MT_MIB_STAT_CCA);
पूर्ण

व्योम
mt7603_edcca_set_strict(काष्ठा mt7603_dev *dev, bool val)
अणु
	u32 rxtd_6 = 0xd7c80000;

	अगर (val == dev->ed_strict_mode)
		वापस;

	dev->ed_strict_mode = val;

	/* Ensure that ED/CCA करोes not trigger अगर disabled */
	अगर (!dev->ed_monitor)
		rxtd_6 |= FIELD_PREP(MT_RXTD_6_CCAED_TH, 0x34);
	अन्यथा
		rxtd_6 |= FIELD_PREP(MT_RXTD_6_CCAED_TH, 0x7d);

	अगर (dev->ed_monitor && !dev->ed_strict_mode)
		rxtd_6 |= FIELD_PREP(MT_RXTD_6_ACI_TH, 0x0f);
	अन्यथा
		rxtd_6 |= FIELD_PREP(MT_RXTD_6_ACI_TH, 0x10);

	mt76_wr(dev, MT_RXTD(6), rxtd_6);

	mt76_rmw_field(dev, MT_RXTD(13), MT_RXTD_13_ACI_TH_EN,
		       dev->ed_monitor && !dev->ed_strict_mode);
पूर्ण

अटल व्योम
mt7603_edcca_check(काष्ठा mt7603_dev *dev)
अणु
	u32 val = mt76_rr(dev, MT_AGC(41));
	kसमय_प्रकार cur_समय;
	पूर्णांक rssi0, rssi1;
	u32 active;
	u32 ed_busy;

	अगर (!dev->ed_monitor)
		वापस;

	rssi0 = FIELD_GET(MT_AGC_41_RSSI_0, val);
	अगर (rssi0 > 128)
		rssi0 -= 256;

	अगर (dev->mphy.antenna_mask & BIT(1)) अणु
		rssi1 = FIELD_GET(MT_AGC_41_RSSI_1, val);
		अगर (rssi1 > 128)
			rssi1 -= 256;
	पूर्ण अन्यथा अणु
		rssi1 = rssi0;
	पूर्ण

	अगर (max(rssi0, rssi1) >= -40 &&
	    dev->ed_strong_संकेत < MT7603_EDCCA_BLOCK_TH)
		dev->ed_strong_संकेत++;
	अन्यथा अगर (dev->ed_strong_संकेत > 0)
		dev->ed_strong_संकेत--;

	cur_समय = kसमय_get_bootसमय();
	ed_busy = mt76_rr(dev, MT_MIB_STAT_ED) & MT_MIB_STAT_ED_MASK;

	active = kसमय_प्रकारo_us(kसमय_sub(cur_समय, dev->ed_समय));
	dev->ed_समय = cur_समय;

	अगर (!active)
		वापस;

	अगर (100 * ed_busy / active > 90) अणु
		अगर (dev->ed_trigger < 0)
			dev->ed_trigger = 0;
		dev->ed_trigger++;
	पूर्ण अन्यथा अणु
		अगर (dev->ed_trigger > 0)
			dev->ed_trigger = 0;
		dev->ed_trigger--;
	पूर्ण

	अगर (dev->ed_trigger > MT7603_EDCCA_BLOCK_TH ||
	    dev->ed_strong_संकेत < MT7603_EDCCA_BLOCK_TH / 2) अणु
		mt7603_edcca_set_strict(dev, true);
	पूर्ण अन्यथा अगर (dev->ed_trigger < -MT7603_EDCCA_BLOCK_TH) अणु
		mt7603_edcca_set_strict(dev, false);
	पूर्ण

	अगर (dev->ed_trigger > MT7603_EDCCA_BLOCK_TH)
		dev->ed_trigger = MT7603_EDCCA_BLOCK_TH;
	अन्यथा अगर (dev->ed_trigger < -MT7603_EDCCA_BLOCK_TH)
		dev->ed_trigger = -MT7603_EDCCA_BLOCK_TH;
पूर्ण

व्योम mt7603_cca_stats_reset(काष्ठा mt7603_dev *dev)
अणु
	mt76_set(dev, MT_PHYCTRL(2), MT_PHYCTRL_2_STATUS_RESET);
	mt76_clear(dev, MT_PHYCTRL(2), MT_PHYCTRL_2_STATUS_RESET);
	mt76_set(dev, MT_PHYCTRL(2), MT_PHYCTRL_2_STATUS_EN);
पूर्ण

अटल व्योम
mt7603_adjust_sensitivity(काष्ठा mt7603_dev *dev)
अणु
	u32 agc0 = dev->agc0, agc3 = dev->agc3;
	u32 adj;

	अगर (!dev->sensitivity || dev->sensitivity < -100) अणु
		dev->sensitivity = 0;
	पूर्ण अन्यथा अगर (dev->sensitivity <= -84) अणु
		adj = 7 + (dev->sensitivity + 92) / 2;

		agc0 = 0x56f0076f;
		agc0 |= adj << 12;
		agc0 |= adj << 16;
		agc3 = 0x81d0d5e3;
	पूर्ण अन्यथा अगर (dev->sensitivity <= -72) अणु
		adj = 7 + (dev->sensitivity + 80) / 2;

		agc0 = 0x6af0006f;
		agc0 |= adj << 8;
		agc0 |= adj << 12;
		agc0 |= adj << 16;

		agc3 = 0x8181d5e3;
	पूर्ण अन्यथा अणु
		अगर (dev->sensitivity > -54)
			dev->sensitivity = -54;

		adj = 7 + (dev->sensitivity + 80) / 2;

		agc0 = 0x7ff0000f;
		agc0 |= adj << 4;
		agc0 |= adj << 8;
		agc0 |= adj << 12;
		agc0 |= adj << 16;

		agc3 = 0x818181e3;
	पूर्ण

	mt76_wr(dev, MT_AGC(0), agc0);
	mt76_wr(dev, MT_AGC1(0), agc0);

	mt76_wr(dev, MT_AGC(3), agc3);
	mt76_wr(dev, MT_AGC1(3), agc3);
पूर्ण

अटल व्योम
mt7603_false_cca_check(काष्ठा mt7603_dev *dev)
अणु
	पूर्णांक pd_cck, pd_ofdm, mdrdy_cck, mdrdy_ofdm;
	पूर्णांक false_cca;
	पूर्णांक min_संकेत;
	u32 val;

	अगर (!dev->dynamic_sensitivity)
		वापस;

	val = mt76_rr(dev, MT_PHYCTRL_STAT_PD);
	pd_cck = FIELD_GET(MT_PHYCTRL_STAT_PD_CCK, val);
	pd_ofdm = FIELD_GET(MT_PHYCTRL_STAT_PD_OFDM, val);

	val = mt76_rr(dev, MT_PHYCTRL_STAT_MDRDY);
	mdrdy_cck = FIELD_GET(MT_PHYCTRL_STAT_MDRDY_CCK, val);
	mdrdy_ofdm = FIELD_GET(MT_PHYCTRL_STAT_MDRDY_OFDM, val);

	dev->false_cca_ofdm = pd_ofdm - mdrdy_ofdm;
	dev->false_cca_cck = pd_cck - mdrdy_cck;

	mt7603_cca_stats_reset(dev);

	min_संकेत = mt76_get_min_avg_rssi(&dev->mt76, false);
	अगर (!min_संकेत) अणु
		dev->sensitivity = 0;
		dev->last_cca_adj = jअगरfies;
		जाओ out;
	पूर्ण

	min_संकेत -= 15;

	false_cca = dev->false_cca_ofdm + dev->false_cca_cck;
	अगर (false_cca > 600 &&
	    dev->sensitivity < -100 + dev->sensitivity_limit) अणु
		अगर (!dev->sensitivity)
			dev->sensitivity = -92;
		अन्यथा
			dev->sensitivity += 2;
		dev->last_cca_adj = jअगरfies;
	पूर्ण अन्यथा अगर (false_cca < 100 ||
		   समय_after(jअगरfies, dev->last_cca_adj + 10 * HZ)) अणु
		dev->last_cca_adj = jअगरfies;
		अगर (!dev->sensitivity)
			जाओ out;

		dev->sensitivity -= 2;
	पूर्ण

	अगर (dev->sensitivity && dev->sensitivity > min_संकेत) अणु
		dev->sensitivity = min_संकेत;
		dev->last_cca_adj = jअगरfies;
	पूर्ण

out:
	mt7603_adjust_sensitivity(dev);
पूर्ण

व्योम mt7603_mac_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7603_dev *dev = container_of(work, काष्ठा mt7603_dev,
					      mphy.mac_work.work);
	bool reset = false;
	पूर्णांक i, idx;

	mt76_tx_status_check(&dev->mt76, शून्य, false);

	mutex_lock(&dev->mt76.mutex);

	dev->mphy.mac_work_count++;
	mt76_update_survey(&dev->mt76);
	mt7603_edcca_check(dev);

	क्रम (i = 0, idx = 0; i < 2; i++) अणु
		u32 val = mt76_rr(dev, MT_TX_AGG_CNT(i));

		dev->mt76.aggr_stats[idx++] += val & 0xffff;
		dev->mt76.aggr_stats[idx++] += val >> 16;
	पूर्ण

	अगर (dev->mphy.mac_work_count == 10)
		mt7603_false_cca_check(dev);

	अगर (mt7603_watchकरोg_check(dev, &dev->rx_pse_check,
				  RESET_CAUSE_RX_PSE_BUSY,
				  mt7603_rx_pse_busy) ||
	    mt7603_watchकरोg_check(dev, &dev->beacon_check,
				  RESET_CAUSE_BEACON_STUCK,
				  शून्य) ||
	    mt7603_watchकरोg_check(dev, &dev->tx_hang_check,
				  RESET_CAUSE_TX_HANG,
				  mt7603_tx_hang) ||
	    mt7603_watchकरोg_check(dev, &dev->tx_dma_check,
				  RESET_CAUSE_TX_BUSY,
				  mt7603_tx_dma_busy) ||
	    mt7603_watchकरोg_check(dev, &dev->rx_dma_check,
				  RESET_CAUSE_RX_BUSY,
				  mt7603_rx_dma_busy) ||
	    mt7603_watchकरोg_check(dev, &dev->mcu_hang,
				  RESET_CAUSE_MCU_HANG,
				  शून्य) ||
	    dev->reset_cause[RESET_CAUSE_RESET_FAILED]) अणु
		dev->beacon_check = 0;
		dev->tx_dma_check = 0;
		dev->tx_hang_check = 0;
		dev->rx_dma_check = 0;
		dev->rx_pse_check = 0;
		dev->mcu_hang = 0;
		dev->rx_dma_idx = ~0;
		स_रखो(dev->tx_dma_idx, 0xff, माप(dev->tx_dma_idx));
		reset = true;
		dev->mphy.mac_work_count = 0;
	पूर्ण

	अगर (dev->mphy.mac_work_count >= 10)
		dev->mphy.mac_work_count = 0;

	mutex_unlock(&dev->mt76.mutex);

	अगर (reset)
		mt7603_mac_watchकरोg_reset(dev);

	ieee80211_queue_delayed_work(mt76_hw(dev), &dev->mphy.mac_work,
				     msecs_to_jअगरfies(MT7603_WATCHDOG_TIME));
पूर्ण
