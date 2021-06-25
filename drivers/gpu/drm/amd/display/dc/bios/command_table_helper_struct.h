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

#अगर_अघोषित __DAL_COMMAND_TABLE_HELPER_STRUCT_H__
#घोषणा __DAL_COMMAND_TABLE_HELPER_STRUCT_H__

#समावेश "dce80/command_table_helper_dce80.h"
#समावेश "dce110/command_table_helper_dce110.h"
#समावेश "dce112/command_table_helper_dce112.h"

काष्ठा _DIG_ENCODER_CONTROL_PARAMETERS_V2;
काष्ठा command_table_helper अणु
	bool (*controller_id_to_atom)(क्रमागत controller_id id, uपूर्णांक8_t *atom_id);
	uपूर्णांक8_t (*encoder_action_to_atom)(
			क्रमागत bp_encoder_control_action action);
	uपूर्णांक32_t (*encoder_mode_bp_to_atom)(क्रमागत संकेत_type s,
			bool enable_dp_audio);
	bool (*engine_bp_to_atom)(क्रमागत engine_id engine_id,
			uपूर्णांक32_t *atom_engine_id);
	व्योम (*assign_control_parameter)(
			स्थिर काष्ठा command_table_helper *h,
			काष्ठा bp_encoder_control *control,
			काष्ठा _DIG_ENCODER_CONTROL_PARAMETERS_V2 *ctrl_param);
	bool (*घड़ी_source_id_to_atom)(क्रमागत घड़ी_source_id id,
			uपूर्णांक32_t *atom_pll_id);
	bool (*घड़ी_source_id_to_ref_clk_src)(
			क्रमागत घड़ी_source_id id,
			uपूर्णांक32_t *ref_clk_src_id);
	uपूर्णांक8_t (*transmitter_bp_to_atom)(क्रमागत transmitter t);
	uपूर्णांक8_t (*encoder_id_to_atom)(क्रमागत encoder_id id);
	uपूर्णांक8_t (*घड़ी_source_id_to_atom_phy_clk_src_id)(
			क्रमागत घड़ी_source_id id);
	uपूर्णांक8_t (*संकेत_type_to_atom_dig_mode)(क्रमागत संकेत_type s);
	uपूर्णांक8_t (*hpd_sel_to_atom)(क्रमागत hpd_source_id id);
	uपूर्णांक8_t (*dig_encoder_sel_to_atom)(क्रमागत engine_id engine_id);
	uपूर्णांक8_t (*phy_id_to_atom)(क्रमागत transmitter t);
	uपूर्णांक8_t (*disp_घातer_gating_action_to_atom)(
			क्रमागत bp_pipe_control_action action);
	bool (*dc_घड़ी_प्रकारype_to_atom)(क्रमागत bp_dce_घड़ी_प्रकारype id,
			uपूर्णांक32_t *atom_घड़ी_प्रकारype);
	uपूर्णांक8_t (*transmitter_color_depth_to_atom)(क्रमागत transmitter_color_depth id);
पूर्ण;

#पूर्ण_अगर
