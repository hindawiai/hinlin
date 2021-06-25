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

#अगर_अघोषित __IA_CSS_CNR2_TYPES_H
#घोषणा __IA_CSS_CNR2_TYPES_H

/* @file
* CSS-API header file क्रम Chroma Noise Reduction (CNR) parameters
*/

/* Chroma Noise Reduction configuration.
 *
 *  Small sensitivity of edge means strong smoothness and NR perक्रमmance.
 *  If you see blurred color on vertical edges,
 *  set higher values on sense_gain_h*.
 *  If you see blurred color on horizontal edges,
 *  set higher values on sense_gain_v*.
 *
 *  ISP block: CNR2
 * (ISP1: CNR1 is used.)
 * (ISP2: CNR1 is used क्रम Preview/Video.)
 *  ISP2: CNR2 is used क्रम Still.
 */
काष्ठा ia_css_cnr_config अणु
	u16 coring_u;	/** Coring level of U.
				u0.13, [0,8191], शेष/ineffective 0 */
	u16 coring_v;	/** Coring level of V.
				u0.13, [0,8191], शेष/ineffective 0 */
	u16 sense_gain_vy;	/** Sensitivity of horizontal edge of Y.
				u13.0, [0,8191], शेष 100, ineffective 8191 */
	u16 sense_gain_vu;	/** Sensitivity of horizontal edge of U.
				u13.0, [0,8191], शेष 100, ineffective 8191 */
	u16 sense_gain_vv;	/** Sensitivity of horizontal edge of V.
				u13.0, [0,8191], शेष 100, ineffective 8191 */
	u16 sense_gain_hy;	/** Sensitivity of vertical edge of Y.
				u13.0, [0,8191], शेष 50, ineffective 8191 */
	u16 sense_gain_hu;	/** Sensitivity of vertical edge of U.
				u13.0, [0,8191], शेष 50, ineffective 8191 */
	u16 sense_gain_hv;	/** Sensitivity of vertical edge of V.
				u13.0, [0,8191], शेष 50, ineffective 8191 */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_CNR2_TYPES_H */
