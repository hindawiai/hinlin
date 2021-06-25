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

#समावेश <निश्चित_support.h>
#समावेश <ia_css_frame_खुला.h>
#समावेश <ia_css_frame.h>
#समावेश <ia_css_binary.h>
#घोषणा IA_CSS_INCLUDE_CONFIGURATIONS
#समावेश "ia_css_isp_configs.h"
#समावेश "isp.h"
#समावेश "ia_css_ref.host.h"

व्योम
ia_css_ref_config(
    काष्ठा sh_css_isp_ref_isp_config *to,
    स्थिर काष्ठा ia_css_ref_configuration  *from,
    अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक elems_a = ISP_VEC_NELEMS, i;

	अगर (from->ref_frames[0]) अणु
		ia_css_dma_configure_from_info(&to->port_b, &from->ref_frames[0]->info);
		to->width_a_over_b = elems_a / to->port_b.elems;
		to->dvs_frame_delay = from->dvs_frame_delay;
	पूर्ण अन्यथा अणु
		to->width_a_over_b = 1;
		to->dvs_frame_delay = 0;
		to->port_b.elems = elems_a;
	पूर्ण
	क्रम (i = 0; i < MAX_NUM_VIDEO_DELAY_FRAMES; i++) अणु
		अगर (from->ref_frames[i]) अणु
			to->ref_frame_addr_y[i] = from->ref_frames[i]->data +
						  from->ref_frames[i]->planes.yuv.y.offset;
			to->ref_frame_addr_c[i] = from->ref_frames[i]->data +
						  from->ref_frames[i]->planes.yuv.u.offset;
		पूर्ण अन्यथा अणु
			to->ref_frame_addr_y[i] = 0;
			to->ref_frame_addr_c[i] = 0;
		पूर्ण
	पूर्ण

	/* Assume भागisiblity here, may need to generalize to fixed poपूर्णांक. */
	निश्चित(elems_a % to->port_b.elems == 0);
पूर्ण

व्योम
ia_css_ref_configure(
    स्थिर काष्ठा ia_css_binary     *binary,
    स्थिर काष्ठा ia_css_frame * स्थिर *ref_frames,
    स्थिर uपूर्णांक32_t dvs_frame_delay)
अणु
	काष्ठा ia_css_ref_configuration config;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MAX_NUM_VIDEO_DELAY_FRAMES; i++)
		config.ref_frames[i] = ref_frames[i];
	config.dvs_frame_delay = dvs_frame_delay;
	ia_css_configure_ref(binary, &config);
पूर्ण

व्योम
ia_css_init_ref_state(
    काष्ठा sh_css_isp_ref_dmem_state *state,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	निश्चित(MAX_NUM_VIDEO_DELAY_FRAMES >= 2);
	state->ref_in_buf_idx = 0;
	state->ref_out_buf_idx = 1;
पूर्ण
