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

#अगर_अघोषित __IA_CSS_SDIS_HOST_H
#घोषणा __IA_CSS_SDIS_HOST_H

#समावेश "ia_css_sdis_types.h"
#समावेश "ia_css_binary.h"
#समावेश "ia_css_stream.h"
#समावेश "sh_css_params.h"

बाह्य स्थिर काष्ठा ia_css_dvs_coefficients शेष_sdis_config;

/* Opaque here, since size is binary dependent. */
काष्ठा sh_css_isp_sdis_hori_coef_tbl;
काष्ठा sh_css_isp_sdis_vert_coef_tbl;
काष्ठा sh_css_isp_sdis_hori_proj_tbl;
काष्ठा sh_css_isp_sdis_vert_proj_tbl;

व्योम ia_css_sdis_horicoef_vmem_encode(
    काष्ठा sh_css_isp_sdis_hori_coef_tbl *to,
    स्थिर काष्ठा ia_css_dvs_coefficients *from,
    अचिन्हित पूर्णांक size);

व्योम ia_css_sdis_vertcoef_vmem_encode(
    काष्ठा sh_css_isp_sdis_vert_coef_tbl *to,
    स्थिर काष्ठा ia_css_dvs_coefficients *from,
    अचिन्हित पूर्णांक size);

व्योम ia_css_sdis_horiproj_encode(
    काष्ठा sh_css_isp_sdis_hori_proj_tbl *to,
    स्थिर काष्ठा ia_css_dvs_coefficients *from,
    अचिन्हित पूर्णांक size);

व्योम ia_css_sdis_vertproj_encode(
    काष्ठा sh_css_isp_sdis_vert_proj_tbl *to,
    स्थिर काष्ठा ia_css_dvs_coefficients *from,
    अचिन्हित पूर्णांक size);

व्योम ia_css_get_isp_dis_coefficients(
    काष्ठा ia_css_stream *stream,
    लघु *horizontal_coefficients,
    लघु *vertical_coefficients);

पूर्णांक
ia_css_get_dvs_statistics(
    काष्ठा ia_css_dvs_statistics	       *host_stats,
    स्थिर काष्ठा ia_css_isp_dvs_statistics *isp_stats);

व्योम
ia_css_translate_dvs_statistics(
    काष्ठा ia_css_dvs_statistics               *host_stats,
    स्थिर काष्ठा ia_css_isp_dvs_statistics_map *isp_stats);

काष्ठा ia_css_isp_dvs_statistics *
ia_css_isp_dvs_statistics_allocate(
    स्थिर काष्ठा ia_css_dvs_grid_info *grid);

व्योम
ia_css_isp_dvs_statistics_मुक्त(
    काष्ठा ia_css_isp_dvs_statistics *me);

माप_प्रकार ia_css_sdis_hor_coef_tbl_bytes(स्थिर काष्ठा ia_css_binary *binary);
माप_प्रकार ia_css_sdis_ver_coef_tbl_bytes(स्थिर काष्ठा ia_css_binary *binary);

व्योम
ia_css_sdis_init_info(
    काष्ठा ia_css_sdis_info *dis,
    अचिन्हित पूर्णांक sc_3a_dis_width,
    अचिन्हित पूर्णांक sc_3a_dis_padded_width,
    अचिन्हित पूर्णांक sc_3a_dis_height,
    अचिन्हित पूर्णांक isp_pipe_version,
    अचिन्हित पूर्णांक enabled);

व्योम ia_css_sdis_clear_coefficients(
    काष्ठा ia_css_dvs_coefficients *dvs_coefs);

व्योम ia_css_sdis_horicoef_debug_dtrace(
    स्थिर काष्ठा ia_css_dvs_coefficients *config, अचिन्हित पूर्णांक level);

व्योम ia_css_sdis_vertcoef_debug_dtrace(
    स्थिर काष्ठा ia_css_dvs_coefficients *config, अचिन्हित पूर्णांक level);

व्योम ia_css_sdis_horiproj_debug_dtrace(
    स्थिर काष्ठा ia_css_dvs_coefficients *config, अचिन्हित पूर्णांक level);

व्योम ia_css_sdis_vertproj_debug_dtrace(
    स्थिर काष्ठा ia_css_dvs_coefficients *config, अचिन्हित पूर्णांक level);

#पूर्ण_अगर /* __IA_CSS_SDIS_HOST_H */
