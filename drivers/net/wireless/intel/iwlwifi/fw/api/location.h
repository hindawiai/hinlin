<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2015-2017 Intel Deutschland GmbH
 * Copyright (C) 2018-2020 Intel Corporation
 */
#अगर_अघोषित __iwl_fw_api_location_h__
#घोषणा __iwl_fw_api_location_h__

/**
 * क्रमागत iwl_location_subcmd_ids - location group command IDs
 */
क्रमागत iwl_location_subcmd_ids अणु
	/**
	 * @TOF_RANGE_REQ_CMD: TOF ranging request,
	 *	uses one of &काष्ठा iwl_tof_range_req_cmd_v5,
	 *	&काष्ठा iwl_tof_range_req_cmd_v7,
	 *	&काष्ठा iwl_tof_range_req_cmd_v8,
	 *	&काष्ठा iwl_tof_range_req_cmd_v9,
	 *	&काष्ठा iwl_tof_range_req_cmd_v11,
	 *	&काष्ठा iwl_tof_range_req_cmd_v7
	 */
	TOF_RANGE_REQ_CMD = 0x0,
	/**
	 * @TOF_CONFIG_CMD: TOF configuration, uses &काष्ठा iwl_tof_config_cmd
	 */
	TOF_CONFIG_CMD = 0x1,
	/**
	 * @TOF_RANGE_ABORT_CMD: पात ongoing ranging, uses
	 *	&काष्ठा iwl_tof_range_पात_cmd
	 */
	TOF_RANGE_ABORT_CMD = 0x2,
	/**
	 * @TOF_RANGE_REQ_EXT_CMD: TOF extended ranging config,
	 *	uses &काष्ठा iwl_tof_range_req_ext_cmd
	 */
	TOF_RANGE_REQ_EXT_CMD = 0x3,
	/**
	 * @TOF_RESPONDER_CONFIG_CMD: FTM responder configuration,
	 *	uses &काष्ठा iwl_tof_responder_config_cmd
	 */
	TOF_RESPONDER_CONFIG_CMD = 0x4,
	/**
	 * @TOF_RESPONDER_DYN_CONFIG_CMD: FTM dynamic configuration,
	 *	uses &काष्ठा iwl_tof_responder_dyn_config_cmd
	 */
	TOF_RESPONDER_DYN_CONFIG_CMD = 0x5,
	/**
	 * @CSI_HEADER_NOTIFICATION: CSI header
	 */
	CSI_HEADER_NOTIFICATION = 0xFA,
	/**
	 * @CSI_CHUNKS_NOTIFICATION: CSI chunk,
	 *	uses &काष्ठा iwl_csi_chunk_notअगरication
	 */
	CSI_CHUNKS_NOTIFICATION = 0xFB,
	/**
	 * @TOF_LC_NOTIF: used क्रम LCI/civic location, contains just
	 *	the action frame
	 */
	TOF_LC_NOTIF = 0xFC,
	/**
	 * @TOF_RESPONDER_STATS: FTM responder statistics notअगरication,
	 *	uses &काष्ठा iwl_fपंचांग_responder_stats
	 */
	TOF_RESPONDER_STATS = 0xFD,
	/**
	 * @TOF_MCSI_DEBUG_NOTIF: MCSI debug notअगरication, uses
	 *	&काष्ठा iwl_tof_mcsi_notअगर
	 */
	TOF_MCSI_DEBUG_NOTIF = 0xFE,
	/**
	 * @TOF_RANGE_RESPONSE_NOTIF: ranging response, using
	 *	&काष्ठा iwl_tof_range_rsp_ntfy
	 */
	TOF_RANGE_RESPONSE_NOTIF = 0xFF,
पूर्ण;

/**
 * काष्ठा iwl_tof_config_cmd - ToF configuration
 * @tof_disabled: indicates अगर ToF is disabled (or not)
 * @one_sided_disabled: indicates अगर one-sided is disabled (or not)
 * @is_debug_mode: indiciates अगर debug mode is active
 * @is_buf_required: indicates अगर channel estimation buffer is required
 */
काष्ठा iwl_tof_config_cmd अणु
	u8 tof_disabled;
	u8 one_sided_disabled;
	u8 is_debug_mode;
	u8 is_buf_required;
पूर्ण __packed;

/**
 * क्रमागत iwl_tof_bandwidth - values क्रम iwl_tof_range_req_ap_entry.bandwidth
 * @IWL_TOF_BW_20_LEGACY: 20 MHz non-HT
 * @IWL_TOF_BW_20_HT: 20 MHz HT
 * @IWL_TOF_BW_40: 40 MHz
 * @IWL_TOF_BW_80: 80 MHz
 * @IWL_TOF_BW_160: 160 MHz
 * @IWL_TOF_BW_NUM: number of tof bandwidths
 */
क्रमागत iwl_tof_bandwidth अणु
	IWL_TOF_BW_20_LEGACY,
	IWL_TOF_BW_20_HT,
	IWL_TOF_BW_40,
	IWL_TOF_BW_80,
	IWL_TOF_BW_160,
	IWL_TOF_BW_NUM,
पूर्ण; /* LOCAT_BW_TYPE_E */

/*
 * क्रमागत iwl_tof_algo_type - Algorithym type क्रम range measurement request
 */
क्रमागत iwl_tof_algo_type अणु
	IWL_TOF_ALGO_TYPE_MAX_LIKE	= 0,
	IWL_TOF_ALGO_TYPE_LINEAR_REG	= 1,
	IWL_TOF_ALGO_TYPE_FFT		= 2,

	/* Keep last */
	IWL_TOF_ALGO_TYPE_INVALID,
पूर्ण; /* ALGO_TYPE_E */

/*
 * क्रमागत iwl_tof_mcsi_ntfy - Enable/Disable MCSI notअगरications
 */
क्रमागत iwl_tof_mcsi_enable अणु
	IWL_TOF_MCSI_DISABLED = 0,
	IWL_TOF_MCSI_ENABLED = 1,
पूर्ण; /* MCSI_ENABLE_E */

/**
 * क्रमागत iwl_tof_responder_cmd_valid_field - valid fields in the responder cfg
 * @IWL_TOF_RESPONDER_CMD_VALID_CHAN_INFO: channel info is valid
 * @IWL_TOF_RESPONDER_CMD_VALID_TOA_OFFSET: ToA offset is valid
 * @IWL_TOF_RESPONDER_CMD_VALID_COMMON_CALIB: common calibration mode is valid
 * @IWL_TOF_RESPONDER_CMD_VALID_SPECIFIC_CALIB: spefici calibration mode is
 *	valid
 * @IWL_TOF_RESPONDER_CMD_VALID_BSSID: BSSID is valid
 * @IWL_TOF_RESPONDER_CMD_VALID_TX_ANT: TX antenna is valid
 * @IWL_TOF_RESPONDER_CMD_VALID_ALGO_TYPE: algorithm type is valid
 * @IWL_TOF_RESPONDER_CMD_VALID_NON_ASAP_SUPPORT: non-ASAP support is valid
 * @IWL_TOF_RESPONDER_CMD_VALID_STATISTICS_REPORT_SUPPORT: statistics report
 *	support is valid
 * @IWL_TOF_RESPONDER_CMD_VALID_MCSI_NOTIF_SUPPORT: MCSI notअगरication support
 *	is valid
 * @IWL_TOF_RESPONDER_CMD_VALID_FAST_ALGO_SUPPORT: fast algorithm support
 *	is valid
 * @IWL_TOF_RESPONDER_CMD_VALID_RETRY_ON_ALGO_FAIL: retry on algorithm failure
 *	is valid
 * @IWL_TOF_RESPONDER_CMD_VALID_STA_ID: station ID is valid
 * @IWL_TOF_RESPONDER_CMD_VALID_NDP_SUPPORT: enable/disable NDP ranging support
 *	is valid
 * @IWL_TOF_RESPONDER_CMD_VALID_NDP_PARAMS: NDP parameters are valid
 * @IWL_TOF_RESPONDER_CMD_VALID_LMR_FEEDBACK: LMR feedback support is valid
 */
क्रमागत iwl_tof_responder_cmd_valid_field अणु
	IWL_TOF_RESPONDER_CMD_VALID_CHAN_INFO = BIT(0),
	IWL_TOF_RESPONDER_CMD_VALID_TOA_OFFSET = BIT(1),
	IWL_TOF_RESPONDER_CMD_VALID_COMMON_CALIB = BIT(2),
	IWL_TOF_RESPONDER_CMD_VALID_SPECIFIC_CALIB = BIT(3),
	IWL_TOF_RESPONDER_CMD_VALID_BSSID = BIT(4),
	IWL_TOF_RESPONDER_CMD_VALID_TX_ANT = BIT(5),
	IWL_TOF_RESPONDER_CMD_VALID_ALGO_TYPE = BIT(6),
	IWL_TOF_RESPONDER_CMD_VALID_NON_ASAP_SUPPORT = BIT(7),
	IWL_TOF_RESPONDER_CMD_VALID_STATISTICS_REPORT_SUPPORT = BIT(8),
	IWL_TOF_RESPONDER_CMD_VALID_MCSI_NOTIF_SUPPORT = BIT(9),
	IWL_TOF_RESPONDER_CMD_VALID_FAST_ALGO_SUPPORT = BIT(10),
	IWL_TOF_RESPONDER_CMD_VALID_RETRY_ON_ALGO_FAIL = BIT(11),
	IWL_TOF_RESPONDER_CMD_VALID_STA_ID = BIT(12),
	IWL_TOF_RESPONDER_CMD_VALID_NDP_SUPPORT = BIT(22),
	IWL_TOF_RESPONDER_CMD_VALID_NDP_PARAMS = BIT(23),
	IWL_TOF_RESPONDER_CMD_VALID_LMR_FEEDBACK = BIT(24),
पूर्ण;

/**
 * क्रमागत iwl_tof_responder_cfg_flags - responder configuration flags
 * @IWL_TOF_RESPONDER_FLAGS_NON_ASAP_SUPPORT: non-ASAP support
 * @IWL_TOF_RESPONDER_FLAGS_REPORT_STATISTICS: report statistics
 * @IWL_TOF_RESPONDER_FLAGS_REPORT_MCSI: report MCSI
 * @IWL_TOF_RESPONDER_FLAGS_ALGO_TYPE: algorithm type
 * @IWL_TOF_RESPONDER_FLAGS_TOA_OFFSET_MODE: ToA offset mode
 * @IWL_TOF_RESPONDER_FLAGS_COMMON_CALIB_MODE: common calibration mode
 * @IWL_TOF_RESPONDER_FLAGS_SPECIFIC_CALIB_MODE: specअगरic calibration mode
 * @IWL_TOF_RESPONDER_FLAGS_FAST_ALGO_SUPPORT: fast algorithm support
 * @IWL_TOF_RESPONDER_FLAGS_RETRY_ON_ALGO_FAIL: retry on algorithm fail
 * @IWL_TOF_RESPONDER_FLAGS_FTM_TX_ANT: TX antenna mask
 * @IWL_TOF_RESPONDER_FLAGS_NDP_SUPPORT: support NDP ranging
 * @IWL_TOF_RESPONDER_FLAGS_LMR_FEEDBACK: request क्रम LMR feedback अगर the
 *	initiator supports it
 */
क्रमागत iwl_tof_responder_cfg_flags अणु
	IWL_TOF_RESPONDER_FLAGS_NON_ASAP_SUPPORT = BIT(0),
	IWL_TOF_RESPONDER_FLAGS_REPORT_STATISTICS = BIT(1),
	IWL_TOF_RESPONDER_FLAGS_REPORT_MCSI = BIT(2),
	IWL_TOF_RESPONDER_FLAGS_ALGO_TYPE = BIT(3) | BIT(4) | BIT(5),
	IWL_TOF_RESPONDER_FLAGS_TOA_OFFSET_MODE = BIT(6),
	IWL_TOF_RESPONDER_FLAGS_COMMON_CALIB_MODE = BIT(7),
	IWL_TOF_RESPONDER_FLAGS_SPECIFIC_CALIB_MODE = BIT(8),
	IWL_TOF_RESPONDER_FLAGS_FAST_ALGO_SUPPORT = BIT(9),
	IWL_TOF_RESPONDER_FLAGS_RETRY_ON_ALGO_FAIL = BIT(10),
	IWL_TOF_RESPONDER_FLAGS_FTM_TX_ANT = RATE_MCS_ANT_ABC_MSK,
	IWL_TOF_RESPONDER_FLAGS_NDP_SUPPORT = BIT(24),
	IWL_TOF_RESPONDER_FLAGS_LMR_FEEDBACK = BIT(25),
पूर्ण;

/**
 * काष्ठा iwl_tof_responder_config_cmd_v6 - ToF AP mode (क्रम debug)
 * @cmd_valid_fields: &iwl_tof_responder_cmd_valid_field
 * @responder_cfg_flags: &iwl_tof_responder_cfg_flags
 * @bandwidth: current AP Bandwidth: &क्रमागत iwl_tof_bandwidth
 * @rate: current AP rate
 * @channel_num: current AP Channel
 * @ctrl_ch_position: coding of the control channel position relative to
 *	the center frequency, see iwl_mvm_get_ctrl_pos()
 * @sta_id: index of the AP STA when in AP mode
 * @reserved1: reserved
 * @toa_offset: Artअगरicial addition [pSec] क्रम the ToA - to be used क्रम debug
 *	purposes, simulating station movement by adding various values
 *	to this field
 * @common_calib: XVT: common calibration value
 * @specअगरic_calib: XVT: specअगरic calibration value
 * @bssid: Current AP BSSID
 * @reserved2: reserved
 */
काष्ठा iwl_tof_responder_config_cmd_v6 अणु
	__le32 cmd_valid_fields;
	__le32 responder_cfg_flags;
	u8 bandwidth;
	u8 rate;
	u8 channel_num;
	u8 ctrl_ch_position;
	u8 sta_id;
	u8 reserved1;
	__le16 toa_offset;
	__le16 common_calib;
	__le16 specअगरic_calib;
	u8 bssid[ETH_ALEN];
	__le16 reserved2;
पूर्ण __packed; /* TOF_RESPONDER_CONFIG_CMD_API_S_VER_6 */

/**
 * काष्ठा iwl_tof_responder_config_cmd_v7 - ToF AP mode (क्रम debug)
 * @cmd_valid_fields: &iwl_tof_responder_cmd_valid_field
 * @responder_cfg_flags: &iwl_tof_responder_cfg_flags
 * @क्रमmat_bw: bits 0 - 3: &क्रमागत iwl_location_frame_क्रमmat.
 *             bits 4 - 7: &क्रमागत iwl_location_bw.
 * @rate: current AP rate
 * @channel_num: current AP Channel
 * @ctrl_ch_position: coding of the control channel position relative to
 *	the center frequency, see iwl_mvm_get_ctrl_pos()
 * @sta_id: index of the AP STA when in AP mode
 * @reserved1: reserved
 * @toa_offset: Artअगरicial addition [pSec] क्रम the ToA - to be used क्रम debug
 *	purposes, simulating station movement by adding various values
 *	to this field
 * @common_calib: XVT: common calibration value
 * @specअगरic_calib: XVT: specअगरic calibration value
 * @bssid: Current AP BSSID
 * @reserved2: reserved
 */
काष्ठा iwl_tof_responder_config_cmd_v7 अणु
	__le32 cmd_valid_fields;
	__le32 responder_cfg_flags;
	u8 क्रमmat_bw;
	u8 rate;
	u8 channel_num;
	u8 ctrl_ch_position;
	u8 sta_id;
	u8 reserved1;
	__le16 toa_offset;
	__le16 common_calib;
	__le16 specअगरic_calib;
	u8 bssid[ETH_ALEN];
	__le16 reserved2;
पूर्ण __packed; /* TOF_RESPONDER_CONFIG_CMD_API_S_VER_7 */

#घोषणा IWL_RESPONDER_STS_POS	3
#घोषणा IWL_RESPONDER_TOTAL_LTF_POS	6

/**
 * काष्ठा iwl_tof_responder_config_cmd_v8 - ToF AP mode (क्रम debug)
 * @cmd_valid_fields: &iwl_tof_responder_cmd_valid_field
 * @responder_cfg_flags: &iwl_tof_responder_cfg_flags
 * @क्रमmat_bw: bits 0 - 3: &क्रमागत iwl_location_frame_क्रमmat.
 *             bits 4 - 7: &क्रमागत iwl_location_bw.
 * @rate: current AP rate
 * @channel_num: current AP Channel
 * @ctrl_ch_position: coding of the control channel position relative to
 *	the center frequency, see iwl_mvm_get_ctrl_pos()
 * @sta_id: index of the AP STA when in AP mode
 * @reserved1: reserved
 * @toa_offset: Artअगरicial addition [pSec] क्रम the ToA - to be used क्रम debug
 *	purposes, simulating station movement by adding various values
 *	to this field
 * @common_calib: XVT: common calibration value
 * @specअगरic_calib: XVT: specअगरic calibration value
 * @bssid: Current AP BSSID
 * @r2i_ndp_params: parameters क्रम R2I NDP.
 *	bits 0 - 2: max number of LTF repetitions
 *	bits 3 - 5: max number of spatial streams (supported values are < 2)
 *	bits 6 - 7: max number of total LTFs
 *		    (&क्रमागत ieee80211_range_params_max_total_ltf)
 * @i2r_ndp_params: parameters क्रम I2R NDP.
 *	bits 0 - 2: max number of LTF repetitions
 *	bits 3 - 5: max number of spatial streams
 *	bits 6 - 7: max number of total LTFs
 *		    (&क्रमागत ieee80211_range_params_max_total_ltf)
 */
काष्ठा iwl_tof_responder_config_cmd_v8 अणु
	__le32 cmd_valid_fields;
	__le32 responder_cfg_flags;
	u8 क्रमmat_bw;
	u8 rate;
	u8 channel_num;
	u8 ctrl_ch_position;
	u8 sta_id;
	u8 reserved1;
	__le16 toa_offset;
	__le16 common_calib;
	__le16 specअगरic_calib;
	u8 bssid[ETH_ALEN];
	u8 r2i_ndp_params;
	u8 i2r_ndp_params;
पूर्ण __packed; /* TOF_RESPONDER_CONFIG_CMD_API_S_VER_8 */

#घोषणा IWL_LCI_CIVIC_IE_MAX_SIZE	400

/**
 * काष्ठा iwl_tof_responder_dyn_config_cmd - Dynamic responder settings
 * @lci_len: The length of the 1st (LCI) part in the @lci_civic buffer
 * @civic_len: The length of the 2nd (CIVIC) part in the @lci_civic buffer
 * @lci_civic: The LCI/CIVIC buffer. LCI data (अगर exists) comes first, then, अगर
 *	needed, 0-padding such that the next part is dword-aligned, then CIVIC
 *	data (अगर exists) follows, and then 0-padding again to complete a
 *	4-multiple दीर्घ buffer.
 */
काष्ठा iwl_tof_responder_dyn_config_cmd_v2 अणु
	__le32 lci_len;
	__le32 civic_len;
	u8 lci_civic[];
पूर्ण __packed; /* TOF_RESPONDER_DYN_CONFIG_CMD_API_S_VER_2 */

#घोषणा IWL_LCI_MAX_SIZE	160
#घोषणा IWL_CIVIC_MAX_SIZE	160
#घोषणा HLTK_11AZ_LEN	32

/**
 * क्रमागत iwl_responder_dyn_cfg_valid_flags - valid flags क्रम dyn_config_cmd
 * @IWL_RESPONDER_DYN_CFG_VALID_LCI: LCI data is valid
 * @IWL_RESPONDER_DYN_CFG_VALID_CIVIC: Civic data is valid
 * @IWL_RESPONDER_DYN_CFG_VALID_PASN_STA: the pasn_addr, HLTK and cipher fields
 *	are valid.
 */
क्रमागत iwl_responder_dyn_cfg_valid_flags अणु
	IWL_RESPONDER_DYN_CFG_VALID_LCI = BIT(0),
	IWL_RESPONDER_DYN_CFG_VALID_CIVIC = BIT(1),
	IWL_RESPONDER_DYN_CFG_VALID_PASN_STA = BIT(2),
पूर्ण;

/**
 * काष्ठा iwl_tof_responder_dyn_config_cmd - Dynamic responder settings
 * @cipher: The negotiated cipher. see &क्रमागत iwl_location_cipher.
 * @valid_flags: flags indicating which fields in the command are valid. see
 *	&क्रमागत iwl_responder_dyn_cfg_valid_flags.
 * @lci_len: length of the LCI data in bytes
 * @civic_len: length of the Civic data in bytes
 * @lci_buf: the LCI buffer
 * @civic_buf: the Civic buffer
 * @hltk_buf: HLTK क्रम secure LTF bits generation क्रम the specअगरied station
 * @addr: mac address of the station क्रम which to use the HLTK
 * @reserved: क्रम alignment
 */
काष्ठा iwl_tof_responder_dyn_config_cmd अणु
	u8 cipher;
	u8 valid_flags;
	u8 lci_len;
	u8 civic_len;
	u8 lci_buf[IWL_LCI_MAX_SIZE];
	u8 civic_buf[IWL_LCI_MAX_SIZE];
	u8 hltk_buf[HLTK_11AZ_LEN];
	u8 addr[ETH_ALEN];
	u8 reserved[2];
पूर्ण __packed; /* TOF_RESPONDER_DYN_CONFIG_CMD_API_S_VER_3 */

/**
 * काष्ठा iwl_tof_range_req_ext_cmd - extended range req क्रम WLS
 * @tsf_समयr_offset_msec: the recommended समय offset (mSec) from the AP's TSF
 * @reserved: reserved
 * @min_delta_fपंचांग: Minimal समय between two consecutive measurements,
 *		   in units of 100us. 0 means no preference by station
 * @fपंचांग_क्रमmat_and_bw20M: FTM Channel Spacing/Format क्रम 20MHz: recommended
 *			value be sent to the AP
 * @fपंचांग_क्रमmat_and_bw40M: FTM Channel Spacing/Format क्रम 40MHz: recommended
 *			value to be sent to the AP
 * @fपंचांग_क्रमmat_and_bw80M: FTM Channel Spacing/Format क्रम 80MHz: recommended
 *			value to be sent to the AP
 */
काष्ठा iwl_tof_range_req_ext_cmd अणु
	__le16 tsf_समयr_offset_msec;
	__le16 reserved;
	u8 min_delta_fपंचांग;
	u8 fपंचांग_क्रमmat_and_bw20M;
	u8 fपंचांग_क्रमmat_and_bw40M;
	u8 fपंचांग_क्रमmat_and_bw80M;
पूर्ण __packed;

/**
 * क्रमागत iwl_tof_location_query - values क्रम query biपंचांगap
 * @IWL_TOF_LOC_LCI: query LCI
 * @IWL_TOF_LOC_CIVIC: query civic
 */
क्रमागत iwl_tof_location_query अणु
	IWL_TOF_LOC_LCI = 0x01,
	IWL_TOF_LOC_CIVIC = 0x02,
पूर्ण;

 /**
 * काष्ठा iwl_tof_range_req_ap_entry_v2 - AP configuration parameters
 * @channel_num: Current AP Channel
 * @bandwidth: Current AP Bandwidth. One of iwl_tof_bandwidth.
 * @tsf_delta_direction: TSF relatively to the subject AP
 * @ctrl_ch_position: Coding of the control channel position relative to the
 *	center frequency, see iwl_mvm_get_ctrl_pos().
 * @bssid: AP's BSSID
 * @measure_type: Measurement type: 0 - two sided, 1 - One sided
 * @num_of_bursts: Recommended value to be sent to the AP.  2s Exponent of the
 *	number of measurement iterations (min 2^0 = 1, max 2^14)
 * @burst_period: Recommended value to be sent to the AP. Measurement
 *	periodicity In units of 100ms. ignored अगर num_of_bursts = 0
 * @samples_per_burst: 2-sided: the number of FTMs pairs in single Burst (1-31);
 *	1-sided: how many rts/cts pairs should be used per burst.
 * @retries_per_sample: Max number of retries that the LMAC should send
 *	in हाल of no replies by the AP.
 * @tsf_delta: TSF Delta in units of microseconds.
 *	The dअगरference between the AP TSF and the device local घड़ी.
 * @location_req: Location Request Bit[0] LCI should be sent in the FTMR;
 *	Bit[1] Civic should be sent in the FTMR
 * @asap_mode: 0 - non asap mode, 1 - asap mode (not relevant क्रम one sided)
 * @enable_dyn_ack: Enable Dynamic ACK BW.
 *	0: Initiator पूर्णांकeract with regular AP;
 *	1: Initiator पूर्णांकeract with Responder machine: need to send the
 *	Initiator Acks with HT 40MHz / 80MHz, since the Responder should
 *	use it क्रम its ch est measurement (this flag will be set when we
 *	configure the opposite machine to be Responder).
 * @rssi: Last received value
 *	legal values: -128-0 (0x7f). above 0x0 indicating an invalid value.
 * @algo_type: &क्रमागत iwl_tof_algo_type
 * @notअगरy_mcsi: &क्रमागत iwl_tof_mcsi_ntfy.
 * @reserved: For alignment and future use
 */
काष्ठा iwl_tof_range_req_ap_entry_v2 अणु
	u8 channel_num;
	u8 bandwidth;
	u8 tsf_delta_direction;
	u8 ctrl_ch_position;
	u8 bssid[ETH_ALEN];
	u8 measure_type;
	u8 num_of_bursts;
	__le16 burst_period;
	u8 samples_per_burst;
	u8 retries_per_sample;
	__le32 tsf_delta;
	u8 location_req;
	u8 asap_mode;
	u8 enable_dyn_ack;
	s8 rssi;
	u8 algo_type;
	u8 notअगरy_mcsi;
	__le16 reserved;
पूर्ण __packed; /* LOCATION_RANGE_REQ_AP_ENTRY_CMD_API_S_VER_2 */

/**
 * क्रमागत iwl_initiator_ap_flags - per responder FTM configuration flags
 * @IWL_INITIATOR_AP_FLAGS_ASAP: Request क्रम ASAP measurement.
 * @IWL_INITIATOR_AP_FLAGS_LCI_REQUEST: Request क्रम LCI inक्रमmation
 * @IWL_INITIATOR_AP_FLAGS_CIVIC_REQUEST: Request क्रम CIVIC inक्रमmation
 * @IWL_INITIATOR_AP_FLAGS_DYN_ACK: Send HT/VHT ack क्रम FTM frames. If not set,
 *	20Mhz dup acks will be sent.
 * @IWL_INITIATOR_AP_FLAGS_ALGO_LR: Use LR algo type क्रम rtt calculation.
 *	Default algo type is ML.
 * @IWL_INITIATOR_AP_FLAGS_ALGO_FFT: Use FFT algo type क्रम rtt calculation.
 *	Default algo type is ML.
 * @IWL_INITIATOR_AP_FLAGS_MCSI_REPORT: Send the MCSI क्रम each FTM frame to the
 *	driver.
 * @IWL_INITIATOR_AP_FLAGS_NON_TB: Use non trigger based flow
 * @IWL_INITIATOR_AP_FLAGS_TB: Use trigger based flow
 * @IWL_INITIATOR_AP_FLAGS_SECURED: request secure LTF measurement
 * @IWL_INITIATOR_AP_FLAGS_LMR_FEEDBACK: Send LMR feedback
 * @IWL_INITIATOR_AP_FLAGS_USE_CALIB: Use calibration values from the request
 *      instead of fw पूर्णांकernal values.
 * @IWL_INITIATOR_AP_FLAGS_PMF: request to protect the negotiation and LMR
 *      frames with रक्षित management frames.
 */
क्रमागत iwl_initiator_ap_flags अणु
	IWL_INITIATOR_AP_FLAGS_ASAP = BIT(1),
	IWL_INITIATOR_AP_FLAGS_LCI_REQUEST = BIT(2),
	IWL_INITIATOR_AP_FLAGS_CIVIC_REQUEST = BIT(3),
	IWL_INITIATOR_AP_FLAGS_DYN_ACK = BIT(4),
	IWL_INITIATOR_AP_FLAGS_ALGO_LR = BIT(5),
	IWL_INITIATOR_AP_FLAGS_ALGO_FFT = BIT(6),
	IWL_INITIATOR_AP_FLAGS_MCSI_REPORT = BIT(8),
	IWL_INITIATOR_AP_FLAGS_NON_TB = BIT(9),
	IWL_INITIATOR_AP_FLAGS_TB = BIT(10),
	IWL_INITIATOR_AP_FLAGS_SECURED = BIT(11),
	IWL_INITIATOR_AP_FLAGS_LMR_FEEDBACK = BIT(12),
	IWL_INITIATOR_AP_FLAGS_USE_CALIB = BIT(13),
	IWL_INITIATOR_AP_FLAGS_PMF = BIT(14),
पूर्ण;

/**
 * काष्ठा iwl_tof_range_req_ap_entry_v3 - AP configuration parameters
 * @initiator_ap_flags: see &क्रमागत iwl_initiator_ap_flags.
 * @channel_num: AP Channel number
 * @bandwidth: AP bandwidth. One of iwl_tof_bandwidth.
 * @ctrl_ch_position: Coding of the control channel position relative to the
 *	center frequency, see iwl_mvm_get_ctrl_pos().
 * @fपंचांगr_max_retries: Max number of retries to send the FTMR in हाल of no
 *	reply from the AP.
 * @bssid: AP's BSSID
 * @burst_period: Recommended value to be sent to the AP. Measurement
 *	periodicity In units of 100ms. ignored अगर num_of_bursts_exp = 0
 * @samples_per_burst: the number of FTMs pairs in single Burst (1-31);
 * @num_of_bursts: Recommended value to be sent to the AP. 2s Exponent of
 *	the number of measurement iterations (min 2^0 = 1, max 2^14)
 * @reserved: For alignment and future use
 * @tsf_delta: not in use
 */
काष्ठा iwl_tof_range_req_ap_entry_v3 अणु
	__le32 initiator_ap_flags;
	u8 channel_num;
	u8 bandwidth;
	u8 ctrl_ch_position;
	u8 fपंचांगr_max_retries;
	u8 bssid[ETH_ALEN];
	__le16 burst_period;
	u8 samples_per_burst;
	u8 num_of_bursts;
	__le16 reserved;
	__le32 tsf_delta;
पूर्ण __packed; /* LOCATION_RANGE_REQ_AP_ENTRY_CMD_API_S_VER_3 */

/**
 * क्रमागत iwl_location_frame_क्रमmat - location frame क्रमmats
 * @IWL_LOCATION_FRAME_FORMAT_LEGACY: legacy
 * @IWL_LOCATION_FRAME_FORMAT_HT: HT
 * @IWL_LOCATION_FRAME_FORMAT_VHT: VHT
 * @IWL_LOCATION_FRAME_FORMAT_HE: HE
 */
क्रमागत iwl_location_frame_क्रमmat अणु
	IWL_LOCATION_FRAME_FORMAT_LEGACY,
	IWL_LOCATION_FRAME_FORMAT_HT,
	IWL_LOCATION_FRAME_FORMAT_VHT,
	IWL_LOCATION_FRAME_FORMAT_HE,
पूर्ण;

/**
 * क्रमागत iwl_location_bw - location bandwidth selection
 * @IWL_LOCATION_BW_20MHZ: 20MHz
 * @IWL_LOCATION_BW_40MHZ: 40MHz
 * @IWL_LOCATION_BW_80MHZ: 80MHz
 */
क्रमागत iwl_location_bw अणु
	IWL_LOCATION_BW_20MHZ,
	IWL_LOCATION_BW_40MHZ,
	IWL_LOCATION_BW_80MHZ,
पूर्ण;

#घोषणा TK_11AZ_LEN	32

#घोषणा LOCATION_BW_POS	4

/**
 * काष्ठा iwl_tof_range_req_ap_entry_v4 - AP configuration parameters
 * @initiator_ap_flags: see &क्रमागत iwl_initiator_ap_flags.
 * @channel_num: AP Channel number
 * @क्रमmat_bw: bits 0 - 3: &क्रमागत iwl_location_frame_क्रमmat.
 *             bits 4 - 7: &क्रमागत iwl_location_bw.
 * @ctrl_ch_position: Coding of the control channel position relative to the
 *	center frequency, see iwl_mvm_get_ctrl_pos().
 * @fपंचांगr_max_retries: Max number of retries to send the FTMR in हाल of no
 *	reply from the AP.
 * @bssid: AP's BSSID
 * @burst_period: Recommended value to be sent to the AP. Measurement
 *	periodicity In units of 100ms. ignored अगर num_of_bursts_exp = 0
 * @samples_per_burst: the number of FTMs pairs in single Burst (1-31);
 * @num_of_bursts: Recommended value to be sent to the AP. 2s Exponent of
 *	the number of measurement iterations (min 2^0 = 1, max 2^14)
 * @reserved: For alignment and future use
 * @hltk: HLTK to be used क्रम secured 11az measurement
 * @tk: TK to be used क्रम secured 11az measurement
 */
काष्ठा iwl_tof_range_req_ap_entry_v4 अणु
	__le32 initiator_ap_flags;
	u8 channel_num;
	u8 क्रमmat_bw;
	u8 ctrl_ch_position;
	u8 fपंचांगr_max_retries;
	u8 bssid[ETH_ALEN];
	__le16 burst_period;
	u8 samples_per_burst;
	u8 num_of_bursts;
	__le16 reserved;
	u8 hltk[HLTK_11AZ_LEN];
	u8 tk[TK_11AZ_LEN];
पूर्ण __packed; /* LOCATION_RANGE_REQ_AP_ENTRY_CMD_API_S_VER_4 */

/**
 * क्रमागत iwl_location_cipher - location cipher selection
 * @IWL_LOCATION_CIPHER_CCMP_128: CCMP 128
 * @IWL_LOCATION_CIPHER_GCMP_128: GCMP 128
 * @IWL_LOCATION_CIPHER_GCMP_256: GCMP 256
 * @IWL_LOCATION_CIPHER_INVALID: security is not used.
 * @IWL_LOCATION_CIPHER_MAX: maximum value क्रम this क्रमागत.
 */
क्रमागत iwl_location_cipher अणु
	IWL_LOCATION_CIPHER_CCMP_128,
	IWL_LOCATION_CIPHER_GCMP_128,
	IWL_LOCATION_CIPHER_GCMP_256,
	IWL_LOCATION_CIPHER_INVALID,
	IWL_LOCATION_CIPHER_MAX,
पूर्ण;

/**
 * काष्ठा iwl_tof_range_req_ap_entry_v6 - AP configuration parameters
 * @initiator_ap_flags: see &क्रमागत iwl_initiator_ap_flags.
 * @channel_num: AP Channel number
 * @क्रमmat_bw: bits 0 - 3: &क्रमागत iwl_location_frame_क्रमmat.
 *             bits 4 - 7: &क्रमागत iwl_location_bw.
 * @ctrl_ch_position: Coding of the control channel position relative to the
 *	center frequency, see iwl_mvm_get_ctrl_pos().
 * @fपंचांगr_max_retries: Max number of retries to send the FTMR in हाल of no
 *	reply from the AP.
 * @bssid: AP's BSSID
 * @burst_period: Recommended value to be sent to the AP. Measurement
 *	periodicity In units of 100ms. ignored अगर num_of_bursts_exp = 0
 * @samples_per_burst: the number of FTMs pairs in single Burst (1-31);
 * @num_of_bursts: Recommended value to be sent to the AP. 2s Exponent of
 *	the number of measurement iterations (min 2^0 = 1, max 2^14)
 * @sta_id: the station id of the AP. Only relevant when associated to the AP,
 *	otherwise should be set to &IWL_MVM_INVALID_STA.
 * @cipher: pairwise cipher suite क्रम secured measurement.
 *          &क्रमागत iwl_location_cipher.
 * @hltk: HLTK to be used क्रम secured 11az measurement
 * @tk: TK to be used क्रम secured 11az measurement
 * @calib: An array of calibration values per FTM rx bandwidth.
 *         If &IWL_INITIATOR_AP_FLAGS_USE_CALIB is set, the fw will use the
 *         calibration value that corresponds to the rx bandwidth of the FTM
 *         frame.
 * @beacon_पूर्णांकerval: beacon पूर्णांकerval of the AP in TUs. Only required अगर
 *	&IWL_INITIATOR_AP_FLAGS_TB is set.
 */
काष्ठा iwl_tof_range_req_ap_entry_v6 अणु
	__le32 initiator_ap_flags;
	u8 channel_num;
	u8 क्रमmat_bw;
	u8 ctrl_ch_position;
	u8 fपंचांगr_max_retries;
	u8 bssid[ETH_ALEN];
	__le16 burst_period;
	u8 samples_per_burst;
	u8 num_of_bursts;
	u8 sta_id;
	u8 cipher;
	u8 hltk[HLTK_11AZ_LEN];
	u8 tk[TK_11AZ_LEN];
	__le16 calib[IWL_TOF_BW_NUM];
	__le16 beacon_पूर्णांकerval;
पूर्ण __packed; /* LOCATION_RANGE_REQ_AP_ENTRY_CMD_API_S_VER_6 */

/**
 * काष्ठा iwl_tof_range_req_ap_entry_v7 - AP configuration parameters
 * @initiator_ap_flags: see &क्रमागत iwl_initiator_ap_flags.
 * @channel_num: AP Channel number
 * @क्रमmat_bw: bits 0 - 3: &क्रमागत iwl_location_frame_क्रमmat.
 *             bits 4 - 7: &क्रमागत iwl_location_bw.
 * @ctrl_ch_position: Coding of the control channel position relative to the
 *	center frequency, see iwl_mvm_get_ctrl_pos().
 * @fपंचांगr_max_retries: Max number of retries to send the FTMR in हाल of no
 *	reply from the AP.
 * @bssid: AP's BSSID
 * @burst_period: Recommended value to be sent to the AP. Measurement
 *	periodicity In units of 100ms. ignored अगर num_of_bursts_exp = 0
 * @samples_per_burst: the number of FTMs pairs in single Burst (1-31);
 * @num_of_bursts: Recommended value to be sent to the AP. 2s Exponent of
 *	the number of measurement iterations (min 2^0 = 1, max 2^14)
 * @sta_id: the station id of the AP. Only relevant when associated to the AP,
 *	otherwise should be set to &IWL_MVM_INVALID_STA.
 * @cipher: pairwise cipher suite क्रम secured measurement.
 *          &क्रमागत iwl_location_cipher.
 * @hltk: HLTK to be used क्रम secured 11az measurement
 * @tk: TK to be used क्रम secured 11az measurement
 * @calib: An array of calibration values per FTM rx bandwidth.
 *         If &IWL_INITIATOR_AP_FLAGS_USE_CALIB is set, the fw will use the
 *         calibration value that corresponds to the rx bandwidth of the FTM
 *         frame.
 * @beacon_पूर्णांकerval: beacon पूर्णांकerval of the AP in TUs. Only required अगर
 *	&IWL_INITIATOR_AP_FLAGS_TB is set.
 * @rx_pn: the next expected PN क्रम रक्षित management frames Rx. LE byte
 *	order. Only valid अगर &IWL_INITIATOR_AP_FLAGS_SECURED is set and sta_id
 *	is set to &IWL_MVM_INVALID_STA.
 * @tx_pn: the next PN to use क्रम रक्षित management frames Tx. LE byte
 *	order. Only valid अगर &IWL_INITIATOR_AP_FLAGS_SECURED is set and sta_id
 *	is set to &IWL_MVM_INVALID_STA.
 */
काष्ठा iwl_tof_range_req_ap_entry_v7 अणु
	__le32 initiator_ap_flags;
	u8 channel_num;
	u8 क्रमmat_bw;
	u8 ctrl_ch_position;
	u8 fपंचांगr_max_retries;
	u8 bssid[ETH_ALEN];
	__le16 burst_period;
	u8 samples_per_burst;
	u8 num_of_bursts;
	u8 sta_id;
	u8 cipher;
	u8 hltk[HLTK_11AZ_LEN];
	u8 tk[TK_11AZ_LEN];
	__le16 calib[IWL_TOF_BW_NUM];
	__le16 beacon_पूर्णांकerval;
	u8 rx_pn[IEEE80211_CCMP_PN_LEN];
	u8 tx_pn[IEEE80211_CCMP_PN_LEN];
पूर्ण __packed; /* LOCATION_RANGE_REQ_AP_ENTRY_CMD_API_S_VER_7 */

#घोषणा IWL_LOCATION_MAX_STS_POS	3

/**
 * काष्ठा iwl_tof_range_req_ap_entry_v8 - AP configuration parameters
 * @initiator_ap_flags: see &क्रमागत iwl_initiator_ap_flags.
 * @channel_num: AP Channel number
 * @क्रमmat_bw: bits 0 - 3: &क्रमागत iwl_location_frame_क्रमmat.
 *             bits 4 - 7: &क्रमागत iwl_location_bw.
 * @ctrl_ch_position: Coding of the control channel position relative to the
 *	center frequency, see iwl_mvm_get_ctrl_pos().
 * @fपंचांगr_max_retries: Max number of retries to send the FTMR in हाल of no
 *	reply from the AP.
 * @bssid: AP's BSSID
 * @burst_period: Recommended value to be sent to the AP. Measurement
 *	periodicity In units of 100ms. ignored अगर num_of_bursts_exp = 0
 * @samples_per_burst: the number of FTMs pairs in single Burst (1-31);
 * @num_of_bursts: Recommended value to be sent to the AP. 2s Exponent of
 *	the number of measurement iterations (min 2^0 = 1, max 2^14)
 * @sta_id: the station id of the AP. Only relevant when associated to the AP,
 *	otherwise should be set to &IWL_MVM_INVALID_STA.
 * @cipher: pairwise cipher suite क्रम secured measurement.
 *          &क्रमागत iwl_location_cipher.
 * @hltk: HLTK to be used क्रम secured 11az measurement
 * @tk: TK to be used क्रम secured 11az measurement
 * @calib: An array of calibration values per FTM rx bandwidth.
 *         If &IWL_INITIATOR_AP_FLAGS_USE_CALIB is set, the fw will use the
 *         calibration value that corresponds to the rx bandwidth of the FTM
 *         frame.
 * @beacon_पूर्णांकerval: beacon पूर्णांकerval of the AP in TUs. Only required अगर
 *	&IWL_INITIATOR_AP_FLAGS_TB is set.
 * @rx_pn: the next expected PN क्रम रक्षित management frames Rx. LE byte
 *	order. Only valid अगर &IWL_INITIATOR_AP_FLAGS_SECURED is set and sta_id
 *	is set to &IWL_MVM_INVALID_STA.
 * @tx_pn: the next PN to use क्रम रक्षित management frames Tx. LE byte
 *	order. Only valid अगर &IWL_INITIATOR_AP_FLAGS_SECURED is set and sta_id
 *	is set to &IWL_MVM_INVALID_STA.
 * @r2i_ndp_params: parameters क्रम R2I NDP ranging negotiation.
 *      bits 0 - 2: max LTF repetitions
 *      bits 3 - 5: max number of spatial streams
 *      bits 6 - 7: reserved
 * @i2r_ndp_params: parameters क्रम I2R NDP ranging negotiation.
 *      bits 0 - 2: max LTF repetitions
 *      bits 3 - 5: max number of spatial streams (supported values are < 2)
 *      bits 6 - 7: reserved
 * @r2i_max_total_ltf: R2I Max Total LTFs क्रम NDP ranging negotiation.
 *      One of &क्रमागत ieee80211_range_params_max_total_ltf.
 * @i2r_max_total_ltf: I2R Max Total LTFs क्रम NDP ranging negotiation.
 *      One of &क्रमागत ieee80211_range_params_max_total_ltf.
 */
काष्ठा iwl_tof_range_req_ap_entry_v8 अणु
	__le32 initiator_ap_flags;
	u8 channel_num;
	u8 क्रमmat_bw;
	u8 ctrl_ch_position;
	u8 fपंचांगr_max_retries;
	u8 bssid[ETH_ALEN];
	__le16 burst_period;
	u8 samples_per_burst;
	u8 num_of_bursts;
	u8 sta_id;
	u8 cipher;
	u8 hltk[HLTK_11AZ_LEN];
	u8 tk[TK_11AZ_LEN];
	__le16 calib[IWL_TOF_BW_NUM];
	__le16 beacon_पूर्णांकerval;
	u8 rx_pn[IEEE80211_CCMP_PN_LEN];
	u8 tx_pn[IEEE80211_CCMP_PN_LEN];
	u8 r2i_ndp_params;
	u8 i2r_ndp_params;
	u8 r2i_max_total_ltf;
	u8 i2r_max_total_ltf;
पूर्ण __packed; /* LOCATION_RANGE_REQ_AP_ENTRY_CMD_API_S_VER_8 */

/**
 * क्रमागत iwl_tof_response_mode
 * @IWL_MVM_TOF_RESPONSE_ASAP: report each AP measurement separately as soon as
 *			       possible (not supported क्रम this release)
 * @IWL_MVM_TOF_RESPONSE_TIMEOUT: report all AP measurements as a batch upon
 *				  समयout expiration
 * @IWL_MVM_TOF_RESPONSE_COMPLETE: report all AP measurements as a batch at the
 *				   earlier of: measurements completion / समयout
 *				   expiration.
 */
क्रमागत iwl_tof_response_mode अणु
	IWL_MVM_TOF_RESPONSE_ASAP,
	IWL_MVM_TOF_RESPONSE_TIMEOUT,
	IWL_MVM_TOF_RESPONSE_COMPLETE,
पूर्ण;

/**
 * क्रमागत iwl_tof_initiator_flags
 *
 * @IWL_TOF_INITIATOR_FLAGS_FAST_ALGO_DISABLED: disable fast algo, meaning run
 *	the algo on ant A+B, instead of only one of them.
 * @IWL_TOF_INITIATOR_FLAGS_RX_CHAIN_SEL_A: खोलो RX antenna A क्रम FTMs RX
 * @IWL_TOF_INITIATOR_FLAGS_RX_CHAIN_SEL_B: खोलो RX antenna B क्रम FTMs RX
 * @IWL_TOF_INITIATOR_FLAGS_RX_CHAIN_SEL_C: खोलो RX antenna C क्रम FTMs RX
 * @IWL_TOF_INITIATOR_FLAGS_TX_CHAIN_SEL_A: use antenna A fo TX ACKs during FTM
 * @IWL_TOF_INITIATOR_FLAGS_TX_CHAIN_SEL_B: use antenna B fo TX ACKs during FTM
 * @IWL_TOF_INITIATOR_FLAGS_TX_CHAIN_SEL_C: use antenna C fo TX ACKs during FTM
 * @IWL_TOF_INITIATOR_FLAGS_MACADDR_RANDOM: use अक्रमom mac address क्रम FTM
 * @IWL_TOF_INITIATOR_FLAGS_SPECIFIC_CALIB: use the specअगरic calib value from
 *	the range request command
 * @IWL_TOF_INITIATOR_FLAGS_COMMON_CALIB: use the common calib value from the
 *	ragne request command
 * @IWL_TOF_INITIATOR_FLAGS_NON_ASAP_SUPPORT: support non-asap measurements
 */
क्रमागत iwl_tof_initiator_flags अणु
	IWL_TOF_INITIATOR_FLAGS_FAST_ALGO_DISABLED = BIT(0),
	IWL_TOF_INITIATOR_FLAGS_RX_CHAIN_SEL_A = BIT(1),
	IWL_TOF_INITIATOR_FLAGS_RX_CHAIN_SEL_B = BIT(2),
	IWL_TOF_INITIATOR_FLAGS_RX_CHAIN_SEL_C = BIT(3),
	IWL_TOF_INITIATOR_FLAGS_TX_CHAIN_SEL_A = BIT(4),
	IWL_TOF_INITIATOR_FLAGS_TX_CHAIN_SEL_B = BIT(5),
	IWL_TOF_INITIATOR_FLAGS_TX_CHAIN_SEL_C = BIT(6),
	IWL_TOF_INITIATOR_FLAGS_MACADDR_RANDOM = BIT(7),
	IWL_TOF_INITIATOR_FLAGS_SPECIFIC_CALIB = BIT(15),
	IWL_TOF_INITIATOR_FLAGS_COMMON_CALIB   = BIT(16),
	IWL_TOF_INITIATOR_FLAGS_NON_ASAP_SUPPORT = BIT(20),
पूर्ण; /* LOCATION_RANGE_REQ_CMD_API_S_VER_5 */

#घोषणा IWL_MVM_TOF_MAX_APS 5
#घोषणा IWL_MVM_TOF_MAX_TWO_SIDED_APS 5

/**
 * काष्ठा iwl_tof_range_req_cmd_v5 - start measurement cmd
 * @initiator_flags: see flags @ iwl_tof_initiator_flags
 * @request_id: A Token incremented per request. The same Token will be
 *		sent back in the range response
 * @initiator: 0- NW initiated,  1 - Client Initiated
 * @one_sided_los_disable: '0'- run ML-Algo क्रम both ToF/OneSided,
 *			   '1' - run ML-Algo क्रम ToF only
 * @req_समयout: Requested समयout of the response in units of 100ms.
 *	     This is equivalent to the session समय configured to the
 *	     LMAC in Initiator Request
 * @report_policy: Supported partially क्रम this release: For current release -
 *		   the range report will be uploaded as a batch when पढ़ोy or
 *		   when the session is करोne (successfully / partially).
 *		   one of iwl_tof_response_mode.
 * @reserved0: reserved
 * @num_of_ap: Number of APs to measure (error अगर > IWL_MVM_TOF_MAX_APS)
 * @macaddr_अक्रमom: '0' Use शेष source MAC address (i.e. p2_p),
 *	            '1' Use MAC Address अक्रमomization according to the below
 * @range_req_bssid: ranging request BSSID
 * @macaddr_ढाँचा: MAC address ढाँचा to use क्रम non-अक्रमomized bits
 * @macaddr_mask: Bits set to 0 shall be copied from the MAC address ढाँचा.
 *		  Bits set to 1 shall be अक्रमomized by the UMAC
 * @fपंचांग_rx_chains: Rx chain to खोलो to receive Responder's FTMs (XVT)
 * @fपंचांग_tx_chains: Tx chain to send the ack to the Responder FTM (XVT)
 * @common_calib: The common calib value to inject to this measurement calc
 * @specअगरic_calib: The specअगरic calib value to inject to this measurement calc
 * @ap: per-AP request data
 */
काष्ठा iwl_tof_range_req_cmd_v5 अणु
	__le32 initiator_flags;
	u8 request_id;
	u8 initiator;
	u8 one_sided_los_disable;
	u8 req_समयout;
	u8 report_policy;
	u8 reserved0;
	u8 num_of_ap;
	u8 macaddr_अक्रमom;
	u8 range_req_bssid[ETH_ALEN];
	u8 macaddr_ढाँचा[ETH_ALEN];
	u8 macaddr_mask[ETH_ALEN];
	u8 fपंचांग_rx_chains;
	u8 fपंचांग_tx_chains;
	__le16 common_calib;
	__le16 specअगरic_calib;
	काष्ठा iwl_tof_range_req_ap_entry_v2 ap[IWL_MVM_TOF_MAX_APS];
पूर्ण __packed;
/* LOCATION_RANGE_REQ_CMD_API_S_VER_5 */

/**
 * काष्ठा iwl_tof_range_req_cmd_v7 - start measurement cmd
 * @initiator_flags: see flags @ iwl_tof_initiator_flags
 * @request_id: A Token incremented per request. The same Token will be
 *		sent back in the range response
 * @num_of_ap: Number of APs to measure (error अगर > IWL_MVM_TOF_MAX_APS)
 * @range_req_bssid: ranging request BSSID
 * @macaddr_mask: Bits set to 0 shall be copied from the MAC address ढाँचा.
 *		  Bits set to 1 shall be अक्रमomized by the UMAC
 * @macaddr_ढाँचा: MAC address ढाँचा to use क्रम non-अक्रमomized bits
 * @req_समयout_ms: Requested समयout of the response in units of milliseconds.
 *	This is the session समय क्रम completing the measurement.
 * @tsf_mac_id: report the measurement start समय क्रम each ap in terms of the
 *	TSF of this mac id. 0xff to disable TSF reporting.
 * @common_calib: The common calib value to inject to this measurement calc
 * @specअगरic_calib: The specअगरic calib value to inject to this measurement calc
 * @ap: per-AP request data, see &काष्ठा iwl_tof_range_req_ap_entry_v2.
 */
काष्ठा iwl_tof_range_req_cmd_v7 अणु
	__le32 initiator_flags;
	u8 request_id;
	u8 num_of_ap;
	u8 range_req_bssid[ETH_ALEN];
	u8 macaddr_mask[ETH_ALEN];
	u8 macaddr_ढाँचा[ETH_ALEN];
	__le32 req_समयout_ms;
	__le32 tsf_mac_id;
	__le16 common_calib;
	__le16 specअगरic_calib;
	काष्ठा iwl_tof_range_req_ap_entry_v3 ap[IWL_MVM_TOF_MAX_APS];
पूर्ण __packed; /* LOCATION_RANGE_REQ_CMD_API_S_VER_7 */

/**
 * काष्ठा iwl_tof_range_req_cmd_v8 - start measurement cmd
 * @initiator_flags: see flags @ iwl_tof_initiator_flags
 * @request_id: A Token incremented per request. The same Token will be
 *		sent back in the range response
 * @num_of_ap: Number of APs to measure (error अगर > IWL_MVM_TOF_MAX_APS)
 * @range_req_bssid: ranging request BSSID
 * @macaddr_mask: Bits set to 0 shall be copied from the MAC address ढाँचा.
 *		  Bits set to 1 shall be अक्रमomized by the UMAC
 * @macaddr_ढाँचा: MAC address ढाँचा to use क्रम non-अक्रमomized bits
 * @req_समयout_ms: Requested समयout of the response in units of milliseconds.
 *	This is the session समय क्रम completing the measurement.
 * @tsf_mac_id: report the measurement start समय क्रम each ap in terms of the
 *	TSF of this mac id. 0xff to disable TSF reporting.
 * @common_calib: The common calib value to inject to this measurement calc
 * @specअगरic_calib: The specअगरic calib value to inject to this measurement calc
 * @ap: per-AP request data, see &काष्ठा iwl_tof_range_req_ap_entry_v2.
 */
काष्ठा iwl_tof_range_req_cmd_v8 अणु
	__le32 initiator_flags;
	u8 request_id;
	u8 num_of_ap;
	u8 range_req_bssid[ETH_ALEN];
	u8 macaddr_mask[ETH_ALEN];
	u8 macaddr_ढाँचा[ETH_ALEN];
	__le32 req_समयout_ms;
	__le32 tsf_mac_id;
	__le16 common_calib;
	__le16 specअगरic_calib;
	काष्ठा iwl_tof_range_req_ap_entry_v4 ap[IWL_MVM_TOF_MAX_APS];
पूर्ण __packed; /* LOCATION_RANGE_REQ_CMD_API_S_VER_8 */

/**
 * काष्ठा iwl_tof_range_req_cmd_v9 - start measurement cmd
 * @initiator_flags: see flags @ iwl_tof_initiator_flags
 * @request_id: A Token incremented per request. The same Token will be
 *		sent back in the range response
 * @num_of_ap: Number of APs to measure (error अगर > IWL_MVM_TOF_MAX_APS)
 * @range_req_bssid: ranging request BSSID
 * @macaddr_mask: Bits set to 0 shall be copied from the MAC address ढाँचा.
 *		  Bits set to 1 shall be अक्रमomized by the UMAC
 * @macaddr_ढाँचा: MAC address ढाँचा to use क्रम non-अक्रमomized bits
 * @req_समयout_ms: Requested समयout of the response in units of milliseconds.
 *	This is the session समय क्रम completing the measurement.
 * @tsf_mac_id: report the measurement start समय क्रम each ap in terms of the
 *	TSF of this mac id. 0xff to disable TSF reporting.
 * @ap: per-AP request data, see &काष्ठा iwl_tof_range_req_ap_entry_v2.
 */
काष्ठा iwl_tof_range_req_cmd_v9 अणु
	__le32 initiator_flags;
	u8 request_id;
	u8 num_of_ap;
	u8 range_req_bssid[ETH_ALEN];
	u8 macaddr_mask[ETH_ALEN];
	u8 macaddr_ढाँचा[ETH_ALEN];
	__le32 req_समयout_ms;
	__le32 tsf_mac_id;
	काष्ठा iwl_tof_range_req_ap_entry_v6 ap[IWL_MVM_TOF_MAX_APS];
पूर्ण __packed; /* LOCATION_RANGE_REQ_CMD_API_S_VER_9 */

/**
 * काष्ठा iwl_tof_range_req_cmd_v11 - start measurement cmd
 * @initiator_flags: see flags @ iwl_tof_initiator_flags
 * @request_id: A Token incremented per request. The same Token will be
 *		sent back in the range response
 * @num_of_ap: Number of APs to measure (error अगर > IWL_MVM_TOF_MAX_APS)
 * @range_req_bssid: ranging request BSSID
 * @macaddr_mask: Bits set to 0 shall be copied from the MAC address ढाँचा.
 *		  Bits set to 1 shall be अक्रमomized by the UMAC
 * @macaddr_ढाँचा: MAC address ढाँचा to use क्रम non-अक्रमomized bits
 * @req_समयout_ms: Requested समयout of the response in units of milliseconds.
 *	This is the session समय क्रम completing the measurement.
 * @tsf_mac_id: report the measurement start समय क्रम each ap in terms of the
 *	TSF of this mac id. 0xff to disable TSF reporting.
 * @ap: per-AP request data, see &काष्ठा iwl_tof_range_req_ap_entry_v2.
 */
काष्ठा iwl_tof_range_req_cmd_v11 अणु
	__le32 initiator_flags;
	u8 request_id;
	u8 num_of_ap;
	u8 range_req_bssid[ETH_ALEN];
	u8 macaddr_mask[ETH_ALEN];
	u8 macaddr_ढाँचा[ETH_ALEN];
	__le32 req_समयout_ms;
	__le32 tsf_mac_id;
	काष्ठा iwl_tof_range_req_ap_entry_v7 ap[IWL_MVM_TOF_MAX_APS];
पूर्ण __packed; /* LOCATION_RANGE_REQ_CMD_API_S_VER_11 */

/**
 * काष्ठा iwl_tof_range_req_cmd_v12 - start measurement cmd
 * @initiator_flags: see flags @ iwl_tof_initiator_flags
 * @request_id: A Token incremented per request. The same Token will be
 *		sent back in the range response
 * @num_of_ap: Number of APs to measure (error अगर > IWL_MVM_TOF_MAX_APS)
 * @range_req_bssid: ranging request BSSID
 * @macaddr_mask: Bits set to 0 shall be copied from the MAC address ढाँचा.
 *		  Bits set to 1 shall be अक्रमomized by the UMAC
 * @macaddr_ढाँचा: MAC address ढाँचा to use क्रम non-अक्रमomized bits
 * @req_समयout_ms: Requested समयout of the response in units of milliseconds.
 *	This is the session समय क्रम completing the measurement.
 * @tsf_mac_id: report the measurement start समय क्रम each ap in terms of the
 *	TSF of this mac id. 0xff to disable TSF reporting.
 * @ap: per-AP request data, see &काष्ठा iwl_tof_range_req_ap_entry_v2.
 */
काष्ठा iwl_tof_range_req_cmd_v12 अणु
	__le32 initiator_flags;
	u8 request_id;
	u8 num_of_ap;
	u8 range_req_bssid[ETH_ALEN];
	u8 macaddr_mask[ETH_ALEN];
	u8 macaddr_ढाँचा[ETH_ALEN];
	__le32 req_समयout_ms;
	__le32 tsf_mac_id;
	काष्ठा iwl_tof_range_req_ap_entry_v8 ap[IWL_MVM_TOF_MAX_APS];
पूर्ण __packed; /* LOCATION_RANGE_REQ_CMD_API_S_VER_12 */

/*
 * क्रमागत iwl_tof_range_request_status - status of the sent request
 * @IWL_TOF_RANGE_REQUEST_STATUS_SUCCESSFUL - FW successfully received the
 *	request
 * @IWL_TOF_RANGE_REQUEST_STATUS_BUSY - FW is busy with a previous request, the
 *	sent request will not be handled
 */
क्रमागत iwl_tof_range_request_status अणु
	IWL_TOF_RANGE_REQUEST_STATUS_SUCCESS,
	IWL_TOF_RANGE_REQUEST_STATUS_BUSY,
पूर्ण;

/**
 * क्रमागत iwl_tof_entry_status
 *
 * @IWL_TOF_ENTRY_SUCCESS: successful measurement.
 * @IWL_TOF_ENTRY_GENERAL_FAILURE: General failure.
 * @IWL_TOF_ENTRY_NO_RESPONSE: Responder didn't reply to the request.
 * @IWL_TOF_ENTRY_REQUEST_REJECTED: Responder rejected the request.
 * @IWL_TOF_ENTRY_NOT_SCHEDULED: Time event was scheduled but not called yet.
 * @IWL_TOF_ENTRY_TIMING_MEASURE_TIMEOUT: Time event triggered but no
 *	measurement was completed.
 * @IWL_TOF_ENTRY_TARGET_DIFF_CH_CANNOT_CHANGE: No range due inability to चयन
 *	from the primary channel.
 * @IWL_TOF_ENTRY_RANGE_NOT_SUPPORTED: Device करोesn't support FTM.
 * @IWL_TOF_ENTRY_REQUEST_ABORT_UNKNOWN_REASON: Request पातed due to unknown
 *	reason.
 * @IWL_TOF_ENTRY_LOCATION_INVALID_T1_T4_TIME_STAMP: Failure due to invalid
 *	T1/T4.
 * @IWL_TOF_ENTRY_11MC_PROTOCOL_FAILURE: Failure due to invalid FTM frame
 *	काष्ठाure.
 * @IWL_TOF_ENTRY_REQUEST_CANNOT_SCHED: Request cannot be scheduled.
 * @IWL_TOF_ENTRY_RESPONDER_CANNOT_COLABORATE: Responder cannot serve the
 *	initiator क्रम some period, period supplied in @refusal_period.
 * @IWL_TOF_ENTRY_BAD_REQUEST_ARGS: Bad request arguments.
 * @IWL_TOF_ENTRY_WIFI_NOT_ENABLED: Wअगरi not enabled.
 * @IWL_TOF_ENTRY_RESPONDER_OVERRIDE_PARAMS: Responder override the original
 *	parameters within the current session.
 */
क्रमागत iwl_tof_entry_status अणु
	IWL_TOF_ENTRY_SUCCESS = 0,
	IWL_TOF_ENTRY_GENERAL_FAILURE = 1,
	IWL_TOF_ENTRY_NO_RESPONSE = 2,
	IWL_TOF_ENTRY_REQUEST_REJECTED = 3,
	IWL_TOF_ENTRY_NOT_SCHEDULED = 4,
	IWL_TOF_ENTRY_TIMING_MEASURE_TIMEOUT = 5,
	IWL_TOF_ENTRY_TARGET_DIFF_CH_CANNOT_CHANGE = 6,
	IWL_TOF_ENTRY_RANGE_NOT_SUPPORTED = 7,
	IWL_TOF_ENTRY_REQUEST_ABORT_UNKNOWN_REASON = 8,
	IWL_TOF_ENTRY_LOCATION_INVALID_T1_T4_TIME_STAMP = 9,
	IWL_TOF_ENTRY_11MC_PROTOCOL_FAILURE = 10,
	IWL_TOF_ENTRY_REQUEST_CANNOT_SCHED = 11,
	IWL_TOF_ENTRY_RESPONDER_CANNOT_COLABORATE = 12,
	IWL_TOF_ENTRY_BAD_REQUEST_ARGS = 13,
	IWL_TOF_ENTRY_WIFI_NOT_ENABLED = 14,
	IWL_TOF_ENTRY_RESPONDER_OVERRIDE_PARAMS = 15,
पूर्ण; /* LOCATION_RANGE_RSP_AP_ENTRY_NTFY_API_S_VER_2 */

/**
 * काष्ठा iwl_tof_range_rsp_ap_entry_ntfy_v3 - AP parameters (response)
 * @bssid: BSSID of the AP
 * @measure_status: current APs measurement status, one of
 *	&क्रमागत iwl_tof_entry_status.
 * @measure_bw: Current AP Bandwidth: 0  20MHz, 1  40MHz, 2  80MHz
 * @rtt: The Round Trip Time that took क्रम the last measurement क्रम
 *	current AP [pSec]
 * @rtt_variance: The Variance of the RTT values measured क्रम current AP
 * @rtt_spपढ़ो: The Dअगरference between the maximum and the minimum RTT
 *	values measured क्रम current AP in the current session [pSec]
 * @rssi: RSSI as uploaded in the Channel Estimation notअगरication
 * @rssi_spपढ़ो: The Dअगरference between the maximum and the minimum RSSI values
 *	measured क्रम current AP in the current session
 * @reserved: reserved
 * @refusal_period: refusal period in हाल of
 *	@IWL_TOF_ENTRY_RESPONDER_CANNOT_COLABORATE [sec]
 * @range: Measured range [cm]
 * @range_variance: Measured range variance [cm]
 * @बारtamp: The GP2 Clock [usec] where Channel Estimation notअगरication was
 *	uploaded by the LMAC
 * @t2t3_initiator: as calculated from the algo in the initiator
 * @t1t4_responder: as calculated from the algo in the responder
 * @common_calib: Calib val that was used in क्रम this AP measurement
 * @specअगरic_calib: val that was used in क्रम this AP measurement
 * @papd_calib_output: The result of the tof papd calibration that was injected
 *	पूर्णांकo the algorithm.
 */
काष्ठा iwl_tof_range_rsp_ap_entry_ntfy_v3 अणु
	u8 bssid[ETH_ALEN];
	u8 measure_status;
	u8 measure_bw;
	__le32 rtt;
	__le32 rtt_variance;
	__le32 rtt_spपढ़ो;
	s8 rssi;
	u8 rssi_spपढ़ो;
	u8 reserved;
	u8 refusal_period;
	__le32 range;
	__le32 range_variance;
	__le32 बारtamp;
	__le32 t2t3_initiator;
	__le32 t1t4_responder;
	__le16 common_calib;
	__le16 specअगरic_calib;
	__le32 papd_calib_output;
पूर्ण __packed; /* LOCATION_RANGE_RSP_AP_ETRY_NTFY_API_S_VER_3 */

/**
 * काष्ठा iwl_tof_range_rsp_ap_entry_ntfy_v4 - AP parameters (response)
 * @bssid: BSSID of the AP
 * @measure_status: current APs measurement status, one of
 *	&क्रमागत iwl_tof_entry_status.
 * @measure_bw: Current AP Bandwidth: 0  20MHz, 1  40MHz, 2  80MHz
 * @rtt: The Round Trip Time that took क्रम the last measurement क्रम
 *	current AP [pSec]
 * @rtt_variance: The Variance of the RTT values measured क्रम current AP
 * @rtt_spपढ़ो: The Dअगरference between the maximum and the minimum RTT
 *	values measured क्रम current AP in the current session [pSec]
 * @rssi: RSSI as uploaded in the Channel Estimation notअगरication
 * @rssi_spपढ़ो: The Dअगरference between the maximum and the minimum RSSI values
 *	measured क्रम current AP in the current session
 * @last_burst: 1 अगर no more FTM sessions are scheduled क्रम this responder
 * @refusal_period: refusal period in हाल of
 *	@IWL_TOF_ENTRY_RESPONDER_CANNOT_COLABORATE [sec]
 * @बारtamp: The GP2 Clock [usec] where Channel Estimation notअगरication was
 *	uploaded by the LMAC
 * @start_tsf: measurement start समय in TSF of the mac specअगरied in the range
 *	request
 * @rx_rate_n_flags: rate and flags of the last FTM frame received from this
 *	responder
 * @tx_rate_n_flags: rate and flags of the last ack sent to this responder
 * @t2t3_initiator: as calculated from the algo in the initiator
 * @t1t4_responder: as calculated from the algo in the responder
 * @common_calib: Calib val that was used in क्रम this AP measurement
 * @specअगरic_calib: val that was used in क्रम this AP measurement
 * @papd_calib_output: The result of the tof papd calibration that was injected
 *	पूर्णांकo the algorithm.
 */
काष्ठा iwl_tof_range_rsp_ap_entry_ntfy_v4 अणु
	u8 bssid[ETH_ALEN];
	u8 measure_status;
	u8 measure_bw;
	__le32 rtt;
	__le32 rtt_variance;
	__le32 rtt_spपढ़ो;
	s8 rssi;
	u8 rssi_spपढ़ो;
	u8 last_burst;
	u8 refusal_period;
	__le32 बारtamp;
	__le32 start_tsf;
	__le32 rx_rate_n_flags;
	__le32 tx_rate_n_flags;
	__le32 t2t3_initiator;
	__le32 t1t4_responder;
	__le16 common_calib;
	__le16 specअगरic_calib;
	__le32 papd_calib_output;
पूर्ण __packed; /* LOCATION_RANGE_RSP_AP_ETRY_NTFY_API_S_VER_4 */

/**
 * काष्ठा iwl_tof_range_rsp_ap_entry_ntfy_v5 - AP parameters (response)
 * @bssid: BSSID of the AP
 * @measure_status: current APs measurement status, one of
 *	&क्रमागत iwl_tof_entry_status.
 * @measure_bw: Current AP Bandwidth: 0  20MHz, 1  40MHz, 2  80MHz
 * @rtt: The Round Trip Time that took क्रम the last measurement क्रम
 *	current AP [pSec]
 * @rtt_variance: The Variance of the RTT values measured क्रम current AP
 * @rtt_spपढ़ो: The Dअगरference between the maximum and the minimum RTT
 *	values measured क्रम current AP in the current session [pSec]
 * @rssi: RSSI as uploaded in the Channel Estimation notअगरication
 * @rssi_spपढ़ो: The Dअगरference between the maximum and the minimum RSSI values
 *	measured क्रम current AP in the current session
 * @last_burst: 1 अगर no more FTM sessions are scheduled क्रम this responder
 * @refusal_period: refusal period in हाल of
 *	@IWL_TOF_ENTRY_RESPONDER_CANNOT_COLABORATE [sec]
 * @बारtamp: The GP2 Clock [usec] where Channel Estimation notअगरication was
 *	uploaded by the LMAC
 * @start_tsf: measurement start समय in TSF of the mac specअगरied in the range
 *	request
 * @rx_rate_n_flags: rate and flags of the last FTM frame received from this
 *	responder
 * @tx_rate_n_flags: rate and flags of the last ack sent to this responder
 * @t2t3_initiator: as calculated from the algo in the initiator
 * @t1t4_responder: as calculated from the algo in the responder
 * @common_calib: Calib val that was used in क्रम this AP measurement
 * @specअगरic_calib: val that was used in क्रम this AP measurement
 * @papd_calib_output: The result of the tof papd calibration that was injected
 *	पूर्णांकo the algorithm.
 * @rttConfidence: a value between 0 - 31 that represents the rtt accuracy.
 * @reserved: क्रम alignment
 */
काष्ठा iwl_tof_range_rsp_ap_entry_ntfy_v5 अणु
	u8 bssid[ETH_ALEN];
	u8 measure_status;
	u8 measure_bw;
	__le32 rtt;
	__le32 rtt_variance;
	__le32 rtt_spपढ़ो;
	s8 rssi;
	u8 rssi_spपढ़ो;
	u8 last_burst;
	u8 refusal_period;
	__le32 बारtamp;
	__le32 start_tsf;
	__le32 rx_rate_n_flags;
	__le32 tx_rate_n_flags;
	__le32 t2t3_initiator;
	__le32 t1t4_responder;
	__le16 common_calib;
	__le16 specअगरic_calib;
	__le32 papd_calib_output;
	u8 rttConfidence;
	u8 reserved[3];
पूर्ण __packed; /* LOCATION_RANGE_RSP_AP_ETRY_NTFY_API_S_VER_5 */

/**
 * काष्ठा iwl_tof_range_rsp_ap_entry_ntfy_v6 - AP parameters (response)
 * @bssid: BSSID of the AP
 * @measure_status: current APs measurement status, one of
 *	&क्रमागत iwl_tof_entry_status.
 * @measure_bw: Current AP Bandwidth: 0  20MHz, 1  40MHz, 2  80MHz
 * @rtt: The Round Trip Time that took क्रम the last measurement क्रम
 *	current AP [pSec]
 * @rtt_variance: The Variance of the RTT values measured क्रम current AP
 * @rtt_spपढ़ो: The Dअगरference between the maximum and the minimum RTT
 *	values measured क्रम current AP in the current session [pSec]
 * @rssi: RSSI as uploaded in the Channel Estimation notअगरication
 * @rssi_spपढ़ो: The Dअगरference between the maximum and the minimum RSSI values
 *	measured क्रम current AP in the current session
 * @last_burst: 1 अगर no more FTM sessions are scheduled क्रम this responder
 * @refusal_period: refusal period in हाल of
 *	@IWL_TOF_ENTRY_RESPONDER_CANNOT_COLABORATE [sec]
 * @बारtamp: The GP2 Clock [usec] where Channel Estimation notअगरication was
 *	uploaded by the LMAC
 * @start_tsf: measurement start समय in TSF of the mac specअगरied in the range
 *	request
 * @rx_rate_n_flags: rate and flags of the last FTM frame received from this
 *	responder
 * @tx_rate_n_flags: rate and flags of the last ack sent to this responder
 * @t2t3_initiator: as calculated from the algo in the initiator
 * @t1t4_responder: as calculated from the algo in the responder
 * @common_calib: Calib val that was used in क्रम this AP measurement
 * @specअगरic_calib: val that was used in क्रम this AP measurement
 * @papd_calib_output: The result of the tof papd calibration that was injected
 *	पूर्णांकo the algorithm.
 * @rttConfidence: a value between 0 - 31 that represents the rtt accuracy.
 * @reserved: क्रम alignment
 * @rx_pn: the last PN used क्रम this responder Rx in हाल PMF is configured in
 *	LE byte order.
 * @tx_pn: the last PN used क्रम this responder Tx in हाल PMF is configured in
 *	LE byte order.
 */
काष्ठा iwl_tof_range_rsp_ap_entry_ntfy_v6 अणु
	u8 bssid[ETH_ALEN];
	u8 measure_status;
	u8 measure_bw;
	__le32 rtt;
	__le32 rtt_variance;
	__le32 rtt_spपढ़ो;
	s8 rssi;
	u8 rssi_spपढ़ो;
	u8 last_burst;
	u8 refusal_period;
	__le32 बारtamp;
	__le32 start_tsf;
	__le32 rx_rate_n_flags;
	__le32 tx_rate_n_flags;
	__le32 t2t3_initiator;
	__le32 t1t4_responder;
	__le16 common_calib;
	__le16 specअगरic_calib;
	__le32 papd_calib_output;
	u8 rttConfidence;
	u8 reserved[3];
	u8 rx_pn[IEEE80211_CCMP_PN_LEN];
	u8 tx_pn[IEEE80211_CCMP_PN_LEN];
पूर्ण __packed; /* LOCATION_RANGE_RSP_AP_ETRY_NTFY_API_S_VER_6 */

/**
 * क्रमागत iwl_tof_response_status - tof response status
 *
 * @IWL_TOF_RESPONSE_SUCCESS: successful range.
 * @IWL_TOF_RESPONSE_TIMEOUT: request पातed due to समयout expiration.
 *	partial result of ranges करोne so far is included in the response.
 * @IWL_TOF_RESPONSE_ABORTED: Measurement पातed by command.
 * @IWL_TOF_RESPONSE_FAILED: Measurement request command failed.
 */
क्रमागत iwl_tof_response_status अणु
	IWL_TOF_RESPONSE_SUCCESS = 0,
	IWL_TOF_RESPONSE_TIMEOUT = 1,
	IWL_TOF_RESPONSE_ABORTED = 4,
	IWL_TOF_RESPONSE_FAILED  = 5,
पूर्ण; /* LOCATION_RNG_RSP_STATUS */

/**
 * काष्ठा iwl_tof_range_rsp_ntfy_v5 - ranging response notअगरication
 * @request_id: A Token ID of the corresponding Range request
 * @request_status: status of current measurement session, one of
 *	&क्रमागत iwl_tof_response_status.
 * @last_in_batch: reprot policy (when not all responses are uploaded at once)
 * @num_of_aps: Number of APs to measure (error अगर > IWL_MVM_TOF_MAX_APS)
 * @ap: per-AP data
 */
काष्ठा iwl_tof_range_rsp_ntfy_v5 अणु
	u8 request_id;
	u8 request_status;
	u8 last_in_batch;
	u8 num_of_aps;
	काष्ठा iwl_tof_range_rsp_ap_entry_ntfy_v3 ap[IWL_MVM_TOF_MAX_APS];
पूर्ण __packed; /* LOCATION_RANGE_RSP_NTFY_API_S_VER_5 */

/**
 * काष्ठा iwl_tof_range_rsp_ntfy_v6 - ranging response notअगरication
 * @request_id: A Token ID of the corresponding Range request
 * @num_of_aps: Number of APs results
 * @last_report: 1 अगर no more FTM sessions are scheduled, 0 otherwise.
 * @reserved: reserved
 * @ap: per-AP data
 */
काष्ठा iwl_tof_range_rsp_ntfy_v6 अणु
	u8 request_id;
	u8 num_of_aps;
	u8 last_report;
	u8 reserved;
	काष्ठा iwl_tof_range_rsp_ap_entry_ntfy_v4 ap[IWL_MVM_TOF_MAX_APS];
पूर्ण __packed; /* LOCATION_RANGE_RSP_NTFY_API_S_VER_6 */

/**
 * काष्ठा iwl_tof_range_rsp_ntfy_v7 - ranging response notअगरication
 * @request_id: A Token ID of the corresponding Range request
 * @num_of_aps: Number of APs results
 * @last_report: 1 अगर no more FTM sessions are scheduled, 0 otherwise.
 * @reserved: reserved
 * @ap: per-AP data
 */
काष्ठा iwl_tof_range_rsp_ntfy_v7 अणु
	u8 request_id;
	u8 num_of_aps;
	u8 last_report;
	u8 reserved;
	काष्ठा iwl_tof_range_rsp_ap_entry_ntfy_v5 ap[IWL_MVM_TOF_MAX_APS];
पूर्ण __packed; /* LOCATION_RANGE_RSP_NTFY_API_S_VER_7 */

/**
 * काष्ठा iwl_tof_range_rsp_ntfy_v8 - ranging response notअगरication
 * @request_id: A Token ID of the corresponding Range request
 * @num_of_aps: Number of APs results
 * @last_report: 1 अगर no more FTM sessions are scheduled, 0 otherwise.
 * @reserved: reserved
 * @ap: per-AP data
 */
काष्ठा iwl_tof_range_rsp_ntfy_v8 अणु
	u8 request_id;
	u8 num_of_aps;
	u8 last_report;
	u8 reserved;
	काष्ठा iwl_tof_range_rsp_ap_entry_ntfy_v6 ap[IWL_MVM_TOF_MAX_APS];
पूर्ण __packed; /* LOCATION_RANGE_RSP_NTFY_API_S_VER_8 */

#घोषणा IWL_MVM_TOF_MCSI_BUF_SIZE  (245)
/**
 * काष्ठा iwl_tof_mcsi_notअगर - used क्रम debug
 * @token: token ID क्रम the current session
 * @role: '0' - initiator, '1' - responder
 * @reserved: reserved
 * @initiator_bssid: initiator machine
 * @responder_bssid: responder machine
 * @mcsi_buffer: debug data
 */
काष्ठा iwl_tof_mcsi_notअगर अणु
	u8 token;
	u8 role;
	__le16 reserved;
	u8 initiator_bssid[ETH_ALEN];
	u8 responder_bssid[ETH_ALEN];
	u8 mcsi_buffer[IWL_MVM_TOF_MCSI_BUF_SIZE * 4];
पूर्ण __packed;

/**
 * काष्ठा iwl_tof_range_पात_cmd
 * @request_id: corresponds to a range request
 * @reserved: reserved
 */
काष्ठा iwl_tof_range_पात_cmd अणु
	u8 request_id;
	u8 reserved[3];
पूर्ण __packed;

क्रमागत fपंचांग_responder_stats_flags अणु
	FTM_RESP_STAT_NON_ASAP_STARTED = BIT(0),
	FTM_RESP_STAT_NON_ASAP_IN_WIN = BIT(1),
	FTM_RESP_STAT_NON_ASAP_OUT_WIN = BIT(2),
	FTM_RESP_STAT_TRIGGER_DUP = BIT(3),
	FTM_RESP_STAT_DUP = BIT(4),
	FTM_RESP_STAT_DUP_IN_WIN = BIT(5),
	FTM_RESP_STAT_DUP_OUT_WIN = BIT(6),
	FTM_RESP_STAT_SCHED_SUCCESS = BIT(7),
	FTM_RESP_STAT_ASAP_REQ = BIT(8),
	FTM_RESP_STAT_NON_ASAP_REQ = BIT(9),
	FTM_RESP_STAT_ASAP_RESP = BIT(10),
	FTM_RESP_STAT_NON_ASAP_RESP = BIT(11),
	FTM_RESP_STAT_FAIL_INITIATOR_INACTIVE = BIT(12),
	FTM_RESP_STAT_FAIL_INITIATOR_OUT_WIN = BIT(13),
	FTM_RESP_STAT_FAIL_INITIATOR_RETRY_LIM = BIT(14),
	FTM_RESP_STAT_FAIL_NEXT_SERVED = BIT(15),
	FTM_RESP_STAT_FAIL_TRIGGER_ERR = BIT(16),
	FTM_RESP_STAT_FAIL_GC = BIT(17),
	FTM_RESP_STAT_SUCCESS = BIT(18),
	FTM_RESP_STAT_INTEL_IE = BIT(19),
	FTM_RESP_STAT_INITIATOR_ACTIVE = BIT(20),
	FTM_RESP_STAT_MEASUREMENTS_AVAILABLE = BIT(21),
	FTM_RESP_STAT_TRIGGER_UNKNOWN = BIT(22),
	FTM_RESP_STAT_PROCESS_FAIL = BIT(23),
	FTM_RESP_STAT_ACK = BIT(24),
	FTM_RESP_STAT_NACK = BIT(25),
	FTM_RESP_STAT_INVALID_INITIATOR_ID = BIT(26),
	FTM_RESP_STAT_TIMER_MIN_DELTA = BIT(27),
	FTM_RESP_STAT_INITIATOR_REMOVED = BIT(28),
	FTM_RESP_STAT_INITIATOR_ADDED = BIT(29),
	FTM_RESP_STAT_ERR_LIST_FULL = BIT(30),
	FTM_RESP_STAT_INITIATOR_SCHED_NOW = BIT(31),
पूर्ण; /* RESP_IND_E */

/**
 * काष्ठा iwl_fपंचांग_responder_stats - FTM responder statistics
 * @addr: initiator address
 * @success_fपंचांग: number of successful fपंचांग frames
 * @fपंचांग_per_burst: num of FTM frames that were received
 * @flags: &क्रमागत fपंचांग_responder_stats_flags
 * @duration: actual duration of FTM
 * @allocated_duration: समय that was allocated क्रम this FTM session
 * @bw: FTM request bandwidth
 * @rate: FTM request rate
 * @reserved: क्रम alingment and future use
 */
काष्ठा iwl_fपंचांग_responder_stats अणु
	u8 addr[ETH_ALEN];
	u8 success_fपंचांग;
	u8 fपंचांग_per_burst;
	__le32 flags;
	__le32 duration;
	__le32 allocated_duration;
	u8 bw;
	u8 rate;
	__le16 reserved;
पूर्ण __packed; /* TOF_RESPONDER_STATISTICS_NTFY_S_VER_2 */

#घोषणा IWL_CSI_MAX_EXPECTED_CHUNKS		16

#घोषणा IWL_CSI_CHUNK_CTL_NUM_MASK_VER_1	0x0003
#घोषणा IWL_CSI_CHUNK_CTL_IDX_MASK_VER_1	0x000c

#घोषणा IWL_CSI_CHUNK_CTL_NUM_MASK_VER_2	0x00ff
#घोषणा IWL_CSI_CHUNK_CTL_IDX_MASK_VER_2	0xff00

काष्ठा iwl_csi_chunk_notअगरication अणु
	__le32 token;
	__le16 seq;
	__le16 ctl;
	__le32 size;
	u8 data[];
पूर्ण __packed; /* CSI_CHUNKS_HDR_NTFY_API_S_VER_1/VER_2 */

#पूर्ण_अगर /* __iwl_fw_api_location_h__ */
