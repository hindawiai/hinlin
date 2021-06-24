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

#अगर_अघोषित __IA_CSS_OB2_TYPES_H
#घोषणा __IA_CSS_OB2_TYPES_H

/* @file
* CSS-API header file क्रम Optical Black algorithm parameters.
*/

/* Optical Black configuration
 *
 * ISP2.6.1: OB2 is used.
 */

#समावेश "ia_css_frac.h"

काष्ठा ia_css_ob2_config अणु
	ia_css_u0_16 level_gr;    /** Black level क्रम GR pixels.
					u0.16, [0,65535],
					शेष/ineffective 0 */
	ia_css_u0_16  level_r;     /** Black level क्रम R pixels.
					u0.16, [0,65535],
					शेष/ineffective 0 */
	ia_css_u0_16  level_b;     /** Black level क्रम B pixels.
					u0.16, [0,65535],
					शेष/ineffective 0 */
	ia_css_u0_16  level_gb;    /** Black level क्रम GB pixels.
					u0.16, [0,65535],
					शेष/ineffective 0 */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_OB2_TYPES_H */
