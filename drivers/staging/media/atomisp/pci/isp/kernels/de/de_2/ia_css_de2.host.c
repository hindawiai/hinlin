<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
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

#समावेश "ia_css_types.h"
#समावेश "sh_css_defs.h"
#समावेश "ia_css_debug.h"

#समावेश "ia_css_de2.host.h"

स्थिर काष्ठा ia_css_ecd_config शेष_ecd_config = अणु
	(1 << (ISP_VEC_ELEMBITS - 1)) * 2 / 3,	/* 2/3 */
	(1 << (ISP_VEC_ELEMBITS - 1)) - 1,	/* 1.0 */
	0,					/* 0.0 */
पूर्ण;

व्योम
ia_css_ecd_encode(
    काष्ठा sh_css_isp_ecd_params *to,
    स्थिर काष्ठा ia_css_ecd_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	to->zip_strength = from->zip_strength;
	to->fc_strength  = from->fc_strength;
	to->fc_debias    = from->fc_debias;
पूर्ण

व्योम
ia_css_ecd_dump(
    स्थिर काष्ठा sh_css_isp_ecd_params *ecd,
    अचिन्हित पूर्णांक level);

व्योम
ia_css_ecd_debug_dtrace(
    स्थिर काष्ठा ia_css_ecd_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.zip_strength=%d, config.fc_strength=%d, config.fc_debias=%d\n",
			    config->zip_strength,
			    config->fc_strength, config->fc_debias);
पूर्ण
