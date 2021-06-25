<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/clk/clk-axm5516.c
 *
 * Provides घड़ी implementations क्रम three dअगरferent types of घड़ी devices on
 * the Axxia device: PLL घड़ी, a घड़ी भागider and a घड़ी mux.
 *
 * Copyright (C) 2014 LSI Corporation
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>
#समावेश <dt-bindings/घड़ी/lsi,axm5516-clks.h>


/**
 * काष्ठा axxia_clk - Common काष्ठा to all Axxia घड़ीs.
 * @hw: clk_hw क्रम the common clk framework
 * @regmap: Regmap क्रम the घड़ी control रेजिस्टरs
 */
काष्ठा axxia_clk अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
पूर्ण;
#घोषणा to_axxia_clk(_hw) container_of(_hw, काष्ठा axxia_clk, hw)

/**
 * काष्ठा axxia_pllclk - Axxia PLL generated घड़ी.
 * @aclk: Common काष्ठा
 * @reg: Offset पूर्णांकo regmap क्रम PLL control रेजिस्टर
 */
काष्ठा axxia_pllclk अणु
	काष्ठा axxia_clk aclk;
	u32 reg;
पूर्ण;
#घोषणा to_axxia_pllclk(_aclk) container_of(_aclk, काष्ठा axxia_pllclk, aclk)

/**
 * axxia_pllclk_recalc - Calculate the PLL generated घड़ी rate given the
 * parent घड़ी rate.
 */
अटल अचिन्हित दीर्घ
axxia_pllclk_recalc(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा axxia_clk *aclk = to_axxia_clk(hw);
	काष्ठा axxia_pllclk *pll = to_axxia_pllclk(aclk);
	अचिन्हित दीर्घ rate, fbभाग, refभाग, postभाग;
	u32 control;

	regmap_पढ़ो(aclk->regmap, pll->reg, &control);
	postभाग = ((control >> 0) & 0xf) + 1;
	fbभाग   = ((control >> 4) & 0xfff) + 3;
	refभाग  = ((control >> 16) & 0x1f) + 1;
	rate = (parent_rate / (refभाग * postभाग)) * fbभाग;

	वापस rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops axxia_pllclk_ops = अणु
	.recalc_rate = axxia_pllclk_recalc,
पूर्ण;

/**
 * काष्ठा axxia_भागclk - Axxia घड़ी भागider
 * @aclk: Common काष्ठा
 * @reg: Offset पूर्णांकo regmap क्रम PLL control रेजिस्टर
 * @shअगरt: Bit position क्रम भागider value
 * @width: Number of bits in भागider value
 */
काष्ठा axxia_भागclk अणु
	काष्ठा axxia_clk aclk;
	u32 reg;
	u32 shअगरt;
	u32 width;
पूर्ण;
#घोषणा to_axxia_भागclk(_aclk) container_of(_aclk, काष्ठा axxia_भागclk, aclk)

/**
 * axxia_भागclk_recalc_rate - Calculate घड़ी भागider output rage
 */
अटल अचिन्हित दीर्घ
axxia_भागclk_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा axxia_clk *aclk = to_axxia_clk(hw);
	काष्ठा axxia_भागclk *भागclk = to_axxia_भागclk(aclk);
	u32 ctrl, भाग;

	regmap_पढ़ो(aclk->regmap, भागclk->reg, &ctrl);
	भाग = 1 + ((ctrl >> भागclk->shअगरt) & ((1 << भागclk->width)-1));

	वापस parent_rate / भाग;
पूर्ण

अटल स्थिर काष्ठा clk_ops axxia_भागclk_ops = अणु
	.recalc_rate = axxia_भागclk_recalc_rate,
पूर्ण;

/**
 * काष्ठा axxia_clkmux - Axxia घड़ी mux
 * @aclk: Common काष्ठा
 * @reg: Offset पूर्णांकo regmap क्रम PLL control रेजिस्टर
 * @shअगरt: Bit position क्रम selection value
 * @width: Number of bits in selection value
 */
काष्ठा axxia_clkmux अणु
	काष्ठा axxia_clk aclk;
	u32 reg;
	u32 shअगरt;
	u32 width;
पूर्ण;
#घोषणा to_axxia_clkmux(_aclk) container_of(_aclk, काष्ठा axxia_clkmux, aclk)

/**
 * axxia_clkmux_get_parent - Return the index of selected parent घड़ी
 */
अटल u8 axxia_clkmux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा axxia_clk *aclk = to_axxia_clk(hw);
	काष्ठा axxia_clkmux *mux = to_axxia_clkmux(aclk);
	u32 ctrl, parent;

	regmap_पढ़ो(aclk->regmap, mux->reg, &ctrl);
	parent = (ctrl >> mux->shअगरt) & ((1 << mux->width) - 1);

	वापस (u8) parent;
पूर्ण

अटल स्थिर काष्ठा clk_ops axxia_clkmux_ops = अणु
	.get_parent = axxia_clkmux_get_parent,
पूर्ण;


/*
 * PLLs
 */

अटल काष्ठा axxia_pllclk clk_fab_pll = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_fab_pll",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_ref0"
		पूर्ण,
		.num_parents = 1,
		.ops = &axxia_pllclk_ops,
	पूर्ण,
	.reg   = 0x01800,
पूर्ण;

अटल काष्ठा axxia_pllclk clk_cpu_pll = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_cpu_pll",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_ref0"
		पूर्ण,
		.num_parents = 1,
		.ops = &axxia_pllclk_ops,
	पूर्ण,
	.reg   = 0x02000,
पूर्ण;

अटल काष्ठा axxia_pllclk clk_sys_pll = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_sys_pll",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_ref0"
		पूर्ण,
		.num_parents = 1,
		.ops = &axxia_pllclk_ops,
	पूर्ण,
	.reg   = 0x02800,
पूर्ण;

अटल काष्ठा axxia_pllclk clk_sm0_pll = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_sm0_pll",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_ref2"
		पूर्ण,
		.num_parents = 1,
		.ops = &axxia_pllclk_ops,
	पूर्ण,
	.reg   = 0x03000,
पूर्ण;

अटल काष्ठा axxia_pllclk clk_sm1_pll = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_sm1_pll",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_ref1"
		पूर्ण,
		.num_parents = 1,
		.ops = &axxia_pllclk_ops,
	पूर्ण,
	.reg   = 0x03800,
पूर्ण;

/*
 * Clock भागiders
 */

अटल काष्ठा axxia_भागclk clk_cpu0_भाग = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_cpu0_div",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_cpu_pll"
		पूर्ण,
		.num_parents = 1,
		.ops = &axxia_भागclk_ops,
	पूर्ण,
	.reg   = 0x10008,
	.shअगरt = 0,
	.width = 4,
पूर्ण;

अटल काष्ठा axxia_भागclk clk_cpu1_भाग = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_cpu1_div",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_cpu_pll"
		पूर्ण,
		.num_parents = 1,
		.ops = &axxia_भागclk_ops,
	पूर्ण,
	.reg   = 0x10008,
	.shअगरt = 4,
	.width = 4,
पूर्ण;

अटल काष्ठा axxia_भागclk clk_cpu2_भाग = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_cpu2_div",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_cpu_pll"
		पूर्ण,
		.num_parents = 1,
		.ops = &axxia_भागclk_ops,
	पूर्ण,
	.reg   = 0x10008,
	.shअगरt = 8,
	.width = 4,
पूर्ण;

अटल काष्ठा axxia_भागclk clk_cpu3_भाग = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_cpu3_div",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_cpu_pll"
		पूर्ण,
		.num_parents = 1,
		.ops = &axxia_भागclk_ops,
	पूर्ण,
	.reg   = 0x10008,
	.shअगरt = 12,
	.width = 4,
पूर्ण;

अटल काष्ठा axxia_भागclk clk_nrcp_भाग = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_nrcp_div",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_sys_pll"
		पूर्ण,
		.num_parents = 1,
		.ops = &axxia_भागclk_ops,
	पूर्ण,
	.reg   = 0x1000c,
	.shअगरt = 0,
	.width = 4,
पूर्ण;

अटल काष्ठा axxia_भागclk clk_sys_भाग = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_sys_div",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_sys_pll"
		पूर्ण,
		.num_parents = 1,
		.ops = &axxia_भागclk_ops,
	पूर्ण,
	.reg   = 0x1000c,
	.shअगरt = 4,
	.width = 4,
पूर्ण;

अटल काष्ठा axxia_भागclk clk_fab_भाग = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_fab_div",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_fab_pll"
		पूर्ण,
		.num_parents = 1,
		.ops = &axxia_भागclk_ops,
	पूर्ण,
	.reg   = 0x1000c,
	.shअगरt = 8,
	.width = 4,
पूर्ण;

अटल काष्ठा axxia_भागclk clk_per_भाग = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_per_div",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_sm1_pll"
		पूर्ण,
		.num_parents = 1,
		.ops = &axxia_भागclk_ops,
	पूर्ण,
	.reg   = 0x1000c,
	.shअगरt = 12,
	.width = 4,
पूर्ण;

अटल काष्ठा axxia_भागclk clk_mmc_भाग = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_mmc_div",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_sm1_pll"
		पूर्ण,
		.num_parents = 1,
		.ops = &axxia_भागclk_ops,
	पूर्ण,
	.reg   = 0x1000c,
	.shअगरt = 16,
	.width = 4,
पूर्ण;

/*
 * Clock MUXes
 */

अटल काष्ठा axxia_clkmux clk_cpu0_mux = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_cpu0",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_ref0",
			"clk_cpu_pll",
			"clk_cpu0_div",
			"clk_cpu0_div"
		पूर्ण,
		.num_parents = 4,
		.ops = &axxia_clkmux_ops,
	पूर्ण,
	.reg   = 0x10000,
	.shअगरt = 0,
	.width = 2,
पूर्ण;

अटल काष्ठा axxia_clkmux clk_cpu1_mux = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_cpu1",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_ref0",
			"clk_cpu_pll",
			"clk_cpu1_div",
			"clk_cpu1_div"
		पूर्ण,
		.num_parents = 4,
		.ops = &axxia_clkmux_ops,
	पूर्ण,
	.reg   = 0x10000,
	.shअगरt = 2,
	.width = 2,
पूर्ण;

अटल काष्ठा axxia_clkmux clk_cpu2_mux = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_cpu2",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_ref0",
			"clk_cpu_pll",
			"clk_cpu2_div",
			"clk_cpu2_div"
		पूर्ण,
		.num_parents = 4,
		.ops = &axxia_clkmux_ops,
	पूर्ण,
	.reg   = 0x10000,
	.shअगरt = 4,
	.width = 2,
पूर्ण;

अटल काष्ठा axxia_clkmux clk_cpu3_mux = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_cpu3",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_ref0",
			"clk_cpu_pll",
			"clk_cpu3_div",
			"clk_cpu3_div"
		पूर्ण,
		.num_parents = 4,
		.ops = &axxia_clkmux_ops,
	पूर्ण,
	.reg   = 0x10000,
	.shअगरt = 6,
	.width = 2,
पूर्ण;

अटल काष्ठा axxia_clkmux clk_nrcp_mux = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_nrcp",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_ref0",
			"clk_sys_pll",
			"clk_nrcp_div",
			"clk_nrcp_div"
		पूर्ण,
		.num_parents = 4,
		.ops = &axxia_clkmux_ops,
	पूर्ण,
	.reg   = 0x10004,
	.shअगरt = 0,
	.width = 2,
पूर्ण;

अटल काष्ठा axxia_clkmux clk_sys_mux = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_sys",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_ref0",
			"clk_sys_pll",
			"clk_sys_div",
			"clk_sys_div"
		पूर्ण,
		.num_parents = 4,
		.ops = &axxia_clkmux_ops,
	पूर्ण,
	.reg   = 0x10004,
	.shअगरt = 2,
	.width = 2,
पूर्ण;

अटल काष्ठा axxia_clkmux clk_fab_mux = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_fab",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_ref0",
			"clk_fab_pll",
			"clk_fab_div",
			"clk_fab_div"
		पूर्ण,
		.num_parents = 4,
		.ops = &axxia_clkmux_ops,
	पूर्ण,
	.reg   = 0x10004,
	.shअगरt = 4,
	.width = 2,
पूर्ण;

अटल काष्ठा axxia_clkmux clk_per_mux = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_per",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_ref1",
			"clk_per_div"
		पूर्ण,
		.num_parents = 2,
		.ops = &axxia_clkmux_ops,
	पूर्ण,
	.reg   = 0x10004,
	.shअगरt = 6,
	.width = 1,
पूर्ण;

अटल काष्ठा axxia_clkmux clk_mmc_mux = अणु
	.aclk.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk_mmc",
		.parent_names = (स्थिर अक्षर *[])अणु
			"clk_ref1",
			"clk_mmc_div"
		पूर्ण,
		.num_parents = 2,
		.ops = &axxia_clkmux_ops,
	पूर्ण,
	.reg   = 0x10004,
	.shअगरt = 9,
	.width = 1,
पूर्ण;

/* Table of all supported घड़ीs indexed by the घड़ी identअगरiers from the
 * device tree binding
 */
अटल काष्ठा axxia_clk *axmclk_घड़ीs[] = अणु
	[AXXIA_CLK_FAB_PLL]  = &clk_fab_pll.aclk,
	[AXXIA_CLK_CPU_PLL]  = &clk_cpu_pll.aclk,
	[AXXIA_CLK_SYS_PLL]  = &clk_sys_pll.aclk,
	[AXXIA_CLK_SM0_PLL]  = &clk_sm0_pll.aclk,
	[AXXIA_CLK_SM1_PLL]  = &clk_sm1_pll.aclk,
	[AXXIA_CLK_FAB_DIV]  = &clk_fab_भाग.aclk,
	[AXXIA_CLK_SYS_DIV]  = &clk_sys_भाग.aclk,
	[AXXIA_CLK_NRCP_DIV] = &clk_nrcp_भाग.aclk,
	[AXXIA_CLK_CPU0_DIV] = &clk_cpu0_भाग.aclk,
	[AXXIA_CLK_CPU1_DIV] = &clk_cpu1_भाग.aclk,
	[AXXIA_CLK_CPU2_DIV] = &clk_cpu2_भाग.aclk,
	[AXXIA_CLK_CPU3_DIV] = &clk_cpu3_भाग.aclk,
	[AXXIA_CLK_PER_DIV]  = &clk_per_भाग.aclk,
	[AXXIA_CLK_MMC_DIV]  = &clk_mmc_भाग.aclk,
	[AXXIA_CLK_FAB]      = &clk_fab_mux.aclk,
	[AXXIA_CLK_SYS]      = &clk_sys_mux.aclk,
	[AXXIA_CLK_NRCP]     = &clk_nrcp_mux.aclk,
	[AXXIA_CLK_CPU0]     = &clk_cpu0_mux.aclk,
	[AXXIA_CLK_CPU1]     = &clk_cpu1_mux.aclk,
	[AXXIA_CLK_CPU2]     = &clk_cpu2_mux.aclk,
	[AXXIA_CLK_CPU3]     = &clk_cpu3_mux.aclk,
	[AXXIA_CLK_PER]      = &clk_per_mux.aclk,
	[AXXIA_CLK_MMC]      = &clk_mmc_mux.aclk,
पूर्ण;

अटल काष्ठा clk_hw *
of_clk_axmclk_get(काष्ठा of_phandle_args *clkspec, व्योम *unused)
अणु
	अचिन्हित पूर्णांक idx = clkspec->args[0];

	अगर (idx >= ARRAY_SIZE(axmclk_घड़ीs)) अणु
		pr_err("%s: invalid index %u\n", __func__, idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस &axmclk_घड़ीs[idx]->hw;
पूर्ण

अटल स्थिर काष्ठा regmap_config axmclk_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x1fffc,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id axmclk_match_table[] = अणु
	अणु .compatible = "lsi,axm5516-clks" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, axmclk_match_table);

अटल पूर्णांक axmclk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *base;
	काष्ठा resource *res;
	पूर्णांक i, ret;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regmap *regmap;
	माप_प्रकार num_clks;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	regmap = devm_regmap_init_mmio(dev, base, &axmclk_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	num_clks = ARRAY_SIZE(axmclk_घड़ीs);
	pr_info("axmclk: supporting %zu clocks\n", num_clks);

	/* Update each entry with the allocated regmap and रेजिस्टर the घड़ी
	 * with the common घड़ी framework
	 */
	क्रम (i = 0; i < num_clks; i++) अणु
		axmclk_घड़ीs[i]->regmap = regmap;
		ret = devm_clk_hw_रेजिस्टर(dev, &axmclk_घड़ीs[i]->hw);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस of_clk_add_hw_provider(dev->of_node, of_clk_axmclk_get, शून्य);
पूर्ण

अटल पूर्णांक axmclk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	of_clk_del_provider(pdev->dev.of_node);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver axmclk_driver = अणु
	.probe		= axmclk_probe,
	.हटाओ		= axmclk_हटाओ,
	.driver		= अणु
		.name	= "clk-axm5516",
		.of_match_table = axmclk_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init axmclk_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&axmclk_driver);
पूर्ण
core_initcall(axmclk_init);

अटल व्योम __निकास axmclk_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&axmclk_driver);
पूर्ण
module_निकास(axmclk_निकास);

MODULE_DESCRIPTION("AXM5516 clock driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:clk-axm5516");
