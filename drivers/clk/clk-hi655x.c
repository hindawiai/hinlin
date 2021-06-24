<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Clock driver क्रम Hi655x
 *
 * Copyright (c) 2017, Linaro Ltd.
 *
 * Author: Daniel Lezcano <daniel.lezcano@linaro.org>
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/hi655x-pmic.h>

#घोषणा HI655X_CLK_BASE	HI655X_BUS_ADDR(0x1c)
#घोषणा HI655X_CLK_SET	BIT(6)

काष्ठा hi655x_clk अणु
	काष्ठा hi655x_pmic *hi655x;
	काष्ठा clk_hw       clk_hw;
पूर्ण;

अटल अचिन्हित दीर्घ hi655x_clk_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	वापस 32768;
पूर्ण

अटल पूर्णांक hi655x_clk_enable(काष्ठा clk_hw *hw, bool enable)
अणु
	काष्ठा hi655x_clk *hi655x_clk =
		container_of(hw, काष्ठा hi655x_clk, clk_hw);

	काष्ठा hi655x_pmic *hi655x = hi655x_clk->hi655x;

	वापस regmap_update_bits(hi655x->regmap, HI655X_CLK_BASE,
				  HI655X_CLK_SET, enable ? HI655X_CLK_SET : 0);
पूर्ण

अटल पूर्णांक hi655x_clk_prepare(काष्ठा clk_hw *hw)
अणु
	वापस hi655x_clk_enable(hw, true);
पूर्ण

अटल व्योम hi655x_clk_unprepare(काष्ठा clk_hw *hw)
अणु
	hi655x_clk_enable(hw, false);
पूर्ण

अटल पूर्णांक hi655x_clk_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा hi655x_clk *hi655x_clk =
		container_of(hw, काष्ठा hi655x_clk, clk_hw);
	काष्ठा hi655x_pmic *hi655x = hi655x_clk->hi655x;
	पूर्णांक ret;
	uपूर्णांक32_t val;

	ret = regmap_पढ़ो(hi655x->regmap, HI655X_CLK_BASE, &val);
	अगर (ret < 0)
		वापस ret;

	वापस val & HI655X_CLK_BASE;
पूर्ण

अटल स्थिर काष्ठा clk_ops hi655x_clk_ops = अणु
	.prepare     = hi655x_clk_prepare,
	.unprepare   = hi655x_clk_unprepare,
	.is_prepared = hi655x_clk_is_prepared,
	.recalc_rate = hi655x_clk_recalc_rate,
पूर्ण;

अटल पूर्णांक hi655x_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *parent = pdev->dev.parent;
	काष्ठा hi655x_pmic *hi655x = dev_get_drvdata(parent);
	काष्ठा hi655x_clk *hi655x_clk;
	स्थिर अक्षर *clk_name = "hi655x-clk";
	काष्ठा clk_init_data init = अणु
		.name = clk_name,
		.ops = &hi655x_clk_ops
	पूर्ण;
	पूर्णांक ret;

	hi655x_clk = devm_kzalloc(&pdev->dev, माप(*hi655x_clk), GFP_KERNEL);
	अगर (!hi655x_clk)
		वापस -ENOMEM;

	of_property_पढ़ो_string_index(parent->of_node, "clock-output-names",
				      0, &clk_name);

	hi655x_clk->clk_hw.init	= &init;
	hi655x_clk->hi655x	= hi655x;

	platक्रमm_set_drvdata(pdev, hi655x_clk);

	ret = devm_clk_hw_रेजिस्टर(&pdev->dev, &hi655x_clk->clk_hw);
	अगर (ret)
		वापस ret;

	वापस devm_of_clk_add_hw_provider(&pdev->dev, of_clk_hw_simple_get,
					   &hi655x_clk->clk_hw);
पूर्ण

अटल काष्ठा platक्रमm_driver hi655x_clk_driver = अणु
	.probe =  hi655x_clk_probe,
	.driver		= अणु
		.name	= "hi655x-clk",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(hi655x_clk_driver);

MODULE_DESCRIPTION("Clk driver for the hi655x series PMICs");
MODULE_AUTHOR("Daniel Lezcano <daniel.lezcano@linaro.org>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:hi655x-clk");
