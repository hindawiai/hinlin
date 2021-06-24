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

#अगर_अघोषित _PixelGen_SysBlock_defs_h
#घोषणा _PixelGen_SysBlock_defs_h

/* Parematers and User_Parameters क्रम HSS */
#घोषणा _PXG_PPC                       Ppc
#घोषणा _PXG_PIXEL_BITS                PixelWidth
#घोषणा _PXG_MAX_NOF_SID               MaxNofSids
#घोषणा _PXG_DATA_BITS                 DataWidth
#घोषणा _PXG_CNT_BITS                  CntWidth
#घोषणा _PXG_FIFODEPTH                 FअगरoDepth
#घोषणा _PXG_DBG                       Dbg_device_not_included

/* ID's and Address */
#घोषणा _PXG_ADRRESS_ALIGN_REG         4

#घोषणा _PXG_COM_ENABLE_REG_IDX        0
#घोषणा _PXG_PRBS_RSTVAL_REG0_IDX      1
#घोषणा _PXG_PRBS_RSTVAL_REG1_IDX      2
#घोषणा _PXG_SYNG_SID_REG_IDX          3
#घोषणा _PXG_SYNG_FREE_RUN_REG_IDX     4
#घोषणा _PXG_SYNG_PAUSE_REG_IDX        5
#घोषणा _PXG_SYNG_NOF_FRAME_REG_IDX    6
#घोषणा _PXG_SYNG_NOF_PIXEL_REG_IDX    7
#घोषणा _PXG_SYNG_NOF_LINE_REG_IDX     8
#घोषणा _PXG_SYNG_HBLANK_CYC_REG_IDX   9
#घोषणा _PXG_SYNG_VBLANK_CYC_REG_IDX  10
#घोषणा _PXG_SYNG_STAT_HCNT_REG_IDX   11
#घोषणा _PXG_SYNG_STAT_VCNT_REG_IDX   12
#घोषणा _PXG_SYNG_STAT_FCNT_REG_IDX   13
#घोषणा _PXG_SYNG_STAT_DONE_REG_IDX   14
#घोषणा _PXG_TPG_MODE_REG_IDX         15
#घोषणा _PXG_TPG_HCNT_MASK_REG_IDX    16
#घोषणा _PXG_TPG_VCNT_MASK_REG_IDX    17
#घोषणा _PXG_TPG_XYCNT_MASK_REG_IDX   18
#घोषणा _PXG_TPG_HCNT_DELTA_REG_IDX   19
#घोषणा _PXG_TPG_VCNT_DELTA_REG_IDX   20
#घोषणा _PXG_TPG_R1_REG_IDX           21
#घोषणा _PXG_TPG_G1_REG_IDX           22
#घोषणा _PXG_TPG_B1_REG_IDX           23
#घोषणा _PXG_TPG_R2_REG_IDX           24
#घोषणा _PXG_TPG_G2_REG_IDX           25
#घोषणा _PXG_TPG_B2_REG_IDX           26
/* */
#घोषणा _PXG_SYNG_PAUSE_CYCLES        0
/* Subblock ID's */
#घोषणा _PXG_DISABLE_IDX              0
#घोषणा _PXG_PRBS_IDX                 0
#घोषणा _PXG_TPG_IDX                  1
#घोषणा _PXG_SYNG_IDX                 2
#घोषणा _PXG_SMUX_IDX                 3
/* Register Widths */
#घोषणा _PXG_COM_ENABLE_REG_WIDTH     2
#घोषणा _PXG_COM_SRST_REG_WIDTH       4
#घोषणा _PXG_PRBS_RSTVAL_REG0_WIDTH  31
#घोषणा _PXG_PRBS_RSTVAL_REG1_WIDTH  31

#घोषणा _PXG_SYNG_SID_REG_WIDTH        3

#घोषणा _PXG_SYNG_FREE_RUN_REG_WIDTH   1
#घोषणा _PXG_SYNG_PAUSE_REG_WIDTH      1
/*
#घोषणा _PXG_SYNG_NOF_FRAME_REG_WIDTH  <sync_gen_cnt_width>
#घोषणा _PXG_SYNG_NOF_PIXEL_REG_WIDTH  <sync_gen_cnt_width>
#घोषणा _PXG_SYNG_NOF_LINE_REG_WIDTH   <sync_gen_cnt_width>
#घोषणा _PXG_SYNG_HBLANK_CYC_REG_WIDTH <sync_gen_cnt_width>
#घोषणा _PXG_SYNG_VBLANK_CYC_REG_WIDTH <sync_gen_cnt_width>
#घोषणा _PXG_SYNG_STAT_HCNT_REG_WIDTH  <sync_gen_cnt_width>
#घोषणा _PXG_SYNG_STAT_VCNT_REG_WIDTH  <sync_gen_cnt_width>
#घोषणा _PXG_SYNG_STAT_FCNT_REG_WIDTH  <sync_gen_cnt_width>
*/
#घोषणा _PXG_SYNG_STAT_DONE_REG_WIDTH  1
#घोषणा _PXG_TPG_MODE_REG_WIDTH        2
/*
#घोषणा _PXG_TPG_HCNT_MASK_REG_WIDTH   <sync_gen_cnt_width>
#घोषणा _PXG_TPG_VCNT_MASK_REG_WIDTH   <sync_gen_cnt_width>
#घोषणा _PXG_TPG_XYCNT_MASK_REG_WIDTH  <pixle_width>
*/
#घोषणा _PXG_TPG_HCNT_DELTA_REG_WIDTH  4
#घोषणा _PXG_TPG_VCNT_DELTA_REG_WIDTH  4
/*
#घोषणा _PXG_TPG_R1_REG_WIDTH          <pixle_width>
#घोषणा _PXG_TPG_G1_REG_WIDTH          <pixle_width>
#घोषणा _PXG_TPG_B1_REG_WIDTH          <pixle_width>
#घोषणा _PXG_TPG_R2_REG_WIDTH          <pixle_width>
#घोषणा _PXG_TPG_G2_REG_WIDTH          <pixle_width>
#घोषणा _PXG_TPG_B2_REG_WIDTH          <pixle_width>
*/
#घोषणा _PXG_FIFO_DEPTH                2
/* MISC */
#घोषणा _PXG_ENABLE_REG_VAL            1
#घोषणा _PXG_PRBS_ENABLE_REG_VAL       1
#घोषणा _PXG_TPG_ENABLE_REG_VAL        2
#घोषणा _PXG_SYNG_ENABLE_REG_VAL       4
#घोषणा _PXG_FIFO_ENABLE_REG_VAL       8
#घोषणा _PXG_PXL_BITS                 14
#घोषणा _PXG_INVALID_FLAG              0xDEADBEEF
#घोषणा _PXG_CAFE_FLAG                 0xCAFEBABE

#पूर्ण_अगर /* _PixelGen_SysBlock_defs_h */
