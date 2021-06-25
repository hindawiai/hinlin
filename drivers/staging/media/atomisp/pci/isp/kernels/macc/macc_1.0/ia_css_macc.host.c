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
#समावेश "sh_css_frac.h"

#समावेश "ia_css_macc.host.h"

स्थिर काष्ठा ia_css_macc_config शेष_macc_config = अणु
	1,
पूर्ण;

व्योम
ia_css_macc_encode(
    काष्ठा sh_css_isp_macc_params *to,
    स्थिर काष्ठा ia_css_macc_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	to->exp = from->exp;
पूर्ण

व्योम
ia_css_macc_dump(
    स्थिर काष्ठा sh_css_isp_macc_params *macc,
    अचिन्हित पूर्णांक level);

व्योम
ia_css_macc_debug_dtrace(
    स्थिर काष्ठा ia_css_macc_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.exp=%d\n",
			    config->exp);
पूर्ण
