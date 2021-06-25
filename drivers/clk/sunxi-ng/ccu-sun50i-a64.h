<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2016 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#अगर_अघोषित _CCU_SUN50I_A64_H_
#घोषणा _CCU_SUN50I_A64_H_

#समावेश <dt-bindings/घड़ी/sun50i-a64-ccu.h>
#समावेश <dt-bindings/reset/sun50i-a64-ccu.h>

#घोषणा CLK_OSC_12M			0
#घोषणा CLK_PLL_CPUX			1
#घोषणा CLK_PLL_AUDIO_BASE		2
#घोषणा CLK_PLL_AUDIO			3
#घोषणा CLK_PLL_AUDIO_2X		4
#घोषणा CLK_PLL_AUDIO_4X		5
#घोषणा CLK_PLL_AUDIO_8X		6

/* PLL_VIDEO0 exported क्रम HDMI PHY */

#घोषणा CLK_PLL_VIDEO0_2X		8
#घोषणा CLK_PLL_VE			9
#घोषणा CLK_PLL_DDR0			10

/* PLL_PERIPH0 exported क्रम PRCM */

#घोषणा CLK_PLL_PERIPH0_2X		12
#घोषणा CLK_PLL_PERIPH1			13
#घोषणा CLK_PLL_PERIPH1_2X		14
#घोषणा CLK_PLL_VIDEO1			15
#घोषणा CLK_PLL_GPU			16
#घोषणा CLK_PLL_MIPI			17
#घोषणा CLK_PLL_HSIC			18
#घोषणा CLK_PLL_DE			19
#घोषणा CLK_PLL_DDR1			20
#घोषणा CLK_AXI				22
#घोषणा CLK_APB				23
#घोषणा CLK_AHB1			24
#घोषणा CLK_APB1			25
#घोषणा CLK_APB2			26
#घोषणा CLK_AHB2			27

/* All the bus gates are exported */

/* The first bunch of module घड़ीs are exported */

#घोषणा CLK_USB_OHCI0_12M		90

#घोषणा CLK_USB_OHCI1_12M		92

#घोषणा CLK_DRAM			94

/* All the DRAM gates are exported */

/* And the DSI and GPU module घड़ी is exported */

#घोषणा CLK_NUMBER			(CLK_GPU + 1)

#पूर्ण_अगर /* _CCU_SUN50I_A64_H_ */
