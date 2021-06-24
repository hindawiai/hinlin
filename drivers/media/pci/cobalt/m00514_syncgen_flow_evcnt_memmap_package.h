<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright 2014-2015 Cisco Systems, Inc. and/or its affiliates.
 *  All rights reserved.
 */

#अगर_अघोषित M00514_SYNCGEN_FLOW_EVCNT_MEMMAP_PACKAGE_H
#घोषणा M00514_SYNCGEN_FLOW_EVCNT_MEMMAP_PACKAGE_H

/*******************************************************************
 * Register Block
 * M00514_SYNCGEN_FLOW_EVCNT_MEMMAP_PACKAGE_VHD_REGMAP
 *******************************************************************/
काष्ठा m00514_syncgen_flow_evcnt_regmap अणु
	uपूर्णांक32_t control;                            /* Reg 0x0000, Default=0x0 */
	uपूर्णांक32_t sync_generator_h_sync_length;       /* Reg 0x0004, Default=0x0 */
	uपूर्णांक32_t sync_generator_h_backporch_length;  /* Reg 0x0008, Default=0x0 */
	uपूर्णांक32_t sync_generator_h_active_length;     /* Reg 0x000c, Default=0x0 */
	uपूर्णांक32_t sync_generator_h_frontporch_length; /* Reg 0x0010, Default=0x0 */
	uपूर्णांक32_t sync_generator_v_sync_length;       /* Reg 0x0014, Default=0x0 */
	uपूर्णांक32_t sync_generator_v_backporch_length;  /* Reg 0x0018, Default=0x0 */
	uपूर्णांक32_t sync_generator_v_active_length;     /* Reg 0x001c, Default=0x0 */
	uपूर्णांक32_t sync_generator_v_frontporch_length; /* Reg 0x0020, Default=0x0 */
	uपूर्णांक32_t error_color;                        /* Reg 0x0024, Default=0x0 */
	uपूर्णांक32_t rd_status;                          /* Reg 0x0028 */
	uपूर्णांक32_t rd_evcnt_count;                     /* Reg 0x002c */
पूर्ण;

#घोषणा M00514_SYNCGEN_FLOW_EVCNT_REG_CONTROL_OFST 0
#घोषणा M00514_SYNCGEN_FLOW_EVCNT_REG_SYNC_GENERATOR_H_SYNC_LENGTH_OFST 4
#घोषणा M00514_SYNCGEN_FLOW_EVCNT_REG_SYNC_GENERATOR_H_BACKPORCH_LENGTH_OFST 8
#घोषणा M00514_SYNCGEN_FLOW_EVCNT_REG_SYNC_GENERATOR_H_ACTIVE_LENGTH_OFST 12
#घोषणा M00514_SYNCGEN_FLOW_EVCNT_REG_SYNC_GENERATOR_H_FRONTPORCH_LENGTH_OFST 16
#घोषणा M00514_SYNCGEN_FLOW_EVCNT_REG_SYNC_GENERATOR_V_SYNC_LENGTH_OFST 20
#घोषणा M00514_SYNCGEN_FLOW_EVCNT_REG_SYNC_GENERATOR_V_BACKPORCH_LENGTH_OFST 24
#घोषणा M00514_SYNCGEN_FLOW_EVCNT_REG_SYNC_GENERATOR_V_ACTIVE_LENGTH_OFST 28
#घोषणा M00514_SYNCGEN_FLOW_EVCNT_REG_SYNC_GENERATOR_V_FRONTPORCH_LENGTH_OFST 32
#घोषणा M00514_SYNCGEN_FLOW_EVCNT_REG_ERROR_COLOR_OFST 36
#घोषणा M00514_SYNCGEN_FLOW_EVCNT_REG_RD_STATUS_OFST 40
#घोषणा M00514_SYNCGEN_FLOW_EVCNT_REG_RD_EVCNT_COUNT_OFST 44

/*******************************************************************
 * Bit Mask क्रम रेजिस्टर
 * M00514_SYNCGEN_FLOW_EVCNT_MEMMAP_PACKAGE_VHD_BITMAP
 *******************************************************************/
/* control [7:0] */
#घोषणा M00514_CONTROL_BITMAP_SYNC_GENERATOR_LOAD_PARAM_OFST (0)
#घोषणा M00514_CONTROL_BITMAP_SYNC_GENERATOR_LOAD_PARAM_MSK  (0x1 << M00514_CONTROL_BITMAP_SYNC_GENERATOR_LOAD_PARAM_OFST)
#घोषणा M00514_CONTROL_BITMAP_SYNC_GENERATOR_ENABLE_OFST     (1)
#घोषणा M00514_CONTROL_BITMAP_SYNC_GENERATOR_ENABLE_MSK      (0x1 << M00514_CONTROL_BITMAP_SYNC_GENERATOR_ENABLE_OFST)
#घोषणा M00514_CONTROL_BITMAP_FLOW_CTRL_OUTPUT_ENABLE_OFST   (2)
#घोषणा M00514_CONTROL_BITMAP_FLOW_CTRL_OUTPUT_ENABLE_MSK    (0x1 << M00514_CONTROL_BITMAP_FLOW_CTRL_OUTPUT_ENABLE_OFST)
#घोषणा M00514_CONTROL_BITMAP_HSYNC_POLARITY_LOW_OFST        (3)
#घोषणा M00514_CONTROL_BITMAP_HSYNC_POLARITY_LOW_MSK         (0x1 << M00514_CONTROL_BITMAP_HSYNC_POLARITY_LOW_OFST)
#घोषणा M00514_CONTROL_BITMAP_VSYNC_POLARITY_LOW_OFST        (4)
#घोषणा M00514_CONTROL_BITMAP_VSYNC_POLARITY_LOW_MSK         (0x1 << M00514_CONTROL_BITMAP_VSYNC_POLARITY_LOW_OFST)
#घोषणा M00514_CONTROL_BITMAP_EVCNT_ENABLE_OFST              (5)
#घोषणा M00514_CONTROL_BITMAP_EVCNT_ENABLE_MSK               (0x1 << M00514_CONTROL_BITMAP_EVCNT_ENABLE_OFST)
#घोषणा M00514_CONTROL_BITMAP_EVCNT_CLEAR_OFST               (6)
#घोषणा M00514_CONTROL_BITMAP_EVCNT_CLEAR_MSK                (0x1 << M00514_CONTROL_BITMAP_EVCNT_CLEAR_OFST)
#घोषणा M00514_CONTROL_BITMAP_FORMAT_16_BPP_OFST             (7)
#घोषणा M00514_CONTROL_BITMAP_FORMAT_16_BPP_MSK              (0x1 << M00514_CONTROL_BITMAP_FORMAT_16_BPP_OFST)
/* error_color [23:0] */
#घोषणा M00514_ERROR_COLOR_BITMAP_BLUE_OFST                  (0)
#घोषणा M00514_ERROR_COLOR_BITMAP_BLUE_MSK                   (0xff << M00514_ERROR_COLOR_BITMAP_BLUE_OFST)
#घोषणा M00514_ERROR_COLOR_BITMAP_GREEN_OFST                 (8)
#घोषणा M00514_ERROR_COLOR_BITMAP_GREEN_MSK                  (0xff << M00514_ERROR_COLOR_BITMAP_GREEN_OFST)
#घोषणा M00514_ERROR_COLOR_BITMAP_RED_OFST                   (16)
#घोषणा M00514_ERROR_COLOR_BITMAP_RED_MSK                    (0xff << M00514_ERROR_COLOR_BITMAP_RED_OFST)
/* rd_status [1:0] */
#घोषणा M00514_RD_STATUS_BITMAP_FLOW_CTRL_NO_DATA_ERROR_OFST (0)
#घोषणा M00514_RD_STATUS_BITMAP_FLOW_CTRL_NO_DATA_ERROR_MSK  (0x1 << M00514_RD_STATUS_BITMAP_FLOW_CTRL_NO_DATA_ERROR_OFST)
#घोषणा M00514_RD_STATUS_BITMAP_READY_BUFFER_FULL_OFST       (1)
#घोषणा M00514_RD_STATUS_BITMAP_READY_BUFFER_FULL_MSK        (0x1 << M00514_RD_STATUS_BITMAP_READY_BUFFER_FULL_OFST)

#पूर्ण_अगर /*M00514_SYNCGEN_FLOW_EVCNT_MEMMAP_PACKAGE_H*/
