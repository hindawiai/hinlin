<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Device Tree स्थिरants क्रम the Texas Instruments DP83867 PHY
 *
 * Author: Dan Murphy <dmurphy@ti.com>
 *
 * Copyright:   (C) 2015 Texas Instruments, Inc.
 */

#अगर_अघोषित _DT_BINDINGS_TI_DP83867_H
#घोषणा _DT_BINDINGS_TI_DP83867_H

/* PHY CTRL bits */
#घोषणा DP83867_PHYCR_FIFO_DEPTH_3_B_NIB	0x00
#घोषणा DP83867_PHYCR_FIFO_DEPTH_4_B_NIB	0x01
#घोषणा DP83867_PHYCR_FIFO_DEPTH_6_B_NIB	0x02
#घोषणा DP83867_PHYCR_FIFO_DEPTH_8_B_NIB	0x03

/* RGMIIDCTL पूर्णांकernal delay क्रम rx and tx */
#घोषणा	DP83867_RGMIIDCTL_250_PS	0x0
#घोषणा	DP83867_RGMIIDCTL_500_PS	0x1
#घोषणा	DP83867_RGMIIDCTL_750_PS	0x2
#घोषणा	DP83867_RGMIIDCTL_1_NS		0x3
#घोषणा	DP83867_RGMIIDCTL_1_25_NS	0x4
#घोषणा	DP83867_RGMIIDCTL_1_50_NS	0x5
#घोषणा	DP83867_RGMIIDCTL_1_75_NS	0x6
#घोषणा	DP83867_RGMIIDCTL_2_00_NS	0x7
#घोषणा	DP83867_RGMIIDCTL_2_25_NS	0x8
#घोषणा	DP83867_RGMIIDCTL_2_50_NS	0x9
#घोषणा	DP83867_RGMIIDCTL_2_75_NS	0xa
#घोषणा	DP83867_RGMIIDCTL_3_00_NS	0xb
#घोषणा	DP83867_RGMIIDCTL_3_25_NS	0xc
#घोषणा	DP83867_RGMIIDCTL_3_50_NS	0xd
#घोषणा	DP83867_RGMIIDCTL_3_75_NS	0xe
#घोषणा	DP83867_RGMIIDCTL_4_00_NS	0xf

/* IO_MUX_CFG - Clock output selection */
#घोषणा DP83867_CLK_O_SEL_CHN_A_RCLK		0x0
#घोषणा DP83867_CLK_O_SEL_CHN_B_RCLK		0x1
#घोषणा DP83867_CLK_O_SEL_CHN_C_RCLK		0x2
#घोषणा DP83867_CLK_O_SEL_CHN_D_RCLK		0x3
#घोषणा DP83867_CLK_O_SEL_CHN_A_RCLK_DIV5	0x4
#घोषणा DP83867_CLK_O_SEL_CHN_B_RCLK_DIV5	0x5
#घोषणा DP83867_CLK_O_SEL_CHN_C_RCLK_DIV5	0x6
#घोषणा DP83867_CLK_O_SEL_CHN_D_RCLK_DIV5	0x7
#घोषणा DP83867_CLK_O_SEL_CHN_A_TCLK		0x8
#घोषणा DP83867_CLK_O_SEL_CHN_B_TCLK		0x9
#घोषणा DP83867_CLK_O_SEL_CHN_C_TCLK		0xA
#घोषणा DP83867_CLK_O_SEL_CHN_D_TCLK		0xB
#घोषणा DP83867_CLK_O_SEL_REF_CLK		0xC
/* Special flag to indicate घड़ी should be off */
#घोषणा DP83867_CLK_O_SEL_OFF			0xFFFFFFFF
#पूर्ण_अगर
