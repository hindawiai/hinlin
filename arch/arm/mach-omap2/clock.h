<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/arch/arm/mach-omap2/घड़ी.h
 *
 *  Copyright (C) 2005-2009 Texas Instruments, Inc.
 *  Copyright (C) 2004-2011 Nokia Corporation
 *
 *  Contacts:
 *  Riअक्षरd Woodruff <r-woodruff2@ti.com>
 *  Paul Walmsley
 */

#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_CLOCK_H
#घोषणा __ARCH_ARM_MACH_OMAP2_CLOCK_H

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>

#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/ti.h>

/* काष्ठा clksel_rate.flags possibilities */
#घोषणा RATE_IN_242X		(1 << 0)
#घोषणा RATE_IN_243X		(1 << 1)
#घोषणा RATE_IN_3430ES1		(1 << 2)	/* 3430ES1 rates only */
#घोषणा RATE_IN_3430ES2PLUS	(1 << 3)	/* 3430 ES >= 2 rates only */
#घोषणा RATE_IN_36XX		(1 << 4)
#घोषणा RATE_IN_4430		(1 << 5)
#घोषणा RATE_IN_TI816X		(1 << 6)
#घोषणा RATE_IN_4460		(1 << 7)
#घोषणा RATE_IN_AM33XX		(1 << 8)
#घोषणा RATE_IN_TI814X		(1 << 9)

#घोषणा RATE_IN_24XX		(RATE_IN_242X | RATE_IN_243X)
#घोषणा RATE_IN_34XX		(RATE_IN_3430ES1 | RATE_IN_3430ES2PLUS)
#घोषणा RATE_IN_3XXX		(RATE_IN_34XX | RATE_IN_36XX)
#घोषणा RATE_IN_44XX		(RATE_IN_4430 | RATE_IN_4460)

/* RATE_IN_3430ES2PLUS_36XX includes 34xx/35xx with ES >=2, and all 36xx/37xx */
#घोषणा RATE_IN_3430ES2PLUS_36XX	(RATE_IN_3430ES2PLUS | RATE_IN_36XX)

/* CM_CLKSEL2_PLL.CORE_CLK_SRC bits (2XXX) */
#घोषणा CORE_CLK_SRC_32K		0x0
#घोषणा CORE_CLK_SRC_DPLL		0x1
#घोषणा CORE_CLK_SRC_DPLL_X2		0x2

/* OMAP2xxx CM_CLKEN_PLL.EN_DPLL bits - क्रम omap2_get_dpll_rate() */
#घोषणा OMAP2XXX_EN_DPLL_LPBYPASS		0x1
#घोषणा OMAP2XXX_EN_DPLL_FRBYPASS		0x2
#घोषणा OMAP2XXX_EN_DPLL_LOCKED			0x3

/* OMAP3xxx CM_CLKEN_PLL*.EN_*_DPLL bits - क्रम omap2_get_dpll_rate() */
#घोषणा OMAP3XXX_EN_DPLL_LPBYPASS		0x5
#घोषणा OMAP3XXX_EN_DPLL_FRBYPASS		0x6
#घोषणा OMAP3XXX_EN_DPLL_LOCKED			0x7

/* OMAP4xxx CM_CLKMODE_DPLL*.EN_*_DPLL bits - क्रम omap2_get_dpll_rate() */
#घोषणा OMAP4XXX_EN_DPLL_MNBYPASS		0x4
#घोषणा OMAP4XXX_EN_DPLL_LPBYPASS		0x5
#घोषणा OMAP4XXX_EN_DPLL_FRBYPASS		0x6
#घोषणा OMAP4XXX_EN_DPLL_LOCKED			0x7

बाह्य काष्ठा ti_clk_ll_ops omap_clk_ll_ops;

बाह्य u16 cpu_mask;

बाह्य स्थिर काष्ठा clkops clkops_omap2_dflt_रुको;
बाह्य स्थिर काष्ठा clkops clkops_omap2_dflt;

बाह्य काष्ठा clk_functions omap2_clk_functions;

पूर्णांक __init omap2_clk_setup_ll_ops(व्योम);

व्योम __init ti_clk_init_features(व्योम);
#पूर्ण_अगर
