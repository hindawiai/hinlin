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

#अगर_अघोषित _input_selector_defs_h
#घोषणा _input_selector_defs_h

#अगर_अघोषित HIVE_ISP_ISEL_SEL_BITS
#घोषणा HIVE_ISP_ISEL_SEL_BITS                                  2
#पूर्ण_अगर

#अगर_अघोषित HIVE_ISP_CH_ID_BITS
#घोषणा HIVE_ISP_CH_ID_BITS                                     2
#पूर्ण_अगर

#अगर_अघोषित HIVE_ISP_FMT_TYPE_BITS
#घोषणा HIVE_ISP_FMT_TYPE_BITS                                  5
#पूर्ण_अगर

/* gp_रेजिस्टर रेजिस्टर id's -- Outमाला_दो */
#घोषणा HIVE_ISEL_GP_REGS_SYNCGEN_ENABLE_IDX                    0
#घोषणा HIVE_ISEL_GP_REGS_SYNCGEN_FREE_RUNNING_IDX              1
#घोषणा HIVE_ISEL_GP_REGS_SYNCGEN_PAUSE_IDX                     2
#घोषणा HIVE_ISEL_GP_REGS_SYNCGEN_NR_FRAMES_IDX                 3
#घोषणा HIVE_ISEL_GP_REGS_SYNCGEN_NR_PIX_IDX                    4
#घोषणा HIVE_ISEL_GP_REGS_SYNCGEN_NR_LINES_IDX                  5
#घोषणा HIVE_ISEL_GP_REGS_SYNCGEN_HBLANK_CYCLES_IDX             6
#घोषणा HIVE_ISEL_GP_REGS_SYNCGEN_VBLANK_CYCLES_IDX             7

#घोषणा HIVE_ISEL_GP_REGS_SOF_IDX                               8
#घोषणा HIVE_ISEL_GP_REGS_खातापूर्ण_IDX                               9
#घोषणा HIVE_ISEL_GP_REGS_SOL_IDX                              10
#घोषणा HIVE_ISEL_GP_REGS_EOL_IDX                              11

#घोषणा HIVE_ISEL_GP_REGS_PRBS_ENABLE                          12
#घोषणा HIVE_ISEL_GP_REGS_PRBS_ENABLE_PORT_B                   13
#घोषणा HIVE_ISEL_GP_REGS_PRBS_LFSR_RESET_VALUE                14

#घोषणा HIVE_ISEL_GP_REGS_TPG_ENABLE                           15
#घोषणा HIVE_ISEL_GP_REGS_TPG_ENABLE_PORT_B                    16
#घोषणा HIVE_ISEL_GP_REGS_TPG_HOR_CNT_MASK_IDX                 17
#घोषणा HIVE_ISEL_GP_REGS_TPG_VER_CNT_MASK_IDX                 18
#घोषणा HIVE_ISEL_GP_REGS_TPG_XY_CNT_MASK_IDX                  19
#घोषणा HIVE_ISEL_GP_REGS_TPG_HOR_CNT_DELTA_IDX                20
#घोषणा HIVE_ISEL_GP_REGS_TPG_VER_CNT_DELTA_IDX                21
#घोषणा HIVE_ISEL_GP_REGS_TPG_MODE_IDX                         22
#घोषणा HIVE_ISEL_GP_REGS_TPG_R1_IDX                           23
#घोषणा HIVE_ISEL_GP_REGS_TPG_G1_IDX                           24
#घोषणा HIVE_ISEL_GP_REGS_TPG_B1_IDX                           25
#घोषणा HIVE_ISEL_GP_REGS_TPG_R2_IDX                           26
#घोषणा HIVE_ISEL_GP_REGS_TPG_G2_IDX                           27
#घोषणा HIVE_ISEL_GP_REGS_TPG_B2_IDX                           28

#घोषणा HIVE_ISEL_GP_REGS_CH_ID_IDX                            29
#घोषणा HIVE_ISEL_GP_REGS_FMT_TYPE_IDX                         30
#घोषणा HIVE_ISEL_GP_REGS_DATA_SEL_IDX                         31
#घोषणा HIVE_ISEL_GP_REGS_SBAND_SEL_IDX                        32
#घोषणा HIVE_ISEL_GP_REGS_SYNC_SEL_IDX                         33
#घोषणा HIVE_ISEL_GP_REGS_SRST_IDX                             37

#घोषणा HIVE_ISEL_GP_REGS_SRST_SYNCGEN_BIT                      0
#घोषणा HIVE_ISEL_GP_REGS_SRST_PRBS_BIT                         1
#घोषणा HIVE_ISEL_GP_REGS_SRST_TPG_BIT                          2
#घोषणा HIVE_ISEL_GP_REGS_SRST_FIFO_BIT                         3

/* gp_रेजिस्टर रेजिस्टर id's -- Inमाला_दो   */
#घोषणा HIVE_ISEL_GP_REGS_SYNCGEN_HOR_CNT_IDX                  34
#घोषणा HIVE_ISEL_GP_REGS_SYNCGEN_VER_CNT_IDX                  35
#घोषणा HIVE_ISEL_GP_REGS_SYNCGEN_FRAMES_CNT_IDX               36

/* irq sources isel irq controller */
#घोषणा HIVE_ISEL_IRQ_SYNC_GEN_SOF_BIT_ID                       0
#घोषणा HIVE_ISEL_IRQ_SYNC_GEN_खातापूर्ण_BIT_ID                       1
#घोषणा HIVE_ISEL_IRQ_SYNC_GEN_SOL_BIT_ID                       2
#घोषणा HIVE_ISEL_IRQ_SYNC_GEN_EOL_BIT_ID                       3
#घोषणा HIVE_ISEL_IRQ_NUM_IRQS                                  4

#पूर्ण_अगर /* _input_selector_defs_h */
