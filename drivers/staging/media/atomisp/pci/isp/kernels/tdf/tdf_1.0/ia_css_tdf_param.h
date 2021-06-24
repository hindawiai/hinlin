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

#अगर_अघोषित __IA_CSS_TDF_PARAM_H
#घोषणा __IA_CSS_TDF_PARAM_H

#समावेश "type_support.h"
#समावेश "vmem.h" /* needed क्रम VMEM_ARRAY */

काष्ठा ia_css_isp_tdf_vmem_params अणु
	VMEM_ARRAY(pyramid, ISP_VEC_NELEMS);
	VMEM_ARRAY(threshold_flat, ISP_VEC_NELEMS);
	VMEM_ARRAY(threshold_detail, ISP_VEC_NELEMS);
पूर्ण;

काष्ठा ia_css_isp_tdf_dmem_params अणु
	s32 Epsilon_0;
	s32 Epsilon_1;
	s32 EpsScaleText;
	s32 EpsScaleEdge;
	s32 Sepa_flat;
	s32 Sepa_Edge;
	s32 Blend_Flat;
	s32 Blend_Text;
	s32 Blend_Edge;
	s32 Shading_Gain;
	s32 Shading_baseGain;
	s32 LocalY_Gain;
	s32 LocalY_baseGain;
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_TDF_PARAM_H */
