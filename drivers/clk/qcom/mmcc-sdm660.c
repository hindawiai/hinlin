<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 * Copyright (c) 2020, Martin Botka <martin.botka@soमुख्यline.org>
 * Copyright (c) 2020, Konrad Dybcio <konrad.dybcio@soमुख्यline.org>
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
#समावेश <linux/clk.h>


#समावेश <dt-bindings/घड़ी/qcom,mmcc-sdm660.h>

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
	P_DSI0PLL_BYTE,
	P_DSI0PLL,
	P_DSI1PLL_BYTE,
	P_DSI1PLL,
	P_GPLL0,
	P_GPLL0_DIV,
	P_MMPLL0,
	P_MMPLL10,
	P_MMPLL3,
	P_MMPLL4,
	P_MMPLL5,
	P_MMPLL6,
	P_MMPLL7,
	P_MMPLL8,
	P_SLEEP_CLK,
	P_DP_PHY_PLL_LINK_CLK,
	P_DP_PHY_PLL_VCO_DIV,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll8_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0, 1 पूर्ण,
	अणु P_MMPLL4, 2 पूर्ण,
	अणु P_MMPLL7, 3 पूर्ण,
	अणु P_MMPLL8, 4 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण,
पूर्ण;

/* Voteable PLL */
अटल काष्ठा clk_alpha_pll mmpll0 = अणु
	.offset = 0xc000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.clkr = अणु
		.enable_reg = 0x1f0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmpll0",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll6 =  अणु
	.offset = 0xf0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.clkr = अणु
		.enable_reg = 0x1f0,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmpll6",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* APSS controlled PLLs */
अटल काष्ठा pll_vco vco[] = अणु
	अणु 1000000000, 2000000000, 0 पूर्ण,
	अणु 750000000, 1500000000, 1 पूर्ण,
	अणु 500000000, 1000000000, 2 पूर्ण,
	अणु 250000000, 500000000, 3 पूर्ण,
पूर्ण;

अटल काष्ठा pll_vco mmpll3_vco[] = अणु
	अणु 750000000, 1500000000, 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा alpha_pll_config mmpll10_config = अणु
	.l = 0x1e,
	.config_ctl_val = 0x00004289,
	.मुख्य_output_mask = 0x1,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll10 = अणु
	.offset = 0x190,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmpll10",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा alpha_pll_config mmpll3_config = अणु
	.l = 0x2e,
	.config_ctl_val = 0x4001055b,
	.vco_val = 0x1 << 20,
	.vco_mask = 0x3 << 20,
	.मुख्य_output_mask = 0x1,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll3 = अणु
	.offset = 0x0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.vco_table = mmpll3_vco,
	.num_vco = ARRAY_SIZE(mmpll3_vco),
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmpll3",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा alpha_pll_config mmpll4_config = अणु
	.l = 0x28,
	.config_ctl_val = 0x4001055b,
	.vco_val = 0x2 << 20,
	.vco_mask = 0x3 << 20,
	.मुख्य_output_mask = 0x1,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll4 = अणु
	.offset = 0x50,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.vco_table = vco,
	.num_vco = ARRAY_SIZE(vco),
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmpll4",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा alpha_pll_config mmpll5_config = अणु
	.l = 0x2a,
	.config_ctl_val = 0x4001055b,
	.alpha_hi = 0xf8,
	.alpha_en_mask = BIT(24),
	.vco_val = 0x2 << 20,
	.vco_mask = 0x3 << 20,
	.मुख्य_output_mask = 0x1,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll5 = अणु
	.offset = 0xa0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.vco_table = vco,
	.num_vco = ARRAY_SIZE(vco),
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmpll5",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा alpha_pll_config mmpll7_config = अणु
	.l = 0x32,
	.config_ctl_val = 0x4001055b,
	.vco_val = 0x2 << 20,
	.vco_mask = 0x3 << 20,
	.मुख्य_output_mask = 0x1,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll7 = अणु
	.offset = 0x140,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.vco_table = vco,
	.num_vco = ARRAY_SIZE(vco),
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmpll7",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा alpha_pll_config mmpll8_config = अणु
	.l = 0x30,
	.alpha_hi = 0x70,
	.alpha_en_mask = BIT(24),
	.config_ctl_val = 0x4001055b,
	.vco_val = 0x2 << 20,
	.vco_mask = 0x3 << 20,
	.मुख्य_output_mask = 0x1,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll8 = अणु
	.offset = 0x1c0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.vco_table = vco,
	.num_vco = ARRAY_SIZE(vco),
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmpll8",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll8_gpll0_gpll0_भाग[] = अणु
	अणु .fw_name = "xo" पूर्ण,
	अणु .hw = &mmpll0.clkr.hw पूर्ण,
	अणु .hw = &mmpll4.clkr.hw पूर्ण,
	अणु .hw = &mmpll7.clkr.hw पूर्ण,
	अणु .hw = &mmpll8.clkr.hw पूर्ण,
	अणु .fw_name = "gpll0" पूर्ण,
	अणु .fw_name = "gpll0_div" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmcc_xo_dsibyte_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_DSI0PLL_BYTE, 1 पूर्ण,
	अणु P_DSI1PLL_BYTE, 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmcc_xo_dsibyte[] = अणु
	अणु .fw_name = "xo" पूर्ण,
	अणु .fw_name = "dsi0pllbyte" पूर्ण,
	अणु .fw_name = "dsi1pllbyte" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0, 1 पूर्ण,
	अणु P_MMPLL4, 2 पूर्ण,
	अणु P_MMPLL7, 3 पूर्ण,
	अणु P_MMPLL10, 4 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग[] = अणु
	अणु .fw_name = "xo" पूर्ण,
	अणु .hw = &mmpll0.clkr.hw पूर्ण,
	अणु .hw = &mmpll4.clkr.hw पूर्ण,
	अणु .hw = &mmpll7.clkr.hw पूर्ण,
	अणु .hw = &mmpll10.clkr.hw पूर्ण,
	अणु .fw_name = "gpll0" पूर्ण,
	अणु .fw_name = "gpll0_div" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmcc_xo_mmpll4_mmpll7_mmpll10_sleep_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL4, 1 पूर्ण,
	अणु P_MMPLL7, 2 पूर्ण,
	अणु P_MMPLL10, 3 पूर्ण,
	अणु P_SLEEP_CLK, 4 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmcc_xo_mmpll4_mmpll7_mmpll10_sleep_gpll0_gpll0_भाग[] = अणु
	अणु .fw_name = "xo" पूर्ण,
	अणु .hw = &mmpll4.clkr.hw पूर्ण,
	अणु .hw = &mmpll7.clkr.hw पूर्ण,
	अणु .hw = &mmpll10.clkr.hw पूर्ण,
	अणु .fw_name = "sleep_clk" पूर्ण,
	अणु .fw_name = "gpll0" पूर्ण,
	अणु .fw_name = "gpll0_div" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmcc_xo_mmpll0_mmpll7_mmpll10_sleep_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0, 1 पूर्ण,
	अणु P_MMPLL7, 2 पूर्ण,
	अणु P_MMPLL10, 3 पूर्ण,
	अणु P_SLEEP_CLK, 4 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmcc_xo_mmpll0_mmpll7_mmpll10_sleep_gpll0_gpll0_भाग[] = अणु
	अणु .fw_name = "xo" पूर्ण,
	अणु .hw = &mmpll0.clkr.hw पूर्ण,
	अणु .hw = &mmpll7.clkr.hw पूर्ण,
	अणु .hw = &mmpll10.clkr.hw पूर्ण,
	अणु .fw_name = "sleep_clk" पूर्ण,
	अणु .fw_name = "gpll0" पूर्ण,
	अणु .fw_name = "gpll0_div" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmcc_xo_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmcc_xo_gpll0_gpll0_भाग[] = अणु
	अणु .fw_name = "xo" पूर्ण,
	अणु .fw_name = "gpll0" पूर्ण,
	अणु .fw_name = "gpll0_div" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmcc_xo_dplink_dpvco_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_DP_PHY_PLL_LINK_CLK, 1 पूर्ण,
	अणु P_DP_PHY_PLL_VCO_DIV, 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmcc_xo_dplink_dpvco[] = अणु
	अणु .fw_name = "xo" पूर्ण,
	अणु .fw_name = "dp_link_2x_clk_divsel_five" पूर्ण,
	अणु .fw_name = "dp_vco_divided_clk_src_mux" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmcc_xo_mmpll0_mmpll5_mmpll7_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0, 1 पूर्ण,
	अणु P_MMPLL5, 2 पूर्ण,
	अणु P_MMPLL7, 3 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmcc_xo_mmpll0_mmpll5_mmpll7_gpll0_gpll0_भाग[] = अणु
	अणु .fw_name = "xo" पूर्ण,
	अणु .hw = &mmpll0.clkr.hw पूर्ण,
	अणु .hw = &mmpll5.clkr.hw पूर्ण,
	अणु .hw = &mmpll7.clkr.hw पूर्ण,
	अणु .fw_name = "gpll0" पूर्ण,
	अणु .fw_name = "gpll0_div" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmcc_xo_dsi0pll_dsi1pll_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_DSI0PLL, 1 पूर्ण,
	अणु P_DSI1PLL, 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmcc_xo_dsi0pll_dsi1pll[] = अणु
	अणु .fw_name = "xo" पूर्ण,
	अणु .fw_name = "dsi0pll" पूर्ण,
	अणु .fw_name = "dsi1pll" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmcc_mmpll0_mmpll4_mmpll7_mmpll10_mmpll6_gpll0_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0, 1 पूर्ण,
	अणु P_MMPLL4, 2 पूर्ण,
	अणु P_MMPLL7, 3 पूर्ण,
	अणु P_MMPLL10, 4 पूर्ण,
	अणु P_MMPLL6, 5 पूर्ण,
	अणु P_GPLL0, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmcc_mmpll0_mmpll4_mmpll7_mmpll10_mmpll6_gpll0[] = अणु
	अणु .fw_name = "xo" पूर्ण,
	अणु .hw = &mmpll0.clkr.hw पूर्ण,
	अणु .hw = &mmpll4.clkr.hw पूर्ण,
	अणु .hw = &mmpll7.clkr.hw पूर्ण,
	अणु .hw = &mmpll10.clkr.hw पूर्ण,
	अणु .hw = &mmpll6.clkr.hw पूर्ण,
	अणु .fw_name = "gpll0" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmcc_xo_mmpll0_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0, 1 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmcc_xo_mmpll0_gpll0_gpll0_भाग[] = अणु
	अणु .fw_name = "xo" पूर्ण,
	अणु .hw = &mmpll0.clkr.hw पूर्ण,
	अणु .fw_name = "gpll0" पूर्ण,
	अणु .fw_name = "gpll0_div" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_mmpll6_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0, 1 पूर्ण,
	अणु P_MMPLL4, 2 पूर्ण,
	अणु P_MMPLL7, 3 पूर्ण,
	अणु P_MMPLL10, 4 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_MMPLL6, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_mmpll6[] = अणु
	अणु .fw_name = "xo" पूर्ण,
	अणु .hw = &mmpll0.clkr.hw पूर्ण,
	अणु .hw = &mmpll4.clkr.hw पूर्ण,
	अणु .hw = &mmpll7.clkr.hw पूर्ण,
	अणु .hw = &mmpll10.clkr.hw पूर्ण,
	अणु .fw_name = "gpll0" पूर्ण,
	अणु .hw = &mmpll6.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmcc_xo_mmpll0_mmpll8_mmpll3_mmpll6_gpll0_mmpll7_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0, 1 पूर्ण,
	अणु P_MMPLL8, 2 पूर्ण,
	अणु P_MMPLL3, 3 पूर्ण,
	अणु P_MMPLL6, 4 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_MMPLL7, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mmcc_xo_mmpll0_mmpll8_mmpll3_mmpll6_gpll0_mmpll7[] = अणु
	अणु .fw_name = "xo" पूर्ण,
	अणु .hw = &mmpll0.clkr.hw पूर्ण,
	अणु .hw = &mmpll8.clkr.hw पूर्ण,
	अणु .hw = &mmpll3.clkr.hw पूर्ण,
	अणु .hw = &mmpll6.clkr.hw पूर्ण,
	अणु .fw_name = "gpll0" पूर्ण,
	अणु .hw = &mmpll7.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_ahb_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(40000000, P_GPLL0_DIV, 7.5, 0, 0),
	F(80800000, P_MMPLL0, 10, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 ahb_clk_src = अणु
	.cmd_rcgr = 0x5000,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll0_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_ahb_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ahb_clk_src",
		.parent_data = mmcc_xo_mmpll0_gpll0_gpll0_भाग,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 byte0_clk_src = अणु
	.cmd_rcgr = 0x2120,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_dsibyte_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "byte0_clk_src",
		.parent_data = mmcc_xo_dsibyte,
		.num_parents = 3,
		.ops = &clk_byte2_ops,
		.flags = CLK_SET_RATE_PARENT | CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 byte1_clk_src = अणु
	.cmd_rcgr = 0x2140,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_dsibyte_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "byte1_clk_src",
		.parent_data = mmcc_xo_dsibyte,
		.num_parents = 3,
		.ops = &clk_byte2_ops,
		.flags = CLK_SET_RATE_PARENT | CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_camss_gp0_clk_src[] = अणु
	F(10000, P_XO, 16, 1, 120),
	F(24000, P_XO, 16, 1, 50),
	F(6000000, P_GPLL0_DIV, 10, 1, 5),
	F(12000000, P_GPLL0_DIV, 10, 2, 5),
	F(13043478, P_GPLL0_DIV, 1, 1, 23),
	F(24000000, P_GPLL0_DIV, 1, 2, 25),
	F(50000000, P_GPLL0_DIV, 6, 0, 0),
	F(100000000, P_GPLL0_DIV, 3, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 camss_gp0_clk_src = अणु
	.cmd_rcgr = 0x3420,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll0_mmpll7_mmpll10_sleep_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_camss_gp0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "camss_gp0_clk_src",
		.parent_data = mmcc_xo_mmpll0_mmpll7_mmpll10_sleep_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 camss_gp1_clk_src = अणु
	.cmd_rcgr = 0x3450,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll0_mmpll7_mmpll10_sleep_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_camss_gp0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "camss_gp1_clk_src",
		.parent_data = mmcc_xo_mmpll0_mmpll7_mmpll10_sleep_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cci_clk_src[] = अणु
	F(37500000, P_GPLL0_DIV, 8, 0, 0),
	F(50000000, P_GPLL0_DIV, 6, 0, 0),
	F(100000000, P_GPLL0, 6, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cci_clk_src = अणु
	.cmd_rcgr = 0x3300,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll0_mmpll7_mmpll10_sleep_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_cci_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cci_clk_src",
		.parent_data = mmcc_xo_mmpll0_mmpll7_mmpll10_sleep_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cpp_clk_src[] = अणु
	F(120000000, P_GPLL0, 5, 0, 0),
	F(256000000, P_MMPLL4, 3, 0, 0),
	F(384000000, P_MMPLL4, 2, 0, 0),
	F(480000000, P_MMPLL7, 2, 0, 0),
	F(540000000, P_MMPLL6, 2, 0, 0),
	F(576000000, P_MMPLL10, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cpp_clk_src = अणु
	.cmd_rcgr = 0x3640,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_mmpll6_map,
	.freq_tbl = ftbl_cpp_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpp_clk_src",
		.parent_data = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_mmpll6,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_csi0_clk_src[] = अणु
	F(100000000, P_GPLL0_DIV, 3, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	F(310000000, P_MMPLL8, 3, 0, 0),
	F(404000000, P_MMPLL0, 2, 0, 0),
	F(465000000, P_MMPLL8, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 csi0_clk_src = अणु
	.cmd_rcgr = 0x3090,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll8_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csi0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi0_clk_src",
		.parent_data = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll8_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_csi0phyसमयr_clk_src[] = अणु
	F(100000000, P_GPLL0_DIV, 3, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	F(269333333, P_MMPLL0, 3, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 csi0phyसमयr_clk_src = अणु
	.cmd_rcgr = 0x3000,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csi0phyसमयr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi0phytimer_clk_src",
		.parent_data = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 csi1_clk_src = अणु
	.cmd_rcgr = 0x3100,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll8_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csi0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi1_clk_src",
		.parent_data = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll8_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 csi1phyसमयr_clk_src = अणु
	.cmd_rcgr = 0x3030,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csi0phyसमयr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi1phytimer_clk_src",
		.parent_data = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 csi2_clk_src = अणु
	.cmd_rcgr = 0x3160,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll8_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csi0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi2_clk_src",
		.parent_data = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll8_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 csi2phyसमयr_clk_src = अणु
	.cmd_rcgr = 0x3060,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csi0phyसमयr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi2phytimer_clk_src",
		.parent_data = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 csi3_clk_src = अणु
	.cmd_rcgr = 0x31c0,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll8_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csi0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi3_clk_src",
		.parent_data = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll8_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_csiphy_clk_src[] = अणु
	F(100000000, P_GPLL0_DIV, 3, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	F(269333333, P_MMPLL0, 3, 0, 0),
	F(320000000, P_MMPLL7, 3, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 csiphy_clk_src = अणु
	.cmd_rcgr = 0x3800,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll8_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csiphy_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csiphy_clk_src",
		.parent_data = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll8_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_dp_aux_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 dp_aux_clk_src = अणु
	.cmd_rcgr = 0x2260,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_dp_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "dp_aux_clk_src",
		.parent_data = mmcc_xo_gpll0_gpll0_भाग,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_dp_crypto_clk_src[] = अणु
	F(101250000, P_DP_PHY_PLL_VCO_DIV, 4, 0, 0),
	F(168750000, P_DP_PHY_PLL_VCO_DIV, 4, 0, 0),
	F(337500000, P_DP_PHY_PLL_VCO_DIV, 4, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 dp_crypto_clk_src = अणु
	.cmd_rcgr = 0x2220,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmcc_xo_dplink_dpvco_map,
	.freq_tbl = ftbl_dp_crypto_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "dp_crypto_clk_src",
		.parent_data = mmcc_xo_dplink_dpvco,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_dp_gtc_clk_src[] = अणु
	F(40000000, P_GPLL0_DIV, 7.5, 0, 0),
	F(60000000, P_GPLL0, 10, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 dp_gtc_clk_src = अणु
	.cmd_rcgr = 0x2280,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_dp_gtc_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "dp_gtc_clk_src",
		.parent_data = mmcc_xo_gpll0_gpll0_भाग,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_dp_link_clk_src[] = अणु
	F(162000000, P_DP_PHY_PLL_LINK_CLK, 2, 0, 0),
	F(270000000, P_DP_PHY_PLL_LINK_CLK, 2, 0, 0),
	F(540000000, P_DP_PHY_PLL_LINK_CLK, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 dp_link_clk_src = अणु
	.cmd_rcgr = 0x2200,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_dplink_dpvco_map,
	.freq_tbl = ftbl_dp_link_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "dp_link_clk_src",
		.parent_data = mmcc_xo_dplink_dpvco,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
		.flags = CLK_GET_RATE_NOCACHE | CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 dp_pixel_clk_src = अणु
	.cmd_rcgr = 0x2240,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = mmcc_xo_dplink_dpvco_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "dp_pixel_clk_src",
		.parent_data = mmcc_xo_dplink_dpvco,
		.num_parents = 3,
		.ops = &clk_dp_ops,
		.flags = CLK_GET_RATE_NOCACHE | CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 esc0_clk_src = अणु
	.cmd_rcgr = 0x2160,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_dsibyte_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "esc0_clk_src",
		.parent_data = mmcc_xo_dsibyte,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 esc1_clk_src = अणु
	.cmd_rcgr = 0x2180,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_dsibyte_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "esc1_clk_src",
		.parent_data = mmcc_xo_dsibyte,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_jpeg0_clk_src[] = अणु
	F(66666667, P_GPLL0_DIV, 4.5, 0, 0),
	F(133333333, P_GPLL0, 4.5, 0, 0),
	F(219428571, P_MMPLL4, 3.5, 0, 0),
	F(320000000, P_MMPLL7, 3, 0, 0),
	F(480000000, P_MMPLL7, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 jpeg0_clk_src = अणु
	.cmd_rcgr = 0x3500,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_jpeg0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "jpeg0_clk_src",
		.parent_data = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_mclk0_clk_src[] = अणु
	F(4800000, P_XO, 4, 0, 0),
	F(6000000, P_GPLL0_DIV, 10, 1, 5),
	F(8000000, P_GPLL0_DIV, 1, 2, 75),
	F(9600000, P_XO, 2, 0, 0),
	F(16666667, P_GPLL0_DIV, 2, 1, 9),
	F(19200000, P_XO, 1, 0, 0),
	F(24000000, P_MMPLL10, 1, 1, 24),
	F(33333333, P_GPLL0_DIV, 1, 1, 9),
	F(48000000, P_GPLL0, 1, 2, 25),
	F(66666667, P_GPLL0, 1, 1, 9),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 mclk0_clk_src = अणु
	.cmd_rcgr = 0x3360,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll4_mmpll7_mmpll10_sleep_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_mclk0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mclk0_clk_src",
		.parent_data = mmcc_xo_mmpll4_mmpll7_mmpll10_sleep_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 mclk1_clk_src = अणु
	.cmd_rcgr = 0x3390,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll4_mmpll7_mmpll10_sleep_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_mclk0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mclk1_clk_src",
		.parent_data = mmcc_xo_mmpll4_mmpll7_mmpll10_sleep_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 mclk2_clk_src = अणु
	.cmd_rcgr = 0x33c0,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll4_mmpll7_mmpll10_sleep_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_mclk0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mclk2_clk_src",
		.parent_data = mmcc_xo_mmpll4_mmpll7_mmpll10_sleep_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 mclk3_clk_src = अणु
	.cmd_rcgr = 0x33f0,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll4_mmpll7_mmpll10_sleep_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_mclk0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mclk3_clk_src",
		.parent_data = mmcc_xo_mmpll4_mmpll7_mmpll10_sleep_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_mdp_clk_src[] = अणु
	F(100000000, P_GPLL0_DIV, 3, 0, 0),
	F(150000000, P_GPLL0_DIV, 2, 0, 0),
	F(171428571, P_GPLL0, 3.5, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	F(275000000, P_MMPLL5, 3, 0, 0),
	F(300000000, P_GPLL0, 2, 0, 0),
	F(330000000, P_MMPLL5, 2.5, 0, 0),
	F(412500000, P_MMPLL5, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 mdp_clk_src = अणु
	.cmd_rcgr = 0x2040,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll0_mmpll5_mmpll7_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_mdp_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mdp_clk_src",
		.parent_data = mmcc_xo_mmpll0_mmpll5_mmpll7_gpll0_gpll0_भाग,
		.num_parents = 6,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 pclk0_clk_src = अणु
	.cmd_rcgr = 0x2000,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmcc_xo_dsi0pll_dsi1pll_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pclk0_clk_src",
		.parent_data = mmcc_xo_dsi0pll_dsi1pll,
		.num_parents = 3,
		.ops = &clk_pixel_ops,
		.flags = CLK_SET_RATE_PARENT | CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 pclk1_clk_src = अणु
	.cmd_rcgr = 0x2020,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmcc_xo_dsi0pll_dsi1pll_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pclk1_clk_src",
		.parent_data = mmcc_xo_dsi0pll_dsi1pll,
		.num_parents = 3,
		.ops = &clk_pixel_ops,
		.flags = CLK_SET_RATE_PARENT | CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_rot_clk_src[] = अणु
	F(171428571, P_GPLL0, 3.5, 0, 0),
	F(275000000, P_MMPLL5, 3, 0, 0),
	F(300000000, P_GPLL0, 2, 0, 0),
	F(330000000, P_MMPLL5, 2.5, 0, 0),
	F(412500000, P_MMPLL5, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 rot_clk_src = अणु
	.cmd_rcgr = 0x21a0,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll0_mmpll5_mmpll7_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_rot_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "rot_clk_src",
		.parent_data = mmcc_xo_mmpll0_mmpll5_mmpll7_gpll0_gpll0_भाग,
		.num_parents = 6,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_vfe0_clk_src[] = अणु
	F(120000000, P_GPLL0, 5, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	F(256000000, P_MMPLL4, 3, 0, 0),
	F(300000000, P_GPLL0, 2, 0, 0),
	F(404000000, P_MMPLL0, 2, 0, 0),
	F(480000000, P_MMPLL7, 2, 0, 0),
	F(540000000, P_MMPLL6, 2, 0, 0),
	F(576000000, P_MMPLL10, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 vfe0_clk_src = अणु
	.cmd_rcgr = 0x3600,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_mmpll0_mmpll4_mmpll7_mmpll10_mmpll6_gpll0_map,
	.freq_tbl = ftbl_vfe0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vfe0_clk_src",
		.parent_data = mmcc_mmpll0_mmpll4_mmpll7_mmpll10_mmpll6_gpll0,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 vfe1_clk_src = अणु
	.cmd_rcgr = 0x3620,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_mmpll0_mmpll4_mmpll7_mmpll10_mmpll6_gpll0_map,
	.freq_tbl = ftbl_vfe0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vfe1_clk_src",
		.parent_data = mmcc_mmpll0_mmpll4_mmpll7_mmpll10_mmpll6_gpll0,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_video_core_clk_src[] = अणु
	F(133333333, P_GPLL0, 4.5, 0, 0),
	F(269333333, P_MMPLL0, 3, 0, 0),
	F(320000000, P_MMPLL7, 3, 0, 0),
	F(404000000, P_MMPLL0, 2, 0, 0),
	F(441600000, P_MMPLL3, 2, 0, 0),
	F(518400000, P_MMPLL3, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 video_core_clk_src = अणु
	.cmd_rcgr = 0x1000,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll0_mmpll8_mmpll3_mmpll6_gpll0_mmpll7_map,
	.freq_tbl = ftbl_video_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "video_core_clk_src",
		.parent_data = mmcc_xo_mmpll0_mmpll8_mmpll3_mmpll6_gpll0_mmpll7,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
		.flags = CLK_IS_CRITICAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 vsync_clk_src = अणु
	.cmd_rcgr = 0x2080,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = mmcc_xo_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_dp_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vsync_clk_src",
		.parent_data = mmcc_xo_gpll0_gpll0_भाग,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch bimc_smmu_ahb_clk = अणु
	.halt_reg = 0xe004,
	.halt_check = BRANCH_VOTED,
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
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch bimc_smmu_axi_clk = अणु
	.halt_reg = 0xe008,
	.halt_check = BRANCH_VOTED,
	.hwcg_reg = 0xe008,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xe008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "bimc_smmu_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_ahb_clk = अणु
	.halt_reg = 0x348c,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x348c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x348c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_cci_ahb_clk = अणु
	.halt_reg = 0x3348,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3348,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_cci_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_cci_clk = अणु
	.halt_reg = 0x3344,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3344,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_cci_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &cci_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_cpp_ahb_clk = अणु
	.halt_reg = 0x36b4,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x36b4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_cpp_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_cpp_axi_clk = अणु
	.halt_reg = 0x36c4,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x36c4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_cpp_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_cpp_clk = अणु
	.halt_reg = 0x36b0,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x36b0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_cpp_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &cpp_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_cpp_vbअगर_ahb_clk = अणु
	.halt_reg = 0x36c8,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x36c8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_cpp_vbif_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi0_ahb_clk = अणु
	.halt_reg = 0x30bc,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x30bc,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi0_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi0_clk = अणु
	.halt_reg = 0x30b4,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x30b4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi0phyसमयr_clk = अणु
	.halt_reg = 0x3024,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi0phytimer_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi0phyसमयr_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi0pix_clk = अणु
	.halt_reg = 0x30e4,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x30e4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi0pix_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi0rdi_clk = अणु
	.halt_reg = 0x30d4,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x30d4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi0rdi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi1_ahb_clk = अणु
	.halt_reg = 0x3128,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3128,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi1_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi1_clk = अणु
	.halt_reg = 0x3124,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3124,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi1phyसमयr_clk = अणु
	.halt_reg = 0x3054,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3054,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi1phytimer_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi1phyसमयr_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi1pix_clk = अणु
	.halt_reg = 0x3154,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3154,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi1pix_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi1rdi_clk = अणु
	.halt_reg = 0x3144,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3144,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi1rdi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi2_ahb_clk = अणु
	.halt_reg = 0x3188,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3188,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi2_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi2_clk = अणु
	.halt_reg = 0x3184,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3184,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi2_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi2_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi2phyसमयr_clk = अणु
	.halt_reg = 0x3084,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3084,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi2phytimer_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi2phyसमयr_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi2pix_clk = अणु
	.halt_reg = 0x31b4,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x31b4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi2pix_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi2_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi2rdi_clk = अणु
	.halt_reg = 0x31a4,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x31a4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi2rdi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi2_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi3_ahb_clk = अणु
	.halt_reg = 0x31e8,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x31e8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi3_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi3_clk = अणु
	.halt_reg = 0x31e4,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x31e4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi3_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi3_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi3pix_clk = अणु
	.halt_reg = 0x3214,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3214,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi3pix_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi3_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi3rdi_clk = अणु
	.halt_reg = 0x3204,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3204,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi3rdi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csi3_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi_vfe0_clk = अणु
	.halt_reg = 0x3704,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3704,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi_vfe0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &vfe0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi_vfe1_clk = अणु
	.halt_reg = 0x3714,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3714,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi_vfe1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &vfe1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csiphy0_clk = अणु
	.halt_reg = 0x3740,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3740,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csiphy0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csiphy_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csiphy1_clk = अणु
	.halt_reg = 0x3744,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3744,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csiphy1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csiphy_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csiphy2_clk = अणु
	.halt_reg = 0x3748,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3748,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csiphy2_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csiphy_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;


अटल काष्ठा clk_branch camss_cphy_csid0_clk = अणु
	.halt_reg = 0x3730,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3730,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_cphy_csid0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &camss_csiphy0_clk.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_cphy_csid1_clk = अणु
	.halt_reg = 0x3734,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3734,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_cphy_csid1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &camss_csiphy1_clk.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_cphy_csid2_clk = अणु
	.halt_reg = 0x3738,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3738,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_cphy_csid2_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &camss_csiphy2_clk.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_cphy_csid3_clk = अणु
	.halt_reg = 0x373c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x373c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_cphy_csid3_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &csiphy_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_gp0_clk = अणु
	.halt_reg = 0x3444,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3444,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_gp0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &camss_gp0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_gp1_clk = अणु
	.halt_reg = 0x3474,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3474,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_gp1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &camss_gp1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_ispअगर_ahb_clk = अणु
	.halt_reg = 0x3224,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3224,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_ispif_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_jpeg0_clk = अणु
	.halt_reg = 0x35a8,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x35a8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_jpeg0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &jpeg0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_jpeg_ahb_clk = अणु
	.halt_reg = 0x35b4,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x35b4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_jpeg_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_jpeg_axi_clk = अणु
	.halt_reg = 0x35b8,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x35b8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_jpeg_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch throttle_camss_axi_clk = अणु
	.halt_reg = 0x3c3c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3c3c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "throttle_camss_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_mclk0_clk = अणु
	.halt_reg = 0x3384,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3384,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_mclk0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mclk0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_mclk1_clk = अणु
	.halt_reg = 0x33b4,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x33b4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_mclk1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mclk1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_mclk2_clk = अणु
	.halt_reg = 0x33e4,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x33e4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_mclk2_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mclk2_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_mclk3_clk = अणु
	.halt_reg = 0x3414,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3414,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_mclk3_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mclk3_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_micro_ahb_clk = अणु
	.halt_reg = 0x3494,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3494,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_micro_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_top_ahb_clk = अणु
	.halt_reg = 0x3484,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3484,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_top_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_vfe0_ahb_clk = अणु
	.halt_reg = 0x3668,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3668,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_vfe0_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_vfe0_clk = अणु
	.halt_reg = 0x36a8,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x36a8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_vfe0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &vfe0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_vfe0_stream_clk = अणु
	.halt_reg = 0x3720,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3720,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_vfe0_stream_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &vfe0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_vfe1_ahb_clk = अणु
	.halt_reg = 0x3678,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3678,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_vfe1_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_vfe1_clk = अणु
	.halt_reg = 0x36ac,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x36ac,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_vfe1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &vfe1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_vfe1_stream_clk = अणु
	.halt_reg = 0x3724,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3724,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_vfe1_stream_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &vfe1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_vfe_vbअगर_ahb_clk = अणु
	.halt_reg = 0x36b8,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x36b8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_vfe_vbif_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_vfe_vbअगर_axi_clk = अणु
	.halt_reg = 0x36bc,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x36bc,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_vfe_vbif_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch csiphy_ahb2crअगर_clk = अणु
	.halt_reg = 0x374c,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x374c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x374c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "csiphy_ahb2crif_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_ahb_clk = अणु
	.halt_reg = 0x2308,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x8a004,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x2308,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.flags = CLK_SET_RATE_PARENT,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_axi_clk_src[] = अणु
		F(75000000, P_GPLL0, 8, 0, 0),
		F(171428571, P_GPLL0, 3.5, 0, 0),
		F(240000000, P_GPLL0, 2.5, 0, 0),
		F(323200000, P_MMPLL0, 2.5, 0, 0),
		F(406000000, P_MMPLL0, 2, 0, 0),
		अणु पूर्ण
पूर्ण;

/* RO to linux */
अटल काष्ठा clk_rcg2 axi_clk_src = अणु
	.cmd_rcgr = 0xd000,
	.hid_width = 5,
	.parent_map = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_axi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "axi_clk_src",
		.parent_data = mmcc_xo_mmpll0_mmpll4_mmpll7_mmpll10_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_axi_clk = अणु
	.halt_reg = 0x2310,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2310,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &axi_clk_src.clkr.hw पूर्ण,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch throttle_mdss_axi_clk = अणु
	.halt_reg = 0x246c,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x246c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x246c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "throttle_mdss_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_byte0_clk = अणु
	.halt_reg = 0x233c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x233c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_byte0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &byte0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_भाग mdss_byte0_पूर्णांकf_भाग_clk = अणु
	.reg = 0x237c,
	.shअगरt = 0,
	.width = 2,
	/*
	 * NOTE: Op करोes not work क्रम भाग-3. Current assumption is that भाग-3
	 * is not a recommended setting क्रम this भागider.
	 */
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_byte0_intf_div_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &byte0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_regmap_भाग_ops,
			.flags = CLK_GET_RATE_NOCACHE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_byte0_पूर्णांकf_clk = अणु
	.halt_reg = 0x2374,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2374,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_byte0_intf_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mdss_byte0_पूर्णांकf_भाग_clk.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT | CLK_GET_RATE_NOCACHE,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_byte1_clk = अणु
	.halt_reg = 0x2340,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2340,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_byte1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &byte1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_भाग mdss_byte1_पूर्णांकf_भाग_clk = अणु
	.reg = 0x2380,
	.shअगरt = 0,
	.width = 2,
	/*
	 * NOTE: Op करोes not work क्रम भाग-3. Current assumption is that भाग-3
	 * is not a recommended setting क्रम this भागider.
	 */
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_byte1_intf_div_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &byte1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_regmap_भाग_ops,
			.flags = CLK_GET_RATE_NOCACHE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_byte1_पूर्णांकf_clk = अणु
	.halt_reg = 0x2378,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2378,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_byte1_intf_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mdss_byte1_पूर्णांकf_भाग_clk.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT | CLK_GET_RATE_NOCACHE,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_dp_aux_clk = अणु
	.halt_reg = 0x2364,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2364,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_dp_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &dp_aux_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_dp_crypto_clk = अणु
	.halt_reg = 0x235c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x235c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_dp_crypto_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &dp_crypto_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_dp_gtc_clk = अणु
	.halt_reg = 0x2368,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2368,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_dp_gtc_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &dp_gtc_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_dp_link_clk = अणु
	.halt_reg = 0x2354,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2354,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_dp_link_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &dp_link_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_GET_RATE_NOCACHE | CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* Reset state of MDSS_DP_LINK_INTF_DIV is 0x3 (भाग-4) */
अटल काष्ठा clk_branch mdss_dp_link_पूर्णांकf_clk = अणु
	.halt_reg = 0x2358,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2358,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_dp_link_intf_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &dp_link_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_dp_pixel_clk = अणु
	.halt_reg = 0x2360,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2360,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_dp_pixel_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &dp_pixel_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_GET_RATE_NOCACHE | CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_esc0_clk = अणु
	.halt_reg = 0x2344,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2344,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_esc0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &esc0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_esc1_clk = अणु
	.halt_reg = 0x2348,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2348,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_esc1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &esc1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_hdmi_dp_ahb_clk = अणु
	.halt_reg = 0x230c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x230c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_hdmi_dp_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_mdp_clk = अणु
	.halt_reg = 0x231c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x231c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_mdp_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mdp_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_pclk0_clk = अणु
	.halt_reg = 0x2314,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2314,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_pclk0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &pclk0_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_pclk1_clk = अणु
	.halt_reg = 0x2318,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2318,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_pclk1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &pclk1_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_rot_clk = अणु
	.halt_reg = 0x2350,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2350,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_rot_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &rot_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_vsync_clk = अणु
	.halt_reg = 0x2328,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2328,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_vsync_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &vsync_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mnoc_ahb_clk = अणु
	.halt_reg = 0x5024,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x5024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mnoc_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &ahb_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch misc_ahb_clk = अणु
	.halt_reg = 0x328,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x328,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x328,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "misc_ahb_clk",
			/*
			 * Dependency to be enabled beक्रमe the branch is
			 * enabled.
			 */
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &mnoc_ahb_clk.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch misc_cxo_clk = अणु
	.halt_reg = 0x324,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x324,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "misc_cxo_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch snoc_dvm_axi_clk = अणु
	.halt_reg = 0xe040,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xe040,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "snoc_dvm_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_ahb_clk = अणु
	.halt_reg = 0x1030,
	.halt_check = BRANCH_HALT,
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
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_axi_clk = अणु
	.halt_reg = 0x1034,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x1034,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch throttle_video_axi_clk = अणु
	.halt_reg = 0x118c,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x118c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x118c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "throttle_video_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_core_clk = अणु
	.halt_reg = 0x1028,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x1028,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &video_core_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_subcore0_clk = अणु
	.halt_reg = 0x1048,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x1048,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_subcore0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &video_core_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT | CLK_GET_RATE_NOCACHE,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gdsc venus_gdsc = अणु
	.gdscr = 0x1024,
	.pd = अणु
		.name = "venus",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc venus_core0_gdsc = अणु
	.gdscr = 0x1040,
	.pd = अणु
		.name = "venus_core0",
	पूर्ण,
	.parent = &venus_gdsc.pd,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc mdss_gdsc = अणु
	.gdscr = 0x2304,
	.pd = अणु
		.name = "mdss",
	पूर्ण,
	.cxcs = (अचिन्हित पूर्णांक [])अणु 0x2040 पूर्ण,
	.cxc_count = 1,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc camss_top_gdsc = अणु
	.gdscr = 0x34a0,
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

/* This GDSC seems to hang the whole mulसमयdia subप्रणाली.
अटल काष्ठा gdsc bimc_smmu_gdsc = अणु
	.gdscr = 0xe020,
	.gds_hw_ctrl = 0xe024,
	.pd = अणु
		.name = "bimc_smmu",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.parent = &bimc_smmu_gdsc.pd,
	.flags = HW_CTRL,
पूर्ण;
*/

अटल काष्ठा clk_regmap *mmcc_660_घड़ीs[] = अणु
	[AHB_CLK_SRC] = &ahb_clk_src.clkr,
	[BYTE0_CLK_SRC] = &byte0_clk_src.clkr,
	[BYTE1_CLK_SRC] = &byte1_clk_src.clkr,
	[CAMSS_GP0_CLK_SRC] = &camss_gp0_clk_src.clkr,
	[CAMSS_GP1_CLK_SRC] = &camss_gp1_clk_src.clkr,
	[CCI_CLK_SRC] = &cci_clk_src.clkr,
	[CPP_CLK_SRC] = &cpp_clk_src.clkr,
	[CSI0_CLK_SRC] = &csi0_clk_src.clkr,
	[CSI0PHYTIMER_CLK_SRC] = &csi0phyसमयr_clk_src.clkr,
	[CSI1_CLK_SRC] = &csi1_clk_src.clkr,
	[CSI1PHYTIMER_CLK_SRC] = &csi1phyसमयr_clk_src.clkr,
	[CSI2_CLK_SRC] = &csi2_clk_src.clkr,
	[CSI2PHYTIMER_CLK_SRC] = &csi2phyसमयr_clk_src.clkr,
	[CSI3_CLK_SRC] = &csi3_clk_src.clkr,
	[CSIPHY_CLK_SRC] = &csiphy_clk_src.clkr,
	[DP_AUX_CLK_SRC] = &dp_aux_clk_src.clkr,
	[DP_CRYPTO_CLK_SRC] = &dp_crypto_clk_src.clkr,
	[DP_GTC_CLK_SRC] = &dp_gtc_clk_src.clkr,
	[DP_LINK_CLK_SRC] = &dp_link_clk_src.clkr,
	[DP_PIXEL_CLK_SRC] = &dp_pixel_clk_src.clkr,
	[ESC0_CLK_SRC] = &esc0_clk_src.clkr,
	[ESC1_CLK_SRC] = &esc1_clk_src.clkr,
	[JPEG0_CLK_SRC] = &jpeg0_clk_src.clkr,
	[MCLK0_CLK_SRC] = &mclk0_clk_src.clkr,
	[MCLK1_CLK_SRC] = &mclk1_clk_src.clkr,
	[MCLK2_CLK_SRC] = &mclk2_clk_src.clkr,
	[MCLK3_CLK_SRC] = &mclk3_clk_src.clkr,
	[MDP_CLK_SRC] = &mdp_clk_src.clkr,
	[MMPLL0_PLL] = &mmpll0.clkr,
	[MMPLL10_PLL] = &mmpll10.clkr,
	[MMPLL3_PLL] = &mmpll3.clkr,
	[MMPLL4_PLL] = &mmpll4.clkr,
	[MMPLL5_PLL] = &mmpll5.clkr,
	[MMPLL6_PLL] = &mmpll6.clkr,
	[MMPLL7_PLL] = &mmpll7.clkr,
	[MMPLL8_PLL] = &mmpll8.clkr,
	[BIMC_SMMU_AHB_CLK] = &bimc_smmu_ahb_clk.clkr,
	[BIMC_SMMU_AXI_CLK] = &bimc_smmu_axi_clk.clkr,
	[CAMSS_AHB_CLK] = &camss_ahb_clk.clkr,
	[CAMSS_CCI_AHB_CLK] = &camss_cci_ahb_clk.clkr,
	[CAMSS_CCI_CLK] = &camss_cci_clk.clkr,
	[CAMSS_CPHY_CSID0_CLK] = &camss_cphy_csid0_clk.clkr,
	[CAMSS_CPHY_CSID1_CLK] = &camss_cphy_csid1_clk.clkr,
	[CAMSS_CPHY_CSID2_CLK] = &camss_cphy_csid2_clk.clkr,
	[CAMSS_CPHY_CSID3_CLK] = &camss_cphy_csid3_clk.clkr,
	[CAMSS_CPP_AHB_CLK] = &camss_cpp_ahb_clk.clkr,
	[CAMSS_CPP_AXI_CLK] = &camss_cpp_axi_clk.clkr,
	[CAMSS_CPP_CLK] = &camss_cpp_clk.clkr,
	[CAMSS_CPP_VBIF_AHB_CLK] = &camss_cpp_vbअगर_ahb_clk.clkr,
	[CAMSS_CSI0_AHB_CLK] = &camss_csi0_ahb_clk.clkr,
	[CAMSS_CSI0_CLK] = &camss_csi0_clk.clkr,
	[CAMSS_CSI0PHYTIMER_CLK] = &camss_csi0phyसमयr_clk.clkr,
	[CAMSS_CSI0PIX_CLK] = &camss_csi0pix_clk.clkr,
	[CAMSS_CSI0RDI_CLK] = &camss_csi0rdi_clk.clkr,
	[CAMSS_CSI1_AHB_CLK] = &camss_csi1_ahb_clk.clkr,
	[CAMSS_CSI1_CLK] = &camss_csi1_clk.clkr,
	[CAMSS_CSI1PHYTIMER_CLK] = &camss_csi1phyसमयr_clk.clkr,
	[CAMSS_CSI1PIX_CLK] = &camss_csi1pix_clk.clkr,
	[CAMSS_CSI1RDI_CLK] = &camss_csi1rdi_clk.clkr,
	[CAMSS_CSI2_AHB_CLK] = &camss_csi2_ahb_clk.clkr,
	[CAMSS_CSI2_CLK] = &camss_csi2_clk.clkr,
	[CAMSS_CSI2PHYTIMER_CLK] = &camss_csi2phyसमयr_clk.clkr,
	[CAMSS_CSI2PIX_CLK] = &camss_csi2pix_clk.clkr,
	[CAMSS_CSI2RDI_CLK] = &camss_csi2rdi_clk.clkr,
	[CAMSS_CSI3_AHB_CLK] = &camss_csi3_ahb_clk.clkr,
	[CAMSS_CSI3_CLK] = &camss_csi3_clk.clkr,
	[CAMSS_CSI3PIX_CLK] = &camss_csi3pix_clk.clkr,
	[CAMSS_CSI3RDI_CLK] = &camss_csi3rdi_clk.clkr,
	[CAMSS_CSI_VFE0_CLK] = &camss_csi_vfe0_clk.clkr,
	[CAMSS_CSI_VFE1_CLK] = &camss_csi_vfe1_clk.clkr,
	[CAMSS_CSIPHY0_CLK] = &camss_csiphy0_clk.clkr,
	[CAMSS_CSIPHY1_CLK] = &camss_csiphy1_clk.clkr,
	[CAMSS_CSIPHY2_CLK] = &camss_csiphy2_clk.clkr,
	[CAMSS_GP0_CLK] = &camss_gp0_clk.clkr,
	[CAMSS_GP1_CLK] = &camss_gp1_clk.clkr,
	[CAMSS_ISPIF_AHB_CLK] = &camss_ispअगर_ahb_clk.clkr,
	[CAMSS_JPEG0_CLK] = &camss_jpeg0_clk.clkr,
	[CAMSS_JPEG_AHB_CLK] = &camss_jpeg_ahb_clk.clkr,
	[CAMSS_JPEG_AXI_CLK] = &camss_jpeg_axi_clk.clkr,
	[CAMSS_MCLK0_CLK] = &camss_mclk0_clk.clkr,
	[CAMSS_MCLK1_CLK] = &camss_mclk1_clk.clkr,
	[CAMSS_MCLK2_CLK] = &camss_mclk2_clk.clkr,
	[CAMSS_MCLK3_CLK] = &camss_mclk3_clk.clkr,
	[CAMSS_MICRO_AHB_CLK] = &camss_micro_ahb_clk.clkr,
	[CAMSS_TOP_AHB_CLK] = &camss_top_ahb_clk.clkr,
	[CAMSS_VFE0_AHB_CLK] = &camss_vfe0_ahb_clk.clkr,
	[CAMSS_VFE0_CLK] = &camss_vfe0_clk.clkr,
	[CAMSS_VFE0_STREAM_CLK] = &camss_vfe0_stream_clk.clkr,
	[CAMSS_VFE1_AHB_CLK] = &camss_vfe1_ahb_clk.clkr,
	[CAMSS_VFE1_CLK] = &camss_vfe1_clk.clkr,
	[CAMSS_VFE1_STREAM_CLK] = &camss_vfe1_stream_clk.clkr,
	[CAMSS_VFE_VBIF_AHB_CLK] = &camss_vfe_vbअगर_ahb_clk.clkr,
	[CAMSS_VFE_VBIF_AXI_CLK] = &camss_vfe_vbअगर_axi_clk.clkr,
	[CSIPHY_AHB2CRIF_CLK] = &csiphy_ahb2crअगर_clk.clkr,
	[MDSS_AHB_CLK] = &mdss_ahb_clk.clkr,
	[MDSS_AXI_CLK] = &mdss_axi_clk.clkr,
	[MDSS_BYTE0_CLK] = &mdss_byte0_clk.clkr,
	[MDSS_BYTE0_INTF_CLK] = &mdss_byte0_पूर्णांकf_clk.clkr,
	[MDSS_BYTE0_INTF_DIV_CLK] = &mdss_byte0_पूर्णांकf_भाग_clk.clkr,
	[MDSS_BYTE1_CLK] = &mdss_byte1_clk.clkr,
	[MDSS_BYTE1_INTF_CLK] = &mdss_byte1_पूर्णांकf_clk.clkr,
	[MDSS_DP_AUX_CLK] = &mdss_dp_aux_clk.clkr,
	[MDSS_DP_CRYPTO_CLK] = &mdss_dp_crypto_clk.clkr,
	[MDSS_DP_GTC_CLK] = &mdss_dp_gtc_clk.clkr,
	[MDSS_DP_LINK_CLK] = &mdss_dp_link_clk.clkr,
	[MDSS_DP_LINK_INTF_CLK] = &mdss_dp_link_पूर्णांकf_clk.clkr,
	[MDSS_DP_PIXEL_CLK] = &mdss_dp_pixel_clk.clkr,
	[MDSS_ESC0_CLK] = &mdss_esc0_clk.clkr,
	[MDSS_ESC1_CLK] = &mdss_esc1_clk.clkr,
	[MDSS_HDMI_DP_AHB_CLK] = &mdss_hdmi_dp_ahb_clk.clkr,
	[MDSS_MDP_CLK] = &mdss_mdp_clk.clkr,
	[MDSS_PCLK0_CLK] = &mdss_pclk0_clk.clkr,
	[MDSS_PCLK1_CLK] = &mdss_pclk1_clk.clkr,
	[MDSS_ROT_CLK] = &mdss_rot_clk.clkr,
	[MDSS_VSYNC_CLK] = &mdss_vsync_clk.clkr,
	[MISC_AHB_CLK] = &misc_ahb_clk.clkr,
	[MISC_CXO_CLK] = &misc_cxo_clk.clkr,
	[MNOC_AHB_CLK] = &mnoc_ahb_clk.clkr,
	[SNOC_DVM_AXI_CLK] = &snoc_dvm_axi_clk.clkr,
	[THROTTLE_CAMSS_AXI_CLK] = &throttle_camss_axi_clk.clkr,
	[THROTTLE_MDSS_AXI_CLK] = &throttle_mdss_axi_clk.clkr,
	[THROTTLE_VIDEO_AXI_CLK] = &throttle_video_axi_clk.clkr,
	[VIDEO_AHB_CLK] = &video_ahb_clk.clkr,
	[VIDEO_AXI_CLK] = &video_axi_clk.clkr,
	[VIDEO_CORE_CLK] = &video_core_clk.clkr,
	[VIDEO_SUBCORE0_CLK] = &video_subcore0_clk.clkr,
	[PCLK0_CLK_SRC] = &pclk0_clk_src.clkr,
	[PCLK1_CLK_SRC] = &pclk1_clk_src.clkr,
	[ROT_CLK_SRC] = &rot_clk_src.clkr,
	[VFE0_CLK_SRC] = &vfe0_clk_src.clkr,
	[VFE1_CLK_SRC] = &vfe1_clk_src.clkr,
	[VIDEO_CORE_CLK_SRC] = &video_core_clk_src.clkr,
	[VSYNC_CLK_SRC] = &vsync_clk_src.clkr,
	[MDSS_BYTE1_INTF_DIV_CLK] = &mdss_byte1_पूर्णांकf_भाग_clk.clkr,
	[AXI_CLK_SRC] = &axi_clk_src.clkr,
पूर्ण;

अटल काष्ठा gdsc *mmcc_sdm660_gdscs[] = अणु
	[VENUS_GDSC] = &venus_gdsc,
	[VENUS_CORE0_GDSC] = &venus_core0_gdsc,
	[MDSS_GDSC] = &mdss_gdsc,
	[CAMSS_TOP_GDSC] = &camss_top_gdsc,
	[CAMSS_VFE0_GDSC] = &camss_vfe0_gdsc,
	[CAMSS_VFE1_GDSC] = &camss_vfe1_gdsc,
	[CAMSS_CPP_GDSC] = &camss_cpp_gdsc,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map mmcc_660_resets[] = अणु
	[CAMSS_MICRO_BCR] = अणु 0x3490 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config mmcc_660_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x40000,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc mmcc_660_desc = अणु
	.config = &mmcc_660_regmap_config,
	.clks = mmcc_660_घड़ीs,
	.num_clks = ARRAY_SIZE(mmcc_660_घड़ीs),
	.resets = mmcc_660_resets,
	.num_resets = ARRAY_SIZE(mmcc_660_resets),
	.gdscs = mmcc_sdm660_gdscs,
	.num_gdscs = ARRAY_SIZE(mmcc_sdm660_gdscs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id mmcc_660_match_table[] = अणु
	अणु .compatible = "qcom,mmcc-sdm660" पूर्ण,
	अणु .compatible = "qcom,mmcc-sdm630", .data = (व्योम *)1UL पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mmcc_660_match_table);

अटल व्योम sdm630_घड़ी_override(व्योम)
अणु
	/* SDM630 has only one DSI */
	mmcc_660_desc.clks[BYTE1_CLK_SRC] = शून्य;
	mmcc_660_desc.clks[MDSS_BYTE1_CLK] = शून्य;
	mmcc_660_desc.clks[MDSS_BYTE1_INTF_DIV_CLK] = शून्य;
	mmcc_660_desc.clks[MDSS_BYTE1_INTF_CLK] = शून्य;
	mmcc_660_desc.clks[ESC1_CLK_SRC] = शून्य;
	mmcc_660_desc.clks[MDSS_ESC1_CLK] = शून्य;
	mmcc_660_desc.clks[PCLK1_CLK_SRC] = शून्य;
	mmcc_660_desc.clks[MDSS_PCLK1_CLK] = शून्य;
पूर्ण

अटल पूर्णांक mmcc_660_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *id;
	काष्ठा regmap *regmap;
	bool is_sdm630;

	id = of_match_device(mmcc_660_match_table, &pdev->dev);
	अगर (!id)
		वापस -ENODEV;
	is_sdm630 = !!(id->data);

	regmap = qcom_cc_map(pdev, &mmcc_660_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	अगर (is_sdm630)
		sdm630_घड़ी_override();

	clk_alpha_pll_configure(&mmpll3, regmap, &mmpll3_config);
	clk_alpha_pll_configure(&mmpll4, regmap, &mmpll4_config);
	clk_alpha_pll_configure(&mmpll5, regmap, &mmpll5_config);
	clk_alpha_pll_configure(&mmpll7, regmap, &mmpll7_config);
	clk_alpha_pll_configure(&mmpll8, regmap, &mmpll8_config);
	clk_alpha_pll_configure(&mmpll10, regmap, &mmpll10_config);

	वापस qcom_cc_really_probe(pdev, &mmcc_660_desc, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver mmcc_660_driver = अणु
	.probe		= mmcc_660_probe,
	.driver		= अणु
		.name	= "mmcc-sdm660",
		.of_match_table = mmcc_660_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mmcc_660_driver);

MODULE_DESCRIPTION("Qualcomm SDM630/SDM660 MMCC driver");
MODULE_LICENSE("GPL v2");
