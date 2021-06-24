<शैली गुरु>
/*
 * NXP Wireless LAN device driver: ioctl data काष्ठाures & APIs
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#अगर_अघोषित _MWIFIEX_IOCTL_H_
#घोषणा _MWIFIEX_IOCTL_H_

#समावेश <net/lib80211.h>

क्रमागत अणु
	MWIFIEX_SCAN_TYPE_UNCHANGED = 0,
	MWIFIEX_SCAN_TYPE_ACTIVE,
	MWIFIEX_SCAN_TYPE_PASSIVE
पूर्ण;

काष्ठा mwअगरiex_user_scan अणु
	u32 scan_cfg_len;
	u8 scan_cfg_buf[1];
पूर्ण;

#घोषणा MWIFIEX_PROMISC_MODE            1
#घोषणा MWIFIEX_MULTICAST_MODE		2
#घोषणा	MWIFIEX_ALL_MULTI_MODE		4
#घोषणा MWIFIEX_MAX_MULTICAST_LIST_SIZE	32

काष्ठा mwअगरiex_multicast_list अणु
	u32 mode;
	u32 num_multicast_addr;
	u8 mac_list[MWIFIEX_MAX_MULTICAST_LIST_SIZE][ETH_ALEN];
पूर्ण;

काष्ठा mwअगरiex_chan_freq अणु
	u32 channel;
	u32 freq;
पूर्ण;

काष्ठा mwअगरiex_ssid_bssid अणु
	काष्ठा cfg80211_ssid ssid;
	u8 bssid[ETH_ALEN];
पूर्ण;

क्रमागत अणु
	BAND_B = 1,
	BAND_G = 2,
	BAND_A = 4,
	BAND_GN = 8,
	BAND_AN = 16,
	BAND_AAC = 32,
पूर्ण;

#घोषणा MWIFIEX_WPA_PASSHPHRASE_LEN 64
काष्ठा wpa_param अणु
	u8 pairwise_cipher_wpa;
	u8 pairwise_cipher_wpa2;
	u8 group_cipher;
	u32 length;
	u8 passphrase[MWIFIEX_WPA_PASSHPHRASE_LEN];
पूर्ण;

काष्ठा wep_key अणु
	u8 key_index;
	u8 is_शेष;
	u16 length;
	u8 key[WLAN_KEY_LEN_WEP104];
पूर्ण;

#घोषणा KEY_MGMT_ON_HOST        0x03
#घोषणा MWIFIEX_AUTH_MODE_AUTO  0xFF
#घोषणा BAND_CONFIG_BG          0x00
#घोषणा BAND_CONFIG_A           0x01
#घोषणा MWIFIEX_SEC_CHAN_BELOW	0x30
#घोषणा MWIFIEX_SEC_CHAN_ABOVE	0x10
#घोषणा MWIFIEX_SUPPORTED_RATES                 14
#घोषणा MWIFIEX_SUPPORTED_RATES_EXT             32
#घोषणा MWIFIEX_TDLS_SUPPORTED_RATES		8
#घोषणा MWIFIEX_TDLS_DEF_QOS_CAPAB		0xf
#घोषणा MWIFIEX_PRIO_BK				2
#घोषणा MWIFIEX_PRIO_VI				5
#घोषणा MWIFIEX_SUPPORTED_CHANNELS		2
#घोषणा MWIFIEX_OPERATING_CLASSES		16

काष्ठा mwअगरiex_uap_bss_param अणु
	u8 channel;
	u8 band_cfg;
	u16 rts_threshold;
	u16 frag_threshold;
	u8 retry_limit;
	काष्ठा mwअगरiex_802_11_ssid ssid;
	u8 bcast_ssid_ctl;
	u8 radio_ctl;
	u8 dtim_period;
	u16 beacon_period;
	u16 auth_mode;
	u16 protocol;
	u16 key_mgmt;
	u16 key_mgmt_operation;
	काष्ठा wpa_param wpa_cfg;
	काष्ठा wep_key wep_cfg[NUM_WEP_KEYS];
	काष्ठा ieee80211_ht_cap ht_cap;
	काष्ठा ieee80211_vht_cap vht_cap;
	u8 rates[MWIFIEX_SUPPORTED_RATES];
	u32 sta_ao_समयr;
	u32 ps_sta_ao_समयr;
	u8 qos_info;
	u8 घातer_स्थिरraपूर्णांक;
	काष्ठा mwअगरiex_types_wmm_info wmm_info;
पूर्ण;

क्रमागत अणु
	ADHOC_IDLE,
	ADHOC_STARTED,
	ADHOC_JOINED,
	ADHOC_COALESCED
पूर्ण;

काष्ठा mwअगरiex_ds_get_stats अणु
	u32 mcast_tx_frame;
	u32 failed;
	u32 retry;
	u32 multi_retry;
	u32 frame_dup;
	u32 rts_success;
	u32 rts_failure;
	u32 ack_failure;
	u32 rx_frag;
	u32 mcast_rx_frame;
	u32 fcs_error;
	u32 tx_frame;
	u32 wep_icv_error[4];
	u32 bcn_rcv_cnt;
	u32 bcn_miss_cnt;
पूर्ण;

#घोषणा MWIFIEX_MAX_VER_STR_LEN    128

काष्ठा mwअगरiex_ver_ext अणु
	u32 version_str_sel;
	अक्षर version_str[MWIFIEX_MAX_VER_STR_LEN];
पूर्ण;

काष्ठा mwअगरiex_bss_info अणु
	u32 bss_mode;
	काष्ठा cfg80211_ssid ssid;
	u32 bss_chan;
	u8 country_code[3];
	u32 media_connected;
	u32 max_घातer_level;
	u32 min_घातer_level;
	u32 adhoc_state;
	चिन्हित पूर्णांक bcn_nf_last;
	u32 wep_status;
	u32 is_hs_configured;
	u32 is_deep_sleep;
	u8 bssid[ETH_ALEN];
पूर्ण;

#घोषणा MAX_NUM_TID     8

#घोषणा MAX_RX_WINSIZE  64

काष्ठा mwअगरiex_ds_rx_reorder_tbl अणु
	u16 tid;
	u8 ta[ETH_ALEN];
	u32 start_win;
	u32 win_size;
	u32 buffer[MAX_RX_WINSIZE];
पूर्ण;

काष्ठा mwअगरiex_ds_tx_ba_stream_tbl अणु
	u16 tid;
	u8 ra[ETH_ALEN];
	u8 amsdu;
पूर्ण;

#घोषणा DBG_CMD_NUM    5
#घोषणा MWIFIEX_DBG_SDIO_MP_NUM    10

काष्ठा tdls_peer_info अणु
	u8 peer_addr[ETH_ALEN];
पूर्ण;

काष्ठा mwअगरiex_debug_info अणु
	अचिन्हित पूर्णांक debug_mask;
	u32 पूर्णांक_counter;
	u32 packets_out[MAX_NUM_TID];
	u32 tx_buf_size;
	u32 curr_tx_buf_size;
	u32 tx_tbl_num;
	काष्ठा mwअगरiex_ds_tx_ba_stream_tbl
		tx_tbl[MWIFIEX_MAX_TX_BASTREAM_SUPPORTED];
	u32 rx_tbl_num;
	काष्ठा mwअगरiex_ds_rx_reorder_tbl rx_tbl
		[MWIFIEX_MAX_RX_BASTREAM_SUPPORTED];
	u32 tdls_peer_num;
	काष्ठा tdls_peer_info tdls_list
		[MWIFIEX_MAX_TDLS_PEER_SUPPORTED];
	u16 ps_mode;
	u32 ps_state;
	u8 is_deep_sleep;
	u8 pm_wakeup_card_req;
	u32 pm_wakeup_fw_try;
	u8 is_hs_configured;
	u8 hs_activated;
	u32 num_cmd_host_to_card_failure;
	u32 num_cmd_sleep_cfm_host_to_card_failure;
	u32 num_tx_host_to_card_failure;
	u32 num_event_deauth;
	u32 num_event_disassoc;
	u32 num_event_link_lost;
	u32 num_cmd_deauth;
	u32 num_cmd_assoc_success;
	u32 num_cmd_assoc_failure;
	u32 num_tx_समयout;
	u8 is_cmd_समयकरोut;
	u16 समयout_cmd_id;
	u16 समयout_cmd_act;
	u16 last_cmd_id[DBG_CMD_NUM];
	u16 last_cmd_act[DBG_CMD_NUM];
	u16 last_cmd_index;
	u16 last_cmd_resp_id[DBG_CMD_NUM];
	u16 last_cmd_resp_index;
	u16 last_event[DBG_CMD_NUM];
	u16 last_event_index;
	u8 data_sent;
	u8 cmd_sent;
	u8 cmd_resp_received;
	u8 event_received;
	u32 last_mp_wr_biपंचांगap[MWIFIEX_DBG_SDIO_MP_NUM];
	u32 last_mp_wr_ports[MWIFIEX_DBG_SDIO_MP_NUM];
	u32 last_mp_wr_len[MWIFIEX_DBG_SDIO_MP_NUM];
	u32 last_mp_curr_wr_port[MWIFIEX_DBG_SDIO_MP_NUM];
	u8 last_sdio_mp_index;
पूर्ण;

#घोषणा MWIFIEX_KEY_INDEX_UNICAST	0x40000000
#घोषणा PN_LEN				16

काष्ठा mwअगरiex_ds_encrypt_key अणु
	u32 key_disable;
	u32 key_index;
	u32 key_len;
	u8 key_material[WLAN_MAX_KEY_LEN];
	u8 mac_addr[ETH_ALEN];
	u32 is_wapi_key;
	u8 pn[PN_LEN];		/* packet number */
	u8 pn_len;
	u8 is_igtk_key;
	u8 is_current_wep_key;
	u8 is_rx_seq_valid;
	u8 is_igtk_def_key;
पूर्ण;

काष्ठा mwअगरiex_घातer_cfg अणु
	u32 is_घातer_स्वतः;
	u32 is_घातer_fixed;
	u32 घातer_level;
पूर्ण;

काष्ठा mwअगरiex_ds_hs_cfg अणु
	u32 is_invoke_hostcmd;
	/*  Bit0: non-unicast data
	 *  Bit1: unicast data
	 *  Bit2: mac events
	 *  Bit3: magic packet
	 */
	u32 conditions;
	u32 gpio;
	u32 gap;
पूर्ण;

काष्ठा mwअगरiex_ds_wakeup_reason अणु
	u16  hs_wakeup_reason;
पूर्ण;

#घोषणा DEEP_SLEEP_ON  1
#घोषणा DEEP_SLEEP_OFF 0
#घोषणा DEEP_SLEEP_IDLE_TIME	100
#घोषणा PS_MODE_AUTO		1

काष्ठा mwअगरiex_ds_स्वतः_ds अणु
	u16 स्वतः_ds;
	u16 idle_समय;
पूर्ण;

काष्ठा mwअगरiex_ds_pm_cfg अणु
	जोड़ अणु
		u32 ps_mode;
		काष्ठा mwअगरiex_ds_hs_cfg hs_cfg;
		काष्ठा mwअगरiex_ds_स्वतः_ds स्वतः_deep_sleep;
		u32 sleep_period;
	पूर्ण param;
पूर्ण;

काष्ठा mwअगरiex_11ac_vht_cfg अणु
	u8 band_config;
	u8 misc_config;
	u32 cap_info;
	u32 mcs_tx_set;
	u32 mcs_rx_set;
पूर्ण;

काष्ठा mwअगरiex_ds_11n_tx_cfg अणु
	u16 tx_htcap;
	u16 tx_htinfo;
	u16 misc_config; /* Needed क्रम 802.11AC cards only */
पूर्ण;

काष्ठा mwअगरiex_ds_11n_amsdu_aggr_ctrl अणु
	u16 enable;
	u16 curr_buf_size;
पूर्ण;

काष्ठा mwअगरiex_ds_ant_cfg अणु
	u32 tx_ant;
	u32 rx_ant;
पूर्ण;

#घोषणा MWIFIEX_NUM_OF_CMD_BUFFER	50
#घोषणा MWIFIEX_SIZE_OF_CMD_BUFFER	2048

क्रमागत अणु
	MWIFIEX_IE_TYPE_GEN_IE = 0,
	MWIFIEX_IE_TYPE_ARP_FILTER,
पूर्ण;

क्रमागत अणु
	MWIFIEX_REG_MAC = 1,
	MWIFIEX_REG_BBP,
	MWIFIEX_REG_RF,
	MWIFIEX_REG_PMIC,
	MWIFIEX_REG_CAU,
पूर्ण;

काष्ठा mwअगरiex_ds_reg_rw अणु
	u32 type;
	u32 offset;
	u32 value;
पूर्ण;

#घोषणा MAX_EEPROM_DATA 256

काष्ठा mwअगरiex_ds_पढ़ो_eeprom अणु
	u16 offset;
	u16 byte_count;
	u8 value[MAX_EEPROM_DATA];
पूर्ण;

काष्ठा mwअगरiex_ds_mem_rw अणु
	u32 addr;
	u32 value;
पूर्ण;

#घोषणा IEEE_MAX_IE_SIZE		256

#घोषणा MWIFIEX_IE_HDR_SIZE	(माप(काष्ठा mwअगरiex_ie) - IEEE_MAX_IE_SIZE)

काष्ठा mwअगरiex_ds_misc_gen_ie अणु
	u32 type;
	u32 len;
	u8 ie_data[IEEE_MAX_IE_SIZE];
पूर्ण;

काष्ठा mwअगरiex_ds_misc_cmd अणु
	u32 len;
	u8 cmd[MWIFIEX_SIZE_OF_CMD_BUFFER];
पूर्ण;

#घोषणा BITMASK_BCN_RSSI_LOW	BIT(0)
#घोषणा BITMASK_BCN_RSSI_HIGH	BIT(4)

क्रमागत subsc_evt_rssi_state अणु
	EVENT_HANDLED,
	RSSI_LOW_RECVD,
	RSSI_HIGH_RECVD
पूर्ण;

काष्ठा subsc_evt_cfg अणु
	u8 असल_value;
	u8 evt_freq;
पूर्ण;

काष्ठा mwअगरiex_ds_misc_subsc_evt अणु
	u16 action;
	u16 events;
	काष्ठा subsc_evt_cfg bcn_l_rssi_cfg;
	काष्ठा subsc_evt_cfg bcn_h_rssi_cfg;
पूर्ण;

#घोषणा MWIFIEX_MEF_MAX_BYTESEQ		6	/* non-adjustable */
#घोषणा MWIFIEX_MEF_MAX_FILTERS		10

काष्ठा mwअगरiex_mef_filter अणु
	u16 repeat;
	u16 offset;
	s8 byte_seq[MWIFIEX_MEF_MAX_BYTESEQ + 1];
	u8 filt_type;
	u8 filt_action;
पूर्ण;

काष्ठा mwअगरiex_mef_entry अणु
	u8 mode;
	u8 action;
	काष्ठा mwअगरiex_mef_filter filter[MWIFIEX_MEF_MAX_FILTERS];
पूर्ण;

काष्ठा mwअगरiex_ds_mef_cfg अणु
	u32 criteria;
	u16 num_entries;
	काष्ठा mwअगरiex_mef_entry *mef_entry;
पूर्ण;

#घोषणा MWIFIEX_MAX_VSIE_LEN       (256)
#घोषणा MWIFIEX_MAX_VSIE_NUM       (8)
#घोषणा MWIFIEX_VSIE_MASK_CLEAR    0x00
#घोषणा MWIFIEX_VSIE_MASK_SCAN     0x01
#घोषणा MWIFIEX_VSIE_MASK_ASSOC    0x02
#घोषणा MWIFIEX_VSIE_MASK_ADHOC    0x04
#घोषणा MWIFIEX_VSIE_MASK_BGSCAN   0x08

क्रमागत अणु
	MWIFIEX_FUNC_INIT = 1,
	MWIFIEX_FUNC_SHUTDOWN,
पूर्ण;

क्रमागत COALESCE_OPERATION अणु
	RECV_FILTER_MATCH_TYPE_EQ = 0x80,
	RECV_FILTER_MATCH_TYPE_NE,
पूर्ण;

क्रमागत COALESCE_PACKET_TYPE अणु
	PACKET_TYPE_UNICAST = 1,
	PACKET_TYPE_MULTICAST = 2,
	PACKET_TYPE_BROADCAST = 3
पूर्ण;

#घोषणा MWIFIEX_COALESCE_MAX_RULES	8
#घोषणा MWIFIEX_COALESCE_MAX_BYTESEQ	4	/* non-adjustable */
#घोषणा MWIFIEX_COALESCE_MAX_FILTERS	4
#घोषणा MWIFIEX_MAX_COALESCING_DELAY	100     /* in msecs */

काष्ठा filt_field_param अणु
	u8 operation;
	u8 opeअक्रम_len;
	u16 offset;
	u8 opeअक्रम_byte_stream[MWIFIEX_COALESCE_MAX_BYTESEQ];
पूर्ण;

काष्ठा mwअगरiex_coalesce_rule अणु
	u16 max_coalescing_delay;
	u8 num_of_fields;
	u8 pkt_type;
	काष्ठा filt_field_param params[MWIFIEX_COALESCE_MAX_FILTERS];
पूर्ण;

काष्ठा mwअगरiex_ds_coalesce_cfg अणु
	u16 num_of_rules;
	काष्ठा mwअगरiex_coalesce_rule rule[MWIFIEX_COALESCE_MAX_RULES];
पूर्ण;

काष्ठा mwअगरiex_ds_tdls_oper अणु
	u16 tdls_action;
	u8 peer_mac[ETH_ALEN];
	u16 capability;
	u8 qos_info;
	u8 *ext_capab;
	u8 ext_capab_len;
	u8 *supp_rates;
	u8 supp_rates_len;
	u8 *ht_capab;
पूर्ण;

#पूर्ण_अगर /* !_MWIFIEX_IOCTL_H_ */
