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

#अगर_अघोषित __IA_CSS_GC_HOST_H
#घोषणा __IA_CSS_GC_HOST_H

#समावेश "ia_css_gc_param.h"
#समावेश "ia_css_gc_table.host.h"

बाह्य स्थिर काष्ठा ia_css_gc_config शेष_gc_config;
बाह्य स्थिर काष्ठा ia_css_ce_config शेष_ce_config;

व्योम
ia_css_gc_encode(
    काष्ठा sh_css_isp_gc_params *to,
    स्थिर काष्ठा ia_css_gc_config *from,
    अचिन्हित पूर्णांक size);

व्योम
ia_css_gc_vamem_encode(
    काष्ठा sh_css_isp_gc_vamem_params *to,
    स्थिर काष्ठा ia_css_gamma_table *from,
    अचिन्हित पूर्णांक size);

व्योम
ia_css_ce_encode(
    काष्ठा sh_css_isp_ce_params *to,
    स्थिर काष्ठा ia_css_ce_config *from,
    अचिन्हित पूर्णांक size);

#अगर_अघोषित IA_CSS_NO_DEBUG
व्योम
ia_css_gc_dump(
    स्थिर काष्ठा sh_css_isp_gc_params *gc,
    अचिन्हित पूर्णांक level);

व्योम
ia_css_ce_dump(
    स्थिर काष्ठा sh_css_isp_ce_params *ce,
    अचिन्हित पूर्णांक level);

व्योम
ia_css_gc_debug_dtrace(
    स्थिर काष्ठा ia_css_gc_config *config,
    अचिन्हित पूर्णांक level);

व्योम
ia_css_ce_debug_dtrace(
    स्थिर काष्ठा ia_css_ce_config *config,
    अचिन्हित पूर्णांक level);

#पूर्ण_अगर

#पूर्ण_अगर /* __IA_CSS_GC_HOST_H */
