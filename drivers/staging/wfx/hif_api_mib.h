<शैली गुरु>
/* SPDX-License-Identअगरier: Apache-2.0 */
/*
 * WFx hardware पूर्णांकerface definitions
 *
 * Copyright (c) 2018-2020, Silicon Laboratories Inc.
 */

#अगर_अघोषित WFX_HIF_API_MIB_H
#घोषणा WFX_HIF_API_MIB_H

#समावेश "hif_api_general.h"

#घोषणा HIF_API_IPV4_ADDRESS_SIZE 4
#घोषणा HIF_API_IPV6_ADDRESS_SIZE 16

क्रमागत hअगर_mib_ids अणु
	HIF_MIB_ID_GL_OPERATIONAL_POWER_MODE        = 0x2000,
	HIF_MIB_ID_GL_BLOCK_ACK_INFO                = 0x2001,
	HIF_MIB_ID_GL_SET_MULTI_MSG                 = 0x2002,
	HIF_MIB_ID_CCA_CONFIG                       = 0x2003,
	HIF_MIB_ID_ETHERTYPE_DATAFRAME_CONDITION    = 0x2010,
	HIF_MIB_ID_PORT_DATAFRAME_CONDITION         = 0x2011,
	HIF_MIB_ID_MAGIC_DATAFRAME_CONDITION        = 0x2012,
	HIF_MIB_ID_MAC_ADDR_DATAFRAME_CONDITION     = 0x2013,
	HIF_MIB_ID_IPV4_ADDR_DATAFRAME_CONDITION    = 0x2014,
	HIF_MIB_ID_IPV6_ADDR_DATAFRAME_CONDITION    = 0x2015,
	HIF_MIB_ID_UC_MC_BC_DATAFRAME_CONDITION     = 0x2016,
	HIF_MIB_ID_CONFIG_DATA_FILTER               = 0x2017,
	HIF_MIB_ID_SET_DATA_FILTERING               = 0x2018,
	HIF_MIB_ID_ARP_IP_ADDRESSES_TABLE           = 0x2019,
	HIF_MIB_ID_NS_IP_ADDRESSES_TABLE            = 0x201A,
	HIF_MIB_ID_RX_FILTER                        = 0x201B,
	HIF_MIB_ID_BEACON_FILTER_TABLE              = 0x201C,
	HIF_MIB_ID_BEACON_FILTER_ENABLE             = 0x201D,
	HIF_MIB_ID_GRP_SEQ_COUNTER                  = 0x2030,
	HIF_MIB_ID_TSF_COUNTER                      = 0x2031,
	HIF_MIB_ID_STATISTICS_TABLE                 = 0x2032,
	HIF_MIB_ID_COUNTERS_TABLE                   = 0x2033,
	HIF_MIB_ID_MAX_TX_POWER_LEVEL               = 0x2034,
	HIF_MIB_ID_EXTENDED_COUNTERS_TABLE          = 0x2035,
	HIF_MIB_ID_DOT11_MAC_ADDRESS                = 0x2040,
	HIF_MIB_ID_DOT11_MAX_TRANSMIT_MSDU_LIFETIME = 0x2041,
	HIF_MIB_ID_DOT11_MAX_RECEIVE_LIFETIME       = 0x2042,
	HIF_MIB_ID_DOT11_WEP_DEFAULT_KEY_ID         = 0x2043,
	HIF_MIB_ID_DOT11_RTS_THRESHOLD              = 0x2044,
	HIF_MIB_ID_SLOT_TIME                        = 0x2045,
	HIF_MIB_ID_CURRENT_TX_POWER_LEVEL           = 0x2046,
	HIF_MIB_ID_NON_ERP_PROTECTION               = 0x2047,
	HIF_MIB_ID_TEMPLATE_FRAME                   = 0x2048,
	HIF_MIB_ID_BEACON_WAKEUP_PERIOD             = 0x2049,
	HIF_MIB_ID_RCPI_RSSI_THRESHOLD              = 0x204A,
	HIF_MIB_ID_BLOCK_ACK_POLICY                 = 0x204B,
	HIF_MIB_ID_OVERRIDE_INTERNAL_TX_RATE        = 0x204C,
	HIF_MIB_ID_SET_ASSOCIATION_MODE             = 0x204D,
	HIF_MIB_ID_SET_UAPSD_INFORMATION            = 0x204E,
	HIF_MIB_ID_SET_TX_RATE_RETRY_POLICY         = 0x204F,
	HIF_MIB_ID_PROTECTED_MGMT_POLICY            = 0x2050,
	HIF_MIB_ID_SET_HT_PROTECTION                = 0x2051,
	HIF_MIB_ID_KEEP_ALIVE_PERIOD                = 0x2052,
	HIF_MIB_ID_ARP_KEEP_ALIVE_PERIOD            = 0x2053,
	HIF_MIB_ID_INACTIVITY_TIMER                 = 0x2054,
	HIF_MIB_ID_INTERFACE_PROTECTION             = 0x2055,
	HIF_MIB_ID_BEACON_STATS                     = 0x2056,
पूर्ण;

क्रमागत hअगर_op_घातer_mode अणु
	HIF_OP_POWER_MODE_ACTIVE    = 0x0,
	HIF_OP_POWER_MODE_DOZE      = 0x1,
	HIF_OP_POWER_MODE_QUIESCENT = 0x2
पूर्ण;

काष्ठा hअगर_mib_gl_operational_घातer_mode अणु
	u8     घातer_mode:4;
	u8     reserved1:3;
	u8     wup_ind_activation:1;
	u8     reserved2[3];
पूर्ण __packed;

काष्ठा hअगर_mib_gl_set_multi_msg अणु
	u8     enable_multi_tx_conf:1;
	u8     reserved1:7;
	u8     reserved2[3];
पूर्ण __packed;

क्रमागत hअगर_arp_ns_frame_treaपंचांगent अणु
	HIF_ARP_NS_FILTERING_DISABLE = 0x0,
	HIF_ARP_NS_FILTERING_ENABLE  = 0x1,
	HIF_ARP_NS_REPLY_ENABLE      = 0x2
पूर्ण;

काष्ठा hअगर_mib_arp_ip_addr_table अणु
	u8     condition_idx;
	u8     arp_enable;
	u8     reserved[2];
	u8     ipv4_address[HIF_API_IPV4_ADDRESS_SIZE];
पूर्ण __packed;

काष्ठा hअगर_mib_rx_filter अणु
	u8     reserved1:1;
	u8     bssid_filter:1;
	u8     reserved2:1;
	u8     fwd_probe_req:1;
	u8     keep_alive_filter:1;
	u8     reserved3:3;
	u8     reserved4[3];
पूर्ण __packed;

काष्ठा hअगर_ie_table_entry अणु
	u8     ie_id;
	u8     has_changed:1;
	u8     no_दीर्घer:1;
	u8     has_appeared:1;
	u8     reserved:1;
	u8     num_match_data:4;
	u8     oui[3];
	u8     match_data[3];
पूर्ण __packed;

काष्ठा hअगर_mib_bcn_filter_table अणु
	__le32 num_of_info_elmts;
	काष्ठा hअगर_ie_table_entry ie_table[];
पूर्ण __packed;

क्रमागत hअगर_beacon_filter अणु
	HIF_BEACON_FILTER_DISABLE  = 0x0,
	HIF_BEACON_FILTER_ENABLE   = 0x1,
	HIF_BEACON_FILTER_AUTO_ERP = 0x2
पूर्ण;

काष्ठा hअगर_mib_bcn_filter_enable अणु
	__le32 enable;
	__le32 bcn_count;
पूर्ण __packed;

काष्ठा hअगर_mib_extended_count_table अणु
	__le32 count_plcp_errors;
	__le32 count_fcs_errors;
	__le32 count_tx_packets;
	__le32 count_rx_packets;
	__le32 count_rx_packet_errors;
	__le32 count_rx_decryption_failures;
	__le32 count_rx_mic_failures;
	__le32 count_rx_no_key_failures;
	__le32 count_tx_multicast_frames;
	__le32 count_tx_frames_success;
	__le32 count_tx_frame_failures;
	__le32 count_tx_frames_retried;
	__le32 count_tx_frames_multi_retried;
	__le32 count_rx_frame_duplicates;
	__le32 count_rts_success;
	__le32 count_rts_failures;
	__le32 count_ack_failures;
	__le32 count_rx_multicast_frames;
	__le32 count_rx_frames_success;
	__le32 count_rx_cmacicv_errors;
	__le32 count_rx_cmac_replays;
	__le32 count_rx_mgmt_ccmp_replays;
	__le32 count_rx_bipmic_errors;
	__le32 count_rx_beacon;
	__le32 count_miss_beacon;
	__le32 reserved[15];
पूर्ण __packed;

काष्ठा hअगर_mib_count_table अणु
	__le32 count_plcp_errors;
	__le32 count_fcs_errors;
	__le32 count_tx_packets;
	__le32 count_rx_packets;
	__le32 count_rx_packet_errors;
	__le32 count_rx_decryption_failures;
	__le32 count_rx_mic_failures;
	__le32 count_rx_no_key_failures;
	__le32 count_tx_multicast_frames;
	__le32 count_tx_frames_success;
	__le32 count_tx_frame_failures;
	__le32 count_tx_frames_retried;
	__le32 count_tx_frames_multi_retried;
	__le32 count_rx_frame_duplicates;
	__le32 count_rts_success;
	__le32 count_rts_failures;
	__le32 count_ack_failures;
	__le32 count_rx_multicast_frames;
	__le32 count_rx_frames_success;
	__le32 count_rx_cmacicv_errors;
	__le32 count_rx_cmac_replays;
	__le32 count_rx_mgmt_ccmp_replays;
	__le32 count_rx_bipmic_errors;
पूर्ण __packed;

काष्ठा hअगर_mib_mac_address अणु
	u8     mac_addr[ETH_ALEN];
	__le16 reserved;
पूर्ण __packed;

काष्ठा hअगर_mib_wep_शेष_key_id अणु
	u8     wep_शेष_key_id;
	u8     reserved[3];
पूर्ण __packed;

काष्ठा hअगर_mib_करोt11_rts_threshold अणु
	__le32 threshold;
पूर्ण __packed;

काष्ठा hअगर_mib_slot_समय अणु
	__le32 slot_समय;
पूर्ण __packed;

काष्ठा hअगर_mib_current_tx_घातer_level अणु
	__le32 घातer_level; // चिन्हित value
पूर्ण __packed;

काष्ठा hअगर_mib_non_erp_protection अणु
	u8     use_cts_to_self:1;
	u8     reserved1:7;
	u8     reserved2[3];
पूर्ण __packed;

क्रमागत hअगर_पंचांगplt अणु
	HIF_TMPLT_PRBREQ = 0x0,
	HIF_TMPLT_BCN    = 0x1,
	HIF_TMPLT_शून्य   = 0x2,
	HIF_TMPLT_QOSNUL = 0x3,
	HIF_TMPLT_PSPOLL = 0x4,
	HIF_TMPLT_PRBRES = 0x5,
	HIF_TMPLT_ARP    = 0x6,
	HIF_TMPLT_NA     = 0x7
पूर्ण;

#घोषणा HIF_API_MAX_TEMPLATE_FRAME_SIZE 700

काष्ठा hअगर_mib_ढाँचा_frame अणु
	u8     frame_type;
	u8     init_rate:7;
	u8     mode:1;
	__le16 frame_length;
	u8     frame[];
पूर्ण __packed;

काष्ठा hअगर_mib_beacon_wake_up_period अणु
	u8     wakeup_period_min;
	u8     receive_dtim:1;
	u8     reserved1:7;
	u8     wakeup_period_max;
	u8     reserved2;
पूर्ण __packed;

काष्ठा hअगर_mib_rcpi_rssi_threshold अणु
	u8     detection:1;
	u8     rcpi_rssi:1;
	u8     upperthresh:1;
	u8     lowerthresh:1;
	u8     reserved:4;
	u8     lower_threshold;
	u8     upper_threshold;
	u8     rolling_average_count;
पूर्ण __packed;

#घोषणा DEFAULT_BA_MAX_RX_BUFFER_SIZE 16

काष्ठा hअगर_mib_block_ack_policy अणु
	u8     block_ack_tx_tid_policy;
	u8     reserved1;
	u8     block_ack_rx_tid_policy;
	u8     block_ack_rx_max_buffer_size;
पूर्ण __packed;

क्रमागत hअगर_mpdu_start_spacing अणु
	HIF_MPDU_START_SPACING_NO_RESTRIC = 0x0,
	HIF_MPDU_START_SPACING_QUARTER    = 0x1,
	HIF_MPDU_START_SPACING_HALF       = 0x2,
	HIF_MPDU_START_SPACING_ONE        = 0x3,
	HIF_MPDU_START_SPACING_TWO        = 0x4,
	HIF_MPDU_START_SPACING_FOUR       = 0x5,
	HIF_MPDU_START_SPACING_EIGHT      = 0x6,
	HIF_MPDU_START_SPACING_SIXTEEN    = 0x7
पूर्ण;

काष्ठा hअगर_mib_set_association_mode अणु
	u8     preambtype_use:1;
	u8     mode:1;
	u8     rateset:1;
	u8     spacing:1;
	u8     reserved1:4;
	u8     लघु_preamble:1;
	u8     reserved2:7;
	u8     greenfield:1;
	u8     reserved3:7;
	u8     mpdu_start_spacing;
	__le32 basic_rate_set;
पूर्ण __packed;

काष्ठा hअगर_mib_set_uapsd_inक्रमmation अणु
	u8     trig_bckgrnd:1;
	u8     trig_be:1;
	u8     trig_video:1;
	u8     trig_voice:1;
	u8     reserved1:4;
	u8     deliv_bckgrnd:1;
	u8     deliv_be:1;
	u8     deliv_video:1;
	u8     deliv_voice:1;
	u8     reserved2:4;
	__le16 min_स्वतः_trigger_पूर्णांकerval;
	__le16 max_स्वतः_trigger_पूर्णांकerval;
	__le16 स्वतः_trigger_step;
पूर्ण __packed;

काष्ठा hअगर_tx_rate_retry_policy अणु
	u8     policy_index;
	u8     लघु_retry_count;
	u8     दीर्घ_retry_count;
	u8     first_rate_sel:2;
	u8     terminate:1;
	u8     count_init:1;
	u8     reserved1:4;
	u8     rate_recovery_count;
	u8     reserved2[3];
	u8     rates[12];
पूर्ण __packed;

#घोषणा HIF_TX_RETRY_POLICY_MAX     15
#घोषणा HIF_TX_RETRY_POLICY_INVALID HIF_TX_RETRY_POLICY_MAX

काष्ठा hअगर_mib_set_tx_rate_retry_policy अणु
	u8     num_tx_rate_policies;
	u8     reserved[3];
	काष्ठा hअगर_tx_rate_retry_policy tx_rate_retry_policy[];
पूर्ण __packed;

काष्ठा hअगर_mib_रक्षित_mgmt_policy अणु
	u8     pmf_enable:1;
	u8     unpmf_allowed:1;
	u8     host_enc_auth_frames:1;
	u8     reserved1:5;
	u8     reserved2[3];
पूर्ण __packed;

काष्ठा hअगर_mib_keep_alive_period अणु
	__le16 keep_alive_period;
	u8     reserved[2];
पूर्ण __packed;

#पूर्ण_अगर
