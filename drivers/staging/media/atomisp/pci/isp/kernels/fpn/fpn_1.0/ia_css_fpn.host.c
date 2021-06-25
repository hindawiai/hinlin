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
#समावेश <ia_css_types.h>
#समावेश <sh_css_defs.h>
#समावेश <ia_css_debug.h>

#घोषणा IA_CSS_INCLUDE_CONFIGURATIONS
#समावेश "ia_css_isp_configs.h"
#समावेश "isp.h"

#समावेश "ia_css_fpn.host.h"

व्योम
ia_css_fpn_encode(
    काष्ठा sh_css_isp_fpn_params *to,
    स्थिर काष्ठा ia_css_fpn_table *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	to->shअगरt = from->shअगरt;
	to->enabled = from->data != शून्य;
पूर्ण

व्योम
ia_css_fpn_dump(
    स्थिर काष्ठा sh_css_isp_fpn_params *fpn,
    अचिन्हित पूर्णांक level)
अणु
	अगर (!fpn) वापस;
	ia_css_debug_dtrace(level, "Fixed Pattern Noise Reduction:\n");
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "fpn_shift", fpn->shअगरt);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "fpn_enabled", fpn->enabled);
पूर्ण

व्योम
ia_css_fpn_config(
    काष्ठा sh_css_isp_fpn_isp_config *to,
    स्थिर काष्ठा ia_css_fpn_configuration *from,
    अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक elems_a = ISP_VEC_NELEMS;

	(व्योम)size;
	ia_css_dma_configure_from_info(&to->port_b, from->info);
	to->width_a_over_b = elems_a / to->port_b.elems;

	/* Assume भागisiblity here, may need to generalize to fixed poपूर्णांक. */
	निश्चित(elems_a % to->port_b.elems == 0);
पूर्ण

व्योम
ia_css_fpn_configure(
    स्थिर काष्ठा ia_css_binary     *binary,
    स्थिर काष्ठा ia_css_frame_info *info)
अणु
	काष्ठा ia_css_frame_info my_info = IA_CSS_BINARY_DEFAULT_FRAME_INFO;
	स्थिर काष्ठा ia_css_fpn_configuration config = अणु
		&my_info
	पूर्ण;

	my_info.res.width       = CEIL_DIV(info->res.width, 2);		/* Packed by 2x */
	my_info.res.height      = info->res.height;
	my_info.padded_width    = CEIL_DIV(info->padded_width, 2);	/* Packed by 2x */
	my_info.क्रमmat          = info->क्रमmat;
	my_info.raw_bit_depth   = FPN_BITS_PER_PIXEL;
	my_info.raw_bayer_order = info->raw_bayer_order;
	my_info.crop_info       = info->crop_info;

	ia_css_configure_fpn(binary, &config);
पूर्ण
