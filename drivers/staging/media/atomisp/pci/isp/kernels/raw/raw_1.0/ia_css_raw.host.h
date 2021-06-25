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

#अगर_अघोषित __IA_CSS_RAW_HOST_H
#घोषणा __IA_CSS_RAW_HOST_H

#समावेश "ia_css_binary.h"

#समावेश "ia_css_raw_types.h"
#समावेश "ia_css_raw_param.h"

व्योम
ia_css_raw_config(
    काष्ठा sh_css_isp_raw_isp_config      *to,
    स्थिर काष्ठा ia_css_raw_configuration *from,
    अचिन्हित पूर्णांक size);

व्योम
ia_css_raw_configure(
    स्थिर काष्ठा sh_css_sp_pipeline *pipe,
    स्थिर काष्ठा ia_css_binary     *binary,
    स्थिर काष्ठा ia_css_frame_info *in_info,
    स्थिर काष्ठा ia_css_frame_info *पूर्णांकernal_info,
    bool two_ppc,
    bool deपूर्णांकerleaved);

#पूर्ण_अगर /* __IA_CSS_RAW_HOST_H */
