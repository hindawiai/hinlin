<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#समावेश "ia_css_pipe_stagedesc.h"
#समावेश "assert_support.h"
#समावेश "ia_css_debug.h"

व्योम ia_css_pipe_get_generic_stage_desc(
    काष्ठा ia_css_pipeline_stage_desc *stage_desc,
    काष्ठा ia_css_binary *binary,
    काष्ठा ia_css_frame *out_frame[],
    काष्ठा ia_css_frame *in_frame,
    काष्ठा ia_css_frame *vf_frame)
अणु
	अचिन्हित पूर्णांक i;

	IA_CSS_ENTER_PRIVATE("stage_desc = %p, binary = %p, out_frame = %p, in_frame = %p, vf_frame = %p",
			     stage_desc, binary, out_frame, in_frame, vf_frame);

	निश्चित(stage_desc && binary && binary->info);
	अगर (!stage_desc || !binary || !binary->info) अणु
		IA_CSS_ERROR("invalid arguments");
		जाओ ERR;
	पूर्ण

	stage_desc->binary = binary;
	stage_desc->firmware = शून्य;
	stage_desc->sp_func = IA_CSS_PIPELINE_NO_FUNC;
	stage_desc->max_input_width = 0;
	stage_desc->mode = binary->info->sp.pipeline.mode;
	stage_desc->in_frame = in_frame;
	क्रम (i = 0; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++) अणु
		stage_desc->out_frame[i] = out_frame[i];
	पूर्ण
	stage_desc->vf_frame = vf_frame;
ERR:
	IA_CSS_LEAVE_PRIVATE("");
पूर्ण

व्योम ia_css_pipe_get_firmwares_stage_desc(
    काष्ठा ia_css_pipeline_stage_desc *stage_desc,
    काष्ठा ia_css_binary *binary,
    काष्ठा ia_css_frame *out_frame[],
    काष्ठा ia_css_frame *in_frame,
    काष्ठा ia_css_frame *vf_frame,
    स्थिर काष्ठा ia_css_fw_info *fw,
    अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित पूर्णांक i;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "ia_css_pipe_get_firmwares_stage_desc() enter:\n");
	stage_desc->binary = binary;
	stage_desc->firmware = fw;
	stage_desc->sp_func = IA_CSS_PIPELINE_NO_FUNC;
	stage_desc->max_input_width = 0;
	stage_desc->mode = mode;
	stage_desc->in_frame = in_frame;
	क्रम (i = 0; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++) अणु
		stage_desc->out_frame[i] = out_frame[i];
	पूर्ण
	stage_desc->vf_frame = vf_frame;
पूर्ण

व्योम ia_css_pipe_get_acc_stage_desc(
    काष्ठा ia_css_pipeline_stage_desc *stage_desc,
    काष्ठा ia_css_binary *binary,
    काष्ठा ia_css_fw_info *fw)
अणु
	अचिन्हित पूर्णांक i;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "ia_css_pipe_get_acc_stage_desc() enter:\n");
	stage_desc->binary = binary;
	stage_desc->firmware = fw;
	stage_desc->sp_func = IA_CSS_PIPELINE_NO_FUNC;
	stage_desc->max_input_width = 0;
	stage_desc->mode = IA_CSS_BINARY_MODE_VF_PP;
	stage_desc->in_frame = शून्य;
	क्रम (i = 0; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++) अणु
		stage_desc->out_frame[i] = शून्य;
	पूर्ण
	stage_desc->vf_frame = शून्य;
पूर्ण

व्योम ia_css_pipe_get_sp_func_stage_desc(
    काष्ठा ia_css_pipeline_stage_desc *stage_desc,
    काष्ठा ia_css_frame *out_frame,
    क्रमागत ia_css_pipeline_stage_sp_func sp_func,
    अचिन्हित पूर्णांक max_input_width)
अणु
	अचिन्हित पूर्णांक i;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "ia_css_pipe_get_sp_func_stage_desc() enter:\n");
	stage_desc->binary = शून्य;
	stage_desc->firmware = शून्य;
	stage_desc->sp_func = sp_func;
	stage_desc->max_input_width = max_input_width;
	stage_desc->mode = (अचिन्हित पूर्णांक)-1;
	stage_desc->in_frame = शून्य;
	stage_desc->out_frame[0] = out_frame;
	क्रम (i = 1; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++) अणु
		stage_desc->out_frame[i] = शून्य;
	पूर्ण
	stage_desc->vf_frame = शून्य;
पूर्ण
