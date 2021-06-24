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
#समावेश "ia_css_de.host.h"

स्थिर काष्ठा ia_css_de_config शेष_de_config = अणु
	0,
	0,
	0
पूर्ण;

व्योम
ia_css_de_encode(
    काष्ठा sh_css_isp_de_params *to,
    स्थिर काष्ठा ia_css_de_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	to->pixelnoise =
	    uDIGIT_FITTING(from->pixelnoise, 16, SH_CSS_BAYER_BITS);
	to->c1_coring_threshold =
	    uDIGIT_FITTING(from->c1_coring_threshold, 16,
			   SH_CSS_BAYER_BITS);
	to->c2_coring_threshold =
	    uDIGIT_FITTING(from->c2_coring_threshold, 16,
			   SH_CSS_BAYER_BITS);
पूर्ण

व्योम
ia_css_de_dump(
    स्थिर काष्ठा sh_css_isp_de_params *de,
    अचिन्हित पूर्णांक level)
अणु
	अगर (!de) वापस;
	ia_css_debug_dtrace(level, "Demosaic:\n");
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "de_pixelnoise", de->pixelnoise);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "de_c1_coring_threshold",
			    de->c1_coring_threshold);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "de_c2_coring_threshold",
			    de->c2_coring_threshold);
पूर्ण

व्योम
ia_css_de_debug_dtrace(
    स्थिर काष्ठा ia_css_de_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.pixelnoise=%d, config.c1_coring_threshold=%d, config.c2_coring_threshold=%d\n",
			    config->pixelnoise,
			    config->c1_coring_threshold, config->c2_coring_threshold);
पूर्ण

व्योम
ia_css_init_de_state(
    व्योम/*काष्ठा sh_css_isp_de_vmem_state*/ * state,
    माप_प्रकार size)
अणु
	स_रखो(state, 0, size);
पूर्ण
