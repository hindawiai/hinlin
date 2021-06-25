<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc. */

#समावेश <linux/devcoredump.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/समयkeeping.h>
#समावेश "mt7921.h"
#समावेश "../dma.h"
#समावेश "mac.h"
#समावेश "mcu.h"

#घोषणा HE_BITS(f)		cpu_to_le16(IEEE80211_RADIOTAP_HE_##f)
#घोषणा HE_PREP(f, m, v)	le16_encode_bits(le32_get_bits(v, MT_CRXV_HE_##m),\
						 IEEE80211_RADIOTAP_HE_##f)

अटल काष्ठा mt76_wcid *mt7921_rx_get_wcid(काष्ठा mt7921_dev *dev,
					    u16 idx, bool unicast)
अणु
	काष्ठा mt7921_sta *sta;
	काष्ठा mt76_wcid *wcid;

	अगर (idx >= ARRAY_SIZE(dev->mt76.wcid))
		वापस शून्य;

	wcid = rcu_dereference(dev->mt76.wcid[idx]);
	अगर (unicast || !wcid)
		वापस wcid;

	अगर (!wcid->sta)
		वापस शून्य;

	sta = container_of(wcid, काष्ठा mt7921_sta, wcid);
	अगर (!sta->vअगर)
		वापस शून्य;

	वापस &sta->vअगर->sta.wcid;
पूर्ण

व्योम mt7921_sta_ps(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_sta *sta, bool ps)
अणु
पूर्ण

bool mt7921_mac_wtbl_update(काष्ठा mt7921_dev *dev, पूर्णांक idx, u32 mask)
अणु
	mt76_rmw(dev, MT_WTBL_UPDATE, MT_WTBL_UPDATE_WLAN_IDX,
		 FIELD_PREP(MT_WTBL_UPDATE_WLAN_IDX, idx) | mask);

	वापस mt76_poll(dev, MT_WTBL_UPDATE, MT_WTBL_UPDATE_BUSY,
			 0, 5000);
पूर्ण

अटल व्योम mt7921_mac_sta_poll(काष्ठा mt7921_dev *dev)
अणु
	अटल स्थिर u8 ac_to_tid[] = अणु
		[IEEE80211_AC_BE] = 0,
		[IEEE80211_AC_BK] = 1,
		[IEEE80211_AC_VI] = 4,
		[IEEE80211_AC_VO] = 6
	पूर्ण;
	काष्ठा ieee80211_sta *sta;
	काष्ठा mt7921_sta *msta;
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
					काष्ठा mt7921_sta, poll_list);
		list_del_init(&msta->poll_list);
		spin_unlock_bh(&dev->sta_poll_lock);

		idx = msta->wcid.idx;
		addr = MT_WTBL_LMAC_OFFS(idx, 0) + 20 * 4;

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
			mt7921_mac_wtbl_update(dev, idx,
					       MT_WTBL_UPDATE_ADM_COUNT_CLEAR);
			स_रखो(msta->airसमय_ac, 0, माप(msta->airसमय_ac));
		पूर्ण

		अगर (!msta->wcid.sta)
			जारी;

		sta = container_of((व्योम *)msta, काष्ठा ieee80211_sta,
				   drv_priv);
		क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
			u8 q = mt7921_lmac_mapping(dev, i);
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
mt7921_mac_decode_he_radiotap_ru(काष्ठा mt76_rx_status *status,
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
mt7921_mac_decode_he_radiotap(काष्ठा sk_buff *skb,
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

		mt7921_mac_decode_he_radiotap_ru(status, he, rxv);
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

		mt7921_mac_decode_he_radiotap_ru(status, he, rxv);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
mt7921_get_status_freq_info(काष्ठा mt7921_dev *dev, काष्ठा mt76_phy *mphy,
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

अटल व्योम
mt7921_mac_rssi_iter(व्योम *priv, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा sk_buff *skb = priv;
	काष्ठा mt76_rx_status *status = (काष्ठा mt76_rx_status *)skb->cb;
	काष्ठा mt7921_vअगर *mvअगर = (काष्ठा mt7921_vअगर *)vअगर->drv_priv;
	काष्ठा ieee80211_hdr *hdr = mt76_skb_get_hdr(skb);

	अगर (status->संकेत > 0)
		वापस;

	अगर (!ether_addr_equal(vअगर->addr, hdr->addr1))
		वापस;

	ewma_rssi_add(&mvअगर->rssi, -status->संकेत);
पूर्ण

अटल व्योम
mt7921_mac_assoc_rssi(काष्ठा mt7921_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = mt76_skb_get_hdr(skb);

	अगर (!ieee80211_is_assoc_resp(hdr->frame_control) &&
	    !ieee80211_is_auth(hdr->frame_control))
		वापस;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(mt76_hw(dev),
		IEEE80211_IFACE_ITER_RESUME_ALL,
		mt7921_mac_rssi_iter, skb);
पूर्ण

पूर्णांक mt7921_mac_fill_rx(काष्ठा mt7921_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt76_rx_status *status = (काष्ठा mt76_rx_status *)skb->cb;
	काष्ठा mt76_phy *mphy = &dev->mt76.phy;
	काष्ठा mt7921_phy *phy = &dev->phy;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_hdr *hdr;
	__le32 *rxd = (__le32 *)skb->data;
	__le32 *rxv = शून्य;
	u32 mode = 0;
	u32 rxd1 = le32_to_cpu(rxd[1]);
	u32 rxd2 = le32_to_cpu(rxd[2]);
	u32 rxd3 = le32_to_cpu(rxd[3]);
	bool unicast, insert_ccmp_hdr = false;
	u8 हटाओ_pad;
	पूर्णांक i, idx;
	u8 chfreq;

	स_रखो(status, 0, माप(*status));

	अगर (rxd1 & MT_RXD1_NORMAL_BAND_IDX)
		वापस -EINVAL;

	अगर (!test_bit(MT76_STATE_RUNNING, &mphy->state))
		वापस -EINVAL;

	chfreq = FIELD_GET(MT_RXD3_NORMAL_CH_FREQ, rxd3);
	unicast = FIELD_GET(MT_RXD3_NORMAL_ADDR_TYPE, rxd3) == MT_RXD3_NORMAL_U2M;
	idx = FIELD_GET(MT_RXD1_NORMAL_WLAN_IDX, rxd1);
	status->wcid = mt7921_rx_get_wcid(dev, idx, unicast);

	अगर (status->wcid) अणु
		काष्ठा mt7921_sta *msta;

		msta = container_of(status->wcid, काष्ठा mt7921_sta, wcid);
		spin_lock_bh(&dev->sta_poll_lock);
		अगर (list_empty(&msta->poll_list))
			list_add_tail(&msta->poll_list, &dev->sta_poll_list);
		spin_unlock_bh(&dev->sta_poll_lock);
	पूर्ण

	mt7921_get_status_freq_info(dev, mphy, status, chfreq);

	अगर (status->band == NL80211_BAND_5GHZ)
		sband = &mphy->sband_5g.sband;
	अन्यथा
		sband = &mphy->sband_2g.sband;

	अगर (!sband->channels)
		वापस -EINVAL;

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
		u8 stbc, gi;
		u32 v0, v1;
		bool cck;

		rxv = rxd;
		rxd += 2;
		अगर ((u8 *)rxd - skb->data >= skb->len)
			वापस -EINVAL;

		v0 = le32_to_cpu(rxv[0]);
		v1 = le32_to_cpu(rxv[1]);

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

		stbc = FIELD_GET(MT_PRXV_STBC, v0);
		gi = FIELD_GET(MT_PRXV_SGI, v0);
		cck = false;

		idx = i = FIELD_GET(MT_PRXV_TX_RATE, v0);
		mode = FIELD_GET(MT_PRXV_TX_MODE, v0);

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

		चयन (FIELD_GET(MT_PRXV_FRAME_MODE, v0)) अणु
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

		अगर (rxd1 & MT_RXD1_NORMAL_GROUP_5) अणु
			rxd += 18;
			अगर ((u8 *)rxd - skb->data >= skb->len)
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	skb_pull(skb, (u8 *)rxd - skb->data + 2 * हटाओ_pad);

	अगर (insert_ccmp_hdr) अणु
		u8 key_id = FIELD_GET(MT_RXD1_NORMAL_KEY_ID, rxd1);

		mt76_insert_ccmp_hdr(skb, key_id);
	पूर्ण

	mt7921_mac_assoc_rssi(dev, skb);

	अगर (rxv && status->flag & RX_FLAG_RADIOTAP_HE)
		mt7921_mac_decode_he_radiotap(skb, status, rxv, mode);

	hdr = mt76_skb_get_hdr(skb);
	अगर (!status->wcid || !ieee80211_is_data_qos(hdr->frame_control))
		वापस 0;

	status->aggr = unicast &&
		       !ieee80211_is_qos_nullfunc(hdr->frame_control);
	status->qos_ctl = *ieee80211_get_qos_ctl(hdr);
	status->seqno = IEEE80211_SEQ_TO_SN(le16_to_cpu(hdr->seq_ctrl));

	वापस 0;
पूर्ण

अटल व्योम
mt7921_mac_ग_लिखो_txwi_8023(काष्ठा mt7921_dev *dev, __le32 *txwi,
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
mt7921_mac_ग_लिखो_txwi_80211(काष्ठा mt7921_dev *dev, __le32 *txwi,
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

व्योम mt7921_mac_ग_लिखो_txwi(काष्ठा mt7921_dev *dev, __le32 *txwi,
			   काष्ठा sk_buff *skb, काष्ठा mt76_wcid *wcid,
			   काष्ठा ieee80211_key_conf *key, bool beacon)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_vअगर *vअगर = info->control.vअगर;
	काष्ठा mt76_phy *mphy = &dev->mphy;
	u8 p_fmt, q_idx, omac_idx = 0, wmm_idx = 0;
	bool is_8023 = info->flags & IEEE80211_TX_CTL_HW_80211_ENCAP;
	u16 tx_count = 15;
	u32 val;

	अगर (vअगर) अणु
		काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *)vअगर->drv_priv;

		omac_idx = mvअगर->omac_idx;
		wmm_idx = mvअगर->wmm_idx;
	पूर्ण

	अगर (beacon) अणु
		p_fmt = MT_TX_TYPE_FW;
		q_idx = MT_LMAC_BCN0;
	पूर्ण अन्यथा अगर (skb_get_queue_mapping(skb) >= MT_TXQ_PSD) अणु
		p_fmt = MT_TX_TYPE_CT;
		q_idx = MT_LMAC_ALTX0;
	पूर्ण अन्यथा अणु
		p_fmt = MT_TX_TYPE_CT;
		q_idx = wmm_idx * MT7921_MAX_WMM_SETS +
			mt7921_lmac_mapping(dev, skb_get_queue_mapping(skb));
	पूर्ण

	val = FIELD_PREP(MT_TXD0_TX_BYTES, skb->len + MT_TXD_SIZE) |
	      FIELD_PREP(MT_TXD0_PKT_FMT, p_fmt) |
	      FIELD_PREP(MT_TXD0_Q_IDX, q_idx);
	txwi[0] = cpu_to_le32(val);

	val = MT_TXD1_LONG_FORMAT |
	      FIELD_PREP(MT_TXD1_WLAN_IDX, wcid->idx) |
	      FIELD_PREP(MT_TXD1_OWN_MAC, omac_idx);

	txwi[1] = cpu_to_le32(val);
	txwi[2] = 0;

	val = FIELD_PREP(MT_TXD3_REM_TX_COUNT, tx_count);
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
		mt7921_mac_ग_लिखो_txwi_8023(dev, txwi, skb, wcid);
	अन्यथा
		mt7921_mac_ग_लिखो_txwi_80211(dev, txwi, skb, key);

	अगर (txwi[2] & cpu_to_le32(MT_TXD2_FIX_RATE)) अणु
		u16 rate;

		/* hardware won't add HTC क्रम mgmt/ctrl frame */
		txwi[2] |= cpu_to_le32(MT_TXD2_HTC_VLD);

		अगर (mphy->chandef.chan->band == NL80211_BAND_5GHZ)
			rate = MT7921_5G_RATE_DEFAULT;
		अन्यथा
			rate = MT7921_2G_RATE_DEFAULT;

		val = MT_TXD6_FIXED_BW |
		      FIELD_PREP(MT_TXD6_TX_RATE, rate);
		txwi[6] |= cpu_to_le32(val);
		txwi[3] |= cpu_to_le32(MT_TXD3_BA_DISABLE);
	पूर्ण
पूर्ण

अटल व्योम
mt7921_ग_लिखो_hw_txp(काष्ठा mt7921_dev *dev, काष्ठा mt76_tx_info *tx_info,
		    व्योम *txp_ptr, u32 id)
अणु
	काष्ठा mt7921_hw_txp *txp = txp_ptr;
	काष्ठा mt7921_txp_ptr *ptr = &txp->ptr[0];
	पूर्णांक i, nbuf = tx_info->nbuf - 1;

	tx_info->buf[0].len = MT_TXD_SIZE + माप(*txp);
	tx_info->nbuf = 1;

	txp->msdu_id[0] = cpu_to_le16(id | MT_MSDU_ID_VALID);

	क्रम (i = 0; i < nbuf; i++) अणु
		u16 len = tx_info->buf[i + 1].len & MT_TXD_LEN_MASK;
		u32 addr = tx_info->buf[i + 1].addr;

		अगर (i == nbuf - 1)
			len |= MT_TXD_LEN_LAST;

		अगर (i & 1) अणु
			ptr->buf1 = cpu_to_le32(addr);
			ptr->len1 = cpu_to_le16(len);
			ptr++;
		पूर्ण अन्यथा अणु
			ptr->buf0 = cpu_to_le32(addr);
			ptr->len0 = cpu_to_le16(len);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक mt7921_tx_prepare_skb(काष्ठा mt76_dev *mdev, व्योम *txwi_ptr,
			  क्रमागत mt76_txq_id qid, काष्ठा mt76_wcid *wcid,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा mt76_tx_info *tx_info)
अणु
	काष्ठा mt7921_dev *dev = container_of(mdev, काष्ठा mt7921_dev, mt76);
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(tx_info->skb);
	काष्ठा ieee80211_key_conf *key = info->control.hw_key;
	काष्ठा mt76_tx_cb *cb = mt76_tx_skb_cb(tx_info->skb);
	काष्ठा mt76_txwi_cache *t;
	काष्ठा mt7921_txp_common *txp;
	पूर्णांक id;
	u8 *txwi = (u8 *)txwi_ptr;

	अगर (unlikely(tx_info->skb->len <= ETH_HLEN))
		वापस -EINVAL;

	अगर (!wcid)
		wcid = &dev->mt76.global_wcid;

	cb->wcid = wcid->idx;

	t = (काष्ठा mt76_txwi_cache *)(txwi + mdev->drv->txwi_size);
	t->skb = tx_info->skb;

	id = mt76_token_consume(mdev, &t);
	अगर (id < 0)
		वापस id;

	mt7921_mac_ग_लिखो_txwi(dev, txwi_ptr, tx_info->skb, wcid, key,
			      false);

	txp = (काष्ठा mt7921_txp_common *)(txwi + MT_TXD_SIZE);
	स_रखो(txp, 0, माप(काष्ठा mt7921_txp_common));
	mt7921_ग_लिखो_hw_txp(dev, tx_info, txp, id);

	tx_info->skb = DMA_DUMMY_DATA;

	वापस 0;
पूर्ण

अटल व्योम
mt7921_tx_check_aggr(काष्ठा ieee80211_sta *sta, __le32 *txwi)
अणु
	काष्ठा mt7921_sta *msta;
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

	msta = (काष्ठा mt7921_sta *)sta->drv_priv;
	अगर (!test_and_set_bit(tid, &msta->ampdu_state))
		ieee80211_start_tx_ba_session(sta, tid, 0);
पूर्ण

अटल व्योम
mt7921_tx_complete_status(काष्ठा mt76_dev *mdev, काष्ठा sk_buff *skb,
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
		काष्ठा mt7921_sta *msta;

		msta = (काष्ठा mt7921_sta *)sta->drv_priv;
		status.rate = &msta->stats.tx_rate;
	पूर्ण

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

व्योम mt7921_txp_skb_unmap(काष्ठा mt76_dev *dev,
			  काष्ठा mt76_txwi_cache *t)
अणु
	काष्ठा mt7921_txp_common *txp;
	पूर्णांक i;

	txp = mt7921_txwi_to_txp(dev, t);

	क्रम (i = 0; i < ARRAY_SIZE(txp->hw.ptr); i++) अणु
		काष्ठा mt7921_txp_ptr *ptr = &txp->hw.ptr[i];
		bool last;
		u16 len;

		len = le16_to_cpu(ptr->len0);
		last = len & MT_TXD_LEN_LAST;
		len &= MT_TXD_LEN_MASK;
		dma_unmap_single(dev->dev, le32_to_cpu(ptr->buf0), len,
				 DMA_TO_DEVICE);
		अगर (last)
			अवरोध;

		len = le16_to_cpu(ptr->len1);
		last = len & MT_TXD_LEN_LAST;
		len &= MT_TXD_LEN_MASK;
		dma_unmap_single(dev->dev, le32_to_cpu(ptr->buf1), len,
				 DMA_TO_DEVICE);
		अगर (last)
			अवरोध;
	पूर्ण
पूर्ण

व्योम mt7921_mac_tx_मुक्त(काष्ठा mt7921_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7921_tx_मुक्त *मुक्त = (काष्ठा mt7921_tx_मुक्त *)skb->data;
	काष्ठा mt76_dev *mdev = &dev->mt76;
	काष्ठा mt76_txwi_cache *txwi;
	काष्ठा ieee80211_sta *sta = शून्य;
	LIST_HEAD(मुक्त_list);
	काष्ठा sk_buff *पंचांगp;
	bool wake = false;
	u8 i, count;

	/* clean DMA queues and unmap buffers first */
	mt76_queue_tx_cleanup(dev, dev->mphy.q_tx[MT_TXQ_PSD], false);
	mt76_queue_tx_cleanup(dev, dev->mphy.q_tx[MT_TXQ_BE], false);

	/* TODO: MT_TX_FREE_LATENCY is msdu समय from the TXD is queued पूर्णांकo PLE,
	 * to the समय ack is received or dropped by hw (air + hw queue समय).
	 * Should aव्योम accessing WTBL to get Tx airसमय, and use it instead.
	 */
	count = FIELD_GET(MT_TX_FREE_MSDU_CNT, le16_to_cpu(मुक्त->ctrl));
	क्रम (i = 0; i < count; i++) अणु
		u32 msdu, info = le32_to_cpu(मुक्त->info[i]);
		u8 stat;

		/* 1'b1: new wcid pair.
		 * 1'b0: msdu_id with the same 'wcid pair' as above.
		 */
		अगर (info & MT_TX_FREE_PAIR) अणु
			काष्ठा mt7921_sta *msta;
			काष्ठा mt7921_phy *phy;
			काष्ठा mt76_wcid *wcid;
			u16 idx;

			count++;
			idx = FIELD_GET(MT_TX_FREE_WLAN_ID, info);
			wcid = rcu_dereference(dev->mt76.wcid[idx]);
			sta = wcid_to_sta(wcid);
			अगर (!sta)
				जारी;

			msta = container_of(wcid, काष्ठा mt7921_sta, wcid);
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

		mt7921_txp_skb_unmap(mdev, txwi);
		अगर (txwi->skb) अणु
			काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(txwi->skb);
			व्योम *txwi_ptr = mt76_get_txwi_ptr(mdev, txwi);

			अगर (likely(txwi->skb->protocol != cpu_to_be16(ETH_P_PAE)))
				mt7921_tx_check_aggr(sta, txwi_ptr);

			अगर (sta && !info->tx_समय_est) अणु
				काष्ठा mt76_wcid *wcid = (काष्ठा mt76_wcid *)sta->drv_priv;
				पूर्णांक pending;

				pending = atomic_dec_वापस(&wcid->non_aql_packets);
				अगर (pending < 0)
					atomic_cmpxchg(&wcid->non_aql_packets, pending, 0);
			पूर्ण

			mt7921_tx_complete_status(mdev, txwi->skb, sta, stat, &मुक्त_list);
			txwi->skb = शून्य;
		पूर्ण

		mt76_put_txwi(mdev, txwi);
	पूर्ण

	अगर (wake)
		mt76_set_tx_blocked(&dev->mt76, false);

	napi_consume_skb(skb, 1);

	list_क्रम_each_entry_safe(skb, पंचांगp, &मुक्त_list, list) अणु
		skb_list_del_init(skb);
		napi_consume_skb(skb, 1);
	पूर्ण

	mt7921_mac_sta_poll(dev);
	mt76_worker_schedule(&dev->mt76.tx_worker);
पूर्ण

व्योम mt7921_tx_complete_skb(काष्ठा mt76_dev *mdev, काष्ठा mt76_queue_entry *e)
अणु
	काष्ठा mt7921_dev *dev;

	अगर (!e->txwi) अणु
		dev_kमुक्त_skb_any(e->skb);
		वापस;
	पूर्ण

	dev = container_of(mdev, काष्ठा mt7921_dev, mt76);

	/* error path */
	अगर (e->skb == DMA_DUMMY_DATA) अणु
		काष्ठा mt76_txwi_cache *t;
		काष्ठा mt7921_txp_common *txp;
		u16 token;

		txp = mt7921_txwi_to_txp(mdev, e->txwi);
		token = le16_to_cpu(txp->hw.msdu_id[0]) & ~MT_MSDU_ID_VALID;
		t = mt76_token_put(mdev, token);
		e->skb = t ? t->skb : शून्य;
	पूर्ण

	अगर (e->skb) अणु
		काष्ठा mt76_tx_cb *cb = mt76_tx_skb_cb(e->skb);
		काष्ठा mt76_wcid *wcid;

		wcid = rcu_dereference(dev->mt76.wcid[cb->wcid]);

		mt7921_tx_complete_status(mdev, e->skb, wcid_to_sta(wcid), 0,
					  शून्य);
	पूर्ण
पूर्ण

व्योम mt7921_mac_reset_counters(काष्ठा mt7921_phy *phy)
अणु
	काष्ठा mt7921_dev *dev = phy->dev;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		mt76_rr(dev, MT_TX_AGG_CNT(0, i));
		mt76_rr(dev, MT_TX_AGG_CNT2(0, i));
	पूर्ण

	dev->mt76.phy.survey_समय = kसमय_get_bootसमय();
	स_रखो(&dev->mt76.aggr_stats[0], 0, माप(dev->mt76.aggr_stats) / 2);

	/* reset airसमय counters */
	mt76_rr(dev, MT_MIB_SDR9(0));
	mt76_rr(dev, MT_MIB_SDR36(0));
	mt76_rr(dev, MT_MIB_SDR37(0));

	mt76_set(dev, MT_WF_RMAC_MIB_TIME0(0), MT_WF_RMAC_MIB_RXTIME_CLR);
	mt76_set(dev, MT_WF_RMAC_MIB_AIRTIME0(0), MT_WF_RMAC_MIB_RXTIME_CLR);
पूर्ण

व्योम mt7921_mac_set_timing(काष्ठा mt7921_phy *phy)
अणु
	s16 coverage_class = phy->coverage_class;
	काष्ठा mt7921_dev *dev = phy->dev;
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

	mt76_set(dev, MT_ARB_SCR(0),
		 MT_ARB_SCR_TX_DISABLE | MT_ARB_SCR_RX_DISABLE);
	udelay(1);

	offset = 3 * coverage_class;
	reg_offset = FIELD_PREP(MT_TIMEOUT_VAL_PLCP, offset) |
		     FIELD_PREP(MT_TIMEOUT_VAL_CCA, offset);

	mt76_wr(dev, MT_TMAC_CDTR(0), cck + reg_offset);
	mt76_wr(dev, MT_TMAC_ODTR(0), ofdm + reg_offset);
	mt76_wr(dev, MT_TMAC_ICR0(0),
		FIELD_PREP(MT_IFS_EIFS, 360) |
		FIELD_PREP(MT_IFS_RIFS, 2) |
		FIELD_PREP(MT_IFS_SIFS, sअगरs) |
		FIELD_PREP(MT_IFS_SLOT, phy->slotसमय));

	अगर (phy->slotसमय < 20 || is_5ghz)
		val = MT7921_CFEND_RATE_DEFAULT;
	अन्यथा
		val = MT7921_CFEND_RATE_11B;

	mt76_rmw_field(dev, MT_AGG_ACR0(0), MT_AGG_ACR_CFEND_RATE, val);
	mt76_clear(dev, MT_ARB_SCR(0),
		   MT_ARB_SCR_TX_DISABLE | MT_ARB_SCR_RX_DISABLE);
पूर्ण

अटल u8
mt7921_phy_get_nf(काष्ठा mt7921_phy *phy, पूर्णांक idx)
अणु
	वापस 0;
पूर्ण

अटल व्योम
mt7921_phy_update_channel(काष्ठा mt76_phy *mphy, पूर्णांक idx)
अणु
	काष्ठा mt7921_dev *dev = container_of(mphy->dev, काष्ठा mt7921_dev, mt76);
	काष्ठा mt7921_phy *phy = (काष्ठा mt7921_phy *)mphy->priv;
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

	nf = mt7921_phy_get_nf(phy, idx);
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

व्योम mt7921_update_channel(काष्ठा mt76_dev *mdev)
अणु
	काष्ठा mt7921_dev *dev = container_of(mdev, काष्ठा mt7921_dev, mt76);

	अगर (mt76_connac_pm_wake(&dev->mphy, &dev->pm))
		वापस;

	mt7921_phy_update_channel(&mdev->phy, 0);
	/* reset obss airसमय */
	mt76_set(dev, MT_WF_RMAC_MIB_TIME0(0), MT_WF_RMAC_MIB_RXTIME_CLR);

	mt76_connac_घातer_save_sched(&dev->mphy, &dev->pm);
पूर्ण

व्योम mt7921_tx_token_put(काष्ठा mt7921_dev *dev)
अणु
	काष्ठा mt76_txwi_cache *txwi;
	पूर्णांक id;

	spin_lock_bh(&dev->mt76.token_lock);
	idr_क्रम_each_entry(&dev->mt76.token, txwi, id) अणु
		mt7921_txp_skb_unmap(&dev->mt76, txwi);
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

अटल व्योम
mt7921_vअगर_connect_iter(व्योम *priv, u8 *mac,
			काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7921_vअगर *mvअगर = (काष्ठा mt7921_vअगर *)vअगर->drv_priv;
	काष्ठा mt7921_dev *dev = mvअगर->phy->dev;

	ieee80211_disconnect(vअगर, true);

	mt76_connac_mcu_uni_add_dev(&dev->mphy, vअगर, &mvअगर->sta.wcid, true);
	mt7921_mcu_set_tx(dev, vअगर);
पूर्ण

अटल पूर्णांक
mt7921_mac_reset(काष्ठा mt7921_dev *dev)
अणु
	पूर्णांक i, err;

	mt76_connac_मुक्त_pending_tx_skbs(&dev->pm, शून्य);

	mt76_wr(dev, MT_WFDMA0_HOST_INT_ENA, 0);
	mt76_wr(dev, MT_PCIE_MAC_INT_ENABLE, 0x0);

	set_bit(MT76_MCU_RESET, &dev->mphy.state);
	wake_up(&dev->mt76.mcu.रुको);
	skb_queue_purge(&dev->mt76.mcu.res_q);

	mt76_txq_schedule_all(&dev->mphy);

	mt76_worker_disable(&dev->mt76.tx_worker);
	napi_disable(&dev->mt76.napi[MT_RXQ_MAIN]);
	napi_disable(&dev->mt76.napi[MT_RXQ_MCU]);
	napi_disable(&dev->mt76.napi[MT_RXQ_MCU_WA]);
	napi_disable(&dev->mt76.tx_napi);

	mt7921_tx_token_put(dev);
	idr_init(&dev->mt76.token);

	err = mt7921_wpdma_reset(dev, true);
	अगर (err)
		वापस err;

	mt76_क्रम_each_q_rx(&dev->mt76, i) अणु
		napi_enable(&dev->mt76.napi[i]);
		napi_schedule(&dev->mt76.napi[i]);
	पूर्ण

	napi_enable(&dev->mt76.tx_napi);
	napi_schedule(&dev->mt76.tx_napi);
	mt76_worker_enable(&dev->mt76.tx_worker);

	clear_bit(MT76_MCU_RESET, &dev->mphy.state);
	clear_bit(MT76_STATE_PM, &dev->mphy.state);

	mt76_wr(dev, MT_WFDMA0_HOST_INT_ENA, 0);
	mt76_wr(dev, MT_PCIE_MAC_INT_ENABLE, 0xff);

	err = mt7921_run_firmware(dev);
	अगर (err)
		वापस err;

	err = mt7921_mcu_set_eeprom(dev);
	अगर (err)
		वापस err;

	mt7921_mac_init(dev);
	वापस __mt7921_start(&dev->phy);
पूर्ण

/* प्रणाली error recovery */
व्योम mt7921_mac_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा mt7921_dev *dev;
	पूर्णांक i;

	dev = container_of(work, काष्ठा mt7921_dev, reset_work);
	hw = mt76_hw(dev);

	dev_err(dev->mt76.dev, "chip reset\n");
	ieee80211_stop_queues(hw);

	cancel_delayed_work_sync(&dev->mphy.mac_work);
	cancel_delayed_work_sync(&dev->pm.ps_work);
	cancel_work_sync(&dev->pm.wake_work);

	mutex_lock(&dev->mt76.mutex);
	क्रम (i = 0; i < 10; i++) अणु
		अगर (!mt7921_mac_reset(dev))
			अवरोध;
	पूर्ण
	mutex_unlock(&dev->mt76.mutex);

	अगर (i == 10)
		dev_err(dev->mt76.dev, "chip reset failed\n");

	अगर (test_and_clear_bit(MT76_HW_SCANNING, &dev->mphy.state)) अणु
		काष्ठा cfg80211_scan_info info = अणु
			.पातed = true,
		पूर्ण;

		ieee80211_scan_completed(dev->mphy.hw, &info);
	पूर्ण

	ieee80211_wake_queues(hw);
	ieee80211_iterate_active_पूर्णांकerfaces(hw,
					    IEEE80211_IFACE_ITER_RESUME_ALL,
					    mt7921_vअगर_connect_iter, शून्य);
पूर्ण

व्योम mt7921_reset(काष्ठा mt76_dev *mdev)
अणु
	काष्ठा mt7921_dev *dev = container_of(mdev, काष्ठा mt7921_dev, mt76);

	queue_work(dev->mt76.wq, &dev->reset_work);
पूर्ण

अटल व्योम
mt7921_mac_update_mib_stats(काष्ठा mt7921_phy *phy)
अणु
	काष्ठा mt7921_dev *dev = phy->dev;
	काष्ठा mib_stats *mib = &phy->mib;
	पूर्णांक i, aggr0 = 0, aggr1;

	mib->fcs_err_cnt += mt76_get_field(dev, MT_MIB_SDR3(0),
					   MT_MIB_SDR3_FCS_ERR_MASK);
	mib->ack_fail_cnt += mt76_get_field(dev, MT_MIB_MB_BSDR3(0),
					    MT_MIB_ACK_FAIL_COUNT_MASK);
	mib->ba_miss_cnt += mt76_get_field(dev, MT_MIB_MB_BSDR2(0),
					   MT_MIB_BA_FAIL_COUNT_MASK);
	mib->rts_cnt += mt76_get_field(dev, MT_MIB_MB_BSDR0(0),
				       MT_MIB_RTS_COUNT_MASK);
	mib->rts_retries_cnt += mt76_get_field(dev, MT_MIB_MB_BSDR1(0),
					       MT_MIB_RTS_FAIL_COUNT_MASK);

	क्रम (i = 0, aggr1 = aggr0 + 4; i < 4; i++) अणु
		u32 val, val2;

		val = mt76_rr(dev, MT_TX_AGG_CNT(0, i));
		val2 = mt76_rr(dev, MT_TX_AGG_CNT2(0, i));

		dev->mt76.aggr_stats[aggr0++] += val & 0xffff;
		dev->mt76.aggr_stats[aggr0++] += val >> 16;
		dev->mt76.aggr_stats[aggr1++] += val2 & 0xffff;
		dev->mt76.aggr_stats[aggr1++] += val2 >> 16;
	पूर्ण
पूर्ण

अटल व्योम
mt7921_mac_sta_stats_work(काष्ठा mt7921_phy *phy)
अणु
	काष्ठा mt7921_dev *dev = phy->dev;
	काष्ठा mt7921_sta *msta;
	LIST_HEAD(list);

	spin_lock_bh(&dev->sta_poll_lock);
	list_splice_init(&phy->stats_list, &list);

	जबतक (!list_empty(&list)) अणु
		msta = list_first_entry(&list, काष्ठा mt7921_sta, stats_list);
		list_del_init(&msta->stats_list);
		spin_unlock_bh(&dev->sta_poll_lock);

		/* query wtbl info to report tx rate क्रम further devices */
		mt7921_get_wtbl_info(dev, msta->wcid.idx);

		spin_lock_bh(&dev->sta_poll_lock);
	पूर्ण

	spin_unlock_bh(&dev->sta_poll_lock);
पूर्ण

व्योम mt7921_mac_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7921_phy *phy;
	काष्ठा mt76_phy *mphy;

	mphy = (काष्ठा mt76_phy *)container_of(work, काष्ठा mt76_phy,
					       mac_work.work);
	phy = mphy->priv;

	mt7921_mutex_acquire(phy->dev);

	mt76_update_survey(mphy->dev);
	अगर (++mphy->mac_work_count == 2) अणु
		mphy->mac_work_count = 0;

		mt7921_mac_update_mib_stats(phy);
	पूर्ण
	अगर (++phy->sta_work_count == 4) अणु
		phy->sta_work_count = 0;
		mt7921_mac_sta_stats_work(phy);
	पूर्ण

	mt7921_mutex_release(phy->dev);
	ieee80211_queue_delayed_work(phy->mt76->hw, &mphy->mac_work,
				     MT7921_WATCHDOG_TIME);
पूर्ण

व्योम mt7921_pm_wake_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7921_dev *dev;
	काष्ठा mt76_phy *mphy;

	dev = (काष्ठा mt7921_dev *)container_of(work, काष्ठा mt7921_dev,
						pm.wake_work);
	mphy = dev->phy.mt76;

	अगर (!mt7921_mcu_drv_pmctrl(dev)) अणु
		पूर्णांक i;

		mt76_क्रम_each_q_rx(&dev->mt76, i)
			napi_schedule(&dev->mt76.napi[i]);
		mt76_connac_pm_dequeue_skbs(mphy, &dev->pm);
		mt7921_tx_cleanup(dev);
		अगर (test_bit(MT76_STATE_RUNNING, &mphy->state))
			ieee80211_queue_delayed_work(mphy->hw, &mphy->mac_work,
						     MT7921_WATCHDOG_TIME);
	पूर्ण

	ieee80211_wake_queues(mphy->hw);
	wake_up(&dev->pm.रुको);
पूर्ण

व्योम mt7921_pm_घातer_save_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7921_dev *dev;
	अचिन्हित दीर्घ delta;

	dev = (काष्ठा mt7921_dev *)container_of(work, काष्ठा mt7921_dev,
						pm.ps_work.work);

	delta = dev->pm.idle_समयout;
	अगर (test_bit(MT76_HW_SCANNING, &dev->mphy.state) ||
	    test_bit(MT76_HW_SCHED_SCANNING, &dev->mphy.state))
		जाओ out;

	अगर (समय_is_after_jअगरfies(dev->pm.last_activity + delta)) अणु
		delta = dev->pm.last_activity + delta - jअगरfies;
		जाओ out;
	पूर्ण

	अगर (!mt7921_mcu_fw_pmctrl(dev))
		वापस;
out:
	queue_delayed_work(dev->mt76.wq, &dev->pm.ps_work, delta);
पूर्ण

पूर्णांक mt7921_mac_set_beacon_filter(काष्ठा mt7921_phy *phy,
				 काष्ठा ieee80211_vअगर *vअगर,
				 bool enable)
अणु
	काष्ठा mt7921_dev *dev = phy->dev;
	bool ext_phy = phy != &dev->phy;
	पूर्णांक err;

	अगर (!dev->pm.enable)
		वापस -EOPNOTSUPP;

	err = mt7921_mcu_set_bss_pm(dev, vअगर, enable);
	अगर (err)
		वापस err;

	अगर (enable) अणु
		vअगर->driver_flags |= IEEE80211_VIF_BEACON_FILTER;
		mt76_set(dev, MT_WF_RFCR(ext_phy),
			 MT_WF_RFCR_DROP_OTHER_BEACON);
	पूर्ण अन्यथा अणु
		vअगर->driver_flags &= ~IEEE80211_VIF_BEACON_FILTER;
		mt76_clear(dev, MT_WF_RFCR(ext_phy),
			   MT_WF_RFCR_DROP_OTHER_BEACON);
	पूर्ण

	वापस 0;
पूर्ण

व्योम mt7921_coredump_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7921_dev *dev;
	अक्षर *dump, *data;

	dev = (काष्ठा mt7921_dev *)container_of(work, काष्ठा mt7921_dev,
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

		skb_pull(skb, माप(काष्ठा mt7921_mcu_rxd));
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
	mt7921_reset(&dev->mt76);
पूर्ण
