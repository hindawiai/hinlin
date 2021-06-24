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

#अगर_अघोषित __IA_CSS_CTC2_TYPES_H
#घोषणा __IA_CSS_CTC2_TYPES_H

/* Chroma Tone Control configuration.
*
*  ISP block: CTC2 (CTC by polygonal approximation)
* (ISP1: CTC1 (CTC by look-up table) is used.)
*  ISP2: CTC2 is used.
*  ISP261: CTC2 (CTC by Fast Approximate Distance)
*/
काष्ठा ia_css_ctc2_config अणु
	/** Gains by Y(Luma) at Y =0.0,Y_X1, Y_X2, Y_X3, Y_X4 and Y_X5
	*   --शेष/ineffective value: 4096(0.5f)
	*/
	s32 y_y0;
	s32 y_y1;
	s32 y_y2;
	s32 y_y3;
	s32 y_y4;
	s32 y_y5;
	/* 1st-4th  kneepoपूर्णांकs by Y(Luma) --शेष/ineffective value:n/a
	*   requirement: 0.0 < y_x1 < y_x2 <y _x3 < y_x4 < 1.0
	*/
	s32 y_x1;
	s32 y_x2;
	s32 y_x3;
	s32 y_x4;
	/* Gains by UV(Chroma) under threholds uv_x0 and uv_x1
	*   --शेष/ineffective value: 4096(0.5f)
	*/
	s32 uv_y0;
	s32 uv_y1;
	/* Minimum and Maximum Thresholds by UV(Chroma)- uv_x0 and uv_x1
	*   --शेष/ineffective value: n/a
	*/
	s32 uv_x0;
	s32 uv_x1;
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_CTC2_TYPES_H */
