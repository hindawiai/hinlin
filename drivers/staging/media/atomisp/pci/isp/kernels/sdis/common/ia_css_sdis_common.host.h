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

#अगर_अघोषित _IA_CSS_SDIS_COMMON_HOST_H
#घोषणा _IA_CSS_SDIS_COMMON_HOST_H

#घोषणा ISP_MAX_SDIS_HOR_PROJ_NUM_ISP \
	__ISP_SDIS_HOR_PROJ_NUM_ISP(ISP_MAX_INTERNAL_WIDTH, ISP_MAX_INTERNAL_HEIGHT, \
		SH_CSS_DIS_DECI_FACTOR_LOG2, ISP_PIPE_VERSION)
#घोषणा ISP_MAX_SDIS_VER_PROJ_NUM_ISP \
	__ISP_SDIS_VER_PROJ_NUM_ISP(ISP_MAX_INTERNAL_WIDTH, \
		SH_CSS_DIS_DECI_FACTOR_LOG2)

#घोषणा _ISP_SDIS_HOR_COEF_NUM_VECS \
	__ISP_SDIS_HOR_COEF_NUM_VECS(ISP_INTERNAL_WIDTH)
#घोषणा ISP_MAX_SDIS_HOR_COEF_NUM_VECS \
	__ISP_SDIS_HOR_COEF_NUM_VECS(ISP_MAX_INTERNAL_WIDTH)
#घोषणा ISP_MAX_SDIS_VER_COEF_NUM_VECS \
	__ISP_SDIS_VER_COEF_NUM_VECS(ISP_MAX_INTERNAL_HEIGHT)

/* SDIS Coefficients: */
/* The ISP uses vectors to store the coefficients, so we round
   the number of coefficients up to vectors. */
#घोषणा __ISP_SDIS_HOR_COEF_NUM_VECS(in_width)  _ISP_VECS(_ISP_BQS(in_width))
#घोषणा __ISP_SDIS_VER_COEF_NUM_VECS(in_height) _ISP_VECS(_ISP_BQS(in_height))

/* SDIS Projections:
 * SDIS1: Horizontal projections are calculated क्रम each line.
 * Vertical projections are calculated क्रम each column.
 * SDIS2: Projections are calculated क्रम each grid cell.
 * Grid cells that करो not fall completely within the image are not
 * valid. The host needs to use the bigger one क्रम the stride but
 * should only वापस the valid ones to the 3A. */
#घोषणा __ISP_SDIS_HOR_PROJ_NUM_ISP(in_width, in_height, deci_factor_log2, \
	isp_pipe_version) \
	((isp_pipe_version == 1) ? \
		CEIL_SHIFT(_ISP_BQS(in_height), deci_factor_log2) : \
		CEIL_SHIFT(_ISP_BQS(in_width), deci_factor_log2))

#घोषणा __ISP_SDIS_VER_PROJ_NUM_ISP(in_width, deci_factor_log2) \
	CEIL_SHIFT(_ISP_BQS(in_width), deci_factor_log2)

#घोषणा SH_CSS_DIS_VER_NUM_COEF_TYPES(b) \
  (((b)->info->sp.pipeline.isp_pipe_version == 2) ? \
	IA_CSS_DVS2_NUM_COEF_TYPES : \
	IA_CSS_DVS_NUM_COEF_TYPES)

#अगर_अघोषित PIPE_GENERATION
#अगर defined(__ISP) || defined(MK_FIRMWARE)

/* Array cannot be 2-dimensional, since driver ddr allocation करोes not know stride */
काष्ठा sh_css_isp_sdis_hori_proj_tbl अणु
	s32 tbl[ISP_DVS_NUM_COEF_TYPES * ISP_MAX_SDIS_HOR_PROJ_NUM_ISP];
#अगर DVS2_PROJ_MARGIN > 0
	s32 margin[DVS2_PROJ_MARGIN];
#पूर्ण_अगर
पूर्ण;

काष्ठा sh_css_isp_sdis_vert_proj_tbl अणु
	s32 tbl[ISP_DVS_NUM_COEF_TYPES * ISP_MAX_SDIS_VER_PROJ_NUM_ISP];
#अगर DVS2_PROJ_MARGIN > 0
	s32 margin[DVS2_PROJ_MARGIN];
#पूर्ण_अगर
पूर्ण;

काष्ठा sh_css_isp_sdis_hori_coef_tbl अणु
	VMEM_ARRAY(tbl[ISP_DVS_NUM_COEF_TYPES],
		   ISP_MAX_SDIS_HOR_COEF_NUM_VECS * ISP_NWAY);
पूर्ण;

काष्ठा sh_css_isp_sdis_vert_coef_tbl अणु
	VMEM_ARRAY(tbl[ISP_DVS_NUM_COEF_TYPES],
		   ISP_MAX_SDIS_VER_COEF_NUM_VECS * ISP_NWAY);
पूर्ण;

#पूर्ण_अगर /* defined(__ISP) || defined (MK_FIRMWARE) */
#पूर्ण_अगर /* PIPE_GENERATION */

#अगर_अघोषित PIPE_GENERATION
काष्ठा s_sdis_config अणु
	अचिन्हित पूर्णांक horicoef_vectors;
	अचिन्हित पूर्णांक vertcoef_vectors;
	अचिन्हित पूर्णांक horiproj_num;
	अचिन्हित पूर्णांक vertproj_num;
पूर्ण;

बाह्य काष्ठा s_sdis_config sdis_config;
#पूर्ण_अगर

#पूर्ण_अगर /* _IA_CSS_SDIS_COMMON_HOST_H */
