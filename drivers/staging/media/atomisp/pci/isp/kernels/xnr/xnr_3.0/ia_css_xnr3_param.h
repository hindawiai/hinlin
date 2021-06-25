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

#अगर_अघोषित __IA_CSS_XNR3_PARAM_H
#घोषणा __IA_CSS_XNR3_PARAM_H

#समावेश "type_support.h"
#समावेश "vmem.h" /* ISP2401: needed क्रम VMEM_ARRAY */

/* Scaling factor of the alpha values: which fixed-poपूर्णांक value represents 1.0?
 * It must be chosen such that 1/min_sigma still fits in an ISP vector
 * element. */
#घोषणा XNR_ALPHA_SCALE_LOG2        5
#घोषणा XNR_ALPHA_SCALE_FACTOR      BIT(XNR_ALPHA_SCALE_LOG2)

/* Scaling factor of the coring values on the ISP. */
#घोषणा XNR_CORING_SCALE_LOG2       (ISP_VEC_ELEMBITS - 1)
#घोषणा XNR_CORING_SCALE_FACTOR     BIT(XNR_CORING_SCALE_LOG2)

/* Scaling factor of the blending strength on the ISP. */
#घोषणा XNR_BLENDING_SCALE_LOG2     (ISP_VEC_ELEMBITS - 1)
#घोषणा XNR_BLENDING_SCALE_FACTOR   BIT(XNR_BLENDING_SCALE_LOG2)

/* XNR3 filter size. Must be 11x11, 9x9 or 5x5. */
#घोषणा XNR_FILTER_SIZE             5

/* XNR3 alpha (1/sigma) parameters on the ISP, expressed as a base (0) value
 * क्रम dark areas, and a scaled dअगरf towards the value क्रम bright areas. */
काष्ठा sh_css_xnr3_alpha_params अणु
	s32 y0;
	s32 u0;
	s32 v0;
	s32 ydअगरf;
	s32 udअगरf;
	s32 vdअगरf;
पूर्ण;

/* XNR3 coring parameters on the ISP, expressed as a base (0) value
 * क्रम dark areas, and a scaled dअगरf towards the value क्रम bright areas. */
काष्ठा sh_css_xnr3_coring_params अणु
	s32 u0;
	s32 v0;
	s32 udअगरf;
	s32 vdअगरf;
पूर्ण;

/* XNR3 blending strength on the ISP. */
काष्ठा sh_css_xnr3_blending_params अणु
	s32 strength;
पूर्ण;

/* XNR3 ISP parameters */
काष्ठा sh_css_isp_xnr3_params अणु
	काष्ठा sh_css_xnr3_alpha_params    alpha;
	काष्ठा sh_css_xnr3_coring_params   coring;
	काष्ठा sh_css_xnr3_blending_params blending;
पूर्ण;

/* ISP2401 */
/*
 * STRUCT sh_css_isp_xnr3_vmem_params
 * -----------------------------------------------
 * ISP VMEM parameters
 */
काष्ठा sh_css_isp_xnr3_vmem_params अणु
	VMEM_ARRAY(x, ISP_VEC_NELEMS);
	VMEM_ARRAY(a, ISP_VEC_NELEMS);
	VMEM_ARRAY(b, ISP_VEC_NELEMS);
	VMEM_ARRAY(c, ISP_VEC_NELEMS);
पूर्ण;

#पूर्ण_अगर  /*__IA_CSS_XNR3_PARAM_H */
