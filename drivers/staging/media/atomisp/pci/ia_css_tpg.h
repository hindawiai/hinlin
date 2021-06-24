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

#अगर_अघोषित __IA_CSS_TPG_H
#घोषणा __IA_CSS_TPG_H

/* @file
 * This file contains support क्रम the test pattern generator (TPG)
 */

/* Enumerate the TPG IDs.
 */
क्रमागत ia_css_tpg_id अणु
	IA_CSS_TPG_ID0,
	IA_CSS_TPG_ID1,
	IA_CSS_TPG_ID2
पूर्ण;

/**
 * Maximum number of TPG IDs.
 *
 * Make sure the value of this define माला_लो changed to reflect the correct
 * number of ia_css_tpg_id क्रमागत अगर you add/delete an item in the क्रमागत.
 */
#घोषणा N_CSS_TPG_IDS (IA_CSS_TPG_ID2 + 1)

/* Enumerate the TPG modes.
 */
क्रमागत ia_css_tpg_mode अणु
	IA_CSS_TPG_MODE_RAMP,
	IA_CSS_TPG_MODE_CHECKERBOARD,
	IA_CSS_TPG_MODE_FRAME_BASED_COLOR,
	IA_CSS_TPG_MODE_MONO
पूर्ण;

/* @brief Configure the test pattern generator.
 *
 * Configure the Test Pattern Generator, the way these values are used to
 * generate the pattern can be seen in the HRT extension क्रम the test pattern
 * generator:
 * devices/test_pat_gen/hrt/include/test_pat_gen.h: hrt_calc_tpg_data().
 *
 * This पूर्णांकerface is deprecated, it is not portable -> move to input प्रणाली API
 *
@code
अचिन्हित पूर्णांक test_pattern_value(अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक y)
अणु
 अचिन्हित पूर्णांक x_val, y_val;
 अगर (x_delta > 0) (x_val = (x << x_delta) & x_mask;
 अन्यथा (x_val = (x >> -x_delta) & x_mask;
 अगर (y_delta > 0) (y_val = (y << y_delta) & y_mask;
 अन्यथा (y_val = (y >> -y_delta) & x_mask;
 वापस (x_val + y_val) & xy_mask;
पूर्ण
@endcode
 */
काष्ठा ia_css_tpg_config अणु
	क्रमागत ia_css_tpg_id   id;
	क्रमागत ia_css_tpg_mode mode;
	अचिन्हित पूर्णांक         x_mask;
	पूर्णांक                  x_delta;
	अचिन्हित पूर्णांक         y_mask;
	पूर्णांक                  y_delta;
	अचिन्हित पूर्णांक         xy_mask;
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_TPG_H */
