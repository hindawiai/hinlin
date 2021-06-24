<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_mac_h__
#घोषणा __iwl_fw_api_mac_h__

/*
 * The first MAC indices (starting from 0) are available to the driver,
 * AUX indices follows - 1 क्रम non-CDB, 2 क्रम CDB.
 */
#घोषणा MAC_INDEX_AUX		4
#घोषणा MAC_INDEX_MIN_DRIVER	0
#घोषणा NUM_MAC_INDEX_DRIVER	MAC_INDEX_AUX
#घोषणा NUM_MAC_INDEX		(NUM_MAC_INDEX_DRIVER + 1)
#घोषणा NUM_MAC_INDEX_CDB	(NUM_MAC_INDEX_DRIVER + 2)

#घोषणा IWL_MVM_STATION_COUNT_MAX	16
#घोषणा IWL_MVM_INVALID_STA		0xFF

क्रमागत iwl_ac अणु
	AC_BK,
	AC_BE,
	AC_VI,
	AC_VO,
	AC_NUM,
पूर्ण;

/**
 * क्रमागत iwl_mac_protection_flags - MAC context flags
 * @MAC_PROT_FLG_TGG_PROTECT: 11g protection when transmitting OFDM frames,
 *	this will require CCK RTS/CTS2self.
 *	RTS/CTS will protect full burst समय.
 * @MAC_PROT_FLG_HT_PROT: enable HT protection
 * @MAC_PROT_FLG_FAT_PROT: protect 40 MHz transmissions
 * @MAC_PROT_FLG_SELF_CTS_EN: allow CTS2self
 */
क्रमागत iwl_mac_protection_flags अणु
	MAC_PROT_FLG_TGG_PROTECT	= BIT(3),
	MAC_PROT_FLG_HT_PROT		= BIT(23),
	MAC_PROT_FLG_FAT_PROT		= BIT(24),
	MAC_PROT_FLG_SELF_CTS_EN	= BIT(30),
पूर्ण;

#घोषणा MAC_FLG_SHORT_SLOT		BIT(4)
#घोषणा MAC_FLG_SHORT_PREAMBLE		BIT(5)

/**
 * क्रमागत iwl_mac_types - Supported MAC types
 * @FW_MAC_TYPE_FIRST: lowest supported MAC type
 * @FW_MAC_TYPE_AUX: Auxiliary MAC (पूर्णांकernal)
 * @FW_MAC_TYPE_LISTENER: monitor MAC type (?)
 * @FW_MAC_TYPE_PIBSS: Pseuकरो-IBSS
 * @FW_MAC_TYPE_IBSS: IBSS
 * @FW_MAC_TYPE_BSS_STA: BSS (managed) station
 * @FW_MAC_TYPE_P2P_DEVICE: P2P Device
 * @FW_MAC_TYPE_P2P_STA: P2P client
 * @FW_MAC_TYPE_GO: P2P GO
 * @FW_MAC_TYPE_TEST: ?
 * @FW_MAC_TYPE_MAX: highest support MAC type
 */
क्रमागत iwl_mac_types अणु
	FW_MAC_TYPE_FIRST = 1,
	FW_MAC_TYPE_AUX = FW_MAC_TYPE_FIRST,
	FW_MAC_TYPE_LISTENER,
	FW_MAC_TYPE_PIBSS,
	FW_MAC_TYPE_IBSS,
	FW_MAC_TYPE_BSS_STA,
	FW_MAC_TYPE_P2P_DEVICE,
	FW_MAC_TYPE_P2P_STA,
	FW_MAC_TYPE_GO,
	FW_MAC_TYPE_TEST,
	FW_MAC_TYPE_MAX = FW_MAC_TYPE_TEST
पूर्ण; /* MAC_CONTEXT_TYPE_API_E_VER_1 */

/**
 * क्रमागत iwl_tsf_id - TSF hw समयr ID
 * @TSF_ID_A: use TSF A
 * @TSF_ID_B: use TSF B
 * @TSF_ID_C: use TSF C
 * @TSF_ID_D: use TSF D
 * @NUM_TSF_IDS: number of TSF समयrs available
 */
क्रमागत iwl_tsf_id अणु
	TSF_ID_A = 0,
	TSF_ID_B = 1,
	TSF_ID_C = 2,
	TSF_ID_D = 3,
	NUM_TSF_IDS = 4,
पूर्ण; /* TSF_ID_API_E_VER_1 */

/**
 * काष्ठा iwl_mac_data_ap - configuration data क्रम AP MAC context
 * @beacon_समय: beacon transmit समय in प्रणाली समय
 * @beacon_tsf: beacon transmit समय in TSF
 * @bi: beacon पूर्णांकerval in TU
 * @reserved1: reserved
 * @dtim_पूर्णांकerval: dtim transmit समय in TU
 * @reserved2: reserved
 * @mcast_qid: queue ID क्रम multicast traffic.
 *	NOTE: obsolete from VER2 and on
 * @beacon_ढाँचा: beacon ढाँचा ID
 */
काष्ठा iwl_mac_data_ap अणु
	__le32 beacon_समय;
	__le64 beacon_tsf;
	__le32 bi;
	__le32 reserved1;
	__le32 dtim_पूर्णांकerval;
	__le32 reserved2;
	__le32 mcast_qid;
	__le32 beacon_ढाँचा;
पूर्ण __packed; /* AP_MAC_DATA_API_S_VER_2 */

/**
 * काष्ठा iwl_mac_data_ibss - configuration data क्रम IBSS MAC context
 * @beacon_समय: beacon transmit समय in प्रणाली समय
 * @beacon_tsf: beacon transmit समय in TSF
 * @bi: beacon पूर्णांकerval in TU
 * @reserved: reserved
 * @beacon_ढाँचा: beacon ढाँचा ID
 */
काष्ठा iwl_mac_data_ibss अणु
	__le32 beacon_समय;
	__le64 beacon_tsf;
	__le32 bi;
	__le32 reserved;
	__le32 beacon_ढाँचा;
पूर्ण __packed; /* IBSS_MAC_DATA_API_S_VER_1 */

/**
 * क्रमागत iwl_mac_data_policy - policy of the data path क्रम this MAC
 * @TWT_SUPPORTED: twt is supported
 * @MORE_DATA_ACK_SUPPORTED: AP supports More Data Ack according to
 *	paragraph 9.4.1.17 in P802.11ax_D4 specअगरication. Used क्रम TWT
 *	early termination detection.
 * @FLEXIBLE_TWT_SUPPORTED: AP supports flexible TWT schedule
 * @PROTECTED_TWT_SUPPORTED: AP supports रक्षित TWT frames (with 11w)
 */
क्रमागत iwl_mac_data_policy अणु
	TWT_SUPPORTED = BIT(0),
	MORE_DATA_ACK_SUPPORTED = BIT(1),
	FLEXIBLE_TWT_SUPPORTED = BIT(2),
	PROTECTED_TWT_SUPPORTED = BIT(3),
पूर्ण;

/**
 * काष्ठा iwl_mac_data_sta - configuration data क्रम station MAC context
 * @is_assoc: 1 क्रम associated state, 0 otherwise
 * @dtim_समय: DTIM arrival समय in प्रणाली समय
 * @dtim_tsf: DTIM arrival समय in TSF
 * @bi: beacon पूर्णांकerval in TU, applicable only when associated
 * @reserved1: reserved
 * @dtim_पूर्णांकerval: DTIM पूर्णांकerval in TU, applicable only when associated
 * @data_policy: see &क्रमागत iwl_mac_data_policy
 * @listen_पूर्णांकerval: in beacon पूर्णांकervals, applicable only when associated
 * @assoc_id: unique ID asचिन्हित by the AP during association
 * @assoc_beacon_arrive_समय: TSF of first beacon after association
 */
काष्ठा iwl_mac_data_sta अणु
	__le32 is_assoc;
	__le32 dtim_समय;
	__le64 dtim_tsf;
	__le32 bi;
	__le32 reserved1;
	__le32 dtim_पूर्णांकerval;
	__le32 data_policy;
	__le32 listen_पूर्णांकerval;
	__le32 assoc_id;
	__le32 assoc_beacon_arrive_समय;
पूर्ण __packed; /* STA_MAC_DATA_API_S_VER_2 */

/**
 * काष्ठा iwl_mac_data_go - configuration data क्रम P2P GO MAC context
 * @ap: iwl_mac_data_ap काष्ठा with most config data
 * @ctwin: client traffic winकरोw in TU (period after TBTT when GO is present).
 *	0 indicates that there is no CT winकरोw.
 * @opp_ps_enabled: indicate that opportunistic PS allowed
 */
काष्ठा iwl_mac_data_go अणु
	काष्ठा iwl_mac_data_ap ap;
	__le32 ctwin;
	__le32 opp_ps_enabled;
पूर्ण __packed; /* GO_MAC_DATA_API_S_VER_1 */

/**
 * काष्ठा iwl_mac_data_p2p_sta - configuration data क्रम P2P client MAC context
 * @sta: iwl_mac_data_sta काष्ठा with most config data
 * @ctwin: client traffic winकरोw in TU (period after TBTT when GO is present).
 *	0 indicates that there is no CT winकरोw.
 */
काष्ठा iwl_mac_data_p2p_sta अणु
	काष्ठा iwl_mac_data_sta sta;
	__le32 ctwin;
पूर्ण __packed; /* P2P_STA_MAC_DATA_API_S_VER_2 */

/**
 * काष्ठा iwl_mac_data_pibss - Pseuकरो IBSS config data
 * @stats_पूर्णांकerval: पूर्णांकerval in TU between statistics notअगरications to host.
 */
काष्ठा iwl_mac_data_pibss अणु
	__le32 stats_पूर्णांकerval;
पूर्ण __packed; /* PIBSS_MAC_DATA_API_S_VER_1 */

/*
 * काष्ठा iwl_mac_data_p2p_dev - configuration data क्रम the P2P Device MAC
 * context.
 * @is_disc_extended: अगर set to true, P2P Device discoverability is enabled on
 *	other channels as well. This should be to true only in हाल that the
 *	device is discoverable and there is an active GO. Note that setting this
 *	field when not needed, will increase the number of पूर्णांकerrupts and have
 *	effect on the platक्रमm घातer, as this setting खोलोs the Rx filters on
 *	all macs.
 */
काष्ठा iwl_mac_data_p2p_dev अणु
	__le32 is_disc_extended;
पूर्ण __packed; /* _P2P_DEV_MAC_DATA_API_S_VER_1 */

/**
 * क्रमागत iwl_mac_filter_flags - MAC context filter flags
 * @MAC_FILTER_IN_PROMISC: accept all data frames
 * @MAC_FILTER_IN_CONTROL_AND_MGMT: pass all management and
 *	control frames to the host
 * @MAC_FILTER_ACCEPT_GRP: accept multicast frames
 * @MAC_FILTER_DIS_DECRYPT: करोn't decrypt unicast frames
 * @MAC_FILTER_DIS_GRP_DECRYPT: करोn't decrypt multicast frames
 * @MAC_FILTER_IN_BEACON: transfer क्रमeign BSS's beacons to host
 *	(in station mode when associated)
 * @MAC_FILTER_OUT_BCAST: filter out all broadcast frames
 * @MAC_FILTER_IN_CRC32: extract FCS and append it to frames
 * @MAC_FILTER_IN_PROBE_REQUEST: pass probe requests to host
 */
क्रमागत iwl_mac_filter_flags अणु
	MAC_FILTER_IN_PROMISC		= BIT(0),
	MAC_FILTER_IN_CONTROL_AND_MGMT	= BIT(1),
	MAC_FILTER_ACCEPT_GRP		= BIT(2),
	MAC_FILTER_DIS_DECRYPT		= BIT(3),
	MAC_FILTER_DIS_GRP_DECRYPT	= BIT(4),
	MAC_FILTER_IN_BEACON		= BIT(6),
	MAC_FILTER_OUT_BCAST		= BIT(8),
	MAC_FILTER_IN_CRC32		= BIT(11),
	MAC_FILTER_IN_PROBE_REQUEST	= BIT(12),
	/**
	 * @MAC_FILTER_IN_11AX: mark BSS as supporting 802.11ax
	 */
	MAC_FILTER_IN_11AX		= BIT(14),
पूर्ण;

/**
 * क्रमागत iwl_mac_qos_flags - QoS flags
 * @MAC_QOS_FLG_UPDATE_EDCA: ?
 * @MAC_QOS_FLG_TGN: HT is enabled
 * @MAC_QOS_FLG_TXOP_TYPE: ?
 *
 */
क्रमागत iwl_mac_qos_flags अणु
	MAC_QOS_FLG_UPDATE_EDCA	= BIT(0),
	MAC_QOS_FLG_TGN		= BIT(1),
	MAC_QOS_FLG_TXOP_TYPE	= BIT(4),
पूर्ण;

/**
 * काष्ठा iwl_ac_qos - QOS timing params क्रम MAC_CONTEXT_CMD
 * @cw_min: Contention winकरोw, start value in numbers of slots.
 *	Should be a घातer-of-2, minus 1.  Device's शेष is 0x0f.
 * @cw_max: Contention winकरोw, max value in numbers of slots.
 *	Should be a घातer-of-2, minus 1.  Device's शेष is 0x3f.
 * @aअगरsn:  Number of slots in Arbitration Interframe Space (beक्रमe
 *	perक्रमming अक्रमom backoff timing prior to Tx).  Device शेष 1.
 * @fअगरos_mask: FIFOs used by this MAC क्रम this AC
 * @edca_txop:  Length of Tx opportunity, in uSecs.  Device शेष is 0.
 *
 * One instance of this config काष्ठा क्रम each of 4 EDCA access categories
 * in काष्ठा iwl_qosparam_cmd.
 *
 * Device will स्वतःmatically increase contention winकरोw by (2*CW) + 1 क्रम each
 * transmission retry.  Device uses cw_max as a bit mask, ANDed with new CW
 * value, to cap the CW value.
 */
काष्ठा iwl_ac_qos अणु
	__le16 cw_min;
	__le16 cw_max;
	u8 aअगरsn;
	u8 fअगरos_mask;
	__le16 edca_txop;
पूर्ण __packed; /* AC_QOS_API_S_VER_2 */

/**
 * काष्ठा iwl_mac_ctx_cmd - command काष्ठाure to configure MAC contexts
 * ( MAC_CONTEXT_CMD = 0x28 )
 * @id_and_color: ID and color of the MAC
 * @action: action to perक्रमm, one of FW_CTXT_ACTION_*
 * @mac_type: one of &क्रमागत iwl_mac_types
 * @tsf_id: TSF HW समयr, one of &क्रमागत iwl_tsf_id
 * @node_addr: MAC address
 * @reserved_क्रम_node_addr: reserved
 * @bssid_addr: BSSID
 * @reserved_क्रम_bssid_addr: reserved
 * @cck_rates: basic rates available क्रम CCK
 * @ofdm_rates: basic rates available क्रम OFDM
 * @protection_flags: combination of &क्रमागत iwl_mac_protection_flags
 * @cck_लघु_preamble: 0x20 क्रम enabling लघु preamble, 0 otherwise
 * @लघु_slot: 0x10 क्रम enabling लघु slots, 0 otherwise
 * @filter_flags: combination of &क्रमागत iwl_mac_filter_flags
 * @qos_flags: from &क्रमागत iwl_mac_qos_flags
 * @ac: one iwl_mac_qos configuration क्रम each AC
 */
काष्ठा iwl_mac_ctx_cmd अणु
	/* COMMON_INDEX_HDR_API_S_VER_1 */
	__le32 id_and_color;
	__le32 action;
	/* MAC_CONTEXT_COMMON_DATA_API_S_VER_1 */
	__le32 mac_type;
	__le32 tsf_id;
	u8 node_addr[6];
	__le16 reserved_क्रम_node_addr;
	u8 bssid_addr[6];
	__le16 reserved_क्रम_bssid_addr;
	__le32 cck_rates;
	__le32 ofdm_rates;
	__le32 protection_flags;
	__le32 cck_लघु_preamble;
	__le32 लघु_slot;
	__le32 filter_flags;
	/* MAC_QOS_PARAM_API_S_VER_1 */
	__le32 qos_flags;
	काष्ठा iwl_ac_qos ac[AC_NUM+1];
	/* MAC_CONTEXT_COMMON_DATA_API_S */
	जोड़ अणु
		काष्ठा iwl_mac_data_ap ap;
		काष्ठा iwl_mac_data_go go;
		काष्ठा iwl_mac_data_sta sta;
		काष्ठा iwl_mac_data_p2p_sta p2p_sta;
		काष्ठा iwl_mac_data_p2p_dev p2p_dev;
		काष्ठा iwl_mac_data_pibss pibss;
		काष्ठा iwl_mac_data_ibss ibss;
	पूर्ण;
पूर्ण __packed; /* MAC_CONTEXT_CMD_API_S_VER_1 */

#घोषणा IWL_NONQOS_SEQ_GET	0x1
#घोषणा IWL_NONQOS_SEQ_SET	0x2
काष्ठा iwl_nonqos_seq_query_cmd अणु
	__le32 get_set_flag;
	__le32 mac_id_n_color;
	__le16 value;
	__le16 reserved;
पूर्ण __packed; /* NON_QOS_TX_COUNTER_GET_SET_API_S_VER_1 */

/**
 * काष्ठा iwl_missed_beacons_notअगर - inक्रमmation on missed beacons
 * ( MISSED_BEACONS_NOTIFICATION = 0xa2 )
 * @mac_id: पूर्णांकerface ID
 * @consec_missed_beacons_since_last_rx: number of consecutive missed
 *	beacons since last RX.
 * @consec_missed_beacons: number of consecutive missed beacons
 * @num_expected_beacons: number of expected beacons
 * @num_recvd_beacons: number of received beacons
 */
काष्ठा iwl_missed_beacons_notअगर अणु
	__le32 mac_id;
	__le32 consec_missed_beacons_since_last_rx;
	__le32 consec_missed_beacons;
	__le32 num_expected_beacons;
	__le32 num_recvd_beacons;
पूर्ण __packed; /* MISSED_BEACON_NTFY_API_S_VER_3 */

/**
 * काष्ठा iwl_he_backoff_conf - used क्रम backoff configuration
 * Per each trigger-based AC, (set by MU EDCA Parameter set info-element)
 * used क्रम backoff configuration of TXF5..TXF8 trigger based.
 * The MU-TIMER is reloaded w/ MU_TIME each समय a frame from the AC is sent via
 * trigger-based TX.
 * @cwmin: CW min
 * @cwmax: CW max
 * @aअगरsn: AIFSN
 *	AIFSN=0, means that no backoff from the specअगरied TRIG-BASED AC is
 *	allowed till the MU-TIMER is 0
 * @mu_समय: MU समय in 8TU units
 */
काष्ठा iwl_he_backoff_conf अणु
	__le16 cwmin;
	__le16 cwmax;
	__le16 aअगरsn;
	__le16 mu_समय;
पूर्ण __packed; /* AC_QOS_DOT11AX_API_S */

/**
 * क्रमागत iwl_he_pkt_ext_स्थिरellations - PPE स्थिरellation indices
 * @IWL_HE_PKT_EXT_BPSK: BPSK
 * @IWL_HE_PKT_EXT_QPSK:  QPSK
 * @IWL_HE_PKT_EXT_16QAM: 16-QAM
 * @IWL_HE_PKT_EXT_64QAM: 64-QAM
 * @IWL_HE_PKT_EXT_256QAM: 256-QAM
 * @IWL_HE_PKT_EXT_1024QAM: 1024-QAM
 * @IWL_HE_PKT_EXT_RESERVED: reserved value
 * @IWL_HE_PKT_EXT_NONE: not defined
 */
क्रमागत iwl_he_pkt_ext_स्थिरellations अणु
	IWL_HE_PKT_EXT_BPSK = 0,
	IWL_HE_PKT_EXT_QPSK,
	IWL_HE_PKT_EXT_16QAM,
	IWL_HE_PKT_EXT_64QAM,
	IWL_HE_PKT_EXT_256QAM,
	IWL_HE_PKT_EXT_1024QAM,
	IWL_HE_PKT_EXT_RESERVED,
	IWL_HE_PKT_EXT_NONE,
पूर्ण;

#घोषणा MAX_HE_SUPP_NSS	2
#घोषणा MAX_HE_CHANNEL_BW_INDX	4

/**
 * काष्ठा iwl_he_pkt_ext - QAM thresholds
 * The required PPE is set via HE Capabilities IE, per Nss x BW x MCS
 * The IE is organized in the following way:
 * Support क्रम Nss x BW (or RU) matrix:
 *	(0=SISO, 1=MIMO2) x (0-20MHz, 1-40MHz, 2-80MHz, 3-160MHz)
 * Each entry contains 2 QAM thresholds क्रम 8us and 16us:
 *	0=BPSK, 1=QPSK, 2=16QAM, 3=64QAM, 4=256QAM, 5=1024QAM, 6=RES, 7=NONE
 * i.e. QAM_th1 < QAM_th2 such अगर TX uses QAM_tx:
 *	QAM_tx < QAM_th1            --> PPE=0us
 *	QAM_th1 <= QAM_tx < QAM_th2 --> PPE=8us
 *	QAM_th2 <= QAM_tx           --> PPE=16us
 * @pkt_ext_qam_th: QAM thresholds
 *	For each Nss/Bw define 2 QAM thrsholds (0..5)
 *	For rates below the low_th, no need क्रम PPE
 *	For rates between low_th and high_th, need 8us PPE
 *	For rates equal or higher then the high_th, need 16us PPE
 *	Nss (0-siso, 1-mimo2) x BW (0-20MHz, 1-40MHz, 2-80MHz, 3-160MHz) x
 *		(0-low_th, 1-high_th)
 */
काष्ठा iwl_he_pkt_ext अणु
	u8 pkt_ext_qam_th[MAX_HE_SUPP_NSS][MAX_HE_CHANNEL_BW_INDX][2];
पूर्ण __packed; /* PKT_EXT_DOT11AX_API_S */

/**
 * क्रमागत iwl_he_sta_ctxt_flags - HE STA context flags
 * @STA_CTXT_HE_REF_BSSID_VALID: ref bssid addr valid (क्रम receiving specअगरic
 *	control frames such as TRIG, NDPA, BACK)
 * @STA_CTXT_HE_BSS_COLOR_DIS: BSS color disable, करोn't use the BSS
 *	color क्रम RX filter but use MAC header
 * @STA_CTXT_HE_PARTIAL_BSS_COLOR: partial BSS color allocation
 * @STA_CTXT_HE_32BIT_BA_BITMAP: indicates the receiver supports BA biपंचांगap
 *	of 32-bits
 * @STA_CTXT_HE_PACKET_EXT: indicates that the packet-extension info is valid
 *	and should be used
 * @STA_CTXT_HE_TRIG_RND_ALLOC: indicates that trigger based अक्रमom allocation
 *	is enabled according to UORA element existence
 * @STA_CTXT_HE_CONST_TRIG_RND_ALLOC: used क्रम AV testing
 * @STA_CTXT_HE_ACK_ENABLED: indicates that the AP supports receiving ACK-
 *	enabled AGG, i.e. both BACK and non-BACK frames in a single AGG
 * @STA_CTXT_HE_MU_EDCA_CW: indicates that there is an element of MU EDCA
 *	parameter set, i.e. the backoff counters क्रम trig-based ACs
 * @STA_CTXT_HE_NIC_NOT_ACK_ENABLED: mark that the NIC करोesn't support receiving
 *	ACK-enabled AGG, (i.e. both BACK and non-BACK frames in single AGG).
 *	If the NIC is not ACK_ENABLED it may use the खातापूर्ण-bit in first non-0
 *	len delim to determine अगर AGG or single.
 * @STA_CTXT_HE_RU_2MHZ_BLOCK: indicates that 26-tone RU OFDMA transmission are
 *      not allowed (as there are OBSS that might classअगरy such transmissions as
 *      radar pulses).
 */
क्रमागत iwl_he_sta_ctxt_flags अणु
	STA_CTXT_HE_REF_BSSID_VALID		= BIT(4),
	STA_CTXT_HE_BSS_COLOR_DIS		= BIT(5),
	STA_CTXT_HE_PARTIAL_BSS_COLOR		= BIT(6),
	STA_CTXT_HE_32BIT_BA_BITMAP		= BIT(7),
	STA_CTXT_HE_PACKET_EXT			= BIT(8),
	STA_CTXT_HE_TRIG_RND_ALLOC		= BIT(9),
	STA_CTXT_HE_CONST_TRIG_RND_ALLOC	= BIT(10),
	STA_CTXT_HE_ACK_ENABLED			= BIT(11),
	STA_CTXT_HE_MU_EDCA_CW			= BIT(12),
	STA_CTXT_HE_NIC_NOT_ACK_ENABLED		= BIT(13),
	STA_CTXT_HE_RU_2MHZ_BLOCK		= BIT(14),
पूर्ण;

/**
 * क्रमागत iwl_he_htc_flags - HE HTC support flags
 * @IWL_HE_HTC_SUPPORT: HE-HTC support
 * @IWL_HE_HTC_UL_MU_RESP_SCHED: HE UL MU response schedule
 *	support via A-control field
 * @IWL_HE_HTC_BSR_SUPP: BSR support in A-control field
 * @IWL_HE_HTC_OMI_SUPP: A-OMI support in A-control field
 * @IWL_HE_HTC_BQR_SUPP: A-BQR support in A-control field
 */
क्रमागत iwl_he_htc_flags अणु
	IWL_HE_HTC_SUPPORT			= BIT(0),
	IWL_HE_HTC_UL_MU_RESP_SCHED		= BIT(3),
	IWL_HE_HTC_BSR_SUPP			= BIT(4),
	IWL_HE_HTC_OMI_SUPP			= BIT(5),
	IWL_HE_HTC_BQR_SUPP			= BIT(6),
पूर्ण;

/*
 * @IWL_HE_HTC_LINK_ADAP_NO_FEEDBACK: the STA करोes not provide HE MFB
 * @IWL_HE_HTC_LINK_ADAP_UNSOLICITED: the STA provides only unsolicited HE MFB
 * @IWL_HE_HTC_LINK_ADAP_BOTH: the STA is capable of providing HE MFB in
 *      response to HE MRQ and अगर the STA provides unsolicited HE MFB
 */
#घोषणा IWL_HE_HTC_LINK_ADAP_POS		(1)
#घोषणा IWL_HE_HTC_LINK_ADAP_NO_FEEDBACK	(0)
#घोषणा IWL_HE_HTC_LINK_ADAP_UNSOLICITED	(2 << IWL_HE_HTC_LINK_ADAP_POS)
#घोषणा IWL_HE_HTC_LINK_ADAP_BOTH		(3 << IWL_HE_HTC_LINK_ADAP_POS)

/**
 * काष्ठा iwl_he_sta_context_cmd_v1 - configure FW to work with HE AP
 * @sta_id: STA id
 * @tid_limit: max num of TIDs in TX HE-SU multi-TID agg
 *	0 - bad value, 1 - multi-tid not supported, 2..8 - tid limit
 * @reserved1: reserved byte क्रम future use
 * @reserved2: reserved byte क्रम future use
 * @flags: see %iwl_11ax_sta_ctxt_flags
 * @ref_bssid_addr: reference BSSID used by the AP
 * @reserved0: reserved 2 bytes क्रम aligning the ref_bssid_addr field to 8 bytes
 * @htc_flags: which features are supported in HTC
 * @frag_flags: frag support in A-MSDU
 * @frag_level: frag support level
 * @frag_max_num: max num of "open" MSDUs in the receiver (in घातer of 2)
 * @frag_min_size: min frag size (except last frag)
 * @pkt_ext: optional, exists according to PPE-present bit in the HE-PHY capa
 * @bss_color: 11ax AP ID that is used in the HE SIG-A to mark पूर्णांकer BSS frame
 * @htc_trig_based_pkt_ext: शेष PE in 4us units
 * @frame_समय_rts_th: HE duration RTS threshold, in units of 32us
 * @अक्रम_alloc_ecwmin: अक्रमom CWmin = 2**ECWmin-1
 * @अक्रम_alloc_ecwmax: अक्रमom CWmax = 2**ECWmax-1
 * @reserved3: reserved byte क्रम future use
 * @trig_based_txf: MU EDCA Parameter set क्रम the trigger based traffic queues
 */
काष्ठा iwl_he_sta_context_cmd_v1 अणु
	u8 sta_id;
	u8 tid_limit;
	u8 reserved1;
	u8 reserved2;
	__le32 flags;

	/* The below fields are set via Multiple BSSID IE */
	u8 ref_bssid_addr[6];
	__le16 reserved0;

	/* The below fields are set via HE-capabilities IE */
	__le32 htc_flags;

	u8 frag_flags;
	u8 frag_level;
	u8 frag_max_num;
	u8 frag_min_size;

	/* The below fields are set via PPE thresholds element */
	काष्ठा iwl_he_pkt_ext pkt_ext;

	/* The below fields are set via HE-Operation IE */
	u8 bss_color;
	u8 htc_trig_based_pkt_ext;
	__le16 frame_समय_rts_th;

	/* Ranकरोm access parameter set (i.e. RAPS) */
	u8 अक्रम_alloc_ecwmin;
	u8 अक्रम_alloc_ecwmax;
	__le16 reserved3;

	/* The below fields are set via MU EDCA parameter set element */
	काष्ठा iwl_he_backoff_conf trig_based_txf[AC_NUM];
पूर्ण __packed; /* STA_CONTEXT_DOT11AX_API_S_VER_1 */

/**
 * काष्ठा iwl_he_sta_context_cmd - configure FW to work with HE AP
 * @sta_id: STA id
 * @tid_limit: max num of TIDs in TX HE-SU multi-TID agg
 *	0 - bad value, 1 - multi-tid not supported, 2..8 - tid limit
 * @reserved1: reserved byte क्रम future use
 * @reserved2: reserved byte क्रम future use
 * @flags: see %iwl_11ax_sta_ctxt_flags
 * @ref_bssid_addr: reference BSSID used by the AP
 * @reserved0: reserved 2 bytes क्रम aligning the ref_bssid_addr field to 8 bytes
 * @htc_flags: which features are supported in HTC
 * @frag_flags: frag support in A-MSDU
 * @frag_level: frag support level
 * @frag_max_num: max num of "open" MSDUs in the receiver (in घातer of 2)
 * @frag_min_size: min frag size (except last frag)
 * @pkt_ext: optional, exists according to PPE-present bit in the HE-PHY capa
 * @bss_color: 11ax AP ID that is used in the HE SIG-A to mark पूर्णांकer BSS frame
 * @htc_trig_based_pkt_ext: शेष PE in 4us units
 * @frame_समय_rts_th: HE duration RTS threshold, in units of 32us
 * @अक्रम_alloc_ecwmin: अक्रमom CWmin = 2**ECWmin-1
 * @अक्रम_alloc_ecwmax: अक्रमom CWmax = 2**ECWmax-1
 * @reserved3: reserved byte क्रम future use
 * @trig_based_txf: MU EDCA Parameter set क्रम the trigger based traffic queues
 * @max_bssid_indicator: indicator of the max bssid supported on the associated
 *	bss
 * @bssid_index: index of the associated VAP
 * @ema_ap: AP supports enhanced Multi BSSID advertisement
 * @profile_periodicity: number of Beacon periods that are needed to receive the
 *	complete VAPs info
 * @bssid_count: actual number of VAPs in the MultiBSS Set
 * @reserved4: alignment
 */
काष्ठा iwl_he_sta_context_cmd अणु
	u8 sta_id;
	u8 tid_limit;
	u8 reserved1;
	u8 reserved2;
	__le32 flags;

	/* The below fields are set via Multiple BSSID IE */
	u8 ref_bssid_addr[6];
	__le16 reserved0;

	/* The below fields are set via HE-capabilities IE */
	__le32 htc_flags;

	u8 frag_flags;
	u8 frag_level;
	u8 frag_max_num;
	u8 frag_min_size;

	/* The below fields are set via PPE thresholds element */
	काष्ठा iwl_he_pkt_ext pkt_ext;

	/* The below fields are set via HE-Operation IE */
	u8 bss_color;
	u8 htc_trig_based_pkt_ext;
	__le16 frame_समय_rts_th;

	/* Ranकरोm access parameter set (i.e. RAPS) */
	u8 अक्रम_alloc_ecwmin;
	u8 अक्रम_alloc_ecwmax;
	__le16 reserved3;

	/* The below fields are set via MU EDCA parameter set element */
	काष्ठा iwl_he_backoff_conf trig_based_txf[AC_NUM];

	u8 max_bssid_indicator;
	u8 bssid_index;
	u8 ema_ap;
	u8 profile_periodicity;
	u8 bssid_count;
	u8 reserved4[3];
पूर्ण __packed; /* STA_CONTEXT_DOT11AX_API_S_VER_2 */

/**
 * काष्ठा iwl_he_monitor_cmd - configure air snअगरfer क्रम HE
 * @bssid: the BSSID to snअगरf क्रम
 * @reserved1: reserved क्रम dword alignment
 * @aid: the AID to track on क्रम HE MU
 * @reserved2: reserved क्रम future use
 */
काष्ठा iwl_he_monitor_cmd अणु
	u8 bssid[6];
	__le16 reserved1;
	__le16 aid;
	u8 reserved2[6];
पूर्ण __packed; /* HE_AIR_SNIFFER_CONFIG_CMD_API_S_VER_1 */

#पूर्ण_अगर /* __iwl_fw_api_mac_h__ */
