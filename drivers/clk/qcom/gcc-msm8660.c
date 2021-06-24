<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013, The Linux Foundation. All rights reserved.
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

#समावेश <dt-bindings/घड़ी/qcom,gcc-msm8660.h>
#समावेश <dt-bindings/reset/qcom,gcc-msm8660.h>

#समावेश "common.h"
#समावेश "clk-regmap.h"
#समावेश "clk-pll.h"
#समावेश "clk-rcg.h"
#समावेश "clk-branch.h"
#समावेश "reset.h"

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

क्रमागत अणु
	P_PXO,
	P_PLL8,
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
	.clkr.hw = अणु
		.init = &(काष्ठा clk_init_data)अणु
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

अटल काष्ठा clk_branch gsbi1_h_clk = अणु
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

अटल काष्ठा clk_branch sdc1_h_clk = अणु
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

अटल काष्ठा clk_branch ebi2_2x_clk = अणु
	.halt_reg = 0x2fcc,
	.halt_bit = 18,
	.clkr = अणु
		.enable_reg = 0x2660,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "ebi2_2x_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch ebi2_clk = अणु
	.halt_reg = 0x2fcc,
	.halt_bit = 19,
	.clkr = अणु
		.enable_reg = 0x2664,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "ebi2_clk",
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

अटल काष्ठा clk_branch adm1_clk = अणु
	.halt_reg = 0x2fdc,
	.halt_bit = 12,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x3080,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "adm1_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch adm1_pbus_clk = अणु
	.halt_reg = 0x2fdc,
	.halt_bit = 11,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x3080,
		.enable_mask = BIT(5),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "adm1_pbus_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch modem_ahb1_h_clk = अणु
	.halt_reg = 0x2fdc,
	.halt_bit = 8,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x3080,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "modem_ahb1_h_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch modem_ahb2_h_clk = अणु
	.halt_reg = 0x2fdc,
	.halt_bit = 7,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x3080,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "modem_ahb2_h_clk",
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

अटल काष्ठा clk_regmap *gcc_msm8660_clks[] = अणु
	[PLL8] = &pll8.clkr,
	[PLL8_VOTE] = &pll8_vote,
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
	[PMEM_CLK] = &pmem_clk.clkr,
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
	[USB_FS1_XCVR_FS_SRC] = &usb_fs1_xcvr_fs_src.clkr,
	[USB_FS1_XCVR_FS_CLK] = &usb_fs1_xcvr_fs_clk.clkr,
	[USB_FS1_SYSTEM_CLK] = &usb_fs1_प्रणाली_clk.clkr,
	[USB_FS2_XCVR_FS_SRC] = &usb_fs2_xcvr_fs_src.clkr,
	[USB_FS2_XCVR_FS_CLK] = &usb_fs2_xcvr_fs_clk.clkr,
	[USB_FS2_SYSTEM_CLK] = &usb_fs2_प्रणाली_clk.clkr,
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
	[SDC1_H_CLK] = &sdc1_h_clk.clkr,
	[SDC2_H_CLK] = &sdc2_h_clk.clkr,
	[SDC3_H_CLK] = &sdc3_h_clk.clkr,
	[SDC4_H_CLK] = &sdc4_h_clk.clkr,
	[SDC5_H_CLK] = &sdc5_h_clk.clkr,
	[EBI2_2X_CLK] = &ebi2_2x_clk.clkr,
	[EBI2_CLK] = &ebi2_clk.clkr,
	[ADM0_CLK] = &adm0_clk.clkr,
	[ADM0_PBUS_CLK] = &adm0_pbus_clk.clkr,
	[ADM1_CLK] = &adm1_clk.clkr,
	[ADM1_PBUS_CLK] = &adm1_pbus_clk.clkr,
	[MODEM_AHB1_H_CLK] = &modem_ahb1_h_clk.clkr,
	[MODEM_AHB2_H_CLK] = &modem_ahb2_h_clk.clkr,
	[PMIC_ARB0_H_CLK] = &pmic_arb0_h_clk.clkr,
	[PMIC_ARB1_H_CLK] = &pmic_arb1_h_clk.clkr,
	[PMIC_SSBI2_CLK] = &pmic_ssbi2_clk.clkr,
	[RPM_MSG_RAM_H_CLK] = &rpm_msg_ram_h_clk.clkr,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map gcc_msm8660_resets[] = अणु
	[AFAB_CORE_RESET] = अणु 0x2080, 7 पूर्ण,
	[SCSS_SYS_RESET] = अणु 0x20b4, 1 पूर्ण,
	[SCSS_SYS_POR_RESET] = अणु 0x20b4 पूर्ण,
	[AFAB_SMPSS_S_RESET] = अणु 0x20b8, 2 पूर्ण,
	[AFAB_SMPSS_M1_RESET] = अणु 0x20b8, 1 पूर्ण,
	[AFAB_SMPSS_M0_RESET] = अणु 0x20b8 पूर्ण,
	[AFAB_EBI1_S_RESET] = अणु 0x20c0, 7 पूर्ण,
	[SFAB_CORE_RESET] = अणु 0x2120, 7 पूर्ण,
	[SFAB_ADM0_M0_RESET] = अणु 0x21e0, 7 पूर्ण,
	[SFAB_ADM0_M1_RESET] = अणु 0x21e4, 7 पूर्ण,
	[SFAB_ADM0_M2_RESET] = अणु 0x21e4, 7 पूर्ण,
	[ADM0_C2_RESET] = अणु 0x220c, 4 पूर्ण,
	[ADM0_C1_RESET] = अणु 0x220c, 3 पूर्ण,
	[ADM0_C0_RESET] = अणु 0x220c, 2 पूर्ण,
	[ADM0_PBUS_RESET] = अणु 0x220c, 1 पूर्ण,
	[ADM0_RESET] = अणु 0x220c पूर्ण,
	[SFAB_ADM1_M0_RESET] = अणु 0x2220, 7 पूर्ण,
	[SFAB_ADM1_M1_RESET] = अणु 0x2224, 7 पूर्ण,
	[SFAB_ADM1_M2_RESET] = अणु 0x2228, 7 पूर्ण,
	[MMFAB_ADM1_M3_RESET] = अणु 0x2240, 7 पूर्ण,
	[ADM1_C3_RESET] = अणु 0x226c, 5 पूर्ण,
	[ADM1_C2_RESET] = अणु 0x226c, 4 पूर्ण,
	[ADM1_C1_RESET] = अणु 0x226c, 3 पूर्ण,
	[ADM1_C0_RESET] = अणु 0x226c, 2 पूर्ण,
	[ADM1_PBUS_RESET] = अणु 0x226c, 1 पूर्ण,
	[ADM1_RESET] = अणु 0x226c पूर्ण,
	[IMEM0_RESET] = अणु 0x2280, 7 पूर्ण,
	[SFAB_LPASS_Q6_RESET] = अणु 0x23a0, 7 पूर्ण,
	[SFAB_AFAB_M_RESET] = अणु 0x23e0, 7 पूर्ण,
	[AFAB_SFAB_M0_RESET] = अणु 0x2420, 7 पूर्ण,
	[AFAB_SFAB_M1_RESET] = अणु 0x2424, 7 पूर्ण,
	[DFAB_CORE_RESET] = अणु 0x24ac, 7 पूर्ण,
	[SFAB_DFAB_M_RESET] = अणु 0x2500, 7 पूर्ण,
	[DFAB_SFAB_M_RESET] = अणु 0x2520, 7 पूर्ण,
	[DFAB_SWAY0_RESET] = अणु 0x2540, 7 पूर्ण,
	[DFAB_SWAY1_RESET] = अणु 0x2544, 7 पूर्ण,
	[DFAB_ARB0_RESET] = अणु 0x2560, 7 पूर्ण,
	[DFAB_ARB1_RESET] = अणु 0x2564, 7 पूर्ण,
	[PPSS_PROC_RESET] = अणु 0x2594, 1 पूर्ण,
	[PPSS_RESET] = अणु 0x2594 पूर्ण,
	[PMEM_RESET] = अणु 0x25a0, 7 पूर्ण,
	[DMA_BAM_RESET] = अणु 0x25c0, 7 पूर्ण,
	[SIC_RESET] = अणु 0x25e0, 7 पूर्ण,
	[SPS_TIC_RESET] = अणु 0x2600, 7 पूर्ण,
	[CFBP0_RESET] = अणु 0x2650, 7 पूर्ण,
	[CFBP1_RESET] = अणु 0x2654, 7 पूर्ण,
	[CFBP2_RESET] = अणु 0x2658, 7 पूर्ण,
	[EBI2_RESET] = अणु 0x2664, 7 पूर्ण,
	[SFAB_CFPB_M_RESET] = अणु 0x2680, 7 पूर्ण,
	[CFPB_MASTER_RESET] = अणु 0x26a0, 7 पूर्ण,
	[SFAB_CFPB_S_RESET] = अणु 0x26c0, 7 पूर्ण,
	[CFPB_SPLITTER_RESET] = अणु 0x26e0, 7 पूर्ण,
	[TSIF_RESET] = अणु 0x2700, 7 पूर्ण,
	[CE1_RESET] = अणु 0x2720, 7 पूर्ण,
	[CE2_RESET] = अणु 0x2740, 7 पूर्ण,
	[SFAB_SFPB_M_RESET] = अणु 0x2780, 7 पूर्ण,
	[SFAB_SFPB_S_RESET] = अणु 0x27a0, 7 पूर्ण,
	[RPM_PROC_RESET] = अणु 0x27c0, 7 पूर्ण,
	[RPM_BUS_RESET] = अणु 0x27c4, 7 पूर्ण,
	[RPM_MSG_RAM_RESET] = अणु 0x27e0, 7 पूर्ण,
	[PMIC_ARB0_RESET] = अणु 0x2800, 7 पूर्ण,
	[PMIC_ARB1_RESET] = अणु 0x2804, 7 पूर्ण,
	[PMIC_SSBI2_RESET] = अणु 0x280c, 12 पूर्ण,
	[SDC1_RESET] = अणु 0x2830 पूर्ण,
	[SDC2_RESET] = अणु 0x2850 पूर्ण,
	[SDC3_RESET] = अणु 0x2870 पूर्ण,
	[SDC4_RESET] = अणु 0x2890 पूर्ण,
	[SDC5_RESET] = अणु 0x28b0 पूर्ण,
	[USB_HS1_RESET] = अणु 0x2910 पूर्ण,
	[USB_HS2_XCVR_RESET] = अणु 0x2934, 1 पूर्ण,
	[USB_HS2_RESET] = अणु 0x2934 पूर्ण,
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
	[SEC_CTRL_RESET] = अणु 0x2b80, 7 पूर्ण,
	[TLMM_H_RESET] = अणु 0x2ba0, 7 पूर्ण,
	[TLMM_RESET] = अणु 0x2ba4, 7 पूर्ण,
	[MARRM_PWRON_RESET] = अणु 0x2bd4, 1 पूर्ण,
	[MARM_RESET] = अणु 0x2bd4 पूर्ण,
	[MAHB1_RESET] = अणु 0x2be4, 7 पूर्ण,
	[SFAB_MSS_S_RESET] = अणु 0x2c00, 7 पूर्ण,
	[MAHB2_RESET] = अणु 0x2c20, 7 पूर्ण,
	[MODEM_SW_AHB_RESET] = अणु 0x2c48, 1 पूर्ण,
	[MODEM_RESET] = अणु 0x2c48 पूर्ण,
	[SFAB_MSS_MDM1_RESET] = अणु 0x2c4c, 1 पूर्ण,
	[SFAB_MSS_MDM0_RESET] = अणु 0x2c4c पूर्ण,
	[MSS_SLP_RESET] = अणु 0x2c60, 7 पूर्ण,
	[MSS_MARM_SAW_RESET] = अणु 0x2c68, 1 पूर्ण,
	[MSS_WDOG_RESET] = अणु 0x2c68 पूर्ण,
	[TSSC_RESET] = अणु 0x2ca0, 7 पूर्ण,
	[PDM_RESET] = अणु 0x2cc0, 12 पूर्ण,
	[SCSS_CORE0_RESET] = अणु 0x2d60, 1 पूर्ण,
	[SCSS_CORE0_POR_RESET] = अणु 0x2d60 पूर्ण,
	[SCSS_CORE1_RESET] = अणु 0x2d80, 1 पूर्ण,
	[SCSS_CORE1_POR_RESET] = अणु 0x2d80 पूर्ण,
	[MPM_RESET] = अणु 0x2da4, 1 पूर्ण,
	[EBI1_1X_DIV_RESET] = अणु 0x2dec, 9 पूर्ण,
	[EBI1_RESET] = अणु 0x2dec, 7 पूर्ण,
	[SFAB_SMPSS_S_RESET] = अणु 0x2e00, 7 पूर्ण,
	[USB_PHY0_RESET] = अणु 0x2e20 पूर्ण,
	[USB_PHY1_RESET] = अणु 0x2e40 पूर्ण,
	[PRNG_RESET] = अणु 0x2e80, 12 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config gcc_msm8660_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x363c,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc gcc_msm8660_desc = अणु
	.config = &gcc_msm8660_regmap_config,
	.clks = gcc_msm8660_clks,
	.num_clks = ARRAY_SIZE(gcc_msm8660_clks),
	.resets = gcc_msm8660_resets,
	.num_resets = ARRAY_SIZE(gcc_msm8660_resets),
पूर्ण;

अटल स्थिर काष्ठा of_device_id gcc_msm8660_match_table[] = अणु
	अणु .compatible = "qcom,gcc-msm8660" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gcc_msm8660_match_table);

अटल पूर्णांक gcc_msm8660_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &pdev->dev;

	ret = qcom_cc_रेजिस्टर_board_clk(dev, "cxo_board", "cxo", 19200000);
	अगर (ret)
		वापस ret;

	ret = qcom_cc_रेजिस्टर_board_clk(dev, "pxo_board", "pxo", 27000000);
	अगर (ret)
		वापस ret;

	वापस qcom_cc_probe(pdev, &gcc_msm8660_desc);
पूर्ण

अटल काष्ठा platक्रमm_driver gcc_msm8660_driver = अणु
	.probe		= gcc_msm8660_probe,
	.driver		= अणु
		.name	= "gcc-msm8660",
		.of_match_table = gcc_msm8660_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init gcc_msm8660_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&gcc_msm8660_driver);
पूर्ण
core_initcall(gcc_msm8660_init);

अटल व्योम __निकास gcc_msm8660_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&gcc_msm8660_driver);
पूर्ण
module_निकास(gcc_msm8660_निकास);

MODULE_DESCRIPTION("GCC MSM 8660 Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:gcc-msm8660");
