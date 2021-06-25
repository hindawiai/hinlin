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

#अगर_अघोषित __IA_CSS_CNR2_HOST_H
#घोषणा __IA_CSS_CNR2_HOST_H

#समावेश "ia_css_cnr2_types.h"
#समावेश "ia_css_cnr2_param.h"

बाह्य स्थिर काष्ठा ia_css_cnr_config शेष_cnr_config;

व्योम
ia_css_cnr_encode(
    काष्ठा sh_css_isp_cnr_params *to,
    स्थिर काष्ठा ia_css_cnr_config *from,
    अचिन्हित पूर्णांक size);

व्योम
ia_css_cnr_dump(
    स्थिर काष्ठा sh_css_isp_cnr_params *cnr,
    अचिन्हित पूर्णांक level);

व्योम
ia_css_cnr_debug_dtrace(
    स्थिर काष्ठा ia_css_cnr_config *config,
    अचिन्हित पूर्णांक level);

व्योम
ia_css_init_cnr2_state(
    व्योम/*काष्ठा sh_css_isp_cnr_vmem_state*/ * state,
    माप_प्रकार size);
#पूर्ण_अगर /* __IA_CSS_CNR2_HOST_H */
