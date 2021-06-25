<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>
#समावेश <linux/module.h>

#समावेश <dt-bindings/घड़ी/qcom,apss-ipq.h>

#समावेश "common.h"
#समावेश "clk-regmap.h"
#समावेश "clk-branch.h"
#समावेश "clk-alpha-pll.h"
#समावेश "clk-regmap-mux.h"

क्रमागत अणु
	P_XO,
	P_APSS_PLL_EARLY,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data parents_apcs_alias0_clk_src[] = अणु
	अणु .fw_name = "xo" पूर्ण,
	अणु .fw_name = "pll" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map parents_apcs_alias0_clk_src_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_APSS_PLL_EARLY, 5 पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_mux apcs_alias0_clk_src = अणु
	.reg = 0x0050,
	.width = 3,
	.shअगरt = 7,
	.parent_map = parents_apcs_alias0_clk_src_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "apcs_alias0_clk_src",
		.parent_data = parents_apcs_alias0_clk_src,
		.num_parents = 2,
		.ops = &clk_regmap_mux_बंदst_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch apcs_alias0_core_clk = अणु
	.halt_reg = 0x0058,
	.clkr = अणु
		.enable_reg = 0x0058,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "apcs_alias0_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&apcs_alias0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config apss_ipq6018_regmap_config = अणु
	.reg_bits       = 32,
	.reg_stride     = 4,
	.val_bits       = 32,
	.max_रेजिस्टर   = 0x1000,
	.fast_io        = true,
पूर्ण;

अटल काष्ठा clk_regmap *apss_ipq6018_clks[] = अणु
	[APCS_ALIAS0_CLK_SRC] = &apcs_alias0_clk_src.clkr,
	[APCS_ALIAS0_CORE_CLK] = &apcs_alias0_core_clk.clkr,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc apss_ipq6018_desc = अणु
	.config = &apss_ipq6018_regmap_config,
	.clks = apss_ipq6018_clks,
	.num_clks = ARRAY_SIZE(apss_ipq6018_clks),
पूर्ण;

अटल पूर्णांक apss_ipq6018_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;

	regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!regmap)
		वापस -ENODEV;

	वापस qcom_cc_really_probe(pdev, &apss_ipq6018_desc, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver apss_ipq6018_driver = अणु
	.probe = apss_ipq6018_probe,
	.driver = अणु
		.name   = "qcom,apss-ipq6018-clk",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(apss_ipq6018_driver);

MODULE_DESCRIPTION("QCOM APSS IPQ 6018 CLK Driver");
MODULE_LICENSE("GPL v2");
