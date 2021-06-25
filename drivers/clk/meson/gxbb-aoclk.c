<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/*
 * Copyright (c) 2016 BayLibre, SAS.
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश "meson-aoclk.h"
#समावेश "gxbb-aoclk.h"

#समावेश "clk-regmap.h"
#समावेश "clk-dualdiv.h"

/* AO Configuration Clock रेजिस्टरs offsets */
#घोषणा AO_RTI_PWR_CNTL_REG1	0x0c
#घोषणा AO_RTI_PWR_CNTL_REG0	0x10
#घोषणा AO_RTI_GEN_CNTL_REG0	0x40
#घोषणा AO_OSCIN_CNTL		0x58
#घोषणा AO_CRT_CLK_CNTL1	0x68
#घोषणा AO_RTC_ALT_CLK_CNTL0	0x94
#घोषणा AO_RTC_ALT_CLK_CNTL1	0x98

#घोषणा GXBB_AO_GATE(_name, _bit)					\
अटल काष्ठा clk_regmap _name##_ao = अणु					\
	.data = &(काष्ठा clk_regmap_gate_data) अणु			\
		.offset = AO_RTI_GEN_CNTL_REG0,				\
		.bit_idx = (_bit),					\
	पूर्ण,								\
	.hw.init = &(काष्ठा clk_init_data) अणु				\
		.name = #_name "_ao",					\
		.ops = &clk_regmap_gate_ops,				\
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु	\
			.fw_name = "mpeg-clk",				\
		पूर्ण,							\
		.num_parents = 1,					\
		.flags = CLK_IGNORE_UNUSED,				\
	पूर्ण,								\
पूर्ण

GXBB_AO_GATE(remote, 0);
GXBB_AO_GATE(i2c_master, 1);
GXBB_AO_GATE(i2c_slave, 2);
GXBB_AO_GATE(uart1, 3);
GXBB_AO_GATE(uart2, 5);
GXBB_AO_GATE(ir_blaster, 6);

अटल काष्ठा clk_regmap ao_cts_oscin = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = AO_RTI_PWR_CNTL_REG0,
		.bit_idx = 6,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ao_cts_oscin",
		.ops = &clk_regmap_gate_ro_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			.fw_name = "xtal",
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap ao_32k_pre = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = AO_RTC_ALT_CLK_CNTL0,
		.bit_idx = 31,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ao_32k_pre",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &ao_cts_oscin.hw पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा meson_clk_duaद_भाग_param gxbb_32k_भाग_प्रकारable[] = अणु
	अणु
		.dual	= 1,
		.n1	= 733,
		.m1	= 8,
		.n2	= 732,
		.m2	= 11,
	पूर्ण, अणुपूर्ण
पूर्ण;

अटल काष्ठा clk_regmap ao_32k_भाग = अणु
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
		.table = gxbb_32k_भाग_प्रकारable,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ao_32k_div",
		.ops = &meson_clk_duaद_भाग_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &ao_32k_pre.hw पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap ao_32k_sel = अणु
	.data = &(काष्ठा clk_regmap_mux_data) अणु
		.offset = AO_RTC_ALT_CLK_CNTL1,
		.mask = 0x1,
		.shअगरt = 24,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ao_32k_sel",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&ao_32k_भाग.hw,
			&ao_32k_pre.hw
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap ao_32k = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = AO_RTC_ALT_CLK_CNTL0,
		.bit_idx = 30,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ao_32k",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु &ao_32k_sel.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap ao_cts_rtc_oscin = अणु
	.data = &(काष्ठा clk_regmap_mux_data) अणु
		.offset = AO_RTI_PWR_CNTL_REG0,
		.mask = 0x7,
		.shअगरt = 10,
		.table = (u32[])अणु 1, 2, 3, 4 पूर्ण,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ao_cts_rtc_oscin",
		.ops = &clk_regmap_mux_ops,
		.parent_data = (स्थिर काष्ठा clk_parent_data []) अणु
			अणु .fw_name = "ext-32k-0", पूर्ण,
			अणु .fw_name = "ext-32k-1", पूर्ण,
			अणु .fw_name = "ext-32k-2", पूर्ण,
			अणु .hw = &ao_32k.hw पूर्ण,
		पूर्ण,
		.num_parents = 4,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap ao_clk81 = अणु
	.data = &(काष्ठा clk_regmap_mux_data) अणु
		.offset = AO_RTI_PWR_CNTL_REG0,
		.mask = 0x1,
		.shअगरt = 0,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ao_clk81",
		.ops = &clk_regmap_mux_ro_ops,
		.parent_data = (स्थिर काष्ठा clk_parent_data []) अणु
			अणु .fw_name = "mpeg-clk", पूर्ण,
			अणु .hw = &ao_cts_rtc_oscin.hw पूर्ण,
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap ao_cts_cec = अणु
	.data = &(काष्ठा clk_regmap_mux_data) अणु
		.offset = AO_CRT_CLK_CNTL1,
		.mask = 0x1,
		.shअगरt = 27,
		.flags = CLK_MUX_ROUND_CLOSEST,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ao_cts_cec",
		.ops = &clk_regmap_mux_ops,
		/*
		 * FIXME: The 'fixme' parent obviously करोes not exist.
		 *
		 * ATM, CCF won't call get_parent() अगर num_parents is 1. It
		 * करोes not allow शून्य as a parent name either.
		 *
		 * On this particular mux, we only know the input #1 parent
		 * but, on boot, unknown input #0 is set, so it is critical
		 * to call .get_parent() on it
		 *
		 * Until CCF माला_लो fixed, adding this fake parent that won't
		 * ever be रेजिस्टरed should work around the problem
		 */
		.parent_data = (स्थिर काष्ठा clk_parent_data []) अणु
			अणु .name = "fixme", .index = -1, पूर्ण,
			अणु .hw = &ao_cts_rtc_oscin.hw पूर्ण,
		पूर्ण,
		.num_parents = 2,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक gxbb_aoclk_reset[] = अणु
	[RESET_AO_REMOTE] = 16,
	[RESET_AO_I2C_MASTER] = 18,
	[RESET_AO_I2C_SLAVE] = 19,
	[RESET_AO_UART1] = 17,
	[RESET_AO_UART2] = 22,
	[RESET_AO_IR_BLASTER] = 23,
पूर्ण;

अटल काष्ठा clk_regmap *gxbb_aoclk[] = अणु
	&remote_ao,
	&i2c_master_ao,
	&i2c_slave_ao,
	&uart1_ao,
	&uart2_ao,
	&ir_blaster_ao,
	&ao_cts_oscin,
	&ao_32k_pre,
	&ao_32k_भाग,
	&ao_32k_sel,
	&ao_32k,
	&ao_cts_rtc_oscin,
	&ao_clk81,
	&ao_cts_cec,
पूर्ण;

अटल स्थिर काष्ठा clk_hw_onecell_data gxbb_aoclk_onecell_data = अणु
	.hws = अणु
		[CLKID_AO_REMOTE] = &remote_ao.hw,
		[CLKID_AO_I2C_MASTER] = &i2c_master_ao.hw,
		[CLKID_AO_I2C_SLAVE] = &i2c_slave_ao.hw,
		[CLKID_AO_UART1] = &uart1_ao.hw,
		[CLKID_AO_UART2] = &uart2_ao.hw,
		[CLKID_AO_IR_BLASTER] = &ir_blaster_ao.hw,
		[CLKID_AO_CEC_32K] = &ao_cts_cec.hw,
		[CLKID_AO_CTS_OSCIN] = &ao_cts_oscin.hw,
		[CLKID_AO_32K_PRE] = &ao_32k_pre.hw,
		[CLKID_AO_32K_DIV] = &ao_32k_भाग.hw,
		[CLKID_AO_32K_SEL] = &ao_32k_sel.hw,
		[CLKID_AO_32K] = &ao_32k.hw,
		[CLKID_AO_CTS_RTC_OSCIN] = &ao_cts_rtc_oscin.hw,
		[CLKID_AO_CLK81] = &ao_clk81.hw,
	पूर्ण,
	.num = NR_CLKS,
पूर्ण;

अटल स्थिर काष्ठा meson_aoclk_data gxbb_aoclkc_data = अणु
	.reset_reg	= AO_RTI_GEN_CNTL_REG0,
	.num_reset	= ARRAY_SIZE(gxbb_aoclk_reset),
	.reset		= gxbb_aoclk_reset,
	.num_clks	= ARRAY_SIZE(gxbb_aoclk),
	.clks		= gxbb_aoclk,
	.hw_data	= &gxbb_aoclk_onecell_data,
पूर्ण;

अटल स्थिर काष्ठा of_device_id gxbb_aoclkc_match_table[] = अणु
	अणु
		.compatible	= "amlogic,meson-gx-aoclkc",
		.data		= &gxbb_aoclkc_data,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gxbb_aoclkc_match_table);

अटल काष्ठा platक्रमm_driver gxbb_aoclkc_driver = अणु
	.probe		= meson_aoclkc_probe,
	.driver		= अणु
		.name	= "gxbb-aoclkc",
		.of_match_table = gxbb_aoclkc_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(gxbb_aoclkc_driver);
MODULE_LICENSE("GPL v2");
