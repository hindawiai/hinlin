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

#अगर_अघोषित __IA_CSS_FIXEDBDS_PARAM_H
#घोषणा __IA_CSS_FIXEDBDS_PARAM_H

#समावेश "type_support.h"

/* ISP2401 */
#घोषणा BDS_UNIT 8
#घोषणा FRAC_LOG 3
#घोषणा FRAC_ACC BIT(FRAC_LOG)
#अगर FRAC_ACC != BDS_UNIT
#त्रुटि "FRAC_ACC and BDS_UNIT need to be merged into one define"
#पूर्ण_अगर

काष्ठा sh_css_isp_bds_params अणु
	पूर्णांक baf_strength;
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_FIXEDBDS_PARAM_H */
