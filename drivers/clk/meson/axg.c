<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * AmLogic Meson-AXG Clock Controller Driver
 *
 * Copyright (c) 2016 Baylibre SAS.
 * Author: Michael Turquette <mturquette@baylibre.com>
 *
 * Copyright (c) 2017 Amlogic, inc.
 * Author: Qiufang Dai <qiufang.dai@amlogic.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>

#समावेश "clk-regmap.h"
#समावेश "clk-pll.h"
#समावेश "clk-mpll.h"
#समावेश "axg.h"
#समावेश "meson-eeclk.h"

अटल DEFINE_SPINLOCK(meson_clk_lock);

अटल काष्ठा clk_regmap axg_fixed_pll_dco = अणु
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
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_fixed_pll = अणु
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
			&axg_fixed_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
		/*
		 * This घड़ी won't ever change at runसमय so
		 * CLK_SET_RATE_PARENT is not required
		 */
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_sys_pll_dco = अणु
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
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sys_pll_dco",
		.ops = &meson_clk_pll_ro_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			.fw_name = "xtal",
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_sys_pll = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_SYS_PLL_CNTL,
		.shअगरt = 16,
		.width = 2,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sys_pll",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_sys_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pll_params_table axg_gp0_pll_params_table[] = अणु
	PLL_PARAMS(40, 1),
	PLL_PARAMS(41, 1),
	PLL_PARAMS(42, 1),
	PLL_PARAMS(43, 1),
	PLL_PARAMS(44, 1),
	PLL_PARAMS(45, 1),
	PLL_PARAMS(46, 1),
	PLL_PARAMS(47, 1),
	PLL_PARAMS(48, 1),
	PLL_PARAMS(49, 1),
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
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence axg_gp0_init_regs[] = अणु
	अणु .reg = HHI_GP0_PLL_CNTL1,	.def = 0xc084b000 पूर्ण,
	अणु .reg = HHI_GP0_PLL_CNTL2,	.def = 0xb75020be पूर्ण,
	अणु .reg = HHI_GP0_PLL_CNTL3,	.def = 0x0a59a288 पूर्ण,
	अणु .reg = HHI_GP0_PLL_CNTL4,	.def = 0xc000004d पूर्ण,
	अणु .reg = HHI_GP0_PLL_CNTL5,	.def = 0x00078000 पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_gp0_pll_dco = अणु
	.data = &(काष्ठा meson_clk_pll_data)अणु
		.en = अणु
			.reg_off = HHI_GP0_PLL_CNTL,
			.shअगरt   = 30,
			.width   = 1,
		पूर्ण,
		.m = अणु
			.reg_off = HHI_GP0_PLL_CNTL,
			.shअगरt   = 0,
			.width   = 9,
		पूर्ण,
		.n = अणु
			.reg_off = HHI_GP0_PLL_CNTL,
			.shअगरt   = 9,
			.width   = 5,
		पूर्ण,
		.frac = अणु
			.reg_off = HHI_GP0_PLL_CNTL1,
			.shअगरt   = 0,
			.width   = 10,
		पूर्ण,
		.l = अणु
			.reg_off = HHI_GP0_PLL_CNTL,
			.shअगरt   = 31,
			.width   = 1,
		पूर्ण,
		.rst = अणु
			.reg_off = HHI_GP0_PLL_CNTL,
			.shअगरt   = 29,
			.width   = 1,
		पूर्ण,
		.table = axg_gp0_pll_params_table,
		.init_regs = axg_gp0_init_regs,
		.init_count = ARRAY_SIZE(axg_gp0_init_regs),
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gp0_pll_dco",
		.ops = &meson_clk_pll_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			.fw_name = "xtal",
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_gp0_pll = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_GP0_PLL_CNTL,
		.shअगरt = 16,
		.width = 2,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gp0_pll",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_gp0_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence axg_hअगरi_init_regs[] = अणु
	अणु .reg = HHI_HIFI_PLL_CNTL1,	.def = 0xc084b000 पूर्ण,
	अणु .reg = HHI_HIFI_PLL_CNTL2,	.def = 0xb75020be पूर्ण,
	अणु .reg = HHI_HIFI_PLL_CNTL3,	.def = 0x0a6a3a88 पूर्ण,
	अणु .reg = HHI_HIFI_PLL_CNTL4,	.def = 0xc000004d पूर्ण,
	अणु .reg = HHI_HIFI_PLL_CNTL5,	.def = 0x00058000 पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_hअगरi_pll_dco = अणु
	.data = &(काष्ठा meson_clk_pll_data)अणु
		.en = अणु
			.reg_off = HHI_HIFI_PLL_CNTL,
			.shअगरt   = 30,
			.width   = 1,
		पूर्ण,
		.m = अणु
			.reg_off = HHI_HIFI_PLL_CNTL,
			.shअगरt   = 0,
			.width   = 9,
		पूर्ण,
		.n = अणु
			.reg_off = HHI_HIFI_PLL_CNTL,
			.shअगरt   = 9,
			.width   = 5,
		पूर्ण,
		.frac = अणु
			.reg_off = HHI_HIFI_PLL_CNTL5,
			.shअगरt   = 0,
			.width   = 13,
		पूर्ण,
		.l = अणु
			.reg_off = HHI_HIFI_PLL_CNTL,
			.shअगरt   = 31,
			.width   = 1,
		पूर्ण,
		.rst = अणु
			.reg_off = HHI_HIFI_PLL_CNTL,
			.shअगरt   = 29,
			.width   = 1,
		पूर्ण,
		.table = axg_gp0_pll_params_table,
		.init_regs = axg_hअगरi_init_regs,
		.init_count = ARRAY_SIZE(axg_hअगरi_init_regs),
		.flags = CLK_MESON_PLL_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "hifi_pll_dco",
		.ops = &meson_clk_pll_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			.fw_name = "xtal",
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_hअगरi_pll = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_HIFI_PLL_CNTL,
		.shअगरt = 16,
		.width = 2,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "hifi_pll",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_hअगरi_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor axg_fclk_भाग2_भाग = अणु
	.mult = 1,
	.भाग = 2,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div2_div",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_fixed_pll.hw पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_fclk_भाग2 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL_CNTL6,
		.bit_idx = 27,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div2",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_fclk_भाग2_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_IS_CRITICAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor axg_fclk_भाग3_भाग = अणु
	.mult = 1,
	.भाग = 3,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div3_div",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_fixed_pll.hw पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_fclk_भाग3 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL_CNTL6,
		.bit_idx = 28,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div3",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_fclk_भाग3_भाग.hw
		पूर्ण,
		.num_parents = 1,
		/*
		 * FIXME:
		 * This घड़ी, as fभाग2, is used by the SCPI FW and is required
		 * by the platक्रमm to operate correctly.
		 * Until the following condition are met, we need this घड़ी to
		 * be marked as critical:
		 * a) The SCPI generic driver claims and enable all the घड़ीs
		 *    it needs
		 * b) CCF has a घड़ी hand-off mechanism to make the sure the
		 *    घड़ी stays on until the proper driver comes aदीर्घ
		 */
		.flags = CLK_IS_CRITICAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor axg_fclk_भाग4_भाग = अणु
	.mult = 1,
	.भाग = 4,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div4_div",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_fixed_pll.hw पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_fclk_भाग4 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL_CNTL6,
		.bit_idx = 29,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div4",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_fclk_भाग4_भाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor axg_fclk_भाग5_भाग = अणु
	.mult = 1,
	.भाग = 5,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div5_div",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_fixed_pll.hw पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_fclk_भाग5 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL_CNTL6,
		.bit_idx = 30,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div5",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_fclk_भाग5_भाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor axg_fclk_भाग7_भाग = अणु
	.mult = 1,
	.भाग = 7,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div7_div",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_fixed_pll.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_fclk_भाग7 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL_CNTL6,
		.bit_idx = 31,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div7",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_fclk_भाग7_भाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_mpll_preभाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_MPLL_CNTL5,
		.shअगरt = 12,
		.width = 1,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll_prediv",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_fixed_pll.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_mpll0_भाग = अणु
	.data = &(काष्ठा meson_clk_mpll_data)अणु
		.sdm = अणु
			.reg_off = HHI_MPLL_CNTL7,
			.shअगरt   = 0,
			.width   = 14,
		पूर्ण,
		.sdm_en = अणु
			.reg_off = HHI_MPLL_CNTL7,
			.shअगरt   = 15,
			.width	 = 1,
		पूर्ण,
		.n2 = अणु
			.reg_off = HHI_MPLL_CNTL7,
			.shअगरt   = 16,
			.width   = 9,
		पूर्ण,
		.misc = अणु
			.reg_off = HHI_PLL_TOP_MISC,
			.shअगरt   = 0,
			.width	 = 1,
		पूर्ण,
		.lock = &meson_clk_lock,
		.flags = CLK_MESON_MPLL_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll0_div",
		.ops = &meson_clk_mpll_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_mpll_preभाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_mpll0 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL_CNTL7,
		.bit_idx = 14,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll0",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_mpll0_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_mpll1_भाग = अणु
	.data = &(काष्ठा meson_clk_mpll_data)अणु
		.sdm = अणु
			.reg_off = HHI_MPLL_CNTL8,
			.shअगरt   = 0,
			.width   = 14,
		पूर्ण,
		.sdm_en = अणु
			.reg_off = HHI_MPLL_CNTL8,
			.shअगरt   = 15,
			.width	 = 1,
		पूर्ण,
		.n2 = अणु
			.reg_off = HHI_MPLL_CNTL8,
			.shअगरt   = 16,
			.width   = 9,
		पूर्ण,
		.misc = अणु
			.reg_off = HHI_PLL_TOP_MISC,
			.shअगरt   = 1,
			.width	 = 1,
		पूर्ण,
		.lock = &meson_clk_lock,
		.flags = CLK_MESON_MPLL_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll1_div",
		.ops = &meson_clk_mpll_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_mpll_preभाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_mpll1 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL_CNTL8,
		.bit_idx = 14,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll1",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_mpll1_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_mpll2_भाग = अणु
	.data = &(काष्ठा meson_clk_mpll_data)अणु
		.sdm = अणु
			.reg_off = HHI_MPLL_CNTL9,
			.shअगरt   = 0,
			.width   = 14,
		पूर्ण,
		.sdm_en = अणु
			.reg_off = HHI_MPLL_CNTL9,
			.shअगरt   = 15,
			.width	 = 1,
		पूर्ण,
		.n2 = अणु
			.reg_off = HHI_MPLL_CNTL9,
			.shअगरt   = 16,
			.width   = 9,
		पूर्ण,
		.ssen = अणु
			.reg_off = HHI_MPLL_CNTL,
			.shअगरt   = 25,
			.width	 = 1,
		पूर्ण,
		.misc = अणु
			.reg_off = HHI_PLL_TOP_MISC,
			.shअगरt   = 2,
			.width	 = 1,
		पूर्ण,
		.lock = &meson_clk_lock,
		.flags = CLK_MESON_MPLL_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll2_div",
		.ops = &meson_clk_mpll_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_mpll_preभाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_mpll2 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL_CNTL9,
		.bit_idx = 14,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll2",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_mpll2_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_mpll3_भाग = अणु
	.data = &(काष्ठा meson_clk_mpll_data)अणु
		.sdm = अणु
			.reg_off = HHI_MPLL3_CNTL0,
			.shअगरt   = 12,
			.width   = 14,
		पूर्ण,
		.sdm_en = अणु
			.reg_off = HHI_MPLL3_CNTL0,
			.shअगरt   = 11,
			.width	 = 1,
		पूर्ण,
		.n2 = अणु
			.reg_off = HHI_MPLL3_CNTL0,
			.shअगरt   = 2,
			.width   = 9,
		पूर्ण,
		.misc = अणु
			.reg_off = HHI_PLL_TOP_MISC,
			.shअगरt   = 3,
			.width	 = 1,
		पूर्ण,
		.lock = &meson_clk_lock,
		.flags = CLK_MESON_MPLL_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll3_div",
		.ops = &meson_clk_mpll_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_mpll_preभाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_mpll3 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL3_CNTL0,
		.bit_idx = 0,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll3",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_mpll3_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pll_params_table axg_pcie_pll_params_table[] = अणु
	अणु
		.m = 200,
		.n = 3,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence axg_pcie_init_regs[] = अणु
	अणु .reg = HHI_PCIE_PLL_CNTL1,	.def = 0x0084a2aa पूर्ण,
	अणु .reg = HHI_PCIE_PLL_CNTL2,	.def = 0xb75020be पूर्ण,
	अणु .reg = HHI_PCIE_PLL_CNTL3,	.def = 0x0a47488e पूर्ण,
	अणु .reg = HHI_PCIE_PLL_CNTL4,	.def = 0xc000004d पूर्ण,
	अणु .reg = HHI_PCIE_PLL_CNTL5,	.def = 0x00078000 पूर्ण,
	अणु .reg = HHI_PCIE_PLL_CNTL6,	.def = 0x002323c6 पूर्ण,
	अणु .reg = HHI_PCIE_PLL_CNTL,     .def = 0x400106c8 पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_pcie_pll_dco = अणु
	.data = &(काष्ठा meson_clk_pll_data)अणु
		.en = अणु
			.reg_off = HHI_PCIE_PLL_CNTL,
			.shअगरt   = 30,
			.width   = 1,
		पूर्ण,
		.m = अणु
			.reg_off = HHI_PCIE_PLL_CNTL,
			.shअगरt   = 0,
			.width   = 9,
		पूर्ण,
		.n = अणु
			.reg_off = HHI_PCIE_PLL_CNTL,
			.shअगरt   = 9,
			.width   = 5,
		पूर्ण,
		.frac = अणु
			.reg_off = HHI_PCIE_PLL_CNTL1,
			.shअगरt   = 0,
			.width   = 12,
		पूर्ण,
		.l = अणु
			.reg_off = HHI_PCIE_PLL_CNTL,
			.shअगरt   = 31,
			.width   = 1,
		पूर्ण,
		.rst = अणु
			.reg_off = HHI_PCIE_PLL_CNTL,
			.shअगरt   = 29,
			.width   = 1,
		पूर्ण,
		.table = axg_pcie_pll_params_table,
		.init_regs = axg_pcie_init_regs,
		.init_count = ARRAY_SIZE(axg_pcie_init_regs),
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pcie_pll_dco",
		.ops = &meson_clk_pll_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			.fw_name = "xtal",
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_pcie_pll_od = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_PCIE_PLL_CNTL,
		.shअगरt = 16,
		.width = 2,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pcie_pll_od",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_pcie_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_pcie_pll = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_PCIE_PLL_CNTL6,
		.shअगरt = 6,
		.width = 2,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pcie_pll",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_pcie_pll_od.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_pcie_mux = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_PCIE_PLL_CNTL6,
		.mask = 0x1,
		.shअगरt = 2,
		/* skip the parent mpll3, reserved क्रम debug */
		.table = (u32[])अणु 1 पूर्ण,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pcie_mux",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_pcie_pll.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_pcie_ref = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_PCIE_PLL_CNTL6,
		.mask = 0x1,
		.shअगरt = 1,
		/* skip the parent 0, reserved क्रम debug */
		.table = (u32[])अणु 1 पूर्ण,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pcie_ref",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_pcie_mux.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_pcie_cml_en0 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_PCIE_PLL_CNTL6,
		.bit_idx = 4,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "pcie_cml_en0",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_pcie_ref.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,

	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_pcie_cml_en1 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_PCIE_PLL_CNTL6,
		.bit_idx = 3,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "pcie_cml_en1",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_pcie_ref.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल u32 mux_table_clk81[]	= अणु 0, 2, 3, 4, 5, 6, 7 पूर्ण;
अटल स्थिर काष्ठा clk_parent_data clk81_parent_data[] = अणु
	अणु .fw_name = "xtal", पूर्ण,
	अणु .hw = &axg_fclk_भाग7.hw पूर्ण,
	अणु .hw = &axg_mpll1.hw पूर्ण,
	अणु .hw = &axg_mpll2.hw पूर्ण,
	अणु .hw = &axg_fclk_भाग4.hw पूर्ण,
	अणु .hw = &axg_fclk_भाग3.hw पूर्ण,
	अणु .hw = &axg_fclk_भाग5.hw पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_mpeg_clk_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_MPEG_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 12,
		.table = mux_table_clk81,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpeg_clk_sel",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_data = clk81_parent_data,
		.num_parents = ARRAY_SIZE(clk81_parent_data),
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_mpeg_clk_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_MPEG_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpeg_clk_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_mpeg_clk_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_clk81 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPEG_CLK_CNTL,
		.bit_idx = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk81",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_mpeg_clk_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = (CLK_SET_RATE_PARENT | CLK_IS_CRITICAL),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data axg_sd_emmc_clk0_parent_data[] = अणु
	अणु .fw_name = "xtal", पूर्ण,
	अणु .hw = &axg_fclk_भाग2.hw पूर्ण,
	अणु .hw = &axg_fclk_भाग3.hw पूर्ण,
	अणु .hw = &axg_fclk_भाग5.hw पूर्ण,
	अणु .hw = &axg_fclk_भाग7.hw पूर्ण,
	/*
	 * Following these parent घड़ीs, we should also have had mpll2, mpll3
	 * and gp0_pll but these घड़ीs are too precious to be used here. All
	 * the necessary rates क्रम MMC and न_अंकD operation can be acheived using
	 * xtal or fclk_भाग घड़ीs
	 */
पूर्ण;

/* SDcard घड़ी */
अटल काष्ठा clk_regmap axg_sd_emmc_b_clk0_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SD_EMMC_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 25,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "sd_emmc_b_clk0_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_data = axg_sd_emmc_clk0_parent_data,
		.num_parents = ARRAY_SIZE(axg_sd_emmc_clk0_parent_data),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_sd_emmc_b_clk0_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_SD_EMMC_CLK_CNTL,
		.shअगरt = 16,
		.width = 7,
		.flags = CLK_DIVIDER_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "sd_emmc_b_clk0_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_sd_emmc_b_clk0_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_sd_emmc_b_clk0 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SD_EMMC_CLK_CNTL,
		.bit_idx = 23,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sd_emmc_b_clk0",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_sd_emmc_b_clk0_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* EMMC/न_अंकD घड़ी */
अटल काष्ठा clk_regmap axg_sd_emmc_c_clk0_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_न_अंकD_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 9,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "sd_emmc_c_clk0_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_data = axg_sd_emmc_clk0_parent_data,
		.num_parents = ARRAY_SIZE(axg_sd_emmc_clk0_parent_data),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_sd_emmc_c_clk0_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_न_अंकD_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
		.flags = CLK_DIVIDER_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "sd_emmc_c_clk0_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_sd_emmc_c_clk0_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_sd_emmc_c_clk0 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_न_अंकD_CLK_CNTL,
		.bit_idx = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sd_emmc_c_clk0",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_sd_emmc_c_clk0_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* VPU Clock */

अटल स्थिर काष्ठा clk_hw *axg_vpu_parent_hws[] = अणु
	&axg_fclk_भाग4.hw,
	&axg_fclk_भाग3.hw,
	&axg_fclk_भाग5.hw,
	&axg_fclk_भाग7.hw,
पूर्ण;

अटल काष्ठा clk_regmap axg_vpu_0_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.mask = 0x3,
		.shअगरt = 9,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vpu_0_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = axg_vpu_parent_hws,
		.num_parents = ARRAY_SIZE(axg_vpu_parent_hws),
		/* We need a specअगरic parent क्रम VPU घड़ी source, let it be set in DT */
		.flags = CLK_SET_RATE_NO_REPARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vpu_0_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vpu_0_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_vpu_0_sel.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vpu_0 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vpu_0",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_vpu_0_भाग.hw पूर्ण,
		.num_parents = 1,
		/*
		 * We want to aव्योम CCF to disable the VPU घड़ी अगर
		 * display has been set by Bootloader
		 */
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vpu_1_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.mask = 0x3,
		.shअगरt = 25,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vpu_1_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = axg_vpu_parent_hws,
		.num_parents = ARRAY_SIZE(axg_vpu_parent_hws),
		/* We need a specअगरic parent क्रम VPU घड़ी source, let it be set in DT */
		.flags = CLK_SET_RATE_NO_REPARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vpu_1_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.shअगरt = 16,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vpu_1_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_vpu_1_sel.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vpu_1 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.bit_idx = 24,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vpu_1",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_vpu_1_भाग.hw पूर्ण,
		.num_parents = 1,
		/*
		 * We want to aव्योम CCF to disable the VPU घड़ी अगर
		 * display has been set by Bootloader
		 */
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vpu = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.mask = 1,
		.shअगरt = 31,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vpu",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_vpu_0.hw,
			&axg_vpu_1.hw
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_NO_REPARENT,
	पूर्ण,
पूर्ण;

/* VAPB Clock */

अटल काष्ठा clk_regmap axg_vapb_0_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VAPBCLK_CNTL,
		.mask = 0x3,
		.shअगरt = 9,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vapb_0_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = axg_vpu_parent_hws,
		.num_parents = ARRAY_SIZE(axg_vpu_parent_hws),
		.flags = CLK_SET_RATE_NO_REPARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vapb_0_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VAPBCLK_CNTL,
		.shअगरt = 0,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vapb_0_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_vapb_0_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vapb_0 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VAPBCLK_CNTL,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vapb_0",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_vapb_0_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vapb_1_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VAPBCLK_CNTL,
		.mask = 0x3,
		.shअगरt = 25,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vapb_1_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = axg_vpu_parent_hws,
		.num_parents = ARRAY_SIZE(axg_vpu_parent_hws),
		.flags = CLK_SET_RATE_NO_REPARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vapb_1_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VAPBCLK_CNTL,
		.shअगरt = 16,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vapb_1_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_vapb_1_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vapb_1 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VAPBCLK_CNTL,
		.bit_idx = 24,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vapb_1",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_vapb_1_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vapb_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VAPBCLK_CNTL,
		.mask = 1,
		.shअगरt = 31,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vapb_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_vapb_0.hw,
			&axg_vapb_1.hw
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_NO_REPARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vapb = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VAPBCLK_CNTL,
		.bit_idx = 30,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vapb",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_vapb_sel.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

/* Video Clocks */

अटल स्थिर काष्ठा clk_hw *axg_vclk_parent_hws[] = अणु
	&axg_gp0_pll.hw,
	&axg_fclk_भाग4.hw,
	&axg_fclk_भाग3.hw,
	&axg_fclk_भाग5.hw,
	&axg_fclk_भाग2.hw,
	&axg_fclk_भाग7.hw,
	&axg_mpll1.hw,
पूर्ण;

अटल काष्ठा clk_regmap axg_vclk_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 16,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = axg_vclk_parent_hws,
		.num_parents = ARRAY_SIZE(axg_vclk_parent_hws),
		.flags = CLK_SET_RATE_NO_REPARENT | CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vclk2_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VIID_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 16,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = axg_vclk_parent_hws,
		.num_parents = ARRAY_SIZE(axg_vclk_parent_hws),
		.flags = CLK_SET_RATE_NO_REPARENT | CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vclk_input = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_DIV,
		.bit_idx = 16,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk_input",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_vclk_sel.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vclk2_input = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_DIV,
		.bit_idx = 16,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk2_input",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_vclk2_sel.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vclk_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VID_CLK_DIV,
		.shअगरt = 0,
		.width = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_vclk_input.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vclk2_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VIID_CLK_DIV,
		.shअगरt = 0,
		.width = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_vclk2_input.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vclk = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.bit_idx = 19,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_vclk_भाग.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vclk2 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_CNTL,
		.bit_idx = 19,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk2",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_vclk2_भाग.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vclk_भाग1 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.bit_idx = 0,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk_div1",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_vclk.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vclk_भाग2_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.bit_idx = 1,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk_div2_en",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_vclk.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vclk_भाग4_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.bit_idx = 2,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk_div4_en",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_vclk.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vclk_भाग6_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.bit_idx = 3,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk_div6_en",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_vclk.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vclk_भाग12_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.bit_idx = 4,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk_div12_en",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_vclk.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vclk2_भाग1 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_CNTL,
		.bit_idx = 0,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk2_div1",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_vclk2.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vclk2_भाग2_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_CNTL,
		.bit_idx = 1,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk2_div2_en",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_vclk2.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vclk2_भाग4_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_CNTL,
		.bit_idx = 2,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk2_div4_en",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_vclk2.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vclk2_भाग6_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_CNTL,
		.bit_idx = 3,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk2_div6_en",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_vclk2.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vclk2_भाग12_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_CNTL,
		.bit_idx = 4,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk2_div12_en",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &axg_vclk2.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor axg_vclk_भाग2 = अणु
	.mult = 1,
	.भाग = 2,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_div2",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_vclk_भाग2_en.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor axg_vclk_भाग4 = अणु
	.mult = 1,
	.भाग = 4,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_div4",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_vclk_भाग4_en.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor axg_vclk_भाग6 = अणु
	.mult = 1,
	.भाग = 6,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_div6",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_vclk_भाग6_en.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor axg_vclk_भाग12 = अणु
	.mult = 1,
	.भाग = 12,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_div12",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_vclk_भाग12_en.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor axg_vclk2_भाग2 = अणु
	.mult = 1,
	.भाग = 2,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_div2",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_vclk2_भाग2_en.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor axg_vclk2_भाग4 = अणु
	.mult = 1,
	.भाग = 4,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_div4",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_vclk2_भाग4_en.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor axg_vclk2_भाग6 = अणु
	.mult = 1,
	.भाग = 6,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_div6",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_vclk2_भाग6_en.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor axg_vclk2_भाग12 = अणु
	.mult = 1,
	.भाग = 12,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_div12",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_vclk2_भाग12_en.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल u32 mux_table_cts_sel[] = अणु 0, 1, 2, 3, 4, 8, 9, 10, 11, 12 पूर्ण;
अटल स्थिर काष्ठा clk_hw *axg_cts_parent_hws[] = अणु
	&axg_vclk_भाग1.hw,
	&axg_vclk_भाग2.hw,
	&axg_vclk_भाग4.hw,
	&axg_vclk_भाग6.hw,
	&axg_vclk_भाग12.hw,
	&axg_vclk2_भाग1.hw,
	&axg_vclk2_भाग2.hw,
	&axg_vclk2_भाग4.hw,
	&axg_vclk2_भाग6.hw,
	&axg_vclk2_भाग12.hw,
पूर्ण;

अटल काष्ठा clk_regmap axg_cts_encl_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VIID_CLK_DIV,
		.mask = 0xf,
		.shअगरt = 12,
		.table = mux_table_cts_sel,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cts_encl_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = axg_cts_parent_hws,
		.num_parents = ARRAY_SIZE(axg_cts_parent_hws),
		.flags = CLK_SET_RATE_NO_REPARENT | CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_cts_encl = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL2,
		.bit_idx = 3,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "cts_encl",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_cts_encl_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

/* MIPI DSI Host Clock */

अटल u32 mux_table_axg_vdin_meas[]    = अणु 0, 1, 2, 3, 6, 7 पूर्ण;
अटल स्थिर काष्ठा clk_parent_data axg_vdin_meas_parent_data[] = अणु
	अणु .fw_name = "xtal", पूर्ण,
	अणु .hw = &axg_fclk_भाग4.hw पूर्ण,
	अणु .hw = &axg_fclk_भाग3.hw पूर्ण,
	अणु .hw = &axg_fclk_भाग5.hw पूर्ण,
	अणु .hw = &axg_fclk_भाग2.hw पूर्ण,
	अणु .hw = &axg_fclk_भाग7.hw पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vdin_meas_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VDIN_MEAS_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 21,
		.flags = CLK_MUX_ROUND_CLOSEST,
		.table = mux_table_axg_vdin_meas,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vdin_meas_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_data = axg_vdin_meas_parent_data,
		.num_parents = ARRAY_SIZE(axg_vdin_meas_parent_data),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vdin_meas_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VDIN_MEAS_CLK_CNTL,
		.shअगरt = 12,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vdin_meas_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_vdin_meas_sel.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_vdin_meas = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VDIN_MEAS_CLK_CNTL,
		.bit_idx = 20,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vdin_meas",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_vdin_meas_भाग.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल u32 mux_table_gen_clk[]	= अणु 0, 4, 5, 6, 7, 8,
				    9, 10, 11, 13, 14, पूर्ण;
अटल स्थिर काष्ठा clk_parent_data gen_clk_parent_data[] = अणु
	अणु .fw_name = "xtal", पूर्ण,
	अणु .hw = &axg_hअगरi_pll.hw पूर्ण,
	अणु .hw = &axg_mpll0.hw पूर्ण,
	अणु .hw = &axg_mpll1.hw पूर्ण,
	अणु .hw = &axg_mpll2.hw पूर्ण,
	अणु .hw = &axg_mpll3.hw पूर्ण,
	अणु .hw = &axg_fclk_भाग4.hw पूर्ण,
	अणु .hw = &axg_fclk_भाग3.hw पूर्ण,
	अणु .hw = &axg_fclk_भाग5.hw पूर्ण,
	अणु .hw = &axg_fclk_भाग7.hw पूर्ण,
	अणु .hw = &axg_gp0_pll.hw पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_gen_clk_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_GEN_CLK_CNTL,
		.mask = 0xf,
		.shअगरt = 12,
		.table = mux_table_gen_clk,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gen_clk_sel",
		.ops = &clk_regmap_mux_ops,
		/*
		 * bits 15:12 selects from 14 possible parents:
		 * xtal, [rtc_oscin_i], [sys_cpu_भाग16], [ddr_dpll_pt],
		 * hअगरi_pll, mpll0, mpll1, mpll2, mpll3, fभाग4,
		 * fभाग3, fभाग5, [cts_msr_clk], fभाग7, gp0_pll
		 */
		.parent_data = gen_clk_parent_data,
		.num_parents = ARRAY_SIZE(gen_clk_parent_data),
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_gen_clk_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_GEN_CLK_CNTL,
		.shअगरt = 0,
		.width = 11,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gen_clk_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_gen_clk_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_gen_clk = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_GEN_CLK_CNTL,
		.bit_idx = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gen_clk",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_gen_clk_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

#घोषणा MESON_GATE(_name, _reg, _bit) \
	MESON_PCLK(_name, _reg, _bit, &axg_clk81.hw)

/* Everything Else (EE) करोमुख्य gates */
अटल MESON_GATE(axg_ddr, HHI_GCLK_MPEG0, 0);
अटल MESON_GATE(axg_audio_locker, HHI_GCLK_MPEG0, 2);
अटल MESON_GATE(axg_mipi_dsi_host, HHI_GCLK_MPEG0, 3);
अटल MESON_GATE(axg_isa, HHI_GCLK_MPEG0, 5);
अटल MESON_GATE(axg_pl301, HHI_GCLK_MPEG0, 6);
अटल MESON_GATE(axg_periphs, HHI_GCLK_MPEG0, 7);
अटल MESON_GATE(axg_spicc_0, HHI_GCLK_MPEG0, 8);
अटल MESON_GATE(axg_i2c, HHI_GCLK_MPEG0, 9);
अटल MESON_GATE(axg_rng0, HHI_GCLK_MPEG0, 12);
अटल MESON_GATE(axg_uart0, HHI_GCLK_MPEG0, 13);
अटल MESON_GATE(axg_mipi_dsi_phy, HHI_GCLK_MPEG0, 14);
अटल MESON_GATE(axg_spicc_1, HHI_GCLK_MPEG0, 15);
अटल MESON_GATE(axg_pcie_a, HHI_GCLK_MPEG0, 16);
अटल MESON_GATE(axg_pcie_b, HHI_GCLK_MPEG0, 17);
अटल MESON_GATE(axg_hiu_reg, HHI_GCLK_MPEG0, 19);
अटल MESON_GATE(axg_assist_misc, HHI_GCLK_MPEG0, 23);
अटल MESON_GATE(axg_emmc_b, HHI_GCLK_MPEG0, 25);
अटल MESON_GATE(axg_emmc_c, HHI_GCLK_MPEG0, 26);
अटल MESON_GATE(axg_dma, HHI_GCLK_MPEG0, 27);
अटल MESON_GATE(axg_spi, HHI_GCLK_MPEG0, 30);

अटल MESON_GATE(axg_audio, HHI_GCLK_MPEG1, 0);
अटल MESON_GATE(axg_eth_core, HHI_GCLK_MPEG1, 3);
अटल MESON_GATE(axg_uart1, HHI_GCLK_MPEG1, 16);
अटल MESON_GATE(axg_g2d, HHI_GCLK_MPEG1, 20);
अटल MESON_GATE(axg_usb0, HHI_GCLK_MPEG1, 21);
अटल MESON_GATE(axg_usb1, HHI_GCLK_MPEG1, 22);
अटल MESON_GATE(axg_reset, HHI_GCLK_MPEG1, 23);
अटल MESON_GATE(axg_usb_general, HHI_GCLK_MPEG1, 26);
अटल MESON_GATE(axg_ahb_arb0, HHI_GCLK_MPEG1, 29);
अटल MESON_GATE(axg_efuse, HHI_GCLK_MPEG1, 30);
अटल MESON_GATE(axg_boot_rom, HHI_GCLK_MPEG1, 31);

अटल MESON_GATE(axg_ahb_data_bus, HHI_GCLK_MPEG2, 1);
अटल MESON_GATE(axg_ahb_ctrl_bus, HHI_GCLK_MPEG2, 2);
अटल MESON_GATE(axg_usb1_to_ddr, HHI_GCLK_MPEG2, 8);
अटल MESON_GATE(axg_usb0_to_ddr, HHI_GCLK_MPEG2, 9);
अटल MESON_GATE(axg_mmc_pclk, HHI_GCLK_MPEG2, 11);
अटल MESON_GATE(axg_vpu_पूर्णांकr, HHI_GCLK_MPEG2, 25);
अटल MESON_GATE(axg_sec_ahb_ahb3_bridge, HHI_GCLK_MPEG2, 26);
अटल MESON_GATE(axg_gic, HHI_GCLK_MPEG2, 30);

/* Always On (AO) करोमुख्य gates */

अटल MESON_GATE(axg_ao_media_cpu, HHI_GCLK_AO, 0);
अटल MESON_GATE(axg_ao_ahb_sram, HHI_GCLK_AO, 1);
अटल MESON_GATE(axg_ao_ahb_bus, HHI_GCLK_AO, 2);
अटल MESON_GATE(axg_ao_अगरace, HHI_GCLK_AO, 3);
अटल MESON_GATE(axg_ao_i2c, HHI_GCLK_AO, 4);

/* Array of all घड़ीs provided by this provider */

अटल काष्ठा clk_hw_onecell_data axg_hw_onecell_data = अणु
	.hws = अणु
		[CLKID_SYS_PLL]			= &axg_sys_pll.hw,
		[CLKID_FIXED_PLL]		= &axg_fixed_pll.hw,
		[CLKID_FCLK_DIV2]		= &axg_fclk_भाग2.hw,
		[CLKID_FCLK_DIV3]		= &axg_fclk_भाग3.hw,
		[CLKID_FCLK_DIV4]		= &axg_fclk_भाग4.hw,
		[CLKID_FCLK_DIV5]		= &axg_fclk_भाग5.hw,
		[CLKID_FCLK_DIV7]		= &axg_fclk_भाग7.hw,
		[CLKID_GP0_PLL]			= &axg_gp0_pll.hw,
		[CLKID_MPEG_SEL]		= &axg_mpeg_clk_sel.hw,
		[CLKID_MPEG_DIV]		= &axg_mpeg_clk_भाग.hw,
		[CLKID_CLK81]			= &axg_clk81.hw,
		[CLKID_MPLL0]			= &axg_mpll0.hw,
		[CLKID_MPLL1]			= &axg_mpll1.hw,
		[CLKID_MPLL2]			= &axg_mpll2.hw,
		[CLKID_MPLL3]			= &axg_mpll3.hw,
		[CLKID_DDR]			= &axg_ddr.hw,
		[CLKID_AUDIO_LOCKER]		= &axg_audio_locker.hw,
		[CLKID_MIPI_DSI_HOST]		= &axg_mipi_dsi_host.hw,
		[CLKID_ISA]			= &axg_isa.hw,
		[CLKID_PL301]			= &axg_pl301.hw,
		[CLKID_PERIPHS]			= &axg_periphs.hw,
		[CLKID_SPICC0]			= &axg_spicc_0.hw,
		[CLKID_I2C]			= &axg_i2c.hw,
		[CLKID_RNG0]			= &axg_rng0.hw,
		[CLKID_UART0]			= &axg_uart0.hw,
		[CLKID_MIPI_DSI_PHY]		= &axg_mipi_dsi_phy.hw,
		[CLKID_SPICC1]			= &axg_spicc_1.hw,
		[CLKID_PCIE_A]			= &axg_pcie_a.hw,
		[CLKID_PCIE_B]			= &axg_pcie_b.hw,
		[CLKID_HIU_IFACE]		= &axg_hiu_reg.hw,
		[CLKID_ASSIST_MISC]		= &axg_assist_misc.hw,
		[CLKID_SD_EMMC_B]		= &axg_emmc_b.hw,
		[CLKID_SD_EMMC_C]		= &axg_emmc_c.hw,
		[CLKID_DMA]			= &axg_dma.hw,
		[CLKID_SPI]			= &axg_spi.hw,
		[CLKID_AUDIO]			= &axg_audपन.सw,
		[CLKID_ETH]			= &axg_eth_core.hw,
		[CLKID_UART1]			= &axg_uart1.hw,
		[CLKID_G2D]			= &axg_g2d.hw,
		[CLKID_USB0]			= &axg_usb0.hw,
		[CLKID_USB1]			= &axg_usb1.hw,
		[CLKID_RESET]			= &axg_reset.hw,
		[CLKID_USB]			= &axg_usb_general.hw,
		[CLKID_AHB_ARB0]		= &axg_ahb_arb0.hw,
		[CLKID_EFUSE]			= &axg_efuse.hw,
		[CLKID_BOOT_ROM]		= &axg_boot_rom.hw,
		[CLKID_AHB_DATA_BUS]		= &axg_ahb_data_bus.hw,
		[CLKID_AHB_CTRL_BUS]		= &axg_ahb_ctrl_bus.hw,
		[CLKID_USB1_DDR_BRIDGE]		= &axg_usb1_to_ddr.hw,
		[CLKID_USB0_DDR_BRIDGE]		= &axg_usb0_to_ddr.hw,
		[CLKID_MMC_PCLK]		= &axg_mmc_pclk.hw,
		[CLKID_VPU_INTR]		= &axg_vpu_पूर्णांकr.hw,
		[CLKID_SEC_AHB_AHB3_BRIDGE]	= &axg_sec_ahb_ahb3_bridge.hw,
		[CLKID_GIC]			= &axg_gic.hw,
		[CLKID_AO_MEDIA_CPU]		= &axg_ao_media_cpu.hw,
		[CLKID_AO_AHB_SRAM]		= &axg_ao_ahb_sram.hw,
		[CLKID_AO_AHB_BUS]		= &axg_ao_ahb_bus.hw,
		[CLKID_AO_IFACE]		= &axg_ao_अगरace.hw,
		[CLKID_AO_I2C]			= &axg_ao_i2c.hw,
		[CLKID_SD_EMMC_B_CLK0_SEL]	= &axg_sd_emmc_b_clk0_sel.hw,
		[CLKID_SD_EMMC_B_CLK0_DIV]	= &axg_sd_emmc_b_clk0_भाग.hw,
		[CLKID_SD_EMMC_B_CLK0]		= &axg_sd_emmc_b_clk0.hw,
		[CLKID_SD_EMMC_C_CLK0_SEL]	= &axg_sd_emmc_c_clk0_sel.hw,
		[CLKID_SD_EMMC_C_CLK0_DIV]	= &axg_sd_emmc_c_clk0_भाग.hw,
		[CLKID_SD_EMMC_C_CLK0]		= &axg_sd_emmc_c_clk0.hw,
		[CLKID_MPLL0_DIV]		= &axg_mpll0_भाग.hw,
		[CLKID_MPLL1_DIV]		= &axg_mpll1_भाग.hw,
		[CLKID_MPLL2_DIV]		= &axg_mpll2_भाग.hw,
		[CLKID_MPLL3_DIV]		= &axg_mpll3_भाग.hw,
		[CLKID_HIFI_PLL]		= &axg_hअगरi_pll.hw,
		[CLKID_MPLL_PREDIV]		= &axg_mpll_preभाग.hw,
		[CLKID_FCLK_DIV2_DIV]		= &axg_fclk_भाग2_भाग.hw,
		[CLKID_FCLK_DIV3_DIV]		= &axg_fclk_भाग3_भाग.hw,
		[CLKID_FCLK_DIV4_DIV]		= &axg_fclk_भाग4_भाग.hw,
		[CLKID_FCLK_DIV5_DIV]		= &axg_fclk_भाग5_भाग.hw,
		[CLKID_FCLK_DIV7_DIV]		= &axg_fclk_भाग7_भाग.hw,
		[CLKID_PCIE_PLL]		= &axg_pcie_pll.hw,
		[CLKID_PCIE_MUX]		= &axg_pcie_mux.hw,
		[CLKID_PCIE_REF]		= &axg_pcie_ref.hw,
		[CLKID_PCIE_CML_EN0]		= &axg_pcie_cml_en0.hw,
		[CLKID_PCIE_CML_EN1]		= &axg_pcie_cml_en1.hw,
		[CLKID_GEN_CLK_SEL]		= &axg_gen_clk_sel.hw,
		[CLKID_GEN_CLK_DIV]		= &axg_gen_clk_भाग.hw,
		[CLKID_GEN_CLK]			= &axg_gen_clk.hw,
		[CLKID_SYS_PLL_DCO]		= &axg_sys_pll_dco.hw,
		[CLKID_FIXED_PLL_DCO]		= &axg_fixed_pll_dco.hw,
		[CLKID_GP0_PLL_DCO]		= &axg_gp0_pll_dco.hw,
		[CLKID_HIFI_PLL_DCO]		= &axg_hअगरi_pll_dco.hw,
		[CLKID_PCIE_PLL_DCO]		= &axg_pcie_pll_dco.hw,
		[CLKID_PCIE_PLL_OD]		= &axg_pcie_pll_od.hw,
		[CLKID_VPU_0_DIV]		= &axg_vpu_0_भाग.hw,
		[CLKID_VPU_0_SEL]		= &axg_vpu_0_sel.hw,
		[CLKID_VPU_0]			= &axg_vpu_0.hw,
		[CLKID_VPU_1_DIV]		= &axg_vpu_1_भाग.hw,
		[CLKID_VPU_1_SEL]		= &axg_vpu_1_sel.hw,
		[CLKID_VPU_1]			= &axg_vpu_1.hw,
		[CLKID_VPU]			= &axg_vpu.hw,
		[CLKID_VAPB_0_DIV]		= &axg_vapb_0_भाग.hw,
		[CLKID_VAPB_0_SEL]		= &axg_vapb_0_sel.hw,
		[CLKID_VAPB_0]			= &axg_vapb_0.hw,
		[CLKID_VAPB_1_DIV]		= &axg_vapb_1_भाग.hw,
		[CLKID_VAPB_1_SEL]		= &axg_vapb_1_sel.hw,
		[CLKID_VAPB_1]			= &axg_vapb_1.hw,
		[CLKID_VAPB_SEL]		= &axg_vapb_sel.hw,
		[CLKID_VAPB]			= &axg_vapb.hw,
		[CLKID_VCLK]			= &axg_vclk.hw,
		[CLKID_VCLK2]			= &axg_vclk2.hw,
		[CLKID_VCLK_SEL]		= &axg_vclk_sel.hw,
		[CLKID_VCLK2_SEL]		= &axg_vclk2_sel.hw,
		[CLKID_VCLK_INPUT]		= &axg_vclk_input.hw,
		[CLKID_VCLK2_INPUT]		= &axg_vclk2_input.hw,
		[CLKID_VCLK_DIV]		= &axg_vclk_भाग.hw,
		[CLKID_VCLK2_DIV]		= &axg_vclk2_भाग.hw,
		[CLKID_VCLK_DIV2_EN]		= &axg_vclk_भाग2_en.hw,
		[CLKID_VCLK_DIV4_EN]		= &axg_vclk_भाग4_en.hw,
		[CLKID_VCLK_DIV6_EN]		= &axg_vclk_भाग6_en.hw,
		[CLKID_VCLK_DIV12_EN]		= &axg_vclk_भाग12_en.hw,
		[CLKID_VCLK2_DIV2_EN]		= &axg_vclk2_भाग2_en.hw,
		[CLKID_VCLK2_DIV4_EN]		= &axg_vclk2_भाग4_en.hw,
		[CLKID_VCLK2_DIV6_EN]		= &axg_vclk2_भाग6_en.hw,
		[CLKID_VCLK2_DIV12_EN]		= &axg_vclk2_भाग12_en.hw,
		[CLKID_VCLK_DIV1]		= &axg_vclk_भाग1.hw,
		[CLKID_VCLK_DIV2]		= &axg_vclk_भाग2.hw,
		[CLKID_VCLK_DIV4]		= &axg_vclk_भाग4.hw,
		[CLKID_VCLK_DIV6]		= &axg_vclk_भाग6.hw,
		[CLKID_VCLK_DIV12]		= &axg_vclk_भाग12.hw,
		[CLKID_VCLK2_DIV1]		= &axg_vclk2_भाग1.hw,
		[CLKID_VCLK2_DIV2]		= &axg_vclk2_भाग2.hw,
		[CLKID_VCLK2_DIV4]		= &axg_vclk2_भाग4.hw,
		[CLKID_VCLK2_DIV6]		= &axg_vclk2_भाग6.hw,
		[CLKID_VCLK2_DIV12]		= &axg_vclk2_भाग12.hw,
		[CLKID_CTS_ENCL_SEL]		= &axg_cts_encl_sel.hw,
		[CLKID_CTS_ENCL]		= &axg_cts_encl.hw,
		[CLKID_VDIN_MEAS_SEL]		= &axg_vdin_meas_sel.hw,
		[CLKID_VDIN_MEAS_DIV]		= &axg_vdin_meas_भाग.hw,
		[CLKID_VDIN_MEAS]		= &axg_vdin_meas.hw,
		[NR_CLKS]			= शून्य,
	पूर्ण,
	.num = NR_CLKS,
पूर्ण;

/* Convenience table to populate regmap in .probe */
अटल काष्ठा clk_regmap *स्थिर axg_clk_regmaps[] = अणु
	&axg_clk81,
	&axg_ddr,
	&axg_audio_locker,
	&axg_mipi_dsi_host,
	&axg_isa,
	&axg_pl301,
	&axg_periphs,
	&axg_spicc_0,
	&axg_i2c,
	&axg_rng0,
	&axg_uart0,
	&axg_mipi_dsi_phy,
	&axg_spicc_1,
	&axg_pcie_a,
	&axg_pcie_b,
	&axg_hiu_reg,
	&axg_assist_misc,
	&axg_emmc_b,
	&axg_emmc_c,
	&axg_dma,
	&axg_spi,
	&axg_audio,
	&axg_eth_core,
	&axg_uart1,
	&axg_g2d,
	&axg_usb0,
	&axg_usb1,
	&axg_reset,
	&axg_usb_general,
	&axg_ahb_arb0,
	&axg_efuse,
	&axg_boot_rom,
	&axg_ahb_data_bus,
	&axg_ahb_ctrl_bus,
	&axg_usb1_to_ddr,
	&axg_usb0_to_ddr,
	&axg_mmc_pclk,
	&axg_vpu_पूर्णांकr,
	&axg_sec_ahb_ahb3_bridge,
	&axg_gic,
	&axg_ao_media_cpu,
	&axg_ao_ahb_sram,
	&axg_ao_ahb_bus,
	&axg_ao_अगरace,
	&axg_ao_i2c,
	&axg_sd_emmc_b_clk0,
	&axg_sd_emmc_c_clk0,
	&axg_mpeg_clk_भाग,
	&axg_sd_emmc_b_clk0_भाग,
	&axg_sd_emmc_c_clk0_भाग,
	&axg_mpeg_clk_sel,
	&axg_sd_emmc_b_clk0_sel,
	&axg_sd_emmc_c_clk0_sel,
	&axg_mpll0,
	&axg_mpll1,
	&axg_mpll2,
	&axg_mpll3,
	&axg_mpll0_भाग,
	&axg_mpll1_भाग,
	&axg_mpll2_भाग,
	&axg_mpll3_भाग,
	&axg_fixed_pll,
	&axg_sys_pll,
	&axg_gp0_pll,
	&axg_hअगरi_pll,
	&axg_mpll_preभाग,
	&axg_fclk_भाग2,
	&axg_fclk_भाग3,
	&axg_fclk_भाग4,
	&axg_fclk_भाग5,
	&axg_fclk_भाग7,
	&axg_pcie_pll_dco,
	&axg_pcie_pll_od,
	&axg_pcie_pll,
	&axg_pcie_mux,
	&axg_pcie_ref,
	&axg_pcie_cml_en0,
	&axg_pcie_cml_en1,
	&axg_gen_clk_sel,
	&axg_gen_clk_भाग,
	&axg_gen_clk,
	&axg_fixed_pll_dco,
	&axg_sys_pll_dco,
	&axg_gp0_pll_dco,
	&axg_hअगरi_pll_dco,
	&axg_pcie_pll_dco,
	&axg_pcie_pll_od,
	&axg_vpu_0_भाग,
	&axg_vpu_0_sel,
	&axg_vpu_0,
	&axg_vpu_1_भाग,
	&axg_vpu_1_sel,
	&axg_vpu_1,
	&axg_vpu,
	&axg_vapb_0_भाग,
	&axg_vapb_0_sel,
	&axg_vapb_0,
	&axg_vapb_1_भाग,
	&axg_vapb_1_sel,
	&axg_vapb_1,
	&axg_vapb_sel,
	&axg_vapb,
	&axg_vclk,
	&axg_vclk2,
	&axg_vclk_sel,
	&axg_vclk2_sel,
	&axg_vclk_input,
	&axg_vclk2_input,
	&axg_vclk_भाग,
	&axg_vclk2_भाग,
	&axg_vclk_भाग2_en,
	&axg_vclk_भाग4_en,
	&axg_vclk_भाग6_en,
	&axg_vclk_भाग12_en,
	&axg_vclk2_भाग2_en,
	&axg_vclk2_भाग4_en,
	&axg_vclk2_भाग6_en,
	&axg_vclk2_भाग12_en,
	&axg_cts_encl_sel,
	&axg_cts_encl,
	&axg_vdin_meas_sel,
	&axg_vdin_meas_भाग,
	&axg_vdin_meas,
पूर्ण;

अटल स्थिर काष्ठा meson_eeclkc_data axg_clkc_data = अणु
	.regmap_clks = axg_clk_regmaps,
	.regmap_clk_num = ARRAY_SIZE(axg_clk_regmaps),
	.hw_onecell_data = &axg_hw_onecell_data,
पूर्ण;


अटल स्थिर काष्ठा of_device_id clkc_match_table[] = अणु
	अणु .compatible = "amlogic,axg-clkc", .data = &axg_clkc_data पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, clkc_match_table);

अटल काष्ठा platक्रमm_driver axg_driver = अणु
	.probe		= meson_eeclkc_probe,
	.driver		= अणु
		.name	= "axg-clkc",
		.of_match_table = clkc_match_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(axg_driver);
MODULE_LICENSE("GPL v2");
