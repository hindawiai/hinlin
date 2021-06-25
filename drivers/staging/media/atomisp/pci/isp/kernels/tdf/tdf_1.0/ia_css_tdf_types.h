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

#अगर_अघोषित __IA_CSS_TDF_TYPES_H
#घोषणा __IA_CSS_TDF_TYPES_H

/* @file
* CSS-API header file क्रम Transक्रमm Doमुख्य Filter parameters.
*/

#समावेश "type_support.h"

/* Transक्रमm Doमुख्य Filter configuration
 *
 * \मrief TDF खुला parameters.
 * \details Struct with all parameters क्रम the TDF kernel that can be set
 * from the CSS API.
 *
 * ISP2.6.1: TDF is used.
 */
काष्ठा ia_css_tdf_config अणु
	s32 thres_flat_table[64];	/** Final optimized strength table of NR क्रम flat region. */
	s32 thres_detail_table[64];	/** Final optimized strength table of NR क्रम detail region. */
	s32 epsilon_0;		/** Coefficient to control variance क्रम dark area (क्रम flat region). */
	s32 epsilon_1;		/** Coefficient to control variance क्रम bright area (क्रम flat region). */
	s32 eps_scale_text;		/** Epsilon scaling coefficient क्रम texture region. */
	s32 eps_scale_edge;		/** Epsilon scaling coefficient क्रम edge region. */
	s32 sepa_flat;		/** Threshold to judge flat (edge < m_Flat_thre). */
	s32 sepa_edge;		/** Threshold to judge edge (edge > m_Edge_thre). */
	s32 blend_flat;		/** Blending ratio at flat region. */
	s32 blend_text;		/** Blending ratio at texture region. */
	s32 blend_edge;		/** Blending ratio at edge region. */
	s32 shading_gain;		/** Gain of Shading control. */
	s32 shading_base_gain;	/** Base Gain of Shading control. */
	s32 local_y_gain;		/** Gain of local luminance control. */
	s32 local_y_base_gain;	/** Base gain of local luminance control. */
	s32 rad_x_origin;		/** Initial x coord. क्रम radius computation. */
	s32 rad_y_origin;		/** Initial y coord. क्रम radius computation. */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_TDF_TYPES_H */
