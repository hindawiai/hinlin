<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PLL घड़ी descriptions क्रम TI DM355
 *
 * Copyright (C) 2018 David Lechner <david@lechnology.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk/davinci.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>

#समावेश "pll.h"

अटल स्थिर काष्ठा davinci_pll_clk_info dm355_pll1_info = अणु
	.name = "pll1",
	.pllm_mask = GENMASK(7, 0),
	.pllm_min = 92,
	.pllm_max = 184,
	.flags = PLL_HAS_CLKMODE | PLL_HAS_PREDIV | PLL_PREDIV_ALWAYS_ENABLED |
		 PLL_PREDIV_FIXED8 | PLL_HAS_POSTDIV |
		 PLL_POSTDIV_ALWAYS_ENABLED | PLL_POSTDIV_FIXED_DIV,
पूर्ण;

SYSCLK(1, pll1_sysclk1, pll1_pllen, 5, SYSCLK_FIXED_DIV | SYSCLK_ALWAYS_ENABLED);
SYSCLK(2, pll1_sysclk2, pll1_pllen, 5, SYSCLK_FIXED_DIV | SYSCLK_ALWAYS_ENABLED);
SYSCLK(3, pll1_sysclk3, pll1_pllen, 5, SYSCLK_ALWAYS_ENABLED);
SYSCLK(4, pll1_sysclk4, pll1_pllen, 5, SYSCLK_ALWAYS_ENABLED);

पूर्णांक dm355_pll1_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip)
अणु
	काष्ठा clk *clk;

	davinci_pll_clk_रेजिस्टर(dev, &dm355_pll1_info, "ref_clk", base, cfgchip);

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll1_sysclk1, base);
	clk_रेजिस्टर_clkdev(clk, "pll1_sysclk1", "dm355-psc");

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll1_sysclk2, base);
	clk_रेजिस्टर_clkdev(clk, "pll1_sysclk2", "dm355-psc");

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll1_sysclk3, base);
	clk_रेजिस्टर_clkdev(clk, "pll1_sysclk3", "dm355-psc");

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll1_sysclk4, base);
	clk_रेजिस्टर_clkdev(clk, "pll1_sysclk4", "dm355-psc");

	clk = davinci_pll_auxclk_रेजिस्टर(dev, "pll1_auxclk", base);
	clk_रेजिस्टर_clkdev(clk, "pll1_auxclk", "dm355-psc");

	davinci_pll_sysclkbp_clk_रेजिस्टर(dev, "pll1_sysclkbp", base);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा davinci_pll_clk_info dm355_pll2_info = अणु
	.name = "pll2",
	.pllm_mask = GENMASK(7, 0),
	.pllm_min = 92,
	.pllm_max = 184,
	.flags = PLL_HAS_PREDIV | PLL_PREDIV_ALWAYS_ENABLED | PLL_HAS_POSTDIV |
		 PLL_POSTDIV_ALWAYS_ENABLED | PLL_POSTDIV_FIXED_DIV,
पूर्ण;

SYSCLK(1, pll2_sysclk1, pll2_pllen, 5, SYSCLK_FIXED_DIV | SYSCLK_ALWAYS_ENABLED);

पूर्णांक dm355_pll2_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip)
अणु
	davinci_pll_clk_रेजिस्टर(dev, &dm355_pll2_info, "oscin", base, cfgchip);

	davinci_pll_sysclk_रेजिस्टर(dev, &pll2_sysclk1, base);

	davinci_pll_sysclkbp_clk_रेजिस्टर(dev, "pll2_sysclkbp", base);

	वापस 0;
पूर्ण
