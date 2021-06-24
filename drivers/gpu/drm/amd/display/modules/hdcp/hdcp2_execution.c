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

#समावेश <linux/delay.h>

#समावेश "hdcp.h"

अटल अंतरभूत क्रमागत mod_hdcp_status check_receiver_id_list_पढ़ोy(काष्ठा mod_hdcp *hdcp)
अणु
	uपूर्णांक8_t is_पढ़ोy = 0;

	अगर (is_dp_hdcp(hdcp))
		is_पढ़ोy = HDCP_2_2_DP_RXSTATUS_READY(hdcp->auth.msg.hdcp2.rxstatus_dp) ? 1 : 0;
	अन्यथा
		is_पढ़ोy = (HDCP_2_2_HDMI_RXSTATUS_READY(hdcp->auth.msg.hdcp2.rxstatus[1]) &&
				(HDCP_2_2_HDMI_RXSTATUS_MSG_SZ_HI(hdcp->auth.msg.hdcp2.rxstatus[1]) << 8 |
						hdcp->auth.msg.hdcp2.rxstatus[0])) ? 1 : 0;
	वापस is_पढ़ोy ? MOD_HDCP_STATUS_SUCCESS :
			MOD_HDCP_STATUS_HDCP2_RX_ID_LIST_NOT_READY;
पूर्ण

अटल अंतरभूत क्रमागत mod_hdcp_status check_hdcp2_capable(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp))
		status = (hdcp->auth.msg.hdcp2.rxcaps_dp[0] == HDCP_2_2_RX_CAPS_VERSION_VAL) &&
				HDCP_2_2_DP_HDCP_CAPABLE(hdcp->auth.msg.hdcp2.rxcaps_dp[2]) ?
				MOD_HDCP_STATUS_SUCCESS :
				MOD_HDCP_STATUS_HDCP2_NOT_CAPABLE;
	अन्यथा
		status = (hdcp->auth.msg.hdcp2.hdcp2version_hdmi & HDCP_2_2_HDMI_SUPPORT_MASK) ?
				MOD_HDCP_STATUS_SUCCESS :
				MOD_HDCP_STATUS_HDCP2_NOT_CAPABLE;
	वापस status;
पूर्ण

अटल अंतरभूत क्रमागत mod_hdcp_status check_reauthentication_request(
		काष्ठा mod_hdcp *hdcp)
अणु
	uपूर्णांक8_t ret = 0;

	अगर (is_dp_hdcp(hdcp))
		ret = HDCP_2_2_DP_RXSTATUS_REAUTH_REQ(hdcp->auth.msg.hdcp2.rxstatus_dp) ?
				MOD_HDCP_STATUS_HDCP2_REAUTH_REQUEST :
				MOD_HDCP_STATUS_SUCCESS;
	अन्यथा
		ret = HDCP_2_2_HDMI_RXSTATUS_REAUTH_REQ(hdcp->auth.msg.hdcp2.rxstatus[1]) ?
				MOD_HDCP_STATUS_HDCP2_REAUTH_REQUEST :
				MOD_HDCP_STATUS_SUCCESS;
	वापस ret;
पूर्ण

अटल अंतरभूत क्रमागत mod_hdcp_status check_link_पूर्णांकegrity_failure_dp(
		काष्ठा mod_hdcp *hdcp)
अणु
	वापस HDCP_2_2_DP_RXSTATUS_LINK_FAILED(hdcp->auth.msg.hdcp2.rxstatus_dp) ?
			MOD_HDCP_STATUS_HDCP2_REAUTH_LINK_INTEGRITY_FAILURE :
			MOD_HDCP_STATUS_SUCCESS;
पूर्ण

अटल क्रमागत mod_hdcp_status check_ake_cert_available(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;
	uपूर्णांक16_t size;

	अगर (is_dp_hdcp(hdcp)) अणु
		status = MOD_HDCP_STATUS_SUCCESS;
	पूर्ण अन्यथा अणु
		status = mod_hdcp_पढ़ो_rxstatus(hdcp);
		अगर (status == MOD_HDCP_STATUS_SUCCESS) अणु
			size = HDCP_2_2_HDMI_RXSTATUS_MSG_SZ_HI(hdcp->auth.msg.hdcp2.rxstatus[1]) << 8 |
			       hdcp->auth.msg.hdcp2.rxstatus[0];
			status = (size == माप(hdcp->auth.msg.hdcp2.ake_cert)) ?
					MOD_HDCP_STATUS_SUCCESS :
					MOD_HDCP_STATUS_HDCP2_AKE_CERT_PENDING;
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status check_h_prime_available(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;
	uपूर्णांक8_t size;

	status = mod_hdcp_पढ़ो_rxstatus(hdcp);
	अगर (status != MOD_HDCP_STATUS_SUCCESS)
		जाओ out;

	अगर (is_dp_hdcp(hdcp)) अणु
		status = HDCP_2_2_DP_RXSTATUS_H_PRIME(hdcp->auth.msg.hdcp2.rxstatus_dp) ?
				MOD_HDCP_STATUS_SUCCESS :
				MOD_HDCP_STATUS_HDCP2_H_PRIME_PENDING;
	पूर्ण अन्यथा अणु
		size = HDCP_2_2_HDMI_RXSTATUS_MSG_SZ_HI(hdcp->auth.msg.hdcp2.rxstatus[1]) << 8 |
		       hdcp->auth.msg.hdcp2.rxstatus[0];
		status = (size == माप(hdcp->auth.msg.hdcp2.ake_h_prime)) ?
				MOD_HDCP_STATUS_SUCCESS :
				MOD_HDCP_STATUS_HDCP2_H_PRIME_PENDING;
	पूर्ण
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status check_pairing_info_available(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;
	uपूर्णांक8_t size;

	status = mod_hdcp_पढ़ो_rxstatus(hdcp);
	अगर (status != MOD_HDCP_STATUS_SUCCESS)
		जाओ out;

	अगर (is_dp_hdcp(hdcp)) अणु
		status = HDCP_2_2_DP_RXSTATUS_PAIRING(hdcp->auth.msg.hdcp2.rxstatus_dp) ?
				MOD_HDCP_STATUS_SUCCESS :
				MOD_HDCP_STATUS_HDCP2_PAIRING_INFO_PENDING;
	पूर्ण अन्यथा अणु
		size = HDCP_2_2_HDMI_RXSTATUS_MSG_SZ_HI(hdcp->auth.msg.hdcp2.rxstatus[1]) << 8 |
		       hdcp->auth.msg.hdcp2.rxstatus[0];
		status = (size == माप(hdcp->auth.msg.hdcp2.ake_pairing_info)) ?
				MOD_HDCP_STATUS_SUCCESS :
				MOD_HDCP_STATUS_HDCP2_PAIRING_INFO_PENDING;
	पूर्ण
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status poll_l_prime_available(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;
	uपूर्णांक8_t size;
	uपूर्णांक16_t max_रुको = 20; // units of ms
	uपूर्णांक16_t num_polls = 5;
	uपूर्णांक16_t रुको_समय = max_रुको / num_polls;

	अगर (is_dp_hdcp(hdcp))
		status = MOD_HDCP_STATUS_INVALID_OPERATION;
	अन्यथा
		क्रम (; num_polls; num_polls--) अणु
			msleep(रुको_समय);

			status = mod_hdcp_पढ़ो_rxstatus(hdcp);
			अगर (status != MOD_HDCP_STATUS_SUCCESS)
				अवरोध;

			size = HDCP_2_2_HDMI_RXSTATUS_MSG_SZ_HI(hdcp->auth.msg.hdcp2.rxstatus[1]) << 8 |
			       hdcp->auth.msg.hdcp2.rxstatus[0];
			status = (size == माप(hdcp->auth.msg.hdcp2.lc_l_prime)) ?
					MOD_HDCP_STATUS_SUCCESS :
					MOD_HDCP_STATUS_HDCP2_L_PRIME_PENDING;
			अगर (status == MOD_HDCP_STATUS_SUCCESS)
				अवरोध;
		पूर्ण
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status check_stream_पढ़ोy_available(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;
	uपूर्णांक8_t size;

	अगर (is_dp_hdcp(hdcp)) अणु
		status = MOD_HDCP_STATUS_INVALID_OPERATION;
	पूर्ण अन्यथा अणु
		status = mod_hdcp_पढ़ो_rxstatus(hdcp);
		अगर (status != MOD_HDCP_STATUS_SUCCESS)
			जाओ out;
		size = HDCP_2_2_HDMI_RXSTATUS_MSG_SZ_HI(hdcp->auth.msg.hdcp2.rxstatus[1]) << 8 |
		       hdcp->auth.msg.hdcp2.rxstatus[0];
		status = (size == माप(hdcp->auth.msg.hdcp2.repeater_auth_stream_पढ़ोy)) ?
				MOD_HDCP_STATUS_SUCCESS :
				MOD_HDCP_STATUS_HDCP2_STREAM_READY_PENDING;
	पूर्ण
out:
	वापस status;
पूर्ण

अटल अंतरभूत uपूर्णांक8_t get_device_count(काष्ठा mod_hdcp *hdcp)
अणु
	वापस HDCP_2_2_DEV_COUNT_LO(hdcp->auth.msg.hdcp2.rx_id_list[2]) +
			(HDCP_2_2_DEV_COUNT_HI(hdcp->auth.msg.hdcp2.rx_id_list[1]) << 4);
पूर्ण

अटल क्रमागत mod_hdcp_status check_device_count(काष्ठा mod_hdcp *hdcp)
अणु
	/* Some MST display may choose to report the पूर्णांकernal panel as an HDCP RX.   */
	/* To update this condition with 1(because the immediate repeater's पूर्णांकernal */
	/* panel is possibly not included in DEVICE_COUNT) + get_device_count(hdcp). */
	/* Device count must be greater than or equal to tracked hdcp displays.      */
	वापस ((1 + get_device_count(hdcp)) < get_active_display_count(hdcp)) ?
			MOD_HDCP_STATUS_HDCP2_DEVICE_COUNT_MISMATCH_FAILURE :
			MOD_HDCP_STATUS_SUCCESS;
पूर्ण

अटल uपूर्णांक8_t process_rxstatus(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input,
		क्रमागत mod_hdcp_status *status)
अणु
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_rxstatus,
			&input->rxstatus_पढ़ो, status,
			hdcp, "rxstatus_read"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(check_reauthentication_request,
			&input->reauth_request_check, status,
			hdcp, "reauth_request_check"))
		जाओ out;
	अगर (is_dp_hdcp(hdcp)) अणु
		अगर (!mod_hdcp_execute_and_set(check_link_पूर्णांकegrity_failure_dp,
				&input->link_पूर्णांकegrity_check_dp, status,
				hdcp, "link_integrity_check_dp"))
			जाओ out;
	पूर्ण
	अगर (hdcp->connection.is_repeater)
		अगर (check_receiver_id_list_पढ़ोy(hdcp) ==
				MOD_HDCP_STATUS_SUCCESS) अणु
			HDCP_INPUT_PASS_TRACE(hdcp, "rx_id_list_ready");
			event_ctx->rx_id_list_पढ़ोy = 1;
			अगर (is_dp_hdcp(hdcp))
				hdcp->auth.msg.hdcp2.rx_id_list_size =
						माप(hdcp->auth.msg.hdcp2.rx_id_list);
			अन्यथा
				hdcp->auth.msg.hdcp2.rx_id_list_size =
					HDCP_2_2_HDMI_RXSTATUS_MSG_SZ_HI(hdcp->auth.msg.hdcp2.rxstatus[1]) << 8 |
					hdcp->auth.msg.hdcp2.rxstatus[0];
		पूर्ण
out:
	वापस (*status == MOD_HDCP_STATUS_SUCCESS);
पूर्ण

अटल क्रमागत mod_hdcp_status known_hdcp2_capable_rx(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_hdcp2version,
			&input->hdcp2version_पढ़ो, &status,
			hdcp, "hdcp2version_read"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(check_hdcp2_capable,
			&input->hdcp2_capable_check, &status,
			hdcp, "hdcp2_capable"))
		जाओ out;
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status send_ake_init(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_create_session,
			&input->create_session, &status,
			hdcp, "create_session"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_prepare_ake_init,
			&input->ake_init_prepare, &status,
			hdcp, "ake_init_prepare"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_ग_लिखो_ake_init,
			&input->ake_init_ग_लिखो, &status,
			hdcp, "ake_init_write"))
		जाओ out;
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status validate_ake_cert(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;


	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK &&
			event_ctx->event != MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (is_hdmi_dvi_sl_hdcp(hdcp))
		अगर (!mod_hdcp_execute_and_set(check_ake_cert_available,
				&input->ake_cert_available, &status,
				hdcp, "ake_cert_available"))
			जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_ake_cert,
			&input->ake_cert_पढ़ो, &status,
			hdcp, "ake_cert_read"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_validate_ake_cert,
			&input->ake_cert_validation, &status,
			hdcp, "ake_cert_validation"))
		जाओ out;
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status send_no_stored_km(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (!mod_hdcp_execute_and_set(mod_hdcp_ग_लिखो_no_stored_km,
			&input->no_stored_km_ग_लिखो, &status,
			hdcp, "no_stored_km_write"))
		जाओ out;
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status पढ़ो_h_prime(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIRQ &&
			event_ctx->event != MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (!mod_hdcp_execute_and_set(check_h_prime_available,
			&input->h_prime_available, &status,
			hdcp, "h_prime_available"))
		जाओ out;

	अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_h_prime,
			&input->h_prime_पढ़ो, &status,
			hdcp, "h_prime_read"))
		जाओ out;
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status पढ़ो_pairing_info_and_validate_h_prime(
		काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIRQ &&
			event_ctx->event != MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (!mod_hdcp_execute_and_set(check_pairing_info_available,
			&input->pairing_available, &status,
			hdcp, "pairing_available"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_pairing_info,
			&input->pairing_info_पढ़ो, &status,
			hdcp, "pairing_info_read"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_validate_h_prime,
			&input->h_prime_validation, &status,
			hdcp, "h_prime_validation"))
		जाओ out;
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status send_stored_km(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (!mod_hdcp_execute_and_set(mod_hdcp_ग_लिखो_stored_km,
			&input->stored_km_ग_लिखो, &status,
			hdcp, "stored_km_write"))
		जाओ out;
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status validate_h_prime(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIRQ &&
			event_ctx->event != MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (!mod_hdcp_execute_and_set(check_h_prime_available,
			&input->h_prime_available, &status,
			hdcp, "h_prime_available"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_h_prime,
			&input->h_prime_पढ़ो, &status,
			hdcp, "h_prime_read"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_validate_h_prime,
			&input->h_prime_validation, &status,
			hdcp, "h_prime_validation"))
		जाओ out;
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status locality_check(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_prepare_lc_init,
			&input->lc_init_prepare, &status,
			hdcp, "lc_init_prepare"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_ग_लिखो_lc_init,
			&input->lc_init_ग_लिखो, &status,
			 hdcp, "lc_init_write"))
		जाओ out;
	अगर (is_dp_hdcp(hdcp))
		msleep(16);
	अन्यथा
		अगर (!mod_hdcp_execute_and_set(poll_l_prime_available,
				&input->l_prime_available_poll, &status,
				hdcp, "l_prime_available_poll"))
			जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_l_prime,
			&input->l_prime_पढ़ो, &status,
			hdcp, "l_prime_read"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_validate_l_prime,
			&input->l_prime_validation, &status,
			hdcp, "l_prime_validation"))
		जाओ out;
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status exchange_ks_and_test_क्रम_repeater(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_prepare_eks,
			&input->eks_prepare, &status,
			hdcp, "eks_prepare"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_ग_लिखो_eks,
			&input->eks_ग_लिखो, &status,
			hdcp, "eks_write"))
		जाओ out;
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status enable_encryption(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIRQ) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण
	अगर (event_ctx->event == MOD_HDCP_EVENT_CPIRQ) अणु
		process_rxstatus(hdcp, event_ctx, input, &status);
		जाओ out;
	पूर्ण

	अगर (is_hdmi_dvi_sl_hdcp(hdcp)) अणु
		अगर (!process_rxstatus(hdcp, event_ctx, input, &status))
			जाओ out;
		अगर (event_ctx->rx_id_list_पढ़ोy)
			जाओ out;
	पूर्ण
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_enable_encryption,
			&input->enable_encryption, &status,
			hdcp, "enable_encryption"))
		जाओ out;
	अगर (is_dp_mst_hdcp(hdcp)) अणु
		अगर (!mod_hdcp_execute_and_set(
				mod_hdcp_hdcp2_enable_dp_stream_encryption,
				&input->stream_encryption_dp, &status,
				hdcp, "stream_encryption_dp"))
			जाओ out;
	पूर्ण
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status authenticated(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIRQ) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	process_rxstatus(hdcp, event_ctx, input, &status);

	अगर (status != MOD_HDCP_STATUS_SUCCESS)
		mod_hdcp_save_current_encryption_states(hdcp);
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status रुको_क्रम_rx_id_list(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIRQ &&
			event_ctx->event != MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (!process_rxstatus(hdcp, event_ctx, input, &status))
		जाओ out;
	अगर (!event_ctx->rx_id_list_पढ़ोy) अणु
		status = MOD_HDCP_STATUS_HDCP2_RX_ID_LIST_NOT_READY;
		जाओ out;
	पूर्ण
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status verअगरy_rx_id_list_and_send_ack(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIRQ) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण
	अगर (event_ctx->event == MOD_HDCP_EVENT_CPIRQ) अणु
		process_rxstatus(hdcp, event_ctx, input, &status);
		जाओ out;
	पूर्ण

	अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_rx_id_list,
			&input->rx_id_list_पढ़ो,
			&status, hdcp, "receiver_id_list_read"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(check_device_count,
			&input->device_count_check,
			&status, hdcp, "device_count_check"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_validate_rx_id_list,
			&input->rx_id_list_validation,
			&status, hdcp, "rx_id_list_validation"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_ग_लिखो_repeater_auth_ack,
			&input->repeater_auth_ack_ग_लिखो,
			&status, hdcp, "repeater_auth_ack_write"))
		जाओ out;
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status send_stream_management(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIRQ) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण
	अगर (event_ctx->event == MOD_HDCP_EVENT_CPIRQ) अणु
		process_rxstatus(hdcp, event_ctx, input, &status);
		जाओ out;
	पूर्ण

	अगर (is_hdmi_dvi_sl_hdcp(hdcp)) अणु
		अगर (!process_rxstatus(hdcp, event_ctx, input, &status))
			जाओ out;
		अगर (event_ctx->rx_id_list_पढ़ोy)
			जाओ out;
	पूर्ण
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_prepare_stream_management,
			&input->prepare_stream_manage,
			&status, hdcp, "prepare_stream_manage"))
		जाओ out;

	अगर (!mod_hdcp_execute_and_set(mod_hdcp_ग_लिखो_stream_manage,
			&input->stream_manage_ग_लिखो,
			&status, hdcp, "stream_manage_write"))
		जाओ out;
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status validate_stream_पढ़ोy(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIRQ &&
			event_ctx->event != MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण
	अगर (event_ctx->event == MOD_HDCP_EVENT_CPIRQ) अणु
		process_rxstatus(hdcp, event_ctx, input, &status);
		जाओ out;
	पूर्ण

	अगर (is_hdmi_dvi_sl_hdcp(hdcp)) अणु
		अगर (!process_rxstatus(hdcp, event_ctx, input, &status))
			जाओ out;
		अगर (event_ctx->rx_id_list_पढ़ोy) अणु
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (is_hdmi_dvi_sl_hdcp(hdcp))
		अगर (!mod_hdcp_execute_and_set(check_stream_पढ़ोy_available,
				&input->stream_पढ़ोy_available,
				&status, hdcp, "stream_ready_available"))
			जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_stream_पढ़ोy,
			&input->stream_पढ़ोy_पढ़ो,
			&status, hdcp, "stream_ready_read"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_validate_stream_पढ़ोy,
			&input->stream_पढ़ोy_validation,
			&status, hdcp, "stream_ready_validation"))
		जाओ out;

out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status determine_rx_hdcp_capable_dp(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_rxcaps,
			&input->rx_caps_पढ़ो_dp,
			&status, hdcp, "rx_caps_read_dp"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(check_hdcp2_capable,
			&input->hdcp2_capable_check, &status,
			hdcp, "hdcp2_capable_check"))
		जाओ out;
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status send_content_stream_type_dp(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp2 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIRQ) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (!process_rxstatus(hdcp, event_ctx, input, &status))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_ग_लिखो_content_type,
			&input->content_stream_type_ग_लिखो, &status,
			hdcp, "content_stream_type_write"))
		जाओ out;
out:
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp2_execution(काष्ठा mod_hdcp *hdcp,
	काष्ठा mod_hdcp_event_context *event_ctx,
	काष्ठा mod_hdcp_transition_input_hdcp2 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	चयन (current_state(hdcp)) अणु
	हाल H2_A0_KNOWN_HDCP2_CAPABLE_RX:
		status = known_hdcp2_capable_rx(hdcp, event_ctx, input);
		अवरोध;
	हाल H2_A1_SEND_AKE_INIT:
		status = send_ake_init(hdcp, event_ctx, input);
		अवरोध;
	हाल H2_A1_VALIDATE_AKE_CERT:
		status = validate_ake_cert(hdcp, event_ctx, input);
		अवरोध;
	हाल H2_A1_SEND_NO_STORED_KM:
		status = send_no_stored_km(hdcp, event_ctx, input);
		अवरोध;
	हाल H2_A1_READ_H_PRIME:
		status = पढ़ो_h_prime(hdcp, event_ctx, input);
		अवरोध;
	हाल H2_A1_READ_PAIRING_INFO_AND_VALIDATE_H_PRIME:
		status = पढ़ो_pairing_info_and_validate_h_prime(hdcp,
				event_ctx, input);
		अवरोध;
	हाल H2_A1_SEND_STORED_KM:
		status = send_stored_km(hdcp, event_ctx, input);
		अवरोध;
	हाल H2_A1_VALIDATE_H_PRIME:
		status = validate_h_prime(hdcp, event_ctx, input);
		अवरोध;
	हाल H2_A2_LOCALITY_CHECK:
		status = locality_check(hdcp, event_ctx, input);
		अवरोध;
	हाल H2_A3_EXCHANGE_KS_AND_TEST_FOR_REPEATER:
		status = exchange_ks_and_test_क्रम_repeater(hdcp, event_ctx, input);
		अवरोध;
	हाल H2_ENABLE_ENCRYPTION:
		status = enable_encryption(hdcp, event_ctx, input);
		अवरोध;
	हाल H2_A5_AUTHENTICATED:
		status = authenticated(hdcp, event_ctx, input);
		अवरोध;
	हाल H2_A6_WAIT_FOR_RX_ID_LIST:
		status = रुको_क्रम_rx_id_list(hdcp, event_ctx, input);
		अवरोध;
	हाल H2_A78_VERIFY_RX_ID_LIST_AND_SEND_ACK:
		status = verअगरy_rx_id_list_and_send_ack(hdcp, event_ctx, input);
		अवरोध;
	हाल H2_A9_SEND_STREAM_MANAGEMENT:
		status = send_stream_management(hdcp, event_ctx, input);
		अवरोध;
	हाल H2_A9_VALIDATE_STREAM_READY:
		status = validate_stream_पढ़ोy(hdcp, event_ctx, input);
		अवरोध;
	शेष:
		status = MOD_HDCP_STATUS_INVALID_STATE;
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp2_dp_execution(काष्ठा mod_hdcp *hdcp,
	काष्ठा mod_hdcp_event_context *event_ctx,
	काष्ठा mod_hdcp_transition_input_hdcp2 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	चयन (current_state(hdcp)) अणु
	हाल D2_A0_DETERMINE_RX_HDCP_CAPABLE:
		status = determine_rx_hdcp_capable_dp(hdcp, event_ctx, input);
		अवरोध;
	हाल D2_A1_SEND_AKE_INIT:
		status = send_ake_init(hdcp, event_ctx, input);
		अवरोध;
	हाल D2_A1_VALIDATE_AKE_CERT:
		status = validate_ake_cert(hdcp, event_ctx, input);
		अवरोध;
	हाल D2_A1_SEND_NO_STORED_KM:
		status = send_no_stored_km(hdcp, event_ctx, input);
		अवरोध;
	हाल D2_A1_READ_H_PRIME:
		status = पढ़ो_h_prime(hdcp, event_ctx, input);
		अवरोध;
	हाल D2_A1_READ_PAIRING_INFO_AND_VALIDATE_H_PRIME:
		status = पढ़ो_pairing_info_and_validate_h_prime(hdcp,
				event_ctx, input);
		अवरोध;
	हाल D2_A1_SEND_STORED_KM:
		status = send_stored_km(hdcp, event_ctx, input);
		अवरोध;
	हाल D2_A1_VALIDATE_H_PRIME:
		status = validate_h_prime(hdcp, event_ctx, input);
		अवरोध;
	हाल D2_A2_LOCALITY_CHECK:
		status = locality_check(hdcp, event_ctx, input);
		अवरोध;
	हाल D2_A34_EXCHANGE_KS_AND_TEST_FOR_REPEATER:
		status = exchange_ks_and_test_क्रम_repeater(hdcp,
				event_ctx, input);
		अवरोध;
	हाल D2_SEND_CONTENT_STREAM_TYPE:
		status = send_content_stream_type_dp(hdcp, event_ctx, input);
		अवरोध;
	हाल D2_ENABLE_ENCRYPTION:
		status = enable_encryption(hdcp, event_ctx, input);
		अवरोध;
	हाल D2_A5_AUTHENTICATED:
		status = authenticated(hdcp, event_ctx, input);
		अवरोध;
	हाल D2_A6_WAIT_FOR_RX_ID_LIST:
		status = रुको_क्रम_rx_id_list(hdcp, event_ctx, input);
		अवरोध;
	हाल D2_A78_VERIFY_RX_ID_LIST_AND_SEND_ACK:
		status = verअगरy_rx_id_list_and_send_ack(hdcp, event_ctx, input);
		अवरोध;
	हाल D2_A9_SEND_STREAM_MANAGEMENT:
		status = send_stream_management(hdcp, event_ctx, input);
		अवरोध;
	हाल D2_A9_VALIDATE_STREAM_READY:
		status = validate_stream_पढ़ोy(hdcp, event_ctx, input);
		अवरोध;
	शेष:
		status = MOD_HDCP_STATUS_INVALID_STATE;
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण
