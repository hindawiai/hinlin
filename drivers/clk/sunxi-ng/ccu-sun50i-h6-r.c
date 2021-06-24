<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2017 Icenowy Zheng <icenowy@aosc.xyz>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "ccu_common.h"
#समावेश "ccu_reset.h"

#समावेश "ccu_div.h"
#समावेश "ccu_gate.h"
#समावेश "ccu_mp.h"
#समावेश "ccu_nm.h"

#समावेश "ccu-sun50i-h6-r.h"

/*
 * Inक्रमmation about AR100 and AHB/APB घड़ीs in R_CCU are gathered from
 * घड़ी definitions in the BSP source code.
 */

अटल स्थिर अक्षर * स्थिर ar100_r_apb2_parents[] = अणु "osc24M", "osc32k",
						     "iosc", "pll-periph0" पूर्ण;
अटल स्थिर काष्ठा ccu_mux_var_preभाग ar100_r_apb2_preभागs[] = अणु
	अणु .index = 3, .shअगरt = 0, .width = 5 पूर्ण,
पूर्ण;

अटल काष्ठा ccu_भाग ar100_clk = अणु
	.भाग		= _SUNXI_CCU_DIV_FLAGS(8, 2, CLK_DIVIDER_POWER_OF_TWO),

	.mux		= अणु
		.shअगरt	= 24,
		.width	= 2,

		.var_preभागs	= ar100_r_apb2_preभागs,
		.n_var_preभागs	= ARRAY_SIZE(ar100_r_apb2_preभागs),
	पूर्ण,

	.common		= अणु
		.reg		= 0x000,
		.features	= CCU_FEATURE_VARIABLE_PREDIV,
		.hw.init	= CLK_HW_INIT_PARENTS("ar100",
						      ar100_r_apb2_parents,
						      &ccu_भाग_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल CLK_FIXED_FACTOR_HW(r_ahb_clk, "r-ahb", &ar100_clk.common.hw, 1, 1, 0);

अटल SUNXI_CCU_M(r_apb1_clk, "r-apb1", "r-ahb", 0x00c, 0, 2, 0);

अटल काष्ठा ccu_भाग r_apb2_clk = अणु
	.भाग		= _SUNXI_CCU_DIV_FLAGS(8, 2, CLK_DIVIDER_POWER_OF_TWO),

	.mux		= अणु
		.shअगरt	= 24,
		.width	= 2,

		.var_preभागs	= ar100_r_apb2_preभागs,
		.n_var_preभागs	= ARRAY_SIZE(ar100_r_apb2_preभागs),
	पूर्ण,

	.common		= अणु
		.reg		= 0x010,
		.features	= CCU_FEATURE_VARIABLE_PREDIV,
		.hw.init	= CLK_HW_INIT_PARENTS("r-apb2",
						      ar100_r_apb2_parents,
						      &ccu_भाग_ops,
						      0),
	पूर्ण,
पूर्ण;

/*
 * Inक्रमmation about the gate/resets are gathered from the घड़ी header file
 * in the BSP source code, although most of them are unused. The existence
 * of the hardware block is verअगरied with "3.1 Memory Mapping" chapter in
 * "Allwinner H6 V200 User Manual V1.1"; and the parent APB buses are verअगरied
 * with "3.3.2.1 System Bus Tree" chapter पूर्णांकhe same करोcument.
 */
अटल SUNXI_CCU_GATE(r_apb1_समयr_clk,	"r-apb1-timer",	"r-apb1",
		      0x11c, BIT(0), 0);
अटल SUNXI_CCU_GATE(r_apb1_twd_clk,	"r-apb1-twd",	"r-apb1",
		      0x12c, BIT(0), 0);
अटल SUNXI_CCU_GATE(r_apb1_pwm_clk,	"r-apb1-pwm",	"r-apb1",
		      0x13c, BIT(0), 0);
अटल SUNXI_CCU_GATE(r_apb2_uart_clk,	"r-apb2-uart",	"r-apb2",
		      0x18c, BIT(0), 0);
अटल SUNXI_CCU_GATE(r_apb2_i2c_clk,	"r-apb2-i2c",	"r-apb2",
		      0x19c, BIT(0), 0);
अटल SUNXI_CCU_GATE(r_apb2_rsb_clk,	"r-apb2-rsb",	"r-apb2",
		      0x1bc, BIT(0), 0);
अटल SUNXI_CCU_GATE(r_apb1_ir_clk,	"r-apb1-ir",	"r-apb1",
		      0x1cc, BIT(0), 0);
अटल SUNXI_CCU_GATE(r_apb1_w1_clk,	"r-apb1-w1",	"r-apb1",
		      0x1ec, BIT(0), 0);

/* Inक्रमmation of IR(RX) mod घड़ी is gathered from BSP source code */
अटल स्थिर अक्षर * स्थिर r_mod0_शेष_parents[] = अणु "osc32k", "osc24M" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX_GATE(ir_clk, "ir",
				  r_mod0_शेष_parents, 0x1c0,
				  0, 5,		/* M */
				  8, 2,		/* P */
				  24, 1,	/* mux */
				  BIT(31),	/* gate */
				  0);

/*
 * BSP didn't use the 1-wire function at all now, and the inक्रमmation about
 * this mod घड़ी is guessed from the IR mod घड़ी above. The existence of
 * this mod घड़ी is proven by BSP घड़ी header, and the भागiders are verअगरied
 * by contents in the 1-wire related chapter of the User Manual.
 */

अटल SUNXI_CCU_MP_WITH_MUX_GATE(w1_clk, "w1",
				  r_mod0_शेष_parents, 0x1e0,
				  0, 5,		/* M */
				  8, 2,		/* P */
				  24, 1,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल काष्ठा ccu_common *sun50i_h6_r_ccu_clks[] = अणु
	&ar100_clk.common,
	&r_apb1_clk.common,
	&r_apb2_clk.common,
	&r_apb1_समयr_clk.common,
	&r_apb1_twd_clk.common,
	&r_apb1_pwm_clk.common,
	&r_apb2_uart_clk.common,
	&r_apb2_i2c_clk.common,
	&r_apb2_rsb_clk.common,
	&r_apb1_ir_clk.common,
	&r_apb1_w1_clk.common,
	&ir_clk.common,
	&w1_clk.common,
पूर्ण;

अटल काष्ठा ccu_common *sun50i_h616_r_ccu_clks[] = अणु
	&r_apb1_clk.common,
	&r_apb2_clk.common,
	&r_apb1_twd_clk.common,
	&r_apb2_i2c_clk.common,
	&r_apb2_rsb_clk.common,
	&r_apb1_ir_clk.common,
	&ir_clk.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sun50i_h6_r_hw_clks = अणु
	.hws	= अणु
		[CLK_AR100]		= &ar100_clk.common.hw,
		[CLK_R_AHB]		= &r_ahb_clk.hw,
		[CLK_R_APB1]		= &r_apb1_clk.common.hw,
		[CLK_R_APB2]		= &r_apb2_clk.common.hw,
		[CLK_R_APB1_TIMER]	= &r_apb1_समयr_clk.common.hw,
		[CLK_R_APB1_TWD]	= &r_apb1_twd_clk.common.hw,
		[CLK_R_APB1_PWM]	= &r_apb1_pwm_clk.common.hw,
		[CLK_R_APB2_UART]	= &r_apb2_uart_clk.common.hw,
		[CLK_R_APB2_I2C]	= &r_apb2_i2c_clk.common.hw,
		[CLK_R_APB2_RSB]	= &r_apb2_rsb_clk.common.hw,
		[CLK_R_APB1_IR]		= &r_apb1_ir_clk.common.hw,
		[CLK_R_APB1_W1]		= &r_apb1_w1_clk.common.hw,
		[CLK_IR]		= &ir_clk.common.hw,
		[CLK_W1]		= &w1_clk.common.hw,
	पूर्ण,
	.num	= CLK_NUMBER,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sun50i_h616_r_hw_clks = अणु
	.hws	= अणु
		[CLK_R_AHB]		= &r_ahb_clk.hw,
		[CLK_R_APB1]		= &r_apb1_clk.common.hw,
		[CLK_R_APB2]		= &r_apb2_clk.common.hw,
		[CLK_R_APB1_TWD]	= &r_apb1_twd_clk.common.hw,
		[CLK_R_APB2_I2C]	= &r_apb2_i2c_clk.common.hw,
		[CLK_R_APB2_RSB]	= &r_apb2_rsb_clk.common.hw,
		[CLK_R_APB1_IR]		= &r_apb1_ir_clk.common.hw,
		[CLK_IR]		= &ir_clk.common.hw,
	पूर्ण,
	.num	= CLK_NUMBER,
पूर्ण;

अटल काष्ठा ccu_reset_map sun50i_h6_r_ccu_resets[] = अणु
	[RST_R_APB1_TIMER]	=  अणु 0x11c, BIT(16) पूर्ण,
	[RST_R_APB1_TWD]	=  अणु 0x12c, BIT(16) पूर्ण,
	[RST_R_APB1_PWM]	=  अणु 0x13c, BIT(16) पूर्ण,
	[RST_R_APB2_UART]	=  अणु 0x18c, BIT(16) पूर्ण,
	[RST_R_APB2_I2C]	=  अणु 0x19c, BIT(16) पूर्ण,
	[RST_R_APB2_RSB]	=  अणु 0x1bc, BIT(16) पूर्ण,
	[RST_R_APB1_IR]		=  अणु 0x1cc, BIT(16) पूर्ण,
	[RST_R_APB1_W1]		=  अणु 0x1ec, BIT(16) पूर्ण,
पूर्ण;

अटल काष्ठा ccu_reset_map sun50i_h616_r_ccu_resets[] = अणु
	[RST_R_APB1_TWD]	=  अणु 0x12c, BIT(16) पूर्ण,
	[RST_R_APB2_I2C]	=  अणु 0x19c, BIT(16) पूर्ण,
	[RST_R_APB2_RSB]	=  अणु 0x1bc, BIT(16) पूर्ण,
	[RST_R_APB1_IR]		=  अणु 0x1cc, BIT(16) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun50i_h6_r_ccu_desc = अणु
	.ccu_clks	= sun50i_h6_r_ccu_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun50i_h6_r_ccu_clks),

	.hw_clks	= &sun50i_h6_r_hw_clks,

	.resets		= sun50i_h6_r_ccu_resets,
	.num_resets	= ARRAY_SIZE(sun50i_h6_r_ccu_resets),
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun50i_h616_r_ccu_desc = अणु
	.ccu_clks	= sun50i_h616_r_ccu_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun50i_h616_r_ccu_clks),

	.hw_clks	= &sun50i_h616_r_hw_clks,

	.resets		= sun50i_h616_r_ccu_resets,
	.num_resets	= ARRAY_SIZE(sun50i_h616_r_ccu_resets),
पूर्ण;

अटल व्योम __init sunxi_r_ccu_init(काष्ठा device_node *node,
				    स्थिर काष्ठा sunxi_ccu_desc *desc)
अणु
	व्योम __iomem *reg;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg)) अणु
		pr_err("%pOF: Could not map the clock registers\n", node);
		वापस;
	पूर्ण

	sunxi_ccu_probe(node, reg, desc);
पूर्ण

अटल व्योम __init sun50i_h6_r_ccu_setup(काष्ठा device_node *node)
अणु
	sunxi_r_ccu_init(node, &sun50i_h6_r_ccu_desc);
पूर्ण
CLK_OF_DECLARE(sun50i_h6_r_ccu, "allwinner,sun50i-h6-r-ccu",
	       sun50i_h6_r_ccu_setup);

अटल व्योम __init sun50i_h616_r_ccu_setup(काष्ठा device_node *node)
अणु
	sunxi_r_ccu_init(node, &sun50i_h616_r_ccu_desc);
पूर्ण
CLK_OF_DECLARE(sun50i_h616_r_ccu, "allwinner,sun50i-h616-r-ccu",
	       sun50i_h616_r_ccu_setup);
