<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2019-2021, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/qcom,gcc-sc7180.h>

#समावेश "clk-alpha-pll.h"
#समावेश "clk-branch.h"
#समावेश "clk-rcg.h"
#समावेश "clk-regmap.h"
#समावेश "common.h"
#समावेश "gdsc.h"
#समावेश "reset.h"

क्रमागत अणु
	P_BI_TCXO,
	P_CORE_BI_PLL_TEST_SE,
	P_GPLL0_OUT_EVEN,
	P_GPLL0_OUT_MAIN,
	P_GPLL1_OUT_MAIN,
	P_GPLL4_OUT_MAIN,
	P_GPLL6_OUT_MAIN,
	P_GPLL7_OUT_MAIN,
	P_SLEEP_CLK,
पूर्ण;

अटल काष्ठा clk_alpha_pll gpll0 = अणु
	.offset = 0x0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr = अणु
		.enable_reg = 0x52010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpll0",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
				.name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_fabia_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable post_भाग_प्रकारable_gpll0_out_even[] = अणु
	अणु 0x1, 2 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll0_out_even = अणु
	.offset = 0x0,
	.post_भाग_shअगरt = 8,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_gpll0_out_even,
	.num_post_भाग = ARRAY_SIZE(post_भाग_प्रकारable_gpll0_out_even),
	.width = 4,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll0_out_even",
		.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
			&gpll0.clkr.hw,
		पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor gcc_pll0_मुख्य_भाग_cभाग = अणु
	.mult = 1,
	.भाग = 2,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_pll0_main_div_cdiv",
		.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
			&gpll0.clkr.hw,
		पूर्ण,
		.num_parents = 1,
		.ops = &clk_fixed_factor_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll gpll1 = अणु
	.offset = 0x01000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr = अणु
		.enable_reg = 0x52010,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpll1",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
				.name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_fabia_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll gpll4 = अणु
	.offset = 0x76000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr = अणु
		.enable_reg = 0x52010,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpll4",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
				.name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_fabia_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll gpll6 = अणु
	.offset = 0x13000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr = अणु
		.enable_reg = 0x52010,
		.enable_mask = BIT(6),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpll6",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
				.name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_fabia_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll gpll7 = अणु
	.offset = 0x27000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr = अणु
		.enable_reg = 0x52010,
		.enable_mask = BIT(7),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpll7",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
				.name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_fabia_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_0[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_GPLL0_OUT_EVEN, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_0[] = अणु
	अणु .fw_name = "bi_tcxo", .name = "bi_tcxo" पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .hw = &gpll0_out_even.clkr.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_0_ao[] = अणु
	अणु .fw_name = "bi_tcxo_ao", .name = "bi_tcxo_ao" पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .hw = &gpll0_out_even.clkr.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_1[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_GPLL6_OUT_MAIN, 2 पूर्ण,
	अणु P_GPLL0_OUT_EVEN, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_1[] = अणु
	अणु .fw_name = "bi_tcxo", .name = "bi_tcxo" पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .hw = &gpll6.clkr.hw पूर्ण,
	अणु .hw = &gpll0_out_even.clkr.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_2[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_GPLL1_OUT_MAIN, 4 पूर्ण,
	अणु P_GPLL4_OUT_MAIN, 5 पूर्ण,
	अणु P_GPLL0_OUT_EVEN, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_2[] = अणु
	अणु .fw_name = "bi_tcxo", .name = "bi_tcxo" पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .hw = &gpll1.clkr.hw पूर्ण,
	अणु .hw = &gpll4.clkr.hw पूर्ण,
	अणु .hw = &gpll0_out_even.clkr.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_3[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_3[] = अणु
	अणु .fw_name = "bi_tcxo", .name = "bi_tcxo" पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_4[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_SLEEP_CLK, 5 पूर्ण,
	अणु P_GPLL0_OUT_EVEN, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_4[] = अणु
	अणु .fw_name = "bi_tcxo", .name = "bi_tcxo" पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .fw_name = "sleep_clk", .name = "sleep_clk" पूर्ण,
	अणु .hw = &gpll0_out_even.clkr.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_5[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_GPLL7_OUT_MAIN, 3 पूर्ण,
	अणु P_GPLL0_OUT_EVEN, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_5[] = अणु
	अणु .fw_name = "bi_tcxo", .name = "bi_tcxo" पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .hw = &gpll7.clkr.hw पूर्ण,
	अणु .hw = &gpll0_out_even.clkr.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_6[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_SLEEP_CLK, 5 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_6[] = अणु
	अणु .fw_name = "bi_tcxo", .name = "bi_tcxo" पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .fw_name = "sleep_clk", .name = "sleep_clk" पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_cpuss_ahb_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
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
		.parent_data = gcc_parent_data_0_ao,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0_ao),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
		पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_gp1_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(25000000, P_GPLL0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GPLL0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPLL0_OUT_EVEN, 3, 0, 0),
	F(200000000, P_GPLL0_OUT_EVEN, 1.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_gp1_clk_src = अणु
	.cmd_rcgr = 0x64004,
	.mnd_width = 8,
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
	.mnd_width = 8,
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
	.mnd_width = 8,
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

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_pdm2_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(60000000, P_GPLL0_OUT_EVEN, 5, 0, 0),
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
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_qspi_core_clk_src[] = अणु
	F(75000000, P_GPLL0_OUT_EVEN, 4, 0, 0),
	F(150000000, P_GPLL0_OUT_EVEN, 2, 0, 0),
	F(300000000, P_GPLL0_OUT_EVEN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qspi_core_clk_src = अणु
	.cmd_rcgr = 0x4b00c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_2,
	.freq_tbl = ftbl_gcc_qspi_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_qspi_core_clk_src",
		.parent_data = gcc_parent_data_2,
		.num_parents = ARRAY_SIZE(gcc_parent_data_2),
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
	F(51200000, P_GPLL6_OUT_MAIN, 7.5, 0, 0),
	F(64000000, P_GPLL0_OUT_EVEN, 1, 16, 75),
	F(75000000, P_GPLL0_OUT_EVEN, 4, 0, 0),
	F(80000000, P_GPLL0_OUT_EVEN, 1, 4, 15),
	F(96000000, P_GPLL0_OUT_EVEN, 1, 8, 25),
	F(100000000, P_GPLL0_OUT_EVEN, 3, 0, 0),
	F(102400000, P_GPLL0_OUT_EVEN, 1, 128, 375),
	F(112000000, P_GPLL0_OUT_EVEN, 1, 28, 75),
	F(117964800, P_GPLL0_OUT_EVEN, 1, 6144, 15625),
	F(120000000, P_GPLL0_OUT_EVEN, 2.5, 0, 0),
	F(128000000, P_GPLL6_OUT_MAIN, 3, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s0_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s0_clk_src",
	.parent_data = gcc_parent_data_1,
	.num_parents = ARRAY_SIZE(gcc_parent_data_1),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s0_clk_src = अणु
	.cmd_rcgr = 0x17034,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s0_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s1_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s1_clk_src",
	.parent_data = gcc_parent_data_1,
	.num_parents = ARRAY_SIZE(gcc_parent_data_1),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s1_clk_src = अणु
	.cmd_rcgr = 0x17164,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s1_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s2_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s2_clk_src",
	.parent_data = gcc_parent_data_1,
	.num_parents = ARRAY_SIZE(gcc_parent_data_1),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s2_clk_src = अणु
	.cmd_rcgr = 0x17294,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s2_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s3_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s3_clk_src",
	.parent_data = gcc_parent_data_1,
	.num_parents = ARRAY_SIZE(gcc_parent_data_1),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s3_clk_src = अणु
	.cmd_rcgr = 0x173c4,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s3_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s4_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s4_clk_src",
	.parent_data = gcc_parent_data_1,
	.num_parents = ARRAY_SIZE(gcc_parent_data_1),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s4_clk_src = अणु
	.cmd_rcgr = 0x174f4,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s4_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s5_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s5_clk_src",
	.parent_data = gcc_parent_data_1,
	.num_parents = ARRAY_SIZE(gcc_parent_data_1),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s5_clk_src = अणु
	.cmd_rcgr = 0x17624,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s5_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap1_s0_clk_src_init = अणु
	.name = "gcc_qupv3_wrap1_s0_clk_src",
	.parent_data = gcc_parent_data_1,
	.num_parents = ARRAY_SIZE(gcc_parent_data_1),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s0_clk_src = अणु
	.cmd_rcgr = 0x18018,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap1_s0_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap1_s1_clk_src_init = अणु
	.name = "gcc_qupv3_wrap1_s1_clk_src",
	.parent_data = gcc_parent_data_1,
	.num_parents = ARRAY_SIZE(gcc_parent_data_1),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s1_clk_src = अणु
	.cmd_rcgr = 0x18148,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap1_s1_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap1_s2_clk_src_init = अणु
	.name = "gcc_qupv3_wrap1_s2_clk_src",
	.parent_data = gcc_parent_data_1,
	.num_parents = ARRAY_SIZE(gcc_parent_data_1),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s2_clk_src = अणु
	.cmd_rcgr = 0x18278,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap1_s2_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap1_s3_clk_src_init = अणु
	.name = "gcc_qupv3_wrap1_s3_clk_src",
	.parent_data = gcc_parent_data_1,
	.num_parents = ARRAY_SIZE(gcc_parent_data_1),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s3_clk_src = अणु
	.cmd_rcgr = 0x183a8,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap1_s3_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap1_s4_clk_src_init = अणु
	.name = "gcc_qupv3_wrap1_s4_clk_src",
	.parent_data = gcc_parent_data_1,
	.num_parents = ARRAY_SIZE(gcc_parent_data_1),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s4_clk_src = अणु
	.cmd_rcgr = 0x184d8,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap1_s4_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap1_s5_clk_src_init = अणु
	.name = "gcc_qupv3_wrap1_s5_clk_src",
	.parent_data = gcc_parent_data_1,
	.num_parents = ARRAY_SIZE(gcc_parent_data_1),
	.ops = &clk_rcg2_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s5_clk_src = अणु
	.cmd_rcgr = 0x18608,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap1_s5_clk_src_init,
पूर्ण;


अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sdcc1_apps_clk_src[] = अणु
	F(144000, P_BI_TCXO, 16, 3, 25),
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(20000000, P_GPLL0_OUT_EVEN, 5, 1, 3),
	F(25000000, P_GPLL0_OUT_EVEN, 6, 1, 2),
	F(50000000, P_GPLL0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPLL0_OUT_EVEN, 3, 0, 0),
	F(192000000, P_GPLL6_OUT_MAIN, 2, 0, 0),
	F(384000000, P_GPLL6_OUT_MAIN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_sdcc1_apps_clk_src = अणु
	.cmd_rcgr = 0x12028,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_gcc_sdcc1_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_sdcc1_apps_clk_src",
		.parent_data = gcc_parent_data_1,
		.num_parents = ARRAY_SIZE(gcc_parent_data_1),
		.ops = &clk_rcg2_न्यूनमान_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sdcc1_ice_core_clk_src[] = अणु
	F(100000000, P_GPLL0_OUT_EVEN, 3, 0, 0),
	F(150000000, P_GPLL0_OUT_EVEN, 2, 0, 0),
	F(200000000, P_GPLL0_OUT_MAIN, 3, 0, 0),
	F(300000000, P_GPLL0_OUT_EVEN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_sdcc1_ice_core_clk_src = अणु
	.cmd_rcgr = 0x12010,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_sdcc1_ice_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_sdcc1_ice_core_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sdcc2_apps_clk_src[] = अणु
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(25000000, P_GPLL0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GPLL0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPLL0_OUT_EVEN, 3, 0, 0),
	F(202000000, P_GPLL7_OUT_MAIN, 4, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_sdcc2_apps_clk_src = अणु
	.cmd_rcgr = 0x1400c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_5,
	.freq_tbl = ftbl_gcc_sdcc2_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_sdcc2_apps_clk_src",
		.parent_data = gcc_parent_data_5,
		.num_parents = ARRAY_SIZE(gcc_parent_data_5),
		.ops = &clk_rcg2_न्यूनमान_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ufs_phy_axi_clk_src[] = अणु
	F(25000000, P_GPLL0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GPLL0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPLL0_OUT_EVEN, 3, 0, 0),
	F(200000000, P_GPLL0_OUT_MAIN, 3, 0, 0),
	F(240000000, P_GPLL0_OUT_MAIN, 2.5, 0, 0),
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
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ufs_phy_ice_core_clk_src[] = अणु
	F(37500000, P_GPLL0_OUT_EVEN, 8, 0, 0),
	F(75000000, P_GPLL0_OUT_EVEN, 4, 0, 0),
	F(150000000, P_GPLL0_OUT_EVEN, 2, 0, 0),
	F(300000000, P_GPLL0_OUT_EVEN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_phy_ice_core_clk_src = अणु
	.cmd_rcgr = 0x77048,
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

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ufs_phy_phy_aux_clk_src[] = अणु
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_phy_phy_aux_clk_src = अणु
	.cmd_rcgr = 0x77098,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_3,
	.freq_tbl = ftbl_gcc_ufs_phy_phy_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_phy_phy_aux_clk_src",
		.parent_data = gcc_parent_data_3,
		.num_parents = ARRAY_SIZE(gcc_parent_data_3),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ufs_phy_unipro_core_clk_src[] = अणु
	F(37500000, P_GPLL0_OUT_EVEN, 8, 0, 0),
	F(75000000, P_GPLL0_OUT_EVEN, 4, 0, 0),
	F(150000000, P_GPLL0_OUT_EVEN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_phy_unipro_core_clk_src = अणु
	.cmd_rcgr = 0x77060,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_ufs_phy_unipro_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_phy_unipro_core_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb30_prim_master_clk_src[] = अणु
	F(66666667, P_GPLL0_OUT_EVEN, 4.5, 0, 0),
	F(133333333, P_GPLL0_OUT_MAIN, 4.5, 0, 0),
	F(200000000, P_GPLL0_OUT_MAIN, 3, 0, 0),
	F(240000000, P_GPLL0_OUT_MAIN, 2.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb30_prim_master_clk_src = अणु
	.cmd_rcgr = 0xf01c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_usb30_prim_master_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb30_prim_master_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb30_prim_mock_uपंचांगi_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(20000000, P_GPLL0_OUT_EVEN, 15, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb30_prim_mock_uपंचांगi_clk_src = अणु
	.cmd_rcgr = 0xf034,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_usb30_prim_mock_uपंचांगi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb30_prim_mock_utmi_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb3_prim_phy_aux_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb3_prim_phy_aux_clk_src = अणु
	.cmd_rcgr = 0xf060,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_6,
	.freq_tbl = ftbl_gcc_usb3_prim_phy_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb3_prim_phy_aux_clk_src",
		.parent_data = gcc_parent_data_6,
		.num_parents = ARRAY_SIZE(gcc_parent_data_6),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sec_ctrl_clk_src[] = अणु
	F(4800000, P_BI_TCXO, 4, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_sec_ctrl_clk_src = अणु
	.cmd_rcgr = 0x3d030,
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

अटल काष्ठा clk_branch gcc_aggre_ufs_phy_axi_clk = अणु
	.halt_reg = 0x82024,
	.halt_check = BRANCH_HALT_DELAY,
	.hwcg_reg = 0x82024,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x82024,
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
	.halt_reg = 0x8201c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8201c,
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

अटल काष्ठा clk_branch gcc_boot_rom_ahb_clk = अणु
	.halt_reg = 0x38004,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x38004,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(10),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_boot_rom_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camera_hf_axi_clk = अणु
	.halt_reg = 0xb020,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb020,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camera_hf_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camera_throttle_hf_axi_clk = अणु
	.halt_reg = 0xb080,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0xb080,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xb080,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camera_throttle_hf_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ce1_ahb_clk = अणु
	.halt_reg = 0x4100c,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x4100c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(3),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ce1_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ce1_axi_clk = अणु
	.halt_reg = 0x41008,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ce1_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ce1_clk = अणु
	.halt_reg = 0x41004,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(5),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ce1_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_cfg_noc_usb3_prim_axi_clk = अणु
	.halt_reg = 0x502c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x502c,
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

/* For CPUSS functionality the AHB घड़ी needs to be left enabled */
अटल काष्ठा clk_branch gcc_cpuss_ahb_clk = अणु
	.halt_reg = 0x48000,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(21),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_cpuss_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_cpuss_ahb_clk_src.clkr.hw,
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
	.halt_reg = 0x4452c,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x4452c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ddrss_gpu_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_disp_gpll0_clk_src = अणु
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(18),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_disp_gpll0_clk_src",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gpll0.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_aon_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_disp_gpll0_भाग_clk_src = अणु
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(19),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_disp_gpll0_div_clk_src",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_pll0_मुख्य_भाग_cभाग.hw,
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_disp_hf_axi_clk = अणु
	.halt_reg = 0xb024,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_disp_hf_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_disp_throttle_hf_axi_clk = अणु
	.halt_reg = 0xb084,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0xb084,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xb084,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_disp_throttle_hf_axi_clk",
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
				&gpll0.clkr.hw,
			पूर्ण,
			.num_parents = 1,
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
				&gcc_pll0_मुख्य_भाग_cभाग.hw,
			पूर्ण,
			.num_parents = 1,
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

अटल काष्ठा clk_branch gcc_npu_axi_clk = अणु
	.halt_reg = 0x4d008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x4d008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_npu_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_npu_bwmon_axi_clk = अणु
	.halt_reg = 0x73008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x73008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_npu_bwmon_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_npu_bwmon_dma_cfg_ahb_clk = अणु
	.halt_reg = 0x73018,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x73018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_npu_bwmon_dma_cfg_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_npu_bwmon_dsp_cfg_ahb_clk = अणु
	.halt_reg = 0x7301c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x7301c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_npu_bwmon_dsp_cfg_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_npu_cfg_ahb_clk = अणु
	.halt_reg = 0x4d004,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x4d004,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x4d004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_npu_cfg_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_npu_dma_clk = अणु
	.halt_reg = 0x4d1a0,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x4d1a0,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x4d1a0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_npu_dma_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_npu_gpll0_clk_src = अणु
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(25),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_npu_gpll0_clk_src",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gpll0.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_npu_gpll0_भाग_clk_src = अणु
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(26),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_npu_gpll0_div_clk_src",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_pll0_मुख्य_भाग_cभाग.hw,
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
	.hwcg_reg = 0x34004,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(13),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_prng_ahb_clk",
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
	.halt_reg = 0x17014,
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
	.halt_reg = 0x1700c,
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
	.halt_reg = 0x17030,
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
	.halt_reg = 0x17160,
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
	.halt_reg = 0x17290,
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
	.halt_reg = 0x173c0,
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
	.halt_reg = 0x174f0,
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
	.halt_reg = 0x17620,
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

अटल काष्ठा clk_branch gcc_qupv3_wrap1_core_2x_clk = अणु
	.halt_reg = 0x18004,
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
	.halt_reg = 0x18008,
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
	.halt_reg = 0x18014,
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
	.halt_reg = 0x18144,
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
	.halt_reg = 0x18274,
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
	.halt_reg = 0x183a4,
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
	.halt_reg = 0x184d4,
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
	.halt_reg = 0x18604,
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

अटल काष्ठा clk_branch gcc_qupv3_wrap_0_m_ahb_clk = अणु
	.halt_reg = 0x17004,
	.halt_check = BRANCH_HALT_VOTED,
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
	.halt_reg = 0x1800c,
	.halt_check = BRANCH_HALT_VOTED,
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
	.halt_reg = 0x18010,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x18010,
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
	.halt_reg = 0x12008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x12008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sdcc1_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc1_apps_clk = अणु
	.halt_reg = 0x1200c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x1200c,
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
	.halt_reg = 0x12040,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x12040,
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

/* For CPUSS functionality the SYS NOC घड़ी needs to be left enabled */
अटल काष्ठा clk_branch gcc_sys_noc_cpuss_ahb_clk = अणु
	.halt_reg = 0x4144,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sys_noc_cpuss_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_cpuss_ahb_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_IS_CRITICAL | CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_mem_clkref_clk = अणु
	.halt_reg = 0x8c000,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8c000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_mem_clkref_clk",
			.ops = &clk_branch2_ops,
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
	.halt_reg = 0x77038,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x77038,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x77038,
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
	.halt_reg = 0x77090,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x77090,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x77090,
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
	.halt_reg = 0x77094,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x77094,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x77094,
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
	.halt_reg = 0x7708c,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x7708c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x7708c,
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
	.halt_reg = 0xf018,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_prim_mock_utmi_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw =
				&gcc_usb30_prim_mock_uपंचांगi_clk_src.clkr.hw,
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

अटल काष्ठा clk_branch gcc_usb3_prim_clkref_clk = अणु
	.halt_reg = 0x8c010,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8c010,
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
	.halt_reg = 0xf054,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf054,
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

अटल काष्ठा clk_branch gcc_usb_phy_cfg_ahb2phy_clk = अणु
	.halt_reg = 0x6a004,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x6a004,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x6a004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb_phy_cfg_ahb2phy_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_video_axi_clk = अणु
	.halt_reg = 0xb01c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb01c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_video_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_video_gpll0_भाग_clk_src = अणु
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(20),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_video_gpll0_div_clk_src",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_pll0_मुख्य_भाग_cभाग.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_video_throttle_axi_clk = अणु
	.halt_reg = 0xb07c,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0xb07c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xb07c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_video_throttle_axi_clk",
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

अटल काष्ठा clk_branch gcc_mss_mfab_axis_clk = अणु
	.halt_reg = 0x8a004,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x8a004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_mfab_axis_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mss_nav_axi_clk = अणु
	.halt_reg = 0x8a00c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x8a00c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_nav_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mss_snoc_axi_clk = अणु
	.halt_reg = 0x8a150,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8a150,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_snoc_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mss_q6_memnoc_axi_clk = अणु
	.halt_reg = 0x8a154,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8a154,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_q6_memnoc_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_lpass_cfg_noc_sway_clk = अणु
	.halt_reg = 0x47018,
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x47018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_lpass_cfg_noc_sway_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gdsc ufs_phy_gdsc = अणु
	.gdscr = 0x77004,
	.pd = अणु
		.name = "ufs_phy_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc usb30_prim_gdsc = अणु
	.gdscr = 0x0f004,
	.pd = अणु
		.name = "usb30_prim_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc hlos1_vote_mmnoc_mmu_tbu_hf0_gdsc = अणु
	.gdscr = 0x7d040,
	.pd = अणु
		.name = "hlos1_vote_mmnoc_mmu_tbu_hf0_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc hlos1_vote_mmnoc_mmu_tbu_sf_gdsc = अणु
	.gdscr = 0x7d044,
	.pd = अणु
		.name = "hlos1_vote_mmnoc_mmu_tbu_sf_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc *gcc_sc7180_gdscs[] = अणु
	[UFS_PHY_GDSC] = &ufs_phy_gdsc,
	[USB30_PRIM_GDSC] = &usb30_prim_gdsc,
	[HLOS1_VOTE_MMNOC_MMU_TBU_HF0_GDSC] =
					&hlos1_vote_mmnoc_mmu_tbu_hf0_gdsc,
	[HLOS1_VOTE_MMNOC_MMU_TBU_SF_GDSC] =
					&hlos1_vote_mmnoc_mmu_tbu_sf_gdsc,
पूर्ण;


अटल काष्ठा clk_hw *gcc_sc7180_hws[] = अणु
	[GCC_GPLL0_MAIN_DIV_CDIV] = &gcc_pll0_मुख्य_भाग_cभाग.hw,
पूर्ण;

अटल काष्ठा clk_regmap *gcc_sc7180_घड़ीs[] = अणु
	[GCC_AGGRE_UFS_PHY_AXI_CLK] = &gcc_aggre_ufs_phy_axi_clk.clkr,
	[GCC_AGGRE_USB3_PRIM_AXI_CLK] = &gcc_aggre_usb3_prim_axi_clk.clkr,
	[GCC_BOOT_ROM_AHB_CLK] = &gcc_boot_rom_ahb_clk.clkr,
	[GCC_CAMERA_HF_AXI_CLK] = &gcc_camera_hf_axi_clk.clkr,
	[GCC_CAMERA_THROTTLE_HF_AXI_CLK] = &gcc_camera_throttle_hf_axi_clk.clkr,
	[GCC_CE1_AHB_CLK] = &gcc_ce1_ahb_clk.clkr,
	[GCC_CE1_AXI_CLK] = &gcc_ce1_axi_clk.clkr,
	[GCC_CE1_CLK] = &gcc_ce1_clk.clkr,
	[GCC_CFG_NOC_USB3_PRIM_AXI_CLK] = &gcc_cfg_noc_usb3_prim_axi_clk.clkr,
	[GCC_CPUSS_AHB_CLK] = &gcc_cpuss_ahb_clk.clkr,
	[GCC_CPUSS_AHB_CLK_SRC] = &gcc_cpuss_ahb_clk_src.clkr,
	[GCC_CPUSS_RBCPR_CLK] = &gcc_cpuss_rbcpr_clk.clkr,
	[GCC_DDRSS_GPU_AXI_CLK] = &gcc_ddrss_gpu_axi_clk.clkr,
	[GCC_DISP_GPLL0_CLK_SRC] = &gcc_disp_gpll0_clk_src.clkr,
	[GCC_DISP_GPLL0_DIV_CLK_SRC] = &gcc_disp_gpll0_भाग_clk_src.clkr,
	[GCC_DISP_HF_AXI_CLK] = &gcc_disp_hf_axi_clk.clkr,
	[GCC_DISP_THROTTLE_HF_AXI_CLK] = &gcc_disp_throttle_hf_axi_clk.clkr,
	[GCC_GP1_CLK] = &gcc_gp1_clk.clkr,
	[GCC_GP1_CLK_SRC] = &gcc_gp1_clk_src.clkr,
	[GCC_GP2_CLK] = &gcc_gp2_clk.clkr,
	[GCC_GP2_CLK_SRC] = &gcc_gp2_clk_src.clkr,
	[GCC_GP3_CLK] = &gcc_gp3_clk.clkr,
	[GCC_GP3_CLK_SRC] = &gcc_gp3_clk_src.clkr,
	[GCC_GPU_GPLL0_CLK_SRC] = &gcc_gpu_gpll0_clk_src.clkr,
	[GCC_GPU_GPLL0_DIV_CLK_SRC] = &gcc_gpu_gpll0_भाग_clk_src.clkr,
	[GCC_GPU_MEMNOC_GFX_CLK] = &gcc_gpu_memnoc_gfx_clk.clkr,
	[GCC_GPU_SNOC_DVM_GFX_CLK] = &gcc_gpu_snoc_dvm_gfx_clk.clkr,
	[GCC_NPU_AXI_CLK] = &gcc_npu_axi_clk.clkr,
	[GCC_NPU_BWMON_AXI_CLK] = &gcc_npu_bwmon_axi_clk.clkr,
	[GCC_NPU_BWMON_DMA_CFG_AHB_CLK] = &gcc_npu_bwmon_dma_cfg_ahb_clk.clkr,
	[GCC_NPU_BWMON_DSP_CFG_AHB_CLK] = &gcc_npu_bwmon_dsp_cfg_ahb_clk.clkr,
	[GCC_NPU_CFG_AHB_CLK] = &gcc_npu_cfg_ahb_clk.clkr,
	[GCC_NPU_DMA_CLK] = &gcc_npu_dma_clk.clkr,
	[GCC_NPU_GPLL0_CLK_SRC] = &gcc_npu_gpll0_clk_src.clkr,
	[GCC_NPU_GPLL0_DIV_CLK_SRC] = &gcc_npu_gpll0_भाग_clk_src.clkr,
	[GCC_PDM2_CLK] = &gcc_pdm2_clk.clkr,
	[GCC_PDM2_CLK_SRC] = &gcc_pdm2_clk_src.clkr,
	[GCC_PDM_AHB_CLK] = &gcc_pdm_ahb_clk.clkr,
	[GCC_PDM_XO4_CLK] = &gcc_pdm_xo4_clk.clkr,
	[GCC_PRNG_AHB_CLK] = &gcc_prng_ahb_clk.clkr,
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
	[GCC_SYS_NOC_CPUSS_AHB_CLK] = &gcc_sys_noc_cpuss_ahb_clk.clkr,
	[GCC_UFS_MEM_CLKREF_CLK] = &gcc_ufs_mem_clkref_clk.clkr,
	[GCC_UFS_PHY_AHB_CLK] = &gcc_ufs_phy_ahb_clk.clkr,
	[GCC_UFS_PHY_AXI_CLK] = &gcc_ufs_phy_axi_clk.clkr,
	[GCC_UFS_PHY_AXI_CLK_SRC] = &gcc_ufs_phy_axi_clk_src.clkr,
	[GCC_UFS_PHY_ICE_CORE_CLK] = &gcc_ufs_phy_ice_core_clk.clkr,
	[GCC_UFS_PHY_ICE_CORE_CLK_SRC] = &gcc_ufs_phy_ice_core_clk_src.clkr,
	[GCC_UFS_PHY_PHY_AUX_CLK] = &gcc_ufs_phy_phy_aux_clk.clkr,
	[GCC_UFS_PHY_PHY_AUX_CLK_SRC] = &gcc_ufs_phy_phy_aux_clk_src.clkr,
	[GCC_UFS_PHY_RX_SYMBOL_0_CLK] = &gcc_ufs_phy_rx_symbol_0_clk.clkr,
	[GCC_UFS_PHY_TX_SYMBOL_0_CLK] = &gcc_ufs_phy_tx_symbol_0_clk.clkr,
	[GCC_UFS_PHY_UNIPRO_CORE_CLK] = &gcc_ufs_phy_unipro_core_clk.clkr,
	[GCC_UFS_PHY_UNIPRO_CORE_CLK_SRC] =
		&gcc_ufs_phy_unipro_core_clk_src.clkr,
	[GCC_USB30_PRIM_MASTER_CLK] = &gcc_usb30_prim_master_clk.clkr,
	[GCC_USB30_PRIM_MASTER_CLK_SRC] = &gcc_usb30_prim_master_clk_src.clkr,
	[GCC_USB30_PRIM_MOCK_UTMI_CLK] = &gcc_usb30_prim_mock_uपंचांगi_clk.clkr,
	[GCC_USB30_PRIM_MOCK_UTMI_CLK_SRC] =
		&gcc_usb30_prim_mock_uपंचांगi_clk_src.clkr,
	[GCC_USB30_PRIM_SLEEP_CLK] = &gcc_usb30_prim_sleep_clk.clkr,
	[GCC_USB3_PRIM_CLKREF_CLK] = &gcc_usb3_prim_clkref_clk.clkr,
	[GCC_USB3_PRIM_PHY_AUX_CLK] = &gcc_usb3_prim_phy_aux_clk.clkr,
	[GCC_USB3_PRIM_PHY_AUX_CLK_SRC] = &gcc_usb3_prim_phy_aux_clk_src.clkr,
	[GCC_USB3_PRIM_PHY_COM_AUX_CLK] = &gcc_usb3_prim_phy_com_aux_clk.clkr,
	[GCC_USB3_PRIM_PHY_PIPE_CLK] = &gcc_usb3_prim_phy_pipe_clk.clkr,
	[GCC_USB_PHY_CFG_AHB2PHY_CLK] = &gcc_usb_phy_cfg_ahb2phy_clk.clkr,
	[GCC_VIDEO_AXI_CLK] = &gcc_video_axi_clk.clkr,
	[GCC_VIDEO_GPLL0_DIV_CLK_SRC] = &gcc_video_gpll0_भाग_clk_src.clkr,
	[GCC_VIDEO_THROTTLE_AXI_CLK] = &gcc_video_throttle_axi_clk.clkr,
	[GPLL0] = &gpll0.clkr,
	[GPLL0_OUT_EVEN] = &gpll0_out_even.clkr,
	[GPLL6] = &gpll6.clkr,
	[GPLL7] = &gpll7.clkr,
	[GPLL4] = &gpll4.clkr,
	[GPLL1] = &gpll1.clkr,
	[GCC_MSS_CFG_AHB_CLK] = &gcc_mss_cfg_ahb_clk.clkr,
	[GCC_MSS_MFAB_AXIS_CLK] = &gcc_mss_mfab_axis_clk.clkr,
	[GCC_MSS_NAV_AXI_CLK] = &gcc_mss_nav_axi_clk.clkr,
	[GCC_MSS_Q6_MEMNOC_AXI_CLK] = &gcc_mss_q6_memnoc_axi_clk.clkr,
	[GCC_MSS_SNOC_AXI_CLK] = &gcc_mss_snoc_axi_clk.clkr,
	[GCC_SEC_CTRL_CLK_SRC] = &gcc_sec_ctrl_clk_src.clkr,
	[GCC_LPASS_CFG_NOC_SWAY_CLK] = &gcc_lpass_cfg_noc_sway_clk.clkr,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map gcc_sc7180_resets[] = अणु
	[GCC_QUSB2PHY_PRIM_BCR] = अणु 0x26000 पूर्ण,
	[GCC_QUSB2PHY_SEC_BCR] = अणु 0x26004 पूर्ण,
	[GCC_UFS_PHY_BCR] = अणु 0x77000 पूर्ण,
	[GCC_USB30_PRIM_BCR] = अणु 0xf000 पूर्ण,
	[GCC_USB3_PHY_PRIM_BCR] = अणु 0x50000 पूर्ण,
	[GCC_USB3PHY_PHY_PRIM_BCR] = अणु 0x50004 पूर्ण,
	[GCC_USB3_PHY_SEC_BCR] = अणु 0x5000c पूर्ण,
	[GCC_USB3_DP_PHY_PRIM_BCR] = अणु 0x50008 पूर्ण,
	[GCC_USB3PHY_PHY_SEC_BCR] = अणु 0x50010 पूर्ण,
	[GCC_USB3_DP_PHY_SEC_BCR] = अणु 0x50014 पूर्ण,
	[GCC_USB_PHY_CFG_AHB2PHY_BCR] = अणु 0x6a000 पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg_dfs_data gcc_dfs_घड़ीs[] = अणु
	DEFINE_RCG_DFS(gcc_qupv3_wrap0_s0_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap0_s1_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap0_s2_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap0_s3_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap0_s4_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap0_s5_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap1_s0_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap1_s1_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap1_s2_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap1_s3_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap1_s4_clk_src),
	DEFINE_RCG_DFS(gcc_qupv3_wrap1_s5_clk_src),
पूर्ण;

अटल स्थिर काष्ठा regmap_config gcc_sc7180_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = 0x18208c,
	.fast_io = true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc gcc_sc7180_desc = अणु
	.config = &gcc_sc7180_regmap_config,
	.clk_hws = gcc_sc7180_hws,
	.num_clk_hws = ARRAY_SIZE(gcc_sc7180_hws),
	.clks = gcc_sc7180_घड़ीs,
	.num_clks = ARRAY_SIZE(gcc_sc7180_घड़ीs),
	.resets = gcc_sc7180_resets,
	.num_resets = ARRAY_SIZE(gcc_sc7180_resets),
	.gdscs = gcc_sc7180_gdscs,
	.num_gdscs = ARRAY_SIZE(gcc_sc7180_gdscs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id gcc_sc7180_match_table[] = अणु
	अणु .compatible = "qcom,gcc-sc7180" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gcc_sc7180_match_table);

अटल पूर्णांक gcc_sc7180_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	regmap = qcom_cc_map(pdev, &gcc_sc7180_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/*
	 * Disable the GPLL0 active input to MM blocks, NPU
	 * and GPU via MISC रेजिस्टरs.
	 */
	regmap_update_bits(regmap, 0x09ffc, 0x3, 0x3);
	regmap_update_bits(regmap, 0x4d110, 0x3, 0x3);
	regmap_update_bits(regmap, 0x71028, 0x3, 0x3);

	/*
	 * Keep the घड़ीs always-ON
	 * GCC_CPUSS_GNOC_CLK, GCC_VIDEO_AHB_CLK, GCC_CAMERA_AHB_CLK,
	 * GCC_DISP_AHB_CLK, GCC_GPU_CFG_AHB_CLK
	 */
	regmap_update_bits(regmap, 0x48004, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0x0b004, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0x0b008, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0x0b00c, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0x0b02c, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0x0b028, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0x0b030, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0x71004, BIT(0), BIT(0));

	ret = qcom_cc_रेजिस्टर_rcg_dfs(regmap, gcc_dfs_घड़ीs,
					ARRAY_SIZE(gcc_dfs_घड़ीs));
	अगर (ret)
		वापस ret;

	वापस qcom_cc_really_probe(pdev, &gcc_sc7180_desc, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver gcc_sc7180_driver = अणु
	.probe = gcc_sc7180_probe,
	.driver = अणु
		.name = "gcc-sc7180",
		.of_match_table = gcc_sc7180_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init gcc_sc7180_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&gcc_sc7180_driver);
पूर्ण
core_initcall(gcc_sc7180_init);

अटल व्योम __निकास gcc_sc7180_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&gcc_sc7180_driver);
पूर्ण
module_निकास(gcc_sc7180_निकास);

MODULE_DESCRIPTION("QTI GCC SC7180 Driver");
MODULE_LICENSE("GPL v2");
