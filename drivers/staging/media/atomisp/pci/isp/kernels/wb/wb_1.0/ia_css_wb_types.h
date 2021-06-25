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

#अगर_अघोषित __IA_CSS_WB_TYPES_H
#घोषणा __IA_CSS_WB_TYPES_H

/* @file
* CSS-API header file क्रम White Balance parameters.
*/

/* White Balance configuration (Gain Adjust).
 *
 *  ISP block: WB1
 *  ISP1: WB1 is used.
 *  ISP2: WB1 is used.
 */
काष्ठा ia_css_wb_config अणु
	u32 पूर्णांकeger_bits; /** Common exponent of gains.
				u8.0, [0,3],
				शेष 1, ineffective 1 */
	u32 gr;	/** Signअगरicand of Gr gain.
				u[पूर्णांकeger_bits].[16-पूर्णांकeger_bits], [0,65535],
				शेष/ineffective 32768(u1.15, 1.0) */
	u32 r;	/** Signअगरicand of R gain.
				u[पूर्णांकeger_bits].[16-पूर्णांकeger_bits], [0,65535],
				शेष/ineffective 32768(u1.15, 1.0) */
	u32 b;	/** Signअगरicand of B gain.
				u[पूर्णांकeger_bits].[16-पूर्णांकeger_bits], [0,65535],
				शेष/ineffective 32768(u1.15, 1.0) */
	u32 gb;	/** Signअगरicand of Gb gain.
				u[पूर्णांकeger_bits].[16-पूर्णांकeger_bits], [0,65535],
				शेष/ineffective 32768(u1.15, 1.0) */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_WB_TYPES_H */
