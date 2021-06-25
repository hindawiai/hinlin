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

#अगर_अघोषित __IA_CSS_SC_PARAM_H
#घोषणा __IA_CSS_SC_PARAM_H

#समावेश "type_support.h"

/* SC (Shading Corrction) */
काष्ठा sh_css_isp_sc_params अणु
	s32 gain_shअगरt;
पूर्ण;

/* Number of horizontal slice बार क्रम पूर्णांकerpolated gain:
 *
 * The start position of the पूर्णांकernal frame करोes not match the start position of the shading table.
 * To get a vector of shading gains (पूर्णांकerpolated horizontally and vertically)
 * which matches a vector on the पूर्णांकernal frame,
 * vec_slice is used क्रम 2 adjacent vectors of shading gains.
 * The number of shअगरt बार by vec_slice is 8.
 *     Max grid cell bqs to support the shading table centerting: N = 32
 *     CEIL_DIV(N-1, ISP_SLICE_NELEMS) = CEIL_DIV(31, 4) = 8
 */
#घोषणा SH_CSS_SC_INTERPED_GAIN_HOR_SLICE_TIMES   8

काष्ठा sh_css_isp_sc_isp_config अणु
	u32 पूर्णांकerped_gain_hor_slice_bqs[SH_CSS_SC_INTERPED_GAIN_HOR_SLICE_TIMES];
	u32 पूर्णांकernal_frame_origin_y_bqs_on_sctbl;
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_SC_PARAM_H */
