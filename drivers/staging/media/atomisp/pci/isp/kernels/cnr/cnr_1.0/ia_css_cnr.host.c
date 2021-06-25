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

#समावेश "ia_css_cnr.host.h"

/* keep the पूर्णांकerface here, it is not enabled yet because host करोesn't know the size of inभागidual state */
व्योम
ia_css_init_cnr_state(
    व्योम/*काष्ठा sh_css_isp_cnr_vmem_state*/ * state,
    माप_प्रकार size)
अणु
	स_रखो(state, 0, size);
पूर्ण
