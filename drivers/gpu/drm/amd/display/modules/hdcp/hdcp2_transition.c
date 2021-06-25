<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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

#समावेश "hdcp.h"

क्रमागत mod_hdcp_status mod_hdcp_hdcp2_transition(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input,
		काष्ठा mod_hdcp_output *output)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;
	काष्ठा mod_hdcp_connection *conn = &hdcp->connection;
	काष्ठा mod_hdcp_link_adjusपंचांगent *adjust = &hdcp->connection.link.adjust;

	चयन (current_state(hdcp)) अणु
	हाल H2_A0_KNOWN_HDCP2_CAPABLE_RX:
		अगर (input->hdcp2version_पढ़ो != PASS ||
				input->hdcp2_capable_check != PASS) अणु
			adjust->hdcp2.disable = 1;
			callback_in_ms(0, output);
			set_state_id(hdcp, output, HDCP_INITIALIZED);
		पूर्ण अन्यथा अणु
			callback_in_ms(0, output);
			set_state_id(hdcp, output, H2_A1_SEND_AKE_INIT);
		पूर्ण
		अवरोध;
	हाल H2_A1_SEND_AKE_INIT:
		अगर (input->create_session != PASS ||
				input->ake_init_prepare != PASS) अणु
			/* out of sync with psp state */
			adjust->hdcp2.disable = 1;
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (input->ake_init_ग_लिखो != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		set_watchकरोg_in_ms(hdcp, 100, output);
		callback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A1_VALIDATE_AKE_CERT);
		अवरोध;
	हाल H2_A1_VALIDATE_AKE_CERT:
		अगर (input->ake_cert_available != PASS) अणु
			अगर (event_ctx->event ==
					MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) अणु
				/* 1A-08: consider ake समयout a failure */
				/* some hdmi receivers are not पढ़ोy क्रम HDCP
				 * immediately after video becomes active,
				 * delay 1s beक्रमe retry on first HDCP message
				 * समयout.
				 */
				fail_and_restart_in_ms(1000, &status, output);
			पूर्ण अन्यथा अणु
				/* जारी ake cert polling*/
				callback_in_ms(10, output);
				increment_stay_counter(hdcp);
			पूर्ण
			अवरोध;
		पूर्ण अन्यथा अगर (input->ake_cert_पढ़ो != PASS ||
				input->ake_cert_validation != PASS) अणु
			/*
			 * 1A-09: consider invalid ake cert a failure
			 * 1A-10: consider receiver id listed in SRM a failure
			 */
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		अगर (conn->is_km_stored &&
				!adjust->hdcp2.क्रमce_no_stored_km) अणु
			callback_in_ms(0, output);
			set_state_id(hdcp, output, H2_A1_SEND_STORED_KM);
		पूर्ण अन्यथा अणु
			callback_in_ms(0, output);
			set_state_id(hdcp, output, H2_A1_SEND_NO_STORED_KM);
		पूर्ण
		अवरोध;
	हाल H2_A1_SEND_NO_STORED_KM:
		अगर (input->no_stored_km_ग_लिखो != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		अगर (adjust->hdcp2.increase_h_prime_समयout)
			set_watchकरोg_in_ms(hdcp, 2000, output);
		अन्यथा
			set_watchकरोg_in_ms(hdcp, 1000, output);
		callback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A1_READ_H_PRIME);
		अवरोध;
	हाल H2_A1_READ_H_PRIME:
		अगर (input->h_prime_available != PASS) अणु
			अगर (event_ctx->event ==
					MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) अणु
				/* 1A-11-3: consider h' समयout a failure */
				fail_and_restart_in_ms(1000, &status, output);
			पूर्ण अन्यथा अणु
				/* जारी h' polling */
				callback_in_ms(100, output);
				increment_stay_counter(hdcp);
			पूर्ण
			अवरोध;
		पूर्ण अन्यथा अगर (input->h_prime_पढ़ो != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		set_watchकरोg_in_ms(hdcp, 200, output);
		callback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A1_READ_PAIRING_INFO_AND_VALIDATE_H_PRIME);
		अवरोध;
	हाल H2_A1_READ_PAIRING_INFO_AND_VALIDATE_H_PRIME:
		अगर (input->pairing_available != PASS) अणु
			अगर (event_ctx->event ==
					MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) अणु
				/* 1A-12: consider pairing info समयout
				 * a failure
				 */
				fail_and_restart_in_ms(0, &status, output);
			पूर्ण अन्यथा अणु
				/* जारी pairing info polling */
				callback_in_ms(20, output);
				increment_stay_counter(hdcp);
			पूर्ण
			अवरोध;
		पूर्ण अन्यथा अगर (input->pairing_info_पढ़ो != PASS ||
				input->h_prime_validation != PASS) अणु
			/* 1A-11-1: consider invalid h' a failure */
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		callback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A2_LOCALITY_CHECK);
		अवरोध;
	हाल H2_A1_SEND_STORED_KM:
		अगर (input->stored_km_ग_लिखो != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		set_watchकरोg_in_ms(hdcp, 200, output);
		callback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A1_VALIDATE_H_PRIME);
		अवरोध;
	हाल H2_A1_VALIDATE_H_PRIME:
		अगर (input->h_prime_available != PASS) अणु
			अगर (event_ctx->event ==
					MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) अणु
				/* 1A-11-2: consider h' समयout a failure */
				fail_and_restart_in_ms(1000, &status, output);
			पूर्ण अन्यथा अणु
				/* जारी h' polling */
				callback_in_ms(20, output);
				increment_stay_counter(hdcp);
			पूर्ण
			अवरोध;
		पूर्ण अन्यथा अगर (input->h_prime_पढ़ो != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (input->h_prime_validation != PASS) अणु
			/* 1A-11-1: consider invalid h' a failure */
			adjust->hdcp2.क्रमce_no_stored_km = 1;
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		callback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A2_LOCALITY_CHECK);
		अवरोध;
	हाल H2_A2_LOCALITY_CHECK:
		अगर (hdcp->state.stay_count > 10 ||
				input->lc_init_prepare != PASS ||
				input->lc_init_ग_लिखो != PASS ||
				input->l_prime_available_poll != PASS ||
				input->l_prime_पढ़ो != PASS) अणु
			/*
			 * 1A-05: consider disconnection after LC init a failure
			 * 1A-13-1: consider invalid l' a failure
			 * 1A-13-2: consider l' समयout a failure
			 */
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (input->l_prime_validation != PASS) अणु
			callback_in_ms(0, output);
			increment_stay_counter(hdcp);
			अवरोध;
		पूर्ण
		callback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A3_EXCHANGE_KS_AND_TEST_FOR_REPEATER);
		अवरोध;
	हाल H2_A3_EXCHANGE_KS_AND_TEST_FOR_REPEATER:
		अगर (input->eks_prepare != PASS ||
				input->eks_ग_लिखो != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		अगर (conn->is_repeater) अणु
			set_watchकरोg_in_ms(hdcp, 3000, output);
			callback_in_ms(0, output);
			set_state_id(hdcp, output, H2_A6_WAIT_FOR_RX_ID_LIST);
		पूर्ण अन्यथा अणु
			/* some CTS equipment requires a delay GREATER than
			 * 200 ms, so delay 210 ms instead of 200 ms
			 */
			callback_in_ms(210, output);
			set_state_id(hdcp, output, H2_ENABLE_ENCRYPTION);
		पूर्ण
		अवरोध;
	हाल H2_ENABLE_ENCRYPTION:
		अगर (input->rxstatus_पढ़ो != PASS ||
				input->reauth_request_check != PASS) अणु
			/*
			 * 1A-07: restart hdcp on REAUTH_REQ
			 * 1B-08: restart hdcp on REAUTH_REQ
			 */
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (event_ctx->rx_id_list_पढ़ोy && conn->is_repeater) अणु
			callback_in_ms(0, output);
			set_state_id(hdcp, output, H2_A78_VERIFY_RX_ID_LIST_AND_SEND_ACK);
			अवरोध;
		पूर्ण अन्यथा अगर (input->enable_encryption != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		callback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A5_AUTHENTICATED);
		HDCP_FULL_DDC_TRACE(hdcp);
		अवरोध;
	हाल H2_A5_AUTHENTICATED:
		अगर (input->rxstatus_पढ़ो == FAIL ||
				input->reauth_request_check == FAIL) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (event_ctx->rx_id_list_पढ़ोy && conn->is_repeater) अणु
			callback_in_ms(0, output);
			set_state_id(hdcp, output, H2_A78_VERIFY_RX_ID_LIST_AND_SEND_ACK);
			अवरोध;
		पूर्ण
		callback_in_ms(500, output);
		increment_stay_counter(hdcp);
		अवरोध;
	हाल H2_A6_WAIT_FOR_RX_ID_LIST:
		अगर (input->rxstatus_पढ़ो != PASS ||
				input->reauth_request_check != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (!event_ctx->rx_id_list_पढ़ोy) अणु
			अगर (event_ctx->event == MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) अणु
				/* 1B-02: consider rx id list समयout a failure */
				/* some CTS equipment's actual समयout
				 * measurement is slightly greater than 3000 ms.
				 * Delay 100 ms to ensure it is fully समयout
				 * beक्रमe re-authentication.
				 */
				fail_and_restart_in_ms(100, &status, output);
			पूर्ण अन्यथा अणु
				callback_in_ms(300, output);
				increment_stay_counter(hdcp);
			पूर्ण
			अवरोध;
		पूर्ण
		callback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A78_VERIFY_RX_ID_LIST_AND_SEND_ACK);
		अवरोध;
	हाल H2_A78_VERIFY_RX_ID_LIST_AND_SEND_ACK:
		अगर (input->rxstatus_पढ़ो != PASS ||
				input->reauth_request_check != PASS ||
				input->rx_id_list_पढ़ो != PASS ||
				input->device_count_check != PASS ||
				input->rx_id_list_validation != PASS ||
				input->repeater_auth_ack_ग_लिखो != PASS) अणु
			/* 1B-03: consider invalid v' a failure
			 * 1B-04: consider MAX_DEVS_EXCEEDED a failure
			 * 1B-05: consider MAX_CASCADE_EXCEEDED a failure
			 * 1B-06: consider invalid seq_num_V a failure
			 * 1B-09: consider seq_num_V rollover a failure
			 */
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		callback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A9_SEND_STREAM_MANAGEMENT);
		अवरोध;
	हाल H2_A9_SEND_STREAM_MANAGEMENT:
		अगर (input->rxstatus_पढ़ो != PASS ||
				input->reauth_request_check != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (event_ctx->rx_id_list_पढ़ोy && conn->is_repeater) अणु
			callback_in_ms(0, output);
			set_state_id(hdcp, output, H2_A78_VERIFY_RX_ID_LIST_AND_SEND_ACK);
			अवरोध;
		पूर्ण अन्यथा अगर (input->prepare_stream_manage != PASS ||
				input->stream_manage_ग_लिखो != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		set_watchकरोg_in_ms(hdcp, 100, output);
		callback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A9_VALIDATE_STREAM_READY);
		अवरोध;
	हाल H2_A9_VALIDATE_STREAM_READY:
		अगर (input->rxstatus_पढ़ो != PASS ||
				input->reauth_request_check != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (event_ctx->rx_id_list_पढ़ोy && conn->is_repeater) अणु
			callback_in_ms(0, output);
			set_state_id(hdcp, output, H2_A78_VERIFY_RX_ID_LIST_AND_SEND_ACK);
			अवरोध;
		पूर्ण अन्यथा अगर (input->stream_पढ़ोy_available != PASS) अणु
			अगर (event_ctx->event == MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) अणु
				/* 1B-10-2: restart content stream management on
				 * stream पढ़ोy समयout
				 */
				hdcp->auth.count.stream_management_retry_count++;
				callback_in_ms(0, output);
				set_state_id(hdcp, output, H2_A9_SEND_STREAM_MANAGEMENT);
			पूर्ण अन्यथा अणु
				callback_in_ms(10, output);
				increment_stay_counter(hdcp);
			पूर्ण
			अवरोध;
		पूर्ण अन्यथा अगर (input->stream_पढ़ोy_पढ़ो != PASS ||
				input->stream_पढ़ोy_validation != PASS) अणु
			/*
			 * 1B-10-1: restart content stream management
			 * on invalid M'
			 */
			अगर (hdcp->auth.count.stream_management_retry_count > 10) अणु
				fail_and_restart_in_ms(0, &status, output);
			पूर्ण अन्यथा अणु
				hdcp->auth.count.stream_management_retry_count++;
				callback_in_ms(0, output);
				set_state_id(hdcp, output, H2_A9_SEND_STREAM_MANAGEMENT);
			पूर्ण
			अवरोध;
		पूर्ण
		callback_in_ms(200, output);
		set_state_id(hdcp, output, H2_ENABLE_ENCRYPTION);
		अवरोध;
	शेष:
		status = MOD_HDCP_STATUS_INVALID_STATE;
		fail_and_restart_in_ms(0, &status, output);
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp2_dp_transition(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input,
		काष्ठा mod_hdcp_output *output)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;
	काष्ठा mod_hdcp_connection *conn = &hdcp->connection;
	काष्ठा mod_hdcp_link_adjusपंचांगent *adjust = &hdcp->connection.link.adjust;

	चयन (current_state(hdcp)) अणु
	हाल D2_A0_DETERMINE_RX_HDCP_CAPABLE:
		अगर (input->rx_caps_पढ़ो_dp != PASS ||
				input->hdcp2_capable_check != PASS) अणु
			adjust->hdcp2.disable = 1;
			callback_in_ms(0, output);
			set_state_id(hdcp, output, HDCP_INITIALIZED);
		पूर्ण अन्यथा अणु
			callback_in_ms(0, output);
			set_state_id(hdcp, output, D2_A1_SEND_AKE_INIT);
		पूर्ण
		अवरोध;
	हाल D2_A1_SEND_AKE_INIT:
		अगर (input->create_session != PASS ||
				input->ake_init_prepare != PASS) अणु
			/* out of sync with psp state */
			adjust->hdcp2.disable = 1;
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (input->ake_init_ग_लिखो != PASS) अणु
			/* possibly display not पढ़ोy */
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		callback_in_ms(100, output);
		set_state_id(hdcp, output, D2_A1_VALIDATE_AKE_CERT);
		अवरोध;
	हाल D2_A1_VALIDATE_AKE_CERT:
		अगर (input->ake_cert_पढ़ो != PASS ||
				input->ake_cert_validation != PASS) अणु
			/*
			 * 1A-08: consider invalid ake cert a failure
			 * 1A-09: consider receiver id listed in SRM a failure
			 */
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		अगर (conn->is_km_stored &&
				!adjust->hdcp2.क्रमce_no_stored_km) अणु
			callback_in_ms(0, output);
			set_state_id(hdcp, output, D2_A1_SEND_STORED_KM);
		पूर्ण अन्यथा अणु
			callback_in_ms(0, output);
			set_state_id(hdcp, output, D2_A1_SEND_NO_STORED_KM);
		पूर्ण
		अवरोध;
	हाल D2_A1_SEND_NO_STORED_KM:
		अगर (input->no_stored_km_ग_लिखो != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		अगर (adjust->hdcp2.increase_h_prime_समयout)
			set_watchकरोg_in_ms(hdcp, 2000, output);
		अन्यथा
			set_watchकरोg_in_ms(hdcp, 1000, output);
		set_state_id(hdcp, output, D2_A1_READ_H_PRIME);
		अवरोध;
	हाल D2_A1_READ_H_PRIME:
		अगर (input->h_prime_available != PASS) अणु
			अगर (event_ctx->event ==
					MOD_HDCP_EVENT_WATCHDOG_TIMEOUT)
				/* 1A-10-3: consider h' समयout a failure */
				fail_and_restart_in_ms(1000, &status, output);
			अन्यथा
				increment_stay_counter(hdcp);
			अवरोध;
		पूर्ण अन्यथा अगर (input->h_prime_पढ़ो != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		set_watchकरोg_in_ms(hdcp, 200, output);
		set_state_id(hdcp, output, D2_A1_READ_PAIRING_INFO_AND_VALIDATE_H_PRIME);
		अवरोध;
	हाल D2_A1_READ_PAIRING_INFO_AND_VALIDATE_H_PRIME:
		अगर (input->pairing_available != PASS) अणु
			अगर (event_ctx->event ==
					MOD_HDCP_EVENT_WATCHDOG_TIMEOUT)
				/*
				 * 1A-11: consider pairing info समयout
				 * a failure
				 */
				fail_and_restart_in_ms(0, &status, output);
			अन्यथा
				increment_stay_counter(hdcp);
			अवरोध;
		पूर्ण अन्यथा अगर (input->pairing_info_पढ़ो != PASS ||
				input->h_prime_validation != PASS) अणु
			/* 1A-10-1: consider invalid h' a failure */
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		callback_in_ms(0, output);
		set_state_id(hdcp, output, D2_A2_LOCALITY_CHECK);
		अवरोध;
	हाल D2_A1_SEND_STORED_KM:
		अगर (input->stored_km_ग_लिखो != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		set_watchकरोg_in_ms(hdcp, 200, output);
		set_state_id(hdcp, output, D2_A1_VALIDATE_H_PRIME);
		अवरोध;
	हाल D2_A1_VALIDATE_H_PRIME:
		अगर (input->h_prime_available != PASS) अणु
			अगर (event_ctx->event ==
					MOD_HDCP_EVENT_WATCHDOG_TIMEOUT)
				/* 1A-10-2: consider h' समयout a failure */
				fail_and_restart_in_ms(1000, &status, output);
			अन्यथा
				increment_stay_counter(hdcp);
			अवरोध;
		पूर्ण अन्यथा अगर (input->h_prime_पढ़ो != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (input->h_prime_validation != PASS) अणु
			/* 1A-10-1: consider invalid h' a failure */
			adjust->hdcp2.क्रमce_no_stored_km = 1;
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		callback_in_ms(0, output);
		set_state_id(hdcp, output, D2_A2_LOCALITY_CHECK);
		अवरोध;
	हाल D2_A2_LOCALITY_CHECK:
		अगर (hdcp->state.stay_count > 10 ||
				input->lc_init_prepare != PASS ||
				input->lc_init_ग_लिखो != PASS ||
				input->l_prime_पढ़ो != PASS) अणु
			/* 1A-12: consider invalid l' a failure */
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (input->l_prime_validation != PASS) अणु
			callback_in_ms(0, output);
			increment_stay_counter(hdcp);
			अवरोध;
		पूर्ण
		callback_in_ms(0, output);
		set_state_id(hdcp, output, D2_A34_EXCHANGE_KS_AND_TEST_FOR_REPEATER);
		अवरोध;
	हाल D2_A34_EXCHANGE_KS_AND_TEST_FOR_REPEATER:
		अगर (input->eks_prepare != PASS ||
				input->eks_ग_लिखो != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		अगर (conn->is_repeater) अणु
			set_watchकरोg_in_ms(hdcp, 3000, output);
			set_state_id(hdcp, output, D2_A6_WAIT_FOR_RX_ID_LIST);
		पूर्ण अन्यथा अणु
			callback_in_ms(0, output);
			set_state_id(hdcp, output, D2_SEND_CONTENT_STREAM_TYPE);
		पूर्ण
		अवरोध;
	हाल D2_SEND_CONTENT_STREAM_TYPE:
		अगर (input->rxstatus_पढ़ो != PASS ||
				input->reauth_request_check != PASS ||
				input->link_पूर्णांकegrity_check_dp != PASS ||
				input->content_stream_type_ग_लिखो != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		callback_in_ms(210, output);
		set_state_id(hdcp, output, D2_ENABLE_ENCRYPTION);
		अवरोध;
	हाल D2_ENABLE_ENCRYPTION:
		अगर (input->rxstatus_पढ़ो != PASS ||
				input->reauth_request_check != PASS ||
				input->link_पूर्णांकegrity_check_dp != PASS) अणु
			/*
			 * 1A-07: restart hdcp on REAUTH_REQ
			 * 1B-08: restart hdcp on REAUTH_REQ
			 */
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (event_ctx->rx_id_list_पढ़ोy && conn->is_repeater) अणु
			callback_in_ms(0, output);
			set_state_id(hdcp, output, D2_A78_VERIFY_RX_ID_LIST_AND_SEND_ACK);
			अवरोध;
		पूर्ण अन्यथा अगर (input->enable_encryption != PASS ||
				(is_dp_mst_hdcp(hdcp) && input->stream_encryption_dp != PASS)) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		set_state_id(hdcp, output, D2_A5_AUTHENTICATED);
		HDCP_FULL_DDC_TRACE(hdcp);
		अवरोध;
	हाल D2_A5_AUTHENTICATED:
		अगर (input->rxstatus_पढ़ो == FAIL ||
				input->reauth_request_check == FAIL) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (input->link_पूर्णांकegrity_check_dp == FAIL) अणु
			अगर (hdcp->connection.hdcp2_retry_count >= 1)
				adjust->hdcp2.क्रमce_type = MOD_HDCP_FORCE_TYPE_0;
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (event_ctx->rx_id_list_पढ़ोy && conn->is_repeater) अणु
			callback_in_ms(0, output);
			set_state_id(hdcp, output, D2_A78_VERIFY_RX_ID_LIST_AND_SEND_ACK);
			अवरोध;
		पूर्ण
		increment_stay_counter(hdcp);
		अवरोध;
	हाल D2_A6_WAIT_FOR_RX_ID_LIST:
		अगर (input->rxstatus_पढ़ो != PASS ||
				input->reauth_request_check != PASS ||
				input->link_पूर्णांकegrity_check_dp != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (!event_ctx->rx_id_list_पढ़ोy) अणु
			अगर (event_ctx->event == MOD_HDCP_EVENT_WATCHDOG_TIMEOUT)
				/* 1B-02: consider rx id list समयout a failure */
				fail_and_restart_in_ms(0, &status, output);
			अन्यथा
				increment_stay_counter(hdcp);
			अवरोध;
		पूर्ण
		callback_in_ms(0, output);
		set_state_id(hdcp, output, D2_A78_VERIFY_RX_ID_LIST_AND_SEND_ACK);
		अवरोध;
	हाल D2_A78_VERIFY_RX_ID_LIST_AND_SEND_ACK:
		अगर (input->rxstatus_पढ़ो != PASS ||
				input->reauth_request_check != PASS ||
				input->link_पूर्णांकegrity_check_dp != PASS ||
				input->rx_id_list_पढ़ो != PASS ||
				input->device_count_check != PASS ||
				input->rx_id_list_validation != PASS ||
				input->repeater_auth_ack_ग_लिखो != PASS) अणु
			/*
			 * 1B-03: consider invalid v' a failure
			 * 1B-04: consider MAX_DEVS_EXCEEDED a failure
			 * 1B-05: consider MAX_CASCADE_EXCEEDED a failure
			 * 1B-06: consider invalid seq_num_V a failure
			 * 1B-09: consider seq_num_V rollover a failure
			 */
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		callback_in_ms(0, output);
		set_state_id(hdcp, output, D2_A9_SEND_STREAM_MANAGEMENT);
		अवरोध;
	हाल D2_A9_SEND_STREAM_MANAGEMENT:
		अगर (input->rxstatus_पढ़ो != PASS ||
				input->reauth_request_check != PASS ||
				input->link_पूर्णांकegrity_check_dp != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (event_ctx->rx_id_list_पढ़ोy) अणु
			callback_in_ms(0, output);
			set_state_id(hdcp, output, D2_A78_VERIFY_RX_ID_LIST_AND_SEND_ACK);
			अवरोध;
		पूर्ण अन्यथा अगर (input->prepare_stream_manage != PASS ||
				input->stream_manage_ग_लिखो != PASS) अणु
			अगर (event_ctx->event == MOD_HDCP_EVENT_CALLBACK)
				fail_and_restart_in_ms(0, &status, output);
			अन्यथा
				increment_stay_counter(hdcp);
			अवरोध;
		पूर्ण
		callback_in_ms(100, output);
		set_state_id(hdcp, output, D2_A9_VALIDATE_STREAM_READY);
		अवरोध;
	हाल D2_A9_VALIDATE_STREAM_READY:
		अगर (input->rxstatus_पढ़ो != PASS ||
				input->reauth_request_check != PASS ||
				input->link_पूर्णांकegrity_check_dp != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (event_ctx->rx_id_list_पढ़ोy) अणु
			callback_in_ms(0, output);
			set_state_id(hdcp, output, D2_A78_VERIFY_RX_ID_LIST_AND_SEND_ACK);
			अवरोध;
		पूर्ण अन्यथा अगर (input->stream_पढ़ोy_पढ़ो != PASS ||
				input->stream_पढ़ोy_validation != PASS) अणु
			/*
			 * 1B-10-1: restart content stream management
			 * on invalid M'
			 * 1B-10-2: consider stream पढ़ोy समयout a failure
			 */
			अगर (hdcp->auth.count.stream_management_retry_count > 10) अणु
				fail_and_restart_in_ms(0, &status, output);
			पूर्ण अन्यथा अगर (event_ctx->event == MOD_HDCP_EVENT_CALLBACK) अणु
				hdcp->auth.count.stream_management_retry_count++;
				callback_in_ms(0, output);
				set_state_id(hdcp, output, D2_A9_SEND_STREAM_MANAGEMENT);
			पूर्ण अन्यथा अणु
				increment_stay_counter(hdcp);
			पूर्ण
			अवरोध;
		पूर्ण
		callback_in_ms(200, output);
		set_state_id(hdcp, output, D2_ENABLE_ENCRYPTION);
		अवरोध;
	शेष:
		status = MOD_HDCP_STATUS_INVALID_STATE;
		fail_and_restart_in_ms(0, &status, output);
		अवरोध;
	पूर्ण
	वापस status;
पूर्ण
