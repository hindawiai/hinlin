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

#अगर_अघोषित __DAL_COMMAND_TABLE_HELPER2_H__
#घोषणा __DAL_COMMAND_TABLE_HELPER2_H__

#अगर defined(CONFIG_DRM_AMD_DC_SI)
#समावेश "dce60/command_table_helper_dce60.h"
#पूर्ण_अगर
#समावेश "dce80/command_table_helper_dce80.h"
#समावेश "dce110/command_table_helper_dce110.h"
#समावेश "dce112/command_table_helper2_dce112.h"
#समावेश "command_table_helper_struct.h"

bool dal_bios_parser_init_cmd_tbl_helper2(स्थिर काष्ठा command_table_helper **h,
	क्रमागत dce_version dce);

bool dal_cmd_table_helper_controller_id_to_atom2(
	क्रमागत controller_id id,
	uपूर्णांक8_t *atom_id);

uपूर्णांक32_t dal_cmd_table_helper_encoder_mode_bp_to_atom2(
	क्रमागत संकेत_type s,
	bool enable_dp_audio);

bool dal_cmd_table_helper_घड़ी_source_id_to_ref_clk_src2(
	क्रमागत घड़ी_source_id id,
	uपूर्णांक32_t *ref_clk_src_id);

uपूर्णांक8_t dal_cmd_table_helper_transmitter_bp_to_atom2(
	क्रमागत transmitter t);

uपूर्णांक8_t dal_cmd_table_helper_encoder_id_to_atom2(
	क्रमागत encoder_id id);
#पूर्ण_अगर
