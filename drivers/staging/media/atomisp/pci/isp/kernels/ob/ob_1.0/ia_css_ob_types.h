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

#अगर_अघोषित __IA_CSS_OB_TYPES_H
#घोषणा __IA_CSS_OB_TYPES_H

/* @file
* CSS-API header file क्रम Optical Black level parameters.
*/

#समावेश "ia_css_frac.h"

/* Optical black mode.
 */
क्रमागत ia_css_ob_mode अणु
	IA_CSS_OB_MODE_NONE,	/** OB has no effect. */
	IA_CSS_OB_MODE_FIXED,	/** Fixed OB */
	IA_CSS_OB_MODE_RASTER	/** Raster OB */
पूर्ण;

/* Optical Black level configuration.
 *
 *  ISP block: OB1
 *  ISP1: OB1 is used.
 *  ISP2: OB1 is used.
 */
काष्ठा ia_css_ob_config अणु
	क्रमागत ia_css_ob_mode mode; /** Mode (None / Fixed / Raster).
					क्रमागत, [0,2],
					शेष 1, ineffective 0 */
	ia_css_u0_16 level_gr;    /** Black level क्रम GR pixels
					(used क्रम Fixed Mode only).
					u0.16, [0,65535],
					शेष/ineffective 0 */
	ia_css_u0_16 level_r;     /** Black level क्रम R pixels
					(used क्रम Fixed Mode only).
					u0.16, [0,65535],
					शेष/ineffective 0 */
	ia_css_u0_16 level_b;     /** Black level क्रम B pixels
					(used क्रम Fixed Mode only).
					u0.16, [0,65535],
					शेष/ineffective 0 */
	ia_css_u0_16 level_gb;    /** Black level क्रम GB pixels
					(used क्रम Fixed Mode only).
					u0.16, [0,65535],
					शेष/ineffective 0 */
	u16 start_position; /** Start position of OB area
					(used क्रम Raster Mode only).
					u16.0, [0,63],
					शेष/ineffective 0 */
	u16 end_position;  /** End position of OB area
					(used क्रम Raster Mode only).
					u16.0, [0,63],
					शेष/ineffective 0 */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_OB_TYPES_H */
