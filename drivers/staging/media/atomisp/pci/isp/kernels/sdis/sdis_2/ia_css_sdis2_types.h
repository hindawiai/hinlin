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

#अगर_अघोषित __IA_CSS_SDIS2_TYPES_H
#घोषणा __IA_CSS_SDIS2_TYPES_H

/* @file
* CSS-API header file क्रम DVS statistics parameters.
*/

/* Number of DVS coefficient types */
#घोषणा IA_CSS_DVS2_NUM_COEF_TYPES     4

#अगर_अघोषित PIPE_GENERATION
#समावेश "isp/kernels/sdis/common/ia_css_sdis_common_types.h"
#पूर्ण_अगर

/* DVS 2.0 Coefficient types. This काष्ठाure contains 4 poपूर्णांकers to
 *  arrays that contain the coeffients क्रम each type.
 */
काष्ठा ia_css_dvs2_coef_types अणु
	s16 *odd_real; /** real part of the odd coefficients*/
	s16 *odd_imag; /** imaginary part of the odd coefficients*/
	s16 *even_real;/** real part of the even coefficients*/
	s16 *even_imag;/** imaginary part of the even coefficients*/
पूर्ण;

/* DVS 2.0 Coefficients. This काष्ठाure describes the coefficients that are needed क्रम the dvs statistics.
 *  e.g. hor_coefs.odd_real is the poपूर्णांकer to पूर्णांक16_t[grid.num_hor_coefs] containing the horizontal odd real
 *  coefficients.
 */
काष्ठा ia_css_dvs2_coefficients अणु
	काष्ठा ia_css_dvs_grid_info
		grid;        /** grid info contains the dimensions of the dvs grid */
	काष्ठा ia_css_dvs2_coef_types
		hor_coefs; /** काष्ठा with poपूर्णांकers that contain the horizontal coefficients */
	काष्ठा ia_css_dvs2_coef_types
		ver_coefs; /** काष्ठा with poपूर्णांकers that contain the vertical coefficients */
पूर्ण;

/* DVS 2.0 Statistic types. This काष्ठाure contains 4 poपूर्णांकers to
 *  arrays that contain the statistics क्रम each type.
 */
काष्ठा ia_css_dvs2_stat_types अणु
	s32 *odd_real; /** real part of the odd statistics*/
	s32 *odd_imag; /** imaginary part of the odd statistics*/
	s32 *even_real;/** real part of the even statistics*/
	s32 *even_imag;/** imaginary part of the even statistics*/
पूर्ण;

/* DVS 2.0 Statistics. This काष्ठाure describes the statistics that are generated using the provided coefficients.
 *  e.g. hor_prod.odd_real is the poपूर्णांकer to पूर्णांक16_t[grid.aligned_height][grid.aligned_width] containing
 *  the horizontal odd real statistics. Valid statistics data area is पूर्णांक16_t[0..grid.height-1][0..grid.width-1]
 */
काष्ठा ia_css_dvs2_statistics अणु
	काष्ठा ia_css_dvs_grid_info
		grid;       /** grid info contains the dimensions of the dvs grid */
	काष्ठा ia_css_dvs2_stat_types
		hor_prod; /** काष्ठा with poपूर्णांकers that contain the horizontal statistics */
	काष्ठा ia_css_dvs2_stat_types
		ver_prod; /** काष्ठा with poपूर्णांकers that contain the vertical statistics */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_SDIS2_TYPES_H */
