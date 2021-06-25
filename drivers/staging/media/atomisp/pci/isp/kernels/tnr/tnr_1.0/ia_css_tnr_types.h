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

#अगर_अघोषित __IA_CSS_TNR_TYPES_H
#घोषणा __IA_CSS_TNR_TYPES_H

/* @file
* CSS-API header file क्रम Temporal Noise Reduction (TNR) parameters.
*/

/* Temporal Noise Reduction (TNR) configuration.
 *
 *  When dअगरference between current frame and previous frame is less than or
 *  equal to threshold, TNR works and current frame is mixed
 *  with previous frame.
 *  When dअगरference between current frame and previous frame is greater
 *  than threshold, we judge motion is detected. Then, TNR करोes not work and
 *  current frame is outputted as it is.
 *  Thereक्रमe, when threshold_y and threshold_uv are set as 0, TNR can be disabled.
 *
 *  ISP block: TNR1
 *  ISP1: TNR1 is used.
 *  ISP2: TNR1 is used.
 */

काष्ठा ia_css_tnr_config अणु
	ia_css_u0_16 gain; /** Interpolation ratio of current frame
				and previous frame.
				gain=0.0 -> previous frame is outputted.
				gain=1.0 -> current frame is outputted.
				u0.16, [0,65535],
			शेष 32768(0.5), ineffective 65535(almost 1.0) */
	ia_css_u0_16 threshold_y; /** Threshold to enable पूर्णांकerpolation of Y.
				If dअगरference between current frame and
				previous frame is greater than threshold_y,
				TNR क्रम Y is disabled.
				u0.16, [0,65535], शेष/ineffective 0 */
	ia_css_u0_16 threshold_uv; /** Threshold to enable पूर्णांकerpolation of
				U/V.
				If dअगरference between current frame and
				previous frame is greater than threshold_uv,
				TNR क्रम UV is disabled.
				u0.16, [0,65535], शेष/ineffective 0 */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_TNR_TYPES_H */
