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

#अगर_अघोषित __DML20_DISPLAY_RQ_DLG_CALC_H__
#घोषणा __DML20_DISPLAY_RQ_DLG_CALC_H__

#समावेश "../display_rq_dlg_helpers.h"

काष्ठा display_mode_lib;


// Function: dml_rq_dlg_get_rq_reg
//  Main entry poपूर्णांक क्रम test to get the रेजिस्टर values out of this DML class.
//  This function calls <get_rq_param> and <extract_rq_regs> functions to calculate
//  and then populate the rq_regs काष्ठा
// Input:
//  pipe_src_param - pipe source configuration (e.g. vp, pitch, etc.)
// Output:
//  rq_regs - काष्ठा that holds all the RQ रेजिस्टरs field value.
//            See also: <display_rq_regs_st>
व्योम dml20_rq_dlg_get_rq_reg(
		काष्ठा display_mode_lib *mode_lib,
		display_rq_regs_st *rq_regs,
		स्थिर display_pipe_params_st pipe_param);


// Function: dml_rq_dlg_get_dlg_reg
//   Calculate and वापस DLG and TTU रेजिस्टर काष्ठा given the प्रणाली setting
// Output:
//  dlg_regs - output DLG रेजिस्टर काष्ठा
//  ttu_regs - output DLG TTU रेजिस्टर काष्ठा
// Input:
//  e2e_pipe_param - "compacted" array of e2e pipe param काष्ठा
//  num_pipes - num of active "pipe" or "route"
//  pipe_idx - index that identअगरies the e2e_pipe_param that corresponding to this dlg
//  cstate - 0: when calculate min_ttu_vblank it is assumed cstate is not required. 1: Normal mode, cstate is considered.
//           Added क्रम legacy or unrealistic timing tests.
व्योम dml20_rq_dlg_get_dlg_reg(
		काष्ठा display_mode_lib *mode_lib,
		display_dlg_regs_st *dlg_regs,
		display_ttu_regs_st *ttu_regs,
		display_e2e_pipe_params_st *e2e_pipe_param,
		स्थिर अचिन्हित पूर्णांक num_pipes,
		स्थिर अचिन्हित पूर्णांक pipe_idx,
		स्थिर bool cstate_en,
		स्थिर bool pstate_en,
		स्थिर bool vm_en,
		स्थिर bool ignore_viewport_pos,
		स्थिर bool immediate_flip_support);

#पूर्ण_अगर
