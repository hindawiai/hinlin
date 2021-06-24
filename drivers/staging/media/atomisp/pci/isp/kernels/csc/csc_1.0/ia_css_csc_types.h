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

#अगर_अघोषित __IA_CSS_CSC_TYPES_H
#घोषणा __IA_CSS_CSC_TYPES_H

/* @file
* CSS-API header file क्रम Color Space Conversion parameters.
*/

/* Color Correction configuration.
 *
 *  This काष्ठाure is used क्रम 3 हालs.
 *  ("YCgCo" is the output क्रमmat of Demosaic.)
 *
 *  1. Color Space Conversion (YCgCo to YUV) क्रम ISP1.
 *     ISP block: CSC1 (Color Space Conversion)
 *     काष्ठा ia_css_cc_config   *cc_config
 *
 *  2. Color Correction Matrix (YCgCo to RGB) क्रम ISP2.
 *     ISP block: CCM2 (Color Correction Matrix)
 *     काष्ठा ia_css_cc_config   *yuv2rgb_cc_config
 *
 *  3. Color Space Conversion (RGB to YUV) क्रम ISP2.
 *     ISP block: CSC2 (Color Space Conversion)
 *     काष्ठा ia_css_cc_config   *rgb2yuv_cc_config
 *
 *  शेष/ineffective:
 *  1. YCgCo -> YUV
 *	1	0.174		0.185
 *	0	-0.66252	-0.66874
 *	0	-0.83738	0.58131
 *
 *	fraction_bits = 12
 *	4096	713	758
 *	0	-2714	-2739
 *	0	-3430	2381
 *
 *  2. YCgCo -> RGB
 *	1	-1	1
 *	1	1	0
 *	1	-1	-1
 *
 *	fraction_bits = 12
 *	4096	-4096	4096
 *	4096	4096	0
 *	4096	-4096	-4096
 *
 *  3. RGB -> YUV
 *	0.299	   0.587	0.114
 *	-0.16874   -0.33126	0.5
 *	0.5	   -0.41869	-0.08131
 *
 *	fraction_bits = 13
 *	2449	4809	934
 *	-1382	-2714	4096
 *	4096	-3430	-666
 */
काष्ठा ia_css_cc_config अणु
	u32 fraction_bits;/** Fractional bits of matrix.
					u8.0, [0,13] */
	s32 matrix[3 * 3]; /** Conversion matrix.
					s[13-fraction_bits].[fraction_bits],
					[-8192,8191] */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_CSC_TYPES_H */
