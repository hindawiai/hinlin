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

#अगर_अघोषित __IA_CSS_HB_PARAM_H
#घोषणा __IA_CSS_HB_PARAM_H

#समावेश "type_support.h"

#अगर_अघोषित PIPE_GENERATION
#घोषणा __INLINE_HMEM__
#समावेश "hmem.h"
#पूर्ण_अगर

#समावेश "ia_css_bh_types.h"

/* AE (3A Support) */
काष्ठा sh_css_isp_bh_params अणु
	/* coefficients to calculate Y */
	s32 y_coef_r;
	s32 y_coef_g;
	s32 y_coef_b;
पूर्ण;

/* This should be hmem_data_t, but that अवरोधs the pipe generator */
काष्ठा sh_css_isp_bh_hmem_params अणु
	u32 bh[ISP_HIST_COMPONENTS][IA_CSS_HMEM_BH_UNIT_SIZE];
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_HB_PARAM_H */
