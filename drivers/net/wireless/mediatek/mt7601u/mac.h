<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 */

#अगर_अघोषित __MT76_MAC_H
#घोषणा __MT76_MAC_H

काष्ठा mt76_tx_status अणु
	u8 valid:1;
	u8 success:1;
	u8 aggr:1;
	u8 ack_req:1;
	u8 is_probe:1;
	u8 wcid;
	u8 pktid;
	u8 retry;
	u16 rate;
पूर्ण __packed __aligned(2);

/* Note: values in original "RSSI" and "SNR" fields are not actually what they
 *	 are called क्रम MT7601U, names used by this driver are educated guesses
 *	 (see venकरोr mac/ral_omac.c).
 */
काष्ठा mt7601u_rxwi अणु
	__le32 rxinfo;

	__le32 ctl;

	__le16 frag_sn;
	__le16 rate;

	u8 unknown;
	u8 zero[3];

	u8 snr;
	u8 ant;
	u8 gain;
	u8 freq_off;

	__le32 resv2;
	__le32 expert_ant;
पूर्ण __packed __aligned(4);

#घोषणा MT_RXINFO_BA			BIT(0)
#घोषणा MT_RXINFO_DATA			BIT(1)
#घोषणा MT_RXINFO_शून्य			BIT(2)
#घोषणा MT_RXINFO_FRAG			BIT(3)
#घोषणा MT_RXINFO_U2M			BIT(4)
#घोषणा MT_RXINFO_MULTICAST		BIT(5)
#घोषणा MT_RXINFO_BROADCAST		BIT(6)
#घोषणा MT_RXINFO_MYBSS			BIT(7)
#घोषणा MT_RXINFO_CRCERR		BIT(8)
#घोषणा MT_RXINFO_ICVERR		BIT(9)
#घोषणा MT_RXINFO_MICERR		BIT(10)
#घोषणा MT_RXINFO_AMSDU			BIT(11)
#घोषणा MT_RXINFO_HTC			BIT(12)
#घोषणा MT_RXINFO_RSSI			BIT(13)
#घोषणा MT_RXINFO_L2PAD			BIT(14)
#घोषणा MT_RXINFO_AMPDU			BIT(15)
#घोषणा MT_RXINFO_DECRYPT		BIT(16)
#घोषणा MT_RXINFO_BSSIDX3		BIT(17)
#घोषणा MT_RXINFO_WAPI_KEY		BIT(18)
#घोषणा MT_RXINFO_PN_LEN		GENMASK(21, 19)
#घोषणा MT_RXINFO_SW_PKT_80211		BIT(22)
#घोषणा MT_RXINFO_TCP_SUM_BYPASS	BIT(28)
#घोषणा MT_RXINFO_IP_SUM_BYPASS		BIT(29)
#घोषणा MT_RXINFO_TCP_SUM_ERR		BIT(30)
#घोषणा MT_RXINFO_IP_SUM_ERR		BIT(31)

#घोषणा MT_RXWI_CTL_WCID		GENMASK(7, 0)
#घोषणा MT_RXWI_CTL_KEY_IDX		GENMASK(9, 8)
#घोषणा MT_RXWI_CTL_BSS_IDX		GENMASK(12, 10)
#घोषणा MT_RXWI_CTL_UDF			GENMASK(15, 13)
#घोषणा MT_RXWI_CTL_MPDU_LEN		GENMASK(27, 16)
#घोषणा MT_RXWI_CTL_TID			GENMASK(31, 28)

#घोषणा MT_RXWI_FRAG			GENMASK(3, 0)
#घोषणा MT_RXWI_SN			GENMASK(15, 4)

#घोषणा MT_RXWI_RATE_MCS		GENMASK(6, 0)
#घोषणा MT_RXWI_RATE_BW			BIT(7)
#घोषणा MT_RXWI_RATE_SGI		BIT(8)
#घोषणा MT_RXWI_RATE_STBC		GENMASK(10, 9)
#घोषणा MT_RXWI_RATE_ETXBF		BIT(11)
#घोषणा MT_RXWI_RATE_SND		BIT(12)
#घोषणा MT_RXWI_RATE_ITXBF		BIT(13)
#घोषणा MT_RXWI_RATE_PHY		GENMASK(15, 14)

#घोषणा MT_RXWI_GAIN_RSSI_VAL		GENMASK(5, 0)
#घोषणा MT_RXWI_GAIN_RSSI_LNA_ID	GENMASK(7, 6)
#घोषणा MT_RXWI_ANT_AUX_LNA		BIT(7)

#घोषणा MT_RXWI_EANT_ENC_ANT_ID		GENMASK(7, 0)

क्रमागत mt76_phy_type अणु
	MT_PHY_TYPE_CCK,
	MT_PHY_TYPE_OFDM,
	MT_PHY_TYPE_HT,
	MT_PHY_TYPE_HT_GF,
पूर्ण;

क्रमागत mt76_phy_bandwidth अणु
	MT_PHY_BW_20,
	MT_PHY_BW_40,
पूर्ण;

काष्ठा mt76_txwi अणु
	__le16 flags;
	__le16 rate_ctl;

	u8 ack_ctl;
	u8 wcid;
	__le16 len_ctl;

	__le32 iv;

	__le32 eiv;

	u8 aid;
	u8 txstream;
	__le16 ctl;
पूर्ण __packed __aligned(4);

#घोषणा MT_TXWI_FLAGS_FRAG		BIT(0)
#घोषणा MT_TXWI_FLAGS_MMPS		BIT(1)
#घोषणा MT_TXWI_FLAGS_CFACK		BIT(2)
#घोषणा MT_TXWI_FLAGS_TS		BIT(3)
#घोषणा MT_TXWI_FLAGS_AMPDU		BIT(4)
#घोषणा MT_TXWI_FLAGS_MPDU_DENSITY	GENMASK(7, 5)
#घोषणा MT_TXWI_FLAGS_TXOP		GENMASK(9, 8)
#घोषणा MT_TXWI_FLAGS_CWMIN		GENMASK(12, 10)
#घोषणा MT_TXWI_FLAGS_NO_RATE_FALLBACK	BIT(13)
#घोषणा MT_TXWI_FLAGS_TX_RPT		BIT(14)
#घोषणा MT_TXWI_FLAGS_TX_RATE_LUT	BIT(15)

#घोषणा MT_TXWI_RATE_MCS		GENMASK(6, 0)
#घोषणा MT_TXWI_RATE_BW			BIT(7)
#घोषणा MT_TXWI_RATE_SGI		BIT(8)
#घोषणा MT_TXWI_RATE_STBC		GENMASK(10, 9)
#घोषणा MT_TXWI_RATE_PHY_MODE		GENMASK(15, 14)

#घोषणा MT_TXWI_ACK_CTL_REQ		BIT(0)
#घोषणा MT_TXWI_ACK_CTL_NSEQ		BIT(1)
#घोषणा MT_TXWI_ACK_CTL_BA_WINDOW	GENMASK(7, 2)

#घोषणा MT_TXWI_LEN_BYTE_CNT		GENMASK(11, 0)
#घोषणा MT_TXWI_LEN_PKTID		GENMASK(15, 12)

#घोषणा MT_TXWI_CTL_TX_POWER_ADJ	GENMASK(3, 0)
#घोषणा MT_TXWI_CTL_CHAN_CHECK_PKT	BIT(4)
#घोषणा MT_TXWI_CTL_PIFS_REV		BIT(6)

u32 mt76_mac_process_rx(काष्ठा mt7601u_dev *dev, काष्ठा sk_buff *skb,
			u8 *data, व्योम *rxi);
पूर्णांक mt76_mac_wcid_set_key(काष्ठा mt7601u_dev *dev, u8 idx,
			  काष्ठा ieee80211_key_conf *key);
व्योम mt76_mac_wcid_set_rate(काष्ठा mt7601u_dev *dev, काष्ठा mt76_wcid *wcid,
			    स्थिर काष्ठा ieee80211_tx_rate *rate);

पूर्णांक mt76_mac_shared_key_setup(काष्ठा mt7601u_dev *dev, u8 vअगर_idx, u8 key_idx,
			      काष्ठा ieee80211_key_conf *key);
u16 mt76_mac_tx_rate_val(काष्ठा mt7601u_dev *dev,
			 स्थिर काष्ठा ieee80211_tx_rate *rate, u8 *nss_val);
काष्ठा mt76_tx_status
mt7601u_mac_fetch_tx_status(काष्ठा mt7601u_dev *dev);
व्योम mt76_send_tx_status(काष्ठा mt7601u_dev *dev, काष्ठा mt76_tx_status *stat);
व्योम mt7601u_set_macaddr(काष्ठा mt7601u_dev *dev, स्थिर u8 *addr);

#पूर्ण_अगर
