<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 Icenowy Zheng <icenowy@aosc.xyz>
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

#समावेश "ccu-sun8i-r.h"

अटल स्थिर काष्ठा clk_parent_data ar100_parents[] = अणु
	अणु .fw_name = "losc" पूर्ण,
	अणु .fw_name = "hosc" पूर्ण,
	अणु .fw_name = "pll-periph" पूर्ण,
	अणु .fw_name = "iosc" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ccu_mux_var_preभाग ar100_preभागs[] = अणु
	अणु .index = 2, .shअगरt = 8, .width = 5 पूर्ण,
पूर्ण;

अटल काष्ठा ccu_भाग ar100_clk = अणु
	.भाग		= _SUNXI_CCU_DIV_FLAGS(4, 2, CLK_DIVIDER_POWER_OF_TWO),

	.mux		= अणु
		.shअगरt	= 16,
		.width	= 2,

		.var_preभागs	= ar100_preभागs,
		.n_var_preभागs	= ARRAY_SIZE(ar100_preभागs),
	पूर्ण,

	.common		= अणु
		.reg		= 0x00,
		.features	= CCU_FEATURE_VARIABLE_PREDIV,
		.hw.init	= CLK_HW_INIT_PARENTS_DATA("ar100",
							   ar100_parents,
							   &ccu_भाग_ops,
							   0),
	पूर्ण,
पूर्ण;

अटल CLK_FIXED_FACTOR_HW(ahb0_clk, "ahb0", &ar100_clk.common.hw, 1, 1, 0);

अटल SUNXI_CCU_M(apb0_clk, "apb0", "ahb0", 0x0c, 0, 2, 0);

/*
 * Define the parent as an array that can be reused to save space
 * instead of having compound literals क्रम each gate. Also have it
 * non-स्थिर so we can change it on the A83T.
 */
अटल स्थिर काष्ठा clk_hw *apb0_gate_parent[] = अणु &apb0_clk.common.hw पूर्ण;
अटल SUNXI_CCU_GATE_HWS(apb0_pio_clk,		"apb0-pio",
			  apb0_gate_parent, 0x28, BIT(0), 0);
अटल SUNXI_CCU_GATE_HWS(apb0_ir_clk,		"apb0-ir",
			  apb0_gate_parent, 0x28, BIT(1), 0);
अटल SUNXI_CCU_GATE_HWS(apb0_समयr_clk,	"apb0-timer",
			  apb0_gate_parent, 0x28, BIT(2), 0);
अटल SUNXI_CCU_GATE_HWS(apb0_rsb_clk,		"apb0-rsb",
			  apb0_gate_parent, 0x28, BIT(3), 0);
अटल SUNXI_CCU_GATE_HWS(apb0_uart_clk,	"apb0-uart",
			  apb0_gate_parent, 0x28, BIT(4), 0);
अटल SUNXI_CCU_GATE_HWS(apb0_i2c_clk,		"apb0-i2c",
			  apb0_gate_parent, 0x28, BIT(6), 0);
अटल SUNXI_CCU_GATE_HWS(apb0_twd_clk,		"apb0-twd",
			  apb0_gate_parent, 0x28, BIT(7), 0);

अटल स्थिर अक्षर * स्थिर r_mod0_शेष_parents[] = अणु "osc32k", "osc24M" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX_GATE(ir_clk, "ir",
				  r_mod0_शेष_parents, 0x54,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल स्थिर काष्ठा clk_parent_data a83t_r_mod0_parents[] = अणु
	अणु .fw_name = "iosc" पूर्ण,
	अणु .fw_name = "hosc" पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा ccu_mux_fixed_preभाग a83t_ir_preभागs[] = अणु
	अणु .index = 0, .भाग = 16 पूर्ण,
पूर्ण;
अटल काष्ठा ccu_mp a83t_ir_clk = अणु
	.enable	= BIT(31),

	.m	= _SUNXI_CCU_DIV(0, 4),
	.p	= _SUNXI_CCU_DIV(16, 2),

	.mux	= अणु
		.shअगरt	= 24,
		.width	= 2,
		.fixed_preभागs	= a83t_ir_preभागs,
		.n_preभागs	= ARRAY_SIZE(a83t_ir_preभागs),
	पूर्ण,

	.common		= अणु
		.reg		= 0x54,
		.features	= CCU_FEATURE_VARIABLE_PREDIV,
		.hw.init	= CLK_HW_INIT_PARENTS_DATA("ir",
							   a83t_r_mod0_parents,
							   &ccu_mp_ops,
							   0),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_common *sun8i_a83t_r_ccu_clks[] = अणु
	&ar100_clk.common,
	&apb0_clk.common,
	&apb0_pio_clk.common,
	&apb0_ir_clk.common,
	&apb0_समयr_clk.common,
	&apb0_rsb_clk.common,
	&apb0_uart_clk.common,
	&apb0_i2c_clk.common,
	&apb0_twd_clk.common,
	&a83t_ir_clk.common,
पूर्ण;

अटल काष्ठा ccu_common *sun8i_h3_r_ccu_clks[] = अणु
	&ar100_clk.common,
	&apb0_clk.common,
	&apb0_pio_clk.common,
	&apb0_ir_clk.common,
	&apb0_समयr_clk.common,
	&apb0_uart_clk.common,
	&apb0_i2c_clk.common,
	&apb0_twd_clk.common,
	&ir_clk.common,
पूर्ण;

अटल काष्ठा ccu_common *sun50i_a64_r_ccu_clks[] = अणु
	&ar100_clk.common,
	&apb0_clk.common,
	&apb0_pio_clk.common,
	&apb0_ir_clk.common,
	&apb0_समयr_clk.common,
	&apb0_rsb_clk.common,
	&apb0_uart_clk.common,
	&apb0_i2c_clk.common,
	&apb0_twd_clk.common,
	&ir_clk.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sun8i_a83t_r_hw_clks = अणु
	.hws	= अणु
		[CLK_AR100]		= &ar100_clk.common.hw,
		[CLK_AHB0]		= &ahb0_clk.hw,
		[CLK_APB0]		= &apb0_clk.common.hw,
		[CLK_APB0_PIO]		= &apb0_pio_clk.common.hw,
		[CLK_APB0_IR]		= &apb0_ir_clk.common.hw,
		[CLK_APB0_TIMER]	= &apb0_समयr_clk.common.hw,
		[CLK_APB0_RSB]		= &apb0_rsb_clk.common.hw,
		[CLK_APB0_UART]		= &apb0_uart_clk.common.hw,
		[CLK_APB0_I2C]		= &apb0_i2c_clk.common.hw,
		[CLK_APB0_TWD]		= &apb0_twd_clk.common.hw,
		[CLK_IR]		= &a83t_ir_clk.common.hw,
	पूर्ण,
	.num	= CLK_NUMBER,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sun8i_h3_r_hw_clks = अणु
	.hws	= अणु
		[CLK_AR100]		= &ar100_clk.common.hw,
		[CLK_AHB0]		= &ahb0_clk.hw,
		[CLK_APB0]		= &apb0_clk.common.hw,
		[CLK_APB0_PIO]		= &apb0_pio_clk.common.hw,
		[CLK_APB0_IR]		= &apb0_ir_clk.common.hw,
		[CLK_APB0_TIMER]	= &apb0_समयr_clk.common.hw,
		[CLK_APB0_UART]		= &apb0_uart_clk.common.hw,
		[CLK_APB0_I2C]		= &apb0_i2c_clk.common.hw,
		[CLK_APB0_TWD]		= &apb0_twd_clk.common.hw,
		[CLK_IR]		= &ir_clk.common.hw,
	पूर्ण,
	.num	= CLK_NUMBER,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sun50i_a64_r_hw_clks = अणु
	.hws	= अणु
		[CLK_AR100]		= &ar100_clk.common.hw,
		[CLK_AHB0]		= &ahb0_clk.hw,
		[CLK_APB0]		= &apb0_clk.common.hw,
		[CLK_APB0_PIO]		= &apb0_pio_clk.common.hw,
		[CLK_APB0_IR]		= &apb0_ir_clk.common.hw,
		[CLK_APB0_TIMER]	= &apb0_समयr_clk.common.hw,
		[CLK_APB0_RSB]		= &apb0_rsb_clk.common.hw,
		[CLK_APB0_UART]		= &apb0_uart_clk.common.hw,
		[CLK_APB0_I2C]		= &apb0_i2c_clk.common.hw,
		[CLK_APB0_TWD]		= &apb0_twd_clk.common.hw,
		[CLK_IR]		= &ir_clk.common.hw,
	पूर्ण,
	.num	= CLK_NUMBER,
पूर्ण;

अटल काष्ठा ccu_reset_map sun8i_a83t_r_ccu_resets[] = अणु
	[RST_APB0_IR]		=  अणु 0xb0, BIT(1) पूर्ण,
	[RST_APB0_TIMER]	=  अणु 0xb0, BIT(2) पूर्ण,
	[RST_APB0_RSB]		=  अणु 0xb0, BIT(3) पूर्ण,
	[RST_APB0_UART]		=  अणु 0xb0, BIT(4) पूर्ण,
	[RST_APB0_I2C]		=  अणु 0xb0, BIT(6) पूर्ण,
पूर्ण;

अटल काष्ठा ccu_reset_map sun8i_h3_r_ccu_resets[] = अणु
	[RST_APB0_IR]		=  अणु 0xb0, BIT(1) पूर्ण,
	[RST_APB0_TIMER]	=  अणु 0xb0, BIT(2) पूर्ण,
	[RST_APB0_UART]		=  अणु 0xb0, BIT(4) पूर्ण,
	[RST_APB0_I2C]		=  अणु 0xb0, BIT(6) पूर्ण,
पूर्ण;

अटल काष्ठा ccu_reset_map sun50i_a64_r_ccu_resets[] = अणु
	[RST_APB0_IR]		=  अणु 0xb0, BIT(1) पूर्ण,
	[RST_APB0_TIMER]	=  अणु 0xb0, BIT(2) पूर्ण,
	[RST_APB0_RSB]		=  अणु 0xb0, BIT(3) पूर्ण,
	[RST_APB0_UART]		=  अणु 0xb0, BIT(4) पूर्ण,
	[RST_APB0_I2C]		=  अणु 0xb0, BIT(6) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun8i_a83t_r_ccu_desc = अणु
	.ccu_clks	= sun8i_a83t_r_ccu_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun8i_a83t_r_ccu_clks),

	.hw_clks	= &sun8i_a83t_r_hw_clks,

	.resets		= sun8i_a83t_r_ccu_resets,
	.num_resets	= ARRAY_SIZE(sun8i_a83t_r_ccu_resets),
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun8i_h3_r_ccu_desc = अणु
	.ccu_clks	= sun8i_h3_r_ccu_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun8i_h3_r_ccu_clks),

	.hw_clks	= &sun8i_h3_r_hw_clks,

	.resets		= sun8i_h3_r_ccu_resets,
	.num_resets	= ARRAY_SIZE(sun8i_h3_r_ccu_resets),
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun50i_a64_r_ccu_desc = अणु
	.ccu_clks	= sun50i_a64_r_ccu_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun50i_a64_r_ccu_clks),

	.hw_clks	= &sun50i_a64_r_hw_clks,

	.resets		= sun50i_a64_r_ccu_resets,
	.num_resets	= ARRAY_SIZE(sun50i_a64_r_ccu_resets),
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

अटल व्योम __init sun8i_a83t_r_ccu_setup(काष्ठा device_node *node)
अणु
	sunxi_r_ccu_init(node, &sun8i_a83t_r_ccu_desc);
पूर्ण
CLK_OF_DECLARE(sun8i_a83t_r_ccu, "allwinner,sun8i-a83t-r-ccu",
	       sun8i_a83t_r_ccu_setup);

अटल व्योम __init sun8i_h3_r_ccu_setup(काष्ठा device_node *node)
अणु
	sunxi_r_ccu_init(node, &sun8i_h3_r_ccu_desc);
पूर्ण
CLK_OF_DECLARE(sun8i_h3_r_ccu, "allwinner,sun8i-h3-r-ccu",
	       sun8i_h3_r_ccu_setup);

अटल व्योम __init sun50i_a64_r_ccu_setup(काष्ठा device_node *node)
अणु
	sunxi_r_ccu_init(node, &sun50i_a64_r_ccu_desc);
पूर्ण
CLK_OF_DECLARE(sun50i_a64_r_ccu, "allwinner,sun50i-a64-r-ccu",
	       sun50i_a64_r_ccu_setup);
