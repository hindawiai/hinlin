<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Amlogic Meson-AXG Clock Controller Driver
 *
 * Copyright (c) 2016 Baylibre SAS.
 * Author: Michael Turquette <mturquette@baylibre.com>
 *
 * Copyright (c) 2019 Baylibre SAS.
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश "meson-aoclk.h"
#समावेश "g12a-aoclk.h"

#समावेश "clk-regmap.h"
#समावेश "clk-dualdiv.h"

/*
 * AO Configuration Clock रेजिस्टरs offsets
 * Register offsets from the data sheet must be multiplied by 4.
 */
#घोषणा AO_RTI_STATUS_REG3	0x0C
#घोषणा AO_RTI_PWR_CNTL_REG0	0x10
#घोषणा AO_RTI_GEN_CNTL_REG0	0x40
#घोषणा AO_CLK_GATE0		0x4c
#घोषणा AO_CLK_GATE0_SP		0x50
#घोषणा AO_OSCIN_CNTL		0x58
#घोषणा AO_CEC_CLK_CNTL_REG0	0x74
#घोषणा AO_CEC_CLK_CNTL_REG1	0x78
#घोषणा AO_SAR_CLK		0x90
#घोषणा AO_RTC_ALT_CLK_CNTL0	0x94
#घोषणा AO_RTC_ALT_CLK_CNTL1	0x98

/*
 * Like every other peripheral घड़ी gate in Amlogic Clock drivers,
 * we are using CLK_IGNORE_UNUSED here, so we keep the state of the
 * bootloader. The goal is to हटाओ this flag at some poपूर्णांक.
 * Actually removing it will require some extensive test to be करोne safely.
 */
#घोषणा AXG_AO_GATE(_name, _reg, _bit)					\
अटल काष्ठा clk_regmap g12a_aoclk_##_name = अणु				\
	.data = &(काष्ठा clk_regmap_gate_data) अणु			\
		.offset = (_reg),					\
		.bit_idx = (_bit),					\
	पूर्ण,								\
	.hw.init = &(काष्ठा clk_init_data) अणु				\
		.name =  "g12a_ao_" #_name,				\
		.ops = &clk_regmap_gate_ops,				\
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु	\
			.fw_name = "mpeg-clk",				\
		पूर्ण,							\
		.num_parents = 1,					\
		.flags = CLK_IGNORE_UNUSED,				\
	पूर्ण,								\
पूर्ण

AXG_AO_GATE(ahb, AO_CLK_GATE0, 0);
AXG_AO_GATE(ir_in, AO_CLK_GATE0, 1);
AXG_AO_GATE(i2c_m0, AO_CLK_GATE0, 2);
AXG_AO_GATE(i2c_s0, AO_CLK_GATE0, 3);
AXG_AO_GATE(uart, AO_CLK_GATE0, 4);
AXG_AO_GATE(prod_i2c, AO_CLK_GATE0, 5);
AXG_AO_GATE(uart2, AO_CLK_GATE0, 6);
AXG_AO_GATE(ir_out, AO_CLK_GATE0, 7);
AXG_AO_GATE(saradc, AO_CLK_GATE0, 8);
AXG_AO_GATE(mailbox, AO_CLK_GATE0_SP, 0);
AXG_AO_GATE(m3, AO_CLK_GATE0_SP, 1);
AXG_AO_GATE(ahb_sram, AO_CLK_GATE0_SP, 2);
AXG_AO_GATE(rti, AO_CLK_GATE0_SP, 3);
AXG_AO_GATE(m4_fclk, AO_CLK_GATE0_SP, 4);
AXG_AO_GATE(m4_hclk, AO_CLK_GATE0_SP, 5);

अटल काष्ठा clk_regmap g12a_aoclk_cts_oscin = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = AO_RTI_PWR_CNTL_REG0,
		.bit_idx = 14,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cts_oscin",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			.fw_name = "xtal",
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा meson_clk_duaद_भाग_param g12a_32k_भाग_प्रकारable[] = अणु
	अणु
		.dual	= 1,
		.n1	= 733,
		.m1	= 8,
		.n2	= 732,
		.m2	= 11,
	पूर्ण, अणुपूर्ण
पूर्ण;

/* 32k_by_oscin घड़ी */

अटल काष्ठा clk_regmap g12a_aoclk_32k_by_oscin_pre = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = AO_RTC_ALT_CLK_CNTL0,
		.bit_idx = 31,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "g12a_ao_32k_by_oscin_pre",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_aoclk_cts_oscin.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_aoclk_32k_by_oscin_भाग = अणु
	.data = &(काष्ठा meson_clk_duaद_भाग_data)अणु
		.n1 = अणु
			.reg_off = AO_RTC_ALT_CLK_CNTL0,
			.shअगरt   = 0,
			.width   = 12,
		पूर्ण,
		.n2 = अणु
			.reg_off = AO_RTC_ALT_CLK_CNTL0,
			.shअगरt   = 12,
			.width   = 12,
		पूर्ण,
		.m1 = अणु
			.reg_off = AO_RTC_ALT_CLK_CNTL1,
			.shअगरt   = 0,
			.width   = 12,
		पूर्ण,
		.m2 = अणु
			.reg_off = AO_RTC_ALT_CLK_CNTL1,
			.shअगरt   = 12,
			.width   = 12,
		पूर्ण,
		.dual = अणु
			.reg_off = AO_RTC_ALT_CLK_CNTL0,
			.shअगरt   = 28,
			.width   = 1,
		पूर्ण,
		.table = g12a_32k_भाग_प्रकारable,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "g12a_ao_32k_by_oscin_div",
		.ops = &meson_clk_duaद_भाग_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_aoclk_32k_by_oscin_pre.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_aoclk_32k_by_oscin_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data) अणु
		.offset = AO_RTC_ALT_CLK_CNTL1,
		.mask = 0x1,
		.shअगरt = 24,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "g12a_ao_32k_by_oscin_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_aoclk_32k_by_oscin_भाग.hw,
			&g12a_aoclk_32k_by_oscin_pre.hw,
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_aoclk_32k_by_oscin = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = AO_RTC_ALT_CLK_CNTL0,
		.bit_idx = 30,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "g12a_ao_32k_by_oscin",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_aoclk_32k_by_oscin_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

/* cec घड़ी */

अटल काष्ठा clk_regmap g12a_aoclk_cec_pre = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = AO_CEC_CLK_CNTL_REG0,
		.bit_idx = 31,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "g12a_ao_cec_pre",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_aoclk_cts_oscin.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_aoclk_cec_भाग = अणु
	.data = &(काष्ठा meson_clk_duaद_भाग_data)अणु
		.n1 = अणु
			.reg_off = AO_CEC_CLK_CNTL_REG0,
			.shअगरt   = 0,
			.width   = 12,
		पूर्ण,
		.n2 = अणु
			.reg_off = AO_CEC_CLK_CNTL_REG0,
			.shअगरt   = 12,
			.width   = 12,
		पूर्ण,
		.m1 = अणु
			.reg_off = AO_CEC_CLK_CNTL_REG1,
			.shअगरt   = 0,
			.width   = 12,
		पूर्ण,
		.m2 = अणु
			.reg_off = AO_CEC_CLK_CNTL_REG1,
			.shअगरt   = 12,
			.width   = 12,
		पूर्ण,
		.dual = अणु
			.reg_off = AO_CEC_CLK_CNTL_REG0,
			.shअगरt   = 28,
			.width   = 1,
		पूर्ण,
		.table = g12a_32k_भाग_प्रकारable,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "g12a_ao_cec_div",
		.ops = &meson_clk_duaद_भाग_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_aoclk_cec_pre.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_aoclk_cec_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data) अणु
		.offset = AO_CEC_CLK_CNTL_REG1,
		.mask = 0x1,
		.shअगरt = 24,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "g12a_ao_cec_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_aoclk_cec_भाग.hw,
			&g12a_aoclk_cec_pre.hw,
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_aoclk_cec = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = AO_CEC_CLK_CNTL_REG0,
		.bit_idx = 30,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "g12a_ao_cec",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_aoclk_cec_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_aoclk_cts_rtc_oscin = अणु
	.data = &(काष्ठा clk_regmap_mux_data) अणु
		.offset = AO_RTI_PWR_CNTL_REG0,
		.mask = 0x1,
		.shअगरt = 10,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "g12a_ao_cts_rtc_oscin",
		.ops = &clk_regmap_mux_ops,
		.parent_data = (स्थिर काष्ठा clk_parent_data []) अणु
			अणु .hw = &g12a_aoclk_32k_by_oscin.hw पूर्ण,
			अणु .fw_name = "ext-32k-0", पूर्ण,
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_aoclk_clk81 = अणु
	.data = &(काष्ठा clk_regmap_mux_data) अणु
		.offset = AO_RTI_PWR_CNTL_REG0,
		.mask = 0x1,
		.shअगरt = 8,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "g12a_ao_clk81",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_data = (स्थिर काष्ठा clk_parent_data []) अणु
			अणु .fw_name = "mpeg-clk", पूर्ण,
			अणु .hw = &g12a_aoclk_cts_rtc_oscin.hw पूर्ण,
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_aoclk_saradc_mux = अणु
	.data = &(काष्ठा clk_regmap_mux_data) अणु
		.offset = AO_SAR_CLK,
		.mask = 0x3,
		.shअगरt = 9,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "g12a_ao_saradc_mux",
		.ops = &clk_regmap_mux_ops,
		.parent_data = (स्थिर काष्ठा clk_parent_data []) अणु
			अणु .fw_name = "xtal", पूर्ण,
			अणु .hw = &g12a_aoclk_clk81.hw पूर्ण,
		पूर्ण,
		.num_parents = 2,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_aoclk_saradc_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data) अणु
		.offset = AO_SAR_CLK,
		.shअगरt = 0,
		.width = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "g12a_ao_saradc_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_aoclk_saradc_mux.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap g12a_aoclk_saradc_gate = अणु
	.data = &(काष्ठा clk_regmap_gate_data) अणु
		.offset = AO_SAR_CLK,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "g12a_ao_saradc_gate",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&g12a_aoclk_saradc_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक g12a_aoclk_reset[] = अणु
	[RESET_AO_IR_IN]	= 16,
	[RESET_AO_UART]		= 17,
	[RESET_AO_I2C_M]	= 18,
	[RESET_AO_I2C_S]	= 19,
	[RESET_AO_SAR_ADC]	= 20,
	[RESET_AO_UART2]	= 22,
	[RESET_AO_IR_OUT]	= 23,
पूर्ण;

अटल काष्ठा clk_regmap *g12a_aoclk_regmap[] = अणु
	&g12a_aoclk_ahb,
	&g12a_aoclk_ir_in,
	&g12a_aoclk_i2c_m0,
	&g12a_aoclk_i2c_s0,
	&g12a_aoclk_uart,
	&g12a_aoclk_prod_i2c,
	&g12a_aoclk_uart2,
	&g12a_aoclk_ir_out,
	&g12a_aoclk_saradc,
	&g12a_aoclk_mailbox,
	&g12a_aoclk_m3,
	&g12a_aoclk_ahb_sram,
	&g12a_aoclk_rti,
	&g12a_aoclk_m4_fclk,
	&g12a_aoclk_m4_hclk,
	&g12a_aoclk_cts_oscin,
	&g12a_aoclk_32k_by_oscin_pre,
	&g12a_aoclk_32k_by_oscin_भाग,
	&g12a_aoclk_32k_by_oscin_sel,
	&g12a_aoclk_32k_by_oscin,
	&g12a_aoclk_cec_pre,
	&g12a_aoclk_cec_भाग,
	&g12a_aoclk_cec_sel,
	&g12a_aoclk_cec,
	&g12a_aoclk_cts_rtc_oscin,
	&g12a_aoclk_clk81,
	&g12a_aoclk_saradc_mux,
	&g12a_aoclk_saradc_भाग,
	&g12a_aoclk_saradc_gate,
पूर्ण;

अटल स्थिर काष्ठा clk_hw_onecell_data g12a_aoclk_onecell_data = अणु
	.hws = अणु
		[CLKID_AO_AHB]		= &g12a_aoclk_ahb.hw,
		[CLKID_AO_IR_IN]	= &g12a_aoclk_ir_in.hw,
		[CLKID_AO_I2C_M0]	= &g12a_aoclk_i2c_m0.hw,
		[CLKID_AO_I2C_S0]	= &g12a_aoclk_i2c_s0.hw,
		[CLKID_AO_UART]		= &g12a_aoclk_uart.hw,
		[CLKID_AO_PROD_I2C]	= &g12a_aoclk_prod_i2c.hw,
		[CLKID_AO_UART2]	= &g12a_aoclk_uart2.hw,
		[CLKID_AO_IR_OUT]	= &g12a_aoclk_ir_out.hw,
		[CLKID_AO_SAR_ADC]	= &g12a_aoclk_saradc.hw,
		[CLKID_AO_MAILBOX]	= &g12a_aoclk_mailbox.hw,
		[CLKID_AO_M3]		= &g12a_aoclk_m3.hw,
		[CLKID_AO_AHB_SRAM]	= &g12a_aoclk_ahb_sram.hw,
		[CLKID_AO_RTI]		= &g12a_aoclk_rti.hw,
		[CLKID_AO_M4_FCLK]	= &g12a_aoclk_m4_fclk.hw,
		[CLKID_AO_M4_HCLK]	= &g12a_aoclk_m4_hclk.hw,
		[CLKID_AO_CLK81]	= &g12a_aoclk_clk81.hw,
		[CLKID_AO_SAR_ADC_SEL]	= &g12a_aoclk_saradc_mux.hw,
		[CLKID_AO_SAR_ADC_DIV]	= &g12a_aoclk_saradc_भाग.hw,
		[CLKID_AO_SAR_ADC_CLK]	= &g12a_aoclk_saradc_gate.hw,
		[CLKID_AO_CTS_OSCIN]	= &g12a_aoclk_cts_oscin.hw,
		[CLKID_AO_32K_PRE]	= &g12a_aoclk_32k_by_oscin_pre.hw,
		[CLKID_AO_32K_DIV]	= &g12a_aoclk_32k_by_oscin_भाग.hw,
		[CLKID_AO_32K_SEL]	= &g12a_aoclk_32k_by_oscin_sel.hw,
		[CLKID_AO_32K]		= &g12a_aoclk_32k_by_oscin.hw,
		[CLKID_AO_CEC_PRE]	= &g12a_aoclk_cec_pre.hw,
		[CLKID_AO_CEC_DIV]	= &g12a_aoclk_cec_भाग.hw,
		[CLKID_AO_CEC_SEL]	= &g12a_aoclk_cec_sel.hw,
		[CLKID_AO_CEC]		= &g12a_aoclk_cec.hw,
		[CLKID_AO_CTS_RTC_OSCIN] = &g12a_aoclk_cts_rtc_oscin.hw,
	पूर्ण,
	.num = NR_CLKS,
पूर्ण;

अटल स्थिर काष्ठा meson_aoclk_data g12a_aoclkc_data = अणु
	.reset_reg	= AO_RTI_GEN_CNTL_REG0,
	.num_reset	= ARRAY_SIZE(g12a_aoclk_reset),
	.reset		= g12a_aoclk_reset,
	.num_clks	= ARRAY_SIZE(g12a_aoclk_regmap),
	.clks		= g12a_aoclk_regmap,
	.hw_data	= &g12a_aoclk_onecell_data,
पूर्ण;

अटल स्थिर काष्ठा of_device_id g12a_aoclkc_match_table[] = अणु
	अणु
		.compatible	= "amlogic,meson-g12a-aoclkc",
		.data		= &g12a_aoclkc_data,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, g12a_aoclkc_match_table);

अटल काष्ठा platक्रमm_driver g12a_aoclkc_driver = अणु
	.probe		= meson_aoclkc_probe,
	.driver		= अणु
		.name	= "g12a-aoclkc",
		.of_match_table = g12a_aoclkc_match_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(g12a_aoclkc_driver);
MODULE_LICENSE("GPL v2");
