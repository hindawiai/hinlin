<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2019, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/qcom,dispcc-sc7180.h>

#समावेश "clk-alpha-pll.h"
#समावेश "clk-branch.h"
#समावेश "clk-rcg.h"
#समावेश "clk-regmap-divider.h"
#समावेश "common.h"
#समावेश "gdsc.h"

क्रमागत अणु
	P_BI_TCXO,
	P_DISP_CC_PLL0_OUT_EVEN,
	P_DISP_CC_PLL0_OUT_MAIN,
	P_DP_PHY_PLL_LINK_CLK,
	P_DP_PHY_PLL_VCO_DIV_CLK,
	P_DSI0_PHY_PLL_OUT_BYTECLK,
	P_DSI0_PHY_PLL_OUT_DSICLK,
	P_GPLL0_OUT_MAIN,
पूर्ण;

अटल स्थिर काष्ठा pll_vco fabia_vco[] = अणु
	अणु 249600000, 2000000000, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll disp_cc_pll0 = अणु
	.offset = 0x0,
	.vco_table = fabia_vco,
	.num_vco = ARRAY_SIZE(fabia_vco),
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_pll0",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fabia_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable post_भाग_प्रकारable_disp_cc_pll0_out_even[] = अणु
	अणु 0x0, 1 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग disp_cc_pll0_out_even = अणु
	.offset = 0x0,
	.post_भाग_shअगरt = 8,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_disp_cc_pll0_out_even,
	.num_post_भाग = ARRAY_SIZE(post_भाग_प्रकारable_disp_cc_pll0_out_even),
	.width = 4,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_pll0_out_even",
		.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
			&disp_cc_pll0.clkr.hw,
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map disp_cc_parent_map_0[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data disp_cc_parent_data_0[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map disp_cc_parent_map_1[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_DP_PHY_PLL_LINK_CLK, 1 पूर्ण,
	अणु P_DP_PHY_PLL_VCO_DIV_CLK, 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data disp_cc_parent_data_1[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .fw_name = "dp_phy_pll_link_clk" पूर्ण,
	अणु .fw_name = "dp_phy_pll_vco_div_clk" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map disp_cc_parent_map_2[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_DSI0_PHY_PLL_OUT_BYTECLK, 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data disp_cc_parent_data_2[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .fw_name = "dsi0_phy_pll_out_byteclk" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map disp_cc_parent_map_3[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_DISP_CC_PLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 4 पूर्ण,
	अणु P_DISP_CC_PLL0_OUT_EVEN, 5 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data disp_cc_parent_data_3[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &disp_cc_pll0.clkr.hw पूर्ण,
	अणु .fw_name = "gcc_disp_gpll0_clk_src" पूर्ण,
	अणु .hw = &disp_cc_pll0_out_even.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map disp_cc_parent_map_4[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 4 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data disp_cc_parent_data_4[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .fw_name = "gcc_disp_gpll0_clk_src" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map disp_cc_parent_map_5[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_DSI0_PHY_PLL_OUT_DSICLK, 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data disp_cc_parent_data_5[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .fw_name = "dsi0_phy_pll_out_dsiclk" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_disp_cc_mdss_ahb_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(37500000, P_GPLL0_OUT_MAIN, 16, 0, 0),
	F(75000000, P_GPLL0_OUT_MAIN, 8, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_ahb_clk_src = अणु
	.cmd_rcgr = 0x22bc,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_4,
	.freq_tbl = ftbl_disp_cc_mdss_ahb_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_ahb_clk_src",
		.parent_data = disp_cc_parent_data_4,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_4),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_byte0_clk_src = अणु
	.cmd_rcgr = 0x2110,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_2,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_byte0_clk_src",
		.parent_data = disp_cc_parent_data_2,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_2),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_byte2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_disp_cc_mdss_dp_aux_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_dp_aux_clk_src = अणु
	.cmd_rcgr = 0x21dc,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_0,
	.freq_tbl = ftbl_disp_cc_mdss_dp_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_dp_aux_clk_src",
		.parent_data = disp_cc_parent_data_0,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_0),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_dp_crypto_clk_src = अणु
	.cmd_rcgr = 0x2194,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_1,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_dp_crypto_clk_src",
		.parent_data = disp_cc_parent_data_1,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_1),
		.ops = &clk_byte2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_dp_link_clk_src = अणु
	.cmd_rcgr = 0x2178,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_1,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_dp_link_clk_src",
		.parent_data = disp_cc_parent_data_1,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_1),
		.ops = &clk_byte2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_dp_pixel_clk_src = अणु
	.cmd_rcgr = 0x21ac,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_1,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_dp_pixel_clk_src",
		.parent_data = disp_cc_parent_data_1,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_1),
		.ops = &clk_dp_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_esc0_clk_src = अणु
	.cmd_rcgr = 0x2148,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_2,
	.freq_tbl = ftbl_disp_cc_mdss_dp_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_esc0_clk_src",
		.parent_data = disp_cc_parent_data_2,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_2),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_disp_cc_mdss_mdp_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(200000000, P_GPLL0_OUT_MAIN, 3, 0, 0),
	F(300000000, P_GPLL0_OUT_MAIN, 2, 0, 0),
	F(345000000, P_DISP_CC_PLL0_OUT_MAIN, 4, 0, 0),
	F(460000000, P_DISP_CC_PLL0_OUT_MAIN, 3, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_mdp_clk_src = अणु
	.cmd_rcgr = 0x20c8,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_3,
	.freq_tbl = ftbl_disp_cc_mdss_mdp_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_mdp_clk_src",
		.parent_data = disp_cc_parent_data_3,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_3),
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_pclk0_clk_src = अणु
	.cmd_rcgr = 0x2098,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_5,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_pclk0_clk_src",
		.parent_data = disp_cc_parent_data_5,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_5),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_pixel_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_rot_clk_src = अणु
	.cmd_rcgr = 0x20e0,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_3,
	.freq_tbl = ftbl_disp_cc_mdss_mdp_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_rot_clk_src",
		.parent_data = disp_cc_parent_data_3,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_3),
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_vsync_clk_src = अणु
	.cmd_rcgr = 0x20f8,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_0,
	.freq_tbl = ftbl_disp_cc_mdss_dp_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_vsync_clk_src",
		.parent_data = disp_cc_parent_data_0,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_0),
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch disp_cc_mdss_ahb_clk = अणु
	.halt_reg = 0x2080,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2080,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_ahb_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch disp_cc_mdss_byte0_clk = अणु
	.halt_reg = 0x2028,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2028,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_byte0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_byte0_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_भाग disp_cc_mdss_byte0_भाग_clk_src = अणु
	.reg = 0x2128,
	.shअगरt = 0,
	.width = 2,
	.clkr.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "disp_cc_mdss_byte0_div_clk_src",
		.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
			.hw = &disp_cc_mdss_byte0_clk_src.clkr.hw
		पूर्ण,
		.num_parents = 1,
		.ops = &clk_regmap_भाग_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_भाग disp_cc_mdss_dp_link_भाग_clk_src = अणु
	.reg = 0x2190,
	.shअगरt = 0,
	.width = 2,
	.clkr.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "disp_cc_mdss_dp_link_div_clk_src",
		.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
			.hw = &disp_cc_mdss_dp_link_clk_src.clkr.hw
		पूर्ण,
		.num_parents = 1,
		.ops = &clk_regmap_भाग_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch disp_cc_mdss_byte0_पूर्णांकf_clk = अणु
	.halt_reg = 0x202c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x202c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_byte0_intf_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_byte0_भाग_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch disp_cc_mdss_dp_aux_clk = अणु
	.halt_reg = 0x2054,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2054,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_dp_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_dp_aux_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch disp_cc_mdss_dp_crypto_clk = अणु
	.halt_reg = 0x2048,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2048,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_dp_crypto_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_dp_crypto_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch disp_cc_mdss_dp_link_clk = अणु
	.halt_reg = 0x2040,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2040,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_dp_link_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_dp_link_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch disp_cc_mdss_dp_link_पूर्णांकf_clk = अणु
	.halt_reg = 0x2044,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2044,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_dp_link_intf_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_dp_link_भाग_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch disp_cc_mdss_dp_pixel_clk = अणु
	.halt_reg = 0x204c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x204c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_dp_pixel_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_dp_pixel_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch disp_cc_mdss_esc0_clk = अणु
	.halt_reg = 0x2038,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2038,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_esc0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_esc0_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch disp_cc_mdss_mdp_clk = अणु
	.halt_reg = 0x200c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x200c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_mdp_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_mdp_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch disp_cc_mdss_mdp_lut_clk = अणु
	.halt_reg = 0x201c,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x201c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_mdp_lut_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_mdp_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch disp_cc_mdss_non_gdsc_ahb_clk = अणु
	.halt_reg = 0x4004,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x4004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_non_gdsc_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_ahb_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch disp_cc_mdss_pclk0_clk = अणु
	.halt_reg = 0x2004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_pclk0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_pclk0_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch disp_cc_mdss_rot_clk = अणु
	.halt_reg = 0x2014,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_rot_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_rot_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch disp_cc_mdss_rscc_vsync_clk = अणु
	.halt_reg = 0x4008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x4008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_rscc_vsync_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_vsync_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch disp_cc_mdss_vsync_clk = अणु
	.halt_reg = 0x2024,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_vsync_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_vsync_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gdsc mdss_gdsc = अणु
	.gdscr = 0x3000,
	.pd = अणु
		.name = "mdss_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = HW_CTRL,
पूर्ण;

अटल काष्ठा gdsc *disp_cc_sc7180_gdscs[] = अणु
	[MDSS_GDSC] = &mdss_gdsc,
पूर्ण;

अटल काष्ठा clk_regmap *disp_cc_sc7180_घड़ीs[] = अणु
	[DISP_CC_MDSS_AHB_CLK] = &disp_cc_mdss_ahb_clk.clkr,
	[DISP_CC_MDSS_AHB_CLK_SRC] = &disp_cc_mdss_ahb_clk_src.clkr,
	[DISP_CC_MDSS_BYTE0_CLK] = &disp_cc_mdss_byte0_clk.clkr,
	[DISP_CC_MDSS_BYTE0_CLK_SRC] = &disp_cc_mdss_byte0_clk_src.clkr,
	[DISP_CC_MDSS_BYTE0_DIV_CLK_SRC] = &disp_cc_mdss_byte0_भाग_clk_src.clkr,
	[DISP_CC_MDSS_BYTE0_INTF_CLK] = &disp_cc_mdss_byte0_पूर्णांकf_clk.clkr,
	[DISP_CC_MDSS_DP_AUX_CLK] = &disp_cc_mdss_dp_aux_clk.clkr,
	[DISP_CC_MDSS_DP_AUX_CLK_SRC] = &disp_cc_mdss_dp_aux_clk_src.clkr,
	[DISP_CC_MDSS_DP_CRYPTO_CLK] = &disp_cc_mdss_dp_crypto_clk.clkr,
	[DISP_CC_MDSS_DP_CRYPTO_CLK_SRC] = &disp_cc_mdss_dp_crypto_clk_src.clkr,
	[DISP_CC_MDSS_DP_LINK_CLK] = &disp_cc_mdss_dp_link_clk.clkr,
	[DISP_CC_MDSS_DP_LINK_CLK_SRC] = &disp_cc_mdss_dp_link_clk_src.clkr,
	[DISP_CC_MDSS_DP_LINK_DIV_CLK_SRC] =
				&disp_cc_mdss_dp_link_भाग_clk_src.clkr,
	[DISP_CC_MDSS_DP_LINK_INTF_CLK] = &disp_cc_mdss_dp_link_पूर्णांकf_clk.clkr,
	[DISP_CC_MDSS_DP_PIXEL_CLK] = &disp_cc_mdss_dp_pixel_clk.clkr,
	[DISP_CC_MDSS_DP_PIXEL_CLK_SRC] = &disp_cc_mdss_dp_pixel_clk_src.clkr,
	[DISP_CC_MDSS_ESC0_CLK] = &disp_cc_mdss_esc0_clk.clkr,
	[DISP_CC_MDSS_ESC0_CLK_SRC] = &disp_cc_mdss_esc0_clk_src.clkr,
	[DISP_CC_MDSS_MDP_CLK] = &disp_cc_mdss_mdp_clk.clkr,
	[DISP_CC_MDSS_MDP_CLK_SRC] = &disp_cc_mdss_mdp_clk_src.clkr,
	[DISP_CC_MDSS_MDP_LUT_CLK] = &disp_cc_mdss_mdp_lut_clk.clkr,
	[DISP_CC_MDSS_NON_GDSC_AHB_CLK] = &disp_cc_mdss_non_gdsc_ahb_clk.clkr,
	[DISP_CC_MDSS_PCLK0_CLK] = &disp_cc_mdss_pclk0_clk.clkr,
	[DISP_CC_MDSS_PCLK0_CLK_SRC] = &disp_cc_mdss_pclk0_clk_src.clkr,
	[DISP_CC_MDSS_ROT_CLK] = &disp_cc_mdss_rot_clk.clkr,
	[DISP_CC_MDSS_ROT_CLK_SRC] = &disp_cc_mdss_rot_clk_src.clkr,
	[DISP_CC_MDSS_RSCC_VSYNC_CLK] = &disp_cc_mdss_rscc_vsync_clk.clkr,
	[DISP_CC_MDSS_VSYNC_CLK] = &disp_cc_mdss_vsync_clk.clkr,
	[DISP_CC_MDSS_VSYNC_CLK_SRC] = &disp_cc_mdss_vsync_clk_src.clkr,
	[DISP_CC_PLL0] = &disp_cc_pll0.clkr,
	[DISP_CC_PLL0_OUT_EVEN] = &disp_cc_pll0_out_even.clkr,
पूर्ण;

अटल स्थिर काष्ठा regmap_config disp_cc_sc7180_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = 0x10000,
	.fast_io = true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc disp_cc_sc7180_desc = अणु
	.config = &disp_cc_sc7180_regmap_config,
	.clks = disp_cc_sc7180_घड़ीs,
	.num_clks = ARRAY_SIZE(disp_cc_sc7180_घड़ीs),
	.gdscs = disp_cc_sc7180_gdscs,
	.num_gdscs = ARRAY_SIZE(disp_cc_sc7180_gdscs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id disp_cc_sc7180_match_table[] = अणु
	अणु .compatible = "qcom,sc7180-dispcc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, disp_cc_sc7180_match_table);

अटल पूर्णांक disp_cc_sc7180_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;
	काष्ठा alpha_pll_config disp_cc_pll_config = अणुपूर्ण;

	regmap = qcom_cc_map(pdev, &disp_cc_sc7180_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/* 1380MHz configuration */
	disp_cc_pll_config.l = 0x47;
	disp_cc_pll_config.alpha = 0xe000;
	disp_cc_pll_config.user_ctl_val = 0x00000001;
	disp_cc_pll_config.user_ctl_hi_val = 0x00004805;

	clk_fabia_pll_configure(&disp_cc_pll0, regmap, &disp_cc_pll_config);

	वापस qcom_cc_really_probe(pdev, &disp_cc_sc7180_desc, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver disp_cc_sc7180_driver = अणु
	.probe = disp_cc_sc7180_probe,
	.driver = अणु
		.name = "sc7180-dispcc",
		.of_match_table = disp_cc_sc7180_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init disp_cc_sc7180_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&disp_cc_sc7180_driver);
पूर्ण
subsys_initcall(disp_cc_sc7180_init);

अटल व्योम __निकास disp_cc_sc7180_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&disp_cc_sc7180_driver);
पूर्ण
module_निकास(disp_cc_sc7180_निकास);

MODULE_DESCRIPTION("QTI DISP_CC SC7180 Driver");
MODULE_LICENSE("GPL v2");
