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

#अगर_अघोषित __IA_CSS_SDIS_TYPES_H
#घोषणा __IA_CSS_SDIS_TYPES_H

/* @file
* CSS-API header file क्रम DVS statistics parameters.
*/

/* Number of DVS coefficient types */
#घोषणा IA_CSS_DVS_NUM_COEF_TYPES      6

#अगर_अघोषित PIPE_GENERATION
#समावेश "isp/kernels/sdis/common/ia_css_sdis_common_types.h"
#पूर्ण_अगर

/* DVS 1.0 Coefficients.
 *  This काष्ठाure describes the coefficients that are needed क्रम the dvs statistics.
 */

काष्ठा ia_css_dvs_coefficients अणु
	काष्ठा ia_css_dvs_grid_info
		grid;/** grid info contains the dimensions of the dvs grid */
	s16 *hor_coefs;	/** the poपूर्णांकer to पूर्णांक16_t[grid.num_hor_coefs * IA_CSS_DVS_NUM_COEF_TYPES]
				     containing the horizontal coefficients */
	s16 *ver_coefs;	/** the poपूर्णांकer to पूर्णांक16_t[grid.num_ver_coefs * IA_CSS_DVS_NUM_COEF_TYPES]
				     containing the vertical coefficients */
पूर्ण;

/* DVS 1.0 Statistics.
 *  This काष्ठाure describes the statistics that are generated using the provided coefficients.
 */

काष्ठा ia_css_dvs_statistics अणु
	काष्ठा ia_css_dvs_grid_info
		grid;/** grid info contains the dimensions of the dvs grid */
	s32 *hor_proj;	/** the poपूर्णांकer to पूर्णांक16_t[grid.height * IA_CSS_DVS_NUM_COEF_TYPES]
				     containing the horizontal projections */
	s32 *ver_proj;	/** the poपूर्णांकer to पूर्णांक16_t[grid.width * IA_CSS_DVS_NUM_COEF_TYPES]
				     containing the vertical projections */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_SDIS_TYPES_H */
