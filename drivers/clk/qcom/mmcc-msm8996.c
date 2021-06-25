<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*x
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
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

#समावेश <dt-bindings/घड़ी/qcom,mmcc-msm8996.h>

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
	P_MMPLL0,
	P_GPLL0,
	P_GPLL0_DIV,
	P_MMPLL1,
	P_MMPLL9,
	P_MMPLL2,
	P_MMPLL8,
	P_MMPLL3,
	P_DSI0PLL,
	P_DSI1PLL,
	P_MMPLL5,
	P_HDMIPLL,
	P_DSI0PLL_BYTE,
	P_DSI1PLL_BYTE,
	P_MMPLL4,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_hdmi_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_HDMIPLL, 1 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर mmss_xo_hdmi[] = अणु
	"xo",
	"hdmipll"
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_dsi0pll_dsi1pll_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_DSI0PLL, 1 पूर्ण,
	अणु P_DSI1PLL, 2 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर mmss_xo_dsi0pll_dsi1pll[] = अणु
	"xo",
	"dsi0pll",
	"dsi1pll"
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर mmss_xo_gpll0_gpll0_भाग[] = अणु
	"xo",
	"gpll0",
	"gpll0_div"
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_dsibyte_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_DSI0PLL_BYTE, 1 पूर्ण,
	अणु P_DSI1PLL_BYTE, 2 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर mmss_xo_dsibyte[] = अणु
	"xo",
	"dsi0pllbyte",
	"dsi1pllbyte"
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_mmpll0_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0, 1 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर mmss_xo_mmpll0_gpll0_gpll0_भाग[] = अणु
	"xo",
	"mmpll0",
	"gpll0",
	"gpll0_div"
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_mmpll0_mmpll1_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0, 1 पूर्ण,
	अणु P_MMPLL1, 2 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर mmss_xo_mmpll0_mmpll1_gpll0_gpll0_भाग[] = अणु
	"xo",
	"mmpll0",
	"mmpll1",
	"gpll0",
	"gpll0_div"
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_mmpll0_mmpll3_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0, 1 पूर्ण,
	अणु P_MMPLL3, 3 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर mmss_xo_mmpll0_mmpll3_gpll0_gpll0_भाग[] = अणु
	"xo",
	"mmpll0",
	"mmpll3",
	"gpll0",
	"gpll0_div"
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_mmpll0_mmpll5_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0, 1 पूर्ण,
	अणु P_MMPLL5, 2 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर mmss_xo_mmpll0_mmpll5_gpll0_gpll0_भाग[] = अणु
	"xo",
	"mmpll0",
	"mmpll5",
	"gpll0",
	"gpll0_div"
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_mmpll0_mmpll4_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0, 1 पूर्ण,
	अणु P_MMPLL4, 3 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर mmss_xo_mmpll0_mmpll4_gpll0_gpll0_भाग[] = अणु
	"xo",
	"mmpll0",
	"mmpll4",
	"gpll0",
	"gpll0_div"
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_mmpll0_mmpll9_mmpll2_mmpll8_gpll0_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0, 1 पूर्ण,
	अणु P_MMPLL9, 2 पूर्ण,
	अणु P_MMPLL2, 3 पूर्ण,
	अणु P_MMPLL8, 4 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर mmss_xo_mmpll0_mmpll9_mmpll2_mmpll8_gpll0[] = अणु
	"xo",
	"mmpll0",
	"mmpll9",
	"mmpll2",
	"mmpll8",
	"gpll0"
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_mmpll0_mmpll9_mmpll2_mmpll8_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0, 1 पूर्ण,
	अणु P_MMPLL9, 2 पूर्ण,
	अणु P_MMPLL2, 3 पूर्ण,
	अणु P_MMPLL8, 4 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर mmss_xo_mmpll0_mmpll9_mmpll2_mmpll8_gpll0_gpll0_भाग[] = अणु
	"xo",
	"mmpll0",
	"mmpll9",
	"mmpll2",
	"mmpll8",
	"gpll0",
	"gpll0_div"
पूर्ण;

अटल स्थिर काष्ठा parent_map mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_MMPLL0, 1 पूर्ण,
	अणु P_MMPLL1, 2 पूर्ण,
	अणु P_MMPLL4, 3 पूर्ण,
	अणु P_MMPLL3, 4 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
	अणु P_GPLL0_DIV, 6 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग[] = अणु
	"xo",
	"mmpll0",
	"mmpll1",
	"mmpll4",
	"mmpll3",
	"gpll0",
	"gpll0_div"
पूर्ण;

अटल काष्ठा clk_fixed_factor gpll0_भाग = अणु
	.mult = 1,
	.भाग = 2,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll0_div",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll0" पूर्ण,
		.num_parents = 1,
		.ops = &clk_fixed_factor_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा pll_vco mmpll_p_vco[] = अणु
	अणु 250000000, 500000000, 3 पूर्ण,
	अणु 500000000, 1000000000, 2 पूर्ण,
	अणु 1000000000, 1500000000, 1 पूर्ण,
	अणु 1500000000, 2000000000, 0 पूर्ण,
पूर्ण;

अटल काष्ठा pll_vco mmpll_gfx_vco[] = अणु
	अणु 400000000, 1000000000, 2 पूर्ण,
	अणु 1000000000, 1500000000, 1 पूर्ण,
	अणु 1500000000, 2000000000, 0 पूर्ण,
पूर्ण;

अटल काष्ठा pll_vco mmpll_t_vco[] = अणु
	अणु 500000000, 1500000000, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll0_early = अणु
	.offset = 0x0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.vco_table = mmpll_p_vco,
	.num_vco = ARRAY_SIZE(mmpll_p_vco),
	.clkr = अणु
		.enable_reg = 0x100,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmpll0_early",
			.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग mmpll0 = अणु
	.offset = 0x0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.width = 4,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll0",
		.parent_names = (स्थिर अक्षर *[])अणु "mmpll0_early" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll1_early = अणु
	.offset = 0x30,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.vco_table = mmpll_p_vco,
	.num_vco = ARRAY_SIZE(mmpll_p_vco),
	.clkr = अणु
		.enable_reg = 0x100,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmpll1_early",
			.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_ops,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग mmpll1 = अणु
	.offset = 0x30,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.width = 4,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll1",
		.parent_names = (स्थिर अक्षर *[])अणु "mmpll1_early" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll2_early = अणु
	.offset = 0x4100,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.vco_table = mmpll_gfx_vco,
	.num_vco = ARRAY_SIZE(mmpll_gfx_vco),
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll2_early",
		.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग mmpll2 = अणु
	.offset = 0x4100,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.width = 4,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll2",
		.parent_names = (स्थिर अक्षर *[])अणु "mmpll2_early" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll3_early = अणु
	.offset = 0x60,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.vco_table = mmpll_p_vco,
	.num_vco = ARRAY_SIZE(mmpll_p_vco),
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll3_early",
		.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग mmpll3 = अणु
	.offset = 0x60,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.width = 4,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll3",
		.parent_names = (स्थिर अक्षर *[])अणु "mmpll3_early" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll4_early = अणु
	.offset = 0x90,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.vco_table = mmpll_t_vco,
	.num_vco = ARRAY_SIZE(mmpll_t_vco),
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll4_early",
		.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग mmpll4 = अणु
	.offset = 0x90,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.width = 2,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll4",
		.parent_names = (स्थिर अक्षर *[])अणु "mmpll4_early" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll5_early = अणु
	.offset = 0xc0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.vco_table = mmpll_p_vco,
	.num_vco = ARRAY_SIZE(mmpll_p_vco),
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll5_early",
		.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग mmpll5 = अणु
	.offset = 0xc0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.width = 4,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll5",
		.parent_names = (स्थिर अक्षर *[])अणु "mmpll5_early" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll8_early = अणु
	.offset = 0x4130,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.vco_table = mmpll_gfx_vco,
	.num_vco = ARRAY_SIZE(mmpll_gfx_vco),
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll8_early",
		.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग mmpll8 = अणु
	.offset = 0x4130,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.width = 4,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll8",
		.parent_names = (स्थिर अक्षर *[])अणु "mmpll8_early" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll mmpll9_early = अणु
	.offset = 0x4200,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.vco_table = mmpll_t_vco,
	.num_vco = ARRAY_SIZE(mmpll_t_vco),
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll9_early",
		.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग mmpll9 = अणु
	.offset = 0x4200,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.width = 2,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mmpll9",
		.parent_names = (स्थिर अक्षर *[])अणु "mmpll9_early" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_ahb_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(40000000, P_GPLL0_DIV, 7.5, 0, 0),
	F(80000000, P_MMPLL0, 10, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 ahb_clk_src = अणु
	.cmd_rcgr = 0x5000,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_ahb_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ahb_clk_src",
		.parent_names = mmss_xo_mmpll0_gpll0_gpll0_भाग,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_axi_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(75000000, P_GPLL0_DIV, 4, 0, 0),
	F(100000000, P_GPLL0, 6, 0, 0),
	F(171430000, P_GPLL0, 3.5, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	F(320000000, P_MMPLL0, 2.5, 0, 0),
	F(400000000, P_MMPLL0, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 axi_clk_src = अणु
	.cmd_rcgr = 0x5040,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll1_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_axi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "axi_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll1_gpll0_gpll0_भाग,
		.num_parents = 5,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 maxi_clk_src = अणु
	.cmd_rcgr = 0x5090,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll1_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_axi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "maxi_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll1_gpll0_gpll0_भाग,
		.num_parents = 5,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2_gfx3d gfx3d_clk_src = अणु
	.rcg = अणु
		.cmd_rcgr = 0x4000,
		.hid_width = 5,
		.parent_map = mmss_xo_mmpll0_mmpll9_mmpll2_mmpll8_gpll0_map,
		.clkr.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gfx3d_clk_src",
			.parent_names = mmss_xo_mmpll0_mmpll9_mmpll2_mmpll8_gpll0,
			.num_parents = 6,
			.ops = &clk_gfx3d_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
	.hws = (काष्ठा clk_hw*[]) अणु
		&mmpll9.clkr.hw,
		&mmpll2.clkr.hw,
		&mmpll8.clkr.hw
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_rbbmसमयr_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 rbbmसमयr_clk_src = अणु
	.cmd_rcgr = 0x4090,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_rbbmसमयr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "rbbmtimer_clk_src",
		.parent_names = mmss_xo_mmpll0_gpll0_gpll0_भाग,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 isense_clk_src = अणु
	.cmd_rcgr = 0x4010,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll9_mmpll2_mmpll8_gpll0_gpll0_भाग_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "isense_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll9_mmpll2_mmpll8_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_rbcpr_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(50000000, P_GPLL0, 12, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 rbcpr_clk_src = अणु
	.cmd_rcgr = 0x4060,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_rbcpr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "rbcpr_clk_src",
		.parent_names = mmss_xo_mmpll0_gpll0_gpll0_भाग,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_video_core_clk_src[] = अणु
	F(75000000, P_GPLL0_DIV, 4, 0, 0),
	F(150000000, P_GPLL0, 4, 0, 0),
	F(346666667, P_MMPLL3, 3, 0, 0),
	F(520000000, P_MMPLL3, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 video_core_clk_src = अणु
	.cmd_rcgr = 0x1000,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll3_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_video_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "video_core_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll3_gpll0_gpll0_भाग,
		.num_parents = 5,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 video_subcore0_clk_src = अणु
	.cmd_rcgr = 0x1060,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll3_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_video_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "video_subcore0_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll3_gpll0_gpll0_भाग,
		.num_parents = 5,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 video_subcore1_clk_src = अणु
	.cmd_rcgr = 0x1080,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll3_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_video_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "video_subcore1_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll3_gpll0_gpll0_भाग,
		.num_parents = 5,
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
		.parent_names = mmss_xo_dsi0pll_dsi1pll,
		.num_parents = 3,
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
		.parent_names = mmss_xo_dsi0pll_dsi1pll,
		.num_parents = 3,
		.ops = &clk_pixel_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_mdp_clk_src[] = अणु
	F(85714286, P_GPLL0, 7, 0, 0),
	F(100000000, P_GPLL0, 6, 0, 0),
	F(150000000, P_GPLL0, 4, 0, 0),
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
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll5_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_mdp_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mdp_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll5_gpll0_gpll0_भाग,
		.num_parents = 5,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl extpclk_freq_tbl[] = अणु
	अणु .src = P_HDMIPLL पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 extpclk_clk_src = अणु
	.cmd_rcgr = 0x2060,
	.hid_width = 5,
	.parent_map = mmss_xo_hdmi_map,
	.freq_tbl = extpclk_freq_tbl,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "extpclk_clk_src",
		.parent_names = mmss_xo_hdmi,
		.num_parents = 2,
		.ops = &clk_byte_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_mdss_vsync_clk[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 vsync_clk_src = अणु
	.cmd_rcgr = 0x2080,
	.hid_width = 5,
	.parent_map = mmss_xo_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_mdss_vsync_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vsync_clk_src",
		.parent_names = mmss_xo_gpll0_gpll0_भाग,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_mdss_hdmi_clk[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 hdmi_clk_src = अणु
	.cmd_rcgr = 0x2100,
	.hid_width = 5,
	.parent_map = mmss_xo_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_mdss_hdmi_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "hdmi_clk_src",
		.parent_names = mmss_xo_gpll0_gpll0_भाग,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 byte0_clk_src = अणु
	.cmd_rcgr = 0x2120,
	.hid_width = 5,
	.parent_map = mmss_xo_dsibyte_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "byte0_clk_src",
		.parent_names = mmss_xo_dsibyte,
		.num_parents = 3,
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
		.parent_names = mmss_xo_dsibyte,
		.num_parents = 3,
		.ops = &clk_byte2_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_mdss_esc0_1_clk[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 esc0_clk_src = अणु
	.cmd_rcgr = 0x2160,
	.hid_width = 5,
	.parent_map = mmss_xo_dsibyte_map,
	.freq_tbl = ftbl_mdss_esc0_1_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "esc0_clk_src",
		.parent_names = mmss_xo_dsibyte,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 esc1_clk_src = अणु
	.cmd_rcgr = 0x2180,
	.hid_width = 5,
	.parent_map = mmss_xo_dsibyte_map,
	.freq_tbl = ftbl_mdss_esc0_1_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "esc1_clk_src",
		.parent_names = mmss_xo_dsibyte,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_camss_gp0_clk_src[] = अणु
	F(10000, P_XO, 16, 1, 120),
	F(24000, P_XO, 16, 1, 50),
	F(6000000, P_GPLL0_DIV, 10, 1, 5),
	F(12000000, P_GPLL0_DIV, 1, 1, 25),
	F(13000000, P_GPLL0_DIV, 2, 13, 150),
	F(24000000, P_GPLL0_DIV, 1, 2, 25),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 camss_gp0_clk_src = अणु
	.cmd_rcgr = 0x3420,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_camss_gp0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "camss_gp0_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll4_gpll0_gpll0_भाग,
		.num_parents = 5,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 camss_gp1_clk_src = अणु
	.cmd_rcgr = 0x3450,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_camss_gp0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "camss_gp1_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll4_gpll0_gpll0_भाग,
		.num_parents = 5,
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
	F(24000000, P_GPLL0_DIV, 1, 2, 25),
	F(33333333, P_GPLL0_DIV, 1, 1, 9),
	F(48000000, P_GPLL0, 1, 2, 25),
	F(66666667, P_GPLL0, 1, 1, 9),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 mclk0_clk_src = अणु
	.cmd_rcgr = 0x3360,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_mclk0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mclk0_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll4_gpll0_gpll0_भाग,
		.num_parents = 5,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 mclk1_clk_src = अणु
	.cmd_rcgr = 0x3390,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_mclk0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mclk1_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll4_gpll0_gpll0_भाग,
		.num_parents = 5,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 mclk2_clk_src = अणु
	.cmd_rcgr = 0x33c0,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_mclk0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mclk2_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll4_gpll0_gpll0_भाग,
		.num_parents = 5,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 mclk3_clk_src = अणु
	.cmd_rcgr = 0x33f0,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_mclk0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mclk3_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll4_gpll0_gpll0_भाग,
		.num_parents = 5,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cci_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(37500000, P_GPLL0, 16, 0, 0),
	F(50000000, P_GPLL0, 12, 0, 0),
	F(100000000, P_GPLL0, 6, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cci_clk_src = अणु
	.cmd_rcgr = 0x3300,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_cci_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cci_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll4_gpll0_gpll0_भाग,
		.num_parents = 5,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_csi0phyसमयr_clk_src[] = अणु
	F(100000000, P_GPLL0_DIV, 3, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	F(266666667, P_MMPLL0, 3, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 csi0phyसमयr_clk_src = अणु
	.cmd_rcgr = 0x3000,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csi0phyसमयr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi0phytimer_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 csi1phyसमयr_clk_src = अणु
	.cmd_rcgr = 0x3030,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csi0phyसमयr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi1phytimer_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 csi2phyसमयr_clk_src = अणु
	.cmd_rcgr = 0x3060,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csi0phyसमयr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi2phytimer_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_csiphy0_3p_clk_src[] = अणु
	F(100000000, P_GPLL0_DIV, 3, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	F(320000000, P_MMPLL4, 3, 0, 0),
	F(384000000, P_MMPLL4, 2.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 csiphy0_3p_clk_src = अणु
	.cmd_rcgr = 0x3240,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csiphy0_3p_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csiphy0_3p_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 csiphy1_3p_clk_src = अणु
	.cmd_rcgr = 0x3260,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csiphy0_3p_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csiphy1_3p_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 csiphy2_3p_clk_src = अणु
	.cmd_rcgr = 0x3280,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csiphy0_3p_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csiphy2_3p_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_jpeg0_clk_src[] = अणु
	F(75000000, P_GPLL0_DIV, 4, 0, 0),
	F(150000000, P_GPLL0, 4, 0, 0),
	F(228571429, P_MMPLL0, 3.5, 0, 0),
	F(266666667, P_MMPLL0, 3, 0, 0),
	F(320000000, P_MMPLL0, 2.5, 0, 0),
	F(480000000, P_MMPLL4, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 jpeg0_clk_src = अणु
	.cmd_rcgr = 0x3500,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_jpeg0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "jpeg0_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_jpeg2_clk_src[] = अणु
	F(75000000, P_GPLL0_DIV, 4, 0, 0),
	F(150000000, P_GPLL0, 4, 0, 0),
	F(228571429, P_MMPLL0, 3.5, 0, 0),
	F(266666667, P_MMPLL0, 3, 0, 0),
	F(320000000, P_MMPLL0, 2.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 jpeg2_clk_src = अणु
	.cmd_rcgr = 0x3540,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_jpeg2_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "jpeg2_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 jpeg_dma_clk_src = अणु
	.cmd_rcgr = 0x3560,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_jpeg0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "jpeg_dma_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_vfe0_clk_src[] = अणु
	F(75000000, P_GPLL0_DIV, 4, 0, 0),
	F(100000000, P_GPLL0_DIV, 3, 0, 0),
	F(300000000, P_GPLL0, 2, 0, 0),
	F(320000000, P_MMPLL0, 2.5, 0, 0),
	F(480000000, P_MMPLL4, 2, 0, 0),
	F(600000000, P_GPLL0, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 vfe0_clk_src = अणु
	.cmd_rcgr = 0x3600,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_vfe0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vfe0_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 vfe1_clk_src = अणु
	.cmd_rcgr = 0x3620,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_vfe0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vfe1_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cpp_clk_src[] = अणु
	F(100000000, P_GPLL0_DIV, 3, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	F(320000000, P_MMPLL0, 2.5, 0, 0),
	F(480000000, P_MMPLL4, 2, 0, 0),
	F(640000000, P_MMPLL4, 1.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cpp_clk_src = अणु
	.cmd_rcgr = 0x3640,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_cpp_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpp_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_csi0_clk_src[] = अणु
	F(100000000, P_GPLL0_DIV, 3, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	F(266666667, P_MMPLL0, 3, 0, 0),
	F(480000000, P_MMPLL4, 2, 0, 0),
	F(600000000, P_GPLL0, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 csi0_clk_src = अणु
	.cmd_rcgr = 0x3090,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csi0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi0_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 csi1_clk_src = अणु
	.cmd_rcgr = 0x3100,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csi0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi1_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 csi2_clk_src = अणु
	.cmd_rcgr = 0x3160,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csi0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi2_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 csi3_clk_src = अणु
	.cmd_rcgr = 0x31c0,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_csi0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi3_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll1_mmpll4_mmpll3_gpll0_gpll0_भाग,
		.num_parents = 7,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_fd_core_clk_src[] = अणु
	F(100000000, P_GPLL0_DIV, 3, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	F(400000000, P_MMPLL0, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 fd_core_clk_src = अणु
	.cmd_rcgr = 0x3b00,
	.hid_width = 5,
	.parent_map = mmss_xo_mmpll0_mmpll4_gpll0_gpll0_भाग_map,
	.freq_tbl = ftbl_fd_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fd_core_clk_src",
		.parent_names = mmss_xo_mmpll0_mmpll4_gpll0_gpll0_भाग,
		.num_parents = 5,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mmss_mmagic_ahb_clk = अणु
	.halt_reg = 0x5024,
	.clkr = अणु
		.enable_reg = 0x5024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmss_mmagic_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT | CLK_IS_CRITICAL,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mmss_mmagic_cfg_ahb_clk = अणु
	.halt_reg = 0x5054,
	.clkr = अणु
		.enable_reg = 0x5054,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmss_mmagic_cfg_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT | CLK_IS_CRITICAL,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mmss_misc_ahb_clk = अणु
	.halt_reg = 0x5018,
	.clkr = अणु
		.enable_reg = 0x5018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmss_misc_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mmss_misc_cxo_clk = अणु
	.halt_reg = 0x5014,
	.clkr = अणु
		.enable_reg = 0x5014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmss_misc_cxo_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mmss_mmagic_maxi_clk = अणु
	.halt_reg = 0x5074,
	.clkr = अणु
		.enable_reg = 0x5074,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmss_mmagic_maxi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "maxi_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mmagic_camss_axi_clk = अणु
	.halt_reg = 0x3c44,
	.clkr = अणु
		.enable_reg = 0x3c44,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmagic_camss_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "axi_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT | CLK_IS_CRITICAL,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mmagic_camss_noc_cfg_ahb_clk = अणु
	.halt_reg = 0x3c48,
	.clkr = अणु
		.enable_reg = 0x3c48,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmagic_camss_noc_cfg_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gcc_mmss_noc_cfg_ahb_clk" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT | CLK_IS_CRITICAL,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch smmu_vfe_ahb_clk = अणु
	.halt_reg = 0x3c04,
	.clkr = अणु
		.enable_reg = 0x3c04,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "smmu_vfe_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch smmu_vfe_axi_clk = अणु
	.halt_reg = 0x3c08,
	.clkr = अणु
		.enable_reg = 0x3c08,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "smmu_vfe_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "axi_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch smmu_cpp_ahb_clk = अणु
	.halt_reg = 0x3c14,
	.clkr = अणु
		.enable_reg = 0x3c14,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "smmu_cpp_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch smmu_cpp_axi_clk = अणु
	.halt_reg = 0x3c18,
	.clkr = अणु
		.enable_reg = 0x3c18,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "smmu_cpp_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "axi_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch smmu_jpeg_ahb_clk = अणु
	.halt_reg = 0x3c24,
	.clkr = अणु
		.enable_reg = 0x3c24,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "smmu_jpeg_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch smmu_jpeg_axi_clk = अणु
	.halt_reg = 0x3c28,
	.clkr = अणु
		.enable_reg = 0x3c28,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "smmu_jpeg_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "axi_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mmagic_mdss_axi_clk = अणु
	.halt_reg = 0x2474,
	.clkr = अणु
		.enable_reg = 0x2474,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmagic_mdss_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "axi_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT | CLK_IS_CRITICAL,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mmagic_mdss_noc_cfg_ahb_clk = अणु
	.halt_reg = 0x2478,
	.clkr = अणु
		.enable_reg = 0x2478,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmagic_mdss_noc_cfg_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gcc_mmss_noc_cfg_ahb_clk" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT | CLK_IS_CRITICAL,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch smmu_rot_ahb_clk = अणु
	.halt_reg = 0x2444,
	.clkr = अणु
		.enable_reg = 0x2444,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "smmu_rot_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch smmu_rot_axi_clk = अणु
	.halt_reg = 0x2448,
	.clkr = अणु
		.enable_reg = 0x2448,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "smmu_rot_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "axi_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch smmu_mdp_ahb_clk = अणु
	.halt_reg = 0x2454,
	.clkr = अणु
		.enable_reg = 0x2454,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "smmu_mdp_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch smmu_mdp_axi_clk = अणु
	.halt_reg = 0x2458,
	.clkr = अणु
		.enable_reg = 0x2458,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "smmu_mdp_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "axi_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mmagic_video_axi_clk = अणु
	.halt_reg = 0x1194,
	.clkr = अणु
		.enable_reg = 0x1194,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmagic_video_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "axi_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT | CLK_IS_CRITICAL,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mmagic_video_noc_cfg_ahb_clk = अणु
	.halt_reg = 0x1198,
	.clkr = अणु
		.enable_reg = 0x1198,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmagic_video_noc_cfg_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gcc_mmss_noc_cfg_ahb_clk" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT | CLK_IS_CRITICAL,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch smmu_video_ahb_clk = अणु
	.halt_reg = 0x1174,
	.clkr = अणु
		.enable_reg = 0x1174,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "smmu_video_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch smmu_video_axi_clk = अणु
	.halt_reg = 0x1178,
	.clkr = अणु
		.enable_reg = 0x1178,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "smmu_video_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "axi_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mmagic_bimc_noc_cfg_ahb_clk = अणु
	.halt_reg = 0x5298,
	.clkr = अणु
		.enable_reg = 0x5298,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmagic_bimc_noc_cfg_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gcc_mmss_noc_cfg_ahb_clk" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gpu_gx_gfx3d_clk = अणु
	.halt_reg = 0x4028,
	.clkr = अणु
		.enable_reg = 0x4028,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpu_gx_gfx3d_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gfx3d_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gpu_gx_rbbmसमयr_clk = अणु
	.halt_reg = 0x40b0,
	.clkr = अणु
		.enable_reg = 0x40b0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpu_gx_rbbmtimer_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "rbbmtimer_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gpu_ahb_clk = अणु
	.halt_reg = 0x403c,
	.clkr = अणु
		.enable_reg = 0x403c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpu_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gpu_aon_isense_clk = अणु
	.halt_reg = 0x4044,
	.clkr = अणु
		.enable_reg = 0x4044,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpu_aon_isense_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "isense_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch vmem_maxi_clk = अणु
	.halt_reg = 0x1204,
	.clkr = अणु
		.enable_reg = 0x1204,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vmem_maxi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "maxi_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch vmem_ahb_clk = अणु
	.halt_reg = 0x1208,
	.clkr = अणु
		.enable_reg = 0x1208,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vmem_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mmss_rbcpr_clk = अणु
	.halt_reg = 0x4084,
	.clkr = अणु
		.enable_reg = 0x4084,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmss_rbcpr_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "rbcpr_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mmss_rbcpr_ahb_clk = अणु
	.halt_reg = 0x4088,
	.clkr = अणु
		.enable_reg = 0x4088,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmss_rbcpr_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "video_core_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "axi_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
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
			.parent_names = (स्थिर अक्षर *[])अणु "maxi_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch video_ahb_clk = अणु
	.halt_reg = 0x1030,
	.clkr = अणु
		.enable_reg = 0x1030,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "video_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "video_subcore0_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "video_subcore1_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_ahb_clk = अणु
	.halt_reg = 0x2308,
	.clkr = अणु
		.enable_reg = 0x2308,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdss_hdmi_ahb_clk = अणु
	.halt_reg = 0x230c,
	.clkr = अणु
		.enable_reg = 0x230c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdss_hdmi_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "axi_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
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
			.parent_names = (स्थिर अक्षर *[])अणु "pclk0_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "pclk1_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "mdp_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "extpclk_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "vsync_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "hdmi_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "byte0_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "byte1_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "esc0_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "esc1_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_gp0_clk = अणु
	.halt_reg = 0x3444,
	.clkr = अणु
		.enable_reg = 0x3444,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_gp0_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "camss_gp0_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_gp1_clk = अणु
	.halt_reg = 0x3474,
	.clkr = अणु
		.enable_reg = 0x3474,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_gp1_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "camss_gp1_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "mclk0_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "mclk1_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "mclk2_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "mclk3_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "cci_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "csi0phytimer_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "csi1phytimer_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "csi2phytimer_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csiphy0_3p_clk = अणु
	.halt_reg = 0x3234,
	.clkr = अणु
		.enable_reg = 0x3234,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csiphy0_3p_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "csiphy0_3p_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csiphy1_3p_clk = अणु
	.halt_reg = 0x3254,
	.clkr = अणु
		.enable_reg = 0x3254,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csiphy1_3p_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "csiphy1_3p_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csiphy2_3p_clk = अणु
	.halt_reg = 0x3274,
	.clkr = अणु
		.enable_reg = 0x3274,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csiphy2_3p_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "csiphy2_3p_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "jpeg0_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_jpeg2_clk = अणु
	.halt_reg = 0x35b0,
	.clkr = अणु
		.enable_reg = 0x35b0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_jpeg2_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "jpeg2_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_jpeg_dma_clk = अणु
	.halt_reg = 0x35c0,
	.clkr = अणु
		.enable_reg = 0x35c0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_jpeg_dma_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "jpeg_dma_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "axi_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_vfe_ahb_clk = अणु
	.halt_reg = 0x36b8,
	.clkr = अणु
		.enable_reg = 0x36b8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_vfe_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_vfe_axi_clk = अणु
	.halt_reg = 0x36bc,
	.clkr = अणु
		.enable_reg = 0x36bc,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_vfe_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "axi_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "vfe0_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "vfe0_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
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
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "vfe1_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "vfe1_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "vfe0_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "vfe1_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
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
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
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
			.parent_names = (स्थिर अक्षर *[])अणु "axi_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "cpp_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "csi0_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi0phy_clk = अणु
	.halt_reg = 0x30c4,
	.clkr = अणु
		.enable_reg = 0x30c4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi0phy_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "csi0_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "csi0_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "csi0_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "csi1_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi1phy_clk = अणु
	.halt_reg = 0x3134,
	.clkr = अणु
		.enable_reg = 0x3134,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi1phy_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "csi1_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "csi1_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "csi1_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "csi2_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi2phy_clk = अणु
	.halt_reg = 0x3194,
	.clkr = अणु
		.enable_reg = 0x3194,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi2phy_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "csi2_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "csi2_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "csi2_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "csi3_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camss_csi3phy_clk = अणु
	.halt_reg = 0x31f4,
	.clkr = अणु
		.enable_reg = 0x31f4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camss_csi3phy_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "csi3_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "csi3_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "csi3_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "fd_core_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
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
			.parent_names = (स्थिर अक्षर *[])अणु "fd_core_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch fd_ahb_clk = अणु
	.halt_reg = 0x3ba74,
	.clkr = अणु
		.enable_reg = 0x3ba74,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "fd_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "ahb_clk_src" पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_hw *mmcc_msm8996_hws[] = अणु
	&gpll0_भाग.hw,
पूर्ण;

अटल काष्ठा gdsc mmagic_bimc_gdsc = अणु
	.gdscr = 0x529c,
	.pd = अणु
		.name = "mmagic_bimc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = ALWAYS_ON,
पूर्ण;

अटल काष्ठा gdsc mmagic_video_gdsc = अणु
	.gdscr = 0x119c,
	.gds_hw_ctrl = 0x120c,
	.pd = अणु
		.name = "mmagic_video",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE | ALWAYS_ON,
पूर्ण;

अटल काष्ठा gdsc mmagic_mdss_gdsc = अणु
	.gdscr = 0x247c,
	.gds_hw_ctrl = 0x2480,
	.pd = अणु
		.name = "mmagic_mdss",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE | ALWAYS_ON,
पूर्ण;

अटल काष्ठा gdsc mmagic_camss_gdsc = अणु
	.gdscr = 0x3c4c,
	.gds_hw_ctrl = 0x3c50,
	.pd = अणु
		.name = "mmagic_camss",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE | ALWAYS_ON,
पूर्ण;

अटल काष्ठा gdsc venus_gdsc = अणु
	.gdscr = 0x1024,
	.cxcs = (अचिन्हित पूर्णांक [])अणु 0x1028, 0x1034, 0x1038 पूर्ण,
	.cxc_count = 3,
	.pd = अणु
		.name = "venus",
	पूर्ण,
	.parent = &mmagic_video_gdsc.pd,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc venus_core0_gdsc = अणु
	.gdscr = 0x1040,
	.cxcs = (अचिन्हित पूर्णांक [])अणु 0x1048 पूर्ण,
	.cxc_count = 1,
	.pd = अणु
		.name = "venus_core0",
	पूर्ण,
	.parent = &venus_gdsc.pd,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = HW_CTRL,
पूर्ण;

अटल काष्ठा gdsc venus_core1_gdsc = अणु
	.gdscr = 0x1044,
	.cxcs = (अचिन्हित पूर्णांक [])अणु 0x104c पूर्ण,
	.cxc_count = 1,
	.pd = अणु
		.name = "venus_core1",
	पूर्ण,
	.parent = &venus_gdsc.pd,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = HW_CTRL,
पूर्ण;

अटल काष्ठा gdsc camss_gdsc = अणु
	.gdscr = 0x34a0,
	.cxcs = (अचिन्हित पूर्णांक [])अणु 0x36bc, 0x36c4 पूर्ण,
	.cxc_count = 2,
	.pd = अणु
		.name = "camss",
	पूर्ण,
	.parent = &mmagic_camss_gdsc.pd,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc vfe0_gdsc = अणु
	.gdscr = 0x3664,
	.cxcs = (अचिन्हित पूर्णांक [])अणु 0x36a8 पूर्ण,
	.cxc_count = 1,
	.pd = अणु
		.name = "vfe0",
	पूर्ण,
	.parent = &camss_gdsc.pd,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc vfe1_gdsc = अणु
	.gdscr = 0x3674,
	.cxcs = (अचिन्हित पूर्णांक [])अणु 0x36ac पूर्ण,
	.cxc_count = 1,
	.pd = अणु
		.name = "vfe1",
	पूर्ण,
	.parent = &camss_gdsc.pd,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc jpeg_gdsc = अणु
	.gdscr = 0x35a4,
	.cxcs = (अचिन्हित पूर्णांक [])अणु 0x35a8, 0x35b0, 0x35c0, 0x35b8 पूर्ण,
	.cxc_count = 4,
	.pd = अणु
		.name = "jpeg",
	पूर्ण,
	.parent = &camss_gdsc.pd,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc cpp_gdsc = अणु
	.gdscr = 0x36d4,
	.cxcs = (अचिन्हित पूर्णांक [])अणु 0x36b0 पूर्ण,
	.cxc_count = 1,
	.pd = अणु
		.name = "cpp",
	पूर्ण,
	.parent = &camss_gdsc.pd,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc fd_gdsc = अणु
	.gdscr = 0x3b64,
	.cxcs = (अचिन्हित पूर्णांक [])अणु 0x3b68, 0x3b6c पूर्ण,
	.cxc_count = 2,
	.pd = अणु
		.name = "fd",
	पूर्ण,
	.parent = &camss_gdsc.pd,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc mdss_gdsc = अणु
	.gdscr = 0x2304,
	.cxcs = (अचिन्हित पूर्णांक [])अणु 0x2310, 0x231c पूर्ण,
	.cxc_count = 2,
	.pd = अणु
		.name = "mdss",
	पूर्ण,
	.parent = &mmagic_mdss_gdsc.pd,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc gpu_gdsc = अणु
	.gdscr = 0x4034,
	.gds_hw_ctrl = 0x4038,
	.pd = अणु
		.name = "gpu",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc gpu_gx_gdsc = अणु
	.gdscr = 0x4024,
	.clamp_io_ctrl = 0x4300,
	.cxcs = (अचिन्हित पूर्णांक [])अणु 0x4028 पूर्ण,
	.cxc_count = 1,
	.pd = अणु
		.name = "gpu_gx",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.parent = &gpu_gdsc.pd,
	.flags = CLAMP_IO,
	.supply = "vdd-gfx",
पूर्ण;

अटल काष्ठा clk_regmap *mmcc_msm8996_घड़ीs[] = अणु
	[MMPLL0_EARLY] = &mmpll0_early.clkr,
	[MMPLL0_PLL] = &mmpll0.clkr,
	[MMPLL1_EARLY] = &mmpll1_early.clkr,
	[MMPLL1_PLL] = &mmpll1.clkr,
	[MMPLL2_EARLY] = &mmpll2_early.clkr,
	[MMPLL2_PLL] = &mmpll2.clkr,
	[MMPLL3_EARLY] = &mmpll3_early.clkr,
	[MMPLL3_PLL] = &mmpll3.clkr,
	[MMPLL4_EARLY] = &mmpll4_early.clkr,
	[MMPLL4_PLL] = &mmpll4.clkr,
	[MMPLL5_EARLY] = &mmpll5_early.clkr,
	[MMPLL5_PLL] = &mmpll5.clkr,
	[MMPLL8_EARLY] = &mmpll8_early.clkr,
	[MMPLL8_PLL] = &mmpll8.clkr,
	[MMPLL9_EARLY] = &mmpll9_early.clkr,
	[MMPLL9_PLL] = &mmpll9.clkr,
	[AHB_CLK_SRC] = &ahb_clk_src.clkr,
	[AXI_CLK_SRC] = &axi_clk_src.clkr,
	[MAXI_CLK_SRC] = &maxi_clk_src.clkr,
	[GFX3D_CLK_SRC] = &gfx3d_clk_src.rcg.clkr,
	[RBBMTIMER_CLK_SRC] = &rbbmसमयr_clk_src.clkr,
	[ISENSE_CLK_SRC] = &isense_clk_src.clkr,
	[RBCPR_CLK_SRC] = &rbcpr_clk_src.clkr,
	[VIDEO_CORE_CLK_SRC] = &video_core_clk_src.clkr,
	[VIDEO_SUBCORE0_CLK_SRC] = &video_subcore0_clk_src.clkr,
	[VIDEO_SUBCORE1_CLK_SRC] = &video_subcore1_clk_src.clkr,
	[PCLK0_CLK_SRC] = &pclk0_clk_src.clkr,
	[PCLK1_CLK_SRC] = &pclk1_clk_src.clkr,
	[MDP_CLK_SRC] = &mdp_clk_src.clkr,
	[EXTPCLK_CLK_SRC] = &extpclk_clk_src.clkr,
	[VSYNC_CLK_SRC] = &vsync_clk_src.clkr,
	[HDMI_CLK_SRC] = &hdmi_clk_src.clkr,
	[BYTE0_CLK_SRC] = &byte0_clk_src.clkr,
	[BYTE1_CLK_SRC] = &byte1_clk_src.clkr,
	[ESC0_CLK_SRC] = &esc0_clk_src.clkr,
	[ESC1_CLK_SRC] = &esc1_clk_src.clkr,
	[CAMSS_GP0_CLK_SRC] = &camss_gp0_clk_src.clkr,
	[CAMSS_GP1_CLK_SRC] = &camss_gp1_clk_src.clkr,
	[MCLK0_CLK_SRC] = &mclk0_clk_src.clkr,
	[MCLK1_CLK_SRC] = &mclk1_clk_src.clkr,
	[MCLK2_CLK_SRC] = &mclk2_clk_src.clkr,
	[MCLK3_CLK_SRC] = &mclk3_clk_src.clkr,
	[CCI_CLK_SRC] = &cci_clk_src.clkr,
	[CSI0PHYTIMER_CLK_SRC] = &csi0phyसमयr_clk_src.clkr,
	[CSI1PHYTIMER_CLK_SRC] = &csi1phyसमयr_clk_src.clkr,
	[CSI2PHYTIMER_CLK_SRC] = &csi2phyसमयr_clk_src.clkr,
	[CSIPHY0_3P_CLK_SRC] = &csiphy0_3p_clk_src.clkr,
	[CSIPHY1_3P_CLK_SRC] = &csiphy1_3p_clk_src.clkr,
	[CSIPHY2_3P_CLK_SRC] = &csiphy2_3p_clk_src.clkr,
	[JPEG0_CLK_SRC] = &jpeg0_clk_src.clkr,
	[JPEG2_CLK_SRC] = &jpeg2_clk_src.clkr,
	[JPEG_DMA_CLK_SRC] = &jpeg_dma_clk_src.clkr,
	[VFE0_CLK_SRC] = &vfe0_clk_src.clkr,
	[VFE1_CLK_SRC] = &vfe1_clk_src.clkr,
	[CPP_CLK_SRC] = &cpp_clk_src.clkr,
	[CSI0_CLK_SRC] = &csi0_clk_src.clkr,
	[CSI1_CLK_SRC] = &csi1_clk_src.clkr,
	[CSI2_CLK_SRC] = &csi2_clk_src.clkr,
	[CSI3_CLK_SRC] = &csi3_clk_src.clkr,
	[FD_CORE_CLK_SRC] = &fd_core_clk_src.clkr,
	[MMSS_MMAGIC_AHB_CLK] = &mmss_mmagic_ahb_clk.clkr,
	[MMSS_MMAGIC_CFG_AHB_CLK] = &mmss_mmagic_cfg_ahb_clk.clkr,
	[MMSS_MISC_AHB_CLK] = &mmss_misc_ahb_clk.clkr,
	[MMSS_MISC_CXO_CLK] = &mmss_misc_cxo_clk.clkr,
	[MMSS_MMAGIC_MAXI_CLK] = &mmss_mmagic_maxi_clk.clkr,
	[MMAGIC_CAMSS_AXI_CLK] = &mmagic_camss_axi_clk.clkr,
	[MMAGIC_CAMSS_NOC_CFG_AHB_CLK] = &mmagic_camss_noc_cfg_ahb_clk.clkr,
	[SMMU_VFE_AHB_CLK] = &smmu_vfe_ahb_clk.clkr,
	[SMMU_VFE_AXI_CLK] = &smmu_vfe_axi_clk.clkr,
	[SMMU_CPP_AHB_CLK] = &smmu_cpp_ahb_clk.clkr,
	[SMMU_CPP_AXI_CLK] = &smmu_cpp_axi_clk.clkr,
	[SMMU_JPEG_AHB_CLK] = &smmu_jpeg_ahb_clk.clkr,
	[SMMU_JPEG_AXI_CLK] = &smmu_jpeg_axi_clk.clkr,
	[MMAGIC_MDSS_AXI_CLK] = &mmagic_mdss_axi_clk.clkr,
	[MMAGIC_MDSS_NOC_CFG_AHB_CLK] = &mmagic_mdss_noc_cfg_ahb_clk.clkr,
	[SMMU_ROT_AHB_CLK] = &smmu_rot_ahb_clk.clkr,
	[SMMU_ROT_AXI_CLK] = &smmu_rot_axi_clk.clkr,
	[SMMU_MDP_AHB_CLK] = &smmu_mdp_ahb_clk.clkr,
	[SMMU_MDP_AXI_CLK] = &smmu_mdp_axi_clk.clkr,
	[MMAGIC_VIDEO_AXI_CLK] = &mmagic_video_axi_clk.clkr,
	[MMAGIC_VIDEO_NOC_CFG_AHB_CLK] = &mmagic_video_noc_cfg_ahb_clk.clkr,
	[SMMU_VIDEO_AHB_CLK] = &smmu_video_ahb_clk.clkr,
	[SMMU_VIDEO_AXI_CLK] = &smmu_video_axi_clk.clkr,
	[MMAGIC_BIMC_NOC_CFG_AHB_CLK] = &mmagic_bimc_noc_cfg_ahb_clk.clkr,
	[GPU_GX_GFX3D_CLK] = &gpu_gx_gfx3d_clk.clkr,
	[GPU_GX_RBBMTIMER_CLK] = &gpu_gx_rbbmसमयr_clk.clkr,
	[GPU_AHB_CLK] = &gpu_ahb_clk.clkr,
	[GPU_AON_ISENSE_CLK] = &gpu_aon_isense_clk.clkr,
	[VMEM_MAXI_CLK] = &vmem_maxi_clk.clkr,
	[VMEM_AHB_CLK] = &vmem_ahb_clk.clkr,
	[MMSS_RBCPR_CLK] = &mmss_rbcpr_clk.clkr,
	[MMSS_RBCPR_AHB_CLK] = &mmss_rbcpr_ahb_clk.clkr,
	[VIDEO_CORE_CLK] = &video_core_clk.clkr,
	[VIDEO_AXI_CLK] = &video_axi_clk.clkr,
	[VIDEO_MAXI_CLK] = &video_maxi_clk.clkr,
	[VIDEO_AHB_CLK] = &video_ahb_clk.clkr,
	[VIDEO_SUBCORE0_CLK] = &video_subcore0_clk.clkr,
	[VIDEO_SUBCORE1_CLK] = &video_subcore1_clk.clkr,
	[MDSS_AHB_CLK] = &mdss_ahb_clk.clkr,
	[MDSS_HDMI_AHB_CLK] = &mdss_hdmi_ahb_clk.clkr,
	[MDSS_AXI_CLK] = &mdss_axi_clk.clkr,
	[MDSS_PCLK0_CLK] = &mdss_pclk0_clk.clkr,
	[MDSS_PCLK1_CLK] = &mdss_pclk1_clk.clkr,
	[MDSS_MDP_CLK] = &mdss_mdp_clk.clkr,
	[MDSS_EXTPCLK_CLK] = &mdss_extpclk_clk.clkr,
	[MDSS_VSYNC_CLK] = &mdss_vsync_clk.clkr,
	[MDSS_HDMI_CLK] = &mdss_hdmi_clk.clkr,
	[MDSS_BYTE0_CLK] = &mdss_byte0_clk.clkr,
	[MDSS_BYTE1_CLK] = &mdss_byte1_clk.clkr,
	[MDSS_ESC0_CLK] = &mdss_esc0_clk.clkr,
	[MDSS_ESC1_CLK] = &mdss_esc1_clk.clkr,
	[CAMSS_TOP_AHB_CLK] = &camss_top_ahb_clk.clkr,
	[CAMSS_AHB_CLK] = &camss_ahb_clk.clkr,
	[CAMSS_MICRO_AHB_CLK] = &camss_micro_ahb_clk.clkr,
	[CAMSS_GP0_CLK] = &camss_gp0_clk.clkr,
	[CAMSS_GP1_CLK] = &camss_gp1_clk.clkr,
	[CAMSS_MCLK0_CLK] = &camss_mclk0_clk.clkr,
	[CAMSS_MCLK1_CLK] = &camss_mclk1_clk.clkr,
	[CAMSS_MCLK2_CLK] = &camss_mclk2_clk.clkr,
	[CAMSS_MCLK3_CLK] = &camss_mclk3_clk.clkr,
	[CAMSS_CCI_CLK] = &camss_cci_clk.clkr,
	[CAMSS_CCI_AHB_CLK] = &camss_cci_ahb_clk.clkr,
	[CAMSS_CSI0PHYTIMER_CLK] = &camss_csi0phyसमयr_clk.clkr,
	[CAMSS_CSI1PHYTIMER_CLK] = &camss_csi1phyसमयr_clk.clkr,
	[CAMSS_CSI2PHYTIMER_CLK] = &camss_csi2phyसमयr_clk.clkr,
	[CAMSS_CSIPHY0_3P_CLK] = &camss_csiphy0_3p_clk.clkr,
	[CAMSS_CSIPHY1_3P_CLK] = &camss_csiphy1_3p_clk.clkr,
	[CAMSS_CSIPHY2_3P_CLK] = &camss_csiphy2_3p_clk.clkr,
	[CAMSS_JPEG0_CLK] = &camss_jpeg0_clk.clkr,
	[CAMSS_JPEG2_CLK] = &camss_jpeg2_clk.clkr,
	[CAMSS_JPEG_DMA_CLK] = &camss_jpeg_dma_clk.clkr,
	[CAMSS_JPEG_AHB_CLK] = &camss_jpeg_ahb_clk.clkr,
	[CAMSS_JPEG_AXI_CLK] = &camss_jpeg_axi_clk.clkr,
	[CAMSS_VFE_AHB_CLK] = &camss_vfe_ahb_clk.clkr,
	[CAMSS_VFE_AXI_CLK] = &camss_vfe_axi_clk.clkr,
	[CAMSS_VFE0_CLK] = &camss_vfe0_clk.clkr,
	[CAMSS_VFE0_STREAM_CLK] = &camss_vfe0_stream_clk.clkr,
	[CAMSS_VFE0_AHB_CLK] = &camss_vfe0_ahb_clk.clkr,
	[CAMSS_VFE1_CLK] = &camss_vfe1_clk.clkr,
	[CAMSS_VFE1_STREAM_CLK] = &camss_vfe1_stream_clk.clkr,
	[CAMSS_VFE1_AHB_CLK] = &camss_vfe1_ahb_clk.clkr,
	[CAMSS_CSI_VFE0_CLK] = &camss_csi_vfe0_clk.clkr,
	[CAMSS_CSI_VFE1_CLK] = &camss_csi_vfe1_clk.clkr,
	[CAMSS_CPP_VBIF_AHB_CLK] = &camss_cpp_vbअगर_ahb_clk.clkr,
	[CAMSS_CPP_AXI_CLK] = &camss_cpp_axi_clk.clkr,
	[CAMSS_CPP_CLK] = &camss_cpp_clk.clkr,
	[CAMSS_CPP_AHB_CLK] = &camss_cpp_ahb_clk.clkr,
	[CAMSS_CSI0_CLK] = &camss_csi0_clk.clkr,
	[CAMSS_CSI0_AHB_CLK] = &camss_csi0_ahb_clk.clkr,
	[CAMSS_CSI0PHY_CLK] = &camss_csi0phy_clk.clkr,
	[CAMSS_CSI0RDI_CLK] = &camss_csi0rdi_clk.clkr,
	[CAMSS_CSI0PIX_CLK] = &camss_csi0pix_clk.clkr,
	[CAMSS_CSI1_CLK] = &camss_csi1_clk.clkr,
	[CAMSS_CSI1_AHB_CLK] = &camss_csi1_ahb_clk.clkr,
	[CAMSS_CSI1PHY_CLK] = &camss_csi1phy_clk.clkr,
	[CAMSS_CSI1RDI_CLK] = &camss_csi1rdi_clk.clkr,
	[CAMSS_CSI1PIX_CLK] = &camss_csi1pix_clk.clkr,
	[CAMSS_CSI2_CLK] = &camss_csi2_clk.clkr,
	[CAMSS_CSI2_AHB_CLK] = &camss_csi2_ahb_clk.clkr,
	[CAMSS_CSI2PHY_CLK] = &camss_csi2phy_clk.clkr,
	[CAMSS_CSI2RDI_CLK] = &camss_csi2rdi_clk.clkr,
	[CAMSS_CSI2PIX_CLK] = &camss_csi2pix_clk.clkr,
	[CAMSS_CSI3_CLK] = &camss_csi3_clk.clkr,
	[CAMSS_CSI3_AHB_CLK] = &camss_csi3_ahb_clk.clkr,
	[CAMSS_CSI3PHY_CLK] = &camss_csi3phy_clk.clkr,
	[CAMSS_CSI3RDI_CLK] = &camss_csi3rdi_clk.clkr,
	[CAMSS_CSI3PIX_CLK] = &camss_csi3pix_clk.clkr,
	[CAMSS_ISPIF_AHB_CLK] = &camss_ispअगर_ahb_clk.clkr,
	[FD_CORE_CLK] = &fd_core_clk.clkr,
	[FD_CORE_UAR_CLK] = &fd_core_uar_clk.clkr,
	[FD_AHB_CLK] = &fd_ahb_clk.clkr,
पूर्ण;

अटल काष्ठा gdsc *mmcc_msm8996_gdscs[] = अणु
	[MMAGIC_BIMC_GDSC] = &mmagic_bimc_gdsc,
	[MMAGIC_VIDEO_GDSC] = &mmagic_video_gdsc,
	[MMAGIC_MDSS_GDSC] = &mmagic_mdss_gdsc,
	[MMAGIC_CAMSS_GDSC] = &mmagic_camss_gdsc,
	[VENUS_GDSC] = &venus_gdsc,
	[VENUS_CORE0_GDSC] = &venus_core0_gdsc,
	[VENUS_CORE1_GDSC] = &venus_core1_gdsc,
	[CAMSS_GDSC] = &camss_gdsc,
	[VFE0_GDSC] = &vfe0_gdsc,
	[VFE1_GDSC] = &vfe1_gdsc,
	[JPEG_GDSC] = &jpeg_gdsc,
	[CPP_GDSC] = &cpp_gdsc,
	[FD_GDSC] = &fd_gdsc,
	[MDSS_GDSC] = &mdss_gdsc,
	[GPU_GDSC] = &gpu_gdsc,
	[GPU_GX_GDSC] = &gpu_gx_gdsc,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map mmcc_msm8996_resets[] = अणु
	[MMAGICAHB_BCR] = अणु 0x5020 पूर्ण,
	[MMAGIC_CFG_BCR] = अणु 0x5050 पूर्ण,
	[MISC_BCR] = अणु 0x5010 पूर्ण,
	[BTO_BCR] = अणु 0x5030 पूर्ण,
	[MMAGICAXI_BCR] = अणु 0x5060 पूर्ण,
	[MMAGICMAXI_BCR] = अणु 0x5070 पूर्ण,
	[DSA_BCR] = अणु 0x50a0 पूर्ण,
	[MMAGIC_CAMSS_BCR] = अणु 0x3c40 पूर्ण,
	[THROTTLE_CAMSS_BCR] = अणु 0x3c30 पूर्ण,
	[SMMU_VFE_BCR] = अणु 0x3c00 पूर्ण,
	[SMMU_CPP_BCR] = अणु 0x3c10 पूर्ण,
	[SMMU_JPEG_BCR] = अणु 0x3c20 पूर्ण,
	[MMAGIC_MDSS_BCR] = अणु 0x2470 पूर्ण,
	[THROTTLE_MDSS_BCR] = अणु 0x2460 पूर्ण,
	[SMMU_ROT_BCR] = अणु 0x2440 पूर्ण,
	[SMMU_MDP_BCR] = अणु 0x2450 पूर्ण,
	[MMAGIC_VIDEO_BCR] = अणु 0x1190 पूर्ण,
	[THROTTLE_VIDEO_BCR] = अणु 0x1180 पूर्ण,
	[SMMU_VIDEO_BCR] = अणु 0x1170 पूर्ण,
	[MMAGIC_BIMC_BCR] = अणु 0x5290 पूर्ण,
	[GPU_GX_BCR] = अणु 0x4020 पूर्ण,
	[GPU_BCR] = अणु 0x4030 पूर्ण,
	[GPU_AON_BCR] = अणु 0x4040 पूर्ण,
	[VMEM_BCR] = अणु 0x1200 पूर्ण,
	[MMSS_RBCPR_BCR] = अणु 0x4080 पूर्ण,
	[VIDEO_BCR] = अणु 0x1020 पूर्ण,
	[MDSS_BCR] = अणु 0x2300 पूर्ण,
	[CAMSS_TOP_BCR] = अणु 0x3480 पूर्ण,
	[CAMSS_AHB_BCR] = अणु 0x3488 पूर्ण,
	[CAMSS_MICRO_BCR] = अणु 0x3490 पूर्ण,
	[CAMSS_CCI_BCR] = अणु 0x3340 पूर्ण,
	[CAMSS_PHY0_BCR] = अणु 0x3020 पूर्ण,
	[CAMSS_PHY1_BCR] = अणु 0x3050 पूर्ण,
	[CAMSS_PHY2_BCR] = अणु 0x3080 पूर्ण,
	[CAMSS_CSIPHY0_3P_BCR] = अणु 0x3230 पूर्ण,
	[CAMSS_CSIPHY1_3P_BCR] = अणु 0x3250 पूर्ण,
	[CAMSS_CSIPHY2_3P_BCR] = अणु 0x3270 पूर्ण,
	[CAMSS_JPEG_BCR] = अणु 0x35a0 पूर्ण,
	[CAMSS_VFE_BCR] = अणु 0x36a0 पूर्ण,
	[CAMSS_VFE0_BCR] = अणु 0x3660 पूर्ण,
	[CAMSS_VFE1_BCR] = अणु 0x3670 पूर्ण,
	[CAMSS_CSI_VFE0_BCR] = अणु 0x3700 पूर्ण,
	[CAMSS_CSI_VFE1_BCR] = अणु 0x3710 पूर्ण,
	[CAMSS_CPP_TOP_BCR] = अणु 0x36c0 पूर्ण,
	[CAMSS_CPP_BCR] = अणु 0x36d0 पूर्ण,
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
	[FD_BCR] = अणु 0x3b60 पूर्ण,
	[MMSS_SPDM_RM_BCR] = अणु 0x300 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config mmcc_msm8996_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0xb008,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc mmcc_msm8996_desc = अणु
	.config = &mmcc_msm8996_regmap_config,
	.clks = mmcc_msm8996_घड़ीs,
	.num_clks = ARRAY_SIZE(mmcc_msm8996_घड़ीs),
	.resets = mmcc_msm8996_resets,
	.num_resets = ARRAY_SIZE(mmcc_msm8996_resets),
	.gdscs = mmcc_msm8996_gdscs,
	.num_gdscs = ARRAY_SIZE(mmcc_msm8996_gdscs),
	.clk_hws = mmcc_msm8996_hws,
	.num_clk_hws = ARRAY_SIZE(mmcc_msm8996_hws),
पूर्ण;

अटल स्थिर काष्ठा of_device_id mmcc_msm8996_match_table[] = अणु
	अणु .compatible = "qcom,mmcc-msm8996" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mmcc_msm8996_match_table);

अटल पूर्णांक mmcc_msm8996_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;

	regmap = qcom_cc_map(pdev, &mmcc_msm8996_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/* Disable the AHB DCD */
	regmap_update_bits(regmap, 0x50d8, BIT(31), 0);
	/* Disable the NoC FSM क्रम mmss_mmagic_cfg_ahb_clk */
	regmap_update_bits(regmap, 0x5054, BIT(15), 0);

	वापस qcom_cc_really_probe(pdev, &mmcc_msm8996_desc, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver mmcc_msm8996_driver = अणु
	.probe		= mmcc_msm8996_probe,
	.driver		= अणु
		.name	= "mmcc-msm8996",
		.of_match_table = mmcc_msm8996_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mmcc_msm8996_driver);

MODULE_DESCRIPTION("QCOM MMCC MSM8996 Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:mmcc-msm8996");
