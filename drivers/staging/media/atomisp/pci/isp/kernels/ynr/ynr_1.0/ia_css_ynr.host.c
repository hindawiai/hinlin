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

#समावेश "bnr/bnr_1.0/ia_css_bnr.host.h"
#समावेश "ia_css_ynr.host.h"

स्थिर काष्ठा ia_css_nr_config शेष_nr_config = अणु
	16384,
	8192,
	1280,
	0,
	0
पूर्ण;

स्थिर काष्ठा ia_css_ee_config शेष_ee_config = अणु
	8192,
	128,
	2048
पूर्ण;

व्योम
ia_css_nr_encode(
    काष्ठा sh_css_isp_ynr_params *to,
    स्थिर काष्ठा ia_css_nr_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	/* YNR (Y Noise Reduction) */
	to->threshold =
	    uDIGIT_FITTING(8192U, 16, SH_CSS_BAYER_BITS);
	to->gain_all =
	    uDIGIT_FITTING(from->ynr_gain, 16, SH_CSS_YNR_GAIN_SHIFT);
	to->gain_dir =
	    uDIGIT_FITTING(from->ynr_gain, 16, SH_CSS_YNR_GAIN_SHIFT);
	to->threshold_cb =
	    uDIGIT_FITTING(from->threshold_cb, 16, SH_CSS_BAYER_BITS);
	to->threshold_cr =
	    uDIGIT_FITTING(from->threshold_cr, 16, SH_CSS_BAYER_BITS);
पूर्ण

व्योम
ia_css_yee_encode(
    काष्ठा sh_css_isp_yee_params *to,
    स्थिर काष्ठा ia_css_yee_config *from,
    अचिन्हित पूर्णांक size)
अणु
	पूर्णांक asiWk1 = (पूर्णांक)from->ee.gain;
	पूर्णांक asiWk2 = asiWk1 / 8;
	पूर्णांक asiWk3 = asiWk1 / 4;

	(व्योम)size;
	/* YEE (Y Edge Enhancement) */
	to->dirthreshold_s =
	    min((uDIGIT_FITTING(from->nr.direction, 16, SH_CSS_BAYER_BITS)
		 << 1),
		SH_CSS_BAYER_MAXVAL);
	to->dirthreshold_g =
	    min((uDIGIT_FITTING(from->nr.direction, 16, SH_CSS_BAYER_BITS)
		 << 4),
		SH_CSS_BAYER_MAXVAL);
	to->dirthreshold_width_log2 =
	    uFRACTION_BITS_FITTING(8);
	to->dirthreshold_width =
	    1 << to->dirthreshold_width_log2;
	to->detailgain =
	    uDIGIT_FITTING(from->ee.detail_gain, 11,
			   SH_CSS_YEE_DETAIL_GAIN_SHIFT);
	to->coring_s =
	    (uDIGIT_FITTING(56U, 16, SH_CSS_BAYER_BITS) *
	     from->ee.threshold) >> 8;
	to->coring_g =
	    (uDIGIT_FITTING(224U, 16, SH_CSS_BAYER_BITS) *
	     from->ee.threshold) >> 8;
	/* 8; // *1.125 ->[s4.8] */
	to->scale_plus_s =
	    (asiWk1 + asiWk2) >> (11 - SH_CSS_YEE_SCALE_SHIFT);
	/* 8; // ( * -.25)->[s4.8] */
	to->scale_plus_g =
	    (0 - asiWk3) >> (11 - SH_CSS_YEE_SCALE_SHIFT);
	/* 8; // *0.875 ->[s4.8] */
	to->scale_minus_s =
	    (asiWk1 - asiWk2) >> (11 - SH_CSS_YEE_SCALE_SHIFT);
	/* 8; // ( *.25 ) ->[s4.8] */
	to->scale_minus_g =
	    (asiWk3) >> (11 - SH_CSS_YEE_SCALE_SHIFT);
	to->clip_plus_s =
	    uDIGIT_FITTING(32760U, 16, SH_CSS_BAYER_BITS);
	to->clip_plus_g = 0;
	to->clip_minus_s =
	    uDIGIT_FITTING(504U, 16, SH_CSS_BAYER_BITS);
	to->clip_minus_g =
	    uDIGIT_FITTING(32256U, 16, SH_CSS_BAYER_BITS);
	to->Yclip = SH_CSS_BAYER_MAXVAL;
पूर्ण

व्योम
ia_css_nr_dump(
    स्थिर काष्ठा sh_css_isp_ynr_params *ynr,
    अचिन्हित पूर्णांक level)
अणु
	अगर (!ynr) वापस;
	ia_css_debug_dtrace(level,
			    "Y Noise Reduction:\n");
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ynr_threshold", ynr->threshold);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ynr_gain_all", ynr->gain_all);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ynr_gain_dir", ynr->gain_dir);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ynr_threshold_cb", ynr->threshold_cb);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ynr_threshold_cr", ynr->threshold_cr);
पूर्ण

व्योम
ia_css_yee_dump(
    स्थिर काष्ठा sh_css_isp_yee_params *yee,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "Y Edge Enhancement:\n");
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ynryee_dirthreshold_s",
			    yee->dirthreshold_s);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ynryee_dirthreshold_g",
			    yee->dirthreshold_g);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ynryee_dirthreshold_width_log2",
			    yee->dirthreshold_width_log2);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ynryee_dirthreshold_width",
			    yee->dirthreshold_width);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "yee_detailgain",
			    yee->detailgain);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "yee_coring_s",
			    yee->coring_s);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "yee_coring_g",
			    yee->coring_g);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "yee_scale_plus_s",
			    yee->scale_plus_s);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "yee_scale_plus_g",
			    yee->scale_plus_g);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "yee_scale_minus_s",
			    yee->scale_minus_s);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "yee_scale_minus_g",
			    yee->scale_minus_g);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "yee_clip_plus_s",
			    yee->clip_plus_s);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "yee_clip_plus_g",
			    yee->clip_plus_g);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "yee_clip_minus_s",
			    yee->clip_minus_s);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "yee_clip_minus_g",
			    yee->clip_minus_g);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ynryee_Yclip",
			    yee->Yclip);
पूर्ण

व्योम
ia_css_nr_debug_dtrace(
    स्थिर काष्ठा ia_css_nr_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.direction=%d, config.bnr_gain=%d, config.ynr_gain=%d, config.threshold_cb=%d, config.threshold_cr=%d\n",
			    config->direction,
			    config->bnr_gain, config->ynr_gain,
			    config->threshold_cb, config->threshold_cr);
पूर्ण

व्योम
ia_css_ee_debug_dtrace(
    स्थिर काष्ठा ia_css_ee_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.threshold=%d, config.gain=%d, config.detail_gain=%d\n",
			    config->threshold, config->gain, config->detail_gain);
पूर्ण

व्योम
ia_css_init_ynr_state(
    व्योम/*काष्ठा sh_css_isp_ynr_vmem_state*/ * state,
    माप_प्रकार size)
अणु
	स_रखो(state, 0, size);
पूर्ण
