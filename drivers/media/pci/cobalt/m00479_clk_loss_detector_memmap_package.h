<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright 2014-2015 Cisco Systems, Inc. and/or its affiliates.
 *  All rights reserved.
 */

#अगर_अघोषित M00479_CLK_LOSS_DETECTOR_MEMMAP_PACKAGE_H
#घोषणा M00479_CLK_LOSS_DETECTOR_MEMMAP_PACKAGE_H

/*******************************************************************
 * Register Block
 * M00479_CLK_LOSS_DETECTOR_MEMMAP_PACKAGE_VHD_REGMAP
 *******************************************************************/
काष्ठा m00479_clk_loss_detector_regmap अणु
	/* Control module */
	uपूर्णांक32_t ctrl;             /* Reg 0x0000, Default=0x0 */
	uपूर्णांक32_t status;           /* Reg 0x0004 */
	/* Number of ref clk cycles beक्रमe checking the घड़ी under test */
	uपूर्णांक32_t ref_clk_cnt_val;  /* Reg 0x0008, Default=0xc4 */
	/* Number of test clk cycles required in the ref_clk_cnt_val period
	 * to ensure that the test घड़ी is perक्रमming as expected */
	uपूर्णांक32_t test_clk_cnt_val; /* Reg 0x000c, Default=0xa */
पूर्ण;

#घोषणा M00479_CLK_LOSS_DETECTOR_REG_CTRL_OFST 0
#घोषणा M00479_CLK_LOSS_DETECTOR_REG_STATUS_OFST 4
#घोषणा M00479_CLK_LOSS_DETECTOR_REG_REF_CLK_CNT_VAL_OFST 8
#घोषणा M00479_CLK_LOSS_DETECTOR_REG_TEST_CLK_CNT_VAL_OFST 12

/*******************************************************************
 * Bit Mask क्रम रेजिस्टर
 * M00479_CLK_LOSS_DETECTOR_MEMMAP_PACKAGE_VHD_BITMAP
 *******************************************************************/
/* ctrl [0:0] */
#घोषणा M00479_CTRL_BITMAP_ENABLE_OFST          (0)
#घोषणा M00479_CTRL_BITMAP_ENABLE_MSK           (0x1 << M00479_CTRL_BITMAP_ENABLE_OFST)
/* status [0:0] */
#घोषणा M00479_STATUS_BITMAP_CLOCK_MISSING_OFST (0)
#घोषणा M00479_STATUS_BITMAP_CLOCK_MISSING_MSK  (0x1 << M00479_STATUS_BITMAP_CLOCK_MISSING_OFST)

#पूर्ण_अगर /*M00479_CLK_LOSS_DETECTOR_MEMMAP_PACKAGE_H*/
