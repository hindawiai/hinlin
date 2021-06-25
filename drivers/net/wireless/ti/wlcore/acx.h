<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl1271
 *
 * Copyright (C) 1998-2009 Texas Instruments. All rights reserved.
 * Copyright (C) 2008-2010 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#अगर_अघोषित __ACX_H__
#घोषणा __ACX_H__

#समावेश "wlcore.h"
#समावेश "cmd.h"

/*************************************************************************

    Host Interrupt Register (WiLink -> Host)

**************************************************************************/
/* HW Initiated पूर्णांकerrupt Watchकरोg समयr expiration */
#घोषणा WL1271_ACX_INTR_WATCHDOG           BIT(0)
/* Init sequence is करोne (masked पूर्णांकerrupt, detection through polling only ) */
#घोषणा WL1271_ACX_INTR_INIT_COMPLETE      BIT(1)
/* Event was entered to Event MBOX #A*/
#घोषणा WL1271_ACX_INTR_EVENT_A            BIT(2)
/* Event was entered to Event MBOX #B*/
#घोषणा WL1271_ACX_INTR_EVENT_B            BIT(3)
/* Command processing completion*/
#घोषणा WL1271_ACX_INTR_CMD_COMPLETE       BIT(4)
/* Signaling the host on HW wakeup */
#घोषणा WL1271_ACX_INTR_HW_AVAILABLE       BIT(5)
/* The MISC bit is used क्रम aggregation of RX, TxComplete and TX rate update */
#घोषणा WL1271_ACX_INTR_DATA               BIT(6)
/* Trace message on MBOX #A */
#घोषणा WL1271_ACX_INTR_TRACE_A            BIT(7)
/* Trace message on MBOX #B */
#घोषणा WL1271_ACX_INTR_TRACE_B            BIT(8)
/* SW FW Initiated पूर्णांकerrupt Watchकरोg समयr expiration */
#घोषणा WL1271_ACX_SW_INTR_WATCHDOG        BIT(9)

#घोषणा WL1271_ACX_INTR_ALL             0xFFFFFFFF

/* all possible पूर्णांकerrupts - only appropriate ones will be masked in */
#घोषणा WLCORE_ALL_INTR_MASK		(WL1271_ACX_INTR_WATCHDOG     | \
					WL1271_ACX_INTR_EVENT_A       | \
					WL1271_ACX_INTR_EVENT_B       | \
					WL1271_ACX_INTR_HW_AVAILABLE  | \
					WL1271_ACX_INTR_DATA          | \
					WL1271_ACX_SW_INTR_WATCHDOG)

/* Target's inक्रमmation element */
काष्ठा acx_header अणु
	काष्ठा wl1271_cmd_header cmd;

	/* acx (or inक्रमmation element) header */
	__le16 id;

	/* payload length (not including headers */
	__le16 len;
पूर्ण __packed;

काष्ठा acx_error_counter अणु
	काष्ठा acx_header header;

	/* The number of PLCP errors since the last समय this */
	/* inक्रमmation element was पूर्णांकerrogated. This field is */
	/* स्वतःmatically cleared when it is पूर्णांकerrogated.*/
	__le32 PLCP_error;

	/* The number of FCS errors since the last समय this */
	/* inक्रमmation element was पूर्णांकerrogated. This field is */
	/* स्वतःmatically cleared when it is पूर्णांकerrogated.*/
	__le32 FCS_error;

	/* The number of MPDUs without PLCP header errors received*/
	/* since the last समय this inक्रमmation element was पूर्णांकerrogated. */
	/* This field is स्वतःmatically cleared when it is पूर्णांकerrogated.*/
	__le32 valid_frame;

	/* the number of missed sequence numbers in the squentially */
	/* values of frames seq numbers */
	__le32 seq_num_miss;
पूर्ण __packed;

क्रमागत wl12xx_role अणु
	WL1271_ROLE_STA = 0,
	WL1271_ROLE_IBSS,
	WL1271_ROLE_AP,
	WL1271_ROLE_DEVICE,
	WL1271_ROLE_P2P_CL,
	WL1271_ROLE_P2P_GO,
	WL1271_ROLE_MESH_POINT,

	WL12XX_INVALID_ROLE_TYPE = 0xff
पूर्ण;

क्रमागत wl1271_psm_mode अणु
	/* Active mode */
	WL1271_PSM_CAM = 0,

	/* Power save mode */
	WL1271_PSM_PS = 1,

	/* Extreme low घातer */
	WL1271_PSM_ELP = 2,

	WL1271_PSM_MAX = WL1271_PSM_ELP,

	/* illegal out of band value of PSM mode */
	WL1271_PSM_ILLEGAL = 0xff
पूर्ण;

काष्ठा acx_sleep_auth अणु
	काष्ठा acx_header header;

	/* The sleep level authorization of the device. */
	/* 0 - Always active*/
	/* 1 - Power करोwn mode: light / fast sleep*/
	/* 2 - ELP mode: Deep / Max sleep*/
	u8  sleep_auth;
	u8  padding[3];
पूर्ण __packed;

क्रमागत अणु
	HOSTIF_PCI_MASTER_HOST_INसूचीECT,
	HOSTIF_PCI_MASTER_HOST_सूचीECT,
	HOSTIF_SLAVE,
	HOSTIF_PKT_RING,
	HOSTIF_DONTCARE = 0xFF
पूर्ण;

#घोषणा DEFAULT_UCAST_PRIORITY          0
#घोषणा DEFAULT_RX_Q_PRIORITY           0
#घोषणा DEFAULT_RXQ_PRIORITY            0 /* low 0 .. 15 high  */
#घोषणा DEFAULT_RXQ_TYPE                0x07    /* All frames, Data/Ctrl/Mgmt */
#घोषणा TRACE_BUFFER_MAX_SIZE           256

#घोषणा  DP_RX_PACKET_RING_CHUNK_SIZE 1600
#घोषणा  DP_TX_PACKET_RING_CHUNK_SIZE 1600
#घोषणा  DP_RX_PACKET_RING_CHUNK_NUM 2
#घोषणा  DP_TX_PACKET_RING_CHUNK_NUM 2
#घोषणा  DP_TX_COMPLETE_TIME_OUT 20

#घोषणा TX_MSDU_LIFETIME_MIN       0
#घोषणा TX_MSDU_LIFETIME_MAX       3000
#घोषणा TX_MSDU_LIFETIME_DEF       512
#घोषणा RX_MSDU_LIFETIME_MIN       0
#घोषणा RX_MSDU_LIFETIME_MAX       0xFFFFFFFF
#घोषणा RX_MSDU_LIFETIME_DEF       512000

काष्ठा acx_rx_msdu_lअगरeसमय अणु
	काष्ठा acx_header header;

	/*
	 * The maximum amount of समय, in TU, beक्रमe the
	 * firmware discards the MSDU.
	 */
	__le32 lअगरeसमय;
पूर्ण __packed;

क्रमागत acx_slot_type अणु
	SLOT_TIME_LONG = 0,
	SLOT_TIME_SHORT = 1,
	DEFAULT_SLOT_TIME = SLOT_TIME_SHORT,
	MAX_SLOT_TIMES = 0xFF
पूर्ण;

#घोषणा STATION_WONE_INDEX 0

काष्ठा acx_slot अणु
	काष्ठा acx_header header;

	u8 role_id;
	u8 wone_index; /* Reserved */
	u8 slot_समय;
	u8 reserved[5];
पूर्ण __packed;


#घोषणा ACX_MC_ADDRESS_GROUP_MAX	(8)
#घोषणा ADDRESS_GROUP_MAX_LEN	        (ETH_ALEN * ACX_MC_ADDRESS_GROUP_MAX)

काष्ठा acx_करोt11_grp_addr_tbl अणु
	काष्ठा acx_header header;

	u8 role_id;
	u8 enabled;
	u8 num_groups;
	u8 pad[1];
	u8 mac_table[ADDRESS_GROUP_MAX_LEN];
पूर्ण __packed;

काष्ठा acx_rx_समयout अणु
	काष्ठा acx_header header;

	u8 role_id;
	u8 reserved;
	__le16 ps_poll_समयout;
	__le16 upsd_समयout;
	u8 padding[2];
पूर्ण __packed;

काष्ठा acx_rts_threshold अणु
	काष्ठा acx_header header;

	u8 role_id;
	u8 reserved;
	__le16 threshold;
पूर्ण __packed;

काष्ठा acx_beacon_filter_option अणु
	काष्ठा acx_header header;

	u8 role_id;
	u8 enable;
	/*
	 * The number of beacons without the unicast TIM
	 * bit set that the firmware buffers beक्रमe
	 * संकेतing the host about पढ़ोy frames.
	 * When set to 0 and the filter is enabled, beacons
	 * without the unicast TIM bit set are dropped.
	 */
	u8 max_num_beacons;
	u8 pad[1];
पूर्ण __packed;

/*
 * ACXBeaconFilterEntry (not 221)
 * Byte Offset     Size (Bytes)    Definition
 * ===========     ============    ==========
 * 0               1               IE identअगरier
 * 1               1               Treaपंचांगent bit mask
 *
 * ACXBeaconFilterEntry (221)
 * Byte Offset     Size (Bytes)    Definition
 * ===========     ============    ==========
 * 0               1               IE identअगरier
 * 1               1               Treaपंचांगent bit mask
 * 2               3               OUI
 * 5               1               Type
 * 6               2               Version
 *
 *
 * Treaपंचांगent bit mask - The inक्रमmation element handling:
 * bit 0 - The inक्रमmation element is compared and transferred
 * in हाल of change.
 * bit 1 - The inक्रमmation element is transferred to the host
 * with each appearance or disappearance.
 * Note that both bits can be set at the same समय.
 */
#घोषणा	BEACON_FILTER_TABLE_MAX_IE_NUM		       (32)
#घोषणा BEACON_FILTER_TABLE_MAX_VENDOR_SPECIFIC_IE_NUM (6)
#घोषणा BEACON_FILTER_TABLE_IE_ENTRY_SIZE	       (2)
#घोषणा BEACON_FILTER_TABLE_EXTRA_VENDOR_SPECIFIC_IE_SIZE (6)
#घोषणा BEACON_FILTER_TABLE_MAX_SIZE ((BEACON_FILTER_TABLE_MAX_IE_NUM * \
			    BEACON_FILTER_TABLE_IE_ENTRY_SIZE) + \
			   (BEACON_FILTER_TABLE_MAX_VENDOR_SPECIFIC_IE_NUM * \
			    BEACON_FILTER_TABLE_EXTRA_VENDOR_SPECIFIC_IE_SIZE))

काष्ठा acx_beacon_filter_ie_table अणु
	काष्ठा acx_header header;

	u8 role_id;
	u8 num_ie;
	u8 pad[2];
	u8 table[BEACON_FILTER_TABLE_MAX_SIZE];
पूर्ण __packed;

काष्ठा acx_conn_monit_params अणु
       काष्ठा acx_header header;

	   u8 role_id;
	   u8 padding[3];
       __le32 synch_fail_thold; /* number of beacons missed */
       __le32 bss_lose_समयout; /* number of TU's from synch fail */
पूर्ण __packed;

काष्ठा acx_bt_wlan_coex अणु
	काष्ठा acx_header header;

	u8 enable;
	u8 pad[3];
पूर्ण __packed;

काष्ठा acx_bt_wlan_coex_param अणु
	काष्ठा acx_header header;

	__le32 params[WLCORE_CONF_SG_PARAMS_MAX];
	u8 param_idx;
	u8 padding[3];
पूर्ण __packed;

काष्ठा acx_dco_itrim_params अणु
	काष्ठा acx_header header;

	u8 enable;
	u8 padding[3];
	__le32 समयout;
पूर्ण __packed;

काष्ठा acx_energy_detection अणु
	काष्ठा acx_header header;

	/* The RX Clear Channel Assessment threshold in the PHY */
	__le16 rx_cca_threshold;
	u8 tx_energy_detection;
	u8 pad;
पूर्ण __packed;

काष्ठा acx_beacon_broadcast अणु
	काष्ठा acx_header header;

	u8 role_id;
	/* Enables receiving of broadcast packets in PS mode */
	u8 rx_broadcast_in_ps;

	__le16 beacon_rx_समयout;
	__le16 broadcast_समयout;

	/* Consecutive PS Poll failures beक्रमe updating the host */
	u8 ps_poll_threshold;
	u8 pad[1];
पूर्ण __packed;

काष्ठा acx_event_mask अणु
	काष्ठा acx_header header;

	__le32 event_mask;
	__le32 high_event_mask; /* Unused */
पूर्ण __packed;

#घोषणा SCAN_PASSIVE		BIT(0)
#घोषणा SCAN_5GHZ_BAND		BIT(1)
#घोषणा SCAN_TRIGGERED		BIT(2)
#घोषणा SCAN_PRIORITY_HIGH	BIT(3)

/* When set, disable HW encryption */
#घोषणा DF_ENCRYPTION_DISABLE      0x01
#घोषणा DF_SNIFF_MODE_ENABLE       0x80

काष्ठा acx_feature_config अणु
	काष्ठा acx_header header;

	u8 role_id;
	u8 padding[3];
	__le32 options;
	__le32 data_flow_options;
पूर्ण __packed;

काष्ठा acx_current_tx_घातer अणु
	काष्ठा acx_header header;

	u8  role_id;
	u8  current_tx_घातer;
	u8  padding[2];
पूर्ण __packed;

काष्ठा acx_wake_up_condition अणु
	काष्ठा acx_header header;

	u8 role_id;
	u8 wake_up_event; /* Only one bit can be set */
	u8 listen_पूर्णांकerval;
	u8 pad[1];
पूर्ण __packed;

काष्ठा acx_aid अणु
	काष्ठा acx_header header;

	/*
	 * To be set when associated with an AP.
	 */
	u8 role_id;
	u8 reserved;
	__le16 aid;
पूर्ण __packed;

क्रमागत acx_preamble_type अणु
	ACX_PREAMBLE_LONG = 0,
	ACX_PREAMBLE_SHORT = 1
पूर्ण;

काष्ठा acx_preamble अणु
	काष्ठा acx_header header;

	/*
	 * When set, the WiLink transmits the frames with a लघु preamble and
	 * when cleared, the WiLink transmits the frames with a दीर्घ preamble.
	 */
	u8 role_id;
	u8 preamble;
	u8 padding[2];
पूर्ण __packed;

क्रमागत acx_ctsprotect_type अणु
	CTSPROTECT_DISABLE = 0,
	CTSPROTECT_ENABLE = 1
पूर्ण;

काष्ठा acx_ctsprotect अणु
	काष्ठा acx_header header;
	u8 role_id;
	u8 ctsprotect;
	u8 padding[2];
पूर्ण __packed;

काष्ठा acx_rate_class अणु
	__le32 enabled_rates;
	u8 लघु_retry_limit;
	u8 दीर्घ_retry_limit;
	u8 aflags;
	u8 reserved;
पूर्ण;

काष्ठा acx_rate_policy अणु
	काष्ठा acx_header header;

	__le32 rate_policy_idx;
	काष्ठा acx_rate_class rate_policy;
पूर्ण __packed;

काष्ठा acx_ac_cfg अणु
	काष्ठा acx_header header;
	u8 role_id;
	u8 ac;
	u8 aअगरsn;
	u8 cw_min;
	__le16 cw_max;
	__le16 tx_op_limit;
पूर्ण __packed;

काष्ठा acx_tid_config अणु
	काष्ठा acx_header header;
	u8 role_id;
	u8 queue_id;
	u8 channel_type;
	u8 tsid;
	u8 ps_scheme;
	u8 ack_policy;
	u8 padding[2];
	__le32 apsd_conf[2];
पूर्ण __packed;

काष्ठा acx_frag_threshold अणु
	काष्ठा acx_header header;
	__le16 frag_threshold;
	u8 padding[2];
पूर्ण __packed;

काष्ठा acx_tx_config_options अणु
	काष्ठा acx_header header;
	__le16 tx_compl_समयout;     /* msec */
	__le16 tx_compl_threshold;   /* number of packets */
पूर्ण __packed;

काष्ठा wl12xx_acx_config_memory अणु
	काष्ठा acx_header header;

	u8 rx_mem_block_num;
	u8 tx_min_mem_block_num;
	u8 num_stations;
	u8 num_ssid_profiles;
	__le32 total_tx_descriptors;
	u8 dyn_mem_enable;
	u8 tx_मुक्त_req;
	u8 rx_मुक्त_req;
	u8 tx_min;
	u8 fwlog_blocks;
	u8 padding[3];
पूर्ण __packed;

काष्ठा wl1271_acx_mem_map अणु
	काष्ठा acx_header header;

	__le32 code_start;
	__le32 code_end;

	__le32 wep_defkey_start;
	__le32 wep_defkey_end;

	__le32 sta_table_start;
	__le32 sta_table_end;

	__le32 packet_ढाँचा_start;
	__le32 packet_ढाँचा_end;

	/* Address of the TX result पूर्णांकerface (control block) */
	__le32 tx_result;
	__le32 tx_result_queue_start;

	__le32 queue_memory_start;
	__le32 queue_memory_end;

	__le32 packet_memory_pool_start;
	__le32 packet_memory_pool_end;

	__le32 debug_buffer1_start;
	__le32 debug_buffer1_end;

	__le32 debug_buffer2_start;
	__le32 debug_buffer2_end;

	/* Number of blocks FW allocated क्रम TX packets */
	__le32 num_tx_mem_blocks;

	/* Number of blocks FW allocated क्रम RX packets */
	__le32 num_rx_mem_blocks;

	/* the following 4 fields are valid in SLAVE mode only */
	u8 *tx_cbuf;
	u8 *rx_cbuf;
	__le32 rx_ctrl;
	__le32 tx_ctrl;
पूर्ण __packed;

काष्ठा wl1271_acx_rx_config_opt अणु
	काष्ठा acx_header header;

	__le16 mblk_threshold;
	__le16 threshold;
	__le16 समयout;
	u8 queue_type;
	u8 reserved;
पूर्ण __packed;


काष्ठा wl1271_acx_bet_enable अणु
	काष्ठा acx_header header;

	u8 role_id;
	u8 enable;
	u8 max_consecutive;
	u8 padding[1];
पूर्ण __packed;

#घोषणा ACX_IPV4_VERSION 4
#घोषणा ACX_IPV6_VERSION 6
#घोषणा ACX_IPV4_ADDR_SIZE 4

/* biपंचांगap of enabled arp_filter features */
#घोषणा ACX_ARP_FILTER_ARP_FILTERING	BIT(0)
#घोषणा ACX_ARP_FILTER_AUTO_ARP		BIT(1)

काष्ठा wl1271_acx_arp_filter अणु
	काष्ठा acx_header header;
	u8 role_id;
	u8 version;         /* ACX_IPV4_VERSION, ACX_IPV6_VERSION */
	u8 enable;          /* biपंचांगap of enabled ARP filtering features */
	u8 padding[1];
	u8 address[16];     /* The configured device IP address - all ARP
			       requests directed to this IP address will pass
			       through. For IPv4, the first four bytes are
			       used. */
पूर्ण __packed;

काष्ठा wl1271_acx_pm_config अणु
	काष्ठा acx_header header;

	__le32 host_clk_settling_समय;
	u8 host_fast_wakeup_support;
	u8 padding[3];
पूर्ण __packed;

काष्ठा wl1271_acx_keep_alive_mode अणु
	काष्ठा acx_header header;

	u8 role_id;
	u8 enabled;
	u8 padding[2];
पूर्ण __packed;

क्रमागत अणु
	ACX_KEEP_ALIVE_NO_TX = 0,
	ACX_KEEP_ALIVE_PERIOD_ONLY
पूर्ण;

क्रमागत अणु
	ACX_KEEP_ALIVE_TPL_INVALID = 0,
	ACX_KEEP_ALIVE_TPL_VALID
पूर्ण;

काष्ठा wl1271_acx_keep_alive_config अणु
	काष्ठा acx_header header;

	u8 role_id;
	u8 index;
	u8 tpl_validation;
	u8 trigger;
	__le32 period;
पूर्ण __packed;

/* TODO: maybe this needs to be moved somewhere अन्यथा? */
#घोषणा HOST_IF_CFG_RX_FIFO_ENABLE     BIT(0)
#घोषणा HOST_IF_CFG_TX_EXTRA_BLKS_SWAP BIT(1)
#घोषणा HOST_IF_CFG_TX_PAD_TO_SDIO_BLK BIT(3)
#घोषणा HOST_IF_CFG_RX_PAD_TO_SDIO_BLK BIT(4)
#घोषणा HOST_IF_CFG_ADD_RX_ALIGNMENT   BIT(6)

क्रमागत अणु
	WL1271_ACX_TRIG_TYPE_LEVEL = 0,
	WL1271_ACX_TRIG_TYPE_EDGE,
पूर्ण;

क्रमागत अणु
	WL1271_ACX_TRIG_सूची_LOW = 0,
	WL1271_ACX_TRIG_सूची_HIGH,
	WL1271_ACX_TRIG_सूची_BIसूची,
पूर्ण;

क्रमागत अणु
	WL1271_ACX_TRIG_ENABLE = 1,
	WL1271_ACX_TRIG_DISABLE,
पूर्ण;

क्रमागत अणु
	WL1271_ACX_TRIG_METRIC_RSSI_BEACON = 0,
	WL1271_ACX_TRIG_METRIC_RSSI_DATA,
	WL1271_ACX_TRIG_METRIC_SNR_BEACON,
	WL1271_ACX_TRIG_METRIC_SNR_DATA,
पूर्ण;

क्रमागत अणु
	WL1271_ACX_TRIG_IDX_RSSI = 0,
	WL1271_ACX_TRIG_COUNT = 8,
पूर्ण;

काष्ठा wl1271_acx_rssi_snr_trigger अणु
	काष्ठा acx_header header;

	u8 role_id;
	u8 metric;
	u8 type;
	u8 dir;
	__le16 threshold;
	__le16 pacing; /* 0 - 60000 ms */
	u8 hysteresis;
	u8 index;
	u8 enable;
	u8 padding[1];
पूर्ण;

काष्ठा wl1271_acx_rssi_snr_avg_weights अणु
	काष्ठा acx_header header;

	u8 role_id;
	u8 padding[3];
	u8 rssi_beacon;
	u8 rssi_data;
	u8 snr_beacon;
	u8 snr_data;
पूर्ण;


/* special capability bit (not employed by the 802.11n spec) */
#घोषणा WL12XX_HT_CAP_HT_OPERATION BIT(16)

/*
 * ACX_PEER_HT_CAP
 * Configure HT capabilities - declare the capabilities of the peer
 * we are connected to.
 */
काष्ठा wl1271_acx_ht_capabilities अणु
	काष्ठा acx_header header;

	/* biपंचांगask of capability bits supported by the peer */
	__le32 ht_capabilites;

	/* Indicates to which link these capabilities apply. */
	u8 hlid;

	/*
	 * This the maximum A-MPDU length supported by the AP. The FW may not
	 * exceed this length when sending A-MPDUs
	 */
	u8 ampdu_max_length;

	/* This is the minimal spacing required when sending A-MPDUs to the AP*/
	u8 ampdu_min_spacing;

	u8 padding;
पूर्ण __packed;

/*
 * ACX_HT_BSS_OPERATION
 * Configure HT capabilities - AP rules क्रम behavior in the BSS.
 */
काष्ठा wl1271_acx_ht_inक्रमmation अणु
	काष्ठा acx_header header;

	u8 role_id;

	/* Values: 0 - RIFS not allowed, 1 - RIFS allowed */
	u8 rअगरs_mode;

	/* Values: 0 - 3 like in spec */
	u8 ht_protection;

	/* Values: 0 - GF protection not required, 1 - GF protection required */
	u8 gf_protection;

	/*Values: 0 - TX Burst limit not required, 1 - TX Burst Limit required*/
	u8 ht_tx_burst_limit;

	/*
	 * Values: 0 - Dual CTS protection not required,
	 *         1 - Dual CTS Protection required
	 * Note: When this value is set to 1 FW will protect all TXOP with RTS
	 * frame and will not use CTS-to-self regardless of the value of the
	 * ACX_CTS_PROTECTION inक्रमmation element
	 */
	u8 dual_cts_protection;

	u8 padding[2];
पूर्ण __packed;

काष्ठा wl1271_acx_ba_initiator_policy अणु
	काष्ठा acx_header header;

	/* Specअगरies role Id, Range 0-7, 0xFF means ANY role. */
	u8 role_id;

	/*
	 * Per TID setting क्रम allowing TX BA. Set a bit to 1 to allow
	 * TX BA sessions क्रम the corresponding TID.
	 */
	u8 tid_biपंचांगap;

	/* Winकरोws size in number of packets */
	u8 win_size;

	u8 padding1[1];

	/* As initiator inactivity समयout in समय units(TU) of 1024us */
	u16 inactivity_समयout;

	u8 padding[2];
पूर्ण __packed;

काष्ठा wl1271_acx_ba_receiver_setup अणु
	काष्ठा acx_header header;

	/* Specअगरies link id, range 0-31 */
	u8 hlid;

	u8 tid;

	u8 enable;

	/* Winकरोws size in number of packets */
	u8 win_size;

	/* BA session starting sequence number.  RANGE 0-FFF */
	u16 ssn;

	u8 padding[2];
पूर्ण __packed;

काष्ठा wl12xx_acx_fw_tsf_inक्रमmation अणु
	काष्ठा acx_header header;

	u8 role_id;
	u8 padding1[3];
	__le32 current_tsf_high;
	__le32 current_tsf_low;
	__le32 last_bttt_high;
	__le32 last_tbtt_low;
	u8 last_dtim_count;
	u8 padding2[3];
पूर्ण __packed;

काष्ठा wl1271_acx_ps_rx_streaming अणु
	काष्ठा acx_header header;

	u8 role_id;
	u8 tid;
	u8 enable;

	/* पूर्णांकerval between triggers (10-100 msec) */
	u8 period;

	/* समयout beक्रमe first trigger (0-200 msec) */
	u8 समयout;
	u8 padding[3];
पूर्ण __packed;

काष्ठा wl1271_acx_ap_max_tx_retry अणु
	काष्ठा acx_header header;

	u8 role_id;
	u8 padding_1;

	/*
	 * the number of frames transmission failures beक्रमe
	 * issuing the aging event.
	 */
	__le16 max_tx_retry;
पूर्ण __packed;

काष्ठा wl1271_acx_config_ps अणु
	काष्ठा acx_header header;

	u8 निकास_retries;
	u8 enter_retries;
	u8 padding[2];
	__le32 null_data_rate;
पूर्ण __packed;

काष्ठा wl1271_acx_inconnection_sta अणु
	काष्ठा acx_header header;

	u8 addr[ETH_ALEN];
	u8 role_id;
	u8 padding;
पूर्ण __packed;

/*
 * ACX_FM_COEX_CFG
 * set the FM co-existence parameters.
 */
काष्ठा wl1271_acx_fm_coex अणु
	काष्ठा acx_header header;
	/* enable(1) / disable(0) the FM Coex feature */
	u8 enable;
	/*
	 * Swallow period used in COEX PLL swallowing mechanism.
	 * 0xFF = use FW शेष
	 */
	u8 swallow_period;
	/*
	 * The N भागider used in COEX PLL swallowing mechanism क्रम Fref of
	 * 38.4/19.2 Mhz. 0xFF = use FW शेष
	 */
	u8 n_भागider_fref_set_1;
	/*
	 * The N भागider used in COEX PLL swallowing mechanism क्रम Fref of
	 * 26/52 Mhz. 0xFF = use FW शेष
	 */
	u8 n_भागider_fref_set_2;
	/*
	 * The M भागider used in COEX PLL swallowing mechanism क्रम Fref of
	 * 38.4/19.2 Mhz. 0xFFFF = use FW शेष
	 */
	__le16 m_भागider_fref_set_1;
	/*
	 * The M भागider used in COEX PLL swallowing mechanism क्रम Fref of
	 * 26/52 Mhz. 0xFFFF = use FW शेष
	 */
	__le16 m_भागider_fref_set_2;
	/*
	 * The समय duration in uSec required क्रम COEX PLL to stabilize.
	 * 0xFFFFFFFF = use FW शेष
	 */
	__le32 coex_pll_stabilization_समय;
	/*
	 * The समय duration in uSec required क्रम LDO to stabilize.
	 * 0xFFFFFFFF = use FW शेष
	 */
	__le16 lकरो_stabilization_समय;
	/*
	 * The disturbed frequency band margin around the disturbed frequency
	 * center (single sided).
	 * For example, अगर 2 is configured, the following channels will be
	 * considered disturbed channel:
	 *   80 +- 0.1 MHz, 91 +- 0.1 MHz, 98 +- 0.1 MHz, 102 +- 0.1 MH
	 * 0xFF = use FW शेष
	 */
	u8 fm_disturbed_band_margin;
	/*
	 * The swallow घड़ी dअगरference of the swallowing mechanism.
	 * 0xFF = use FW शेष
	 */
	u8 swallow_clk_dअगरf;
पूर्ण __packed;

#घोषणा ACX_RATE_MGMT_ALL_PARAMS 0xff
काष्ठा wl12xx_acx_set_rate_mgmt_params अणु
	काष्ठा acx_header header;

	u8 index; /* 0xff to configure all params */
	u8 padding1;
	__le16 rate_retry_score;
	__le16 per_add;
	__le16 per_th1;
	__le16 per_th2;
	__le16 max_per;
	u8 inverse_curiosity_factor;
	u8 tx_fail_low_th;
	u8 tx_fail_high_th;
	u8 per_alpha_shअगरt;
	u8 per_add_shअगरt;
	u8 per_beta1_shअगरt;
	u8 per_beta2_shअगरt;
	u8 rate_check_up;
	u8 rate_check_करोwn;
	u8 rate_retry_policy[ACX_RATE_MGMT_NUM_OF_RATES];
	u8 padding2[2];
पूर्ण __packed;

काष्ठा wl12xx_acx_config_hangover अणु
	काष्ठा acx_header header;

	__le32 recover_समय;
	u8 hangover_period;
	u8 dynamic_mode;
	u8 early_termination_mode;
	u8 max_period;
	u8 min_period;
	u8 increase_delta;
	u8 decrease_delta;
	u8 quiet_समय;
	u8 increase_समय;
	u8 winकरोw_size;
	u8 padding[2];
पूर्ण __packed;


काष्ठा acx_शेष_rx_filter अणु
	काष्ठा acx_header header;
	u8 enable;

	/* action of type FILTER_XXX */
	u8 शेष_action;

	u8 pad[2];
पूर्ण __packed;


काष्ठा acx_rx_filter_cfg अणु
	काष्ठा acx_header header;

	u8 enable;

	/* 0 - WL1271_MAX_RX_FILTERS-1 */
	u8 index;

	u8 action;

	u8 num_fields;
	u8 fields[];
पूर्ण __packed;

काष्ठा acx_roaming_stats अणु
	काष्ठा acx_header header;

	u8	role_id;
	u8	pad[3];
	u32	missed_beacons;
	u8	snr_data;
	u8	snr_bacon;
	s8	rssi_data;
	s8	rssi_beacon;
पूर्ण __packed;

क्रमागत अणु
	ACX_WAKE_UP_CONDITIONS           = 0x0000,
	ACX_MEM_CFG                      = 0x0001,
	ACX_SLOT                         = 0x0002,
	ACX_AC_CFG                       = 0x0003,
	ACX_MEM_MAP                      = 0x0004,
	ACX_AID                          = 0x0005,
	ACX_MEDIUM_USAGE                 = 0x0006,
	ACX_STATISTICS                   = 0x0007,
	ACX_PWR_CONSUMPTION_STATISTICS   = 0x0008,
	ACX_TID_CFG                      = 0x0009,
	ACX_PS_RX_STREAMING              = 0x000A,
	ACX_BEACON_FILTER_OPT            = 0x000B,
	ACX_NOISE_HIST                   = 0x000C,
	ACX_HDK_VERSION                  = 0x000D,
	ACX_PD_THRESHOLD                 = 0x000E,
	ACX_TX_CONFIG_OPT                = 0x000F,
	ACX_CCA_THRESHOLD                = 0x0010,
	ACX_EVENT_MBOX_MASK              = 0x0011,
	ACX_CONN_MONIT_PARAMS            = 0x0012,
	ACX_DISABLE_BROADCASTS           = 0x0013,
	ACX_BCN_DTIM_OPTIONS             = 0x0014,
	ACX_SG_ENABLE                    = 0x0015,
	ACX_SG_CFG                       = 0x0016,
	ACX_FM_COEX_CFG                  = 0x0017,
	ACX_BEACON_FILTER_TABLE          = 0x0018,
	ACX_ARP_IP_FILTER                = 0x0019,
	ACX_ROAMING_STATISTICS_TBL       = 0x001A,
	ACX_RATE_POLICY                  = 0x001B,
	ACX_CTS_PROTECTION               = 0x001C,
	ACX_SLEEP_AUTH                   = 0x001D,
	ACX_PREAMBLE_TYPE                = 0x001E,
	ACX_ERROR_CNT                    = 0x001F,
	ACX_IBSS_FILTER                  = 0x0020,
	ACX_SERVICE_PERIOD_TIMEOUT       = 0x0021,
	ACX_TSF_INFO                     = 0x0022,
	ACX_CONFIG_PS_WMM                = 0x0023,
	ACX_ENABLE_RX_DATA_FILTER        = 0x0024,
	ACX_SET_RX_DATA_FILTER           = 0x0025,
	ACX_GET_DATA_FILTER_STATISTICS   = 0x0026,
	ACX_RX_CONFIG_OPT                = 0x0027,
	ACX_FRAG_CFG                     = 0x0028,
	ACX_BET_ENABLE                   = 0x0029,
	ACX_RSSI_SNR_TRIGGER             = 0x002A,
	ACX_RSSI_SNR_WEIGHTS             = 0x002B,
	ACX_KEEP_ALIVE_MODE              = 0x002C,
	ACX_SET_KEEP_ALIVE_CONFIG        = 0x002D,
	ACX_BA_SESSION_INIT_POLICY       = 0x002E,
	ACX_BA_SESSION_RX_SETUP          = 0x002F,
	ACX_PEER_HT_CAP                  = 0x0030,
	ACX_HT_BSS_OPERATION             = 0x0031,
	ACX_COEX_ACTIVITY                = 0x0032,
	ACX_BURST_MODE                   = 0x0033,
	ACX_SET_RATE_MGMT_PARAMS         = 0x0034,
	ACX_GET_RATE_MGMT_PARAMS         = 0x0035,
	ACX_SET_RATE_ADAPT_PARAMS        = 0x0036,
	ACX_SET_DCO_ITRIM_PARAMS         = 0x0037,
	ACX_GEN_FW_CMD                   = 0x0038,
	ACX_HOST_IF_CFG_BITMAP           = 0x0039,
	ACX_MAX_TX_FAILURE               = 0x003A,
	ACX_UPDATE_INCONNECTION_STA_LIST = 0x003B,
	DOT11_RX_MSDU_LIFE_TIME          = 0x003C,
	DOT11_CUR_TX_PWR                 = 0x003D,
	DOT11_RTS_THRESHOLD              = 0x003E,
	DOT11_GROUP_ADDRESS_TBL          = 0x003F,
	ACX_PM_CONFIG                    = 0x0040,
	ACX_CONFIG_PS                    = 0x0041,
	ACX_CONFIG_HANGOVER              = 0x0042,
	ACX_FEATURE_CFG                  = 0x0043,
	ACX_PROTECTION_CFG               = 0x0044,
पूर्ण;


पूर्णांक wl1271_acx_wake_up_conditions(काष्ठा wl1271 *wl,
				  काष्ठा wl12xx_vअगर *wlvअगर,
				  u8 wake_up_event, u8 listen_पूर्णांकerval);
पूर्णांक wl1271_acx_sleep_auth(काष्ठा wl1271 *wl, u8 sleep_auth);
पूर्णांक wl1271_acx_tx_घातer(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			पूर्णांक घातer);
पूर्णांक wl1271_acx_feature_cfg(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
पूर्णांक wl1271_acx_mem_map(काष्ठा wl1271 *wl,
		       काष्ठा acx_header *mem_map, माप_प्रकार len);
पूर्णांक wl1271_acx_rx_msdu_lअगरe_समय(काष्ठा wl1271 *wl);
पूर्णांक wl1271_acx_slot(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
		    क्रमागत acx_slot_type slot_समय);
पूर्णांक wl1271_acx_group_address_tbl(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				 bool enable, व्योम *mc_list, u32 mc_list_len);
पूर्णांक wl1271_acx_service_period_समयout(काष्ठा wl1271 *wl,
				      काष्ठा wl12xx_vअगर *wlvअगर);
पूर्णांक wl1271_acx_rts_threshold(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			     u32 rts_threshold);
पूर्णांक wl1271_acx_dco_itrim_params(काष्ठा wl1271 *wl);
पूर्णांक wl1271_acx_beacon_filter_opt(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				 bool enable_filter);
पूर्णांक wl1271_acx_beacon_filter_table(काष्ठा wl1271 *wl,
				   काष्ठा wl12xx_vअगर *wlvअगर);
पूर्णांक wl1271_acx_conn_monit_params(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				 bool enable);
पूर्णांक wl1271_acx_sg_enable(काष्ठा wl1271 *wl, bool enable);
पूर्णांक wl12xx_acx_sg_cfg(काष्ठा wl1271 *wl);
पूर्णांक wl1271_acx_cca_threshold(काष्ठा wl1271 *wl);
पूर्णांक wl1271_acx_bcn_dtim_options(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
पूर्णांक wl1271_acx_aid(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर, u16 aid);
पूर्णांक wl1271_acx_event_mbox_mask(काष्ठा wl1271 *wl, u32 event_mask);
पूर्णांक wl1271_acx_set_preamble(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			    क्रमागत acx_preamble_type preamble);
पूर्णांक wl1271_acx_cts_protect(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			   क्रमागत acx_ctsprotect_type ctsprotect);
पूर्णांक wl1271_acx_statistics(काष्ठा wl1271 *wl, व्योम *stats);
पूर्णांक wl1271_acx_sta_rate_policies(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
पूर्णांक wl1271_acx_ap_rate_policy(काष्ठा wl1271 *wl, काष्ठा conf_tx_rate_class *c,
		      u8 idx);
पूर्णांक wl1271_acx_ac_cfg(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
		      u8 ac, u8 cw_min, u16 cw_max, u8 aअगरsn, u16 txop);
पूर्णांक wl1271_acx_tid_cfg(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
		       u8 queue_id, u8 channel_type,
		       u8 tsid, u8 ps_scheme, u8 ack_policy,
		       u32 apsd_conf0, u32 apsd_conf1);
पूर्णांक wl1271_acx_frag_threshold(काष्ठा wl1271 *wl, u32 frag_threshold);
पूर्णांक wl1271_acx_tx_config_options(काष्ठा wl1271 *wl);
पूर्णांक wl12xx_acx_mem_cfg(काष्ठा wl1271 *wl);
पूर्णांक wl1271_acx_init_mem_config(काष्ठा wl1271 *wl);
पूर्णांक wl1271_acx_init_rx_पूर्णांकerrupt(काष्ठा wl1271 *wl);
पूर्णांक wl1271_acx_smart_reflex(काष्ठा wl1271 *wl);
पूर्णांक wl1271_acx_bet_enable(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			  bool enable);
पूर्णांक wl1271_acx_arp_ip_filter(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			     u8 enable, __be32 address);
पूर्णांक wl1271_acx_pm_config(काष्ठा wl1271 *wl);
पूर्णांक wl1271_acx_keep_alive_mode(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *vअगर,
			       bool enable);
पूर्णांक wl1271_acx_keep_alive_config(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				 u8 index, u8 tpl_valid);
पूर्णांक wl1271_acx_rssi_snr_trigger(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				bool enable, s16 thold, u8 hyst);
पूर्णांक wl1271_acx_rssi_snr_avg_weights(काष्ठा wl1271 *wl,
				    काष्ठा wl12xx_vअगर *wlvअगर);
पूर्णांक wl1271_acx_set_ht_capabilities(काष्ठा wl1271 *wl,
				    काष्ठा ieee80211_sta_ht_cap *ht_cap,
				    bool allow_ht_operation, u8 hlid);
पूर्णांक wl1271_acx_set_ht_inक्रमmation(काष्ठा wl1271 *wl,
				   काष्ठा wl12xx_vअगर *wlvअगर,
				   u16 ht_operation_mode);
पूर्णांक wl12xx_acx_set_ba_initiator_policy(काष्ठा wl1271 *wl,
				       काष्ठा wl12xx_vअगर *wlvअगर);
पूर्णांक wl12xx_acx_set_ba_receiver_session(काष्ठा wl1271 *wl, u8 tid_index,
				       u16 ssn, bool enable, u8 peer_hlid,
				       u8 win_size);
पूर्णांक wl12xx_acx_tsf_info(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			u64 *maस_समय);
पूर्णांक wl1271_acx_ps_rx_streaming(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			       bool enable);
पूर्णांक wl1271_acx_ap_max_tx_retry(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
पूर्णांक wl12xx_acx_config_ps(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
पूर्णांक wl1271_acx_set_inconnection_sta(काष्ठा wl1271 *wl,
				    काष्ठा wl12xx_vअगर *wlvअगर, u8 *addr);
पूर्णांक wl1271_acx_fm_coex(काष्ठा wl1271 *wl);
पूर्णांक wl12xx_acx_set_rate_mgmt_params(काष्ठा wl1271 *wl);
पूर्णांक wl12xx_acx_config_hangover(काष्ठा wl1271 *wl);
पूर्णांक wlcore_acx_average_rssi(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			    s8 *avg_rssi);

पूर्णांक wl1271_acx_शेष_rx_filter_enable(काष्ठा wl1271 *wl, bool enable,
					क्रमागत rx_filter_action action);
पूर्णांक wl1271_acx_set_rx_filter(काष्ठा wl1271 *wl, u8 index, bool enable,
			     काष्ठा wl12xx_rx_filter *filter);
#पूर्ण_अगर /* __WL1271_ACX_H__ */
