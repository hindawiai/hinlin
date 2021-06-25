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

#समावेश "dmub_psr.h"
#समावेश "dc.h"
#समावेश "dc_dmub_srv.h"
#समावेश "dmub/dmub_srv.h"
#समावेश "core_types.h"

#घोषणा MAX_PIPES 6

/*
 * Convert dmcub psr state to dmcu psr state.
 */
अटल क्रमागत dc_psr_state convert_psr_state(uपूर्णांक32_t raw_state)
अणु
	क्रमागत dc_psr_state state = PSR_STATE0;

	अगर (raw_state == 0)
		state = PSR_STATE0;
	अन्यथा अगर (raw_state == 0x10)
		state = PSR_STATE1;
	अन्यथा अगर (raw_state == 0x11)
		state = PSR_STATE1a;
	अन्यथा अगर (raw_state == 0x20)
		state = PSR_STATE2;
	अन्यथा अगर (raw_state == 0x21)
		state = PSR_STATE2a;
	अन्यथा अगर (raw_state == 0x30)
		state = PSR_STATE3;
	अन्यथा अगर (raw_state == 0x31)
		state = PSR_STATE3Init;
	अन्यथा अगर (raw_state == 0x40)
		state = PSR_STATE4;
	अन्यथा अगर (raw_state == 0x41)
		state = PSR_STATE4a;
	अन्यथा अगर (raw_state == 0x42)
		state = PSR_STATE4b;
	अन्यथा अगर (raw_state == 0x43)
		state = PSR_STATE4c;
	अन्यथा अगर (raw_state == 0x44)
		state = PSR_STATE4d;
	अन्यथा अगर (raw_state == 0x50)
		state = PSR_STATE5;
	अन्यथा अगर (raw_state == 0x51)
		state = PSR_STATE5a;
	अन्यथा अगर (raw_state == 0x52)
		state = PSR_STATE5b;
	अन्यथा अगर (raw_state == 0x53)
		state = PSR_STATE5c;

	वापस state;
पूर्ण

/*
 * Get PSR state from firmware.
 */
अटल व्योम dmub_psr_get_state(काष्ठा dmub_psr *dmub, क्रमागत dc_psr_state *state)
अणु
	काष्ठा dmub_srv *srv = dmub->ctx->dmub_srv->dmub;
	uपूर्णांक32_t raw_state = 0;
	uपूर्णांक32_t retry_count = 0;
	क्रमागत dmub_status status;

	करो अणु
		// Send gpपूर्णांक command and रुको क्रम ack
		status = dmub_srv_send_gpपूर्णांक_command(srv, DMUB_GPINT__GET_PSR_STATE, 0, 30);

		अगर (status == DMUB_STATUS_OK) अणु
			// GPINT was executed, get response
			dmub_srv_get_gpपूर्णांक_response(srv, &raw_state);
			*state = convert_psr_state(raw_state);
		पूर्ण अन्यथा
			// Return invalid state when GPINT बार out
			*state = PSR_STATE_INVALID;

		// Assert अगर max retry hit
		अगर (retry_count >= 1000)
			ASSERT(0);
	पूर्ण जबतक (++retry_count <= 1000 && *state == PSR_STATE_INVALID);
पूर्ण

/*
 * Set PSR version.
 */
अटल bool dmub_psr_set_version(काष्ठा dmub_psr *dmub, काष्ठा dc_stream_state *stream)
अणु
	जोड़ dmub_rb_cmd cmd;
	काष्ठा dc_context *dc = dmub->ctx;

	अगर (stream->link->psr_settings.psr_version == DC_PSR_VERSION_UNSUPPORTED)
		वापस false;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.psr_set_version.header.type = DMUB_CMD__PSR;
	cmd.psr_set_version.header.sub_type = DMUB_CMD__PSR_SET_VERSION;
	चयन (stream->link->psr_settings.psr_version) अणु
	हाल DC_PSR_VERSION_1:
		cmd.psr_set_version.psr_set_version_data.version = PSR_VERSION_1;
		अवरोध;
	हाल DC_PSR_VERSION_UNSUPPORTED:
	शेष:
		cmd.psr_set_version.psr_set_version_data.version = PSR_VERSION_UNSUPPORTED;
		अवरोध;
	पूर्ण
	cmd.psr_set_version.header.payload_bytes = माप(काष्ठा dmub_cmd_psr_set_version_data);

	dc_dmub_srv_cmd_queue(dc->dmub_srv, &cmd);
	dc_dmub_srv_cmd_execute(dc->dmub_srv);
	dc_dmub_srv_रुको_idle(dc->dmub_srv);

	वापस true;
पूर्ण

/*
 * Enable/Disable PSR.
 */
अटल व्योम dmub_psr_enable(काष्ठा dmub_psr *dmub, bool enable, bool रुको)
अणु
	जोड़ dmub_rb_cmd cmd;
	काष्ठा dc_context *dc = dmub->ctx;
	uपूर्णांक32_t retry_count;
	क्रमागत dc_psr_state state = PSR_STATE0;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.psr_enable.header.type = DMUB_CMD__PSR;

	अगर (enable)
		cmd.psr_enable.header.sub_type = DMUB_CMD__PSR_ENABLE;
	अन्यथा
		cmd.psr_enable.header.sub_type = DMUB_CMD__PSR_DISABLE;

	cmd.psr_enable.header.payload_bytes = 0; // Send header only

	dc_dmub_srv_cmd_queue(dc->dmub_srv, &cmd);
	dc_dmub_srv_cmd_execute(dc->dmub_srv);
	dc_dmub_srv_रुको_idle(dc->dmub_srv);

	/* Below loops 1000 x 500us = 500 ms.
	 *  Exit PSR may need to रुको 1-2 frames to घातer up. Timeout after at
	 *  least a few frames. Should never hit the max retry निश्चित below.
	 */
	अगर (रुको) अणु
		क्रम (retry_count = 0; retry_count <= 1000; retry_count++) अणु
			dmub_psr_get_state(dmub, &state);

			अगर (enable) अणु
				अगर (state != PSR_STATE0)
					अवरोध;
			पूर्ण अन्यथा अणु
				अगर (state == PSR_STATE0)
					अवरोध;
			पूर्ण

			udelay(500);
		पूर्ण

		/* निश्चित अगर max retry hit */
		अगर (retry_count >= 1000)
			ASSERT(0);
	पूर्ण
पूर्ण

/*
 * Set PSR level.
 */
अटल व्योम dmub_psr_set_level(काष्ठा dmub_psr *dmub, uपूर्णांक16_t psr_level)
अणु
	जोड़ dmub_rb_cmd cmd;
	क्रमागत dc_psr_state state = PSR_STATE0;
	काष्ठा dc_context *dc = dmub->ctx;

	dmub_psr_get_state(dmub, &state);

	अगर (state == PSR_STATE0)
		वापस;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.psr_set_level.header.type = DMUB_CMD__PSR;
	cmd.psr_set_level.header.sub_type = DMUB_CMD__PSR_SET_LEVEL;
	cmd.psr_set_level.header.payload_bytes = माप(काष्ठा dmub_cmd_psr_set_level_data);
	cmd.psr_set_level.psr_set_level_data.psr_level = psr_level;

	dc_dmub_srv_cmd_queue(dc->dmub_srv, &cmd);
	dc_dmub_srv_cmd_execute(dc->dmub_srv);
	dc_dmub_srv_रुको_idle(dc->dmub_srv);
पूर्ण

/*
 * Setup PSR by programming phy रेजिस्टरs and sending psr hw context values to firmware.
 */
अटल bool dmub_psr_copy_settings(काष्ठा dmub_psr *dmub,
		काष्ठा dc_link *link,
		काष्ठा psr_context *psr_context)
अणु
	जोड़ dmub_rb_cmd cmd;
	काष्ठा dc_context *dc = dmub->ctx;
	काष्ठा dmub_cmd_psr_copy_settings_data *copy_settings_data
		= &cmd.psr_copy_settings.psr_copy_settings_data;
	काष्ठा pipe_ctx *pipe_ctx = शून्य;
	काष्ठा resource_context *res_ctx = &link->ctx->dc->current_state->res_ctx;
	पूर्णांक i = 0;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		अगर (res_ctx->pipe_ctx[i].stream &&
		    res_ctx->pipe_ctx[i].stream->link == link &&
		    res_ctx->pipe_ctx[i].stream->link->connector_संकेत == SIGNAL_TYPE_EDP) अणु
			pipe_ctx = &res_ctx->pipe_ctx[i];
			//TODO: refactor क्रम multi edp support
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!pipe_ctx)
		वापस false;

	// First, set the psr version
	अगर (!dmub_psr_set_version(dmub, pipe_ctx->stream))
		वापस false;

	// Program DP DPHY fast training रेजिस्टरs
	link->link_enc->funcs->psr_program_dp_dphy_fast_training(link->link_enc,
			psr_context->psrExitLinkTrainingRequired);

	// Program DP_SEC_CNTL1 रेजिस्टर to set transmission GPS0 line num and priority to high
	link->link_enc->funcs->psr_program_secondary_packet(link->link_enc,
			psr_context->sdpTransmitLineNumDeadline);

	स_रखो(&cmd, 0, माप(cmd));
	cmd.psr_copy_settings.header.type = DMUB_CMD__PSR;
	cmd.psr_copy_settings.header.sub_type = DMUB_CMD__PSR_COPY_SETTINGS;
	cmd.psr_copy_settings.header.payload_bytes = माप(काष्ठा dmub_cmd_psr_copy_settings_data);

	// Hw insts
	copy_settings_data->dpphy_inst				= psr_context->transmitterId;
	copy_settings_data->aux_inst				= psr_context->channel;
	copy_settings_data->digfe_inst				= psr_context->engineId;
	copy_settings_data->digbe_inst				= psr_context->transmitterId;

	copy_settings_data->mpcc_inst				= pipe_ctx->plane_res.mpcc_inst;

	अगर (pipe_ctx->plane_res.dpp)
		copy_settings_data->dpp_inst			= pipe_ctx->plane_res.dpp->inst;
	अन्यथा
		copy_settings_data->dpp_inst			= 0;
	अगर (pipe_ctx->stream_res.opp)
		copy_settings_data->opp_inst			= pipe_ctx->stream_res.opp->inst;
	अन्यथा
		copy_settings_data->opp_inst			= 0;
	अगर (pipe_ctx->stream_res.tg)
		copy_settings_data->otg_inst			= pipe_ctx->stream_res.tg->inst;
	अन्यथा
		copy_settings_data->otg_inst			= 0;

	// Misc
	copy_settings_data->psr_level				= psr_context->psr_level.u32all;
	copy_settings_data->smu_optimizations_en		= psr_context->allow_smu_optimizations;
	copy_settings_data->multi_disp_optimizations_en	= psr_context->allow_multi_disp_optimizations;
	copy_settings_data->frame_delay				= psr_context->frame_delay;
	copy_settings_data->frame_cap_ind			= psr_context->psrFrameCaptureIndicationReq;
	copy_settings_data->init_sdp_deadline			= psr_context->sdpTransmitLineNumDeadline;
	copy_settings_data->debug.u32All = 0;
	copy_settings_data->debug.bitfields.visual_confirm	= dc->dc->debug.visual_confirm == VISUAL_CONFIRM_PSR;
	copy_settings_data->debug.bitfields.use_hw_lock_mgr		= 1;
	copy_settings_data->fec_enable_status = (link->fec_state == dc_link_fec_enabled);
	copy_settings_data->fec_enable_delay_in100us = link->dc->debug.fec_enable_delay_in100us;

	dc_dmub_srv_cmd_queue(dc->dmub_srv, &cmd);
	dc_dmub_srv_cmd_execute(dc->dmub_srv);
	dc_dmub_srv_रुको_idle(dc->dmub_srv);

	वापस true;
पूर्ण

/*
 * Send command to PSR to क्रमce अटल ENTER and ignore all state changes until निकास
 */
अटल व्योम dmub_psr_क्रमce_अटल(काष्ठा dmub_psr *dmub)
अणु
	जोड़ dmub_rb_cmd cmd;
	काष्ठा dc_context *dc = dmub->ctx;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.psr_क्रमce_अटल.header.type = DMUB_CMD__PSR;
	cmd.psr_क्रमce_अटल.header.sub_type = DMUB_CMD__PSR_FORCE_STATIC;
	cmd.psr_enable.header.payload_bytes = 0;

	dc_dmub_srv_cmd_queue(dc->dmub_srv, &cmd);
	dc_dmub_srv_cmd_execute(dc->dmub_srv);
	dc_dmub_srv_रुको_idle(dc->dmub_srv);
पूर्ण

/*
 * Get PSR residency from firmware.
 */
अटल व्योम dmub_psr_get_residency(काष्ठा dmub_psr *dmub, uपूर्णांक32_t *residency)
अणु
	काष्ठा dmub_srv *srv = dmub->ctx->dmub_srv->dmub;

	// Send gpपूर्णांक command and रुको क्रम ack
	dmub_srv_send_gpपूर्णांक_command(srv, DMUB_GPINT__PSR_RESIDENCY, 0, 30);

	dmub_srv_get_gpपूर्णांक_response(srv, residency);
पूर्ण

अटल स्थिर काष्ठा dmub_psr_funcs psr_funcs = अणु
	.psr_copy_settings		= dmub_psr_copy_settings,
	.psr_enable			= dmub_psr_enable,
	.psr_get_state			= dmub_psr_get_state,
	.psr_set_level			= dmub_psr_set_level,
	.psr_क्रमce_अटल		= dmub_psr_क्रमce_अटल,
	.psr_get_residency		= dmub_psr_get_residency,
पूर्ण;

/*
 * Conकाष्ठा PSR object.
 */
अटल व्योम dmub_psr_स्थिरruct(काष्ठा dmub_psr *psr, काष्ठा dc_context *ctx)
अणु
	psr->ctx = ctx;
	psr->funcs = &psr_funcs;
पूर्ण

/*
 * Allocate and initialize PSR object.
 */
काष्ठा dmub_psr *dmub_psr_create(काष्ठा dc_context *ctx)
अणु
	काष्ठा dmub_psr *psr = kzalloc(माप(काष्ठा dmub_psr), GFP_KERNEL);

	अगर (psr == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dmub_psr_स्थिरruct(psr, ctx);

	वापस psr;
पूर्ण

/*
 * Deallocate PSR object.
 */
व्योम dmub_psr_destroy(काष्ठा dmub_psr **dmub)
अणु
	kमुक्त(*dmub);
	*dmub = शून्य;
पूर्ण
