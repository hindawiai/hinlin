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

#समावेश "ia_css_dp.host.h"

/* We use a dअगरferent set of DPC configuration parameters when
 * DPC is used beक्रमe OBC and NORM. Currently these parameters
 * are used in useहालs which selects both BDS and DPC.
 **/
स्थिर काष्ठा ia_css_dp_config शेष_dp_10bpp_config = अणु
	1024,
	2048,
	32768,
	32768,
	32768,
	32768
पूर्ण;

स्थिर काष्ठा ia_css_dp_config शेष_dp_config = अणु
	8192,
	2048,
	32768,
	32768,
	32768,
	32768
पूर्ण;

व्योम
ia_css_dp_encode(
    काष्ठा sh_css_isp_dp_params *to,
    स्थिर काष्ठा ia_css_dp_config *from,
    अचिन्हित पूर्णांक size)
अणु
	पूर्णांक gain = from->gain;
	पूर्णांक gr   = from->gr;
	पूर्णांक r    = from->r;
	पूर्णांक b    = from->b;
	पूर्णांक gb   = from->gb;

	(व्योम)size;
	to->threshold_single =
	    SH_CSS_BAYER_MAXVAL;
	to->threshold_2adjacent =
	    uDIGIT_FITTING(from->threshold, 16, SH_CSS_BAYER_BITS);
	to->gain =
	    uDIGIT_FITTING(from->gain, 8, SH_CSS_DP_GAIN_SHIFT);

	to->coef_rr_gr =
	    uDIGIT_FITTING(gain * gr / r, 8, SH_CSS_DP_GAIN_SHIFT);
	to->coef_rr_gb =
	    uDIGIT_FITTING(gain * gb / r, 8, SH_CSS_DP_GAIN_SHIFT);
	to->coef_bb_gb =
	    uDIGIT_FITTING(gain * gb / b, 8, SH_CSS_DP_GAIN_SHIFT);
	to->coef_bb_gr =
	    uDIGIT_FITTING(gain * gr / b, 8, SH_CSS_DP_GAIN_SHIFT);
	to->coef_gr_rr =
	    uDIGIT_FITTING(gain * r / gr, 8, SH_CSS_DP_GAIN_SHIFT);
	to->coef_gr_bb =
	    uDIGIT_FITTING(gain * b / gr, 8, SH_CSS_DP_GAIN_SHIFT);
	to->coef_gb_bb =
	    uDIGIT_FITTING(gain * b / gb, 8, SH_CSS_DP_GAIN_SHIFT);
	to->coef_gb_rr =
	    uDIGIT_FITTING(gain * r / gb, 8, SH_CSS_DP_GAIN_SHIFT);
पूर्ण

व्योम
ia_css_dp_dump(
    स्थिर काष्ठा sh_css_isp_dp_params *dp,
    अचिन्हित पूर्णांक level)
अणु
	अगर (!dp) वापस;
	ia_css_debug_dtrace(level, "Defect Pixel Correction:\n");
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "dp_threshold_single_w_2adj_on",
			    dp->threshold_single);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "dp_threshold_2adj_w_2adj_on",
			    dp->threshold_2adjacent);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "dp_gain", dp->gain);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "dpc_coef_rr_gr", dp->coef_rr_gr);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "dpc_coef_rr_gb", dp->coef_rr_gb);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "dpc_coef_bb_gb", dp->coef_bb_gb);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "dpc_coef_bb_gr", dp->coef_bb_gr);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "dpc_coef_gr_rr", dp->coef_gr_rr);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "dpc_coef_gr_bb", dp->coef_gr_bb);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "dpc_coef_gb_bb", dp->coef_gb_bb);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "dpc_coef_gb_rr", dp->coef_gb_rr);
पूर्ण

व्योम
ia_css_dp_debug_dtrace(
    स्थिर काष्ठा ia_css_dp_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.threshold=%d, config.gain=%d\n",
			    config->threshold, config->gain);
पूर्ण

व्योम
ia_css_init_dp_state(
    व्योम/*काष्ठा sh_css_isp_dp_vmem_state*/ * state,
    माप_प्रकार size)
अणु
	स_रखो(state, 0, size);
पूर्ण
