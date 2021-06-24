<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Amlogic Meson-G12A Clock Controller Driver
 *
 * Copyright (c) 2016 Baylibre SAS.
 * Author: Michael Turquette <mturquette@baylibre.com>
 *
 * Copyright (c) 2018 Amlogic, inc.
 * Author: Qiufang Dai <qiufang.dai@amlogic.com>
 * Author: Jian Hu <jian.hu@amlogic.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>

#समावेश "clk-mpll.h"
#समावेश "clk-pll.h"
#समावेश "clk-regmap.h"
#समावेश "clk-cpu-dyndiv.h"
#समावेश "vid-pll-div.h"
#समावेश "meson-eeclk.h"
#समावेश "g12a.h"

अटल DEFINE_SPINLOCK(meson_clk_lock);

अटल काष्ठा clk_regmap g12a_fixed_pll_dco = अणु
	.data = &(काष्ठा meson_clk_pll_data)अणु
		.en = अणु
			.reg_off = HHI_FIX_PLL_CNTL0,
			.shअगरt   = 28,
			.width   = 1,
		पूर्ण,
		.m = अणु
			.reg_off = HHI_FIX_PLL_CNTL0,
			.shअगरt   = 0,
			.width   = 8,
		पूर्ण,
		.n = अणु
			.reg_off = HHI_FIX_PLL_CNTL0,
			.shअगरt   = 10,
			.width   = 5,
		पूर्ण,
		.frac = अणु
			.reg_off = HHI_FIX_PLL_CNTL1,
			.shअगरt   = 0,
			.width   = 17,
		पूर्ण,
		.l = अणु
			.reg_off = HHI_FIX_PLL_CNTL0,
			.shअगरt   = 31,
			.width   = 1,
		पूर्ण,
		.rst = अणु
			.reg_off = HHI_FIX_PLL_CNTL0,
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

अटल काष्ठा clk_regmap g12a_fixed_pll = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_FIX_PLL_CNTL0,
		.shअगरt = 16,
		.width = 2,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fixed_pll",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_fixed_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
		/*
		 * This घड़ी won't ever change at runसमय so
		 * CLK_SET_RATE_PARENT is not required
		 */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pll_mult_range g12a_sys_pll_mult_range = अणु
	.min = 128,
	.max = 250,
पूर्ण;

अटल काष्ठा clk_regmap g12a_sys_pll_dco = अणु
	.data = &(काष्ठा meson_clk_pll_data)अणु
		.en = अणु
			.reg_off = HHI_SYS_PLL_CNTL0,
			.shअगरt   = 28,
			.width   = 1,
		पूर्ण,
		.m = अणु
			.reg_off = HHI_SYS_PLL_CNTL0,
			.shअगरt   = 0,
			.width   = 8,
		पूर्ण,
		.n = अणु
			.reg_off = HHI_SYS_PLL_CNTL0,
			.shअगरt   = 10,
			.width   = 5,
		पूर्ण,
		.l = अणु
			.reg_off = HHI_SYS_PLL_CNTL0,
			.shअगरt   = 31,
			.width   = 1,
		पूर्ण,
		.rst = अणु
			.reg_off = HHI_SYS_PLL_CNTL0,
			.shअगरt   = 29,
			.width   = 1,
		पूर्ण,
		.range = &g12a_sys_pll_mult_range,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sys_pll_dco",
		.ops = &meson_clk_pll_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			.fw_name = "xtal",
		पूर्ण,
		.num_parents = 1,
		/* This घड़ी feeds the CPU, aव्योम disabling it */
		.flags = CLK_IS_CRITICAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_sys_pll = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_SYS_PLL_CNTL0,
		.shअगरt = 16,
		.width = 3,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sys_pll",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_sys_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12b_sys1_pll_dco = अणु
	.data = &(काष्ठा meson_clk_pll_data)अणु
		.en = अणु
			.reg_off = HHI_SYS1_PLL_CNTL0,
			.shअगरt   = 28,
			.width   = 1,
		पूर्ण,
		.m = अणु
			.reg_off = HHI_SYS1_PLL_CNTL0,
			.shअगरt   = 0,
			.width   = 8,
		पूर्ण,
		.n = अणु
			.reg_off = HHI_SYS1_PLL_CNTL0,
			.shअगरt   = 10,
			.width   = 5,
		पूर्ण,
		.l = अणु
			.reg_off = HHI_SYS1_PLL_CNTL0,
			.shअगरt   = 31,
			.width   = 1,
		पूर्ण,
		.rst = अणु
			.reg_off = HHI_SYS1_PLL_CNTL0,
			.shअगरt   = 29,
			.width   = 1,
		पूर्ण,
		.range = &g12a_sys_pll_mult_range,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sys1_pll_dco",
		.ops = &meson_clk_pll_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			.fw_name = "xtal",
		पूर्ण,
		.num_parents = 1,
		/* This घड़ी feeds the CPU, aव्योम disabling it */
		.flags = CLK_IS_CRITICAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12b_sys1_pll = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_SYS1_PLL_CNTL0,
		.shअगरt = 16,
		.width = 3,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sys1_pll",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_sys1_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_sys_pll_भाग16_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL1,
		.bit_idx = 24,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "sys_pll_div16_en",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_sys_pll.hw पूर्ण,
		.num_parents = 1,
		/*
		 * This घड़ी is used to debug the sys_pll range
		 * Linux should not change it at runसमय
		 */
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12b_sys1_pll_भाग16_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SYS_CPUB_CLK_CNTL1,
		.bit_idx = 24,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "sys1_pll_div16_en",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_sys1_pll.hw
		पूर्ण,
		.num_parents = 1,
		/*
		 * This घड़ी is used to debug the sys_pll range
		 * Linux should not change it at runसमय
		 */
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12a_sys_pll_भाग16 = अणु
	.mult = 1,
	.भाग = 16,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sys_pll_div16",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_sys_pll_भाग16_en.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12b_sys1_pll_भाग16 = अणु
	.mult = 1,
	.भाग = 16,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sys1_pll_div16",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_sys1_pll_भाग16_en.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12a_fclk_भाग2_भाग = अणु
	.mult = 1,
	.भाग = 2,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div2_div",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_fixed_pll.hw पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_fclk_भाग2 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_FIX_PLL_CNTL1,
		.bit_idx = 24,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div2",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_fclk_भाग2_भाग.hw
		पूर्ण,
		.num_parents = 1,
		/*
		 * Similar to fclk_भाग3, it seems that this घड़ी is used by
		 * the resident firmware and is required by the platक्रमm to
		 * operate correctly.
		 * Until the following condition are met, we need this घड़ी to
		 * be marked as critical:
		 * a) Mark the घड़ी used by a firmware resource, अगर possible
		 * b) CCF has a घड़ी hand-off mechanism to make the sure the
		 *    घड़ी stays on until the proper driver comes aदीर्घ
		 */
		.flags = CLK_IS_CRITICAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12a_fclk_भाग3_भाग = अणु
	.mult = 1,
	.भाग = 3,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div3_div",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_fixed_pll.hw पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_fclk_भाग3 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_FIX_PLL_CNTL1,
		.bit_idx = 20,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div3",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_fclk_भाग3_भाग.hw
		पूर्ण,
		.num_parents = 1,
		/*
		 * This घड़ी is used by the resident firmware and is required
		 * by the platक्रमm to operate correctly.
		 * Until the following condition are met, we need this घड़ी to
		 * be marked as critical:
		 * a) Mark the घड़ी used by a firmware resource, अगर possible
		 * b) CCF has a घड़ी hand-off mechanism to make the sure the
		 *    घड़ी stays on until the proper driver comes aदीर्घ
		 */
		.flags = CLK_IS_CRITICAL,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "premux0" */
अटल काष्ठा clk_regmap g12a_cpu_clk_premux0 = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL0,
		.mask = 0x3,
		.shअगरt = 0,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk_dyn0_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_data = (स्थिर काष्ठा clk_parent_data []) अणु
			अणु .fw_name = "xtal", पूर्ण,
			अणु .hw = &g12a_fclk_भाग2.hw पूर्ण,
			अणु .hw = &g12a_fclk_भाग3.hw पूर्ण,
		पूर्ण,
		.num_parents = 3,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "premux1" */
अटल काष्ठा clk_regmap g12a_cpu_clk_premux1 = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL0,
		.mask = 0x3,
		.shअगरt = 16,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk_dyn1_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_data = (स्थिर काष्ठा clk_parent_data []) अणु
			अणु .fw_name = "xtal", पूर्ण,
			अणु .hw = &g12a_fclk_भाग2.hw पूर्ण,
			अणु .hw = &g12a_fclk_भाग3.hw पूर्ण,
		पूर्ण,
		.num_parents = 3,
		/* This sub-tree is used a parking घड़ी */
		.flags = CLK_SET_RATE_NO_REPARENT
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "mux0_divn_tcnt" */
अटल काष्ठा clk_regmap g12a_cpu_clk_mux0_भाग = अणु
	.data = &(काष्ठा meson_clk_cpu_dynभाग_data)अणु
		.भाग = अणु
			.reg_off = HHI_SYS_CPU_CLK_CNTL0,
			.shअगरt = 4,
			.width = 6,
		पूर्ण,
		.dyn = अणु
			.reg_off = HHI_SYS_CPU_CLK_CNTL0,
			.shअगरt = 26,
			.width = 1,
		पूर्ण,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk_dyn0_div",
		.ops = &meson_clk_cpu_dynभाग_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_cpu_clk_premux0.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "postmux0" */
अटल काष्ठा clk_regmap g12a_cpu_clk_posपंचांगux0 = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL0,
		.mask = 0x1,
		.shअगरt = 2,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk_dyn0",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_cpu_clk_premux0.hw,
			&g12a_cpu_clk_mux0_भाग.hw,
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "Mux1_divn_tcnt" */
अटल काष्ठा clk_regmap g12a_cpu_clk_mux1_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL0,
		.shअगरt = 20,
		.width = 6,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk_dyn1_div",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_cpu_clk_premux1.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "postmux1" */
अटल काष्ठा clk_regmap g12a_cpu_clk_posपंचांगux1 = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL0,
		.mask = 0x1,
		.shअगरt = 18,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk_dyn1",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_cpu_clk_premux1.hw,
			&g12a_cpu_clk_mux1_भाग.hw,
		पूर्ण,
		.num_parents = 2,
		/* This sub-tree is used a parking घड़ी */
		.flags = CLK_SET_RATE_NO_REPARENT,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "Final_dyn_mux_sel" */
अटल काष्ठा clk_regmap g12a_cpu_clk_dyn = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL0,
		.mask = 0x1,
		.shअगरt = 10,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk_dyn",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_cpu_clk_posपंचांगux0.hw,
			&g12a_cpu_clk_posपंचांगux1.hw,
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "Final_mux_sel" */
अटल काष्ठा clk_regmap g12a_cpu_clk = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL0,
		.mask = 0x1,
		.shअगरt = 11,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_cpu_clk_dyn.hw,
			&g12a_sys_pll.hw,
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "Final_mux_sel" */
अटल काष्ठा clk_regmap g12b_cpu_clk = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL0,
		.mask = 0x1,
		.shअगरt = 11,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_cpu_clk_dyn.hw,
			&g12b_sys1_pll.hw
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "premux0" */
अटल काष्ठा clk_regmap g12b_cpub_clk_premux0 = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPUB_CLK_CNTL,
		.mask = 0x3,
		.shअगरt = 0,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpub_clk_dyn0_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_data = (स्थिर काष्ठा clk_parent_data []) अणु
			अणु .fw_name = "xtal", पूर्ण,
			अणु .hw = &g12a_fclk_भाग2.hw पूर्ण,
			अणु .hw = &g12a_fclk_भाग3.hw पूर्ण,
		पूर्ण,
		.num_parents = 3,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "mux0_divn_tcnt" */
अटल काष्ठा clk_regmap g12b_cpub_clk_mux0_भाग = अणु
	.data = &(काष्ठा meson_clk_cpu_dynभाग_data)अणु
		.भाग = अणु
			.reg_off = HHI_SYS_CPUB_CLK_CNTL,
			.shअगरt = 4,
			.width = 6,
		पूर्ण,
		.dyn = अणु
			.reg_off = HHI_SYS_CPUB_CLK_CNTL,
			.shअगरt = 26,
			.width = 1,
		पूर्ण,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpub_clk_dyn0_div",
		.ops = &meson_clk_cpu_dynभाग_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk_premux0.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "postmux0" */
अटल काष्ठा clk_regmap g12b_cpub_clk_posपंचांगux0 = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPUB_CLK_CNTL,
		.mask = 0x1,
		.shअगरt = 2,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpub_clk_dyn0",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk_premux0.hw,
			&g12b_cpub_clk_mux0_भाग.hw
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "premux1" */
अटल काष्ठा clk_regmap g12b_cpub_clk_premux1 = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPUB_CLK_CNTL,
		.mask = 0x3,
		.shअगरt = 16,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpub_clk_dyn1_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_data = (स्थिर काष्ठा clk_parent_data []) अणु
			अणु .fw_name = "xtal", पूर्ण,
			अणु .hw = &g12a_fclk_भाग2.hw पूर्ण,
			अणु .hw = &g12a_fclk_भाग3.hw पूर्ण,
		पूर्ण,
		.num_parents = 3,
		/* This sub-tree is used a parking घड़ी */
		.flags = CLK_SET_RATE_NO_REPARENT,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "Mux1_divn_tcnt" */
अटल काष्ठा clk_regmap g12b_cpub_clk_mux1_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_SYS_CPUB_CLK_CNTL,
		.shअगरt = 20,
		.width = 6,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpub_clk_dyn1_div",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk_premux1.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "postmux1" */
अटल काष्ठा clk_regmap g12b_cpub_clk_posपंचांगux1 = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPUB_CLK_CNTL,
		.mask = 0x1,
		.shअगरt = 18,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpub_clk_dyn1",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk_premux1.hw,
			&g12b_cpub_clk_mux1_भाग.hw
		पूर्ण,
		.num_parents = 2,
		/* This sub-tree is used a parking घड़ी */
		.flags = CLK_SET_RATE_NO_REPARENT,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "Final_dyn_mux_sel" */
अटल काष्ठा clk_regmap g12b_cpub_clk_dyn = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPUB_CLK_CNTL,
		.mask = 0x1,
		.shअगरt = 10,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpub_clk_dyn",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk_posपंचांगux0.hw,
			&g12b_cpub_clk_posपंचांगux1.hw
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "Final_mux_sel" */
अटल काष्ठा clk_regmap g12b_cpub_clk = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPUB_CLK_CNTL,
		.mask = 0x1,
		.shअगरt = 11,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpub_clk",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk_dyn.hw,
			&g12a_sys_pll.hw
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap sm1_gp1_pll;

/* Datasheet names this field as "premux0" */
अटल काष्ठा clk_regmap sm1_dsu_clk_premux0 = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL5,
		.mask = 0x3,
		.shअगरt = 0,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "dsu_clk_dyn0_sel",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_data = (स्थिर काष्ठा clk_parent_data []) अणु
			अणु .fw_name = "xtal", पूर्ण,
			अणु .hw = &g12a_fclk_भाग2.hw पूर्ण,
			अणु .hw = &g12a_fclk_भाग3.hw पूर्ण,
			अणु .hw = &sm1_gp1_pll.hw पूर्ण,
		पूर्ण,
		.num_parents = 4,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "premux1" */
अटल काष्ठा clk_regmap sm1_dsu_clk_premux1 = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL5,
		.mask = 0x3,
		.shअगरt = 16,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "dsu_clk_dyn1_sel",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_data = (स्थिर काष्ठा clk_parent_data []) अणु
			अणु .fw_name = "xtal", पूर्ण,
			अणु .hw = &g12a_fclk_भाग2.hw पूर्ण,
			अणु .hw = &g12a_fclk_भाग3.hw पूर्ण,
			अणु .hw = &sm1_gp1_pll.hw पूर्ण,
		पूर्ण,
		.num_parents = 4,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "Mux0_divn_tcnt" */
अटल काष्ठा clk_regmap sm1_dsu_clk_mux0_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL5,
		.shअगरt = 4,
		.width = 6,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "dsu_clk_dyn0_div",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&sm1_dsu_clk_premux0.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "postmux0" */
अटल काष्ठा clk_regmap sm1_dsu_clk_posपंचांगux0 = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL5,
		.mask = 0x1,
		.shअगरt = 2,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "dsu_clk_dyn0",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&sm1_dsu_clk_premux0.hw,
			&sm1_dsu_clk_mux0_भाग.hw,
		पूर्ण,
		.num_parents = 2,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "Mux1_divn_tcnt" */
अटल काष्ठा clk_regmap sm1_dsu_clk_mux1_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL5,
		.shअगरt = 20,
		.width = 6,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "dsu_clk_dyn1_div",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&sm1_dsu_clk_premux1.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "postmux1" */
अटल काष्ठा clk_regmap sm1_dsu_clk_posपंचांगux1 = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL5,
		.mask = 0x1,
		.shअगरt = 18,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "dsu_clk_dyn1",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&sm1_dsu_clk_premux1.hw,
			&sm1_dsu_clk_mux1_भाग.hw,
		पूर्ण,
		.num_parents = 2,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "Final_dyn_mux_sel" */
अटल काष्ठा clk_regmap sm1_dsu_clk_dyn = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL5,
		.mask = 0x1,
		.shअगरt = 10,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "dsu_clk_dyn",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&sm1_dsu_clk_posपंचांगux0.hw,
			&sm1_dsu_clk_posपंचांगux1.hw,
		पूर्ण,
		.num_parents = 2,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "Final_mux_sel" */
अटल काष्ठा clk_regmap sm1_dsu_final_clk = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL5,
		.mask = 0x1,
		.shअगरt = 11,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "dsu_clk_final",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&sm1_dsu_clk_dyn.hw,
			&g12a_sys_pll.hw,
		पूर्ण,
		.num_parents = 2,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "Cpu_clk_sync_mux_sel" bit 0 */
अटल काष्ठा clk_regmap sm1_cpu1_clk = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL6,
		.mask = 0x1,
		.shअगरt = 24,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu1_clk",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_cpu_clk.hw,
			/* This CPU also have a dedicated घड़ी tree */
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "Cpu_clk_sync_mux_sel" bit 1 */
अटल काष्ठा clk_regmap sm1_cpu2_clk = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL6,
		.mask = 0x1,
		.shअगरt = 25,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu2_clk",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_cpu_clk.hw,
			/* This CPU also have a dedicated घड़ी tree */
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "Cpu_clk_sync_mux_sel" bit 2 */
अटल काष्ठा clk_regmap sm1_cpu3_clk = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL6,
		.mask = 0x1,
		.shअगरt = 26,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu3_clk",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_cpu_clk.hw,
			/* This CPU also have a dedicated घड़ी tree */
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

/* Datasheet names this field as "Cpu_clk_sync_mux_sel" bit 4 */
अटल काष्ठा clk_regmap sm1_dsu_clk = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL6,
		.mask = 0x1,
		.shअगरt = 27,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "dsu_clk",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_cpu_clk.hw,
			&sm1_dsu_final_clk.hw,
		पूर्ण,
		.num_parents = 2,
	पूर्ण,
पूर्ण;

अटल पूर्णांक g12a_cpu_clk_mux_notअगरier_cb(काष्ठा notअगरier_block *nb,
					अचिन्हित दीर्घ event, व्योम *data)
अणु
	अगर (event == POST_RATE_CHANGE || event == PRE_RATE_CHANGE) अणु
		/* Wait क्रम घड़ी propagation beक्रमe/after changing the mux */
		udelay(100);
		वापस NOTIFY_OK;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block g12a_cpu_clk_mux_nb = अणु
	.notअगरier_call = g12a_cpu_clk_mux_notअगरier_cb,
पूर्ण;

काष्ठा g12a_cpu_clk_posपंचांगux_nb_data अणु
	काष्ठा notअगरier_block nb;
	काष्ठा clk_hw *xtal;
	काष्ठा clk_hw *cpu_clk_dyn;
	काष्ठा clk_hw *cpu_clk_posपंचांगux0;
	काष्ठा clk_hw *cpu_clk_posपंचांगux1;
	काष्ठा clk_hw *cpu_clk_premux1;
पूर्ण;

अटल पूर्णांक g12a_cpu_clk_posपंचांगux_notअगरier_cb(काष्ठा notअगरier_block *nb,
					    अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा g12a_cpu_clk_posपंचांगux_nb_data *nb_data =
		container_of(nb, काष्ठा g12a_cpu_clk_posपंचांगux_nb_data, nb);

	चयन (event) अणु
	हाल PRE_RATE_CHANGE:
		/*
		 * This notअगरier means cpu_clk_posपंचांगux0 घड़ी will be changed
		 * to feed cpu_clk, this is the current path :
		 * cpu_clk
		 *    \- cpu_clk_dyn
		 *          \- cpu_clk_posपंचांगux0
		 *                \- cpu_clk_muxX_भाग
		 *                      \- cpu_clk_premux0
		 *				\- fclk_भाग3 or fclk_भाग2
		 *		OR
		 *                \- cpu_clk_premux0
		 *			\- fclk_भाग3 or fclk_भाग2
		 */

		/* Setup cpu_clk_premux1 to xtal */
		clk_hw_set_parent(nb_data->cpu_clk_premux1,
				  nb_data->xtal);

		/* Setup cpu_clk_posपंचांगux1 to bypass भागider */
		clk_hw_set_parent(nb_data->cpu_clk_posपंचांगux1,
				  nb_data->cpu_clk_premux1);

		/* Switch to parking clk on cpu_clk_posपंचांगux1 */
		clk_hw_set_parent(nb_data->cpu_clk_dyn,
				  nb_data->cpu_clk_posपंचांगux1);

		/*
		 * Now, cpu_clk is 24MHz in the current path :
		 * cpu_clk
		 *    \- cpu_clk_dyn
		 *          \- cpu_clk_posपंचांगux1
		 *                \- cpu_clk_premux1
		 *                      \- xtal
		 */

		udelay(100);

		वापस NOTIFY_OK;

	हाल POST_RATE_CHANGE:
		/*
		 * The cpu_clk_posपंचांगux0 has ben updated, now चयन back
		 * cpu_clk_dyn to cpu_clk_posपंचांगux0 and take the changes
		 * in account.
		 */

		/* Configure cpu_clk_dyn back to cpu_clk_posपंचांगux0 */
		clk_hw_set_parent(nb_data->cpu_clk_dyn,
				  nb_data->cpu_clk_posपंचांगux0);

		/*
		 * new path :
		 * cpu_clk
		 *    \- cpu_clk_dyn
		 *          \- cpu_clk_posपंचांगux0
		 *                \- cpu_clk_muxX_भाग
		 *                      \- cpu_clk_premux0
		 *				\- fclk_भाग3 or fclk_भाग2
		 *		OR
		 *                \- cpu_clk_premux0
		 *			\- fclk_भाग3 or fclk_भाग2
		 */

		udelay(100);

		वापस NOTIFY_OK;

	शेष:
		वापस NOTIFY_DONE;
	पूर्ण
पूर्ण

अटल काष्ठा g12a_cpu_clk_posपंचांगux_nb_data g12a_cpu_clk_posपंचांगux0_nb_data = अणु
	.cpu_clk_dyn = &g12a_cpu_clk_dyn.hw,
	.cpu_clk_posपंचांगux0 = &g12a_cpu_clk_posपंचांगux0.hw,
	.cpu_clk_posपंचांगux1 = &g12a_cpu_clk_posपंचांगux1.hw,
	.cpu_clk_premux1 = &g12a_cpu_clk_premux1.hw,
	.nb.notअगरier_call = g12a_cpu_clk_posपंचांगux_notअगरier_cb,
पूर्ण;

अटल काष्ठा g12a_cpu_clk_posपंचांगux_nb_data g12b_cpub_clk_posपंचांगux0_nb_data = अणु
	.cpu_clk_dyn = &g12b_cpub_clk_dyn.hw,
	.cpu_clk_posपंचांगux0 = &g12b_cpub_clk_posपंचांगux0.hw,
	.cpu_clk_posपंचांगux1 = &g12b_cpub_clk_posपंचांगux1.hw,
	.cpu_clk_premux1 = &g12b_cpub_clk_premux1.hw,
	.nb.notअगरier_call = g12a_cpu_clk_posपंचांगux_notअगरier_cb,
पूर्ण;

काष्ठा g12a_sys_pll_nb_data अणु
	काष्ठा notअगरier_block nb;
	काष्ठा clk_hw *sys_pll;
	काष्ठा clk_hw *cpu_clk;
	काष्ठा clk_hw *cpu_clk_dyn;
पूर्ण;

अटल पूर्णांक g12a_sys_pll_notअगरier_cb(काष्ठा notअगरier_block *nb,
				    अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा g12a_sys_pll_nb_data *nb_data =
		container_of(nb, काष्ठा g12a_sys_pll_nb_data, nb);

	चयन (event) अणु
	हाल PRE_RATE_CHANGE:
		/*
		 * This notअगरier means sys_pll घड़ी will be changed
		 * to feed cpu_clk, this the current path :
		 * cpu_clk
		 *    \- sys_pll
		 *          \- sys_pll_dco
		 */

		/* Configure cpu_clk to use cpu_clk_dyn */
		clk_hw_set_parent(nb_data->cpu_clk,
				  nb_data->cpu_clk_dyn);

		/*
		 * Now, cpu_clk uses the dyn path
		 * cpu_clk
		 *    \- cpu_clk_dyn
		 *          \- cpu_clk_dynX
		 *                \- cpu_clk_dynX_sel
		 *		     \- cpu_clk_dynX_भाग
		 *                      \- xtal/fclk_भाग2/fclk_भाग3
		 *                   \- xtal/fclk_भाग2/fclk_भाग3
		 */

		udelay(100);

		वापस NOTIFY_OK;

	हाल POST_RATE_CHANGE:
		/*
		 * The sys_pll has ben updated, now चयन back cpu_clk to
		 * sys_pll
		 */

		/* Configure cpu_clk to use sys_pll */
		clk_hw_set_parent(nb_data->cpu_clk,
				  nb_data->sys_pll);

		udelay(100);

		/* new path :
		 * cpu_clk
		 *    \- sys_pll
		 *          \- sys_pll_dco
		 */

		वापस NOTIFY_OK;

	शेष:
		वापस NOTIFY_DONE;
	पूर्ण
पूर्ण

अटल काष्ठा g12a_sys_pll_nb_data g12a_sys_pll_nb_data = अणु
	.sys_pll = &g12a_sys_pll.hw,
	.cpu_clk = &g12a_cpu_clk.hw,
	.cpu_clk_dyn = &g12a_cpu_clk_dyn.hw,
	.nb.notअगरier_call = g12a_sys_pll_notअगरier_cb,
पूर्ण;

/* G12B first CPU cluster uses sys1_pll */
अटल काष्ठा g12a_sys_pll_nb_data g12b_cpu_clk_sys1_pll_nb_data = अणु
	.sys_pll = &g12b_sys1_pll.hw,
	.cpu_clk = &g12b_cpu_clk.hw,
	.cpu_clk_dyn = &g12a_cpu_clk_dyn.hw,
	.nb.notअगरier_call = g12a_sys_pll_notअगरier_cb,
पूर्ण;

/* G12B second CPU cluster uses sys_pll */
अटल काष्ठा g12a_sys_pll_nb_data g12b_cpub_clk_sys_pll_nb_data = अणु
	.sys_pll = &g12a_sys_pll.hw,
	.cpu_clk = &g12b_cpub_clk.hw,
	.cpu_clk_dyn = &g12b_cpub_clk_dyn.hw,
	.nb.notअगरier_call = g12a_sys_pll_notअगरier_cb,
पूर्ण;

अटल काष्ठा clk_regmap g12a_cpu_clk_भाग16_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL1,
		.bit_idx = 1,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "cpu_clk_div16_en",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_cpu_clk.hw
		पूर्ण,
		.num_parents = 1,
		/*
		 * This घड़ी is used to debug the cpu_clk range
		 * Linux should not change it at runसमय
		 */
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12b_cpub_clk_भाग16_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SYS_CPUB_CLK_CNTL1,
		.bit_idx = 1,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "cpub_clk_div16_en",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk.hw
		पूर्ण,
		.num_parents = 1,
		/*
		 * This घड़ी is used to debug the cpu_clk range
		 * Linux should not change it at runसमय
		 */
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12a_cpu_clk_भाग16 = अणु
	.mult = 1,
	.भाग = 16,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk_div16",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_cpu_clk_भाग16_en.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12b_cpub_clk_भाग16 = अणु
	.mult = 1,
	.भाग = 16,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpub_clk_div16",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk_भाग16_en.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_cpu_clk_apb_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL1,
		.shअगरt = 3,
		.width = 3,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk_apb_div",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_cpu_clk.hw पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_cpu_clk_apb = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL1,
		.bit_idx = 1,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "cpu_clk_apb",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_cpu_clk_apb_भाग.hw
		पूर्ण,
		.num_parents = 1,
		/*
		 * This घड़ी is set by the ROM monitor code,
		 * Linux should not change it at runसमय
		 */
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_cpu_clk_atb_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL1,
		.shअगरt = 6,
		.width = 3,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk_atb_div",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_cpu_clk.hw पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_cpu_clk_atb = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL1,
		.bit_idx = 17,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "cpu_clk_atb",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_cpu_clk_atb_भाग.hw
		पूर्ण,
		.num_parents = 1,
		/*
		 * This घड़ी is set by the ROM monitor code,
		 * Linux should not change it at runसमय
		 */
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_cpu_clk_axi_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL1,
		.shअगरt = 9,
		.width = 3,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk_axi_div",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_cpu_clk.hw पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_cpu_clk_axi = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL1,
		.bit_idx = 18,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "cpu_clk_axi",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_cpu_clk_axi_भाग.hw
		पूर्ण,
		.num_parents = 1,
		/*
		 * This घड़ी is set by the ROM monitor code,
		 * Linux should not change it at runसमय
		 */
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_cpu_clk_trace_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL1,
		.shअगरt = 20,
		.width = 3,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpu_clk_trace_div",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			/*
			 * Note:
			 * G12A and G12B have dअगरferent cpu_clks (with
			 * dअगरferent काष्ठा clk_hw). We fallback to the global
			 * naming string mechanism so cpu_clk_trace_भाग picks
			 * up the appropriate one.
			 */
			.name = "cpu_clk",
			.index = -1,
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_cpu_clk_trace = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SYS_CPU_CLK_CNTL1,
		.bit_idx = 23,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "cpu_clk_trace",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_cpu_clk_trace_भाग.hw
		पूर्ण,
		.num_parents = 1,
		/*
		 * This घड़ी is set by the ROM monitor code,
		 * Linux should not change it at runसमय
		 */
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12b_cpub_clk_भाग2 = अणु
	.mult = 1,
	.भाग = 2,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpub_clk_div2",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12b_cpub_clk_भाग3 = अणु
	.mult = 1,
	.भाग = 3,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpub_clk_div3",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12b_cpub_clk_भाग4 = अणु
	.mult = 1,
	.भाग = 4,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpub_clk_div4",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12b_cpub_clk_भाग5 = अणु
	.mult = 1,
	.भाग = 5,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpub_clk_div5",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12b_cpub_clk_भाग6 = अणु
	.mult = 1,
	.भाग = 6,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpub_clk_div6",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12b_cpub_clk_भाग7 = अणु
	.mult = 1,
	.भाग = 7,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpub_clk_div7",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12b_cpub_clk_भाग8 = अणु
	.mult = 1,
	.भाग = 8,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpub_clk_div8",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल u32 mux_table_cpub[] = अणु 1, 2, 3, 4, 5, 6, 7 पूर्ण;
अटल काष्ठा clk_regmap g12b_cpub_clk_apb_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPUB_CLK_CNTL1,
		.mask = 7,
		.shअगरt = 3,
		.table = mux_table_cpub,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpub_clk_apb_sel",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk_भाग2.hw,
			&g12b_cpub_clk_भाग3.hw,
			&g12b_cpub_clk_भाग4.hw,
			&g12b_cpub_clk_भाग5.hw,
			&g12b_cpub_clk_भाग6.hw,
			&g12b_cpub_clk_भाग7.hw,
			&g12b_cpub_clk_भाग8.hw
		पूर्ण,
		.num_parents = 7,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12b_cpub_clk_apb = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SYS_CPUB_CLK_CNTL1,
		.bit_idx = 16,
		.flags = CLK_GATE_SET_TO_DISABLE,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "cpub_clk_apb",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk_apb_sel.hw
		पूर्ण,
		.num_parents = 1,
		/*
		 * This घड़ी is set by the ROM monitor code,
		 * Linux should not change it at runसमय
		 */
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12b_cpub_clk_atb_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPUB_CLK_CNTL1,
		.mask = 7,
		.shअगरt = 6,
		.table = mux_table_cpub,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpub_clk_atb_sel",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk_भाग2.hw,
			&g12b_cpub_clk_भाग3.hw,
			&g12b_cpub_clk_भाग4.hw,
			&g12b_cpub_clk_भाग5.hw,
			&g12b_cpub_clk_भाग6.hw,
			&g12b_cpub_clk_भाग7.hw,
			&g12b_cpub_clk_भाग8.hw
		पूर्ण,
		.num_parents = 7,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12b_cpub_clk_atb = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SYS_CPUB_CLK_CNTL1,
		.bit_idx = 17,
		.flags = CLK_GATE_SET_TO_DISABLE,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "cpub_clk_atb",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk_atb_sel.hw
		पूर्ण,
		.num_parents = 1,
		/*
		 * This घड़ी is set by the ROM monitor code,
		 * Linux should not change it at runसमय
		 */
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12b_cpub_clk_axi_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPUB_CLK_CNTL1,
		.mask = 7,
		.shअगरt = 9,
		.table = mux_table_cpub,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpub_clk_axi_sel",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk_भाग2.hw,
			&g12b_cpub_clk_भाग3.hw,
			&g12b_cpub_clk_भाग4.hw,
			&g12b_cpub_clk_भाग5.hw,
			&g12b_cpub_clk_भाग6.hw,
			&g12b_cpub_clk_भाग7.hw,
			&g12b_cpub_clk_भाग8.hw
		पूर्ण,
		.num_parents = 7,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12b_cpub_clk_axi = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SYS_CPUB_CLK_CNTL1,
		.bit_idx = 18,
		.flags = CLK_GATE_SET_TO_DISABLE,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "cpub_clk_axi",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk_axi_sel.hw
		पूर्ण,
		.num_parents = 1,
		/*
		 * This घड़ी is set by the ROM monitor code,
		 * Linux should not change it at runसमय
		 */
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12b_cpub_clk_trace_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SYS_CPUB_CLK_CNTL1,
		.mask = 7,
		.shअगरt = 20,
		.table = mux_table_cpub,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpub_clk_trace_sel",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk_भाग2.hw,
			&g12b_cpub_clk_भाग3.hw,
			&g12b_cpub_clk_भाग4.hw,
			&g12b_cpub_clk_भाग5.hw,
			&g12b_cpub_clk_भाग6.hw,
			&g12b_cpub_clk_भाग7.hw,
			&g12b_cpub_clk_भाग8.hw
		पूर्ण,
		.num_parents = 7,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12b_cpub_clk_trace = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SYS_CPUB_CLK_CNTL1,
		.bit_idx = 23,
		.flags = CLK_GATE_SET_TO_DISABLE,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "cpub_clk_trace",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12b_cpub_clk_trace_sel.hw
		पूर्ण,
		.num_parents = 1,
		/*
		 * This घड़ी is set by the ROM monitor code,
		 * Linux should not change it at runसमय
		 */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pll_mult_range g12a_gp0_pll_mult_range = अणु
	.min = 55,
	.max = 255,
पूर्ण;

/*
 * Internal gp0 pll emulation configuration parameters
 */
अटल स्थिर काष्ठा reg_sequence g12a_gp0_init_regs[] = अणु
	अणु .reg = HHI_GP0_PLL_CNTL1,	.def = 0x00000000 पूर्ण,
	अणु .reg = HHI_GP0_PLL_CNTL2,	.def = 0x00000000 पूर्ण,
	अणु .reg = HHI_GP0_PLL_CNTL3,	.def = 0x48681c00 पूर्ण,
	अणु .reg = HHI_GP0_PLL_CNTL4,	.def = 0x33771290 पूर्ण,
	अणु .reg = HHI_GP0_PLL_CNTL5,	.def = 0x39272000 पूर्ण,
	अणु .reg = HHI_GP0_PLL_CNTL6,	.def = 0x56540000 पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_gp0_pll_dco = अणु
	.data = &(काष्ठा meson_clk_pll_data)अणु
		.en = अणु
			.reg_off = HHI_GP0_PLL_CNTL0,
			.shअगरt   = 28,
			.width   = 1,
		पूर्ण,
		.m = अणु
			.reg_off = HHI_GP0_PLL_CNTL0,
			.shअगरt   = 0,
			.width   = 8,
		पूर्ण,
		.n = अणु
			.reg_off = HHI_GP0_PLL_CNTL0,
			.shअगरt   = 10,
			.width   = 5,
		पूर्ण,
		.frac = अणु
			.reg_off = HHI_GP0_PLL_CNTL1,
			.shअगरt   = 0,
			.width   = 17,
		पूर्ण,
		.l = अणु
			.reg_off = HHI_GP0_PLL_CNTL0,
			.shअगरt   = 31,
			.width   = 1,
		पूर्ण,
		.rst = अणु
			.reg_off = HHI_GP0_PLL_CNTL0,
			.shअगरt   = 29,
			.width   = 1,
		पूर्ण,
		.range = &g12a_gp0_pll_mult_range,
		.init_regs = g12a_gp0_init_regs,
		.init_count = ARRAY_SIZE(g12a_gp0_init_regs),
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

अटल काष्ठा clk_regmap g12a_gp0_pll = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_GP0_PLL_CNTL0,
		.shअगरt = 16,
		.width = 3,
		.flags = (CLK_DIVIDER_POWER_OF_TWO |
			  CLK_DIVIDER_ROUND_CLOSEST),
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gp0_pll",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_gp0_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap sm1_gp1_pll_dco = अणु
	.data = &(काष्ठा meson_clk_pll_data)अणु
		.en = अणु
			.reg_off = HHI_GP1_PLL_CNTL0,
			.shअगरt   = 28,
			.width   = 1,
		पूर्ण,
		.m = अणु
			.reg_off = HHI_GP1_PLL_CNTL0,
			.shअगरt   = 0,
			.width   = 8,
		पूर्ण,
		.n = अणु
			.reg_off = HHI_GP1_PLL_CNTL0,
			.shअगरt   = 10,
			.width   = 5,
		पूर्ण,
		.frac = अणु
			.reg_off = HHI_GP1_PLL_CNTL1,
			.shअगरt   = 0,
			.width   = 17,
		पूर्ण,
		.l = अणु
			.reg_off = HHI_GP1_PLL_CNTL0,
			.shअगरt   = 31,
			.width   = 1,
		पूर्ण,
		.rst = अणु
			.reg_off = HHI_GP1_PLL_CNTL0,
			.shअगरt   = 29,
			.width   = 1,
		पूर्ण,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gp1_pll_dco",
		.ops = &meson_clk_pll_ro_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			.fw_name = "xtal",
		पूर्ण,
		.num_parents = 1,
		/* This घड़ी feeds the DSU, aव्योम disabling it */
		.flags = CLK_IS_CRITICAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap sm1_gp1_pll = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_GP1_PLL_CNTL0,
		.shअगरt = 16,
		.width = 3,
		.flags = (CLK_DIVIDER_POWER_OF_TWO |
			  CLK_DIVIDER_ROUND_CLOSEST),
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gp1_pll",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&sm1_gp1_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

/*
 * Internal hअगरi pll emulation configuration parameters
 */
अटल स्थिर काष्ठा reg_sequence g12a_hअगरi_init_regs[] = अणु
	अणु .reg = HHI_HIFI_PLL_CNTL1,	.def = 0x00000000 पूर्ण,
	अणु .reg = HHI_HIFI_PLL_CNTL2,	.def = 0x00000000 पूर्ण,
	अणु .reg = HHI_HIFI_PLL_CNTL3,	.def = 0x6a285c00 पूर्ण,
	अणु .reg = HHI_HIFI_PLL_CNTL4,	.def = 0x65771290 पूर्ण,
	अणु .reg = HHI_HIFI_PLL_CNTL5,	.def = 0x39272000 पूर्ण,
	अणु .reg = HHI_HIFI_PLL_CNTL6,	.def = 0x56540000 पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_hअगरi_pll_dco = अणु
	.data = &(काष्ठा meson_clk_pll_data)अणु
		.en = अणु
			.reg_off = HHI_HIFI_PLL_CNTL0,
			.shअगरt   = 28,
			.width   = 1,
		पूर्ण,
		.m = अणु
			.reg_off = HHI_HIFI_PLL_CNTL0,
			.shअगरt   = 0,
			.width   = 8,
		पूर्ण,
		.n = अणु
			.reg_off = HHI_HIFI_PLL_CNTL0,
			.shअगरt   = 10,
			.width   = 5,
		पूर्ण,
		.frac = अणु
			.reg_off = HHI_HIFI_PLL_CNTL1,
			.shअगरt   = 0,
			.width   = 17,
		पूर्ण,
		.l = अणु
			.reg_off = HHI_HIFI_PLL_CNTL0,
			.shअगरt   = 31,
			.width   = 1,
		पूर्ण,
		.rst = अणु
			.reg_off = HHI_HIFI_PLL_CNTL0,
			.shअगरt   = 29,
			.width   = 1,
		पूर्ण,
		.range = &g12a_gp0_pll_mult_range,
		.init_regs = g12a_hअगरi_init_regs,
		.init_count = ARRAY_SIZE(g12a_hअगरi_init_regs),
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

अटल काष्ठा clk_regmap g12a_hअगरi_pll = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_HIFI_PLL_CNTL0,
		.shअगरt = 16,
		.width = 2,
		.flags = (CLK_DIVIDER_POWER_OF_TWO |
			  CLK_DIVIDER_ROUND_CLOSEST),
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "hifi_pll",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_hअगरi_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/*
 * The Meson G12A PCIE PLL is fined tuned to deliver a very precise
 * 100MHz reference घड़ी क्रम the PCIe Analog PHY, and thus requires
 * a strict रेजिस्टर sequence to enable the PLL.
 */
अटल स्थिर काष्ठा reg_sequence g12a_pcie_pll_init_regs[] = अणु
	अणु .reg = HHI_PCIE_PLL_CNTL0,	.def = 0x20090496 पूर्ण,
	अणु .reg = HHI_PCIE_PLL_CNTL0,	.def = 0x30090496 पूर्ण,
	अणु .reg = HHI_PCIE_PLL_CNTL1,	.def = 0x00000000 पूर्ण,
	अणु .reg = HHI_PCIE_PLL_CNTL2,	.def = 0x00001100 पूर्ण,
	अणु .reg = HHI_PCIE_PLL_CNTL3,	.def = 0x10058e00 पूर्ण,
	अणु .reg = HHI_PCIE_PLL_CNTL4,	.def = 0x000100c0 पूर्ण,
	अणु .reg = HHI_PCIE_PLL_CNTL5,	.def = 0x68000048 पूर्ण,
	अणु .reg = HHI_PCIE_PLL_CNTL5,	.def = 0x68000068, .delay_us = 20 पूर्ण,
	अणु .reg = HHI_PCIE_PLL_CNTL4,	.def = 0x008100c0, .delay_us = 10 पूर्ण,
	अणु .reg = HHI_PCIE_PLL_CNTL0,	.def = 0x34090496 पूर्ण,
	अणु .reg = HHI_PCIE_PLL_CNTL0,	.def = 0x14090496, .delay_us = 10 पूर्ण,
	अणु .reg = HHI_PCIE_PLL_CNTL2,	.def = 0x00001000 पूर्ण,
पूर्ण;

/* Keep a single entry table क्रम recalc/round_rate() ops */
अटल स्थिर काष्ठा pll_params_table g12a_pcie_pll_table[] = अणु
	PLL_PARAMS(150, 1),
	अणु0, 0पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_pcie_pll_dco = अणु
	.data = &(काष्ठा meson_clk_pll_data)अणु
		.en = अणु
			.reg_off = HHI_PCIE_PLL_CNTL0,
			.shअगरt   = 28,
			.width   = 1,
		पूर्ण,
		.m = अणु
			.reg_off = HHI_PCIE_PLL_CNTL0,
			.shअगरt   = 0,
			.width   = 8,
		पूर्ण,
		.n = अणु
			.reg_off = HHI_PCIE_PLL_CNTL0,
			.shअगरt   = 10,
			.width   = 5,
		पूर्ण,
		.frac = अणु
			.reg_off = HHI_PCIE_PLL_CNTL1,
			.shअगरt   = 0,
			.width   = 12,
		पूर्ण,
		.l = अणु
			.reg_off = HHI_PCIE_PLL_CNTL0,
			.shअगरt   = 31,
			.width   = 1,
		पूर्ण,
		.rst = अणु
			.reg_off = HHI_PCIE_PLL_CNTL0,
			.shअगरt   = 29,
			.width   = 1,
		पूर्ण,
		.table = g12a_pcie_pll_table,
		.init_regs = g12a_pcie_pll_init_regs,
		.init_count = ARRAY_SIZE(g12a_pcie_pll_init_regs),
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pcie_pll_dco",
		.ops = &meson_clk_pcie_pll_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			.fw_name = "xtal",
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12a_pcie_pll_dco_भाग2 = अणु
	.mult = 1,
	.भाग = 2,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pcie_pll_dco_div2",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_pcie_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_pcie_pll_od = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_PCIE_PLL_CNTL0,
		.shअगरt = 16,
		.width = 5,
		.flags = CLK_DIVIDER_ROUND_CLOSEST |
			 CLK_DIVIDER_ONE_BASED |
			 CLK_DIVIDER_ALLOW_ZERO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pcie_pll_od",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_pcie_pll_dco_भाग2.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12a_pcie_pll = अणु
	.mult = 1,
	.भाग = 2,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pcie_pll_pll",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_pcie_pll_od.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_hdmi_pll_dco = अणु
	.data = &(काष्ठा meson_clk_pll_data)अणु
		.en = अणु
			.reg_off = HHI_HDMI_PLL_CNTL0,
			.shअगरt   = 28,
			.width   = 1,
		पूर्ण,
		.m = अणु
			.reg_off = HHI_HDMI_PLL_CNTL0,
			.shअगरt   = 0,
			.width   = 8,
		पूर्ण,
		.n = अणु
			.reg_off = HHI_HDMI_PLL_CNTL0,
			.shअगरt   = 10,
			.width   = 5,
		पूर्ण,
		.frac = अणु
			.reg_off = HHI_HDMI_PLL_CNTL1,
			.shअगरt   = 0,
			.width   = 16,
		पूर्ण,
		.l = अणु
			.reg_off = HHI_HDMI_PLL_CNTL0,
			.shअगरt   = 30,
			.width   = 1,
		पूर्ण,
		.rst = अणु
			.reg_off = HHI_HDMI_PLL_CNTL0,
			.shअगरt   = 29,
			.width   = 1,
		पूर्ण,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "hdmi_pll_dco",
		.ops = &meson_clk_pll_ro_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			.fw_name = "xtal",
		पूर्ण,
		.num_parents = 1,
		/*
		 * Display directly handle hdmi pll रेजिस्टरs ATM, we need
		 * NOCACHE to keep our view of the घड़ी as accurate as possible
		 */
		.flags = CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_hdmi_pll_od = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_HDMI_PLL_CNTL0,
		.shअगरt = 16,
		.width = 2,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "hdmi_pll_od",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_hdmi_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_GET_RATE_NOCACHE | CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_hdmi_pll_od2 = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_HDMI_PLL_CNTL0,
		.shअगरt = 18,
		.width = 2,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "hdmi_pll_od2",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_hdmi_pll_od.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_GET_RATE_NOCACHE | CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_hdmi_pll = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_HDMI_PLL_CNTL0,
		.shअगरt = 20,
		.width = 2,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "hdmi_pll",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_hdmi_pll_od2.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_GET_RATE_NOCACHE | CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12a_fclk_भाग4_भाग = अणु
	.mult = 1,
	.भाग = 4,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div4_div",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_fixed_pll.hw पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_fclk_भाग4 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_FIX_PLL_CNTL1,
		.bit_idx = 21,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div4",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_fclk_भाग4_भाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12a_fclk_भाग5_भाग = अणु
	.mult = 1,
	.भाग = 5,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div5_div",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_fixed_pll.hw पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_fclk_भाग5 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_FIX_PLL_CNTL1,
		.bit_idx = 22,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div5",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_fclk_भाग5_भाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12a_fclk_भाग7_भाग = अणु
	.mult = 1,
	.भाग = 7,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div7_div",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_fixed_pll.hw पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_fclk_भाग7 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_FIX_PLL_CNTL1,
		.bit_idx = 23,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div7",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_fclk_भाग7_भाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12a_fclk_भाग2p5_भाग = अणु
	.mult = 1,
	.भाग = 5,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div2p5_div",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_fixed_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_fclk_भाग2p5 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_FIX_PLL_CNTL1,
		.bit_idx = 25,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fclk_div2p5",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_fclk_भाग2p5_भाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12a_mpll_50m_भाग = अणु
	.mult = 1,
	.भाग = 80,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll_50m_div",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_fixed_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_mpll_50m = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_FIX_PLL_CNTL3,
		.mask = 0x1,
		.shअगरt = 5,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll_50m",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_data = (स्थिर काष्ठा clk_parent_data []) अणु
			अणु .fw_name = "xtal", पूर्ण,
			अणु .hw = &g12a_mpll_50m_भाग.hw पूर्ण,
		पूर्ण,
		.num_parents = 2,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12a_mpll_preभाग = अणु
	.mult = 1,
	.भाग = 2,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll_prediv",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_fixed_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence g12a_mpll0_init_regs[] = अणु
	अणु .reg = HHI_MPLL_CNTL2,	.def = 0x40000033 पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_mpll0_भाग = अणु
	.data = &(काष्ठा meson_clk_mpll_data)अणु
		.sdm = अणु
			.reg_off = HHI_MPLL_CNTL1,
			.shअगरt   = 0,
			.width   = 14,
		पूर्ण,
		.sdm_en = अणु
			.reg_off = HHI_MPLL_CNTL1,
			.shअगरt   = 30,
			.width	 = 1,
		पूर्ण,
		.n2 = अणु
			.reg_off = HHI_MPLL_CNTL1,
			.shअगरt   = 20,
			.width   = 9,
		पूर्ण,
		.ssen = अणु
			.reg_off = HHI_MPLL_CNTL1,
			.shअगरt   = 29,
			.width	 = 1,
		पूर्ण,
		.lock = &meson_clk_lock,
		.init_regs = g12a_mpll0_init_regs,
		.init_count = ARRAY_SIZE(g12a_mpll0_init_regs),
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll0_div",
		.ops = &meson_clk_mpll_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_mpll_preभाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_mpll0 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL_CNTL1,
		.bit_idx = 31,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll0",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_mpll0_भाग.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence g12a_mpll1_init_regs[] = अणु
	अणु .reg = HHI_MPLL_CNTL4,	.def = 0x40000033 पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_mpll1_भाग = अणु
	.data = &(काष्ठा meson_clk_mpll_data)अणु
		.sdm = अणु
			.reg_off = HHI_MPLL_CNTL3,
			.shअगरt   = 0,
			.width   = 14,
		पूर्ण,
		.sdm_en = अणु
			.reg_off = HHI_MPLL_CNTL3,
			.shअगरt   = 30,
			.width	 = 1,
		पूर्ण,
		.n2 = अणु
			.reg_off = HHI_MPLL_CNTL3,
			.shअगरt   = 20,
			.width   = 9,
		पूर्ण,
		.ssen = अणु
			.reg_off = HHI_MPLL_CNTL3,
			.shअगरt   = 29,
			.width	 = 1,
		पूर्ण,
		.lock = &meson_clk_lock,
		.init_regs = g12a_mpll1_init_regs,
		.init_count = ARRAY_SIZE(g12a_mpll1_init_regs),
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll1_div",
		.ops = &meson_clk_mpll_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_mpll_preभाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_mpll1 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL_CNTL3,
		.bit_idx = 31,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll1",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_mpll1_भाग.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence g12a_mpll2_init_regs[] = अणु
	अणु .reg = HHI_MPLL_CNTL6,	.def = 0x40000033 पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_mpll2_भाग = अणु
	.data = &(काष्ठा meson_clk_mpll_data)अणु
		.sdm = अणु
			.reg_off = HHI_MPLL_CNTL5,
			.shअगरt   = 0,
			.width   = 14,
		पूर्ण,
		.sdm_en = अणु
			.reg_off = HHI_MPLL_CNTL5,
			.shअगरt   = 30,
			.width	 = 1,
		पूर्ण,
		.n2 = अणु
			.reg_off = HHI_MPLL_CNTL5,
			.shअगरt   = 20,
			.width   = 9,
		पूर्ण,
		.ssen = अणु
			.reg_off = HHI_MPLL_CNTL5,
			.shअगरt   = 29,
			.width	 = 1,
		पूर्ण,
		.lock = &meson_clk_lock,
		.init_regs = g12a_mpll2_init_regs,
		.init_count = ARRAY_SIZE(g12a_mpll2_init_regs),
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll2_div",
		.ops = &meson_clk_mpll_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_mpll_preभाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_mpll2 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL_CNTL5,
		.bit_idx = 31,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll2",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_mpll2_भाग.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence g12a_mpll3_init_regs[] = अणु
	अणु .reg = HHI_MPLL_CNTL8,	.def = 0x40000033 पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_mpll3_भाग = अणु
	.data = &(काष्ठा meson_clk_mpll_data)अणु
		.sdm = अणु
			.reg_off = HHI_MPLL_CNTL7,
			.shअगरt   = 0,
			.width   = 14,
		पूर्ण,
		.sdm_en = अणु
			.reg_off = HHI_MPLL_CNTL7,
			.shअगरt   = 30,
			.width	 = 1,
		पूर्ण,
		.n2 = अणु
			.reg_off = HHI_MPLL_CNTL7,
			.shअगरt   = 20,
			.width   = 9,
		पूर्ण,
		.ssen = अणु
			.reg_off = HHI_MPLL_CNTL7,
			.shअगरt   = 29,
			.width	 = 1,
		पूर्ण,
		.lock = &meson_clk_lock,
		.init_regs = g12a_mpll3_init_regs,
		.init_count = ARRAY_SIZE(g12a_mpll3_init_regs),
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll3_div",
		.ops = &meson_clk_mpll_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_mpll_preभाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_mpll3 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPLL_CNTL7,
		.bit_idx = 31,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpll3",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_mpll3_भाग.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल u32 mux_table_clk81[]	= अणु 0, 2, 3, 4, 5, 6, 7 पूर्ण;
अटल स्थिर काष्ठा clk_parent_data clk81_parent_data[] = अणु
	अणु .fw_name = "xtal", पूर्ण,
	अणु .hw = &g12a_fclk_भाग7.hw पूर्ण,
	अणु .hw = &g12a_mpll1.hw पूर्ण,
	अणु .hw = &g12a_mpll2.hw पूर्ण,
	अणु .hw = &g12a_fclk_भाग4.hw पूर्ण,
	अणु .hw = &g12a_fclk_भाग3.hw पूर्ण,
	अणु .hw = &g12a_fclk_भाग5.hw पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_mpeg_clk_sel = अणु
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

अटल काष्ठा clk_regmap g12a_mpeg_clk_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_MPEG_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mpeg_clk_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_mpeg_clk_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_clk81 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MPEG_CLK_CNTL,
		.bit_idx = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "clk81",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_mpeg_clk_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = (CLK_SET_RATE_PARENT | CLK_IS_CRITICAL),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data g12a_sd_emmc_clk0_parent_data[] = अणु
	अणु .fw_name = "xtal", पूर्ण,
	अणु .hw = &g12a_fclk_भाग2.hw पूर्ण,
	अणु .hw = &g12a_fclk_भाग3.hw पूर्ण,
	अणु .hw = &g12a_fclk_भाग5.hw पूर्ण,
	अणु .hw = &g12a_fclk_भाग7.hw पूर्ण,
	/*
	 * Following these parent घड़ीs, we should also have had mpll2, mpll3
	 * and gp0_pll but these घड़ीs are too precious to be used here. All
	 * the necessary rates क्रम MMC and न_अंकD operation can be acheived using
	 * g12a_ee_core or fclk_भाग घड़ीs
	 */
पूर्ण;

/* SDIO घड़ी */
अटल काष्ठा clk_regmap g12a_sd_emmc_a_clk0_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SD_EMMC_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 9,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "sd_emmc_a_clk0_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_data = g12a_sd_emmc_clk0_parent_data,
		.num_parents = ARRAY_SIZE(g12a_sd_emmc_clk0_parent_data),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_sd_emmc_a_clk0_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_SD_EMMC_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "sd_emmc_a_clk0_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_sd_emmc_a_clk0_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_sd_emmc_a_clk0 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SD_EMMC_CLK_CNTL,
		.bit_idx = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sd_emmc_a_clk0",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_sd_emmc_a_clk0_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* SDcard घड़ी */
अटल काष्ठा clk_regmap g12a_sd_emmc_b_clk0_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SD_EMMC_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 25,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "sd_emmc_b_clk0_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_data = g12a_sd_emmc_clk0_parent_data,
		.num_parents = ARRAY_SIZE(g12a_sd_emmc_clk0_parent_data),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_sd_emmc_b_clk0_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_SD_EMMC_CLK_CNTL,
		.shअगरt = 16,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "sd_emmc_b_clk0_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_sd_emmc_b_clk0_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_sd_emmc_b_clk0 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SD_EMMC_CLK_CNTL,
		.bit_idx = 23,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sd_emmc_b_clk0",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_sd_emmc_b_clk0_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* EMMC/न_अंकD घड़ी */
अटल काष्ठा clk_regmap g12a_sd_emmc_c_clk0_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_न_अंकD_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 9,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "sd_emmc_c_clk0_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_data = g12a_sd_emmc_clk0_parent_data,
		.num_parents = ARRAY_SIZE(g12a_sd_emmc_clk0_parent_data),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_sd_emmc_c_clk0_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_न_अंकD_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "sd_emmc_c_clk0_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_sd_emmc_c_clk0_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_sd_emmc_c_clk0 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_न_अंकD_CLK_CNTL,
		.bit_idx = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sd_emmc_c_clk0",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_sd_emmc_c_clk0_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* Video Clocks */

अटल काष्ठा clk_regmap g12a_vid_pll_भाग = अणु
	.data = &(काष्ठा meson_vid_pll_भाग_data)अणु
		.val = अणु
			.reg_off = HHI_VID_PLL_CLK_DIV,
			.shअगरt   = 0,
			.width   = 15,
		पूर्ण,
		.sel = अणु
			.reg_off = HHI_VID_PLL_CLK_DIV,
			.shअगरt   = 16,
			.width   = 2,
		पूर्ण,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vid_pll_div",
		.ops = &meson_vid_pll_भाग_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_hdmi_pll.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_hw *g12a_vid_pll_parent_hws[] = अणु
	&g12a_vid_pll_भाग.hw,
	&g12a_hdmi_pll.hw,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vid_pll_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VID_PLL_CLK_DIV,
		.mask = 0x1,
		.shअगरt = 18,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vid_pll_sel",
		.ops = &clk_regmap_mux_ops,
		/*
		 * bit 18 selects from 2 possible parents:
		 * vid_pll_भाग or hdmi_pll
		 */
		.parent_hws = g12a_vid_pll_parent_hws,
		.num_parents = ARRAY_SIZE(g12a_vid_pll_parent_hws),
		.flags = CLK_SET_RATE_NO_REPARENT | CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vid_pll = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_PLL_CLK_DIV,
		.bit_idx = 19,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vid_pll",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vid_pll_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

/* VPU Clock */

अटल स्थिर काष्ठा clk_hw *g12a_vpu_parent_hws[] = अणु
	&g12a_fclk_भाग3.hw,
	&g12a_fclk_भाग4.hw,
	&g12a_fclk_भाग5.hw,
	&g12a_fclk_भाग7.hw,
	&g12a_mpll1.hw,
	&g12a_vid_pll.hw,
	&g12a_hअगरi_pll.hw,
	&g12a_gp0_pll.hw,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vpu_0_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 9,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vpu_0_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = g12a_vpu_parent_hws,
		.num_parents = ARRAY_SIZE(g12a_vpu_parent_hws),
		.flags = CLK_SET_RATE_NO_REPARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vpu_0_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vpu_0_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_vpu_0_sel.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vpu_0 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vpu_0",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_vpu_0_भाग.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vpu_1_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 25,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vpu_1_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = g12a_vpu_parent_hws,
		.num_parents = ARRAY_SIZE(g12a_vpu_parent_hws),
		.flags = CLK_SET_RATE_NO_REPARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vpu_1_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.shअगरt = 16,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vpu_1_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_vpu_1_sel.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vpu_1 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.bit_idx = 24,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vpu_1",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_vpu_1_भाग.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vpu = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VPU_CLK_CNTL,
		.mask = 1,
		.shअगरt = 31,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vpu",
		.ops = &clk_regmap_mux_ops,
		/*
		 * bit 31 selects from 2 possible parents:
		 * vpu_0 or vpu_1
		 */
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vpu_0.hw,
			&g12a_vpu_1.hw,
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_NO_REPARENT,
	पूर्ण,
पूर्ण;

/* VDEC घड़ीs */

अटल स्थिर काष्ठा clk_hw *g12a_vdec_parent_hws[] = अणु
	&g12a_fclk_भाग2p5.hw,
	&g12a_fclk_भाग3.hw,
	&g12a_fclk_भाग4.hw,
	&g12a_fclk_भाग5.hw,
	&g12a_fclk_भाग7.hw,
	&g12a_hअगरi_pll.hw,
	&g12a_gp0_pll.hw,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vdec_1_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VDEC_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 9,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vdec_1_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = g12a_vdec_parent_hws,
		.num_parents = ARRAY_SIZE(g12a_vdec_parent_hws),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vdec_1_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VDEC_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
		.flags = CLK_DIVIDER_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vdec_1_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vdec_1_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vdec_1 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VDEC_CLK_CNTL,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vdec_1",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vdec_1_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vdec_hevcf_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VDEC2_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 9,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vdec_hevcf_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = g12a_vdec_parent_hws,
		.num_parents = ARRAY_SIZE(g12a_vdec_parent_hws),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vdec_hevcf_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VDEC2_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
		.flags = CLK_DIVIDER_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vdec_hevcf_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vdec_hevcf_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vdec_hevcf = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VDEC2_CLK_CNTL,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vdec_hevcf",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vdec_hevcf_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vdec_hevc_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VDEC2_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 25,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vdec_hevc_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = g12a_vdec_parent_hws,
		.num_parents = ARRAY_SIZE(g12a_vdec_parent_hws),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vdec_hevc_भाग = अणु
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
			&g12a_vdec_hevc_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vdec_hevc = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VDEC2_CLK_CNTL,
		.bit_idx = 24,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vdec_hevc",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vdec_hevc_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* VAPB Clock */

अटल स्थिर काष्ठा clk_hw *g12a_vapb_parent_hws[] = अणु
	&g12a_fclk_भाग4.hw,
	&g12a_fclk_भाग3.hw,
	&g12a_fclk_भाग5.hw,
	&g12a_fclk_भाग7.hw,
	&g12a_mpll1.hw,
	&g12a_vid_pll.hw,
	&g12a_mpll2.hw,
	&g12a_fclk_भाग2p5.hw,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vapb_0_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VAPBCLK_CNTL,
		.mask = 0x3,
		.shअगरt = 9,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vapb_0_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = g12a_vapb_parent_hws,
		.num_parents = ARRAY_SIZE(g12a_vapb_parent_hws),
		.flags = CLK_SET_RATE_NO_REPARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vapb_0_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VAPBCLK_CNTL,
		.shअगरt = 0,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vapb_0_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vapb_0_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vapb_0 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VAPBCLK_CNTL,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vapb_0",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vapb_0_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vapb_1_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VAPBCLK_CNTL,
		.mask = 0x3,
		.shअगरt = 25,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vapb_1_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = g12a_vapb_parent_hws,
		.num_parents = ARRAY_SIZE(g12a_vapb_parent_hws),
		.flags = CLK_SET_RATE_NO_REPARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vapb_1_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VAPBCLK_CNTL,
		.shअगरt = 16,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vapb_1_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vapb_1_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vapb_1 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VAPBCLK_CNTL,
		.bit_idx = 24,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vapb_1",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vapb_1_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vapb_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VAPBCLK_CNTL,
		.mask = 1,
		.shअगरt = 31,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vapb_sel",
		.ops = &clk_regmap_mux_ops,
		/*
		 * bit 31 selects from 2 possible parents:
		 * vapb_0 or vapb_1
		 */
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vapb_0.hw,
			&g12a_vapb_1.hw,
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_NO_REPARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vapb = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VAPBCLK_CNTL,
		.bit_idx = 30,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vapb",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_vapb_sel.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_hw *g12a_vclk_parent_hws[] = अणु
	&g12a_vid_pll.hw,
	&g12a_gp0_pll.hw,
	&g12a_hअगरi_pll.hw,
	&g12a_mpll1.hw,
	&g12a_fclk_भाग3.hw,
	&g12a_fclk_भाग4.hw,
	&g12a_fclk_भाग5.hw,
	&g12a_fclk_भाग7.hw,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vclk_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 16,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = g12a_vclk_parent_hws,
		.num_parents = ARRAY_SIZE(g12a_vclk_parent_hws),
		.flags = CLK_SET_RATE_NO_REPARENT | CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vclk2_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VIID_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 16,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = g12a_vclk_parent_hws,
		.num_parents = ARRAY_SIZE(g12a_vclk_parent_hws),
		.flags = CLK_SET_RATE_NO_REPARENT | CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vclk_input = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_DIV,
		.bit_idx = 16,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk_input",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_vclk_sel.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vclk2_input = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_DIV,
		.bit_idx = 16,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk2_input",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_vclk2_sel.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vclk_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VID_CLK_DIV,
		.shअगरt = 0,
		.width = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vclk_input.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vclk2_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_VIID_CLK_DIV,
		.shअगरt = 0,
		.width = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vclk2_input.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vclk = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.bit_idx = 19,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_vclk_भाग.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vclk2 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_CNTL,
		.bit_idx = 19,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk2",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_vclk2_भाग.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vclk_भाग1 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.bit_idx = 0,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk_div1",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_vclk.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vclk_भाग2_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.bit_idx = 1,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk_div2_en",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_vclk.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vclk_भाग4_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.bit_idx = 2,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk_div4_en",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_vclk.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vclk_भाग6_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.bit_idx = 3,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk_div6_en",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_vclk.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vclk_भाग12_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL,
		.bit_idx = 4,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk_div12_en",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_vclk.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vclk2_भाग1 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_CNTL,
		.bit_idx = 0,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk2_div1",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_vclk2.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vclk2_भाग2_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_CNTL,
		.bit_idx = 1,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk2_div2_en",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_vclk2.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vclk2_भाग4_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_CNTL,
		.bit_idx = 2,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk2_div4_en",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_vclk2.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vclk2_भाग6_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_CNTL,
		.bit_idx = 3,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk2_div6_en",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_vclk2.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_vclk2_भाग12_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VIID_CLK_CNTL,
		.bit_idx = 4,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "vclk2_div12_en",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_vclk2.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12a_vclk_भाग2 = अणु
	.mult = 1,
	.भाग = 2,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_div2",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vclk_भाग2_en.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12a_vclk_भाग4 = अणु
	.mult = 1,
	.भाग = 4,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_div4",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vclk_भाग4_en.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12a_vclk_भाग6 = अणु
	.mult = 1,
	.भाग = 6,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_div6",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vclk_भाग6_en.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12a_vclk_भाग12 = अणु
	.mult = 1,
	.भाग = 12,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk_div12",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vclk_भाग12_en.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12a_vclk2_भाग2 = अणु
	.mult = 1,
	.भाग = 2,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_div2",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vclk2_भाग2_en.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12a_vclk2_भाग4 = अणु
	.mult = 1,
	.भाग = 4,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_div4",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vclk2_भाग4_en.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12a_vclk2_भाग6 = अणु
	.mult = 1,
	.भाग = 6,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_div6",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vclk2_भाग6_en.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor g12a_vclk2_भाग12 = अणु
	.mult = 1,
	.भाग = 12,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vclk2_div12",
		.ops = &clk_fixed_factor_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_vclk2_भाग12_en.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल u32 mux_table_cts_sel[] = अणु 0, 1, 2, 3, 4, 8, 9, 10, 11, 12 पूर्ण;
अटल स्थिर काष्ठा clk_hw *g12a_cts_parent_hws[] = अणु
	&g12a_vclk_भाग1.hw,
	&g12a_vclk_भाग2.hw,
	&g12a_vclk_भाग4.hw,
	&g12a_vclk_भाग6.hw,
	&g12a_vclk_भाग12.hw,
	&g12a_vclk2_भाग1.hw,
	&g12a_vclk2_भाग2.hw,
	&g12a_vclk2_भाग4.hw,
	&g12a_vclk2_भाग6.hw,
	&g12a_vclk2_भाग12.hw,
पूर्ण;

अटल काष्ठा clk_regmap g12a_cts_enci_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VID_CLK_DIV,
		.mask = 0xf,
		.shअगरt = 28,
		.table = mux_table_cts_sel,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cts_enci_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = g12a_cts_parent_hws,
		.num_parents = ARRAY_SIZE(g12a_cts_parent_hws),
		.flags = CLK_SET_RATE_NO_REPARENT | CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_cts_encp_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VID_CLK_DIV,
		.mask = 0xf,
		.shअगरt = 20,
		.table = mux_table_cts_sel,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cts_encp_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = g12a_cts_parent_hws,
		.num_parents = ARRAY_SIZE(g12a_cts_parent_hws),
		.flags = CLK_SET_RATE_NO_REPARENT | CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_cts_vdac_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_VIID_CLK_DIV,
		.mask = 0xf,
		.shअगरt = 28,
		.table = mux_table_cts_sel,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cts_vdac_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = g12a_cts_parent_hws,
		.num_parents = ARRAY_SIZE(g12a_cts_parent_hws),
		.flags = CLK_SET_RATE_NO_REPARENT | CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

/* TOFIX: add support क्रम cts_tcon */
अटल u32 mux_table_hdmi_tx_sel[] = अणु 0, 1, 2, 3, 4, 8, 9, 10, 11, 12 पूर्ण;
अटल स्थिर काष्ठा clk_hw *g12a_cts_hdmi_tx_parent_hws[] = अणु
	&g12a_vclk_भाग1.hw,
	&g12a_vclk_भाग2.hw,
	&g12a_vclk_भाग4.hw,
	&g12a_vclk_भाग6.hw,
	&g12a_vclk_भाग12.hw,
	&g12a_vclk2_भाग1.hw,
	&g12a_vclk2_भाग2.hw,
	&g12a_vclk2_भाग4.hw,
	&g12a_vclk2_भाग6.hw,
	&g12a_vclk2_भाग12.hw,
पूर्ण;

अटल काष्ठा clk_regmap g12a_hdmi_tx_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_HDMI_CLK_CNTL,
		.mask = 0xf,
		.shअगरt = 16,
		.table = mux_table_hdmi_tx_sel,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "hdmi_tx_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = g12a_cts_hdmi_tx_parent_hws,
		.num_parents = ARRAY_SIZE(g12a_cts_hdmi_tx_parent_hws),
		.flags = CLK_SET_RATE_NO_REPARENT | CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_cts_enci = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL2,
		.bit_idx = 0,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "cts_enci",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_cts_enci_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_cts_encp = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL2,
		.bit_idx = 2,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "cts_encp",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_cts_encp_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_cts_vdac = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL2,
		.bit_idx = 4,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "cts_vdac",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_cts_vdac_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_hdmi_tx = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_VID_CLK_CNTL2,
		.bit_idx = 5,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "hdmi_tx",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_hdmi_tx_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

/* MIPI DSI Host Clocks */

अटल स्थिर काष्ठा clk_hw *g12a_mipi_dsi_pxclk_parent_hws[] = अणु
	&g12a_vid_pll.hw,
	&g12a_gp0_pll.hw,
	&g12a_hअगरi_pll.hw,
	&g12a_mpll1.hw,
	&g12a_fclk_भाग2.hw,
	&g12a_fclk_भाग2p5.hw,
	&g12a_fclk_भाग3.hw,
	&g12a_fclk_भाग7.hw,
पूर्ण;

अटल काष्ठा clk_regmap g12a_mipi_dsi_pxclk_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_MIPIDSI_PHY_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 12,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mipi_dsi_pxclk_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = g12a_mipi_dsi_pxclk_parent_hws,
		.num_parents = ARRAY_SIZE(g12a_mipi_dsi_pxclk_parent_hws),
		.flags = CLK_SET_RATE_NO_REPARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_mipi_dsi_pxclk_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_MIPIDSI_PHY_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mipi_dsi_pxclk_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_mipi_dsi_pxclk_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_mipi_dsi_pxclk = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MIPIDSI_PHY_CLK_CNTL,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "mipi_dsi_pxclk",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_mipi_dsi_pxclk_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* HDMI Clocks */

अटल स्थिर काष्ठा clk_parent_data g12a_hdmi_parent_data[] = अणु
	अणु .fw_name = "xtal", पूर्ण,
	अणु .hw = &g12a_fclk_भाग4.hw पूर्ण,
	अणु .hw = &g12a_fclk_भाग3.hw पूर्ण,
	अणु .hw = &g12a_fclk_भाग5.hw पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_hdmi_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_HDMI_CLK_CNTL,
		.mask = 0x3,
		.shअगरt = 9,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "hdmi_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_data = g12a_hdmi_parent_data,
		.num_parents = ARRAY_SIZE(g12a_hdmi_parent_data),
		.flags = CLK_SET_RATE_NO_REPARENT | CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_hdmi_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_HDMI_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "hdmi_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_hdmi_sel.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_hdmi = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_HDMI_CLK_CNTL,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "hdmi",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &g12a_hdmi_भाग.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
	पूर्ण,
पूर्ण;

/*
 * The MALI IP is घड़ीed by two identical घड़ीs (mali_0 and mali_1)
 * muxed by a glitch-मुक्त चयन. The CCF can manage this glitch-मुक्त
 * mux because it करोes top-to-bottom updates the each घड़ी tree and
 * चयनes to the "inactive" one when CLK_SET_RATE_GATE is set.
 */
अटल स्थिर काष्ठा clk_parent_data g12a_mali_0_1_parent_data[] = अणु
	अणु .fw_name = "xtal", पूर्ण,
	अणु .hw = &g12a_gp0_pll.hw पूर्ण,
	अणु .hw = &g12a_hअगरi_pll.hw पूर्ण,
	अणु .hw = &g12a_fclk_भाग2p5.hw पूर्ण,
	अणु .hw = &g12a_fclk_भाग3.hw पूर्ण,
	अणु .hw = &g12a_fclk_भाग4.hw पूर्ण,
	अणु .hw = &g12a_fclk_भाग5.hw पूर्ण,
	अणु .hw = &g12a_fclk_भाग7.hw पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_mali_0_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_MALI_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 9,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mali_0_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_data = g12a_mali_0_1_parent_data,
		.num_parents = 8,
		/*
		 * Don't request the parent to change the rate because
		 * all GPU frequencies can be derived from the fclk_*
		 * घड़ीs and one special GP0_PLL setting. This is
		 * important because we need the MPLL घड़ीs क्रम audio.
		 */
		.flags = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_mali_0_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_MALI_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mali_0_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_mali_0_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_mali_0 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MALI_CLK_CNTL,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mali_0",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_mali_0_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_GATE | CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_mali_1_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_MALI_CLK_CNTL,
		.mask = 0x7,
		.shअगरt = 25,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mali_1_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_data = g12a_mali_0_1_parent_data,
		.num_parents = 8,
		/*
		 * Don't request the parent to change the rate because
		 * all GPU frequencies can be derived from the fclk_*
		 * घड़ीs and one special GP0_PLL setting. This is
		 * important because we need the MPLL घड़ीs क्रम audio.
		 */
		.flags = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_mali_1_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_MALI_CLK_CNTL,
		.shअगरt = 16,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mali_1_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_mali_1_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_mali_1 = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_MALI_CLK_CNTL,
		.bit_idx = 24,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mali_1",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_mali_1_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_GATE | CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_hw *g12a_mali_parent_hws[] = अणु
	&g12a_mali_0.hw,
	&g12a_mali_1.hw,
पूर्ण;

अटल काष्ठा clk_regmap g12a_mali = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_MALI_CLK_CNTL,
		.mask = 1,
		.shअगरt = 31,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mali",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = g12a_mali_parent_hws,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_ts_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_TS_CLK_CNTL,
		.shअगरt = 0,
		.width = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ts_div",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			.fw_name = "xtal",
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_ts = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_TS_CLK_CNTL,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ts",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_ts_भाग.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

/* SPICC SCLK source घड़ी */

अटल स्थिर काष्ठा clk_parent_data spicc_sclk_parent_data[] = अणु
	अणु .fw_name = "xtal", पूर्ण,
	अणु .hw = &g12a_clk81.hw पूर्ण,
	अणु .hw = &g12a_fclk_भाग4.hw पूर्ण,
	अणु .hw = &g12a_fclk_भाग3.hw पूर्ण,
	अणु .hw = &g12a_fclk_भाग5.hw पूर्ण,
	अणु .hw = &g12a_fclk_भाग7.hw पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_spicc0_sclk_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SPICC_CLK_CNTL,
		.mask = 7,
		.shअगरt = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "spicc0_sclk_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_data = spicc_sclk_parent_data,
		.num_parents = ARRAY_SIZE(spicc_sclk_parent_data),
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_spicc0_sclk_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_SPICC_CLK_CNTL,
		.shअगरt = 0,
		.width = 6,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "spicc0_sclk_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_spicc0_sclk_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_spicc0_sclk = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SPICC_CLK_CNTL,
		.bit_idx = 6,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "spicc0_sclk",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_spicc0_sclk_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_spicc1_sclk_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_SPICC_CLK_CNTL,
		.mask = 7,
		.shअगरt = 23,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "spicc1_sclk_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_data = spicc_sclk_parent_data,
		.num_parents = ARRAY_SIZE(spicc_sclk_parent_data),
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_spicc1_sclk_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_SPICC_CLK_CNTL,
		.shअगरt = 16,
		.width = 6,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "spicc1_sclk_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_spicc1_sclk_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_spicc1_sclk = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_SPICC_CLK_CNTL,
		.bit_idx = 22,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "spicc1_sclk",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_spicc1_sclk_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* Neural Network Accelerator source घड़ी */

अटल स्थिर काष्ठा clk_parent_data nna_clk_parent_data[] = अणु
	अणु .fw_name = "xtal", पूर्ण,
	अणु .hw = &g12a_gp0_pll.hw, पूर्ण,
	अणु .hw = &g12a_hअगरi_pll.hw, पूर्ण,
	अणु .hw = &g12a_fclk_भाग2p5.hw, पूर्ण,
	अणु .hw = &g12a_fclk_भाग3.hw, पूर्ण,
	अणु .hw = &g12a_fclk_भाग4.hw, पूर्ण,
	अणु .hw = &g12a_fclk_भाग5.hw, पूर्ण,
	अणु .hw = &g12a_fclk_भाग7.hw पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap sm1_nna_axi_clk_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_NNA_CLK_CNTL,
		.mask = 7,
		.shअगरt = 9,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "nna_axi_clk_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_data = nna_clk_parent_data,
		.num_parents = ARRAY_SIZE(nna_clk_parent_data),
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap sm1_nna_axi_clk_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_NNA_CLK_CNTL,
		.shअगरt = 0,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "nna_axi_clk_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&sm1_nna_axi_clk_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap sm1_nna_axi_clk = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_NNA_CLK_CNTL,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "nna_axi_clk",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&sm1_nna_axi_clk_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap sm1_nna_core_clk_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = HHI_NNA_CLK_CNTL,
		.mask = 7,
		.shअगरt = 25,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "nna_core_clk_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_data = nna_clk_parent_data,
		.num_parents = ARRAY_SIZE(nna_clk_parent_data),
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap sm1_nna_core_clk_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = HHI_NNA_CLK_CNTL,
		.shअगरt = 16,
		.width = 7,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "nna_core_clk_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&sm1_nna_core_clk_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap sm1_nna_core_clk = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = HHI_NNA_CLK_CNTL,
		.bit_idx = 24,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "nna_core_clk",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&sm1_nna_core_clk_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

#घोषणा MESON_GATE(_name, _reg, _bit) \
	MESON_PCLK(_name, _reg, _bit, &g12a_clk81.hw)

#घोषणा MESON_GATE_RO(_name, _reg, _bit) \
	MESON_PCLK_RO(_name, _reg, _bit, &g12a_clk81.hw)

/* Everything Else (EE) करोमुख्य gates */
अटल MESON_GATE(g12a_ddr,			HHI_GCLK_MPEG0,	0);
अटल MESON_GATE(g12a_करोs,			HHI_GCLK_MPEG0,	1);
अटल MESON_GATE(g12a_audio_locker,		HHI_GCLK_MPEG0,	2);
अटल MESON_GATE(g12a_mipi_dsi_host,		HHI_GCLK_MPEG0,	3);
अटल MESON_GATE(g12a_eth_phy,			HHI_GCLK_MPEG0,	4);
अटल MESON_GATE(g12a_isa,			HHI_GCLK_MPEG0,	5);
अटल MESON_GATE(g12a_pl301,			HHI_GCLK_MPEG0,	6);
अटल MESON_GATE(g12a_periphs,			HHI_GCLK_MPEG0,	7);
अटल MESON_GATE(g12a_spicc_0,			HHI_GCLK_MPEG0,	8);
अटल MESON_GATE(g12a_i2c,			HHI_GCLK_MPEG0,	9);
अटल MESON_GATE(g12a_sana,			HHI_GCLK_MPEG0,	10);
अटल MESON_GATE(g12a_sd,			HHI_GCLK_MPEG0,	11);
अटल MESON_GATE(g12a_rng0,			HHI_GCLK_MPEG0,	12);
अटल MESON_GATE(g12a_uart0,			HHI_GCLK_MPEG0,	13);
अटल MESON_GATE(g12a_spicc_1,			HHI_GCLK_MPEG0,	14);
अटल MESON_GATE(g12a_hiu_reg,			HHI_GCLK_MPEG0,	19);
अटल MESON_GATE(g12a_mipi_dsi_phy,		HHI_GCLK_MPEG0,	20);
अटल MESON_GATE(g12a_assist_misc,		HHI_GCLK_MPEG0,	23);
अटल MESON_GATE(g12a_emmc_a,			HHI_GCLK_MPEG0,	4);
अटल MESON_GATE(g12a_emmc_b,			HHI_GCLK_MPEG0,	25);
अटल MESON_GATE(g12a_emmc_c,			HHI_GCLK_MPEG0,	26);
अटल MESON_GATE(g12a_audio_codec,		HHI_GCLK_MPEG0,	28);

अटल MESON_GATE(g12a_audio,			HHI_GCLK_MPEG1,	0);
अटल MESON_GATE(g12a_eth_core,		HHI_GCLK_MPEG1,	3);
अटल MESON_GATE(g12a_demux,			HHI_GCLK_MPEG1,	4);
अटल MESON_GATE(g12a_audio_अगरअगरo,		HHI_GCLK_MPEG1,	11);
अटल MESON_GATE(g12a_adc,			HHI_GCLK_MPEG1,	13);
अटल MESON_GATE(g12a_uart1,			HHI_GCLK_MPEG1,	16);
अटल MESON_GATE(g12a_g2d,			HHI_GCLK_MPEG1,	20);
अटल MESON_GATE(g12a_reset,			HHI_GCLK_MPEG1,	23);
अटल MESON_GATE(g12a_pcie_comb,		HHI_GCLK_MPEG1,	24);
अटल MESON_GATE(g12a_parser,			HHI_GCLK_MPEG1,	25);
अटल MESON_GATE(g12a_usb_general,		HHI_GCLK_MPEG1,	26);
अटल MESON_GATE(g12a_pcie_phy,		HHI_GCLK_MPEG1,	27);
अटल MESON_GATE(g12a_ahb_arb0,		HHI_GCLK_MPEG1,	29);

अटल MESON_GATE(g12a_ahb_data_bus,		HHI_GCLK_MPEG2,	1);
अटल MESON_GATE(g12a_ahb_ctrl_bus,		HHI_GCLK_MPEG2,	2);
अटल MESON_GATE(g12a_htx_hdcp22,		HHI_GCLK_MPEG2,	3);
अटल MESON_GATE(g12a_htx_pclk,		HHI_GCLK_MPEG2,	4);
अटल MESON_GATE(g12a_bt656,			HHI_GCLK_MPEG2,	6);
अटल MESON_GATE(g12a_usb1_to_ddr,		HHI_GCLK_MPEG2,	8);
अटल MESON_GATE(g12a_mmc_pclk,		HHI_GCLK_MPEG2,	11);
अटल MESON_GATE(g12a_uart2,			HHI_GCLK_MPEG2,	15);
अटल MESON_GATE(g12a_vpu_पूर्णांकr,		HHI_GCLK_MPEG2,	25);
अटल MESON_GATE(g12a_gic,			HHI_GCLK_MPEG2,	30);

अटल MESON_GATE(g12a_vclk2_venci0,		HHI_GCLK_OTHER,	1);
अटल MESON_GATE(g12a_vclk2_venci1,		HHI_GCLK_OTHER,	2);
अटल MESON_GATE(g12a_vclk2_vencp0,		HHI_GCLK_OTHER,	3);
अटल MESON_GATE(g12a_vclk2_vencp1,		HHI_GCLK_OTHER,	4);
अटल MESON_GATE(g12a_vclk2_venct0,		HHI_GCLK_OTHER,	5);
अटल MESON_GATE(g12a_vclk2_venct1,		HHI_GCLK_OTHER,	6);
अटल MESON_GATE(g12a_vclk2_other,		HHI_GCLK_OTHER,	7);
अटल MESON_GATE(g12a_vclk2_enci,		HHI_GCLK_OTHER,	8);
अटल MESON_GATE(g12a_vclk2_encp,		HHI_GCLK_OTHER,	9);
अटल MESON_GATE(g12a_dac_clk,			HHI_GCLK_OTHER,	10);
अटल MESON_GATE(g12a_aoclk_gate,		HHI_GCLK_OTHER,	14);
अटल MESON_GATE(g12a_iec958_gate,		HHI_GCLK_OTHER,	16);
अटल MESON_GATE(g12a_enc480p,			HHI_GCLK_OTHER,	20);
अटल MESON_GATE(g12a_rng1,			HHI_GCLK_OTHER,	21);
अटल MESON_GATE(g12a_vclk2_enct,		HHI_GCLK_OTHER,	22);
अटल MESON_GATE(g12a_vclk2_encl,		HHI_GCLK_OTHER,	23);
अटल MESON_GATE(g12a_vclk2_venclmmc,		HHI_GCLK_OTHER,	24);
अटल MESON_GATE(g12a_vclk2_vencl,		HHI_GCLK_OTHER,	25);
अटल MESON_GATE(g12a_vclk2_other1,		HHI_GCLK_OTHER,	26);

अटल MESON_GATE_RO(g12a_dma,			HHI_GCLK_OTHER2, 0);
अटल MESON_GATE_RO(g12a_efuse,		HHI_GCLK_OTHER2, 1);
अटल MESON_GATE_RO(g12a_rom_boot,		HHI_GCLK_OTHER2, 2);
अटल MESON_GATE_RO(g12a_reset_sec,		HHI_GCLK_OTHER2, 3);
अटल MESON_GATE_RO(g12a_sec_ahb_apb3,		HHI_GCLK_OTHER2, 4);

/* Array of all घड़ीs provided by this provider */
अटल काष्ठा clk_hw_onecell_data g12a_hw_onecell_data = अणु
	.hws = अणु
		[CLKID_SYS_PLL]			= &g12a_sys_pll.hw,
		[CLKID_FIXED_PLL]		= &g12a_fixed_pll.hw,
		[CLKID_FCLK_DIV2]		= &g12a_fclk_भाग2.hw,
		[CLKID_FCLK_DIV3]		= &g12a_fclk_भाग3.hw,
		[CLKID_FCLK_DIV4]		= &g12a_fclk_भाग4.hw,
		[CLKID_FCLK_DIV5]		= &g12a_fclk_भाग5.hw,
		[CLKID_FCLK_DIV7]		= &g12a_fclk_भाग7.hw,
		[CLKID_FCLK_DIV2P5]		= &g12a_fclk_भाग2p5.hw,
		[CLKID_GP0_PLL]			= &g12a_gp0_pll.hw,
		[CLKID_MPEG_SEL]		= &g12a_mpeg_clk_sel.hw,
		[CLKID_MPEG_DIV]		= &g12a_mpeg_clk_भाग.hw,
		[CLKID_CLK81]			= &g12a_clk81.hw,
		[CLKID_MPLL0]			= &g12a_mpll0.hw,
		[CLKID_MPLL1]			= &g12a_mpll1.hw,
		[CLKID_MPLL2]			= &g12a_mpll2.hw,
		[CLKID_MPLL3]			= &g12a_mpll3.hw,
		[CLKID_DDR]			= &g12a_ddr.hw,
		[CLKID_DOS]			= &g12a_डॉस.सw,
		[CLKID_AUDIO_LOCKER]		= &g12a_audio_locker.hw,
		[CLKID_MIPI_DSI_HOST]		= &g12a_mipi_dsi_host.hw,
		[CLKID_ETH_PHY]			= &g12a_eth_phy.hw,
		[CLKID_ISA]			= &g12a_isa.hw,
		[CLKID_PL301]			= &g12a_pl301.hw,
		[CLKID_PERIPHS]			= &g12a_periphs.hw,
		[CLKID_SPICC0]			= &g12a_spicc_0.hw,
		[CLKID_I2C]			= &g12a_i2c.hw,
		[CLKID_SANA]			= &g12a_sana.hw,
		[CLKID_SD]			= &g12a_sd.hw,
		[CLKID_RNG0]			= &g12a_rng0.hw,
		[CLKID_UART0]			= &g12a_uart0.hw,
		[CLKID_SPICC1]			= &g12a_spicc_1.hw,
		[CLKID_HIU_IFACE]		= &g12a_hiu_reg.hw,
		[CLKID_MIPI_DSI_PHY]		= &g12a_mipi_dsi_phy.hw,
		[CLKID_ASSIST_MISC]		= &g12a_assist_misc.hw,
		[CLKID_SD_EMMC_A]		= &g12a_emmc_a.hw,
		[CLKID_SD_EMMC_B]		= &g12a_emmc_b.hw,
		[CLKID_SD_EMMC_C]		= &g12a_emmc_c.hw,
		[CLKID_AUDIO_CODEC]		= &g12a_audio_codec.hw,
		[CLKID_AUDIO]			= &g12a_audपन.सw,
		[CLKID_ETH]			= &g12a_eth_core.hw,
		[CLKID_DEMUX]			= &g12a_demux.hw,
		[CLKID_AUDIO_IFIFO]		= &g12a_audio_अगरअगरo.hw,
		[CLKID_ADC]			= &g12a_adc.hw,
		[CLKID_UART1]			= &g12a_uart1.hw,
		[CLKID_G2D]			= &g12a_g2d.hw,
		[CLKID_RESET]			= &g12a_reset.hw,
		[CLKID_PCIE_COMB]		= &g12a_pcie_comb.hw,
		[CLKID_PARSER]			= &g12a_parser.hw,
		[CLKID_USB]			= &g12a_usb_general.hw,
		[CLKID_PCIE_PHY]		= &g12a_pcie_phy.hw,
		[CLKID_AHB_ARB0]		= &g12a_ahb_arb0.hw,
		[CLKID_AHB_DATA_BUS]		= &g12a_ahb_data_bus.hw,
		[CLKID_AHB_CTRL_BUS]		= &g12a_ahb_ctrl_bus.hw,
		[CLKID_HTX_HDCP22]		= &g12a_htx_hdcp22.hw,
		[CLKID_HTX_PCLK]		= &g12a_htx_pclk.hw,
		[CLKID_BT656]			= &g12a_bt656.hw,
		[CLKID_USB1_DDR_BRIDGE]		= &g12a_usb1_to_ddr.hw,
		[CLKID_MMC_PCLK]		= &g12a_mmc_pclk.hw,
		[CLKID_UART2]			= &g12a_uart2.hw,
		[CLKID_VPU_INTR]		= &g12a_vpu_पूर्णांकr.hw,
		[CLKID_GIC]			= &g12a_gic.hw,
		[CLKID_SD_EMMC_A_CLK0_SEL]	= &g12a_sd_emmc_a_clk0_sel.hw,
		[CLKID_SD_EMMC_A_CLK0_DIV]	= &g12a_sd_emmc_a_clk0_भाग.hw,
		[CLKID_SD_EMMC_A_CLK0]		= &g12a_sd_emmc_a_clk0.hw,
		[CLKID_SD_EMMC_B_CLK0_SEL]	= &g12a_sd_emmc_b_clk0_sel.hw,
		[CLKID_SD_EMMC_B_CLK0_DIV]	= &g12a_sd_emmc_b_clk0_भाग.hw,
		[CLKID_SD_EMMC_B_CLK0]		= &g12a_sd_emmc_b_clk0.hw,
		[CLKID_SD_EMMC_C_CLK0_SEL]	= &g12a_sd_emmc_c_clk0_sel.hw,
		[CLKID_SD_EMMC_C_CLK0_DIV]	= &g12a_sd_emmc_c_clk0_भाग.hw,
		[CLKID_SD_EMMC_C_CLK0]		= &g12a_sd_emmc_c_clk0.hw,
		[CLKID_MPLL0_DIV]		= &g12a_mpll0_भाग.hw,
		[CLKID_MPLL1_DIV]		= &g12a_mpll1_भाग.hw,
		[CLKID_MPLL2_DIV]		= &g12a_mpll2_भाग.hw,
		[CLKID_MPLL3_DIV]		= &g12a_mpll3_भाग.hw,
		[CLKID_FCLK_DIV2_DIV]		= &g12a_fclk_भाग2_भाग.hw,
		[CLKID_FCLK_DIV3_DIV]		= &g12a_fclk_भाग3_भाग.hw,
		[CLKID_FCLK_DIV4_DIV]		= &g12a_fclk_भाग4_भाग.hw,
		[CLKID_FCLK_DIV5_DIV]		= &g12a_fclk_भाग5_भाग.hw,
		[CLKID_FCLK_DIV7_DIV]		= &g12a_fclk_भाग7_भाग.hw,
		[CLKID_FCLK_DIV2P5_DIV]		= &g12a_fclk_भाग2p5_भाग.hw,
		[CLKID_HIFI_PLL]		= &g12a_hअगरi_pll.hw,
		[CLKID_VCLK2_VENCI0]		= &g12a_vclk2_venci0.hw,
		[CLKID_VCLK2_VENCI1]		= &g12a_vclk2_venci1.hw,
		[CLKID_VCLK2_VENCP0]		= &g12a_vclk2_vencp0.hw,
		[CLKID_VCLK2_VENCP1]		= &g12a_vclk2_vencp1.hw,
		[CLKID_VCLK2_VENCT0]		= &g12a_vclk2_venct0.hw,
		[CLKID_VCLK2_VENCT1]		= &g12a_vclk2_venct1.hw,
		[CLKID_VCLK2_OTHER]		= &g12a_vclk2_other.hw,
		[CLKID_VCLK2_ENCI]		= &g12a_vclk2_enci.hw,
		[CLKID_VCLK2_ENCP]		= &g12a_vclk2_encp.hw,
		[CLKID_DAC_CLK]			= &g12a_dac_clk.hw,
		[CLKID_AOCLK]			= &g12a_aoclk_gate.hw,
		[CLKID_IEC958]			= &g12a_iec958_gate.hw,
		[CLKID_ENC480P]			= &g12a_enc480p.hw,
		[CLKID_RNG1]			= &g12a_rng1.hw,
		[CLKID_VCLK2_ENCT]		= &g12a_vclk2_enct.hw,
		[CLKID_VCLK2_ENCL]		= &g12a_vclk2_encl.hw,
		[CLKID_VCLK2_VENCLMMC]		= &g12a_vclk2_venclmmc.hw,
		[CLKID_VCLK2_VENCL]		= &g12a_vclk2_vencl.hw,
		[CLKID_VCLK2_OTHER1]		= &g12a_vclk2_other1.hw,
		[CLKID_FIXED_PLL_DCO]		= &g12a_fixed_pll_dco.hw,
		[CLKID_SYS_PLL_DCO]		= &g12a_sys_pll_dco.hw,
		[CLKID_GP0_PLL_DCO]		= &g12a_gp0_pll_dco.hw,
		[CLKID_HIFI_PLL_DCO]		= &g12a_hअगरi_pll_dco.hw,
		[CLKID_DMA]			= &g12a_dma.hw,
		[CLKID_EFUSE]			= &g12a_efuse.hw,
		[CLKID_ROM_BOOT]		= &g12a_rom_boot.hw,
		[CLKID_RESET_SEC]		= &g12a_reset_sec.hw,
		[CLKID_SEC_AHB_APB3]		= &g12a_sec_ahb_apb3.hw,
		[CLKID_MPLL_PREDIV]		= &g12a_mpll_preभाग.hw,
		[CLKID_VPU_0_SEL]		= &g12a_vpu_0_sel.hw,
		[CLKID_VPU_0_DIV]		= &g12a_vpu_0_भाग.hw,
		[CLKID_VPU_0]			= &g12a_vpu_0.hw,
		[CLKID_VPU_1_SEL]		= &g12a_vpu_1_sel.hw,
		[CLKID_VPU_1_DIV]		= &g12a_vpu_1_भाग.hw,
		[CLKID_VPU_1]			= &g12a_vpu_1.hw,
		[CLKID_VPU]			= &g12a_vpu.hw,
		[CLKID_VAPB_0_SEL]		= &g12a_vapb_0_sel.hw,
		[CLKID_VAPB_0_DIV]		= &g12a_vapb_0_भाग.hw,
		[CLKID_VAPB_0]			= &g12a_vapb_0.hw,
		[CLKID_VAPB_1_SEL]		= &g12a_vapb_1_sel.hw,
		[CLKID_VAPB_1_DIV]		= &g12a_vapb_1_भाग.hw,
		[CLKID_VAPB_1]			= &g12a_vapb_1.hw,
		[CLKID_VAPB_SEL]		= &g12a_vapb_sel.hw,
		[CLKID_VAPB]			= &g12a_vapb.hw,
		[CLKID_HDMI_PLL_DCO]		= &g12a_hdmi_pll_dco.hw,
		[CLKID_HDMI_PLL_OD]		= &g12a_hdmi_pll_od.hw,
		[CLKID_HDMI_PLL_OD2]		= &g12a_hdmi_pll_od2.hw,
		[CLKID_HDMI_PLL]		= &g12a_hdmi_pll.hw,
		[CLKID_VID_PLL]			= &g12a_vid_pll_भाग.hw,
		[CLKID_VID_PLL_SEL]		= &g12a_vid_pll_sel.hw,
		[CLKID_VID_PLL_DIV]		= &g12a_vid_pll.hw,
		[CLKID_VCLK_SEL]		= &g12a_vclk_sel.hw,
		[CLKID_VCLK2_SEL]		= &g12a_vclk2_sel.hw,
		[CLKID_VCLK_INPUT]		= &g12a_vclk_input.hw,
		[CLKID_VCLK2_INPUT]		= &g12a_vclk2_input.hw,
		[CLKID_VCLK_DIV]		= &g12a_vclk_भाग.hw,
		[CLKID_VCLK2_DIV]		= &g12a_vclk2_भाग.hw,
		[CLKID_VCLK]			= &g12a_vclk.hw,
		[CLKID_VCLK2]			= &g12a_vclk2.hw,
		[CLKID_VCLK_DIV1]		= &g12a_vclk_भाग1.hw,
		[CLKID_VCLK_DIV2_EN]		= &g12a_vclk_भाग2_en.hw,
		[CLKID_VCLK_DIV4_EN]		= &g12a_vclk_भाग4_en.hw,
		[CLKID_VCLK_DIV6_EN]		= &g12a_vclk_भाग6_en.hw,
		[CLKID_VCLK_DIV12_EN]		= &g12a_vclk_भाग12_en.hw,
		[CLKID_VCLK2_DIV1]		= &g12a_vclk2_भाग1.hw,
		[CLKID_VCLK2_DIV2_EN]		= &g12a_vclk2_भाग2_en.hw,
		[CLKID_VCLK2_DIV4_EN]		= &g12a_vclk2_भाग4_en.hw,
		[CLKID_VCLK2_DIV6_EN]		= &g12a_vclk2_भाग6_en.hw,
		[CLKID_VCLK2_DIV12_EN]		= &g12a_vclk2_भाग12_en.hw,
		[CLKID_VCLK_DIV2]		= &g12a_vclk_भाग2.hw,
		[CLKID_VCLK_DIV4]		= &g12a_vclk_भाग4.hw,
		[CLKID_VCLK_DIV6]		= &g12a_vclk_भाग6.hw,
		[CLKID_VCLK_DIV12]		= &g12a_vclk_भाग12.hw,
		[CLKID_VCLK2_DIV2]		= &g12a_vclk2_भाग2.hw,
		[CLKID_VCLK2_DIV4]		= &g12a_vclk2_भाग4.hw,
		[CLKID_VCLK2_DIV6]		= &g12a_vclk2_भाग6.hw,
		[CLKID_VCLK2_DIV12]		= &g12a_vclk2_भाग12.hw,
		[CLKID_CTS_ENCI_SEL]		= &g12a_cts_enci_sel.hw,
		[CLKID_CTS_ENCP_SEL]		= &g12a_cts_encp_sel.hw,
		[CLKID_CTS_VDAC_SEL]		= &g12a_cts_vdac_sel.hw,
		[CLKID_HDMI_TX_SEL]		= &g12a_hdmi_tx_sel.hw,
		[CLKID_CTS_ENCI]		= &g12a_cts_enci.hw,
		[CLKID_CTS_ENCP]		= &g12a_cts_encp.hw,
		[CLKID_CTS_VDAC]		= &g12a_cts_vdac.hw,
		[CLKID_HDMI_TX]			= &g12a_hdmi_tx.hw,
		[CLKID_HDMI_SEL]		= &g12a_hdmi_sel.hw,
		[CLKID_HDMI_DIV]		= &g12a_hdmi_भाग.hw,
		[CLKID_HDMI]			= &g12a_hdmi.hw,
		[CLKID_MALI_0_SEL]		= &g12a_mali_0_sel.hw,
		[CLKID_MALI_0_DIV]		= &g12a_mali_0_भाग.hw,
		[CLKID_MALI_0]			= &g12a_mali_0.hw,
		[CLKID_MALI_1_SEL]		= &g12a_mali_1_sel.hw,
		[CLKID_MALI_1_DIV]		= &g12a_mali_1_भाग.hw,
		[CLKID_MALI_1]			= &g12a_mali_1.hw,
		[CLKID_MALI]			= &g12a_mali.hw,
		[CLKID_MPLL_50M_DIV]		= &g12a_mpll_50m_भाग.hw,
		[CLKID_MPLL_50M]		= &g12a_mpll_50m.hw,
		[CLKID_SYS_PLL_DIV16_EN]	= &g12a_sys_pll_भाग16_en.hw,
		[CLKID_SYS_PLL_DIV16]		= &g12a_sys_pll_भाग16.hw,
		[CLKID_CPU_CLK_DYN0_SEL]	= &g12a_cpu_clk_premux0.hw,
		[CLKID_CPU_CLK_DYN0_DIV]	= &g12a_cpu_clk_mux0_भाग.hw,
		[CLKID_CPU_CLK_DYN0]		= &g12a_cpu_clk_posपंचांगux0.hw,
		[CLKID_CPU_CLK_DYN1_SEL]	= &g12a_cpu_clk_premux1.hw,
		[CLKID_CPU_CLK_DYN1_DIV]	= &g12a_cpu_clk_mux1_भाग.hw,
		[CLKID_CPU_CLK_DYN1]		= &g12a_cpu_clk_posपंचांगux1.hw,
		[CLKID_CPU_CLK_DYN]		= &g12a_cpu_clk_dyn.hw,
		[CLKID_CPU_CLK]			= &g12a_cpu_clk.hw,
		[CLKID_CPU_CLK_DIV16_EN]	= &g12a_cpu_clk_भाग16_en.hw,
		[CLKID_CPU_CLK_DIV16]		= &g12a_cpu_clk_भाग16.hw,
		[CLKID_CPU_CLK_APB_DIV]		= &g12a_cpu_clk_apb_भाग.hw,
		[CLKID_CPU_CLK_APB]		= &g12a_cpu_clk_apb.hw,
		[CLKID_CPU_CLK_ATB_DIV]		= &g12a_cpu_clk_atb_भाग.hw,
		[CLKID_CPU_CLK_ATB]		= &g12a_cpu_clk_atb.hw,
		[CLKID_CPU_CLK_AXI_DIV]		= &g12a_cpu_clk_axi_भाग.hw,
		[CLKID_CPU_CLK_AXI]		= &g12a_cpu_clk_axi.hw,
		[CLKID_CPU_CLK_TRACE_DIV]	= &g12a_cpu_clk_trace_भाग.hw,
		[CLKID_CPU_CLK_TRACE]		= &g12a_cpu_clk_trace.hw,
		[CLKID_PCIE_PLL_DCO]		= &g12a_pcie_pll_dco.hw,
		[CLKID_PCIE_PLL_DCO_DIV2]	= &g12a_pcie_pll_dco_भाग2.hw,
		[CLKID_PCIE_PLL_OD]		= &g12a_pcie_pll_od.hw,
		[CLKID_PCIE_PLL]		= &g12a_pcie_pll.hw,
		[CLKID_VDEC_1_SEL]		= &g12a_vdec_1_sel.hw,
		[CLKID_VDEC_1_DIV]		= &g12a_vdec_1_भाग.hw,
		[CLKID_VDEC_1]			= &g12a_vdec_1.hw,
		[CLKID_VDEC_HEVC_SEL]		= &g12a_vdec_hevc_sel.hw,
		[CLKID_VDEC_HEVC_DIV]		= &g12a_vdec_hevc_भाग.hw,
		[CLKID_VDEC_HEVC]		= &g12a_vdec_hevc.hw,
		[CLKID_VDEC_HEVCF_SEL]		= &g12a_vdec_hevcf_sel.hw,
		[CLKID_VDEC_HEVCF_DIV]		= &g12a_vdec_hevcf_भाग.hw,
		[CLKID_VDEC_HEVCF]		= &g12a_vdec_hevcf.hw,
		[CLKID_TS_DIV]			= &g12a_ts_भाग.hw,
		[CLKID_TS]			= &g12a_ts.hw,
		[CLKID_SPICC0_SCLK_SEL]		= &g12a_spicc0_sclk_sel.hw,
		[CLKID_SPICC0_SCLK_DIV]		= &g12a_spicc0_sclk_भाग.hw,
		[CLKID_SPICC0_SCLK]		= &g12a_spicc0_sclk.hw,
		[CLKID_SPICC1_SCLK_SEL]		= &g12a_spicc1_sclk_sel.hw,
		[CLKID_SPICC1_SCLK_DIV]		= &g12a_spicc1_sclk_भाग.hw,
		[CLKID_SPICC1_SCLK]		= &g12a_spicc1_sclk.hw,
		[CLKID_MIPI_DSI_PXCLK_SEL]	= &g12a_mipi_dsi_pxclk_sel.hw,
		[CLKID_MIPI_DSI_PXCLK_DIV]	= &g12a_mipi_dsi_pxclk_भाग.hw,
		[CLKID_MIPI_DSI_PXCLK]		= &g12a_mipi_dsi_pxclk.hw,
		[NR_CLKS]			= शून्य,
	पूर्ण,
	.num = NR_CLKS,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data g12b_hw_onecell_data = अणु
	.hws = अणु
		[CLKID_SYS_PLL]			= &g12a_sys_pll.hw,
		[CLKID_FIXED_PLL]		= &g12a_fixed_pll.hw,
		[CLKID_FCLK_DIV2]		= &g12a_fclk_भाग2.hw,
		[CLKID_FCLK_DIV3]		= &g12a_fclk_भाग3.hw,
		[CLKID_FCLK_DIV4]		= &g12a_fclk_भाग4.hw,
		[CLKID_FCLK_DIV5]		= &g12a_fclk_भाग5.hw,
		[CLKID_FCLK_DIV7]		= &g12a_fclk_भाग7.hw,
		[CLKID_FCLK_DIV2P5]		= &g12a_fclk_भाग2p5.hw,
		[CLKID_GP0_PLL]			= &g12a_gp0_pll.hw,
		[CLKID_MPEG_SEL]		= &g12a_mpeg_clk_sel.hw,
		[CLKID_MPEG_DIV]		= &g12a_mpeg_clk_भाग.hw,
		[CLKID_CLK81]			= &g12a_clk81.hw,
		[CLKID_MPLL0]			= &g12a_mpll0.hw,
		[CLKID_MPLL1]			= &g12a_mpll1.hw,
		[CLKID_MPLL2]			= &g12a_mpll2.hw,
		[CLKID_MPLL3]			= &g12a_mpll3.hw,
		[CLKID_DDR]			= &g12a_ddr.hw,
		[CLKID_DOS]			= &g12a_डॉस.सw,
		[CLKID_AUDIO_LOCKER]		= &g12a_audio_locker.hw,
		[CLKID_MIPI_DSI_HOST]		= &g12a_mipi_dsi_host.hw,
		[CLKID_ETH_PHY]			= &g12a_eth_phy.hw,
		[CLKID_ISA]			= &g12a_isa.hw,
		[CLKID_PL301]			= &g12a_pl301.hw,
		[CLKID_PERIPHS]			= &g12a_periphs.hw,
		[CLKID_SPICC0]			= &g12a_spicc_0.hw,
		[CLKID_I2C]			= &g12a_i2c.hw,
		[CLKID_SANA]			= &g12a_sana.hw,
		[CLKID_SD]			= &g12a_sd.hw,
		[CLKID_RNG0]			= &g12a_rng0.hw,
		[CLKID_UART0]			= &g12a_uart0.hw,
		[CLKID_SPICC1]			= &g12a_spicc_1.hw,
		[CLKID_HIU_IFACE]		= &g12a_hiu_reg.hw,
		[CLKID_MIPI_DSI_PHY]		= &g12a_mipi_dsi_phy.hw,
		[CLKID_ASSIST_MISC]		= &g12a_assist_misc.hw,
		[CLKID_SD_EMMC_A]		= &g12a_emmc_a.hw,
		[CLKID_SD_EMMC_B]		= &g12a_emmc_b.hw,
		[CLKID_SD_EMMC_C]		= &g12a_emmc_c.hw,
		[CLKID_AUDIO_CODEC]		= &g12a_audio_codec.hw,
		[CLKID_AUDIO]			= &g12a_audपन.सw,
		[CLKID_ETH]			= &g12a_eth_core.hw,
		[CLKID_DEMUX]			= &g12a_demux.hw,
		[CLKID_AUDIO_IFIFO]		= &g12a_audio_अगरअगरo.hw,
		[CLKID_ADC]			= &g12a_adc.hw,
		[CLKID_UART1]			= &g12a_uart1.hw,
		[CLKID_G2D]			= &g12a_g2d.hw,
		[CLKID_RESET]			= &g12a_reset.hw,
		[CLKID_PCIE_COMB]		= &g12a_pcie_comb.hw,
		[CLKID_PARSER]			= &g12a_parser.hw,
		[CLKID_USB]			= &g12a_usb_general.hw,
		[CLKID_PCIE_PHY]		= &g12a_pcie_phy.hw,
		[CLKID_AHB_ARB0]		= &g12a_ahb_arb0.hw,
		[CLKID_AHB_DATA_BUS]		= &g12a_ahb_data_bus.hw,
		[CLKID_AHB_CTRL_BUS]		= &g12a_ahb_ctrl_bus.hw,
		[CLKID_HTX_HDCP22]		= &g12a_htx_hdcp22.hw,
		[CLKID_HTX_PCLK]		= &g12a_htx_pclk.hw,
		[CLKID_BT656]			= &g12a_bt656.hw,
		[CLKID_USB1_DDR_BRIDGE]		= &g12a_usb1_to_ddr.hw,
		[CLKID_MMC_PCLK]		= &g12a_mmc_pclk.hw,
		[CLKID_UART2]			= &g12a_uart2.hw,
		[CLKID_VPU_INTR]		= &g12a_vpu_पूर्णांकr.hw,
		[CLKID_GIC]			= &g12a_gic.hw,
		[CLKID_SD_EMMC_A_CLK0_SEL]	= &g12a_sd_emmc_a_clk0_sel.hw,
		[CLKID_SD_EMMC_A_CLK0_DIV]	= &g12a_sd_emmc_a_clk0_भाग.hw,
		[CLKID_SD_EMMC_A_CLK0]		= &g12a_sd_emmc_a_clk0.hw,
		[CLKID_SD_EMMC_B_CLK0_SEL]	= &g12a_sd_emmc_b_clk0_sel.hw,
		[CLKID_SD_EMMC_B_CLK0_DIV]	= &g12a_sd_emmc_b_clk0_भाग.hw,
		[CLKID_SD_EMMC_B_CLK0]		= &g12a_sd_emmc_b_clk0.hw,
		[CLKID_SD_EMMC_C_CLK0_SEL]	= &g12a_sd_emmc_c_clk0_sel.hw,
		[CLKID_SD_EMMC_C_CLK0_DIV]	= &g12a_sd_emmc_c_clk0_भाग.hw,
		[CLKID_SD_EMMC_C_CLK0]		= &g12a_sd_emmc_c_clk0.hw,
		[CLKID_MPLL0_DIV]		= &g12a_mpll0_भाग.hw,
		[CLKID_MPLL1_DIV]		= &g12a_mpll1_भाग.hw,
		[CLKID_MPLL2_DIV]		= &g12a_mpll2_भाग.hw,
		[CLKID_MPLL3_DIV]		= &g12a_mpll3_भाग.hw,
		[CLKID_FCLK_DIV2_DIV]		= &g12a_fclk_भाग2_भाग.hw,
		[CLKID_FCLK_DIV3_DIV]		= &g12a_fclk_भाग3_भाग.hw,
		[CLKID_FCLK_DIV4_DIV]		= &g12a_fclk_भाग4_भाग.hw,
		[CLKID_FCLK_DIV5_DIV]		= &g12a_fclk_भाग5_भाग.hw,
		[CLKID_FCLK_DIV7_DIV]		= &g12a_fclk_भाग7_भाग.hw,
		[CLKID_FCLK_DIV2P5_DIV]		= &g12a_fclk_भाग2p5_भाग.hw,
		[CLKID_HIFI_PLL]		= &g12a_hअगरi_pll.hw,
		[CLKID_VCLK2_VENCI0]		= &g12a_vclk2_venci0.hw,
		[CLKID_VCLK2_VENCI1]		= &g12a_vclk2_venci1.hw,
		[CLKID_VCLK2_VENCP0]		= &g12a_vclk2_vencp0.hw,
		[CLKID_VCLK2_VENCP1]		= &g12a_vclk2_vencp1.hw,
		[CLKID_VCLK2_VENCT0]		= &g12a_vclk2_venct0.hw,
		[CLKID_VCLK2_VENCT1]		= &g12a_vclk2_venct1.hw,
		[CLKID_VCLK2_OTHER]		= &g12a_vclk2_other.hw,
		[CLKID_VCLK2_ENCI]		= &g12a_vclk2_enci.hw,
		[CLKID_VCLK2_ENCP]		= &g12a_vclk2_encp.hw,
		[CLKID_DAC_CLK]			= &g12a_dac_clk.hw,
		[CLKID_AOCLK]			= &g12a_aoclk_gate.hw,
		[CLKID_IEC958]			= &g12a_iec958_gate.hw,
		[CLKID_ENC480P]			= &g12a_enc480p.hw,
		[CLKID_RNG1]			= &g12a_rng1.hw,
		[CLKID_VCLK2_ENCT]		= &g12a_vclk2_enct.hw,
		[CLKID_VCLK2_ENCL]		= &g12a_vclk2_encl.hw,
		[CLKID_VCLK2_VENCLMMC]		= &g12a_vclk2_venclmmc.hw,
		[CLKID_VCLK2_VENCL]		= &g12a_vclk2_vencl.hw,
		[CLKID_VCLK2_OTHER1]		= &g12a_vclk2_other1.hw,
		[CLKID_FIXED_PLL_DCO]		= &g12a_fixed_pll_dco.hw,
		[CLKID_SYS_PLL_DCO]		= &g12a_sys_pll_dco.hw,
		[CLKID_GP0_PLL_DCO]		= &g12a_gp0_pll_dco.hw,
		[CLKID_HIFI_PLL_DCO]		= &g12a_hअगरi_pll_dco.hw,
		[CLKID_DMA]			= &g12a_dma.hw,
		[CLKID_EFUSE]			= &g12a_efuse.hw,
		[CLKID_ROM_BOOT]		= &g12a_rom_boot.hw,
		[CLKID_RESET_SEC]		= &g12a_reset_sec.hw,
		[CLKID_SEC_AHB_APB3]		= &g12a_sec_ahb_apb3.hw,
		[CLKID_MPLL_PREDIV]		= &g12a_mpll_preभाग.hw,
		[CLKID_VPU_0_SEL]		= &g12a_vpu_0_sel.hw,
		[CLKID_VPU_0_DIV]		= &g12a_vpu_0_भाग.hw,
		[CLKID_VPU_0]			= &g12a_vpu_0.hw,
		[CLKID_VPU_1_SEL]		= &g12a_vpu_1_sel.hw,
		[CLKID_VPU_1_DIV]		= &g12a_vpu_1_भाग.hw,
		[CLKID_VPU_1]			= &g12a_vpu_1.hw,
		[CLKID_VPU]			= &g12a_vpu.hw,
		[CLKID_VAPB_0_SEL]		= &g12a_vapb_0_sel.hw,
		[CLKID_VAPB_0_DIV]		= &g12a_vapb_0_भाग.hw,
		[CLKID_VAPB_0]			= &g12a_vapb_0.hw,
		[CLKID_VAPB_1_SEL]		= &g12a_vapb_1_sel.hw,
		[CLKID_VAPB_1_DIV]		= &g12a_vapb_1_भाग.hw,
		[CLKID_VAPB_1]			= &g12a_vapb_1.hw,
		[CLKID_VAPB_SEL]		= &g12a_vapb_sel.hw,
		[CLKID_VAPB]			= &g12a_vapb.hw,
		[CLKID_HDMI_PLL_DCO]		= &g12a_hdmi_pll_dco.hw,
		[CLKID_HDMI_PLL_OD]		= &g12a_hdmi_pll_od.hw,
		[CLKID_HDMI_PLL_OD2]		= &g12a_hdmi_pll_od2.hw,
		[CLKID_HDMI_PLL]		= &g12a_hdmi_pll.hw,
		[CLKID_VID_PLL]			= &g12a_vid_pll_भाग.hw,
		[CLKID_VID_PLL_SEL]		= &g12a_vid_pll_sel.hw,
		[CLKID_VID_PLL_DIV]		= &g12a_vid_pll.hw,
		[CLKID_VCLK_SEL]		= &g12a_vclk_sel.hw,
		[CLKID_VCLK2_SEL]		= &g12a_vclk2_sel.hw,
		[CLKID_VCLK_INPUT]		= &g12a_vclk_input.hw,
		[CLKID_VCLK2_INPUT]		= &g12a_vclk2_input.hw,
		[CLKID_VCLK_DIV]		= &g12a_vclk_भाग.hw,
		[CLKID_VCLK2_DIV]		= &g12a_vclk2_भाग.hw,
		[CLKID_VCLK]			= &g12a_vclk.hw,
		[CLKID_VCLK2]			= &g12a_vclk2.hw,
		[CLKID_VCLK_DIV1]		= &g12a_vclk_भाग1.hw,
		[CLKID_VCLK_DIV2_EN]		= &g12a_vclk_भाग2_en.hw,
		[CLKID_VCLK_DIV4_EN]		= &g12a_vclk_भाग4_en.hw,
		[CLKID_VCLK_DIV6_EN]		= &g12a_vclk_भाग6_en.hw,
		[CLKID_VCLK_DIV12_EN]		= &g12a_vclk_भाग12_en.hw,
		[CLKID_VCLK2_DIV1]		= &g12a_vclk2_भाग1.hw,
		[CLKID_VCLK2_DIV2_EN]		= &g12a_vclk2_भाग2_en.hw,
		[CLKID_VCLK2_DIV4_EN]		= &g12a_vclk2_भाग4_en.hw,
		[CLKID_VCLK2_DIV6_EN]		= &g12a_vclk2_भाग6_en.hw,
		[CLKID_VCLK2_DIV12_EN]		= &g12a_vclk2_भाग12_en.hw,
		[CLKID_VCLK_DIV2]		= &g12a_vclk_भाग2.hw,
		[CLKID_VCLK_DIV4]		= &g12a_vclk_भाग4.hw,
		[CLKID_VCLK_DIV6]		= &g12a_vclk_भाग6.hw,
		[CLKID_VCLK_DIV12]		= &g12a_vclk_भाग12.hw,
		[CLKID_VCLK2_DIV2]		= &g12a_vclk2_भाग2.hw,
		[CLKID_VCLK2_DIV4]		= &g12a_vclk2_भाग4.hw,
		[CLKID_VCLK2_DIV6]		= &g12a_vclk2_भाग6.hw,
		[CLKID_VCLK2_DIV12]		= &g12a_vclk2_भाग12.hw,
		[CLKID_CTS_ENCI_SEL]		= &g12a_cts_enci_sel.hw,
		[CLKID_CTS_ENCP_SEL]		= &g12a_cts_encp_sel.hw,
		[CLKID_CTS_VDAC_SEL]		= &g12a_cts_vdac_sel.hw,
		[CLKID_HDMI_TX_SEL]		= &g12a_hdmi_tx_sel.hw,
		[CLKID_CTS_ENCI]		= &g12a_cts_enci.hw,
		[CLKID_CTS_ENCP]		= &g12a_cts_encp.hw,
		[CLKID_CTS_VDAC]		= &g12a_cts_vdac.hw,
		[CLKID_HDMI_TX]			= &g12a_hdmi_tx.hw,
		[CLKID_HDMI_SEL]		= &g12a_hdmi_sel.hw,
		[CLKID_HDMI_DIV]		= &g12a_hdmi_भाग.hw,
		[CLKID_HDMI]			= &g12a_hdmi.hw,
		[CLKID_MALI_0_SEL]		= &g12a_mali_0_sel.hw,
		[CLKID_MALI_0_DIV]		= &g12a_mali_0_भाग.hw,
		[CLKID_MALI_0]			= &g12a_mali_0.hw,
		[CLKID_MALI_1_SEL]		= &g12a_mali_1_sel.hw,
		[CLKID_MALI_1_DIV]		= &g12a_mali_1_भाग.hw,
		[CLKID_MALI_1]			= &g12a_mali_1.hw,
		[CLKID_MALI]			= &g12a_mali.hw,
		[CLKID_MPLL_50M_DIV]		= &g12a_mpll_50m_भाग.hw,
		[CLKID_MPLL_50M]		= &g12a_mpll_50m.hw,
		[CLKID_SYS_PLL_DIV16_EN]	= &g12a_sys_pll_भाग16_en.hw,
		[CLKID_SYS_PLL_DIV16]		= &g12a_sys_pll_भाग16.hw,
		[CLKID_CPU_CLK_DYN0_SEL]	= &g12a_cpu_clk_premux0.hw,
		[CLKID_CPU_CLK_DYN0_DIV]	= &g12a_cpu_clk_mux0_भाग.hw,
		[CLKID_CPU_CLK_DYN0]		= &g12a_cpu_clk_posपंचांगux0.hw,
		[CLKID_CPU_CLK_DYN1_SEL]	= &g12a_cpu_clk_premux1.hw,
		[CLKID_CPU_CLK_DYN1_DIV]	= &g12a_cpu_clk_mux1_भाग.hw,
		[CLKID_CPU_CLK_DYN1]		= &g12a_cpu_clk_posपंचांगux1.hw,
		[CLKID_CPU_CLK_DYN]		= &g12a_cpu_clk_dyn.hw,
		[CLKID_CPU_CLK]			= &g12b_cpu_clk.hw,
		[CLKID_CPU_CLK_DIV16_EN]	= &g12a_cpu_clk_भाग16_en.hw,
		[CLKID_CPU_CLK_DIV16]		= &g12a_cpu_clk_भाग16.hw,
		[CLKID_CPU_CLK_APB_DIV]		= &g12a_cpu_clk_apb_भाग.hw,
		[CLKID_CPU_CLK_APB]		= &g12a_cpu_clk_apb.hw,
		[CLKID_CPU_CLK_ATB_DIV]		= &g12a_cpu_clk_atb_भाग.hw,
		[CLKID_CPU_CLK_ATB]		= &g12a_cpu_clk_atb.hw,
		[CLKID_CPU_CLK_AXI_DIV]		= &g12a_cpu_clk_axi_भाग.hw,
		[CLKID_CPU_CLK_AXI]		= &g12a_cpu_clk_axi.hw,
		[CLKID_CPU_CLK_TRACE_DIV]	= &g12a_cpu_clk_trace_भाग.hw,
		[CLKID_CPU_CLK_TRACE]		= &g12a_cpu_clk_trace.hw,
		[CLKID_PCIE_PLL_DCO]		= &g12a_pcie_pll_dco.hw,
		[CLKID_PCIE_PLL_DCO_DIV2]	= &g12a_pcie_pll_dco_भाग2.hw,
		[CLKID_PCIE_PLL_OD]		= &g12a_pcie_pll_od.hw,
		[CLKID_PCIE_PLL]		= &g12a_pcie_pll.hw,
		[CLKID_VDEC_1_SEL]		= &g12a_vdec_1_sel.hw,
		[CLKID_VDEC_1_DIV]		= &g12a_vdec_1_भाग.hw,
		[CLKID_VDEC_1]			= &g12a_vdec_1.hw,
		[CLKID_VDEC_HEVC_SEL]		= &g12a_vdec_hevc_sel.hw,
		[CLKID_VDEC_HEVC_DIV]		= &g12a_vdec_hevc_भाग.hw,
		[CLKID_VDEC_HEVC]		= &g12a_vdec_hevc.hw,
		[CLKID_VDEC_HEVCF_SEL]		= &g12a_vdec_hevcf_sel.hw,
		[CLKID_VDEC_HEVCF_DIV]		= &g12a_vdec_hevcf_भाग.hw,
		[CLKID_VDEC_HEVCF]		= &g12a_vdec_hevcf.hw,
		[CLKID_TS_DIV]			= &g12a_ts_भाग.hw,
		[CLKID_TS]			= &g12a_ts.hw,
		[CLKID_SYS1_PLL_DCO]		= &g12b_sys1_pll_dco.hw,
		[CLKID_SYS1_PLL]		= &g12b_sys1_pll.hw,
		[CLKID_SYS1_PLL_DIV16_EN]	= &g12b_sys1_pll_भाग16_en.hw,
		[CLKID_SYS1_PLL_DIV16]		= &g12b_sys1_pll_भाग16.hw,
		[CLKID_CPUB_CLK_DYN0_SEL]	= &g12b_cpub_clk_premux0.hw,
		[CLKID_CPUB_CLK_DYN0_DIV]	= &g12b_cpub_clk_mux0_भाग.hw,
		[CLKID_CPUB_CLK_DYN0]		= &g12b_cpub_clk_posपंचांगux0.hw,
		[CLKID_CPUB_CLK_DYN1_SEL]	= &g12b_cpub_clk_premux1.hw,
		[CLKID_CPUB_CLK_DYN1_DIV]	= &g12b_cpub_clk_mux1_भाग.hw,
		[CLKID_CPUB_CLK_DYN1]		= &g12b_cpub_clk_posपंचांगux1.hw,
		[CLKID_CPUB_CLK_DYN]		= &g12b_cpub_clk_dyn.hw,
		[CLKID_CPUB_CLK]		= &g12b_cpub_clk.hw,
		[CLKID_CPUB_CLK_DIV16_EN]	= &g12b_cpub_clk_भाग16_en.hw,
		[CLKID_CPUB_CLK_DIV16]		= &g12b_cpub_clk_भाग16.hw,
		[CLKID_CPUB_CLK_DIV2]		= &g12b_cpub_clk_भाग2.hw,
		[CLKID_CPUB_CLK_DIV3]		= &g12b_cpub_clk_भाग3.hw,
		[CLKID_CPUB_CLK_DIV4]		= &g12b_cpub_clk_भाग4.hw,
		[CLKID_CPUB_CLK_DIV5]		= &g12b_cpub_clk_भाग5.hw,
		[CLKID_CPUB_CLK_DIV6]		= &g12b_cpub_clk_भाग6.hw,
		[CLKID_CPUB_CLK_DIV7]		= &g12b_cpub_clk_भाग7.hw,
		[CLKID_CPUB_CLK_DIV8]		= &g12b_cpub_clk_भाग8.hw,
		[CLKID_CPUB_CLK_APB_SEL]	= &g12b_cpub_clk_apb_sel.hw,
		[CLKID_CPUB_CLK_APB]		= &g12b_cpub_clk_apb.hw,
		[CLKID_CPUB_CLK_ATB_SEL]	= &g12b_cpub_clk_atb_sel.hw,
		[CLKID_CPUB_CLK_ATB]		= &g12b_cpub_clk_atb.hw,
		[CLKID_CPUB_CLK_AXI_SEL]	= &g12b_cpub_clk_axi_sel.hw,
		[CLKID_CPUB_CLK_AXI]		= &g12b_cpub_clk_axi.hw,
		[CLKID_CPUB_CLK_TRACE_SEL]	= &g12b_cpub_clk_trace_sel.hw,
		[CLKID_CPUB_CLK_TRACE]		= &g12b_cpub_clk_trace.hw,
		[CLKID_SPICC0_SCLK_SEL]		= &g12a_spicc0_sclk_sel.hw,
		[CLKID_SPICC0_SCLK_DIV]		= &g12a_spicc0_sclk_भाग.hw,
		[CLKID_SPICC0_SCLK]		= &g12a_spicc0_sclk.hw,
		[CLKID_SPICC1_SCLK_SEL]		= &g12a_spicc1_sclk_sel.hw,
		[CLKID_SPICC1_SCLK_DIV]		= &g12a_spicc1_sclk_भाग.hw,
		[CLKID_SPICC1_SCLK]		= &g12a_spicc1_sclk.hw,
		[CLKID_MIPI_DSI_PXCLK_SEL]	= &g12a_mipi_dsi_pxclk_sel.hw,
		[CLKID_MIPI_DSI_PXCLK_DIV]	= &g12a_mipi_dsi_pxclk_भाग.hw,
		[CLKID_MIPI_DSI_PXCLK]		= &g12a_mipi_dsi_pxclk.hw,
		[NR_CLKS]			= शून्य,
	पूर्ण,
	.num = NR_CLKS,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sm1_hw_onecell_data = अणु
	.hws = अणु
		[CLKID_SYS_PLL]			= &g12a_sys_pll.hw,
		[CLKID_FIXED_PLL]		= &g12a_fixed_pll.hw,
		[CLKID_FCLK_DIV2]		= &g12a_fclk_भाग2.hw,
		[CLKID_FCLK_DIV3]		= &g12a_fclk_भाग3.hw,
		[CLKID_FCLK_DIV4]		= &g12a_fclk_भाग4.hw,
		[CLKID_FCLK_DIV5]		= &g12a_fclk_भाग5.hw,
		[CLKID_FCLK_DIV7]		= &g12a_fclk_भाग7.hw,
		[CLKID_FCLK_DIV2P5]		= &g12a_fclk_भाग2p5.hw,
		[CLKID_GP0_PLL]			= &g12a_gp0_pll.hw,
		[CLKID_MPEG_SEL]		= &g12a_mpeg_clk_sel.hw,
		[CLKID_MPEG_DIV]		= &g12a_mpeg_clk_भाग.hw,
		[CLKID_CLK81]			= &g12a_clk81.hw,
		[CLKID_MPLL0]			= &g12a_mpll0.hw,
		[CLKID_MPLL1]			= &g12a_mpll1.hw,
		[CLKID_MPLL2]			= &g12a_mpll2.hw,
		[CLKID_MPLL3]			= &g12a_mpll3.hw,
		[CLKID_DDR]			= &g12a_ddr.hw,
		[CLKID_DOS]			= &g12a_डॉस.सw,
		[CLKID_AUDIO_LOCKER]		= &g12a_audio_locker.hw,
		[CLKID_MIPI_DSI_HOST]		= &g12a_mipi_dsi_host.hw,
		[CLKID_ETH_PHY]			= &g12a_eth_phy.hw,
		[CLKID_ISA]			= &g12a_isa.hw,
		[CLKID_PL301]			= &g12a_pl301.hw,
		[CLKID_PERIPHS]			= &g12a_periphs.hw,
		[CLKID_SPICC0]			= &g12a_spicc_0.hw,
		[CLKID_I2C]			= &g12a_i2c.hw,
		[CLKID_SANA]			= &g12a_sana.hw,
		[CLKID_SD]			= &g12a_sd.hw,
		[CLKID_RNG0]			= &g12a_rng0.hw,
		[CLKID_UART0]			= &g12a_uart0.hw,
		[CLKID_SPICC1]			= &g12a_spicc_1.hw,
		[CLKID_HIU_IFACE]		= &g12a_hiu_reg.hw,
		[CLKID_MIPI_DSI_PHY]		= &g12a_mipi_dsi_phy.hw,
		[CLKID_ASSIST_MISC]		= &g12a_assist_misc.hw,
		[CLKID_SD_EMMC_A]		= &g12a_emmc_a.hw,
		[CLKID_SD_EMMC_B]		= &g12a_emmc_b.hw,
		[CLKID_SD_EMMC_C]		= &g12a_emmc_c.hw,
		[CLKID_AUDIO_CODEC]		= &g12a_audio_codec.hw,
		[CLKID_AUDIO]			= &g12a_audपन.सw,
		[CLKID_ETH]			= &g12a_eth_core.hw,
		[CLKID_DEMUX]			= &g12a_demux.hw,
		[CLKID_AUDIO_IFIFO]		= &g12a_audio_अगरअगरo.hw,
		[CLKID_ADC]			= &g12a_adc.hw,
		[CLKID_UART1]			= &g12a_uart1.hw,
		[CLKID_G2D]			= &g12a_g2d.hw,
		[CLKID_RESET]			= &g12a_reset.hw,
		[CLKID_PCIE_COMB]		= &g12a_pcie_comb.hw,
		[CLKID_PARSER]			= &g12a_parser.hw,
		[CLKID_USB]			= &g12a_usb_general.hw,
		[CLKID_PCIE_PHY]		= &g12a_pcie_phy.hw,
		[CLKID_AHB_ARB0]		= &g12a_ahb_arb0.hw,
		[CLKID_AHB_DATA_BUS]		= &g12a_ahb_data_bus.hw,
		[CLKID_AHB_CTRL_BUS]		= &g12a_ahb_ctrl_bus.hw,
		[CLKID_HTX_HDCP22]		= &g12a_htx_hdcp22.hw,
		[CLKID_HTX_PCLK]		= &g12a_htx_pclk.hw,
		[CLKID_BT656]			= &g12a_bt656.hw,
		[CLKID_USB1_DDR_BRIDGE]		= &g12a_usb1_to_ddr.hw,
		[CLKID_MMC_PCLK]		= &g12a_mmc_pclk.hw,
		[CLKID_UART2]			= &g12a_uart2.hw,
		[CLKID_VPU_INTR]		= &g12a_vpu_पूर्णांकr.hw,
		[CLKID_GIC]			= &g12a_gic.hw,
		[CLKID_SD_EMMC_A_CLK0_SEL]	= &g12a_sd_emmc_a_clk0_sel.hw,
		[CLKID_SD_EMMC_A_CLK0_DIV]	= &g12a_sd_emmc_a_clk0_भाग.hw,
		[CLKID_SD_EMMC_A_CLK0]		= &g12a_sd_emmc_a_clk0.hw,
		[CLKID_SD_EMMC_B_CLK0_SEL]	= &g12a_sd_emmc_b_clk0_sel.hw,
		[CLKID_SD_EMMC_B_CLK0_DIV]	= &g12a_sd_emmc_b_clk0_भाग.hw,
		[CLKID_SD_EMMC_B_CLK0]		= &g12a_sd_emmc_b_clk0.hw,
		[CLKID_SD_EMMC_C_CLK0_SEL]	= &g12a_sd_emmc_c_clk0_sel.hw,
		[CLKID_SD_EMMC_C_CLK0_DIV]	= &g12a_sd_emmc_c_clk0_भाग.hw,
		[CLKID_SD_EMMC_C_CLK0]		= &g12a_sd_emmc_c_clk0.hw,
		[CLKID_MPLL0_DIV]		= &g12a_mpll0_भाग.hw,
		[CLKID_MPLL1_DIV]		= &g12a_mpll1_भाग.hw,
		[CLKID_MPLL2_DIV]		= &g12a_mpll2_भाग.hw,
		[CLKID_MPLL3_DIV]		= &g12a_mpll3_भाग.hw,
		[CLKID_FCLK_DIV2_DIV]		= &g12a_fclk_भाग2_भाग.hw,
		[CLKID_FCLK_DIV3_DIV]		= &g12a_fclk_भाग3_भाग.hw,
		[CLKID_FCLK_DIV4_DIV]		= &g12a_fclk_भाग4_भाग.hw,
		[CLKID_FCLK_DIV5_DIV]		= &g12a_fclk_भाग5_भाग.hw,
		[CLKID_FCLK_DIV7_DIV]		= &g12a_fclk_भाग7_भाग.hw,
		[CLKID_FCLK_DIV2P5_DIV]		= &g12a_fclk_भाग2p5_भाग.hw,
		[CLKID_HIFI_PLL]		= &g12a_hअगरi_pll.hw,
		[CLKID_VCLK2_VENCI0]		= &g12a_vclk2_venci0.hw,
		[CLKID_VCLK2_VENCI1]		= &g12a_vclk2_venci1.hw,
		[CLKID_VCLK2_VENCP0]		= &g12a_vclk2_vencp0.hw,
		[CLKID_VCLK2_VENCP1]		= &g12a_vclk2_vencp1.hw,
		[CLKID_VCLK2_VENCT0]		= &g12a_vclk2_venct0.hw,
		[CLKID_VCLK2_VENCT1]		= &g12a_vclk2_venct1.hw,
		[CLKID_VCLK2_OTHER]		= &g12a_vclk2_other.hw,
		[CLKID_VCLK2_ENCI]		= &g12a_vclk2_enci.hw,
		[CLKID_VCLK2_ENCP]		= &g12a_vclk2_encp.hw,
		[CLKID_DAC_CLK]			= &g12a_dac_clk.hw,
		[CLKID_AOCLK]			= &g12a_aoclk_gate.hw,
		[CLKID_IEC958]			= &g12a_iec958_gate.hw,
		[CLKID_ENC480P]			= &g12a_enc480p.hw,
		[CLKID_RNG1]			= &g12a_rng1.hw,
		[CLKID_VCLK2_ENCT]		= &g12a_vclk2_enct.hw,
		[CLKID_VCLK2_ENCL]		= &g12a_vclk2_encl.hw,
		[CLKID_VCLK2_VENCLMMC]		= &g12a_vclk2_venclmmc.hw,
		[CLKID_VCLK2_VENCL]		= &g12a_vclk2_vencl.hw,
		[CLKID_VCLK2_OTHER1]		= &g12a_vclk2_other1.hw,
		[CLKID_FIXED_PLL_DCO]		= &g12a_fixed_pll_dco.hw,
		[CLKID_SYS_PLL_DCO]		= &g12a_sys_pll_dco.hw,
		[CLKID_GP0_PLL_DCO]		= &g12a_gp0_pll_dco.hw,
		[CLKID_HIFI_PLL_DCO]		= &g12a_hअगरi_pll_dco.hw,
		[CLKID_DMA]			= &g12a_dma.hw,
		[CLKID_EFUSE]			= &g12a_efuse.hw,
		[CLKID_ROM_BOOT]		= &g12a_rom_boot.hw,
		[CLKID_RESET_SEC]		= &g12a_reset_sec.hw,
		[CLKID_SEC_AHB_APB3]		= &g12a_sec_ahb_apb3.hw,
		[CLKID_MPLL_PREDIV]		= &g12a_mpll_preभाग.hw,
		[CLKID_VPU_0_SEL]		= &g12a_vpu_0_sel.hw,
		[CLKID_VPU_0_DIV]		= &g12a_vpu_0_भाग.hw,
		[CLKID_VPU_0]			= &g12a_vpu_0.hw,
		[CLKID_VPU_1_SEL]		= &g12a_vpu_1_sel.hw,
		[CLKID_VPU_1_DIV]		= &g12a_vpu_1_भाग.hw,
		[CLKID_VPU_1]			= &g12a_vpu_1.hw,
		[CLKID_VPU]			= &g12a_vpu.hw,
		[CLKID_VAPB_0_SEL]		= &g12a_vapb_0_sel.hw,
		[CLKID_VAPB_0_DIV]		= &g12a_vapb_0_भाग.hw,
		[CLKID_VAPB_0]			= &g12a_vapb_0.hw,
		[CLKID_VAPB_1_SEL]		= &g12a_vapb_1_sel.hw,
		[CLKID_VAPB_1_DIV]		= &g12a_vapb_1_भाग.hw,
		[CLKID_VAPB_1]			= &g12a_vapb_1.hw,
		[CLKID_VAPB_SEL]		= &g12a_vapb_sel.hw,
		[CLKID_VAPB]			= &g12a_vapb.hw,
		[CLKID_HDMI_PLL_DCO]		= &g12a_hdmi_pll_dco.hw,
		[CLKID_HDMI_PLL_OD]		= &g12a_hdmi_pll_od.hw,
		[CLKID_HDMI_PLL_OD2]		= &g12a_hdmi_pll_od2.hw,
		[CLKID_HDMI_PLL]		= &g12a_hdmi_pll.hw,
		[CLKID_VID_PLL]			= &g12a_vid_pll_भाग.hw,
		[CLKID_VID_PLL_SEL]		= &g12a_vid_pll_sel.hw,
		[CLKID_VID_PLL_DIV]		= &g12a_vid_pll.hw,
		[CLKID_VCLK_SEL]		= &g12a_vclk_sel.hw,
		[CLKID_VCLK2_SEL]		= &g12a_vclk2_sel.hw,
		[CLKID_VCLK_INPUT]		= &g12a_vclk_input.hw,
		[CLKID_VCLK2_INPUT]		= &g12a_vclk2_input.hw,
		[CLKID_VCLK_DIV]		= &g12a_vclk_भाग.hw,
		[CLKID_VCLK2_DIV]		= &g12a_vclk2_भाग.hw,
		[CLKID_VCLK]			= &g12a_vclk.hw,
		[CLKID_VCLK2]			= &g12a_vclk2.hw,
		[CLKID_VCLK_DIV1]		= &g12a_vclk_भाग1.hw,
		[CLKID_VCLK_DIV2_EN]		= &g12a_vclk_भाग2_en.hw,
		[CLKID_VCLK_DIV4_EN]		= &g12a_vclk_भाग4_en.hw,
		[CLKID_VCLK_DIV6_EN]		= &g12a_vclk_भाग6_en.hw,
		[CLKID_VCLK_DIV12_EN]		= &g12a_vclk_भाग12_en.hw,
		[CLKID_VCLK2_DIV1]		= &g12a_vclk2_भाग1.hw,
		[CLKID_VCLK2_DIV2_EN]		= &g12a_vclk2_भाग2_en.hw,
		[CLKID_VCLK2_DIV4_EN]		= &g12a_vclk2_भाग4_en.hw,
		[CLKID_VCLK2_DIV6_EN]		= &g12a_vclk2_भाग6_en.hw,
		[CLKID_VCLK2_DIV12_EN]		= &g12a_vclk2_भाग12_en.hw,
		[CLKID_VCLK_DIV2]		= &g12a_vclk_भाग2.hw,
		[CLKID_VCLK_DIV4]		= &g12a_vclk_भाग4.hw,
		[CLKID_VCLK_DIV6]		= &g12a_vclk_भाग6.hw,
		[CLKID_VCLK_DIV12]		= &g12a_vclk_भाग12.hw,
		[CLKID_VCLK2_DIV2]		= &g12a_vclk2_भाग2.hw,
		[CLKID_VCLK2_DIV4]		= &g12a_vclk2_भाग4.hw,
		[CLKID_VCLK2_DIV6]		= &g12a_vclk2_भाग6.hw,
		[CLKID_VCLK2_DIV12]		= &g12a_vclk2_भाग12.hw,
		[CLKID_CTS_ENCI_SEL]		= &g12a_cts_enci_sel.hw,
		[CLKID_CTS_ENCP_SEL]		= &g12a_cts_encp_sel.hw,
		[CLKID_CTS_VDAC_SEL]		= &g12a_cts_vdac_sel.hw,
		[CLKID_HDMI_TX_SEL]		= &g12a_hdmi_tx_sel.hw,
		[CLKID_CTS_ENCI]		= &g12a_cts_enci.hw,
		[CLKID_CTS_ENCP]		= &g12a_cts_encp.hw,
		[CLKID_CTS_VDAC]		= &g12a_cts_vdac.hw,
		[CLKID_HDMI_TX]			= &g12a_hdmi_tx.hw,
		[CLKID_HDMI_SEL]		= &g12a_hdmi_sel.hw,
		[CLKID_HDMI_DIV]		= &g12a_hdmi_भाग.hw,
		[CLKID_HDMI]			= &g12a_hdmi.hw,
		[CLKID_MALI_0_SEL]		= &g12a_mali_0_sel.hw,
		[CLKID_MALI_0_DIV]		= &g12a_mali_0_भाग.hw,
		[CLKID_MALI_0]			= &g12a_mali_0.hw,
		[CLKID_MALI_1_SEL]		= &g12a_mali_1_sel.hw,
		[CLKID_MALI_1_DIV]		= &g12a_mali_1_भाग.hw,
		[CLKID_MALI_1]			= &g12a_mali_1.hw,
		[CLKID_MALI]			= &g12a_mali.hw,
		[CLKID_MPLL_50M_DIV]		= &g12a_mpll_50m_भाग.hw,
		[CLKID_MPLL_50M]		= &g12a_mpll_50m.hw,
		[CLKID_SYS_PLL_DIV16_EN]	= &g12a_sys_pll_भाग16_en.hw,
		[CLKID_SYS_PLL_DIV16]		= &g12a_sys_pll_भाग16.hw,
		[CLKID_CPU_CLK_DYN0_SEL]	= &g12a_cpu_clk_premux0.hw,
		[CLKID_CPU_CLK_DYN0_DIV]	= &g12a_cpu_clk_mux0_भाग.hw,
		[CLKID_CPU_CLK_DYN0]		= &g12a_cpu_clk_posपंचांगux0.hw,
		[CLKID_CPU_CLK_DYN1_SEL]	= &g12a_cpu_clk_premux1.hw,
		[CLKID_CPU_CLK_DYN1_DIV]	= &g12a_cpu_clk_mux1_भाग.hw,
		[CLKID_CPU_CLK_DYN1]		= &g12a_cpu_clk_posपंचांगux1.hw,
		[CLKID_CPU_CLK_DYN]		= &g12a_cpu_clk_dyn.hw,
		[CLKID_CPU_CLK]			= &g12a_cpu_clk.hw,
		[CLKID_CPU_CLK_DIV16_EN]	= &g12a_cpu_clk_भाग16_en.hw,
		[CLKID_CPU_CLK_DIV16]		= &g12a_cpu_clk_भाग16.hw,
		[CLKID_CPU_CLK_APB_DIV]		= &g12a_cpu_clk_apb_भाग.hw,
		[CLKID_CPU_CLK_APB]		= &g12a_cpu_clk_apb.hw,
		[CLKID_CPU_CLK_ATB_DIV]		= &g12a_cpu_clk_atb_भाग.hw,
		[CLKID_CPU_CLK_ATB]		= &g12a_cpu_clk_atb.hw,
		[CLKID_CPU_CLK_AXI_DIV]		= &g12a_cpu_clk_axi_भाग.hw,
		[CLKID_CPU_CLK_AXI]		= &g12a_cpu_clk_axi.hw,
		[CLKID_CPU_CLK_TRACE_DIV]	= &g12a_cpu_clk_trace_भाग.hw,
		[CLKID_CPU_CLK_TRACE]		= &g12a_cpu_clk_trace.hw,
		[CLKID_PCIE_PLL_DCO]		= &g12a_pcie_pll_dco.hw,
		[CLKID_PCIE_PLL_DCO_DIV2]	= &g12a_pcie_pll_dco_भाग2.hw,
		[CLKID_PCIE_PLL_OD]		= &g12a_pcie_pll_od.hw,
		[CLKID_PCIE_PLL]		= &g12a_pcie_pll.hw,
		[CLKID_VDEC_1_SEL]		= &g12a_vdec_1_sel.hw,
		[CLKID_VDEC_1_DIV]		= &g12a_vdec_1_भाग.hw,
		[CLKID_VDEC_1]			= &g12a_vdec_1.hw,
		[CLKID_VDEC_HEVC_SEL]		= &g12a_vdec_hevc_sel.hw,
		[CLKID_VDEC_HEVC_DIV]		= &g12a_vdec_hevc_भाग.hw,
		[CLKID_VDEC_HEVC]		= &g12a_vdec_hevc.hw,
		[CLKID_VDEC_HEVCF_SEL]		= &g12a_vdec_hevcf_sel.hw,
		[CLKID_VDEC_HEVCF_DIV]		= &g12a_vdec_hevcf_भाग.hw,
		[CLKID_VDEC_HEVCF]		= &g12a_vdec_hevcf.hw,
		[CLKID_TS_DIV]			= &g12a_ts_भाग.hw,
		[CLKID_TS]			= &g12a_ts.hw,
		[CLKID_GP1_PLL_DCO]		= &sm1_gp1_pll_dco.hw,
		[CLKID_GP1_PLL]			= &sm1_gp1_pll.hw,
		[CLKID_DSU_CLK_DYN0_SEL]	= &sm1_dsu_clk_premux0.hw,
		[CLKID_DSU_CLK_DYN0_DIV]	= &sm1_dsu_clk_premux1.hw,
		[CLKID_DSU_CLK_DYN0]		= &sm1_dsu_clk_mux0_भाग.hw,
		[CLKID_DSU_CLK_DYN1_SEL]	= &sm1_dsu_clk_posपंचांगux0.hw,
		[CLKID_DSU_CLK_DYN1_DIV]	= &sm1_dsu_clk_mux1_भाग.hw,
		[CLKID_DSU_CLK_DYN1]		= &sm1_dsu_clk_posपंचांगux1.hw,
		[CLKID_DSU_CLK_DYN]		= &sm1_dsu_clk_dyn.hw,
		[CLKID_DSU_CLK_FINAL]		= &sm1_dsu_final_clk.hw,
		[CLKID_DSU_CLK]			= &sm1_dsu_clk.hw,
		[CLKID_CPU1_CLK]		= &sm1_cpu1_clk.hw,
		[CLKID_CPU2_CLK]		= &sm1_cpu2_clk.hw,
		[CLKID_CPU3_CLK]		= &sm1_cpu3_clk.hw,
		[CLKID_SPICC0_SCLK_SEL]		= &g12a_spicc0_sclk_sel.hw,
		[CLKID_SPICC0_SCLK_DIV]		= &g12a_spicc0_sclk_भाग.hw,
		[CLKID_SPICC0_SCLK]		= &g12a_spicc0_sclk.hw,
		[CLKID_SPICC1_SCLK_SEL]		= &g12a_spicc1_sclk_sel.hw,
		[CLKID_SPICC1_SCLK_DIV]		= &g12a_spicc1_sclk_भाग.hw,
		[CLKID_SPICC1_SCLK]		= &g12a_spicc1_sclk.hw,
		[CLKID_NNA_AXI_CLK_SEL]		= &sm1_nna_axi_clk_sel.hw,
		[CLKID_NNA_AXI_CLK_DIV]		= &sm1_nna_axi_clk_भाग.hw,
		[CLKID_NNA_AXI_CLK]		= &sm1_nna_axi_clk.hw,
		[CLKID_NNA_CORE_CLK_SEL]	= &sm1_nna_core_clk_sel.hw,
		[CLKID_NNA_CORE_CLK_DIV]	= &sm1_nna_core_clk_भाग.hw,
		[CLKID_NNA_CORE_CLK]		= &sm1_nna_core_clk.hw,
		[CLKID_MIPI_DSI_PXCLK_SEL]	= &g12a_mipi_dsi_pxclk_sel.hw,
		[CLKID_MIPI_DSI_PXCLK_DIV]	= &g12a_mipi_dsi_pxclk_भाग.hw,
		[CLKID_MIPI_DSI_PXCLK]		= &g12a_mipi_dsi_pxclk.hw,
		[NR_CLKS]			= शून्य,
	पूर्ण,
	.num = NR_CLKS,
पूर्ण;

/* Convenience table to populate regmap in .probe */
अटल काष्ठा clk_regmap *स्थिर g12a_clk_regmaps[] = अणु
	&g12a_clk81,
	&g12a_करोs,
	&g12a_ddr,
	&g12a_audio_locker,
	&g12a_mipi_dsi_host,
	&g12a_eth_phy,
	&g12a_isa,
	&g12a_pl301,
	&g12a_periphs,
	&g12a_spicc_0,
	&g12a_i2c,
	&g12a_sana,
	&g12a_sd,
	&g12a_rng0,
	&g12a_uart0,
	&g12a_spicc_1,
	&g12a_hiu_reg,
	&g12a_mipi_dsi_phy,
	&g12a_assist_misc,
	&g12a_emmc_a,
	&g12a_emmc_b,
	&g12a_emmc_c,
	&g12a_audio_codec,
	&g12a_audio,
	&g12a_eth_core,
	&g12a_demux,
	&g12a_audio_अगरअगरo,
	&g12a_adc,
	&g12a_uart1,
	&g12a_g2d,
	&g12a_reset,
	&g12a_pcie_comb,
	&g12a_parser,
	&g12a_usb_general,
	&g12a_pcie_phy,
	&g12a_ahb_arb0,
	&g12a_ahb_data_bus,
	&g12a_ahb_ctrl_bus,
	&g12a_htx_hdcp22,
	&g12a_htx_pclk,
	&g12a_bt656,
	&g12a_usb1_to_ddr,
	&g12a_mmc_pclk,
	&g12a_uart2,
	&g12a_vpu_पूर्णांकr,
	&g12a_gic,
	&g12a_sd_emmc_a_clk0,
	&g12a_sd_emmc_b_clk0,
	&g12a_sd_emmc_c_clk0,
	&g12a_mpeg_clk_भाग,
	&g12a_sd_emmc_a_clk0_भाग,
	&g12a_sd_emmc_b_clk0_भाग,
	&g12a_sd_emmc_c_clk0_भाग,
	&g12a_mpeg_clk_sel,
	&g12a_sd_emmc_a_clk0_sel,
	&g12a_sd_emmc_b_clk0_sel,
	&g12a_sd_emmc_c_clk0_sel,
	&g12a_mpll0,
	&g12a_mpll1,
	&g12a_mpll2,
	&g12a_mpll3,
	&g12a_mpll0_भाग,
	&g12a_mpll1_भाग,
	&g12a_mpll2_भाग,
	&g12a_mpll3_भाग,
	&g12a_fixed_pll,
	&g12a_sys_pll,
	&g12a_gp0_pll,
	&g12a_hअगरi_pll,
	&g12a_vclk2_venci0,
	&g12a_vclk2_venci1,
	&g12a_vclk2_vencp0,
	&g12a_vclk2_vencp1,
	&g12a_vclk2_venct0,
	&g12a_vclk2_venct1,
	&g12a_vclk2_other,
	&g12a_vclk2_enci,
	&g12a_vclk2_encp,
	&g12a_dac_clk,
	&g12a_aoclk_gate,
	&g12a_iec958_gate,
	&g12a_enc480p,
	&g12a_rng1,
	&g12a_vclk2_enct,
	&g12a_vclk2_encl,
	&g12a_vclk2_venclmmc,
	&g12a_vclk2_vencl,
	&g12a_vclk2_other1,
	&g12a_fixed_pll_dco,
	&g12a_sys_pll_dco,
	&g12a_gp0_pll_dco,
	&g12a_hअगरi_pll_dco,
	&g12a_fclk_भाग2,
	&g12a_fclk_भाग3,
	&g12a_fclk_भाग4,
	&g12a_fclk_भाग5,
	&g12a_fclk_भाग7,
	&g12a_fclk_भाग2p5,
	&g12a_dma,
	&g12a_efuse,
	&g12a_rom_boot,
	&g12a_reset_sec,
	&g12a_sec_ahb_apb3,
	&g12a_vpu_0_sel,
	&g12a_vpu_0_भाग,
	&g12a_vpu_0,
	&g12a_vpu_1_sel,
	&g12a_vpu_1_भाग,
	&g12a_vpu_1,
	&g12a_vpu,
	&g12a_vapb_0_sel,
	&g12a_vapb_0_भाग,
	&g12a_vapb_0,
	&g12a_vapb_1_sel,
	&g12a_vapb_1_भाग,
	&g12a_vapb_1,
	&g12a_vapb_sel,
	&g12a_vapb,
	&g12a_hdmi_pll_dco,
	&g12a_hdmi_pll_od,
	&g12a_hdmi_pll_od2,
	&g12a_hdmi_pll,
	&g12a_vid_pll_भाग,
	&g12a_vid_pll_sel,
	&g12a_vid_pll,
	&g12a_vclk_sel,
	&g12a_vclk2_sel,
	&g12a_vclk_input,
	&g12a_vclk2_input,
	&g12a_vclk_भाग,
	&g12a_vclk2_भाग,
	&g12a_vclk,
	&g12a_vclk2,
	&g12a_vclk_भाग1,
	&g12a_vclk_भाग2_en,
	&g12a_vclk_भाग4_en,
	&g12a_vclk_भाग6_en,
	&g12a_vclk_भाग12_en,
	&g12a_vclk2_भाग1,
	&g12a_vclk2_भाग2_en,
	&g12a_vclk2_भाग4_en,
	&g12a_vclk2_भाग6_en,
	&g12a_vclk2_भाग12_en,
	&g12a_cts_enci_sel,
	&g12a_cts_encp_sel,
	&g12a_cts_vdac_sel,
	&g12a_hdmi_tx_sel,
	&g12a_cts_enci,
	&g12a_cts_encp,
	&g12a_cts_vdac,
	&g12a_hdmi_tx,
	&g12a_hdmi_sel,
	&g12a_hdmi_भाग,
	&g12a_hdmi,
	&g12a_mali_0_sel,
	&g12a_mali_0_भाग,
	&g12a_mali_0,
	&g12a_mali_1_sel,
	&g12a_mali_1_भाग,
	&g12a_mali_1,
	&g12a_mali,
	&g12a_mpll_50m,
	&g12a_sys_pll_भाग16_en,
	&g12a_cpu_clk_premux0,
	&g12a_cpu_clk_mux0_भाग,
	&g12a_cpu_clk_posपंचांगux0,
	&g12a_cpu_clk_premux1,
	&g12a_cpu_clk_mux1_भाग,
	&g12a_cpu_clk_posपंचांगux1,
	&g12a_cpu_clk_dyn,
	&g12a_cpu_clk,
	&g12a_cpu_clk_भाग16_en,
	&g12a_cpu_clk_apb_भाग,
	&g12a_cpu_clk_apb,
	&g12a_cpu_clk_atb_भाग,
	&g12a_cpu_clk_atb,
	&g12a_cpu_clk_axi_भाग,
	&g12a_cpu_clk_axi,
	&g12a_cpu_clk_trace_भाग,
	&g12a_cpu_clk_trace,
	&g12a_pcie_pll_od,
	&g12a_pcie_pll_dco,
	&g12a_vdec_1_sel,
	&g12a_vdec_1_भाग,
	&g12a_vdec_1,
	&g12a_vdec_hevc_sel,
	&g12a_vdec_hevc_भाग,
	&g12a_vdec_hevc,
	&g12a_vdec_hevcf_sel,
	&g12a_vdec_hevcf_भाग,
	&g12a_vdec_hevcf,
	&g12a_ts_भाग,
	&g12a_ts,
	&g12b_cpu_clk,
	&g12b_sys1_pll_dco,
	&g12b_sys1_pll,
	&g12b_sys1_pll_भाग16_en,
	&g12b_cpub_clk_premux0,
	&g12b_cpub_clk_mux0_भाग,
	&g12b_cpub_clk_posपंचांगux0,
	&g12b_cpub_clk_premux1,
	&g12b_cpub_clk_mux1_भाग,
	&g12b_cpub_clk_posपंचांगux1,
	&g12b_cpub_clk_dyn,
	&g12b_cpub_clk,
	&g12b_cpub_clk_भाग16_en,
	&g12b_cpub_clk_apb_sel,
	&g12b_cpub_clk_apb,
	&g12b_cpub_clk_atb_sel,
	&g12b_cpub_clk_atb,
	&g12b_cpub_clk_axi_sel,
	&g12b_cpub_clk_axi,
	&g12b_cpub_clk_trace_sel,
	&g12b_cpub_clk_trace,
	&sm1_gp1_pll_dco,
	&sm1_gp1_pll,
	&sm1_dsu_clk_premux0,
	&sm1_dsu_clk_premux1,
	&sm1_dsu_clk_mux0_भाग,
	&sm1_dsu_clk_posपंचांगux0,
	&sm1_dsu_clk_mux1_भाग,
	&sm1_dsu_clk_posपंचांगux1,
	&sm1_dsu_clk_dyn,
	&sm1_dsu_final_clk,
	&sm1_dsu_clk,
	&sm1_cpu1_clk,
	&sm1_cpu2_clk,
	&sm1_cpu3_clk,
	&g12a_spicc0_sclk_sel,
	&g12a_spicc0_sclk_भाग,
	&g12a_spicc0_sclk,
	&g12a_spicc1_sclk_sel,
	&g12a_spicc1_sclk_भाग,
	&g12a_spicc1_sclk,
	&sm1_nna_axi_clk_sel,
	&sm1_nna_axi_clk_भाग,
	&sm1_nna_axi_clk,
	&sm1_nna_core_clk_sel,
	&sm1_nna_core_clk_भाग,
	&sm1_nna_core_clk,
	&g12a_mipi_dsi_pxclk_sel,
	&g12a_mipi_dsi_pxclk_भाग,
	&g12a_mipi_dsi_pxclk,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence g12a_init_regs[] = अणु
	अणु .reg = HHI_MPLL_CNTL0,	.def = 0x00000543 पूर्ण,
पूर्ण;

#घोषणा DVFS_CON_ID "dvfs"

अटल पूर्णांक meson_g12a_dvfs_setup_common(काष्ठा device *dev,
					काष्ठा clk_hw **hws)
अणु
	काष्ठा clk *notअगरier_clk;
	काष्ठा clk_hw *xtal;
	पूर्णांक ret;

	xtal = clk_hw_get_parent_by_index(hws[CLKID_CPU_CLK_DYN1_SEL], 0);

	/* Setup घड़ी notअगरier क्रम cpu_clk_posपंचांगux0 */
	g12a_cpu_clk_posपंचांगux0_nb_data.xtal = xtal;
	notअगरier_clk = devm_clk_hw_get_clk(dev, &g12a_cpu_clk_posपंचांगux0.hw,
					   DVFS_CON_ID);
	ret = devm_clk_notअगरier_रेजिस्टर(dev, notअगरier_clk,
					 &g12a_cpu_clk_posपंचांगux0_nb_data.nb);
	अगर (ret) अणु
		dev_err(dev, "failed to register the cpu_clk_postmux0 notifier\n");
		वापस ret;
	पूर्ण

	/* Setup घड़ी notअगरier क्रम cpu_clk_dyn mux */
	notअगरier_clk = devm_clk_hw_get_clk(dev, &g12a_cpu_clk_dyn.hw,
					   DVFS_CON_ID);
	ret = devm_clk_notअगरier_रेजिस्टर(dev, notअगरier_clk,
					 &g12a_cpu_clk_mux_nb);
	अगर (ret) अणु
		dev_err(dev, "failed to register the cpu_clk_dyn notifier\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक meson_g12b_dvfs_setup(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_hw **hws = g12b_hw_onecell_data.hws;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा clk *notअगरier_clk;
	काष्ठा clk_hw *xtal;
	पूर्णांक ret;

	ret = meson_g12a_dvfs_setup_common(dev, hws);
	अगर (ret)
		वापस ret;

	xtal = clk_hw_get_parent_by_index(hws[CLKID_CPU_CLK_DYN1_SEL], 0);

	/* Setup घड़ी notअगरier क्रम cpu_clk mux */
	notअगरier_clk = devm_clk_hw_get_clk(dev, &g12b_cpu_clk.hw,
					   DVFS_CON_ID);
	ret = devm_clk_notअगरier_रेजिस्टर(dev, notअगरier_clk,
					 &g12a_cpu_clk_mux_nb);
	अगर (ret) अणु
		dev_err(dev, "failed to register the cpu_clk notifier\n");
		वापस ret;
	पूर्ण

	/* Setup घड़ी notअगरier क्रम sys1_pll */
	notअगरier_clk = devm_clk_hw_get_clk(dev, &g12b_sys1_pll.hw,
					   DVFS_CON_ID);
	ret = devm_clk_notअगरier_रेजिस्टर(dev, notअगरier_clk,
					 &g12b_cpu_clk_sys1_pll_nb_data.nb);
	अगर (ret) अणु
		dev_err(dev, "failed to register the sys1_pll notifier\n");
		वापस ret;
	पूर्ण

	/* Add notअगरiers क्रम the second CPU cluster */

	/* Setup घड़ी notअगरier क्रम cpub_clk_posपंचांगux0 */
	g12b_cpub_clk_posपंचांगux0_nb_data.xtal = xtal;
	notअगरier_clk = devm_clk_hw_get_clk(dev, &g12b_cpub_clk_posपंचांगux0.hw,
					   DVFS_CON_ID);
	ret = devm_clk_notअगरier_रेजिस्टर(dev, notअगरier_clk,
					 &g12b_cpub_clk_posपंचांगux0_nb_data.nb);
	अगर (ret) अणु
		dev_err(dev, "failed to register the cpub_clk_postmux0 notifier\n");
		वापस ret;
	पूर्ण

	/* Setup घड़ी notअगरier क्रम cpub_clk_dyn mux */
	notअगरier_clk = devm_clk_hw_get_clk(dev, &g12b_cpub_clk_dyn.hw, "dvfs");
	ret = devm_clk_notअगरier_रेजिस्टर(dev, notअगरier_clk,
					 &g12a_cpu_clk_mux_nb);
	अगर (ret) अणु
		dev_err(dev, "failed to register the cpub_clk_dyn notifier\n");
		वापस ret;
	पूर्ण

	/* Setup घड़ी notअगरier क्रम cpub_clk mux */
	notअगरier_clk = devm_clk_hw_get_clk(dev, &g12b_cpub_clk.hw, DVFS_CON_ID);
	ret = devm_clk_notअगरier_रेजिस्टर(dev, notअगरier_clk,
					 &g12a_cpu_clk_mux_nb);
	अगर (ret) अणु
		dev_err(dev, "failed to register the cpub_clk notifier\n");
		वापस ret;
	पूर्ण

	/* Setup घड़ी notअगरier क्रम sys_pll */
	notअगरier_clk = devm_clk_hw_get_clk(dev, &g12a_sys_pll.hw, DVFS_CON_ID);
	ret = devm_clk_notअगरier_रेजिस्टर(dev, notअगरier_clk,
					 &g12b_cpub_clk_sys_pll_nb_data.nb);
	अगर (ret) अणु
		dev_err(dev, "failed to register the sys_pll notifier\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक meson_g12a_dvfs_setup(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_hw **hws = g12a_hw_onecell_data.hws;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा clk *notअगरier_clk;
	पूर्णांक ret;

	ret = meson_g12a_dvfs_setup_common(dev, hws);
	अगर (ret)
		वापस ret;

	/* Setup घड़ी notअगरier क्रम cpu_clk mux */
	notअगरier_clk = devm_clk_hw_get_clk(dev, &g12a_cpu_clk.hw, DVFS_CON_ID);
	ret = devm_clk_notअगरier_रेजिस्टर(dev, notअगरier_clk,
				    &g12a_cpu_clk_mux_nb);
	अगर (ret) अणु
		dev_err(dev, "failed to register the cpu_clk notifier\n");
		वापस ret;
	पूर्ण

	/* Setup घड़ी notअगरier क्रम sys_pll */
	notअगरier_clk = devm_clk_hw_get_clk(dev, &g12a_sys_pll.hw, DVFS_CON_ID);
	ret = devm_clk_notअगरier_रेजिस्टर(dev, notअगरier_clk,
					 &g12a_sys_pll_nb_data.nb);
	अगर (ret) अणु
		dev_err(dev, "failed to register the sys_pll notifier\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा meson_g12a_data अणु
	स्थिर काष्ठा meson_eeclkc_data eeclkc_data;
	पूर्णांक (*dvfs_setup)(काष्ठा platक्रमm_device *pdev);
पूर्ण;

अटल पूर्णांक meson_g12a_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा meson_eeclkc_data *eeclkc_data;
	स्थिर काष्ठा meson_g12a_data *g12a_data;
	पूर्णांक ret;

	eeclkc_data = of_device_get_match_data(&pdev->dev);
	अगर (!eeclkc_data)
		वापस -EINVAL;

	ret = meson_eeclkc_probe(pdev);
	अगर (ret)
		वापस ret;

	g12a_data = container_of(eeclkc_data, काष्ठा meson_g12a_data,
				 eeclkc_data);

	अगर (g12a_data->dvfs_setup)
		वापस g12a_data->dvfs_setup(pdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा meson_g12a_data g12a_clkc_data = अणु
	.eeclkc_data = अणु
		.regmap_clks = g12a_clk_regmaps,
		.regmap_clk_num = ARRAY_SIZE(g12a_clk_regmaps),
		.hw_onecell_data = &g12a_hw_onecell_data,
		.init_regs = g12a_init_regs,
		.init_count = ARRAY_SIZE(g12a_init_regs),
	पूर्ण,
	.dvfs_setup = meson_g12a_dvfs_setup,
पूर्ण;

अटल स्थिर काष्ठा meson_g12a_data g12b_clkc_data = अणु
	.eeclkc_data = अणु
		.regmap_clks = g12a_clk_regmaps,
		.regmap_clk_num = ARRAY_SIZE(g12a_clk_regmaps),
		.hw_onecell_data = &g12b_hw_onecell_data,
	पूर्ण,
	.dvfs_setup = meson_g12b_dvfs_setup,
पूर्ण;

अटल स्थिर काष्ठा meson_g12a_data sm1_clkc_data = अणु
	.eeclkc_data = अणु
		.regmap_clks = g12a_clk_regmaps,
		.regmap_clk_num = ARRAY_SIZE(g12a_clk_regmaps),
		.hw_onecell_data = &sm1_hw_onecell_data,
	पूर्ण,
	.dvfs_setup = meson_g12a_dvfs_setup,
पूर्ण;

अटल स्थिर काष्ठा of_device_id clkc_match_table[] = अणु
	अणु
		.compatible = "amlogic,g12a-clkc",
		.data = &g12a_clkc_data.eeclkc_data
	पूर्ण,
	अणु
		.compatible = "amlogic,g12b-clkc",
		.data = &g12b_clkc_data.eeclkc_data
	पूर्ण,
	अणु
		.compatible = "amlogic,sm1-clkc",
		.data = &sm1_clkc_data.eeclkc_data
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, clkc_match_table);

अटल काष्ठा platक्रमm_driver g12a_driver = अणु
	.probe		= meson_g12a_probe,
	.driver		= अणु
		.name	= "g12a-clkc",
		.of_match_table = clkc_match_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(g12a_driver);
MODULE_LICENSE("GPL v2");
