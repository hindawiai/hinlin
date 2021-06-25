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

#समावेश "hdcp.h"

अटल अंतरभूत क्रमागत mod_hdcp_status validate_bksv(काष्ठा mod_hdcp *hdcp)
अणु
	uपूर्णांक64_t n = 0;
	uपूर्णांक8_t count = 0;

	स_नकल(&n, hdcp->auth.msg.hdcp1.bksv, माप(uपूर्णांक64_t));

	जबतक (n) अणु
		count++;
		n &= (n - 1);
	पूर्ण
	वापस (count == 20) ? MOD_HDCP_STATUS_SUCCESS :
			MOD_HDCP_STATUS_HDCP1_INVALID_BKSV;
पूर्ण

अटल अंतरभूत क्रमागत mod_hdcp_status check_ksv_पढ़ोy(काष्ठा mod_hdcp *hdcp)
अणु
	अगर (is_dp_hdcp(hdcp))
		वापस (hdcp->auth.msg.hdcp1.bstatus & DP_BSTATUS_READY) ?
				MOD_HDCP_STATUS_SUCCESS :
				MOD_HDCP_STATUS_HDCP1_KSV_LIST_NOT_READY;
	वापस (hdcp->auth.msg.hdcp1.bcaps & DRM_HDCP_DDC_BCAPS_KSV_FIFO_READY) ?
			MOD_HDCP_STATUS_SUCCESS :
			MOD_HDCP_STATUS_HDCP1_KSV_LIST_NOT_READY;
पूर्ण

अटल अंतरभूत क्रमागत mod_hdcp_status check_hdcp_capable_dp(काष्ठा mod_hdcp *hdcp)
अणु
	वापस (hdcp->auth.msg.hdcp1.bcaps & DP_BCAPS_HDCP_CAPABLE) ?
			MOD_HDCP_STATUS_SUCCESS :
			MOD_HDCP_STATUS_HDCP1_NOT_CAPABLE;
पूर्ण

अटल अंतरभूत क्रमागत mod_hdcp_status check_r0p_available_dp(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;
	अगर (is_dp_hdcp(hdcp)) अणु
		status = (hdcp->auth.msg.hdcp1.bstatus &
				DP_BSTATUS_R0_PRIME_READY) ?
			MOD_HDCP_STATUS_SUCCESS :
			MOD_HDCP_STATUS_HDCP1_R0_PRIME_PENDING;
	पूर्ण अन्यथा अणु
		status = MOD_HDCP_STATUS_INVALID_OPERATION;
	पूर्ण
	वापस status;
पूर्ण

अटल अंतरभूत क्रमागत mod_hdcp_status check_link_पूर्णांकegrity_dp(
		काष्ठा mod_hdcp *hdcp)
अणु
	वापस (hdcp->auth.msg.hdcp1.bstatus &
			DP_BSTATUS_LINK_FAILURE) ?
			MOD_HDCP_STATUS_HDCP1_LINK_INTEGRITY_FAILURE :
			MOD_HDCP_STATUS_SUCCESS;
पूर्ण

अटल अंतरभूत क्रमागत mod_hdcp_status check_no_reauthentication_request_dp(
		काष्ठा mod_hdcp *hdcp)
अणु
	वापस (hdcp->auth.msg.hdcp1.bstatus & DP_BSTATUS_REAUTH_REQ) ?
			MOD_HDCP_STATUS_HDCP1_REAUTH_REQUEST_ISSUED :
			MOD_HDCP_STATUS_SUCCESS;
पूर्ण

अटल अंतरभूत क्रमागत mod_hdcp_status check_no_max_cascade(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp))
		status = DRM_HDCP_MAX_CASCADE_EXCEEDED(hdcp->auth.msg.hdcp1.binfo_dp >> 8)
				 ? MOD_HDCP_STATUS_HDCP1_MAX_CASCADE_EXCEEDED_FAILURE
				 : MOD_HDCP_STATUS_SUCCESS;
	अन्यथा
		status = DRM_HDCP_MAX_CASCADE_EXCEEDED(hdcp->auth.msg.hdcp1.bstatus >> 8)
				 ? MOD_HDCP_STATUS_HDCP1_MAX_CASCADE_EXCEEDED_FAILURE
				 : MOD_HDCP_STATUS_SUCCESS;
	वापस status;
पूर्ण

अटल अंतरभूत क्रमागत mod_hdcp_status check_no_max_devs(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp))
		status = DRM_HDCP_MAX_DEVICE_EXCEEDED(hdcp->auth.msg.hdcp1.binfo_dp) ?
				MOD_HDCP_STATUS_HDCP1_MAX_DEVS_EXCEEDED_FAILURE :
				MOD_HDCP_STATUS_SUCCESS;
	अन्यथा
		status = DRM_HDCP_MAX_DEVICE_EXCEEDED(hdcp->auth.msg.hdcp1.bstatus) ?
				MOD_HDCP_STATUS_HDCP1_MAX_DEVS_EXCEEDED_FAILURE :
				MOD_HDCP_STATUS_SUCCESS;
	वापस status;
पूर्ण

अटल अंतरभूत uपूर्णांक8_t get_device_count(काष्ठा mod_hdcp *hdcp)
अणु
	वापस is_dp_hdcp(hdcp) ?
			DRM_HDCP_NUM_DOWNSTREAM(hdcp->auth.msg.hdcp1.binfo_dp) :
			DRM_HDCP_NUM_DOWNSTREAM(hdcp->auth.msg.hdcp1.bstatus);
पूर्ण

अटल अंतरभूत क्रमागत mod_hdcp_status check_device_count(काष्ठा mod_hdcp *hdcp)
अणु
	/* Some MST display may choose to report the पूर्णांकernal panel as an HDCP RX.
	 * To update this condition with 1(because the immediate repeater's पूर्णांकernal
	 * panel is possibly not included in DEVICE_COUNT) + get_device_count(hdcp).
	 * Device count must be greater than or equal to tracked hdcp displays.
	 */
	वापस ((1 + get_device_count(hdcp)) < get_active_display_count(hdcp)) ?
			MOD_HDCP_STATUS_HDCP1_DEVICE_COUNT_MISMATCH_FAILURE :
			MOD_HDCP_STATUS_SUCCESS;
पूर्ण

अटल क्रमागत mod_hdcp_status रुको_क्रम_active_rx(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp1 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_bksv,
			&input->bksv_पढ़ो, &status,
			hdcp, "bksv_read"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_bcaps,
			&input->bcaps_पढ़ो, &status,
			hdcp, "bcaps_read"))
		जाओ out;
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status exchange_ksvs(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp1 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (!mod_hdcp_execute_and_set(mod_hdcp_hdcp1_create_session,
			&input->create_session, &status,
			hdcp, "create_session"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_ग_लिखो_an,
			&input->an_ग_लिखो, &status,
			hdcp, "an_write"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_ग_लिखो_aksv,
			&input->aksv_ग_लिखो, &status,
			hdcp, "aksv_write"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_bksv,
			&input->bksv_पढ़ो, &status,
			hdcp, "bksv_read"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(validate_bksv,
			&input->bksv_validation, &status,
			hdcp, "bksv_validation"))
		जाओ out;
	अगर (hdcp->auth.msg.hdcp1.ainfo) अणु
		अगर (!mod_hdcp_execute_and_set(mod_hdcp_ग_लिखो_ainfo,
				&input->ainfo_ग_लिखो, &status,
				hdcp, "ainfo_write"))
			जाओ out;
	पूर्ण
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status computations_validate_rx_test_क्रम_repeater(
		काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp1 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_r0p,
			&input->r0p_पढ़ो, &status,
			hdcp, "r0p_read"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_hdcp1_validate_rx,
			&input->rx_validation, &status,
			hdcp, "rx_validation"))
		जाओ out;
	अगर (hdcp->connection.is_repeater) अणु
		अगर (!hdcp->connection.link.adjust.hdcp1.postpone_encryption)
			अगर (!mod_hdcp_execute_and_set(
					mod_hdcp_hdcp1_enable_encryption,
					&input->encryption, &status,
					hdcp, "encryption"))
				जाओ out;
	पूर्ण अन्यथा अणु
		अगर (!mod_hdcp_execute_and_set(mod_hdcp_hdcp1_enable_encryption,
				&input->encryption, &status,
				hdcp, "encryption"))
			जाओ out;
		अगर (is_dp_mst_hdcp(hdcp))
			अगर (!mod_hdcp_execute_and_set(
					mod_hdcp_hdcp1_enable_dp_stream_encryption,
					&input->stream_encryption_dp, &status,
					hdcp, "stream_encryption_dp"))
				जाओ out;
	पूर्ण
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status authenticated(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp1 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	mod_hdcp_execute_and_set(mod_hdcp_hdcp1_link_मुख्यtenance,
			&input->link_मुख्यtenance, &status,
			hdcp, "link_maintenance");

	अगर (status != MOD_HDCP_STATUS_SUCCESS)
		mod_hdcp_save_current_encryption_states(hdcp);
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status रुको_क्रम_पढ़ोy(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp1 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIRQ &&
			event_ctx->event != MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (is_dp_hdcp(hdcp)) अणु
		अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_bstatus,
				&input->bstatus_पढ़ो, &status,
				hdcp, "bstatus_read"))
			जाओ out;
		अगर (!mod_hdcp_execute_and_set(check_link_पूर्णांकegrity_dp,
				&input->link_पूर्णांकegrity_check, &status,
				hdcp, "link_integrity_check"))
			जाओ out;
		अगर (!mod_hdcp_execute_and_set(check_no_reauthentication_request_dp,
				&input->reauth_request_check, &status,
				hdcp, "reauth_request_check"))
			जाओ out;
	पूर्ण अन्यथा अणु
		अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_bcaps,
				&input->bcaps_पढ़ो, &status,
				hdcp, "bcaps_read"))
			जाओ out;
	पूर्ण
	अगर (!mod_hdcp_execute_and_set(check_ksv_पढ़ोy,
			&input->पढ़ोy_check, &status,
			hdcp, "ready_check"))
		जाओ out;
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status पढ़ो_ksv_list(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp1 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;
	uपूर्णांक8_t device_count;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (is_dp_hdcp(hdcp)) अणु
		अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_binfo,
				&input->binfo_पढ़ो_dp, &status,
				hdcp, "binfo_read_dp"))
			जाओ out;
	पूर्ण अन्यथा अणु
		अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_bstatus,
				&input->bstatus_पढ़ो, &status,
				hdcp, "bstatus_read"))
			जाओ out;
	पूर्ण
	अगर (!mod_hdcp_execute_and_set(check_no_max_cascade,
			&input->max_cascade_check, &status,
			hdcp, "max_cascade_check"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(check_no_max_devs,
			&input->max_devs_check, &status,
			hdcp, "max_devs_check"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(check_device_count,
			&input->device_count_check, &status,
			hdcp, "device_count_check"))
		जाओ out;
	device_count = get_device_count(hdcp);
	hdcp->auth.msg.hdcp1.ksvlist_size = device_count*5;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_ksvlist,
			&input->ksvlist_पढ़ो, &status,
			hdcp, "ksvlist_read"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_vp,
			&input->vp_पढ़ो, &status,
			hdcp, "vp_read"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(mod_hdcp_hdcp1_validate_ksvlist_vp,
			&input->ksvlist_vp_validation, &status,
			hdcp, "ksvlist_vp_validation"))
		जाओ out;
	अगर (input->encryption != PASS)
		अगर (!mod_hdcp_execute_and_set(mod_hdcp_hdcp1_enable_encryption,
				&input->encryption, &status,
				hdcp, "encryption"))
			जाओ out;
	अगर (is_dp_mst_hdcp(hdcp))
		अगर (!mod_hdcp_execute_and_set(
				mod_hdcp_hdcp1_enable_dp_stream_encryption,
				&input->stream_encryption_dp, &status,
				hdcp, "stream_encryption_dp"))
			जाओ out;
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status determine_rx_hdcp_capable_dp(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp1 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_bcaps,
			&input->bcaps_पढ़ो, &status,
			hdcp, "bcaps_read"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(check_hdcp_capable_dp,
			&input->hdcp_capable_dp, &status,
			hdcp, "hdcp_capable_dp"))
		जाओ out;
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status रुको_क्रम_r0_prime_dp(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp1 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CPIRQ &&
			event_ctx->event != MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (!mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_bstatus,
			&input->bstatus_पढ़ो, &status,
			hdcp, "bstatus_read"))
		जाओ out;
	अगर (!mod_hdcp_execute_and_set(check_r0p_available_dp,
			&input->r0p_available_dp, &status,
			hdcp, "r0p_available_dp"))
		जाओ out;
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status authenticated_dp(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp1 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->event != MOD_HDCP_EVENT_CPIRQ) अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण

	अगर (status == MOD_HDCP_STATUS_SUCCESS)
		mod_hdcp_execute_and_set(mod_hdcp_पढ़ो_bstatus,
				&input->bstatus_पढ़ो, &status,
				hdcp, "bstatus_read");
	अगर (status == MOD_HDCP_STATUS_SUCCESS)
		mod_hdcp_execute_and_set(check_link_पूर्णांकegrity_dp,
				&input->link_पूर्णांकegrity_check, &status,
				hdcp, "link_integrity_check");
	अगर (status == MOD_HDCP_STATUS_SUCCESS)
		mod_hdcp_execute_and_set(check_no_reauthentication_request_dp,
				&input->reauth_request_check, &status,
				hdcp, "reauth_request_check");

	अगर (status != MOD_HDCP_STATUS_SUCCESS)
		mod_hdcp_save_current_encryption_states(hdcp);
out:
	वापस status;
पूर्ण

uपूर्णांक8_t mod_hdcp_execute_and_set(
		mod_hdcp_action func, uपूर्णांक8_t *flag,
		क्रमागत mod_hdcp_status *status, काष्ठा mod_hdcp *hdcp, अक्षर *str)
अणु
	*status = func(hdcp);
	अगर (*status == MOD_HDCP_STATUS_SUCCESS && *flag != PASS) अणु
		HDCP_INPUT_PASS_TRACE(hdcp, str);
		*flag = PASS;
	पूर्ण अन्यथा अगर (*status != MOD_HDCP_STATUS_SUCCESS && *flag != FAIL) अणु
		HDCP_INPUT_FAIL_TRACE(hdcp, str);
		*flag = FAIL;
	पूर्ण
	वापस (*status == MOD_HDCP_STATUS_SUCCESS);
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp1_execution(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp1 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	चयन (current_state(hdcp)) अणु
	हाल H1_A0_WAIT_FOR_ACTIVE_RX:
		status = रुको_क्रम_active_rx(hdcp, event_ctx, input);
		अवरोध;
	हाल H1_A1_EXCHANGE_KSVS:
		status = exchange_ksvs(hdcp, event_ctx, input);
		अवरोध;
	हाल H1_A2_COMPUTATIONS_A3_VALIDATE_RX_A6_TEST_FOR_REPEATER:
		status = computations_validate_rx_test_क्रम_repeater(hdcp,
				event_ctx, input);
		अवरोध;
	हाल H1_A45_AUTHENTICATED:
		status = authenticated(hdcp, event_ctx, input);
		अवरोध;
	हाल H1_A8_WAIT_FOR_READY:
		status = रुको_क्रम_पढ़ोy(hdcp, event_ctx, input);
		अवरोध;
	हाल H1_A9_READ_KSV_LIST:
		status = पढ़ो_ksv_list(hdcp, event_ctx, input);
		अवरोध;
	शेष:
		status = MOD_HDCP_STATUS_INVALID_STATE;
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

बाह्य क्रमागत mod_hdcp_status mod_hdcp_hdcp1_dp_execution(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp1 *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	चयन (current_state(hdcp)) अणु
	हाल D1_A0_DETERMINE_RX_HDCP_CAPABLE:
		status = determine_rx_hdcp_capable_dp(hdcp, event_ctx, input);
		अवरोध;
	हाल D1_A1_EXCHANGE_KSVS:
		status = exchange_ksvs(hdcp, event_ctx, input);
		अवरोध;
	हाल D1_A23_WAIT_FOR_R0_PRIME:
		status = रुको_क्रम_r0_prime_dp(hdcp, event_ctx, input);
		अवरोध;
	हाल D1_A2_COMPUTATIONS_A3_VALIDATE_RX_A5_TEST_FOR_REPEATER:
		status = computations_validate_rx_test_क्रम_repeater(
				hdcp, event_ctx, input);
		अवरोध;
	हाल D1_A4_AUTHENTICATED:
		status = authenticated_dp(hdcp, event_ctx, input);
		अवरोध;
	हाल D1_A6_WAIT_FOR_READY:
		status = रुको_क्रम_पढ़ोy(hdcp, event_ctx, input);
		अवरोध;
	हाल D1_A7_READ_KSV_LIST:
		status = पढ़ो_ksv_list(hdcp, event_ctx, input);
		अवरोध;
	शेष:
		status = MOD_HDCP_STATUS_INVALID_STATE;
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण
