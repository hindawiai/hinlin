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

#अगर_अघोषित __IA_CSS_ITERATOR_PARAM_H
#घोषणा __IA_CSS_ITERATOR_PARAM_H

#समावेश "ia_css_types.h" /* ia_css_resolution */
#समावेश "ia_css_frame_public.h" /* ia_css_frame_info */
#समावेश "ia_css_frame_comm.h" /* ia_css_frame_sp_info */

काष्ठा ia_css_iterator_configuration अणु
	स्थिर काष्ठा ia_css_frame_info *input_info;
	स्थिर काष्ठा ia_css_frame_info *पूर्णांकernal_info;
	स्थिर काष्ठा ia_css_frame_info *output_info;
	स्थिर काष्ठा ia_css_frame_info *vf_info;
	स्थिर काष्ठा ia_css_resolution *dvs_envelope;
पूर्ण;

काष्ठा sh_css_isp_iterator_isp_config अणु
	काष्ठा ia_css_frame_sp_info input_info;
	काष्ठा ia_css_frame_sp_info पूर्णांकernal_info;
	काष्ठा ia_css_frame_sp_info output_info;
	काष्ठा ia_css_frame_sp_info vf_info;
	काष्ठा ia_css_sp_resolution dvs_envelope;
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_ITERATOR_PARAM_H */
