<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2016 Icenowy Zheng <icenowy@aosc.io>
 */

#अगर_अघोषित _CCU_SUN50I_H6_H_
#घोषणा _CCU_SUN50I_H6_H_

#समावेश <dt-bindings/घड़ी/sun50i-h6-ccu.h>
#समावेश <dt-bindings/reset/sun50i-h6-ccu.h>

#घोषणा CLK_OSC12M		0
#घोषणा CLK_PLL_CPUX		1
#घोषणा CLK_PLL_DDR0		2

/* PLL_PERIPH0 exported क्रम PRCM */

#घोषणा CLK_PLL_PERIPH0_2X	4
#घोषणा CLK_PLL_PERIPH0_4X	5
#घोषणा CLK_PLL_PERIPH1		6
#घोषणा CLK_PLL_PERIPH1_2X	7
#घोषणा CLK_PLL_PERIPH1_4X	8
#घोषणा CLK_PLL_GPU		9
#घोषणा CLK_PLL_VIDEO0		10
#घोषणा CLK_PLL_VIDEO0_4X	11
#घोषणा CLK_PLL_VIDEO1		12
#घोषणा CLK_PLL_VIDEO1_4X	13
#घोषणा CLK_PLL_VE		14
#घोषणा CLK_PLL_DE		15
#घोषणा CLK_PLL_HSIC		16
#घोषणा CLK_PLL_AUDIO_BASE	17
#घोषणा CLK_PLL_AUDIO		18
#घोषणा CLK_PLL_AUDIO_2X	19
#घोषणा CLK_PLL_AUDIO_4X	20

/* CPUX घड़ी exported क्रम DVFS */

#घोषणा CLK_AXI			22
#घोषणा CLK_CPUX_APB		23
#घोषणा CLK_PSI_AHB1_AHB2	24
#घोषणा CLK_AHB3		25

/* APB1 घड़ी exported क्रम PIO */

#घोषणा CLK_APB2		27
#घोषणा CLK_MBUS		28

/* All module घड़ीs and bus gates are exported except DRAM */

#घोषणा CLK_DRAM		52

#घोषणा CLK_BUS_DRAM		60

#घोषणा CLK_NUMBER		(CLK_BUS_HDCP + 1)

#पूर्ण_अगर /* _CCU_SUN50I_H6_H_ */
