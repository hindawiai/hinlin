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

#समावेश "ia_css_debug.h"
#समावेश "ia_css_tdf.host.h"

अटल स्थिर s16 g_pyramid[8][8] = अणु
	अणु128, 384, 640, 896, 896, 640, 384, 128पूर्ण,
	अणु384, 1152, 1920, 2688, 2688, 1920, 1152, 384पूर्ण,
	अणु640, 1920, 3200, 4480, 4480, 3200, 1920, 640पूर्ण,
	अणु896, 2688, 4480, 6272, 6272, 4480, 2688, 896पूर्ण,
	अणु896, 2688, 4480, 6272, 6272, 4480, 2688, 896पूर्ण,
	अणु640, 1920, 3200, 4480, 4480, 3200, 1920, 640पूर्ण,
	अणु384, 1152, 1920, 2688, 2688, 1920, 1152, 384पूर्ण,
	अणु128, 384, 640, 896, 896, 640, 384, 128पूर्ण
पूर्ण;

व्योम
ia_css_tdf_vmem_encode(
    काष्ठा ia_css_isp_tdf_vmem_params *to,
    स्थिर काष्ठा ia_css_tdf_config *from,
    माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक i;
	(व्योम)size;

	क्रम (i = 0; i < ISP_VEC_NELEMS; i++) अणु
		to->pyramid[0][i]          = g_pyramid[i / 8][i % 8];
		to->threshold_flat[0][i]   = from->thres_flat_table[i];
		to->threshold_detail[0][i] = from->thres_detail_table[i];
	पूर्ण
पूर्ण

व्योम
ia_css_tdf_encode(
    काष्ठा ia_css_isp_tdf_dmem_params *to,
    स्थिर काष्ठा ia_css_tdf_config *from,
    माप_प्रकार size)
अणु
	(व्योम)size;
	to->Epsilon_0        = from->epsilon_0;
	to->Epsilon_1        = from->epsilon_1;
	to->EpsScaleText     = from->eps_scale_text;
	to->EpsScaleEdge     = from->eps_scale_edge;
	to->Sepa_flat	     = from->sepa_flat;
	to->Sepa_Edge	     = from->sepa_edge;
	to->Blend_Flat	     = from->blend_flat;
	to->Blend_Text	     = from->blend_text;
	to->Blend_Edge	     = from->blend_edge;
	to->Shading_Gain     = from->shading_gain;
	to->Shading_baseGain = from->shading_base_gain;
	to->LocalY_Gain      = from->local_y_gain;
	to->LocalY_baseGain  = from->local_y_base_gain;
पूर्ण

व्योम
ia_css_tdf_debug_dtrace(
    स्थिर काष्ठा ia_css_tdf_config *config,
    अचिन्हित पूर्णांक level)
अणु
	(व्योम)config;
	(व्योम)level;
पूर्ण
