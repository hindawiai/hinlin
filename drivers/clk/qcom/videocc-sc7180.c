<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2019, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/qcom,videocc-sc7180.h>

#समावेश "clk-alpha-pll.h"
#समावेश "clk-branch.h"
#समावेश "clk-rcg.h"
#समावेश "clk-regmap.h"
#समावेश "common.h"
#समावेश "gdsc.h"

क्रमागत अणु
	P_BI_TCXO,
	P_VIDEO_PLL0_OUT_MAIN,
पूर्ण;

अटल स्थिर काष्ठा pll_vco fabia_vco[] = अणु
	अणु 249600000, 2000000000, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll video_pll0 = अणु
	.offset = 0x42c,
	.vco_table = fabia_vco,
	.num_vco = ARRAY_SIZE(fabia_vco),
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_pll0",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fabia_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map video_cc_parent_map_1[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_VIDEO_PLL0_OUT_MAIN, 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data video_cc_parent_data_1[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &video_pll0.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_video_cc_venus_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(150000000, P_VIDEO_PLL0_OUT_MAIN, 4, 0, 0),
	F(270000000, P_VIDEO_PLL0_OUT_MAIN, 2.5, 0, 0),
	F(340000000, P_VIDEO_PLL0_OUT_MAIN, 2, 0, 0),
	F(434000000, P_VIDEO_PLL0_OUT_MAIN, 2, 0, 0),
	F(500000000, P_VIDEO_PLL0_OUT_MAIN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 video_cc_venus_clk_src = अणु
	.cmd_rcgr = 0x7f0,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = video_cc_parent_map_1,
	.freq_tbl = ftbl_video_cc_venus_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "video_cc_venus_clk_src",
		.parent_data = video_cc_parent_data_1,
		.num_parents = ARRAY_SIZE(video_cc_parent_data_1),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_vcodec0_axi_clk = अणु
	.halt_reg = 0x9ec,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9ec,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_vcodec0_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_vcodec0_core_clk = अणु
	.halt_reg = 0x890,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x890,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_vcodec0_core_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &video_cc_venus_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_venus_ahb_clk = अणु
	.halt_reg = 0xa4c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa4c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_venus_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_venus_ctl_axi_clk = अणु
	.halt_reg = 0x9cc,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9cc,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_venus_ctl_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_venus_ctl_core_clk = अणु
	.halt_reg = 0x850,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x850,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_venus_ctl_core_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &video_cc_venus_clk_src.clkr.hw,
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

अटल काष्ठा clk_regmap *video_cc_sc7180_घड़ीs[] = अणु
	[VIDEO_CC_VCODEC0_AXI_CLK] = &video_cc_vcodec0_axi_clk.clkr,
	[VIDEO_CC_VCODEC0_CORE_CLK] = &video_cc_vcodec0_core_clk.clkr,
	[VIDEO_CC_VENUS_AHB_CLK] = &video_cc_venus_ahb_clk.clkr,
	[VIDEO_CC_VENUS_CLK_SRC] = &video_cc_venus_clk_src.clkr,
	[VIDEO_CC_VENUS_CTL_AXI_CLK] = &video_cc_venus_ctl_axi_clk.clkr,
	[VIDEO_CC_VENUS_CTL_CORE_CLK] = &video_cc_venus_ctl_core_clk.clkr,
	[VIDEO_PLL0] = &video_pll0.clkr,
पूर्ण;

अटल काष्ठा gdsc *video_cc_sc7180_gdscs[] = अणु
	[VENUS_GDSC] = &venus_gdsc,
	[VCODEC0_GDSC] = &vcodec0_gdsc,
पूर्ण;

अटल स्थिर काष्ठा regmap_config video_cc_sc7180_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = 0xb94,
	.fast_io = true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc video_cc_sc7180_desc = अणु
	.config = &video_cc_sc7180_regmap_config,
	.clks = video_cc_sc7180_घड़ीs,
	.num_clks = ARRAY_SIZE(video_cc_sc7180_घड़ीs),
	.gdscs = video_cc_sc7180_gdscs,
	.num_gdscs = ARRAY_SIZE(video_cc_sc7180_gdscs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id video_cc_sc7180_match_table[] = अणु
	अणु .compatible = "qcom,sc7180-videocc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, video_cc_sc7180_match_table);

अटल पूर्णांक video_cc_sc7180_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;
	काष्ठा alpha_pll_config video_pll0_config = अणुपूर्ण;

	regmap = qcom_cc_map(pdev, &video_cc_sc7180_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	video_pll0_config.l = 0x1f;
	video_pll0_config.alpha = 0x4000;
	video_pll0_config.user_ctl_val = 0x00000001;
	video_pll0_config.user_ctl_hi_val = 0x00004805;

	clk_fabia_pll_configure(&video_pll0, regmap, &video_pll0_config);

	/* Keep VIDEO_CC_XO_CLK ALWAYS-ON */
	regmap_update_bits(regmap, 0x984, 0x1, 0x1);

	वापस qcom_cc_really_probe(pdev, &video_cc_sc7180_desc, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver video_cc_sc7180_driver = अणु
	.probe = video_cc_sc7180_probe,
	.driver = अणु
		.name = "sc7180-videocc",
		.of_match_table = video_cc_sc7180_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init video_cc_sc7180_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&video_cc_sc7180_driver);
पूर्ण
subsys_initcall(video_cc_sc7180_init);

अटल व्योम __निकास video_cc_sc7180_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&video_cc_sc7180_driver);
पूर्ण
module_निकास(video_cc_sc7180_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("QTI VIDEOCC SC7180 Driver");
