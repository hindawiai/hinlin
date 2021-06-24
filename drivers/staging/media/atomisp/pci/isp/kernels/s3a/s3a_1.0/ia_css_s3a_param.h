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

#अगर_अघोषित __IA_CSS_S3A_PARAM_H
#घोषणा __IA_CSS_S3A_PARAM_H

#समावेश "type_support.h"

/* AE (3A Support) */
काष्ठा sh_css_isp_ae_params अणु
	/* coefficients to calculate Y */
	s32 y_coef_r;
	s32 y_coef_g;
	s32 y_coef_b;
पूर्ण;

/* AWB (3A Support) */
काष्ठा sh_css_isp_awb_params अणु
	s32 lg_high_raw;
	s32 lg_low;
	s32 lg_high;
पूर्ण;

/* AF (3A Support) */
काष्ठा sh_css_isp_af_params अणु
	s32 fir1[7];
	s32 fir2[7];
पूर्ण;

/* S3A (3A Support) */
काष्ठा sh_css_isp_s3a_params अणु
	/* coefficients to calculate Y */
	काष्ठा sh_css_isp_ae_params ae;

	/* AWB level gate */
	काष्ठा sh_css_isp_awb_params awb;

	/* af fir coefficients */
	काष्ठा sh_css_isp_af_params af;
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_S3A_PARAM_H */
