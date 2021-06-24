<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Release Version: irci_stable_candrpv_0415_20150521_0458 */
/* Release Version: irci_ecr-master_20150911_0724 */
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

#समावेश "ia_css_hdr.host.h"

व्योम
ia_css_hdr_init_config(
    काष्ठा sh_css_isp_hdr_params *to,
    स्थिर काष्ठा ia_css_hdr_config *from,
    अचिन्हित पूर्णांक size)
अणु
	पूर्णांक i;
	(व्योम)size;

	क्रम (i = 0; i < HDR_NUM_INPUT_FRAMES - 1; i++) अणु
		to->irradiance.match_shअगरt[i] = from->irradiance.match_shअगरt[i];
		to->irradiance.match_mul[i]   = from->irradiance.match_mul[i];
		to->irradiance.thr_low[i]     = from->irradiance.thr_low[i];
		to->irradiance.thr_high[i]    = from->irradiance.thr_high[i];
		to->irradiance.thr_coeff[i]   = from->irradiance.thr_coeff[i];
		to->irradiance.thr_shअगरt[i]   = from->irradiance.thr_shअगरt[i];
	पूर्ण
	to->irradiance.test_irr    = from->irradiance.test_irr;
	to->irradiance.weight_bpp  = from->irradiance.weight_bpp;

	to->deghost.test_deg    = from->deghost.test_deg;
	to->exclusion.test_excl = from->exclusion.test_excl;
पूर्ण
