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

#अगर_अघोषित _SH_CSS_PARAMS_DVS_H_
#घोषणा _SH_CSS_PARAMS_DVS_H_

#समावेश <math_support.h>
#समावेश <ia_css_types.h>
#समावेश <sh_css_dvs_info.h>
#समावेश "gdc_global.h" /* gdc_warp_param_mem_t */

#घोषणा DVS_ENV_MIN_X (12)
#घोषणा DVS_ENV_MIN_Y (12)

#घोषणा DVS_BLOCKDIM_X (64)        /* X block height*/
#घोषणा DVS_BLOCKDIM_Y_LUMA (64)   /* Y block height*/
#घोषणा DVS_BLOCKDIM_Y_CHROMA (32) /* UV height block size is half the Y block height*/

/* ISP2400 */
/* horizontal 64x64 blocks round up to DVS_BLOCKDIM_X, make even */
#घोषणा DVS_NUM_BLOCKS_X(X)		(CEIL_MUL(CEIL_DIV((X), DVS_BLOCKDIM_X), 2))

/* ISP2400 */
/* vertical   64x64 blocks round up to DVS_BLOCKDIM_Y */
#घोषणा DVS_NUM_BLOCKS_Y(X)		(CEIL_DIV((X), DVS_BLOCKDIM_Y_LUMA))
#घोषणा DVS_NUM_BLOCKS_X_CHROMA(X)	(CEIL_DIV((X), DVS_BLOCKDIM_X))
#घोषणा DVS_NUM_BLOCKS_Y_CHROMA(X)	(CEIL_DIV((X), DVS_BLOCKDIM_Y_CHROMA))

#घोषणा DVS_TABLE_IN_BLOCKDIM_X_LUMA(X)	(DVS_NUM_BLOCKS_X(X) + 1)  /* N blocks have N + 1 set of coords */
#घोषणा DVS_TABLE_IN_BLOCKDIM_X_CHROMA(X)   (DVS_NUM_BLOCKS_X_CHROMA(X) + 1)
#घोषणा DVS_TABLE_IN_BLOCKDIM_Y_LUMA(X)		(DVS_NUM_BLOCKS_Y(X) + 1)
#घोषणा DVS_TABLE_IN_BLOCKDIM_Y_CHROMA(X)	(DVS_NUM_BLOCKS_Y_CHROMA(X) + 1)

#घोषणा DVS_ENVELOPE_X(X) (((X) == 0) ? (DVS_ENV_MIN_X) : (X))
#घोषणा DVS_ENVELOPE_Y(X) (((X) == 0) ? (DVS_ENV_MIN_Y) : (X))

#घोषणा DVS_COORD_FRAC_BITS (10)

/* ISP2400 */
#घोषणा DVS_INPUT_BYTES_PER_PIXEL (1)

#घोषणा XMEM_ALIGN_LOG2 (5)

#घोषणा DVS_6AXIS_COORDS_ELEMS CEIL_MUL(माप(gdc_warp_param_mem_t) \
					, HIVE_ISP_DDR_WORD_BYTES)

/* currently we only support two output with the same resolution, output 0 is th शेष one. */
#घोषणा DVS_6AXIS_BYTES(binary) \
	(DVS_6AXIS_COORDS_ELEMS \
	* DVS_NUM_BLOCKS_X((binary)->out_frame_info[0].res.width) \
	* DVS_NUM_BLOCKS_Y((binary)->out_frame_info[0].res.height))

/*
 * ISP2400:
 * Bilinear पूर्णांकerpolation (HRT_GDC_BLI_MODE) is the supported method currently.
 * Bicubic पूर्णांकerpolation (HRT_GDC_BCI_MODE) is not supported yet */
#घोषणा DVS_GDC_INTERP_METHOD HRT_GDC_BLI_MODE

काष्ठा ia_css_dvs_6axis_config *
generate_dvs_6axis_table(स्थिर काष्ठा ia_css_resolution	*frame_res,
			 स्थिर काष्ठा ia_css_resolution *dvs_offset);

काष्ठा ia_css_dvs_6axis_config *
generate_dvs_6axis_table_from_config(काष्ठा ia_css_dvs_6axis_config
				     *dvs_config_src);

व्योम
मुक्त_dvs_6axis_table(काष्ठा ia_css_dvs_6axis_config  **dvs_6axis_config);

व्योम
copy_dvs_6axis_table(काष्ठा ia_css_dvs_6axis_config *dvs_config_dst,
		     स्थिर काष्ठा ia_css_dvs_6axis_config *dvs_config_src);

#पूर्ण_अगर
