<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/**
Support क्रम Intel Camera Imaging ISP subप्रणाली.
Copyright (c) 2010 - 2015, Intel Corporation.

This program is मुक्त software; you can redistribute it and/or modअगरy it
under the terms and conditions of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
more details.
*/

#अगर_अघोषित __SH_CSS_DVS_INFO_H__
#घोषणा __SH_CSS_DVS_INFO_H__

#समावेश <math_support.h>

/* horizontal 64x64 blocks round up to DVS_BLOCKDIM_X, make even */
#घोषणा DVS_NUM_BLOCKS_X(X)		(CEIL_MUL(CEIL_DIV((X), DVS_BLOCKDIM_X), 2))

/* vertical   64x64 blocks round up to DVS_BLOCKDIM_Y */
#घोषणा DVS_NUM_BLOCKS_Y(X)		(CEIL_DIV((X), DVS_BLOCKDIM_Y_LUMA))

/* Bilinear पूर्णांकerpolation (HRT_GDC_BLI_MODE) is the supported method currently.
 * Bicubic पूर्णांकerpolation (HRT_GDC_BCI_MODE) is not supported yet */
#घोषणा DVS_GDC_INTERP_METHOD HRT_GDC_BLI_MODE

#घोषणा DVS_INPUT_BYTES_PER_PIXEL (1)

#घोषणा DVS_NUM_BLOCKS_X_CHROMA(X)	(CEIL_DIV((X), DVS_BLOCKDIM_X))

#घोषणा DVS_NUM_BLOCKS_Y_CHROMA(X)	(CEIL_DIV((X), DVS_BLOCKDIM_Y_CHROMA))

#पूर्ण_अगर /* __SH_CSS_DVS_INFO_H__ */
