<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018, The Linux Foundation. All rights reserved.
#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश "clk-alpha-pll.h"

अटल स्थिर u8 ipq_pll_offsets[] = अणु
	[PLL_OFF_L_VAL] = 0x08,
	[PLL_OFF_ALPHA_VAL] = 0x10,
	[PLL_OFF_USER_CTL] = 0x18,
	[PLL_OFF_CONFIG_CTL] = 0x20,
	[PLL_OFF_CONFIG_CTL_U] = 0x24,
	[PLL_OFF_STATUS] = 0x28,
	[PLL_OFF_TEST_CTL] = 0x30,
	[PLL_OFF_TEST_CTL_U] = 0x34,
पूर्ण;

अटल काष्ठा clk_alpha_pll ipq_pll = अणु
	.offset = 0x0,
	.regs = ipq_pll_offsets,
	.flags = SUPPORTS_DYNAMIC_UPDATE,
	.clkr = अणु
		.enable_reg = 0x0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "a53pll",
			.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
				.fw_name = "xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_huayra_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा alpha_pll_config ipq_pll_config = अणु
	.l = 0x37,
	.config_ctl_val = 0x04141200,
	.config_ctl_hi_val = 0x0,
	.early_output_mask = BIT(3),
	.मुख्य_output_mask = BIT(0),
पूर्ण;

अटल स्थिर काष्ठा regmap_config ipq_pll_regmap_config = अणु
	.reg_bits		= 32,
	.reg_stride		= 4,
	.val_bits		= 32,
	.max_रेजिस्टर		= 0x40,
	.fast_io		= true,
पूर्ण;

अटल पूर्णांक apss_ipq_pll_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regmap *regmap;
	व्योम __iomem *base;
	पूर्णांक ret;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	regmap = devm_regmap_init_mmio(dev, base, &ipq_pll_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	clk_alpha_pll_configure(&ipq_pll, regmap, &ipq_pll_config);

	ret = devm_clk_रेजिस्टर_regmap(dev, &ipq_pll.clkr);
	अगर (ret)
		वापस ret;

	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get,
					   &ipq_pll.clkr.hw);
पूर्ण

अटल स्थिर काष्ठा of_device_id apss_ipq_pll_match_table[] = अणु
	अणु .compatible = "qcom,ipq6018-a53pll" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, apss_ipq_pll_match_table);

अटल काष्ठा platक्रमm_driver apss_ipq_pll_driver = अणु
	.probe = apss_ipq_pll_probe,
	.driver = अणु
		.name = "qcom-ipq-apss-pll",
		.of_match_table = apss_ipq_pll_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(apss_ipq_pll_driver);

MODULE_DESCRIPTION("Qualcomm technology Inc APSS ALPHA PLL Driver");
MODULE_LICENSE("GPL v2");
