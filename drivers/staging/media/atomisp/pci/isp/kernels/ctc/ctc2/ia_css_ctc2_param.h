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

#अगर_अघोषित __IA_CSS_CTC2_PARAM_H
#घोषणा __IA_CSS_CTC2_PARAM_H

#घोषणा IA_CSS_CTC_COEF_SHIFT          13
#समावेश "vmem.h" /* needed क्रम VMEM_ARRAY */

/* CTC (Chroma Tone Control)ISP Parameters */

/*VMEM Luma params*/
काष्ठा ia_css_isp_ctc2_vmem_params अणु
	/** Gains by Y(Luma) at Y = 0.0,Y_X1, Y_X2, Y_X3, Y_X4*/
	VMEM_ARRAY(y_x, ISP_VEC_NELEMS);
	/* kneepoपूर्णांकs by Y(Luma) 0.0, y_x1, y_x2, y _x3, y_x4*/
	VMEM_ARRAY(y_y, ISP_VEC_NELEMS);
	/* Slopes of lines पूर्णांकerconnecting
	 *  0.0 -> y_x1 -> y_x2 -> y _x3 -> y_x4 -> 1.0*/
	VMEM_ARRAY(e_y_slope, ISP_VEC_NELEMS);
पूर्ण;

/*DMEM Chroma params*/
काष्ठा ia_css_isp_ctc2_dmem_params अणु
	/* Gains by UV(Chroma) under kneepoपूर्णांकs uv_x0 and uv_x1*/
	s32 uv_y0;
	s32 uv_y1;

	/* Kneepoपूर्णांकs by UV(Chroma)- uv_x0 and uv_x1*/
	s32 uv_x0;
	s32 uv_x1;

	/* Slope of line पूर्णांकerconnecting uv_x0 -> uv_x1*/
	s32 uv_dydx;

पूर्ण;
#पूर्ण_अगर /* __IA_CSS_CTC2_PARAM_H */
