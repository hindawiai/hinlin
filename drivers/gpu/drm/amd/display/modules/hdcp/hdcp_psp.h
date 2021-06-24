<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित MODULES_HDCP_HDCP_PSP_H_
#घोषणा MODULES_HDCP_HDCP_PSP_H_

/*
 * NOTE: These parameters are a one-to-one copy of the
 * parameters required by PSP
 */
क्रमागत bgd_security_hdcp_encryption_level अणु
	HDCP_ENCRYPTION_LEVEL__INVALID = 0,
	HDCP_ENCRYPTION_LEVEL__OFF,
	HDCP_ENCRYPTION_LEVEL__ON
पूर्ण;

क्रमागत bgd_security_hdcp2_content_type अणु
	HDCP2_CONTENT_TYPE__INVALID = 0,
	HDCP2_CONTENT_TYPE__TYPE0,
	HDCP2_CONTENT_TYPE__TYPE1
पूर्ण;
क्रमागत ta_dपंचांग_command अणु
	TA_DTM_COMMAND__UNUSED_1 = 1,
	TA_DTM_COMMAND__TOPOLOGY_UPDATE_V2,
	TA_DTM_COMMAND__TOPOLOGY_ASSR_ENABLE
पूर्ण;

/* DTM related क्रमागतerations */
/**********************************************************/

क्रमागत ta_dपंचांग_status अणु
	TA_DTM_STATUS__SUCCESS = 0x00,
	TA_DTM_STATUS__GENERIC_FAILURE = 0x01,
	TA_DTM_STATUS__INVALID_PARAMETER = 0x02,
	TA_DTM_STATUS__शून्य_POINTER = 0x3
पूर्ण;

/* input/output काष्ठाures क्रम DTM commands */
/**********************************************************/
/**
 * Input काष्ठाures
 */
क्रमागत ta_dपंचांग_hdcp_version_max_supported अणु
	TA_DTM_HDCP_VERSION_MAX_SUPPORTED__NONE = 0,
	TA_DTM_HDCP_VERSION_MAX_SUPPORTED__1_x = 10,
	TA_DTM_HDCP_VERSION_MAX_SUPPORTED__2_0 = 20,
	TA_DTM_HDCP_VERSION_MAX_SUPPORTED__2_1 = 21,
	TA_DTM_HDCP_VERSION_MAX_SUPPORTED__2_2 = 22,
	TA_DTM_HDCP_VERSION_MAX_SUPPORTED__2_3 = 23
पूर्ण;

काष्ठा ta_dपंचांग_topology_update_input_v2 अणु
	/* display handle is unique across the driver and is used to identअगरy a display */
	/* क्रम all security पूर्णांकerfaces which reference displays such as HDCP */
	uपूर्णांक32_t display_handle;
	uपूर्णांक32_t is_active;
	uपूर्णांक32_t is_miracast;
	uपूर्णांक32_t controller;
	uपूर्णांक32_t ddc_line;
	uपूर्णांक32_t dig_be;
	uपूर्णांक32_t dig_fe;
	uपूर्णांक32_t dp_mst_vcid;
	uपूर्णांक32_t is_assr;
	uपूर्णांक32_t max_hdcp_supported_version;
पूर्ण;

काष्ठा ta_dपंचांग_topology_assr_enable अणु
	uपूर्णांक32_t display_topology_dig_be_index;
पूर्ण;

/**
 * Output काष्ठाures
 */

/* No output काष्ठाures yet */

जोड़ ta_dपंचांग_cmd_input अणु
	काष्ठा ta_dपंचांग_topology_update_input_v2 topology_update_v2;
	काष्ठा ta_dपंचांग_topology_assr_enable topology_assr_enable;
पूर्ण;

जोड़ ta_dपंचांग_cmd_output अणु
	uपूर्णांक32_t reserved;
पूर्ण;

काष्ठा ta_dपंचांग_shared_memory अणु
	uपूर्णांक32_t cmd_id;
	uपूर्णांक32_t resp_id;
	क्रमागत ta_dपंचांग_status dपंचांग_status;
	uपूर्णांक32_t reserved;
	जोड़ ta_dपंचांग_cmd_input dपंचांग_in_message;
	जोड़ ta_dपंचांग_cmd_output dपंचांग_out_message;
पूर्ण;

पूर्णांक psp_cmd_submit_buf(काष्ठा psp_context *psp, काष्ठा amdgpu_firmware_info *ucode, काष्ठा psp_gfx_cmd_resp *cmd,
		uपूर्णांक64_t fence_mc_addr);

क्रमागत अणु PSP_HDCP_SRM_FIRST_GEN_MAX_SIZE = 5120 पूर्ण;

क्रमागत ta_hdcp_command अणु
	TA_HDCP_COMMAND__INITIALIZE,
	TA_HDCP_COMMAND__HDCP1_CREATE_SESSION,
	TA_HDCP_COMMAND__HDCP1_DESTROY_SESSION,
	TA_HDCP_COMMAND__HDCP1_FIRST_PART_AUTHENTICATION,
	TA_HDCP_COMMAND__HDCP1_SECOND_PART_AUTHENTICATION,
	TA_HDCP_COMMAND__HDCP1_ENABLE_ENCRYPTION,
	TA_HDCP_COMMAND__HDCP1_ENABLE_DP_STREAM_ENCRYPTION,
	TA_HDCP_COMMAND__HDCP1_GET_ENCRYPTION_STATUS,
	TA_HDCP_COMMAND__UNUSED_1,
	TA_HDCP_COMMAND__HDCP2_DESTROY_SESSION,
	TA_HDCP_COMMAND__UNUSED_2,
	TA_HDCP_COMMAND__HDCP2_SET_ENCRYPTION,
	TA_HDCP_COMMAND__HDCP2_GET_ENCRYPTION_STATUS,
	TA_HDCP_COMMAND__UNUSED_3,
	TA_HDCP_COMMAND__HDCP2_CREATE_SESSION_V2,
	TA_HDCP_COMMAND__HDCP2_PREPARE_PROCESS_AUTHENTICATION_MSG_V2,
	TA_HDCP_COMMAND__HDCP2_ENABLE_DP_STREAM_ENCRYPTION,
	TA_HDCP_COMMAND__HDCP_DESTROY_ALL_SESSIONS,
	TA_HDCP_COMMAND__HDCP_SET_SRM,
	TA_HDCP_COMMAND__HDCP_GET_SRM
पूर्ण;

क्रमागत ta_hdcp2_msg_id अणु
	TA_HDCP_HDCP2_MSG_ID__शून्य_MESSAGE = 1,
	TA_HDCP_HDCP2_MSG_ID__AKE_INIT = 2,
	TA_HDCP_HDCP2_MSG_ID__AKE_SEND_CERT = 3,
	TA_HDCP_HDCP2_MSG_ID__AKE_NO_STORED_KM = 4,
	TA_HDCP_HDCP2_MSG_ID__AKE_STORED_KM = 5,
	TA_HDCP_HDCP2_MSG_ID__AKE_SEND_RRX = 6,
	TA_HDCP_HDCP2_MSG_ID__AKE_SEND_H_PRIME = 7,
	TA_HDCP_HDCP2_MSG_ID__AKE_SEND_PAIRING_INFO = 8,
	TA_HDCP_HDCP2_MSG_ID__LC_INIT = 9,
	TA_HDCP_HDCP2_MSG_ID__LC_SEND_L_PRIME = 10,
	TA_HDCP_HDCP2_MSG_ID__SKE_SEND_EKS = 11,
	TA_HDCP_HDCP2_MSG_ID__REPEATERAUTH_SEND_RECEIVERID_LIST = 12,
	TA_HDCP_HDCP2_MSG_ID__RTT_READY = 13,
	TA_HDCP_HDCP2_MSG_ID__RTT_CHALLENGE = 14,
	TA_HDCP_HDCP2_MSG_ID__REPEATERAUTH_SEND_ACK = 15,
	TA_HDCP_HDCP2_MSG_ID__REPEATERAUTH_STREAM_MANAGE = 16,
	TA_HDCP_HDCP2_MSG_ID__REPEATERAUTH_STREAM_READY = 17,
	TA_HDCP_HDCP2_MSG_ID__RECEIVER_AUTH_STATUS = 18,
	TA_HDCP_HDCP2_MSG_ID__AKE_TRANSMITTER_INFO = 19,
	TA_HDCP_HDCP2_MSG_ID__AKE_RECEIVER_INFO = 20,
	TA_HDCP_HDCP2_MSG_ID__SIGNAL_CONTENT_STREAM_TYPE_DP = 129
पूर्ण;

क्रमागत ta_hdcp2_hdcp2_msg_id_max_size अणु
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__शून्य_MESSAGE = 0,
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__AKE_INIT = 12,
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__AKE_SEND_CERT = 534,
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__AKE_NO_STORED_KM = 129,
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__AKE_STORED_KM = 33,
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__AKE_SEND_RRX = 9,
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__AKE_SEND_H_PRIME = 33,
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__AKE_SEND_PAIRING_INFO = 17,
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__LC_INIT = 9,
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__LC_SEND_L_PRIME = 33,
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__SKE_SEND_EKS = 25,
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__REPEATERAUTH_SEND_RECEIVERID_LIST = 181,
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__RTT_READY = 1,
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__RTT_CHALLENGE = 17,
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__REPEATERAUTH_SEND_RACK = 17,
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__REPEATERAUTH_STREAM_MANAGE = 13,
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__REPEATERAUTH_STREAM_READY = 33,
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__RECEIVER_AUTH_STATUS = 4,
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__AKE_TRANSMITTER_INFO = 6,
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__AKE_RECEIVER_INFO = 6,
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__SIGNAL_CONTENT_STREAM_TYPE_DP = 1
पूर्ण;

/* HDCP related क्रमागतerations */
/**********************************************************/
#घोषणा TA_HDCP__INVALID_SESSION 0xFFFF
#घोषणा TA_HDCP__HDCP1_AN_SIZE 8
#घोषणा TA_HDCP__HDCP1_KSV_SIZE 5
#घोषणा TA_HDCP__HDCP1_KSV_LIST_MAX_ENTRIES 127
#घोषणा TA_HDCP__HDCP1_V_PRIME_SIZE 20
#घोषणा TA_HDCP__HDCP2_TX_BUF_MAX_SIZE                                                                                 \
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__AKE_NO_STORED_KM + TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__AKE_STORED_KM + 6

// 64 bits boundaries
#घोषणा TA_HDCP__HDCP2_RX_BUF_MAX_SIZE                                                                                 \
	TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__AKE_SEND_CERT + TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__AKE_RECEIVER_INFO + 4

क्रमागत ta_hdcp_status अणु
	TA_HDCP_STATUS__SUCCESS = 0x00,
	TA_HDCP_STATUS__GENERIC_FAILURE = 0x01,
	TA_HDCP_STATUS__शून्य_POINTER = 0x02,
	TA_HDCP_STATUS__FAILED_ALLOCATING_SESSION = 0x03,
	TA_HDCP_STATUS__FAILED_SETUP_TX = 0x04,
	TA_HDCP_STATUS__INVALID_PARAMETER = 0x05,
	TA_HDCP_STATUS__VHX_ERROR = 0x06,
	TA_HDCP_STATUS__SESSION_NOT_CLOSED_PROPERLY = 0x07,
	TA_HDCP_STATUS__SRM_FAILURE = 0x08,
	TA_HDCP_STATUS__MST_AUTHENTICATED_ALREADY_STARTED = 0x09,
	TA_HDCP_STATUS__AKE_SEND_CERT_FAILURE = 0x0A,
	TA_HDCP_STATUS__AKE_NO_STORED_KM_FAILURE = 0x0B,
	TA_HDCP_STATUS__AKE_SEND_HPRIME_FAILURE = 0x0C,
	TA_HDCP_STATUS__LC_SEND_LPRIME_FAILURE = 0x0D,
	TA_HDCP_STATUS__SKE_SEND_EKS_FAILURE = 0x0E,
	TA_HDCP_STATUS__REPAUTH_SEND_RXIDLIST_FAILURE = 0x0F,
	TA_HDCP_STATUS__REPAUTH_STREAM_READY_FAILURE = 0x10,
	TA_HDCP_STATUS__ASD_GENERIC_FAILURE = 0x11,
	TA_HDCP_STATUS__UNWRAP_SECRET_FAILURE = 0x12,
	TA_HDCP_STATUS__ENABLE_ENCR_FAILURE = 0x13,
	TA_HDCP_STATUS__DISABLE_ENCR_FAILURE = 0x14,
	TA_HDCP_STATUS__NOT_ENOUGH_MEMORY_FAILURE = 0x15,
	TA_HDCP_STATUS__UNKNOWN_MESSAGE = 0x16,
	TA_HDCP_STATUS__TOO_MANY_STREAM = 0x17
पूर्ण;

क्रमागत ta_hdcp_authentication_status अणु
	TA_HDCP_AUTHENTICATION_STATUS__NOT_STARTED = 0x00,
	TA_HDCP_AUTHENTICATION_STATUS__HDCP1_FIRST_PART_FAILED = 0x01,
	TA_HDCP_AUTHENTICATION_STATUS__HDCP1_FIRST_PART_COMPLETE = 0x02,
	TA_HDCP_AUTHENTICATION_STATUS__HDCP1_SECOND_PART_FAILED = 0x03,
	TA_HDCP_AUTHENTICATION_STATUS__HDCP1_AUTHENTICATED = 0x04,
	TA_HDCP_AUTHENTICATION_STATUS__HDCP22_AUTHENTICATION_PENDING = 0x06,
	TA_HDCP_AUTHENTICATION_STATUS__HDCP22_AUTHENTICATION_FAILED = 0x07,
	TA_HDCP_AUTHENTICATION_STATUS__HDCP22_AUTHENTICATED = 0x08,
	TA_HDCP_AUTHENTICATION_STATUS__HDCP1_KSV_VALIDATION_FAILED = 0x09,
	TA_HDCP_AUTHENTICATION_STATUS__HDCP1_KSV_REVOKED = 0x0A
पूर्ण;

क्रमागत ta_hdcp2_msg_authentication_status अणु
	TA_HDCP2_MSG_AUTHENTICATION_STATUS__SUCCESS = 0,
	TA_HDCP2_MSG_AUTHENTICATION_STATUS__KM_NOT_AVAILABLE,
	TA_HDCP2_MSG_AUTHENTICATION_STATUS__UNUSED,
	TA_HDCP2_MSG_AUTHENTICATION_STATUS__INVALID = 100, // everything above करोes not fail the request
	TA_HDCP2_MSG_AUTHENTICATION_STATUS__NOT_ENOUGH_MEMORY,
	TA_HDCP2_MSG_AUTHENTICATION_STATUS__NOT_EXPECTED_MSG,
	TA_HDCP2_MSG_AUTHENTICATION_STATUS__SIGNATURE_CERTIFICAT_ERROR,
	TA_HDCP2_MSG_AUTHENTICATION_STATUS__INCORRECT_HDCP_VERSION,
	TA_HDCP2_MSG_AUTHENTICATION_STATUS__UNKNOWN_MESSAGE,
	TA_HDCP2_MSG_AUTHENTICATION_STATUS__INVALID_HMAC,
	TA_HDCP2_MSG_AUTHENTICATION_STATUS__INVALID_TOPOLOGY,
	TA_HDCP2_MSG_AUTHENTICATION_STATUS__INVALID_SEQ_NUM,
	TA_HDCP2_MSG_AUTHENTICATION_STATUS__INVALID_SIZE,
	TA_HDCP2_MSG_AUTHENTICATION_STATUS__INVALID_LENGTH,
	TA_HDCP2_MSG_AUTHENTICATION_STATUS__REAUTH_REQUEST,
	TA_HDCP2_MSG_AUTHENTICATION_STATUS__RECEIVERID_REVOKED
पूर्ण;

क्रमागत ta_hdcp_content_type अणु
	TA_HDCP2_CONTENT_TYPE__TYPE0 = 1,
	TA_HDCP2_CONTENT_TYPE__TYPE1,
पूर्ण;

क्रमागत ta_hdcp_content_type_negotiation_type अणु
	TA_HDCP2_CONTENT_TYPE_NEGOTIATION_TYPE__FORCE_TYPE0 = 1,
	TA_HDCP2_CONTENT_TYPE_NEGOTIATION_TYPE__FORCE_TYPE1,
	TA_HDCP2_CONTENT_TYPE_NEGOTIATION_TYPE__MAX_SUPPORTED
पूर्ण;

क्रमागत ta_hdcp2_version अणु
	TA_HDCP2_VERSION_UNKNOWN = 0,
	TA_HDCP2_VERSION_2_0 = 20,
	TA_HDCP2_VERSION_2_1 = 21,
	TA_HDCP2_VERSION_2_2 = 22
पूर्ण;

/* input/output काष्ठाures क्रम HDCP commands */
/**********************************************************/
काष्ठा ta_hdcp_cmd_hdcp1_create_session_input अणु
	uपूर्णांक8_t display_handle;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp1_create_session_output अणु
	uपूर्णांक32_t session_handle;
	uपूर्णांक8_t an_primary[TA_HDCP__HDCP1_AN_SIZE];
	uपूर्णांक8_t aksv_primary[TA_HDCP__HDCP1_KSV_SIZE];
	uपूर्णांक8_t ainfo_primary;
	uपूर्णांक8_t an_secondary[TA_HDCP__HDCP1_AN_SIZE];
	uपूर्णांक8_t aksv_secondary[TA_HDCP__HDCP1_KSV_SIZE];
	uपूर्णांक8_t ainfo_secondary;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp1_destroy_session_input अणु
	uपूर्णांक32_t session_handle;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp1_first_part_authentication_input अणु
	uपूर्णांक32_t session_handle;
	uपूर्णांक8_t bksv_primary[TA_HDCP__HDCP1_KSV_SIZE];
	uपूर्णांक8_t bksv_secondary[TA_HDCP__HDCP1_KSV_SIZE];
	uपूर्णांक8_t bcaps;
	uपूर्णांक16_t r0_prime_primary;
	uपूर्णांक16_t r0_prime_secondary;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp1_first_part_authentication_output अणु
	क्रमागत ta_hdcp_authentication_status authentication_status;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp1_second_part_authentication_input अणु
	uपूर्णांक32_t session_handle;
	uपूर्णांक16_t bstatus_binfo;
	uपूर्णांक8_t ksv_list[TA_HDCP__HDCP1_KSV_LIST_MAX_ENTRIES][TA_HDCP__HDCP1_KSV_SIZE];
	uपूर्णांक32_t ksv_list_size;
	uपूर्णांक8_t pj_prime;
	uपूर्णांक8_t v_prime[TA_HDCP__HDCP1_V_PRIME_SIZE];
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp1_second_part_authentication_output अणु
	क्रमागत ta_hdcp_authentication_status authentication_status;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp1_enable_encryption_input अणु
	uपूर्णांक32_t session_handle;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp1_enable_dp_stream_encryption_input अणु
	uपूर्णांक32_t session_handle;
	uपूर्णांक32_t display_handle;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp1_get_encryption_status_input अणु
	uपूर्णांक32_t session_handle;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp1_get_encryption_status_output अणु
	uपूर्णांक32_t protection_level;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp2_create_session_input_v2 अणु
	uपूर्णांक32_t display_handle;
	क्रमागत ta_hdcp_content_type_negotiation_type negotiate_content_type;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp2_create_session_output_v2 अणु
	uपूर्णांक32_t session_handle;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp2_destroy_session_input अणु
	uपूर्णांक32_t session_handle;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp2_authentication_message_v2 अणु
	क्रमागत ta_hdcp2_msg_id msg_id;
	uपूर्णांक32_t msg_size;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp2_process_authentication_message_input_v2 अणु
	काष्ठा ta_hdcp_cmd_hdcp2_authentication_message_v2 msg1_desc;
	काष्ठा ta_hdcp_cmd_hdcp2_authentication_message_v2 msg2_desc;
	काष्ठा ta_hdcp_cmd_hdcp2_authentication_message_v2 msg3_desc;
	uपूर्णांक8_t receiver_message[TA_HDCP__HDCP2_RX_BUF_MAX_SIZE];
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp2_process_authentication_message_output_v2 अणु
	uपूर्णांक32_t hdcp_version;
	uपूर्णांक32_t is_km_stored;
	uपूर्णांक32_t is_locality_precompute_support;
	uपूर्णांक32_t is_repeater;
	क्रमागत ta_hdcp2_msg_authentication_status msg1_status;
	क्रमागत ta_hdcp2_msg_authentication_status msg2_status;
	क्रमागत ta_hdcp2_msg_authentication_status msg3_status;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp2_prepare_authentication_message_input_v2 अणु
	क्रमागत ta_hdcp2_msg_id msg1_id;
	क्रमागत ta_hdcp2_msg_id msg2_id;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp2_prepare_authentication_message_output_v2 अणु
	क्रमागत ta_hdcp2_msg_authentication_status msg1_status;
	क्रमागत ta_hdcp2_msg_authentication_status msg2_status;
	काष्ठा ta_hdcp_cmd_hdcp2_authentication_message_v2 msg1_desc;
	काष्ठा ta_hdcp_cmd_hdcp2_authentication_message_v2 msg2_desc;
	uपूर्णांक8_t transmitter_message[TA_HDCP__HDCP2_TX_BUF_MAX_SIZE];
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_input_v2 अणु
	uपूर्णांक32_t session_handle;
	काष्ठा ta_hdcp_cmd_hdcp2_process_authentication_message_input_v2 process;
	काष्ठा ta_hdcp_cmd_hdcp2_prepare_authentication_message_input_v2 prepare;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_output_v2 अणु
	uपूर्णांक32_t authentication_status;
	काष्ठा ta_hdcp_cmd_hdcp2_process_authentication_message_output_v2 process;
	काष्ठा ta_hdcp_cmd_hdcp2_prepare_authentication_message_output_v2 prepare;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp2_set_encryption_input अणु
	uपूर्णांक32_t session_handle;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp2_get_encryption_status_input अणु
	uपूर्णांक32_t session_handle;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp2_get_encryption_status_output अणु
	क्रमागत ta_hdcp_content_type hdcp2_type;
	uपूर्णांक32_t protection_level;
पूर्ण;

काष्ठा ta_hdcp_cmd_hdcp2_enable_dp_stream_encryption_input अणु
	uपूर्णांक32_t session_handle;
	uपूर्णांक32_t display_handle;
पूर्ण;

काष्ठा ta_hdcp_cmd_set_srm_input अणु
	uपूर्णांक32_t srm_buf_size;
	uपूर्णांक8_t srm_buf[PSP_HDCP_SRM_FIRST_GEN_MAX_SIZE];
पूर्ण;

काष्ठा ta_hdcp_cmd_set_srm_output अणु
	uपूर्णांक8_t valid_signature;
	uपूर्णांक32_t srm_version;
पूर्ण;

काष्ठा ta_hdcp_cmd_get_srm_output अणु
	uपूर्णांक32_t srm_version;
	uपूर्णांक32_t srm_buf_size;
	uपूर्णांक8_t srm_buf[PSP_HDCP_SRM_FIRST_GEN_MAX_SIZE];
पूर्ण;

/**********************************************************/
/* Common input काष्ठाure क्रम HDCP callbacks */
जोड़ ta_hdcp_cmd_input अणु
	काष्ठा ta_hdcp_cmd_hdcp1_create_session_input hdcp1_create_session;
	काष्ठा ta_hdcp_cmd_hdcp1_destroy_session_input hdcp1_destroy_session;
	काष्ठा ta_hdcp_cmd_hdcp1_first_part_authentication_input hdcp1_first_part_authentication;
	काष्ठा ta_hdcp_cmd_hdcp1_second_part_authentication_input hdcp1_second_part_authentication;
	काष्ठा ta_hdcp_cmd_hdcp1_enable_encryption_input hdcp1_enable_encryption;
	काष्ठा ta_hdcp_cmd_hdcp1_enable_dp_stream_encryption_input hdcp1_enable_dp_stream_encryption;
	काष्ठा ta_hdcp_cmd_hdcp1_get_encryption_status_input hdcp1_get_encryption_status;
	काष्ठा ta_hdcp_cmd_hdcp2_destroy_session_input hdcp2_destroy_session;
	काष्ठा ta_hdcp_cmd_hdcp2_set_encryption_input hdcp2_set_encryption;
	काष्ठा ta_hdcp_cmd_hdcp2_get_encryption_status_input hdcp2_get_encryption_status;
	काष्ठा ta_hdcp_cmd_hdcp2_create_session_input_v2 hdcp2_create_session_v2;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_input_v2
		hdcp2_prepare_process_authentication_message_v2;
	काष्ठा ta_hdcp_cmd_hdcp2_enable_dp_stream_encryption_input hdcp2_enable_dp_stream_encryption;
	काष्ठा ta_hdcp_cmd_set_srm_input hdcp_set_srm;
पूर्ण;

/* Common output काष्ठाure क्रम HDCP callbacks */
जोड़ ta_hdcp_cmd_output अणु
	काष्ठा ta_hdcp_cmd_hdcp1_create_session_output hdcp1_create_session;
	काष्ठा ta_hdcp_cmd_hdcp1_first_part_authentication_output hdcp1_first_part_authentication;
	काष्ठा ta_hdcp_cmd_hdcp1_second_part_authentication_output hdcp1_second_part_authentication;
	काष्ठा ta_hdcp_cmd_hdcp1_get_encryption_status_output hdcp1_get_encryption_status;
	काष्ठा ta_hdcp_cmd_hdcp2_get_encryption_status_output hdcp2_get_encryption_status;
	काष्ठा ta_hdcp_cmd_hdcp2_create_session_output_v2 hdcp2_create_session_v2;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_output_v2
		hdcp2_prepare_process_authentication_message_v2;
	काष्ठा ta_hdcp_cmd_set_srm_output hdcp_set_srm;
	काष्ठा ta_hdcp_cmd_get_srm_output hdcp_get_srm;
पूर्ण;
/**********************************************************/

काष्ठा ta_hdcp_shared_memory अणु
	uपूर्णांक32_t cmd_id;
	क्रमागत ta_hdcp_status hdcp_status;
	uपूर्णांक32_t reserved;
	जोड़ ta_hdcp_cmd_input in_msg;
	जोड़ ta_hdcp_cmd_output out_msg;
पूर्ण;

क्रमागत psp_status अणु
	PSP_STATUS__SUCCESS = 0,
	PSP_STATUS__ERROR_INVALID_PARAMS,
	PSP_STATUS__ERROR_GENERIC,
	PSP_STATUS__ERROR_OUT_OF_MEMORY,
	PSP_STATUS__ERROR_UNSUPPORTED_FEATURE
पूर्ण;

#पूर्ण_अगर /* MODULES_HDCP_HDCP_PSP_H_ */
