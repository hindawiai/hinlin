<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2012 - 2018 Microchip Technology Inc., and its subsidiaries.
 * All rights reserved.
 */

#अगर_अघोषित WILC_NETDEV_H
#घोषणा WILC_NETDEV_H

#समावेश <linux/tcp.h>
#समावेश <linux/ieee80211.h>
#समावेश <net/cfg80211.h>
#समावेश <net/ieee80211_radiotap.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/gpio/consumer.h>

#समावेश "hif.h"
#समावेश "wlan.h"
#समावेश "wlan_cfg.h"

#घोषणा FLOW_CONTROL_LOWER_THRESHOLD		128
#घोषणा FLOW_CONTROL_UPPER_THRESHOLD		256

#घोषणा PMKID_FOUND				1
#घोषणा NUM_STA_ASSOCIATED			8

#घोषणा TCP_ACK_FILTER_LINK_SPEED_THRESH	54
#घोषणा DEFAULT_LINK_SPEED			72

काष्ठा wilc_wfi_stats अणु
	अचिन्हित दीर्घ rx_packets;
	अचिन्हित दीर्घ tx_packets;
	अचिन्हित दीर्घ rx_bytes;
	अचिन्हित दीर्घ tx_bytes;
	u64 rx_समय;
	u64 tx_समय;

पूर्ण;

काष्ठा wilc_wfi_key अणु
	u8 *key;
	u8 *seq;
	पूर्णांक key_len;
	पूर्णांक seq_len;
	u32 cipher;
पूर्ण;

काष्ठा wilc_wfi_wep_key अणु
	u8 *key;
	u8 key_len;
	u8 key_idx;
पूर्ण;

काष्ठा sta_info अणु
	u8 sta_associated_bss[WILC_MAX_NUM_STA][ETH_ALEN];
पूर्ण;

/* Parameters needed क्रम host पूर्णांकerface क्रम reमुख्यing on channel */
काष्ठा wilc_wfi_p2p_listen_params अणु
	काष्ठा ieee80211_channel *listen_ch;
	u32 listen_duration;
	u64 listen_cookie;
पूर्ण;

अटल स्थिर u32 wilc_cipher_suites[] = अणु
	WLAN_CIPHER_SUITE_WEP40,
	WLAN_CIPHER_SUITE_WEP104,
	WLAN_CIPHER_SUITE_TKIP,
	WLAN_CIPHER_SUITE_CCMP,
	WLAN_CIPHER_SUITE_AES_CMAC
पूर्ण;

#घोषणा CHAN2G(_channel, _freq, _flags) अणु	 \
	.band             = NL80211_BAND_2GHZ, \
	.center_freq      = (_freq),		 \
	.hw_value         = (_channel),		 \
	.flags            = (_flags),		 \
	.max_antenna_gain = 0,			 \
	.max_घातer        = 30,			 \
पूर्ण

अटल स्थिर काष्ठा ieee80211_channel wilc_2ghz_channels[] = अणु
	CHAN2G(1,  2412, 0),
	CHAN2G(2,  2417, 0),
	CHAN2G(3,  2422, 0),
	CHAN2G(4,  2427, 0),
	CHAN2G(5,  2432, 0),
	CHAN2G(6,  2437, 0),
	CHAN2G(7,  2442, 0),
	CHAN2G(8,  2447, 0),
	CHAN2G(9,  2452, 0),
	CHAN2G(10, 2457, 0),
	CHAN2G(11, 2462, 0),
	CHAN2G(12, 2467, 0),
	CHAN2G(13, 2472, 0),
	CHAN2G(14, 2484, 0)
पूर्ण;

#घोषणा RATETAB_ENT(_rate, _hw_value, _flags) अणु	\
	.bitrate  = (_rate),			\
	.hw_value = (_hw_value),		\
	.flags    = (_flags),			\
पूर्ण

अटल काष्ठा ieee80211_rate wilc_bitrates[] = अणु
	RATETAB_ENT(10,  0,  0),
	RATETAB_ENT(20,  1,  0),
	RATETAB_ENT(55,  2,  0),
	RATETAB_ENT(110, 3,  0),
	RATETAB_ENT(60,  9,  0),
	RATETAB_ENT(90,  6,  0),
	RATETAB_ENT(120, 7,  0),
	RATETAB_ENT(180, 8,  0),
	RATETAB_ENT(240, 9,  0),
	RATETAB_ENT(360, 10, 0),
	RATETAB_ENT(480, 11, 0),
	RATETAB_ENT(540, 12, 0)
पूर्ण;

काष्ठा wilc_priv अणु
	काष्ठा wireless_dev wdev;
	काष्ठा cfg80211_scan_request *scan_req;

	काष्ठा wilc_wfi_p2p_listen_params reमुख्य_on_ch_params;
	u64 tx_cookie;

	bool cfg_scanning;

	u8 associated_bss[ETH_ALEN];
	काष्ठा sta_info assoc_stainfo;
	काष्ठा sk_buff *skb;
	काष्ठा net_device *dev;
	काष्ठा host_अगर_drv *hअगर_drv;
	काष्ठा wilc_pmkid_attr pmkid_list;
	u8 wep_key[4][WLAN_KEY_LEN_WEP104];
	u8 wep_key_len[4];

	/* The real पूर्णांकerface that the monitor is on */
	काष्ठा net_device *real_ndev;
	काष्ठा wilc_wfi_key *wilc_gtk[WILC_MAX_NUM_STA];
	काष्ठा wilc_wfi_key *wilc_ptk[WILC_MAX_NUM_STA];
	u8 wilc_groupkey;

	/* mutexes */
	काष्ठा mutex scan_req_lock;
	bool p2p_listen_state;
	पूर्णांक scanned_cnt;

	u64 inc_roc_cookie;
पूर्ण;

#घोषणा MAX_TCP_SESSION                25
#घोषणा MAX_PENDING_ACKS               256

काष्ठा ack_session_info अणु
	u32 seq_num;
	u32 bigger_ack_num;
	u16 src_port;
	u16 dst_port;
	u16 status;
पूर्ण;

काष्ठा pending_acks अणु
	u32 ack_num;
	u32 session_index;
	काष्ठा txq_entry_t  *txqe;
पूर्ण;

काष्ठा tcp_ack_filter अणु
	काष्ठा ack_session_info ack_session_info[2 * MAX_TCP_SESSION];
	काष्ठा pending_acks pending_acks[MAX_PENDING_ACKS];
	u32 pending_base;
	u32 tcp_session;
	u32 pending_acks_idx;
	bool enabled;
पूर्ण;

काष्ठा wilc_vअगर अणु
	u8 idx;
	u8 अगरtype;
	पूर्णांक monitor_flag;
	पूर्णांक mac_खोलोed;
	u32 mgmt_reg_stypes;
	काष्ठा net_device_stats netstats;
	काष्ठा wilc *wilc;
	u8 bssid[ETH_ALEN];
	काष्ठा host_अगर_drv *hअगर_drv;
	काष्ठा net_device *ndev;
	u8 mode;
	काष्ठा समयr_list during_ip_समयr;
	काष्ठा समयr_list periodic_rssi;
	काष्ठा rf_info periodic_stat;
	काष्ठा tcp_ack_filter ack_filter;
	bool connecting;
	काष्ठा wilc_priv priv;
	काष्ठा list_head list;
	काष्ठा cfg80211_bss *bss;
पूर्ण;

काष्ठा wilc_tx_queue_status अणु
	u8 buffer[AC_BUFFER_SIZE];
	u16 end_index;
	u16 cnt[NQUEUES];
	u16 sum;
	bool initialized;
पूर्ण;

काष्ठा wilc अणु
	काष्ठा wiphy *wiphy;
	स्थिर काष्ठा wilc_hअगर_func *hअगर_func;
	पूर्णांक io_type;
	s8 mac_status;
	काष्ठा clk *rtc_clk;
	bool initialized;
	पूर्णांक dev_irq_num;
	पूर्णांक बंद;
	u8 vअगर_num;
	काष्ठा list_head vअगर_list;

	/* protect vअगर list */
	काष्ठा mutex vअगर_mutex;
	काष्ठा srcu_काष्ठा srcu;
	u8 खोलो_अगरcs;

	/* protect head of transmit queue */
	काष्ठा mutex txq_add_to_head_cs;

	/* protect txq_entry_t transmit queue */
	spinlock_t txq_spinlock;

	/* protect rxq_entry_t receiver queue */
	काष्ठा mutex rxq_cs;

	/* lock to protect hअगर access */
	काष्ठा mutex hअगर_cs;

	काष्ठा completion cfg_event;
	काष्ठा completion sync_event;
	काष्ठा completion txq_event;
	काष्ठा completion txq_thपढ़ो_started;

	काष्ठा task_काष्ठा *txq_thपढ़ो;

	पूर्णांक quit;

	/* lock to protect issue of wid command to firmware */
	काष्ठा mutex cfg_cmd_lock;
	काष्ठा wilc_cfg_frame cfg_frame;
	u32 cfg_frame_offset;
	u8 cfg_seq_no;

	u8 *rx_buffer;
	u32 rx_buffer_offset;
	u8 *tx_buffer;

	काष्ठा txq_handle txq[NQUEUES];
	पूर्णांक txq_entries;

	काष्ठा wilc_tx_queue_status tx_q_limit;
	काष्ठा rxq_entry_t rxq_head;

	स्थिर काष्ठा firmware *firmware;

	काष्ठा device *dev;
	bool suspend_event;

	पूर्णांक clients_count;
	काष्ठा workqueue_काष्ठा *hअगर_workqueue;
	क्रमागत chip_ps_states chip_ps_state;
	काष्ठा wilc_cfg cfg;
	व्योम *bus_data;
	काष्ठा net_device *monitor_dev;

	/* deinit lock */
	काष्ठा mutex deinit_lock;
	u8 sta_ch;
	u8 op_ch;
	काष्ठा ieee80211_channel channels[ARRAY_SIZE(wilc_2ghz_channels)];
	काष्ठा ieee80211_rate bitrates[ARRAY_SIZE(wilc_bitrates)];
	काष्ठा ieee80211_supported_band band;
	u32 cipher_suites[ARRAY_SIZE(wilc_cipher_suites)];
पूर्ण;

काष्ठा wilc_wfi_mon_priv अणु
	काष्ठा net_device *real_ndev;
पूर्ण;

व्योम wilc_frmw_to_host(काष्ठा wilc *wilc, u8 *buff, u32 size, u32 pkt_offset);
व्योम wilc_mac_indicate(काष्ठा wilc *wilc);
व्योम wilc_netdev_cleanup(काष्ठा wilc *wilc);
व्योम wilc_wfi_mgmt_rx(काष्ठा wilc *wilc, u8 *buff, u32 size);
व्योम wilc_wlan_set_bssid(काष्ठा net_device *wilc_netdev, u8 *bssid, u8 mode);
काष्ठा wilc_vअगर *wilc_netdev_अगरc_init(काष्ठा wilc *wl, स्थिर अक्षर *name,
				      पूर्णांक vअगर_type, क्रमागत nl80211_अगरtype type,
				      bool rtnl_locked);
#पूर्ण_अगर
