<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Amlogic Meson-AXG Clock Controller Driver
 *
 * Copyright (c) 2016 Baylibre SAS.
 * Author: Michael Turquette <mturquette@baylibre.com>
 *
 * Copyright (c) 2018 Amlogic, inc.
 * Author: Qiufang Dai <qiufang.dai@amlogic.com>
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश "meson-aoclk.h"
#समावेश "axg-aoclk.h"

#समावेश "clk-regmap.h"
#समावेश "clk-dualdiv.h"

/*
 * AO Configuration Clock रेजिस्टरs offsets
 * Register offsets from the data sheet must be multiplied by 4.
 */
#घोषणा AO_RTI_PWR_CNTL_REG1	0x0C
#घोषणा AO_RTI_PWR_CNTL_REG0	0x10
#घोषणा AO_RTI_GEN_CNTL_REG0	0x40
#घोषणा AO_OSCIN_CNTL		0x58
#घोषणा AO_CRT_CLK_CNTL1	0x68
#घोषणा AO_SAR_CLK		0x90
#घोषणा AO_RTC_ALT_CLK_CNTL0	0x94
#घोषणा AO_RTC_ALT_CLK_CNTL1	0x98

#घोषणा AXG_AO_GATE(_name, _bit)					\
अटल काष्ठा clk_regmap axg_aoclk_##_name = अणु				\
	.data = &(काष्ठा clk_regmap_gate_data) अणु			\
		.offset = (AO_RTI_GEN_CNTL_REG0),			\
		.bit_idx = (_bit),					\
	पूर्ण,								\
	.hw.init = &(काष्ठा clk_init_data) अणु				\
		.name =  "axg_ao_" #_name,				\
		.ops = &clk_regmap_gate_ops,				\
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु	\
			.fw_name = "mpeg-clk",				\
		पूर्ण,							\
		.num_parents = 1,					\
		.flags = CLK_IGNORE_UNUSED,				\
	पूर्ण,								\
पूर्ण

AXG_AO_GATE(remote, 0);
AXG_AO_GATE(i2c_master, 1);
AXG_AO_GATE(i2c_slave, 2);
AXG_AO_GATE(uart1, 3);
AXG_AO_GATE(uart2, 5);
AXG_AO_GATE(ir_blaster, 6);
AXG_AO_GATE(saradc, 7);

अटल काष्ठा clk_regmap axg_aoclk_cts_oscin = अणु
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

अटल काष्ठा clk_regmap axg_aoclk_32k_pre = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = AO_RTC_ALT_CLK_CNTL0,
		.bit_idx = 31,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "axg_ao_32k_pre",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_aoclk_cts_oscin.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा meson_clk_duaद_भाग_param axg_32k_भाग_प्रकारable[] = अणु
	अणु
		.dual	= 1,
		.n1	= 733,
		.m1	= 8,
		.n2	= 732,
		.m2	= 11,
	पूर्ण, अणुपूर्ण
पूर्ण;

अटल काष्ठा clk_regmap axg_aoclk_32k_भाग = अणु
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
		.table = axg_32k_भाग_प्रकारable,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "axg_ao_32k_div",
		.ops = &meson_clk_duaद_भाग_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_aoclk_32k_pre.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_aoclk_32k_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data) अणु
		.offset = AO_RTC_ALT_CLK_CNTL1,
		.mask = 0x1,
		.shअगरt = 24,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "axg_ao_32k_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_aoclk_32k_भाग.hw,
			&axg_aoclk_32k_pre.hw,
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_aoclk_32k = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = AO_RTC_ALT_CLK_CNTL0,
		.bit_idx = 30,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "axg_ao_32k",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_aoclk_32k_sel.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_aoclk_cts_rtc_oscin = अणु
	.data = &(काष्ठा clk_regmap_mux_data) अणु
		.offset = AO_RTI_PWR_CNTL_REG0,
		.mask = 0x1,
		.shअगरt = 10,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "axg_ao_cts_rtc_oscin",
		.ops = &clk_regmap_mux_ops,
		.parent_data = (स्थिर काष्ठा clk_parent_data []) अणु
			अणु .hw = &axg_aoclk_32k.hw पूर्ण,
			अणु .fw_name = "ext_32k-0", पूर्ण,
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_aoclk_clk81 = अणु
	.data = &(काष्ठा clk_regmap_mux_data) अणु
		.offset = AO_RTI_PWR_CNTL_REG0,
		.mask = 0x1,
		.shअगरt = 8,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "axg_ao_clk81",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_data = (स्थिर काष्ठा clk_parent_data []) अणु
			अणु .fw_name = "mpeg-clk", पूर्ण,
			अणु .hw = &axg_aoclk_cts_rtc_oscin.hw पूर्ण,
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_aoclk_saradc_mux = अणु
	.data = &(काष्ठा clk_regmap_mux_data) अणु
		.offset = AO_SAR_CLK,
		.mask = 0x3,
		.shअगरt = 9,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "axg_ao_saradc_mux",
		.ops = &clk_regmap_mux_ops,
		.parent_data = (स्थिर काष्ठा clk_parent_data []) अणु
			अणु .fw_name = "xtal", पूर्ण,
			अणु .hw = &axg_aoclk_clk81.hw पूर्ण,
		पूर्ण,
		.num_parents = 2,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_aoclk_saradc_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data) अणु
		.offset = AO_SAR_CLK,
		.shअगरt = 0,
		.width = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "axg_ao_saradc_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_aoclk_saradc_mux.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap axg_aoclk_saradc_gate = अणु
	.data = &(काष्ठा clk_regmap_gate_data) अणु
		.offset = AO_SAR_CLK,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "axg_ao_saradc_gate",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&axg_aoclk_saradc_भाग.hw
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक axg_aoclk_reset[] = अणु
	[RESET_AO_REMOTE]	= 16,
	[RESET_AO_I2C_MASTER]	= 18,
	[RESET_AO_I2C_SLAVE]	= 19,
	[RESET_AO_UART1]	= 17,
	[RESET_AO_UART2]	= 22,
	[RESET_AO_IR_BLASTER]	= 23,
पूर्ण;

अटल काष्ठा clk_regmap *axg_aoclk_regmap[] = अणु
	&axg_aoclk_remote,
	&axg_aoclk_i2c_master,
	&axg_aoclk_i2c_slave,
	&axg_aoclk_uart1,
	&axg_aoclk_uart2,
	&axg_aoclk_ir_blaster,
	&axg_aoclk_saradc,
	&axg_aoclk_cts_oscin,
	&axg_aoclk_32k_pre,
	&axg_aoclk_32k_भाग,
	&axg_aoclk_32k_sel,
	&axg_aoclk_32k,
	&axg_aoclk_cts_rtc_oscin,
	&axg_aoclk_clk81,
	&axg_aoclk_saradc_mux,
	&axg_aoclk_saradc_भाग,
	&axg_aoclk_saradc_gate,
पूर्ण;

अटल स्थिर काष्ठा clk_hw_onecell_data axg_aoclk_onecell_data = अणु
	.hws = अणु
		[CLKID_AO_REMOTE]	= &axg_aoclk_remote.hw,
		[CLKID_AO_I2C_MASTER]	= &axg_aoclk_i2c_master.hw,
		[CLKID_AO_I2C_SLAVE]	= &axg_aoclk_i2c_slave.hw,
		[CLKID_AO_UART1]	= &axg_aoclk_uart1.hw,
		[CLKID_AO_UART2]	= &axg_aoclk_uart2.hw,
		[CLKID_AO_IR_BLASTER]	= &axg_aoclk_ir_blaster.hw,
		[CLKID_AO_SAR_ADC]	= &axg_aoclk_saradc.hw,
		[CLKID_AO_CLK81]	= &axg_aoclk_clk81.hw,
		[CLKID_AO_SAR_ADC_SEL]	= &axg_aoclk_saradc_mux.hw,
		[CLKID_AO_SAR_ADC_DIV]	= &axg_aoclk_saradc_भाग.hw,
		[CLKID_AO_SAR_ADC_CLK]	= &axg_aoclk_saradc_gate.hw,
		[CLKID_AO_CTS_OSCIN]	= &axg_aoclk_cts_oscin.hw,
		[CLKID_AO_32K_PRE]	= &axg_aoclk_32k_pre.hw,
		[CLKID_AO_32K_DIV]	= &axg_aoclk_32k_भाग.hw,
		[CLKID_AO_32K_SEL]	= &axg_aoclk_32k_sel.hw,
		[CLKID_AO_32K]		= &axg_aoclk_32k.hw,
		[CLKID_AO_CTS_RTC_OSCIN] = &axg_aoclk_cts_rtc_oscin.hw,
	पूर्ण,
	.num = NR_CLKS,
पूर्ण;

अटल स्थिर काष्ठा meson_aoclk_data axg_aoclkc_data = अणु
	.reset_reg	= AO_RTI_GEN_CNTL_REG0,
	.num_reset	= ARRAY_SIZE(axg_aoclk_reset),
	.reset		= axg_aoclk_reset,
	.num_clks	= ARRAY_SIZE(axg_aoclk_regmap),
	.clks		= axg_aoclk_regmap,
	.hw_data	= &axg_aoclk_onecell_data,
पूर्ण;

अटल स्थिर काष्ठा of_device_id axg_aoclkc_match_table[] = अणु
	अणु
		.compatible	= "amlogic,meson-axg-aoclkc",
		.data		= &axg_aoclkc_data,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, axg_aoclkc_match_table);

अटल काष्ठा platक्रमm_driver axg_aoclkc_driver = अणु
	.probe		= meson_aoclkc_probe,
	.driver		= अणु
		.name	= "axg-aoclkc",
		.of_match_table = axg_aoclkc_match_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(axg_aoclkc_driver);
MODULE_LICENSE("GPL v2");
