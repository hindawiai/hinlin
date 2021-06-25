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

#अगर_अघोषित __IA_CSS_YNR2_TYPES_H
#घोषणा __IA_CSS_YNR2_TYPES_H

/* @file
* CSS-API header file क्रम Y(Luma) Noise Reduction.
*/

/* Y(Luma) Noise Reduction configuration.
 *
 *  ISP block: YNR2 & YEE2
 * (ISP1: YNR1 and YEE1 are used.)
 * (ISP2: YNR1 and YEE1 are used क्रम Preview/Video.)
 *  ISP2: YNR2 and YEE2 are used क्रम Still.
 */
काष्ठा ia_css_ynr_config अणु
	u16 edge_sense_gain_0;   /** Sensitivity of edge in dark area.
					u13.0, [0,8191],
					शेष 1000, ineffective 0 */
	u16 edge_sense_gain_1;   /** Sensitivity of edge in bright area.
					u13.0, [0,8191],
					शेष 1000, ineffective 0 */
	u16 corner_sense_gain_0; /** Sensitivity of corner in dark area.
					u13.0, [0,8191],
					शेष 1000, ineffective 0 */
	u16 corner_sense_gain_1; /** Sensitivity of corner in bright area.
					u13.0, [0,8191],
					शेष 1000, ineffective 0 */
पूर्ण;

/* Fringe Control configuration.
 *
 *  ISP block: FC2 (FC2 is used with YNR2/YEE2.)
 * (ISP1: FC2 is not used.)
 * (ISP2: FC2 is not क्रम Preview/Video.)
 *  ISP2: FC2 is used क्रम Still.
 */
काष्ठा ia_css_fc_config अणु
	u8  gain_exp;   /** Common exponent of gains.
				u8.0, [0,13],
				शेष 1, ineffective 0 */
	u16 coring_pos_0; /** Coring threshold क्रम positive edge in dark area.
				u0.13, [0,8191],
				शेष 0(0), ineffective 0 */
	u16 coring_pos_1; /** Coring threshold क्रम positive edge in bright area.
				u0.13, [0,8191],
				शेष 0(0), ineffective 0 */
	u16 coring_neg_0; /** Coring threshold क्रम negative edge in dark area.
				u0.13, [0,8191],
				शेष 0(0), ineffective 0 */
	u16 coring_neg_1; /** Coring threshold क्रम negative edge in bright area.
				u0.13, [0,8191],
				शेष 0(0), ineffective 0 */
	u16 gain_pos_0; /** Gain क्रम positive edge in dark area.
				u0.13, [0,8191],
				शेष 4096(0.5), ineffective 0 */
	u16 gain_pos_1; /** Gain क्रम positive edge in bright area.
				u0.13, [0,8191],
				शेष 4096(0.5), ineffective 0 */
	u16 gain_neg_0; /** Gain क्रम negative edge in dark area.
				u0.13, [0,8191],
				शेष 4096(0.5), ineffective 0 */
	u16 gain_neg_1; /** Gain क्रम negative edge in bright area.
				u0.13, [0,8191],
				शेष 4096(0.5), ineffective 0 */
	u16 crop_pos_0; /** Limit क्रम positive edge in dark area.
				u0.13, [0,8191],
				शेष/ineffective 8191(almost 1.0) */
	u16 crop_pos_1; /** Limit क्रम positive edge in bright area.
				u0.13, [0,8191],
				शेष/ineffective 8191(almost 1.0) */
	s16  crop_neg_0; /** Limit क्रम negative edge in dark area.
				s0.13, [-8192,0],
				शेष/ineffective -8192(-1.0) */
	s16  crop_neg_1; /** Limit क्रम negative edge in bright area.
				s0.13, [-8192,0],
				शेष/ineffective -8192(-1.0) */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_YNR2_TYPES_H */
