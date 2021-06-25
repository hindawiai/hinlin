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
#अगर_अघोषित IA_CSS_NO_DEBUG
/* FIXME: See BZ 4427 */
#समावेश "ia_css_debug.h"
#पूर्ण_अगर

#समावेश "ia_css_csc.host.h"

स्थिर काष्ठा ia_css_cc_config शेष_cc_config = अणु
	8,
	अणु255, 29, 120, 0, -374, -342, 0, -672, 301पूर्ण,
पूर्ण;

व्योम
ia_css_encode_cc(
    काष्ठा sh_css_isp_csc_params *to,
    स्थिर काष्ठा ia_css_cc_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
#अगर_अघोषित IA_CSS_NO_DEBUG
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE, "ia_css_encode_cc() enter:\n");
#पूर्ण_अगर

	to->m_shअगरt    = (पूर्णांक16_t)from->fraction_bits;
	to->m00 = (पूर्णांक16_t)from->matrix[0];
	to->m01 = (पूर्णांक16_t)from->matrix[1];
	to->m02 = (पूर्णांक16_t)from->matrix[2];
	to->m10 = (पूर्णांक16_t)from->matrix[3];
	to->m11 = (पूर्णांक16_t)from->matrix[4];
	to->m12 = (पूर्णांक16_t)from->matrix[5];
	to->m20 = (पूर्णांक16_t)from->matrix[6];
	to->m21 = (पूर्णांक16_t)from->matrix[7];
	to->m22 = (पूर्णांक16_t)from->matrix[8];

#अगर_अघोषित IA_CSS_NO_DEBUG
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE, "ia_css_encode_cc() leave:\n");
#पूर्ण_अगर
पूर्ण

व्योम
ia_css_csc_encode(
    काष्ठा sh_css_isp_csc_params *to,
    स्थिर काष्ठा ia_css_cc_config *from,
    अचिन्हित पूर्णांक size)
अणु
	ia_css_encode_cc(to, from, size);
पूर्ण

#अगर_अघोषित IA_CSS_NO_DEBUG
व्योम
ia_css_cc_dump(
    स्थिर काष्ठा sh_css_isp_csc_params *csc,
    अचिन्हित पूर्णांक level,
    स्थिर अक्षर *name)
अणु
	अगर (!csc) वापस;
	ia_css_debug_dtrace(level, "%s\n", name);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "m_shift",
			    csc->m_shअगरt);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "m00",
			    csc->m00);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "m01",
			    csc->m01);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "m02",
			    csc->m02);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "m10",
			    csc->m10);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "m11",
			    csc->m11);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "m12",
			    csc->m12);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "m20",
			    csc->m20);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "m21",
			    csc->m21);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "m22",
			    csc->m22);
पूर्ण

व्योम
ia_css_csc_dump(
    स्थिर काष्ठा sh_css_isp_csc_params *csc,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_cc_dump(csc, level, "Color Space Conversion");
पूर्ण

व्योम
ia_css_cc_config_debug_dtrace(
    स्थिर काष्ठा ia_css_cc_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.m[0]=%d, config.m[1]=%d, config.m[2]=%d, config.m[3]=%d, config.m[4]=%d, config.m[5]=%d, config.m[6]=%d, config.m[7]=%d, config.m[8]=%d\n",
			    config->matrix[0],
			    config->matrix[1], config->matrix[2],
			    config->matrix[3], config->matrix[4],
			    config->matrix[5], config->matrix[6],
			    config->matrix[7], config->matrix[8]);
पूर्ण
#पूर्ण_अगर
