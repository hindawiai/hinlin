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
#समावेश "ia_css_frame.h"
#समावेश "sh_css_defs.h"
#समावेश "ia_css_debug.h"
#समावेश "sh_css_frac.h"
#समावेश "assert_support.h"
#घोषणा IA_CSS_INCLUDE_CONFIGURATIONS
#समावेश "ia_css_isp_configs.h"
#समावेश "isp.h"

#समावेश "ia_css_tnr.host.h"
स्थिर काष्ठा ia_css_tnr_config शेष_tnr_config = अणु
	32768,
	32,
	32,
पूर्ण;

व्योम
ia_css_tnr_encode(
    काष्ठा sh_css_isp_tnr_params *to,
    स्थिर काष्ठा ia_css_tnr_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	to->coef =
	    uDIGIT_FITTING(from->gain, 16, SH_CSS_TNR_COEF_SHIFT);
	to->threshold_Y =
	    uDIGIT_FITTING(from->threshold_y, 16, SH_CSS_ISP_YUV_BITS);
	to->threshold_C =
	    uDIGIT_FITTING(from->threshold_uv, 16, SH_CSS_ISP_YUV_BITS);
पूर्ण

व्योम
ia_css_tnr_dump(
    स्थिर काष्ठा sh_css_isp_tnr_params *tnr,
    अचिन्हित पूर्णांक level)
अणु
	अगर (!tnr) वापस;
	ia_css_debug_dtrace(level, "Temporal Noise Reduction:\n");
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "tnr_coef", tnr->coef);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "tnr_threshold_Y", tnr->threshold_Y);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "tnr_threshold_C", tnr->threshold_C);
पूर्ण

व्योम
ia_css_tnr_debug_dtrace(
    स्थिर काष्ठा ia_css_tnr_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.gain=%d, config.threshold_y=%d, config.threshold_uv=%d\n",
			    config->gain,
			    config->threshold_y, config->threshold_uv);
पूर्ण

व्योम
ia_css_tnr_config(
    काष्ठा sh_css_isp_tnr_isp_config *to,
    स्थिर काष्ठा ia_css_tnr_configuration *from,
    अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक elems_a = ISP_VEC_NELEMS;
	अचिन्हित पूर्णांक i;

	(व्योम)size;
	ia_css_dma_configure_from_info(&to->port_b, &from->tnr_frames[0]->info);
	to->width_a_over_b = elems_a / to->port_b.elems;
	to->frame_height = from->tnr_frames[0]->info.res.height;
	क्रम (i = 0; i < NUM_TNR_FRAMES; i++) अणु
		to->tnr_frame_addr[i] = from->tnr_frames[i]->data +
					from->tnr_frames[i]->planes.yuyv.offset;
	पूर्ण

	/* Assume भागisiblity here, may need to generalize to fixed poपूर्णांक. */
	निश्चित(elems_a % to->port_b.elems == 0);
पूर्ण

व्योम
ia_css_tnr_configure(
    स्थिर काष्ठा ia_css_binary     *binary,
    स्थिर काष्ठा ia_css_frame * स्थिर *frames)
अणु
	काष्ठा ia_css_tnr_configuration config;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < NUM_TNR_FRAMES; i++)
		config.tnr_frames[i] = frames[i];

	ia_css_configure_tnr(binary, &config);
पूर्ण

व्योम
ia_css_init_tnr_state(
    काष्ठा sh_css_isp_tnr_dmem_state *state,
    माप_प्रकार size)
अणु
	(व्योम)size;

	निश्चित(NUM_TNR_FRAMES >= 2);
	निश्चित(माप(*state) == size);
	state->tnr_in_buf_idx = 0;
	state->tnr_out_buf_idx = 1;
पूर्ण
