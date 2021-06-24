<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
 * Copyright (c) BayLibre, SAS.
 * Author : Neil Armstrong <narmstrong@baylibre.com>
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

#समावेश <dt-bindings/घड़ी/qcom,gcc-mdm9615.h>
#समावेश <dt-bindings/reset/qcom,gcc-mdm9615.h>

#समावेश "common.h"
#समावेश "clk-regmap.h"
#समावेश "clk-pll.h"
#समावेश "clk-rcg.h"
#समावेश "clk-branch.h"
#समावेश "reset.h"

अटल काष्ठा clk_fixed_factor cxo = अणु
	.mult = 1,
	.भाग = 1,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cxo",
		.parent_names = (स्थिर अक्षर *[])अणु "cxo_board" पूर्ण,
		.num_parents = 1,
		.ops = &clk_fixed_factor_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_pll pll0 = अणु
	.l_reg = 0x30c4,
	.m_reg = 0x30c8,
	.n_reg = 0x30cc,
	.config_reg = 0x30d4,
	.mode_reg = 0x30c0,
	.status_reg = 0x30d8,
	.status_bit = 16,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pll0",
		.parent_names = (स्थिर अक्षर *[])अणु "cxo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap pll0_vote = अणु
	.enable_reg = 0x34c0,
	.enable_mask = BIT(0),
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pll0_vote",
		.parent_names = (स्थिर अक्षर *[])अणु "pll8" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_vote_ops,
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
		.parent_names = (स्थिर अक्षर *[])अणु "cxo" पूर्ण,
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
		.parent_names = (स्थिर अक्षर *[])अणु "cxo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap pll14_vote = अणु
	.enable_reg = 0x34c0,
	.enable_mask = BIT(11),
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pll14_vote",
		.parent_names = (स्थिर अक्षर *[])अणु "pll14" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_vote_ops,
	पूर्ण,
पूर्ण;

क्रमागत अणु
	P_CXO,
	P_PLL8,
	P_PLL14,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_cxo_pll8_map[] = अणु
	अणु P_CXO, 0 पूर्ण,
	अणु P_PLL8, 3 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_cxo_pll8[] = अणु
	"cxo",
	"pll8_vote",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_cxo_pll14_map[] = अणु
	अणु P_CXO, 0 पूर्ण,
	अणु P_PLL14, 4 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_cxo_pll14[] = अणु
	"cxo",
	"pll14_vote",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_cxo_map[] = अणु
	अणु P_CXO, 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_cxo[] = अणु
	"cxo",
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
		.parent_map = gcc_cxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_uart,
	.clkr = अणु
		.enable_reg = 0x29d4,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi1_uart_src",
			.parent_names = gcc_cxo_pll8,
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
		.parent_map = gcc_cxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_uart,
	.clkr = अणु
		.enable_reg = 0x29f4,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi2_uart_src",
			.parent_names = gcc_cxo_pll8,
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
		.parent_map = gcc_cxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_uart,
	.clkr = अणु
		.enable_reg = 0x2a14,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi3_uart_src",
			.parent_names = gcc_cxo_pll8,
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
		.parent_map = gcc_cxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_uart,
	.clkr = अणु
		.enable_reg = 0x2a34,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi4_uart_src",
			.parent_names = gcc_cxo_pll8,
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
		.parent_map = gcc_cxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_uart,
	.clkr = अणु
		.enable_reg = 0x2a54,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi5_uart_src",
			.parent_names = gcc_cxo_pll8,
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

अटल काष्ठा freq_tbl clk_tbl_gsbi_qup[] = अणु
	अणु   960000, P_CXO,  4, 1,  5 पूर्ण,
	अणु  4800000, P_CXO,  4, 0,  1 पूर्ण,
	अणु  9600000, P_CXO,  2, 0,  1 पूर्ण,
	अणु 15060000, P_PLL8, 1, 2, 51 पूर्ण,
	अणु 24000000, P_PLL8, 4, 1,  4 पूर्ण,
	अणु 25600000, P_PLL8, 1, 1, 15 पूर्ण,
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
		.parent_map = gcc_cxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_qup,
	.clkr = अणु
		.enable_reg = 0x29cc,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi1_qup_src",
			.parent_names = gcc_cxo_pll8,
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
		.parent_map = gcc_cxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_qup,
	.clkr = अणु
		.enable_reg = 0x29ec,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi2_qup_src",
			.parent_names = gcc_cxo_pll8,
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
		.parent_map = gcc_cxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_qup,
	.clkr = अणु
		.enable_reg = 0x2a0c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi3_qup_src",
			.parent_names = gcc_cxo_pll8,
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
		.parent_map = gcc_cxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_qup,
	.clkr = अणु
		.enable_reg = 0x2a2c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi4_qup_src",
			.parent_names = gcc_cxo_pll8,
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
		.parent_map = gcc_cxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gsbi_qup,
	.clkr = अणु
		.enable_reg = 0x2a4c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gsbi5_qup_src",
			.parent_names = gcc_cxo_pll8,
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

अटल स्थिर काष्ठा freq_tbl clk_tbl_gp[] = अणु
	अणु 9600000, P_CXO,  2, 0, 0 पूर्ण,
	अणु 19200000, P_CXO,  1, 0, 0 पूर्ण,
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
		.parent_map = gcc_cxo_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gp,
	.clkr = अणु
		.enable_reg = 0x2d24,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gp0_src",
			.parent_names = gcc_cxo,
			.num_parents = 1,
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
		.parent_map = gcc_cxo_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gp,
	.clkr = अणु
		.enable_reg = 0x2d44,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gp1_src",
			.parent_names = gcc_cxo,
			.num_parents = 1,
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
		.parent_map = gcc_cxo_map,
	पूर्ण,
	.freq_tbl = clk_tbl_gp,
	.clkr = अणु
		.enable_reg = 0x2d64,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gp2_src",
			.parent_names = gcc_cxo,
			.num_parents = 1,
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
		.parent_map = gcc_cxo_pll8_map,
	पूर्ण,
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "prng_src",
			.parent_names = gcc_cxo_pll8,
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
	अणु    144000, P_CXO,   1, 1, 133 पूर्ण,
	अणु    400000, P_PLL8,  4, 1, 240 पूर्ण,
	अणु  16000000, P_PLL8,  4, 1,   6 पूर्ण,
	अणु  17070000, P_PLL8,  1, 2,  45 पूर्ण,
	अणु  20210000, P_PLL8,  1, 1,  19 पूर्ण,
	अणु  24000000, P_PLL8,  4, 1,   4 पूर्ण,
	अणु  38400000, P_PLL8,  2, 1,   5 पूर्ण,
	अणु  48000000, P_PLL8,  4, 1,   2 पूर्ण,
	अणु  64000000, P_PLL8,  3, 1,   2 पूर्ण,
	अणु  76800000, P_PLL8,  1, 1,   5 पूर्ण,
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
		.parent_map = gcc_cxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_sdc,
	.clkr = अणु
		.enable_reg = 0x282c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sdc1_src",
			.parent_names = gcc_cxo_pll8,
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
		.parent_map = gcc_cxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_sdc,
	.clkr = अणु
		.enable_reg = 0x284c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sdc2_src",
			.parent_names = gcc_cxo_pll8,
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
		.parent_map = gcc_cxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_usb,
	.clkr = अणु
		.enable_reg = 0x290c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_hs1_xcvr_src",
			.parent_names = gcc_cxo_pll8,
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
		.parent_map = gcc_cxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_usb,
	.clkr = अणु
		.enable_reg = 0x2928,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_hsic_xcvr_fs_src",
			.parent_names = gcc_cxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_RATE_GATE,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_branch usb_hsic_xcvr_fs_clk = अणु
	.halt_reg = 0x2fc8,
	.halt_bit = 9,
	.clkr = अणु
		.enable_reg = 0x2928,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_hsic_xcvr_fs_clk",
			.parent_names =
				(स्थिर अक्षर *[])अणु "usb_hsic_xcvr_fs_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl clk_tbl_usb_hs1_प्रणाली[] = अणु
	अणु 60000000, P_PLL8, 1, 5, 32 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg usb_hs1_प्रणाली_src = अणु
	.ns_reg = 0x36a4,
	.md_reg = 0x36a0,
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
		.parent_map = gcc_cxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_usb_hs1_प्रणाली,
	.clkr = अणु
		.enable_reg = 0x36a4,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_hs1_system_src",
			.parent_names = gcc_cxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_RATE_GATE,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_branch usb_hs1_प्रणाली_clk = अणु
	.halt_reg = 0x2fc8,
	.halt_bit = 4,
	.clkr = अणु
		.enable_reg = 0x36a4,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names =
				(स्थिर अक्षर *[])अणु "usb_hs1_system_src" पूर्ण,
			.num_parents = 1,
			.name = "usb_hs1_system_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl clk_tbl_usb_hsic_प्रणाली[] = अणु
	अणु 64000000, P_PLL8, 1, 1, 6 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg usb_hsic_प्रणाली_src = अणु
	.ns_reg = 0x2b58,
	.md_reg = 0x2b54,
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
		.parent_map = gcc_cxo_pll8_map,
	पूर्ण,
	.freq_tbl = clk_tbl_usb_hsic_प्रणाली,
	.clkr = अणु
		.enable_reg = 0x2b58,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_hsic_system_src",
			.parent_names = gcc_cxo_pll8,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_RATE_GATE,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_branch usb_hsic_प्रणाली_clk = अणु
	.halt_reg = 0x2fc8,
	.halt_bit = 7,
	.clkr = अणु
		.enable_reg = 0x2b58,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names =
				(स्थिर अक्षर *[])अणु "usb_hsic_system_src" पूर्ण,
			.num_parents = 1,
			.name = "usb_hsic_system_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl clk_tbl_usb_hsic_hsic[] = अणु
	अणु 48000000, P_PLL14, 1, 0, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg usb_hsic_hsic_src = अणु
	.ns_reg = 0x2b50,
	.md_reg = 0x2b4c,
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
		.parent_map = gcc_cxo_pll14_map,
	पूर्ण,
	.freq_tbl = clk_tbl_usb_hsic_hsic,
	.clkr = अणु
		.enable_reg = 0x2b50,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "usb_hsic_hsic_src",
			.parent_names = gcc_cxo_pll14,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_RATE_GATE,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_branch usb_hsic_hsic_clk = अणु
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x2b50,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = (स्थिर अक्षर *[])अणु "usb_hsic_hsic_src" पूर्ण,
			.num_parents = 1,
			.name = "usb_hsic_hsic_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch usb_hsic_hsio_cal_clk = अणु
	.halt_reg = 0x2fc8,
	.halt_bit = 8,
	.clkr = अणु
		.enable_reg = 0x2b48,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = (स्थिर अक्षर *[])अणु "cxo" पूर्ण,
			.num_parents = 1,
			.name = "usb_hsic_hsio_cal_clk",
			.ops = &clk_branch_ops,
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

अटल काष्ठा clk_branch ebi2_clk = अणु
	.hwcg_reg = 0x2664,
	.hwcg_bit = 6,
	.halt_reg = 0x2fcc,
	.halt_bit = 24,
	.clkr = अणु
		.enable_reg = 0x2664,
		.enable_mask = BIT(6) | BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "ebi2_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch ebi2_aon_clk = अणु
	.halt_reg = 0x2fcc,
	.halt_bit = 23,
	.clkr = अणु
		.enable_reg = 0x2664,
		.enable_mask = BIT(8),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "ebi2_aon_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_hw *gcc_mdm9615_hws[] = अणु
	&cxo.hw,
पूर्ण;

अटल काष्ठा clk_regmap *gcc_mdm9615_clks[] = अणु
	[PLL0] = &pll0.clkr,
	[PLL0_VOTE] = &pll0_vote,
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
	[USB_HS1_XCVR_SRC] = &usb_hs1_xcvr_src.clkr,
	[USB_HS1_XCVR_CLK] = &usb_hs1_xcvr_clk.clkr,
	[USB_HS1_SYSTEM_CLK_SRC] = &usb_hs1_प्रणाली_src.clkr,
	[USB_HS1_SYSTEM_CLK] = &usb_hs1_प्रणाली_clk.clkr,
	[USB_HSIC_XCVR_FS_SRC] = &usb_hsic_xcvr_fs_src.clkr,
	[USB_HSIC_XCVR_FS_CLK] = &usb_hsic_xcvr_fs_clk.clkr,
	[USB_HSIC_SYSTEM_CLK_SRC] = &usb_hsic_प्रणाली_src.clkr,
	[USB_HSIC_SYSTEM_CLK] = &usb_hsic_प्रणाली_clk.clkr,
	[USB_HSIC_HSIC_CLK_SRC] = &usb_hsic_hsic_src.clkr,
	[USB_HSIC_HSIC_CLK] = &usb_hsic_hsic_clk.clkr,
	[USB_HSIC_HSIO_CAL_CLK] = &usb_hsic_hsio_cal_clk.clkr,
	[CE1_CORE_CLK] = &ce1_core_clk.clkr,
	[CE1_H_CLK] = &ce1_h_clk.clkr,
	[DMA_BAM_H_CLK] = &dma_bam_h_clk.clkr,
	[GSBI1_H_CLK] = &gsbi1_h_clk.clkr,
	[GSBI2_H_CLK] = &gsbi2_h_clk.clkr,
	[GSBI3_H_CLK] = &gsbi3_h_clk.clkr,
	[GSBI4_H_CLK] = &gsbi4_h_clk.clkr,
	[GSBI5_H_CLK] = &gsbi5_h_clk.clkr,
	[USB_HS1_H_CLK] = &usb_hs1_h_clk.clkr,
	[USB_HSIC_H_CLK] = &usb_hsic_h_clk.clkr,
	[SDC1_H_CLK] = &sdc1_h_clk.clkr,
	[SDC2_H_CLK] = &sdc2_h_clk.clkr,
	[ADM0_CLK] = &adm0_clk.clkr,
	[ADM0_PBUS_CLK] = &adm0_pbus_clk.clkr,
	[PMIC_ARB0_H_CLK] = &pmic_arb0_h_clk.clkr,
	[PMIC_ARB1_H_CLK] = &pmic_arb1_h_clk.clkr,
	[PMIC_SSBI2_CLK] = &pmic_ssbi2_clk.clkr,
	[RPM_MSG_RAM_H_CLK] = &rpm_msg_ram_h_clk.clkr,
	[EBI2_CLK] = &ebi2_clk.clkr,
	[EBI2_AON_CLK] = &ebi2_aon_clk.clkr,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map gcc_mdm9615_resets[] = अणु
	[DMA_BAM_RESET] = अणु 0x25c0, 7 पूर्ण,
	[CE1_H_RESET] = अणु 0x2720, 7 पूर्ण,
	[CE1_CORE_RESET] = अणु 0x2724, 7 पूर्ण,
	[SDC1_RESET] = अणु 0x2830 पूर्ण,
	[SDC2_RESET] = अणु 0x2850 पूर्ण,
	[ADM0_C2_RESET] = अणु 0x220c, 4 पूर्ण,
	[ADM0_C1_RESET] = अणु 0x220c, 3 पूर्ण,
	[ADM0_C0_RESET] = अणु 0x220c, 2 पूर्ण,
	[ADM0_PBUS_RESET] = अणु 0x220c, 1 पूर्ण,
	[ADM0_RESET] = अणु 0x220c पूर्ण,
	[USB_HS1_RESET] = अणु 0x2910 पूर्ण,
	[USB_HSIC_RESET] = अणु 0x2934 पूर्ण,
	[GSBI1_RESET] = अणु 0x29dc पूर्ण,
	[GSBI2_RESET] = अणु 0x29fc पूर्ण,
	[GSBI3_RESET] = अणु 0x2a1c पूर्ण,
	[GSBI4_RESET] = अणु 0x2a3c पूर्ण,
	[GSBI5_RESET] = अणु 0x2a5c पूर्ण,
	[PDM_RESET] = अणु 0x2CC0, 12 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config gcc_mdm9615_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x3660,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc gcc_mdm9615_desc = अणु
	.config = &gcc_mdm9615_regmap_config,
	.clks = gcc_mdm9615_clks,
	.num_clks = ARRAY_SIZE(gcc_mdm9615_clks),
	.resets = gcc_mdm9615_resets,
	.num_resets = ARRAY_SIZE(gcc_mdm9615_resets),
	.clk_hws = gcc_mdm9615_hws,
	.num_clk_hws = ARRAY_SIZE(gcc_mdm9615_hws),
पूर्ण;

अटल स्थिर काष्ठा of_device_id gcc_mdm9615_match_table[] = अणु
	अणु .compatible = "qcom,gcc-mdm9615" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gcc_mdm9615_match_table);

अटल पूर्णांक gcc_mdm9615_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;

	regmap = qcom_cc_map(pdev, &gcc_mdm9615_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस qcom_cc_really_probe(pdev, &gcc_mdm9615_desc, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver gcc_mdm9615_driver = अणु
	.probe		= gcc_mdm9615_probe,
	.driver		= अणु
		.name	= "gcc-mdm9615",
		.of_match_table = gcc_mdm9615_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init gcc_mdm9615_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&gcc_mdm9615_driver);
पूर्ण
core_initcall(gcc_mdm9615_init);

अटल व्योम __निकास gcc_mdm9615_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&gcc_mdm9615_driver);
पूर्ण
module_निकास(gcc_mdm9615_निकास);

MODULE_DESCRIPTION("QCOM GCC MDM9615 Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:gcc-mdm9615");
