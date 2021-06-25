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

#समावेश "hmm.h"

#समावेश "assert_support.h"
#समावेश "ia_css_debug.h"
#समावेश "ia_css_sdis_types.h"
#समावेश "sdis/common/ia_css_sdis_common.host.h"
#समावेश "ia_css_sdis.host.h"

स्थिर काष्ठा ia_css_dvs_coefficients शेष_sdis_config = अणु
	.grid = अणु 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	.hor_coefs = शून्य,
	.ver_coefs = शून्य
पूर्ण;

अटल व्योम
fill_row(लघु *निजी, स्थिर लघु *खुला, अचिन्हित पूर्णांक width,
	 अचिन्हित पूर्णांक padding)
अणु
	निश्चित((पूर्णांक)width >= 0);
	निश्चित((पूर्णांक)padding >= 0);
	स_नकल(निजी, खुला, width * माप(लघु));
	स_रखो(&निजी[width], 0, padding * माप(लघु));
पूर्ण

व्योम ia_css_sdis_horicoef_vmem_encode(
    काष्ठा sh_css_isp_sdis_hori_coef_tbl *to,
    स्थिर काष्ठा ia_css_dvs_coefficients *from,
    अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक aligned_width = from->grid.aligned_width *
				     from->grid.bqs_per_grid_cell;
	अचिन्हित पूर्णांक width         = from->grid.num_hor_coefs;
	पूर्णांक      padding       = aligned_width - width;
	अचिन्हित पूर्णांक stride        = size / IA_CSS_DVS_NUM_COEF_TYPES / माप(लघु);
	अचिन्हित पूर्णांक total_bytes   = aligned_width * IA_CSS_DVS_NUM_COEF_TYPES * माप(
					 लघु);
	लघु   *खुला        = from->hor_coefs;
	लघु   *निजी       = (लघु *)to;
	अचिन्हित पूर्णांक type;

	/* Copy the table, add padding */
	निश्चित(padding >= 0);
	निश्चित(total_bytes <= size);
	निश्चित(size % (IA_CSS_DVS_NUM_COEF_TYPES * ISP_VEC_NELEMS * माप(
			   लघु)) == 0);

	क्रम (type = 0; type < IA_CSS_DVS_NUM_COEF_TYPES; type++) अणु
		fill_row(&निजी[type * stride], &खुला[type * width], width, padding);
	पूर्ण
पूर्ण

व्योम ia_css_sdis_vertcoef_vmem_encode(
    काष्ठा sh_css_isp_sdis_vert_coef_tbl *to,
    स्थिर काष्ठा ia_css_dvs_coefficients *from,
    अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक aligned_height = from->grid.aligned_height *
				      from->grid.bqs_per_grid_cell;
	अचिन्हित पूर्णांक height         = from->grid.num_ver_coefs;
	पूर्णांक      padding        = aligned_height - height;
	अचिन्हित पूर्णांक stride         = size / IA_CSS_DVS_NUM_COEF_TYPES / माप(लघु);
	अचिन्हित पूर्णांक total_bytes    = aligned_height * IA_CSS_DVS_NUM_COEF_TYPES *
				      माप(लघु);
	लघु   *खुला         = from->ver_coefs;
	लघु   *निजी        = (लघु *)to;
	अचिन्हित पूर्णांक type;

	/* Copy the table, add padding */
	निश्चित(padding >= 0);
	निश्चित(total_bytes <= size);
	निश्चित(size % (IA_CSS_DVS_NUM_COEF_TYPES * ISP_VEC_NELEMS * माप(
			   लघु)) == 0);

	क्रम (type = 0; type < IA_CSS_DVS_NUM_COEF_TYPES; type++) अणु
		fill_row(&निजी[type * stride], &खुला[type * height], height, padding);
	पूर्ण
पूर्ण

व्योम ia_css_sdis_horiproj_encode(
    काष्ठा sh_css_isp_sdis_hori_proj_tbl *to,
    स्थिर काष्ठा ia_css_dvs_coefficients *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)to;
	(व्योम)from;
	(व्योम)size;
पूर्ण

व्योम ia_css_sdis_vertproj_encode(
    काष्ठा sh_css_isp_sdis_vert_proj_tbl *to,
    स्थिर काष्ठा ia_css_dvs_coefficients *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)to;
	(व्योम)from;
	(व्योम)size;
पूर्ण

व्योम ia_css_get_isp_dis_coefficients(
    काष्ठा ia_css_stream *stream,
    लघु *horizontal_coefficients,
    लघु *vertical_coefficients)
अणु
	काष्ठा ia_css_isp_parameters *params;
	अचिन्हित पूर्णांक hor_num_isp, ver_num_isp;
	अचिन्हित पूर्णांक hor_num_3a,  ver_num_3a;
	पूर्णांक i;
	काष्ठा ia_css_binary *dvs_binary;

	IA_CSS_ENTER("void");

	निश्चित(horizontal_coefficients);
	निश्चित(vertical_coefficients);

	params = stream->isp_params_configs;

	/* Only video pipe supports DVS */
	dvs_binary = ia_css_stream_get_dvs_binary(stream);
	अगर (!dvs_binary)
		वापस;

	hor_num_isp = dvs_binary->dis.coef.pad.width;
	ver_num_isp = dvs_binary->dis.coef.pad.height;
	hor_num_3a  = dvs_binary->dis.coef.dim.width;
	ver_num_3a  = dvs_binary->dis.coef.dim.height;

	क्रम (i = 0; i < IA_CSS_DVS_NUM_COEF_TYPES; i++) अणु
		fill_row(&horizontal_coefficients[i * hor_num_isp],
			 &params->dvs_coefs.hor_coefs[i * hor_num_3a], hor_num_3a,
			 hor_num_isp - hor_num_3a);
	पूर्ण
	क्रम (i = 0; i < SH_CSS_DIS_VER_NUM_COEF_TYPES(dvs_binary); i++) अणु
		fill_row(&vertical_coefficients[i * ver_num_isp],
			 &params->dvs_coefs.ver_coefs[i * ver_num_3a], ver_num_3a,
			 ver_num_isp - ver_num_3a);
	पूर्ण

	IA_CSS_LEAVE("void");
पूर्ण

माप_प्रकार
ia_css_sdis_hor_coef_tbl_bytes(
    स्थिर काष्ठा ia_css_binary *binary)
अणु
	अगर (binary->info->sp.pipeline.isp_pipe_version == 1)
		वापस माप(लघु) * IA_CSS_DVS_NUM_COEF_TYPES  * binary->dis.coef.pad.width;
	अन्यथा
		वापस माप(लघु) * IA_CSS_DVS2_NUM_COEF_TYPES * binary->dis.coef.pad.width;
पूर्ण

माप_प्रकार
ia_css_sdis_ver_coef_tbl_bytes(
    स्थिर काष्ठा ia_css_binary *binary)
अणु
	वापस माप(लघु) * SH_CSS_DIS_VER_NUM_COEF_TYPES(binary) *
	       binary->dis.coef.pad.height;
पूर्ण

व्योम
ia_css_sdis_init_info(
    काष्ठा ia_css_sdis_info *dis,
    अचिन्हित पूर्णांक sc_3a_dis_width,
    अचिन्हित पूर्णांक sc_3a_dis_padded_width,
    अचिन्हित पूर्णांक sc_3a_dis_height,
    अचिन्हित पूर्णांक isp_pipe_version,
    अचिन्हित पूर्णांक enabled)
अणु
	अगर (!enabled) अणु
		*dis = (काष्ठा ia_css_sdis_info) अणु पूर्ण;
		वापस;
	पूर्ण

	dis->deci_factor_log2 = SH_CSS_DIS_DECI_FACTOR_LOG2;

	dis->grid.dim.width  =
	    _ISP_BQS(sc_3a_dis_width) >> SH_CSS_DIS_DECI_FACTOR_LOG2;
	dis->grid.dim.height =
	    _ISP_BQS(sc_3a_dis_height) >> SH_CSS_DIS_DECI_FACTOR_LOG2;
	dis->grid.pad.width  =
	    CEIL_SHIFT(_ISP_BQS(sc_3a_dis_padded_width), SH_CSS_DIS_DECI_FACTOR_LOG2);
	dis->grid.pad.height =
	    CEIL_SHIFT(_ISP_BQS(sc_3a_dis_height), SH_CSS_DIS_DECI_FACTOR_LOG2);

	dis->coef.dim.width  =
	    (_ISP_BQS(sc_3a_dis_width)  >> SH_CSS_DIS_DECI_FACTOR_LOG2) <<
	    SH_CSS_DIS_DECI_FACTOR_LOG2;
	dis->coef.dim.height =
	    (_ISP_BQS(sc_3a_dis_height) >> SH_CSS_DIS_DECI_FACTOR_LOG2) <<
	    SH_CSS_DIS_DECI_FACTOR_LOG2;
	dis->coef.pad.width  =
	    __ISP_SDIS_HOR_COEF_NUM_VECS(sc_3a_dis_padded_width) * ISP_VEC_NELEMS;
	dis->coef.pad.height =
	    __ISP_SDIS_VER_COEF_NUM_VECS(sc_3a_dis_height) * ISP_VEC_NELEMS;
	अगर (isp_pipe_version == 1) अणु
		dis->proj.dim.width  =
		    _ISP_BQS(sc_3a_dis_height) >> SH_CSS_DIS_DECI_FACTOR_LOG2;
		dis->proj.dim.height =
		    _ISP_BQS(sc_3a_dis_width)  >> SH_CSS_DIS_DECI_FACTOR_LOG2;
	पूर्ण अन्यथा अणु
		dis->proj.dim.width  =
		    (_ISP_BQS(sc_3a_dis_width)  >> SH_CSS_DIS_DECI_FACTOR_LOG2) *
		    (_ISP_BQS(sc_3a_dis_height) >> SH_CSS_DIS_DECI_FACTOR_LOG2);
		dis->proj.dim.height =
		    (_ISP_BQS(sc_3a_dis_width)  >> SH_CSS_DIS_DECI_FACTOR_LOG2) *
		    (_ISP_BQS(sc_3a_dis_height) >> SH_CSS_DIS_DECI_FACTOR_LOG2);
	पूर्ण
	dis->proj.pad.width  =
	    __ISP_SDIS_HOR_PROJ_NUM_ISP(sc_3a_dis_padded_width,
					sc_3a_dis_height,
					SH_CSS_DIS_DECI_FACTOR_LOG2,
					isp_pipe_version);
	dis->proj.pad.height =
	    __ISP_SDIS_VER_PROJ_NUM_ISP(sc_3a_dis_padded_width,
					SH_CSS_DIS_DECI_FACTOR_LOG2);
पूर्ण

व्योम ia_css_sdis_clear_coefficients(
    काष्ठा ia_css_dvs_coefficients *dvs_coefs)
अणु
	dvs_coefs->hor_coefs = शून्य;
	dvs_coefs->ver_coefs = शून्य;
पूर्ण

पूर्णांक
ia_css_get_dvs_statistics(
    काष्ठा ia_css_dvs_statistics	       *host_stats,
    स्थिर काष्ठा ia_css_isp_dvs_statistics *isp_stats) अणु
	काष्ठा ia_css_isp_dvs_statistics_map *map;
	पूर्णांक ret = 0;

	IA_CSS_ENTER("host_stats=%p, isp_stats=%p", host_stats, isp_stats);

	निश्चित(host_stats);
	निश्चित(isp_stats);

	map = ia_css_isp_dvs_statistics_map_allocate(isp_stats, शून्य);
	अगर (map)
	अणु
		hmm_load(isp_stats->data_ptr, map->data_ptr, isp_stats->size);
		ia_css_translate_dvs_statistics(host_stats, map);
		ia_css_isp_dvs_statistics_map_मुक्त(map);
	पूर्ण अन्यथा
	अणु
		IA_CSS_ERROR("out of memory");
		ret = -ENOMEM;
	पूर्ण

	IA_CSS_LEAVE_ERR(ret);
	वापस ret;
पूर्ण

व्योम
ia_css_translate_dvs_statistics(
    काष्ठा ia_css_dvs_statistics               *host_stats,
    स्थिर काष्ठा ia_css_isp_dvs_statistics_map *isp_stats)
अणु
	अचिन्हित पूर्णांक hor_num_isp, ver_num_isp, hor_num_dvs, ver_num_dvs, i;
	s32 *hor_ptr_dvs, *ver_ptr_dvs, *hor_ptr_isp, *ver_ptr_isp;

	निश्चित(host_stats);
	निश्चित(host_stats->hor_proj);
	निश्चित(host_stats->ver_proj);
	निश्चित(isp_stats);
	निश्चित(isp_stats->hor_proj);
	निश्चित(isp_stats->ver_proj);

	IA_CSS_ENTER("hproj=%p, vproj=%p, haddr=%p, vaddr=%p",
		     host_stats->hor_proj, host_stats->ver_proj,
		     isp_stats->hor_proj, isp_stats->ver_proj);

	hor_num_isp = host_stats->grid.aligned_height;
	ver_num_isp = host_stats->grid.aligned_width;
	hor_ptr_isp = isp_stats->hor_proj;
	ver_ptr_isp = isp_stats->ver_proj;
	hor_num_dvs = host_stats->grid.height;
	ver_num_dvs = host_stats->grid.width;
	hor_ptr_dvs = host_stats->hor_proj;
	ver_ptr_dvs = host_stats->ver_proj;

	क्रम (i = 0; i < IA_CSS_DVS_NUM_COEF_TYPES; i++) अणु
		स_नकल(hor_ptr_dvs, hor_ptr_isp, hor_num_dvs * माप(पूर्णांक32_t));
		hor_ptr_isp += hor_num_isp;
		hor_ptr_dvs += hor_num_dvs;

		स_नकल(ver_ptr_dvs, ver_ptr_isp, ver_num_dvs * माप(पूर्णांक32_t));
		ver_ptr_isp += ver_num_isp;
		ver_ptr_dvs += ver_num_dvs;
	पूर्ण

	IA_CSS_LEAVE("void");
पूर्ण

काष्ठा ia_css_isp_dvs_statistics *
ia_css_isp_dvs_statistics_allocate(
    स्थिर काष्ठा ia_css_dvs_grid_info *grid)
अणु
	काष्ठा ia_css_isp_dvs_statistics *me;
	पूर्णांक hor_size, ver_size;

	निश्चित(grid);

	IA_CSS_ENTER("grid=%p", grid);

	अगर (!grid->enable)
		वापस शून्य;

	me = kvसुस्मृति(1, माप(*me), GFP_KERNEL);
	अगर (!me)
		जाओ err;

	hor_size = CEIL_MUL(माप(पूर्णांक) * IA_CSS_DVS_NUM_COEF_TYPES *
			    grid->aligned_height,
			    HIVE_ISP_DDR_WORD_BYTES);
	ver_size = CEIL_MUL(माप(पूर्णांक) * IA_CSS_DVS_NUM_COEF_TYPES *
			    grid->aligned_width,
			    HIVE_ISP_DDR_WORD_BYTES);

	me->size = hor_size + ver_size;
	me->data_ptr = hmm_alloc(me->size, HMM_BO_PRIVATE, 0, शून्य, 0);
	अगर (me->data_ptr == mmgr_शून्य)
		जाओ err;
	me->hor_size = hor_size;
	me->hor_proj = me->data_ptr;
	me->ver_size = ver_size;
	me->ver_proj = me->data_ptr + hor_size;

	IA_CSS_LEAVE("return=%p", me);

	वापस me;
err:
	ia_css_isp_dvs_statistics_मुक्त(me);

	IA_CSS_LEAVE("return=%p", शून्य);

	वापस शून्य;
पूर्ण

काष्ठा ia_css_isp_dvs_statistics_map *
ia_css_isp_dvs_statistics_map_allocate(
    स्थिर काष्ठा ia_css_isp_dvs_statistics *isp_stats,
    व्योम *data_ptr)
अणु
	काष्ठा ia_css_isp_dvs_statistics_map *me;
	/* Winकरोws compiler करोes not like adding sizes to a व्योम *
	 * so we use a local अक्षर * instead. */
	अक्षर *base_ptr;

	me = kvदो_स्मृति(माप(*me), GFP_KERNEL);
	अगर (!me) अणु
		IA_CSS_LOG("cannot allocate memory");
		जाओ err;
	पूर्ण

	me->data_ptr = data_ptr;
	me->data_allocated = !data_ptr;

	अगर (!me->data_ptr) अणु
		me->data_ptr = kvदो_स्मृति(isp_stats->size, GFP_KERNEL);
		अगर (!me->data_ptr) अणु
			IA_CSS_LOG("cannot allocate memory");
			जाओ err;
		पूर्ण
	पूर्ण
	base_ptr = me->data_ptr;

	me->size = isp_stats->size;
	/* GCC complains when we assign a अक्षर * to a व्योम *, so these
	 * casts are necessary unक्रमtunately. */
	me->hor_proj = (व्योम *)base_ptr;
	me->ver_proj = (व्योम *)(base_ptr + isp_stats->hor_size);

	वापस me;
err:
	kvमुक्त(me);
	वापस शून्य;
पूर्ण

व्योम
ia_css_isp_dvs_statistics_map_मुक्त(काष्ठा ia_css_isp_dvs_statistics_map *me)
अणु
	अगर (me) अणु
		अगर (me->data_allocated)
			kvमुक्त(me->data_ptr);
		kvमुक्त(me);
	पूर्ण
पूर्ण

व्योम
ia_css_isp_dvs_statistics_मुक्त(काष्ठा ia_css_isp_dvs_statistics *me)
अणु
	अगर (me) अणु
		hmm_मुक्त(me->data_ptr);
		kvमुक्त(me);
	पूर्ण
पूर्ण

व्योम ia_css_sdis_horicoef_debug_dtrace(
    स्थिर काष्ठा ia_css_dvs_coefficients *config, अचिन्हित पूर्णांक level)
अणु
	(व्योम)config;
	(व्योम)level;
पूर्ण

व्योम ia_css_sdis_vertcoef_debug_dtrace(
    स्थिर काष्ठा ia_css_dvs_coefficients *config, अचिन्हित पूर्णांक level)
अणु
	(व्योम)config;
	(व्योम)level;
पूर्ण

व्योम ia_css_sdis_horiproj_debug_dtrace(
    स्थिर काष्ठा ia_css_dvs_coefficients *config, अचिन्हित पूर्णांक level)
अणु
	(व्योम)config;
	(व्योम)level;
पूर्ण

व्योम ia_css_sdis_vertproj_debug_dtrace(
    स्थिर काष्ठा ia_css_dvs_coefficients *config, अचिन्हित पूर्णांक level)
अणु
	(व्योम)config;
	(व्योम)level;
पूर्ण
