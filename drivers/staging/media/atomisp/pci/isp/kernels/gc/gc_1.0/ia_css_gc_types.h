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

#अगर_अघोषित __IA_CSS_GC_TYPES_H
#घोषणा __IA_CSS_GC_TYPES_H

/* @file
* CSS-API header file क्रम Gamma Correction parameters.
*/

#समावेश "isp/kernels/ctc/ctc_1.0/ia_css_ctc_types.h"  /* FIXME: Needed क्रम ia_css_vamem_type */

/* Fractional bits क्रम GAMMA gain */
#घोषणा IA_CSS_GAMMA_GAIN_K_SHIFT      13

/* Number of elements in the gamma table. */
#घोषणा IA_CSS_VAMEM_1_GAMMA_TABLE_SIZE_LOG2    10
#घोषणा IA_CSS_VAMEM_1_GAMMA_TABLE_SIZE         BIT(IA_CSS_VAMEM_1_GAMMA_TABLE_SIZE_LOG2)

/* Number of elements in the gamma table. */
#घोषणा IA_CSS_VAMEM_2_GAMMA_TABLE_SIZE_LOG2    8
#घोषणा IA_CSS_VAMEM_2_GAMMA_TABLE_SIZE         ((1U << IA_CSS_VAMEM_2_GAMMA_TABLE_SIZE_LOG2) + 1)

/* Gamma table, used क्रम Y(Luma) Gamma Correction.
 *
 *  ISP block: GC1 (YUV Gamma Correction)
 *  ISP1: GC1 is used.
 * (ISP2: GC2(sRGB Gamma Correction) is used.)
 */
/** IA_CSS_VAMEM_TYPE_1(ISP2300) or
     IA_CSS_VAMEM_TYPE_2(ISP2400) */
जोड़ ia_css_gc_data अणु
	u16 vamem_1[IA_CSS_VAMEM_1_GAMMA_TABLE_SIZE];
	/** Y(Luma) Gamma table on vamem type 1. u0.8, [0,255] */
	u16 vamem_2[IA_CSS_VAMEM_2_GAMMA_TABLE_SIZE];
	/** Y(Luma) Gamma table on vamem type 2. u0.8, [0,255] */
पूर्ण;

काष्ठा ia_css_gamma_table अणु
	क्रमागत ia_css_vamem_type vamem_type;
	जोड़ ia_css_gc_data data;
पूर्ण;

/* Gamma Correction configuration (used only क्रम YUV Gamma Correction).
 *
 *  ISP block: GC1 (YUV Gamma Correction)
 *  ISP1: GC1 is used.
 * (ISP2: GC2 (sRGB Gamma Correction) is used.)
  */
काष्ठा ia_css_gc_config अणु
	u16 gain_k1; /** Gain to adjust U after YUV Gamma Correction.
				u0.16, [0,65535],
				शेष/ineffective 19000(0.29) */
	u16 gain_k2; /** Gain to adjust V after YUV Gamma Correction.
				u0.16, [0,65535],
				शेष/ineffective 19000(0.29) */
पूर्ण;

/* Chroma Enhancement configuration.
 *
 *  This parameter specअगरies range of chroma output level.
 *  The standard range is [0,255] or [16,240].
 *
 *  ISP block: CE1
 *  ISP1: CE1 is used.
 * (ISP2: CE1 is not used.)
 */
काष्ठा ia_css_ce_config अणु
	u8 uv_level_min; /** Minimum of chroma output level.
				u0.8, [0,255], शेष/ineffective 0 */
	u8 uv_level_max; /** Maximum of chroma output level.
				u0.8, [0,255], शेष/ineffective 255 */
पूर्ण;

/* Multi-Axes Color Correction (MACC) configuration.
 *
 *  ISP block: MACC2 (MACC by matrix and exponent(ia_css_macc_config))
 * (ISP1: MACC1 (MACC by only matrix) is used.)
 *  ISP2: MACC2 is used.
 */
काष्ठा ia_css_macc_config अणु
	u8 exp;	/** Common exponent of ia_css_macc_table.
				u8.0, [0,13], शेष 1, ineffective 1 */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_GC_TYPES_H */
