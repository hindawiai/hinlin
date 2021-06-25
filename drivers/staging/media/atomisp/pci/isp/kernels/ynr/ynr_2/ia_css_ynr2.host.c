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
#समावेश "assert_support.h"

#समावेश "ia_css_ynr2.host.h"

स्थिर काष्ठा ia_css_ynr_config शेष_ynr_config = अणु
	0,
	0,
	0,
	0,
पूर्ण;

स्थिर काष्ठा ia_css_fc_config शेष_fc_config = अणु
	1,
	0,		/* 0 -> ineffective */
	0,		/* 0 -> ineffective */
	0,		/* 0 -> ineffective */
	0,		/* 0 -> ineffective */
	(1 << (ISP_VEC_ELEMBITS - 2)),		/* 0.5 */
	(1 << (ISP_VEC_ELEMBITS - 2)),		/* 0.5 */
	(1 << (ISP_VEC_ELEMBITS - 2)),		/* 0.5 */
	(1 << (ISP_VEC_ELEMBITS - 2)),		/* 0.5 */
	(1 << (ISP_VEC_ELEMBITS - 1)) - 1,	/* 1 */
	(1 << (ISP_VEC_ELEMBITS - 1)) - 1,	/* 1 */
	(पूर्णांक16_t)-(1 << (ISP_VEC_ELEMBITS - 1)),	/* -1 */
	(पूर्णांक16_t)-(1 << (ISP_VEC_ELEMBITS - 1)),	/* -1 */
पूर्ण;

व्योम
ia_css_ynr_encode(
    काष्ठा sh_css_isp_yee2_params *to,
    स्थिर काष्ठा ia_css_ynr_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	to->edge_sense_gain_0   = from->edge_sense_gain_0;
	to->edge_sense_gain_1   = from->edge_sense_gain_1;
	to->corner_sense_gain_0 = from->corner_sense_gain_0;
	to->corner_sense_gain_1 = from->corner_sense_gain_1;
पूर्ण

व्योम
ia_css_fc_encode(
    काष्ठा sh_css_isp_fc_params *to,
    स्थिर काष्ठा ia_css_fc_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	to->gain_exp   = from->gain_exp;

	to->coring_pos_0 = from->coring_pos_0;
	to->coring_pos_1 = from->coring_pos_1;
	to->coring_neg_0 = from->coring_neg_0;
	to->coring_neg_1 = from->coring_neg_1;

	to->gain_pos_0 = from->gain_pos_0;
	to->gain_pos_1 = from->gain_pos_1;
	to->gain_neg_0 = from->gain_neg_0;
	to->gain_neg_1 = from->gain_neg_1;

	to->crop_pos_0 = from->crop_pos_0;
	to->crop_pos_1 = from->crop_pos_1;
	to->crop_neg_0 = from->crop_neg_0;
	to->crop_neg_1 = from->crop_neg_1;
पूर्ण

व्योम
ia_css_ynr_dump(
    स्थिर काष्ठा sh_css_isp_yee2_params *yee2,
    अचिन्हित पूर्णांक level);

व्योम
ia_css_fc_dump(
    स्थिर काष्ठा sh_css_isp_fc_params *fc,
    अचिन्हित पूर्णांक level);

व्योम
ia_css_fc_debug_dtrace(
    स्थिर काष्ठा ia_css_fc_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.gain_exp=%d, config.coring_pos_0=%d, config.coring_pos_1=%d, config.coring_neg_0=%d, config.coring_neg_1=%d, config.gain_pos_0=%d, config.gain_pos_1=%d, config.gain_neg_0=%d, config.gain_neg_1=%d, config.crop_pos_0=%d, config.crop_pos_1=%d, config.crop_neg_0=%d, config.crop_neg_1=%d\n",
			    config->gain_exp,
			    config->coring_pos_0, config->coring_pos_1,
			    config->coring_neg_0, config->coring_neg_1,
			    config->gain_pos_0, config->gain_pos_1,
			    config->gain_neg_0, config->gain_neg_1,
			    config->crop_pos_0, config->crop_pos_1,
			    config->crop_neg_0, config->crop_neg_1);
पूर्ण

व्योम
ia_css_ynr_debug_dtrace(
    स्थिर काष्ठा ia_css_ynr_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.edge_sense_gain_0=%d, config.edge_sense_gain_1=%d, config.corner_sense_gain_0=%d, config.corner_sense_gain_1=%d\n",
			    config->edge_sense_gain_0, config->edge_sense_gain_1,
			    config->corner_sense_gain_0, config->corner_sense_gain_1);
पूर्ण
