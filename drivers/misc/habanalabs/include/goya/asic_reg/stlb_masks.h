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

#अगर_अघोषित ASIC_REG_STLB_MASKS_H_
#घोषणा ASIC_REG_STLB_MASKS_H_

/*
 *****************************************
 *   STLB (Prototype: STLB)
 *****************************************
 */

/* STLB_CACHE_INV */
#घोषणा STLB_CACHE_INV_PRODUCER_INDEX_SHIFT                          0
#घोषणा STLB_CACHE_INV_PRODUCER_INDEX_MASK                           0xFF
#घोषणा STLB_CACHE_INV_INDEX_MASK_SHIFT                              8
#घोषणा STLB_CACHE_INV_INDEX_MASK_MASK                               0xFF00

/* STLB_CACHE_INV_BASE_39_8 */
#घोषणा STLB_CACHE_INV_BASE_39_8_PA_SHIFT                            0
#घोषणा STLB_CACHE_INV_BASE_39_8_PA_MASK                             0xFFFFFFFF

/* STLB_CACHE_INV_BASE_49_40 */
#घोषणा STLB_CACHE_INV_BASE_49_40_PA_SHIFT                           0
#घोषणा STLB_CACHE_INV_BASE_49_40_PA_MASK                            0x3FF

/* STLB_STLB_FEATURE_EN */
#घोषणा STLB_STLB_FEATURE_EN_STLB_CTRL_MULTI_PAGE_SIZE_EN_SHIFT      0
#घोषणा STLB_STLB_FEATURE_EN_STLB_CTRL_MULTI_PAGE_SIZE_EN_MASK       0x1
#घोषणा STLB_STLB_FEATURE_EN_MULTI_PAGE_SIZE_EN_SHIFT                1
#घोषणा STLB_STLB_FEATURE_EN_MULTI_PAGE_SIZE_EN_MASK                 0x2
#घोषणा STLB_STLB_FEATURE_EN_LOOKUP_EN_SHIFT                         2
#घोषणा STLB_STLB_FEATURE_EN_LOOKUP_EN_MASK                          0x4
#घोषणा STLB_STLB_FEATURE_EN_BYPASS_SHIFT                            3
#घोषणा STLB_STLB_FEATURE_EN_BYPASS_MASK                             0x8
#घोषणा STLB_STLB_FEATURE_EN_BANK_STOP_SHIFT                         4
#घोषणा STLB_STLB_FEATURE_EN_BANK_STOP_MASK                          0x10
#घोषणा STLB_STLB_FEATURE_EN_TRACE_EN_SHIFT                          5
#घोषणा STLB_STLB_FEATURE_EN_TRACE_EN_MASK                           0x20
#घोषणा STLB_STLB_FEATURE_EN_FOLLOWER_EN_SHIFT                       6
#घोषणा STLB_STLB_FEATURE_EN_FOLLOWER_EN_MASK                        0x40
#घोषणा STLB_STLB_FEATURE_EN_CACHING_EN_SHIFT                        7
#घोषणा STLB_STLB_FEATURE_EN_CACHING_EN_MASK                         0xF80

/* STLB_STLB_AXI_CACHE */
#घोषणा STLB_STLB_AXI_CACHE_STLB_CTRL_ARCACHE_SHIFT                  0
#घोषणा STLB_STLB_AXI_CACHE_STLB_CTRL_ARCACHE_MASK                   0xF
#घोषणा STLB_STLB_AXI_CACHE_STLB_CTRL_AWCACHE_SHIFT                  4
#घोषणा STLB_STLB_AXI_CACHE_STLB_CTRL_AWCACHE_MASK                   0xF0
#घोषणा STLB_STLB_AXI_CACHE_INV_ARCACHE_SHIFT                        8
#घोषणा STLB_STLB_AXI_CACHE_INV_ARCACHE_MASK                         0xF00

/* STLB_HOP_CONFIGURATION */
#घोषणा STLB_HOP_CONFIGURATION_FIRST_HOP_SHIFT                       0
#घोषणा STLB_HOP_CONFIGURATION_FIRST_HOP_MASK                        0x7
#घोषणा STLB_HOP_CONFIGURATION_FIRST_LOOKUP_HOP_SHIFT                4
#घोषणा STLB_HOP_CONFIGURATION_FIRST_LOOKUP_HOP_MASK                 0x70
#घोषणा STLB_HOP_CONFIGURATION_LAST_HOP_SHIFT                        8
#घोषणा STLB_HOP_CONFIGURATION_LAST_HOP_MASK                         0x700

/* STLB_LINK_LIST_LOOKUP_MASK_49_32 */
#घोषणा STLB_LINK_LIST_LOOKUP_MASK_49_32_R_SHIFT                     0
#घोषणा STLB_LINK_LIST_LOOKUP_MASK_49_32_R_MASK                      0x3FFFF

/* STLB_LINK_LIST_LOOKUP_MASK_31_0 */
#घोषणा STLB_LINK_LIST_LOOKUP_MASK_31_0_R_SHIFT                      0
#घोषणा STLB_LINK_LIST_LOOKUP_MASK_31_0_R_MASK                       0xFFFFFFFF

/* STLB_LINK_LIST */
#घोषणा STLB_LINK_LIST_CLEAR_SHIFT                                   0
#घोषणा STLB_LINK_LIST_CLEAR_MASK                                    0x1
#घोषणा STLB_LINK_LIST_EN_SHIFT                                      1
#घोषणा STLB_LINK_LIST_EN_MASK                                       0x2

/* STLB_INV_ALL_START */
#घोषणा STLB_INV_ALL_START_R_SHIFT                                   0
#घोषणा STLB_INV_ALL_START_R_MASK                                    0x1

/* STLB_INV_ALL_SET */
#घोषणा STLB_INV_ALL_SET_R_SHIFT                                     0
#घोषणा STLB_INV_ALL_SET_R_MASK                                      0xFF

/* STLB_INV_PS */
#घोषणा STLB_INV_PS_R_SHIFT                                          0
#घोषणा STLB_INV_PS_R_MASK                                           0x3

/* STLB_INV_CONSUMER_INDEX */
#घोषणा STLB_INV_CONSUMER_INDEX_R_SHIFT                              0
#घोषणा STLB_INV_CONSUMER_INDEX_R_MASK                               0xFF

/* STLB_INV_HIT_COUNT */
#घोषणा STLB_INV_HIT_COUNT_R_SHIFT                                   0
#घोषणा STLB_INV_HIT_COUNT_R_MASK                                    0x7FF

/* STLB_INV_SET */
#घोषणा STLB_INV_SET_R_SHIFT                                         0
#घोषणा STLB_INV_SET_R_MASK                                          0xFF

/* STLB_SRAM_INIT */
#घोषणा STLB_SRAM_INIT_BUSY_TAG_SHIFT                                0
#घोषणा STLB_SRAM_INIT_BUSY_TAG_MASK                                 0x3
#घोषणा STLB_SRAM_INIT_BUSY_SLICE_SHIFT                              2
#घोषणा STLB_SRAM_INIT_BUSY_SLICE_MASK                               0xC
#घोषणा STLB_SRAM_INIT_BUSY_DATA_SHIFT                               4
#घोषणा STLB_SRAM_INIT_BUSY_DATA_MASK                                0x10

#पूर्ण_अगर /* ASIC_REG_STLB_MASKS_H_ */
