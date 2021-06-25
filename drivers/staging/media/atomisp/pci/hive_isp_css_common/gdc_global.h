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

#अगर_अघोषित __GDC_GLOBAL_H_INCLUDED__
#घोषणा __GDC_GLOBAL_H_INCLUDED__

#घोषणा IS_GDC_VERSION_2

#समावेश <type_support.h>
#समावेश "gdc_v2_defs.h"

/*
 * Storage addresses क्रम packed data transfer
 */
#घोषणा GDC_PARAM_ICX_LEFT_ROUNDED_IDX            0
#घोषणा GDC_PARAM_OXDIM_FLOORED_IDX               1
#घोषणा GDC_PARAM_OXDIM_LAST_IDX                  2
#घोषणा GDC_PARAM_WOIX_LAST_IDX                   3
#घोषणा GDC_PARAM_IY_TOPLEFT_IDX                  4
#घोषणा GDC_PARAM_CHUNK_CNT_IDX                   5
/*#घोषणा GDC_PARAM_ELEMENTS_PER_XMEM_ADDR_IDX    6 */		/* Derived from bpp */
#घोषणा GDC_PARAM_BPP_IDX                         6
#घोषणा GDC_PARAM_BLOCK_HEIGHT_IDX                7
/*#घोषणा GDC_PARAM_DMA_CHANNEL_STRIDE_A_IDX      8*/		/* The DMA stride == the GDC buffer stride */
#घोषणा GDC_PARAM_WOIX_IDX                        8
#घोषणा GDC_PARAM_DMA_CHANNEL_STRIDE_B_IDX        9
#घोषणा GDC_PARAM_DMA_CHANNEL_WIDTH_A_IDX        10
#घोषणा GDC_PARAM_DMA_CHANNEL_WIDTH_B_IDX        11
#घोषणा GDC_PARAM_VECTORS_PER_LINE_IN_IDX        12
#घोषणा GDC_PARAM_VECTORS_PER_LINE_OUT_IDX       13
#घोषणा GDC_PARAM_VMEM_IN_DIMY_IDX               14
#घोषणा GDC_PARAM_COMMAND_IDX                    15
#घोषणा N_GDC_PARAM                              16

/* Because of the packed parameter transfer max(params) == max(fragments) */
#घोषणा	N_GDC_FRAGMENTS		N_GDC_PARAM

/* The GDC is capable of higher पूर्णांकernal precision than the parameter data काष्ठाures */
#घोषणा HRT_GDC_COORD_SCALE_BITS	6
#घोषणा HRT_GDC_COORD_SCALE			BIT(HRT_GDC_COORD_SCALE_BITS)

प्रकार क्रमागत अणु
	GDC_CH0_ID = 0,
	N_GDC_CHANNEL_ID
पूर्ण gdc_channel_ID_t;

प्रकार क्रमागत अणु
	gdc_8_bpp  = 8,
	gdc_10_bpp = 10,
	gdc_12_bpp = 12,
	gdc_14_bpp = 14
पूर्ण gdc_bits_per_pixel_t;

प्रकार काष्ठा gdc_scale_param_mem_s अणु
	u16  params[N_GDC_PARAM];
	u16  ipx_start_array[N_GDC_PARAM];
	u16  ibuf_offset[N_GDC_PARAM];
	u16  obuf_offset[N_GDC_PARAM];
पूर्ण gdc_scale_param_mem_t;

प्रकार काष्ठा gdc_warp_param_mem_s अणु
	u32      origin_x;
	u32      origin_y;
	u32      in_addr_offset;
	u32      in_block_width;
	u32      in_block_height;
	u32      p0_x;
	u32      p0_y;
	u32      p1_x;
	u32      p1_y;
	u32      p2_x;
	u32      p2_y;
	u32      p3_x;
	u32      p3_y;
	u32      padding[3];
पूर्ण gdc_warp_param_mem_t;

#पूर्ण_अगर /* __GDC_GLOBAL_H_INCLUDED__ */
