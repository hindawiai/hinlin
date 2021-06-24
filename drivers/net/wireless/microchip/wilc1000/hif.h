<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2012 - 2018 Microchip Technology Inc., and its subsidiaries
 * All rights reserved.
 */

#अगर_अघोषित WILC_HIF_H
#घोषणा WILC_HIF_H
#समावेश <linux/ieee80211.h>
#समावेश "wlan_if.h"

क्रमागत अणु
	WILC_IDLE_MODE = 0x0,
	WILC_AP_MODE = 0x1,
	WILC_STATION_MODE = 0x2,
	WILC_GO_MODE = 0x3,
	WILC_CLIENT_MODE = 0x4
पूर्ण;

#घोषणा WILC_MAX_NUM_PROBED_SSID		10

#घोषणा WILC_TX_MIC_KEY_LEN			8
#घोषणा WILC_RX_MIC_KEY_LEN			8

#घोषणा WILC_ADD_STA_LENGTH			40
#घोषणा WILC_NUM_CONCURRENT_IFC			2

क्रमागत अणु
	WILC_SET_CFG = 0,
	WILC_GET_CFG
पूर्ण;

#घोषणा WILC_MAX_ASSOC_RESP_FRAME_SIZE   256

काष्ठा rf_info अणु
	u8 link_speed;
	s8 rssi;
	u32 tx_cnt;
	u32 rx_cnt;
	u32 tx_fail_cnt;
पूर्ण;

क्रमागत host_अगर_state अणु
	HOST_IF_IDLE			= 0,
	HOST_IF_SCANNING		= 1,
	HOST_IF_CONNECTING		= 2,
	HOST_IF_WAITING_CONN_RESP	= 3,
	HOST_IF_CONNECTED		= 4,
	HOST_IF_P2P_LISTEN		= 5,
	HOST_IF_FORCE_32BIT		= 0xFFFFFFFF
पूर्ण;

काष्ठा cfg_param_attr अणु
	u32 flag;
	u16 लघु_retry_limit;
	u16 दीर्घ_retry_limit;
	u16 frag_threshold;
	u16 rts_threshold;
पूर्ण;

क्रमागत cfg_param अणु
	WILC_CFG_PARAM_RETRY_SHORT = BIT(0),
	WILC_CFG_PARAM_RETRY_LONG = BIT(1),
	WILC_CFG_PARAM_FRAG_THRESHOLD = BIT(2),
	WILC_CFG_PARAM_RTS_THRESHOLD = BIT(3)
पूर्ण;

क्रमागत scan_event अणु
	SCAN_EVENT_NETWORK_FOUND	= 0,
	SCAN_EVENT_DONE			= 1,
	SCAN_EVENT_ABORTED		= 2,
	SCAN_EVENT_FORCE_32BIT		= 0xFFFFFFFF
पूर्ण;

क्रमागत conn_event अणु
	CONN_DISCONN_EVENT_CONN_RESP		= 0,
	CONN_DISCONN_EVENT_DISCONN_NOTIF	= 1,
	CONN_DISCONN_EVENT_FORCE_32BIT		= 0xFFFFFFFF
पूर्ण;

क्रमागत अणु
	WILC_HIF_SDIO = 0,
	WILC_HIF_SPI = BIT(0)
पूर्ण;

क्रमागत अणु
	WILC_MAC_STATUS_INIT = -1,
	WILC_MAC_STATUS_DISCONNECTED = 0,
	WILC_MAC_STATUS_CONNECTED = 1
पूर्ण;

काष्ठा wilc_rcvd_net_info अणु
	s8 rssi;
	u8 ch;
	u16 frame_len;
	काष्ठा ieee80211_mgmt *mgmt;
पूर्ण;

काष्ठा wilc_user_scan_req अणु
	व्योम (*scan_result)(क्रमागत scan_event evt,
			    काष्ठा wilc_rcvd_net_info *info, व्योम *priv);
	व्योम *arg;
	u32 ch_cnt;
पूर्ण;

काष्ठा wilc_conn_info अणु
	u8 bssid[ETH_ALEN];
	u8 security;
	क्रमागत authtype auth_type;
	u8 ch;
	u8 *req_ies;
	माप_प्रकार req_ies_len;
	u8 *resp_ies;
	u16 resp_ies_len;
	u16 status;
	व्योम (*conn_result)(क्रमागत conn_event evt, u8 status, व्योम *priv_data);
	व्योम *arg;
	व्योम *param;
पूर्ण;

काष्ठा wilc_reमुख्य_ch अणु
	u16 ch;
	u32 duration;
	व्योम (*expired)(व्योम *priv, u64 cookie);
	व्योम *arg;
	u32 cookie;
पूर्ण;

काष्ठा wilc;
काष्ठा host_अगर_drv अणु
	काष्ठा wilc_user_scan_req usr_scan_req;
	काष्ठा wilc_conn_info conn_info;
	काष्ठा wilc_reमुख्य_ch reमुख्य_on_ch;
	u64 p2p_समयout;

	क्रमागत host_अगर_state hअगर_state;

	u8 assoc_bssid[ETH_ALEN];

	काष्ठा समयr_list scan_समयr;
	काष्ठा wilc_vअगर *scan_समयr_vअगर;

	काष्ठा समयr_list connect_समयr;
	काष्ठा wilc_vअगर *connect_समयr_vअगर;

	काष्ठा समयr_list reमुख्य_on_ch_समयr;
	काष्ठा wilc_vअगर *reमुख्य_on_ch_समयr_vअगर;

	bool अगरc_up;
	u8 assoc_resp[WILC_MAX_ASSOC_RESP_FRAME_SIZE];
पूर्ण;

काष्ठा wilc_vअगर;
पूर्णांक wilc_हटाओ_wep_key(काष्ठा wilc_vअगर *vअगर, u8 index);
पूर्णांक wilc_set_wep_शेष_keyid(काष्ठा wilc_vअगर *vअगर, u8 index);
पूर्णांक wilc_add_wep_key_bss_sta(काष्ठा wilc_vअगर *vअगर, स्थिर u8 *key, u8 len,
			     u8 index);
पूर्णांक wilc_add_wep_key_bss_ap(काष्ठा wilc_vअगर *vअगर, स्थिर u8 *key, u8 len,
			    u8 index, u8 mode, क्रमागत authtype auth_type);
पूर्णांक wilc_add_ptk(काष्ठा wilc_vअगर *vअगर, स्थिर u8 *ptk, u8 ptk_key_len,
		 स्थिर u8 *mac_addr, स्थिर u8 *rx_mic, स्थिर u8 *tx_mic,
		 u8 mode, u8 cipher_mode, u8 index);
s32 wilc_get_inactive_समय(काष्ठा wilc_vअगर *vअगर, स्थिर u8 *mac,
			   u32 *out_val);
पूर्णांक wilc_add_rx_gtk(काष्ठा wilc_vअगर *vअगर, स्थिर u8 *rx_gtk, u8 gtk_key_len,
		    u8 index, u32 key_rsc_len, स्थिर u8 *key_rsc,
		    स्थिर u8 *rx_mic, स्थिर u8 *tx_mic, u8 mode,
		    u8 cipher_mode);
पूर्णांक wilc_set_pmkid_info(काष्ठा wilc_vअगर *vअगर, काष्ठा wilc_pmkid_attr *pmkid);
पूर्णांक wilc_get_mac_address(काष्ठा wilc_vअगर *vअगर, u8 *mac_addr);
पूर्णांक wilc_set_mac_address(काष्ठा wilc_vअगर *vअगर, u8 *mac_addr);
पूर्णांक wilc_set_join_req(काष्ठा wilc_vअगर *vअगर, u8 *bssid, स्थिर u8 *ies,
		      माप_प्रकार ies_len);
पूर्णांक wilc_disconnect(काष्ठा wilc_vअगर *vअगर);
पूर्णांक wilc_set_mac_chnl_num(काष्ठा wilc_vअगर *vअगर, u8 channel);
पूर्णांक wilc_get_rssi(काष्ठा wilc_vअगर *vअगर, s8 *rssi_level);
पूर्णांक wilc_scan(काष्ठा wilc_vअगर *vअगर, u8 scan_source, u8 scan_type,
	      u8 *ch_freq_list, u8 ch_list_len,
	      व्योम (*scan_result_fn)(क्रमागत scan_event,
				     काष्ठा wilc_rcvd_net_info *, व्योम *),
	      व्योम *user_arg, काष्ठा cfg80211_scan_request *request);
पूर्णांक wilc_hअगर_set_cfg(काष्ठा wilc_vअगर *vअगर,
		     काष्ठा cfg_param_attr *cfg_param);
पूर्णांक wilc_init(काष्ठा net_device *dev, काष्ठा host_अगर_drv **hअगर_drv_handler);
पूर्णांक wilc_deinit(काष्ठा wilc_vअगर *vअगर);
पूर्णांक wilc_add_beacon(काष्ठा wilc_vअगर *vअगर, u32 पूर्णांकerval, u32 dtim_period,
		    काष्ठा cfg80211_beacon_data *params);
पूर्णांक wilc_del_beacon(काष्ठा wilc_vअगर *vअगर);
पूर्णांक wilc_add_station(काष्ठा wilc_vअगर *vअगर, स्थिर u8 *mac,
		     काष्ठा station_parameters *params);
पूर्णांक wilc_del_allstation(काष्ठा wilc_vअगर *vअगर, u8 mac_addr[][ETH_ALEN]);
पूर्णांक wilc_del_station(काष्ठा wilc_vअगर *vअगर, स्थिर u8 *mac_addr);
पूर्णांक wilc_edit_station(काष्ठा wilc_vअगर *vअगर, स्थिर u8 *mac,
		      काष्ठा station_parameters *params);
पूर्णांक wilc_set_घातer_mgmt(काष्ठा wilc_vअगर *vअगर, bool enabled, u32 समयout);
पूर्णांक wilc_setup_multicast_filter(काष्ठा wilc_vअगर *vअगर, u32 enabled, u32 count,
				u8 *mc_list);
पूर्णांक wilc_reमुख्य_on_channel(काष्ठा wilc_vअगर *vअगर, u64 cookie,
			   u32 duration, u16 chan,
			   व्योम (*expired)(व्योम *, u64),
			   व्योम *user_arg);
पूर्णांक wilc_listen_state_expired(काष्ठा wilc_vअगर *vअगर, u64 cookie);
व्योम wilc_frame_रेजिस्टर(काष्ठा wilc_vअगर *vअगर, u16 frame_type, bool reg);
पूर्णांक wilc_set_operation_mode(काष्ठा wilc_vअगर *vअगर, पूर्णांक index, u8 mode,
			    u8 अगरc_id);
पूर्णांक wilc_get_statistics(काष्ठा wilc_vअगर *vअगर, काष्ठा rf_info *stats);
पूर्णांक wilc_get_vअगर_idx(काष्ठा wilc_vअगर *vअगर);
पूर्णांक wilc_set_tx_घातer(काष्ठा wilc_vअगर *vअगर, u8 tx_घातer);
पूर्णांक wilc_get_tx_घातer(काष्ठा wilc_vअगर *vअगर, u8 *tx_घातer);
व्योम wilc_scan_complete_received(काष्ठा wilc *wilc, u8 *buffer, u32 length);
व्योम wilc_network_info_received(काष्ठा wilc *wilc, u8 *buffer, u32 length);
व्योम wilc_gnrl_async_info_received(काष्ठा wilc *wilc, u8 *buffer, u32 length);
व्योम *wilc_parse_join_bss_param(काष्ठा cfg80211_bss *bss,
				काष्ठा cfg80211_crypto_settings *crypto);
#पूर्ण_अगर
