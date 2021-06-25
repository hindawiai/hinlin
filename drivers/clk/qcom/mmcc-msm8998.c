<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset-controller.h>

#समावेश <dt-bindings/घड़ी/qcom,mmcc-msm8998.h>

#समावेश "common.h"
#समावेश "clk-regmap.h"
#समावेश "clk-regmap-divider.h"
#समावेश "clk-alpha-pll.h"
#समावेश "clk-rcg.h"
#समावेश "clk-branch.h"
#समावेश "reset.h"
#समावेश "gdsc.h"

क्रमागत अणु
	P_XO,
	P_GPLL0,
	P_GPLL0_DIV,
	P_MMPLL0_OUT_EVEN,
	P_MMPLL1_OUT_EVEN,
	P_MMPLL3_OUT_EVEN,
	P_MMPLL4_OUT_EVEN,
	P_MMPLL5_OUT_EVEN,
	P_MMPLL6_OUT_EVEN,
	P_MMPLL7_OUT_EVEN,
	P_MMPLL10_OUT_EVEN,
	P_DSI0PLL,
	P_DSI1PLL,
	P_DSI0PLL_BYTE,
	P_DSI1PLL_BYTE,
	P_HDMIPLL,
	P_DPVCO,
	P_DPLINK,
	P_CORE_BI_PLL_TEST_SE,
पूर्ण;

अटल काष्ठा clk_fixed_factor gpll0_भाग = अणु
	.mult = 1,
	.भाग = 2,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmss_gpll0_div",
		.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
			.fw_name = "gpll0",
			.name = "gpll0"
		पूर्ण,
		.num_parents = 1,
		.ops = &clk_fixed_factor_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable post_भाग_प्रकारable_fabia_even[] = अणु
	अणु 0x0, 1 पूर्ण,
	अणु 0x1, 2 पूर्ण,
	अणु 0x3, 4 पूर्ण,
	अणु 0x7, 8 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll0 = अणु
	.offset = 0xc000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr = अणु
		.enable_reg = 0x1e0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmpll0",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "xo",
				.name = "xo"
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_fabia_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग mmpll0_out_even = अणु
	.offset = 0xc000,
	.post_भाग_shअगरt = 8,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_fabia_even,
	.num_post_भाग = ARRAY_SIZE(post_भाग_प्रकारable_fabia_even),
	.width = 4,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll0_out_even",
		.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mmpll0.clkr.hw पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll1 = अणु
	.offset = 0xc050,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr = अणु
		.enable_reg = 0x1e0,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmpll1",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "xo",
				.name = "xo"
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_fabia_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग mmpll1_out_even = अणु
	.offset = 0xc050,
	.post_भाग_shअगरt = 8,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_fabia_even,
	.num_post_भाग = ARRAY_SIZE(post_भाग_प्रकारable_fabia_even),
	.width = 4,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll1_out_even",
		.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mmpll1.clkr.hw पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll3 = अणु
	.offset = 0x0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll3",
		.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
			.fw_name = "xo",
			.name = "xo"
		पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_fixed_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग mmpll3_out_even = अणु
	.offset = 0x0,
	.post_भाग_shअगरt = 8,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_fabia_even,
	.num_post_भाग = ARRAY_SIZE(post_भाग_प्रकारable_fabia_even),
	.width = 4,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll3_out_even",
		.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mmpll3.clkr.hw पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll4 = अणु
	.offset = 0x50,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll4",
		.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
			.fw_name = "xo",
			.name = "xo"
		पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_fixed_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग mmpll4_out_even = अणु
	.offset = 0x50,
	.post_भाग_shअगरt = 8,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_fabia_even,
	.num_post_भाग = ARRAY_SIZE(post_भाग_प्रकारable_fabia_even),
	.width = 4,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll4_out_even",
		.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mmpll4.clkr.hw पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll5 = अणु
	.offset = 0xa0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll5",
		.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
			.fw_name = "xo",
			.name = "xo"
		पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_fixed_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग mmpll5_out_even = अणु
	.offset = 0xa0,
	.post_भाग_shअगरt = 8,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_fabia_even,
	.num_post_भाग = ARRAY_SIZE(post_भाग_प्रकारable_fabia_even),
	.width = 4,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll5_out_even",
		.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mmpll5.clkr.hw पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll6 = अणु
	.offset = 0xf0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll6",
		.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
			.fw_name = "xo",
			.name = "xo"
		पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_fixed_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग mmpll6_out_even = अणु
	.offset = 0xf0,
	.post_भाग_shअगरt = 8,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_fabia_even,
	.num_post_भाग = ARRAY_SIZE(post_भाग_प्रकारable_fabia_even),
	.width = 4,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll6_out_even",
		.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mmpll6.clkr.hw पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll7 = अणु
	.offset = 0x140,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll7",
		.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
			.fw_name = "xo",
			.name = "xo"
		पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_fixed_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग mmpll7_out_even = अणु
	.offset = 0x140,
	.post_भाग_shअगरt = 8,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_fabia_even,
	.num_post_भाग = ARRAY_SIZE(post_भाग_प्रकारable_fabia_even),
	.width = 4,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll7_out_even",
		.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mmpll7.clkr.hw पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll10 = अणु
	.offset = 0x190,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll10",
		.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
			.fw_name = "xo",
			.name = "xo"
		पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_fixed_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग mmpll10_out_even = अणु
	.offset = 0x190,
	.post_भाग_shअगरt = 8,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_fabia_even,
	.num_post_भाग = ARRAY_SIZE(post_भाग_प्रकारable_fabia_even),
	.width = 4,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll10_out_even",
		.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mmpll10.clkr.hw पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_hdmi_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_HDMIPLL, 1 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmss_xo_hdmi[] = अणु
	अणु .fw_name = "xo", .name = "xo" पूर्ण,
	अणु .fw_name = "hdmipll", .name = "hdmipll" पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_dsi0pll_dsi1pll_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_DSI0PLL, 1 पूर्ण,
	अणु P_DSI1PLL, 2 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmss_xo_dsi0pll_dsi1pll[] = अणु
	अणु .fw_name = "xo", .name = "xo" पूर्ण,
	अणु .fw_name = "dsi0dsi", .name = "dsi0dsi" पूर्ण,
	अणु .fw_name = "dsi1dsi", .name = "dsi1dsi" पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_dsibyte_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_DSI0PLL_BYTE, 1 पूर्ण,
	अणु P_DSI1PLL_BYTE, 2 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmss_xo_dsibyte[] = अणु
	अणु .fw_name = "xo", .name = "xo" पूर्ण,
	अणु .fw_name = "dsi0byte", .name = "dsi0byte" पूर्ण,
	अणु .fw_name = "dsi1byte", .name = "dsi1byte" पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_dp_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_DPLINK, 1 पूर्ण,
	अणु P_DPVCO, 2 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmss_xo_dp[] = अणु
	अणु .fw_name = "xo", .name = "xo" पूर्ण,
	अणु .fw_name = "dplink", .name = "dplink" पूर्ण,
	अणु .fw_name = "dpvco", .name = "dpvco" पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmss_xo_gpll0_gpll0_भाग[] = अणु
	अणु .fw_name = "xo", .name = "xo" पूर्ण,
	अणु .fw_name = "gpll0", .name = "gpll0" पूर्ण,
	अणु .hw = &gpll0_भाग.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_mmpll0_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0_OUT_EVEN, 1 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmss_xo_mmpll0_gpll0_gpll0_भाग[] = अणु
	अणु .fw_name = "xo", .name = "xo" पूर्ण,
	अणु .hw = &mmpll0_out_even.clkr.hw पूर्ण,
	अणु .fw_name = "gpll0", .name = "gpll0" पूर्ण,
	अणु .hw = &gpll0_भाग.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_mmpll0_mmpll1_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0_OUT_EVEN, 1 पूर्ण,
	अणु P_MMPLL1_OUT_EVEN, 2 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmss_xo_mmpll0_mmpll1_gpll0_gpll0_भाग[] = अणु
	अणु .fw_name = "xo", .name = "xo" पूर्ण,
	अणु .hw = &mmpll0_out_even.clkr.hw पूर्ण,
	अणु .hw = &mmpll1_out_even.clkr.hw पूर्ण,
	अणु .fw_name = "gpll0", .name = "gpll0" पूर्ण,
	अणु .hw = &gpll0_भाग.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_mmpll0_mmpll5_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0_OUT_EVEN, 1 पूर्ण,
	अणु P_MMPLL5_OUT_EVEN, 2 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmss_xo_mmpll0_mmpll5_gpll0_gpll0_भाग[] = अणु
	अणु .fw_name = "xo", .name = "xo" पूर्ण,
	अणु .hw = &mmpll0_out_even.clkr.hw पूर्ण,
	अणु .hw = &mmpll5_out_even.clkr.hw पूर्ण,
	अणु .fw_name = "gpll0", .name = "gpll0" पूर्ण,
	अणु .hw = &gpll0_भाग.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_mmpll0_mmpll3_mmpll6_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0_OUT_EVEN, 1 पूर्ण,
	अणु P_MMPLL3_OUT_EVEN, 3 पूर्ण,
	अणु P_MMPLL6_OUT_EVEN, 4 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmss_xo_mmpll0_mmpll3_mmpll6_gpll0_gpll0_भाग[] = अणु
	अणु .fw_name = "xo", .name = "xo" पूर्ण,
	अणु .hw = &mmpll0_out_even.clkr.hw पूर्ण,
	अणु .hw = &mmpll3_out_even.clkr.hw पूर्ण,
	अणु .hw = &mmpll6_out_even.clkr.hw पूर्ण,
	अणु .fw_name = "gpll0", .name = "gpll0" पूर्ण,
	अणु .hw = &gpll0_भाग.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL4_OUT_EVEN, 1 पूर्ण,
	अणु P_MMPLL7_OUT_EVEN, 2 पूर्ण,
	अणु P_MMPLL10_OUT_EVEN, 3 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmss_xo_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग[] = अणु
	अणु .fw_name = "xo", .name = "xo" पूर्ण,
	अणु .hw = &mmpll4_out_even.clkr.hw पूर्ण,
	अणु .hw = &mmpll7_out_even.clkr.hw पूर्ण,
	अणु .hw = &mmpll10_out_even.clkr.hw पूर्ण,
	अणु .fw_name = "gpll0", .name = "gpll0" पूर्ण,
	अणु .hw = &gpll0_भाग.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_mmpll0_mmpll7_mmpll10_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0_OUT_EVEN, 1 पूर्ण,
	अणु P_MMPLL7_OUT_EVEN, 2 पूर्ण,
	अणु P_MMPLL10_OUT_EVEN, 3 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmss_xo_mmpll0_mmpll7_mmpll10_gpll0_gpll0_भाग[] = अणु
	अणु .fw_name = "xo", .name = "xo" पूर्ण,
	अणु .hw = &mmpll0_out_even.clkr.hw पूर्ण,
	अणु .hw = &mmpll7_out_even.clkr.hw पूर्ण,
	अणु .hw = &mmpll10_out_even.clkr.hw पूर्ण,
	अणु .fw_name = "gpll0", .name = "gpll0" पूर्ण,
	अणु .hw = &gpll0_भाग.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0_OUT_EVEN, 1 पूर्ण,
	अणु P_MMPLL4_OUT_EVEN, 2 पूर्ण,
	अणु P_MMPLL7_OUT_EVEN, 3 पूर्ण,
	अणु P_MMPLL10_OUT_EVEN, 4 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग[] = अणु
	अणु .fw_name = "xo", .name = "xo" पूर्ण,
	अणु .hw = &mmpll0_out_even.clkr.hw पूर्ण,
	अणु .hw = &mmpll4_out_even.clkr.hw पूर्ण,
	अणु .hw = &mmpll7_out_even.clkr.hw पूर्ण,
	अणु .hw = &mmpll10_out_even.clkr.hw पूर्ण,
	अणु .fw_name = "gpll0", .name = "gpll0" पूर्ण,
	अणु .hw = &gpll0_भाग.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 byte0_clk_src = अणु
	.cmd_rcgr = 0x2120,
	.hid_width = 5,
	.parent_map = mmss_xo_dsibyte_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "byte0_clk_src",
		.parent_data = mmss_xo_dsibyte,
		.num_parents = 4,
		.ops = &clk_byte2_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 byte1_clk_src = अणु
	.cmd_rcgr = 0x2140,
	.hid_width = 5,
	.parent_map = mmss_xo_dsibyte_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "byte1_clk_src",
		.parent_data = mmss_xo_dsibyte,
		.num_parents = 4,
		.ops = &clk_byte2_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cci_clk_src[] = अणु
	F(37500000, P_GPLL0, 16, 0, 0),
	F(50000000, P_GPLL0, 12, 0, 0),
	F(100000000, P_GPLL0, 6, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cci_clk_src = अणु
	.cmd_rcgr = 0x3300,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_cci_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cci_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cpp_clk_src[] = अणु
	F(100000000, P_GPLL0, 6, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	F(384000000, P_MMPLL4_OUT_EVEN, 2, 0, 0),
	F(404000000, P_MMPLL0_OUT_EVEN, 2, 0, 0),
	F(480000000, P_MMPLL7_OUT_EVEN, 2, 0, 0),
	F(576000000, P_MMPLL10_OUT_EVEN, 1, 0, 0),
	F(600000000, P_GPLL0, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cpp_clk_src = अणु
	.cmd_rcgr = 0x3640,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_cpp_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpp_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 8,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_csi_clk_src[] = अणु
	F(164571429, P_MMPLL10_OUT_EVEN, 3.5, 0, 0),
	F(256000000, P_MMPLL4_OUT_EVEN, 3, 0, 0),
	F(274290000, P_MMPLL7_OUT_EVEN, 3.5, 0, 0),
	F(300000000, P_GPLL0, 2, 0, 0),
	F(384000000, P_MMPLL4_OUT_EVEN, 2, 0, 0),
	F(576000000, P_MMPLL10_OUT_EVEN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 csi0_clk_src = अणु
	.cmd_rcgr = 0x3090,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi0_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 8,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 csi1_clk_src = अणु
	.cmd_rcgr = 0x3100,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi1_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 8,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 csi2_clk_src = अणु
	.cmd_rcgr = 0x3160,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi2_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 8,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 csi3_clk_src = अणु
	.cmd_rcgr = 0x31c0,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi3_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 8,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_csiphy_clk_src[] = अणु
	F(164571429, P_MMPLL10_OUT_EVEN, 3.5, 0, 0),
	F(256000000, P_MMPLL4_OUT_EVEN, 3, 0, 0),
	F(274290000, P_MMPLL7_OUT_EVEN, 3.5, 0, 0),
	F(300000000, P_GPLL0, 2, 0, 0),
	F(384000000, P_MMPLL4_OUT_EVEN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 csiphy_clk_src = अणु
	.cmd_rcgr = 0x3800,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csiphy_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csiphy_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 8,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_csiphyसमयr_clk_src[] = अणु
	F(200000000, P_GPLL0, 3, 0, 0),
	F(269333333, P_MMPLL0_OUT_EVEN, 3, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 csi0phyसमयr_clk_src = अणु
	.cmd_rcgr = 0x3000,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csiphyसमयr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi0phytimer_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 8,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 csi1phyसमयr_clk_src = अणु
	.cmd_rcgr = 0x3030,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csiphyसमयr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi1phytimer_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 8,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 csi2phyसमयr_clk_src = अणु
	.cmd_rcgr = 0x3060,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csiphyसमयr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi2phytimer_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 8,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_dp_aux_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 dp_aux_clk_src = अणु
	.cmd_rcgr = 0x2260,
	.hid_width = 5,
	.parent_map = mmss_xo_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_dp_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "dp_aux_clk_src",
		.parent_data = mmss_xo_gpll0_gpll0_भाग,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_dp_crypto_clk_src[] = अणु
	F(101250, P_DPLINK, 1, 5, 16),
	F(168750, P_DPLINK, 1, 5, 16),
	F(337500, P_DPLINK, 1, 5, 16),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 dp_crypto_clk_src = अणु
	.cmd_rcgr = 0x2220,
	.hid_width = 5,
	.parent_map = mmss_xo_dp_map,
	.freq_tbl = ftbl_dp_crypto_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "dp_crypto_clk_src",
		.parent_data = mmss_xo_dp,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_dp_link_clk_src[] = अणु
	F(162000, P_DPLINK, 2, 0, 0),
	F(270000, P_DPLINK, 2, 0, 0),
	F(540000, P_DPLINK, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 dp_link_clk_src = अणु
	.cmd_rcgr = 0x2200,
	.hid_width = 5,
	.parent_map = mmss_xo_dp_map,
	.freq_tbl = ftbl_dp_link_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "dp_link_clk_src",
		.parent_data = mmss_xo_dp,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_dp_pixel_clk_src[] = अणु
	F(154000000, P_DPVCO, 1, 0, 0),
	F(337500000, P_DPVCO, 2, 0, 0),
	F(675000000, P_DPVCO, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 dp_pixel_clk_src = अणु
	.cmd_rcgr = 0x2240,
	.hid_width = 5,
	.parent_map = mmss_xo_dp_map,
	.freq_tbl = ftbl_dp_pixel_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "dp_pixel_clk_src",
		.parent_data = mmss_xo_dp,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_esc_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 esc0_clk_src = अणु
	.cmd_rcgr = 0x2160,
	.hid_width = 5,
	.parent_map = mmss_xo_dsibyte_map,
	.freq_tbl = ftbl_esc_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "esc0_clk_src",
		.parent_data = mmss_xo_dsibyte,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 esc1_clk_src = अणु
	.cmd_rcgr = 0x2180,
	.hid_width = 5,
	.parent_map = mmss_xo_dsibyte_map,
	.freq_tbl = ftbl_esc_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "esc1_clk_src",
		.parent_data = mmss_xo_dsibyte,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_extpclk_clk_src[] = अणु
	अणु .src = P_HDMIPLL पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 extpclk_clk_src = अणु
	.cmd_rcgr = 0x2060,
	.hid_width = 5,
	.parent_map = mmss_xo_hdmi_map,
	.freq_tbl = ftbl_extpclk_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "extpclk_clk_src",
		.parent_data = mmss_xo_hdmi,
		.num_parents = 3,
		.ops = &clk_byte_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_fd_core_clk_src[] = अणु
	F(100000000, P_GPLL0, 6, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	F(404000000, P_MMPLL0_OUT_EVEN, 2, 0, 0),
	F(480000000, P_MMPLL7_OUT_EVEN, 2, 0, 0),
	F(576000000, P_MMPLL10_OUT_EVEN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 fd_core_clk_src = अणु
	.cmd_rcgr = 0x3b00,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_fd_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fd_core_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 8,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_hdmi_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 hdmi_clk_src = अणु
	.cmd_rcgr = 0x2100,
	.hid_width = 5,
	.parent_map = mmss_xo_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_hdmi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "hdmi_clk_src",
		.parent_data = mmss_xo_gpll0_gpll0_भाग,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_jpeg0_clk_src[] = अणु
	F(75000000, P_GPLL0, 8, 0, 0),
	F(150000000, P_GPLL0, 4, 0, 0),
	F(320000000, P_MMPLL7_OUT_EVEN, 3, 0, 0),
	F(480000000, P_MMPLL7_OUT_EVEN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 jpeg0_clk_src = अणु
	.cmd_rcgr = 0x3500,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_jpeg0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "jpeg0_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 8,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_maxi_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(75000000, P_GPLL0_DIV, 4, 0, 0),
	F(171428571, P_GPLL0, 3.5, 0, 0),
	F(323200000, P_MMPLL0_OUT_EVEN, 2.5, 0, 0),
	F(406000000, P_MMPLL1_OUT_EVEN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 maxi_clk_src = अणु
	.cmd_rcgr = 0xf020,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll1_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_maxi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "maxi_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll1_gpll0_gpll0_भाग,
		.num_parents = 6,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_mclk_clk_src[] = अणु
	F(4800000, P_XO, 4, 0, 0),
	F(6000000, P_GPLL0_DIV, 10, 1, 5),
	F(8000000, P_GPLL0_DIV, 1, 2, 75),
	F(9600000, P_XO, 2, 0, 0),
	F(16666667, P_GPLL0_DIV, 2, 1, 9),
	F(19200000, P_XO, 1, 0, 0),
	F(24000000, P_GPLL0_DIV, 1, 2, 25),
	F(33333333, P_GPLL0_DIV, 1, 2, 9),
	F(48000000, P_GPLL0, 1, 2, 25),
	F(66666667, P_GPLL0, 1, 2, 9),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 mclk0_clk_src = अणु
	.cmd_rcgr = 0x3360,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_mclk_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mclk0_clk_src",
		.parent_data = mmss_xo_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 mclk1_clk_src = अणु
	.cmd_rcgr = 0x3390,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_mclk_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mclk1_clk_src",
		.parent_data = mmss_xo_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 mclk2_clk_src = अणु
	.cmd_rcgr = 0x33c0,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_mclk_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mclk2_clk_src",
		.parent_data = mmss_xo_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 mclk3_clk_src = अणु
	.cmd_rcgr = 0x33f0,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_mclk_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mclk3_clk_src",
		.parent_data = mmss_xo_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_mdp_clk_src[] = अणु
	F(85714286, P_GPLL0, 7, 0, 0),
	F(100000000, P_GPLL0, 6, 0, 0),
	F(150000000, P_GPLL0, 4, 0, 0),
	F(171428571, P_GPLL0, 3.5, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	F(275000000, P_MMPLL5_OUT_EVEN, 3, 0, 0),
	F(300000000, P_GPLL0, 2, 0, 0),
	F(330000000, P_MMPLL5_OUT_EVEN, 2.5, 0, 0),
	F(412500000, P_MMPLL5_OUT_EVEN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 mdp_clk_src = अणु
	.cmd_rcgr = 0x2040,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll5_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_mdp_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mdp_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll5_gpll0_gpll0_भाग,
		.num_parents = 6,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_vsync_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 vsync_clk_src = अणु
	.cmd_rcgr = 0x2080,
	.hid_width = 5,
	.parent_map = mmss_xo_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_vsync_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vsync_clk_src",
		.parent_data = mmss_xo_gpll0_gpll0_भाग,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_ahb_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(40000000, P_GPLL0, 15, 0, 0),
	F(80800000, P_MMPLL0_OUT_EVEN, 10, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 ahb_clk_src = अणु
	.cmd_rcgr = 0x5000,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_ahb_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ahb_clk_src",
		.parent_data = mmss_xo_mmpll0_gpll0_gpll0_भाग,
		.num_parents = 5,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_axi_clk_src[] = अणु
	F(75000000, P_GPLL0, 8, 0, 0),
	F(171428571, P_GPLL0, 3.5, 0, 0),
	F(240000000, P_GPLL0, 2.5, 0, 0),
	F(323200000, P_MMPLL0_OUT_EVEN, 2.5, 0, 0),
	F(406000000, P_MMPLL0_OUT_EVEN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

/* RO to linux */
अटल काष्ठा clk_rcg2 axi_clk_src = अणु
	.cmd_rcgr = 0xd000,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll1_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_axi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "axi_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll1_gpll0_gpll0_भाग,
		.num_parents = 6,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 pclk0_clk_src = अणु
	.cmd_rcgr = 0x2000,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmss_xo_dsi0pll_dsi1pll_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pclk0_clk_src",
		.parent_data = mmss_xo_dsi0pll_dsi1pll,
		.num_parents = 4,
		.ops = &clk_pixel_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 pclk1_clk_src = अणु
	.cmd_rcgr = 0x2020,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmss_xo_dsi0pll_dsi1pll_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pclk1_clk_src",
		.parent_data = mmss_xo_dsi0pll_dsi1pll,
		.num_parents = 4,
		.ops = &clk_pixel_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_rot_clk_src[] = अणु
	F(171428571, P_GPLL0, 3.5, 0, 0),
	F(275000000, P_MMPLL5_OUT_EVEN, 3, 0, 0),
	F(330000000, P_MMPLL5_OUT_EVEN, 2.5, 0, 0),
	F(412500000, P_MMPLL5_OUT_EVEN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 rot_clk_src = अणु
	.cmd_rcgr = 0x21a0,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll5_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_rot_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "rot_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll5_gpll0_gpll0_भाग,
		.num_parents = 6,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_video_core_clk_src[] = अणु
	F(200000000, P_GPLL0, 3, 0, 0),
	F(269330000, P_MMPLL0_OUT_EVEN, 3, 0, 0),
	F(355200000, P_MMPLL6_OUT_EVEN, 2.5, 0, 0),
	F(444000000, P_MMPLL6_OUT_EVEN, 2, 0, 0),
	F(533000000, P_MMPLL3_OUT_EVEN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 video_core_clk_src = अणु
	.cmd_rcgr = 0x1000,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll3_mmpll6_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_video_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "video_core_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll3_mmpll6_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 video_subcore0_clk_src = अणु
	.cmd_rcgr = 0x1060,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll3_mmpll6_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_video_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "video_subcore0_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll3_mmpll6_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 video_subcore1_clk_src = अणु
	.cmd_rcgr = 0x1080,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll3_mmpll6_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_video_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "video_subcore1_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll3_mmpll6_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_vfe_clk_src[] = अणु
	F(200000000, P_GPLL0, 3, 0, 0),
	F(300000000, P_GPLL0, 2, 0, 0),
	F(320000000, P_MMPLL7_OUT_EVEN, 3, 0, 0),
	F(384000000, P_MMPLL4_OUT_EVEN, 2, 0, 0),
	F(404000000, P_MMPLL0_OUT_EVEN, 2, 0, 0),
	F(480000000, P_MMPLL7_OUT_EVEN, 2, 0, 0),
	F(576000000, P_MMPLL10_OUT_EVEN, 1, 0, 0),
	F(600000000, P_GPLL0, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 vfe0_clk_src = अणु
	.cmd_rcgr = 0x3600,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_vfe_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vfe0_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 8,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 vfe1_clk_src = अणु
	.cmd_rcgr = 0x3620,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_vfe_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vfe1_clk_src",
		.parent_data = mmss_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 8,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch misc_ahb_clk = अणु
	.halt_reg = 0x328,
	.hwcg_reg = 0x328,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x328,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "misc_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_core_clk = अणु
	.halt_reg = 0x1028,
	.clkr = अणु
		.enable_reg = 0x1028,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &video_core_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_ahb_clk = अणु
	.halt_reg = 0x1030,
	.hwcg_reg = 0x1030,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x1030,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_axi_clk = अणु
	.halt_reg = 0x1034,
	.clkr = अणु
		.enable_reg = 0x1034,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &axi_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_maxi_clk = अणु
	.halt_reg = 0x1038,
	.clkr = अणु
		.enable_reg = 0x1038,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_maxi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &maxi_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_subcore0_clk = अणु
	.halt_reg = 0x1048,
	.clkr = अणु
		.enable_reg = 0x1048,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_subcore0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &video_subcore0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_subcore1_clk = अणु
	.halt_reg = 0x104c,
	.clkr = अणु
		.enable_reg = 0x104c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_subcore1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &video_subcore1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_ahb_clk = अणु
	.halt_reg = 0x2308,
	.hwcg_reg = 0x2308,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x2308,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_hdmi_dp_ahb_clk = अणु
	.halt_reg = 0x230c,
	.clkr = अणु
		.enable_reg = 0x230c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_hdmi_dp_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_axi_clk = अणु
	.halt_reg = 0x2310,
	.clkr = अणु
		.enable_reg = 0x2310,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &axi_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_pclk0_clk = अणु
	.halt_reg = 0x2314,
	.clkr = अणु
		.enable_reg = 0x2314,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_pclk0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &pclk0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_pclk1_clk = अणु
	.halt_reg = 0x2318,
	.clkr = अणु
		.enable_reg = 0x2318,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_pclk1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &pclk1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_mdp_clk = अणु
	.halt_reg = 0x231c,
	.clkr = अणु
		.enable_reg = 0x231c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_mdp_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mdp_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_mdp_lut_clk = अणु
	.halt_reg = 0x2320,
	.clkr = अणु
		.enable_reg = 0x2320,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_mdp_lut_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mdp_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_extpclk_clk = अणु
	.halt_reg = 0x2324,
	.clkr = अणु
		.enable_reg = 0x2324,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_extpclk_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &extpclk_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_vsync_clk = अणु
	.halt_reg = 0x2328,
	.clkr = अणु
		.enable_reg = 0x2328,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_vsync_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &vsync_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_hdmi_clk = अणु
	.halt_reg = 0x2338,
	.clkr = अणु
		.enable_reg = 0x2338,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_hdmi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &hdmi_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_byte0_clk = अणु
	.halt_reg = 0x233c,
	.clkr = अणु
		.enable_reg = 0x233c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_byte0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &byte0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_byte1_clk = अणु
	.halt_reg = 0x2340,
	.clkr = अणु
		.enable_reg = 0x2340,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_byte1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &byte1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_esc0_clk = अणु
	.halt_reg = 0x2344,
	.clkr = अणु
		.enable_reg = 0x2344,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_esc0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &esc0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_esc1_clk = अणु
	.halt_reg = 0x2348,
	.clkr = अणु
		.enable_reg = 0x2348,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_esc1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &esc1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_rot_clk = अणु
	.halt_reg = 0x2350,
	.clkr = अणु
		.enable_reg = 0x2350,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_rot_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &rot_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_dp_link_clk = अणु
	.halt_reg = 0x2354,
	.clkr = अणु
		.enable_reg = 0x2354,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_dp_link_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &dp_link_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_dp_link_पूर्णांकf_clk = अणु
	.halt_reg = 0x2358,
	.clkr = अणु
		.enable_reg = 0x2358,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_dp_link_intf_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &dp_link_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_dp_crypto_clk = अणु
	.halt_reg = 0x235c,
	.clkr = अणु
		.enable_reg = 0x235c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_dp_crypto_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &dp_crypto_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_dp_pixel_clk = अणु
	.halt_reg = 0x2360,
	.clkr = अणु
		.enable_reg = 0x2360,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_dp_pixel_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &dp_pixel_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_dp_aux_clk = अणु
	.halt_reg = 0x2364,
	.clkr = अणु
		.enable_reg = 0x2364,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_dp_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &dp_aux_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_byte0_पूर्णांकf_clk = अणु
	.halt_reg = 0x2374,
	.clkr = अणु
		.enable_reg = 0x2374,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_byte0_intf_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &byte0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_byte1_पूर्णांकf_clk = अणु
	.halt_reg = 0x2378,
	.clkr = अणु
		.enable_reg = 0x2378,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_byte1_intf_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &byte1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi0phyसमयr_clk = अणु
	.halt_reg = 0x3024,
	.clkr = अणु
		.enable_reg = 0x3024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi0phytimer_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi0phyसमयr_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi1phyसमयr_clk = अणु
	.halt_reg = 0x3054,
	.clkr = अणु
		.enable_reg = 0x3054,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi1phytimer_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi1phyसमयr_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi2phyसमयr_clk = अणु
	.halt_reg = 0x3084,
	.clkr = अणु
		.enable_reg = 0x3084,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi2phytimer_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi2phyसमयr_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi0_clk = अणु
	.halt_reg = 0x30b4,
	.clkr = अणु
		.enable_reg = 0x30b4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi0_ahb_clk = अणु
	.halt_reg = 0x30bc,
	.clkr = अणु
		.enable_reg = 0x30bc,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi0_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi0rdi_clk = अणु
	.halt_reg = 0x30d4,
	.clkr = अणु
		.enable_reg = 0x30d4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi0rdi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi0pix_clk = अणु
	.halt_reg = 0x30e4,
	.clkr = अणु
		.enable_reg = 0x30e4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi0pix_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi1_clk = अणु
	.halt_reg = 0x3124,
	.clkr = अणु
		.enable_reg = 0x3124,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi1_ahb_clk = अणु
	.halt_reg = 0x3128,
	.clkr = अणु
		.enable_reg = 0x3128,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi1_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi1rdi_clk = अणु
	.halt_reg = 0x3144,
	.clkr = अणु
		.enable_reg = 0x3144,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi1rdi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi1pix_clk = अणु
	.halt_reg = 0x3154,
	.clkr = अणु
		.enable_reg = 0x3154,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi1pix_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi2_clk = अणु
	.halt_reg = 0x3184,
	.clkr = अणु
		.enable_reg = 0x3184,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi2_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi2_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi2_ahb_clk = अणु
	.halt_reg = 0x3188,
	.clkr = अणु
		.enable_reg = 0x3188,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi2_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi2rdi_clk = अणु
	.halt_reg = 0x31a4,
	.clkr = अणु
		.enable_reg = 0x31a4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi2rdi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi2_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi2pix_clk = अणु
	.halt_reg = 0x31b4,
	.clkr = अणु
		.enable_reg = 0x31b4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi2pix_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi2_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi3_clk = अणु
	.halt_reg = 0x31e4,
	.clkr = अणु
		.enable_reg = 0x31e4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi3_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi3_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi3_ahb_clk = अणु
	.halt_reg = 0x31e8,
	.clkr = अणु
		.enable_reg = 0x31e8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi3_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi3rdi_clk = अणु
	.halt_reg = 0x3204,
	.clkr = अणु
		.enable_reg = 0x3204,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi3rdi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi3_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi3pix_clk = अणु
	.halt_reg = 0x3214,
	.clkr = अणु
		.enable_reg = 0x3214,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi3pix_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi3_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_ispअगर_ahb_clk = अणु
	.halt_reg = 0x3224,
	.clkr = अणु
		.enable_reg = 0x3224,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_ispif_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_cci_clk = अणु
	.halt_reg = 0x3344,
	.clkr = अणु
		.enable_reg = 0x3344,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_cci_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &cci_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_cci_ahb_clk = अणु
	.halt_reg = 0x3348,
	.clkr = अणु
		.enable_reg = 0x3348,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_cci_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_mclk0_clk = अणु
	.halt_reg = 0x3384,
	.clkr = अणु
		.enable_reg = 0x3384,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_mclk0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mclk0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_mclk1_clk = अणु
	.halt_reg = 0x33b4,
	.clkr = अणु
		.enable_reg = 0x33b4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_mclk1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mclk1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_mclk2_clk = अणु
	.halt_reg = 0x33e4,
	.clkr = अणु
		.enable_reg = 0x33e4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_mclk2_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mclk2_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_mclk3_clk = अणु
	.halt_reg = 0x3414,
	.clkr = अणु
		.enable_reg = 0x3414,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_mclk3_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mclk3_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_top_ahb_clk = अणु
	.halt_reg = 0x3484,
	.clkr = अणु
		.enable_reg = 0x3484,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_top_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_ahb_clk = अणु
	.halt_reg = 0x348c,
	.clkr = अणु
		.enable_reg = 0x348c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_micro_ahb_clk = अणु
	.halt_reg = 0x3494,
	.clkr = अणु
		.enable_reg = 0x3494,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_micro_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_jpeg0_clk = अणु
	.halt_reg = 0x35a8,
	.clkr = अणु
		.enable_reg = 0x35a8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_jpeg0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &jpeg0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_jpeg_ahb_clk = अणु
	.halt_reg = 0x35b4,
	.clkr = अणु
		.enable_reg = 0x35b4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_jpeg_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_jpeg_axi_clk = अणु
	.halt_reg = 0x35b8,
	.clkr = अणु
		.enable_reg = 0x35b8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_jpeg_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &axi_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_vfe0_ahb_clk = अणु
	.halt_reg = 0x3668,
	.clkr = अणु
		.enable_reg = 0x3668,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_vfe0_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_vfe1_ahb_clk = अणु
	.halt_reg = 0x3678,
	.clkr = अणु
		.enable_reg = 0x3678,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_vfe1_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_vfe0_clk = अणु
	.halt_reg = 0x36a8,
	.clkr = अणु
		.enable_reg = 0x36a8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_vfe0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &vfe0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_vfe1_clk = अणु
	.halt_reg = 0x36ac,
	.clkr = अणु
		.enable_reg = 0x36ac,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_vfe1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &vfe1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_cpp_clk = अणु
	.halt_reg = 0x36b0,
	.clkr = अणु
		.enable_reg = 0x36b0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_cpp_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &cpp_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_cpp_ahb_clk = अणु
	.halt_reg = 0x36b4,
	.clkr = अणु
		.enable_reg = 0x36b4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_cpp_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_vfe_vbअगर_ahb_clk = अणु
	.halt_reg = 0x36b8,
	.clkr = अणु
		.enable_reg = 0x36b8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_vfe_vbif_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_vfe_vbअगर_axi_clk = अणु
	.halt_reg = 0x36bc,
	.clkr = अणु
		.enable_reg = 0x36bc,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_vfe_vbif_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &axi_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_cpp_axi_clk = अणु
	.halt_reg = 0x36c4,
	.clkr = अणु
		.enable_reg = 0x36c4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_cpp_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &axi_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_cpp_vbअगर_ahb_clk = अणु
	.halt_reg = 0x36c8,
	.clkr = अणु
		.enable_reg = 0x36c8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_cpp_vbif_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi_vfe0_clk = अणु
	.halt_reg = 0x3704,
	.clkr = अणु
		.enable_reg = 0x3704,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi_vfe0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &vfe0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi_vfe1_clk = अणु
	.halt_reg = 0x3714,
	.clkr = अणु
		.enable_reg = 0x3714,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi_vfe1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &vfe1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_vfe0_stream_clk = अणु
	.halt_reg = 0x3720,
	.clkr = अणु
		.enable_reg = 0x3720,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_vfe0_stream_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &vfe0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_vfe1_stream_clk = अणु
	.halt_reg = 0x3724,
	.clkr = अणु
		.enable_reg = 0x3724,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_vfe1_stream_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &vfe1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_cphy_csid0_clk = अणु
	.halt_reg = 0x3730,
	.clkr = अणु
		.enable_reg = 0x3730,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_cphy_csid0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csiphy_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_cphy_csid1_clk = अणु
	.halt_reg = 0x3734,
	.clkr = अणु
		.enable_reg = 0x3734,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_cphy_csid1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csiphy_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_cphy_csid2_clk = अणु
	.halt_reg = 0x3738,
	.clkr = अणु
		.enable_reg = 0x3738,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_cphy_csid2_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csiphy_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_cphy_csid3_clk = अणु
	.halt_reg = 0x373c,
	.clkr = अणु
		.enable_reg = 0x373c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_cphy_csid3_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csiphy_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csiphy0_clk = अणु
	.halt_reg = 0x3740,
	.clkr = अणु
		.enable_reg = 0x3740,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csiphy0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csiphy_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csiphy1_clk = अणु
	.halt_reg = 0x3744,
	.clkr = अणु
		.enable_reg = 0x3744,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csiphy1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csiphy_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csiphy2_clk = अणु
	.halt_reg = 0x3748,
	.clkr = अणु
		.enable_reg = 0x3748,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csiphy2_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csiphy_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch fd_core_clk = अणु
	.halt_reg = 0x3b68,
	.clkr = अणु
		.enable_reg = 0x3b68,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "fd_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &fd_core_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch fd_core_uar_clk = अणु
	.halt_reg = 0x3b6c,
	.clkr = अणु
		.enable_reg = 0x3b6c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "fd_core_uar_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &fd_core_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch fd_ahb_clk = अणु
	.halt_reg = 0x3b74,
	.clkr = अणु
		.enable_reg = 0x3b74,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "fd_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mnoc_ahb_clk = अणु
	.halt_reg = 0x5024,
	.clkr = अणु
		.enable_reg = 0x5024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mnoc_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch bimc_smmu_ahb_clk = अणु
	.halt_reg = 0xe004,
	.hwcg_reg = 0xe004,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xe004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "bimc_smmu_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch bimc_smmu_axi_clk = अणु
	.halt_reg = 0xe008,
	.hwcg_reg = 0xe008,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xe008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "bimc_smmu_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &axi_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mnoc_maxi_clk = अणु
	.halt_reg = 0xf004,
	.clkr = अणु
		.enable_reg = 0xf004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mnoc_maxi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &maxi_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch vmem_maxi_clk = अणु
	.halt_reg = 0xf064,
	.clkr = अणु
		.enable_reg = 0xf064,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vmem_maxi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &maxi_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch vmem_ahb_clk = अणु
	.halt_reg = 0xf068,
	.clkr = अणु
		.enable_reg = 0xf068,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vmem_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_hw *mmcc_msm8998_hws[] = अणु
	&gpll0_भाग.hw,
पूर्ण;

अटल काष्ठा gdsc video_top_gdsc = अणु
	.gdscr = 0x1024,
	.pd = अणु
		.name = "video_top",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc video_subcore0_gdsc = अणु
	.gdscr = 0x1040,
	.pd = अणु
		.name = "video_subcore0",
	पूर्ण,
	.parent = &video_top_gdsc.pd,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc video_subcore1_gdsc = अणु
	.gdscr = 0x1044,
	.pd = अणु
		.name = "video_subcore1",
	पूर्ण,
	.parent = &video_top_gdsc.pd,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc mdss_gdsc = अणु
	.gdscr = 0x2304,
	.cxcs = (अचिन्हित पूर्णांक [])अणु 0x2310, 0x2350, 0x231c, 0x2320 पूर्ण,
	.cxc_count = 4,
	.pd = अणु
		.name = "mdss",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc camss_top_gdsc = अणु
	.gdscr = 0x34a0,
	.cxcs = (अचिन्हित पूर्णांक [])अणु 0x35b8, 0x36c4, 0x3704, 0x3714, 0x3494,
				   0x35a8, 0x3868 पूर्ण,
	.cxc_count = 7,
	.pd = अणु
		.name = "camss_top",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc camss_vfe0_gdsc = अणु
	.gdscr = 0x3664,
	.pd = अणु
		.name = "camss_vfe0",
	पूर्ण,
	.parent = &camss_top_gdsc.pd,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc camss_vfe1_gdsc = अणु
	.gdscr = 0x3674,
	.pd = अणु
		.name = "camss_vfe1_gdsc",
	पूर्ण,
	.parent = &camss_top_gdsc.pd,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc camss_cpp_gdsc = अणु
	.gdscr = 0x36d4,
	.pd = अणु
		.name = "camss_cpp",
	पूर्ण,
	.parent = &camss_top_gdsc.pd,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc bimc_smmu_gdsc = अणु
	.gdscr = 0xe020,
	.gds_hw_ctrl = 0xe024,
	.pd = अणु
		.name = "bimc_smmu",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = HW_CTRL | ALWAYS_ON,
पूर्ण;

अटल काष्ठा clk_regmap *mmcc_msm8998_घड़ीs[] = अणु
	[MMPLL0] = &mmpll0.clkr,
	[MMPLL0_OUT_EVEN] = &mmpll0_out_even.clkr,
	[MMPLL1] = &mmpll1.clkr,
	[MMPLL1_OUT_EVEN] = &mmpll1_out_even.clkr,
	[MMPLL3] = &mmpll3.clkr,
	[MMPLL3_OUT_EVEN] = &mmpll3_out_even.clkr,
	[MMPLL4] = &mmpll4.clkr,
	[MMPLL4_OUT_EVEN] = &mmpll4_out_even.clkr,
	[MMPLL5] = &mmpll5.clkr,
	[MMPLL5_OUT_EVEN] = &mmpll5_out_even.clkr,
	[MMPLL6] = &mmpll6.clkr,
	[MMPLL6_OUT_EVEN] = &mmpll6_out_even.clkr,
	[MMPLL7] = &mmpll7.clkr,
	[MMPLL7_OUT_EVEN] = &mmpll7_out_even.clkr,
	[MMPLL10] = &mmpll10.clkr,
	[MMPLL10_OUT_EVEN] = &mmpll10_out_even.clkr,
	[BYTE0_CLK_SRC] = &byte0_clk_src.clkr,
	[BYTE1_CLK_SRC] = &byte1_clk_src.clkr,
	[CCI_CLK_SRC] = &cci_clk_src.clkr,
	[CPP_CLK_SRC] = &cpp_clk_src.clkr,
	[CSI0_CLK_SRC] = &csi0_clk_src.clkr,
	[CSI1_CLK_SRC] = &csi1_clk_src.clkr,
	[CSI2_CLK_SRC] = &csi2_clk_src.clkr,
	[CSI3_CLK_SRC] = &csi3_clk_src.clkr,
	[CSIPHY_CLK_SRC] = &csiphy_clk_src.clkr,
	[CSI0PHYTIMER_CLK_SRC] = &csi0phyसमयr_clk_src.clkr,
	[CSI1PHYTIMER_CLK_SRC] = &csi1phyसमयr_clk_src.clkr,
	[CSI2PHYTIMER_CLK_SRC] = &csi2phyसमयr_clk_src.clkr,
	[DP_AUX_CLK_SRC] = &dp_aux_clk_src.clkr,
	[DP_CRYPTO_CLK_SRC] = &dp_crypto_clk_src.clkr,
	[DP_LINK_CLK_SRC] = &dp_link_clk_src.clkr,
	[DP_PIXEL_CLK_SRC] = &dp_pixel_clk_src.clkr,
	[ESC0_CLK_SRC] = &esc0_clk_src.clkr,
	[ESC1_CLK_SRC] = &esc1_clk_src.clkr,
	[EXTPCLK_CLK_SRC] = &extpclk_clk_src.clkr,
	[FD_CORE_CLK_SRC] = &fd_core_clk_src.clkr,
	[HDMI_CLK_SRC] = &hdmi_clk_src.clkr,
	[JPEG0_CLK_SRC] = &jpeg0_clk_src.clkr,
	[MAXI_CLK_SRC] = &maxi_clk_src.clkr,
	[MCLK0_CLK_SRC] = &mclk0_clk_src.clkr,
	[MCLK1_CLK_SRC] = &mclk1_clk_src.clkr,
	[MCLK2_CLK_SRC] = &mclk2_clk_src.clkr,
	[MCLK3_CLK_SRC] = &mclk3_clk_src.clkr,
	[MDP_CLK_SRC] = &mdp_clk_src.clkr,
	[VSYNC_CLK_SRC] = &vsync_clk_src.clkr,
	[AHB_CLK_SRC] = &ahb_clk_src.clkr,
	[AXI_CLK_SRC] = &axi_clk_src.clkr,
	[PCLK0_CLK_SRC] = &pclk0_clk_src.clkr,
	[PCLK1_CLK_SRC] = &pclk1_clk_src.clkr,
	[ROT_CLK_SRC] = &rot_clk_src.clkr,
	[VIDEO_CORE_CLK_SRC] = &video_core_clk_src.clkr,
	[VIDEO_SUBCORE0_CLK_SRC] = &video_subcore0_clk_src.clkr,
	[VIDEO_SUBCORE1_CLK_SRC] = &video_subcore1_clk_src.clkr,
	[VFE0_CLK_SRC] = &vfe0_clk_src.clkr,
	[VFE1_CLK_SRC] = &vfe1_clk_src.clkr,
	[MISC_AHB_CLK] = &misc_ahb_clk.clkr,
	[VIDEO_CORE_CLK] = &video_core_clk.clkr,
	[VIDEO_AHB_CLK] = &video_ahb_clk.clkr,
	[VIDEO_AXI_CLK] = &video_axi_clk.clkr,
	[VIDEO_MAXI_CLK] = &video_maxi_clk.clkr,
	[VIDEO_SUBCORE0_CLK] = &video_subcore0_clk.clkr,
	[VIDEO_SUBCORE1_CLK] = &video_subcore1_clk.clkr,
	[MDSS_AHB_CLK] = &mdss_ahb_clk.clkr,
	[MDSS_HDMI_DP_AHB_CLK] = &mdss_hdmi_dp_ahb_clk.clkr,
	[MDSS_AXI_CLK] = &mdss_axi_clk.clkr,
	[MDSS_PCLK0_CLK] = &mdss_pclk0_clk.clkr,
	[MDSS_PCLK1_CLK] = &mdss_pclk1_clk.clkr,
	[MDSS_MDP_CLK] = &mdss_mdp_clk.clkr,
	[MDSS_MDP_LUT_CLK] = &mdss_mdp_lut_clk.clkr,
	[MDSS_EXTPCLK_CLK] = &mdss_extpclk_clk.clkr,
	[MDSS_VSYNC_CLK] = &mdss_vsync_clk.clkr,
	[MDSS_HDMI_CLK] = &mdss_hdmi_clk.clkr,
	[MDSS_BYTE0_CLK] = &mdss_byte0_clk.clkr,
	[MDSS_BYTE1_CLK] = &mdss_byte1_clk.clkr,
	[MDSS_ESC0_CLK] = &mdss_esc0_clk.clkr,
	[MDSS_ESC1_CLK] = &mdss_esc1_clk.clkr,
	[MDSS_ROT_CLK] = &mdss_rot_clk.clkr,
	[MDSS_DP_LINK_CLK] = &mdss_dp_link_clk.clkr,
	[MDSS_DP_LINK_INTF_CLK] = &mdss_dp_link_पूर्णांकf_clk.clkr,
	[MDSS_DP_CRYPTO_CLK] = &mdss_dp_crypto_clk.clkr,
	[MDSS_DP_PIXEL_CLK] = &mdss_dp_pixel_clk.clkr,
	[MDSS_DP_AUX_CLK] = &mdss_dp_aux_clk.clkr,
	[MDSS_BYTE0_INTF_CLK] = &mdss_byte0_पूर्णांकf_clk.clkr,
	[MDSS_BYTE1_INTF_CLK] = &mdss_byte1_पूर्णांकf_clk.clkr,
	[CAMSS_CSI0PHYTIMER_CLK] = &camss_csi0phyसमयr_clk.clkr,
	[CAMSS_CSI1PHYTIMER_CLK] = &camss_csi1phyसमयr_clk.clkr,
	[CAMSS_CSI2PHYTIMER_CLK] = &camss_csi2phyसमयr_clk.clkr,
	[CAMSS_CSI0_CLK] = &camss_csi0_clk.clkr,
	[CAMSS_CSI0_AHB_CLK] = &camss_csi0_ahb_clk.clkr,
	[CAMSS_CSI0RDI_CLK] = &camss_csi0rdi_clk.clkr,
	[CAMSS_CSI0PIX_CLK] = &camss_csi0pix_clk.clkr,
	[CAMSS_CSI1_CLK] = &camss_csi1_clk.clkr,
	[CAMSS_CSI1_AHB_CLK] = &camss_csi1_ahb_clk.clkr,
	[CAMSS_CSI1RDI_CLK] = &camss_csi1rdi_clk.clkr,
	[CAMSS_CSI1PIX_CLK] = &camss_csi1pix_clk.clkr,
	[CAMSS_CSI2_CLK] = &camss_csi2_clk.clkr,
	[CAMSS_CSI2_AHB_CLK] = &camss_csi2_ahb_clk.clkr,
	[CAMSS_CSI2RDI_CLK] = &camss_csi2rdi_clk.clkr,
	[CAMSS_CSI2PIX_CLK] = &camss_csi2pix_clk.clkr,
	[CAMSS_CSI3_CLK] = &camss_csi3_clk.clkr,
	[CAMSS_CSI3_AHB_CLK] = &camss_csi3_ahb_clk.clkr,
	[CAMSS_CSI3RDI_CLK] = &camss_csi3rdi_clk.clkr,
	[CAMSS_CSI3PIX_CLK] = &camss_csi3pix_clk.clkr,
	[CAMSS_ISPIF_AHB_CLK] = &camss_ispअगर_ahb_clk.clkr,
	[CAMSS_CCI_CLK] = &camss_cci_clk.clkr,
	[CAMSS_CCI_AHB_CLK] = &camss_cci_ahb_clk.clkr,
	[CAMSS_MCLK0_CLK] = &camss_mclk0_clk.clkr,
	[CAMSS_MCLK1_CLK] = &camss_mclk1_clk.clkr,
	[CAMSS_MCLK2_CLK] = &camss_mclk2_clk.clkr,
	[CAMSS_MCLK3_CLK] = &camss_mclk3_clk.clkr,
	[CAMSS_TOP_AHB_CLK] = &camss_top_ahb_clk.clkr,
	[CAMSS_AHB_CLK] = &camss_ahb_clk.clkr,
	[CAMSS_MICRO_AHB_CLK] = &camss_micro_ahb_clk.clkr,
	[CAMSS_JPEG0_CLK] = &camss_jpeg0_clk.clkr,
	[CAMSS_JPEG_AHB_CLK] = &camss_jpeg_ahb_clk.clkr,
	[CAMSS_JPEG_AXI_CLK] = &camss_jpeg_axi_clk.clkr,
	[CAMSS_VFE0_AHB_CLK] = &camss_vfe0_ahb_clk.clkr,
	[CAMSS_VFE1_AHB_CLK] = &camss_vfe1_ahb_clk.clkr,
	[CAMSS_VFE0_CLK] = &camss_vfe0_clk.clkr,
	[CAMSS_VFE1_CLK] = &camss_vfe1_clk.clkr,
	[CAMSS_CPP_CLK] = &camss_cpp_clk.clkr,
	[CAMSS_CPP_AHB_CLK] = &camss_cpp_ahb_clk.clkr,
	[CAMSS_VFE_VBIF_AHB_CLK] = &camss_vfe_vbअगर_ahb_clk.clkr,
	[CAMSS_VFE_VBIF_AXI_CLK] = &camss_vfe_vbअगर_axi_clk.clkr,
	[CAMSS_CPP_AXI_CLK] = &camss_cpp_axi_clk.clkr,
	[CAMSS_CPP_VBIF_AHB_CLK] = &camss_cpp_vbअगर_ahb_clk.clkr,
	[CAMSS_CSI_VFE0_CLK] = &camss_csi_vfe0_clk.clkr,
	[CAMSS_CSI_VFE1_CLK] = &camss_csi_vfe1_clk.clkr,
	[CAMSS_VFE0_STREAM_CLK] = &camss_vfe0_stream_clk.clkr,
	[CAMSS_VFE1_STREAM_CLK] = &camss_vfe1_stream_clk.clkr,
	[CAMSS_CPHY_CSID0_CLK] = &camss_cphy_csid0_clk.clkr,
	[CAMSS_CPHY_CSID1_CLK] = &camss_cphy_csid1_clk.clkr,
	[CAMSS_CPHY_CSID2_CLK] = &camss_cphy_csid2_clk.clkr,
	[CAMSS_CPHY_CSID3_CLK] = &camss_cphy_csid3_clk.clkr,
	[CAMSS_CSIPHY0_CLK] = &camss_csiphy0_clk.clkr,
	[CAMSS_CSIPHY1_CLK] = &camss_csiphy1_clk.clkr,
	[CAMSS_CSIPHY2_CLK] = &camss_csiphy2_clk.clkr,
	[FD_CORE_CLK] = &fd_core_clk.clkr,
	[FD_CORE_UAR_CLK] = &fd_core_uar_clk.clkr,
	[FD_AHB_CLK] = &fd_ahb_clk.clkr,
	[MNOC_AHB_CLK] = &mnoc_ahb_clk.clkr,
	[BIMC_SMMU_AHB_CLK] = &bimc_smmu_ahb_clk.clkr,
	[BIMC_SMMU_AXI_CLK] = &bimc_smmu_axi_clk.clkr,
	[MNOC_MAXI_CLK] = &mnoc_maxi_clk.clkr,
	[VMEM_MAXI_CLK] = &vmem_maxi_clk.clkr,
	[VMEM_AHB_CLK] = &vmem_ahb_clk.clkr,
पूर्ण;

अटल काष्ठा gdsc *mmcc_msm8998_gdscs[] = अणु
	[VIDEO_TOP_GDSC] = &video_top_gdsc,
	[VIDEO_SUBCORE0_GDSC] = &video_subcore0_gdsc,
	[VIDEO_SUBCORE1_GDSC] = &video_subcore1_gdsc,
	[MDSS_GDSC] = &mdss_gdsc,
	[CAMSS_TOP_GDSC] = &camss_top_gdsc,
	[CAMSS_VFE0_GDSC] = &camss_vfe0_gdsc,
	[CAMSS_VFE1_GDSC] = &camss_vfe1_gdsc,
	[CAMSS_CPP_GDSC] = &camss_cpp_gdsc,
	[BIMC_SMMU_GDSC] = &bimc_smmu_gdsc,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map mmcc_msm8998_resets[] = अणु
	[SPDM_BCR] = अणु 0x200 पूर्ण,
	[SPDM_RM_BCR] = अणु 0x300 पूर्ण,
	[MISC_BCR] = अणु 0x320 पूर्ण,
	[VIDEO_TOP_BCR] = अणु 0x1020 पूर्ण,
	[THROTTLE_VIDEO_BCR] = अणु 0x1180 पूर्ण,
	[MDSS_BCR] = अणु 0x2300 पूर्ण,
	[THROTTLE_MDSS_BCR] = अणु 0x2460 पूर्ण,
	[CAMSS_PHY0_BCR] = अणु 0x3020 पूर्ण,
	[CAMSS_PHY1_BCR] = अणु 0x3050 पूर्ण,
	[CAMSS_PHY2_BCR] = अणु 0x3080 पूर्ण,
	[CAMSS_CSI0_BCR] = अणु 0x30b0 पूर्ण,
	[CAMSS_CSI0RDI_BCR] = अणु 0x30d0 पूर्ण,
	[CAMSS_CSI0PIX_BCR] = अणु 0x30e0 पूर्ण,
	[CAMSS_CSI1_BCR] = अणु 0x3120 पूर्ण,
	[CAMSS_CSI1RDI_BCR] = अणु 0x3140 पूर्ण,
	[CAMSS_CSI1PIX_BCR] = अणु 0x3150 पूर्ण,
	[CAMSS_CSI2_BCR] = अणु 0x3180 पूर्ण,
	[CAMSS_CSI2RDI_BCR] = अणु 0x31a0 पूर्ण,
	[CAMSS_CSI2PIX_BCR] = अणु 0x31b0 पूर्ण,
	[CAMSS_CSI3_BCR] = अणु 0x31e0 पूर्ण,
	[CAMSS_CSI3RDI_BCR] = अणु 0x3200 पूर्ण,
	[CAMSS_CSI3PIX_BCR] = अणु 0x3210 पूर्ण,
	[CAMSS_ISPIF_BCR] = अणु 0x3220 पूर्ण,
	[CAMSS_CCI_BCR] = अणु 0x3340 पूर्ण,
	[CAMSS_TOP_BCR] = अणु 0x3480 पूर्ण,
	[CAMSS_AHB_BCR] = अणु 0x3488 पूर्ण,
	[CAMSS_MICRO_BCR] = अणु 0x3490 पूर्ण,
	[CAMSS_JPEG_BCR] = अणु 0x35a0 पूर्ण,
	[CAMSS_VFE0_BCR] = अणु 0x3660 पूर्ण,
	[CAMSS_VFE1_BCR] = अणु 0x3670 पूर्ण,
	[CAMSS_VFE_VBIF_BCR] = अणु 0x36a0 पूर्ण,
	[CAMSS_CPP_TOP_BCR] = अणु 0x36c0 पूर्ण,
	[CAMSS_CPP_BCR] = अणु 0x36d0 पूर्ण,
	[CAMSS_CSI_VFE0_BCR] = अणु 0x3700 पूर्ण,
	[CAMSS_CSI_VFE1_BCR] = अणु 0x3710 पूर्ण,
	[CAMSS_FD_BCR] = अणु 0x3b60 पूर्ण,
	[THROTTLE_CAMSS_BCR] = अणु 0x3c30 पूर्ण,
	[MNOCAHB_BCR] = अणु 0x5020 पूर्ण,
	[MNOCAXI_BCR] = अणु 0xd020 पूर्ण,
	[BMIC_SMMU_BCR] = अणु 0xe000 पूर्ण,
	[MNOC_MAXI_BCR] = अणु 0xf000 पूर्ण,
	[VMEM_BCR] = अणु 0xf060 पूर्ण,
	[BTO_BCR] = अणु 0x10004 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config mmcc_msm8998_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x10004,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc mmcc_msm8998_desc = अणु
	.config = &mmcc_msm8998_regmap_config,
	.clks = mmcc_msm8998_घड़ीs,
	.num_clks = ARRAY_SIZE(mmcc_msm8998_घड़ीs),
	.resets = mmcc_msm8998_resets,
	.num_resets = ARRAY_SIZE(mmcc_msm8998_resets),
	.gdscs = mmcc_msm8998_gdscs,
	.num_gdscs = ARRAY_SIZE(mmcc_msm8998_gdscs),
	.clk_hws = mmcc_msm8998_hws,
	.num_clk_hws = ARRAY_SIZE(mmcc_msm8998_hws),
पूर्ण;

अटल स्थिर काष्ठा of_device_id mmcc_msm8998_match_table[] = अणु
	अणु .compatible = "qcom,mmcc-msm8998" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mmcc_msm8998_match_table);

अटल पूर्णांक mmcc_msm8998_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;

	regmap = qcom_cc_map(pdev, &mmcc_msm8998_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस qcom_cc_really_probe(pdev, &mmcc_msm8998_desc, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver mmcc_msm8998_driver = अणु
	.probe		= mmcc_msm8998_probe,
	.driver		= अणु
		.name	= "mmcc-msm8998",
		.of_match_table = mmcc_msm8998_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mmcc_msm8998_driver);

MODULE_DESCRIPTION("QCOM MMCC MSM8998 Driver");
MODULE_LICENSE("GPL v2");
