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

#अगर_अघोषित __IA_CSS_DPC2_TYPES_H
#घोषणा __IA_CSS_DPC2_TYPES_H

/* @file
* CSS-API header file क्रम Defect Pixel Correction 2 (DPC2) parameters.
*/

#समावेश "type_support.h"

/**@अणु*/
/* Floating poपूर्णांक स्थिरants क्रम dअगरferent metrics. */
#घोषणा METRIC1_ONE_FP	BIT(12)
#घोषणा METRIC2_ONE_FP	BIT(5)
#घोषणा METRIC3_ONE_FP	BIT(12)
#घोषणा WBGAIN_ONE_FP	BIT(9)
/**@पूर्ण*/

/**@अणु*/
/* Defect Pixel Correction 2 configuration.
 *
 * \मrief DPC2 खुला parameters.
 * \details Struct with all parameters क्रम the Defect Pixel Correction 2
 * kernel that can be set from the CSS API.
 *
 * ISP block: DPC1 (DPC after WB)
 *            DPC2 (DPC beक्रमe WB)
 * ISP1: DPC1 is used.
 * ISP2: DPC2 is used.
 *
 */
काष्ठा ia_css_dpc2_config अणु
	/**@अणु*/
	s32 metric1;
	s32 metric2;
	s32 metric3;
	s32 wb_gain_gr;
	s32 wb_gain_r;
	s32 wb_gain_b;
	s32 wb_gain_gb;
	/**@पूर्ण*/
पूर्ण;

/**@पूर्ण*/

#पूर्ण_अगर /* __IA_CSS_DPC2_TYPES_H */
