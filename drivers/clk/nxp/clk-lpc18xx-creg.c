<शैली गुरु>
/*
 * Clk driver क्रम NXP LPC18xx/43xx Configuration Registers (CREG)
 *
 * Copyright (C) 2015 Joachim Eastwood <manabian@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा LPC18XX_CREG_CREG0			0x004
#घोषणा  LPC18XX_CREG_CREG0_EN1KHZ		BIT(0)
#घोषणा  LPC18XX_CREG_CREG0_EN32KHZ		BIT(1)
#घोषणा  LPC18XX_CREG_CREG0_RESET32KHZ		BIT(2)
#घोषणा  LPC18XX_CREG_CREG0_PD32KHZ		BIT(3)

#घोषणा to_clk_creg(_hw) container_of(_hw, काष्ठा clk_creg_data, hw)

क्रमागत अणु
	CREG_CLK_1KHZ,
	CREG_CLK_32KHZ,
	CREG_CLK_MAX,
पूर्ण;

काष्ठा clk_creg_data अणु
	काष्ठा clk_hw hw;
	स्थिर अक्षर *name;
	काष्ठा regmap *reg;
	अचिन्हित पूर्णांक en_mask;
	स्थिर काष्ठा clk_ops *ops;
पूर्ण;

#घोषणा CREG_CLK(_name, _emask, _ops)		\
अणु						\
	.name = _name,				\
	.en_mask = LPC18XX_CREG_CREG0_##_emask,	\
	.ops = &_ops,				\
पूर्ण

अटल पूर्णांक clk_creg_32k_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_creg_data *creg = to_clk_creg(hw);
	पूर्णांक ret;

	ret = regmap_update_bits(creg->reg, LPC18XX_CREG_CREG0,
				 LPC18XX_CREG_CREG0_PD32KHZ |
				 LPC18XX_CREG_CREG0_RESET32KHZ, 0);

	/*
	 * Powering up the 32k oscillator takes a दीर्घ जबतक
	 * and sadly there aren't any status bit to poll.
	 */
	msleep(2500);

	वापस ret;
पूर्ण

अटल व्योम clk_creg_32k_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_creg_data *creg = to_clk_creg(hw);

	regmap_update_bits(creg->reg, LPC18XX_CREG_CREG0,
			   LPC18XX_CREG_CREG0_PD32KHZ,
			   LPC18XX_CREG_CREG0_PD32KHZ);
पूर्ण

अटल पूर्णांक clk_creg_32k_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_creg_data *creg = to_clk_creg(hw);
	u32 reg;

	regmap_पढ़ो(creg->reg, LPC18XX_CREG_CREG0, &reg);

	वापस !(reg & LPC18XX_CREG_CREG0_PD32KHZ) &&
	       !(reg & LPC18XX_CREG_CREG0_RESET32KHZ);
पूर्ण

अटल अचिन्हित दीर्घ clk_creg_1k_recalc_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	वापस parent_rate / 32;
पूर्ण

अटल पूर्णांक clk_creg_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_creg_data *creg = to_clk_creg(hw);

	वापस regmap_update_bits(creg->reg, LPC18XX_CREG_CREG0,
				  creg->en_mask, creg->en_mask);
पूर्ण

अटल व्योम clk_creg_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_creg_data *creg = to_clk_creg(hw);

	regmap_update_bits(creg->reg, LPC18XX_CREG_CREG0,
			   creg->en_mask, 0);
पूर्ण

अटल पूर्णांक clk_creg_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_creg_data *creg = to_clk_creg(hw);
	u32 reg;

	regmap_पढ़ो(creg->reg, LPC18XX_CREG_CREG0, &reg);

	वापस !!(reg & creg->en_mask);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_creg_32k = अणु
	.enable		= clk_creg_enable,
	.disable	= clk_creg_disable,
	.is_enabled	= clk_creg_is_enabled,
	.prepare	= clk_creg_32k_prepare,
	.unprepare	= clk_creg_32k_unprepare,
	.is_prepared	= clk_creg_32k_is_prepared,
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_creg_1k = अणु
	.enable		= clk_creg_enable,
	.disable	= clk_creg_disable,
	.is_enabled	= clk_creg_is_enabled,
	.recalc_rate	= clk_creg_1k_recalc_rate,
पूर्ण;

अटल काष्ठा clk_creg_data clk_creg_घड़ीs[] = अणु
	[CREG_CLK_1KHZ]  = CREG_CLK("1khz_clk",  EN1KHZ,  clk_creg_1k),
	[CREG_CLK_32KHZ] = CREG_CLK("32khz_clk", EN32KHZ, clk_creg_32k),
पूर्ण;

अटल काष्ठा clk *clk_रेजिस्टर_creg_clk(काष्ठा device *dev,
					 काष्ठा clk_creg_data *creg_clk,
					 स्थिर अक्षर **parent_name,
					 काष्ठा regmap *syscon)
अणु
	काष्ठा clk_init_data init;

	init.ops = creg_clk->ops;
	init.name = creg_clk->name;
	init.parent_names = parent_name;
	init.num_parents = 1;
	init.flags = 0;

	creg_clk->reg = syscon;
	creg_clk->hw.init = &init;

	अगर (dev)
		वापस devm_clk_रेजिस्टर(dev, &creg_clk->hw);

	वापस clk_रेजिस्टर(शून्य, &creg_clk->hw);
पूर्ण

अटल काष्ठा clk *clk_creg_early[CREG_CLK_MAX];
अटल काष्ठा clk_onecell_data clk_creg_early_data = अणु
	.clks = clk_creg_early,
	.clk_num = CREG_CLK_MAX,
पूर्ण;

अटल व्योम __init lpc18xx_creg_clk_init(काष्ठा device_node *np)
अणु
	स्थिर अक्षर *clk_32khz_parent;
	काष्ठा regmap *syscon;

	syscon = syscon_node_to_regmap(np->parent);
	अगर (IS_ERR(syscon)) अणु
		pr_err("%s: syscon lookup failed\n", __func__);
		वापस;
	पूर्ण

	clk_32khz_parent = of_clk_get_parent_name(np, 0);

	clk_creg_early[CREG_CLK_32KHZ] =
		clk_रेजिस्टर_creg_clk(शून्य, &clk_creg_घड़ीs[CREG_CLK_32KHZ],
				      &clk_32khz_parent, syscon);
	clk_creg_early[CREG_CLK_1KHZ] = ERR_PTR(-EPROBE_DEFER);

	of_clk_add_provider(np, of_clk_src_onecell_get, &clk_creg_early_data);
पूर्ण
CLK_OF_DECLARE_DRIVER(lpc18xx_creg_clk, "nxp,lpc1850-creg-clk",
		      lpc18xx_creg_clk_init);

अटल काष्ठा clk *clk_creg[CREG_CLK_MAX];
अटल काष्ठा clk_onecell_data clk_creg_data = अणु
	.clks = clk_creg,
	.clk_num = CREG_CLK_MAX,
पूर्ण;

अटल पूर्णांक lpc18xx_creg_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा regmap *syscon;

	syscon = syscon_node_to_regmap(np->parent);
	अगर (IS_ERR(syscon)) अणु
		dev_err(&pdev->dev, "syscon lookup failed\n");
		वापस PTR_ERR(syscon);
	पूर्ण

	clk_creg[CREG_CLK_32KHZ] = clk_creg_early[CREG_CLK_32KHZ];
	clk_creg[CREG_CLK_1KHZ] =
		clk_रेजिस्टर_creg_clk(शून्य, &clk_creg_घड़ीs[CREG_CLK_1KHZ],
				      &clk_creg_घड़ीs[CREG_CLK_32KHZ].name,
				      syscon);

	वापस of_clk_add_provider(np, of_clk_src_onecell_get, &clk_creg_data);
पूर्ण

अटल स्थिर काष्ठा of_device_id lpc18xx_creg_clk_of_match[] = अणु
	अणु .compatible = "nxp,lpc1850-creg-clk" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver lpc18xx_creg_clk_driver = अणु
	.probe = lpc18xx_creg_clk_probe,
	.driver = अणु
		.name = "lpc18xx-creg-clk",
		.of_match_table = lpc18xx_creg_clk_of_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(lpc18xx_creg_clk_driver);
