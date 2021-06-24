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

#समावेश "atom.h"

#समावेश "include/bios_parser_types.h"

#समावेश "../command_table_helper2.h"

अटल uपूर्णांक8_t phy_id_to_atom(क्रमागत transmitter t)
अणु
	uपूर्णांक8_t atom_phy_id;

	चयन (t) अणु
	हाल TRANSMITTER_UNIPHY_A:
		atom_phy_id = ATOM_PHY_ID_UNIPHYA;
		अवरोध;
	हाल TRANSMITTER_UNIPHY_B:
		atom_phy_id = ATOM_PHY_ID_UNIPHYB;
		अवरोध;
	हाल TRANSMITTER_UNIPHY_C:
		atom_phy_id = ATOM_PHY_ID_UNIPHYC;
		अवरोध;
	हाल TRANSMITTER_UNIPHY_D:
		atom_phy_id = ATOM_PHY_ID_UNIPHYD;
		अवरोध;
	हाल TRANSMITTER_UNIPHY_E:
		atom_phy_id = ATOM_PHY_ID_UNIPHYE;
		अवरोध;
	हाल TRANSMITTER_UNIPHY_F:
		atom_phy_id = ATOM_PHY_ID_UNIPHYF;
		अवरोध;
	हाल TRANSMITTER_UNIPHY_G:
		atom_phy_id = ATOM_PHY_ID_UNIPHYG;
		अवरोध;
	शेष:
		atom_phy_id = ATOM_PHY_ID_UNIPHYA;
		अवरोध;
	पूर्ण
	वापस atom_phy_id;
पूर्ण

अटल uपूर्णांक8_t संकेत_type_to_atom_dig_mode(क्रमागत संकेत_type s)
अणु
	uपूर्णांक8_t atom_dig_mode = ATOM_TRANSMITTER_DIGMODE_V6_DP;

	चयन (s) अणु
	हाल SIGNAL_TYPE_DISPLAY_PORT:
	हाल SIGNAL_TYPE_EDP:
		atom_dig_mode = ATOM_TRANSMITTER_DIGMODE_V6_DP;
		अवरोध;
	हाल SIGNAL_TYPE_DVI_SINGLE_LINK:
	हाल SIGNAL_TYPE_DVI_DUAL_LINK:
		atom_dig_mode = ATOM_TRANSMITTER_DIGMODE_V6_DVI;
		अवरोध;
	हाल SIGNAL_TYPE_HDMI_TYPE_A:
		atom_dig_mode = ATOM_TRANSMITTER_DIGMODE_V6_HDMI;
		अवरोध;
	हाल SIGNAL_TYPE_DISPLAY_PORT_MST:
		atom_dig_mode = ATOM_TRANSMITTER_DIGMODE_V6_DP_MST;
		अवरोध;
	शेष:
		atom_dig_mode = ATOM_TRANSMITTER_DIGMODE_V6_DVI;
		अवरोध;
	पूर्ण

	वापस atom_dig_mode;
पूर्ण

अटल uपूर्णांक8_t घड़ी_source_id_to_atom_phy_clk_src_id(
		क्रमागत घड़ी_source_id id)
अणु
	uपूर्णांक8_t atom_phy_clk_src_id = 0;

	चयन (id) अणु
	हाल CLOCK_SOURCE_ID_PLL0:
		atom_phy_clk_src_id = ATOM_TRANSMITTER_CONFIG_V5_P0PLL;
		अवरोध;
	हाल CLOCK_SOURCE_ID_PLL1:
		atom_phy_clk_src_id = ATOM_TRANSMITTER_CONFIG_V5_P1PLL;
		अवरोध;
	हाल CLOCK_SOURCE_ID_PLL2:
		atom_phy_clk_src_id = ATOM_TRANSMITTER_CONFIG_V5_P2PLL;
		अवरोध;
	हाल CLOCK_SOURCE_ID_EXTERNAL:
		atom_phy_clk_src_id = ATOM_TRANSMITTER_CONFIG_V5_REFCLK_SRC_EXT;
		अवरोध;
	शेष:
		atom_phy_clk_src_id = ATOM_TRANSMITTER_CONFIG_V5_P1PLL;
		अवरोध;
	पूर्ण

	वापस atom_phy_clk_src_id >> 2;
पूर्ण

अटल uपूर्णांक8_t hpd_sel_to_atom(क्रमागत hpd_source_id id)
अणु
	uपूर्णांक8_t atom_hpd_sel = 0;

	चयन (id) अणु
	हाल HPD_SOURCEID1:
		atom_hpd_sel = ATOM_TRANSMITTER_V6_HPD1_SEL;
		अवरोध;
	हाल HPD_SOURCEID2:
		atom_hpd_sel = ATOM_TRANSMITTER_V6_HPD2_SEL;
		अवरोध;
	हाल HPD_SOURCEID3:
		atom_hpd_sel = ATOM_TRANSMITTER_V6_HPD3_SEL;
		अवरोध;
	हाल HPD_SOURCEID4:
		atom_hpd_sel = ATOM_TRANSMITTER_V6_HPD4_SEL;
		अवरोध;
	हाल HPD_SOURCEID5:
		atom_hpd_sel = ATOM_TRANSMITTER_V6_HPD5_SEL;
		अवरोध;
	हाल HPD_SOURCEID6:
		atom_hpd_sel = ATOM_TRANSMITTER_V6_HPD6_SEL;
		अवरोध;
	हाल HPD_SOURCEID_UNKNOWN:
	शेष:
		atom_hpd_sel = 0;
		अवरोध;
	पूर्ण
	वापस atom_hpd_sel;
पूर्ण

अटल uपूर्णांक8_t dig_encoder_sel_to_atom(क्रमागत engine_id id)
अणु
	/* On any ASIC after DCE80, we manually program the DIG_FE
	 * selection (see connect_dig_be_to_fe function of the link
	 * encoder), so translation should always वापस 0 (no FE).
	 */

	वापस 0;
पूर्ण

अटल bool घड़ी_source_id_to_atom(
	क्रमागत घड़ी_source_id id,
	uपूर्णांक32_t *atom_pll_id)
अणु
	bool result = true;

	अगर (atom_pll_id != शून्य)
		चयन (id) अणु
		हाल CLOCK_SOURCE_COMBO_PHY_PLL0:
			*atom_pll_id = ATOM_COMBOPHY_PLL0;
			अवरोध;
		हाल CLOCK_SOURCE_COMBO_PHY_PLL1:
			*atom_pll_id = ATOM_COMBOPHY_PLL1;
			अवरोध;
		हाल CLOCK_SOURCE_COMBO_PHY_PLL2:
			*atom_pll_id = ATOM_COMBOPHY_PLL2;
			अवरोध;
		हाल CLOCK_SOURCE_COMBO_PHY_PLL3:
			*atom_pll_id = ATOM_COMBOPHY_PLL3;
			अवरोध;
		हाल CLOCK_SOURCE_COMBO_PHY_PLL4:
			*atom_pll_id = ATOM_COMBOPHY_PLL4;
			अवरोध;
		हाल CLOCK_SOURCE_COMBO_PHY_PLL5:
			*atom_pll_id = ATOM_COMBOPHY_PLL5;
			अवरोध;
		हाल CLOCK_SOURCE_COMBO_DISPLAY_PLL0:
			*atom_pll_id = ATOM_PPLL0;
			अवरोध;
		हाल CLOCK_SOURCE_ID_DFS:
			*atom_pll_id = ATOM_GCK_DFS;
			अवरोध;
		हाल CLOCK_SOURCE_ID_VCE:
			*atom_pll_id = ATOM_DP_DTO;
			अवरोध;
		हाल CLOCK_SOURCE_ID_DP_DTO:
			*atom_pll_id = ATOM_DP_DTO;
			अवरोध;
		हाल CLOCK_SOURCE_ID_UNDEFINED:
			/* Should not happen */
			*atom_pll_id = ATOM_PPLL_INVALID;
			result = false;
			अवरोध;
		शेष:
			result = false;
			अवरोध;
		पूर्ण

	वापस result;
पूर्ण

अटल bool engine_bp_to_atom(क्रमागत engine_id id, uपूर्णांक32_t *atom_engine_id)
अणु
	bool result = false;

	अगर (atom_engine_id != शून्य)
		चयन (id) अणु
		हाल ENGINE_ID_DIGA:
			*atom_engine_id = ASIC_INT_DIG1_ENCODER_ID;
			result = true;
			अवरोध;
		हाल ENGINE_ID_DIGB:
			*atom_engine_id = ASIC_INT_DIG2_ENCODER_ID;
			result = true;
			अवरोध;
		हाल ENGINE_ID_DIGC:
			*atom_engine_id = ASIC_INT_DIG3_ENCODER_ID;
			result = true;
			अवरोध;
		हाल ENGINE_ID_DIGD:
			*atom_engine_id = ASIC_INT_DIG4_ENCODER_ID;
			result = true;
			अवरोध;
		हाल ENGINE_ID_DIGE:
			*atom_engine_id = ASIC_INT_DIG5_ENCODER_ID;
			result = true;
			अवरोध;
		हाल ENGINE_ID_DIGF:
			*atom_engine_id = ASIC_INT_DIG6_ENCODER_ID;
			result = true;
			अवरोध;
		हाल ENGINE_ID_DIGG:
			*atom_engine_id = ASIC_INT_DIG7_ENCODER_ID;
			result = true;
			अवरोध;
		हाल ENGINE_ID_DACA:
			*atom_engine_id = ASIC_INT_DAC1_ENCODER_ID;
			result = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

	वापस result;
पूर्ण

अटल uपूर्णांक8_t encoder_action_to_atom(क्रमागत bp_encoder_control_action action)
अणु
	uपूर्णांक8_t atom_action = 0;

	चयन (action) अणु
	हाल ENCODER_CONTROL_ENABLE:
		atom_action = ATOM_ENABLE;
		अवरोध;
	हाल ENCODER_CONTROL_DISABLE:
		atom_action = ATOM_DISABLE;
		अवरोध;
	हाल ENCODER_CONTROL_SETUP:
		atom_action = ATOM_ENCODER_CMD_STREAM_SETUP;
		अवरोध;
	हाल ENCODER_CONTROL_INIT:
		atom_action = ATOM_ENCODER_INIT;
		अवरोध;
	शेष:
		BREAK_TO_DEBUGGER(); /* Unhandle action in driver.!! */
		अवरोध;
	पूर्ण

	वापस atom_action;
पूर्ण

अटल uपूर्णांक8_t disp_घातer_gating_action_to_atom(
	क्रमागत bp_pipe_control_action action)
अणु
	uपूर्णांक8_t atom_pipe_action = 0;

	चयन (action) अणु
	हाल ASIC_PIPE_DISABLE:
		atom_pipe_action = ATOM_DISABLE;
		अवरोध;
	हाल ASIC_PIPE_ENABLE:
		atom_pipe_action = ATOM_ENABLE;
		अवरोध;
	हाल ASIC_PIPE_INIT:
		atom_pipe_action = ATOM_INIT;
		अवरोध;
	शेष:
		ASSERT_CRITICAL(false); /* Unhandle action in driver! */
		अवरोध;
	पूर्ण

	वापस atom_pipe_action;
पूर्ण

अटल bool dc_घड़ी_प्रकारype_to_atom(
		क्रमागत bp_dce_घड़ी_प्रकारype id,
		uपूर्णांक32_t *atom_घड़ी_प्रकारype)
अणु
	bool retCode = true;

	अगर (atom_घड़ी_प्रकारype != शून्य) अणु
		चयन (id) अणु
		हाल DCECLOCK_TYPE_DISPLAY_CLOCK:
			*atom_घड़ी_प्रकारype = DCE_CLOCK_TYPE_DISPCLK;
			अवरोध;

		हाल DCECLOCK_TYPE_DPREFCLK:
			*atom_घड़ी_प्रकारype = DCE_CLOCK_TYPE_DPREFCLK;
			अवरोध;

		शेष:
			ASSERT_CRITICAL(false); /* Unhandle action in driver! */
			अवरोध;
		पूर्ण
	पूर्ण

	वापस retCode;
पूर्ण

अटल uपूर्णांक8_t transmitter_color_depth_to_atom(क्रमागत transmitter_color_depth id)
अणु
	uपूर्णांक8_t atomColorDepth = 0;

	चयन (id) अणु
	हाल TRANSMITTER_COLOR_DEPTH_24:
		atomColorDepth = PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_DIS;
		अवरोध;
	हाल TRANSMITTER_COLOR_DEPTH_30:
		atomColorDepth = PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_5_4;
		अवरोध;
	हाल TRANSMITTER_COLOR_DEPTH_36:
		atomColorDepth = PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_3_2;
		अवरोध;
	हाल TRANSMITTER_COLOR_DEPTH_48:
		atomColorDepth = PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_2_1;
		अवरोध;
	शेष:
		ASSERT_CRITICAL(false); /* Unhandle action in driver! */
		अवरोध;
	पूर्ण

	वापस atomColorDepth;
पूर्ण

/* function table */
अटल स्थिर काष्ठा command_table_helper command_table_helper_funcs = अणु
	.controller_id_to_atom = dal_cmd_table_helper_controller_id_to_atom2,
	.encoder_action_to_atom = encoder_action_to_atom,
	.engine_bp_to_atom = engine_bp_to_atom,
	.घड़ी_source_id_to_atom = घड़ी_source_id_to_atom,
	.घड़ी_source_id_to_atom_phy_clk_src_id =
			घड़ी_source_id_to_atom_phy_clk_src_id,
	.संकेत_type_to_atom_dig_mode = संकेत_type_to_atom_dig_mode,
	.hpd_sel_to_atom = hpd_sel_to_atom,
	.dig_encoder_sel_to_atom = dig_encoder_sel_to_atom,
	.phy_id_to_atom = phy_id_to_atom,
	.disp_घातer_gating_action_to_atom = disp_घातer_gating_action_to_atom,
	.घड़ी_source_id_to_ref_clk_src = शून्य,
	.transmitter_bp_to_atom = शून्य,
	.encoder_id_to_atom = dal_cmd_table_helper_encoder_id_to_atom2,
	.encoder_mode_bp_to_atom =
			dal_cmd_table_helper_encoder_mode_bp_to_atom2,
	.dc_घड़ी_प्रकारype_to_atom = dc_घड़ी_प्रकारype_to_atom,
	.transmitter_color_depth_to_atom = transmitter_color_depth_to_atom,
पूर्ण;

/*
 * dal_cmd_tbl_helper_dce110_get_table
 *
 * @brief
 * Initialize command table helper functions
 *
 * @param
 * स्थिर काष्ठा command_table_helper **h - [out] काष्ठा of functions
 *
 */
स्थिर काष्ठा command_table_helper *dal_cmd_tbl_helper_dce112_get_table2(व्योम)
अणु
	वापस &command_table_helper_funcs;
पूर्ण
