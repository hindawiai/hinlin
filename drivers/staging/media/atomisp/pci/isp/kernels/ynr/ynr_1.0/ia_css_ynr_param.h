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

#अगर_अघोषित __IA_CSS_YNR_PARAM_H
#घोषणा __IA_CSS_YNR_PARAM_H

#समावेश "type_support.h"

/* YNR (Y Noise Reduction) */
काष्ठा sh_css_isp_ynr_params अणु
	s32 threshold;
	s32 gain_all;
	s32 gain_dir;
	s32 threshold_cb;
	s32 threshold_cr;
पूर्ण;

/* YEE (Y Edge Enhancement) */
काष्ठा sh_css_isp_yee_params अणु
	s32 dirthreshold_s;
	s32 dirthreshold_g;
	s32 dirthreshold_width_log2;
	s32 dirthreshold_width;
	s32 detailgain;
	s32 coring_s;
	s32 coring_g;
	s32 scale_plus_s;
	s32 scale_plus_g;
	s32 scale_minus_s;
	s32 scale_minus_g;
	s32 clip_plus_s;
	s32 clip_plus_g;
	s32 clip_minus_s;
	s32 clip_minus_g;
	s32 Yclip;
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_YNR_PARAM_H */
