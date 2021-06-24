<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Atheros AR71XX/AR724X/AR913X common routines
 *
 *  Copyright (C) 2010-2011 Jaiganesh Narayanan <jnarayanan@atheros.com>
 *  Copyright (C) 2011 Gabor Juhos <juhosg@खोलोwrt.org>
 *
 *  Parts of this file are based on Atheros' 2.6.15/2.6.31 BSP
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <dt-bindings/घड़ी/ath79-clk.h>

#समावेश <यंत्र/भाग64.h>

#समावेश <यंत्र/mach-ath79/ath79.h>
#समावेश <यंत्र/mach-ath79/ar71xx_regs.h>
#समावेश "common.h"

#घोषणा AR71XX_BASE_FREQ	40000000
#घोषणा AR724X_BASE_FREQ	40000000

अटल काष्ठा clk *clks[ATH79_CLK_END];
अटल काष्ठा clk_onecell_data clk_data = अणु
	.clks = clks,
	.clk_num = ARRAY_SIZE(clks),
पूर्ण;

अटल स्थिर अक्षर * स्थिर clk_names[ATH79_CLK_END] = अणु
	[ATH79_CLK_CPU] = "cpu",
	[ATH79_CLK_DDR] = "ddr",
	[ATH79_CLK_AHB] = "ahb",
	[ATH79_CLK_REF] = "ref",
	[ATH79_CLK_MDIO] = "mdio",
पूर्ण;

अटल स्थिर अक्षर * __init ath79_clk_name(पूर्णांक type)
अणु
	BUG_ON(type >= ARRAY_SIZE(clk_names) || !clk_names[type]);
	वापस clk_names[type];
पूर्ण

अटल व्योम __init __ath79_set_clk(पूर्णांक type, स्थिर अक्षर *name, काष्ठा clk *clk)
अणु
	अगर (IS_ERR(clk))
		panic("failed to allocate %s clock structure", clk_names[type]);

	clks[type] = clk;
	clk_रेजिस्टर_clkdev(clk, name, शून्य);
पूर्ण

अटल काष्ठा clk * __init ath79_set_clk(पूर्णांक type, अचिन्हित दीर्घ rate)
अणु
	स्थिर अक्षर *name = ath79_clk_name(type);
	काष्ठा clk *clk;

	clk = clk_रेजिस्टर_fixed_rate(शून्य, name, शून्य, 0, rate);
	__ath79_set_clk(type, name, clk);
	वापस clk;
पूर्ण

अटल काष्ठा clk * __init ath79_set_ff_clk(पूर्णांक type, स्थिर अक्षर *parent,
					    अचिन्हित पूर्णांक mult, अचिन्हित पूर्णांक भाग)
अणु
	स्थिर अक्षर *name = ath79_clk_name(type);
	काष्ठा clk *clk;

	clk = clk_रेजिस्टर_fixed_factor(शून्य, name, parent, 0, mult, भाग);
	__ath79_set_clk(type, name, clk);
	वापस clk;
पूर्ण

अटल अचिन्हित दीर्घ __init ath79_setup_ref_clk(अचिन्हित दीर्घ rate)
अणु
	काष्ठा clk *clk = clks[ATH79_CLK_REF];

	अगर (clk)
		rate = clk_get_rate(clk);
	अन्यथा
		clk = ath79_set_clk(ATH79_CLK_REF, rate);

	वापस rate;
पूर्ण

अटल व्योम __init ar71xx_घड़ीs_init(व्योम __iomem *pll_base)
अणु
	अचिन्हित दीर्घ ref_rate;
	अचिन्हित दीर्घ cpu_rate;
	अचिन्हित दीर्घ ddr_rate;
	अचिन्हित दीर्घ ahb_rate;
	u32 pll;
	u32 freq;
	u32 भाग;

	ref_rate = ath79_setup_ref_clk(AR71XX_BASE_FREQ);

	pll = __raw_पढ़ोl(pll_base + AR71XX_PLL_REG_CPU_CONFIG);

	भाग = ((pll >> AR71XX_PLL_FB_SHIFT) & AR71XX_PLL_FB_MASK) + 1;
	freq = भाग * ref_rate;

	भाग = ((pll >> AR71XX_CPU_DIV_SHIFT) & AR71XX_CPU_DIV_MASK) + 1;
	cpu_rate = freq / भाग;

	भाग = ((pll >> AR71XX_DDR_DIV_SHIFT) & AR71XX_DDR_DIV_MASK) + 1;
	ddr_rate = freq / भाग;

	भाग = (((pll >> AR71XX_AHB_DIV_SHIFT) & AR71XX_AHB_DIV_MASK) + 1) * 2;
	ahb_rate = cpu_rate / भाग;

	ath79_set_clk(ATH79_CLK_CPU, cpu_rate);
	ath79_set_clk(ATH79_CLK_DDR, ddr_rate);
	ath79_set_clk(ATH79_CLK_AHB, ahb_rate);
पूर्ण

अटल व्योम __init ar724x_घड़ीs_init(व्योम __iomem *pll_base)
अणु
	u32 mult, भाग, ddr_भाग, ahb_भाग;
	u32 pll;

	ath79_setup_ref_clk(AR71XX_BASE_FREQ);

	pll = __raw_पढ़ोl(pll_base + AR724X_PLL_REG_CPU_CONFIG);

	mult = ((pll >> AR724X_PLL_FB_SHIFT) & AR724X_PLL_FB_MASK);
	भाग = ((pll >> AR724X_PLL_REF_DIV_SHIFT) & AR724X_PLL_REF_DIV_MASK) * 2;

	ddr_भाग = ((pll >> AR724X_DDR_DIV_SHIFT) & AR724X_DDR_DIV_MASK) + 1;
	ahb_भाग = (((pll >> AR724X_AHB_DIV_SHIFT) & AR724X_AHB_DIV_MASK) + 1) * 2;

	ath79_set_ff_clk(ATH79_CLK_CPU, "ref", mult, भाग);
	ath79_set_ff_clk(ATH79_CLK_DDR, "ref", mult, भाग * ddr_भाग);
	ath79_set_ff_clk(ATH79_CLK_AHB, "ref", mult, भाग * ahb_भाग);
पूर्ण

अटल व्योम __init ar933x_घड़ीs_init(व्योम __iomem *pll_base)
अणु
	अचिन्हित दीर्घ ref_rate;
	u32 घड़ी_ctrl;
	u32 ref_भाग;
	u32 ninit_mul;
	u32 out_भाग;

	u32 cpu_भाग;
	u32 ddr_भाग;
	u32 ahb_भाग;
	u32 t;

	t = ath79_reset_rr(AR933X_RESET_REG_BOOTSTRAP);
	अगर (t & AR933X_BOOTSTRAP_REF_CLK_40)
		ref_rate = (40 * 1000 * 1000);
	अन्यथा
		ref_rate = (25 * 1000 * 1000);

	ath79_setup_ref_clk(ref_rate);

	घड़ी_ctrl = __raw_पढ़ोl(pll_base + AR933X_PLL_CLOCK_CTRL_REG);
	अगर (घड़ी_ctrl & AR933X_PLL_CLOCK_CTRL_BYPASS) अणु
		ref_भाग = 1;
		ninit_mul = 1;
		out_भाग = 1;

		cpu_भाग = 1;
		ddr_भाग = 1;
		ahb_भाग = 1;
	पूर्ण अन्यथा अणु
		u32 cpu_config;
		u32 t;

		cpu_config = __raw_पढ़ोl(pll_base + AR933X_PLL_CPU_CONFIG_REG);

		t = (cpu_config >> AR933X_PLL_CPU_CONFIG_REFDIV_SHIFT) &
		    AR933X_PLL_CPU_CONFIG_REFDIV_MASK;
		ref_भाग = t;

		ninit_mul = (cpu_config >> AR933X_PLL_CPU_CONFIG_NINT_SHIFT) &
		    AR933X_PLL_CPU_CONFIG_NINT_MASK;

		t = (cpu_config >> AR933X_PLL_CPU_CONFIG_OUTDIV_SHIFT) &
		    AR933X_PLL_CPU_CONFIG_OUTDIV_MASK;
		अगर (t == 0)
			t = 1;

		out_भाग = (1 << t);

		cpu_भाग = ((घड़ी_ctrl >> AR933X_PLL_CLOCK_CTRL_CPU_DIV_SHIFT) &
		     AR933X_PLL_CLOCK_CTRL_CPU_DIV_MASK) + 1;

		ddr_भाग = ((घड़ी_ctrl >> AR933X_PLL_CLOCK_CTRL_DDR_DIV_SHIFT) &
		      AR933X_PLL_CLOCK_CTRL_DDR_DIV_MASK) + 1;

		ahb_भाग = ((घड़ी_ctrl >> AR933X_PLL_CLOCK_CTRL_AHB_DIV_SHIFT) &
		     AR933X_PLL_CLOCK_CTRL_AHB_DIV_MASK) + 1;
	पूर्ण

	ath79_set_ff_clk(ATH79_CLK_CPU, "ref", ninit_mul,
			 ref_भाग * out_भाग * cpu_भाग);
	ath79_set_ff_clk(ATH79_CLK_DDR, "ref", ninit_mul,
			 ref_भाग * out_भाग * ddr_भाग);
	ath79_set_ff_clk(ATH79_CLK_AHB, "ref", ninit_mul,
			 ref_भाग * out_भाग * ahb_भाग);
पूर्ण

अटल u32 __init ar934x_get_pll_freq(u32 ref, u32 ref_भाग, u32 nपूर्णांक, u32 nfrac,
				      u32 frac, u32 out_भाग)
अणु
	u64 t;
	u32 ret;

	t = ref;
	t *= nपूर्णांक;
	करो_भाग(t, ref_भाग);
	ret = t;

	t = ref;
	t *= nfrac;
	करो_भाग(t, ref_भाग * frac);
	ret += t;

	ret /= (1 << out_भाग);
	वापस ret;
पूर्ण

अटल व्योम __init ar934x_घड़ीs_init(व्योम __iomem *pll_base)
अणु
	अचिन्हित दीर्घ ref_rate;
	अचिन्हित दीर्घ cpu_rate;
	अचिन्हित दीर्घ ddr_rate;
	अचिन्हित दीर्घ ahb_rate;
	u32 pll, out_भाग, ref_भाग, nपूर्णांक, nfrac, frac, clk_ctrl, postभाग;
	u32 cpu_pll, ddr_pll;
	u32 bootstrap;
	व्योम __iomem *dpll_base;

	dpll_base = ioremap(AR934X_SRIF_BASE, AR934X_SRIF_SIZE);

	bootstrap = ath79_reset_rr(AR934X_RESET_REG_BOOTSTRAP);
	अगर (bootstrap & AR934X_BOOTSTRAP_REF_CLK_40)
		ref_rate = 40 * 1000 * 1000;
	अन्यथा
		ref_rate = 25 * 1000 * 1000;

	ref_rate = ath79_setup_ref_clk(ref_rate);

	pll = __raw_पढ़ोl(dpll_base + AR934X_SRIF_CPU_DPLL2_REG);
	अगर (pll & AR934X_SRIF_DPLL2_LOCAL_PLL) अणु
		out_भाग = (pll >> AR934X_SRIF_DPLL2_OUTDIV_SHIFT) &
			  AR934X_SRIF_DPLL2_OUTDIV_MASK;
		pll = __raw_पढ़ोl(dpll_base + AR934X_SRIF_CPU_DPLL1_REG);
		nपूर्णांक = (pll >> AR934X_SRIF_DPLL1_NINT_SHIFT) &
		       AR934X_SRIF_DPLL1_NINT_MASK;
		nfrac = pll & AR934X_SRIF_DPLL1_NFRAC_MASK;
		ref_भाग = (pll >> AR934X_SRIF_DPLL1_REFDIV_SHIFT) &
			  AR934X_SRIF_DPLL1_REFDIV_MASK;
		frac = 1 << 18;
	पूर्ण अन्यथा अणु
		pll = __raw_पढ़ोl(pll_base + AR934X_PLL_CPU_CONFIG_REG);
		out_भाग = (pll >> AR934X_PLL_CPU_CONFIG_OUTDIV_SHIFT) &
			AR934X_PLL_CPU_CONFIG_OUTDIV_MASK;
		ref_भाग = (pll >> AR934X_PLL_CPU_CONFIG_REFDIV_SHIFT) &
			  AR934X_PLL_CPU_CONFIG_REFDIV_MASK;
		nपूर्णांक = (pll >> AR934X_PLL_CPU_CONFIG_NINT_SHIFT) &
		       AR934X_PLL_CPU_CONFIG_NINT_MASK;
		nfrac = (pll >> AR934X_PLL_CPU_CONFIG_NFRAC_SHIFT) &
			AR934X_PLL_CPU_CONFIG_NFRAC_MASK;
		frac = 1 << 6;
	पूर्ण

	cpu_pll = ar934x_get_pll_freq(ref_rate, ref_भाग, nपूर्णांक,
				      nfrac, frac, out_भाग);

	pll = __raw_पढ़ोl(dpll_base + AR934X_SRIF_DDR_DPLL2_REG);
	अगर (pll & AR934X_SRIF_DPLL2_LOCAL_PLL) अणु
		out_भाग = (pll >> AR934X_SRIF_DPLL2_OUTDIV_SHIFT) &
			  AR934X_SRIF_DPLL2_OUTDIV_MASK;
		pll = __raw_पढ़ोl(dpll_base + AR934X_SRIF_DDR_DPLL1_REG);
		nपूर्णांक = (pll >> AR934X_SRIF_DPLL1_NINT_SHIFT) &
		       AR934X_SRIF_DPLL1_NINT_MASK;
		nfrac = pll & AR934X_SRIF_DPLL1_NFRAC_MASK;
		ref_भाग = (pll >> AR934X_SRIF_DPLL1_REFDIV_SHIFT) &
			  AR934X_SRIF_DPLL1_REFDIV_MASK;
		frac = 1 << 18;
	पूर्ण अन्यथा अणु
		pll = __raw_पढ़ोl(pll_base + AR934X_PLL_DDR_CONFIG_REG);
		out_भाग = (pll >> AR934X_PLL_DDR_CONFIG_OUTDIV_SHIFT) &
			  AR934X_PLL_DDR_CONFIG_OUTDIV_MASK;
		ref_भाग = (pll >> AR934X_PLL_DDR_CONFIG_REFDIV_SHIFT) &
			   AR934X_PLL_DDR_CONFIG_REFDIV_MASK;
		nपूर्णांक = (pll >> AR934X_PLL_DDR_CONFIG_NINT_SHIFT) &
		       AR934X_PLL_DDR_CONFIG_NINT_MASK;
		nfrac = (pll >> AR934X_PLL_DDR_CONFIG_NFRAC_SHIFT) &
			AR934X_PLL_DDR_CONFIG_NFRAC_MASK;
		frac = 1 << 10;
	पूर्ण

	ddr_pll = ar934x_get_pll_freq(ref_rate, ref_भाग, nपूर्णांक,
				      nfrac, frac, out_भाग);

	clk_ctrl = __raw_पढ़ोl(pll_base + AR934X_PLL_CPU_DDR_CLK_CTRL_REG);

	postभाग = (clk_ctrl >> AR934X_PLL_CPU_DDR_CLK_CTRL_CPU_POST_DIV_SHIFT) &
		  AR934X_PLL_CPU_DDR_CLK_CTRL_CPU_POST_DIV_MASK;

	अगर (clk_ctrl & AR934X_PLL_CPU_DDR_CLK_CTRL_CPU_PLL_BYPASS)
		cpu_rate = ref_rate;
	अन्यथा अगर (clk_ctrl & AR934X_PLL_CPU_DDR_CLK_CTRL_CPUCLK_FROM_CPUPLL)
		cpu_rate = cpu_pll / (postभाग + 1);
	अन्यथा
		cpu_rate = ddr_pll / (postभाग + 1);

	postभाग = (clk_ctrl >> AR934X_PLL_CPU_DDR_CLK_CTRL_DDR_POST_DIV_SHIFT) &
		  AR934X_PLL_CPU_DDR_CLK_CTRL_DDR_POST_DIV_MASK;

	अगर (clk_ctrl & AR934X_PLL_CPU_DDR_CLK_CTRL_DDR_PLL_BYPASS)
		ddr_rate = ref_rate;
	अन्यथा अगर (clk_ctrl & AR934X_PLL_CPU_DDR_CLK_CTRL_DDRCLK_FROM_DDRPLL)
		ddr_rate = ddr_pll / (postभाग + 1);
	अन्यथा
		ddr_rate = cpu_pll / (postभाग + 1);

	postभाग = (clk_ctrl >> AR934X_PLL_CPU_DDR_CLK_CTRL_AHB_POST_DIV_SHIFT) &
		  AR934X_PLL_CPU_DDR_CLK_CTRL_AHB_POST_DIV_MASK;

	अगर (clk_ctrl & AR934X_PLL_CPU_DDR_CLK_CTRL_AHB_PLL_BYPASS)
		ahb_rate = ref_rate;
	अन्यथा अगर (clk_ctrl & AR934X_PLL_CPU_DDR_CLK_CTRL_AHBCLK_FROM_DDRPLL)
		ahb_rate = ddr_pll / (postभाग + 1);
	अन्यथा
		ahb_rate = cpu_pll / (postभाग + 1);

	ath79_set_clk(ATH79_CLK_CPU, cpu_rate);
	ath79_set_clk(ATH79_CLK_DDR, ddr_rate);
	ath79_set_clk(ATH79_CLK_AHB, ahb_rate);

	clk_ctrl = __raw_पढ़ोl(pll_base + AR934X_PLL_SWITCH_CLOCK_CONTROL_REG);
	अगर (clk_ctrl & AR934X_PLL_SWITCH_CLOCK_CONTROL_MDIO_CLK_SEL)
		ath79_set_clk(ATH79_CLK_MDIO, 100 * 1000 * 1000);

	iounmap(dpll_base);
पूर्ण

अटल व्योम __init qca953x_घड़ीs_init(व्योम __iomem *pll_base)
अणु
	अचिन्हित दीर्घ ref_rate;
	अचिन्हित दीर्घ cpu_rate;
	अचिन्हित दीर्घ ddr_rate;
	अचिन्हित दीर्घ ahb_rate;
	u32 pll, out_भाग, ref_भाग, nपूर्णांक, frac, clk_ctrl, postभाग;
	u32 cpu_pll, ddr_pll;
	u32 bootstrap;

	bootstrap = ath79_reset_rr(QCA953X_RESET_REG_BOOTSTRAP);
	अगर (bootstrap &	QCA953X_BOOTSTRAP_REF_CLK_40)
		ref_rate = 40 * 1000 * 1000;
	अन्यथा
		ref_rate = 25 * 1000 * 1000;

	ref_rate = ath79_setup_ref_clk(ref_rate);

	pll = __raw_पढ़ोl(pll_base + QCA953X_PLL_CPU_CONFIG_REG);
	out_भाग = (pll >> QCA953X_PLL_CPU_CONFIG_OUTDIV_SHIFT) &
		  QCA953X_PLL_CPU_CONFIG_OUTDIV_MASK;
	ref_भाग = (pll >> QCA953X_PLL_CPU_CONFIG_REFDIV_SHIFT) &
		  QCA953X_PLL_CPU_CONFIG_REFDIV_MASK;
	nपूर्णांक = (pll >> QCA953X_PLL_CPU_CONFIG_NINT_SHIFT) &
	       QCA953X_PLL_CPU_CONFIG_NINT_MASK;
	frac = (pll >> QCA953X_PLL_CPU_CONFIG_NFRAC_SHIFT) &
	       QCA953X_PLL_CPU_CONFIG_NFRAC_MASK;

	cpu_pll = nपूर्णांक * ref_rate / ref_भाग;
	cpu_pll += frac * (ref_rate >> 6) / ref_भाग;
	cpu_pll /= (1 << out_भाग);

	pll = __raw_पढ़ोl(pll_base + QCA953X_PLL_DDR_CONFIG_REG);
	out_भाग = (pll >> QCA953X_PLL_DDR_CONFIG_OUTDIV_SHIFT) &
		  QCA953X_PLL_DDR_CONFIG_OUTDIV_MASK;
	ref_भाग = (pll >> QCA953X_PLL_DDR_CONFIG_REFDIV_SHIFT) &
		  QCA953X_PLL_DDR_CONFIG_REFDIV_MASK;
	nपूर्णांक = (pll >> QCA953X_PLL_DDR_CONFIG_NINT_SHIFT) &
	       QCA953X_PLL_DDR_CONFIG_NINT_MASK;
	frac = (pll >> QCA953X_PLL_DDR_CONFIG_NFRAC_SHIFT) &
	       QCA953X_PLL_DDR_CONFIG_NFRAC_MASK;

	ddr_pll = nपूर्णांक * ref_rate / ref_भाग;
	ddr_pll += frac * (ref_rate >> 6) / (ref_भाग << 4);
	ddr_pll /= (1 << out_भाग);

	clk_ctrl = __raw_पढ़ोl(pll_base + QCA953X_PLL_CLK_CTRL_REG);

	postभाग = (clk_ctrl >> QCA953X_PLL_CLK_CTRL_CPU_POST_DIV_SHIFT) &
		  QCA953X_PLL_CLK_CTRL_CPU_POST_DIV_MASK;

	अगर (clk_ctrl & QCA953X_PLL_CLK_CTRL_CPU_PLL_BYPASS)
		cpu_rate = ref_rate;
	अन्यथा अगर (clk_ctrl & QCA953X_PLL_CLK_CTRL_CPUCLK_FROM_CPUPLL)
		cpu_rate = cpu_pll / (postभाग + 1);
	अन्यथा
		cpu_rate = ddr_pll / (postभाग + 1);

	postभाग = (clk_ctrl >> QCA953X_PLL_CLK_CTRL_DDR_POST_DIV_SHIFT) &
		  QCA953X_PLL_CLK_CTRL_DDR_POST_DIV_MASK;

	अगर (clk_ctrl & QCA953X_PLL_CLK_CTRL_DDR_PLL_BYPASS)
		ddr_rate = ref_rate;
	अन्यथा अगर (clk_ctrl & QCA953X_PLL_CLK_CTRL_DDRCLK_FROM_DDRPLL)
		ddr_rate = ddr_pll / (postभाग + 1);
	अन्यथा
		ddr_rate = cpu_pll / (postभाग + 1);

	postभाग = (clk_ctrl >> QCA953X_PLL_CLK_CTRL_AHB_POST_DIV_SHIFT) &
		  QCA953X_PLL_CLK_CTRL_AHB_POST_DIV_MASK;

	अगर (clk_ctrl & QCA953X_PLL_CLK_CTRL_AHB_PLL_BYPASS)
		ahb_rate = ref_rate;
	अन्यथा अगर (clk_ctrl & QCA953X_PLL_CLK_CTRL_AHBCLK_FROM_DDRPLL)
		ahb_rate = ddr_pll / (postभाग + 1);
	अन्यथा
		ahb_rate = cpu_pll / (postभाग + 1);

	ath79_set_clk(ATH79_CLK_CPU, cpu_rate);
	ath79_set_clk(ATH79_CLK_DDR, ddr_rate);
	ath79_set_clk(ATH79_CLK_AHB, ahb_rate);
पूर्ण

अटल व्योम __init qca955x_घड़ीs_init(व्योम __iomem *pll_base)
अणु
	अचिन्हित दीर्घ ref_rate;
	अचिन्हित दीर्घ cpu_rate;
	अचिन्हित दीर्घ ddr_rate;
	अचिन्हित दीर्घ ahb_rate;
	u32 pll, out_भाग, ref_भाग, nपूर्णांक, frac, clk_ctrl, postभाग;
	u32 cpu_pll, ddr_pll;
	u32 bootstrap;

	bootstrap = ath79_reset_rr(QCA955X_RESET_REG_BOOTSTRAP);
	अगर (bootstrap &	QCA955X_BOOTSTRAP_REF_CLK_40)
		ref_rate = 40 * 1000 * 1000;
	अन्यथा
		ref_rate = 25 * 1000 * 1000;

	ref_rate = ath79_setup_ref_clk(ref_rate);

	pll = __raw_पढ़ोl(pll_base + QCA955X_PLL_CPU_CONFIG_REG);
	out_भाग = (pll >> QCA955X_PLL_CPU_CONFIG_OUTDIV_SHIFT) &
		  QCA955X_PLL_CPU_CONFIG_OUTDIV_MASK;
	ref_भाग = (pll >> QCA955X_PLL_CPU_CONFIG_REFDIV_SHIFT) &
		  QCA955X_PLL_CPU_CONFIG_REFDIV_MASK;
	nपूर्णांक = (pll >> QCA955X_PLL_CPU_CONFIG_NINT_SHIFT) &
	       QCA955X_PLL_CPU_CONFIG_NINT_MASK;
	frac = (pll >> QCA955X_PLL_CPU_CONFIG_NFRAC_SHIFT) &
	       QCA955X_PLL_CPU_CONFIG_NFRAC_MASK;

	cpu_pll = nपूर्णांक * ref_rate / ref_भाग;
	cpu_pll += frac * ref_rate / (ref_भाग * (1 << 6));
	cpu_pll /= (1 << out_भाग);

	pll = __raw_पढ़ोl(pll_base + QCA955X_PLL_DDR_CONFIG_REG);
	out_भाग = (pll >> QCA955X_PLL_DDR_CONFIG_OUTDIV_SHIFT) &
		  QCA955X_PLL_DDR_CONFIG_OUTDIV_MASK;
	ref_भाग = (pll >> QCA955X_PLL_DDR_CONFIG_REFDIV_SHIFT) &
		  QCA955X_PLL_DDR_CONFIG_REFDIV_MASK;
	nपूर्णांक = (pll >> QCA955X_PLL_DDR_CONFIG_NINT_SHIFT) &
	       QCA955X_PLL_DDR_CONFIG_NINT_MASK;
	frac = (pll >> QCA955X_PLL_DDR_CONFIG_NFRAC_SHIFT) &
	       QCA955X_PLL_DDR_CONFIG_NFRAC_MASK;

	ddr_pll = nपूर्णांक * ref_rate / ref_भाग;
	ddr_pll += frac * ref_rate / (ref_भाग * (1 << 10));
	ddr_pll /= (1 << out_भाग);

	clk_ctrl = __raw_पढ़ोl(pll_base + QCA955X_PLL_CLK_CTRL_REG);

	postभाग = (clk_ctrl >> QCA955X_PLL_CLK_CTRL_CPU_POST_DIV_SHIFT) &
		  QCA955X_PLL_CLK_CTRL_CPU_POST_DIV_MASK;

	अगर (clk_ctrl & QCA955X_PLL_CLK_CTRL_CPU_PLL_BYPASS)
		cpu_rate = ref_rate;
	अन्यथा अगर (clk_ctrl & QCA955X_PLL_CLK_CTRL_CPUCLK_FROM_CPUPLL)
		cpu_rate = ddr_pll / (postभाग + 1);
	अन्यथा
		cpu_rate = cpu_pll / (postभाग + 1);

	postभाग = (clk_ctrl >> QCA955X_PLL_CLK_CTRL_DDR_POST_DIV_SHIFT) &
		  QCA955X_PLL_CLK_CTRL_DDR_POST_DIV_MASK;

	अगर (clk_ctrl & QCA955X_PLL_CLK_CTRL_DDR_PLL_BYPASS)
		ddr_rate = ref_rate;
	अन्यथा अगर (clk_ctrl & QCA955X_PLL_CLK_CTRL_DDRCLK_FROM_DDRPLL)
		ddr_rate = cpu_pll / (postभाग + 1);
	अन्यथा
		ddr_rate = ddr_pll / (postभाग + 1);

	postभाग = (clk_ctrl >> QCA955X_PLL_CLK_CTRL_AHB_POST_DIV_SHIFT) &
		  QCA955X_PLL_CLK_CTRL_AHB_POST_DIV_MASK;

	अगर (clk_ctrl & QCA955X_PLL_CLK_CTRL_AHB_PLL_BYPASS)
		ahb_rate = ref_rate;
	अन्यथा अगर (clk_ctrl & QCA955X_PLL_CLK_CTRL_AHBCLK_FROM_DDRPLL)
		ahb_rate = ddr_pll / (postभाग + 1);
	अन्यथा
		ahb_rate = cpu_pll / (postभाग + 1);

	ath79_set_clk(ATH79_CLK_CPU, cpu_rate);
	ath79_set_clk(ATH79_CLK_DDR, ddr_rate);
	ath79_set_clk(ATH79_CLK_AHB, ahb_rate);
पूर्ण

अटल व्योम __init qca956x_घड़ीs_init(व्योम __iomem *pll_base)
अणु
	अचिन्हित दीर्घ ref_rate;
	अचिन्हित दीर्घ cpu_rate;
	अचिन्हित दीर्घ ddr_rate;
	अचिन्हित दीर्घ ahb_rate;
	u32 pll, out_भाग, ref_भाग, nपूर्णांक, hfrac, lfrac, clk_ctrl, postभाग;
	u32 cpu_pll, ddr_pll;
	u32 bootstrap;

	/*
	 * QCA956x समयr init workaround has to be applied right beक्रमe setting
	 * up the घड़ी. Else, there will be no jअगरfies
	 */
	u32 misc;

	misc = ath79_reset_rr(AR71XX_RESET_REG_MISC_INT_ENABLE);
	misc |= MISC_INT_MIPS_SI_TIMERINT_MASK;
	ath79_reset_wr(AR71XX_RESET_REG_MISC_INT_ENABLE, misc);

	bootstrap = ath79_reset_rr(QCA956X_RESET_REG_BOOTSTRAP);
	अगर (bootstrap &	QCA956X_BOOTSTRAP_REF_CLK_40)
		ref_rate = 40 * 1000 * 1000;
	अन्यथा
		ref_rate = 25 * 1000 * 1000;

	ref_rate = ath79_setup_ref_clk(ref_rate);

	pll = __raw_पढ़ोl(pll_base + QCA956X_PLL_CPU_CONFIG_REG);
	out_भाग = (pll >> QCA956X_PLL_CPU_CONFIG_OUTDIV_SHIFT) &
		  QCA956X_PLL_CPU_CONFIG_OUTDIV_MASK;
	ref_भाग = (pll >> QCA956X_PLL_CPU_CONFIG_REFDIV_SHIFT) &
		  QCA956X_PLL_CPU_CONFIG_REFDIV_MASK;

	pll = __raw_पढ़ोl(pll_base + QCA956X_PLL_CPU_CONFIG1_REG);
	nपूर्णांक = (pll >> QCA956X_PLL_CPU_CONFIG1_NINT_SHIFT) &
	       QCA956X_PLL_CPU_CONFIG1_NINT_MASK;
	hfrac = (pll >> QCA956X_PLL_CPU_CONFIG1_NFRAC_H_SHIFT) &
	       QCA956X_PLL_CPU_CONFIG1_NFRAC_H_MASK;
	lfrac = (pll >> QCA956X_PLL_CPU_CONFIG1_NFRAC_L_SHIFT) &
	       QCA956X_PLL_CPU_CONFIG1_NFRAC_L_MASK;

	cpu_pll = nपूर्णांक * ref_rate / ref_भाग;
	cpu_pll += (lfrac * ref_rate) / ((ref_भाग * 25) << 13);
	cpu_pll += (hfrac >> 13) * ref_rate / ref_भाग;
	cpu_pll /= (1 << out_भाग);

	pll = __raw_पढ़ोl(pll_base + QCA956X_PLL_DDR_CONFIG_REG);
	out_भाग = (pll >> QCA956X_PLL_DDR_CONFIG_OUTDIV_SHIFT) &
		  QCA956X_PLL_DDR_CONFIG_OUTDIV_MASK;
	ref_भाग = (pll >> QCA956X_PLL_DDR_CONFIG_REFDIV_SHIFT) &
		  QCA956X_PLL_DDR_CONFIG_REFDIV_MASK;
	pll = __raw_पढ़ोl(pll_base + QCA956X_PLL_DDR_CONFIG1_REG);
	nपूर्णांक = (pll >> QCA956X_PLL_DDR_CONFIG1_NINT_SHIFT) &
	       QCA956X_PLL_DDR_CONFIG1_NINT_MASK;
	hfrac = (pll >> QCA956X_PLL_DDR_CONFIG1_NFRAC_H_SHIFT) &
	       QCA956X_PLL_DDR_CONFIG1_NFRAC_H_MASK;
	lfrac = (pll >> QCA956X_PLL_DDR_CONFIG1_NFRAC_L_SHIFT) &
	       QCA956X_PLL_DDR_CONFIG1_NFRAC_L_MASK;

	ddr_pll = nपूर्णांक * ref_rate / ref_भाग;
	ddr_pll += (lfrac * ref_rate) / ((ref_भाग * 25) << 13);
	ddr_pll += (hfrac >> 13) * ref_rate / ref_भाग;
	ddr_pll /= (1 << out_भाग);

	clk_ctrl = __raw_पढ़ोl(pll_base + QCA956X_PLL_CLK_CTRL_REG);

	postभाग = (clk_ctrl >> QCA956X_PLL_CLK_CTRL_CPU_POST_DIV_SHIFT) &
		  QCA956X_PLL_CLK_CTRL_CPU_POST_DIV_MASK;

	अगर (clk_ctrl & QCA956X_PLL_CLK_CTRL_CPU_PLL_BYPASS)
		cpu_rate = ref_rate;
	अन्यथा अगर (clk_ctrl & QCA956X_PLL_CLK_CTRL_CPU_DDRCLK_FROM_CPUPLL)
		cpu_rate = ddr_pll / (postभाग + 1);
	अन्यथा
		cpu_rate = cpu_pll / (postभाग + 1);

	postभाग = (clk_ctrl >> QCA956X_PLL_CLK_CTRL_DDR_POST_DIV_SHIFT) &
		  QCA956X_PLL_CLK_CTRL_DDR_POST_DIV_MASK;

	अगर (clk_ctrl & QCA956X_PLL_CLK_CTRL_DDR_PLL_BYPASS)
		ddr_rate = ref_rate;
	अन्यथा अगर (clk_ctrl & QCA956X_PLL_CLK_CTRL_CPU_DDRCLK_FROM_DDRPLL)
		ddr_rate = cpu_pll / (postभाग + 1);
	अन्यथा
		ddr_rate = ddr_pll / (postभाग + 1);

	postभाग = (clk_ctrl >> QCA956X_PLL_CLK_CTRL_AHB_POST_DIV_SHIFT) &
		  QCA956X_PLL_CLK_CTRL_AHB_POST_DIV_MASK;

	अगर (clk_ctrl & QCA956X_PLL_CLK_CTRL_AHB_PLL_BYPASS)
		ahb_rate = ref_rate;
	अन्यथा अगर (clk_ctrl & QCA956X_PLL_CLK_CTRL_AHBCLK_FROM_DDRPLL)
		ahb_rate = ddr_pll / (postभाग + 1);
	अन्यथा
		ahb_rate = cpu_pll / (postभाग + 1);

	ath79_set_clk(ATH79_CLK_CPU, cpu_rate);
	ath79_set_clk(ATH79_CLK_DDR, ddr_rate);
	ath79_set_clk(ATH79_CLK_AHB, ahb_rate);
पूर्ण

अटल व्योम __init ath79_घड़ीs_init_dt(काष्ठा device_node *np)
अणु
	काष्ठा clk *ref_clk;
	व्योम __iomem *pll_base;

	ref_clk = of_clk_get(np, 0);
	अगर (!IS_ERR(ref_clk))
		clks[ATH79_CLK_REF] = ref_clk;

	pll_base = of_iomap(np, 0);
	अगर (!pll_base) अणु
		pr_err("%pOF: can't map pll registers\n", np);
		जाओ err_clk;
	पूर्ण

	अगर (of_device_is_compatible(np, "qca,ar7100-pll"))
		ar71xx_घड़ीs_init(pll_base);
	अन्यथा अगर (of_device_is_compatible(np, "qca,ar7240-pll") ||
		 of_device_is_compatible(np, "qca,ar9130-pll"))
		ar724x_घड़ीs_init(pll_base);
	अन्यथा अगर (of_device_is_compatible(np, "qca,ar9330-pll"))
		ar933x_घड़ीs_init(pll_base);
	अन्यथा अगर (of_device_is_compatible(np, "qca,ar9340-pll"))
		ar934x_घड़ीs_init(pll_base);
	अन्यथा अगर (of_device_is_compatible(np, "qca,qca9530-pll"))
		qca953x_घड़ीs_init(pll_base);
	अन्यथा अगर (of_device_is_compatible(np, "qca,qca9550-pll"))
		qca955x_घड़ीs_init(pll_base);
	अन्यथा अगर (of_device_is_compatible(np, "qca,qca9560-pll"))
		qca956x_घड़ीs_init(pll_base);

	अगर (!clks[ATH79_CLK_MDIO])
		clks[ATH79_CLK_MDIO] = clks[ATH79_CLK_REF];

	अगर (of_clk_add_provider(np, of_clk_src_onecell_get, &clk_data)) अणु
		pr_err("%pOF: could not register clk provider\n", np);
		जाओ err_iounmap;
	पूर्ण

	वापस;

err_iounmap:
	iounmap(pll_base);

err_clk:
	clk_put(ref_clk);
पूर्ण

CLK_OF_DECLARE(ar7100_clk, "qca,ar7100-pll", ath79_घड़ीs_init_dt);
CLK_OF_DECLARE(ar7240_clk, "qca,ar7240-pll", ath79_घड़ीs_init_dt);
CLK_OF_DECLARE(ar9130_clk, "qca,ar9130-pll", ath79_घड़ीs_init_dt);
CLK_OF_DECLARE(ar9330_clk, "qca,ar9330-pll", ath79_घड़ीs_init_dt);
CLK_OF_DECLARE(ar9340_clk, "qca,ar9340-pll", ath79_घड़ीs_init_dt);
CLK_OF_DECLARE(ar9530_clk, "qca,qca9530-pll", ath79_घड़ीs_init_dt);
CLK_OF_DECLARE(ar9550_clk, "qca,qca9550-pll", ath79_घड़ीs_init_dt);
CLK_OF_DECLARE(ar9560_clk, "qca,qca9560-pll", ath79_घड़ीs_init_dt);
