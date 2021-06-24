<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PLL घड़ी descriptions क्रम TI DM644X
 *
 * Copyright (C) 2018 David Lechner <david@lechnology.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk/davinci.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>

#समावेश "pll.h"

अटल स्थिर काष्ठा davinci_pll_clk_info dm644x_pll1_info = अणु
	.name = "pll1",
	.pllm_mask = GENMASK(4, 0),
	.pllm_min = 1,
	.pllm_max = 32,
	.pllout_min_rate = 400000000,
	.pllout_max_rate = 600000000, /* 810MHz @ 1.3V, -810 only */
	.flags = PLL_HAS_CLKMODE | PLL_HAS_POSTDIV,
पूर्ण;

SYSCLK(1, pll1_sysclk1, pll1_pllen, 4, SYSCLK_FIXED_DIV);
SYSCLK(2, pll1_sysclk2, pll1_pllen, 4, SYSCLK_FIXED_DIV);
SYSCLK(3, pll1_sysclk3, pll1_pllen, 4, SYSCLK_FIXED_DIV);
SYSCLK(5, pll1_sysclk5, pll1_pllen, 4, SYSCLK_FIXED_DIV);

पूर्णांक dm644x_pll1_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip)
अणु
	काष्ठा clk *clk;

	davinci_pll_clk_रेजिस्टर(dev, &dm644x_pll1_info, "ref_clk", base, cfgchip);

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll1_sysclk1, base);
	clk_रेजिस्टर_clkdev(clk, "pll1_sysclk1", "dm644x-psc");

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll1_sysclk2, base);
	clk_रेजिस्टर_clkdev(clk, "pll1_sysclk2", "dm644x-psc");

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll1_sysclk3, base);
	clk_रेजिस्टर_clkdev(clk, "pll1_sysclk3", "dm644x-psc");

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll1_sysclk5, base);
	clk_रेजिस्टर_clkdev(clk, "pll1_sysclk5", "dm644x-psc");

	clk = davinci_pll_auxclk_रेजिस्टर(dev, "pll1_auxclk", base);
	clk_रेजिस्टर_clkdev(clk, "pll1_auxclk", "dm644x-psc");

	davinci_pll_sysclkbp_clk_रेजिस्टर(dev, "pll1_sysclkbp", base);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा davinci_pll_clk_info dm644x_pll2_info = अणु
	.name = "pll2",
	.pllm_mask = GENMASK(4, 0),
	.pllm_min = 1,
	.pllm_max = 32,
	.pllout_min_rate = 400000000,
	.pllout_max_rate = 900000000,
	.flags = PLL_HAS_POSTDIV | PLL_POSTDIV_FIXED_DIV,
पूर्ण;

SYSCLK(1, pll2_sysclk1, pll2_pllen, 4, 0);
SYSCLK(2, pll2_sysclk2, pll2_pllen, 4, 0);

पूर्णांक dm644x_pll2_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip)
अणु
	davinci_pll_clk_रेजिस्टर(dev, &dm644x_pll2_info, "oscin", base, cfgchip);

	davinci_pll_sysclk_रेजिस्टर(dev, &pll2_sysclk1, base);

	davinci_pll_sysclk_रेजिस्टर(dev, &pll2_sysclk2, base);

	davinci_pll_sysclkbp_clk_रेजिस्टर(dev, "pll2_sysclkbp", base);

	वापस 0;
पूर्ण
