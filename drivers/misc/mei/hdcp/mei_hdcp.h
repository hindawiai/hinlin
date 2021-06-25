<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright तऊ 2019 Intel Corporation
 *
 * Authors:
 * Ramalingam C <ramalingam.c@पूर्णांकel.com>
 */

#अगर_अघोषित __MEI_HDCP_H__
#घोषणा __MEI_HDCP_H__

#समावेश <drm/drm_hdcp.h>

/* me_hdcp_status: Enumeration of all HDCP Status Codes */
क्रमागत me_hdcp_status अणु
	ME_HDCP_STATUS_SUCCESS			= 0x0000,

	/* WiDi Generic Status Codes */
	ME_HDCP_STATUS_INTERNAL_ERROR		= 0x1000,
	ME_HDCP_STATUS_UNKNOWN_ERROR		= 0x1001,
	ME_HDCP_STATUS_INCORRECT_API_VERSION	= 0x1002,
	ME_HDCP_STATUS_INVALID_FUNCTION		= 0x1003,
	ME_HDCP_STATUS_INVALID_BUFFER_LENGTH	= 0x1004,
	ME_HDCP_STATUS_INVALID_PARAMS		= 0x1005,
	ME_HDCP_STATUS_AUTHENTICATION_FAILED	= 0x1006,

	/* WiDi Status Codes */
	ME_HDCP_INVALID_SESSION_STATE		= 0x6000,
	ME_HDCP_SRM_FRAGMENT_UNEXPECTED		= 0x6001,
	ME_HDCP_SRM_INVALID_LENGTH		= 0x6002,
	ME_HDCP_SRM_FRAGMENT_OFFSET_INVALID	= 0x6003,
	ME_HDCP_SRM_VERIFICATION_FAILED		= 0x6004,
	ME_HDCP_SRM_VERSION_TOO_OLD		= 0x6005,
	ME_HDCP_RX_CERT_VERIFICATION_FAILED	= 0x6006,
	ME_HDCP_RX_REVOKED			= 0x6007,
	ME_HDCP_H_VERIFICATION_FAILED		= 0x6008,
	ME_HDCP_REPEATER_CHECK_UNEXPECTED	= 0x6009,
	ME_HDCP_TOPOLOGY_MAX_EXCEEDED		= 0x600A,
	ME_HDCP_V_VERIFICATION_FAILED		= 0x600B,
	ME_HDCP_L_VERIFICATION_FAILED		= 0x600C,
	ME_HDCP_STREAM_KEY_ALLOC_FAILED		= 0x600D,
	ME_HDCP_BASE_KEY_RESET_FAILED		= 0x600E,
	ME_HDCP_NONCE_GENERATION_FAILED		= 0x600F,
	ME_HDCP_STATUS_INVALID_E_KEY_STATE	= 0x6010,
	ME_HDCP_STATUS_INVALID_CS_ICV		= 0x6011,
	ME_HDCP_STATUS_INVALID_KB_KEY_STATE	= 0x6012,
	ME_HDCP_STATUS_INVALID_PAVP_MODE_ICV	= 0x6013,
	ME_HDCP_STATUS_INVALID_PAVP_MODE	= 0x6014,
	ME_HDCP_STATUS_LC_MAX_ATTEMPTS		= 0x6015,

	/* New status क्रम HDCP 2.1 */
	ME_HDCP_STATUS_MISMATCH_IN_M		= 0x6016,

	/* New status code क्रम HDCP 2.2 Rx */
	ME_HDCP_STATUS_RX_PROV_NOT_ALLOWED	= 0x6017,
	ME_HDCP_STATUS_RX_PROV_WRONG_SUBJECT	= 0x6018,
	ME_HDCP_RX_NEEDS_PROVISIONING		= 0x6019,
	ME_HDCP_BKSV_ICV_AUTH_FAILED		= 0x6020,
	ME_HDCP_STATUS_INVALID_STREAM_ID	= 0x6021,
	ME_HDCP_STATUS_CHAIN_NOT_INITIALIZED	= 0x6022,
	ME_HDCP_FAIL_NOT_EXPECTED		= 0x6023,
	ME_HDCP_FAIL_HDCP_OFF			= 0x6024,
	ME_HDCP_FAIL_INVALID_PAVP_MEMORY_MODE	= 0x6025,
	ME_HDCP_FAIL_AES_ECB_FAILURE		= 0x6026,
	ME_HDCP_FEATURE_NOT_SUPPORTED		= 0x6027,
	ME_HDCP_DMA_READ_ERROR			= 0x6028,
	ME_HDCP_DMA_WRITE_ERROR			= 0x6029,
	ME_HDCP_FAIL_INVALID_PACKET_SIZE	= 0x6030,
	ME_HDCP_H264_PARSING_ERROR		= 0x6031,
	ME_HDCP_HDCP2_ERRATA_VIDEO_VIOLATION	= 0x6032,
	ME_HDCP_HDCP2_ERRATA_AUDIO_VIOLATION	= 0x6033,
	ME_HDCP_TX_ACTIVE_ERROR			= 0x6034,
	ME_HDCP_MODE_CHANGE_ERROR		= 0x6035,
	ME_HDCP_STREAM_TYPE_ERROR		= 0x6036,
	ME_HDCP_STREAM_MANAGE_NOT_POSSIBLE	= 0x6037,

	ME_HDCP_STATUS_PORT_INVALID_COMMAND	= 0x6038,
	ME_HDCP_STATUS_UNSUPPORTED_PROTOCOL	= 0x6039,
	ME_HDCP_STATUS_INVALID_PORT_INDEX	= 0x603a,
	ME_HDCP_STATUS_TX_AUTH_NEEDED		= 0x603b,
	ME_HDCP_STATUS_NOT_INTEGRATED_PORT	= 0x603c,
	ME_HDCP_STATUS_SESSION_MAX_REACHED	= 0x603d,

	/* hdcp capable bit is not set in rx_caps(error is unique to DP) */
	ME_HDCP_STATUS_NOT_HDCP_CAPABLE		= 0x6041,

	ME_HDCP_STATUS_INVALID_STREAM_COUNT	= 0x6042,
पूर्ण;

#घोषणा HDCP_API_VERSION				0x00010000

#घोषणा HDCP_M_LEN					16
#घोषणा HDCP_KH_LEN					16

/* Payload Buffer size(Excluding Header) क्रम CMDs and corresponding response */
/* Wired_Tx_AKE  */
#घोषणा	WIRED_CMD_BUF_LEN_INITIATE_HDCP2_SESSION_IN	(4 + 1)
#घोषणा	WIRED_CMD_BUF_LEN_INITIATE_HDCP2_SESSION_OUT	(4 + 8 + 3)

#घोषणा	WIRED_CMD_BUF_LEN_VERIFY_RECEIVER_CERT_IN	(4 + 522 + 8 + 3)
#घोषणा	WIRED_CMD_BUF_LEN_VERIFY_RECEIVER_CERT_MIN_OUT	(4 + 1 + 3 + 16 + 16)
#घोषणा	WIRED_CMD_BUF_LEN_VERIFY_RECEIVER_CERT_MAX_OUT	(4 + 1 + 3 + 128)

#घोषणा	WIRED_CMD_BUF_LEN_AKE_SEND_HPRIME_IN		(4 + 32)
#घोषणा	WIRED_CMD_BUF_LEN_AKE_SEND_HPRIME_OUT		(4)

#घोषणा	WIRED_CMD_BUF_LEN_SEND_PAIRING_INFO_IN		(4 + 16)
#घोषणा	WIRED_CMD_BUF_LEN_SEND_PAIRING_INFO_OUT		(4)

#घोषणा	WIRED_CMD_BUF_LEN_CLOSE_SESSION_IN		(4)
#घोषणा	WIRED_CMD_BUF_LEN_CLOSE_SESSION_OUT		(4)

/* Wired_Tx_LC */
#घोषणा	WIRED_CMD_BUF_LEN_INIT_LOCALITY_CHECK_IN	(4)
#घोषणा	WIRED_CMD_BUF_LEN_INIT_LOCALITY_CHECK_OUT	(4 + 8)

#घोषणा	WIRED_CMD_BUF_LEN_VALIDATE_LOCALITY_IN		(4 + 32)
#घोषणा	WIRED_CMD_BUF_LEN_VALIDATE_LOCALITY_OUT		(4)

/* Wired_Tx_SKE */
#घोषणा	WIRED_CMD_BUF_LEN_GET_SESSION_KEY_IN		(4)
#घोषणा	WIRED_CMD_BUF_LEN_GET_SESSION_KEY_OUT		(4 + 16 + 8)

/* Wired_Tx_SKE */
#घोषणा	WIRED_CMD_BUF_LEN_ENABLE_AUTH_IN		(4 + 1)
#घोषणा	WIRED_CMD_BUF_LEN_ENABLE_AUTH_OUT		(4)

/* Wired_Tx_Repeater */
#घोषणा	WIRED_CMD_BUF_LEN_VERIFY_REPEATER_IN		(4 + 2 + 3 + 16 + 155)
#घोषणा	WIRED_CMD_BUF_LEN_VERIFY_REPEATER_OUT		(4 + 1 + 16)

#घोषणा	WIRED_CMD_BUF_LEN_REPEATER_AUTH_STREAM_REQ_MIN_IN	(4 + 3 + \
								32 + 2 + 2)

#घोषणा	WIRED_CMD_BUF_LEN_REPEATER_AUTH_STREAM_REQ_OUT		(4)

/* hdcp_command_id: Enumeration of all WIRED HDCP Command IDs */
क्रमागत hdcp_command_id अणु
	_WIDI_COMMAND_BASE		= 0x00030000,
	WIDI_INITIATE_HDCP2_SESSION	= _WIDI_COMMAND_BASE,
	HDCP_GET_SRM_STATUS,
	HDCP_SEND_SRM_FRAGMENT,

	/* The wired HDCP Tx commands */
	_WIRED_COMMAND_BASE		= 0x00031000,
	WIRED_INITIATE_HDCP2_SESSION	= _WIRED_COMMAND_BASE,
	WIRED_VERIFY_RECEIVER_CERT,
	WIRED_AKE_SEND_HPRIME,
	WIRED_AKE_SEND_PAIRING_INFO,
	WIRED_INIT_LOCALITY_CHECK,
	WIRED_VALIDATE_LOCALITY,
	WIRED_GET_SESSION_KEY,
	WIRED_ENABLE_AUTH,
	WIRED_VERIFY_REPEATER,
	WIRED_REPEATER_AUTH_STREAM_REQ,
	WIRED_CLOSE_SESSION,

	_WIRED_COMMANDS_COUNT,
पूर्ण;

जोड़ encrypted_buff अणु
	u8		e_kpub_km[HDCP_2_2_E_KPUB_KM_LEN];
	u8		e_kh_km_m[HDCP_2_2_E_KH_KM_M_LEN];
	काष्ठा अणु
		u8	e_kh_km[HDCP_KH_LEN];
		u8	m[HDCP_M_LEN];
	पूर्ण __packed;
पूर्ण;

/* HDCP HECI message header. All header values are little endian. */
काष्ठा hdcp_cmd_header अणु
	u32			api_version;
	u32			command_id;
	क्रमागत me_hdcp_status	status;
	/* Length of the HECI message (excluding the header) */
	u32			buffer_len;
पूर्ण __packed;

/* Empty command request or response. No data follows the header. */
काष्ठा hdcp_cmd_no_data अणु
	काष्ठा hdcp_cmd_header header;
पूर्ण __packed;

/* Uniquely identअगरies the hdcp port being addressed क्रम a given command. */
काष्ठा hdcp_port_id अणु
	u8	पूर्णांकegrated_port_type;
	/* physical_port is used until Gen11.5. Must be zero क्रम Gen11.5+ */
	u8	physical_port;
	/* attached_transcoder is क्रम Gen11.5+. Set to zero क्रम <Gen11.5 */
	u8	attached_transcoder;
	u8	reserved;
पूर्ण __packed;

/*
 * Data काष्ठाures क्रम पूर्णांकegrated wired HDCP2 Tx in
 * support of the AKE protocol
 */
/* HECI काष्ठा क्रम पूर्णांकegrated wired HDCP Tx session initiation. */
काष्ठा wired_cmd_initiate_hdcp2_session_in अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
	u8			protocol; /* क्रम HDMI vs DP */
पूर्ण __packed;

काष्ठा wired_cmd_initiate_hdcp2_session_out अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
	u8			r_tx[HDCP_2_2_RTX_LEN];
	काष्ठा hdcp2_tx_caps	tx_caps;
पूर्ण __packed;

/* HECI काष्ठा क्रम ending an पूर्णांकegrated wired HDCP Tx session. */
काष्ठा wired_cmd_बंद_session_in अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
पूर्ण __packed;

काष्ठा wired_cmd_बंद_session_out अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
पूर्ण __packed;

/* HECI काष्ठा क्रम पूर्णांकegrated wired HDCP Tx Rx Cert verअगरication. */
काष्ठा wired_cmd_verअगरy_receiver_cert_in अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
	काष्ठा hdcp2_cert_rx	cert_rx;
	u8			r_rx[HDCP_2_2_RRX_LEN];
	u8			rx_caps[HDCP_2_2_RXCAPS_LEN];
पूर्ण __packed;

काष्ठा wired_cmd_verअगरy_receiver_cert_out अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
	u8			km_stored;
	u8			reserved[3];
	जोड़ encrypted_buff	ekm_buff;
पूर्ण __packed;

/* HECI काष्ठा क्रम verअगरication of Rx's Hprime in a HDCP Tx session */
काष्ठा wired_cmd_ake_send_hprime_in अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
	u8			h_prime[HDCP_2_2_H_PRIME_LEN];
पूर्ण __packed;

काष्ठा wired_cmd_ake_send_hprime_out अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
पूर्ण __packed;

/*
 * HECI काष्ठा क्रम sending in AKE pairing data generated by the Rx in an
 * पूर्णांकegrated wired HDCP Tx session.
 */
काष्ठा wired_cmd_ake_send_pairing_info_in अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
	u8			e_kh_km[HDCP_2_2_E_KH_KM_LEN];
पूर्ण __packed;

काष्ठा wired_cmd_ake_send_pairing_info_out अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
पूर्ण __packed;

/* Data काष्ठाures क्रम पूर्णांकegrated wired HDCP2 Tx in support of the LC protocol*/
/*
 * HECI काष्ठा क्रम initiating locality check with an
 * पूर्णांकegrated wired HDCP Tx session.
 */
काष्ठा wired_cmd_init_locality_check_in अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
पूर्ण __packed;

काष्ठा wired_cmd_init_locality_check_out अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
	u8			r_n[HDCP_2_2_RN_LEN];
पूर्ण __packed;

/*
 * HECI काष्ठा क्रम validating an Rx's LPrime value in an
 * पूर्णांकegrated wired HDCP Tx session.
 */
काष्ठा wired_cmd_validate_locality_in अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
	u8			l_prime[HDCP_2_2_L_PRIME_LEN];
पूर्ण __packed;

काष्ठा wired_cmd_validate_locality_out अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
पूर्ण __packed;

/*
 * Data काष्ठाures क्रम पूर्णांकegrated wired HDCP2 Tx in support of the
 * SKE protocol
 */
/* HECI काष्ठा क्रम creating session key */
काष्ठा wired_cmd_get_session_key_in अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
पूर्ण __packed;

काष्ठा wired_cmd_get_session_key_out अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
	u8			e_dkey_ks[HDCP_2_2_E_DKEY_KS_LEN];
	u8			r_iv[HDCP_2_2_RIV_LEN];
पूर्ण __packed;

/* HECI काष्ठा क्रम the Tx enable authentication command */
काष्ठा wired_cmd_enable_auth_in अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
	u8			stream_type;
पूर्ण __packed;

काष्ठा wired_cmd_enable_auth_out अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
पूर्ण __packed;

/*
 * Data काष्ठाures क्रम पूर्णांकegrated wired HDCP2 Tx in support of
 * the repeater protocols
 */
/*
 * HECI काष्ठा क्रम verअगरying the करोwnstream repeater's HDCP topology in an
 * पूर्णांकegrated wired HDCP Tx session.
 */
काष्ठा wired_cmd_verअगरy_repeater_in अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
	u8			rx_info[HDCP_2_2_RXINFO_LEN];
	u8			seq_num_v[HDCP_2_2_SEQ_NUM_LEN];
	u8			v_prime[HDCP_2_2_V_PRIME_HALF_LEN];
	u8			receiver_ids[HDCP_2_2_RECEIVER_IDS_MAX_LEN];
पूर्ण __packed;

काष्ठा wired_cmd_verअगरy_repeater_out अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
	u8			content_type_supported;
	u8			v[HDCP_2_2_V_PRIME_HALF_LEN];
पूर्ण __packed;

/*
 * HECI काष्ठा in support of stream management in an
 * पूर्णांकegrated wired HDCP Tx session.
 */
काष्ठा wired_cmd_repeater_auth_stream_req_in अणु
	काष्ठा hdcp_cmd_header		header;
	काष्ठा hdcp_port_id		port;
	u8				seq_num_m[HDCP_2_2_SEQ_NUM_LEN];
	u8				m_prime[HDCP_2_2_MPRIME_LEN];
	__be16				k;
	काष्ठा hdcp2_streamid_type	streams[];
पूर्ण __packed;

काष्ठा wired_cmd_repeater_auth_stream_req_out अणु
	काष्ठा hdcp_cmd_header	header;
	काष्ठा hdcp_port_id	port;
पूर्ण __packed;
#पूर्ण_अगर /* __MEI_HDCP_H__ */
