<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2012-2016 Zhang, Keguang <keguang.zhang@gmail.com>
 */

#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>

#समावेश <loongson1.h>
#समावेश "clk.h"

#घोषणा OSC		(33 * 1000000)
#घोषणा DIV_APB		2

अटल DEFINE_SPINLOCK(_lock);

अटल अचिन्हित दीर्घ ls1x_pll_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	u32 pll, rate;

	pll = __raw_पढ़ोl(LS1X_CLK_PLL_FREQ);
	rate = 12 + (pll & GENMASK(5, 0));
	rate *= OSC;
	rate >>= 1;

	वापस rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops ls1x_pll_clk_ops = अणु
	.recalc_rate = ls1x_pll_recalc_rate,
पूर्ण;

अटल स्थिर अक्षर *स्थिर cpu_parents[] = अणु "cpu_clk_div", "osc_clk", पूर्ण;
अटल स्थिर अक्षर *स्थिर ahb_parents[] = अणु "ahb_clk_div", "osc_clk", पूर्ण;
अटल स्थिर अक्षर *स्थिर dc_parents[] = अणु "dc_clk_div", "osc_clk", पूर्ण;

व्योम __init ls1x_clk_init(व्योम)
अणु
	काष्ठा clk_hw *hw;

	hw = clk_hw_रेजिस्टर_fixed_rate(शून्य, "osc_clk", शून्य, 0, OSC);
	clk_hw_रेजिस्टर_clkdev(hw, "osc_clk", शून्य);

	/* घड़ी derived from 33 MHz OSC clk */
	hw = clk_hw_रेजिस्टर_pll(शून्य, "pll_clk", "osc_clk",
				 &ls1x_pll_clk_ops, 0);
	clk_hw_रेजिस्टर_clkdev(hw, "pll_clk", शून्य);

	/* घड़ी derived from PLL clk */
	/*                                 _____
	 *         _______________________|     |
	 * OSC ___/                       | MUX |___ CPU CLK
	 *        \___ PLL ___ CPU DIV ___|     |
	 *                                |_____|
	 */
	hw = clk_hw_रेजिस्टर_भागider(शून्य, "cpu_clk_div", "pll_clk",
				   CLK_GET_RATE_NOCACHE, LS1X_CLK_PLL_DIV,
				   DIV_CPU_SHIFT, DIV_CPU_WIDTH,
				   CLK_DIVIDER_ONE_BASED |
				   CLK_DIVIDER_ROUND_CLOSEST, &_lock);
	clk_hw_रेजिस्टर_clkdev(hw, "cpu_clk_div", शून्य);
	hw = clk_hw_रेजिस्टर_mux(शून्य, "cpu_clk", cpu_parents,
			       ARRAY_SIZE(cpu_parents),
			       CLK_SET_RATE_NO_REPARENT, LS1X_CLK_PLL_DIV,
			       BYPASS_CPU_SHIFT, BYPASS_CPU_WIDTH, 0, &_lock);
	clk_hw_रेजिस्टर_clkdev(hw, "cpu_clk", शून्य);

	/*                                 _____
	 *         _______________________|     |
	 * OSC ___/                       | MUX |___ DC  CLK
	 *        \___ PLL ___ DC  DIV ___|     |
	 *                                |_____|
	 */
	hw = clk_hw_रेजिस्टर_भागider(शून्य, "dc_clk_div", "pll_clk",
				   0, LS1X_CLK_PLL_DIV, DIV_DC_SHIFT,
				   DIV_DC_WIDTH, CLK_DIVIDER_ONE_BASED, &_lock);
	clk_hw_रेजिस्टर_clkdev(hw, "dc_clk_div", शून्य);
	hw = clk_hw_रेजिस्टर_mux(शून्य, "dc_clk", dc_parents,
			       ARRAY_SIZE(dc_parents),
			       CLK_SET_RATE_NO_REPARENT, LS1X_CLK_PLL_DIV,
			       BYPASS_DC_SHIFT, BYPASS_DC_WIDTH, 0, &_lock);
	clk_hw_रेजिस्टर_clkdev(hw, "dc_clk", शून्य);

	/*                                 _____
	 *         _______________________|     |
	 * OSC ___/                       | MUX |___ DDR CLK
	 *        \___ PLL ___ DDR DIV ___|     |
	 *                                |_____|
	 */
	hw = clk_hw_रेजिस्टर_भागider(शून्य, "ahb_clk_div", "pll_clk",
				   0, LS1X_CLK_PLL_DIV, DIV_DDR_SHIFT,
				   DIV_DDR_WIDTH, CLK_DIVIDER_ONE_BASED,
				   &_lock);
	clk_hw_रेजिस्टर_clkdev(hw, "ahb_clk_div", शून्य);
	hw = clk_hw_रेजिस्टर_mux(शून्य, "ahb_clk", ahb_parents,
			       ARRAY_SIZE(ahb_parents),
			       CLK_SET_RATE_NO_REPARENT, LS1X_CLK_PLL_DIV,
			       BYPASS_DDR_SHIFT, BYPASS_DDR_WIDTH, 0, &_lock);
	clk_hw_रेजिस्टर_clkdev(hw, "ahb_clk", शून्य);
	clk_hw_रेजिस्टर_clkdev(hw, "ls1x-dma", शून्य);
	clk_hw_रेजिस्टर_clkdev(hw, "stmmaceth", शून्य);

	/* घड़ी derived from AHB clk */
	/* APB clk is always half of the AHB clk */
	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, "apb_clk", "ahb_clk", 0, 1,
					DIV_APB);
	clk_hw_रेजिस्टर_clkdev(hw, "apb_clk", शून्य);
	clk_hw_रेजिस्टर_clkdev(hw, "ls1x-ac97", शून्य);
	clk_hw_रेजिस्टर_clkdev(hw, "ls1x-i2c", शून्य);
	clk_hw_रेजिस्टर_clkdev(hw, "ls1x-nand", शून्य);
	clk_hw_रेजिस्टर_clkdev(hw, "ls1x-pwmtimer", शून्य);
	clk_hw_रेजिस्टर_clkdev(hw, "ls1x-spi", शून्य);
	clk_hw_रेजिस्टर_clkdev(hw, "ls1x-wdt", शून्य);
	clk_hw_रेजिस्टर_clkdev(hw, "serial8250", शून्य);
पूर्ण
