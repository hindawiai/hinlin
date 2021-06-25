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

#अगर_अघोषित __IA_CSS_DE2_TYPES_H
#घोषणा __IA_CSS_DE2_TYPES_H

/* @file
* CSS-API header file क्रम Demosaicing parameters.
*/

/* Eigen Color Demosaicing configuration.
 *
 *  ISP block: DE2
 * (ISP1: DE1 is used.)
 *  ISP2: DE2 is used.
 */
काष्ठा ia_css_ecd_config अणु
	u16 zip_strength;	/** Strength of zipper reduction.
				u0.13, [0,8191],
				शेष 5489(0.67), ineffective 0 */
	u16 fc_strength;	/** Strength of false color reduction.
				u0.13, [0,8191],
				शेष 8191(almost 1.0), ineffective 0 */
	u16 fc_debias;	/** Prevent color change
				     on noise or Gr/Gb imbalance.
				u0.13, [0,8191],
				शेष 0, ineffective 0 */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_DE2_TYPES_H */
