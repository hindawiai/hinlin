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

#अगर_अघोषित __IA_CSS_QPLANE_HOST_H
#घोषणा __IA_CSS_QPLANE_HOST_H

#समावेश <ia_css_frame_खुला.h>
#समावेश <ia_css_binary.h>

#अगर 0
/* Cannot be included, since sh_css_पूर्णांकernal.h is too generic
 * e.g. क्रम FW generation.
*/
#समावेश "sh_css_internal.h"	/* sh_css_sp_pipeline */
#पूर्ण_अगर

#समावेश "ia_css_qplane_types.h"
#समावेश "ia_css_qplane_param.h"

व्योम
ia_css_qplane_config(
    काष्ठा sh_css_isp_qplane_isp_config      *to,
    स्थिर काष्ठा ia_css_qplane_configuration *from,
    अचिन्हित पूर्णांक size);

व्योम
ia_css_qplane_configure(
    स्थिर काष्ठा sh_css_sp_pipeline *pipe,
    स्थिर काष्ठा ia_css_binary     *binary,
    स्थिर काष्ठा ia_css_frame_info *from);

#पूर्ण_अगर /* __IA_CSS_QPLANE_HOST_H */
