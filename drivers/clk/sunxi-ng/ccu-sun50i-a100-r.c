<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020 Yangtao Li <frank@allwinnertech.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "ccu_common.h"
#समावेश "ccu_reset.h"

#समावेश "ccu_div.h"
#समावेश "ccu_gate.h"
#समावेश "ccu_mp.h"
#समावेश "ccu_nm.h"

#समावेश "ccu-sun50i-a100-r.h"

अटल स्थिर अक्षर * स्थिर cpus_r_apb2_parents[] = अणु "dcxo24M", "osc32k",
						     "iosc", "pll-periph0" पूर्ण;
अटल स्थिर काष्ठा ccu_mux_var_preभाग cpus_r_apb2_preभागs[] = अणु
	अणु .index = 3, .shअगरt = 0, .width = 5 पूर्ण,
पूर्ण;

अटल काष्ठा ccu_भाग r_cpus_clk = अणु
	.भाग		= _SUNXI_CCU_DIV_FLAGS(8, 2, CLK_DIVIDER_POWER_OF_TWO),

	.mux		= अणु
		.shअगरt	= 24,
		.width	= 2,

		.var_preभागs	= cpus_r_apb2_preभागs,
		.n_var_preभागs	= ARRAY_SIZE(cpus_r_apb2_preभागs),
	पूर्ण,

	.common		= अणु
		.reg		= 0x000,
		.features	= CCU_FEATURE_VARIABLE_PREDIV,
		.hw.init	= CLK_HW_INIT_PARENTS("cpus",
						      cpus_r_apb2_parents,
						      &ccu_भाग_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल CLK_FIXED_FACTOR_HW(r_ahb_clk, "r-ahb", &r_cpus_clk.common.hw, 1, 1, 0);

अटल काष्ठा ccu_भाग r_apb1_clk = अणु
	.भाग		= _SUNXI_CCU_DIV(0, 2),

	.common		= अणु
		.reg		= 0x00c,
		.hw.init	= CLK_HW_INIT("r-apb1",
					      "r-ahb",
					      &ccu_भाग_ops,
					      0),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_भाग r_apb2_clk = अणु
	.भाग		= _SUNXI_CCU_DIV_FLAGS(8, 2, CLK_DIVIDER_POWER_OF_TWO),

	.mux		= अणु
		.shअगरt	= 24,
		.width	= 2,

		.var_preभागs	= cpus_r_apb2_preभागs,
		.n_var_preभागs	= ARRAY_SIZE(cpus_r_apb2_preभागs),
	पूर्ण,

	.common		= अणु
		.reg		= 0x010,
		.features	= CCU_FEATURE_VARIABLE_PREDIV,
		.hw.init	= CLK_HW_INIT_PARENTS("r-apb2",
						      cpus_r_apb2_parents,
						      &ccu_भाग_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data clk_parent_r_apb1[] = अणु
	अणु .hw = &r_apb1_clk.common.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data clk_parent_r_apb2[] = अणु
	अणु .hw = &r_apb2_clk.common.hw पूर्ण,
पूर्ण;

अटल SUNXI_CCU_GATE_DATA(r_apb1_समयr_clk, "r-apb1-timer", clk_parent_r_apb1,
			   0x11c, BIT(0), 0);

अटल SUNXI_CCU_GATE_DATA(r_apb1_twd_clk, "r-apb1-twd", clk_parent_r_apb1,
			   0x12c, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर r_apb1_pwm_clk_parents[] = अणु "dcxo24M", "osc32k",
						       "iosc" पूर्ण;
अटल SUNXI_CCU_MUX(r_apb1_pwm_clk, "r-apb1-pwm", r_apb1_pwm_clk_parents,
		     0x130, 24, 2, 0);

अटल SUNXI_CCU_GATE_DATA(r_apb1_bus_pwm_clk, "r-apb1-bus-pwm",
			   clk_parent_r_apb1, 0x13c, BIT(0), 0);

अटल SUNXI_CCU_GATE_DATA(r_apb1_ppu_clk, "r-apb1-ppu", clk_parent_r_apb1,
			   0x17c, BIT(0), 0);

अटल SUNXI_CCU_GATE_DATA(r_apb2_uart_clk, "r-apb2-uart", clk_parent_r_apb2,
			   0x18c, BIT(0), 0);

अटल SUNXI_CCU_GATE_DATA(r_apb2_i2c0_clk, "r-apb2-i2c0", clk_parent_r_apb2,
			   0x19c, BIT(0), 0);

अटल SUNXI_CCU_GATE_DATA(r_apb2_i2c1_clk, "r-apb2-i2c1", clk_parent_r_apb2,
			   0x19c, BIT(1), 0);

अटल स्थिर अक्षर * स्थिर r_apb1_ir_rx_parents[] = अणु "osc32k", "dcxo24M" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX_GATE(r_apb1_ir_rx_clk, "r-apb1-ir-rx",
				  r_apb1_ir_rx_parents, 0x1c0,
				  0, 5,		/* M */
				  8, 2,		/* P */
				  24, 1,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_GATE_DATA(r_apb1_bus_ir_rx_clk, "r-apb1-bus-ir-rx",
			   clk_parent_r_apb1, 0x1cc, BIT(0), 0);

अटल SUNXI_CCU_GATE(r_ahb_bus_rtc_clk, "r-ahb-rtc", "r-ahb",
		      0x20c, BIT(0), 0);

अटल काष्ठा ccu_common *sun50i_a100_r_ccu_clks[] = अणु
	&r_cpus_clk.common,
	&r_apb1_clk.common,
	&r_apb2_clk.common,
	&r_apb1_समयr_clk.common,
	&r_apb1_twd_clk.common,
	&r_apb1_pwm_clk.common,
	&r_apb1_bus_pwm_clk.common,
	&r_apb1_ppu_clk.common,
	&r_apb2_uart_clk.common,
	&r_apb2_i2c0_clk.common,
	&r_apb2_i2c1_clk.common,
	&r_apb1_ir_rx_clk.common,
	&r_apb1_bus_ir_rx_clk.common,
	&r_ahb_bus_rtc_clk.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sun50i_a100_r_hw_clks = अणु
	.hws	= अणु
		[CLK_R_CPUS]		= &r_cpus_clk.common.hw,
		[CLK_R_AHB]		= &r_ahb_clk.hw,
		[CLK_R_APB1]		= &r_apb1_clk.common.hw,
		[CLK_R_APB2]		= &r_apb2_clk.common.hw,
		[CLK_R_APB1_TIMER]	= &r_apb1_समयr_clk.common.hw,
		[CLK_R_APB1_TWD]	= &r_apb1_twd_clk.common.hw,
		[CLK_R_APB1_PWM]	= &r_apb1_pwm_clk.common.hw,
		[CLK_R_APB1_BUS_PWM]	= &r_apb1_bus_pwm_clk.common.hw,
		[CLK_R_APB1_PPU]	= &r_apb1_ppu_clk.common.hw,
		[CLK_R_APB2_UART]	= &r_apb2_uart_clk.common.hw,
		[CLK_R_APB2_I2C0]	= &r_apb2_i2c0_clk.common.hw,
		[CLK_R_APB2_I2C1]	= &r_apb2_i2c1_clk.common.hw,
		[CLK_R_APB1_IR]		= &r_apb1_ir_rx_clk.common.hw,
		[CLK_R_APB1_BUS_IR]	= &r_apb1_bus_ir_rx_clk.common.hw,
		[CLK_R_AHB_BUS_RTC]	= &r_ahb_bus_rtc_clk.common.hw,
	पूर्ण,
	.num	= CLK_NUMBER,
पूर्ण;

अटल काष्ठा ccu_reset_map sun50i_a100_r_ccu_resets[] = अणु
	[RST_R_APB1_TIMER]	=  अणु 0x11c, BIT(16) पूर्ण,
	[RST_R_APB1_BUS_PWM]	=  अणु 0x13c, BIT(16) पूर्ण,
	[RST_R_APB1_PPU]	=  अणु 0x17c, BIT(16) पूर्ण,
	[RST_R_APB2_UART]	=  अणु 0x18c, BIT(16) पूर्ण,
	[RST_R_APB2_I2C0]	=  अणु 0x19c, BIT(16) पूर्ण,
	[RST_R_APB2_I2C1]	=  अणु 0x19c, BIT(17) पूर्ण,
	[RST_R_APB1_BUS_IR]	=  अणु 0x1cc, BIT(16) पूर्ण,
	[RST_R_AHB_BUS_RTC]	=  अणु 0x20c, BIT(16) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun50i_a100_r_ccu_desc = अणु
	.ccu_clks	= sun50i_a100_r_ccu_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun50i_a100_r_ccu_clks),

	.hw_clks	= &sun50i_a100_r_hw_clks,

	.resets		= sun50i_a100_r_ccu_resets,
	.num_resets	= ARRAY_SIZE(sun50i_a100_r_ccu_resets),
पूर्ण;

अटल पूर्णांक sun50i_a100_r_ccu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *reg;

	reg = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	वापस sunxi_ccu_probe(pdev->dev.of_node, reg, &sun50i_a100_r_ccu_desc);
पूर्ण

अटल स्थिर काष्ठा of_device_id sun50i_a100_r_ccu_ids[] = अणु
	अणु .compatible = "allwinner,sun50i-a100-r-ccu" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sun50i_a100_r_ccu_driver = अणु
	.probe	= sun50i_a100_r_ccu_probe,
	.driver	= अणु
		.name	= "sun50i-a100-r-ccu",
		.of_match_table	= sun50i_a100_r_ccu_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun50i_a100_r_ccu_driver);
