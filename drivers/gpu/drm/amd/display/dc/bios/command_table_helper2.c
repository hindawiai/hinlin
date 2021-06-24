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

#समावेश "include/bios_parser_types.h"

#समावेश "command_table_helper2.h"

bool dal_bios_parser_init_cmd_tbl_helper2(
	स्थिर काष्ठा command_table_helper **h,
	क्रमागत dce_version dce)
अणु
	चयन (dce) अणु
#अगर defined(CONFIG_DRM_AMD_DC_SI)
	हाल DCE_VERSION_6_0:
	हाल DCE_VERSION_6_1:
	हाल DCE_VERSION_6_4:
		*h = dal_cmd_tbl_helper_dce60_get_table();
		वापस true;
#पूर्ण_अगर

	हाल DCE_VERSION_8_0:
	हाल DCE_VERSION_8_1:
	हाल DCE_VERSION_8_3:
		*h = dal_cmd_tbl_helper_dce80_get_table();
		वापस true;

	हाल DCE_VERSION_10_0:
		*h = dal_cmd_tbl_helper_dce110_get_table();
		वापस true;

	हाल DCE_VERSION_11_0:
		*h = dal_cmd_tbl_helper_dce110_get_table();
		वापस true;

	हाल DCE_VERSION_11_2:
	हाल DCE_VERSION_11_22:
	हाल DCE_VERSION_12_0:
	हाल DCE_VERSION_12_1:
		*h = dal_cmd_tbl_helper_dce112_get_table2();
		वापस true;
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	हाल DCN_VERSION_1_0:
	हाल DCN_VERSION_1_01:
	हाल DCN_VERSION_2_0:
	हाल DCN_VERSION_2_1:
	हाल DCN_VERSION_3_0:
	हाल DCN_VERSION_3_01:
	हाल DCN_VERSION_3_02:
		*h = dal_cmd_tbl_helper_dce112_get_table2();
		वापस true;
#पूर्ण_अगर
	शेष:
		/* Unsupported DCE */
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण
पूर्ण

/* real implementations */

bool dal_cmd_table_helper_controller_id_to_atom2(
	क्रमागत controller_id id,
	uपूर्णांक8_t *atom_id)
अणु
	अगर (atom_id == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण

	चयन (id) अणु
	हाल CONTROLLER_ID_D0:
		*atom_id = ATOM_CRTC1;
		वापस true;
	हाल CONTROLLER_ID_D1:
		*atom_id = ATOM_CRTC2;
		वापस true;
	हाल CONTROLLER_ID_D2:
		*atom_id = ATOM_CRTC3;
		वापस true;
	हाल CONTROLLER_ID_D3:
		*atom_id = ATOM_CRTC4;
		वापस true;
	हाल CONTROLLER_ID_D4:
		*atom_id = ATOM_CRTC5;
		वापस true;
	हाल CONTROLLER_ID_D5:
		*atom_id = ATOM_CRTC6;
		वापस true;
	/* TODO :हाल CONTROLLER_ID_UNDERLAY0:
		*atom_id = ATOM_UNDERLAY_PIPE0;
		वापस true;
	*/
	हाल CONTROLLER_ID_UNDEFINED:
		*atom_id = ATOM_CRTC_INVALID;
		वापस true;
	शेष:
		/* Wrong controller id */
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण
पूर्ण

/**
 * translate_transmitter_bp_to_atom2 - Translate the Transmitter to the
 *                                     corresponding ATOM BIOS value
 *  @t: transmitter
 *  वापसs: digitalTransmitter
 *    // =00: Digital Transmitter1 ( UNIPHY linkAB )
 *    // =01: Digital Transmitter2 ( UNIPHY linkCD )
 *    // =02: Digital Transmitter3 ( UNIPHY linkEF )
 */
uपूर्णांक8_t dal_cmd_table_helper_transmitter_bp_to_atom2(
	क्रमागत transmitter t)
अणु
	चयन (t) अणु
	हाल TRANSMITTER_UNIPHY_A:
	हाल TRANSMITTER_UNIPHY_B:
	हाल TRANSMITTER_TRAVIS_LCD:
		वापस 0;
	हाल TRANSMITTER_UNIPHY_C:
	हाल TRANSMITTER_UNIPHY_D:
		वापस 1;
	हाल TRANSMITTER_UNIPHY_E:
	हाल TRANSMITTER_UNIPHY_F:
		वापस 2;
	शेष:
		/* Invalid Transmitter Type! */
		BREAK_TO_DEBUGGER();
		वापस 0;
	पूर्ण
पूर्ण

uपूर्णांक32_t dal_cmd_table_helper_encoder_mode_bp_to_atom2(
	क्रमागत संकेत_type s,
	bool enable_dp_audio)
अणु
	चयन (s) अणु
	हाल SIGNAL_TYPE_DVI_SINGLE_LINK:
	हाल SIGNAL_TYPE_DVI_DUAL_LINK:
		वापस ATOM_ENCODER_MODE_DVI;
	हाल SIGNAL_TYPE_HDMI_TYPE_A:
		वापस ATOM_ENCODER_MODE_HDMI;
	हाल SIGNAL_TYPE_LVDS:
		वापस ATOM_ENCODER_MODE_LVDS;
	हाल SIGNAL_TYPE_EDP:
	हाल SIGNAL_TYPE_DISPLAY_PORT_MST:
	हाल SIGNAL_TYPE_DISPLAY_PORT:
	हाल SIGNAL_TYPE_VIRTUAL:
		अगर (enable_dp_audio)
			वापस ATOM_ENCODER_MODE_DP_AUDIO;
		अन्यथा
			वापस ATOM_ENCODER_MODE_DP;
	हाल SIGNAL_TYPE_RGB:
		वापस ATOM_ENCODER_MODE_CRT;
	शेष:
		वापस ATOM_ENCODER_MODE_CRT;
	पूर्ण
पूर्ण

bool dal_cmd_table_helper_घड़ी_source_id_to_ref_clk_src2(
	क्रमागत घड़ी_source_id id,
	uपूर्णांक32_t *ref_clk_src_id)
अणु
	अगर (ref_clk_src_id == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण

	चयन (id) अणु
	हाल CLOCK_SOURCE_ID_PLL1:
		*ref_clk_src_id = ENCODER_REFCLK_SRC_P1PLL;
		वापस true;
	हाल CLOCK_SOURCE_ID_PLL2:
		*ref_clk_src_id = ENCODER_REFCLK_SRC_P2PLL;
		वापस true;
	/*TODO:हाल CLOCK_SOURCE_ID_DCPLL:
		*ref_clk_src_id = ENCODER_REFCLK_SRC_DCPLL;
		वापस true;
	*/
	हाल CLOCK_SOURCE_ID_EXTERNAL:
		*ref_clk_src_id = ENCODER_REFCLK_SRC_EXTCLK;
		वापस true;
	हाल CLOCK_SOURCE_ID_UNDEFINED:
		*ref_clk_src_id = ENCODER_REFCLK_SRC_INVALID;
		वापस true;
	शेष:
		/* Unsupported घड़ी source id */
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण
पूर्ण

uपूर्णांक8_t dal_cmd_table_helper_encoder_id_to_atom2(
	क्रमागत encoder_id id)
अणु
	चयन (id) अणु
	हाल ENCODER_ID_INTERNAL_LVDS:
		वापस ENCODER_OBJECT_ID_INTERNAL_LVDS;
	हाल ENCODER_ID_INTERNAL_TMDS1:
		वापस ENCODER_OBJECT_ID_INTERNAL_TMDS1;
	हाल ENCODER_ID_INTERNAL_TMDS2:
		वापस ENCODER_OBJECT_ID_INTERNAL_TMDS2;
	हाल ENCODER_ID_INTERNAL_DAC1:
		वापस ENCODER_OBJECT_ID_INTERNAL_DAC1;
	हाल ENCODER_ID_INTERNAL_DAC2:
		वापस ENCODER_OBJECT_ID_INTERNAL_DAC2;
	हाल ENCODER_ID_INTERNAL_LVTM1:
		वापस ENCODER_OBJECT_ID_INTERNAL_LVTM1;
	हाल ENCODER_ID_INTERNAL_HDMI:
		वापस ENCODER_OBJECT_ID_HDMI_INTERNAL;
	हाल ENCODER_ID_EXTERNAL_TRAVIS:
		वापस ENCODER_OBJECT_ID_TRAVIS;
	हाल ENCODER_ID_EXTERNAL_NUTMEG:
		वापस ENCODER_OBJECT_ID_NUTMEG;
	हाल ENCODER_ID_INTERNAL_KLDSCP_TMDS1:
		वापस ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1;
	हाल ENCODER_ID_INTERNAL_KLDSCP_DAC1:
		वापस ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1;
	हाल ENCODER_ID_INTERNAL_KLDSCP_DAC2:
		वापस ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2;
	हाल ENCODER_ID_EXTERNAL_MVPU_FPGA:
		वापस ENCODER_OBJECT_ID_MVPU_FPGA;
	हाल ENCODER_ID_INTERNAL_DDI:
		वापस ENCODER_OBJECT_ID_INTERNAL_DDI;
	हाल ENCODER_ID_INTERNAL_UNIPHY:
		वापस ENCODER_OBJECT_ID_INTERNAL_UNIPHY;
	हाल ENCODER_ID_INTERNAL_KLDSCP_LVTMA:
		वापस ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA;
	हाल ENCODER_ID_INTERNAL_UNIPHY1:
		वापस ENCODER_OBJECT_ID_INTERNAL_UNIPHY1;
	हाल ENCODER_ID_INTERNAL_UNIPHY2:
		वापस ENCODER_OBJECT_ID_INTERNAL_UNIPHY2;
	हाल ENCODER_ID_INTERNAL_UNIPHY3:
		वापस ENCODER_OBJECT_ID_INTERNAL_UNIPHY3;
	हाल ENCODER_ID_INTERNAL_WIRELESS:
		वापस ENCODER_OBJECT_ID_INTERNAL_VCE;
	हाल ENCODER_ID_INTERNAL_VIRTUAL:
		वापस ENCODER_OBJECT_ID_NONE;
	हाल ENCODER_ID_UNKNOWN:
		वापस ENCODER_OBJECT_ID_NONE;
	शेष:
		/* Invalid encoder id */
		BREAK_TO_DEBUGGER();
		वापस ENCODER_OBJECT_ID_NONE;
	पूर्ण
पूर्ण
