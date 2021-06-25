<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Clock driver क्रम DA8xx/AM17xx/AM18xx/OMAP-L13x CFGCHIP
 *
 * Copyright (C) 2018 David Lechner <david@lechnology.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/da8xx-cfgchip.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_data/clk-da8xx-cfgchip.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

/* --- Gate घड़ीs --- */

#घोषणा DA8XX_GATE_CLOCK_IS_DIV4P5	BIT(1)

काष्ठा da8xx_cfgchip_gate_clk_info अणु
	स्थिर अक्षर *name;
	u32 cfgchip;
	u32 bit;
	u32 flags;
पूर्ण;

काष्ठा da8xx_cfgchip_gate_clk अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	u32 reg;
	u32 mask;
पूर्ण;

#घोषणा to_da8xx_cfgchip_gate_clk(_hw) \
	container_of((_hw), काष्ठा da8xx_cfgchip_gate_clk, hw)

अटल पूर्णांक da8xx_cfgchip_gate_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा da8xx_cfgchip_gate_clk *clk = to_da8xx_cfgchip_gate_clk(hw);

	वापस regmap_ग_लिखो_bits(clk->regmap, clk->reg, clk->mask, clk->mask);
पूर्ण

अटल व्योम da8xx_cfgchip_gate_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा da8xx_cfgchip_gate_clk *clk = to_da8xx_cfgchip_gate_clk(hw);

	regmap_ग_लिखो_bits(clk->regmap, clk->reg, clk->mask, 0);
पूर्ण

अटल पूर्णांक da8xx_cfgchip_gate_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा da8xx_cfgchip_gate_clk *clk = to_da8xx_cfgchip_gate_clk(hw);
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(clk->regmap, clk->reg, &val);

	वापस !!(val & clk->mask);
पूर्ण

अटल अचिन्हित दीर्घ da8xx_cfgchip_भाग4p5_recalc_rate(काष्ठा clk_hw *hw,
						      अचिन्हित दीर्घ parent_rate)
अणु
	/* this घड़ी भागides by 4.5 */
	वापस parent_rate * 2 / 9;
पूर्ण

अटल स्थिर काष्ठा clk_ops da8xx_cfgchip_gate_clk_ops = अणु
	.enable		= da8xx_cfgchip_gate_clk_enable,
	.disable	= da8xx_cfgchip_gate_clk_disable,
	.is_enabled	= da8xx_cfgchip_gate_clk_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा clk_ops da8xx_cfgchip_भाग4p5_clk_ops = अणु
	.enable		= da8xx_cfgchip_gate_clk_enable,
	.disable	= da8xx_cfgchip_gate_clk_disable,
	.is_enabled	= da8xx_cfgchip_gate_clk_is_enabled,
	.recalc_rate	= da8xx_cfgchip_भाग4p5_recalc_rate,
पूर्ण;

अटल काष्ठा da8xx_cfgchip_gate_clk * __init
da8xx_cfgchip_gate_clk_रेजिस्टर(काष्ठा device *dev,
				स्थिर काष्ठा da8xx_cfgchip_gate_clk_info *info,
				काष्ठा regmap *regmap)
अणु
	काष्ठा clk *parent;
	स्थिर अक्षर *parent_name;
	काष्ठा da8xx_cfgchip_gate_clk *gate;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	parent = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(parent))
		वापस ERR_CAST(parent);

	parent_name = __clk_get_name(parent);

	gate = devm_kzalloc(dev, माप(*gate), GFP_KERNEL);
	अगर (!gate)
		वापस ERR_PTR(-ENOMEM);

	init.name = info->name;
	अगर (info->flags & DA8XX_GATE_CLOCK_IS_DIV4P5)
		init.ops = &da8xx_cfgchip_भाग4p5_clk_ops;
	अन्यथा
		init.ops = &da8xx_cfgchip_gate_clk_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = 0;

	gate->hw.init = &init;
	gate->regmap = regmap;
	gate->reg = info->cfgchip;
	gate->mask = info->bit;

	ret = devm_clk_hw_रेजिस्टर(dev, &gate->hw);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	वापस gate;
पूर्ण

अटल स्थिर काष्ठा da8xx_cfgchip_gate_clk_info da8xx_tbclksync_info __initस्थिर = अणु
	.name = "ehrpwm_tbclk",
	.cfgchip = CFGCHIP(1),
	.bit = CFGCHIP1_TBCLKSYNC,
पूर्ण;

अटल पूर्णांक __init da8xx_cfgchip_रेजिस्टर_tbclk(काष्ठा device *dev,
					       काष्ठा regmap *regmap)
अणु
	काष्ठा da8xx_cfgchip_gate_clk *gate;

	gate = da8xx_cfgchip_gate_clk_रेजिस्टर(dev, &da8xx_tbclksync_info,
					       regmap);
	अगर (IS_ERR(gate))
		वापस PTR_ERR(gate);

	clk_hw_रेजिस्टर_clkdev(&gate->hw, "tbclk", "ehrpwm.0");
	clk_hw_रेजिस्टर_clkdev(&gate->hw, "tbclk", "ehrpwm.1");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा da8xx_cfgchip_gate_clk_info da8xx_भाग4p5ena_info __initस्थिर = अणु
	.name = "div4.5",
	.cfgchip = CFGCHIP(3),
	.bit = CFGCHIP3_DIV45PENA,
	.flags = DA8XX_GATE_CLOCK_IS_DIV4P5,
पूर्ण;

अटल पूर्णांक __init da8xx_cfgchip_रेजिस्टर_भाग4p5(काष्ठा device *dev,
						काष्ठा regmap *regmap)
अणु
	काष्ठा da8xx_cfgchip_gate_clk *gate;

	gate = da8xx_cfgchip_gate_clk_रेजिस्टर(dev, &da8xx_भाग4p5ena_info, regmap);

	वापस PTR_ERR_OR_ZERO(gate);
पूर्ण

अटल पूर्णांक __init
of_da8xx_cfgchip_gate_clk_init(काष्ठा device *dev,
			       स्थिर काष्ठा da8xx_cfgchip_gate_clk_info *info,
			       काष्ठा regmap *regmap)
अणु
	काष्ठा da8xx_cfgchip_gate_clk *gate;

	gate = da8xx_cfgchip_gate_clk_रेजिस्टर(dev, info, regmap);
	अगर (IS_ERR(gate))
		वापस PTR_ERR(gate);

	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get, gate);
पूर्ण

अटल पूर्णांक __init of_da8xx_tbclksync_init(काष्ठा device *dev,
					  काष्ठा regmap *regmap)
अणु
	वापस of_da8xx_cfgchip_gate_clk_init(dev, &da8xx_tbclksync_info, regmap);
पूर्ण

अटल पूर्णांक __init of_da8xx_भाग4p5ena_init(काष्ठा device *dev,
					  काष्ठा regmap *regmap)
अणु
	वापस of_da8xx_cfgchip_gate_clk_init(dev, &da8xx_भाग4p5ena_info, regmap);
पूर्ण

/* --- MUX घड़ीs --- */

काष्ठा da8xx_cfgchip_mux_clk_info अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent0;
	स्थिर अक्षर *parent1;
	u32 cfgchip;
	u32 bit;
पूर्ण;

काष्ठा da8xx_cfgchip_mux_clk अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	u32 reg;
	u32 mask;
पूर्ण;

#घोषणा to_da8xx_cfgchip_mux_clk(_hw) \
	container_of((_hw), काष्ठा da8xx_cfgchip_mux_clk, hw)

अटल पूर्णांक da8xx_cfgchip_mux_clk_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा da8xx_cfgchip_mux_clk *clk = to_da8xx_cfgchip_mux_clk(hw);
	अचिन्हित पूर्णांक val = index ? clk->mask : 0;

	वापस regmap_ग_लिखो_bits(clk->regmap, clk->reg, clk->mask, val);
पूर्ण

अटल u8 da8xx_cfgchip_mux_clk_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा da8xx_cfgchip_mux_clk *clk = to_da8xx_cfgchip_mux_clk(hw);
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(clk->regmap, clk->reg, &val);

	वापस (val & clk->mask) ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops da8xx_cfgchip_mux_clk_ops = अणु
	.set_parent	= da8xx_cfgchip_mux_clk_set_parent,
	.get_parent	= da8xx_cfgchip_mux_clk_get_parent,
पूर्ण;

अटल काष्ठा da8xx_cfgchip_mux_clk * __init
da8xx_cfgchip_mux_clk_रेजिस्टर(काष्ठा device *dev,
			       स्थिर काष्ठा da8xx_cfgchip_mux_clk_info *info,
			       काष्ठा regmap *regmap)
अणु
	स्थिर अक्षर * स्थिर parent_names[] = अणु info->parent0, info->parent1 पूर्ण;
	काष्ठा da8xx_cfgchip_mux_clk *mux;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	mux = devm_kzalloc(dev, माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस ERR_PTR(-ENOMEM);

	init.name = info->name;
	init.ops = &da8xx_cfgchip_mux_clk_ops;
	init.parent_names = parent_names;
	init.num_parents = 2;
	init.flags = 0;

	mux->hw.init = &init;
	mux->regmap = regmap;
	mux->reg = info->cfgchip;
	mux->mask = info->bit;

	ret = devm_clk_hw_रेजिस्टर(dev, &mux->hw);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	वापस mux;
पूर्ण

अटल स्थिर काष्ठा da8xx_cfgchip_mux_clk_info da850_async1_info __initस्थिर = अणु
	.name = "async1",
	.parent0 = "pll0_sysclk3",
	.parent1 = "div4.5",
	.cfgchip = CFGCHIP(3),
	.bit = CFGCHIP3_EMA_CLKSRC,
पूर्ण;

अटल पूर्णांक __init da8xx_cfgchip_रेजिस्टर_async1(काष्ठा device *dev,
						काष्ठा regmap *regmap)
अणु
	काष्ठा da8xx_cfgchip_mux_clk *mux;

	mux = da8xx_cfgchip_mux_clk_रेजिस्टर(dev, &da850_async1_info, regmap);
	अगर (IS_ERR(mux))
		वापस PTR_ERR(mux);

	clk_hw_रेजिस्टर_clkdev(&mux->hw, "async1", "da850-psc0");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा da8xx_cfgchip_mux_clk_info da850_async3_info __initस्थिर = अणु
	.name = "async3",
	.parent0 = "pll0_sysclk2",
	.parent1 = "pll1_sysclk2",
	.cfgchip = CFGCHIP(3),
	.bit = CFGCHIP3_ASYNC3_CLKSRC,
पूर्ण;

अटल पूर्णांक __init da850_cfgchip_रेजिस्टर_async3(काष्ठा device *dev,
						काष्ठा regmap *regmap)
अणु
	काष्ठा da8xx_cfgchip_mux_clk *mux;
	काष्ठा clk_hw *parent;

	mux = da8xx_cfgchip_mux_clk_रेजिस्टर(dev, &da850_async3_info, regmap);
	अगर (IS_ERR(mux))
		वापस PTR_ERR(mux);

	clk_hw_रेजिस्टर_clkdev(&mux->hw, "async3", "da850-psc1");

	/* pll1_sysclk2 is not affected by CPU scaling, so use it क्रम async3 */
	parent = clk_hw_get_parent_by_index(&mux->hw, 1);
	अगर (parent)
		clk_set_parent(mux->hw.clk, parent->clk);
	अन्यथा
		dev_warn(dev, "Failed to find async3 parent clock\n");

	वापस 0;
पूर्ण

अटल पूर्णांक __init
of_da8xx_cfgchip_init_mux_घड़ी(काष्ठा device *dev,
				स्थिर काष्ठा da8xx_cfgchip_mux_clk_info *info,
				काष्ठा regmap *regmap)
अणु
	काष्ठा da8xx_cfgchip_mux_clk *mux;

	mux = da8xx_cfgchip_mux_clk_रेजिस्टर(dev, info, regmap);
	अगर (IS_ERR(mux))
		वापस PTR_ERR(mux);

	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get, &mux->hw);
पूर्ण

अटल पूर्णांक __init of_da850_async1_init(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	वापस of_da8xx_cfgchip_init_mux_घड़ी(dev, &da850_async1_info, regmap);
पूर्ण

अटल पूर्णांक __init of_da850_async3_init(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	वापस of_da8xx_cfgchip_init_mux_घड़ी(dev, &da850_async3_info, regmap);
पूर्ण

/* --- USB 2.0 PHY घड़ी --- */

काष्ठा da8xx_usb0_clk48 अणु
	काष्ठा clk_hw hw;
	काष्ठा clk *fck;
	काष्ठा regmap *regmap;
पूर्ण;

#घोषणा to_da8xx_usb0_clk48(_hw) \
	container_of((_hw), काष्ठा da8xx_usb0_clk48, hw)

अटल पूर्णांक da8xx_usb0_clk48_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा da8xx_usb0_clk48 *usb0 = to_da8xx_usb0_clk48(hw);

	/* The USB 2.0 PSC घड़ी is only needed temporarily during the USB 2.0
	 * PHY घड़ी enable, but since clk_prepare() can't be called in an
	 * atomic context (i.e. in clk_enable()), we have to prepare it here.
	 */
	वापस clk_prepare(usb0->fck);
पूर्ण

अटल व्योम da8xx_usb0_clk48_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा da8xx_usb0_clk48 *usb0 = to_da8xx_usb0_clk48(hw);

	clk_unprepare(usb0->fck);
पूर्ण

अटल पूर्णांक da8xx_usb0_clk48_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा da8xx_usb0_clk48 *usb0 = to_da8xx_usb0_clk48(hw);
	अचिन्हित पूर्णांक mask, val;
	पूर्णांक ret;

	/* Locking the USB 2.O PLL requires that the USB 2.O PSC is enabled
	 * temporaily. It can be turned back off once the PLL is locked.
	 */
	clk_enable(usb0->fck);

	/* Turn on the USB 2.0 PHY, but just the PLL, and not OTG. The USB 1.1
	 * PHY may use the USB 2.0 PLL घड़ी without USB 2.0 OTG being used.
	 */
	mask = CFGCHIP2_RESET | CFGCHIP2_PHYPWRDN | CFGCHIP2_PHY_PLLON;
	val = CFGCHIP2_PHY_PLLON;

	regmap_ग_लिखो_bits(usb0->regmap, CFGCHIP(2), mask, val);
	ret = regmap_पढ़ो_poll_समयout(usb0->regmap, CFGCHIP(2), val,
				       val & CFGCHIP2_PHYCLKGD, 0, 500000);

	clk_disable(usb0->fck);

	वापस ret;
पूर्ण

अटल व्योम da8xx_usb0_clk48_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा da8xx_usb0_clk48 *usb0 = to_da8xx_usb0_clk48(hw);
	अचिन्हित पूर्णांक val;

	val = CFGCHIP2_PHYPWRDN;
	regmap_ग_लिखो_bits(usb0->regmap, CFGCHIP(2), val, val);
पूर्ण

अटल पूर्णांक da8xx_usb0_clk48_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा da8xx_usb0_clk48 *usb0 = to_da8xx_usb0_clk48(hw);
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(usb0->regmap, CFGCHIP(2), &val);

	वापस !!(val & CFGCHIP2_PHYCLKGD);
पूर्ण

अटल अचिन्हित दीर्घ da8xx_usb0_clk48_recalc_rate(काष्ठा clk_hw *hw,
						  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा da8xx_usb0_clk48 *usb0 = to_da8xx_usb0_clk48(hw);
	अचिन्हित पूर्णांक mask, val;

	/* The parent घड़ी rate must be one of the following */
	mask = CFGCHIP2_REFFREQ_MASK;
	चयन (parent_rate) अणु
	हाल 12000000:
		val = CFGCHIP2_REFFREQ_12MHZ;
		अवरोध;
	हाल 13000000:
		val = CFGCHIP2_REFFREQ_13MHZ;
		अवरोध;
	हाल 19200000:
		val = CFGCHIP2_REFFREQ_19_2MHZ;
		अवरोध;
	हाल 20000000:
		val = CFGCHIP2_REFFREQ_20MHZ;
		अवरोध;
	हाल 24000000:
		val = CFGCHIP2_REFFREQ_24MHZ;
		अवरोध;
	हाल 26000000:
		val = CFGCHIP2_REFFREQ_26MHZ;
		अवरोध;
	हाल 38400000:
		val = CFGCHIP2_REFFREQ_38_4MHZ;
		अवरोध;
	हाल 40000000:
		val = CFGCHIP2_REFFREQ_40MHZ;
		अवरोध;
	हाल 48000000:
		val = CFGCHIP2_REFFREQ_48MHZ;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	regmap_ग_लिखो_bits(usb0->regmap, CFGCHIP(2), mask, val);

	/* USB 2.0 PLL always supplies 48MHz */
	वापस 48000000;
पूर्ण

अटल दीर्घ da8xx_usb0_clk48_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ *parent_rate)
अणु
	वापस 48000000;
पूर्ण

अटल पूर्णांक da8xx_usb0_clk48_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा da8xx_usb0_clk48 *usb0 = to_da8xx_usb0_clk48(hw);

	वापस regmap_ग_लिखो_bits(usb0->regmap, CFGCHIP(2),
				 CFGCHIP2_USB2PHYCLKMUX,
				 index ? CFGCHIP2_USB2PHYCLKMUX : 0);
पूर्ण

अटल u8 da8xx_usb0_clk48_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा da8xx_usb0_clk48 *usb0 = to_da8xx_usb0_clk48(hw);
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(usb0->regmap, CFGCHIP(2), &val);

	वापस (val & CFGCHIP2_USB2PHYCLKMUX) ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops da8xx_usb0_clk48_ops = अणु
	.prepare	= da8xx_usb0_clk48_prepare,
	.unprepare	= da8xx_usb0_clk48_unprepare,
	.enable		= da8xx_usb0_clk48_enable,
	.disable	= da8xx_usb0_clk48_disable,
	.is_enabled	= da8xx_usb0_clk48_is_enabled,
	.recalc_rate	= da8xx_usb0_clk48_recalc_rate,
	.round_rate	= da8xx_usb0_clk48_round_rate,
	.set_parent	= da8xx_usb0_clk48_set_parent,
	.get_parent	= da8xx_usb0_clk48_get_parent,
पूर्ण;

अटल काष्ठा da8xx_usb0_clk48 *
da8xx_cfgchip_रेजिस्टर_usb0_clk48(काष्ठा device *dev,
				  काष्ठा regmap *regmap)
अणु
	स्थिर अक्षर * स्थिर parent_names[] = अणु "usb_refclkin", "pll0_auxclk" पूर्ण;
	काष्ठा clk *fck_clk;
	काष्ठा da8xx_usb0_clk48 *usb0;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	fck_clk = devm_clk_get(dev, "fck");
	अगर (IS_ERR(fck_clk)) अणु
		अगर (PTR_ERR(fck_clk) != -EPROBE_DEFER)
			dev_err(dev, "Missing fck clock\n");
		वापस ERR_CAST(fck_clk);
	पूर्ण

	usb0 = devm_kzalloc(dev, माप(*usb0), GFP_KERNEL);
	अगर (!usb0)
		वापस ERR_PTR(-ENOMEM);

	init.name = "usb0_clk48";
	init.ops = &da8xx_usb0_clk48_ops;
	init.parent_names = parent_names;
	init.num_parents = 2;

	usb0->hw.init = &init;
	usb0->fck = fck_clk;
	usb0->regmap = regmap;

	ret = devm_clk_hw_रेजिस्टर(dev, &usb0->hw);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	वापस usb0;
पूर्ण

/* --- USB 1.1 PHY घड़ी --- */

काष्ठा da8xx_usb1_clk48 अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
पूर्ण;

#घोषणा to_da8xx_usb1_clk48(_hw) \
	container_of((_hw), काष्ठा da8xx_usb1_clk48, hw)

अटल पूर्णांक da8xx_usb1_clk48_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा da8xx_usb1_clk48 *usb1 = to_da8xx_usb1_clk48(hw);

	वापस regmap_ग_लिखो_bits(usb1->regmap, CFGCHIP(2),
				 CFGCHIP2_USB1PHYCLKMUX,
				 index ? CFGCHIP2_USB1PHYCLKMUX : 0);
पूर्ण

अटल u8 da8xx_usb1_clk48_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा da8xx_usb1_clk48 *usb1 = to_da8xx_usb1_clk48(hw);
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(usb1->regmap, CFGCHIP(2), &val);

	वापस (val & CFGCHIP2_USB1PHYCLKMUX) ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops da8xx_usb1_clk48_ops = अणु
	.set_parent	= da8xx_usb1_clk48_set_parent,
	.get_parent	= da8xx_usb1_clk48_get_parent,
पूर्ण;

/**
 * da8xx_cfgchip_रेजिस्टर_usb1_clk48 - Register a new USB 1.1 PHY घड़ी
 * @dev: The device
 * @regmap: The CFGCHIP regmap
 */
अटल काष्ठा da8xx_usb1_clk48 *
da8xx_cfgchip_रेजिस्टर_usb1_clk48(काष्ठा device *dev,
				  काष्ठा regmap *regmap)
अणु
	स्थिर अक्षर * स्थिर parent_names[] = अणु "usb0_clk48", "usb_refclkin" पूर्ण;
	काष्ठा da8xx_usb1_clk48 *usb1;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	usb1 = devm_kzalloc(dev, माप(*usb1), GFP_KERNEL);
	अगर (!usb1)
		वापस ERR_PTR(-ENOMEM);

	init.name = "usb1_clk48";
	init.ops = &da8xx_usb1_clk48_ops;
	init.parent_names = parent_names;
	init.num_parents = 2;

	usb1->hw.init = &init;
	usb1->regmap = regmap;

	ret = devm_clk_hw_रेजिस्टर(dev, &usb1->hw);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	वापस usb1;
पूर्ण

अटल पूर्णांक da8xx_cfgchip_रेजिस्टर_usb_phy_clk(काष्ठा device *dev,
					      काष्ठा regmap *regmap)
अणु
	काष्ठा da8xx_usb0_clk48 *usb0;
	काष्ठा da8xx_usb1_clk48 *usb1;
	काष्ठा clk_hw *parent;

	usb0 = da8xx_cfgchip_रेजिस्टर_usb0_clk48(dev, regmap);
	अगर (IS_ERR(usb0))
		वापस PTR_ERR(usb0);

	/*
	 * All existing boards use pll0_auxclk as the parent and new boards
	 * should use device tree, so hard-coding the value (1) here.
	 */
	parent = clk_hw_get_parent_by_index(&usb0->hw, 1);
	अगर (parent)
		clk_set_parent(usb0->hw.clk, parent->clk);
	अन्यथा
		dev_warn(dev, "Failed to find usb0 parent clock\n");

	usb1 = da8xx_cfgchip_रेजिस्टर_usb1_clk48(dev, regmap);
	अगर (IS_ERR(usb1))
		वापस PTR_ERR(usb1);

	/*
	 * All existing boards use usb0_clk48 as the parent and new boards
	 * should use device tree, so hard-coding the value (0) here.
	 */
	parent = clk_hw_get_parent_by_index(&usb1->hw, 0);
	अगर (parent)
		clk_set_parent(usb1->hw.clk, parent->clk);
	अन्यथा
		dev_warn(dev, "Failed to find usb1 parent clock\n");

	clk_hw_रेजिस्टर_clkdev(&usb0->hw, "usb0_clk48", "da8xx-usb-phy");
	clk_hw_रेजिस्टर_clkdev(&usb1->hw, "usb1_clk48", "da8xx-usb-phy");

	वापस 0;
पूर्ण

अटल पूर्णांक of_da8xx_usb_phy_clk_init(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	काष्ठा clk_hw_onecell_data *clk_data;
	काष्ठा da8xx_usb0_clk48 *usb0;
	काष्ठा da8xx_usb1_clk48 *usb1;

	clk_data = devm_kzalloc(dev, काष्ठा_size(clk_data, hws, 2),
				GFP_KERNEL);
	अगर (!clk_data)
		वापस -ENOMEM;

	clk_data->num = 2;

	usb0 = da8xx_cfgchip_रेजिस्टर_usb0_clk48(dev, regmap);
	अगर (IS_ERR(usb0)) अणु
		अगर (PTR_ERR(usb0) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		dev_warn(dev, "Failed to register usb0_clk48 (%ld)\n",
			 PTR_ERR(usb0));

		clk_data->hws[0] = ERR_PTR(-ENOENT);
	पूर्ण अन्यथा अणु
		clk_data->hws[0] = &usb0->hw;
	पूर्ण

	usb1 = da8xx_cfgchip_रेजिस्टर_usb1_clk48(dev, regmap);
	अगर (IS_ERR(usb1)) अणु
		अगर (PTR_ERR(usb1) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		dev_warn(dev, "Failed to register usb1_clk48 (%ld)\n",
			 PTR_ERR(usb1));

		clk_data->hws[1] = ERR_PTR(-ENOENT);
	पूर्ण अन्यथा अणु
		clk_data->hws[1] = &usb1->hw;
	पूर्ण

	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get, clk_data);
पूर्ण

/* --- platक्रमm device --- */

अटल स्थिर काष्ठा of_device_id da8xx_cfgchip_of_match[] = अणु
	अणु
		.compatible = "ti,da830-tbclksync",
		.data = of_da8xx_tbclksync_init,
	पूर्ण,
	अणु
		.compatible = "ti,da830-div4p5ena",
		.data = of_da8xx_भाग4p5ena_init,
	पूर्ण,
	अणु
		.compatible = "ti,da850-async1-clksrc",
		.data = of_da850_async1_init,
	पूर्ण,
	अणु
		.compatible = "ti,da850-async3-clksrc",
		.data = of_da850_async3_init,
	पूर्ण,
	अणु
		.compatible = "ti,da830-usb-phy-clocks",
		.data = of_da8xx_usb_phy_clk_init,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id da8xx_cfgchip_id_table[] = अणु
	अणु
		.name = "da830-tbclksync",
		.driver_data = (kernel_uदीर्घ_t)da8xx_cfgchip_रेजिस्टर_tbclk,
	पूर्ण,
	अणु
		.name = "da830-div4p5ena",
		.driver_data = (kernel_uदीर्घ_t)da8xx_cfgchip_रेजिस्टर_भाग4p5,
	पूर्ण,
	अणु
		.name = "da850-async1-clksrc",
		.driver_data = (kernel_uदीर्घ_t)da8xx_cfgchip_रेजिस्टर_async1,
	पूर्ण,
	अणु
		.name = "da850-async3-clksrc",
		.driver_data = (kernel_uदीर्घ_t)da850_cfgchip_रेजिस्टर_async3,
	पूर्ण,
	अणु
		.name = "da830-usb-phy-clks",
		.driver_data = (kernel_uदीर्घ_t)da8xx_cfgchip_रेजिस्टर_usb_phy_clk,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

प्रकार पूर्णांक (*da8xx_cfgchip_init)(काष्ठा device *dev, काष्ठा regmap *regmap);

अटल पूर्णांक da8xx_cfgchip_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा da8xx_cfgchip_clk_platक्रमm_data *pdata = dev->platक्रमm_data;
	स्थिर काष्ठा of_device_id *of_id;
	da8xx_cfgchip_init clk_init = शून्य;
	काष्ठा regmap *regmap = शून्य;

	of_id = of_match_device(da8xx_cfgchip_of_match, dev);
	अगर (of_id) अणु
		काष्ठा device_node *parent;

		clk_init = of_id->data;
		parent = of_get_parent(dev->of_node);
		regmap = syscon_node_to_regmap(parent);
		of_node_put(parent);
	पूर्ण अन्यथा अगर (pdev->id_entry && pdata) अणु
		clk_init = (व्योम *)pdev->id_entry->driver_data;
		regmap = pdata->cfgchip;
	पूर्ण

	अगर (!clk_init) अणु
		dev_err(dev, "unable to find driver data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (IS_ERR_OR_शून्य(regmap)) अणु
		dev_err(dev, "no regmap for CFGCHIP syscon\n");
		वापस regmap ? PTR_ERR(regmap) : -ENOENT;
	पूर्ण

	वापस clk_init(dev, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver da8xx_cfgchip_driver = अणु
	.probe		= da8xx_cfgchip_probe,
	.driver		= अणु
		.name		= "da8xx-cfgchip-clk",
		.of_match_table	= da8xx_cfgchip_of_match,
	पूर्ण,
	.id_table	= da8xx_cfgchip_id_table,
पूर्ण;

अटल पूर्णांक __init da8xx_cfgchip_driver_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&da8xx_cfgchip_driver);
पूर्ण

/* has to be postcore_initcall because PSC devices depend on the async3 घड़ी */
postcore_initcall(da8xx_cfgchip_driver_init);
