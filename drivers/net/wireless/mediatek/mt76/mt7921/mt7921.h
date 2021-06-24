<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/* Copyright (C) 2020 MediaTek Inc. */

#अगर_अघोषित __MT7921_H
#घोषणा __MT7921_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kसमय.स>
#समावेश "../mt76_connac_mcu.h"
#समावेश "regs.h"

#घोषणा MT7921_MAX_INTERFACES		4
#घोषणा MT7921_MAX_WMM_SETS		4
#घोषणा MT7921_WTBL_SIZE		20
#घोषणा MT7921_WTBL_RESERVED		(MT7921_WTBL_SIZE - 1)
#घोषणा MT7921_WTBL_STA			(MT7921_WTBL_RESERVED - \
					 MT7921_MAX_INTERFACES)

#घोषणा MT7921_PM_TIMEOUT		(HZ / 12)
#घोषणा MT7921_HW_SCAN_TIMEOUT		(HZ / 10)
#घोषणा MT7921_WATCHDOG_TIME		(HZ / 4)
#घोषणा MT7921_RESET_TIMEOUT		(30 * HZ)

#घोषणा MT7921_TX_RING_SIZE		2048
#घोषणा MT7921_TX_MCU_RING_SIZE		256
#घोषणा MT7921_TX_FWDL_RING_SIZE	128

#घोषणा MT7921_RX_RING_SIZE		1536
#घोषणा MT7921_RX_MCU_RING_SIZE		512

#घोषणा MT7921_DRV_OWN_RETRY_COUNT	10

#घोषणा MT7921_FIRMWARE_WM		"mediatek/WIFI_RAM_CODE_MT7961_1.bin"
#घोषणा MT7921_ROM_PATCH		"mediatek/WIFI_MT7961_patch_mcu_1_2_hdr.bin"

#घोषणा MT7921_EEPROM_SIZE		3584
#घोषणा MT7921_TOKEN_SIZE		8192

#घोषणा MT7921_CFEND_RATE_DEFAULT	0x49	/* OFDM 24M */
#घोषणा MT7921_CFEND_RATE_11B		0x03	/* 11B LP, 11M */
#घोषणा MT7921_5G_RATE_DEFAULT		0x4b	/* OFDM 6M */
#घोषणा MT7921_2G_RATE_DEFAULT		0x0	/* CCK 1M */

#घोषणा MT7921_SKU_RATE_NUM		161
#घोषणा MT7921_SKU_MAX_DELTA_IDX	MT7921_SKU_RATE_NUM
#घोषणा MT7921_SKU_TABLE_SIZE		(MT7921_SKU_RATE_NUM + 1)

#घोषणा to_rssi(field, rxv)		((FIELD_GET(field, rxv) - 220) / 2)
#घोषणा to_rcpi(rssi)			(2 * (rssi) + 220)

काष्ठा mt7921_vअगर;
काष्ठा mt7921_sta;

क्रमागत mt7921_txq_id अणु
	MT7921_TXQ_BAND0,
	MT7921_TXQ_BAND1,
	MT7921_TXQ_FWDL = 16,
	MT7921_TXQ_MCU_WM,
पूर्ण;

क्रमागत mt7921_rxq_id अणु
	MT7921_RXQ_BAND0 = 0,
	MT7921_RXQ_BAND1,
	MT7921_RXQ_MCU_WM = 0,
पूर्ण;

काष्ठा mt7921_sta_stats अणु
	काष्ठा rate_info prob_rate;
	काष्ठा rate_info tx_rate;

	अचिन्हित दीर्घ per;
	अचिन्हित दीर्घ changed;
	अचिन्हित दीर्घ jअगरfies;
पूर्ण;

काष्ठा mt7921_sta_key_conf अणु
	s8 keyidx;
	u8 key[16];
पूर्ण;

काष्ठा mt7921_sta अणु
	काष्ठा mt76_wcid wcid; /* must be first */

	काष्ठा mt7921_vअगर *vअगर;

	काष्ठा list_head stats_list;
	काष्ठा list_head poll_list;
	u32 airसमय_ac[8];

	काष्ठा mt7921_sta_stats stats;

	अचिन्हित दीर्घ ampdu_state;

	काष्ठा mt7921_sta_key_conf bip;
पूर्ण;

DECLARE_EWMA(rssi, 10, 8);

काष्ठा mt7921_vअगर अणु
	काष्ठा mt76_vअगर mt76; /* must be first */

	काष्ठा mt7921_sta sta;
	काष्ठा mt7921_phy *phy;

	काष्ठा ewma_rssi rssi;

	काष्ठा ieee80211_tx_queue_params queue_params[IEEE80211_NUM_ACS];
पूर्ण;

काष्ठा mib_stats अणु
	u32 ack_fail_cnt;
	u32 fcs_err_cnt;
	u32 rts_cnt;
	u32 rts_retries_cnt;
	u32 ba_miss_cnt;
पूर्ण;

काष्ठा mt7921_phy अणु
	काष्ठा mt76_phy *mt76;
	काष्ठा mt7921_dev *dev;

	काष्ठा ieee80211_sband_अगरtype_data अगरtype[2][NUM_NL80211_IFTYPES];

	काष्ठा ieee80211_vअगर *monitor_vअगर;

	u32 rxfilter;
	u64 omac_mask;

	u16 noise;

	s16 coverage_class;
	u8 slotसमय;

	u32 rx_ampdu_ts;
	u32 ampdu_ref;

	काष्ठा mib_stats mib;
	काष्ठा list_head stats_list;

	u8 sta_work_count;

	काष्ठा sk_buff_head scan_event_list;
	काष्ठा delayed_work scan_work;
पूर्ण;

काष्ठा mt7921_dev अणु
	जोड़ अणु /* must be first */
		काष्ठा mt76_dev mt76;
		काष्ठा mt76_phy mphy;
	पूर्ण;

	स्थिर काष्ठा mt76_bus_ops *bus_ops;
	काष्ठा mt7921_phy phy;
	काष्ठा tasklet_काष्ठा irq_tasklet;

	u16 chainmask;

	काष्ठा work_काष्ठा reset_work;

	काष्ठा list_head sta_poll_list;
	spinlock_t sta_poll_lock;

	u8 fw_debug;

	काष्ठा mt76_connac_pm pm;
	काष्ठा mt76_connac_coredump coredump;
पूर्ण;

क्रमागत अणु
	TXPWR_USER,
	TXPWR_EEPROM,
	TXPWR_MAC,
	TXPWR_MAX_NUM,
पूर्ण;

काष्ठा mt7921_txpwr अणु
	u8 ch;
	u8 rsv[3];
	काष्ठा अणु
		u8 ch;
		u8 cck[4];
		u8 ofdm[8];
		u8 ht20[8];
		u8 ht40[9];
		u8 vht20[12];
		u8 vht40[12];
		u8 vht80[12];
		u8 vht160[12];
		u8 he26[12];
		u8 he52[12];
		u8 he106[12];
		u8 he242[12];
		u8 he484[12];
		u8 he996[12];
		u8 he996x2[12];
	पूर्ण data[TXPWR_MAX_NUM];
पूर्ण;

क्रमागत अणु
	MT_LMAC_AC00,
	MT_LMAC_AC01,
	MT_LMAC_AC02,
	MT_LMAC_AC03,
	MT_LMAC_ALTX0 = 0x10,
	MT_LMAC_BMC0,
	MT_LMAC_BCN0,
पूर्ण;

अटल अंतरभूत काष्ठा mt7921_phy *
mt7921_hw_phy(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt76_phy *phy = hw->priv;

	वापस phy->priv;
पूर्ण

अटल अंतरभूत काष्ठा mt7921_dev *
mt7921_hw_dev(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt76_phy *phy = hw->priv;

	वापस container_of(phy->dev, काष्ठा mt7921_dev, mt76);
पूर्ण

#घोषणा mt7921_mutex_acquire(dev)	\
	mt76_connac_mutex_acquire(&(dev)->mt76, &(dev)->pm)
#घोषणा mt7921_mutex_release(dev)	\
	mt76_connac_mutex_release(&(dev)->mt76, &(dev)->pm)

अटल अंतरभूत u8 mt7921_lmac_mapping(काष्ठा mt7921_dev *dev, u8 ac)
अणु
	/* LMAC uses the reverse order of mac80211 AC indexes */
	वापस 3 - ac;
पूर्ण

बाह्य स्थिर काष्ठा ieee80211_ops mt7921_ops;
बाह्य काष्ठा pci_driver mt7921_pci_driver;

u32 mt7921_reg_map(काष्ठा mt7921_dev *dev, u32 addr);

पूर्णांक __mt7921_start(काष्ठा mt7921_phy *phy);
पूर्णांक mt7921_रेजिस्टर_device(काष्ठा mt7921_dev *dev);
व्योम mt7921_unरेजिस्टर_device(काष्ठा mt7921_dev *dev);
पूर्णांक mt7921_eeprom_init(काष्ठा mt7921_dev *dev);
व्योम mt7921_eeprom_parse_band_config(काष्ठा mt7921_phy *phy);
पूर्णांक mt7921_eeprom_get_target_घातer(काष्ठा mt7921_dev *dev,
				   काष्ठा ieee80211_channel *chan,
				   u8 chain_idx);
व्योम mt7921_eeprom_init_sku(काष्ठा mt7921_dev *dev);
पूर्णांक mt7921_dma_init(काष्ठा mt7921_dev *dev);
पूर्णांक mt7921_wpdma_reset(काष्ठा mt7921_dev *dev, bool क्रमce);
पूर्णांक mt7921_wpdma_reinit_cond(काष्ठा mt7921_dev *dev);
व्योम mt7921_dma_cleanup(काष्ठा mt7921_dev *dev);
पूर्णांक mt7921_run_firmware(काष्ठा mt7921_dev *dev);
पूर्णांक mt7921_mcu_init(काष्ठा mt7921_dev *dev);
पूर्णांक mt7921_mcu_add_key(काष्ठा mt7921_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा mt7921_sta *msta, काष्ठा ieee80211_key_conf *key,
		       क्रमागत set_key_cmd cmd);
पूर्णांक mt7921_set_channel(काष्ठा mt7921_phy *phy);
पूर्णांक mt7921_mcu_sta_add(काष्ठा mt7921_dev *dev, काष्ठा ieee80211_sta *sta,
		       काष्ठा ieee80211_vअगर *vअगर, bool enable);
पूर्णांक mt7921_mcu_set_chan_info(काष्ठा mt7921_phy *phy, पूर्णांक cmd);
पूर्णांक mt7921_mcu_set_tx(काष्ठा mt7921_dev *dev, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक mt7921_mcu_set_eeprom(काष्ठा mt7921_dev *dev);
पूर्णांक mt7921_mcu_get_eeprom(काष्ठा mt7921_dev *dev, u32 offset);
पूर्णांक mt7921_mcu_get_rx_rate(काष्ठा mt7921_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta, काष्ठा rate_info *rate);
पूर्णांक mt7921_mcu_fw_log_2_host(काष्ठा mt7921_dev *dev, u8 ctrl);
व्योम mt7921_mcu_rx_event(काष्ठा mt7921_dev *dev, काष्ठा sk_buff *skb);
व्योम mt7921_mcu_निकास(काष्ठा mt7921_dev *dev);

अटल अंतरभूत व्योम mt7921_irq_enable(काष्ठा mt7921_dev *dev, u32 mask)
अणु
	mt76_set_irq_mask(&dev->mt76, 0, 0, mask);

	tasklet_schedule(&dev->irq_tasklet);
पूर्ण

अटल अंतरभूत u32
mt7921_reg_map_l1(काष्ठा mt7921_dev *dev, u32 addr)
अणु
	u32 offset = FIELD_GET(MT_HIF_REMAP_L1_OFFSET, addr);
	u32 base = FIELD_GET(MT_HIF_REMAP_L1_BASE, addr);

	mt76_rmw_field(dev, MT_HIF_REMAP_L1, MT_HIF_REMAP_L1_MASK, base);
	/* use पढ़ो to push ग_लिखो */
	mt76_rr(dev, MT_HIF_REMAP_L1);

	वापस MT_HIF_REMAP_BASE_L1 + offset;
पूर्ण

अटल अंतरभूत u32
mt7921_l1_rr(काष्ठा mt7921_dev *dev, u32 addr)
अणु
	वापस mt76_rr(dev, mt7921_reg_map_l1(dev, addr));
पूर्ण

अटल अंतरभूत व्योम
mt7921_l1_wr(काष्ठा mt7921_dev *dev, u32 addr, u32 val)
अणु
	mt76_wr(dev, mt7921_reg_map_l1(dev, addr), val);
पूर्ण

अटल अंतरभूत u32
mt7921_l1_rmw(काष्ठा mt7921_dev *dev, u32 addr, u32 mask, u32 val)
अणु
	val |= mt7921_l1_rr(dev, addr) & ~mask;
	mt7921_l1_wr(dev, addr, val);

	वापस val;
पूर्ण

#घोषणा mt7921_l1_set(dev, addr, val)	mt7921_l1_rmw(dev, addr, 0, val)
#घोषणा mt7921_l1_clear(dev, addr, val)	mt7921_l1_rmw(dev, addr, val, 0)

अटल अंतरभूत bool mt7921_dma_need_reinit(काष्ठा mt7921_dev *dev)
अणु
	वापस !mt76_get_field(dev, MT_WFDMA_DUMMY_CR, MT_WFDMA_NEED_REINIT);
पूर्ण

व्योम mt7921_mac_init(काष्ठा mt7921_dev *dev);
bool mt7921_mac_wtbl_update(काष्ठा mt7921_dev *dev, पूर्णांक idx, u32 mask);
व्योम mt7921_mac_reset_counters(काष्ठा mt7921_phy *phy);
व्योम mt7921_mac_ग_लिखो_txwi(काष्ठा mt7921_dev *dev, __le32 *txwi,
			   काष्ठा sk_buff *skb, काष्ठा mt76_wcid *wcid,
			   काष्ठा ieee80211_key_conf *key, bool beacon);
व्योम mt7921_mac_set_timing(काष्ठा mt7921_phy *phy);
पूर्णांक mt7921_mac_fill_rx(काष्ठा mt7921_dev *dev, काष्ठा sk_buff *skb);
व्योम mt7921_mac_fill_rx_vector(काष्ठा mt7921_dev *dev, काष्ठा sk_buff *skb);
व्योम mt7921_mac_tx_मुक्त(काष्ठा mt7921_dev *dev, काष्ठा sk_buff *skb);
पूर्णांक mt7921_mac_sta_add(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_sta *sta);
व्योम mt7921_mac_sta_हटाओ(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta);
व्योम mt7921_mac_work(काष्ठा work_काष्ठा *work);
व्योम mt7921_mac_reset_work(काष्ठा work_काष्ठा *work);
व्योम mt7921_reset(काष्ठा mt76_dev *mdev);
व्योम mt7921_tx_cleanup(काष्ठा mt7921_dev *dev);
पूर्णांक mt7921_tx_prepare_skb(काष्ठा mt76_dev *mdev, व्योम *txwi_ptr,
			  क्रमागत mt76_txq_id qid, काष्ठा mt76_wcid *wcid,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा mt76_tx_info *tx_info);

व्योम mt7921_tx_worker(काष्ठा mt76_worker *w);
व्योम mt7921_tx_complete_skb(काष्ठा mt76_dev *mdev, काष्ठा mt76_queue_entry *e);
पूर्णांक mt7921_init_tx_queues(काष्ठा mt7921_phy *phy, पूर्णांक idx, पूर्णांक n_desc);
व्योम mt7921_tx_token_put(काष्ठा mt7921_dev *dev);
व्योम mt7921_queue_rx_skb(काष्ठा mt76_dev *mdev, क्रमागत mt76_rxq_id q,
			 काष्ठा sk_buff *skb);
व्योम mt7921_sta_ps(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_sta *sta, bool ps);
व्योम mt7921_stats_work(काष्ठा work_काष्ठा *work);
व्योम mt7921_txp_skb_unmap(काष्ठा mt76_dev *dev,
			  काष्ठा mt76_txwi_cache *txwi);
व्योम mt7921_set_stream_he_caps(काष्ठा mt7921_phy *phy);
व्योम mt7921_update_channel(काष्ठा mt76_dev *mdev);
पूर्णांक mt7921_init_debugfs(काष्ठा mt7921_dev *dev);

पूर्णांक mt7921_mcu_uni_tx_ba(काष्ठा mt7921_dev *dev,
			 काष्ठा ieee80211_ampdu_params *params,
			 bool enable);
पूर्णांक mt7921_mcu_uni_rx_ba(काष्ठा mt7921_dev *dev,
			 काष्ठा ieee80211_ampdu_params *params,
			 bool enable);
व्योम mt7921_scan_work(काष्ठा work_काष्ठा *work);
u32 mt7921_get_wtbl_info(काष्ठा mt7921_dev *dev, u32 wlan_idx);
पूर्णांक mt7921_mcu_uni_bss_ps(काष्ठा mt7921_dev *dev, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक mt7921_mcu_uni_bss_bcnft(काष्ठा mt7921_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
			     bool enable);
पूर्णांक mt7921_mcu_set_bss_pm(काष्ठा mt7921_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
			  bool enable);
पूर्णांक mt7921_mcu_drv_pmctrl(काष्ठा mt7921_dev *dev);
पूर्णांक mt7921_mcu_fw_pmctrl(काष्ठा mt7921_dev *dev);
व्योम mt7921_pm_wake_work(काष्ठा work_काष्ठा *work);
व्योम mt7921_pm_घातer_save_work(काष्ठा work_काष्ठा *work);
bool mt7921_रुको_क्रम_mcu_init(काष्ठा mt7921_dev *dev);
पूर्णांक mt7921_mac_set_beacon_filter(काष्ठा mt7921_phy *phy,
				 काष्ठा ieee80211_vअगर *vअगर,
				 bool enable);
व्योम mt7921_pm_पूर्णांकerface_iter(व्योम *priv, u8 *mac, काष्ठा ieee80211_vअगर *vअगर);
व्योम mt7921_coredump_work(काष्ठा work_काष्ठा *work);
पूर्णांक mt7921_wfsys_reset(काष्ठा mt7921_dev *dev);
पूर्णांक mt7921_get_txpwr_info(काष्ठा mt7921_dev *dev, काष्ठा mt7921_txpwr *txpwr);
#पूर्ण_अगर
