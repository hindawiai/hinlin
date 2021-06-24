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

#अगर_अघोषित __IA_CSS_DP_TYPES_H
#घोषणा __IA_CSS_DP_TYPES_H

/* @file
* CSS-API header file क्रम Defect Pixel Correction (DPC) parameters.
*/

/* Defect Pixel Correction configuration.
 *
 *  ISP block: DPC1 (DPC after WB)
 *             DPC2 (DPC beक्रमe WB)
 *  ISP1: DPC1 is used.
 *  ISP2: DPC2 is used.
 */
काष्ठा ia_css_dp_config अणु
	ia_css_u0_16 threshold; /** The threshold of defect pixel correction,
			      representing the permissible dअगरference of
			      पूर्णांकensity between one pixel and its
			      surrounding pixels. Smaller values result
				in more frequent pixel corrections.
				u0.16, [0,65535],
				शेष 8192, ineffective 65535 */
	ia_css_u8_8 gain;	 /** The sensitivity of mis-correction. ISP will
			      miss a lot of defects अगर the value is set
				too large.
				u8.8, [0,65535],
				शेष 4096, ineffective 65535 */
	u32 gr;	/* अचिन्हित <पूर्णांकeger_bits>.<16-पूर्णांकeger_bits> */
	u32 r;	/* अचिन्हित <पूर्णांकeger_bits>.<16-पूर्णांकeger_bits> */
	u32 b;	/* अचिन्हित <पूर्णांकeger_bits>.<16-पूर्णांकeger_bits> */
	u32 gb;	/* अचिन्हित <पूर्णांकeger_bits>.<16-पूर्णांकeger_bits> */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_DP_TYPES_H */
