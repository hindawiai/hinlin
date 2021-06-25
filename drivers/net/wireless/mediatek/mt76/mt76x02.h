<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 * Copyright (C) 2018 Stanislaw Gruszka <stf_xl@wp.pl>
 */

#अगर_अघोषित __MT76x02_H
#घोषणा __MT76x02_H

#समावेश <linux/kfअगरo.h>

#समावेश "mt76.h"
#समावेश "mt76x02_regs.h"
#समावेश "mt76x02_mac.h"
#समावेश "mt76x02_dfs.h"
#समावेश "mt76x02_dma.h"

#घोषणा MT76x02_TX_RING_SIZE	512
#घोषणा MT76x02_PSD_RING_SIZE	128
#घोषणा MT76x02_N_WCIDS 128
#घोषणा MT_CALIBRATE_INTERVAL	HZ
#घोषणा MT_MAC_WORK_INTERVAL	(HZ / 10)

#घोषणा MT_WATCHDOG_TIME	(HZ / 10)
#घोषणा MT_TX_HANG_TH		10

#घोषणा MT_MAX_CHAINS		2
काष्ठा mt76x02_rx_freq_cal अणु
	s8 high_gain[MT_MAX_CHAINS];
	s8 rssi_offset[MT_MAX_CHAINS];
	s8 lna_gain;
	u32 mcu_gain;
	s16 temp_offset;
	u8 freq_offset;
पूर्ण;

काष्ठा mt76x02_calibration अणु
	काष्ठा mt76x02_rx_freq_cal rx;

	u8 agc_gain_init[MT_MAX_CHAINS];
	u8 agc_gain_cur[MT_MAX_CHAINS];

	u16 false_cca;
	s8 avg_rssi_all;
	s8 agc_gain_adjust;
	s8 agc_lowest_gain;
	s8 low_gain;

	s8 temp_vco;
	s8 temp;

	bool init_cal_करोne;
	bool tssi_cal_करोne;
	bool tssi_comp_pending;
	bool dpd_cal_करोne;
	bool channel_cal_करोne;
	bool gain_init_करोne;

	पूर्णांक tssi_target;
	s8 tssi_dc;
पूर्ण;

काष्ठा mt76x02_beacon_ops अणु
	अचिन्हित पूर्णांक nslots;
	अचिन्हित पूर्णांक slot_size;
	व्योम (*pre_tbtt_enable)(काष्ठा mt76x02_dev *dev, bool en);
	व्योम (*beacon_enable)(काष्ठा mt76x02_dev *dev, bool en);
पूर्ण;

#घोषणा mt76x02_beacon_enable(dev, enable)	\
	(dev)->beacon_ops->beacon_enable(dev, enable)
#घोषणा mt76x02_pre_tbtt_enable(dev, enable)	\
	(dev)->beacon_ops->pre_tbtt_enable(dev, enable)

काष्ठा mt76x02_dev अणु
	जोड़ अणु /* must be first */
		काष्ठा mt76_dev mt76;
		काष्ठा mt76_phy mphy;
	पूर्ण;

	काष्ठा mac_address macaddr_list[8];

	काष्ठा mutex phy_mutex;

	u8 txकरोne_seq;
	DECLARE_KFIFO_PTR(txstatus_fअगरo, काष्ठा mt76x02_tx_status);
	spinlock_t txstatus_fअगरo_lock;
	u32 tx_airसमय;
	u32 ampdu_ref;

	काष्ठा sk_buff *rx_head;

	काष्ठा delayed_work cal_work;
	काष्ठा delayed_work wdt_work;

	काष्ठा hrसमयr pre_tbtt_समयr;
	काष्ठा work_काष्ठा pre_tbtt_work;

	स्थिर काष्ठा mt76x02_beacon_ops *beacon_ops;

	u8 beacon_data_count;

	u8 tbtt_count;

	u32 tx_hang_reset;
	u8 tx_hang_check;
	u8 mcu_समयout;

	काष्ठा mt76x02_calibration cal;

	पूर्णांक txघातer_conf;
	s8 target_घातer;
	s8 target_घातer_delta[2];
	bool enable_tpc;

	bool no_2ghz;

	s16 coverage_class;
	u8 slotसमय;

	काष्ठा mt76x02_dfs_pattern_detector dfs_pd;

	/* edcca monitor */
	अचिन्हित दीर्घ ed_trigger_समयout;
	bool ed_tx_blocked;
	bool ed_monitor;
	u8 ed_monitor_enabled;
	u8 ed_monitor_learning;
	u8 ed_trigger;
	u8 ed_silent;
	kसमय_प्रकार ed_समय;
पूर्ण;

बाह्य काष्ठा ieee80211_rate mt76x02_rates[12];

व्योम mt76x02_init_device(काष्ठा mt76x02_dev *dev);
व्योम mt76x02_configure_filter(काष्ठा ieee80211_hw *hw,
			      अचिन्हित पूर्णांक changed_flags,
			      अचिन्हित पूर्णांक *total_flags, u64 multicast);
पूर्णांक mt76x02_sta_add(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
		    काष्ठा ieee80211_sta *sta);
व्योम mt76x02_sta_हटाओ(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_sta *sta);

व्योम mt76x02_config_mac_addr_list(काष्ठा mt76x02_dev *dev);

पूर्णांक mt76x02_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_vअगर *vअगर);
व्योम mt76x02_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर);

पूर्णांक mt76x02_ampdu_action(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा ieee80211_ampdu_params *params);
पूर्णांक mt76x02_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
		    काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
		    काष्ठा ieee80211_key_conf *key);
पूर्णांक mt76x02_conf_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		    u16 queue, स्थिर काष्ठा ieee80211_tx_queue_params *params);
व्योम mt76x02_sta_rate_tbl_update(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_sta *sta);
s8 mt76x02_tx_get_max_txpwr_adj(काष्ठा mt76x02_dev *dev,
				स्थिर काष्ठा ieee80211_tx_rate *rate);
s8 mt76x02_tx_get_txpwr_adj(काष्ठा mt76x02_dev *dev, s8 txpwr,
			    s8 max_txpwr_adj);
व्योम mt76x02_wdt_work(काष्ठा work_काष्ठा *work);
व्योम mt76x02_tx_set_txpwr_स्वतः(काष्ठा mt76x02_dev *dev, s8 txpwr);
व्योम mt76x02_set_tx_ackto(काष्ठा mt76x02_dev *dev);
व्योम mt76x02_set_coverage_class(काष्ठा ieee80211_hw *hw,
				s16 coverage_class);
पूर्णांक mt76x02_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 val);
व्योम mt76x02_हटाओ_hdr_pad(काष्ठा sk_buff *skb, पूर्णांक len);
bool mt76x02_tx_status_data(काष्ठा mt76_dev *mdev, u8 *update);
व्योम mt76x02_queue_rx_skb(काष्ठा mt76_dev *mdev, क्रमागत mt76_rxq_id q,
			  काष्ठा sk_buff *skb);
व्योम mt76x02_rx_poll_complete(काष्ठा mt76_dev *mdev, क्रमागत mt76_rxq_id q);
irqवापस_t mt76x02_irq_handler(पूर्णांक irq, व्योम *dev_instance);
व्योम mt76x02_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_tx_control *control,
		काष्ठा sk_buff *skb);
पूर्णांक mt76x02_tx_prepare_skb(काष्ठा mt76_dev *mdev, व्योम *txwi,
			   क्रमागत mt76_txq_id qid, काष्ठा mt76_wcid *wcid,
			   काष्ठा ieee80211_sta *sta,
			   काष्ठा mt76_tx_info *tx_info);
व्योम mt76x02_sw_scan_complete(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर);
व्योम mt76x02_sta_ps(काष्ठा mt76_dev *dev, काष्ठा ieee80211_sta *sta, bool ps);
व्योम mt76x02_bss_info_changed(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_bss_conf *info, u32 changed);
व्योम mt76x02_reconfig_complete(काष्ठा ieee80211_hw *hw,
			       क्रमागत ieee80211_reconfig_type reconfig_type);

काष्ठा beacon_bc_data अणु
	काष्ठा mt76x02_dev *dev;
	काष्ठा sk_buff_head q;
	काष्ठा sk_buff *tail[8];
पूर्ण;

व्योम mt76x02_init_beacon_config(काष्ठा mt76x02_dev *dev);
व्योम mt76x02e_init_beacon_config(काष्ठा mt76x02_dev *dev);
व्योम mt76x02_resync_beacon_समयr(काष्ठा mt76x02_dev *dev);
व्योम mt76x02_update_beacon_iter(व्योम *priv, u8 *mac, काष्ठा ieee80211_vअगर *vअगर);
व्योम mt76x02_enqueue_buffered_bc(काष्ठा mt76x02_dev *dev,
				 काष्ठा beacon_bc_data *data,
				 पूर्णांक max_nframes);

व्योम mt76x02_mac_start(काष्ठा mt76x02_dev *dev);

व्योम mt76x02_init_debugfs(काष्ठा mt76x02_dev *dev);

अटल अंतरभूत bool is_mt76x0(काष्ठा mt76x02_dev *dev)
अणु
	वापस mt76_chip(&dev->mt76) == 0x7610 ||
	       mt76_chip(&dev->mt76) == 0x7630 ||
	       mt76_chip(&dev->mt76) == 0x7650;
पूर्ण

अटल अंतरभूत bool is_mt76x2(काष्ठा mt76x02_dev *dev)
अणु
	वापस mt76_chip(&dev->mt76) == 0x7612 ||
	       mt76_chip(&dev->mt76) == 0x7632 ||
	       mt76_chip(&dev->mt76) == 0x7662 ||
	       mt76_chip(&dev->mt76) == 0x7602;
पूर्ण

अटल अंतरभूत व्योम mt76x02_irq_enable(काष्ठा mt76x02_dev *dev, u32 mask)
अणु
	mt76_set_irq_mask(&dev->mt76, MT_INT_MASK_CSR, 0, mask);
पूर्ण

अटल अंतरभूत व्योम mt76x02_irq_disable(काष्ठा mt76x02_dev *dev, u32 mask)
अणु
	mt76_set_irq_mask(&dev->mt76, MT_INT_MASK_CSR, mask, 0);
पूर्ण

अटल अंतरभूत bool
mt76x02_रुको_क्रम_txrx_idle(काष्ठा mt76_dev *dev)
अणु
	वापस __mt76_poll_msec(dev, MT_MAC_STATUS,
				MT_MAC_STATUS_TX | MT_MAC_STATUS_RX,
				0, 100);
पूर्ण

अटल अंतरभूत काष्ठा mt76x02_sta *
mt76x02_rx_get_sta(काष्ठा mt76_dev *dev, u8 idx)
अणु
	काष्ठा mt76_wcid *wcid;

	अगर (idx >= MT76x02_N_WCIDS)
		वापस शून्य;

	wcid = rcu_dereference(dev->wcid[idx]);
	अगर (!wcid)
		वापस शून्य;

	वापस container_of(wcid, काष्ठा mt76x02_sta, wcid);
पूर्ण

अटल अंतरभूत काष्ठा mt76_wcid *
mt76x02_rx_get_sta_wcid(काष्ठा mt76x02_sta *sta, bool unicast)
अणु
	अगर (!sta)
		वापस शून्य;

	अगर (unicast)
		वापस &sta->wcid;
	अन्यथा
		वापस &sta->vअगर->group_wcid;
पूर्ण

#पूर्ण_अगर /* __MT76x02_H */
