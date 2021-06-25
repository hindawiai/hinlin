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

#अगर_अघोषित __IA_CSS_CSC_HOST_H
#घोषणा __IA_CSS_CSC_HOST_H

#समावेश "ia_css_csc_types.h"
#समावेश "ia_css_csc_param.h"

बाह्य स्थिर काष्ठा ia_css_cc_config शेष_cc_config;

व्योम
ia_css_encode_cc(
    काष्ठा sh_css_isp_csc_params *to,
    स्थिर काष्ठा ia_css_cc_config *from,
    अचिन्हित पूर्णांक size);

व्योम
ia_css_csc_encode(
    काष्ठा sh_css_isp_csc_params *to,
    स्थिर काष्ठा ia_css_cc_config *from,
    अचिन्हित पूर्णांक size);

#अगर_अघोषित IA_CSS_NO_DEBUG
व्योम
ia_css_cc_dump(
    स्थिर काष्ठा sh_css_isp_csc_params *csc, अचिन्हित पूर्णांक level,
    स्थिर अक्षर *name);

व्योम
ia_css_csc_dump(
    स्थिर काष्ठा sh_css_isp_csc_params *csc,
    अचिन्हित पूर्णांक level);

व्योम
ia_css_cc_config_debug_dtrace(
    स्थिर काष्ठा ia_css_cc_config *config,
    अचिन्हित पूर्णांक level);

#घोषणा ia_css_csc_debug_dtrace ia_css_cc_config_debug_dtrace
#पूर्ण_अगर

#पूर्ण_अगर /* __IA_CSS_CSC_HOST_H */
