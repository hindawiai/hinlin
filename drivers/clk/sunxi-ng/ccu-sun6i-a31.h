<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2016 Chen-Yu Tsai
 *
 * Chen-Yu Tsai <wens@csie.org>
 */

#अगर_अघोषित _CCU_SUN6I_A31_H_
#घोषणा _CCU_SUN6I_A31_H_

#समावेश <dt-bindings/घड़ी/sun6i-a31-ccu.h>
#समावेश <dt-bindings/reset/sun6i-a31-ccu.h>

#घोषणा CLK_PLL_CPU		0
#घोषणा CLK_PLL_AUDIO_BASE	1
#घोषणा CLK_PLL_AUDIO		2
#घोषणा CLK_PLL_AUDIO_2X	3
#घोषणा CLK_PLL_AUDIO_4X	4
#घोषणा CLK_PLL_AUDIO_8X	5
#घोषणा CLK_PLL_VIDEO0		6

/* The PLL_VIDEO0_2X घड़ी is exported */

#घोषणा CLK_PLL_VE		8
#घोषणा CLK_PLL_DDR		9

/* The PLL_PERIPH घड़ी is exported */

#घोषणा CLK_PLL_PERIPH_2X	11
#घोषणा CLK_PLL_VIDEO1		12

/* The PLL_VIDEO1_2X घड़ी is exported */

#घोषणा CLK_PLL_GPU		14

/* The PLL_VIDEO1_2X घड़ी is exported */

#घोषणा CLK_PLL9		16
#घोषणा CLK_PLL10		17

/* The CPUX घड़ी is exported */

#घोषणा CLK_AXI			19
#घोषणा CLK_AHB1		20
#घोषणा CLK_APB1		21
#घोषणा CLK_APB2		22

/* All the bus gates are exported */

/* The first bunch of module घड़ीs are exported */

/* EMAC घड़ी is not implemented */

#घोषणा CLK_MDFS		107
#घोषणा CLK_SDRAM0		108
#घोषणा CLK_SDRAM1		109

/* All the DRAM gates are exported */

/* Some more module घड़ीs are exported */

#घोषणा CLK_MBUS0		141
#घोषणा CLK_MBUS1		142

/* Some more module घड़ीs and बाह्यal घड़ी outमाला_दो are exported */

#घोषणा CLK_NUMBER		(CLK_OUT_C + 1)

#पूर्ण_अगर /* _CCU_SUN6I_A31_H_ */
