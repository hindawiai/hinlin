<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/* Copyright (C) 2020 MediaTek Inc. */

#अगर_अघोषित __MT7915_H
#घोषणा __MT7915_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kसमय.स>
#समावेश "../mt76.h"
#समावेश "regs.h"

#घोषणा MT7915_MAX_INTERFACES		32
#घोषणा MT7915_MAX_WMM_SETS		4
#घोषणा MT7915_WTBL_SIZE		288
#घोषणा MT7915_WTBL_RESERVED		(MT7915_WTBL_SIZE - 1)
#घोषणा MT7915_WTBL_STA			(MT7915_WTBL_RESERVED - \
					 MT7915_MAX_INTERFACES)

#घोषणा MT7915_WATCHDOG_TIME		(HZ / 10)
#घोषणा MT7915_RESET_TIMEOUT		(30 * HZ)

#घोषणा MT7915_TX_RING_SIZE		2048
#घोषणा MT7915_TX_MCU_RING_SIZE		256
#घोषणा MT7915_TX_FWDL_RING_SIZE	128

#घोषणा MT7915_RX_RING_SIZE		1536
#घोषणा MT7915_RX_MCU_RING_SIZE		512

#घोषणा MT7915_FIRMWARE_WA		"mediatek/mt7915_wa.bin"
#घोषणा MT7915_FIRMWARE_WM		"mediatek/mt7915_wm.bin"
#घोषणा MT7915_ROM_PATCH		"mediatek/mt7915_rom_patch.bin"

#घोषणा MT7915_EEPROM_SIZE		3584
#घोषणा MT7915_TOKEN_SIZE		8192

#घोषणा MT7915_CFEND_RATE_DEFAULT	0x49	/* OFDM 24M */
#घोषणा MT7915_CFEND_RATE_11B		0x03	/* 11B LP, 11M */
#घोषणा MT7915_5G_RATE_DEFAULT		0x4b	/* OFDM 6M */
#घोषणा MT7915_2G_RATE_DEFAULT		0x0	/* CCK 1M */

काष्ठा mt7915_vअगर;
काष्ठा mt7915_sta;
काष्ठा mt7915_dfs_pulse;
काष्ठा mt7915_dfs_pattern;

क्रमागत mt7915_txq_id अणु
	MT7915_TXQ_FWDL = 16,
	MT7915_TXQ_MCU_WM,
	MT7915_TXQ_BAND0,
	MT7915_TXQ_BAND1,
	MT7915_TXQ_MCU_WA,
पूर्ण;

क्रमागत mt7915_rxq_id अणु
	MT7915_RXQ_BAND0 = 0,
	MT7915_RXQ_BAND1,
	MT7915_RXQ_MCU_WM = 0,
	MT7915_RXQ_MCU_WA,
	MT7915_RXQ_MCU_WA_EXT,
पूर्ण;

काष्ठा mt7915_sta_stats अणु
	काष्ठा rate_info prob_rate;
	काष्ठा rate_info tx_rate;

	अचिन्हित दीर्घ per;
	अचिन्हित दीर्घ changed;
	अचिन्हित दीर्घ jअगरfies;
पूर्ण;

काष्ठा mt7915_sta_key_conf अणु
	s8 keyidx;
	u8 key[16];
पूर्ण;

काष्ठा mt7915_sta अणु
	काष्ठा mt76_wcid wcid; /* must be first */

	काष्ठा mt7915_vअगर *vअगर;

	काष्ठा list_head stats_list;
	काष्ठा list_head poll_list;
	काष्ठा list_head rc_list;
	u32 airसमय_ac[8];

	काष्ठा mt7915_sta_stats stats;

	अचिन्हित दीर्घ ampdu_state;

	काष्ठा mt7915_sta_key_conf bip;
पूर्ण;

काष्ठा mt7915_vअगर अणु
	u16 idx;
	u8 omac_idx;
	u8 band_idx;
	u8 wmm_idx;

	काष्ठा mt7915_sta sta;
	काष्ठा mt7915_phy *phy;

	काष्ठा ieee80211_tx_queue_params queue_params[IEEE80211_NUM_ACS];
पूर्ण;

काष्ठा mib_stats अणु
	u32 ack_fail_cnt;
	u32 fcs_err_cnt;
	u32 rts_cnt;
	u32 rts_retries_cnt;
	u32 ba_miss_cnt;
पूर्ण;

काष्ठा mt7915_hअगर अणु
	काष्ठा list_head list;

	काष्ठा device *dev;
	व्योम __iomem *regs;
	पूर्णांक irq;
पूर्ण;

काष्ठा mt7915_phy अणु
	काष्ठा mt76_phy *mt76;
	काष्ठा mt7915_dev *dev;

	काष्ठा ieee80211_sband_अगरtype_data अगरtype[2][NUM_NL80211_IFTYPES];

	काष्ठा ieee80211_vअगर *monitor_vअगर;

	u32 rxfilter;
	u64 omac_mask;

	u16 noise;

	s16 coverage_class;
	u8 slotसमय;

	u8 rdd_state;
	पूर्णांक dfs_state;

	u32 rx_ampdu_ts;
	u32 ampdu_ref;

	काष्ठा mib_stats mib;
	काष्ठा list_head stats_list;

	u8 sta_work_count;

#अगर_घोषित CONFIG_NL80211_TESTMODE
	काष्ठा अणु
		u32 *reg_backup;

		s32 last_freq_offset;
		u8 last_rcpi[4];
		s8 last_ib_rssi[4];
		s8 last_wb_rssi[4];
		u8 last_snr;

		u8 spe_idx;
	पूर्ण test;
#पूर्ण_अगर
पूर्ण;

काष्ठा mt7915_dev अणु
	जोड़ अणु /* must be first */
		काष्ठा mt76_dev mt76;
		काष्ठा mt76_phy mphy;
	पूर्ण;

	काष्ठा mt7915_hअगर *hअगर2;

	स्थिर काष्ठा mt76_bus_ops *bus_ops;
	काष्ठा mt7915_phy phy;

	u16 chainmask;
	u32 hअगर_idx;

	काष्ठा work_काष्ठा init_work;
	काष्ठा work_काष्ठा rc_work;
	काष्ठा work_काष्ठा reset_work;
	रुको_queue_head_t reset_रुको;
	u32 reset_state;

	काष्ठा list_head sta_rc_list;
	काष्ठा list_head sta_poll_list;
	spinlock_t sta_poll_lock;

	u32 hw_pattern;

	bool dbdc_support;
	bool flash_mode;
	bool fw_debug;
	bool ibf;

	व्योम *cal;
पूर्ण;

क्रमागत अणु
	HW_BSSID_0 = 0x0,
	HW_BSSID_1,
	HW_BSSID_2,
	HW_BSSID_3,
	HW_BSSID_MAX = HW_BSSID_3,
	EXT_BSSID_START = 0x10,
	EXT_BSSID_1,
	EXT_BSSID_15 = 0x1f,
	EXT_BSSID_MAX = EXT_BSSID_15,
	REPEATER_BSSID_START = 0x20,
	REPEATER_BSSID_MAX = 0x3f,
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

क्रमागत अणु
	MT_RX_SEL0,
	MT_RX_SEL1,
पूर्ण;

क्रमागत mt7915_rdd_cmd अणु
	RDD_STOP,
	RDD_START,
	RDD_DET_MODE,
	RDD_RADAR_EMULATE,
	RDD_START_TXQ = 20,
	RDD_CAC_START = 50,
	RDD_CAC_END,
	RDD_NORMAL_START,
	RDD_DISABLE_DFS_CAL,
	RDD_PULSE_DBG,
	RDD_READ_PULSE,
	RDD_RESUME_BF,
	RDD_IRQ_OFF,
पूर्ण;

क्रमागत अणु
	RATE_CTRL_RU_INFO,
	RATE_CTRL_FIXED_RATE_INFO,
	RATE_CTRL_DUMP_INFO,
	RATE_CTRL_MU_INFO,
पूर्ण;

अटल अंतरभूत काष्ठा mt7915_phy *
mt7915_hw_phy(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt76_phy *phy = hw->priv;

	वापस phy->priv;
पूर्ण

अटल अंतरभूत काष्ठा mt7915_dev *
mt7915_hw_dev(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt76_phy *phy = hw->priv;

	वापस container_of(phy->dev, काष्ठा mt7915_dev, mt76);
पूर्ण

अटल अंतरभूत काष्ठा mt7915_phy *
mt7915_ext_phy(काष्ठा mt7915_dev *dev)
अणु
	काष्ठा mt76_phy *phy = dev->mt76.phy2;

	अगर (!phy)
		वापस शून्य;

	वापस phy->priv;
पूर्ण

अटल अंतरभूत u8 mt7915_lmac_mapping(काष्ठा mt7915_dev *dev, u8 ac)
अणु
	/* LMAC uses the reverse order of mac80211 AC indexes */
	वापस 3 - ac;
पूर्ण

बाह्य स्थिर काष्ठा ieee80211_ops mt7915_ops;
बाह्य स्थिर काष्ठा mt76_tesपंचांगode_ops mt7915_tesपंचांगode_ops;

u32 mt7915_reg_map(काष्ठा mt7915_dev *dev, u32 addr);

पूर्णांक mt7915_रेजिस्टर_device(काष्ठा mt7915_dev *dev);
व्योम mt7915_unरेजिस्टर_device(काष्ठा mt7915_dev *dev);
पूर्णांक mt7915_eeprom_init(काष्ठा mt7915_dev *dev);
व्योम mt7915_eeprom_parse_band_config(काष्ठा mt7915_phy *phy);
पूर्णांक mt7915_eeprom_get_target_घातer(काष्ठा mt7915_dev *dev,
				   काष्ठा ieee80211_channel *chan,
				   u8 chain_idx);
s8 mt7915_eeprom_get_घातer_delta(काष्ठा mt7915_dev *dev, पूर्णांक band);
पूर्णांक mt7915_dma_init(काष्ठा mt7915_dev *dev);
व्योम mt7915_dma_prefetch(काष्ठा mt7915_dev *dev);
व्योम mt7915_dma_cleanup(काष्ठा mt7915_dev *dev);
पूर्णांक mt7915_mcu_init(काष्ठा mt7915_dev *dev);
पूर्णांक mt7915_mcu_add_dev_info(काष्ठा mt7915_phy *phy,
			    काष्ठा ieee80211_vअगर *vअगर, bool enable);
पूर्णांक mt7915_mcu_add_bss_info(काष्ठा mt7915_phy *phy,
			    काष्ठा ieee80211_vअगर *vअगर, पूर्णांक enable);
पूर्णांक mt7915_mcu_add_sta(काष्ठा mt7915_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_sta *sta, bool enable);
पूर्णांक mt7915_mcu_add_sta_adv(काष्ठा mt7915_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta, bool enable);
पूर्णांक mt7915_mcu_sta_update_hdr_trans(काष्ठा mt7915_dev *dev,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_sta *sta);
पूर्णांक mt7915_mcu_add_tx_ba(काष्ठा mt7915_dev *dev,
			 काष्ठा ieee80211_ampdu_params *params,
			 bool add);
पूर्णांक mt7915_mcu_add_rx_ba(काष्ठा mt7915_dev *dev,
			 काष्ठा ieee80211_ampdu_params *params,
			 bool add);
पूर्णांक mt7915_mcu_add_key(काष्ठा mt7915_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा mt7915_sta *msta, काष्ठा ieee80211_key_conf *key,
		       क्रमागत set_key_cmd cmd);
पूर्णांक mt7915_mcu_add_beacon(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			  पूर्णांक enable);
पूर्णांक mt7915_mcu_add_obss_spr(काष्ठा mt7915_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
                            bool enable);
पूर्णांक mt7915_mcu_add_rate_ctrl(काष्ठा mt7915_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_sta *sta);
पूर्णांक mt7915_mcu_add_smps(काष्ठा mt7915_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_sta *sta);
पूर्णांक mt7915_set_channel(काष्ठा mt7915_phy *phy);
पूर्णांक mt7915_mcu_set_chan_info(काष्ठा mt7915_phy *phy, पूर्णांक cmd);
पूर्णांक mt7915_mcu_set_tx(काष्ठा mt7915_dev *dev, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक mt7915_mcu_update_edca(काष्ठा mt7915_dev *dev, व्योम *req);
पूर्णांक mt7915_mcu_set_fixed_rate(काष्ठा mt7915_dev *dev,
			      काष्ठा ieee80211_sta *sta, u32 rate);
पूर्णांक mt7915_mcu_set_eeprom(काष्ठा mt7915_dev *dev);
पूर्णांक mt7915_mcu_get_eeprom(काष्ठा mt7915_dev *dev, u32 offset);
पूर्णांक mt7915_mcu_set_mac(काष्ठा mt7915_dev *dev, पूर्णांक band, bool enable,
		       bool hdr_trans);
पूर्णांक mt7915_mcu_set_test_param(काष्ठा mt7915_dev *dev, u8 param, bool test_mode,
			      u8 en);
पूर्णांक mt7915_mcu_set_scs(काष्ठा mt7915_dev *dev, u8 band, bool enable);
पूर्णांक mt7915_mcu_set_ser(काष्ठा mt7915_dev *dev, u8 action, u8 set, u8 band);
पूर्णांक mt7915_mcu_set_rts_thresh(काष्ठा mt7915_phy *phy, u32 val);
पूर्णांक mt7915_mcu_set_pm(काष्ठा mt7915_dev *dev, पूर्णांक band, पूर्णांक enter);
पूर्णांक mt7915_mcu_set_sku_en(काष्ठा mt7915_phy *phy, bool enable);
पूर्णांक mt7915_mcu_set_txघातer_sku(काष्ठा mt7915_phy *phy);
पूर्णांक mt7915_mcu_set_txbf_type(काष्ठा mt7915_dev *dev);
पूर्णांक mt7915_mcu_set_txbf_module(काष्ठा mt7915_dev *dev);
पूर्णांक mt7915_mcu_set_txbf_sounding(काष्ठा mt7915_dev *dev);
पूर्णांक mt7915_mcu_set_fcc5_lpn(काष्ठा mt7915_dev *dev, पूर्णांक val);
पूर्णांक mt7915_mcu_set_pulse_th(काष्ठा mt7915_dev *dev,
			    स्थिर काष्ठा mt7915_dfs_pulse *pulse);
पूर्णांक mt7915_mcu_set_radar_th(काष्ठा mt7915_dev *dev, पूर्णांक index,
			    स्थिर काष्ठा mt7915_dfs_pattern *pattern);
पूर्णांक mt7915_mcu_apply_group_cal(काष्ठा mt7915_dev *dev);
पूर्णांक mt7915_mcu_apply_tx_dpd(काष्ठा mt7915_phy *phy);
पूर्णांक mt7915_mcu_get_temperature(काष्ठा mt7915_dev *dev, पूर्णांक index);
पूर्णांक mt7915_mcu_get_tx_rate(काष्ठा mt7915_dev *dev, u32 cmd, u16 wlan_idx);
पूर्णांक mt7915_mcu_get_rx_rate(काष्ठा mt7915_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta, काष्ठा rate_info *rate);
पूर्णांक mt7915_mcu_rdd_cmd(काष्ठा mt7915_dev *dev, क्रमागत mt7915_rdd_cmd cmd,
		       u8 index, u8 rx_sel, u8 val);
पूर्णांक mt7915_mcu_fw_log_2_host(काष्ठा mt7915_dev *dev, u8 ctrl);
पूर्णांक mt7915_mcu_fw_dbg_ctrl(काष्ठा mt7915_dev *dev, u32 module, u8 level);
व्योम mt7915_mcu_rx_event(काष्ठा mt7915_dev *dev, काष्ठा sk_buff *skb);
व्योम mt7915_mcu_निकास(काष्ठा mt7915_dev *dev);

अटल अंतरभूत bool is_mt7915(काष्ठा mt76_dev *dev)
अणु
	वापस mt76_chip(dev) == 0x7915;
पूर्ण

व्योम mt7915_dual_hअगर_set_irq_mask(काष्ठा mt7915_dev *dev, bool ग_लिखो_reg,
				  u32 clear, u32 set);

अटल अंतरभूत व्योम mt7915_irq_enable(काष्ठा mt7915_dev *dev, u32 mask)
अणु
	अगर (dev->hअगर2)
		mt7915_dual_hअगर_set_irq_mask(dev, true, 0, mask);
	अन्यथा
		mt76_set_irq_mask(&dev->mt76, MT_INT_MASK_CSR, 0, mask);
पूर्ण

अटल अंतरभूत व्योम mt7915_irq_disable(काष्ठा mt7915_dev *dev, u32 mask)
अणु
	अगर (dev->hअगर2)
		mt7915_dual_hअगर_set_irq_mask(dev, true, mask, 0);
	अन्यथा
		mt76_set_irq_mask(&dev->mt76, MT_INT_MASK_CSR, mask, 0);
पूर्ण

bool mt7915_mac_wtbl_update(काष्ठा mt7915_dev *dev, पूर्णांक idx, u32 mask);
व्योम mt7915_mac_reset_counters(काष्ठा mt7915_phy *phy);
व्योम mt7915_mac_cca_stats_reset(काष्ठा mt7915_phy *phy);
व्योम mt7915_mac_enable_nf(काष्ठा mt7915_dev *dev, bool ext_phy);
व्योम mt7915_mac_ग_लिखो_txwi(काष्ठा mt7915_dev *dev, __le32 *txwi,
			   काष्ठा sk_buff *skb, काष्ठा mt76_wcid *wcid,
			   काष्ठा ieee80211_key_conf *key, bool beacon);
व्योम mt7915_mac_set_timing(काष्ठा mt7915_phy *phy);
पूर्णांक mt7915_mac_fill_rx(काष्ठा mt7915_dev *dev, काष्ठा sk_buff *skb);
व्योम mt7915_mac_fill_rx_vector(काष्ठा mt7915_dev *dev, काष्ठा sk_buff *skb);
व्योम mt7915_mac_tx_मुक्त(काष्ठा mt7915_dev *dev, काष्ठा sk_buff *skb);
पूर्णांक mt7915_mac_sta_add(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_sta *sta);
व्योम mt7915_mac_sta_हटाओ(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta);
व्योम mt7915_mac_work(काष्ठा work_काष्ठा *work);
व्योम mt7915_mac_reset_work(काष्ठा work_काष्ठा *work);
व्योम mt7915_mac_sta_rc_work(काष्ठा work_काष्ठा *work);
पूर्णांक mt7915_mmio_init(काष्ठा mt76_dev *mdev, व्योम __iomem *mem_base, पूर्णांक irq);
पूर्णांक mt7915_tx_prepare_skb(काष्ठा mt76_dev *mdev, व्योम *txwi_ptr,
			  क्रमागत mt76_txq_id qid, काष्ठा mt76_wcid *wcid,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा mt76_tx_info *tx_info);
व्योम mt7915_tx_complete_skb(काष्ठा mt76_dev *mdev, काष्ठा mt76_queue_entry *e);
व्योम mt7915_tx_token_put(काष्ठा mt7915_dev *dev);
पूर्णांक mt7915_init_tx_queues(काष्ठा mt7915_phy *phy, पूर्णांक idx, पूर्णांक n_desc);
व्योम mt7915_queue_rx_skb(काष्ठा mt76_dev *mdev, क्रमागत mt76_rxq_id q,
			 काष्ठा sk_buff *skb);
व्योम mt7915_sta_ps(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_sta *sta, bool ps);
व्योम mt7915_stats_work(काष्ठा work_काष्ठा *work);
व्योम mt7915_txp_skb_unmap(काष्ठा mt76_dev *dev,
			  काष्ठा mt76_txwi_cache *txwi);
पूर्णांक mt76_dfs_start_rdd(काष्ठा mt7915_dev *dev, bool क्रमce);
पूर्णांक mt7915_dfs_init_radar_detector(काष्ठा mt7915_phy *phy);
व्योम mt7915_set_stream_he_caps(काष्ठा mt7915_phy *phy);
व्योम mt7915_set_stream_vht_txbf_caps(काष्ठा mt7915_phy *phy);
व्योम mt7915_update_channel(काष्ठा mt76_dev *mdev);
पूर्णांक mt7915_init_debugfs(काष्ठा mt7915_dev *dev);
#अगर_घोषित CONFIG_MAC80211_DEBUGFS
व्योम mt7915_sta_add_debugfs(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta, काष्ठा dentry *dir);
#पूर्ण_अगर

#पूर्ण_अगर
