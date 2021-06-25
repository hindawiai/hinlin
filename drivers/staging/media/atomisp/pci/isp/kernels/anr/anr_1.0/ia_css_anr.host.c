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

#समावेश "ia_css_anr.host.h"

स्थिर काष्ठा ia_css_anr_config शेष_anr_config = अणु
	10,
	अणु
		0, 3, 1, 2, 3, 6, 4, 5, 1, 4, 2, 3, 2, 5, 3, 4,
		0, 3, 1, 2, 3, 6, 4, 5, 1, 4, 2, 3, 2, 5, 3, 4,
		0, 3, 1, 2, 3, 6, 4, 5, 1, 4, 2, 3, 2, 5, 3, 4,
		0, 3, 1, 2, 3, 6, 4, 5, 1, 4, 2, 3, 2, 5, 3, 4
	पूर्ण,
	अणु10, 20, 30पूर्ण
पूर्ण;

व्योम
ia_css_anr_encode(
    काष्ठा sh_css_isp_anr_params *to,
    स्थिर काष्ठा ia_css_anr_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	to->threshold = from->threshold;
पूर्ण

व्योम
ia_css_anr_dump(
    स्थिर काष्ठा sh_css_isp_anr_params *anr,
    अचिन्हित पूर्णांक level)
अणु
	अगर (!anr) वापस;
	ia_css_debug_dtrace(level, "Advance Noise Reduction:\n");
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "anr_threshold", anr->threshold);
पूर्ण

व्योम
ia_css_anr_debug_dtrace(
    स्थिर काष्ठा ia_css_anr_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.threshold=%d\n",
			    config->threshold);
पूर्ण
