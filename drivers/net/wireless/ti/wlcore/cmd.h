<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl1271
 *
 * Copyright (C) 1998-2009 Texas Instruments. All rights reserved.
 * Copyright (C) 2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#अगर_अघोषित __CMD_H__
#घोषणा __CMD_H__

#समावेश "wlcore.h"

काष्ठा acx_header;

पूर्णांक wl1271_cmd_send(काष्ठा wl1271 *wl, u16 id, व्योम *buf, माप_प्रकार len,
		    माप_प्रकार res_len);
पूर्णांक wl12xx_cmd_role_enable(काष्ठा wl1271 *wl, u8 *addr, u8 role_type,
			   u8 *role_id);
पूर्णांक wl12xx_cmd_role_disable(काष्ठा wl1271 *wl, u8 *role_id);
पूर्णांक wl12xx_cmd_role_start_sta(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
पूर्णांक wl12xx_cmd_role_stop_sta(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
पूर्णांक wl12xx_cmd_role_start_ap(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
पूर्णांक wl12xx_cmd_role_stop_ap(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
पूर्णांक wl12xx_cmd_role_start_ibss(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
पूर्णांक wl12xx_start_dev(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
		     क्रमागत nl80211_band band, पूर्णांक channel);
पूर्णांक wl12xx_stop_dev(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
पूर्णांक wl1271_cmd_test(काष्ठा wl1271 *wl, व्योम *buf, माप_प्रकार buf_len, u8 answer);
पूर्णांक wl1271_cmd_पूर्णांकerrogate(काष्ठा wl1271 *wl, u16 id, व्योम *buf,
			   माप_प्रकार cmd_len, माप_प्रकार res_len);
पूर्णांक wl1271_cmd_configure(काष्ठा wl1271 *wl, u16 id, व्योम *buf, माप_प्रकार len);
पूर्णांक wlcore_cmd_configure_failsafe(काष्ठा wl1271 *wl, u16 id, व्योम *buf,
				  माप_प्रकार len, अचिन्हित दीर्घ valid_rets);
पूर्णांक wl1271_cmd_data_path(काष्ठा wl1271 *wl, bool enable);
पूर्णांक wl1271_cmd_ps_mode(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
		       u8 ps_mode, u16 स्वतः_ps_समयout);
पूर्णांक wl1271_cmd_पढ़ो_memory(काष्ठा wl1271 *wl, u32 addr, व्योम *answer,
			   माप_प्रकार len);
पूर्णांक wl1271_cmd_ढाँचा_set(काष्ठा wl1271 *wl, u8 role_id,
			    u16 ढाँचा_id, व्योम *buf, माप_प्रकार buf_len,
			    पूर्णांक index, u32 rates);
पूर्णांक wl12xx_cmd_build_null_data(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
पूर्णांक wl1271_cmd_build_ps_poll(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			     u16 aid);
पूर्णांक wl12xx_cmd_build_probe_req(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			       u8 role_id, u8 band,
			       स्थिर u8 *ssid, माप_प्रकार ssid_len,
			       स्थिर u8 *ie, माप_प्रकार ie_len, स्थिर u8 *common_ie,
			       माप_प्रकार common_ie_len, bool sched_scan);
काष्ठा sk_buff *wl1271_cmd_build_ap_probe_req(काष्ठा wl1271 *wl,
					      काष्ठा wl12xx_vअगर *wlvअगर,
					      काष्ठा sk_buff *skb);
पूर्णांक wl1271_cmd_build_arp_rsp(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
पूर्णांक wl1271_build_qos_null_data(काष्ठा wl1271 *wl, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक wl12xx_cmd_build_klv_null_data(काष्ठा wl1271 *wl,
				   काष्ठा wl12xx_vअगर *wlvअगर);
पूर्णांक wl12xx_cmd_set_शेष_wep_key(काष्ठा wl1271 *wl, u8 id, u8 hlid);
पूर्णांक wl1271_cmd_set_sta_key(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			   u16 action, u8 id, u8 key_type,
			   u8 key_size, स्थिर u8 *key, स्थिर u8 *addr,
			   u32 tx_seq_32, u16 tx_seq_16);
पूर्णांक wl1271_cmd_set_ap_key(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			  u16 action, u8 id, u8 key_type,
			  u8 key_size, स्थिर u8 *key, u8 hlid, u32 tx_seq_32,
			  u16 tx_seq_16, bool is_pairwise);
पूर्णांक wl12xx_cmd_set_peer_state(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			      u8 hlid);
पूर्णांक wl12xx_roc(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर, u8 role_id,
	       क्रमागत nl80211_band band, u8 channel);
पूर्णांक wl12xx_croc(काष्ठा wl1271 *wl, u8 role_id);
पूर्णांक wl12xx_cmd_add_peer(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			काष्ठा ieee80211_sta *sta, u8 hlid);
पूर्णांक wl12xx_cmd_हटाओ_peer(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			   u8 hlid);
व्योम wlcore_set_pending_regकरोमुख्य_ch(काष्ठा wl1271 *wl, u16 channel,
				     क्रमागत nl80211_band band);
पूर्णांक wlcore_cmd_regकरोमुख्य_config_locked(काष्ठा wl1271 *wl);
पूर्णांक wlcore_cmd_generic_cfg(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			   u8 feature, u8 enable, u8 value);
पूर्णांक wl12xx_cmd_config_fwlog(काष्ठा wl1271 *wl);
पूर्णांक wl12xx_cmd_start_fwlog(काष्ठा wl1271 *wl);
पूर्णांक wl12xx_cmd_stop_fwlog(काष्ठा wl1271 *wl);
पूर्णांक wl12xx_cmd_channel_चयन(काष्ठा wl1271 *wl,
			      काष्ठा wl12xx_vअगर *wlvअगर,
			      काष्ठा ieee80211_channel_चयन *ch_चयन);
पूर्णांक wl12xx_cmd_stop_channel_चयन(काष्ठा wl1271 *wl,
				   काष्ठा wl12xx_vअगर *wlvअगर);
पूर्णांक wl12xx_allocate_link(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			 u8 *hlid);
व्योम wl12xx_मुक्त_link(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर, u8 *hlid);
पूर्णांक wlcore_cmd_रुको_क्रम_event_or_समयout(काष्ठा wl1271 *wl,
					 u32 mask, bool *समयout);
u8 wlcore_get_native_channel_type(u8 nl_channel_type);

क्रमागत wl1271_commands अणु
	CMD_INTERROGATE	= 1, /* use this to पढ़ो inक्रमmation elements */
	CMD_CONFIGURE	= 2, /* use this to ग_लिखो inक्रमmation elements */
	CMD_ENABLE_RX	= 3,
	CMD_ENABLE_TX	= 4,
	CMD_DISABLE_RX	= 5,
	CMD_DISABLE_TX	= 6,
	CMD_SCAN	= 7,
	CMD_STOP_SCAN	= 8,
	CMD_SET_KEYS	= 9,
	CMD_READ_MEMORY	= 10,
	CMD_WRITE_MEMORY	= 11,
	CMD_SET_TEMPLATE	= 12,
	CMD_TEST		= 13,
	CMD_NOISE_HIST		= 14,
	CMD_QUIET_ELEMENT_SET_STATE = 15,
	CMD_SET_BCN_MODE	= 16,

	CMD_MEASUREMENT		= 17,
	CMD_STOP_MEASUREMENT	= 18,
	CMD_SET_PS_MODE		= 19,
	CMD_CHANNEL_SWITCH	= 20,
	CMD_STOP_CHANNEL_SWICTH = 21,
	CMD_AP_DISCOVERY	= 22,
	CMD_STOP_AP_DISCOVERY	= 23,
	CMD_HEALTH_CHECK	= 24,
	CMD_DEBUG		= 25,
	CMD_TRIGGER_SCAN_TO	= 26,
	CMD_CONNECTION_SCAN_CFG	= 27,
	CMD_CONNECTION_SCAN_SSID_CFG	= 28,
	CMD_START_PERIODIC_SCAN	= 29,
	CMD_STOP_PERIODIC_SCAN	= 30,
	CMD_SET_PEER_STATE	= 31,
	CMD_REMAIN_ON_CHANNEL	= 32,
	CMD_CANCEL_REMAIN_ON_CHANNEL	= 33,
	CMD_CONFIG_FWLOGGER		= 34,
	CMD_START_FWLOGGER			= 35,
	CMD_STOP_FWLOGGER			= 36,

	/* Access poपूर्णांक commands */
	CMD_ADD_PEER		= 37,
	CMD_REMOVE_PEER		= 38,

	/* Role API */
	CMD_ROLE_ENABLE		= 39,
	CMD_ROLE_DISABLE	= 40,
	CMD_ROLE_START		= 41,
	CMD_ROLE_STOP		= 42,

	/* DFS */
	CMD_START_RADAR_DETECTION	= 43,
	CMD_STOP_RADAR_DETECTION	= 44,

	/* WIFI Direct */
	CMD_WFD_START_DISCOVERY	= 45,
	CMD_WFD_STOP_DISCOVERY	= 46,
	CMD_WFD_ATTRIBUTE_CONFIG	= 47,
	CMD_GENERIC_CFG			= 48,
	CMD_NOP				= 49,

	/* start of 18xx specअगरic commands */
	CMD_DFS_CHANNEL_CONFIG		= 60,
	CMD_SMART_CONFIG_START		= 61,
	CMD_SMART_CONFIG_STOP		= 62,
	CMD_SMART_CONFIG_SET_GROUP_KEY	= 63,

	CMD_CAC_START			= 64,
	CMD_CAC_STOP			= 65,
	CMD_DFS_MASTER_RESTART		= 66,
	CMD_DFS_RADAR_DETECTION_DEBUG	= 67,

	MAX_COMMAND_ID = 0xFFFF,
पूर्ण;

#घोषणा MAX_CMD_PARAMS 572

क्रमागत cmd_templ अणु
	CMD_TEMPL_शून्य_DATA = 0,
	CMD_TEMPL_BEACON,
	CMD_TEMPL_CFG_PROBE_REQ_2_4,
	CMD_TEMPL_CFG_PROBE_REQ_5,
	CMD_TEMPL_PROBE_RESPONSE,
	CMD_TEMPL_QOS_शून्य_DATA,
	CMD_TEMPL_PS_POLL,
	CMD_TEMPL_KLV,
	CMD_TEMPL_DISCONNECT,
	CMD_TEMPL_APP_PROBE_REQ_2_4_LEGACY,
	CMD_TEMPL_APP_PROBE_REQ_5_LEGACY,
	CMD_TEMPL_BAR,           /* क्रम firmware पूर्णांकernal use only */
	CMD_TEMPL_CTS,           /*
				  * For CTS-to-self (FastCTS) mechanism
				  * क्रम BT/WLAN coexistence (SoftGemini). */
	CMD_TEMPL_AP_BEACON,
	CMD_TEMPL_AP_PROBE_RESPONSE,
	CMD_TEMPL_ARP_RSP,
	CMD_TEMPL_DEAUTH_AP,
	CMD_TEMPL_TEMPORARY,
	CMD_TEMPL_LINK_MEASUREMENT_REPORT,
	CMD_TEMPL_PROBE_REQ_2_4_PERIODIC,
	CMD_TEMPL_PROBE_REQ_5_PERIODIC,

	CMD_TEMPL_MAX = 0xff
पूर्ण;

/* unit ms */
#घोषणा WL1271_COMMAND_TIMEOUT     2000
#घोषणा WL1271_CMD_TEMPL_DFLT_SIZE 252
#घोषणा WL1271_CMD_TEMPL_MAX_SIZE  512
#घोषणा WL1271_EVENT_TIMEOUT       5000

काष्ठा wl1271_cmd_header अणु
	__le16 id;
	__le16 status;
	/* payload */
	u8 data[];
पूर्ण __packed;

#घोषणा WL1271_CMD_MAX_PARAMS 572

काष्ठा wl1271_command अणु
	काष्ठा wl1271_cmd_header header;
	u8  parameters[WL1271_CMD_MAX_PARAMS];
पूर्ण __packed;

क्रमागत अणु
	CMD_MAILBOX_IDLE		=  0,
	CMD_STATUS_SUCCESS		=  1,
	CMD_STATUS_UNKNOWN_CMD		=  2,
	CMD_STATUS_UNKNOWN_IE		=  3,
	CMD_STATUS_REJECT_MEAS_SG_ACTIVE	= 11,
	CMD_STATUS_RX_BUSY		= 13,
	CMD_STATUS_INVALID_PARAM		= 14,
	CMD_STATUS_TEMPLATE_TOO_LARGE		= 15,
	CMD_STATUS_OUT_OF_MEMORY		= 16,
	CMD_STATUS_STA_TABLE_FULL		= 17,
	CMD_STATUS_RADIO_ERROR		= 18,
	CMD_STATUS_WRONG_NESTING		= 19,
	CMD_STATUS_TIMEOUT		= 21, /* Driver पूर्णांकernal use.*/
	CMD_STATUS_FW_RESET		= 22, /* Driver पूर्णांकernal use.*/
	CMD_STATUS_TEMPLATE_OOM		= 23,
	CMD_STATUS_NO_RX_BA_SESSION	= 24,

	MAX_COMMAND_STATUS
पूर्ण;

#घोषणा CMDMBOX_HEADER_LEN 4
#घोषणा CMDMBOX_INFO_ELEM_HEADER_LEN 4

क्रमागत अणु
	BSS_TYPE_IBSS = 0,
	BSS_TYPE_STA_BSS = 2,
	BSS_TYPE_AP_BSS = 3,
	MAX_BSS_TYPE = 0xFF
पूर्ण;

#घोषणा WL1271_JOIN_CMD_CTRL_TX_FLUSH     0x80 /* Firmware flushes all Tx */
#घोषणा WL1271_JOIN_CMD_TX_SESSION_OFFSET 1
#घोषणा WL1271_JOIN_CMD_BSS_TYPE_5GHZ 0x10

काष्ठा wl12xx_cmd_role_enable अणु
	काष्ठा wl1271_cmd_header header;

	u8 role_id;
	u8 role_type;
	u8 mac_address[ETH_ALEN];
पूर्ण __packed;

काष्ठा wl12xx_cmd_role_disable अणु
	काष्ठा wl1271_cmd_header header;

	u8 role_id;
	u8 padding[3];
पूर्ण __packed;

क्रमागत wlcore_band अणु
	WLCORE_BAND_2_4GHZ		= 0,
	WLCORE_BAND_5GHZ		= 1,
	WLCORE_BAND_JAPAN_4_9_GHZ	= 2,
	WLCORE_BAND_DEFAULT		= WLCORE_BAND_2_4GHZ,
	WLCORE_BAND_INVALID		= 0x7E,
	WLCORE_BAND_MAX_RADIO		= 0x7F,
पूर्ण;

क्रमागत wlcore_channel_type अणु
	WLCORE_CHAN_NO_HT,
	WLCORE_CHAN_HT20,
	WLCORE_CHAN_HT40MINUS,
	WLCORE_CHAN_HT40PLUS
पूर्ण;

काष्ठा wl12xx_cmd_role_start अणु
	काष्ठा wl1271_cmd_header header;

	u8 role_id;
	u8 band;
	u8 channel;

	/* क्रमागत wlcore_channel_type */
	u8 channel_type;

	जोड़ अणु
		काष्ठा अणु
			u8 hlid;
			u8 session;
			u8 padding_1[54];
		पूर्ण __packed device;
		/* sta & p2p_cli use the same काष्ठा */
		काष्ठा अणु
			u8 bssid[ETH_ALEN];
			u8 hlid; /* data hlid */
			u8 session;
			__le32 remote_rates; /* remote supported rates */

			/*
			 * The target uses this field to determine the rate at
			 * which to transmit control frame responses (such as
			 * ACK or CTS frames).
			 */
			__le32 basic_rate_set;
			__le32 local_rates; /* local supported rates */

			u8 ssid_type;
			u8 ssid_len;
			u8 ssid[IEEE80211_MAX_SSID_LEN];

			__le16 beacon_पूर्णांकerval; /* in TBTTs */
		पूर्ण __packed sta;
		काष्ठा अणु
			u8 bssid[ETH_ALEN];
			u8 hlid; /* data hlid */
			u8 dtim_पूर्णांकerval;
			__le32 remote_rates; /* remote supported rates */

			__le32 basic_rate_set;
			__le32 local_rates; /* local supported rates */

			u8 ssid_type;
			u8 ssid_len;
			u8 ssid[IEEE80211_MAX_SSID_LEN];

			__le16 beacon_पूर्णांकerval; /* in TBTTs */

			u8 padding_1[4];
		पूर्ण __packed ibss;
		/* ap & p2p_go use the same काष्ठा */
		काष्ठा अणु
			__le16 aging_period; /* in secs */
			u8 beacon_expiry; /* in ms */
			u8 bss_index;
			/* The host link id क्रम the AP's global queue */
			u8 global_hlid;
			/* The host link id क्रम the AP's broadcast queue */
			u8 broadcast_hlid;

			__le16 beacon_पूर्णांकerval; /* in TBTTs */

			__le32 basic_rate_set;
			__le32 local_rates; /* local supported rates */

			u8 dtim_पूर्णांकerval;

			u8 ssid_type;
			u8 ssid_len;
			u8 ssid[IEEE80211_MAX_SSID_LEN];

			u8 reset_tsf;

			/*
			 * ap supports wmm (note that there is additional
			 * per-sta wmm configuration)
			 */
			u8 wmm;

			u8 bcast_session_id;
			u8 global_session_id;
			u8 padding_1[1];
		पूर्ण __packed ap;
	पूर्ण;
पूर्ण __packed;

काष्ठा wl12xx_cmd_role_stop अणु
	काष्ठा wl1271_cmd_header header;

	u8 role_id;
	u8 disc_type; /* only STA and P2P_CLI */
	__le16 reason; /* only STA and P2P_CLI */
पूर्ण __packed;

काष्ठा cmd_enabledisable_path अणु
	काष्ठा wl1271_cmd_header header;

	u8 channel;
	u8 padding[3];
पूर्ण __packed;

#घोषणा WL1271_RATE_AUTOMATIC  0

काष्ठा wl1271_cmd_ढाँचा_set अणु
	काष्ठा wl1271_cmd_header header;

	u8 role_id;
	u8 ढाँचा_type;
	__le16 len;
	u8 index;  /* relevant only क्रम KLV_TEMPLATE type */
	u8 padding[3];

	__le32 enabled_rates;
	u8 लघु_retry_limit;
	u8 दीर्घ_retry_limit;
	u8 aflags;
	u8 reserved;

	u8 ढाँचा_data[WL1271_CMD_TEMPL_MAX_SIZE];
पूर्ण __packed;

#घोषणा TIM_ELE_ID    5
#घोषणा PARTIAL_VBM_MAX    251

काष्ठा wl1271_tim अणु
	u8 identity;
	u8 length;
	u8 dtim_count;
	u8 dtim_period;
	u8 biपंचांगap_ctrl;
	u8 pvb_field[PARTIAL_VBM_MAX]; /* Partial Virtual Biपंचांगap */
पूर्ण __packed;

क्रमागत wl1271_cmd_ps_mode अणु
	STATION_AUTO_PS_MODE,   /* Dynamic Power Save */
	STATION_ACTIVE_MODE,
	STATION_POWER_SAVE_MODE
पूर्ण;

काष्ठा wl1271_cmd_ps_params अणु
	काष्ठा wl1271_cmd_header header;

	u8 role_id;
	u8 ps_mode; /* STATION_* */
	u16 स्वतः_ps_समयout;
पूर्ण __packed;

/* HW encryption keys */
#घोषणा NUM_ACCESS_CATEGORIES_COPY 4

क्रमागत wl1271_cmd_key_action अणु
	KEY_ADD_OR_REPLACE = 1,
	KEY_REMOVE         = 2,
	KEY_SET_ID         = 3,
	MAX_KEY_ACTION     = 0xffff,
पूर्ण;

क्रमागत wl1271_cmd_lid_key_type अणु
	UNICAST_LID_TYPE     = 0,
	BROADCAST_LID_TYPE   = 1,
	WEP_DEFAULT_LID_TYPE = 2
पूर्ण;

क्रमागत wl1271_cmd_key_type अणु
	KEY_NONE = 0,
	KEY_WEP  = 1,
	KEY_TKIP = 2,
	KEY_AES  = 3,
	KEY_GEM  = 4,
पूर्ण;

काष्ठा wl1271_cmd_set_keys अणु
	काष्ठा wl1271_cmd_header header;

	/*
	 * Indicates whether the HLID is a unicast key set
	 * or broadcast key set. A special value 0xFF is
	 * used to indicate that the HLID is on WEP-शेष
	 * (multi-hlids). of type wl1271_cmd_lid_key_type.
	 */
	u8 hlid;

	/*
	 * In WEP-शेष network (hlid == 0xFF) used to
	 * indicate which network STA/IBSS/AP role should be
	 * changed
	 */
	u8 lid_key_type;

	/*
	 * Key ID - For TKIP and AES key types, this field
	 * indicates the value that should be inserted पूर्णांकo
	 * the KeyID field of frames transmitted using this
	 * key entry. For broadcast keys the index use as a
	 * marker क्रम TX/RX key.
	 * For WEP शेष network (HLID=0xFF), this field
	 * indicates the ID of the key to add or हटाओ.
	 */
	u8 key_id;
	u8 reserved_1;

	/* key_action_e */
	__le16 key_action;

	/* key size in bytes */
	u8 key_size;

	/* key_type_e */
	u8 key_type;

	/* This field holds the security key data to add to the STA table */
	u8 key[MAX_KEY_SIZE];
	__le16 ac_seq_num16[NUM_ACCESS_CATEGORIES_COPY];
	__le32 ac_seq_num32[NUM_ACCESS_CATEGORIES_COPY];
पूर्ण __packed;

काष्ठा wl1271_cmd_test_header अणु
	u8 id;
	u8 padding[3];
पूर्ण __packed;

क्रमागत wl1271_channel_tune_bands अणु
	WL1271_CHANNEL_TUNE_BAND_2_4,
	WL1271_CHANNEL_TUNE_BAND_5,
	WL1271_CHANNEL_TUNE_BAND_4_9
पूर्ण;

#घोषणा WL1271_PD_REFERENCE_POINT_BAND_B_G  0

/*
 * There are three types of disconnections:
 *
 * DISCONNECT_IMMEDIATE: the fw करोesn't send any frames
 * DISCONNECT_DEAUTH:    the fw generates a DEAUTH request with the reason
 *                       we have passed
 * DISCONNECT_DISASSOC:  the fw generates a DESASSOC request with the reason
 *                       we have passed
 */
क्रमागत wl1271_disconnect_type अणु
	DISCONNECT_IMMEDIATE,
	DISCONNECT_DEAUTH,
	DISCONNECT_DISASSOC
पूर्ण;

#घोषणा WL1271_CMD_STA_STATE_CONNECTED  1

काष्ठा wl12xx_cmd_set_peer_state अणु
	काष्ठा wl1271_cmd_header header;

	u8 hlid;
	u8 state;

	/*
	 * wmm is relevant क्रम sta role only.
	 * ap role configures the per-sta wmm params in
	 * the add_peer command.
	 */
	u8 wmm;
	u8 padding[1];
पूर्ण __packed;

काष्ठा wl12xx_cmd_roc अणु
	काष्ठा wl1271_cmd_header header;

	u8 role_id;
	u8 channel;
	u8 band;
	u8 padding;
पूर्ण;

काष्ठा wl12xx_cmd_croc अणु
	काष्ठा wl1271_cmd_header header;

	u8 role_id;
	u8 padding[3];
पूर्ण;

क्रमागत wl12xx_ssid_type अणु
	WL12XX_SSID_TYPE_PUBLIC = 0,
	WL12XX_SSID_TYPE_HIDDEN = 1,
	WL12XX_SSID_TYPE_ANY = 2,
पूर्ण;

क्रमागत wl1271_psd_type अणु
	WL1271_PSD_LEGACY = 0,
	WL1271_PSD_UPSD_TRIGGER = 1,
	WL1271_PSD_LEGACY_PSPOLL = 2,
	WL1271_PSD_SAPSD = 3
पूर्ण;

काष्ठा wl12xx_cmd_add_peer अणु
	काष्ठा wl1271_cmd_header header;

	u8 addr[ETH_ALEN];
	u8 hlid;
	u8 aid;
	u8 psd_type[NUM_ACCESS_CATEGORIES_COPY];
	__le32 supported_rates;
	u8 bss_index;
	u8 sp_len;
	u8 wmm;
	u8 session_id;
	u8 role_id;
	u8 padding[3];
पूर्ण __packed;

काष्ठा wl12xx_cmd_हटाओ_peer अणु
	काष्ठा wl1271_cmd_header header;

	u8 hlid;
	u8 reason_opcode;
	u8 send_deauth_flag;
	u8 role_id;
पूर्ण __packed;

/*
 * Continuous mode - packets are transferred to the host periodically
 * via the data path.
 * On demand - Log messages are stored in a cyclic buffer in the
 * firmware, and only transferred to the host when explicitly requested
 */
क्रमागत wl12xx_fwlogger_log_mode अणु
	WL12XX_FWLOG_CONTINUOUS,
पूर्ण;

/* Include/exclude बारtamps from the log messages */
क्रमागत wl12xx_fwlogger_बारtamp अणु
	WL12XX_FWLOG_TIMESTAMP_DISABLED,
	WL12XX_FWLOG_TIMESTAMP_ENABLED
पूर्ण;

/*
 * Logs can be routed to the debug pinouts (where available), to the host bus
 * (SDIO/SPI), or dropped
 */
क्रमागत wl12xx_fwlogger_output अणु
	WL12XX_FWLOG_OUTPUT_NONE,
	WL12XX_FWLOG_OUTPUT_DBG_PINS,
	WL12XX_FWLOG_OUTPUT_HOST,
पूर्ण;

काष्ठा wl12xx_cmd_regकरोमुख्य_dfs_config अणु
	काष्ठा wl1271_cmd_header header;

	__le32 ch_bit_map1;
	__le32 ch_bit_map2;
	u8 dfs_region;
	u8 padding[3];
पूर्ण __packed;

क्रमागत wlcore_generic_cfg_feature अणु
	WLCORE_CFG_FEATURE_RADAR_DEBUG = 2,
पूर्ण;

काष्ठा wlcore_cmd_generic_cfg अणु
	काष्ठा wl1271_cmd_header header;

	u8 role_id;
	u8 feature;
	u8 enable;
	u8 value;
पूर्ण __packed;

काष्ठा wl12xx_cmd_config_fwlog अणु
	काष्ठा wl1271_cmd_header header;

	/* See क्रमागत wl12xx_fwlogger_log_mode */
	u8 logger_mode;

	/* Minimum log level threshold */
	u8 log_severity;

	/* Include/exclude बारtamps from the log messages */
	u8 बारtamp;

	/* See क्रमागत wl1271_fwlogger_output */
	u8 output;

	/* Regulates the frequency of log messages */
	u8 threshold;

	u8 padding[3];
पूर्ण __packed;

काष्ठा wl12xx_cmd_start_fwlog अणु
	काष्ठा wl1271_cmd_header header;
पूर्ण __packed;

काष्ठा wl12xx_cmd_stop_fwlog अणु
	काष्ठा wl1271_cmd_header header;
पूर्ण __packed;

काष्ठा wl12xx_cmd_stop_channel_चयन अणु
	काष्ठा wl1271_cmd_header header;

	u8 role_id;
	u8 padding[3];
पूर्ण __packed;

/* Used to check radio status after calibration */
#घोषणा MAX_TLV_LENGTH		500
#घोषणा TEST_CMD_P2G_CAL	2	/* TX BiP */

काष्ठा wl1271_cmd_cal_p2g अणु
	काष्ठा wl1271_cmd_header header;

	काष्ठा wl1271_cmd_test_header test;

	__le32 ver;
	__le16 len;
	u8 buf[MAX_TLV_LENGTH];
	u8 type;
	u8 padding;

	__le16 radio_status;

	u8 sub_band_mask;
	u8 padding2;
पूर्ण __packed;

#पूर्ण_अगर /* __WL1271_CMD_H__ */
