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

#अगर_अघोषित __IA_CSS_DVS_PARAM_H
#घोषणा __IA_CSS_DVS_PARAM_H

#समावेश <type_support.h>

#अगर !defined(ENABLE_TPROXY) && !defined(ENABLE_CRUN_FOR_TD) && !defined(PARAMBIN_GENERATION)
#समावेश "dma.h"
#पूर्ण_अगर /* !defined(ENABLE_TPROXY) && !defined(ENABLE_CRUN_FOR_TD) */

#समावेश "uds/uds_1.0/ia_css_uds_param.h"

/* dvserence frame */
काष्ठा sh_css_isp_dvs_isp_config अणु
	u32 num_horizontal_blocks;
	u32 num_vertical_blocks;
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_DVS_PARAM_H */
