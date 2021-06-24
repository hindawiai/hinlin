<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Release Version: irci_stable_candrpv_0415_20150521_0458 */
/* Release Version: irci_ecr-master_20150911_0724 */
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

#अगर_अघोषित __IA_CSS_HDR_TYPES_H
#घोषणा __IA_CSS_HDR_TYPES_H

#घोषणा IA_CSS_HDR_MAX_NUM_INPUT_FRAMES         (3)

/**
 * \मrief HDR Irradiance Parameters
 * \detail Currently HDR parameters are used only क्रम testing purposes
 */
काष्ठा ia_css_hdr_irradiance_params अणु
	पूर्णांक test_irr;                                          /** Test parameter */
	पूर्णांक match_shअगरt[IA_CSS_HDR_MAX_NUM_INPUT_FRAMES -
							1];  /** Histogram matching shअगरt parameter */
	पूर्णांक match_mul[IA_CSS_HDR_MAX_NUM_INPUT_FRAMES -
						      1];    /** Histogram matching multiplication parameter */
	पूर्णांक thr_low[IA_CSS_HDR_MAX_NUM_INPUT_FRAMES -
						    1];      /** Weight map soft threshold low bound parameter */
	पूर्णांक thr_high[IA_CSS_HDR_MAX_NUM_INPUT_FRAMES -
						     1];     /** Weight map soft threshold high bound parameter */
	पूर्णांक thr_coeff[IA_CSS_HDR_MAX_NUM_INPUT_FRAMES -
						      1];    /** Soft threshold linear function coefficien */
	पूर्णांक thr_shअगरt[IA_CSS_HDR_MAX_NUM_INPUT_FRAMES -
						      1];    /** Soft threshold precision shअगरt parameter */
	पूर्णांक weight_bpp;                                        /** Weight map bits per pixel */
पूर्ण;

/**
 * \मrief HDR Deghosting Parameters
 * \detail Currently HDR parameters are used only क्रम testing purposes
 */
काष्ठा ia_css_hdr_deghost_params अणु
	पूर्णांक test_deg; /** Test parameter */
पूर्ण;

/**
 * \मrief HDR Exclusion Parameters
 * \detail Currently HDR parameters are used only क्रम testing purposes
 */
काष्ठा ia_css_hdr_exclusion_params अणु
	पूर्णांक test_excl; /** Test parameter */
पूर्ण;

/**
 * \मrief HDR खुला paramterers.
 * \details Struct with all parameters क्रम HDR that can be seet from
 * the CSS API. Currenly, only test parameters are defined.
 */
काष्ठा ia_css_hdr_config अणु
	काष्ठा ia_css_hdr_irradiance_params irradiance; /** HDR irradiance parameters */
	काष्ठा ia_css_hdr_deghost_params    deghost;    /** HDR deghosting parameters */
	काष्ठा ia_css_hdr_exclusion_params  exclusion; /** HDR exclusion parameters */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_HDR_TYPES_H */
