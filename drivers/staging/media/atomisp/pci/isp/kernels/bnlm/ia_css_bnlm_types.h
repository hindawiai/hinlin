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

#अगर_अघोषित __IA_CSS_BNLM_TYPES_H
#घोषणा __IA_CSS_BNLM_TYPES_H

/* @file
* CSS-API header file क्रम Bayer Non-Linear Mean parameters.
*/

#समावेश "type_support.h" /* पूर्णांक32_t */

/* Bayer Non-Linear Mean configuration
 *
 * \मrief BNLM खुला parameters.
 * \details Struct with all parameters क्रम the BNLM kernel that can be set
 * from the CSS API.
 *
 * ISP2.6.1: BNLM is used.
 */
काष्ठा ia_css_bnlm_config अणु
	bool		rad_enable;	/** Enable a radial dependency in a weight calculation */
	s32		rad_x_origin;	/** Initial x coordinate क्रम a radius calculation */
	s32		rad_y_origin;	/** Initial x coordinate क्रम a radius calculation */
	/* a threshold क्रम average of weights अगर this < Th, करो not denoise pixel */
	s32		avg_min_th;
	/* minimum weight क्रम denoising अगर max < th, करो not denoise pixel */
	s32		max_min_th;

	/**@अणु*/
	/* Coefficient क्रम approximation, in the क्रमm of (1 + x / N)^N,
	 * that fits the first-order exp() to शेष exp_lut in BNLM sheet
	 * */
	s32		exp_coeff_a;
	u32	exp_coeff_b;
	s32		exp_coeff_c;
	u32	exp_exponent;
	/**@पूर्ण*/

	s32 nl_th[3];	/** Detail thresholds */

	/* Index क्रम n-th maximum candidate weight क्रम each detail group */
	s32 match_quality_max_idx[4];

	/**@अणु*/
	/* A lookup table क्रम 1/वर्ग_मूल(1+mu) approximation */
	s32 mu_root_lut_thr[15];
	s32 mu_root_lut_val[16];
	/**@पूर्ण*/
	/**@अणु*/
	/* A lookup table क्रम SAD normalization */
	s32 sad_norm_lut_thr[15];
	s32 sad_norm_lut_val[16];
	/**@पूर्ण*/
	/**@अणु*/
	/* A lookup table that models a weight's dependency on textures */
	s32 sig_detail_lut_thr[15];
	s32 sig_detail_lut_val[16];
	/**@पूर्ण*/
	/**@अणु*/
	/* A lookup table that models a weight's dependency on a pixel's radial distance */
	s32 sig_rad_lut_thr[15];
	s32 sig_rad_lut_val[16];
	/**@पूर्ण*/
	/**@अणु*/
	/* A lookup table to control denoise घातer depending on a pixel's radial distance */
	s32 rad_घात_lut_thr[15];
	s32 rad_घात_lut_val[16];
	/**@पूर्ण*/
	/**@अणु*/
	/* Non linear transfer functions to calculate the blending coefficient depending on detail group */
	/* detail group 0 */
	/**@अणु*/
	s32 nl_0_lut_thr[15];
	s32 nl_0_lut_val[16];
	/**@पूर्ण*/
	/**@अणु*/
	/* detail group 1 */
	s32 nl_1_lut_thr[15];
	s32 nl_1_lut_val[16];
	/**@पूर्ण*/
	/**@अणु*/
	/* detail group 2 */
	s32 nl_2_lut_thr[15];
	s32 nl_2_lut_val[16];
	/**@पूर्ण*/
	/**@अणु*/
	/* detail group 3 */
	s32 nl_3_lut_thr[15];
	s32 nl_3_lut_val[16];
	/**@पूर्ण*/
	/**@पूर्ण*/
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_BNLM_TYPES_H */
