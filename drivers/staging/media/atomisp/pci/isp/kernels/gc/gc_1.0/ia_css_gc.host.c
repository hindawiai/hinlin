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
#समावेश "sh_css_frac.h"
#समावेश "vamem.h"

#समावेश "ia_css_gc.host.h"

स्थिर काष्ठा ia_css_gc_config शेष_gc_config = अणु
	0,
	0
पूर्ण;

स्थिर काष्ठा ia_css_ce_config शेष_ce_config = अणु
	0,
	255
पूर्ण;

व्योम
ia_css_gc_encode(
    काष्ठा sh_css_isp_gc_params *to,
    स्थिर काष्ठा ia_css_gc_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	to->gain_k1 =
	    uDIGIT_FITTING((पूर्णांक)from->gain_k1, 16,
			   IA_CSS_GAMMA_GAIN_K_SHIFT);
	to->gain_k2 =
	    uDIGIT_FITTING((पूर्णांक)from->gain_k2, 16,
			   IA_CSS_GAMMA_GAIN_K_SHIFT);
पूर्ण

व्योम
ia_css_ce_encode(
    काष्ठा sh_css_isp_ce_params *to,
    स्थिर काष्ठा ia_css_ce_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	to->uv_level_min = from->uv_level_min;
	to->uv_level_max = from->uv_level_max;
पूर्ण

व्योम
ia_css_gc_vamem_encode(
    काष्ठा sh_css_isp_gc_vamem_params *to,
    स्थिर काष्ठा ia_css_gamma_table *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	स_नकल(&to->gc,  &from->data, माप(to->gc));
पूर्ण

#अगर_अघोषित IA_CSS_NO_DEBUG
व्योम
ia_css_gc_dump(
    स्थिर काष्ठा sh_css_isp_gc_params *gc,
    अचिन्हित पूर्णांक level)
अणु
	अगर (!gc) वापस;
	ia_css_debug_dtrace(level, "Gamma Correction:\n");
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "gamma_gain_k1", gc->gain_k1);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "gamma_gain_k2", gc->gain_k2);
पूर्ण

व्योम
ia_css_ce_dump(
    स्थिर काष्ठा sh_css_isp_ce_params *ce,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level, "Chroma Enhancement:\n");
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ce_uv_level_min", ce->uv_level_min);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ce_uv_level_max", ce->uv_level_max);
पूर्ण

व्योम
ia_css_gc_debug_dtrace(
    स्थिर काष्ठा ia_css_gc_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.gain_k1=%d, config.gain_k2=%d\n",
			    config->gain_k1, config->gain_k2);
पूर्ण

व्योम
ia_css_ce_debug_dtrace(
    स्थिर काष्ठा ia_css_ce_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.uv_level_min=%d, config.uv_level_max=%d\n",
			    config->uv_level_min, config->uv_level_max);
पूर्ण
#पूर्ण_अगर
