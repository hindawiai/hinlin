<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2020 Yangtao Li <frank@allwinnertech.com>
 */

#अगर_अघोषित _CCU_SUN50I_A100_H_
#घोषणा _CCU_SUN50I_A100_H_

#समावेश <dt-bindings/घड़ी/sun50i-a100-ccu.h>
#समावेश <dt-bindings/reset/sun50i-a100-ccu.h>

#घोषणा CLK_OSC12M		0
#घोषणा CLK_PLL_CPUX		1
#घोषणा CLK_PLL_DDR0		2

/* PLL_PERIPH0 exported क्रम PRCM */

#घोषणा CLK_PLL_PERIPH0_2X	4
#घोषणा CLK_PLL_PERIPH1		5
#घोषणा CLK_PLL_PERIPH1_2X	6
#घोषणा CLK_PLL_GPU		7
#घोषणा CLK_PLL_VIDEO0		8
#घोषणा CLK_PLL_VIDEO0_2X	9
#घोषणा CLK_PLL_VIDEO0_4X	10
#घोषणा CLK_PLL_VIDEO1		11
#घोषणा CLK_PLL_VIDEO1_2X	12
#घोषणा CLK_PLL_VIDEO1_4X	13
#घोषणा CLK_PLL_VIDEO2		14
#घोषणा CLK_PLL_VIDEO2_2X	15
#घोषणा CLK_PLL_VIDEO2_4X	16
#घोषणा CLK_PLL_VIDEO3		17
#घोषणा CLK_PLL_VIDEO3_2X	18
#घोषणा CLK_PLL_VIDEO3_4X	19
#घोषणा CLK_PLL_VE		20
#घोषणा CLK_PLL_COM		21
#घोषणा CLK_PLL_COM_AUDIO	22
#घोषणा CLK_PLL_AUDIO		23

/* CPUX घड़ी exported क्रम DVFS */

#घोषणा CLK_AXI			25
#घोषणा CLK_CPUX_APB		26
#घोषणा CLK_PSI_AHB1_AHB2	27
#घोषणा CLK_AHB3		28

/* APB1 घड़ी exported क्रम PIO */

#घोषणा CLK_APB2		30

/* All module घड़ीs and bus gates are exported except DRAM */

#घोषणा CLK_BUS_DRAM		58

#घोषणा CLK_NUMBER		(CLK_CSI_ISP + 1)

#पूर्ण_अगर /* _CCU_SUN50I_A100_H_ */
