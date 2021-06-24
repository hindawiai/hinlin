<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_घड़ी.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/qcom,q6sstopcc-qcs404.h>

#समावेश "clk-regmap.h"
#समावेश "clk-branch.h"
#समावेश "common.h"
#समावेश "reset.h"

अटल काष्ठा clk_branch lcc_ahbfabric_cbc_clk = अणु
	.halt_reg = 0x1b004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x1b004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "lcc_ahbfabric_cbc_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch lcc_q6ss_ahbs_cbc_clk = अणु
	.halt_reg = 0x22000,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x22000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "lcc_q6ss_ahbs_cbc_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch lcc_q6ss_tcm_slave_cbc_clk = अणु
	.halt_reg = 0x1c000,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x1c000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "lcc_q6ss_tcm_slave_cbc_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch lcc_q6ss_ahbm_cbc_clk = अणु
	.halt_reg = 0x22004,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x22004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "lcc_q6ss_ahbm_cbc_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch lcc_q6ss_axim_cbc_clk = अणु
	.halt_reg = 0x1c004,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x1c004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "lcc_q6ss_axim_cbc_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch lcc_q6ss_bcr_sleep_clk = अणु
	.halt_reg = 0x6004,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x6004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "lcc_q6ss_bcr_sleep_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* TCSR घड़ी */
अटल काष्ठा clk_branch tcsr_lcc_csr_cbcr_clk = अणु
	.halt_reg = 0x8008,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x8008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "tcsr_lcc_csr_cbcr_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा regmap_config q6sstop_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.fast_io	= true,
पूर्ण;

अटल काष्ठा clk_regmap *q6sstop_qcs404_घड़ीs[] = अणु
	[LCC_AHBFABRIC_CBC_CLK] = &lcc_ahbfabric_cbc_clk.clkr,
	[LCC_Q6SS_AHBS_CBC_CLK] = &lcc_q6ss_ahbs_cbc_clk.clkr,
	[LCC_Q6SS_TCM_SLAVE_CBC_CLK] = &lcc_q6ss_tcm_slave_cbc_clk.clkr,
	[LCC_Q6SS_AHBM_CBC_CLK] = &lcc_q6ss_ahbm_cbc_clk.clkr,
	[LCC_Q6SS_AXIM_CBC_CLK] = &lcc_q6ss_axim_cbc_clk.clkr,
	[LCC_Q6SS_BCR_SLEEP_CLK] = &lcc_q6ss_bcr_sleep_clk.clkr,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map q6sstop_qcs404_resets[] = अणु
	[Q6SSTOP_BCR_RESET] = अणु 0x6000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc q6sstop_qcs404_desc = अणु
	.config = &q6sstop_regmap_config,
	.clks = q6sstop_qcs404_घड़ीs,
	.num_clks = ARRAY_SIZE(q6sstop_qcs404_घड़ीs),
	.resets = q6sstop_qcs404_resets,
	.num_resets = ARRAY_SIZE(q6sstop_qcs404_resets),
पूर्ण;

अटल काष्ठा clk_regmap *tcsr_qcs404_घड़ीs[] = अणु
	[TCSR_Q6SS_LCC_CBCR_CLK] = &tcsr_lcc_csr_cbcr_clk.clkr,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc tcsr_qcs404_desc = अणु
	.config = &q6sstop_regmap_config,
	.clks = tcsr_qcs404_घड़ीs,
	.num_clks = ARRAY_SIZE(tcsr_qcs404_घड़ीs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id q6sstopcc_qcs404_match_table[] = अणु
	अणु .compatible = "qcom,qcs404-q6sstopcc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, q6sstopcc_qcs404_match_table);

अटल पूर्णांक q6sstopcc_qcs404_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा qcom_cc_desc *desc;
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

	q6sstop_regmap_config.name = "q6sstop_tcsr";
	desc = &tcsr_qcs404_desc;

	ret = qcom_cc_probe_by_index(pdev, 1, desc);
	अगर (ret)
		जाओ destroy_pm_clk;

	q6sstop_regmap_config.name = "q6sstop_cc";
	desc = &q6sstop_qcs404_desc;

	ret = qcom_cc_probe_by_index(pdev, 0, desc);
	अगर (ret)
		जाओ destroy_pm_clk;

	वापस 0;

destroy_pm_clk:
	pm_clk_destroy(&pdev->dev);

disable_pm_runसमय:
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक q6sstopcc_qcs404_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_clk_destroy(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops q6sstopcc_pm_ops = अणु
	SET_RUNTIME_PM_OPS(pm_clk_suspend, pm_clk_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver q6sstopcc_qcs404_driver = अणु
	.probe		= q6sstopcc_qcs404_probe,
	.हटाओ		= q6sstopcc_qcs404_हटाओ,
	.driver		= अणु
		.name	= "qcs404-q6sstopcc",
		.of_match_table = q6sstopcc_qcs404_match_table,
		.pm = &q6sstopcc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(q6sstopcc_qcs404_driver);

MODULE_DESCRIPTION("QTI QCS404 Q6SSTOP Clock Controller Driver");
MODULE_LICENSE("GPL v2");
