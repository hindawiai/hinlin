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

#अगर_अघोषित __IA_CSS_FORMATS_HOST_H
#घोषणा __IA_CSS_FORMATS_HOST_H

#समावेश "ia_css_formats_types.h"
#समावेश "ia_css_formats_param.h"

बाह्य स्थिर काष्ठा ia_css_क्रमmats_config शेष_क्रमmats_config;

व्योम
ia_css_क्रमmats_encode(
    काष्ठा sh_css_isp_क्रमmats_params *to,
    स्थिर काष्ठा ia_css_क्रमmats_config *from,
    अचिन्हित पूर्णांक size);
#अगर_अघोषित IA_CSS_NO_DEBUG
/* FIXME: See BZ 4427 */
व्योम
ia_css_क्रमmats_dump(
    स्थिर काष्ठा sh_css_isp_क्रमmats_params *क्रमmats,
    अचिन्हित पूर्णांक level);
#पूर्ण_अगर

#अगर_अघोषित IA_CSS_NO_DEBUG
/* FIXME: See BZ 4427 */
व्योम
ia_css_क्रमmats_debug_dtrace(
    स्थिर काष्ठा ia_css_क्रमmats_config *क्रमmats,
    अचिन्हित पूर्णांक level);
#पूर्ण_अगर /*IA_CSS_NO_DEBUG*/

#पूर्ण_अगर /* __IA_CSS_FORMATS_HOST_H */
