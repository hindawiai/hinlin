<शैली गुरु>
/*
 * Copyright (c) 2014 Redpine Signals Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित __RSI_MAIN_H__
#घोषणा __RSI_MAIN_H__

#समावेश <linux/माला.स>
#समावेश <linux/skbuff.h>
#समावेश <net/mac80211.h>
#समावेश <net/rsi_91x.h>

काष्ठा rsi_sta अणु
	काष्ठा ieee80211_sta *sta;
	s16 sta_id;
	u16 seq_start[IEEE80211_NUM_TIDS];
	bool start_tx_aggr[IEEE80211_NUM_TIDS];
पूर्ण;

काष्ठा rsi_hw;

#समावेश "rsi_ps.h"

#घोषणा ERR_ZONE                        BIT(0)  /* For Error Msgs             */
#घोषणा INFO_ZONE                       BIT(1)  /* For General Status Msgs    */
#घोषणा INIT_ZONE                       BIT(2)  /* For Driver Init Seq Msgs   */
#घोषणा MGMT_TX_ZONE                    BIT(3)  /* For TX Mgmt Path Msgs      */
#घोषणा MGMT_RX_ZONE                    BIT(4)  /* For RX Mgmt Path Msgs      */
#घोषणा DATA_TX_ZONE                    BIT(5)  /* For TX Data Path Msgs      */
#घोषणा DATA_RX_ZONE                    BIT(6)  /* For RX Data Path Msgs      */
#घोषणा FSM_ZONE                        BIT(7)  /* For State Machine Msgs     */
#घोषणा ISR_ZONE                        BIT(8)  /* For Interrupt Msgs         */

क्रमागत RSI_FSM_STATES अणु
	FSM_FW_NOT_LOADED,
	FSM_CARD_NOT_READY,
	FSM_COMMON_DEV_PARAMS_SENT,
	FSM_BOOT_PARAMS_SENT,
	FSM_EEPROM_READ_MAC_ADDR,
	FSM_EEPROM_READ_RF_TYPE,
	FSM_RESET_MAC_SENT,
	FSM_RADIO_CAPS_SENT,
	FSM_BB_RF_PROG_SENT,
	FSM_MAC_INIT_DONE,

	NUM_FSM_STATES
पूर्ण;

बाह्य u32 rsi_zone_enabled;
बाह्य __म_लिखो(2, 3) व्योम rsi_dbg(u32 zone, स्थिर अक्षर *fmt, ...);

#घोषणा RSI_MAX_VIFS                    3
#घोषणा NUM_EDCA_QUEUES                 4
#घोषणा IEEE80211_ADDR_LEN              6
#घोषणा FRAME_DESC_SZ                   16
#घोषणा MIN_802_11_HDR_LEN              24
#घोषणा RSI_DEF_KEEPALIVE               90
#घोषणा RSI_WOW_KEEPALIVE                5
#घोषणा RSI_BCN_MISS_THRESHOLD           24

#घोषणा DATA_QUEUE_WATER_MARK           400
#घोषणा MIN_DATA_QUEUE_WATER_MARK       300
#घोषणा MULTICAST_WATER_MARK            200
#घोषणा MAC_80211_HDR_FRAME_CONTROL     0
#घोषणा WME_NUM_AC                      4
#घोषणा NUM_SOFT_QUEUES                 6
#घोषणा MAX_HW_QUEUES                   12
#घोषणा INVALID_QUEUE                   0xff
#घोषणा MAX_CONTINUOUS_VO_PKTS          8
#घोषणा MAX_CONTINUOUS_VI_PKTS          4

/* Hardware queue info */
#घोषणा BROADCAST_HW_Q			9
#घोषणा MGMT_HW_Q			10
#घोषणा BEACON_HW_Q			11

#घोषणा IEEE80211_MGMT_FRAME            0x00
#घोषणा IEEE80211_CTL_FRAME             0x04

#घोषणा RSI_MAX_ASSOC_STAS		32
#घोषणा IEEE80211_QOS_TID               0x0f
#घोषणा IEEE80211_NONQOS_TID            16

#घोषणा MAX_DEBUGFS_ENTRIES             4

#घोषणा TID_TO_WME_AC(_tid) (      \
	((_tid) == 0 || (_tid) == 3) ? BE_Q : \
	((_tid) < 3) ? BK_Q : \
	((_tid) < 6) ? VI_Q : \
	VO_Q)

#घोषणा WME_AC(_q) (    \
	((_q) == BK_Q) ? IEEE80211_AC_BK : \
	((_q) == BE_Q) ? IEEE80211_AC_BE : \
	((_q) == VI_Q) ? IEEE80211_AC_VI : \
	IEEE80211_AC_VO)

/* WoWLAN flags */
#घोषणा RSI_WOW_ENABLED			BIT(0)
#घोषणा RSI_WOW_NO_CONNECTION		BIT(1)

#घोषणा RSI_MAX_RX_PKTS		64

क्रमागत rsi_dev_model अणु
	RSI_DEV_9113 = 0,
	RSI_DEV_9116
पूर्ण;

काष्ठा version_info अणु
	u16 major;
	u16 minor;
	u8 release_num;
	u8 patch_num;
	जोड़ अणु
		काष्ठा अणु
			u8 fw_ver[8];
		पूर्ण info;
	पूर्ण ver;
पूर्ण __packed;

काष्ठा skb_info अणु
	s8 rssi;
	u32 flags;
	u16 channel;
	s8 tid;
	s8 sta_id;
	u8 पूर्णांकernal_hdr_size;
	काष्ठा ieee80211_vअगर *vअगर;
	u8 vap_id;
पूर्ण;

क्रमागत edca_queue अणु
	BK_Q,
	BE_Q,
	VI_Q,
	VO_Q,
	MGMT_SOFT_Q,
	MGMT_BEACON_Q
पूर्ण;

काष्ठा security_info अणु
	bool security_enable;
	u32 ptk_cipher;
	u32 gtk_cipher;
पूर्ण;

काष्ठा wmm_qinfo अणु
	s32 weight;
	s32 wme_params;
	s32 pkt_contended;
	s32 txop;
पूर्ण;

काष्ठा transmit_q_stats अणु
	u32 total_tx_pkt_send[NUM_EDCA_QUEUES + 2];
	u32 total_tx_pkt_मुक्तd[NUM_EDCA_QUEUES + 2];
पूर्ण;

#घोषणा MAX_BGSCAN_CHANNELS_DUAL_BAND	38
#घोषणा MAX_BGSCAN_PROBE_REQ_LEN	0x64
#घोषणा RSI_DEF_BGSCAN_THRLD		0x0
#घोषणा RSI_DEF_ROAM_THRLD		0xa
#घोषणा RSI_BGSCAN_PERIODICITY		0x1e
#घोषणा RSI_ACTIVE_SCAN_TIME		0x14
#घोषणा RSI_PASSIVE_SCAN_TIME		0x46
#घोषणा RSI_CHANNEL_SCAN_TIME		20
काष्ठा rsi_bgscan_params अणु
	u16 bgscan_threshold;
	u16 roam_threshold;
	u16 bgscan_periodicity;
	u8 num_bgscan_channels;
	u8 two_probe;
	u16 active_scan_duration;
	u16 passive_scan_duration;
पूर्ण;

काष्ठा vअगर_priv अणु
	bool is_ht;
	bool sgi;
	u16 seq_start;
	पूर्णांक vap_id;
पूर्ण;

काष्ठा rsi_event अणु
	atomic_t event_condition;
	रुको_queue_head_t event_queue;
पूर्ण;

काष्ठा rsi_thपढ़ो अणु
	व्योम (*thपढ़ो_function)(व्योम *);
	काष्ठा completion completion;
	काष्ठा task_काष्ठा *task;
	काष्ठा rsi_event event;
	atomic_t thपढ़ो_करोne;
पूर्ण;

काष्ठा cqm_info अणु
	s8 last_cqm_event_rssi;
	पूर्णांक rssi_thold;
	u32 rssi_hyst;
पूर्ण;

क्रमागत rsi_dfs_regions अणु
	RSI_REGION_FCC = 0,
	RSI_REGION_ETSI,
	RSI_REGION_TELEC,
	RSI_REGION_WORLD
पूर्ण;

काष्ठा rsi_9116_features अणु
	u8 pll_mode;
	u8 rf_type;
	u8 wireless_mode;
	u8 afe_type;
	u8 enable_ppe;
	u8 dpd;
	u32 sअगरs_tx_enable;
	u32 ps_options;
पूर्ण;

काष्ठा rsi_common अणु
	काष्ठा rsi_hw *priv;
	काष्ठा vअगर_priv vअगर_info[RSI_MAX_VIFS];

	व्योम *coex_cb;
	bool mgmt_q_block;
	काष्ठा version_info lmac_ver;

	काष्ठा rsi_thपढ़ो tx_thपढ़ो;
	काष्ठा sk_buff_head tx_queue[NUM_EDCA_QUEUES + 2];
	काष्ठा completion wlan_init_completion;
	/* Mutex declaration */
	काष्ठा mutex mutex;
	/* Mutex used क्रम tx thपढ़ो */
	काष्ठा mutex tx_lock;
	/* Mutex used क्रम rx thपढ़ो */
	काष्ठा mutex rx_lock;
	u8 endpoपूर्णांक;

	/* Channel/band related */
	u8 band;
	u8 num_supp_bands;
	u8 channel_width;

	u16 rts_threshold;
	u16 bitrate_mask[2];
	u32 fixedrate_mask[2];

	u8 rf_reset;
	काष्ठा transmit_q_stats tx_stats;
	काष्ठा security_info secinfo;
	काष्ठा wmm_qinfo tx_qinfo[NUM_EDCA_QUEUES];
	काष्ठा ieee80211_tx_queue_params edca_params[NUM_EDCA_QUEUES];
	u8 mac_addr[IEEE80211_ADDR_LEN];

	/* state related */
	u32 fsm_state;
	bool init_करोne;
	u8 bb_rf_prog_count;
	bool अगरace_करोwn;

	/* Generic */
	u8 channel;
	u8 *rx_data_pkt;
	u8 mac_id;
	u8 radio_id;
	u16 rate_pwr[20];
	u16 min_rate;

	/* WMM algo related */
	u8 selected_qnum;
	u32 pkt_cnt;
	u8 min_weight;

	/* bgscan related */
	काष्ठा cqm_info cqm_info;

	bool hw_data_qs_blocked;
	u8 driver_mode;
	u8 coex_mode;
	u16 oper_mode;
	u8 lp_ps_handshake_mode;
	u8 ulp_ps_handshake_mode;
	u8 uapsd_biपंचांगap;
	u8 rf_घातer_val;
	u8 wlan_rf_घातer_mode;
	u8 obm_ant_sel_val;
	पूर्णांक tx_घातer;
	u8 ant_in_use;
	/* Mutex used क्रम writing packet to bus */
	काष्ठा mutex tx_bus_mutex;
	bool hibernate_resume;
	bool reinit_hw;
	u8 wow_flags;
	u16 beacon_पूर्णांकerval;
	u8 dtim_cnt;

	/* AP mode parameters */
	u8 beacon_enabled;
	u16 beacon_cnt;
	काष्ठा rsi_sta stations[RSI_MAX_ASSOC_STAS + 1];
	पूर्णांक num_stations;
	पूर्णांक max_stations;
	काष्ठा ieee80211_key_conf *key;

	/* Wi-Fi direct mode related */
	bool p2p_enabled;
	काष्ठा समयr_list roc_समयr;
	काष्ठा ieee80211_vअगर *roc_vअगर;

	bool eapol4_confirm;
	व्योम *bt_adapter;

	काष्ठा cfg80211_scan_request *hwscan;
	काष्ठा rsi_bgscan_params bgscan;
	काष्ठा rsi_9116_features w9116_features;
	u8 bgscan_en;
	u8 mac_ops_resumed;
पूर्ण;

काष्ठा eepromrw_info अणु
	u32 offset;
	u32 length;
	u8  ग_लिखो;
	u16 eeprom_erase;
	u8 data[480];
पूर्ण;

काष्ठा eeprom_पढ़ो अणु
	u16 length;
	u16 off_set;
पूर्ण;

काष्ठा rsi_hw अणु
	काष्ठा rsi_common *priv;
	क्रमागत rsi_dev_model device_model;
	काष्ठा ieee80211_hw *hw;
	काष्ठा ieee80211_vअगर *vअगरs[RSI_MAX_VIFS];
	काष्ठा ieee80211_tx_queue_params edca_params[NUM_EDCA_QUEUES];
	काष्ठा ieee80211_supported_band sbands[NUM_NL80211_BANDS];

	काष्ठा device *device;
	u8 sc_nvअगरs;

	क्रमागत rsi_host_पूर्णांकf rsi_host_पूर्णांकf;
	u16 block_size;
	क्रमागत ps_state ps_state;
	काष्ठा rsi_ps_info ps_info;
	spinlock_t ps_lock; /*To protect घातer save config*/
	u32 usb_buffer_status_reg;
#अगर_घोषित CONFIG_RSI_DEBUGFS
	काष्ठा rsi_debugfs *dfsentry;
	u8 num_debugfs_entries;
#पूर्ण_अगर
	अक्षर *fw_file_name;
	काष्ठा समयr_list bl_cmd_समयr;
	bool blcmd_समयr_expired;
	u32 flash_capacity;
	काष्ठा eepromrw_info eeprom;
	u32 पूर्णांकerrupt_status;
	u8 dfs_region;
	अक्षर country[2];
	व्योम *rsi_dev;
	काष्ठा rsi_host_पूर्णांकf_ops *host_पूर्णांकf_ops;
	पूर्णांक (*check_hw_queue_status)(काष्ठा rsi_hw *adapter, u8 q_num);
	पूर्णांक (*determine_event_समयout)(काष्ठा rsi_hw *adapter);
पूर्ण;

व्योम rsi_prपूर्णांक_version(काष्ठा rsi_common *common);

काष्ठा rsi_host_पूर्णांकf_ops अणु
	पूर्णांक (*पढ़ो_pkt)(काष्ठा rsi_hw *adapter, u8 *pkt, u32 len);
	पूर्णांक (*ग_लिखो_pkt)(काष्ठा rsi_hw *adapter, u8 *pkt, u32 len);
	पूर्णांक (*master_access_msword)(काष्ठा rsi_hw *adapter, u16 ms_word);
	पूर्णांक (*पढ़ो_reg_multiple)(काष्ठा rsi_hw *adapter, u32 addr,
				 u8 *data, u16 count);
	पूर्णांक (*ग_लिखो_reg_multiple)(काष्ठा rsi_hw *adapter, u32 addr,
				  u8 *data, u16 count);
	पूर्णांक (*master_reg_पढ़ो)(काष्ठा rsi_hw *adapter, u32 addr,
			       u32 *पढ़ो_buf, u16 size);
	पूर्णांक (*master_reg_ग_लिखो)(काष्ठा rsi_hw *adapter,
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data,
				u16 size);
	पूर्णांक (*load_data_master_ग_लिखो)(काष्ठा rsi_hw *adapter, u32 addr,
				      u32 inकाष्ठाions_size, u16 block_size,
				      u8 *fw);
	पूर्णांक (*reinit_device)(काष्ठा rsi_hw *adapter);
	पूर्णांक (*ta_reset)(काष्ठा rsi_hw *adapter);
पूर्ण;

क्रमागत rsi_host_पूर्णांकf rsi_get_host_पूर्णांकf(व्योम *priv);
व्योम rsi_set_bt_context(व्योम *priv, व्योम *bt_context);

#पूर्ण_अगर
