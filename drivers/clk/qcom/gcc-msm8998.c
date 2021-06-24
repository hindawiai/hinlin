<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016, The Linux Foundation. All rights reserved.
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

#समावेश <dt-bindings/घड़ी/qcom,gcc-msm8998.h>

#समावेश "common.h"
#समावेश "clk-regmap.h"
#समावेश "clk-alpha-pll.h"
#समावेश "clk-pll.h"
#समावेश "clk-rcg.h"
#समावेश "clk-branch.h"
#समावेश "reset.h"
#समावेश "gdsc.h"

क्रमागत अणु
	P_AUD_REF_CLK,
	P_CORE_BI_PLL_TEST_SE,
	P_GPLL0_OUT_MAIN,
	P_GPLL4_OUT_MAIN,
	P_PLL0_EARLY_DIV_CLK_SRC,
	P_SLEEP_CLK,
	P_XO,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_0[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_PLL0_EARLY_DIV_CLK_SRC, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_parent_names_0[] = अणु
	"xo",
	"gpll0_out_main",
	"gpll0_out_main",
	"core_bi_pll_test_se",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_1[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_parent_names_1[] = अणु
	"xo",
	"gpll0_out_main",
	"core_bi_pll_test_se",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_2[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_SLEEP_CLK, 5 पूर्ण,
	अणु P_PLL0_EARLY_DIV_CLK_SRC, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_parent_names_2[] = अणु
	"xo",
	"gpll0_out_main",
	"core_pi_sleep_clk",
	"gpll0_out_main",
	"core_bi_pll_test_se",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_3[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_SLEEP_CLK, 5 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_parent_names_3[] = अणु
	"xo",
	"core_pi_sleep_clk",
	"core_bi_pll_test_se",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_4[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_GPLL4_OUT_MAIN, 5 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_parent_names_4[] = अणु
	"xo",
	"gpll0_out_main",
	"gpll4_out_main",
	"core_bi_pll_test_se",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_parent_map_5[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 1 पूर्ण,
	अणु P_AUD_REF_CLK, 2 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_parent_names_5[] = अणु
	"xo",
	"gpll0_out_main",
	"aud_ref_clk",
	"core_bi_pll_test_se",
पूर्ण;

अटल काष्ठा clk_fixed_factor xo = अणु
	.mult = 1,
	.भाग = 1,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "xo",
		.parent_names = (स्थिर अक्षर *[])अणु "xo_board" पूर्ण,
		.num_parents = 1,
		.ops = &clk_fixed_factor_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा pll_vco fabia_vco[] = अणु
	अणु 250000000, 2000000000, 0 पूर्ण,
	अणु 125000000, 1000000000, 1 पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll gpll0 = अणु
	.offset = 0x0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.vco_table = fabia_vco,
	.num_vco = ARRAY_SIZE(fabia_vco),
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpll0",
			.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_fabia_ops,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll0_out_even = अणु
	.offset = 0x0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll0_out_even",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll0" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll0_out_मुख्य = अणु
	.offset = 0x0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll0_out_main",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll0" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll0_out_odd = अणु
	.offset = 0x0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll0_out_odd",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll0" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll0_out_test = अणु
	.offset = 0x0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll0_out_test",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll0" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll gpll1 = अणु
	.offset = 0x1000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.vco_table = fabia_vco,
	.num_vco = ARRAY_SIZE(fabia_vco),
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpll1",
			.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_fabia_ops,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll1_out_even = अणु
	.offset = 0x1000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll1_out_even",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll1" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll1_out_मुख्य = अणु
	.offset = 0x1000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll1_out_main",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll1" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll1_out_odd = अणु
	.offset = 0x1000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll1_out_odd",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll1" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll1_out_test = अणु
	.offset = 0x1000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll1_out_test",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll1" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll gpll2 = अणु
	.offset = 0x2000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.vco_table = fabia_vco,
	.num_vco = ARRAY_SIZE(fabia_vco),
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpll2",
			.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_fabia_ops,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll2_out_even = अणु
	.offset = 0x2000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll2_out_even",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll2" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll2_out_मुख्य = अणु
	.offset = 0x2000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll2_out_main",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll2" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll2_out_odd = अणु
	.offset = 0x2000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll2_out_odd",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll2" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll2_out_test = अणु
	.offset = 0x2000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll2_out_test",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll2" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll gpll3 = अणु
	.offset = 0x3000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.vco_table = fabia_vco,
	.num_vco = ARRAY_SIZE(fabia_vco),
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(3),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpll3",
			.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_fabia_ops,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll3_out_even = अणु
	.offset = 0x3000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll3_out_even",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll3" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll3_out_मुख्य = अणु
	.offset = 0x3000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll3_out_main",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll3" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll3_out_odd = अणु
	.offset = 0x3000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll3_out_odd",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll3" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll3_out_test = अणु
	.offset = 0x3000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll3_out_test",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll3" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll gpll4 = अणु
	.offset = 0x77000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.vco_table = fabia_vco,
	.num_vco = ARRAY_SIZE(fabia_vco),
	.clkr = अणु
		.enable_reg = 0x52000,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpll4",
			.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fixed_fabia_ops,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll4_out_even = अणु
	.offset = 0x77000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll4_out_even",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll4" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll4_out_मुख्य = अणु
	.offset = 0x77000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll4_out_main",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll4" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll4_out_odd = अणु
	.offset = 0x77000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll4_out_odd",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll4" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll4_out_test = अणु
	.offset = 0x77000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll4_out_test",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll4" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_blsp1_qup1_i2c_apps_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(50000000, P_GPLL0_OUT_MAIN, 12, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup1_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x19020,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_blsp1_qup1_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup1_i2c_apps_clk_src",
		.parent_names = gcc_parent_names_1,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_blsp1_qup1_spi_apps_clk_src[] = अणु
	F(960000, P_XO, 10, 1, 2),
	F(4800000, P_XO, 4, 0, 0),
	F(9600000, P_XO, 2, 0, 0),
	F(15000000, P_GPLL0_OUT_MAIN, 10, 1, 4),
	F(19200000, P_XO, 1, 0, 0),
	F(25000000, P_GPLL0_OUT_MAIN, 12, 1, 2),
	F(50000000, P_GPLL0_OUT_MAIN, 12, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup1_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x1900c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_blsp1_qup1_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup1_spi_apps_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup2_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x1b020,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_blsp1_qup1_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup2_i2c_apps_clk_src",
		.parent_names = gcc_parent_names_1,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup2_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x1b00c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_blsp1_qup1_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup2_spi_apps_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup3_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x1d020,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_blsp1_qup1_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup3_i2c_apps_clk_src",
		.parent_names = gcc_parent_names_1,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup3_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x1d00c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_blsp1_qup1_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup3_spi_apps_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup4_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x1f020,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_blsp1_qup1_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup4_i2c_apps_clk_src",
		.parent_names = gcc_parent_names_1,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup4_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x1f00c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_blsp1_qup1_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup4_spi_apps_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup5_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x21020,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_blsp1_qup1_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup5_i2c_apps_clk_src",
		.parent_names = gcc_parent_names_1,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup5_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x2100c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_blsp1_qup1_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup5_spi_apps_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup6_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x23020,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_blsp1_qup1_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup6_i2c_apps_clk_src",
		.parent_names = gcc_parent_names_1,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup6_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x2300c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_blsp1_qup1_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup6_spi_apps_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_blsp1_uart1_apps_clk_src[] = अणु
	F(3686400, P_GPLL0_OUT_MAIN, 1, 96, 15625),
	F(7372800, P_GPLL0_OUT_MAIN, 1, 192, 15625),
	F(14745600, P_GPLL0_OUT_MAIN, 1, 384, 15625),
	F(16000000, P_GPLL0_OUT_MAIN, 5, 2, 15),
	F(19200000, P_XO, 1, 0, 0),
	F(24000000, P_GPLL0_OUT_MAIN, 5, 1, 5),
	F(32000000, P_GPLL0_OUT_MAIN, 1, 4, 75),
	F(40000000, P_GPLL0_OUT_MAIN, 15, 0, 0),
	F(46400000, P_GPLL0_OUT_MAIN, 1, 29, 375),
	F(48000000, P_GPLL0_OUT_MAIN, 12.5, 0, 0),
	F(51200000, P_GPLL0_OUT_MAIN, 1, 32, 375),
	F(56000000, P_GPLL0_OUT_MAIN, 1, 7, 75),
	F(58982400, P_GPLL0_OUT_MAIN, 1, 1536, 15625),
	F(60000000, P_GPLL0_OUT_MAIN, 10, 0, 0),
	F(63157895, P_GPLL0_OUT_MAIN, 9.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_uart1_apps_clk_src = अणु
	.cmd_rcgr = 0x1a00c,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_blsp1_uart1_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_uart1_apps_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_uart2_apps_clk_src = अणु
	.cmd_rcgr = 0x1c00c,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_blsp1_uart1_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_uart2_apps_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_uart3_apps_clk_src = अणु
	.cmd_rcgr = 0x1e00c,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_blsp1_uart1_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_uart3_apps_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup1_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x26020,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_blsp1_qup1_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp2_qup1_i2c_apps_clk_src",
		.parent_names = gcc_parent_names_1,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup1_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x2600c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_blsp1_qup1_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp2_qup1_spi_apps_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup2_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x28020,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_blsp1_qup1_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp2_qup2_i2c_apps_clk_src",
		.parent_names = gcc_parent_names_1,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup2_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x2800c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_blsp1_qup1_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp2_qup2_spi_apps_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup3_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x2a020,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_blsp1_qup1_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp2_qup3_i2c_apps_clk_src",
		.parent_names = gcc_parent_names_1,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup3_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x2a00c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_blsp1_qup1_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp2_qup3_spi_apps_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup4_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x2c020,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_blsp1_qup1_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp2_qup4_i2c_apps_clk_src",
		.parent_names = gcc_parent_names_1,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup4_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x2c00c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_blsp1_qup1_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp2_qup4_spi_apps_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup5_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x2e020,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_blsp1_qup1_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp2_qup5_i2c_apps_clk_src",
		.parent_names = gcc_parent_names_1,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup5_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x2e00c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_blsp1_qup1_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp2_qup5_spi_apps_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup6_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x30020,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_blsp1_qup1_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp2_qup6_i2c_apps_clk_src",
		.parent_names = gcc_parent_names_1,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup6_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x3000c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_blsp1_qup1_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp2_qup6_spi_apps_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_uart1_apps_clk_src = अणु
	.cmd_rcgr = 0x2700c,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_blsp1_uart1_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp2_uart1_apps_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_uart2_apps_clk_src = अणु
	.cmd_rcgr = 0x2900c,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_blsp1_uart1_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp2_uart2_apps_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_uart3_apps_clk_src = अणु
	.cmd_rcgr = 0x2b00c,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_blsp1_uart1_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp2_uart3_apps_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gp1_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(100000000, P_GPLL0_OUT_MAIN, 6, 0, 0),
	F(200000000, P_GPLL0_OUT_MAIN, 3, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gp1_clk_src = अणु
	.cmd_rcgr = 0x64004,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_2,
	.freq_tbl = ftbl_gp1_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gp1_clk_src",
		.parent_names = gcc_parent_names_2,
		.num_parents = 5,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gp2_clk_src = अणु
	.cmd_rcgr = 0x65004,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_2,
	.freq_tbl = ftbl_gp1_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gp2_clk_src",
		.parent_names = gcc_parent_names_2,
		.num_parents = 5,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gp3_clk_src = अणु
	.cmd_rcgr = 0x66004,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_2,
	.freq_tbl = ftbl_gp1_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gp3_clk_src",
		.parent_names = gcc_parent_names_2,
		.num_parents = 5,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_hmss_ahb_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(37500000, P_GPLL0_OUT_MAIN, 16, 0, 0),
	F(75000000, P_GPLL0_OUT_MAIN, 8, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 hmss_ahb_clk_src = अणु
	.cmd_rcgr = 0x48014,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_hmss_ahb_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "hmss_ahb_clk_src",
		.parent_names = gcc_parent_names_1,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_hmss_rbcpr_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 hmss_rbcpr_clk_src = अणु
	.cmd_rcgr = 0x48044,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_hmss_rbcpr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "hmss_rbcpr_clk_src",
		.parent_names = gcc_parent_names_1,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_pcie_aux_clk_src[] = अणु
	F(1010526, P_XO, 1, 1, 19),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 pcie_aux_clk_src = अणु
	.cmd_rcgr = 0x6c000,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_parent_map_3,
	.freq_tbl = ftbl_pcie_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pcie_aux_clk_src",
		.parent_names = gcc_parent_names_3,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_pdm2_clk_src[] = अणु
	F(60000000, P_GPLL0_OUT_MAIN, 10, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 pdm2_clk_src = अणु
	.cmd_rcgr = 0x33010,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_pdm2_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pdm2_clk_src",
		.parent_names = gcc_parent_names_1,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_sdcc2_apps_clk_src[] = अणु
	F(144000, P_XO, 16, 3, 25),
	F(400000, P_XO, 12, 1, 4),
	F(20000000, P_GPLL0_OUT_MAIN, 15, 1, 2),
	F(25000000, P_GPLL0_OUT_MAIN, 12, 1, 2),
	F(50000000, P_GPLL0_OUT_MAIN, 12, 0, 0),
	F(100000000, P_GPLL0_OUT_MAIN, 6, 0, 0),
	F(200000000, P_GPLL0_OUT_MAIN, 3, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 sdcc2_apps_clk_src = अणु
	.cmd_rcgr = 0x14010,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_4,
	.freq_tbl = ftbl_sdcc2_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sdcc2_apps_clk_src",
		.parent_names = gcc_parent_names_4,
		.num_parents = 4,
		.ops = &clk_rcg2_न्यूनमान_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_sdcc4_apps_clk_src[] = अणु
	F(144000, P_XO, 16, 3, 25),
	F(400000, P_XO, 12, 1, 4),
	F(20000000, P_GPLL0_OUT_MAIN, 15, 1, 2),
	F(25000000, P_GPLL0_OUT_MAIN, 12, 1, 2),
	F(50000000, P_GPLL0_OUT_MAIN, 12, 0, 0),
	F(100000000, P_GPLL0_OUT_MAIN, 6, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 sdcc4_apps_clk_src = अणु
	.cmd_rcgr = 0x16010,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_sdcc4_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sdcc4_apps_clk_src",
		.parent_names = gcc_parent_names_1,
		.num_parents = 3,
		.ops = &clk_rcg2_न्यूनमान_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_tsअगर_ref_clk_src[] = अणु
	F(105495, P_XO, 1, 1, 182),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 tsअगर_ref_clk_src = अणु
	.cmd_rcgr = 0x36010,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_5,
	.freq_tbl = ftbl_tsअगर_ref_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "tsif_ref_clk_src",
		.parent_names = gcc_parent_names_5,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_ufs_axi_clk_src[] = अणु
	F(100000000, P_GPLL0_OUT_MAIN, 6, 0, 0),
	F(200000000, P_GPLL0_OUT_MAIN, 3, 0, 0),
	F(240000000, P_GPLL0_OUT_MAIN, 2.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 ufs_axi_clk_src = अणु
	.cmd_rcgr = 0x75018,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_ufs_axi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ufs_axi_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_ufs_unipro_core_clk_src[] = अणु
	F(37500000, P_GPLL0_OUT_MAIN, 16, 0, 0),
	F(75000000, P_GPLL0_OUT_MAIN, 8, 0, 0),
	F(150000000, P_GPLL0_OUT_MAIN, 4, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 ufs_unipro_core_clk_src = अणु
	.cmd_rcgr = 0x76028,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_ufs_unipro_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ufs_unipro_core_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_usb30_master_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(60000000, P_GPLL0_OUT_MAIN, 10, 0, 0),
	F(120000000, P_GPLL0_OUT_MAIN, 5, 0, 0),
	F(150000000, P_GPLL0_OUT_MAIN, 4, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 usb30_master_clk_src = अणु
	.cmd_rcgr = 0xf014,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_usb30_master_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "usb30_master_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 usb30_mock_uपंचांगi_clk_src = अणु
	.cmd_rcgr = 0xf028,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_0,
	.freq_tbl = ftbl_hmss_rbcpr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "usb30_mock_utmi_clk_src",
		.parent_names = gcc_parent_names_0,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_usb3_phy_aux_clk_src[] = अणु
	F(1200000, P_XO, 16, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 usb3_phy_aux_clk_src = अणु
	.cmd_rcgr = 0x5000c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gcc_parent_map_3,
	.freq_tbl = ftbl_usb3_phy_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "usb3_phy_aux_clk_src",
		.parent_names = gcc_parent_names_3,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre1_noc_xo_clk = अणु
	.halt_reg = 0x8202c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8202c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_aggre1_noc_xo_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre1_ufs_axi_clk = अणु
	.halt_reg = 0x82028,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x82028,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_aggre1_ufs_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ufs_axi_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_aggre1_usb3_axi_clk = अणु
	.halt_reg = 0x82024,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x82024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_aggre1_usb3_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"usb30_master_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_apss_qdss_tsctr_भाग2_clk = अणु
	.halt_reg = 0x48090,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x48090,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_apss_qdss_tsctr_div2_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_apss_qdss_tsctr_भाग8_clk = अणु
	.halt_reg = 0x48094,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x48094,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_apss_qdss_tsctr_div8_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_bimc_hmss_axi_clk = अणु
	.halt_reg = 0x48004,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(22),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_bimc_hmss_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_bimc_mss_q6_axi_clk = अणु
	.halt_reg = 0x4401c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x4401c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_bimc_mss_q6_axi_clk",
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

अटल काष्ठा clk_branch gcc_mss_snoc_axi_clk = अणु
	.halt_reg = 0x8a03c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8a03c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_snoc_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mss_mnoc_bimc_axi_clk = अणु
	.halt_reg = 0x8a004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8a004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_mnoc_bimc_axi_clk",
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

अटल काष्ठा clk_branch gcc_mmss_gpll0_clk = अणु
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mmss_gpll0_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gpll0_out_main",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mss_gpll0_भाग_clk_src = अणु
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x5200c,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_gpll0_div_clk_src",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_ahb_clk = अणु
	.halt_reg = 0x17004,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(17),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup1_i2c_apps_clk = अणु
	.halt_reg = 0x19008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x19008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup1_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup1_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup1_spi_apps_clk = अणु
	.halt_reg = 0x19004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x19004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup1_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup1_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup2_i2c_apps_clk = अणु
	.halt_reg = 0x1b008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x1b008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup2_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup2_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup2_spi_apps_clk = अणु
	.halt_reg = 0x1b004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x1b004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup2_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup2_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup3_i2c_apps_clk = अणु
	.halt_reg = 0x1d008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x1d008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup3_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup3_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup3_spi_apps_clk = अणु
	.halt_reg = 0x1d004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x1d004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup3_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup3_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup4_i2c_apps_clk = अणु
	.halt_reg = 0x1f008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x1f008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup4_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup4_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup4_spi_apps_clk = अणु
	.halt_reg = 0x1f004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x1f004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup4_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup4_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup5_i2c_apps_clk = अणु
	.halt_reg = 0x21008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x21008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup5_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup5_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup5_spi_apps_clk = अणु
	.halt_reg = 0x21004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x21004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup5_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup5_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup6_i2c_apps_clk = अणु
	.halt_reg = 0x23008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x23008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup6_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup6_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup6_spi_apps_clk = अणु
	.halt_reg = 0x23004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x23004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup6_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup6_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_sleep_clk = अणु
	.halt_reg = 0x17008,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(16),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_sleep_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_uart1_apps_clk = अणु
	.halt_reg = 0x1a004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x1a004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_uart1_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_uart1_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_uart2_apps_clk = अणु
	.halt_reg = 0x1c004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x1c004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_uart2_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_uart2_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_uart3_apps_clk = अणु
	.halt_reg = 0x1e004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x1e004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_uart3_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_uart3_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_ahb_clk = अणु
	.halt_reg = 0x25004,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(15),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup1_i2c_apps_clk = अणु
	.halt_reg = 0x26008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x26008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup1_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp2_qup1_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup1_spi_apps_clk = अणु
	.halt_reg = 0x26004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x26004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup1_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp2_qup1_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup2_i2c_apps_clk = अणु
	.halt_reg = 0x28008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x28008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup2_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp2_qup2_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup2_spi_apps_clk = अणु
	.halt_reg = 0x28004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x28004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup2_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp2_qup2_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup3_i2c_apps_clk = अणु
	.halt_reg = 0x2a008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2a008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup3_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp2_qup3_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup3_spi_apps_clk = अणु
	.halt_reg = 0x2a004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2a004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup3_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp2_qup3_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup4_i2c_apps_clk = अणु
	.halt_reg = 0x2c008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2c008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup4_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp2_qup4_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup4_spi_apps_clk = अणु
	.halt_reg = 0x2c004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2c004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup4_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp2_qup4_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup5_i2c_apps_clk = अणु
	.halt_reg = 0x2e008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2e008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup5_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp2_qup5_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup5_spi_apps_clk = अणु
	.halt_reg = 0x2e004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2e004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup5_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp2_qup5_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup6_i2c_apps_clk = अणु
	.halt_reg = 0x30008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x30008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup6_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp2_qup6_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup6_spi_apps_clk = अणु
	.halt_reg = 0x30004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x30004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup6_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp2_qup6_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_sleep_clk = अणु
	.halt_reg = 0x25008,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(14),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_sleep_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_uart1_apps_clk = अणु
	.halt_reg = 0x27004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x27004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_uart1_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp2_uart1_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_uart2_apps_clk = अणु
	.halt_reg = 0x29004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x29004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_uart2_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp2_uart2_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_uart3_apps_clk = अणु
	.halt_reg = 0x2b004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x2b004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_uart3_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp2_uart3_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_cfg_noc_usb3_axi_clk = अणु
	.halt_reg = 0x5018,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x5018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_cfg_noc_usb3_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"usb30_master_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"gp1_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"gp2_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"gp3_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_bimc_gfx_clk = अणु
	.halt_reg = 0x46040,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x46040,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_bimc_gfx_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gpu_bimc_gfx_clk = अणु
	.halt_reg = 0x71010,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x71010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gpu_bimc_gfx_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gpu_bimc_gfx_src_clk = अणु
	.halt_reg = 0x7100c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x7100c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gpu_bimc_gfx_src_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gpu_cfg_ahb_clk = अणु
	.halt_reg = 0x71004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x71004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gpu_cfg_ahb_clk",
			.ops = &clk_branch2_ops,
			/*
			 * The GPU IOMMU depends on this घड़ी and hypervisor
			 * will crash the SoC अगर this घड़ी goes करोwn, due to
			 * secure contexts protection.
			 */
			.flags = CLK_IS_CRITICAL,
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

अटल काष्ठा clk_branch gcc_hmss_ahb_clk = अणु
	.halt_reg = 0x48000,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x52004,
		.enable_mask = BIT(21),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_hmss_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"hmss_ahb_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_hmss_at_clk = अणु
	.halt_reg = 0x48010,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x48010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_hmss_at_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_hmss_rbcpr_clk = अणु
	.halt_reg = 0x48008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x48008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_hmss_rbcpr_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"hmss_rbcpr_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_hmss_trig_clk = अणु
	.halt_reg = 0x4800c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x4800c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_hmss_trig_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_hmss_gpll0_clk_src[] = अणु
	F( 300000000, P_GPLL0_OUT_MAIN, 2, 0, 0),
	F( 600000000, P_GPLL0_OUT_MAIN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 hmss_gpll0_clk_src = अणु
	.cmd_rcgr = 0x4805c,
	.hid_width = 5,
	.parent_map = gcc_parent_map_1,
	.freq_tbl = ftbl_hmss_gpll0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "hmss_gpll0_clk_src",
		.parent_names = gcc_parent_names_1,
		.num_parents = ARRAY_SIZE(gcc_parent_names_1),
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mmss_noc_cfg_ahb_clk = अणु
	.halt_reg = 0x9004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mmss_noc_cfg_ahb_clk",
			.ops = &clk_branch2_ops,
			/*
			 * Any access to mmss depends on this घड़ी.
			 * Gating this घड़ी has been shown to crash the प्रणाली
			 * when mmssnoc_axi_rpm_clk is inited in rpmcc.
			 */
			.flags = CLK_IS_CRITICAL,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mmss_qm_ahb_clk = अणु
	.halt_reg = 0x9030,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9030,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mmss_qm_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mmss_qm_core_clk = अणु
	.halt_reg = 0x900c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x900c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mmss_qm_core_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mmss_sys_noc_axi_clk = अणु
	.halt_reg = 0x9000,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mmss_sys_noc_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mss_at_clk = अणु
	.halt_reg = 0x8a00c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8a00c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_at_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_aux_clk = अणु
	.halt_reg = 0x6b014,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6b014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_aux_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcie_aux_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_cfg_ahb_clk = अणु
	.halt_reg = 0x6b010,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6b010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_cfg_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_mstr_axi_clk = अणु
	.halt_reg = 0x6b00c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6b00c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_mstr_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_pipe_clk = अणु
	.halt_reg = 0x6b018,
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x6b018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_pipe_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_slv_axi_clk = अणु
	.halt_reg = 0x6b008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6b008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_slv_axi_clk",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcie_aux_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"pdm2_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"sdcc2_apps_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"sdcc4_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"tsif_ref_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_ahb_clk = अणु
	.halt_reg = 0x7500c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x7500c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_axi_clk = अणु
	.halt_reg = 0x75008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x75008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ufs_axi_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_ice_core_clk = अणु
	.halt_reg = 0x7600c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x7600c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_ice_core_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_phy_aux_clk = अणु
	.halt_reg = 0x76040,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x76040,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_phy_aux_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_rx_symbol_0_clk = अणु
	.halt_reg = 0x75014,
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x75014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_rx_symbol_0_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_rx_symbol_1_clk = अणु
	.halt_reg = 0x7605c,
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x7605c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_rx_symbol_1_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_tx_symbol_0_clk = अणु
	.halt_reg = 0x75010,
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x75010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_tx_symbol_0_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_unipro_core_clk = अणु
	.halt_reg = 0x76008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x76008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_unipro_core_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ufs_unipro_core_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_master_clk = अणु
	.halt_reg = 0xf008,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_master_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"usb30_master_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_mock_uपंचांगi_clk = अणु
	.halt_reg = 0xf010,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_mock_utmi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"usb30_mock_utmi_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_sleep_clk = अणु
	.halt_reg = 0xf00c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xf00c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_sleep_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_phy_aux_clk = अणु
	.halt_reg = 0x50000,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x50000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_phy_aux_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"usb3_phy_aux_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_phy_pipe_clk = अणु
	.halt_reg = 0x50004,
	.halt_check = BRANCH_HALT_SKIP,
	.clkr = अणु
		.enable_reg = 0x50004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_phy_pipe_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb_phy_cfg_ahb2phy_clk = अणु
	.halt_reg = 0x6a004,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6a004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb_phy_cfg_ahb2phy_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_hdmi_clkref_clk = अणु
	.halt_reg = 0x88000,
	.clkr = अणु
		.enable_reg = 0x88000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_hdmi_clkref_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_clkref_clk = अणु
	.halt_reg = 0x88004,
	.clkr = अणु
		.enable_reg = 0x88004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_clkref_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_clkref_clk = अणु
	.halt_reg = 0x88008,
	.clkr = अणु
		.enable_reg = 0x88008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_clkref_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_clkref_clk = अणु
	.halt_reg = 0x8800c,
	.clkr = अणु
		.enable_reg = 0x8800c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_clkref_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_rx1_usb2_clkref_clk = अणु
	.halt_reg = 0x88014,
	.clkr = अणु
		.enable_reg = 0x88014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_rx1_usb2_clkref_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gdsc pcie_0_gdsc = अणु
	.gdscr = 0x6b004,
	.gds_hw_ctrl = 0x0,
	.pd = अणु
		.name = "pcie_0_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc ufs_gdsc = अणु
	.gdscr = 0x75004,
	.gds_hw_ctrl = 0x0,
	.pd = अणु
		.name = "ufs_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc usb_30_gdsc = अणु
	.gdscr = 0xf004,
	.gds_hw_ctrl = 0x0,
	.pd = अणु
		.name = "usb_30_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा clk_regmap *gcc_msm8998_घड़ीs[] = अणु
	[BLSP1_QUP1_I2C_APPS_CLK_SRC] = &blsp1_qup1_i2c_apps_clk_src.clkr,
	[BLSP1_QUP1_SPI_APPS_CLK_SRC] = &blsp1_qup1_spi_apps_clk_src.clkr,
	[BLSP1_QUP2_I2C_APPS_CLK_SRC] = &blsp1_qup2_i2c_apps_clk_src.clkr,
	[BLSP1_QUP2_SPI_APPS_CLK_SRC] = &blsp1_qup2_spi_apps_clk_src.clkr,
	[BLSP1_QUP3_I2C_APPS_CLK_SRC] = &blsp1_qup3_i2c_apps_clk_src.clkr,
	[BLSP1_QUP3_SPI_APPS_CLK_SRC] = &blsp1_qup3_spi_apps_clk_src.clkr,
	[BLSP1_QUP4_I2C_APPS_CLK_SRC] = &blsp1_qup4_i2c_apps_clk_src.clkr,
	[BLSP1_QUP4_SPI_APPS_CLK_SRC] = &blsp1_qup4_spi_apps_clk_src.clkr,
	[BLSP1_QUP5_I2C_APPS_CLK_SRC] = &blsp1_qup5_i2c_apps_clk_src.clkr,
	[BLSP1_QUP5_SPI_APPS_CLK_SRC] = &blsp1_qup5_spi_apps_clk_src.clkr,
	[BLSP1_QUP6_I2C_APPS_CLK_SRC] = &blsp1_qup6_i2c_apps_clk_src.clkr,
	[BLSP1_QUP6_SPI_APPS_CLK_SRC] = &blsp1_qup6_spi_apps_clk_src.clkr,
	[BLSP1_UART1_APPS_CLK_SRC] = &blsp1_uart1_apps_clk_src.clkr,
	[BLSP1_UART2_APPS_CLK_SRC] = &blsp1_uart2_apps_clk_src.clkr,
	[BLSP1_UART3_APPS_CLK_SRC] = &blsp1_uart3_apps_clk_src.clkr,
	[BLSP2_QUP1_I2C_APPS_CLK_SRC] = &blsp2_qup1_i2c_apps_clk_src.clkr,
	[BLSP2_QUP1_SPI_APPS_CLK_SRC] = &blsp2_qup1_spi_apps_clk_src.clkr,
	[BLSP2_QUP2_I2C_APPS_CLK_SRC] = &blsp2_qup2_i2c_apps_clk_src.clkr,
	[BLSP2_QUP2_SPI_APPS_CLK_SRC] = &blsp2_qup2_spi_apps_clk_src.clkr,
	[BLSP2_QUP3_I2C_APPS_CLK_SRC] = &blsp2_qup3_i2c_apps_clk_src.clkr,
	[BLSP2_QUP3_SPI_APPS_CLK_SRC] = &blsp2_qup3_spi_apps_clk_src.clkr,
	[BLSP2_QUP4_I2C_APPS_CLK_SRC] = &blsp2_qup4_i2c_apps_clk_src.clkr,
	[BLSP2_QUP4_SPI_APPS_CLK_SRC] = &blsp2_qup4_spi_apps_clk_src.clkr,
	[BLSP2_QUP5_I2C_APPS_CLK_SRC] = &blsp2_qup5_i2c_apps_clk_src.clkr,
	[BLSP2_QUP5_SPI_APPS_CLK_SRC] = &blsp2_qup5_spi_apps_clk_src.clkr,
	[BLSP2_QUP6_I2C_APPS_CLK_SRC] = &blsp2_qup6_i2c_apps_clk_src.clkr,
	[BLSP2_QUP6_SPI_APPS_CLK_SRC] = &blsp2_qup6_spi_apps_clk_src.clkr,
	[BLSP2_UART1_APPS_CLK_SRC] = &blsp2_uart1_apps_clk_src.clkr,
	[BLSP2_UART2_APPS_CLK_SRC] = &blsp2_uart2_apps_clk_src.clkr,
	[BLSP2_UART3_APPS_CLK_SRC] = &blsp2_uart3_apps_clk_src.clkr,
	[GCC_AGGRE1_NOC_XO_CLK] = &gcc_aggre1_noc_xo_clk.clkr,
	[GCC_AGGRE1_UFS_AXI_CLK] = &gcc_aggre1_ufs_axi_clk.clkr,
	[GCC_AGGRE1_USB3_AXI_CLK] = &gcc_aggre1_usb3_axi_clk.clkr,
	[GCC_APSS_QDSS_TSCTR_DIV2_CLK] = &gcc_apss_qdss_tsctr_भाग2_clk.clkr,
	[GCC_APSS_QDSS_TSCTR_DIV8_CLK] = &gcc_apss_qdss_tsctr_भाग8_clk.clkr,
	[GCC_BIMC_HMSS_AXI_CLK] = &gcc_bimc_hmss_axi_clk.clkr,
	[GCC_BIMC_MSS_Q6_AXI_CLK] = &gcc_bimc_mss_q6_axi_clk.clkr,
	[GCC_BLSP1_AHB_CLK] = &gcc_blsp1_ahb_clk.clkr,
	[GCC_BLSP1_QUP1_I2C_APPS_CLK] = &gcc_blsp1_qup1_i2c_apps_clk.clkr,
	[GCC_BLSP1_QUP1_SPI_APPS_CLK] = &gcc_blsp1_qup1_spi_apps_clk.clkr,
	[GCC_BLSP1_QUP2_I2C_APPS_CLK] = &gcc_blsp1_qup2_i2c_apps_clk.clkr,
	[GCC_BLSP1_QUP2_SPI_APPS_CLK] = &gcc_blsp1_qup2_spi_apps_clk.clkr,
	[GCC_BLSP1_QUP3_I2C_APPS_CLK] = &gcc_blsp1_qup3_i2c_apps_clk.clkr,
	[GCC_BLSP1_QUP3_SPI_APPS_CLK] = &gcc_blsp1_qup3_spi_apps_clk.clkr,
	[GCC_BLSP1_QUP4_I2C_APPS_CLK] = &gcc_blsp1_qup4_i2c_apps_clk.clkr,
	[GCC_BLSP1_QUP4_SPI_APPS_CLK] = &gcc_blsp1_qup4_spi_apps_clk.clkr,
	[GCC_BLSP1_QUP5_I2C_APPS_CLK] = &gcc_blsp1_qup5_i2c_apps_clk.clkr,
	[GCC_BLSP1_QUP5_SPI_APPS_CLK] = &gcc_blsp1_qup5_spi_apps_clk.clkr,
	[GCC_BLSP1_QUP6_I2C_APPS_CLK] = &gcc_blsp1_qup6_i2c_apps_clk.clkr,
	[GCC_BLSP1_QUP6_SPI_APPS_CLK] = &gcc_blsp1_qup6_spi_apps_clk.clkr,
	[GCC_BLSP1_SLEEP_CLK] = &gcc_blsp1_sleep_clk.clkr,
	[GCC_BLSP1_UART1_APPS_CLK] = &gcc_blsp1_uart1_apps_clk.clkr,
	[GCC_BLSP1_UART2_APPS_CLK] = &gcc_blsp1_uart2_apps_clk.clkr,
	[GCC_BLSP1_UART3_APPS_CLK] = &gcc_blsp1_uart3_apps_clk.clkr,
	[GCC_BLSP2_AHB_CLK] = &gcc_blsp2_ahb_clk.clkr,
	[GCC_BLSP2_QUP1_I2C_APPS_CLK] = &gcc_blsp2_qup1_i2c_apps_clk.clkr,
	[GCC_BLSP2_QUP1_SPI_APPS_CLK] = &gcc_blsp2_qup1_spi_apps_clk.clkr,
	[GCC_BLSP2_QUP2_I2C_APPS_CLK] = &gcc_blsp2_qup2_i2c_apps_clk.clkr,
	[GCC_BLSP2_QUP2_SPI_APPS_CLK] = &gcc_blsp2_qup2_spi_apps_clk.clkr,
	[GCC_BLSP2_QUP3_I2C_APPS_CLK] = &gcc_blsp2_qup3_i2c_apps_clk.clkr,
	[GCC_BLSP2_QUP3_SPI_APPS_CLK] = &gcc_blsp2_qup3_spi_apps_clk.clkr,
	[GCC_BLSP2_QUP4_I2C_APPS_CLK] = &gcc_blsp2_qup4_i2c_apps_clk.clkr,
	[GCC_BLSP2_QUP4_SPI_APPS_CLK] = &gcc_blsp2_qup4_spi_apps_clk.clkr,
	[GCC_BLSP2_QUP5_I2C_APPS_CLK] = &gcc_blsp2_qup5_i2c_apps_clk.clkr,
	[GCC_BLSP2_QUP5_SPI_APPS_CLK] = &gcc_blsp2_qup5_spi_apps_clk.clkr,
	[GCC_BLSP2_QUP6_I2C_APPS_CLK] = &gcc_blsp2_qup6_i2c_apps_clk.clkr,
	[GCC_BLSP2_QUP6_SPI_APPS_CLK] = &gcc_blsp2_qup6_spi_apps_clk.clkr,
	[GCC_BLSP2_SLEEP_CLK] = &gcc_blsp2_sleep_clk.clkr,
	[GCC_BLSP2_UART1_APPS_CLK] = &gcc_blsp2_uart1_apps_clk.clkr,
	[GCC_BLSP2_UART2_APPS_CLK] = &gcc_blsp2_uart2_apps_clk.clkr,
	[GCC_BLSP2_UART3_APPS_CLK] = &gcc_blsp2_uart3_apps_clk.clkr,
	[GCC_CFG_NOC_USB3_AXI_CLK] = &gcc_cfg_noc_usb3_axi_clk.clkr,
	[GCC_GP1_CLK] = &gcc_gp1_clk.clkr,
	[GCC_GP2_CLK] = &gcc_gp2_clk.clkr,
	[GCC_GP3_CLK] = &gcc_gp3_clk.clkr,
	[GCC_BIMC_GFX_CLK] = &gcc_bimc_gfx_clk.clkr,
	[GCC_GPU_BIMC_GFX_CLK] = &gcc_gpu_bimc_gfx_clk.clkr,
	[GCC_GPU_BIMC_GFX_SRC_CLK] = &gcc_gpu_bimc_gfx_src_clk.clkr,
	[GCC_GPU_CFG_AHB_CLK] = &gcc_gpu_cfg_ahb_clk.clkr,
	[GCC_GPU_SNOC_DVM_GFX_CLK] = &gcc_gpu_snoc_dvm_gfx_clk.clkr,
	[GCC_HMSS_AHB_CLK] = &gcc_hmss_ahb_clk.clkr,
	[GCC_HMSS_AT_CLK] = &gcc_hmss_at_clk.clkr,
	[GCC_HMSS_RBCPR_CLK] = &gcc_hmss_rbcpr_clk.clkr,
	[GCC_HMSS_TRIG_CLK] = &gcc_hmss_trig_clk.clkr,
	[GCC_MMSS_NOC_CFG_AHB_CLK] = &gcc_mmss_noc_cfg_ahb_clk.clkr,
	[GCC_MMSS_QM_AHB_CLK] = &gcc_mmss_qm_ahb_clk.clkr,
	[GCC_MMSS_QM_CORE_CLK] = &gcc_mmss_qm_core_clk.clkr,
	[GCC_MMSS_SYS_NOC_AXI_CLK] = &gcc_mmss_sys_noc_axi_clk.clkr,
	[GCC_MSS_AT_CLK] = &gcc_mss_at_clk.clkr,
	[GCC_PCIE_0_AUX_CLK] = &gcc_pcie_0_aux_clk.clkr,
	[GCC_PCIE_0_CFG_AHB_CLK] = &gcc_pcie_0_cfg_ahb_clk.clkr,
	[GCC_PCIE_0_MSTR_AXI_CLK] = &gcc_pcie_0_mstr_axi_clk.clkr,
	[GCC_PCIE_0_PIPE_CLK] = &gcc_pcie_0_pipe_clk.clkr,
	[GCC_PCIE_0_SLV_AXI_CLK] = &gcc_pcie_0_slv_axi_clk.clkr,
	[GCC_PCIE_PHY_AUX_CLK] = &gcc_pcie_phy_aux_clk.clkr,
	[GCC_PDM2_CLK] = &gcc_pdm2_clk.clkr,
	[GCC_PDM_AHB_CLK] = &gcc_pdm_ahb_clk.clkr,
	[GCC_PDM_XO4_CLK] = &gcc_pdm_xo4_clk.clkr,
	[GCC_PRNG_AHB_CLK] = &gcc_prng_ahb_clk.clkr,
	[GCC_SDCC2_AHB_CLK] = &gcc_sdcc2_ahb_clk.clkr,
	[GCC_SDCC2_APPS_CLK] = &gcc_sdcc2_apps_clk.clkr,
	[GCC_SDCC4_AHB_CLK] = &gcc_sdcc4_ahb_clk.clkr,
	[GCC_SDCC4_APPS_CLK] = &gcc_sdcc4_apps_clk.clkr,
	[GCC_TSIF_AHB_CLK] = &gcc_tsअगर_ahb_clk.clkr,
	[GCC_TSIF_INACTIVITY_TIMERS_CLK] = &gcc_tsअगर_inactivity_समयrs_clk.clkr,
	[GCC_TSIF_REF_CLK] = &gcc_tsअगर_ref_clk.clkr,
	[GCC_UFS_AHB_CLK] = &gcc_ufs_ahb_clk.clkr,
	[GCC_UFS_AXI_CLK] = &gcc_ufs_axi_clk.clkr,
	[GCC_UFS_ICE_CORE_CLK] = &gcc_ufs_ice_core_clk.clkr,
	[GCC_UFS_PHY_AUX_CLK] = &gcc_ufs_phy_aux_clk.clkr,
	[GCC_UFS_RX_SYMBOL_0_CLK] = &gcc_ufs_rx_symbol_0_clk.clkr,
	[GCC_UFS_RX_SYMBOL_1_CLK] = &gcc_ufs_rx_symbol_1_clk.clkr,
	[GCC_UFS_TX_SYMBOL_0_CLK] = &gcc_ufs_tx_symbol_0_clk.clkr,
	[GCC_UFS_UNIPRO_CORE_CLK] = &gcc_ufs_unipro_core_clk.clkr,
	[GCC_USB30_MASTER_CLK] = &gcc_usb30_master_clk.clkr,
	[GCC_USB30_MOCK_UTMI_CLK] = &gcc_usb30_mock_uपंचांगi_clk.clkr,
	[GCC_USB30_SLEEP_CLK] = &gcc_usb30_sleep_clk.clkr,
	[GCC_USB3_PHY_AUX_CLK] = &gcc_usb3_phy_aux_clk.clkr,
	[GCC_USB3_PHY_PIPE_CLK] = &gcc_usb3_phy_pipe_clk.clkr,
	[GCC_USB_PHY_CFG_AHB2PHY_CLK] = &gcc_usb_phy_cfg_ahb2phy_clk.clkr,
	[GP1_CLK_SRC] = &gp1_clk_src.clkr,
	[GP2_CLK_SRC] = &gp2_clk_src.clkr,
	[GP3_CLK_SRC] = &gp3_clk_src.clkr,
	[GPLL0] = &gpll0.clkr,
	[GPLL0_OUT_EVEN] = &gpll0_out_even.clkr,
	[GPLL0_OUT_MAIN] = &gpll0_out_मुख्य.clkr,
	[GPLL0_OUT_ODD] = &gpll0_out_odd.clkr,
	[GPLL0_OUT_TEST] = &gpll0_out_test.clkr,
	[GPLL1] = &gpll1.clkr,
	[GPLL1_OUT_EVEN] = &gpll1_out_even.clkr,
	[GPLL1_OUT_MAIN] = &gpll1_out_मुख्य.clkr,
	[GPLL1_OUT_ODD] = &gpll1_out_odd.clkr,
	[GPLL1_OUT_TEST] = &gpll1_out_test.clkr,
	[GPLL2] = &gpll2.clkr,
	[GPLL2_OUT_EVEN] = &gpll2_out_even.clkr,
	[GPLL2_OUT_MAIN] = &gpll2_out_मुख्य.clkr,
	[GPLL2_OUT_ODD] = &gpll2_out_odd.clkr,
	[GPLL2_OUT_TEST] = &gpll2_out_test.clkr,
	[GPLL3] = &gpll3.clkr,
	[GPLL3_OUT_EVEN] = &gpll3_out_even.clkr,
	[GPLL3_OUT_MAIN] = &gpll3_out_मुख्य.clkr,
	[GPLL3_OUT_ODD] = &gpll3_out_odd.clkr,
	[GPLL3_OUT_TEST] = &gpll3_out_test.clkr,
	[GPLL4] = &gpll4.clkr,
	[GPLL4_OUT_EVEN] = &gpll4_out_even.clkr,
	[GPLL4_OUT_MAIN] = &gpll4_out_मुख्य.clkr,
	[GPLL4_OUT_ODD] = &gpll4_out_odd.clkr,
	[GPLL4_OUT_TEST] = &gpll4_out_test.clkr,
	[HMSS_AHB_CLK_SRC] = &hmss_ahb_clk_src.clkr,
	[HMSS_RBCPR_CLK_SRC] = &hmss_rbcpr_clk_src.clkr,
	[PCIE_AUX_CLK_SRC] = &pcie_aux_clk_src.clkr,
	[PDM2_CLK_SRC] = &pdm2_clk_src.clkr,
	[SDCC2_APPS_CLK_SRC] = &sdcc2_apps_clk_src.clkr,
	[SDCC4_APPS_CLK_SRC] = &sdcc4_apps_clk_src.clkr,
	[TSIF_REF_CLK_SRC] = &tsअगर_ref_clk_src.clkr,
	[UFS_AXI_CLK_SRC] = &ufs_axi_clk_src.clkr,
	[UFS_UNIPRO_CORE_CLK_SRC] = &ufs_unipro_core_clk_src.clkr,
	[USB30_MASTER_CLK_SRC] = &usb30_master_clk_src.clkr,
	[USB30_MOCK_UTMI_CLK_SRC] = &usb30_mock_uपंचांगi_clk_src.clkr,
	[USB3_PHY_AUX_CLK_SRC] = &usb3_phy_aux_clk_src.clkr,
	[GCC_HDMI_CLKREF_CLK] = &gcc_hdmi_clkref_clk.clkr,
	[GCC_UFS_CLKREF_CLK] = &gcc_ufs_clkref_clk.clkr,
	[GCC_USB3_CLKREF_CLK] = &gcc_usb3_clkref_clk.clkr,
	[GCC_PCIE_CLKREF_CLK] = &gcc_pcie_clkref_clk.clkr,
	[GCC_RX1_USB2_CLKREF_CLK] = &gcc_rx1_usb2_clkref_clk.clkr,
	[GCC_MSS_CFG_AHB_CLK] = &gcc_mss_cfg_ahb_clk.clkr,
	[GCC_BOOT_ROM_AHB_CLK] = &gcc_boot_rom_ahb_clk.clkr,
	[GCC_MSS_GPLL0_DIV_CLK_SRC] = &gcc_mss_gpll0_भाग_clk_src.clkr,
	[GCC_MSS_SNOC_AXI_CLK] = &gcc_mss_snoc_axi_clk.clkr,
	[GCC_MSS_MNOC_BIMC_AXI_CLK] = &gcc_mss_mnoc_bimc_axi_clk.clkr,
	[GCC_MMSS_GPLL0_CLK] = &gcc_mmss_gpll0_clk.clkr,
	[HMSS_GPLL0_CLK_SRC] = &hmss_gpll0_clk_src.clkr,
पूर्ण;

अटल काष्ठा gdsc *gcc_msm8998_gdscs[] = अणु
	[PCIE_0_GDSC] = &pcie_0_gdsc,
	[UFS_GDSC] = &ufs_gdsc,
	[USB_30_GDSC] = &usb_30_gdsc,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map gcc_msm8998_resets[] = अणु
	[GCC_BLSP1_QUP1_BCR] = अणु 0x19000 पूर्ण,
	[GCC_BLSP1_QUP2_BCR] = अणु 0x1b000 पूर्ण,
	[GCC_BLSP1_QUP3_BCR] = अणु 0x1d000 पूर्ण,
	[GCC_BLSP1_QUP4_BCR] = अणु 0x1f000 पूर्ण,
	[GCC_BLSP1_QUP5_BCR] = अणु 0x21000 पूर्ण,
	[GCC_BLSP1_QUP6_BCR] = अणु 0x23000 पूर्ण,
	[GCC_BLSP2_QUP1_BCR] = अणु 0x26000 पूर्ण,
	[GCC_BLSP2_QUP2_BCR] = अणु 0x28000 पूर्ण,
	[GCC_BLSP2_QUP3_BCR] = अणु 0x2a000 पूर्ण,
	[GCC_BLSP2_QUP4_BCR] = अणु 0x2c000 पूर्ण,
	[GCC_BLSP2_QUP5_BCR] = अणु 0x2e000 पूर्ण,
	[GCC_BLSP2_QUP6_BCR] = अणु 0x30000 पूर्ण,
	[GCC_PCIE_0_BCR] = अणु 0x6b000 पूर्ण,
	[GCC_PDM_BCR] = अणु 0x33000 पूर्ण,
	[GCC_SDCC2_BCR] = अणु 0x14000 पूर्ण,
	[GCC_SDCC4_BCR] = अणु 0x16000 पूर्ण,
	[GCC_TSIF_BCR] = अणु 0x36000 पूर्ण,
	[GCC_UFS_BCR] = अणु 0x75000 पूर्ण,
	[GCC_USB_30_BCR] = अणु 0xf000 पूर्ण,
	[GCC_SYSTEM_NOC_BCR] = अणु 0x4000 पूर्ण,
	[GCC_CONFIG_NOC_BCR] = अणु 0x5000 पूर्ण,
	[GCC_AHB2PHY_EAST_BCR] = अणु 0x7000 पूर्ण,
	[GCC_IMEM_BCR] = अणु 0x8000 पूर्ण,
	[GCC_PIMEM_BCR] = अणु 0xa000 पूर्ण,
	[GCC_MMSS_BCR] = अणु 0xb000 पूर्ण,
	[GCC_QDSS_BCR] = अणु 0xc000 पूर्ण,
	[GCC_WCSS_BCR] = अणु 0x11000 पूर्ण,
	[GCC_QUSB2PHY_PRIM_BCR] = अणु 0x12000 पूर्ण,
	[GCC_QUSB2PHY_SEC_BCR] = अणु 0x12004 पूर्ण,
	[GCC_BLSP1_BCR] = अणु 0x17000 पूर्ण,
	[GCC_BLSP1_UART1_BCR] = अणु 0x1a000 पूर्ण,
	[GCC_BLSP1_UART2_BCR] = अणु 0x1c000 पूर्ण,
	[GCC_BLSP1_UART3_BCR] = अणु 0x1e000 पूर्ण,
	[GCC_CM_PHY_REFGEN1_BCR] = अणु 0x22000 पूर्ण,
	[GCC_CM_PHY_REFGEN2_BCR] = अणु 0x24000 पूर्ण,
	[GCC_BLSP2_BCR] = अणु 0x25000 पूर्ण,
	[GCC_BLSP2_UART1_BCR] = अणु 0x27000 पूर्ण,
	[GCC_BLSP2_UART2_BCR] = अणु 0x29000 पूर्ण,
	[GCC_BLSP2_UART3_BCR] = अणु 0x2b000 पूर्ण,
	[GCC_SRAM_SENSOR_BCR] = अणु 0x2d000 पूर्ण,
	[GCC_PRNG_BCR] = अणु 0x34000 पूर्ण,
	[GCC_TSIF_0_RESET] = अणु 0x36024 पूर्ण,
	[GCC_TSIF_1_RESET] = अणु 0x36028 पूर्ण,
	[GCC_TCSR_BCR] = अणु 0x37000 पूर्ण,
	[GCC_BOOT_ROM_BCR] = अणु 0x38000 पूर्ण,
	[GCC_MSG_RAM_BCR] = अणु 0x39000 पूर्ण,
	[GCC_TLMM_BCR] = अणु 0x3a000 पूर्ण,
	[GCC_MPM_BCR] = अणु 0x3b000 पूर्ण,
	[GCC_SEC_CTRL_BCR] = अणु 0x3d000 पूर्ण,
	[GCC_SPMI_BCR] = अणु 0x3f000 पूर्ण,
	[GCC_SPDM_BCR] = अणु 0x40000 पूर्ण,
	[GCC_CE1_BCR] = अणु 0x41000 पूर्ण,
	[GCC_BIMC_BCR] = अणु 0x44000 पूर्ण,
	[GCC_SNOC_BUS_TIMEOUT0_BCR] = अणु 0x49000 पूर्ण,
	[GCC_SNOC_BUS_TIMEOUT1_BCR] = अणु 0x49008 पूर्ण,
	[GCC_SNOC_BUS_TIMEOUT3_BCR] = अणु 0x49010 पूर्ण,
	[GCC_SNOC_BUS_TIMEOUT_EXTREF_BCR] = अणु 0x49018 पूर्ण,
	[GCC_PNOC_BUS_TIMEOUT0_BCR] = अणु 0x4a000 पूर्ण,
	[GCC_CNOC_PERIPH_BUS_TIMEOUT1_BCR] = अणु 0x4a004 पूर्ण,
	[GCC_CNOC_PERIPH_BUS_TIMEOUT2_BCR] = अणु 0x4a00c पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT0_BCR] = अणु 0x4b000 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT1_BCR] = अणु 0x4b008 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT2_BCR] = अणु 0x4b010 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT3_BCR] = अणु 0x4b018 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT4_BCR] = अणु 0x4b020 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT5_BCR] = अणु 0x4b028 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT6_BCR] = अणु 0x4b030 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT7_BCR] = अणु 0x4b038 पूर्ण,
	[GCC_APB2JTAG_BCR] = अणु 0x4c000 पूर्ण,
	[GCC_RBCPR_CX_BCR] = अणु 0x4e000 पूर्ण,
	[GCC_RBCPR_MX_BCR] = अणु 0x4f000 पूर्ण,
	[GCC_USB3_PHY_BCR] = अणु 0x50020 पूर्ण,
	[GCC_USB3PHY_PHY_BCR] = अणु 0x50024 पूर्ण,
	[GCC_USB3_DP_PHY_BCR] = अणु 0x50028 पूर्ण,
	[GCC_SSC_BCR] = अणु 0x63000 पूर्ण,
	[GCC_SSC_RESET] = अणु 0x63020 पूर्ण,
	[GCC_USB_PHY_CFG_AHB2PHY_BCR] = अणु 0x6a000 पूर्ण,
	[GCC_PCIE_0_LINK_DOWN_BCR] = अणु 0x6c014 पूर्ण,
	[GCC_PCIE_0_PHY_BCR] = अणु 0x6c01c पूर्ण,
	[GCC_PCIE_0_NOCSR_COM_PHY_BCR] = अणु 0x6c020 पूर्ण,
	[GCC_PCIE_PHY_BCR] = अणु 0x6f000 पूर्ण,
	[GCC_PCIE_PHY_NOCSR_COM_PHY_BCR] = अणु 0x6f00c पूर्ण,
	[GCC_PCIE_PHY_CFG_AHB_BCR] = अणु 0x6f010 पूर्ण,
	[GCC_PCIE_PHY_COM_BCR] = अणु 0x6f014 पूर्ण,
	[GCC_GPU_BCR] = अणु 0x71000 पूर्ण,
	[GCC_SPSS_BCR] = अणु 0x72000 पूर्ण,
	[GCC_OBT_ODT_BCR] = अणु 0x73000 पूर्ण,
	[GCC_MSS_RESTART] = अणु 0x79000 पूर्ण,
	[GCC_VS_BCR] = अणु 0x7a000 पूर्ण,
	[GCC_MSS_VS_RESET] = अणु 0x7a100 पूर्ण,
	[GCC_GPU_VS_RESET] = अणु 0x7a104 पूर्ण,
	[GCC_APC0_VS_RESET] = अणु 0x7a108 पूर्ण,
	[GCC_APC1_VS_RESET] = अणु 0x7a10c पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT8_BCR] = अणु 0x80000 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT9_BCR] = अणु 0x80008 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT10_BCR] = अणु 0x80010 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT11_BCR] = अणु 0x80018 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT12_BCR] = अणु 0x80020 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT13_BCR] = अणु 0x80028 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT14_BCR] = अणु 0x80030 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT_EXTREF_BCR] = अणु 0x80038 पूर्ण,
	[GCC_AGGRE1_NOC_BCR] = अणु 0x82000 पूर्ण,
	[GCC_AGGRE2_NOC_BCR] = अणु 0x83000 पूर्ण,
	[GCC_DCC_BCR] = अणु 0x84000 पूर्ण,
	[GCC_QREFS_VBG_CAL_BCR] = अणु 0x88028 पूर्ण,
	[GCC_IPA_BCR] = अणु 0x89000 पूर्ण,
	[GCC_GLM_BCR] = अणु 0x8b000 पूर्ण,
	[GCC_SKL_BCR] = अणु 0x8c000 पूर्ण,
	[GCC_MSMPU_BCR] = अणु 0x8d000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config gcc_msm8998_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x8f000,
	.fast_io	= true,
पूर्ण;

अटल काष्ठा clk_hw *gcc_msm8998_hws[] = अणु
	&xo.hw,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc gcc_msm8998_desc = अणु
	.config = &gcc_msm8998_regmap_config,
	.clks = gcc_msm8998_घड़ीs,
	.num_clks = ARRAY_SIZE(gcc_msm8998_घड़ीs),
	.resets = gcc_msm8998_resets,
	.num_resets = ARRAY_SIZE(gcc_msm8998_resets),
	.gdscs = gcc_msm8998_gdscs,
	.num_gdscs = ARRAY_SIZE(gcc_msm8998_gdscs),
	.clk_hws = gcc_msm8998_hws,
	.num_clk_hws = ARRAY_SIZE(gcc_msm8998_hws),
पूर्ण;

अटल पूर्णांक gcc_msm8998_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	regmap = qcom_cc_map(pdev, &gcc_msm8998_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/*
	 * Set the HMSS_AHB_CLK_SLEEP_ENA bit to allow the hmss_ahb_clk to be
	 * turned off by hardware during certain apps low घातer modes.
	 */
	ret = regmap_update_bits(regmap, 0x52008, BIT(21), BIT(21));
	अगर (ret)
		वापस ret;

	वापस qcom_cc_really_probe(pdev, &gcc_msm8998_desc, regmap);
पूर्ण

अटल स्थिर काष्ठा of_device_id gcc_msm8998_match_table[] = अणु
	अणु .compatible = "qcom,gcc-msm8998" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gcc_msm8998_match_table);

अटल काष्ठा platक्रमm_driver gcc_msm8998_driver = अणु
	.probe		= gcc_msm8998_probe,
	.driver		= अणु
		.name	= "gcc-msm8998",
		.of_match_table = gcc_msm8998_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init gcc_msm8998_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&gcc_msm8998_driver);
पूर्ण
core_initcall(gcc_msm8998_init);

अटल व्योम __निकास gcc_msm8998_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&gcc_msm8998_driver);
पूर्ण
module_निकास(gcc_msm8998_निकास);

MODULE_DESCRIPTION("QCOM GCC msm8998 Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:gcc-msm8998");
