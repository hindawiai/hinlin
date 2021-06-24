<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PLL घड़ी driver क्रम Keystone devices
 *
 * Copyright (C) 2013 Texas Instruments Inc.
 *	Murali Karicheri <m-karicheri2@ti.com>
 *	Santosh Shilimkar <santosh.shilimkar@ti.com>
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of.h>
#समावेश <linux/module.h>

#घोषणा PLLM_LOW_MASK		0x3f
#घोषणा PLLM_HIGH_MASK		0x7ffc0
#घोषणा MAIN_PLLM_HIGH_MASK	0x7f000
#घोषणा PLLM_HIGH_SHIFT		6
#घोषणा PLLD_MASK		0x3f
#घोषणा CLKOD_MASK		0x780000
#घोषणा CLKOD_SHIFT		19

/**
 * काष्ठा clk_pll_data - pll data काष्ठाure
 * @has_pllctrl: If set to non zero, lower 6 bits of multiplier is in pllm
 *	रेजिस्टर of pll controller, अन्यथा it is in the pll_ctrl0((bit 11-6)
 * @phy_pllm: Physical address of PLLM in pll controller. Used when
 *	has_pllctrl is non zero.
 * @phy_pll_ctl0: Physical address of PLL ctrl0. This could be that of
 *	Main PLL or any other PLLs in the device such as ARM PLL, DDR PLL
 *	or PA PLL available on keystone2. These PLLs are controlled by
 *	this रेजिस्टर. Main PLL is controlled by a PLL controller.
 * @pllm: PLL रेजिस्टर map address क्रम multiplier bits
 * @pllod: PLL रेजिस्टर map address क्रम post भागider bits
 * @pll_ctl0: PLL controller map address
 * @pllm_lower_mask: multiplier lower mask
 * @pllm_upper_mask: multiplier upper mask
 * @pllm_upper_shअगरt: multiplier upper shअगरt
 * @plld_mask: भागider mask
 * @clkod_mask: output भागider mask
 * @clkod_shअगरt: output भागider shअगरt
 * @plld_mask: भागider mask
 * @postभाग: Fixed post भागider
 */
काष्ठा clk_pll_data अणु
	bool has_pllctrl;
	u32 phy_pllm;
	u32 phy_pll_ctl0;
	व्योम __iomem *pllm;
	व्योम __iomem *pllod;
	व्योम __iomem *pll_ctl0;
	u32 pllm_lower_mask;
	u32 pllm_upper_mask;
	u32 pllm_upper_shअगरt;
	u32 plld_mask;
	u32 clkod_mask;
	u32 clkod_shअगरt;
	u32 postभाग;
पूर्ण;

/**
 * काष्ठा clk_pll - Main pll घड़ी
 * @hw: clk_hw क्रम the pll
 * @pll_data: PLL driver specअगरic data
 */
काष्ठा clk_pll अणु
	काष्ठा clk_hw hw;
	काष्ठा clk_pll_data *pll_data;
पूर्ण;

#घोषणा to_clk_pll(_hw) container_of(_hw, काष्ठा clk_pll, hw)

अटल अचिन्हित दीर्घ clk_pllclk_recalc(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);
	काष्ठा clk_pll_data *pll_data = pll->pll_data;
	अचिन्हित दीर्घ rate = parent_rate;
	u32  mult = 0, preभाग, postभाग, val;

	/*
	 * get bits 0-5 of multiplier from pllctrl PLLM रेजिस्टर
	 * अगर has_pllctrl is non zero
	 */
	अगर (pll_data->has_pllctrl) अणु
		val = पढ़ोl(pll_data->pllm);
		mult = (val & pll_data->pllm_lower_mask);
	पूर्ण

	/* bit6-12 of PLLM is in Main PLL control रेजिस्टर */
	val = पढ़ोl(pll_data->pll_ctl0);
	mult |= ((val & pll_data->pllm_upper_mask)
			>> pll_data->pllm_upper_shअगरt);
	preभाग = (val & pll_data->plld_mask);

	अगर (!pll_data->has_pllctrl)
		/* पढ़ो post भागider from od bits*/
		postभाग = ((val & pll_data->clkod_mask) >>
				 pll_data->clkod_shअगरt) + 1;
	अन्यथा अगर (pll_data->pllod) अणु
		postभाग = पढ़ोl(pll_data->pllod);
		postभाग = ((postभाग & pll_data->clkod_mask) >>
				pll_data->clkod_shअगरt) + 1;
	पूर्ण अन्यथा
		postभाग = pll_data->postभाग;

	rate /= (preभाग + 1);
	rate = (rate * (mult + 1));
	rate /= postभाग;

	वापस rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_pll_ops = अणु
	.recalc_rate = clk_pllclk_recalc,
पूर्ण;

अटल काष्ठा clk *clk_रेजिस्टर_pll(काष्ठा device *dev,
			स्थिर अक्षर *name,
			स्थिर अक्षर *parent_name,
			काष्ठा clk_pll_data *pll_data)
अणु
	काष्ठा clk_init_data init;
	काष्ठा clk_pll *pll;
	काष्ठा clk *clk;

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &clk_pll_ops;
	init.flags = 0;
	init.parent_names = (parent_name ? &parent_name : शून्य);
	init.num_parents = (parent_name ? 1 : 0);

	pll->pll_data	= pll_data;
	pll->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &pll->hw);
	अगर (IS_ERR(clk))
		जाओ out;

	वापस clk;
out:
	kमुक्त(pll);
	वापस शून्य;
पूर्ण

/**
 * _of_pll_clk_init - PLL initialisation via DT
 * @node: device tree node क्रम this घड़ी
 * @pllctrl: If true, lower 6 bits of multiplier is in pllm रेजिस्टर of
 *		pll controller, अन्यथा it is in the control रेजिस्टर0(bit 11-6)
 */
अटल व्योम __init _of_pll_clk_init(काष्ठा device_node *node, bool pllctrl)
अणु
	काष्ठा clk_pll_data *pll_data;
	स्थिर अक्षर *parent_name;
	काष्ठा clk *clk;
	पूर्णांक i;

	pll_data = kzalloc(माप(*pll_data), GFP_KERNEL);
	अगर (!pll_data) अणु
		pr_err("%s: Out of memory\n", __func__);
		वापस;
	पूर्ण

	parent_name = of_clk_get_parent_name(node, 0);
	अगर (of_property_पढ़ो_u32(node, "fixed-postdiv",	&pll_data->postभाग)) अणु
		/* assume the PLL has output भागider रेजिस्टर bits */
		pll_data->clkod_mask = CLKOD_MASK;
		pll_data->clkod_shअगरt = CLKOD_SHIFT;

		/*
		 * Check अगर there is an post-भागider रेजिस्टर. If not
		 * assume od bits are part of control रेजिस्टर.
		 */
		i = of_property_match_string(node, "reg-names",
					     "post-divider");
		pll_data->pllod = of_iomap(node, i);
	पूर्ण

	i = of_property_match_string(node, "reg-names", "control");
	pll_data->pll_ctl0 = of_iomap(node, i);
	अगर (!pll_data->pll_ctl0) अणु
		pr_err("%s: ioremap failed\n", __func__);
		iounmap(pll_data->pllod);
		जाओ out;
	पूर्ण

	pll_data->pllm_lower_mask = PLLM_LOW_MASK;
	pll_data->pllm_upper_shअगरt = PLLM_HIGH_SHIFT;
	pll_data->plld_mask = PLLD_MASK;
	pll_data->has_pllctrl = pllctrl;
	अगर (!pll_data->has_pllctrl) अणु
		pll_data->pllm_upper_mask = PLLM_HIGH_MASK;
	पूर्ण अन्यथा अणु
		pll_data->pllm_upper_mask = MAIN_PLLM_HIGH_MASK;
		i = of_property_match_string(node, "reg-names", "multiplier");
		pll_data->pllm = of_iomap(node, i);
		अगर (!pll_data->pllm) अणु
			iounmap(pll_data->pll_ctl0);
			iounmap(pll_data->pllod);
			जाओ out;
		पूर्ण
	पूर्ण

	clk = clk_रेजिस्टर_pll(शून्य, node->name, parent_name, pll_data);
	अगर (clk) अणु
		of_clk_add_provider(node, of_clk_src_simple_get, clk);
		वापस;
	पूर्ण

out:
	pr_err("%s: error initializing pll %pOFn\n", __func__, node);
	kमुक्त(pll_data);
पूर्ण

/**
 * of_keystone_pll_clk_init - PLL initialisation DT wrapper
 * @node: device tree node क्रम this घड़ी
 */
अटल व्योम __init of_keystone_pll_clk_init(काष्ठा device_node *node)
अणु
	_of_pll_clk_init(node, false);
पूर्ण
CLK_OF_DECLARE(keystone_pll_घड़ी, "ti,keystone,pll-clock",
					of_keystone_pll_clk_init);

/**
 * of_keystone_मुख्य_pll_clk_init - Main PLL initialisation DT wrapper
 * @node: device tree node क्रम this घड़ी
 */
अटल व्योम __init of_keystone_मुख्य_pll_clk_init(काष्ठा device_node *node)
अणु
	_of_pll_clk_init(node, true);
पूर्ण
CLK_OF_DECLARE(keystone_मुख्य_pll_घड़ी, "ti,keystone,main-pll-clock",
						of_keystone_मुख्य_pll_clk_init);

/**
 * of_pll_भाग_clk_init - PLL भागider setup function
 * @node: device tree node क्रम this घड़ी
 */
अटल व्योम __init of_pll_भाग_clk_init(काष्ठा device_node *node)
अणु
	स्थिर अक्षर *parent_name;
	व्योम __iomem *reg;
	u32 shअगरt, mask;
	काष्ठा clk *clk;
	स्थिर अक्षर *clk_name = node->name;

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);
	reg = of_iomap(node, 0);
	अगर (!reg) अणु
		pr_err("%s: ioremap failed\n", __func__);
		वापस;
	पूर्ण

	parent_name = of_clk_get_parent_name(node, 0);
	अगर (!parent_name) अणु
		pr_err("%s: missing parent clock\n", __func__);
		iounmap(reg);
		वापस;
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "bit-shift", &shअगरt)) अणु
		pr_err("%s: missing 'shift' property\n", __func__);
		iounmap(reg);
		वापस;
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "bit-mask", &mask)) अणु
		pr_err("%s: missing 'bit-mask' property\n", __func__);
		iounmap(reg);
		वापस;
	पूर्ण

	clk = clk_रेजिस्टर_भागider(शून्य, clk_name, parent_name, 0, reg, shअगरt,
				 mask, 0, शून्य);
	अगर (clk) अणु
		of_clk_add_provider(node, of_clk_src_simple_get, clk);
	पूर्ण अन्यथा अणु
		pr_err("%s: error registering divider %s\n", __func__, clk_name);
		iounmap(reg);
	पूर्ण
पूर्ण
CLK_OF_DECLARE(pll_भागider_घड़ी, "ti,keystone,pll-divider-clock", of_pll_भाग_clk_init);

/**
 * of_pll_mux_clk_init - PLL mux setup function
 * @node: device tree node क्रम this घड़ी
 */
अटल व्योम __init of_pll_mux_clk_init(काष्ठा device_node *node)
अणु
	व्योम __iomem *reg;
	u32 shअगरt, mask;
	काष्ठा clk *clk;
	स्थिर अक्षर *parents[2];
	स्थिर अक्षर *clk_name = node->name;

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);
	reg = of_iomap(node, 0);
	अगर (!reg) अणु
		pr_err("%s: ioremap failed\n", __func__);
		वापस;
	पूर्ण

	of_clk_parent_fill(node, parents, 2);
	अगर (!parents[0] || !parents[1]) अणु
		pr_err("%s: missing parent clocks\n", __func__);
		वापस;
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "bit-shift", &shअगरt)) अणु
		pr_err("%s: missing 'shift' property\n", __func__);
		वापस;
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "bit-mask", &mask)) अणु
		pr_err("%s: missing 'bit-mask' property\n", __func__);
		वापस;
	पूर्ण

	clk = clk_रेजिस्टर_mux(शून्य, clk_name, (स्थिर अक्षर **)&parents,
				ARRAY_SIZE(parents) , 0, reg, shअगरt, mask,
				0, शून्य);
	अगर (clk)
		of_clk_add_provider(node, of_clk_src_simple_get, clk);
	अन्यथा
		pr_err("%s: error registering mux %s\n", __func__, clk_name);
पूर्ण
CLK_OF_DECLARE(pll_mux_घड़ी, "ti,keystone,pll-mux-clock", of_pll_mux_clk_init);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PLL clock driver for Keystone devices");
MODULE_AUTHOR("Murali Karicheri <m-karicheri2@ti.com>");
MODULE_AUTHOR("Santosh Shilimkar <santosh.shilimkar@ti.com>");
