<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Qualcomm A7 PLL driver
 *
 * Copyright (c) 2020, Linaro Limited
 * Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश "clk-alpha-pll.h"

#घोषणा LUCID_PLL_OFF_L_VAL 0x04

अटल स्थिर काष्ठा pll_vco lucid_vco[] = अणु
	अणु 249600000, 2000000000, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll a7pll = अणु
	.offset = 0x100,
	.vco_table = lucid_vco,
	.num_vco = ARRAY_SIZE(lucid_vco),
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_LUCID],
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "a7pll",
			.parent_data =  &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_lucid_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा alpha_pll_config a7pll_config = अणु
	.l = 0x39,
	.config_ctl_val = 0x20485699,
	.config_ctl_hi_val = 0x2261,
	.config_ctl_hi1_val = 0x029A699C,
	.user_ctl_val = 0x1,
	.user_ctl_hi_val = 0x805,
पूर्ण;

अटल स्थिर काष्ठा regmap_config a7pll_regmap_config = अणु
	.reg_bits		= 32,
	.reg_stride		= 4,
	.val_bits		= 32,
	.max_रेजिस्टर		= 0x1000,
	.fast_io		= true,
पूर्ण;

अटल पूर्णांक qcom_a7pll_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regmap *regmap;
	व्योम __iomem *base;
	u32 l_val;
	पूर्णांक ret;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	regmap = devm_regmap_init_mmio(dev, base, &a7pll_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/* Configure PLL only अगर the l_val is zero */
	regmap_पढ़ो(regmap, a7pll.offset + LUCID_PLL_OFF_L_VAL, &l_val);
	अगर (!l_val)
		clk_lucid_pll_configure(&a7pll, regmap, &a7pll_config);

	ret = devm_clk_रेजिस्टर_regmap(dev, &a7pll.clkr);
	अगर (ret)
		वापस ret;

	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get,
					   &a7pll.clkr.hw);
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_a7pll_match_table[] = अणु
	अणु .compatible = "qcom,sdx55-a7pll" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_a7pll_match_table);

अटल काष्ठा platक्रमm_driver qcom_a7pll_driver = अणु
	.probe = qcom_a7pll_probe,
	.driver = अणु
		.name = "qcom-a7pll",
		.of_match_table = qcom_a7pll_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qcom_a7pll_driver);

MODULE_DESCRIPTION("Qualcomm A7 PLL Driver");
MODULE_LICENSE("GPL v2");
