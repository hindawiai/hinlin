<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2019 MediaTek Inc.
 *
 * Author: Ryder Lee <ryder.lee@mediatek.com>
 *         Roy Luo <royluo@google.com>
 *         Felix Fietkau <nbd@nbd.name>
 *         Lorenzo Bianconi <lorenzo@kernel.org>
 */

#समावेश <linux/devcoredump.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/समयkeeping.h>
#समावेश "mt7615.h"
#समावेश "../trace.h"
#समावेश "../dma.h"
#समावेश "mt7615_trace.h"
#समावेश "mac.h"
#समावेश "mcu.h"

#घोषणा to_rssi(field, rxv)		((FIELD_GET(field, rxv) - 220) / 2)

अटल स्थिर काष्ठा mt7615_dfs_radar_spec etsi_radar_specs = अणु
	.pulse_th = अणु 40, -10, -80, 800, 3360, 128, 5200 पूर्ण,
	.radar_pattern = अणु
		[5] =  अणु 1, 0,  6, 32, 28, 0, 17,  990, 5010, 1, 1 पूर्ण,
		[6] =  अणु 1, 0,  9, 32, 28, 0, 27,  615, 5010, 1, 1 पूर्ण,
		[7] =  अणु 1, 0, 15, 32, 28, 0, 27,  240,  445, 1, 1 पूर्ण,
		[8] =  अणु 1, 0, 12, 32, 28, 0, 42,  240,  510, 1, 1 पूर्ण,
		[9] =  अणु 1, 1,  0,  0,  0, 0, 14, 2490, 3343, 0, 0, 12, 32, 28 पूर्ण,
		[10] = अणु 1, 1,  0,  0,  0, 0, 14, 2490, 3343, 0, 0, 15, 32, 24 पूर्ण,
		[11] = अणु 1, 1,  0,  0,  0, 0, 14,  823, 2510, 0, 0, 18, 32, 28 पूर्ण,
		[12] = अणु 1, 1,  0,  0,  0, 0, 14,  823, 2510, 0, 0, 27, 32, 24 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mt7615_dfs_radar_spec fcc_radar_specs = अणु
	.pulse_th = अणु 40, -10, -80, 800, 3360, 128, 5200 पूर्ण,
	.radar_pattern = अणु
		[0] = अणु 1, 0,  9,  32, 28, 0, 13, 508, 3076, 1,  1 पूर्ण,
		[1] = अणु 1, 0, 12,  32, 28, 0, 17, 140,  240, 1,  1 पूर्ण,
		[2] = अणु 1, 0,  8,  32, 28, 0, 22, 190,  510, 1,  1 पूर्ण,
		[3] = अणु 1, 0,  6,  32, 28, 0, 32, 190,  510, 1,  1 पूर्ण,
		[4] = अणु 1, 0,  9, 255, 28, 0, 13, 323,  343, 1, 32 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mt7615_dfs_radar_spec jp_radar_specs = अणु
	.pulse_th = अणु 40, -10, -80, 800, 3360, 128, 5200 पूर्ण,
	.radar_pattern = अणु
		[0] =  अणु 1, 0,  8, 32, 28, 0, 13,  508, 3076, 1,  1 पूर्ण,
		[1] =  अणु 1, 0, 12, 32, 28, 0, 17,  140,  240, 1,  1 पूर्ण,
		[2] =  अणु 1, 0,  8, 32, 28, 0, 22,  190,  510, 1,  1 पूर्ण,
		[3] =  अणु 1, 0,  6, 32, 28, 0, 32,  190,  510, 1,  1 पूर्ण,
		[4] =  अणु 1, 0,  9, 32, 28, 0, 13,  323,  343, 1, 32 पूर्ण,
		[13] = अणु 1, 0, 8,  32, 28, 0, 14, 3836, 3856, 1,  1 पूर्ण,
		[14] = अणु 1, 0, 8,  32, 28, 0, 14, 3990, 4010, 1,  1 पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा mt76_wcid *mt7615_rx_get_wcid(काष्ठा mt7615_dev *dev,
					    u8 idx, bool unicast)
अणु
	काष्ठा mt7615_sta *sta;
	काष्ठा mt76_wcid *wcid;

	अगर (idx >= MT7615_WTBL_SIZE)
		वापस शून्य;

	wcid = rcu_dereference(dev->mt76.wcid[idx]);
	अगर (unicast || !wcid)
		वापस wcid;

	अगर (!wcid->sta)
		वापस शून्य;

	sta = container_of(wcid, काष्ठा mt7615_sta, wcid);
	अगर (!sta->vअगर)
		वापस शून्य;

	वापस &sta->vअगर->sta.wcid;
पूर्ण

व्योम mt7615_mac_reset_counters(काष्ठा mt7615_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		mt76_rr(dev, MT_TX_AGG_CNT(0, i));
		mt76_rr(dev, MT_TX_AGG_CNT(1, i));
	पूर्ण

	स_रखो(dev->mt76.aggr_stats, 0, माप(dev->mt76.aggr_stats));
	dev->mt76.phy.survey_समय = kसमय_get_bootसमय();
	अगर (dev->mt76.phy2)
		dev->mt76.phy2->survey_समय = kसमय_get_bootसमय();

	/* reset airसमय counters */
	mt76_rr(dev, MT_MIB_SDR9(0));
	mt76_rr(dev, MT_MIB_SDR9(1));

	mt76_rr(dev, MT_MIB_SDR36(0));
	mt76_rr(dev, MT_MIB_SDR36(1));

	mt76_rr(dev, MT_MIB_SDR37(0));
	mt76_rr(dev, MT_MIB_SDR37(1));

	mt76_set(dev, MT_WF_RMAC_MIB_TIME0, MT_WF_RMAC_MIB_RXTIME_CLR);
	mt76_set(dev, MT_WF_RMAC_MIB_AIRTIME0, MT_WF_RMAC_MIB_RXTIME_CLR);
पूर्ण

व्योम mt7615_mac_set_timing(काष्ठा mt7615_phy *phy)
अणु
	s16 coverage_class = phy->coverage_class;
	काष्ठा mt7615_dev *dev = phy->dev;
	bool ext_phy = phy != &dev->phy;
	u32 val, reg_offset;
	u32 cck = FIELD_PREP(MT_TIMEOUT_VAL_PLCP, 231) |
		  FIELD_PREP(MT_TIMEOUT_VAL_CCA, 48);
	u32 ofdm = FIELD_PREP(MT_TIMEOUT_VAL_PLCP, 60) |
		   FIELD_PREP(MT_TIMEOUT_VAL_CCA, 28);
	पूर्णांक sअगरs, offset;
	bool is_5ghz = phy->mt76->chandef.chan->band == NL80211_BAND_5GHZ;

	अगर (!test_bit(MT76_STATE_RUNNING, &phy->mt76->state))
		वापस;

	अगर (is_5ghz)
		sअगरs = 16;
	अन्यथा
		sअगरs = 10;

	अगर (ext_phy) अणु
		coverage_class = max_t(s16, dev->phy.coverage_class,
				       coverage_class);
		mt76_set(dev, MT_ARB_SCR,
			 MT_ARB_SCR_TX1_DISABLE | MT_ARB_SCR_RX1_DISABLE);
	पूर्ण अन्यथा अणु
		काष्ठा mt7615_phy *phy_ext = mt7615_ext_phy(dev);

		अगर (phy_ext)
			coverage_class = max_t(s16, phy_ext->coverage_class,
					       coverage_class);
		mt76_set(dev, MT_ARB_SCR,
			 MT_ARB_SCR_TX0_DISABLE | MT_ARB_SCR_RX0_DISABLE);
	पूर्ण
	udelay(1);

	offset = 3 * coverage_class;
	reg_offset = FIELD_PREP(MT_TIMEOUT_VAL_PLCP, offset) |
		     FIELD_PREP(MT_TIMEOUT_VAL_CCA, offset);
	mt76_wr(dev, MT_TMAC_CDTR, cck + reg_offset);
	mt76_wr(dev, MT_TMAC_ODTR, ofdm + reg_offset);

	mt76_wr(dev, MT_TMAC_ICR(ext_phy),
		FIELD_PREP(MT_IFS_EIFS, 360) |
		FIELD_PREP(MT_IFS_RIFS, 2) |
		FIELD_PREP(MT_IFS_SIFS, sअगरs) |
		FIELD_PREP(MT_IFS_SLOT, phy->slotसमय));

	अगर (phy->slotसमय < 20 || is_5ghz)
		val = MT7615_CFEND_RATE_DEFAULT;
	अन्यथा
		val = MT7615_CFEND_RATE_11B;

	mt76_rmw_field(dev, MT_AGG_ACR(ext_phy), MT_AGG_ACR_CFEND_RATE, val);
	अगर (ext_phy)
		mt76_clear(dev, MT_ARB_SCR,
			   MT_ARB_SCR_TX1_DISABLE | MT_ARB_SCR_RX1_DISABLE);
	अन्यथा
		mt76_clear(dev, MT_ARB_SCR,
			   MT_ARB_SCR_TX0_DISABLE | MT_ARB_SCR_RX0_DISABLE);

पूर्ण

अटल व्योम
mt7615_get_status_freq_info(काष्ठा mt7615_dev *dev, काष्ठा mt76_phy *mphy,
			    काष्ठा mt76_rx_status *status, u8 chfreq)
अणु
	अगर (!test_bit(MT76_HW_SCANNING, &mphy->state) &&
	    !test_bit(MT76_HW_SCHED_SCANNING, &mphy->state) &&
	    !test_bit(MT76_STATE_ROC, &mphy->state)) अणु
		status->freq = mphy->chandef.chan->center_freq;
		status->band = mphy->chandef.chan->band;
		वापस;
	पूर्ण

	status->band = chfreq <= 14 ? NL80211_BAND_2GHZ : NL80211_BAND_5GHZ;
	status->freq = ieee80211_channel_to_frequency(chfreq, status->band);
पूर्ण

अटल व्योम mt7615_mac_fill_पंचांग_rx(काष्ठा mt7615_phy *phy, __le32 *rxv)
अणु
#अगर_घोषित CONFIG_NL80211_TESTMODE
	u32 rxv1 = le32_to_cpu(rxv[0]);
	u32 rxv3 = le32_to_cpu(rxv[2]);
	u32 rxv4 = le32_to_cpu(rxv[3]);
	u32 rxv5 = le32_to_cpu(rxv[4]);
	u8 cbw = FIELD_GET(MT_RXV1_FRAME_MODE, rxv1);
	u8 mode = FIELD_GET(MT_RXV1_TX_MODE, rxv1);
	s16 foe = FIELD_GET(MT_RXV5_FOE, rxv5);
	u32 foe_स्थिर = (BIT(cbw + 1) & 0xf) * 10000;

	अगर (!mode) अणु
		/* CCK */
		foe &= ~BIT(11);
		foe *= 1000;
		foe >>= 11;
	पूर्ण अन्यथा अणु
		अगर (foe > 2048)
			foe -= 4096;

		foe = (foe * foe_स्थिर) >> 15;
	पूर्ण

	phy->test.last_freq_offset = foe;
	phy->test.last_rcpi[0] = FIELD_GET(MT_RXV4_RCPI0, rxv4);
	phy->test.last_rcpi[1] = FIELD_GET(MT_RXV4_RCPI1, rxv4);
	phy->test.last_rcpi[2] = FIELD_GET(MT_RXV4_RCPI2, rxv4);
	phy->test.last_rcpi[3] = FIELD_GET(MT_RXV4_RCPI3, rxv4);
	phy->test.last_ib_rssi[0] = FIELD_GET(MT_RXV3_IB_RSSI, rxv3);
	phy->test.last_wb_rssi[0] = FIELD_GET(MT_RXV3_WB_RSSI, rxv3);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक mt7615_mac_fill_rx(काष्ठा mt7615_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt76_rx_status *status = (काष्ठा mt76_rx_status *)skb->cb;
	काष्ठा mt76_phy *mphy = &dev->mt76.phy;
	काष्ठा mt7615_phy *phy = &dev->phy;
	काष्ठा mt7615_phy *phy2 = dev->mt76.phy2 ? dev->mt76.phy2->priv : शून्य;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_hdr *hdr;
	__le32 *rxd = (__le32 *)skb->data;
	u32 rxd0 = le32_to_cpu(rxd[0]);
	u32 rxd1 = le32_to_cpu(rxd[1]);
	u32 rxd2 = le32_to_cpu(rxd[2]);
	u32 csum_mask = MT_RXD0_NORMAL_IP_SUM | MT_RXD0_NORMAL_UDP_TCP_SUM;
	bool unicast, hdr_trans, हटाओ_pad, insert_ccmp_hdr = false;
	पूर्णांक phy_idx;
	पूर्णांक i, idx;
	u8 chfreq, amsdu_info, qos_ctl = 0;
	u16 seq_ctrl = 0;
	__le16 fc = 0;

	स_रखो(status, 0, माप(*status));

	chfreq = FIELD_GET(MT_RXD1_NORMAL_CH_FREQ, rxd1);
	अगर (!phy2)
		phy_idx = 0;
	अन्यथा अगर (phy2->chfreq == phy->chfreq)
		phy_idx = -1;
	अन्यथा अगर (phy->chfreq == chfreq)
		phy_idx = 0;
	अन्यथा अगर (phy2->chfreq == chfreq)
		phy_idx = 1;
	अन्यथा
		phy_idx = -1;

	अगर (rxd2 & MT_RXD2_NORMAL_AMSDU_ERR)
		वापस -EINVAL;

	unicast = (rxd1 & MT_RXD1_NORMAL_ADDR_TYPE) == MT_RXD1_NORMAL_U2M;
	idx = FIELD_GET(MT_RXD2_NORMAL_WLAN_IDX, rxd2);
	hdr_trans = rxd1 & MT_RXD1_NORMAL_HDR_TRANS;
	status->wcid = mt7615_rx_get_wcid(dev, idx, unicast);

	अगर (status->wcid) अणु
		काष्ठा mt7615_sta *msta;

		msta = container_of(status->wcid, काष्ठा mt7615_sta, wcid);
		spin_lock_bh(&dev->sta_poll_lock);
		अगर (list_empty(&msta->poll_list))
			list_add_tail(&msta->poll_list, &dev->sta_poll_list);
		spin_unlock_bh(&dev->sta_poll_lock);
	पूर्ण

	अगर ((rxd0 & csum_mask) == csum_mask)
		skb->ip_summed = CHECKSUM_UNNECESSARY;

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

	rxd += 4;
	अगर (rxd0 & MT_RXD0_NORMAL_GROUP_4) अणु
		u32 v0 = le32_to_cpu(rxd[0]);
		u32 v2 = le32_to_cpu(rxd[2]);

		fc = cpu_to_le16(FIELD_GET(MT_RXD4_FRAME_CONTROL, v0));
		qos_ctl = FIELD_GET(MT_RXD6_QOS_CTL, v2);
		seq_ctrl = FIELD_GET(MT_RXD6_SEQ_CTRL, v2);

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
			अगर (phy->rx_ampdu_ts != status->बारtamp) अणु
				अगर (!++phy->ampdu_ref)
					phy->ampdu_ref++;
			पूर्ण
			phy->rx_ampdu_ts = status->बारtamp;

			status->ampdu_ref = phy->ampdu_ref;
		पूर्ण

		rxd += 2;
		अगर ((u8 *)rxd - skb->data >= skb->len)
			वापस -EINVAL;
	पूर्ण

	अगर (rxd0 & MT_RXD0_NORMAL_GROUP_3) अणु
		u32 rxdg5 = le32_to_cpu(rxd[5]);

		/*
		 * If both PHYs are on the same channel and we करोn't have a WCID,
		 * we need to figure out which PHY this packet was received on.
		 * On the primary PHY, the noise value क्रम the chains beदीर्घing to the
		 * second PHY will be set to the noise value of the last packet from
		 * that PHY.
		 */
		अगर (phy_idx < 0) अणु
			पूर्णांक first_chain = ffs(phy2->mt76->chainmask) - 1;

			phy_idx = ((rxdg5 >> (first_chain * 8)) & 0xff) == 0;
		पूर्ण
	पूर्ण

	अगर (phy_idx == 1 && phy2) अणु
		mphy = dev->mt76.phy2;
		phy = phy2;
		status->ext_phy = true;
	पूर्ण

	अगर (!mt7615_firmware_offload(dev) && chfreq != phy->chfreq)
		वापस -EINVAL;

	mt7615_get_status_freq_info(dev, mphy, status, chfreq);
	अगर (status->band == NL80211_BAND_5GHZ)
		sband = &mphy->sband_5g.sband;
	अन्यथा
		sband = &mphy->sband_2g.sband;

	अगर (!test_bit(MT76_STATE_RUNNING, &mphy->state))
		वापस -EINVAL;

	अगर (!sband->channels)
		वापस -EINVAL;

	अगर (rxd0 & MT_RXD0_NORMAL_GROUP_3) अणु
		u32 rxdg0 = le32_to_cpu(rxd[0]);
		u32 rxdg1 = le32_to_cpu(rxd[1]);
		u32 rxdg3 = le32_to_cpu(rxd[3]);
		u8 stbc = FIELD_GET(MT_RXV1_HT_STBC, rxdg0);
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
			अगर (i > 31)
				वापस -EINVAL;
			अवरोध;
		हाल MT_PHY_TYPE_VHT:
			status->nss = FIELD_GET(MT_RXV2_NSTS, rxdg1) + 1;
			status->encoding = RX_ENC_VHT;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		status->rate_idx = i;

		चयन (FIELD_GET(MT_RXV1_FRAME_MODE, rxdg0)) अणु
		हाल MT_PHY_BW_20:
			अवरोध;
		हाल MT_PHY_BW_40:
			status->bw = RATE_INFO_BW_40;
			अवरोध;
		हाल MT_PHY_BW_80:
			status->bw = RATE_INFO_BW_80;
			अवरोध;
		हाल MT_PHY_BW_160:
			status->bw = RATE_INFO_BW_160;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अगर (rxdg0 & MT_RXV1_HT_SHORT_GI)
			status->enc_flags |= RX_ENC_FLAG_SHORT_GI;
		अगर (rxdg0 & MT_RXV1_HT_AD_CODE)
			status->enc_flags |= RX_ENC_FLAG_LDPC;

		status->enc_flags |= RX_ENC_FLAG_STBC_MASK * stbc;

		status->chains = mphy->antenna_mask;
		status->chain_संकेत[0] = to_rssi(MT_RXV4_RCPI0, rxdg3);
		status->chain_संकेत[1] = to_rssi(MT_RXV4_RCPI1, rxdg3);
		status->chain_संकेत[2] = to_rssi(MT_RXV4_RCPI2, rxdg3);
		status->chain_संकेत[3] = to_rssi(MT_RXV4_RCPI3, rxdg3);
		status->संकेत = status->chain_संकेत[0];

		क्रम (i = 1; i < hweight8(mphy->antenna_mask); i++) अणु
			अगर (!(status->chains & BIT(i)))
				जारी;

			status->संकेत = max(status->संकेत,
					     status->chain_संकेत[i]);
		पूर्ण

		mt7615_mac_fill_पंचांग_rx(mphy->priv, rxd);

		rxd += 6;
		अगर ((u8 *)rxd - skb->data >= skb->len)
			वापस -EINVAL;
	पूर्ण

	skb_pull(skb, (u8 *)rxd - skb->data + 2 * हटाओ_pad);

	amsdu_info = FIELD_GET(MT_RXD1_NORMAL_PAYLOAD_FORMAT, rxd1);
	status->amsdu = !!amsdu_info;
	अगर (status->amsdu) अणु
		status->first_amsdu = amsdu_info == MT_RXD1_FIRST_AMSDU_FRAME;
		status->last_amsdu = amsdu_info == MT_RXD1_LAST_AMSDU_FRAME;
		अगर (!hdr_trans) अणु
			स_हटाओ(skb->data + 2, skb->data,
				ieee80211_get_hdrlen_from_skb(skb));
			skb_pull(skb, 2);
		पूर्ण
	पूर्ण

	अगर (insert_ccmp_hdr && !hdr_trans) अणु
		u8 key_id = FIELD_GET(MT_RXD1_NORMAL_KEY_ID, rxd1);

		mt76_insert_ccmp_hdr(skb, key_id);
	पूर्ण

	अगर (!hdr_trans) अणु
		hdr = (काष्ठा ieee80211_hdr *)skb->data;
		fc = hdr->frame_control;
		अगर (ieee80211_is_data_qos(fc)) अणु
			seq_ctrl = le16_to_cpu(hdr->seq_ctrl);
			qos_ctl = *ieee80211_get_qos_ctl(hdr);
		पूर्ण
	पूर्ण अन्यथा अणु
		status->flag |= RX_FLAG_8023;
	पूर्ण

	अगर (!status->wcid || !ieee80211_is_data_qos(fc))
		वापस 0;

	status->aggr = unicast &&
		       !ieee80211_is_qos_nullfunc(fc);
	status->qos_ctl = qos_ctl;
	status->seqno = IEEE80211_SEQ_TO_SN(seq_ctrl);

	वापस 0;
पूर्ण

व्योम mt7615_sta_ps(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_sta *sta, bool ps)
अणु
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_sta_ps);

अटल u16
mt7615_mac_tx_rate_val(काष्ठा mt7615_dev *dev,
		       काष्ठा mt76_phy *mphy,
		       स्थिर काष्ठा ieee80211_tx_rate *rate,
		       bool stbc, u8 *bw)
अणु
	u8 phy, nss, rate_idx;
	u16 rateval = 0;

	*bw = 0;

	अगर (rate->flags & IEEE80211_TX_RC_VHT_MCS) अणु
		rate_idx = ieee80211_rate_get_vht_mcs(rate);
		nss = ieee80211_rate_get_vht_nss(rate);
		phy = MT_PHY_TYPE_VHT;
		अगर (rate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
			*bw = 1;
		अन्यथा अगर (rate->flags & IEEE80211_TX_RC_80_MHZ_WIDTH)
			*bw = 2;
		अन्यथा अगर (rate->flags & IEEE80211_TX_RC_160_MHZ_WIDTH)
			*bw = 3;
	पूर्ण अन्यथा अगर (rate->flags & IEEE80211_TX_RC_MCS) अणु
		rate_idx = rate->idx;
		nss = 1 + (rate->idx >> 3);
		phy = MT_PHY_TYPE_HT;
		अगर (rate->flags & IEEE80211_TX_RC_GREEN_FIELD)
			phy = MT_PHY_TYPE_HT_GF;
		अगर (rate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
			*bw = 1;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा ieee80211_rate *r;
		पूर्णांक band = mphy->chandef.chan->band;
		u16 val;

		nss = 1;
		r = &mphy->hw->wiphy->bands[band]->bitrates[rate->idx];
		अगर (rate->flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE)
			val = r->hw_value_लघु;
		अन्यथा
			val = r->hw_value;

		phy = val >> 8;
		rate_idx = val & 0xff;
	पूर्ण

	अगर (stbc && nss == 1) अणु
		nss++;
		rateval |= MT_TX_RATE_STBC;
	पूर्ण

	rateval |= (FIELD_PREP(MT_TX_RATE_IDX, rate_idx) |
		    FIELD_PREP(MT_TX_RATE_MODE, phy) |
		    FIELD_PREP(MT_TX_RATE_NSS, nss - 1));

	वापस rateval;
पूर्ण

पूर्णांक mt7615_mac_ग_लिखो_txwi(काष्ठा mt7615_dev *dev, __le32 *txwi,
			  काष्ठा sk_buff *skb, काष्ठा mt76_wcid *wcid,
			  काष्ठा ieee80211_sta *sta, पूर्णांक pid,
			  काष्ठा ieee80211_key_conf *key, bool beacon)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	u8 fc_type, fc_stype, p_fmt, q_idx, omac_idx = 0, wmm_idx = 0;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_tx_rate *rate = &info->control.rates[0];
	bool ext_phy = info->hw_queue & MT_TX_HW_QUEUE_EXT_PHY;
	bool multicast = is_multicast_ether_addr(hdr->addr1);
	काष्ठा ieee80211_vअगर *vअगर = info->control.vअगर;
	bool is_mmio = mt76_is_mmio(&dev->mt76);
	u32 val, sz_txd = is_mmio ? MT_TXD_SIZE : MT_USB_TXD_SIZE;
	काष्ठा mt76_phy *mphy = &dev->mphy;
	__le16 fc = hdr->frame_control;
	पूर्णांक tx_count = 8;
	u16 seqno = 0;

	अगर (vअगर) अणु
		काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *)vअगर->drv_priv;

		omac_idx = mvअगर->omac_idx;
		wmm_idx = mvअगर->wmm_idx;
	पूर्ण

	अगर (sta) अणु
		काष्ठा mt7615_sta *msta = (काष्ठा mt7615_sta *)sta->drv_priv;

		tx_count = msta->rate_count;
	पूर्ण

	अगर (ext_phy && dev->mt76.phy2)
		mphy = dev->mt76.phy2;

	fc_type = (le16_to_cpu(fc) & IEEE80211_FCTL_FTYPE) >> 2;
	fc_stype = (le16_to_cpu(fc) & IEEE80211_FCTL_STYPE) >> 4;

	अगर (beacon) अणु
		p_fmt = MT_TX_TYPE_FW;
		q_idx = ext_phy ? MT_LMAC_BCN1 : MT_LMAC_BCN0;
	पूर्ण अन्यथा अगर (skb_get_queue_mapping(skb) >= MT_TXQ_PSD) अणु
		p_fmt = is_mmio ? MT_TX_TYPE_CT : MT_TX_TYPE_SF;
		q_idx = ext_phy ? MT_LMAC_ALTX1 : MT_LMAC_ALTX0;
	पूर्ण अन्यथा अणु
		p_fmt = is_mmio ? MT_TX_TYPE_CT : MT_TX_TYPE_SF;
		q_idx = wmm_idx * MT7615_MAX_WMM_SETS +
			mt7615_lmac_mapping(dev, skb_get_queue_mapping(skb));
	पूर्ण

	val = FIELD_PREP(MT_TXD0_TX_BYTES, skb->len + sz_txd) |
	      FIELD_PREP(MT_TXD0_P_IDX, MT_TX_PORT_IDX_LMAC) |
	      FIELD_PREP(MT_TXD0_Q_IDX, q_idx);
	txwi[0] = cpu_to_le32(val);

	val = MT_TXD1_LONG_FORMAT |
	      FIELD_PREP(MT_TXD1_WLAN_IDX, wcid->idx) |
	      FIELD_PREP(MT_TXD1_HDR_FORMAT, MT_HDR_FORMAT_802_11) |
	      FIELD_PREP(MT_TXD1_HDR_INFO,
			 ieee80211_get_hdrlen_from_skb(skb) / 2) |
	      FIELD_PREP(MT_TXD1_TID,
			 skb->priority & IEEE80211_QOS_CTL_TID_MASK) |
	      FIELD_PREP(MT_TXD1_PKT_FMT, p_fmt) |
	      FIELD_PREP(MT_TXD1_OWN_MAC, omac_idx);
	txwi[1] = cpu_to_le32(val);

	val = FIELD_PREP(MT_TXD2_FRAME_TYPE, fc_type) |
	      FIELD_PREP(MT_TXD2_SUB_TYPE, fc_stype) |
	      FIELD_PREP(MT_TXD2_MULTICAST, multicast);
	अगर (key) अणु
		अगर (multicast && ieee80211_is_robust_mgmt_frame(skb) &&
		    key->cipher == WLAN_CIPHER_SUITE_AES_CMAC) अणु
			val |= MT_TXD2_BIP;
			txwi[3] = 0;
		पूर्ण अन्यथा अणु
			txwi[3] = cpu_to_le32(MT_TXD3_PROTECT_FRAME);
		पूर्ण
	पूर्ण अन्यथा अणु
		txwi[3] = 0;
	पूर्ण
	txwi[2] = cpu_to_le32(val);

	अगर (!(info->flags & IEEE80211_TX_CTL_AMPDU))
		txwi[2] |= cpu_to_le32(MT_TXD2_BA_DISABLE);

	txwi[4] = 0;
	txwi[6] = 0;

	अगर (rate->idx >= 0 && rate->count &&
	    !(info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE)) अणु
		bool stbc = info->flags & IEEE80211_TX_CTL_STBC;
		u8 bw;
		u16 rateval = mt7615_mac_tx_rate_val(dev, mphy, rate, stbc,
						     &bw);

		txwi[2] |= cpu_to_le32(MT_TXD2_FIX_RATE);

		val = MT_TXD6_FIXED_BW |
		      FIELD_PREP(MT_TXD6_BW, bw) |
		      FIELD_PREP(MT_TXD6_TX_RATE, rateval);
		txwi[6] |= cpu_to_le32(val);

		अगर (rate->flags & IEEE80211_TX_RC_SHORT_GI)
			txwi[6] |= cpu_to_le32(MT_TXD6_SGI);

		अगर (info->flags & IEEE80211_TX_CTL_LDPC)
			txwi[6] |= cpu_to_le32(MT_TXD6_LDPC);

		अगर (!(rate->flags & (IEEE80211_TX_RC_MCS |
				     IEEE80211_TX_RC_VHT_MCS)))
			txwi[2] |= cpu_to_le32(MT_TXD2_BA_DISABLE);

		tx_count = rate->count;
	पूर्ण

	अगर (!ieee80211_is_beacon(fc)) अणु
		काष्ठा ieee80211_hw *hw = mt76_hw(dev);

		val = MT_TXD5_TX_STATUS_HOST | FIELD_PREP(MT_TXD5_PID, pid);
		अगर (!ieee80211_hw_check(hw, SUPPORTS_PS))
			val |= MT_TXD5_SW_POWER_MGMT;
		txwi[5] = cpu_to_le32(val);
	पूर्ण अन्यथा अणु
		txwi[5] = 0;
		/* use maximum tx count क्रम beacons */
		tx_count = 0x1f;
	पूर्ण

	val = FIELD_PREP(MT_TXD3_REM_TX_COUNT, tx_count);
	अगर (info->flags & IEEE80211_TX_CTL_INJECTED) अणु
		seqno = le16_to_cpu(hdr->seq_ctrl);

		अगर (ieee80211_is_back_req(hdr->frame_control)) अणु
			काष्ठा ieee80211_bar *bar;

			bar = (काष्ठा ieee80211_bar *)skb->data;
			seqno = le16_to_cpu(bar->start_seq_num);
		पूर्ण

		val |= MT_TXD3_SN_VALID |
		       FIELD_PREP(MT_TXD3_SEQ, IEEE80211_SEQ_TO_SN(seqno));
	पूर्ण

	txwi[3] |= cpu_to_le32(val);

	अगर (info->flags & IEEE80211_TX_CTL_NO_ACK)
		txwi[3] |= cpu_to_le32(MT_TXD3_NO_ACK);

	txwi[7] = FIELD_PREP(MT_TXD7_TYPE, fc_type) |
		  FIELD_PREP(MT_TXD7_SUB_TYPE, fc_stype) |
		  FIELD_PREP(MT_TXD7_SPE_IDX, 0x18);
	अगर (!is_mmio)
		txwi[8] = FIELD_PREP(MT_TXD8_L_TYPE, fc_type) |
			  FIELD_PREP(MT_TXD8_L_SUB_TYPE, fc_stype);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_mac_ग_लिखो_txwi);

अटल व्योम
mt7615_txp_skb_unmap_fw(काष्ठा mt76_dev *dev, काष्ठा mt7615_fw_txp *txp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < txp->nbuf; i++)
		dma_unmap_single(dev->dev, le32_to_cpu(txp->buf[i]),
				 le16_to_cpu(txp->len[i]), DMA_TO_DEVICE);
पूर्ण

अटल व्योम
mt7615_txp_skb_unmap_hw(काष्ठा mt76_dev *dev, काष्ठा mt7615_hw_txp *txp)
अणु
	u32 last_mask;
	पूर्णांक i;

	last_mask = is_mt7663(dev) ? MT_TXD_LEN_LAST : MT_TXD_LEN_MSDU_LAST;

	क्रम (i = 0; i < ARRAY_SIZE(txp->ptr); i++) अणु
		काष्ठा mt7615_txp_ptr *ptr = &txp->ptr[i];
		bool last;
		u16 len;

		len = le16_to_cpu(ptr->len0);
		last = len & last_mask;
		len &= MT_TXD_LEN_MASK;
		dma_unmap_single(dev->dev, le32_to_cpu(ptr->buf0), len,
				 DMA_TO_DEVICE);
		अगर (last)
			अवरोध;

		len = le16_to_cpu(ptr->len1);
		last = len & last_mask;
		len &= MT_TXD_LEN_MASK;
		dma_unmap_single(dev->dev, le32_to_cpu(ptr->buf1), len,
				 DMA_TO_DEVICE);
		अगर (last)
			अवरोध;
	पूर्ण
पूर्ण

व्योम mt7615_txp_skb_unmap(काष्ठा mt76_dev *dev,
			  काष्ठा mt76_txwi_cache *t)
अणु
	काष्ठा mt7615_txp_common *txp;

	txp = mt7615_txwi_to_txp(dev, t);
	अगर (is_mt7615(dev))
		mt7615_txp_skb_unmap_fw(dev, &txp->fw);
	अन्यथा
		mt7615_txp_skb_unmap_hw(dev, &txp->hw);
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_txp_skb_unmap);

bool mt7615_mac_wtbl_update(काष्ठा mt7615_dev *dev, पूर्णांक idx, u32 mask)
अणु
	mt76_rmw(dev, MT_WTBL_UPDATE, MT_WTBL_UPDATE_WLAN_IDX,
		 FIELD_PREP(MT_WTBL_UPDATE_WLAN_IDX, idx) | mask);

	वापस mt76_poll(dev, MT_WTBL_UPDATE, MT_WTBL_UPDATE_BUSY,
			 0, 5000);
पूर्ण

व्योम mt7615_mac_sta_poll(काष्ठा mt7615_dev *dev)
अणु
	अटल स्थिर u8 ac_to_tid[4] = अणु
		[IEEE80211_AC_BE] = 0,
		[IEEE80211_AC_BK] = 1,
		[IEEE80211_AC_VI] = 4,
		[IEEE80211_AC_VO] = 6
	पूर्ण;
	अटल स्थिर u8 hw_queue_map[] = अणु
		[IEEE80211_AC_BK] = 0,
		[IEEE80211_AC_BE] = 1,
		[IEEE80211_AC_VI] = 2,
		[IEEE80211_AC_VO] = 3,
	पूर्ण;
	काष्ठा ieee80211_sta *sta;
	काष्ठा mt7615_sta *msta;
	u32 addr, tx_समय[4], rx_समय[4];
	काष्ठा list_head sta_poll_list;
	पूर्णांक i;

	INIT_LIST_HEAD(&sta_poll_list);
	spin_lock_bh(&dev->sta_poll_lock);
	list_splice_init(&dev->sta_poll_list, &sta_poll_list);
	spin_unlock_bh(&dev->sta_poll_lock);

	जबतक (!list_empty(&sta_poll_list)) अणु
		bool clear = false;

		msta = list_first_entry(&sta_poll_list, काष्ठा mt7615_sta,
					poll_list);
		list_del_init(&msta->poll_list);

		addr = mt7615_mac_wtbl_addr(dev, msta->wcid.idx) + 19 * 4;

		क्रम (i = 0; i < 4; i++, addr += 8) अणु
			u32 tx_last = msta->airसमय_ac[i];
			u32 rx_last = msta->airसमय_ac[i + 4];

			msta->airसमय_ac[i] = mt76_rr(dev, addr);
			msta->airसमय_ac[i + 4] = mt76_rr(dev, addr + 4);
			tx_समय[i] = msta->airसमय_ac[i] - tx_last;
			rx_समय[i] = msta->airसमय_ac[i + 4] - rx_last;

			अगर ((tx_last | rx_last) & BIT(30))
				clear = true;
		पूर्ण

		अगर (clear) अणु
			mt7615_mac_wtbl_update(dev, msta->wcid.idx,
					       MT_WTBL_UPDATE_ADM_COUNT_CLEAR);
			स_रखो(msta->airसमय_ac, 0, माप(msta->airसमय_ac));
		पूर्ण

		अगर (!msta->wcid.sta)
			जारी;

		sta = container_of((व्योम *)msta, काष्ठा ieee80211_sta,
				   drv_priv);
		क्रम (i = 0; i < 4; i++) अणु
			u32 tx_cur = tx_समय[i];
			u32 rx_cur = rx_समय[hw_queue_map[i]];
			u8 tid = ac_to_tid[i];

			अगर (!tx_cur && !rx_cur)
				जारी;

			ieee80211_sta_रेजिस्टर_airसमय(sta, tid, tx_cur,
						       rx_cur);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_mac_sta_poll);

अटल व्योम
mt7615_mac_update_rate_desc(काष्ठा mt7615_phy *phy, काष्ठा mt7615_sta *sta,
			    काष्ठा ieee80211_tx_rate *probe_rate,
			    काष्ठा ieee80211_tx_rate *rates,
			    काष्ठा mt7615_rate_desc *rd)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;
	काष्ठा mt76_phy *mphy = phy->mt76;
	काष्ठा ieee80211_tx_rate *ref;
	bool rateset, stbc = false;
	पूर्णांक n_rates = sta->n_rates;
	u8 bw, bw_prev;
	पूर्णांक i, j;

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

		क्रम (j = 0; j < i; j++) अणु
			अगर (rates[i].idx != rates[j].idx)
				जारी;
			अगर ((rates[i].flags ^ rates[j].flags) &
			    (IEEE80211_TX_RC_40_MHZ_WIDTH |
			     IEEE80211_TX_RC_80_MHZ_WIDTH |
			     IEEE80211_TX_RC_160_MHZ_WIDTH))
				जारी;

			अगर (!rates[i].idx)
				जारी;

			rates[i].idx--;
		पूर्ण
	पूर्ण

	rd->val[0] = mt7615_mac_tx_rate_val(dev, mphy, &rates[0], stbc, &bw);
	bw_prev = bw;

	अगर (probe_rate) अणु
		rd->probe_val = mt7615_mac_tx_rate_val(dev, mphy, probe_rate,
						       stbc, &bw);
		अगर (bw)
			rd->bw_idx = 1;
		अन्यथा
			bw_prev = 0;
	पूर्ण अन्यथा अणु
		rd->probe_val = rd->val[0];
	पूर्ण

	rd->val[1] = mt7615_mac_tx_rate_val(dev, mphy, &rates[1], stbc, &bw);
	अगर (bw_prev) अणु
		rd->bw_idx = 3;
		bw_prev = bw;
	पूर्ण

	rd->val[2] = mt7615_mac_tx_rate_val(dev, mphy, &rates[2], stbc, &bw);
	अगर (bw_prev) अणु
		rd->bw_idx = 5;
		bw_prev = bw;
	पूर्ण

	rd->val[3] = mt7615_mac_tx_rate_val(dev, mphy, &rates[3], stbc, &bw);
	अगर (bw_prev)
		rd->bw_idx = 7;

	rd->rateset = rateset;
	rd->bw = bw;
पूर्ण

अटल पूर्णांक
mt7615_mac_queue_rate_update(काष्ठा mt7615_phy *phy, काष्ठा mt7615_sta *sta,
			     काष्ठा ieee80211_tx_rate *probe_rate,
			     काष्ठा ieee80211_tx_rate *rates)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;
	काष्ठा mt7615_wtbl_rate_desc *wrd;

	अगर (work_pending(&dev->rate_work))
		वापस -EBUSY;

	wrd = kzalloc(माप(*wrd), GFP_ATOMIC);
	अगर (!wrd)
		वापस -ENOMEM;

	wrd->sta = sta;
	mt7615_mac_update_rate_desc(phy, sta, probe_rate, rates,
				    &wrd->rate);
	list_add_tail(&wrd->node, &dev->wrd_head);
	queue_work(dev->mt76.wq, &dev->rate_work);

	वापस 0;
पूर्ण

u32 mt7615_mac_get_sta_tid_sn(काष्ठा mt7615_dev *dev, पूर्णांक wcid, u8 tid)
अणु
	u32 addr, val, val2;
	u8 offset;

	addr = mt7615_mac_wtbl_addr(dev, wcid) + 11 * 4;

	offset = tid * 12;
	addr += 4 * (offset / 32);
	offset %= 32;

	val = mt76_rr(dev, addr);
	val >>= (tid % 32);

	अगर (offset > 20) अणु
		addr += 4;
		val2 = mt76_rr(dev, addr);
		val |= val2 << (32 - offset);
	पूर्ण

	वापस val & GENMASK(11, 0);
पूर्ण

व्योम mt7615_mac_set_rates(काष्ठा mt7615_phy *phy, काष्ठा mt7615_sta *sta,
			  काष्ठा ieee80211_tx_rate *probe_rate,
			  काष्ठा ieee80211_tx_rate *rates)
अणु
	पूर्णांक wcid = sta->wcid.idx, n_rates = sta->n_rates;
	काष्ठा mt7615_dev *dev = phy->dev;
	काष्ठा mt7615_rate_desc rd;
	u32 w5, w27, addr;
	u16 idx = sta->vअगर->mt76.omac_idx;

	अगर (!mt76_is_mmio(&dev->mt76)) अणु
		mt7615_mac_queue_rate_update(phy, sta, probe_rate, rates);
		वापस;
	पूर्ण

	अगर (!mt76_poll(dev, MT_WTBL_UPDATE, MT_WTBL_UPDATE_BUSY, 0, 5000))
		वापस;

	स_रखो(&rd, 0, माप(काष्ठा mt7615_rate_desc));
	mt7615_mac_update_rate_desc(phy, sta, probe_rate, rates, &rd);

	addr = mt7615_mac_wtbl_addr(dev, wcid);
	w27 = mt76_rr(dev, addr + 27 * 4);
	w27 &= ~MT_WTBL_W27_CC_BW_SEL;
	w27 |= FIELD_PREP(MT_WTBL_W27_CC_BW_SEL, rd.bw);

	w5 = mt76_rr(dev, addr + 5 * 4);
	w5 &= ~(MT_WTBL_W5_BW_CAP | MT_WTBL_W5_CHANGE_BW_RATE |
		MT_WTBL_W5_MPDU_OK_COUNT |
		MT_WTBL_W5_MPDU_FAIL_COUNT |
		MT_WTBL_W5_RATE_IDX);
	w5 |= FIELD_PREP(MT_WTBL_W5_BW_CAP, rd.bw) |
	      FIELD_PREP(MT_WTBL_W5_CHANGE_BW_RATE,
			 rd.bw_idx ? rd.bw_idx - 1 : 7);

	mt76_wr(dev, MT_WTBL_RIUCR0, w5);

	mt76_wr(dev, MT_WTBL_RIUCR1,
		FIELD_PREP(MT_WTBL_RIUCR1_RATE0, rd.probe_val) |
		FIELD_PREP(MT_WTBL_RIUCR1_RATE1, rd.val[0]) |
		FIELD_PREP(MT_WTBL_RIUCR1_RATE2_LO, rd.val[1]));

	mt76_wr(dev, MT_WTBL_RIUCR2,
		FIELD_PREP(MT_WTBL_RIUCR2_RATE2_HI, rd.val[1] >> 8) |
		FIELD_PREP(MT_WTBL_RIUCR2_RATE3, rd.val[1]) |
		FIELD_PREP(MT_WTBL_RIUCR2_RATE4, rd.val[2]) |
		FIELD_PREP(MT_WTBL_RIUCR2_RATE5_LO, rd.val[2]));

	mt76_wr(dev, MT_WTBL_RIUCR3,
		FIELD_PREP(MT_WTBL_RIUCR3_RATE5_HI, rd.val[2] >> 4) |
		FIELD_PREP(MT_WTBL_RIUCR3_RATE6, rd.val[3]) |
		FIELD_PREP(MT_WTBL_RIUCR3_RATE7, rd.val[3]));

	mt76_wr(dev, MT_WTBL_UPDATE,
		FIELD_PREP(MT_WTBL_UPDATE_WLAN_IDX, wcid) |
		MT_WTBL_UPDATE_RATE_UPDATE |
		MT_WTBL_UPDATE_TX_COUNT_CLEAR);

	mt76_wr(dev, addr + 27 * 4, w27);

	idx = idx > HW_BSSID_MAX ? HW_BSSID_0 : idx;
	addr = idx > 1 ? MT_LPON_TCR2(idx): MT_LPON_TCR0(idx);

	mt76_set(dev, addr, MT_LPON_TCR_MODE); /* TSF पढ़ो */
	sta->rate_set_tsf = mt76_rr(dev, MT_LPON_UTTR0) & ~BIT(0);
	sta->rate_set_tsf |= rd.rateset;

	अगर (!(sta->wcid.tx_info & MT_WCID_TX_INFO_SET))
		mt76_poll(dev, MT_WTBL_UPDATE, MT_WTBL_UPDATE_BUSY, 0, 5000);

	sta->rate_count = 2 * MT7615_RATE_RETRY * n_rates;
	sta->wcid.tx_info |= MT_WCID_TX_INFO_SET;
	sta->rate_probe = !!probe_rate;
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_mac_set_rates);

अटल पूर्णांक
mt7615_mac_wtbl_update_key(काष्ठा mt7615_dev *dev, काष्ठा mt76_wcid *wcid,
			   काष्ठा ieee80211_key_conf *key,
			   क्रमागत mt7615_cipher_type cipher, u16 cipher_mask,
			   क्रमागत set_key_cmd cmd)
अणु
	u32 addr = mt7615_mac_wtbl_addr(dev, wcid->idx) + 30 * 4;
	u8 data[32] = अणुपूर्ण;

	अगर (key->keylen > माप(data))
		वापस -EINVAL;

	mt76_rr_copy(dev, addr, data, माप(data));
	अगर (cmd == SET_KEY) अणु
		अगर (cipher == MT_CIPHER_TKIP) अणु
			/* Rx/Tx MIC keys are swapped */
			स_नकल(data, key->key, 16);
			स_नकल(data + 16, key->key + 24, 8);
			स_नकल(data + 24, key->key + 16, 8);
		पूर्ण अन्यथा अणु
			अगर (cipher_mask == BIT(cipher))
				स_नकल(data, key->key, key->keylen);
			अन्यथा अगर (cipher != MT_CIPHER_BIP_CMAC_128)
				स_नकल(data, key->key, 16);
			अगर (cipher == MT_CIPHER_BIP_CMAC_128)
				स_नकल(data + 16, key->key, 16);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (cipher == MT_CIPHER_BIP_CMAC_128)
			स_रखो(data + 16, 0, 16);
		अन्यथा अगर (cipher_mask)
			स_रखो(data, 0, 16);
		अगर (!cipher_mask)
			स_रखो(data, 0, माप(data));
	पूर्ण

	mt76_wr_copy(dev, addr, data, माप(data));

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7615_mac_wtbl_update_pk(काष्ठा mt7615_dev *dev, काष्ठा mt76_wcid *wcid,
			  क्रमागत mt7615_cipher_type cipher, u16 cipher_mask,
			  पूर्णांक keyidx, क्रमागत set_key_cmd cmd)
अणु
	u32 addr = mt7615_mac_wtbl_addr(dev, wcid->idx), w0, w1;

	अगर (!mt76_poll(dev, MT_WTBL_UPDATE, MT_WTBL_UPDATE_BUSY, 0, 5000))
		वापस -ETIMEDOUT;

	w0 = mt76_rr(dev, addr);
	w1 = mt76_rr(dev, addr + 4);

	अगर (cipher_mask)
		w0 |= MT_WTBL_W0_RX_KEY_VALID;
	अन्यथा
		w0 &= ~(MT_WTBL_W0_RX_KEY_VALID | MT_WTBL_W0_KEY_IDX);
	अगर (cipher_mask & BIT(MT_CIPHER_BIP_CMAC_128))
		w0 |= MT_WTBL_W0_RX_IK_VALID;
	अन्यथा
		w0 &= ~MT_WTBL_W0_RX_IK_VALID;

	अगर (cmd == SET_KEY &&
	    (cipher != MT_CIPHER_BIP_CMAC_128 ||
	     cipher_mask == BIT(cipher))) अणु
		w0 &= ~MT_WTBL_W0_KEY_IDX;
		w0 |= FIELD_PREP(MT_WTBL_W0_KEY_IDX, keyidx);
	पूर्ण

	mt76_wr(dev, MT_WTBL_RICR0, w0);
	mt76_wr(dev, MT_WTBL_RICR1, w1);

	अगर (!mt7615_mac_wtbl_update(dev, wcid->idx,
				    MT_WTBL_UPDATE_RXINFO_UPDATE))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल व्योम
mt7615_mac_wtbl_update_cipher(काष्ठा mt7615_dev *dev, काष्ठा mt76_wcid *wcid,
			      क्रमागत mt7615_cipher_type cipher, u16 cipher_mask,
			      क्रमागत set_key_cmd cmd)
अणु
	u32 addr = mt7615_mac_wtbl_addr(dev, wcid->idx);

	अगर (!cipher_mask) अणु
		mt76_clear(dev, addr + 2 * 4, MT_WTBL_W2_KEY_TYPE);
		वापस;
	पूर्ण

	अगर (cmd != SET_KEY)
		वापस;

	अगर (cipher == MT_CIPHER_BIP_CMAC_128 &&
	    cipher_mask & ~BIT(MT_CIPHER_BIP_CMAC_128))
		वापस;

	mt76_rmw(dev, addr + 2 * 4, MT_WTBL_W2_KEY_TYPE,
		 FIELD_PREP(MT_WTBL_W2_KEY_TYPE, cipher));
पूर्ण

पूर्णांक __mt7615_mac_wtbl_set_key(काष्ठा mt7615_dev *dev,
			      काष्ठा mt76_wcid *wcid,
			      काष्ठा ieee80211_key_conf *key,
			      क्रमागत set_key_cmd cmd)
अणु
	क्रमागत mt7615_cipher_type cipher;
	u16 cipher_mask = wcid->cipher;
	पूर्णांक err;

	cipher = mt7615_mac_get_cipher(key->cipher);
	अगर (cipher == MT_CIPHER_NONE)
		वापस -EOPNOTSUPP;

	अगर (cmd == SET_KEY)
		cipher_mask |= BIT(cipher);
	अन्यथा
		cipher_mask &= ~BIT(cipher);

	mt7615_mac_wtbl_update_cipher(dev, wcid, cipher, cipher_mask, cmd);
	err = mt7615_mac_wtbl_update_key(dev, wcid, key, cipher, cipher_mask,
					 cmd);
	अगर (err < 0)
		वापस err;

	err = mt7615_mac_wtbl_update_pk(dev, wcid, cipher, cipher_mask,
					key->keyidx, cmd);
	अगर (err < 0)
		वापस err;

	wcid->cipher = cipher_mask;

	वापस 0;
पूर्ण

पूर्णांक mt7615_mac_wtbl_set_key(काष्ठा mt7615_dev *dev,
			    काष्ठा mt76_wcid *wcid,
			    काष्ठा ieee80211_key_conf *key,
			    क्रमागत set_key_cmd cmd)
अणु
	पूर्णांक err;

	spin_lock_bh(&dev->mt76.lock);
	err = __mt7615_mac_wtbl_set_key(dev, wcid, key, cmd);
	spin_unlock_bh(&dev->mt76.lock);

	वापस err;
पूर्ण

अटल bool mt7615_fill_txs(काष्ठा mt7615_dev *dev, काष्ठा mt7615_sta *sta,
			    काष्ठा ieee80211_tx_info *info, __le32 *txs_data)
अणु
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा mt7615_rate_set *rs;
	काष्ठा mt76_phy *mphy;
	पूर्णांक first_idx = 0, last_idx;
	पूर्णांक i, idx, count;
	bool fixed_rate, ack_समयout;
	bool probe, ampdu, cck = false;
	bool rs_idx;
	u32 rate_set_tsf;
	u32 final_rate, final_rate_flags, final_nss, txs;

	fixed_rate = info->status.rates[0].count;
	probe = !!(info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE);

	txs = le32_to_cpu(txs_data[1]);
	ampdu = !fixed_rate && (txs & MT_TXS1_AMPDU);

	txs = le32_to_cpu(txs_data[3]);
	count = FIELD_GET(MT_TXS3_TX_COUNT, txs);
	last_idx = FIELD_GET(MT_TXS3_LAST_TX_RATE, txs);

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

	first_idx = max_t(पूर्णांक, 0, last_idx - (count - 1) / MT7615_RATE_RETRY);

	अगर (fixed_rate && !probe) अणु
		info->status.rates[0].count = count;
		i = 0;
		जाओ out;
	पूर्ण

	rate_set_tsf = READ_ONCE(sta->rate_set_tsf);
	rs_idx = !((u32)(FIELD_GET(MT_TXS4_F0_TIMESTAMP, le32_to_cpu(txs_data[4])) -
			 rate_set_tsf) < 1000000);
	rs_idx ^= rate_set_tsf & BIT(0);
	rs = &sta->rateset[rs_idx];

	अगर (!first_idx && rs->probe_rate.idx >= 0) अणु
		info->status.rates[0] = rs->probe_rate;

		spin_lock_bh(&dev->mt76.lock);
		अगर (sta->rate_probe) अणु
			काष्ठा mt7615_phy *phy = &dev->phy;

			अगर (sta->wcid.ext_phy && dev->mt76.phy2)
				phy = dev->mt76.phy2->priv;

			mt7615_mac_set_rates(phy, sta, शून्य, sta->rates);
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
		cur_count = min_t(पूर्णांक, MT7615_RATE_RETRY, count);
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
		mphy = &dev->mphy;
		अगर (sta->wcid.ext_phy && dev->mt76.phy2)
			mphy = dev->mt76.phy2;

		अगर (mphy->chandef.chan->band == NL80211_BAND_5GHZ)
			sband = &mphy->sband_5g.sband;
		अन्यथा
			sband = &mphy->sband_2g.sband;
		final_rate &= MT_TX_RATE_IDX;
		final_rate = mt76_get_rate(&dev->mt76, sband, final_rate,
					   cck);
		final_rate_flags = 0;
		अवरोध;
	हाल MT_PHY_TYPE_HT_GF:
	हाल MT_PHY_TYPE_HT:
		final_rate_flags |= IEEE80211_TX_RC_MCS;
		final_rate &= MT_TX_RATE_IDX;
		अगर (final_rate > 31)
			वापस false;
		अवरोध;
	हाल MT_PHY_TYPE_VHT:
		final_nss = FIELD_GET(MT_TX_RATE_NSS, final_rate);

		अगर ((final_rate & MT_TX_RATE_STBC) && final_nss)
			final_nss--;

		final_rate_flags |= IEEE80211_TX_RC_VHT_MCS;
		final_rate = (final_rate & MT_TX_RATE_IDX) | (final_nss << 4);
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	info->status.rates[i].idx = final_rate;
	info->status.rates[i].flags = final_rate_flags;

	वापस true;
पूर्ण

अटल bool mt7615_mac_add_txs_skb(काष्ठा mt7615_dev *dev,
				   काष्ठा mt7615_sta *sta, पूर्णांक pid,
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

		अगर (!mt7615_fill_txs(dev, sta, info, txs_data)) अणु
			ieee80211_tx_info_clear_status(info);
			info->status.rates[0].idx = -1;
		पूर्ण

		mt76_tx_status_skb_करोne(mdev, skb, &list);
	पूर्ण
	mt76_tx_status_unlock(mdev, &list);

	वापस !!skb;
पूर्ण

अटल व्योम mt7615_mac_add_txs(काष्ठा mt7615_dev *dev, व्योम *data)
अणु
	काष्ठा ieee80211_tx_info info = अणुपूर्ण;
	काष्ठा ieee80211_sta *sta = शून्य;
	काष्ठा mt7615_sta *msta = शून्य;
	काष्ठा mt76_wcid *wcid;
	काष्ठा mt76_phy *mphy = &dev->mt76.phy;
	__le32 *txs_data = data;
	u32 txs;
	u8 wcidx;
	u8 pid;

	txs = le32_to_cpu(txs_data[0]);
	pid = FIELD_GET(MT_TXS0_PID, txs);
	txs = le32_to_cpu(txs_data[2]);
	wcidx = FIELD_GET(MT_TXS2_WCID, txs);

	अगर (pid == MT_PACKET_ID_NO_ACK)
		वापस;

	अगर (wcidx >= MT7615_WTBL_SIZE)
		वापस;

	rcu_पढ़ो_lock();

	wcid = rcu_dereference(dev->mt76.wcid[wcidx]);
	अगर (!wcid)
		जाओ out;

	msta = container_of(wcid, काष्ठा mt7615_sta, wcid);
	sta = wcid_to_sta(wcid);

	spin_lock_bh(&dev->sta_poll_lock);
	अगर (list_empty(&msta->poll_list))
		list_add_tail(&msta->poll_list, &dev->sta_poll_list);
	spin_unlock_bh(&dev->sta_poll_lock);

	अगर (mt7615_mac_add_txs_skb(dev, msta, pid, txs_data))
		जाओ out;

	अगर (wcidx >= MT7615_WTBL_STA || !sta)
		जाओ out;

	अगर (wcid->ext_phy && dev->mt76.phy2)
		mphy = dev->mt76.phy2;

	अगर (mt7615_fill_txs(dev, msta, &info, txs_data))
		ieee80211_tx_status_noskb(mphy->hw, sta, &info);

out:
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम
mt7615_mac_tx_मुक्त_token(काष्ठा mt7615_dev *dev, u16 token)
अणु
	काष्ठा mt76_dev *mdev = &dev->mt76;
	काष्ठा mt76_txwi_cache *txwi;
	__le32 *txwi_data;
	u32 val;
	u8 wcid;

	trace_mac_tx_मुक्त(dev, token);
	txwi = mt76_token_put(mdev, token);
	अगर (!txwi)
		वापस;

	txwi_data = (__le32 *)mt76_get_txwi_ptr(mdev, txwi);
	val = le32_to_cpu(txwi_data[1]);
	wcid = FIELD_GET(MT_TXD1_WLAN_IDX, val);

	mt7615_txp_skb_unmap(mdev, txwi);
	अगर (txwi->skb) अणु
		mt76_tx_complete_skb(mdev, wcid, txwi->skb);
		txwi->skb = शून्य;
	पूर्ण

	mt76_put_txwi(mdev, txwi);
पूर्ण

अटल व्योम mt7615_mac_tx_मुक्त(काष्ठा mt7615_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7615_tx_मुक्त *मुक्त = (काष्ठा mt7615_tx_मुक्त *)skb->data;
	u8 i, count;

	mt76_queue_tx_cleanup(dev, dev->mphy.q_tx[MT_TXQ_PSD], false);
	अगर (is_mt7615(&dev->mt76)) अणु
		mt76_queue_tx_cleanup(dev, dev->mphy.q_tx[MT_TXQ_BE], false);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < IEEE80211_NUM_ACS; i++)
			mt76_queue_tx_cleanup(dev, dev->mphy.q_tx[i], false);
	पूर्ण

	count = FIELD_GET(MT_TX_FREE_MSDU_ID_CNT, le16_to_cpu(मुक्त->ctrl));
	अगर (is_mt7615(&dev->mt76)) अणु
		__le16 *token = &मुक्त->token[0];

		क्रम (i = 0; i < count; i++)
			mt7615_mac_tx_मुक्त_token(dev, le16_to_cpu(token[i]));
	पूर्ण अन्यथा अणु
		__le32 *token = (__le32 *)&मुक्त->token[0];

		क्रम (i = 0; i < count; i++)
			mt7615_mac_tx_मुक्त_token(dev, le32_to_cpu(token[i]));
	पूर्ण

	dev_kमुक्त_skb(skb);

	rcu_पढ़ो_lock();
	mt7615_mac_sta_poll(dev);
	rcu_पढ़ो_unlock();

	mt76_worker_schedule(&dev->mt76.tx_worker);
पूर्ण

व्योम mt7615_queue_rx_skb(काष्ठा mt76_dev *mdev, क्रमागत mt76_rxq_id q,
			 काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7615_dev *dev = container_of(mdev, काष्ठा mt7615_dev, mt76);
	__le32 *rxd = (__le32 *)skb->data;
	__le32 *end = (__le32 *)&skb->data[skb->len];
	क्रमागत rx_pkt_type type;
	u16 flag;

	type = FIELD_GET(MT_RXD0_PKT_TYPE, le32_to_cpu(rxd[0]));
	flag = FIELD_GET(MT_RXD0_PKT_FLAG, le32_to_cpu(rxd[0]));
	अगर (type == PKT_TYPE_RX_EVENT && flag == 0x1)
		type = PKT_TYPE_NORMAL_MCU;

	चयन (type) अणु
	हाल PKT_TYPE_TXS:
		क्रम (rxd++; rxd + 7 <= end; rxd += 7)
			mt7615_mac_add_txs(dev, rxd);
		dev_kमुक्त_skb(skb);
		अवरोध;
	हाल PKT_TYPE_TXRX_NOTIFY:
		mt7615_mac_tx_मुक्त(dev, skb);
		अवरोध;
	हाल PKT_TYPE_RX_EVENT:
		mt7615_mcu_rx_event(dev, skb);
		अवरोध;
	हाल PKT_TYPE_NORMAL_MCU:
	हाल PKT_TYPE_NORMAL:
		अगर (!mt7615_mac_fill_rx(dev, skb)) अणु
			mt76_rx(&dev->mt76, q, skb);
			वापस;
		पूर्ण
		fallthrough;
	शेष:
		dev_kमुक्त_skb(skb);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_queue_rx_skb);

अटल व्योम
mt7615_mac_set_sensitivity(काष्ठा mt7615_phy *phy, पूर्णांक val, bool ofdm)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;
	bool ext_phy = phy != &dev->phy;

	अगर (is_mt7663(&dev->mt76)) अणु
		अगर (ofdm)
			mt76_rmw(dev, MT7663_WF_PHY_MIN_PRI_PWR(ext_phy),
				 MT_WF_PHY_PD_OFDM_MASK(0),
				 MT_WF_PHY_PD_OFDM(0, val));
		अन्यथा
			mt76_rmw(dev, MT7663_WF_PHY_RXTD_CCK_PD(ext_phy),
				 MT_WF_PHY_PD_CCK_MASK(ext_phy),
				 MT_WF_PHY_PD_CCK(ext_phy, val));
		वापस;
	पूर्ण

	अगर (ofdm)
		mt76_rmw(dev, MT_WF_PHY_MIN_PRI_PWR(ext_phy),
			 MT_WF_PHY_PD_OFDM_MASK(ext_phy),
			 MT_WF_PHY_PD_OFDM(ext_phy, val));
	अन्यथा
		mt76_rmw(dev, MT_WF_PHY_RXTD_CCK_PD(ext_phy),
			 MT_WF_PHY_PD_CCK_MASK(ext_phy),
			 MT_WF_PHY_PD_CCK(ext_phy, val));
पूर्ण

अटल व्योम
mt7615_mac_set_शेष_sensitivity(काष्ठा mt7615_phy *phy)
अणु
	/* ofdm */
	mt7615_mac_set_sensitivity(phy, 0x13c, true);
	/* cck */
	mt7615_mac_set_sensitivity(phy, 0x92, false);

	phy->ofdm_sensitivity = -98;
	phy->cck_sensitivity = -110;
	phy->last_cca_adj = jअगरfies;
पूर्ण

व्योम mt7615_mac_set_scs(काष्ठा mt7615_phy *phy, bool enable)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;
	bool ext_phy = phy != &dev->phy;
	u32 reg, mask;

	mt7615_mutex_acquire(dev);

	अगर (phy->scs_en == enable)
		जाओ out;

	अगर (is_mt7663(&dev->mt76)) अणु
		reg = MT7663_WF_PHY_MIN_PRI_PWR(ext_phy);
		mask = MT_WF_PHY_PD_BLK(0);
	पूर्ण अन्यथा अणु
		reg = MT_WF_PHY_MIN_PRI_PWR(ext_phy);
		mask = MT_WF_PHY_PD_BLK(ext_phy);
	पूर्ण

	अगर (enable) अणु
		mt76_set(dev, reg, mask);
		अगर (is_mt7622(&dev->mt76)) अणु
			mt76_set(dev, MT_MIB_M0_MISC_CR(0), 0x7 << 8);
			mt76_set(dev, MT_MIB_M0_MISC_CR(0), 0x7);
		पूर्ण
	पूर्ण अन्यथा अणु
		mt76_clear(dev, reg, mask);
	पूर्ण

	mt7615_mac_set_शेष_sensitivity(phy);
	phy->scs_en = enable;

out:
	mt7615_mutex_release(dev);
पूर्ण

व्योम mt7615_mac_enable_nf(काष्ठा mt7615_dev *dev, bool ext_phy)
अणु
	u32 rxtd, reg;

	अगर (is_mt7663(&dev->mt76))
		reg = MT7663_WF_PHY_R0_PHYMUX_5;
	अन्यथा
		reg = MT_WF_PHY_R0_PHYMUX_5(ext_phy);

	अगर (ext_phy)
		rxtd = MT_WF_PHY_RXTD2(10);
	अन्यथा
		rxtd = MT_WF_PHY_RXTD(12);

	mt76_set(dev, rxtd, BIT(18) | BIT(29));
	mt76_set(dev, reg, 0x5 << 12);
पूर्ण

व्योम mt7615_mac_cca_stats_reset(काष्ठा mt7615_phy *phy)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;
	bool ext_phy = phy != &dev->phy;
	u32 reg;

	अगर (is_mt7663(&dev->mt76))
		reg = MT7663_WF_PHY_R0_PHYMUX_5;
	अन्यथा
		reg = MT_WF_PHY_R0_PHYMUX_5(ext_phy);

	/* reset PD and MDRDY counters */
	mt76_clear(dev, reg, GENMASK(22, 20));
	mt76_set(dev, reg, BIT(22) | BIT(20));
पूर्ण

अटल व्योम
mt7615_mac_adjust_sensitivity(काष्ठा mt7615_phy *phy,
			      u32 rts_err_rate, bool ofdm)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;
	पूर्णांक false_cca = ofdm ? phy->false_cca_ofdm : phy->false_cca_cck;
	bool ext_phy = phy != &dev->phy;
	u16 def_th = ofdm ? -98 : -110;
	bool update = false;
	s8 *sensitivity;
	पूर्णांक संकेत;

	sensitivity = ofdm ? &phy->ofdm_sensitivity : &phy->cck_sensitivity;
	संकेत = mt76_get_min_avg_rssi(&dev->mt76, ext_phy);
	अगर (!संकेत) अणु
		mt7615_mac_set_शेष_sensitivity(phy);
		वापस;
	पूर्ण

	संकेत = min(संकेत, -72);
	अगर (false_cca > 500) अणु
		अगर (rts_err_rate > MT_FRAC(40, 100))
			वापस;

		/* decrease coverage */
		अगर (*sensitivity == def_th && संकेत > -90) अणु
			*sensitivity = -90;
			update = true;
		पूर्ण अन्यथा अगर (*sensitivity + 2 < संकेत) अणु
			*sensitivity += 2;
			update = true;
		पूर्ण
	पूर्ण अन्यथा अगर ((false_cca > 0 && false_cca < 50) ||
		   rts_err_rate > MT_FRAC(60, 100)) अणु
		/* increase coverage */
		अगर (*sensitivity - 2 >= def_th) अणु
			*sensitivity -= 2;
			update = true;
		पूर्ण
	पूर्ण

	अगर (*sensitivity > संकेत) अणु
		*sensitivity = संकेत;
		update = true;
	पूर्ण

	अगर (update) अणु
		u16 val = ofdm ? *sensitivity * 2 + 512 : *sensitivity + 256;

		mt7615_mac_set_sensitivity(phy, val, ofdm);
		phy->last_cca_adj = jअगरfies;
	पूर्ण
पूर्ण

अटल व्योम
mt7615_mac_scs_check(काष्ठा mt7615_phy *phy)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;
	काष्ठा mib_stats *mib = &phy->mib;
	u32 val, rts_err_rate = 0;
	u32 mdrdy_cck, mdrdy_ofdm, pd_cck, pd_ofdm;
	bool ext_phy = phy != &dev->phy;

	अगर (!phy->scs_en)
		वापस;

	अगर (is_mt7663(&dev->mt76))
		val = mt76_rr(dev, MT7663_WF_PHY_R0_PHYCTRL_STS0(ext_phy));
	अन्यथा
		val = mt76_rr(dev, MT_WF_PHY_R0_PHYCTRL_STS0(ext_phy));
	pd_cck = FIELD_GET(MT_WF_PHYCTRL_STAT_PD_CCK, val);
	pd_ofdm = FIELD_GET(MT_WF_PHYCTRL_STAT_PD_OFDM, val);

	अगर (is_mt7663(&dev->mt76))
		val = mt76_rr(dev, MT7663_WF_PHY_R0_PHYCTRL_STS5(ext_phy));
	अन्यथा
		val = mt76_rr(dev, MT_WF_PHY_R0_PHYCTRL_STS5(ext_phy));
	mdrdy_cck = FIELD_GET(MT_WF_PHYCTRL_STAT_MDRDY_CCK, val);
	mdrdy_ofdm = FIELD_GET(MT_WF_PHYCTRL_STAT_MDRDY_OFDM, val);

	phy->false_cca_ofdm = pd_ofdm - mdrdy_ofdm;
	phy->false_cca_cck = pd_cck - mdrdy_cck;
	mt7615_mac_cca_stats_reset(phy);

	अगर (mib->rts_cnt + mib->rts_retries_cnt)
		rts_err_rate = MT_FRAC(mib->rts_retries_cnt,
				       mib->rts_cnt + mib->rts_retries_cnt);

	/* cck */
	mt7615_mac_adjust_sensitivity(phy, rts_err_rate, false);
	/* ofdm */
	mt7615_mac_adjust_sensitivity(phy, rts_err_rate, true);

	अगर (समय_after(jअगरfies, phy->last_cca_adj + 10 * HZ))
		mt7615_mac_set_शेष_sensitivity(phy);
पूर्ण

अटल u8
mt7615_phy_get_nf(काष्ठा mt7615_dev *dev, पूर्णांक idx)
अणु
	अटल स्थिर u8 nf_घातer[] = अणु 92, 89, 86, 83, 80, 75, 70, 65, 60, 55, 52 पूर्ण;
	u32 reg, val, sum = 0, n = 0;
	पूर्णांक i;

	अगर (is_mt7663(&dev->mt76))
		reg = MT7663_WF_PHY_RXTD(20);
	अन्यथा
		reg = idx ? MT_WF_PHY_RXTD2(17) : MT_WF_PHY_RXTD(20);

	क्रम (i = 0; i < ARRAY_SIZE(nf_घातer); i++, reg += 4) अणु
		val = mt76_rr(dev, reg);
		sum += val * nf_घातer[i];
		n += val;
	पूर्ण

	अगर (!n)
		वापस 0;

	वापस sum / n;
पूर्ण

अटल व्योम
mt7615_phy_update_channel(काष्ठा mt76_phy *mphy, पूर्णांक idx)
अणु
	काष्ठा mt7615_dev *dev = container_of(mphy->dev, काष्ठा mt7615_dev, mt76);
	काष्ठा mt7615_phy *phy = mphy->priv;
	काष्ठा mt76_channel_state *state;
	u64 busy_समय, tx_समय, rx_समय, obss_समय;
	u32 obss_reg = idx ? MT_WF_RMAC_MIB_TIME6 : MT_WF_RMAC_MIB_TIME5;
	पूर्णांक nf;

	busy_समय = mt76_get_field(dev, MT_MIB_SDR9(idx),
				   MT_MIB_SDR9_BUSY_MASK);
	tx_समय = mt76_get_field(dev, MT_MIB_SDR36(idx),
				 MT_MIB_SDR36_TXTIME_MASK);
	rx_समय = mt76_get_field(dev, MT_MIB_SDR37(idx),
				 MT_MIB_SDR37_RXTIME_MASK);
	obss_समय = mt76_get_field(dev, obss_reg, MT_MIB_OBSSTIME_MASK);

	nf = mt7615_phy_get_nf(dev, idx);
	अगर (!phy->noise)
		phy->noise = nf << 4;
	अन्यथा अगर (nf)
		phy->noise += nf - (phy->noise >> 4);

	state = mphy->chan_state;
	state->cc_busy += busy_समय;
	state->cc_tx += tx_समय;
	state->cc_rx += rx_समय + obss_समय;
	state->cc_bss_rx += rx_समय;
	state->noise = -(phy->noise >> 4);
पूर्ण

अटल व्योम __mt7615_update_channel(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा mt76_dev *mdev = &dev->mt76;

	mt7615_phy_update_channel(&mdev->phy, 0);
	अगर (mdev->phy2)
		mt7615_phy_update_channel(mdev->phy2, 1);

	/* reset obss airसमय */
	mt76_set(dev, MT_WF_RMAC_MIB_TIME0, MT_WF_RMAC_MIB_RXTIME_CLR);
पूर्ण

व्योम mt7615_update_channel(काष्ठा mt76_dev *mdev)
अणु
	काष्ठा mt7615_dev *dev = container_of(mdev, काष्ठा mt7615_dev, mt76);

	अगर (mt76_connac_pm_wake(&dev->mphy, &dev->pm))
		वापस;

	__mt7615_update_channel(dev);
	mt76_connac_घातer_save_sched(&dev->mphy, &dev->pm);
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_update_channel);

अटल व्योम mt7615_update_survey(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा mt76_dev *mdev = &dev->mt76;
	kसमय_प्रकार cur_समय;

	__mt7615_update_channel(dev);
	cur_समय = kसमय_get_bootसमय();

	mt76_update_survey_active_समय(&mdev->phy, cur_समय);
	अगर (mdev->phy2)
		mt76_update_survey_active_समय(mdev->phy2, cur_समय);
पूर्ण

अटल व्योम
mt7615_mac_update_mib_stats(काष्ठा mt7615_phy *phy)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;
	काष्ठा mib_stats *mib = &phy->mib;
	bool ext_phy = phy != &dev->phy;
	पूर्णांक i, aggr;
	u32 val, val2;

	mib->fcs_err_cnt += mt76_get_field(dev, MT_MIB_SDR3(ext_phy),
					   MT_MIB_SDR3_FCS_ERR_MASK);

	val = mt76_get_field(dev, MT_MIB_SDR14(ext_phy),
			     MT_MIB_AMPDU_MPDU_COUNT);
	अगर (val) अणु
		val2 = mt76_get_field(dev, MT_MIB_SDR15(ext_phy),
				      MT_MIB_AMPDU_ACK_COUNT);
		mib->aggr_per = 1000 * (val - val2) / val;
	पूर्ण

	aggr = ext_phy ? ARRAY_SIZE(dev->mt76.aggr_stats) / 2 : 0;
	क्रम (i = 0; i < 4; i++) अणु
		val = mt76_rr(dev, MT_MIB_MB_SDR1(ext_phy, i));
		mib->ba_miss_cnt += FIELD_GET(MT_MIB_BA_MISS_COUNT_MASK, val);
		mib->ack_fail_cnt += FIELD_GET(MT_MIB_ACK_FAIL_COUNT_MASK,
					       val);

		val = mt76_rr(dev, MT_MIB_MB_SDR0(ext_phy, i));
		mib->rts_cnt += FIELD_GET(MT_MIB_RTS_COUNT_MASK, val);
		mib->rts_retries_cnt += FIELD_GET(MT_MIB_RTS_RETRIES_COUNT_MASK,
						  val);

		val = mt76_rr(dev, MT_TX_AGG_CNT(ext_phy, i));
		dev->mt76.aggr_stats[aggr++] += val & 0xffff;
		dev->mt76.aggr_stats[aggr++] += val >> 16;
	पूर्ण
पूर्ण

व्योम mt7615_pm_wake_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7615_dev *dev;
	काष्ठा mt76_phy *mphy;

	dev = (काष्ठा mt7615_dev *)container_of(work, काष्ठा mt7615_dev,
						pm.wake_work);
	mphy = dev->phy.mt76;

	अगर (!mt7615_mcu_set_drv_ctrl(dev)) अणु
		पूर्णांक i;

		mt76_क्रम_each_q_rx(&dev->mt76, i)
			napi_schedule(&dev->mt76.napi[i]);
		mt76_connac_pm_dequeue_skbs(mphy, &dev->pm);
		mt76_queue_tx_cleanup(dev, dev->mt76.q_mcu[MT_MCUQ_WM], false);
		अगर (test_bit(MT76_STATE_RUNNING, &mphy->state))
			ieee80211_queue_delayed_work(mphy->hw, &mphy->mac_work,
						     MT7615_WATCHDOG_TIME);
	पूर्ण

	ieee80211_wake_queues(mphy->hw);
	wake_up(&dev->pm.रुको);
पूर्ण

व्योम mt7615_pm_घातer_save_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7615_dev *dev;
	अचिन्हित दीर्घ delta;

	dev = (काष्ठा mt7615_dev *)container_of(work, काष्ठा mt7615_dev,
						pm.ps_work.work);

	delta = dev->pm.idle_समयout;
	अगर (test_bit(MT76_HW_SCANNING, &dev->mphy.state) ||
	    test_bit(MT76_HW_SCHED_SCANNING, &dev->mphy.state))
		जाओ out;

	अगर (समय_is_after_jअगरfies(dev->pm.last_activity + delta)) अणु
		delta = dev->pm.last_activity + delta - jअगरfies;
		जाओ out;
	पूर्ण

	अगर (!mt7615_mcu_set_fw_ctrl(dev))
		वापस;
out:
	queue_delayed_work(dev->mt76.wq, &dev->pm.ps_work, delta);
पूर्ण

व्योम mt7615_mac_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7615_phy *phy;
	काष्ठा mt76_phy *mphy;

	mphy = (काष्ठा mt76_phy *)container_of(work, काष्ठा mt76_phy,
					       mac_work.work);
	phy = mphy->priv;

	mt7615_mutex_acquire(phy->dev);

	mt7615_update_survey(phy->dev);
	अगर (++mphy->mac_work_count == 5) अणु
		mphy->mac_work_count = 0;

		mt7615_mac_update_mib_stats(phy);
		mt7615_mac_scs_check(phy);
	पूर्ण

	mt7615_mutex_release(phy->dev);

	mt76_tx_status_check(mphy->dev, शून्य, false);
	ieee80211_queue_delayed_work(mphy->hw, &mphy->mac_work,
				     MT7615_WATCHDOG_TIME);
पूर्ण

व्योम mt7615_tx_token_put(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा mt76_txwi_cache *txwi;
	पूर्णांक id;

	spin_lock_bh(&dev->mt76.token_lock);
	idr_क्रम_each_entry(&dev->mt76.token, txwi, id) अणु
		mt7615_txp_skb_unmap(&dev->mt76, txwi);
		अगर (txwi->skb) अणु
			काष्ठा ieee80211_hw *hw;

			hw = mt76_tx_status_get_hw(&dev->mt76, txwi->skb);
			ieee80211_मुक्त_txskb(hw, txwi->skb);
		पूर्ण
		mt76_put_txwi(&dev->mt76, txwi);
	पूर्ण
	spin_unlock_bh(&dev->mt76.token_lock);
	idr_destroy(&dev->mt76.token);
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_tx_token_put);

अटल व्योम mt7615_dfs_stop_radar_detector(काष्ठा mt7615_phy *phy)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;

	अगर (phy->rdd_state & BIT(0))
		mt7615_mcu_rdd_cmd(dev, RDD_STOP, 0, MT_RX_SEL0, 0);
	अगर (phy->rdd_state & BIT(1))
		mt7615_mcu_rdd_cmd(dev, RDD_STOP, 1, MT_RX_SEL0, 0);
पूर्ण

अटल पूर्णांक mt7615_dfs_start_rdd(काष्ठा mt7615_dev *dev, पूर्णांक chain)
अणु
	पूर्णांक err;

	err = mt7615_mcu_rdd_cmd(dev, RDD_START, chain, MT_RX_SEL0, 0);
	अगर (err < 0)
		वापस err;

	वापस mt7615_mcu_rdd_cmd(dev, RDD_DET_MODE, chain,
				  MT_RX_SEL0, 1);
पूर्ण

अटल पूर्णांक mt7615_dfs_start_radar_detector(काष्ठा mt7615_phy *phy)
अणु
	काष्ठा cfg80211_chan_def *chandef = &phy->mt76->chandef;
	काष्ठा mt7615_dev *dev = phy->dev;
	bool ext_phy = phy != &dev->phy;
	पूर्णांक err;

	/* start CAC */
	err = mt7615_mcu_rdd_cmd(dev, RDD_CAC_START, ext_phy, MT_RX_SEL0, 0);
	अगर (err < 0)
		वापस err;

	err = mt7615_dfs_start_rdd(dev, ext_phy);
	अगर (err < 0)
		वापस err;

	phy->rdd_state |= BIT(ext_phy);

	अगर (chandef->width == NL80211_CHAN_WIDTH_160 ||
	    chandef->width == NL80211_CHAN_WIDTH_80P80) अणु
		err = mt7615_dfs_start_rdd(dev, 1);
		अगर (err < 0)
			वापस err;

		phy->rdd_state |= BIT(1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7615_dfs_init_radar_specs(काष्ठा mt7615_phy *phy)
अणु
	स्थिर काष्ठा mt7615_dfs_radar_spec *radar_specs;
	काष्ठा mt7615_dev *dev = phy->dev;
	पूर्णांक err, i;

	चयन (dev->mt76.region) अणु
	हाल NL80211_DFS_FCC:
		radar_specs = &fcc_radar_specs;
		err = mt7615_mcu_set_fcc5_lpn(dev, 8);
		अगर (err < 0)
			वापस err;
		अवरोध;
	हाल NL80211_DFS_ETSI:
		radar_specs = &etsi_radar_specs;
		अवरोध;
	हाल NL80211_DFS_JP:
		radar_specs = &jp_radar_specs;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(radar_specs->radar_pattern); i++) अणु
		err = mt7615_mcu_set_radar_th(dev, i,
					      &radar_specs->radar_pattern[i]);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस mt7615_mcu_set_pulse_th(dev, &radar_specs->pulse_th);
पूर्ण

पूर्णांक mt7615_dfs_init_radar_detector(काष्ठा mt7615_phy *phy)
अणु
	काष्ठा cfg80211_chan_def *chandef = &phy->mt76->chandef;
	काष्ठा mt7615_dev *dev = phy->dev;
	bool ext_phy = phy != &dev->phy;
	पूर्णांक err;

	अगर (is_mt7663(&dev->mt76))
		वापस 0;

	अगर (dev->mt76.region == NL80211_DFS_UNSET) अणु
		phy->dfs_state = -1;
		अगर (phy->rdd_state)
			जाओ stop;

		वापस 0;
	पूर्ण

	अगर (test_bit(MT76_SCANNING, &phy->mt76->state))
		वापस 0;

	अगर (phy->dfs_state == chandef->chan->dfs_state)
		वापस 0;

	err = mt7615_dfs_init_radar_specs(phy);
	अगर (err < 0) अणु
		phy->dfs_state = -1;
		जाओ stop;
	पूर्ण

	phy->dfs_state = chandef->chan->dfs_state;

	अगर (chandef->chan->flags & IEEE80211_CHAN_RADAR) अणु
		अगर (chandef->chan->dfs_state != NL80211_DFS_AVAILABLE)
			वापस mt7615_dfs_start_radar_detector(phy);

		वापस mt7615_mcu_rdd_cmd(dev, RDD_CAC_END, ext_phy,
					  MT_RX_SEL0, 0);
	पूर्ण

stop:
	err = mt7615_mcu_rdd_cmd(dev, RDD_NORMAL_START, ext_phy, MT_RX_SEL0, 0);
	अगर (err < 0)
		वापस err;

	mt7615_dfs_stop_radar_detector(phy);
	वापस 0;
पूर्ण

पूर्णांक mt7615_mac_set_beacon_filter(काष्ठा mt7615_phy *phy,
				 काष्ठा ieee80211_vअगर *vअगर,
				 bool enable)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;
	bool ext_phy = phy != &dev->phy;
	पूर्णांक err;

	अगर (!mt7615_firmware_offload(dev))
		वापस -EOPNOTSUPP;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_MONITOR:
		वापस 0;
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_AP:
		अगर (enable)
			phy->n_beacon_vअगर++;
		अन्यथा
			phy->n_beacon_vअगर--;
		fallthrough;
	शेष:
		अवरोध;
	पूर्ण

	err = mt7615_mcu_set_bss_pm(dev, vअगर, !phy->n_beacon_vअगर);
	अगर (err)
		वापस err;

	अगर (phy->n_beacon_vअगर) अणु
		vअगर->driver_flags &= ~IEEE80211_VIF_BEACON_FILTER;
		mt76_clear(dev, MT_WF_RFCR(ext_phy),
			   MT_WF_RFCR_DROP_OTHER_BEACON);
	पूर्ण अन्यथा अणु
		vअगर->driver_flags |= IEEE80211_VIF_BEACON_FILTER;
		mt76_set(dev, MT_WF_RFCR(ext_phy),
			 MT_WF_RFCR_DROP_OTHER_BEACON);
	पूर्ण

	वापस 0;
पूर्ण

व्योम mt7615_coredump_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7615_dev *dev;
	अक्षर *dump, *data;

	dev = (काष्ठा mt7615_dev *)container_of(work, काष्ठा mt7615_dev,
						coredump.work.work);

	अगर (समय_is_after_jअगरfies(dev->coredump.last_activity +
				  4 * MT76_CONNAC_COREDUMP_TIMEOUT)) अणु
		queue_delayed_work(dev->mt76.wq, &dev->coredump.work,
				   MT76_CONNAC_COREDUMP_TIMEOUT);
		वापस;
	पूर्ण

	dump = vzalloc(MT76_CONNAC_COREDUMP_SZ);
	data = dump;

	जबतक (true) अणु
		काष्ठा sk_buff *skb;

		spin_lock_bh(&dev->mt76.lock);
		skb = __skb_dequeue(&dev->coredump.msg_list);
		spin_unlock_bh(&dev->mt76.lock);

		अगर (!skb)
			अवरोध;

		skb_pull(skb, माप(काष्ठा mt7615_mcu_rxd));
		अगर (data + skb->len - dump > MT76_CONNAC_COREDUMP_SZ) अणु
			dev_kमुक्त_skb(skb);
			जारी;
		पूर्ण

		स_नकल(data, skb->data, skb->len);
		data += skb->len;

		dev_kमुक्त_skb(skb);
	पूर्ण
	dev_coredumpv(dev->mt76.dev, dump, MT76_CONNAC_COREDUMP_SZ,
		      GFP_KERNEL);
पूर्ण
