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

#अगर_अघोषित __IA_CSS_AA2_TYPES_H
#घोषणा __IA_CSS_AA2_TYPES_H

/* @file
* CSS-API header file क्रम Anti-Aliasing parameters.
*/

/* Anti-Aliasing configuration.
 *
 *  This काष्ठाure is used both क्रम YUV AA and Bayer AA.
 *
 *  1. YUV Anti-Aliasing
 *     काष्ठा ia_css_aa_config   *aa_config
 *
 *     ISP block: AA2
 *    (ISP1: AA2 is not used.)
 *     ISP2: AA2 should be used. But, AA2 is not used currently.
 *
 *  2. Bayer Anti-Aliasing
 *     काष्ठा ia_css_aa_config   *baa_config
 *
 *     ISP block: BAA2
 *     ISP1: BAA2 is used.
 *     ISP2: BAA2 is used.
 */
काष्ठा ia_css_aa_config अणु
	u16 strength;	/** Strength of the filter.
					u0.13, [0,8191],
					शेष/ineffective 0 */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_AA2_TYPES_H */
