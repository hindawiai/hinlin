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

#अगर_अघोषित IA_CSS_NO_DEBUG
/* FIXME: See BZ 4427 */
#समावेश "ia_css_debug.h"
#पूर्ण_अगर

#समावेश "ia_css_macc1_5.host.h"

स्थिर काष्ठा ia_css_macc1_5_config शेष_macc1_5_config = अणु
	1
पूर्ण;

व्योम
ia_css_macc1_5_encode(
    काष्ठा sh_css_isp_macc1_5_params *to,
    स्थिर काष्ठा ia_css_macc1_5_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	to->exp = from->exp;
पूर्ण

व्योम
ia_css_macc1_5_vmem_encode(
    काष्ठा sh_css_isp_macc1_5_vmem_params *params,
    स्थिर काष्ठा ia_css_macc1_5_table *from,
    अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i, j, k, idx;
	अचिन्हित पूर्णांक idx_map[] = अणु
		0, 1, 3, 2, 6, 7, 5, 4, 12, 13, 15, 14, 10, 11, 9, 8
	पूर्ण;

	(व्योम)size;

	क्रम (k = 0; k < 4; k++)
		क्रम (i = 0; i < IA_CSS_MACC_NUM_AXES; i++) अणु
			idx = idx_map[i] + (k * IA_CSS_MACC_NUM_AXES);
			j   = 4 * i;

			params->data[0][(idx)] = from->data[j];
			params->data[1][(idx)] = from->data[j + 1];
			params->data[2][(idx)] = from->data[j + 2];
			params->data[3][(idx)] = from->data[j + 3];
		पूर्ण
पूर्ण

#अगर_अघोषित IA_CSS_NO_DEBUG
व्योम
ia_css_macc1_5_debug_dtrace(
    स्थिर काष्ठा ia_css_macc1_5_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.exp=%d\n",
			    config->exp);
पूर्ण
#पूर्ण_अगर
