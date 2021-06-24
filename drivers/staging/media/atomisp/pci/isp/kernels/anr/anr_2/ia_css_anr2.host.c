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

#समावेश "ia_css_anr2.host.h"

व्योम
ia_css_anr2_vmem_encode(
    काष्ठा ia_css_isp_anr2_params *to,
    स्थिर काष्ठा ia_css_anr_thres *from,
    माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक i;

	(व्योम)size;
	क्रम (i = 0; i < ANR_PARAM_SIZE; i++) अणु
		अचिन्हित पूर्णांक j;

		क्रम (j = 0; j < ISP_VEC_NELEMS; j++) अणु
			to->data[i][j] = from->data[i * ISP_VEC_NELEMS + j];
		पूर्ण
	पूर्ण
पूर्ण

व्योम
ia_css_anr2_debug_dtrace(
    स्थिर काष्ठा ia_css_anr_thres *config,
    अचिन्हित पूर्णांक level)
अणु
	(व्योम)config;
	(व्योम)level;
पूर्ण
