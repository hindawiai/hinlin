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

#अगर_अघोषित __IA_CSS_OUTPUT_TYPES_H
#घोषणा __IA_CSS_OUTPUT_TYPES_H

/* @file
* CSS-API header file क्रम parameters of output frames.
*/

/* Output frame
 *
 *  ISP block: output frame
 */

//#समावेश "ia_css_frame_public.h"
काष्ठा ia_css_frame_info;

काष्ठा ia_css_output_configuration अणु
	स्थिर काष्ठा ia_css_frame_info *info;
पूर्ण;

काष्ठा ia_css_output0_configuration अणु
	स्थिर काष्ठा ia_css_frame_info *info;
पूर्ण;

काष्ठा ia_css_output1_configuration अणु
	स्थिर काष्ठा ia_css_frame_info *info;
पूर्ण;

काष्ठा ia_css_output_config अणु
	u8 enable_hflip;  /** enable horizontal output mirroring */
	u8 enable_vflip;  /** enable vertical output mirroring */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_OUTPUT_TYPES_H */
