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

#समावेश "ia_css_xnr.host.h"

स्थिर काष्ठा ia_css_xnr_config शेष_xnr_config = अणु
	/* शेष threshold 6400 translates to 25 on ISP. */
	6400
पूर्ण;

व्योम
ia_css_xnr_table_vamem_encode(
    काष्ठा sh_css_isp_xnr_vamem_params *to,
    स्थिर काष्ठा ia_css_xnr_table *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	स_नकल(&to->xnr,  &from->data, माप(to->xnr));
पूर्ण

व्योम
ia_css_xnr_encode(
    काष्ठा sh_css_isp_xnr_params *to,
    स्थिर काष्ठा ia_css_xnr_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;

	to->threshold =
	    (uपूर्णांक16_t)uDIGIT_FITTING(from->threshold, 16, SH_CSS_ISP_YUV_BITS);
पूर्ण

व्योम
ia_css_xnr_table_debug_dtrace(
    स्थिर काष्ठा ia_css_xnr_table *config,
    अचिन्हित पूर्णांक level)
अणु
	(व्योम)config;
	(व्योम)level;
पूर्ण

व्योम
ia_css_xnr_debug_dtrace(
    स्थिर काष्ठा ia_css_xnr_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.threshold=%d\n", config->threshold);
पूर्ण
