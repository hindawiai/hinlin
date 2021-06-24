<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PLL घड़ी descriptions क्रम TI DM646X
 *
 * Copyright (C) 2018 David Lechner <david@lechnology.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/davinci.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>

#समावेश "pll.h"

अटल स्थिर काष्ठा davinci_pll_clk_info dm646x_pll1_info = अणु
	.name = "pll1",
	.pllm_mask = GENMASK(4, 0),
	.pllm_min = 14,
	.pllm_max = 32,
	.flags = PLL_HAS_CLKMODE,
पूर्ण;

SYSCLK(1, pll1_sysclk1, pll1_pllen, 4, SYSCLK_FIXED_DIV);
SYSCLK(2, pll1_sysclk2, pll1_pllen, 4, SYSCLK_FIXED_DIV);
SYSCLK(3, pll1_sysclk3, pll1_pllen, 4, SYSCLK_FIXED_DIV);
SYSCLK(4, pll1_sysclk4, pll1_pllen, 4, 0);
SYSCLK(5, pll1_sysclk5, pll1_pllen, 4, 0);
SYSCLK(6, pll1_sysclk6, pll1_pllen, 4, 0);
SYSCLK(8, pll1_sysclk8, pll1_pllen, 4, 0);
SYSCLK(9, pll1_sysclk9, pll1_pllen, 4, 0);

पूर्णांक dm646x_pll1_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip)
अणु
	काष्ठा clk *clk;

	davinci_pll_clk_रेजिस्टर(dev, &dm646x_pll1_info, "ref_clk", base, cfgchip);

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll1_sysclk1, base);
	clk_रेजिस्टर_clkdev(clk, "pll1_sysclk1", "dm646x-psc");

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll1_sysclk2, base);
	clk_रेजिस्टर_clkdev(clk, "pll1_sysclk2", "dm646x-psc");

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll1_sysclk3, base);
	clk_रेजिस्टर_clkdev(clk, "pll1_sysclk3", "dm646x-psc");
	clk_रेजिस्टर_clkdev(clk, शून्य, "davinci-wdt");

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll1_sysclk4, base);
	clk_रेजिस्टर_clkdev(clk, "pll1_sysclk4", "dm646x-psc");

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll1_sysclk5, base);
	clk_रेजिस्टर_clkdev(clk, "pll1_sysclk5", "dm646x-psc");

	davinci_pll_sysclk_रेजिस्टर(dev, &pll1_sysclk6, base);

	davinci_pll_sysclk_रेजिस्टर(dev, &pll1_sysclk8, base);

	davinci_pll_sysclk_रेजिस्टर(dev, &pll1_sysclk9, base);

	davinci_pll_sysclkbp_clk_रेजिस्टर(dev, "pll1_sysclkbp", base);

	davinci_pll_auxclk_रेजिस्टर(dev, "pll1_auxclk", base);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा davinci_pll_clk_info dm646x_pll2_info = अणु
	.name = "pll2",
	.pllm_mask = GENMASK(4, 0),
	.pllm_min = 14,
	.pllm_max = 32,
	.flags = 0,
पूर्ण;

SYSCLK(1, pll2_sysclk1, pll2_pllen, 4, SYSCLK_ALWAYS_ENABLED);

पूर्णांक dm646x_pll2_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip)
अणु
	davinci_pll_clk_रेजिस्टर(dev, &dm646x_pll2_info, "oscin", base, cfgchip);

	davinci_pll_sysclk_रेजिस्टर(dev, &pll2_sysclk1, base);

	वापस 0;
पूर्ण
