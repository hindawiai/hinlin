<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * OMAP3-common घड़ी function prototypes and macros
 *
 * Copyright (C) 2007-2010 Texas Instruments, Inc.
 * Copyright (C) 2007-2010 Nokia Corporation
 */

#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_CLOCK3XXX_H
#घोषणा __ARCH_ARM_MACH_OMAP2_CLOCK3XXX_H

पूर्णांक omap3xxx_clk_init(व्योम);
पूर्णांक omap3_core_dpll_m2_set_rate(काष्ठा clk_hw *clk, अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ parent_rate);

बाह्य काष्ठा clk *sdrc_ick_p;
बाह्य काष्ठा clk *arm_fck_p;

बाह्य स्थिर काष्ठा clkops clkops_noncore_dpll_ops;

#पूर्ण_अगर
