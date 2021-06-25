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
#समावेश "sh_css_frac.h"
#अगर_अघोषित IA_CSS_NO_DEBUG
#समावेश "ia_css_debug.h"
#पूर्ण_अगर
#समावेश "isp.h"
#समावेश "ia_css_ob2.host.h"

स्थिर काष्ठा ia_css_ob2_config शेष_ob2_config = अणु
	0,
	0,
	0,
	0
पूर्ण;

व्योम
ia_css_ob2_encode(
    काष्ठा sh_css_isp_ob2_params *to,
    स्थिर काष्ठा ia_css_ob2_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;

	/* Blacklevels types are u0_16 */
	to->blacklevel_gr = uDIGIT_FITTING(from->level_gr, 16, SH_CSS_BAYER_BITS);
	to->blacklevel_r  = uDIGIT_FITTING(from->level_r,  16, SH_CSS_BAYER_BITS);
	to->blacklevel_b  = uDIGIT_FITTING(from->level_b,  16, SH_CSS_BAYER_BITS);
	to->blacklevel_gb = uDIGIT_FITTING(from->level_gb, 16, SH_CSS_BAYER_BITS);
पूर्ण

#अगर_अघोषित IA_CSS_NO_DEBUG
व्योम
ia_css_ob2_dump(
    स्थिर काष्ठा sh_css_isp_ob2_params *ob2,
    अचिन्हित पूर्णांक level)
अणु
	अगर (!ob2)
		वापस;

	ia_css_debug_dtrace(level, "Optical Black 2:\n");
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ob2_blacklevel_gr", ob2->blacklevel_gr);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ob2_blacklevel_r", ob2->blacklevel_r);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ob2_blacklevel_b", ob2->blacklevel_b);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ob2_blacklevel_gb", ob2->blacklevel_gb);
पूर्ण

व्योम
ia_css_ob2_debug_dtrace(
    स्थिर काष्ठा ia_css_ob2_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.level_gr=%d, config.level_r=%d, config.level_b=%d,  config.level_gb=%d, ",
			    config->level_gr, config->level_r,
			    config->level_b, config->level_gb);
पूर्ण
#पूर्ण_अगर
