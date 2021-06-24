<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित __IA_CSS_GC2_HOST_H
#घोषणा __IA_CSS_GC2_HOST_H

#समावेश "ia_css_gc2_types.h"
#समावेश "ia_css_gc2_param.h"
#समावेश "ia_css_gc2_table.host.h"

बाह्य स्थिर काष्ठा ia_css_cc_config शेष_yuv2rgb_cc_config;
बाह्य स्थिर काष्ठा ia_css_cc_config शेष_rgb2yuv_cc_config;

व्योम
ia_css_yuv2rgb_encode(
    काष्ठा sh_css_isp_csc_params *to,
    स्थिर काष्ठा ia_css_cc_config *from,
    अचिन्हित पूर्णांक size);

व्योम
ia_css_rgb2yuv_encode(
    काष्ठा sh_css_isp_csc_params *to,
    स्थिर काष्ठा ia_css_cc_config *from,
    अचिन्हित पूर्णांक size);

व्योम
ia_css_r_gamma_vamem_encode(
    काष्ठा sh_css_isp_rgb_gamma_vamem_params *to,
    स्थिर काष्ठा ia_css_rgb_gamma_table *from,
    अचिन्हित पूर्णांक size);

व्योम
ia_css_g_gamma_vamem_encode(
    काष्ठा sh_css_isp_rgb_gamma_vamem_params *to,
    स्थिर काष्ठा ia_css_rgb_gamma_table *from,
    अचिन्हित पूर्णांक size);

व्योम
ia_css_b_gamma_vamem_encode(
    काष्ठा sh_css_isp_rgb_gamma_vamem_params *to,
    स्थिर काष्ठा ia_css_rgb_gamma_table *from,
    अचिन्हित पूर्णांक size);

#अगर_अघोषित IA_CSS_NO_DEBUG
व्योम
ia_css_yuv2rgb_dump(
    स्थिर काष्ठा sh_css_isp_csc_params *yuv2rgb,
    अचिन्हित पूर्णांक level);

व्योम
ia_css_rgb2yuv_dump(
    स्थिर काष्ठा sh_css_isp_csc_params *rgb2yuv,
    अचिन्हित पूर्णांक level);

व्योम
ia_css_rgb_gamma_table_debug_dtrace(
    स्थिर काष्ठा ia_css_rgb_gamma_table *config,
    अचिन्हित पूर्णांक level);

#घोषणा ia_css_yuv2rgb_debug_dtrace ia_css_cc_config_debug_dtrace
#घोषणा ia_css_rgb2yuv_debug_dtrace ia_css_cc_config_debug_dtrace
#घोषणा ia_css_r_gamma_debug_dtrace ia_css_rgb_gamma_table_debug_dtrace
#घोषणा ia_css_g_gamma_debug_dtrace ia_css_rgb_gamma_table_debug_dtrace
#घोषणा ia_css_b_gamma_debug_dtrace ia_css_rgb_gamma_table_debug_dtrace

#पूर्ण_अगर

#पूर्ण_अगर /* __IA_CSS_GC2_HOST_H */
