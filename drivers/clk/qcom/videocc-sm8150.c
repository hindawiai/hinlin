<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017-2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/qcom,videocc-sm8150.h>

#समावेश "common.h"
#समावेश "clk-alpha-pll.h"
#समावेश "clk-branch.h"
#समावेश "clk-rcg.h"
#समावेश "clk-regmap.h"
#समावेश "reset.h"
#समावेश "gdsc.h"

क्रमागत अणु
	P_BI_TCXO,
	P_VIDEO_PLL0_OUT_MAIN,
पूर्ण;

अटल काष्ठा pll_vco trion_vco[] = अणु
	अणु 249600000, 2000000000, 0 पूर्ण,
पूर्ण;

अटल काष्ठा alpha_pll_config video_pll0_config = अणु
	.l = 0x14,
	.alpha = 0xD555,
	.config_ctl_val = 0x20485699,
	.config_ctl_hi_val = 0x00002267,
	.config_ctl_hi1_val = 0x00000024,
	.user_ctl_val = 0x00000000,
	.user_ctl_hi_val = 0x00000805,
	.user_ctl_hi1_val = 0x000000D0,
पूर्ण;

अटल काष्ठा clk_alpha_pll video_pll0 = अणु
	.offset = 0x42c,
	.vco_table = trion_vco,
	.num_vco = ARRAY_SIZE(trion_vco),
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_TRION],
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_pll0",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_trion_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map video_cc_parent_map_0[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_VIDEO_PLL0_OUT_MAIN, 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data video_cc_parent_data_0[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &video_pll0.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_video_cc_iris_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(200000000, P_VIDEO_PLL0_OUT_MAIN, 2, 0, 0),
	F(240000000, P_VIDEO_PLL0_OUT_MAIN, 2, 0, 0),
	F(338000000, P_VIDEO_PLL0_OUT_MAIN, 2, 0, 0),
	F(365000000, P_VIDEO_PLL0_OUT_MAIN, 2, 0, 0),
	F(444000000, P_VIDEO_PLL0_OUT_MAIN, 2, 0, 0),
	F(533000000, P_VIDEO_PLL0_OUT_MAIN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 video_cc_iris_clk_src = अणु
	.cmd_rcgr = 0x7f0,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = video_cc_parent_map_0,
	.freq_tbl = ftbl_video_cc_iris_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "video_cc_iris_clk_src",
		.parent_data = video_cc_parent_data_0,
		.num_parents = ARRAY_SIZE(video_cc_parent_data_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_iris_ahb_clk = अणु
	.halt_reg = 0x8f4,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x8f4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_iris_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&video_cc_iris_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_mvs0_core_clk = अणु
	.halt_reg = 0x890,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x890,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_mvs0_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&video_cc_iris_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_mvs1_core_clk = अणु
	.halt_reg = 0x8d0,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x8d0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_mvs1_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&video_cc_iris_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_mvsc_core_clk = अणु
	.halt_reg = 0x850,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x850,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_mvsc_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&video_cc_iris_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gdsc venus_gdsc = अणु
	.gdscr = 0x814,
	.pd = अणु
		.name = "venus_gdsc",
	पूर्ण,
	.flags = 0,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc vcodec0_gdsc = अणु
	.gdscr = 0x874,
	.pd = अणु
		.name = "vcodec0_gdsc",
	पूर्ण,
	.flags = HW_CTRL,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc vcodec1_gdsc = अणु
	.gdscr = 0x8b4,
	.pd = अणु
		.name = "vcodec1_gdsc",
	पूर्ण,
	.flags = HW_CTRL,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;
अटल काष्ठा clk_regmap *video_cc_sm8150_घड़ीs[] = अणु
	[VIDEO_CC_IRIS_AHB_CLK] = &video_cc_iris_ahb_clk.clkr,
	[VIDEO_CC_IRIS_CLK_SRC] = &video_cc_iris_clk_src.clkr,
	[VIDEO_CC_MVS0_CORE_CLK] = &video_cc_mvs0_core_clk.clkr,
	[VIDEO_CC_MVS1_CORE_CLK] = &video_cc_mvs1_core_clk.clkr,
	[VIDEO_CC_MVSC_CORE_CLK] = &video_cc_mvsc_core_clk.clkr,
	[VIDEO_CC_PLL0] = &video_pll0.clkr,
पूर्ण;

अटल काष्ठा gdsc *video_cc_sm8150_gdscs[] = अणु
	[VENUS_GDSC] = &venus_gdsc,
	[VCODEC0_GDSC] = &vcodec0_gdsc,
	[VCODEC1_GDSC] = &vcodec1_gdsc,
पूर्ण;

अटल स्थिर काष्ठा regmap_config video_cc_sm8150_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0xb94,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map video_cc_sm8150_resets[] = अणु
	[VIDEO_CC_MVSC_CORE_CLK_BCR] = अणु 0x850, 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc video_cc_sm8150_desc = अणु
	.config = &video_cc_sm8150_regmap_config,
	.clks = video_cc_sm8150_घड़ीs,
	.num_clks = ARRAY_SIZE(video_cc_sm8150_घड़ीs),
	.resets = video_cc_sm8150_resets,
	.num_resets = ARRAY_SIZE(video_cc_sm8150_resets),
	.gdscs = video_cc_sm8150_gdscs,
	.num_gdscs = ARRAY_SIZE(video_cc_sm8150_gdscs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id video_cc_sm8150_match_table[] = अणु
	अणु .compatible = "qcom,sm8150-videocc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, video_cc_sm8150_match_table);

अटल पूर्णांक video_cc_sm8150_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;

	regmap = qcom_cc_map(pdev, &video_cc_sm8150_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	clk_trion_pll_configure(&video_pll0, regmap, &video_pll0_config);

	/* Keep VIDEO_CC_XO_CLK ALWAYS-ON */
	regmap_update_bits(regmap, 0x984, 0x1, 0x1);

	वापस qcom_cc_really_probe(pdev, &video_cc_sm8150_desc, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver video_cc_sm8150_driver = अणु
	.probe = video_cc_sm8150_probe,
	.driver = अणु
		.name	= "video_cc-sm8150",
		.of_match_table = video_cc_sm8150_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init video_cc_sm8150_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&video_cc_sm8150_driver);
पूर्ण
subsys_initcall(video_cc_sm8150_init);

अटल व्योम __निकास video_cc_sm8150_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&video_cc_sm8150_driver);
पूर्ण
module_निकास(video_cc_sm8150_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("QTI VIDEOCC SM8150 Driver");
