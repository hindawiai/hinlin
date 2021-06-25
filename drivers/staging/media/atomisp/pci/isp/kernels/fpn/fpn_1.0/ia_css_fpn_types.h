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

#अगर_अघोषित __IA_CSS_FPN_TYPES_H
#घोषणा __IA_CSS_FPN_TYPES_H

/* @file
* CSS-API header file क्रम Fixed Pattern Noise parameters.
*/

/* Fixed Pattern Noise table.
 *
 *  This contains the fixed patterns noise values
 *  obtained from a black frame capture.
 *
 *  "shift" should be set as the smallest value
 *  which satisfies the requirement the maximum data is less than 64.
 *
 *  ISP block: FPN1
 *  ISP1: FPN1 is used.
 *  ISP2: FPN1 is used.
 */

काष्ठा ia_css_fpn_table अणु
	s16 *data;		/** Table content (fixed patterns noise).
					u0.[13-shअगरt], [0,63] */
	u32 width;		/** Table width (in pixels).
					This is the input frame width. */
	u32 height;	/** Table height (in pixels).
					This is the input frame height. */
	u32 shअगरt;		/** Common exponent of table content.
					u8.0, [0,13] */
	u32 enabled;	/** Fpn is enabled.
					bool */
पूर्ण;

काष्ठा ia_css_fpn_configuration अणु
	स्थिर काष्ठा ia_css_frame_info *info;
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_FPN_TYPES_H */
