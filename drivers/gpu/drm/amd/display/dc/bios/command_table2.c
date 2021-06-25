<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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

#समावेश "dm_services.h"

#समावेश "ObjectID.h"

#समावेश "atomfirmware.h"
#समावेश "atom.h"
#समावेश "include/bios_parser_interface.h"

#समावेश "command_table2.h"
#समावेश "command_table_helper2.h"
#समावेश "bios_parser_helper.h"
#समावेश "bios_parser_types_internal2.h"
#समावेश "amdgpu.h"

#समावेश "dc_dmub_srv.h"
#समावेश "dc.h"

#घोषणा DC_LOGGER \
	bp->base.ctx->logger

#घोषणा GET_INDEX_INTO_MASTER_TABLE(MasterOrData, FieldName)\
	(((अक्षर *)(&((\
		काष्ठा atom_master_list_of_##MasterOrData##_functions_v2_1 *)0)\
		->FieldName)-(अक्षर *)0)/माप(uपूर्णांक16_t))

#घोषणा EXEC_BIOS_CMD_TABLE(fname, params)\
	(amdgpu_atom_execute_table(((काष्ठा amdgpu_device *)bp->base.ctx->driver_context)->mode_info.atom_context, \
		GET_INDEX_INTO_MASTER_TABLE(command, fname), \
		(uपूर्णांक32_t *)&params) == 0)

#घोषणा BIOS_CMD_TABLE_REVISION(fname, frev, crev)\
	amdgpu_atom_parse_cmd_header(((काष्ठा amdgpu_device *)bp->base.ctx->driver_context)->mode_info.atom_context, \
		GET_INDEX_INTO_MASTER_TABLE(command, fname), &frev, &crev)

#घोषणा BIOS_CMD_TABLE_PARA_REVISION(fname)\
	bios_cmd_table_para_revision(bp->base.ctx->driver_context, \
			GET_INDEX_INTO_MASTER_TABLE(command, fname))



अटल uपूर्णांक32_t bios_cmd_table_para_revision(व्योम *dev,
					     uपूर्णांक32_t index)
अणु
	काष्ठा amdgpu_device *adev = dev;
	uपूर्णांक8_t frev, crev;

	अगर (amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context,
					index,
					&frev, &crev))
		वापस crev;
	अन्यथा
		वापस 0;
पूर्ण

/******************************************************************************
 ******************************************************************************
 **
 **                  D I G E N C O D E R C O N T R O L
 **
 ******************************************************************************
 *****************************************************************************/

अटल क्रमागत bp_result encoder_control_digx_v1_5(
	काष्ठा bios_parser *bp,
	काष्ठा bp_encoder_control *cntl);

अटल क्रमागत bp_result encoder_control_fallback(
	काष्ठा bios_parser *bp,
	काष्ठा bp_encoder_control *cntl);

अटल व्योम init_dig_encoder_control(काष्ठा bios_parser *bp)
अणु
	uपूर्णांक32_t version =
		BIOS_CMD_TABLE_PARA_REVISION(digxencodercontrol);

	चयन (version) अणु
	हाल 5:
		bp->cmd_tbl.dig_encoder_control = encoder_control_digx_v1_5;
		अवरोध;
	शेष:
		dm_output_to_console("Don't have dig_encoder_control for v%d\n", version);
		bp->cmd_tbl.dig_encoder_control = encoder_control_fallback;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम encoder_control_dmcub(
		काष्ठा dc_dmub_srv *dmcub,
		काष्ठा dig_encoder_stream_setup_parameters_v1_5 *dig)
अणु
	जोड़ dmub_rb_cmd cmd;

	स_रखो(&cmd, 0, माप(cmd));

	cmd.digx_encoder_control.header.type = DMUB_CMD__VBIOS;
	cmd.digx_encoder_control.header.sub_type =
		DMUB_CMD__VBIOS_DIGX_ENCODER_CONTROL;
	cmd.digx_encoder_control.header.payload_bytes =
		माप(cmd.digx_encoder_control) -
		माप(cmd.digx_encoder_control.header);
	cmd.digx_encoder_control.encoder_control.dig.stream_param = *dig;

	dc_dmub_srv_cmd_queue(dmcub, &cmd);
	dc_dmub_srv_cmd_execute(dmcub);
	dc_dmub_srv_रुको_idle(dmcub);
पूर्ण

अटल क्रमागत bp_result encoder_control_digx_v1_5(
	काष्ठा bios_parser *bp,
	काष्ठा bp_encoder_control *cntl)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	काष्ठा dig_encoder_stream_setup_parameters_v1_5 params = अणु0पूर्ण;

	params.digid = (uपूर्णांक8_t)(cntl->engine_id);
	params.action = bp->cmd_helper->encoder_action_to_atom(cntl->action);

	params.pclk_10khz = cntl->pixel_घड़ी / 10;
	params.digmode =
			(uपूर्णांक8_t)(bp->cmd_helper->encoder_mode_bp_to_atom(
					cntl->संकेत,
					cntl->enable_dp_audio));
	params.lanक्रमागत = (uपूर्णांक8_t)(cntl->lanes_number);

	चयन (cntl->color_depth) अणु
	हाल COLOR_DEPTH_888:
		params.bitpercolor = PANEL_8BIT_PER_COLOR;
		अवरोध;
	हाल COLOR_DEPTH_101010:
		params.bitpercolor = PANEL_10BIT_PER_COLOR;
		अवरोध;
	हाल COLOR_DEPTH_121212:
		params.bitpercolor = PANEL_12BIT_PER_COLOR;
		अवरोध;
	हाल COLOR_DEPTH_161616:
		params.bitpercolor = PANEL_16BIT_PER_COLOR;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (cntl->संकेत == SIGNAL_TYPE_HDMI_TYPE_A)
		चयन (cntl->color_depth) अणु
		हाल COLOR_DEPTH_101010:
			params.pclk_10khz =
				(params.pclk_10khz * 30) / 24;
			अवरोध;
		हाल COLOR_DEPTH_121212:
			params.pclk_10khz =
				(params.pclk_10khz * 36) / 24;
			अवरोध;
		हाल COLOR_DEPTH_161616:
			params.pclk_10khz =
				(params.pclk_10khz * 48) / 24;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

	अगर (bp->base.ctx->dc->ctx->dmub_srv &&
	    bp->base.ctx->dc->debug.dmub_command_table) अणु
		encoder_control_dmcub(bp->base.ctx->dmub_srv, &params);
		वापस BP_RESULT_OK;
	पूर्ण

	अगर (EXEC_BIOS_CMD_TABLE(digxencodercontrol, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

अटल क्रमागत bp_result encoder_control_fallback(
	काष्ठा bios_parser *bp,
	काष्ठा bp_encoder_control *cntl)
अणु
	अगर (bp->base.ctx->dc->ctx->dmub_srv &&
	    bp->base.ctx->dc->debug.dmub_command_table) अणु
		वापस encoder_control_digx_v1_5(bp, cntl);
	पूर्ण

	वापस BP_RESULT_FAILURE;
पूर्ण

/*****************************************************************************
 ******************************************************************************
 **
 **                  TRANSMITTER CONTROL
 **
 ******************************************************************************
 *****************************************************************************/

अटल क्रमागत bp_result transmitter_control_v1_6(
	काष्ठा bios_parser *bp,
	काष्ठा bp_transmitter_control *cntl);

अटल क्रमागत bp_result transmitter_control_v1_7(
	काष्ठा bios_parser *bp,
	काष्ठा bp_transmitter_control *cntl);

अटल क्रमागत bp_result transmitter_control_fallback(
	काष्ठा bios_parser *bp,
	काष्ठा bp_transmitter_control *cntl);

अटल व्योम init_transmitter_control(काष्ठा bios_parser *bp)
अणु
	uपूर्णांक8_t frev;
	uपूर्णांक8_t crev;

	BIOS_CMD_TABLE_REVISION(dig1transmittercontrol, frev, crev);

	चयन (crev) अणु
	हाल 6:
		bp->cmd_tbl.transmitter_control = transmitter_control_v1_6;
		अवरोध;
	हाल 7:
		bp->cmd_tbl.transmitter_control = transmitter_control_v1_7;
		अवरोध;
	शेष:
		dm_output_to_console("Don't have transmitter_control for v%d\n", crev);
		bp->cmd_tbl.transmitter_control = transmitter_control_fallback;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम transmitter_control_dmcub(
		काष्ठा dc_dmub_srv *dmcub,
		काष्ठा dig_transmitter_control_parameters_v1_6 *dig)
अणु
	जोड़ dmub_rb_cmd cmd;

	स_रखो(&cmd, 0, माप(cmd));

	cmd.dig1_transmitter_control.header.type = DMUB_CMD__VBIOS;
	cmd.dig1_transmitter_control.header.sub_type =
		DMUB_CMD__VBIOS_DIG1_TRANSMITTER_CONTROL;
	cmd.dig1_transmitter_control.header.payload_bytes =
		माप(cmd.dig1_transmitter_control) -
		माप(cmd.dig1_transmitter_control.header);
	cmd.dig1_transmitter_control.transmitter_control.dig = *dig;

	dc_dmub_srv_cmd_queue(dmcub, &cmd);
	dc_dmub_srv_cmd_execute(dmcub);
	dc_dmub_srv_रुको_idle(dmcub);
पूर्ण

अटल क्रमागत bp_result transmitter_control_v1_6(
	काष्ठा bios_parser *bp,
	काष्ठा bp_transmitter_control *cntl)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	स्थिर काष्ठा command_table_helper *cmd = bp->cmd_helper;
	काष्ठा dig_transmitter_control_ps_allocation_v1_6 ps = अणु अणु 0 पूर्ण पूर्ण;

	ps.param.phyid = cmd->phy_id_to_atom(cntl->transmitter);
	ps.param.action = (uपूर्णांक8_t)cntl->action;

	अगर (cntl->action == TRANSMITTER_CONTROL_SET_VOLTAGE_AND_PREEMPASIS)
		ps.param.mode_laneset.dplaneset = (uपूर्णांक8_t)cntl->lane_settings;
	अन्यथा
		ps.param.mode_laneset.digmode =
				cmd->संकेत_type_to_atom_dig_mode(cntl->संकेत);

	ps.param.lanक्रमागत = (uपूर्णांक8_t)cntl->lanes_number;
	ps.param.hpdsel = cmd->hpd_sel_to_atom(cntl->hpd_sel);
	ps.param.digfe_sel = cmd->dig_encoder_sel_to_atom(cntl->engine_id);
	ps.param.connobj_id = (uपूर्णांक8_t)cntl->connector_obj_id.id;
	ps.param.symclk_10khz = cntl->pixel_घड़ी/10;


	अगर (cntl->action == TRANSMITTER_CONTROL_ENABLE ||
		cntl->action == TRANSMITTER_CONTROL_ACTIAVATE ||
		cntl->action == TRANSMITTER_CONTROL_DEACTIVATE) अणु
		DC_LOG_BIOS("%s:ps.param.symclk_10khz = %d\n",\
		__func__, ps.param.symclk_10khz);
	पूर्ण

	अगर (bp->base.ctx->dc->ctx->dmub_srv &&
	    bp->base.ctx->dc->debug.dmub_command_table) अणु
		transmitter_control_dmcub(bp->base.ctx->dmub_srv, &ps.param);
		वापस BP_RESULT_OK;
	पूर्ण

/*color_depth not used any more, driver has deep color factor in the Phyclk*/
	अगर (EXEC_BIOS_CMD_TABLE(dig1transmittercontrol, ps))
		result = BP_RESULT_OK;
	वापस result;
पूर्ण

अटल व्योम transmitter_control_dmcub_v1_7(
		काष्ठा dc_dmub_srv *dmcub,
		काष्ठा dmub_dig_transmitter_control_data_v1_7 *dig)
अणु
	जोड़ dmub_rb_cmd cmd;

	स_रखो(&cmd, 0, माप(cmd));

	cmd.dig1_transmitter_control.header.type = DMUB_CMD__VBIOS;
	cmd.dig1_transmitter_control.header.sub_type =
		DMUB_CMD__VBIOS_DIG1_TRANSMITTER_CONTROL;
	cmd.dig1_transmitter_control.header.payload_bytes =
		माप(cmd.dig1_transmitter_control) -
		माप(cmd.dig1_transmitter_control.header);
	cmd.dig1_transmitter_control.transmitter_control.dig_v1_7 = *dig;

	dc_dmub_srv_cmd_queue(dmcub, &cmd);
	dc_dmub_srv_cmd_execute(dmcub);
	dc_dmub_srv_रुको_idle(dmcub);
पूर्ण

अटल क्रमागत bp_result transmitter_control_v1_7(
	काष्ठा bios_parser *bp,
	काष्ठा bp_transmitter_control *cntl)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	स्थिर काष्ठा command_table_helper *cmd = bp->cmd_helper;
	काष्ठा dmub_dig_transmitter_control_data_v1_7 dig_v1_7 = अणु0पूर्ण;

	dig_v1_7.phyid = cmd->phy_id_to_atom(cntl->transmitter);
	dig_v1_7.action = (uपूर्णांक8_t)cntl->action;

	अगर (cntl->action == TRANSMITTER_CONTROL_SET_VOLTAGE_AND_PREEMPASIS)
		dig_v1_7.mode_laneset.dplaneset = (uपूर्णांक8_t)cntl->lane_settings;
	अन्यथा
		dig_v1_7.mode_laneset.digmode =
				cmd->संकेत_type_to_atom_dig_mode(cntl->संकेत);

	dig_v1_7.lanक्रमागत = (uपूर्णांक8_t)cntl->lanes_number;
	dig_v1_7.hpdsel = cmd->hpd_sel_to_atom(cntl->hpd_sel);
	dig_v1_7.digfe_sel = cmd->dig_encoder_sel_to_atom(cntl->engine_id);
	dig_v1_7.connobj_id = (uपूर्णांक8_t)cntl->connector_obj_id.id;
	dig_v1_7.symclk_units.symclk_10khz = cntl->pixel_घड़ी/10;

	अगर (cntl->action == TRANSMITTER_CONTROL_ENABLE ||
		cntl->action == TRANSMITTER_CONTROL_ACTIAVATE ||
		cntl->action == TRANSMITTER_CONTROL_DEACTIVATE) अणु
			DC_LOG_BIOS("%s:dig_v1_7.symclk_units.symclk_10khz = %d\n",
			__func__, dig_v1_7.symclk_units.symclk_10khz);
	पूर्ण

	अगर (bp->base.ctx->dc->ctx->dmub_srv &&
		bp->base.ctx->dc->debug.dmub_command_table) अणु
		transmitter_control_dmcub_v1_7(bp->base.ctx->dmub_srv, &dig_v1_7);
		वापस BP_RESULT_OK;
	पूर्ण

/*color_depth not used any more, driver has deep color factor in the Phyclk*/
	अगर (EXEC_BIOS_CMD_TABLE(dig1transmittercontrol, dig_v1_7))
		result = BP_RESULT_OK;
	वापस result;
पूर्ण

अटल क्रमागत bp_result transmitter_control_fallback(
	काष्ठा bios_parser *bp,
	काष्ठा bp_transmitter_control *cntl)
अणु
	अगर (bp->base.ctx->dc->ctx->dmub_srv &&
	    bp->base.ctx->dc->debug.dmub_command_table) अणु
		वापस transmitter_control_v1_7(bp, cntl);
	पूर्ण

	वापस BP_RESULT_FAILURE;
पूर्ण

/******************************************************************************
 ******************************************************************************
 **
 **                  SET PIXEL CLOCK
 **
 ******************************************************************************
 *****************************************************************************/

अटल क्रमागत bp_result set_pixel_घड़ी_v7(
	काष्ठा bios_parser *bp,
	काष्ठा bp_pixel_घड़ी_parameters *bp_params);

अटल क्रमागत bp_result set_pixel_घड़ी_fallback(
	काष्ठा bios_parser *bp,
	काष्ठा bp_pixel_घड़ी_parameters *bp_params);

अटल व्योम init_set_pixel_घड़ी(काष्ठा bios_parser *bp)
अणु
	चयन (BIOS_CMD_TABLE_PARA_REVISION(setpixelघड़ी)) अणु
	हाल 7:
		bp->cmd_tbl.set_pixel_घड़ी = set_pixel_घड़ी_v7;
		अवरोध;
	शेष:
		dm_output_to_console("Don't have set_pixel_clock for v%d\n",
			 BIOS_CMD_TABLE_PARA_REVISION(setpixelघड़ी));
		bp->cmd_tbl.set_pixel_घड़ी = set_pixel_घड़ी_fallback;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम set_pixel_घड़ी_dmcub(
		काष्ठा dc_dmub_srv *dmcub,
		काष्ठा set_pixel_घड़ी_parameter_v1_7 *clk)
अणु
	जोड़ dmub_rb_cmd cmd;

	स_रखो(&cmd, 0, माप(cmd));

	cmd.set_pixel_घड़ी.header.type = DMUB_CMD__VBIOS;
	cmd.set_pixel_घड़ी.header.sub_type = DMUB_CMD__VBIOS_SET_PIXEL_CLOCK;
	cmd.set_pixel_घड़ी.header.payload_bytes =
		माप(cmd.set_pixel_घड़ी) -
		माप(cmd.set_pixel_घड़ी.header);
	cmd.set_pixel_घड़ी.pixel_घड़ी.clk = *clk;

	dc_dmub_srv_cmd_queue(dmcub, &cmd);
	dc_dmub_srv_cmd_execute(dmcub);
	dc_dmub_srv_रुको_idle(dmcub);
पूर्ण

अटल क्रमागत bp_result set_pixel_घड़ी_v7(
	काष्ठा bios_parser *bp,
	काष्ठा bp_pixel_घड़ी_parameters *bp_params)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	काष्ठा set_pixel_घड़ी_parameter_v1_7 clk;
	uपूर्णांक8_t controller_id;
	uपूर्णांक32_t pll_id;

	स_रखो(&clk, 0, माप(clk));

	अगर (bp->cmd_helper->घड़ी_source_id_to_atom(bp_params->pll_id, &pll_id)
			&& bp->cmd_helper->controller_id_to_atom(bp_params->
					controller_id, &controller_id)) अणु
		/* Note: VBIOS still wants to use ucCRTC name which is now
		 * 1 byte in ULONG
		 *प्रकार काष्ठा _CRTC_PIXEL_CLOCK_FREQ
		 *अणु
		 * target the pixel घड़ी to drive the CRTC timing.
		 * ULONG ulPixelClock:24;
		 * 0 means disable PPLL/DCPLL. Expanded to 24 bits comparing to
		 * previous version.
		 * ATOM_CRTC1~6, indicate the CRTC controller to
		 * ULONG ucCRTC:8;
		 * drive the pixel घड़ी. not used क्रम DCPLL हाल.
		 *पूर्णCRTC_PIXEL_CLOCK_FREQ;
		 *जोड़
		 *अणु
		 * pixel घड़ी and CRTC id frequency
		 * CRTC_PIXEL_CLOCK_FREQ ulCrtcPclkFreq;
		 * ULONG ulDispEngClkFreq; dispclk frequency
		 *पूर्ण;
		 */
		clk.crtc_id = controller_id;
		clk.pll_id = (uपूर्णांक8_t) pll_id;
		clk.encoderobjid =
			bp->cmd_helper->encoder_id_to_atom(
				dal_graphics_object_id_get_encoder_id(
					bp_params->encoder_object_id));

		clk.encoder_mode = (uपूर्णांक8_t) bp->
			cmd_helper->encoder_mode_bp_to_atom(
				bp_params->संकेत_type, false);

		clk.pixclk_100hz = cpu_to_le32(bp_params->target_pixel_घड़ी_100hz);

		clk.deep_color_ratio =
			(uपूर्णांक8_t) bp->cmd_helper->
				transmitter_color_depth_to_atom(
					bp_params->color_depth);

		DC_LOG_BIOS("%s:program display clock = %d, tg = %d, pll = %d, "\
				"colorDepth = %d\n", __func__,
				bp_params->target_pixel_घड़ी_100hz, (पूर्णांक)controller_id,
				pll_id, bp_params->color_depth);

		अगर (bp_params->flags.FORCE_PROGRAMMING_OF_PLL)
			clk.miscinfo |= PIXEL_CLOCK_V7_MISC_FORCE_PROG_PPLL;

		अगर (bp_params->flags.PROGRAM_PHY_PLL_ONLY)
			clk.miscinfo |= PIXEL_CLOCK_V7_MISC_PROG_PHYPLL;

		अगर (bp_params->flags.SUPPORT_YUV_420)
			clk.miscinfo |= PIXEL_CLOCK_V7_MISC_YUV420_MODE;

		अगर (bp_params->flags.SET_XTALIN_REF_SRC)
			clk.miscinfo |= PIXEL_CLOCK_V7_MISC_REF_DIV_SRC_XTALIN;

		अगर (bp_params->flags.SET_GENLOCK_REF_DIV_SRC)
			clk.miscinfo |= PIXEL_CLOCK_V7_MISC_REF_DIV_SRC_GENLK;

		अगर (bp_params->संकेत_type == SIGNAL_TYPE_DVI_DUAL_LINK)
			clk.miscinfo |= PIXEL_CLOCK_V7_MISC_DVI_DUALLINK_EN;

		अगर (bp->base.ctx->dc->ctx->dmub_srv &&
		    bp->base.ctx->dc->debug.dmub_command_table) अणु
			set_pixel_घड़ी_dmcub(bp->base.ctx->dmub_srv, &clk);
			वापस BP_RESULT_OK;
		पूर्ण

		अगर (EXEC_BIOS_CMD_TABLE(setpixelघड़ी, clk))
			result = BP_RESULT_OK;
	पूर्ण
	वापस result;
पूर्ण

अटल क्रमागत bp_result set_pixel_घड़ी_fallback(
	काष्ठा bios_parser *bp,
	काष्ठा bp_pixel_घड़ी_parameters *bp_params)
अणु
	अगर (bp->base.ctx->dc->ctx->dmub_srv &&
	    bp->base.ctx->dc->debug.dmub_command_table) अणु
		वापस set_pixel_घड़ी_v7(bp, bp_params);
	पूर्ण

	वापस BP_RESULT_FAILURE;
पूर्ण

/******************************************************************************
 ******************************************************************************
 **
 **                  SET CRTC TIMING
 **
 ******************************************************************************
 *****************************************************************************/

अटल क्रमागत bp_result set_crtc_using_dtd_timing_v3(
	काष्ठा bios_parser *bp,
	काष्ठा bp_hw_crtc_timing_parameters *bp_params);

अटल व्योम init_set_crtc_timing(काष्ठा bios_parser *bp)
अणु
	uपूर्णांक32_t dtd_version =
			BIOS_CMD_TABLE_PARA_REVISION(setcrtc_usingdtdtiming);

	चयन (dtd_version) अणु
	हाल 3:
		bp->cmd_tbl.set_crtc_timing =
			set_crtc_using_dtd_timing_v3;
		अवरोध;
	शेष:
		dm_output_to_console("Don't have set_crtc_timing for v%d\n", dtd_version);
		bp->cmd_tbl.set_crtc_timing = शून्य;
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत bp_result set_crtc_using_dtd_timing_v3(
	काष्ठा bios_parser *bp,
	काष्ठा bp_hw_crtc_timing_parameters *bp_params)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	काष्ठा set_crtc_using_dtd_timing_parameters params = अणु0पूर्ण;
	uपूर्णांक8_t atom_controller_id;

	अगर (bp->cmd_helper->controller_id_to_atom(
			bp_params->controller_id, &atom_controller_id))
		params.crtc_id = atom_controller_id;

	/* bios usH_Size wants h addressable size */
	params.h_size = cpu_to_le16((uपूर्णांक16_t)bp_params->h_addressable);
	/* bios usH_Blanking_Time wants borders included in blanking */
	params.h_blanking_समय =
			cpu_to_le16((uपूर्णांक16_t)(bp_params->h_total -
					bp_params->h_addressable));
	/* bios usV_Size wants v addressable size */
	params.v_size = cpu_to_le16((uपूर्णांक16_t)bp_params->v_addressable);
	/* bios usV_Blanking_Time wants borders included in blanking */
	params.v_blanking_समय =
			cpu_to_le16((uपूर्णांक16_t)(bp_params->v_total -
					bp_params->v_addressable));
	/* bios usHSyncOffset is the offset from the end of h addressable,
	 * our horizontalSyncStart is the offset from the beginning
	 * of h addressable
	 */
	params.h_syncoffset =
			cpu_to_le16((uपूर्णांक16_t)(bp_params->h_sync_start -
					bp_params->h_addressable));
	params.h_syncwidth = cpu_to_le16((uपूर्णांक16_t)bp_params->h_sync_width);
	/* bios usHSyncOffset is the offset from the end of v addressable,
	 * our verticalSyncStart is the offset from the beginning of
	 * v addressable
	 */
	params.v_syncoffset =
			cpu_to_le16((uपूर्णांक16_t)(bp_params->v_sync_start -
					bp_params->v_addressable));
	params.v_syncwidth = cpu_to_le16((uपूर्णांक16_t)bp_params->v_sync_width);

	/* we assume that overscan from original timing करोes not get bigger
	 * than 255
	 * we will program all the borders in the Set CRTC Overscan call below
	 */

	अगर (bp_params->flags.HSYNC_POSITIVE_POLARITY == 0)
		params.modemiscinfo =
				cpu_to_le16(le16_to_cpu(params.modemiscinfo) |
						ATOM_HSYNC_POLARITY);

	अगर (bp_params->flags.VSYNC_POSITIVE_POLARITY == 0)
		params.modemiscinfo =
				cpu_to_le16(le16_to_cpu(params.modemiscinfo) |
						ATOM_VSYNC_POLARITY);

	अगर (bp_params->flags.INTERLACE)	अणु
		params.modemiscinfo =
				cpu_to_le16(le16_to_cpu(params.modemiscinfo) |
						ATOM_INTERLACE);

		/* original DAL code has this condition to apply this
		 * क्रम non-TV/CV only
		 * due to complex MV testing क्रम possible impact
		 * अगर ( pACParameters->संकेत != SignalType_YPbPr &&
		 *  pACParameters->संकेत != SignalType_Composite &&
		 *  pACParameters->संकेत != SignalType_SVideo)
		 */
		अणु
			/* HW will deduct 0.5 line from 2nd feild.
			 * i.e. क्रम 1080i, it is 2 lines क्रम 1st field,
			 * 2.5 lines क्रम the 2nd feild. we need input as 5
			 * instead of 4.
			 * but it is 4 either from Edid data (spec CEA 861)
			 * or CEA timing table.
			 */
			le16_add_cpu(&params.v_syncoffset, 1);
		पूर्ण
	पूर्ण

	अगर (bp_params->flags.HORZ_COUNT_BY_TWO)
		params.modemiscinfo =
			cpu_to_le16(le16_to_cpu(params.modemiscinfo) |
					0x100); /* ATOM_DOUBLE_CLOCK_MODE */

	अगर (EXEC_BIOS_CMD_TABLE(setcrtc_usingdtdtiming, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

/******************************************************************************
 ******************************************************************************
 **
 **                  ENABLE CRTC
 **
 ******************************************************************************
 *****************************************************************************/

अटल क्रमागत bp_result enable_crtc_v1(
	काष्ठा bios_parser *bp,
	क्रमागत controller_id controller_id,
	bool enable);

अटल व्योम init_enable_crtc(काष्ठा bios_parser *bp)
अणु
	चयन (BIOS_CMD_TABLE_PARA_REVISION(enablecrtc)) अणु
	हाल 1:
		bp->cmd_tbl.enable_crtc = enable_crtc_v1;
		अवरोध;
	शेष:
		dm_output_to_console("Don't have enable_crtc for v%d\n",
			 BIOS_CMD_TABLE_PARA_REVISION(enablecrtc));
		bp->cmd_tbl.enable_crtc = शून्य;
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत bp_result enable_crtc_v1(
	काष्ठा bios_parser *bp,
	क्रमागत controller_id controller_id,
	bool enable)
अणु
	bool result = BP_RESULT_FAILURE;
	काष्ठा enable_crtc_parameters params = अणु0पूर्ण;
	uपूर्णांक8_t id;

	अगर (bp->cmd_helper->controller_id_to_atom(controller_id, &id))
		params.crtc_id = id;
	अन्यथा
		वापस BP_RESULT_BADINPUT;

	अगर (enable)
		params.enable = ATOM_ENABLE;
	अन्यथा
		params.enable = ATOM_DISABLE;

	अगर (EXEC_BIOS_CMD_TABLE(enablecrtc, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

/******************************************************************************
 ******************************************************************************
 **
 **                  DISPLAY PLL
 **
 ******************************************************************************
 *****************************************************************************/



/******************************************************************************
 ******************************************************************************
 **
 **                  EXTERNAL ENCODER CONTROL
 **
 ******************************************************************************
 *****************************************************************************/

अटल क्रमागत bp_result बाह्यal_encoder_control_v3(
	काष्ठा bios_parser *bp,
	काष्ठा bp_बाह्यal_encoder_control *cntl);

अटल व्योम init_बाह्यal_encoder_control(
	काष्ठा bios_parser *bp)
अणु
	चयन (BIOS_CMD_TABLE_PARA_REVISION(बाह्यalencodercontrol)) अणु
	हाल 3:
		bp->cmd_tbl.बाह्यal_encoder_control =
				बाह्यal_encoder_control_v3;
		अवरोध;
	शेष:
		bp->cmd_tbl.बाह्यal_encoder_control = शून्य;
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत bp_result बाह्यal_encoder_control_v3(
	काष्ठा bios_parser *bp,
	काष्ठा bp_बाह्यal_encoder_control *cntl)
अणु
	/* TODO */
	वापस BP_RESULT_OK;
पूर्ण

/******************************************************************************
 ******************************************************************************
 **
 **                  ENABLE DISPLAY POWER GATING
 **
 ******************************************************************************
 *****************************************************************************/

अटल क्रमागत bp_result enable_disp_घातer_gating_v2_1(
	काष्ठा bios_parser *bp,
	क्रमागत controller_id crtc_id,
	क्रमागत bp_pipe_control_action action);

अटल क्रमागत bp_result enable_disp_घातer_gating_fallback(
	काष्ठा bios_parser *bp,
	क्रमागत controller_id crtc_id,
	क्रमागत bp_pipe_control_action action);

अटल व्योम init_enable_disp_घातer_gating(
	काष्ठा bios_parser *bp)
अणु
	चयन (BIOS_CMD_TABLE_PARA_REVISION(enabledispघातergating)) अणु
	हाल 1:
		bp->cmd_tbl.enable_disp_घातer_gating =
				enable_disp_घातer_gating_v2_1;
		अवरोध;
	शेष:
		dm_output_to_console("Don't enable_disp_power_gating enable_crtc for v%d\n",
			 BIOS_CMD_TABLE_PARA_REVISION(enabledispघातergating));
		bp->cmd_tbl.enable_disp_घातer_gating = enable_disp_घातer_gating_fallback;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम enable_disp_घातer_gating_dmcub(
	काष्ठा dc_dmub_srv *dmcub,
	काष्ठा enable_disp_घातer_gating_parameters_v2_1 *pwr)
अणु
	जोड़ dmub_rb_cmd cmd;

	स_रखो(&cmd, 0, माप(cmd));

	cmd.enable_disp_घातer_gating.header.type = DMUB_CMD__VBIOS;
	cmd.enable_disp_घातer_gating.header.sub_type =
		DMUB_CMD__VBIOS_ENABLE_DISP_POWER_GATING;
	cmd.enable_disp_घातer_gating.header.payload_bytes =
		माप(cmd.enable_disp_घातer_gating) -
		माप(cmd.enable_disp_घातer_gating.header);
	cmd.enable_disp_घातer_gating.घातer_gating.pwr = *pwr;

	dc_dmub_srv_cmd_queue(dmcub, &cmd);
	dc_dmub_srv_cmd_execute(dmcub);
	dc_dmub_srv_रुको_idle(dmcub);
पूर्ण

अटल क्रमागत bp_result enable_disp_घातer_gating_v2_1(
	काष्ठा bios_parser *bp,
	क्रमागत controller_id crtc_id,
	क्रमागत bp_pipe_control_action action)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;


	काष्ठा enable_disp_घातer_gating_ps_allocation ps = अणु अणु 0 पूर्ण पूर्ण;
	uपूर्णांक8_t atom_crtc_id;

	अगर (bp->cmd_helper->controller_id_to_atom(crtc_id, &atom_crtc_id))
		ps.param.disp_pipe_id = atom_crtc_id;
	अन्यथा
		वापस BP_RESULT_BADINPUT;

	ps.param.enable =
		bp->cmd_helper->disp_घातer_gating_action_to_atom(action);

	अगर (bp->base.ctx->dc->ctx->dmub_srv &&
	    bp->base.ctx->dc->debug.dmub_command_table) अणु
		enable_disp_घातer_gating_dmcub(bp->base.ctx->dmub_srv,
					       &ps.param);
		वापस BP_RESULT_OK;
	पूर्ण

	अगर (EXEC_BIOS_CMD_TABLE(enabledispघातergating, ps.param))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

अटल क्रमागत bp_result enable_disp_घातer_gating_fallback(
	काष्ठा bios_parser *bp,
	क्रमागत controller_id crtc_id,
	क्रमागत bp_pipe_control_action action)
अणु
	अगर (bp->base.ctx->dc->ctx->dmub_srv &&
	    bp->base.ctx->dc->debug.dmub_command_table) अणु
		वापस enable_disp_घातer_gating_v2_1(bp, crtc_id, action);
	पूर्ण

	वापस BP_RESULT_FAILURE;
पूर्ण

/******************************************************************************
*******************************************************************************
 **
 **                  SET DCE CLOCK
 **
*******************************************************************************
*******************************************************************************/

अटल क्रमागत bp_result set_dce_घड़ी_v2_1(
	काष्ठा bios_parser *bp,
	काष्ठा bp_set_dce_घड़ी_parameters *bp_params);

अटल व्योम init_set_dce_घड़ी(काष्ठा bios_parser *bp)
अणु
	चयन (BIOS_CMD_TABLE_PARA_REVISION(setdceघड़ी)) अणु
	हाल 1:
		bp->cmd_tbl.set_dce_घड़ी = set_dce_घड़ी_v2_1;
		अवरोध;
	शेष:
		dm_output_to_console("Don't have set_dce_clock for v%d\n",
			 BIOS_CMD_TABLE_PARA_REVISION(setdceघड़ी));
		bp->cmd_tbl.set_dce_घड़ी = शून्य;
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत bp_result set_dce_घड़ी_v2_1(
	काष्ठा bios_parser *bp,
	काष्ठा bp_set_dce_घड़ी_parameters *bp_params)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;

	काष्ठा set_dce_घड़ी_ps_allocation_v2_1 params;
	uपूर्णांक32_t atom_pll_id;
	uपूर्णांक32_t atom_घड़ी_प्रकारype;
	स्थिर काष्ठा command_table_helper *cmd = bp->cmd_helper;

	स_रखो(&params, 0, माप(params));

	अगर (!cmd->घड़ी_source_id_to_atom(bp_params->pll_id, &atom_pll_id) ||
			!cmd->dc_घड़ी_प्रकारype_to_atom(bp_params->घड़ी_प्रकारype,
					&atom_घड़ी_प्रकारype))
		वापस BP_RESULT_BADINPUT;

	params.param.dceclksrc  = atom_pll_id;
	params.param.dceclktype = atom_घड़ी_प्रकारype;

	अगर (bp_params->घड़ी_प्रकारype == DCECLOCK_TYPE_DPREFCLK) अणु
		अगर (bp_params->flags.USE_GENLOCK_AS_SOURCE_FOR_DPREFCLK)
			params.param.dceclkflag |=
					DCE_CLOCK_FLAG_PLL_REFCLK_SRC_GENLK;

		अगर (bp_params->flags.USE_PCIE_AS_SOURCE_FOR_DPREFCLK)
			params.param.dceclkflag |=
					DCE_CLOCK_FLAG_PLL_REFCLK_SRC_PCIE;

		अगर (bp_params->flags.USE_XTALIN_AS_SOURCE_FOR_DPREFCLK)
			params.param.dceclkflag |=
					DCE_CLOCK_FLAG_PLL_REFCLK_SRC_XTALIN;

		अगर (bp_params->flags.USE_GENERICA_AS_SOURCE_FOR_DPREFCLK)
			params.param.dceclkflag |=
					DCE_CLOCK_FLAG_PLL_REFCLK_SRC_GENERICA;
	पूर्ण अन्यथा
		/* only program घड़ी frequency अगर display घड़ी is used;
		 * VBIOS will program DPREFCLK
		 * We need to convert from KHz units पूर्णांकo 10KHz units
		 */
		params.param.dceclk_10khz = cpu_to_le32(
				bp_params->target_घड़ी_frequency / 10);
	DC_LOG_BIOS("%s:target_clock_frequency = %d"\
			"clock_type = %d \n", __func__,\
			bp_params->target_घड़ी_frequency,\
			bp_params->घड़ी_प्रकारype);

	अगर (EXEC_BIOS_CMD_TABLE(setdceघड़ी, params)) अणु
		/* Convert from 10KHz units back to KHz */
		bp_params->target_घड़ी_frequency = le32_to_cpu(
				params.param.dceclk_10khz) * 10;
		result = BP_RESULT_OK;
	पूर्ण

	वापस result;
पूर्ण


/******************************************************************************
 ******************************************************************************
 **
 **                  GET SMU CLOCK INFO
 **
 ******************************************************************************
 *****************************************************************************/

अटल अचिन्हित पूर्णांक get_smu_घड़ी_info_v3_1(काष्ठा bios_parser *bp, uपूर्णांक8_t id);

अटल व्योम init_get_smu_घड़ी_info(काष्ठा bios_parser *bp)
अणु
	/* TODO add चयन क्रम table vrsion */
	bp->cmd_tbl.get_smu_घड़ी_info = get_smu_घड़ी_info_v3_1;

पूर्ण

अटल अचिन्हित पूर्णांक get_smu_घड़ी_info_v3_1(काष्ठा bios_parser *bp, uपूर्णांक8_t id)
अणु
	काष्ठा atom_get_smu_घड़ी_info_parameters_v3_1 smu_input = अणु0पूर्ण;
	काष्ठा atom_get_smu_घड़ी_info_output_parameters_v3_1 smu_output;

	smu_input.command = GET_SMU_CLOCK_INFO_V3_1_GET_PLLVCO_FREQ;
	smu_input.syspll_id = id;

	/* Get Specअगरic Clock */
	अगर (EXEC_BIOS_CMD_TABLE(माला_लोmuघड़ीinfo, smu_input)) अणु
		स_हटाओ(&smu_output, &smu_input, माप(
			काष्ठा atom_get_smu_घड़ी_info_parameters_v3_1));
		वापस smu_output.atom_smu_outअ_दोlkfreq.syspllvcofreq_10khz;
	पूर्ण

	वापस 0;
पूर्ण

/******************************************************************************
 ******************************************************************************
 **
 **                  LVTMA CONTROL
 **
 ******************************************************************************
 *****************************************************************************/

अटल क्रमागत bp_result enable_lvपंचांगa_control(
	काष्ठा bios_parser *bp,
	uपूर्णांक8_t uc_pwr_on,
	uपूर्णांक8_t panel_instance);

अटल व्योम init_enable_lvपंचांगa_control(काष्ठा bios_parser *bp)
अणु
	/* TODO add चयन क्रम table vrsion */
	bp->cmd_tbl.enable_lvपंचांगa_control = enable_lvपंचांगa_control;

पूर्ण

अटल व्योम enable_lvपंचांगa_control_dmcub(
	काष्ठा dc_dmub_srv *dmcub,
	uपूर्णांक8_t uc_pwr_on,
	uपूर्णांक8_t panel_instance)
अणु

	जोड़ dmub_rb_cmd cmd;

	स_रखो(&cmd, 0, माप(cmd));

	cmd.lvपंचांगa_control.header.type = DMUB_CMD__VBIOS;
	cmd.lvपंचांगa_control.header.sub_type =
			DMUB_CMD__VBIOS_LVTMA_CONTROL;
	cmd.lvपंचांगa_control.data.uc_pwr_action =
			uc_pwr_on;
	cmd.lvपंचांगa_control.data.panel_inst =
			panel_instance;
	dc_dmub_srv_cmd_queue(dmcub, &cmd);
	dc_dmub_srv_cmd_execute(dmcub);
	dc_dmub_srv_रुको_idle(dmcub);

पूर्ण

अटल क्रमागत bp_result enable_lvपंचांगa_control(
	काष्ठा bios_parser *bp,
	uपूर्णांक8_t uc_pwr_on,
	uपूर्णांक8_t panel_instance)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;

	अगर (bp->base.ctx->dc->ctx->dmub_srv &&
	    bp->base.ctx->dc->debug.dmub_command_table) अणु
		enable_lvपंचांगa_control_dmcub(bp->base.ctx->dmub_srv,
				uc_pwr_on,
				panel_instance);
		वापस BP_RESULT_OK;
	पूर्ण
	वापस result;
पूर्ण

व्योम dal_firmware_parser_init_cmd_tbl(काष्ठा bios_parser *bp)
अणु
	init_dig_encoder_control(bp);
	init_transmitter_control(bp);
	init_set_pixel_घड़ी(bp);

	init_set_crtc_timing(bp);

	init_enable_crtc(bp);

	init_बाह्यal_encoder_control(bp);
	init_enable_disp_घातer_gating(bp);
	init_set_dce_घड़ी(bp);
	init_get_smu_घड़ी_info(bp);

	init_enable_lvपंचांगa_control(bp);
पूर्ण
