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
#समावेश "ia_css_conversion.host.h"

स्थिर काष्ठा ia_css_conversion_config शेष_conversion_config = अणु
	0,
	0,
	0,
	0,
पूर्ण;

व्योम
ia_css_conversion_encode(
    काष्ठा sh_css_isp_conversion_params *to,
    स्थिर काष्ठा ia_css_conversion_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	to->en     = from->en;
	to->dummy0 = from->dummy0;
	to->dummy1 = from->dummy1;
	to->dummy2 = from->dummy2;
पूर्ण
