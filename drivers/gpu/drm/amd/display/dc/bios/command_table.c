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
#समावेश "amdgpu.h"
#समावेश "atom.h"

#समावेश "include/bios_parser_interface.h"

#समावेश "command_table.h"
#समावेश "command_table_helper.h"
#समावेश "bios_parser_helper.h"
#समावेश "bios_parser_types_internal.h"

#घोषणा EXEC_BIOS_CMD_TABLE(command, params)\
	(amdgpu_atom_execute_table(((काष्ठा amdgpu_device *)bp->base.ctx->driver_context)->mode_info.atom_context, \
		GetIndexIntoMasterTable(COMMAND, command), \
		(uपूर्णांक32_t *)&params) == 0)

#घोषणा BIOS_CMD_TABLE_REVISION(command, frev, crev)\
	amdgpu_atom_parse_cmd_header(((काष्ठा amdgpu_device *)bp->base.ctx->driver_context)->mode_info.atom_context, \
		GetIndexIntoMasterTable(COMMAND, command), &frev, &crev)

#घोषणा BIOS_CMD_TABLE_PARA_REVISION(command)\
	bios_cmd_table_para_revision(bp->base.ctx->driver_context, \
		GetIndexIntoMasterTable(COMMAND, command))

अटल व्योम init_dig_encoder_control(काष्ठा bios_parser *bp);
अटल व्योम init_transmitter_control(काष्ठा bios_parser *bp);
अटल व्योम init_set_pixel_घड़ी(काष्ठा bios_parser *bp);
अटल व्योम init_enable_spपढ़ो_spectrum_on_ppll(काष्ठा bios_parser *bp);
अटल व्योम init_adjust_display_pll(काष्ठा bios_parser *bp);
अटल व्योम init_dac_encoder_control(काष्ठा bios_parser *bp);
अटल व्योम init_dac_output_control(काष्ठा bios_parser *bp);
अटल व्योम init_set_crtc_timing(काष्ठा bios_parser *bp);
अटल व्योम init_enable_crtc(काष्ठा bios_parser *bp);
अटल व्योम init_enable_crtc_mem_req(काष्ठा bios_parser *bp);
अटल व्योम init_बाह्यal_encoder_control(काष्ठा bios_parser *bp);
अटल व्योम init_enable_disp_घातer_gating(काष्ठा bios_parser *bp);
अटल व्योम init_program_घड़ी(काष्ठा bios_parser *bp);
अटल व्योम init_set_dce_घड़ी(काष्ठा bios_parser *bp);

व्योम dal_bios_parser_init_cmd_tbl(काष्ठा bios_parser *bp)
अणु
	init_dig_encoder_control(bp);
	init_transmitter_control(bp);
	init_set_pixel_घड़ी(bp);
	init_enable_spपढ़ो_spectrum_on_ppll(bp);
	init_adjust_display_pll(bp);
	init_dac_encoder_control(bp);
	init_dac_output_control(bp);
	init_set_crtc_timing(bp);
	init_enable_crtc(bp);
	init_enable_crtc_mem_req(bp);
	init_program_घड़ी(bp);
	init_बाह्यal_encoder_control(bp);
	init_enable_disp_घातer_gating(bp);
	init_set_dce_घड़ी(bp);
पूर्ण

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

/*******************************************************************************
 ********************************************************************************
 **
 **                  D I G E N C O D E R C O N T R O L
 **
 ********************************************************************************
 *******************************************************************************/
अटल क्रमागत bp_result encoder_control_digx_v3(
	काष्ठा bios_parser *bp,
	काष्ठा bp_encoder_control *cntl);

अटल क्रमागत bp_result encoder_control_digx_v4(
	काष्ठा bios_parser *bp,
	काष्ठा bp_encoder_control *cntl);

अटल क्रमागत bp_result encoder_control_digx_v5(
	काष्ठा bios_parser *bp,
	काष्ठा bp_encoder_control *cntl);

अटल व्योम init_encoder_control_dig_v1(काष्ठा bios_parser *bp);

अटल व्योम init_dig_encoder_control(काष्ठा bios_parser *bp)
अणु
	uपूर्णांक32_t version =
		BIOS_CMD_TABLE_PARA_REVISION(DIGxEncoderControl);

	चयन (version) अणु
	हाल 2:
		bp->cmd_tbl.dig_encoder_control = encoder_control_digx_v3;
		अवरोध;
	हाल 4:
		bp->cmd_tbl.dig_encoder_control = encoder_control_digx_v4;
		अवरोध;

	हाल 5:
		bp->cmd_tbl.dig_encoder_control = encoder_control_digx_v5;
		अवरोध;

	शेष:
		init_encoder_control_dig_v1(bp);
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत bp_result encoder_control_dig_v1(
	काष्ठा bios_parser *bp,
	काष्ठा bp_encoder_control *cntl);
अटल क्रमागत bp_result encoder_control_dig1_v1(
	काष्ठा bios_parser *bp,
	काष्ठा bp_encoder_control *cntl);
अटल क्रमागत bp_result encoder_control_dig2_v1(
	काष्ठा bios_parser *bp,
	काष्ठा bp_encoder_control *cntl);

अटल व्योम init_encoder_control_dig_v1(काष्ठा bios_parser *bp)
अणु
	काष्ठा cmd_tbl *cmd_tbl = &bp->cmd_tbl;

	अगर (1 == BIOS_CMD_TABLE_PARA_REVISION(DIG1EncoderControl))
		cmd_tbl->encoder_control_dig1 = encoder_control_dig1_v1;
	अन्यथा
		cmd_tbl->encoder_control_dig1 = शून्य;

	अगर (1 == BIOS_CMD_TABLE_PARA_REVISION(DIG2EncoderControl))
		cmd_tbl->encoder_control_dig2 = encoder_control_dig2_v1;
	अन्यथा
		cmd_tbl->encoder_control_dig2 = शून्य;

	cmd_tbl->dig_encoder_control = encoder_control_dig_v1;
पूर्ण

अटल क्रमागत bp_result encoder_control_dig_v1(
	काष्ठा bios_parser *bp,
	काष्ठा bp_encoder_control *cntl)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	काष्ठा cmd_tbl *cmd_tbl = &bp->cmd_tbl;

	अगर (cntl != शून्य)
		चयन (cntl->engine_id) अणु
		हाल ENGINE_ID_DIGA:
			अगर (cmd_tbl->encoder_control_dig1 != शून्य)
				result =
					cmd_tbl->encoder_control_dig1(bp, cntl);
			अवरोध;
		हाल ENGINE_ID_DIGB:
			अगर (cmd_tbl->encoder_control_dig2 != शून्य)
				result =
					cmd_tbl->encoder_control_dig2(bp, cntl);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

	वापस result;
पूर्ण

अटल क्रमागत bp_result encoder_control_dig1_v1(
	काष्ठा bios_parser *bp,
	काष्ठा bp_encoder_control *cntl)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	DIG_ENCODER_CONTROL_PARAMETERS_V2 params = अणु0पूर्ण;

	bp->cmd_helper->assign_control_parameter(bp->cmd_helper, cntl, &params);

	अगर (EXEC_BIOS_CMD_TABLE(DIG1EncoderControl, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

अटल क्रमागत bp_result encoder_control_dig2_v1(
	काष्ठा bios_parser *bp,
	काष्ठा bp_encoder_control *cntl)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	DIG_ENCODER_CONTROL_PARAMETERS_V2 params = अणु0पूर्ण;

	bp->cmd_helper->assign_control_parameter(bp->cmd_helper, cntl, &params);

	अगर (EXEC_BIOS_CMD_TABLE(DIG2EncoderControl, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

अटल क्रमागत bp_result encoder_control_digx_v3(
	काष्ठा bios_parser *bp,
	काष्ठा bp_encoder_control *cntl)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	DIG_ENCODER_CONTROL_PARAMETERS_V3 params = अणु0पूर्ण;

	अगर (LANE_COUNT_FOUR < cntl->lanes_number)
		params.acConfig.ucDPLinkRate = 1; /* dual link 2.7GHz */
	अन्यथा
		params.acConfig.ucDPLinkRate = 0; /* single link 1.62GHz */

	params.acConfig.ucDigSel = (uपूर्णांक8_t)(cntl->engine_id);

	/* We need to convert from KHz units पूर्णांकo 10KHz units */
	params.ucAction = bp->cmd_helper->encoder_action_to_atom(cntl->action);
	params.usPixelClock = cpu_to_le16((uपूर्णांक16_t)(cntl->pixel_घड़ी / 10));
	params.ucEncoderMode =
			(uपूर्णांक8_t)bp->cmd_helper->encoder_mode_bp_to_atom(
					cntl->संकेत,
					cntl->enable_dp_audio);
	params.ucLaneNum = (uपूर्णांक8_t)(cntl->lanes_number);

	चयन (cntl->color_depth) अणु
	हाल COLOR_DEPTH_888:
		params.ucBitPerColor = PANEL_8BIT_PER_COLOR;
		अवरोध;
	हाल COLOR_DEPTH_101010:
		params.ucBitPerColor = PANEL_10BIT_PER_COLOR;
		अवरोध;
	हाल COLOR_DEPTH_121212:
		params.ucBitPerColor = PANEL_12BIT_PER_COLOR;
		अवरोध;
	हाल COLOR_DEPTH_161616:
		params.ucBitPerColor = PANEL_16BIT_PER_COLOR;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (EXEC_BIOS_CMD_TABLE(DIGxEncoderControl, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

अटल क्रमागत bp_result encoder_control_digx_v4(
	काष्ठा bios_parser *bp,
	काष्ठा bp_encoder_control *cntl)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	DIG_ENCODER_CONTROL_PARAMETERS_V4 params = अणु0पूर्ण;

	अगर (LANE_COUNT_FOUR < cntl->lanes_number)
		params.acConfig.ucDPLinkRate = 1; /* dual link 2.7GHz */
	अन्यथा
		params.acConfig.ucDPLinkRate = 0; /* single link 1.62GHz */

	params.acConfig.ucDigSel = (uपूर्णांक8_t)(cntl->engine_id);

	/* We need to convert from KHz units पूर्णांकo 10KHz units */
	params.ucAction = bp->cmd_helper->encoder_action_to_atom(cntl->action);
	params.usPixelClock = cpu_to_le16((uपूर्णांक16_t)(cntl->pixel_घड़ी / 10));
	params.ucEncoderMode =
			(uपूर्णांक8_t)(bp->cmd_helper->encoder_mode_bp_to_atom(
					cntl->संकेत,
					cntl->enable_dp_audio));
	params.ucLaneNum = (uपूर्णांक8_t)(cntl->lanes_number);

	चयन (cntl->color_depth) अणु
	हाल COLOR_DEPTH_888:
		params.ucBitPerColor = PANEL_8BIT_PER_COLOR;
		अवरोध;
	हाल COLOR_DEPTH_101010:
		params.ucBitPerColor = PANEL_10BIT_PER_COLOR;
		अवरोध;
	हाल COLOR_DEPTH_121212:
		params.ucBitPerColor = PANEL_12BIT_PER_COLOR;
		अवरोध;
	हाल COLOR_DEPTH_161616:
		params.ucBitPerColor = PANEL_16BIT_PER_COLOR;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (EXEC_BIOS_CMD_TABLE(DIGxEncoderControl, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

अटल क्रमागत bp_result encoder_control_digx_v5(
	काष्ठा bios_parser *bp,
	काष्ठा bp_encoder_control *cntl)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	ENCODER_STREAM_SETUP_PARAMETERS_V5 params = अणु0पूर्ण;

	params.ucDigId = (uपूर्णांक8_t)(cntl->engine_id);
	params.ucAction = bp->cmd_helper->encoder_action_to_atom(cntl->action);

	params.ulPixelClock = cntl->pixel_घड़ी / 10;
	params.ucDigMode =
			(uपूर्णांक8_t)(bp->cmd_helper->encoder_mode_bp_to_atom(
					cntl->संकेत,
					cntl->enable_dp_audio));
	params.ucLaneNum = (uपूर्णांक8_t)(cntl->lanes_number);

	चयन (cntl->color_depth) अणु
	हाल COLOR_DEPTH_888:
		params.ucBitPerColor = PANEL_8BIT_PER_COLOR;
		अवरोध;
	हाल COLOR_DEPTH_101010:
		params.ucBitPerColor = PANEL_10BIT_PER_COLOR;
		अवरोध;
	हाल COLOR_DEPTH_121212:
		params.ucBitPerColor = PANEL_12BIT_PER_COLOR;
		अवरोध;
	हाल COLOR_DEPTH_161616:
		params.ucBitPerColor = PANEL_16BIT_PER_COLOR;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (cntl->संकेत == SIGNAL_TYPE_HDMI_TYPE_A)
		चयन (cntl->color_depth) अणु
		हाल COLOR_DEPTH_101010:
			params.ulPixelClock =
				(params.ulPixelClock * 30) / 24;
			अवरोध;
		हाल COLOR_DEPTH_121212:
			params.ulPixelClock =
				(params.ulPixelClock * 36) / 24;
			अवरोध;
		हाल COLOR_DEPTH_161616:
			params.ulPixelClock =
				(params.ulPixelClock * 48) / 24;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

	अगर (EXEC_BIOS_CMD_TABLE(DIGxEncoderControl, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

/*******************************************************************************
 ********************************************************************************
 **
 **                  TRANSMITTER CONTROL
 **
 ********************************************************************************
 *******************************************************************************/

अटल क्रमागत bp_result transmitter_control_v2(
	काष्ठा bios_parser *bp,
	काष्ठा bp_transmitter_control *cntl);
अटल क्रमागत bp_result transmitter_control_v3(
	काष्ठा bios_parser *bp,
	काष्ठा bp_transmitter_control *cntl);
अटल क्रमागत bp_result transmitter_control_v4(
	काष्ठा bios_parser *bp,
	काष्ठा bp_transmitter_control *cntl);
अटल क्रमागत bp_result transmitter_control_v1_5(
	काष्ठा bios_parser *bp,
	काष्ठा bp_transmitter_control *cntl);
अटल क्रमागत bp_result transmitter_control_v1_6(
	काष्ठा bios_parser *bp,
	काष्ठा bp_transmitter_control *cntl);

अटल व्योम init_transmitter_control(काष्ठा bios_parser *bp)
अणु
	uपूर्णांक8_t frev;
	uपूर्णांक8_t crev;

	अगर (BIOS_CMD_TABLE_REVISION(UNIPHYTransmitterControl,
			frev, crev) == false)
		BREAK_TO_DEBUGGER();
	चयन (crev) अणु
	हाल 2:
		bp->cmd_tbl.transmitter_control = transmitter_control_v2;
		अवरोध;
	हाल 3:
		bp->cmd_tbl.transmitter_control = transmitter_control_v3;
		अवरोध;
	हाल 4:
		bp->cmd_tbl.transmitter_control = transmitter_control_v4;
		अवरोध;
	हाल 5:
		bp->cmd_tbl.transmitter_control = transmitter_control_v1_5;
		अवरोध;
	हाल 6:
		bp->cmd_tbl.transmitter_control = transmitter_control_v1_6;
		अवरोध;
	शेष:
		dm_output_to_console("Don't have transmitter_control for v%d\n", crev);
		bp->cmd_tbl.transmitter_control = शून्य;
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत bp_result transmitter_control_v2(
	काष्ठा bios_parser *bp,
	काष्ठा bp_transmitter_control *cntl)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	DIG_TRANSMITTER_CONTROL_PARAMETERS_V2 params;
	क्रमागत connector_id connector_id =
		dal_graphics_object_id_get_connector_id(cntl->connector_obj_id);

	स_रखो(&params, 0, माप(params));

	चयन (cntl->transmitter) अणु
	हाल TRANSMITTER_UNIPHY_A:
	हाल TRANSMITTER_UNIPHY_B:
	हाल TRANSMITTER_UNIPHY_C:
	हाल TRANSMITTER_UNIPHY_D:
	हाल TRANSMITTER_UNIPHY_E:
	हाल TRANSMITTER_UNIPHY_F:
	हाल TRANSMITTER_TRAVIS_LCD:
		अवरोध;
	शेष:
		वापस BP_RESULT_BADINPUT;
	पूर्ण

	चयन (cntl->action) अणु
	हाल TRANSMITTER_CONTROL_INIT:
		अगर ((CONNECTOR_ID_DUAL_LINK_DVII == connector_id) ||
				(CONNECTOR_ID_DUAL_LINK_DVID == connector_id))
			/* on INIT this bit should be set according to the
			 * phisycal connector
			 * Bit0: dual link connector flag
			 * =0 connector is single link connector
			 * =1 connector is dual link connector
			 */
			params.acConfig.fDualLinkConnector = 1;

		/* connector object id */
		params.usInitInfo =
				cpu_to_le16((uपूर्णांक8_t)cntl->connector_obj_id.id);
		अवरोध;
	हाल TRANSMITTER_CONTROL_SET_VOLTAGE_AND_PREEMPASIS:
		/* votage swing and pre-emphsis */
		params.asMode.ucLaneSel = (uपूर्णांक8_t)cntl->lane_select;
		params.asMode.ucLaneSet = (uपूर्णांक8_t)cntl->lane_settings;
		अवरोध;
	शेष:
		/* अगर dual-link */
		अगर (LANE_COUNT_FOUR < cntl->lanes_number) अणु
			/* on ENABLE/DISABLE this bit should be set according to
			 * actual timing (number of lanes)
			 * Bit0: dual link connector flag
			 * =0 connector is single link connector
			 * =1 connector is dual link connector
			 */
			params.acConfig.fDualLinkConnector = 1;

			/* link rate, half क्रम dual link
			 * We need to convert from KHz units पूर्णांकo 20KHz units
			 */
			params.usPixelClock =
					cpu_to_le16((uपूर्णांक16_t)(cntl->pixel_घड़ी / 20));
		पूर्ण अन्यथा
			/* link rate, half क्रम dual link
			 * We need to convert from KHz units पूर्णांकo 10KHz units
			 */
			params.usPixelClock =
					cpu_to_le16((uपूर्णांक16_t)(cntl->pixel_घड़ी / 10));
		अवरोध;
	पूर्ण

	/* 00 - coherent mode
	 * 01 - incoherent mode
	 */

	params.acConfig.fCoherentMode = cntl->coherent;

	अगर ((TRANSMITTER_UNIPHY_B == cntl->transmitter)
			|| (TRANSMITTER_UNIPHY_D == cntl->transmitter)
			|| (TRANSMITTER_UNIPHY_F == cntl->transmitter))
		/* Bit2: Transmitter Link selection
		 * =0 when bit0=0, single link A/C/E, when bit0=1,
		 * master link A/C/E
		 * =1 when bit0=0, single link B/D/F, when bit0=1,
		 * master link B/D/F
		 */
		params.acConfig.ucLinkSel = 1;

	अगर (ENGINE_ID_DIGB == cntl->engine_id)
		/* Bit3: Transmitter data source selection
		 * =0 DIGA is data source.
		 * =1 DIGB is data source.
		 * This bit is only useful when ucAction= ATOM_ENABLE
		 */
		params.acConfig.ucEncoderSel = 1;

	अगर (CONNECTOR_ID_DISPLAY_PORT == connector_id)
		/* Bit4: DP connector flag
		 * =0 connector is none-DP connector
		 * =1 connector is DP connector
		 */
		params.acConfig.fDPConnector = 1;

	/* Bit[7:6]: Transmitter selection
	 * =0 UNIPHY_ENCODER: UNIPHYA/B
	 * =1 UNIPHY1_ENCODER: UNIPHYC/D
	 * =2 UNIPHY2_ENCODER: UNIPHYE/F
	 * =3 reserved
	 */
	params.acConfig.ucTransmitterSel =
			(uपूर्णांक8_t)bp->cmd_helper->transmitter_bp_to_atom(
					cntl->transmitter);

	params.ucAction = (uपूर्णांक8_t)cntl->action;

	अगर (EXEC_BIOS_CMD_TABLE(UNIPHYTransmitterControl, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

अटल क्रमागत bp_result transmitter_control_v3(
	काष्ठा bios_parser *bp,
	काष्ठा bp_transmitter_control *cntl)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	DIG_TRANSMITTER_CONTROL_PARAMETERS_V3 params;
	uपूर्णांक32_t pll_id;
	क्रमागत connector_id conn_id =
			dal_graphics_object_id_get_connector_id(cntl->connector_obj_id);
	स्थिर काष्ठा command_table_helper *cmd = bp->cmd_helper;
	bool dual_link_conn = (CONNECTOR_ID_DUAL_LINK_DVII == conn_id)
					|| (CONNECTOR_ID_DUAL_LINK_DVID == conn_id);

	स_रखो(&params, 0, माप(params));

	चयन (cntl->transmitter) अणु
	हाल TRANSMITTER_UNIPHY_A:
	हाल TRANSMITTER_UNIPHY_B:
	हाल TRANSMITTER_UNIPHY_C:
	हाल TRANSMITTER_UNIPHY_D:
	हाल TRANSMITTER_UNIPHY_E:
	हाल TRANSMITTER_UNIPHY_F:
	हाल TRANSMITTER_TRAVIS_LCD:
		अवरोध;
	शेष:
		वापस BP_RESULT_BADINPUT;
	पूर्ण

	अगर (!cmd->घड़ी_source_id_to_atom(cntl->pll_id, &pll_id))
		वापस BP_RESULT_BADINPUT;

	/* fill inक्रमmation based on the action */
	चयन (cntl->action) अणु
	हाल TRANSMITTER_CONTROL_INIT:
		अगर (dual_link_conn) अणु
			/* on INIT this bit should be set according to the
			 * phisycal connector
			 * Bit0: dual link connector flag
			 * =0 connector is single link connector
			 * =1 connector is dual link connector
			 */
			params.acConfig.fDualLinkConnector = 1;
		पूर्ण

		/* connector object id */
		params.usInitInfo =
				cpu_to_le16((uपूर्णांक8_t)(cntl->connector_obj_id.id));
		अवरोध;
	हाल TRANSMITTER_CONTROL_SET_VOLTAGE_AND_PREEMPASIS:
		/* votage swing and pre-emphsis */
		params.asMode.ucLaneSel = (uपूर्णांक8_t)cntl->lane_select;
		params.asMode.ucLaneSet = (uपूर्णांक8_t)cntl->lane_settings;
		अवरोध;
	शेष:
		अगर (dual_link_conn && cntl->multi_path)
			/* on ENABLE/DISABLE this bit should be set according to
			 * actual timing (number of lanes)
			 * Bit0: dual link connector flag
			 * =0 connector is single link connector
			 * =1 connector is dual link connector
			 */
			params.acConfig.fDualLinkConnector = 1;

		/* अगर dual-link */
		अगर (LANE_COUNT_FOUR < cntl->lanes_number) अणु
			/* on ENABLE/DISABLE this bit should be set according to
			 * actual timing (number of lanes)
			 * Bit0: dual link connector flag
			 * =0 connector is single link connector
			 * =1 connector is dual link connector
			 */
			params.acConfig.fDualLinkConnector = 1;

			/* link rate, half क्रम dual link
			 * We need to convert from KHz units पूर्णांकo 20KHz units
			 */
			params.usPixelClock =
					cpu_to_le16((uपूर्णांक16_t)(cntl->pixel_घड़ी / 20));
		पूर्ण अन्यथा अणु
			/* link rate, half क्रम dual link
			 * We need to convert from KHz units पूर्णांकo 10KHz units
			 */
			params.usPixelClock =
					cpu_to_le16((uपूर्णांक16_t)(cntl->pixel_घड़ी / 10));
		पूर्ण
		अवरोध;
	पूर्ण

	/* 00 - coherent mode
	 * 01 - incoherent mode
	 */

	params.acConfig.fCoherentMode = cntl->coherent;

	अगर ((TRANSMITTER_UNIPHY_B == cntl->transmitter)
		|| (TRANSMITTER_UNIPHY_D == cntl->transmitter)
		|| (TRANSMITTER_UNIPHY_F == cntl->transmitter))
		/* Bit2: Transmitter Link selection
		 * =0 when bit0=0, single link A/C/E, when bit0=1,
		 * master link A/C/E
		 * =1 when bit0=0, single link B/D/F, when bit0=1,
		 * master link B/D/F
		 */
		params.acConfig.ucLinkSel = 1;

	अगर (ENGINE_ID_DIGB == cntl->engine_id)
		/* Bit3: Transmitter data source selection
		 * =0 DIGA is data source.
		 * =1 DIGB is data source.
		 * This bit is only useful when ucAction= ATOM_ENABLE
		 */
		params.acConfig.ucEncoderSel = 1;

	/* Bit[7:6]: Transmitter selection
	 * =0 UNIPHY_ENCODER: UNIPHYA/B
	 * =1 UNIPHY1_ENCODER: UNIPHYC/D
	 * =2 UNIPHY2_ENCODER: UNIPHYE/F
	 * =3 reserved
	 */
	params.acConfig.ucTransmitterSel =
			(uपूर्णांक8_t)cmd->transmitter_bp_to_atom(cntl->transmitter);

	params.ucLaneNum = (uपूर्णांक8_t)cntl->lanes_number;

	params.acConfig.ucRefClkSource = (uपूर्णांक8_t)pll_id;

	params.ucAction = (uपूर्णांक8_t)cntl->action;

	अगर (EXEC_BIOS_CMD_TABLE(UNIPHYTransmitterControl, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

अटल क्रमागत bp_result transmitter_control_v4(
	काष्ठा bios_parser *bp,
	काष्ठा bp_transmitter_control *cntl)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	DIG_TRANSMITTER_CONTROL_PARAMETERS_V4 params;
	uपूर्णांक32_t ref_clk_src_id;
	क्रमागत connector_id conn_id =
			dal_graphics_object_id_get_connector_id(cntl->connector_obj_id);
	स्थिर काष्ठा command_table_helper *cmd = bp->cmd_helper;

	स_रखो(&params, 0, माप(params));

	चयन (cntl->transmitter) अणु
	हाल TRANSMITTER_UNIPHY_A:
	हाल TRANSMITTER_UNIPHY_B:
	हाल TRANSMITTER_UNIPHY_C:
	हाल TRANSMITTER_UNIPHY_D:
	हाल TRANSMITTER_UNIPHY_E:
	हाल TRANSMITTER_UNIPHY_F:
	हाल TRANSMITTER_TRAVIS_LCD:
		अवरोध;
	शेष:
		वापस BP_RESULT_BADINPUT;
	पूर्ण

	अगर (!cmd->घड़ी_source_id_to_ref_clk_src(cntl->pll_id, &ref_clk_src_id))
		वापस BP_RESULT_BADINPUT;

	चयन (cntl->action) अणु
	हाल TRANSMITTER_CONTROL_INIT:
	अणु
		अगर ((CONNECTOR_ID_DUAL_LINK_DVII == conn_id) ||
				(CONNECTOR_ID_DUAL_LINK_DVID == conn_id))
			/* on INIT this bit should be set according to the
			 * phisycal connector
			 * Bit0: dual link connector flag
			 * =0 connector is single link connector
			 * =1 connector is dual link connector
			 */
			params.acConfig.fDualLinkConnector = 1;

		/* connector object id */
		params.usInitInfo =
				cpu_to_le16((uपूर्णांक8_t)(cntl->connector_obj_id.id));
	पूर्ण
	अवरोध;
	हाल TRANSMITTER_CONTROL_SET_VOLTAGE_AND_PREEMPASIS:
		/* votage swing and pre-emphsis */
		params.asMode.ucLaneSel = (uपूर्णांक8_t)(cntl->lane_select);
		params.asMode.ucLaneSet = (uपूर्णांक8_t)(cntl->lane_settings);
		अवरोध;
	शेष:
		अगर ((CONNECTOR_ID_DUAL_LINK_DVII == conn_id) ||
				(CONNECTOR_ID_DUAL_LINK_DVID == conn_id))
			/* on ENABLE/DISABLE this bit should be set according to
			 * actual timing (number of lanes)
			 * Bit0: dual link connector flag
			 * =0 connector is single link connector
			 * =1 connector is dual link connector
			 */
			params.acConfig.fDualLinkConnector = 1;

		/* अगर dual-link */
		अगर (LANE_COUNT_FOUR < cntl->lanes_number)
			/* link rate, half क्रम dual link
			 * We need to convert from KHz units पूर्णांकo 20KHz units
			 */
			params.usPixelClock =
					cpu_to_le16((uपूर्णांक16_t)(cntl->pixel_घड़ी / 20));
		अन्यथा अणु
			/* link rate, half क्रम dual link
			 * We need to convert from KHz units पूर्णांकo 10KHz units
			 */
			params.usPixelClock =
					cpu_to_le16((uपूर्णांक16_t)(cntl->pixel_घड़ी / 10));
		पूर्ण
		अवरोध;
	पूर्ण

	/* 00 - coherent mode
	 * 01 - incoherent mode
	 */

	params.acConfig.fCoherentMode = cntl->coherent;

	अगर ((TRANSMITTER_UNIPHY_B == cntl->transmitter)
		|| (TRANSMITTER_UNIPHY_D == cntl->transmitter)
		|| (TRANSMITTER_UNIPHY_F == cntl->transmitter))
		/* Bit2: Transmitter Link selection
		 * =0 when bit0=0, single link A/C/E, when bit0=1,
		 * master link A/C/E
		 * =1 when bit0=0, single link B/D/F, when bit0=1,
		 * master link B/D/F
		 */
		params.acConfig.ucLinkSel = 1;

	अगर (ENGINE_ID_DIGB == cntl->engine_id)
		/* Bit3: Transmitter data source selection
		 * =0 DIGA is data source.
		 * =1 DIGB is data source.
		 * This bit is only useful when ucAction= ATOM_ENABLE
		 */
		params.acConfig.ucEncoderSel = 1;

	/* Bit[7:6]: Transmitter selection
	 * =0 UNIPHY_ENCODER: UNIPHYA/B
	 * =1 UNIPHY1_ENCODER: UNIPHYC/D
	 * =2 UNIPHY2_ENCODER: UNIPHYE/F
	 * =3 reserved
	 */
	params.acConfig.ucTransmitterSel =
		(uपूर्णांक8_t)(cmd->transmitter_bp_to_atom(cntl->transmitter));
	params.ucLaneNum = (uपूर्णांक8_t)(cntl->lanes_number);
	params.acConfig.ucRefClkSource = (uपूर्णांक8_t)(ref_clk_src_id);
	params.ucAction = (uपूर्णांक8_t)(cntl->action);

	अगर (EXEC_BIOS_CMD_TABLE(UNIPHYTransmitterControl, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

अटल क्रमागत bp_result transmitter_control_v1_5(
	काष्ठा bios_parser *bp,
	काष्ठा bp_transmitter_control *cntl)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	स्थिर काष्ठा command_table_helper *cmd = bp->cmd_helper;
	DIG_TRANSMITTER_CONTROL_PARAMETERS_V1_5 params;

	स_रखो(&params, 0, माप(params));
	params.ucPhyId = cmd->phy_id_to_atom(cntl->transmitter);
	params.ucAction = (uपूर्णांक8_t)cntl->action;
	params.ucLaneNum = (uपूर्णांक8_t)cntl->lanes_number;
	params.ucConnObjId = (uपूर्णांक8_t)cntl->connector_obj_id.id;

	params.ucDigMode =
		cmd->संकेत_type_to_atom_dig_mode(cntl->संकेत);
	params.asConfig.ucPhyClkSrcId =
		cmd->घड़ी_source_id_to_atom_phy_clk_src_id(cntl->pll_id);
	/* 00 - coherent mode */
	params.asConfig.ucCoherentMode = cntl->coherent;
	params.asConfig.ucHPDSel =
		cmd->hpd_sel_to_atom(cntl->hpd_sel);
	params.ucDigEncoderSel =
		cmd->dig_encoder_sel_to_atom(cntl->engine_id);
	params.ucDPLaneSet = (uपूर्णांक8_t) cntl->lane_settings;
	params.usSymClock = cpu_to_le16((uपूर्णांक16_t) (cntl->pixel_घड़ी / 10));
	/*
	 * In SI/TN हाल, caller have to set usPixelClock as following:
	 * DP mode: usPixelClock = DP_LINK_CLOCK/10
	 * (DP_LINK_CLOCK = 1.62GHz, 2.7GHz, 5.4GHz)
	 * DVI single link mode: usPixelClock = pixel घड़ी
	 * DVI dual link mode: usPixelClock = pixel घड़ी
	 * HDMI mode: usPixelClock = pixel घड़ी * deep_color_ratio
	 * (=1: 8bpp, =1.25: 10bpp, =1.5:12bpp, =2: 16bpp)
	 * LVDS mode: usPixelClock = pixel घड़ी
	 */
	अगर  (cntl->संकेत == SIGNAL_TYPE_HDMI_TYPE_A) अणु
		चयन (cntl->color_depth) अणु
		हाल COLOR_DEPTH_101010:
			params.usSymClock =
				cpu_to_le16((le16_to_cpu(params.usSymClock) * 30) / 24);
			अवरोध;
		हाल COLOR_DEPTH_121212:
			params.usSymClock =
				cpu_to_le16((le16_to_cpu(params.usSymClock) * 36) / 24);
			अवरोध;
		हाल COLOR_DEPTH_161616:
			params.usSymClock =
				cpu_to_le16((le16_to_cpu(params.usSymClock) * 48) / 24);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (EXEC_BIOS_CMD_TABLE(UNIPHYTransmitterControl, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

अटल क्रमागत bp_result transmitter_control_v1_6(
	काष्ठा bios_parser *bp,
	काष्ठा bp_transmitter_control *cntl)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	स्थिर काष्ठा command_table_helper *cmd = bp->cmd_helper;
	DIG_TRANSMITTER_CONTROL_PARAMETERS_V1_6 params;

	स_रखो(&params, 0, माप(params));
	params.ucPhyId = cmd->phy_id_to_atom(cntl->transmitter);
	params.ucAction = (uपूर्णांक8_t)cntl->action;

	अगर (cntl->action == TRANSMITTER_CONTROL_SET_VOLTAGE_AND_PREEMPASIS)
		params.ucDPLaneSet = (uपूर्णांक8_t)cntl->lane_settings;
	अन्यथा
		params.ucDigMode = cmd->संकेत_type_to_atom_dig_mode(cntl->संकेत);

	params.ucLaneNum = (uपूर्णांक8_t)cntl->lanes_number;
	params.ucHPDSel = cmd->hpd_sel_to_atom(cntl->hpd_sel);
	params.ucDigEncoderSel = cmd->dig_encoder_sel_to_atom(cntl->engine_id);
	params.ucConnObjId = (uपूर्णांक8_t)cntl->connector_obj_id.id;
	params.ulSymClock = cntl->pixel_घड़ी/10;

	/*
	 * In SI/TN हाल, caller have to set usPixelClock as following:
	 * DP mode: usPixelClock = DP_LINK_CLOCK/10
	 * (DP_LINK_CLOCK = 1.62GHz, 2.7GHz, 5.4GHz)
	 * DVI single link mode: usPixelClock = pixel घड़ी
	 * DVI dual link mode: usPixelClock = pixel घड़ी
	 * HDMI mode: usPixelClock = pixel घड़ी * deep_color_ratio
	 * (=1: 8bpp, =1.25: 10bpp, =1.5:12bpp, =2: 16bpp)
	 * LVDS mode: usPixelClock = pixel घड़ी
	 */
	चयन (cntl->संकेत) अणु
	हाल SIGNAL_TYPE_HDMI_TYPE_A:
		चयन (cntl->color_depth) अणु
		हाल COLOR_DEPTH_101010:
			params.ulSymClock =
				cpu_to_le16((le16_to_cpu(params.ulSymClock) * 30) / 24);
			अवरोध;
		हाल COLOR_DEPTH_121212:
			params.ulSymClock =
				cpu_to_le16((le16_to_cpu(params.ulSymClock) * 36) / 24);
			अवरोध;
		हाल COLOR_DEPTH_161616:
			params.ulSymClock =
				cpu_to_le16((le16_to_cpu(params.ulSymClock) * 48) / 24);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
		शेष:
			अवरोध;
	पूर्ण

	अगर (EXEC_BIOS_CMD_TABLE(UNIPHYTransmitterControl, params))
		result = BP_RESULT_OK;
	वापस result;
पूर्ण

/*******************************************************************************
 ********************************************************************************
 **
 **                  SET PIXEL CLOCK
 **
 ********************************************************************************
 *******************************************************************************/

अटल क्रमागत bp_result set_pixel_घड़ी_v3(
	काष्ठा bios_parser *bp,
	काष्ठा bp_pixel_घड़ी_parameters *bp_params);
अटल क्रमागत bp_result set_pixel_घड़ी_v5(
	काष्ठा bios_parser *bp,
	काष्ठा bp_pixel_घड़ी_parameters *bp_params);
अटल क्रमागत bp_result set_pixel_घड़ी_v6(
	काष्ठा bios_parser *bp,
	काष्ठा bp_pixel_घड़ी_parameters *bp_params);
अटल क्रमागत bp_result set_pixel_घड़ी_v7(
	काष्ठा bios_parser *bp,
	काष्ठा bp_pixel_घड़ी_parameters *bp_params);

अटल व्योम init_set_pixel_घड़ी(काष्ठा bios_parser *bp)
अणु
	चयन (BIOS_CMD_TABLE_PARA_REVISION(SetPixelClock)) अणु
	हाल 3:
		bp->cmd_tbl.set_pixel_घड़ी = set_pixel_घड़ी_v3;
		अवरोध;
	हाल 5:
		bp->cmd_tbl.set_pixel_घड़ी = set_pixel_घड़ी_v5;
		अवरोध;
	हाल 6:
		bp->cmd_tbl.set_pixel_घड़ी = set_pixel_घड़ी_v6;
		अवरोध;
	हाल 7:
		bp->cmd_tbl.set_pixel_घड़ी = set_pixel_घड़ी_v7;
		अवरोध;
	शेष:
		dm_output_to_console("Don't have set_pixel_clock for v%d\n",
			 BIOS_CMD_TABLE_PARA_REVISION(SetPixelClock));
		bp->cmd_tbl.set_pixel_घड़ी = शून्य;
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत bp_result set_pixel_घड़ी_v3(
	काष्ठा bios_parser *bp,
	काष्ठा bp_pixel_घड़ी_parameters *bp_params)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	PIXEL_CLOCK_PARAMETERS_V3 *params;
	SET_PIXEL_CLOCK_PS_ALLOCATION allocation;

	स_रखो(&allocation, 0, माप(allocation));

	अगर (CLOCK_SOURCE_ID_PLL1 == bp_params->pll_id)
		allocation.sPCLKInput.ucPpll = ATOM_PPLL1;
	अन्यथा अगर (CLOCK_SOURCE_ID_PLL2 == bp_params->pll_id)
		allocation.sPCLKInput.ucPpll = ATOM_PPLL2;
	अन्यथा
		वापस BP_RESULT_BADINPUT;

	allocation.sPCLKInput.usRefDiv =
			cpu_to_le16((uपूर्णांक16_t)bp_params->reference_भागider);
	allocation.sPCLKInput.usFbDiv =
			cpu_to_le16((uपूर्णांक16_t)bp_params->feedback_भागider);
	allocation.sPCLKInput.ucFracFbDiv =
			(uपूर्णांक8_t)bp_params->fractional_feedback_भागider;
	allocation.sPCLKInput.ucPostDiv =
			(uपूर्णांक8_t)bp_params->pixel_घड़ी_post_भागider;

	/* We need to convert from 100Hz units पूर्णांकo 10KHz units */
	allocation.sPCLKInput.usPixelClock =
			cpu_to_le16((uपूर्णांक16_t)(bp_params->target_pixel_घड़ी_100hz / 100));

	params = (PIXEL_CLOCK_PARAMETERS_V3 *)&allocation.sPCLKInput;
	params->ucTransmitterId =
			bp->cmd_helper->encoder_id_to_atom(
					dal_graphics_object_id_get_encoder_id(
							bp_params->encoder_object_id));
	params->ucEncoderMode =
			(uपूर्णांक8_t)(bp->cmd_helper->encoder_mode_bp_to_atom(
					bp_params->संकेत_type, false));

	अगर (bp_params->flags.FORCE_PROGRAMMING_OF_PLL)
		params->ucMiscInfo |= PIXEL_CLOCK_MISC_FORCE_PROG_PPLL;

	अगर (bp_params->flags.USE_E_CLOCK_AS_SOURCE_FOR_D_CLOCK)
		params->ucMiscInfo |= PIXEL_CLOCK_MISC_USE_ENGINE_FOR_DISPCLK;

	अगर (CONTROLLER_ID_D1 != bp_params->controller_id)
		params->ucMiscInfo |= PIXEL_CLOCK_MISC_CRTC_SEL_CRTC2;

	अगर (EXEC_BIOS_CMD_TABLE(SetPixelClock, allocation))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

#अगर_अघोषित SET_PIXEL_CLOCK_PS_ALLOCATION_V5
/* video bios did not define this: */
प्रकार काष्ठा _SET_PIXEL_CLOCK_PS_ALLOCATION_V5 अणु
	PIXEL_CLOCK_PARAMETERS_V5 sPCLKInput;
	/* Caller करोesn't need to init this portion */
	ENABLE_SPREAD_SPECTRUM_ON_PPLL sReserved;
पूर्ण SET_PIXEL_CLOCK_PS_ALLOCATION_V5;
#पूर्ण_अगर

#अगर_अघोषित SET_PIXEL_CLOCK_PS_ALLOCATION_V6
/* video bios did not define this: */
प्रकार काष्ठा _SET_PIXEL_CLOCK_PS_ALLOCATION_V6 अणु
	PIXEL_CLOCK_PARAMETERS_V6 sPCLKInput;
	/* Caller करोesn't need to init this portion */
	ENABLE_SPREAD_SPECTRUM_ON_PPLL sReserved;
पूर्ण SET_PIXEL_CLOCK_PS_ALLOCATION_V6;
#पूर्ण_अगर

अटल क्रमागत bp_result set_pixel_घड़ी_v5(
	काष्ठा bios_parser *bp,
	काष्ठा bp_pixel_घड़ी_parameters *bp_params)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	SET_PIXEL_CLOCK_PS_ALLOCATION_V5 clk;
	uपूर्णांक8_t controller_id;
	uपूर्णांक32_t pll_id;

	स_रखो(&clk, 0, माप(clk));

	अगर (bp->cmd_helper->घड़ी_source_id_to_atom(bp_params->pll_id, &pll_id)
			&& bp->cmd_helper->controller_id_to_atom(
					bp_params->controller_id, &controller_id)) अणु
		clk.sPCLKInput.ucCRTC = controller_id;
		clk.sPCLKInput.ucPpll = (uपूर्णांक8_t)pll_id;
		clk.sPCLKInput.ucRefDiv =
				(uपूर्णांक8_t)(bp_params->reference_भागider);
		clk.sPCLKInput.usFbDiv =
				cpu_to_le16((uपूर्णांक16_t)(bp_params->feedback_भागider));
		clk.sPCLKInput.ulFbDivDecFrac =
				cpu_to_le32(bp_params->fractional_feedback_भागider);
		clk.sPCLKInput.ucPostDiv =
				(uपूर्णांक8_t)(bp_params->pixel_घड़ी_post_भागider);
		clk.sPCLKInput.ucTransmitterID =
				bp->cmd_helper->encoder_id_to_atom(
						dal_graphics_object_id_get_encoder_id(
								bp_params->encoder_object_id));
		clk.sPCLKInput.ucEncoderMode =
				(uपूर्णांक8_t)bp->cmd_helper->encoder_mode_bp_to_atom(
						bp_params->संकेत_type, false);

		/* We need to convert from 100Hz units पूर्णांकo 10KHz units */
		clk.sPCLKInput.usPixelClock =
				cpu_to_le16((uपूर्णांक16_t)(bp_params->target_pixel_घड़ी_100hz / 100));

		अगर (bp_params->flags.FORCE_PROGRAMMING_OF_PLL)
			clk.sPCLKInput.ucMiscInfo |=
					PIXEL_CLOCK_MISC_FORCE_PROG_PPLL;

		अगर (bp_params->flags.SET_EXTERNAL_REF_DIV_SRC)
			clk.sPCLKInput.ucMiscInfo |=
					PIXEL_CLOCK_MISC_REF_DIV_SRC;

		/* clkV5.ucMiscInfo bit[3:2]= HDMI panel bit depth: =0: 24bpp
		 * =1:30bpp, =2:32bpp
		 * driver choose program it itself, i.e. here we program it
		 * to 888 by शेष.
		 */
		अगर (bp_params->संकेत_type == SIGNAL_TYPE_HDMI_TYPE_A)
			चयन (bp_params->color_depth) अणु
			हाल TRANSMITTER_COLOR_DEPTH_30:
				/* yes this is correct, the atom define is wrong */
				clk.sPCLKInput.ucMiscInfo |= PIXEL_CLOCK_V5_MISC_HDMI_32BPP;
				अवरोध;
			हाल TRANSMITTER_COLOR_DEPTH_36:
				/* yes this is correct, the atom define is wrong */
				clk.sPCLKInput.ucMiscInfo |= PIXEL_CLOCK_V5_MISC_HDMI_30BPP;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

		अगर (EXEC_BIOS_CMD_TABLE(SetPixelClock, clk))
			result = BP_RESULT_OK;
	पूर्ण

	वापस result;
पूर्ण

अटल क्रमागत bp_result set_pixel_घड़ी_v6(
	काष्ठा bios_parser *bp,
	काष्ठा bp_pixel_घड़ी_parameters *bp_params)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	SET_PIXEL_CLOCK_PS_ALLOCATION_V6 clk;
	uपूर्णांक8_t controller_id;
	uपूर्णांक32_t pll_id;

	स_रखो(&clk, 0, माप(clk));

	अगर (bp->cmd_helper->घड़ी_source_id_to_atom(bp_params->pll_id, &pll_id)
			&& bp->cmd_helper->controller_id_to_atom(
					bp_params->controller_id, &controller_id)) अणु
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
		clk.sPCLKInput.ulCrtcPclkFreq.ucCRTC = controller_id;
		clk.sPCLKInput.ucPpll = (uपूर्णांक8_t) pll_id;
		clk.sPCLKInput.ucRefDiv =
				(uपूर्णांक8_t) bp_params->reference_भागider;
		clk.sPCLKInput.usFbDiv =
				cpu_to_le16((uपूर्णांक16_t) bp_params->feedback_भागider);
		clk.sPCLKInput.ulFbDivDecFrac =
				cpu_to_le32(bp_params->fractional_feedback_भागider);
		clk.sPCLKInput.ucPostDiv =
				(uपूर्णांक8_t) bp_params->pixel_घड़ी_post_भागider;
		clk.sPCLKInput.ucTransmitterID =
				bp->cmd_helper->encoder_id_to_atom(
						dal_graphics_object_id_get_encoder_id(
								bp_params->encoder_object_id));
		clk.sPCLKInput.ucEncoderMode =
				(uपूर्णांक8_t) bp->cmd_helper->encoder_mode_bp_to_atom(
						bp_params->संकेत_type, false);

		/* We need to convert from 100 Hz units पूर्णांकo 10KHz units */
		clk.sPCLKInput.ulCrtcPclkFreq.ulPixelClock =
				cpu_to_le32(bp_params->target_pixel_घड़ी_100hz / 100);

		अगर (bp_params->flags.FORCE_PROGRAMMING_OF_PLL) अणु
			clk.sPCLKInput.ucMiscInfo |=
					PIXEL_CLOCK_V6_MISC_FORCE_PROG_PPLL;
		पूर्ण

		अगर (bp_params->flags.SET_EXTERNAL_REF_DIV_SRC) अणु
			clk.sPCLKInput.ucMiscInfo |=
					PIXEL_CLOCK_V6_MISC_REF_DIV_SRC;
		पूर्ण

		/* clkV6.ucMiscInfo bit[3:2]= HDMI panel bit depth: =0:
		 * 24bpp =1:30bpp, =2:32bpp
		 * driver choose program it itself, i.e. here we pass required
		 * target rate that includes deep color.
		 */
		अगर (bp_params->संकेत_type == SIGNAL_TYPE_HDMI_TYPE_A)
			चयन (bp_params->color_depth) अणु
			हाल TRANSMITTER_COLOR_DEPTH_30:
				clk.sPCLKInput.ucMiscInfo |= PIXEL_CLOCK_V6_MISC_HDMI_30BPP_V6;
				अवरोध;
			हाल TRANSMITTER_COLOR_DEPTH_36:
				clk.sPCLKInput.ucMiscInfo |= PIXEL_CLOCK_V6_MISC_HDMI_36BPP_V6;
				अवरोध;
			हाल TRANSMITTER_COLOR_DEPTH_48:
				clk.sPCLKInput.ucMiscInfo |= PIXEL_CLOCK_V6_MISC_HDMI_48BPP;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

		अगर (EXEC_BIOS_CMD_TABLE(SetPixelClock, clk))
			result = BP_RESULT_OK;
	पूर्ण

	वापस result;
पूर्ण

अटल क्रमागत bp_result set_pixel_घड़ी_v7(
	काष्ठा bios_parser *bp,
	काष्ठा bp_pixel_घड़ी_parameters *bp_params)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	PIXEL_CLOCK_PARAMETERS_V7 clk;
	uपूर्णांक8_t controller_id;
	uपूर्णांक32_t pll_id;

	स_रखो(&clk, 0, माप(clk));

	अगर (bp->cmd_helper->घड़ी_source_id_to_atom(bp_params->pll_id, &pll_id)
			&& bp->cmd_helper->controller_id_to_atom(bp_params->controller_id, &controller_id)) अणु
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
		clk.ucCRTC = controller_id;
		clk.ucPpll = (uपूर्णांक8_t) pll_id;
		clk.ucTransmitterID = bp->cmd_helper->encoder_id_to_atom(dal_graphics_object_id_get_encoder_id(bp_params->encoder_object_id));
		clk.ucEncoderMode = (uपूर्णांक8_t) bp->cmd_helper->encoder_mode_bp_to_atom(bp_params->संकेत_type, false);

		clk.ulPixelClock = cpu_to_le32(bp_params->target_pixel_घड़ी_100hz);

		clk.ucDeepColorRatio = (uपूर्णांक8_t) bp->cmd_helper->transmitter_color_depth_to_atom(bp_params->color_depth);

		अगर (bp_params->flags.FORCE_PROGRAMMING_OF_PLL)
			clk.ucMiscInfo |= PIXEL_CLOCK_V7_MISC_FORCE_PROG_PPLL;

		अगर (bp_params->flags.SET_EXTERNAL_REF_DIV_SRC)
			clk.ucMiscInfo |= PIXEL_CLOCK_V7_MISC_REF_DIV_SRC;

		अगर (bp_params->flags.PROGRAM_PHY_PLL_ONLY)
			clk.ucMiscInfo |= PIXEL_CLOCK_V7_MISC_PROG_PHYPLL;

		अगर (bp_params->flags.SUPPORT_YUV_420)
			clk.ucMiscInfo |= PIXEL_CLOCK_V7_MISC_YUV420_MODE;

		अगर (bp_params->flags.SET_XTALIN_REF_SRC)
			clk.ucMiscInfo |= PIXEL_CLOCK_V7_MISC_REF_DIV_SRC_XTALIN;

		अगर (bp_params->flags.SET_GENLOCK_REF_DIV_SRC)
			clk.ucMiscInfo |= PIXEL_CLOCK_V7_MISC_REF_DIV_SRC_GENLK;

		अगर (bp_params->संकेत_type == SIGNAL_TYPE_DVI_DUAL_LINK)
			clk.ucMiscInfo |= PIXEL_CLOCK_V7_MISC_DVI_DUALLINK_EN;

		अगर (EXEC_BIOS_CMD_TABLE(SetPixelClock, clk))
			result = BP_RESULT_OK;
	पूर्ण
	वापस result;
पूर्ण

/*******************************************************************************
 ********************************************************************************
 **
 **                  ENABLE PIXEL CLOCK SS
 **
 ********************************************************************************
 *******************************************************************************/
अटल क्रमागत bp_result enable_spपढ़ो_spectrum_on_ppll_v1(
	काष्ठा bios_parser *bp,
	काष्ठा bp_spपढ़ो_spectrum_parameters *bp_params,
	bool enable);
अटल क्रमागत bp_result enable_spपढ़ो_spectrum_on_ppll_v2(
	काष्ठा bios_parser *bp,
	काष्ठा bp_spपढ़ो_spectrum_parameters *bp_params,
	bool enable);
अटल क्रमागत bp_result enable_spपढ़ो_spectrum_on_ppll_v3(
	काष्ठा bios_parser *bp,
	काष्ठा bp_spपढ़ो_spectrum_parameters *bp_params,
	bool enable);

अटल व्योम init_enable_spपढ़ो_spectrum_on_ppll(काष्ठा bios_parser *bp)
अणु
	चयन (BIOS_CMD_TABLE_PARA_REVISION(EnableSpपढ़ोSpectrumOnPPLL)) अणु
	हाल 1:
		bp->cmd_tbl.enable_spपढ़ो_spectrum_on_ppll =
				enable_spपढ़ो_spectrum_on_ppll_v1;
		अवरोध;
	हाल 2:
		bp->cmd_tbl.enable_spपढ़ो_spectrum_on_ppll =
				enable_spपढ़ो_spectrum_on_ppll_v2;
		अवरोध;
	हाल 3:
		bp->cmd_tbl.enable_spपढ़ो_spectrum_on_ppll =
				enable_spपढ़ो_spectrum_on_ppll_v3;
		अवरोध;
	शेष:
		dm_output_to_console("Don't have enable_spread_spectrum_on_ppll for v%d\n",
			 BIOS_CMD_TABLE_PARA_REVISION(EnableSpपढ़ोSpectrumOnPPLL));
		bp->cmd_tbl.enable_spपढ़ो_spectrum_on_ppll = शून्य;
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत bp_result enable_spपढ़ो_spectrum_on_ppll_v1(
	काष्ठा bios_parser *bp,
	काष्ठा bp_spपढ़ो_spectrum_parameters *bp_params,
	bool enable)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	ENABLE_SPREAD_SPECTRUM_ON_PPLL params;

	स_रखो(&params, 0, माप(params));

	अगर ((enable == true) && (bp_params->percentage > 0))
		params.ucEnable = ATOM_ENABLE;
	अन्यथा
		params.ucEnable = ATOM_DISABLE;

	params.usSpपढ़ोSpectrumPercentage =
			cpu_to_le16((uपूर्णांक16_t)bp_params->percentage);
	params.ucSpपढ़ोSpectrumStep =
			(uपूर्णांक8_t)bp_params->ver1.step;
	params.ucSpपढ़ोSpectrumDelay =
			(uपूर्णांक8_t)bp_params->ver1.delay;
	/* convert back to unit of 10KHz */
	params.ucSpपढ़ोSpectrumRange =
			(uपूर्णांक8_t)(bp_params->ver1.range / 10000);

	अगर (bp_params->flags.EXTERNAL_SS)
		params.ucSpपढ़ोSpectrumType |= ATOM_EXTERNAL_SS_MASK;

	अगर (bp_params->flags.CENTER_SPREAD)
		params.ucSpपढ़ोSpectrumType |= ATOM_SS_CENTRE_SPREAD_MODE;

	अगर (bp_params->pll_id == CLOCK_SOURCE_ID_PLL1)
		params.ucPpll = ATOM_PPLL1;
	अन्यथा अगर (bp_params->pll_id == CLOCK_SOURCE_ID_PLL2)
		params.ucPpll = ATOM_PPLL2;
	अन्यथा
		BREAK_TO_DEBUGGER(); /* Unexpected PLL value!! */

	अगर (EXEC_BIOS_CMD_TABLE(EnableSpपढ़ोSpectrumOnPPLL, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

अटल क्रमागत bp_result enable_spपढ़ो_spectrum_on_ppll_v2(
	काष्ठा bios_parser *bp,
	काष्ठा bp_spपढ़ो_spectrum_parameters *bp_params,
	bool enable)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	ENABLE_SPREAD_SPECTRUM_ON_PPLL_V2 params;

	स_रखो(&params, 0, माप(params));

	अगर (bp_params->pll_id == CLOCK_SOURCE_ID_PLL1)
		params.ucSpपढ़ोSpectrumType = ATOM_PPLL_SS_TYPE_V2_P1PLL;
	अन्यथा अगर (bp_params->pll_id == CLOCK_SOURCE_ID_PLL2)
		params.ucSpपढ़ोSpectrumType = ATOM_PPLL_SS_TYPE_V2_P2PLL;
	अन्यथा
		BREAK_TO_DEBUGGER(); /* Unexpected PLL value!! */

	अगर ((enable == true) && (bp_params->percentage > 0)) अणु
		params.ucEnable = ATOM_ENABLE;

		params.usSpपढ़ोSpectrumPercentage =
				cpu_to_le16((uपूर्णांक16_t)(bp_params->percentage));
		params.usSpपढ़ोSpectrumStep =
				cpu_to_le16((uपूर्णांक16_t)(bp_params->ds.ds_frac_size));

		अगर (bp_params->flags.EXTERNAL_SS)
			params.ucSpपढ़ोSpectrumType |=
					ATOM_PPLL_SS_TYPE_V2_EXT_SPREAD;

		अगर (bp_params->flags.CENTER_SPREAD)
			params.ucSpपढ़ोSpectrumType |=
					ATOM_PPLL_SS_TYPE_V2_CENTRE_SPREAD;

		/* Both amounts need to be left shअगरted first beक्रमe bit
		 * comparison. Otherwise, the result will always be zero here
		 */
		params.usSpपढ़ोSpectrumAmount = cpu_to_le16((uपूर्णांक16_t)(
				((bp_params->ds.feedback_amount <<
						ATOM_PPLL_SS_AMOUNT_V2_FBDIV_SHIFT) &
						ATOM_PPLL_SS_AMOUNT_V2_FBDIV_MASK) |
						((bp_params->ds.nfrac_amount <<
								ATOM_PPLL_SS_AMOUNT_V2_NFRAC_SHIFT) &
								ATOM_PPLL_SS_AMOUNT_V2_NFRAC_MASK)));
	पूर्ण अन्यथा
		params.ucEnable = ATOM_DISABLE;

	अगर (EXEC_BIOS_CMD_TABLE(EnableSpपढ़ोSpectrumOnPPLL, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

अटल क्रमागत bp_result enable_spपढ़ो_spectrum_on_ppll_v3(
	काष्ठा bios_parser *bp,
	काष्ठा bp_spपढ़ो_spectrum_parameters *bp_params,
	bool enable)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	ENABLE_SPREAD_SPECTRUM_ON_PPLL_V3 params;

	स_रखो(&params, 0, माप(params));

	चयन (bp_params->pll_id) अणु
	हाल CLOCK_SOURCE_ID_PLL0:
		/* ATOM_PPLL_SS_TYPE_V3_P0PLL; this is pixel घड़ी only,
		 * not क्रम SI display घड़ी.
		 */
		params.ucSpपढ़ोSpectrumType = ATOM_PPLL_SS_TYPE_V3_DCPLL;
		अवरोध;
	हाल CLOCK_SOURCE_ID_PLL1:
		params.ucSpपढ़ोSpectrumType = ATOM_PPLL_SS_TYPE_V3_P1PLL;
		अवरोध;

	हाल CLOCK_SOURCE_ID_PLL2:
		params.ucSpपढ़ोSpectrumType = ATOM_PPLL_SS_TYPE_V3_P2PLL;
		अवरोध;

	हाल CLOCK_SOURCE_ID_DCPLL:
		params.ucSpपढ़ोSpectrumType = ATOM_PPLL_SS_TYPE_V3_DCPLL;
		अवरोध;

	शेष:
		BREAK_TO_DEBUGGER();
		/* Unexpected PLL value!! */
		वापस result;
	पूर्ण

	अगर (enable == true) अणु
		params.ucEnable = ATOM_ENABLE;

		params.usSpपढ़ोSpectrumAmountFrac =
				cpu_to_le16((uपूर्णांक16_t)(bp_params->ds_frac_amount));
		params.usSpपढ़ोSpectrumStep =
				cpu_to_le16((uपूर्णांक16_t)(bp_params->ds.ds_frac_size));

		अगर (bp_params->flags.EXTERNAL_SS)
			params.ucSpपढ़ोSpectrumType |=
					ATOM_PPLL_SS_TYPE_V3_EXT_SPREAD;
		अगर (bp_params->flags.CENTER_SPREAD)
			params.ucSpपढ़ोSpectrumType |=
					ATOM_PPLL_SS_TYPE_V3_CENTRE_SPREAD;

		/* Both amounts need to be left shअगरted first beक्रमe bit
		 * comparison. Otherwise, the result will always be zero here
		 */
		params.usSpपढ़ोSpectrumAmount = cpu_to_le16((uपूर्णांक16_t)(
				((bp_params->ds.feedback_amount <<
						ATOM_PPLL_SS_AMOUNT_V3_FBDIV_SHIFT) &
						ATOM_PPLL_SS_AMOUNT_V3_FBDIV_MASK) |
						((bp_params->ds.nfrac_amount <<
								ATOM_PPLL_SS_AMOUNT_V3_NFRAC_SHIFT) &
								ATOM_PPLL_SS_AMOUNT_V3_NFRAC_MASK)));
	पूर्ण अन्यथा
		params.ucEnable = ATOM_DISABLE;

	अगर (EXEC_BIOS_CMD_TABLE(EnableSpपढ़ोSpectrumOnPPLL, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

/*******************************************************************************
 ********************************************************************************
 **
 **                  ADJUST DISPLAY PLL
 **
 ********************************************************************************
 *******************************************************************************/

अटल क्रमागत bp_result adjust_display_pll_v2(
	काष्ठा bios_parser *bp,
	काष्ठा bp_adjust_pixel_घड़ी_parameters *bp_params);
अटल क्रमागत bp_result adjust_display_pll_v3(
	काष्ठा bios_parser *bp,
	काष्ठा bp_adjust_pixel_घड़ी_parameters *bp_params);

अटल व्योम init_adjust_display_pll(काष्ठा bios_parser *bp)
अणु
	चयन (BIOS_CMD_TABLE_PARA_REVISION(AdjustDisplayPll)) अणु
	हाल 2:
		bp->cmd_tbl.adjust_display_pll = adjust_display_pll_v2;
		अवरोध;
	हाल 3:
		bp->cmd_tbl.adjust_display_pll = adjust_display_pll_v3;
		अवरोध;
	शेष:
		dm_output_to_console("Don't have adjust_display_pll for v%d\n",
			 BIOS_CMD_TABLE_PARA_REVISION(AdjustDisplayPll));
		bp->cmd_tbl.adjust_display_pll = शून्य;
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत bp_result adjust_display_pll_v2(
	काष्ठा bios_parser *bp,
	काष्ठा bp_adjust_pixel_घड़ी_parameters *bp_params)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	ADJUST_DISPLAY_PLL_PS_ALLOCATION params = अणु 0 पूर्ण;

	/* We need to convert from KHz units पूर्णांकo 10KHz units and then convert
	 * output pixel घड़ी back 10KHz-->KHz */
	uपूर्णांक32_t pixel_घड़ी_10KHz_in = bp_params->pixel_घड़ी / 10;

	params.usPixelClock = cpu_to_le16((uपूर्णांक16_t)(pixel_घड़ी_10KHz_in));
	params.ucTransmitterID =
			bp->cmd_helper->encoder_id_to_atom(
					dal_graphics_object_id_get_encoder_id(
							bp_params->encoder_object_id));
	params.ucEncodeMode =
			(uपूर्णांक8_t)bp->cmd_helper->encoder_mode_bp_to_atom(
					bp_params->संकेत_type, false);

	अगर (EXEC_BIOS_CMD_TABLE(AdjustDisplayPll, params)) अणु
		/* Convert output pixel घड़ी back 10KHz-->KHz: multiply
		 * original pixel घड़ी in KHz by ratio
		 * [output pxlClk/input pxlClk] */
		uपूर्णांक64_t pixel_clk_10_khz_out =
				(uपूर्णांक64_t)le16_to_cpu(params.usPixelClock);
		uपूर्णांक64_t pixel_clk = (uपूर्णांक64_t)bp_params->pixel_घड़ी;

		अगर (pixel_घड़ी_10KHz_in != 0) अणु
			bp_params->adjusted_pixel_घड़ी =
					भाग_u64(pixel_clk * pixel_clk_10_khz_out,
							pixel_घड़ी_10KHz_in);
		पूर्ण अन्यथा अणु
			bp_params->adjusted_pixel_घड़ी = 0;
			BREAK_TO_DEBUGGER();
		पूर्ण

		result = BP_RESULT_OK;
	पूर्ण

	वापस result;
पूर्ण

अटल क्रमागत bp_result adjust_display_pll_v3(
	काष्ठा bios_parser *bp,
	काष्ठा bp_adjust_pixel_घड़ी_parameters *bp_params)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	ADJUST_DISPLAY_PLL_PS_ALLOCATION_V3 params;
	uपूर्णांक32_t pixel_clk_10_kHz_in = bp_params->pixel_घड़ी / 10;

	स_रखो(&params, 0, माप(params));

	/* We need to convert from KHz units पूर्णांकo 10KHz units and then convert
	 * output pixel घड़ी back 10KHz-->KHz */
	params.sInput.usPixelClock = cpu_to_le16((uपूर्णांक16_t)pixel_clk_10_kHz_in);
	params.sInput.ucTransmitterID =
			bp->cmd_helper->encoder_id_to_atom(
					dal_graphics_object_id_get_encoder_id(
							bp_params->encoder_object_id));
	params.sInput.ucEncodeMode =
			(uपूर्णांक8_t)bp->cmd_helper->encoder_mode_bp_to_atom(
					bp_params->संकेत_type, false);

	अगर (bp_params->ss_enable == true)
		params.sInput.ucDispPllConfig |= DISPPLL_CONFIG_SS_ENABLE;

	अगर (bp_params->संकेत_type == SIGNAL_TYPE_DVI_DUAL_LINK)
		params.sInput.ucDispPllConfig |= DISPPLL_CONFIG_DUAL_LINK;

	अगर (EXEC_BIOS_CMD_TABLE(AdjustDisplayPll, params)) अणु
		/* Convert output pixel घड़ी back 10KHz-->KHz: multiply
		 * original pixel घड़ी in KHz by ratio
		 * [output pxlClk/input pxlClk] */
		uपूर्णांक64_t pixel_clk_10_khz_out =
				(uपूर्णांक64_t)le32_to_cpu(params.sOutput.ulDispPllFreq);
		uपूर्णांक64_t pixel_clk = (uपूर्णांक64_t)bp_params->pixel_घड़ी;

		अगर (pixel_clk_10_kHz_in != 0) अणु
			bp_params->adjusted_pixel_घड़ी =
					भाग_u64(pixel_clk * pixel_clk_10_khz_out,
							pixel_clk_10_kHz_in);
		पूर्ण अन्यथा अणु
			bp_params->adjusted_pixel_घड़ी = 0;
			BREAK_TO_DEBUGGER();
		पूर्ण

		bp_params->reference_भागider = params.sOutput.ucRefDiv;
		bp_params->pixel_घड़ी_post_भागider = params.sOutput.ucPostDiv;

		result = BP_RESULT_OK;
	पूर्ण

	वापस result;
पूर्ण

/*******************************************************************************
 ********************************************************************************
 **
 **                  DAC ENCODER CONTROL
 **
 ********************************************************************************
 *******************************************************************************/

अटल क्रमागत bp_result dac1_encoder_control_v1(
	काष्ठा bios_parser *bp,
	bool enable,
	uपूर्णांक32_t pixel_घड़ी,
	uपूर्णांक8_t dac_standard);
अटल क्रमागत bp_result dac2_encoder_control_v1(
	काष्ठा bios_parser *bp,
	bool enable,
	uपूर्णांक32_t pixel_घड़ी,
	uपूर्णांक8_t dac_standard);

अटल व्योम init_dac_encoder_control(काष्ठा bios_parser *bp)
अणु
	चयन (BIOS_CMD_TABLE_PARA_REVISION(DAC1EncoderControl)) अणु
	हाल 1:
		bp->cmd_tbl.dac1_encoder_control = dac1_encoder_control_v1;
		अवरोध;
	शेष:
		bp->cmd_tbl.dac1_encoder_control = शून्य;
		अवरोध;
	पूर्ण
	चयन (BIOS_CMD_TABLE_PARA_REVISION(DAC2EncoderControl)) अणु
	हाल 1:
		bp->cmd_tbl.dac2_encoder_control = dac2_encoder_control_v1;
		अवरोध;
	शेष:
		bp->cmd_tbl.dac2_encoder_control = शून्य;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम dac_encoder_control_prepare_params(
	DAC_ENCODER_CONTROL_PS_ALLOCATION *params,
	bool enable,
	uपूर्णांक32_t pixel_घड़ी,
	uपूर्णांक8_t dac_standard)
अणु
	params->ucDacStandard = dac_standard;
	अगर (enable)
		params->ucAction = ATOM_ENABLE;
	अन्यथा
		params->ucAction = ATOM_DISABLE;

	/* We need to convert from KHz units पूर्णांकo 10KHz units
	 * it looks as अगर the TvControl करो not care about pixel घड़ी
	 */
	params->usPixelClock = cpu_to_le16((uपूर्णांक16_t)(pixel_घड़ी / 10));
पूर्ण

अटल क्रमागत bp_result dac1_encoder_control_v1(
	काष्ठा bios_parser *bp,
	bool enable,
	uपूर्णांक32_t pixel_घड़ी,
	uपूर्णांक8_t dac_standard)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	DAC_ENCODER_CONTROL_PS_ALLOCATION params;

	dac_encoder_control_prepare_params(
		&params,
		enable,
		pixel_घड़ी,
		dac_standard);

	अगर (EXEC_BIOS_CMD_TABLE(DAC1EncoderControl, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

अटल क्रमागत bp_result dac2_encoder_control_v1(
	काष्ठा bios_parser *bp,
	bool enable,
	uपूर्णांक32_t pixel_घड़ी,
	uपूर्णांक8_t dac_standard)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	DAC_ENCODER_CONTROL_PS_ALLOCATION params;

	dac_encoder_control_prepare_params(
		&params,
		enable,
		pixel_घड़ी,
		dac_standard);

	अगर (EXEC_BIOS_CMD_TABLE(DAC2EncoderControl, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

/*******************************************************************************
 ********************************************************************************
 **
 **                  DAC OUTPUT CONTROL
 **
 ********************************************************************************
 *******************************************************************************/
अटल क्रमागत bp_result dac1_output_control_v1(
	काष्ठा bios_parser *bp,
	bool enable);
अटल क्रमागत bp_result dac2_output_control_v1(
	काष्ठा bios_parser *bp,
	bool enable);

अटल व्योम init_dac_output_control(काष्ठा bios_parser *bp)
अणु
	चयन (BIOS_CMD_TABLE_PARA_REVISION(DAC1OutputControl)) अणु
	हाल 1:
		bp->cmd_tbl.dac1_output_control = dac1_output_control_v1;
		अवरोध;
	शेष:
		bp->cmd_tbl.dac1_output_control = शून्य;
		अवरोध;
	पूर्ण
	चयन (BIOS_CMD_TABLE_PARA_REVISION(DAC2OutputControl)) अणु
	हाल 1:
		bp->cmd_tbl.dac2_output_control = dac2_output_control_v1;
		अवरोध;
	शेष:
		bp->cmd_tbl.dac2_output_control = शून्य;
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत bp_result dac1_output_control_v1(
	काष्ठा bios_parser *bp, bool enable)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	DISPLAY_DEVICE_OUTPUT_CONTROL_PS_ALLOCATION params;

	अगर (enable)
		params.ucAction = ATOM_ENABLE;
	अन्यथा
		params.ucAction = ATOM_DISABLE;

	अगर (EXEC_BIOS_CMD_TABLE(DAC1OutputControl, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

अटल क्रमागत bp_result dac2_output_control_v1(
	काष्ठा bios_parser *bp, bool enable)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	DISPLAY_DEVICE_OUTPUT_CONTROL_PS_ALLOCATION params;

	अगर (enable)
		params.ucAction = ATOM_ENABLE;
	अन्यथा
		params.ucAction = ATOM_DISABLE;

	अगर (EXEC_BIOS_CMD_TABLE(DAC2OutputControl, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

/*******************************************************************************
 ********************************************************************************
 **
 **                  SET CRTC TIMING
 **
 ********************************************************************************
 *******************************************************************************/

अटल क्रमागत bp_result set_crtc_using_dtd_timing_v3(
	काष्ठा bios_parser *bp,
	काष्ठा bp_hw_crtc_timing_parameters *bp_params);
अटल क्रमागत bp_result set_crtc_timing_v1(
	काष्ठा bios_parser *bp,
	काष्ठा bp_hw_crtc_timing_parameters *bp_params);

अटल व्योम init_set_crtc_timing(काष्ठा bios_parser *bp)
अणु
	uपूर्णांक32_t dtd_version =
			BIOS_CMD_TABLE_PARA_REVISION(SetCRTC_UsingDTDTiming);
	अगर (dtd_version > 2)
		चयन (dtd_version) अणु
		हाल 3:
			bp->cmd_tbl.set_crtc_timing =
					set_crtc_using_dtd_timing_v3;
			अवरोध;
		शेष:
			dm_output_to_console("Don't have set_crtc_timing for dtd v%d\n",
				 dtd_version);
			bp->cmd_tbl.set_crtc_timing = शून्य;
			अवरोध;
		पूर्ण
	अन्यथा
		चयन (BIOS_CMD_TABLE_PARA_REVISION(SetCRTC_Timing)) अणु
		हाल 1:
			bp->cmd_tbl.set_crtc_timing = set_crtc_timing_v1;
			अवरोध;
		शेष:
			dm_output_to_console("Don't have set_crtc_timing for v%d\n",
				 BIOS_CMD_TABLE_PARA_REVISION(SetCRTC_Timing));
			bp->cmd_tbl.set_crtc_timing = शून्य;
			अवरोध;
		पूर्ण
पूर्ण

अटल क्रमागत bp_result set_crtc_timing_v1(
	काष्ठा bios_parser *bp,
	काष्ठा bp_hw_crtc_timing_parameters *bp_params)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	SET_CRTC_TIMING_PARAMETERS_PS_ALLOCATION params = अणु0पूर्ण;
	uपूर्णांक8_t atom_controller_id;

	अगर (bp->cmd_helper->controller_id_to_atom(
			bp_params->controller_id, &atom_controller_id))
		params.ucCRTC = atom_controller_id;

	params.usH_Total = cpu_to_le16((uपूर्णांक16_t)(bp_params->h_total));
	params.usH_Disp = cpu_to_le16((uपूर्णांक16_t)(bp_params->h_addressable));
	params.usH_SyncStart = cpu_to_le16((uपूर्णांक16_t)(bp_params->h_sync_start));
	params.usH_SyncWidth = cpu_to_le16((uपूर्णांक16_t)(bp_params->h_sync_width));
	params.usV_Total = cpu_to_le16((uपूर्णांक16_t)(bp_params->v_total));
	params.usV_Disp = cpu_to_le16((uपूर्णांक16_t)(bp_params->v_addressable));
	params.usV_SyncStart =
			cpu_to_le16((uपूर्णांक16_t)(bp_params->v_sync_start));
	params.usV_SyncWidth =
			cpu_to_le16((uपूर्णांक16_t)(bp_params->v_sync_width));

	/* VBIOS करोes not expect any value except zero पूर्णांकo this call, क्रम
	 * underscan use another entry ProgramOverscan call but when mode
	 * 1776x1000 with the overscan 72x44 .e.i. 1920x1080 @30 DAL2 is ok,
	 * but when same ,but 60 Hz there is corruption
	 * DAL1 करोes not allow the mode 1776x1000@60
	 */
	params.ucOverscanRight = (uपूर्णांक8_t)bp_params->h_overscan_right;
	params.ucOverscanLeft = (uपूर्णांक8_t)bp_params->h_overscan_left;
	params.ucOverscanBottom = (uपूर्णांक8_t)bp_params->v_overscan_bottom;
	params.ucOverscanTop = (uपूर्णांक8_t)bp_params->v_overscan_top;

	अगर (0 == bp_params->flags.HSYNC_POSITIVE_POLARITY)
		params.susModeMiscInfo.usAccess =
				cpu_to_le16(le16_to_cpu(params.susModeMiscInfo.usAccess) | ATOM_HSYNC_POLARITY);

	अगर (0 == bp_params->flags.VSYNC_POSITIVE_POLARITY)
		params.susModeMiscInfo.usAccess =
				cpu_to_le16(le16_to_cpu(params.susModeMiscInfo.usAccess) | ATOM_VSYNC_POLARITY);

	अगर (bp_params->flags.INTERLACE) अणु
		params.susModeMiscInfo.usAccess =
				cpu_to_le16(le16_to_cpu(params.susModeMiscInfo.usAccess) | ATOM_INTERLACE);

		/* original DAL code has this condition to apply tis क्रम
		 * non-TV/CV only due to complex MV testing क्रम possible
		 * impact
		 * अगर (pACParameters->संकेत != SignalType_YPbPr &&
		 *  pACParameters->संकेत != SignalType_Composite &&
		 *  pACParameters->संकेत != SignalType_SVideo)
		 */
		/* HW will deduct 0.5 line from 2nd feild.
		 * i.e. क्रम 1080i, it is 2 lines क्रम 1st field, 2.5
		 * lines क्रम the 2nd feild. we need input as 5 instead
		 * of 4, but it is 4 either from Edid data
		 * (spec CEA 861) or CEA timing table.
		 */
		params.usV_SyncStart =
				cpu_to_le16((uपूर्णांक16_t)(bp_params->v_sync_start + 1));
	पूर्ण

	अगर (bp_params->flags.HORZ_COUNT_BY_TWO)
		params.susModeMiscInfo.usAccess =
				cpu_to_le16(le16_to_cpu(params.susModeMiscInfo.usAccess) | ATOM_DOUBLE_CLOCK_MODE);

	अगर (EXEC_BIOS_CMD_TABLE(SetCRTC_Timing, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

अटल क्रमागत bp_result set_crtc_using_dtd_timing_v3(
	काष्ठा bios_parser *bp,
	काष्ठा bp_hw_crtc_timing_parameters *bp_params)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;
	SET_CRTC_USING_DTD_TIMING_PARAMETERS params = अणु0पूर्ण;
	uपूर्णांक8_t atom_controller_id;

	अगर (bp->cmd_helper->controller_id_to_atom(
			bp_params->controller_id, &atom_controller_id))
		params.ucCRTC = atom_controller_id;

	/* bios usH_Size wants h addressable size */
	params.usH_Size = cpu_to_le16((uपूर्णांक16_t)bp_params->h_addressable);
	/* bios usH_Blanking_Time wants borders included in blanking */
	params.usH_Blanking_Time =
			cpu_to_le16((uपूर्णांक16_t)(bp_params->h_total - bp_params->h_addressable));
	/* bios usV_Size wants v addressable size */
	params.usV_Size = cpu_to_le16((uपूर्णांक16_t)bp_params->v_addressable);
	/* bios usV_Blanking_Time wants borders included in blanking */
	params.usV_Blanking_Time =
			cpu_to_le16((uपूर्णांक16_t)(bp_params->v_total - bp_params->v_addressable));
	/* bios usHSyncOffset is the offset from the end of h addressable,
	 * our horizontalSyncStart is the offset from the beginning
	 * of h addressable */
	params.usH_SyncOffset =
			cpu_to_le16((uपूर्णांक16_t)(bp_params->h_sync_start - bp_params->h_addressable));
	params.usH_SyncWidth = cpu_to_le16((uपूर्णांक16_t)bp_params->h_sync_width);
	/* bios usHSyncOffset is the offset from the end of v addressable,
	 * our verticalSyncStart is the offset from the beginning of
	 * v addressable */
	params.usV_SyncOffset =
			cpu_to_le16((uपूर्णांक16_t)(bp_params->v_sync_start - bp_params->v_addressable));
	params.usV_SyncWidth = cpu_to_le16((uपूर्णांक16_t)bp_params->v_sync_width);

	/* we assume that overscan from original timing करोes not get bigger
	 * than 255
	 * we will program all the borders in the Set CRTC Overscan call below
	 */

	अगर (0 == bp_params->flags.HSYNC_POSITIVE_POLARITY)
		params.susModeMiscInfo.usAccess =
				cpu_to_le16(le16_to_cpu(params.susModeMiscInfo.usAccess) | ATOM_HSYNC_POLARITY);

	अगर (0 == bp_params->flags.VSYNC_POSITIVE_POLARITY)
		params.susModeMiscInfo.usAccess =
				cpu_to_le16(le16_to_cpu(params.susModeMiscInfo.usAccess) | ATOM_VSYNC_POLARITY);

	अगर (bp_params->flags.INTERLACE)	अणु
		params.susModeMiscInfo.usAccess =
				cpu_to_le16(le16_to_cpu(params.susModeMiscInfo.usAccess) | ATOM_INTERLACE);

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
			le16_add_cpu(&params.usV_SyncOffset, 1);
		पूर्ण
	पूर्ण

	अगर (bp_params->flags.HORZ_COUNT_BY_TWO)
		params.susModeMiscInfo.usAccess =
				cpu_to_le16(le16_to_cpu(params.susModeMiscInfo.usAccess) | ATOM_DOUBLE_CLOCK_MODE);

	अगर (EXEC_BIOS_CMD_TABLE(SetCRTC_UsingDTDTiming, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

/*******************************************************************************
 ********************************************************************************
 **
 **                  ENABLE CRTC
 **
 ********************************************************************************
 *******************************************************************************/

अटल क्रमागत bp_result enable_crtc_v1(
	काष्ठा bios_parser *bp,
	क्रमागत controller_id controller_id,
	bool enable);

अटल व्योम init_enable_crtc(काष्ठा bios_parser *bp)
अणु
	चयन (BIOS_CMD_TABLE_PARA_REVISION(EnableCRTC)) अणु
	हाल 1:
		bp->cmd_tbl.enable_crtc = enable_crtc_v1;
		अवरोध;
	शेष:
		dm_output_to_console("Don't have enable_crtc for v%d\n",
			 BIOS_CMD_TABLE_PARA_REVISION(EnableCRTC));
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
	ENABLE_CRTC_PARAMETERS params = अणु0पूर्ण;
	uपूर्णांक8_t id;

	अगर (bp->cmd_helper->controller_id_to_atom(controller_id, &id))
		params.ucCRTC = id;
	अन्यथा
		वापस BP_RESULT_BADINPUT;

	अगर (enable)
		params.ucEnable = ATOM_ENABLE;
	अन्यथा
		params.ucEnable = ATOM_DISABLE;

	अगर (EXEC_BIOS_CMD_TABLE(EnableCRTC, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

/*******************************************************************************
 ********************************************************************************
 **
 **                  ENABLE CRTC MEM REQ
 **
 ********************************************************************************
 *******************************************************************************/

अटल क्रमागत bp_result enable_crtc_mem_req_v1(
	काष्ठा bios_parser *bp,
	क्रमागत controller_id controller_id,
	bool enable);

अटल व्योम init_enable_crtc_mem_req(काष्ठा bios_parser *bp)
अणु
	चयन (BIOS_CMD_TABLE_PARA_REVISION(EnableCRTCMemReq)) अणु
	हाल 1:
		bp->cmd_tbl.enable_crtc_mem_req = enable_crtc_mem_req_v1;
		अवरोध;
	शेष:
		bp->cmd_tbl.enable_crtc_mem_req = शून्य;
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत bp_result enable_crtc_mem_req_v1(
	काष्ठा bios_parser *bp,
	क्रमागत controller_id controller_id,
	bool enable)
अणु
	bool result = BP_RESULT_BADINPUT;
	ENABLE_CRTC_PARAMETERS params = अणु0पूर्ण;
	uपूर्णांक8_t id;

	अगर (bp->cmd_helper->controller_id_to_atom(controller_id, &id)) अणु
		params.ucCRTC = id;

		अगर (enable)
			params.ucEnable = ATOM_ENABLE;
		अन्यथा
			params.ucEnable = ATOM_DISABLE;

		अगर (EXEC_BIOS_CMD_TABLE(EnableCRTCMemReq, params))
			result = BP_RESULT_OK;
		अन्यथा
			result = BP_RESULT_FAILURE;
	पूर्ण

	वापस result;
पूर्ण

/*******************************************************************************
 ********************************************************************************
 **
 **                  DISPLAY PLL
 **
 ********************************************************************************
 *******************************************************************************/

अटल क्रमागत bp_result program_घड़ी_v5(
	काष्ठा bios_parser *bp,
	काष्ठा bp_pixel_घड़ी_parameters *bp_params);
अटल क्रमागत bp_result program_घड़ी_v6(
	काष्ठा bios_parser *bp,
	काष्ठा bp_pixel_घड़ी_parameters *bp_params);

अटल व्योम init_program_घड़ी(काष्ठा bios_parser *bp)
अणु
	चयन (BIOS_CMD_TABLE_PARA_REVISION(SetPixelClock)) अणु
	हाल 5:
		bp->cmd_tbl.program_घड़ी = program_घड़ी_v5;
		अवरोध;
	हाल 6:
		bp->cmd_tbl.program_घड़ी = program_घड़ी_v6;
		अवरोध;
	शेष:
		dm_output_to_console("Don't have program_clock for v%d\n",
			 BIOS_CMD_TABLE_PARA_REVISION(SetPixelClock));
		bp->cmd_tbl.program_घड़ी = शून्य;
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत bp_result program_घड़ी_v5(
	काष्ठा bios_parser *bp,
	काष्ठा bp_pixel_घड़ी_parameters *bp_params)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;

	SET_PIXEL_CLOCK_PS_ALLOCATION_V5 params;
	uपूर्णांक32_t atom_pll_id;

	स_रखो(&params, 0, माप(params));
	अगर (!bp->cmd_helper->घड़ी_source_id_to_atom(
			bp_params->pll_id, &atom_pll_id)) अणु
		BREAK_TO_DEBUGGER(); /* Invalid Inpute!! */
		वापस BP_RESULT_BADINPUT;
	पूर्ण

	/* We need to convert from KHz units पूर्णांकo 10KHz units */
	params.sPCLKInput.ucPpll = (uपूर्णांक8_t) atom_pll_id;
	params.sPCLKInput.usPixelClock =
			cpu_to_le16((uपूर्णांक16_t) (bp_params->target_pixel_घड़ी_100hz / 100));
	params.sPCLKInput.ucCRTC = (uपूर्णांक8_t) ATOM_CRTC_INVALID;

	अगर (bp_params->flags.SET_EXTERNAL_REF_DIV_SRC)
		params.sPCLKInput.ucMiscInfo |= PIXEL_CLOCK_MISC_REF_DIV_SRC;

	अगर (EXEC_BIOS_CMD_TABLE(SetPixelClock, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

अटल क्रमागत bp_result program_घड़ी_v6(
	काष्ठा bios_parser *bp,
	काष्ठा bp_pixel_घड़ी_parameters *bp_params)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;

	SET_PIXEL_CLOCK_PS_ALLOCATION_V6 params;
	uपूर्णांक32_t atom_pll_id;

	स_रखो(&params, 0, माप(params));

	अगर (!bp->cmd_helper->घड़ी_source_id_to_atom(
			bp_params->pll_id, &atom_pll_id)) अणु
		BREAK_TO_DEBUGGER(); /*Invalid Input!!*/
		वापस BP_RESULT_BADINPUT;
	पूर्ण

	/* We need to convert from KHz units पूर्णांकo 10KHz units */
	params.sPCLKInput.ucPpll = (uपूर्णांक8_t)atom_pll_id;
	params.sPCLKInput.ulDispEngClkFreq =
			cpu_to_le32(bp_params->target_pixel_घड़ी_100hz / 100);

	अगर (bp_params->flags.SET_EXTERNAL_REF_DIV_SRC)
		params.sPCLKInput.ucMiscInfo |= PIXEL_CLOCK_MISC_REF_DIV_SRC;

	अगर (bp_params->flags.SET_DISPCLK_DFS_BYPASS)
		params.sPCLKInput.ucMiscInfo |= PIXEL_CLOCK_V6_MISC_DPREFCLK_BYPASS;

	अगर (EXEC_BIOS_CMD_TABLE(SetPixelClock, params)) अणु
		/* True display घड़ी is वापसed by VBIOS अगर DFS bypass
		 * is enabled. */
		bp_params->dfs_bypass_display_घड़ी =
				(uपूर्णांक32_t)(le32_to_cpu(params.sPCLKInput.ulDispEngClkFreq) * 10);
		result = BP_RESULT_OK;
	पूर्ण

	वापस result;
पूर्ण

/*******************************************************************************
 ********************************************************************************
 **
 **                  EXTERNAL ENCODER CONTROL
 **
 ********************************************************************************
 *******************************************************************************/

अटल क्रमागत bp_result बाह्यal_encoder_control_v3(
	काष्ठा bios_parser *bp,
	काष्ठा bp_बाह्यal_encoder_control *cntl);

अटल व्योम init_बाह्यal_encoder_control(
	काष्ठा bios_parser *bp)
अणु
	चयन (BIOS_CMD_TABLE_PARA_REVISION(ExternalEncoderControl)) अणु
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
	क्रमागत bp_result result = BP_RESULT_FAILURE;

	/* we need use _PS_Alloc काष्ठा */
	EXTERNAL_ENCODER_CONTROL_PS_ALLOCATION_V3 params;
	EXTERNAL_ENCODER_CONTROL_PARAMETERS_V3 *cntl_params;
	काष्ठा graphics_object_id encoder;
	bool is_input_संकेत_dp = false;

	स_रखो(&params, 0, माप(params));

	cntl_params = &params.sExtEncoder;

	encoder = cntl->encoder_id;

	/* check अगर encoder supports बाह्यal encoder control table */
	चयन (dal_graphics_object_id_get_encoder_id(encoder)) अणु
	हाल ENCODER_ID_EXTERNAL_NUTMEG:
	हाल ENCODER_ID_EXTERNAL_TRAVIS:
		is_input_संकेत_dp = true;
		अवरोध;

	शेष:
		BREAK_TO_DEBUGGER();
		वापस BP_RESULT_BADINPUT;
	पूर्ण

	/* Fill inक्रमmation based on the action
	 *
	 * Bit[6:4]: indicate बाह्यal encoder, applied to all functions.
	 * =0: बाह्यal encoder1, mapped to बाह्यal encoder क्रमागत id1
	 * =1: बाह्यal encoder2, mapped to बाह्यal encoder क्रमागत id2
	 *
	 * क्रमागत ObjectEnumId
	 * अणु
	 *  EnumId_Unknown = 0,
	 *  EnumId_1,
	 *  EnumId_2,
	 * पूर्ण;
	 */
	cntl_params->ucConfig = (uपूर्णांक8_t)((encoder.क्रमागत_id - 1) << 4);

	चयन (cntl->action) अणु
	हाल EXTERNAL_ENCODER_CONTROL_INIT:
		/* output display connector type. Only valid in encoder
		 * initialization */
		cntl_params->usConnectorId =
				cpu_to_le16((uपूर्णांक16_t)cntl->connector_obj_id.id);
		अवरोध;
	हाल EXTERNAL_ENCODER_CONTROL_SETUP:
		/* EXTERNAL_ENCODER_CONTROL_PARAMETERS_V3 pixel घड़ी unit in
		 * 10KHz
		 * output display device pixel घड़ी frequency in unit of 10KHz.
		 * Only valid in setup and enableoutput
		 */
		cntl_params->usPixelClock =
				cpu_to_le16((uपूर्णांक16_t)(cntl->pixel_घड़ी / 10));
		/* Indicate display output संकेत type drive by बाह्यal
		 * encoder, only valid in setup and enableoutput */
		cntl_params->ucEncoderMode =
				(uपूर्णांक8_t)bp->cmd_helper->encoder_mode_bp_to_atom(
						cntl->संकेत, false);

		अगर (is_input_संकेत_dp) अणु
			/* Bit[0]: indicate link rate, =1: 2.7Ghz, =0: 1.62Ghz,
			 * only valid in encoder setup with DP mode. */
			अगर (LINK_RATE_HIGH == cntl->link_rate)
				cntl_params->ucConfig |= 1;
			/* output color depth Indicate encoder data bpc क्रमmat
			 * in DP mode, only valid in encoder setup in DP mode.
			 */
			cntl_params->ucBitPerColor =
					(uपूर्णांक8_t)(cntl->color_depth);
		पूर्ण
		/* Indicate how many lanes used by बाह्यal encoder, only valid
		 * in encoder setup and enableoutput. */
		cntl_params->ucLaneNum = (uपूर्णांक8_t)(cntl->lanes_number);
		अवरोध;
	हाल EXTERNAL_ENCODER_CONTROL_ENABLE:
		cntl_params->usPixelClock =
				cpu_to_le16((uपूर्णांक16_t)(cntl->pixel_घड़ी / 10));
		cntl_params->ucEncoderMode =
				(uपूर्णांक8_t)bp->cmd_helper->encoder_mode_bp_to_atom(
						cntl->संकेत, false);
		cntl_params->ucLaneNum = (uपूर्णांक8_t)cntl->lanes_number;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	cntl_params->ucAction = (uपूर्णांक8_t)cntl->action;

	अगर (EXEC_BIOS_CMD_TABLE(ExternalEncoderControl, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

/*******************************************************************************
 ********************************************************************************
 **
 **                  ENABLE DISPLAY POWER GATING
 **
 ********************************************************************************
 *******************************************************************************/

अटल क्रमागत bp_result enable_disp_घातer_gating_v2_1(
	काष्ठा bios_parser *bp,
	क्रमागत controller_id crtc_id,
	क्रमागत bp_pipe_control_action action);

अटल व्योम init_enable_disp_घातer_gating(
	काष्ठा bios_parser *bp)
अणु
	चयन (BIOS_CMD_TABLE_PARA_REVISION(EnableDispPowerGating)) अणु
	हाल 1:
		bp->cmd_tbl.enable_disp_घातer_gating =
				enable_disp_घातer_gating_v2_1;
		अवरोध;
	शेष:
		dm_output_to_console("Don't enable_disp_power_gating enable_crtc for v%d\n",
			 BIOS_CMD_TABLE_PARA_REVISION(EnableDispPowerGating));
		bp->cmd_tbl.enable_disp_घातer_gating = शून्य;
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत bp_result enable_disp_घातer_gating_v2_1(
	काष्ठा bios_parser *bp,
	क्रमागत controller_id crtc_id,
	क्रमागत bp_pipe_control_action action)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;

	ENABLE_DISP_POWER_GATING_PS_ALLOCATION params = अणु0पूर्ण;
	uपूर्णांक8_t atom_crtc_id;

	अगर (bp->cmd_helper->controller_id_to_atom(crtc_id, &atom_crtc_id))
		params.ucDispPipeId = atom_crtc_id;
	अन्यथा
		वापस BP_RESULT_BADINPUT;

	params.ucEnable =
			bp->cmd_helper->disp_घातer_gating_action_to_atom(action);

	अगर (EXEC_BIOS_CMD_TABLE(EnableDispPowerGating, params))
		result = BP_RESULT_OK;

	वापस result;
पूर्ण

/*******************************************************************************
 ********************************************************************************
 **
 **                  SET DCE CLOCK
 **
 ********************************************************************************
 *******************************************************************************/
अटल क्रमागत bp_result set_dce_घड़ी_v2_1(
	काष्ठा bios_parser *bp,
	काष्ठा bp_set_dce_घड़ी_parameters *bp_params);

अटल व्योम init_set_dce_घड़ी(काष्ठा bios_parser *bp)
अणु
	चयन (BIOS_CMD_TABLE_PARA_REVISION(SetDCEClock)) अणु
	हाल 1:
		bp->cmd_tbl.set_dce_घड़ी = set_dce_घड़ी_v2_1;
		अवरोध;
	शेष:
		dm_output_to_console("Don't have set_dce_clock for v%d\n",
			 BIOS_CMD_TABLE_PARA_REVISION(SetDCEClock));
		bp->cmd_tbl.set_dce_घड़ी = शून्य;
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत bp_result set_dce_घड़ी_v2_1(
	काष्ठा bios_parser *bp,
	काष्ठा bp_set_dce_घड़ी_parameters *bp_params)
अणु
	क्रमागत bp_result result = BP_RESULT_FAILURE;

	SET_DCE_CLOCK_PS_ALLOCATION_V2_1 params;
	uपूर्णांक32_t atom_pll_id;
	uपूर्णांक32_t atom_घड़ी_प्रकारype;
	स्थिर काष्ठा command_table_helper *cmd = bp->cmd_helper;

	स_रखो(&params, 0, माप(params));

	अगर (!cmd->घड़ी_source_id_to_atom(bp_params->pll_id, &atom_pll_id) ||
			!cmd->dc_घड़ी_प्रकारype_to_atom(bp_params->घड़ी_प्रकारype, &atom_घड़ी_प्रकारype))
		वापस BP_RESULT_BADINPUT;

	params.asParam.ucDCEClkSrc  = atom_pll_id;
	params.asParam.ucDCEClkType = atom_घड़ी_प्रकारype;

	अगर (bp_params->घड़ी_प्रकारype == DCECLOCK_TYPE_DPREFCLK) अणु
		अगर (bp_params->flags.USE_GENLOCK_AS_SOURCE_FOR_DPREFCLK)
			params.asParam.ucDCEClkFlag |= DCE_CLOCK_FLAG_PLL_REFCLK_SRC_GENLK;

		अगर (bp_params->flags.USE_PCIE_AS_SOURCE_FOR_DPREFCLK)
			params.asParam.ucDCEClkFlag |= DCE_CLOCK_FLAG_PLL_REFCLK_SRC_PCIE;

		अगर (bp_params->flags.USE_XTALIN_AS_SOURCE_FOR_DPREFCLK)
			params.asParam.ucDCEClkFlag |= DCE_CLOCK_FLAG_PLL_REFCLK_SRC_XTALIN;

		अगर (bp_params->flags.USE_GENERICA_AS_SOURCE_FOR_DPREFCLK)
			params.asParam.ucDCEClkFlag |= DCE_CLOCK_FLAG_PLL_REFCLK_SRC_GENERICA;
	पूर्ण
	अन्यथा
		/* only program घड़ी frequency अगर display घड़ी is used; VBIOS will program DPREFCLK */
		/* We need to convert from KHz units पूर्णांकo 10KHz units */
		params.asParam.ulDCEClkFreq = cpu_to_le32(bp_params->target_घड़ी_frequency / 10);

	अगर (EXEC_BIOS_CMD_TABLE(SetDCEClock, params)) अणु
		/* Convert from 10KHz units back to KHz */
		bp_params->target_घड़ी_frequency = le32_to_cpu(params.asParam.ulDCEClkFreq) * 10;
		result = BP_RESULT_OK;
	पूर्ण

	वापस result;
पूर्ण
