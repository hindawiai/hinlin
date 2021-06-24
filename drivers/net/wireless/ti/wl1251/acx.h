<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl1251
 *
 * Copyright (c) 1998-2007 Texas Instruments Incorporated
 * Copyright (C) 2008 Nokia Corporation
 */

#अगर_अघोषित __WL1251_ACX_H__
#घोषणा __WL1251_ACX_H__

#समावेश "wl1251.h"
#समावेश "cmd.h"

/* Target's inक्रमmation element */
काष्ठा acx_header अणु
	काष्ठा wl1251_cmd_header cmd;

	/* acx (or inक्रमmation element) header */
	u16 id;

	/* payload length (not including headers */
	u16 len;
पूर्ण __packed;

काष्ठा acx_error_counter अणु
	काष्ठा acx_header header;

	/* The number of PLCP errors since the last समय this */
	/* inक्रमmation element was पूर्णांकerrogated. This field is */
	/* स्वतःmatically cleared when it is पूर्णांकerrogated.*/
	u32 PLCP_error;

	/* The number of FCS errors since the last समय this */
	/* inक्रमmation element was पूर्णांकerrogated. This field is */
	/* स्वतःmatically cleared when it is पूर्णांकerrogated.*/
	u32 FCS_error;

	/* The number of MPDUs without PLCP header errors received*/
	/* since the last समय this inक्रमmation element was पूर्णांकerrogated. */
	/* This field is स्वतःmatically cleared when it is पूर्णांकerrogated.*/
	u32 valid_frame;

	/* the number of missed sequence numbers in the squentially */
	/* values of frames seq numbers */
	u32 seq_num_miss;
पूर्ण __packed;

काष्ठा acx_revision अणु
	काष्ठा acx_header header;

	/*
	 * The WiLink firmware version, an ASCII string x.x.x.x,
	 * that uniquely identअगरies the current firmware.
	 * The left most digit is incremented each समय a
	 * signअगरicant change is made to the firmware, such as
	 * code redesign or new platक्रमm support.
	 * The second digit is incremented when major enhancements
	 * are added or major fixes are made.
	 * The third digit is incremented क्रम each GA release.
	 * The fourth digit is incremented क्रम each build.
	 * The first two digits identअगरy a firmware release version,
	 * in other words, a unique set of features.
	 * The first three digits identअगरy a GA release.
	 */
	अक्षर fw_version[20];

	/*
	 * This 4 byte field specअगरies the WiLink hardware version.
	 * bits 0  - 15: Reserved.
	 * bits 16 - 23: Version ID - The WiLink version ID
	 *              (1 = first spin, 2 = second spin, and so on).
	 * bits 24 - 31: Chip ID - The WiLink chip ID.
	 */
	u32 hw_version;
पूर्ण __packed;

क्रमागत wl1251_psm_mode अणु
	/* Active mode */
	WL1251_PSM_CAM = 0,

	/* Power save mode */
	WL1251_PSM_PS = 1,

	/* Extreme low घातer */
	WL1251_PSM_ELP = 2,
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
#घोषणा DEFAULT_NUM_STATIONS            1
#घोषणा DEFAULT_RXQ_PRIORITY            0 /* low 0 .. 15 high  */
#घोषणा DEFAULT_RXQ_TYPE                0x07    /* All frames, Data/Ctrl/Mgmt */
#घोषणा TRACE_BUFFER_MAX_SIZE           256

#घोषणा  DP_RX_PACKET_RING_CHUNK_SIZE 1600
#घोषणा  DP_TX_PACKET_RING_CHUNK_SIZE 1600
#घोषणा  DP_RX_PACKET_RING_CHUNK_NUM 2
#घोषणा  DP_TX_PACKET_RING_CHUNK_NUM 2
#घोषणा  DP_TX_COMPLETE_TIME_OUT 20
#घोषणा  FW_TX_CMPLT_BLOCK_SIZE 16

काष्ठा acx_data_path_params अणु
	काष्ठा acx_header header;

	u16 rx_packet_ring_chunk_size;
	u16 tx_packet_ring_chunk_size;

	u8 rx_packet_ring_chunk_num;
	u8 tx_packet_ring_chunk_num;

	/*
	 * Maximum number of packets that can be gathered
	 * in the TX complete ring beक्रमe an पूर्णांकerrupt
	 * is generated.
	 */
	u8 tx_complete_threshold;

	/* Number of pending TX complete entries in cyclic ring.*/
	u8 tx_complete_ring_depth;

	/*
	 * Max num microseconds since a packet enters the TX
	 * complete ring until an पूर्णांकerrupt is generated.
	 */
	u32 tx_complete_समयout;
पूर्ण __packed;


काष्ठा acx_data_path_params_resp अणु
	काष्ठा acx_header header;

	u16 rx_packet_ring_chunk_size;
	u16 tx_packet_ring_chunk_size;

	u8 rx_packet_ring_chunk_num;
	u8 tx_packet_ring_chunk_num;

	u8 pad[2];

	u32 rx_packet_ring_addr;
	u32 tx_packet_ring_addr;

	u32 rx_control_addr;
	u32 tx_control_addr;

	u32 tx_complete_addr;
पूर्ण __packed;

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
	u32 lअगरeसमय;
पूर्ण __packed;

/*
 * RX Config Options Table
 * Bit		Definition
 * ===		==========
 * 31:14		Reserved
 * 13		Copy RX Status - when set, ग_लिखो three receive status words
 * 	 	to top of rx'd MPDUs.
 * 		When cleared, करो not ग_लिखो three status words (added rev 1.5)
 * 12		Reserved
 * 11		RX Complete upon FCS error - when set, give rx complete
 *	 	पूर्णांकerrupt क्रम FCS errors, after the rx filtering, e.g. unicast
 *	 	frames not to us with FCS error will not generate an पूर्णांकerrupt.
 * 10		SSID Filter Enable - When set, the WiLink discards all beacon,
 *	        probe request, and probe response frames with an SSID that करोes
 *		not match the SSID specअगरied by the host in the START/JOIN
 *		command.
 *		When clear, the WiLink receives frames with any SSID.
 * 9		Broadcast Filter Enable - When set, the WiLink discards all
 * 	 	broadcast frames. When clear, the WiLink receives all received
 *		broadcast frames.
 * 8:6		Reserved
 * 5		BSSID Filter Enable - When set, the WiLink discards any frames
 * 	 	with a BSSID that करोes not match the BSSID specअगरied by the
 *		host.
 *		When clear, the WiLink receives frames from any BSSID.
 * 4		MAC Addr Filter - When set, the WiLink discards any frames
 * 	 	with a destination address that करोes not match the MAC address
 *		of the adaptor.
 *		When clear, the WiLink receives frames destined to any MAC
 *		address.
 * 3		Promiscuous - When set, the WiLink receives all valid frames
 * 	 	(i.e., all frames that pass the FCS check).
 *		When clear, only frames that pass the other filters specअगरied
 *		are received.
 * 2		FCS - When set, the WiLink includes the FCS with the received
 *	 	frame.
 *		When cleared, the FCS is discarded.
 * 1		PLCP header - When set, ग_लिखो all data from baseband to frame
 * 	 	buffer including PHY header.
 * 0		Reserved - Always equal to 0.
 *
 * RX Filter Options Table
 * Bit		Definition
 * ===		==========
 * 31:12		Reserved - Always equal to 0.
 * 11		Association - When set, the WiLink receives all association
 * 	 	related frames (association request/response, reassocation
 *		request/response, and disassociation). When clear, these frames
 *		are discarded.
 * 10		Auth/De auth - When set, the WiLink receives all authentication
 * 	 	and de-authentication frames. When clear, these frames are
 *		discarded.
 * 9		Beacon - When set, the WiLink receives all beacon frames.
 * 	 	When clear, these frames are discarded.
 * 8		Contention Free - When set, the WiLink receives all contention
 * 	 	मुक्त frames.
 *		When clear, these frames are discarded.
 * 7		Control - When set, the WiLink receives all control frames.
 * 	 	When clear, these frames are discarded.
 * 6		Data - When set, the WiLink receives all data frames.
 * 	 	When clear, these frames are discarded.
 * 5		FCS Error - When set, the WiLink receives frames that have FCS
 *	 	errors.
 *		When clear, these frames are discarded.
 * 4		Management - When set, the WiLink receives all management
 *		frames.
 * 	 	When clear, these frames are discarded.
 * 3		Probe Request - When set, the WiLink receives all probe request
 * 	 	frames.
 *		When clear, these frames are discarded.
 * 2		Probe Response - When set, the WiLink receives all probe
 * 		response frames.
 *		When clear, these frames are discarded.
 * 1		RTS/CTS/ACK - When set, the WiLink receives all RTS, CTS and ACK
 * 	 	frames.
 *		When clear, these frames are discarded.
 * 0		Rsvd Type/Sub Type - When set, the WiLink receives all frames
 * 	 	that have reserved frame types and sub types as defined by the
 *		802.11 specअगरication.
 *		When clear, these frames are discarded.
 */
काष्ठा acx_rx_config अणु
	काष्ठा acx_header header;

	u32 config_options;
	u32 filter_options;
पूर्ण __packed;

क्रमागत अणु
	QOS_AC_BE = 0,
	QOS_AC_BK,
	QOS_AC_VI,
	QOS_AC_VO,
	QOS_HIGHEST_AC_INDEX = QOS_AC_VO,
पूर्ण;

#घोषणा MAX_NUM_OF_AC             (QOS_HIGHEST_AC_INDEX+1)
#घोषणा FIRST_AC_INDEX            QOS_AC_BE
#घोषणा MAX_NUM_OF_802_1d_TAGS    8
#घोषणा AC_PARAMS_MAX_TSID        15
#घोषणा MAX_APSD_CONF             0xffff

#घोषणा  QOS_TX_HIGH_MIN      (0)
#घोषणा  QOS_TX_HIGH_MAX      (100)

#घोषणा  QOS_TX_HIGH_BK_DEF   (25)
#घोषणा  QOS_TX_HIGH_BE_DEF   (35)
#घोषणा  QOS_TX_HIGH_VI_DEF   (35)
#घोषणा  QOS_TX_HIGH_VO_DEF   (35)

#घोषणा  QOS_TX_LOW_BK_DEF    (15)
#घोषणा  QOS_TX_LOW_BE_DEF    (25)
#घोषणा  QOS_TX_LOW_VI_DEF    (25)
#घोषणा  QOS_TX_LOW_VO_DEF    (25)

काष्ठा acx_tx_queue_qos_config अणु
	काष्ठा acx_header header;

	u8 qid;
	u8 pad[3];

	/* Max number of blocks allowd in the queue */
	u16 high_threshold;

	/* Lowest memory blocks guaranteed क्रम this queue */
	u16 low_threshold;
पूर्ण __packed;

काष्ठा acx_packet_detection अणु
	काष्ठा acx_header header;

	u32 threshold;
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

	u8 wone_index; /* Reserved */
	u8 slot_समय;
	u8 reserved[6];
पूर्ण __packed;


#घोषणा ACX_MC_ADDRESS_GROUP_MAX	(8)
#घोषणा ACX_MC_ADDRESS_GROUP_MAX_LEN	(ETH_ALEN * ACX_MC_ADDRESS_GROUP_MAX)

काष्ठा acx_करोt11_grp_addr_tbl अणु
	काष्ठा acx_header header;

	u8 enabled;
	u8 num_groups;
	u8 pad[2];
	u8 mac_table[ACX_MC_ADDRESS_GROUP_MAX_LEN];
पूर्ण __packed;


#घोषणा  RX_TIMEOUT_PS_POLL_MIN    0
#घोषणा  RX_TIMEOUT_PS_POLL_MAX    (200000)
#घोषणा  RX_TIMEOUT_PS_POLL_DEF    (15)
#घोषणा  RX_TIMEOUT_UPSD_MIN       0
#घोषणा  RX_TIMEOUT_UPSD_MAX       (200000)
#घोषणा  RX_TIMEOUT_UPSD_DEF       (15)

काष्ठा acx_rx_समयout अणु
	काष्ठा acx_header header;

	/*
	 * The दीर्घest समय the STA will रुको to receive
	 * traffic from the AP after a PS-poll has been
	 * transmitted.
	 */
	u16 ps_poll_समयout;

	/*
	 * The दीर्घest समय the STA will रुको to receive
	 * traffic from the AP after a frame has been sent
	 * from an UPSD enabled queue.
	 */
	u16 upsd_समयout;
पूर्ण __packed;

#घोषणा RTS_THRESHOLD_MIN              0
#घोषणा RTS_THRESHOLD_MAX              4096
#घोषणा RTS_THRESHOLD_DEF              2347

काष्ठा acx_rts_threshold अणु
	काष्ठा acx_header header;

	u16 threshold;
	u8 pad[2];
पूर्ण __packed;

क्रमागत wl1251_acx_low_rssi_type अणु
	/*
	 * The event is a "Level" indication which keeps triggering
	 * as दीर्घ as the average RSSI is below the threshold.
	 */
	WL1251_ACX_LOW_RSSI_TYPE_LEVEL = 0,

	/*
	 * The event is an "Edge" indication which triggers
	 * only when the RSSI threshold is crossed from above.
	 */
	WL1251_ACX_LOW_RSSI_TYPE_EDGE = 1,
पूर्ण;

काष्ठा acx_low_rssi अणु
	काष्ठा acx_header header;

	/*
	 * The threshold (in dBm) below (or above after low rssi
	 * indication) which the firmware generates an पूर्णांकerrupt to the
	 * host. This parameter is चिन्हित.
	 */
	s8 threshold;

	/*
	 * The weight of the current RSSI sample, beक्रमe adding the new
	 * sample, that is used to calculate the average RSSI.
	 */
	u8 weight;

	/*
	 * The number of Beacons/Probe response frames that will be
	 * received beक्रमe issuing the Low or Regained RSSI event.
	 */
	u8 depth;

	/*
	 * Configures how the Low RSSI Event is triggered. Refer to
	 * क्रमागत wl1251_acx_low_rssi_type क्रम more.
	 */
	u8 type;
पूर्ण __packed;

काष्ठा acx_beacon_filter_option अणु
	काष्ठा acx_header header;

	u8 enable;

	/*
	 * The number of beacons without the unicast TIM
	 * bit set that the firmware buffers beक्रमe
	 * संकेतing the host about पढ़ोy frames.
	 * When set to 0 and the filter is enabled, beacons
	 * without the unicast TIM bit set are dropped.
	 */
	u8 max_num_beacons;
	u8 pad[2];
पूर्ण __packed;

/*
 * ACXBeaconFilterEntry (not 221)
 * Byte Offset     Size (Bytes)    Definition
 * ===========     ============    ==========
 * 0				1               IE identअगरier
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

#घोषणा BEACON_RULE_PASS_ON_CHANGE                     BIT(0)
#घोषणा BEACON_RULE_PASS_ON_APPEARANCE                 BIT(1)

#घोषणा BEACON_FILTER_IE_ID_CHANNEL_SWITCH_ANN         (37)

काष्ठा acx_beacon_filter_ie_table अणु
	काष्ठा acx_header header;

	u8 num_ie;
	u8 pad[3];
	u8 table[BEACON_FILTER_TABLE_MAX_SIZE];
पूर्ण __packed;

#घोषणा SYNCH_FAIL_DEFAULT_THRESHOLD    10     /* number of beacons */
#घोषणा NO_BEACON_DEFAULT_TIMEOUT       (500) /* in microseconds */

काष्ठा acx_conn_monit_params अणु
	काष्ठा acx_header header;

	u32 synch_fail_thold; /* number of beacons missed */
	u32 bss_lose_समयout; /* number of TU's from synch fail */
पूर्ण __packed;

क्रमागत अणु
	SG_ENABLE = 0,
	SG_DISABLE,
	SG_SENSE_NO_ACTIVITY,
	SG_SENSE_ACTIVE
पूर्ण;

काष्ठा acx_bt_wlan_coex अणु
	काष्ठा acx_header header;

	/*
	 * 0 -> PTA enabled
	 * 1 -> PTA disabled
	 * 2 -> sense no active mode, i.e.
	 *      an पूर्णांकerrupt is sent upon
	 *      BT activity.
	 * 3 -> PTA is चयनed on in response
	 *      to the पूर्णांकerrupt sending.
	 */
	u8 enable;
	u8 pad[3];
पूर्ण __packed;

#घोषणा PTA_ANTENNA_TYPE_DEF		  (0)
#घोषणा PTA_BT_HP_MAXTIME_DEF		  (2000)
#घोषणा PTA_WLAN_HP_MAX_TIME_DEF	  (5000)
#घोषणा PTA_SENSE_DISABLE_TIMER_DEF	  (1350)
#घोषणा PTA_PROTECTIVE_RX_TIME_DEF	  (1500)
#घोषणा PTA_PROTECTIVE_TX_TIME_DEF	  (1500)
#घोषणा PTA_TIMEOUT_NEXT_BT_LP_PACKET_DEF (3000)
#घोषणा PTA_SIGNALING_TYPE_DEF		  (1)
#घोषणा PTA_AFH_LEVERAGE_ON_DEF		  (0)
#घोषणा PTA_NUMBER_QUIET_CYCLE_DEF	  (0)
#घोषणा PTA_MAX_NUM_CTS_DEF		  (3)
#घोषणा PTA_NUMBER_OF_WLAN_PACKETS_DEF	  (2)
#घोषणा PTA_NUMBER_OF_BT_PACKETS_DEF	  (2)
#घोषणा PTA_PROTECTIVE_RX_TIME_FAST_DEF	  (1500)
#घोषणा PTA_PROTECTIVE_TX_TIME_FAST_DEF	  (3000)
#घोषणा PTA_CYCLE_TIME_FAST_DEF		  (8700)
#घोषणा PTA_RX_FOR_AVALANCHE_DEF	  (5)
#घोषणा PTA_ELP_HP_DEF			  (0)
#घोषणा PTA_ANTI_STARVE_PERIOD_DEF	  (500)
#घोषणा PTA_ANTI_STARVE_NUM_CYCLE_DEF	  (4)
#घोषणा PTA_ALLOW_PA_SD_DEF		  (1)
#घोषणा PTA_TIME_BEFORE_BEACON_DEF	  (6300)
#घोषणा PTA_HPDM_MAX_TIME_DEF		  (1600)
#घोषणा PTA_TIME_OUT_NEXT_WLAN_DEF	  (2550)
#घोषणा PTA_AUTO_MODE_NO_CTS_DEF	  (0)
#घोषणा PTA_BT_HP_RESPECTED_DEF		  (3)
#घोषणा PTA_WLAN_RX_MIN_RATE_DEF	  (24)
#घोषणा PTA_ACK_MODE_DEF		  (1)

काष्ठा acx_bt_wlan_coex_param अणु
	काष्ठा acx_header header;

	/*
	 * The minimum rate of a received WLAN packet in the STA,
	 * during protective mode, of which a new BT-HP request
	 * during this Rx will always be respected and gain the antenna.
	 */
	u32 min_rate;

	/* Max समय the BT HP will be respected. */
	u16 bt_hp_max_समय;

	/* Max समय the WLAN HP will be respected. */
	u16 wlan_hp_max_समय;

	/*
	 * The समय between the last BT activity
	 * and the moment when the sense mode वापसs
	 * to SENSE_INACTIVE.
	 */
	u16 sense_disable_समयr;

	/* Time beक्रमe the next BT HP instance */
	u16 rx_समय_bt_hp;
	u16 tx_समय_bt_hp;

	/* range: 10-20000    शेष: 1500 */
	u16 rx_समय_bt_hp_fast;
	u16 tx_समय_bt_hp_fast;

	/* range: 2000-65535  शेष: 8700 */
	u16 wlan_cycle_fast;

	/* range: 0 - 15000 (Msec) शेष: 1000 */
	u16 bt_anti_starvation_period;

	/* range 400-10000(Usec) शेष: 3000 */
	u16 next_bt_lp_packet;

	/* Deafult: worst हाल क्रम BT DH5 traffic */
	u16 wake_up_beacon;

	/* range: 0-50000(Usec) शेष: 1050 */
	u16 hp_dm_max_guard_समय;

	/*
	 * This is to prevent both BT & WLAN antenna
	 * starvation.
	 * Range: 100-50000(Usec) शेष:2550
	 */
	u16 next_wlan_packet;

	/* 0 -> shared antenna */
	u8 antenna_type;

	/*
	 * 0 -> TI legacy
	 * 1 -> Palau
	 */
	u8 संकेत_type;

	/*
	 * BT AFH status
	 * 0 -> no AFH
	 * 1 -> from dedicated GPIO
	 * 2 -> AFH on (from host)
	 */
	u8 afh_leverage_on;

	/*
	 * The number of cycles during which no
	 * TX will be sent after 1 cycle of RX
	 * transaction in protective mode
	 */
	u8 quiet_cycle_num;

	/*
	 * The maximum number of CTSs that will
	 * be sent क्रम receiving RX packet in
	 * protective mode
	 */
	u8 max_cts;

	/*
	 * The number of WLAN packets
	 * transferred in common mode beक्रमe
	 * चयनing to BT.
	 */
	u8 wlan_packets_num;

	/*
	 * The number of BT packets
	 * transferred in common mode beक्रमe
	 * चयनing to WLAN.
	 */
	u8 bt_packets_num;

	/* range: 1-255  शेष: 5 */
	u8 missed_rx_avalanche;

	/* range: 0-1    शेष: 1 */
	u8 wlan_elp_hp;

	/* range: 0 - 15  शेष: 4 */
	u8 bt_anti_starvation_cycles;

	u8 ack_mode_dual_ant;

	/*
	 * Allow PA_SD निश्चितion/de-निश्चितion
	 * during enabled BT activity.
	 */
	u8 pa_sd_enable;

	/*
	 * Enable/Disable PTA in स्वतः mode:
	 * Support Both Active & P.S modes
	 */
	u8 pta_स्वतः_mode_enable;

	/* range: 0 - 20  शेष: 1 */
	u8 bt_hp_respected_num;
पूर्ण __packed;

#घोषणा CCA_THRSH_ENABLE_ENERGY_D       0x140A
#घोषणा CCA_THRSH_DISABLE_ENERGY_D      0xFFEF

काष्ठा acx_energy_detection अणु
	काष्ठा acx_header header;

	/* The RX Clear Channel Assessment threshold in the PHY */
	u16 rx_cca_threshold;
	u8 tx_energy_detection;
	u8 pad;
पूर्ण __packed;

#घोषणा BCN_RX_TIMEOUT_DEF_VALUE        10000
#घोषणा BROADCAST_RX_TIMEOUT_DEF_VALUE  20000
#घोषणा RX_BROADCAST_IN_PS_DEF_VALUE    1
#घोषणा CONSECUTIVE_PS_POLL_FAILURE_DEF 4

काष्ठा acx_beacon_broadcast अणु
	काष्ठा acx_header header;

	u16 beacon_rx_समयout;
	u16 broadcast_समयout;

	/* Enables receiving of broadcast packets in PS mode */
	u8 rx_broadcast_in_ps;

	/* Consecutive PS Poll failures beक्रमe updating the host */
	u8 ps_poll_threshold;
	u8 pad[2];
पूर्ण __packed;

काष्ठा acx_event_mask अणु
	काष्ठा acx_header header;

	u32 event_mask;
	u32 high_event_mask; /* Unused */
पूर्ण __packed;

#घोषणा CFG_RX_FCS		BIT(2)
#घोषणा CFG_RX_ALL_GOOD		BIT(3)
#घोषणा CFG_UNI_FILTER_EN	BIT(4)
#घोषणा CFG_BSSID_FILTER_EN	BIT(5)
#घोषणा CFG_MC_FILTER_EN	BIT(6)
#घोषणा CFG_MC_ADDR0_EN		BIT(7)
#घोषणा CFG_MC_ADDR1_EN		BIT(8)
#घोषणा CFG_BC_REJECT_EN	BIT(9)
#घोषणा CFG_SSID_FILTER_EN	BIT(10)
#घोषणा CFG_RX_INT_FCS_ERROR	BIT(11)
#घोषणा CFG_RX_INT_ENCRYPTED	BIT(12)
#घोषणा CFG_RX_WR_RX_STATUS	BIT(13)
#घोषणा CFG_RX_FILTER_NULTI	BIT(14)
#घोषणा CFG_RX_RESERVE		BIT(15)
#घोषणा CFG_RX_TIMESTAMP_TSF	BIT(16)

#घोषणा CFG_RX_RSV_EN		BIT(0)
#घोषणा CFG_RX_RCTS_ACK		BIT(1)
#घोषणा CFG_RX_PRSP_EN		BIT(2)
#घोषणा CFG_RX_PREQ_EN		BIT(3)
#घोषणा CFG_RX_MGMT_EN		BIT(4)
#घोषणा CFG_RX_FCS_ERROR	BIT(5)
#घोषणा CFG_RX_DATA_EN		BIT(6)
#घोषणा CFG_RX_CTL_EN		BIT(7)
#घोषणा CFG_RX_CF_EN		BIT(8)
#घोषणा CFG_RX_BCN_EN		BIT(9)
#घोषणा CFG_RX_AUTH_EN		BIT(10)
#घोषणा CFG_RX_ASSOC_EN		BIT(11)

#घोषणा SCAN_PASSIVE		BIT(0)
#घोषणा SCAN_5GHZ_BAND		BIT(1)
#घोषणा SCAN_TRIGGERED		BIT(2)
#घोषणा SCAN_PRIORITY_HIGH	BIT(3)

काष्ठा acx_fw_gen_frame_rates अणु
	काष्ठा acx_header header;

	u8 tx_ctrl_frame_rate; /* RATE_* */
	u8 tx_ctrl_frame_mod; /* CCK_* or PBCC_* */
	u8 tx_mgt_frame_rate;
	u8 tx_mgt_frame_mod;
पूर्ण __packed;

/* STA MAC */
काष्ठा acx_करोt11_station_id अणु
	काष्ठा acx_header header;

	u8 mac[ETH_ALEN];
	u8 pad[2];
पूर्ण __packed;

काष्ठा acx_feature_config अणु
	काष्ठा acx_header header;

	u32 options;
	u32 data_flow_options;
पूर्ण __packed;

काष्ठा acx_current_tx_घातer अणु
	काष्ठा acx_header header;

	u8  current_tx_घातer;
	u8  padding[3];
पूर्ण __packed;

काष्ठा acx_करोt11_शेष_key अणु
	काष्ठा acx_header header;

	u8 id;
	u8 pad[3];
पूर्ण __packed;

काष्ठा acx_tsf_info अणु
	काष्ठा acx_header header;

	u32 current_tsf_msb;
	u32 current_tsf_lsb;
	u32 last_TBTT_msb;
	u32 last_TBTT_lsb;
	u8 last_dtim_count;
	u8 pad[3];
पूर्ण __packed;

क्रमागत acx_wake_up_event अणु
	WAKE_UP_EVENT_BEACON_BITMAP	= 0x01, /* Wake on every Beacon*/
	WAKE_UP_EVENT_DTIM_BITMAP	= 0x02,	/* Wake on every DTIM*/
	WAKE_UP_EVENT_N_DTIM_BITMAP	= 0x04, /* Wake on every Nth DTIM */
	WAKE_UP_EVENT_N_BEACONS_BITMAP	= 0x08, /* Wake on every Nth Beacon */
	WAKE_UP_EVENT_BITS_MASK		= 0x0F
पूर्ण;

काष्ठा acx_wake_up_condition अणु
	काष्ठा acx_header header;

	u8 wake_up_event; /* Only one bit can be set */
	u8 listen_पूर्णांकerval;
	u8 pad[2];
पूर्ण __packed;

काष्ठा acx_aid अणु
	काष्ठा acx_header header;

	/*
	 * To be set when associated with an AP.
	 */
	u16 aid;
	u8 pad[2];
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
	u8 preamble;
	u8 padding[3];
पूर्ण __packed;

क्रमागत acx_ctsprotect_type अणु
	CTSPROTECT_DISABLE = 0,
	CTSPROTECT_ENABLE = 1
पूर्ण;

काष्ठा acx_ctsprotect अणु
	काष्ठा acx_header header;
	u8 ctsprotect;
	u8 padding[3];
पूर्ण __packed;

काष्ठा acx_tx_statistics अणु
	u32 पूर्णांकernal_desc_overflow;
पूर्ण  __packed;

काष्ठा acx_rx_statistics अणु
	u32 out_of_mem;
	u32 hdr_overflow;
	u32 hw_stuck;
	u32 dropped;
	u32 fcs_err;
	u32 xfr_hपूर्णांक_trig;
	u32 path_reset;
	u32 reset_counter;
पूर्ण __packed;

काष्ठा acx_dma_statistics अणु
	u32 rx_requested;
	u32 rx_errors;
	u32 tx_requested;
	u32 tx_errors;
पूर्ण  __packed;

काष्ठा acx_isr_statistics अणु
	/* host command complete */
	u32 cmd_cmplt;

	/* fiqisr() */
	u32 fiqs;

	/* (INT_STS_ND & INT_TRIG_RX_HEADER) */
	u32 rx_headers;

	/* (INT_STS_ND & INT_TRIG_RX_CMPLT) */
	u32 rx_completes;

	/* (INT_STS_ND & INT_TRIG_NO_RX_BUF) */
	u32 rx_mem_overflow;

	/* (INT_STS_ND & INT_TRIG_S_RX_RDY) */
	u32 rx_rdys;

	/* irqisr() */
	u32 irqs;

	/* (INT_STS_ND & INT_TRIG_TX_PROC) */
	u32 tx_procs;

	/* (INT_STS_ND & INT_TRIG_DECRYPT_DONE) */
	u32 decrypt_करोne;

	/* (INT_STS_ND & INT_TRIG_DMA0) */
	u32 dma0_करोne;

	/* (INT_STS_ND & INT_TRIG_DMA1) */
	u32 dma1_करोne;

	/* (INT_STS_ND & INT_TRIG_TX_EXC_CMPLT) */
	u32 tx_exch_complete;

	/* (INT_STS_ND & INT_TRIG_COMMAND) */
	u32 commands;

	/* (INT_STS_ND & INT_TRIG_RX_PROC) */
	u32 rx_procs;

	/* (INT_STS_ND & INT_TRIG_PM_802) */
	u32 hw_pm_mode_changes;

	/* (INT_STS_ND & INT_TRIG_ACKNOWLEDGE) */
	u32 host_acknowledges;

	/* (INT_STS_ND & INT_TRIG_PM_PCI) */
	u32 pci_pm;

	/* (INT_STS_ND & INT_TRIG_ACM_WAKEUP) */
	u32 wakeups;

	/* (INT_STS_ND & INT_TRIG_LOW_RSSI) */
	u32 low_rssi;
पूर्ण __packed;

काष्ठा acx_wep_statistics अणु
	/* WEP address keys configured */
	u32 addr_key_count;

	/* शेष keys configured */
	u32 शेष_key_count;

	u32 reserved;

	/* number of बार that WEP key not found on lookup */
	u32 key_not_found;

	/* number of बार that WEP key decryption failed */
	u32 decrypt_fail;

	/* WEP packets decrypted */
	u32 packets;

	/* WEP decrypt पूर्णांकerrupts */
	u32 पूर्णांकerrupt;
पूर्ण __packed;

#घोषणा ACX_MISSED_BEACONS_SPREAD 10

काष्ठा acx_pwr_statistics अणु
	/* the amount of enters पूर्णांकo घातer save mode (both PD & ELP) */
	u32 ps_enter;

	/* the amount of enters पूर्णांकo ELP mode */
	u32 elp_enter;

	/* the amount of missing beacon पूर्णांकerrupts to the host */
	u32 missing_bcns;

	/* the amount of wake on host-access बार */
	u32 wake_on_host;

	/* the amount of wake on समयr-expire */
	u32 wake_on_समयr_exp;

	/* the number of packets that were transmitted with PS bit set */
	u32 tx_with_ps;

	/* the number of packets that were transmitted with PS bit clear */
	u32 tx_without_ps;

	/* the number of received beacons */
	u32 rcvd_beacons;

	/* the number of entering पूर्णांकo PowerOn (घातer save off) */
	u32 घातer_save_off;

	/* the number of entries पूर्णांकo घातer save mode */
	u16 enable_ps;

	/*
	 * the number of निकासs from घातer save, not including failed PS
	 * transitions
	 */
	u16 disable_ps;

	/*
	 * the number of बार the TSF counter was adjusted because
	 * of drअगरt
	 */
	u32 fix_tsf_ps;

	/* Gives statistics about the spपढ़ो continuous missed beacons.
	 * The 16 LSB are dedicated क्रम the PS mode.
	 * The 16 MSB are dedicated क्रम the PS mode.
	 * cont_miss_bcns_spपढ़ो[0] - single missed beacon.
	 * cont_miss_bcns_spपढ़ो[1] - two continuous missed beacons.
	 * cont_miss_bcns_spपढ़ो[2] - three continuous missed beacons.
	 * ...
	 * cont_miss_bcns_spपढ़ो[9] - ten and more continuous missed beacons.
	*/
	u32 cont_miss_bcns_spपढ़ो[ACX_MISSED_BEACONS_SPREAD];

	/* the number of beacons in awake mode */
	u32 rcvd_awake_beacons;
पूर्ण __packed;

काष्ठा acx_mic_statistics अणु
	u32 rx_pkts;
	u32 calc_failure;
पूर्ण __packed;

काष्ठा acx_aes_statistics अणु
	u32 encrypt_fail;
	u32 decrypt_fail;
	u32 encrypt_packets;
	u32 decrypt_packets;
	u32 encrypt_पूर्णांकerrupt;
	u32 decrypt_पूर्णांकerrupt;
पूर्ण __packed;

काष्ठा acx_event_statistics अणु
	u32 heart_beat;
	u32 calibration;
	u32 rx_mismatch;
	u32 rx_mem_empty;
	u32 rx_pool;
	u32 oom_late;
	u32 phy_transmit_error;
	u32 tx_stuck;
पूर्ण __packed;

काष्ठा acx_ps_statistics अणु
	u32 pspoll_समयouts;
	u32 upsd_समयouts;
	u32 upsd_max_spसमय;
	u32 upsd_max_apturn;
	u32 pspoll_max_apturn;
	u32 pspoll_utilization;
	u32 upsd_utilization;
पूर्ण __packed;

काष्ठा acx_rxpipe_statistics अणु
	u32 rx_prep_beacon_drop;
	u32 descr_host_पूर्णांक_trig_rx_data;
	u32 beacon_buffer_thres_host_पूर्णांक_trig_rx_data;
	u32 missed_beacon_host_पूर्णांक_trig_rx_data;
	u32 tx_xfr_host_पूर्णांक_trig_rx_data;
पूर्ण __packed;

काष्ठा acx_statistics अणु
	काष्ठा acx_header header;

	काष्ठा acx_tx_statistics tx;
	काष्ठा acx_rx_statistics rx;
	काष्ठा acx_dma_statistics dma;
	काष्ठा acx_isr_statistics isr;
	काष्ठा acx_wep_statistics wep;
	काष्ठा acx_pwr_statistics pwr;
	काष्ठा acx_aes_statistics aes;
	काष्ठा acx_mic_statistics mic;
	काष्ठा acx_event_statistics event;
	काष्ठा acx_ps_statistics ps;
	काष्ठा acx_rxpipe_statistics rxpipe;
पूर्ण __packed;

#घोषणा ACX_MAX_RATE_CLASSES       8
#घोषणा ACX_RATE_MASK_UNSPECIFIED  0
#घोषणा ACX_RATE_RETRY_LIMIT      10

काष्ठा acx_rate_class अणु
	u32 enabled_rates;
	u8 लघु_retry_limit;
	u8 दीर्घ_retry_limit;
	u8 aflags;
	u8 reserved;
पूर्ण __packed;

काष्ठा acx_rate_policy अणु
	काष्ठा acx_header header;

	u32 rate_class_cnt;
	काष्ठा acx_rate_class rate_class[ACX_MAX_RATE_CLASSES];
पूर्ण __packed;

काष्ठा wl1251_acx_memory अणु
	__le16 num_stations; /* number of STAs to be supported. */
	u16 reserved_1;

	/*
	 * Nmber of memory buffers क्रम the RX mem pool.
	 * The actual number may be less अगर there are
	 * not enough blocks left क्रम the minimum num
	 * of TX ones.
	 */
	u8 rx_mem_block_num;
	u8 reserved_2;
	u8 num_tx_queues; /* From 1 to 16 */
	u8 host_अगर_options; /* HOST_IF* */
	u8 tx_min_mem_block_num;
	u8 num_ssid_profiles;
	__le16 debug_buffer_size;
पूर्ण __packed;


#घोषणा ACX_RX_DESC_MIN                1
#घोषणा ACX_RX_DESC_MAX                127
#घोषणा ACX_RX_DESC_DEF                32
काष्ठा wl1251_acx_rx_queue_config अणु
	u8 num_descs;
	u8 pad;
	u8 type;
	u8 priority;
	__le32 dma_address;
पूर्ण __packed;

#घोषणा ACX_TX_DESC_MIN                1
#घोषणा ACX_TX_DESC_MAX                127
#घोषणा ACX_TX_DESC_DEF                16
काष्ठा wl1251_acx_tx_queue_config अणु
    u8 num_descs;
    u8 pad[2];
    u8 attributes;
पूर्ण __packed;

#घोषणा MAX_TX_QUEUE_CONFIGS 5
#घोषणा MAX_TX_QUEUES 4
काष्ठा wl1251_acx_config_memory अणु
	काष्ठा acx_header header;

	काष्ठा wl1251_acx_memory mem_config;
	काष्ठा wl1251_acx_rx_queue_config rx_queue_config;
	काष्ठा wl1251_acx_tx_queue_config tx_queue_config[MAX_TX_QUEUE_CONFIGS];
पूर्ण __packed;

काष्ठा wl1251_acx_mem_map अणु
	काष्ठा acx_header header;

	व्योम *code_start;
	व्योम *code_end;

	व्योम *wep_defkey_start;
	व्योम *wep_defkey_end;

	व्योम *sta_table_start;
	व्योम *sta_table_end;

	व्योम *packet_ढाँचा_start;
	व्योम *packet_ढाँचा_end;

	व्योम *queue_memory_start;
	व्योम *queue_memory_end;

	व्योम *packet_memory_pool_start;
	व्योम *packet_memory_pool_end;

	व्योम *debug_buffer1_start;
	व्योम *debug_buffer1_end;

	व्योम *debug_buffer2_start;
	व्योम *debug_buffer2_end;

	/* Number of blocks FW allocated क्रम TX packets */
	u32 num_tx_mem_blocks;

	/* Number of blocks FW allocated क्रम RX packets */
	u32 num_rx_mem_blocks;
पूर्ण __packed;


काष्ठा wl1251_acx_wr_tbtt_and_dtim अणु

	काष्ठा acx_header header;

	/* Time in TUs between two consecutive beacons */
	u16 tbtt;

	/*
	 * DTIM period
	 * For BSS: Number of TBTTs in a DTIM period (range: 1-10)
	 * For IBSS: value shall be set to 1
	*/
	u8  dtim;
	u8  padding;
पूर्ण __packed;

क्रमागत wl1251_acx_bet_mode अणु
	WL1251_ACX_BET_DISABLE = 0,
	WL1251_ACX_BET_ENABLE = 1,
पूर्ण;

काष्ठा wl1251_acx_bet_enable अणु
	काष्ठा acx_header header;

	/*
	 * Specअगरies अगर beacon early termination procedure is enabled or
	 * disabled, see क्रमागत wl1251_acx_bet_mode.
	 */
	u8 enable;

	/*
	 * Specअगरies the maximum number of consecutive beacons that may be
	 * early terminated. After this number is reached at least one full
	 * beacon must be correctly received in FW beक्रमe beacon ET
	 * resumes. Range 0 - 255.
	 */
	u8 max_consecutive;

	u8 padding[2];
पूर्ण __packed;

#घोषणा ACX_IPV4_VERSION 4
#घोषणा ACX_IPV6_VERSION 6
#घोषणा ACX_IPV4_ADDR_SIZE 4
काष्ठा wl1251_acx_arp_filter अणु
	काष्ठा acx_header header;
	u8 version;	/* The IP version: 4 - IPv4, 6 - IPv6.*/
	u8 enable;	/* 1 - ARP filtering is enabled, 0 - disabled */
	u8 padding[2];
	u8 address[16];	/* The IP address used to filter ARP packets.
			   ARP packets that करो not match this address are
			   dropped. When the IP Version is 4, the last 12
			   bytes of the the address are ignored. */
पूर्ण __attribute__((packed));

काष्ठा wl1251_acx_ac_cfg अणु
	काष्ठा acx_header header;

	/*
	 * Access Category - The TX queue's access category
	 * (refer to AccessCategory_क्रमागत)
	 */
	u8 ac;

	/*
	 * The contention winकरोw minimum size (in slots) क्रम
	 * the access class.
	 */
	u8 cw_min;

	/*
	 * The contention winकरोw maximum size (in slots) क्रम
	 * the access class.
	 */
	u16 cw_max;

	/* The AIF value (in slots) क्रम the access class. */
	u8 aअगरsn;

	u8 reserved;

	/* The TX Op Limit (in microseconds) क्रम the access class. */
	u16 txop_limit;
पूर्ण __packed;


क्रमागत wl1251_acx_channel_type अणु
	CHANNEL_TYPE_DCF	= 0,
	CHANNEL_TYPE_EDCF	= 1,
	CHANNEL_TYPE_HCCA	= 2,
पूर्ण;

क्रमागत wl1251_acx_ps_scheme अणु
	/* regular ps: simple sending of packets */
	WL1251_ACX_PS_SCHEME_LEGACY	= 0,

	/* sending a packet triggers a unscheduled apsd करोwnstream */
	WL1251_ACX_PS_SCHEME_UPSD_TRIGGER	= 1,

	/* a pspoll packet will be sent beक्रमe every data packet */
	WL1251_ACX_PS_SCHEME_LEGACY_PSPOLL	= 2,

	/* scheduled apsd mode */
	WL1251_ACX_PS_SCHEME_SAPSD		= 3,
पूर्ण;

क्रमागत wl1251_acx_ack_policy अणु
	WL1251_ACX_ACK_POLICY_LEGACY	= 0,
	WL1251_ACX_ACK_POLICY_NO_ACK	= 1,
	WL1251_ACX_ACK_POLICY_BLOCK	= 2,
पूर्ण;

काष्ठा wl1251_acx_tid_cfg अणु
	काष्ठा acx_header header;

	/* tx queue id number (0-7) */
	u8 queue;

	/* channel access type क्रम the queue, क्रमागत wl1251_acx_channel_type */
	u8 type;

	/* EDCA: ac index (0-3), HCCA: traffic stream id (8-15) */
	u8 tsid;

	/* ps scheme of the specअगरied queue, क्रमागत wl1251_acx_ps_scheme */
	u8 ps_scheme;

	/* the tx queue ack policy, क्रमागत wl1251_acx_ack_policy */
	u8 ack_policy;

	u8 padding[3];

	/* not supported */
	u32 apsdconf[2];
पूर्ण __packed;

/*************************************************************************

    Host Interrupt Register (WiLink -> Host)

**************************************************************************/

/* RX packet is पढ़ोy in Xfer buffer #0 */
#घोषणा WL1251_ACX_INTR_RX0_DATA      BIT(0)

/* TX result(s) are in the TX complete buffer */
#घोषणा WL1251_ACX_INTR_TX_RESULT	BIT(1)

/* OBSOLETE */
#घोषणा WL1251_ACX_INTR_TX_XFR		BIT(2)

/* RX packet is पढ़ोy in Xfer buffer #1 */
#घोषणा WL1251_ACX_INTR_RX1_DATA	BIT(3)

/* Event was entered to Event MBOX #A */
#घोषणा WL1251_ACX_INTR_EVENT_A		BIT(4)

/* Event was entered to Event MBOX #B */
#घोषणा WL1251_ACX_INTR_EVENT_B		BIT(5)

/* OBSOLETE */
#घोषणा WL1251_ACX_INTR_WAKE_ON_HOST	BIT(6)

/* Trace message on MBOX #A */
#घोषणा WL1251_ACX_INTR_TRACE_A		BIT(7)

/* Trace message on MBOX #B */
#घोषणा WL1251_ACX_INTR_TRACE_B		BIT(8)

/* Command processing completion */
#घोषणा WL1251_ACX_INTR_CMD_COMPLETE	BIT(9)

/* Init sequence is करोne */
#घोषणा WL1251_ACX_INTR_INIT_COMPLETE	BIT(14)

#घोषणा WL1251_ACX_INTR_ALL           0xFFFFFFFF

क्रमागत अणु
	ACX_WAKE_UP_CONDITIONS      = 0x0002,
	ACX_MEM_CFG                 = 0x0003,
	ACX_SLOT                    = 0x0004,
	ACX_QUEUE_HEAD              = 0x0005, /* क्रम MASTER mode only */
	ACX_AC_CFG                  = 0x0007,
	ACX_MEM_MAP                 = 0x0008,
	ACX_AID                     = 0x000A,
	ACX_RADIO_PARAM             = 0x000B, /* Not used */
	ACX_CFG                     = 0x000C, /* Not used */
	ACX_FW_REV                  = 0x000D,
	ACX_MEDIUM_USAGE            = 0x000F,
	ACX_RX_CFG                  = 0x0010,
	ACX_TX_QUEUE_CFG            = 0x0011, /* FIXME: only used by wl1251 */
	ACX_BSS_IN_PS               = 0x0012, /* क्रम AP only */
	ACX_STATISTICS              = 0x0013, /* Debug API */
	ACX_FEATURE_CFG             = 0x0015,
	ACX_MISC_CFG                = 0x0017, /* Not used */
	ACX_TID_CFG                 = 0x001A,
	ACX_BEACON_FILTER_OPT       = 0x001F,
	ACX_LOW_RSSI                = 0x0020,
	ACX_NOISE_HIST              = 0x0021,
	ACX_HDK_VERSION             = 0x0022, /* ??? */
	ACX_PD_THRESHOLD            = 0x0023,
	ACX_DATA_PATH_PARAMS        = 0x0024, /* WO */
	ACX_DATA_PATH_RESP_PARAMS   = 0x0024, /* RO */
	ACX_CCA_THRESHOLD           = 0x0025,
	ACX_EVENT_MBOX_MASK         = 0x0026,
#अगर_घोषित FW_RUNNING_AS_AP
	ACX_DTIM_PERIOD             = 0x0027, /* क्रम AP only */
#अन्यथा
	ACX_WR_TBTT_AND_DTIM        = 0x0027, /* STA only */
#पूर्ण_अगर
	ACX_ACI_OPTION_CFG          = 0x0029, /* OBSOLETE (क्रम 1251)*/
	ACX_GPIO_CFG                = 0x002A, /* Not used */
	ACX_GPIO_SET                = 0x002B, /* Not used */
	ACX_PM_CFG                  = 0x002C, /* To Be Documented */
	ACX_CONN_MONIT_PARAMS       = 0x002D,
	ACX_AVERAGE_RSSI            = 0x002E, /* Not used */
	ACX_CONS_TX_FAILURE         = 0x002F,
	ACX_BCN_DTIM_OPTIONS        = 0x0031,
	ACX_SG_ENABLE               = 0x0032,
	ACX_SG_CFG                  = 0x0033,
	ACX_ANTENNA_DIVERSITY_CFG   = 0x0035, /* To Be Documented */
	ACX_LOW_SNR		    = 0x0037, /* To Be Documented */
	ACX_BEACON_FILTER_TABLE     = 0x0038,
	ACX_ARP_IP_FILTER           = 0x0039,
	ACX_ROAMING_STATISTICS_TBL  = 0x003B,
	ACX_RATE_POLICY             = 0x003D,
	ACX_CTS_PROTECTION          = 0x003E,
	ACX_SLEEP_AUTH              = 0x003F,
	ACX_PREAMBLE_TYPE	    = 0x0040,
	ACX_ERROR_CNT               = 0x0041,
	ACX_FW_GEN_FRAME_RATES      = 0x0042,
	ACX_IBSS_FILTER		    = 0x0044,
	ACX_SERVICE_PERIOD_TIMEOUT  = 0x0045,
	ACX_TSF_INFO                = 0x0046,
	ACX_CONFIG_PS_WMM           = 0x0049,
	ACX_ENABLE_RX_DATA_FILTER   = 0x004A,
	ACX_SET_RX_DATA_FILTER      = 0x004B,
	ACX_GET_DATA_FILTER_STATISTICS = 0x004C,
	ACX_POWER_LEVEL_TABLE       = 0x004D,
	ACX_BET_ENABLE              = 0x0050,
	DOT11_STATION_ID            = 0x1001,
	DOT11_RX_MSDU_LIFE_TIME     = 0x1004,
	DOT11_CUR_TX_PWR            = 0x100D,
	DOT11_DEFAULT_KEY           = 0x1010,
	DOT11_RX_DOT11_MODE         = 0x1012,
	DOT11_RTS_THRESHOLD         = 0x1013,
	DOT11_GROUP_ADDRESS_TBL     = 0x1014,

	MAX_DOT11_IE = DOT11_GROUP_ADDRESS_TBL,

	MAX_IE = 0xFFFF
पूर्ण;


पूर्णांक wl1251_acx_frame_rates(काष्ठा wl1251 *wl, u8 ctrl_rate, u8 ctrl_mod,
			   u8 mgt_rate, u8 mgt_mod);
पूर्णांक wl1251_acx_station_id(काष्ठा wl1251 *wl);
पूर्णांक wl1251_acx_शेष_key(काष्ठा wl1251 *wl, u8 key_id);
पूर्णांक wl1251_acx_wake_up_conditions(काष्ठा wl1251 *wl, u8 wake_up_event,
				  u8 listen_पूर्णांकerval);
पूर्णांक wl1251_acx_sleep_auth(काष्ठा wl1251 *wl, u8 sleep_auth);
पूर्णांक wl1251_acx_fw_version(काष्ठा wl1251 *wl, अक्षर *buf, माप_प्रकार len);
पूर्णांक wl1251_acx_tx_घातer(काष्ठा wl1251 *wl, पूर्णांक घातer);
पूर्णांक wl1251_acx_feature_cfg(काष्ठा wl1251 *wl, u32 data_flow_options);
पूर्णांक wl1251_acx_mem_map(काष्ठा wl1251 *wl,
		       काष्ठा acx_header *mem_map, माप_प्रकार len);
पूर्णांक wl1251_acx_data_path_params(काष्ठा wl1251 *wl,
				काष्ठा acx_data_path_params_resp *data_path);
पूर्णांक wl1251_acx_rx_msdu_lअगरe_समय(काष्ठा wl1251 *wl, u32 lअगरe_समय);
पूर्णांक wl1251_acx_rx_config(काष्ठा wl1251 *wl, u32 config, u32 filter);
पूर्णांक wl1251_acx_pd_threshold(काष्ठा wl1251 *wl);
पूर्णांक wl1251_acx_slot(काष्ठा wl1251 *wl, क्रमागत acx_slot_type slot_समय);
पूर्णांक wl1251_acx_group_address_tbl(काष्ठा wl1251 *wl, bool enable,
				 व्योम *mc_list, u32 mc_list_len);
पूर्णांक wl1251_acx_service_period_समयout(काष्ठा wl1251 *wl);
पूर्णांक wl1251_acx_rts_threshold(काष्ठा wl1251 *wl, u16 rts_threshold);
पूर्णांक wl1251_acx_beacon_filter_opt(काष्ठा wl1251 *wl, bool enable_filter);
पूर्णांक wl1251_acx_beacon_filter_table(काष्ठा wl1251 *wl);
पूर्णांक wl1251_acx_conn_monit_params(काष्ठा wl1251 *wl);
पूर्णांक wl1251_acx_sg_enable(काष्ठा wl1251 *wl);
पूर्णांक wl1251_acx_sg_cfg(काष्ठा wl1251 *wl);
पूर्णांक wl1251_acx_cca_threshold(काष्ठा wl1251 *wl);
पूर्णांक wl1251_acx_bcn_dtim_options(काष्ठा wl1251 *wl);
पूर्णांक wl1251_acx_aid(काष्ठा wl1251 *wl, u16 aid);
पूर्णांक wl1251_acx_event_mbox_mask(काष्ठा wl1251 *wl, u32 event_mask);
पूर्णांक wl1251_acx_low_rssi(काष्ठा wl1251 *wl, s8 threshold, u8 weight,
			u8 depth, क्रमागत wl1251_acx_low_rssi_type type);
पूर्णांक wl1251_acx_set_preamble(काष्ठा wl1251 *wl, क्रमागत acx_preamble_type preamble);
पूर्णांक wl1251_acx_cts_protect(काष्ठा wl1251 *wl,
			    क्रमागत acx_ctsprotect_type ctsprotect);
पूर्णांक wl1251_acx_statistics(काष्ठा wl1251 *wl, काष्ठा acx_statistics *stats);
पूर्णांक wl1251_acx_tsf_info(काष्ठा wl1251 *wl, u64 *maस_समय);
पूर्णांक wl1251_acx_rate_policies(काष्ठा wl1251 *wl);
पूर्णांक wl1251_acx_mem_cfg(काष्ठा wl1251 *wl);
पूर्णांक wl1251_acx_wr_tbtt_and_dtim(काष्ठा wl1251 *wl, u16 tbtt, u8 dtim);
पूर्णांक wl1251_acx_bet_enable(काष्ठा wl1251 *wl, क्रमागत wl1251_acx_bet_mode mode,
			  u8 max_consecutive);
पूर्णांक wl1251_acx_arp_ip_filter(काष्ठा wl1251 *wl, bool enable, __be32 address);
पूर्णांक wl1251_acx_ac_cfg(काष्ठा wl1251 *wl, u8 ac, u8 cw_min, u16 cw_max,
		      u8 aअगरs, u16 txop);
पूर्णांक wl1251_acx_tid_cfg(काष्ठा wl1251 *wl, u8 queue,
		       क्रमागत wl1251_acx_channel_type type,
		       u8 tsid, क्रमागत wl1251_acx_ps_scheme ps_scheme,
		       क्रमागत wl1251_acx_ack_policy ack_policy);

#पूर्ण_अगर /* __WL1251_ACX_H__ */
