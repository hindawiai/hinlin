<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2016 Icenowy Zheng <icenowy@aosc.xyz>
 *
 * Based on ccu-sun8i-h3.h, which is:
 * Copyright (c) 2016 Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#अगर_अघोषित _CCU_SUN8I_H3_H_
#घोषणा _CCU_SUN8I_H3_H_

#समावेश <dt-bindings/घड़ी/sun8i-v3s-ccu.h>
#समावेश <dt-bindings/reset/sun8i-v3s-ccu.h>

#घोषणा CLK_PLL_CPU		0
#घोषणा CLK_PLL_AUDIO_BASE	1
#घोषणा CLK_PLL_AUDIO		2
#घोषणा CLK_PLL_AUDIO_2X	3
#घोषणा CLK_PLL_AUDIO_4X	4
#घोषणा CLK_PLL_AUDIO_8X	5
#घोषणा CLK_PLL_VIDEO		6
#घोषणा CLK_PLL_VE		7
#घोषणा CLK_PLL_DDR0		8
#घोषणा CLK_PLL_PERIPH0		9
#घोषणा CLK_PLL_PERIPH0_2X	10
#घोषणा CLK_PLL_ISP		11
#घोषणा CLK_PLL_PERIPH1		12
/* Reserve one number क्रम not implemented and not used PLL_DDR1 */

/* The CPU घड़ी is exported */

#घोषणा CLK_AXI			15
#घोषणा CLK_AHB1		16
#घोषणा CLK_APB1		17
#घोषणा CLK_APB2		18
#घोषणा CLK_AHB2		19

/* All the bus gates are exported */

/* The first bunch of module घड़ीs are exported */

#घोषणा CLK_DRAM		58

/* All the DRAM gates are exported */

/* Some more module घड़ीs are exported */

#घोषणा CLK_MBUS		72

/* And the GPU module घड़ी is exported */

#घोषणा CLK_PLL_DDR1		74

#पूर्ण_अगर /* _CCU_SUN8I_H3_H_ */
