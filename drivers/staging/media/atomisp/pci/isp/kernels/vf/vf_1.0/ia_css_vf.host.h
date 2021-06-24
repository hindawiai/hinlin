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

#अगर_अघोषित __IA_CSS_VF_HOST_H
#घोषणा __IA_CSS_VF_HOST_H

#समावेश "ia_css_frame_public.h"
#समावेश "ia_css_binary.h"

#समावेश "ia_css_vf_types.h"
#समावेश "ia_css_vf_param.h"

/* compute the log2 of the करोwnscale factor needed to get बंदst
 * to the requested viewfinder resolution on the upper side. The output cannot
 * be smaller than the requested viewfinder resolution.
 */
पूर्णांक
sh_css_vf_करोwnscale_log2(
    स्थिर काष्ठा ia_css_frame_info *out_info,
    स्थिर काष्ठा ia_css_frame_info *vf_info,
    अचिन्हित पूर्णांक *करोwnscale_log2);

व्योम
ia_css_vf_config(
    काष्ठा sh_css_isp_vf_isp_config *to,
    स्थिर काष्ठा ia_css_vf_configuration *from,
    अचिन्हित पूर्णांक size);

पूर्णांक
ia_css_vf_configure(
    स्थिर काष्ठा ia_css_binary *binary,
    स्थिर काष्ठा ia_css_frame_info *out_info,
    काष्ठा ia_css_frame_info *vf_info,
    अचिन्हित पूर्णांक *करोwnscale_log2);

#पूर्ण_अगर /* __IA_CSS_VF_HOST_H */
