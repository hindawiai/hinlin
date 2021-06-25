<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_घड़ी.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/qcom,lpasscorecc-sc7180.h>

#समावेश "clk-alpha-pll.h"
#समावेश "clk-branch.h"
#समावेश "clk-rcg.h"
#समावेश "clk-regmap.h"
#समावेश "common.h"
#समावेश "gdsc.h"

क्रमागत अणु
	P_BI_TCXO,
	P_LPASS_LPAAUDIO_DIG_PLL_OUT_ODD,
	P_SLEEP_CLK,
पूर्ण;

अटल काष्ठा pll_vco fabia_vco[] = अणु
	अणु 249600000, 2000000000, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा alpha_pll_config lpass_lpaaudio_dig_pll_config = अणु
	.l = 0x20,
	.alpha = 0x0,
	.config_ctl_val = 0x20485699,
	.config_ctl_hi_val = 0x00002067,
	.test_ctl_val = 0x40000000,
	.test_ctl_hi_val = 0x00000000,
	.user_ctl_val = 0x00005105,
	.user_ctl_hi_val = 0x00004805,
पूर्ण;

अटल स्थिर u8 clk_alpha_pll_regs_offset[][PLL_OFF_MAX_REGS] = अणु
	[CLK_ALPHA_PLL_TYPE_FABIA] =  अणु
		[PLL_OFF_L_VAL] = 0x04,
		[PLL_OFF_CAL_L_VAL] = 0x8,
		[PLL_OFF_USER_CTL] = 0x0c,
		[PLL_OFF_USER_CTL_U] = 0x10,
		[PLL_OFF_USER_CTL_U1] = 0x14,
		[PLL_OFF_CONFIG_CTL] = 0x18,
		[PLL_OFF_CONFIG_CTL_U] = 0x1C,
		[PLL_OFF_CONFIG_CTL_U1] = 0x20,
		[PLL_OFF_TEST_CTL] = 0x24,
		[PLL_OFF_TEST_CTL_U] = 0x28,
		[PLL_OFF_STATUS] = 0x30,
		[PLL_OFF_OPMODE] = 0x38,
		[PLL_OFF_FRAC] = 0x40,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll lpass_lpaaudio_dig_pll = अणु
	.offset = 0x1000,
	.vco_table = fabia_vco,
	.num_vco = ARRAY_SIZE(fabia_vco),
	.regs = clk_alpha_pll_regs_offset[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "lpass_lpaaudio_dig_pll",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fabia_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable
			post_भाग_प्रकारable_lpass_lpaaudio_dig_pll_out_odd[] = अणु
	अणु 0x5, 5 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग lpass_lpaaudio_dig_pll_out_odd = अणु
	.offset = 0x1000,
	.post_भाग_shअगरt = 12,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_lpass_lpaaudio_dig_pll_out_odd,
	.num_post_भाग =
		ARRAY_SIZE(post_भाग_प्रकारable_lpass_lpaaudio_dig_pll_out_odd),
	.width = 4,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "lpass_lpaaudio_dig_pll_out_odd",
		.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
			.hw = &lpass_lpaaudio_dig_pll.clkr.hw,
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map lpass_core_cc_parent_map_0[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_LPASS_LPAAUDIO_DIG_PLL_OUT_ODD, 5 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data lpass_core_cc_parent_data_0[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &lpass_lpaaudio_dig_pll_out_odd.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map lpass_core_cc_parent_map_2[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 core_clk_src = अणु
	.cmd_rcgr = 0x1d000,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = lpass_core_cc_parent_map_2,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "core_clk_src",
		.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
			.fw_name = "bi_tcxo",
		पूर्ण,
		.num_parents = 1,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_ext_mclk0_clk_src[] = अणु
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_ext_lpaअगर_clk_src[] = अणु
	F(256000, P_LPASS_LPAAUDIO_DIG_PLL_OUT_ODD, 15, 1, 32),
	F(512000, P_LPASS_LPAAUDIO_DIG_PLL_OUT_ODD, 15, 1, 16),
	F(768000, P_LPASS_LPAAUDIO_DIG_PLL_OUT_ODD, 10, 1, 16),
	F(1024000, P_LPASS_LPAAUDIO_DIG_PLL_OUT_ODD, 15, 1, 8),
	F(1536000, P_LPASS_LPAAUDIO_DIG_PLL_OUT_ODD, 10, 1, 8),
	F(2048000, P_LPASS_LPAAUDIO_DIG_PLL_OUT_ODD, 15, 1, 4),
	F(3072000, P_LPASS_LPAAUDIO_DIG_PLL_OUT_ODD, 10, 1, 4),
	F(4096000, P_LPASS_LPAAUDIO_DIG_PLL_OUT_ODD, 15, 1, 2),
	F(6144000, P_LPASS_LPAAUDIO_DIG_PLL_OUT_ODD, 10, 1, 2),
	F(8192000, P_LPASS_LPAAUDIO_DIG_PLL_OUT_ODD, 15, 0, 0),
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(12288000, P_LPASS_LPAAUDIO_DIG_PLL_OUT_ODD, 10, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(24576000, P_LPASS_LPAAUDIO_DIG_PLL_OUT_ODD, 5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 ext_mclk0_clk_src = अणु
	.cmd_rcgr = 0x20000,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = lpass_core_cc_parent_map_0,
	.freq_tbl = ftbl_ext_mclk0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ext_mclk0_clk_src",
		.parent_data = lpass_core_cc_parent_data_0,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 lpaअगर_pri_clk_src = अणु
	.cmd_rcgr = 0x10000,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = lpass_core_cc_parent_map_0,
	.freq_tbl = ftbl_ext_lpaअगर_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "lpaif_pri_clk_src",
		.parent_data = lpass_core_cc_parent_data_0,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 lpaअगर_sec_clk_src = अणु
	.cmd_rcgr = 0x11000,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = lpass_core_cc_parent_map_0,
	.freq_tbl = ftbl_ext_lpaअगर_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "lpaif_sec_clk_src",
		.parent_data = lpass_core_cc_parent_data_0,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch lpass_audio_core_ext_mclk0_clk = अणु
	.halt_reg = 0x20014,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x20014,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x20014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "lpass_audio_core_ext_mclk0_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &ext_mclk0_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch lpass_audio_core_lpaअगर_pri_ibit_clk = अणु
	.halt_reg = 0x10018,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x10018,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x10018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "lpass_audio_core_lpaif_pri_ibit_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &lpaअगर_pri_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch lpass_audio_core_lpaअगर_sec_ibit_clk = अणु
	.halt_reg = 0x11018,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x11018,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x11018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "lpass_audio_core_lpaif_sec_ibit_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &lpaअगर_sec_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch lpass_audio_core_sysnoc_mport_core_clk = अणु
	.halt_reg = 0x23000,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x23000,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x23000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "lpass_audio_core_sysnoc_mport_core_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &core_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap *lpass_core_cc_sc7180_घड़ीs[] = अणु
	[EXT_MCLK0_CLK_SRC] = &ext_mclk0_clk_src.clkr,
	[LPAIF_PRI_CLK_SRC] = &lpaअगर_pri_clk_src.clkr,
	[LPAIF_SEC_CLK_SRC] = &lpaअगर_sec_clk_src.clkr,
	[CORE_CLK_SRC] = &core_clk_src.clkr,
	[LPASS_AUDIO_CORE_EXT_MCLK0_CLK] = &lpass_audio_core_ext_mclk0_clk.clkr,
	[LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CLK] =
		&lpass_audio_core_lpaअगर_pri_ibit_clk.clkr,
	[LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CLK] =
		&lpass_audio_core_lpaअगर_sec_ibit_clk.clkr,
	[LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CLK] =
		&lpass_audio_core_sysnoc_mport_core_clk.clkr,
	[LPASS_LPAAUDIO_DIG_PLL] = &lpass_lpaaudio_dig_pll.clkr,
	[LPASS_LPAAUDIO_DIG_PLL_OUT_ODD] = &lpass_lpaaudio_dig_pll_out_odd.clkr,
पूर्ण;

अटल काष्ठा gdsc lpass_pdc_hm_gdsc = अणु
	.gdscr = 0x3090,
	.pd = अणु
		.name = "lpass_pdc_hm_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc lpass_audio_hm_gdsc = अणु
	.gdscr = 0x9090,
	.pd = अणु
		.name = "lpass_audio_hm_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc lpass_core_hm_gdsc = अणु
	.gdscr = 0x0,
	.pd = अणु
		.name = "lpass_core_hm_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = RETAIN_FF_ENABLE,
पूर्ण;

अटल काष्ठा gdsc *lpass_core_hm_sc7180_gdscs[] = अणु
	[LPASS_CORE_HM_GDSCR] = &lpass_core_hm_gdsc,
पूर्ण;

अटल काष्ठा gdsc *lpass_audio_hm_sc7180_gdscs[] = अणु
	[LPASS_PDC_HM_GDSCR] = &lpass_pdc_hm_gdsc,
	[LPASS_AUDIO_HM_GDSCR] = &lpass_audio_hm_gdsc,
पूर्ण;

अटल काष्ठा regmap_config lpass_core_cc_sc7180_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.fast_io = true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc lpass_core_hm_sc7180_desc = अणु
	.config = &lpass_core_cc_sc7180_regmap_config,
	.gdscs = lpass_core_hm_sc7180_gdscs,
	.num_gdscs = ARRAY_SIZE(lpass_core_hm_sc7180_gdscs),
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc lpass_core_cc_sc7180_desc = अणु
	.config = &lpass_core_cc_sc7180_regmap_config,
	.clks = lpass_core_cc_sc7180_घड़ीs,
	.num_clks = ARRAY_SIZE(lpass_core_cc_sc7180_घड़ीs),
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc lpass_audio_hm_sc7180_desc = अणु
	.config = &lpass_core_cc_sc7180_regmap_config,
	.gdscs = lpass_audio_hm_sc7180_gdscs,
	.num_gdscs = ARRAY_SIZE(lpass_audio_hm_sc7180_gdscs),
पूर्ण;

अटल व्योम lpass_pm_runसमय_disable(व्योम *data)
अणु
	pm_runसमय_disable(data);
पूर्ण

अटल व्योम lpass_pm_clk_destroy(व्योम *data)
अणु
	pm_clk_destroy(data);
पूर्ण

अटल पूर्णांक lpass_create_pm_clks(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 500);
	pm_runसमय_enable(&pdev->dev);

	ret = devm_add_action_or_reset(&pdev->dev, lpass_pm_runसमय_disable, &pdev->dev);
	अगर (ret)
		वापस ret;

	ret = pm_clk_create(&pdev->dev);
	अगर (ret)
		वापस ret;
	ret = devm_add_action_or_reset(&pdev->dev, lpass_pm_clk_destroy, &pdev->dev);
	अगर (ret)
		वापस ret;

	ret = pm_clk_add(&pdev->dev, "iface");
	अगर (ret < 0)
		dev_err(&pdev->dev, "failed to acquire iface clock\n");

	वापस ret;
पूर्ण

अटल पूर्णांक lpass_core_cc_sc7180_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा qcom_cc_desc *desc;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	ret = lpass_create_pm_clks(pdev);
	अगर (ret)
		वापस ret;

	lpass_core_cc_sc7180_regmap_config.name = "lpass_audio_cc";
	desc = &lpass_audio_hm_sc7180_desc;
	ret = qcom_cc_probe_by_index(pdev, 1, desc);
	अगर (ret)
		वापस ret;

	lpass_core_cc_sc7180_regmap_config.name = "lpass_core_cc";
	regmap = qcom_cc_map(pdev, &lpass_core_cc_sc7180_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/*
	 * Keep the CLK always-ON
	 * LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CLK
	 */
	regmap_update_bits(regmap, 0x24000, BIT(0), BIT(0));

	/* PLL settings */
	regmap_ग_लिखो(regmap, 0x1008, 0x20);
	regmap_update_bits(regmap, 0x1014, BIT(0), BIT(0));

	clk_fabia_pll_configure(&lpass_lpaaudio_dig_pll, regmap,
				&lpass_lpaaudio_dig_pll_config);

	ret = qcom_cc_really_probe(pdev, &lpass_core_cc_sc7180_desc, regmap);

	pm_runसमय_mark_last_busy(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक lpass_hm_core_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा qcom_cc_desc *desc;
	पूर्णांक ret;

	ret = lpass_create_pm_clks(pdev);
	अगर (ret)
		वापस ret;

	lpass_core_cc_sc7180_regmap_config.name = "lpass_hm_core";
	desc = &lpass_core_hm_sc7180_desc;

	वापस qcom_cc_probe_by_index(pdev, 0, desc);
पूर्ण

अटल स्थिर काष्ठा of_device_id lpass_hm_sc7180_match_table[] = अणु
	अणु
		.compatible = "qcom,sc7180-lpasshm",
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lpass_hm_sc7180_match_table);

अटल स्थिर काष्ठा of_device_id lpass_core_cc_sc7180_match_table[] = अणु
	अणु
		.compatible = "qcom,sc7180-lpasscorecc",
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lpass_core_cc_sc7180_match_table);

अटल स्थिर काष्ठा dev_pm_ops lpass_core_cc_pm_ops = अणु
	SET_RUNTIME_PM_OPS(pm_clk_suspend, pm_clk_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver lpass_core_cc_sc7180_driver = अणु
	.probe = lpass_core_cc_sc7180_probe,
	.driver = अणु
		.name = "lpass_core_cc-sc7180",
		.of_match_table = lpass_core_cc_sc7180_match_table,
		.pm = &lpass_core_cc_pm_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops lpass_hm_pm_ops = अणु
	SET_RUNTIME_PM_OPS(pm_clk_suspend, pm_clk_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver lpass_hm_sc7180_driver = अणु
	.probe = lpass_hm_core_probe,
	.driver = अणु
		.name = "lpass_hm-sc7180",
		.of_match_table = lpass_hm_sc7180_match_table,
		.pm = &lpass_hm_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init lpass_sc7180_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&lpass_core_cc_sc7180_driver);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&lpass_hm_sc7180_driver);
	अगर (ret) अणु
		platक्रमm_driver_unरेजिस्टर(&lpass_core_cc_sc7180_driver);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
subsys_initcall(lpass_sc7180_init);

अटल व्योम __निकास lpass_sc7180_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&lpass_hm_sc7180_driver);
	platक्रमm_driver_unरेजिस्टर(&lpass_core_cc_sc7180_driver);
पूर्ण
module_निकास(lpass_sc7180_निकास);

MODULE_DESCRIPTION("QTI LPASS_CORE_CC SC7180 Driver");
MODULE_LICENSE("GPL v2");
