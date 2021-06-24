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
#समावेश "sh_css_frac.h"

#समावेश "ia_css_bnr.host.h"

व्योम
ia_css_bnr_encode(
    काष्ठा sh_css_isp_bnr_params *to,
    स्थिर काष्ठा ia_css_nr_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	/* BNR (Bayer Noise Reduction) */
	to->threshold_low =
	    uDIGIT_FITTING(from->direction, 16, SH_CSS_BAYER_BITS);
	to->threshold_width_log2 = uFRACTION_BITS_FITTING(8);
	to->threshold_width =
	    1 << to->threshold_width_log2;
	to->gain_all =
	    uDIGIT_FITTING(from->bnr_gain, 16, SH_CSS_BNR_GAIN_SHIFT);
	to->gain_dir =
	    uDIGIT_FITTING(from->bnr_gain, 16, SH_CSS_BNR_GAIN_SHIFT);
	to->clip = uDIGIT_FITTING(16384U, 16, SH_CSS_BAYER_BITS);
पूर्ण

व्योम
ia_css_bnr_dump(
    स्थिर काष्ठा sh_css_isp_bnr_params *bnr,
    अचिन्हित पूर्णांक level)
अणु
	अगर (!bnr) वापस;
	ia_css_debug_dtrace(level, "Bayer Noise Reduction:\n");
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "bnr_gain_all", bnr->gain_all);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "bnr_gain_dir", bnr->gain_dir);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "bnr_threshold_low",
			    bnr->threshold_low);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "bnr_threshold_width_log2",
			    bnr->threshold_width_log2);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "bnr_threshold_width",
			    bnr->threshold_width);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "bnr_clip", bnr->clip);
पूर्ण
