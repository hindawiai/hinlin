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

अटल व्योम push_error_status(काष्ठा mod_hdcp *hdcp,
		क्रमागत mod_hdcp_status status)
अणु
	काष्ठा mod_hdcp_trace *trace = &hdcp->connection.trace;

	अगर (trace->error_count < MAX_NUM_OF_ERROR_TRACE) अणु
		trace->errors[trace->error_count].status = status;
		trace->errors[trace->error_count].state_id = hdcp->state.id;
		trace->error_count++;
		HDCP_ERROR_TRACE(hdcp, status);
	पूर्ण

	अगर (is_hdcp1(hdcp)) अणु
		hdcp->connection.hdcp1_retry_count++;
	पूर्ण अन्यथा अगर (is_hdcp2(hdcp)) अणु
		hdcp->connection.hdcp2_retry_count++;
	पूर्ण
पूर्ण

अटल uपूर्णांक8_t is_cp_desired_hdcp1(काष्ठा mod_hdcp *hdcp)
अणु
	पूर्णांक i, is_auth_needed = 0;

	/* अगर all displays on the link करोn't need authentication,
	 * hdcp is not desired
	 */
	क्रम (i = 0; i < MAX_NUM_OF_DISPLAYS; i++) अणु
		अगर (hdcp->displays[i].state != MOD_HDCP_DISPLAY_INACTIVE &&
				hdcp->displays[i].adjust.disable != MOD_HDCP_DISPLAY_DISABLE_AUTHENTICATION) अणु
			is_auth_needed = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस (hdcp->connection.hdcp1_retry_count < MAX_NUM_OF_ATTEMPTS) &&
			is_auth_needed &&
			!hdcp->connection.link.adjust.hdcp1.disable &&
			!hdcp->connection.is_hdcp1_revoked;
पूर्ण

अटल uपूर्णांक8_t is_cp_desired_hdcp2(काष्ठा mod_hdcp *hdcp)
अणु
	पूर्णांक i, is_auth_needed = 0;

	/* अगर all displays on the link करोn't need authentication,
	 * hdcp is not desired
	 */
	क्रम (i = 0; i < MAX_NUM_OF_DISPLAYS; i++) अणु
		अगर (hdcp->displays[i].state != MOD_HDCP_DISPLAY_INACTIVE &&
				hdcp->displays[i].adjust.disable != MOD_HDCP_DISPLAY_DISABLE_AUTHENTICATION) अणु
			is_auth_needed = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस (hdcp->connection.hdcp2_retry_count < MAX_NUM_OF_ATTEMPTS) &&
			is_auth_needed &&
			!hdcp->connection.link.adjust.hdcp2.disable &&
			!hdcp->connection.is_hdcp2_revoked;
पूर्ण

अटल क्रमागत mod_hdcp_status execution(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		जोड़ mod_hdcp_transition_input *input)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (is_in_initialized_state(hdcp)) अणु
		अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK) अणु
			event_ctx->unexpected_event = 1;
			जाओ out;
		पूर्ण
		/* initialize transition input */
		स_रखो(input, 0, माप(जोड़ mod_hdcp_transition_input));
	पूर्ण अन्यथा अगर (is_in_cp_not_desired_state(hdcp)) अणु
		अगर (event_ctx->event != MOD_HDCP_EVENT_CALLBACK) अणु
			event_ctx->unexpected_event = 1;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (is_in_hdcp1_states(hdcp)) अणु
		status = mod_hdcp_hdcp1_execution(hdcp, event_ctx, &input->hdcp1);
	पूर्ण अन्यथा अगर (is_in_hdcp1_dp_states(hdcp)) अणु
		status = mod_hdcp_hdcp1_dp_execution(hdcp,
				event_ctx, &input->hdcp1);
	पूर्ण अन्यथा अगर (is_in_hdcp2_states(hdcp)) अणु
		status = mod_hdcp_hdcp2_execution(hdcp, event_ctx, &input->hdcp2);
	पूर्ण अन्यथा अगर (is_in_hdcp2_dp_states(hdcp)) अणु
		status = mod_hdcp_hdcp2_dp_execution(hdcp,
				event_ctx, &input->hdcp2);
	पूर्ण अन्यथा अणु
		event_ctx->unexpected_event = 1;
		जाओ out;
	पूर्ण
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status transition(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_event_context *event_ctx,
		जोड़ mod_hdcp_transition_input *input,
		काष्ठा mod_hdcp_output *output)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (event_ctx->unexpected_event)
		जाओ out;

	अगर (is_in_initialized_state(hdcp)) अणु
		अगर (is_dp_hdcp(hdcp))
			अगर (is_cp_desired_hdcp2(hdcp)) अणु
				callback_in_ms(0, output);
				set_state_id(hdcp, output, D2_A0_DETERMINE_RX_HDCP_CAPABLE);
			पूर्ण अन्यथा अगर (is_cp_desired_hdcp1(hdcp)) अणु
				callback_in_ms(0, output);
				set_state_id(hdcp, output, D1_A0_DETERMINE_RX_HDCP_CAPABLE);
			पूर्ण अन्यथा अणु
				callback_in_ms(0, output);
				set_state_id(hdcp, output, HDCP_CP_NOT_DESIRED);
			पूर्ण
		अन्यथा अगर (is_hdmi_dvi_sl_hdcp(hdcp))
			अगर (is_cp_desired_hdcp2(hdcp)) अणु
				callback_in_ms(0, output);
				set_state_id(hdcp, output, H2_A0_KNOWN_HDCP2_CAPABLE_RX);
			पूर्ण अन्यथा अगर (is_cp_desired_hdcp1(hdcp)) अणु
				callback_in_ms(0, output);
				set_state_id(hdcp, output, H1_A0_WAIT_FOR_ACTIVE_RX);
			पूर्ण अन्यथा अणु
				callback_in_ms(0, output);
				set_state_id(hdcp, output, HDCP_CP_NOT_DESIRED);
			पूर्ण
		अन्यथा अणु
			callback_in_ms(0, output);
			set_state_id(hdcp, output, HDCP_CP_NOT_DESIRED);
		पूर्ण
	पूर्ण अन्यथा अगर (is_in_cp_not_desired_state(hdcp)) अणु
		increment_stay_counter(hdcp);
	पूर्ण अन्यथा अगर (is_in_hdcp1_states(hdcp)) अणु
		status = mod_hdcp_hdcp1_transition(hdcp,
				event_ctx, &input->hdcp1, output);
	पूर्ण अन्यथा अगर (is_in_hdcp1_dp_states(hdcp)) अणु
		status = mod_hdcp_hdcp1_dp_transition(hdcp,
				event_ctx, &input->hdcp1, output);
	पूर्ण अन्यथा अगर (is_in_hdcp2_states(hdcp)) अणु
		status = mod_hdcp_hdcp2_transition(hdcp,
				event_ctx, &input->hdcp2, output);
	पूर्ण अन्यथा अगर (is_in_hdcp2_dp_states(hdcp)) अणु
		status = mod_hdcp_hdcp2_dp_transition(hdcp,
				event_ctx, &input->hdcp2, output);
	पूर्ण अन्यथा अणु
		status = MOD_HDCP_STATUS_INVALID_STATE;
	पूर्ण
out:
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status reset_authentication(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_output *output)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (is_hdcp1(hdcp)) अणु
		अगर (hdcp->auth.trans_input.hdcp1.create_session != UNKNOWN) अणु
			/* TODO - update psp to unअगरy create session failure
			 * recovery between hdcp1 and 2.
			 */
			mod_hdcp_hdcp1_destroy_session(hdcp);

		पूर्ण

		HDCP_TOP_RESET_AUTH_TRACE(hdcp);
		स_रखो(&hdcp->auth, 0, माप(काष्ठा mod_hdcp_authentication));
		स_रखो(&hdcp->state, 0, माप(काष्ठा mod_hdcp_state));
		set_state_id(hdcp, output, HDCP_INITIALIZED);
	पूर्ण अन्यथा अगर (is_hdcp2(hdcp)) अणु
		अगर (hdcp->auth.trans_input.hdcp2.create_session == PASS) अणु
			status = mod_hdcp_hdcp2_destroy_session(hdcp);
			अगर (status != MOD_HDCP_STATUS_SUCCESS) अणु
				output->callback_needed = 0;
				output->watchकरोg_समयr_needed = 0;
				जाओ out;
			पूर्ण
		पूर्ण

		HDCP_TOP_RESET_AUTH_TRACE(hdcp);
		स_रखो(&hdcp->auth, 0, माप(काष्ठा mod_hdcp_authentication));
		स_रखो(&hdcp->state, 0, माप(काष्ठा mod_hdcp_state));
		set_state_id(hdcp, output, HDCP_INITIALIZED);
	पूर्ण अन्यथा अगर (is_in_cp_not_desired_state(hdcp)) अणु
		HDCP_TOP_RESET_AUTH_TRACE(hdcp);
		स_रखो(&hdcp->auth, 0, माप(काष्ठा mod_hdcp_authentication));
		स_रखो(&hdcp->state, 0, माप(काष्ठा mod_hdcp_state));
		set_state_id(hdcp, output, HDCP_INITIALIZED);
	पूर्ण

out:
	/* stop callback and watchकरोg requests from previous authentication*/
	output->watchकरोg_समयr_stop = 1;
	output->callback_stop = 1;
	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status reset_connection(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_output *output)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	स_रखो(output, 0, माप(काष्ठा mod_hdcp_output));

	status = reset_authentication(hdcp, output);
	अगर (status != MOD_HDCP_STATUS_SUCCESS)
		जाओ out;

	अगर (current_state(hdcp) != HDCP_UNINITIALIZED) अणु
		HDCP_TOP_RESET_CONN_TRACE(hdcp);
		set_state_id(hdcp, output, HDCP_UNINITIALIZED);
	पूर्ण
	स_रखो(&hdcp->connection, 0, माप(hdcp->connection));
out:
	वापस status;
पूर्ण

/*
 * Implementation of functions in mod_hdcp.h
 */
माप_प्रकार mod_hdcp_get_memory_size(व्योम)
अणु
	वापस माप(काष्ठा mod_hdcp);
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_setup(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_config *config)
अणु
	काष्ठा mod_hdcp_output output;
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	स_रखो(hdcp, 0, माप(काष्ठा mod_hdcp));
	स_रखो(&output, 0, माप(output));
	hdcp->config = *config;
	HDCP_TOP_INTERFACE_TRACE(hdcp);
	status = reset_connection(hdcp, &output);
	अगर (status != MOD_HDCP_STATUS_SUCCESS)
		push_error_status(hdcp, status);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_tearकरोwn(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;
	काष्ठा mod_hdcp_output output;

	HDCP_TOP_INTERFACE_TRACE(hdcp);
	स_रखो(&output, 0,  माप(output));
	status = reset_connection(hdcp, &output);
	अगर (status == MOD_HDCP_STATUS_SUCCESS)
		स_रखो(hdcp, 0, माप(काष्ठा mod_hdcp));
	अन्यथा
		push_error_status(hdcp, status);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_add_display(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_link *link, काष्ठा mod_hdcp_display *display,
		काष्ठा mod_hdcp_output *output)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;
	काष्ठा mod_hdcp_display *display_container = शून्य;

	HDCP_TOP_INTERFACE_TRACE_WITH_INDEX(hdcp, display->index);
	स_रखो(output, 0, माप(काष्ठा mod_hdcp_output));

	/* skip inactive display */
	अगर (display->state != MOD_HDCP_DISPLAY_ACTIVE) अणु
		status = MOD_HDCP_STATUS_SUCCESS;
		जाओ out;
	पूर्ण

	/* check existing display container */
	अगर (get_active_display_at_index(hdcp, display->index)) अणु
		status = MOD_HDCP_STATUS_SUCCESS;
		जाओ out;
	पूर्ण

	/* find an empty display container */
	display_container = get_empty_display_container(hdcp);
	अगर (!display_container) अणु
		status = MOD_HDCP_STATUS_DISPLAY_OUT_OF_BOUND;
		जाओ out;
	पूर्ण

	/* save current encryption states to restore after next authentication */
	mod_hdcp_save_current_encryption_states(hdcp);

	/* reset existing authentication status */
	status = reset_authentication(hdcp, output);
	अगर (status != MOD_HDCP_STATUS_SUCCESS)
		जाओ out;

	/* reset retry counters */
	reset_retry_counts(hdcp);

	/* reset error trace */
	स_रखो(&hdcp->connection.trace, 0, माप(hdcp->connection.trace));

	/* add display to connection */
	hdcp->connection.link = *link;
	*display_container = *display;
	status = mod_hdcp_add_display_to_topology(hdcp, display_container);

	अगर (status != MOD_HDCP_STATUS_SUCCESS)
		जाओ out;

	/* request authentication */
	अगर (current_state(hdcp) != HDCP_INITIALIZED)
		set_state_id(hdcp, output, HDCP_INITIALIZED);
	callback_in_ms(hdcp->connection.link.adjust.auth_delay * 1000, output);
out:
	अगर (status != MOD_HDCP_STATUS_SUCCESS)
		push_error_status(hdcp, status);

	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_हटाओ_display(काष्ठा mod_hdcp *hdcp,
		uपूर्णांक8_t index, काष्ठा mod_hdcp_output *output)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;
	काष्ठा mod_hdcp_display *display = शून्य;

	HDCP_TOP_INTERFACE_TRACE_WITH_INDEX(hdcp, index);
	स_रखो(output, 0, माप(काष्ठा mod_hdcp_output));

	/* find display in connection */
	display = get_active_display_at_index(hdcp, index);
	अगर (!display) अणु
		status = MOD_HDCP_STATUS_SUCCESS;
		जाओ out;
	पूर्ण

	/* save current encryption states to restore after next authentication */
	mod_hdcp_save_current_encryption_states(hdcp);

	/* stop current authentication */
	status = reset_authentication(hdcp, output);
	अगर (status != MOD_HDCP_STATUS_SUCCESS)
		जाओ out;

	/* clear retry counters */
	reset_retry_counts(hdcp);

	/* reset error trace */
	स_रखो(&hdcp->connection.trace, 0, माप(hdcp->connection.trace));

	/* हटाओ display */
	status = mod_hdcp_हटाओ_display_from_topology(hdcp, index);
	अगर (status != MOD_HDCP_STATUS_SUCCESS)
		जाओ out;
	स_रखो(display, 0, माप(काष्ठा mod_hdcp_display));

	/* request authentication when connection is not reset */
	अगर (current_state(hdcp) != HDCP_UNINITIALIZED)
		callback_in_ms(hdcp->connection.link.adjust.auth_delay * 1000,
				output);
out:
	अगर (status != MOD_HDCP_STATUS_SUCCESS)
		push_error_status(hdcp, status);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_query_display(काष्ठा mod_hdcp *hdcp,
		uपूर्णांक8_t index, काष्ठा mod_hdcp_display_query *query)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;
	काष्ठा mod_hdcp_display *display = शून्य;

	/* find display in connection */
	display = get_active_display_at_index(hdcp, index);
	अगर (!display) अणु
		status = MOD_HDCP_STATUS_DISPLAY_NOT_FOUND;
		जाओ out;
	पूर्ण

	/* populate query */
	query->link = &hdcp->connection.link;
	query->display = display;
	query->trace = &hdcp->connection.trace;
	query->encryption_status = MOD_HDCP_ENCRYPTION_STATUS_HDCP_OFF;

	अगर (is_display_encryption_enabled(display)) अणु
		अगर (is_hdcp1(hdcp)) अणु
			query->encryption_status = MOD_HDCP_ENCRYPTION_STATUS_HDCP1_ON;
		पूर्ण अन्यथा अगर (is_hdcp2(hdcp)) अणु
			अगर (query->link->adjust.hdcp2.क्रमce_type == MOD_HDCP_FORCE_TYPE_0)
				query->encryption_status = MOD_HDCP_ENCRYPTION_STATUS_HDCP2_TYPE0_ON;
			अन्यथा अगर (query->link->adjust.hdcp2.क्रमce_type == MOD_HDCP_FORCE_TYPE_1)
				query->encryption_status = MOD_HDCP_ENCRYPTION_STATUS_HDCP2_TYPE1_ON;
			अन्यथा
				query->encryption_status = MOD_HDCP_ENCRYPTION_STATUS_HDCP2_ON;
		पूर्ण
	पूर्ण अन्यथा अणु
		query->encryption_status = MOD_HDCP_ENCRYPTION_STATUS_HDCP_OFF;
	पूर्ण

out:
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_reset_connection(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_output *output)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	HDCP_TOP_INTERFACE_TRACE(hdcp);
	status = reset_connection(hdcp, output);
	अगर (status != MOD_HDCP_STATUS_SUCCESS)
		push_error_status(hdcp, status);

	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_process_event(काष्ठा mod_hdcp *hdcp,
		क्रमागत mod_hdcp_event event, काष्ठा mod_hdcp_output *output)
अणु
	क्रमागत mod_hdcp_status exec_status, trans_status, reset_status, status;
	काष्ठा mod_hdcp_event_context event_ctx;

	HDCP_EVENT_TRACE(hdcp, event);
	स_रखो(output, 0, माप(काष्ठा mod_hdcp_output));
	स_रखो(&event_ctx, 0, माप(काष्ठा mod_hdcp_event_context));
	event_ctx.event = event;

	/* execute and transition */
	exec_status = execution(hdcp, &event_ctx, &hdcp->auth.trans_input);
	trans_status = transition(
			hdcp, &event_ctx, &hdcp->auth.trans_input, output);
	अगर (trans_status == MOD_HDCP_STATUS_SUCCESS) अणु
		status = MOD_HDCP_STATUS_SUCCESS;
	पूर्ण अन्यथा अगर (exec_status == MOD_HDCP_STATUS_SUCCESS) अणु
		status = MOD_HDCP_STATUS_INTERNAL_POLICY_FAILURE;
		push_error_status(hdcp, status);
	पूर्ण अन्यथा अणु
		status = exec_status;
		push_error_status(hdcp, status);
	पूर्ण

	/* reset authentication अगर needed */
	अगर (trans_status == MOD_HDCP_STATUS_RESET_NEEDED) अणु
		HDCP_FULL_DDC_TRACE(hdcp);
		reset_status = reset_authentication(hdcp, output);
		अगर (reset_status != MOD_HDCP_STATUS_SUCCESS)
			push_error_status(hdcp, reset_status);
	पूर्ण

	/* Clear CP_IRQ status अगर needed */
	अगर (event_ctx.event == MOD_HDCP_EVENT_CPIRQ) अणु
		status = mod_hdcp_clear_cp_irq_status(hdcp);
		अगर (status != MOD_HDCP_STATUS_SUCCESS)
			push_error_status(hdcp, status);
	पूर्ण

	वापस status;
पूर्ण

क्रमागत mod_hdcp_operation_mode mod_hdcp_संकेत_type_to_operation_mode(
		क्रमागत संकेत_type संकेत)
अणु
	क्रमागत mod_hdcp_operation_mode mode = MOD_HDCP_MODE_OFF;

	चयन (संकेत) अणु
	हाल SIGNAL_TYPE_DVI_SINGLE_LINK:
	हाल SIGNAL_TYPE_HDMI_TYPE_A:
		mode = MOD_HDCP_MODE_DEFAULT;
		अवरोध;
	हाल SIGNAL_TYPE_EDP:
	हाल SIGNAL_TYPE_DISPLAY_PORT:
	हाल SIGNAL_TYPE_DISPLAY_PORT_MST:
		mode = MOD_HDCP_MODE_DP;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस mode;
पूर्ण
