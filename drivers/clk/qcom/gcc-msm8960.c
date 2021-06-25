<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
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

#समावेश <dt-bindings/घड़ी/qcom,gcc-msm8960.h>
#समावेश <dt-bindings/reset/qcom,gcc-msm8960.h>

#समावेश "common.h"
#समावेश "clk-regmap.h"
#समावेश "clk-pll.h"
#समावेश "clk-rcg.h"
#समावेश "clk-branch.h"
#समावेश "clk-hfpll.h"
#समावेश "reset.h"

अटल काष्ठा clk_pll pll3 = अणु
	.l_reg = 0x3164,
	.m_reg = 0x3168,
	.n_reg = 0x316c,
	.config_reg = 0x3174,
	.mode_reg = 0x3160,
	.status_reg = 0x3178,
	.status_bit = 16,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pll3",
		.parent_names = (स्थिर अक्षर *[])अणु "pxo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap pll4_vote = अणु
	.enable_reg = 0x34c0,
	.enable_mask = BIT(4),
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pll4_vote",
		.parent_names = (स्थिर अक्षर *[])अणु "pll4" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_vote_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_pll pll8 = अणु
	.l_reg = 0x3144,
	.m_reg = 0x3148,
	.n_reg = 0x314c,
	.config_reg = 0x3154,
	.mode_reg = 0x3140,
	.status_reg = 0x3158,
	.status_bit = 16,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pll8",
		.parent_names = (स्थिर अक्षर *[])अणु "pxo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap pll8_vote = अणु
	.enable_reg = 0x34c0,
	.enable_mask = BIT(8),
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pll8_vote",
		.parent_names = (स्थिर अक्षर *[])अणु "pll8" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_vote_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा hfpll_data hfpll0_data = अणु
	.mode_reg = 0x3200,
	.l_reg = 0x3208,
	.m_reg = 0x320c,
	.n_reg = 0x3210,
	.config_reg = 0x3204,
	.status_reg = 0x321c,
	.config_val = 0x7845c665,
	.droop_reg = 0x3214,
	.droop_val = 0x0108c000,
	.min_rate = 600000000UL,
	.max_rate = 1800000000UL,
पूर्ण;

अटल काष्ठा clk_hfpll hfpll0 = अणु
	.d = &hfpll0_data,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.parent_names = (स्थिर अक्षर *[])अणु "pxo" पूर्ण,
		.num_parents = 1,
		.name = "hfpll0",
		.ops = &clk_ops_hfpll,
		.flags = CLK_IGNORE_UNUSED,
	पूर्ण,
	.lock = __SPIN_LOCK_UNLOCKED(hfpll0.lock),
पूर्ण;

अटल काष्ठा hfpll_data hfpll1_8064_data = अणु
	.mode_reg = 0x3240,
	.l_reg = 0x3248,
	.m_reg = 0x324c,
	.n_reg = 0x3250,
	.config_reg = 0x3244,
	.status_reg = 0x325c,
	.config_val = 0x7845c665,
	.droop_reg = 0x3254,
	.droop_val = 0x0108c000,
	.min_rate = 600000000UL,
	.max_rate = 1800000000UL,
पूर्ण;

अटल काष्ठा hfpll_data hfpll1_data = अणु
	.mode_reg = 0x3300,
	.l_reg = 0x3308,
	.m_reg = 0x330c,
	.n_reg = 0x3310,
	.config_reg = 0x3304,
	.status_reg = 0x331c,
	.config_val = 0x7845c665,
	.droop_reg = 0x3314,
	.droop_val = 0x0108c000,
	.min_rate = 600000000UL,
	.max_rate = 1800000000UL,
पूर्ण;

अटल काष्ठा clk_hfpll hfpll1 = अणु
	.d = &hfpll1_data,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.parent_names = (स्थिर अक्षर *[])अणु "pxo" पूर्ण,
		.num_parents = 1,
		.name = "hfpll1",
		.ops = &clk_ops_hfpll,
		.flags = CLK_IGNORE_UNUSED,
	पूर्ण,
	.lock = __SPIN_LOCK_UNLOCKED(hfpll1.lock),
पूर्ण;

अटल काष्ठा hfpll_data hfpll2_data = अणु
	.mode_reg = 0x3280,
	.l_reg = 0x3288,
	.m_reg = 0x328c,
	.n_reg = 0x3290,
	.config_reg = 0x3284,
	.status_reg = 0x329c,
	.config_val = 0x7845c665,
	.droop_reg = 0x3294,
	.droop_val = 0x0108c000,
	.min_rate = 600000000UL,
	.max_rate = 1800000000UL,
पूर्ण;

अटल काष्ठा clk_hfpll hfpll2 = अणु
	.d = &hfpll2_data,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.parent_names = (स्थिर अक्षर *[])अणु "pxo" पूर्ण,
		.num_parents = 1,
		.name = "hfpll2",
		.ops = &clk_ops_hfpll,
		.flags = CLK_IGNORE_UNUSED,
	पूर्ण,
	.lock = __SPIN_LOCK_UNLOCKED(hfpll2.lock),
पूर्ण;

अटल काष्ठा hfpll_data hfpll3_data = अणु
	.mode_reg = 0x32c0,
	.l_reg = 0x32c8,
	.m_reg = 0x32cc,
	.n_reg = 0x32d0,
	.config_reg = 0x32c4,
	.status_reg = 0x32dc,
	.config_val = 0x7845c665,
	.droop_reg = 0x32d4,
	.droop_val = 0x0108c000,
	.min_rate = 600000000UL,
	.max_rate = 1800000000UL,
पूर्ण;

अटल काष्ठा clk_hfpll hfpll3 = अणु
	.d = &hfpll3_data,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.parent_names = (स्थिर अक्षर *[])अणु "pxo" पूर्ण,
		.num_parents = 1,
		.name = "hfpll3",
		.ops = &clk_ops_hfpll,
		.flags = CLK_IGNORE_UNUSED,
	पूर्ण,
	.lock = __SPIN_LOCK_UNLOCKED(hfpll3.lock),
पूर्ण;

अटल काष्ठा hfpll_data hfpll_l2_8064_data = अणु
	.mode_reg = 0x3300,
	.l_reg = 0x3308,
	.m_reg = 0x330c,
	.n_reg = 0x3310,
	.config_reg = 0x3304,
	.status_reg = 0x331c,
	.config_val = 0x7845c665,
	.droop_reg = 0x3314,
	.droop_val = 0x0108c000,
	.min_rate = 600000000UL,
	.max_rate = 1800000000UL,
पूर्ण;

अटल काष्ठा hfpll_data hfpll_l2_data = अणु
	.mode_reg = 0x3400,
	.l_reg = 0x3408,
	.m_reg = 0x340c,
	.n_reg = 0x3410,
	.config_reg = 0x3404,
	.status_reg = 0x341c,
	.config_val = 0x7845c665,
	.droop_reg = 0x3414,
	.droop_val = 0x0108c000,
	.min_rate = 600000000UL,
	.max_rate = 1800000000UL,
पूर्ण;

अटल काष्ठा clk_hfpll hfpll_l2 = अणु
	.d = &hfpll_l2_data,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.parent_names = (स्थिर अक्षर *[])अणु "pxo" पूर्ण,
		.num_parents = 1,
		.name = "hfpll_l2",
		.ops = &clk_ops_hfpll,
		.flags = CLK_IGNORE_UNUSED,
	पूर्ण,
	.lock = __SPIN_LOCK_UNLOCKED(hfpll_l2.lock),
पूर्ण;

अटल काष्ठा clk_pll pll14 = अणु
	.l_reg = 0x31c4,
	.m_reg = 0x31c8,
	.n_reg = 0x31cc,
	.config_reg = 0x31d4,
	.mode_reg = 0x31c0,
	.status_reg = 0x31d8,
	.status_bit = 16,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pll14",
		.parent_names = (स्थिर अक्षर *[])अणु "pxo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap pll14_vote = अणु
	.enable_reg = 0x34c0,
	.enable_mask = BIT(14),
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pll14_vote",
		.parent_names = (स्थिर अक्षर *[])अणु "pll14" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_vote_ops,
	पूर्ण,
पूर्ण;

क्रमागत अणु
	P_PXO,
	P_PLL8,
	P_PLL3,
	P_CXO,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_pxo_pll8_map[] = अणु
	अणु P_PXO, 0 पूर्ण,
	अणु P_PLL8, 3 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_pxo_pll8[] = अणु
	"pxo",
	"pll8_vote",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_pxo_pll8_cxo_map[] = अणु
	अणु P_PXO, 0 पूर्ण,
	अणु P_PLL8, 3 पूर्ण,
	अणु P_CXO, 5 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_pxo_pll8_cxo[] = अणु
	"pxo",
	"pll8_vote",
	"cxo",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_pxo_pll8_pll3_map[] = अणु
	अणु P_PXO, 0 पूर्ण,
	अणु P_PLL8, 3 पूर्ण,
	अणु P_PLL3, 6 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_pxo_pll8_pll3[] = अणु
	"pxo",
	"pll8_vote",
	"pll3",
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_gsbi_uart[] = अणु
	अणु  1843200, P_PLL8, 2,  6, 625 पूर्ण,
	अणु  3686400, P_PLL8, 2, 12, 625 पूर्ण,
	अणु  7372800, P_PLL8, 2, 24, 625 पूर्ण,
	अणु 14745600, P_PLL8, 2, 48, 625 पूर्ण,
	अणु 16000000, P_PLL8, 4,  1,   6 पूर्ण,
	अणु 24000000, P_PLL8, 4,  1,   4 पूर्ण,
	अणु 32000000, P_PLL8, 4,  1,   3 पूर्ण,
	अणु 40000000, P_PLL8, 1,  5,  48 पूर्ण,
	अणु 46400000, P_PLL8, 1, 29, 240 पूर्ण,
	अणु 48000000, P_PLL8, 4,  1,   2 पूर्ण,
	अणु 51200000, P_PLL8, 1,  2,  15 पूर्ण,
	अणु 56000000, P_PLL8, 1,  7,  48 पूर्ण,
	अणु 58982400, P_PLL8, 1, 96, 625 पूर्ण,
	अणु 64000000, P_PLL8, 2,  1,   3 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg gsbi1_uart_src = अणु
	.ns_reg = 0x29d4,
	.md_reg = 0x29d0,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 16,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_uart,
	.clkr = अणु
		.enable_reg = 0x29d4,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi1_uart_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi1_uart_clk = अणु
	.halt_reg = 0x2fcc,
	.halt_bit = 10,
	.clkr = अणु
		.enable_reg = 0x29d4,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi1_uart_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gsbi1_uart_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi2_uart_src = अणु
	.ns_reg = 0x29f4,
	.md_reg = 0x29f0,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 16,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_uart,
	.clkr = अणु
		.enable_reg = 0x29f4,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi2_uart_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi2_uart_clk = अणु
	.halt_reg = 0x2fcc,
	.halt_bit = 6,
	.clkr = अणु
		.enable_reg = 0x29f4,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi2_uart_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gsbi2_uart_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi3_uart_src = अणु
	.ns_reg = 0x2a14,
	.md_reg = 0x2a10,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 16,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_uart,
	.clkr = अणु
		.enable_reg = 0x2a14,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi3_uart_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi3_uart_clk = अणु
	.halt_reg = 0x2fcc,
	.halt_bit = 2,
	.clkr = अणु
		.enable_reg = 0x2a14,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi3_uart_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gsbi3_uart_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi4_uart_src = अणु
	.ns_reg = 0x2a34,
	.md_reg = 0x2a30,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 16,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_uart,
	.clkr = अणु
		.enable_reg = 0x2a34,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi4_uart_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi4_uart_clk = अणु
	.halt_reg = 0x2fd0,
	.halt_bit = 26,
	.clkr = अणु
		.enable_reg = 0x2a34,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi4_uart_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gsbi4_uart_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi5_uart_src = अणु
	.ns_reg = 0x2a54,
	.md_reg = 0x2a50,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 16,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_uart,
	.clkr = अणु
		.enable_reg = 0x2a54,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi5_uart_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi5_uart_clk = अणु
	.halt_reg = 0x2fd0,
	.halt_bit = 22,
	.clkr = अणु
		.enable_reg = 0x2a54,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi5_uart_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gsbi5_uart_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi6_uart_src = अणु
	.ns_reg = 0x2a74,
	.md_reg = 0x2a70,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 16,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_uart,
	.clkr = अणु
		.enable_reg = 0x2a74,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi6_uart_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi6_uart_clk = अणु
	.halt_reg = 0x2fd0,
	.halt_bit = 18,
	.clkr = अणु
		.enable_reg = 0x2a74,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi6_uart_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gsbi6_uart_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi7_uart_src = अणु
	.ns_reg = 0x2a94,
	.md_reg = 0x2a90,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 16,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_uart,
	.clkr = अणु
		.enable_reg = 0x2a94,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi7_uart_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi7_uart_clk = अणु
	.halt_reg = 0x2fd0,
	.halt_bit = 14,
	.clkr = अणु
		.enable_reg = 0x2a94,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi7_uart_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gsbi7_uart_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi8_uart_src = अणु
	.ns_reg = 0x2ab4,
	.md_reg = 0x2ab0,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 16,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_uart,
	.clkr = अणु
		.enable_reg = 0x2ab4,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi8_uart_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi8_uart_clk = अणु
	.halt_reg = 0x2fd0,
	.halt_bit = 10,
	.clkr = अणु
		.enable_reg = 0x2ab4,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi8_uart_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gsbi8_uart_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi9_uart_src = अणु
	.ns_reg = 0x2ad4,
	.md_reg = 0x2ad0,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 16,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_uart,
	.clkr = अणु
		.enable_reg = 0x2ad4,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi9_uart_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi9_uart_clk = अणु
	.halt_reg = 0x2fd0,
	.halt_bit = 6,
	.clkr = अणु
		.enable_reg = 0x2ad4,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi9_uart_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gsbi9_uart_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi10_uart_src = अणु
	.ns_reg = 0x2af4,
	.md_reg = 0x2af0,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 16,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_uart,
	.clkr = अणु
		.enable_reg = 0x2af4,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi10_uart_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi10_uart_clk = अणु
	.halt_reg = 0x2fd0,
	.halt_bit = 2,
	.clkr = अणु
		.enable_reg = 0x2af4,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi10_uart_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gsbi10_uart_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi11_uart_src = अणु
	.ns_reg = 0x2b14,
	.md_reg = 0x2b10,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 16,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_uart,
	.clkr = अणु
		.enable_reg = 0x2b14,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi11_uart_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi11_uart_clk = अणु
	.halt_reg = 0x2fd4,
	.halt_bit = 17,
	.clkr = अणु
		.enable_reg = 0x2b14,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi11_uart_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gsbi11_uart_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi12_uart_src = अणु
	.ns_reg = 0x2b34,
	.md_reg = 0x2b30,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 16,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_uart,
	.clkr = अणु
		.enable_reg = 0x2b34,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi12_uart_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi12_uart_clk = अणु
	.halt_reg = 0x2fd4,
	.halt_bit = 13,
	.clkr = अणु
		.enable_reg = 0x2b34,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi12_uart_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gsbi12_uart_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_gsbi_qup[] = अणु
	अणु  1100000, P_PXO,  1, 2, 49 पूर्ण,
	अणु  5400000, P_PXO,  1, 1,  5 पूर्ण,
	अणु 10800000, P_PXO,  1, 2,  5 पूर्ण,
	अणु 15060000, P_PLL8, 1, 2, 51 पूर्ण,
	अणु 24000000, P_PLL8, 4, 1,  4 पूर्ण,
	अणु 25600000, P_PLL8, 1, 1, 15 पूर्ण,
	अणु 27000000, P_PXO,  1, 0,  0 पूर्ण,
	अणु 48000000, P_PLL8, 4, 1,  2 पूर्ण,
	अणु 51200000, P_PLL8, 1, 2, 15 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg gsbi1_qup_src = अणु
	.ns_reg = 0x29cc,
	.md_reg = 0x29c8,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_qup,
	.clkr = अणु
		.enable_reg = 0x29cc,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi1_qup_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi1_qup_clk = अणु
	.halt_reg = 0x2fcc,
	.halt_bit = 9,
	.clkr = अणु
		.enable_reg = 0x29cc,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi1_qup_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gsbi1_qup_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi2_qup_src = अणु
	.ns_reg = 0x29ec,
	.md_reg = 0x29e8,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_qup,
	.clkr = अणु
		.enable_reg = 0x29ec,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi2_qup_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi2_qup_clk = अणु
	.halt_reg = 0x2fcc,
	.halt_bit = 4,
	.clkr = अणु
		.enable_reg = 0x29ec,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi2_qup_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gsbi2_qup_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi3_qup_src = अणु
	.ns_reg = 0x2a0c,
	.md_reg = 0x2a08,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_qup,
	.clkr = अणु
		.enable_reg = 0x2a0c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi3_qup_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi3_qup_clk = अणु
	.halt_reg = 0x2fcc,
	.halt_bit = 0,
	.clkr = अणु
		.enable_reg = 0x2a0c,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi3_qup_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gsbi3_qup_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi4_qup_src = अणु
	.ns_reg = 0x2a2c,
	.md_reg = 0x2a28,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_qup,
	.clkr = अणु
		.enable_reg = 0x2a2c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi4_qup_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi4_qup_clk = अणु
	.halt_reg = 0x2fd0,
	.halt_bit = 24,
	.clkr = अणु
		.enable_reg = 0x2a2c,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi4_qup_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gsbi4_qup_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi5_qup_src = अणु
	.ns_reg = 0x2a4c,
	.md_reg = 0x2a48,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_qup,
	.clkr = अणु
		.enable_reg = 0x2a4c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi5_qup_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi5_qup_clk = अणु
	.halt_reg = 0x2fd0,
	.halt_bit = 20,
	.clkr = अणु
		.enable_reg = 0x2a4c,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi5_qup_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gsbi5_qup_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi6_qup_src = अणु
	.ns_reg = 0x2a6c,
	.md_reg = 0x2a68,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_qup,
	.clkr = अणु
		.enable_reg = 0x2a6c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi6_qup_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi6_qup_clk = अणु
	.halt_reg = 0x2fd0,
	.halt_bit = 16,
	.clkr = अणु
		.enable_reg = 0x2a6c,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi6_qup_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gsbi6_qup_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi7_qup_src = अणु
	.ns_reg = 0x2a8c,
	.md_reg = 0x2a88,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_qup,
	.clkr = अणु
		.enable_reg = 0x2a8c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi7_qup_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi7_qup_clk = अणु
	.halt_reg = 0x2fd0,
	.halt_bit = 12,
	.clkr = अणु
		.enable_reg = 0x2a8c,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi7_qup_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gsbi7_qup_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi8_qup_src = अणु
	.ns_reg = 0x2aac,
	.md_reg = 0x2aa8,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_qup,
	.clkr = अणु
		.enable_reg = 0x2aac,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi8_qup_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi8_qup_clk = अणु
	.halt_reg = 0x2fd0,
	.halt_bit = 8,
	.clkr = अणु
		.enable_reg = 0x2aac,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi8_qup_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gsbi8_qup_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi9_qup_src = अणु
	.ns_reg = 0x2acc,
	.md_reg = 0x2ac8,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_qup,
	.clkr = अणु
		.enable_reg = 0x2acc,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi9_qup_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi9_qup_clk = अणु
	.halt_reg = 0x2fd0,
	.halt_bit = 4,
	.clkr = अणु
		.enable_reg = 0x2acc,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi9_qup_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gsbi9_qup_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi10_qup_src = अणु
	.ns_reg = 0x2aec,
	.md_reg = 0x2ae8,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_qup,
	.clkr = अणु
		.enable_reg = 0x2aec,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi10_qup_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi10_qup_clk = अणु
	.halt_reg = 0x2fd0,
	.halt_bit = 0,
	.clkr = अणु
		.enable_reg = 0x2aec,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi10_qup_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gsbi10_qup_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi11_qup_src = अणु
	.ns_reg = 0x2b0c,
	.md_reg = 0x2b08,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_qup,
	.clkr = अणु
		.enable_reg = 0x2b0c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi11_qup_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi11_qup_clk = अणु
	.halt_reg = 0x2fd4,
	.halt_bit = 15,
	.clkr = अणु
		.enable_reg = 0x2b0c,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi11_qup_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gsbi11_qup_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gsbi12_qup_src = अणु
	.ns_reg = 0x2b2c,
	.md_reg = 0x2b28,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_qup,
	.clkr = अणु
		.enable_reg = 0x2b2c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi12_qup_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi12_qup_clk = अणु
	.halt_reg = 0x2fd4,
	.halt_bit = 11,
	.clkr = अणु
		.enable_reg = 0x2b2c,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi12_qup_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gsbi12_qup_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl clk_tbl_gp[] = अणु
	अणु 9600000, P_CXO,  2, 0, 0 पूर्ण,
	अणु 13500000, P_PXO,  2, 0, 0 पूर्ण,
	अणु 19200000, P_CXO,  1, 0, 0 पूर्ण,
	अणु 27000000, P_PXO,  1, 0, 0 पूर्ण,
	अणु 64000000, P_PLL8, 2, 1, 3 पूर्ण,
	अणु 76800000, P_PLL8, 1, 1, 5 पूर्ण,
	अणु 96000000, P_PLL8, 4, 0, 0 पूर्ण,
	अणु 128000000, P_PLL8, 3, 0, 0 पूर्ण,
	अणु 192000000, P_PLL8, 2, 0, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg gp0_src = अणु
	.ns_reg = 0x2d24,
	.md_reg = 0x2d00,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_cxo_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gp,
	.clkr = अणु
		.enable_reg = 0x2d24,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gp0_src",
			.parent_names = gcc_pxo_pll8_cxo,
			.num_parents = 3,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_PARENT_GATE,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_branch gp0_clk = अणु
	.halt_reg = 0x2fd8,
	.halt_bit = 7,
	.clkr = अणु
		.enable_reg = 0x2d24,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gp0_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gp0_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gp1_src = अणु
	.ns_reg = 0x2d44,
	.md_reg = 0x2d40,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_cxo_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gp,
	.clkr = अणु
		.enable_reg = 0x2d44,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gp1_src",
			.parent_names = gcc_pxo_pll8_cxo,
			.num_parents = 3,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_RATE_GATE,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_branch gp1_clk = अणु
	.halt_reg = 0x2fd8,
	.halt_bit = 6,
	.clkr = अणु
		.enable_reg = 0x2d44,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gp1_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gp1_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg gp2_src = अणु
	.ns_reg = 0x2d64,
	.md_reg = 0x2d60,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_cxo_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gp,
	.clkr = अणु
		.enable_reg = 0x2d64,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gp2_src",
			.parent_names = gcc_pxo_pll8_cxo,
			.num_parents = 3,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_RATE_GATE,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_branch gp2_clk = अणु
	.halt_reg = 0x2fd8,
	.halt_bit = 5,
	.clkr = अणु
		.enable_reg = 0x2d64,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gp2_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gp2_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch pmem_clk = अणु
	.hwcg_reg = 0x25a0,
	.hwcg_bit = 6,
	.halt_reg = 0x2fc8,
	.halt_bit = 20,
	.clkr = अणु
		.enable_reg = 0x25a0,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "pmem_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg prng_src = अणु
	.ns_reg = 0x2e80,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 4,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "prng_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch prng_clk = अणु
	.halt_reg = 0x2fd8,
	.halt_check = BRANCH_HALT_VOTED,
	.halt_bit = 10,
	.clkr = अणु
		.enable_reg = 0x3080,
		.enable_mask = BIT(10),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "prng_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "prng_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl clk_tbl_sdc[] = अणु
	अणु    144000, P_PXO,   3, 2, 125 पूर्ण,
	अणु    400000, P_PLL8,  4, 1, 240 पूर्ण,
	अणु  16000000, P_PLL8,  4, 1,   6 पूर्ण,
	अणु  17070000, P_PLL8,  1, 2,  45 पूर्ण,
	अणु  20210000, P_PLL8,  1, 1,  19 पूर्ण,
	अणु  24000000, P_PLL8,  4, 1,   4 पूर्ण,
	अणु  48000000, P_PLL8,  4, 1,   2 पूर्ण,
	अणु  64000000, P_PLL8,  3, 1,   2 पूर्ण,
	अणु  96000000, P_PLL8,  4, 0,   0 पूर्ण,
	अणु 192000000, P_PLL8,  2, 0,   0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg sdc1_src = अणु
	.ns_reg = 0x282c,
	.md_reg = 0x2828,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_sdc,
	.clkr = अणु
		.enable_reg = 0x282c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sdc1_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_branch sdc1_clk = अणु
	.halt_reg = 0x2fc8,
	.halt_bit = 6,
	.clkr = अणु
		.enable_reg = 0x282c,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sdc1_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "sdc1_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg sdc2_src = अणु
	.ns_reg = 0x284c,
	.md_reg = 0x2848,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_sdc,
	.clkr = अणु
		.enable_reg = 0x284c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sdc2_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_branch sdc2_clk = अणु
	.halt_reg = 0x2fc8,
	.halt_bit = 5,
	.clkr = अणु
		.enable_reg = 0x284c,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sdc2_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "sdc2_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg sdc3_src = अणु
	.ns_reg = 0x286c,
	.md_reg = 0x2868,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_sdc,
	.clkr = अणु
		.enable_reg = 0x286c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sdc3_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_branch sdc3_clk = अणु
	.halt_reg = 0x2fc8,
	.halt_bit = 4,
	.clkr = अणु
		.enable_reg = 0x286c,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sdc3_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "sdc3_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg sdc4_src = अणु
	.ns_reg = 0x288c,
	.md_reg = 0x2888,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_sdc,
	.clkr = अणु
		.enable_reg = 0x288c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sdc4_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_branch sdc4_clk = अणु
	.halt_reg = 0x2fc8,
	.halt_bit = 3,
	.clkr = अणु
		.enable_reg = 0x288c,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sdc4_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "sdc4_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg sdc5_src = अणु
	.ns_reg = 0x28ac,
	.md_reg = 0x28a8,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_sdc,
	.clkr = अणु
		.enable_reg = 0x28ac,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sdc5_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_branch sdc5_clk = अणु
	.halt_reg = 0x2fc8,
	.halt_bit = 2,
	.clkr = अणु
		.enable_reg = 0x28ac,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sdc5_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "sdc5_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl clk_tbl_tsअगर_ref[] = अणु
	अणु 105000, P_PXO,  1, 1, 256 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg tsअगर_ref_src = अणु
	.ns_reg = 0x2710,
	.md_reg = 0x270c,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 16,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_tsअगर_ref,
	.clkr = अणु
		.enable_reg = 0x2710,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "tsif_ref_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_RATE_GATE,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_branch tsअगर_ref_clk = अणु
	.halt_reg = 0x2fd4,
	.halt_bit = 5,
	.clkr = अणु
		.enable_reg = 0x2710,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "tsif_ref_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "tsif_ref_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl clk_tbl_usb[] = अणु
	अणु 60000000, P_PLL8, 1, 5, 32 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg usb_hs1_xcvr_src = अणु
	.ns_reg = 0x290c,
	.md_reg = 0x2908,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_usb,
	.clkr = अणु
		.enable_reg = 0x290c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_hs1_xcvr_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_RATE_GATE,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_branch usb_hs1_xcvr_clk = अणु
	.halt_reg = 0x2fc8,
	.halt_bit = 0,
	.clkr = अणु
		.enable_reg = 0x290c,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_hs1_xcvr_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "usb_hs1_xcvr_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg usb_hs3_xcvr_src = अणु
	.ns_reg = 0x370c,
	.md_reg = 0x3708,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_usb,
	.clkr = अणु
		.enable_reg = 0x370c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_hs3_xcvr_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_RATE_GATE,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_branch usb_hs3_xcvr_clk = अणु
	.halt_reg = 0x2fc8,
	.halt_bit = 30,
	.clkr = अणु
		.enable_reg = 0x370c,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_hs3_xcvr_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "usb_hs3_xcvr_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg usb_hs4_xcvr_src = अणु
	.ns_reg = 0x372c,
	.md_reg = 0x3728,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_usb,
	.clkr = अणु
		.enable_reg = 0x372c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_hs4_xcvr_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_RATE_GATE,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_branch usb_hs4_xcvr_clk = अणु
	.halt_reg = 0x2fc8,
	.halt_bit = 2,
	.clkr = अणु
		.enable_reg = 0x372c,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_hs4_xcvr_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "usb_hs4_xcvr_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg usb_hsic_xcvr_fs_src = अणु
	.ns_reg = 0x2928,
	.md_reg = 0x2924,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_usb,
	.clkr = अणु
		.enable_reg = 0x2928,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_hsic_xcvr_fs_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_RATE_GATE,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर usb_hsic_xcvr_fs_src_p[] = अणु "usb_hsic_xcvr_fs_src" पूर्ण;

अटल काष्ठा clk_branch usb_hsic_xcvr_fs_clk = अणु
	.halt_reg = 0x2fc8,
	.halt_bit = 2,
	.clkr = अणु
		.enable_reg = 0x2928,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_hsic_xcvr_fs_clk",
			.parent_names = usb_hsic_xcvr_fs_src_p,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch usb_hsic_प्रणाली_clk = अणु
	.halt_reg = 0x2fcc,
	.halt_bit = 24,
	.clkr = अणु
		.enable_reg = 0x292c,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = usb_hsic_xcvr_fs_src_p,
			.num_parents = 1,
			.name = "usb_hsic_system_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch usb_hsic_hsic_clk = अणु
	.halt_reg = 0x2fcc,
	.halt_bit = 19,
	.clkr = अणु
		.enable_reg = 0x2b44,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = (स्थिर अक्षर *[])अणु "pll14_vote" पूर्ण,
			.num_parents = 1,
			.name = "usb_hsic_hsic_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch usb_hsic_hsio_cal_clk = अणु
	.halt_reg = 0x2fcc,
	.halt_bit = 23,
	.clkr = अणु
		.enable_reg = 0x2b48,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_hsic_hsio_cal_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg usb_fs1_xcvr_fs_src = अणु
	.ns_reg = 0x2968,
	.md_reg = 0x2964,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_usb,
	.clkr = अणु
		.enable_reg = 0x2968,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_fs1_xcvr_fs_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_RATE_GATE,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर usb_fs1_xcvr_fs_src_p[] = अणु "usb_fs1_xcvr_fs_src" पूर्ण;

अटल काष्ठा clk_branch usb_fs1_xcvr_fs_clk = अणु
	.halt_reg = 0x2fcc,
	.halt_bit = 15,
	.clkr = अणु
		.enable_reg = 0x2968,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_fs1_xcvr_fs_clk",
			.parent_names = usb_fs1_xcvr_fs_src_p,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch usb_fs1_प्रणाली_clk = अणु
	.halt_reg = 0x2fcc,
	.halt_bit = 16,
	.clkr = अणु
		.enable_reg = 0x296c,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = usb_fs1_xcvr_fs_src_p,
			.num_parents = 1,
			.name = "usb_fs1_system_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg usb_fs2_xcvr_fs_src = अणु
	.ns_reg = 0x2988,
	.md_reg = 0x2984,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_usb,
	.clkr = अणु
		.enable_reg = 0x2988,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_fs2_xcvr_fs_src",
			.parent_names = gcc_pxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_RATE_GATE,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर usb_fs2_xcvr_fs_src_p[] = अणु "usb_fs2_xcvr_fs_src" पूर्ण;

अटल काष्ठा clk_branch usb_fs2_xcvr_fs_clk = अणु
	.halt_reg = 0x2fcc,
	.halt_bit = 12,
	.clkr = अणु
		.enable_reg = 0x2988,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_fs2_xcvr_fs_clk",
			.parent_names = usb_fs2_xcvr_fs_src_p,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch usb_fs2_प्रणाली_clk = अणु
	.halt_reg = 0x2fcc,
	.halt_bit = 13,
	.clkr = अणु
		.enable_reg = 0x298c,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_fs2_system_clk",
			.parent_names = usb_fs2_xcvr_fs_src_p,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch ce1_core_clk = अणु
	.hwcg_reg = 0x2724,
	.hwcg_bit = 6,
	.halt_reg = 0x2fd4,
	.halt_bit = 27,
	.clkr = अणु
		.enable_reg = 0x2724,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "ce1_core_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch ce1_h_clk = अणु
	.halt_reg = 0x2fd4,
	.halt_bit = 1,
	.clkr = अणु
		.enable_reg = 0x2720,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "ce1_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch dma_bam_h_clk = अणु
	.hwcg_reg = 0x25c0,
	.hwcg_bit = 6,
	.halt_reg = 0x2fc8,
	.halt_bit = 12,
	.clkr = अणु
		.enable_reg = 0x25c0,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "dma_bam_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi1_h_clk = अणु
	.hwcg_reg = 0x29c0,
	.hwcg_bit = 6,
	.halt_reg = 0x2fcc,
	.halt_bit = 11,
	.clkr = अणु
		.enable_reg = 0x29c0,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi1_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi2_h_clk = अणु
	.hwcg_reg = 0x29e0,
	.hwcg_bit = 6,
	.halt_reg = 0x2fcc,
	.halt_bit = 7,
	.clkr = अणु
		.enable_reg = 0x29e0,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi2_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi3_h_clk = अणु
	.hwcg_reg = 0x2a00,
	.hwcg_bit = 6,
	.halt_reg = 0x2fcc,
	.halt_bit = 3,
	.clkr = अणु
		.enable_reg = 0x2a00,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi3_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi4_h_clk = अणु
	.hwcg_reg = 0x2a20,
	.hwcg_bit = 6,
	.halt_reg = 0x2fd0,
	.halt_bit = 27,
	.clkr = अणु
		.enable_reg = 0x2a20,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi4_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi5_h_clk = अणु
	.hwcg_reg = 0x2a40,
	.hwcg_bit = 6,
	.halt_reg = 0x2fd0,
	.halt_bit = 23,
	.clkr = अणु
		.enable_reg = 0x2a40,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi5_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi6_h_clk = अणु
	.hwcg_reg = 0x2a60,
	.hwcg_bit = 6,
	.halt_reg = 0x2fd0,
	.halt_bit = 19,
	.clkr = अणु
		.enable_reg = 0x2a60,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi6_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi7_h_clk = अणु
	.hwcg_reg = 0x2a80,
	.hwcg_bit = 6,
	.halt_reg = 0x2fd0,
	.halt_bit = 15,
	.clkr = अणु
		.enable_reg = 0x2a80,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi7_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi8_h_clk = अणु
	.hwcg_reg = 0x2aa0,
	.hwcg_bit = 6,
	.halt_reg = 0x2fd0,
	.halt_bit = 11,
	.clkr = अणु
		.enable_reg = 0x2aa0,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi8_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi9_h_clk = अणु
	.hwcg_reg = 0x2ac0,
	.hwcg_bit = 6,
	.halt_reg = 0x2fd0,
	.halt_bit = 7,
	.clkr = अणु
		.enable_reg = 0x2ac0,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi9_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi10_h_clk = अणु
	.hwcg_reg = 0x2ae0,
	.hwcg_bit = 6,
	.halt_reg = 0x2fd0,
	.halt_bit = 3,
	.clkr = अणु
		.enable_reg = 0x2ae0,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi10_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi11_h_clk = अणु
	.hwcg_reg = 0x2b00,
	.hwcg_bit = 6,
	.halt_reg = 0x2fd4,
	.halt_bit = 18,
	.clkr = अणु
		.enable_reg = 0x2b00,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi11_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gsbi12_h_clk = अणु
	.hwcg_reg = 0x2b20,
	.hwcg_bit = 6,
	.halt_reg = 0x2fd4,
	.halt_bit = 14,
	.clkr = अणु
		.enable_reg = 0x2b20,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi12_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch tsअगर_h_clk = अणु
	.hwcg_reg = 0x2700,
	.hwcg_bit = 6,
	.halt_reg = 0x2fd4,
	.halt_bit = 7,
	.clkr = अणु
		.enable_reg = 0x2700,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "tsif_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch usb_fs1_h_clk = अणु
	.halt_reg = 0x2fcc,
	.halt_bit = 17,
	.clkr = अणु
		.enable_reg = 0x2960,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_fs1_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch usb_fs2_h_clk = अणु
	.halt_reg = 0x2fcc,
	.halt_bit = 14,
	.clkr = अणु
		.enable_reg = 0x2980,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_fs2_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch usb_hs1_h_clk = अणु
	.hwcg_reg = 0x2900,
	.hwcg_bit = 6,
	.halt_reg = 0x2fc8,
	.halt_bit = 1,
	.clkr = अणु
		.enable_reg = 0x2900,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_hs1_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch usb_hs3_h_clk = अणु
	.halt_reg = 0x2fc8,
	.halt_bit = 31,
	.clkr = अणु
		.enable_reg = 0x3700,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_hs3_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch usb_hs4_h_clk = अणु
	.halt_reg = 0x2fc8,
	.halt_bit = 7,
	.clkr = अणु
		.enable_reg = 0x3720,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_hs4_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch usb_hsic_h_clk = अणु
	.halt_reg = 0x2fcc,
	.halt_bit = 28,
	.clkr = अणु
		.enable_reg = 0x2920,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_hsic_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch sdc1_h_clk = अणु
	.hwcg_reg = 0x2820,
	.hwcg_bit = 6,
	.halt_reg = 0x2fc8,
	.halt_bit = 11,
	.clkr = अणु
		.enable_reg = 0x2820,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sdc1_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch sdc2_h_clk = अणु
	.hwcg_reg = 0x2840,
	.hwcg_bit = 6,
	.halt_reg = 0x2fc8,
	.halt_bit = 10,
	.clkr = अणु
		.enable_reg = 0x2840,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sdc2_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch sdc3_h_clk = अणु
	.hwcg_reg = 0x2860,
	.hwcg_bit = 6,
	.halt_reg = 0x2fc8,
	.halt_bit = 9,
	.clkr = अणु
		.enable_reg = 0x2860,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sdc3_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch sdc4_h_clk = अणु
	.hwcg_reg = 0x2880,
	.hwcg_bit = 6,
	.halt_reg = 0x2fc8,
	.halt_bit = 8,
	.clkr = अणु
		.enable_reg = 0x2880,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sdc4_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch sdc5_h_clk = अणु
	.hwcg_reg = 0x28a0,
	.hwcg_bit = 6,
	.halt_reg = 0x2fc8,
	.halt_bit = 7,
	.clkr = अणु
		.enable_reg = 0x28a0,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sdc5_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch adm0_clk = अणु
	.halt_reg = 0x2fdc,
	.halt_check = BRANCH_HALT_VOTED,
	.halt_bit = 14,
	.clkr = अणु
		.enable_reg = 0x3080,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "adm0_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch adm0_pbus_clk = अणु
	.hwcg_reg = 0x2208,
	.hwcg_bit = 6,
	.halt_reg = 0x2fdc,
	.halt_check = BRANCH_HALT_VOTED,
	.halt_bit = 13,
	.clkr = अणु
		.enable_reg = 0x3080,
		.enable_mask = BIT(3),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "adm0_pbus_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_ce3[] = अणु
	अणु 48000000, P_PLL8, 8 पूर्ण,
	अणु 100000000, P_PLL3, 12 पूर्ण,
	अणु 120000000, P_PLL3, 10 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg ce3_src = अणु
	.ns_reg = 0x36c0,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 4,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_pll3_map,
	पूर्ण,
	.freq_tbl = clk_tbl_ce3,
	.clkr = अणु
		.enable_reg = 0x36c0,
		.enable_mask = BIT(7),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "ce3_src",
			.parent_names = gcc_pxo_pll8_pll3,
			.num_parents = 3,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_RATE_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch ce3_core_clk = अणु
	.halt_reg = 0x2fdc,
	.halt_bit = 5,
	.clkr = अणु
		.enable_reg = 0x36cc,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "ce3_core_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "ce3_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch ce3_h_clk = अणु
	.halt_reg = 0x2fc4,
	.halt_bit = 16,
	.clkr = अणु
		.enable_reg = 0x36c4,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "ce3_h_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "ce3_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl clk_tbl_sata_ref[] = अणु
	अणु 48000000, P_PLL8, 8, 0, 0 पूर्ण,
	अणु 100000000, P_PLL3, 12, 0, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg sata_clk_src = अणु
	.ns_reg = 0x2c08,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 4,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = gcc_pxo_pll8_pll3_map,
	पूर्ण,
	.freq_tbl = clk_tbl_sata_ref,
	.clkr = अणु
		.enable_reg = 0x2c08,
		.enable_mask = BIT(7),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sata_clk_src",
			.parent_names = gcc_pxo_pll8_pll3,
			.num_parents = 3,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_RATE_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch sata_rxoob_clk = अणु
	.halt_reg = 0x2fdc,
	.halt_bit = 26,
	.clkr = अणु
		.enable_reg = 0x2c0c,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sata_rxoob_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "sata_clk_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch sata_pmalive_clk = अणु
	.halt_reg = 0x2fdc,
	.halt_bit = 25,
	.clkr = अणु
		.enable_reg = 0x2c10,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sata_pmalive_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "sata_clk_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch sata_phy_ref_clk = अणु
	.halt_reg = 0x2fdc,
	.halt_bit = 24,
	.clkr = अणु
		.enable_reg = 0x2c14,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sata_phy_ref_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "pxo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch sata_a_clk = अणु
	.halt_reg = 0x2fc0,
	.halt_bit = 12,
	.clkr = अणु
		.enable_reg = 0x2c20,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sata_a_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch sata_h_clk = अणु
	.halt_reg = 0x2fdc,
	.halt_bit = 27,
	.clkr = अणु
		.enable_reg = 0x2c00,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sata_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch sfab_sata_s_h_clk = अणु
	.halt_reg = 0x2fc4,
	.halt_bit = 14,
	.clkr = अणु
		.enable_reg = 0x2480,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sfab_sata_s_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch sata_phy_cfg_clk = अणु
	.halt_reg = 0x2fcc,
	.halt_bit = 12,
	.clkr = अणु
		.enable_reg = 0x2c40,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sata_phy_cfg_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch pcie_phy_ref_clk = अणु
	.halt_reg = 0x2fdc,
	.halt_bit = 29,
	.clkr = अणु
		.enable_reg = 0x22d0,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "pcie_phy_ref_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch pcie_h_clk = अणु
	.halt_reg = 0x2fd4,
	.halt_bit = 8,
	.clkr = अणु
		.enable_reg = 0x22cc,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "pcie_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch pcie_a_clk = अणु
	.halt_reg = 0x2fc0,
	.halt_bit = 13,
	.clkr = अणु
		.enable_reg = 0x22c0,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "pcie_a_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch pmic_arb0_h_clk = अणु
	.halt_reg = 0x2fd8,
	.halt_check = BRANCH_HALT_VOTED,
	.halt_bit = 22,
	.clkr = अणु
		.enable_reg = 0x3080,
		.enable_mask = BIT(8),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "pmic_arb0_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch pmic_arb1_h_clk = अणु
	.halt_reg = 0x2fd8,
	.halt_check = BRANCH_HALT_VOTED,
	.halt_bit = 21,
	.clkr = अणु
		.enable_reg = 0x3080,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "pmic_arb1_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch pmic_ssbi2_clk = अणु
	.halt_reg = 0x2fd8,
	.halt_check = BRANCH_HALT_VOTED,
	.halt_bit = 23,
	.clkr = अणु
		.enable_reg = 0x3080,
		.enable_mask = BIT(7),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "pmic_ssbi2_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch rpm_msg_ram_h_clk = अणु
	.hwcg_reg = 0x27e0,
	.hwcg_bit = 6,
	.halt_reg = 0x2fd8,
	.halt_check = BRANCH_HALT_VOTED,
	.halt_bit = 12,
	.clkr = अणु
		.enable_reg = 0x3080,
		.enable_mask = BIT(6),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "rpm_msg_ram_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap *gcc_msm8960_clks[] = अणु
	[PLL3] = &pll3.clkr,
	[PLL4_VOTE] = &pll4_vote,
	[PLL8] = &pll8.clkr,
	[PLL8_VOTE] = &pll8_vote,
	[PLL14] = &pll14.clkr,
	[PLL14_VOTE] = &pll14_vote,
	[GSBI1_UART_SRC] = &gsbi1_uart_src.clkr,
	[GSBI1_UART_CLK] = &gsbi1_uart_clk.clkr,
	[GSBI2_UART_SRC] = &gsbi2_uart_src.clkr,
	[GSBI2_UART_CLK] = &gsbi2_uart_clk.clkr,
	[GSBI3_UART_SRC] = &gsbi3_uart_src.clkr,
	[GSBI3_UART_CLK] = &gsbi3_uart_clk.clkr,
	[GSBI4_UART_SRC] = &gsbi4_uart_src.clkr,
	[GSBI4_UART_CLK] = &gsbi4_uart_clk.clkr,
	[GSBI5_UART_SRC] = &gsbi5_uart_src.clkr,
	[GSBI5_UART_CLK] = &gsbi5_uart_clk.clkr,
	[GSBI6_UART_SRC] = &gsbi6_uart_src.clkr,
	[GSBI6_UART_CLK] = &gsbi6_uart_clk.clkr,
	[GSBI7_UART_SRC] = &gsbi7_uart_src.clkr,
	[GSBI7_UART_CLK] = &gsbi7_uart_clk.clkr,
	[GSBI8_UART_SRC] = &gsbi8_uart_src.clkr,
	[GSBI8_UART_CLK] = &gsbi8_uart_clk.clkr,
	[GSBI9_UART_SRC] = &gsbi9_uart_src.clkr,
	[GSBI9_UART_CLK] = &gsbi9_uart_clk.clkr,
	[GSBI10_UART_SRC] = &gsbi10_uart_src.clkr,
	[GSBI10_UART_CLK] = &gsbi10_uart_clk.clkr,
	[GSBI11_UART_SRC] = &gsbi11_uart_src.clkr,
	[GSBI11_UART_CLK] = &gsbi11_uart_clk.clkr,
	[GSBI12_UART_SRC] = &gsbi12_uart_src.clkr,
	[GSBI12_UART_CLK] = &gsbi12_uart_clk.clkr,
	[GSBI1_QUP_SRC] = &gsbi1_qup_src.clkr,
	[GSBI1_QUP_CLK] = &gsbi1_qup_clk.clkr,
	[GSBI2_QUP_SRC] = &gsbi2_qup_src.clkr,
	[GSBI2_QUP_CLK] = &gsbi2_qup_clk.clkr,
	[GSBI3_QUP_SRC] = &gsbi3_qup_src.clkr,
	[GSBI3_QUP_CLK] = &gsbi3_qup_clk.clkr,
	[GSBI4_QUP_SRC] = &gsbi4_qup_src.clkr,
	[GSBI4_QUP_CLK] = &gsbi4_qup_clk.clkr,
	[GSBI5_QUP_SRC] = &gsbi5_qup_src.clkr,
	[GSBI5_QUP_CLK] = &gsbi5_qup_clk.clkr,
	[GSBI6_QUP_SRC] = &gsbi6_qup_src.clkr,
	[GSBI6_QUP_CLK] = &gsbi6_qup_clk.clkr,
	[GSBI7_QUP_SRC] = &gsbi7_qup_src.clkr,
	[GSBI7_QUP_CLK] = &gsbi7_qup_clk.clkr,
	[GSBI8_QUP_SRC] = &gsbi8_qup_src.clkr,
	[GSBI8_QUP_CLK] = &gsbi8_qup_clk.clkr,
	[GSBI9_QUP_SRC] = &gsbi9_qup_src.clkr,
	[GSBI9_QUP_CLK] = &gsbi9_qup_clk.clkr,
	[GSBI10_QUP_SRC] = &gsbi10_qup_src.clkr,
	[GSBI10_QUP_CLK] = &gsbi10_qup_clk.clkr,
	[GSBI11_QUP_SRC] = &gsbi11_qup_src.clkr,
	[GSBI11_QUP_CLK] = &gsbi11_qup_clk.clkr,
	[GSBI12_QUP_SRC] = &gsbi12_qup_src.clkr,
	[GSBI12_QUP_CLK] = &gsbi12_qup_clk.clkr,
	[GP0_SRC] = &gp0_src.clkr,
	[GP0_CLK] = &gp0_clk.clkr,
	[GP1_SRC] = &gp1_src.clkr,
	[GP1_CLK] = &gp1_clk.clkr,
	[GP2_SRC] = &gp2_src.clkr,
	[GP2_CLK] = &gp2_clk.clkr,
	[PMEM_A_CLK] = &pmem_clk.clkr,
	[PRNG_SRC] = &prng_src.clkr,
	[PRNG_CLK] = &prng_clk.clkr,
	[SDC1_SRC] = &sdc1_src.clkr,
	[SDC1_CLK] = &sdc1_clk.clkr,
	[SDC2_SRC] = &sdc2_src.clkr,
	[SDC2_CLK] = &sdc2_clk.clkr,
	[SDC3_SRC] = &sdc3_src.clkr,
	[SDC3_CLK] = &sdc3_clk.clkr,
	[SDC4_SRC] = &sdc4_src.clkr,
	[SDC4_CLK] = &sdc4_clk.clkr,
	[SDC5_SRC] = &sdc5_src.clkr,
	[SDC5_CLK] = &sdc5_clk.clkr,
	[TSIF_REF_SRC] = &tsअगर_ref_src.clkr,
	[TSIF_REF_CLK] = &tsअगर_ref_clk.clkr,
	[USB_HS1_XCVR_SRC] = &usb_hs1_xcvr_src.clkr,
	[USB_HS1_XCVR_CLK] = &usb_hs1_xcvr_clk.clkr,
	[USB_HSIC_XCVR_FS_SRC] = &usb_hsic_xcvr_fs_src.clkr,
	[USB_HSIC_XCVR_FS_CLK] = &usb_hsic_xcvr_fs_clk.clkr,
	[USB_HSIC_SYSTEM_CLK] = &usb_hsic_प्रणाली_clk.clkr,
	[USB_HSIC_HSIC_CLK] = &usb_hsic_hsic_clk.clkr,
	[USB_HSIC_HSIO_CAL_CLK] = &usb_hsic_hsio_cal_clk.clkr,
	[USB_FS1_XCVR_FS_SRC] = &usb_fs1_xcvr_fs_src.clkr,
	[USB_FS1_XCVR_FS_CLK] = &usb_fs1_xcvr_fs_clk.clkr,
	[USB_FS1_SYSTEM_CLK] = &usb_fs1_प्रणाली_clk.clkr,
	[USB_FS2_XCVR_FS_SRC] = &usb_fs2_xcvr_fs_src.clkr,
	[USB_FS2_XCVR_FS_CLK] = &usb_fs2_xcvr_fs_clk.clkr,
	[USB_FS2_SYSTEM_CLK] = &usb_fs2_प्रणाली_clk.clkr,
	[CE1_CORE_CLK] = &ce1_core_clk.clkr,
	[CE1_H_CLK] = &ce1_h_clk.clkr,
	[DMA_BAM_H_CLK] = &dma_bam_h_clk.clkr,
	[GSBI1_H_CLK] = &gsbi1_h_clk.clkr,
	[GSBI2_H_CLK] = &gsbi2_h_clk.clkr,
	[GSBI3_H_CLK] = &gsbi3_h_clk.clkr,
	[GSBI4_H_CLK] = &gsbi4_h_clk.clkr,
	[GSBI5_H_CLK] = &gsbi5_h_clk.clkr,
	[GSBI6_H_CLK] = &gsbi6_h_clk.clkr,
	[GSBI7_H_CLK] = &gsbi7_h_clk.clkr,
	[GSBI8_H_CLK] = &gsbi8_h_clk.clkr,
	[GSBI9_H_CLK] = &gsbi9_h_clk.clkr,
	[GSBI10_H_CLK] = &gsbi10_h_clk.clkr,
	[GSBI11_H_CLK] = &gsbi11_h_clk.clkr,
	[GSBI12_H_CLK] = &gsbi12_h_clk.clkr,
	[TSIF_H_CLK] = &tsअगर_h_clk.clkr,
	[USB_FS1_H_CLK] = &usb_fs1_h_clk.clkr,
	[USB_FS2_H_CLK] = &usb_fs2_h_clk.clkr,
	[USB_HS1_H_CLK] = &usb_hs1_h_clk.clkr,
	[USB_HSIC_H_CLK] = &usb_hsic_h_clk.clkr,
	[SDC1_H_CLK] = &sdc1_h_clk.clkr,
	[SDC2_H_CLK] = &sdc2_h_clk.clkr,
	[SDC3_H_CLK] = &sdc3_h_clk.clkr,
	[SDC4_H_CLK] = &sdc4_h_clk.clkr,
	[SDC5_H_CLK] = &sdc5_h_clk.clkr,
	[ADM0_CLK] = &adm0_clk.clkr,
	[ADM0_PBUS_CLK] = &adm0_pbus_clk.clkr,
	[PMIC_ARB0_H_CLK] = &pmic_arb0_h_clk.clkr,
	[PMIC_ARB1_H_CLK] = &pmic_arb1_h_clk.clkr,
	[PMIC_SSBI2_CLK] = &pmic_ssbi2_clk.clkr,
	[RPM_MSG_RAM_H_CLK] = &rpm_msg_ram_h_clk.clkr,
	[PLL9] = &hfpll0.clkr,
	[PLL10] = &hfpll1.clkr,
	[PLL12] = &hfpll_l2.clkr,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map gcc_msm8960_resets[] = अणु
	[SFAB_MSS_Q6_SW_RESET] = अणु 0x2040, 7 पूर्ण,
	[SFAB_MSS_Q6_FW_RESET] = अणु 0x2044, 7 पूर्ण,
	[QDSS_STM_RESET] = अणु 0x2060, 6 पूर्ण,
	[AFAB_SMPSS_S_RESET] = अणु 0x20b8, 2 पूर्ण,
	[AFAB_SMPSS_M1_RESET] = अणु 0x20b8, 1 पूर्ण,
	[AFAB_SMPSS_M0_RESET] = अणु 0x20b8 पूर्ण,
	[AFAB_EBI1_CH0_RESET] = अणु 0x20c0, 7 पूर्ण,
	[AFAB_EBI1_CH1_RESET] = अणु 0x20c4, 7पूर्ण,
	[SFAB_ADM0_M0_RESET] = अणु 0x21e0, 7 पूर्ण,
	[SFAB_ADM0_M1_RESET] = अणु 0x21e4, 7 पूर्ण,
	[SFAB_ADM0_M2_RESET] = अणु 0x21e8, 7 पूर्ण,
	[ADM0_C2_RESET] = अणु 0x220c, 4पूर्ण,
	[ADM0_C1_RESET] = अणु 0x220c, 3पूर्ण,
	[ADM0_C0_RESET] = अणु 0x220c, 2पूर्ण,
	[ADM0_PBUS_RESET] = अणु 0x220c, 1 पूर्ण,
	[ADM0_RESET] = अणु 0x220c पूर्ण,
	[QDSS_CLKS_SW_RESET] = अणु 0x2260, 5 पूर्ण,
	[QDSS_POR_RESET] = अणु 0x2260, 4 पूर्ण,
	[QDSS_TSCTR_RESET] = अणु 0x2260, 3 पूर्ण,
	[QDSS_HRESET_RESET] = अणु 0x2260, 2 पूर्ण,
	[QDSS_AXI_RESET] = अणु 0x2260, 1 पूर्ण,
	[QDSS_DBG_RESET] = अणु 0x2260 पूर्ण,
	[PCIE_A_RESET] = अणु 0x22c0, 7 पूर्ण,
	[PCIE_AUX_RESET] = अणु 0x22c8, 7 पूर्ण,
	[PCIE_H_RESET] = अणु 0x22d0, 7 पूर्ण,
	[SFAB_PCIE_M_RESET] = अणु 0x22d4, 1 पूर्ण,
	[SFAB_PCIE_S_RESET] = अणु 0x22d4 पूर्ण,
	[SFAB_MSS_M_RESET] = अणु 0x2340, 7 पूर्ण,
	[SFAB_USB3_M_RESET] = अणु 0x2360, 7 पूर्ण,
	[SFAB_RIVA_M_RESET] = अणु 0x2380, 7 पूर्ण,
	[SFAB_LPASS_RESET] = अणु 0x23a0, 7 पूर्ण,
	[SFAB_AFAB_M_RESET] = अणु 0x23e0, 7 पूर्ण,
	[AFAB_SFAB_M0_RESET] = अणु 0x2420, 7 पूर्ण,
	[AFAB_SFAB_M1_RESET] = अणु 0x2424, 7 पूर्ण,
	[SFAB_SATA_S_RESET] = अणु 0x2480, 7 पूर्ण,
	[SFAB_DFAB_M_RESET] = अणु 0x2500, 7 पूर्ण,
	[DFAB_SFAB_M_RESET] = अणु 0x2520, 7 पूर्ण,
	[DFAB_SWAY0_RESET] = अणु 0x2540, 7 पूर्ण,
	[DFAB_SWAY1_RESET] = अणु 0x2544, 7 पूर्ण,
	[DFAB_ARB0_RESET] = अणु 0x2560, 7 पूर्ण,
	[DFAB_ARB1_RESET] = अणु 0x2564, 7 पूर्ण,
	[PPSS_PROC_RESET] = अणु 0x2594, 1 पूर्ण,
	[PPSS_RESET] = अणु 0x2594पूर्ण,
	[DMA_BAM_RESET] = अणु 0x25c0, 7 पूर्ण,
	[SPS_TIC_H_RESET] = अणु 0x2600, 7 पूर्ण,
	[SLIMBUS_H_RESET] = अणु 0x2620, 7 पूर्ण,
	[SFAB_CFPB_M_RESET] = अणु 0x2680, 7 पूर्ण,
	[SFAB_CFPB_S_RESET] = अणु 0x26c0, 7 पूर्ण,
	[TSIF_H_RESET] = अणु 0x2700, 7 पूर्ण,
	[CE1_H_RESET] = अणु 0x2720, 7 पूर्ण,
	[CE1_CORE_RESET] = अणु 0x2724, 7 पूर्ण,
	[CE1_SLEEP_RESET] = अणु 0x2728, 7 पूर्ण,
	[CE2_H_RESET] = अणु 0x2740, 7 पूर्ण,
	[CE2_CORE_RESET] = अणु 0x2744, 7 पूर्ण,
	[SFAB_SFPB_M_RESET] = अणु 0x2780, 7 पूर्ण,
	[SFAB_SFPB_S_RESET] = अणु 0x27a0, 7 पूर्ण,
	[RPM_PROC_RESET] = अणु 0x27c0, 7 पूर्ण,
	[PMIC_SSBI2_RESET] = अणु 0x280c, 12 पूर्ण,
	[SDC1_RESET] = अणु 0x2830 पूर्ण,
	[SDC2_RESET] = अणु 0x2850 पूर्ण,
	[SDC3_RESET] = अणु 0x2870 पूर्ण,
	[SDC4_RESET] = अणु 0x2890 पूर्ण,
	[SDC5_RESET] = अणु 0x28b0 पूर्ण,
	[DFAB_A2_RESET] = अणु 0x28c0, 7 पूर्ण,
	[USB_HS1_RESET] = अणु 0x2910 पूर्ण,
	[USB_HSIC_RESET] = अणु 0x2934 पूर्ण,
	[USB_FS1_XCVR_RESET] = अणु 0x2974, 1 पूर्ण,
	[USB_FS1_RESET] = अणु 0x2974 पूर्ण,
	[USB_FS2_XCVR_RESET] = अणु 0x2994, 1 पूर्ण,
	[USB_FS2_RESET] = अणु 0x2994 पूर्ण,
	[GSBI1_RESET] = अणु 0x29dc पूर्ण,
	[GSBI2_RESET] = अणु 0x29fc पूर्ण,
	[GSBI3_RESET] = अणु 0x2a1c पूर्ण,
	[GSBI4_RESET] = अणु 0x2a3c पूर्ण,
	[GSBI5_RESET] = अणु 0x2a5c पूर्ण,
	[GSBI6_RESET] = अणु 0x2a7c पूर्ण,
	[GSBI7_RESET] = अणु 0x2a9c पूर्ण,
	[GSBI8_RESET] = अणु 0x2abc पूर्ण,
	[GSBI9_RESET] = अणु 0x2adc पूर्ण,
	[GSBI10_RESET] = अणु 0x2afc पूर्ण,
	[GSBI11_RESET] = अणु 0x2b1c पूर्ण,
	[GSBI12_RESET] = अणु 0x2b3c पूर्ण,
	[SPDM_RESET] = अणु 0x2b6c पूर्ण,
	[TLMM_H_RESET] = अणु 0x2ba0, 7 पूर्ण,
	[SFAB_MSS_S_RESET] = अणु 0x2c00, 7 पूर्ण,
	[MSS_SLP_RESET] = अणु 0x2c60, 7 पूर्ण,
	[MSS_Q6SW_JTAG_RESET] = अणु 0x2c68, 7 पूर्ण,
	[MSS_Q6FW_JTAG_RESET] = अणु 0x2c6c, 7 पूर्ण,
	[MSS_RESET] = अणु 0x2c64 पूर्ण,
	[SATA_H_RESET] = अणु 0x2c80, 7 पूर्ण,
	[SATA_RXOOB_RESE] = अणु 0x2c8c, 7 पूर्ण,
	[SATA_PMALIVE_RESET] = अणु 0x2c90, 7 पूर्ण,
	[SATA_SFAB_M_RESET] = अणु 0x2c98, 7 पूर्ण,
	[TSSC_RESET] = अणु 0x2ca0, 7 पूर्ण,
	[PDM_RESET] = अणु 0x2cc0, 12 पूर्ण,
	[MPM_H_RESET] = अणु 0x2da0, 7 पूर्ण,
	[MPM_RESET] = अणु 0x2da4 पूर्ण,
	[SFAB_SMPSS_S_RESET] = अणु 0x2e00, 7 पूर्ण,
	[PRNG_RESET] = अणु 0x2e80, 12 पूर्ण,
	[RIVA_RESET] = अणु 0x35e0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap *gcc_apq8064_clks[] = अणु
	[PLL3] = &pll3.clkr,
	[PLL4_VOTE] = &pll4_vote,
	[PLL8] = &pll8.clkr,
	[PLL8_VOTE] = &pll8_vote,
	[PLL14] = &pll14.clkr,
	[PLL14_VOTE] = &pll14_vote,
	[GSBI1_UART_SRC] = &gsbi1_uart_src.clkr,
	[GSBI1_UART_CLK] = &gsbi1_uart_clk.clkr,
	[GSBI2_UART_SRC] = &gsbi2_uart_src.clkr,
	[GSBI2_UART_CLK] = &gsbi2_uart_clk.clkr,
	[GSBI3_UART_SRC] = &gsbi3_uart_src.clkr,
	[GSBI3_UART_CLK] = &gsbi3_uart_clk.clkr,
	[GSBI4_UART_SRC] = &gsbi4_uart_src.clkr,
	[GSBI4_UART_CLK] = &gsbi4_uart_clk.clkr,
	[GSBI5_UART_SRC] = &gsbi5_uart_src.clkr,
	[GSBI5_UART_CLK] = &gsbi5_uart_clk.clkr,
	[GSBI6_UART_SRC] = &gsbi6_uart_src.clkr,
	[GSBI6_UART_CLK] = &gsbi6_uart_clk.clkr,
	[GSBI7_UART_SRC] = &gsbi7_uart_src.clkr,
	[GSBI7_UART_CLK] = &gsbi7_uart_clk.clkr,
	[GSBI1_QUP_SRC] = &gsbi1_qup_src.clkr,
	[GSBI1_QUP_CLK] = &gsbi1_qup_clk.clkr,
	[GSBI2_QUP_SRC] = &gsbi2_qup_src.clkr,
	[GSBI2_QUP_CLK] = &gsbi2_qup_clk.clkr,
	[GSBI3_QUP_SRC] = &gsbi3_qup_src.clkr,
	[GSBI3_QUP_CLK] = &gsbi3_qup_clk.clkr,
	[GSBI4_QUP_SRC] = &gsbi4_qup_src.clkr,
	[GSBI4_QUP_CLK] = &gsbi4_qup_clk.clkr,
	[GSBI5_QUP_SRC] = &gsbi5_qup_src.clkr,
	[GSBI5_QUP_CLK] = &gsbi5_qup_clk.clkr,
	[GSBI6_QUP_SRC] = &gsbi6_qup_src.clkr,
	[GSBI6_QUP_CLK] = &gsbi6_qup_clk.clkr,
	[GSBI7_QUP_SRC] = &gsbi7_qup_src.clkr,
	[GSBI7_QUP_CLK] = &gsbi7_qup_clk.clkr,
	[GP0_SRC] = &gp0_src.clkr,
	[GP0_CLK] = &gp0_clk.clkr,
	[GP1_SRC] = &gp1_src.clkr,
	[GP1_CLK] = &gp1_clk.clkr,
	[GP2_SRC] = &gp2_src.clkr,
	[GP2_CLK] = &gp2_clk.clkr,
	[PMEM_A_CLK] = &pmem_clk.clkr,
	[PRNG_SRC] = &prng_src.clkr,
	[PRNG_CLK] = &prng_clk.clkr,
	[SDC1_SRC] = &sdc1_src.clkr,
	[SDC1_CLK] = &sdc1_clk.clkr,
	[SDC2_SRC] = &sdc2_src.clkr,
	[SDC2_CLK] = &sdc2_clk.clkr,
	[SDC3_SRC] = &sdc3_src.clkr,
	[SDC3_CLK] = &sdc3_clk.clkr,
	[SDC4_SRC] = &sdc4_src.clkr,
	[SDC4_CLK] = &sdc4_clk.clkr,
	[TSIF_REF_SRC] = &tsअगर_ref_src.clkr,
	[TSIF_REF_CLK] = &tsअगर_ref_clk.clkr,
	[USB_HS1_XCVR_SRC] = &usb_hs1_xcvr_src.clkr,
	[USB_HS1_XCVR_CLK] = &usb_hs1_xcvr_clk.clkr,
	[USB_HS3_XCVR_SRC] = &usb_hs3_xcvr_src.clkr,
	[USB_HS3_XCVR_CLK] = &usb_hs3_xcvr_clk.clkr,
	[USB_HS4_XCVR_SRC] = &usb_hs4_xcvr_src.clkr,
	[USB_HS4_XCVR_CLK] = &usb_hs4_xcvr_clk.clkr,
	[USB_HSIC_XCVR_FS_SRC] = &usb_hsic_xcvr_fs_src.clkr,
	[USB_HSIC_XCVR_FS_CLK] = &usb_hsic_xcvr_fs_clk.clkr,
	[USB_HSIC_SYSTEM_CLK] = &usb_hsic_प्रणाली_clk.clkr,
	[USB_HSIC_HSIC_CLK] = &usb_hsic_hsic_clk.clkr,
	[USB_HSIC_HSIO_CAL_CLK] = &usb_hsic_hsio_cal_clk.clkr,
	[USB_FS1_XCVR_FS_SRC] = &usb_fs1_xcvr_fs_src.clkr,
	[USB_FS1_XCVR_FS_CLK] = &usb_fs1_xcvr_fs_clk.clkr,
	[USB_FS1_SYSTEM_CLK] = &usb_fs1_प्रणाली_clk.clkr,
	[SATA_H_CLK] = &sata_h_clk.clkr,
	[SATA_CLK_SRC] = &sata_clk_src.clkr,
	[SATA_RXOOB_CLK] = &sata_rxoob_clk.clkr,
	[SATA_PMALIVE_CLK] = &sata_pmalive_clk.clkr,
	[SATA_PHY_REF_CLK] = &sata_phy_ref_clk.clkr,
	[SATA_PHY_CFG_CLK] = &sata_phy_cfg_clk.clkr,
	[SATA_A_CLK] = &sata_a_clk.clkr,
	[SFAB_SATA_S_H_CLK] = &sfab_sata_s_h_clk.clkr,
	[CE3_SRC] = &ce3_src.clkr,
	[CE3_CORE_CLK] = &ce3_core_clk.clkr,
	[CE3_H_CLK] = &ce3_h_clk.clkr,
	[DMA_BAM_H_CLK] = &dma_bam_h_clk.clkr,
	[GSBI1_H_CLK] = &gsbi1_h_clk.clkr,
	[GSBI2_H_CLK] = &gsbi2_h_clk.clkr,
	[GSBI3_H_CLK] = &gsbi3_h_clk.clkr,
	[GSBI4_H_CLK] = &gsbi4_h_clk.clkr,
	[GSBI5_H_CLK] = &gsbi5_h_clk.clkr,
	[GSBI6_H_CLK] = &gsbi6_h_clk.clkr,
	[GSBI7_H_CLK] = &gsbi7_h_clk.clkr,
	[TSIF_H_CLK] = &tsअगर_h_clk.clkr,
	[USB_FS1_H_CLK] = &usb_fs1_h_clk.clkr,
	[USB_HS1_H_CLK] = &usb_hs1_h_clk.clkr,
	[USB_HSIC_H_CLK] = &usb_hsic_h_clk.clkr,
	[USB_HS3_H_CLK] = &usb_hs3_h_clk.clkr,
	[USB_HS4_H_CLK] = &usb_hs4_h_clk.clkr,
	[SDC1_H_CLK] = &sdc1_h_clk.clkr,
	[SDC2_H_CLK] = &sdc2_h_clk.clkr,
	[SDC3_H_CLK] = &sdc3_h_clk.clkr,
	[SDC4_H_CLK] = &sdc4_h_clk.clkr,
	[ADM0_CLK] = &adm0_clk.clkr,
	[ADM0_PBUS_CLK] = &adm0_pbus_clk.clkr,
	[PCIE_A_CLK] = &pcie_a_clk.clkr,
	[PCIE_PHY_REF_CLK] = &pcie_phy_ref_clk.clkr,
	[PCIE_H_CLK] = &pcie_h_clk.clkr,
	[PMIC_ARB0_H_CLK] = &pmic_arb0_h_clk.clkr,
	[PMIC_ARB1_H_CLK] = &pmic_arb1_h_clk.clkr,
	[PMIC_SSBI2_CLK] = &pmic_ssbi2_clk.clkr,
	[RPM_MSG_RAM_H_CLK] = &rpm_msg_ram_h_clk.clkr,
	[PLL9] = &hfpll0.clkr,
	[PLL10] = &hfpll1.clkr,
	[PLL12] = &hfpll_l2.clkr,
	[PLL16] = &hfpll2.clkr,
	[PLL17] = &hfpll3.clkr,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map gcc_apq8064_resets[] = अणु
	[QDSS_STM_RESET] = अणु 0x2060, 6 पूर्ण,
	[AFAB_SMPSS_S_RESET] = अणु 0x20b8, 2 पूर्ण,
	[AFAB_SMPSS_M1_RESET] = अणु 0x20b8, 1 पूर्ण,
	[AFAB_SMPSS_M0_RESET] = अणु 0x20b8 पूर्ण,
	[AFAB_EBI1_CH0_RESET] = अणु 0x20c0, 7 पूर्ण,
	[AFAB_EBI1_CH1_RESET] = अणु 0x20c4, 7पूर्ण,
	[SFAB_ADM0_M0_RESET] = अणु 0x21e0, 7 पूर्ण,
	[SFAB_ADM0_M1_RESET] = अणु 0x21e4, 7 पूर्ण,
	[SFAB_ADM0_M2_RESET] = अणु 0x21e8, 7 पूर्ण,
	[ADM0_C2_RESET] = अणु 0x220c, 4पूर्ण,
	[ADM0_C1_RESET] = अणु 0x220c, 3पूर्ण,
	[ADM0_C0_RESET] = अणु 0x220c, 2पूर्ण,
	[ADM0_PBUS_RESET] = अणु 0x220c, 1 पूर्ण,
	[ADM0_RESET] = अणु 0x220c पूर्ण,
	[QDSS_CLKS_SW_RESET] = अणु 0x2260, 5 पूर्ण,
	[QDSS_POR_RESET] = अणु 0x2260, 4 पूर्ण,
	[QDSS_TSCTR_RESET] = अणु 0x2260, 3 पूर्ण,
	[QDSS_HRESET_RESET] = अणु 0x2260, 2 पूर्ण,
	[QDSS_AXI_RESET] = अणु 0x2260, 1 पूर्ण,
	[QDSS_DBG_RESET] = अणु 0x2260 पूर्ण,
	[SFAB_PCIE_M_RESET] = अणु 0x22d8, 1 पूर्ण,
	[SFAB_PCIE_S_RESET] = अणु 0x22d8 पूर्ण,
	[PCIE_EXT_PCI_RESET] = अणु 0x22dc, 6 पूर्ण,
	[PCIE_PHY_RESET] = अणु 0x22dc, 5 पूर्ण,
	[PCIE_PCI_RESET] = अणु 0x22dc, 4 पूर्ण,
	[PCIE_POR_RESET] = अणु 0x22dc, 3 पूर्ण,
	[PCIE_HCLK_RESET] = अणु 0x22dc, 2 पूर्ण,
	[PCIE_ACLK_RESET] = अणु 0x22dc पूर्ण,
	[SFAB_USB3_M_RESET] = अणु 0x2360, 7 पूर्ण,
	[SFAB_RIVA_M_RESET] = अणु 0x2380, 7 पूर्ण,
	[SFAB_LPASS_RESET] = अणु 0x23a0, 7 पूर्ण,
	[SFAB_AFAB_M_RESET] = अणु 0x23e0, 7 पूर्ण,
	[AFAB_SFAB_M0_RESET] = अणु 0x2420, 7 पूर्ण,
	[AFAB_SFAB_M1_RESET] = अणु 0x2424, 7 पूर्ण,
	[SFAB_SATA_S_RESET] = अणु 0x2480, 7 पूर्ण,
	[SFAB_DFAB_M_RESET] = अणु 0x2500, 7 पूर्ण,
	[DFAB_SFAB_M_RESET] = अणु 0x2520, 7 पूर्ण,
	[DFAB_SWAY0_RESET] = अणु 0x2540, 7 पूर्ण,
	[DFAB_SWAY1_RESET] = अणु 0x2544, 7 पूर्ण,
	[DFAB_ARB0_RESET] = अणु 0x2560, 7 पूर्ण,
	[DFAB_ARB1_RESET] = अणु 0x2564, 7 पूर्ण,
	[PPSS_PROC_RESET] = अणु 0x2594, 1 पूर्ण,
	[PPSS_RESET] = अणु 0x2594पूर्ण,
	[DMA_BAM_RESET] = अणु 0x25c0, 7 पूर्ण,
	[SPS_TIC_H_RESET] = अणु 0x2600, 7 पूर्ण,
	[SFAB_CFPB_M_RESET] = अणु 0x2680, 7 पूर्ण,
	[SFAB_CFPB_S_RESET] = अणु 0x26c0, 7 पूर्ण,
	[TSIF_H_RESET] = अणु 0x2700, 7 पूर्ण,
	[CE1_H_RESET] = अणु 0x2720, 7 पूर्ण,
	[CE1_CORE_RESET] = अणु 0x2724, 7 पूर्ण,
	[CE1_SLEEP_RESET] = अणु 0x2728, 7 पूर्ण,
	[CE2_H_RESET] = अणु 0x2740, 7 पूर्ण,
	[CE2_CORE_RESET] = अणु 0x2744, 7 पूर्ण,
	[SFAB_SFPB_M_RESET] = अणु 0x2780, 7 पूर्ण,
	[SFAB_SFPB_S_RESET] = अणु 0x27a0, 7 पूर्ण,
	[RPM_PROC_RESET] = अणु 0x27c0, 7 पूर्ण,
	[PMIC_SSBI2_RESET] = अणु 0x280c, 12 पूर्ण,
	[SDC1_RESET] = अणु 0x2830 पूर्ण,
	[SDC2_RESET] = अणु 0x2850 पूर्ण,
	[SDC3_RESET] = अणु 0x2870 पूर्ण,
	[SDC4_RESET] = अणु 0x2890 पूर्ण,
	[USB_HS1_RESET] = अणु 0x2910 पूर्ण,
	[USB_HSIC_RESET] = अणु 0x2934 पूर्ण,
	[USB_FS1_XCVR_RESET] = अणु 0x2974, 1 पूर्ण,
	[USB_FS1_RESET] = अणु 0x2974 पूर्ण,
	[GSBI1_RESET] = अणु 0x29dc पूर्ण,
	[GSBI2_RESET] = अणु 0x29fc पूर्ण,
	[GSBI3_RESET] = अणु 0x2a1c पूर्ण,
	[GSBI4_RESET] = अणु 0x2a3c पूर्ण,
	[GSBI5_RESET] = अणु 0x2a5c पूर्ण,
	[GSBI6_RESET] = अणु 0x2a7c पूर्ण,
	[GSBI7_RESET] = अणु 0x2a9c पूर्ण,
	[SPDM_RESET] = अणु 0x2b6c पूर्ण,
	[TLMM_H_RESET] = अणु 0x2ba0, 7 पूर्ण,
	[SATA_SFAB_M_RESET] = अणु 0x2c18 पूर्ण,
	[SATA_RESET] = अणु 0x2c1c पूर्ण,
	[GSS_SLP_RESET] = अणु 0x2c60, 7 पूर्ण,
	[GSS_RESET] = अणु 0x2c64 पूर्ण,
	[TSSC_RESET] = अणु 0x2ca0, 7 पूर्ण,
	[PDM_RESET] = अणु 0x2cc0, 12 पूर्ण,
	[MPM_H_RESET] = अणु 0x2da0, 7 पूर्ण,
	[MPM_RESET] = अणु 0x2da4 पूर्ण,
	[SFAB_SMPSS_S_RESET] = अणु 0x2e00, 7 पूर्ण,
	[PRNG_RESET] = अणु 0x2e80, 12 पूर्ण,
	[RIVA_RESET] = अणु 0x35e0 पूर्ण,
	[CE3_H_RESET] = अणु 0x36c4, 7 पूर्ण,
	[SFAB_CE3_M_RESET] = अणु 0x36c8, 1 पूर्ण,
	[SFAB_CE3_S_RESET] = अणु 0x36c8 पूर्ण,
	[CE3_RESET] = अणु 0x36cc, 7 पूर्ण,
	[CE3_SLEEP_RESET] = अणु 0x36d0, 7 पूर्ण,
	[USB_HS3_RESET] = अणु 0x3710 पूर्ण,
	[USB_HS4_RESET] = अणु 0x3730 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config gcc_msm8960_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x3660,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा regmap_config gcc_apq8064_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x3880,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc gcc_msm8960_desc = अणु
	.config = &gcc_msm8960_regmap_config,
	.clks = gcc_msm8960_clks,
	.num_clks = ARRAY_SIZE(gcc_msm8960_clks),
	.resets = gcc_msm8960_resets,
	.num_resets = ARRAY_SIZE(gcc_msm8960_resets),
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc gcc_apq8064_desc = अणु
	.config = &gcc_apq8064_regmap_config,
	.clks = gcc_apq8064_clks,
	.num_clks = ARRAY_SIZE(gcc_apq8064_clks),
	.resets = gcc_apq8064_resets,
	.num_resets = ARRAY_SIZE(gcc_apq8064_resets),
पूर्ण;

अटल स्थिर काष्ठा of_device_id gcc_msm8960_match_table[] = अणु
	अणु .compatible = "qcom,gcc-msm8960", .data = &gcc_msm8960_desc पूर्ण,
	अणु .compatible = "qcom,gcc-apq8064", .data = &gcc_apq8064_desc पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gcc_msm8960_match_table);

अटल पूर्णांक gcc_msm8960_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा platक्रमm_device *tsens;
	पूर्णांक ret;

	match = of_match_device(gcc_msm8960_match_table, &pdev->dev);
	अगर (!match)
		वापस -EINVAL;

	ret = qcom_cc_रेजिस्टर_board_clk(dev, "cxo_board", "cxo", 19200000);
	अगर (ret)
		वापस ret;

	ret = qcom_cc_रेजिस्टर_board_clk(dev, "pxo_board", "pxo", 27000000);
	अगर (ret)
		वापस ret;

	ret = qcom_cc_probe(pdev, match->data);
	अगर (ret)
		वापस ret;

	अगर (match->data == &gcc_apq8064_desc) अणु
		hfpll1.d = &hfpll1_8064_data;
		hfpll_l2.d = &hfpll_l2_8064_data;
	पूर्ण

	tsens = platक्रमm_device_रेजिस्टर_data(&pdev->dev, "qcom-tsens", -1,
					      शून्य, 0);
	अगर (IS_ERR(tsens))
		वापस PTR_ERR(tsens);

	platक्रमm_set_drvdata(pdev, tsens);

	वापस 0;
पूर्ण

अटल पूर्णांक gcc_msm8960_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा platक्रमm_device *tsens = platक्रमm_get_drvdata(pdev);

	platक्रमm_device_unरेजिस्टर(tsens);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver gcc_msm8960_driver = अणु
	.probe		= gcc_msm8960_probe,
	.हटाओ		= gcc_msm8960_हटाओ,
	.driver		= अणु
		.name	= "gcc-msm8960",
		.of_match_table = gcc_msm8960_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init gcc_msm8960_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&gcc_msm8960_driver);
पूर्ण
core_initcall(gcc_msm8960_init);

अटल व्योम __निकास gcc_msm8960_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&gcc_msm8960_driver);
पूर्ण
module_निकास(gcc_msm8960_निकास);

MODULE_DESCRIPTION("QCOM GCC MSM8960 Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:gcc-msm8960");
