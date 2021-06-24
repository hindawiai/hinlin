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
#समावेश "ia_css_debug.h"
#समावेश "assert_support.h"

#समावेश "ia_css_ctc.host.h"

स्थिर काष्ठा ia_css_ctc_config शेष_ctc_config = अणु
	((1 << IA_CSS_CTC_COEF_SHIFT) + 1) / 2,		/* 0.5 */
	((1 << IA_CSS_CTC_COEF_SHIFT) + 1) / 2,		/* 0.5 */
	((1 << IA_CSS_CTC_COEF_SHIFT) + 1) / 2,		/* 0.5 */
	((1 << IA_CSS_CTC_COEF_SHIFT) + 1) / 2,		/* 0.5 */
	((1 << IA_CSS_CTC_COEF_SHIFT) + 1) / 2,		/* 0.5 */
	((1 << IA_CSS_CTC_COEF_SHIFT) + 1) / 2,		/* 0.5 */
	1,
	SH_CSS_BAYER_MAXVAL / 5,	/* To be implemented */
	SH_CSS_BAYER_MAXVAL * 2 / 5,	/* To be implemented */
	SH_CSS_BAYER_MAXVAL * 3 / 5,	/* To be implemented */
	SH_CSS_BAYER_MAXVAL * 4 / 5,	/* To be implemented */
पूर्ण;

व्योम
ia_css_ctc_vamem_encode(
    काष्ठा sh_css_isp_ctc_vamem_params *to,
    स्थिर काष्ठा ia_css_ctc_table *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	स_नकल(&to->ctc,  &from->data, माप(to->ctc));
पूर्ण

व्योम
ia_css_ctc_debug_dtrace(
    स्थिर काष्ठा ia_css_ctc_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.ce_gain_exp=%d, config.y0=%d, config.x1=%d, config.y1=%d, config.x2=%d, config.y2=%d, config.x3=%d, config.y3=%d, config.x4=%d, config.y4=%d\n",
			    config->ce_gain_exp, config->y0,
			    config->x1, config->y1,
			    config->x2, config->y2,
			    config->x3, config->y3,
			    config->x4, config->y4);
पूर्ण
