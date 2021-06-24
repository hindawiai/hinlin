<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2018-2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/qcom,videocc-sm8250.h>

#समावेश "clk-alpha-pll.h"
#समावेश "clk-branch.h"
#समावेश "clk-rcg.h"
#समावेश "clk-regmap.h"
#समावेश "clk-regmap-divider.h"
#समावेश "common.h"
#समावेश "reset.h"
#समावेश "gdsc.h"

क्रमागत अणु
	P_BI_TCXO,
	P_VIDEO_PLL0_OUT_MAIN,
	P_VIDEO_PLL1_OUT_MAIN,
पूर्ण;

अटल काष्ठा pll_vco lucid_vco[] = अणु
	अणु 249600000, 2000000000, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा alpha_pll_config video_pll0_config = अणु
	.l = 0x25,
	.alpha = 0x8000,
	.config_ctl_val = 0x20485699,
	.config_ctl_hi_val = 0x00002261,
	.config_ctl_hi1_val = 0x329A699C,
	.user_ctl_val = 0x00000000,
	.user_ctl_hi_val = 0x00000805,
	.user_ctl_hi1_val = 0x00000000,
पूर्ण;

अटल काष्ठा clk_alpha_pll video_pll0 = अणु
	.offset = 0x42c,
	.vco_table = lucid_vco,
	.num_vco = ARRAY_SIZE(lucid_vco),
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_LUCID],
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_pll0",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_lucid_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा alpha_pll_config video_pll1_config = अणु
	.l = 0x2B,
	.alpha = 0xC000,
	.config_ctl_val = 0x20485699,
	.config_ctl_hi_val = 0x00002261,
	.config_ctl_hi1_val = 0x329A699C,
	.user_ctl_val = 0x00000000,
	.user_ctl_hi_val = 0x00000805,
	.user_ctl_hi1_val = 0x00000000,
पूर्ण;

अटल काष्ठा clk_alpha_pll video_pll1 = अणु
	.offset = 0x7d0,
	.vco_table = lucid_vco,
	.num_vco = ARRAY_SIZE(lucid_vco),
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_LUCID],
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_pll1",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_lucid_ops,
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

अटल स्थिर काष्ठा parent_map video_cc_parent_map_2[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_VIDEO_PLL1_OUT_MAIN, 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data video_cc_parent_data_2[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &video_pll1.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_video_cc_mvs0_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(720000000, P_VIDEO_PLL0_OUT_MAIN, 1, 0, 0),
	F(1014000000, P_VIDEO_PLL0_OUT_MAIN, 1, 0, 0),
	F(1098000000, P_VIDEO_PLL0_OUT_MAIN, 1, 0, 0),
	F(1332000000, P_VIDEO_PLL0_OUT_MAIN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 video_cc_mvs0_clk_src = अणु
	.cmd_rcgr = 0xb94,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = video_cc_parent_map_1,
	.freq_tbl = ftbl_video_cc_mvs0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "video_cc_mvs0_clk_src",
		.parent_data = video_cc_parent_data_1,
		.num_parents = ARRAY_SIZE(video_cc_parent_data_1),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_video_cc_mvs1_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(840000000, P_VIDEO_PLL1_OUT_MAIN, 1, 0, 0),
	F(1098000000, P_VIDEO_PLL1_OUT_MAIN, 1, 0, 0),
	F(1332000000, P_VIDEO_PLL1_OUT_MAIN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 video_cc_mvs1_clk_src = अणु
	.cmd_rcgr = 0xbb4,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = video_cc_parent_map_2,
	.freq_tbl = ftbl_video_cc_mvs1_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "video_cc_mvs1_clk_src",
		.parent_data = video_cc_parent_data_2,
		.num_parents = ARRAY_SIZE(video_cc_parent_data_2),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_भाग video_cc_mvs0c_भाग2_भाग_clk_src = अणु
	.reg = 0xc54,
	.shअगरt = 0,
	.width = 2,
	.clkr.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "video_cc_mvs0c_div2_div_clk_src",
		.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
			&video_cc_mvs0_clk_src.clkr.hw,
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_regmap_भाग_ro_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_भाग video_cc_mvs0_भाग_clk_src = अणु
	.reg = 0xd54,
	.shअगरt = 0,
	.width = 2,
	.clkr.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "video_cc_mvs0_div_clk_src",
		.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
			&video_cc_mvs0_clk_src.clkr.hw,
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_regmap_भाग_ro_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_भाग video_cc_mvs1c_भाग2_भाग_clk_src = अणु
	.reg = 0xcf4,
	.shअगरt = 0,
	.width = 2,
	.clkr.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "video_cc_mvs1c_div2_div_clk_src",
		.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
			&video_cc_mvs1_clk_src.clkr.hw,
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_regmap_भाग_ro_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_mvs0c_clk = अणु
	.halt_reg = 0xc34,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xc34,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_mvs0c_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&video_cc_mvs0c_भाग2_भाग_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_mvs0_clk = अणु
	.halt_reg = 0xd34,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0xd34,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_mvs0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&video_cc_mvs0_भाग_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_mvs1_भाग2_clk = अणु
	.halt_reg = 0xdf4,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0xdf4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_mvs1_div2_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&video_cc_mvs1c_भाग2_भाग_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_mvs1c_clk = अणु
	.halt_reg = 0xcd4,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0xcd4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_mvs1c_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&video_cc_mvs1c_भाग2_भाग_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gdsc mvs0c_gdsc = अणु
	.gdscr = 0xbf8,
	.pd = अणु
		.name = "mvs0c_gdsc",
	पूर्ण,
	.flags = 0,
	.pwrsts = PWRSTS_OFF_ON,
	.supply = "mmcx",
पूर्ण;

अटल काष्ठा gdsc mvs1c_gdsc = अणु
	.gdscr = 0xc98,
	.pd = अणु
		.name = "mvs1c_gdsc",
	पूर्ण,
	.flags = 0,
	.pwrsts = PWRSTS_OFF_ON,
	.supply = "mmcx",
पूर्ण;

अटल काष्ठा gdsc mvs0_gdsc = अणु
	.gdscr = 0xd18,
	.pd = अणु
		.name = "mvs0_gdsc",
	पूर्ण,
	.flags = HW_CTRL,
	.pwrsts = PWRSTS_OFF_ON,
	.supply = "mmcx",
पूर्ण;

अटल काष्ठा gdsc mvs1_gdsc = अणु
	.gdscr = 0xd98,
	.pd = अणु
		.name = "mvs1_gdsc",
	पूर्ण,
	.flags = HW_CTRL,
	.pwrsts = PWRSTS_OFF_ON,
	.supply = "mmcx",
पूर्ण;

अटल काष्ठा clk_regmap *video_cc_sm8250_घड़ीs[] = अणु
	[VIDEO_CC_MVS0_CLK] = &video_cc_mvs0_clk.clkr,
	[VIDEO_CC_MVS0_CLK_SRC] = &video_cc_mvs0_clk_src.clkr,
	[VIDEO_CC_MVS0_DIV_CLK_SRC] = &video_cc_mvs0_भाग_clk_src.clkr,
	[VIDEO_CC_MVS0C_CLK] = &video_cc_mvs0c_clk.clkr,
	[VIDEO_CC_MVS0C_DIV2_DIV_CLK_SRC] = &video_cc_mvs0c_भाग2_भाग_clk_src.clkr,
	[VIDEO_CC_MVS1_CLK_SRC] = &video_cc_mvs1_clk_src.clkr,
	[VIDEO_CC_MVS1_DIV2_CLK] = &video_cc_mvs1_भाग2_clk.clkr,
	[VIDEO_CC_MVS1C_CLK] = &video_cc_mvs1c_clk.clkr,
	[VIDEO_CC_MVS1C_DIV2_DIV_CLK_SRC] = &video_cc_mvs1c_भाग2_भाग_clk_src.clkr,
	[VIDEO_CC_PLL0] = &video_pll0.clkr,
	[VIDEO_CC_PLL1] = &video_pll1.clkr,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map video_cc_sm8250_resets[] = अणु
	[VIDEO_CC_CVP_INTERFACE_BCR] = अणु 0xe54 पूर्ण,
	[VIDEO_CC_CVP_MVS0_BCR] = अणु 0xd14 पूर्ण,
	[VIDEO_CC_MVS0C_CLK_ARES] = अणु 0xc34, 2 पूर्ण,
	[VIDEO_CC_CVP_MVS0C_BCR] = अणु 0xbf4 पूर्ण,
	[VIDEO_CC_CVP_MVS1_BCR] = अणु 0xd94 पूर्ण,
	[VIDEO_CC_MVS1C_CLK_ARES] = अणु 0xcd4, 2 पूर्ण,
	[VIDEO_CC_CVP_MVS1C_BCR] = अणु 0xc94 पूर्ण,
पूर्ण;

अटल काष्ठा gdsc *video_cc_sm8250_gdscs[] = अणु
	[MVS0C_GDSC] = &mvs0c_gdsc,
	[MVS1C_GDSC] = &mvs1c_gdsc,
	[MVS0_GDSC] = &mvs0_gdsc,
	[MVS1_GDSC] = &mvs1_gdsc,
पूर्ण;

अटल स्थिर काष्ठा regmap_config video_cc_sm8250_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = 0xf4c,
	.fast_io = true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc video_cc_sm8250_desc = अणु
	.config = &video_cc_sm8250_regmap_config,
	.clks = video_cc_sm8250_घड़ीs,
	.num_clks = ARRAY_SIZE(video_cc_sm8250_घड़ीs),
	.resets = video_cc_sm8250_resets,
	.num_resets = ARRAY_SIZE(video_cc_sm8250_resets),
	.gdscs = video_cc_sm8250_gdscs,
	.num_gdscs = ARRAY_SIZE(video_cc_sm8250_gdscs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id video_cc_sm8250_match_table[] = अणु
	अणु .compatible = "qcom,sm8250-videocc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, video_cc_sm8250_match_table);

अटल पूर्णांक video_cc_sm8250_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;

	regmap = qcom_cc_map(pdev, &video_cc_sm8250_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	clk_lucid_pll_configure(&video_pll0, regmap, &video_pll0_config);
	clk_lucid_pll_configure(&video_pll1, regmap, &video_pll1_config);

	/* Keep VIDEO_CC_AHB_CLK and VIDEO_CC_XO_CLK ALWAYS-ON */
	regmap_update_bits(regmap, 0xe58, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0xeec, BIT(0), BIT(0));

	वापस qcom_cc_really_probe(pdev, &video_cc_sm8250_desc, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver video_cc_sm8250_driver = अणु
	.probe	= video_cc_sm8250_probe,
	.driver	= अणु
		.name = "sm8250-videocc",
		.of_match_table = video_cc_sm8250_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init video_cc_sm8250_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&video_cc_sm8250_driver);
पूर्ण
subsys_initcall(video_cc_sm8250_init);

अटल व्योम __निकास video_cc_sm8250_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&video_cc_sm8250_driver);
पूर्ण
module_निकास(video_cc_sm8250_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("QTI VIDEOCC SM8250 Driver");
