<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 * Copyright (c) 2020-2021, Linaro Ltd.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset-controller.h>

#समावेश <dt-bindings/घड़ी/qcom,gcc-sc8180x.h>

#समावेश "common.h"
#समावेश "clk-alpha-pll.h"
#समावेश "clk-branch.h"
#समावेश "clk-pll.h"
#समावेश "clk-rcg.h"
#समावेश "clk-regmap.h"
#समावेश "gdsc.h"
#समावेश "reset.h"

क्रमागत अणु
	P_AUD_REF_CLK,
	P_BI_TCXO,
	P_GPLL0_OUT_EVEN,
	P_GPLL0_OUT_MAIN,
	P_GPLL1_OUT_MAIN,
	P_GPLL2_OUT_MAIN,
	P_GPLL4_OUT_MAIN,
	P_GPLL5_OUT_MAIN,
	P_GPLL7_OUT_MAIN,
	P_GPLL9_OUT_MAIN,
	P_SLEEP_CLK,
पूर्ण;

अटल काष्ठा pll_vco trion_vco[] = अणु
	अणु 249600000, 2000000000, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll gpll0 = अणु
	.offset = 0x0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_TRION],
	.vco_table = trion_vco,
	.num_vco = ARRAY_SIZE(trion_vco),
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpll0",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_trion_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable post_भाग_प्रकारable_trion_even[] = अणु
	अणु 0x0, 1 पूर्ण,
	अणु 0x1, 2 पूर्ण,
	अणु 0x3, 4 पूर्ण,
	अणु 0x7, 8 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll0_out_even = अणु
	.offset = 0x0,
	.post_भाग_shअगरt = 8,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_trion_even,
	.num_post_भाग = ARRAY_SIZE(post_भाग_प्रकारable_trion_even),
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_TRION],
	.width = 4,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll0_out_even",
		.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &gpll0.clkr.hw पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_प्रकारrion_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll gpll1 = अणु
	.offset = 0x1000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_TRION],
	.vco_table = trion_vco,
	.num_vco = ARRAY_SIZE(trion_vco),
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpll1",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_trion_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll gpll4 = अणु
	.offset = 0x76000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_TRION],
	.vco_table = trion_vco,
	.num_vco = ARRAY_SIZE(trion_vco),
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpll4",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_trion_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll gpll7 = अणु
	.offset = 0x1a000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_TRION],
	.vco_table = trion_vco,
	.num_vco = ARRAY_SIZE(trion_vco),
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(7),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpll7",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_trion_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_0[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_GPLL0_OUT_EVEN, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parents_0[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .hw = &gpll0_out_even.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_1[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_SLEEP_CLK, 5 पूर्ण,
	अणु P_GPLL0_OUT_EVEN, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parents_1[] = अणु
	अणु .fw_name = "bi_tcxo", पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .fw_name = "sleep_clk", पूर्ण,
	अणु .hw = &gpll0_out_even.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_2[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_SLEEP_CLK, 5 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parents_2[] = अणु
	अणु .fw_name = "bi_tcxo", पूर्ण,
	अणु .fw_name = "sleep_clk", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_3[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_GPLL2_OUT_MAIN, 2 पूर्ण,
	अणु P_GPLL5_OUT_MAIN, 3 पूर्ण,
	अणु P_GPLL1_OUT_MAIN, 4 पूर्ण,
	अणु P_GPLL4_OUT_MAIN, 5 पूर्ण,
	अणु P_GPLL0_OUT_EVEN, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parents_3[] = अणु
	अणु .fw_name = "bi_tcxo", पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .name = "gpll2" पूर्ण,
	अणु .name = "gpll5" पूर्ण,
	अणु .hw = &gpll1.clkr.hw पूर्ण,
	अणु .hw = &gpll4.clkr.hw पूर्ण,
	अणु .hw = &gpll0_out_even.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_4[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parents_4[] = अणु
	अणु .fw_name = "bi_tcxo", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_5[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parents_5[] = अणु
	अणु .fw_name = "bi_tcxo", पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_6[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_GPLL7_OUT_MAIN, 3 पूर्ण,
	अणु P_GPLL0_OUT_EVEN, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parents_6[] = अणु
	अणु .fw_name = "bi_tcxo", पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .hw = &gpll7.clkr.hw पूर्ण,
	अणु .hw = &gpll0_out_even.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_7[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_GPLL9_OUT_MAIN, 2 पूर्ण,
	अणु P_GPLL4_OUT_MAIN, 5 पूर्ण,
	अणु P_GPLL0_OUT_EVEN, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parents_7[] = अणु
	अणु .fw_name = "bi_tcxo", पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .name = "gppl9" पूर्ण,
	अणु .hw = &gpll4.clkr.hw पूर्ण,
	अणु .hw = &gpll0_out_even.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_8[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_AUD_REF_CLK, 2 पूर्ण,
	अणु P_GPLL0_OUT_EVEN, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parents_8[] = अणु
	अणु .fw_name = "bi_tcxo", पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .name = "aud_ref_clk" पूर्ण,
	अणु .hw = &gpll0_out_even.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_cpuss_ahb_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(50000000, P_GPLL0_OUT_MAIN, 12, 0, 0),
	F(100000000, P_GPLL0_OUT_MAIN, 6, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_cpuss_ahb_clk_src = अणु
	.cmd_rcgr = 0x48014,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_cpuss_ahb_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_cpuss_ahb_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_emac_ptp_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(50000000, P_GPLL0_OUT_EVEN, 6, 0, 0),
	F(125000000, P_GPLL7_OUT_MAIN, 4, 0, 0),
	F(250000000, P_GPLL7_OUT_MAIN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_emac_ptp_clk_src = अणु
	.cmd_rcgr = 0x6038,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_6,
	.freq_tbl = ftbl_gcc_emac_ptp_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_emac_ptp_clk_src",
		.parent_data = gcc_parents_6,
		.num_parents = ARRAY_SIZE(gcc_parents_6),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_emac_rgmii_clk_src[] = अणु
	F(2500000, P_BI_TCXO, 1, 25, 192),
	F(5000000, P_BI_TCXO, 1, 25, 96),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(25000000, P_GPLL0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GPLL0_OUT_EVEN, 6, 0, 0),
	F(125000000, P_GPLL7_OUT_MAIN, 4, 0, 0),
	F(250000000, P_GPLL7_OUT_MAIN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_emac_rgmii_clk_src = अणु
	.cmd_rcgr = 0x601c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_6,
	.freq_tbl = ftbl_gcc_emac_rgmii_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_emac_rgmii_clk_src",
		.parent_data = gcc_parents_6,
		.num_parents = ARRAY_SIZE(gcc_parents_6),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_gp1_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(25000000, P_GPLL0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GPLL0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPLL0_OUT_MAIN, 6, 0, 0),
	F(200000000, P_GPLL0_OUT_MAIN, 3, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_gp1_clk_src = अणु
	.cmd_rcgr = 0x64004,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_gp1_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_gp1_clk_src",
		.parent_data = gcc_parents_1,
		.num_parents = ARRAY_SIZE(gcc_parents_1),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_gp2_clk_src = अणु
	.cmd_rcgr = 0x65004,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_gp1_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_gp2_clk_src",
		.parent_data = gcc_parents_1,
		.num_parents = ARRAY_SIZE(gcc_parents_1),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_gp3_clk_src = अणु
	.cmd_rcgr = 0x66004,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_gp1_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_gp3_clk_src",
		.parent_data = gcc_parents_1,
		.num_parents = ARRAY_SIZE(gcc_parents_1),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_gp4_clk_src = अणु
	.cmd_rcgr = 0xbe004,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_gp1_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_gp4_clk_src",
		.parent_data = gcc_parents_1,
		.num_parents = ARRAY_SIZE(gcc_parents_1),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_gp5_clk_src = अणु
	.cmd_rcgr = 0xbf004,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_gp1_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_gp5_clk_src",
		.parent_data = gcc_parents_1,
		.num_parents = ARRAY_SIZE(gcc_parents_1),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_npu_axi_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(60000000, P_GPLL0_OUT_EVEN, 5, 0, 0),
	F(150000000, P_GPLL0_OUT_EVEN, 2, 0, 0),
	F(200000000, P_GPLL0_OUT_MAIN, 3, 0, 0),
	F(300000000, P_GPLL0_OUT_MAIN, 2, 0, 0),
	F(403000000, P_GPLL4_OUT_MAIN, 2, 0, 0),
	F(533000000, P_GPLL1_OUT_MAIN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_npu_axi_clk_src = अणु
	.cmd_rcgr = 0x4d014,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_3,
	.freq_tbl = ftbl_gcc_npu_axi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_npu_axi_clk_src",
		.parent_data = gcc_parents_3,
		.num_parents = ARRAY_SIZE(gcc_parents_3),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_pcie_0_aux_clk_src[] = अणु
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_pcie_0_aux_clk_src = अणु
	.cmd_rcgr = 0x6b02c,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_2,
	.freq_tbl = ftbl_gcc_pcie_0_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_pcie_0_aux_clk_src",
		.parent_data = gcc_parents_2,
		.num_parents = ARRAY_SIZE(gcc_parents_2),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_pcie_1_aux_clk_src = अणु
	.cmd_rcgr = 0x8d02c,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_2,
	.freq_tbl = ftbl_gcc_pcie_0_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_pcie_1_aux_clk_src",
		.parent_data = gcc_parents_2,
		.num_parents = ARRAY_SIZE(gcc_parents_2),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_pcie_2_aux_clk_src = अणु
	.cmd_rcgr = 0x9d02c,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_2,
	.freq_tbl = ftbl_gcc_pcie_0_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_pcie_2_aux_clk_src",
		.parent_data = gcc_parents_2,
		.num_parents = ARRAY_SIZE(gcc_parents_2),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_pcie_3_aux_clk_src = अणु
	.cmd_rcgr = 0xa302c,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_2,
	.freq_tbl = ftbl_gcc_pcie_0_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_pcie_3_aux_clk_src",
		.parent_data = gcc_parents_2,
		.num_parents = ARRAY_SIZE(gcc_parents_2),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_pcie_phy_refgen_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_GPLL0_OUT_MAIN, 6, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_pcie_phy_refgen_clk_src = अणु
	.cmd_rcgr = 0x6f014,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_pcie_phy_refgen_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_pcie_phy_refgen_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_pdm2_clk_src[] = अणु
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(60000000, P_GPLL0_OUT_MAIN, 10, 0, 0),
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
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_qspi_1_core_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(75000000, P_GPLL0_OUT_EVEN, 4, 0, 0),
	F(150000000, P_GPLL0_OUT_MAIN, 4, 0, 0),
	F(300000000, P_GPLL0_OUT_MAIN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qspi_1_core_clk_src = अणु
	.cmd_rcgr = 0x4a00c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qspi_1_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qspi_1_core_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qspi_core_clk_src = अणु
	.cmd_rcgr = 0x4b008,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qspi_1_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qspi_core_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_qupv3_wrap0_s0_clk_src[] = अणु
	F(7372800, P_GPLL0_OUT_EVEN, 1, 384, 15625),
	F(14745600, P_GPLL0_OUT_EVEN, 1, 768, 15625),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(29491200, P_GPLL0_OUT_EVEN, 1, 1536, 15625),
	F(32000000, P_GPLL0_OUT_EVEN, 1, 8, 75),
	F(48000000, P_GPLL0_OUT_EVEN, 1, 4, 25),
	F(50000000, P_GPLL0_OUT_EVEN, 6, 0, 0),
	F(64000000, P_GPLL0_OUT_EVEN, 1, 16, 75),
	F(75000000, P_GPLL0_OUT_EVEN, 4, 0, 0),
	F(80000000, P_GPLL0_OUT_EVEN, 1, 4, 15),
	F(96000000, P_GPLL0_OUT_EVEN, 1, 8, 25),
	F(100000000, P_GPLL0_OUT_MAIN, 6, 0, 0),
	F(102400000, P_GPLL0_OUT_EVEN, 1, 128, 375),
	F(112000000, P_GPLL0_OUT_EVEN, 1, 28, 75),
	F(117964800, P_GPLL0_OUT_EVEN, 1, 6144, 15625),
	F(120000000, P_GPLL0_OUT_EVEN, 2.5, 0, 0),
	F(128000000, P_GPLL0_OUT_MAIN, 1, 16, 75),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s0_clk_src = अणु
	.cmd_rcgr = 0x17148,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qupv3_wrap0_s0_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s1_clk_src = अणु
	.cmd_rcgr = 0x17278,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qupv3_wrap0_s1_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s2_clk_src = अणु
	.cmd_rcgr = 0x173a8,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qupv3_wrap0_s2_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s3_clk_src = अणु
	.cmd_rcgr = 0x174d8,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qupv3_wrap0_s3_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s4_clk_src = अणु
	.cmd_rcgr = 0x17608,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qupv3_wrap0_s4_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s5_clk_src = अणु
	.cmd_rcgr = 0x17738,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qupv3_wrap0_s5_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s6_clk_src = अणु
	.cmd_rcgr = 0x17868,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qupv3_wrap0_s6_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s7_clk_src = अणु
	.cmd_rcgr = 0x17998,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qupv3_wrap0_s7_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s0_clk_src = अणु
	.cmd_rcgr = 0x18148,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qupv3_wrap1_s0_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s1_clk_src = अणु
	.cmd_rcgr = 0x18278,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qupv3_wrap1_s1_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s2_clk_src = अणु
	.cmd_rcgr = 0x183a8,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qupv3_wrap1_s2_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s3_clk_src = अणु
	.cmd_rcgr = 0x184d8,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qupv3_wrap1_s3_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s4_clk_src = अणु
	.cmd_rcgr = 0x18608,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qupv3_wrap1_s4_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s5_clk_src = अणु
	.cmd_rcgr = 0x18738,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qupv3_wrap1_s5_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap2_s0_clk_src = अणु
	.cmd_rcgr = 0x1e148,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qupv3_wrap2_s0_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap2_s1_clk_src = अणु
	.cmd_rcgr = 0x1e278,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qupv3_wrap2_s1_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap2_s2_clk_src = अणु
	.cmd_rcgr = 0x1e3a8,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qupv3_wrap2_s2_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap2_s3_clk_src = अणु
	.cmd_rcgr = 0x1e4d8,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qupv3_wrap2_s3_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap2_s4_clk_src = अणु
	.cmd_rcgr = 0x1e608,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qupv3_wrap2_s4_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap2_s5_clk_src = अणु
	.cmd_rcgr = 0x1e738,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qupv3_wrap2_s5_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sdcc2_apps_clk_src[] = अणु
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(25000000, P_GPLL0_OUT_MAIN, 12, 1, 2),
	F(50000000, P_GPLL0_OUT_MAIN, 12, 0, 0),
	F(100000000, P_GPLL0_OUT_MAIN, 6, 0, 0),
	F(200000000, P_GPLL0_OUT_MAIN, 3, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_sdcc2_apps_clk_src = अणु
	.cmd_rcgr = 0x1400c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_7,
	.freq_tbl = ftbl_gcc_sdcc2_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_sdcc2_apps_clk_src",
		.parent_data = gcc_parents_7,
		.num_parents = ARRAY_SIZE(gcc_parents_7),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_न्यूनमान_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sdcc4_apps_clk_src[] = अणु
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(37500000, P_GPLL0_OUT_MAIN, 16, 0, 0),
	F(50000000, P_GPLL0_OUT_MAIN, 12, 0, 0),
	F(75000000, P_GPLL0_OUT_MAIN, 8, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_sdcc4_apps_clk_src = अणु
	.cmd_rcgr = 0x1600c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_5,
	.freq_tbl = ftbl_gcc_sdcc4_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_sdcc4_apps_clk_src",
		.parent_data = gcc_parents_5,
		.num_parents = ARRAY_SIZE(gcc_parents_5),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_न्यूनमान_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_tsअगर_ref_clk_src[] = अणु
	F(105495, P_BI_TCXO, 2, 1, 91),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_tsअगर_ref_clk_src = अणु
	.cmd_rcgr = 0x36010,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_8,
	.freq_tbl = ftbl_gcc_tsअगर_ref_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_tsif_ref_clk_src",
		.parent_data = gcc_parents_8,
		.num_parents = ARRAY_SIZE(gcc_parents_8),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ufs_card_2_axi_clk_src[] = अणु
	F(37500000, P_GPLL0_OUT_EVEN, 8, 0, 0),
	F(75000000, P_GPLL0_OUT_EVEN, 4, 0, 0),
	F(150000000, P_GPLL0_OUT_MAIN, 4, 0, 0),
	F(300000000, P_GPLL0_OUT_MAIN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_card_2_axi_clk_src = अणु
	.cmd_rcgr = 0xa2020,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_ufs_card_2_axi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_card_2_axi_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_card_2_ice_core_clk_src = अणु
	.cmd_rcgr = 0xa2060,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_ufs_card_2_axi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_card_2_ice_core_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ufs_card_2_phy_aux_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_card_2_phy_aux_clk_src = अणु
	.cmd_rcgr = 0xa2094,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_4,
	.freq_tbl = ftbl_gcc_ufs_card_2_phy_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_card_2_phy_aux_clk_src",
		.parent_data = gcc_parents_4,
		.num_parents = ARRAY_SIZE(gcc_parents_4),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_card_2_unipro_core_clk_src = अणु
	.cmd_rcgr = 0xa2078,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_ufs_card_2_axi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_card_2_unipro_core_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ufs_card_axi_clk_src[] = अणु
	F(25000000, P_GPLL0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GPLL0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPLL0_OUT_MAIN, 6, 0, 0),
	F(200000000, P_GPLL0_OUT_MAIN, 3, 0, 0),
	F(240000000, P_GPLL0_OUT_MAIN, 2.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_card_axi_clk_src = अणु
	.cmd_rcgr = 0x75020,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_ufs_card_axi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_card_axi_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ufs_card_ice_core_clk_src[] = अणु
	F(75000000, P_GPLL0_OUT_EVEN, 4, 0, 0),
	F(150000000, P_GPLL0_OUT_MAIN, 4, 0, 0),
	F(300000000, P_GPLL0_OUT_MAIN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_card_ice_core_clk_src = अणु
	.cmd_rcgr = 0x75060,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_ufs_card_ice_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_card_ice_core_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_card_phy_aux_clk_src = अणु
	.cmd_rcgr = 0x75094,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_4,
	.freq_tbl = ftbl_gcc_ufs_card_2_phy_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_card_phy_aux_clk_src",
		.parent_data = gcc_parents_4,
		.num_parents = ARRAY_SIZE(gcc_parents_4),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ufs_card_unipro_core_clk_src[] = अणु
	F(37500000, P_GPLL0_OUT_EVEN, 8, 0, 0),
	F(75000000, P_GPLL0_OUT_MAIN, 8, 0, 0),
	F(150000000, P_GPLL0_OUT_MAIN, 4, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_card_unipro_core_clk_src = अणु
	.cmd_rcgr = 0x75078,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_ufs_card_unipro_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_card_unipro_core_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ufs_phy_axi_clk_src[] = अणु
	F(25000000, P_GPLL0_OUT_EVEN, 12, 0, 0),
	F(37500000, P_GPLL0_OUT_EVEN, 8, 0, 0),
	F(75000000, P_GPLL0_OUT_EVEN, 4, 0, 0),
	F(150000000, P_GPLL0_OUT_MAIN, 4, 0, 0),
	F(300000000, P_GPLL0_OUT_MAIN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_phy_axi_clk_src = अणु
	.cmd_rcgr = 0x77020,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_ufs_phy_axi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_phy_axi_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_phy_ice_core_clk_src = अणु
	.cmd_rcgr = 0x77060,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_ufs_card_2_axi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_phy_ice_core_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_phy_phy_aux_clk_src = अणु
	.cmd_rcgr = 0x77094,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_4,
	.freq_tbl = ftbl_gcc_pcie_0_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_phy_phy_aux_clk_src",
		.parent_data = gcc_parents_4,
		.num_parents = ARRAY_SIZE(gcc_parents_4),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_phy_unipro_core_clk_src = अणु
	.cmd_rcgr = 0x77078,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_ufs_card_2_axi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_phy_unipro_core_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb30_mp_master_clk_src[] = अणु
	F(33333333, P_GPLL0_OUT_EVEN, 9, 0, 0),
	F(66666667, P_GPLL0_OUT_EVEN, 4.5, 0, 0),
	F(133333333, P_GPLL0_OUT_MAIN, 4.5, 0, 0),
	F(200000000, P_GPLL0_OUT_MAIN, 3, 0, 0),
	F(240000000, P_GPLL0_OUT_MAIN, 2.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb30_mp_master_clk_src = अणु
	.cmd_rcgr = 0xa601c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_usb30_mp_master_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb30_mp_master_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb30_mp_mock_uपंचांगi_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(20000000, P_GPLL0_OUT_EVEN, 15, 0, 0),
	F(40000000, P_GPLL0_OUT_EVEN, 7.5, 0, 0),
	F(60000000, P_GPLL0_OUT_MAIN, 10, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb30_mp_mock_uपंचांगi_clk_src = अणु
	.cmd_rcgr = 0xa6034,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_usb30_mp_mock_uपंचांगi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb30_mp_mock_utmi_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb30_prim_master_clk_src = अणु
	.cmd_rcgr = 0xf01c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_usb30_mp_master_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb30_prim_master_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb30_prim_mock_uपंचांगi_clk_src = अणु
	.cmd_rcgr = 0xf034,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_usb30_mp_mock_uपंचांगi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb30_prim_mock_utmi_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb30_sec_master_clk_src = अणु
	.cmd_rcgr = 0x1001c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_usb30_mp_master_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb30_sec_master_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb30_sec_mock_uपंचांगi_clk_src = अणु
	.cmd_rcgr = 0x10034,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_usb30_mp_mock_uपंचांगi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb30_sec_mock_utmi_clk_src",
		.parent_data = gcc_parents_0,
		.num_parents = ARRAY_SIZE(gcc_parents_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb3_mp_phy_aux_clk_src = अणु
	.cmd_rcgr = 0xa6068,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_2,
	.freq_tbl = ftbl_gcc_ufs_card_2_phy_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb3_mp_phy_aux_clk_src",
		.parent_data = gcc_parents_2,
		.num_parents = ARRAY_SIZE(gcc_parents_2),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb3_prim_phy_aux_clk_src = अणु
	.cmd_rcgr = 0xf060,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_2,
	.freq_tbl = ftbl_gcc_ufs_card_2_phy_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb3_prim_phy_aux_clk_src",
		.parent_data = gcc_parents_2,
		.num_parents = ARRAY_SIZE(gcc_parents_2),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb3_sec_phy_aux_clk_src = अणु
	.cmd_rcgr = 0x10060,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_2,
	.freq_tbl = ftbl_gcc_ufs_card_2_phy_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb3_sec_phy_aux_clk_src",
		.parent_data = gcc_parents_2,
		.num_parents = ARRAY_SIZE(gcc_parents_2),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre_noc_pcie_tbu_clk = अणु
	.halt_reg = 0x90018,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x90018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_aggre_noc_pcie_tbu_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre_ufs_card_axi_clk = अणु
	.halt_reg = 0x750c0,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x750c0,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x750c0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_aggre_ufs_card_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_ufs_card_axi_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre_ufs_card_axi_hw_ctl_clk = अणु
	.halt_reg = 0x750c0,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x750c0,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x750c0,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_aggre_ufs_card_axi_hw_ctl_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_aggre_ufs_card_axi_clk.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch_simple_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre_ufs_phy_axi_clk = अणु
	.halt_reg = 0x770c0,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x770c0,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x770c0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_aggre_ufs_phy_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_ufs_phy_axi_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre_ufs_phy_axi_hw_ctl_clk = अणु
	.halt_reg = 0x770c0,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x770c0,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x770c0,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_aggre_ufs_phy_axi_hw_ctl_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_aggre_ufs_phy_axi_clk.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch_simple_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre_usb3_mp_axi_clk = अणु
	.halt_reg = 0xa6084,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa6084,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_aggre_usb3_mp_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_usb30_mp_master_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre_usb3_prim_axi_clk = अणु
	.halt_reg = 0xf07c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf07c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_aggre_usb3_prim_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_usb30_prim_master_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre_usb3_sec_axi_clk = अणु
	.halt_reg = 0x1007c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x1007c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_aggre_usb3_sec_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_usb30_sec_master_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_boot_rom_ahb_clk = अणु
	.halt_reg = 0x38004,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x38004,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(10),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_boot_rom_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camera_hf_axi_clk = अणु
	.halt_reg = 0xb030,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb030,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camera_hf_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camera_sf_axi_clk = अणु
	.halt_reg = 0xb034,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb034,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camera_sf_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_cfg_noc_usb3_mp_axi_clk = अणु
	.halt_reg = 0xa609c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa609c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_cfg_noc_usb3_mp_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_usb30_mp_master_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_cfg_noc_usb3_prim_axi_clk = अणु
	.halt_reg = 0xf078,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf078,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_cfg_noc_usb3_prim_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_usb30_prim_master_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_cfg_noc_usb3_sec_axi_clk = अणु
	.halt_reg = 0x10078,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x10078,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_cfg_noc_usb3_sec_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_usb30_sec_master_clk_src.clkr.hw
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
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(21),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_cpuss_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_cpuss_ahb_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_IS_CRITICAL | CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_cpuss_rbcpr_clk = अणु
	.halt_reg = 0x48008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x48008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_cpuss_rbcpr_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ddrss_gpu_axi_clk = अणु
	.halt_reg = 0x71154,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x71154,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ddrss_gpu_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_disp_hf_axi_clk = अणु
	.halt_reg = 0xb038,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb038,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_disp_hf_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_disp_sf_axi_clk = अणु
	.halt_reg = 0xb03c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb03c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_disp_sf_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_emac_axi_clk = अणु
	.halt_reg = 0x6010,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_emac_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_emac_ptp_clk = अणु
	.halt_reg = 0x6034,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6034,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_emac_ptp_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_emac_ptp_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_emac_rgmii_clk = अणु
	.halt_reg = 0x6018,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_emac_rgmii_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_emac_rgmii_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_emac_slv_ahb_clk = अणु
	.halt_reg = 0x6014,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x6014,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x6014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_emac_slv_ahb_clk",
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
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_gp1_clk_src.clkr.hw
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
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_gp2_clk_src.clkr.hw
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
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_gp3_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gp4_clk = अणु
	.halt_reg = 0xbe000,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xbe000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gp4_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_gp4_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gp5_clk = अणु
	.halt_reg = 0xbf000,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xbf000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gp5_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_gp5_clk_src.clkr.hw
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
		.enable_reg = 0x52004,
		.enable_mask = BIT(15),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gpu_gpll0_clk_src",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &gpll0.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gpu_gpll0_भाग_clk_src = अणु
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(16),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gpu_gpll0_div_clk_src",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gpll0_out_even.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gpu_memnoc_gfx_clk = अणु
	.halt_reg = 0x7100c,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x7100c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gpu_memnoc_gfx_clk",
			.ops = &clk_branch2_ops,
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
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_npu_at_clk = अणु
	.halt_reg = 0x4d010,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x4d010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_npu_at_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_npu_axi_clk = अणु
	.halt_reg = 0x4d008,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x4d008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_npu_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_npu_axi_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_npu_gpll0_clk_src = अणु
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(18),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_npu_gpll0_clk_src",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &gpll0.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_npu_gpll0_भाग_clk_src = अणु
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(19),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_npu_gpll0_div_clk_src",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gpll0_out_even.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_npu_trig_clk = अणु
	.halt_reg = 0x4d00c,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x4d00c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_npu_trig_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie0_phy_refgen_clk = अणु
	.halt_reg = 0x6f02c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6f02c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie0_phy_refgen_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_pcie_phy_refgen_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie1_phy_refgen_clk = अणु
	.halt_reg = 0x6f030,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6f030,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie1_phy_refgen_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_pcie_phy_refgen_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie2_phy_refgen_clk = अणु
	.halt_reg = 0x6f034,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6f034,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie2_phy_refgen_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_pcie_phy_refgen_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie3_phy_refgen_clk = अणु
	.halt_reg = 0x6f038,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6f038,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie3_phy_refgen_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_pcie_phy_refgen_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_aux_clk = अणु
	.halt_reg = 0x6b020,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(3),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_pcie_0_aux_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_cfg_ahb_clk = अणु
	.halt_reg = 0x6b01c,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x6b01c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_cfg_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_clkref_clk = अणु
	.halt_reg = 0x8c00c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8c00c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_clkref_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_mstr_axi_clk = अणु
	.halt_reg = 0x6b018,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_mstr_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_pipe_clk = अणु
	.halt_reg = 0x6b024,
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_pipe_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_slv_axi_clk = अणु
	.halt_reg = 0x6b014,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x6b014,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x5200c,
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
		.enable_reg = 0x5200c,
		.enable_mask = BIT(5),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_slv_q2a_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_aux_clk = अणु
	.halt_reg = 0x8d020,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(29),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_1_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_pcie_1_aux_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_cfg_ahb_clk = अणु
	.halt_reg = 0x8d01c,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x8d01c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(28),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_1_cfg_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_clkref_clk = अणु
	.halt_reg = 0x8c02c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8c02c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_1_clkref_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_mstr_axi_clk = अणु
	.halt_reg = 0x8d018,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(27),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_1_mstr_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_pipe_clk = अणु
	.halt_reg = 0x8d024,
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(30),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_1_pipe_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_slv_axi_clk = अणु
	.halt_reg = 0x8d014,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x8d014,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52004,
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
		.enable_reg = 0x52004,
		.enable_mask = BIT(25),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_1_slv_q2a_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_2_aux_clk = अणु
	.halt_reg = 0x9d020,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52014,
		.enable_mask = BIT(14),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_2_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_pcie_2_aux_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_2_cfg_ahb_clk = अणु
	.halt_reg = 0x9d01c,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x9d01c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52014,
		.enable_mask = BIT(13),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_2_cfg_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_2_clkref_clk = अणु
	.halt_reg = 0x8c014,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8c014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_2_clkref_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_2_mstr_axi_clk = अणु
	.halt_reg = 0x9d018,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52014,
		.enable_mask = BIT(12),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_2_mstr_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_2_pipe_clk = अणु
	.halt_reg = 0x9d024,
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x52014,
		.enable_mask = BIT(15),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_2_pipe_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_2_slv_axi_clk = अणु
	.halt_reg = 0x9d014,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x9d014,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52014,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_2_slv_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_2_slv_q2a_axi_clk = अणु
	.halt_reg = 0x9d010,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52014,
		.enable_mask = BIT(10),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_2_slv_q2a_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_3_aux_clk = अणु
	.halt_reg = 0xa3020,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52014,
		.enable_mask = BIT(20),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_3_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_pcie_3_aux_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_3_cfg_ahb_clk = अणु
	.halt_reg = 0xa301c,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0xa301c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52014,
		.enable_mask = BIT(19),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_3_cfg_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_3_clkref_clk = अणु
	.halt_reg = 0x8c018,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8c018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_3_clkref_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_3_mstr_axi_clk = अणु
	.halt_reg = 0xa3018,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52014,
		.enable_mask = BIT(18),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_3_mstr_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_3_pipe_clk = अणु
	.halt_reg = 0xa3024,
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x52014,
		.enable_mask = BIT(21),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_3_pipe_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_3_slv_axi_clk = अणु
	.halt_reg = 0xa3014,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0xa3014,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52014,
		.enable_mask = BIT(17),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_3_slv_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_3_slv_q2a_axi_clk = अणु
	.halt_reg = 0xa3010,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52014,
		.enable_mask = BIT(16),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_3_slv_q2a_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_phy_aux_clk = अणु
	.halt_reg = 0x6f004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6f004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_phy_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_pcie_0_aux_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
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
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_pdm2_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pdm_ahb_clk = अणु
	.halt_reg = 0x33004,
	.halt_check = BRANCH_HALT,
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

अटल काष्ठा clk_branch gcc_prng_ahb_clk = अणु
	.halt_reg = 0x34004,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(13),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_prng_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qmip_camera_nrt_ahb_clk = अणु
	.halt_reg = 0xb018,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0xb018,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xb018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qmip_camera_nrt_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qmip_camera_rt_ahb_clk = अणु
	.halt_reg = 0xb01c,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0xb01c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xb01c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qmip_camera_rt_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qmip_disp_ahb_clk = अणु
	.halt_reg = 0xb020,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0xb020,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xb020,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qmip_disp_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qmip_video_cvp_ahb_clk = अणु
	.halt_reg = 0xb010,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0xb010,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xb010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qmip_video_cvp_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qmip_video_vcodec_ahb_clk = अणु
	.halt_reg = 0xb014,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0xb014,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xb014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qmip_video_vcodec_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qspi_1_cnoc_periph_ahb_clk = अणु
	.halt_reg = 0x4a004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x4a004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qspi_1_cnoc_periph_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qspi_1_core_clk = अणु
	.halt_reg = 0x4a008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x4a008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qspi_1_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_qspi_1_core_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qspi_cnoc_periph_ahb_clk = अणु
	.halt_reg = 0x4b000,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x4b000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qspi_cnoc_periph_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qspi_core_clk = अणु
	.halt_reg = 0x4b004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x4b004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qspi_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_qspi_core_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap0_s0_clk = अणु
	.halt_reg = 0x17144,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(10),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap0_s0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_qupv3_wrap0_s0_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap0_s1_clk = अणु
	.halt_reg = 0x17274,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap0_s1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_qupv3_wrap0_s1_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap0_s2_clk = अणु
	.halt_reg = 0x173a4,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(12),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap0_s2_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_qupv3_wrap0_s2_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap0_s3_clk = अणु
	.halt_reg = 0x174d4,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(13),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap0_s3_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_qupv3_wrap0_s3_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap0_s4_clk = अणु
	.halt_reg = 0x17604,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(14),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap0_s4_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_qupv3_wrap0_s4_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap0_s5_clk = अणु
	.halt_reg = 0x17734,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(15),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap0_s5_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_qupv3_wrap0_s5_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap0_s6_clk = अणु
	.halt_reg = 0x17864,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(16),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap0_s6_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_qupv3_wrap0_s6_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap0_s7_clk = अणु
	.halt_reg = 0x17994,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(17),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap0_s7_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_qupv3_wrap0_s7_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap1_s0_clk = अणु
	.halt_reg = 0x18144,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(22),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap1_s0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_qupv3_wrap1_s0_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap1_s1_clk = अणु
	.halt_reg = 0x18274,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(23),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap1_s1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_qupv3_wrap1_s1_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap1_s2_clk = अणु
	.halt_reg = 0x183a4,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(24),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap1_s2_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_qupv3_wrap1_s2_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap1_s3_clk = अणु
	.halt_reg = 0x184d4,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(25),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap1_s3_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_qupv3_wrap1_s3_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap1_s4_clk = अणु
	.halt_reg = 0x18604,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(26),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap1_s4_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_qupv3_wrap1_s4_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap1_s5_clk = अणु
	.halt_reg = 0x18734,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(27),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap1_s5_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_qupv3_wrap1_s5_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap2_s0_clk = अणु
	.halt_reg = 0x1e144,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52014,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap2_s0_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_qupv3_wrap2_s0_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap2_s1_clk = अणु
	.halt_reg = 0x1e274,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52014,
		.enable_mask = BIT(5),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap2_s1_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_qupv3_wrap2_s1_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap2_s2_clk = अणु
	.halt_reg = 0x1e3a4,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52014,
		.enable_mask = BIT(6),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap2_s2_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_qupv3_wrap2_s2_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap2_s3_clk = अणु
	.halt_reg = 0x1e4d4,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52014,
		.enable_mask = BIT(7),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap2_s3_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_qupv3_wrap2_s3_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap2_s4_clk = अणु
	.halt_reg = 0x1e604,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52014,
		.enable_mask = BIT(8),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap2_s4_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_qupv3_wrap2_s4_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap2_s5_clk = अणु
	.halt_reg = 0x1e734,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52014,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap2_s5_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_qupv3_wrap2_s5_clk_src.clkr.hw
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
	.clkr = अणु
		.enable_reg = 0x5200c,
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
		.enable_reg = 0x5200c,
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
	.clkr = अणु
		.enable_reg = 0x5200c,
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
		.enable_reg = 0x5200c,
		.enable_mask = BIT(21),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap_1_s_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap_2_m_ahb_clk = अणु
	.halt_reg = 0x1e004,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52014,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap_2_m_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap_2_s_ahb_clk = अणु
	.halt_reg = 0x1e008,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x1e008,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52014,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qupv3_wrap_2_s_ahb_clk",
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
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_sdcc2_apps_clk_src.clkr.hw
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
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_sdcc4_apps_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* For CPUSS functionality the SYS NOC घड़ी needs to be left enabled */
अटल काष्ठा clk_branch gcc_sys_noc_cpuss_ahb_clk = अणु
	.halt_reg = 0x4819c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sys_noc_cpuss_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_cpuss_ahb_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_IS_CRITICAL | CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_tsअगर_ahb_clk = अणु
	.halt_reg = 0x36004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x36004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_tsif_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_tsअगर_inactivity_समयrs_clk = अणु
	.halt_reg = 0x3600c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x3600c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_tsif_inactivity_timers_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_tsअगर_ref_clk = अणु
	.halt_reg = 0x36008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x36008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_tsif_ref_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_tsअगर_ref_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_2_ahb_clk = अणु
	.halt_reg = 0xa2014,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0xa2014,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xa2014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_2_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_2_axi_clk = अणु
	.halt_reg = 0xa2010,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0xa2010,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xa2010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_2_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_ufs_card_2_axi_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_2_ice_core_clk = अणु
	.halt_reg = 0xa205c,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0xa205c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xa205c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_2_ice_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_ufs_card_2_ice_core_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_2_phy_aux_clk = अणु
	.halt_reg = 0xa2090,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0xa2090,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xa2090,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_2_phy_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_ufs_card_2_phy_aux_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_2_rx_symbol_0_clk = अणु
	.halt_reg = 0xa201c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa201c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_2_rx_symbol_0_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_2_rx_symbol_1_clk = अणु
	.halt_reg = 0xa20ac,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa20ac,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_2_rx_symbol_1_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_2_tx_symbol_0_clk = अणु
	.halt_reg = 0xa2018,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa2018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_2_tx_symbol_0_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_2_unipro_core_clk = अणु
	.halt_reg = 0xa2058,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0xa2058,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xa2058,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_2_unipro_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				&gcc_ufs_card_2_unipro_core_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_ahb_clk = अणु
	.halt_reg = 0x75014,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x75014,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x75014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_axi_clk = अणु
	.halt_reg = 0x75010,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x75010,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x75010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_ufs_card_axi_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_axi_hw_ctl_clk = अणु
	.halt_reg = 0x75010,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x75010,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x75010,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_axi_hw_ctl_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_ufs_card_axi_clk.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch_simple_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_ice_core_clk = अणु
	.halt_reg = 0x7505c,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x7505c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x7505c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_ice_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_ufs_card_ice_core_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_ice_core_hw_ctl_clk = अणु
	.halt_reg = 0x7505c,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x7505c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x7505c,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_ice_core_hw_ctl_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_ufs_card_ice_core_clk.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch_simple_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_phy_aux_clk = अणु
	.halt_reg = 0x75090,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x75090,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x75090,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_phy_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_ufs_card_phy_aux_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_phy_aux_hw_ctl_clk = अणु
	.halt_reg = 0x75090,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x75090,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x75090,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_phy_aux_hw_ctl_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_ufs_card_phy_aux_clk.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch_simple_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_rx_symbol_0_clk = अणु
	.halt_reg = 0x7501c,
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x7501c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_rx_symbol_0_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_rx_symbol_1_clk = अणु
	.halt_reg = 0x750ac,
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x750ac,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_rx_symbol_1_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_tx_symbol_0_clk = अणु
	.halt_reg = 0x75018,
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x75018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_tx_symbol_0_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_unipro_core_clk = अणु
	.halt_reg = 0x75058,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x75058,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x75058,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_unipro_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_ufs_card_unipro_core_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_unipro_core_hw_ctl_clk = अणु
	.halt_reg = 0x75058,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x75058,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x75058,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_unipro_core_hw_ctl_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_ufs_card_unipro_core_clk.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch_simple_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_ahb_clk = अणु
	.halt_reg = 0x77014,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x77014,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x77014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_axi_clk = अणु
	.halt_reg = 0x77010,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x77010,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x77010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_ufs_phy_axi_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_axi_hw_ctl_clk = अणु
	.halt_reg = 0x77010,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x77010,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x77010,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_axi_hw_ctl_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_ufs_phy_axi_clk.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch_simple_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_ice_core_clk = अणु
	.halt_reg = 0x7705c,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x7705c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x7705c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_ice_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_ufs_phy_ice_core_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_ice_core_hw_ctl_clk = अणु
	.halt_reg = 0x7705c,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x7705c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x7705c,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_ice_core_hw_ctl_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_ufs_phy_ice_core_clk.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch_simple_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_phy_aux_clk = अणु
	.halt_reg = 0x77090,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x77090,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x77090,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_phy_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_ufs_phy_phy_aux_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_phy_aux_hw_ctl_clk = अणु
	.halt_reg = 0x77090,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x77090,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x77090,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_phy_aux_hw_ctl_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_ufs_phy_phy_aux_clk.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch_simple_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_rx_symbol_0_clk = अणु
	.halt_reg = 0x7701c,
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x7701c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_rx_symbol_0_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_rx_symbol_1_clk = अणु
	.halt_reg = 0x770ac,
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x770ac,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_rx_symbol_1_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_tx_symbol_0_clk = अणु
	.halt_reg = 0x77018,
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x77018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_tx_symbol_0_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_unipro_core_clk = अणु
	.halt_reg = 0x77058,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x77058,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x77058,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_unipro_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_ufs_phy_unipro_core_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_unipro_core_hw_ctl_clk = अणु
	.halt_reg = 0x77058,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x77058,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x77058,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_unipro_core_hw_ctl_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_ufs_phy_unipro_core_clk.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch_simple_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_mp_master_clk = अणु
	.halt_reg = 0xa6010,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa6010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_mp_master_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_usb30_mp_master_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_mp_mock_uपंचांगi_clk = अणु
	.halt_reg = 0xa6018,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa6018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_mp_mock_utmi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_usb30_mp_mock_uपंचांगi_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_mp_sleep_clk = अणु
	.halt_reg = 0xa6014,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa6014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_mp_sleep_clk",
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
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_usb30_prim_master_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_prim_mock_uपंचांगi_clk = अणु
	.halt_reg = 0xf018,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_prim_mock_utmi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_usb30_prim_mock_uपंचांगi_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_prim_sleep_clk = अणु
	.halt_reg = 0xf014,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_prim_sleep_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_sec_master_clk = अणु
	.halt_reg = 0x10010,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x10010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_sec_master_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_usb30_sec_master_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_sec_mock_uपंचांगi_clk = अणु
	.halt_reg = 0x10018,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x10018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_sec_mock_utmi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_usb30_sec_mock_uपंचांगi_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_sec_sleep_clk = अणु
	.halt_reg = 0x10014,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x10014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_sec_sleep_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_mp_phy_aux_clk = अणु
	.halt_reg = 0xa6050,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa6050,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_mp_phy_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_usb3_mp_phy_aux_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_mp_phy_com_aux_clk = अणु
	.halt_reg = 0xa6054,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa6054,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_mp_phy_com_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_usb3_mp_phy_aux_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_mp_phy_pipe_0_clk = अणु
	.halt_reg = 0xa6058,
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0xa6058,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_mp_phy_pipe_0_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_mp_phy_pipe_1_clk = अणु
	.halt_reg = 0xa605c,
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0xa605c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_mp_phy_pipe_1_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_prim_clkref_clk = अणु
	.halt_reg = 0x8c008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8c008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_prim_clkref_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_prim_phy_aux_clk = अणु
	.halt_reg = 0xf050,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf050,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_prim_phy_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_usb3_prim_phy_aux_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_prim_phy_com_aux_clk = अणु
	.halt_reg = 0xf054,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf054,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_prim_phy_com_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_usb3_prim_phy_aux_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_prim_phy_pipe_clk = अणु
	.halt_reg = 0xf058,
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0xf058,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_prim_phy_pipe_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_sec_clkref_clk = अणु
	.halt_reg = 0x8c028,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8c028,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_sec_clkref_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_sec_phy_aux_clk = अणु
	.halt_reg = 0x10050,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x10050,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_sec_phy_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_usb3_sec_phy_aux_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_sec_phy_com_aux_clk = अणु
	.halt_reg = 0x10054,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x10054,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_sec_phy_com_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु
				      &gcc_usb3_sec_phy_aux_clk_src.clkr.hw
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_sec_phy_pipe_clk = अणु
	.halt_reg = 0x10058,
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x10058,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_sec_phy_pipe_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_video_axi0_clk = अणु
	.halt_reg = 0xb024,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_video_axi0_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_video_axi1_clk = अणु
	.halt_reg = 0xb028,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb028,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_video_axi1_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_video_axic_clk = अणु
	.halt_reg = 0xb02c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb02c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_video_axic_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gdsc usb30_sec_gdsc = अणु
	.gdscr = 0x10004,
	.pd = अणु
		.name = "usb30_sec_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = POLL_CFG_GDSCR,
पूर्ण;

अटल काष्ठा gdsc emac_gdsc = अणु
	.gdscr = 0x6004,
	.pd = अणु
		.name = "emac_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = POLL_CFG_GDSCR,
पूर्ण;

अटल काष्ठा gdsc usb30_prim_gdsc = अणु
	.gdscr = 0xf004,
	.pd = अणु
		.name = "usb30_prim_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = POLL_CFG_GDSCR,
पूर्ण;

अटल काष्ठा gdsc pcie_0_gdsc = अणु
	.gdscr = 0x6b004,
	.pd = अणु
		.name = "pcie_0_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = POLL_CFG_GDSCR,
पूर्ण;

अटल काष्ठा gdsc ufs_card_gdsc = अणु
	.gdscr = 0x75004,
	.pd = अणु
		.name = "ufs_card_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = POLL_CFG_GDSCR,
पूर्ण;

अटल काष्ठा gdsc ufs_phy_gdsc = अणु
	.gdscr = 0x77004,
	.pd = अणु
		.name = "ufs_phy_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = POLL_CFG_GDSCR,
पूर्ण;

अटल काष्ठा gdsc pcie_1_gdsc = अणु
	.gdscr = 0x8d004,
	.pd = अणु
		.name = "pcie_1_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = POLL_CFG_GDSCR,
पूर्ण;

अटल काष्ठा gdsc pcie_2_gdsc = अणु
	.gdscr = 0x9d004,
	.pd = अणु
		.name = "pcie_2_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = POLL_CFG_GDSCR,
पूर्ण;

अटल काष्ठा gdsc ufs_card_2_gdsc = अणु
	.gdscr = 0xa2004,
	.pd = अणु
		.name = "ufs_card_2_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = POLL_CFG_GDSCR,
पूर्ण;

अटल काष्ठा gdsc pcie_3_gdsc = अणु
	.gdscr = 0xa3004,
	.pd = अणु
		.name = "pcie_3_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = POLL_CFG_GDSCR,
पूर्ण;

अटल काष्ठा gdsc usb30_mp_gdsc = अणु
	.gdscr = 0xa6004,
	.pd = अणु
		.name = "usb30_mp_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = POLL_CFG_GDSCR,
पूर्ण;

अटल काष्ठा clk_regmap *gcc_sc8180x_घड़ीs[] = अणु
	[GCC_AGGRE_NOC_PCIE_TBU_CLK] = &gcc_aggre_noc_pcie_tbu_clk.clkr,
	[GCC_AGGRE_UFS_CARD_AXI_CLK] = &gcc_aggre_ufs_card_axi_clk.clkr,
	[GCC_AGGRE_UFS_CARD_AXI_HW_CTL_CLK] = &gcc_aggre_ufs_card_axi_hw_ctl_clk.clkr,
	[GCC_AGGRE_UFS_PHY_AXI_CLK] = &gcc_aggre_ufs_phy_axi_clk.clkr,
	[GCC_AGGRE_UFS_PHY_AXI_HW_CTL_CLK] = &gcc_aggre_ufs_phy_axi_hw_ctl_clk.clkr,
	[GCC_AGGRE_USB3_MP_AXI_CLK] = &gcc_aggre_usb3_mp_axi_clk.clkr,
	[GCC_AGGRE_USB3_PRIM_AXI_CLK] = &gcc_aggre_usb3_prim_axi_clk.clkr,
	[GCC_AGGRE_USB3_SEC_AXI_CLK] = &gcc_aggre_usb3_sec_axi_clk.clkr,
	[GCC_BOOT_ROM_AHB_CLK] = &gcc_boot_rom_ahb_clk.clkr,
	[GCC_CAMERA_HF_AXI_CLK] = &gcc_camera_hf_axi_clk.clkr,
	[GCC_CAMERA_SF_AXI_CLK] = &gcc_camera_sf_axi_clk.clkr,
	[GCC_CFG_NOC_USB3_MP_AXI_CLK] = &gcc_cfg_noc_usb3_mp_axi_clk.clkr,
	[GCC_CFG_NOC_USB3_PRIM_AXI_CLK] = &gcc_cfg_noc_usb3_prim_axi_clk.clkr,
	[GCC_CFG_NOC_USB3_SEC_AXI_CLK] = &gcc_cfg_noc_usb3_sec_axi_clk.clkr,
	[GCC_CPUSS_AHB_CLK] = &gcc_cpuss_ahb_clk.clkr,
	[GCC_CPUSS_AHB_CLK_SRC] = &gcc_cpuss_ahb_clk_src.clkr,
	[GCC_CPUSS_RBCPR_CLK] = &gcc_cpuss_rbcpr_clk.clkr,
	[GCC_DDRSS_GPU_AXI_CLK] = &gcc_ddrss_gpu_axi_clk.clkr,
	[GCC_DISP_HF_AXI_CLK] = &gcc_disp_hf_axi_clk.clkr,
	[GCC_DISP_SF_AXI_CLK] = &gcc_disp_sf_axi_clk.clkr,
	[GCC_EMAC_AXI_CLK] = &gcc_emac_axi_clk.clkr,
	[GCC_EMAC_PTP_CLK] = &gcc_emac_ptp_clk.clkr,
	[GCC_EMAC_PTP_CLK_SRC] = &gcc_emac_ptp_clk_src.clkr,
	[GCC_EMAC_RGMII_CLK] = &gcc_emac_rgmii_clk.clkr,
	[GCC_EMAC_RGMII_CLK_SRC] = &gcc_emac_rgmii_clk_src.clkr,
	[GCC_EMAC_SLV_AHB_CLK] = &gcc_emac_slv_ahb_clk.clkr,
	[GCC_GP1_CLK] = &gcc_gp1_clk.clkr,
	[GCC_GP1_CLK_SRC] = &gcc_gp1_clk_src.clkr,
	[GCC_GP2_CLK] = &gcc_gp2_clk.clkr,
	[GCC_GP2_CLK_SRC] = &gcc_gp2_clk_src.clkr,
	[GCC_GP3_CLK] = &gcc_gp3_clk.clkr,
	[GCC_GP3_CLK_SRC] = &gcc_gp3_clk_src.clkr,
	[GCC_GP4_CLK] = &gcc_gp4_clk.clkr,
	[GCC_GP4_CLK_SRC] = &gcc_gp4_clk_src.clkr,
	[GCC_GP5_CLK] = &gcc_gp5_clk.clkr,
	[GCC_GP5_CLK_SRC] = &gcc_gp5_clk_src.clkr,
	[GCC_GPU_GPLL0_CLK_SRC] = &gcc_gpu_gpll0_clk_src.clkr,
	[GCC_GPU_GPLL0_DIV_CLK_SRC] = &gcc_gpu_gpll0_भाग_clk_src.clkr,
	[GCC_GPU_MEMNOC_GFX_CLK] = &gcc_gpu_memnoc_gfx_clk.clkr,
	[GCC_GPU_SNOC_DVM_GFX_CLK] = &gcc_gpu_snoc_dvm_gfx_clk.clkr,
	[GCC_NPU_AT_CLK] = &gcc_npu_at_clk.clkr,
	[GCC_NPU_AXI_CLK] = &gcc_npu_axi_clk.clkr,
	[GCC_NPU_AXI_CLK_SRC] = &gcc_npu_axi_clk_src.clkr,
	[GCC_NPU_GPLL0_CLK_SRC] = &gcc_npu_gpll0_clk_src.clkr,
	[GCC_NPU_GPLL0_DIV_CLK_SRC] = &gcc_npu_gpll0_भाग_clk_src.clkr,
	[GCC_NPU_TRIG_CLK] = &gcc_npu_trig_clk.clkr,
	[GCC_PCIE0_PHY_REFGEN_CLK] = &gcc_pcie0_phy_refgen_clk.clkr,
	[GCC_PCIE1_PHY_REFGEN_CLK] = &gcc_pcie1_phy_refgen_clk.clkr,
	[GCC_PCIE2_PHY_REFGEN_CLK] = &gcc_pcie2_phy_refgen_clk.clkr,
	[GCC_PCIE3_PHY_REFGEN_CLK] = &gcc_pcie3_phy_refgen_clk.clkr,
	[GCC_PCIE_0_AUX_CLK] = &gcc_pcie_0_aux_clk.clkr,
	[GCC_PCIE_0_AUX_CLK_SRC] = &gcc_pcie_0_aux_clk_src.clkr,
	[GCC_PCIE_0_CFG_AHB_CLK] = &gcc_pcie_0_cfg_ahb_clk.clkr,
	[GCC_PCIE_0_CLKREF_CLK] = &gcc_pcie_0_clkref_clk.clkr,
	[GCC_PCIE_0_MSTR_AXI_CLK] = &gcc_pcie_0_mstr_axi_clk.clkr,
	[GCC_PCIE_0_PIPE_CLK] = &gcc_pcie_0_pipe_clk.clkr,
	[GCC_PCIE_0_SLV_AXI_CLK] = &gcc_pcie_0_slv_axi_clk.clkr,
	[GCC_PCIE_0_SLV_Q2A_AXI_CLK] = &gcc_pcie_0_slv_q2a_axi_clk.clkr,
	[GCC_PCIE_1_AUX_CLK] = &gcc_pcie_1_aux_clk.clkr,
	[GCC_PCIE_1_AUX_CLK_SRC] = &gcc_pcie_1_aux_clk_src.clkr,
	[GCC_PCIE_1_CFG_AHB_CLK] = &gcc_pcie_1_cfg_ahb_clk.clkr,
	[GCC_PCIE_1_CLKREF_CLK] = &gcc_pcie_1_clkref_clk.clkr,
	[GCC_PCIE_1_MSTR_AXI_CLK] = &gcc_pcie_1_mstr_axi_clk.clkr,
	[GCC_PCIE_1_PIPE_CLK] = &gcc_pcie_1_pipe_clk.clkr,
	[GCC_PCIE_1_SLV_AXI_CLK] = &gcc_pcie_1_slv_axi_clk.clkr,
	[GCC_PCIE_1_SLV_Q2A_AXI_CLK] = &gcc_pcie_1_slv_q2a_axi_clk.clkr,
	[GCC_PCIE_2_AUX_CLK] = &gcc_pcie_2_aux_clk.clkr,
	[GCC_PCIE_2_AUX_CLK_SRC] = &gcc_pcie_2_aux_clk_src.clkr,
	[GCC_PCIE_2_CFG_AHB_CLK] = &gcc_pcie_2_cfg_ahb_clk.clkr,
	[GCC_PCIE_2_CLKREF_CLK] = &gcc_pcie_2_clkref_clk.clkr,
	[GCC_PCIE_2_MSTR_AXI_CLK] = &gcc_pcie_2_mstr_axi_clk.clkr,
	[GCC_PCIE_2_PIPE_CLK] = &gcc_pcie_2_pipe_clk.clkr,
	[GCC_PCIE_2_SLV_AXI_CLK] = &gcc_pcie_2_slv_axi_clk.clkr,
	[GCC_PCIE_2_SLV_Q2A_AXI_CLK] = &gcc_pcie_2_slv_q2a_axi_clk.clkr,
	[GCC_PCIE_3_AUX_CLK] = &gcc_pcie_3_aux_clk.clkr,
	[GCC_PCIE_3_AUX_CLK_SRC] = &gcc_pcie_3_aux_clk_src.clkr,
	[GCC_PCIE_3_CFG_AHB_CLK] = &gcc_pcie_3_cfg_ahb_clk.clkr,
	[GCC_PCIE_3_CLKREF_CLK] = &gcc_pcie_3_clkref_clk.clkr,
	[GCC_PCIE_3_MSTR_AXI_CLK] = &gcc_pcie_3_mstr_axi_clk.clkr,
	[GCC_PCIE_3_PIPE_CLK] = &gcc_pcie_3_pipe_clk.clkr,
	[GCC_PCIE_3_SLV_AXI_CLK] = &gcc_pcie_3_slv_axi_clk.clkr,
	[GCC_PCIE_3_SLV_Q2A_AXI_CLK] = &gcc_pcie_3_slv_q2a_axi_clk.clkr,
	[GCC_PCIE_PHY_AUX_CLK] = &gcc_pcie_phy_aux_clk.clkr,
	[GCC_PCIE_PHY_REFGEN_CLK_SRC] = &gcc_pcie_phy_refgen_clk_src.clkr,
	[GCC_PDM2_CLK] = &gcc_pdm2_clk.clkr,
	[GCC_PDM2_CLK_SRC] = &gcc_pdm2_clk_src.clkr,
	[GCC_PDM_AHB_CLK] = &gcc_pdm_ahb_clk.clkr,
	[GCC_PDM_XO4_CLK] = &gcc_pdm_xo4_clk.clkr,
	[GCC_PRNG_AHB_CLK] = &gcc_prng_ahb_clk.clkr,
	[GCC_QMIP_CAMERA_NRT_AHB_CLK] = &gcc_qmip_camera_nrt_ahb_clk.clkr,
	[GCC_QMIP_CAMERA_RT_AHB_CLK] = &gcc_qmip_camera_rt_ahb_clk.clkr,
	[GCC_QMIP_DISP_AHB_CLK] = &gcc_qmip_disp_ahb_clk.clkr,
	[GCC_QMIP_VIDEO_CVP_AHB_CLK] = &gcc_qmip_video_cvp_ahb_clk.clkr,
	[GCC_QMIP_VIDEO_VCODEC_AHB_CLK] = &gcc_qmip_video_vcodec_ahb_clk.clkr,
	[GCC_QSPI_1_CNOC_PERIPH_AHB_CLK] = &gcc_qspi_1_cnoc_periph_ahb_clk.clkr,
	[GCC_QSPI_1_CORE_CLK] = &gcc_qspi_1_core_clk.clkr,
	[GCC_QSPI_1_CORE_CLK_SRC] = &gcc_qspi_1_core_clk_src.clkr,
	[GCC_QSPI_CNOC_PERIPH_AHB_CLK] = &gcc_qspi_cnoc_periph_ahb_clk.clkr,
	[GCC_QSPI_CORE_CLK] = &gcc_qspi_core_clk.clkr,
	[GCC_QSPI_CORE_CLK_SRC] = &gcc_qspi_core_clk_src.clkr,
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
	[GCC_QUPV3_WRAP2_S0_CLK] = &gcc_qupv3_wrap2_s0_clk.clkr,
	[GCC_QUPV3_WRAP2_S0_CLK_SRC] = &gcc_qupv3_wrap2_s0_clk_src.clkr,
	[GCC_QUPV3_WRAP2_S1_CLK] = &gcc_qupv3_wrap2_s1_clk.clkr,
	[GCC_QUPV3_WRAP2_S1_CLK_SRC] = &gcc_qupv3_wrap2_s1_clk_src.clkr,
	[GCC_QUPV3_WRAP2_S2_CLK] = &gcc_qupv3_wrap2_s2_clk.clkr,
	[GCC_QUPV3_WRAP2_S2_CLK_SRC] = &gcc_qupv3_wrap2_s2_clk_src.clkr,
	[GCC_QUPV3_WRAP2_S3_CLK] = &gcc_qupv3_wrap2_s3_clk.clkr,
	[GCC_QUPV3_WRAP2_S3_CLK_SRC] = &gcc_qupv3_wrap2_s3_clk_src.clkr,
	[GCC_QUPV3_WRAP2_S4_CLK] = &gcc_qupv3_wrap2_s4_clk.clkr,
	[GCC_QUPV3_WRAP2_S4_CLK_SRC] = &gcc_qupv3_wrap2_s4_clk_src.clkr,
	[GCC_QUPV3_WRAP2_S5_CLK] = &gcc_qupv3_wrap2_s5_clk.clkr,
	[GCC_QUPV3_WRAP2_S5_CLK_SRC] = &gcc_qupv3_wrap2_s5_clk_src.clkr,
	[GCC_QUPV3_WRAP_0_M_AHB_CLK] = &gcc_qupv3_wrap_0_m_ahb_clk.clkr,
	[GCC_QUPV3_WRAP_0_S_AHB_CLK] = &gcc_qupv3_wrap_0_s_ahb_clk.clkr,
	[GCC_QUPV3_WRAP_1_M_AHB_CLK] = &gcc_qupv3_wrap_1_m_ahb_clk.clkr,
	[GCC_QUPV3_WRAP_1_S_AHB_CLK] = &gcc_qupv3_wrap_1_s_ahb_clk.clkr,
	[GCC_QUPV3_WRAP_2_M_AHB_CLK] = &gcc_qupv3_wrap_2_m_ahb_clk.clkr,
	[GCC_QUPV3_WRAP_2_S_AHB_CLK] = &gcc_qupv3_wrap_2_s_ahb_clk.clkr,
	[GCC_SDCC2_AHB_CLK] = &gcc_sdcc2_ahb_clk.clkr,
	[GCC_SDCC2_APPS_CLK] = &gcc_sdcc2_apps_clk.clkr,
	[GCC_SDCC2_APPS_CLK_SRC] = &gcc_sdcc2_apps_clk_src.clkr,
	[GCC_SDCC4_AHB_CLK] = &gcc_sdcc4_ahb_clk.clkr,
	[GCC_SDCC4_APPS_CLK] = &gcc_sdcc4_apps_clk.clkr,
	[GCC_SDCC4_APPS_CLK_SRC] = &gcc_sdcc4_apps_clk_src.clkr,
	[GCC_SYS_NOC_CPUSS_AHB_CLK] = &gcc_sys_noc_cpuss_ahb_clk.clkr,
	[GCC_TSIF_AHB_CLK] = &gcc_tsअगर_ahb_clk.clkr,
	[GCC_TSIF_INACTIVITY_TIMERS_CLK] = &gcc_tsअगर_inactivity_समयrs_clk.clkr,
	[GCC_TSIF_REF_CLK] = &gcc_tsअगर_ref_clk.clkr,
	[GCC_TSIF_REF_CLK_SRC] = &gcc_tsअगर_ref_clk_src.clkr,
	[GCC_UFS_CARD_2_AHB_CLK] = &gcc_ufs_card_2_ahb_clk.clkr,
	[GCC_UFS_CARD_2_AXI_CLK] = &gcc_ufs_card_2_axi_clk.clkr,
	[GCC_UFS_CARD_2_AXI_CLK_SRC] = &gcc_ufs_card_2_axi_clk_src.clkr,
	[GCC_UFS_CARD_2_ICE_CORE_CLK] = &gcc_ufs_card_2_ice_core_clk.clkr,
	[GCC_UFS_CARD_2_ICE_CORE_CLK_SRC] = &gcc_ufs_card_2_ice_core_clk_src.clkr,
	[GCC_UFS_CARD_2_PHY_AUX_CLK] = &gcc_ufs_card_2_phy_aux_clk.clkr,
	[GCC_UFS_CARD_2_PHY_AUX_CLK_SRC] = &gcc_ufs_card_2_phy_aux_clk_src.clkr,
	[GCC_UFS_CARD_2_RX_SYMBOL_0_CLK] = &gcc_ufs_card_2_rx_symbol_0_clk.clkr,
	[GCC_UFS_CARD_2_RX_SYMBOL_1_CLK] = &gcc_ufs_card_2_rx_symbol_1_clk.clkr,
	[GCC_UFS_CARD_2_TX_SYMBOL_0_CLK] = &gcc_ufs_card_2_tx_symbol_0_clk.clkr,
	[GCC_UFS_CARD_2_UNIPRO_CORE_CLK] = &gcc_ufs_card_2_unipro_core_clk.clkr,
	[GCC_UFS_CARD_2_UNIPRO_CORE_CLK_SRC] = &gcc_ufs_card_2_unipro_core_clk_src.clkr,
	[GCC_UFS_CARD_AHB_CLK] = &gcc_ufs_card_ahb_clk.clkr,
	[GCC_UFS_CARD_AXI_CLK] = &gcc_ufs_card_axi_clk.clkr,
	[GCC_UFS_CARD_AXI_CLK_SRC] = &gcc_ufs_card_axi_clk_src.clkr,
	[GCC_UFS_CARD_AXI_HW_CTL_CLK] = &gcc_ufs_card_axi_hw_ctl_clk.clkr,
	[GCC_UFS_CARD_ICE_CORE_CLK] = &gcc_ufs_card_ice_core_clk.clkr,
	[GCC_UFS_CARD_ICE_CORE_CLK_SRC] = &gcc_ufs_card_ice_core_clk_src.clkr,
	[GCC_UFS_CARD_ICE_CORE_HW_CTL_CLK] = &gcc_ufs_card_ice_core_hw_ctl_clk.clkr,
	[GCC_UFS_CARD_PHY_AUX_CLK] = &gcc_ufs_card_phy_aux_clk.clkr,
	[GCC_UFS_CARD_PHY_AUX_CLK_SRC] = &gcc_ufs_card_phy_aux_clk_src.clkr,
	[GCC_UFS_CARD_PHY_AUX_HW_CTL_CLK] = &gcc_ufs_card_phy_aux_hw_ctl_clk.clkr,
	[GCC_UFS_CARD_RX_SYMBOL_0_CLK] = &gcc_ufs_card_rx_symbol_0_clk.clkr,
	[GCC_UFS_CARD_RX_SYMBOL_1_CLK] = &gcc_ufs_card_rx_symbol_1_clk.clkr,
	[GCC_UFS_CARD_TX_SYMBOL_0_CLK] = &gcc_ufs_card_tx_symbol_0_clk.clkr,
	[GCC_UFS_CARD_UNIPRO_CORE_CLK] = &gcc_ufs_card_unipro_core_clk.clkr,
	[GCC_UFS_CARD_UNIPRO_CORE_CLK_SRC] = &gcc_ufs_card_unipro_core_clk_src.clkr,
	[GCC_UFS_CARD_UNIPRO_CORE_HW_CTL_CLK] = &gcc_ufs_card_unipro_core_hw_ctl_clk.clkr,
	[GCC_UFS_PHY_AHB_CLK] = &gcc_ufs_phy_ahb_clk.clkr,
	[GCC_UFS_PHY_AXI_CLK] = &gcc_ufs_phy_axi_clk.clkr,
	[GCC_UFS_PHY_AXI_CLK_SRC] = &gcc_ufs_phy_axi_clk_src.clkr,
	[GCC_UFS_PHY_AXI_HW_CTL_CLK] = &gcc_ufs_phy_axi_hw_ctl_clk.clkr,
	[GCC_UFS_PHY_ICE_CORE_CLK] = &gcc_ufs_phy_ice_core_clk.clkr,
	[GCC_UFS_PHY_ICE_CORE_CLK_SRC] = &gcc_ufs_phy_ice_core_clk_src.clkr,
	[GCC_UFS_PHY_ICE_CORE_HW_CTL_CLK] = &gcc_ufs_phy_ice_core_hw_ctl_clk.clkr,
	[GCC_UFS_PHY_PHY_AUX_CLK] = &gcc_ufs_phy_phy_aux_clk.clkr,
	[GCC_UFS_PHY_PHY_AUX_CLK_SRC] = &gcc_ufs_phy_phy_aux_clk_src.clkr,
	[GCC_UFS_PHY_PHY_AUX_HW_CTL_CLK] = &gcc_ufs_phy_phy_aux_hw_ctl_clk.clkr,
	[GCC_UFS_PHY_RX_SYMBOL_0_CLK] = &gcc_ufs_phy_rx_symbol_0_clk.clkr,
	[GCC_UFS_PHY_RX_SYMBOL_1_CLK] = &gcc_ufs_phy_rx_symbol_1_clk.clkr,
	[GCC_UFS_PHY_TX_SYMBOL_0_CLK] = &gcc_ufs_phy_tx_symbol_0_clk.clkr,
	[GCC_UFS_PHY_UNIPRO_CORE_CLK] = &gcc_ufs_phy_unipro_core_clk.clkr,
	[GCC_UFS_PHY_UNIPRO_CORE_CLK_SRC] = &gcc_ufs_phy_unipro_core_clk_src.clkr,
	[GCC_UFS_PHY_UNIPRO_CORE_HW_CTL_CLK] = &gcc_ufs_phy_unipro_core_hw_ctl_clk.clkr,
	[GCC_USB30_MP_MASTER_CLK] = &gcc_usb30_mp_master_clk.clkr,
	[GCC_USB30_MP_MASTER_CLK_SRC] = &gcc_usb30_mp_master_clk_src.clkr,
	[GCC_USB30_MP_MOCK_UTMI_CLK] = &gcc_usb30_mp_mock_uपंचांगi_clk.clkr,
	[GCC_USB30_MP_MOCK_UTMI_CLK_SRC] = &gcc_usb30_mp_mock_uपंचांगi_clk_src.clkr,
	[GCC_USB30_MP_SLEEP_CLK] = &gcc_usb30_mp_sleep_clk.clkr,
	[GCC_USB30_PRIM_MASTER_CLK] = &gcc_usb30_prim_master_clk.clkr,
	[GCC_USB30_PRIM_MASTER_CLK_SRC] = &gcc_usb30_prim_master_clk_src.clkr,
	[GCC_USB30_PRIM_MOCK_UTMI_CLK] = &gcc_usb30_prim_mock_uपंचांगi_clk.clkr,
	[GCC_USB30_PRIM_MOCK_UTMI_CLK_SRC] = &gcc_usb30_prim_mock_uपंचांगi_clk_src.clkr,
	[GCC_USB30_PRIM_SLEEP_CLK] = &gcc_usb30_prim_sleep_clk.clkr,
	[GCC_USB30_SEC_MASTER_CLK] = &gcc_usb30_sec_master_clk.clkr,
	[GCC_USB30_SEC_MASTER_CLK_SRC] = &gcc_usb30_sec_master_clk_src.clkr,
	[GCC_USB30_SEC_MOCK_UTMI_CLK] = &gcc_usb30_sec_mock_uपंचांगi_clk.clkr,
	[GCC_USB30_SEC_MOCK_UTMI_CLK_SRC] = &gcc_usb30_sec_mock_uपंचांगi_clk_src.clkr,
	[GCC_USB30_SEC_SLEEP_CLK] = &gcc_usb30_sec_sleep_clk.clkr,
	[GCC_USB3_MP_PHY_AUX_CLK] = &gcc_usb3_mp_phy_aux_clk.clkr,
	[GCC_USB3_MP_PHY_AUX_CLK_SRC] = &gcc_usb3_mp_phy_aux_clk_src.clkr,
	[GCC_USB3_MP_PHY_COM_AUX_CLK] = &gcc_usb3_mp_phy_com_aux_clk.clkr,
	[GCC_USB3_MP_PHY_PIPE_0_CLK] = &gcc_usb3_mp_phy_pipe_0_clk.clkr,
	[GCC_USB3_MP_PHY_PIPE_1_CLK] = &gcc_usb3_mp_phy_pipe_1_clk.clkr,
	[GCC_USB3_PRIM_CLKREF_CLK] = &gcc_usb3_prim_clkref_clk.clkr,
	[GCC_USB3_PRIM_PHY_AUX_CLK] = &gcc_usb3_prim_phy_aux_clk.clkr,
	[GCC_USB3_PRIM_PHY_AUX_CLK_SRC] = &gcc_usb3_prim_phy_aux_clk_src.clkr,
	[GCC_USB3_PRIM_PHY_COM_AUX_CLK] = &gcc_usb3_prim_phy_com_aux_clk.clkr,
	[GCC_USB3_PRIM_PHY_PIPE_CLK] = &gcc_usb3_prim_phy_pipe_clk.clkr,
	[GCC_USB3_SEC_CLKREF_CLK] = &gcc_usb3_sec_clkref_clk.clkr,
	[GCC_USB3_SEC_PHY_AUX_CLK] = &gcc_usb3_sec_phy_aux_clk.clkr,
	[GCC_USB3_SEC_PHY_AUX_CLK_SRC] = &gcc_usb3_sec_phy_aux_clk_src.clkr,
	[GCC_USB3_SEC_PHY_COM_AUX_CLK] = &gcc_usb3_sec_phy_com_aux_clk.clkr,
	[GCC_USB3_SEC_PHY_PIPE_CLK] = &gcc_usb3_sec_phy_pipe_clk.clkr,
	[GCC_VIDEO_AXI0_CLK] = &gcc_video_axi0_clk.clkr,
	[GCC_VIDEO_AXI1_CLK] = &gcc_video_axi1_clk.clkr,
	[GCC_VIDEO_AXIC_CLK] = &gcc_video_axic_clk.clkr,
	[GPLL0] = &gpll0.clkr,
	[GPLL0_OUT_EVEN] = &gpll0_out_even.clkr,
	[GPLL1] = &gpll1.clkr,
	[GPLL4] = &gpll4.clkr,
	[GPLL7] = &gpll7.clkr,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map gcc_sc8180x_resets[] = अणु
	[GCC_EMAC_BCR] = अणु 0x6000 पूर्ण,
	[GCC_GPU_BCR] = अणु 0x71000 पूर्ण,
	[GCC_MMSS_BCR] = अणु 0xb000 पूर्ण,
	[GCC_NPU_BCR] = अणु 0x4d000 पूर्ण,
	[GCC_PCIE_0_BCR] = अणु 0x6b000 पूर्ण,
	[GCC_PCIE_0_PHY_BCR] = अणु 0x6c01c पूर्ण,
	[GCC_PCIE_1_BCR] = अणु 0x8d000 पूर्ण,
	[GCC_PCIE_1_PHY_BCR] = अणु 0x8e01c पूर्ण,
	[GCC_PCIE_2_BCR] = अणु 0x9d000 पूर्ण,
	[GCC_PCIE_2_PHY_BCR] = अणु 0xa701c पूर्ण,
	[GCC_PCIE_3_BCR] = अणु 0xa3000 पूर्ण,
	[GCC_PCIE_3_PHY_BCR] = अणु 0xa801c पूर्ण,
	[GCC_PCIE_PHY_BCR] = अणु 0x6f000 पूर्ण,
	[GCC_PDM_BCR] = अणु 0x33000 पूर्ण,
	[GCC_PRNG_BCR] = अणु 0x34000 पूर्ण,
	[GCC_QSPI_1_BCR] = अणु 0x4a000 पूर्ण,
	[GCC_QSPI_BCR] = अणु 0x24008 पूर्ण,
	[GCC_QUPV3_WRAPPER_0_BCR] = अणु 0x17000 पूर्ण,
	[GCC_QUPV3_WRAPPER_1_BCR] = अणु 0x18000 पूर्ण,
	[GCC_QUPV3_WRAPPER_2_BCR] = अणु 0x1e000 पूर्ण,
	[GCC_QUSB2PHY_5_BCR] = अणु 0x12010 पूर्ण,
	[GCC_QUSB2PHY_MP0_BCR] = अणु 0x12008 पूर्ण,
	[GCC_QUSB2PHY_MP1_BCR] = अणु 0x1200c पूर्ण,
	[GCC_QUSB2PHY_PRIM_BCR] = अणु 0x12000 पूर्ण,
	[GCC_QUSB2PHY_SEC_BCR] = अणु 0x12004 पूर्ण,
	[GCC_USB3_PHY_PRIM_SP0_BCR] = अणु 0x50000 पूर्ण,
	[GCC_USB3_PHY_PRIM_SP1_BCR] = अणु 0x50004 पूर्ण,
	[GCC_USB3_DP_PHY_PRIM_SP0_BCR] = अणु 0x50010 पूर्ण,
	[GCC_USB3_DP_PHY_PRIM_SP1_BCR] = अणु 0x50014 पूर्ण,
	[GCC_USB3_PHY_SEC_BCR] = अणु 0x50018 पूर्ण,
	[GCC_USB3PHY_PHY_SEC_BCR] = अणु 0x5001c पूर्ण,
	[GCC_USB3_DP_PHY_SEC_BCR] = अणु 0x50020 पूर्ण,
	[GCC_SDCC2_BCR] = अणु 0x14000 पूर्ण,
	[GCC_SDCC4_BCR] = अणु 0x16000 पूर्ण,
	[GCC_TSIF_BCR] = अणु 0x36000 पूर्ण,
	[GCC_UFS_CARD_2_BCR] = अणु 0xa2000 पूर्ण,
	[GCC_UFS_CARD_BCR] = अणु 0x75000 पूर्ण,
	[GCC_UFS_PHY_BCR] = अणु 0x77000 पूर्ण,
	[GCC_USB30_MP_BCR] = अणु 0xa6000 पूर्ण,
	[GCC_USB30_PRIM_BCR] = अणु 0xf000 पूर्ण,
	[GCC_USB30_SEC_BCR] = अणु 0x10000 पूर्ण,
	[GCC_USB_PHY_CFG_AHB2PHY_BCR] = अणु 0x6a000 पूर्ण,
	[GCC_VIDEO_AXIC_CLK_BCR] = अणु 0xb02c, 2 पूर्ण,
	[GCC_VIDEO_AXI0_CLK_BCR] = अणु 0xb024, 2 पूर्ण,
	[GCC_VIDEO_AXI1_CLK_BCR] = अणु 0xb028, 2 पूर्ण,
पूर्ण;

अटल काष्ठा gdsc *gcc_sc8180x_gdscs[] = अणु
	[EMAC_GDSC] = &emac_gdsc,
	[PCIE_0_GDSC] = &pcie_0_gdsc,
	[PCIE_1_GDSC] = &pcie_1_gdsc,
	[PCIE_2_GDSC] = &pcie_2_gdsc,
	[PCIE_3_GDSC] = &pcie_3_gdsc,
	[UFS_CARD_GDSC] = &ufs_card_gdsc,
	[UFS_CARD_2_GDSC] = &ufs_card_2_gdsc,
	[UFS_PHY_GDSC] = &ufs_phy_gdsc,
	[USB30_MP_GDSC] = &usb30_mp_gdsc,
	[USB30_PRIM_GDSC] = &usb30_prim_gdsc,
	[USB30_SEC_GDSC] = &usb30_sec_gdsc,
पूर्ण;

अटल स्थिर काष्ठा regmap_config gcc_sc8180x_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0xc0004,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc gcc_sc8180x_desc = अणु
	.config = &gcc_sc8180x_regmap_config,
	.clks = gcc_sc8180x_घड़ीs,
	.num_clks = ARRAY_SIZE(gcc_sc8180x_घड़ीs),
	.resets = gcc_sc8180x_resets,
	.num_resets = ARRAY_SIZE(gcc_sc8180x_resets),
	.gdscs = gcc_sc8180x_gdscs,
	.num_gdscs = ARRAY_SIZE(gcc_sc8180x_gdscs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id gcc_sc8180x_match_table[] = अणु
	अणु .compatible = "qcom,gcc-sc8180x" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gcc_sc8180x_match_table);

अटल पूर्णांक gcc_sc8180x_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;

	regmap = qcom_cc_map(pdev, &gcc_sc8180x_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/*
	 * Enable the following always-on घड़ीs:
	 * GCC_VIDEO_AHB_CLK, GCC_CAMERA_AHB_CLK, GCC_DISP_AHB_CLK,
	 * GCC_VIDEO_XO_CLK, GCC_CAMERA_XO_CLK, GCC_DISP_XO_CLK,
	 * GCC_CPUSS_GNOC_CLK, GCC_CPUSS_DVM_BUS_CLK, GCC_NPU_CFG_AHB_CLK and
	 * GCC_GPU_CFG_AHB_CLK
	 */
	regmap_update_bits(regmap, 0xb004, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0xb008, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0xb00c, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0xb040, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0xb044, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0xb048, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0x48004, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0x48190, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0x4d004, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0x71004, BIT(0), BIT(0));

	/* Disable the GPLL0 active input to NPU and GPU via MISC रेजिस्टरs */
	regmap_update_bits(regmap, 0x4d110, 0x3, 0x3);
	regmap_update_bits(regmap, 0x71028, 0x3, 0x3);

	वापस qcom_cc_really_probe(pdev, &gcc_sc8180x_desc, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver gcc_sc8180x_driver = अणु
	.probe		= gcc_sc8180x_probe,
	.driver		= अणु
		.name	= "gcc-sc8180x",
		.of_match_table = gcc_sc8180x_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init gcc_sc8180x_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&gcc_sc8180x_driver);
पूर्ण
core_initcall(gcc_sc8180x_init);

अटल व्योम __निकास gcc_sc8180x_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&gcc_sc8180x_driver);
पूर्ण
module_निकास(gcc_sc8180x_निकास);

MODULE_DESCRIPTION("QTI GCC SC8180x driver");
MODULE_LICENSE("GPL v2");
