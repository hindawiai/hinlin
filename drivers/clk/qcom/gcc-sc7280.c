<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2020-2021, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/qcom,gcc-sc7280.h>

#समावेश "clk-alpha-pll.h"
#समावेश "clk-branch.h"
#समावेश "clk-rcg.h"
#समावेश "clk-regmap-divider.h"
#समावेश "clk-regmap-mux.h"
#समावेश "common.h"
#समावेश "gdsc.h"
#समावेश "reset.h"

क्रमागत अणु
	P_BI_TCXO,
	P_GCC_GPLL0_OUT_EVEN,
	P_GCC_GPLL0_OUT_MAIN,
	P_GCC_GPLL0_OUT_ODD,
	P_GCC_GPLL10_OUT_MAIN,
	P_GCC_GPLL4_OUT_MAIN,
	P_GCC_GPLL9_OUT_MAIN,
	P_PCIE_0_PIPE_CLK,
	P_PCIE_1_PIPE_CLK,
	P_SLEEP_CLK,
	P_UFS_PHY_RX_SYMBOL_0_CLK,
	P_UFS_PHY_RX_SYMBOL_1_CLK,
	P_UFS_PHY_TX_SYMBOL_0_CLK,
	P_USB3_PHY_WRAPPER_GCC_USB30_PIPE_CLK,
	P_GCC_MSS_GPLL0_MAIN_DIV_CLK,
पूर्ण;

अटल काष्ठा clk_alpha_pll gcc_gpll0 = अणु
	.offset = 0x0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_LUCID],
	.clkr = अणु
		.enable_reg = 0x52010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gpll0",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_lucid_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable post_भाग_प्रकारable_gcc_gpll0_out_even[] = अणु
	अणु 0x1, 2 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gcc_gpll0_out_even = अणु
	.offset = 0x0,
	.post_भाग_shअगरt = 8,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_gcc_gpll0_out_even,
	.num_post_भाग = ARRAY_SIZE(post_भाग_प्रकारable_gcc_gpll0_out_even),
	.width = 4,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_LUCID],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_gpll0_out_even",
		.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
			&gcc_gpll0.clkr.hw,
		पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_lucid_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable post_भाग_प्रकारable_gcc_gpll0_out_odd[] = अणु
	अणु 0x3, 3 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gcc_gpll0_out_odd = अणु
	.offset = 0x0,
	.post_भाग_shअगरt = 12,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_gcc_gpll0_out_odd,
	.num_post_भाग = ARRAY_SIZE(post_भाग_प्रकारable_gcc_gpll0_out_odd),
	.width = 4,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_LUCID],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_gpll0_out_odd",
		.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
			&gcc_gpll0.clkr.hw,
		पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_lucid_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll gcc_gpll1 = अणु
	.offset = 0x1000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_LUCID],
	.clkr = अणु
		.enable_reg = 0x52010,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gpll1",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_lucid_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll gcc_gpll10 = अणु
	.offset = 0x1e000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_LUCID],
	.clkr = अणु
		.enable_reg = 0x52010,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gpll10",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_lucid_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll gcc_gpll4 = अणु
	.offset = 0x76000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_LUCID],
	.clkr = अणु
		.enable_reg = 0x52010,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gpll4",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_lucid_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll gcc_gpll9 = अणु
	.offset = 0x1c000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_LUCID],
	.clkr = अणु
		.enable_reg = 0x52010,
		.enable_mask = BIT(8),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gpll9",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_lucid_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mss_gpll0_मुख्य_भाग_clk_src = अणु
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(17),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_gpll0_main_div_clk_src",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_gpll0_out_even.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_0[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GCC_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_GCC_GPLL0_OUT_EVEN, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_0[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &gcc_gpll0.clkr.hw पूर्ण,
	अणु .hw = &gcc_gpll0_out_even.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_0_ao[] = अणु
	अणु .fw_name = "bi_tcxo_ao" पूर्ण,
	अणु .hw = &gcc_gpll0.clkr.hw पूर्ण,
	अणु .hw = &gcc_gpll0_out_even.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_1[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GCC_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_GCC_GPLL0_OUT_ODD, 3 पूर्ण,
	अणु P_GCC_GPLL0_OUT_EVEN, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_1[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &gcc_gpll0.clkr.hw पूर्ण,
	अणु .hw = &gcc_gpll0_out_odd.clkr.hw पूर्ण,
	अणु .hw = &gcc_gpll0_out_even.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_2[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_SLEEP_CLK, 5 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_2[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .fw_name = "sleep_clk" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_3[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_3[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_4[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GCC_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_GCC_GPLL0_OUT_ODD, 3 पूर्ण,
	अणु P_SLEEP_CLK, 5 पूर्ण,
	अणु P_GCC_GPLL0_OUT_EVEN, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_4[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &gcc_gpll0.clkr.hw पूर्ण,
	अणु .hw = &gcc_gpll0_out_odd.clkr.hw पूर्ण,
	अणु .fw_name = "sleep_clk" पूर्ण,
	अणु .hw = &gcc_gpll0_out_even.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_5[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GCC_GPLL0_OUT_EVEN, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_5[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &gcc_gpll0_out_even.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_6[] = अणु
	अणु P_PCIE_0_PIPE_CLK, 0 पूर्ण,
	अणु P_BI_TCXO, 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_6[] = अणु
	अणु .fw_name = "pcie_0_pipe_clk", .name = "pcie_0_pipe_clk" पूर्ण,
	अणु .fw_name = "bi_tcxo" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_7[] = अणु
	अणु P_PCIE_1_PIPE_CLK, 0 पूर्ण,
	अणु P_BI_TCXO, 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_7[] = अणु
	अणु .fw_name = "pcie_1_pipe_clk", .name = "pcie_1_pipe_clk" पूर्ण,
	अणु .fw_name = "bi_tcxo" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_8[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GCC_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_GCC_GPLL0_OUT_ODD, 3 पूर्ण,
	अणु P_GCC_GPLL10_OUT_MAIN, 5 पूर्ण,
	अणु P_GCC_GPLL0_OUT_EVEN, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_8[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &gcc_gpll0.clkr.hw पूर्ण,
	अणु .hw = &gcc_gpll0_out_odd.clkr.hw पूर्ण,
	अणु .hw = &gcc_gpll10.clkr.hw पूर्ण,
	अणु .hw = &gcc_gpll0_out_even.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_9[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GCC_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_GCC_GPLL9_OUT_MAIN, 2 पूर्ण,
	अणु P_GCC_GPLL0_OUT_ODD, 3 पूर्ण,
	अणु P_GCC_GPLL4_OUT_MAIN, 5 पूर्ण,
	अणु P_GCC_GPLL0_OUT_EVEN, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_9[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &gcc_gpll0.clkr.hw पूर्ण,
	अणु .hw = &gcc_gpll9.clkr.hw पूर्ण,
	अणु .hw = &gcc_gpll0_out_odd.clkr.hw पूर्ण,
	अणु .hw = &gcc_gpll4.clkr.hw पूर्ण,
	अणु .hw = &gcc_gpll0_out_even.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_10[] = अणु
	अणु P_UFS_PHY_RX_SYMBOL_0_CLK, 0 पूर्ण,
	अणु P_BI_TCXO, 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_10[] = अणु
	अणु .fw_name = "ufs_phy_rx_symbol_0_clk" पूर्ण,
	अणु .fw_name = "bi_tcxo" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_11[] = अणु
	अणु P_UFS_PHY_RX_SYMBOL_1_CLK, 0 पूर्ण,
	अणु P_BI_TCXO, 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_11[] = अणु
	अणु .fw_name = "ufs_phy_rx_symbol_1_clk" पूर्ण,
	अणु .fw_name = "bi_tcxo" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_12[] = अणु
	अणु P_UFS_PHY_TX_SYMBOL_0_CLK, 0 पूर्ण,
	अणु P_BI_TCXO, 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_12[] = अणु
	अणु .fw_name = "ufs_phy_tx_symbol_0_clk" पूर्ण,
	अणु .fw_name = "bi_tcxo" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_13[] = अणु
	अणु P_USB3_PHY_WRAPPER_GCC_USB30_PIPE_CLK, 0 पूर्ण,
	अणु P_BI_TCXO, 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_13[] = अणु
	अणु .fw_name = "usb3_phy_wrapper_gcc_usb30_pipe_clk" पूर्ण,
	अणु .fw_name = "bi_tcxo" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_14[] = अणु
	अणु P_USB3_PHY_WRAPPER_GCC_USB30_PIPE_CLK, 0 पूर्ण,
	अणु P_BI_TCXO, 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_14[] = अणु
	अणु .fw_name = "usb3_phy_wrapper_gcc_usb30_pipe_clk" पूर्ण,
	अणु .fw_name = "bi_tcxo" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_15[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GCC_MSS_GPLL0_MAIN_DIV_CLK, 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_15[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &gcc_mss_gpll0_मुख्य_भाग_clk_src.clkr.hw पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_mux gcc_pcie_0_pipe_clk_src = अणु
	.reg = 0x6b054,
	.shअगरt = 0,
	.width = 2,
	.parent_map = gcc_parent_map_6,
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_pipe_clk_src",
			.parent_data = gcc_parent_data_6,
			.num_parents = ARRAY_SIZE(gcc_parent_data_6),
			.ops = &clk_regmap_mux_बंदst_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_mux gcc_pcie_1_pipe_clk_src = अणु
	.reg = 0x8d054,
	.shअगरt = 0,
	.width = 2,
	.parent_map = gcc_parent_map_7,
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_1_pipe_clk_src",
			.parent_data = gcc_parent_data_7,
			.num_parents = ARRAY_SIZE(gcc_parent_data_7),
			.ops = &clk_regmap_mux_बंदst_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_mux gcc_ufs_phy_rx_symbol_0_clk_src = अणु
	.reg = 0x77058,
	.shअगरt = 0,
	.width = 2,
	.parent_map = gcc_parent_map_10,
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_rx_symbol_0_clk_src",
			.parent_data = gcc_parent_data_10,
			.num_parents = ARRAY_SIZE(gcc_parent_data_10),
			.ops = &clk_regmap_mux_बंदst_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_mux gcc_ufs_phy_rx_symbol_1_clk_src = अणु
	.reg = 0x770c8,
	.shअगरt = 0,
	.width = 2,
	.parent_map = gcc_parent_map_11,
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_rx_symbol_1_clk_src",
			.parent_data = gcc_parent_data_11,
			.num_parents = ARRAY_SIZE(gcc_parent_data_11),
			.ops = &clk_regmap_mux_बंदst_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_mux gcc_ufs_phy_tx_symbol_0_clk_src = अणु
	.reg = 0x77048,
	.shअगरt = 0,
	.width = 2,
	.parent_map = gcc_parent_map_12,
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_tx_symbol_0_clk_src",
			.parent_data = gcc_parent_data_12,
			.num_parents = ARRAY_SIZE(gcc_parent_data_12),
			.ops = &clk_regmap_mux_बंदst_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_mux gcc_usb3_prim_phy_pipe_clk_src = अणु
	.reg = 0xf060,
	.shअगरt = 0,
	.width = 2,
	.parent_map = gcc_parent_map_13,
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_prim_phy_pipe_clk_src",
			.parent_data = gcc_parent_data_13,
			.num_parents = ARRAY_SIZE(gcc_parent_data_13),
			.ops = &clk_regmap_mux_बंदst_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_mux gcc_usb3_sec_phy_pipe_clk_src = अणु
	.reg = 0x9e060,
	.shअगरt = 0,
	.width = 2,
	.parent_map = gcc_parent_map_14,
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_sec_phy_pipe_clk_src",
			.parent_data = gcc_parent_data_14,
			.num_parents = ARRAY_SIZE(gcc_parent_data_14),
			.ops = &clk_regmap_mux_बंदst_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा freq_tbl ftbl_gcc_cpuss_ahb_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_cpuss_ahb_clk_src = अणु
	.cmd_rcgr = 0x4800c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_cpuss_ahb_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_cpuss_ahb_clk_src",
		.parent_data = gcc_parent_data_0_ao,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0_ao),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_gp1_clk_src[] = अणु
	F(50000000, P_GCC_GPLL0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GCC_GPLL0_OUT_EVEN, 3, 0, 0),
	F(200000000, P_GCC_GPLL0_OUT_ODD, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_gp1_clk_src = अणु
	.cmd_rcgr = 0x64004,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_4,
	.freq_tbl = ftbl_gcc_gp1_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_gp1_clk_src",
		.parent_data = gcc_parent_data_4,
		.num_parents = ARRAY_SIZE(gcc_parent_data_4),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_gp2_clk_src = अणु
	.cmd_rcgr = 0x65004,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_4,
	.freq_tbl = ftbl_gcc_gp1_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_gp2_clk_src",
		.parent_data = gcc_parent_data_4,
		.num_parents = ARRAY_SIZE(gcc_parent_data_4),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_gp3_clk_src = अणु
	.cmd_rcgr = 0x66004,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_4,
	.freq_tbl = ftbl_gcc_gp1_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_gp3_clk_src",
		.parent_data = gcc_parent_data_4,
		.num_parents = ARRAY_SIZE(gcc_parent_data_4),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_pcie_0_aux_clk_src[] = अणु
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_pcie_0_aux_clk_src = अणु
	.cmd_rcgr = 0x6b058,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_2,
	.freq_tbl = ftbl_gcc_pcie_0_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_pcie_0_aux_clk_src",
		.parent_data = gcc_parent_data_2,
		.num_parents = ARRAY_SIZE(gcc_parent_data_2),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_pcie_0_phy_rchng_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_GCC_GPLL0_OUT_EVEN, 3, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_pcie_0_phy_rchng_clk_src = अणु
	.cmd_rcgr = 0x6b03c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_pcie_0_phy_rchng_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_pcie_0_phy_rchng_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_pcie_1_aux_clk_src = अणु
	.cmd_rcgr = 0x8d058,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_2,
	.freq_tbl = ftbl_gcc_pcie_0_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_pcie_1_aux_clk_src",
		.parent_data = gcc_parent_data_2,
		.num_parents = ARRAY_SIZE(gcc_parent_data_2),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_pcie_1_phy_rchng_clk_src = अणु
	.cmd_rcgr = 0x8d03c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_pcie_0_phy_rchng_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_pcie_1_phy_rchng_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_pdm2_clk_src[] = अणु
	F(60000000, P_GCC_GPLL0_OUT_EVEN, 5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_pdm2_clk_src = अणु
	.cmd_rcgr = 0x33010,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_pdm2_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_pdm2_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_qspi_core_clk_src[] = अणु
	F(100000000, P_GCC_GPLL0_OUT_MAIN, 6, 0, 0),
	F(150000000, P_GCC_GPLL0_OUT_MAIN, 4, 0, 0),
	F(200000000, P_GCC_GPLL0_OUT_MAIN, 3, 0, 0),
	F(300000000, P_GCC_GPLL0_OUT_MAIN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qspi_core_clk_src = अणु
	.cmd_rcgr = 0x4b00c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qspi_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qspi_core_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_न्यूनमान_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_qupv3_wrap0_s0_clk_src[] = अणु
	F(7372800, P_GCC_GPLL0_OUT_EVEN, 1, 384, 15625),
	F(14745600, P_GCC_GPLL0_OUT_EVEN, 1, 768, 15625),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(29491200, P_GCC_GPLL0_OUT_EVEN, 1, 1536, 15625),
	F(32000000, P_GCC_GPLL0_OUT_EVEN, 1, 8, 75),
	F(48000000, P_GCC_GPLL0_OUT_EVEN, 1, 4, 25),
	F(64000000, P_GCC_GPLL0_OUT_EVEN, 1, 16, 75),
	F(75000000, P_GCC_GPLL0_OUT_EVEN, 4, 0, 0),
	F(80000000, P_GCC_GPLL0_OUT_EVEN, 1, 4, 15),
	F(96000000, P_GCC_GPLL0_OUT_EVEN, 1, 8, 25),
	F(100000000, P_GCC_GPLL0_OUT_MAIN, 6, 0, 0),
	F(102400000, P_GCC_GPLL0_OUT_EVEN, 1, 128, 375),
	F(112000000, P_GCC_GPLL0_OUT_EVEN, 1, 28, 75),
	F(117964800, P_GCC_GPLL0_OUT_EVEN, 1, 6144, 15625),
	F(120000000, P_GCC_GPLL0_OUT_EVEN, 2.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s0_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s0_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s0_clk_src = अणु
	.cmd_rcgr = 0x17010,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s0_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s1_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s1_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s1_clk_src = अणु
	.cmd_rcgr = 0x17140,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s1_clk_src_init,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_qupv3_wrap0_s2_clk_src[] = अणु
	F(7372800, P_GCC_GPLL0_OUT_EVEN, 1, 384, 15625),
	F(14745600, P_GCC_GPLL0_OUT_EVEN, 1, 768, 15625),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(29491200, P_GCC_GPLL0_OUT_EVEN, 1, 1536, 15625),
	F(32000000, P_GCC_GPLL0_OUT_EVEN, 1, 8, 75),
	F(48000000, P_GCC_GPLL0_OUT_EVEN, 1, 4, 25),
	F(64000000, P_GCC_GPLL0_OUT_EVEN, 1, 16, 75),
	F(75000000, P_GCC_GPLL0_OUT_EVEN, 4, 0, 0),
	F(80000000, P_GCC_GPLL0_OUT_EVEN, 1, 4, 15),
	F(96000000, P_GCC_GPLL0_OUT_EVEN, 1, 8, 25),
	F(100000000, P_GCC_GPLL0_OUT_MAIN, 6, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s2_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s2_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s2_clk_src = अणु
	.cmd_rcgr = 0x17270,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s2_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s2_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s3_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s3_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s3_clk_src = अणु
	.cmd_rcgr = 0x173a0,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s2_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s3_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s4_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s4_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s4_clk_src = अणु
	.cmd_rcgr = 0x174d0,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s2_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s4_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s5_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s5_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s5_clk_src = अणु
	.cmd_rcgr = 0x17600,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s2_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s5_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s6_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s6_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s6_clk_src = अणु
	.cmd_rcgr = 0x17730,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s2_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s6_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s7_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s7_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s7_clk_src = अणु
	.cmd_rcgr = 0x17860,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s2_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s7_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap1_s0_clk_src_init = अणु
	.name = "gcc_qupv3_wrap1_s0_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s0_clk_src = अणु
	.cmd_rcgr = 0x18010,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap1_s0_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap1_s1_clk_src_init = अणु
	.name = "gcc_qupv3_wrap1_s1_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s1_clk_src = अणु
	.cmd_rcgr = 0x18140,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap1_s1_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap1_s2_clk_src_init = अणु
	.name = "gcc_qupv3_wrap1_s2_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s2_clk_src = अणु
	.cmd_rcgr = 0x18270,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s2_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap1_s2_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap1_s3_clk_src_init = अणु
	.name = "gcc_qupv3_wrap1_s3_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s3_clk_src = अणु
	.cmd_rcgr = 0x183a0,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s2_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap1_s3_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap1_s4_clk_src_init = अणु
	.name = "gcc_qupv3_wrap1_s4_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s4_clk_src = अणु
	.cmd_rcgr = 0x184d0,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s2_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap1_s4_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap1_s5_clk_src_init = अणु
	.name = "gcc_qupv3_wrap1_s5_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s5_clk_src = अणु
	.cmd_rcgr = 0x18600,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s2_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap1_s5_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap1_s6_clk_src_init = अणु
	.name = "gcc_qupv3_wrap1_s6_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s6_clk_src = अणु
	.cmd_rcgr = 0x18730,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s2_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap1_s6_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap1_s7_clk_src_init = अणु
	.name = "gcc_qupv3_wrap1_s7_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s7_clk_src = अणु
	.cmd_rcgr = 0x18860,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s2_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap1_s7_clk_src_init,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sdcc1_apps_clk_src[] = अणु
	F(144000, P_BI_TCXO, 16, 3, 25),
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(20000000, P_GCC_GPLL0_OUT_EVEN, 5, 1, 3),
	F(25000000, P_GCC_GPLL0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GCC_GPLL0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GCC_GPLL0_OUT_EVEN, 3, 0, 0),
	F(192000000, P_GCC_GPLL10_OUT_MAIN, 2, 0, 0),
	F(384000000, P_GCC_GPLL10_OUT_MAIN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_sdcc1_apps_clk_src = अणु
	.cmd_rcgr = 0x7500c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_8,
	.freq_tbl = ftbl_gcc_sdcc1_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_sdcc1_apps_clk_src",
		.parent_data = gcc_parent_data_8,
		.num_parents = ARRAY_SIZE(gcc_parent_data_8),
		.ops = &clk_rcg2_न्यूनमान_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sdcc1_ice_core_clk_src[] = अणु
	F(100000000, P_GCC_GPLL0_OUT_EVEN, 3, 0, 0),
	F(150000000, P_GCC_GPLL0_OUT_EVEN, 2, 0, 0),
	F(300000000, P_GCC_GPLL0_OUT_EVEN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_sdcc1_ice_core_clk_src = अणु
	.cmd_rcgr = 0x7502c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_sdcc1_ice_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_sdcc1_ice_core_clk_src",
		.parent_data = gcc_parent_data_1,
		.num_parents = ARRAY_SIZE(gcc_parent_data_1),
		.ops = &clk_rcg2_न्यूनमान_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sdcc2_apps_clk_src[] = अणु
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(25000000, P_GCC_GPLL0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GCC_GPLL0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GCC_GPLL0_OUT_EVEN, 3, 0, 0),
	F(202000000, P_GCC_GPLL9_OUT_MAIN, 4, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_sdcc2_apps_clk_src = अणु
	.cmd_rcgr = 0x1400c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_9,
	.freq_tbl = ftbl_gcc_sdcc2_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_sdcc2_apps_clk_src",
		.parent_data = gcc_parent_data_9,
		.num_parents = ARRAY_SIZE(gcc_parent_data_9),
		.flags = CLK_OPS_PARENT_ENABLE,
		.ops = &clk_rcg2_न्यूनमान_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sdcc4_apps_clk_src[] = अणु
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(25000000, P_GCC_GPLL0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GCC_GPLL0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GCC_GPLL0_OUT_EVEN, 3, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_sdcc4_apps_clk_src = अणु
	.cmd_rcgr = 0x1600c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_sdcc4_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_sdcc4_apps_clk_src",
		.parent_data = gcc_parent_data_1,
		.num_parents = ARRAY_SIZE(gcc_parent_data_1),
		.ops = &clk_rcg2_न्यूनमान_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ufs_phy_axi_clk_src[] = अणु
	F(25000000, P_GCC_GPLL0_OUT_EVEN, 12, 0, 0),
	F(75000000, P_GCC_GPLL0_OUT_EVEN, 4, 0, 0),
	F(150000000, P_GCC_GPLL0_OUT_EVEN, 2, 0, 0),
	F(300000000, P_GCC_GPLL0_OUT_EVEN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_phy_axi_clk_src = अणु
	.cmd_rcgr = 0x77024,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_ufs_phy_axi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_phy_axi_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ufs_phy_ice_core_clk_src[] = अणु
	F(75000000, P_GCC_GPLL0_OUT_EVEN, 4, 0, 0),
	F(150000000, P_GCC_GPLL0_OUT_EVEN, 2, 0, 0),
	F(300000000, P_GCC_GPLL0_OUT_EVEN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_phy_ice_core_clk_src = अणु
	.cmd_rcgr = 0x7706c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_ufs_phy_ice_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_phy_ice_core_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_phy_phy_aux_clk_src = अणु
	.cmd_rcgr = 0x770a0,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_3,
	.freq_tbl = ftbl_gcc_pcie_0_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_phy_phy_aux_clk_src",
		.parent_data = gcc_parent_data_3,
		.num_parents = ARRAY_SIZE(gcc_parent_data_3),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_phy_unipro_core_clk_src = अणु
	.cmd_rcgr = 0x77084,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_ufs_phy_ice_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_phy_unipro_core_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb30_prim_master_clk_src[] = अणु
	F(66666667, P_GCC_GPLL0_OUT_EVEN, 4.5, 0, 0),
	F(133333333, P_GCC_GPLL0_OUT_MAIN, 4.5, 0, 0),
	F(200000000, P_GCC_GPLL0_OUT_ODD, 1, 0, 0),
	F(240000000, P_GCC_GPLL0_OUT_MAIN, 2.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb30_prim_master_clk_src = अणु
	.cmd_rcgr = 0xf020,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_usb30_prim_master_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb30_prim_master_clk_src",
		.parent_data = gcc_parent_data_1,
		.num_parents = ARRAY_SIZE(gcc_parent_data_1),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb30_prim_mock_uपंचांगi_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb30_prim_mock_uपंचांगi_clk_src = अणु
	.cmd_rcgr = 0xf038,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_3,
	.freq_tbl = ftbl_gcc_usb30_prim_mock_uपंचांगi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb30_prim_mock_utmi_clk_src",
		.parent_data = gcc_parent_data_3,
		.num_parents = ARRAY_SIZE(gcc_parent_data_3),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb30_sec_master_clk_src[] = अणु
	F(60000000, P_GCC_GPLL0_OUT_EVEN, 5, 0, 0),
	F(120000000, P_GCC_GPLL0_OUT_EVEN, 2.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb30_sec_master_clk_src = अणु
	.cmd_rcgr = 0x9e020,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_5,
	.freq_tbl = ftbl_gcc_usb30_sec_master_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb30_sec_master_clk_src",
		.parent_data = gcc_parent_data_5,
		.num_parents = ARRAY_SIZE(gcc_parent_data_5),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb30_sec_mock_uपंचांगi_clk_src = अणु
	.cmd_rcgr = 0x9e038,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_3,
	.freq_tbl = ftbl_gcc_usb30_prim_mock_uपंचांगi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb30_sec_mock_utmi_clk_src",
		.parent_data = gcc_parent_data_3,
		.num_parents = ARRAY_SIZE(gcc_parent_data_3),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb3_prim_phy_aux_clk_src = अणु
	.cmd_rcgr = 0xf064,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_2,
	.freq_tbl = ftbl_gcc_usb30_prim_mock_uपंचांगi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb3_prim_phy_aux_clk_src",
		.parent_data = gcc_parent_data_2,
		.num_parents = ARRAY_SIZE(gcc_parent_data_2),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb3_sec_phy_aux_clk_src = अणु
	.cmd_rcgr = 0x9e064,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_2,
	.freq_tbl = ftbl_gcc_usb30_prim_mock_uपंचांगi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb3_sec_phy_aux_clk_src",
		.parent_data = gcc_parent_data_2,
		.num_parents = ARRAY_SIZE(gcc_parent_data_2),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sec_ctrl_clk_src[] = अणु
	F(4800000, P_BI_TCXO, 4, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_sec_ctrl_clk_src = अणु
	.cmd_rcgr = 0x3d02c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_3,
	.freq_tbl = ftbl_gcc_sec_ctrl_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_sec_ctrl_clk_src",
		.parent_data = gcc_parent_data_3,
		.num_parents = ARRAY_SIZE(gcc_parent_data_3),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_भाग gcc_cpuss_ahb_postभाग_clk_src = अणु
	.reg = 0x48024,
	.shअगरt = 0,
	.width = 4,
	.clkr.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "gcc_cpuss_ahb_postdiv_clk_src",
		.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
			&gcc_cpuss_ahb_clk_src.clkr.hw,
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_regmap_भाग_ro_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_भाग gcc_usb30_prim_mock_uपंचांगi_postभाग_clk_src = अणु
	.reg = 0xf050,
	.shअगरt = 0,
	.width = 4,
	.clkr.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "gcc_usb30_prim_mock_utmi_postdiv_clk_src",
		.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
			&gcc_usb30_prim_mock_uपंचांगi_clk_src.clkr.hw,
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_regmap_भाग_ro_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_भाग gcc_usb30_sec_mock_uपंचांगi_postभाग_clk_src = अणु
	.reg = 0x9e050,
	.shअगरt = 0,
	.width = 4,
	.clkr.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "gcc_usb30_sec_mock_utmi_postdiv_clk_src",
		.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
			&gcc_usb30_sec_mock_uपंचांगi_clk_src.clkr.hw,
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_regmap_भाग_ro_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_clkref_en = अणु
	.halt_reg = 0x8c004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8c004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_clkref_en",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_edp_clkref_en = अणु
	.halt_reg = 0x8c008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8c008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_edp_clkref_en",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre_noc_pcie_0_axi_clk = अणु
	.halt_reg = 0x6b080,
	.halt_check = BRANCH_HALT_SKIP,
	.hwcg_reg = 0x6b080,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(12),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_aggre_noc_pcie_0_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre_noc_pcie_1_axi_clk = अणु
	.halt_reg = 0x8d084,
	.halt_check = BRANCH_HALT_SKIP,
	.hwcg_reg = 0x8d084,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_aggre_noc_pcie_1_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre_noc_pcie_tbu_clk = अणु
	.halt_reg = 0x90010,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x90010,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(18),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_aggre_noc_pcie_tbu_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre_noc_pcie_center_sf_axi_clk = अणु
	.halt_reg = 0x8d088,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x8d088,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(28),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_aggre_noc_pcie_center_sf_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre_ufs_phy_axi_clk = अणु
	.halt_reg = 0x770cc,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x770cc,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x770cc,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_aggre_ufs_phy_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_ufs_phy_axi_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre_usb3_prim_axi_clk = अणु
	.halt_reg = 0xf080,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0xf080,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xf080,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_aggre_usb3_prim_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_usb30_prim_master_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre_usb3_sec_axi_clk = अणु
	.halt_reg = 0x9e080,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x9e080,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x9e080,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_aggre_usb3_sec_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_usb30_sec_master_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camera_hf_axi_clk = अणु
	.halt_reg = 0x26010,
	.halt_check = BRANCH_HALT_SKIP,
	.hwcg_reg = 0x26010,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x26010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camera_hf_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camera_sf_axi_clk = अणु
	.halt_reg = 0x2601c,
	.halt_check = BRANCH_HALT_SKIP,
	.hwcg_reg = 0x2601c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x2601c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camera_sf_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_cfg_noc_usb3_prim_axi_clk = अणु
	.halt_reg = 0xf07c,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0xf07c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xf07c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_cfg_noc_usb3_prim_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_usb30_prim_master_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_cfg_noc_usb3_sec_axi_clk = अणु
	.halt_reg = 0x9e07c,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x9e07c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x9e07c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_cfg_noc_usb3_sec_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_usb30_sec_master_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* For CPUSS functionality the AHB घड़ी needs to be left enabled */
अटल काष्ठा clk_branch gcc_cpuss_ahb_clk = अणु
	.halt_reg = 0x48000,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x48000,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(21),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_cpuss_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_cpuss_ahb_postभाग_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_IS_CRITICAL | CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ddrss_gpu_axi_clk = अणु
	.halt_reg = 0x71154,
	.halt_check = BRANCH_HALT_SKIP,
	.hwcg_reg = 0x71154,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x71154,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ddrss_gpu_axi_clk",
			.ops = &clk_branch2_aon_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ddrss_pcie_sf_clk = अणु
	.halt_reg = 0x8d080,
	.halt_check = BRANCH_HALT_SKIP,
	.hwcg_reg = 0x8d080,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(19),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ddrss_pcie_sf_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_disp_gpll0_clk_src = अणु
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(7),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_disp_gpll0_clk_src",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_gpll0.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_disp_hf_axi_clk = अणु
	.halt_reg = 0x2700c,
	.halt_check = BRANCH_HALT_SKIP,
	.hwcg_reg = 0x2700c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x2700c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_disp_hf_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_disp_sf_axi_clk = अणु
	.halt_reg = 0x27014,
	.halt_check = BRANCH_HALT_SKIP,
	.hwcg_reg = 0x27014,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x27014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_disp_sf_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gp1_clk = अणु
	.halt_reg = 0x64000,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x64000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gp1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_gp1_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gp2_clk = अणु
	.halt_reg = 0x65000,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x65000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gp2_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_gp2_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gp3_clk = अणु
	.halt_reg = 0x66000,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x66000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gp3_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_gp3_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gpu_gpll0_clk_src = अणु
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(15),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gpu_gpll0_clk_src",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_gpll0.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gpu_gpll0_भाग_clk_src = अणु
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(16),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gpu_gpll0_div_clk_src",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_gpll0_out_even.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gpu_iref_en = अणु
	.halt_reg = 0x8c014,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8c014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gpu_iref_en",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gpu_memnoc_gfx_clk = अणु
	.halt_reg = 0x7100c,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x7100c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x7100c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gpu_memnoc_gfx_clk",
			.ops = &clk_branch2_aon_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gpu_snoc_dvm_gfx_clk = अणु
	.halt_reg = 0x71018,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x71018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gpu_snoc_dvm_gfx_clk",
			.ops = &clk_branch2_aon_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie0_phy_rchng_clk = अणु
	.halt_reg = 0x6b038,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(22),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie0_phy_rchng_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_pcie_0_phy_rchng_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie1_phy_rchng_clk = अणु
	.halt_reg = 0x8d038,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(23),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie1_phy_rchng_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_pcie_1_phy_rchng_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_aux_clk = अणु
	.halt_reg = 0x6b028,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(3),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_pcie_0_aux_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_cfg_ahb_clk = अणु
	.halt_reg = 0x6b024,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x6b024,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_cfg_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_mstr_axi_clk = अणु
	.halt_reg = 0x6b01c,
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_mstr_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_pipe_clk = अणु
	.halt_reg = 0x6b030,
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_pipe_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_pcie_0_pipe_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_slv_axi_clk = अणु
	.halt_reg = 0x6b014,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_slv_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_slv_q2a_axi_clk = अणु
	.halt_reg = 0x6b010,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(5),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_slv_q2a_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_aux_clk = अणु
	.halt_reg = 0x8d028,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(29),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_1_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_pcie_1_aux_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_cfg_ahb_clk = अणु
	.halt_reg = 0x8d024,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x8d024,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(28),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_1_cfg_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_mstr_axi_clk = अणु
	.halt_reg = 0x8d01c,
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(27),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_1_mstr_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_pipe_clk = अणु
	.halt_reg = 0x8d030,
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(30),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_1_pipe_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_pcie_1_pipe_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_slv_axi_clk = अणु
	.halt_reg = 0x8d014,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(26),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_1_slv_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_slv_q2a_axi_clk = अणु
	.halt_reg = 0x8d010,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(25),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_1_slv_q2a_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_throttle_core_clk = अणु
	.halt_reg = 0x90018,
	.halt_check = BRANCH_HALT_SKIP,
	.hwcg_reg = 0x90018,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(20),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_throttle_core_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pdm2_clk = अणु
	.halt_reg = 0x3300c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3300c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pdm2_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_pdm2_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pdm_ahb_clk = अणु
	.halt_reg = 0x33004,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x33004,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x33004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pdm_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pdm_xo4_clk = अणु
	.halt_reg = 0x33008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x33008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pdm_xo4_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qmip_camera_nrt_ahb_clk = अणु
	.halt_reg = 0x26008,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x26008,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x26008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qmip_camera_nrt_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qmip_camera_rt_ahb_clk = अणु
	.halt_reg = 0x2600c,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x2600c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x2600c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qmip_camera_rt_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qmip_disp_ahb_clk = अणु
	.halt_reg = 0x27008,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x27008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qmip_disp_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qmip_video_vcodec_ahb_clk = अणु
	.halt_reg = 0x28008,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x28008,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x28008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qmip_video_vcodec_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qspi_cnoc_periph_ahb_clk = अणु
	.halt_reg = 0x4b004,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x4b004,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x4b004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qspi_cnoc_periph_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qspi_core_clk = अणु
	.halt_reg = 0x4b008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x4b008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qspi_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_qspi_core_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap0_core_2x_clk = अणु
	.halt_reg = 0x23008,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap0_core_2x_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap0_core_clk = अणु
	.halt_reg = 0x23000,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(8),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap0_core_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap0_s0_clk = अणु
	.halt_reg = 0x1700c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(10),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap0_s0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_qupv3_wrap0_s0_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap0_s1_clk = अणु
	.halt_reg = 0x1713c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap0_s1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_qupv3_wrap0_s1_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap0_s2_clk = अणु
	.halt_reg = 0x1726c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(12),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap0_s2_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_qupv3_wrap0_s2_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap0_s3_clk = अणु
	.halt_reg = 0x1739c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(13),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap0_s3_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_qupv3_wrap0_s3_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap0_s4_clk = अणु
	.halt_reg = 0x174cc,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(14),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap0_s4_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_qupv3_wrap0_s4_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap0_s5_clk = अणु
	.halt_reg = 0x175fc,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(15),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap0_s5_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_qupv3_wrap0_s5_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap0_s6_clk = अणु
	.halt_reg = 0x1772c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(16),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap0_s6_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_qupv3_wrap0_s6_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap0_s7_clk = अणु
	.halt_reg = 0x1785c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(17),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap0_s7_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_qupv3_wrap0_s7_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap1_core_2x_clk = अणु
	.halt_reg = 0x23140,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(18),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap1_core_2x_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap1_core_clk = अणु
	.halt_reg = 0x23138,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(19),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap1_core_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap1_s0_clk = अणु
	.halt_reg = 0x1800c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(22),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap1_s0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_qupv3_wrap1_s0_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap1_s1_clk = अणु
	.halt_reg = 0x1813c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(23),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap1_s1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_qupv3_wrap1_s1_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap1_s2_clk = अणु
	.halt_reg = 0x1826c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(24),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap1_s2_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_qupv3_wrap1_s2_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap1_s3_clk = अणु
	.halt_reg = 0x1839c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(25),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap1_s3_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_qupv3_wrap1_s3_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap1_s4_clk = अणु
	.halt_reg = 0x184cc,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(26),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap1_s4_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_qupv3_wrap1_s4_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap1_s5_clk = अणु
	.halt_reg = 0x185fc,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(27),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap1_s5_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_qupv3_wrap1_s5_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap1_s6_clk = अणु
	.halt_reg = 0x1872c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(13),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap1_s6_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_qupv3_wrap1_s6_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap1_s7_clk = अणु
	.halt_reg = 0x1885c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(14),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap1_s7_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_qupv3_wrap1_s7_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap_0_m_ahb_clk = अणु
	.halt_reg = 0x17004,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x17004,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(6),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap_0_m_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap_0_s_ahb_clk = अणु
	.halt_reg = 0x17008,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x17008,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(7),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap_0_s_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap_1_m_ahb_clk = अणु
	.halt_reg = 0x18004,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x18004,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(20),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap_1_m_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap_1_s_ahb_clk = अणु
	.halt_reg = 0x18008,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x18008,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52008,
		.enable_mask = BIT(21),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap_1_s_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc1_ahb_clk = अणु
	.halt_reg = 0x75004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x75004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sdcc1_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc1_apps_clk = अणु
	.halt_reg = 0x75008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x75008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sdcc1_apps_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_sdcc1_apps_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc1_ice_core_clk = अणु
	.halt_reg = 0x75024,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x75024,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x75024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sdcc1_ice_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_sdcc1_ice_core_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc2_ahb_clk = अणु
	.halt_reg = 0x14008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x14008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sdcc2_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc2_apps_clk = अणु
	.halt_reg = 0x14004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x14004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sdcc2_apps_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_sdcc2_apps_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc4_ahb_clk = अणु
	.halt_reg = 0x16008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x16008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sdcc4_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc4_apps_clk = अणु
	.halt_reg = 0x16004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x16004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sdcc4_apps_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_sdcc4_apps_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* For CPUSS functionality the AHB घड़ी needs to be left enabled */
अटल काष्ठा clk_branch gcc_sys_noc_cpuss_ahb_clk = अणु
	.halt_reg = 0x48178,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x48178,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sys_noc_cpuss_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_cpuss_ahb_postभाग_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_IS_CRITICAL | CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_throttle_pcie_ahb_clk = अणु
	.halt_reg = 0x9001c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9001c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_throttle_pcie_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_titan_nrt_throttle_core_clk = अणु
	.halt_reg = 0x26024,
	.halt_check = BRANCH_HALT_SKIP,
	.hwcg_reg = 0x26024,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x26024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_titan_nrt_throttle_core_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_titan_rt_throttle_core_clk = अणु
	.halt_reg = 0x26018,
	.halt_check = BRANCH_HALT_SKIP,
	.hwcg_reg = 0x26018,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x26018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_titan_rt_throttle_core_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_1_clkref_en = अणु
	.halt_reg = 0x8c000,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8c000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_1_clkref_en",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_ahb_clk = अणु
	.halt_reg = 0x77018,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x77018,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x77018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_axi_clk = अणु
	.halt_reg = 0x77010,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x77010,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x77010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_ufs_phy_axi_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_ice_core_clk = अणु
	.halt_reg = 0x77064,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x77064,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x77064,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_ice_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_ufs_phy_ice_core_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_phy_aux_clk = अणु
	.halt_reg = 0x7709c,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x7709c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x7709c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_phy_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_ufs_phy_phy_aux_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_rx_symbol_0_clk = अणु
	.halt_reg = 0x77020,
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x77020,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_rx_symbol_0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_ufs_phy_rx_symbol_0_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_rx_symbol_1_clk = अणु
	.halt_reg = 0x770b8,
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x770b8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_rx_symbol_1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_ufs_phy_rx_symbol_1_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_tx_symbol_0_clk = अणु
	.halt_reg = 0x7701c,
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x7701c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_tx_symbol_0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_ufs_phy_tx_symbol_0_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_unipro_core_clk = अणु
	.halt_reg = 0x7705c,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x7705c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x7705c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_unipro_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_ufs_phy_unipro_core_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_prim_master_clk = अणु
	.halt_reg = 0xf010,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_prim_master_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_usb30_prim_master_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_prim_mock_uपंचांगi_clk = अणु
	.halt_reg = 0xf01c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf01c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_prim_mock_utmi_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw =
					&gcc_usb30_prim_mock_uपंचांगi_postभाग_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_prim_sleep_clk = अणु
	.halt_reg = 0xf018,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_prim_sleep_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_sec_master_clk = अणु
	.halt_reg = 0x9e010,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9e010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_sec_master_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_usb30_sec_master_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_sec_mock_uपंचांगi_clk = अणु
	.halt_reg = 0x9e01c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9e01c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_sec_mock_utmi_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw =
					&gcc_usb30_sec_mock_uपंचांगi_postभाग_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_sec_sleep_clk = अणु
	.halt_reg = 0x9e018,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9e018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_sec_sleep_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_prim_phy_aux_clk = अणु
	.halt_reg = 0xf054,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf054,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_prim_phy_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_usb3_prim_phy_aux_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_prim_phy_com_aux_clk = अणु
	.halt_reg = 0xf058,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf058,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_prim_phy_com_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_usb3_prim_phy_aux_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_prim_phy_pipe_clk = अणु
	.halt_reg = 0xf05c,
	.halt_check = BRANCH_HALT_DELAY,
	.hwcg_reg = 0xf05c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xf05c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_prim_phy_pipe_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_usb3_prim_phy_pipe_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_cfg_noc_lpass_clk = अणु
	.halt_reg = 0x47020,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x47020,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_cfg_noc_lpass_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;
अटल काष्ठा clk_branch gcc_mss_cfg_ahb_clk = अणु
	.halt_reg = 0x8a000,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8a000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_cfg_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mss_offline_axi_clk = अणु
	.halt_reg = 0x8a004,
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x8a004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_offline_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mss_snoc_axi_clk = अणु
	.halt_reg = 0x8a154,
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x8a154,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_snoc_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mss_q6_memnoc_axi_clk = अणु
	.halt_reg = 0x8a158,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8a158,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_q6_memnoc_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_mux gcc_mss_q6ss_boot_clk_src = अणु
	.reg = 0x8a2a4,
	.shअगरt = 0,
	.width = 1,
	.parent_map = gcc_parent_map_15,
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_q6ss_boot_clk_src",
			.parent_data = gcc_parent_data_15,
			.num_parents = ARRAY_SIZE(gcc_parent_data_15),
			.ops = &clk_regmap_mux_बंदst_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_sec_phy_aux_clk = अणु
	.halt_reg = 0x9e054,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9e054,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_sec_phy_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_usb3_sec_phy_aux_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_sec_phy_com_aux_clk = अणु
	.halt_reg = 0x9e058,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9e058,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_sec_phy_com_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_usb3_sec_phy_aux_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_sec_phy_pipe_clk = अणु
	.halt_reg = 0x9e05c,
	.halt_check = BRANCH_HALT_SKIP,
	.hwcg_reg = 0x9e05c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x9e05c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_sec_phy_pipe_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_usb3_sec_phy_pipe_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_video_axi0_clk = अणु
	.halt_reg = 0x2800c,
	.halt_check = BRANCH_HALT_SKIP,
	.hwcg_reg = 0x2800c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x2800c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_video_axi0_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_video_mvp_throttle_core_clk = अणु
	.halt_reg = 0x28010,
	.halt_check = BRANCH_HALT_SKIP,
	.hwcg_reg = 0x28010,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x28010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_video_mvp_throttle_core_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_wpss_ahb_clk = अणु
	.halt_reg = 0x9d154,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9d154,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_wpss_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_wpss_ahb_bdg_mst_clk = अणु
	.halt_reg = 0x9d158,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9d158,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_wpss_ahb_bdg_mst_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_wpss_rscp_clk = अणु
	.halt_reg = 0x9d16c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9d16c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_wpss_rscp_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gdsc gcc_pcie_0_gdsc = अणु
	.gdscr = 0x6b004,
	.pd = अणु
		.name = "gcc_pcie_0_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc gcc_pcie_1_gdsc = अणु
	.gdscr = 0x8d004,
	.pd = अणु
		.name = "gcc_pcie_1_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc gcc_ufs_phy_gdsc = अणु
	.gdscr = 0x77004,
	.pd = अणु
		.name = "gcc_ufs_phy_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc gcc_usb30_prim_gdsc = अणु
	.gdscr = 0xf004,
	.pd = अणु
		.name = "gcc_usb30_prim_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc gcc_usb30_sec_gdsc = अणु
	.gdscr = 0x9e004,
	.pd = अणु
		.name = "gcc_usb30_sec_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc hlos1_vote_mmnoc_mmu_tbu_hf0_gdsc = अणु
	.gdscr = 0x7d050,
	.pd = अणु
		.name = "hlos1_vote_mmnoc_mmu_tbu_hf0_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc hlos1_vote_mmnoc_mmu_tbu_hf1_gdsc = अणु
	.gdscr = 0x7d058,
	.pd = अणु
		.name = "hlos1_vote_mmnoc_mmu_tbu_hf1_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc hlos1_vote_mmnoc_mmu_tbu_sf0_gdsc = अणु
	.gdscr = 0x7d054,
	.pd = अणु
		.name = "hlos1_vote_mmnoc_mmu_tbu_sf0_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc hlos1_vote_turing_mmu_tbu0_gdsc = अणु
	.gdscr = 0x7d05c,
	.pd = अणु
		.name = "hlos1_vote_turing_mmu_tbu0_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc hlos1_vote_turing_mmu_tbu1_gdsc = अणु
	.gdscr = 0x7d060,
	.pd = अणु
		.name = "hlos1_vote_turing_mmu_tbu1_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा clk_regmap *gcc_sc7280_घड़ीs[] = अणु
	[GCC_AGGRE_NOC_PCIE_0_AXI_CLK] = &gcc_aggre_noc_pcie_0_axi_clk.clkr,
	[GCC_AGGRE_NOC_PCIE_1_AXI_CLK] = &gcc_aggre_noc_pcie_1_axi_clk.clkr,
	[GCC_AGGRE_UFS_PHY_AXI_CLK] = &gcc_aggre_ufs_phy_axi_clk.clkr,
	[GCC_AGGRE_USB3_PRIM_AXI_CLK] = &gcc_aggre_usb3_prim_axi_clk.clkr,
	[GCC_AGGRE_USB3_SEC_AXI_CLK] = &gcc_aggre_usb3_sec_axi_clk.clkr,
	[GCC_CAMERA_HF_AXI_CLK] = &gcc_camera_hf_axi_clk.clkr,
	[GCC_CAMERA_SF_AXI_CLK] = &gcc_camera_sf_axi_clk.clkr,
	[GCC_CFG_NOC_USB3_PRIM_AXI_CLK] = &gcc_cfg_noc_usb3_prim_axi_clk.clkr,
	[GCC_CFG_NOC_USB3_SEC_AXI_CLK] = &gcc_cfg_noc_usb3_sec_axi_clk.clkr,
	[GCC_CPUSS_AHB_CLK] = &gcc_cpuss_ahb_clk.clkr,
	[GCC_CPUSS_AHB_CLK_SRC] = &gcc_cpuss_ahb_clk_src.clkr,
	[GCC_CPUSS_AHB_POSTDIV_CLK_SRC] = &gcc_cpuss_ahb_postभाग_clk_src.clkr,
	[GCC_DDRSS_GPU_AXI_CLK] = &gcc_ddrss_gpu_axi_clk.clkr,
	[GCC_DDRSS_PCIE_SF_CLK] = &gcc_ddrss_pcie_sf_clk.clkr,
	[GCC_DISP_GPLL0_CLK_SRC] = &gcc_disp_gpll0_clk_src.clkr,
	[GCC_DISP_HF_AXI_CLK] = &gcc_disp_hf_axi_clk.clkr,
	[GCC_DISP_SF_AXI_CLK] = &gcc_disp_sf_axi_clk.clkr,
	[GCC_GP1_CLK] = &gcc_gp1_clk.clkr,
	[GCC_GP1_CLK_SRC] = &gcc_gp1_clk_src.clkr,
	[GCC_GP2_CLK] = &gcc_gp2_clk.clkr,
	[GCC_GP2_CLK_SRC] = &gcc_gp2_clk_src.clkr,
	[GCC_GP3_CLK] = &gcc_gp3_clk.clkr,
	[GCC_GP3_CLK_SRC] = &gcc_gp3_clk_src.clkr,
	[GCC_GPLL0] = &gcc_gpll0.clkr,
	[GCC_GPLL0_OUT_EVEN] = &gcc_gpll0_out_even.clkr,
	[GCC_GPLL0_OUT_ODD] = &gcc_gpll0_out_odd.clkr,
	[GCC_GPLL1] = &gcc_gpll1.clkr,
	[GCC_GPLL10] = &gcc_gpll10.clkr,
	[GCC_GPLL4] = &gcc_gpll4.clkr,
	[GCC_GPLL9] = &gcc_gpll9.clkr,
	[GCC_GPU_GPLL0_CLK_SRC] = &gcc_gpu_gpll0_clk_src.clkr,
	[GCC_GPU_GPLL0_DIV_CLK_SRC] = &gcc_gpu_gpll0_भाग_clk_src.clkr,
	[GCC_GPU_IREF_EN] = &gcc_gpu_iref_en.clkr,
	[GCC_GPU_MEMNOC_GFX_CLK] = &gcc_gpu_memnoc_gfx_clk.clkr,
	[GCC_GPU_SNOC_DVM_GFX_CLK] = &gcc_gpu_snoc_dvm_gfx_clk.clkr,
	[GCC_PCIE0_PHY_RCHNG_CLK] = &gcc_pcie0_phy_rchng_clk.clkr,
	[GCC_PCIE1_PHY_RCHNG_CLK] = &gcc_pcie1_phy_rchng_clk.clkr,
	[GCC_PCIE_0_AUX_CLK] = &gcc_pcie_0_aux_clk.clkr,
	[GCC_PCIE_0_AUX_CLK_SRC] = &gcc_pcie_0_aux_clk_src.clkr,
	[GCC_PCIE_0_CFG_AHB_CLK] = &gcc_pcie_0_cfg_ahb_clk.clkr,
	[GCC_PCIE_0_MSTR_AXI_CLK] = &gcc_pcie_0_mstr_axi_clk.clkr,
	[GCC_PCIE_0_PHY_RCHNG_CLK_SRC] = &gcc_pcie_0_phy_rchng_clk_src.clkr,
	[GCC_PCIE_0_PIPE_CLK] = &gcc_pcie_0_pipe_clk.clkr,
	[GCC_PCIE_0_PIPE_CLK_SRC] = &gcc_pcie_0_pipe_clk_src.clkr,
	[GCC_PCIE_0_SLV_AXI_CLK] = &gcc_pcie_0_slv_axi_clk.clkr,
	[GCC_PCIE_0_SLV_Q2A_AXI_CLK] = &gcc_pcie_0_slv_q2a_axi_clk.clkr,
	[GCC_PCIE_1_AUX_CLK] = &gcc_pcie_1_aux_clk.clkr,
	[GCC_PCIE_1_AUX_CLK_SRC] = &gcc_pcie_1_aux_clk_src.clkr,
	[GCC_PCIE_1_CFG_AHB_CLK] = &gcc_pcie_1_cfg_ahb_clk.clkr,
	[GCC_PCIE_1_MSTR_AXI_CLK] = &gcc_pcie_1_mstr_axi_clk.clkr,
	[GCC_PCIE_1_PHY_RCHNG_CLK_SRC] = &gcc_pcie_1_phy_rchng_clk_src.clkr,
	[GCC_PCIE_1_PIPE_CLK] = &gcc_pcie_1_pipe_clk.clkr,
	[GCC_PCIE_1_PIPE_CLK_SRC] = &gcc_pcie_1_pipe_clk_src.clkr,
	[GCC_PCIE_1_SLV_AXI_CLK] = &gcc_pcie_1_slv_axi_clk.clkr,
	[GCC_PCIE_1_SLV_Q2A_AXI_CLK] = &gcc_pcie_1_slv_q2a_axi_clk.clkr,
	[GCC_PCIE_THROTTLE_CORE_CLK] = &gcc_pcie_throttle_core_clk.clkr,
	[GCC_PDM2_CLK] = &gcc_pdm2_clk.clkr,
	[GCC_PDM2_CLK_SRC] = &gcc_pdm2_clk_src.clkr,
	[GCC_PDM_AHB_CLK] = &gcc_pdm_ahb_clk.clkr,
	[GCC_PDM_XO4_CLK] = &gcc_pdm_xo4_clk.clkr,
	[GCC_QMIP_CAMERA_NRT_AHB_CLK] = &gcc_qmip_camera_nrt_ahb_clk.clkr,
	[GCC_QMIP_CAMERA_RT_AHB_CLK] = &gcc_qmip_camera_rt_ahb_clk.clkr,
	[GCC_QMIP_DISP_AHB_CLK] = &gcc_qmip_disp_ahb_clk.clkr,
	[GCC_QMIP_VIDEO_VCODEC_AHB_CLK] = &gcc_qmip_video_vcodec_ahb_clk.clkr,
	[GCC_QSPI_CNOC_PERIPH_AHB_CLK] = &gcc_qspi_cnoc_periph_ahb_clk.clkr,
	[GCC_QSPI_CORE_CLK] = &gcc_qspi_core_clk.clkr,
	[GCC_QSPI_CORE_CLK_SRC] = &gcc_qspi_core_clk_src.clkr,
	[GCC_QUPV3_WRAP0_CORE_2X_CLK] = &gcc_qupv3_wrap0_core_2x_clk.clkr,
	[GCC_QUPV3_WRAP0_CORE_CLK] = &gcc_qupv3_wrap0_core_clk.clkr,
	[GCC_QUPV3_WRAP0_S0_CLK] = &gcc_qupv3_wrap0_s0_clk.clkr,
	[GCC_QUPV3_WRAP0_S0_CLK_SRC] = &gcc_qupv3_wrap0_s0_clk_src.clkr,
	[GCC_QUPV3_WRAP0_S1_CLK] = &gcc_qupv3_wrap0_s1_clk.clkr,
	[GCC_QUPV3_WRAP0_S1_CLK_SRC] = &gcc_qupv3_wrap0_s1_clk_src.clkr,
	[GCC_QUPV3_WRAP0_S2_CLK] = &gcc_qupv3_wrap0_s2_clk.clkr,
	[GCC_QUPV3_WRAP0_S2_CLK_SRC] = &gcc_qupv3_wrap0_s2_clk_src.clkr,
	[GCC_QUPV3_WRAP0_S3_CLK] = &gcc_qupv3_wrap0_s3_clk.clkr,
	[GCC_QUPV3_WRAP0_S3_CLK_SRC] = &gcc_qupv3_wrap0_s3_clk_src.clkr,
	[GCC_QUPV3_WRAP0_S4_CLK] = &gcc_qupv3_wrap0_s4_clk.clkr,
	[GCC_QUPV3_WRAP0_S4_CLK_SRC] = &gcc_qupv3_wrap0_s4_clk_src.clkr,
	[GCC_QUPV3_WRAP0_S5_CLK] = &gcc_qupv3_wrap0_s5_clk.clkr,
	[GCC_QUPV3_WRAP0_S5_CLK_SRC] = &gcc_qupv3_wrap0_s5_clk_src.clkr,
	[GCC_QUPV3_WRAP0_S6_CLK] = &gcc_qupv3_wrap0_s6_clk.clkr,
	[GCC_QUPV3_WRAP0_S6_CLK_SRC] = &gcc_qupv3_wrap0_s6_clk_src.clkr,
	[GCC_QUPV3_WRAP0_S7_CLK] = &gcc_qupv3_wrap0_s7_clk.clkr,
	[GCC_QUPV3_WRAP0_S7_CLK_SRC] = &gcc_qupv3_wrap0_s7_clk_src.clkr,
	[GCC_QUPV3_WRAP1_CORE_2X_CLK] = &gcc_qupv3_wrap1_core_2x_clk.clkr,
	[GCC_QUPV3_WRAP1_CORE_CLK] = &gcc_qupv3_wrap1_core_clk.clkr,
	[GCC_QUPV3_WRAP1_S0_CLK] = &gcc_qupv3_wrap1_s0_clk.clkr,
	[GCC_QUPV3_WRAP1_S0_CLK_SRC] = &gcc_qupv3_wrap1_s0_clk_src.clkr,
	[GCC_QUPV3_WRAP1_S1_CLK] = &gcc_qupv3_wrap1_s1_clk.clkr,
	[GCC_QUPV3_WRAP1_S1_CLK_SRC] = &gcc_qupv3_wrap1_s1_clk_src.clkr,
	[GCC_QUPV3_WRAP1_S2_CLK] = &gcc_qupv3_wrap1_s2_clk.clkr,
	[GCC_QUPV3_WRAP1_S2_CLK_SRC] = &gcc_qupv3_wrap1_s2_clk_src.clkr,
	[GCC_QUPV3_WRAP1_S3_CLK] = &gcc_qupv3_wrap1_s3_clk.clkr,
	[GCC_QUPV3_WRAP1_S3_CLK_SRC] = &gcc_qupv3_wrap1_s3_clk_src.clkr,
	[GCC_QUPV3_WRAP1_S4_CLK] = &gcc_qupv3_wrap1_s4_clk.clkr,
	[GCC_QUPV3_WRAP1_S4_CLK_SRC] = &gcc_qupv3_wrap1_s4_clk_src.clkr,
	[GCC_QUPV3_WRAP1_S5_CLK] = &gcc_qupv3_wrap1_s5_clk.clkr,
	[GCC_QUPV3_WRAP1_S5_CLK_SRC] = &gcc_qupv3_wrap1_s5_clk_src.clkr,
	[GCC_QUPV3_WRAP1_S6_CLK] = &gcc_qupv3_wrap1_s6_clk.clkr,
	[GCC_QUPV3_WRAP1_S6_CLK_SRC] = &gcc_qupv3_wrap1_s6_clk_src.clkr,
	[GCC_QUPV3_WRAP1_S7_CLK] = &gcc_qupv3_wrap1_s7_clk.clkr,
	[GCC_QUPV3_WRAP1_S7_CLK_SRC] = &gcc_qupv3_wrap1_s7_clk_src.clkr,
	[GCC_QUPV3_WRAP_0_M_AHB_CLK] = &gcc_qupv3_wrap_0_m_ahb_clk.clkr,
	[GCC_QUPV3_WRAP_0_S_AHB_CLK] = &gcc_qupv3_wrap_0_s_ahb_clk.clkr,
	[GCC_QUPV3_WRAP_1_M_AHB_CLK] = &gcc_qupv3_wrap_1_m_ahb_clk.clkr,
	[GCC_QUPV3_WRAP_1_S_AHB_CLK] = &gcc_qupv3_wrap_1_s_ahb_clk.clkr,
	[GCC_SDCC1_AHB_CLK] = &gcc_sdcc1_ahb_clk.clkr,
	[GCC_SDCC1_APPS_CLK] = &gcc_sdcc1_apps_clk.clkr,
	[GCC_SDCC1_APPS_CLK_SRC] = &gcc_sdcc1_apps_clk_src.clkr,
	[GCC_SDCC1_ICE_CORE_CLK] = &gcc_sdcc1_ice_core_clk.clkr,
	[GCC_SDCC1_ICE_CORE_CLK_SRC] = &gcc_sdcc1_ice_core_clk_src.clkr,
	[GCC_SDCC2_AHB_CLK] = &gcc_sdcc2_ahb_clk.clkr,
	[GCC_SDCC2_APPS_CLK] = &gcc_sdcc2_apps_clk.clkr,
	[GCC_SDCC2_APPS_CLK_SRC] = &gcc_sdcc2_apps_clk_src.clkr,
	[GCC_SDCC4_AHB_CLK] = &gcc_sdcc4_ahb_clk.clkr,
	[GCC_SDCC4_APPS_CLK] = &gcc_sdcc4_apps_clk.clkr,
	[GCC_SDCC4_APPS_CLK_SRC] = &gcc_sdcc4_apps_clk_src.clkr,
	[GCC_SYS_NOC_CPUSS_AHB_CLK] = &gcc_sys_noc_cpuss_ahb_clk.clkr,
	[GCC_THROTTLE_PCIE_AHB_CLK] = &gcc_throttle_pcie_ahb_clk.clkr,
	[GCC_TITAN_NRT_THROTTLE_CORE_CLK] =
		&gcc_titan_nrt_throttle_core_clk.clkr,
	[GCC_TITAN_RT_THROTTLE_CORE_CLK] = &gcc_titan_rt_throttle_core_clk.clkr,
	[GCC_UFS_1_CLKREF_EN] = &gcc_ufs_1_clkref_en.clkr,
	[GCC_UFS_PHY_AHB_CLK] = &gcc_ufs_phy_ahb_clk.clkr,
	[GCC_UFS_PHY_AXI_CLK] = &gcc_ufs_phy_axi_clk.clkr,
	[GCC_UFS_PHY_AXI_CLK_SRC] = &gcc_ufs_phy_axi_clk_src.clkr,
	[GCC_UFS_PHY_ICE_CORE_CLK] = &gcc_ufs_phy_ice_core_clk.clkr,
	[GCC_UFS_PHY_ICE_CORE_CLK_SRC] = &gcc_ufs_phy_ice_core_clk_src.clkr,
	[GCC_UFS_PHY_PHY_AUX_CLK] = &gcc_ufs_phy_phy_aux_clk.clkr,
	[GCC_UFS_PHY_PHY_AUX_CLK_SRC] = &gcc_ufs_phy_phy_aux_clk_src.clkr,
	[GCC_UFS_PHY_RX_SYMBOL_0_CLK] = &gcc_ufs_phy_rx_symbol_0_clk.clkr,
	[GCC_UFS_PHY_RX_SYMBOL_0_CLK_SRC] =
		&gcc_ufs_phy_rx_symbol_0_clk_src.clkr,
	[GCC_UFS_PHY_RX_SYMBOL_1_CLK] = &gcc_ufs_phy_rx_symbol_1_clk.clkr,
	[GCC_UFS_PHY_RX_SYMBOL_1_CLK_SRC] =
		&gcc_ufs_phy_rx_symbol_1_clk_src.clkr,
	[GCC_UFS_PHY_TX_SYMBOL_0_CLK] = &gcc_ufs_phy_tx_symbol_0_clk.clkr,
	[GCC_UFS_PHY_TX_SYMBOL_0_CLK_SRC] =
		&gcc_ufs_phy_tx_symbol_0_clk_src.clkr,
	[GCC_UFS_PHY_UNIPRO_CORE_CLK] = &gcc_ufs_phy_unipro_core_clk.clkr,
	[GCC_UFS_PHY_UNIPRO_CORE_CLK_SRC] =
		&gcc_ufs_phy_unipro_core_clk_src.clkr,
	[GCC_USB30_PRIM_MASTER_CLK] = &gcc_usb30_prim_master_clk.clkr,
	[GCC_USB30_PRIM_MASTER_CLK_SRC] = &gcc_usb30_prim_master_clk_src.clkr,
	[GCC_USB30_PRIM_MOCK_UTMI_CLK] = &gcc_usb30_prim_mock_uपंचांगi_clk.clkr,
	[GCC_USB30_PRIM_MOCK_UTMI_CLK_SRC] =
		&gcc_usb30_prim_mock_uपंचांगi_clk_src.clkr,
	[GCC_USB30_PRIM_MOCK_UTMI_POSTDIV_CLK_SRC] =
		&gcc_usb30_prim_mock_uपंचांगi_postभाग_clk_src.clkr,
	[GCC_USB30_PRIM_SLEEP_CLK] = &gcc_usb30_prim_sleep_clk.clkr,
	[GCC_USB30_SEC_MASTER_CLK] = &gcc_usb30_sec_master_clk.clkr,
	[GCC_USB30_SEC_MASTER_CLK_SRC] = &gcc_usb30_sec_master_clk_src.clkr,
	[GCC_USB30_SEC_MOCK_UTMI_CLK] = &gcc_usb30_sec_mock_uपंचांगi_clk.clkr,
	[GCC_USB30_SEC_MOCK_UTMI_CLK_SRC] =
			&gcc_usb30_sec_mock_uपंचांगi_clk_src.clkr,
	[GCC_USB30_SEC_MOCK_UTMI_POSTDIV_CLK_SRC] =
			&gcc_usb30_sec_mock_uपंचांगi_postभाग_clk_src.clkr,
	[GCC_USB30_SEC_SLEEP_CLK] = &gcc_usb30_sec_sleep_clk.clkr,
	[GCC_USB3_PRIM_PHY_AUX_CLK] = &gcc_usb3_prim_phy_aux_clk.clkr,
	[GCC_USB3_PRIM_PHY_AUX_CLK_SRC] = &gcc_usb3_prim_phy_aux_clk_src.clkr,
	[GCC_USB3_PRIM_PHY_COM_AUX_CLK] = &gcc_usb3_prim_phy_com_aux_clk.clkr,
	[GCC_USB3_PRIM_PHY_PIPE_CLK] = &gcc_usb3_prim_phy_pipe_clk.clkr,
	[GCC_USB3_PRIM_PHY_PIPE_CLK_SRC] = &gcc_usb3_prim_phy_pipe_clk_src.clkr,
	[GCC_USB3_SEC_PHY_AUX_CLK] = &gcc_usb3_sec_phy_aux_clk.clkr,
	[GCC_USB3_SEC_PHY_AUX_CLK_SRC] = &gcc_usb3_sec_phy_aux_clk_src.clkr,
	[GCC_USB3_SEC_PHY_COM_AUX_CLK] = &gcc_usb3_sec_phy_com_aux_clk.clkr,
	[GCC_USB3_SEC_PHY_PIPE_CLK] = &gcc_usb3_sec_phy_pipe_clk.clkr,
	[GCC_USB3_SEC_PHY_PIPE_CLK_SRC] = &gcc_usb3_sec_phy_pipe_clk_src.clkr,
	[GCC_VIDEO_AXI0_CLK] = &gcc_video_axi0_clk.clkr,
	[GCC_VIDEO_MVP_THROTTLE_CORE_CLK] =
			&gcc_video_mvp_throttle_core_clk.clkr,
	[GCC_CFG_NOC_LPASS_CLK] = &gcc_cfg_noc_lpass_clk.clkr,
	[GCC_MSS_GPLL0_MAIN_DIV_CLK_SRC] = &gcc_mss_gpll0_मुख्य_भाग_clk_src.clkr,
	[GCC_MSS_CFG_AHB_CLK] = &gcc_mss_cfg_ahb_clk.clkr,
	[GCC_MSS_OFFLINE_AXI_CLK] = &gcc_mss_offline_axi_clk.clkr,
	[GCC_MSS_SNOC_AXI_CLK] = &gcc_mss_snoc_axi_clk.clkr,
	[GCC_MSS_Q6_MEMNOC_AXI_CLK] = &gcc_mss_q6_memnoc_axi_clk.clkr,
	[GCC_MSS_Q6SS_BOOT_CLK_SRC] = &gcc_mss_q6ss_boot_clk_src.clkr,
	[GCC_AGGRE_NOC_PCIE_TBU_CLK] = &gcc_aggre_noc_pcie_tbu_clk.clkr,
	[GCC_AGGRE_NOC_PCIE_CENTER_SF_AXI_CLK] =
				&gcc_aggre_noc_pcie_center_sf_axi_clk.clkr,
	[GCC_PCIE_CLKREF_EN] = &gcc_pcie_clkref_en.clkr,
	[GCC_EDP_CLKREF_EN] = &gcc_edp_clkref_en.clkr,
	[GCC_SEC_CTRL_CLK_SRC] = &gcc_sec_ctrl_clk_src.clkr,
	[GCC_WPSS_AHB_CLK] = &gcc_wpss_ahb_clk.clkr,
	[GCC_WPSS_AHB_BDG_MST_CLK] = &gcc_wpss_ahb_bdg_mst_clk.clkr,
	[GCC_WPSS_RSCP_CLK] = &gcc_wpss_rscp_clk.clkr,
पूर्ण;

अटल काष्ठा gdsc *gcc_sc7280_gdscs[] = अणु
	[GCC_PCIE_0_GDSC] = &gcc_pcie_0_gdsc,
	[GCC_PCIE_1_GDSC] = &gcc_pcie_1_gdsc,
	[GCC_UFS_PHY_GDSC] = &gcc_ufs_phy_gdsc,
	[GCC_USB30_PRIM_GDSC] = &gcc_usb30_prim_gdsc,
	[GCC_USB30_SEC_GDSC] = &gcc_usb30_sec_gdsc,
	[HLOS1_VOTE_MMNOC_MMU_TBU_HF0_GDSC] = &hlos1_vote_mmnoc_mmu_tbu_hf0_gdsc,
	[HLOS1_VOTE_MMNOC_MMU_TBU_HF1_GDSC] = &hlos1_vote_mmnoc_mmu_tbu_hf1_gdsc,
	[HLOS1_VOTE_MMNOC_MMU_TBU_SF0_GDSC] = &hlos1_vote_mmnoc_mmu_tbu_sf0_gdsc,
	[HLOS1_VOTE_TURING_MMU_TBU0_GDSC] = &hlos1_vote_turing_mmu_tbu0_gdsc,
	[HLOS1_VOTE_TURING_MMU_TBU1_GDSC] = &hlos1_vote_turing_mmu_tbu1_gdsc,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map gcc_sc7280_resets[] = अणु
	[GCC_PCIE_0_BCR] = अणु 0x6b000 पूर्ण,
	[GCC_PCIE_0_PHY_BCR] = अणु 0x6c01c पूर्ण,
	[GCC_PCIE_1_BCR] = अणु 0x8d000 पूर्ण,
	[GCC_PCIE_1_PHY_BCR] = अणु 0x8e01c पूर्ण,
	[GCC_QUSB2PHY_PRIM_BCR] = अणु 0x12000 पूर्ण,
	[GCC_QUSB2PHY_SEC_BCR] = अणु 0x12004 पूर्ण,
	[GCC_SDCC1_BCR] = अणु 0x75000 पूर्ण,
	[GCC_SDCC2_BCR] = अणु 0x14000 पूर्ण,
	[GCC_SDCC4_BCR] = अणु 0x16000 पूर्ण,
	[GCC_UFS_PHY_BCR] = अणु 0x77000 पूर्ण,
	[GCC_USB30_PRIM_BCR] = अणु 0xf000 पूर्ण,
	[GCC_USB30_SEC_BCR] = अणु 0x9e000 पूर्ण,
	[GCC_USB3_DP_PHY_PRIM_BCR] = अणु 0x50008 पूर्ण,
	[GCC_USB3_PHY_PRIM_BCR] = अणु 0x50000 पूर्ण,
	[GCC_USB3PHY_PHY_PRIM_BCR] = अणु 0x50004 पूर्ण,
	[GCC_USB_PHY_CFG_AHB2PHY_BCR] = अणु 0x6a000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_rcg_dfs_data gcc_dfs_घड़ीs[] = अणु
	DEFINE_RCG_DFS(gcc_qupv3_wrap0_s0_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap0_s1_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap0_s2_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap0_s3_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap0_s4_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap0_s5_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap0_s6_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap0_s7_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap1_s0_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap1_s1_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap1_s2_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap1_s3_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap1_s4_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap1_s5_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap1_s6_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap1_s7_clk_src),
पूर्ण;

अटल स्थिर काष्ठा regmap_config gcc_sc7280_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = 0x9f128,
	.fast_io = true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc gcc_sc7280_desc = अणु
	.config = &gcc_sc7280_regmap_config,
	.clks = gcc_sc7280_घड़ीs,
	.num_clks = ARRAY_SIZE(gcc_sc7280_घड़ीs),
	.resets = gcc_sc7280_resets,
	.num_resets = ARRAY_SIZE(gcc_sc7280_resets),
	.gdscs = gcc_sc7280_gdscs,
	.num_gdscs = ARRAY_SIZE(gcc_sc7280_gdscs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id gcc_sc7280_match_table[] = अणु
	अणु .compatible = "qcom,gcc-sc7280" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gcc_sc7280_match_table);

अटल पूर्णांक gcc_sc7280_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	regmap = qcom_cc_map(pdev, &gcc_sc7280_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/*
	 * Keep the घड़ीs always-ON
	 * GCC_CAMERA_AHB_CLK/XO_CLK, GCC_DISP_AHB_CLK/XO_CLK
	 * GCC_VIDEO_AHB_CLK/XO_CLK, GCC_GPU_CFG_AHB_CLK
	 */
	regmap_update_bits(regmap, 0x26004, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0x26028, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0x27004, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0x2701C, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0x28004, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0x28014, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0x71004, BIT(0), BIT(0));

	ret = qcom_cc_रेजिस्टर_rcg_dfs(regmap, gcc_dfs_घड़ीs,
			ARRAY_SIZE(gcc_dfs_घड़ीs));
	अगर (ret)
		वापस ret;

	वापस qcom_cc_really_probe(pdev, &gcc_sc7280_desc, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver gcc_sc7280_driver = अणु
	.probe = gcc_sc7280_probe,
	.driver = अणु
		.name = "gcc-sc7280",
		.of_match_table = gcc_sc7280_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init gcc_sc7280_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&gcc_sc7280_driver);
पूर्ण
subsys_initcall(gcc_sc7280_init);

अटल व्योम __निकास gcc_sc7280_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&gcc_sc7280_driver);
पूर्ण
module_निकास(gcc_sc7280_निकास);

MODULE_DESCRIPTION("QTI GCC SC7280 Driver");
MODULE_LICENSE("GPL v2");
