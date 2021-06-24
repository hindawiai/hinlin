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
#समावेश "ia_css_debug.h"
#पूर्ण_अगर
#समावेश "sh_css_frac.h"

#समावेश "ia_css_wb.host.h"

स्थिर काष्ठा ia_css_wb_config शेष_wb_config = अणु
	1,
	32768,
	32768,
	32768,
	32768
पूर्ण;

व्योम
ia_css_wb_encode(
    काष्ठा sh_css_isp_wb_params *to,
    स्थिर काष्ठा ia_css_wb_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	to->gain_shअगरt =
	    uISP_REG_BIT - from->पूर्णांकeger_bits;
	to->gain_gr =
	    uDIGIT_FITTING(from->gr, 16 - from->पूर्णांकeger_bits,
			   to->gain_shअगरt);
	to->gain_r =
	    uDIGIT_FITTING(from->r, 16 - from->पूर्णांकeger_bits,
			   to->gain_shअगरt);
	to->gain_b =
	    uDIGIT_FITTING(from->b, 16 - from->पूर्णांकeger_bits,
			   to->gain_shअगरt);
	to->gain_gb =
	    uDIGIT_FITTING(from->gb, 16 - from->पूर्णांकeger_bits,
			   to->gain_shअगरt);
पूर्ण

#अगर_अघोषित IA_CSS_NO_DEBUG
व्योम
ia_css_wb_dump(
    स्थिर काष्ठा sh_css_isp_wb_params *wb,
    अचिन्हित पूर्णांक level)
अणु
	अगर (!wb) वापस;
	ia_css_debug_dtrace(level, "White Balance:\n");
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "wb_gain_shift", wb->gain_shअगरt);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "wb_gain_gr", wb->gain_gr);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "wb_gain_r", wb->gain_r);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "wb_gain_b", wb->gain_b);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "wb_gain_gb", wb->gain_gb);
पूर्ण

व्योम
ia_css_wb_debug_dtrace(
    स्थिर काष्ठा ia_css_wb_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.integer_bits=%d, config.gr=%d, config.r=%d, config.b=%d, config.gb=%d\n",
			    config->पूर्णांकeger_bits,
			    config->gr, config->r,
			    config->b, config->gb);
पूर्ण
#पूर्ण_अगर
