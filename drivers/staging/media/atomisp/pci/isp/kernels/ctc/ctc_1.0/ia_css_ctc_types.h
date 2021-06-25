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

#अगर_अघोषित __IA_CSS_CTC_TYPES_H
#घोषणा __IA_CSS_CTC_TYPES_H

#समावेश <linux/bitops.h>

/* @file
* CSS-API header file क्रम Chroma Tone Control parameters.
*/

/* Fractional bits क्रम CTC gain (used only क्रम ISP1).
 *
 *  IA_CSS_CTC_COEF_SHIFT(=13) includes not only the fractional bits
 *  of gain(=8), but also the bits(=5) to convert chroma
 *  from 13bit precision to 8bit precision.
 *
 *    Gain (काष्ठा ia_css_ctc_table) : u5.8
 *    Input(Chorma) : s0.12 (13bit precision)
 *    Output(Chorma): s0.7  (8bit precision)
 *    Output = (Input * Gain) >> IA_CSS_CTC_COEF_SHIFT
 */
#घोषणा IA_CSS_CTC_COEF_SHIFT          13

/* Number of elements in the CTC table. */
#घोषणा IA_CSS_VAMEM_1_CTC_TABLE_SIZE_LOG2      10
/* Number of elements in the CTC table. */
#घोषणा IA_CSS_VAMEM_1_CTC_TABLE_SIZE           BIT(IA_CSS_VAMEM_1_CTC_TABLE_SIZE_LOG2)

/* Number of elements in the CTC table. */
#घोषणा IA_CSS_VAMEM_2_CTC_TABLE_SIZE_LOG2      8
/* Number of elements in the CTC table. */
#घोषणा IA_CSS_VAMEM_2_CTC_TABLE_SIZE           ((1U << IA_CSS_VAMEM_2_CTC_TABLE_SIZE_LOG2) + 1)

क्रमागत ia_css_vamem_type अणु
	IA_CSS_VAMEM_TYPE_1,
	IA_CSS_VAMEM_TYPE_2
पूर्ण;

/* Chroma Tone Control configuration.
 *
 *  ISP block: CTC2 (CTC by polygonal line approximation)
 * (ISP1: CTC1 (CTC by look-up table) is used.)
 *  ISP2: CTC2 is used.
 */
काष्ठा ia_css_ctc_config अणु
	u16 y0;	/** 1st kneepoपूर्णांक gain.
				u[ce_gain_exp].[13-ce_gain_exp], [0,8191],
				शेष/ineffective 4096(0.5) */
	u16 y1;	/** 2nd kneepoपूर्णांक gain.
				u[ce_gain_exp].[13-ce_gain_exp], [0,8191],
				शेष/ineffective 4096(0.5) */
	u16 y2;	/** 3rd kneepoपूर्णांक gain.
				u[ce_gain_exp].[13-ce_gain_exp], [0,8191],
				शेष/ineffective 4096(0.5) */
	u16 y3;	/** 4th kneepoपूर्णांक gain.
				u[ce_gain_exp].[13-ce_gain_exp], [0,8191],
				शेष/ineffective 4096(0.5) */
	u16 y4;	/** 5th kneepoपूर्णांक gain.
				u[ce_gain_exp].[13-ce_gain_exp], [0,8191],
				शेष/ineffective 4096(0.5) */
	u16 y5;	/** 6th kneepoपूर्णांक gain.
				u[ce_gain_exp].[13-ce_gain_exp], [0,8191],
				शेष/ineffective 4096(0.5) */
	u16 ce_gain_exp;	/** Common exponent of y-axis gain.
				u8.0, [0,13],
				शेष/ineffective 1 */
	u16 x1;	/** 2nd kneepoपूर्णांक luma.
				u0.13, [0,8191], स्थिरraपूर्णांकs: 0<x1<x2,
				शेष/ineffective 1024 */
	u16 x2;	/** 3rd kneepoपूर्णांक luma.
				u0.13, [0,8191], स्थिरraपूर्णांकs: x1<x2<x3,
				शेष/ineffective 2048 */
	u16 x3;	/** 4th kneepoपूर्णांक luma.
				u0.13, [0,8191], स्थिरraपूर्णांकs: x2<x3<x4,
				शेष/ineffective 6144 */
	u16 x4;	/** 5tn kneepoपूर्णांक luma.
				u0.13, [0,8191], स्थिरraपूर्णांकs: x3<x4<8191,
				शेष/ineffective 7168 */
पूर्ण;

जोड़ ia_css_ctc_data अणु
	u16 vamem_1[IA_CSS_VAMEM_1_CTC_TABLE_SIZE];
	u16 vamem_2[IA_CSS_VAMEM_2_CTC_TABLE_SIZE];
पूर्ण;

/* CTC table, used क्रम Chroma Tone Control.
 *
 *  ISP block: CTC1 (CTC by look-up table)
 *  ISP1: CTC1 is used.
 * (ISP2: CTC2 (CTC by polygonal line approximation) is used.)
 */
काष्ठा ia_css_ctc_table अणु
	क्रमागत ia_css_vamem_type vamem_type;
	जोड़ ia_css_ctc_data data;
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_CTC_TYPES_H */
