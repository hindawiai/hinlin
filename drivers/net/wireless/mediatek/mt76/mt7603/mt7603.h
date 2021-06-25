<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */

#अगर_अघोषित __MT7603_H
#घोषणा __MT7603_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kसमय.स>
#समावेश "../mt76.h"
#समावेश "regs.h"

#घोषणा MT7603_MAX_INTERFACES	4
#घोषणा MT7603_WTBL_SIZE	128
#घोषणा MT7603_WTBL_RESERVED	(MT7603_WTBL_SIZE - 1)
#घोषणा MT7603_WTBL_STA		(MT7603_WTBL_RESERVED - MT7603_MAX_INTERFACES)

#घोषणा MT7603_RATE_RETRY	2

#घोषणा MT7603_MCU_RX_RING_SIZE	64
#घोषणा MT7603_RX_RING_SIZE     128
#घोषणा MT7603_TX_RING_SIZE	256
#घोषणा MT7603_PSD_RING_SIZE	128

#घोषणा MT7603_FIRMWARE_E1	"mt7603_e1.bin"
#घोषणा MT7603_FIRMWARE_E2	"mt7603_e2.bin"
#घोषणा MT7628_FIRMWARE_E1	"mt7628_e1.bin"
#घोषणा MT7628_FIRMWARE_E2	"mt7628_e2.bin"

#घोषणा MT7603_EEPROM_SIZE	1024

#घोषणा MT_AGG_SIZE_LIMIT(_n)	(((_n) + 1) * 4)

#घोषणा MT7603_PRE_TBTT_TIME	5000 /* ms */

#घोषणा MT7603_WATCHDOG_TIME	100 /* ms */
#घोषणा MT7603_WATCHDOG_TIMEOUT	10 /* number of checks */

#घोषणा MT7603_EDCCA_BLOCK_TH	10

#घोषणा MT7603_CFEND_RATE_DEFAULT	0x69 /* chip शेष (24M) */
#घोषणा MT7603_CFEND_RATE_11B		0x03 /* 11B LP, 11M */

काष्ठा mt7603_vअगर;
काष्ठा mt7603_sta;

क्रमागत अणु
	MT7603_REV_E1 = 0x00,
	MT7603_REV_E2 = 0x10,
	MT7628_REV_E1 = 0x8a00,
पूर्ण;

क्रमागत mt7603_bw अणु
	MT_BW_20,
	MT_BW_40,
	MT_BW_80,
पूर्ण;

काष्ठा mt7603_rate_set अणु
	काष्ठा ieee80211_tx_rate probe_rate;
	काष्ठा ieee80211_tx_rate rates[4];
पूर्ण;

काष्ठा mt7603_sta अणु
	काष्ठा mt76_wcid wcid; /* must be first */

	काष्ठा mt7603_vअगर *vअगर;

	काष्ठा list_head poll_list;
	u32 tx_airसमय_ac[4];

	काष्ठा sk_buff_head psq;

	काष्ठा ieee80211_tx_rate rates[4];

	काष्ठा mt7603_rate_set rateset[2];
	u32 rate_set_tsf;

	u8 rate_count;
	u8 n_rates;

	u8 rate_probe;
	u8 smps;

	u8 ps;
पूर्ण;

काष्ठा mt7603_vअगर अणु
	काष्ठा mt7603_sta sta; /* must be first */

	u8 idx;
पूर्ण;

क्रमागत mt7603_reset_cause अणु
	RESET_CAUSE_TX_HANG,
	RESET_CAUSE_TX_BUSY,
	RESET_CAUSE_RX_BUSY,
	RESET_CAUSE_BEACON_STUCK,
	RESET_CAUSE_RX_PSE_BUSY,
	RESET_CAUSE_MCU_HANG,
	RESET_CAUSE_RESET_FAILED,
	__RESET_CAUSE_MAX
पूर्ण;

काष्ठा mt7603_dev अणु
	जोड़ अणु /* must be first */
		काष्ठा mt76_dev mt76;
		काष्ठा mt76_phy mphy;
	पूर्ण;

	स्थिर काष्ठा mt76_bus_ops *bus_ops;

	u32 rxfilter;

	काष्ठा list_head sta_poll_list;
	spinlock_t sta_poll_lock;

	काष्ठा mt7603_sta global_sta;

	u32 agc0, agc3;
	u32 false_cca_ofdm, false_cca_cck;
	अचिन्हित दीर्घ last_cca_adj;

	u32 ampdu_ref;
	u32 rx_ampdu_ts;
	u8 rssi_offset[3];

	u8 slotसमय;
	s16 coverage_class;

	s8 tx_घातer_limit;

	kसमय_प्रकार ed_समय;

	spinlock_t ps_lock;

	u8 mcu_running;

	u8 ed_monitor_enabled;
	u8 ed_monitor;
	s8 ed_trigger;
	u8 ed_strict_mode;
	u8 ed_strong_संकेत;

	bool dynamic_sensitivity;
	s8 sensitivity;
	u8 sensitivity_limit;

	u8 beacon_check;
	u8 tx_hang_check;
	u8 tx_dma_check;
	u8 rx_dma_check;
	u8 rx_pse_check;
	u8 mcu_hang;

	क्रमागत mt7603_reset_cause cur_reset_cause;

	u16 tx_dma_idx[4];
	u16 rx_dma_idx;

	u32 reset_test;

	अचिन्हित पूर्णांक reset_cause[__RESET_CAUSE_MAX];
पूर्ण;

बाह्य स्थिर काष्ठा mt76_driver_ops mt7603_drv_ops;
बाह्य स्थिर काष्ठा ieee80211_ops mt7603_ops;
बाह्य काष्ठा pci_driver mt7603_pci_driver;
बाह्य काष्ठा platक्रमm_driver mt76_wmac_driver;

अटल अंतरभूत bool is_mt7603(काष्ठा mt7603_dev *dev)
अणु
	वापस mt76xx_chip(dev) == 0x7603;
पूर्ण

अटल अंतरभूत bool is_mt7628(काष्ठा mt7603_dev *dev)
अणु
	वापस mt76xx_chip(dev) == 0x7628;
पूर्ण

/* need offset to prevent conflict with ampdu_ack_len */
#घोषणा MT_RATE_DRIVER_DATA_OFFSET	4

u32 mt7603_reg_map(काष्ठा mt7603_dev *dev, u32 addr);

irqवापस_t mt7603_irq_handler(पूर्णांक irq, व्योम *dev_instance);

पूर्णांक mt7603_रेजिस्टर_device(काष्ठा mt7603_dev *dev);
व्योम mt7603_unरेजिस्टर_device(काष्ठा mt7603_dev *dev);
पूर्णांक mt7603_eeprom_init(काष्ठा mt7603_dev *dev);
पूर्णांक mt7603_dma_init(काष्ठा mt7603_dev *dev);
व्योम mt7603_dma_cleanup(काष्ठा mt7603_dev *dev);
पूर्णांक mt7603_mcu_init(काष्ठा mt7603_dev *dev);
व्योम mt7603_init_debugfs(काष्ठा mt7603_dev *dev);

अटल अंतरभूत व्योम mt7603_irq_enable(काष्ठा mt7603_dev *dev, u32 mask)
अणु
	mt76_set_irq_mask(&dev->mt76, MT_INT_MASK_CSR, 0, mask);
पूर्ण

अटल अंतरभूत व्योम mt7603_irq_disable(काष्ठा mt7603_dev *dev, u32 mask)
अणु
	mt76_set_irq_mask(&dev->mt76, MT_INT_MASK_CSR, mask, 0);
पूर्ण

व्योम mt7603_mac_reset_counters(काष्ठा mt7603_dev *dev);
व्योम mt7603_mac_dma_start(काष्ठा mt7603_dev *dev);
व्योम mt7603_mac_start(काष्ठा mt7603_dev *dev);
व्योम mt7603_mac_stop(काष्ठा mt7603_dev *dev);
व्योम mt7603_mac_work(काष्ठा work_काष्ठा *work);
व्योम mt7603_mac_set_timing(काष्ठा mt7603_dev *dev);
व्योम mt7603_beacon_set_समयr(काष्ठा mt7603_dev *dev, पूर्णांक idx, पूर्णांक पूर्णांकval);
पूर्णांक mt7603_mac_fill_rx(काष्ठा mt7603_dev *dev, काष्ठा sk_buff *skb);
व्योम mt7603_mac_add_txs(काष्ठा mt7603_dev *dev, व्योम *data);
व्योम mt7603_mac_rx_ba_reset(काष्ठा mt7603_dev *dev, व्योम *addr, u8 tid);
व्योम mt7603_mac_tx_ba_reset(काष्ठा mt7603_dev *dev, पूर्णांक wcid, पूर्णांक tid,
			    पूर्णांक ba_size);
व्योम mt7603_mac_sta_poll(काष्ठा mt7603_dev *dev);

व्योम mt7603_pse_client_reset(काष्ठा mt7603_dev *dev);

पूर्णांक mt7603_mcu_set_channel(काष्ठा mt7603_dev *dev);
पूर्णांक mt7603_mcu_set_eeprom(काष्ठा mt7603_dev *dev);
व्योम mt7603_mcu_निकास(काष्ठा mt7603_dev *dev);

व्योम mt7603_wtbl_init(काष्ठा mt7603_dev *dev, पूर्णांक idx, पूर्णांक vअगर,
		      स्थिर u8 *mac_addr);
व्योम mt7603_wtbl_clear(काष्ठा mt7603_dev *dev, पूर्णांक idx);
व्योम mt7603_wtbl_update_cap(काष्ठा mt7603_dev *dev, काष्ठा ieee80211_sta *sta);
व्योम mt7603_wtbl_set_rates(काष्ठा mt7603_dev *dev, काष्ठा mt7603_sta *sta,
			   काष्ठा ieee80211_tx_rate *probe_rate,
			   काष्ठा ieee80211_tx_rate *rates);
पूर्णांक mt7603_wtbl_set_key(काष्ठा mt7603_dev *dev, पूर्णांक wcid,
			काष्ठा ieee80211_key_conf *key);
व्योम mt7603_wtbl_set_ps(काष्ठा mt7603_dev *dev, काष्ठा mt7603_sta *sta,
			bool enabled);
व्योम mt7603_wtbl_set_smps(काष्ठा mt7603_dev *dev, काष्ठा mt7603_sta *sta,
			  bool enabled);
व्योम mt7603_filter_tx(काष्ठा mt7603_dev *dev, पूर्णांक idx, bool पात);

पूर्णांक mt7603_tx_prepare_skb(काष्ठा mt76_dev *mdev, व्योम *txwi_ptr,
			  क्रमागत mt76_txq_id qid, काष्ठा mt76_wcid *wcid,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा mt76_tx_info *tx_info);

व्योम mt7603_tx_complete_skb(काष्ठा mt76_dev *mdev, काष्ठा mt76_queue_entry *e);

व्योम mt7603_queue_rx_skb(काष्ठा mt76_dev *mdev, क्रमागत mt76_rxq_id q,
			 काष्ठा sk_buff *skb);
व्योम mt7603_rx_poll_complete(काष्ठा mt76_dev *mdev, क्रमागत mt76_rxq_id q);
व्योम mt7603_sta_ps(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_sta *sta, bool ps);
पूर्णांक mt7603_sta_add(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_sta *sta);
व्योम mt7603_sta_assoc(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
		      काष्ठा ieee80211_sta *sta);
व्योम mt7603_sta_हटाओ(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_sta *sta);

व्योम mt7603_pre_tbtt_tasklet(काष्ठा tasklet_काष्ठा *t);

व्योम mt7603_update_channel(काष्ठा mt76_dev *mdev);

व्योम mt7603_edcca_set_strict(काष्ठा mt7603_dev *dev, bool val);
व्योम mt7603_cca_stats_reset(काष्ठा mt7603_dev *dev);

व्योम mt7603_init_edcca(काष्ठा mt7603_dev *dev);
#पूर्ण_अगर
