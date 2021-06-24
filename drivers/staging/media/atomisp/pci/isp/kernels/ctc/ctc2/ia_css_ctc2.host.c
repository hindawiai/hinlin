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

#समावेश "ia_css_types.h"
#समावेश "sh_css_defs.h"
#समावेश "assert_support.h"

#समावेश "ia_css_ctc2.host.h"

#घोषणा INEFFECTIVE_VAL 4096
#घोषणा BASIC_VAL 819

/*Default configuration of parameters क्रम Ctc2*/
स्थिर काष्ठा ia_css_ctc2_config शेष_ctc2_config = अणु
	INEFFECTIVE_VAL, INEFFECTIVE_VAL, INEFFECTIVE_VAL,
	INEFFECTIVE_VAL, INEFFECTIVE_VAL, INEFFECTIVE_VAL,
	BASIC_VAL * 2, BASIC_VAL * 4, BASIC_VAL * 6,
	BASIC_VAL * 8, INEFFECTIVE_VAL, INEFFECTIVE_VAL,
	BASIC_VAL >> 1, BASIC_VAL
पूर्ण;

/* (dydx) = ctc2_slope(y1, y0, x1, x0)
 * -----------------------------------------------
 * Calculation of the Slope of a Line = ((y1 - y0) >> 8)/(x1 - x0)
 *
 * Note: y1, y0 , x1 & x0 must lie within the range 0 <-> 8191
 */
अटल पूर्णांक ctc2_slope(पूर्णांक y1, पूर्णांक y0, पूर्णांक x1, पूर्णांक x0)
अणु
	स्थिर पूर्णांक shअगरt_val = 8;
	स्थिर पूर्णांक max_slope = (1 << IA_CSS_CTC_COEF_SHIFT) - 1;
	पूर्णांक dy = y1 - y0;
	पूर्णांक dx = x1 - x0;
	पूर्णांक rounding = (dx + 1) >> 1;
	पूर्णांक dy_shअगरt = dy << shअगरt_val;
	पूर्णांक slope, dydx;

	/*Protection क्रम parameter values, & aव्योमing zero भागisions*/
	निश्चित(y0 >= 0 && y0 <= max_slope);
	निश्चित(y1 >= 0 && y1 <= max_slope);
	निश्चित(x0 >= 0 && x0 <= max_slope);
	निश्चित(x1 > 0 && x1 <= max_slope);
	निश्चित(dx > 0);

	अगर (dy < 0)
		rounding = -rounding;
	slope = (पूर्णांक)(dy_shअगरt + rounding) / dx;

	/*the slope must lie within the range
	  (-max_slope-1) >= (dydx) >= (max_slope)
	*/
	अगर (slope <= -max_slope - 1) अणु
		dydx = -max_slope - 1;
	पूर्ण अन्यथा अगर (slope >= max_slope) अणु
		dydx = max_slope;
	पूर्ण अन्यथा अणु
		dydx = slope;
	पूर्ण

	वापस dydx;
पूर्ण

/* (व्योम) = ia_css_ctc2_vmem_encode(*to, *from)
 * -----------------------------------------------
 * VMEM Encode Function to translate Y parameters from userspace पूर्णांकo ISP space
 */
व्योम ia_css_ctc2_vmem_encode(काष्ठा ia_css_isp_ctc2_vmem_params *to,
			     स्थिर काष्ठा ia_css_ctc2_config *from,
			     माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक i, j;
	स्थिर अचिन्हित पूर्णांक shffl_blck = 4;
	स्थिर अचिन्हित पूर्णांक length_zeros = 11;
	लघु dydx0, dydx1, dydx2, dydx3, dydx4;

	(व्योम)size;
	/*
	*  Calculation of slopes of lines पूर्णांकerconnecting
	*  0.0 -> y_x1 -> y_x2 -> y _x3 -> y_x4 -> 1.0
	*/
	dydx0 = ctc2_slope(from->y_y1, from->y_y0,
			   from->y_x1, 0);
	dydx1 = ctc2_slope(from->y_y2, from->y_y1,
			   from->y_x2, from->y_x1);
	dydx2 = ctc2_slope(from->y_y3, from->y_y2,
			   from->y_x3, from->y_x2);
	dydx3 = ctc2_slope(from->y_y4, from->y_y3,
			   from->y_x4, from->y_x3);
	dydx4 = ctc2_slope(from->y_y5, from->y_y4,
			   SH_CSS_BAYER_MAXVAL, from->y_x4);

	/*Fill 3 arrays with:
	 * - Luma input gain values y_y0, y_y1, y_y2, y_3, y_y4
	 * - Luma kneepoपूर्णांकs 0, y_x1, y_x2, y_x3, y_x4
	 * - Calculated slopes dydx0, dyxd1, dydx2, dydx3, dydx4
	 *
	 * - Each 64-element array is भागided in blocks of 16 elements:
	 *   the 5 parameters + zeros in the reमुख्यing 11 positions
	 * - All blocks of the same array will contain the same data
	 */
	क्रम (i = 0; i < shffl_blck; i++) अणु
		to->y_x[0][(i << shffl_blck)]     = 0;
		to->y_x[0][(i << shffl_blck) + 1] = from->y_x1;
		to->y_x[0][(i << shffl_blck) + 2] = from->y_x2;
		to->y_x[0][(i << shffl_blck) + 3] = from->y_x3;
		to->y_x[0][(i << shffl_blck) + 4] = from->y_x4;

		to->y_y[0][(i << shffl_blck)]     = from->y_y0;
		to->y_y[0][(i << shffl_blck) + 1] = from->y_y1;
		to->y_y[0][(i << shffl_blck) + 2] = from->y_y2;
		to->y_y[0][(i << shffl_blck) + 3] = from->y_y3;
		to->y_y[0][(i << shffl_blck) + 4] = from->y_y4;

		to->e_y_slope[0][(i << shffl_blck)]    = dydx0;
		to->e_y_slope[0][(i << shffl_blck) + 1] = dydx1;
		to->e_y_slope[0][(i << shffl_blck) + 2] = dydx2;
		to->e_y_slope[0][(i << shffl_blck) + 3] = dydx3;
		to->e_y_slope[0][(i << shffl_blck) + 4] = dydx4;

		क्रम (j = 0; j < length_zeros; j++) अणु
			to->y_x[0][(i << shffl_blck) + 5 + j] = 0;
			to->y_y[0][(i << shffl_blck) + 5 + j] = 0;
			to->e_y_slope[0][(i << shffl_blck) + 5 + j] = 0;
		पूर्ण
	पूर्ण
पूर्ण

/* (व्योम) = ia_css_ctc2_encode(*to, *from)
 * -----------------------------------------------
 * DMEM Encode Function to translate UV parameters from userspace पूर्णांकo ISP space
 */
व्योम ia_css_ctc2_encode(काष्ठा ia_css_isp_ctc2_dmem_params *to,
			काष्ठा ia_css_ctc2_config *from,
			माप_प्रकार size)
अणु
	(व्योम)size;

	to->uv_y0 = from->uv_y0;
	to->uv_y1 = from->uv_y1;
	to->uv_x0 = from->uv_x0;
	to->uv_x1 = from->uv_x1;

	/*Slope Calculation*/
	to->uv_dydx = ctc2_slope(from->uv_y1, from->uv_y0,
				 from->uv_x1, from->uv_x0);
पूर्ण
