<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DISPLAY_RQ_DLG_CALC_H__
#घोषणा __DISPLAY_RQ_DLG_CALC_H__

काष्ठा display_mode_lib;

#समावेश "display_rq_dlg_helpers.h"

व्योम dml1_extract_rq_regs(
		काष्ठा display_mode_lib *mode_lib,
		काष्ठा _vcs_dpi_display_rq_regs_st *rq_regs,
		स्थिर काष्ठा _vcs_dpi_display_rq_params_st rq_param);
/* Function: dml_rq_dlg_get_rq_params
 *  Calculate requestor related parameters that रेजिस्टर definition agnostic
 *  (i.e. this layer करोes try to separate real values from रेजिस्टर definition)
 * Input:
 *  pipe_src_param - pipe source configuration (e.g. vp, pitch, etc.)
 * Output:
 *  rq_param - values that can be used to setup RQ (e.g. swath_height, plane1_addr, etc.)
 */
व्योम dml1_rq_dlg_get_rq_params(
		काष्ठा display_mode_lib *mode_lib,
		काष्ठा _vcs_dpi_display_rq_params_st *rq_param,
		स्थिर काष्ठा _vcs_dpi_display_pipe_source_params_st pipe_src_param);


/* Function: dml_rq_dlg_get_dlg_params
 *  Calculate deadline related parameters
 */
व्योम dml1_rq_dlg_get_dlg_params(
		काष्ठा display_mode_lib *mode_lib,
		काष्ठा _vcs_dpi_display_dlg_regs_st *dlg_regs,
		काष्ठा _vcs_dpi_display_ttu_regs_st *ttu_regs,
		स्थिर काष्ठा _vcs_dpi_display_rq_dlg_params_st rq_dlg_param,
		स्थिर काष्ठा _vcs_dpi_display_dlg_sys_params_st dlg_sys_param,
		स्थिर काष्ठा _vcs_dpi_display_e2e_pipe_params_st e2e_pipe_param,
		स्थिर bool cstate_en,
		स्थिर bool pstate_en,
		स्थिर bool vm_en,
		स्थिर bool अगरlip_en);

#पूर्ण_अगर
