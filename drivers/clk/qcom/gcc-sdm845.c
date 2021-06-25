<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, 2020, The Linux Foundation. All rights reserved.
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

#समावेश <dt-bindings/घड़ी/qcom,gcc-sdm845.h>

#समावेश "common.h"
#समावेश "clk-regmap.h"
#समावेश "clk-pll.h"
#समावेश "clk-rcg.h"
#समावेश "clk-branch.h"
#समावेश "clk-alpha-pll.h"
#समावेश "gdsc.h"
#समावेश "reset.h"

क्रमागत अणु
	P_BI_TCXO,
	P_AUD_REF_CLK,
	P_GPLL0_OUT_EVEN,
	P_GPLL0_OUT_MAIN,
	P_GPLL4_OUT_MAIN,
	P_SLEEP_CLK,
पूर्ण;

अटल काष्ठा clk_alpha_pll gpll0 = अणु
	.offset = 0x0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpll0",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo", .name = "bi_tcxo",
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
		.enable_reg = 0x52000,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpll4",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo", .name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_fabia_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable post_भाग_प्रकारable_fabia_even[] = अणु
	अणु 0x0, 1 पूर्ण,
	अणु 0x1, 2 पूर्ण,
	अणु 0x3, 4 पूर्ण,
	अणु 0x7, 8 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll0_out_even = अणु
	.offset = 0x0,
	.post_भाग_shअगरt = 8,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_fabia_even,
	.num_post_भाग = ARRAY_SIZE(post_भाग_प्रकारable_fabia_even),
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

अटल स्थिर काष्ठा parent_map gcc_parent_map_0[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_GPLL0_OUT_EVEN, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_0[] = अणु
	अणु .fw_name = "bi_tcxo", .name = "bi_tcxo" पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .hw = &gpll0_out_even.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_1[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_SLEEP_CLK, 5 पूर्ण,
	अणु P_GPLL0_OUT_EVEN, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_1[] = अणु
	अणु .fw_name = "bi_tcxo", .name = "bi_tcxo" पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .fw_name = "sleep_clk", .name = "core_pi_sleep_clk" पूर्ण,
	अणु .hw = &gpll0_out_even.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_2[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_SLEEP_CLK, 5 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_2[] = अणु
	अणु .fw_name = "bi_tcxo", .name = "bi_tcxo" पूर्ण,
	अणु .fw_name = "sleep_clk", .name = "core_pi_sleep_clk" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_3[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_3[] = अणु
	अणु .fw_name = "bi_tcxo", .name = "bi_tcxo" पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_4[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_4[] = अणु
	अणु .fw_name = "bi_tcxo", .name = "bi_tcxo" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_6[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_AUD_REF_CLK, 2 पूर्ण,
	अणु P_GPLL0_OUT_EVEN, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_6[] = अणु
	अणु .fw_name = "bi_tcxo", .name = "bi_tcxo" पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .fw_name = "aud_ref_clk", .name = "aud_ref_clk" पूर्ण,
	अणु .hw = &gpll0_out_even.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_7_ao[] = अणु
	अणु .fw_name = "bi_tcxo_ao", .name = "bi_tcxo_ao" पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .hw = &gpll0_out_even.clkr.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_8[] = अणु
	अणु .fw_name = "bi_tcxo", .name = "bi_tcxo" पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_8_ao[] = अणु
	अणु .fw_name = "bi_tcxo_ao", .name = "bi_tcxo_ao" पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_10[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_GPLL4_OUT_MAIN, 5 पूर्ण,
	अणु P_GPLL0_OUT_EVEN, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gcc_parent_data_10[] = अणु
	अणु .fw_name = "bi_tcxo", .name = "bi_tcxo" पूर्ण,
	अणु .hw = &gpll0.clkr.hw पूर्ण,
	अणु .hw = &gpll4.clkr.hw पूर्ण,
	अणु .hw = &gpll0_out_even.clkr.hw पूर्ण,
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
		.parent_data = gcc_parent_data_7_ao,
		.num_parents = ARRAY_SIZE(gcc_parent_data_7_ao),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_cpuss_rbcpr_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_cpuss_rbcpr_clk_src = अणु
	.cmd_rcgr = 0x4815c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_3,
	.freq_tbl = ftbl_gcc_cpuss_rbcpr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_cpuss_rbcpr_clk_src",
		.parent_data = gcc_parent_data_8_ao,
		.num_parents = ARRAY_SIZE(gcc_parent_data_8_ao),
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
		.parent_data = gcc_parent_data_1,
		.num_parents = ARRAY_SIZE(gcc_parent_data_1),
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
		.parent_data = gcc_parent_data_1,
		.num_parents = ARRAY_SIZE(gcc_parent_data_1),
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
		.parent_data = gcc_parent_data_1,
		.num_parents = ARRAY_SIZE(gcc_parent_data_1),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_pcie_0_aux_clk_src[] = अणु
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_pcie_0_aux_clk_src = अणु
	.cmd_rcgr = 0x6b028,
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

अटल काष्ठा clk_rcg2 gcc_pcie_1_aux_clk_src = अणु
	.cmd_rcgr = 0x8d028,
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
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_qspi_core_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_GPLL0_OUT_MAIN, 6, 0, 0),
	F(150000000, P_GPLL0_OUT_MAIN, 4, 0, 0),
	F(300000000, P_GPLL0_OUT_MAIN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qspi_core_clk_src = अणु
	.cmd_rcgr = 0x4b008,
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
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
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
	F(64000000, P_GPLL0_OUT_EVEN, 1, 16, 75),
	F(80000000, P_GPLL0_OUT_EVEN, 1, 4, 15),
	F(96000000, P_GPLL0_OUT_EVEN, 1, 8, 25),
	F(100000000, P_GPLL0_OUT_EVEN, 3, 0, 0),
	F(102400000, P_GPLL0_OUT_EVEN, 1, 128, 375),
	F(112000000, P_GPLL0_OUT_EVEN, 1, 28, 75),
	F(117964800, P_GPLL0_OUT_EVEN, 1, 6144, 15625),
	F(120000000, P_GPLL0_OUT_EVEN, 2.5, 0, 0),
	F(128000000, P_GPLL0_OUT_MAIN, 1, 16, 75),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s0_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s0_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_shared_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s0_clk_src = अणु
	.cmd_rcgr = 0x17034,
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
	.ops = &clk_rcg2_shared_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s1_clk_src = अणु
	.cmd_rcgr = 0x17164,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s1_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s2_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s2_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_shared_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s2_clk_src = अणु
	.cmd_rcgr = 0x17294,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s2_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s3_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s3_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_shared_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s3_clk_src = अणु
	.cmd_rcgr = 0x173c4,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s3_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s4_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s4_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_shared_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s4_clk_src = अणु
	.cmd_rcgr = 0x174f4,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s4_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s5_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s5_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_shared_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s5_clk_src = अणु
	.cmd_rcgr = 0x17624,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s5_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s6_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s6_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_shared_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s6_clk_src = अणु
	.cmd_rcgr = 0x17754,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s6_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap0_s7_clk_src_init = अणु
	.name = "gcc_qupv3_wrap0_s7_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_shared_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap0_s7_clk_src = अणु
	.cmd_rcgr = 0x17884,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap0_s7_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap1_s0_clk_src_init = अणु
	.name = "gcc_qupv3_wrap1_s0_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_shared_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s0_clk_src = अणु
	.cmd_rcgr = 0x18018,
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
	.ops = &clk_rcg2_shared_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s1_clk_src = अणु
	.cmd_rcgr = 0x18148,
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
	.ops = &clk_rcg2_shared_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s2_clk_src = अणु
	.cmd_rcgr = 0x18278,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap1_s2_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap1_s3_clk_src_init = अणु
	.name = "gcc_qupv3_wrap1_s3_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_shared_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s3_clk_src = अणु
	.cmd_rcgr = 0x183a8,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap1_s3_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap1_s4_clk_src_init = अणु
	.name = "gcc_qupv3_wrap1_s4_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_shared_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s4_clk_src = अणु
	.cmd_rcgr = 0x184d8,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap1_s4_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap1_s5_clk_src_init = अणु
	.name = "gcc_qupv3_wrap1_s5_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_shared_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s5_clk_src = अणु
	.cmd_rcgr = 0x18608,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap1_s5_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap1_s6_clk_src_init = अणु
	.name = "gcc_qupv3_wrap1_s6_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_shared_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s6_clk_src = अणु
	.cmd_rcgr = 0x18738,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap1_s6_clk_src_init,
पूर्ण;

अटल काष्ठा clk_init_data gcc_qupv3_wrap1_s7_clk_src_init = अणु
	.name = "gcc_qupv3_wrap1_s7_clk_src",
	.parent_data = gcc_parent_data_0,
	.num_parents = ARRAY_SIZE(gcc_parent_data_0),
	.ops = &clk_rcg2_shared_ops,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_qupv3_wrap1_s7_clk_src = अणु
	.cmd_rcgr = 0x18868,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_qupv3_wrap0_s0_clk_src,
	.clkr.hw.init = &gcc_qupv3_wrap1_s7_clk_src_init,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sdcc2_apps_clk_src[] = अणु
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(25000000, P_GPLL0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GPLL0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPLL0_OUT_MAIN, 6, 0, 0),
	F(201500000, P_GPLL4_OUT_MAIN, 4, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_sdcc2_apps_clk_src = अणु
	.cmd_rcgr = 0x1400c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_10,
	.freq_tbl = ftbl_gcc_sdcc2_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_sdcc2_apps_clk_src",
		.parent_data = gcc_parent_data_10,
		.num_parents = ARRAY_SIZE(gcc_parent_data_10),
		.ops = &clk_rcg2_न्यूनमान_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sdcc4_apps_clk_src[] = अणु
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(25000000, P_GPLL0_OUT_MAIN, 12, 1, 2),
	F(50000000, P_GPLL0_OUT_MAIN, 12, 0, 0),
	F(100000000, P_GPLL0_OUT_MAIN, 6, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_sdcc4_apps_clk_src = अणु
	.cmd_rcgr = 0x1600c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_sdcc4_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_sdcc4_apps_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
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
	.parent_map = gcc_parent_map_6,
	.freq_tbl = ftbl_gcc_tsअगर_ref_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_tsif_ref_clk_src",
		.parent_data = gcc_parent_data_6,
		.num_parents = ARRAY_SIZE(gcc_parent_data_6),
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
	.cmd_rcgr = 0x7501c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_ufs_card_axi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_card_axi_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ufs_card_ice_core_clk_src[] = अणु
	F(37500000, P_GPLL0_OUT_EVEN, 8, 0, 0),
	F(75000000, P_GPLL0_OUT_EVEN, 4, 0, 0),
	F(150000000, P_GPLL0_OUT_MAIN, 4, 0, 0),
	F(300000000, P_GPLL0_OUT_MAIN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_card_ice_core_clk_src = अणु
	.cmd_rcgr = 0x7505c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_ufs_card_ice_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_card_ice_core_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_card_phy_aux_clk_src = अणु
	.cmd_rcgr = 0x75090,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_4,
	.freq_tbl = ftbl_gcc_cpuss_rbcpr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_card_phy_aux_clk_src",
		.parent_data = gcc_parent_data_4,
		.num_parents = ARRAY_SIZE(gcc_parent_data_4),
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
	.cmd_rcgr = 0x75074,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_ufs_card_unipro_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_card_unipro_core_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ufs_phy_axi_clk_src[] = अणु
	F(25000000, P_GPLL0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GPLL0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPLL0_OUT_MAIN, 6, 0, 0),
	F(200000000, P_GPLL0_OUT_MAIN, 3, 0, 0),
	F(240000000, P_GPLL0_OUT_MAIN, 2.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_phy_axi_clk_src = अणु
	.cmd_rcgr = 0x7701c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_ufs_phy_axi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_phy_axi_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_phy_ice_core_clk_src = अणु
	.cmd_rcgr = 0x7705c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_ufs_card_ice_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_phy_ice_core_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_phy_phy_aux_clk_src = अणु
	.cmd_rcgr = 0x77090,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_4,
	.freq_tbl = ftbl_gcc_pcie_0_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_phy_phy_aux_clk_src",
		.parent_data = gcc_parent_data_4,
		.num_parents = ARRAY_SIZE(gcc_parent_data_4),
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_ufs_phy_unipro_core_clk_src = अणु
	.cmd_rcgr = 0x77074,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_ufs_card_unipro_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_ufs_phy_unipro_core_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb30_prim_master_clk_src[] = अणु
	F(33333333, P_GPLL0_OUT_EVEN, 9, 0, 0),
	F(66666667, P_GPLL0_OUT_EVEN, 4.5, 0, 0),
	F(133333333, P_GPLL0_OUT_MAIN, 4.5, 0, 0),
	F(200000000, P_GPLL0_OUT_MAIN, 3, 0, 0),
	F(240000000, P_GPLL0_OUT_MAIN, 2.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb30_prim_master_clk_src = अणु
	.cmd_rcgr = 0xf018,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_usb30_prim_master_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb30_prim_master_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb30_prim_mock_uपंचांगi_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(20000000, P_GPLL0_OUT_EVEN, 15, 0, 0),
	F(40000000, P_GPLL0_OUT_EVEN, 7.5, 0, 0),
	F(60000000, P_GPLL0_OUT_MAIN, 10, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb30_prim_mock_uपंचांगi_clk_src = अणु
	.cmd_rcgr = 0xf030,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_usb30_prim_mock_uपंचांगi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb30_prim_mock_utmi_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb30_sec_master_clk_src = अणु
	.cmd_rcgr = 0x10018,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_usb30_prim_master_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb30_sec_master_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb30_sec_mock_uपंचांगi_clk_src = अणु
	.cmd_rcgr = 0x10030,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_gcc_usb30_prim_mock_uपंचांगi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb30_sec_mock_utmi_clk_src",
		.parent_data = gcc_parent_data_0,
		.num_parents = ARRAY_SIZE(gcc_parent_data_0),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb3_prim_phy_aux_clk_src = अणु
	.cmd_rcgr = 0xf05c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_2,
	.freq_tbl = ftbl_gcc_cpuss_rbcpr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb3_prim_phy_aux_clk_src",
		.parent_data = gcc_parent_data_2,
		.num_parents = ARRAY_SIZE(gcc_parent_data_2),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_usb3_sec_phy_aux_clk_src = अणु
	.cmd_rcgr = 0x1005c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_2,
	.freq_tbl = ftbl_gcc_cpuss_rbcpr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_usb3_sec_phy_aux_clk_src",
		.parent_data = gcc_parent_data_2,
		.num_parents = ARRAY_SIZE(gcc_parent_data_2),
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_vs_ctrl_clk_src = अणु
	.cmd_rcgr = 0x7a030,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_3,
	.freq_tbl = ftbl_gcc_cpuss_rbcpr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_vs_ctrl_clk_src",
		.parent_data = gcc_parent_data_3,
		.num_parents = ARRAY_SIZE(gcc_parent_data_3),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_vsensor_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(300000000, P_GPLL0_OUT_MAIN, 2, 0, 0),
	F(600000000, P_GPLL0_OUT_MAIN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_vsensor_clk_src = अणु
	.cmd_rcgr = 0x7a018,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_3,
	.freq_tbl = ftbl_gcc_vsensor_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_vsensor_clk_src",
		.parent_data = gcc_parent_data_8,
		.num_parents = ARRAY_SIZE(gcc_parent_data_8),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre_noc_pcie_tbu_clk = अणु
	.halt_reg = 0x90014,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x90014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_aggre_noc_pcie_tbu_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre_ufs_card_axi_clk = अणु
	.halt_reg = 0x82028,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x82028,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x82028,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_aggre_ufs_card_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_ufs_card_axi_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre_ufs_phy_axi_clk = अणु
	.halt_reg = 0x82024,
	.halt_check = BRANCH_HALT,
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

अटल काष्ठा clk_branch gcc_aggre_usb3_sec_axi_clk = अणु
	.halt_reg = 0x82020,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x82020,
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

अटल काष्ठा clk_branch gcc_apc_vs_clk = अणु
	.halt_reg = 0x7a050,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x7a050,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_apc_vs_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_vsensor_clk_src.clkr.hw,
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

अटल काष्ठा clk_branch gcc_camera_ahb_clk = अणु
	.halt_reg = 0xb008,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0xb008,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xb008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camera_ahb_clk",
			.flags = CLK_IS_CRITICAL,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camera_axi_clk = अणु
	.halt_reg = 0xb020,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0xb020,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camera_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camera_xo_clk = अणु
	.halt_reg = 0xb02c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb02c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camera_xo_clk",
			.flags = CLK_IS_CRITICAL,
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
		.enable_reg = 0x52004,
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
		.enable_reg = 0x52004,
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
		.enable_reg = 0x52004,
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

अटल काष्ठा clk_branch gcc_cfg_noc_usb3_sec_axi_clk = अणु
	.halt_reg = 0x5030,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x5030,
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

अटल काष्ठा clk_branch gcc_cpuss_ahb_clk = अणु
	.halt_reg = 0x48000,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(21),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_cpuss_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_cpuss_ahb_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT | CLK_IS_CRITICAL,
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
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_cpuss_rbcpr_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ddrss_gpu_axi_clk = अणु
	.halt_reg = 0x44038,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x44038,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ddrss_gpu_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_disp_ahb_clk = अणु
	.halt_reg = 0xb00c,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0xb00c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xb00c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_disp_ahb_clk",
			.flags = CLK_IS_CRITICAL,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_disp_axi_clk = अणु
	.halt_reg = 0xb024,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0xb024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_disp_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_disp_gpll0_clk_src = अणु
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x52004,
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
		.enable_reg = 0x52004,
		.enable_mask = BIT(19),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_disp_gpll0_div_clk_src",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gpll0_out_even.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_disp_xo_clk = अणु
	.halt_reg = 0xb030,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb030,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_disp_xo_clk",
			.flags = CLK_IS_CRITICAL,
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

अटल काष्ठा clk_branch gcc_gpu_cfg_ahb_clk = अणु
	.halt_reg = 0x71004,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x71004,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x71004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gpu_cfg_ahb_clk",
			.flags = CLK_IS_CRITICAL,
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
		.enable_reg = 0x52004,
		.enable_mask = BIT(16),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gpu_gpll0_div_clk_src",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gpll0_out_even.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gpu_iref_clk = अणु
	.halt_reg = 0x8c010,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8c010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gpu_iref_clk",
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

अटल काष्ठा clk_branch gcc_gpu_vs_clk = अणु
	.halt_reg = 0x7a04c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x7a04c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gpu_vs_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_vsensor_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mss_axis2_clk = अणु
	.halt_reg = 0x8a008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8a008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_axis2_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mss_cfg_ahb_clk = अणु
	.halt_reg = 0x8a000,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x8a000,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x8a000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_cfg_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mss_gpll0_भाग_clk_src = अणु
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(17),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_gpll0_div_clk_src",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mss_mfab_axis_clk = अणु
	.halt_reg = 0x8a004,
	.halt_check = BRANCH_VOTED,
	.hwcg_reg = 0x8a004,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x8a004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_mfab_axis_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mss_q6_memnoc_axi_clk = अणु
	.halt_reg = 0x8a154,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x8a154,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_q6_memnoc_axi_clk",
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

अटल काष्ठा clk_branch gcc_mss_vs_clk = अणु
	.halt_reg = 0x7a048,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x7a048,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_vs_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_vsensor_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_aux_clk = अणु
	.halt_reg = 0x6b01c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
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
	.halt_reg = 0x6b018,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x6b018,
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
	.halt_reg = 0x6b014,
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
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_pipe_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "pcie_0_pipe_clk", .name = "pcie_0_pipe_clk",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_slv_axi_clk = अणु
	.halt_reg = 0x6b010,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x6b010,
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
	.halt_reg = 0x6b00c,
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
	.halt_reg = 0x8d01c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52004,
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
	.halt_reg = 0x8d018,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x8d018,
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
	.halt_reg = 0x8d014,
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
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(30),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_1_pipe_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "pcie_1_pipe_clk", .name = "pcie_1_pipe_clk",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_slv_axi_clk = अणु
	.halt_reg = 0x8d010,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x8d010,
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
	.halt_reg = 0x8d00c,
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

अटल काष्ठा clk_branch gcc_pcie_phy_aux_clk = अणु
	.halt_reg = 0x6f004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6f004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_phy_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_pcie_0_aux_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_phy_refgen_clk = अणु
	.halt_reg = 0x6f02c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6f02c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_phy_refgen_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_pcie_phy_refgen_clk_src.clkr.hw,
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
		.enable_reg = 0x52004,
		.enable_mask = BIT(13),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_prng_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qmip_camera_ahb_clk = अणु
	.halt_reg = 0xb014,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0xb014,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xb014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qmip_camera_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qmip_disp_ahb_clk = अणु
	.halt_reg = 0xb018,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0xb018,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xb018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qmip_disp_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qmip_video_ahb_clk = अणु
	.halt_reg = 0xb010,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0xb010,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xb010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qmip_video_ahb_clk",
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
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_qspi_core_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qupv3_wrap0_s0_clk = अणु
	.halt_reg = 0x17030,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
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
		.enable_reg = 0x5200c,
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
		.enable_reg = 0x5200c,
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
		.enable_reg = 0x5200c,
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
		.enable_reg = 0x5200c,
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
		.enable_reg = 0x5200c,
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
	.halt_reg = 0x17750,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
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
	.halt_reg = 0x17880,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
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

अटल काष्ठा clk_branch gcc_qupv3_wrap1_s0_clk = अणु
	.halt_reg = 0x18014,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
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
		.enable_reg = 0x5200c,
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
		.enable_reg = 0x5200c,
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
		.enable_reg = 0x5200c,
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
		.enable_reg = 0x5200c,
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
		.enable_reg = 0x5200c,
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
	.halt_reg = 0x18734,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(28),
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
	.halt_reg = 0x18864,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(29),
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
	.halt_reg = 0x1800c,
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
	.halt_reg = 0x18010,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x18010,
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

अटल काष्ठा clk_branch gcc_sys_noc_cpuss_ahb_clk = अणु
	.halt_reg = 0x414c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sys_noc_cpuss_ahb_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_cpuss_ahb_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT | CLK_IS_CRITICAL,
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
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_tsअगर_ref_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_ahb_clk = अणु
	.halt_reg = 0x75010,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x75010,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x75010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_axi_clk = अणु
	.halt_reg = 0x7500c,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x7500c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x7500c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_axi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_ufs_card_axi_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_clkref_clk = अणु
	.halt_reg = 0x8c004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8c004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_clkref_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_ice_core_clk = अणु
	.halt_reg = 0x75058,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x75058,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x75058,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_ice_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_ufs_card_ice_core_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_phy_aux_clk = अणु
	.halt_reg = 0x7508c,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x7508c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x7508c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_phy_aux_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_ufs_card_phy_aux_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_rx_symbol_0_clk = अणु
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x75018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_rx_symbol_0_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_rx_symbol_1_clk = अणु
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x750a8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_rx_symbol_1_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_tx_symbol_0_clk = अणु
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x75014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_tx_symbol_0_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_card_unipro_core_clk = अणु
	.halt_reg = 0x75054,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x75054,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x75054,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_card_unipro_core_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_ufs_card_unipro_core_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
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
	.halt_reg = 0x77010,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x77010,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x77010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_axi_clk = अणु
	.halt_reg = 0x7700c,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x7700c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x7700c,
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
	.halt_reg = 0x77058,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x77058,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x77058,
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
	.halt_reg = 0x7708c,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x7708c,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x7708c,
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
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x77018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_rx_symbol_0_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_rx_symbol_1_clk = अणु
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x770a8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_rx_symbol_1_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_tx_symbol_0_clk = अणु
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x77014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_tx_symbol_0_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_unipro_core_clk = अणु
	.halt_reg = 0x77054,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x77054,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x77054,
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
	.halt_reg = 0xf00c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf00c,
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
	.halt_reg = 0xf014,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_prim_mock_utmi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_usb30_prim_mock_uपंचांगi_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_prim_sleep_clk = अणु
	.halt_reg = 0xf010,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_prim_sleep_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_sec_master_clk = अणु
	.halt_reg = 0x1000c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x1000c,
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
	.halt_reg = 0x10014,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x10014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_sec_mock_utmi_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_usb30_sec_mock_uपंचांगi_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_sec_sleep_clk = अणु
	.halt_reg = 0x10010,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x10010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_sec_sleep_clk",
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
	.halt_reg = 0xf04c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf04c,
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
	.halt_reg = 0xf050,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf050,
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
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0xf054,
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
	.halt_reg = 0x1004c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x1004c,
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
	.halt_reg = 0x10050,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x10050,
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
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x10054,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_sec_phy_pipe_clk",
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

अटल काष्ठा clk_branch gcc_vdda_vs_clk = अणु
	.halt_reg = 0x7a00c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x7a00c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_vdda_vs_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_vsensor_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_vddcx_vs_clk = अणु
	.halt_reg = 0x7a004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x7a004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_vddcx_vs_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_vsensor_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_vddmx_vs_clk = अणु
	.halt_reg = 0x7a008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x7a008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_vddmx_vs_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_vsensor_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_video_ahb_clk = अणु
	.halt_reg = 0xb004,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0xb004,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0xb004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_video_ahb_clk",
			.flags = CLK_IS_CRITICAL,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_video_axi_clk = अणु
	.halt_reg = 0xb01c,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0xb01c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_video_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_video_xo_clk = अणु
	.halt_reg = 0xb028,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb028,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_video_xo_clk",
			.flags = CLK_IS_CRITICAL,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_vs_ctrl_ahb_clk = अणु
	.halt_reg = 0x7a014,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x7a014,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x7a014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_vs_ctrl_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_vs_ctrl_clk = अणु
	.halt_reg = 0x7a010,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x7a010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_vs_ctrl_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gcc_vs_ctrl_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_cpuss_dvm_bus_clk = अणु
	.halt_reg = 0x48190,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x48190,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_cpuss_dvm_bus_clk",
			.flags = CLK_IS_CRITICAL,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_cpuss_gnoc_clk = अणु
	.halt_reg = 0x48004,
	.halt_check = BRANCH_HALT_VOTED,
	.hwcg_reg = 0x48004,
	.hwcg_bit = 1,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(22),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_cpuss_gnoc_clk",
			.flags = CLK_IS_CRITICAL,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* TODO: Remove after DTS updated to protect these */
#अगर_घोषित CONFIG_SDM_LPASSCC_845
अटल काष्ठा clk_branch gcc_lpass_q6_axi_clk = अणु
	.halt_reg = 0x47000,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x47000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_lpass_q6_axi_clk",
			.flags = CLK_IS_CRITICAL,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_lpass_sway_clk = अणु
	.halt_reg = 0x47008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x47008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_lpass_sway_clk",
			.flags = CLK_IS_CRITICAL,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा gdsc pcie_0_gdsc = अणु
	.gdscr = 0x6b004,
	.pd = अणु
		.name = "pcie_0_gdsc",
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

अटल काष्ठा gdsc usb30_prim_gdsc = अणु
	.gdscr = 0xf004,
	.pd = अणु
		.name = "usb30_prim_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = POLL_CFG_GDSCR,
पूर्ण;

अटल काष्ठा gdsc usb30_sec_gdsc = अणु
	.gdscr = 0x10004,
	.pd = अणु
		.name = "usb30_sec_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = POLL_CFG_GDSCR,
पूर्ण;

अटल काष्ठा gdsc hlos1_vote_aggre_noc_mmu_audio_tbu_gdsc = अणु
	.gdscr = 0x7d030,
	.pd = अणु
		.name = "hlos1_vote_aggre_noc_mmu_audio_tbu_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc hlos1_vote_aggre_noc_mmu_pcie_tbu_gdsc = अणु
	.gdscr = 0x7d03c,
	.pd = अणु
		.name = "hlos1_vote_aggre_noc_mmu_pcie_tbu_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc hlos1_vote_aggre_noc_mmu_tbu1_gdsc = अणु
	.gdscr = 0x7d034,
	.pd = अणु
		.name = "hlos1_vote_aggre_noc_mmu_tbu1_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc hlos1_vote_aggre_noc_mmu_tbu2_gdsc = अणु
	.gdscr = 0x7d038,
	.pd = अणु
		.name = "hlos1_vote_aggre_noc_mmu_tbu2_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc hlos1_vote_mmnoc_mmu_tbu_hf0_gdsc = अणु
	.gdscr = 0x7d040,
	.pd = अणु
		.name = "hlos1_vote_mmnoc_mmu_tbu_hf0_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc hlos1_vote_mmnoc_mmu_tbu_hf1_gdsc = अणु
	.gdscr = 0x7d048,
	.pd = अणु
		.name = "hlos1_vote_mmnoc_mmu_tbu_hf1_gdsc",
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

अटल काष्ठा clk_regmap *gcc_sdm845_घड़ीs[] = अणु
	[GCC_AGGRE_NOC_PCIE_TBU_CLK] = &gcc_aggre_noc_pcie_tbu_clk.clkr,
	[GCC_AGGRE_UFS_CARD_AXI_CLK] = &gcc_aggre_ufs_card_axi_clk.clkr,
	[GCC_AGGRE_UFS_PHY_AXI_CLK] = &gcc_aggre_ufs_phy_axi_clk.clkr,
	[GCC_AGGRE_USB3_PRIM_AXI_CLK] = &gcc_aggre_usb3_prim_axi_clk.clkr,
	[GCC_AGGRE_USB3_SEC_AXI_CLK] = &gcc_aggre_usb3_sec_axi_clk.clkr,
	[GCC_APC_VS_CLK] = &gcc_apc_vs_clk.clkr,
	[GCC_BOOT_ROM_AHB_CLK] = &gcc_boot_rom_ahb_clk.clkr,
	[GCC_CAMERA_AHB_CLK] = &gcc_camera_ahb_clk.clkr,
	[GCC_CAMERA_AXI_CLK] = &gcc_camera_axi_clk.clkr,
	[GCC_CAMERA_XO_CLK] = &gcc_camera_xo_clk.clkr,
	[GCC_CE1_AHB_CLK] = &gcc_ce1_ahb_clk.clkr,
	[GCC_CE1_AXI_CLK] = &gcc_ce1_axi_clk.clkr,
	[GCC_CE1_CLK] = &gcc_ce1_clk.clkr,
	[GCC_CFG_NOC_USB3_PRIM_AXI_CLK] = &gcc_cfg_noc_usb3_prim_axi_clk.clkr,
	[GCC_CFG_NOC_USB3_SEC_AXI_CLK] = &gcc_cfg_noc_usb3_sec_axi_clk.clkr,
	[GCC_CPUSS_AHB_CLK] = &gcc_cpuss_ahb_clk.clkr,
	[GCC_CPUSS_AHB_CLK_SRC] = &gcc_cpuss_ahb_clk_src.clkr,
	[GCC_CPUSS_RBCPR_CLK] = &gcc_cpuss_rbcpr_clk.clkr,
	[GCC_CPUSS_RBCPR_CLK_SRC] = &gcc_cpuss_rbcpr_clk_src.clkr,
	[GCC_DDRSS_GPU_AXI_CLK] = &gcc_ddrss_gpu_axi_clk.clkr,
	[GCC_DISP_AHB_CLK] = &gcc_disp_ahb_clk.clkr,
	[GCC_DISP_AXI_CLK] = &gcc_disp_axi_clk.clkr,
	[GCC_DISP_GPLL0_CLK_SRC] = &gcc_disp_gpll0_clk_src.clkr,
	[GCC_DISP_GPLL0_DIV_CLK_SRC] = &gcc_disp_gpll0_भाग_clk_src.clkr,
	[GCC_DISP_XO_CLK] = &gcc_disp_xo_clk.clkr,
	[GCC_GP1_CLK] = &gcc_gp1_clk.clkr,
	[GCC_GP1_CLK_SRC] = &gcc_gp1_clk_src.clkr,
	[GCC_GP2_CLK] = &gcc_gp2_clk.clkr,
	[GCC_GP2_CLK_SRC] = &gcc_gp2_clk_src.clkr,
	[GCC_GP3_CLK] = &gcc_gp3_clk.clkr,
	[GCC_GP3_CLK_SRC] = &gcc_gp3_clk_src.clkr,
	[GCC_GPU_CFG_AHB_CLK] = &gcc_gpu_cfg_ahb_clk.clkr,
	[GCC_GPU_GPLL0_CLK_SRC] = &gcc_gpu_gpll0_clk_src.clkr,
	[GCC_GPU_GPLL0_DIV_CLK_SRC] = &gcc_gpu_gpll0_भाग_clk_src.clkr,
	[GCC_GPU_IREF_CLK] = &gcc_gpu_iref_clk.clkr,
	[GCC_GPU_MEMNOC_GFX_CLK] = &gcc_gpu_memnoc_gfx_clk.clkr,
	[GCC_GPU_SNOC_DVM_GFX_CLK] = &gcc_gpu_snoc_dvm_gfx_clk.clkr,
	[GCC_GPU_VS_CLK] = &gcc_gpu_vs_clk.clkr,
	[GCC_MSS_AXIS2_CLK] = &gcc_mss_axis2_clk.clkr,
	[GCC_MSS_CFG_AHB_CLK] = &gcc_mss_cfg_ahb_clk.clkr,
	[GCC_MSS_GPLL0_DIV_CLK_SRC] = &gcc_mss_gpll0_भाग_clk_src.clkr,
	[GCC_MSS_MFAB_AXIS_CLK] = &gcc_mss_mfab_axis_clk.clkr,
	[GCC_MSS_Q6_MEMNOC_AXI_CLK] = &gcc_mss_q6_memnoc_axi_clk.clkr,
	[GCC_MSS_SNOC_AXI_CLK] = &gcc_mss_snoc_axi_clk.clkr,
	[GCC_MSS_VS_CLK] = &gcc_mss_vs_clk.clkr,
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
	[GCC_PCIE_PHY_AUX_CLK] = &gcc_pcie_phy_aux_clk.clkr,
	[GCC_PCIE_PHY_REFGEN_CLK] = &gcc_pcie_phy_refgen_clk.clkr,
	[GCC_PCIE_PHY_REFGEN_CLK_SRC] = &gcc_pcie_phy_refgen_clk_src.clkr,
	[GCC_PDM2_CLK] = &gcc_pdm2_clk.clkr,
	[GCC_PDM2_CLK_SRC] = &gcc_pdm2_clk_src.clkr,
	[GCC_PDM_AHB_CLK] = &gcc_pdm_ahb_clk.clkr,
	[GCC_PDM_XO4_CLK] = &gcc_pdm_xo4_clk.clkr,
	[GCC_PRNG_AHB_CLK] = &gcc_prng_ahb_clk.clkr,
	[GCC_QMIP_CAMERA_AHB_CLK] = &gcc_qmip_camera_ahb_clk.clkr,
	[GCC_QMIP_DISP_AHB_CLK] = &gcc_qmip_disp_ahb_clk.clkr,
	[GCC_QMIP_VIDEO_AHB_CLK] = &gcc_qmip_video_ahb_clk.clkr,
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
	[GCC_QUPV3_WRAP1_S6_CLK] = &gcc_qupv3_wrap1_s6_clk.clkr,
	[GCC_QUPV3_WRAP1_S6_CLK_SRC] = &gcc_qupv3_wrap1_s6_clk_src.clkr,
	[GCC_QUPV3_WRAP1_S7_CLK] = &gcc_qupv3_wrap1_s7_clk.clkr,
	[GCC_QUPV3_WRAP1_S7_CLK_SRC] = &gcc_qupv3_wrap1_s7_clk_src.clkr,
	[GCC_QUPV3_WRAP_0_M_AHB_CLK] = &gcc_qupv3_wrap_0_m_ahb_clk.clkr,
	[GCC_QUPV3_WRAP_0_S_AHB_CLK] = &gcc_qupv3_wrap_0_s_ahb_clk.clkr,
	[GCC_QUPV3_WRAP_1_M_AHB_CLK] = &gcc_qupv3_wrap_1_m_ahb_clk.clkr,
	[GCC_QUPV3_WRAP_1_S_AHB_CLK] = &gcc_qupv3_wrap_1_s_ahb_clk.clkr,
	[GCC_SDCC2_AHB_CLK] = &gcc_sdcc2_ahb_clk.clkr,
	[GCC_SDCC2_APPS_CLK] = &gcc_sdcc2_apps_clk.clkr,
	[GCC_SDCC2_APPS_CLK_SRC] = &gcc_sdcc2_apps_clk_src.clkr,
	[GCC_SDCC4_AHB_CLK] = &gcc_sdcc4_ahb_clk.clkr,
	[GCC_SDCC4_APPS_CLK] = &gcc_sdcc4_apps_clk.clkr,
	[GCC_SDCC4_APPS_CLK_SRC] = &gcc_sdcc4_apps_clk_src.clkr,
	[GCC_SYS_NOC_CPUSS_AHB_CLK] = &gcc_sys_noc_cpuss_ahb_clk.clkr,
	[GCC_TSIF_AHB_CLK] = &gcc_tsअगर_ahb_clk.clkr,
	[GCC_TSIF_INACTIVITY_TIMERS_CLK] =
					&gcc_tsअगर_inactivity_समयrs_clk.clkr,
	[GCC_TSIF_REF_CLK] = &gcc_tsअगर_ref_clk.clkr,
	[GCC_TSIF_REF_CLK_SRC] = &gcc_tsअगर_ref_clk_src.clkr,
	[GCC_UFS_CARD_AHB_CLK] = &gcc_ufs_card_ahb_clk.clkr,
	[GCC_UFS_CARD_AXI_CLK] = &gcc_ufs_card_axi_clk.clkr,
	[GCC_UFS_CARD_AXI_CLK_SRC] = &gcc_ufs_card_axi_clk_src.clkr,
	[GCC_UFS_CARD_CLKREF_CLK] = &gcc_ufs_card_clkref_clk.clkr,
	[GCC_UFS_CARD_ICE_CORE_CLK] = &gcc_ufs_card_ice_core_clk.clkr,
	[GCC_UFS_CARD_ICE_CORE_CLK_SRC] = &gcc_ufs_card_ice_core_clk_src.clkr,
	[GCC_UFS_CARD_PHY_AUX_CLK] = &gcc_ufs_card_phy_aux_clk.clkr,
	[GCC_UFS_CARD_PHY_AUX_CLK_SRC] = &gcc_ufs_card_phy_aux_clk_src.clkr,
	[GCC_UFS_CARD_RX_SYMBOL_0_CLK] = &gcc_ufs_card_rx_symbol_0_clk.clkr,
	[GCC_UFS_CARD_RX_SYMBOL_1_CLK] = &gcc_ufs_card_rx_symbol_1_clk.clkr,
	[GCC_UFS_CARD_TX_SYMBOL_0_CLK] = &gcc_ufs_card_tx_symbol_0_clk.clkr,
	[GCC_UFS_CARD_UNIPRO_CORE_CLK] = &gcc_ufs_card_unipro_core_clk.clkr,
	[GCC_UFS_CARD_UNIPRO_CORE_CLK_SRC] =
					&gcc_ufs_card_unipro_core_clk_src.clkr,
	[GCC_UFS_MEM_CLKREF_CLK] = &gcc_ufs_mem_clkref_clk.clkr,
	[GCC_UFS_PHY_AHB_CLK] = &gcc_ufs_phy_ahb_clk.clkr,
	[GCC_UFS_PHY_AXI_CLK] = &gcc_ufs_phy_axi_clk.clkr,
	[GCC_UFS_PHY_AXI_CLK_SRC] = &gcc_ufs_phy_axi_clk_src.clkr,
	[GCC_UFS_PHY_ICE_CORE_CLK] = &gcc_ufs_phy_ice_core_clk.clkr,
	[GCC_UFS_PHY_ICE_CORE_CLK_SRC] = &gcc_ufs_phy_ice_core_clk_src.clkr,
	[GCC_UFS_PHY_PHY_AUX_CLK] = &gcc_ufs_phy_phy_aux_clk.clkr,
	[GCC_UFS_PHY_PHY_AUX_CLK_SRC] = &gcc_ufs_phy_phy_aux_clk_src.clkr,
	[GCC_UFS_PHY_RX_SYMBOL_0_CLK] = &gcc_ufs_phy_rx_symbol_0_clk.clkr,
	[GCC_UFS_PHY_RX_SYMBOL_1_CLK] = &gcc_ufs_phy_rx_symbol_1_clk.clkr,
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
	[GCC_USB30_SEC_MASTER_CLK] = &gcc_usb30_sec_master_clk.clkr,
	[GCC_USB30_SEC_MASTER_CLK_SRC] = &gcc_usb30_sec_master_clk_src.clkr,
	[GCC_USB30_SEC_MOCK_UTMI_CLK] = &gcc_usb30_sec_mock_uपंचांगi_clk.clkr,
	[GCC_USB30_SEC_MOCK_UTMI_CLK_SRC] =
					&gcc_usb30_sec_mock_uपंचांगi_clk_src.clkr,
	[GCC_USB30_SEC_SLEEP_CLK] = &gcc_usb30_sec_sleep_clk.clkr,
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
	[GCC_USB_PHY_CFG_AHB2PHY_CLK] = &gcc_usb_phy_cfg_ahb2phy_clk.clkr,
	[GCC_VDDA_VS_CLK] = &gcc_vdda_vs_clk.clkr,
	[GCC_VDDCX_VS_CLK] = &gcc_vddcx_vs_clk.clkr,
	[GCC_VDDMX_VS_CLK] = &gcc_vddmx_vs_clk.clkr,
	[GCC_VIDEO_AHB_CLK] = &gcc_video_ahb_clk.clkr,
	[GCC_VIDEO_AXI_CLK] = &gcc_video_axi_clk.clkr,
	[GCC_VIDEO_XO_CLK] = &gcc_video_xo_clk.clkr,
	[GCC_VS_CTRL_AHB_CLK] = &gcc_vs_ctrl_ahb_clk.clkr,
	[GCC_VS_CTRL_CLK] = &gcc_vs_ctrl_clk.clkr,
	[GCC_VS_CTRL_CLK_SRC] = &gcc_vs_ctrl_clk_src.clkr,
	[GCC_VSENSOR_CLK_SRC] = &gcc_vsensor_clk_src.clkr,
	[GPLL0] = &gpll0.clkr,
	[GPLL0_OUT_EVEN] = &gpll0_out_even.clkr,
	[GPLL4] = &gpll4.clkr,
	[GCC_CPUSS_DVM_BUS_CLK] = &gcc_cpuss_dvm_bus_clk.clkr,
	[GCC_CPUSS_GNOC_CLK] = &gcc_cpuss_gnoc_clk.clkr,
	[GCC_QSPI_CORE_CLK_SRC] = &gcc_qspi_core_clk_src.clkr,
	[GCC_QSPI_CORE_CLK] = &gcc_qspi_core_clk.clkr,
	[GCC_QSPI_CNOC_PERIPH_AHB_CLK] = &gcc_qspi_cnoc_periph_ahb_clk.clkr,
#अगर_घोषित CONFIG_SDM_LPASSCC_845
	[GCC_LPASS_Q6_AXI_CLK] = &gcc_lpass_q6_axi_clk.clkr,
	[GCC_LPASS_SWAY_CLK] = &gcc_lpass_sway_clk.clkr,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map gcc_sdm845_resets[] = अणु
	[GCC_MMSS_BCR] = अणु 0xb000 पूर्ण,
	[GCC_PCIE_0_BCR] = अणु 0x6b000 पूर्ण,
	[GCC_PCIE_1_BCR] = अणु 0x8d000 पूर्ण,
	[GCC_PCIE_PHY_BCR] = अणु 0x6f000 पूर्ण,
	[GCC_PDM_BCR] = अणु 0x33000 पूर्ण,
	[GCC_PRNG_BCR] = अणु 0x34000 पूर्ण,
	[GCC_QUPV3_WRAPPER_0_BCR] = अणु 0x17000 पूर्ण,
	[GCC_QUPV3_WRAPPER_1_BCR] = अणु 0x18000 पूर्ण,
	[GCC_QUSB2PHY_PRIM_BCR] = अणु 0x12000 पूर्ण,
	[GCC_QUSB2PHY_SEC_BCR] = अणु 0x12004 पूर्ण,
	[GCC_SDCC2_BCR] = अणु 0x14000 पूर्ण,
	[GCC_SDCC4_BCR] = अणु 0x16000 पूर्ण,
	[GCC_TSIF_BCR] = अणु 0x36000 पूर्ण,
	[GCC_UFS_CARD_BCR] = अणु 0x75000 पूर्ण,
	[GCC_UFS_PHY_BCR] = अणु 0x77000 पूर्ण,
	[GCC_USB30_PRIM_BCR] = अणु 0xf000 पूर्ण,
	[GCC_USB30_SEC_BCR] = अणु 0x10000 पूर्ण,
	[GCC_USB3_PHY_PRIM_BCR] = अणु 0x50000 पूर्ण,
	[GCC_USB3PHY_PHY_PRIM_BCR] = अणु 0x50004 पूर्ण,
	[GCC_USB3_DP_PHY_PRIM_BCR] = अणु 0x50008 पूर्ण,
	[GCC_USB3_PHY_SEC_BCR] = अणु 0x5000c पूर्ण,
	[GCC_USB3PHY_PHY_SEC_BCR] = अणु 0x50010 पूर्ण,
	[GCC_USB3_DP_PHY_SEC_BCR] = अणु 0x50014 पूर्ण,
	[GCC_USB_PHY_CFG_AHB2PHY_BCR] = अणु 0x6a000 पूर्ण,
	[GCC_PCIE_0_PHY_BCR] = अणु 0x6c01c पूर्ण,
	[GCC_PCIE_1_PHY_BCR] = अणु 0x8e01c पूर्ण,
पूर्ण;

अटल काष्ठा gdsc *gcc_sdm845_gdscs[] = अणु
	[PCIE_0_GDSC] = &pcie_0_gdsc,
	[PCIE_1_GDSC] = &pcie_1_gdsc,
	[UFS_CARD_GDSC] = &ufs_card_gdsc,
	[UFS_PHY_GDSC] = &ufs_phy_gdsc,
	[USB30_PRIM_GDSC] = &usb30_prim_gdsc,
	[USB30_SEC_GDSC] = &usb30_sec_gdsc,
	[HLOS1_VOTE_AGGRE_NOC_MMU_AUDIO_TBU_GDSC] =
			&hlos1_vote_aggre_noc_mmu_audio_tbu_gdsc,
	[HLOS1_VOTE_AGGRE_NOC_MMU_PCIE_TBU_GDSC] =
			&hlos1_vote_aggre_noc_mmu_pcie_tbu_gdsc,
	[HLOS1_VOTE_AGGRE_NOC_MMU_TBU1_GDSC] =
			&hlos1_vote_aggre_noc_mmu_tbu1_gdsc,
	[HLOS1_VOTE_AGGRE_NOC_MMU_TBU2_GDSC] =
			&hlos1_vote_aggre_noc_mmu_tbu2_gdsc,
	[HLOS1_VOTE_MMNOC_MMU_TBU_HF0_GDSC] =
			&hlos1_vote_mmnoc_mmu_tbu_hf0_gdsc,
	[HLOS1_VOTE_MMNOC_MMU_TBU_HF1_GDSC] =
			&hlos1_vote_mmnoc_mmu_tbu_hf1_gdsc,
	[HLOS1_VOTE_MMNOC_MMU_TBU_SF_GDSC] = &hlos1_vote_mmnoc_mmu_tbu_sf_gdsc,
पूर्ण;

अटल स्थिर काष्ठा regmap_config gcc_sdm845_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x182090,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc gcc_sdm845_desc = अणु
	.config = &gcc_sdm845_regmap_config,
	.clks = gcc_sdm845_घड़ीs,
	.num_clks = ARRAY_SIZE(gcc_sdm845_घड़ीs),
	.resets = gcc_sdm845_resets,
	.num_resets = ARRAY_SIZE(gcc_sdm845_resets),
	.gdscs = gcc_sdm845_gdscs,
	.num_gdscs = ARRAY_SIZE(gcc_sdm845_gdscs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id gcc_sdm845_match_table[] = अणु
	अणु .compatible = "qcom,gcc-sdm845" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gcc_sdm845_match_table);

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

अटल पूर्णांक gcc_sdm845_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	regmap = qcom_cc_map(pdev, &gcc_sdm845_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/* Disable the GPLL0 active input to MMSS and GPU via MISC रेजिस्टरs */
	regmap_update_bits(regmap, 0x09ffc, 0x3, 0x3);
	regmap_update_bits(regmap, 0x71028, 0x3, 0x3);

	ret = qcom_cc_रेजिस्टर_rcg_dfs(regmap, gcc_dfs_घड़ीs,
					ARRAY_SIZE(gcc_dfs_घड़ीs));
	अगर (ret)
		वापस ret;

	वापस qcom_cc_really_probe(pdev, &gcc_sdm845_desc, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver gcc_sdm845_driver = अणु
	.probe		= gcc_sdm845_probe,
	.driver		= अणु
		.name	= "gcc-sdm845",
		.of_match_table = gcc_sdm845_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init gcc_sdm845_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&gcc_sdm845_driver);
पूर्ण
core_initcall(gcc_sdm845_init);

अटल व्योम __निकास gcc_sdm845_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&gcc_sdm845_driver);
पूर्ण
module_निकास(gcc_sdm845_निकास);

MODULE_DESCRIPTION("QTI GCC SDM845 Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:gcc-sdm845");
