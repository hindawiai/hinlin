<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2016 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#अगर_अघोषित _CCU_SUN8I_H3_H_
#घोषणा _CCU_SUN8I_H3_H_

#समावेश <dt-bindings/घड़ी/sun8i-h3-ccu.h>
#समावेश <dt-bindings/reset/sun8i-h3-ccu.h>

#घोषणा CLK_PLL_CPUX		0
#घोषणा CLK_PLL_AUDIO_BASE	1
#घोषणा CLK_PLL_AUDIO		2
#घोषणा CLK_PLL_AUDIO_2X	3
#घोषणा CLK_PLL_AUDIO_4X	4
#घोषणा CLK_PLL_AUDIO_8X	5

/* PLL_VIDEO is exported */

#घोषणा CLK_PLL_VE		7
#घोषणा CLK_PLL_DDR		8

/* PLL_PERIPH0 exported क्रम PRCM */

#घोषणा CLK_PLL_PERIPH0_2X	10
#घोषणा CLK_PLL_GPU		11
#घोषणा CLK_PLL_PERIPH1		12
#घोषणा CLK_PLL_DE		13

/* The CPUX घड़ी is exported */

#घोषणा CLK_AXI			15
#घोषणा CLK_AHB1		16
#घोषणा CLK_APB1		17
#घोषणा CLK_APB2		18
#घोषणा CLK_AHB2		19

/* All the bus gates are exported */

/* The first bunch of module घड़ीs are exported */

#घोषणा CLK_DRAM		96

/* All the DRAM gates are exported */

/* Some more module घड़ीs are exported */

#घोषणा CLK_NUMBER_H3		(CLK_GPU + 1)
#घोषणा CLK_NUMBER_H5		(CLK_BUS_SCR1 + 1)

#पूर्ण_अगर /* _CCU_SUN8I_H3_H_ */
