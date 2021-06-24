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

#समावेश "ia_css_dpc2.host.h"
#समावेश "assert_support.h"

व्योम
ia_css_dpc2_encode(
    काष्ठा ia_css_isp_dpc2_params *to,
    स्थिर काष्ठा ia_css_dpc2_config *from,
    माप_प्रकार size)
अणु
	(व्योम)size;

	निश्चित((from->metric1 >= 0) && (from->metric1 <= METRIC1_ONE_FP));
	निश्चित((from->metric3 >= 0) && (from->metric3 <= METRIC3_ONE_FP));
	निश्चित((from->metric2 >= METRIC2_ONE_FP) &&
	       (from->metric2 < 256 * METRIC2_ONE_FP));
	निश्चित((from->wb_gain_gr > 0) && (from->wb_gain_gr < 16 * WBGAIN_ONE_FP));
	निश्चित((from->wb_gain_r  > 0) && (from->wb_gain_r  < 16 * WBGAIN_ONE_FP));
	निश्चित((from->wb_gain_b  > 0) && (from->wb_gain_b  < 16 * WBGAIN_ONE_FP));
	निश्चित((from->wb_gain_gb > 0) && (from->wb_gain_gb < 16 * WBGAIN_ONE_FP));

	to->metric1 = from->metric1;
	to->metric2 = from->metric2;
	to->metric3 = from->metric3;

	to->wb_gain_gr = from->wb_gain_gr;
	to->wb_gain_r  = from->wb_gain_r;
	to->wb_gain_b  = from->wb_gain_b;
	to->wb_gain_gb = from->wb_gain_gb;
पूर्ण

/* TODO: AM: This needs a proper implementation. */
व्योम
ia_css_init_dpc2_state(
    व्योम *state,
    माप_प्रकार size)
अणु
	(व्योम)state;
	(व्योम)size;
पूर्ण

#अगर_अघोषित IA_CSS_NO_DEBUG
/* TODO: AM: This needs a proper implementation. */
व्योम
ia_css_dpc2_debug_dtrace(
    स्थिर काष्ठा ia_css_dpc2_config *config,
    अचिन्हित पूर्णांक level)
अणु
	(व्योम)config;
	(व्योम)level;
पूर्ण
#पूर्ण_अगर
