<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018, The Linux Foundation. All rights reserved.

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>

#समावेश "clk-regmap.h"
#समावेश "clk-hfpll.h"

अटल स्थिर काष्ठा hfpll_data hdata = अणु
	.mode_reg = 0x00,
	.l_reg = 0x04,
	.m_reg = 0x08,
	.n_reg = 0x0c,
	.user_reg = 0x10,
	.config_reg = 0x14,
	.config_val = 0x430405d,
	.status_reg = 0x1c,
	.lock_bit = 16,

	.user_val = 0x8,
	.user_vco_mask = 0x100000,
	.low_vco_max_rate = 1248000000,
	.min_rate = 537600000UL,
	.max_rate = 2900000000UL,
पूर्ण;

अटल स्थिर काष्ठा of_device_id qcom_hfpll_match_table[] = अणु
	अणु .compatible = "qcom,hfpll" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_hfpll_match_table);

अटल स्थिर काष्ठा regmap_config hfpll_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x30,
	.fast_io	= true,
पूर्ण;

अटल पूर्णांक qcom_hfpll_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा device *dev = &pdev->dev;
	व्योम __iomem *base;
	काष्ठा regmap *regmap;
	काष्ठा clk_hfpll *h;
	काष्ठा clk_init_data init = अणु
		.num_parents = 1,
		.ops = &clk_ops_hfpll,
		/*
		 * rather than marking the घड़ी critical and क्रमcing the घड़ी
		 * to be always enabled, we make sure that the घड़ी is not
		 * disabled: the firmware reमुख्यs responsible of enabling this
		 * घड़ी (क्रम more info check the commit log)
		 */
		.flags = CLK_IGNORE_UNUSED,
	पूर्ण;
	पूर्णांक ret;
	काष्ठा clk_parent_data pdata = अणु .index = 0 पूर्ण;

	h = devm_kzalloc(dev, माप(*h), GFP_KERNEL);
	अगर (!h)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	regmap = devm_regmap_init_mmio(&pdev->dev, base, &hfpll_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	अगर (of_property_पढ़ो_string_index(dev->of_node, "clock-output-names",
					  0, &init.name))
		वापस -ENODEV;

	init.parent_data = &pdata;

	h->d = &hdata;
	h->clkr.hw.init = &init;
	spin_lock_init(&h->lock);

	ret = devm_clk_रेजिस्टर_regmap(dev, &h->clkr);
	अगर (ret) अणु
		dev_err(dev, "failed to register regmap clock: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get,
					   &h->clkr.hw);
पूर्ण

अटल काष्ठा platक्रमm_driver qcom_hfpll_driver = अणु
	.probe		= qcom_hfpll_probe,
	.driver		= अणु
		.name	= "qcom-hfpll",
		.of_match_table = qcom_hfpll_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qcom_hfpll_driver);

MODULE_DESCRIPTION("QCOM HFPLL Clock Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:qcom-hfpll");
