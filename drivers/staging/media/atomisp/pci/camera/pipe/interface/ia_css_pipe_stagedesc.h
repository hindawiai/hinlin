<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित __IA_CSS_PIPE_STAGEDESC_H__
#घोषणा __IA_CSS_PIPE_STAGEDESC_H__

#समावेश <ia_css_acc_types.h> /* ia_css_fw_info */
#समावेश <ia_css_frame_खुला.h>
#समावेश <ia_css_binary.h>
#समावेश "ia_css_pipeline.h"
#समावेश "ia_css_pipeline_common.h"

व्योम ia_css_pipe_get_generic_stage_desc(
    काष्ठा ia_css_pipeline_stage_desc *stage_desc,
    काष्ठा ia_css_binary *binary,
    काष्ठा ia_css_frame *out_frame[],
    काष्ठा ia_css_frame *in_frame,
    काष्ठा ia_css_frame *vf_frame);

व्योम ia_css_pipe_get_firmwares_stage_desc(
    काष्ठा ia_css_pipeline_stage_desc *stage_desc,
    काष्ठा ia_css_binary *binary,
    काष्ठा ia_css_frame *out_frame[],
    काष्ठा ia_css_frame *in_frame,
    काष्ठा ia_css_frame *vf_frame,
    स्थिर काष्ठा ia_css_fw_info *fw,
    अचिन्हित पूर्णांक mode);

व्योम ia_css_pipe_get_acc_stage_desc(
    काष्ठा ia_css_pipeline_stage_desc *stage_desc,
    काष्ठा ia_css_binary *binary,
    काष्ठा ia_css_fw_info *fw);

व्योम ia_css_pipe_get_sp_func_stage_desc(
    काष्ठा ia_css_pipeline_stage_desc *stage_desc,
    काष्ठा ia_css_frame *out_frame,
    क्रमागत ia_css_pipeline_stage_sp_func sp_func,
    अचिन्हित पूर्णांक max_input_width);

#पूर्ण_अगर /*__IA_CSS_PIPE_STAGEDESC__H__ */
