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

#अगर !defined(HAS_NO_HMEM)

#समावेश "ia_css_types.h"
#समावेश "sh_css_internal.h"
#समावेश "assert_support.h"
#समावेश "sh_css_frac.h"

#समावेश "ia_css_bh.host.h"

व्योम
ia_css_bh_hmem_decode(
    काष्ठा ia_css_3a_rgby_output *out_ptr,
    स्थिर काष्ठा ia_css_bh_table *hmem_buf)
अणु
	पूर्णांक i;

	/*
	 * No weighted histogram, hence no grid definition
	 */
	अगर (!hmem_buf)
		वापस;
	निश्चित(माप_hmem(HMEM0_ID) == माप(*hmem_buf));

	/* Deपूर्णांकerleave */
	क्रम (i = 0; i < HMEM_UNIT_SIZE; i++) अणु
		out_ptr[i].r = hmem_buf->hmem[BH_COLOR_R][i];
		out_ptr[i].g = hmem_buf->hmem[BH_COLOR_G][i];
		out_ptr[i].b = hmem_buf->hmem[BH_COLOR_B][i];
		out_ptr[i].y = hmem_buf->hmem[BH_COLOR_Y][i];
		/* sh_css_prपूर्णांक ("hmem[%d] = %d, %d, %d, %d\n",
			i, out_ptr[i].r, out_ptr[i].g, out_ptr[i].b, out_ptr[i].y); */
	पूर्ण
पूर्ण

व्योम
ia_css_bh_encode(
    काष्ठा sh_css_isp_bh_params *to,
    स्थिर काष्ठा ia_css_3a_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	/* coefficients to calculate Y */
	to->y_coef_r =
	    uDIGIT_FITTING(from->ae_y_coef_r, 16, SH_CSS_AE_YCOEF_SHIFT);
	to->y_coef_g =
	    uDIGIT_FITTING(from->ae_y_coef_g, 16, SH_CSS_AE_YCOEF_SHIFT);
	to->y_coef_b =
	    uDIGIT_FITTING(from->ae_y_coef_b, 16, SH_CSS_AE_YCOEF_SHIFT);
पूर्ण

#पूर्ण_अगर
