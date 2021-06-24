<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_घड़ी.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/qcom,mss-sc7180.h>

#समावेश "clk-regmap.h"
#समावेश "clk-branch.h"
#समावेश "common.h"

अटल काष्ठा clk_branch mss_axi_nav_clk = अणु
	.halt_reg = 0x20bc,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x20bc,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mss_axi_nav_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "gcc_mss_nav_axi",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mss_axi_crypto_clk = अणु
	.halt_reg = 0x20cc,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x20cc,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mss_axi_crypto_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "gcc_mss_mfab_axis",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config mss_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.fast_io	= true,
	.max_रेजिस्टर	= 0x41aa0cc,
पूर्ण;

अटल काष्ठा clk_regmap *mss_sc7180_घड़ीs[] = अणु
	[MSS_AXI_CRYPTO_CLK] = &mss_axi_crypto_clk.clkr,
	[MSS_AXI_NAV_CLK] = &mss_axi_nav_clk.clkr,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc mss_sc7180_desc = अणु
	.config = &mss_regmap_config,
	.clks = mss_sc7180_घड़ीs,
	.num_clks = ARRAY_SIZE(mss_sc7180_घड़ीs),
पूर्ण;

अटल पूर्णांक mss_sc7180_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	pm_runसमय_enable(&pdev->dev);
	ret = pm_clk_create(&pdev->dev);
	अगर (ret)
		जाओ disable_pm_runसमय;

	ret = pm_clk_add(&pdev->dev, "cfg_ahb");
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to acquire iface clock\n");
		जाओ destroy_pm_clk;
	पूर्ण

	ret = qcom_cc_probe(pdev, &mss_sc7180_desc);
	अगर (ret < 0)
		जाओ destroy_pm_clk;

	वापस 0;

destroy_pm_clk:
	pm_clk_destroy(&pdev->dev);

disable_pm_runसमय:
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक mss_sc7180_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_clk_destroy(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mss_sc7180_pm_ops = अणु
	SET_RUNTIME_PM_OPS(pm_clk_suspend, pm_clk_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id mss_sc7180_match_table[] = अणु
	अणु .compatible = "qcom,sc7180-mss" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mss_sc7180_match_table);

अटल काष्ठा platक्रमm_driver mss_sc7180_driver = अणु
	.probe		= mss_sc7180_probe,
	.हटाओ		= mss_sc7180_हटाओ,
	.driver		= अणु
		.name		= "sc7180-mss",
		.of_match_table = mss_sc7180_match_table,
		.pm = &mss_sc7180_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mss_sc7180_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mss_sc7180_driver);
पूर्ण
subsys_initcall(mss_sc7180_init);

अटल व्योम __निकास mss_sc7180_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mss_sc7180_driver);
पूर्ण
module_निकास(mss_sc7180_निकास);

MODULE_DESCRIPTION("QTI MSS SC7180 Driver");
MODULE_LICENSE("GPL v2");
