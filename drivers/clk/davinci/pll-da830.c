<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PLL घड़ी descriptions क्रम TI DA830/OMAP-L137/AM17XX
 *
 * Copyright (C) 2018 David Lechner <david@lechnology.com>
 */

#समावेश <linux/clkdev.h>
#समावेश <linux/clk/davinci.h>
#समावेश <linux/bitops.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>

#समावेश "pll.h"

अटल स्थिर काष्ठा davinci_pll_clk_info da830_pll_info = अणु
	.name = "pll0",
	.pllm_mask = GENMASK(4, 0),
	.pllm_min = 4,
	.pllm_max = 32,
	.pllout_min_rate = 300000000,
	.pllout_max_rate = 600000000,
	.flags = PLL_HAS_CLKMODE | PLL_HAS_PREDIV | PLL_HAS_POSTDIV,
पूर्ण;

/*
 * NB: Technically, the घड़ीs flagged as SYSCLK_FIXED_DIV are "fixed ratio",
 * meaning that we could change the भागider as दीर्घ as we keep the correct
 * ratio between all of the घड़ीs, but we करोn't support that because there is
 * currently not a need क्रम it.
 */

SYSCLK(2, pll0_sysclk2, pll0_pllen, 5, SYSCLK_FIXED_DIV);
SYSCLK(3, pll0_sysclk3, pll0_pllen, 5, 0);
SYSCLK(4, pll0_sysclk4, pll0_pllen, 5, SYSCLK_FIXED_DIV);
SYSCLK(5, pll0_sysclk5, pll0_pllen, 5, 0);
SYSCLK(6, pll0_sysclk6, pll0_pllen, 5, SYSCLK_FIXED_DIV);
SYSCLK(7, pll0_sysclk7, pll0_pllen, 5, 0);

पूर्णांक da830_pll_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip)
अणु
	काष्ठा clk *clk;

	davinci_pll_clk_रेजिस्टर(dev, &da830_pll_info, "ref_clk", base, cfgchip);

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll0_sysclk2, base);
	clk_रेजिस्टर_clkdev(clk, "pll0_sysclk2", "da830-psc0");
	clk_रेजिस्टर_clkdev(clk, "pll0_sysclk2", "da830-psc1");

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll0_sysclk3, base);
	clk_रेजिस्टर_clkdev(clk, "pll0_sysclk3", "da830-psc0");

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll0_sysclk4, base);
	clk_रेजिस्टर_clkdev(clk, "pll0_sysclk4", "da830-psc0");
	clk_रेजिस्टर_clkdev(clk, "pll0_sysclk4", "da830-psc1");

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll0_sysclk5, base);
	clk_रेजिस्टर_clkdev(clk, "pll0_sysclk5", "da830-psc1");

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll0_sysclk6, base);
	clk_रेजिस्टर_clkdev(clk, "pll0_sysclk6", "da830-psc0");

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll0_sysclk7, base);

	clk = davinci_pll_auxclk_रेजिस्टर(dev, "pll0_auxclk", base);
	clk_रेजिस्टर_clkdev(clk, शून्य, "i2c_davinci.1");
	clk_रेजिस्टर_clkdev(clk, "timer0", शून्य);
	clk_रेजिस्टर_clkdev(clk, शून्य, "davinci-wdt");

	वापस 0;
पूर्ण
