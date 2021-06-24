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

#अगर_अघोषित HDCP_H_
#घोषणा HDCP_H_

#समावेश "mod_hdcp.h"
#समावेश "hdcp_log.h"

#समावेश <drm/drm_hdcp.h>
#समावेश <drm/drm_dp_helper.h>

क्रमागत mod_hdcp_trans_input_result अणु
	UNKNOWN = 0,
	PASS,
	FAIL
पूर्ण;

काष्ठा mod_hdcp_transition_input_hdcp1 अणु
	uपूर्णांक8_t bksv_पढ़ो;
	uपूर्णांक8_t bksv_validation;
	uपूर्णांक8_t create_session;
	uपूर्णांक8_t an_ग_लिखो;
	uपूर्णांक8_t aksv_ग_लिखो;
	uपूर्णांक8_t ainfo_ग_लिखो;
	uपूर्णांक8_t bcaps_पढ़ो;
	uपूर्णांक8_t r0p_पढ़ो;
	uपूर्णांक8_t rx_validation;
	uपूर्णांक8_t encryption;
	uपूर्णांक8_t link_मुख्यtenance;
	uपूर्णांक8_t पढ़ोy_check;
	uपूर्णांक8_t bstatus_पढ़ो;
	uपूर्णांक8_t max_cascade_check;
	uपूर्णांक8_t max_devs_check;
	uपूर्णांक8_t device_count_check;
	uपूर्णांक8_t ksvlist_पढ़ो;
	uपूर्णांक8_t vp_पढ़ो;
	uपूर्णांक8_t ksvlist_vp_validation;

	uपूर्णांक8_t hdcp_capable_dp;
	uपूर्णांक8_t binfo_पढ़ो_dp;
	uपूर्णांक8_t r0p_available_dp;
	uपूर्णांक8_t link_पूर्णांकegrity_check;
	uपूर्णांक8_t reauth_request_check;
	uपूर्णांक8_t stream_encryption_dp;
पूर्ण;

काष्ठा mod_hdcp_transition_input_hdcp2 अणु
	uपूर्णांक8_t hdcp2version_पढ़ो;
	uपूर्णांक8_t hdcp2_capable_check;
	uपूर्णांक8_t create_session;
	uपूर्णांक8_t ake_init_prepare;
	uपूर्णांक8_t ake_init_ग_लिखो;
	uपूर्णांक8_t rxstatus_पढ़ो;
	uपूर्णांक8_t ake_cert_available;
	uपूर्णांक8_t ake_cert_पढ़ो;
	uपूर्णांक8_t ake_cert_validation;
	uपूर्णांक8_t stored_km_ग_लिखो;
	uपूर्णांक8_t no_stored_km_ग_लिखो;
	uपूर्णांक8_t h_prime_available;
	uपूर्णांक8_t h_prime_पढ़ो;
	uपूर्णांक8_t pairing_available;
	uपूर्णांक8_t pairing_info_पढ़ो;
	uपूर्णांक8_t h_prime_validation;
	uपूर्णांक8_t lc_init_prepare;
	uपूर्णांक8_t lc_init_ग_लिखो;
	uपूर्णांक8_t l_prime_available_poll;
	uपूर्णांक8_t l_prime_पढ़ो;
	uपूर्णांक8_t l_prime_validation;
	uपूर्णांक8_t eks_prepare;
	uपूर्णांक8_t eks_ग_लिखो;
	uपूर्णांक8_t enable_encryption;
	uपूर्णांक8_t reauth_request_check;
	uपूर्णांक8_t rx_id_list_पढ़ो;
	uपूर्णांक8_t device_count_check;
	uपूर्णांक8_t rx_id_list_validation;
	uपूर्णांक8_t repeater_auth_ack_ग_लिखो;
	uपूर्णांक8_t prepare_stream_manage;
	uपूर्णांक8_t stream_manage_ग_लिखो;
	uपूर्णांक8_t stream_पढ़ोy_available;
	uपूर्णांक8_t stream_पढ़ोy_पढ़ो;
	uपूर्णांक8_t stream_पढ़ोy_validation;

	uपूर्णांक8_t rx_caps_पढ़ो_dp;
	uपूर्णांक8_t content_stream_type_ग_लिखो;
	uपूर्णांक8_t link_पूर्णांकegrity_check_dp;
	uपूर्णांक8_t stream_encryption_dp;
पूर्ण;

जोड़ mod_hdcp_transition_input अणु
	काष्ठा mod_hdcp_transition_input_hdcp1 hdcp1;
	काष्ठा mod_hdcp_transition_input_hdcp2 hdcp2;
पूर्ण;

काष्ठा mod_hdcp_message_hdcp1 अणु
	uपूर्णांक8_t		an[8];
	uपूर्णांक8_t		aksv[5];
	uपूर्णांक8_t		ainfo;
	uपूर्णांक8_t		bksv[5];
	uपूर्णांक16_t	r0p;
	uपूर्णांक8_t		bcaps;
	uपूर्णांक16_t	bstatus;
	uपूर्णांक8_t		ksvlist[635];
	uपूर्णांक16_t	ksvlist_size;
	uपूर्णांक8_t		vp[20];

	uपूर्णांक16_t	binfo_dp;
पूर्ण;

काष्ठा mod_hdcp_message_hdcp2 अणु
	uपूर्णांक8_t		hdcp2version_hdmi;
	uपूर्णांक8_t		rxcaps_dp[3];
	uपूर्णांक8_t		rxstatus[2];

	uपूर्णांक8_t		ake_init[12];
	uपूर्णांक8_t		ake_cert[534];
	uपूर्णांक8_t		ake_no_stored_km[129];
	uपूर्णांक8_t		ake_stored_km[33];
	uपूर्णांक8_t		ake_h_prime[33];
	uपूर्णांक8_t		ake_pairing_info[17];
	uपूर्णांक8_t		lc_init[9];
	uपूर्णांक8_t		lc_l_prime[33];
	uपूर्णांक8_t		ske_eks[25];
	uपूर्णांक8_t		rx_id_list[177]; // 22 + 5 * 31
	uपूर्णांक16_t	rx_id_list_size;
	uपूर्णांक8_t		repeater_auth_ack[17];
	uपूर्णांक8_t		repeater_auth_stream_manage[68]; // 6 + 2 * 31
	uपूर्णांक16_t	stream_manage_size;
	uपूर्णांक8_t		repeater_auth_stream_पढ़ोy[33];
	uपूर्णांक8_t		rxstatus_dp;
	uपूर्णांक8_t		content_stream_type_dp[2];
पूर्ण;

जोड़ mod_hdcp_message अणु
	काष्ठा mod_hdcp_message_hdcp1 hdcp1;
	काष्ठा mod_hdcp_message_hdcp2 hdcp2;
पूर्ण;

काष्ठा mod_hdcp_auth_counters अणु
	uपूर्णांक8_t stream_management_retry_count;
पूर्ण;

/* contains values per connection */
काष्ठा mod_hdcp_connection अणु
	काष्ठा mod_hdcp_link link;
	uपूर्णांक8_t is_repeater;
	uपूर्णांक8_t is_km_stored;
	uपूर्णांक8_t is_hdcp1_revoked;
	uपूर्णांक8_t is_hdcp2_revoked;
	काष्ठा mod_hdcp_trace trace;
	uपूर्णांक8_t hdcp1_retry_count;
	uपूर्णांक8_t hdcp2_retry_count;
पूर्ण;

/* contains values per authentication cycle */
काष्ठा mod_hdcp_authentication अणु
	uपूर्णांक32_t id;
	जोड़ mod_hdcp_message msg;
	जोड़ mod_hdcp_transition_input trans_input;
	काष्ठा mod_hdcp_auth_counters count;
पूर्ण;

/* contains values per state change */
काष्ठा mod_hdcp_state अणु
	uपूर्णांक8_t id;
	uपूर्णांक32_t stay_count;
पूर्ण;

/* per event in a state */
काष्ठा mod_hdcp_event_context अणु
	क्रमागत mod_hdcp_event event;
	uपूर्णांक8_t rx_id_list_पढ़ोy;
	uपूर्णांक8_t unexpected_event;
पूर्ण;

काष्ठा mod_hdcp अणु
	/* per link */
	काष्ठा mod_hdcp_config config;
	/* per connection */
	काष्ठा mod_hdcp_connection connection;
	/* per displays */
	काष्ठा mod_hdcp_display displays[MAX_NUM_OF_DISPLAYS];
	/* per authentication attempt */
	काष्ठा mod_hdcp_authentication auth;
	/* per state in an authentication */
	काष्ठा mod_hdcp_state state;
	/* reserved memory buffer */
	uपूर्णांक8_t buf[2025];
पूर्ण;

क्रमागत mod_hdcp_initial_state_id अणु
	HDCP_UNINITIALIZED = 0x0,
	HDCP_INITIAL_STATE_START = HDCP_UNINITIALIZED,
	HDCP_INITIALIZED,
	HDCP_CP_NOT_DESIRED,
	HDCP_INITIAL_STATE_END = HDCP_CP_NOT_DESIRED
पूर्ण;

क्रमागत mod_hdcp_hdcp1_state_id अणु
	HDCP1_STATE_START = HDCP_INITIAL_STATE_END,
	H1_A0_WAIT_FOR_ACTIVE_RX,
	H1_A1_EXCHANGE_KSVS,
	H1_A2_COMPUTATIONS_A3_VALIDATE_RX_A6_TEST_FOR_REPEATER,
	H1_A45_AUTHENTICATED,
	H1_A8_WAIT_FOR_READY,
	H1_A9_READ_KSV_LIST,
	HDCP1_STATE_END = H1_A9_READ_KSV_LIST
पूर्ण;

क्रमागत mod_hdcp_hdcp1_dp_state_id अणु
	HDCP1_DP_STATE_START = HDCP1_STATE_END,
	D1_A0_DETERMINE_RX_HDCP_CAPABLE,
	D1_A1_EXCHANGE_KSVS,
	D1_A23_WAIT_FOR_R0_PRIME,
	D1_A2_COMPUTATIONS_A3_VALIDATE_RX_A5_TEST_FOR_REPEATER,
	D1_A4_AUTHENTICATED,
	D1_A6_WAIT_FOR_READY,
	D1_A7_READ_KSV_LIST,
	HDCP1_DP_STATE_END = D1_A7_READ_KSV_LIST,
पूर्ण;

क्रमागत mod_hdcp_hdcp2_state_id अणु
	HDCP2_STATE_START = HDCP1_DP_STATE_END,
	H2_A0_KNOWN_HDCP2_CAPABLE_RX,
	H2_A1_SEND_AKE_INIT,
	H2_A1_VALIDATE_AKE_CERT,
	H2_A1_SEND_NO_STORED_KM,
	H2_A1_READ_H_PRIME,
	H2_A1_READ_PAIRING_INFO_AND_VALIDATE_H_PRIME,
	H2_A1_SEND_STORED_KM,
	H2_A1_VALIDATE_H_PRIME,
	H2_A2_LOCALITY_CHECK,
	H2_A3_EXCHANGE_KS_AND_TEST_FOR_REPEATER,
	H2_ENABLE_ENCRYPTION,
	H2_A5_AUTHENTICATED,
	H2_A6_WAIT_FOR_RX_ID_LIST,
	H2_A78_VERIFY_RX_ID_LIST_AND_SEND_ACK,
	H2_A9_SEND_STREAM_MANAGEMENT,
	H2_A9_VALIDATE_STREAM_READY,
	HDCP2_STATE_END = H2_A9_VALIDATE_STREAM_READY,
पूर्ण;

क्रमागत mod_hdcp_hdcp2_dp_state_id अणु
	HDCP2_DP_STATE_START = HDCP2_STATE_END,
	D2_A0_DETERMINE_RX_HDCP_CAPABLE,
	D2_A1_SEND_AKE_INIT,
	D2_A1_VALIDATE_AKE_CERT,
	D2_A1_SEND_NO_STORED_KM,
	D2_A1_READ_H_PRIME,
	D2_A1_READ_PAIRING_INFO_AND_VALIDATE_H_PRIME,
	D2_A1_SEND_STORED_KM,
	D2_A1_VALIDATE_H_PRIME,
	D2_A2_LOCALITY_CHECK,
	D2_A34_EXCHANGE_KS_AND_TEST_FOR_REPEATER,
	D2_SEND_CONTENT_STREAM_TYPE,
	D2_ENABLE_ENCRYPTION,
	D2_A5_AUTHENTICATED,
	D2_A6_WAIT_FOR_RX_ID_LIST,
	D2_A78_VERIFY_RX_ID_LIST_AND_SEND_ACK,
	D2_A9_SEND_STREAM_MANAGEMENT,
	D2_A9_VALIDATE_STREAM_READY,
	HDCP2_DP_STATE_END = D2_A9_VALIDATE_STREAM_READY,
	HDCP_STATE_END = HDCP2_DP_STATE_END,
पूर्ण;

/* hdcp1 executions and transitions */
प्रकार क्रमागत mod_hdcp_status (*mod_hdcp_action)(काष्ठा mod_hdcp *hdcp);
uपूर्णांक8_t mod_hdcp_execute_and_set(
		mod_hdcp_action func, uपूर्णांक8_t *flag,
		क्रमागत mod_hdcp_status *status, काष्ठा mod_hdcp *hdcp, अक्षर *str);
क्रमागत mod_hdcp_status mod_hdcp_hdcp1_execution(काष्ठा mod_hdcp *hdcp,
	काष्ठा mod_hdcp_event_context *event_ctx,
	काष्ठा mod_hdcp_transition_input_hdcp1 *input);
क्रमागत mod_hdcp_status mod_hdcp_hdcp1_dp_execution(काष्ठा mod_hdcp *hdcp,
	काष्ठा mod_hdcp_event_context *event_ctx,
	काष्ठा mod_hdcp_transition_input_hdcp1 *input);
क्रमागत mod_hdcp_status mod_hdcp_hdcp1_transition(काष्ठा mod_hdcp *hdcp,
	काष्ठा mod_hdcp_event_context *event_ctx,
	काष्ठा mod_hdcp_transition_input_hdcp1 *input,
	काष्ठा mod_hdcp_output *output);
क्रमागत mod_hdcp_status mod_hdcp_hdcp1_dp_transition(काष्ठा mod_hdcp *hdcp,
	काष्ठा mod_hdcp_event_context *event_ctx,
	काष्ठा mod_hdcp_transition_input_hdcp1 *input,
	काष्ठा mod_hdcp_output *output);

/* hdcp2 executions and transitions */
क्रमागत mod_hdcp_status mod_hdcp_hdcp2_execution(काष्ठा mod_hdcp *hdcp,
	काष्ठा mod_hdcp_event_context *event_ctx,
	काष्ठा mod_hdcp_transition_input_hdcp2 *input);
क्रमागत mod_hdcp_status mod_hdcp_hdcp2_dp_execution(काष्ठा mod_hdcp *hdcp,
	काष्ठा mod_hdcp_event_context *event_ctx,
	काष्ठा mod_hdcp_transition_input_hdcp2 *input);
क्रमागत mod_hdcp_status mod_hdcp_hdcp2_transition(काष्ठा mod_hdcp *hdcp,
	काष्ठा mod_hdcp_event_context *event_ctx,
	काष्ठा mod_hdcp_transition_input_hdcp2 *input,
	काष्ठा mod_hdcp_output *output);
क्रमागत mod_hdcp_status mod_hdcp_hdcp2_dp_transition(काष्ठा mod_hdcp *hdcp,
	काष्ठा mod_hdcp_event_context *event_ctx,
	काष्ठा mod_hdcp_transition_input_hdcp2 *input,
	काष्ठा mod_hdcp_output *output);

/* log functions */
व्योम mod_hdcp_dump_binary_message(uपूर्णांक8_t *msg, uपूर्णांक32_t msg_size,
		uपूर्णांक8_t *buf, uपूर्णांक32_t buf_size);
/* TODO: add adjusपंचांगent log */

/* psp functions */
क्रमागत mod_hdcp_status mod_hdcp_add_display_to_topology(
		काष्ठा mod_hdcp *hdcp, काष्ठा mod_hdcp_display *display);
क्रमागत mod_hdcp_status mod_hdcp_हटाओ_display_from_topology(
		काष्ठा mod_hdcp *hdcp, uपूर्णांक8_t index);
bool mod_hdcp_is_link_encryption_enabled(काष्ठा mod_hdcp *hdcp);
व्योम mod_hdcp_save_current_encryption_states(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_hdcp1_create_session(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_hdcp1_destroy_session(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_hdcp1_validate_rx(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_hdcp1_enable_encryption(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_hdcp1_validate_ksvlist_vp(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_hdcp1_enable_dp_stream_encryption(
	काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_hdcp1_link_मुख्यtenance(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_hdcp2_create_session(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_hdcp2_destroy_session(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_hdcp2_prepare_ake_init(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_hdcp2_validate_ake_cert(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_hdcp2_validate_h_prime(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_hdcp2_prepare_lc_init(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_hdcp2_validate_l_prime(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_hdcp2_prepare_eks(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_hdcp2_enable_encryption(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_hdcp2_validate_rx_id_list(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_hdcp2_enable_dp_stream_encryption(
		काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_hdcp2_prepare_stream_management(
		काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_hdcp2_validate_stream_पढ़ोy(
		काष्ठा mod_hdcp *hdcp);

/* ddc functions */
क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_bksv(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_bcaps(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_bstatus(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_r0p(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_ksvlist(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_vp(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_binfo(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_aksv(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_ainfo(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_an(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_hdcp2version(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_rxcaps(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_rxstatus(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_ake_cert(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_h_prime(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_pairing_info(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_l_prime(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_rx_id_list(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_stream_पढ़ोy(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_ake_init(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_no_stored_km(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_stored_km(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_lc_init(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_eks(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_repeater_auth_ack(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_stream_manage(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_content_type(काष्ठा mod_hdcp *hdcp);
क्रमागत mod_hdcp_status mod_hdcp_clear_cp_irq_status(काष्ठा mod_hdcp *hdcp);

/* hdcp version helpers */
अटल अंतरभूत uपूर्णांक8_t is_dp_hdcp(काष्ठा mod_hdcp *hdcp)
अणु
	वापस (hdcp->connection.link.mode == MOD_HDCP_MODE_DP);
पूर्ण

अटल अंतरभूत uपूर्णांक8_t is_dp_mst_hdcp(काष्ठा mod_hdcp *hdcp)
अणु
	वापस (hdcp->connection.link.mode == MOD_HDCP_MODE_DP &&
			hdcp->connection.link.dp.mst_enabled);
पूर्ण

अटल अंतरभूत uपूर्णांक8_t is_hdmi_dvi_sl_hdcp(काष्ठा mod_hdcp *hdcp)
अणु
	वापस (hdcp->connection.link.mode == MOD_HDCP_MODE_DEFAULT);
पूर्ण

/* hdcp state helpers */
अटल अंतरभूत uपूर्णांक8_t current_state(काष्ठा mod_hdcp *hdcp)
अणु
	वापस hdcp->state.id;
पूर्ण

अटल अंतरभूत व्योम set_state_id(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_output *output, uपूर्णांक8_t id)
अणु
	स_रखो(&hdcp->state, 0, माप(hdcp->state));
	hdcp->state.id = id;
	/* callback समयr should be reset per state */
	output->callback_stop = 1;
	output->watchकरोg_समयr_stop = 1;
	HDCP_NEXT_STATE_TRACE(hdcp, id, output);
पूर्ण

अटल अंतरभूत uपूर्णांक8_t is_in_hdcp1_states(काष्ठा mod_hdcp *hdcp)
अणु
	वापस (current_state(hdcp) > HDCP1_STATE_START &&
			current_state(hdcp) <= HDCP1_STATE_END);
पूर्ण

अटल अंतरभूत uपूर्णांक8_t is_in_hdcp1_dp_states(काष्ठा mod_hdcp *hdcp)
अणु
	वापस (current_state(hdcp) > HDCP1_DP_STATE_START &&
			current_state(hdcp) <= HDCP1_DP_STATE_END);
पूर्ण

अटल अंतरभूत uपूर्णांक8_t is_in_hdcp2_states(काष्ठा mod_hdcp *hdcp)
अणु
	वापस (current_state(hdcp) > HDCP2_STATE_START &&
			current_state(hdcp) <= HDCP2_STATE_END);
पूर्ण

अटल अंतरभूत uपूर्णांक8_t is_in_hdcp2_dp_states(काष्ठा mod_hdcp *hdcp)
अणु
	वापस (current_state(hdcp) > HDCP2_DP_STATE_START &&
			current_state(hdcp) <= HDCP2_DP_STATE_END);
पूर्ण

अटल अंतरभूत uपूर्णांक8_t is_hdcp1(काष्ठा mod_hdcp *hdcp)
अणु
	वापस (is_in_hdcp1_states(hdcp) || is_in_hdcp1_dp_states(hdcp));
पूर्ण

अटल अंतरभूत uपूर्णांक8_t is_hdcp2(काष्ठा mod_hdcp *hdcp)
अणु
	वापस (is_in_hdcp2_states(hdcp) || is_in_hdcp2_dp_states(hdcp));
पूर्ण

अटल अंतरभूत uपूर्णांक8_t is_in_cp_not_desired_state(काष्ठा mod_hdcp *hdcp)
अणु
	वापस current_state(hdcp) == HDCP_CP_NOT_DESIRED;
पूर्ण

अटल अंतरभूत uपूर्णांक8_t is_in_initialized_state(काष्ठा mod_hdcp *hdcp)
अणु
	वापस current_state(hdcp) == HDCP_INITIALIZED;
पूर्ण

/* transition operation helpers */
अटल अंतरभूत व्योम increment_stay_counter(काष्ठा mod_hdcp *hdcp)
अणु
	hdcp->state.stay_count++;
पूर्ण

अटल अंतरभूत व्योम fail_and_restart_in_ms(uपूर्णांक16_t समय,
		क्रमागत mod_hdcp_status *status,
		काष्ठा mod_hdcp_output *output)
अणु
	output->callback_needed = 1;
	output->callback_delay = समय;
	output->watchकरोg_समयr_needed = 0;
	output->watchकरोg_समयr_delay = 0;
	*status = MOD_HDCP_STATUS_RESET_NEEDED;
पूर्ण

अटल अंतरभूत व्योम callback_in_ms(uपूर्णांक16_t समय, काष्ठा mod_hdcp_output *output)
अणु
	output->callback_needed = 1;
	output->callback_delay = समय;
पूर्ण

अटल अंतरभूत व्योम set_watchकरोg_in_ms(काष्ठा mod_hdcp *hdcp, uपूर्णांक16_t समय,
		काष्ठा mod_hdcp_output *output)
अणु
	output->watchकरोg_समयr_needed = 1;
	output->watchकरोg_समयr_delay = समय;
पूर्ण

/* connection topology helpers */
अटल अंतरभूत uपूर्णांक8_t is_display_active(काष्ठा mod_hdcp_display *display)
अणु
	वापस display->state >= MOD_HDCP_DISPLAY_ACTIVE;
पूर्ण

अटल अंतरभूत uपूर्णांक8_t is_display_encryption_enabled(काष्ठा mod_hdcp_display *display)
अणु
	वापस display->state >= MOD_HDCP_DISPLAY_ENCRYPTION_ENABLED;
पूर्ण

अटल अंतरभूत uपूर्णांक8_t get_active_display_count(काष्ठा mod_hdcp *hdcp)
अणु
	uपूर्णांक8_t active_count = 0;
	uपूर्णांक8_t i;

	क्रम (i = 0; i < MAX_NUM_OF_DISPLAYS; i++)
		अगर (is_display_active(&hdcp->displays[i]))
			active_count++;
	वापस active_count;
पूर्ण

अटल अंतरभूत काष्ठा mod_hdcp_display *get_first_active_display(
		काष्ठा mod_hdcp *hdcp)
अणु
	uपूर्णांक8_t i;
	काष्ठा mod_hdcp_display *display = शून्य;

	क्रम (i = 0; i < MAX_NUM_OF_DISPLAYS; i++)
		अगर (is_display_active(&hdcp->displays[i])) अणु
			display = &hdcp->displays[i];
			अवरोध;
		पूर्ण
	वापस display;
पूर्ण

अटल अंतरभूत काष्ठा mod_hdcp_display *get_active_display_at_index(
		काष्ठा mod_hdcp *hdcp, uपूर्णांक8_t index)
अणु
	uपूर्णांक8_t i;
	काष्ठा mod_hdcp_display *display = शून्य;

	क्रम (i = 0; i < MAX_NUM_OF_DISPLAYS; i++)
		अगर (hdcp->displays[i].index == index &&
				is_display_active(&hdcp->displays[i])) अणु
			display = &hdcp->displays[i];
			अवरोध;
		पूर्ण
	वापस display;
पूर्ण

अटल अंतरभूत काष्ठा mod_hdcp_display *get_empty_display_container(
		काष्ठा mod_hdcp *hdcp)
अणु
	uपूर्णांक8_t i;
	काष्ठा mod_hdcp_display *display = शून्य;

	क्रम (i = 0; i < MAX_NUM_OF_DISPLAYS; i++)
		अगर (!is_display_active(&hdcp->displays[i])) अणु
			display = &hdcp->displays[i];
			अवरोध;
		पूर्ण
	वापस display;
पूर्ण

अटल अंतरभूत व्योम reset_retry_counts(काष्ठा mod_hdcp *hdcp)
अणु
	hdcp->connection.hdcp1_retry_count = 0;
	hdcp->connection.hdcp2_retry_count = 0;
पूर्ण

#पूर्ण_अगर /* HDCP_H_ */
