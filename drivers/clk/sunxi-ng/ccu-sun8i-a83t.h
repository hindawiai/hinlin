<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2016 Chen-Yu Tsai
 *
 * Chen-Yu Tsai <wens@csie.org>
 */

#अगर_अघोषित _CCU_SUN8I_A83T_H_
#घोषणा _CCU_SUN8I_A83T_H_

#समावेश <dt-bindings/घड़ी/sun8i-a83t-ccu.h>
#समावेश <dt-bindings/reset/sun8i-a83t-ccu.h>

#घोषणा CLK_PLL_C0CPUX		0
#घोषणा CLK_PLL_C1CPUX		1
#घोषणा CLK_PLL_AUDIO		2
#घोषणा CLK_PLL_VIDEO0		3
#घोषणा CLK_PLL_VE		4
#घोषणा CLK_PLL_DDR		5

/* pll-periph is exported to the PRCM block */

#घोषणा CLK_PLL_GPU		7
#घोषणा CLK_PLL_HSIC		8

/* pll-de is exported क्रम the display engine */

#घोषणा CLK_PLL_VIDEO1		10

/* The CPUX घड़ीs are exported */

#घोषणा CLK_AXI0		13
#घोषणा CLK_AXI1		14
#घोषणा CLK_AHB1		15
#घोषणा CLK_AHB2		16
#घोषणा CLK_APB1		17
#घोषणा CLK_APB2		18

/* bus gates exported */

#घोषणा CLK_CCI400		58

/* module and usb घड़ीs exported */

#घोषणा CLK_DRAM		82

/* dram gates and more module घड़ीs exported */

#घोषणा CLK_MBUS		95

/* more module घड़ीs exported */

#घोषणा CLK_NUMBER		(CLK_GPU_HYD + 1)

#पूर्ण_अगर /* _CCU_SUN8I_A83T_H_ */
