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

#अगर_अघोषित __IA_CSS_YNR_TYPES_H
#घोषणा __IA_CSS_YNR_TYPES_H

/* @file
* CSS-API header file क्रम Noise Reduction (BNR) and YCC Noise Reduction (YNR,CNR).
*/

/* Configuration used by Bayer Noise Reduction (BNR) and
 *  YCC Noise Reduction (YNR,CNR).
 *
 *  ISP block: BNR1, YNR1, CNR1
 *  ISP1: BNR1,YNR1,CNR1 are used.
 *  ISP2: BNR1,YNR1,CNR1 are used क्रम Preview/Video.
 *        BNR1,YNR2,CNR2 are used क्रम Still.
 */
काष्ठा ia_css_nr_config अणु
	ia_css_u0_16 bnr_gain;	   /** Strength of noise reduction (BNR).
				u0.16, [0,65535],
				शेष 14336(0.21875), ineffective 0 */
	ia_css_u0_16 ynr_gain;	   /** Strength of noise reduction (YNR).
				u0.16, [0,65535],
				शेष 14336(0.21875), ineffective 0 */
	ia_css_u0_16 direction;    /** Sensitivity of edge (BNR).
				u0.16, [0,65535],
				शेष 512(0.0078125), ineffective 0 */
	ia_css_u0_16 threshold_cb; /** Coring threshold क्रम Cb (CNR).
				This is the same as
				de_config.c1_coring_threshold.
				u0.16, [0,65535],
				शेष 0(0), ineffective 0 */
	ia_css_u0_16 threshold_cr; /** Coring threshold क्रम Cr (CNR).
				This is the same as
				de_config.c2_coring_threshold.
				u0.16, [0,65535],
				शेष 0(0), ineffective 0 */
पूर्ण;

/* Edge Enhancement (sharpen) configuration.
 *
 *  ISP block: YEE1
 *  ISP1: YEE1 is used.
 *  ISP2: YEE1 is used क्रम Preview/Video.
 *       (YEE2 is used क्रम Still.)
 */
काष्ठा ia_css_ee_config अणु
	ia_css_u5_11 gain;	  /** The strength of sharpness.
					u5.11, [0,65535],
					शेष 8192(4.0), ineffective 0 */
	ia_css_u8_8 threshold;    /** The threshold that भागides noises from
					edge.
					u8.8, [0,65535],
					शेष 256(1.0), ineffective 65535 */
	ia_css_u5_11 detail_gain; /** The strength of sharpness in pell-mell
					area.
					u5.11, [0,65535],
					शेष 2048(1.0), ineffective 0 */
पूर्ण;

/* YNR and YEE (sharpen) configuration.
 */
काष्ठा ia_css_yee_config अणु
	काष्ठा ia_css_nr_config nr; /** The NR configuration. */
	काष्ठा ia_css_ee_config ee; /** The EE configuration. */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_YNR_TYPES_H */
