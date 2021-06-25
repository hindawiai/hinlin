<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018-2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset-controller.h>

#समावेश <dt-bindings/घड़ी/qcom,dispcc-sm8250.h>

#समावेश "clk-alpha-pll.h"
#समावेश "clk-branch.h"
#समावेश "clk-rcg.h"
#समावेश "clk-regmap-divider.h"
#समावेश "common.h"
#समावेश "gdsc.h"
#समावेश "reset.h"

क्रमागत अणु
	P_BI_TCXO,
	P_DISP_CC_PLL0_OUT_MAIN,
	P_DISP_CC_PLL1_OUT_EVEN,
	P_DISP_CC_PLL1_OUT_MAIN,
	P_DP_PHY_PLL_LINK_CLK,
	P_DP_PHY_PLL_VCO_DIV_CLK,
	P_DSI0_PHY_PLL_OUT_BYTECLK,
	P_DSI0_PHY_PLL_OUT_DSICLK,
	P_DSI1_PHY_PLL_OUT_BYTECLK,
	P_DSI1_PHY_PLL_OUT_DSICLK,
पूर्ण;

अटल काष्ठा pll_vco vco_table[] = अणु
	अणु 249600000, 2000000000, 0 पूर्ण,
पूर्ण;

अटल काष्ठा alpha_pll_config disp_cc_pll0_config = अणु
	.l = 0x47,
	.alpha = 0xE000,
	.config_ctl_val = 0x20485699,
	.config_ctl_hi_val = 0x00002261,
	.config_ctl_hi1_val = 0x329A699C,
	.user_ctl_val = 0x00000000,
	.user_ctl_hi_val = 0x00000805,
	.user_ctl_hi1_val = 0x00000000,
पूर्ण;

अटल काष्ठा clk_init_data disp_cc_pll0_init = अणु
	.name = "disp_cc_pll0",
	.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
		.fw_name = "bi_tcxo",
	पूर्ण,
	.num_parents = 1,
	.ops = &clk_alpha_pll_lucid_ops,
पूर्ण;

अटल काष्ठा clk_alpha_pll disp_cc_pll0 = अणु
	.offset = 0x0,
	.vco_table = vco_table,
	.num_vco = ARRAY_SIZE(vco_table),
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_LUCID],
	.clkr.hw.init = &disp_cc_pll0_init
पूर्ण;

अटल काष्ठा alpha_pll_config disp_cc_pll1_config = अणु
	.l = 0x1F,
	.alpha = 0x4000,
	.config_ctl_val = 0x20485699,
	.config_ctl_hi_val = 0x00002261,
	.config_ctl_hi1_val = 0x329A699C,
	.user_ctl_val = 0x00000000,
	.user_ctl_hi_val = 0x00000805,
	.user_ctl_hi1_val = 0x00000000,
पूर्ण;

अटल काष्ठा clk_init_data disp_cc_pll1_init = अणु
	.name = "disp_cc_pll1",
	.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
		.fw_name = "bi_tcxo",
	पूर्ण,
	.num_parents = 1,
	.ops = &clk_alpha_pll_lucid_ops,
पूर्ण;

अटल काष्ठा clk_alpha_pll disp_cc_pll1 = अणु
	.offset = 0x1000,
	.vco_table = vco_table,
	.num_vco = ARRAY_SIZE(vco_table),
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_LUCID],
	.clkr.hw.init = &disp_cc_pll1_init
पूर्ण;

अटल स्थिर काष्ठा parent_map disp_cc_parent_map_0[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_DP_PHY_PLL_LINK_CLK, 1 पूर्ण,
	अणु P_DP_PHY_PLL_VCO_DIV_CLK, 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data disp_cc_parent_data_0[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .fw_name = "dp_phy_pll_link_clk" पूर्ण,
	अणु .fw_name = "dp_phy_pll_vco_div_clk" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map disp_cc_parent_map_1[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data disp_cc_parent_data_1[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map disp_cc_parent_map_2[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_DSI0_PHY_PLL_OUT_BYTECLK, 1 पूर्ण,
	अणु P_DSI1_PHY_PLL_OUT_BYTECLK, 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data disp_cc_parent_data_2[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .fw_name = "dsi0_phy_pll_out_byteclk" पूर्ण,
	अणु .fw_name = "dsi1_phy_pll_out_byteclk" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map disp_cc_parent_map_3[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_DISP_CC_PLL1_OUT_MAIN, 4 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data disp_cc_parent_data_3[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &disp_cc_pll1.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map disp_cc_parent_map_5[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_DISP_CC_PLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_DISP_CC_PLL1_OUT_MAIN, 4 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data disp_cc_parent_data_5[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &disp_cc_pll0.clkr.hw पूर्ण,
	अणु .hw = &disp_cc_pll1.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map disp_cc_parent_map_6[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_DSI0_PHY_PLL_OUT_DSICLK, 1 पूर्ण,
	अणु P_DSI1_PHY_PLL_OUT_DSICLK, 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data disp_cc_parent_data_6[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .fw_name = "dsi0_phy_pll_out_dsiclk" पूर्ण,
	अणु .fw_name = "dsi1_phy_pll_out_dsiclk" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_disp_cc_mdss_ahb_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(37500000, P_DISP_CC_PLL1_OUT_MAIN, 16, 0, 0),
	F(75000000, P_DISP_CC_PLL1_OUT_MAIN, 8, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_ahb_clk_src = अणु
	.cmd_rcgr = 0x22bc,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_3,
	.freq_tbl = ftbl_disp_cc_mdss_ahb_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_ahb_clk_src",
		.parent_data = disp_cc_parent_data_3,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_3),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_disp_cc_mdss_byte0_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	अणु पूर्ण
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

अटल काष्ठा clk_rcg2 disp_cc_mdss_byte1_clk_src = अणु
	.cmd_rcgr = 0x212c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_2,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_byte1_clk_src",
		.parent_data = disp_cc_parent_data_2,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_2),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_byte2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_dp_aux1_clk_src = अणु
	.cmd_rcgr = 0x2240,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_1,
	.freq_tbl = ftbl_disp_cc_mdss_byte0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_dp_aux1_clk_src",
		.parent_data = disp_cc_parent_data_1,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_1),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_dp_aux_clk_src = अणु
	.cmd_rcgr = 0x21dc,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_1,
	.freq_tbl = ftbl_disp_cc_mdss_byte0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_dp_aux_clk_src",
		.parent_data = disp_cc_parent_data_1,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_1),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_disp_cc_mdss_dp_link1_clk_src[] = अणु
	F(162000000, P_DP_PHY_PLL_LINK_CLK, 1, 0, 0),
	F(270000000, P_DP_PHY_PLL_LINK_CLK, 1, 0, 0),
	F(540000000, P_DP_PHY_PLL_LINK_CLK, 1, 0, 0),
	F(810000000, P_DP_PHY_PLL_LINK_CLK, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_dp_link1_clk_src = अणु
	.cmd_rcgr = 0x220c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_0,
	.freq_tbl = ftbl_disp_cc_mdss_dp_link1_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_dp_link1_clk_src",
		.parent_data = disp_cc_parent_data_0,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_0),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_dp_link_clk_src = अणु
	.cmd_rcgr = 0x2178,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_0,
	.freq_tbl = ftbl_disp_cc_mdss_dp_link1_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_dp_link_clk_src",
		.parent_data = disp_cc_parent_data_0,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_0),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_dp_pixel1_clk_src = अणु
	.cmd_rcgr = 0x21c4,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_0,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_dp_pixel1_clk_src",
		.parent_data = disp_cc_parent_data_0,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_0),
		.ops = &clk_dp_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_dp_pixel2_clk_src = अणु
	.cmd_rcgr = 0x21f4,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_0,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_dp_pixel2_clk_src",
		.parent_data = disp_cc_parent_data_0,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_0),
		.ops = &clk_dp_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_dp_pixel_clk_src = अणु
	.cmd_rcgr = 0x21ac,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_0,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_dp_pixel_clk_src",
		.parent_data = disp_cc_parent_data_0,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_0),
		.ops = &clk_dp_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_esc0_clk_src = अणु
	.cmd_rcgr = 0x2148,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_2,
	.freq_tbl = ftbl_disp_cc_mdss_byte0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_esc0_clk_src",
		.parent_data = disp_cc_parent_data_2,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_2),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_esc1_clk_src = अणु
	.cmd_rcgr = 0x2160,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_2,
	.freq_tbl = ftbl_disp_cc_mdss_byte0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_esc1_clk_src",
		.parent_data = disp_cc_parent_data_2,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_2),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_disp_cc_mdss_mdp_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(85714286, P_DISP_CC_PLL1_OUT_MAIN, 7, 0, 0),
	F(100000000, P_DISP_CC_PLL1_OUT_MAIN, 6, 0, 0),
	F(150000000, P_DISP_CC_PLL1_OUT_MAIN, 4, 0, 0),
	F(200000000, P_DISP_CC_PLL1_OUT_MAIN, 3, 0, 0),
	F(300000000, P_DISP_CC_PLL1_OUT_MAIN, 2, 0, 0),
	F(345000000, P_DISP_CC_PLL0_OUT_MAIN, 4, 0, 0),
	F(460000000, P_DISP_CC_PLL0_OUT_MAIN, 3, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_mdp_clk_src = अणु
	.cmd_rcgr = 0x20c8,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_5,
	.freq_tbl = ftbl_disp_cc_mdss_mdp_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_mdp_clk_src",
		.parent_data = disp_cc_parent_data_5,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_5),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_pclk0_clk_src = अणु
	.cmd_rcgr = 0x2098,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_6,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_pclk0_clk_src",
		.parent_data = disp_cc_parent_data_6,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_6),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_pixel_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_pclk1_clk_src = अणु
	.cmd_rcgr = 0x20b0,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_6,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_pclk1_clk_src",
		.parent_data = disp_cc_parent_data_6,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_6),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_pixel_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_disp_cc_mdss_rot_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(200000000, P_DISP_CC_PLL1_OUT_MAIN, 3, 0, 0),
	F(300000000, P_DISP_CC_PLL1_OUT_MAIN, 2, 0, 0),
	F(345000000, P_DISP_CC_PLL0_OUT_MAIN, 4, 0, 0),
	F(460000000, P_DISP_CC_PLL0_OUT_MAIN, 3, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_rot_clk_src = अणु
	.cmd_rcgr = 0x20e0,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_5,
	.freq_tbl = ftbl_disp_cc_mdss_rot_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_rot_clk_src",
		.parent_data = disp_cc_parent_data_5,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_5),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 disp_cc_mdss_vsync_clk_src = अणु
	.cmd_rcgr = 0x20f8,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = disp_cc_parent_map_1,
	.freq_tbl = ftbl_disp_cc_mdss_byte0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "disp_cc_mdss_vsync_clk_src",
		.parent_data = disp_cc_parent_data_1,
		.num_parents = ARRAY_SIZE(disp_cc_parent_data_1),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_भाग disp_cc_mdss_byte0_भाग_clk_src = अणु
	.reg = 0x2128,
	.shअगरt = 0,
	.width = 2,
	.clkr.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "disp_cc_mdss_byte0_div_clk_src",
		.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
			&disp_cc_mdss_byte0_clk_src.clkr.hw,
		पूर्ण,
		.num_parents = 1,
		.ops = &clk_regmap_भाग_ops,
	पूर्ण,
पूर्ण;


अटल काष्ठा clk_regmap_भाग disp_cc_mdss_byte1_भाग_clk_src = अणु
	.reg = 0x2144,
	.shअगरt = 0,
	.width = 2,
	.clkr.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "disp_cc_mdss_byte1_div_clk_src",
		.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
			&disp_cc_mdss_byte1_clk_src.clkr.hw,
		पूर्ण,
		.num_parents = 1,
		.ops = &clk_regmap_भाग_ops,
	पूर्ण,
पूर्ण;


अटल काष्ठा clk_regmap_भाग disp_cc_mdss_dp_link1_भाग_clk_src = अणु
	.reg = 0x2224,
	.shअगरt = 0,
	.width = 2,
	.clkr.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "disp_cc_mdss_dp_link1_div_clk_src",
		.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
			&disp_cc_mdss_dp_link1_clk_src.clkr.hw,
		पूर्ण,
		.num_parents = 1,
		.ops = &clk_regmap_भाग_ro_ops,
	पूर्ण,
पूर्ण;


अटल काष्ठा clk_regmap_भाग disp_cc_mdss_dp_link_भाग_clk_src = अणु
	.reg = 0x2190,
	.shअगरt = 0,
	.width = 2,
	.clkr.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "disp_cc_mdss_dp_link_div_clk_src",
		.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
			&disp_cc_mdss_dp_link_clk_src.clkr.hw,
		पूर्ण,
		.num_parents = 1,
		.ops = &clk_regmap_भाग_ro_ops,
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

अटल काष्ठा clk_branch disp_cc_mdss_byte1_clk = अणु
	.halt_reg = 0x2030,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2030,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_byte1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_byte1_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch disp_cc_mdss_byte1_पूर्णांकf_clk = अणु
	.halt_reg = 0x2034,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2034,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_byte1_intf_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_byte1_भाग_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch disp_cc_mdss_dp_aux1_clk = अणु
	.halt_reg = 0x2068,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2068,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_dp_aux1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_dp_aux1_clk_src.clkr.hw,
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

अटल काष्ठा clk_branch disp_cc_mdss_dp_link1_clk = अणु
	.halt_reg = 0x205c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x205c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_dp_link1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_dp_link1_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch disp_cc_mdss_dp_link1_पूर्णांकf_clk = अणु
	.halt_reg = 0x2060,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2060,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_dp_link1_intf_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_dp_link1_भाग_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
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

अटल काष्ठा clk_branch disp_cc_mdss_dp_pixel1_clk = अणु
	.halt_reg = 0x2050,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2050,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_dp_pixel1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_dp_pixel1_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch disp_cc_mdss_dp_pixel2_clk = अणु
	.halt_reg = 0x2058,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2058,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_dp_pixel2_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_dp_pixel2_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
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

अटल काष्ठा clk_branch disp_cc_mdss_esc1_clk = अणु
	.halt_reg = 0x203c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x203c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_esc1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_esc1_clk_src.clkr.hw,
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

अटल काष्ठा clk_branch disp_cc_mdss_pclk1_clk = अणु
	.halt_reg = 0x2008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_pclk1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_pclk1_clk_src.clkr.hw,
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

अटल काष्ठा clk_branch disp_cc_mdss_rscc_ahb_clk = अणु
	.halt_reg = 0x400c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x400c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "disp_cc_mdss_rscc_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&disp_cc_mdss_ahb_clk_src.clkr.hw,
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
	.supply = "mmcx",
पूर्ण;

अटल काष्ठा clk_regmap *disp_cc_sm8250_घड़ीs[] = अणु
	[DISP_CC_MDSS_AHB_CLK] = &disp_cc_mdss_ahb_clk.clkr,
	[DISP_CC_MDSS_AHB_CLK_SRC] = &disp_cc_mdss_ahb_clk_src.clkr,
	[DISP_CC_MDSS_BYTE0_CLK] = &disp_cc_mdss_byte0_clk.clkr,
	[DISP_CC_MDSS_BYTE0_CLK_SRC] = &disp_cc_mdss_byte0_clk_src.clkr,
	[DISP_CC_MDSS_BYTE0_DIV_CLK_SRC] = &disp_cc_mdss_byte0_भाग_clk_src.clkr,
	[DISP_CC_MDSS_BYTE0_INTF_CLK] = &disp_cc_mdss_byte0_पूर्णांकf_clk.clkr,
	[DISP_CC_MDSS_BYTE1_CLK] = &disp_cc_mdss_byte1_clk.clkr,
	[DISP_CC_MDSS_BYTE1_CLK_SRC] = &disp_cc_mdss_byte1_clk_src.clkr,
	[DISP_CC_MDSS_BYTE1_DIV_CLK_SRC] = &disp_cc_mdss_byte1_भाग_clk_src.clkr,
	[DISP_CC_MDSS_BYTE1_INTF_CLK] = &disp_cc_mdss_byte1_पूर्णांकf_clk.clkr,
	[DISP_CC_MDSS_DP_AUX1_CLK] = &disp_cc_mdss_dp_aux1_clk.clkr,
	[DISP_CC_MDSS_DP_AUX1_CLK_SRC] = &disp_cc_mdss_dp_aux1_clk_src.clkr,
	[DISP_CC_MDSS_DP_AUX_CLK] = &disp_cc_mdss_dp_aux_clk.clkr,
	[DISP_CC_MDSS_DP_AUX_CLK_SRC] = &disp_cc_mdss_dp_aux_clk_src.clkr,
	[DISP_CC_MDSS_DP_LINK1_CLK] = &disp_cc_mdss_dp_link1_clk.clkr,
	[DISP_CC_MDSS_DP_LINK1_CLK_SRC] = &disp_cc_mdss_dp_link1_clk_src.clkr,
	[DISP_CC_MDSS_DP_LINK1_DIV_CLK_SRC] = &disp_cc_mdss_dp_link1_भाग_clk_src.clkr,
	[DISP_CC_MDSS_DP_LINK1_INTF_CLK] = &disp_cc_mdss_dp_link1_पूर्णांकf_clk.clkr,
	[DISP_CC_MDSS_DP_LINK_CLK] = &disp_cc_mdss_dp_link_clk.clkr,
	[DISP_CC_MDSS_DP_LINK_CLK_SRC] = &disp_cc_mdss_dp_link_clk_src.clkr,
	[DISP_CC_MDSS_DP_LINK_DIV_CLK_SRC] = &disp_cc_mdss_dp_link_भाग_clk_src.clkr,
	[DISP_CC_MDSS_DP_LINK_INTF_CLK] = &disp_cc_mdss_dp_link_पूर्णांकf_clk.clkr,
	[DISP_CC_MDSS_DP_PIXEL1_CLK] = &disp_cc_mdss_dp_pixel1_clk.clkr,
	[DISP_CC_MDSS_DP_PIXEL1_CLK_SRC] = &disp_cc_mdss_dp_pixel1_clk_src.clkr,
	[DISP_CC_MDSS_DP_PIXEL2_CLK] = &disp_cc_mdss_dp_pixel2_clk.clkr,
	[DISP_CC_MDSS_DP_PIXEL2_CLK_SRC] = &disp_cc_mdss_dp_pixel2_clk_src.clkr,
	[DISP_CC_MDSS_DP_PIXEL_CLK] = &disp_cc_mdss_dp_pixel_clk.clkr,
	[DISP_CC_MDSS_DP_PIXEL_CLK_SRC] = &disp_cc_mdss_dp_pixel_clk_src.clkr,
	[DISP_CC_MDSS_ESC0_CLK] = &disp_cc_mdss_esc0_clk.clkr,
	[DISP_CC_MDSS_ESC0_CLK_SRC] = &disp_cc_mdss_esc0_clk_src.clkr,
	[DISP_CC_MDSS_ESC1_CLK] = &disp_cc_mdss_esc1_clk.clkr,
	[DISP_CC_MDSS_ESC1_CLK_SRC] = &disp_cc_mdss_esc1_clk_src.clkr,
	[DISP_CC_MDSS_MDP_CLK] = &disp_cc_mdss_mdp_clk.clkr,
	[DISP_CC_MDSS_MDP_CLK_SRC] = &disp_cc_mdss_mdp_clk_src.clkr,
	[DISP_CC_MDSS_MDP_LUT_CLK] = &disp_cc_mdss_mdp_lut_clk.clkr,
	[DISP_CC_MDSS_NON_GDSC_AHB_CLK] = &disp_cc_mdss_non_gdsc_ahb_clk.clkr,
	[DISP_CC_MDSS_PCLK0_CLK] = &disp_cc_mdss_pclk0_clk.clkr,
	[DISP_CC_MDSS_PCLK0_CLK_SRC] = &disp_cc_mdss_pclk0_clk_src.clkr,
	[DISP_CC_MDSS_PCLK1_CLK] = &disp_cc_mdss_pclk1_clk.clkr,
	[DISP_CC_MDSS_PCLK1_CLK_SRC] = &disp_cc_mdss_pclk1_clk_src.clkr,
	[DISP_CC_MDSS_ROT_CLK] = &disp_cc_mdss_rot_clk.clkr,
	[DISP_CC_MDSS_ROT_CLK_SRC] = &disp_cc_mdss_rot_clk_src.clkr,
	[DISP_CC_MDSS_RSCC_AHB_CLK] = &disp_cc_mdss_rscc_ahb_clk.clkr,
	[DISP_CC_MDSS_RSCC_VSYNC_CLK] = &disp_cc_mdss_rscc_vsync_clk.clkr,
	[DISP_CC_MDSS_VSYNC_CLK] = &disp_cc_mdss_vsync_clk.clkr,
	[DISP_CC_MDSS_VSYNC_CLK_SRC] = &disp_cc_mdss_vsync_clk_src.clkr,
	[DISP_CC_PLL0] = &disp_cc_pll0.clkr,
	[DISP_CC_PLL1] = &disp_cc_pll1.clkr,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map disp_cc_sm8250_resets[] = अणु
	[DISP_CC_MDSS_CORE_BCR] = अणु 0x2000 पूर्ण,
	[DISP_CC_MDSS_RSCC_BCR] = अणु 0x4000 पूर्ण,
पूर्ण;

अटल काष्ठा gdsc *disp_cc_sm8250_gdscs[] = अणु
	[MDSS_GDSC] = &mdss_gdsc,
पूर्ण;

अटल स्थिर काष्ठा regmap_config disp_cc_sm8250_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x10000,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc disp_cc_sm8250_desc = अणु
	.config = &disp_cc_sm8250_regmap_config,
	.clks = disp_cc_sm8250_घड़ीs,
	.num_clks = ARRAY_SIZE(disp_cc_sm8250_घड़ीs),
	.resets = disp_cc_sm8250_resets,
	.num_resets = ARRAY_SIZE(disp_cc_sm8250_resets),
	.gdscs = disp_cc_sm8250_gdscs,
	.num_gdscs = ARRAY_SIZE(disp_cc_sm8250_gdscs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id disp_cc_sm8250_match_table[] = अणु
	अणु .compatible = "qcom,sm8150-dispcc" पूर्ण,
	अणु .compatible = "qcom,sm8250-dispcc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, disp_cc_sm8250_match_table);

अटल पूर्णांक disp_cc_sm8250_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;

	regmap = qcom_cc_map(pdev, &disp_cc_sm8250_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/* note: trion == lucid, except क्रम the prepare() op */
	BUILD_BUG_ON(CLK_ALPHA_PLL_TYPE_TRION != CLK_ALPHA_PLL_TYPE_LUCID);
	अगर (of_device_is_compatible(pdev->dev.of_node, "qcom,sm8150-dispcc")) अणु
		disp_cc_pll0_config.config_ctl_hi_val = 0x00002267;
		disp_cc_pll0_config.config_ctl_hi1_val = 0x00000024;
		disp_cc_pll0_config.user_ctl_hi1_val = 0x000000D0;
		disp_cc_pll0_init.ops = &clk_alpha_pll_trion_ops;
		disp_cc_pll1_config.config_ctl_hi_val = 0x00002267;
		disp_cc_pll1_config.config_ctl_hi1_val = 0x00000024;
		disp_cc_pll1_config.user_ctl_hi1_val = 0x000000D0;
		disp_cc_pll1_init.ops = &clk_alpha_pll_trion_ops;
	पूर्ण

	clk_lucid_pll_configure(&disp_cc_pll0, regmap, &disp_cc_pll0_config);
	clk_lucid_pll_configure(&disp_cc_pll1, regmap, &disp_cc_pll1_config);

	/* Enable घड़ी gating क्रम MDP घड़ीs */
	regmap_update_bits(regmap, 0x8000, 0x10, 0x10);

	/* DISP_CC_XO_CLK always-on */
	regmap_update_bits(regmap, 0x605c, BIT(0), BIT(0));

	वापस qcom_cc_really_probe(pdev, &disp_cc_sm8250_desc, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver disp_cc_sm8250_driver = अणु
	.probe = disp_cc_sm8250_probe,
	.driver = अणु
		.name = "disp_cc-sm8250",
		.of_match_table = disp_cc_sm8250_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init disp_cc_sm8250_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&disp_cc_sm8250_driver);
पूर्ण
subsys_initcall(disp_cc_sm8250_init);

अटल व्योम __निकास disp_cc_sm8250_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&disp_cc_sm8250_driver);
पूर्ण
module_निकास(disp_cc_sm8250_निकास);

MODULE_DESCRIPTION("QTI DISPCC SM8250 Driver");
MODULE_LICENSE("GPL v2");
