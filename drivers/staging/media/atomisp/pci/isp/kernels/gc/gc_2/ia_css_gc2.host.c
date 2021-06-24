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
#समावेश "csc/csc_1.0/ia_css_csc.host.h"
#समावेश "vamem.h"

#समावेश "ia_css_gc2.host.h"

स्थिर काष्ठा ia_css_cc_config शेष_yuv2rgb_cc_config = अणु
	12,
	अणु4096, -4096, 4096, 4096, 4096, 0, 4096, -4096, -4096पूर्ण
पूर्ण;

स्थिर काष्ठा ia_css_cc_config शेष_rgb2yuv_cc_config = अणु
	13,
	अणु2449, 4809, 934, -1382, -2714, 4096, 4096, -3430, -666पूर्ण
पूर्ण;

व्योम
ia_css_yuv2rgb_encode(
    काष्ठा sh_css_isp_csc_params *to,
    स्थिर काष्ठा ia_css_cc_config *from,
    अचिन्हित पूर्णांक size)
अणु
	ia_css_encode_cc(to, from, size);
पूर्ण

व्योम
ia_css_rgb2yuv_encode(
    काष्ठा sh_css_isp_csc_params *to,
    स्थिर काष्ठा ia_css_cc_config *from,
    अचिन्हित पूर्णांक size)
अणु
	ia_css_encode_cc(to, from, size);
पूर्ण

व्योम
ia_css_r_gamma_vamem_encode(
    काष्ठा sh_css_isp_rgb_gamma_vamem_params *to,
    स्थिर काष्ठा ia_css_rgb_gamma_table *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	स_नकल(&to->gc,  &from->data, माप(to->gc));
पूर्ण

व्योम
ia_css_g_gamma_vamem_encode(
    काष्ठा sh_css_isp_rgb_gamma_vamem_params *to,
    स्थिर काष्ठा ia_css_rgb_gamma_table *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	स_नकल(&to->gc,  &from->data, माप(to->gc));
पूर्ण

व्योम
ia_css_b_gamma_vamem_encode(
    काष्ठा sh_css_isp_rgb_gamma_vamem_params *to,
    स्थिर काष्ठा ia_css_rgb_gamma_table *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	स_नकल(&to->gc,  &from->data, माप(to->gc));
पूर्ण

#अगर_अघोषित IA_CSS_NO_DEBUG
व्योम
ia_css_yuv2rgb_dump(
    स्थिर काष्ठा sh_css_isp_csc_params *yuv2rgb,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_cc_dump(yuv2rgb, level, "YUV to RGB Conversion");
पूर्ण

व्योम
ia_css_rgb2yuv_dump(
    स्थिर काष्ठा sh_css_isp_csc_params *rgb2yuv,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_cc_dump(rgb2yuv, level, "RGB to YUV Conversion");
पूर्ण

व्योम
ia_css_rgb_gamma_table_debug_dtrace(
    स्थिर काष्ठा ia_css_rgb_gamma_table *config,
    अचिन्हित पूर्णांक level)
अणु
	(व्योम)config;
	(व्योम)level;
पूर्ण
#पूर्ण_अगर
