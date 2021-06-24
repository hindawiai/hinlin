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

#अगर_अघोषित __IA_CSS_HDR_PARAMS_H
#घोषणा __IA_CSS_HDR_PARAMS_H

#समावेश "type_support.h"

#घोषणा HDR_NUM_INPUT_FRAMES         (3)

/* HDR irradiance map parameters on ISP. */
काष्ठा sh_css_hdr_irradiance_params अणु
	s32 test_irr;
	s32 match_shअगरt[HDR_NUM_INPUT_FRAMES -
					     1];  /* Histogram matching shअगरt parameter */
	s32 match_mul[HDR_NUM_INPUT_FRAMES -
					   1];    /* Histogram matching multiplication parameter */
	s32 thr_low[HDR_NUM_INPUT_FRAMES -
					 1];      /* Weight map soft threshold low bound parameter */
	s32 thr_high[HDR_NUM_INPUT_FRAMES -
					  1];     /* Weight map soft threshold high bound parameter */
	s32 thr_coeff[HDR_NUM_INPUT_FRAMES -
					   1];    /* Soft threshold linear function coefficient */
	s32 thr_shअगरt[HDR_NUM_INPUT_FRAMES -
					   1];    /* Soft threshold precision shअगरt parameter */
	s32 weight_bpp;                             /* Weight map bits per pixel */
पूर्ण;

/* HDR deghosting parameters on ISP */
काष्ठा sh_css_hdr_deghost_params अणु
	s32 test_deg;
पूर्ण;

/* HDR exclusion parameters on ISP */
काष्ठा sh_css_hdr_exclusion_params अणु
	s32 test_excl;
पूर्ण;

/* HDR ISP parameters */
काष्ठा sh_css_isp_hdr_params अणु
	काष्ठा sh_css_hdr_irradiance_params irradiance;
	काष्ठा sh_css_hdr_deghost_params    deghost;
	काष्ठा sh_css_hdr_exclusion_params  exclusion;
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_HDR_PARAMS_H */
