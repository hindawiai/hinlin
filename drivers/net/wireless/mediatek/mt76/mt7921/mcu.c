<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc. */

#समावेश <linux/firmware.h>
#समावेश <linux/fs.h>
#समावेश "mt7921.h"
#समावेश "mt7921_trace.h"
#समावेश "mcu.h"
#समावेश "mac.h"

काष्ठा mt7921_patch_hdr अणु
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

काष्ठा mt7921_patch_sec अणु
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

काष्ठा mt7921_fw_trailer अणु
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

काष्ठा mt7921_fw_region अणु
	__le32 decomp_crc;
	__le32 decomp_len;
	__le32 decomp_blk_sz;
	u8 reserved[4];
	__le32 addr;
	__le32 len;
	u8 feature_set;
	u8 reserved1[15];
पूर्ण __packed;

#घोषणा MT_STA_BFER			BIT(0)
#घोषणा MT_STA_BFEE			BIT(1)

#घोषणा FW_FEATURE_SET_ENCRYPT		BIT(0)
#घोषणा FW_FEATURE_SET_KEY_IDX		GENMASK(2, 1)
#घोषणा FW_FEATURE_ENCRY_MODE		BIT(4)
#घोषणा FW_FEATURE_OVERRIDE_ADDR	BIT(5)

#घोषणा DL_MODE_ENCRYPT			BIT(0)
#घोषणा DL_MODE_KEY_IDX			GENMASK(2, 1)
#घोषणा DL_MODE_RESET_SEC_IV		BIT(3)
#घोषणा DL_MODE_WORKING_PDA_CR4		BIT(4)
#घोषणा DL_CONFIG_ENCRY_MODE_SEL	BIT(6)
#घोषणा DL_MODE_NEED_RSP		BIT(31)

#घोषणा FW_START_OVERRIDE		BIT(0)
#घोषणा FW_START_WORKING_PDA_CR4	BIT(2)

#घोषणा PATCH_SEC_TYPE_MASK		GENMASK(15, 0)
#घोषणा PATCH_SEC_TYPE_INFO		0x2

#घोषणा to_wcid_lo(id)			FIELD_GET(GENMASK(7, 0), (u16)id)
#घोषणा to_wcid_hi(id)			FIELD_GET(GENMASK(9, 8), (u16)id)

अटल क्रमागत mt7921_cipher_type
mt7921_mcu_get_cipher(पूर्णांक cipher)
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

अटल u8 mt7921_mcu_chan_bw(काष्ठा cfg80211_chan_def *chandef)
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

अटल पूर्णांक
mt7921_mcu_parse_eeprom(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7921_mcu_eeprom_info *res;
	u8 *buf;

	अगर (!skb)
		वापस -EINVAL;

	skb_pull(skb, माप(काष्ठा mt7921_mcu_rxd));

	res = (काष्ठा mt7921_mcu_eeprom_info *)skb->data;
	buf = dev->eeprom.data + le32_to_cpu(res->addr);
	स_नकल(buf, res->data, 16);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7921_mcu_parse_response(काष्ठा mt76_dev *mdev, पूर्णांक cmd,
			  काष्ठा sk_buff *skb, पूर्णांक seq)
अणु
	काष्ठा mt7921_mcu_rxd *rxd;
	पूर्णांक ret = 0;

	अगर (!skb) अणु
		dev_err(mdev->dev, "Message %08x (seq %d) timeout\n",
			cmd, seq);
		mt7921_reset(mdev);

		वापस -ETIMEDOUT;
	पूर्ण

	rxd = (काष्ठा mt7921_mcu_rxd *)skb->data;
	अगर (seq != rxd->seq)
		वापस -EAGAIN;

	चयन (cmd) अणु
	हाल MCU_CMD_PATCH_SEM_CONTROL:
		skb_pull(skb, माप(*rxd) - 4);
		ret = *skb->data;
		अवरोध;
	हाल MCU_EXT_CMD_GET_TEMP:
		skb_pull(skb, माप(*rxd) + 4);
		ret = le32_to_cpu(*(__le32 *)skb->data);
		अवरोध;
	हाल MCU_EXT_CMD_EFUSE_ACCESS:
		ret = mt7921_mcu_parse_eeprom(mdev, skb);
		अवरोध;
	हाल MCU_UNI_CMD_DEV_INFO_UPDATE:
	हाल MCU_UNI_CMD_BSS_INFO_UPDATE:
	हाल MCU_UNI_CMD_STA_REC_UPDATE:
	हाल MCU_UNI_CMD_HIF_CTRL:
	हाल MCU_UNI_CMD_OFFLOAD:
	हाल MCU_UNI_CMD_SUSPEND: अणु
		काष्ठा mt7921_mcu_uni_event *event;

		skb_pull(skb, माप(*rxd));
		event = (काष्ठा mt7921_mcu_uni_event *)skb->data;
		ret = le32_to_cpu(event->status);
		अवरोध;
	पूर्ण
	हाल MCU_CMD_REG_READ: अणु
		काष्ठा mt7921_mcu_reg_event *event;

		skb_pull(skb, माप(*rxd));
		event = (काष्ठा mt7921_mcu_reg_event *)skb->data;
		ret = (पूर्णांक)le32_to_cpu(event->val);
		अवरोध;
	पूर्ण
	शेष:
		skb_pull(skb, माप(काष्ठा mt7921_mcu_rxd));
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7921_mcu_send_message(काष्ठा mt76_dev *mdev, काष्ठा sk_buff *skb,
			पूर्णांक cmd, पूर्णांक *रुको_seq)
अणु
	काष्ठा mt7921_dev *dev = container_of(mdev, काष्ठा mt7921_dev, mt76);
	पूर्णांक txd_len, mcu_cmd = cmd & MCU_CMD_MASK;
	क्रमागत mt76_mcuq_id txq = MT_MCUQ_WM;
	काष्ठा mt7921_uni_txd *uni_txd;
	काष्ठा mt7921_mcu_txd *mcu_txd;
	__le32 *txd;
	u32 val;
	u8 seq;

	चयन (cmd) अणु
	हाल MCU_UNI_CMD_HIF_CTRL:
	हाल MCU_UNI_CMD_SUSPEND:
	हाल MCU_UNI_CMD_OFFLOAD:
		mdev->mcu.समयout = HZ / 3;
		अवरोध;
	शेष:
		mdev->mcu.समयout = 3 * HZ;
		अवरोध;
	पूर्ण

	seq = ++dev->mt76.mcu.msg_seq & 0xf;
	अगर (!seq)
		seq = ++dev->mt76.mcu.msg_seq & 0xf;

	अगर (cmd == MCU_CMD_FW_SCATTER) अणु
		txq = MT_MCUQ_FWDL;
		जाओ निकास;
	पूर्ण

	txd_len = cmd & MCU_UNI_PREFIX ? माप(*uni_txd) : माप(*mcu_txd);
	txd = (__le32 *)skb_push(skb, txd_len);

	val = FIELD_PREP(MT_TXD0_TX_BYTES, skb->len) |
	      FIELD_PREP(MT_TXD0_PKT_FMT, MT_TX_TYPE_CMD) |
	      FIELD_PREP(MT_TXD0_Q_IDX, MT_TX_MCU_PORT_RX_Q0);
	txd[0] = cpu_to_le32(val);

	val = MT_TXD1_LONG_FORMAT |
	      FIELD_PREP(MT_TXD1_HDR_FORMAT, MT_HDR_FORMAT_CMD);
	txd[1] = cpu_to_le32(val);

	अगर (cmd & MCU_UNI_PREFIX) अणु
		uni_txd = (काष्ठा mt7921_uni_txd *)txd;
		uni_txd->len = cpu_to_le16(skb->len - माप(uni_txd->txd));
		uni_txd->option = MCU_CMD_UNI_EXT_ACK;
		uni_txd->cid = cpu_to_le16(mcu_cmd);
		uni_txd->s2d_index = MCU_S2D_H2N;
		uni_txd->pkt_type = MCU_PKT_ID;
		uni_txd->seq = seq;

		जाओ निकास;
	पूर्ण

	mcu_txd = (काष्ठा mt7921_mcu_txd *)txd;
	mcu_txd->len = cpu_to_le16(skb->len - माप(mcu_txd->txd));
	mcu_txd->pq_id = cpu_to_le16(MCU_PQ_ID(MT_TX_PORT_IDX_MCU,
					       MT_TX_MCU_PORT_RX_Q0));
	mcu_txd->pkt_type = MCU_PKT_ID;
	mcu_txd->seq = seq;

	चयन (cmd & ~MCU_CMD_MASK) अणु
	हाल MCU_FW_PREFIX:
		mcu_txd->set_query = MCU_Q_NA;
		mcu_txd->cid = mcu_cmd;
		अवरोध;
	हाल MCU_CE_PREFIX:
		अगर (cmd & MCU_QUERY_MASK)
			mcu_txd->set_query = MCU_Q_QUERY;
		अन्यथा
			mcu_txd->set_query = MCU_Q_SET;
		mcu_txd->cid = mcu_cmd;
		अवरोध;
	शेष:
		mcu_txd->cid = MCU_CMD_EXT_CID;
		अगर (cmd & MCU_QUERY_PREFIX || cmd == MCU_EXT_CMD_EFUSE_ACCESS)
			mcu_txd->set_query = MCU_Q_QUERY;
		अन्यथा
			mcu_txd->set_query = MCU_Q_SET;
		mcu_txd->ext_cid = mcu_cmd;
		mcu_txd->ext_cid_ack = 1;
		अवरोध;
	पूर्ण

	mcu_txd->s2d_index = MCU_S2D_H2N;
	WARN_ON(cmd == MCU_EXT_CMD_EFUSE_ACCESS &&
		mcu_txd->set_query != MCU_Q_QUERY);

निकास:
	अगर (रुको_seq)
		*रुको_seq = seq;

	वापस mt76_tx_queue_skb_raw(dev, mdev->q_mcu[txq], skb, 0);
पूर्ण

अटल व्योम
mt7921_mcu_tx_rate_parse(काष्ठा mt76_phy *mphy,
			 काष्ठा mt7921_mcu_peer_cap *peer,
			 काष्ठा rate_info *rate, u16 r)
अणु
	काष्ठा ieee80211_supported_band *sband;
	u16 flags = 0;
	u8 txmode = FIELD_GET(MT_WTBL_RATE_TX_MODE, r);
	u8 gi = 0;
	u8 bw = 0;

	rate->mcs = FIELD_GET(MT_WTBL_RATE_MCS, r);
	rate->nss = FIELD_GET(MT_WTBL_RATE_NSS, r) + 1;

	चयन (peer->bw) अणु
	हाल IEEE80211_STA_RX_BW_160:
		gi = peer->g16;
		अवरोध;
	हाल IEEE80211_STA_RX_BW_80:
		gi = peer->g8;
		अवरोध;
	हाल IEEE80211_STA_RX_BW_40:
		gi = peer->g4;
		अवरोध;
	शेष:
		gi = peer->g2;
		अवरोध;
	पूर्ण

	gi = txmode >= MT_PHY_TYPE_HE_SU ?
		FIELD_GET(MT_WTBL_RATE_HE_GI, gi) :
		FIELD_GET(MT_WTBL_RATE_GI, gi);

	चयन (txmode) अणु
	हाल MT_PHY_TYPE_CCK:
	हाल MT_PHY_TYPE_OFDM:
		अगर (mphy->chandef.chan->band == NL80211_BAND_5GHZ)
			sband = &mphy->sband_5g.sband;
		अन्यथा
			sband = &mphy->sband_2g.sband;

		rate->legacy = sband->bitrates[rate->mcs].bitrate;
		अवरोध;
	हाल MT_PHY_TYPE_HT:
	हाल MT_PHY_TYPE_HT_GF:
		flags |= RATE_INFO_FLAGS_MCS;

		अगर (gi)
			flags |= RATE_INFO_FLAGS_SHORT_GI;
		अवरोध;
	हाल MT_PHY_TYPE_VHT:
		flags |= RATE_INFO_FLAGS_VHT_MCS;

		अगर (gi)
			flags |= RATE_INFO_FLAGS_SHORT_GI;
		अवरोध;
	हाल MT_PHY_TYPE_HE_SU:
	हाल MT_PHY_TYPE_HE_EXT_SU:
	हाल MT_PHY_TYPE_HE_TB:
	हाल MT_PHY_TYPE_HE_MU:
		rate->he_gi = gi;
		rate->he_dcm = FIELD_GET(MT_RA_RATE_DCM_EN, r);

		flags |= RATE_INFO_FLAGS_HE_MCS;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	rate->flags = flags;

	bw = mt7921_mcu_chan_bw(&mphy->chandef) - FIELD_GET(MT_RA_RATE_BW, r);

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

अटल व्योम
mt7921_mcu_tx_rate_report(काष्ठा mt7921_dev *dev, काष्ठा sk_buff *skb,
			  u16 wlan_idx)
अणु
	काष्ठा mt7921_mcu_wlan_info_event *wtbl_info;
	काष्ठा mt76_phy *mphy = &dev->mphy;
	काष्ठा mt7921_sta_stats *stats;
	काष्ठा rate_info rate = अणुपूर्ण;
	काष्ठा mt7921_sta *msta;
	काष्ठा mt76_wcid *wcid;
	u8 idx;

	अगर (wlan_idx >= MT76_N_WCIDS)
		वापस;

	wtbl_info = (काष्ठा mt7921_mcu_wlan_info_event *)skb->data;
	idx = wtbl_info->rate_info.rate_idx;
	अगर (idx >= ARRAY_SIZE(wtbl_info->rate_info.rate))
		वापस;

	rcu_पढ़ो_lock();

	wcid = rcu_dereference(dev->mt76.wcid[wlan_idx]);
	अगर (!wcid)
		जाओ out;

	msta = container_of(wcid, काष्ठा mt7921_sta, wcid);
	stats = &msta->stats;

	/* current rate */
	mt7921_mcu_tx_rate_parse(mphy, &wtbl_info->peer_cap, &rate,
				 le16_to_cpu(wtbl_info->rate_info.rate[idx]));
	stats->tx_rate = rate;
out:
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम
mt7921_mcu_scan_event(काष्ठा mt7921_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt76_phy *mphy = &dev->mt76.phy;
	काष्ठा mt7921_phy *phy = (काष्ठा mt7921_phy *)mphy->priv;

	spin_lock_bh(&dev->mt76.lock);
	__skb_queue_tail(&phy->scan_event_list, skb);
	spin_unlock_bh(&dev->mt76.lock);

	ieee80211_queue_delayed_work(mphy->hw, &phy->scan_work,
				     MT7921_HW_SCAN_TIMEOUT);
पूर्ण

अटल व्योम
mt7921_mcu_beacon_loss_event(काष्ठा mt7921_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt76_connac_beacon_loss_event *event;
	काष्ठा mt76_phy *mphy;
	u8 band_idx = 0; /* DBDC support */

	skb_pull(skb, माप(काष्ठा mt7921_mcu_rxd));
	event = (काष्ठा mt76_connac_beacon_loss_event *)skb->data;
	अगर (band_idx && dev->mt76.phy2)
		mphy = dev->mt76.phy2;
	अन्यथा
		mphy = &dev->mt76.phy;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(mphy->hw,
					IEEE80211_IFACE_ITER_RESUME_ALL,
					mt76_connac_mcu_beacon_loss_iter, event);
पूर्ण

अटल व्योम
mt7921_mcu_bss_event(काष्ठा mt7921_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt76_phy *mphy = &dev->mt76.phy;
	काष्ठा mt76_connac_mcu_bss_event *event;

	skb_pull(skb, माप(काष्ठा mt7921_mcu_rxd));
	event = (काष्ठा mt76_connac_mcu_bss_event *)skb->data;
	अगर (event->is_असलent)
		ieee80211_stop_queues(mphy->hw);
	अन्यथा
		ieee80211_wake_queues(mphy->hw);
पूर्ण

अटल व्योम
mt7921_mcu_debug_msg_event(काष्ठा mt7921_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7921_debug_msg अणु
		__le16 id;
		u8 type;
		u8 flag;
		__le32 value;
		__le16 len;
		u8 content[512];
	पूर्ण __packed * msg;

	skb_pull(skb, माप(काष्ठा mt7921_mcu_rxd));
	msg = (काष्ठा mt7921_debug_msg *)skb->data;

	अगर (msg->type == 3) अणु /* fw log */
		u16 len = min_t(u16, le16_to_cpu(msg->len), 512);
		पूर्णांक i;

		क्रम (i = 0 ; i < len; i++) अणु
			अगर (!msg->content[i])
				msg->content[i] = ' ';
		पूर्ण
		wiphy_info(mt76_hw(dev)->wiphy, "%.*s", len, msg->content);
	पूर्ण
पूर्ण

अटल व्योम
mt7921_mcu_low_घातer_event(काष्ठा mt7921_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7921_mcu_lp_event अणु
		u8 state;
		u8 reserved[3];
	पूर्ण __packed * event;

	skb_pull(skb, माप(काष्ठा mt7921_mcu_rxd));
	event = (काष्ठा mt7921_mcu_lp_event *)skb->data;

	trace_lp_event(dev, event->state);
पूर्ण

अटल व्योम
mt7921_mcu_rx_unsolicited_event(काष्ठा mt7921_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7921_mcu_rxd *rxd = (काष्ठा mt7921_mcu_rxd *)skb->data;

	चयन (rxd->eid) अणु
	हाल MCU_EVENT_BSS_BEACON_LOSS:
		mt7921_mcu_beacon_loss_event(dev, skb);
		अवरोध;
	हाल MCU_EVENT_SCHED_SCAN_DONE:
	हाल MCU_EVENT_SCAN_DONE:
		mt7921_mcu_scan_event(dev, skb);
		वापस;
	हाल MCU_EVENT_BSS_ABSENCE:
		mt7921_mcu_bss_event(dev, skb);
		अवरोध;
	हाल MCU_EVENT_DBG_MSG:
		mt7921_mcu_debug_msg_event(dev, skb);
		अवरोध;
	हाल MCU_EVENT_COREDUMP:
		mt76_connac_mcu_coredump_event(&dev->mt76, skb,
					       &dev->coredump);
		वापस;
	हाल MCU_EVENT_LP_INFO:
		mt7921_mcu_low_घातer_event(dev, skb);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	dev_kमुक्त_skb(skb);
पूर्ण

व्योम mt7921_mcu_rx_event(काष्ठा mt7921_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7921_mcu_rxd *rxd = (काष्ठा mt7921_mcu_rxd *)skb->data;

	अगर (rxd->eid == 0x6) अणु
		mt76_mcu_rx_event(&dev->mt76, skb);
		वापस;
	पूर्ण

	अगर (rxd->ext_eid == MCU_EXT_EVENT_RATE_REPORT ||
	    rxd->eid == MCU_EVENT_BSS_BEACON_LOSS ||
	    rxd->eid == MCU_EVENT_SCHED_SCAN_DONE ||
	    rxd->eid == MCU_EVENT_BSS_ABSENCE ||
	    rxd->eid == MCU_EVENT_SCAN_DONE ||
	    rxd->eid == MCU_EVENT_DBG_MSG ||
	    rxd->eid == MCU_EVENT_COREDUMP ||
	    rxd->eid == MCU_EVENT_LP_INFO ||
	    !rxd->seq)
		mt7921_mcu_rx_unsolicited_event(dev, skb);
	अन्यथा
		mt76_mcu_rx_event(&dev->mt76, skb);
पूर्ण

/** starec & wtbl **/
अटल पूर्णांक
mt7921_mcu_sta_key_tlv(काष्ठा mt7921_sta *msta, काष्ठा sk_buff *skb,
		       काष्ठा ieee80211_key_conf *key, क्रमागत set_key_cmd cmd)
अणु
	काष्ठा mt7921_sta_key_conf *bip = &msta->bip;
	काष्ठा sta_rec_sec *sec;
	काष्ठा tlv *tlv;
	u32 len = माप(*sec);

	tlv = mt76_connac_mcu_add_tlv(skb, STA_REC_KEY_V2, माप(*sec));

	sec = (काष्ठा sta_rec_sec *)tlv;
	sec->add = cmd;

	अगर (cmd == SET_KEY) अणु
		काष्ठा sec_key *sec_key;
		u8 cipher;

		cipher = mt7921_mcu_get_cipher(key->cipher);
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

पूर्णांक mt7921_mcu_add_key(काष्ठा mt7921_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा mt7921_sta *msta, काष्ठा ieee80211_key_conf *key,
		       क्रमागत set_key_cmd cmd)
अणु
	काष्ठा mt7921_vअगर *mvअगर = (काष्ठा mt7921_vअगर *)vअगर->drv_priv;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = mt76_connac_mcu_alloc_sta_req(&dev->mt76, &mvअगर->mt76,
					    &msta->wcid);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	ret = mt7921_mcu_sta_key_tlv(msta, skb, key, cmd);
	अगर (ret)
		वापस ret;

	वापस mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_UNI_CMD_STA_REC_UPDATE, true);
पूर्ण

पूर्णांक mt7921_mcu_uni_tx_ba(काष्ठा mt7921_dev *dev,
			 काष्ठा ieee80211_ampdu_params *params,
			 bool enable)
अणु
	काष्ठा mt7921_sta *msta = (काष्ठा mt7921_sta *)params->sta->drv_priv;

	अगर (enable && !params->amsdu)
		msta->wcid.amsdu = false;

	वापस mt76_connac_mcu_sta_ba(&dev->mt76, &msta->vअगर->mt76, params,
				      enable, true);
पूर्ण

पूर्णांक mt7921_mcu_uni_rx_ba(काष्ठा mt7921_dev *dev,
			 काष्ठा ieee80211_ampdu_params *params,
			 bool enable)
अणु
	काष्ठा mt7921_sta *msta = (काष्ठा mt7921_sta *)params->sta->drv_priv;

	वापस mt76_connac_mcu_sta_ba(&dev->mt76, &msta->vअगर->mt76, params,
				      enable, false);
पूर्ण

अटल पूर्णांक mt7921_mcu_restart(काष्ठा mt76_dev *dev)
अणु
	काष्ठा अणु
		u8 घातer_mode;
		u8 rsv[3];
	पूर्ण req = अणु
		.घातer_mode = 1,
	पूर्ण;

	वापस mt76_mcu_send_msg(dev, MCU_CMD_NIC_POWER_CTRL, &req,
				 माप(req), false);
पूर्ण

अटल पूर्णांक mt7921_driver_own(काष्ठा mt7921_dev *dev)
अणु
	u32 reg = mt7921_reg_map_l1(dev, MT_TOP_LPCR_HOST_BAND0);

	mt76_wr(dev, reg, MT_TOP_LPCR_HOST_DRV_OWN);
	अगर (!mt76_poll_msec(dev, reg, MT_TOP_LPCR_HOST_FW_OWN,
			    0, 500)) अणु
		dev_err(dev->mt76.dev, "Timeout for driver own\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt7921_load_patch(काष्ठा mt7921_dev *dev)
अणु
	स्थिर काष्ठा mt7921_patch_hdr *hdr;
	स्थिर काष्ठा firmware *fw = शून्य;
	पूर्णांक i, ret, sem;

	sem = mt76_connac_mcu_patch_sem_ctrl(&dev->mt76, true);
	चयन (sem) अणु
	हाल PATCH_IS_DL:
		वापस 0;
	हाल PATCH_NOT_DL_SEM_SUCCESS:
		अवरोध;
	शेष:
		dev_err(dev->mt76.dev, "Failed to get patch semaphore\n");
		वापस -EAGAIN;
	पूर्ण

	ret = request_firmware(&fw, MT7921_ROM_PATCH, dev->mt76.dev);
	अगर (ret)
		जाओ out;

	अगर (!fw || !fw->data || fw->size < माप(*hdr)) अणु
		dev_err(dev->mt76.dev, "Invalid firmware\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	hdr = (स्थिर काष्ठा mt7921_patch_hdr *)(fw->data);

	dev_info(dev->mt76.dev, "HW/SW Version: 0x%x, Build Time: %.16s\n",
		 be32_to_cpu(hdr->hw_sw_ver), hdr->build_date);

	क्रम (i = 0; i < be32_to_cpu(hdr->desc.n_region); i++) अणु
		काष्ठा mt7921_patch_sec *sec;
		स्थिर u8 *dl;
		u32 len, addr;

		sec = (काष्ठा mt7921_patch_sec *)(fw->data + माप(*hdr) +
						  i * माप(*sec));
		अगर ((be32_to_cpu(sec->type) & PATCH_SEC_TYPE_MASK) !=
		    PATCH_SEC_TYPE_INFO) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		addr = be32_to_cpu(sec->info.addr);
		len = be32_to_cpu(sec->info.len);
		dl = fw->data + be32_to_cpu(sec->offs);

		ret = mt76_connac_mcu_init_करोwnload(&dev->mt76, addr, len,
						    DL_MODE_NEED_RSP);
		अगर (ret) अणु
			dev_err(dev->mt76.dev, "Download request failed\n");
			जाओ out;
		पूर्ण

		ret = mt76_mcu_send_firmware(&dev->mt76, MCU_CMD_FW_SCATTER,
					     dl, len);
		अगर (ret) अणु
			dev_err(dev->mt76.dev, "Failed to send patch\n");
			जाओ out;
		पूर्ण
	पूर्ण

	ret = mt76_connac_mcu_start_patch(&dev->mt76);
	अगर (ret)
		dev_err(dev->mt76.dev, "Failed to start patch\n");

out:
	sem = mt76_connac_mcu_patch_sem_ctrl(&dev->mt76, false);
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

अटल u32 mt7921_mcu_gen_dl_mode(u8 feature_set, bool is_wa)
अणु
	u32 ret = 0;

	ret |= (feature_set & FW_FEATURE_SET_ENCRYPT) ?
	       (DL_MODE_ENCRYPT | DL_MODE_RESET_SEC_IV) : 0;
	ret |= (feature_set & FW_FEATURE_ENCRY_MODE) ?
	       DL_CONFIG_ENCRY_MODE_SEL : 0;
	ret |= FIELD_PREP(DL_MODE_KEY_IDX,
			  FIELD_GET(FW_FEATURE_SET_KEY_IDX, feature_set));
	ret |= DL_MODE_NEED_RSP;
	ret |= is_wa ? DL_MODE_WORKING_PDA_CR4 : 0;

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7921_mcu_send_ram_firmware(काष्ठा mt7921_dev *dev,
			     स्थिर काष्ठा mt7921_fw_trailer *hdr,
			     स्थिर u8 *data, bool is_wa)
अणु
	पूर्णांक i, offset = 0;
	u32 override = 0, option = 0;

	क्रम (i = 0; i < hdr->n_region; i++) अणु
		स्थिर काष्ठा mt7921_fw_region *region;
		पूर्णांक err;
		u32 len, addr, mode;

		region = (स्थिर काष्ठा mt7921_fw_region *)((स्थिर u8 *)hdr -
			 (hdr->n_region - i) * माप(*region));
		mode = mt7921_mcu_gen_dl_mode(region->feature_set, is_wa);
		len = le32_to_cpu(region->len);
		addr = le32_to_cpu(region->addr);

		अगर (region->feature_set & FW_FEATURE_OVERRIDE_ADDR)
			override = addr;

		err = mt76_connac_mcu_init_करोwnload(&dev->mt76, addr, len,
						    mode);
		अगर (err) अणु
			dev_err(dev->mt76.dev, "Download request failed\n");
			वापस err;
		पूर्ण

		err = mt76_mcu_send_firmware(&dev->mt76, MCU_CMD_FW_SCATTER,
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

	वापस mt76_connac_mcu_start_firmware(&dev->mt76, override, option);
पूर्ण

अटल पूर्णांक mt7921_load_ram(काष्ठा mt7921_dev *dev)
अणु
	स्थिर काष्ठा mt7921_fw_trailer *hdr;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;

	ret = request_firmware(&fw, MT7921_FIRMWARE_WM, dev->mt76.dev);
	अगर (ret)
		वापस ret;

	अगर (!fw || !fw->data || fw->size < माप(*hdr)) अणु
		dev_err(dev->mt76.dev, "Invalid firmware\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	hdr = (स्थिर काष्ठा mt7921_fw_trailer *)(fw->data + fw->size -
					माप(*hdr));

	dev_info(dev->mt76.dev, "WM Firmware Version: %.10s, Build Time: %.15s\n",
		 hdr->fw_ver, hdr->build_date);

	ret = mt7921_mcu_send_ram_firmware(dev, hdr, fw->data, false);
	अगर (ret) अणु
		dev_err(dev->mt76.dev, "Failed to start WM firmware\n");
		जाओ out;
	पूर्ण

	snम_लिखो(dev->mt76.hw->wiphy->fw_version,
		 माप(dev->mt76.hw->wiphy->fw_version),
		 "%.10s-%.15s", hdr->fw_ver, hdr->build_date);

out:
	release_firmware(fw);

	वापस ret;
पूर्ण

अटल पूर्णांक mt7921_load_firmware(काष्ठा mt7921_dev *dev)
अणु
	पूर्णांक ret;

	ret = mt76_get_field(dev, MT_CONN_ON_MISC, MT_TOP_MISC2_FW_N9_RDY);
	अगर (ret) अणु
		dev_dbg(dev->mt76.dev, "Firmware is already download\n");
		वापस -EIO;
	पूर्ण

	ret = mt7921_load_patch(dev);
	अगर (ret)
		वापस ret;

	ret = mt7921_load_ram(dev);
	अगर (ret)
		वापस ret;

	अगर (!mt76_poll_msec(dev, MT_CONN_ON_MISC, MT_TOP_MISC2_FW_N9_RDY,
			    MT_TOP_MISC2_FW_N9_RDY, 1500)) अणु
		dev_err(dev->mt76.dev, "Timeout for initializing firmware\n");

		वापस -EIO;
	पूर्ण

	mt76_queue_tx_cleanup(dev, dev->mt76.q_mcu[MT_MCUQ_FWDL], false);

#अगर_घोषित CONFIG_PM
	dev->mt76.hw->wiphy->wowlan = &mt76_connac_wowlan_support;
#पूर्ण_अगर /* CONFIG_PM */

	clear_bit(MT76_STATE_PM, &dev->mphy.state);

	dev_err(dev->mt76.dev, "Firmware init done\n");

	वापस 0;
पूर्ण

पूर्णांक mt7921_mcu_fw_log_2_host(काष्ठा mt7921_dev *dev, u8 ctrl)
अणु
	काष्ठा अणु
		u8 ctrl_val;
		u8 pad[3];
	पूर्ण data = अणु
		.ctrl_val = ctrl
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_CMD_FWLOG_2_HOST, &data,
				 माप(data), false);
पूर्ण

पूर्णांक mt7921_run_firmware(काष्ठा mt7921_dev *dev)
अणु
	पूर्णांक err;

	err = mt7921_driver_own(dev);
	अगर (err)
		वापस err;

	err = mt7921_load_firmware(dev);
	अगर (err)
		वापस err;

	set_bit(MT76_STATE_MCU_RUNNING, &dev->mphy.state);
	mt7921_mcu_fw_log_2_host(dev, 1);

	वापस 0;
पूर्ण

पूर्णांक mt7921_mcu_init(काष्ठा mt7921_dev *dev)
अणु
	अटल स्थिर काष्ठा mt76_mcu_ops mt7921_mcu_ops = अणु
		.headroom = माप(काष्ठा mt7921_mcu_txd),
		.mcu_skb_send_msg = mt7921_mcu_send_message,
		.mcu_parse_response = mt7921_mcu_parse_response,
		.mcu_restart = mt7921_mcu_restart,
	पूर्ण;

	dev->mt76.mcu_ops = &mt7921_mcu_ops;

	वापस mt7921_run_firmware(dev);
पूर्ण

व्योम mt7921_mcu_निकास(काष्ठा mt7921_dev *dev)
अणु
	mt7921_wfsys_reset(dev);
	skb_queue_purge(&dev->mt76.mcu.res_q);
पूर्ण

पूर्णांक mt7921_mcu_set_tx(काष्ठा mt7921_dev *dev, काष्ठा ieee80211_vअगर *vअगर)
अणु
#घोषणा WMM_AIFS_SET		BIT(0)
#घोषणा WMM_CW_MIN_SET		BIT(1)
#घोषणा WMM_CW_MAX_SET		BIT(2)
#घोषणा WMM_TXOP_SET		BIT(3)
#घोषणा WMM_PARAM_SET		GENMASK(3, 0)
#घोषणा TX_CMD_MODE		1
	काष्ठा edca अणु
		u8 queue;
		u8 set;
		u8 aअगरs;
		u8 cw_min;
		__le16 cw_max;
		__le16 txop;
	पूर्ण;
	काष्ठा mt7921_mcu_tx अणु
		u8 total;
		u8 action;
		u8 valid;
		u8 mode;

		काष्ठा edca edca[IEEE80211_NUM_ACS];
	पूर्ण __packed req = अणु
		.valid = true,
		.mode = TX_CMD_MODE,
		.total = IEEE80211_NUM_ACS,
	पूर्ण;
	काष्ठा mt7921_vअगर *mvअगर = (काष्ठा mt7921_vअगर *)vअगर->drv_priv;
	पूर्णांक ac;

	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++) अणु
		काष्ठा ieee80211_tx_queue_params *q = &mvअगर->queue_params[ac];
		काष्ठा edca *e = &req.edca[ac];

		e->set = WMM_PARAM_SET;
		e->queue = ac + mvअगर->mt76.wmm_idx * MT7921_MAX_WMM_SETS;
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
	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_EDCA_UPDATE, &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7921_mcu_set_chan_info(काष्ठा mt7921_phy *phy, पूर्णांक cmd)
अणु
	काष्ठा mt7921_dev *dev = phy->dev;
	काष्ठा cfg80211_chan_def *chandef = &phy->mt76->chandef;
	पूर्णांक freq1 = chandef->center_freq1;
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
		.bw = mt7921_mcu_chan_bw(chandef),
		.tx_streams_num = hweight8(phy->mt76->antenna_mask),
		.rx_streams = phy->mt76->antenna_mask,
		.band_idx = phy != &dev->phy,
		.channel_band = chandef->chan->band,
	पूर्ण;

	अगर (dev->mt76.hw->conf.flags & IEEE80211_CONF_OFFCHANNEL)
		req.चयन_reason = CH_SWITCH_SCAN_BYPASS_DPD;
	अन्यथा अगर ((chandef->chan->flags & IEEE80211_CHAN_RADAR) &&
		 chandef->chan->dfs_state != NL80211_DFS_AVAILABLE)
		req.चयन_reason = CH_SWITCH_DFS;
	अन्यथा
		req.चयन_reason = CH_SWITCH_NORMAL;

	अगर (cmd == MCU_EXT_CMD_CHANNEL_SWITCH)
		req.rx_streams = hweight8(req.rx_streams);

	अगर (chandef->width == NL80211_CHAN_WIDTH_80P80) अणु
		पूर्णांक freq2 = chandef->center_freq2;

		req.center_ch2 = ieee80211_frequency_to_channel(freq2);
	पूर्ण

	वापस mt76_mcu_send_msg(&dev->mt76, cmd, &req, माप(req), true);
पूर्ण

पूर्णांक mt7921_mcu_set_eeprom(काष्ठा mt7921_dev *dev)
अणु
	काष्ठा req_hdr अणु
		u8 buffer_mode;
		u8 क्रमmat;
		__le16 len;
	पूर्ण __packed req = अणु
		.buffer_mode = EE_MODE_EFUSE,
		.क्रमmat = EE_FORMAT_WHOLE,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_EFUSE_BUFFER_MODE,
				 &req, माप(req), true);
पूर्ण

पूर्णांक mt7921_mcu_get_eeprom(काष्ठा mt7921_dev *dev, u32 offset)
अणु
	काष्ठा mt7921_mcu_eeprom_info req = अणु
		.addr = cpu_to_le32(round_करोwn(offset, 16)),
	पूर्ण;
	काष्ठा mt7921_mcu_eeprom_info *res;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;
	u8 *buf;

	ret = mt76_mcu_send_and_get_msg(&dev->mt76, MCU_EXT_CMD_EFUSE_ACCESS, &req,
					माप(req), true, &skb);
	अगर (ret)
		वापस ret;

	res = (काष्ठा mt7921_mcu_eeprom_info *)skb->data;
	buf = dev->mt76.eeprom.data + le32_to_cpu(res->addr);
	स_नकल(buf, res->data, 16);
	dev_kमुक्त_skb(skb);

	वापस 0;
पूर्ण

u32 mt7921_get_wtbl_info(काष्ठा mt7921_dev *dev, u32 wlan_idx)
अणु
	काष्ठा mt7921_mcu_wlan_info wtbl_info = अणु
		.wlan_idx = cpu_to_le32(wlan_idx),
	पूर्ण;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	ret = mt76_mcu_send_and_get_msg(&dev->mt76, MCU_CMD_GET_WTBL,
					&wtbl_info, माप(wtbl_info), true,
					&skb);
	अगर (ret)
		वापस ret;

	mt7921_mcu_tx_rate_report(dev, skb, wlan_idx);
	dev_kमुक्त_skb(skb);

	वापस 0;
पूर्ण

पूर्णांक mt7921_mcu_uni_bss_ps(काष्ठा mt7921_dev *dev, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7921_vअगर *mvअगर = (काष्ठा mt7921_vअगर *)vअगर->drv_priv;
	काष्ठा अणु
		काष्ठा अणु
			u8 bss_idx;
			u8 pad[3];
		पूर्ण __packed hdr;
		काष्ठा ps_tlv अणु
			__le16 tag;
			__le16 len;
			u8 ps_state; /* 0: device awake
				      * 1: अटल घातer save
				      * 2: dynamic घातer saving
				      * 3: enter TWT घातer saving
				      * 4: leave TWT घातer saving
				      */
			u8 pad[3];
		पूर्ण __packed ps;
	पूर्ण __packed ps_req = अणु
		.hdr = अणु
			.bss_idx = mvअगर->mt76.idx,
		पूर्ण,
		.ps = अणु
			.tag = cpu_to_le16(UNI_BSS_INFO_PS),
			.len = cpu_to_le16(माप(काष्ठा ps_tlv)),
			.ps_state = vअगर->bss_conf.ps ? 2 : 0,
		पूर्ण,
	पूर्ण;

	अगर (vअगर->type != NL80211_IFTYPE_STATION)
		वापस -EOPNOTSUPP;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_UNI_CMD_BSS_INFO_UPDATE,
				 &ps_req, माप(ps_req), true);
पूर्ण

पूर्णांक mt7921_mcu_uni_bss_bcnft(काष्ठा mt7921_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
			     bool enable)
अणु
	काष्ठा mt7921_vअगर *mvअगर = (काष्ठा mt7921_vअगर *)vअगर->drv_priv;
	काष्ठा अणु
		काष्ठा अणु
			u8 bss_idx;
			u8 pad[3];
		पूर्ण __packed hdr;
		काष्ठा bcnft_tlv अणु
			__le16 tag;
			__le16 len;
			__le16 bcn_पूर्णांकerval;
			u8 dtim_period;
			u8 pad;
		पूर्ण __packed bcnft;
	पूर्ण __packed bcnft_req = अणु
		.hdr = अणु
			.bss_idx = mvअगर->mt76.idx,
		पूर्ण,
		.bcnft = अणु
			.tag = cpu_to_le16(UNI_BSS_INFO_BCNFT),
			.len = cpu_to_le16(माप(काष्ठा bcnft_tlv)),
			.bcn_पूर्णांकerval = cpu_to_le16(vअगर->bss_conf.beacon_पूर्णांक),
			.dtim_period = vअगर->bss_conf.dtim_period,
		पूर्ण,
	पूर्ण;

	अगर (vअगर->type != NL80211_IFTYPE_STATION)
		वापस 0;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_UNI_CMD_BSS_INFO_UPDATE,
				 &bcnft_req, माप(bcnft_req), true);
पूर्ण

पूर्णांक mt7921_mcu_set_bss_pm(काष्ठा mt7921_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
			  bool enable)
अणु
	काष्ठा mt7921_vअगर *mvअगर = (काष्ठा mt7921_vअगर *)vअगर->drv_priv;
	काष्ठा अणु
		u8 bss_idx;
		u8 dtim_period;
		__le16 aid;
		__le16 bcn_पूर्णांकerval;
		__le16 atim_winकरोw;
		u8 uapsd;
		u8 bmc_delivered_ac;
		u8 bmc_triggered_ac;
		u8 pad;
	पूर्ण req = अणु
		.bss_idx = mvअगर->mt76.idx,
		.aid = cpu_to_le16(vअगर->bss_conf.aid),
		.dtim_period = vअगर->bss_conf.dtim_period,
		.bcn_पूर्णांकerval = cpu_to_le16(vअगर->bss_conf.beacon_पूर्णांक),
	पूर्ण;
	काष्ठा अणु
		u8 bss_idx;
		u8 pad[3];
	पूर्ण req_hdr = अणु
		.bss_idx = mvअगर->mt76.idx,
	पूर्ण;
	पूर्णांक err;

	अगर (vअगर->type != NL80211_IFTYPE_STATION)
		वापस 0;

	err = mt76_mcu_send_msg(&dev->mt76, MCU_CMD_SET_BSS_ABORT, &req_hdr,
				माप(req_hdr), false);
	अगर (err < 0 || !enable)
		वापस err;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_CMD_SET_BSS_CONNECTED, &req,
				 माप(req), false);
पूर्ण

पूर्णांक mt7921_mcu_sta_add(काष्ठा mt7921_dev *dev, काष्ठा ieee80211_sta *sta,
		       काष्ठा ieee80211_vअगर *vअगर, bool enable)
अणु
	काष्ठा mt7921_vअगर *mvअगर = (काष्ठा mt7921_vअगर *)vअगर->drv_priv;
	पूर्णांक rssi = -ewma_rssi_पढ़ो(&mvअगर->rssi);
	काष्ठा mt76_sta_cmd_info info = अणु
		.sta = sta,
		.vअगर = vअगर,
		.enable = enable,
		.cmd = MCU_UNI_CMD_STA_REC_UPDATE,
		.rcpi = to_rcpi(rssi),
	पूर्ण;
	काष्ठा mt7921_sta *msta;

	msta = sta ? (काष्ठा mt7921_sta *)sta->drv_priv : शून्य;
	info.wcid = msta ? &msta->wcid : &mvअगर->sta.wcid;

	वापस mt76_connac_mcu_add_sta_cmd(&dev->mphy, &info);
पूर्ण

पूर्णांक mt7921_mcu_drv_pmctrl(काष्ठा mt7921_dev *dev)
अणु
	काष्ठा mt76_phy *mphy = &dev->mt76.phy;
	काष्ठा mt76_connac_pm *pm = &dev->pm;
	पूर्णांक i, err = 0;

	mutex_lock(&pm->mutex);

	अगर (!test_bit(MT76_STATE_PM, &mphy->state))
		जाओ out;

	क्रम (i = 0; i < MT7921_DRV_OWN_RETRY_COUNT; i++) अणु
		mt76_wr(dev, MT_CONN_ON_LPCTL, PCIE_LPCR_HOST_CLR_OWN);
		अगर (mt76_poll_msec(dev, MT_CONN_ON_LPCTL,
				   PCIE_LPCR_HOST_OWN_SYNC, 0, 50))
			अवरोध;
	पूर्ण

	अगर (i == MT7921_DRV_OWN_RETRY_COUNT) अणु
		dev_err(dev->mt76.dev, "driver own failed\n");
		err = -EIO;
		जाओ out;
	पूर्ण

	mt7921_wpdma_reinit_cond(dev);
	clear_bit(MT76_STATE_PM, &mphy->state);

	pm->stats.last_wake_event = jअगरfies;
	pm->stats.करोze_समय += pm->stats.last_wake_event -
			       pm->stats.last_करोze_event;
out:
	mutex_unlock(&pm->mutex);

	अगर (err)
		mt7921_reset(&dev->mt76);

	वापस err;
पूर्ण

पूर्णांक mt7921_mcu_fw_pmctrl(काष्ठा mt7921_dev *dev)
अणु
	काष्ठा mt76_phy *mphy = &dev->mt76.phy;
	काष्ठा mt76_connac_pm *pm = &dev->pm;
	पूर्णांक i, err = 0;

	mutex_lock(&pm->mutex);

	अगर (mt76_connac_skip_fw_pmctrl(mphy, pm))
		जाओ out;

	क्रम (i = 0; i < MT7921_DRV_OWN_RETRY_COUNT; i++) अणु
		mt76_wr(dev, MT_CONN_ON_LPCTL, PCIE_LPCR_HOST_SET_OWN);
		अगर (mt76_poll_msec(dev, MT_CONN_ON_LPCTL,
				   PCIE_LPCR_HOST_OWN_SYNC, 4, 50))
			अवरोध;
	पूर्ण

	अगर (i == MT7921_DRV_OWN_RETRY_COUNT) अणु
		dev_err(dev->mt76.dev, "firmware own failed\n");
		clear_bit(MT76_STATE_PM, &mphy->state);
		err = -EIO;
	पूर्ण

	pm->stats.last_करोze_event = jअगरfies;
	pm->stats.awake_समय += pm->stats.last_करोze_event -
				pm->stats.last_wake_event;
out:
	mutex_unlock(&pm->mutex);

	अगर (err)
		mt7921_reset(&dev->mt76);

	वापस err;
पूर्ण

व्योम
mt7921_pm_पूर्णांकerface_iter(व्योम *priv, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7921_phy *phy = priv;
	काष्ठा mt7921_dev *dev = phy->dev;
	पूर्णांक ret;

	अगर (dev->pm.enable)
		ret = mt7921_mcu_uni_bss_bcnft(dev, vअगर, true);
	अन्यथा
		ret = mt7921_mcu_set_bss_pm(dev, vअगर, false);

	अगर (ret)
		वापस;

	अगर (dev->pm.enable) अणु
		vअगर->driver_flags |= IEEE80211_VIF_BEACON_FILTER;
		mt76_set(dev, MT_WF_RFCR(0), MT_WF_RFCR_DROP_OTHER_BEACON);
	पूर्ण अन्यथा अणु
		vअगर->driver_flags &= ~IEEE80211_VIF_BEACON_FILTER;
		mt76_clear(dev, MT_WF_RFCR(0), MT_WF_RFCR_DROP_OTHER_BEACON);
	पूर्ण
पूर्ण

पूर्णांक mt7921_get_txpwr_info(काष्ठा mt7921_dev *dev, काष्ठा mt7921_txpwr *txpwr)
अणु
	काष्ठा mt7921_txpwr_event *event;
	काष्ठा mt7921_txpwr_req req = अणु
		.dbdc_idx = 0,
	पूर्ण;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	ret = mt76_mcu_send_and_get_msg(&dev->mt76, MCU_CMD_GET_TXPWR,
					&req, माप(req), true, &skb);
	अगर (ret)
		वापस ret;

	event = (काष्ठा mt7921_txpwr_event *)skb->data;
	WARN_ON(skb->len != le16_to_cpu(event->len));
	स_नकल(txpwr, &event->txpwr, माप(event->txpwr));

	dev_kमुक्त_skb(skb);

	वापस 0;
पूर्ण
