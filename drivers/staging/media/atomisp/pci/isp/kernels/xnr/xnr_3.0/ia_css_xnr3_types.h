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

#अगर_अघोषित __IA_CSS_XNR3_TYPES_H
#घोषणा __IA_CSS_XNR3_TYPES_H

/* @file
* CSS-API header file क्रम Extra Noise Reduction (XNR) parameters.
*/

/**
 * \मrief Scale of the XNR sigma parameters.
 * \details The define specअगरies which fixed-poपूर्णांक value represents 1.0.
 */
#घोषणा IA_CSS_XNR3_SIGMA_SCALE  BIT(10)

/**
 * \मrief Scale of the XNR coring parameters.
 * \details The define specअगरies which fixed-poपूर्णांक value represents 1.0.
 */
#घोषणा IA_CSS_XNR3_CORING_SCALE BIT(15)

/**
 * \मrief Scale of the XNR blending parameter.
 * \details The define specअगरies which fixed-poपूर्णांक value represents 1.0.
 */
#घोषणा IA_CSS_XNR3_BLENDING_SCALE BIT(11)

/**
 * \मrief XNR3 Sigma Parameters.
 * \details Sigma parameters define the strength of the XNR filter.
 * A higher number means stronger filtering. There are two values क्रम each of
 * the three YUV planes: one क्रम dark areas and one क्रम bright areas. All
 * sigma parameters are fixed-poपूर्णांक values between 0.0 and 1.0, scaled with
 * IA_CSS_XNR3_SIGMA_SCALE.
 */
काष्ठा ia_css_xnr3_sigma_params अणु
	पूर्णांक y0;     /** Sigma क्रम Y range similarity in dark area */
	पूर्णांक y1;     /** Sigma क्रम Y range similarity in bright area */
	पूर्णांक u0;     /** Sigma क्रम U range similarity in dark area */
	पूर्णांक u1;     /** Sigma क्रम U range similarity in bright area */
	पूर्णांक v0;     /** Sigma क्रम V range similarity in dark area */
	पूर्णांक v1;     /** Sigma क्रम V range similarity in bright area */
पूर्ण;

/**
 * \मrief XNR3 Coring Parameters
 * \details Coring parameters define the "coring" strength, which is a soft
 * thresholding technique to aव्योम false coloring. There are two values क्रम
 * each of the two chroma planes: one क्रम dark areas and one क्रम bright areas.
 * All coring parameters are fixed-poपूर्णांक values between 0.0 and 1.0, scaled
 * with IA_CSS_XNR3_CORING_SCALE. The ineffective value is 0.
 */
काष्ठा ia_css_xnr3_coring_params अणु
	पूर्णांक u0;     /** Coring threshold of U channel in dark area */
	पूर्णांक u1;     /** Coring threshold of U channel in bright area */
	पूर्णांक v0;     /** Coring threshold of V channel in dark area */
	पूर्णांक v1;     /** Coring threshold of V channel in bright area */
पूर्ण;

/**
 * \मrief XNR3 Blending Parameters
 * \details Blending parameters define the blending strength of filtered
 * output pixels with the original chroma pixels from beक्रमe xnr3. The
 * blending strength is a fixed-poपूर्णांक value between 0.0 and 1.0 (inclusive),
 * scaled with IA_CSS_XNR3_BLENDING_SCALE.
 * A higher number applies xnr filtering more strongly. A value of 1.0
 * disables the blending and वापसs the xnr3 filtered output, जबतक a
 * value of 0.0 bypasses the entire xnr3 filter.
 */
काष्ठा ia_css_xnr3_blending_params अणु
	पूर्णांक strength;   /** Blending strength */
पूर्ण;

/**
 * \मrief XNR3 खुला parameters.
 * \details Struct with all parameters क्रम the XNR3 kernel that can be set
 * from the CSS API.
 */
काष्ठा ia_css_xnr3_config अणु
	काष्ठा ia_css_xnr3_sigma_params    sigma;    /** XNR3 sigma parameters */
	काष्ठा ia_css_xnr3_coring_params   coring;   /** XNR3 coring parameters */
	काष्ठा ia_css_xnr3_blending_params blending; /** XNR3 blending parameters */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_XNR3_TYPES_H */
