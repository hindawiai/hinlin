<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 Chen-Yu Tsai. All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "ccu_common.h"
#समावेश "ccu_reset.h"

#समावेश "ccu_div.h"
#समावेश "ccu_gate.h"
#समावेश "ccu_mp.h"
#समावेश "ccu_nkmp.h"
#समावेश "ccu_nm.h"
#समावेश "ccu_phase.h"

#समावेश "ccu-sun9i-a80.h"

#घोषणा CCU_SUN9I_LOCK_REG	0x09c

/*
 * The CPU PLLs are actually NP घड़ीs, with P being /1 or /4. However
 * P should only be used क्रम output frequencies lower than 228 MHz.
 * Neither मुख्यline Linux, U-boot, nor the venकरोr BSPs use these.
 *
 * For now we can just model it as a multiplier घड़ी, and क्रमce P to /1.
 */
#घोषणा SUN9I_A80_PLL_C0CPUX_REG	0x000
#घोषणा SUN9I_A80_PLL_C1CPUX_REG	0x004

अटल काष्ठा ccu_mult pll_c0cpux_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(0),
	.mult		= _SUNXI_CCU_MULT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.common		= अणु
		.reg		= SUN9I_A80_PLL_C0CPUX_REG,
		.lock_reg	= CCU_SUN9I_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-c0cpux", "osc24M",
					      &ccu_mult_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_mult pll_c1cpux_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(1),
	.mult		= _SUNXI_CCU_MULT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.common		= अणु
		.reg		= SUN9I_A80_PLL_C1CPUX_REG,
		.lock_reg	= CCU_SUN9I_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-c1cpux", "osc24M",
					      &ccu_mult_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

/*
 * The Audio PLL has d1, d2 भागiders in addition to the usual N, M
 * factors. Since we only need 2 frequencies from this PLL: 22.5792 MHz
 * and 24.576 MHz, ignore them क्रम now. Enक्रमce d1 = 0 and d2 = 0.
 */
#घोषणा SUN9I_A80_PLL_AUDIO_REG	0x008

अटल काष्ठा ccu_nm pll_audio_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(2),
	.n		= _SUNXI_CCU_MULT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV_OFFSET(0, 6, 0),
	.common		= अणु
		.reg		= 0x008,
		.lock_reg	= CCU_SUN9I_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-audio", "osc24M",
					      &ccu_nm_ops, CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

/* Some PLLs are input * N / भाग1 / भाग2. Model them as NKMP with no K */
अटल काष्ठा ccu_nkmp pll_periph0_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(3),
	.n		= _SUNXI_CCU_MULT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(18, 1), /* output भागider */
	.common		= अणु
		.reg		= 0x00c,
		.lock_reg	= CCU_SUN9I_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-periph0", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_nkmp pll_ve_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(4),
	.n		= _SUNXI_CCU_MULT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(18, 1), /* output भागider */
	.common		= अणु
		.reg		= 0x010,
		.lock_reg	= CCU_SUN9I_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-ve", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_nkmp pll_ddr_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(5),
	.n		= _SUNXI_CCU_MULT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(18, 1), /* output भागider */
	.common		= अणु
		.reg		= 0x014,
		.lock_reg	= CCU_SUN9I_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-ddr", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_nm pll_video0_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(6),
	.n		= _SUNXI_CCU_MULT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input भागider */
	.common		= अणु
		.reg		= 0x018,
		.lock_reg	= CCU_SUN9I_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-video0", "osc24M",
					      &ccu_nm_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_nkmp pll_video1_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(7),
	.n		= _SUNXI_CCU_MULT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(0, 2), /* बाह्यal भागider p */
	.common		= अणु
		.reg		= 0x01c,
		.lock_reg	= CCU_SUN9I_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-video1", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_nkmp pll_gpu_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(8),
	.n		= _SUNXI_CCU_MULT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(18, 1), /* output भागider */
	.common		= अणु
		.reg		= 0x020,
		.lock_reg	= CCU_SUN9I_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-gpu", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_nkmp pll_de_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(9),
	.n		= _SUNXI_CCU_MULT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(18, 1), /* output भागider */
	.common		= अणु
		.reg		= 0x024,
		.lock_reg	= CCU_SUN9I_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-de", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_nkmp pll_isp_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(10),
	.n		= _SUNXI_CCU_MULT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(18, 1), /* output भागider */
	.common		= अणु
		.reg		= 0x028,
		.lock_reg	= CCU_SUN9I_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-isp", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_nkmp pll_periph1_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(11),
	.n		= _SUNXI_CCU_MULT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(18, 1), /* output भागider */
	.common		= अणु
		.reg		= 0x028,
		.lock_reg	= CCU_SUN9I_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-periph1", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर c0cpux_parents[] = अणु "osc24M", "pll-c0cpux" पूर्ण;
अटल SUNXI_CCU_MUX(c0cpux_clk, "c0cpux", c0cpux_parents,
		     0x50, 0, 1, CLK_SET_RATE_PARENT | CLK_IS_CRITICAL);

अटल स्थिर अक्षर * स्थिर c1cpux_parents[] = अणु "osc24M", "pll-c1cpux" पूर्ण;
अटल SUNXI_CCU_MUX(c1cpux_clk, "c1cpux", c1cpux_parents,
		     0x50, 8, 1, CLK_SET_RATE_PARENT | CLK_IS_CRITICAL);

अटल काष्ठा clk_भाग_प्रकारable axi_भाग_प्रकारable[] = अणु
	अणु .val = 0, .भाग = 1 पूर्ण,
	अणु .val = 1, .भाग = 2 पूर्ण,
	अणु .val = 2, .भाग = 3 पूर्ण,
	अणु .val = 3, .भाग = 4 पूर्ण,
	अणु .val = 4, .भाग = 4 पूर्ण,
	अणु .val = 5, .भाग = 4 पूर्ण,
	अणु .val = 6, .भाग = 4 पूर्ण,
	अणु .val = 7, .भाग = 4 पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;

अटल SUNXI_CCU_M(atb0_clk, "atb0", "c0cpux", 0x054, 8, 2, 0);

अटल SUNXI_CCU_DIV_TABLE(axi0_clk, "axi0", "c0cpux",
			   0x054, 0, 3, axi_भाग_प्रकारable, 0);

अटल SUNXI_CCU_M(atb1_clk, "atb1", "c1cpux", 0x058, 8, 2, 0);

अटल SUNXI_CCU_DIV_TABLE(axi1_clk, "axi1", "c1cpux",
			   0x058, 0, 3, axi_भाग_प्रकारable, 0);

अटल स्थिर अक्षर * स्थिर gtbus_parents[] = अणु "osc24M", "pll-periph0",
					      "pll-periph1", "pll-periph1" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX(gtbus_clk, "gtbus", gtbus_parents,
			    0x05c, 0, 2, 24, 2, CLK_IS_CRITICAL);

अटल स्थिर अक्षर * स्थिर ahb_parents[] = अणु "gtbus", "pll-periph0",
					    "pll-periph1", "pll-periph1" पूर्ण;
अटल काष्ठा ccu_भाग ahb0_clk = अणु
	.भाग		= _SUNXI_CCU_DIV_FLAGS(0, 2, CLK_DIVIDER_POWER_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= अणु
		.reg		= 0x060,
		.hw.init	= CLK_HW_INIT_PARENTS("ahb0",
						      ahb_parents,
						      &ccu_भाग_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_भाग ahb1_clk = अणु
	.भाग		= _SUNXI_CCU_DIV_FLAGS(0, 2, CLK_DIVIDER_POWER_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= अणु
		.reg		= 0x064,
		.hw.init	= CLK_HW_INIT_PARENTS("ahb1",
						      ahb_parents,
						      &ccu_भाग_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_भाग ahb2_clk = अणु
	.भाग		= _SUNXI_CCU_DIV_FLAGS(0, 2, CLK_DIVIDER_POWER_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= अणु
		.reg		= 0x068,
		.hw.init	= CLK_HW_INIT_PARENTS("ahb2",
						      ahb_parents,
						      &ccu_भाग_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर apb_parents[] = अणु "osc24M", "pll-periph0" पूर्ण;

अटल काष्ठा ccu_भाग apb0_clk = अणु
	.भाग		= _SUNXI_CCU_DIV_FLAGS(0, 2, CLK_DIVIDER_POWER_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 1),
	.common		= अणु
		.reg		= 0x070,
		.hw.init	= CLK_HW_INIT_PARENTS("apb0",
						      apb_parents,
						      &ccu_भाग_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_भाग apb1_clk = अणु
	.भाग		= _SUNXI_CCU_DIV_FLAGS(0, 2, CLK_DIVIDER_POWER_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 1),
	.common		= अणु
		.reg		= 0x074,
		.hw.init	= CLK_HW_INIT_PARENTS("apb1",
						      apb_parents,
						      &ccu_भाग_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_भाग cci400_clk = अणु
	.भाग		= _SUNXI_CCU_DIV_FLAGS(0, 2, CLK_DIVIDER_POWER_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= अणु
		.reg		= 0x078,
		.hw.init	= CLK_HW_INIT_PARENTS("cci400",
						      ahb_parents,
						      &ccu_भाग_ops,
						      CLK_IS_CRITICAL),
	पूर्ण,
पूर्ण;

अटल SUNXI_CCU_M_WITH_MUX_GATE(ats_clk, "ats", apb_parents,
				 0x080, 0, 3, 24, 2, BIT(31), 0);

अटल SUNXI_CCU_M_WITH_MUX_GATE(trace_clk, "trace", apb_parents,
				 0x084, 0, 3, 24, 2, BIT(31), 0);

अटल स्थिर अक्षर * स्थिर out_parents[] = अणु "osc24M", "osc32k", "osc24M" पूर्ण;
अटल स्थिर काष्ठा ccu_mux_fixed_preभाग out_preभाग = अणु
	.index = 0, .भाग = 750
पूर्ण;

अटल काष्ठा ccu_mp out_a_clk = अणु
	.enable		= BIT(31),
	.m		= _SUNXI_CCU_DIV(8, 5),
	.p		= _SUNXI_CCU_DIV(20, 2),
	.mux		= अणु
		.shअगरt		= 24,
		.width		= 4,
		.fixed_preभागs	= &out_preभाग,
		.n_preभागs	= 1,
	पूर्ण,
	.common		= अणु
		.reg		= 0x180,
		.features	= CCU_FEATURE_FIXED_PREDIV,
		.hw.init	= CLK_HW_INIT_PARENTS("out-a",
						      out_parents,
						      &ccu_mp_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_mp out_b_clk = अणु
	.enable		= BIT(31),
	.m		= _SUNXI_CCU_DIV(8, 5),
	.p		= _SUNXI_CCU_DIV(20, 2),
	.mux		= अणु
		.shअगरt		= 24,
		.width		= 4,
		.fixed_preभागs	= &out_preभाग,
		.n_preभागs	= 1,
	पूर्ण,
	.common		= अणु
		.reg		= 0x184,
		.features	= CCU_FEATURE_FIXED_PREDIV,
		.hw.init	= CLK_HW_INIT_PARENTS("out-b",
						      out_parents,
						      &ccu_mp_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर mod0_शेष_parents[] = अणु "osc24M", "pll-periph0" पूर्ण;

अटल SUNXI_CCU_MP_WITH_MUX_GATE(nand0_0_clk, "nand0-0", mod0_शेष_parents,
				  0x400,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 4,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(nand0_1_clk, "nand0-1", mod0_शेष_parents,
				  0x404,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 4,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(nand1_0_clk, "nand1-0", mod0_शेष_parents,
				  0x408,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 4,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(nand1_1_clk, "nand1-1", mod0_शेष_parents,
				  0x40c,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 4,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(mmc0_clk, "mmc0", mod0_शेष_parents,
				  0x410,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 4,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_PHASE(mmc0_sample_clk, "mmc0-sample", "mmc0",
		       0x410, 20, 3, 0);
अटल SUNXI_CCU_PHASE(mmc0_output_clk, "mmc0-output", "mmc0",
		       0x410, 8, 3, 0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(mmc1_clk, "mmc1", mod0_शेष_parents,
				  0x414,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 4,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_PHASE(mmc1_sample_clk, "mmc1-sample", "mmc1",
		       0x414, 20, 3, 0);
अटल SUNXI_CCU_PHASE(mmc1_output_clk, "mmc1-output", "mmc1",
		       0x414, 8, 3, 0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(mmc2_clk, "mmc2", mod0_शेष_parents,
				  0x418,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 4,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_PHASE(mmc2_sample_clk, "mmc2-sample", "mmc2",
		       0x418, 20, 3, 0);
अटल SUNXI_CCU_PHASE(mmc2_output_clk, "mmc2-output", "mmc2",
		       0x418, 8, 3, 0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(mmc3_clk, "mmc3", mod0_शेष_parents,
				  0x41c,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 4,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_PHASE(mmc3_sample_clk, "mmc3-sample", "mmc3",
		       0x41c, 20, 3, 0);
अटल SUNXI_CCU_PHASE(mmc3_output_clk, "mmc3-output", "mmc3",
		       0x41c, 8, 3, 0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(ts_clk, "ts", mod0_शेष_parents,
				  0x428,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 4,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल स्थिर अक्षर * स्थिर ss_parents[] = अणु "osc24M", "pll-periph",
					   "pll-periph1" पूर्ण;
अटल स्थिर u8 ss_table[] = अणु 0, 1, 13 पूर्ण;
अटल काष्ठा ccu_mp ss_clk = अणु
	.enable		= BIT(31),
	.m		= _SUNXI_CCU_DIV(0, 4),
	.p		= _SUNXI_CCU_DIV(16, 2),
	.mux		= _SUNXI_CCU_MUX_TABLE(24, 4, ss_table),
	.common		= अणु
		.reg		= 0x42c,
		.hw.init	= CLK_HW_INIT_PARENTS("ss",
						      ss_parents,
						      &ccu_mp_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल SUNXI_CCU_MP_WITH_MUX_GATE(spi0_clk, "spi0", mod0_शेष_parents,
				  0x430,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 4,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(spi1_clk, "spi1", mod0_शेष_parents,
				  0x434,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 4,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(spi2_clk, "spi2", mod0_शेष_parents,
				  0x438,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 4,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(spi3_clk, "spi3", mod0_शेष_parents,
				  0x43c,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 4,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_M_WITH_GATE(i2s0_clk, "i2s0", "pll-audio",
			     0x440, 0, 4, BIT(31), CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_M_WITH_GATE(i2s1_clk, "i2s1", "pll-audio",
			     0x444, 0, 4, BIT(31), CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_M_WITH_GATE(spdअगर_clk, "spdif", "pll-audio",
			     0x44c, 0, 4, BIT(31), CLK_SET_RATE_PARENT);

अटल स्थिर अक्षर * स्थिर sdram_parents[] = अणु "pll-periph0", "pll-ddr" पूर्ण;
अटल स्थिर u8 sdram_table[] = अणु 0, 3 पूर्ण;

अटल SUNXI_CCU_M_WITH_MUX_TABLE_GATE(sdram_clk, "sdram",
				       sdram_parents, sdram_table,
				       0x484,
				       8, 4,	/* M */
				       12, 4,	/* mux */
				       0,	/* no gate */
				       CLK_IS_CRITICAL);

अटल SUNXI_CCU_M_WITH_GATE(de_clk, "de", "pll-de", 0x490,
			     0, 4, BIT(31), CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_GATE(edp_clk, "edp", "osc24M", 0x494, BIT(31), 0);

अटल स्थिर अक्षर * स्थिर mp_parents[] = अणु "pll-video1", "pll-gpu", "pll-de" पूर्ण;
अटल स्थिर u8 mp_table[] = अणु 9, 10, 11 पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_TABLE_GATE(mp_clk, "mp", mp_parents, mp_table,
				       0x498,
				       0, 4,	/* M */
				       24, 4,	/* mux */
				       BIT(31),	/* gate */
				       0);

अटल स्थिर अक्षर * स्थिर display_parents[] = अणु "pll-video0", "pll-video1" पूर्ण;
अटल स्थिर u8 display_table[] = अणु 8, 9 पूर्ण;

अटल SUNXI_CCU_M_WITH_MUX_TABLE_GATE(lcd0_clk, "lcd0",
				       display_parents, display_table,
				       0x49c,
				       0, 4,	/* M */
				       24, 4,	/* mux */
				       BIT(31),	/* gate */
				       CLK_SET_RATE_NO_REPARENT |
				       CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_M_WITH_MUX_TABLE_GATE(lcd1_clk, "lcd1",
				       display_parents, display_table,
				       0x4a0,
				       0, 4,	/* M */
				       24, 4,	/* mux */
				       BIT(31),	/* gate */
				       CLK_SET_RATE_NO_REPARENT |
				       CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_M_WITH_MUX_TABLE_GATE(mipi_dsi0_clk, "mipi-dsi0",
				       display_parents, display_table,
				       0x4a8,
				       0, 4,	/* M */
				       24, 4,	/* mux */
				       BIT(31),	/* gate */
				       CLK_SET_RATE_PARENT);

अटल स्थिर अक्षर * स्थिर mipi_dsi1_parents[] = अणु "osc24M", "pll-video1" पूर्ण;
अटल स्थिर u8 mipi_dsi1_table[] = अणु 0, 9 पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_TABLE_GATE(mipi_dsi1_clk, "mipi-dsi1",
				       mipi_dsi1_parents, mipi_dsi1_table,
				       0x4ac,
				       0, 4,	/* M */
				       24, 4,	/* mux */
				       BIT(31),	/* gate */
				       CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_M_WITH_MUX_TABLE_GATE(hdmi_clk, "hdmi",
				       display_parents, display_table,
				       0x4b0,
				       0, 4,	/* M */
				       24, 4,	/* mux */
				       BIT(31),	/* gate */
				       CLK_SET_RATE_NO_REPARENT |
				       CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_GATE(hdmi_slow_clk, "hdmi-slow", "osc24M", 0x4b4, BIT(31), 0);

अटल SUNXI_CCU_M_WITH_GATE(mipi_csi_clk, "mipi-csi", "osc24M", 0x4bc,
			     0, 4, BIT(31), 0);

अटल SUNXI_CCU_M_WITH_GATE(csi_isp_clk, "csi-isp", "pll-isp", 0x4c0,
			     0, 4, BIT(31), CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_GATE(csi_misc_clk, "csi-misc", "osc24M", 0x4c0, BIT(16), 0);

अटल SUNXI_CCU_M_WITH_MUX_TABLE_GATE(csi0_mclk_clk, "csi0-mclk",
				       mipi_dsi1_parents, mipi_dsi1_table,
				       0x4c4,
				       0, 4,	/* M */
				       24, 4,	/* mux */
				       BIT(31),	/* gate */
				       CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_M_WITH_MUX_TABLE_GATE(csi1_mclk_clk, "csi1-mclk",
				       mipi_dsi1_parents, mipi_dsi1_table,
				       0x4c8,
				       0, 4,	/* M */
				       24, 4,	/* mux */
				       BIT(31),	/* gate */
				       CLK_SET_RATE_PARENT);

अटल स्थिर अक्षर * स्थिर fd_parents[] = अणु "pll-periph0", "pll-isp" पूर्ण;
अटल स्थिर u8 fd_table[] = अणु 1, 12 पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_TABLE_GATE(fd_clk, "fd", fd_parents, fd_table,
				       0x4cc,
				       0, 4,	/* M */
				       24, 4,	/* mux */
				       BIT(31),	/* gate */
				       0);
अटल SUNXI_CCU_M_WITH_GATE(ve_clk, "ve", "pll-ve", 0x4d0,
			     16, 3, BIT(31), CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_GATE(avs_clk, "avs", "osc24M", 0x4d4, BIT(31), 0);

अटल SUNXI_CCU_M_WITH_GATE(gpu_core_clk, "gpu-core", "pll-gpu", 0x4f0,
			     0, 3, BIT(31), CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_M_WITH_GATE(gpu_memory_clk, "gpu-memory", "pll-gpu", 0x4f4,
			     0, 3, BIT(31), CLK_SET_RATE_PARENT);

अटल स्थिर अक्षर * स्थिर gpu_axi_parents[] = अणु "pll-periph0", "pll-gpu" पूर्ण;
अटल स्थिर u8 gpu_axi_table[] = अणु 1, 10 पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_TABLE_GATE(gpu_axi_clk, "gpu-axi",
				       gpu_axi_parents, gpu_axi_table,
				       0x4f8,
				       0, 4,	/* M */
				       24, 4,	/* mux */
				       BIT(31),	/* gate */
				       CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_M_WITH_GATE(sata_clk, "sata", "pll-periph0", 0x500,
			     0, 4, BIT(31), 0);

अटल SUNXI_CCU_M_WITH_GATE(ac97_clk, "ac97", "pll-audio",
			     0x504, 0, 4, BIT(31), CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_M_WITH_MUX_GATE(mipi_hsi_clk, "mipi-hsi",
				 mod0_शेष_parents, 0x508,
				 0, 4,		/* M */
				 24, 4,		/* mux */
				 BIT(31),	/* gate */
				 0);

अटल स्थिर अक्षर * स्थिर gpadc_parents[] = अणु "osc24M", "pll-audio", "osc32k" पूर्ण;
अटल स्थिर u8 gpadc_table[] = अणु 0, 4, 7 पूर्ण;
अटल काष्ठा ccu_mp gpadc_clk = अणु
	.enable		= BIT(31),
	.m		= _SUNXI_CCU_DIV(0, 4),
	.p		= _SUNXI_CCU_DIV(16, 2),
	.mux		= _SUNXI_CCU_MUX_TABLE(24, 4, gpadc_table),
	.common		= अणु
		.reg		= 0x50c,
		.hw.init	= CLK_HW_INIT_PARENTS("gpadc",
						      gpadc_parents,
						      &ccu_mp_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर cir_tx_parents[] = अणु "osc24M", "osc32k" पूर्ण;
अटल स्थिर u8 cir_tx_table[] = अणु 0, 7 पूर्ण;
अटल काष्ठा ccu_mp cir_tx_clk = अणु
	.enable		= BIT(31),
	.m		= _SUNXI_CCU_DIV(0, 4),
	.p		= _SUNXI_CCU_DIV(16, 2),
	.mux		= _SUNXI_CCU_MUX_TABLE(24, 4, cir_tx_table),
	.common		= अणु
		.reg		= 0x510,
		.hw.init	= CLK_HW_INIT_PARENTS("cir-tx",
						      cir_tx_parents,
						      &ccu_mp_ops,
						      0),
	पूर्ण,
पूर्ण;

/* AHB0 bus gates */
अटल SUNXI_CCU_GATE(bus_fd_clk,	"bus-fd",	"ahb0",
		      0x580, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_ve_clk,	"bus-ve",	"ahb0",
		      0x580, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_gpu_ctrl_clk,	"bus-gpu-ctrl",	"ahb0",
		      0x580, BIT(3), 0);
अटल SUNXI_CCU_GATE(bus_ss_clk,	"bus-ss",	"ahb0",
		      0x580, BIT(5), 0);
अटल SUNXI_CCU_GATE(bus_mmc_clk,	"bus-mmc",	"ahb0",
		      0x580, BIT(8), 0);
अटल SUNXI_CCU_GATE(bus_nand0_clk,	"bus-nand0",	"ahb0",
		      0x580, BIT(12), 0);
अटल SUNXI_CCU_GATE(bus_nand1_clk,	"bus-nand1",	"ahb0",
		      0x580, BIT(13), 0);
अटल SUNXI_CCU_GATE(bus_sdram_clk,	"bus-sdram",	"ahb0",
		      0x580, BIT(14), 0);
अटल SUNXI_CCU_GATE(bus_mipi_hsi_clk,	"bus-mipi-hsi",	"ahb0",
		      0x580, BIT(15), 0);
अटल SUNXI_CCU_GATE(bus_sata_clk,	"bus-sata",	"ahb0",
		      0x580, BIT(16), 0);
अटल SUNXI_CCU_GATE(bus_ts_clk,	"bus-ts",	"ahb0",
		      0x580, BIT(18), 0);
अटल SUNXI_CCU_GATE(bus_spi0_clk,	"bus-spi0",	"ahb0",
		      0x580, BIT(20), 0);
अटल SUNXI_CCU_GATE(bus_spi1_clk,	"bus-spi1",	"ahb0",
		      0x580, BIT(21), 0);
अटल SUNXI_CCU_GATE(bus_spi2_clk,	"bus-spi2",	"ahb0",
		      0x580, BIT(22), 0);
अटल SUNXI_CCU_GATE(bus_spi3_clk,	"bus-spi3",	"ahb0",
		      0x580, BIT(23), 0);

/* AHB1 bus gates */
अटल SUNXI_CCU_GATE(bus_otg_clk,	"bus-otg",	"ahb1",
		      0x584, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_usb_clk,	"bus-usb",	"ahb1",
		      0x584, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_gmac_clk,	"bus-gmac",	"ahb1",
		      0x584, BIT(17), 0);
अटल SUNXI_CCU_GATE(bus_msgbox_clk,	"bus-msgbox",	"ahb1",
		      0x584, BIT(21), 0);
अटल SUNXI_CCU_GATE(bus_spinlock_clk,	"bus-spinlock",	"ahb1",
		      0x584, BIT(22), 0);
अटल SUNXI_CCU_GATE(bus_hsसमयr_clk,	"bus-hstimer",	"ahb1",
		      0x584, BIT(23), 0);
अटल SUNXI_CCU_GATE(bus_dma_clk,	"bus-dma",	"ahb1",
		      0x584, BIT(24), 0);

/* AHB2 bus gates */
अटल SUNXI_CCU_GATE(bus_lcd0_clk,	"bus-lcd0",	"ahb2",
		      0x588, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_lcd1_clk,	"bus-lcd1",	"ahb2",
		      0x588, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_edp_clk,	"bus-edp",	"ahb2",
		      0x588, BIT(2), 0);
अटल SUNXI_CCU_GATE(bus_csi_clk,	"bus-csi",	"ahb2",
		      0x588, BIT(4), 0);
अटल SUNXI_CCU_GATE(bus_hdmi_clk,	"bus-hdmi",	"ahb2",
		      0x588, BIT(5), 0);
अटल SUNXI_CCU_GATE(bus_de_clk,	"bus-de",	"ahb2",
		      0x588, BIT(7), 0);
अटल SUNXI_CCU_GATE(bus_mp_clk,	"bus-mp",	"ahb2",
		      0x588, BIT(8), 0);
अटल SUNXI_CCU_GATE(bus_mipi_dsi_clk,	"bus-mipi-dsi",	"ahb2",
		      0x588, BIT(11), 0);

/* APB0 bus gates */
अटल SUNXI_CCU_GATE(bus_spdअगर_clk,	"bus-spdif",	"apb0",
		      0x590, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_pio_clk,	"bus-pio",	"apb0",
		      0x590, BIT(5), 0);
अटल SUNXI_CCU_GATE(bus_ac97_clk,	"bus-ac97",	"apb0",
		      0x590, BIT(11), 0);
अटल SUNXI_CCU_GATE(bus_i2s0_clk,	"bus-i2s0",	"apb0",
		      0x590, BIT(12), 0);
अटल SUNXI_CCU_GATE(bus_i2s1_clk,	"bus-i2s1",	"apb0",
		      0x590, BIT(13), 0);
अटल SUNXI_CCU_GATE(bus_lradc_clk,	"bus-lradc",	"apb0",
		      0x590, BIT(15), 0);
अटल SUNXI_CCU_GATE(bus_gpadc_clk,	"bus-gpadc",	"apb0",
		      0x590, BIT(17), 0);
अटल SUNXI_CCU_GATE(bus_twd_clk,	"bus-twd",	"apb0",
		      0x590, BIT(18), 0);
अटल SUNXI_CCU_GATE(bus_cir_tx_clk,	"bus-cir-tx",	"apb0",
		      0x590, BIT(19), 0);

/* APB1 bus gates */
अटल SUNXI_CCU_GATE(bus_i2c0_clk,	"bus-i2c0",	"apb1",
		      0x594, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_i2c1_clk,	"bus-i2c1",	"apb1",
		      0x594, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_i2c2_clk,	"bus-i2c2",	"apb1",
		      0x594, BIT(2), 0);
अटल SUNXI_CCU_GATE(bus_i2c3_clk,	"bus-i2c3",	"apb1",
		      0x594, BIT(3), 0);
अटल SUNXI_CCU_GATE(bus_i2c4_clk,	"bus-i2c4",	"apb1",
		      0x594, BIT(4), 0);
अटल SUNXI_CCU_GATE(bus_uart0_clk,	"bus-uart0",	"apb1",
		      0x594, BIT(16), 0);
अटल SUNXI_CCU_GATE(bus_uart1_clk,	"bus-uart1",	"apb1",
		      0x594, BIT(17), 0);
अटल SUNXI_CCU_GATE(bus_uart2_clk,	"bus-uart2",	"apb1",
		      0x594, BIT(18), 0);
अटल SUNXI_CCU_GATE(bus_uart3_clk,	"bus-uart3",	"apb1",
		      0x594, BIT(19), 0);
अटल SUNXI_CCU_GATE(bus_uart4_clk,	"bus-uart4",	"apb1",
		      0x594, BIT(20), 0);
अटल SUNXI_CCU_GATE(bus_uart5_clk,	"bus-uart5",	"apb1",
		      0x594, BIT(21), 0);

अटल काष्ठा ccu_common *sun9i_a80_ccu_clks[] = अणु
	&pll_c0cpux_clk.common,
	&pll_c1cpux_clk.common,
	&pll_audio_clk.common,
	&pll_periph0_clk.common,
	&pll_ve_clk.common,
	&pll_ddr_clk.common,
	&pll_video0_clk.common,
	&pll_video1_clk.common,
	&pll_gpu_clk.common,
	&pll_de_clk.common,
	&pll_isp_clk.common,
	&pll_periph1_clk.common,
	&c0cpux_clk.common,
	&c1cpux_clk.common,
	&atb0_clk.common,
	&axi0_clk.common,
	&atb1_clk.common,
	&axi1_clk.common,
	&gtbus_clk.common,
	&ahb0_clk.common,
	&ahb1_clk.common,
	&ahb2_clk.common,
	&apb0_clk.common,
	&apb1_clk.common,
	&cci400_clk.common,
	&ats_clk.common,
	&trace_clk.common,

	&out_a_clk.common,
	&out_b_clk.common,

	/* module घड़ीs */
	&nand0_0_clk.common,
	&nand0_1_clk.common,
	&nand1_0_clk.common,
	&nand1_1_clk.common,
	&mmc0_clk.common,
	&mmc0_sample_clk.common,
	&mmc0_output_clk.common,
	&mmc1_clk.common,
	&mmc1_sample_clk.common,
	&mmc1_output_clk.common,
	&mmc2_clk.common,
	&mmc2_sample_clk.common,
	&mmc2_output_clk.common,
	&mmc3_clk.common,
	&mmc3_sample_clk.common,
	&mmc3_output_clk.common,
	&ts_clk.common,
	&ss_clk.common,
	&spi0_clk.common,
	&spi1_clk.common,
	&spi2_clk.common,
	&spi3_clk.common,
	&i2s0_clk.common,
	&i2s1_clk.common,
	&spdअगर_clk.common,
	&sdram_clk.common,
	&de_clk.common,
	&edp_clk.common,
	&mp_clk.common,
	&lcd0_clk.common,
	&lcd1_clk.common,
	&mipi_dsi0_clk.common,
	&mipi_dsi1_clk.common,
	&hdmi_clk.common,
	&hdmi_slow_clk.common,
	&mipi_csi_clk.common,
	&csi_isp_clk.common,
	&csi_misc_clk.common,
	&csi0_mclk_clk.common,
	&csi1_mclk_clk.common,
	&fd_clk.common,
	&ve_clk.common,
	&avs_clk.common,
	&gpu_core_clk.common,
	&gpu_memory_clk.common,
	&gpu_axi_clk.common,
	&sata_clk.common,
	&ac97_clk.common,
	&mipi_hsi_clk.common,
	&gpadc_clk.common,
	&cir_tx_clk.common,

	/* AHB0 bus gates */
	&bus_fd_clk.common,
	&bus_ve_clk.common,
	&bus_gpu_ctrl_clk.common,
	&bus_ss_clk.common,
	&bus_mmc_clk.common,
	&bus_nand0_clk.common,
	&bus_nand1_clk.common,
	&bus_sdram_clk.common,
	&bus_mipi_hsi_clk.common,
	&bus_sata_clk.common,
	&bus_ts_clk.common,
	&bus_spi0_clk.common,
	&bus_spi1_clk.common,
	&bus_spi2_clk.common,
	&bus_spi3_clk.common,

	/* AHB1 bus gates */
	&bus_otg_clk.common,
	&bus_usb_clk.common,
	&bus_gmac_clk.common,
	&bus_msgbox_clk.common,
	&bus_spinlock_clk.common,
	&bus_hsसमयr_clk.common,
	&bus_dma_clk.common,

	/* AHB2 bus gates */
	&bus_lcd0_clk.common,
	&bus_lcd1_clk.common,
	&bus_edp_clk.common,
	&bus_csi_clk.common,
	&bus_hdmi_clk.common,
	&bus_de_clk.common,
	&bus_mp_clk.common,
	&bus_mipi_dsi_clk.common,

	/* APB0 bus gates */
	&bus_spdअगर_clk.common,
	&bus_pio_clk.common,
	&bus_ac97_clk.common,
	&bus_i2s0_clk.common,
	&bus_i2s1_clk.common,
	&bus_lradc_clk.common,
	&bus_gpadc_clk.common,
	&bus_twd_clk.common,
	&bus_cir_tx_clk.common,

	/* APB1 bus gates */
	&bus_i2c0_clk.common,
	&bus_i2c1_clk.common,
	&bus_i2c2_clk.common,
	&bus_i2c3_clk.common,
	&bus_i2c4_clk.common,
	&bus_uart0_clk.common,
	&bus_uart1_clk.common,
	&bus_uart2_clk.common,
	&bus_uart3_clk.common,
	&bus_uart4_clk.common,
	&bus_uart5_clk.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sun9i_a80_hw_clks = अणु
	.hws	= अणु
		[CLK_PLL_C0CPUX]	= &pll_c0cpux_clk.common.hw,
		[CLK_PLL_C1CPUX]	= &pll_c1cpux_clk.common.hw,
		[CLK_PLL_AUDIO]		= &pll_audio_clk.common.hw,
		[CLK_PLL_PERIPH0]	= &pll_periph0_clk.common.hw,
		[CLK_PLL_VE]		= &pll_ve_clk.common.hw,
		[CLK_PLL_DDR]		= &pll_ddr_clk.common.hw,
		[CLK_PLL_VIDEO0]	= &pll_video0_clk.common.hw,
		[CLK_PLL_VIDEO1]	= &pll_video1_clk.common.hw,
		[CLK_PLL_GPU]		= &pll_gpu_clk.common.hw,
		[CLK_PLL_DE]		= &pll_de_clk.common.hw,
		[CLK_PLL_ISP]		= &pll_isp_clk.common.hw,
		[CLK_PLL_PERIPH1]	= &pll_periph1_clk.common.hw,
		[CLK_C0CPUX]		= &c0cpux_clk.common.hw,
		[CLK_C1CPUX]		= &c1cpux_clk.common.hw,
		[CLK_ATB0]		= &atb0_clk.common.hw,
		[CLK_AXI0]		= &axi0_clk.common.hw,
		[CLK_ATB1]		= &atb1_clk.common.hw,
		[CLK_AXI1]		= &axi1_clk.common.hw,
		[CLK_GTBUS]		= &gtbus_clk.common.hw,
		[CLK_AHB0]		= &ahb0_clk.common.hw,
		[CLK_AHB1]		= &ahb1_clk.common.hw,
		[CLK_AHB2]		= &ahb2_clk.common.hw,
		[CLK_APB0]		= &apb0_clk.common.hw,
		[CLK_APB1]		= &apb1_clk.common.hw,
		[CLK_CCI400]		= &cci400_clk.common.hw,
		[CLK_ATS]		= &ats_clk.common.hw,
		[CLK_TRACE]		= &trace_clk.common.hw,

		[CLK_OUT_A]		= &out_a_clk.common.hw,
		[CLK_OUT_B]		= &out_b_clk.common.hw,

		[CLK_न_अंकD0_0]		= &nand0_0_clk.common.hw,
		[CLK_न_अंकD0_1]		= &nand0_1_clk.common.hw,
		[CLK_न_अंकD1_0]		= &nand1_0_clk.common.hw,
		[CLK_न_अंकD1_1]		= &nand1_1_clk.common.hw,
		[CLK_MMC0]		= &mmc0_clk.common.hw,
		[CLK_MMC0_SAMPLE]	= &mmc0_sample_clk.common.hw,
		[CLK_MMC0_OUTPUT]	= &mmc0_output_clk.common.hw,
		[CLK_MMC1]		= &mmc1_clk.common.hw,
		[CLK_MMC1_SAMPLE]	= &mmc1_sample_clk.common.hw,
		[CLK_MMC1_OUTPUT]	= &mmc1_output_clk.common.hw,
		[CLK_MMC2]		= &mmc2_clk.common.hw,
		[CLK_MMC2_SAMPLE]	= &mmc2_sample_clk.common.hw,
		[CLK_MMC2_OUTPUT]	= &mmc2_output_clk.common.hw,
		[CLK_MMC3]		= &mmc3_clk.common.hw,
		[CLK_MMC3_SAMPLE]	= &mmc3_sample_clk.common.hw,
		[CLK_MMC3_OUTPUT]	= &mmc3_output_clk.common.hw,
		[CLK_TS]		= &ts_clk.common.hw,
		[CLK_SS]		= &ss_clk.common.hw,
		[CLK_SPI0]		= &spi0_clk.common.hw,
		[CLK_SPI1]		= &spi1_clk.common.hw,
		[CLK_SPI2]		= &spi2_clk.common.hw,
		[CLK_SPI3]		= &spi3_clk.common.hw,
		[CLK_I2S0]		= &i2s0_clk.common.hw,
		[CLK_I2S1]		= &i2s1_clk.common.hw,
		[CLK_SPDIF]		= &spdअगर_clk.common.hw,
		[CLK_SDRAM]		= &sdram_clk.common.hw,
		[CLK_DE]		= &de_clk.common.hw,
		[CLK_EDP]		= &edp_clk.common.hw,
		[CLK_MP]		= &mp_clk.common.hw,
		[CLK_LCD0]		= &lcd0_clk.common.hw,
		[CLK_LCD1]		= &lcd1_clk.common.hw,
		[CLK_MIPI_DSI0]		= &mipi_dsi0_clk.common.hw,
		[CLK_MIPI_DSI1]		= &mipi_dsi1_clk.common.hw,
		[CLK_HDMI]		= &hdmi_clk.common.hw,
		[CLK_HDMI_SLOW]		= &hdmi_slow_clk.common.hw,
		[CLK_MIPI_CSI]		= &mipi_csi_clk.common.hw,
		[CLK_CSI_ISP]		= &csi_isp_clk.common.hw,
		[CLK_CSI_MISC]		= &csi_misc_clk.common.hw,
		[CLK_CSI0_MCLK]		= &csi0_mclk_clk.common.hw,
		[CLK_CSI1_MCLK]		= &csi1_mclk_clk.common.hw,
		[CLK_FD]		= &fd_clk.common.hw,
		[CLK_VE]		= &ve_clk.common.hw,
		[CLK_AVS]		= &avs_clk.common.hw,
		[CLK_GPU_CORE]		= &gpu_core_clk.common.hw,
		[CLK_GPU_MEMORY]	= &gpu_memory_clk.common.hw,
		[CLK_GPU_AXI]		= &gpu_axi_clk.common.hw,
		[CLK_SATA]		= &sata_clk.common.hw,
		[CLK_AC97]		= &ac97_clk.common.hw,
		[CLK_MIPI_HSI]		= &mipi_hsi_clk.common.hw,
		[CLK_GPADC]		= &gpadc_clk.common.hw,
		[CLK_CIR_TX]		= &cir_tx_clk.common.hw,

		[CLK_BUS_FD]		= &bus_fd_clk.common.hw,
		[CLK_BUS_VE]		= &bus_ve_clk.common.hw,
		[CLK_BUS_GPU_CTRL]	= &bus_gpu_ctrl_clk.common.hw,
		[CLK_BUS_SS]		= &bus_ss_clk.common.hw,
		[CLK_BUS_MMC]		= &bus_mmc_clk.common.hw,
		[CLK_BUS_न_अंकD0]		= &bus_nand0_clk.common.hw,
		[CLK_BUS_न_अंकD1]		= &bus_nand1_clk.common.hw,
		[CLK_BUS_SDRAM]		= &bus_sdram_clk.common.hw,
		[CLK_BUS_MIPI_HSI]	= &bus_mipi_hsi_clk.common.hw,
		[CLK_BUS_SATA]		= &bus_sata_clk.common.hw,
		[CLK_BUS_TS]		= &bus_ts_clk.common.hw,
		[CLK_BUS_SPI0]		= &bus_spi0_clk.common.hw,
		[CLK_BUS_SPI1]		= &bus_spi1_clk.common.hw,
		[CLK_BUS_SPI2]		= &bus_spi2_clk.common.hw,
		[CLK_BUS_SPI3]		= &bus_spi3_clk.common.hw,

		[CLK_BUS_OTG]		= &bus_otg_clk.common.hw,
		[CLK_BUS_USB]		= &bus_usb_clk.common.hw,
		[CLK_BUS_GMAC]		= &bus_gmac_clk.common.hw,
		[CLK_BUS_MSGBOX]	= &bus_msgbox_clk.common.hw,
		[CLK_BUS_SPINLOCK]	= &bus_spinlock_clk.common.hw,
		[CLK_BUS_HSTIMER]	= &bus_hsसमयr_clk.common.hw,
		[CLK_BUS_DMA]		= &bus_dma_clk.common.hw,

		[CLK_BUS_LCD0]		= &bus_lcd0_clk.common.hw,
		[CLK_BUS_LCD1]		= &bus_lcd1_clk.common.hw,
		[CLK_BUS_EDP]		= &bus_edp_clk.common.hw,
		[CLK_BUS_CSI]		= &bus_csi_clk.common.hw,
		[CLK_BUS_HDMI]		= &bus_hdmi_clk.common.hw,
		[CLK_BUS_DE]		= &bus_de_clk.common.hw,
		[CLK_BUS_MP]		= &bus_mp_clk.common.hw,
		[CLK_BUS_MIPI_DSI]	= &bus_mipi_dsi_clk.common.hw,

		[CLK_BUS_SPDIF]		= &bus_spdअगर_clk.common.hw,
		[CLK_BUS_PIO]		= &bus_pio_clk.common.hw,
		[CLK_BUS_AC97]		= &bus_ac97_clk.common.hw,
		[CLK_BUS_I2S0]		= &bus_i2s0_clk.common.hw,
		[CLK_BUS_I2S1]		= &bus_i2s1_clk.common.hw,
		[CLK_BUS_LRADC]		= &bus_lradc_clk.common.hw,
		[CLK_BUS_GPADC]		= &bus_gpadc_clk.common.hw,
		[CLK_BUS_TWD]		= &bus_twd_clk.common.hw,
		[CLK_BUS_CIR_TX]	= &bus_cir_tx_clk.common.hw,

		[CLK_BUS_I2C0]		= &bus_i2c0_clk.common.hw,
		[CLK_BUS_I2C1]		= &bus_i2c1_clk.common.hw,
		[CLK_BUS_I2C2]		= &bus_i2c2_clk.common.hw,
		[CLK_BUS_I2C3]		= &bus_i2c3_clk.common.hw,
		[CLK_BUS_I2C4]		= &bus_i2c4_clk.common.hw,
		[CLK_BUS_UART0]		= &bus_uart0_clk.common.hw,
		[CLK_BUS_UART1]		= &bus_uart1_clk.common.hw,
		[CLK_BUS_UART2]		= &bus_uart2_clk.common.hw,
		[CLK_BUS_UART3]		= &bus_uart3_clk.common.hw,
		[CLK_BUS_UART4]		= &bus_uart4_clk.common.hw,
		[CLK_BUS_UART5]		= &bus_uart5_clk.common.hw,
	पूर्ण,
	.num	= CLK_NUMBER,
पूर्ण;

अटल काष्ठा ccu_reset_map sun9i_a80_ccu_resets[] = अणु
	/* AHB0 reset controls */
	[RST_BUS_FD]		= अणु 0x5a0, BIT(0) पूर्ण,
	[RST_BUS_VE]		= अणु 0x5a0, BIT(1) पूर्ण,
	[RST_BUS_GPU_CTRL]	= अणु 0x5a0, BIT(3) पूर्ण,
	[RST_BUS_SS]		= अणु 0x5a0, BIT(5) पूर्ण,
	[RST_BUS_MMC]		= अणु 0x5a0, BIT(8) पूर्ण,
	[RST_BUS_न_अंकD0]		= अणु 0x5a0, BIT(12) पूर्ण,
	[RST_BUS_न_अंकD1]		= अणु 0x5a0, BIT(13) पूर्ण,
	[RST_BUS_SDRAM]		= अणु 0x5a0, BIT(14) पूर्ण,
	[RST_BUS_SATA]		= अणु 0x5a0, BIT(16) पूर्ण,
	[RST_BUS_TS]		= अणु 0x5a0, BIT(18) पूर्ण,
	[RST_BUS_SPI0]		= अणु 0x5a0, BIT(20) पूर्ण,
	[RST_BUS_SPI1]		= अणु 0x5a0, BIT(21) पूर्ण,
	[RST_BUS_SPI2]		= अणु 0x5a0, BIT(22) पूर्ण,
	[RST_BUS_SPI3]		= अणु 0x5a0, BIT(23) पूर्ण,

	/* AHB1 reset controls */
	[RST_BUS_OTG]		= अणु 0x5a4, BIT(0) पूर्ण,
	[RST_BUS_OTG_PHY]	= अणु 0x5a4, BIT(1) पूर्ण,
	[RST_BUS_MIPI_HSI]	= अणु 0x5a4, BIT(9) पूर्ण,
	[RST_BUS_GMAC]		= अणु 0x5a4, BIT(17) पूर्ण,
	[RST_BUS_MSGBOX]	= अणु 0x5a4, BIT(21) पूर्ण,
	[RST_BUS_SPINLOCK]	= अणु 0x5a4, BIT(22) पूर्ण,
	[RST_BUS_HSTIMER]	= अणु 0x5a4, BIT(23) पूर्ण,
	[RST_BUS_DMA]		= अणु 0x5a4, BIT(24) पूर्ण,

	/* AHB2 reset controls */
	[RST_BUS_LCD0]		= अणु 0x5a8, BIT(0) पूर्ण,
	[RST_BUS_LCD1]		= अणु 0x5a8, BIT(1) पूर्ण,
	[RST_BUS_EDP]		= अणु 0x5a8, BIT(2) पूर्ण,
	[RST_BUS_LVDS]		= अणु 0x5a8, BIT(3) पूर्ण,
	[RST_BUS_CSI]		= अणु 0x5a8, BIT(4) पूर्ण,
	[RST_BUS_HDMI0]		= अणु 0x5a8, BIT(5) पूर्ण,
	[RST_BUS_HDMI1]		= अणु 0x5a8, BIT(6) पूर्ण,
	[RST_BUS_DE]		= अणु 0x5a8, BIT(7) पूर्ण,
	[RST_BUS_MP]		= अणु 0x5a8, BIT(8) पूर्ण,
	[RST_BUS_GPU]		= अणु 0x5a8, BIT(9) पूर्ण,
	[RST_BUS_MIPI_DSI]	= अणु 0x5a8, BIT(11) पूर्ण,

	/* APB0 reset controls */
	[RST_BUS_SPDIF]		= अणु 0x5b0, BIT(1) पूर्ण,
	[RST_BUS_AC97]		= अणु 0x5b0, BIT(11) पूर्ण,
	[RST_BUS_I2S0]		= अणु 0x5b0, BIT(12) पूर्ण,
	[RST_BUS_I2S1]		= अणु 0x5b0, BIT(13) पूर्ण,
	[RST_BUS_LRADC]		= अणु 0x5b0, BIT(15) पूर्ण,
	[RST_BUS_GPADC]		= अणु 0x5b0, BIT(17) पूर्ण,
	[RST_BUS_CIR_TX]	= अणु 0x5b0, BIT(19) पूर्ण,

	/* APB1 reset controls */
	[RST_BUS_I2C0]		= अणु 0x5b4, BIT(0) पूर्ण,
	[RST_BUS_I2C1]		= अणु 0x5b4, BIT(1) पूर्ण,
	[RST_BUS_I2C2]		= अणु 0x5b4, BIT(2) पूर्ण,
	[RST_BUS_I2C3]		= अणु 0x5b4, BIT(3) पूर्ण,
	[RST_BUS_I2C4]		= अणु 0x5b4, BIT(4) पूर्ण,
	[RST_BUS_UART0]		= अणु 0x5b4, BIT(16) पूर्ण,
	[RST_BUS_UART1]		= अणु 0x5b4, BIT(17) पूर्ण,
	[RST_BUS_UART2]		= अणु 0x5b4, BIT(18) पूर्ण,
	[RST_BUS_UART3]		= अणु 0x5b4, BIT(19) पूर्ण,
	[RST_BUS_UART4]		= अणु 0x5b4, BIT(20) पूर्ण,
	[RST_BUS_UART5]		= अणु 0x5b4, BIT(21) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun9i_a80_ccu_desc = अणु
	.ccu_clks	= sun9i_a80_ccu_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun9i_a80_ccu_clks),

	.hw_clks	= &sun9i_a80_hw_clks,

	.resets		= sun9i_a80_ccu_resets,
	.num_resets	= ARRAY_SIZE(sun9i_a80_ccu_resets),
पूर्ण;

#घोषणा SUN9I_A80_PLL_P_SHIFT	16
#घोषणा SUN9I_A80_PLL_N_SHIFT	8
#घोषणा SUN9I_A80_PLL_N_WIDTH	8

अटल व्योम sun9i_a80_cpu_pll_fixup(व्योम __iomem *reg)
अणु
	u32 val = पढ़ोl(reg);

	/* bail out अगर P भागider is not used */
	अगर (!(val & BIT(SUN9I_A80_PLL_P_SHIFT)))
		वापस;

	/*
	 * If P is used, output should be less than 288 MHz. When we
	 * set P to 1, we should also decrease the multiplier so the
	 * output करोesn't go out of range, but not too much such that
	 * the multiplier stays above 12, the minimal operation value.
	 *
	 * To keep it simple, set the multiplier to 17, the reset value.
	 */
	val &= ~GENMASK(SUN9I_A80_PLL_N_SHIFT + SUN9I_A80_PLL_N_WIDTH - 1,
			SUN9I_A80_PLL_N_SHIFT);
	val |= 17 << SUN9I_A80_PLL_N_SHIFT;

	/* And clear P */
	val &= ~BIT(SUN9I_A80_PLL_P_SHIFT);

	ग_लिखोl(val, reg);
पूर्ण

अटल पूर्णांक sun9i_a80_ccu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	व्योम __iomem *reg;
	u32 val;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	reg = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	/* Enक्रमce d1 = 0, d2 = 0 क्रम Audio PLL */
	val = पढ़ोl(reg + SUN9I_A80_PLL_AUDIO_REG);
	val &= ~(BIT(16) | BIT(18));
	ग_लिखोl(val, reg + SUN9I_A80_PLL_AUDIO_REG);

	/* Enक्रमce P = 1 क्रम both CPU cluster PLLs */
	sun9i_a80_cpu_pll_fixup(reg + SUN9I_A80_PLL_C0CPUX_REG);
	sun9i_a80_cpu_pll_fixup(reg + SUN9I_A80_PLL_C1CPUX_REG);

	वापस sunxi_ccu_probe(pdev->dev.of_node, reg, &sun9i_a80_ccu_desc);
पूर्ण

अटल स्थिर काष्ठा of_device_id sun9i_a80_ccu_ids[] = अणु
	अणु .compatible = "allwinner,sun9i-a80-ccu" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sun9i_a80_ccu_driver = अणु
	.probe	= sun9i_a80_ccu_probe,
	.driver	= अणु
		.name	= "sun9i-a80-ccu",
		.of_match_table	= sun9i_a80_ccu_ids,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(sun9i_a80_ccu_driver);
