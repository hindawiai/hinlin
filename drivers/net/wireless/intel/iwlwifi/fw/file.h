<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2008-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_file_h__
#घोषणा __iwl_fw_file_h__

#समावेश <linux/netdevice.h>
#समावेश <linux/nl80211.h>

/* v1/v2 uCode file layout */
काष्ठा iwl_ucode_header अणु
	__le32 ver;	/* major/minor/API/serial */
	जोड़ अणु
		काष्ठा अणु
			__le32 inst_size;	/* bytes of runसमय code */
			__le32 data_size;	/* bytes of runसमय data */
			__le32 init_size;	/* bytes of init code */
			__le32 init_data_size;	/* bytes of init data */
			__le32 boot_size;	/* bytes of bootstrap code */
			u8 data[0];		/* in same order as sizes */
		पूर्ण v1;
		काष्ठा अणु
			__le32 build;		/* build number */
			__le32 inst_size;	/* bytes of runसमय code */
			__le32 data_size;	/* bytes of runसमय data */
			__le32 init_size;	/* bytes of init code */
			__le32 init_data_size;	/* bytes of init data */
			__le32 boot_size;	/* bytes of bootstrap code */
			u8 data[0];		/* in same order as sizes */
		पूर्ण v2;
	पूर्ण u;
पूर्ण;

#घोषणा IWL_UCODE_TLV_DEBUG_BASE	0x1000005
#घोषणा IWL_UCODE_TLV_CONST_BASE	0x100

/*
 * new TLV uCode file layout
 *
 * The new TLV file क्रमmat contains TLVs, that each specअगरy
 * some piece of data.
 */

क्रमागत iwl_ucode_tlv_type अणु
	IWL_UCODE_TLV_INVALID		= 0, /* unused */
	IWL_UCODE_TLV_INST		= 1,
	IWL_UCODE_TLV_DATA		= 2,
	IWL_UCODE_TLV_INIT		= 3,
	IWL_UCODE_TLV_INIT_DATA		= 4,
	IWL_UCODE_TLV_BOOT		= 5,
	IWL_UCODE_TLV_PROBE_MAX_LEN	= 6, /* a u32 value */
	IWL_UCODE_TLV_PAN		= 7,
	IWL_UCODE_TLV_RUNT_EVTLOG_PTR	= 8,
	IWL_UCODE_TLV_RUNT_EVTLOG_SIZE	= 9,
	IWL_UCODE_TLV_RUNT_ERRLOG_PTR	= 10,
	IWL_UCODE_TLV_INIT_EVTLOG_PTR	= 11,
	IWL_UCODE_TLV_INIT_EVTLOG_SIZE	= 12,
	IWL_UCODE_TLV_INIT_ERRLOG_PTR	= 13,
	IWL_UCODE_TLV_ENHANCE_SENS_TBL	= 14,
	IWL_UCODE_TLV_PHY_CALIBRATION_SIZE = 15,
	IWL_UCODE_TLV_WOWLAN_INST	= 16,
	IWL_UCODE_TLV_WOWLAN_DATA	= 17,
	IWL_UCODE_TLV_FLAGS		= 18,
	IWL_UCODE_TLV_SEC_RT		= 19,
	IWL_UCODE_TLV_SEC_INIT		= 20,
	IWL_UCODE_TLV_SEC_WOWLAN	= 21,
	IWL_UCODE_TLV_DEF_CALIB		= 22,
	IWL_UCODE_TLV_PHY_SKU		= 23,
	IWL_UCODE_TLV_SECURE_SEC_RT	= 24,
	IWL_UCODE_TLV_SECURE_SEC_INIT	= 25,
	IWL_UCODE_TLV_SECURE_SEC_WOWLAN	= 26,
	IWL_UCODE_TLV_NUM_OF_CPU	= 27,
	IWL_UCODE_TLV_CSCHEME		= 28,
	IWL_UCODE_TLV_API_CHANGES_SET	= 29,
	IWL_UCODE_TLV_ENABLED_CAPABILITIES	= 30,
	IWL_UCODE_TLV_N_SCAN_CHANNELS		= 31,
	IWL_UCODE_TLV_PAGING		= 32,
	IWL_UCODE_TLV_SEC_RT_USNIFFER	= 34,
	/* 35 is unused */
	IWL_UCODE_TLV_FW_VERSION	= 36,
	IWL_UCODE_TLV_FW_DBG_DEST	= 38,
	IWL_UCODE_TLV_FW_DBG_CONF	= 39,
	IWL_UCODE_TLV_FW_DBG_TRIGGER	= 40,
	IWL_UCODE_TLV_CMD_VERSIONS	= 48,
	IWL_UCODE_TLV_FW_GSCAN_CAPA	= 50,
	IWL_UCODE_TLV_FW_MEM_SEG	= 51,
	IWL_UCODE_TLV_IML		= 52,
	IWL_UCODE_TLV_UMAC_DEBUG_ADDRS	= 54,
	IWL_UCODE_TLV_LMAC_DEBUG_ADDRS	= 55,
	IWL_UCODE_TLV_FW_RECOVERY_INFO	= 57,
	IWL_UCODE_TLV_HW_TYPE			= 58,
	IWL_UCODE_TLV_FW_FSEQ_VERSION		= 60,
	IWL_UCODE_TLV_PHY_INTEGRATION_VERSION	= 61,

	IWL_UCODE_TLV_PNVM_VERSION		= 62,
	IWL_UCODE_TLV_PNVM_SKU			= 64,

	IWL_UCODE_TLV_FW_NUM_STATIONS		= IWL_UCODE_TLV_CONST_BASE + 0,

	IWL_UCODE_TLV_TYPE_DEBUG_INFO		= IWL_UCODE_TLV_DEBUG_BASE + 0,
	IWL_UCODE_TLV_TYPE_BUFFER_ALLOCATION	= IWL_UCODE_TLV_DEBUG_BASE + 1,
	IWL_UCODE_TLV_TYPE_HCMD			= IWL_UCODE_TLV_DEBUG_BASE + 2,
	IWL_UCODE_TLV_TYPE_REGIONS		= IWL_UCODE_TLV_DEBUG_BASE + 3,
	IWL_UCODE_TLV_TYPE_TRIGGERS		= IWL_UCODE_TLV_DEBUG_BASE + 4,
	IWL_UCODE_TLV_DEBUG_MAX = IWL_UCODE_TLV_TYPE_TRIGGERS,

	/* TLVs 0x1000-0x2000 are क्रम पूर्णांकernal driver usage */
	IWL_UCODE_TLV_FW_DBG_DUMP_LST	= 0x1000,
पूर्ण;

काष्ठा iwl_ucode_tlv अणु
	__le32 type;		/* see above */
	__le32 length;		/* not including type/length fields */
	u8 data[0];
पूर्ण;

#घोषणा IWL_TLV_UCODE_MAGIC		0x0a4c5749
#घोषणा FW_VER_HUMAN_READABLE_SZ	64

काष्ठा iwl_tlv_ucode_header अणु
	/*
	 * The TLV style ucode header is distinguished from
	 * the v1/v2 style header by first four bytes being
	 * zero, as such is an invalid combination of
	 * major/minor/API/serial versions.
	 */
	__le32 zero;
	__le32 magic;
	u8 human_पढ़ोable[FW_VER_HUMAN_READABLE_SZ];
	/* major/minor/API/serial or major in new क्रमmat */
	__le32 ver;
	__le32 build;
	__le64 ignore;
	/*
	 * The data contained herein has a TLV layout,
	 * see above क्रम the TLV header and types.
	 * Note that each TLV is padded to a length
	 * that is a multiple of 4 क्रम alignment.
	 */
	u8 data[0];
पूर्ण;

/*
 * ucode TLVs
 *
 * ability to get extension क्रम: flags & capabilities from ucode binaries files
 */
काष्ठा iwl_ucode_api अणु
	__le32 api_index;
	__le32 api_flags;
पूर्ण __packed;

काष्ठा iwl_ucode_capa अणु
	__le32 api_index;
	__le32 api_capa;
पूर्ण __packed;

/**
 * क्रमागत iwl_ucode_tlv_flag - ucode API flags
 * @IWL_UCODE_TLV_FLAGS_PAN: This is PAN capable microcode; this previously
 *	was a separate TLV but moved here to save space.
 * @IWL_UCODE_TLV_FLAGS_NEWSCAN: new uCode scan behavior on hidden SSID,
 *	treats good CRC threshold as a boolean
 * @IWL_UCODE_TLV_FLAGS_MFP: This uCode image supports MFP (802.11w).
 * @IWL_UCODE_TLV_FLAGS_UAPSD_SUPPORT: This uCode image supports uAPSD
 * @IWL_UCODE_TLV_FLAGS_SHORT_BL: 16 entries of block list instead of 64 in scan
 *	offload profile config command.
 * @IWL_UCODE_TLV_FLAGS_D3_6_IPV6_ADDRS: D3 image supports up to six
 *	(rather than two) IPv6 addresses
 * @IWL_UCODE_TLV_FLAGS_NO_BASIC_SSID: not sending a probe with the SSID element
 *	from the probe request ढाँचा.
 * @IWL_UCODE_TLV_FLAGS_NEW_NSOFFL_SMALL: new NS offload (small version)
 * @IWL_UCODE_TLV_FLAGS_NEW_NSOFFL_LARGE: new NS offload (large version)
 * @IWL_UCODE_TLV_FLAGS_UAPSD_SUPPORT: General support क्रम uAPSD
 * @IWL_UCODE_TLV_FLAGS_P2P_PS_UAPSD: P2P client supports uAPSD घातer save
 * @IWL_UCODE_TLV_FLAGS_BCAST_FILTERING: uCode supports broadcast filtering.
 * @IWL_UCODE_TLV_FLAGS_EBS_SUPPORT: this uCode image supports EBS.
 */
क्रमागत iwl_ucode_tlv_flag अणु
	IWL_UCODE_TLV_FLAGS_PAN			= BIT(0),
	IWL_UCODE_TLV_FLAGS_NEWSCAN		= BIT(1),
	IWL_UCODE_TLV_FLAGS_MFP			= BIT(2),
	IWL_UCODE_TLV_FLAGS_SHORT_BL		= BIT(7),
	IWL_UCODE_TLV_FLAGS_D3_6_IPV6_ADDRS	= BIT(10),
	IWL_UCODE_TLV_FLAGS_NO_BASIC_SSID	= BIT(12),
	IWL_UCODE_TLV_FLAGS_NEW_NSOFFL_SMALL	= BIT(15),
	IWL_UCODE_TLV_FLAGS_NEW_NSOFFL_LARGE	= BIT(16),
	IWL_UCODE_TLV_FLAGS_UAPSD_SUPPORT	= BIT(24),
	IWL_UCODE_TLV_FLAGS_EBS_SUPPORT		= BIT(25),
	IWL_UCODE_TLV_FLAGS_P2P_PS_UAPSD	= BIT(26),
	IWL_UCODE_TLV_FLAGS_BCAST_FILTERING	= BIT(29),
पूर्ण;

प्रकार अचिन्हित पूर्णांक __bitwise iwl_ucode_tlv_api_t;

/**
 * क्रमागत iwl_ucode_tlv_api - ucode api
 * @IWL_UCODE_TLV_API_FRAGMENTED_SCAN: This ucode supports active dwell समय
 *	दीर्घer than the passive one, which is essential क्रम fragmented scan.
 * @IWL_UCODE_TLV_API_WIFI_MCC_UPDATE: ucode supports MCC updates with source.
 * @IWL_UCODE_TLV_API_LQ_SS_PARAMS: Configure STBC/BFER via LQ CMD ss_params
 * @IWL_UCODE_TLV_API_NEW_VERSION: new versioning क्रमmat
 * @IWL_UCODE_TLV_API_SCAN_TSF_REPORT: Scan start समय reported in scan
 *	iteration complete notअगरication, and the बारtamp reported क्रम RX
 *	received during scan, are reported in TSF of the mac specअगरied in the
 *	scan request.
 * @IWL_UCODE_TLV_API_TKIP_MIC_KEYS: This ucode supports version 2 of
 *	ADD_MODIFY_STA_KEY_API_S_VER_2.
 * @IWL_UCODE_TLV_API_STA_TYPE: This ucode supports station type assignement.
 * @IWL_UCODE_TLV_API_न_अंक2_VER2: This ucode supports न_अंक API version 2
 * @IWL_UCODE_TLV_API_NEW_RX_STATS: should new RX STATISTICS API be used
 * @IWL_UCODE_TLV_API_QUOTA_LOW_LATENCY: Quota command includes a field
 *	indicating low latency direction.
 * @IWL_UCODE_TLV_API_DEPRECATE_TTAK: RX status flag TTAK ok (bit 7) is
 *	deprecated.
 * @IWL_UCODE_TLV_API_ADAPTIVE_DWELL_V2: This ucode supports version 8
 *	of scan request: SCAN_REQUEST_CMD_UMAC_API_S_VER_8
 * @IWL_UCODE_TLV_API_FRAG_EBS: This ucode supports fragmented EBS
 * @IWL_UCODE_TLV_API_REDUCE_TX_POWER: This ucode supports v5 of
 *	the REDUCE_TX_POWER_CMD.
 * @IWL_UCODE_TLV_API_SHORT_BEACON_NOTIF: This ucode supports the लघु
 *	version of the beacon notअगरication.
 * @IWL_UCODE_TLV_API_BEACON_FILTER_V4: This ucode supports v4 of
 *	BEACON_FILTER_CONFIG_API_S_VER_4.
 * @IWL_UCODE_TLV_API_REGULATORY_NVM_INFO: This ucode supports v4 of
 *	REGULATORY_NVM_GET_INFO_RSP_API_S.
 * @IWL_UCODE_TLV_API_FTM_NEW_RANGE_REQ: This ucode supports v7 of
 *	LOCATION_RANGE_REQ_CMD_API_S and v6 of LOCATION_RANGE_RESP_NTFY_API_S.
 * @IWL_UCODE_TLV_API_SCAN_OFFLOAD_CHANS: This ucode supports v2 of
 *	SCAN_OFFLOAD_PROखाता_MATCH_RESULTS_S and v3 of
 *	SCAN_OFFLOAD_PROखाताS_QUERY_RSP_S.
 * @IWL_UCODE_TLV_API_MBSSID_HE: This ucode supports v2 of
 *	STA_CONTEXT_DOT11AX_API_S
 * @IWL_UCODE_TLV_API_SAR_TABLE_VER: This ucode supports dअगरferent sar
 *	version tables.
 * @IWL_UCODE_TLV_API_REDUCED_SCAN_CONFIG: This ucode supports v3 of
 *  SCAN_CONFIG_DB_CMD_API_S.
 *
 * @NUM_IWL_UCODE_TLV_API: number of bits used
 */
क्रमागत iwl_ucode_tlv_api अणु
	/* API Set 0 */
	IWL_UCODE_TLV_API_FRAGMENTED_SCAN	= (__क्रमce iwl_ucode_tlv_api_t)8,
	IWL_UCODE_TLV_API_WIFI_MCC_UPDATE	= (__क्रमce iwl_ucode_tlv_api_t)9,
	IWL_UCODE_TLV_API_LQ_SS_PARAMS		= (__क्रमce iwl_ucode_tlv_api_t)18,
	IWL_UCODE_TLV_API_NEW_VERSION		= (__क्रमce iwl_ucode_tlv_api_t)20,
	IWL_UCODE_TLV_API_SCAN_TSF_REPORT	= (__क्रमce iwl_ucode_tlv_api_t)28,
	IWL_UCODE_TLV_API_TKIP_MIC_KEYS		= (__क्रमce iwl_ucode_tlv_api_t)29,
	IWL_UCODE_TLV_API_STA_TYPE		= (__क्रमce iwl_ucode_tlv_api_t)30,
	IWL_UCODE_TLV_API_न_अंक2_VER2		= (__क्रमce iwl_ucode_tlv_api_t)31,
	/* API Set 1 */
	IWL_UCODE_TLV_API_ADAPTIVE_DWELL	= (__क्रमce iwl_ucode_tlv_api_t)32,
	IWL_UCODE_TLV_API_OCE			= (__क्रमce iwl_ucode_tlv_api_t)33,
	IWL_UCODE_TLV_API_NEW_BEACON_TEMPLATE	= (__क्रमce iwl_ucode_tlv_api_t)34,
	IWL_UCODE_TLV_API_NEW_RX_STATS		= (__क्रमce iwl_ucode_tlv_api_t)35,
	IWL_UCODE_TLV_API_WOWLAN_KEY_MATERIAL	= (__क्रमce iwl_ucode_tlv_api_t)36,
	IWL_UCODE_TLV_API_QUOTA_LOW_LATENCY	= (__क्रमce iwl_ucode_tlv_api_t)38,
	IWL_UCODE_TLV_API_DEPRECATE_TTAK	= (__क्रमce iwl_ucode_tlv_api_t)41,
	IWL_UCODE_TLV_API_ADAPTIVE_DWELL_V2	= (__क्रमce iwl_ucode_tlv_api_t)42,
	IWL_UCODE_TLV_API_FRAG_EBS		= (__क्रमce iwl_ucode_tlv_api_t)44,
	IWL_UCODE_TLV_API_REDUCE_TX_POWER	= (__क्रमce iwl_ucode_tlv_api_t)45,
	IWL_UCODE_TLV_API_SHORT_BEACON_NOTIF	= (__क्रमce iwl_ucode_tlv_api_t)46,
	IWL_UCODE_TLV_API_BEACON_FILTER_V4      = (__क्रमce iwl_ucode_tlv_api_t)47,
	IWL_UCODE_TLV_API_REGULATORY_NVM_INFO   = (__क्रमce iwl_ucode_tlv_api_t)48,
	IWL_UCODE_TLV_API_FTM_NEW_RANGE_REQ     = (__क्रमce iwl_ucode_tlv_api_t)49,
	IWL_UCODE_TLV_API_SCAN_OFFLOAD_CHANS    = (__क्रमce iwl_ucode_tlv_api_t)50,
	IWL_UCODE_TLV_API_MBSSID_HE		= (__क्रमce iwl_ucode_tlv_api_t)52,
	IWL_UCODE_TLV_API_WOWLAN_TCP_SYN_WAKE	= (__क्रमce iwl_ucode_tlv_api_t)53,
	IWL_UCODE_TLV_API_FTM_RTT_ACCURACY      = (__क्रमce iwl_ucode_tlv_api_t)54,
	IWL_UCODE_TLV_API_SAR_TABLE_VER         = (__क्रमce iwl_ucode_tlv_api_t)55,
	IWL_UCODE_TLV_API_REDUCED_SCAN_CONFIG   = (__क्रमce iwl_ucode_tlv_api_t)56,
	IWL_UCODE_TLV_API_ADWELL_HB_DEF_N_AP	= (__क्रमce iwl_ucode_tlv_api_t)57,
	IWL_UCODE_TLV_API_SCAN_EXT_CHAN_VER	= (__क्रमce iwl_ucode_tlv_api_t)58,
	IWL_UCODE_TLV_API_BAND_IN_RX_DATA	= (__क्रमce iwl_ucode_tlv_api_t)59,


	NUM_IWL_UCODE_TLV_API
#अगर_घोषित __CHECKER__
		/* sparse says it cannot increment the previous क्रमागत member */
		= 128
#पूर्ण_अगर
पूर्ण;

प्रकार अचिन्हित पूर्णांक __bitwise iwl_ucode_tlv_capa_t;

/**
 * क्रमागत iwl_ucode_tlv_capa - ucode capabilities
 * @IWL_UCODE_TLV_CAPA_D0I3_SUPPORT: supports D0i3
 * @IWL_UCODE_TLV_CAPA_LAR_SUPPORT: supports Location Aware Regulatory
 * @IWL_UCODE_TLV_CAPA_UMAC_SCAN: supports UMAC scan.
 * @IWL_UCODE_TLV_CAPA_BEAMFORMER: supports Beamक्रमmer
 * @IWL_UCODE_TLV_CAPA_TDLS_SUPPORT: support basic TDLS functionality
 * @IWL_UCODE_TLV_CAPA_TXPOWER_INSERTION_SUPPORT: supports insertion of current
 *	tx घातer value पूर्णांकo TPC Report action frame and Link Measurement Report
 *	action frame
 * @IWL_UCODE_TLV_CAPA_DS_PARAM_SET_IE_SUPPORT: supports updating current
 *	channel in DS parameter set element in probe requests.
 * @IWL_UCODE_TLV_CAPA_WFA_TPC_REP_IE_SUPPORT: supports adding TPC Report IE in
 *	probe requests.
 * @IWL_UCODE_TLV_CAPA_QUIET_PERIOD_SUPPORT: supports Quiet Period requests
 * @IWL_UCODE_TLV_CAPA_DQA_SUPPORT: supports dynamic queue allocation (DQA),
 *	which also implies support क्रम the scheduler configuration command
 * @IWL_UCODE_TLV_CAPA_TDLS_CHANNEL_SWITCH: supports TDLS channel चयनing
 * @IWL_UCODE_TLV_CAPA_CNSLDTD_D3_D0_IMG: Consolidated D3-D0 image
 * @IWL_UCODE_TLV_CAPA_HOTSPOT_SUPPORT: supports Hot Spot Command
 * @IWL_UCODE_TLV_CAPA_DC2DC_SUPPORT: supports DC2DC Command
 * @IWL_UCODE_TLV_CAPA_CSUM_SUPPORT: supports TCP Checksum Offload
 * @IWL_UCODE_TLV_CAPA_RADIO_BEACON_STATS: support radio and beacon statistics
 * @IWL_UCODE_TLV_CAPA_P2P_SCM_UAPSD: supports U-APSD on p2p पूर्णांकerface when it
 *	is standalone or with a BSS station पूर्णांकerface in the same binding.
 * @IWL_UCODE_TLV_CAPA_BT_COEX_PLCR: enabled BT Coex packet level co-running
 * @IWL_UCODE_TLV_CAPA_LAR_MULTI_MCC: ucode supports LAR updates with dअगरferent
 *	sources क्रम the MCC. This TLV bit is a future replacement to
 *	IWL_UCODE_TLV_API_WIFI_MCC_UPDATE. When either is set, multi-source LAR
 *	is supported.
 * @IWL_UCODE_TLV_CAPA_BT_COEX_RRC: supports BT Coex RRC
 * @IWL_UCODE_TLV_CAPA_GSCAN_SUPPORT: supports gscan (no दीर्घer used)
 * @IWL_UCODE_TLV_CAPA_SOC_LATENCY_SUPPORT: the firmware supports setting
 *	stabilization latency क्रम SoCs.
 * @IWL_UCODE_TLV_CAPA_STA_PM_NOTIF: firmware will send STA PM notअगरication
 * @IWL_UCODE_TLV_CAPA_TLC_OFFLOAD: firmware implements rate scaling algorithm
 * @IWL_UCODE_TLV_CAPA_DYNAMIC_QUOTA: firmware implements quota related
 * @IWL_UCODE_TLV_CAPA_COEX_SCHEMA_2: firmware implements Coex Schema 2
 * IWL_UCODE_TLV_CAPA_CHANNEL_SWITCH_CMD: firmware supports CSA command
 * @IWL_UCODE_TLV_CAPA_ULTRA_HB_CHANNELS: firmware supports ultra high band
 *	(6 GHz).
 * @IWL_UCODE_TLV_CAPA_CS_MODIFY: firmware supports modअगरy action CSA command
 * @IWL_UCODE_TLV_CAPA_EXTENDED_DTS_MEASURE: extended DTS measurement
 * @IWL_UCODE_TLV_CAPA_SHORT_PM_TIMEOUTS: supports लघु PM समयouts
 * @IWL_UCODE_TLV_CAPA_BT_MPLUT_SUPPORT: supports bt-coex Multi-priority LUT
 * @IWL_UCODE_TLV_CAPA_CSA_AND_TBTT_OFFLOAD: the firmware supports CSA
 *	countकरोwn offloading. Beacon notअगरications are not sent to the host.
 *	The fw also offloads TBTT alignment.
 * @IWL_UCODE_TLV_CAPA_BEACON_ANT_SELECTION: firmware will decide on what
 *	antenna the beacon should be transmitted
 * @IWL_UCODE_TLV_CAPA_BEACON_STORING: firmware will store the latest beacon
 *	from AP and will send it upon d0i3 निकास.
 * @IWL_UCODE_TLV_CAPA_LAR_SUPPORT_V3: support LAR API V3
 * @IWL_UCODE_TLV_CAPA_CT_KILL_BY_FW: firmware responsible क्रम CT-समाप्त
 * @IWL_UCODE_TLV_CAPA_TEMP_THS_REPORT_SUPPORT: supports temperature
 *	thresholds reporting
 * @IWL_UCODE_TLV_CAPA_CTDP_SUPPORT: supports cTDP command
 * @IWL_UCODE_TLV_CAPA_USNIFFER_UNIFIED: supports usnअगरfer enabled in
 *	regular image.
 * @IWL_UCODE_TLV_CAPA_EXTEND_SHARED_MEM_CFG: support getting more shared
 *	memory addresses from the firmware.
 * @IWL_UCODE_TLV_CAPA_LQM_SUPPORT: supports Link Quality Measurement
 * @IWL_UCODE_TLV_CAPA_TX_POWER_ACK: reduced TX घातer API has larger
 *	command size (command version 4) that supports toggling ACK TX
 *	घातer reduction.
 * @IWL_UCODE_TLV_CAPA_D3_DEBUG: supports debug recording during D3
 * @IWL_UCODE_TLV_CAPA_MCC_UPDATE_11AX_SUPPORT: MCC response support 11ax
 *	capability.
 * @IWL_UCODE_TLV_CAPA_CSI_REPORTING: firmware is capable of being configured
 *	to report the CSI inक्रमmation with (certain) RX frames
 * @IWL_UCODE_TLV_CAPA_FTM_CALIBRATED: has FTM calibrated and thus supports both
 *	initiator and responder
 * @IWL_UCODE_TLV_CAPA_MLME_OFFLOAD: supports MLME offload
 * @IWL_UCODE_TLV_CAPA_PROTECTED_TWT: Supports protection of TWT action frames
 * @IWL_UCODE_TLV_CAPA_FW_RESET_HANDSHAKE: Supports the firmware handshake in
 *	reset flow
 * @IWL_UCODE_TLV_CAPA_PASSIVE_6GHZ_SCAN: Support क्रम passive scan on 6GHz PSC
 *      channels even when these are not enabled.
 *
 * @NUM_IWL_UCODE_TLV_CAPA: number of bits used
 */
क्रमागत iwl_ucode_tlv_capa अणु
	/* set 0 */
	IWL_UCODE_TLV_CAPA_D0I3_SUPPORT			= (__क्रमce iwl_ucode_tlv_capa_t)0,
	IWL_UCODE_TLV_CAPA_LAR_SUPPORT			= (__क्रमce iwl_ucode_tlv_capa_t)1,
	IWL_UCODE_TLV_CAPA_UMAC_SCAN			= (__क्रमce iwl_ucode_tlv_capa_t)2,
	IWL_UCODE_TLV_CAPA_BEAMFORMER			= (__क्रमce iwl_ucode_tlv_capa_t)3,
	IWL_UCODE_TLV_CAPA_TDLS_SUPPORT			= (__क्रमce iwl_ucode_tlv_capa_t)6,
	IWL_UCODE_TLV_CAPA_TXPOWER_INSERTION_SUPPORT	= (__क्रमce iwl_ucode_tlv_capa_t)8,
	IWL_UCODE_TLV_CAPA_DS_PARAM_SET_IE_SUPPORT	= (__क्रमce iwl_ucode_tlv_capa_t)9,
	IWL_UCODE_TLV_CAPA_WFA_TPC_REP_IE_SUPPORT	= (__क्रमce iwl_ucode_tlv_capa_t)10,
	IWL_UCODE_TLV_CAPA_QUIET_PERIOD_SUPPORT		= (__क्रमce iwl_ucode_tlv_capa_t)11,
	IWL_UCODE_TLV_CAPA_DQA_SUPPORT			= (__क्रमce iwl_ucode_tlv_capa_t)12,
	IWL_UCODE_TLV_CAPA_TDLS_CHANNEL_SWITCH		= (__क्रमce iwl_ucode_tlv_capa_t)13,
	IWL_UCODE_TLV_CAPA_CNSLDTD_D3_D0_IMG		= (__क्रमce iwl_ucode_tlv_capa_t)17,
	IWL_UCODE_TLV_CAPA_HOTSPOT_SUPPORT		= (__क्रमce iwl_ucode_tlv_capa_t)18,
	IWL_UCODE_TLV_CAPA_DC2DC_CONFIG_SUPPORT		= (__क्रमce iwl_ucode_tlv_capa_t)19,
	IWL_UCODE_TLV_CAPA_CSUM_SUPPORT			= (__क्रमce iwl_ucode_tlv_capa_t)21,
	IWL_UCODE_TLV_CAPA_RADIO_BEACON_STATS		= (__क्रमce iwl_ucode_tlv_capa_t)22,
	IWL_UCODE_TLV_CAPA_P2P_SCM_UAPSD		= (__क्रमce iwl_ucode_tlv_capa_t)26,
	IWL_UCODE_TLV_CAPA_BT_COEX_PLCR			= (__क्रमce iwl_ucode_tlv_capa_t)28,
	IWL_UCODE_TLV_CAPA_LAR_MULTI_MCC		= (__क्रमce iwl_ucode_tlv_capa_t)29,
	IWL_UCODE_TLV_CAPA_BT_COEX_RRC			= (__क्रमce iwl_ucode_tlv_capa_t)30,
	IWL_UCODE_TLV_CAPA_GSCAN_SUPPORT		= (__क्रमce iwl_ucode_tlv_capa_t)31,

	/* set 1 */
	IWL_UCODE_TLV_CAPA_SOC_LATENCY_SUPPORT		= (__क्रमce iwl_ucode_tlv_capa_t)37,
	IWL_UCODE_TLV_CAPA_STA_PM_NOTIF			= (__क्रमce iwl_ucode_tlv_capa_t)38,
	IWL_UCODE_TLV_CAPA_BINDING_CDB_SUPPORT		= (__क्रमce iwl_ucode_tlv_capa_t)39,
	IWL_UCODE_TLV_CAPA_CDB_SUPPORT			= (__क्रमce iwl_ucode_tlv_capa_t)40,
	IWL_UCODE_TLV_CAPA_D0I3_END_FIRST		= (__क्रमce iwl_ucode_tlv_capa_t)41,
	IWL_UCODE_TLV_CAPA_TLC_OFFLOAD                  = (__क्रमce iwl_ucode_tlv_capa_t)43,
	IWL_UCODE_TLV_CAPA_DYNAMIC_QUOTA                = (__क्रमce iwl_ucode_tlv_capa_t)44,
	IWL_UCODE_TLV_CAPA_COEX_SCHEMA_2		= (__क्रमce iwl_ucode_tlv_capa_t)45,
	IWL_UCODE_TLV_CAPA_CHANNEL_SWITCH_CMD		= (__क्रमce iwl_ucode_tlv_capa_t)46,
	IWL_UCODE_TLV_CAPA_FTM_CALIBRATED		= (__क्रमce iwl_ucode_tlv_capa_t)47,
	IWL_UCODE_TLV_CAPA_ULTRA_HB_CHANNELS		= (__क्रमce iwl_ucode_tlv_capa_t)48,
	IWL_UCODE_TLV_CAPA_CS_MODIFY			= (__क्रमce iwl_ucode_tlv_capa_t)49,
	IWL_UCODE_TLV_CAPA_SET_LTR_GEN2			= (__क्रमce iwl_ucode_tlv_capa_t)50,
	IWL_UCODE_TLV_CAPA_SET_PPAG			= (__क्रमce iwl_ucode_tlv_capa_t)52,
	IWL_UCODE_TLV_CAPA_TAS_CFG			= (__क्रमce iwl_ucode_tlv_capa_t)53,
	IWL_UCODE_TLV_CAPA_SESSION_PROT_CMD		= (__क्रमce iwl_ucode_tlv_capa_t)54,
	IWL_UCODE_TLV_CAPA_PROTECTED_TWT		= (__क्रमce iwl_ucode_tlv_capa_t)56,
	IWL_UCODE_TLV_CAPA_FW_RESET_HANDSHAKE		= (__क्रमce iwl_ucode_tlv_capa_t)57,
	IWL_UCODE_TLV_CAPA_PASSIVE_6GHZ_SCAN		= (__क्रमce iwl_ucode_tlv_capa_t)58,

	/* set 2 */
	IWL_UCODE_TLV_CAPA_EXTENDED_DTS_MEASURE		= (__क्रमce iwl_ucode_tlv_capa_t)64,
	IWL_UCODE_TLV_CAPA_SHORT_PM_TIMEOUTS		= (__क्रमce iwl_ucode_tlv_capa_t)65,
	IWL_UCODE_TLV_CAPA_BT_MPLUT_SUPPORT		= (__क्रमce iwl_ucode_tlv_capa_t)67,
	IWL_UCODE_TLV_CAPA_MULTI_QUEUE_RX_SUPPORT	= (__क्रमce iwl_ucode_tlv_capa_t)68,
	IWL_UCODE_TLV_CAPA_CSA_AND_TBTT_OFFLOAD		= (__क्रमce iwl_ucode_tlv_capa_t)70,
	IWL_UCODE_TLV_CAPA_BEACON_ANT_SELECTION		= (__क्रमce iwl_ucode_tlv_capa_t)71,
	IWL_UCODE_TLV_CAPA_BEACON_STORING		= (__क्रमce iwl_ucode_tlv_capa_t)72,
	IWL_UCODE_TLV_CAPA_LAR_SUPPORT_V3		= (__क्रमce iwl_ucode_tlv_capa_t)73,
	IWL_UCODE_TLV_CAPA_CT_KILL_BY_FW		= (__क्रमce iwl_ucode_tlv_capa_t)74,
	IWL_UCODE_TLV_CAPA_TEMP_THS_REPORT_SUPPORT	= (__क्रमce iwl_ucode_tlv_capa_t)75,
	IWL_UCODE_TLV_CAPA_CTDP_SUPPORT			= (__क्रमce iwl_ucode_tlv_capa_t)76,
	IWL_UCODE_TLV_CAPA_USNIFFER_UNIFIED		= (__क्रमce iwl_ucode_tlv_capa_t)77,
	IWL_UCODE_TLV_CAPA_EXTEND_SHARED_MEM_CFG	= (__क्रमce iwl_ucode_tlv_capa_t)80,
	IWL_UCODE_TLV_CAPA_LQM_SUPPORT			= (__क्रमce iwl_ucode_tlv_capa_t)81,
	IWL_UCODE_TLV_CAPA_TX_POWER_ACK			= (__क्रमce iwl_ucode_tlv_capa_t)84,
	IWL_UCODE_TLV_CAPA_D3_DEBUG			= (__क्रमce iwl_ucode_tlv_capa_t)87,
	IWL_UCODE_TLV_CAPA_LED_CMD_SUPPORT		= (__क्रमce iwl_ucode_tlv_capa_t)88,
	IWL_UCODE_TLV_CAPA_MCC_UPDATE_11AX_SUPPORT	= (__क्रमce iwl_ucode_tlv_capa_t)89,
	IWL_UCODE_TLV_CAPA_CSI_REPORTING		= (__क्रमce iwl_ucode_tlv_capa_t)90,
	IWL_UCODE_TLV_CAPA_DBG_SUSPEND_RESUME_CMD_SUPP	= (__क्रमce iwl_ucode_tlv_capa_t)92,
	IWL_UCODE_TLV_CAPA_DBG_BUF_ALLOC_CMD_SUPP	= (__क्रमce iwl_ucode_tlv_capa_t)93,

	/* set 3 */
	IWL_UCODE_TLV_CAPA_MLME_OFFLOAD			= (__क्रमce iwl_ucode_tlv_capa_t)96,

	/*
	 * @IWL_UCODE_TLV_CAPA_PSC_CHAN_SUPPORT: supports PSC channels
	 */
	IWL_UCODE_TLV_CAPA_PSC_CHAN_SUPPORT		= (__क्रमce iwl_ucode_tlv_capa_t)98,

	IWL_UCODE_TLV_CAPA_BIGTK_SUPPORT		= (__क्रमce iwl_ucode_tlv_capa_t)100,
	IWL_UCODE_TLV_CAPA_RFIM_SUPPORT			= (__क्रमce iwl_ucode_tlv_capa_t)102,

	NUM_IWL_UCODE_TLV_CAPA
#अगर_घोषित __CHECKER__
		/* sparse says it cannot increment the previous क्रमागत member */
		= 128
#पूर्ण_अगर
पूर्ण;

/* The शेष calibrate table size अगर not specअगरied by firmware file */
#घोषणा IWL_DEFAULT_STANDARD_PHY_CALIBRATE_TBL_SIZE	18
#घोषणा IWL_MAX_STANDARD_PHY_CALIBRATE_TBL_SIZE		19
#घोषणा IWL_MAX_PHY_CALIBRATE_TBL_SIZE			253

/* The शेष max probe length अगर not specअगरied by the firmware file */
#घोषणा IWL_DEFAULT_MAX_PROBE_LENGTH	200

/*
 * For 16.0 uCode and above, there is no dअगरferentiation between sections,
 * just an offset to the HW address.
 */
#घोषणा CPU1_CPU2_SEPARATOR_SECTION	0xFFFFCCCC
#घोषणा PAGING_SEPARATOR_SECTION	0xAAAABBBB

/* uCode version contains 4 values: Major/Minor/API/Serial */
#घोषणा IWL_UCODE_MAJOR(ver)	(((ver) & 0xFF000000) >> 24)
#घोषणा IWL_UCODE_MINOR(ver)	(((ver) & 0x00FF0000) >> 16)
#घोषणा IWL_UCODE_API(ver)	(((ver) & 0x0000FF00) >> 8)
#घोषणा IWL_UCODE_SERIAL(ver)	((ver) & 0x000000FF)

/**
 * काष्ठा iwl_tlv_calib_ctrl - Calibration control काष्ठा.
 * Sent as part of the phy configuration command.
 * @flow_trigger: biपंचांगap क्रम which calibrations to perक्रमm according to
 *		flow triggers.
 * @event_trigger: biपंचांगap क्रम which calibrations to perक्रमm according to
 *		event triggers.
 */
काष्ठा iwl_tlv_calib_ctrl अणु
	__le32 flow_trigger;
	__le32 event_trigger;
पूर्ण __packed;

क्रमागत iwl_fw_phy_cfg अणु
	FW_PHY_CFG_RADIO_TYPE_POS = 0,
	FW_PHY_CFG_RADIO_TYPE = 0x3 << FW_PHY_CFG_RADIO_TYPE_POS,
	FW_PHY_CFG_RADIO_STEP_POS = 2,
	FW_PHY_CFG_RADIO_STEP = 0x3 << FW_PHY_CFG_RADIO_STEP_POS,
	FW_PHY_CFG_RADIO_DASH_POS = 4,
	FW_PHY_CFG_RADIO_DASH = 0x3 << FW_PHY_CFG_RADIO_DASH_POS,
	FW_PHY_CFG_TX_CHAIN_POS = 16,
	FW_PHY_CFG_TX_CHAIN = 0xf << FW_PHY_CFG_TX_CHAIN_POS,
	FW_PHY_CFG_RX_CHAIN_POS = 20,
	FW_PHY_CFG_RX_CHAIN = 0xf << FW_PHY_CFG_RX_CHAIN_POS,
	FW_PHY_CFG_CHAIN_SAD_POS = 23,
	FW_PHY_CFG_CHAIN_SAD_ENABLED = 0x1 << FW_PHY_CFG_CHAIN_SAD_POS,
	FW_PHY_CFG_CHAIN_SAD_ANT_A = 0x2 << FW_PHY_CFG_CHAIN_SAD_POS,
	FW_PHY_CFG_CHAIN_SAD_ANT_B = 0x4 << FW_PHY_CFG_CHAIN_SAD_POS,
	FW_PHY_CFG_SHARED_CLK = BIT(31),
पूर्ण;

#घोषणा IWL_UCODE_MAX_CS		1

/**
 * काष्ठा iwl_fw_cipher_scheme - a cipher scheme supported by FW.
 * @cipher: a cipher suite selector
 * @flags: cipher scheme flags (currently reserved क्रम a future use)
 * @hdr_len: a size of MPDU security header
 * @pn_len: a size of PN
 * @pn_off: an offset of pn from the beginning of the security header
 * @key_idx_off: an offset of key index byte in the security header
 * @key_idx_mask: a bit mask of key_idx bits
 * @key_idx_shअगरt: bit shअगरt needed to get key_idx
 * @mic_len: mic length in bytes
 * @hw_cipher: a HW cipher index used in host commands
 */
काष्ठा iwl_fw_cipher_scheme अणु
	__le32 cipher;
	u8 flags;
	u8 hdr_len;
	u8 pn_len;
	u8 pn_off;
	u8 key_idx_off;
	u8 key_idx_mask;
	u8 key_idx_shअगरt;
	u8 mic_len;
	u8 hw_cipher;
पूर्ण __packed;

क्रमागत iwl_fw_dbg_reg_चालक अणु
	CSR_ASSIGN,
	CSR_SETBIT,
	CSR_CLEARBIT,

	PRPH_ASSIGN,
	PRPH_SETBIT,
	PRPH_CLEARBIT,

	INसूचीECT_ASSIGN,
	INसूचीECT_SETBIT,
	INसूचीECT_CLEARBIT,

	PRPH_BLOCKBIT,
पूर्ण;

/**
 * काष्ठा iwl_fw_dbg_reg_op - an operation on a रेजिस्टर
 *
 * @op: &क्रमागत iwl_fw_dbg_reg_चालक
 * @addr: offset of the रेजिस्टर
 * @val: value
 */
काष्ठा iwl_fw_dbg_reg_op अणु
	u8 op;
	u8 reserved[3];
	__le32 addr;
	__le32 val;
पूर्ण __packed;

/**
 * क्रमागत iwl_fw_dbg_monitor_mode - available monitor recording modes
 *
 * @SMEM_MODE: monitor stores the data in SMEM
 * @EXTERNAL_MODE: monitor stores the data in allocated DRAM
 * @MARBH_MODE: monitor stores the data in MARBH buffer
 * @MIPI_MODE: monitor outमाला_दो the data through the MIPI पूर्णांकerface
 */
क्रमागत iwl_fw_dbg_monitor_mode अणु
	SMEM_MODE = 0,
	EXTERNAL_MODE = 1,
	MARBH_MODE = 2,
	MIPI_MODE = 3,
पूर्ण;

/**
 * काष्ठा iwl_fw_dbg_mem_seg_tlv - configures the debug data memory segments
 *
 * @data_type: the memory segment type to record
 * @ofs: the memory segment offset
 * @len: the memory segment length, in bytes
 *
 * This parses IWL_UCODE_TLV_FW_MEM_SEG
 */
काष्ठा iwl_fw_dbg_mem_seg_tlv अणु
	__le32 data_type;
	__le32 ofs;
	__le32 len;
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_dbg_dest_tlv_v1 - configures the destination of the debug data
 *
 * @version: version of the TLV - currently 0
 * @monitor_mode: &क्रमागत iwl_fw_dbg_monitor_mode
 * @size_घातer: buffer size will be 2^(size_घातer + 11)
 * @base_reg: addr of the base addr रेजिस्टर (PRPH)
 * @end_reg:  addr of the end addr रेजिस्टर (PRPH)
 * @ग_लिखो_ptr_reg: the addr of the reg of the ग_लिखो poपूर्णांकer
 * @wrap_count: the addr of the reg of the wrap_count
 * @base_shअगरt: shअगरt right of the base addr reg
 * @end_shअगरt: shअगरt right of the end addr reg
 * @reg_ops: array of रेजिस्टरs operations
 *
 * This parses IWL_UCODE_TLV_FW_DBG_DEST
 */
काष्ठा iwl_fw_dbg_dest_tlv_v1 अणु
	u8 version;
	u8 monitor_mode;
	u8 size_घातer;
	u8 reserved;
	__le32 base_reg;
	__le32 end_reg;
	__le32 ग_लिखो_ptr_reg;
	__le32 wrap_count;
	u8 base_shअगरt;
	u8 end_shअगरt;
	काष्ठा iwl_fw_dbg_reg_op reg_ops[0];
पूर्ण __packed;

/* Mask of the रेजिस्टर क्रम defining the LDBG MAC2SMEM buffer SMEM size */
#घोषणा IWL_LDBG_M2S_BUF_SIZE_MSK	0x0fff0000
/* Mask of the रेजिस्टर क्रम defining the LDBG MAC2SMEM SMEM base address */
#घोषणा IWL_LDBG_M2S_BUF_BA_MSK		0x00000fff
/* The smem buffer chunks are in units of 256 bits */
#घोषणा IWL_M2S_UNIT_SIZE			0x100

काष्ठा iwl_fw_dbg_dest_tlv अणु
	u8 version;
	u8 monitor_mode;
	u8 size_घातer;
	u8 reserved;
	__le32 cfg_reg;
	__le32 ग_लिखो_ptr_reg;
	__le32 wrap_count;
	u8 base_shअगरt;
	u8 size_shअगरt;
	काष्ठा iwl_fw_dbg_reg_op reg_ops[0];
पूर्ण __packed;

काष्ठा iwl_fw_dbg_conf_hcmd अणु
	u8 id;
	u8 reserved;
	__le16 len;
	u8 data[0];
पूर्ण __packed;

/**
 * क्रमागत iwl_fw_dbg_trigger_mode - triggers functionalities
 *
 * @IWL_FW_DBG_TRIGGER_START: when trigger occurs re-conf the dbg mechanism
 * @IWL_FW_DBG_TRIGGER_STOP: when trigger occurs pull the dbg data
 * @IWL_FW_DBG_TRIGGER_MONITOR_ONLY: when trigger occurs trigger is set to
 *	collect only monitor data
 */
क्रमागत iwl_fw_dbg_trigger_mode अणु
	IWL_FW_DBG_TRIGGER_START = BIT(0),
	IWL_FW_DBG_TRIGGER_STOP = BIT(1),
	IWL_FW_DBG_TRIGGER_MONITOR_ONLY = BIT(2),
पूर्ण;

/**
 * क्रमागत iwl_fw_dbg_trigger_flags - the flags supported by wrt triggers
 * @IWL_FW_DBG_FORCE_RESTART: क्रमce a firmware restart
 */
क्रमागत iwl_fw_dbg_trigger_flags अणु
	IWL_FW_DBG_FORCE_RESTART = BIT(0),
पूर्ण;

/**
 * क्रमागत iwl_fw_dbg_trigger_vअगर_type - define the VIF type क्रम a trigger
 * @IWL_FW_DBG_CONF_VIF_ANY: any vअगर type
 * @IWL_FW_DBG_CONF_VIF_IBSS: IBSS mode
 * @IWL_FW_DBG_CONF_VIF_STATION: BSS mode
 * @IWL_FW_DBG_CONF_VIF_AP: AP mode
 * @IWL_FW_DBG_CONF_VIF_P2P_CLIENT: P2P Client mode
 * @IWL_FW_DBG_CONF_VIF_P2P_GO: P2P GO mode
 * @IWL_FW_DBG_CONF_VIF_P2P_DEVICE: P2P device
 */
क्रमागत iwl_fw_dbg_trigger_vअगर_type अणु
	IWL_FW_DBG_CONF_VIF_ANY = NL80211_IFTYPE_UNSPECIFIED,
	IWL_FW_DBG_CONF_VIF_IBSS = NL80211_IFTYPE_ADHOC,
	IWL_FW_DBG_CONF_VIF_STATION = NL80211_IFTYPE_STATION,
	IWL_FW_DBG_CONF_VIF_AP = NL80211_IFTYPE_AP,
	IWL_FW_DBG_CONF_VIF_P2P_CLIENT = NL80211_IFTYPE_P2P_CLIENT,
	IWL_FW_DBG_CONF_VIF_P2P_GO = NL80211_IFTYPE_P2P_GO,
	IWL_FW_DBG_CONF_VIF_P2P_DEVICE = NL80211_IFTYPE_P2P_DEVICE,
पूर्ण;

/**
 * काष्ठा iwl_fw_dbg_trigger_tlv - a TLV that describes the trigger
 * @id: &क्रमागत iwl_fw_dbg_trigger
 * @vअगर_type: &क्रमागत iwl_fw_dbg_trigger_vअगर_type
 * @stop_conf_ids: biपंचांगap of configurations this trigger relates to.
 *	अगर the mode is %IWL_FW_DBG_TRIGGER_STOP, then अगर the bit corresponding
 *	to the currently running configuration is set, the data should be
 *	collected.
 * @stop_delay: how many milliseconds to रुको beक्रमe collecting the data
 *	after the STOP trigger fires.
 * @mode: &क्रमागत iwl_fw_dbg_trigger_mode - can be stop / start of both
 * @start_conf_id: अगर mode is %IWL_FW_DBG_TRIGGER_START, this defines what
 *	configuration should be applied when the triggers kicks in.
 * @occurrences: number of occurrences. 0 means the trigger will never fire.
 * @trig_dis_ms: the समय, in milliseconds, after an occurrence of this
 *	trigger in which another occurrence should be ignored.
 * @flags: &क्रमागत iwl_fw_dbg_trigger_flags
 */
काष्ठा iwl_fw_dbg_trigger_tlv अणु
	__le32 id;
	__le32 vअगर_type;
	__le32 stop_conf_ids;
	__le32 stop_delay;
	u8 mode;
	u8 start_conf_id;
	__le16 occurrences;
	__le16 trig_dis_ms;
	u8 flags;
	u8 reserved[5];

	u8 data[0];
पूर्ण __packed;

#घोषणा FW_DBG_START_FROM_ALIVE	0
#घोषणा FW_DBG_CONF_MAX		32
#घोषणा FW_DBG_INVALID		0xff

/**
 * काष्ठा iwl_fw_dbg_trigger_missed_bcon - configures trigger क्रम missed beacons
 * @stop_consec_missed_bcon: stop recording अगर threshold is crossed.
 * @stop_consec_missed_bcon_since_rx: stop recording अगर threshold is crossed.
 * @start_consec_missed_bcon: start recording अगर threshold is crossed.
 * @start_consec_missed_bcon_since_rx: start recording अगर threshold is crossed.
 * @reserved1: reserved
 * @reserved2: reserved
 */
काष्ठा iwl_fw_dbg_trigger_missed_bcon अणु
	__le32 stop_consec_missed_bcon;
	__le32 stop_consec_missed_bcon_since_rx;
	__le32 reserved2[2];
	__le32 start_consec_missed_bcon;
	__le32 start_consec_missed_bcon_since_rx;
	__le32 reserved1[2];
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_dbg_trigger_cmd - configures trigger क्रम messages from FW.
 * cmds: the list of commands to trigger the collection on
 */
काष्ठा iwl_fw_dbg_trigger_cmd अणु
	काष्ठा cmd अणु
		u8 cmd_id;
		u8 group_id;
	पूर्ण __packed cmds[16];
पूर्ण __packed;

/**
 * iwl_fw_dbg_trigger_stats - configures trigger क्रम statistics
 * @stop_offset: the offset of the value to be monitored
 * @stop_threshold: the threshold above which to collect
 * @start_offset: the offset of the value to be monitored
 * @start_threshold: the threshold above which to start recording
 */
काष्ठा iwl_fw_dbg_trigger_stats अणु
	__le32 stop_offset;
	__le32 stop_threshold;
	__le32 start_offset;
	__le32 start_threshold;
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_dbg_trigger_low_rssi - trigger क्रम low beacon RSSI
 * @rssi: RSSI value to trigger at
 */
काष्ठा iwl_fw_dbg_trigger_low_rssi अणु
	__le32 rssi;
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_dbg_trigger_mlme - configures trigger क्रम mlme events
 * @stop_auth_denied: number of denied authentication to collect
 * @stop_auth_समयout: number of authentication समयout to collect
 * @stop_rx_deauth: number of Rx deauth beक्रमe to collect
 * @stop_tx_deauth: number of Tx deauth beक्रमe to collect
 * @stop_assoc_denied: number of denied association to collect
 * @stop_assoc_समयout: number of association समयout to collect
 * @stop_connection_loss: number of connection loss to collect
 * @start_auth_denied: number of denied authentication to start recording
 * @start_auth_समयout: number of authentication समयout to start recording
 * @start_rx_deauth: number of Rx deauth to start recording
 * @start_tx_deauth: number of Tx deauth to start recording
 * @start_assoc_denied: number of denied association to start recording
 * @start_assoc_समयout: number of association समयout to start recording
 * @start_connection_loss: number of connection loss to start recording
 */
काष्ठा iwl_fw_dbg_trigger_mlme अणु
	u8 stop_auth_denied;
	u8 stop_auth_समयout;
	u8 stop_rx_deauth;
	u8 stop_tx_deauth;

	u8 stop_assoc_denied;
	u8 stop_assoc_समयout;
	u8 stop_connection_loss;
	u8 reserved;

	u8 start_auth_denied;
	u8 start_auth_समयout;
	u8 start_rx_deauth;
	u8 start_tx_deauth;

	u8 start_assoc_denied;
	u8 start_assoc_समयout;
	u8 start_connection_loss;
	u8 reserved2;
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_dbg_trigger_txq_समयr - configures the Tx queue's समयr
 * @command_queue: समयout क्रम the command queue in ms
 * @bss: समयout क्रम the queues of a BSS (except क्रम TDLS queues) in ms
 * @softap: समयout क्रम the queues of a softAP in ms
 * @p2p_go: समयout क्रम the queues of a P2P GO in ms
 * @p2p_client: समयout क्रम the queues of a P2P client in ms
 * @p2p_device: समयout क्रम the queues of a P2P device in ms
 * @ibss: समयout क्रम the queues of an IBSS in ms
 * @tdls: समयout क्रम the queues of a TDLS station in ms
 */
काष्ठा iwl_fw_dbg_trigger_txq_समयr अणु
	__le32 command_queue;
	__le32 bss;
	__le32 softap;
	__le32 p2p_go;
	__le32 p2p_client;
	__le32 p2p_device;
	__le32 ibss;
	__le32 tdls;
	__le32 reserved[4];
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_dbg_trigger_समय_event - configures a समय event trigger
 * समय_Events: a list of tuples <id, action_biपंचांगap>. The driver will issue a
 *	trigger each समय a समय event notअगरication that relates to समय event
 *	id with one of the actions in the biपंचांगap is received and
 *	BIT(notअगर->status) is set in status_biपंचांगap.
 *
 */
काष्ठा iwl_fw_dbg_trigger_समय_event अणु
	काष्ठा अणु
		__le32 id;
		__le32 action_biपंचांगap;
		__le32 status_biपंचांगap;
	पूर्ण __packed समय_events[16];
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_dbg_trigger_ba - configures BlockAck related trigger
 * rx_ba_start: tid biपंचांगap to configure on what tid the trigger should occur
 *	when an Rx BlockAck session is started.
 * rx_ba_stop: tid biपंचांगap to configure on what tid the trigger should occur
 *	when an Rx BlockAck session is stopped.
 * tx_ba_start: tid biपंचांगap to configure on what tid the trigger should occur
 *	when a Tx BlockAck session is started.
 * tx_ba_stop: tid biपंचांगap to configure on what tid the trigger should occur
 *	when a Tx BlockAck session is stopped.
 * rx_bar: tid biपंचांगap to configure on what tid the trigger should occur
 *	when a BAR is received (क्रम a Tx BlockAck session).
 * tx_bar: tid biपंचांगap to configure on what tid the trigger should occur
 *	when a BAR is send (क्रम an Rx BlocAck session).
 * frame_समयout: tid biपंचांगap to configure on what tid the trigger should occur
 *	when a frame बार out in the reordering buffer.
 */
काष्ठा iwl_fw_dbg_trigger_ba अणु
	__le16 rx_ba_start;
	__le16 rx_ba_stop;
	__le16 tx_ba_start;
	__le16 tx_ba_stop;
	__le16 rx_bar;
	__le16 tx_bar;
	__le16 frame_समयout;
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_dbg_trigger_tdls - configures trigger क्रम TDLS events.
 * @action_biपंचांगap: the TDLS action to trigger the collection upon
 * @peer_mode: trigger on specअगरic peer or all
 * @peer: the TDLS peer to trigger the collection on
 */
काष्ठा iwl_fw_dbg_trigger_tdls अणु
	u8 action_biपंचांगap;
	u8 peer_mode;
	u8 peer[ETH_ALEN];
	u8 reserved[4];
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_dbg_trigger_tx_status - configures trigger क्रम tx response
 *  status.
 * @statuses: the list of statuses to trigger the collection on
 */
काष्ठा iwl_fw_dbg_trigger_tx_status अणु
	काष्ठा tx_status अणु
		u8 status;
		u8 reserved[3];
	पूर्ण __packed statuses[16];
	__le32 reserved[2];
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_dbg_conf_tlv - a TLV that describes a debug configuration.
 * @id: conf id
 * @usnअगरfer: should the uSnअगरfer image be used
 * @num_of_hcmds: how many HCMDs to send are present here
 * @hcmd: a variable length host command to be sent to apply the configuration.
 *	If there is more than one HCMD to send, they will appear one after the
 *	other and be sent in the order that they appear in.
 * This parses IWL_UCODE_TLV_FW_DBG_CONF. The user can add up-to
 * %FW_DBG_CONF_MAX configuration per run.
 */
काष्ठा iwl_fw_dbg_conf_tlv अणु
	u8 id;
	u8 usnअगरfer;
	u8 reserved;
	u8 num_of_hcmds;
	काष्ठा iwl_fw_dbg_conf_hcmd hcmd;
पूर्ण __packed;

#घोषणा IWL_FW_CMD_VER_UNKNOWN 99

/**
 * काष्ठा iwl_fw_cmd_version - firmware command version entry
 * @cmd: command ID
 * @group: group ID
 * @cmd_ver: command version
 * @notअगर_ver: notअगरication version
 */
काष्ठा iwl_fw_cmd_version अणु
	u8 cmd;
	u8 group;
	u8 cmd_ver;
	u8 notअगर_ver;
पूर्ण __packed;

अटल अंतरभूत माप_प्रकार _iwl_tlv_array_len(स्थिर काष्ठा iwl_ucode_tlv *tlv,
					माप_प्रकार fixed_size, माप_प्रकार var_size)
अणु
	माप_प्रकार var_len = le32_to_cpu(tlv->length) - fixed_size;

	अगर (WARN_ON(var_len % var_size))
		वापस 0;

	वापस var_len / var_size;
पूर्ण

#घोषणा iwl_tlv_array_len(_tlv_ptr, _काष्ठा_ptr, _memb)			\
	_iwl_tlv_array_len((_tlv_ptr), माप(*(_काष्ठा_ptr)),		\
			   माप(_काष्ठा_ptr->_memb[0]))

#पूर्ण_अगर  /* __iwl_fw_file_h__ */
