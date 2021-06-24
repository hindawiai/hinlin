<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Clkout driver क्रम Rockchip RK808
 *
 * Copyright (c) 2014, Fuzhou Rockchip Electronics Co., Ltd
 *
 * Author:Chris Zhong <zyw@rock-chips.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/rk808.h>
#समावेश <linux/i2c.h>

काष्ठा rk808_clkout अणु
	काष्ठा rk808 *rk808;
	काष्ठा clk_hw		clkout1_hw;
	काष्ठा clk_hw		clkout2_hw;
पूर्ण;

अटल अचिन्हित दीर्घ rk808_clkout_recalc_rate(काष्ठा clk_hw *hw,
					      अचिन्हित दीर्घ parent_rate)
अणु
	वापस 32768;
पूर्ण

अटल पूर्णांक rk808_clkout2_enable(काष्ठा clk_hw *hw, bool enable)
अणु
	काष्ठा rk808_clkout *rk808_clkout = container_of(hw,
							 काष्ठा rk808_clkout,
							 clkout2_hw);
	काष्ठा rk808 *rk808 = rk808_clkout->rk808;

	वापस regmap_update_bits(rk808->regmap, RK808_CLK32OUT_REG,
				  CLK32KOUT2_EN, enable ? CLK32KOUT2_EN : 0);
पूर्ण

अटल पूर्णांक rk808_clkout2_prepare(काष्ठा clk_hw *hw)
अणु
	वापस rk808_clkout2_enable(hw, true);
पूर्ण

अटल व्योम rk808_clkout2_unprepare(काष्ठा clk_hw *hw)
अणु
	rk808_clkout2_enable(hw, false);
पूर्ण

अटल पूर्णांक rk808_clkout2_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा rk808_clkout *rk808_clkout = container_of(hw,
							 काष्ठा rk808_clkout,
							 clkout2_hw);
	काष्ठा rk808 *rk808 = rk808_clkout->rk808;
	uपूर्णांक32_t val;

	पूर्णांक ret = regmap_पढ़ो(rk808->regmap, RK808_CLK32OUT_REG, &val);

	अगर (ret < 0)
		वापस ret;

	वापस (val & CLK32KOUT2_EN) ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops rk808_clkout1_ops = अणु
	.recalc_rate = rk808_clkout_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops rk808_clkout2_ops = अणु
	.prepare = rk808_clkout2_prepare,
	.unprepare = rk808_clkout2_unprepare,
	.is_prepared = rk808_clkout2_is_prepared,
	.recalc_rate = rk808_clkout_recalc_rate,
पूर्ण;

अटल काष्ठा clk_hw *
of_clk_rk808_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	काष्ठा rk808_clkout *rk808_clkout = data;
	अचिन्हित पूर्णांक idx = clkspec->args[0];

	अगर (idx >= 2) अणु
		pr_err("%s: invalid index %u\n", __func__, idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस idx ? &rk808_clkout->clkout2_hw : &rk808_clkout->clkout1_hw;
पूर्ण

अटल पूर्णांक rk817_clkout2_enable(काष्ठा clk_hw *hw, bool enable)
अणु
	काष्ठा rk808_clkout *rk808_clkout = container_of(hw,
							 काष्ठा rk808_clkout,
							 clkout2_hw);
	काष्ठा rk808 *rk808 = rk808_clkout->rk808;

	वापस regmap_update_bits(rk808->regmap, RK817_SYS_CFG(1),
				  RK817_CLK32KOUT2_EN,
				  enable ? RK817_CLK32KOUT2_EN : 0);
पूर्ण

अटल पूर्णांक rk817_clkout2_prepare(काष्ठा clk_hw *hw)
अणु
	वापस rk817_clkout2_enable(hw, true);
पूर्ण

अटल व्योम rk817_clkout2_unprepare(काष्ठा clk_hw *hw)
अणु
	rk817_clkout2_enable(hw, false);
पूर्ण

अटल पूर्णांक rk817_clkout2_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा rk808_clkout *rk808_clkout = container_of(hw,
							 काष्ठा rk808_clkout,
							 clkout2_hw);
	काष्ठा rk808 *rk808 = rk808_clkout->rk808;
	अचिन्हित पूर्णांक val;

	पूर्णांक ret = regmap_पढ़ो(rk808->regmap, RK817_SYS_CFG(1), &val);

	अगर (ret < 0)
		वापस 0;

	वापस (val & RK817_CLK32KOUT2_EN) ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops rk817_clkout2_ops = अणु
	.prepare = rk817_clkout2_prepare,
	.unprepare = rk817_clkout2_unprepare,
	.is_prepared = rk817_clkout2_is_prepared,
	.recalc_rate = rk808_clkout_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops *rkpmic_get_ops(दीर्घ variant)
अणु
	चयन (variant) अणु
	हाल RK809_ID:
	हाल RK817_ID:
		वापस &rk817_clkout2_ops;
	/*
	 * For the शेष हाल, it match the following PMIC type.
	 * RK805_ID
	 * RK808_ID
	 * RK818_ID
	 */
	शेष:
		वापस &rk808_clkout2_ops;
	पूर्ण
पूर्ण

अटल पूर्णांक rk808_clkout_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rk808 *rk808 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा i2c_client *client = rk808->i2c;
	काष्ठा device_node *node = client->dev.of_node;
	काष्ठा clk_init_data init = अणुपूर्ण;
	काष्ठा rk808_clkout *rk808_clkout;
	पूर्णांक ret;

	rk808_clkout = devm_kzalloc(&client->dev,
				    माप(*rk808_clkout), GFP_KERNEL);
	अगर (!rk808_clkout)
		वापस -ENOMEM;

	rk808_clkout->rk808 = rk808;

	init.parent_names = शून्य;
	init.num_parents = 0;
	init.name = "rk808-clkout1";
	init.ops = &rk808_clkout1_ops;
	rk808_clkout->clkout1_hw.init = &init;

	/* optional override of the घड़ीname */
	of_property_पढ़ो_string_index(node, "clock-output-names",
				      0, &init.name);

	ret = devm_clk_hw_रेजिस्टर(&client->dev, &rk808_clkout->clkout1_hw);
	अगर (ret)
		वापस ret;

	init.name = "rk808-clkout2";
	init.ops = rkpmic_get_ops(rk808->variant);
	rk808_clkout->clkout2_hw.init = &init;

	/* optional override of the घड़ीname */
	of_property_पढ़ो_string_index(node, "clock-output-names",
				      1, &init.name);

	ret = devm_clk_hw_रेजिस्टर(&client->dev, &rk808_clkout->clkout2_hw);
	अगर (ret)
		वापस ret;

	वापस devm_of_clk_add_hw_provider(&pdev->dev, of_clk_rk808_get,
					   rk808_clkout);
पूर्ण

अटल काष्ठा platक्रमm_driver rk808_clkout_driver = अणु
	.probe = rk808_clkout_probe,
	.driver		= अणु
		.name	= "rk808-clkout",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rk808_clkout_driver);

MODULE_DESCRIPTION("Clkout driver for the rk808 series PMICs");
MODULE_AUTHOR("Chris Zhong <zyw@rock-chips.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rk808-clkout");
