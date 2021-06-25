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

#अगर_अघोषित __IA_CSS_SDIS2_HOST_H
#घोषणा __IA_CSS_SDIS2_HOST_H

#समावेश "ia_css_sdis2_types.h"
#समावेश "ia_css_binary.h"
#समावेश "ia_css_stream.h"
#समावेश "sh_css_params.h"

बाह्य स्थिर काष्ठा ia_css_dvs2_coefficients शेष_sdis2_config;

/* Opaque here, since size is binary dependent. */
काष्ठा sh_css_isp_sdis_hori_coef_tbl;
काष्ठा sh_css_isp_sdis_vert_coef_tbl;
काष्ठा sh_css_isp_sdis_hori_proj_tbl;
काष्ठा sh_css_isp_sdis_vert_proj_tbl;

व्योम ia_css_sdis2_horicoef_vmem_encode(
    काष्ठा sh_css_isp_sdis_hori_coef_tbl *to,
    स्थिर काष्ठा ia_css_dvs2_coefficients *from,
    अचिन्हित पूर्णांक size);

व्योम ia_css_sdis2_vertcoef_vmem_encode(
    काष्ठा sh_css_isp_sdis_vert_coef_tbl *to,
    स्थिर काष्ठा ia_css_dvs2_coefficients *from,
    अचिन्हित पूर्णांक size);

व्योम ia_css_sdis2_horiproj_encode(
    काष्ठा sh_css_isp_sdis_hori_proj_tbl *to,
    स्थिर काष्ठा ia_css_dvs2_coefficients *from,
    अचिन्हित पूर्णांक size);

व्योम ia_css_sdis2_vertproj_encode(
    काष्ठा sh_css_isp_sdis_vert_proj_tbl *to,
    स्थिर काष्ठा ia_css_dvs2_coefficients *from,
    अचिन्हित पूर्णांक size);

व्योम ia_css_get_isp_dvs2_coefficients(
    काष्ठा ia_css_stream *stream,
    लघु *hor_coefs_odd_real,
    लघु *hor_coefs_odd_imag,
    लघु *hor_coefs_even_real,
    लघु *hor_coefs_even_imag,
    लघु *ver_coefs_odd_real,
    लघु *ver_coefs_odd_imag,
    लघु *ver_coefs_even_real,
    लघु *ver_coefs_even_imag);

व्योम ia_css_sdis2_clear_coefficients(
    काष्ठा ia_css_dvs2_coefficients *dvs2_coefs);

पूर्णांक
ia_css_get_dvs2_statistics(
    काष्ठा ia_css_dvs2_statistics	       *host_stats,
    स्थिर काष्ठा ia_css_isp_dvs_statistics *isp_stats);

व्योम
ia_css_translate_dvs2_statistics(
    काष्ठा ia_css_dvs2_statistics              *host_stats,
    स्थिर काष्ठा ia_css_isp_dvs_statistics_map *isp_stats);

काष्ठा ia_css_isp_dvs_statistics *
ia_css_isp_dvs2_statistics_allocate(
    स्थिर काष्ठा ia_css_dvs_grid_info *grid);

व्योम
ia_css_isp_dvs2_statistics_मुक्त(
    काष्ठा ia_css_isp_dvs_statistics *me);

व्योम ia_css_sdis2_horicoef_debug_dtrace(
    स्थिर काष्ठा ia_css_dvs2_coefficients *config, अचिन्हित पूर्णांक level);

व्योम ia_css_sdis2_vertcoef_debug_dtrace(
    स्थिर काष्ठा ia_css_dvs2_coefficients *config, अचिन्हित पूर्णांक level);

व्योम ia_css_sdis2_horiproj_debug_dtrace(
    स्थिर काष्ठा ia_css_dvs2_coefficients *config, अचिन्हित पूर्णांक level);

व्योम ia_css_sdis2_vertproj_debug_dtrace(
    स्थिर काष्ठा ia_css_dvs2_coefficients *config, अचिन्हित पूर्णांक level);

#पूर्ण_अगर /* __IA_CSS_SDIS2_HOST_H */
