<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc. */

#समावेश <linux/etherdevice.h>
#समावेश <linux/समयkeeping.h>
#समावेश "mt7915.h"
#समावेश "../dma.h"
#समावेश "mac.h"

#घोषणा to_rssi(field, rxv)	((FIELD_GET(field, rxv) - 220) / 2)

#घोषणा HE_BITS(f)		cpu_to_le16(IEEE80211_RADIOTAP_HE_##f)
#घोषणा HE_PREP(f, m, v)	le16_encode_bits(le32_get_bits(v, MT_CRXV_HE_##m),\
						 IEEE80211_RADIOTAP_HE_##f)

अटल स्थिर काष्ठा mt7915_dfs_radar_spec etsi_radar_specs = अणु
	.pulse_th = अणु 110, -10, -80, 40, 5200, 128, 5200 पूर्ण,
	.radar_pattern = अणु
		[5] =  अणु 1, 0,  6, 32, 28, 0,  990, 5010, 17, 1, 1 पूर्ण,
		[6] =  अणु 1, 0,  9, 32, 28, 0,  615, 5010, 27, 1, 1 पूर्ण,
		[7] =  अणु 1, 0, 15, 32, 28, 0,  240,  445, 27, 1, 1 पूर्ण,
		[8] =  अणु 1, 0, 12, 32, 28, 0,  240,  510, 42, 1, 1 पूर्ण,
		[9] =  अणु 1, 1,  0,  0,  0, 0, 2490, 3343, 14, 0, 0, 12, 32, 28, अणु पूर्ण, 126 पूर्ण,
		[10] = अणु 1, 1,  0,  0,  0, 0, 2490, 3343, 14, 0, 0, 15, 32, 24, अणु पूर्ण, 126 पूर्ण,
		[11] = अणु 1, 1,  0,  0,  0, 0,  823, 2510, 14, 0, 0, 18, 32, 28, अणु पूर्ण,  54 पूर्ण,
		[12] = अणु 1, 1,  0,  0,  0, 0,  823, 2510, 14, 0, 0, 27, 32, 24, अणु पूर्ण,  54 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mt7915_dfs_radar_spec fcc_radar_specs = अणु
	.pulse_th = अणु 110, -10, -80, 40, 5200, 128, 5200 पूर्ण,
	.radar_pattern = अणु
		[0] = अणु 1, 0,  8,  32, 28, 0, 508, 3076, 13, 1,  1 पूर्ण,
		[1] = अणु 1, 0, 12,  32, 28, 0, 140,  240, 17, 1,  1 पूर्ण,
		[2] = अणु 1, 0,  8,  32, 28, 0, 190,  510, 22, 1,  1 पूर्ण,
		[3] = अणु 1, 0,  6,  32, 28, 0, 190,  510, 32, 1,  1 पूर्ण,
		[4] = अणु 1, 0,  9, 255, 28, 0, 323,  343, 13, 1, 32 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mt7915_dfs_radar_spec jp_radar_specs = अणु
	.pulse_th = अणु 110, -10, -80, 40, 5200, 128, 5200 पूर्ण,
	.radar_pattern = अणु
		[0] =  अणु 1, 0,  8,  32, 28, 0,  508, 3076,  13, 1,  1 पूर्ण,
		[1] =  अणु 1, 0, 12,  32, 28, 0,  140,  240,  17, 1,  1 पूर्ण,
		[2] =  अणु 1, 0,  8,  32, 28, 0,  190,  510,  22, 1,  1 पूर्ण,
		[3] =  अणु 1, 0,  6,  32, 28, 0,  190,  510,  32, 1,  1 पूर्ण,
		[4] =  अणु 1, 0,  9, 255, 28, 0,  323,  343,  13, 1, 32 पूर्ण,
		[13] = अणु 1, 0,  7,  32, 28, 0, 3836, 3856,  14, 1,  1 पूर्ण,
		[14] = अणु 1, 0,  6,  32, 28, 0,  615, 5010, 110, 1,  1 पूर्ण,
		[15] = अणु 1, 1,  0,   0,  0, 0,   15, 5010, 110, 0,  0, 12, 32, 28 पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा mt76_wcid *mt7915_rx_get_wcid(काष्ठा mt7915_dev *dev,
					    u16 idx, bool unicast)
अणु
	काष्ठा mt7915_sta *sta;
	काष्ठा mt76_wcid *wcid;

	अगर (idx >= ARRAY_SIZE(dev->mt76.wcid))
		वापस शून्य;

	wcid = rcu_dereference(dev->mt76.wcid[idx]);
	अगर (unicast || !wcid)
		वापस wcid;

	अगर (!wcid->sta)
		वापस शून्य;

	sta = container_of(wcid, काष्ठा mt7915_sta, wcid);
	अगर (!sta->vअगर)
		वापस शून्य;

	वापस &sta->vअगर->sta.wcid;
पूर्ण

व्योम mt7915_sta_ps(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_sta *sta, bool ps)
अणु
पूर्ण

bool mt7915_mac_wtbl_update(काष्ठा mt7915_dev *dev, पूर्णांक idx, u32 mask)
अणु
	mt76_rmw(dev, MT_WTBL_UPDATE, MT_WTBL_UPDATE_WLAN_IDX,
		 FIELD_PREP(MT_WTBL_UPDATE_WLAN_IDX, idx) | mask);

	वापस mt76_poll(dev, MT_WTBL_UPDATE, MT_WTBL_UPDATE_BUSY,
			 0, 5000);
पूर्ण

अटल u32 mt7915_mac_wtbl_lmac_addr(काष्ठा mt7915_dev *dev, u16 wcid)
अणु
	mt76_wr(dev, MT_WTBLON_TOP_WDUCR,
		FIELD_PREP(MT_WTBLON_TOP_WDUCR_GROUP, (wcid >> 7)));

	वापस MT_WTBL_LMAC_OFFS(wcid, 0);
पूर्ण

/* TODO: use txमुक्त airसमय info to aव्योम runसमय accessing in the दीर्घ run */
अटल व्योम mt7915_mac_sta_poll(काष्ठा mt7915_dev *dev)
अणु
	अटल स्थिर u8 ac_to_tid[] = अणु
		[IEEE80211_AC_BE] = 0,
		[IEEE80211_AC_BK] = 1,
		[IEEE80211_AC_VI] = 4,
		[IEEE80211_AC_VO] = 6
	पूर्ण;
	काष्ठा ieee80211_sta *sta;
	काष्ठा mt7915_sta *msta;
	u32 tx_समय[IEEE80211_NUM_ACS], rx_समय[IEEE80211_NUM_ACS];
	LIST_HEAD(sta_poll_list);
	पूर्णांक i;

	spin_lock_bh(&dev->sta_poll_lock);
	list_splice_init(&dev->sta_poll_list, &sta_poll_list);
	spin_unlock_bh(&dev->sta_poll_lock);

	rcu_पढ़ो_lock();

	जबतक (true) अणु
		bool clear = false;
		u32 addr;
		u16 idx;

		spin_lock_bh(&dev->sta_poll_lock);
		अगर (list_empty(&sta_poll_list)) अणु
			spin_unlock_bh(&dev->sta_poll_lock);
			अवरोध;
		पूर्ण
		msta = list_first_entry(&sta_poll_list,
					काष्ठा mt7915_sta, poll_list);
		list_del_init(&msta->poll_list);
		spin_unlock_bh(&dev->sta_poll_lock);

		idx = msta->wcid.idx;
		addr = mt7915_mac_wtbl_lmac_addr(dev, idx) + 20 * 4;

		क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
			u32 tx_last = msta->airसमय_ac[i];
			u32 rx_last = msta->airसमय_ac[i + 4];

			msta->airसमय_ac[i] = mt76_rr(dev, addr);
			msta->airसमय_ac[i + 4] = mt76_rr(dev, addr + 4);

			tx_समय[i] = msta->airसमय_ac[i] - tx_last;
			rx_समय[i] = msta->airसमय_ac[i + 4] - rx_last;

			अगर ((tx_last | rx_last) & BIT(30))
				clear = true;

			addr += 8;
		पूर्ण

		अगर (clear) अणु
			mt7915_mac_wtbl_update(dev, idx,
					       MT_WTBL_UPDATE_ADM_COUNT_CLEAR);
			स_रखो(msta->airसमय_ac, 0, माप(msta->airसमय_ac));
		पूर्ण

		अगर (!msta->wcid.sta)
			जारी;

		sta = container_of((व्योम *)msta, काष्ठा ieee80211_sta,
				   drv_priv);
		क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
			u8 q = mt7915_lmac_mapping(dev, i);
			u32 tx_cur = tx_समय[q];
			u32 rx_cur = rx_समय[q];
			u8 tid = ac_to_tid[i];

			अगर (!tx_cur && !rx_cur)
				जारी;

			ieee80211_sta_रेजिस्टर_airसमय(sta, tid, tx_cur,
						       rx_cur);
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम
mt7915_mac_decode_he_radiotap_ru(काष्ठा mt76_rx_status *status,
				 काष्ठा ieee80211_radiotap_he *he,
				 __le32 *rxv)
अणु
	u32 ru_h, ru_l;
	u8 ru, offs = 0;

	ru_l = FIELD_GET(MT_PRXV_HE_RU_ALLOC_L, le32_to_cpu(rxv[0]));
	ru_h = FIELD_GET(MT_PRXV_HE_RU_ALLOC_H, le32_to_cpu(rxv[1]));
	ru = (u8)(ru_l | ru_h << 4);

	status->bw = RATE_INFO_BW_HE_RU;

	चयन (ru) अणु
	हाल 0 ... 36:
		status->he_ru = NL80211_RATE_INFO_HE_RU_ALLOC_26;
		offs = ru;
		अवरोध;
	हाल 37 ... 52:
		status->he_ru = NL80211_RATE_INFO_HE_RU_ALLOC_52;
		offs = ru - 37;
		अवरोध;
	हाल 53 ... 60:
		status->he_ru = NL80211_RATE_INFO_HE_RU_ALLOC_106;
		offs = ru - 53;
		अवरोध;
	हाल 61 ... 64:
		status->he_ru = NL80211_RATE_INFO_HE_RU_ALLOC_242;
		offs = ru - 61;
		अवरोध;
	हाल 65 ... 66:
		status->he_ru = NL80211_RATE_INFO_HE_RU_ALLOC_484;
		offs = ru - 65;
		अवरोध;
	हाल 67:
		status->he_ru = NL80211_RATE_INFO_HE_RU_ALLOC_996;
		अवरोध;
	हाल 68:
		status->he_ru = NL80211_RATE_INFO_HE_RU_ALLOC_2x996;
		अवरोध;
	पूर्ण

	he->data1 |= HE_BITS(DATA1_BW_RU_ALLOC_KNOWN);
	he->data2 |= HE_BITS(DATA2_RU_OFFSET_KNOWN) |
		     le16_encode_bits(offs,
				      IEEE80211_RADIOTAP_HE_DATA2_RU_OFFSET);
पूर्ण

अटल व्योम
mt7915_mac_decode_he_radiotap(काष्ठा sk_buff *skb,
			      काष्ठा mt76_rx_status *status,
			      __le32 *rxv, u32 phy)
अणु
	/* TODO: काष्ठा ieee80211_radiotap_he_mu */
	अटल स्थिर काष्ठा ieee80211_radiotap_he known = अणु
		.data1 = HE_BITS(DATA1_DATA_MCS_KNOWN) |
			 HE_BITS(DATA1_DATA_DCM_KNOWN) |
			 HE_BITS(DATA1_STBC_KNOWN) |
			 HE_BITS(DATA1_CODING_KNOWN) |
			 HE_BITS(DATA1_LDPC_XSYMSEG_KNOWN) |
			 HE_BITS(DATA1_DOPPLER_KNOWN) |
			 HE_BITS(DATA1_BSS_COLOR_KNOWN),
		.data2 = HE_BITS(DATA2_GI_KNOWN) |
			 HE_BITS(DATA2_TXBF_KNOWN) |
			 HE_BITS(DATA2_PE_DISAMBIG_KNOWN) |
			 HE_BITS(DATA2_TXOP_KNOWN),
	पूर्ण;
	काष्ठा ieee80211_radiotap_he *he = शून्य;
	u32 ltf_size = le32_get_bits(rxv[2], MT_CRXV_HE_LTF_SIZE) + 1;

	he = skb_push(skb, माप(known));
	स_नकल(he, &known, माप(known));

	he->data3 = HE_PREP(DATA3_BSS_COLOR, BSS_COLOR, rxv[14]) |
		    HE_PREP(DATA3_LDPC_XSYMSEG, LDPC_EXT_SYM, rxv[2]);
	he->data5 = HE_PREP(DATA5_PE_DISAMBIG, PE_DISAMBIG, rxv[2]) |
		    le16_encode_bits(ltf_size,
				     IEEE80211_RADIOTAP_HE_DATA5_LTF_SIZE);
	he->data6 = HE_PREP(DATA6_TXOP, TXOP_DUR, rxv[14]) |
		    HE_PREP(DATA6_DOPPLER, DOPPLER, rxv[14]);

	चयन (phy) अणु
	हाल MT_PHY_TYPE_HE_SU:
		he->data1 |= HE_BITS(DATA1_FORMAT_SU) |
			     HE_BITS(DATA1_UL_DL_KNOWN) |
			     HE_BITS(DATA1_BEAM_CHANGE_KNOWN) |
			     HE_BITS(DATA1_SPTL_REUSE_KNOWN);

		he->data3 |= HE_PREP(DATA3_BEAM_CHANGE, BEAM_CHNG, rxv[14]) |
			     HE_PREP(DATA3_UL_DL, UPLINK, rxv[2]);
		he->data4 |= HE_PREP(DATA4_SU_MU_SPTL_REUSE, SR_MASK, rxv[11]);
		अवरोध;
	हाल MT_PHY_TYPE_HE_EXT_SU:
		he->data1 |= HE_BITS(DATA1_FORMAT_EXT_SU) |
			     HE_BITS(DATA1_UL_DL_KNOWN);

		he->data3 |= HE_PREP(DATA3_UL_DL, UPLINK, rxv[2]);
		अवरोध;
	हाल MT_PHY_TYPE_HE_MU:
		he->data1 |= HE_BITS(DATA1_FORMAT_MU) |
			     HE_BITS(DATA1_UL_DL_KNOWN) |
			     HE_BITS(DATA1_SPTL_REUSE_KNOWN);

		he->data3 |= HE_PREP(DATA3_UL_DL, UPLINK, rxv[2]);
		he->data4 |= HE_PREP(DATA4_SU_MU_SPTL_REUSE, SR_MASK, rxv[11]);

		mt7915_mac_decode_he_radiotap_ru(status, he, rxv);
		अवरोध;
	हाल MT_PHY_TYPE_HE_TB:
		he->data1 |= HE_BITS(DATA1_FORMAT_TRIG) |
			     HE_BITS(DATA1_SPTL_REUSE_KNOWN) |
			     HE_BITS(DATA1_SPTL_REUSE2_KNOWN) |
			     HE_BITS(DATA1_SPTL_REUSE3_KNOWN) |
			     HE_BITS(DATA1_SPTL_REUSE4_KNOWN);

		he->data4 |= HE_PREP(DATA4_TB_SPTL_REUSE1, SR_MASK, rxv[11]) |
			     HE_PREP(DATA4_TB_SPTL_REUSE2, SR1_MASK, rxv[11]) |
			     HE_PREP(DATA4_TB_SPTL_REUSE3, SR2_MASK, rxv[11]) |
			     HE_PREP(DATA4_TB_SPTL_REUSE4, SR3_MASK, rxv[11]);

		mt7915_mac_decode_he_radiotap_ru(status, he, rxv);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक mt7915_mac_fill_rx(काष्ठा mt7915_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt76_rx_status *status = (काष्ठा mt76_rx_status *)skb->cb;
	काष्ठा mt76_phy *mphy = &dev->mt76.phy;
	काष्ठा mt7915_phy *phy = &dev->phy;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_hdr *hdr;
	__le32 *rxd = (__le32 *)skb->data;
	__le32 *rxv = शून्य;
	u32 mode = 0;
	u32 rxd0 = le32_to_cpu(rxd[0]);
	u32 rxd1 = le32_to_cpu(rxd[1]);
	u32 rxd2 = le32_to_cpu(rxd[2]);
	u32 rxd3 = le32_to_cpu(rxd[3]);
	u32 rxd4 = le32_to_cpu(rxd[4]);
	u32 csum_mask = MT_RXD0_NORMAL_IP_SUM | MT_RXD0_NORMAL_UDP_TCP_SUM;
	bool unicast, insert_ccmp_hdr = false;
	u8 हटाओ_pad, amsdu_info;
	bool hdr_trans;
	u16 seq_ctrl = 0;
	u8 qos_ctl = 0;
	__le16 fc = 0;
	पूर्णांक i, idx;

	स_रखो(status, 0, माप(*status));

	अगर (rxd1 & MT_RXD1_NORMAL_BAND_IDX) अणु
		mphy = dev->mt76.phy2;
		अगर (!mphy)
			वापस -EINVAL;

		phy = mphy->priv;
		status->ext_phy = true;
	पूर्ण

	अगर (!test_bit(MT76_STATE_RUNNING, &mphy->state))
		वापस -EINVAL;

	अगर (rxd2 & MT_RXD2_NORMAL_AMSDU_ERR)
		वापस -EINVAL;

	unicast = FIELD_GET(MT_RXD3_NORMAL_ADDR_TYPE, rxd3) == MT_RXD3_NORMAL_U2M;
	idx = FIELD_GET(MT_RXD1_NORMAL_WLAN_IDX, rxd1);
	hdr_trans = rxd2 & MT_RXD2_NORMAL_HDR_TRANS;
	status->wcid = mt7915_rx_get_wcid(dev, idx, unicast);

	अगर (status->wcid) अणु
		काष्ठा mt7915_sta *msta;

		msta = container_of(status->wcid, काष्ठा mt7915_sta, wcid);
		spin_lock_bh(&dev->sta_poll_lock);
		अगर (list_empty(&msta->poll_list))
			list_add_tail(&msta->poll_list, &dev->sta_poll_list);
		spin_unlock_bh(&dev->sta_poll_lock);
	पूर्ण

	status->freq = mphy->chandef.chan->center_freq;
	status->band = mphy->chandef.chan->band;
	अगर (status->band == NL80211_BAND_5GHZ)
		sband = &mphy->sband_5g.sband;
	अन्यथा
		sband = &mphy->sband_2g.sband;

	अगर (!sband->channels)
		वापस -EINVAL;

	अगर ((rxd0 & csum_mask) == csum_mask)
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	अगर (rxd1 & MT_RXD1_NORMAL_FCS_ERR)
		status->flag |= RX_FLAG_FAILED_FCS_CRC;

	अगर (rxd1 & MT_RXD1_NORMAL_TKIP_MIC_ERR)
		status->flag |= RX_FLAG_MMIC_ERROR;

	अगर (FIELD_GET(MT_RXD1_NORMAL_SEC_MODE, rxd1) != 0 &&
	    !(rxd1 & (MT_RXD1_NORMAL_CLM | MT_RXD1_NORMAL_CM))) अणु
		status->flag |= RX_FLAG_DECRYPTED;
		status->flag |= RX_FLAG_IV_STRIPPED;
		status->flag |= RX_FLAG_MMIC_STRIPPED | RX_FLAG_MIC_STRIPPED;
	पूर्ण

	हटाओ_pad = FIELD_GET(MT_RXD2_NORMAL_HDR_OFFSET, rxd2);

	अगर (rxd2 & MT_RXD2_NORMAL_MAX_LEN_ERROR)
		वापस -EINVAL;

	rxd += 6;
	अगर (rxd1 & MT_RXD1_NORMAL_GROUP_4) अणु
		u32 v0 = le32_to_cpu(rxd[0]);
		u32 v2 = le32_to_cpu(rxd[2]);

		fc = cpu_to_le16(FIELD_GET(MT_RXD6_FRAME_CONTROL, v0));
		qos_ctl = FIELD_GET(MT_RXD8_QOS_CTL, v2);
		seq_ctrl = FIELD_GET(MT_RXD8_SEQ_CTRL, v2);

		rxd += 4;
		अगर ((u8 *)rxd - skb->data >= skb->len)
			वापस -EINVAL;
	पूर्ण

	अगर (rxd1 & MT_RXD1_NORMAL_GROUP_1) अणु
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

	अगर (rxd1 & MT_RXD1_NORMAL_GROUP_2) अणु
		status->बारtamp = le32_to_cpu(rxd[0]);
		status->flag |= RX_FLAG_MACTIME_START;

		अगर (!(rxd2 & MT_RXD2_NORMAL_NON_AMPDU)) अणु
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

	/* RXD Group 3 - P-RXV */
	अगर (rxd1 & MT_RXD1_NORMAL_GROUP_3) अणु
		u32 v0, v1, v2;

		rxv = rxd;
		rxd += 2;
		अगर ((u8 *)rxd - skb->data >= skb->len)
			वापस -EINVAL;

		v0 = le32_to_cpu(rxv[0]);
		v1 = le32_to_cpu(rxv[1]);
		v2 = le32_to_cpu(rxv[2]);

		अगर (v0 & MT_PRXV_HT_AD_CODE)
			status->enc_flags |= RX_ENC_FLAG_LDPC;

		status->chains = mphy->antenna_mask;
		status->chain_संकेत[0] = to_rssi(MT_PRXV_RCPI0, v1);
		status->chain_संकेत[1] = to_rssi(MT_PRXV_RCPI1, v1);
		status->chain_संकेत[2] = to_rssi(MT_PRXV_RCPI2, v1);
		status->chain_संकेत[3] = to_rssi(MT_PRXV_RCPI3, v1);
		status->संकेत = status->chain_संकेत[0];

		क्रम (i = 1; i < hweight8(mphy->antenna_mask); i++) अणु
			अगर (!(status->chains & BIT(i)))
				जारी;

			status->संकेत = max(status->संकेत,
					     status->chain_संकेत[i]);
		पूर्ण

		/* RXD Group 5 - C-RXV */
		अगर (rxd1 & MT_RXD1_NORMAL_GROUP_5) अणु
			u8 stbc = FIELD_GET(MT_CRXV_HT_STBC, v2);
			u8 gi = FIELD_GET(MT_CRXV_HT_SHORT_GI, v2);
			bool cck = false;

			rxd += 18;
			अगर ((u8 *)rxd - skb->data >= skb->len)
				वापस -EINVAL;

			idx = i = FIELD_GET(MT_PRXV_TX_RATE, v0);
			mode = FIELD_GET(MT_CRXV_TX_MODE, v2);

			चयन (mode) अणु
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
				status->nss =
					FIELD_GET(MT_PRXV_NSTS, v0) + 1;
				status->encoding = RX_ENC_VHT;
				अगर (i > 9)
					वापस -EINVAL;
				अवरोध;
			हाल MT_PHY_TYPE_HE_MU:
				status->flag |= RX_FLAG_RADIOTAP_HE_MU;
				fallthrough;
			हाल MT_PHY_TYPE_HE_SU:
			हाल MT_PHY_TYPE_HE_EXT_SU:
			हाल MT_PHY_TYPE_HE_TB:
				status->nss =
					FIELD_GET(MT_PRXV_NSTS, v0) + 1;
				status->encoding = RX_ENC_HE;
				status->flag |= RX_FLAG_RADIOTAP_HE;
				i &= GENMASK(3, 0);

				अगर (gi <= NL80211_RATE_INFO_HE_GI_3_2)
					status->he_gi = gi;

				status->he_dcm = !!(idx & MT_PRXV_TX_DCM);
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
			status->rate_idx = i;

			चयन (FIELD_GET(MT_CRXV_FRAME_MODE, v2)) अणु
			हाल IEEE80211_STA_RX_BW_20:
				अवरोध;
			हाल IEEE80211_STA_RX_BW_40:
				अगर (mode & MT_PHY_TYPE_HE_EXT_SU &&
				    (idx & MT_PRXV_TX_ER_SU_106T)) अणु
					status->bw = RATE_INFO_BW_HE_RU;
					status->he_ru =
						NL80211_RATE_INFO_HE_RU_ALLOC_106;
				पूर्ण अन्यथा अणु
					status->bw = RATE_INFO_BW_40;
				पूर्ण
				अवरोध;
			हाल IEEE80211_STA_RX_BW_80:
				status->bw = RATE_INFO_BW_80;
				अवरोध;
			हाल IEEE80211_STA_RX_BW_160:
				status->bw = RATE_INFO_BW_160;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण

			status->enc_flags |= RX_ENC_FLAG_STBC_MASK * stbc;
			अगर (mode < MT_PHY_TYPE_HE_SU && gi)
				status->enc_flags |= RX_ENC_FLAG_SHORT_GI;
		पूर्ण
	पूर्ण

	skb_pull(skb, (u8 *)rxd - skb->data + 2 * हटाओ_pad);

	amsdu_info = FIELD_GET(MT_RXD4_NORMAL_PAYLOAD_FORMAT, rxd4);
	status->amsdu = !!amsdu_info;
	अगर (status->amsdu) अणु
		status->first_amsdu = amsdu_info == MT_RXD4_FIRST_AMSDU_FRAME;
		status->last_amsdu = amsdu_info == MT_RXD4_LAST_AMSDU_FRAME;
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
		hdr = mt76_skb_get_hdr(skb);
		fc = hdr->frame_control;
		अगर (ieee80211_is_data_qos(fc)) अणु
			seq_ctrl = le16_to_cpu(hdr->seq_ctrl);
			qos_ctl = *ieee80211_get_qos_ctl(hdr);
		पूर्ण
	पूर्ण अन्यथा अणु
		status->flag &= ~(RX_FLAG_RADIOTAP_HE |
				  RX_FLAG_RADIOTAP_HE_MU);
		status->flag |= RX_FLAG_8023;
	पूर्ण

	अगर (rxv && status->flag & RX_FLAG_RADIOTAP_HE)
		mt7915_mac_decode_he_radiotap(skb, status, rxv, mode);

	अगर (!status->wcid || !ieee80211_is_data_qos(fc))
		वापस 0;

	status->aggr = unicast &&
		       !ieee80211_is_qos_nullfunc(fc);
	status->qos_ctl = qos_ctl;
	status->seqno = IEEE80211_SEQ_TO_SN(seq_ctrl);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NL80211_TESTMODE
व्योम mt7915_mac_fill_rx_vector(काष्ठा mt7915_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7915_phy *phy = &dev->phy;
	__le32 *rxd = (__le32 *)skb->data;
	__le32 *rxv_hdr = rxd + 2;
	__le32 *rxv = rxd + 4;
	u32 rcpi, ib_rssi, wb_rssi, v20, v21;
	bool ext_phy;
	s32 foe;
	u8 snr;
	पूर्णांक i;

	ext_phy = FIELD_GET(MT_RXV_HDR_BAND_IDX, le32_to_cpu(rxv_hdr[1]));
	अगर (ext_phy)
		phy = mt7915_ext_phy(dev);

	rcpi = le32_to_cpu(rxv[6]);
	ib_rssi = le32_to_cpu(rxv[7]);
	wb_rssi = le32_to_cpu(rxv[8]) >> 5;

	क्रम (i = 0; i < 4; i++, rcpi >>= 8, ib_rssi >>= 8, wb_rssi >>= 9) अणु
		अगर (i == 3)
			wb_rssi = le32_to_cpu(rxv[9]);

		phy->test.last_rcpi[i] = rcpi & 0xff;
		phy->test.last_ib_rssi[i] = ib_rssi & 0xff;
		phy->test.last_wb_rssi[i] = wb_rssi & 0xff;
	पूर्ण

	v20 = le32_to_cpu(rxv[20]);
	v21 = le32_to_cpu(rxv[21]);

	foe = FIELD_GET(MT_CRXV_FOE_LO, v20) |
	      (FIELD_GET(MT_CRXV_FOE_HI, v21) << MT_CRXV_FOE_SHIFT);

	snr = FIELD_GET(MT_CRXV_SNR, v20) - 16;

	phy->test.last_freq_offset = foe;
	phy->test.last_snr = snr;

	dev_kमुक्त_skb(skb);
पूर्ण
#पूर्ण_अगर

अटल व्योम
mt7915_mac_ग_लिखो_txwi_पंचांग(काष्ठा mt7915_phy *phy, __le32 *txwi,
			 काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_NL80211_TESTMODE
	काष्ठा mt76_tesपंचांगode_data *td = &phy->mt76->test;
	स्थिर काष्ठा ieee80211_rate *r;
	u8 bw, mode, nss = td->tx_rate_nss;
	u8 rate_idx = td->tx_rate_idx;
	u16 rateval = 0;
	u32 val;
	bool cck = false;
	पूर्णांक band;

	अगर (skb != phy->mt76->test.tx_skb)
		वापस;

	चयन (td->tx_rate_mode) अणु
	हाल MT76_TM_TX_MODE_HT:
		nss = 1 + (rate_idx >> 3);
		mode = MT_PHY_TYPE_HT;
		अवरोध;
	हाल MT76_TM_TX_MODE_VHT:
		mode = MT_PHY_TYPE_VHT;
		अवरोध;
	हाल MT76_TM_TX_MODE_HE_SU:
		mode = MT_PHY_TYPE_HE_SU;
		अवरोध;
	हाल MT76_TM_TX_MODE_HE_EXT_SU:
		mode = MT_PHY_TYPE_HE_EXT_SU;
		अवरोध;
	हाल MT76_TM_TX_MODE_HE_TB:
		mode = MT_PHY_TYPE_HE_TB;
		अवरोध;
	हाल MT76_TM_TX_MODE_HE_MU:
		mode = MT_PHY_TYPE_HE_MU;
		अवरोध;
	हाल MT76_TM_TX_MODE_CCK:
		cck = true;
		fallthrough;
	हाल MT76_TM_TX_MODE_OFDM:
		band = phy->mt76->chandef.chan->band;
		अगर (band == NL80211_BAND_2GHZ && !cck)
			rate_idx += 4;

		r = &phy->mt76->hw->wiphy->bands[band]->bitrates[rate_idx];
		val = cck ? r->hw_value_लघु : r->hw_value;

		mode = val >> 8;
		rate_idx = val & 0xff;
		अवरोध;
	शेष:
		mode = MT_PHY_TYPE_OFDM;
		अवरोध;
	पूर्ण

	चयन (phy->mt76->chandef.width) अणु
	हाल NL80211_CHAN_WIDTH_40:
		bw = 1;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
		bw = 2;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80P80:
	हाल NL80211_CHAN_WIDTH_160:
		bw = 3;
		अवरोध;
	शेष:
		bw = 0;
		अवरोध;
	पूर्ण

	अगर (td->tx_rate_stbc && nss == 1) अणु
		nss++;
		rateval |= MT_TX_RATE_STBC;
	पूर्ण

	rateval |= FIELD_PREP(MT_TX_RATE_IDX, rate_idx) |
		   FIELD_PREP(MT_TX_RATE_MODE, mode) |
		   FIELD_PREP(MT_TX_RATE_NSS, nss - 1);

	txwi[2] |= cpu_to_le32(MT_TXD2_FIX_RATE);

	le32p_replace_bits(&txwi[3], 1, MT_TXD3_REM_TX_COUNT);
	अगर (td->tx_rate_mode < MT76_TM_TX_MODE_HT)
		txwi[3] |= cpu_to_le32(MT_TXD3_BA_DISABLE);

	val = MT_TXD6_FIXED_BW |
	      FIELD_PREP(MT_TXD6_BW, bw) |
	      FIELD_PREP(MT_TXD6_TX_RATE, rateval) |
	      FIELD_PREP(MT_TXD6_SGI, td->tx_rate_sgi);

	/* क्रम HE_SU/HE_EXT_SU PPDU
	 * - 1x, 2x, 4x LTF + 0.8us GI
	 * - 2x LTF + 1.6us GI, 4x LTF + 3.2us GI
	 * क्रम HE_MU PPDU
	 * - 2x, 4x LTF + 0.8us GI
	 * - 2x LTF + 1.6us GI, 4x LTF + 3.2us GI
	 * क्रम HE_TB PPDU
	 * - 1x, 2x LTF + 1.6us GI
	 * - 4x LTF + 3.2us GI
	 */
	अगर (mode >= MT_PHY_TYPE_HE_SU)
		val |= FIELD_PREP(MT_TXD6_HELTF, td->tx_ltf);

	अगर (td->tx_rate_ldpc || (bw > 0 && mode >= MT_PHY_TYPE_HE_SU))
		val |= MT_TXD6_LDPC;

	txwi[3] &= ~cpu_to_le32(MT_TXD3_SN_VALID);
	txwi[6] |= cpu_to_le32(val);
	txwi[7] |= cpu_to_le32(FIELD_PREP(MT_TXD7_SPE_IDX,
					  phy->test.spe_idx));
#पूर्ण_अगर
पूर्ण

अटल व्योम
mt7915_mac_ग_लिखो_txwi_8023(काष्ठा mt7915_dev *dev, __le32 *txwi,
			   काष्ठा sk_buff *skb, काष्ठा mt76_wcid *wcid)
अणु

	u8 tid = skb->priority & IEEE80211_QOS_CTL_TID_MASK;
	u8 fc_type, fc_stype;
	bool wmm = false;
	u32 val;

	अगर (wcid->sta) अणु
		काष्ठा ieee80211_sta *sta;

		sta = container_of((व्योम *)wcid, काष्ठा ieee80211_sta, drv_priv);
		wmm = sta->wme;
	पूर्ण

	val = FIELD_PREP(MT_TXD1_HDR_FORMAT, MT_HDR_FORMAT_802_3) |
	      FIELD_PREP(MT_TXD1_TID, tid);

	अगर (be16_to_cpu(skb->protocol) >= ETH_P_802_3_MIN)
		val |= MT_TXD1_ETH_802_3;

	txwi[1] |= cpu_to_le32(val);

	fc_type = IEEE80211_FTYPE_DATA >> 2;
	fc_stype = wmm ? IEEE80211_STYPE_QOS_DATA >> 4 : 0;

	val = FIELD_PREP(MT_TXD2_FRAME_TYPE, fc_type) |
	      FIELD_PREP(MT_TXD2_SUB_TYPE, fc_stype);

	txwi[2] |= cpu_to_le32(val);

	val = FIELD_PREP(MT_TXD7_TYPE, fc_type) |
	      FIELD_PREP(MT_TXD7_SUB_TYPE, fc_stype);
	txwi[7] |= cpu_to_le32(val);
पूर्ण

अटल व्योम
mt7915_mac_ग_लिखो_txwi_80211(काष्ठा mt7915_dev *dev, __le32 *txwi,
			    काष्ठा sk_buff *skb, काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_mgmt *mgmt = (काष्ठा ieee80211_mgmt *)skb->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	bool multicast = is_multicast_ether_addr(hdr->addr1);
	u8 tid = skb->priority & IEEE80211_QOS_CTL_TID_MASK;
	__le16 fc = hdr->frame_control;
	u8 fc_type, fc_stype;
	u32 val;

	अगर (ieee80211_is_action(fc) &&
	    mgmt->u.action.category == WLAN_CATEGORY_BACK &&
	    mgmt->u.action.u.addba_req.action_code == WLAN_ACTION_ADDBA_REQ) अणु
		u16 capab = le16_to_cpu(mgmt->u.action.u.addba_req.capab);

		txwi[5] |= cpu_to_le32(MT_TXD5_ADD_BA);
		tid = (capab >> 2) & IEEE80211_QOS_CTL_TID_MASK;
	पूर्ण अन्यथा अगर (ieee80211_is_back_req(hdr->frame_control)) अणु
		काष्ठा ieee80211_bar *bar = (काष्ठा ieee80211_bar *)hdr;
		u16 control = le16_to_cpu(bar->control);

		tid = FIELD_GET(IEEE80211_BAR_CTRL_TID_INFO_MASK, control);
	पूर्ण

	val = FIELD_PREP(MT_TXD1_HDR_FORMAT, MT_HDR_FORMAT_802_11) |
	      FIELD_PREP(MT_TXD1_HDR_INFO,
			 ieee80211_get_hdrlen_from_skb(skb) / 2) |
	      FIELD_PREP(MT_TXD1_TID, tid);
	txwi[1] |= cpu_to_le32(val);

	fc_type = (le16_to_cpu(fc) & IEEE80211_FCTL_FTYPE) >> 2;
	fc_stype = (le16_to_cpu(fc) & IEEE80211_FCTL_STYPE) >> 4;

	val = FIELD_PREP(MT_TXD2_FRAME_TYPE, fc_type) |
	      FIELD_PREP(MT_TXD2_SUB_TYPE, fc_stype) |
	      FIELD_PREP(MT_TXD2_MULTICAST, multicast);

	अगर (key && multicast && ieee80211_is_robust_mgmt_frame(skb) &&
	    key->cipher == WLAN_CIPHER_SUITE_AES_CMAC) अणु
		val |= MT_TXD2_BIP;
		txwi[3] &= ~cpu_to_le32(MT_TXD3_PROTECT_FRAME);
	पूर्ण

	अगर (!ieee80211_is_data(fc) || multicast)
		val |= MT_TXD2_FIX_RATE;

	txwi[2] |= cpu_to_le32(val);

	अगर (ieee80211_is_beacon(fc)) अणु
		txwi[3] &= ~cpu_to_le32(MT_TXD3_SW_POWER_MGMT);
		txwi[3] |= cpu_to_le32(MT_TXD3_REM_TX_COUNT);
	पूर्ण

	अगर (info->flags & IEEE80211_TX_CTL_INJECTED) अणु
		u16 seqno = le16_to_cpu(hdr->seq_ctrl);

		अगर (ieee80211_is_back_req(hdr->frame_control)) अणु
			काष्ठा ieee80211_bar *bar;

			bar = (काष्ठा ieee80211_bar *)skb->data;
			seqno = le16_to_cpu(bar->start_seq_num);
		पूर्ण

		val = MT_TXD3_SN_VALID |
		      FIELD_PREP(MT_TXD3_SEQ, IEEE80211_SEQ_TO_SN(seqno));
		txwi[3] |= cpu_to_le32(val);
	पूर्ण

	val = FIELD_PREP(MT_TXD7_TYPE, fc_type) |
	      FIELD_PREP(MT_TXD7_SUB_TYPE, fc_stype);
	txwi[7] |= cpu_to_le32(val);
पूर्ण

व्योम mt7915_mac_ग_लिखो_txwi(काष्ठा mt7915_dev *dev, __le32 *txwi,
			   काष्ठा sk_buff *skb, काष्ठा mt76_wcid *wcid,
			   काष्ठा ieee80211_key_conf *key, bool beacon)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_vअगर *vअगर = info->control.vअगर;
	काष्ठा mt76_phy *mphy = &dev->mphy;
	bool ext_phy = info->hw_queue & MT_TX_HW_QUEUE_EXT_PHY;
	u8 p_fmt, q_idx, omac_idx = 0, wmm_idx = 0;
	bool is_8023 = info->flags & IEEE80211_TX_CTL_HW_80211_ENCAP;
	u16 tx_count = 15;
	u32 val;

	अगर (vअगर) अणु
		काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;

		omac_idx = mvअगर->omac_idx;
		wmm_idx = mvअगर->wmm_idx;
	पूर्ण

	अगर (ext_phy && dev->mt76.phy2)
		mphy = dev->mt76.phy2;

	अगर (beacon) अणु
		p_fmt = MT_TX_TYPE_FW;
		q_idx = MT_LMAC_BCN0;
	पूर्ण अन्यथा अगर (skb_get_queue_mapping(skb) >= MT_TXQ_PSD) अणु
		p_fmt = MT_TX_TYPE_CT;
		q_idx = MT_LMAC_ALTX0;
	पूर्ण अन्यथा अणु
		p_fmt = MT_TX_TYPE_CT;
		q_idx = wmm_idx * MT7915_MAX_WMM_SETS +
			mt7915_lmac_mapping(dev, skb_get_queue_mapping(skb));
	पूर्ण

	val = FIELD_PREP(MT_TXD0_TX_BYTES, skb->len + MT_TXD_SIZE) |
	      FIELD_PREP(MT_TXD0_PKT_FMT, p_fmt) |
	      FIELD_PREP(MT_TXD0_Q_IDX, q_idx);
	txwi[0] = cpu_to_le32(val);

	val = MT_TXD1_LONG_FORMAT |
	      FIELD_PREP(MT_TXD1_WLAN_IDX, wcid->idx) |
	      FIELD_PREP(MT_TXD1_OWN_MAC, omac_idx);

	अगर (ext_phy && q_idx >= MT_LMAC_ALTX0 && q_idx <= MT_LMAC_BCN0)
		val |= MT_TXD1_TGID;

	txwi[1] = cpu_to_le32(val);

	txwi[2] = 0;

	val = MT_TXD3_SW_POWER_MGMT |
	      FIELD_PREP(MT_TXD3_REM_TX_COUNT, tx_count);
	अगर (key)
		val |= MT_TXD3_PROTECT_FRAME;
	अगर (info->flags & IEEE80211_TX_CTL_NO_ACK)
		val |= MT_TXD3_NO_ACK;

	txwi[3] = cpu_to_le32(val);
	txwi[4] = 0;
	txwi[5] = 0;
	txwi[6] = 0;
	txwi[7] = wcid->amsdu ? cpu_to_le32(MT_TXD7_HW_AMSDU) : 0;

	अगर (is_8023)
		mt7915_mac_ग_लिखो_txwi_8023(dev, txwi, skb, wcid);
	अन्यथा
		mt7915_mac_ग_लिखो_txwi_80211(dev, txwi, skb, key);

	अगर (txwi[2] & cpu_to_le32(MT_TXD2_FIX_RATE)) अणु
		u16 rate;

		/* hardware won't add HTC क्रम mgmt/ctrl frame */
		txwi[2] |= cpu_to_le32(MT_TXD2_HTC_VLD);

		अगर (mphy->chandef.chan->band == NL80211_BAND_5GHZ)
			rate = MT7915_5G_RATE_DEFAULT;
		अन्यथा
			rate = MT7915_2G_RATE_DEFAULT;

		val = MT_TXD6_FIXED_BW |
		      FIELD_PREP(MT_TXD6_TX_RATE, rate);
		txwi[6] |= cpu_to_le32(val);
		txwi[3] |= cpu_to_le32(MT_TXD3_BA_DISABLE);
	पूर्ण

	अगर (mt76_tesपंचांगode_enabled(mphy))
		mt7915_mac_ग_लिखो_txwi_पंचांग(mphy->priv, txwi, skb);
पूर्ण

पूर्णांक mt7915_tx_prepare_skb(काष्ठा mt76_dev *mdev, व्योम *txwi_ptr,
			  क्रमागत mt76_txq_id qid, काष्ठा mt76_wcid *wcid,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा mt76_tx_info *tx_info)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)tx_info->skb->data;
	काष्ठा mt7915_dev *dev = container_of(mdev, काष्ठा mt7915_dev, mt76);
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(tx_info->skb);
	काष्ठा ieee80211_key_conf *key = info->control.hw_key;
	काष्ठा ieee80211_vअगर *vअगर = info->control.vअगर;
	काष्ठा mt76_tx_cb *cb = mt76_tx_skb_cb(tx_info->skb);
	काष्ठा mt76_txwi_cache *t;
	काष्ठा mt7915_txp *txp;
	पूर्णांक id, i, nbuf = tx_info->nbuf - 1;
	u8 *txwi = (u8 *)txwi_ptr;

	अगर (unlikely(tx_info->skb->len <= ETH_HLEN))
		वापस -EINVAL;

	अगर (!wcid)
		wcid = &dev->mt76.global_wcid;

	mt7915_mac_ग_लिखो_txwi(dev, txwi_ptr, tx_info->skb, wcid, key,
			      false);

	cb->wcid = wcid->idx;

	txp = (काष्ठा mt7915_txp *)(txwi + MT_TXD_SIZE);
	क्रम (i = 0; i < nbuf; i++) अणु
		txp->buf[i] = cpu_to_le32(tx_info->buf[i + 1].addr);
		txp->len[i] = cpu_to_le16(tx_info->buf[i + 1].len);
	पूर्ण
	txp->nbuf = nbuf;

	txp->flags = cpu_to_le16(MT_CT_INFO_APPLY_TXD | MT_CT_INFO_FROM_HOST);

	अगर (!key)
		txp->flags |= cpu_to_le16(MT_CT_INFO_NONE_CIPHER_FRAME);

	अगर (!(info->flags & IEEE80211_TX_CTL_HW_80211_ENCAP) &&
	    ieee80211_is_mgmt(hdr->frame_control))
		txp->flags |= cpu_to_le16(MT_CT_INFO_MGMT_FRAME);

	अगर (vअगर) अणु
		काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;

		txp->bss_idx = mvअगर->idx;
	पूर्ण

	t = (काष्ठा mt76_txwi_cache *)(txwi + mdev->drv->txwi_size);
	t->skb = tx_info->skb;

	id = mt76_token_consume(mdev, &t);
	अगर (id < 0)
		वापस id;

	txp->token = cpu_to_le16(id);
	अगर (test_bit(MT_WCID_FLAG_4ADDR, &wcid->flags))
		txp->rept_wds_wcid = cpu_to_le16(wcid->idx);
	अन्यथा
		txp->rept_wds_wcid = cpu_to_le16(0x3ff);
	tx_info->skb = DMA_DUMMY_DATA;

	/* pass partial skb header to fw */
	tx_info->buf[1].len = MT_CT_PARSE_LEN;
	tx_info->buf[1].skip_unmap = true;
	tx_info->nbuf = MT_CT_DMA_BUF_NUM;

	वापस 0;
पूर्ण

अटल व्योम
mt7915_tx_check_aggr(काष्ठा ieee80211_sta *sta, __le32 *txwi)
अणु
	काष्ठा mt7915_sta *msta;
	u16 fc, tid;
	u32 val;

	अगर (!sta || !sta->ht_cap.ht_supported)
		वापस;

	tid = FIELD_GET(MT_TXD1_TID, le32_to_cpu(txwi[1]));
	अगर (tid >= 6) /* skip VO queue */
		वापस;

	val = le32_to_cpu(txwi[2]);
	fc = FIELD_GET(MT_TXD2_FRAME_TYPE, val) << 2 |
	     FIELD_GET(MT_TXD2_SUB_TYPE, val) << 4;
	अगर (unlikely(fc != (IEEE80211_FTYPE_DATA | IEEE80211_STYPE_QOS_DATA)))
		वापस;

	msta = (काष्ठा mt7915_sta *)sta->drv_priv;
	अगर (!test_and_set_bit(tid, &msta->ampdu_state))
		ieee80211_start_tx_ba_session(sta, tid, 0);
पूर्ण

अटल व्योम
mt7915_tx_complete_status(काष्ठा mt76_dev *mdev, काष्ठा sk_buff *skb,
			  काष्ठा ieee80211_sta *sta, u8 stat,
			  काष्ठा list_head *मुक्त_list)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_tx_status status = अणु
		.sta = sta,
		.info = info,
		.skb = skb,
		.मुक्त_list = मुक्त_list,
	पूर्ण;
	काष्ठा ieee80211_hw *hw;

	अगर (sta) अणु
		काष्ठा mt7915_sta *msta;

		msta = (काष्ठा mt7915_sta *)sta->drv_priv;
		status.rate = &msta->stats.tx_rate;
	पूर्ण

#अगर_घोषित CONFIG_NL80211_TESTMODE
	अगर (mt76_is_tesपंचांगode_skb(mdev, skb, &hw)) अणु
		काष्ठा mt7915_phy *phy = mt7915_hw_phy(hw);
		काष्ठा ieee80211_vअगर *vअगर = phy->monitor_vअगर;
		काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;

		mt76_tx_complete_skb(mdev, mvअगर->sta.wcid.idx, skb);
		वापस;
	पूर्ण
#पूर्ण_अगर

	hw = mt76_tx_status_get_hw(mdev, skb);

	अगर (info->flags & IEEE80211_TX_CTL_AMPDU)
		info->flags |= IEEE80211_TX_STAT_AMPDU;

	अगर (stat)
		ieee80211_tx_info_clear_status(info);

	अगर (!(info->flags & IEEE80211_TX_CTL_NO_ACK))
		info->flags |= IEEE80211_TX_STAT_ACK;

	info->status.tx_समय = 0;
	ieee80211_tx_status_ext(hw, &status);
पूर्ण

व्योम mt7915_txp_skb_unmap(काष्ठा mt76_dev *dev,
			  काष्ठा mt76_txwi_cache *t)
अणु
	काष्ठा mt7915_txp *txp;
	पूर्णांक i;

	txp = mt7915_txwi_to_txp(dev, t);
	क्रम (i = 0; i < txp->nbuf; i++)
		dma_unmap_single(dev->dev, le32_to_cpu(txp->buf[i]),
				 le16_to_cpu(txp->len[i]), DMA_TO_DEVICE);
पूर्ण

व्योम mt7915_mac_tx_मुक्त(काष्ठा mt7915_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7915_tx_मुक्त *मुक्त = (काष्ठा mt7915_tx_मुक्त *)skb->data;
	काष्ठा mt76_dev *mdev = &dev->mt76;
	काष्ठा mt76_phy *mphy_ext = mdev->phy2;
	काष्ठा mt76_txwi_cache *txwi;
	काष्ठा ieee80211_sta *sta = शून्य;
	LIST_HEAD(मुक्त_list);
	काष्ठा sk_buff *पंचांगp;
	u8 i, count;
	bool wake = false;

	/* clean DMA queues and unmap buffers first */
	mt76_queue_tx_cleanup(dev, dev->mphy.q_tx[MT_TXQ_PSD], false);
	mt76_queue_tx_cleanup(dev, dev->mphy.q_tx[MT_TXQ_BE], false);
	अगर (mphy_ext) अणु
		mt76_queue_tx_cleanup(dev, mphy_ext->q_tx[MT_TXQ_PSD], false);
		mt76_queue_tx_cleanup(dev, mphy_ext->q_tx[MT_TXQ_BE], false);
	पूर्ण

	/*
	 * TODO: MT_TX_FREE_LATENCY is msdu समय from the TXD is queued पूर्णांकo PLE,
	 * to the समय ack is received or dropped by hw (air + hw queue समय).
	 * Should aव्योम accessing WTBL to get Tx airसमय, and use it instead.
	 */
	count = FIELD_GET(MT_TX_FREE_MSDU_CNT, le16_to_cpu(मुक्त->ctrl));
	क्रम (i = 0; i < count; i++) अणु
		u32 msdu, info = le32_to_cpu(मुक्त->info[i]);
		u8 stat;

		/*
		 * 1'b1: new wcid pair.
		 * 1'b0: msdu_id with the same 'wcid pair' as above.
		 */
		अगर (info & MT_TX_FREE_PAIR) अणु
			काष्ठा mt7915_sta *msta;
			काष्ठा mt7915_phy *phy;
			काष्ठा mt76_wcid *wcid;
			u16 idx;

			count++;
			idx = FIELD_GET(MT_TX_FREE_WLAN_ID, info);
			wcid = rcu_dereference(dev->mt76.wcid[idx]);
			sta = wcid_to_sta(wcid);
			अगर (!sta)
				जारी;

			msta = container_of(wcid, काष्ठा mt7915_sta, wcid);
			phy = msta->vअगर->phy;
			spin_lock_bh(&dev->sta_poll_lock);
			अगर (list_empty(&msta->stats_list))
				list_add_tail(&msta->stats_list, &phy->stats_list);
			अगर (list_empty(&msta->poll_list))
				list_add_tail(&msta->poll_list, &dev->sta_poll_list);
			spin_unlock_bh(&dev->sta_poll_lock);
			जारी;
		पूर्ण

		msdu = FIELD_GET(MT_TX_FREE_MSDU_ID, info);
		stat = FIELD_GET(MT_TX_FREE_STATUS, info);

		txwi = mt76_token_release(mdev, msdu, &wake);
		अगर (!txwi)
			जारी;

		mt7915_txp_skb_unmap(mdev, txwi);
		अगर (txwi->skb) अणु
			काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(txwi->skb);
			व्योम *txwi_ptr = mt76_get_txwi_ptr(mdev, txwi);

			अगर (likely(txwi->skb->protocol != cpu_to_be16(ETH_P_PAE)))
				mt7915_tx_check_aggr(sta, txwi_ptr);

			अगर (sta && !info->tx_समय_est) अणु
				काष्ठा mt76_wcid *wcid = (काष्ठा mt76_wcid *)sta->drv_priv;
				पूर्णांक pending;

				pending = atomic_dec_वापस(&wcid->non_aql_packets);
				अगर (pending < 0)
					atomic_cmpxchg(&wcid->non_aql_packets, pending, 0);
			पूर्ण

			mt7915_tx_complete_status(mdev, txwi->skb, sta, stat, &मुक्त_list);
			txwi->skb = शून्य;
		पूर्ण

		mt76_put_txwi(mdev, txwi);
	पूर्ण

	mt7915_mac_sta_poll(dev);

	अगर (wake)
		mt76_set_tx_blocked(&dev->mt76, false);

	mt76_worker_schedule(&dev->mt76.tx_worker);

	napi_consume_skb(skb, 1);

	list_क्रम_each_entry_safe(skb, पंचांगp, &मुक्त_list, list) अणु
		skb_list_del_init(skb);
		napi_consume_skb(skb, 1);
	पूर्ण
पूर्ण

व्योम mt7915_tx_complete_skb(काष्ठा mt76_dev *mdev, काष्ठा mt76_queue_entry *e)
अणु
	काष्ठा mt7915_dev *dev;

	अगर (!e->txwi) अणु
		dev_kमुक्त_skb_any(e->skb);
		वापस;
	पूर्ण

	dev = container_of(mdev, काष्ठा mt7915_dev, mt76);

	/* error path */
	अगर (e->skb == DMA_DUMMY_DATA) अणु
		काष्ठा mt76_txwi_cache *t;
		काष्ठा mt7915_txp *txp;

		txp = mt7915_txwi_to_txp(mdev, e->txwi);
		t = mt76_token_put(mdev, le16_to_cpu(txp->token));
		e->skb = t ? t->skb : शून्य;
	पूर्ण

	अगर (e->skb) अणु
		काष्ठा mt76_tx_cb *cb = mt76_tx_skb_cb(e->skb);
		काष्ठा mt76_wcid *wcid;

		wcid = rcu_dereference(dev->mt76.wcid[cb->wcid]);

		mt7915_tx_complete_status(mdev, e->skb, wcid_to_sta(wcid), 0,
					  शून्य);
	पूर्ण
पूर्ण

व्योम mt7915_mac_cca_stats_reset(काष्ठा mt7915_phy *phy)
अणु
	काष्ठा mt7915_dev *dev = phy->dev;
	bool ext_phy = phy != &dev->phy;
	u32 reg = MT_WF_PHY_RX_CTRL1(ext_phy);

	mt76_clear(dev, reg, MT_WF_PHY_RX_CTRL1_STSCNT_EN);
	mt76_set(dev, reg, BIT(11) | BIT(9));
पूर्ण

व्योम mt7915_mac_reset_counters(काष्ठा mt7915_phy *phy)
अणु
	काष्ठा mt7915_dev *dev = phy->dev;
	bool ext_phy = phy != &dev->phy;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		mt76_rr(dev, MT_TX_AGG_CNT(ext_phy, i));
		mt76_rr(dev, MT_TX_AGG_CNT2(ext_phy, i));
	पूर्ण

	अगर (ext_phy) अणु
		dev->mt76.phy2->survey_समय = kसमय_get_bootसमय();
		i = ARRAY_SIZE(dev->mt76.aggr_stats) / 2;
	पूर्ण अन्यथा अणु
		dev->mt76.phy.survey_समय = kसमय_get_bootसमय();
		i = 0;
	पूर्ण
	स_रखो(&dev->mt76.aggr_stats[i], 0, माप(dev->mt76.aggr_stats) / 2);

	/* reset airसमय counters */
	mt76_rr(dev, MT_MIB_SDR9(ext_phy));
	mt76_rr(dev, MT_MIB_SDR36(ext_phy));
	mt76_rr(dev, MT_MIB_SDR37(ext_phy));

	mt76_set(dev, MT_WF_RMAC_MIB_TIME0(ext_phy),
		 MT_WF_RMAC_MIB_RXTIME_CLR);
	mt76_set(dev, MT_WF_RMAC_MIB_AIRTIME0(ext_phy),
		 MT_WF_RMAC_MIB_RXTIME_CLR);
पूर्ण

व्योम mt7915_mac_set_timing(काष्ठा mt7915_phy *phy)
अणु
	s16 coverage_class = phy->coverage_class;
	काष्ठा mt7915_dev *dev = phy->dev;
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
	पूर्ण अन्यथा अणु
		काष्ठा mt7915_phy *phy_ext = mt7915_ext_phy(dev);

		अगर (phy_ext)
			coverage_class = max_t(s16, phy_ext->coverage_class,
					       coverage_class);
	पूर्ण
	mt76_set(dev, MT_ARB_SCR(ext_phy),
		 MT_ARB_SCR_TX_DISABLE | MT_ARB_SCR_RX_DISABLE);
	udelay(1);

	offset = 3 * coverage_class;
	reg_offset = FIELD_PREP(MT_TIMEOUT_VAL_PLCP, offset) |
		     FIELD_PREP(MT_TIMEOUT_VAL_CCA, offset);

	mt76_wr(dev, MT_TMAC_CDTR(ext_phy), cck + reg_offset);
	mt76_wr(dev, MT_TMAC_ODTR(ext_phy), ofdm + reg_offset);
	mt76_wr(dev, MT_TMAC_ICR0(ext_phy),
		FIELD_PREP(MT_IFS_EIFS, 360) |
		FIELD_PREP(MT_IFS_RIFS, 2) |
		FIELD_PREP(MT_IFS_SIFS, sअगरs) |
		FIELD_PREP(MT_IFS_SLOT, phy->slotसमय));

	अगर (phy->slotसमय < 20 || is_5ghz)
		val = MT7915_CFEND_RATE_DEFAULT;
	अन्यथा
		val = MT7915_CFEND_RATE_11B;

	mt76_rmw_field(dev, MT_AGG_ACR0(ext_phy), MT_AGG_ACR_CFEND_RATE, val);
	mt76_clear(dev, MT_ARB_SCR(ext_phy),
		   MT_ARB_SCR_TX_DISABLE | MT_ARB_SCR_RX_DISABLE);
पूर्ण

व्योम mt7915_mac_enable_nf(काष्ठा mt7915_dev *dev, bool ext_phy)
अणु
	mt76_set(dev, MT_WF_PHY_RXTD12(ext_phy),
		 MT_WF_PHY_RXTD12_IRPI_SW_CLR_ONLY |
		 MT_WF_PHY_RXTD12_IRPI_SW_CLR);

	mt76_set(dev, MT_WF_PHY_RX_CTRL1(ext_phy),
		 FIELD_PREP(MT_WF_PHY_RX_CTRL1_IPI_EN, 0x5));
पूर्ण

अटल u8
mt7915_phy_get_nf(काष्ठा mt7915_phy *phy, पूर्णांक idx)
अणु
	अटल स्थिर u8 nf_घातer[] = अणु 92, 89, 86, 83, 80, 75, 70, 65, 60, 55, 52 पूर्ण;
	काष्ठा mt7915_dev *dev = phy->dev;
	u32 val, sum = 0, n = 0;
	पूर्णांक nss, i;

	क्रम (nss = 0; nss < hweight8(phy->mt76->chainmask); nss++) अणु
		u32 reg = MT_WF_IRPI(nss + (idx << dev->dbdc_support));

		क्रम (i = 0; i < ARRAY_SIZE(nf_घातer); i++, reg += 4) अणु
			val = mt76_rr(dev, reg);
			sum += val * nf_घातer[i];
			n += val;
		पूर्ण
	पूर्ण

	अगर (!n)
		वापस 0;

	वापस sum / n;
पूर्ण

अटल व्योम
mt7915_phy_update_channel(काष्ठा mt76_phy *mphy, पूर्णांक idx)
अणु
	काष्ठा mt7915_dev *dev = container_of(mphy->dev, काष्ठा mt7915_dev, mt76);
	काष्ठा mt7915_phy *phy = (काष्ठा mt7915_phy *)mphy->priv;
	काष्ठा mt76_channel_state *state;
	u64 busy_समय, tx_समय, rx_समय, obss_समय;
	पूर्णांक nf;

	busy_समय = mt76_get_field(dev, MT_MIB_SDR9(idx),
				   MT_MIB_SDR9_BUSY_MASK);
	tx_समय = mt76_get_field(dev, MT_MIB_SDR36(idx),
				 MT_MIB_SDR36_TXTIME_MASK);
	rx_समय = mt76_get_field(dev, MT_MIB_SDR37(idx),
				 MT_MIB_SDR37_RXTIME_MASK);
	obss_समय = mt76_get_field(dev, MT_WF_RMAC_MIB_AIRTIME14(idx),
				   MT_MIB_OBSSTIME_MASK);

	nf = mt7915_phy_get_nf(phy, idx);
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

व्योम mt7915_update_channel(काष्ठा mt76_dev *mdev)
अणु
	काष्ठा mt7915_dev *dev = container_of(mdev, काष्ठा mt7915_dev, mt76);

	mt7915_phy_update_channel(&mdev->phy, 0);
	अगर (mdev->phy2)
		mt7915_phy_update_channel(mdev->phy2, 1);

	/* reset obss airसमय */
	mt76_set(dev, MT_WF_RMAC_MIB_TIME0(0), MT_WF_RMAC_MIB_RXTIME_CLR);
	अगर (mdev->phy2)
		mt76_set(dev, MT_WF_RMAC_MIB_TIME0(1),
			 MT_WF_RMAC_MIB_RXTIME_CLR);
पूर्ण

अटल bool
mt7915_रुको_reset_state(काष्ठा mt7915_dev *dev, u32 state)
अणु
	bool ret;

	ret = रुको_event_समयout(dev->reset_रुको,
				 (READ_ONCE(dev->reset_state) & state),
				 MT7915_RESET_TIMEOUT);

	WARN(!ret, "Timeout waiting for MCU reset state %x\n", state);
	वापस ret;
पूर्ण

अटल व्योम
mt7915_update_vअगर_beacon(व्योम *priv, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_hw *hw = priv;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_AP:
		mt7915_mcu_add_beacon(hw, vअगर, vअगर->bss_conf.enable_beacon);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
mt7915_update_beacons(काष्ठा mt7915_dev *dev)
अणु
	ieee80211_iterate_active_पूर्णांकerfaces(dev->mt76.hw,
		IEEE80211_IFACE_ITER_RESUME_ALL,
		mt7915_update_vअगर_beacon, dev->mt76.hw);

	अगर (!dev->mt76.phy2)
		वापस;

	ieee80211_iterate_active_पूर्णांकerfaces(dev->mt76.phy2->hw,
		IEEE80211_IFACE_ITER_RESUME_ALL,
		mt7915_update_vअगर_beacon, dev->mt76.phy2->hw);
पूर्ण

अटल व्योम
mt7915_dma_reset(काष्ठा mt7915_dev *dev)
अणु
	काष्ठा mt76_phy *mphy_ext = dev->mt76.phy2;
	u32 hअगर1_ofs = MT_WFDMA1_PCIE1_BASE - MT_WFDMA1_BASE;
	पूर्णांक i;

	mt76_clear(dev, MT_WFDMA0_GLO_CFG,
		   MT_WFDMA0_GLO_CFG_TX_DMA_EN | MT_WFDMA0_GLO_CFG_RX_DMA_EN);
	mt76_clear(dev, MT_WFDMA1_GLO_CFG,
		   MT_WFDMA1_GLO_CFG_TX_DMA_EN | MT_WFDMA1_GLO_CFG_RX_DMA_EN);
	अगर (dev->hअगर2) अणु
		mt76_clear(dev, MT_WFDMA0_GLO_CFG + hअगर1_ofs,
			   (MT_WFDMA0_GLO_CFG_TX_DMA_EN |
			    MT_WFDMA0_GLO_CFG_RX_DMA_EN));
		mt76_clear(dev, MT_WFDMA1_GLO_CFG + hअगर1_ofs,
			   (MT_WFDMA1_GLO_CFG_TX_DMA_EN |
			    MT_WFDMA1_GLO_CFG_RX_DMA_EN));
	पूर्ण

	usleep_range(1000, 2000);

	क्रम (i = 0; i < __MT_TXQ_MAX; i++) अणु
		mt76_queue_tx_cleanup(dev, dev->mphy.q_tx[i], true);
		अगर (mphy_ext)
			mt76_queue_tx_cleanup(dev, mphy_ext->q_tx[i], true);
	पूर्ण

	क्रम (i = 0; i < __MT_MCUQ_MAX; i++)
		mt76_queue_tx_cleanup(dev, dev->mt76.q_mcu[i], true);

	mt76_क्रम_each_q_rx(&dev->mt76, i)
		mt76_queue_rx_reset(dev, i);

	mt76_tx_status_check(&dev->mt76, शून्य, true);

	/* re-init prefetch settings after reset */
	mt7915_dma_prefetch(dev);

	mt76_set(dev, MT_WFDMA0_GLO_CFG,
		 MT_WFDMA0_GLO_CFG_TX_DMA_EN | MT_WFDMA0_GLO_CFG_RX_DMA_EN);
	mt76_set(dev, MT_WFDMA1_GLO_CFG,
		 MT_WFDMA1_GLO_CFG_TX_DMA_EN | MT_WFDMA1_GLO_CFG_RX_DMA_EN);
	अगर (dev->hअगर2) अणु
		mt76_set(dev, MT_WFDMA0_GLO_CFG + hअगर1_ofs,
			(MT_WFDMA0_GLO_CFG_TX_DMA_EN |
			 MT_WFDMA0_GLO_CFG_RX_DMA_EN));
		mt76_set(dev, MT_WFDMA1_GLO_CFG + hअगर1_ofs,
			(MT_WFDMA1_GLO_CFG_TX_DMA_EN |
			 MT_WFDMA1_GLO_CFG_RX_DMA_EN));
	पूर्ण
पूर्ण

व्योम mt7915_tx_token_put(काष्ठा mt7915_dev *dev)
अणु
	काष्ठा mt76_txwi_cache *txwi;
	पूर्णांक id;

	spin_lock_bh(&dev->mt76.token_lock);
	idr_क्रम_each_entry(&dev->mt76.token, txwi, id) अणु
		mt7915_txp_skb_unmap(&dev->mt76, txwi);
		अगर (txwi->skb) अणु
			काष्ठा ieee80211_hw *hw;

			hw = mt76_tx_status_get_hw(&dev->mt76, txwi->skb);
			ieee80211_मुक्त_txskb(hw, txwi->skb);
		पूर्ण
		mt76_put_txwi(&dev->mt76, txwi);
		dev->mt76.token_count--;
	पूर्ण
	spin_unlock_bh(&dev->mt76.token_lock);
	idr_destroy(&dev->mt76.token);
पूर्ण

/* प्रणाली error recovery */
व्योम mt7915_mac_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7915_phy *phy2;
	काष्ठा mt76_phy *ext_phy;
	काष्ठा mt7915_dev *dev;

	dev = container_of(work, काष्ठा mt7915_dev, reset_work);
	ext_phy = dev->mt76.phy2;
	phy2 = ext_phy ? ext_phy->priv : शून्य;

	अगर (!(READ_ONCE(dev->reset_state) & MT_MCU_CMD_STOP_DMA))
		वापस;

	ieee80211_stop_queues(mt76_hw(dev));
	अगर (ext_phy)
		ieee80211_stop_queues(ext_phy->hw);

	set_bit(MT76_RESET, &dev->mphy.state);
	set_bit(MT76_MCU_RESET, &dev->mphy.state);
	wake_up(&dev->mt76.mcu.रुको);
	cancel_delayed_work_sync(&dev->mphy.mac_work);
	अगर (phy2) अणु
		set_bit(MT76_RESET, &phy2->mt76->state);
		cancel_delayed_work_sync(&phy2->mt76->mac_work);
	पूर्ण
	/* lock/unlock all queues to ensure that no tx is pending */
	mt76_txq_schedule_all(&dev->mphy);
	अगर (ext_phy)
		mt76_txq_schedule_all(ext_phy);

	mt76_worker_disable(&dev->mt76.tx_worker);
	napi_disable(&dev->mt76.napi[0]);
	napi_disable(&dev->mt76.napi[1]);
	napi_disable(&dev->mt76.napi[2]);
	napi_disable(&dev->mt76.tx_napi);

	mutex_lock(&dev->mt76.mutex);

	mt76_wr(dev, MT_MCU_INT_EVENT, MT_MCU_INT_EVENT_DMA_STOPPED);

	अगर (mt7915_रुको_reset_state(dev, MT_MCU_CMD_RESET_DONE)) अणु
		mt7915_dma_reset(dev);

		mt7915_tx_token_put(dev);
		idr_init(&dev->mt76.token);

		mt76_wr(dev, MT_MCU_INT_EVENT, MT_MCU_INT_EVENT_DMA_INIT);
		mt7915_रुको_reset_state(dev, MT_MCU_CMD_RECOVERY_DONE);
	पूर्ण

	clear_bit(MT76_MCU_RESET, &dev->mphy.state);
	clear_bit(MT76_RESET, &dev->mphy.state);
	अगर (phy2)
		clear_bit(MT76_RESET, &phy2->mt76->state);

	mt76_worker_enable(&dev->mt76.tx_worker);
	napi_enable(&dev->mt76.tx_napi);
	napi_schedule(&dev->mt76.tx_napi);

	napi_enable(&dev->mt76.napi[0]);
	napi_schedule(&dev->mt76.napi[0]);

	napi_enable(&dev->mt76.napi[1]);
	napi_schedule(&dev->mt76.napi[1]);

	napi_enable(&dev->mt76.napi[2]);
	napi_schedule(&dev->mt76.napi[2]);

	ieee80211_wake_queues(mt76_hw(dev));
	अगर (ext_phy)
		ieee80211_wake_queues(ext_phy->hw);

	mt76_wr(dev, MT_MCU_INT_EVENT, MT_MCU_INT_EVENT_RESET_DONE);
	mt7915_रुको_reset_state(dev, MT_MCU_CMD_NORMAL_STATE);

	mutex_unlock(&dev->mt76.mutex);

	mt7915_update_beacons(dev);

	ieee80211_queue_delayed_work(mt76_hw(dev), &dev->mphy.mac_work,
				     MT7915_WATCHDOG_TIME);
	अगर (phy2)
		ieee80211_queue_delayed_work(ext_phy->hw,
					     &phy2->mt76->mac_work,
					     MT7915_WATCHDOG_TIME);
पूर्ण

अटल व्योम
mt7915_mac_update_mib_stats(काष्ठा mt7915_phy *phy)
अणु
	काष्ठा mt7915_dev *dev = phy->dev;
	काष्ठा mib_stats *mib = &phy->mib;
	bool ext_phy = phy != &dev->phy;
	पूर्णांक i, aggr0, aggr1;

	mib->fcs_err_cnt += mt76_get_field(dev, MT_MIB_SDR3(ext_phy),
					   MT_MIB_SDR3_FCS_ERR_MASK);

	aggr0 = ext_phy ? ARRAY_SIZE(dev->mt76.aggr_stats) / 2 : 0;
	क्रम (i = 0, aggr1 = aggr0 + 4; i < 4; i++) अणु
		u32 val;

		val = mt76_rr(dev, MT_MIB_MB_SDR1(ext_phy, i));
		mib->ba_miss_cnt += FIELD_GET(MT_MIB_BA_MISS_COUNT_MASK, val);
		mib->ack_fail_cnt +=
			FIELD_GET(MT_MIB_ACK_FAIL_COUNT_MASK, val);

		val = mt76_rr(dev, MT_MIB_MB_SDR0(ext_phy, i));
		mib->rts_cnt += FIELD_GET(MT_MIB_RTS_COUNT_MASK, val);
		mib->rts_retries_cnt +=
			FIELD_GET(MT_MIB_RTS_RETRIES_COUNT_MASK, val);

		val = mt76_rr(dev, MT_TX_AGG_CNT(ext_phy, i));
		dev->mt76.aggr_stats[aggr0++] += val & 0xffff;
		dev->mt76.aggr_stats[aggr0++] += val >> 16;

		val = mt76_rr(dev, MT_TX_AGG_CNT2(ext_phy, i));
		dev->mt76.aggr_stats[aggr1++] += val & 0xffff;
		dev->mt76.aggr_stats[aggr1++] += val >> 16;
	पूर्ण
पूर्ण

अटल व्योम
mt7915_mac_sta_stats_work(काष्ठा mt7915_phy *phy)
अणु
	काष्ठा mt7915_dev *dev = phy->dev;
	काष्ठा mt7915_sta *msta;
	LIST_HEAD(list);

	spin_lock_bh(&dev->sta_poll_lock);
	list_splice_init(&phy->stats_list, &list);

	जबतक (!list_empty(&list)) अणु
		msta = list_first_entry(&list, काष्ठा mt7915_sta, stats_list);
		list_del_init(&msta->stats_list);
		spin_unlock_bh(&dev->sta_poll_lock);

		/* use MT_TX_FREE_RATE to report Tx rate क्रम further devices */
		mt7915_mcu_get_tx_rate(dev, RATE_CTRL_RU_INFO, msta->wcid.idx);

		spin_lock_bh(&dev->sta_poll_lock);
	पूर्ण

	spin_unlock_bh(&dev->sta_poll_lock);
पूर्ण

व्योम mt7915_mac_sta_rc_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7915_dev *dev = container_of(work, काष्ठा mt7915_dev, rc_work);
	काष्ठा ieee80211_sta *sta;
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा mt7915_sta *msta;
	u32 changed;
	LIST_HEAD(list);

	spin_lock_bh(&dev->sta_poll_lock);
	list_splice_init(&dev->sta_rc_list, &list);

	जबतक (!list_empty(&list)) अणु
		msta = list_first_entry(&list, काष्ठा mt7915_sta, rc_list);
		list_del_init(&msta->rc_list);
		changed = msta->stats.changed;
		msta->stats.changed = 0;
		spin_unlock_bh(&dev->sta_poll_lock);

		sta = container_of((व्योम *)msta, काष्ठा ieee80211_sta, drv_priv);
		vअगर = container_of((व्योम *)msta->vअगर, काष्ठा ieee80211_vअगर, drv_priv);

		अगर (changed & (IEEE80211_RC_SUPP_RATES_CHANGED |
			       IEEE80211_RC_NSS_CHANGED |
			       IEEE80211_RC_BW_CHANGED))
			mt7915_mcu_add_rate_ctrl(dev, vअगर, sta);

		अगर (changed & IEEE80211_RC_SMPS_CHANGED)
			mt7915_mcu_add_smps(dev, vअगर, sta);

		spin_lock_bh(&dev->sta_poll_lock);
	पूर्ण

	spin_unlock_bh(&dev->sta_poll_lock);
पूर्ण

व्योम mt7915_mac_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7915_phy *phy;
	काष्ठा mt76_phy *mphy;

	mphy = (काष्ठा mt76_phy *)container_of(work, काष्ठा mt76_phy,
					       mac_work.work);
	phy = mphy->priv;

	mutex_lock(&mphy->dev->mutex);

	mt76_update_survey(mphy->dev);
	अगर (++mphy->mac_work_count == 5) अणु
		mphy->mac_work_count = 0;

		mt7915_mac_update_mib_stats(phy);
	पूर्ण

	अगर (++phy->sta_work_count == 10) अणु
		phy->sta_work_count = 0;
		mt7915_mac_sta_stats_work(phy);
	पूर्ण

	mutex_unlock(&mphy->dev->mutex);

	ieee80211_queue_delayed_work(mphy->hw, &mphy->mac_work,
				     MT7915_WATCHDOG_TIME);
पूर्ण

अटल व्योम mt7915_dfs_stop_radar_detector(काष्ठा mt7915_phy *phy)
अणु
	काष्ठा mt7915_dev *dev = phy->dev;

	अगर (phy->rdd_state & BIT(0))
		mt7915_mcu_rdd_cmd(dev, RDD_STOP, 0, MT_RX_SEL0, 0);
	अगर (phy->rdd_state & BIT(1))
		mt7915_mcu_rdd_cmd(dev, RDD_STOP, 1, MT_RX_SEL0, 0);
पूर्ण

अटल पूर्णांक mt7915_dfs_start_rdd(काष्ठा mt7915_dev *dev, पूर्णांक chain)
अणु
	पूर्णांक err;

	err = mt7915_mcu_rdd_cmd(dev, RDD_START, chain, MT_RX_SEL0, 0);
	अगर (err < 0)
		वापस err;

	वापस mt7915_mcu_rdd_cmd(dev, RDD_DET_MODE, chain, MT_RX_SEL0, 1);
पूर्ण

अटल पूर्णांक mt7915_dfs_start_radar_detector(काष्ठा mt7915_phy *phy)
अणु
	काष्ठा cfg80211_chan_def *chandef = &phy->mt76->chandef;
	काष्ठा mt7915_dev *dev = phy->dev;
	bool ext_phy = phy != &dev->phy;
	पूर्णांक err;

	/* start CAC */
	err = mt7915_mcu_rdd_cmd(dev, RDD_CAC_START, ext_phy, MT_RX_SEL0, 0);
	अगर (err < 0)
		वापस err;

	err = mt7915_dfs_start_rdd(dev, ext_phy);
	अगर (err < 0)
		वापस err;

	phy->rdd_state |= BIT(ext_phy);

	अगर (chandef->width == NL80211_CHAN_WIDTH_160 ||
	    chandef->width == NL80211_CHAN_WIDTH_80P80) अणु
		err = mt7915_dfs_start_rdd(dev, 1);
		अगर (err < 0)
			वापस err;

		phy->rdd_state |= BIT(1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7915_dfs_init_radar_specs(काष्ठा mt7915_phy *phy)
अणु
	स्थिर काष्ठा mt7915_dfs_radar_spec *radar_specs;
	काष्ठा mt7915_dev *dev = phy->dev;
	पूर्णांक err, i;

	चयन (dev->mt76.region) अणु
	हाल NL80211_DFS_FCC:
		radar_specs = &fcc_radar_specs;
		err = mt7915_mcu_set_fcc5_lpn(dev, 8);
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
		err = mt7915_mcu_set_radar_th(dev, i,
					      &radar_specs->radar_pattern[i]);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस mt7915_mcu_set_pulse_th(dev, &radar_specs->pulse_th);
पूर्ण

पूर्णांक mt7915_dfs_init_radar_detector(काष्ठा mt7915_phy *phy)
अणु
	काष्ठा cfg80211_chan_def *chandef = &phy->mt76->chandef;
	काष्ठा mt7915_dev *dev = phy->dev;
	bool ext_phy = phy != &dev->phy;
	पूर्णांक err;

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

	err = mt7915_dfs_init_radar_specs(phy);
	अगर (err < 0) अणु
		phy->dfs_state = -1;
		जाओ stop;
	पूर्ण

	phy->dfs_state = chandef->chan->dfs_state;

	अगर (chandef->chan->flags & IEEE80211_CHAN_RADAR) अणु
		अगर (chandef->chan->dfs_state != NL80211_DFS_AVAILABLE)
			वापस mt7915_dfs_start_radar_detector(phy);

		वापस mt7915_mcu_rdd_cmd(dev, RDD_CAC_END, ext_phy,
					  MT_RX_SEL0, 0);
	पूर्ण

stop:
	err = mt7915_mcu_rdd_cmd(dev, RDD_NORMAL_START, ext_phy,
				 MT_RX_SEL0, 0);
	अगर (err < 0)
		वापस err;

	mt7915_dfs_stop_radar_detector(phy);
	वापस 0;
पूर्ण
