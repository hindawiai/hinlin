<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Qualcomm A53 PLL driver
 *
 * Copyright (c) 2017, Linaro Limited
 * Author: Georgi Djakov <georgi.djakov@linaro.org>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/module.h>

#समावेश "clk-pll.h"
#समावेश "clk-regmap.h"

अटल स्थिर काष्ठा pll_freq_tbl a53pll_freq[] = अणु
	अणु  998400000, 52, 0x0, 0x1, 0 पूर्ण,
	अणु 1094400000, 57, 0x0, 0x1, 0 पूर्ण,
	अणु 1152000000, 62, 0x0, 0x1, 0 पूर्ण,
	अणु 1209600000, 63, 0x0, 0x1, 0 पूर्ण,
	अणु 1248000000, 65, 0x0, 0x1, 0 पूर्ण,
	अणु 1363200000, 71, 0x0, 0x1, 0 पूर्ण,
	अणु 1401600000, 73, 0x0, 0x1, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा regmap_config a53pll_regmap_config = अणु
	.reg_bits		= 32,
	.reg_stride		= 4,
	.val_bits		= 32,
	.max_रेजिस्टर		= 0x40,
	.fast_io		= true,
पूर्ण;

अटल पूर्णांक qcom_a53pll_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regmap *regmap;
	काष्ठा resource *res;
	काष्ठा clk_pll *pll;
	व्योम __iomem *base;
	काष्ठा clk_init_data init = अणु पूर्ण;
	पूर्णांक ret;

	pll = devm_kzalloc(dev, माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	regmap = devm_regmap_init_mmio(dev, base, &a53pll_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	pll->l_reg = 0x04;
	pll->m_reg = 0x08;
	pll->n_reg = 0x0c;
	pll->config_reg = 0x14;
	pll->mode_reg = 0x00;
	pll->status_reg = 0x1c;
	pll->status_bit = 16;
	pll->freq_tbl = a53pll_freq;

	init.name = "a53pll";
	init.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण;
	init.num_parents = 1;
	init.ops = &clk_pll_sr2_ops;
	init.flags = CLK_IS_CRITICAL;
	pll->clkr.hw.init = &init;

	ret = devm_clk_रेजिस्टर_regmap(dev, &pll->clkr);
	अगर (ret) अणु
		dev_err(dev, "failed to register regmap clock: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get,
					  &pll->clkr.hw);
	अगर (ret) अणु
		dev_err(dev, "failed to add clock provider: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_a53pll_match_table[] = अणु
	अणु .compatible = "qcom,msm8916-a53pll" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_a53pll_match_table);

अटल काष्ठा platक्रमm_driver qcom_a53pll_driver = अणु
	.probe = qcom_a53pll_probe,
	.driver = अणु
		.name = "qcom-a53pll",
		.of_match_table = qcom_a53pll_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qcom_a53pll_driver);

MODULE_DESCRIPTION("Qualcomm A53 PLL Driver");
MODULE_LICENSE("GPL v2");
