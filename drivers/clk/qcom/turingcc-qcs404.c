<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019, Linaro Ltd.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pm_घड़ी.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/qcom,turingcc-qcs404.h>

#समावेश "clk-regmap.h"
#समावेश "clk-branch.h"
#समावेश "common.h"
#समावेश "reset.h"

अटल काष्ठा clk_branch turing_wrapper_aon_cbcr = अणु
	.halt_reg = 0x5098,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x5098,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data) अणु
			.name = "turing_wrapper_aon_clk",
			.ops = &clk_branch2_aon_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch turing_q6ss_ahbm_aon_cbcr = अणु
	.halt_reg = 0x9000,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data) अणु
			.name = "turing_q6ss_ahbm_aon_cbcr",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch turing_q6ss_q6_axim_clk = अणु
	.halt_reg = 0xb000,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data) अणु
			.name = "turing_q6ss_q6_axim_clk",
			.ops = &clk_branch2_aon_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch turing_q6ss_ahbs_aon_cbcr = अणु
	.halt_reg = 0x10000,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x10000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data) अणु
			.name = "turing_q6ss_ahbs_aon_clk",
			.ops = &clk_branch2_aon_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch turing_wrapper_qos_ahbs_aon_cbcr = अणु
	.halt_reg = 0x11014,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x11014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data) अणु
			.name = "turing_wrapper_qos_ahbs_aon_clk",
			.ops = &clk_branch2_aon_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap *turingcc_घड़ीs[] = अणु
	[TURING_WRAPPER_AON_CLK] = &turing_wrapper_aon_cbcr.clkr,
	[TURING_Q6SS_AHBM_AON_CLK] = &turing_q6ss_ahbm_aon_cbcr.clkr,
	[TURING_Q6SS_Q6_AXIM_CLK] = &turing_q6ss_q6_axim_clk.clkr,
	[TURING_Q6SS_AHBS_AON_CLK] = &turing_q6ss_ahbs_aon_cbcr.clkr,
	[TURING_WRAPPER_QOS_AHBS_AON_CLK] = &turing_wrapper_qos_ahbs_aon_cbcr.clkr,
पूर्ण;

अटल स्थिर काष्ठा regmap_config turingcc_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x23004,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc turingcc_desc = अणु
	.config = &turingcc_regmap_config,
	.clks = turingcc_घड़ीs,
	.num_clks = ARRAY_SIZE(turingcc_घड़ीs),
पूर्ण;

अटल पूर्णांक turingcc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	pm_runसमय_enable(&pdev->dev);
	ret = pm_clk_create(&pdev->dev);
	अगर (ret)
		जाओ disable_pm_runसमय;

	ret = pm_clk_add(&pdev->dev, शून्य);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to acquire iface clock\n");
		जाओ destroy_pm_clk;
	पूर्ण

	ret = qcom_cc_probe(pdev, &turingcc_desc);
	अगर (ret < 0)
		जाओ destroy_pm_clk;

	वापस 0;

destroy_pm_clk:
	pm_clk_destroy(&pdev->dev);

disable_pm_runसमय:
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक turingcc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_clk_destroy(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops turingcc_pm_ops = अणु
	SET_RUNTIME_PM_OPS(pm_clk_suspend, pm_clk_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id turingcc_match_table[] = अणु
	अणु .compatible = "qcom,qcs404-turingcc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, turingcc_match_table);

अटल काष्ठा platक्रमm_driver turingcc_driver = अणु
	.probe		= turingcc_probe,
	.हटाओ		= turingcc_हटाओ,
	.driver		= अणु
		.name	= "qcs404-turingcc",
		.of_match_table = turingcc_match_table,
		.pm = &turingcc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(turingcc_driver);

MODULE_DESCRIPTION("Qualcomm QCS404 Turing Clock Controller");
MODULE_LICENSE("GPL v2");
