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

#घोषणा MAX_NUM_DISPLAYS 24


#समावेश "hdcp.h"

#समावेश "amdgpu.h"
#समावेश "hdcp_psp.h"

अटल व्योम hdcp2_message_init(काष्ठा mod_hdcp *hdcp,
			       काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_input_v2 *in)
अणु
	in->session_handle = hdcp->auth.id;
	in->prepare.msg1_id = TA_HDCP_HDCP2_MSG_ID__शून्य_MESSAGE;
	in->prepare.msg2_id = TA_HDCP_HDCP2_MSG_ID__शून्य_MESSAGE;
	in->process.msg1_desc.msg_id = TA_HDCP_HDCP2_MSG_ID__शून्य_MESSAGE;
	in->process.msg1_desc.msg_size = 0;
	in->process.msg2_desc.msg_id = TA_HDCP_HDCP2_MSG_ID__शून्य_MESSAGE;
	in->process.msg2_desc.msg_size = 0;
	in->process.msg3_desc.msg_id = TA_HDCP_HDCP2_MSG_ID__शून्य_MESSAGE;
	in->process.msg3_desc.msg_size = 0;
पूर्ण
क्रमागत mod_hdcp_status mod_hdcp_हटाओ_display_from_topology(
		काष्ठा mod_hdcp *hdcp, uपूर्णांक8_t index)
 अणु
 	काष्ठा psp_context *psp = hdcp->config.psp.handle;
 	काष्ठा ta_dपंचांग_shared_memory *dपंचांग_cmd;
	काष्ठा mod_hdcp_display *display =
			get_active_display_at_index(hdcp, index);
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	dपंचांग_cmd = (काष्ठा ta_dपंचांग_shared_memory *)psp->dपंचांग_context.dपंचांग_shared_buf;

	अगर (!display || !is_display_active(display))
		वापस MOD_HDCP_STATUS_DISPLAY_NOT_FOUND;

	mutex_lock(&psp->dपंचांग_context.mutex);

	स_रखो(dपंचांग_cmd, 0, माप(काष्ठा ta_dपंचांग_shared_memory));

	dपंचांग_cmd->cmd_id = TA_DTM_COMMAND__TOPOLOGY_UPDATE_V2;
	dपंचांग_cmd->dपंचांग_in_message.topology_update_v2.display_handle = display->index;
	dपंचांग_cmd->dपंचांग_in_message.topology_update_v2.is_active = 0;
	dपंचांग_cmd->dपंचांग_status = TA_DTM_STATUS__GENERIC_FAILURE;

	psp_dपंचांग_invoke(psp, dपंचांग_cmd->cmd_id);

	अगर (dपंचांग_cmd->dपंचांग_status != TA_DTM_STATUS__SUCCESS) अणु
		status = MOD_HDCP_STATUS_UPDATE_TOPOLOGY_FAILURE;
	पूर्ण अन्यथा अणु
		display->state = MOD_HDCP_DISPLAY_ACTIVE;
		HDCP_TOP_REMOVE_DISPLAY_TRACE(hdcp, display->index);
	पूर्ण

	mutex_unlock(&psp->dपंचांग_context.mutex);
	वापस status;
पूर्ण
क्रमागत mod_hdcp_status mod_hdcp_add_display_to_topology(काष्ठा mod_hdcp *hdcp,
					       काष्ठा mod_hdcp_display *display)
अणु
	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा ta_dपंचांग_shared_memory *dपंचांग_cmd;
	काष्ठा mod_hdcp_link *link = &hdcp->connection.link;
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (!psp->dपंचांग_context.dपंचांग_initialized) अणु
		DRM_INFO("Failed to add display topology, DTM TA is not initialized.");
		display->state = MOD_HDCP_DISPLAY_INACTIVE;
		वापस MOD_HDCP_STATUS_FAILURE;
	पूर्ण

	dपंचांग_cmd = (काष्ठा ta_dपंचांग_shared_memory *)psp->dपंचांग_context.dपंचांग_shared_buf;

	mutex_lock(&psp->dपंचांग_context.mutex);
	स_रखो(dपंचांग_cmd, 0, माप(काष्ठा ta_dपंचांग_shared_memory));

	dपंचांग_cmd->cmd_id = TA_DTM_COMMAND__TOPOLOGY_UPDATE_V2;
	dपंचांग_cmd->dपंचांग_in_message.topology_update_v2.display_handle = display->index;
	dपंचांग_cmd->dपंचांग_in_message.topology_update_v2.is_active = 1;
	dपंचांग_cmd->dपंचांग_in_message.topology_update_v2.controller = display->controller;
	dपंचांग_cmd->dपंचांग_in_message.topology_update_v2.ddc_line = link->ddc_line;
	dपंचांग_cmd->dपंचांग_in_message.topology_update_v2.dig_be = link->dig_be;
	dपंचांग_cmd->dपंचांग_in_message.topology_update_v2.dig_fe = display->dig_fe;
	अगर (is_dp_hdcp(hdcp))
		dपंचांग_cmd->dपंचांग_in_message.topology_update_v2.is_assr = link->dp.assr_enabled;

	dपंचांग_cmd->dपंचांग_in_message.topology_update_v2.dp_mst_vcid = display->vc_id;
	dपंचांग_cmd->dपंचांग_in_message.topology_update_v2.max_hdcp_supported_version =
			TA_DTM_HDCP_VERSION_MAX_SUPPORTED__2_2;
	dपंचांग_cmd->dपंचांग_status = TA_DTM_STATUS__GENERIC_FAILURE;

	psp_dपंचांग_invoke(psp, dपंचांग_cmd->cmd_id);

	अगर (dपंचांग_cmd->dपंचांग_status != TA_DTM_STATUS__SUCCESS) अणु
		display->state = MOD_HDCP_DISPLAY_INACTIVE;
		status = MOD_HDCP_STATUS_UPDATE_TOPOLOGY_FAILURE;
	पूर्ण अन्यथा अणु
		HDCP_TOP_ADD_DISPLAY_TRACE(hdcp, display->index);
	पूर्ण

	mutex_unlock(&psp->dपंचांग_context.mutex);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp1_create_session(काष्ठा mod_hdcp *hdcp)
अणु

	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा mod_hdcp_display *display = get_first_active_display(hdcp);
	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (!psp->hdcp_context.hdcp_initialized) अणु
		DRM_ERROR("Failed to create hdcp session. HDCP TA is not initialized.");
		वापस MOD_HDCP_STATUS_FAILURE;
	पूर्ण

	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;

	mutex_lock(&psp->hdcp_context.mutex);
	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	hdcp_cmd->in_msg.hdcp1_create_session.display_handle = display->index;
	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP1_CREATE_SESSION;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	hdcp->auth.id = hdcp_cmd->out_msg.hdcp1_create_session.session_handle;

	अगर (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) अणु
		status = MOD_HDCP_STATUS_HDCP1_CREATE_SESSION_FAILURE;
	पूर्ण अन्यथा अणु
		hdcp->auth.msg.hdcp1.ainfo = hdcp_cmd->out_msg.hdcp1_create_session.ainfo_primary;
		स_नकल(hdcp->auth.msg.hdcp1.aksv, hdcp_cmd->out_msg.hdcp1_create_session.aksv_primary,
		       माप(hdcp->auth.msg.hdcp1.aksv));
		स_नकल(hdcp->auth.msg.hdcp1.an, hdcp_cmd->out_msg.hdcp1_create_session.an_primary,
		       माप(hdcp->auth.msg.hdcp1.an));
	पूर्ण

	mutex_unlock(&psp->hdcp_context.mutex);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp1_destroy_session(काष्ठा mod_hdcp *hdcp)
अणु

	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;
	uपूर्णांक8_t i = 0;
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_lock(&psp->hdcp_context.mutex);
	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;
	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	hdcp_cmd->in_msg.hdcp1_destroy_session.session_handle = hdcp->auth.id;
	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP1_DESTROY_SESSION;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	अगर (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) अणु
		status = MOD_HDCP_STATUS_HDCP1_DESTROY_SESSION_FAILURE;
	पूर्ण अन्यथा अणु
		HDCP_TOP_HDCP1_DESTROY_SESSION_TRACE(hdcp);
		क्रम (i = 0; i < MAX_NUM_OF_DISPLAYS; i++)
			अगर (is_display_encryption_enabled(&hdcp->displays[i])) अणु
				hdcp->displays[i].state =
							MOD_HDCP_DISPLAY_ACTIVE;
				HDCP_HDCP1_DISABLED_TRACE(
					hdcp, hdcp->displays[i].index);
			पूर्ण
	पूर्ण

	mutex_unlock(&psp->hdcp_context.mutex);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp1_validate_rx(काष्ठा mod_hdcp *hdcp)
अणु
	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_lock(&psp->hdcp_context.mutex);
	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;
	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	hdcp_cmd->in_msg.hdcp1_first_part_authentication.session_handle = hdcp->auth.id;

	स_नकल(hdcp_cmd->in_msg.hdcp1_first_part_authentication.bksv_primary, hdcp->auth.msg.hdcp1.bksv,
		TA_HDCP__HDCP1_KSV_SIZE);

	hdcp_cmd->in_msg.hdcp1_first_part_authentication.r0_prime_primary = hdcp->auth.msg.hdcp1.r0p;
	hdcp_cmd->in_msg.hdcp1_first_part_authentication.bcaps = hdcp->auth.msg.hdcp1.bcaps;
	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP1_FIRST_PART_AUTHENTICATION;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	अगर (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) अणु
		status = MOD_HDCP_STATUS_HDCP1_VALIDATE_RX_FAILURE;
	पूर्ण अन्यथा अगर (hdcp_cmd->out_msg.hdcp1_first_part_authentication.authentication_status ==
	    TA_HDCP_AUTHENTICATION_STATUS__HDCP1_FIRST_PART_COMPLETE) अणु
		/* needs second part of authentication */
		hdcp->connection.is_repeater = 1;
	पूर्ण अन्यथा अगर (hdcp_cmd->out_msg.hdcp1_first_part_authentication.authentication_status ==
		   TA_HDCP_AUTHENTICATION_STATUS__HDCP1_AUTHENTICATED) अणु
		hdcp->connection.is_repeater = 0;
	पूर्ण अन्यथा अगर (hdcp_cmd->out_msg.hdcp1_first_part_authentication.authentication_status ==
		   TA_HDCP_AUTHENTICATION_STATUS__HDCP1_KSV_REVOKED) अणु
		hdcp->connection.is_hdcp1_revoked = 1;
		status = MOD_HDCP_STATUS_HDCP1_BKSV_REVOKED;
	पूर्ण अन्यथा
		status = MOD_HDCP_STATUS_HDCP1_VALIDATE_RX_FAILURE;

	mutex_unlock(&psp->hdcp_context.mutex);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp1_enable_encryption(काष्ठा mod_hdcp *hdcp)
अणु
	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;
	काष्ठा mod_hdcp_display *display = get_first_active_display(hdcp);
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_lock(&psp->hdcp_context.mutex);
	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;
	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	hdcp_cmd->in_msg.hdcp1_enable_encryption.session_handle = hdcp->auth.id;
	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP1_ENABLE_ENCRYPTION;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	अगर (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) अणु
		status = MOD_HDCP_STATUS_HDCP1_ENABLE_ENCRYPTION_FAILURE;
	पूर्ण अन्यथा अगर (!is_dp_mst_hdcp(hdcp)) अणु
		display->state = MOD_HDCP_DISPLAY_ENCRYPTION_ENABLED;
		HDCP_HDCP1_ENABLED_TRACE(hdcp, display->index);
	पूर्ण

	mutex_unlock(&psp->hdcp_context.mutex);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp1_validate_ksvlist_vp(काष्ठा mod_hdcp *hdcp)
अणु
	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_lock(&psp->hdcp_context.mutex);
	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;
	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	hdcp_cmd->in_msg.hdcp1_second_part_authentication.session_handle = hdcp->auth.id;

	hdcp_cmd->in_msg.hdcp1_second_part_authentication.ksv_list_size = hdcp->auth.msg.hdcp1.ksvlist_size;
	स_नकल(hdcp_cmd->in_msg.hdcp1_second_part_authentication.ksv_list, hdcp->auth.msg.hdcp1.ksvlist,
	       hdcp->auth.msg.hdcp1.ksvlist_size);

	स_नकल(hdcp_cmd->in_msg.hdcp1_second_part_authentication.v_prime, hdcp->auth.msg.hdcp1.vp,
	       माप(hdcp->auth.msg.hdcp1.vp));

	hdcp_cmd->in_msg.hdcp1_second_part_authentication.bstatus_binfo =
		is_dp_hdcp(hdcp) ? hdcp->auth.msg.hdcp1.binfo_dp : hdcp->auth.msg.hdcp1.bstatus;
	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP1_SECOND_PART_AUTHENTICATION;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	अगर (hdcp_cmd->hdcp_status == TA_HDCP_STATUS__SUCCESS &&
	    hdcp_cmd->out_msg.hdcp1_second_part_authentication.authentication_status ==
		    TA_HDCP_AUTHENTICATION_STATUS__HDCP1_AUTHENTICATED) अणु
		status = MOD_HDCP_STATUS_SUCCESS;
	पूर्ण अन्यथा अगर (hdcp_cmd->out_msg.hdcp1_second_part_authentication.authentication_status ==
		   TA_HDCP_AUTHENTICATION_STATUS__HDCP1_KSV_REVOKED) अणु
		hdcp->connection.is_hdcp1_revoked = 1;
		status = MOD_HDCP_STATUS_HDCP1_KSV_LIST_REVOKED;
	पूर्ण अन्यथा अणु
		status = MOD_HDCP_STATUS_HDCP1_VALIDATE_KSV_LIST_FAILURE;
	पूर्ण

	mutex_unlock(&psp->hdcp_context.mutex);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp1_enable_dp_stream_encryption(काष्ठा mod_hdcp *hdcp)
अणु

	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;
	पूर्णांक i = 0;
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_lock(&psp->hdcp_context.mutex);
	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;

	क्रम (i = 0; i < MAX_NUM_OF_DISPLAYS; i++) अणु

		अगर (hdcp->displays[i].adjust.disable || hdcp->displays[i].state != MOD_HDCP_DISPLAY_ACTIVE)
				जारी;

		स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

		hdcp_cmd->in_msg.hdcp1_enable_dp_stream_encryption.session_handle = hdcp->auth.id;
		hdcp_cmd->in_msg.hdcp1_enable_dp_stream_encryption.display_handle = hdcp->displays[i].index;
		hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP1_ENABLE_DP_STREAM_ENCRYPTION;

		psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

		अगर (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) अणु
			status = MOD_HDCP_STATUS_HDCP1_ENABLE_STREAM_ENCRYPTION_FAILURE;
			अवरोध;
		पूर्ण

		hdcp->displays[i].state = MOD_HDCP_DISPLAY_ENCRYPTION_ENABLED;
		HDCP_HDCP1_ENABLED_TRACE(hdcp, hdcp->displays[i].index);
	पूर्ण

	mutex_unlock(&psp->hdcp_context.mutex);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp1_link_मुख्यtenance(काष्ठा mod_hdcp *hdcp)
अणु
	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_lock(&psp->hdcp_context.mutex);
	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;

	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	hdcp_cmd->in_msg.hdcp1_get_encryption_status.session_handle = hdcp->auth.id;

	hdcp_cmd->out_msg.hdcp1_get_encryption_status.protection_level = 0;
	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP1_GET_ENCRYPTION_STATUS;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	अगर (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS ||
			hdcp_cmd->out_msg.hdcp1_get_encryption_status.protection_level != 1)
		status = MOD_HDCP_STATUS_HDCP1_LINK_MAINTEन_अंकCE_FAILURE;

	mutex_unlock(&psp->hdcp_context.mutex);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp1_get_link_encryption_status(काष्ठा mod_hdcp *hdcp,
							       क्रमागत mod_hdcp_encryption_status *encryption_status)
अणु
	*encryption_status = MOD_HDCP_ENCRYPTION_STATUS_HDCP_OFF;

	अगर (mod_hdcp_hdcp1_link_मुख्यtenance(hdcp) != MOD_HDCP_STATUS_SUCCESS)
		वापस MOD_HDCP_STATUS_FAILURE;

	*encryption_status = MOD_HDCP_ENCRYPTION_STATUS_HDCP1_ON;

	वापस MOD_HDCP_STATUS_SUCCESS;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp2_create_session(काष्ठा mod_hdcp *hdcp)
अणु
	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;
	काष्ठा mod_hdcp_display *display = get_first_active_display(hdcp);
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;


	अगर (!psp->hdcp_context.hdcp_initialized) अणु
		DRM_ERROR("Failed to create hdcp session, HDCP TA is not initialized");
		वापस MOD_HDCP_STATUS_FAILURE;
	पूर्ण

	अगर (!display)
		वापस MOD_HDCP_STATUS_DISPLAY_NOT_FOUND;

	mutex_lock(&psp->hdcp_context.mutex);

	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;
	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	hdcp_cmd->in_msg.hdcp2_create_session_v2.display_handle = display->index;

	अगर (hdcp->connection.link.adjust.hdcp2.क्रमce_type == MOD_HDCP_FORCE_TYPE_0)
		hdcp_cmd->in_msg.hdcp2_create_session_v2.negotiate_content_type =
			TA_HDCP2_CONTENT_TYPE_NEGOTIATION_TYPE__FORCE_TYPE0;
	अन्यथा अगर (hdcp->connection.link.adjust.hdcp2.क्रमce_type == MOD_HDCP_FORCE_TYPE_1)
		hdcp_cmd->in_msg.hdcp2_create_session_v2.negotiate_content_type =
			TA_HDCP2_CONTENT_TYPE_NEGOTIATION_TYPE__FORCE_TYPE1;
	अन्यथा अगर (hdcp->connection.link.adjust.hdcp2.क्रमce_type == MOD_HDCP_FORCE_TYPE_MAX)
		hdcp_cmd->in_msg.hdcp2_create_session_v2.negotiate_content_type =
			TA_HDCP2_CONTENT_TYPE_NEGOTIATION_TYPE__MAX_SUPPORTED;

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_CREATE_SESSION_V2;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);


	अगर (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS)
		status = MOD_HDCP_STATUS_HDCP2_CREATE_SESSION_FAILURE;
	अन्यथा
		hdcp->auth.id = hdcp_cmd->out_msg.hdcp2_create_session_v2.session_handle;

	mutex_unlock(&psp->hdcp_context.mutex);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp2_destroy_session(काष्ठा mod_hdcp *hdcp)
अणु
	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;
	uपूर्णांक8_t i = 0;
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_lock(&psp->hdcp_context.mutex);
	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;
	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	hdcp_cmd->in_msg.hdcp2_destroy_session.session_handle = hdcp->auth.id;
	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_DESTROY_SESSION;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	अगर (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) अणु
		status = MOD_HDCP_STATUS_HDCP2_DESTROY_SESSION_FAILURE;
	पूर्ण अन्यथा अणु
		HDCP_TOP_HDCP2_DESTROY_SESSION_TRACE(hdcp);
		क्रम (i = 0; i < MAX_NUM_OF_DISPLAYS; i++)
			अगर (is_display_encryption_enabled(&hdcp->displays[i])) अणु
				hdcp->displays[i].state =
							MOD_HDCP_DISPLAY_ACTIVE;
				HDCP_HDCP2_DISABLED_TRACE(
					hdcp, hdcp->displays[i].index);
			पूर्ण
	पूर्ण

	mutex_unlock(&psp->hdcp_context.mutex);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp2_prepare_ake_init(काष्ठा mod_hdcp *hdcp)
अणु
	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_input_v2 *msg_in;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_output_v2 *msg_out;
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_lock(&psp->hdcp_context.mutex);
	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;
	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	msg_in = &hdcp_cmd->in_msg.hdcp2_prepare_process_authentication_message_v2;
	msg_out = &hdcp_cmd->out_msg.hdcp2_prepare_process_authentication_message_v2;

	hdcp2_message_init(hdcp, msg_in);

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_PREPARE_PROCESS_AUTHENTICATION_MSG_V2;
	msg_in->prepare.msg1_id = TA_HDCP_HDCP2_MSG_ID__AKE_INIT;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	अगर (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS)
		status = MOD_HDCP_STATUS_HDCP2_PREP_AKE_INIT_FAILURE;
	अन्यथा
		स_नकल(&hdcp->auth.msg.hdcp2.ake_init[0], &msg_out->prepare.transmitter_message[0],
		       माप(hdcp->auth.msg.hdcp2.ake_init));

	mutex_unlock(&psp->hdcp_context.mutex);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp2_validate_ake_cert(काष्ठा mod_hdcp *hdcp)
अणु
	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_input_v2 *msg_in;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_output_v2 *msg_out;
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_lock(&psp->hdcp_context.mutex);
	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;
	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	msg_in = &hdcp_cmd->in_msg.hdcp2_prepare_process_authentication_message_v2;
	msg_out = &hdcp_cmd->out_msg.hdcp2_prepare_process_authentication_message_v2;

	hdcp2_message_init(hdcp, msg_in);

	msg_in->process.msg1_desc.msg_id = TA_HDCP_HDCP2_MSG_ID__AKE_SEND_CERT;
	msg_in->process.msg1_desc.msg_size = TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__AKE_SEND_CERT;

	स_नकल(&msg_in->process.receiver_message[0], hdcp->auth.msg.hdcp2.ake_cert,
	       माप(hdcp->auth.msg.hdcp2.ake_cert));

	msg_in->prepare.msg1_id = TA_HDCP_HDCP2_MSG_ID__AKE_NO_STORED_KM;
	msg_in->prepare.msg2_id = TA_HDCP_HDCP2_MSG_ID__AKE_STORED_KM;

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_PREPARE_PROCESS_AUTHENTICATION_MSG_V2;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	अगर (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) अणु
		status = MOD_HDCP_STATUS_HDCP2_VALIDATE_AKE_CERT_FAILURE;
	पूर्ण अन्यथा अणु
		स_नकल(hdcp->auth.msg.hdcp2.ake_no_stored_km,
		       &msg_out->prepare.transmitter_message[0],
		       माप(hdcp->auth.msg.hdcp2.ake_no_stored_km));

		स_नकल(hdcp->auth.msg.hdcp2.ake_stored_km,
		       &msg_out->prepare.transmitter_message[माप(hdcp->auth.msg.hdcp2.ake_no_stored_km)],
		       माप(hdcp->auth.msg.hdcp2.ake_stored_km));

		अगर (msg_out->process.msg1_status ==
		    TA_HDCP2_MSG_AUTHENTICATION_STATUS__SUCCESS) अणु
			hdcp->connection.is_km_stored =
				msg_out->process.is_km_stored ? 1 : 0;
			hdcp->connection.is_repeater =
				msg_out->process.is_repeater ? 1 : 0;
			status = MOD_HDCP_STATUS_SUCCESS;
		पूर्ण अन्यथा अगर (msg_out->process.msg1_status ==
			   TA_HDCP2_MSG_AUTHENTICATION_STATUS__RECEIVERID_REVOKED) अणु
			hdcp->connection.is_hdcp2_revoked = 1;
			status = MOD_HDCP_STATUS_HDCP2_AKE_CERT_REVOKED;
		पूर्ण  अन्यथा अणु
			status = MOD_HDCP_STATUS_HDCP2_VALIDATE_AKE_CERT_FAILURE;
		पूर्ण
	पूर्ण
	mutex_unlock(&psp->hdcp_context.mutex);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp2_validate_h_prime(काष्ठा mod_hdcp *hdcp)
अणु
	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_input_v2 *msg_in;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_output_v2 *msg_out;
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_lock(&psp->hdcp_context.mutex);
	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;
	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	msg_in = &hdcp_cmd->in_msg.hdcp2_prepare_process_authentication_message_v2;
	msg_out = &hdcp_cmd->out_msg.hdcp2_prepare_process_authentication_message_v2;

	hdcp2_message_init(hdcp, msg_in);

	msg_in->process.msg1_desc.msg_id = TA_HDCP_HDCP2_MSG_ID__AKE_SEND_H_PRIME;
	msg_in->process.msg1_desc.msg_size = TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__AKE_SEND_H_PRIME;

	स_नकल(&msg_in->process.receiver_message[0], hdcp->auth.msg.hdcp2.ake_h_prime,
	       माप(hdcp->auth.msg.hdcp2.ake_h_prime));

	अगर (!hdcp->connection.is_km_stored) अणु
		msg_in->process.msg2_desc.msg_id = TA_HDCP_HDCP2_MSG_ID__AKE_SEND_PAIRING_INFO;
		msg_in->process.msg2_desc.msg_size = TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__AKE_SEND_PAIRING_INFO;
		स_नकल(&msg_in->process.receiver_message[माप(hdcp->auth.msg.hdcp2.ake_h_prime)],
		       hdcp->auth.msg.hdcp2.ake_pairing_info, माप(hdcp->auth.msg.hdcp2.ake_pairing_info));
	पूर्ण

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_PREPARE_PROCESS_AUTHENTICATION_MSG_V2;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	अगर (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS)
		status = MOD_HDCP_STATUS_HDCP2_VALIDATE_H_PRIME_FAILURE;
	अन्यथा अगर (msg_out->process.msg1_status != TA_HDCP2_MSG_AUTHENTICATION_STATUS__SUCCESS)
		status = MOD_HDCP_STATUS_HDCP2_VALIDATE_H_PRIME_FAILURE;
	अन्यथा अगर (!hdcp->connection.is_km_stored &&
		   msg_out->process.msg2_status != TA_HDCP2_MSG_AUTHENTICATION_STATUS__SUCCESS)
		status = MOD_HDCP_STATUS_HDCP2_VALIDATE_PAIRING_INFO_FAILURE;

	mutex_unlock(&psp->hdcp_context.mutex);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp2_prepare_lc_init(काष्ठा mod_hdcp *hdcp)
अणु
	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_input_v2 *msg_in;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_output_v2 *msg_out;
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_lock(&psp->hdcp_context.mutex);
	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;
	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	msg_in = &hdcp_cmd->in_msg.hdcp2_prepare_process_authentication_message_v2;
	msg_out = &hdcp_cmd->out_msg.hdcp2_prepare_process_authentication_message_v2;

	hdcp2_message_init(hdcp, msg_in);

	msg_in->prepare.msg1_id = TA_HDCP_HDCP2_MSG_ID__LC_INIT;

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_PREPARE_PROCESS_AUTHENTICATION_MSG_V2;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	अगर (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS)
		status = MOD_HDCP_STATUS_HDCP2_PREP_LC_INIT_FAILURE;
	अन्यथा
		स_नकल(hdcp->auth.msg.hdcp2.lc_init, &msg_out->prepare.transmitter_message[0],
		       माप(hdcp->auth.msg.hdcp2.lc_init));

	mutex_unlock(&psp->hdcp_context.mutex);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp2_validate_l_prime(काष्ठा mod_hdcp *hdcp)
अणु
	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_input_v2 *msg_in;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_output_v2 *msg_out;
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_lock(&psp->hdcp_context.mutex);
	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;
	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	msg_in = &hdcp_cmd->in_msg.hdcp2_prepare_process_authentication_message_v2;
	msg_out = &hdcp_cmd->out_msg.hdcp2_prepare_process_authentication_message_v2;

	hdcp2_message_init(hdcp, msg_in);

	msg_in->process.msg1_desc.msg_id = TA_HDCP_HDCP2_MSG_ID__LC_SEND_L_PRIME;
	msg_in->process.msg1_desc.msg_size = TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__LC_SEND_L_PRIME;

	स_नकल(&msg_in->process.receiver_message[0], hdcp->auth.msg.hdcp2.lc_l_prime,
	       माप(hdcp->auth.msg.hdcp2.lc_l_prime));

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_PREPARE_PROCESS_AUTHENTICATION_MSG_V2;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	अगर (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS ||
			msg_out->process.msg1_status != TA_HDCP2_MSG_AUTHENTICATION_STATUS__SUCCESS)
		status = MOD_HDCP_STATUS_HDCP2_VALIDATE_L_PRIME_FAILURE;

	mutex_unlock(&psp->hdcp_context.mutex);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp2_prepare_eks(काष्ठा mod_hdcp *hdcp)
अणु
	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_input_v2 *msg_in;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_output_v2 *msg_out;
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_lock(&psp->hdcp_context.mutex);
	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;
	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	msg_in = &hdcp_cmd->in_msg.hdcp2_prepare_process_authentication_message_v2;
	msg_out = &hdcp_cmd->out_msg.hdcp2_prepare_process_authentication_message_v2;

	hdcp2_message_init(hdcp, msg_in);

	msg_in->prepare.msg1_id = TA_HDCP_HDCP2_MSG_ID__SKE_SEND_EKS;

	अगर (is_dp_hdcp(hdcp))
		msg_in->prepare.msg2_id = TA_HDCP_HDCP2_MSG_ID__SIGNAL_CONTENT_STREAM_TYPE_DP;

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_PREPARE_PROCESS_AUTHENTICATION_MSG_V2;
	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	अगर (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) अणु
		status = MOD_HDCP_STATUS_HDCP2_PREP_EKS_FAILURE;
	पूर्ण अन्यथा अणु
		स_नकल(hdcp->auth.msg.hdcp2.ske_eks,
		       &msg_out->prepare.transmitter_message[0],
		       माप(hdcp->auth.msg.hdcp2.ske_eks));
		msg_out->prepare.msg1_desc.msg_size =
			माप(hdcp->auth.msg.hdcp2.ske_eks);

		अगर (is_dp_hdcp(hdcp)) अणु
			स_नकल(hdcp->auth.msg.hdcp2.content_stream_type_dp,
			       &msg_out->prepare.transmitter_message[माप(hdcp->auth.msg.hdcp2.ske_eks)],
			       माप(hdcp->auth.msg.hdcp2.content_stream_type_dp));
		पूर्ण
	पूर्ण
	mutex_unlock(&psp->hdcp_context.mutex);

	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp2_enable_encryption(काष्ठा mod_hdcp *hdcp)
अणु
	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;
	काष्ठा mod_hdcp_display *display = get_first_active_display(hdcp);
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (!display)
		वापस MOD_HDCP_STATUS_DISPLAY_NOT_FOUND;

	mutex_lock(&psp->hdcp_context.mutex);

	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;
	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	hdcp_cmd->in_msg.hdcp2_set_encryption.session_handle = hdcp->auth.id;

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_SET_ENCRYPTION;
	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	अगर (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) अणु
		status = MOD_HDCP_STATUS_HDCP2_ENABLE_ENCRYPTION_FAILURE;
	पूर्ण अन्यथा अगर (!is_dp_mst_hdcp(hdcp)) अणु
		display->state = MOD_HDCP_DISPLAY_ENCRYPTION_ENABLED;
		HDCP_HDCP2_ENABLED_TRACE(hdcp, display->index);
	पूर्ण

	mutex_unlock(&psp->hdcp_context.mutex);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp2_validate_rx_id_list(काष्ठा mod_hdcp *hdcp)
अणु
	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_input_v2 *msg_in;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_output_v2 *msg_out;
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_lock(&psp->hdcp_context.mutex);

	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;
	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	msg_in = &hdcp_cmd->in_msg.hdcp2_prepare_process_authentication_message_v2;
	msg_out = &hdcp_cmd->out_msg.hdcp2_prepare_process_authentication_message_v2;

	hdcp2_message_init(hdcp, msg_in);

	msg_in->process.msg1_desc.msg_id = TA_HDCP_HDCP2_MSG_ID__REPEATERAUTH_SEND_RECEIVERID_LIST;
	msg_in->process.msg1_desc.msg_size = माप(hdcp->auth.msg.hdcp2.rx_id_list);
	स_नकल(&msg_in->process.receiver_message[0], hdcp->auth.msg.hdcp2.rx_id_list,
	       माप(hdcp->auth.msg.hdcp2.rx_id_list));

	msg_in->prepare.msg1_id = TA_HDCP_HDCP2_MSG_ID__REPEATERAUTH_SEND_ACK;

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_PREPARE_PROCESS_AUTHENTICATION_MSG_V2;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	अगर (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) अणु
		status = MOD_HDCP_STATUS_HDCP2_VALIDATE_RX_ID_LIST_FAILURE;
	पूर्ण अन्यथा अणु
		स_नकल(hdcp->auth.msg.hdcp2.repeater_auth_ack,
		       &msg_out->prepare.transmitter_message[0],
		       माप(hdcp->auth.msg.hdcp2.repeater_auth_ack));

		अगर (msg_out->process.msg1_status ==
		    TA_HDCP2_MSG_AUTHENTICATION_STATUS__SUCCESS) अणु
			hdcp->connection.is_km_stored = msg_out->process.is_km_stored ? 1 : 0;
			hdcp->connection.is_repeater = msg_out->process.is_repeater ? 1 : 0;
			status = MOD_HDCP_STATUS_SUCCESS;
		पूर्ण अन्यथा अगर (msg_out->process.msg1_status ==
			   TA_HDCP2_MSG_AUTHENTICATION_STATUS__RECEIVERID_REVOKED) अणु
			hdcp->connection.is_hdcp2_revoked = 1;
			status = MOD_HDCP_STATUS_HDCP2_RX_ID_LIST_REVOKED;
		पूर्ण अन्यथा अणु
			status = MOD_HDCP_STATUS_HDCP2_VALIDATE_RX_ID_LIST_FAILURE;
		पूर्ण
	पूर्ण
	mutex_unlock(&psp->hdcp_context.mutex);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp2_enable_dp_stream_encryption(काष्ठा mod_hdcp *hdcp)
अणु
	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_input_v2 *msg_in;
	uपूर्णांक8_t i;
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_lock(&psp->hdcp_context.mutex);
	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;
	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	msg_in = &hdcp_cmd->in_msg.hdcp2_prepare_process_authentication_message_v2;

	hdcp2_message_init(hdcp, msg_in);


	क्रम (i = 0; i < MAX_NUM_OF_DISPLAYS; i++) अणु
		अगर (hdcp->displays[i].adjust.disable || hdcp->displays[i].state != MOD_HDCP_DISPLAY_ACTIVE)
				जारी;

		hdcp_cmd->in_msg.hdcp2_enable_dp_stream_encryption.display_handle = hdcp->displays[i].index;
		hdcp_cmd->in_msg.hdcp2_enable_dp_stream_encryption.session_handle = hdcp->auth.id;

		hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_ENABLE_DP_STREAM_ENCRYPTION;
		psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

		अगर (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS)
			अवरोध;

		hdcp->displays[i].state = MOD_HDCP_DISPLAY_ENCRYPTION_ENABLED;
		HDCP_HDCP2_ENABLED_TRACE(hdcp, hdcp->displays[i].index);
	पूर्ण

	अगर (hdcp_cmd->hdcp_status == TA_HDCP_STATUS__SUCCESS)
		status = MOD_HDCP_STATUS_SUCCESS;
	अन्यथा
		status = MOD_HDCP_STATUS_HDCP2_ENABLE_STREAM_ENCRYPTION_FAILURE;

	mutex_unlock(&psp->hdcp_context.mutex);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp2_prepare_stream_management(काष्ठा mod_hdcp *hdcp)
अणु

	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_input_v2 *msg_in;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_output_v2 *msg_out;
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_lock(&psp->hdcp_context.mutex);
	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;
	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	msg_in = &hdcp_cmd->in_msg.hdcp2_prepare_process_authentication_message_v2;
	msg_out = &hdcp_cmd->out_msg.hdcp2_prepare_process_authentication_message_v2;

	hdcp2_message_init(hdcp, msg_in);

	msg_in->prepare.msg1_id = TA_HDCP_HDCP2_MSG_ID__REPEATERAUTH_STREAM_MANAGE;


	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_PREPARE_PROCESS_AUTHENTICATION_MSG_V2;
	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	अगर (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) अणु
		status = MOD_HDCP_STATUS_HDCP2_PREPARE_STREAM_MANAGEMENT_FAILURE;
	पूर्ण अन्यथा अणु
		hdcp->auth.msg.hdcp2.stream_manage_size = msg_out->prepare.msg1_desc.msg_size;

		स_नकल(hdcp->auth.msg.hdcp2.repeater_auth_stream_manage,
		       &msg_out->prepare.transmitter_message[0],
		       माप(hdcp->auth.msg.hdcp2.repeater_auth_stream_manage));
	पूर्ण
	mutex_unlock(&psp->hdcp_context.mutex);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_hdcp2_validate_stream_पढ़ोy(काष्ठा mod_hdcp *hdcp)
अणु
	काष्ठा psp_context *psp = hdcp->config.psp.handle;
	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_input_v2 *msg_in;
	काष्ठा ta_hdcp_cmd_hdcp2_process_prepare_authentication_message_output_v2 *msg_out;
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_lock(&psp->hdcp_context.mutex);
	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;
	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	msg_in = &hdcp_cmd->in_msg.hdcp2_prepare_process_authentication_message_v2;
	msg_out = &hdcp_cmd->out_msg.hdcp2_prepare_process_authentication_message_v2;

	hdcp2_message_init(hdcp, msg_in);

	msg_in->process.msg1_desc.msg_id = TA_HDCP_HDCP2_MSG_ID__REPEATERAUTH_STREAM_READY;

	msg_in->process.msg1_desc.msg_size = माप(hdcp->auth.msg.hdcp2.repeater_auth_stream_पढ़ोy);

	स_नकल(&msg_in->process.receiver_message[0], hdcp->auth.msg.hdcp2.repeater_auth_stream_पढ़ोy,
	       माप(hdcp->auth.msg.hdcp2.repeater_auth_stream_पढ़ोy));

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_PREPARE_PROCESS_AUTHENTICATION_MSG_V2;
	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	अगर (hdcp_cmd->hdcp_status == TA_HDCP_STATUS__SUCCESS &&
	    msg_out->process.msg1_status == TA_HDCP2_MSG_AUTHENTICATION_STATUS__SUCCESS)
		status = MOD_HDCP_STATUS_SUCCESS;
	अन्यथा
		status = MOD_HDCP_STATUS_HDCP2_VALIDATE_STREAM_READY_FAILURE;

	mutex_unlock(&psp->hdcp_context.mutex);
	वापस status;
पूर्ण

bool mod_hdcp_is_link_encryption_enabled(काष्ठा mod_hdcp *hdcp)
अणु
	/* unsupported */
	वापस true;
पूर्ण

व्योम mod_hdcp_save_current_encryption_states(काष्ठा mod_hdcp *hdcp)
अणु
	/* unsupported */
पूर्ण
