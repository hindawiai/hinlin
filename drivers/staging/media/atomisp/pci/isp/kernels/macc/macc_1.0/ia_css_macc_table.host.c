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

#समावेश "system_global.h"
#समावेश "ia_css_types.h"
#समावेश "ia_css_macc_table.host.h"

/* Multi-Axes Color Correction table क्रम ISP1.
 *	64values = 2x2matrix क्रम 16area, [s2.13]
 *	ineffective: 16 of "identity 2x2 matix" अणु8192,0,0,8192पूर्ण
 */
स्थिर काष्ठा ia_css_macc_table शेष_macc_table = अणु
	अणु
		8192, 0, 0, 8192, 8192, 0, 0, 8192,
		8192, 0, 0, 8192, 8192, 0, 0, 8192,
		8192, 0, 0, 8192, 8192, 0, 0, 8192,
		8192, 0, 0, 8192, 8192, 0, 0, 8192,
		8192, 0, 0, 8192, 8192, 0, 0, 8192,
		8192, 0, 0, 8192, 8192, 0, 0, 8192,
		8192, 0, 0, 8192, 8192, 0, 0, 8192,
		8192, 0, 0, 8192, 8192, 0, 0, 8192
	पूर्ण
पूर्ण;

/* Multi-Axes Color Correction table क्रम ISP2.
 *	64values = 2x2matrix क्रम 16area, [s1.12]
 *	ineffective: 16 of "identity 2x2 matix" अणु4096,0,0,4096पूर्ण
 */
स्थिर काष्ठा ia_css_macc_table शेष_macc2_table = अणु
	अणु
		4096, 0, 0, 4096, 4096, 0, 0, 4096,
		4096, 0, 0, 4096, 4096, 0, 0, 4096,
		4096, 0, 0, 4096, 4096, 0, 0, 4096,
		4096, 0, 0, 4096, 4096, 0, 0, 4096,
		4096, 0, 0, 4096, 4096, 0, 0, 4096,
		4096, 0, 0, 4096, 4096, 0, 0, 4096,
		4096, 0, 0, 4096, 4096, 0, 0, 4096,
		4096, 0, 0, 4096, 4096, 0, 0, 4096
	पूर्ण
पूर्ण;
