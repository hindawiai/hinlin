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

#समावेश "ia_css_properties.h"
#समावेश <निश्चित_support.h>
#समावेश "ia_css_types.h"
#समावेश "gdc_device.h"

व्योम
ia_css_get_properties(काष्ठा ia_css_properties *properties)
अणु
	निश्चित(properties);
	/*
	 * MW: We करोn't want to store the coordinates
	 * full range in memory: Truncate
	 */
	properties->gdc_coord_one = gdc_get_unity(GDC0_ID) / HRT_GDC_COORD_SCALE;

	properties->l1_base_is_index = true;

	properties->vamem_type = IA_CSS_VAMEM_TYPE_2;
पूर्ण
