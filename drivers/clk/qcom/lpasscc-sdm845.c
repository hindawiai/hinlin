<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/qcom,lpass-sdm845.h>

#समावेश "clk-regmap.h"
#समावेश "clk-branch.h"
#समावेश "common.h"

अटल काष्ठा clk_branch lpass_q6ss_ahbm_aon_clk = अणु
	.halt_reg = 0x12000,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x12000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "lpass_q6ss_ahbm_aon_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch lpass_q6ss_ahbs_aon_clk = अणु
	.halt_reg = 0x1f000,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x1f000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "lpass_q6ss_ahbs_aon_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch lpass_qdsp6ss_core_clk = अणु
	.halt_reg = 0x20,
	/* CLK_OFF would not toggle until LPASS is out of reset */
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x20,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "lpass_qdsp6ss_core_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch lpass_qdsp6ss_xo_clk = अणु
	.halt_reg = 0x38,
	/* CLK_OFF would not toggle until LPASS is out of reset */
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x38,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "lpass_qdsp6ss_xo_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch lpass_qdsp6ss_sleep_clk = अणु
	.halt_reg = 0x3c,
	/* CLK_OFF would not toggle until LPASS is out of reset */
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x3c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "lpass_qdsp6ss_sleep_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा regmap_config lpass_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.fast_io	= true,
पूर्ण;

अटल काष्ठा clk_regmap *lpass_cc_sdm845_घड़ीs[] = अणु
	[LPASS_Q6SS_AHBM_AON_CLK] = &lpass_q6ss_ahbm_aon_clk.clkr,
	[LPASS_Q6SS_AHBS_AON_CLK] = &lpass_q6ss_ahbs_aon_clk.clkr,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc lpass_cc_sdm845_desc = अणु
	.config = &lpass_regmap_config,
	.clks = lpass_cc_sdm845_घड़ीs,
	.num_clks = ARRAY_SIZE(lpass_cc_sdm845_घड़ीs),
पूर्ण;

अटल काष्ठा clk_regmap *lpass_qdsp6ss_sdm845_घड़ीs[] = अणु
	[LPASS_QDSP6SS_XO_CLK] = &lpass_qdsp6ss_xo_clk.clkr,
	[LPASS_QDSP6SS_SLEEP_CLK] = &lpass_qdsp6ss_sleep_clk.clkr,
	[LPASS_QDSP6SS_CORE_CLK] = &lpass_qdsp6ss_core_clk.clkr,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc lpass_qdsp6ss_sdm845_desc = अणु
	.config = &lpass_regmap_config,
	.clks = lpass_qdsp6ss_sdm845_घड़ीs,
	.num_clks = ARRAY_SIZE(lpass_qdsp6ss_sdm845_घड़ीs),
पूर्ण;

अटल पूर्णांक lpass_cc_sdm845_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा qcom_cc_desc *desc;
	पूर्णांक ret;

	lpass_regmap_config.name = "cc";
	desc = &lpass_cc_sdm845_desc;

	ret = qcom_cc_probe_by_index(pdev, 0, desc);
	अगर (ret)
		वापस ret;

	lpass_regmap_config.name = "qdsp6ss";
	desc = &lpass_qdsp6ss_sdm845_desc;

	वापस qcom_cc_probe_by_index(pdev, 1, desc);
पूर्ण

अटल स्थिर काष्ठा of_device_id lpass_cc_sdm845_match_table[] = अणु
	अणु .compatible = "qcom,sdm845-lpasscc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lpass_cc_sdm845_match_table);

अटल काष्ठा platक्रमm_driver lpass_cc_sdm845_driver = अणु
	.probe		= lpass_cc_sdm845_probe,
	.driver		= अणु
		.name	= "sdm845-lpasscc",
		.of_match_table = lpass_cc_sdm845_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init lpass_cc_sdm845_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&lpass_cc_sdm845_driver);
पूर्ण
subsys_initcall(lpass_cc_sdm845_init);

अटल व्योम __निकास lpass_cc_sdm845_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&lpass_cc_sdm845_driver);
पूर्ण
module_निकास(lpass_cc_sdm845_निकास);

MODULE_DESCRIPTION("QTI LPASS_CC SDM845 Driver");
MODULE_LICENSE("GPL v2");
