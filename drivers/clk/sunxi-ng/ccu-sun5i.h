<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2016 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#अगर_अघोषित _CCU_SUN5I_H_
#घोषणा _CCU_SUN5I_H_

#समावेश <dt-bindings/घड़ी/sun5i-ccu.h>
#समावेश <dt-bindings/reset/sun5i-ccu.h>

/* The HOSC is exported */
#घोषणा CLK_PLL_CORE		2
#घोषणा CLK_PLL_AUDIO_BASE	3
#घोषणा CLK_PLL_AUDIO		4
#घोषणा CLK_PLL_AUDIO_2X	5
#घोषणा CLK_PLL_AUDIO_4X	6
#घोषणा CLK_PLL_AUDIO_8X	7
#घोषणा CLK_PLL_VIDEO0		8

/* The PLL_VIDEO0_2X is exported क्रम HDMI */

#घोषणा CLK_PLL_VE		10
#घोषणा CLK_PLL_DDR_BASE	11
#घोषणा CLK_PLL_DDR		12
#घोषणा CLK_PLL_DDR_OTHER	13
#घोषणा CLK_PLL_PERIPH		14
#घोषणा CLK_PLL_VIDEO1		15

/* The PLL_VIDEO1_2X is exported क्रम HDMI */
/* The CPU घड़ी is exported */

#घोषणा CLK_AXI			18
#घोषणा CLK_AHB			19
#घोषणा CLK_APB0		20
#घोषणा CLK_APB1		21
#घोषणा CLK_DRAM_AXI		22

/* AHB gates are exported */
/* APB0 gates are exported */
/* APB1 gates are exported */
/* Modules घड़ीs are exported */
/* USB घड़ीs are exported */
/* GPS घड़ी is exported */
/* DRAM gates are exported */
/* More display modules घड़ीs are exported */

#घोषणा CLK_TCON_CH1_SCLK	91

/* The rest of the module घड़ीs are exported */

#घोषणा CLK_NUMBER		(CLK_IEP + 1)

#पूर्ण_अगर /* _CCU_SUN5I_H_ */
