<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/**
Support क्रम Intel Camera Imaging ISP subप्रणाली.
Copyright (c) 2010 - 2015, Intel Corporation.

This program is मुक्त software; you can redistribute it and/or modअगरy it
under the terms and conditions of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
more details.
*/

#अगर_अघोषित _IA_CSS_TNR3_TYPES_H
#घोषणा _IA_CSS_TNR3_TYPES_H

/* @file
* CSS-API header file क्रम Temporal Noise Reduction v3 (TNR3) kernel
*/

/**
 * \मrief Number of piecewise linear segments.
 * \details The parameters to TNR3 are specअगरied as a piecewise linear segment.
 * The number of such segments is fixed at 3.
 */
#घोषणा TNR3_NUM_SEGMENTS    3

/* Temporal Noise Reduction v3 (TNR3) configuration.
 * The parameter to this kernel is fourfold
 * 1. Three piecewise linear graphs (one क्रम each plane) with three segments
 * each. Each line graph has Luma values on the x axis and sigma values क्रम
 * each plane on the y axis. The three linear segments may have a dअगरferent
 * slope and the poपूर्णांक of Luma value which where the slope may change is called
 * a "Knee" poपूर्णांक. As there are three such segments, four poपूर्णांकs need to be
 * specअगरied each on the Luma axis and the per plane Sigma axis. On the Luma
 * axis two poपूर्णांकs are fixed (namely 0 and maximum luma value - depending on
 * ISP bit depth). The other two poपूर्णांकs are the poपूर्णांकs where the slope may
 * change its value. These two poपूर्णांकs are called knee poपूर्णांकs. The four poपूर्णांकs on
 * the per plane sigma axis are also specअगरied at the पूर्णांकerface.
 * 2. One rounding adjusपंचांगent parameter क्रम each plane
 * 3. One maximum feedback threshold value क्रम each plane
 * 4. Selection of the reference frame buffer to be used क्रम noise reduction.
 */
काष्ठा ia_css_tnr3_kernel_config अणु
	अचिन्हित पूर्णांक maxfb_y;                        /** Maximum Feedback Gain क्रम Y */
	अचिन्हित पूर्णांक maxfb_u;                        /** Maximum Feedback Gain क्रम U */
	अचिन्हित पूर्णांक maxfb_v;                        /** Maximum Feedback Gain क्रम V */
	अचिन्हित पूर्णांक round_adj_y;                    /** Rounding Adjust क्रम Y */
	अचिन्हित पूर्णांक round_adj_u;                    /** Rounding Adjust क्रम U */
	अचिन्हित पूर्णांक round_adj_v;                    /** Rounding Adjust क्रम V */
	अचिन्हित पूर्णांक knee_y[TNR3_NUM_SEGMENTS - 1];  /** Knee poपूर्णांकs */
	अचिन्हित पूर्णांक sigma_y[TNR3_NUM_SEGMENTS +
					       1]; /** Standard deviation क्रम Y at poपूर्णांकs Y0, Y1, Y2, Y3 */
	अचिन्हित पूर्णांक sigma_u[TNR3_NUM_SEGMENTS +
					       1]; /** Standard deviation क्रम U at poपूर्णांकs U0, U1, U2, U3 */
	अचिन्हित पूर्णांक sigma_v[TNR3_NUM_SEGMENTS +
					       1]; /** Standard deviation क्रम V at poपूर्णांकs V0, V1, V2, V3 */
	अचिन्हित पूर्णांक
	ref_buf_select;                 /** Selection of the reference buffer */
पूर्ण;

#पूर्ण_अगर
