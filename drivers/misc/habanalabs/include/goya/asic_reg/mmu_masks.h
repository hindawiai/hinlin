<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright 2016-2018 HabanaLअसल, Ltd.
 * All Rights Reserved.
 *
 */

/************************************
 ** This is an स्वतः-generated file **
 **       DO NOT EDIT BELOW        **
 ************************************/

#अगर_अघोषित ASIC_REG_MMU_MASKS_H_
#घोषणा ASIC_REG_MMU_MASKS_H_

/*
 *****************************************
 *   MMU (Prototype: MMU)
 *****************************************
 */

/* MMU_INPUT_FIFO_THRESHOLD */
#घोषणा MMU_INPUT_FIFO_THRESHOLD_PCI_SHIFT                           0
#घोषणा MMU_INPUT_FIFO_THRESHOLD_PCI_MASK                            0x7
#घोषणा MMU_INPUT_FIFO_THRESHOLD_PSOC_SHIFT                          4
#घोषणा MMU_INPUT_FIFO_THRESHOLD_PSOC_MASK                           0x70
#घोषणा MMU_INPUT_FIFO_THRESHOLD_DMA_SHIFT                           8
#घोषणा MMU_INPUT_FIFO_THRESHOLD_DMA_MASK                            0x700
#घोषणा MMU_INPUT_FIFO_THRESHOLD_CPU_SHIFT                           12
#घोषणा MMU_INPUT_FIFO_THRESHOLD_CPU_MASK                            0x7000
#घोषणा MMU_INPUT_FIFO_THRESHOLD_MME_SHIFT                           16
#घोषणा MMU_INPUT_FIFO_THRESHOLD_MME_MASK                            0x70000
#घोषणा MMU_INPUT_FIFO_THRESHOLD_TPC_SHIFT                           20
#घोषणा MMU_INPUT_FIFO_THRESHOLD_TPC_MASK                            0x700000
#घोषणा MMU_INPUT_FIFO_THRESHOLD_OTHER_SHIFT                         24
#घोषणा MMU_INPUT_FIFO_THRESHOLD_OTHER_MASK                          0x7000000

/* MMU_MMU_ENABLE */
#घोषणा MMU_MMU_ENABLE_R_SHIFT                                       0
#घोषणा MMU_MMU_ENABLE_R_MASK                                        0x1

/* MMU_FORCE_ORDERING */
#घोषणा MMU_FORCE_ORDERING_DMA_WEAK_ORDERING_SHIFT                   0
#घोषणा MMU_FORCE_ORDERING_DMA_WEAK_ORDERING_MASK                    0x1
#घोषणा MMU_FORCE_ORDERING_PSOC_WEAK_ORDERING_SHIFT                  1
#घोषणा MMU_FORCE_ORDERING_PSOC_WEAK_ORDERING_MASK                   0x2
#घोषणा MMU_FORCE_ORDERING_PCI_WEAK_ORDERING_SHIFT                   2
#घोषणा MMU_FORCE_ORDERING_PCI_WEAK_ORDERING_MASK                    0x4
#घोषणा MMU_FORCE_ORDERING_CPU_WEAK_ORDERING_SHIFT                   3
#घोषणा MMU_FORCE_ORDERING_CPU_WEAK_ORDERING_MASK                    0x8
#घोषणा MMU_FORCE_ORDERING_MME_WEAK_ORDERING_SHIFT                   4
#घोषणा MMU_FORCE_ORDERING_MME_WEAK_ORDERING_MASK                    0x10
#घोषणा MMU_FORCE_ORDERING_TPC_WEAK_ORDERING_SHIFT                   5
#घोषणा MMU_FORCE_ORDERING_TPC_WEAK_ORDERING_MASK                    0x20
#घोषणा MMU_FORCE_ORDERING_DEFAULT_WEAK_ORDERING_SHIFT               6
#घोषणा MMU_FORCE_ORDERING_DEFAULT_WEAK_ORDERING_MASK                0x40
#घोषणा MMU_FORCE_ORDERING_DMA_STRONG_ORDERING_SHIFT                 8
#घोषणा MMU_FORCE_ORDERING_DMA_STRONG_ORDERING_MASK                  0x100
#घोषणा MMU_FORCE_ORDERING_PSOC_STRONG_ORDERING_SHIFT                9
#घोषणा MMU_FORCE_ORDERING_PSOC_STRONG_ORDERING_MASK                 0x200
#घोषणा MMU_FORCE_ORDERING_PCI_STRONG_ORDERING_SHIFT                 10
#घोषणा MMU_FORCE_ORDERING_PCI_STRONG_ORDERING_MASK                  0x400
#घोषणा MMU_FORCE_ORDERING_CPU_STRONG_ORDERING_SHIFT                 11
#घोषणा MMU_FORCE_ORDERING_CPU_STRONG_ORDERING_MASK                  0x800
#घोषणा MMU_FORCE_ORDERING_MME_STRONG_ORDERING_SHIFT                 12
#घोषणा MMU_FORCE_ORDERING_MME_STRONG_ORDERING_MASK                  0x1000
#घोषणा MMU_FORCE_ORDERING_TPC_STRONG_ORDERING_SHIFT                 13
#घोषणा MMU_FORCE_ORDERING_TPC_STRONG_ORDERING_MASK                  0x2000
#घोषणा MMU_FORCE_ORDERING_DEFAULT_STRONG_ORDERING_SHIFT             14
#घोषणा MMU_FORCE_ORDERING_DEFAULT_STRONG_ORDERING_MASK              0x4000

/* MMU_FEATURE_ENABLE */
#घोषणा MMU_FEATURE_ENABLE_VA_ORDERING_EN_SHIFT                      0
#घोषणा MMU_FEATURE_ENABLE_VA_ORDERING_EN_MASK                       0x1
#घोषणा MMU_FEATURE_ENABLE_CLEAN_LINK_LIST_SHIFT                     1
#घोषणा MMU_FEATURE_ENABLE_CLEAN_LINK_LIST_MASK                      0x2
#घोषणा MMU_FEATURE_ENABLE_HOP_OFFSET_EN_SHIFT                       2
#घोषणा MMU_FEATURE_ENABLE_HOP_OFFSET_EN_MASK                        0x4
#घोषणा MMU_FEATURE_ENABLE_OBI_ORDERING_EN_SHIFT                     3
#घोषणा MMU_FEATURE_ENABLE_OBI_ORDERING_EN_MASK                      0x8
#घोषणा MMU_FEATURE_ENABLE_STRONG_ORDERING_READ_EN_SHIFT             4
#घोषणा MMU_FEATURE_ENABLE_STRONG_ORDERING_READ_EN_MASK              0x10
#घोषणा MMU_FEATURE_ENABLE_TRACE_ENABLE_SHIFT                        5
#घोषणा MMU_FEATURE_ENABLE_TRACE_ENABLE_MASK                         0x20

/* MMU_VA_ORDERING_MASK_31_7 */
#घोषणा MMU_VA_ORDERING_MASK_31_7_R_SHIFT                            0
#घोषणा MMU_VA_ORDERING_MASK_31_7_R_MASK                             0x1FFFFFF

/* MMU_VA_ORDERING_MASK_49_32 */
#घोषणा MMU_VA_ORDERING_MASK_49_32_R_SHIFT                           0
#घोषणा MMU_VA_ORDERING_MASK_49_32_R_MASK                            0x3FFFF

/* MMU_LOG2_DDR_SIZE */
#घोषणा MMU_LOG2_DDR_SIZE_R_SHIFT                                    0
#घोषणा MMU_LOG2_DDR_SIZE_R_MASK                                     0xFF

/* MMU_SCRAMBLER */
#घोषणा MMU_SCRAMBLER_ADDR_BIT_SHIFT                                 0
#घोषणा MMU_SCRAMBLER_ADDR_BIT_MASK                                  0x3F
#घोषणा MMU_SCRAMBLER_SINGLE_DDR_EN_SHIFT                            6
#घोषणा MMU_SCRAMBLER_SINGLE_DDR_EN_MASK                             0x40
#घोषणा MMU_SCRAMBLER_SINGLE_DDR_ID_SHIFT                            7
#घोषणा MMU_SCRAMBLER_SINGLE_DDR_ID_MASK                             0x80

/* MMU_MEM_INIT_BUSY */
#घोषणा MMU_MEM_INIT_BUSY_DATA_SHIFT                                 0
#घोषणा MMU_MEM_INIT_BUSY_DATA_MASK                                  0x3
#घोषणा MMU_MEM_INIT_BUSY_OBI0_SHIFT                                 2
#घोषणा MMU_MEM_INIT_BUSY_OBI0_MASK                                  0x4
#घोषणा MMU_MEM_INIT_BUSY_OBI1_SHIFT                                 3
#घोषणा MMU_MEM_INIT_BUSY_OBI1_MASK                                  0x8

/* MMU_SPI_MASK */
#घोषणा MMU_SPI_MASK_R_SHIFT                                         0
#घोषणा MMU_SPI_MASK_R_MASK                                          0xFF

/* MMU_SPI_CAUSE */
#घोषणा MMU_SPI_CAUSE_R_SHIFT                                        0
#घोषणा MMU_SPI_CAUSE_R_MASK                                         0xFF

/* MMU_PAGE_ERROR_CAPTURE */
#घोषणा MMU_PAGE_ERROR_CAPTURE_VA_49_32_SHIFT                        0
#घोषणा MMU_PAGE_ERROR_CAPTURE_VA_49_32_MASK                         0x3FFFF
#घोषणा MMU_PAGE_ERROR_CAPTURE_ENTRY_VALID_SHIFT                     18
#घोषणा MMU_PAGE_ERROR_CAPTURE_ENTRY_VALID_MASK                      0x40000

/* MMU_PAGE_ERROR_CAPTURE_VA */
#घोषणा MMU_PAGE_ERROR_CAPTURE_VA_VA_31_0_SHIFT                      0
#घोषणा MMU_PAGE_ERROR_CAPTURE_VA_VA_31_0_MASK                       0xFFFFFFFF

/* MMU_ACCESS_ERROR_CAPTURE */
#घोषणा MMU_ACCESS_ERROR_CAPTURE_VA_49_32_SHIFT                      0
#घोषणा MMU_ACCESS_ERROR_CAPTURE_VA_49_32_MASK                       0x3FFFF
#घोषणा MMU_ACCESS_ERROR_CAPTURE_ENTRY_VALID_SHIFT                   18
#घोषणा MMU_ACCESS_ERROR_CAPTURE_ENTRY_VALID_MASK                    0x40000

/* MMU_ACCESS_ERROR_CAPTURE_VA */
#घोषणा MMU_ACCESS_ERROR_CAPTURE_VA_VA_31_0_SHIFT                    0
#घोषणा MMU_ACCESS_ERROR_CAPTURE_VA_VA_31_0_MASK                     0xFFFFFFFF

#पूर्ण_अगर /* ASIC_REG_MMU_MASKS_H_ */
