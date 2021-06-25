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

#अगर_अघोषित __IA_CSS_BNR2_2_TYPES_H
#घोषणा __IA_CSS_BNR2_2_TYPES_H

/* @file
* CSS-API header file क्रम Bayer Noise Reduction parameters.
*/

#समावेश "type_support.h" /* पूर्णांक32_t */

/* Bayer Noise Reduction 2.2 configuration
 *
 * \मrief BNR2_2 खुला parameters.
 * \details Struct with all parameters क्रम the BNR2.2 kernel that can be set
 * from the CSS API.
 *
 * ISP2.6.1: BNR2.2 is used.
 */
काष्ठा ia_css_bnr2_2_config अणु
	/**@अणु*/
	/* Directional variance gain क्रम R/G/B components in dark region */
	s32 d_var_gain_r;
	s32 d_var_gain_g;
	s32 d_var_gain_b;
	/**@पूर्ण*/
	/**@अणु*/
	/* Slope of Directional variance gain between dark and bright region */
	s32 d_var_gain_slope_r;
	s32 d_var_gain_slope_g;
	s32 d_var_gain_slope_b;
	/**@पूर्ण*/
	/**@अणु*/
	/* Non-Directional variance gain क्रम R/G/B components in dark region */
	s32 n_var_gain_r;
	s32 n_var_gain_g;
	s32 n_var_gain_b;
	/**@पूर्ण*/
	/**@अणु*/
	/* Slope of Non-Directional variance gain between dark and bright region */
	s32 n_var_gain_slope_r;
	s32 n_var_gain_slope_g;
	s32 n_var_gain_slope_b;
	/**@पूर्ण*/

	s32 dir_thres;		/** Threshold क्रम directional filtering */
	s32 dir_thres_w;		/** Threshold width क्रम directional filtering */
	s32 var_offset_coef;	/** Variance offset coefficient */
	s32 dir_gain;		/** Gain क्रम directional coefficient */
	s32 detail_gain;		/** Gain क्रम low contrast texture control */
	s32 detail_gain_भागisor;	/** Gain भागisor क्रम low contrast texture control */
	s32 detail_level_offset;	/** Bias value क्रम low contrast texture control */
	s32 d_var_th_min;		/** Minimum clipping value क्रम directional variance*/
	s32 d_var_th_max;		/** Maximum clipping value क्रम diretional variance*/
	s32 n_var_th_min;		/** Minimum clipping value क्रम non-directional variance*/
	s32 n_var_th_max;		/** Maximum clipping value क्रम non-directional variance*/
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_BNR2_2_TYPES_H */
