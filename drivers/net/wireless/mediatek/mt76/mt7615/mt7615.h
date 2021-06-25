<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/* Copyright (C) 2019 MediaTek Inc. */

#अगर_अघोषित __MT7615_H
#घोषणा __MT7615_H

#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/regmap.h>
#समावेश "../mt76_connac_mcu.h"
#समावेश "regs.h"

#घोषणा MT7615_MAX_INTERFACES		16
#घोषणा MT7615_MAX_WMM_SETS		4
#घोषणा MT7663_WTBL_SIZE		32
#घोषणा MT7615_WTBL_SIZE		128
#घोषणा MT7615_WTBL_RESERVED		(mt7615_wtbl_size(dev) - 1)
#घोषणा MT7615_WTBL_STA			(MT7615_WTBL_RESERVED - \
					 MT7615_MAX_INTERFACES)

#घोषणा MT7615_PM_TIMEOUT		(HZ / 12)
#घोषणा MT7615_WATCHDOG_TIME		(HZ / 10)
#घोषणा MT7615_HW_SCAN_TIMEOUT		(HZ / 10)
#घोषणा MT7615_RESET_TIMEOUT		(30 * HZ)
#घोषणा MT7615_RATE_RETRY		2

#घोषणा MT7615_TX_RING_SIZE		1024
#घोषणा MT7615_TX_MGMT_RING_SIZE	128
#घोषणा MT7615_TX_MCU_RING_SIZE		128
#घोषणा MT7615_TX_FWDL_RING_SIZE	128

#घोषणा MT7615_RX_RING_SIZE		1024
#घोषणा MT7615_RX_MCU_RING_SIZE		512

#घोषणा MT7615_DRV_OWN_RETRY_COUNT	10

#घोषणा MT7615_FIRMWARE_CR4		"mediatek/mt7615_cr4.bin"
#घोषणा MT7615_FIRMWARE_N9		"mediatek/mt7615_n9.bin"
#घोषणा MT7615_ROM_PATCH		"mediatek/mt7615_rom_patch.bin"

#घोषणा MT7622_FIRMWARE_N9		"mediatek/mt7622_n9.bin"
#घोषणा MT7622_ROM_PATCH		"mediatek/mt7622_rom_patch.bin"

#घोषणा MT7615_FIRMWARE_V1		1
#घोषणा MT7615_FIRMWARE_V2		2
#घोषणा MT7615_FIRMWARE_V3		3

#घोषणा MT7663_OFFLOAD_ROM_PATCH	"mediatek/mt7663pr2h.bin"
#घोषणा MT7663_OFFLOAD_FIRMWARE_N9	"mediatek/mt7663_n9_v3.bin"
#घोषणा MT7663_ROM_PATCH		"mediatek/mt7663pr2h_rebb.bin"
#घोषणा MT7663_FIRMWARE_N9		"mediatek/mt7663_n9_rebb.bin"

#घोषणा MT7615_EEPROM_SIZE		1024
#घोषणा MT7615_TOKEN_SIZE		4096

#घोषणा MT_FRAC_SCALE		12
#घोषणा MT_FRAC(val, भाग)	(((val) << MT_FRAC_SCALE) / (भाग))

#घोषणा MT_CHFREQ_VALID		BIT(7)
#घोषणा MT_CHFREQ_DBDC_IDX	BIT(6)
#घोषणा MT_CHFREQ_SEQ		GENMASK(5, 0)

#घोषणा MT7615_BAR_RATE_DEFAULT		0x4b /* OFDM 6M */
#घोषणा MT7615_CFEND_RATE_DEFAULT	0x49 /* OFDM 24M */
#घोषणा MT7615_CFEND_RATE_11B		0x03 /* 11B LP, 11M */

काष्ठा mt7615_vअगर;
काष्ठा mt7615_sta;
काष्ठा mt7615_dfs_pulse;
काष्ठा mt7615_dfs_pattern;
क्रमागत mt7615_cipher_type;

क्रमागत mt7615_hw_txq_id अणु
	MT7615_TXQ_MAIN,
	MT7615_TXQ_EXT,
	MT7615_TXQ_MCU,
	MT7615_TXQ_FWDL,
पूर्ण;

क्रमागत mt7622_hw_txq_id अणु
	MT7622_TXQ_AC0,
	MT7622_TXQ_AC1,
	MT7622_TXQ_AC2,
	MT7622_TXQ_FWDL = MT7615_TXQ_FWDL,
	MT7622_TXQ_AC3,
	MT7622_TXQ_MGMT,
	MT7622_TXQ_MCU = 15,
पूर्ण;

काष्ठा mt7615_rate_set अणु
	काष्ठा ieee80211_tx_rate probe_rate;
	काष्ठा ieee80211_tx_rate rates[4];
पूर्ण;

काष्ठा mt7615_rate_desc अणु
	bool rateset;
	u16 probe_val;
	u16 val[4];
	u8 bw_idx;
	u8 bw;
पूर्ण;

काष्ठा mt7615_wtbl_rate_desc अणु
	काष्ठा list_head node;

	काष्ठा mt7615_rate_desc rate;
	काष्ठा mt7615_sta *sta;
पूर्ण;

काष्ठा mt7615_sta अणु
	काष्ठा mt76_wcid wcid; /* must be first */

	काष्ठा mt7615_vअगर *vअगर;

	काष्ठा list_head poll_list;
	u32 airसमय_ac[8];

	काष्ठा ieee80211_tx_rate rates[4];

	काष्ठा mt7615_rate_set rateset[2];
	u32 rate_set_tsf;

	u8 rate_count;
	u8 n_rates;

	u8 rate_probe;
पूर्ण;

काष्ठा mt7615_vअगर अणु
	काष्ठा mt76_vअगर mt76; /* must be first */
	काष्ठा mt7615_sta sta;
पूर्ण;

काष्ठा mib_stats अणु
	u32 ack_fail_cnt;
	u32 fcs_err_cnt;
	u32 rts_cnt;
	u32 rts_retries_cnt;
	u32 ba_miss_cnt;
	अचिन्हित दीर्घ aggr_per;
पूर्ण;

काष्ठा mt7615_phy अणु
	काष्ठा mt76_phy *mt76;
	काष्ठा mt7615_dev *dev;

	काष्ठा ieee80211_vअगर *monitor_vअगर;

	u8 n_beacon_vअगर;

	u32 rxfilter;
	u64 omac_mask;

	u16 noise;

	bool scs_en;

	अचिन्हित दीर्घ last_cca_adj;
	पूर्णांक false_cca_ofdm, false_cca_cck;
	s8 ofdm_sensitivity;
	s8 cck_sensitivity;

	s16 coverage_class;
	u8 slotसमय;

	u8 chfreq;
	u8 rdd_state;
	पूर्णांक dfs_state;

	u32 rx_ampdu_ts;
	u32 ampdu_ref;

	काष्ठा mib_stats mib;

	काष्ठा sk_buff_head scan_event_list;
	काष्ठा delayed_work scan_work;

	काष्ठा work_काष्ठा roc_work;
	काष्ठा समयr_list roc_समयr;
	रुको_queue_head_t roc_रुको;
	bool roc_grant;

#अगर_घोषित CONFIG_NL80211_TESTMODE
	काष्ठा अणु
		u32 *reg_backup;

		s16 last_freq_offset;
		u8 last_rcpi[4];
		s8 last_ib_rssi[4];
		s8 last_wb_rssi[4];
	पूर्ण test;
#पूर्ण_अगर
पूर्ण;

#घोषणा mt7615_mcu_add_tx_ba(dev, ...)	(dev)->mcu_ops->add_tx_ba((dev), __VA_ARGS__)
#घोषणा mt7615_mcu_add_rx_ba(dev, ...)	(dev)->mcu_ops->add_rx_ba((dev), __VA_ARGS__)
#घोषणा mt7615_mcu_sta_add(phy, ...)	((phy)->dev)->mcu_ops->sta_add((phy),  __VA_ARGS__)
#घोषणा mt7615_mcu_add_dev_info(phy, ...) ((phy)->dev)->mcu_ops->add_dev_info((phy),  __VA_ARGS__)
#घोषणा mt7615_mcu_add_bss_info(phy, ...) ((phy)->dev)->mcu_ops->add_bss_info((phy),  __VA_ARGS__)
#घोषणा mt7615_mcu_add_beacon(dev, ...)	(dev)->mcu_ops->add_beacon_offload((dev),  __VA_ARGS__)
#घोषणा mt7615_mcu_set_pm(dev, ...)	(dev)->mcu_ops->set_pm_state((dev),  __VA_ARGS__)
#घोषणा mt7615_mcu_set_drv_ctrl(dev)	(dev)->mcu_ops->set_drv_ctrl((dev))
#घोषणा mt7615_mcu_set_fw_ctrl(dev)	(dev)->mcu_ops->set_fw_ctrl((dev))
काष्ठा mt7615_mcu_ops अणु
	पूर्णांक (*add_tx_ba)(काष्ठा mt7615_dev *dev,
			 काष्ठा ieee80211_ampdu_params *params,
			 bool enable);
	पूर्णांक (*add_rx_ba)(काष्ठा mt7615_dev *dev,
			 काष्ठा ieee80211_ampdu_params *params,
			 bool enable);
	पूर्णांक (*sta_add)(काष्ठा mt7615_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_sta *sta, bool enable);
	पूर्णांक (*add_dev_info)(काष्ठा mt7615_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
			    bool enable);
	पूर्णांक (*add_bss_info)(काष्ठा mt7615_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta, bool enable);
	पूर्णांक (*add_beacon_offload)(काष्ठा mt7615_dev *dev,
				  काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर, bool enable);
	पूर्णांक (*set_pm_state)(काष्ठा mt7615_dev *dev, पूर्णांक band, पूर्णांक state);
	पूर्णांक (*set_drv_ctrl)(काष्ठा mt7615_dev *dev);
	पूर्णांक (*set_fw_ctrl)(काष्ठा mt7615_dev *dev);
पूर्ण;

काष्ठा mt7615_dev अणु
	जोड़ अणु /* must be first */
		काष्ठा mt76_dev mt76;
		काष्ठा mt76_phy mphy;
	पूर्ण;

	स्थिर काष्ठा mt76_bus_ops *bus_ops;
	काष्ठा tasklet_काष्ठा irq_tasklet;

	काष्ठा mt7615_phy phy;
	u64 omac_mask;

	u16 chainmask;

	काष्ठा ieee80211_ops *ops;
	स्थिर काष्ठा mt7615_mcu_ops *mcu_ops;
	काष्ठा regmap *infracfg;
	स्थिर u32 *reg_map;

	काष्ठा work_काष्ठा mcu_work;

	काष्ठा work_काष्ठा reset_work;
	रुको_queue_head_t reset_रुको;
	u32 reset_state;

	काष्ठा list_head sta_poll_list;
	spinlock_t sta_poll_lock;

	काष्ठा अणु
		u8 n_pulses;
		u32 period;
		u16 width;
		s16 घातer;
	पूर्ण radar_pattern;
	u32 hw_pattern;

	bool fw_debug;
	bool flash_eeprom;
	bool dbdc_support;

	u8 fw_ver;

	काष्ठा work_काष्ठा rate_work;
	काष्ठा list_head wrd_head;

	u32 debugfs_rf_wf;
	u32 debugfs_rf_reg;

	u32 muar_mask;

	काष्ठा mt76_connac_pm pm;
	काष्ठा mt76_connac_coredump coredump;
पूर्ण;

क्रमागत tx_pkt_queue_idx अणु
	MT_LMAC_AC00,
	MT_LMAC_AC01,
	MT_LMAC_AC02,
	MT_LMAC_AC03,
	MT_LMAC_ALTX0 = 0x10,
	MT_LMAC_BMC0,
	MT_LMAC_BCN0,
	MT_LMAC_PSMP0,
	MT_LMAC_ALTX1,
	MT_LMAC_BMC1,
	MT_LMAC_BCN1,
	MT_LMAC_PSMP1,
पूर्ण;

क्रमागत अणु
	MT_RX_SEL0,
	MT_RX_SEL1,
पूर्ण;

क्रमागत mt7615_rdd_cmd अणु
	RDD_STOP,
	RDD_START,
	RDD_DET_MODE,
	RDD_DET_STOP,
	RDD_CAC_START,
	RDD_CAC_END,
	RDD_NORMAL_START,
	RDD_DISABLE_DFS_CAL,
	RDD_PULSE_DBG,
	RDD_READ_PULSE,
	RDD_RESUME_BF,
पूर्ण;

अटल अंतरभूत काष्ठा mt7615_phy *
mt7615_hw_phy(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt76_phy *phy = hw->priv;

	वापस phy->priv;
पूर्ण

अटल अंतरभूत काष्ठा mt7615_dev *
mt7615_hw_dev(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt76_phy *phy = hw->priv;

	वापस container_of(phy->dev, काष्ठा mt7615_dev, mt76);
पूर्ण

अटल अंतरभूत काष्ठा mt7615_phy *
mt7615_ext_phy(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा mt76_phy *phy = dev->mt76.phy2;

	अगर (!phy)
		वापस शून्य;

	वापस phy->priv;
पूर्ण

बाह्य काष्ठा ieee80211_rate mt7615_rates[12];
बाह्य स्थिर काष्ठा ieee80211_ops mt7615_ops;
बाह्य स्थिर u32 mt7615e_reg_map[__MT_BASE_MAX];
बाह्य स्थिर u32 mt7663e_reg_map[__MT_BASE_MAX];
बाह्य स्थिर u32 mt7663_usb_sdio_reg_map[__MT_BASE_MAX];
बाह्य काष्ठा pci_driver mt7615_pci_driver;
बाह्य काष्ठा platक्रमm_driver mt7622_wmac_driver;
बाह्य स्थिर काष्ठा mt76_tesपंचांगode_ops mt7615_tesपंचांगode_ops;

#अगर_घोषित CONFIG_MT7622_WMAC
पूर्णांक mt7622_wmac_init(काष्ठा mt7615_dev *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक mt7622_wmac_init(काष्ठा mt7615_dev *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक mt7615_mmio_probe(काष्ठा device *pdev, व्योम __iomem *mem_base,
		      पूर्णांक irq, स्थिर u32 *map);
u32 mt7615_reg_map(काष्ठा mt7615_dev *dev, u32 addr);

व्योम mt7615_init_device(काष्ठा mt7615_dev *dev);
पूर्णांक mt7615_रेजिस्टर_device(काष्ठा mt7615_dev *dev);
व्योम mt7615_unरेजिस्टर_device(काष्ठा mt7615_dev *dev);
पूर्णांक mt7615_रेजिस्टर_ext_phy(काष्ठा mt7615_dev *dev);
व्योम mt7615_unरेजिस्टर_ext_phy(काष्ठा mt7615_dev *dev);
पूर्णांक mt7615_eeprom_init(काष्ठा mt7615_dev *dev, u32 addr);
पूर्णांक mt7615_eeprom_get_target_घातer_index(काष्ठा mt7615_dev *dev,
					 काष्ठा ieee80211_channel *chan,
					 u8 chain_idx);
पूर्णांक mt7615_eeprom_get_घातer_delta_index(काष्ठा mt7615_dev *dev,
					क्रमागत nl80211_band band);
पूर्णांक mt7615_रुको_pdma_busy(काष्ठा mt7615_dev *dev);
पूर्णांक mt7615_dma_init(काष्ठा mt7615_dev *dev);
व्योम mt7615_dma_start(काष्ठा mt7615_dev *dev);
व्योम mt7615_dma_cleanup(काष्ठा mt7615_dev *dev);
पूर्णांक mt7615_mcu_init(काष्ठा mt7615_dev *dev);
bool mt7615_रुको_क्रम_mcu_init(काष्ठा mt7615_dev *dev);
व्योम mt7615_mac_set_rates(काष्ठा mt7615_phy *phy, काष्ठा mt7615_sta *sta,
			  काष्ठा ieee80211_tx_rate *probe_rate,
			  काष्ठा ieee80211_tx_rate *rates);
व्योम mt7615_pm_wake_work(काष्ठा work_काष्ठा *work);
व्योम mt7615_pm_घातer_save_work(काष्ठा work_काष्ठा *work);
पूर्णांक mt7615_mcu_del_wtbl_all(काष्ठा mt7615_dev *dev);
पूर्णांक mt7615_mcu_set_chan_info(काष्ठा mt7615_phy *phy, पूर्णांक cmd);
पूर्णांक mt7615_mcu_set_wmm(काष्ठा mt7615_dev *dev, u8 queue,
		       स्थिर काष्ठा ieee80211_tx_queue_params *params);
व्योम mt7615_mcu_rx_event(काष्ठा mt7615_dev *dev, काष्ठा sk_buff *skb);
पूर्णांक mt7615_mcu_rdd_cmd(काष्ठा mt7615_dev *dev,
		       क्रमागत mt7615_rdd_cmd cmd, u8 index,
		       u8 rx_sel, u8 val);
पूर्णांक mt7615_mcu_rdd_send_pattern(काष्ठा mt7615_dev *dev);
पूर्णांक mt7615_mcu_fw_log_2_host(काष्ठा mt7615_dev *dev, u8 ctrl);

अटल अंतरभूत bool is_mt7622(काष्ठा mt76_dev *dev)
अणु
	अगर (!IS_ENABLED(CONFIG_MT7622_WMAC))
		वापस false;

	वापस mt76_chip(dev) == 0x7622;
पूर्ण

अटल अंतरभूत bool is_mt7615(काष्ठा mt76_dev *dev)
अणु
	वापस mt76_chip(dev) == 0x7615 || mt76_chip(dev) == 0x7611;
पूर्ण

अटल अंतरभूत bool is_mt7611(काष्ठा mt76_dev *dev)
अणु
	वापस mt76_chip(dev) == 0x7611;
पूर्ण

अटल अंतरभूत व्योम mt7615_irq_enable(काष्ठा mt7615_dev *dev, u32 mask)
अणु
	mt76_set_irq_mask(&dev->mt76, 0, 0, mask);

	tasklet_schedule(&dev->irq_tasklet);
पूर्ण

अटल अंतरभूत bool mt7615_firmware_offload(काष्ठा mt7615_dev *dev)
अणु
	वापस dev->fw_ver > MT7615_FIRMWARE_V2;
पूर्ण

अटल अंतरभूत u16 mt7615_wtbl_size(काष्ठा mt7615_dev *dev)
अणु
	अगर (is_mt7663(&dev->mt76) && mt7615_firmware_offload(dev))
		वापस MT7663_WTBL_SIZE;
	अन्यथा
		वापस MT7615_WTBL_SIZE;
पूर्ण

#घोषणा mt7615_mutex_acquire(dev)	\
	mt76_connac_mutex_acquire(&(dev)->mt76, &(dev)->pm)
#घोषणा mt7615_mutex_release(dev)	\
	mt76_connac_mutex_release(&(dev)->mt76, &(dev)->pm)

अटल अंतरभूत u8 mt7615_lmac_mapping(काष्ठा mt7615_dev *dev, u8 ac)
अणु
	अटल स्थिर u8 lmac_queue_map[] = अणु
		[IEEE80211_AC_BK] = MT_LMAC_AC00,
		[IEEE80211_AC_BE] = MT_LMAC_AC01,
		[IEEE80211_AC_VI] = MT_LMAC_AC02,
		[IEEE80211_AC_VO] = MT_LMAC_AC03,
	पूर्ण;

	अगर (WARN_ON_ONCE(ac >= ARRAY_SIZE(lmac_queue_map)))
		वापस MT_LMAC_AC01; /* BE */

	वापस lmac_queue_map[ac];
पूर्ण

अटल अंतरभूत u32 mt7615_tx_mcu_पूर्णांक_mask(काष्ठा mt7615_dev *dev)
अणु
	वापस MT_INT_TX_DONE(dev->mt76.q_mcu[MT_MCUQ_WM]->hw_idx);
पूर्ण

व्योम mt7615_dma_reset(काष्ठा mt7615_dev *dev);
व्योम mt7615_scan_work(काष्ठा work_काष्ठा *work);
व्योम mt7615_roc_work(काष्ठा work_काष्ठा *work);
व्योम mt7615_roc_समयr(काष्ठा समयr_list *समयr);
व्योम mt7615_init_txघातer(काष्ठा mt7615_dev *dev,
			 काष्ठा ieee80211_supported_band *sband);
पूर्णांक mt7615_set_channel(काष्ठा mt7615_phy *phy);
व्योम mt7615_init_work(काष्ठा mt7615_dev *dev);

पूर्णांक mt7615_mcu_restart(काष्ठा mt76_dev *dev);
व्योम mt7615_update_channel(काष्ठा mt76_dev *mdev);
bool mt7615_mac_wtbl_update(काष्ठा mt7615_dev *dev, पूर्णांक idx, u32 mask);
व्योम mt7615_mac_reset_counters(काष्ठा mt7615_dev *dev);
व्योम mt7615_mac_cca_stats_reset(काष्ठा mt7615_phy *phy);
व्योम mt7615_mac_set_scs(काष्ठा mt7615_phy *phy, bool enable);
व्योम mt7615_mac_enable_nf(काष्ठा mt7615_dev *dev, bool ext_phy);
व्योम mt7615_mac_sta_poll(काष्ठा mt7615_dev *dev);
पूर्णांक mt7615_mac_ग_लिखो_txwi(काष्ठा mt7615_dev *dev, __le32 *txwi,
			  काष्ठा sk_buff *skb, काष्ठा mt76_wcid *wcid,
			  काष्ठा ieee80211_sta *sta, पूर्णांक pid,
			  काष्ठा ieee80211_key_conf *key, bool beacon);
व्योम mt7615_mac_set_timing(काष्ठा mt7615_phy *phy);
पूर्णांक __mt7615_mac_wtbl_set_key(काष्ठा mt7615_dev *dev,
			      काष्ठा mt76_wcid *wcid,
			      काष्ठा ieee80211_key_conf *key,
			      क्रमागत set_key_cmd cmd);
पूर्णांक mt7615_mac_wtbl_set_key(काष्ठा mt7615_dev *dev, काष्ठा mt76_wcid *wcid,
			    काष्ठा ieee80211_key_conf *key,
			    क्रमागत set_key_cmd cmd);
व्योम mt7615_mac_reset_work(काष्ठा work_काष्ठा *work);
u32 mt7615_mac_get_sta_tid_sn(काष्ठा mt7615_dev *dev, पूर्णांक wcid, u8 tid);

पूर्णांक mt7615_mcu_parse_response(काष्ठा mt76_dev *mdev, पूर्णांक cmd,
			      काष्ठा sk_buff *skb, पूर्णांक seq);
u32 mt7615_rf_rr(काष्ठा mt7615_dev *dev, u32 wf, u32 reg);
पूर्णांक mt7615_rf_wr(काष्ठा mt7615_dev *dev, u32 wf, u32 reg, u32 val);
पूर्णांक mt7615_mcu_set_dbdc(काष्ठा mt7615_dev *dev);
पूर्णांक mt7615_mcu_set_eeprom(काष्ठा mt7615_dev *dev);
पूर्णांक mt7615_mcu_get_temperature(काष्ठा mt7615_dev *dev, पूर्णांक index);
पूर्णांक mt7615_mcu_set_tx_घातer(काष्ठा mt7615_phy *phy);
व्योम mt7615_mcu_निकास(काष्ठा mt7615_dev *dev);
व्योम mt7615_mcu_fill_msg(काष्ठा mt7615_dev *dev, काष्ठा sk_buff *skb,
			 पूर्णांक cmd, पूर्णांक *रुको_seq);

पूर्णांक mt7615_tx_prepare_skb(काष्ठा mt76_dev *mdev, व्योम *txwi_ptr,
			  क्रमागत mt76_txq_id qid, काष्ठा mt76_wcid *wcid,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा mt76_tx_info *tx_info);

व्योम mt7615_tx_worker(काष्ठा mt76_worker *w);
व्योम mt7615_tx_complete_skb(काष्ठा mt76_dev *mdev, काष्ठा mt76_queue_entry *e);
व्योम mt7615_tx_token_put(काष्ठा mt7615_dev *dev);
व्योम mt7615_queue_rx_skb(काष्ठा mt76_dev *mdev, क्रमागत mt76_rxq_id q,
			 काष्ठा sk_buff *skb);
व्योम mt7615_sta_ps(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_sta *sta, bool ps);
पूर्णांक mt7615_mac_sta_add(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_sta *sta);
व्योम mt7615_mac_sta_हटाओ(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta);
व्योम mt7615_mac_work(काष्ठा work_काष्ठा *work);
व्योम mt7615_txp_skb_unmap(काष्ठा mt76_dev *dev,
			  काष्ठा mt76_txwi_cache *txwi);
पूर्णांक mt7615_mcu_sta_update_hdr_trans(काष्ठा mt7615_dev *dev,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_sta *sta);
पूर्णांक mt7615_mcu_set_rx_hdr_trans_blacklist(काष्ठा mt7615_dev *dev);
पूर्णांक mt7615_mcu_set_fcc5_lpn(काष्ठा mt7615_dev *dev, पूर्णांक val);
पूर्णांक mt7615_mcu_set_pulse_th(काष्ठा mt7615_dev *dev,
			    स्थिर काष्ठा mt7615_dfs_pulse *pulse);
पूर्णांक mt7615_mcu_set_radar_th(काष्ठा mt7615_dev *dev, पूर्णांक index,
			    स्थिर काष्ठा mt7615_dfs_pattern *pattern);
पूर्णांक mt7615_mcu_set_test_param(काष्ठा mt7615_dev *dev, u8 param, bool test_mode,
			      u32 val);
पूर्णांक mt7615_mcu_set_sku_en(काष्ठा mt7615_phy *phy, bool enable);
पूर्णांक mt7615_mcu_apply_rx_dcoc(काष्ठा mt7615_phy *phy);
पूर्णांक mt7615_mcu_apply_tx_dpd(काष्ठा mt7615_phy *phy);
पूर्णांक mt7615_dfs_init_radar_detector(काष्ठा mt7615_phy *phy);

पूर्णांक mt7615_mcu_set_p2p_oppps(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक mt7615_mcu_set_roc(काष्ठा mt7615_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_channel *chan, पूर्णांक duration);

पूर्णांक mt7615_init_debugfs(काष्ठा mt7615_dev *dev);
पूर्णांक mt7615_mcu_रुको_response(काष्ठा mt7615_dev *dev, पूर्णांक cmd, पूर्णांक seq);

पूर्णांक mt7615_mac_set_beacon_filter(काष्ठा mt7615_phy *phy,
				 काष्ठा ieee80211_vअगर *vअगर,
				 bool enable);
पूर्णांक mt7615_mcu_set_bss_pm(काष्ठा mt7615_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
			  bool enable);
पूर्णांक __mt7663_load_firmware(काष्ठा mt7615_dev *dev);
u32 mt7615_mcu_reg_rr(काष्ठा mt76_dev *dev, u32 offset);
व्योम mt7615_mcu_reg_wr(काष्ठा mt76_dev *dev, u32 offset, u32 val);
व्योम mt7615_coredump_work(काष्ठा work_काष्ठा *work);

व्योम mt7622_trigger_hअगर_पूर्णांक(काष्ठा mt7615_dev *dev, bool en);

/* usb */
पूर्णांक mt7663_usb_sdio_tx_prepare_skb(काष्ठा mt76_dev *mdev, व्योम *txwi_ptr,
				   क्रमागत mt76_txq_id qid, काष्ठा mt76_wcid *wcid,
				   काष्ठा ieee80211_sta *sta,
				   काष्ठा mt76_tx_info *tx_info);
bool mt7663_usb_sdio_tx_status_data(काष्ठा mt76_dev *mdev, u8 *update);
व्योम mt7663_usb_sdio_tx_complete_skb(काष्ठा mt76_dev *mdev,
				     काष्ठा mt76_queue_entry *e);
पूर्णांक mt7663_usb_sdio_रेजिस्टर_device(काष्ठा mt7615_dev *dev);
पूर्णांक mt7663u_mcu_init(काष्ठा mt7615_dev *dev);

/* sdio */
u32 mt7663s_पढ़ो_pcr(काष्ठा mt7615_dev *dev);
पूर्णांक mt7663s_mcu_init(काष्ठा mt7615_dev *dev);
व्योम mt7663s_txrx_worker(काष्ठा mt76_worker *w);
व्योम mt7663s_rx_work(काष्ठा work_काष्ठा *work);
व्योम mt7663s_sdio_irq(काष्ठा sdio_func *func);

#पूर्ण_अगर
