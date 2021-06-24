<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 */

#अगर_अघोषित MT7601U_H
#घोषणा MT7601U_H

#समावेश <linux/bitfield.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/usb.h>
#समावेश <linux/completion.h>
#समावेश <net/mac80211.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/average.h>

#समावेश "regs.h"

#घोषणा MT_CALIBRATE_INTERVAL		(4 * HZ)

#घोषणा MT_FREQ_CAL_INIT_DELAY		(30 * HZ)
#घोषणा MT_FREQ_CAL_CHECK_INTERVAL	(10 * HZ)
#घोषणा MT_FREQ_CAL_ADJ_INTERVAL	(HZ / 2)

#घोषणा MT_BBP_REG_VERSION		0x00

#घोषणा MT_USB_AGGR_SIZE_LIMIT		28 /* * 1024B */
#घोषणा MT_USB_AGGR_TIMEOUT		0x80 /* * 33ns */
#घोषणा MT_RX_ORDER			3
#घोषणा MT_RX_URB_SIZE			(PAGE_SIZE << MT_RX_ORDER)

काष्ठा mt7601u_dma_buf अणु
	काष्ठा urb *urb;
	व्योम *buf;
	dma_addr_t dma;
	माप_प्रकार len;
पूर्ण;

काष्ठा mt7601u_mcu अणु
	काष्ठा mutex mutex;

	u8 msg_seq;

	काष्ठा mt7601u_dma_buf resp;
	काष्ठा completion resp_cmpl;
पूर्ण;

काष्ठा mt7601u_freq_cal अणु
	काष्ठा delayed_work work;
	u8 freq;
	bool enabled;
	bool adjusting;
पूर्ण;

काष्ठा mac_stats अणु
	u64 rx_stat[6];
	u64 tx_stat[6];
	u64 aggr_stat[2];
	u64 aggr_n[32];
	u64 zero_len_del[2];
पूर्ण;

#घोषणा N_RX_ENTRIES	16
काष्ठा mt7601u_rx_queue अणु
	काष्ठा mt7601u_dev *dev;

	काष्ठा mt7601u_dma_buf_rx अणु
		काष्ठा urb *urb;
		काष्ठा page *p;
	पूर्ण e[N_RX_ENTRIES];

	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक end;
	अचिन्हित पूर्णांक entries;
	अचिन्हित पूर्णांक pending;
पूर्ण;

#घोषणा N_TX_ENTRIES	64

काष्ठा mt7601u_tx_queue अणु
	काष्ठा mt7601u_dev *dev;

	काष्ठा mt7601u_dma_buf_tx अणु
		काष्ठा urb *urb;
		काष्ठा sk_buff *skb;
	पूर्ण e[N_TX_ENTRIES];

	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक end;
	अचिन्हित पूर्णांक entries;
	अचिन्हित पूर्णांक used;
	अचिन्हित पूर्णांक fअगरo_seq;
पूर्ण;

/* WCID allocation:
 *     0: mcast wcid
 *     1: bssid wcid
 *  1...: STAs
 * ...7e: group wcids
 *    7f: reserved
 */
#घोषणा N_WCIDS		128
#घोषणा GROUP_WCID(idx)	(N_WCIDS - 2 - idx)

काष्ठा mt7601u_eeprom_params;

#घोषणा MT_EE_TEMPERATURE_SLOPE		39
#घोषणा MT_FREQ_OFFSET_INVALID		-128

क्रमागत mt_temp_mode अणु
	MT_TEMP_MODE_NORMAL,
	MT_TEMP_MODE_HIGH,
	MT_TEMP_MODE_LOW,
पूर्ण;

क्रमागत mt_bw अणु
	MT_BW_20,
	MT_BW_40,
पूर्ण;

क्रमागत अणु
	MT7601U_STATE_INITIALIZED,
	MT7601U_STATE_REMOVED,
	MT7601U_STATE_WLAN_RUNNING,
	MT7601U_STATE_MCU_RUNNING,
	MT7601U_STATE_SCANNING,
	MT7601U_STATE_READING_STATS,
	MT7601U_STATE_MORE_STATS,
पूर्ण;

DECLARE_EWMA(rssi, 10, 4);

/**
 * काष्ठा mt7601u_dev - adapter काष्ठाure
 * @lock:		protects @wcid->tx_rate.
 * @mac_lock:		locks out mac80211's tx status and rx paths.
 * @tx_lock:		protects @tx_q and changes of MT7601U_STATE_*_STATS
 *			flags in @state.
 * @rx_lock:		protects @rx_q.
 * @con_mon_lock:	protects @ap_bssid, @bcn_*, @avg_rssi.
 * @mutex:		ensures exclusive access from mac80211 callbacks.
 * @venकरोr_req_mutex:	protects @vend_buf, ensures atomicity of पढ़ो/ग_लिखो
 *			accesses
 * @reg_atomic_mutex:	ensures atomicity of indirect रेजिस्टर accesses
 *			(accesses to RF and BBP).
 * @hw_atomic_mutex:	ensures exclusive access to HW during critical
 *			operations (घातer management, channel चयन).
 */
काष्ठा mt7601u_dev अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा device *dev;

	अचिन्हित दीर्घ state;

	काष्ठा mutex mutex;

	अचिन्हित दीर्घ wcid_mask[N_WCIDS / BITS_PER_LONG];

	काष्ठा cfg80211_chan_def chandef;
	काष्ठा ieee80211_supported_band *sband_2g;

	काष्ठा mt7601u_mcu mcu;

	काष्ठा delayed_work cal_work;
	काष्ठा delayed_work mac_work;

	काष्ठा workqueue_काष्ठा *stat_wq;
	काष्ठा delayed_work stat_work;

	काष्ठा mt76_wcid *mon_wcid;
	काष्ठा mt76_wcid __rcu *wcid[N_WCIDS];

	spinlock_t lock;
	spinlock_t mac_lock;

	स्थिर u16 *beacon_offsets;

	u8 macaddr[ETH_ALEN];
	काष्ठा mt7601u_eeprom_params *ee;

	काष्ठा mutex venकरोr_req_mutex;
	व्योम *vend_buf;

	काष्ठा mutex reg_atomic_mutex;
	काष्ठा mutex hw_atomic_mutex;

	u32 rxfilter;
	u32 debugfs_reg;

	u8 out_eps[8];
	u8 in_eps[8];
	u16 out_max_packet;
	u16 in_max_packet;

	/* TX */
	spinlock_t tx_lock;
	काष्ठा tasklet_काष्ठा tx_tasklet;
	काष्ठा mt7601u_tx_queue *tx_q;
	काष्ठा sk_buff_head tx_skb_करोne;

	atomic_t avg_ampdu_len;

	/* RX */
	spinlock_t rx_lock;
	काष्ठा tasklet_काष्ठा rx_tasklet;
	काष्ठा mt7601u_rx_queue rx_q;

	/* Connection monitoring things */
	spinlock_t con_mon_lock;
	u8 ap_bssid[ETH_ALEN];

	s8 bcn_freq_off;
	u8 bcn_phy_mode;

	काष्ठा ewma_rssi avg_rssi;

	u8 agc_save;

	काष्ठा mt7601u_freq_cal freq_cal;

	bool tssi_पढ़ो_trig;

	s8 tssi_init;
	s8 tssi_init_hvga;
	s16 tssi_init_hvga_offset_db;

	पूर्णांक prev_pwr_dअगरf;

	क्रमागत mt_temp_mode temp_mode;
	पूर्णांक curr_temp;
	पूर्णांक dpd_temp;
	s8 raw_temp;
	bool pll_lock_protect;

	u8 bw;
	bool chan_ext_below;

	/* PA mode */
	u32 rf_pa_mode[2];

	काष्ठा mac_stats stats;
पूर्ण;

काष्ठा mt7601u_tssi_params अणु
	अक्षर tssi0;
	पूर्णांक trgt_घातer;
पूर्ण;

काष्ठा mt76_wcid अणु
	u8 idx;
	u8 hw_key_idx;

	u16 tx_rate;
	bool tx_rate_set;
	u8 tx_rate_nss;
पूर्ण;

काष्ठा mt76_vअगर अणु
	u8 idx;

	काष्ठा mt76_wcid group_wcid;
पूर्ण;

काष्ठा mt76_sta अणु
	काष्ठा mt76_wcid wcid;
	u16 agg_ssn[IEEE80211_NUM_TIDS];
पूर्ण;

काष्ठा mt76_reg_pair अणु
	u32 reg;
	u32 value;
पूर्ण;

काष्ठा mt7601u_rxwi;

बाह्य स्थिर काष्ठा ieee80211_ops mt7601u_ops;

व्योम mt7601u_init_debugfs(काष्ठा mt7601u_dev *dev);

u32 mt7601u_rr(काष्ठा mt7601u_dev *dev, u32 offset);
व्योम mt7601u_wr(काष्ठा mt7601u_dev *dev, u32 offset, u32 val);
u32 mt7601u_rmw(काष्ठा mt7601u_dev *dev, u32 offset, u32 mask, u32 val);
u32 mt7601u_rmc(काष्ठा mt7601u_dev *dev, u32 offset, u32 mask, u32 val);
व्योम mt7601u_wr_copy(काष्ठा mt7601u_dev *dev, u32 offset,
		     स्थिर व्योम *data, पूर्णांक len);

पूर्णांक mt7601u_रुको_asic_पढ़ोy(काष्ठा mt7601u_dev *dev);
bool mt76_poll(काष्ठा mt7601u_dev *dev, u32 offset, u32 mask, u32 val,
	       पूर्णांक समयout);
bool mt76_poll_msec(काष्ठा mt7601u_dev *dev, u32 offset, u32 mask, u32 val,
		    पूर्णांक समयout);

/* Compatibility with mt76 */
#घोषणा mt76_rmw_field(_dev, _reg, _field, _val)	\
	mt76_rmw(_dev, _reg, _field, FIELD_PREP(_field, _val))

अटल अंतरभूत u32 mt76_rr(काष्ठा mt7601u_dev *dev, u32 offset)
अणु
	वापस mt7601u_rr(dev, offset);
पूर्ण

अटल अंतरभूत व्योम mt76_wr(काष्ठा mt7601u_dev *dev, u32 offset, u32 val)
अणु
	वापस mt7601u_wr(dev, offset, val);
पूर्ण

अटल अंतरभूत u32
mt76_rmw(काष्ठा mt7601u_dev *dev, u32 offset, u32 mask, u32 val)
अणु
	वापस mt7601u_rmw(dev, offset, mask, val);
पूर्ण

अटल अंतरभूत u32 mt76_set(काष्ठा mt7601u_dev *dev, u32 offset, u32 val)
अणु
	वापस mt76_rmw(dev, offset, 0, val);
पूर्ण

अटल अंतरभूत u32 mt76_clear(काष्ठा mt7601u_dev *dev, u32 offset, u32 val)
अणु
	वापस mt76_rmw(dev, offset, val, 0);
पूर्ण

पूर्णांक mt7601u_ग_लिखो_reg_pairs(काष्ठा mt7601u_dev *dev, u32 base,
			    स्थिर काष्ठा mt76_reg_pair *data, पूर्णांक len);
पूर्णांक mt7601u_burst_ग_लिखो_regs(काष्ठा mt7601u_dev *dev, u32 offset,
			     स्थिर u32 *data, पूर्णांक n);
व्योम mt7601u_addr_wr(काष्ठा mt7601u_dev *dev, स्थिर u32 offset, स्थिर u8 *addr);

/* Init */
काष्ठा mt7601u_dev *mt7601u_alloc_device(काष्ठा device *dev);
पूर्णांक mt7601u_init_hardware(काष्ठा mt7601u_dev *dev);
पूर्णांक mt7601u_रेजिस्टर_device(काष्ठा mt7601u_dev *dev);
व्योम mt7601u_cleanup(काष्ठा mt7601u_dev *dev);

पूर्णांक mt7601u_mac_start(काष्ठा mt7601u_dev *dev);
व्योम mt7601u_mac_stop(काष्ठा mt7601u_dev *dev);

/* PHY */
पूर्णांक mt7601u_phy_init(काष्ठा mt7601u_dev *dev);
पूर्णांक mt7601u_रुको_bbp_पढ़ोy(काष्ठा mt7601u_dev *dev);
व्योम mt7601u_set_rx_path(काष्ठा mt7601u_dev *dev, u8 path);
व्योम mt7601u_set_tx_dac(काष्ठा mt7601u_dev *dev, u8 path);
पूर्णांक mt7601u_bbp_set_bw(काष्ठा mt7601u_dev *dev, पूर्णांक bw);
व्योम mt7601u_agc_save(काष्ठा mt7601u_dev *dev);
व्योम mt7601u_agc_restore(काष्ठा mt7601u_dev *dev);
पूर्णांक mt7601u_phy_set_channel(काष्ठा mt7601u_dev *dev,
			    काष्ठा cfg80211_chan_def *chandef);
व्योम mt7601u_phy_recalibrate_after_assoc(काष्ठा mt7601u_dev *dev);
पूर्णांक mt7601u_phy_get_rssi(काष्ठा mt7601u_dev *dev,
			 काष्ठा mt7601u_rxwi *rxwi, u16 rate);
व्योम mt7601u_phy_con_cal_onoff(काष्ठा mt7601u_dev *dev,
			       काष्ठा ieee80211_bss_conf *info);

/* MAC */
व्योम mt7601u_mac_work(काष्ठा work_काष्ठा *work);
व्योम mt7601u_mac_set_protection(काष्ठा mt7601u_dev *dev, bool legacy_prot,
				पूर्णांक ht_mode);
व्योम mt7601u_mac_set_लघु_preamble(काष्ठा mt7601u_dev *dev, bool लघु_preamb);
व्योम mt7601u_mac_config_tsf(काष्ठा mt7601u_dev *dev, bool enable, पूर्णांक पूर्णांकerval);
व्योम
mt7601u_mac_wcid_setup(काष्ठा mt7601u_dev *dev, u8 idx, u8 vअगर_idx, u8 *mac);
व्योम mt7601u_mac_set_ampdu_factor(काष्ठा mt7601u_dev *dev);

/* TX */
व्योम mt7601u_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_tx_control *control,
		काष्ठा sk_buff *skb);
पूर्णांक mt7601u_conf_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		    u16 queue, स्थिर काष्ठा ieee80211_tx_queue_params *params);
व्योम mt7601u_tx_status(काष्ठा mt7601u_dev *dev, काष्ठा sk_buff *skb);
व्योम mt7601u_tx_stat(काष्ठा work_काष्ठा *work);

/* util */
व्योम mt76_हटाओ_hdr_pad(काष्ठा sk_buff *skb);
पूर्णांक mt76_insert_hdr_pad(काष्ठा sk_buff *skb);

u32 mt7601u_bbp_set_ctrlch(काष्ठा mt7601u_dev *dev, bool below);

अटल अंतरभूत u32 mt7601u_mac_set_ctrlch(काष्ठा mt7601u_dev *dev, bool below)
अणु
	वापस mt7601u_rmc(dev, MT_TX_BAND_CFG, 1, below);
पूर्ण

पूर्णांक mt7601u_dma_init(काष्ठा mt7601u_dev *dev);
व्योम mt7601u_dma_cleanup(काष्ठा mt7601u_dev *dev);

पूर्णांक mt7601u_dma_enqueue_tx(काष्ठा mt7601u_dev *dev, काष्ठा sk_buff *skb,
			   काष्ठा mt76_wcid *wcid, पूर्णांक hw_q);

#पूर्ण_अगर
