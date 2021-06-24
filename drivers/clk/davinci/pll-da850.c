<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PLL घड़ी descriptions क्रम TI DA850/OMAP-L138/AM18XX
 *
 * Copyright (C) 2018 David Lechner <david@lechnology.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/davinci.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/da8xx-cfgchip.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of.h>
#समावेश <linux/types.h>

#समावेश "pll.h"

#घोषणा OCSEL_OCSRC_OSCIN		0x14
#घोषणा OCSEL_OCSRC_PLL0_SYSCLK(n)	(0x16 + (n))
#घोषणा OCSEL_OCSRC_PLL1_OBSCLK		0x1e
#घोषणा OCSEL_OCSRC_PLL1_SYSCLK(n)	(0x16 + (n))

अटल स्थिर काष्ठा davinci_pll_clk_info da850_pll0_info = अणु
	.name = "pll0",
	.unlock_reg = CFGCHIP(0),
	.unlock_mask = CFGCHIP0_PLL_MASTER_LOCK,
	.pllm_mask = GENMASK(4, 0),
	.pllm_min = 4,
	.pllm_max = 32,
	.pllout_min_rate = 300000000,
	.pllout_max_rate = 600000000,
	.flags = PLL_HAS_CLKMODE | PLL_HAS_PREDIV | PLL_HAS_POSTDIV |
		 PLL_HAS_EXTCLKSRC,
पूर्ण;

/*
 * NB: Technically, the घड़ीs flagged as SYSCLK_FIXED_DIV are "fixed ratio",
 * meaning that we could change the भागider as दीर्घ as we keep the correct
 * ratio between all of the घड़ीs, but we करोn't support that because there is
 * currently not a need क्रम it.
 */

SYSCLK(1, pll0_sysclk1, pll0_pllen, 5, SYSCLK_FIXED_DIV);
SYSCLK(2, pll0_sysclk2, pll0_pllen, 5, SYSCLK_FIXED_DIV);
SYSCLK(3, pll0_sysclk3, pll0_pllen, 5, 0);
SYSCLK(4, pll0_sysclk4, pll0_pllen, 5, SYSCLK_FIXED_DIV);
SYSCLK(5, pll0_sysclk5, pll0_pllen, 5, 0);
SYSCLK(6, pll0_sysclk6, pll0_pllen, 5, SYSCLK_ARM_RATE | SYSCLK_FIXED_DIV);
SYSCLK(7, pll0_sysclk7, pll0_pllen, 5, 0);

अटल स्थिर अक्षर * स्थिर da850_pll0_obsclk_parent_names[] = अणु
	"oscin",
	"pll0_sysclk1",
	"pll0_sysclk2",
	"pll0_sysclk3",
	"pll0_sysclk4",
	"pll0_sysclk5",
	"pll0_sysclk6",
	"pll0_sysclk7",
	"pll1_obsclk",
पूर्ण;

अटल u32 da850_pll0_obsclk_table[] = अणु
	OCSEL_OCSRC_OSCIN,
	OCSEL_OCSRC_PLL0_SYSCLK(1),
	OCSEL_OCSRC_PLL0_SYSCLK(2),
	OCSEL_OCSRC_PLL0_SYSCLK(3),
	OCSEL_OCSRC_PLL0_SYSCLK(4),
	OCSEL_OCSRC_PLL0_SYSCLK(5),
	OCSEL_OCSRC_PLL0_SYSCLK(6),
	OCSEL_OCSRC_PLL0_SYSCLK(7),
	OCSEL_OCSRC_PLL1_OBSCLK,
पूर्ण;

अटल स्थिर काष्ठा davinci_pll_obsclk_info da850_pll0_obsclk_info = अणु
	.name = "pll0_obsclk",
	.parent_names = da850_pll0_obsclk_parent_names,
	.num_parents = ARRAY_SIZE(da850_pll0_obsclk_parent_names),
	.table = da850_pll0_obsclk_table,
	.ocsrc_mask = GENMASK(4, 0),
पूर्ण;

पूर्णांक da850_pll0_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip)
अणु
	काष्ठा clk *clk;

	davinci_pll_clk_रेजिस्टर(dev, &da850_pll0_info, "ref_clk", base, cfgchip);

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll0_sysclk1, base);
	clk_रेजिस्टर_clkdev(clk, "pll0_sysclk1", "da850-psc0");

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll0_sysclk2, base);
	clk_रेजिस्टर_clkdev(clk, "pll0_sysclk2", "da850-psc0");
	clk_रेजिस्टर_clkdev(clk, "pll0_sysclk2", "da850-psc1");
	clk_रेजिस्टर_clkdev(clk, "pll0_sysclk2", "da850-async3-clksrc");

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll0_sysclk3, base);
	clk_रेजिस्टर_clkdev(clk, "pll0_sysclk3", "da850-async1-clksrc");

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll0_sysclk4, base);
	clk_रेजिस्टर_clkdev(clk, "pll0_sysclk4", "da850-psc0");
	clk_रेजिस्टर_clkdev(clk, "pll0_sysclk4", "da850-psc1");

	davinci_pll_sysclk_रेजिस्टर(dev, &pll0_sysclk5, base);

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll0_sysclk6, base);
	clk_रेजिस्टर_clkdev(clk, "pll0_sysclk6", "da850-psc0");

	davinci_pll_sysclk_रेजिस्टर(dev, &pll0_sysclk7, base);

	davinci_pll_auxclk_रेजिस्टर(dev, "pll0_auxclk", base);

	clk = clk_रेजिस्टर_fixed_factor(dev, "async2", "pll0_auxclk",
					CLK_IS_CRITICAL, 1, 1);

	clk_रेजिस्टर_clkdev(clk, शून्य, "i2c_davinci.1");
	clk_रेजिस्टर_clkdev(clk, "timer0", शून्य);
	clk_रेजिस्टर_clkdev(clk, शून्य, "davinci-wdt");

	davinci_pll_obsclk_रेजिस्टर(dev, &da850_pll0_obsclk_info, base);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा davinci_pll_sysclk_info *da850_pll0_sysclk_info[] = अणु
	&pll0_sysclk1,
	&pll0_sysclk2,
	&pll0_sysclk3,
	&pll0_sysclk4,
	&pll0_sysclk5,
	&pll0_sysclk6,
	&pll0_sysclk7,
	शून्य
पूर्ण;

व्योम of_da850_pll0_init(काष्ठा device_node *node)
अणु
	व्योम __iomem *base;
	काष्ठा regmap *cfgchip;

	base = of_iomap(node, 0);
	अगर (!base) अणु
		pr_err("%s: ioremap failed\n", __func__);
		वापस;
	पूर्ण

	cfgchip = syscon_regmap_lookup_by_compatible("ti,da830-cfgchip");

	of_davinci_pll_init(शून्य, node, &da850_pll0_info,
			    &da850_pll0_obsclk_info,
			    da850_pll0_sysclk_info, 7, base, cfgchip);
पूर्ण

अटल स्थिर काष्ठा davinci_pll_clk_info da850_pll1_info = अणु
	.name = "pll1",
	.unlock_reg = CFGCHIP(3),
	.unlock_mask = CFGCHIP3_PLL1_MASTER_LOCK,
	.pllm_mask = GENMASK(4, 0),
	.pllm_min = 4,
	.pllm_max = 32,
	.pllout_min_rate = 300000000,
	.pllout_max_rate = 600000000,
	.flags = PLL_HAS_POSTDIV,
पूर्ण;

SYSCLK(1, pll1_sysclk1, pll1_pllen, 5, SYSCLK_ALWAYS_ENABLED);
SYSCLK(2, pll1_sysclk2, pll1_pllen, 5, 0);
SYSCLK(3, pll1_sysclk3, pll1_pllen, 5, 0);

अटल स्थिर अक्षर * स्थिर da850_pll1_obsclk_parent_names[] = अणु
	"oscin",
	"pll1_sysclk1",
	"pll1_sysclk2",
	"pll1_sysclk3",
पूर्ण;

अटल u32 da850_pll1_obsclk_table[] = अणु
	OCSEL_OCSRC_OSCIN,
	OCSEL_OCSRC_PLL1_SYSCLK(1),
	OCSEL_OCSRC_PLL1_SYSCLK(2),
	OCSEL_OCSRC_PLL1_SYSCLK(3),
पूर्ण;

अटल स्थिर काष्ठा davinci_pll_obsclk_info da850_pll1_obsclk_info = अणु
	.name = "pll1_obsclk",
	.parent_names = da850_pll1_obsclk_parent_names,
	.num_parents = ARRAY_SIZE(da850_pll1_obsclk_parent_names),
	.table = da850_pll1_obsclk_table,
	.ocsrc_mask = GENMASK(4, 0),
पूर्ण;

पूर्णांक da850_pll1_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip)
अणु
	काष्ठा clk *clk;

	davinci_pll_clk_रेजिस्टर(dev, &da850_pll1_info, "oscin", base, cfgchip);

	davinci_pll_sysclk_रेजिस्टर(dev, &pll1_sysclk1, base);

	clk = davinci_pll_sysclk_रेजिस्टर(dev, &pll1_sysclk2, base);
	clk_रेजिस्टर_clkdev(clk, "pll1_sysclk2", "da850-async3-clksrc");

	davinci_pll_sysclk_रेजिस्टर(dev, &pll1_sysclk3, base);

	davinci_pll_obsclk_रेजिस्टर(dev, &da850_pll1_obsclk_info, base);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा davinci_pll_sysclk_info *da850_pll1_sysclk_info[] = अणु
	&pll1_sysclk1,
	&pll1_sysclk2,
	&pll1_sysclk3,
	शून्य
पूर्ण;

पूर्णांक of_da850_pll1_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip)
अणु
	वापस of_davinci_pll_init(dev, dev->of_node, &da850_pll1_info,
				   &da850_pll1_obsclk_info,
				   da850_pll1_sysclk_info, 3, base, cfgchip);
पूर्ण
