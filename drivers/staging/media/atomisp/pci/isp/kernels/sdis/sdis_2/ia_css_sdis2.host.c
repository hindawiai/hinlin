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

#समावेश <निश्चित_support.h>
#समावेश "ia_css_debug.h"
#समावेश "ia_css_sdis2.host.h"

स्थिर काष्ठा ia_css_dvs2_coefficients शेष_sdis2_config = अणु
	.grid = अणु 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	.hor_coefs = अणु शून्य, शून्य, शून्य, शून्य पूर्ण,
	.ver_coefs = अणु शून्य, शून्य, शून्य, शून्य पूर्ण,
पूर्ण;

अटल व्योम
fill_row(लघु *निजी, स्थिर लघु *खुला, अचिन्हित पूर्णांक width,
	 अचिन्हित पूर्णांक padding)
अणु
	स_नकल(निजी, खुला, width * माप(लघु));
	स_रखो(&निजी[width], 0, padding * माप(लघु));
पूर्ण

व्योम ia_css_sdis2_horicoef_vmem_encode(
    काष्ठा sh_css_isp_sdis_hori_coef_tbl *to,
    स्थिर काष्ठा ia_css_dvs2_coefficients *from,
    अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक aligned_width = from->grid.aligned_width *
				     from->grid.bqs_per_grid_cell;
	अचिन्हित पूर्णांक width         = from->grid.num_hor_coefs;
	पूर्णांक      padding       = aligned_width - width;
	अचिन्हित पूर्णांक stride        = size / IA_CSS_DVS2_NUM_COEF_TYPES / माप(लघु);
	अचिन्हित पूर्णांक total_bytes   = aligned_width * IA_CSS_DVS2_NUM_COEF_TYPES *
				     माप(लघु);
	लघु   *निजी       = (लघु *)to;

	/* Copy the table, add padding */
	निश्चित(padding >= 0);
	निश्चित(total_bytes <= size);
	निश्चित(size % (IA_CSS_DVS2_NUM_COEF_TYPES * ISP_VEC_NELEMS * माप(
			   लघु)) == 0);
	fill_row(&निजी[0 * stride], from->hor_coefs.odd_real,  width, padding);
	fill_row(&निजी[1 * stride], from->hor_coefs.odd_imag,  width, padding);
	fill_row(&निजी[2 * stride], from->hor_coefs.even_real, width, padding);
	fill_row(&निजी[3 * stride], from->hor_coefs.even_imag, width, padding);
पूर्ण

व्योम ia_css_sdis2_vertcoef_vmem_encode(
    काष्ठा sh_css_isp_sdis_vert_coef_tbl *to,
    स्थिर काष्ठा ia_css_dvs2_coefficients *from,
    अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक aligned_height = from->grid.aligned_height *
				      from->grid.bqs_per_grid_cell;
	अचिन्हित पूर्णांक height         = from->grid.num_ver_coefs;
	पूर्णांक      padding        = aligned_height - height;
	अचिन्हित पूर्णांक stride         = size / IA_CSS_DVS2_NUM_COEF_TYPES / माप(लघु);
	अचिन्हित पूर्णांक total_bytes    = aligned_height * IA_CSS_DVS2_NUM_COEF_TYPES *
				      माप(लघु);
	लघु   *निजी        = (लघु *)to;

	/* Copy the table, add padding */
	निश्चित(padding >= 0);
	निश्चित(total_bytes <= size);
	निश्चित(size % (IA_CSS_DVS2_NUM_COEF_TYPES * ISP_VEC_NELEMS * माप(
			   लघु)) == 0);
	fill_row(&निजी[0 * stride], from->ver_coefs.odd_real,  height, padding);
	fill_row(&निजी[1 * stride], from->ver_coefs.odd_imag,  height, padding);
	fill_row(&निजी[2 * stride], from->ver_coefs.even_real, height, padding);
	fill_row(&निजी[3 * stride], from->ver_coefs.even_imag, height, padding);
पूर्ण

व्योम ia_css_sdis2_horiproj_encode(
    काष्ठा sh_css_isp_sdis_hori_proj_tbl *to,
    स्थिर काष्ठा ia_css_dvs2_coefficients *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)to;
	(व्योम)from;
	(व्योम)size;
पूर्ण

व्योम ia_css_sdis2_vertproj_encode(
    काष्ठा sh_css_isp_sdis_vert_proj_tbl *to,
    स्थिर काष्ठा ia_css_dvs2_coefficients *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)to;
	(व्योम)from;
	(व्योम)size;
पूर्ण

व्योम ia_css_get_isp_dvs2_coefficients(
    काष्ठा ia_css_stream *stream,
    लघु *hor_coefs_odd_real,
    लघु *hor_coefs_odd_imag,
    लघु *hor_coefs_even_real,
    लघु *hor_coefs_even_imag,
    लघु *ver_coefs_odd_real,
    लघु *ver_coefs_odd_imag,
    लघु *ver_coefs_even_real,
    लघु *ver_coefs_even_imag)
अणु
	काष्ठा ia_css_isp_parameters *params;
	अचिन्हित पूर्णांक hor_num_3a, ver_num_3a;
	काष्ठा ia_css_binary *dvs_binary;

	IA_CSS_ENTER("void");

	निश्चित(stream);
	निश्चित(hor_coefs_odd_real);
	निश्चित(hor_coefs_odd_imag);
	निश्चित(hor_coefs_even_real);
	निश्चित(hor_coefs_even_imag);
	निश्चित(ver_coefs_odd_real);
	निश्चित(ver_coefs_odd_imag);
	निश्चित(ver_coefs_even_real);
	निश्चित(ver_coefs_even_imag);

	params = stream->isp_params_configs;

	/* Only video pipe supports DVS */
	dvs_binary = ia_css_stream_get_dvs_binary(stream);
	अगर (!dvs_binary)
		वापस;

	hor_num_3a  = dvs_binary->dis.coef.dim.width;
	ver_num_3a  = dvs_binary->dis.coef.dim.height;

	स_नकल(hor_coefs_odd_real,  params->dvs2_coefs.hor_coefs.odd_real,
	       hor_num_3a * माप(लघु));
	स_नकल(hor_coefs_odd_imag,  params->dvs2_coefs.hor_coefs.odd_imag,
	       hor_num_3a * माप(लघु));
	स_नकल(hor_coefs_even_real, params->dvs2_coefs.hor_coefs.even_real,
	       hor_num_3a * माप(लघु));
	स_नकल(hor_coefs_even_imag, params->dvs2_coefs.hor_coefs.even_imag,
	       hor_num_3a * माप(लघु));
	स_नकल(ver_coefs_odd_real,  params->dvs2_coefs.ver_coefs.odd_real,
	       ver_num_3a * माप(लघु));
	स_नकल(ver_coefs_odd_imag,  params->dvs2_coefs.ver_coefs.odd_imag,
	       ver_num_3a * माप(लघु));
	स_नकल(ver_coefs_even_real, params->dvs2_coefs.ver_coefs.even_real,
	       ver_num_3a * माप(लघु));
	स_नकल(ver_coefs_even_imag, params->dvs2_coefs.ver_coefs.even_imag,
	       ver_num_3a * माप(लघु));

	IA_CSS_LEAVE("void");
पूर्ण

व्योम ia_css_sdis2_clear_coefficients(
    काष्ठा ia_css_dvs2_coefficients *dvs2_coefs)
अणु
	dvs2_coefs->hor_coefs.odd_real  = शून्य;
	dvs2_coefs->hor_coefs.odd_imag  = शून्य;
	dvs2_coefs->hor_coefs.even_real = शून्य;
	dvs2_coefs->hor_coefs.even_imag = शून्य;
	dvs2_coefs->ver_coefs.odd_real  = शून्य;
	dvs2_coefs->ver_coefs.odd_imag  = शून्य;
	dvs2_coefs->ver_coefs.even_real = शून्य;
	dvs2_coefs->ver_coefs.even_imag = शून्य;
पूर्ण

पूर्णांक
ia_css_get_dvs2_statistics(
    काष्ठा ia_css_dvs2_statistics          *host_stats,
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
		ia_css_translate_dvs2_statistics(host_stats, map);
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
ia_css_translate_dvs2_statistics(
    काष्ठा ia_css_dvs2_statistics		   *host_stats,
    स्थिर काष्ठा ia_css_isp_dvs_statistics_map *isp_stats)
अणु
	अचिन्हित पूर्णांक size_bytes, table_width, table_size, height;
	अचिन्हित पूर्णांक src_offset = 0, dst_offset = 0;
	s32 *htemp_ptr, *vtemp_ptr;

	निश्चित(host_stats);
	निश्चित(host_stats->hor_prod.odd_real);
	निश्चित(host_stats->hor_prod.odd_imag);
	निश्चित(host_stats->hor_prod.even_real);
	निश्चित(host_stats->hor_prod.even_imag);
	निश्चित(host_stats->ver_prod.odd_real);
	निश्चित(host_stats->ver_prod.odd_imag);
	निश्चित(host_stats->ver_prod.even_real);
	निश्चित(host_stats->ver_prod.even_imag);
	निश्चित(isp_stats);
	निश्चित(isp_stats->hor_proj);
	निश्चित(isp_stats->ver_proj);

	IA_CSS_ENTER("hor_coefs.odd_real=%p, hor_coefs.odd_imag=%p, hor_coefs.even_real=%p, hor_coefs.even_imag=%p, ver_coefs.odd_real=%p, ver_coefs.odd_imag=%p, ver_coefs.even_real=%p, ver_coefs.even_imag=%p, haddr=%p, vaddr=%p",
		     host_stats->hor_prod.odd_real, host_stats->hor_prod.odd_imag,
		     host_stats->hor_prod.even_real, host_stats->hor_prod.even_imag,
		     host_stats->ver_prod.odd_real, host_stats->ver_prod.odd_imag,
		     host_stats->ver_prod.even_real, host_stats->ver_prod.even_imag,
		     isp_stats->hor_proj, isp_stats->ver_proj);

	/* Host side: reflecting the true width in bytes */
	size_bytes = host_stats->grid.aligned_width * माप(*htemp_ptr);

	/* DDR side: need to be aligned to the प्रणाली bus width */
	/* statistics table width in terms of 32-bit words*/
	table_width = CEIL_MUL(size_bytes,
			       HIVE_ISP_DDR_WORD_BYTES) / माप(*htemp_ptr);
	table_size = table_width * host_stats->grid.aligned_height;

	htemp_ptr = isp_stats->hor_proj; /* horizontal stats */
	vtemp_ptr = isp_stats->ver_proj; /* vertical stats */
	क्रम (height = 0; height < host_stats->grid.aligned_height; height++) अणु
		/* hor stats */
		स_नकल(host_stats->hor_prod.odd_real + dst_offset,
		       &htemp_ptr[0 * table_size + src_offset], size_bytes);
		स_नकल(host_stats->hor_prod.odd_imag + dst_offset,
		       &htemp_ptr[1 * table_size + src_offset], size_bytes);
		स_नकल(host_stats->hor_prod.even_real + dst_offset,
		       &htemp_ptr[2 * table_size + src_offset], size_bytes);
		स_नकल(host_stats->hor_prod.even_imag + dst_offset,
		       &htemp_ptr[3 * table_size + src_offset], size_bytes);

		/* ver stats */
		स_नकल(host_stats->ver_prod.odd_real + dst_offset,
		       &vtemp_ptr[0 * table_size + src_offset], size_bytes);
		स_नकल(host_stats->ver_prod.odd_imag + dst_offset,
		       &vtemp_ptr[1 * table_size + src_offset], size_bytes);
		स_नकल(host_stats->ver_prod.even_real + dst_offset,
		       &vtemp_ptr[2 * table_size + src_offset], size_bytes);
		स_नकल(host_stats->ver_prod.even_imag + dst_offset,
		       &vtemp_ptr[3 * table_size + src_offset], size_bytes);

		src_offset += table_width; /* aligned table width */
		dst_offset += host_stats->grid.aligned_width;
	पूर्ण

	IA_CSS_LEAVE("void");
पूर्ण

काष्ठा ia_css_isp_dvs_statistics *
ia_css_isp_dvs2_statistics_allocate(
    स्थिर काष्ठा ia_css_dvs_grid_info *grid)
अणु
	काष्ठा ia_css_isp_dvs_statistics *me;
	पूर्णांक size;

	निश्चित(grid);

	IA_CSS_ENTER("grid=%p", grid);

	अगर (!grid->enable)
		वापस शून्य;

	me = kvसुस्मृति(1, माप(*me), GFP_KERNEL);
	अगर (!me)
		जाओ err;

	/* on ISP 2 SDIS DMA model, every row of projection table width must be
	   aligned to HIVE_ISP_DDR_WORD_BYTES
	*/
	size = CEIL_MUL(माप(पूर्णांक) * grid->aligned_width, HIVE_ISP_DDR_WORD_BYTES)
	       * grid->aligned_height * IA_CSS_DVS2_NUM_COEF_TYPES;

	me->size = 2 * size;
	me->data_ptr = hmm_alloc(me->size, HMM_BO_PRIVATE, 0, शून्य, 0);
	अगर (me->data_ptr == mmgr_शून्य)
		जाओ err;
	me->hor_proj = me->data_ptr;
	me->hor_size = size;
	me->ver_proj = me->data_ptr + size;
	me->ver_size = size;

	IA_CSS_LEAVE("return=%p", me);
	वापस me;
err:
	ia_css_isp_dvs2_statistics_मुक्त(me);
	IA_CSS_LEAVE("return=%p", शून्य);

	वापस शून्य;
पूर्ण

व्योम
ia_css_isp_dvs2_statistics_मुक्त(काष्ठा ia_css_isp_dvs_statistics *me)
अणु
	अगर (me) अणु
		hmm_मुक्त(me->data_ptr);
		kvमुक्त(me);
	पूर्ण
पूर्ण

व्योम ia_css_sdis2_horicoef_debug_dtrace(
    स्थिर काष्ठा ia_css_dvs2_coefficients *config, अचिन्हित पूर्णांक level)
अणु
	(व्योम)config;
	(व्योम)level;
पूर्ण

व्योम ia_css_sdis2_vertcoef_debug_dtrace(
    स्थिर काष्ठा ia_css_dvs2_coefficients *config, अचिन्हित पूर्णांक level)
अणु
	(व्योम)config;
	(व्योम)level;
पूर्ण

व्योम ia_css_sdis2_horiproj_debug_dtrace(
    स्थिर काष्ठा ia_css_dvs2_coefficients *config, अचिन्हित पूर्णांक level)
अणु
	(व्योम)config;
	(व्योम)level;
पूर्ण

व्योम ia_css_sdis2_vertproj_debug_dtrace(
    स्थिर काष्ठा ia_css_dvs2_coefficients *config, अचिन्हित पूर्णांक level)
अणु
	(व्योम)config;
	(व्योम)level;
पूर्ण
