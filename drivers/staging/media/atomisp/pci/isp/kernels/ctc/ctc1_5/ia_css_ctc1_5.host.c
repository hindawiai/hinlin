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

#समावेश "ctc/ctc_1.0/ia_css_ctc.host.h"
#समावेश "ia_css_ctc1_5.host.h"

अटल व्योम ctc_gradient(
    पूर्णांक *dydx, पूर्णांक *shअगरt,
    पूर्णांक y1, पूर्णांक y0, पूर्णांक x1, पूर्णांक x0)
अणु
	पूर्णांक frc_bits = max(IA_CSS_CTC_COEF_SHIFT, 16);
	पूर्णांक dy = y1 - y0;
	पूर्णांक dx = x1 - x0;
	पूर्णांक dydx_पूर्णांक;
	पूर्णांक dydx_frc;
	पूर्णांक sft;
	/* max_dydx = the maxinum gradient = the maximum y (gain) */
	पूर्णांक max_dydx = (1 << IA_CSS_CTC_COEF_SHIFT) - 1;

	अगर (dx == 0) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
				    "ctc_gradient() error, illegal division operation\n");
		वापस;
	पूर्ण अन्यथा अणु
		dydx_पूर्णांक = dy / dx;
		dydx_frc = ((dy - dydx_पूर्णांक * dx) << frc_bits) / dx;
	पूर्ण

	निश्चित(y0 >= 0 && y0 <= max_dydx);
	निश्चित(y1 >= 0 && y1 <= max_dydx);
	निश्चित(x0 < x1);
	निश्चित(dydx);
	निश्चित(shअगरt);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE, "ctc_gradient() enter:\n");

	/* search "sft" which meets this condition:
		   (1 << (IA_CSS_CTC_COEF_SHIFT - 1))
		<= (((भग्न)dy / (भग्न)dx) * (1 << sft))
		<= ((1 << IA_CSS_CTC_COEF_SHIFT) - 1) */
	क्रम (sft = 0; sft <= IA_CSS_CTC_COEF_SHIFT; sft++) अणु
		पूर्णांक पंचांगp_dydx = (dydx_पूर्णांक << sft)
			       + (dydx_frc >> (frc_bits - sft));
		अगर (पंचांगp_dydx <= max_dydx) अणु
			*dydx = पंचांगp_dydx;
			*shअगरt = sft;
		पूर्ण
		अगर (पंचांगp_dydx >= max_dydx)
			अवरोध;
	पूर्ण

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE, "ctc_gradient() leave:\n");
पूर्ण

व्योम
ia_css_ctc_encode(
    काष्ठा sh_css_isp_ctc_params *to,
    स्थिर काष्ठा ia_css_ctc_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	to->y0 = from->y0;
	to->y1 = from->y1;
	to->y2 = from->y2;
	to->y3 = from->y3;
	to->y4 = from->y4;
	to->y5 = from->y5;

	to->ce_gain_exp = from->ce_gain_exp;

	to->x1 = from->x1;
	to->x2 = from->x2;
	to->x3 = from->x3;
	to->x4 = from->x4;

	ctc_gradient(&to->dydx0,
		     &to->dydx0_shअगरt,
		     from->y1, from->y0,
		     from->x1, 0);

	ctc_gradient(&to->dydx1,
		     &to->dydx1_shअगरt,
		     from->y2, from->y1,
		     from->x2, from->x1);

	ctc_gradient(&to->dydx2,
		     &to->dydx2_shअगरt,
		     from->y3, from->y2,
		     from->x3, from->x2);

	ctc_gradient(&to->dydx3,
		     &to->dydx3_shअगरt,
		     from->y4, from->y3,
		     from->x4, from->x3);

	ctc_gradient(&to->dydx4,
		     &to->dydx4_shअगरt,
		     from->y5, from->y4,
		     SH_CSS_BAYER_MAXVAL, from->x4);
पूर्ण

व्योम
ia_css_ctc_dump(
    स्थिर काष्ठा sh_css_isp_ctc_params *ctc,
    अचिन्हित पूर्णांक level);
