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
#समावेश "isp.h"

#समावेश "ia_css_ob.host.h"

स्थिर काष्ठा ia_css_ob_config शेष_ob_config = अणु
	IA_CSS_OB_MODE_NONE,
	0,
	0,
	0,
	0,
	0,
	0
पूर्ण;

/* TODO: include ob.isp.h to get isp knowledge and
   add निश्चित on platक्रमm restrictions */

व्योम
ia_css_ob_configure(
    काष्ठा sh_css_isp_ob_stream_config *config,
    अचिन्हित पूर्णांक isp_pipe_version,
    अचिन्हित पूर्णांक raw_bit_depth)
अणु
	config->isp_pipe_version = isp_pipe_version;
	config->raw_bit_depth    = raw_bit_depth;
पूर्ण

व्योम
ia_css_ob_encode(
    काष्ठा sh_css_isp_ob_params *to,
    स्थिर काष्ठा ia_css_ob_config *from,
    स्थिर काष्ठा sh_css_isp_ob_stream_config *config,
    अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक ob_bit_depth
	    = config->isp_pipe_version == 2 ? SH_CSS_BAYER_BITS : config->raw_bit_depth;
	अचिन्हित पूर्णांक scale = 16 - ob_bit_depth;

	(व्योम)size;
	चयन (from->mode) अणु
	हाल IA_CSS_OB_MODE_FIXED:
		to->blacklevel_gr = from->level_gr >> scale;
		to->blacklevel_r  = from->level_r  >> scale;
		to->blacklevel_b  = from->level_b  >> scale;
		to->blacklevel_gb = from->level_gb >> scale;
		to->area_start_bq = 0;
		to->area_length_bq = 0;
		to->area_length_bq_inverse = 0;
		अवरोध;
	हाल IA_CSS_OB_MODE_RASTER:
		to->blacklevel_gr = 0;
		to->blacklevel_r = 0;
		to->blacklevel_b = 0;
		to->blacklevel_gb = 0;
		to->area_start_bq = from->start_position;
		to->area_length_bq =
		    (from->end_position - from->start_position) + 1;
		to->area_length_bq_inverse = AREA_LENGTH_UNIT / to->area_length_bq;
		अवरोध;
	शेष:
		to->blacklevel_gr = 0;
		to->blacklevel_r = 0;
		to->blacklevel_b = 0;
		to->blacklevel_gb = 0;
		to->area_start_bq = 0;
		to->area_length_bq = 0;
		to->area_length_bq_inverse = 0;
		अवरोध;
	पूर्ण
पूर्ण

व्योम
ia_css_ob_vmem_encode(
    काष्ठा sh_css_isp_ob_vmem_params *to,
    स्थिर काष्ठा ia_css_ob_config *from,
    स्थिर काष्ठा sh_css_isp_ob_stream_config *config,
    अचिन्हित पूर्णांक size)
अणु
	काष्ठा sh_css_isp_ob_params पंचांगp;
	काष्ठा sh_css_isp_ob_params *ob = &पंचांगp;

	(व्योम)size;
	ia_css_ob_encode(&पंचांगp, from, config, माप(पंचांगp));

	अणु
		अचिन्हित पूर्णांक i;
		अचिन्हित पूर्णांक sp_obarea_start_bq  = ob->area_start_bq;
		अचिन्हित पूर्णांक sp_obarea_length_bq = ob->area_length_bq;
		अचिन्हित पूर्णांक low = sp_obarea_start_bq;
		अचिन्हित पूर्णांक high = low + sp_obarea_length_bq;
		u16 all_ones = ~0;

		क्रम (i = 0; i < OBAREA_MASK_SIZE; i++) अणु
			अगर (i >= low && i < high)
				to->vmask[i / ISP_VEC_NELEMS][i % ISP_VEC_NELEMS] = all_ones;
			अन्यथा
				to->vmask[i / ISP_VEC_NELEMS][i % ISP_VEC_NELEMS] = 0;
		पूर्ण
	पूर्ण
पूर्ण

व्योम
ia_css_ob_dump(
    स्थिर काष्ठा sh_css_isp_ob_params *ob,
    अचिन्हित पूर्णांक level)
अणु
	अगर (!ob) वापस;
	ia_css_debug_dtrace(level, "Optical Black:\n");
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ob_blacklevel_gr", ob->blacklevel_gr);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ob_blacklevel_r", ob->blacklevel_r);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ob_blacklevel_b", ob->blacklevel_b);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ob_blacklevel_gb", ob->blacklevel_gb);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "obarea_start_bq", ob->area_start_bq);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "obarea_length_bq", ob->area_length_bq);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "obarea_length_bq_inverse",
			    ob->area_length_bq_inverse);
पूर्ण

व्योम
ia_css_ob_debug_dtrace(
    स्थिर काष्ठा ia_css_ob_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.mode=%d, config.level_gr=%d, config.level_r=%d, config.level_b=%d,  config.level_gb=%d, config.start_position=%d, config.end_position=%d\n",
			    config->mode,
			    config->level_gr, config->level_r,
			    config->level_b, config->level_gb,
			    config->start_position, config->end_position);
पूर्ण
