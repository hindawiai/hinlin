<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
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

#समावेश "ia_css_types.h"
#समावेश "sh_css_defs.h"
#समावेश "ia_css_debug.h"

#समावेश "ia_css_cnr2.host.h"

स्थिर काष्ठा ia_css_cnr_config शेष_cnr_config = अणु
	0,
	0,
	100,
	100,
	100,
	50,
	50,
	50
पूर्ण;

व्योम
ia_css_cnr_encode(
    काष्ठा sh_css_isp_cnr_params *to,
    स्थिर काष्ठा ia_css_cnr_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	to->coring_u = from->coring_u;
	to->coring_v = from->coring_v;
	to->sense_gain_vy = from->sense_gain_vy;
	to->sense_gain_vu = from->sense_gain_vu;
	to->sense_gain_vv = from->sense_gain_vv;
	to->sense_gain_hy = from->sense_gain_hy;
	to->sense_gain_hu = from->sense_gain_hu;
	to->sense_gain_hv = from->sense_gain_hv;
पूर्ण

व्योम
ia_css_cnr_dump(
    स्थिर काष्ठा sh_css_isp_cnr_params *cnr,
    अचिन्हित पूर्णांक level);

व्योम
ia_css_cnr_debug_dtrace(
    स्थिर काष्ठा ia_css_cnr_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.coring_u=%d, config.coring_v=%d, config.sense_gain_vy=%d, config.sense_gain_hy=%d, config.sense_gain_vu=%d, config.sense_gain_hu=%d, config.sense_gain_vv=%d, config.sense_gain_hv=%d\n",
			    config->coring_u, config->coring_v,
			    config->sense_gain_vy, config->sense_gain_hy,
			    config->sense_gain_vu, config->sense_gain_hu,
			    config->sense_gain_vv, config->sense_gain_hv);
पूर्ण

व्योम
ia_css_init_cnr2_state(
    व्योम/*काष्ठा sh_css_isp_cnr_vmem_state*/ * state,
    माप_प्रकार size)
अणु
	स_रखो(state, 0, size);
पूर्ण
