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
#अगर_अघोषित __DISPLAY_MODE_LIB_H__
#घोषणा __DISPLAY_MODE_LIB_H__

#समावेश "dm_services.h"
#समावेश "dc_features.h"
#समावेश "display_mode_structs.h"
#समावेश "display_mode_enums.h"
#समावेश "display_mode_vba.h"

क्रमागत dml_project अणु
	DML_PROJECT_UNDEFINED,
	DML_PROJECT_RAVEN1,
	DML_PROJECT_NAVI10,
	DML_PROJECT_NAVI10v2,
	DML_PROJECT_DCN21,
	DML_PROJECT_DCN30,
पूर्ण;

काष्ठा display_mode_lib;

काष्ठा dml_funcs अणु
	व्योम (*rq_dlg_get_dlg_reg)(
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
	व्योम (*rq_dlg_get_rq_reg)(
		काष्ठा display_mode_lib *mode_lib,
		display_rq_regs_st *rq_regs,
		स्थिर display_pipe_params_st pipe_param);
	व्योम (*recalculate)(काष्ठा display_mode_lib *mode_lib);
	व्योम (*validate)(काष्ठा display_mode_lib *mode_lib);
पूर्ण;

काष्ठा display_mode_lib अणु
	काष्ठा _vcs_dpi_ip_params_st ip;
	काष्ठा _vcs_dpi_soc_bounding_box_st soc;
	क्रमागत dml_project project;
	काष्ठा vba_vars_st vba;
	काष्ठा dal_logger *logger;
	काष्ठा dml_funcs funcs;
पूर्ण;

व्योम dml_init_instance(काष्ठा display_mode_lib *lib,
		स्थिर काष्ठा _vcs_dpi_soc_bounding_box_st *soc_bb,
		स्थिर काष्ठा _vcs_dpi_ip_params_st *ip_params,
		क्रमागत dml_project project);

स्थिर अक्षर *dml_get_status_message(क्रमागत dm_validation_status status);

व्योम dml_log_pipe_params(
		काष्ठा display_mode_lib *mode_lib,
		display_e2e_pipe_params_st *pipes,
		पूर्णांक pipe_cnt);

व्योम dml_log_mode_support_params(काष्ठा display_mode_lib *mode_lib);
#पूर्ण_अगर
