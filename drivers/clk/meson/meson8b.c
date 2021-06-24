<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015 Endless Mobile, Inc.
 * Author: Carlo Caione <carlo@endlessm.com>
 *
 * Copyright (c) 2016 BayLibre, Inc.
 * Michael Turquette <mturquette@baylibre.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_address.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>

#समावेश "meson8b.h"
#समावेश "clk-regmap.h"
#समावेश "clk-pll.h"
#समावेश "clk-mpll.h"

अटल DEFINE_SPINLOCK(meson_clk_lock);

काष्ठा meson8b_clk_reset अणु
	काष्ठा reset_controller_dev reset;
	काष्ठा regmap *regmap;
पूर्ण;

अटल स्थिर काष्ठा pll_params_table sys_pll_params_table[] = अणु
	PLL_PARAMS(50, 1),
	PLL_PARAMS(51, 1),
	PLL_PARAMS(52, 1),
	PLL_PARAMS(53, 1),
	PLL_PARAMS(54, 1),
	PLL_PARAMS(55, 1),
	PLL_PARAMS(56, 1),
	PLL_PARAMS(57, 1),
	PLL_PARAMS(58, 1),
	PLL_PARAMS(59, 1),
	PLL_PARAMS(60, 1),
	PLL_PARAMS(61, 1),
	PLL_PARAMS(62, 1),
	PLL_PARAMS(63, 1),
	PLL_PARAMS(64, 1),
	PLL_PARAMS(65, 1),
	PLL_PARAMS(66, 1),
	PLL_PARAMS(67, 1),
	PLL_PARAMS(68, 1),
	PLL_PARAMS(84, 1),
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_fixed_pll_dco = अणु
	.data = &(काष्ठा meson_clk_pll_data)अणु
		.en = अणु
			.reg_off = HHI_MPLL_CNTL,
			.shअगरt   = 30,
			.width   = 1,
		पूर्ण,
		.m = अणु
			.reg_off = HHI_MPLL_CNTL,
			.shअगरt   = 0,
			.width   = 9,
		पूर्ण,
		.n = अणु
			.reg_off = HHI_MPLL_CNTL,
			.shअगरt   = 9,
			.width   = 5,
		पूर्ण,
		.frac = अणु
			.reg_off = HHI_MPLL_CNTL2,
			.shअगरt   = 0,
			.width   = 12,
		पूर्ण,
		.l = अणु
			.reg_off = HHI_MPLL_CNTL,
			.shअगरt   = 31,
			.width   = 1,
		पूर्ण,
		.rst = अणु
			.reg_off = HHI_MPLL_CNTL,
			.shअगरt   = 29,
			.width   = 1,
		पूर्ण,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fixed_pll_dco",
		.ops = &meson_clk_pll_ro_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			.fw_name = "xtal",
			.name = "xtal",
			.index = -1,
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_fixed_pll = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_MPLL_CNTL,
		.shअगरt = 16,
		.width = 2,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fixed_pll",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_fixed_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
		/*
		 * This घड़ी won't ever change at runसमय so
		 * CLK_SET_RATE_PARENT is not required
		 */
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_hdmi_pll_dco = अणु
	.data = &(काष्ठा meson_clk_pll_data)अणु
		.en = अणु
			.reg_off = HHI_VID_PLL_CNTL,
			.shअगरt   = 30,
			.width   = 1,
		पूर्ण,
		.m = अणु
			.reg_off = HHI_VID_PLL_CNTL,
			.shअगरt   = 0,
			.width   = 9,
		पूर्ण,
		.n = अणु
			.reg_off = HHI_VID_PLL_CNTL,
			.shअगरt   = 10,
			.width   = 5,
		पूर्ण,
		.frac = अणु
			.reg_off = HHI_VID_PLL_CNTL2,
			.shअगरt   = 0,
			.width   = 12,
		पूर्ण,
		.l = अणु
			.reg_off = HHI_VID_PLL_CNTL,
			.shअगरt   = 31,
			.width   = 1,
		पूर्ण,
		.rst = अणु
			.reg_off = HHI_VID_PLL_CNTL,
			.shअगरt   = 29,
			.width   = 1,
		पूर्ण,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		/* someबार also called "HPLL" or "HPLL PLL" */
		.name = "hdmi_pll_dco",
		.ops = &meson_clk_pll_ro_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			.fw_name = "xtal",
			.name = "xtal",
			.index = -1,
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_hdmi_pll_lvds_out = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VID_PLL_CNTL,
		.shअगरt = 16,
		.width = 2,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "hdmi_pll_lvds_out",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_hdmi_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_hdmi_pll_hdmi_out = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VID_PLL_CNTL,
		.shअगरt = 18,
		.width = 2,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "hdmi_pll_hdmi_out",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_hdmi_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_sys_pll_dco = अणु
	.data = &(काष्ठा meson_clk_pll_data)अणु
		.en = अणु
			.reg_off = HHI_SYS_PLL_CNTL,
			.shअगरt   = 30,
			.width   = 1,
		पूर्ण,
		.m = अणु
			.reg_off = HHI_SYS_PLL_CNTL,
			.shअगरt   = 0,
			.width   = 9,
		पूर्ण,
		.n = अणु
			.reg_off = HHI_SYS_PLL_CNTL,
			.shअगरt   = 9,
			.width   = 5,
		पूर्ण,
		.l = अणु
			.reg_off = HHI_SYS_PLL_CNTL,
			.shअगरt   = 31,
			.width   = 1,
		पूर्ण,
		.rst = अणु
			.reg_off = HHI_SYS_PLL_CNTL,
			.shअगरt   = 29,
			.width   = 1,
		पूर्ण,
		.table = sys_pll_params_table,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sys_pll_dco",
		.ops = &meson_clk_pll_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			.fw_name = "xtal",
			.name = "xtal",
			.index = -1,
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_sys_pll = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_SYS_PLL_CNTL,
		.shअगरt = 16,
		.width = 2,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sys_pll",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_sys_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_fclk_भाग2_भाग = अणु
	.mult = 1,
	.भाग = 2,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div2_div",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_fixed_pll.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_fclk_भाग2 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL_CNTL6,
		.bit_idx = 27,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div2",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_fclk_भाग2_भाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_fclk_भाग3_भाग = अणु
	.mult = 1,
	.भाग = 3,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div3_div",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_fixed_pll.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_fclk_भाग3 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL_CNTL6,
		.bit_idx = 28,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div3",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_fclk_भाग3_भाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_fclk_भाग4_भाग = अणु
	.mult = 1,
	.भाग = 4,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div4_div",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_fixed_pll.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_fclk_भाग4 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL_CNTL6,
		.bit_idx = 29,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div4",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_fclk_भाग4_भाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_fclk_भाग5_भाग = अणु
	.mult = 1,
	.भाग = 5,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div5_div",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_fixed_pll.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_fclk_भाग5 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL_CNTL6,
		.bit_idx = 30,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div5",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_fclk_भाग5_भाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_fclk_भाग7_भाग = अणु
	.mult = 1,
	.भाग = 7,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div7_div",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_fixed_pll.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_fclk_भाग7 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL_CNTL6,
		.bit_idx = 31,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div7",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_fclk_भाग7_भाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_mpll_preभाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_MPLL_CNTL5,
		.shअगरt = 12,
		.width = 1,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll_prediv",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_fixed_pll.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_mpll0_भाग = अणु
	.data = &(काष्ठा meson_clk_mpll_data)अणु
		.sdm = अणु
			.reg_off = HHI_MPLL_CNTL7,
			.shअगरt   = 0,
			.width   = 14,
		पूर्ण,
		.sdm_en = अणु
			.reg_off = HHI_MPLL_CNTL7,
			.shअगरt   = 15,
			.width   = 1,
		पूर्ण,
		.n2 = अणु
			.reg_off = HHI_MPLL_CNTL7,
			.shअगरt   = 16,
			.width   = 9,
		पूर्ण,
		.ssen = अणु
			.reg_off = HHI_MPLL_CNTL,
			.shअगरt   = 25,
			.width   = 1,
		पूर्ण,
		.lock = &meson_clk_lock,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll0_div",
		.ops = &meson_clk_mpll_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_mpll_preभाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_mpll0 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL_CNTL7,
		.bit_idx = 14,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll0",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_mpll0_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_mpll1_भाग = अणु
	.data = &(काष्ठा meson_clk_mpll_data)अणु
		.sdm = अणु
			.reg_off = HHI_MPLL_CNTL8,
			.shअगरt   = 0,
			.width   = 14,
		पूर्ण,
		.sdm_en = अणु
			.reg_off = HHI_MPLL_CNTL8,
			.shअगरt   = 15,
			.width   = 1,
		पूर्ण,
		.n2 = अणु
			.reg_off = HHI_MPLL_CNTL8,
			.shअगरt   = 16,
			.width   = 9,
		पूर्ण,
		.lock = &meson_clk_lock,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll1_div",
		.ops = &meson_clk_mpll_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_mpll_preभाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_mpll1 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL_CNTL8,
		.bit_idx = 14,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll1",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_mpll1_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_mpll2_भाग = अणु
	.data = &(काष्ठा meson_clk_mpll_data)अणु
		.sdm = अणु
			.reg_off = HHI_MPLL_CNTL9,
			.shअगरt   = 0,
			.width   = 14,
		पूर्ण,
		.sdm_en = अणु
			.reg_off = HHI_MPLL_CNTL9,
			.shअगरt   = 15,
			.width   = 1,
		पूर्ण,
		.n2 = अणु
			.reg_off = HHI_MPLL_CNTL9,
			.shअगरt   = 16,
			.width   = 9,
		पूर्ण,
		.lock = &meson_clk_lock,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll2_div",
		.ops = &meson_clk_mpll_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_mpll_preभाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_mpll2 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL_CNTL9,
		.bit_idx = 14,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll2",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_mpll2_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल u32 mux_table_clk81[]	= अणु 6, 5, 7 पूर्ण;
अटल काष्ठा clk_regmap meson8b_mpeg_clk_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_MPEG_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 12,
		.table = mux_table_clk81,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpeg_clk_sel",
		.ops = &clk_regmap_mux_ro_ops,
		/*
		 * FIXME bits 14:12 selects from 8 possible parents:
		 * xtal, 1'b0 (wtf), fclk_भाग7, mpll_clkout1, mpll_clkout2,
		 * fclk_भाग4, fclk_भाग3, fclk_भाग5
		 */
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_fclk_भाग3.hw,
			&meson8b_fclk_भाग4.hw,
			&meson8b_fclk_भाग5.hw,
		पूर्ण,
		.num_parents = 3,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_mpeg_clk_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_MPEG_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpeg_clk_div",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_mpeg_clk_sel.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_clk81 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPEG_CLK_CNTL,
		.bit_idx = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk81",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_mpeg_clk_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_IS_CRITICAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_cpu_in_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL0,
		.mask = 0x1,
		.shअगरt = 0,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_in_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_data = (स्थिर काष्ठा clk_parent_data[]) अणु
			अणु .fw_name = "xtal", .name = "xtal", .index = -1, पूर्ण,
			अणु .hw = &meson8b_sys_pll.hw, पूर्ण,
		पूर्ण,
		.num_parents = 2,
		.flags = (CLK_SET_RATE_PARENT |
			  CLK_SET_RATE_NO_REPARENT),
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_cpu_in_भाग2 = अणु
	.mult = 1,
	.भाग = 2,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_in_div2",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cpu_in_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_cpu_in_भाग3 = अणु
	.mult = 1,
	.भाग = 3,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_in_div3",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cpu_in_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable cpu_scale_table[] = अणु
	अणु .val = 1, .भाग = 4 पूर्ण,
	अणु .val = 2, .भाग = 6 पूर्ण,
	अणु .val = 3, .भाग = 8 पूर्ण,
	अणु .val = 4, .भाग = 10 पूर्ण,
	अणु .val = 5, .भाग = 12 पूर्ण,
	अणु .val = 6, .भाग = 14 पूर्ण,
	अणु .val = 7, .भाग = 16 पूर्ण,
	अणु .val = 8, .भाग = 18 पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_cpu_scale_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset =  HHI_SYS_CPU_CLK_CNTL1,
		.shअगरt = 20,
		.width = 10,
		.table = cpu_scale_table,
		.flags = CLK_DIVIDER_ALLOW_ZERO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_scale_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cpu_in_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल u32 mux_table_cpu_scale_out_sel[] = अणु 0, 1, 3 पूर्ण;
अटल काष्ठा clk_regmap meson8b_cpu_scale_out_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL0,
		.mask = 0x3,
		.shअगरt = 2,
		.table = mux_table_cpu_scale_out_sel,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_scale_out_sel",
		.ops = &clk_regmap_mux_ops,
		/*
		 * NOTE: We are skipping the parent with value 0x2 (which is
		 * meson8b_cpu_in_भाग3) because it results in a duty cycle of
		 * 33% which makes the प्रणाली unstable and can result in a
		 * lockup of the whole प्रणाली.
		 */
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cpu_in_sel.hw,
			&meson8b_cpu_in_भाग2.hw,
			&meson8b_cpu_scale_भाग.hw,
		पूर्ण,
		.num_parents = 3,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_cpu_clk = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL0,
		.mask = 0x1,
		.shअगरt = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk",
		.ops = &clk_regmap_mux_ops,
		.parent_data = (स्थिर काष्ठा clk_parent_data[]) अणु
			अणु .fw_name = "xtal", .name = "xtal", .index = -1, पूर्ण,
			अणु .hw = &meson8b_cpu_scale_out_sel.hw, पूर्ण,
		पूर्ण,
		.num_parents = 2,
		.flags = (CLK_SET_RATE_PARENT |
			  CLK_SET_RATE_NO_REPARENT |
			  CLK_IS_CRITICAL),
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_nand_clk_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_न_अंकD_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 9,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "nand_clk_sel",
		.ops = &clk_regmap_mux_ops,
		/* FIXME all other parents are unknown: */
		.parent_data = (स्थिर काष्ठा clk_parent_data[]) अणु
			अणु .hw = &meson8b_fclk_भाग4.hw, पूर्ण,
			अणु .hw = &meson8b_fclk_भाग3.hw, पूर्ण,
			अणु .hw = &meson8b_fclk_भाग5.hw, पूर्ण,
			अणु .hw = &meson8b_fclk_भाग7.hw, पूर्ण,
			अणु .fw_name = "xtal", .name = "xtal", .index = -1, पूर्ण,
		पूर्ण,
		.num_parents = 5,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_nand_clk_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset =  HHI_न_अंकD_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
		.flags = CLK_DIVIDER_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "nand_clk_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_nand_clk_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_nand_clk_gate = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_न_अंकD_CLK_CNTL,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "nand_clk_gate",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_nand_clk_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_cpu_clk_भाग2 = अणु
	.mult = 1,
	.भाग = 2,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk_div2",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cpu_clk.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_cpu_clk_भाग3 = अणु
	.mult = 1,
	.भाग = 3,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk_div3",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cpu_clk.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_cpu_clk_भाग4 = अणु
	.mult = 1,
	.भाग = 4,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk_div4",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cpu_clk.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_cpu_clk_भाग5 = अणु
	.mult = 1,
	.भाग = 5,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk_div5",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cpu_clk.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_cpu_clk_भाग6 = अणु
	.mult = 1,
	.भाग = 6,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk_div6",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cpu_clk.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_cpu_clk_भाग7 = अणु
	.mult = 1,
	.भाग = 7,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk_div7",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cpu_clk.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_cpu_clk_भाग8 = अणु
	.mult = 1,
	.भाग = 8,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk_div8",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cpu_clk.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल u32 mux_table_apb[] = अणु 1, 2, 3, 4, 5, 6, 7 पूर्ण;
अटल काष्ठा clk_regmap meson8b_apb_clk_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL1,
		.mask = 0x7,
		.shअगरt = 3,
		.table = mux_table_apb,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "apb_clk_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cpu_clk_भाग2.hw,
			&meson8b_cpu_clk_भाग3.hw,
			&meson8b_cpu_clk_भाग4.hw,
			&meson8b_cpu_clk_भाग5.hw,
			&meson8b_cpu_clk_भाग6.hw,
			&meson8b_cpu_clk_भाग7.hw,
			&meson8b_cpu_clk_भाग8.hw,
		पूर्ण,
		.num_parents = 7,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_apb_clk_gate = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL1,
		.bit_idx = 16,
		.flags = CLK_GATE_SET_TO_DISABLE,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "apb_clk_dis",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_apb_clk_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_periph_clk_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL1,
		.mask = 0x7,
		.shअगरt = 6,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "periph_clk_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cpu_clk_भाग2.hw,
			&meson8b_cpu_clk_भाग3.hw,
			&meson8b_cpu_clk_भाग4.hw,
			&meson8b_cpu_clk_भाग5.hw,
			&meson8b_cpu_clk_भाग6.hw,
			&meson8b_cpu_clk_भाग7.hw,
			&meson8b_cpu_clk_भाग8.hw,
		पूर्ण,
		.num_parents = 7,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_periph_clk_gate = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL1,
		.bit_idx = 17,
		.flags = CLK_GATE_SET_TO_DISABLE,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "periph_clk_dis",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_periph_clk_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल u32 mux_table_axi[] = अणु 1, 2, 3, 4, 5, 6, 7 पूर्ण;
अटल काष्ठा clk_regmap meson8b_axi_clk_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL1,
		.mask = 0x7,
		.shअगरt = 9,
		.table = mux_table_axi,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "axi_clk_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cpu_clk_भाग2.hw,
			&meson8b_cpu_clk_भाग3.hw,
			&meson8b_cpu_clk_भाग4.hw,
			&meson8b_cpu_clk_भाग5.hw,
			&meson8b_cpu_clk_भाग6.hw,
			&meson8b_cpu_clk_भाग7.hw,
			&meson8b_cpu_clk_भाग8.hw,
		पूर्ण,
		.num_parents = 7,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_axi_clk_gate = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL1,
		.bit_idx = 18,
		.flags = CLK_GATE_SET_TO_DISABLE,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "axi_clk_dis",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_axi_clk_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_l2_dram_clk_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL1,
		.mask = 0x7,
		.shअगरt = 12,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "l2_dram_clk_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cpu_clk_भाग2.hw,
			&meson8b_cpu_clk_भाग3.hw,
			&meson8b_cpu_clk_भाग4.hw,
			&meson8b_cpu_clk_भाग5.hw,
			&meson8b_cpu_clk_भाग6.hw,
			&meson8b_cpu_clk_भाग7.hw,
			&meson8b_cpu_clk_भाग8.hw,
		पूर्ण,
		.num_parents = 7,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_l2_dram_clk_gate = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL1,
		.bit_idx = 19,
		.flags = CLK_GATE_SET_TO_DISABLE,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "l2_dram_clk_dis",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_l2_dram_clk_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vid_pll_in_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VID_DIVIDER_CNTL,
		.mask = 0x1,
		.shअगरt = 15,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vid_pll_in_sel",
		.ops = &clk_regmap_mux_ro_ops,
		/*
		 * TODO: depending on the SoC there is also a second parent:
		 * Meson8: unknown
		 * Meson8b: hdmi_pll_dco
		 * Meson8m2: vid2_pll
		 */
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_hdmi_pll_lvds_out.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vid_pll_in_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_DIVIDER_CNTL,
		.bit_idx = 16,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vid_pll_in_en",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vid_pll_in_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vid_pll_pre_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset =  HHI_VID_DIVIDER_CNTL,
		.shअगरt = 4,
		.width = 3,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vid_pll_pre_div",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vid_pll_in_en.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vid_pll_post_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset =  HHI_VID_DIVIDER_CNTL,
		.shअगरt = 12,
		.width = 3,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vid_pll_post_div",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vid_pll_pre_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vid_pll = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VID_DIVIDER_CNTL,
		.mask = 0x3,
		.shअगरt = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vid_pll",
		.ops = &clk_regmap_mux_ro_ops,
		/* TODO: parent 0x2 is vid_pll_pre_भाग_mult7_भाग2 */
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vid_pll_pre_भाग.hw,
			&meson8b_vid_pll_post_भाग.hw,
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vid_pll_final_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset =  HHI_VID_CLK_DIV,
		.shअगरt = 0,
		.width = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vid_pll_final_div",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vid_pll.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_hw *meson8b_vclk_mux_parent_hws[] = अणु
	&meson8b_vid_pll_final_भाग.hw,
	&meson8b_fclk_भाग4.hw,
	&meson8b_fclk_भाग3.hw,
	&meson8b_fclk_भाग5.hw,
	&meson8b_vid_pll_final_भाग.hw,
	&meson8b_fclk_भाग7.hw,
	&meson8b_mpll1.hw,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vclk_in_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 16,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_in_sel",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_hws = meson8b_vclk_mux_parent_hws,
		.num_parents = ARRAY_SIZE(meson8b_vclk_mux_parent_hws),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vclk_in_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_DIV,
		.bit_idx = 16,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_in_en",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk_in_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vclk_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.bit_idx = 19,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_en",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk_in_en.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vclk_भाग1_gate = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.bit_idx = 0,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_div1_en",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk_en.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_vclk_भाग2_भाग = अणु
	.mult = 1,
	.भाग = 2,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_div2",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk_en.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vclk_भाग2_भाग_gate = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.bit_idx = 1,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_div2_en",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk_भाग2_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_vclk_भाग4_भाग = अणु
	.mult = 1,
	.भाग = 4,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_div4",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk_en.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vclk_भाग4_भाग_gate = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.bit_idx = 2,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_div4_en",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk_भाग4_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_vclk_भाग6_भाग = अणु
	.mult = 1,
	.भाग = 6,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_div6",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk_en.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vclk_भाग6_भाग_gate = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.bit_idx = 3,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_div6_en",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk_भाग6_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_vclk_भाग12_भाग = अणु
	.mult = 1,
	.भाग = 12,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_div12",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk_en.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vclk_भाग12_भाग_gate = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.bit_idx = 4,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_div12_en",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk_भाग12_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vclk2_in_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VIID_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 16,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_in_sel",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_hws = meson8b_vclk_mux_parent_hws,
		.num_parents = ARRAY_SIZE(meson8b_vclk_mux_parent_hws),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vclk2_clk_in_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_DIV,
		.bit_idx = 16,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_in_en",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk2_in_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vclk2_clk_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_DIV,
		.bit_idx = 19,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_en",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk2_clk_in_en.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vclk2_भाग1_gate = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_DIV,
		.bit_idx = 0,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_div1_en",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk2_clk_en.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_vclk2_भाग2_भाग = अणु
	.mult = 1,
	.भाग = 2,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_div2",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk2_clk_en.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vclk2_भाग2_भाग_gate = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_DIV,
		.bit_idx = 1,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_div2_en",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk2_भाग2_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_vclk2_भाग4_भाग = अणु
	.mult = 1,
	.भाग = 4,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_div4",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk2_clk_en.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vclk2_भाग4_भाग_gate = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_DIV,
		.bit_idx = 2,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_div4_en",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk2_भाग4_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_vclk2_भाग6_भाग = अणु
	.mult = 1,
	.भाग = 6,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_div6",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk2_clk_en.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vclk2_भाग6_भाग_gate = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_DIV,
		.bit_idx = 3,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_div6_en",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk2_भाग6_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor meson8b_vclk2_भाग12_भाग = अणु
	.mult = 1,
	.भाग = 12,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_div12",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk2_clk_en.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vclk2_भाग12_भाग_gate = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_DIV,
		.bit_idx = 4,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_div12_en",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vclk2_भाग12_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_hw *meson8b_vclk_enc_mux_parent_hws[] = अणु
	&meson8b_vclk_भाग1_gate.hw,
	&meson8b_vclk_भाग2_भाग_gate.hw,
	&meson8b_vclk_भाग4_भाग_gate.hw,
	&meson8b_vclk_भाग6_भाग_gate.hw,
	&meson8b_vclk_भाग12_भाग_gate.hw,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_cts_enct_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VID_CLK_DIV,
		.mask = 0xf,
		.shअगरt = 20,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cts_enct_sel",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_hws = meson8b_vclk_enc_mux_parent_hws,
		.num_parents = ARRAY_SIZE(meson8b_vclk_enc_mux_parent_hws),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_cts_enct = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL2,
		.bit_idx = 1,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cts_enct",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cts_enct_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_cts_encp_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VID_CLK_DIV,
		.mask = 0xf,
		.shअगरt = 24,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cts_encp_sel",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_hws = meson8b_vclk_enc_mux_parent_hws,
		.num_parents = ARRAY_SIZE(meson8b_vclk_enc_mux_parent_hws),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_cts_encp = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL2,
		.bit_idx = 2,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cts_encp",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cts_encp_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_cts_enci_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VID_CLK_DIV,
		.mask = 0xf,
		.shअगरt = 28,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cts_enci_sel",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_hws = meson8b_vclk_enc_mux_parent_hws,
		.num_parents = ARRAY_SIZE(meson8b_vclk_enc_mux_parent_hws),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_cts_enci = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL2,
		.bit_idx = 0,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cts_enci",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cts_enci_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_hdmi_tx_pixel_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_HDMI_CLK_CNTL,
		.mask = 0xf,
		.shअगरt = 16,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "hdmi_tx_pixel_sel",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_hws = meson8b_vclk_enc_mux_parent_hws,
		.num_parents = ARRAY_SIZE(meson8b_vclk_enc_mux_parent_hws),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_hdmi_tx_pixel = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL2,
		.bit_idx = 5,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "hdmi_tx_pixel",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_hdmi_tx_pixel_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_hw *meson8b_vclk2_enc_mux_parent_hws[] = अणु
	&meson8b_vclk2_भाग1_gate.hw,
	&meson8b_vclk2_भाग2_भाग_gate.hw,
	&meson8b_vclk2_भाग4_भाग_gate.hw,
	&meson8b_vclk2_भाग6_भाग_gate.hw,
	&meson8b_vclk2_भाग12_भाग_gate.hw,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_cts_encl_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VIID_CLK_DIV,
		.mask = 0xf,
		.shअगरt = 12,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cts_encl_sel",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_hws = meson8b_vclk2_enc_mux_parent_hws,
		.num_parents = ARRAY_SIZE(meson8b_vclk2_enc_mux_parent_hws),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_cts_encl = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL2,
		.bit_idx = 3,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cts_encl",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cts_encl_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_cts_vdac0_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VIID_CLK_DIV,
		.mask = 0xf,
		.shअगरt = 28,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cts_vdac0_sel",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_hws = meson8b_vclk2_enc_mux_parent_hws,
		.num_parents = ARRAY_SIZE(meson8b_vclk2_enc_mux_parent_hws),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_cts_vdac0 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL2,
		.bit_idx = 4,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cts_vdac0",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cts_vdac0_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_hdmi_sys_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_HDMI_CLK_CNTL,
		.mask = 0x3,
		.shअगरt = 9,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "hdmi_sys_sel",
		.ops = &clk_regmap_mux_ops,
		/* FIXME: all other parents are unknown */
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			.fw_name = "xtal",
			.name = "xtal",
			.index = -1,
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_NO_REPARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_hdmi_sys_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_HDMI_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "hdmi_sys_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_hdmi_sys_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_hdmi_sys = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_HDMI_CLK_CNTL,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "hdmi_sys",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_hdmi_sys_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/*
 * The MALI IP is घड़ीed by two identical घड़ीs (mali_0 and mali_1)
 * muxed by a glitch-मुक्त चयन on Meson8b and Meson8m2. The CCF can
 * actually manage this glitch-मुक्त mux because it करोes top-to-bottom
 * updates the each घड़ी tree and चयनes to the "inactive" one when
 * CLK_SET_RATE_GATE is set.
 * Meson8 only has mali_0 and no glitch-मुक्त mux.
 */
अटल स्थिर काष्ठा clk_parent_data meson8b_mali_0_1_parent_data[] = अणु
	अणु .fw_name = "xtal", .name = "xtal", .index = -1, पूर्ण,
	अणु .hw = &meson8b_mpll2.hw, पूर्ण,
	अणु .hw = &meson8b_mpll1.hw, पूर्ण,
	अणु .hw = &meson8b_fclk_भाग7.hw, पूर्ण,
	अणु .hw = &meson8b_fclk_भाग4.hw, पूर्ण,
	अणु .hw = &meson8b_fclk_भाग3.hw, पूर्ण,
	अणु .hw = &meson8b_fclk_भाग5.hw, पूर्ण,
पूर्ण;

अटल u32 meson8b_mali_0_1_mux_table[] = अणु 0, 2, 3, 4, 5, 6, 7 पूर्ण;

अटल काष्ठा clk_regmap meson8b_mali_0_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_MALI_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 9,
		.table = meson8b_mali_0_1_mux_table,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mali_0_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_data = meson8b_mali_0_1_parent_data,
		.num_parents = ARRAY_SIZE(meson8b_mali_0_1_parent_data),
		/*
		 * Don't propagate rate changes up because the only changeable
		 * parents are mpll1 and mpll2 but we need those क्रम audio and
		 * RGMII (Ethernet). We करोn't want to change the audio or
		 * Ethernet घड़ीs when setting the GPU frequency.
		 */
		.flags = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_mali_0_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_MALI_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mali_0_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_mali_0_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_mali_0 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MALI_CLK_CNTL,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mali_0",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_mali_0_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_GATE | CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_mali_1_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_MALI_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 25,
		.table = meson8b_mali_0_1_mux_table,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mali_1_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_data = meson8b_mali_0_1_parent_data,
		.num_parents = ARRAY_SIZE(meson8b_mali_0_1_parent_data),
		/*
		 * Don't propagate rate changes up because the only changeable
		 * parents are mpll1 and mpll2 but we need those क्रम audio and
		 * RGMII (Ethernet). We करोn't want to change the audio or
		 * Ethernet घड़ीs when setting the GPU frequency.
		 */
		.flags = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_mali_1_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_MALI_CLK_CNTL,
		.shअगरt = 16,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mali_1_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_mali_1_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_mali_1 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MALI_CLK_CNTL,
		.bit_idx = 24,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mali_1",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_mali_1_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_GATE | CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_mali = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_MALI_CLK_CNTL,
		.mask = 1,
		.shअगरt = 31,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mali",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_mali_0.hw,
			&meson8b_mali_1.hw,
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence meson8m2_gp_pll_init_regs[] = अणु
	अणु .reg = HHI_GP_PLL_CNTL2,	.def = 0x59c88000 पूर्ण,
	अणु .reg = HHI_GP_PLL_CNTL3,	.def = 0xca463823 पूर्ण,
	अणु .reg = HHI_GP_PLL_CNTL4,	.def = 0x0286a027 पूर्ण,
	अणु .reg = HHI_GP_PLL_CNTL5,	.def = 0x00003000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pll_params_table meson8m2_gp_pll_params_table[] = अणु
	PLL_PARAMS(182, 3),
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8m2_gp_pll_dco = अणु
	.data = &(काष्ठा meson_clk_pll_data)अणु
		.en = अणु
			.reg_off = HHI_GP_PLL_CNTL,
			.shअगरt   = 30,
			.width   = 1,
		पूर्ण,
		.m = अणु
			.reg_off = HHI_GP_PLL_CNTL,
			.shअगरt   = 0,
			.width   = 9,
		पूर्ण,
		.n = अणु
			.reg_off = HHI_GP_PLL_CNTL,
			.shअगरt   = 9,
			.width   = 5,
		पूर्ण,
		.l = अणु
			.reg_off = HHI_GP_PLL_CNTL,
			.shअगरt   = 31,
			.width   = 1,
		पूर्ण,
		.rst = अणु
			.reg_off = HHI_GP_PLL_CNTL,
			.shअगरt   = 29,
			.width   = 1,
		पूर्ण,
		.table = meson8m2_gp_pll_params_table,
		.init_regs = meson8m2_gp_pll_init_regs,
		.init_count = ARRAY_SIZE(meson8m2_gp_pll_init_regs),
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gp_pll_dco",
		.ops = &meson_clk_pll_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			.fw_name = "xtal",
			.name = "xtal",
			.index = -1,
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8m2_gp_pll = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_GP_PLL_CNTL,
		.shअगरt = 16,
		.width = 2,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gp_pll",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8m2_gp_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_hw *meson8b_vpu_0_1_parent_hws[] = अणु
	&meson8b_fclk_भाग4.hw,
	&meson8b_fclk_भाग3.hw,
	&meson8b_fclk_भाग5.hw,
	&meson8b_fclk_भाग7.hw,
पूर्ण;

अटल स्थिर काष्ठा clk_hw *mmeson8m2_vpu_0_1_parent_hws[] = अणु
	&meson8b_fclk_भाग4.hw,
	&meson8b_fclk_भाग3.hw,
	&meson8b_fclk_भाग5.hw,
	&meson8m2_gp_pll.hw,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vpu_0_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.mask = 0x3,
		.shअगरt = 9,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vpu_0_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = meson8b_vpu_0_1_parent_hws,
		.num_parents = ARRAY_SIZE(meson8b_vpu_0_1_parent_hws),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8m2_vpu_0_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.mask = 0x3,
		.shअगरt = 9,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vpu_0_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = mmeson8m2_vpu_0_1_parent_hws,
		.num_parents = ARRAY_SIZE(mmeson8m2_vpu_0_1_parent_hws),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vpu_0_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vpu_0_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			/*
			 * Note:
			 * meson8b and meson8m2 have dअगरferent vpu_0_sels (with
			 * dअगरferent काष्ठा clk_hw). We fallback to the global
			 * naming string mechanism so vpu_0_भाग picks up the
			 * appropriate one.
			 */
			.name = "vpu_0_sel",
			.index = -1,
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vpu_0 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vpu_0",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vpu_0_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_GATE | CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vpu_1_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.mask = 0x3,
		.shअगरt = 25,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vpu_1_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = meson8b_vpu_0_1_parent_hws,
		.num_parents = ARRAY_SIZE(meson8b_vpu_0_1_parent_hws),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8m2_vpu_1_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.mask = 0x3,
		.shअगरt = 25,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vpu_1_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = mmeson8m2_vpu_0_1_parent_hws,
		.num_parents = ARRAY_SIZE(mmeson8m2_vpu_0_1_parent_hws),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vpu_1_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.shअगरt = 16,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vpu_1_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			/*
			 * Note:
			 * meson8b and meson8m2 have dअगरferent vpu_1_sels (with
			 * dअगरferent काष्ठा clk_hw). We fallback to the global
			 * naming string mechanism so vpu_1_भाग picks up the
			 * appropriate one.
			 */
			.name = "vpu_1_sel",
			.index = -1,
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vpu_1 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.bit_idx = 24,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vpu_1",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vpu_1_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_GATE | CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/*
 * The VPU घड़ी has two two identical घड़ी trees (vpu_0 and vpu_1)
 * muxed by a glitch-मुक्त चयन on Meson8b and Meson8m2. The CCF can
 * actually manage this glitch-मुक्त mux because it करोes top-to-bottom
 * updates the each घड़ी tree and चयनes to the "inactive" one when
 * CLK_SET_RATE_GATE is set.
 * Meson8 only has vpu_0 and no glitch-मुक्त mux.
 */
अटल काष्ठा clk_regmap meson8b_vpu = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.mask = 1,
		.shअगरt = 31,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vpu",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vpu_0.hw,
			&meson8b_vpu_1.hw,
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_hw *meson8b_vdec_parent_hws[] = अणु
	&meson8b_fclk_भाग4.hw,
	&meson8b_fclk_भाग3.hw,
	&meson8b_fclk_भाग5.hw,
	&meson8b_fclk_भाग7.hw,
	&meson8b_mpll2.hw,
	&meson8b_mpll1.hw,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vdec_1_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VDEC_CLK_CNTL,
		.mask = 0x3,
		.shअगरt = 9,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vdec_1_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = meson8b_vdec_parent_hws,
		.num_parents = ARRAY_SIZE(meson8b_vdec_parent_hws),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vdec_1_1_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VDEC_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
		.flags = CLK_DIVIDER_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vdec_1_1_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vdec_1_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vdec_1_1 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VDEC_CLK_CNTL,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vdec_1_1",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vdec_1_1_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vdec_1_2_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VDEC3_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
		.flags = CLK_DIVIDER_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vdec_1_2_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vdec_1_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vdec_1_2 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VDEC3_CLK_CNTL,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vdec_1_2",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vdec_1_2_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vdec_1 = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VDEC3_CLK_CNTL,
		.mask = 0x1,
		.shअगरt = 15,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vdec_1",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vdec_1_1.hw,
			&meson8b_vdec_1_2.hw,
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vdec_hcodec_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VDEC_CLK_CNTL,
		.mask = 0x3,
		.shअगरt = 25,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vdec_hcodec_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = meson8b_vdec_parent_hws,
		.num_parents = ARRAY_SIZE(meson8b_vdec_parent_hws),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vdec_hcodec_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VDEC_CLK_CNTL,
		.shअगरt = 16,
		.width = 7,
		.flags = CLK_DIVIDER_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vdec_hcodec_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vdec_hcodec_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vdec_hcodec = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VDEC_CLK_CNTL,
		.bit_idx = 24,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vdec_hcodec",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vdec_hcodec_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vdec_2_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VDEC2_CLK_CNTL,
		.mask = 0x3,
		.shअगरt = 9,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vdec_2_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = meson8b_vdec_parent_hws,
		.num_parents = ARRAY_SIZE(meson8b_vdec_parent_hws),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vdec_2_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VDEC2_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
		.flags = CLK_DIVIDER_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vdec_2_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vdec_2_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vdec_2 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VDEC2_CLK_CNTL,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vdec_2",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vdec_2_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vdec_hevc_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VDEC2_CLK_CNTL,
		.mask = 0x3,
		.shअगरt = 25,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vdec_hevc_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = meson8b_vdec_parent_hws,
		.num_parents = ARRAY_SIZE(meson8b_vdec_parent_hws),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vdec_hevc_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VDEC2_CLK_CNTL,
		.shअगरt = 16,
		.width = 7,
		.flags = CLK_DIVIDER_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vdec_hevc_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vdec_hevc_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vdec_hevc_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VDEC2_CLK_CNTL,
		.bit_idx = 24,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vdec_hevc_en",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vdec_hevc_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_vdec_hevc = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VDEC2_CLK_CNTL,
		.mask = 0x1,
		.shअगरt = 31,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vdec_hevc",
		.ops = &clk_regmap_mux_ops,
		/* TODO: The second parent is currently unknown */
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_vdec_hevc_en.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* TODO: the घड़ी at index 0 is "DDR_PLL" which we करोn't support yet */
अटल स्थिर काष्ठा clk_hw *meson8b_cts_amclk_parent_hws[] = अणु
	&meson8b_mpll0.hw,
	&meson8b_mpll1.hw,
	&meson8b_mpll2.hw
पूर्ण;

अटल u32 meson8b_cts_amclk_mux_table[] = अणु 1, 2, 3 पूर्ण;

अटल काष्ठा clk_regmap meson8b_cts_amclk_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_AUD_CLK_CNTL,
		.mask = 0x3,
		.shअगरt = 9,
		.table = meson8b_cts_amclk_mux_table,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cts_amclk_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = meson8b_cts_amclk_parent_hws,
		.num_parents = ARRAY_SIZE(meson8b_cts_amclk_parent_hws),
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_cts_amclk_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data) अणु
		.offset = HHI_AUD_CLK_CNTL,
		.shअगरt = 0,
		.width = 8,
		.flags = CLK_DIVIDER_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cts_amclk_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cts_amclk_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_cts_amclk = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_AUD_CLK_CNTL,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cts_amclk",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cts_amclk_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* TODO: the घड़ी at index 0 is "DDR_PLL" which we करोn't support yet */
अटल स्थिर काष्ठा clk_hw *meson8b_cts_mclk_i958_parent_hws[] = अणु
	&meson8b_mpll0.hw,
	&meson8b_mpll1.hw,
	&meson8b_mpll2.hw
पूर्ण;

अटल u32 meson8b_cts_mclk_i958_mux_table[] = अणु 1, 2, 3 पूर्ण;

अटल काष्ठा clk_regmap meson8b_cts_mclk_i958_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_AUD_CLK_CNTL2,
		.mask = 0x3,
		.shअगरt = 25,
		.table = meson8b_cts_mclk_i958_mux_table,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "cts_mclk_i958_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = meson8b_cts_mclk_i958_parent_hws,
		.num_parents = ARRAY_SIZE(meson8b_cts_mclk_i958_parent_hws),
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_cts_mclk_i958_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_AUD_CLK_CNTL2,
		.shअगरt = 16,
		.width = 8,
		.flags = CLK_DIVIDER_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "cts_mclk_i958_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cts_mclk_i958_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_cts_mclk_i958 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_AUD_CLK_CNTL2,
		.bit_idx = 24,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cts_mclk_i958",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cts_mclk_i958_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8b_cts_i958 = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_AUD_CLK_CNTL2,
		.mask = 0x1,
		.shअगरt = 27,
		पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cts_i958",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8b_cts_amclk.hw,
			&meson8b_cts_mclk_i958.hw
		पूर्ण,
		.num_parents = 2,
		/*
		 * The parent is specअगरic to origin of the audio data. Let the
		 * consumer choose the appropriate parent.
		 */
		.flags = CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
	पूर्ण,
पूर्ण;

#घोषणा MESON_GATE(_name, _reg, _bit) \
	MESON_PCLK(_name, _reg, _bit, &meson8b_clk81.hw)

/* Everything Else (EE) करोमुख्य gates */

अटल MESON_GATE(meson8b_ddr, HHI_GCLK_MPEG0, 0);
अटल MESON_GATE(meson8b_करोs, HHI_GCLK_MPEG0, 1);
अटल MESON_GATE(meson8b_isa, HHI_GCLK_MPEG0, 5);
अटल MESON_GATE(meson8b_pl301, HHI_GCLK_MPEG0, 6);
अटल MESON_GATE(meson8b_periphs, HHI_GCLK_MPEG0, 7);
अटल MESON_GATE(meson8b_spicc, HHI_GCLK_MPEG0, 8);
अटल MESON_GATE(meson8b_i2c, HHI_GCLK_MPEG0, 9);
अटल MESON_GATE(meson8b_sar_adc, HHI_GCLK_MPEG0, 10);
अटल MESON_GATE(meson8b_smart_card, HHI_GCLK_MPEG0, 11);
अटल MESON_GATE(meson8b_rng0, HHI_GCLK_MPEG0, 12);
अटल MESON_GATE(meson8b_uart0, HHI_GCLK_MPEG0, 13);
अटल MESON_GATE(meson8b_sdhc, HHI_GCLK_MPEG0, 14);
अटल MESON_GATE(meson8b_stream, HHI_GCLK_MPEG0, 15);
अटल MESON_GATE(meson8b_async_fअगरo, HHI_GCLK_MPEG0, 16);
अटल MESON_GATE(meson8b_sdio, HHI_GCLK_MPEG0, 17);
अटल MESON_GATE(meson8b_abuf, HHI_GCLK_MPEG0, 18);
अटल MESON_GATE(meson8b_hiu_अगरace, HHI_GCLK_MPEG0, 19);
अटल MESON_GATE(meson8b_assist_misc, HHI_GCLK_MPEG0, 23);
अटल MESON_GATE(meson8b_spi, HHI_GCLK_MPEG0, 30);

अटल MESON_GATE(meson8b_i2s_spdअगर, HHI_GCLK_MPEG1, 2);
अटल MESON_GATE(meson8b_eth, HHI_GCLK_MPEG1, 3);
अटल MESON_GATE(meson8b_demux, HHI_GCLK_MPEG1, 4);
अटल MESON_GATE(meson8b_blkmv, HHI_GCLK_MPEG1, 14);
अटल MESON_GATE(meson8b_aiu, HHI_GCLK_MPEG1, 15);
अटल MESON_GATE(meson8b_uart1, HHI_GCLK_MPEG1, 16);
अटल MESON_GATE(meson8b_g2d, HHI_GCLK_MPEG1, 20);
अटल MESON_GATE(meson8b_usb0, HHI_GCLK_MPEG1, 21);
अटल MESON_GATE(meson8b_usb1, HHI_GCLK_MPEG1, 22);
अटल MESON_GATE(meson8b_reset, HHI_GCLK_MPEG1, 23);
अटल MESON_GATE(meson8b_nand, HHI_GCLK_MPEG1, 24);
अटल MESON_GATE(meson8b_करोs_parser, HHI_GCLK_MPEG1, 25);
अटल MESON_GATE(meson8b_usb, HHI_GCLK_MPEG1, 26);
अटल MESON_GATE(meson8b_vdin1, HHI_GCLK_MPEG1, 28);
अटल MESON_GATE(meson8b_ahb_arb0, HHI_GCLK_MPEG1, 29);
अटल MESON_GATE(meson8b_efuse, HHI_GCLK_MPEG1, 30);
अटल MESON_GATE(meson8b_boot_rom, HHI_GCLK_MPEG1, 31);

अटल MESON_GATE(meson8b_ahb_data_bus, HHI_GCLK_MPEG2, 1);
अटल MESON_GATE(meson8b_ahb_ctrl_bus, HHI_GCLK_MPEG2, 2);
अटल MESON_GATE(meson8b_hdmi_पूर्णांकr_sync, HHI_GCLK_MPEG2, 3);
अटल MESON_GATE(meson8b_hdmi_pclk, HHI_GCLK_MPEG2, 4);
अटल MESON_GATE(meson8b_usb1_ddr_bridge, HHI_GCLK_MPEG2, 8);
अटल MESON_GATE(meson8b_usb0_ddr_bridge, HHI_GCLK_MPEG2, 9);
अटल MESON_GATE(meson8b_mmc_pclk, HHI_GCLK_MPEG2, 11);
अटल MESON_GATE(meson8b_dvin, HHI_GCLK_MPEG2, 12);
अटल MESON_GATE(meson8b_uart2, HHI_GCLK_MPEG2, 15);
अटल MESON_GATE(meson8b_sana, HHI_GCLK_MPEG2, 22);
अटल MESON_GATE(meson8b_vpu_पूर्णांकr, HHI_GCLK_MPEG2, 25);
अटल MESON_GATE(meson8b_sec_ahb_ahb3_bridge, HHI_GCLK_MPEG2, 26);
अटल MESON_GATE(meson8b_clk81_a9, HHI_GCLK_MPEG2, 29);

अटल MESON_GATE(meson8b_vclk2_venci0, HHI_GCLK_OTHER, 1);
अटल MESON_GATE(meson8b_vclk2_venci1, HHI_GCLK_OTHER, 2);
अटल MESON_GATE(meson8b_vclk2_vencp0, HHI_GCLK_OTHER, 3);
अटल MESON_GATE(meson8b_vclk2_vencp1, HHI_GCLK_OTHER, 4);
अटल MESON_GATE(meson8b_gclk_venci_पूर्णांक, HHI_GCLK_OTHER, 8);
अटल MESON_GATE(meson8b_gclk_vencp_पूर्णांक, HHI_GCLK_OTHER, 9);
अटल MESON_GATE(meson8b_dac_clk, HHI_GCLK_OTHER, 10);
अटल MESON_GATE(meson8b_aoclk_gate, HHI_GCLK_OTHER, 14);
अटल MESON_GATE(meson8b_iec958_gate, HHI_GCLK_OTHER, 16);
अटल MESON_GATE(meson8b_enc480p, HHI_GCLK_OTHER, 20);
अटल MESON_GATE(meson8b_rng1, HHI_GCLK_OTHER, 21);
अटल MESON_GATE(meson8b_gclk_vencl_पूर्णांक, HHI_GCLK_OTHER, 22);
अटल MESON_GATE(meson8b_vclk2_venclmcc, HHI_GCLK_OTHER, 24);
अटल MESON_GATE(meson8b_vclk2_vencl, HHI_GCLK_OTHER, 25);
अटल MESON_GATE(meson8b_vclk2_other, HHI_GCLK_OTHER, 26);
अटल MESON_GATE(meson8b_edp, HHI_GCLK_OTHER, 31);

/* AIU gates */
#घोषणा MESON_AIU_GLUE_GATE(_name, _reg, _bit) \
	MESON_PCLK(_name, _reg, _bit, &meson8b_aiu_glue.hw)

अटल MESON_PCLK(meson8b_aiu_glue, HHI_GCLK_MPEG1, 6, &meson8b_aiu.hw);
अटल MESON_AIU_GLUE_GATE(meson8b_iec958, HHI_GCLK_MPEG1, 7);
अटल MESON_AIU_GLUE_GATE(meson8b_i2s_out, HHI_GCLK_MPEG1, 8);
अटल MESON_AIU_GLUE_GATE(meson8b_amclk, HHI_GCLK_MPEG1, 9);
अटल MESON_AIU_GLUE_GATE(meson8b_aअगरअगरo2, HHI_GCLK_MPEG1, 10);
अटल MESON_AIU_GLUE_GATE(meson8b_mixer, HHI_GCLK_MPEG1, 11);
अटल MESON_AIU_GLUE_GATE(meson8b_mixer_अगरace, HHI_GCLK_MPEG1, 12);
अटल MESON_AIU_GLUE_GATE(meson8b_adc, HHI_GCLK_MPEG1, 13);

/* Always On (AO) करोमुख्य gates */

अटल MESON_GATE(meson8b_ao_media_cpu, HHI_GCLK_AO, 0);
अटल MESON_GATE(meson8b_ao_ahb_sram, HHI_GCLK_AO, 1);
अटल MESON_GATE(meson8b_ao_ahb_bus, HHI_GCLK_AO, 2);
अटल MESON_GATE(meson8b_ao_अगरace, HHI_GCLK_AO, 3);

अटल काष्ठा clk_hw_onecell_data meson8_hw_onecell_data = अणु
	.hws = अणु
		[CLKID_PLL_FIXED] = &meson8b_fixed_pll.hw,
		[CLKID_PLL_VID] = &meson8b_vid_pll.hw,
		[CLKID_PLL_SYS] = &meson8b_sys_pll.hw,
		[CLKID_FCLK_DIV2] = &meson8b_fclk_भाग2.hw,
		[CLKID_FCLK_DIV3] = &meson8b_fclk_भाग3.hw,
		[CLKID_FCLK_DIV4] = &meson8b_fclk_भाग4.hw,
		[CLKID_FCLK_DIV5] = &meson8b_fclk_भाग5.hw,
		[CLKID_FCLK_DIV7] = &meson8b_fclk_भाग7.hw,
		[CLKID_CPUCLK] = &meson8b_cpu_clk.hw,
		[CLKID_MPEG_SEL] = &meson8b_mpeg_clk_sel.hw,
		[CLKID_MPEG_DIV] = &meson8b_mpeg_clk_भाग.hw,
		[CLKID_CLK81] = &meson8b_clk81.hw,
		[CLKID_DDR]		    = &meson8b_ddr.hw,
		[CLKID_DOS]		    = &meson8b_डॉस.सw,
		[CLKID_ISA]		    = &meson8b_isa.hw,
		[CLKID_PL301]		    = &meson8b_pl301.hw,
		[CLKID_PERIPHS]		    = &meson8b_periphs.hw,
		[CLKID_SPICC]		    = &meson8b_spicc.hw,
		[CLKID_I2C]		    = &meson8b_i2c.hw,
		[CLKID_SAR_ADC]		    = &meson8b_sar_adc.hw,
		[CLKID_SMART_CARD]	    = &meson8b_smart_card.hw,
		[CLKID_RNG0]		    = &meson8b_rng0.hw,
		[CLKID_UART0]		    = &meson8b_uart0.hw,
		[CLKID_SDHC]		    = &meson8b_sdhc.hw,
		[CLKID_STREAM]		    = &meson8b_stream.hw,
		[CLKID_ASYNC_FIFO]	    = &meson8b_async_fअगरo.hw,
		[CLKID_SDIO]		    = &meson8b_sdपन.सw,
		[CLKID_ABUF]		    = &meson8b_abuf.hw,
		[CLKID_HIU_IFACE]	    = &meson8b_hiu_अगरace.hw,
		[CLKID_ASSIST_MISC]	    = &meson8b_assist_misc.hw,
		[CLKID_SPI]		    = &meson8b_spi.hw,
		[CLKID_I2S_SPDIF]	    = &meson8b_i2s_spdअगर.hw,
		[CLKID_ETH]		    = &meson8b_eth.hw,
		[CLKID_DEMUX]		    = &meson8b_demux.hw,
		[CLKID_AIU_GLUE]	    = &meson8b_aiu_glue.hw,
		[CLKID_IEC958]		    = &meson8b_iec958.hw,
		[CLKID_I2S_OUT]		    = &meson8b_i2s_out.hw,
		[CLKID_AMCLK]		    = &meson8b_amclk.hw,
		[CLKID_AIFIFO2]		    = &meson8b_aअगरअगरo2.hw,
		[CLKID_MIXER]		    = &meson8b_mixer.hw,
		[CLKID_MIXER_IFACE]	    = &meson8b_mixer_अगरace.hw,
		[CLKID_ADC]		    = &meson8b_adc.hw,
		[CLKID_BLKMV]		    = &meson8b_blkmv.hw,
		[CLKID_AIU]		    = &meson8b_aiu.hw,
		[CLKID_UART1]		    = &meson8b_uart1.hw,
		[CLKID_G2D]		    = &meson8b_g2d.hw,
		[CLKID_USB0]		    = &meson8b_usb0.hw,
		[CLKID_USB1]		    = &meson8b_usb1.hw,
		[CLKID_RESET]		    = &meson8b_reset.hw,
		[CLKID_न_अंकD]		    = &meson8b_nand.hw,
		[CLKID_DOS_PARSER]	    = &meson8b_करोs_parser.hw,
		[CLKID_USB]		    = &meson8b_usb.hw,
		[CLKID_VDIN1]		    = &meson8b_vdin1.hw,
		[CLKID_AHB_ARB0]	    = &meson8b_ahb_arb0.hw,
		[CLKID_EFUSE]		    = &meson8b_efuse.hw,
		[CLKID_BOOT_ROM]	    = &meson8b_boot_rom.hw,
		[CLKID_AHB_DATA_BUS]	    = &meson8b_ahb_data_bus.hw,
		[CLKID_AHB_CTRL_BUS]	    = &meson8b_ahb_ctrl_bus.hw,
		[CLKID_HDMI_INTR_SYNC]	    = &meson8b_hdmi_पूर्णांकr_sync.hw,
		[CLKID_HDMI_PCLK]	    = &meson8b_hdmi_pclk.hw,
		[CLKID_USB1_DDR_BRIDGE]	    = &meson8b_usb1_ddr_bridge.hw,
		[CLKID_USB0_DDR_BRIDGE]	    = &meson8b_usb0_ddr_bridge.hw,
		[CLKID_MMC_PCLK]	    = &meson8b_mmc_pclk.hw,
		[CLKID_DVIN]		    = &meson8b_dvin.hw,
		[CLKID_UART2]		    = &meson8b_uart2.hw,
		[CLKID_SANA]		    = &meson8b_sana.hw,
		[CLKID_VPU_INTR]	    = &meson8b_vpu_पूर्णांकr.hw,
		[CLKID_SEC_AHB_AHB3_BRIDGE] = &meson8b_sec_ahb_ahb3_bridge.hw,
		[CLKID_CLK81_A9]	    = &meson8b_clk81_a9.hw,
		[CLKID_VCLK2_VENCI0]	    = &meson8b_vclk2_venci0.hw,
		[CLKID_VCLK2_VENCI1]	    = &meson8b_vclk2_venci1.hw,
		[CLKID_VCLK2_VENCP0]	    = &meson8b_vclk2_vencp0.hw,
		[CLKID_VCLK2_VENCP1]	    = &meson8b_vclk2_vencp1.hw,
		[CLKID_GCLK_VENCI_INT]	    = &meson8b_gclk_venci_पूर्णांक.hw,
		[CLKID_GCLK_VENCP_INT]	    = &meson8b_gclk_vencp_पूर्णांक.hw,
		[CLKID_DAC_CLK]		    = &meson8b_dac_clk.hw,
		[CLKID_AOCLK_GATE]	    = &meson8b_aoclk_gate.hw,
		[CLKID_IEC958_GATE]	    = &meson8b_iec958_gate.hw,
		[CLKID_ENC480P]		    = &meson8b_enc480p.hw,
		[CLKID_RNG1]		    = &meson8b_rng1.hw,
		[CLKID_GCLK_VENCL_INT]	    = &meson8b_gclk_vencl_पूर्णांक.hw,
		[CLKID_VCLK2_VENCLMCC]	    = &meson8b_vclk2_venclmcc.hw,
		[CLKID_VCLK2_VENCL]	    = &meson8b_vclk2_vencl.hw,
		[CLKID_VCLK2_OTHER]	    = &meson8b_vclk2_other.hw,
		[CLKID_EDP]		    = &meson8b_edp.hw,
		[CLKID_AO_MEDIA_CPU]	    = &meson8b_ao_media_cpu.hw,
		[CLKID_AO_AHB_SRAM]	    = &meson8b_ao_ahb_sram.hw,
		[CLKID_AO_AHB_BUS]	    = &meson8b_ao_ahb_bus.hw,
		[CLKID_AO_IFACE]	    = &meson8b_ao_अगरace.hw,
		[CLKID_MPLL0]		    = &meson8b_mpll0.hw,
		[CLKID_MPLL1]		    = &meson8b_mpll1.hw,
		[CLKID_MPLL2]		    = &meson8b_mpll2.hw,
		[CLKID_MPLL0_DIV]	    = &meson8b_mpll0_भाग.hw,
		[CLKID_MPLL1_DIV]	    = &meson8b_mpll1_भाग.hw,
		[CLKID_MPLL2_DIV]	    = &meson8b_mpll2_भाग.hw,
		[CLKID_CPU_IN_SEL]	    = &meson8b_cpu_in_sel.hw,
		[CLKID_CPU_IN_DIV2]	    = &meson8b_cpu_in_भाग2.hw,
		[CLKID_CPU_IN_DIV3]	    = &meson8b_cpu_in_भाग3.hw,
		[CLKID_CPU_SCALE_DIV]	    = &meson8b_cpu_scale_भाग.hw,
		[CLKID_CPU_SCALE_OUT_SEL]   = &meson8b_cpu_scale_out_sel.hw,
		[CLKID_MPLL_PREDIV]	    = &meson8b_mpll_preभाग.hw,
		[CLKID_FCLK_DIV2_DIV]	    = &meson8b_fclk_भाग2_भाग.hw,
		[CLKID_FCLK_DIV3_DIV]	    = &meson8b_fclk_भाग3_भाग.hw,
		[CLKID_FCLK_DIV4_DIV]	    = &meson8b_fclk_भाग4_भाग.hw,
		[CLKID_FCLK_DIV5_DIV]	    = &meson8b_fclk_भाग5_भाग.hw,
		[CLKID_FCLK_DIV7_DIV]	    = &meson8b_fclk_भाग7_भाग.hw,
		[CLKID_न_अंकD_SEL]	    = &meson8b_nand_clk_sel.hw,
		[CLKID_न_अंकD_DIV]	    = &meson8b_nand_clk_भाग.hw,
		[CLKID_न_अंकD_CLK]	    = &meson8b_nand_clk_gate.hw,
		[CLKID_PLL_FIXED_DCO]	    = &meson8b_fixed_pll_dco.hw,
		[CLKID_HDMI_PLL_DCO]	    = &meson8b_hdmi_pll_dco.hw,
		[CLKID_PLL_SYS_DCO]	    = &meson8b_sys_pll_dco.hw,
		[CLKID_CPU_CLK_DIV2]	    = &meson8b_cpu_clk_भाग2.hw,
		[CLKID_CPU_CLK_DIV3]	    = &meson8b_cpu_clk_भाग3.hw,
		[CLKID_CPU_CLK_DIV4]	    = &meson8b_cpu_clk_भाग4.hw,
		[CLKID_CPU_CLK_DIV5]	    = &meson8b_cpu_clk_भाग5.hw,
		[CLKID_CPU_CLK_DIV6]	    = &meson8b_cpu_clk_भाग6.hw,
		[CLKID_CPU_CLK_DIV7]	    = &meson8b_cpu_clk_भाग7.hw,
		[CLKID_CPU_CLK_DIV8]	    = &meson8b_cpu_clk_भाग8.hw,
		[CLKID_APB_SEL]		    = &meson8b_apb_clk_sel.hw,
		[CLKID_APB]		    = &meson8b_apb_clk_gate.hw,
		[CLKID_PERIPH_SEL]	    = &meson8b_periph_clk_sel.hw,
		[CLKID_PERIPH]		    = &meson8b_periph_clk_gate.hw,
		[CLKID_AXI_SEL]		    = &meson8b_axi_clk_sel.hw,
		[CLKID_AXI]		    = &meson8b_axi_clk_gate.hw,
		[CLKID_L2_DRAM_SEL]	    = &meson8b_l2_dram_clk_sel.hw,
		[CLKID_L2_DRAM]		    = &meson8b_l2_dram_clk_gate.hw,
		[CLKID_HDMI_PLL_LVDS_OUT]   = &meson8b_hdmi_pll_lvds_out.hw,
		[CLKID_HDMI_PLL_HDMI_OUT]   = &meson8b_hdmi_pll_hdmi_out.hw,
		[CLKID_VID_PLL_IN_SEL]	    = &meson8b_vid_pll_in_sel.hw,
		[CLKID_VID_PLL_IN_EN]	    = &meson8b_vid_pll_in_en.hw,
		[CLKID_VID_PLL_PRE_DIV]	    = &meson8b_vid_pll_pre_भाग.hw,
		[CLKID_VID_PLL_POST_DIV]    = &meson8b_vid_pll_post_भाग.hw,
		[CLKID_VID_PLL_FINAL_DIV]   = &meson8b_vid_pll_final_भाग.hw,
		[CLKID_VCLK_IN_SEL]	    = &meson8b_vclk_in_sel.hw,
		[CLKID_VCLK_IN_EN]	    = &meson8b_vclk_in_en.hw,
		[CLKID_VCLK_EN]		    = &meson8b_vclk_en.hw,
		[CLKID_VCLK_DIV1]	    = &meson8b_vclk_भाग1_gate.hw,
		[CLKID_VCLK_DIV2_DIV]	    = &meson8b_vclk_भाग2_भाग.hw,
		[CLKID_VCLK_DIV2]	    = &meson8b_vclk_भाग2_भाग_gate.hw,
		[CLKID_VCLK_DIV4_DIV]	    = &meson8b_vclk_भाग4_भाग.hw,
		[CLKID_VCLK_DIV4]	    = &meson8b_vclk_भाग4_भाग_gate.hw,
		[CLKID_VCLK_DIV6_DIV]	    = &meson8b_vclk_भाग6_भाग.hw,
		[CLKID_VCLK_DIV6]	    = &meson8b_vclk_भाग6_भाग_gate.hw,
		[CLKID_VCLK_DIV12_DIV]	    = &meson8b_vclk_भाग12_भाग.hw,
		[CLKID_VCLK_DIV12]	    = &meson8b_vclk_भाग12_भाग_gate.hw,
		[CLKID_VCLK2_IN_SEL]	    = &meson8b_vclk2_in_sel.hw,
		[CLKID_VCLK2_IN_EN]	    = &meson8b_vclk2_clk_in_en.hw,
		[CLKID_VCLK2_EN]	    = &meson8b_vclk2_clk_en.hw,
		[CLKID_VCLK2_DIV1]	    = &meson8b_vclk2_भाग1_gate.hw,
		[CLKID_VCLK2_DIV2_DIV]	    = &meson8b_vclk2_भाग2_भाग.hw,
		[CLKID_VCLK2_DIV2]	    = &meson8b_vclk2_भाग2_भाग_gate.hw,
		[CLKID_VCLK2_DIV4_DIV]	    = &meson8b_vclk2_भाग4_भाग.hw,
		[CLKID_VCLK2_DIV4]	    = &meson8b_vclk2_भाग4_भाग_gate.hw,
		[CLKID_VCLK2_DIV6_DIV]	    = &meson8b_vclk2_भाग6_भाग.hw,
		[CLKID_VCLK2_DIV6]	    = &meson8b_vclk2_भाग6_भाग_gate.hw,
		[CLKID_VCLK2_DIV12_DIV]	    = &meson8b_vclk2_भाग12_भाग.hw,
		[CLKID_VCLK2_DIV12]	    = &meson8b_vclk2_भाग12_भाग_gate.hw,
		[CLKID_CTS_ENCT_SEL]	    = &meson8b_cts_enct_sel.hw,
		[CLKID_CTS_ENCT]	    = &meson8b_cts_enct.hw,
		[CLKID_CTS_ENCP_SEL]	    = &meson8b_cts_encp_sel.hw,
		[CLKID_CTS_ENCP]	    = &meson8b_cts_encp.hw,
		[CLKID_CTS_ENCI_SEL]	    = &meson8b_cts_enci_sel.hw,
		[CLKID_CTS_ENCI]	    = &meson8b_cts_enci.hw,
		[CLKID_HDMI_TX_PIXEL_SEL]   = &meson8b_hdmi_tx_pixel_sel.hw,
		[CLKID_HDMI_TX_PIXEL]	    = &meson8b_hdmi_tx_pixel.hw,
		[CLKID_CTS_ENCL_SEL]	    = &meson8b_cts_encl_sel.hw,
		[CLKID_CTS_ENCL]	    = &meson8b_cts_encl.hw,
		[CLKID_CTS_VDAC0_SEL]	    = &meson8b_cts_vdac0_sel.hw,
		[CLKID_CTS_VDAC0]	    = &meson8b_cts_vdac0.hw,
		[CLKID_HDMI_SYS_SEL]	    = &meson8b_hdmi_sys_sel.hw,
		[CLKID_HDMI_SYS_DIV]	    = &meson8b_hdmi_sys_भाग.hw,
		[CLKID_HDMI_SYS]	    = &meson8b_hdmi_sys.hw,
		[CLKID_MALI_0_SEL]	    = &meson8b_mali_0_sel.hw,
		[CLKID_MALI_0_DIV]	    = &meson8b_mali_0_भाग.hw,
		[CLKID_MALI]		    = &meson8b_mali_0.hw,
		[CLKID_VPU_0_SEL]	    = &meson8b_vpu_0_sel.hw,
		[CLKID_VPU_0_DIV]	    = &meson8b_vpu_0_भाग.hw,
		[CLKID_VPU]		    = &meson8b_vpu_0.hw,
		[CLKID_VDEC_1_SEL]	    = &meson8b_vdec_1_sel.hw,
		[CLKID_VDEC_1_1_DIV]	    = &meson8b_vdec_1_1_भाग.hw,
		[CLKID_VDEC_1]	   	    = &meson8b_vdec_1_1.hw,
		[CLKID_VDEC_HCODEC_SEL]	    = &meson8b_vdec_hcodec_sel.hw,
		[CLKID_VDEC_HCODEC_DIV]	    = &meson8b_vdec_hcodec_भाग.hw,
		[CLKID_VDEC_HCODEC]	    = &meson8b_vdec_hcodec.hw,
		[CLKID_VDEC_2_SEL]	    = &meson8b_vdec_2_sel.hw,
		[CLKID_VDEC_2_DIV]	    = &meson8b_vdec_2_भाग.hw,
		[CLKID_VDEC_2]	    	    = &meson8b_vdec_2.hw,
		[CLKID_VDEC_HEVC_SEL]	    = &meson8b_vdec_hevc_sel.hw,
		[CLKID_VDEC_HEVC_DIV]	    = &meson8b_vdec_hevc_भाग.hw,
		[CLKID_VDEC_HEVC_EN]	    = &meson8b_vdec_hevc_en.hw,
		[CLKID_VDEC_HEVC]	    = &meson8b_vdec_hevc.hw,
		[CLKID_CTS_AMCLK_SEL]	    = &meson8b_cts_amclk_sel.hw,
		[CLKID_CTS_AMCLK_DIV]	    = &meson8b_cts_amclk_भाग.hw,
		[CLKID_CTS_AMCLK]	    = &meson8b_cts_amclk.hw,
		[CLKID_CTS_MCLK_I958_SEL]   = &meson8b_cts_mclk_i958_sel.hw,
		[CLKID_CTS_MCLK_I958_DIV]   = &meson8b_cts_mclk_i958_भाग.hw,
		[CLKID_CTS_MCLK_I958]	    = &meson8b_cts_mclk_i958.hw,
		[CLKID_CTS_I958]	    = &meson8b_cts_i958.hw,
		[CLK_NR_CLKS]		    = शून्य,
	पूर्ण,
	.num = CLK_NR_CLKS,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data meson8b_hw_onecell_data = अणु
	.hws = अणु
		[CLKID_PLL_FIXED] = &meson8b_fixed_pll.hw,
		[CLKID_PLL_VID] = &meson8b_vid_pll.hw,
		[CLKID_PLL_SYS] = &meson8b_sys_pll.hw,
		[CLKID_FCLK_DIV2] = &meson8b_fclk_भाग2.hw,
		[CLKID_FCLK_DIV3] = &meson8b_fclk_भाग3.hw,
		[CLKID_FCLK_DIV4] = &meson8b_fclk_भाग4.hw,
		[CLKID_FCLK_DIV5] = &meson8b_fclk_भाग5.hw,
		[CLKID_FCLK_DIV7] = &meson8b_fclk_भाग7.hw,
		[CLKID_CPUCLK] = &meson8b_cpu_clk.hw,
		[CLKID_MPEG_SEL] = &meson8b_mpeg_clk_sel.hw,
		[CLKID_MPEG_DIV] = &meson8b_mpeg_clk_भाग.hw,
		[CLKID_CLK81] = &meson8b_clk81.hw,
		[CLKID_DDR]		    = &meson8b_ddr.hw,
		[CLKID_DOS]		    = &meson8b_डॉस.सw,
		[CLKID_ISA]		    = &meson8b_isa.hw,
		[CLKID_PL301]		    = &meson8b_pl301.hw,
		[CLKID_PERIPHS]		    = &meson8b_periphs.hw,
		[CLKID_SPICC]		    = &meson8b_spicc.hw,
		[CLKID_I2C]		    = &meson8b_i2c.hw,
		[CLKID_SAR_ADC]		    = &meson8b_sar_adc.hw,
		[CLKID_SMART_CARD]	    = &meson8b_smart_card.hw,
		[CLKID_RNG0]		    = &meson8b_rng0.hw,
		[CLKID_UART0]		    = &meson8b_uart0.hw,
		[CLKID_SDHC]		    = &meson8b_sdhc.hw,
		[CLKID_STREAM]		    = &meson8b_stream.hw,
		[CLKID_ASYNC_FIFO]	    = &meson8b_async_fअगरo.hw,
		[CLKID_SDIO]		    = &meson8b_sdपन.सw,
		[CLKID_ABUF]		    = &meson8b_abuf.hw,
		[CLKID_HIU_IFACE]	    = &meson8b_hiu_अगरace.hw,
		[CLKID_ASSIST_MISC]	    = &meson8b_assist_misc.hw,
		[CLKID_SPI]		    = &meson8b_spi.hw,
		[CLKID_I2S_SPDIF]	    = &meson8b_i2s_spdअगर.hw,
		[CLKID_ETH]		    = &meson8b_eth.hw,
		[CLKID_DEMUX]		    = &meson8b_demux.hw,
		[CLKID_AIU_GLUE]	    = &meson8b_aiu_glue.hw,
		[CLKID_IEC958]		    = &meson8b_iec958.hw,
		[CLKID_I2S_OUT]		    = &meson8b_i2s_out.hw,
		[CLKID_AMCLK]		    = &meson8b_amclk.hw,
		[CLKID_AIFIFO2]		    = &meson8b_aअगरअगरo2.hw,
		[CLKID_MIXER]		    = &meson8b_mixer.hw,
		[CLKID_MIXER_IFACE]	    = &meson8b_mixer_अगरace.hw,
		[CLKID_ADC]		    = &meson8b_adc.hw,
		[CLKID_BLKMV]		    = &meson8b_blkmv.hw,
		[CLKID_AIU]		    = &meson8b_aiu.hw,
		[CLKID_UART1]		    = &meson8b_uart1.hw,
		[CLKID_G2D]		    = &meson8b_g2d.hw,
		[CLKID_USB0]		    = &meson8b_usb0.hw,
		[CLKID_USB1]		    = &meson8b_usb1.hw,
		[CLKID_RESET]		    = &meson8b_reset.hw,
		[CLKID_न_अंकD]		    = &meson8b_nand.hw,
		[CLKID_DOS_PARSER]	    = &meson8b_करोs_parser.hw,
		[CLKID_USB]		    = &meson8b_usb.hw,
		[CLKID_VDIN1]		    = &meson8b_vdin1.hw,
		[CLKID_AHB_ARB0]	    = &meson8b_ahb_arb0.hw,
		[CLKID_EFUSE]		    = &meson8b_efuse.hw,
		[CLKID_BOOT_ROM]	    = &meson8b_boot_rom.hw,
		[CLKID_AHB_DATA_BUS]	    = &meson8b_ahb_data_bus.hw,
		[CLKID_AHB_CTRL_BUS]	    = &meson8b_ahb_ctrl_bus.hw,
		[CLKID_HDMI_INTR_SYNC]	    = &meson8b_hdmi_पूर्णांकr_sync.hw,
		[CLKID_HDMI_PCLK]	    = &meson8b_hdmi_pclk.hw,
		[CLKID_USB1_DDR_BRIDGE]	    = &meson8b_usb1_ddr_bridge.hw,
		[CLKID_USB0_DDR_BRIDGE]	    = &meson8b_usb0_ddr_bridge.hw,
		[CLKID_MMC_PCLK]	    = &meson8b_mmc_pclk.hw,
		[CLKID_DVIN]		    = &meson8b_dvin.hw,
		[CLKID_UART2]		    = &meson8b_uart2.hw,
		[CLKID_SANA]		    = &meson8b_sana.hw,
		[CLKID_VPU_INTR]	    = &meson8b_vpu_पूर्णांकr.hw,
		[CLKID_SEC_AHB_AHB3_BRIDGE] = &meson8b_sec_ahb_ahb3_bridge.hw,
		[CLKID_CLK81_A9]	    = &meson8b_clk81_a9.hw,
		[CLKID_VCLK2_VENCI0]	    = &meson8b_vclk2_venci0.hw,
		[CLKID_VCLK2_VENCI1]	    = &meson8b_vclk2_venci1.hw,
		[CLKID_VCLK2_VENCP0]	    = &meson8b_vclk2_vencp0.hw,
		[CLKID_VCLK2_VENCP1]	    = &meson8b_vclk2_vencp1.hw,
		[CLKID_GCLK_VENCI_INT]	    = &meson8b_gclk_venci_पूर्णांक.hw,
		[CLKID_GCLK_VENCP_INT]	    = &meson8b_gclk_vencp_पूर्णांक.hw,
		[CLKID_DAC_CLK]		    = &meson8b_dac_clk.hw,
		[CLKID_AOCLK_GATE]	    = &meson8b_aoclk_gate.hw,
		[CLKID_IEC958_GATE]	    = &meson8b_iec958_gate.hw,
		[CLKID_ENC480P]		    = &meson8b_enc480p.hw,
		[CLKID_RNG1]		    = &meson8b_rng1.hw,
		[CLKID_GCLK_VENCL_INT]	    = &meson8b_gclk_vencl_पूर्णांक.hw,
		[CLKID_VCLK2_VENCLMCC]	    = &meson8b_vclk2_venclmcc.hw,
		[CLKID_VCLK2_VENCL]	    = &meson8b_vclk2_vencl.hw,
		[CLKID_VCLK2_OTHER]	    = &meson8b_vclk2_other.hw,
		[CLKID_EDP]		    = &meson8b_edp.hw,
		[CLKID_AO_MEDIA_CPU]	    = &meson8b_ao_media_cpu.hw,
		[CLKID_AO_AHB_SRAM]	    = &meson8b_ao_ahb_sram.hw,
		[CLKID_AO_AHB_BUS]	    = &meson8b_ao_ahb_bus.hw,
		[CLKID_AO_IFACE]	    = &meson8b_ao_अगरace.hw,
		[CLKID_MPLL0]		    = &meson8b_mpll0.hw,
		[CLKID_MPLL1]		    = &meson8b_mpll1.hw,
		[CLKID_MPLL2]		    = &meson8b_mpll2.hw,
		[CLKID_MPLL0_DIV]	    = &meson8b_mpll0_भाग.hw,
		[CLKID_MPLL1_DIV]	    = &meson8b_mpll1_भाग.hw,
		[CLKID_MPLL2_DIV]	    = &meson8b_mpll2_भाग.hw,
		[CLKID_CPU_IN_SEL]	    = &meson8b_cpu_in_sel.hw,
		[CLKID_CPU_IN_DIV2]	    = &meson8b_cpu_in_भाग2.hw,
		[CLKID_CPU_IN_DIV3]	    = &meson8b_cpu_in_भाग3.hw,
		[CLKID_CPU_SCALE_DIV]	    = &meson8b_cpu_scale_भाग.hw,
		[CLKID_CPU_SCALE_OUT_SEL]   = &meson8b_cpu_scale_out_sel.hw,
		[CLKID_MPLL_PREDIV]	    = &meson8b_mpll_preभाग.hw,
		[CLKID_FCLK_DIV2_DIV]	    = &meson8b_fclk_भाग2_भाग.hw,
		[CLKID_FCLK_DIV3_DIV]	    = &meson8b_fclk_भाग3_भाग.hw,
		[CLKID_FCLK_DIV4_DIV]	    = &meson8b_fclk_भाग4_भाग.hw,
		[CLKID_FCLK_DIV5_DIV]	    = &meson8b_fclk_भाग5_भाग.hw,
		[CLKID_FCLK_DIV7_DIV]	    = &meson8b_fclk_भाग7_भाग.hw,
		[CLKID_न_अंकD_SEL]	    = &meson8b_nand_clk_sel.hw,
		[CLKID_न_अंकD_DIV]	    = &meson8b_nand_clk_भाग.hw,
		[CLKID_न_अंकD_CLK]	    = &meson8b_nand_clk_gate.hw,
		[CLKID_PLL_FIXED_DCO]	    = &meson8b_fixed_pll_dco.hw,
		[CLKID_HDMI_PLL_DCO]	    = &meson8b_hdmi_pll_dco.hw,
		[CLKID_PLL_SYS_DCO]	    = &meson8b_sys_pll_dco.hw,
		[CLKID_CPU_CLK_DIV2]	    = &meson8b_cpu_clk_भाग2.hw,
		[CLKID_CPU_CLK_DIV3]	    = &meson8b_cpu_clk_भाग3.hw,
		[CLKID_CPU_CLK_DIV4]	    = &meson8b_cpu_clk_भाग4.hw,
		[CLKID_CPU_CLK_DIV5]	    = &meson8b_cpu_clk_भाग5.hw,
		[CLKID_CPU_CLK_DIV6]	    = &meson8b_cpu_clk_भाग6.hw,
		[CLKID_CPU_CLK_DIV7]	    = &meson8b_cpu_clk_भाग7.hw,
		[CLKID_CPU_CLK_DIV8]	    = &meson8b_cpu_clk_भाग8.hw,
		[CLKID_APB_SEL]		    = &meson8b_apb_clk_sel.hw,
		[CLKID_APB]		    = &meson8b_apb_clk_gate.hw,
		[CLKID_PERIPH_SEL]	    = &meson8b_periph_clk_sel.hw,
		[CLKID_PERIPH]		    = &meson8b_periph_clk_gate.hw,
		[CLKID_AXI_SEL]		    = &meson8b_axi_clk_sel.hw,
		[CLKID_AXI]		    = &meson8b_axi_clk_gate.hw,
		[CLKID_L2_DRAM_SEL]	    = &meson8b_l2_dram_clk_sel.hw,
		[CLKID_L2_DRAM]		    = &meson8b_l2_dram_clk_gate.hw,
		[CLKID_HDMI_PLL_LVDS_OUT]   = &meson8b_hdmi_pll_lvds_out.hw,
		[CLKID_HDMI_PLL_HDMI_OUT]   = &meson8b_hdmi_pll_hdmi_out.hw,
		[CLKID_VID_PLL_IN_SEL]	    = &meson8b_vid_pll_in_sel.hw,
		[CLKID_VID_PLL_IN_EN]	    = &meson8b_vid_pll_in_en.hw,
		[CLKID_VID_PLL_PRE_DIV]	    = &meson8b_vid_pll_pre_भाग.hw,
		[CLKID_VID_PLL_POST_DIV]    = &meson8b_vid_pll_post_भाग.hw,
		[CLKID_VID_PLL_FINAL_DIV]   = &meson8b_vid_pll_final_भाग.hw,
		[CLKID_VCLK_IN_SEL]	    = &meson8b_vclk_in_sel.hw,
		[CLKID_VCLK_IN_EN]	    = &meson8b_vclk_in_en.hw,
		[CLKID_VCLK_EN]		    = &meson8b_vclk_en.hw,
		[CLKID_VCLK_DIV1]	    = &meson8b_vclk_भाग1_gate.hw,
		[CLKID_VCLK_DIV2_DIV]	    = &meson8b_vclk_भाग2_भाग.hw,
		[CLKID_VCLK_DIV2]	    = &meson8b_vclk_भाग2_भाग_gate.hw,
		[CLKID_VCLK_DIV4_DIV]	    = &meson8b_vclk_भाग4_भाग.hw,
		[CLKID_VCLK_DIV4]	    = &meson8b_vclk_भाग4_भाग_gate.hw,
		[CLKID_VCLK_DIV6_DIV]	    = &meson8b_vclk_भाग6_भाग.hw,
		[CLKID_VCLK_DIV6]	    = &meson8b_vclk_भाग6_भाग_gate.hw,
		[CLKID_VCLK_DIV12_DIV]	    = &meson8b_vclk_भाग12_भाग.hw,
		[CLKID_VCLK_DIV12]	    = &meson8b_vclk_भाग12_भाग_gate.hw,
		[CLKID_VCLK2_IN_SEL]	    = &meson8b_vclk2_in_sel.hw,
		[CLKID_VCLK2_IN_EN]	    = &meson8b_vclk2_clk_in_en.hw,
		[CLKID_VCLK2_EN]	    = &meson8b_vclk2_clk_en.hw,
		[CLKID_VCLK2_DIV1]	    = &meson8b_vclk2_भाग1_gate.hw,
		[CLKID_VCLK2_DIV2_DIV]	    = &meson8b_vclk2_भाग2_भाग.hw,
		[CLKID_VCLK2_DIV2]	    = &meson8b_vclk2_भाग2_भाग_gate.hw,
		[CLKID_VCLK2_DIV4_DIV]	    = &meson8b_vclk2_भाग4_भाग.hw,
		[CLKID_VCLK2_DIV4]	    = &meson8b_vclk2_भाग4_भाग_gate.hw,
		[CLKID_VCLK2_DIV6_DIV]	    = &meson8b_vclk2_भाग6_भाग.hw,
		[CLKID_VCLK2_DIV6]	    = &meson8b_vclk2_भाग6_भाग_gate.hw,
		[CLKID_VCLK2_DIV12_DIV]	    = &meson8b_vclk2_भाग12_भाग.hw,
		[CLKID_VCLK2_DIV12]	    = &meson8b_vclk2_भाग12_भाग_gate.hw,
		[CLKID_CTS_ENCT_SEL]	    = &meson8b_cts_enct_sel.hw,
		[CLKID_CTS_ENCT]	    = &meson8b_cts_enct.hw,
		[CLKID_CTS_ENCP_SEL]	    = &meson8b_cts_encp_sel.hw,
		[CLKID_CTS_ENCP]	    = &meson8b_cts_encp.hw,
		[CLKID_CTS_ENCI_SEL]	    = &meson8b_cts_enci_sel.hw,
		[CLKID_CTS_ENCI]	    = &meson8b_cts_enci.hw,
		[CLKID_HDMI_TX_PIXEL_SEL]   = &meson8b_hdmi_tx_pixel_sel.hw,
		[CLKID_HDMI_TX_PIXEL]	    = &meson8b_hdmi_tx_pixel.hw,
		[CLKID_CTS_ENCL_SEL]	    = &meson8b_cts_encl_sel.hw,
		[CLKID_CTS_ENCL]	    = &meson8b_cts_encl.hw,
		[CLKID_CTS_VDAC0_SEL]	    = &meson8b_cts_vdac0_sel.hw,
		[CLKID_CTS_VDAC0]	    = &meson8b_cts_vdac0.hw,
		[CLKID_HDMI_SYS_SEL]	    = &meson8b_hdmi_sys_sel.hw,
		[CLKID_HDMI_SYS_DIV]	    = &meson8b_hdmi_sys_भाग.hw,
		[CLKID_HDMI_SYS]	    = &meson8b_hdmi_sys.hw,
		[CLKID_MALI_0_SEL]	    = &meson8b_mali_0_sel.hw,
		[CLKID_MALI_0_DIV]	    = &meson8b_mali_0_भाग.hw,
		[CLKID_MALI_0]		    = &meson8b_mali_0.hw,
		[CLKID_MALI_1_SEL]	    = &meson8b_mali_1_sel.hw,
		[CLKID_MALI_1_DIV]	    = &meson8b_mali_1_भाग.hw,
		[CLKID_MALI_1]		    = &meson8b_mali_1.hw,
		[CLKID_MALI]		    = &meson8b_mali.hw,
		[CLKID_VPU_0_SEL]	    = &meson8b_vpu_0_sel.hw,
		[CLKID_VPU_0_DIV]	    = &meson8b_vpu_0_भाग.hw,
		[CLKID_VPU_0]		    = &meson8b_vpu_0.hw,
		[CLKID_VPU_1_SEL]	    = &meson8b_vpu_1_sel.hw,
		[CLKID_VPU_1_DIV]	    = &meson8b_vpu_1_भाग.hw,
		[CLKID_VPU_1]		    = &meson8b_vpu_1.hw,
		[CLKID_VPU]		    = &meson8b_vpu.hw,
		[CLKID_VDEC_1_SEL]	    = &meson8b_vdec_1_sel.hw,
		[CLKID_VDEC_1_1_DIV]	    = &meson8b_vdec_1_1_भाग.hw,
		[CLKID_VDEC_1_1]	    = &meson8b_vdec_1_1.hw,
		[CLKID_VDEC_1_2_DIV]	    = &meson8b_vdec_1_2_भाग.hw,
		[CLKID_VDEC_1_2]	    = &meson8b_vdec_1_2.hw,
		[CLKID_VDEC_1]	    	    = &meson8b_vdec_1.hw,
		[CLKID_VDEC_HCODEC_SEL]	    = &meson8b_vdec_hcodec_sel.hw,
		[CLKID_VDEC_HCODEC_DIV]	    = &meson8b_vdec_hcodec_भाग.hw,
		[CLKID_VDEC_HCODEC]	    = &meson8b_vdec_hcodec.hw,
		[CLKID_VDEC_2_SEL]	    = &meson8b_vdec_2_sel.hw,
		[CLKID_VDEC_2_DIV]	    = &meson8b_vdec_2_भाग.hw,
		[CLKID_VDEC_2]	    	    = &meson8b_vdec_2.hw,
		[CLKID_VDEC_HEVC_SEL]	    = &meson8b_vdec_hevc_sel.hw,
		[CLKID_VDEC_HEVC_DIV]	    = &meson8b_vdec_hevc_भाग.hw,
		[CLKID_VDEC_HEVC_EN]	    = &meson8b_vdec_hevc_en.hw,
		[CLKID_VDEC_HEVC]	    = &meson8b_vdec_hevc.hw,
		[CLKID_CTS_AMCLK_SEL]	    = &meson8b_cts_amclk_sel.hw,
		[CLKID_CTS_AMCLK_DIV]	    = &meson8b_cts_amclk_भाग.hw,
		[CLKID_CTS_AMCLK]	    = &meson8b_cts_amclk.hw,
		[CLKID_CTS_MCLK_I958_SEL]   = &meson8b_cts_mclk_i958_sel.hw,
		[CLKID_CTS_MCLK_I958_DIV]   = &meson8b_cts_mclk_i958_भाग.hw,
		[CLKID_CTS_MCLK_I958]	    = &meson8b_cts_mclk_i958.hw,
		[CLKID_CTS_I958]	    = &meson8b_cts_i958.hw,
		[CLK_NR_CLKS]		    = शून्य,
	पूर्ण,
	.num = CLK_NR_CLKS,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data meson8m2_hw_onecell_data = अणु
	.hws = अणु
		[CLKID_PLL_FIXED] = &meson8b_fixed_pll.hw,
		[CLKID_PLL_VID] = &meson8b_vid_pll.hw,
		[CLKID_PLL_SYS] = &meson8b_sys_pll.hw,
		[CLKID_FCLK_DIV2] = &meson8b_fclk_भाग2.hw,
		[CLKID_FCLK_DIV3] = &meson8b_fclk_भाग3.hw,
		[CLKID_FCLK_DIV4] = &meson8b_fclk_भाग4.hw,
		[CLKID_FCLK_DIV5] = &meson8b_fclk_भाग5.hw,
		[CLKID_FCLK_DIV7] = &meson8b_fclk_भाग7.hw,
		[CLKID_CPUCLK] = &meson8b_cpu_clk.hw,
		[CLKID_MPEG_SEL] = &meson8b_mpeg_clk_sel.hw,
		[CLKID_MPEG_DIV] = &meson8b_mpeg_clk_भाग.hw,
		[CLKID_CLK81] = &meson8b_clk81.hw,
		[CLKID_DDR]		    = &meson8b_ddr.hw,
		[CLKID_DOS]		    = &meson8b_डॉस.सw,
		[CLKID_ISA]		    = &meson8b_isa.hw,
		[CLKID_PL301]		    = &meson8b_pl301.hw,
		[CLKID_PERIPHS]		    = &meson8b_periphs.hw,
		[CLKID_SPICC]		    = &meson8b_spicc.hw,
		[CLKID_I2C]		    = &meson8b_i2c.hw,
		[CLKID_SAR_ADC]		    = &meson8b_sar_adc.hw,
		[CLKID_SMART_CARD]	    = &meson8b_smart_card.hw,
		[CLKID_RNG0]		    = &meson8b_rng0.hw,
		[CLKID_UART0]		    = &meson8b_uart0.hw,
		[CLKID_SDHC]		    = &meson8b_sdhc.hw,
		[CLKID_STREAM]		    = &meson8b_stream.hw,
		[CLKID_ASYNC_FIFO]	    = &meson8b_async_fअगरo.hw,
		[CLKID_SDIO]		    = &meson8b_sdपन.सw,
		[CLKID_ABUF]		    = &meson8b_abuf.hw,
		[CLKID_HIU_IFACE]	    = &meson8b_hiu_अगरace.hw,
		[CLKID_ASSIST_MISC]	    = &meson8b_assist_misc.hw,
		[CLKID_SPI]		    = &meson8b_spi.hw,
		[CLKID_I2S_SPDIF]	    = &meson8b_i2s_spdअगर.hw,
		[CLKID_ETH]		    = &meson8b_eth.hw,
		[CLKID_DEMUX]		    = &meson8b_demux.hw,
		[CLKID_AIU_GLUE]	    = &meson8b_aiu_glue.hw,
		[CLKID_IEC958]		    = &meson8b_iec958.hw,
		[CLKID_I2S_OUT]		    = &meson8b_i2s_out.hw,
		[CLKID_AMCLK]		    = &meson8b_amclk.hw,
		[CLKID_AIFIFO2]		    = &meson8b_aअगरअगरo2.hw,
		[CLKID_MIXER]		    = &meson8b_mixer.hw,
		[CLKID_MIXER_IFACE]	    = &meson8b_mixer_अगरace.hw,
		[CLKID_ADC]		    = &meson8b_adc.hw,
		[CLKID_BLKMV]		    = &meson8b_blkmv.hw,
		[CLKID_AIU]		    = &meson8b_aiu.hw,
		[CLKID_UART1]		    = &meson8b_uart1.hw,
		[CLKID_G2D]		    = &meson8b_g2d.hw,
		[CLKID_USB0]		    = &meson8b_usb0.hw,
		[CLKID_USB1]		    = &meson8b_usb1.hw,
		[CLKID_RESET]		    = &meson8b_reset.hw,
		[CLKID_न_अंकD]		    = &meson8b_nand.hw,
		[CLKID_DOS_PARSER]	    = &meson8b_करोs_parser.hw,
		[CLKID_USB]		    = &meson8b_usb.hw,
		[CLKID_VDIN1]		    = &meson8b_vdin1.hw,
		[CLKID_AHB_ARB0]	    = &meson8b_ahb_arb0.hw,
		[CLKID_EFUSE]		    = &meson8b_efuse.hw,
		[CLKID_BOOT_ROM]	    = &meson8b_boot_rom.hw,
		[CLKID_AHB_DATA_BUS]	    = &meson8b_ahb_data_bus.hw,
		[CLKID_AHB_CTRL_BUS]	    = &meson8b_ahb_ctrl_bus.hw,
		[CLKID_HDMI_INTR_SYNC]	    = &meson8b_hdmi_पूर्णांकr_sync.hw,
		[CLKID_HDMI_PCLK]	    = &meson8b_hdmi_pclk.hw,
		[CLKID_USB1_DDR_BRIDGE]	    = &meson8b_usb1_ddr_bridge.hw,
		[CLKID_USB0_DDR_BRIDGE]	    = &meson8b_usb0_ddr_bridge.hw,
		[CLKID_MMC_PCLK]	    = &meson8b_mmc_pclk.hw,
		[CLKID_DVIN]		    = &meson8b_dvin.hw,
		[CLKID_UART2]		    = &meson8b_uart2.hw,
		[CLKID_SANA]		    = &meson8b_sana.hw,
		[CLKID_VPU_INTR]	    = &meson8b_vpu_पूर्णांकr.hw,
		[CLKID_SEC_AHB_AHB3_BRIDGE] = &meson8b_sec_ahb_ahb3_bridge.hw,
		[CLKID_CLK81_A9]	    = &meson8b_clk81_a9.hw,
		[CLKID_VCLK2_VENCI0]	    = &meson8b_vclk2_venci0.hw,
		[CLKID_VCLK2_VENCI1]	    = &meson8b_vclk2_venci1.hw,
		[CLKID_VCLK2_VENCP0]	    = &meson8b_vclk2_vencp0.hw,
		[CLKID_VCLK2_VENCP1]	    = &meson8b_vclk2_vencp1.hw,
		[CLKID_GCLK_VENCI_INT]	    = &meson8b_gclk_venci_पूर्णांक.hw,
		[CLKID_GCLK_VENCP_INT]	    = &meson8b_gclk_vencp_पूर्णांक.hw,
		[CLKID_DAC_CLK]		    = &meson8b_dac_clk.hw,
		[CLKID_AOCLK_GATE]	    = &meson8b_aoclk_gate.hw,
		[CLKID_IEC958_GATE]	    = &meson8b_iec958_gate.hw,
		[CLKID_ENC480P]		    = &meson8b_enc480p.hw,
		[CLKID_RNG1]		    = &meson8b_rng1.hw,
		[CLKID_GCLK_VENCL_INT]	    = &meson8b_gclk_vencl_पूर्णांक.hw,
		[CLKID_VCLK2_VENCLMCC]	    = &meson8b_vclk2_venclmcc.hw,
		[CLKID_VCLK2_VENCL]	    = &meson8b_vclk2_vencl.hw,
		[CLKID_VCLK2_OTHER]	    = &meson8b_vclk2_other.hw,
		[CLKID_EDP]		    = &meson8b_edp.hw,
		[CLKID_AO_MEDIA_CPU]	    = &meson8b_ao_media_cpu.hw,
		[CLKID_AO_AHB_SRAM]	    = &meson8b_ao_ahb_sram.hw,
		[CLKID_AO_AHB_BUS]	    = &meson8b_ao_ahb_bus.hw,
		[CLKID_AO_IFACE]	    = &meson8b_ao_अगरace.hw,
		[CLKID_MPLL0]		    = &meson8b_mpll0.hw,
		[CLKID_MPLL1]		    = &meson8b_mpll1.hw,
		[CLKID_MPLL2]		    = &meson8b_mpll2.hw,
		[CLKID_MPLL0_DIV]	    = &meson8b_mpll0_भाग.hw,
		[CLKID_MPLL1_DIV]	    = &meson8b_mpll1_भाग.hw,
		[CLKID_MPLL2_DIV]	    = &meson8b_mpll2_भाग.hw,
		[CLKID_CPU_IN_SEL]	    = &meson8b_cpu_in_sel.hw,
		[CLKID_CPU_IN_DIV2]	    = &meson8b_cpu_in_भाग2.hw,
		[CLKID_CPU_IN_DIV3]	    = &meson8b_cpu_in_भाग3.hw,
		[CLKID_CPU_SCALE_DIV]	    = &meson8b_cpu_scale_भाग.hw,
		[CLKID_CPU_SCALE_OUT_SEL]   = &meson8b_cpu_scale_out_sel.hw,
		[CLKID_MPLL_PREDIV]	    = &meson8b_mpll_preभाग.hw,
		[CLKID_FCLK_DIV2_DIV]	    = &meson8b_fclk_भाग2_भाग.hw,
		[CLKID_FCLK_DIV3_DIV]	    = &meson8b_fclk_भाग3_भाग.hw,
		[CLKID_FCLK_DIV4_DIV]	    = &meson8b_fclk_भाग4_भाग.hw,
		[CLKID_FCLK_DIV5_DIV]	    = &meson8b_fclk_भाग5_भाग.hw,
		[CLKID_FCLK_DIV7_DIV]	    = &meson8b_fclk_भाग7_भाग.hw,
		[CLKID_न_अंकD_SEL]	    = &meson8b_nand_clk_sel.hw,
		[CLKID_न_अंकD_DIV]	    = &meson8b_nand_clk_भाग.hw,
		[CLKID_न_अंकD_CLK]	    = &meson8b_nand_clk_gate.hw,
		[CLKID_PLL_FIXED_DCO]	    = &meson8b_fixed_pll_dco.hw,
		[CLKID_HDMI_PLL_DCO]	    = &meson8b_hdmi_pll_dco.hw,
		[CLKID_PLL_SYS_DCO]	    = &meson8b_sys_pll_dco.hw,
		[CLKID_CPU_CLK_DIV2]	    = &meson8b_cpu_clk_भाग2.hw,
		[CLKID_CPU_CLK_DIV3]	    = &meson8b_cpu_clk_भाग3.hw,
		[CLKID_CPU_CLK_DIV4]	    = &meson8b_cpu_clk_भाग4.hw,
		[CLKID_CPU_CLK_DIV5]	    = &meson8b_cpu_clk_भाग5.hw,
		[CLKID_CPU_CLK_DIV6]	    = &meson8b_cpu_clk_भाग6.hw,
		[CLKID_CPU_CLK_DIV7]	    = &meson8b_cpu_clk_भाग7.hw,
		[CLKID_CPU_CLK_DIV8]	    = &meson8b_cpu_clk_भाग8.hw,
		[CLKID_APB_SEL]		    = &meson8b_apb_clk_sel.hw,
		[CLKID_APB]		    = &meson8b_apb_clk_gate.hw,
		[CLKID_PERIPH_SEL]	    = &meson8b_periph_clk_sel.hw,
		[CLKID_PERIPH]		    = &meson8b_periph_clk_gate.hw,
		[CLKID_AXI_SEL]		    = &meson8b_axi_clk_sel.hw,
		[CLKID_AXI]		    = &meson8b_axi_clk_gate.hw,
		[CLKID_L2_DRAM_SEL]	    = &meson8b_l2_dram_clk_sel.hw,
		[CLKID_L2_DRAM]		    = &meson8b_l2_dram_clk_gate.hw,
		[CLKID_HDMI_PLL_LVDS_OUT]   = &meson8b_hdmi_pll_lvds_out.hw,
		[CLKID_HDMI_PLL_HDMI_OUT]   = &meson8b_hdmi_pll_hdmi_out.hw,
		[CLKID_VID_PLL_IN_SEL]	    = &meson8b_vid_pll_in_sel.hw,
		[CLKID_VID_PLL_IN_EN]	    = &meson8b_vid_pll_in_en.hw,
		[CLKID_VID_PLL_PRE_DIV]	    = &meson8b_vid_pll_pre_भाग.hw,
		[CLKID_VID_PLL_POST_DIV]    = &meson8b_vid_pll_post_भाग.hw,
		[CLKID_VID_PLL_FINAL_DIV]   = &meson8b_vid_pll_final_भाग.hw,
		[CLKID_VCLK_IN_SEL]	    = &meson8b_vclk_in_sel.hw,
		[CLKID_VCLK_IN_EN]	    = &meson8b_vclk_in_en.hw,
		[CLKID_VCLK_EN]		    = &meson8b_vclk_en.hw,
		[CLKID_VCLK_DIV1]	    = &meson8b_vclk_भाग1_gate.hw,
		[CLKID_VCLK_DIV2_DIV]	    = &meson8b_vclk_भाग2_भाग.hw,
		[CLKID_VCLK_DIV2]	    = &meson8b_vclk_भाग2_भाग_gate.hw,
		[CLKID_VCLK_DIV4_DIV]	    = &meson8b_vclk_भाग4_भाग.hw,
		[CLKID_VCLK_DIV4]	    = &meson8b_vclk_भाग4_भाग_gate.hw,
		[CLKID_VCLK_DIV6_DIV]	    = &meson8b_vclk_भाग6_भाग.hw,
		[CLKID_VCLK_DIV6]	    = &meson8b_vclk_भाग6_भाग_gate.hw,
		[CLKID_VCLK_DIV12_DIV]	    = &meson8b_vclk_भाग12_भाग.hw,
		[CLKID_VCLK_DIV12]	    = &meson8b_vclk_भाग12_भाग_gate.hw,
		[CLKID_VCLK2_IN_SEL]	    = &meson8b_vclk2_in_sel.hw,
		[CLKID_VCLK2_IN_EN]	    = &meson8b_vclk2_clk_in_en.hw,
		[CLKID_VCLK2_EN]	    = &meson8b_vclk2_clk_en.hw,
		[CLKID_VCLK2_DIV1]	    = &meson8b_vclk2_भाग1_gate.hw,
		[CLKID_VCLK2_DIV2_DIV]	    = &meson8b_vclk2_भाग2_भाग.hw,
		[CLKID_VCLK2_DIV2]	    = &meson8b_vclk2_भाग2_भाग_gate.hw,
		[CLKID_VCLK2_DIV4_DIV]	    = &meson8b_vclk2_भाग4_भाग.hw,
		[CLKID_VCLK2_DIV4]	    = &meson8b_vclk2_भाग4_भाग_gate.hw,
		[CLKID_VCLK2_DIV6_DIV]	    = &meson8b_vclk2_भाग6_भाग.hw,
		[CLKID_VCLK2_DIV6]	    = &meson8b_vclk2_भाग6_भाग_gate.hw,
		[CLKID_VCLK2_DIV12_DIV]	    = &meson8b_vclk2_भाग12_भाग.hw,
		[CLKID_VCLK2_DIV12]	    = &meson8b_vclk2_भाग12_भाग_gate.hw,
		[CLKID_CTS_ENCT_SEL]	    = &meson8b_cts_enct_sel.hw,
		[CLKID_CTS_ENCT]	    = &meson8b_cts_enct.hw,
		[CLKID_CTS_ENCP_SEL]	    = &meson8b_cts_encp_sel.hw,
		[CLKID_CTS_ENCP]	    = &meson8b_cts_encp.hw,
		[CLKID_CTS_ENCI_SEL]	    = &meson8b_cts_enci_sel.hw,
		[CLKID_CTS_ENCI]	    = &meson8b_cts_enci.hw,
		[CLKID_HDMI_TX_PIXEL_SEL]   = &meson8b_hdmi_tx_pixel_sel.hw,
		[CLKID_HDMI_TX_PIXEL]	    = &meson8b_hdmi_tx_pixel.hw,
		[CLKID_CTS_ENCL_SEL]	    = &meson8b_cts_encl_sel.hw,
		[CLKID_CTS_ENCL]	    = &meson8b_cts_encl.hw,
		[CLKID_CTS_VDAC0_SEL]	    = &meson8b_cts_vdac0_sel.hw,
		[CLKID_CTS_VDAC0]	    = &meson8b_cts_vdac0.hw,
		[CLKID_HDMI_SYS_SEL]	    = &meson8b_hdmi_sys_sel.hw,
		[CLKID_HDMI_SYS_DIV]	    = &meson8b_hdmi_sys_भाग.hw,
		[CLKID_HDMI_SYS]	    = &meson8b_hdmi_sys.hw,
		[CLKID_MALI_0_SEL]	    = &meson8b_mali_0_sel.hw,
		[CLKID_MALI_0_DIV]	    = &meson8b_mali_0_भाग.hw,
		[CLKID_MALI_0]		    = &meson8b_mali_0.hw,
		[CLKID_MALI_1_SEL]	    = &meson8b_mali_1_sel.hw,
		[CLKID_MALI_1_DIV]	    = &meson8b_mali_1_भाग.hw,
		[CLKID_MALI_1]		    = &meson8b_mali_1.hw,
		[CLKID_MALI]		    = &meson8b_mali.hw,
		[CLKID_GP_PLL_DCO]	    = &meson8m2_gp_pll_dco.hw,
		[CLKID_GP_PLL]		    = &meson8m2_gp_pll.hw,
		[CLKID_VPU_0_SEL]	    = &meson8m2_vpu_0_sel.hw,
		[CLKID_VPU_0_DIV]	    = &meson8b_vpu_0_भाग.hw,
		[CLKID_VPU_0]		    = &meson8b_vpu_0.hw,
		[CLKID_VPU_1_SEL]	    = &meson8m2_vpu_1_sel.hw,
		[CLKID_VPU_1_DIV]	    = &meson8b_vpu_1_भाग.hw,
		[CLKID_VPU_1]		    = &meson8b_vpu_1.hw,
		[CLKID_VPU]		    = &meson8b_vpu.hw,
		[CLKID_VDEC_1_SEL]	    = &meson8b_vdec_1_sel.hw,
		[CLKID_VDEC_1_1_DIV]	    = &meson8b_vdec_1_1_भाग.hw,
		[CLKID_VDEC_1_1]	    = &meson8b_vdec_1_1.hw,
		[CLKID_VDEC_1_2_DIV]	    = &meson8b_vdec_1_2_भाग.hw,
		[CLKID_VDEC_1_2]	    = &meson8b_vdec_1_2.hw,
		[CLKID_VDEC_1]	    	    = &meson8b_vdec_1.hw,
		[CLKID_VDEC_HCODEC_SEL]	    = &meson8b_vdec_hcodec_sel.hw,
		[CLKID_VDEC_HCODEC_DIV]	    = &meson8b_vdec_hcodec_भाग.hw,
		[CLKID_VDEC_HCODEC]	    = &meson8b_vdec_hcodec.hw,
		[CLKID_VDEC_2_SEL]	    = &meson8b_vdec_2_sel.hw,
		[CLKID_VDEC_2_DIV]	    = &meson8b_vdec_2_भाग.hw,
		[CLKID_VDEC_2]	    	    = &meson8b_vdec_2.hw,
		[CLKID_VDEC_HEVC_SEL]	    = &meson8b_vdec_hevc_sel.hw,
		[CLKID_VDEC_HEVC_DIV]	    = &meson8b_vdec_hevc_भाग.hw,
		[CLKID_VDEC_HEVC_EN]	    = &meson8b_vdec_hevc_en.hw,
		[CLKID_VDEC_HEVC]	    = &meson8b_vdec_hevc.hw,
		[CLKID_CTS_AMCLK_SEL]	    = &meson8b_cts_amclk_sel.hw,
		[CLKID_CTS_AMCLK_DIV]	    = &meson8b_cts_amclk_भाग.hw,
		[CLKID_CTS_AMCLK]	    = &meson8b_cts_amclk.hw,
		[CLKID_CTS_MCLK_I958_SEL]   = &meson8b_cts_mclk_i958_sel.hw,
		[CLKID_CTS_MCLK_I958_DIV]   = &meson8b_cts_mclk_i958_भाग.hw,
		[CLKID_CTS_MCLK_I958]	    = &meson8b_cts_mclk_i958.hw,
		[CLKID_CTS_I958]	    = &meson8b_cts_i958.hw,
		[CLK_NR_CLKS]		    = शून्य,
	पूर्ण,
	.num = CLK_NR_CLKS,
पूर्ण;

अटल काष्ठा clk_regmap *स्थिर meson8b_clk_regmaps[] = अणु
	&meson8b_clk81,
	&meson8b_ddr,
	&meson8b_करोs,
	&meson8b_isa,
	&meson8b_pl301,
	&meson8b_periphs,
	&meson8b_spicc,
	&meson8b_i2c,
	&meson8b_sar_adc,
	&meson8b_smart_card,
	&meson8b_rng0,
	&meson8b_uart0,
	&meson8b_sdhc,
	&meson8b_stream,
	&meson8b_async_fअगरo,
	&meson8b_sdio,
	&meson8b_abuf,
	&meson8b_hiu_अगरace,
	&meson8b_assist_misc,
	&meson8b_spi,
	&meson8b_i2s_spdअगर,
	&meson8b_eth,
	&meson8b_demux,
	&meson8b_aiu_glue,
	&meson8b_iec958,
	&meson8b_i2s_out,
	&meson8b_amclk,
	&meson8b_aअगरअगरo2,
	&meson8b_mixer,
	&meson8b_mixer_अगरace,
	&meson8b_adc,
	&meson8b_blkmv,
	&meson8b_aiu,
	&meson8b_uart1,
	&meson8b_g2d,
	&meson8b_usb0,
	&meson8b_usb1,
	&meson8b_reset,
	&meson8b_nand,
	&meson8b_करोs_parser,
	&meson8b_usb,
	&meson8b_vdin1,
	&meson8b_ahb_arb0,
	&meson8b_efuse,
	&meson8b_boot_rom,
	&meson8b_ahb_data_bus,
	&meson8b_ahb_ctrl_bus,
	&meson8b_hdmi_पूर्णांकr_sync,
	&meson8b_hdmi_pclk,
	&meson8b_usb1_ddr_bridge,
	&meson8b_usb0_ddr_bridge,
	&meson8b_mmc_pclk,
	&meson8b_dvin,
	&meson8b_uart2,
	&meson8b_sana,
	&meson8b_vpu_पूर्णांकr,
	&meson8b_sec_ahb_ahb3_bridge,
	&meson8b_clk81_a9,
	&meson8b_vclk2_venci0,
	&meson8b_vclk2_venci1,
	&meson8b_vclk2_vencp0,
	&meson8b_vclk2_vencp1,
	&meson8b_gclk_venci_पूर्णांक,
	&meson8b_gclk_vencp_पूर्णांक,
	&meson8b_dac_clk,
	&meson8b_aoclk_gate,
	&meson8b_iec958_gate,
	&meson8b_enc480p,
	&meson8b_rng1,
	&meson8b_gclk_vencl_पूर्णांक,
	&meson8b_vclk2_venclmcc,
	&meson8b_vclk2_vencl,
	&meson8b_vclk2_other,
	&meson8b_edp,
	&meson8b_ao_media_cpu,
	&meson8b_ao_ahb_sram,
	&meson8b_ao_ahb_bus,
	&meson8b_ao_अगरace,
	&meson8b_mpeg_clk_भाग,
	&meson8b_mpeg_clk_sel,
	&meson8b_mpll0,
	&meson8b_mpll1,
	&meson8b_mpll2,
	&meson8b_mpll0_भाग,
	&meson8b_mpll1_भाग,
	&meson8b_mpll2_भाग,
	&meson8b_fixed_pll,
	&meson8b_sys_pll,
	&meson8b_cpu_in_sel,
	&meson8b_cpu_scale_भाग,
	&meson8b_cpu_scale_out_sel,
	&meson8b_cpu_clk,
	&meson8b_mpll_preभाग,
	&meson8b_fclk_भाग2,
	&meson8b_fclk_भाग3,
	&meson8b_fclk_भाग4,
	&meson8b_fclk_भाग5,
	&meson8b_fclk_भाग7,
	&meson8b_nand_clk_sel,
	&meson8b_nand_clk_भाग,
	&meson8b_nand_clk_gate,
	&meson8b_fixed_pll_dco,
	&meson8b_hdmi_pll_dco,
	&meson8b_sys_pll_dco,
	&meson8b_apb_clk_sel,
	&meson8b_apb_clk_gate,
	&meson8b_periph_clk_sel,
	&meson8b_periph_clk_gate,
	&meson8b_axi_clk_sel,
	&meson8b_axi_clk_gate,
	&meson8b_l2_dram_clk_sel,
	&meson8b_l2_dram_clk_gate,
	&meson8b_hdmi_pll_lvds_out,
	&meson8b_hdmi_pll_hdmi_out,
	&meson8b_vid_pll_in_sel,
	&meson8b_vid_pll_in_en,
	&meson8b_vid_pll_pre_भाग,
	&meson8b_vid_pll_post_भाग,
	&meson8b_vid_pll,
	&meson8b_vid_pll_final_भाग,
	&meson8b_vclk_in_sel,
	&meson8b_vclk_in_en,
	&meson8b_vclk_en,
	&meson8b_vclk_भाग1_gate,
	&meson8b_vclk_भाग2_भाग_gate,
	&meson8b_vclk_भाग4_भाग_gate,
	&meson8b_vclk_भाग6_भाग_gate,
	&meson8b_vclk_भाग12_भाग_gate,
	&meson8b_vclk2_in_sel,
	&meson8b_vclk2_clk_in_en,
	&meson8b_vclk2_clk_en,
	&meson8b_vclk2_भाग1_gate,
	&meson8b_vclk2_भाग2_भाग_gate,
	&meson8b_vclk2_भाग4_भाग_gate,
	&meson8b_vclk2_भाग6_भाग_gate,
	&meson8b_vclk2_भाग12_भाग_gate,
	&meson8b_cts_enct_sel,
	&meson8b_cts_enct,
	&meson8b_cts_encp_sel,
	&meson8b_cts_encp,
	&meson8b_cts_enci_sel,
	&meson8b_cts_enci,
	&meson8b_hdmi_tx_pixel_sel,
	&meson8b_hdmi_tx_pixel,
	&meson8b_cts_encl_sel,
	&meson8b_cts_encl,
	&meson8b_cts_vdac0_sel,
	&meson8b_cts_vdac0,
	&meson8b_hdmi_sys_sel,
	&meson8b_hdmi_sys_भाग,
	&meson8b_hdmi_sys,
	&meson8b_mali_0_sel,
	&meson8b_mali_0_भाग,
	&meson8b_mali_0,
	&meson8b_mali_1_sel,
	&meson8b_mali_1_भाग,
	&meson8b_mali_1,
	&meson8b_mali,
	&meson8m2_gp_pll_dco,
	&meson8m2_gp_pll,
	&meson8b_vpu_0_sel,
	&meson8m2_vpu_0_sel,
	&meson8b_vpu_0_भाग,
	&meson8b_vpu_0,
	&meson8b_vpu_1_sel,
	&meson8m2_vpu_1_sel,
	&meson8b_vpu_1_भाग,
	&meson8b_vpu_1,
	&meson8b_vpu,
	&meson8b_vdec_1_sel,
	&meson8b_vdec_1_1_भाग,
	&meson8b_vdec_1_1,
	&meson8b_vdec_1_2_भाग,
	&meson8b_vdec_1_2,
	&meson8b_vdec_1,
	&meson8b_vdec_hcodec_sel,
	&meson8b_vdec_hcodec_भाग,
	&meson8b_vdec_hcodec,
	&meson8b_vdec_2_sel,
	&meson8b_vdec_2_भाग,
	&meson8b_vdec_2,
	&meson8b_vdec_hevc_sel,
	&meson8b_vdec_hevc_भाग,
	&meson8b_vdec_hevc_en,
	&meson8b_vdec_hevc,
	&meson8b_cts_amclk,
	&meson8b_cts_amclk_sel,
	&meson8b_cts_amclk_भाग,
	&meson8b_cts_mclk_i958_sel,
	&meson8b_cts_mclk_i958_भाग,
	&meson8b_cts_mclk_i958,
	&meson8b_cts_i958,
पूर्ण;

अटल स्थिर काष्ठा meson8b_clk_reset_line अणु
	u32 reg;
	u8 bit_idx;
	bool active_low;
पूर्ण meson8b_clk_reset_bits[] = अणु
	[CLKC_RESET_L2_CACHE_SOFT_RESET] = अणु
		.reg = HHI_SYS_CPU_CLK_CNTL0,
		.bit_idx = 30,
		.active_low = false,
	पूर्ण,
	[CLKC_RESET_AXI_64_TO_128_BRIDGE_A5_SOFT_RESET] = अणु
		.reg = HHI_SYS_CPU_CLK_CNTL0,
		.bit_idx = 29,
		.active_low = false,
	पूर्ण,
	[CLKC_RESET_SCU_SOFT_RESET] = अणु
		.reg = HHI_SYS_CPU_CLK_CNTL0,
		.bit_idx = 28,
		.active_low = false,
	पूर्ण,
	[CLKC_RESET_CPU3_SOFT_RESET] = अणु
		.reg = HHI_SYS_CPU_CLK_CNTL0,
		.bit_idx = 27,
		.active_low = false,
	पूर्ण,
	[CLKC_RESET_CPU2_SOFT_RESET] = अणु
		.reg = HHI_SYS_CPU_CLK_CNTL0,
		.bit_idx = 26,
		.active_low = false,
	पूर्ण,
	[CLKC_RESET_CPU1_SOFT_RESET] = अणु
		.reg = HHI_SYS_CPU_CLK_CNTL0,
		.bit_idx = 25,
		.active_low = false,
	पूर्ण,
	[CLKC_RESET_CPU0_SOFT_RESET] = अणु
		.reg = HHI_SYS_CPU_CLK_CNTL0,
		.bit_idx = 24,
		.active_low = false,
	पूर्ण,
	[CLKC_RESET_A5_GLOBAL_RESET] = अणु
		.reg = HHI_SYS_CPU_CLK_CNTL0,
		.bit_idx = 18,
		.active_low = false,
	पूर्ण,
	[CLKC_RESET_A5_AXI_SOFT_RESET] = अणु
		.reg = HHI_SYS_CPU_CLK_CNTL0,
		.bit_idx = 17,
		.active_low = false,
	पूर्ण,
	[CLKC_RESET_A5_ABP_SOFT_RESET] = अणु
		.reg = HHI_SYS_CPU_CLK_CNTL0,
		.bit_idx = 16,
		.active_low = false,
	पूर्ण,
	[CLKC_RESET_AXI_64_TO_128_BRIDGE_MMC_SOFT_RESET] = अणु
		.reg = HHI_SYS_CPU_CLK_CNTL1,
		.bit_idx = 30,
		.active_low = false,
	पूर्ण,
	[CLKC_RESET_VID_CLK_CNTL_SOFT_RESET] = अणु
		.reg = HHI_VID_CLK_CNTL,
		.bit_idx = 15,
		.active_low = false,
	पूर्ण,
	[CLKC_RESET_VID_DIVIDER_CNTL_SOFT_RESET_POST] = अणु
		.reg = HHI_VID_DIVIDER_CNTL,
		.bit_idx = 7,
		.active_low = false,
	पूर्ण,
	[CLKC_RESET_VID_DIVIDER_CNTL_SOFT_RESET_PRE] = अणु
		.reg = HHI_VID_DIVIDER_CNTL,
		.bit_idx = 3,
		.active_low = false,
	पूर्ण,
	[CLKC_RESET_VID_DIVIDER_CNTL_RESET_N_POST] = अणु
		.reg = HHI_VID_DIVIDER_CNTL,
		.bit_idx = 1,
		.active_low = true,
	पूर्ण,
	[CLKC_RESET_VID_DIVIDER_CNTL_RESET_N_PRE] = अणु
		.reg = HHI_VID_DIVIDER_CNTL,
		.bit_idx = 0,
		.active_low = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक meson8b_clk_reset_update(काष्ठा reset_controller_dev *rcdev,
				    अचिन्हित दीर्घ id, bool निश्चित)
अणु
	काष्ठा meson8b_clk_reset *meson8b_clk_reset =
		container_of(rcdev, काष्ठा meson8b_clk_reset, reset);
	स्थिर काष्ठा meson8b_clk_reset_line *reset;
	अचिन्हित पूर्णांक value = 0;
	अचिन्हित दीर्घ flags;

	अगर (id >= ARRAY_SIZE(meson8b_clk_reset_bits))
		वापस -EINVAL;

	reset = &meson8b_clk_reset_bits[id];

	अगर (निश्चित != reset->active_low)
		value = BIT(reset->bit_idx);

	spin_lock_irqsave(&meson_clk_lock, flags);

	regmap_update_bits(meson8b_clk_reset->regmap, reset->reg,
			   BIT(reset->bit_idx), value);

	spin_unlock_irqrestore(&meson_clk_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक meson8b_clk_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
				     अचिन्हित दीर्घ id)
अणु
	वापस meson8b_clk_reset_update(rcdev, id, true);
पूर्ण

अटल पूर्णांक meson8b_clk_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				       अचिन्हित दीर्घ id)
अणु
	वापस meson8b_clk_reset_update(rcdev, id, false);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops meson8b_clk_reset_ops = अणु
	.निश्चित = meson8b_clk_reset_निश्चित,
	.deनिश्चित = meson8b_clk_reset_deनिश्चित,
पूर्ण;

काष्ठा meson8b_nb_data अणु
	काष्ठा notअगरier_block nb;
	काष्ठा clk_hw *cpu_clk;
पूर्ण;

अटल पूर्णांक meson8b_cpu_clk_notअगरier_cb(काष्ठा notअगरier_block *nb,
				       अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा meson8b_nb_data *nb_data =
		container_of(nb, काष्ठा meson8b_nb_data, nb);
	काष्ठा clk_hw *parent_clk;
	पूर्णांक ret;

	चयन (event) अणु
	हाल PRE_RATE_CHANGE:
		/* xtal */
		parent_clk = clk_hw_get_parent_by_index(nb_data->cpu_clk, 0);
		अवरोध;

	हाल POST_RATE_CHANGE:
		/* cpu_scale_out_sel */
		parent_clk = clk_hw_get_parent_by_index(nb_data->cpu_clk, 1);
		अवरोध;

	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	ret = clk_hw_set_parent(nb_data->cpu_clk, parent_clk);
	अगर (ret)
		वापस notअगरier_from_त्रुटि_सं(ret);

	udelay(100);

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा meson8b_nb_data meson8b_cpu_nb_data = अणु
	.nb.notअगरier_call = meson8b_cpu_clk_notअगरier_cb,
पूर्ण;

अटल व्योम __init meson8b_clkc_init_common(काष्ठा device_node *np,
			काष्ठा clk_hw_onecell_data *clk_hw_onecell_data)
अणु
	काष्ठा meson8b_clk_reset *rstc;
	स्थिर अक्षर *notअगरier_clk_name;
	काष्ठा clk *notअगरier_clk;
	काष्ठा regmap *map;
	पूर्णांक i, ret;

	map = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(map)) अणु
		pr_err("failed to get HHI regmap - Trying obsolete regs\n");
		वापस;
	पूर्ण

	rstc = kzalloc(माप(*rstc), GFP_KERNEL);
	अगर (!rstc)
		वापस;

	/* Reset Controller */
	rstc->regmap = map;
	rstc->reset.ops = &meson8b_clk_reset_ops;
	rstc->reset.nr_resets = ARRAY_SIZE(meson8b_clk_reset_bits);
	rstc->reset.of_node = np;
	ret = reset_controller_रेजिस्टर(&rstc->reset);
	अगर (ret) अणु
		pr_err("%s: Failed to register clkc reset controller: %d\n",
		       __func__, ret);
		वापस;
	पूर्ण

	/* Populate regmap क्रम the regmap backed घड़ीs */
	क्रम (i = 0; i < ARRAY_SIZE(meson8b_clk_regmaps); i++)
		meson8b_clk_regmaps[i]->map = map;

	/*
	 * रेजिस्टर all clks and start with the first used ID (which is
	 * CLKID_PLL_FIXED)
	 */
	क्रम (i = CLKID_PLL_FIXED; i < CLK_NR_CLKS; i++) अणु
		/* array might be sparse */
		अगर (!clk_hw_onecell_data->hws[i])
			जारी;

		ret = of_clk_hw_रेजिस्टर(np, clk_hw_onecell_data->hws[i]);
		अगर (ret)
			वापस;
	पूर्ण

	meson8b_cpu_nb_data.cpu_clk = clk_hw_onecell_data->hws[CLKID_CPUCLK];

	/*
	 * FIXME we shouldn't program the muxes in notअगरier handlers. The
	 * tricky programming sequence will be handled by the क्रमthcoming
	 * coordinated घड़ी rates mechanism once that feature is released.
	 */
	notअगरier_clk_name = clk_hw_get_name(&meson8b_cpu_scale_out_sel.hw);
	notअगरier_clk = __clk_lookup(notअगरier_clk_name);
	ret = clk_notअगरier_रेजिस्टर(notअगरier_clk, &meson8b_cpu_nb_data.nb);
	अगर (ret) अणु
		pr_err("%s: failed to register the CPU clock notifier\n",
		       __func__);
		वापस;
	पूर्ण

	ret = of_clk_add_hw_provider(np, of_clk_hw_onecell_get,
				     clk_hw_onecell_data);
	अगर (ret)
		pr_err("%s: failed to register clock provider\n", __func__);
पूर्ण

अटल व्योम __init meson8_clkc_init(काष्ठा device_node *np)
अणु
	वापस meson8b_clkc_init_common(np, &meson8_hw_onecell_data);
पूर्ण

अटल व्योम __init meson8b_clkc_init(काष्ठा device_node *np)
अणु
	वापस meson8b_clkc_init_common(np, &meson8b_hw_onecell_data);
पूर्ण

अटल व्योम __init meson8m2_clkc_init(काष्ठा device_node *np)
अणु
	वापस meson8b_clkc_init_common(np, &meson8m2_hw_onecell_data);
पूर्ण

CLK_OF_DECLARE_DRIVER(meson8_clkc, "amlogic,meson8-clkc",
		      meson8_clkc_init);
CLK_OF_DECLARE_DRIVER(meson8b_clkc, "amlogic,meson8b-clkc",
		      meson8b_clkc_init);
CLK_OF_DECLARE_DRIVER(meson8m2_clkc, "amlogic,meson8m2-clkc",
		      meson8m2_clkc_init);
