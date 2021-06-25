<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright 2014-2015 Cisco Systems, Inc. and/or its affiliates.
 *  All rights reserved.
 */

#अगर_अघोषित M00389_CVI_MEMMAP_PACKAGE_H
#घोषणा M00389_CVI_MEMMAP_PACKAGE_H

/*******************************************************************
 * Register Block
 * M00389_CVI_MEMMAP_PACKAGE_VHD_REGMAP
 *******************************************************************/
काष्ठा m00389_cvi_regmap अणु
	uपूर्णांक32_t control;          /* Reg 0x0000, Default=0x0 */
	uपूर्णांक32_t frame_width;      /* Reg 0x0004, Default=0x10 */
	uपूर्णांक32_t frame_height;     /* Reg 0x0008, Default=0xc */
	uपूर्णांक32_t मुक्तwheel_period; /* Reg 0x000c, Default=0x0 */
	uपूर्णांक32_t error_color;      /* Reg 0x0010, Default=0x0 */
	uपूर्णांक32_t status;           /* Reg 0x0014 */
पूर्ण;

#घोषणा M00389_CVI_REG_CONTROL_OFST 0
#घोषणा M00389_CVI_REG_FRAME_WIDTH_OFST 4
#घोषणा M00389_CVI_REG_FRAME_HEIGHT_OFST 8
#घोषणा M00389_CVI_REG_FREEWHEEL_PERIOD_OFST 12
#घोषणा M00389_CVI_REG_ERROR_COLOR_OFST 16
#घोषणा M00389_CVI_REG_STATUS_OFST 20

/*******************************************************************
 * Bit Mask क्रम रेजिस्टर
 * M00389_CVI_MEMMAP_PACKAGE_VHD_BITMAP
 *******************************************************************/
/* control [2:0] */
#घोषणा M00389_CONTROL_BITMAP_ENABLE_OFST             (0)
#घोषणा M00389_CONTROL_BITMAP_ENABLE_MSK              (0x1 << M00389_CONTROL_BITMAP_ENABLE_OFST)
#घोषणा M00389_CONTROL_BITMAP_HSYNC_POLARITY_LOW_OFST (1)
#घोषणा M00389_CONTROL_BITMAP_HSYNC_POLARITY_LOW_MSK  (0x1 << M00389_CONTROL_BITMAP_HSYNC_POLARITY_LOW_OFST)
#घोषणा M00389_CONTROL_BITMAP_VSYNC_POLARITY_LOW_OFST (2)
#घोषणा M00389_CONTROL_BITMAP_VSYNC_POLARITY_LOW_MSK  (0x1 << M00389_CONTROL_BITMAP_VSYNC_POLARITY_LOW_OFST)
/* status [1:0] */
#घोषणा M00389_STATUS_BITMAP_LOCK_OFST                (0)
#घोषणा M00389_STATUS_BITMAP_LOCK_MSK                 (0x1 << M00389_STATUS_BITMAP_LOCK_OFST)
#घोषणा M00389_STATUS_BITMAP_ERROR_OFST               (1)
#घोषणा M00389_STATUS_BITMAP_ERROR_MSK                (0x1 << M00389_STATUS_BITMAP_ERROR_OFST)

#पूर्ण_अगर /*M00389_CVI_MEMMAP_PACKAGE_H*/
