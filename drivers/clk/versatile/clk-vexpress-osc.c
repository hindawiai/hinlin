<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2012 ARM Limited
 */

#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/vexpress.h>

काष्ठा vexpress_osc अणु
	काष्ठा regmap *reg;
	काष्ठा clk_hw hw;
	अचिन्हित दीर्घ rate_min;
	अचिन्हित दीर्घ rate_max;
पूर्ण;

#घोषणा to_vexpress_osc(osc) container_of(osc, काष्ठा vexpress_osc, hw)

अटल अचिन्हित दीर्घ vexpress_osc_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा vexpress_osc *osc = to_vexpress_osc(hw);
	u32 rate;

	regmap_पढ़ो(osc->reg, 0, &rate);

	वापस rate;
पूर्ण

अटल दीर्घ vexpress_osc_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा vexpress_osc *osc = to_vexpress_osc(hw);

	अगर (osc->rate_min && rate < osc->rate_min)
		rate = osc->rate_min;

	अगर (osc->rate_max && rate > osc->rate_max)
		rate = osc->rate_max;

	वापस rate;
पूर्ण

अटल पूर्णांक vexpress_osc_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा vexpress_osc *osc = to_vexpress_osc(hw);

	वापस regmap_ग_लिखो(osc->reg, 0, rate);
पूर्ण

अटल स्थिर काष्ठा clk_ops vexpress_osc_ops = अणु
	.recalc_rate = vexpress_osc_recalc_rate,
	.round_rate = vexpress_osc_round_rate,
	.set_rate = vexpress_osc_set_rate,
पूर्ण;


अटल पूर्णांक vexpress_osc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_init_data init;
	काष्ठा vexpress_osc *osc;
	u32 range[2];
	पूर्णांक ret;

	osc = devm_kzalloc(&pdev->dev, माप(*osc), GFP_KERNEL);
	अगर (!osc)
		वापस -ENOMEM;

	osc->reg = devm_regmap_init_vexpress_config(&pdev->dev);
	अगर (IS_ERR(osc->reg))
		वापस PTR_ERR(osc->reg);

	अगर (of_property_पढ़ो_u32_array(pdev->dev.of_node, "freq-range", range,
			ARRAY_SIZE(range)) == 0) अणु
		osc->rate_min = range[0];
		osc->rate_max = range[1];
	पूर्ण

	अगर (of_property_पढ़ो_string(pdev->dev.of_node, "clock-output-names",
			&init.name) != 0)
		init.name = dev_name(&pdev->dev);

	init.ops = &vexpress_osc_ops;
	init.flags = 0;
	init.num_parents = 0;

	osc->hw.init = &init;

	ret = devm_clk_hw_रेजिस्टर(&pdev->dev, &osc->hw);
	अगर (ret < 0)
		वापस ret;

	devm_of_clk_add_hw_provider(&pdev->dev, of_clk_hw_simple_get, &osc->hw);
	clk_hw_set_rate_range(&osc->hw, osc->rate_min, osc->rate_max);

	dev_dbg(&pdev->dev, "Registered clock '%s'\n", init.name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id vexpress_osc_of_match[] = अणु
	अणु .compatible = "arm,vexpress-osc", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, vexpress_osc_of_match);

अटल काष्ठा platक्रमm_driver vexpress_osc_driver = अणु
	.driver	= अणु
		.name = "vexpress-osc",
		.of_match_table = vexpress_osc_of_match,
	पूर्ण,
	.probe = vexpress_osc_probe,
पूर्ण;
module_platक्रमm_driver(vexpress_osc_driver);
MODULE_LICENSE("GPL v2");
