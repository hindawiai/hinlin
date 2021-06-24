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
#समावेश "ia_css_crop.host.h"

अटल स्थिर काष्ठा ia_css_crop_configuration शेष_config = अणु
	.info = (काष्ठा ia_css_frame_info *)शून्य,
पूर्ण;

व्योम
ia_css_crop_encode(
    काष्ठा sh_css_isp_crop_isp_params *to,
    स्थिर काष्ठा ia_css_crop_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	to->crop_pos = from->crop_pos;
पूर्ण

व्योम
ia_css_crop_config(
    काष्ठा sh_css_isp_crop_isp_config *to,
    स्थिर काष्ठा ia_css_crop_configuration  *from,
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
ia_css_crop_configure(
    स्थिर काष्ठा ia_css_binary     *binary,
    स्थिर काष्ठा ia_css_frame_info *info)
अणु
	काष्ठा ia_css_crop_configuration config = शेष_config;

	config.info = info;

	ia_css_configure_crop(binary, &config);
पूर्ण
