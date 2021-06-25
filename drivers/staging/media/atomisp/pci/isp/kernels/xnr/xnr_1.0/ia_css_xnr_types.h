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

#अगर_अघोषित __IA_CSS_XNR_TYPES_H
#घोषणा __IA_CSS_XNR_TYPES_H

/* @file
* CSS-API header file क्रम Extra Noise Reduction (XNR) parameters.
*/

/* XNR table.
 *
 *  NOTE: The driver करोes not need to set this table,
 *        because the शेष values are set inside the css.
 *
 *  This table contains coefficients used क्रम भागision in XNR.
 *
 *	u0.12, [0,4095],
 *      अणु4095, 2048, 1365, .........., 65, 64पूर्ण
 *      (अणु1/1, 1/2, 1/3, ............., 1/63, 1/64पूर्ण)
 *
 *  ISP block: XNR1
 *  ISP1: XNR1 is used.
 *  ISP2: XNR1 is used.
 *
 */

/* Number of elements in the xnr table. */
#घोषणा IA_CSS_VAMEM_1_XNR_TABLE_SIZE_LOG2      6
/* Number of elements in the xnr table. */
#घोषणा IA_CSS_VAMEM_1_XNR_TABLE_SIZE           BIT(IA_CSS_VAMEM_1_XNR_TABLE_SIZE_LOG2)

/* Number of elements in the xnr table. */
#घोषणा IA_CSS_VAMEM_2_XNR_TABLE_SIZE_LOG2      6
/* Number of elements in the xnr table. */
#घोषणा IA_CSS_VAMEM_2_XNR_TABLE_SIZE		BIT(IA_CSS_VAMEM_2_XNR_TABLE_SIZE_LOG2)

/** IA_CSS_VAMEM_TYPE_1(ISP2300) or
     IA_CSS_VAMEM_TYPE_2(ISP2400) */
जोड़ ia_css_xnr_data अणु
	u16 vamem_1[IA_CSS_VAMEM_1_XNR_TABLE_SIZE];
	/** Coefficients table on vamem type1. u0.12, [0,4095] */
	u16 vamem_2[IA_CSS_VAMEM_2_XNR_TABLE_SIZE];
	/** Coefficients table on vamem type2. u0.12, [0,4095] */
पूर्ण;

काष्ठा ia_css_xnr_table अणु
	क्रमागत ia_css_vamem_type vamem_type;
	जोड़ ia_css_xnr_data data;
पूर्ण;

काष्ठा ia_css_xnr_config अणु
	/* XNR threshold.
	 * type:u0.16 valid range:[0,65535]
	 * शेष: 6400 */
	u16 threshold;
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_XNR_TYPES_H */
