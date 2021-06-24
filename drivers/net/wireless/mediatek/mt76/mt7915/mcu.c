<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc. */

#समावेश <linux/firmware.h>
#समावेश <linux/fs.h>
#समावेश "mt7915.h"
#समावेश "mcu.h"
#समावेश "mac.h"
#समावेश "eeprom.h"

काष्ठा mt7915_patch_hdr अणु
	अक्षर build_date[16];
	अक्षर platक्रमm[4];
	__be32 hw_sw_ver;
	__be32 patch_ver;
	__be16 checksum;
	u16 reserved;
	काष्ठा अणु
		__be32 patch_ver;
		__be32 subsys;
		__be32 feature;
		__be32 n_region;
		__be32 crc;
		u32 reserved[11];
	पूर्ण desc;
पूर्ण __packed;

काष्ठा mt7915_patch_sec अणु
	__be32 type;
	__be32 offs;
	__be32 size;
	जोड़ अणु
		__be32 spec[13];
		काष्ठा अणु
			__be32 addr;
			__be32 len;
			__be32 sec_key_idx;
			__be32 align_len;
			u32 reserved[9];
		पूर्ण info;
	पूर्ण;
पूर्ण __packed;

काष्ठा mt7915_fw_trailer अणु
	u8 chip_id;
	u8 eco_code;
	u8 n_region;
	u8 क्रमmat_ver;
	u8 क्रमmat_flag;
	u8 reserved[2];
	अक्षर fw_ver[10];
	अक्षर build_date[15];
	u32 crc;
पूर्ण __packed;

काष्ठा mt7915_fw_region अणु
	__le32 decomp_crc;
	__le32 decomp_len;
	__le32 decomp_blk_sz;
	u8 reserved[4];
	__le32 addr;
	__le32 len;
	u8 feature_set;
	u8 reserved1[15];
पूर्ण __packed;

#घोषणा MCU_PATCH_ADDRESS		0x200000

#घोषणा FW_FEATURE_SET_ENCRYPT		BIT(0)
#घोषणा FW_FEATURE_SET_KEY_IDX		GENMASK(2, 1)
#घोषणा FW_FEATURE_OVERRIDE_ADDR	BIT(5)

#घोषणा DL_MODE_ENCRYPT			BIT(0)
#घोषणा DL_MODE_KEY_IDX			GENMASK(2, 1)
#घोषणा DL_MODE_RESET_SEC_IV		BIT(3)
#घोषणा DL_MODE_WORKING_PDA_CR4		BIT(4)
#घोषणा DL_MODE_NEED_RSP		BIT(31)

#घोषणा FW_START_OVERRIDE		BIT(0)
#घोषणा FW_START_WORKING_PDA_CR4	BIT(2)

#घोषणा PATCH_SEC_TYPE_MASK		GENMASK(15, 0)
#घोषणा PATCH_SEC_TYPE_INFO		0x2

#घोषणा to_wcid_lo(id)			FIELD_GET(GENMASK(7, 0), (u16)id)
#घोषणा to_wcid_hi(id)			FIELD_GET(GENMASK(9, 8), (u16)id)

#घोषणा HE_PHY(p, c)			u8_get_bits(c, IEEE80211_HE_PHY_##p)
#घोषणा HE_MAC(m, c)			u8_get_bits(c, IEEE80211_HE_MAC_##m)

अटल क्रमागत mt7915_cipher_type
mt7915_mcu_get_cipher(पूर्णांक cipher)
अणु
	चयन (cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
		वापस MT_CIPHER_WEP40;
	हाल WLAN_CIPHER_SUITE_WEP104:
		वापस MT_CIPHER_WEP104;
	हाल WLAN_CIPHER_SUITE_TKIP:
		वापस MT_CIPHER_TKIP;
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
		वापस MT_CIPHER_BIP_CMAC_128;
	हाल WLAN_CIPHER_SUITE_CCMP:
		वापस MT_CIPHER_AES_CCMP;
	हाल WLAN_CIPHER_SUITE_CCMP_256:
		वापस MT_CIPHER_CCMP_256;
	हाल WLAN_CIPHER_SUITE_GCMP:
		वापस MT_CIPHER_GCMP;
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		वापस MT_CIPHER_GCMP_256;
	हाल WLAN_CIPHER_SUITE_SMS4:
		वापस MT_CIPHER_WAPI;
	शेष:
		वापस MT_CIPHER_NONE;
	पूर्ण
पूर्ण

अटल u8 mt7915_mcu_chan_bw(काष्ठा cfg80211_chan_def *chandef)
अणु
	अटल स्थिर u8 width_to_bw[] = अणु
		[NL80211_CHAN_WIDTH_40] = CMD_CBW_40MHZ,
		[NL80211_CHAN_WIDTH_80] = CMD_CBW_80MHZ,
		[NL80211_CHAN_WIDTH_80P80] = CMD_CBW_8080MHZ,
		[NL80211_CHAN_WIDTH_160] = CMD_CBW_160MHZ,
		[NL80211_CHAN_WIDTH_5] = CMD_CBW_5MHZ,
		[NL80211_CHAN_WIDTH_10] = CMD_CBW_10MHZ,
		[NL80211_CHAN_WIDTH_20] = CMD_CBW_20MHZ,
		[NL80211_CHAN_WIDTH_20_NOHT] = CMD_CBW_20MHZ,
	पूर्ण;

	अगर (chandef->width >= ARRAY_SIZE(width_to_bw))
		वापस 0;

	वापस width_to_bw[chandef->width];
पूर्ण

अटल स्थिर काष्ठा ieee80211_sta_he_cap *
mt7915_get_he_phy_cap(काष्ठा mt7915_phy *phy, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_supported_band *sband;
	क्रमागत nl80211_band band;

	band = phy->mt76->chandef.chan->band;
	sband = phy->mt76->hw->wiphy->bands[band];

	वापस ieee80211_get_he_अगरtype_cap(sband, vअगर->type);
पूर्ण

अटल u8
mt7915_get_phy_mode(काष्ठा mt76_phy *mphy, काष्ठा ieee80211_vअगर *vअगर,
		    काष्ठा ieee80211_sta *sta)
अणु
	क्रमागत nl80211_band band = mphy->chandef.chan->band;
	काष्ठा ieee80211_sta_ht_cap *ht_cap;
	काष्ठा ieee80211_sta_vht_cap *vht_cap;
	स्थिर काष्ठा ieee80211_sta_he_cap *he_cap;
	u8 mode = 0;

	अगर (sta) अणु
		ht_cap = &sta->ht_cap;
		vht_cap = &sta->vht_cap;
		he_cap = &sta->he_cap;
	पूर्ण अन्यथा अणु
		काष्ठा ieee80211_supported_band *sband;

		sband = mphy->hw->wiphy->bands[band];

		ht_cap = &sband->ht_cap;
		vht_cap = &sband->vht_cap;
		he_cap = ieee80211_get_he_अगरtype_cap(sband, vअगर->type);
	पूर्ण

	अगर (band == NL80211_BAND_2GHZ) अणु
		mode |= PHY_MODE_B | PHY_MODE_G;

		अगर (ht_cap->ht_supported)
			mode |= PHY_MODE_GN;

		अगर (he_cap->has_he)
			mode |= PHY_MODE_AX_24G;
	पूर्ण अन्यथा अगर (band == NL80211_BAND_5GHZ) अणु
		mode |= PHY_MODE_A;

		अगर (ht_cap->ht_supported)
			mode |= PHY_MODE_AN;

		अगर (vht_cap->vht_supported)
			mode |= PHY_MODE_AC;

		अगर (he_cap->has_he)
			mode |= PHY_MODE_AX_5G;
	पूर्ण

	वापस mode;
पूर्ण

अटल u8
mt7915_mcu_get_sta_nss(u16 mcs_map)
अणु
	u8 nss;

	क्रम (nss = 8; nss > 0; nss--) अणु
		u8 nss_mcs = (mcs_map >> (2 * (nss - 1))) & 3;

		अगर (nss_mcs != IEEE80211_VHT_MCS_NOT_SUPPORTED)
			अवरोध;
	पूर्ण

	वापस nss - 1;
पूर्ण

अटल पूर्णांक
mt7915_mcu_parse_response(काष्ठा mt76_dev *mdev, पूर्णांक cmd,
			  काष्ठा sk_buff *skb, पूर्णांक seq)
अणु
	काष्ठा mt7915_mcu_rxd *rxd;
	पूर्णांक ret = 0;

	अगर (!skb) अणु
		dev_err(mdev->dev, "Message %08x (seq %d) timeout\n",
			cmd, seq);
		वापस -ETIMEDOUT;
	पूर्ण

	rxd = (काष्ठा mt7915_mcu_rxd *)skb->data;
	अगर (seq != rxd->seq)
		वापस -EAGAIN;

	अगर (cmd == MCU_CMD(PATCH_SEM_CONTROL)) अणु
		skb_pull(skb, माप(*rxd) - 4);
		ret = *skb->data;
	पूर्ण अन्यथा अगर (cmd == MCU_EXT_CMD(THERMAL_CTRL)) अणु
		skb_pull(skb, माप(*rxd) + 4);
		ret = le32_to_cpu(*(__le32 *)skb->data);
	पूर्ण अन्यथा अणु
		skb_pull(skb, माप(काष्ठा mt7915_mcu_rxd));
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7915_mcu_send_message(काष्ठा mt76_dev *mdev, काष्ठा sk_buff *skb,
			पूर्णांक cmd, पूर्णांक *रुको_seq)
अणु
	काष्ठा mt7915_dev *dev = container_of(mdev, काष्ठा mt7915_dev, mt76);
	काष्ठा mt7915_mcu_txd *mcu_txd;
	क्रमागत mt76_mcuq_id qid;
	__le32 *txd;
	u32 val;
	u8 seq;

	/* TODO: make dynamic based on msg type */
	mdev->mcu.समयout = 20 * HZ;

	seq = ++dev->mt76.mcu.msg_seq & 0xf;
	अगर (!seq)
		seq = ++dev->mt76.mcu.msg_seq & 0xf;

	अगर (cmd == MCU_CMD(FW_SCATTER)) अणु
		qid = MT_MCUQ_FWDL;
		जाओ निकास;
	पूर्ण

	mcu_txd = (काष्ठा mt7915_mcu_txd *)skb_push(skb, माप(*mcu_txd));
	अगर (test_bit(MT76_STATE_MCU_RUNNING, &dev->mphy.state))
		qid = MT_MCUQ_WA;
	अन्यथा
		qid = MT_MCUQ_WM;

	txd = mcu_txd->txd;

	val = FIELD_PREP(MT_TXD0_TX_BYTES, skb->len) |
	      FIELD_PREP(MT_TXD0_PKT_FMT, MT_TX_TYPE_CMD) |
	      FIELD_PREP(MT_TXD0_Q_IDX, MT_TX_MCU_PORT_RX_Q0);
	txd[0] = cpu_to_le32(val);

	val = MT_TXD1_LONG_FORMAT |
	      FIELD_PREP(MT_TXD1_HDR_FORMAT, MT_HDR_FORMAT_CMD);
	txd[1] = cpu_to_le32(val);

	mcu_txd->len = cpu_to_le16(skb->len - माप(mcu_txd->txd));
	mcu_txd->pq_id = cpu_to_le16(MCU_PQ_ID(MT_TX_PORT_IDX_MCU,
					       MT_TX_MCU_PORT_RX_Q0));
	mcu_txd->pkt_type = MCU_PKT_ID;
	mcu_txd->seq = seq;

	mcu_txd->cid = FIELD_GET(__MCU_CMD_FIELD_ID, cmd);
	mcu_txd->set_query = MCU_Q_NA;
	mcu_txd->ext_cid = FIELD_GET(__MCU_CMD_FIELD_EXT_ID, cmd);
	अगर (mcu_txd->ext_cid) अणु
		mcu_txd->ext_cid_ack = 1;

		/* करो not use Q_SET क्रम efuse */
		अगर (cmd & __MCU_CMD_FIELD_QUERY)
			mcu_txd->set_query = MCU_Q_QUERY;
		अन्यथा
			mcu_txd->set_query = MCU_Q_SET;
	पूर्ण

	अगर (cmd & __MCU_CMD_FIELD_WA)
		mcu_txd->s2d_index = MCU_S2D_H2C;
	अन्यथा
		mcu_txd->s2d_index = MCU_S2D_H2N;

निकास:
	अगर (रुको_seq)
		*रुको_seq = seq;

	वापस mt76_tx_queue_skb_raw(dev, mdev->q_mcu[qid], skb, 0);
पूर्ण

अटल व्योम
mt7915_mcu_wa_cmd(काष्ठा mt7915_dev *dev, पूर्णांक cmd, u32 a1, u32 a2, u32 a3)
अणु
	काष्ठा अणु
		__le32 args[3];
	पूर्ण req = अणु
		.args = अणु
			cpu_to_le32(a1),
			cpu_to_le32(a2),
			cpu_to_le32(a3),
		पूर्ण,
	पूर्ण;

	mt76_mcu_send_msg(&dev->mt76, cmd, &req, माप(req), true);
पूर्ण

अटल व्योम
mt7915_mcu_csa_finish(व्योम *priv, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	अगर (vअगर->csa_active)
		ieee80211_csa_finish(vअगर);
पूर्ण

अटल व्योम
mt7915_mcu_rx_csa_notअगरy(काष्ठा mt7915_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt76_phy *mphy = &dev->mt76.phy;
	काष्ठा mt7915_mcu_csa_notअगरy *c;

	c = (काष्ठा mt7915_mcu_csa_notअगरy *)skb->data;

	अगर (c->band_idx && dev->mt76.phy2)
		mphy = dev->mt76.phy2;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(mphy->hw,
			IEEE80211_IFACE_ITER_RESUME_ALL,
			mt7915_mcu_csa_finish, mphy->hw);
पूर्ण

अटल व्योम
mt7915_mcu_rx_radar_detected(काष्ठा mt7915_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt76_phy *mphy = &dev->mt76.phy;
	काष्ठा mt7915_mcu_rdd_report *r;

	r = (काष्ठा mt7915_mcu_rdd_report *)skb->data;

	अगर (r->band_idx && dev->mt76.phy2)
		mphy = dev->mt76.phy2;

	ieee80211_radar_detected(mphy->hw);
	dev->hw_pattern++;
पूर्ण

अटल पूर्णांक
mt7915_mcu_tx_rate_parse(काष्ठा mt76_phy *mphy, काष्ठा mt7915_mcu_ra_info *ra,
			 काष्ठा rate_info *rate, u16 r)
अणु
	काष्ठा ieee80211_supported_band *sband;
	u16 ru_idx = le16_to_cpu(ra->ru_idx);
	bool cck = false;

	rate->mcs = FIELD_GET(MT_RA_RATE_MCS, r);
	rate->nss = FIELD_GET(MT_RA_RATE_NSS, r) + 1;

	चयन (FIELD_GET(MT_RA_RATE_TX_MODE, r)) अणु
	हाल MT_PHY_TYPE_CCK:
		cck = true;
		fallthrough;
	हाल MT_PHY_TYPE_OFDM:
		अगर (mphy->chandef.chan->band == NL80211_BAND_5GHZ)
			sband = &mphy->sband_5g.sband;
		अन्यथा
			sband = &mphy->sband_2g.sband;

		rate->mcs = mt76_get_rate(mphy->dev, sband, rate->mcs, cck);
		rate->legacy = sband->bitrates[rate->mcs].bitrate;
		अवरोध;
	हाल MT_PHY_TYPE_HT:
	हाल MT_PHY_TYPE_HT_GF:
		rate->mcs += (rate->nss - 1) * 8;
		अगर (rate->mcs > 31)
			वापस -EINVAL;

		rate->flags = RATE_INFO_FLAGS_MCS;
		अगर (ra->gi)
			rate->flags |= RATE_INFO_FLAGS_SHORT_GI;
		अवरोध;
	हाल MT_PHY_TYPE_VHT:
		अगर (rate->mcs > 9)
			वापस -EINVAL;

		rate->flags = RATE_INFO_FLAGS_VHT_MCS;
		अगर (ra->gi)
			rate->flags |= RATE_INFO_FLAGS_SHORT_GI;
		अवरोध;
	हाल MT_PHY_TYPE_HE_SU:
	हाल MT_PHY_TYPE_HE_EXT_SU:
	हाल MT_PHY_TYPE_HE_TB:
	हाल MT_PHY_TYPE_HE_MU:
		अगर (ra->gi > NL80211_RATE_INFO_HE_GI_3_2 || rate->mcs > 11)
			वापस -EINVAL;

		rate->he_gi = ra->gi;
		rate->he_dcm = FIELD_GET(MT_RA_RATE_DCM_EN, r);
		rate->flags = RATE_INFO_FLAGS_HE_MCS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (ru_idx) अणु
		चयन (ru_idx) अणु
		हाल 1 ... 2:
			rate->he_ru_alloc = NL80211_RATE_INFO_HE_RU_ALLOC_996;
			अवरोध;
		हाल 3 ... 6:
			rate->he_ru_alloc = NL80211_RATE_INFO_HE_RU_ALLOC_484;
			अवरोध;
		हाल 7 ... 14:
			rate->he_ru_alloc = NL80211_RATE_INFO_HE_RU_ALLOC_242;
			अवरोध;
		शेष:
			rate->he_ru_alloc = NL80211_RATE_INFO_HE_RU_ALLOC_106;
			अवरोध;
		पूर्ण
		rate->bw = RATE_INFO_BW_HE_RU;
	पूर्ण अन्यथा अणु
		u8 bw = mt7915_mcu_chan_bw(&mphy->chandef) -
			FIELD_GET(MT_RA_RATE_BW, r);

		चयन (bw) अणु
		हाल IEEE80211_STA_RX_BW_160:
			rate->bw = RATE_INFO_BW_160;
			अवरोध;
		हाल IEEE80211_STA_RX_BW_80:
			rate->bw = RATE_INFO_BW_80;
			अवरोध;
		हाल IEEE80211_STA_RX_BW_40:
			rate->bw = RATE_INFO_BW_40;
			अवरोध;
		शेष:
			rate->bw = RATE_INFO_BW_20;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
mt7915_mcu_tx_rate_report(काष्ठा mt7915_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7915_mcu_ra_info *ra = (काष्ठा mt7915_mcu_ra_info *)skb->data;
	काष्ठा rate_info rate = अणुपूर्ण, prob_rate = अणुपूर्ण;
	u16 probe = le16_to_cpu(ra->prob_up_rate);
	u16 attempts = le16_to_cpu(ra->attempts);
	u16 curr = le16_to_cpu(ra->curr_rate);
	u16 wcidx = le16_to_cpu(ra->wlan_idx);
	काष्ठा mt76_phy *mphy = &dev->mphy;
	काष्ठा mt7915_sta_stats *stats;
	काष्ठा mt7915_sta *msta;
	काष्ठा mt76_wcid *wcid;

	अगर (wcidx >= MT76_N_WCIDS)
		वापस;

	wcid = rcu_dereference(dev->mt76.wcid[wcidx]);
	अगर (!wcid)
		वापस;

	msta = container_of(wcid, काष्ठा mt7915_sta, wcid);
	stats = &msta->stats;

	अगर (msta->wcid.ext_phy && dev->mt76.phy2)
		mphy = dev->mt76.phy2;

	/* current rate */
	अगर (!mt7915_mcu_tx_rate_parse(mphy, ra, &rate, curr))
		stats->tx_rate = rate;

	/* probing rate */
	अगर (!mt7915_mcu_tx_rate_parse(mphy, ra, &prob_rate, probe))
		stats->prob_rate = prob_rate;

	अगर (attempts) अणु
		u16 success = le16_to_cpu(ra->success);

		stats->per = 1000 * (attempts - success) / attempts;
	पूर्ण
पूर्ण

अटल व्योम
mt7915_mcu_rx_log_message(काष्ठा mt7915_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7915_mcu_rxd *rxd = (काष्ठा mt7915_mcu_rxd *)skb->data;
	स्थिर अक्षर *data = (अक्षर *)&rxd[1];
	स्थिर अक्षर *type;

	चयन (rxd->s2d_index) अणु
	हाल 0:
		type = "WM";
		अवरोध;
	हाल 2:
		type = "WA";
		अवरोध;
	शेष:
		type = "unknown";
		अवरोध;
	पूर्ण

	wiphy_info(mt76_hw(dev)->wiphy, "%s: %.*s", type,
		   (पूर्णांक)(skb->len - माप(*rxd)), data);
पूर्ण

अटल व्योम
mt7915_mcu_rx_ext_event(काष्ठा mt7915_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7915_mcu_rxd *rxd = (काष्ठा mt7915_mcu_rxd *)skb->data;

	चयन (rxd->ext_eid) अणु
	हाल MCU_EXT_EVENT_RDD_REPORT:
		mt7915_mcu_rx_radar_detected(dev, skb);
		अवरोध;
	हाल MCU_EXT_EVENT_CSA_NOTIFY:
		mt7915_mcu_rx_csa_notअगरy(dev, skb);
		अवरोध;
	हाल MCU_EXT_EVENT_RATE_REPORT:
		mt7915_mcu_tx_rate_report(dev, skb);
		अवरोध;
	हाल MCU_EXT_EVENT_FW_LOG_2_HOST:
		mt7915_mcu_rx_log_message(dev, skb);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
mt7915_mcu_rx_unsolicited_event(काष्ठा mt7915_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7915_mcu_rxd *rxd = (काष्ठा mt7915_mcu_rxd *)skb->data;

	चयन (rxd->eid) अणु
	हाल MCU_EVENT_EXT:
		mt7915_mcu_rx_ext_event(dev, skb);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	dev_kमुक्त_skb(skb);
पूर्ण

व्योम mt7915_mcu_rx_event(काष्ठा mt7915_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7915_mcu_rxd *rxd = (काष्ठा mt7915_mcu_rxd *)skb->data;

	अगर (rxd->ext_eid == MCU_EXT_EVENT_THERMAL_PROTECT ||
	    rxd->ext_eid == MCU_EXT_EVENT_FW_LOG_2_HOST ||
	    rxd->ext_eid == MCU_EXT_EVENT_ASSERT_DUMP ||
	    rxd->ext_eid == MCU_EXT_EVENT_PS_SYNC ||
	    rxd->ext_eid == MCU_EXT_EVENT_RATE_REPORT ||
	    !rxd->seq)
		mt7915_mcu_rx_unsolicited_event(dev, skb);
	अन्यथा
		mt76_mcu_rx_event(&dev->mt76, skb);
पूर्ण

अटल काष्ठा sk_buff *
mt7915_mcu_alloc_sta_req(काष्ठा mt7915_dev *dev, काष्ठा mt7915_vअगर *mvअगर,
			 काष्ठा mt7915_sta *msta, पूर्णांक len)
अणु
	काष्ठा sta_req_hdr hdr = अणु
		.bss_idx = mvअगर->idx,
		.wlan_idx_lo = msta ? to_wcid_lo(msta->wcid.idx) : 0,
		.wlan_idx_hi = msta ? to_wcid_hi(msta->wcid.idx) : 0,
		.muar_idx = msta ? mvअगर->omac_idx : 0,
		.is_tlv_append = 1,
	पूर्ण;
	काष्ठा sk_buff *skb;

	skb = mt76_mcu_msg_alloc(&dev->mt76, शून्य, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	skb_put_data(skb, &hdr, माप(hdr));

	वापस skb;
पूर्ण

अटल काष्ठा wtbl_req_hdr *
mt7915_mcu_alloc_wtbl_req(काष्ठा mt7915_dev *dev, काष्ठा mt7915_sta *msta,
			  पूर्णांक cmd, व्योम *sta_wtbl, काष्ठा sk_buff **skb)
अणु
	काष्ठा tlv *sta_hdr = sta_wtbl;
	काष्ठा wtbl_req_hdr hdr = अणु
		.wlan_idx_lo = to_wcid_lo(msta->wcid.idx),
		.wlan_idx_hi = to_wcid_hi(msta->wcid.idx),
		.operation = cmd,
	पूर्ण;
	काष्ठा sk_buff *nskb = *skb;

	अगर (!nskb) अणु
		nskb = mt76_mcu_msg_alloc(&dev->mt76, शून्य,
					  MT7915_WTBL_UPDATE_MAX_SIZE);
		अगर (!nskb)
			वापस ERR_PTR(-ENOMEM);

		*skb = nskb;
	पूर्ण

	अगर (sta_hdr)
		sta_hdr->len = cpu_to_le16(माप(hdr));

	वापस skb_put_data(nskb, &hdr, माप(hdr));
पूर्ण

अटल काष्ठा tlv *
mt7915_mcu_add_nested_tlv(काष्ठा sk_buff *skb, पूर्णांक tag, पूर्णांक len,
			  व्योम *sta_ntlv, व्योम *sta_wtbl)
अणु
	काष्ठा sta_ntlv_hdr *ntlv_hdr = sta_ntlv;
	काष्ठा tlv *sta_hdr = sta_wtbl;
	काष्ठा tlv *ptlv, tlv = अणु
		.tag = cpu_to_le16(tag),
		.len = cpu_to_le16(len),
	पूर्ण;
	u16 ntlv;

	ptlv = skb_put(skb, len);
	स_नकल(ptlv, &tlv, माप(tlv));

	ntlv = le16_to_cpu(ntlv_hdr->tlv_num);
	ntlv_hdr->tlv_num = cpu_to_le16(ntlv + 1);

	अगर (sta_hdr) अणु
		u16 size = le16_to_cpu(sta_hdr->len);

		sta_hdr->len = cpu_to_le16(size + len);
	पूर्ण

	वापस ptlv;
पूर्ण

अटल काष्ठा tlv *
mt7915_mcu_add_tlv(काष्ठा sk_buff *skb, पूर्णांक tag, पूर्णांक len)
अणु
	वापस mt7915_mcu_add_nested_tlv(skb, tag, len, skb->data, शून्य);
पूर्ण

अटल काष्ठा tlv *
mt7915_mcu_add_nested_subtlv(काष्ठा sk_buff *skb, पूर्णांक sub_tag, पूर्णांक sub_len,
			     __le16 *sub_ntlv, __le16 *len)
अणु
	काष्ठा tlv *ptlv, tlv = अणु
		.tag = cpu_to_le16(sub_tag),
		.len = cpu_to_le16(sub_len),
	पूर्ण;

	ptlv = skb_put(skb, sub_len);
	स_नकल(ptlv, &tlv, माप(tlv));

	le16_add_cpu(sub_ntlv, 1);
	le16_add_cpu(len, sub_len);

	वापस ptlv;
पूर्ण

/** bss info **/
अटल पूर्णांक
mt7915_mcu_bss_basic_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा mt7915_phy *phy, bool enable)
अणु
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	काष्ठा bss_info_basic *bss;
	u16 wlan_idx = mvअगर->sta.wcid.idx;
	u32 type = NETWORK_INFRA;
	काष्ठा tlv *tlv;

	tlv = mt7915_mcu_add_tlv(skb, BSS_INFO_BASIC, माप(*bss));

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_MONITOR:
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		/* TODO: enable BSS_INFO_UAPSD & BSS_INFO_PM */
		अगर (enable) अणु
			काष्ठा ieee80211_sta *sta;
			काष्ठा mt7915_sta *msta;

			rcu_पढ़ो_lock();
			sta = ieee80211_find_sta(vअगर, vअगर->bss_conf.bssid);
			अगर (!sta) अणु
				rcu_पढ़ो_unlock();
				वापस -EINVAL;
			पूर्ण

			msta = (काष्ठा mt7915_sta *)sta->drv_priv;
			wlan_idx = msta->wcid.idx;
			rcu_पढ़ो_unlock();
		पूर्ण
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		type = NETWORK_IBSS;
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	bss = (काष्ठा bss_info_basic *)tlv;
	bss->network_type = cpu_to_le32(type);
	bss->bmc_wcid_lo = to_wcid_lo(wlan_idx);
	bss->bmc_wcid_hi = to_wcid_hi(wlan_idx);
	bss->wmm_idx = mvअगर->wmm_idx;
	bss->active = enable;

	अगर (vअगर->type != NL80211_IFTYPE_MONITOR) अणु
		स_नकल(bss->bssid, vअगर->bss_conf.bssid, ETH_ALEN);
		bss->bcn_पूर्णांकerval = cpu_to_le16(vअगर->bss_conf.beacon_पूर्णांक);
		bss->dtim_period = vअगर->bss_conf.dtim_period;
		bss->phy_mode = mt7915_get_phy_mode(phy->mt76, vअगर, शून्य);
	पूर्ण अन्यथा अणु
		स_नकल(bss->bssid, phy->mt76->macaddr, ETH_ALEN);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
mt7915_mcu_bss_omac_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	काष्ठा bss_info_omac *omac;
	काष्ठा tlv *tlv;
	u32 type = 0;
	u8 idx;

	tlv = mt7915_mcu_add_tlv(skb, BSS_INFO_OMAC, माप(*omac));

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_MONITOR:
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_AP:
		type = CONNECTION_INFRA_AP;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		type = CONNECTION_INFRA_STA;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		type = CONNECTION_IBSS_ADHOC;
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	omac = (काष्ठा bss_info_omac *)tlv;
	idx = mvअगर->omac_idx > EXT_BSSID_START ? HW_BSSID_0 : mvअगर->omac_idx;
	omac->conn_type = cpu_to_le32(type);
	omac->omac_idx = mvअगर->omac_idx;
	omac->band_idx = mvअगर->band_idx;
	omac->hw_bss_idx = idx;
पूर्ण

काष्ठा mt7915_he_obss_narrow_bw_ru_data अणु
	bool tolerated;
पूर्ण;

अटल व्योम mt7915_check_he_obss_narrow_bw_ru_iter(काष्ठा wiphy *wiphy,
						   काष्ठा cfg80211_bss *bss,
						   व्योम *_data)
अणु
	काष्ठा mt7915_he_obss_narrow_bw_ru_data *data = _data;
	स्थिर काष्ठा element *elem;

	elem = ieee80211_bss_get_elem(bss, WLAN_EID_EXT_CAPABILITY);

	अगर (!elem || elem->datalen < 10 ||
	    !(elem->data[10] &
	      WLAN_EXT_CAPA10_OBSS_NARROW_BW_RU_TOLERANCE_SUPPORT))
		data->tolerated = false;
पूर्ण

अटल bool mt7915_check_he_obss_narrow_bw_ru(काष्ठा ieee80211_hw *hw,
					      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7915_he_obss_narrow_bw_ru_data iter_data = अणु
		.tolerated = true,
	पूर्ण;

	अगर (!(vअगर->bss_conf.chandef.chan->flags & IEEE80211_CHAN_RADAR))
		वापस false;

	cfg80211_bss_iter(hw->wiphy, &vअगर->bss_conf.chandef,
			  mt7915_check_he_obss_narrow_bw_ru_iter,
			  &iter_data);

	/*
	 * If there is at least one AP on radar channel that cannot
	 * tolerate 26-tone RU UL OFDMA transmissions using HE TB PPDU.
	 */
	वापस !iter_data.tolerated;
पूर्ण

अटल व्योम
mt7915_mcu_bss_rfch_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा mt7915_phy *phy)
अणु
	काष्ठा cfg80211_chan_def *chandef = &phy->mt76->chandef;
	काष्ठा bss_info_rf_ch *ch;
	काष्ठा tlv *tlv;
	पूर्णांक freq1 = chandef->center_freq1;

	tlv = mt7915_mcu_add_tlv(skb, BSS_INFO_RF_CH, माप(*ch));

	ch = (काष्ठा bss_info_rf_ch *)tlv;
	ch->pri_ch = chandef->chan->hw_value;
	ch->center_ch0 = ieee80211_frequency_to_channel(freq1);
	ch->bw = mt7915_mcu_chan_bw(chandef);

	अगर (chandef->width == NL80211_CHAN_WIDTH_80P80) अणु
		पूर्णांक freq2 = chandef->center_freq2;

		ch->center_ch1 = ieee80211_frequency_to_channel(freq2);
	पूर्ण

	अगर (vअगर->bss_conf.he_support && vअगर->type == NL80211_IFTYPE_STATION) अणु
		काष्ठा mt7915_dev *dev = phy->dev;
		काष्ठा mt76_phy *mphy = &dev->mt76.phy;
		bool ext_phy = phy != &dev->phy;

		अगर (ext_phy && dev->mt76.phy2)
			mphy = dev->mt76.phy2;

		ch->he_ru26_block =
			mt7915_check_he_obss_narrow_bw_ru(mphy->hw, vअगर);
		ch->he_all_disable = false;
	पूर्ण अन्यथा अणु
		ch->he_all_disable = true;
	पूर्ण
पूर्ण

अटल व्योम
mt7915_mcu_bss_ra_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_vअगर *vअगर,
		      काष्ठा mt7915_phy *phy)
अणु
	पूर्णांक max_nss = hweight8(phy->mt76->chainmask);
	काष्ठा bss_info_ra *ra;
	काष्ठा tlv *tlv;

	tlv = mt7915_mcu_add_tlv(skb, BSS_INFO_RA, माप(*ra));

	ra = (काष्ठा bss_info_ra *)tlv;
	ra->op_mode = vअगर->type == NL80211_IFTYPE_AP;
	ra->adhoc_en = vअगर->type == NL80211_IFTYPE_ADHOC;
	ra->लघु_preamble = true;
	ra->tx_streams = max_nss;
	ra->rx_streams = max_nss;
	ra->algo = 4;
	ra->train_up_rule = 2;
	ra->train_up_high_thres = 110;
	ra->train_up_rule_rssi = -70;
	ra->low_traffic_thres = 2;
	ra->phy_cap = cpu_to_le32(0xfdf);
	ra->पूर्णांकerval = cpu_to_le32(500);
	ra->fast_पूर्णांकerval = cpu_to_le32(100);
पूर्ण

अटल व्योम
mt7915_mcu_bss_he_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_vअगर *vअगर,
		      काष्ठा mt7915_phy *phy)
अणु
#घोषणा DEFAULT_HE_PE_DURATION		4
#घोषणा DEFAULT_HE_DURATION_RTS_THRES	1023
	स्थिर काष्ठा ieee80211_sta_he_cap *cap;
	काष्ठा bss_info_he *he;
	काष्ठा tlv *tlv;

	cap = mt7915_get_he_phy_cap(phy, vअगर);

	tlv = mt7915_mcu_add_tlv(skb, BSS_INFO_HE_BASIC, माप(*he));

	he = (काष्ठा bss_info_he *)tlv;
	he->he_pe_duration = vअगर->bss_conf.htc_trig_based_pkt_ext;
	अगर (!he->he_pe_duration)
		he->he_pe_duration = DEFAULT_HE_PE_DURATION;

	he->he_rts_thres = cpu_to_le16(vअगर->bss_conf.frame_समय_rts_th);
	अगर (!he->he_rts_thres)
		he->he_rts_thres = cpu_to_le16(DEFAULT_HE_DURATION_RTS_THRES);

	he->max_nss_mcs[CMD_HE_MCS_BW80] = cap->he_mcs_nss_supp.tx_mcs_80;
	he->max_nss_mcs[CMD_HE_MCS_BW160] = cap->he_mcs_nss_supp.tx_mcs_160;
	he->max_nss_mcs[CMD_HE_MCS_BW8080] = cap->he_mcs_nss_supp.tx_mcs_80p80;
पूर्ण

अटल व्योम
mt7915_mcu_bss_hw_amsdu_tlv(काष्ठा sk_buff *skb)
अणु
#घोषणा TXD_CMP_MAP1		GENMASK(15, 0)
#घोषणा TXD_CMP_MAP2		(GENMASK(31, 0) & ~BIT(23))
	काष्ठा bss_info_hw_amsdu *amsdu;
	काष्ठा tlv *tlv;

	tlv = mt7915_mcu_add_tlv(skb, BSS_INFO_HW_AMSDU, माप(*amsdu));

	amsdu = (काष्ठा bss_info_hw_amsdu *)tlv;
	amsdu->cmp_biपंचांगap_0 = cpu_to_le32(TXD_CMP_MAP1);
	amsdu->cmp_biपंचांगap_1 = cpu_to_le32(TXD_CMP_MAP2);
	amsdu->trig_thres = cpu_to_le16(2);
	amsdu->enable = true;
पूर्ण

अटल व्योम
mt7915_mcu_bss_ext_tlv(काष्ठा sk_buff *skb, काष्ठा mt7915_vअगर *mvअगर)
अणु
/* SIFS 20us + 512 byte beacon tranmitted by 1Mbps (3906us) */
#घोषणा BCN_TX_ESTIMATE_TIME	(4096 + 20)
	काष्ठा bss_info_ext_bss *ext;
	पूर्णांक ext_bss_idx, tsf_offset;
	काष्ठा tlv *tlv;

	ext_bss_idx = mvअगर->omac_idx - EXT_BSSID_START;
	अगर (ext_bss_idx < 0)
		वापस;

	tlv = mt7915_mcu_add_tlv(skb, BSS_INFO_EXT_BSS, माप(*ext));

	ext = (काष्ठा bss_info_ext_bss *)tlv;
	tsf_offset = ext_bss_idx * BCN_TX_ESTIMATE_TIME;
	ext->mbss_tsf_offset = cpu_to_le32(tsf_offset);
पूर्ण

अटल व्योम
mt7915_mcu_bss_bmc_tlv(काष्ठा sk_buff *skb, काष्ठा mt7915_phy *phy)
अणु
	काष्ठा bss_info_bmc_rate *bmc;
	काष्ठा cfg80211_chan_def *chandef = &phy->mt76->chandef;
	क्रमागत nl80211_band band = chandef->chan->band;
	काष्ठा tlv *tlv;

	tlv = mt7915_mcu_add_tlv(skb, BSS_INFO_BMC_RATE, माप(*bmc));

	bmc = (काष्ठा bss_info_bmc_rate *)tlv;
	अगर (band == NL80211_BAND_2GHZ) अणु
		bmc->लघु_preamble = true;
	पूर्ण अन्यथा अणु
		bmc->bc_trans = cpu_to_le16(0x2000);
		bmc->mc_trans = cpu_to_le16(0x2080);
	पूर्ण
पूर्ण

अटल पूर्णांक
mt7915_mcu_muar_config(काष्ठा mt7915_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
		       bool bssid, bool enable)
अणु
	काष्ठा mt7915_dev *dev = phy->dev;
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	u32 idx = mvअगर->omac_idx - REPEATER_BSSID_START;
	u32 mask = phy->omac_mask >> 32 & ~BIT(idx);
	स्थिर u8 *addr = vअगर->addr;
	काष्ठा अणु
		u8 mode;
		u8 क्रमce_clear;
		u8 clear_biपंचांगap[8];
		u8 entry_count;
		u8 ग_लिखो;
		u8 band;

		u8 index;
		u8 bssid;
		u8 addr[ETH_ALEN];
	पूर्ण __packed req = अणु
		.mode = !!mask || enable,
		.entry_count = 1,
		.ग_लिखो = 1,
		.band = phy != &dev->phy,
		.index = idx * 2 + bssid,
	पूर्ण;

	अगर (bssid)
		addr = vअगर->bss_conf.bssid;

	अगर (enable)
		ether_addr_copy(req.addr, addr);

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(MUAR_UPDATE), &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7915_mcu_add_bss_info(काष्ठा mt7915_phy *phy,
			    काष्ठा ieee80211_vअगर *vअगर, पूर्णांक enable)
अणु
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	काष्ठा sk_buff *skb;

	अगर (mvअगर->omac_idx >= REPEATER_BSSID_START) अणु
		mt7915_mcu_muar_config(phy, vअगर, false, enable);
		mt7915_mcu_muar_config(phy, vअगर, true, enable);
	पूर्ण

	skb = mt7915_mcu_alloc_sta_req(phy->dev, mvअगर, शून्य,
				       MT7915_BSS_UPDATE_MAX_SIZE);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	/* bss_omac must be first */
	अगर (enable)
		mt7915_mcu_bss_omac_tlv(skb, vअगर);

	mt7915_mcu_bss_basic_tlv(skb, vअगर, phy, enable);

	अगर (vअगर->type == NL80211_IFTYPE_MONITOR)
		जाओ out;

	अगर (enable) अणु
		mt7915_mcu_bss_rfch_tlv(skb, vअगर, phy);
		mt7915_mcu_bss_bmc_tlv(skb, phy);
		mt7915_mcu_bss_ra_tlv(skb, vअगर, phy);
		mt7915_mcu_bss_hw_amsdu_tlv(skb);

		अगर (vअगर->bss_conf.he_support)
			mt7915_mcu_bss_he_tlv(skb, vअगर, phy);

		अगर (mvअगर->omac_idx >= EXT_BSSID_START &&
		    mvअगर->omac_idx < REPEATER_BSSID_START)
			mt7915_mcu_bss_ext_tlv(skb, mvअगर);
	पूर्ण
out:
	वापस mt76_mcu_skb_send_msg(&phy->dev->mt76, skb,
				     MCU_EXT_CMD(BSS_INFO_UPDATE), true);
पूर्ण

/** starec & wtbl **/
अटल पूर्णांक
mt7915_mcu_sta_key_tlv(काष्ठा mt7915_sta *msta, काष्ठा sk_buff *skb,
		       काष्ठा ieee80211_key_conf *key, क्रमागत set_key_cmd cmd)
अणु
	काष्ठा mt7915_sta_key_conf *bip = &msta->bip;
	काष्ठा sta_rec_sec *sec;
	काष्ठा tlv *tlv;
	u32 len = माप(*sec);

	tlv = mt7915_mcu_add_tlv(skb, STA_REC_KEY_V2, माप(*sec));

	sec = (काष्ठा sta_rec_sec *)tlv;
	sec->add = cmd;

	अगर (cmd == SET_KEY) अणु
		काष्ठा sec_key *sec_key;
		u8 cipher;

		cipher = mt7915_mcu_get_cipher(key->cipher);
		अगर (cipher == MT_CIPHER_NONE)
			वापस -EOPNOTSUPP;

		sec_key = &sec->key[0];
		sec_key->cipher_len = माप(*sec_key);

		अगर (cipher == MT_CIPHER_BIP_CMAC_128) अणु
			sec_key->cipher_id = MT_CIPHER_AES_CCMP;
			sec_key->key_id = bip->keyidx;
			sec_key->key_len = 16;
			स_नकल(sec_key->key, bip->key, 16);

			sec_key = &sec->key[1];
			sec_key->cipher_id = MT_CIPHER_BIP_CMAC_128;
			sec_key->cipher_len = माप(*sec_key);
			sec_key->key_len = 16;
			स_नकल(sec_key->key, key->key, 16);

			sec->n_cipher = 2;
		पूर्ण अन्यथा अणु
			sec_key->cipher_id = cipher;
			sec_key->key_id = key->keyidx;
			sec_key->key_len = key->keylen;
			स_नकल(sec_key->key, key->key, key->keylen);

			अगर (cipher == MT_CIPHER_TKIP) अणु
				/* Rx/Tx MIC keys are swapped */
				स_नकल(sec_key->key + 16, key->key + 24, 8);
				स_नकल(sec_key->key + 24, key->key + 16, 8);
			पूर्ण

			/* store key_conf क्रम BIP batch update */
			अगर (cipher == MT_CIPHER_AES_CCMP) अणु
				स_नकल(bip->key, key->key, key->keylen);
				bip->keyidx = key->keyidx;
			पूर्ण

			len -= माप(*sec_key);
			sec->n_cipher = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		len -= माप(sec->key);
		sec->n_cipher = 0;
	पूर्ण
	sec->len = cpu_to_le16(len);

	वापस 0;
पूर्ण

पूर्णांक mt7915_mcu_add_key(काष्ठा mt7915_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा mt7915_sta *msta, काष्ठा ieee80211_key_conf *key,
		       क्रमागत set_key_cmd cmd)
अणु
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	काष्ठा sk_buff *skb;
	पूर्णांक len = माप(काष्ठा sta_req_hdr) + माप(काष्ठा sta_rec_sec);
	पूर्णांक ret;

	skb = mt7915_mcu_alloc_sta_req(dev, mvअगर, msta, len);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	ret = mt7915_mcu_sta_key_tlv(msta, skb, key, cmd);
	अगर (ret)
		वापस ret;

	वापस mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_EXT_CMD(STA_REC_UPDATE), true);
पूर्ण

अटल व्योम
mt7915_mcu_sta_ba_tlv(काष्ठा sk_buff *skb,
		      काष्ठा ieee80211_ampdu_params *params,
		      bool enable, bool tx)
अणु
	काष्ठा sta_rec_ba *ba;
	काष्ठा tlv *tlv;

	tlv = mt7915_mcu_add_tlv(skb, STA_REC_BA, माप(*ba));

	ba = (काष्ठा sta_rec_ba *)tlv;
	ba->ba_type = tx ? MT_BA_TYPE_ORIGINATOR : MT_BA_TYPE_RECIPIENT;
	ba->winsize = cpu_to_le16(params->buf_size);
	ba->ssn = cpu_to_le16(params->ssn);
	ba->ba_en = enable << params->tid;
	ba->amsdu = params->amsdu;
	ba->tid = params->tid;
पूर्ण

अटल व्योम
mt7915_mcu_wtbl_ba_tlv(काष्ठा sk_buff *skb,
		       काष्ठा ieee80211_ampdu_params *params,
		       bool enable, bool tx, व्योम *sta_wtbl,
		       व्योम *wtbl_tlv)
अणु
	काष्ठा wtbl_ba *ba;
	काष्ठा tlv *tlv;

	tlv = mt7915_mcu_add_nested_tlv(skb, WTBL_BA, माप(*ba),
					wtbl_tlv, sta_wtbl);

	ba = (काष्ठा wtbl_ba *)tlv;
	ba->tid = params->tid;

	अगर (tx) अणु
		ba->ba_type = MT_BA_TYPE_ORIGINATOR;
		ba->sn = enable ? cpu_to_le16(params->ssn) : 0;
		ba->ba_en = enable;
	पूर्ण अन्यथा अणु
		स_नकल(ba->peer_addr, params->sta->addr, ETH_ALEN);
		ba->ba_type = MT_BA_TYPE_RECIPIENT;
		ba->rst_ba_tid = params->tid;
		ba->rst_ba_sel = RST_BA_MAC_TID_MATCH;
		ba->rst_ba_sb = 1;
	पूर्ण

	अगर (enable && tx)
		ba->ba_winsize = cpu_to_le16(params->buf_size);
पूर्ण

अटल पूर्णांक
mt7915_mcu_sta_ba(काष्ठा mt7915_dev *dev,
		  काष्ठा ieee80211_ampdu_params *params,
		  bool enable, bool tx)
अणु
	काष्ठा mt7915_sta *msta = (काष्ठा mt7915_sta *)params->sta->drv_priv;
	काष्ठा mt7915_vअगर *mvअगर = msta->vअगर;
	काष्ठा wtbl_req_hdr *wtbl_hdr;
	काष्ठा tlv *sta_wtbl;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	अगर (enable && tx && !params->amsdu)
		msta->wcid.amsdu = false;

	skb = mt7915_mcu_alloc_sta_req(dev, mvअगर, msta,
				       MT7915_STA_UPDATE_MAX_SIZE);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	sta_wtbl = mt7915_mcu_add_tlv(skb, STA_REC_WTBL, माप(काष्ठा tlv));

	wtbl_hdr = mt7915_mcu_alloc_wtbl_req(dev, msta, WTBL_SET, sta_wtbl,
					     &skb);
	अगर (IS_ERR(wtbl_hdr))
		वापस PTR_ERR(wtbl_hdr);

	mt7915_mcu_wtbl_ba_tlv(skb, params, enable, tx, sta_wtbl, wtbl_hdr);

	ret = mt76_mcu_skb_send_msg(&dev->mt76, skb,
				    MCU_EXT_CMD(STA_REC_UPDATE), true);
	अगर (ret)
		वापस ret;

	skb = mt7915_mcu_alloc_sta_req(dev, mvअगर, msta,
				       MT7915_STA_UPDATE_MAX_SIZE);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	mt7915_mcu_sta_ba_tlv(skb, params, enable, tx);

	वापस mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_EXT_CMD(STA_REC_UPDATE), true);
पूर्ण

पूर्णांक mt7915_mcu_add_tx_ba(काष्ठा mt7915_dev *dev,
			 काष्ठा ieee80211_ampdu_params *params,
			 bool enable)
अणु
	वापस mt7915_mcu_sta_ba(dev, params, enable, true);
पूर्ण

पूर्णांक mt7915_mcu_add_rx_ba(काष्ठा mt7915_dev *dev,
			 काष्ठा ieee80211_ampdu_params *params,
			 bool enable)
अणु
	वापस mt7915_mcu_sta_ba(dev, params, enable, false);
पूर्ण

अटल व्योम
mt7915_mcu_wtbl_generic_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta, व्योम *sta_wtbl,
			    व्योम *wtbl_tlv)
अणु
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	काष्ठा wtbl_generic *generic;
	काष्ठा wtbl_rx *rx;
	काष्ठा tlv *tlv;

	tlv = mt7915_mcu_add_nested_tlv(skb, WTBL_GENERIC, माप(*generic),
					wtbl_tlv, sta_wtbl);

	generic = (काष्ठा wtbl_generic *)tlv;

	अगर (sta) अणु
		स_नकल(generic->peer_addr, sta->addr, ETH_ALEN);
		generic->partial_aid = cpu_to_le16(sta->aid);
		generic->muar_idx = mvअगर->omac_idx;
		generic->qos = sta->wme;
	पूर्ण अन्यथा अणु
		/* use BSSID in station mode */
		अगर (vअगर->type == NL80211_IFTYPE_STATION)
			स_नकल(generic->peer_addr, vअगर->bss_conf.bssid,
			       ETH_ALEN);
		अन्यथा
			eth_broadcast_addr(generic->peer_addr);

		generic->muar_idx = 0xe;
	पूर्ण

	tlv = mt7915_mcu_add_nested_tlv(skb, WTBL_RX, माप(*rx),
					wtbl_tlv, sta_wtbl);

	rx = (काष्ठा wtbl_rx *)tlv;
	rx->rca1 = sta ? vअगर->type != NL80211_IFTYPE_AP : 1;
	rx->rca2 = 1;
	rx->rv = 1;
पूर्ण

अटल व्योम
mt7915_mcu_sta_basic_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा ieee80211_sta *sta, bool enable)
अणु
#घोषणा EXTRA_INFO_VER          BIT(0)
#घोषणा EXTRA_INFO_NEW          BIT(1)
	काष्ठा sta_rec_basic *basic;
	काष्ठा tlv *tlv;

	tlv = mt7915_mcu_add_tlv(skb, STA_REC_BASIC, माप(*basic));

	basic = (काष्ठा sta_rec_basic *)tlv;
	basic->extra_info = cpu_to_le16(EXTRA_INFO_VER);

	अगर (enable) अणु
		basic->extra_info |= cpu_to_le16(EXTRA_INFO_NEW);
		basic->conn_state = CONN_STATE_PORT_SECURE;
	पूर्ण अन्यथा अणु
		basic->conn_state = CONN_STATE_DISCONNECT;
	पूर्ण

	अगर (!sta) अणु
		basic->conn_type = cpu_to_le32(CONNECTION_INFRA_BC);
		eth_broadcast_addr(basic->peer_addr);
		वापस;
	पूर्ण

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_AP:
		basic->conn_type = cpu_to_le32(CONNECTION_INFRA_STA);
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		basic->conn_type = cpu_to_le32(CONNECTION_INFRA_AP);
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		basic->conn_type = cpu_to_le32(CONNECTION_IBSS_ADHOC);
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	स_नकल(basic->peer_addr, sta->addr, ETH_ALEN);
	basic->aid = cpu_to_le16(sta->aid);
	basic->qos = sta->wme;
पूर्ण

अटल व्योम
mt7915_mcu_sta_he_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ieee80211_sta_he_cap *he_cap = &sta->he_cap;
	काष्ठा ieee80211_he_cap_elem *elem = &he_cap->he_cap_elem;
	काष्ठा sta_rec_he *he;
	काष्ठा tlv *tlv;
	u32 cap = 0;

	tlv = mt7915_mcu_add_tlv(skb, STA_REC_HE, माप(*he));

	he = (काष्ठा sta_rec_he *)tlv;

	अगर (elem->mac_cap_info[0] & IEEE80211_HE_MAC_CAP0_HTC_HE)
		cap |= STA_REC_HE_CAP_HTC;

	अगर (elem->mac_cap_info[2] & IEEE80211_HE_MAC_CAP2_BSR)
		cap |= STA_REC_HE_CAP_BSR;

	अगर (elem->mac_cap_info[3] & IEEE80211_HE_MAC_CAP3_OMI_CONTROL)
		cap |= STA_REC_HE_CAP_OM;

	अगर (elem->mac_cap_info[4] & IEEE80211_HE_MAC_CAP4_AMSDU_IN_AMPDU)
		cap |= STA_REC_HE_CAP_AMSDU_IN_AMPDU;

	अगर (elem->mac_cap_info[4] & IEEE80211_HE_MAC_CAP4_BQR)
		cap |= STA_REC_HE_CAP_BQR;

	अगर (elem->phy_cap_info[0] &
	    (IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_RU_MAPPING_IN_2G |
	     IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_RU_MAPPING_IN_5G))
		cap |= STA_REC_HE_CAP_BW20_RU242_SUPPORT;

	अगर (elem->phy_cap_info[1] &
	    IEEE80211_HE_PHY_CAP1_LDPC_CODING_IN_PAYLOAD)
		cap |= STA_REC_HE_CAP_LDPC;

	अगर (elem->phy_cap_info[1] &
	    IEEE80211_HE_PHY_CAP1_HE_LTF_AND_GI_FOR_HE_PPDUS_0_8US)
		cap |= STA_REC_HE_CAP_SU_PPDU_1LTF_8US_GI;

	अगर (elem->phy_cap_info[2] &
	    IEEE80211_HE_PHY_CAP2_NDP_4x_LTF_AND_3_2US)
		cap |= STA_REC_HE_CAP_NDP_4LTF_3DOT2MS_GI;

	अगर (elem->phy_cap_info[2] &
	    IEEE80211_HE_PHY_CAP2_STBC_TX_UNDER_80MHZ)
		cap |= STA_REC_HE_CAP_LE_EQ_80M_TX_STBC;

	अगर (elem->phy_cap_info[2] &
	    IEEE80211_HE_PHY_CAP2_STBC_RX_UNDER_80MHZ)
		cap |= STA_REC_HE_CAP_LE_EQ_80M_RX_STBC;

	अगर (elem->phy_cap_info[6] &
	    IEEE80211_HE_PHY_CAP6_PARTIAL_BW_EXT_RANGE)
		cap |= STA_REC_HE_CAP_PARTIAL_BW_EXT_RANGE;

	अगर (elem->phy_cap_info[7] &
	    IEEE80211_HE_PHY_CAP7_HE_SU_MU_PPDU_4XLTF_AND_08_US_GI)
		cap |= STA_REC_HE_CAP_SU_MU_PPDU_4LTF_8US_GI;

	अगर (elem->phy_cap_info[7] &
	    IEEE80211_HE_PHY_CAP7_STBC_TX_ABOVE_80MHZ)
		cap |= STA_REC_HE_CAP_GT_80M_TX_STBC;

	अगर (elem->phy_cap_info[7] &
	    IEEE80211_HE_PHY_CAP7_STBC_RX_ABOVE_80MHZ)
		cap |= STA_REC_HE_CAP_GT_80M_RX_STBC;

	अगर (elem->phy_cap_info[8] &
	    IEEE80211_HE_PHY_CAP8_HE_ER_SU_PPDU_4XLTF_AND_08_US_GI)
		cap |= STA_REC_HE_CAP_ER_SU_PPDU_4LTF_8US_GI;

	अगर (elem->phy_cap_info[8] &
	    IEEE80211_HE_PHY_CAP8_HE_ER_SU_1XLTF_AND_08_US_GI)
		cap |= STA_REC_HE_CAP_ER_SU_PPDU_1LTF_8US_GI;

	अगर (elem->phy_cap_info[9] &
	    IEEE80211_HE_PHY_CAP9_NON_TRIGGERED_CQI_FEEDBACK)
		cap |= STA_REC_HE_CAP_TRIG_CQI_FK;

	अगर (elem->phy_cap_info[9] &
	    IEEE80211_HE_PHY_CAP9_TX_1024_QAM_LESS_THAN_242_TONE_RU)
		cap |= STA_REC_HE_CAP_TX_1024QAM_UNDER_RU242;

	अगर (elem->phy_cap_info[9] &
	    IEEE80211_HE_PHY_CAP9_RX_1024_QAM_LESS_THAN_242_TONE_RU)
		cap |= STA_REC_HE_CAP_RX_1024QAM_UNDER_RU242;

	he->he_cap = cpu_to_le32(cap);

	चयन (sta->bandwidth) अणु
	हाल IEEE80211_STA_RX_BW_160:
		अगर (elem->phy_cap_info[0] &
		    IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G)
			he->max_nss_mcs[CMD_HE_MCS_BW8080] =
				he_cap->he_mcs_nss_supp.rx_mcs_80p80;

		he->max_nss_mcs[CMD_HE_MCS_BW160] =
				he_cap->he_mcs_nss_supp.rx_mcs_160;
		fallthrough;
	शेष:
		he->max_nss_mcs[CMD_HE_MCS_BW80] =
				he_cap->he_mcs_nss_supp.rx_mcs_80;
		अवरोध;
	पूर्ण

	he->t_frame_dur =
		HE_MAC(CAP1_TF_MAC_PAD_DUR_MASK, elem->mac_cap_info[1]);
	he->max_ampdu_exp =
		HE_MAC(CAP3_MAX_AMPDU_LEN_EXP_MASK, elem->mac_cap_info[3]);

	he->bw_set =
		HE_PHY(CAP0_CHANNEL_WIDTH_SET_MASK, elem->phy_cap_info[0]);
	he->device_class =
		HE_PHY(CAP1_DEVICE_CLASS_A, elem->phy_cap_info[1]);
	he->punc_pream_rx =
		HE_PHY(CAP1_PREAMBLE_PUNC_RX_MASK, elem->phy_cap_info[1]);

	he->dcm_tx_mode =
		HE_PHY(CAP3_DCM_MAX_CONST_TX_MASK, elem->phy_cap_info[3]);
	he->dcm_tx_max_nss =
		HE_PHY(CAP3_DCM_MAX_TX_NSS_2, elem->phy_cap_info[3]);
	he->dcm_rx_mode =
		HE_PHY(CAP3_DCM_MAX_CONST_RX_MASK, elem->phy_cap_info[3]);
	he->dcm_rx_max_nss =
		HE_PHY(CAP3_DCM_MAX_RX_NSS_2, elem->phy_cap_info[3]);
	he->dcm_rx_max_nss =
		HE_PHY(CAP8_DCM_MAX_RU_MASK, elem->phy_cap_info[8]);

	he->pkt_ext = 2;
पूर्ण

अटल व्योम
mt7915_mcu_sta_uapsd_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_sta *sta,
		     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा sta_rec_uapsd *uapsd;
	काष्ठा tlv *tlv;

	अगर (vअगर->type != NL80211_IFTYPE_AP || !sta->wme)
		वापस;

	tlv = mt7915_mcu_add_tlv(skb, STA_REC_APPS, माप(*uapsd));
	uapsd = (काष्ठा sta_rec_uapsd *)tlv;

	अगर (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VO) अणु
		uapsd->dac_map |= BIT(3);
		uapsd->tac_map |= BIT(3);
	पूर्ण
	अगर (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VI) अणु
		uapsd->dac_map |= BIT(2);
		uapsd->tac_map |= BIT(2);
	पूर्ण
	अगर (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BE) अणु
		uapsd->dac_map |= BIT(1);
		uapsd->tac_map |= BIT(1);
	पूर्ण
	अगर (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BK) अणु
		uapsd->dac_map |= BIT(0);
		uapsd->tac_map |= BIT(0);
	पूर्ण
	uapsd->max_sp = sta->max_sp;
पूर्ण

अटल व्योम
mt7915_mcu_sta_muru_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ieee80211_sta_he_cap *he_cap = &sta->he_cap;
	काष्ठा ieee80211_he_cap_elem *elem = &he_cap->he_cap_elem;
	काष्ठा sta_rec_muru *muru;
	काष्ठा tlv *tlv;

	tlv = mt7915_mcu_add_tlv(skb, STA_REC_MURU, माप(*muru));

	muru = (काष्ठा sta_rec_muru *)tlv;
	muru->cfg.ofdma_dl_en = true;
	muru->cfg.mimo_dl_en = true;

	muru->ofdma_dl.punc_pream_rx =
		HE_PHY(CAP1_PREAMBLE_PUNC_RX_MASK, elem->phy_cap_info[1]);
	muru->ofdma_dl.he_20m_in_40m_2g =
		HE_PHY(CAP8_20MHZ_IN_40MHZ_HE_PPDU_IN_2G, elem->phy_cap_info[8]);
	muru->ofdma_dl.he_20m_in_160m =
		HE_PHY(CAP8_20MHZ_IN_160MHZ_HE_PPDU, elem->phy_cap_info[8]);
	muru->ofdma_dl.he_80m_in_160m =
		HE_PHY(CAP8_80MHZ_IN_160MHZ_HE_PPDU, elem->phy_cap_info[8]);
	muru->ofdma_dl.lt16_sigb = 0;
	muru->ofdma_dl.rx_su_comp_sigb = 0;
	muru->ofdma_dl.rx_su_non_comp_sigb = 0;

	muru->ofdma_ul.t_frame_dur =
		HE_MAC(CAP1_TF_MAC_PAD_DUR_MASK, elem->mac_cap_info[1]);
	muru->ofdma_ul.mu_cascading =
		HE_MAC(CAP2_MU_CASCADING, elem->mac_cap_info[2]);
	muru->ofdma_ul.uo_ra =
		HE_MAC(CAP3_OFDMA_RA, elem->mac_cap_info[3]);
	muru->ofdma_ul.he_2x996_tone = 0;
	muru->ofdma_ul.rx_t_frame_11ac = 0;

	muru->mimo_dl.vht_mu_bfee =
		!!(sta->vht_cap.cap & IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE);
	muru->mimo_dl.partial_bw_dl_mimo =
		HE_PHY(CAP6_PARTIAL_BANDWIDTH_DL_MUMIMO, elem->phy_cap_info[6]);

	muru->mimo_ul.full_ul_mimo =
		HE_PHY(CAP2_UL_MU_FULL_MU_MIMO, elem->phy_cap_info[2]);
	muru->mimo_ul.partial_ul_mimo =
		HE_PHY(CAP2_UL_MU_PARTIAL_MU_MIMO, elem->phy_cap_info[2]);
पूर्ण

अटल पूर्णांक
mt7915_mcu_add_mu(काष्ठा mt7915_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
		  काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	काष्ठा mt7915_sta *msta = (काष्ठा mt7915_sta *)sta->drv_priv;
	काष्ठा sk_buff *skb;
	पूर्णांक len = माप(काष्ठा sta_req_hdr) + माप(काष्ठा sta_rec_muru);

	अगर (!sta->vht_cap.vht_supported && !sta->he_cap.has_he)
		वापस 0;

	skb = mt7915_mcu_alloc_sta_req(dev, mvअगर, msta, len);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	/* starec muru */
	mt7915_mcu_sta_muru_tlv(skb, sta);

	वापस mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_EXT_CMD(STA_REC_UPDATE), true);
पूर्ण

अटल व्योम
mt7915_mcu_sta_amsdu_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7915_sta *msta = (काष्ठा mt7915_sta *)sta->drv_priv;
	काष्ठा sta_rec_amsdu *amsdu;
	काष्ठा tlv *tlv;

	अगर (!sta->max_amsdu_len)
	    वापस;

	tlv = mt7915_mcu_add_tlv(skb, STA_REC_HW_AMSDU, माप(*amsdu));
	amsdu = (काष्ठा sta_rec_amsdu *)tlv;
	amsdu->max_amsdu_num = 8;
	amsdu->amsdu_en = true;
	amsdu->max_mpdu_size = sta->max_amsdu_len >=
			       IEEE80211_MAX_MPDU_LEN_VHT_7991;
	msta->wcid.amsdu = true;
पूर्ण

अटल bool
mt7915_hw_amsdu_supported(काष्ठा ieee80211_vअगर *vअगर)
अणु
	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_STATION:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम
mt7915_mcu_sta_tlv(काष्ठा mt7915_dev *dev, काष्ठा sk_buff *skb,
		   काष्ठा ieee80211_sta *sta, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा tlv *tlv;

	/* starec ht */
	अगर (sta->ht_cap.ht_supported) अणु
		काष्ठा sta_rec_ht *ht;

		tlv = mt7915_mcu_add_tlv(skb, STA_REC_HT, माप(*ht));
		ht = (काष्ठा sta_rec_ht *)tlv;
		ht->ht_cap = cpu_to_le16(sta->ht_cap.cap);

		अगर (mt7915_hw_amsdu_supported(vअगर))
			mt7915_mcu_sta_amsdu_tlv(skb, sta);
	पूर्ण

	/* starec vht */
	अगर (sta->vht_cap.vht_supported) अणु
		काष्ठा sta_rec_vht *vht;

		tlv = mt7915_mcu_add_tlv(skb, STA_REC_VHT, माप(*vht));
		vht = (काष्ठा sta_rec_vht *)tlv;
		vht->vht_cap = cpu_to_le32(sta->vht_cap.cap);
		vht->vht_rx_mcs_map = sta->vht_cap.vht_mcs.rx_mcs_map;
		vht->vht_tx_mcs_map = sta->vht_cap.vht_mcs.tx_mcs_map;
	पूर्ण

	/* starec he */
	अगर (sta->he_cap.has_he)
		mt7915_mcu_sta_he_tlv(skb, sta);

	/* starec uapsd */
	mt7915_mcu_sta_uapsd_tlv(skb, sta, vअगर);
पूर्ण

अटल व्योम
mt7915_mcu_wtbl_smps_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_sta *sta,
			 व्योम *sta_wtbl, व्योम *wtbl_tlv)
अणु
	काष्ठा wtbl_smps *smps;
	काष्ठा tlv *tlv;

	tlv = mt7915_mcu_add_nested_tlv(skb, WTBL_SMPS, माप(*smps),
					wtbl_tlv, sta_wtbl);
	smps = (काष्ठा wtbl_smps *)tlv;

	अगर (sta->smps_mode == IEEE80211_SMPS_DYNAMIC)
		smps->smps = true;
पूर्ण

अटल व्योम
mt7915_mcu_wtbl_ht_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_sta *sta,
		       व्योम *sta_wtbl, व्योम *wtbl_tlv)
अणु
	काष्ठा wtbl_ht *ht = शून्य;
	काष्ठा tlv *tlv;

	/* wtbl ht */
	अगर (sta->ht_cap.ht_supported) अणु
		tlv = mt7915_mcu_add_nested_tlv(skb, WTBL_HT, माप(*ht),
						wtbl_tlv, sta_wtbl);
		ht = (काष्ठा wtbl_ht *)tlv;
		ht->ldpc = !!(sta->ht_cap.cap & IEEE80211_HT_CAP_LDPC_CODING);
		ht->af = sta->ht_cap.ampdu_factor;
		ht->mm = sta->ht_cap.ampdu_density;
		ht->ht = true;
	पूर्ण

	/* wtbl vht */
	अगर (sta->vht_cap.vht_supported) अणु
		काष्ठा wtbl_vht *vht;
		u8 af;

		tlv = mt7915_mcu_add_nested_tlv(skb, WTBL_VHT, माप(*vht),
						wtbl_tlv, sta_wtbl);
		vht = (काष्ठा wtbl_vht *)tlv;
		vht->ldpc = !!(sta->vht_cap.cap & IEEE80211_VHT_CAP_RXLDPC);
		vht->vht = true;

		af = FIELD_GET(IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK,
			       sta->vht_cap.cap);
		अगर (ht)
			ht->af = max_t(u8, ht->af, af);
	पूर्ण

	mt7915_mcu_wtbl_smps_tlv(skb, sta, sta_wtbl, wtbl_tlv);
पूर्ण

अटल व्योम
mt7915_mcu_wtbl_hdr_trans_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_sta *sta,
			      व्योम *sta_wtbl, व्योम *wtbl_tlv)
अणु
	काष्ठा mt7915_sta *msta;
	काष्ठा wtbl_hdr_trans *htr = शून्य;
	काष्ठा tlv *tlv;

	tlv = mt7915_mcu_add_nested_tlv(skb, WTBL_HDR_TRANS, माप(*htr),
					wtbl_tlv, sta_wtbl);
	htr = (काष्ठा wtbl_hdr_trans *)tlv;
	htr->no_rx_trans = true;
	अगर (vअगर->type == NL80211_IFTYPE_STATION)
		htr->to_ds = true;
	अन्यथा
		htr->from_ds = true;

	अगर (!sta)
		वापस;

	msta = (काष्ठा mt7915_sta *)sta->drv_priv;
	htr->no_rx_trans = !test_bit(MT_WCID_FLAG_HDR_TRANS, &msta->wcid.flags);
	अगर (test_bit(MT_WCID_FLAG_4ADDR, &msta->wcid.flags)) अणु
		htr->to_ds = true;
		htr->from_ds = true;
	पूर्ण
पूर्ण

पूर्णांक mt7915_mcu_sta_update_hdr_trans(काष्ठा mt7915_dev *dev,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7915_sta *msta = (काष्ठा mt7915_sta *)sta->drv_priv;
	काष्ठा wtbl_req_hdr *wtbl_hdr;
	काष्ठा sk_buff *skb;

	skb = mt76_mcu_msg_alloc(&dev->mt76, शून्य, MT7915_WTBL_UPDATE_MAX_SIZE);
	अगर (!skb)
		वापस -ENOMEM;

	wtbl_hdr = mt7915_mcu_alloc_wtbl_req(dev, msta, WTBL_SET, शून्य, &skb);
	अगर (IS_ERR(wtbl_hdr))
		वापस PTR_ERR(wtbl_hdr);

	mt7915_mcu_wtbl_hdr_trans_tlv(skb, vअगर, sta, शून्य, wtbl_hdr);

	वापस mt76_mcu_skb_send_msg(&dev->mt76, skb, MCU_EXT_CMD(WTBL_UPDATE),
				     true);
पूर्ण

पूर्णांक mt7915_mcu_add_smps(काष्ठा mt7915_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	काष्ठा mt7915_sta *msta = (काष्ठा mt7915_sta *)sta->drv_priv;
	काष्ठा wtbl_req_hdr *wtbl_hdr;
	काष्ठा tlv *sta_wtbl;
	काष्ठा sk_buff *skb;

	skb = mt7915_mcu_alloc_sta_req(dev, mvअगर, msta,
				       MT7915_STA_UPDATE_MAX_SIZE);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	sta_wtbl = mt7915_mcu_add_tlv(skb, STA_REC_WTBL, माप(काष्ठा tlv));

	wtbl_hdr = mt7915_mcu_alloc_wtbl_req(dev, msta, WTBL_SET, sta_wtbl,
					     &skb);
	अगर (IS_ERR(wtbl_hdr))
		वापस PTR_ERR(wtbl_hdr);

	mt7915_mcu_wtbl_smps_tlv(skb, sta, sta_wtbl, wtbl_hdr);

	वापस mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_EXT_CMD(STA_REC_UPDATE), true);
पूर्ण

अटल व्योम
mt7915_mcu_sta_sounding_rate(काष्ठा sta_rec_bf *bf)
अणु
	bf->bf_cap = MT_EBF;
	bf->sounding_phy = MT_PHY_TYPE_OFDM;
	bf->ndp_rate = 0;				/* mcs0 */
	bf->ndpa_rate = MT7915_CFEND_RATE_DEFAULT;	/* ofdm 24m */
	bf->rept_poll_rate = MT7915_CFEND_RATE_DEFAULT;	/* ofdm 24m */
पूर्ण

अटल व्योम
mt7915_mcu_sta_bfer_ht(काष्ठा ieee80211_sta *sta, काष्ठा mt7915_phy *phy,
		       काष्ठा sta_rec_bf *bf)
अणु
	काष्ठा ieee80211_mcs_info *mcs = &sta->ht_cap.mcs;
	u8 n = 0;

	bf->tx_mode = MT_PHY_TYPE_HT;
	bf->bf_cap = MT_IBF;

	अगर (mcs->tx_params & IEEE80211_HT_MCS_TX_RX_DIFF &&
	    (mcs->tx_params & IEEE80211_HT_MCS_TX_DEFINED))
		n = FIELD_GET(IEEE80211_HT_MCS_TX_MAX_STREAMS_MASK,
			      mcs->tx_params);
	अन्यथा अगर (mcs->rx_mask[3])
		n = 3;
	अन्यथा अगर (mcs->rx_mask[2])
		n = 2;
	अन्यथा अगर (mcs->rx_mask[1])
		n = 1;

	bf->nr = hweight8(phy->mt76->chainmask) - 1;
	bf->nc = min_t(u8, bf->nr, n);
	bf->ibf_ncol = n;
पूर्ण

अटल व्योम
mt7915_mcu_sta_bfer_vht(काष्ठा ieee80211_sta *sta, काष्ठा mt7915_phy *phy,
			काष्ठा sta_rec_bf *bf, bool explicit)
अणु
	काष्ठा ieee80211_sta_vht_cap *pc = &sta->vht_cap;
	काष्ठा ieee80211_sta_vht_cap *vc = &phy->mt76->sband_5g.sband.vht_cap;
	u16 mcs_map = le16_to_cpu(pc->vht_mcs.rx_mcs_map);
	u8 nss_mcs = mt7915_mcu_get_sta_nss(mcs_map);
	u8 tx_ant = hweight8(phy->mt76->chainmask) - 1;

	bf->tx_mode = MT_PHY_TYPE_VHT;

	अगर (explicit) अणु
		u8 bfee_nr, bfer_nr;

		mt7915_mcu_sta_sounding_rate(bf);
		bfee_nr = FIELD_GET(IEEE80211_VHT_CAP_BEAMFORMEE_STS_MASK,
				    pc->cap);
		bfer_nr = FIELD_GET(IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK,
				    vc->cap);
		bf->nr = min_t(u8, min_t(u8, bfer_nr, bfee_nr), tx_ant);
		bf->nc = min_t(u8, nss_mcs, bf->nr);
		bf->ibf_ncol = bf->nc;

		अगर (sta->bandwidth == IEEE80211_STA_RX_BW_160)
			bf->nr = 1;
	पूर्ण अन्यथा अणु
		bf->bf_cap = MT_IBF;
		bf->nr = tx_ant;
		bf->nc = min_t(u8, nss_mcs, bf->nr);
		bf->ibf_ncol = nss_mcs;

		अगर (sta->bandwidth == IEEE80211_STA_RX_BW_160)
			bf->ibf_nrow = 1;
	पूर्ण
पूर्ण

अटल व्योम
mt7915_mcu_sta_bfer_he(काष्ठा ieee80211_sta *sta, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा mt7915_phy *phy, काष्ठा sta_rec_bf *bf)
अणु
	काष्ठा ieee80211_sta_he_cap *pc = &sta->he_cap;
	काष्ठा ieee80211_he_cap_elem *pe = &pc->he_cap_elem;
	स्थिर काष्ठा ieee80211_sta_he_cap *vc = mt7915_get_he_phy_cap(phy, vअगर);
	स्थिर काष्ठा ieee80211_he_cap_elem *ve = &vc->he_cap_elem;
	u16 mcs_map = le16_to_cpu(pc->he_mcs_nss_supp.rx_mcs_80);
	u8 nss_mcs = mt7915_mcu_get_sta_nss(mcs_map);
	u8 bfee_nr, bfer_nr;

	bf->tx_mode = MT_PHY_TYPE_HE_SU;
	mt7915_mcu_sta_sounding_rate(bf);
	bf->trigger_su = HE_PHY(CAP6_TRIG_SU_BEAMFORMING_FB,
				pe->phy_cap_info[6]);
	bf->trigger_mu = HE_PHY(CAP6_TRIG_MU_BEAMFORMING_PARTIAL_BW_FB,
				pe->phy_cap_info[6]);
	bfer_nr = HE_PHY(CAP5_BEAMFORMEE_NUM_SND_DIM_UNDER_80MHZ_MASK,
			 ve->phy_cap_info[5]);
	bfee_nr = HE_PHY(CAP4_BEAMFORMEE_MAX_STS_UNDER_80MHZ_MASK,
			 pe->phy_cap_info[4]);
	bf->nr = min_t(u8, bfer_nr, bfee_nr);
	bf->nc = min_t(u8, nss_mcs, bf->nr);
	bf->ibf_ncol = bf->nc;

	अगर (sta->bandwidth != IEEE80211_STA_RX_BW_160)
		वापस;

	/* go over क्रम 160MHz and 80p80 */
	अगर (pe->phy_cap_info[0] &
	    IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G) अणु
		mcs_map = le16_to_cpu(pc->he_mcs_nss_supp.rx_mcs_160);
		nss_mcs = mt7915_mcu_get_sta_nss(mcs_map);

		bf->nc_bw160 = nss_mcs;
	पूर्ण

	अगर (pe->phy_cap_info[0] &
	    IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G) अणु
		mcs_map = le16_to_cpu(pc->he_mcs_nss_supp.rx_mcs_80p80);
		nss_mcs = mt7915_mcu_get_sta_nss(mcs_map);

		अगर (bf->nc_bw160)
			bf->nc_bw160 = min_t(u8, bf->nc_bw160, nss_mcs);
		अन्यथा
			bf->nc_bw160 = nss_mcs;
	पूर्ण

	bfer_nr = HE_PHY(CAP5_BEAMFORMEE_NUM_SND_DIM_ABOVE_80MHZ_MASK,
			 ve->phy_cap_info[5]);
	bfee_nr = HE_PHY(CAP4_BEAMFORMEE_MAX_STS_ABOVE_80MHZ_MASK,
			 pe->phy_cap_info[4]);

	bf->nr_bw160 = min_t(पूर्णांक, bfer_nr, bfee_nr);
पूर्ण

अटल व्योम
mt7915_mcu_sta_bfer_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_sta *sta,
			काष्ठा ieee80211_vअगर *vअगर, काष्ठा mt7915_phy *phy,
			bool enable, bool explicit)
अणु
	पूर्णांक tx_ant = hweight8(phy->mt76->chainmask) - 1;
	काष्ठा sta_rec_bf *bf;
	काष्ठा tlv *tlv;
	स्थिर u8 matrix[4][4] = अणु
		अणु0, 0, 0, 0पूर्ण,
		अणु1, 1, 0, 0पूर्ण,	/* 2x1, 2x2, 2x3, 2x4 */
		अणु2, 4, 4, 0पूर्ण,	/* 3x1, 3x2, 3x3, 3x4 */
		अणु3, 5, 6, 0पूर्ण	/* 4x1, 4x2, 4x3, 4x4 */
	पूर्ण;

#घोषणा MT_BFER_FREE		cpu_to_le16(GENMASK(15, 0))

	tlv = mt7915_mcu_add_tlv(skb, STA_REC_BF, माप(*bf));
	bf = (काष्ठा sta_rec_bf *)tlv;

	अगर (!enable) अणु
		bf->pfmu = MT_BFER_FREE;
		वापस;
	पूर्ण

	/* he: eBF only, in accordance with spec
	 * vht: support eBF and iBF
	 * ht: iBF only, since mac80211 lacks of eBF support
	 */
	अगर (sta->he_cap.has_he && explicit)
		mt7915_mcu_sta_bfer_he(sta, vअगर, phy, bf);
	अन्यथा अगर (sta->vht_cap.vht_supported)
		mt7915_mcu_sta_bfer_vht(sta, phy, bf, explicit);
	अन्यथा अगर (sta->ht_cap.ht_supported)
		mt7915_mcu_sta_bfer_ht(sta, phy, bf);
	अन्यथा
		वापस;

	bf->bw = sta->bandwidth;
	bf->ibf_dbw = sta->bandwidth;
	bf->ibf_nrow = tx_ant;

	अगर (!explicit && sta->bandwidth <= IEEE80211_STA_RX_BW_40 && !bf->nc)
		bf->ibf_समयout = 0x48;
	अन्यथा
		bf->ibf_समयout = 0x18;

	अगर (explicit && bf->nr != tx_ant)
		bf->mem_20m = matrix[tx_ant][bf->nc];
	अन्यथा
		bf->mem_20m = matrix[bf->nr][bf->nc];

	चयन (sta->bandwidth) अणु
	हाल IEEE80211_STA_RX_BW_160:
	हाल IEEE80211_STA_RX_BW_80:
		bf->mem_total = bf->mem_20m * 2;
		अवरोध;
	हाल IEEE80211_STA_RX_BW_40:
		bf->mem_total = bf->mem_20m;
		अवरोध;
	हाल IEEE80211_STA_RX_BW_20:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
mt7915_mcu_sta_bfee_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_sta *sta,
			काष्ठा mt7915_phy *phy)
अणु
	पूर्णांक tx_ant = hweight8(phy->mt76->chainmask) - 1;
	काष्ठा sta_rec_bfee *bfee;
	काष्ठा tlv *tlv;
	u8 nr = 0;

	tlv = mt7915_mcu_add_tlv(skb, STA_REC_BFEE, माप(*bfee));
	bfee = (काष्ठा sta_rec_bfee *)tlv;

	अगर (sta->he_cap.has_he) अणु
		काष्ठा ieee80211_he_cap_elem *pe = &sta->he_cap.he_cap_elem;

		nr = HE_PHY(CAP5_BEAMFORMEE_NUM_SND_DIM_UNDER_80MHZ_MASK,
			    pe->phy_cap_info[5]);
	पूर्ण अन्यथा अगर (sta->vht_cap.vht_supported) अणु
		काष्ठा ieee80211_sta_vht_cap *pc = &sta->vht_cap;

		nr = FIELD_GET(IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK,
			       pc->cap);
	पूर्ण

	/* reply with identity matrix to aव्योम 2x2 BF negative gain */
	bfee->fb_identity_matrix = !!(nr == 1 && tx_ant == 2);
पूर्ण

अटल पूर्णांक
mt7915_mcu_add_txbf(काष्ठा mt7915_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
		    काष्ठा ieee80211_sta *sta, bool enable)
अणु
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	काष्ठा mt7915_sta *msta = (काष्ठा mt7915_sta *)sta->drv_priv;
	काष्ठा mt7915_phy *phy;
	काष्ठा sk_buff *skb;
	पूर्णांक r, len;
	bool ebfee = 0, ebf = 0;

	अगर (vअगर->type != NL80211_IFTYPE_STATION &&
	    vअगर->type != NL80211_IFTYPE_AP)
		वापस 0;

	phy = mvअगर->band_idx ? mt7915_ext_phy(dev) : &dev->phy;

	अगर (sta->he_cap.has_he) अणु
		काष्ठा ieee80211_he_cap_elem *pe;
		स्थिर काष्ठा ieee80211_he_cap_elem *ve;
		स्थिर काष्ठा ieee80211_sta_he_cap *vc;

		pe = &sta->he_cap.he_cap_elem;
		vc = mt7915_get_he_phy_cap(phy, vअगर);
		ve = &vc->he_cap_elem;

		ebfee = !!((HE_PHY(CAP3_SU_BEAMFORMER, pe->phy_cap_info[3]) ||
			    HE_PHY(CAP4_MU_BEAMFORMER, pe->phy_cap_info[4])) &&
			   HE_PHY(CAP4_SU_BEAMFORMEE, ve->phy_cap_info[4]));
		ebf = !!((HE_PHY(CAP3_SU_BEAMFORMER, ve->phy_cap_info[3]) ||
			  HE_PHY(CAP4_MU_BEAMFORMER, ve->phy_cap_info[4])) &&
			 HE_PHY(CAP4_SU_BEAMFORMEE, pe->phy_cap_info[4]));
	पूर्ण अन्यथा अगर (sta->vht_cap.vht_supported) अणु
		काष्ठा ieee80211_sta_vht_cap *pc;
		काष्ठा ieee80211_sta_vht_cap *vc;
		u32 cr, ce;

		pc = &sta->vht_cap;
		vc = &phy->mt76->sband_5g.sband.vht_cap;
		cr = IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE |
		     IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE;
		ce = IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE |
		     IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE;

		ebfee = !!((pc->cap & cr) && (vc->cap & ce));
		ebf = !!((vc->cap & cr) && (pc->cap & ce));
	पूर्ण

	/* must keep each tag independent */

	/* starec bf */
	अगर (ebf || dev->ibf) अणु
		len = माप(काष्ठा sta_req_hdr) + माप(काष्ठा sta_rec_bf);

		skb = mt7915_mcu_alloc_sta_req(dev, mvअगर, msta, len);
		अगर (IS_ERR(skb))
			वापस PTR_ERR(skb);

		mt7915_mcu_sta_bfer_tlv(skb, sta, vअगर, phy, enable, ebf);

		r = mt76_mcu_skb_send_msg(&dev->mt76, skb,
					  MCU_EXT_CMD(STA_REC_UPDATE), true);
		अगर (r)
			वापस r;
	पूर्ण

	/* starec bfee */
	अगर (ebfee) अणु
		len = माप(काष्ठा sta_req_hdr) + माप(काष्ठा sta_rec_bfee);

		skb = mt7915_mcu_alloc_sta_req(dev, mvअगर, msta, len);
		अगर (IS_ERR(skb))
			वापस PTR_ERR(skb);

		mt7915_mcu_sta_bfee_tlv(skb, sta, phy);

		r = mt76_mcu_skb_send_msg(&dev->mt76, skb,
					  MCU_EXT_CMD(STA_REC_UPDATE), true);
		अगर (r)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
mt7915_mcu_sta_rate_ctrl_tlv(काष्ठा sk_buff *skb, काष्ठा mt7915_dev *dev,
			     काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7915_sta *msta = (काष्ठा mt7915_sta *)sta->drv_priv;
	काष्ठा mt76_phy *mphy = &dev->mphy;
	क्रमागत nl80211_band band;
	काष्ठा sta_rec_ra *ra;
	काष्ठा tlv *tlv;
	u32 supp_rate, n_rates, cap = sta->wme ? STA_CAP_WMM : 0;
	u8 i, nss = sta->rx_nss, mcs = 0;

	tlv = mt7915_mcu_add_tlv(skb, STA_REC_RA, माप(*ra));
	ra = (काष्ठा sta_rec_ra *)tlv;

	अगर (msta->wcid.ext_phy && dev->mt76.phy2)
		mphy = dev->mt76.phy2;

	band = mphy->chandef.chan->band;
	supp_rate = sta->supp_rates[band];
	n_rates = hweight32(supp_rate);

	ra->valid = true;
	ra->स्वतः_rate = true;
	ra->phy_mode = mt7915_get_phy_mode(mphy, vअगर, sta);
	ra->channel = mphy->chandef.chan->hw_value;
	ra->bw = sta->bandwidth;
	ra->rate_len = n_rates;
	ra->phy.bw = sta->bandwidth;

	अगर (n_rates) अणु
		अगर (band == NL80211_BAND_2GHZ) अणु
			ra->supp_mode = MODE_CCK;
			ra->supp_cck_rate = supp_rate & GENMASK(3, 0);
			ra->phy.type = MT_PHY_TYPE_CCK;

			अगर (n_rates > 4) अणु
				ra->supp_mode |= MODE_OFDM;
				ra->supp_ofdm_rate = supp_rate >> 4;
				ra->phy.type = MT_PHY_TYPE_OFDM;
			पूर्ण
		पूर्ण अन्यथा अणु
			ra->supp_mode = MODE_OFDM;
			ra->supp_ofdm_rate = supp_rate;
			ra->phy.type = MT_PHY_TYPE_OFDM;
		पूर्ण
	पूर्ण

	अगर (sta->ht_cap.ht_supported) अणु
		क्रम (i = 0; i < nss; i++)
			ra->ht_mcs[i] = sta->ht_cap.mcs.rx_mask[i];

		ra->supp_ht_mcs = *(__le32 *)ra->ht_mcs;
		ra->supp_mode |= MODE_HT;
		mcs = hweight32(le32_to_cpu(ra->supp_ht_mcs)) - 1;
		ra->af = sta->ht_cap.ampdu_factor;
		ra->ht_gf = !!(sta->ht_cap.cap & IEEE80211_HT_CAP_GRN_FLD);

		cap |= STA_CAP_HT;
		अगर (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20)
			cap |= STA_CAP_SGI_20;
		अगर (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40)
			cap |= STA_CAP_SGI_40;
		अगर (sta->ht_cap.cap & IEEE80211_HT_CAP_TX_STBC)
			cap |= STA_CAP_TX_STBC;
		अगर (sta->ht_cap.cap & IEEE80211_HT_CAP_RX_STBC)
			cap |= STA_CAP_RX_STBC;
		अगर (sta->ht_cap.cap & IEEE80211_HT_CAP_LDPC_CODING)
			cap |= STA_CAP_LDPC;
	पूर्ण

	अगर (sta->vht_cap.vht_supported) अणु
		u16 mcs_map = le16_to_cpu(sta->vht_cap.vht_mcs.rx_mcs_map);
		u16 vht_mcs;
		u8 af, mcs_prev;

		af = FIELD_GET(IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK,
			       sta->vht_cap.cap);
		ra->af = max_t(u8, ra->af, af);

		cap |= STA_CAP_VHT;
		अगर (sta->vht_cap.cap & IEEE80211_VHT_CAP_SHORT_GI_80)
			cap |= STA_CAP_VHT_SGI_80;
		अगर (sta->vht_cap.cap & IEEE80211_VHT_CAP_SHORT_GI_160)
			cap |= STA_CAP_VHT_SGI_160;
		अगर (sta->vht_cap.cap & IEEE80211_VHT_CAP_TXSTBC)
			cap |= STA_CAP_VHT_TX_STBC;
		अगर (sta->vht_cap.cap & IEEE80211_VHT_CAP_RXSTBC_1)
			cap |= STA_CAP_VHT_RX_STBC;
		अगर (sta->vht_cap.cap & IEEE80211_VHT_CAP_RXLDPC)
			cap |= STA_CAP_VHT_LDPC;

		ra->supp_mode |= MODE_VHT;
		क्रम (mcs = 0, i = 0; i < nss; i++, mcs_map >>= 2) अणु
			चयन (mcs_map & 0x3) अणु
			हाल IEEE80211_VHT_MCS_SUPPORT_0_9:
				vht_mcs = GENMASK(9, 0);
				अवरोध;
			हाल IEEE80211_VHT_MCS_SUPPORT_0_8:
				vht_mcs = GENMASK(8, 0);
				अवरोध;
			हाल IEEE80211_VHT_MCS_SUPPORT_0_7:
				vht_mcs = GENMASK(7, 0);
				अवरोध;
			शेष:
				vht_mcs = 0;
			पूर्ण

			ra->supp_vht_mcs[i] = cpu_to_le16(vht_mcs);

			mcs_prev = hweight16(vht_mcs) - 1;
			अगर (mcs_prev > mcs)
				mcs = mcs_prev;

			/* only support 2ss on 160MHz */
			अगर (i > 1 && (ra->bw == CMD_CBW_160MHZ ||
				      ra->bw == CMD_CBW_8080MHZ))
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (sta->he_cap.has_he) अणु
		ra->supp_mode |= MODE_HE;
		cap |= STA_CAP_HE;
	पूर्ण

	ra->sta_status = cpu_to_le32(cap);

	चयन (BIT(fls(ra->supp_mode) - 1)) अणु
	हाल MODE_VHT:
		ra->phy.type = MT_PHY_TYPE_VHT;
		ra->phy.mcs = mcs;
		ra->phy.nss = nss;
		ra->phy.stbc = !!(sta->vht_cap.cap & IEEE80211_VHT_CAP_TXSTBC);
		ra->phy.ldpc = !!(sta->vht_cap.cap & IEEE80211_VHT_CAP_RXLDPC);
		ra->phy.sgi =
			!!(sta->vht_cap.cap & IEEE80211_VHT_CAP_SHORT_GI_80);
		अवरोध;
	हाल MODE_HT:
		ra->phy.type = MT_PHY_TYPE_HT;
		ra->phy.mcs = mcs;
		ra->phy.ldpc = sta->ht_cap.cap & IEEE80211_HT_CAP_LDPC_CODING;
		ra->phy.stbc = !!(sta->ht_cap.cap & IEEE80211_HT_CAP_TX_STBC);
		ra->phy.sgi = !!(sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक mt7915_mcu_add_rate_ctrl(काष्ठा mt7915_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	काष्ठा mt7915_sta *msta = (काष्ठा mt7915_sta *)sta->drv_priv;
	काष्ठा sk_buff *skb;
	पूर्णांक len = माप(काष्ठा sta_req_hdr) + माप(काष्ठा sta_rec_ra);

	skb = mt7915_mcu_alloc_sta_req(dev, mvअगर, msta, len);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	mt7915_mcu_sta_rate_ctrl_tlv(skb, dev, vअगर, sta);

	वापस mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_EXT_CMD(STA_REC_UPDATE), true);
पूर्ण

पूर्णांक mt7915_mcu_add_sta_adv(काष्ठा mt7915_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta, bool enable)
अणु
	पूर्णांक ret;

	अगर (!sta)
		वापस 0;

	/* must keep the order */
	ret = mt7915_mcu_add_txbf(dev, vअगर, sta, enable);
	अगर (ret)
		वापस ret;

	ret = mt7915_mcu_add_mu(dev, vअगर, sta);
	अगर (ret)
		वापस ret;

	अगर (enable)
		वापस mt7915_mcu_add_rate_ctrl(dev, vअगर, sta);

	वापस 0;
पूर्ण

पूर्णांक mt7915_mcu_add_sta(काष्ठा mt7915_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_sta *sta, bool enable)
अणु
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	काष्ठा wtbl_req_hdr *wtbl_hdr;
	काष्ठा mt7915_sta *msta;
	काष्ठा tlv *sta_wtbl;
	काष्ठा sk_buff *skb;

	msta = sta ? (काष्ठा mt7915_sta *)sta->drv_priv : &mvअगर->sta;

	skb = mt7915_mcu_alloc_sta_req(dev, mvअगर, msta,
				       MT7915_STA_UPDATE_MAX_SIZE);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	mt7915_mcu_sta_basic_tlv(skb, vअगर, sta, enable);
	अगर (enable && sta)
		mt7915_mcu_sta_tlv(dev, skb, sta, vअगर);

	sta_wtbl = mt7915_mcu_add_tlv(skb, STA_REC_WTBL, माप(काष्ठा tlv));

	wtbl_hdr = mt7915_mcu_alloc_wtbl_req(dev, msta, WTBL_RESET_AND_SET,
					     sta_wtbl, &skb);
	अगर (IS_ERR(wtbl_hdr))
		वापस PTR_ERR(wtbl_hdr);

	अगर (enable) अणु
		mt7915_mcu_wtbl_generic_tlv(skb, vअगर, sta, sta_wtbl, wtbl_hdr);
		mt7915_mcu_wtbl_hdr_trans_tlv(skb, vअगर, sta, sta_wtbl, wtbl_hdr);
		अगर (sta)
			mt7915_mcu_wtbl_ht_tlv(skb, sta, sta_wtbl, wtbl_hdr);
	पूर्ण

	वापस mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_EXT_CMD(STA_REC_UPDATE), true);
पूर्ण

पूर्णांक mt7915_mcu_set_fixed_rate(काष्ठा mt7915_dev *dev,
			      काष्ठा ieee80211_sta *sta, u32 rate)
अणु
	काष्ठा mt7915_sta *msta = (काष्ठा mt7915_sta *)sta->drv_priv;
	काष्ठा mt7915_vअगर *mvअगर = msta->vअगर;
	काष्ठा sta_rec_ra_fixed *ra;
	काष्ठा sk_buff *skb;
	काष्ठा tlv *tlv;
	पूर्णांक len = माप(काष्ठा sta_req_hdr) + माप(*ra);

	skb = mt7915_mcu_alloc_sta_req(dev, mvअगर, msta, len);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	tlv = mt7915_mcu_add_tlv(skb, STA_REC_RA_UPDATE, माप(*ra));
	ra = (काष्ठा sta_rec_ra_fixed *)tlv;

	अगर (!rate) अणु
		ra->field = cpu_to_le32(RATE_PARAM_AUTO);
		जाओ out;
	पूर्ण अन्यथा अणु
		ra->field = cpu_to_le32(RATE_PARAM_FIXED);
	पूर्ण

	ra->phy.type = FIELD_GET(RATE_CFG_PHY_TYPE, rate);
	ra->phy.bw = FIELD_GET(RATE_CFG_BW, rate);
	ra->phy.nss = FIELD_GET(RATE_CFG_NSS, rate);
	ra->phy.mcs = FIELD_GET(RATE_CFG_MCS, rate);
	ra->phy.stbc = FIELD_GET(RATE_CFG_STBC, rate);

	अगर (ra->phy.bw)
		ra->phy.ldpc = 7;
	अन्यथा
		ra->phy.ldpc = FIELD_GET(RATE_CFG_LDPC, rate) * 7;

	/* HT/VHT - SGI: 1, LGI: 0; HE - SGI: 0, MGI: 1, LGI: 2 */
	अगर (ra->phy.type > MT_PHY_TYPE_VHT)
		ra->phy.sgi = ra->phy.mcs * 85;
	अन्यथा
		ra->phy.sgi = ra->phy.mcs * 15;

out:
	वापस mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_EXT_CMD(STA_REC_UPDATE), true);
पूर्ण

पूर्णांक mt7915_mcu_add_dev_info(काष्ठा mt7915_phy *phy,
			    काष्ठा ieee80211_vअगर *vअगर, bool enable)
अणु
	काष्ठा mt7915_dev *dev = phy->dev;
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	काष्ठा अणु
		काष्ठा req_hdr अणु
			u8 omac_idx;
			u8 dbdc_idx;
			__le16 tlv_num;
			u8 is_tlv_append;
			u8 rsv[3];
		पूर्ण __packed hdr;
		काष्ठा req_tlv अणु
			__le16 tag;
			__le16 len;
			u8 active;
			u8 dbdc_idx;
			u8 omac_addr[ETH_ALEN];
		पूर्ण __packed tlv;
	पूर्ण data = अणु
		.hdr = अणु
			.omac_idx = mvअगर->omac_idx,
			.dbdc_idx = mvअगर->band_idx,
			.tlv_num = cpu_to_le16(1),
			.is_tlv_append = 1,
		पूर्ण,
		.tlv = अणु
			.tag = cpu_to_le16(DEV_INFO_ACTIVE),
			.len = cpu_to_le16(माप(काष्ठा req_tlv)),
			.active = enable,
			.dbdc_idx = mvअगर->band_idx,
		पूर्ण,
	पूर्ण;

	अगर (mvअगर->omac_idx >= REPEATER_BSSID_START)
		वापस mt7915_mcu_muar_config(phy, vअगर, false, enable);

	स_नकल(data.tlv.omac_addr, vअगर->addr, ETH_ALEN);
	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(DEV_INFO_UPDATE),
				 &data, माप(data), true);
पूर्ण

अटल व्योम
mt7915_mcu_beacon_csa(काष्ठा sk_buff *rskb, काष्ठा sk_buff *skb,
		      काष्ठा bss_info_bcn *bcn,
		      काष्ठा ieee80211_mutable_offsets *offs)
अणु
	अगर (offs->cntdwn_counter_offs[0]) अणु
		काष्ठा tlv *tlv;
		काष्ठा bss_info_bcn_csa *csa;

		tlv = mt7915_mcu_add_nested_subtlv(rskb, BSS_INFO_BCN_CSA,
						   माप(*csa), &bcn->sub_ntlv,
						   &bcn->len);
		csa = (काष्ठा bss_info_bcn_csa *)tlv;
		csa->cnt = skb->data[offs->cntdwn_counter_offs[0]];
	पूर्ण
पूर्ण

अटल व्योम
mt7915_mcu_beacon_cont(काष्ठा mt7915_dev *dev, काष्ठा sk_buff *rskb,
		       काष्ठा sk_buff *skb, काष्ठा bss_info_bcn *bcn,
		       काष्ठा ieee80211_mutable_offsets *offs)
अणु
	काष्ठा mt76_wcid *wcid = &dev->mt76.global_wcid;
	काष्ठा bss_info_bcn_cont *cont;
	काष्ठा tlv *tlv;
	u8 *buf;
	पूर्णांक len = माप(*cont) + MT_TXD_SIZE + skb->len;

	tlv = mt7915_mcu_add_nested_subtlv(rskb, BSS_INFO_BCN_CONTENT,
					   len, &bcn->sub_ntlv, &bcn->len);

	cont = (काष्ठा bss_info_bcn_cont *)tlv;
	cont->pkt_len = cpu_to_le16(MT_TXD_SIZE + skb->len);
	cont->tim_ofs = cpu_to_le16(offs->tim_offset);

	अगर (offs->cntdwn_counter_offs[0])
		cont->csa_ofs = cpu_to_le16(offs->cntdwn_counter_offs[0] - 4);

	buf = (u8 *)tlv + माप(*cont);
	mt7915_mac_ग_लिखो_txwi(dev, (__le32 *)buf, skb, wcid, शून्य,
			      true);
	स_नकल(buf + MT_TXD_SIZE, skb->data, skb->len);
पूर्ण

पूर्णांक mt7915_mcu_add_beacon(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_vअगर *vअगर, पूर्णांक en)
अणु
#घोषणा MAX_BEACON_SIZE 512
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);
	काष्ठा mt7915_phy *phy = mt7915_hw_phy(hw);
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	काष्ठा ieee80211_mutable_offsets offs;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा sk_buff *skb, *rskb;
	काष्ठा tlv *tlv;
	काष्ठा bss_info_bcn *bcn;
	पूर्णांक len = MT7915_BEACON_UPDATE_SIZE + MAX_BEACON_SIZE;

	rskb = mt7915_mcu_alloc_sta_req(dev, mvअगर, शून्य, len);
	अगर (IS_ERR(rskb))
		वापस PTR_ERR(rskb);

	tlv = mt7915_mcu_add_tlv(rskb, BSS_INFO_OFFLOAD, माप(*bcn));
	bcn = (काष्ठा bss_info_bcn *)tlv;
	bcn->enable = en;

	अगर (!en)
		जाओ out;

	skb = ieee80211_beacon_get_ढाँचा(hw, vअगर, &offs);
	अगर (!skb)
		वापस -EINVAL;

	अगर (skb->len > MAX_BEACON_SIZE - MT_TXD_SIZE) अणु
		dev_err(dev->mt76.dev, "Bcn size limit exceed\n");
		dev_kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	अगर (mvअगर->band_idx) अणु
		info = IEEE80211_SKB_CB(skb);
		info->hw_queue |= MT_TX_HW_QUEUE_EXT_PHY;
	पूर्ण

	/* TODO: subtag - bss color count & 11v MBSSID */
	mt7915_mcu_beacon_csa(rskb, skb, bcn, &offs);
	mt7915_mcu_beacon_cont(dev, rskb, skb, bcn, &offs);
	dev_kमुक्त_skb(skb);

out:
	वापस mt76_mcu_skb_send_msg(&phy->dev->mt76, rskb,
				     MCU_EXT_CMD(BSS_INFO_UPDATE), true);
पूर्ण

अटल पूर्णांक mt7915_mcu_start_firmware(काष्ठा mt7915_dev *dev, u32 addr,
				     u32 option)
अणु
	काष्ठा अणु
		__le32 option;
		__le32 addr;
	पूर्ण req = अणु
		.option = cpu_to_le32(option),
		.addr = cpu_to_le32(addr),
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_CMD(FW_START_REQ), &req,
				 माप(req), true);
पूर्ण

अटल पूर्णांक mt7915_mcu_restart(काष्ठा mt76_dev *dev)
अणु
	काष्ठा अणु
		u8 घातer_mode;
		u8 rsv[3];
	पूर्ण req = अणु
		.घातer_mode = 1,
	पूर्ण;

	वापस mt76_mcu_send_msg(dev, MCU_CMD(NIC_POWER_CTRL), &req,
				 माप(req), false);
पूर्ण

अटल पूर्णांक mt7915_mcu_patch_sem_ctrl(काष्ठा mt7915_dev *dev, bool get)
अणु
	काष्ठा अणु
		__le32 op;
	पूर्ण req = अणु
		.op = cpu_to_le32(get ? PATCH_SEM_GET : PATCH_SEM_RELEASE),
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_CMD(PATCH_SEM_CONTROL), &req,
				 माप(req), true);
पूर्ण

अटल पूर्णांक mt7915_mcu_start_patch(काष्ठा mt7915_dev *dev)
अणु
	काष्ठा अणु
		u8 check_crc;
		u8 reserved[3];
	पूर्ण req = अणु
		.check_crc = 0,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_CMD(PATCH_FINISH_REQ), &req,
				 माप(req), true);
पूर्ण

अटल पूर्णांक mt7915_driver_own(काष्ठा mt7915_dev *dev)
अणु
	mt76_wr(dev, MT_TOP_LPCR_HOST_BAND0, MT_TOP_LPCR_HOST_DRV_OWN);
	अगर (!mt76_poll_msec(dev, MT_TOP_LPCR_HOST_BAND0,
			    MT_TOP_LPCR_HOST_FW_OWN, 0, 500)) अणु
		dev_err(dev->mt76.dev, "Timeout for driver own\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt7915_mcu_init_करोwnload(काष्ठा mt7915_dev *dev, u32 addr,
				    u32 len, u32 mode)
अणु
	काष्ठा अणु
		__le32 addr;
		__le32 len;
		__le32 mode;
	पूर्ण req = अणु
		.addr = cpu_to_le32(addr),
		.len = cpu_to_le32(len),
		.mode = cpu_to_le32(mode),
	पूर्ण;
	पूर्णांक attr;

	अगर (req.addr == cpu_to_le32(MCU_PATCH_ADDRESS))
		attr = MCU_CMD(PATCH_START_REQ);
	अन्यथा
		attr = MCU_CMD(TARGET_ADDRESS_LEN_REQ);

	वापस mt76_mcu_send_msg(&dev->mt76, attr, &req, माप(req), true);
पूर्ण

अटल पूर्णांक mt7915_load_patch(काष्ठा mt7915_dev *dev)
अणु
	स्थिर काष्ठा mt7915_patch_hdr *hdr;
	स्थिर काष्ठा firmware *fw = शून्य;
	पूर्णांक i, ret, sem;

	sem = mt7915_mcu_patch_sem_ctrl(dev, 1);
	चयन (sem) अणु
	हाल PATCH_IS_DL:
		वापस 0;
	हाल PATCH_NOT_DL_SEM_SUCCESS:
		अवरोध;
	शेष:
		dev_err(dev->mt76.dev, "Failed to get patch semaphore\n");
		वापस -EAGAIN;
	पूर्ण

	ret = request_firmware(&fw, MT7915_ROM_PATCH, dev->mt76.dev);
	अगर (ret)
		जाओ out;

	अगर (!fw || !fw->data || fw->size < माप(*hdr)) अणु
		dev_err(dev->mt76.dev, "Invalid firmware\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	hdr = (स्थिर काष्ठा mt7915_patch_hdr *)(fw->data);

	dev_info(dev->mt76.dev, "HW/SW Version: 0x%x, Build Time: %.16s\n",
		 be32_to_cpu(hdr->hw_sw_ver), hdr->build_date);

	क्रम (i = 0; i < be32_to_cpu(hdr->desc.n_region); i++) अणु
		काष्ठा mt7915_patch_sec *sec;
		स्थिर u8 *dl;
		u32 len, addr;

		sec = (काष्ठा mt7915_patch_sec *)(fw->data + माप(*hdr) +
						  i * माप(*sec));
		अगर ((be32_to_cpu(sec->type) & PATCH_SEC_TYPE_MASK) !=
		    PATCH_SEC_TYPE_INFO) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		addr = be32_to_cpu(sec->info.addr);
		len = be32_to_cpu(sec->info.len);
		dl = fw->data + be32_to_cpu(sec->offs);

		ret = mt7915_mcu_init_करोwnload(dev, addr, len,
					       DL_MODE_NEED_RSP);
		अगर (ret) अणु
			dev_err(dev->mt76.dev, "Download request failed\n");
			जाओ out;
		पूर्ण

		ret = mt76_mcu_send_firmware(&dev->mt76, MCU_CMD(FW_SCATTER),
					     dl, len);
		अगर (ret) अणु
			dev_err(dev->mt76.dev, "Failed to send patch\n");
			जाओ out;
		पूर्ण
	पूर्ण

	ret = mt7915_mcu_start_patch(dev);
	अगर (ret)
		dev_err(dev->mt76.dev, "Failed to start patch\n");

out:
	sem = mt7915_mcu_patch_sem_ctrl(dev, 0);
	चयन (sem) अणु
	हाल PATCH_REL_SEM_SUCCESS:
		अवरोध;
	शेष:
		ret = -EAGAIN;
		dev_err(dev->mt76.dev, "Failed to release patch semaphore\n");
		जाओ out;
	पूर्ण
	release_firmware(fw);

	वापस ret;
पूर्ण

अटल u32 mt7915_mcu_gen_dl_mode(u8 feature_set, bool is_wa)
अणु
	u32 ret = 0;

	ret |= (feature_set & FW_FEATURE_SET_ENCRYPT) ?
	       (DL_MODE_ENCRYPT | DL_MODE_RESET_SEC_IV) : 0;
	ret |= FIELD_PREP(DL_MODE_KEY_IDX,
			  FIELD_GET(FW_FEATURE_SET_KEY_IDX, feature_set));
	ret |= DL_MODE_NEED_RSP;
	ret |= is_wa ? DL_MODE_WORKING_PDA_CR4 : 0;

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7915_mcu_send_ram_firmware(काष्ठा mt7915_dev *dev,
			     स्थिर काष्ठा mt7915_fw_trailer *hdr,
			     स्थिर u8 *data, bool is_wa)
अणु
	पूर्णांक i, offset = 0;
	u32 override = 0, option = 0;

	क्रम (i = 0; i < hdr->n_region; i++) अणु
		स्थिर काष्ठा mt7915_fw_region *region;
		पूर्णांक err;
		u32 len, addr, mode;

		region = (स्थिर काष्ठा mt7915_fw_region *)((स्थिर u8 *)hdr -
			 (hdr->n_region - i) * माप(*region));
		mode = mt7915_mcu_gen_dl_mode(region->feature_set, is_wa);
		len = le32_to_cpu(region->len);
		addr = le32_to_cpu(region->addr);

		अगर (region->feature_set & FW_FEATURE_OVERRIDE_ADDR)
			override = addr;

		err = mt7915_mcu_init_करोwnload(dev, addr, len, mode);
		अगर (err) अणु
			dev_err(dev->mt76.dev, "Download request failed\n");
			वापस err;
		पूर्ण

		err = mt76_mcu_send_firmware(&dev->mt76, MCU_CMD(FW_SCATTER),
					     data + offset, len);
		अगर (err) अणु
			dev_err(dev->mt76.dev, "Failed to send firmware.\n");
			वापस err;
		पूर्ण

		offset += len;
	पूर्ण

	अगर (override)
		option |= FW_START_OVERRIDE;

	अगर (is_wa)
		option |= FW_START_WORKING_PDA_CR4;

	वापस mt7915_mcu_start_firmware(dev, override, option);
पूर्ण

अटल पूर्णांक mt7915_load_ram(काष्ठा mt7915_dev *dev)
अणु
	स्थिर काष्ठा mt7915_fw_trailer *hdr;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;

	ret = request_firmware(&fw, MT7915_FIRMWARE_WM, dev->mt76.dev);
	अगर (ret)
		वापस ret;

	अगर (!fw || !fw->data || fw->size < माप(*hdr)) अणु
		dev_err(dev->mt76.dev, "Invalid firmware\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	hdr = (स्थिर काष्ठा mt7915_fw_trailer *)(fw->data + fw->size -
					माप(*hdr));

	dev_info(dev->mt76.dev, "WM Firmware Version: %.10s, Build Time: %.15s\n",
		 hdr->fw_ver, hdr->build_date);

	ret = mt7915_mcu_send_ram_firmware(dev, hdr, fw->data, false);
	अगर (ret) अणु
		dev_err(dev->mt76.dev, "Failed to start WM firmware\n");
		जाओ out;
	पूर्ण

	release_firmware(fw);

	ret = request_firmware(&fw, MT7915_FIRMWARE_WA, dev->mt76.dev);
	अगर (ret)
		वापस ret;

	अगर (!fw || !fw->data || fw->size < माप(*hdr)) अणु
		dev_err(dev->mt76.dev, "Invalid firmware\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	hdr = (स्थिर काष्ठा mt7915_fw_trailer *)(fw->data + fw->size -
					माप(*hdr));

	dev_info(dev->mt76.dev, "WA Firmware Version: %.10s, Build Time: %.15s\n",
		 hdr->fw_ver, hdr->build_date);

	ret = mt7915_mcu_send_ram_firmware(dev, hdr, fw->data, true);
	अगर (ret) अणु
		dev_err(dev->mt76.dev, "Failed to start WA firmware\n");
		जाओ out;
	पूर्ण

	snम_लिखो(dev->mt76.hw->wiphy->fw_version,
		 माप(dev->mt76.hw->wiphy->fw_version),
		 "%.10s-%.15s", hdr->fw_ver, hdr->build_date);

out:
	release_firmware(fw);

	वापस ret;
पूर्ण

अटल पूर्णांक mt7915_load_firmware(काष्ठा mt7915_dev *dev)
अणु
	पूर्णांक ret;

	ret = mt7915_load_patch(dev);
	अगर (ret)
		वापस ret;

	ret = mt7915_load_ram(dev);
	अगर (ret)
		वापस ret;

	अगर (!mt76_poll_msec(dev, MT_TOP_MISC, MT_TOP_MISC_FW_STATE,
			    FIELD_PREP(MT_TOP_MISC_FW_STATE,
				       FW_STATE_WACPU_RDY), 1000)) अणु
		dev_err(dev->mt76.dev, "Timeout for initializing firmware\n");
		वापस -EIO;
	पूर्ण

	mt76_queue_tx_cleanup(dev, dev->mt76.q_mcu[MT_MCUQ_FWDL], false);

	dev_dbg(dev->mt76.dev, "Firmware init done\n");

	वापस 0;
पूर्ण

पूर्णांक mt7915_mcu_fw_log_2_host(काष्ठा mt7915_dev *dev, u8 ctrl)
अणु
	काष्ठा अणु
		u8 ctrl_val;
		u8 pad[3];
	पूर्ण data = अणु
		.ctrl_val = ctrl
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(FW_LOG_2_HOST), &data,
				 माप(data), true);
पूर्ण

पूर्णांक mt7915_mcu_fw_dbg_ctrl(काष्ठा mt7915_dev *dev, u32 module, u8 level)
अणु
	काष्ठा अणु
		u8 ver;
		u8 pad;
		__le16 len;
		u8 level;
		u8 rsv[3];
		__le32 module_idx;
	पूर्ण data = अणु
		.module_idx = cpu_to_le32(module),
		.level = level,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(FW_DBG_CTRL), &data,
				 माप(data), false);
पूर्ण

अटल पूर्णांक mt7915_mcu_set_mwds(काष्ठा mt7915_dev *dev, bool enabled)
अणु
	काष्ठा अणु
		u8 enable;
		u8 _rsv[3];
	पूर्ण __packed req = अणु
		.enable = enabled
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_WA_EXT_CMD(MWDS_SUPPORT), &req,
				 माप(req), false);
पूर्ण

पूर्णांक mt7915_mcu_init(काष्ठा mt7915_dev *dev)
अणु
	अटल स्थिर काष्ठा mt76_mcu_ops mt7915_mcu_ops = अणु
		.headroom = माप(काष्ठा mt7915_mcu_txd),
		.mcu_skb_send_msg = mt7915_mcu_send_message,
		.mcu_parse_response = mt7915_mcu_parse_response,
		.mcu_restart = mt7915_mcu_restart,
	पूर्ण;
	पूर्णांक ret;

	dev->mt76.mcu_ops = &mt7915_mcu_ops;

	ret = mt7915_driver_own(dev);
	अगर (ret)
		वापस ret;

	ret = mt7915_load_firmware(dev);
	अगर (ret)
		वापस ret;

	set_bit(MT76_STATE_MCU_RUNNING, &dev->mphy.state);
	mt7915_mcu_fw_log_2_host(dev, 0);
	mt7915_mcu_set_mwds(dev, 1);
	mt7915_mcu_wa_cmd(dev, MCU_WA_PARAM_CMD(SET), MCU_WA_PARAM_RED, 0, 0);

	वापस 0;
पूर्ण

व्योम mt7915_mcu_निकास(काष्ठा mt7915_dev *dev)
अणु
	__mt76_mcu_restart(&dev->mt76);
	अगर (!mt76_poll_msec(dev, MT_TOP_MISC, MT_TOP_MISC_FW_STATE,
			    FIELD_PREP(MT_TOP_MISC_FW_STATE,
				       FW_STATE_FW_DOWNLOAD), 1000)) अणु
		dev_err(dev->mt76.dev, "Failed to exit mcu\n");
		वापस;
	पूर्ण

	mt76_wr(dev, MT_TOP_LPCR_HOST_BAND0, MT_TOP_LPCR_HOST_FW_OWN);
	skb_queue_purge(&dev->mt76.mcu.res_q);
पूर्ण

अटल पूर्णांक
mt7915_mcu_set_rx_hdr_trans_blacklist(काष्ठा mt7915_dev *dev, पूर्णांक band)
अणु
	काष्ठा अणु
		u8 operation;
		u8 count;
		u8 _rsv[2];
		u8 index;
		u8 enable;
		__le16 etype;
	पूर्ण req = अणु
		.operation = 1,
		.count = 1,
		.enable = 1,
		.etype = cpu_to_le16(ETH_P_PAE),
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(RX_HDR_TRANS),
				 &req, माप(req), false);
पूर्ण

पूर्णांक mt7915_mcu_set_mac(काष्ठा mt7915_dev *dev, पूर्णांक band,
		       bool enable, bool hdr_trans)
अणु
	काष्ठा अणु
		u8 operation;
		u8 enable;
		u8 check_bssid;
		u8 insert_vlan;
		u8 हटाओ_vlan;
		u8 tid;
		u8 mode;
		u8 rsv;
	पूर्ण __packed req_trans = अणु
		.enable = hdr_trans,
	पूर्ण;
	काष्ठा अणु
		u8 enable;
		u8 band;
		u8 rsv[2];
	पूर्ण __packed req_mac = अणु
		.enable = enable,
		.band = band,
	पूर्ण;
	पूर्णांक ret;

	ret = mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(RX_HDR_TRANS),
				&req_trans, माप(req_trans), false);
	अगर (ret)
		वापस ret;

	अगर (hdr_trans)
		mt7915_mcu_set_rx_hdr_trans_blacklist(dev, band);

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(MAC_INIT_CTRL),
				 &req_mac, माप(req_mac), true);
पूर्ण

पूर्णांक mt7915_mcu_set_scs(काष्ठा mt7915_dev *dev, u8 band, bool enable)
अणु
	काष्ठा अणु
		__le32 cmd;
		u8 band;
		u8 enable;
	पूर्ण __packed req = अणु
		.cmd = cpu_to_le32(SCS_ENABLE),
		.band = band,
		.enable = enable + 1,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(SCS_CTRL), &req,
				 माप(req), false);
पूर्ण

पूर्णांक mt7915_mcu_set_rts_thresh(काष्ठा mt7915_phy *phy, u32 val)
अणु
	काष्ठा mt7915_dev *dev = phy->dev;
	काष्ठा अणु
		u8 prot_idx;
		u8 band;
		u8 rsv[2];
		__le32 len_thresh;
		__le32 pkt_thresh;
	पूर्ण __packed req = अणु
		.prot_idx = 1,
		.band = phy != &dev->phy,
		.len_thresh = cpu_to_le32(val),
		.pkt_thresh = cpu_to_le32(0x2),
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(PROTECT_CTRL), &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7915_mcu_update_edca(काष्ठा mt7915_dev *dev, व्योम *param)
अणु
	काष्ठा mt7915_mcu_tx *req = (काष्ठा mt7915_mcu_tx *)param;
	u8 num = req->total;
	माप_प्रकार len = माप(*req) -
		     (IEEE80211_NUM_ACS - num) * माप(काष्ठा edca);

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(EDCA_UPDATE), req,
				 len, true);
पूर्ण

पूर्णांक mt7915_mcu_set_tx(काष्ठा mt7915_dev *dev, काष्ठा ieee80211_vअगर *vअगर)
अणु
#घोषणा TX_CMD_MODE		1
	काष्ठा mt7915_mcu_tx req = अणु
		.valid = true,
		.mode = TX_CMD_MODE,
		.total = IEEE80211_NUM_ACS,
	पूर्ण;
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	पूर्णांक ac;

	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++) अणु
		काष्ठा ieee80211_tx_queue_params *q = &mvअगर->queue_params[ac];
		काष्ठा edca *e = &req.edca[ac];

		e->set = WMM_PARAM_SET;
		e->queue = ac + mvअगर->wmm_idx * MT7915_MAX_WMM_SETS;
		e->aअगरs = q->aअगरs;
		e->txop = cpu_to_le16(q->txop);

		अगर (q->cw_min)
			e->cw_min = fls(q->cw_min);
		अन्यथा
			e->cw_min = 5;

		अगर (q->cw_max)
			e->cw_max = cpu_to_le16(fls(q->cw_max));
		अन्यथा
			e->cw_max = cpu_to_le16(10);
	पूर्ण

	वापस mt7915_mcu_update_edca(dev, &req);
पूर्ण

पूर्णांक mt7915_mcu_set_pm(काष्ठा mt7915_dev *dev, पूर्णांक band, पूर्णांक enter)
अणु
#घोषणा ENTER_PM_STATE		1
#घोषणा EXIT_PM_STATE		2
	काष्ठा अणु
		u8 pm_number;
		u8 pm_state;
		u8 bssid[ETH_ALEN];
		u8 dtim_period;
		u8 wlan_idx_lo;
		__le16 bcn_पूर्णांकerval;
		__le32 aid;
		__le32 rx_filter;
		u8 band_idx;
		u8 wlan_idx_hi;
		u8 rsv[2];
		__le32 feature;
		u8 omac_idx;
		u8 wmm_idx;
		u8 bcn_loss_cnt;
		u8 bcn_sp_duration;
	पूर्ण __packed req = अणु
		.pm_number = 5,
		.pm_state = (enter) ? ENTER_PM_STATE : EXIT_PM_STATE,
		.band_idx = band,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(PM_STATE_CTRL), &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7915_mcu_rdd_cmd(काष्ठा mt7915_dev *dev,
		       क्रमागत mt7915_rdd_cmd cmd, u8 index,
		       u8 rx_sel, u8 val)
अणु
	काष्ठा अणु
		u8 ctrl;
		u8 rdd_idx;
		u8 rdd_rx_sel;
		u8 val;
		u8 rsv[4];
	पूर्ण __packed req = अणु
		.ctrl = cmd,
		.rdd_idx = index,
		.rdd_rx_sel = rx_sel,
		.val = val,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(SET_RDD_CTRL), &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7915_mcu_set_fcc5_lpn(काष्ठा mt7915_dev *dev, पूर्णांक val)
अणु
	काष्ठा अणु
		__le32 tag;
		__le16 min_lpn;
		u8 rsv[2];
	पूर्ण __packed req = अणु
		.tag = cpu_to_le32(0x1),
		.min_lpn = cpu_to_le16(val),
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(SET_RDD_TH), &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7915_mcu_set_pulse_th(काष्ठा mt7915_dev *dev,
			    स्थिर काष्ठा mt7915_dfs_pulse *pulse)
अणु
	काष्ठा अणु
		__le32 tag;

		__le32 max_width;		/* us */
		__le32 max_pwr;			/* dbm */
		__le32 min_pwr;			/* dbm */
		__le32 min_stgr_pri;		/* us */
		__le32 max_stgr_pri;		/* us */
		__le32 min_cr_pri;		/* us */
		__le32 max_cr_pri;		/* us */
	पूर्ण __packed req = अणु
		.tag = cpu_to_le32(0x3),

#घोषणा __req_field(field) .field = cpu_to_le32(pulse->field)
		__req_field(max_width),
		__req_field(max_pwr),
		__req_field(min_pwr),
		__req_field(min_stgr_pri),
		__req_field(max_stgr_pri),
		__req_field(min_cr_pri),
		__req_field(max_cr_pri),
#अघोषित __req_field
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(SET_RDD_TH), &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7915_mcu_set_radar_th(काष्ठा mt7915_dev *dev, पूर्णांक index,
			    स्थिर काष्ठा mt7915_dfs_pattern *pattern)
अणु
	काष्ठा अणु
		__le32 tag;
		__le16 radar_type;

		u8 enb;
		u8 stgr;
		u8 min_crpn;
		u8 max_crpn;
		u8 min_crpr;
		u8 min_pw;
		__le32 min_pri;
		__le32 max_pri;
		u8 max_pw;
		u8 min_crbn;
		u8 max_crbn;
		u8 min_stgpn;
		u8 max_stgpn;
		u8 min_stgpr;
		u8 rsv[2];
		__le32 min_stgpr_dअगरf;
	पूर्ण __packed req = अणु
		.tag = cpu_to_le32(0x2),
		.radar_type = cpu_to_le16(index),

#घोषणा __req_field_u8(field) .field = pattern->field
#घोषणा __req_field_u32(field) .field = cpu_to_le32(pattern->field)
		__req_field_u8(enb),
		__req_field_u8(stgr),
		__req_field_u8(min_crpn),
		__req_field_u8(max_crpn),
		__req_field_u8(min_crpr),
		__req_field_u8(min_pw),
		__req_field_u32(min_pri),
		__req_field_u32(max_pri),
		__req_field_u8(max_pw),
		__req_field_u8(min_crbn),
		__req_field_u8(max_crbn),
		__req_field_u8(min_stgpn),
		__req_field_u8(max_stgpn),
		__req_field_u8(min_stgpr),
		__req_field_u32(min_stgpr_dअगरf),
#अघोषित __req_field_u8
#अघोषित __req_field_u32
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(SET_RDD_TH), &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7915_mcu_set_chan_info(काष्ठा mt7915_phy *phy, पूर्णांक cmd)
अणु
	काष्ठा mt7915_dev *dev = phy->dev;
	काष्ठा cfg80211_chan_def *chandef = &phy->mt76->chandef;
	पूर्णांक freq1 = chandef->center_freq1;
	bool ext_phy = phy != &dev->phy;
	काष्ठा अणु
		u8 control_ch;
		u8 center_ch;
		u8 bw;
		u8 tx_streams_num;
		u8 rx_streams;	/* mask or num */
		u8 चयन_reason;
		u8 band_idx;
		u8 center_ch2;	/* क्रम 80+80 only */
		__le16 cac_हाल;
		u8 channel_band;
		u8 rsv0;
		__le32 outband_freq;
		u8 txघातer_drop;
		u8 ap_bw;
		u8 ap_center_ch;
		u8 rsv1[57];
	पूर्ण __packed req = अणु
		.control_ch = chandef->chan->hw_value,
		.center_ch = ieee80211_frequency_to_channel(freq1),
		.bw = mt7915_mcu_chan_bw(chandef),
		.tx_streams_num = hweight8(phy->mt76->antenna_mask),
		.rx_streams = phy->mt76->antenna_mask,
		.band_idx = ext_phy,
		.channel_band = chandef->chan->band,
	पूर्ण;

#अगर_घोषित CONFIG_NL80211_TESTMODE
	अगर (phy->mt76->test.tx_antenna_mask &&
	    (phy->mt76->test.state == MT76_TM_STATE_TX_FRAMES ||
	     phy->mt76->test.state == MT76_TM_STATE_RX_FRAMES ||
	     phy->mt76->test.state == MT76_TM_STATE_TX_CONT)) अणु
		req.tx_streams_num = fls(phy->mt76->test.tx_antenna_mask);
		req.rx_streams = phy->mt76->test.tx_antenna_mask;

		अगर (ext_phy) अणु
			req.tx_streams_num = 2;
			req.rx_streams >>= 2;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (phy->mt76->hw->conf.flags & IEEE80211_CONF_OFFCHANNEL)
		req.चयन_reason = CH_SWITCH_SCAN_BYPASS_DPD;
	अन्यथा अगर ((chandef->chan->flags & IEEE80211_CHAN_RADAR) &&
		 chandef->chan->dfs_state != NL80211_DFS_AVAILABLE)
		req.चयन_reason = CH_SWITCH_DFS;
	अन्यथा
		req.चयन_reason = CH_SWITCH_NORMAL;

	अगर (cmd == MCU_EXT_CMD(CHANNEL_SWITCH))
		req.rx_streams = hweight8(req.rx_streams);

	अगर (chandef->width == NL80211_CHAN_WIDTH_80P80) अणु
		पूर्णांक freq2 = chandef->center_freq2;

		req.center_ch2 = ieee80211_frequency_to_channel(freq2);
	पूर्ण

	वापस mt76_mcu_send_msg(&dev->mt76, cmd, &req, माप(req), true);
पूर्ण

अटल पूर्णांक mt7915_mcu_set_eeprom_flash(काष्ठा mt7915_dev *dev)
अणु
#घोषणा TOTAL_PAGE_MASK		GENMASK(7, 5)
#घोषणा PAGE_IDX_MASK		GENMASK(4, 2)
#घोषणा PER_PAGE_SIZE		0x400
	काष्ठा mt7915_mcu_eeprom req = अणु .buffer_mode = EE_MODE_BUFFER पूर्ण;
	u8 total = MT7915_EEPROM_SIZE / PER_PAGE_SIZE;
	u8 *eep = (u8 *)dev->mt76.eeprom.data;
	पूर्णांक eep_len;
	पूर्णांक i;

	क्रम (i = 0; i <= total; i++, eep += eep_len) अणु
		काष्ठा sk_buff *skb;
		पूर्णांक ret;

		अगर (i == total)
			eep_len = MT7915_EEPROM_SIZE % PER_PAGE_SIZE;
		अन्यथा
			eep_len = PER_PAGE_SIZE;

		skb = mt76_mcu_msg_alloc(&dev->mt76, शून्य,
					 माप(req) + eep_len);
		अगर (!skb)
			वापस -ENOMEM;

		req.क्रमmat = FIELD_PREP(TOTAL_PAGE_MASK, total) |
			     FIELD_PREP(PAGE_IDX_MASK, i) | EE_FORMAT_WHOLE;
		req.len = cpu_to_le16(eep_len);

		skb_put_data(skb, &req, माप(req));
		skb_put_data(skb, eep, eep_len);

		ret = mt76_mcu_skb_send_msg(&dev->mt76, skb,
					    MCU_EXT_CMD(EFUSE_BUFFER_MODE), true);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mt7915_mcu_set_eeprom(काष्ठा mt7915_dev *dev)
अणु
	काष्ठा mt7915_mcu_eeprom req = अणु
		.buffer_mode = EE_MODE_EFUSE,
		.क्रमmat = EE_FORMAT_WHOLE,
	पूर्ण;

	अगर (dev->flash_mode)
		वापस mt7915_mcu_set_eeprom_flash(dev);

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(EFUSE_BUFFER_MODE),
				 &req, माप(req), true);
पूर्ण

पूर्णांक mt7915_mcu_get_eeprom(काष्ठा mt7915_dev *dev, u32 offset)
अणु
	काष्ठा mt7915_mcu_eeprom_info req = अणु
		.addr = cpu_to_le32(round_करोwn(offset, 16)),
	पूर्ण;
	काष्ठा mt7915_mcu_eeprom_info *res;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;
	u8 *buf;

	ret = mt76_mcu_send_and_get_msg(&dev->mt76, MCU_EXT_QUERY(EFUSE_ACCESS), &req,
				माप(req), true, &skb);
	अगर (ret)
		वापस ret;

	res = (काष्ठा mt7915_mcu_eeprom_info *)skb->data;
	buf = dev->mt76.eeprom.data + le32_to_cpu(res->addr);
	स_नकल(buf, res->data, 16);
	dev_kमुक्त_skb(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7915_mcu_set_pre_cal(काष्ठा mt7915_dev *dev, u8 idx,
				  u8 *data, u32 len, पूर्णांक cmd)
अणु
	काष्ठा अणु
		u8 dir;
		u8 valid;
		__le16 biपंचांगap;
		s8 precal;
		u8 action;
		u8 band;
		u8 idx;
		u8 rsv[4];
		__le32 len;
	पूर्ण req;
	काष्ठा sk_buff *skb;

	skb = mt76_mcu_msg_alloc(&dev->mt76, शून्य, माप(req) + len);
	अगर (!skb)
		वापस -ENOMEM;

	req.idx = idx;
	req.len = cpu_to_le32(len);
	skb_put_data(skb, &req, माप(req));
	skb_put_data(skb, data, len);

	वापस mt76_mcu_skb_send_msg(&dev->mt76, skb, cmd, false);
पूर्ण

पूर्णांक mt7915_mcu_apply_group_cal(काष्ठा mt7915_dev *dev)
अणु
	u8 idx = 0, *cal = dev->cal, *eep = dev->mt76.eeprom.data;
	u32 total = MT_EE_CAL_GROUP_SIZE;

	अगर (!(eep[MT_EE_DO_PRE_CAL] & MT_EE_WIFI_CAL_GROUP))
		वापस 0;

	/*
	 * Items: Rx DCOC, RSSI DCOC, Tx TSSI DCOC, Tx LPFG
	 * Tx FDIQ, Tx DCIQ, Rx FDIQ, Rx FIIQ, ADCDCOC
	 */
	जबतक (total > 0) अणु
		पूर्णांक ret, len;

		len = min_t(u32, total, MT_EE_CAL_UNIT);

		ret = mt7915_mcu_set_pre_cal(dev, idx, cal, len,
					     MCU_EXT_CMD(GROUP_PRE_CAL_INFO));
		अगर (ret)
			वापस ret;

		total -= len;
		cal += len;
		idx++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt7915_find_freq_idx(स्थिर u16 *freqs, पूर्णांक n_freqs, u16 cur)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n_freqs; i++)
		अगर (cur == freqs[i])
			वापस i;

	वापस -1;
पूर्ण

अटल पूर्णांक mt7915_dpd_freq_idx(u16 freq, u8 bw)
अणु
	अटल स्थिर u16 freq_list[] = अणु
		5180, 5200, 5220, 5240,
		5260, 5280, 5300, 5320,
		5500, 5520, 5540, 5560,
		5580, 5600, 5620, 5640,
		5660, 5680, 5700, 5745,
		5765, 5785, 5805, 5825
	पूर्ण;
	पूर्णांक offset_2g = ARRAY_SIZE(freq_list);
	पूर्णांक idx;

	अगर (freq < 4000) अणु
		अगर (freq < 2432)
			वापस offset_2g;
		अगर (freq < 2457)
			वापस offset_2g + 1;

		वापस offset_2g + 2;
	पूर्ण

	अगर (bw == NL80211_CHAN_WIDTH_80P80 || bw == NL80211_CHAN_WIDTH_160)
		वापस -1;

	अगर (bw != NL80211_CHAN_WIDTH_20) अणु
		idx = mt7915_find_freq_idx(freq_list, ARRAY_SIZE(freq_list),
					   freq + 10);
		अगर (idx >= 0)
			वापस idx;

		idx = mt7915_find_freq_idx(freq_list, ARRAY_SIZE(freq_list),
					   freq - 10);
		अगर (idx >= 0)
			वापस idx;
	पूर्ण

	वापस mt7915_find_freq_idx(freq_list, ARRAY_SIZE(freq_list), freq);
पूर्ण

पूर्णांक mt7915_mcu_apply_tx_dpd(काष्ठा mt7915_phy *phy)
अणु
	काष्ठा mt7915_dev *dev = phy->dev;
	काष्ठा cfg80211_chan_def *chandef = &phy->mt76->chandef;
	u16 total = 2, idx, center_freq = chandef->center_freq1;
	u8 *cal = dev->cal, *eep = dev->mt76.eeprom.data;

	अगर (!(eep[MT_EE_DO_PRE_CAL] & MT_EE_WIFI_CAL_DPD))
		वापस 0;

	idx = mt7915_dpd_freq_idx(center_freq, chandef->width);
	अगर (idx < 0)
		वापस -EINVAL;

	/* Items: Tx DPD, Tx Flatness */
	idx = idx * 2;
	cal += MT_EE_CAL_GROUP_SIZE;

	जबतक (total--) अणु
		पूर्णांक ret;

		cal += (idx * MT_EE_CAL_UNIT);
		ret = mt7915_mcu_set_pre_cal(dev, idx, cal, MT_EE_CAL_UNIT,
					     MCU_EXT_CMD(DPD_PRE_CAL_INFO));
		अगर (ret)
			वापस ret;

		idx++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mt7915_mcu_get_temperature(काष्ठा mt7915_dev *dev, पूर्णांक index)
अणु
	काष्ठा अणु
		u8 ctrl_id;
		u8 action;
		u8 band;
		u8 rsv[5];
	पूर्ण req = अणु
		.ctrl_id = THERMAL_SENSOR_TEMP_QUERY,
		.action = index,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(THERMAL_CTRL), &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7915_mcu_get_tx_rate(काष्ठा mt7915_dev *dev, u32 cmd, u16 wlan_idx)
अणु
	काष्ठा अणु
		__le32 cmd;
		__le16 wlan_idx;
		__le16 ru_idx;
		__le16 direction;
		__le16 dump_group;
	पूर्ण req = अणु
		.cmd = cpu_to_le32(cmd),
		.wlan_idx = cpu_to_le16(wlan_idx),
		.dump_group = cpu_to_le16(1),
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(RATE_CTRL), &req,
				 माप(req), false);
पूर्ण

पूर्णांक mt7915_mcu_set_txघातer_sku(काष्ठा mt7915_phy *phy)
अणु
#घोषणा MT7915_SKU_RATE_NUM		161
	काष्ठा mt7915_dev *dev = phy->dev;
	काष्ठा mt76_phy *mphy = phy->mt76;
	काष्ठा ieee80211_hw *hw = mphy->hw;
	काष्ठा mt7915_sku_val अणु
		u8 क्रमmat_id;
		u8 limit_type;
		u8 dbdc_idx;
		s8 val[MT7915_SKU_RATE_NUM];
	पूर्ण __packed req = अणु
		.क्रमmat_id = 4,
		.dbdc_idx = phy != &dev->phy,
	पूर्ण;
	काष्ठा mt76_घातer_limits limits_array;
	s8 *la = (s8 *)&limits_array;
	पूर्णांक i, idx, n_chains = hweight8(mphy->antenna_mask);
	पूर्णांक tx_घातer;

	tx_घातer = hw->conf.घातer_level * 2 -
		   mt76_tx_घातer_nss_delta(n_chains);

	tx_घातer = mt76_get_rate_घातer_limits(mphy, mphy->chandef.chan,
					      &limits_array, tx_घातer);
	mphy->txघातer_cur = tx_घातer;

	क्रम (i = 0, idx = 0; i < ARRAY_SIZE(mt7915_sku_group_len); i++) अणु
		u8 mcs_num, len = mt7915_sku_group_len[i];
		पूर्णांक j;

		अगर (i >= SKU_HT_BW20 && i <= SKU_VHT_BW160) अणु
			mcs_num = 10;

			अगर (i == SKU_HT_BW20 || i == SKU_VHT_BW20)
				la = (s8 *)&limits_array + 12;
		पूर्ण अन्यथा अणु
			mcs_num = len;
		पूर्ण

		क्रम (j = 0; j < min_t(u8, mcs_num, len); j++)
			req.val[idx + j] = la[j];

		la += mcs_num;
		idx += len;
	पूर्ण

	वापस mt76_mcu_send_msg(&dev->mt76,
				 MCU_EXT_CMD(TX_POWER_FEATURE_CTRL), &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7915_mcu_set_test_param(काष्ठा mt7915_dev *dev, u8 param, bool test_mode,
			      u8 en)
अणु
	काष्ठा अणु
		u8 test_mode_en;
		u8 param_idx;
		u8 _rsv[2];

		u8 enable;
		u8 _rsv2[3];

		u8 pad[8];
	पूर्ण __packed req = अणु
		.test_mode_en = test_mode,
		.param_idx = param,
		.enable = en,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(ATE_CTRL), &req,
				 माप(req), false);
पूर्ण

पूर्णांक mt7915_mcu_set_sku_en(काष्ठा mt7915_phy *phy, bool enable)
अणु
	काष्ठा mt7915_dev *dev = phy->dev;
	काष्ठा mt7915_sku अणु
		u8 क्रमmat_id;
		u8 sku_enable;
		u8 dbdc_idx;
		u8 rsv;
	पूर्ण __packed req = अणु
		.क्रमmat_id = 0,
		.dbdc_idx = phy != &dev->phy,
		.sku_enable = enable,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76,
				 MCU_EXT_CMD(TX_POWER_FEATURE_CTRL), &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7915_mcu_set_ser(काष्ठा mt7915_dev *dev, u8 action, u8 set, u8 band)
अणु
	काष्ठा अणु
		u8 action;
		u8 set;
		u8 band;
		u8 rsv;
	पूर्ण req = अणु
		.action = action,
		.set = set,
		.band = band,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(SET_SER_TRIGGER),
				 &req, माप(req), false);
पूर्ण

पूर्णांक mt7915_mcu_set_txbf_module(काष्ठा mt7915_dev *dev)
अणु
#घोषणा MT_BF_MODULE_UPDATE               25
	काष्ठा अणु
		u8 action;
		u8 bf_num;
		u8 bf_biपंचांगap;
		u8 bf_sel[8];
		u8 rsv[8];
	पूर्ण __packed req = अणु
		.action = MT_BF_MODULE_UPDATE,
		.bf_num = 2,
		.bf_biपंचांगap = GENMASK(1, 0),
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(TXBF_ACTION), &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7915_mcu_set_txbf_type(काष्ठा mt7915_dev *dev)
अणु
#घोषणा MT_BF_TYPE_UPDATE		20
	काष्ठा अणु
		u8 action;
		bool ebf;
		bool ibf;
		u8 rsv;
	पूर्ण __packed req = अणु
		.action = MT_BF_TYPE_UPDATE,
		.ebf = true,
		.ibf = dev->ibf,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(TXBF_ACTION), &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7915_mcu_set_txbf_sounding(काष्ठा mt7915_dev *dev)
अणु
#घोषणा MT_BF_PROCESSING		4
	काष्ठा अणु
		u8 action;
		u8 snd_mode;
		u8 sta_num;
		u8 rsv;
		u8 wlan_idx[4];
		__le32 snd_period;	/* ms */
	पूर्ण __packed req = अणु
		.action = true,
		.snd_mode = MT_BF_PROCESSING,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(TXBF_ACTION), &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7915_mcu_add_obss_spr(काष्ठा mt7915_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
			    bool enable)
अणु
#घोषणा MT_SPR_ENABLE		1
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	काष्ठा अणु
		u8 action;
		u8 arg_num;
		u8 band_idx;
		u8 status;
		u8 drop_tx_idx;
		u8 sta_idx;	/* 256 sta */
		u8 rsv[2];
		__le32 val;
	पूर्ण __packed req = अणु
		.action = MT_SPR_ENABLE,
		.arg_num = 1,
		.band_idx = mvअगर->band_idx,
		.val = cpu_to_le32(enable),
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(SET_SPR), &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7915_mcu_get_rx_rate(काष्ठा mt7915_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta, काष्ठा rate_info *rate)
अणु
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	काष्ठा mt7915_sta *msta = (काष्ठा mt7915_sta *)sta->drv_priv;
	काष्ठा mt7915_dev *dev = phy->dev;
	काष्ठा mt76_phy *mphy = phy->mt76;
	काष्ठा अणु
		u8 category;
		u8 band;
		__le16 wcid;
	पूर्ण __packed req = अणु
		.category = MCU_PHY_STATE_CONTENTION_RX_RATE,
		.band = mvअगर->band_idx,
		.wcid = cpu_to_le16(msta->wcid.idx),
	पूर्ण;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा mt7915_mcu_phy_rx_info *res;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;
	bool cck = false;

	ret = mt76_mcu_send_and_get_msg(&dev->mt76, MCU_EXT_CMD(PHY_STAT_INFO),
					&req, माप(req), true, &skb);
	अगर (ret)
		वापस ret;

	res = (काष्ठा mt7915_mcu_phy_rx_info *)skb->data;

	rate->mcs = res->rate;
	rate->nss = res->nsts + 1;

	चयन (res->mode) अणु
	हाल MT_PHY_TYPE_CCK:
		cck = true;
		fallthrough;
	हाल MT_PHY_TYPE_OFDM:
		अगर (mphy->chandef.chan->band == NL80211_BAND_5GHZ)
			sband = &mphy->sband_5g.sband;
		अन्यथा
			sband = &mphy->sband_2g.sband;

		rate->mcs = mt76_get_rate(&dev->mt76, sband, rate->mcs, cck);
		rate->legacy = sband->bitrates[rate->mcs].bitrate;
		अवरोध;
	हाल MT_PHY_TYPE_HT:
	हाल MT_PHY_TYPE_HT_GF:
		अगर (rate->mcs > 31) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		rate->flags = RATE_INFO_FLAGS_MCS;
		अगर (res->gi)
			rate->flags |= RATE_INFO_FLAGS_SHORT_GI;
		अवरोध;
	हाल MT_PHY_TYPE_VHT:
		अगर (rate->mcs > 9) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		rate->flags = RATE_INFO_FLAGS_VHT_MCS;
		अगर (res->gi)
			rate->flags |= RATE_INFO_FLAGS_SHORT_GI;
		अवरोध;
	हाल MT_PHY_TYPE_HE_SU:
	हाल MT_PHY_TYPE_HE_EXT_SU:
	हाल MT_PHY_TYPE_HE_TB:
	हाल MT_PHY_TYPE_HE_MU:
		अगर (res->gi > NL80211_RATE_INFO_HE_GI_3_2 || rate->mcs > 11) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		rate->he_gi = res->gi;
		rate->flags = RATE_INFO_FLAGS_HE_MCS;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	चयन (res->bw) अणु
	हाल IEEE80211_STA_RX_BW_160:
		rate->bw = RATE_INFO_BW_160;
		अवरोध;
	हाल IEEE80211_STA_RX_BW_80:
		rate->bw = RATE_INFO_BW_80;
		अवरोध;
	हाल IEEE80211_STA_RX_BW_40:
		rate->bw = RATE_INFO_BW_40;
		अवरोध;
	शेष:
		rate->bw = RATE_INFO_BW_20;
		अवरोध;
	पूर्ण

out:
	dev_kमुक्त_skb(skb);

	वापस ret;
पूर्ण
