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

#अगर_अघोषित __IA_CSS_CTC2_HOST_H
#घोषणा __IA_CSS_CTC2_HOST_H

#समावेश "ia_css_ctc2_param.h"
#समावेश "ia_css_ctc2_types.h"

बाह्य स्थिर काष्ठा ia_css_ctc2_config शेष_ctc2_config;

/*Encode Functions to translate parameters from userspace पूर्णांकo ISP space*/

व्योम ia_css_ctc2_vmem_encode(काष्ठा ia_css_isp_ctc2_vmem_params *to,
			     स्थिर काष्ठा ia_css_ctc2_config *from,
			     माप_प्रकार size);

व्योम ia_css_ctc2_encode(काष्ठा ia_css_isp_ctc2_dmem_params *to,
			काष्ठा ia_css_ctc2_config *from,
			माप_प्रकार size);

#पूर्ण_अगर /* __IA_CSS_CTC2_HOST_H */
