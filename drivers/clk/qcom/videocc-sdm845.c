<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/qcom,videocc-sdm845.h>

#समावेश "common.h"
#समावेश "clk-alpha-pll.h"
#समावेश "clk-branch.h"
#समावेश "clk-rcg.h"
#समावेश "clk-regmap.h"
#समावेश "clk-pll.h"
#समावेश "gdsc.h"

क्रमागत अणु
	P_BI_TCXO,
	P_VIDEO_PLL0_OUT_MAIN,
	/* P_VIDEO_PLL0_OUT_EVEN, */
	/* P_VIDEO_PLL0_OUT_ODD, */
पूर्ण;

अटल स्थिर काष्ठा alpha_pll_config video_pll0_config = अणु
	.l = 0x10,
	.alpha = 0xaaab,
पूर्ण;

अटल काष्ठा clk_alpha_pll video_pll0 = अणु
	.offset = 0x42c,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_pll0",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo", .name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fabia_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map video_cc_parent_map_0[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_VIDEO_PLL0_OUT_MAIN, 1 पूर्ण,
	/* अणु P_VIDEO_PLL0_OUT_EVEN, 2 पूर्ण, */
	/* अणु P_VIDEO_PLL0_OUT_ODD, 3 पूर्ण, */
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data video_cc_parent_data_0[] = अणु
	अणु .fw_name = "bi_tcxo", .name = "bi_tcxo" पूर्ण,
	अणु .hw = &video_pll0.clkr.hw पूर्ण,
	/* अणु .name = "video_pll0_out_even" पूर्ण, */
	/* अणु .name = "video_pll0_out_odd" पूर्ण, */
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_video_cc_venus_clk_src[] = अणु
	F(100000000, P_VIDEO_PLL0_OUT_MAIN, 4, 0, 0),
	F(200000000, P_VIDEO_PLL0_OUT_MAIN, 2, 0, 0),
	F(330000000, P_VIDEO_PLL0_OUT_MAIN, 1, 0, 0),
	F(404000000, P_VIDEO_PLL0_OUT_MAIN, 1, 0, 0),
	F(444000000, P_VIDEO_PLL0_OUT_MAIN, 1, 0, 0),
	F(533000000, P_VIDEO_PLL0_OUT_MAIN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 video_cc_venus_clk_src = अणु
	.cmd_rcgr = 0x7f0,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = video_cc_parent_map_0,
	.freq_tbl = ftbl_video_cc_venus_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "video_cc_venus_clk_src",
		.parent_data = video_cc_parent_data_0,
		.num_parents = ARRAY_SIZE(video_cc_parent_data_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_apb_clk = अणु
	.halt_reg = 0x990,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x990,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_apb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_at_clk = अणु
	.halt_reg = 0x9f0,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9f0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_at_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_qdss_trig_clk = अणु
	.halt_reg = 0x970,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x970,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_qdss_trig_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_qdss_tsctr_भाग8_clk = अणु
	.halt_reg = 0x9d0,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9d0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_qdss_tsctr_div8_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_vcodec0_axi_clk = अणु
	.halt_reg = 0x930,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x930,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_vcodec0_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_vcodec0_core_clk = अणु
	.halt_reg = 0x890,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x890,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_vcodec0_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&video_cc_venus_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_vcodec1_axi_clk = अणु
	.halt_reg = 0x950,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x950,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_vcodec1_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_vcodec1_core_clk = अणु
	.halt_reg = 0x8d0,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x8d0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_vcodec1_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&video_cc_venus_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_venus_ahb_clk = अणु
	.halt_reg = 0x9b0,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9b0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_cc_venus_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_cc_venus_ctl_axi_clk = अणु
	.halt_reg = 0x910,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x910,
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
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&video_cc_venus_clk_src.clkr.hw,
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
	.cxcs = (अचिन्हित पूर्णांक [])अणु 0x850, 0x910 पूर्ण,
	.cxc_count = 2,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = POLL_CFG_GDSCR,
पूर्ण;

अटल काष्ठा gdsc vcodec0_gdsc = अणु
	.gdscr = 0x874,
	.pd = अणु
		.name = "vcodec0_gdsc",
	पूर्ण,
	.cxcs = (अचिन्हित पूर्णांक [])अणु 0x890, 0x930 पूर्ण,
	.cxc_count = 2,
	.flags = HW_CTRL | POLL_CFG_GDSCR,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc vcodec1_gdsc = अणु
	.gdscr = 0x8b4,
	.pd = अणु
		.name = "vcodec1_gdsc",
	पूर्ण,
	.cxcs = (अचिन्हित पूर्णांक [])अणु 0x8d0, 0x950 पूर्ण,
	.cxc_count = 2,
	.flags = HW_CTRL | POLL_CFG_GDSCR,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा clk_regmap *video_cc_sdm845_घड़ीs[] = अणु
	[VIDEO_CC_APB_CLK] = &video_cc_apb_clk.clkr,
	[VIDEO_CC_AT_CLK] = &video_cc_at_clk.clkr,
	[VIDEO_CC_QDSS_TRIG_CLK] = &video_cc_qdss_trig_clk.clkr,
	[VIDEO_CC_QDSS_TSCTR_DIV8_CLK] = &video_cc_qdss_tsctr_भाग8_clk.clkr,
	[VIDEO_CC_VCODEC0_AXI_CLK] = &video_cc_vcodec0_axi_clk.clkr,
	[VIDEO_CC_VCODEC0_CORE_CLK] = &video_cc_vcodec0_core_clk.clkr,
	[VIDEO_CC_VCODEC1_AXI_CLK] = &video_cc_vcodec1_axi_clk.clkr,
	[VIDEO_CC_VCODEC1_CORE_CLK] = &video_cc_vcodec1_core_clk.clkr,
	[VIDEO_CC_VENUS_AHB_CLK] = &video_cc_venus_ahb_clk.clkr,
	[VIDEO_CC_VENUS_CLK_SRC] = &video_cc_venus_clk_src.clkr,
	[VIDEO_CC_VENUS_CTL_AXI_CLK] = &video_cc_venus_ctl_axi_clk.clkr,
	[VIDEO_CC_VENUS_CTL_CORE_CLK] = &video_cc_venus_ctl_core_clk.clkr,
	[VIDEO_PLL0] = &video_pll0.clkr,
पूर्ण;

अटल काष्ठा gdsc *video_cc_sdm845_gdscs[] = अणु
	[VENUS_GDSC] = &venus_gdsc,
	[VCODEC0_GDSC] = &vcodec0_gdsc,
	[VCODEC1_GDSC] = &vcodec1_gdsc,
पूर्ण;

अटल स्थिर काष्ठा regmap_config video_cc_sdm845_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0xb90,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc video_cc_sdm845_desc = अणु
	.config = &video_cc_sdm845_regmap_config,
	.clks = video_cc_sdm845_घड़ीs,
	.num_clks = ARRAY_SIZE(video_cc_sdm845_घड़ीs),
	.gdscs = video_cc_sdm845_gdscs,
	.num_gdscs = ARRAY_SIZE(video_cc_sdm845_gdscs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id video_cc_sdm845_match_table[] = अणु
	अणु .compatible = "qcom,sdm845-videocc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, video_cc_sdm845_match_table);

अटल पूर्णांक video_cc_sdm845_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;

	regmap = qcom_cc_map(pdev, &video_cc_sdm845_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	clk_fabia_pll_configure(&video_pll0, regmap, &video_pll0_config);

	वापस qcom_cc_really_probe(pdev, &video_cc_sdm845_desc, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver video_cc_sdm845_driver = अणु
	.probe		= video_cc_sdm845_probe,
	.driver		= अणु
		.name	= "sdm845-videocc",
		.of_match_table = video_cc_sdm845_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init video_cc_sdm845_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&video_cc_sdm845_driver);
पूर्ण
subsys_initcall(video_cc_sdm845_init);

अटल व्योम __निकास video_cc_sdm845_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&video_cc_sdm845_driver);
पूर्ण
module_निकास(video_cc_sdm845_निकास);

MODULE_LICENSE("GPL v2");
