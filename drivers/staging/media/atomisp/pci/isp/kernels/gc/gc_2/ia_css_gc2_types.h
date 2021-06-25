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

#अगर_अघोषित __IA_CSS_GC2_TYPES_H
#घोषणा __IA_CSS_GC2_TYPES_H

#समावेश "isp/kernels/ctc/ctc_1.0/ia_css_ctc_types.h"  /* FIXME: needed क्रम ia_css_vamem_type */

/* @file
* CSS-API header file क्रम Gamma Correction parameters.
*/

/* sRGB Gamma table, used क्रम sRGB Gamma Correction.
 *
 *  ISP block: GC2 (sRGB Gamma Correction)
 * (ISP1: GC1(YUV Gamma Correction) is used.)
 *  ISP2: GC2 is used.
 */

/* Number of elements in the sRGB gamma table. */
#घोषणा IA_CSS_VAMEM_1_RGB_GAMMA_TABLE_SIZE_LOG2 8
#घोषणा IA_CSS_VAMEM_1_RGB_GAMMA_TABLE_SIZE      BIT(IA_CSS_VAMEM_1_RGB_GAMMA_TABLE_SIZE_LOG2)

/* Number of elements in the sRGB gamma table. */
#घोषणा IA_CSS_VAMEM_2_RGB_GAMMA_TABLE_SIZE_LOG2    8
#घोषणा IA_CSS_VAMEM_2_RGB_GAMMA_TABLE_SIZE     ((1U << IA_CSS_VAMEM_2_RGB_GAMMA_TABLE_SIZE_LOG2) + 1)

/** IA_CSS_VAMEM_TYPE_1(ISP2300) or
     IA_CSS_VAMEM_TYPE_2(ISP2400) */
जोड़ ia_css_rgb_gamma_data अणु
	u16 vamem_1[IA_CSS_VAMEM_1_RGB_GAMMA_TABLE_SIZE];
	/** RGB Gamma table on vamem type1. This table is not used,
		because sRGB Gamma Correction is not implemented क्रम ISP2300. */
	u16 vamem_2[IA_CSS_VAMEM_2_RGB_GAMMA_TABLE_SIZE];
	/** RGB Gamma table on vamem type2. u0.12, [0,4095] */
पूर्ण;

काष्ठा ia_css_rgb_gamma_table अणु
	क्रमागत ia_css_vamem_type vamem_type;
	जोड़ ia_css_rgb_gamma_data data;
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_GC2_TYPES_H */
