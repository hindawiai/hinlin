<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2017 Priit Laes
 *
 * Priit Laes <plaes@plaes.org>
 */

#अगर_अघोषित _CCU_SUN4I_A10_H_
#घोषणा _CCU_SUN4I_A10_H_

#समावेश <dt-bindings/घड़ी/sun4i-a10-ccu.h>
#समावेश <dt-bindings/घड़ी/sun7i-a20-ccu.h>
#समावेश <dt-bindings/reset/sun4i-a10-ccu.h>

/* The HOSC is exported */
#घोषणा CLK_PLL_CORE		2
#घोषणा CLK_PLL_AUDIO_BASE	3
#घोषणा CLK_PLL_AUDIO		4
#घोषणा CLK_PLL_AUDIO_2X	5
#घोषणा CLK_PLL_AUDIO_4X	6
#घोषणा CLK_PLL_AUDIO_8X	7
#घोषणा CLK_PLL_VIDEO0		8
/* The PLL_VIDEO0_2X घड़ी is exported */
#घोषणा CLK_PLL_VE		10
#घोषणा CLK_PLL_DDR_BASE	11
#घोषणा CLK_PLL_DDR		12
#घोषणा CLK_PLL_DDR_OTHER	13
#घोषणा CLK_PLL_PERIPH_BASE	14
#घोषणा CLK_PLL_PERIPH		15
#घोषणा CLK_PLL_PERIPH_SATA	16
#घोषणा CLK_PLL_VIDEO1		17
/* The PLL_VIDEO1_2X घड़ी is exported */
#घोषणा CLK_PLL_GPU		19

/* The CPU घड़ी is exported */
#घोषणा CLK_AXI			21
#घोषणा CLK_AXI_DRAM		22
#घोषणा CLK_AHB			23
#घोषणा CLK_APB0		24
#घोषणा CLK_APB1		25

/* AHB gates are exported (23..68) */
/* APB0 gates are exported (69..78) */
/* APB1 gates are exported (79..95) */
/* IP module घड़ीs are exported (96..128) */
/* DRAM gates are exported (129..142)*/
/* Media (display engine घड़ीs & etc) are exported (143..169) */

#घोषणा CLK_NUMBER_SUN4I	(CLK_MBUS + 1)
#घोषणा CLK_NUMBER_SUN7I	(CLK_OUT_B + 1)

#पूर्ण_अगर /* _CCU_SUN4I_A10_H_ */
