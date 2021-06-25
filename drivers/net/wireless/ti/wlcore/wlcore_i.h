<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl1271
 *
 * Copyright (C) 1998-2009 Texas Instruments. All rights reserved.
 * Copyright (C) 2008-2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#अगर_अघोषित __WLCORE_I_H__
#घोषणा __WLCORE_I_H__

#समावेश <linux/mutex.h>
#समावेश <linux/completion.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/bitops.h>
#समावेश <net/mac80211.h>

#समावेश "conf.h"
#समावेश "ini.h"

काष्ठा wilink_family_data अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *nvs_name;	/* wl12xx nvs file */
	स्थिर अक्षर *cfg_name;	/* wl18xx cfg file */
पूर्ण;

#घोषणा WL1271_TX_SECURITY_LO16(s) ((u16)((s) & 0xffff))
#घोषणा WL1271_TX_SECURITY_HI32(s) ((u32)(((s) >> 16) & 0xffffffff))
#घोषणा WL1271_TX_SQN_POST_RECOVERY_PADDING 0xff
/* Use smaller padding क्रम GEM, as some  APs have issues when it's too big */
#घोषणा WL1271_TX_SQN_POST_RECOVERY_PADDING_GEM 0x20


#घोषणा WL1271_CIPHER_SUITE_GEM 0x00147201

#घोषणा WL1271_BUSY_WORD_CNT 1
#घोषणा WL1271_BUSY_WORD_LEN (WL1271_BUSY_WORD_CNT * माप(u32))

#घोषणा WL1271_ELP_HW_STATE_ASLEEP 0
#घोषणा WL1271_ELP_HW_STATE_IRQ    1

#घोषणा WL1271_DEFAULT_BEACON_INT  100
#घोषणा WL1271_DEFAULT_DTIM_PERIOD 1

#घोषणा WL12XX_MAX_ROLES           4
#घोषणा WL12XX_INVALID_ROLE_ID     0xff
#घोषणा WL12XX_INVALID_LINK_ID     0xff

/*
 * max number of links allowed by all HWs.
 * this is NOT the actual max links supported by the current hw.
 */
#घोषणा WLCORE_MAX_LINKS 16

/* the driver supports the 2.4Ghz and 5Ghz bands */
#घोषणा WLCORE_NUM_BANDS           2

#घोषणा WL12XX_MAX_RATE_POLICIES 16
#घोषणा WLCORE_MAX_KLV_TEMPLATES 4

/* Defined by FW as 0. Will not be मुक्तd or allocated. */
#घोषणा WL12XX_SYSTEM_HLID         0

/*
 * When in AP-mode, we allow (at least) this number of packets
 * to be transmitted to FW क्रम a STA in PS-mode. Only when packets are
 * present in the FW buffers it will wake the sleeping STA. We want to put
 * enough packets क्रम the driver to transmit all of its buffered data beक्रमe
 * the STA goes to sleep again. But we करोn't want to take too much memory
 * as it might hurt the throughput of active STAs.
 */
#घोषणा WL1271_PS_STA_MAX_PACKETS  2

#घोषणा WL1271_AP_BSS_INDEX        0
#घोषणा WL1271_AP_DEF_BEACON_EXP   20

क्रमागत wlcore_state अणु
	WLCORE_STATE_OFF,
	WLCORE_STATE_RESTARTING,
	WLCORE_STATE_ON,
पूर्ण;

क्रमागत wl12xx_fw_type अणु
	WL12XX_FW_TYPE_NONE,
	WL12XX_FW_TYPE_NORMAL,
	WL12XX_FW_TYPE_MULTI,
	WL12XX_FW_TYPE_PLT,
पूर्ण;

काष्ठा wl1271;

क्रमागत अणु
	FW_VER_CHIP,
	FW_VER_IF_TYPE,
	FW_VER_MAJOR,
	FW_VER_SUBTYPE,
	FW_VER_MINOR,

	NUM_FW_VER
पूर्ण;

काष्ठा wl1271_chip अणु
	u32 id;
	अक्षर fw_ver_str[ETHTOOL_FWVERS_LEN];
	अचिन्हित पूर्णांक fw_ver[NUM_FW_VER];
	अक्षर phy_fw_ver_str[ETHTOOL_FWVERS_LEN];
पूर्ण;

#घोषणा NUM_TX_QUEUES              4

काष्ठा wl_fw_status अणु
	u32 पूर्णांकr;
	u8  fw_rx_counter;
	u8  drv_rx_counter;
	u8  tx_results_counter;
	__le32 *rx_pkt_descs;

	u32 fw_स_स्थानीय;

	/*
	 * A biपंचांगap (where each bit represents a single HLID)
	 * to indicate अगर the station is in PS mode.
	 */
	u32 link_ps_biपंचांगap;

	/*
	 * A biपंचांगap (where each bit represents a single HLID) to indicate
	 * अगर the station is in Fast mode
	 */
	u32 link_fast_biपंचांगap;

	/* Cumulative counter of total released mem blocks since FW-reset */
	u32 total_released_blks;

	/* Size (in Memory Blocks) of TX pool */
	u32 tx_total;

	काष्ठा अणु
		/*
		 * Cumulative counter of released packets per AC
		 * (length of the array is NUM_TX_QUEUES)
		 */
		u8 *tx_released_pkts;

		/*
		 * Cumulative counter of मुक्तd packets per HLID
		 * (length of the array is wl->num_links)
		 */
		u8 *tx_lnk_मुक्त_pkts;

		/* Cumulative counter of released Voice memory blocks */
		u8 tx_voice_released_blks;

		/* Tx rate of the last transmitted packet */
		u8 tx_last_rate;

		/* Tx rate or Tx rate estimate pre calculated by fw in mbps */
		u8 tx_last_rate_mbps;

		/* hlid क्रम which the rates were reported */
		u8 hlid;
	पूर्ण counters;

	u32 log_start_addr;

	/* Private status to be used by the lower drivers */
	व्योम *priv;
पूर्ण;

#घोषणा WL1271_MAX_CHANNELS 64
काष्ठा wl1271_scan अणु
	काष्ठा cfg80211_scan_request *req;
	अचिन्हित दीर्घ scanned_ch[BITS_TO_LONGS(WL1271_MAX_CHANNELS)];
	bool failed;
	u8 state;
	u8 ssid[IEEE80211_MAX_SSID_LEN+1];
	माप_प्रकार ssid_len;
पूर्ण;

काष्ठा wl1271_अगर_operations अणु
	पूर्णांक __must_check (*पढ़ो)(काष्ठा device *child, पूर्णांक addr, व्योम *buf,
				 माप_प्रकार len, bool fixed);
	पूर्णांक __must_check (*ग_लिखो)(काष्ठा device *child, पूर्णांक addr, व्योम *buf,
				  माप_प्रकार len, bool fixed);
	व्योम (*reset)(काष्ठा device *child);
	व्योम (*init)(काष्ठा device *child);
	पूर्णांक (*घातer)(काष्ठा device *child, bool enable);
	व्योम (*set_block_size) (काष्ठा device *child, अचिन्हित पूर्णांक blksz);
पूर्ण;

काष्ठा wlcore_platdev_data अणु
	काष्ठा wl1271_अगर_operations *अगर_ops;
	स्थिर काष्ठा wilink_family_data *family;

	bool ref_घड़ी_xtal;	/* specअगरy whether the घड़ी is XTAL or not */
	u32 ref_घड़ी_freq;	/* in Hertz */
	u32 tcxo_घड़ी_freq;	/* in Hertz, tcxo is always XTAL */
	bool pwr_in_suspend;
पूर्ण;

#घोषणा MAX_NUM_KEYS 14
#घोषणा MAX_KEY_SIZE 32

काष्ठा wl1271_ap_key अणु
	u8 id;
	u8 key_type;
	u8 key_size;
	u8 key[MAX_KEY_SIZE];
	u8 hlid;
	u32 tx_seq_32;
	u16 tx_seq_16;
	bool is_pairwise;
पूर्ण;

क्रमागत wl12xx_flags अणु
	WL1271_FLAG_GPIO_POWER,
	WL1271_FLAG_TX_QUEUE_STOPPED,
	WL1271_FLAG_TX_PENDING,
	WL1271_FLAG_IN_ELP,
	WL1271_FLAG_IRQ_RUNNING,
	WL1271_FLAG_FW_TX_BUSY,
	WL1271_FLAG_DUMMY_PACKET_PENDING,
	WL1271_FLAG_SUSPENDED,
	WL1271_FLAG_PENDING_WORK,
	WL1271_FLAG_SOFT_GEMINI,
	WL1271_FLAG_RECOVERY_IN_PROGRESS,
	WL1271_FLAG_VIF_CHANGE_IN_PROGRESS,
	WL1271_FLAG_INTENDED_FW_RECOVERY,
	WL1271_FLAG_IO_FAILED,
	WL1271_FLAG_REINIT_TX_WDOG,
पूर्ण;

क्रमागत wl12xx_vअगर_flags अणु
	WLVIF_FLAG_INITIALIZED,
	WLVIF_FLAG_STA_ASSOCIATED,
	WLVIF_FLAG_STA_AUTHORIZED,
	WLVIF_FLAG_IBSS_JOINED,
	WLVIF_FLAG_AP_STARTED,
	WLVIF_FLAG_IN_PS,
	WLVIF_FLAG_STA_STATE_SENT,
	WLVIF_FLAG_RX_STREAMING_STARTED,
	WLVIF_FLAG_PSPOLL_FAILURE,
	WLVIF_FLAG_CS_PROGRESS,
	WLVIF_FLAG_AP_PROBE_RESP_SET,
	WLVIF_FLAG_IN_USE,
	WLVIF_FLAG_ACTIVE,
	WLVIF_FLAG_BEACON_DISABLED,
पूर्ण;

काष्ठा wl12xx_vअगर;

काष्ठा wl1271_link अणु
	/* AP-mode - TX queue per AC in link */
	काष्ठा sk_buff_head tx_queue[NUM_TX_QUEUES];

	/* accounting क्रम allocated / मुक्तd packets in FW */
	u8 allocated_pkts;
	u8 prev_मुक्तd_pkts;

	u8 addr[ETH_ALEN];

	/* biपंचांगap of TIDs where RX BA sessions are active क्रम this link */
	u8 ba_biपंचांगap;

	/* the last fw rate index we used क्रम this link */
	u8 fw_rate_idx;

	/* the last fw rate [Mbps] we used क्रम this link */
	u8 fw_rate_mbps;

	/* The wlvअगर this link beदीर्घs to. Might be null क्रम global links */
	काष्ठा wl12xx_vअगर *wlvअगर;

	/*
	 * total मुक्तd FW packets on the link - used क्रम tracking the
	 * AES/TKIP PN across recoveries. Re-initialized each समय
	 * from the wl1271_station काष्ठाure.
	 */
	u64 total_मुक्तd_pkts;
पूर्ण;

#घोषणा WL1271_MAX_RX_FILTERS 5
#घोषणा WL1271_RX_FILTER_MAX_FIELDS 8

#घोषणा WL1271_RX_FILTER_ETH_HEADER_SIZE 14
#घोषणा WL1271_RX_FILTER_MAX_FIELDS_SIZE 95
#घोषणा RX_FILTER_FIELD_OVERHEAD				\
	(माप(काष्ठा wl12xx_rx_filter_field) - माप(u8 *))
#घोषणा WL1271_RX_FILTER_MAX_PATTERN_SIZE			\
	(WL1271_RX_FILTER_MAX_FIELDS_SIZE - RX_FILTER_FIELD_OVERHEAD)

#घोषणा WL1271_RX_FILTER_FLAG_MASK                BIT(0)
#घोषणा WL1271_RX_FILTER_FLAG_IP_HEADER           0
#घोषणा WL1271_RX_FILTER_FLAG_ETHERNET_HEADER     BIT(1)

क्रमागत rx_filter_action अणु
	FILTER_DROP = 0,
	FILTER_SIGNAL = 1,
	FILTER_FW_HANDLE = 2
पूर्ण;

क्रमागत plt_mode अणु
	PLT_OFF = 0,
	PLT_ON = 1,
	PLT_FEM_DETECT = 2,
	PLT_CHIP_AWAKE = 3
पूर्ण;

काष्ठा wl12xx_rx_filter_field अणु
	__le16 offset;
	u8 len;
	u8 flags;
	u8 *pattern;
पूर्ण __packed;

काष्ठा wl12xx_rx_filter अणु
	u8 action;
	पूर्णांक num_fields;
	काष्ठा wl12xx_rx_filter_field fields[WL1271_RX_FILTER_MAX_FIELDS];
पूर्ण;

काष्ठा wl1271_station अणु
	u8 hlid;
	bool in_connection;

	/*
	 * total मुक्तd FW packets on the link to the STA - used क्रम tracking the
	 * AES/TKIP PN across recoveries. Re-initialized each समय from the
	 * wl1271_station काष्ठाure.
	 * Used in both AP and STA mode.
	 */
	u64 total_मुक्तd_pkts;
पूर्ण;

काष्ठा wl12xx_vअगर अणु
	काष्ठा wl1271 *wl;
	काष्ठा list_head list;
	अचिन्हित दीर्घ flags;
	u8 bss_type;
	u8 p2p; /* we are using p2p role */
	u8 role_id;

	/* sta/ibss specअगरic */
	u8 dev_role_id;
	u8 dev_hlid;

	जोड़ अणु
		काष्ठा अणु
			u8 hlid;

			u8 basic_rate_idx;
			u8 ap_rate_idx;
			u8 p2p_rate_idx;

			u8 klv_ढाँचा_id;

			bool qos;
			/* channel type we started the STA role with */
			क्रमागत nl80211_channel_type role_chan_type;
		पूर्ण sta;
		काष्ठा अणु
			u8 global_hlid;
			u8 bcast_hlid;

			/* HLIDs biपंचांगap of associated stations */
			अचिन्हित दीर्घ sta_hlid_map[BITS_TO_LONGS(
							WLCORE_MAX_LINKS)];

			/* recoreded keys - set here beक्रमe AP startup */
			काष्ठा wl1271_ap_key *recorded_keys[MAX_NUM_KEYS];

			u8 mgmt_rate_idx;
			u8 bcast_rate_idx;
			u8 ucast_rate_idx[CONF_TX_MAX_AC_COUNT];
		पूर्ण ap;
	पूर्ण;

	/* the hlid of the last transmitted skb */
	पूर्णांक last_tx_hlid;

	/* counters of packets per AC, across all links in the vअगर */
	पूर्णांक tx_queue_count[NUM_TX_QUEUES];

	अचिन्हित दीर्घ links_map[BITS_TO_LONGS(WLCORE_MAX_LINKS)];

	u8 ssid[IEEE80211_MAX_SSID_LEN + 1];
	u8 ssid_len;

	/* The current band */
	क्रमागत nl80211_band band;
	पूर्णांक channel;
	क्रमागत nl80211_channel_type channel_type;

	u32 bitrate_masks[WLCORE_NUM_BANDS];
	u32 basic_rate_set;

	/*
	 * currently configured rate set:
	 *	bits  0-15 - 802.11abg rates
	 *	bits 16-23 - 802.11n   MCS index mask
	 * support only 1 stream, thus only 8 bits क्रम the MCS rates (0-7).
	 */
	u32 basic_rate;
	u32 rate_set;

	/* probe-req ढाँचा क्रम the current AP */
	काष्ठा sk_buff *probereq;

	/* Beaconing पूर्णांकerval (needed क्रम ad-hoc) */
	u32 beacon_पूर्णांक;

	/* Default key (क्रम WEP) */
	u32 शेष_key;

	/* Our association ID */
	u16 aid;

	/* retry counter क्रम PSM entries */
	u8 psm_entry_retry;

	/* in dBm */
	पूर्णांक घातer_level;

	पूर्णांक rssi_thold;
	पूर्णांक last_rssi_event;

	/* save the current encryption type क्रम स्वतः-arp config */
	u8 encryption_type;
	__be32 ip_addr;

	/* RX BA स्थिरraपूर्णांक value */
	bool ba_support;
	bool ba_allowed;

	bool wmm_enabled;

	bool radar_enabled;

	/* Rx Streaming */
	काष्ठा work_काष्ठा rx_streaming_enable_work;
	काष्ठा work_काष्ठा rx_streaming_disable_work;
	काष्ठा समयr_list rx_streaming_समयr;

	काष्ठा delayed_work channel_चयन_work;
	काष्ठा delayed_work connection_loss_work;

	/* number of in connection stations */
	पूर्णांक inconn_count;

	/*
	 * This vअगर's queues are mapped to mac80211 HW queues as:
	 * VO - hw_queue_base
	 * VI - hw_queue_base + 1
	 * BE - hw_queue_base + 2
	 * BK - hw_queue_base + 3
	 */
	पूर्णांक hw_queue_base;

	/* करो we have a pending auth reply? (and ROC) */
	bool ap_pending_auth_reply;

	/* समय when we sent the pending auth reply */
	अचिन्हित दीर्घ pending_auth_reply_समय;

	/* work क्रम canceling ROC after pending auth reply */
	काष्ठा delayed_work pending_auth_complete_work;

	/* update rate conrol */
	क्रमागत ieee80211_sta_rx_bandwidth rc_update_bw;
	काष्ठा ieee80211_sta_ht_cap rc_ht_cap;
	काष्ठा work_काष्ठा rc_update_work;

	/*
	 * total मुक्तd FW packets on the link.
	 * For STA this holds the PN of the link to the AP.
	 * For AP this holds the PN of the broadcast link.
	 */
	u64 total_मुक्तd_pkts;

	/*
	 * This काष्ठा must be last!
	 * data that has to be saved acrossed reconfigs (e.g. recovery)
	 * should be declared in this काष्ठा.
	 */
	काष्ठा अणु
		u8 persistent[0];
	पूर्ण;
पूर्ण;

अटल अंतरभूत काष्ठा wl12xx_vअगर *wl12xx_vअगर_to_data(काष्ठा ieee80211_vअगर *vअगर)
अणु
	WARN_ON(!vअगर);
	वापस (काष्ठा wl12xx_vअगर *)vअगर->drv_priv;
पूर्ण

अटल अंतरभूत
काष्ठा ieee80211_vअगर *wl12xx_wlvअगर_to_vअगर(काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	वापस container_of((व्योम *)wlvअगर, काष्ठा ieee80211_vअगर, drv_priv);
पूर्ण

अटल अंतरभूत bool wlcore_is_p2p_mgmt(काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	वापस wl12xx_wlvअगर_to_vअगर(wlvअगर)->type == NL80211_IFTYPE_P2P_DEVICE;
पूर्ण

#घोषणा wl12xx_क्रम_each_wlvअगर(wl, wlvअगर) \
		list_क्रम_each_entry(wlvअगर, &wl->wlvअगर_list, list)

#घोषणा wl12xx_क्रम_each_wlvअगर_जारी(wl, wlvअगर) \
		list_क्रम_each_entry_जारी(wlvअगर, &wl->wlvअगर_list, list)

#घोषणा wl12xx_क्रम_each_wlvअगर_bss_type(wl, wlvअगर, _bss_type)	\
		wl12xx_क्रम_each_wlvअगर(wl, wlvअगर)		\
			अगर (wlvअगर->bss_type == _bss_type)

#घोषणा wl12xx_क्रम_each_wlvअगर_sta(wl, wlvअगर)	\
		wl12xx_क्रम_each_wlvअगर_bss_type(wl, wlvअगर, BSS_TYPE_STA_BSS)

#घोषणा wl12xx_क्रम_each_wlvअगर_ap(wl, wlvअगर)	\
		wl12xx_क्रम_each_wlvअगर_bss_type(wl, wlvअगर, BSS_TYPE_AP_BSS)

पूर्णांक wl1271_plt_start(काष्ठा wl1271 *wl, स्थिर क्रमागत plt_mode plt_mode);
पूर्णांक wl1271_plt_stop(काष्ठा wl1271 *wl);
पूर्णांक wl1271_recalc_rx_streaming(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
व्योम wl12xx_queue_recovery_work(काष्ठा wl1271 *wl);
माप_प्रकार wl12xx_copy_fwlog(काष्ठा wl1271 *wl, u8 *memblock, माप_प्रकार maxlen);
पूर्णांक wl1271_rx_filter_alloc_field(काष्ठा wl12xx_rx_filter *filter,
				 u16 offset, u8 flags,
				 स्थिर u8 *pattern, u8 len);
व्योम wl1271_rx_filter_मुक्त(काष्ठा wl12xx_rx_filter *filter);
काष्ठा wl12xx_rx_filter *wl1271_rx_filter_alloc(व्योम);
पूर्णांक wl1271_rx_filter_get_fields_size(काष्ठा wl12xx_rx_filter *filter);
व्योम wl1271_rx_filter_flatten_fields(काष्ठा wl12xx_rx_filter *filter,
				     u8 *buf);

#घोषणा JOIN_TIMEOUT 5000 /* 5000 milliseconds to join */

#घोषणा SESSION_COUNTER_MAX 6 /* maximum value क्रम the session counter */
#घोषणा SESSION_COUNTER_INVALID 7 /* used with dummy_packet */

#घोषणा WL1271_DEFAULT_POWER_LEVEL 0

#घोषणा WL1271_TX_QUEUE_LOW_WATERMARK  32
#घोषणा WL1271_TX_QUEUE_HIGH_WATERMARK 256

#घोषणा WL1271_DEFERRED_QUEUE_LIMIT    64

/* WL1271 needs a 200ms sleep after घातer on, and a 20ms sleep beक्रमe घातer
   on in हाल is has been shut करोwn लघुly beक्रमe */
#घोषणा WL1271_PRE_POWER_ON_SLEEP 20 /* in milliseconds */
#घोषणा WL1271_POWER_ON_SLEEP 200 /* in milliseconds */

/* Macros to handle wl1271.sta_rate_set */
#घोषणा HW_BG_RATES_MASK	0xffff
#घोषणा HW_HT_RATES_OFFSET	16
#घोषणा HW_MIMO_RATES_OFFSET	24

#पूर्ण_अगर /* __WLCORE_I_H__ */
