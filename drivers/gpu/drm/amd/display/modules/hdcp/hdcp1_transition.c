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

क्रमागत mod_hdcp_status mod_hdcp_hdcp1_transition(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp1 *input,
		काष्ठा mod_hdcp_output *output)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;
	काष्ठा mod_hdcp_connection *conn = &hdcp->connection;
	काष्ठा mod_hdcp_link_adjusपंचांगent *adjust = &hdcp->connection.link.adjust;

	चयन (current_state(hdcp)) अणु
	हाल H1_A0_WAIT_FOR_ACTIVE_RX:
		अगर (input->bksv_पढ़ो != PASS || input->bcaps_पढ़ो != PASS) अणु
			/* 1A-04: repeatedly attempts on port access failure */
			callback_in_ms(500, output);
			increment_stay_counter(hdcp);
			अवरोध;
		पूर्ण
		callback_in_ms(0, output);
		set_state_id(hdcp, output, H1_A1_EXCHANGE_KSVS);
		अवरोध;
	हाल H1_A1_EXCHANGE_KSVS:
		अगर (input->create_session != PASS) अणु
			/* out of sync with psp state */
			adjust->hdcp1.disable = 1;
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (input->an_ग_लिखो != PASS ||
				input->aksv_ग_लिखो != PASS ||
				input->bksv_पढ़ो != PASS ||
				input->bksv_validation != PASS ||
				input->ainfo_ग_लिखो == FAIL) अणु
			/* 1A-05: consider invalid bksv a failure */
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		callback_in_ms(300, output);
		set_state_id(hdcp, output,
			H1_A2_COMPUTATIONS_A3_VALIDATE_RX_A6_TEST_FOR_REPEATER);
		अवरोध;
	हाल H1_A2_COMPUTATIONS_A3_VALIDATE_RX_A6_TEST_FOR_REPEATER:
		अगर (input->bcaps_पढ़ो != PASS ||
				input->r0p_पढ़ो != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (input->rx_validation != PASS) अणु
			/* 1A-06: consider invalid r0' a failure */
			/* 1A-08: consider bksv listed in SRM a failure */
			/*
			 * some slow RX will fail rx validation when it is
			 * not पढ़ोy. give it more समय to react beक्रमe retry.
			 */
			fail_and_restart_in_ms(1000, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (!conn->is_repeater && input->encryption != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		अगर (conn->is_repeater) अणु
			callback_in_ms(0, output);
			set_watchकरोg_in_ms(hdcp, 5000, output);
			set_state_id(hdcp, output, H1_A8_WAIT_FOR_READY);
		पूर्ण अन्यथा अणु
			callback_in_ms(0, output);
			set_state_id(hdcp, output, H1_A45_AUTHENTICATED);
			HDCP_FULL_DDC_TRACE(hdcp);
		पूर्ण
		अवरोध;
	हाल H1_A45_AUTHENTICATED:
		अगर (input->link_मुख्यtenance == FAIL) अणु
			/* 1A-07: consider invalid ri' a failure */
			/* 1A-07a: consider पढ़ो ri' not वापसed a failure */
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		callback_in_ms(500, output);
		increment_stay_counter(hdcp);
		अवरोध;
	हाल H1_A8_WAIT_FOR_READY:
		अगर (input->पढ़ोy_check != PASS) अणु
			अगर (event_ctx->event ==
					MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) अणु
				/* 1B-03: fail hdcp on ksv list READY समयout */
				/* prevent black screen in next attempt */
				adjust->hdcp1.postpone_encryption = 1;
				fail_and_restart_in_ms(0, &status, output);
			पूर्ण अन्यथा अणु
				/* जारी ksv list READY polling*/
				callback_in_ms(500, output);
				increment_stay_counter(hdcp);
			पूर्ण
			अवरोध;
		पूर्ण
		callback_in_ms(0, output);
		set_state_id(hdcp, output, H1_A9_READ_KSV_LIST);
		अवरोध;
	हाल H1_A9_READ_KSV_LIST:
		अगर (input->bstatus_पढ़ो != PASS ||
				input->max_cascade_check != PASS ||
				input->max_devs_check != PASS ||
				input->device_count_check != PASS ||
				input->ksvlist_पढ़ो != PASS ||
				input->vp_पढ़ो != PASS ||
				input->ksvlist_vp_validation != PASS ||
				input->encryption != PASS) अणु
			/* 1B-06: consider MAX_CASCADE_EXCEEDED a failure */
			/* 1B-05: consider MAX_DEVS_EXCEEDED a failure */
			/* 1B-04: consider invalid v' a failure */
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		callback_in_ms(0, output);
		set_state_id(hdcp, output, H1_A45_AUTHENTICATED);
		HDCP_FULL_DDC_TRACE(hdcp);
		अवरोध;
	शेष:
		status = MOD_HDCP_STATUS_INVALID_STATE;
		fail_and_restart_in_ms(0, &status, output);
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp1_dp_transition(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		काष्ठा mod_hdcp_transition_input_hdcp1 *input,
		काष्ठा mod_hdcp_output *output)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;
	काष्ठा mod_hdcp_connection *conn = &hdcp->connection;
	काष्ठा mod_hdcp_link_adjusपंचांगent *adjust = &hdcp->connection.link.adjust;

	चयन (current_state(hdcp)) अणु
	हाल D1_A0_DETERMINE_RX_HDCP_CAPABLE:
		अगर (input->bcaps_पढ़ो != PASS) अणु
			/* 1A-04: no authentication on bcaps पढ़ो failure */
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (input->hdcp_capable_dp != PASS) अणु
			adjust->hdcp1.disable = 1;
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		callback_in_ms(0, output);
		set_state_id(hdcp, output, D1_A1_EXCHANGE_KSVS);
		अवरोध;
	हाल D1_A1_EXCHANGE_KSVS:
		अगर (input->create_session != PASS) अणु
			/* out of sync with psp state */
			adjust->hdcp1.disable = 1;
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (input->an_ग_लिखो != PASS ||
				input->aksv_ग_लिखो != PASS ||
				input->bksv_पढ़ो != PASS ||
				input->bksv_validation != PASS ||
				input->ainfo_ग_लिखो == FAIL) अणु
			/* 1A-05: consider invalid bksv a failure */
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		set_watchकरोg_in_ms(hdcp, 100, output);
		set_state_id(hdcp, output, D1_A23_WAIT_FOR_R0_PRIME);
		अवरोध;
	हाल D1_A23_WAIT_FOR_R0_PRIME:
		अगर (input->bstatus_पढ़ो != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (input->r0p_available_dp != PASS) अणु
			अगर (event_ctx->event == MOD_HDCP_EVENT_WATCHDOG_TIMEOUT)
				fail_and_restart_in_ms(0, &status, output);
			अन्यथा
				increment_stay_counter(hdcp);
			अवरोध;
		पूर्ण
		callback_in_ms(0, output);
		set_state_id(hdcp, output, D1_A2_COMPUTATIONS_A3_VALIDATE_RX_A5_TEST_FOR_REPEATER);
		अवरोध;
	हाल D1_A2_COMPUTATIONS_A3_VALIDATE_RX_A5_TEST_FOR_REPEATER:
		अगर (input->r0p_पढ़ो != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (input->rx_validation != PASS) अणु
			अगर (hdcp->state.stay_count < 2 &&
					!hdcp->connection.is_hdcp1_revoked) अणु
				/* allow 2 additional retries */
				callback_in_ms(0, output);
				increment_stay_counter(hdcp);
			पूर्ण अन्यथा अणु
				/*
				 * 1A-06: consider invalid r0' a failure
				 * after 3 attempts.
				 * 1A-08: consider bksv listed in SRM a failure
				 */
				/*
				 * some slow RX will fail rx validation when it is
				 * not पढ़ोy. give it more समय to react beक्रमe retry.
				 */
				fail_and_restart_in_ms(1000, &status, output);
			पूर्ण
			अवरोध;
		पूर्ण अन्यथा अगर ((!conn->is_repeater && input->encryption != PASS) ||
				(!conn->is_repeater && is_dp_mst_hdcp(hdcp) && input->stream_encryption_dp != PASS)) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (conn->hdcp1_retry_count < conn->link.adjust.hdcp1.min_auth_retries_wa) अणु
			fail_and_restart_in_ms(200, &status, output);
			अवरोध;
		पूर्ण
		अगर (conn->is_repeater) अणु
			set_watchकरोg_in_ms(hdcp, 5000, output);
			set_state_id(hdcp, output, D1_A6_WAIT_FOR_READY);
		पूर्ण अन्यथा अणु
			set_state_id(hdcp, output, D1_A4_AUTHENTICATED);
			HDCP_FULL_DDC_TRACE(hdcp);
		पूर्ण
		अवरोध;
	हाल D1_A4_AUTHENTICATED:
		अगर (input->link_पूर्णांकegrity_check == FAIL ||
				input->reauth_request_check == FAIL) अणु
			/* 1A-07: restart hdcp on a link पूर्णांकegrity failure */
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल D1_A6_WAIT_FOR_READY:
		अगर (input->link_पूर्णांकegrity_check == FAIL ||
				input->reauth_request_check == FAIL) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (input->पढ़ोy_check != PASS) अणु
			अगर (event_ctx->event ==
					MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) अणु
				/* 1B-04: fail hdcp on ksv list READY समयout */
				/* prevent black screen in next attempt */
				adjust->hdcp1.postpone_encryption = 1;
				fail_and_restart_in_ms(0, &status, output);
			पूर्ण अन्यथा अणु
				increment_stay_counter(hdcp);
			पूर्ण
			अवरोध;
		पूर्ण
		callback_in_ms(0, output);
		set_state_id(hdcp, output, D1_A7_READ_KSV_LIST);
		अवरोध;
	हाल D1_A7_READ_KSV_LIST:
		अगर (input->binfo_पढ़ो_dp != PASS ||
				input->max_cascade_check != PASS ||
				input->max_devs_check != PASS) अणु
			/* 1B-06: consider MAX_DEVS_EXCEEDED a failure */
			/* 1B-07: consider MAX_CASCADE_EXCEEDED a failure */
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (input->device_count_check != PASS) अणु
			/*
			 * some slow करोngle करोesn't update
			 * device count as soon as करोwnstream is connected.
			 * give it more समय to react.
			 */
			adjust->hdcp1.postpone_encryption = 1;
			fail_and_restart_in_ms(1000, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (input->ksvlist_पढ़ो != PASS ||
				input->vp_पढ़ो != PASS) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण अन्यथा अगर (input->ksvlist_vp_validation != PASS) अणु
			अगर (hdcp->state.stay_count < 2 &&
					!hdcp->connection.is_hdcp1_revoked) अणु
				/* allow 2 additional retries */
				callback_in_ms(0, output);
				increment_stay_counter(hdcp);
			पूर्ण अन्यथा अणु
				/*
				 * 1B-05: consider invalid v' a failure
				 * after 3 attempts.
				 */
				fail_and_restart_in_ms(0, &status, output);
			पूर्ण
			अवरोध;
		पूर्ण अन्यथा अगर (input->encryption != PASS ||
				(is_dp_mst_hdcp(hdcp) && input->stream_encryption_dp != PASS)) अणु
			fail_and_restart_in_ms(0, &status, output);
			अवरोध;
		पूर्ण
		set_state_id(hdcp, output, D1_A4_AUTHENTICATED);
		HDCP_FULL_DDC_TRACE(hdcp);
		अवरोध;
	शेष:
		fail_and_restart_in_ms(0, &status, output);
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण
