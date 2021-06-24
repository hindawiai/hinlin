<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 * Copyright (C) 2018 Stanislaw Gruszka <stf_xl@wp.pl>
 */

#अगर_अघोषित __MT76X02_MAC_H
#घोषणा __MT76X02_MAC_H

काष्ठा mt76x02_dev;

काष्ठा mt76x02_tx_status अणु
	u8 valid:1;
	u8 success:1;
	u8 aggr:1;
	u8 ack_req:1;
	u8 wcid;
	u8 pktid;
	u8 retry;
	u16 rate;
पूर्ण __packed __aligned(2);

#घोषणा MT_VIF_WCID(_n)		(254 - ((_n) & 7))
#घोषणा MT_MAX_VIFS		8

#घोषणा MT_PKTID_RATE		GENMASK(4, 0)
#घोषणा MT_PKTID_AC		GENMASK(6, 5)

काष्ठा mt76x02_vअगर अणु
	काष्ठा mt76_wcid group_wcid; /* must be first */
	u8 idx;
पूर्ण;

DECLARE_EWMA(pktlen, 8, 8);

काष्ठा mt76x02_sta अणु
	काष्ठा mt76_wcid wcid; /* must be first */

	काष्ठा mt76x02_vअगर *vअगर;
	काष्ठा mt76x02_tx_status status;
	पूर्णांक n_frames;

	काष्ठा ewma_pktlen pktlen;
पूर्ण;

#घोषणा MT_RXINFO_BA			BIT(0)
#घोषणा MT_RXINFO_DATA			BIT(1)
#घोषणा MT_RXINFO_शून्य			BIT(2)
#घोषणा MT_RXINFO_FRAG			BIT(3)
#घोषणा MT_RXINFO_UNICAST		BIT(4)
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
#घोषणा MT_RXINFO_SW_FTYPE0		BIT(22)
#घोषणा MT_RXINFO_SW_FTYPE1		BIT(23)
#घोषणा MT_RXINFO_PROBE_RESP		BIT(24)
#घोषणा MT_RXINFO_BEACON		BIT(25)
#घोषणा MT_RXINFO_DISASSOC		BIT(26)
#घोषणा MT_RXINFO_DEAUTH		BIT(27)
#घोषणा MT_RXINFO_ACTION		BIT(28)
#घोषणा MT_RXINFO_TCP_SUM_ERR		BIT(30)
#घोषणा MT_RXINFO_IP_SUM_ERR		BIT(31)

#घोषणा MT_RXWI_CTL_WCID		GENMASK(7, 0)
#घोषणा MT_RXWI_CTL_KEY_IDX		GENMASK(9, 8)
#घोषणा MT_RXWI_CTL_BSS_IDX		GENMASK(12, 10)
#घोषणा MT_RXWI_CTL_UDF			GENMASK(15, 13)
#घोषणा MT_RXWI_CTL_MPDU_LEN		GENMASK(29, 16)
#घोषणा MT_RXWI_CTL_खातापूर्ण			BIT(31)

#घोषणा MT_RXWI_TID			GENMASK(3, 0)
#घोषणा MT_RXWI_SN			GENMASK(15, 4)

#घोषणा MT_RXWI_RATE_INDEX		GENMASK(5, 0)
#घोषणा MT_RXWI_RATE_LDPC		BIT(6)
#घोषणा MT_RXWI_RATE_BW			GENMASK(8, 7)
#घोषणा MT_RXWI_RATE_SGI		BIT(9)
#घोषणा MT_RXWI_RATE_STBC		BIT(10)
#घोषणा MT_RXWI_RATE_LDPC_EXSYM		BIT(11)
#घोषणा MT_RXWI_RATE_PHY		GENMASK(15, 13)

#घोषणा MT_RATE_INDEX_VHT_IDX		GENMASK(3, 0)
#घोषणा MT_RATE_INDEX_VHT_NSS		GENMASK(5, 4)

काष्ठा mt76x02_rxwi अणु
	__le32 rxinfo;

	__le32 ctl;

	__le16 tid_sn;
	__le16 rate;

	u8 rssi[4];

	__le32 bbp_rxinfo[4];
पूर्ण;

#घोषणा MT_TX_PWR_ADJ			GENMASK(3, 0)

क्रमागत mt76x2_phy_bandwidth अणु
	MT_PHY_BW_20,
	MT_PHY_BW_40,
	MT_PHY_BW_80,
पूर्ण;

#घोषणा MT_TXWI_FLAGS_FRAG		BIT(0)
#घोषणा MT_TXWI_FLAGS_MMPS		BIT(1)
#घोषणा MT_TXWI_FLAGS_CFACK		BIT(2)
#घोषणा MT_TXWI_FLAGS_TS		BIT(3)
#घोषणा MT_TXWI_FLAGS_AMPDU		BIT(4)
#घोषणा MT_TXWI_FLAGS_MPDU_DENSITY	GENMASK(7, 5)
#घोषणा MT_TXWI_FLAGS_TXOP		GENMASK(9, 8)
#घोषणा MT_TXWI_FLAGS_NDPS		BIT(10)
#घोषणा MT_TXWI_FLAGS_RTSBWSIG		BIT(11)
#घोषणा MT_TXWI_FLAGS_NDP_BW		GENMASK(13, 12)
#घोषणा MT_TXWI_FLAGS_SOUND		BIT(14)
#घोषणा MT_TXWI_FLAGS_TX_RATE_LUT	BIT(15)

#घोषणा MT_TXWI_ACK_CTL_REQ		BIT(0)
#घोषणा MT_TXWI_ACK_CTL_NSEQ		BIT(1)
#घोषणा MT_TXWI_ACK_CTL_BA_WINDOW	GENMASK(7, 2)

काष्ठा mt76x02_txwi अणु
	__le16 flags;
	__le16 rate;
	u8 ack_ctl;
	u8 wcid;
	__le16 len_ctl;
	__le32 iv;
	__le32 eiv;
	u8 aid;
	u8 txstream;
	u8 ctl2;
	u8 pktid;
पूर्ण __packed __aligned(4);

अटल अंतरभूत bool mt76x02_रुको_क्रम_mac(काष्ठा mt76_dev *dev)
अणु
	स्थिर u32 MAC_CSR0 = 0x1000;
	पूर्णांक i;

	क्रम (i = 0; i < 500; i++) अणु
		अगर (test_bit(MT76_REMOVED, &dev->phy.state))
			वापस false;

		चयन (dev->bus->rr(dev, MAC_CSR0)) अणु
		हाल 0:
		हाल ~0:
			अवरोध;
		शेष:
			वापस true;
		पूर्ण
		usleep_range(5000, 10000);
	पूर्ण
	वापस false;
पूर्ण

व्योम mt76x02_mac_reset_counters(काष्ठा mt76x02_dev *dev);
व्योम mt76x02_mac_set_लघु_preamble(काष्ठा mt76x02_dev *dev, bool enable);
पूर्णांक mt76x02_mac_shared_key_setup(काष्ठा mt76x02_dev *dev, u8 vअगर_idx,
				 u8 key_idx, काष्ठा ieee80211_key_conf *key);
पूर्णांक mt76x02_mac_wcid_set_key(काष्ठा mt76x02_dev *dev, u8 idx,
			     काष्ठा ieee80211_key_conf *key);
व्योम mt76x02_mac_wcid_sync_pn(काष्ठा mt76x02_dev *dev, u8 idx,
			      काष्ठा ieee80211_key_conf *key);
व्योम mt76x02_mac_wcid_setup(काष्ठा mt76x02_dev *dev, u8 idx, u8 vअगर_idx,
			    u8 *mac);
व्योम mt76x02_mac_wcid_set_drop(काष्ठा mt76x02_dev *dev, u8 idx, bool drop);
व्योम mt76x02_mac_wcid_set_rate(काष्ठा mt76x02_dev *dev, काष्ठा mt76_wcid *wcid,
			       स्थिर काष्ठा ieee80211_tx_rate *rate);
bool mt76x02_mac_load_tx_status(काष्ठा mt76x02_dev *dev,
				काष्ठा mt76x02_tx_status *stat);
व्योम mt76x02_send_tx_status(काष्ठा mt76x02_dev *dev,
			    काष्ठा mt76x02_tx_status *stat, u8 *update);
पूर्णांक mt76x02_mac_process_rx(काष्ठा mt76x02_dev *dev, काष्ठा sk_buff *skb,
			   व्योम *rxi);
व्योम mt76x02_mac_set_tx_protection(काष्ठा mt76x02_dev *dev, bool legacy_prot,
				   पूर्णांक ht_mode);
व्योम mt76x02_mac_set_rts_thresh(काष्ठा mt76x02_dev *dev, u32 val);
व्योम mt76x02_mac_setaddr(काष्ठा mt76x02_dev *dev, स्थिर u8 *addr);
व्योम mt76x02_mac_ग_लिखो_txwi(काष्ठा mt76x02_dev *dev, काष्ठा mt76x02_txwi *txwi,
			    काष्ठा sk_buff *skb, काष्ठा mt76_wcid *wcid,
			    काष्ठा ieee80211_sta *sta, पूर्णांक len);
व्योम mt76x02_mac_poll_tx_status(काष्ठा mt76x02_dev *dev, bool irq);
व्योम mt76x02_tx_complete_skb(काष्ठा mt76_dev *mdev, काष्ठा mt76_queue_entry *e);
व्योम mt76x02_update_channel(काष्ठा mt76_dev *mdev);
व्योम mt76x02_mac_work(काष्ठा work_काष्ठा *work);

व्योम mt76x02_mac_cc_reset(काष्ठा mt76x02_dev *dev);
व्योम mt76x02_mac_set_bssid(काष्ठा mt76x02_dev *dev, u8 idx, स्थिर u8 *addr);
व्योम mt76x02_mac_set_beacon(काष्ठा mt76x02_dev *dev, काष्ठा sk_buff *skb);
व्योम mt76x02_mac_set_beacon_enable(काष्ठा mt76x02_dev *dev,
				   काष्ठा ieee80211_vअगर *vअगर, bool enable);

व्योम mt76x02_edcca_init(काष्ठा mt76x02_dev *dev);
#पूर्ण_अगर
