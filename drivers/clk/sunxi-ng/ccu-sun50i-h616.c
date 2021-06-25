<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020 Arm Ltd.
 * Based on the H6 CCU driver, which is:
 *   Copyright (c) 2017 Icenowy Zheng <icenowy@aosc.io>
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
#समावेश "ccu_mult.h"
#समावेश "ccu_nk.h"
#समावेश "ccu_nkm.h"
#समावेश "ccu_nkmp.h"
#समावेश "ccu_nm.h"

#समावेश "ccu-sun50i-h616.h"

/*
 * The CPU PLL is actually NP घड़ी, with P being /1, /2 or /4. However
 * P should only be used क्रम output frequencies lower than 288 MHz.
 *
 * For now we can just model it as a multiplier घड़ी, and क्रमce P to /1.
 *
 * The M factor is present in the रेजिस्टर's description, but not in the
 * frequency क्रमmula, and it's करोcumented as "M is only used क्रम backकरोor
 * testing", so it's not modelled and then क्रमce to 0.
 */
#घोषणा SUN50I_H616_PLL_CPUX_REG	0x000
अटल काष्ठा ccu_mult pll_cpux_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(28),
	.mult		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.common		= अणु
		.reg		= 0x000,
		.hw.init	= CLK_HW_INIT("pll-cpux", "osc24M",
					      &ccu_mult_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

/* Some PLLs are input * N / भाग1 / P. Model them as NKMP with no K */
#घोषणा SUN50I_H616_PLL_DDR0_REG	0x010
अटल काष्ठा ccu_nkmp pll_ddr0_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(28),
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output भागider */
	.common		= अणु
		.reg		= 0x010,
		.hw.init	= CLK_HW_INIT("pll-ddr0", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

#घोषणा SUN50I_H616_PLL_DDR1_REG	0x018
अटल काष्ठा ccu_nkmp pll_ddr1_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(28),
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output भागider */
	.common		= अणु
		.reg		= 0x018,
		.hw.init	= CLK_HW_INIT("pll-ddr1", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

#घोषणा SUN50I_H616_PLL_PERIPH0_REG	0x020
अटल काष्ठा ccu_nkmp pll_periph0_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(28),
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output भागider */
	.fixed_post_भाग	= 2,
	.common		= अणु
		.reg		= 0x020,
		.features	= CCU_FEATURE_FIXED_POSTDIV,
		.hw.init	= CLK_HW_INIT("pll-periph0", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

#घोषणा SUN50I_H616_PLL_PERIPH1_REG	0x028
अटल काष्ठा ccu_nkmp pll_periph1_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(28),
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output भागider */
	.fixed_post_भाग	= 2,
	.common		= अणु
		.reg		= 0x028,
		.features	= CCU_FEATURE_FIXED_POSTDIV,
		.hw.init	= CLK_HW_INIT("pll-periph1", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

#घोषणा SUN50I_H616_PLL_GPU_REG		0x030
अटल काष्ठा ccu_nkmp pll_gpu_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(28),
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output भागider */
	.common		= अणु
		.reg		= 0x030,
		.hw.init	= CLK_HW_INIT("pll-gpu", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

/*
 * For Video PLLs, the output भागider is described as "used for testing"
 * in the user manual. So it's not modelled and क्रमced to 0.
 */
#घोषणा SUN50I_H616_PLL_VIDEO0_REG	0x040
अटल काष्ठा ccu_nm pll_video0_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(28),
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input भागider */
	.fixed_post_भाग	= 4,
	.min_rate	= 288000000,
	.max_rate	= 2400000000UL,
	.common		= अणु
		.reg		= 0x040,
		.features	= CCU_FEATURE_FIXED_POSTDIV,
		.hw.init	= CLK_HW_INIT("pll-video0", "osc24M",
					      &ccu_nm_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

#घोषणा SUN50I_H616_PLL_VIDEO1_REG	0x048
अटल काष्ठा ccu_nm pll_video1_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(28),
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input भागider */
	.fixed_post_भाग	= 4,
	.min_rate	= 288000000,
	.max_rate	= 2400000000UL,
	.common		= अणु
		.reg		= 0x048,
		.features	= CCU_FEATURE_FIXED_POSTDIV,
		.hw.init	= CLK_HW_INIT("pll-video1", "osc24M",
					      &ccu_nm_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

#घोषणा SUN50I_H616_PLL_VIDEO2_REG	0x050
अटल काष्ठा ccu_nm pll_video2_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(28),
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input भागider */
	.fixed_post_भाग	= 4,
	.min_rate	= 288000000,
	.max_rate	= 2400000000UL,
	.common		= अणु
		.reg		= 0x050,
		.features	= CCU_FEATURE_FIXED_POSTDIV,
		.hw.init	= CLK_HW_INIT("pll-video2", "osc24M",
					      &ccu_nm_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

#घोषणा SUN50I_H616_PLL_VE_REG		0x058
अटल काष्ठा ccu_nkmp pll_ve_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(28),
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output भागider */
	.common		= अणु
		.reg		= 0x058,
		.hw.init	= CLK_HW_INIT("pll-ve", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

#घोषणा SUN50I_H616_PLL_DE_REG		0x060
अटल काष्ठा ccu_nkmp pll_de_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(28),
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output भागider */
	.common		= अणु
		.reg		= 0x060,
		.hw.init	= CLK_HW_INIT("pll-de", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

/*
 * TODO: Determine SDM settings क्रम the audio PLL. The manual suggests
 * PLL_FACTOR_N=16, PLL_POST_DIV_P=2, OUTPUT_DIV=2, pattern=0xe000c49b
 * क्रम 24.576 MHz, and PLL_FACTOR_N=22, PLL_POST_DIV_P=3, OUTPUT_DIV=2,
 * pattern=0xe001288c क्रम 22.5792 MHz.
 * This clashes with our fixed PLL_POST_DIV_P.
 */
#घोषणा SUN50I_H616_PLL_AUDIO_REG	0x078
अटल काष्ठा ccu_nm pll_audio_hs_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(28),
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input भागider */
	.common		= अणु
		.reg		= 0x078,
		.hw.init	= CLK_HW_INIT("pll-audio-hs", "osc24M",
					      &ccu_nm_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर cpux_parents[] = अणु "osc24M", "osc32k",
					"iosc", "pll-cpux", "pll-periph0" पूर्ण;
अटल SUNXI_CCU_MUX(cpux_clk, "cpux", cpux_parents,
		     0x500, 24, 3, CLK_SET_RATE_PARENT | CLK_IS_CRITICAL);
अटल SUNXI_CCU_M(axi_clk, "axi", "cpux", 0x500, 0, 2, 0);
अटल SUNXI_CCU_M(cpux_apb_clk, "cpux-apb", "cpux", 0x500, 8, 2, 0);

अटल स्थिर अक्षर * स्थिर psi_ahb1_ahb2_parents[] = अणु "osc24M", "osc32k",
						      "iosc", "pll-periph0" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX(psi_ahb1_ahb2_clk, "psi-ahb1-ahb2",
			     psi_ahb1_ahb2_parents,
			     0x510,
			     0, 2,	/* M */
			     8, 2,	/* P */
			     24, 2,	/* mux */
			     0);

अटल स्थिर अक्षर * स्थिर ahb3_apb1_apb2_parents[] = अणु "osc24M", "osc32k",
						       "psi-ahb1-ahb2",
						       "pll-periph0" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX(ahb3_clk, "ahb3", ahb3_apb1_apb2_parents, 0x51c,
			     0, 2,	/* M */
			     8, 2,	/* P */
			     24, 2,	/* mux */
			     0);

अटल SUNXI_CCU_MP_WITH_MUX(apb1_clk, "apb1", ahb3_apb1_apb2_parents, 0x520,
			     0, 2,	/* M */
			     8, 2,	/* P */
			     24, 2,	/* mux */
			     0);

अटल SUNXI_CCU_MP_WITH_MUX(apb2_clk, "apb2", ahb3_apb1_apb2_parents, 0x524,
			     0, 2,	/* M */
			     8, 2,	/* P */
			     24, 2,	/* mux */
			     0);

अटल स्थिर अक्षर * स्थिर mbus_parents[] = अणु "osc24M", "pll-periph0-2x",
					     "pll-ddr0", "pll-ddr1" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(mbus_clk, "mbus", mbus_parents, 0x540,
					0, 3,	/* M */
					24, 2,	/* mux */
					BIT(31),	/* gate */
					CLK_IS_CRITICAL);

अटल स्थिर अक्षर * स्थिर de_parents[] = अणु "pll-de", "pll-periph0-2x" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(de_clk, "de", de_parents, 0x600,
				       0, 4,	/* M */
				       24, 1,	/* mux */
				       BIT(31),	/* gate */
				       CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_GATE(bus_de_clk, "bus-de", "psi-ahb1-ahb2",
		      0x60c, BIT(0), 0);

अटल SUNXI_CCU_M_WITH_MUX_GATE(deपूर्णांकerlace_clk, "deinterlace",
				       de_parents,
				       0x620,
				       0, 4,	/* M */
				       24, 1,	/* mux */
				       BIT(31),	/* gate */
				       0);

अटल SUNXI_CCU_GATE(bus_deपूर्णांकerlace_clk, "bus-deinterlace", "psi-ahb1-ahb2",
		      0x62c, BIT(0), 0);

अटल SUNXI_CCU_M_WITH_MUX_GATE(g2d_clk, "g2d", de_parents, 0x630,
				       0, 4,	/* M */
				       24, 1,	/* mux */
				       BIT(31),	/* gate */
				       0);

अटल SUNXI_CCU_GATE(bus_g2d_clk, "bus-g2d", "psi-ahb1-ahb2",
		      0x63c, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर gpu0_parents[] = अणु "pll-gpu", "gpu1" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(gpu0_clk, "gpu0", gpu0_parents, 0x670,
				       0, 2,	/* M */
				       24, 1,	/* mux */
				       BIT(31),	/* gate */
				       CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_M_WITH_GATE(gpu1_clk, "gpu1", "pll-periph0-2x", 0x674,
					0, 2,	/* M */
					BIT(31),/* gate */
					0);

अटल SUNXI_CCU_GATE(bus_gpu_clk, "bus-gpu", "psi-ahb1-ahb2",
		      0x67c, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर ce_parents[] = अणु "osc24M", "pll-periph0-2x" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX_GATE(ce_clk, "ce", ce_parents, 0x680,
					0, 4,	/* M */
					8, 2,	/* N */
					24, 1,	/* mux */
					BIT(31),/* gate */
					0);

अटल SUNXI_CCU_GATE(bus_ce_clk, "bus-ce", "psi-ahb1-ahb2",
		      0x68c, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर ve_parents[] = अणु "pll-ve" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(ve_clk, "ve", ve_parents, 0x690,
				       0, 3,	/* M */
				       24, 1,	/* mux */
				       BIT(31),	/* gate */
				       CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_GATE(bus_ve_clk, "bus-ve", "psi-ahb1-ahb2",
		      0x69c, BIT(0), 0);

अटल SUNXI_CCU_GATE(bus_dma_clk, "bus-dma", "psi-ahb1-ahb2",
		      0x70c, BIT(0), 0);

अटल SUNXI_CCU_GATE(bus_hsसमयr_clk, "bus-hstimer", "psi-ahb1-ahb2",
		      0x73c, BIT(0), 0);

अटल SUNXI_CCU_GATE(avs_clk, "avs", "osc24M", 0x740, BIT(31), 0);

अटल SUNXI_CCU_GATE(bus_dbg_clk, "bus-dbg", "psi-ahb1-ahb2",
		      0x78c, BIT(0), 0);

अटल SUNXI_CCU_GATE(bus_psi_clk, "bus-psi", "psi-ahb1-ahb2",
		      0x79c, BIT(0), 0);

अटल SUNXI_CCU_GATE(bus_pwm_clk, "bus-pwm", "apb1", 0x7ac, BIT(0), 0);

अटल SUNXI_CCU_GATE(bus_iommu_clk, "bus-iommu", "apb1", 0x7bc, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर dram_parents[] = अणु "pll-ddr0", "pll-ddr1" पूर्ण;
अटल काष्ठा ccu_भाग dram_clk = अणु
	.भाग		= _SUNXI_CCU_DIV(0, 2),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common	= अणु
		.reg		= 0x800,
		.hw.init	= CLK_HW_INIT_PARENTS("dram",
						      dram_parents,
						      &ccu_भाग_ops,
						      CLK_IS_CRITICAL),
	पूर्ण,
पूर्ण;

अटल SUNXI_CCU_GATE(mbus_dma_clk, "mbus-dma", "mbus",
		      0x804, BIT(0), 0);
अटल SUNXI_CCU_GATE(mbus_ve_clk, "mbus-ve", "mbus",
		      0x804, BIT(1), 0);
अटल SUNXI_CCU_GATE(mbus_ce_clk, "mbus-ce", "mbus",
		      0x804, BIT(2), 0);
अटल SUNXI_CCU_GATE(mbus_ts_clk, "mbus-ts", "mbus",
		      0x804, BIT(3), 0);
अटल SUNXI_CCU_GATE(mbus_nand_clk, "mbus-nand", "mbus",
		      0x804, BIT(5), 0);
अटल SUNXI_CCU_GATE(mbus_g2d_clk, "mbus-g2d", "mbus",
		      0x804, BIT(10), 0);

अटल SUNXI_CCU_GATE(bus_dram_clk, "bus-dram", "psi-ahb1-ahb2",
		      0x80c, BIT(0), CLK_IS_CRITICAL);

अटल स्थिर अक्षर * स्थिर nand_spi_parents[] = अणु "osc24M", "pll-periph0",
					     "pll-periph1", "pll-periph0-2x",
					     "pll-periph1-2x" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX_GATE(nand0_clk, "nand0", nand_spi_parents, 0x810,
					0, 4,	/* M */
					8, 2,	/* N */
					24, 3,	/* mux */
					BIT(31),/* gate */
					0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(nand1_clk, "nand1", nand_spi_parents, 0x814,
					0, 4,	/* M */
					8, 2,	/* N */
					24, 3,	/* mux */
					BIT(31),/* gate */
					0);

अटल SUNXI_CCU_GATE(bus_nand_clk, "bus-nand", "ahb3", 0x82c, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर mmc_parents[] = अणु "osc24M", "pll-periph0-2x",
					    "pll-periph1-2x" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX_GATE_POSTDIV(mmc0_clk, "mmc0", mmc_parents, 0x830,
					  0, 4,		/* M */
					  8, 2,		/* N */
					  24, 2,	/* mux */
					  BIT(31),	/* gate */
					  2,		/* post-भाग */
					  0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE_POSTDIV(mmc1_clk, "mmc1", mmc_parents, 0x834,
					  0, 4,		/* M */
					  8, 2,		/* N */
					  24, 2,	/* mux */
					  BIT(31),	/* gate */
					  2,		/* post-भाग */
					  0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE_POSTDIV(mmc2_clk, "mmc2", mmc_parents, 0x838,
					  0, 4,		/* M */
					  8, 2,		/* N */
					  24, 2,	/* mux */
					  BIT(31),	/* gate */
					  2,		/* post-भाग */
					  0);

अटल SUNXI_CCU_GATE(bus_mmc0_clk, "bus-mmc0", "ahb3", 0x84c, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_mmc1_clk, "bus-mmc1", "ahb3", 0x84c, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_mmc2_clk, "bus-mmc2", "ahb3", 0x84c, BIT(2), 0);

अटल SUNXI_CCU_GATE(bus_uart0_clk, "bus-uart0", "apb2", 0x90c, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_uart1_clk, "bus-uart1", "apb2", 0x90c, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_uart2_clk, "bus-uart2", "apb2", 0x90c, BIT(2), 0);
अटल SUNXI_CCU_GATE(bus_uart3_clk, "bus-uart3", "apb2", 0x90c, BIT(3), 0);
अटल SUNXI_CCU_GATE(bus_uart4_clk, "bus-uart4", "apb2", 0x90c, BIT(4), 0);
अटल SUNXI_CCU_GATE(bus_uart5_clk, "bus-uart5", "apb2", 0x90c, BIT(5), 0);

अटल SUNXI_CCU_GATE(bus_i2c0_clk, "bus-i2c0", "apb2", 0x91c, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_i2c1_clk, "bus-i2c1", "apb2", 0x91c, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_i2c2_clk, "bus-i2c2", "apb2", 0x91c, BIT(2), 0);
अटल SUNXI_CCU_GATE(bus_i2c3_clk, "bus-i2c3", "apb2", 0x91c, BIT(3), 0);
अटल SUNXI_CCU_GATE(bus_i2c4_clk, "bus-i2c4", "apb2", 0x91c, BIT(4), 0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(spi0_clk, "spi0", nand_spi_parents, 0x940,
					0, 4,	/* M */
					8, 2,	/* N */
					24, 3,	/* mux */
					BIT(31),/* gate */
					0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(spi1_clk, "spi1", nand_spi_parents, 0x944,
					0, 4,	/* M */
					8, 2,	/* N */
					24, 3,	/* mux */
					BIT(31),/* gate */
					0);

अटल SUNXI_CCU_GATE(bus_spi0_clk, "bus-spi0", "ahb3", 0x96c, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_spi1_clk, "bus-spi1", "ahb3", 0x96c, BIT(1), 0);

अटल SUNXI_CCU_GATE(emac_25m_clk, "emac-25m", "ahb3", 0x970,
		      BIT(31) | BIT(30), 0);

अटल SUNXI_CCU_GATE(bus_emac0_clk, "bus-emac0", "ahb3", 0x97c, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_emac1_clk, "bus-emac1", "ahb3", 0x97c, BIT(1), 0);

अटल स्थिर अक्षर * स्थिर ts_parents[] = अणु "osc24M", "pll-periph0" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX_GATE(ts_clk, "ts", ts_parents, 0x9b0,
					0, 4,	/* M */
					8, 2,	/* N */
					24, 1,	/* mux */
					BIT(31),/* gate */
					0);

अटल SUNXI_CCU_GATE(bus_ts_clk, "bus-ts", "ahb3", 0x9bc, BIT(0), 0);

अटल SUNXI_CCU_GATE(bus_ths_clk, "bus-ths", "apb1", 0x9fc, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर audio_parents[] = अणु "pll-audio-1x", "pll-audio-2x",
					      "pll-audio-4x", "pll-audio-hs" पूर्ण;
अटल काष्ठा ccu_भाग spdअगर_clk = अणु
	.enable		= BIT(31),
	.भाग		= _SUNXI_CCU_DIV_FLAGS(8, 2, CLK_DIVIDER_POWER_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= अणु
		.reg		= 0xa20,
		.hw.init	= CLK_HW_INIT_PARENTS("spdif",
						      audio_parents,
						      &ccu_भाग_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल SUNXI_CCU_GATE(bus_spdअगर_clk, "bus-spdif", "apb1", 0xa2c, BIT(0), 0);

अटल काष्ठा ccu_भाग dmic_clk = अणु
	.enable		= BIT(31),
	.भाग		= _SUNXI_CCU_DIV_FLAGS(8, 2, CLK_DIVIDER_POWER_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= अणु
		.reg		= 0xa40,
		.hw.init	= CLK_HW_INIT_PARENTS("dmic",
						      audio_parents,
						      &ccu_भाग_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल SUNXI_CCU_GATE(bus_dmic_clk, "bus-dmic", "apb1", 0xa4c, BIT(0), 0);

अटल SUNXI_CCU_M_WITH_MUX_GATE(audio_codec_1x_clk, "audio-codec-1x",
				 audio_parents, 0xa50,
				 0, 4,	/* M */
				 24, 2,	/* mux */
				 BIT(31),	/* gate */
				 CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_M_WITH_MUX_GATE(audio_codec_4x_clk, "audio-codec-4x",
				 audio_parents, 0xa54,
				 0, 4,	/* M */
				 24, 2,	/* mux */
				 BIT(31),	/* gate */
				 CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_GATE(bus_audio_codec_clk, "bus-audio-codec", "apb1", 0xa5c,
		BIT(0), 0);

अटल काष्ठा ccu_भाग audio_hub_clk = अणु
	.enable		= BIT(31),
	.भाग		= _SUNXI_CCU_DIV_FLAGS(8, 2, CLK_DIVIDER_POWER_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= अणु
		.reg		= 0xa60,
		.hw.init	= CLK_HW_INIT_PARENTS("audio-hub",
						      audio_parents,
						      &ccu_भाग_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल SUNXI_CCU_GATE(bus_audio_hub_clk, "bus-audio-hub", "apb1", 0xa6c, BIT(0), 0);

/*
 * There are OHCI 12M घड़ी source selection bits क्रम the four USB 2.0 ports.
 * We will क्रमce them to 0 (12M भागided from 48M).
 */
#घोषणा SUN50I_H616_USB0_CLK_REG		0xa70
#घोषणा SUN50I_H616_USB1_CLK_REG		0xa74
#घोषणा SUN50I_H616_USB2_CLK_REG		0xa78
#घोषणा SUN50I_H616_USB3_CLK_REG		0xa7c

अटल SUNXI_CCU_GATE(usb_ohci0_clk, "usb-ohci0", "osc12M", 0xa70, BIT(31), 0);
अटल SUNXI_CCU_GATE(usb_phy0_clk, "usb-phy0", "osc24M", 0xa70, BIT(29), 0);

अटल SUNXI_CCU_GATE(usb_ohci1_clk, "usb-ohci1", "osc12M", 0xa74, BIT(31), 0);
अटल SUNXI_CCU_GATE(usb_phy1_clk, "usb-phy1", "osc24M", 0xa74, BIT(29), 0);

अटल SUNXI_CCU_GATE(usb_ohci2_clk, "usb-ohci2", "osc12M", 0xa78, BIT(31), 0);
अटल SUNXI_CCU_GATE(usb_phy2_clk, "usb-phy2", "osc24M", 0xa78, BIT(29), 0);

अटल SUNXI_CCU_GATE(usb_ohci3_clk, "usb-ohci3", "osc12M", 0xa7c, BIT(31), 0);
अटल SUNXI_CCU_GATE(usb_phy3_clk, "usb-phy3", "osc24M", 0xa7c, BIT(29), 0);

अटल SUNXI_CCU_GATE(bus_ohci0_clk, "bus-ohci0", "ahb3", 0xa8c, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_ohci1_clk, "bus-ohci1", "ahb3", 0xa8c, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_ohci2_clk, "bus-ohci2", "ahb3", 0xa8c, BIT(2), 0);
अटल SUNXI_CCU_GATE(bus_ohci3_clk, "bus-ohci3", "ahb3", 0xa8c, BIT(3), 0);
अटल SUNXI_CCU_GATE(bus_ehci0_clk, "bus-ehci0", "ahb3", 0xa8c, BIT(4), 0);
अटल SUNXI_CCU_GATE(bus_ehci1_clk, "bus-ehci1", "ahb3", 0xa8c, BIT(5), 0);
अटल SUNXI_CCU_GATE(bus_ehci2_clk, "bus-ehci2", "ahb3", 0xa8c, BIT(6), 0);
अटल SUNXI_CCU_GATE(bus_ehci3_clk, "bus-ehci3", "ahb3", 0xa8c, BIT(7), 0);
अटल SUNXI_CCU_GATE(bus_otg_clk, "bus-otg", "ahb3", 0xa8c, BIT(8), 0);

अटल SUNXI_CCU_GATE(bus_keyadc_clk, "bus-keyadc", "apb1", 0xa9c, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर hdmi_parents[] = अणु "pll-video0", "pll-video0-4x",
					     "pll-video2", "pll-video2-4x" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(hdmi_clk, "hdmi", hdmi_parents, 0xb00,
				 0, 4,		/* M */
				 24, 2,		/* mux */
				 BIT(31),	/* gate */
				 0);

अटल SUNXI_CCU_GATE(hdmi_slow_clk, "hdmi-slow", "osc24M", 0xb04, BIT(31), 0);

अटल स्थिर अक्षर * स्थिर hdmi_cec_parents[] = अणु "osc32k", "pll-periph0-2x" पूर्ण;
अटल स्थिर काष्ठा ccu_mux_fixed_preभाग hdmi_cec_preभागs[] = अणु
	अणु .index = 1, .भाग = 36621 पूर्ण,
पूर्ण;

#घोषणा SUN50I_H616_HDMI_CEC_CLK_REG		0xb10
अटल काष्ठा ccu_mux hdmi_cec_clk = अणु
	.enable		= BIT(31) | BIT(30),

	.mux		= अणु
		.shअगरt	= 24,
		.width	= 2,

		.fixed_preभागs	= hdmi_cec_preभागs,
		.n_preभागs	= ARRAY_SIZE(hdmi_cec_preभागs),
	पूर्ण,

	.common		= अणु
		.reg		= 0xb10,
		.features	= CCU_FEATURE_FIXED_PREDIV,
		.hw.init	= CLK_HW_INIT_PARENTS("hdmi-cec",
						      hdmi_cec_parents,
						      &ccu_mux_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल SUNXI_CCU_GATE(bus_hdmi_clk, "bus-hdmi", "ahb3", 0xb1c, BIT(0), 0);

अटल SUNXI_CCU_GATE(bus_tcon_top_clk, "bus-tcon-top", "ahb3",
		      0xb5c, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर tcon_tv_parents[] = अणु "pll-video0",
						"pll-video0-4x",
						"pll-video1",
						"pll-video1-4x" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX_GATE(tcon_tv0_clk, "tcon-tv0",
				  tcon_tv_parents, 0xb80,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_MP_WITH_MUX_GATE(tcon_tv1_clk, "tcon-tv1",
				  tcon_tv_parents, 0xb84,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_GATE(bus_tcon_tv0_clk, "bus-tcon-tv0", "ahb3",
		      0xb9c, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_tcon_tv1_clk, "bus-tcon-tv1", "ahb3",
		      0xb9c, BIT(1), 0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(tve0_clk, "tve0",
				  tcon_tv_parents, 0xbb0,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_GATE(bus_tve_top_clk, "bus-tve-top", "ahb3",
		      0xbbc, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_tve0_clk, "bus-tve0", "ahb3",
		      0xbbc, BIT(1), 0);

अटल स्थिर अक्षर * स्थिर hdcp_parents[] = अणु "pll-periph0", "pll-periph1" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(hdcp_clk, "hdcp", hdcp_parents, 0xc40,
				 0, 4,		/* M */
				 24, 2,		/* mux */
				 BIT(31),	/* gate */
				 0);

अटल SUNXI_CCU_GATE(bus_hdcp_clk, "bus-hdcp", "ahb3", 0xc4c, BIT(0), 0);

/* Fixed factor घड़ीs */
अटल CLK_FIXED_FACTOR_FW_NAME(osc12M_clk, "osc12M", "hosc", 2, 1, 0);

अटल स्थिर काष्ठा clk_hw *clk_parent_pll_audio[] = अणु
	&pll_audio_hs_clk.common.hw
पूर्ण;

/*
 * The भागider of pll-audio is fixed to 24 क्रम now, so 24576000 and 22579200
 * rates can be set exactly in conjunction with sigma-delta modulation.
 */
अटल CLK_FIXED_FACTOR_HWS(pll_audio_1x_clk, "pll-audio-1x",
			    clk_parent_pll_audio,
			    96, 1, CLK_SET_RATE_PARENT);
अटल CLK_FIXED_FACTOR_HWS(pll_audio_2x_clk, "pll-audio-2x",
			    clk_parent_pll_audio,
			    48, 1, CLK_SET_RATE_PARENT);
अटल CLK_FIXED_FACTOR_HWS(pll_audio_4x_clk, "pll-audio-4x",
			    clk_parent_pll_audio,
			    24, 1, CLK_SET_RATE_PARENT);

अटल स्थिर काष्ठा clk_hw *pll_periph0_parents[] = अणु
	&pll_periph0_clk.common.hw
पूर्ण;

अटल CLK_FIXED_FACTOR_HWS(pll_periph0_2x_clk, "pll-periph0-2x",
			    pll_periph0_parents,
			    1, 2, 0);

अटल स्थिर काष्ठा clk_hw *pll_periph1_parents[] = अणु
	&pll_periph1_clk.common.hw
पूर्ण;

अटल CLK_FIXED_FACTOR_HWS(pll_periph1_2x_clk, "pll-periph1-2x",
			    pll_periph1_parents,
			    1, 2, 0);

अटल CLK_FIXED_FACTOR_HW(pll_video0_4x_clk, "pll-video0-4x",
			   &pll_video0_clk.common.hw,
			   1, 4, CLK_SET_RATE_PARENT);
अटल CLK_FIXED_FACTOR_HW(pll_video1_4x_clk, "pll-video1-4x",
			   &pll_video1_clk.common.hw,
			   1, 4, CLK_SET_RATE_PARENT);
अटल CLK_FIXED_FACTOR_HW(pll_video2_4x_clk, "pll-video2-4x",
			   &pll_video2_clk.common.hw,
			   1, 4, CLK_SET_RATE_PARENT);

अटल काष्ठा ccu_common *sun50i_h616_ccu_clks[] = अणु
	&pll_cpux_clk.common,
	&pll_ddr0_clk.common,
	&pll_ddr1_clk.common,
	&pll_periph0_clk.common,
	&pll_periph1_clk.common,
	&pll_gpu_clk.common,
	&pll_video0_clk.common,
	&pll_video1_clk.common,
	&pll_video2_clk.common,
	&pll_ve_clk.common,
	&pll_de_clk.common,
	&pll_audio_hs_clk.common,
	&cpux_clk.common,
	&axi_clk.common,
	&cpux_apb_clk.common,
	&psi_ahb1_ahb2_clk.common,
	&ahb3_clk.common,
	&apb1_clk.common,
	&apb2_clk.common,
	&mbus_clk.common,
	&de_clk.common,
	&bus_de_clk.common,
	&deपूर्णांकerlace_clk.common,
	&bus_deपूर्णांकerlace_clk.common,
	&g2d_clk.common,
	&bus_g2d_clk.common,
	&gpu0_clk.common,
	&bus_gpu_clk.common,
	&gpu1_clk.common,
	&ce_clk.common,
	&bus_ce_clk.common,
	&ve_clk.common,
	&bus_ve_clk.common,
	&bus_dma_clk.common,
	&bus_hsसमयr_clk.common,
	&avs_clk.common,
	&bus_dbg_clk.common,
	&bus_psi_clk.common,
	&bus_pwm_clk.common,
	&bus_iommu_clk.common,
	&dram_clk.common,
	&mbus_dma_clk.common,
	&mbus_ve_clk.common,
	&mbus_ce_clk.common,
	&mbus_ts_clk.common,
	&mbus_nand_clk.common,
	&mbus_g2d_clk.common,
	&bus_dram_clk.common,
	&nand0_clk.common,
	&nand1_clk.common,
	&bus_nand_clk.common,
	&mmc0_clk.common,
	&mmc1_clk.common,
	&mmc2_clk.common,
	&bus_mmc0_clk.common,
	&bus_mmc1_clk.common,
	&bus_mmc2_clk.common,
	&bus_uart0_clk.common,
	&bus_uart1_clk.common,
	&bus_uart2_clk.common,
	&bus_uart3_clk.common,
	&bus_uart4_clk.common,
	&bus_uart5_clk.common,
	&bus_i2c0_clk.common,
	&bus_i2c1_clk.common,
	&bus_i2c2_clk.common,
	&bus_i2c3_clk.common,
	&bus_i2c4_clk.common,
	&spi0_clk.common,
	&spi1_clk.common,
	&bus_spi0_clk.common,
	&bus_spi1_clk.common,
	&emac_25m_clk.common,
	&bus_emac0_clk.common,
	&bus_emac1_clk.common,
	&ts_clk.common,
	&bus_ts_clk.common,
	&bus_ths_clk.common,
	&spdअगर_clk.common,
	&bus_spdअगर_clk.common,
	&dmic_clk.common,
	&bus_dmic_clk.common,
	&audio_codec_1x_clk.common,
	&audio_codec_4x_clk.common,
	&bus_audio_codec_clk.common,
	&audio_hub_clk.common,
	&bus_audio_hub_clk.common,
	&usb_ohci0_clk.common,
	&usb_phy0_clk.common,
	&usb_ohci1_clk.common,
	&usb_phy1_clk.common,
	&usb_ohci2_clk.common,
	&usb_phy2_clk.common,
	&usb_ohci3_clk.common,
	&usb_phy3_clk.common,
	&bus_ohci0_clk.common,
	&bus_ohci1_clk.common,
	&bus_ohci2_clk.common,
	&bus_ohci3_clk.common,
	&bus_ehci0_clk.common,
	&bus_ehci1_clk.common,
	&bus_ehci2_clk.common,
	&bus_ehci3_clk.common,
	&bus_otg_clk.common,
	&bus_keyadc_clk.common,
	&hdmi_clk.common,
	&hdmi_slow_clk.common,
	&hdmi_cec_clk.common,
	&bus_hdmi_clk.common,
	&bus_tcon_top_clk.common,
	&tcon_tv0_clk.common,
	&tcon_tv1_clk.common,
	&bus_tcon_tv0_clk.common,
	&bus_tcon_tv1_clk.common,
	&tve0_clk.common,
	&bus_tve_top_clk.common,
	&bus_tve0_clk.common,
	&hdcp_clk.common,
	&bus_hdcp_clk.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sun50i_h616_hw_clks = अणु
	.hws	= अणु
		[CLK_OSC12M]		= &osc12M_clk.hw,
		[CLK_PLL_CPUX]		= &pll_cpux_clk.common.hw,
		[CLK_PLL_DDR0]		= &pll_ddr0_clk.common.hw,
		[CLK_PLL_DDR1]		= &pll_ddr1_clk.common.hw,
		[CLK_PLL_PERIPH0]	= &pll_periph0_clk.common.hw,
		[CLK_PLL_PERIPH0_2X]	= &pll_periph0_2x_clk.hw,
		[CLK_PLL_PERIPH1]	= &pll_periph1_clk.common.hw,
		[CLK_PLL_PERIPH1_2X]	= &pll_periph1_2x_clk.hw,
		[CLK_PLL_GPU]		= &pll_gpu_clk.common.hw,
		[CLK_PLL_VIDEO0]	= &pll_video0_clk.common.hw,
		[CLK_PLL_VIDEO0_4X]	= &pll_video0_4x_clk.hw,
		[CLK_PLL_VIDEO1]	= &pll_video1_clk.common.hw,
		[CLK_PLL_VIDEO1_4X]	= &pll_video1_4x_clk.hw,
		[CLK_PLL_VIDEO2]	= &pll_video2_clk.common.hw,
		[CLK_PLL_VIDEO2_4X]	= &pll_video2_4x_clk.hw,
		[CLK_PLL_VE]		= &pll_ve_clk.common.hw,
		[CLK_PLL_DE]		= &pll_de_clk.common.hw,
		[CLK_PLL_AUDIO_HS]	= &pll_audio_hs_clk.common.hw,
		[CLK_PLL_AUDIO_1X]	= &pll_audio_1x_clk.hw,
		[CLK_PLL_AUDIO_2X]	= &pll_audio_2x_clk.hw,
		[CLK_PLL_AUDIO_4X]	= &pll_audio_4x_clk.hw,
		[CLK_CPUX]		= &cpux_clk.common.hw,
		[CLK_AXI]		= &axi_clk.common.hw,
		[CLK_CPUX_APB]		= &cpux_apb_clk.common.hw,
		[CLK_PSI_AHB1_AHB2]	= &psi_ahb1_ahb2_clk.common.hw,
		[CLK_AHB3]		= &ahb3_clk.common.hw,
		[CLK_APB1]		= &apb1_clk.common.hw,
		[CLK_APB2]		= &apb2_clk.common.hw,
		[CLK_MBUS]		= &mbus_clk.common.hw,
		[CLK_DE]		= &de_clk.common.hw,
		[CLK_BUS_DE]		= &bus_de_clk.common.hw,
		[CLK_DEINTERLACE]	= &deपूर्णांकerlace_clk.common.hw,
		[CLK_BUS_DEINTERLACE]	= &bus_deपूर्णांकerlace_clk.common.hw,
		[CLK_G2D]		= &g2d_clk.common.hw,
		[CLK_BUS_G2D]		= &bus_g2d_clk.common.hw,
		[CLK_GPU0]		= &gpu0_clk.common.hw,
		[CLK_BUS_GPU]		= &bus_gpu_clk.common.hw,
		[CLK_GPU1]		= &gpu1_clk.common.hw,
		[CLK_CE]		= &ce_clk.common.hw,
		[CLK_BUS_CE]		= &bus_ce_clk.common.hw,
		[CLK_VE]		= &ve_clk.common.hw,
		[CLK_BUS_VE]		= &bus_ve_clk.common.hw,
		[CLK_BUS_DMA]		= &bus_dma_clk.common.hw,
		[CLK_BUS_HSTIMER]	= &bus_hsसमयr_clk.common.hw,
		[CLK_AVS]		= &avs_clk.common.hw,
		[CLK_BUS_DBG]		= &bus_dbg_clk.common.hw,
		[CLK_BUS_PSI]		= &bus_psi_clk.common.hw,
		[CLK_BUS_PWM]		= &bus_pwm_clk.common.hw,
		[CLK_BUS_IOMMU]		= &bus_iommu_clk.common.hw,
		[CLK_DRAM]		= &dram_clk.common.hw,
		[CLK_MBUS_DMA]		= &mbus_dma_clk.common.hw,
		[CLK_MBUS_VE]		= &mbus_ve_clk.common.hw,
		[CLK_MBUS_CE]		= &mbus_ce_clk.common.hw,
		[CLK_MBUS_TS]		= &mbus_ts_clk.common.hw,
		[CLK_MBUS_न_अंकD]		= &mbus_nand_clk.common.hw,
		[CLK_MBUS_G2D]		= &mbus_g2d_clk.common.hw,
		[CLK_BUS_DRAM]		= &bus_dram_clk.common.hw,
		[CLK_न_अंकD0]		= &nand0_clk.common.hw,
		[CLK_न_अंकD1]		= &nand1_clk.common.hw,
		[CLK_BUS_न_अंकD]		= &bus_nand_clk.common.hw,
		[CLK_MMC0]		= &mmc0_clk.common.hw,
		[CLK_MMC1]		= &mmc1_clk.common.hw,
		[CLK_MMC2]		= &mmc2_clk.common.hw,
		[CLK_BUS_MMC0]		= &bus_mmc0_clk.common.hw,
		[CLK_BUS_MMC1]		= &bus_mmc1_clk.common.hw,
		[CLK_BUS_MMC2]		= &bus_mmc2_clk.common.hw,
		[CLK_BUS_UART0]		= &bus_uart0_clk.common.hw,
		[CLK_BUS_UART1]		= &bus_uart1_clk.common.hw,
		[CLK_BUS_UART2]		= &bus_uart2_clk.common.hw,
		[CLK_BUS_UART3]		= &bus_uart3_clk.common.hw,
		[CLK_BUS_UART4]		= &bus_uart4_clk.common.hw,
		[CLK_BUS_UART5]		= &bus_uart5_clk.common.hw,
		[CLK_BUS_I2C0]		= &bus_i2c0_clk.common.hw,
		[CLK_BUS_I2C1]		= &bus_i2c1_clk.common.hw,
		[CLK_BUS_I2C2]		= &bus_i2c2_clk.common.hw,
		[CLK_BUS_I2C3]		= &bus_i2c3_clk.common.hw,
		[CLK_BUS_I2C4]		= &bus_i2c4_clk.common.hw,
		[CLK_SPI0]		= &spi0_clk.common.hw,
		[CLK_SPI1]		= &spi1_clk.common.hw,
		[CLK_BUS_SPI0]		= &bus_spi0_clk.common.hw,
		[CLK_BUS_SPI1]		= &bus_spi1_clk.common.hw,
		[CLK_EMAC_25M]		= &emac_25m_clk.common.hw,
		[CLK_BUS_EMAC0]		= &bus_emac0_clk.common.hw,
		[CLK_BUS_EMAC1]		= &bus_emac1_clk.common.hw,
		[CLK_TS]		= &ts_clk.common.hw,
		[CLK_BUS_TS]		= &bus_ts_clk.common.hw,
		[CLK_BUS_THS]		= &bus_ths_clk.common.hw,
		[CLK_SPDIF]		= &spdअगर_clk.common.hw,
		[CLK_BUS_SPDIF]		= &bus_spdअगर_clk.common.hw,
		[CLK_DMIC]		= &dmic_clk.common.hw,
		[CLK_BUS_DMIC]		= &bus_dmic_clk.common.hw,
		[CLK_AUDIO_CODEC_1X]	= &audio_codec_1x_clk.common.hw,
		[CLK_AUDIO_CODEC_4X]	= &audio_codec_4x_clk.common.hw,
		[CLK_BUS_AUDIO_CODEC]	= &bus_audio_codec_clk.common.hw,
		[CLK_AUDIO_HUB]		= &audio_hub_clk.common.hw,
		[CLK_BUS_AUDIO_HUB]	= &bus_audio_hub_clk.common.hw,
		[CLK_USB_OHCI0]		= &usb_ohci0_clk.common.hw,
		[CLK_USB_PHY0]		= &usb_phy0_clk.common.hw,
		[CLK_USB_OHCI1]		= &usb_ohci1_clk.common.hw,
		[CLK_USB_PHY1]		= &usb_phy1_clk.common.hw,
		[CLK_USB_OHCI2]		= &usb_ohci2_clk.common.hw,
		[CLK_USB_PHY2]		= &usb_phy2_clk.common.hw,
		[CLK_USB_OHCI3]		= &usb_ohci3_clk.common.hw,
		[CLK_USB_PHY3]		= &usb_phy3_clk.common.hw,
		[CLK_BUS_OHCI0]		= &bus_ohci0_clk.common.hw,
		[CLK_BUS_OHCI1]		= &bus_ohci1_clk.common.hw,
		[CLK_BUS_OHCI2]		= &bus_ohci2_clk.common.hw,
		[CLK_BUS_OHCI3]		= &bus_ohci3_clk.common.hw,
		[CLK_BUS_EHCI0]		= &bus_ehci0_clk.common.hw,
		[CLK_BUS_EHCI1]		= &bus_ehci1_clk.common.hw,
		[CLK_BUS_EHCI2]		= &bus_ehci2_clk.common.hw,
		[CLK_BUS_EHCI3]		= &bus_ehci3_clk.common.hw,
		[CLK_BUS_OTG]		= &bus_otg_clk.common.hw,
		[CLK_BUS_KEYADC]	= &bus_keyadc_clk.common.hw,
		[CLK_HDMI]		= &hdmi_clk.common.hw,
		[CLK_HDMI_SLOW]		= &hdmi_slow_clk.common.hw,
		[CLK_HDMI_CEC]		= &hdmi_cec_clk.common.hw,
		[CLK_BUS_HDMI]		= &bus_hdmi_clk.common.hw,
		[CLK_BUS_TCON_TOP]	= &bus_tcon_top_clk.common.hw,
		[CLK_TCON_TV0]		= &tcon_tv0_clk.common.hw,
		[CLK_TCON_TV1]		= &tcon_tv1_clk.common.hw,
		[CLK_BUS_TCON_TV0]	= &bus_tcon_tv0_clk.common.hw,
		[CLK_BUS_TCON_TV1]	= &bus_tcon_tv1_clk.common.hw,
		[CLK_TVE0]		= &tve0_clk.common.hw,
		[CLK_BUS_TVE_TOP]	= &bus_tve_top_clk.common.hw,
		[CLK_BUS_TVE0]		= &bus_tve0_clk.common.hw,
		[CLK_HDCP]		= &hdcp_clk.common.hw,
		[CLK_BUS_HDCP]		= &bus_hdcp_clk.common.hw,
	पूर्ण,
	.num = CLK_NUMBER,
पूर्ण;

अटल काष्ठा ccu_reset_map sun50i_h616_ccu_resets[] = अणु
	[RST_MBUS]		= अणु 0x540, BIT(30) पूर्ण,

	[RST_BUS_DE]		= अणु 0x60c, BIT(16) पूर्ण,
	[RST_BUS_DEINTERLACE]	= अणु 0x62c, BIT(16) पूर्ण,
	[RST_BUS_GPU]		= अणु 0x67c, BIT(16) पूर्ण,
	[RST_BUS_CE]		= अणु 0x68c, BIT(16) पूर्ण,
	[RST_BUS_VE]		= अणु 0x69c, BIT(16) पूर्ण,
	[RST_BUS_DMA]		= अणु 0x70c, BIT(16) पूर्ण,
	[RST_BUS_HSTIMER]	= अणु 0x73c, BIT(16) पूर्ण,
	[RST_BUS_DBG]		= अणु 0x78c, BIT(16) पूर्ण,
	[RST_BUS_PSI]		= अणु 0x79c, BIT(16) पूर्ण,
	[RST_BUS_PWM]		= अणु 0x7ac, BIT(16) पूर्ण,
	[RST_BUS_IOMMU]		= अणु 0x7bc, BIT(16) पूर्ण,
	[RST_BUS_DRAM]		= अणु 0x80c, BIT(16) पूर्ण,
	[RST_BUS_न_अंकD]		= अणु 0x82c, BIT(16) पूर्ण,
	[RST_BUS_MMC0]		= अणु 0x84c, BIT(16) पूर्ण,
	[RST_BUS_MMC1]		= अणु 0x84c, BIT(17) पूर्ण,
	[RST_BUS_MMC2]		= अणु 0x84c, BIT(18) पूर्ण,
	[RST_BUS_UART0]		= अणु 0x90c, BIT(16) पूर्ण,
	[RST_BUS_UART1]		= अणु 0x90c, BIT(17) पूर्ण,
	[RST_BUS_UART2]		= अणु 0x90c, BIT(18) पूर्ण,
	[RST_BUS_UART3]		= अणु 0x90c, BIT(19) पूर्ण,
	[RST_BUS_UART4]		= अणु 0x90c, BIT(20) पूर्ण,
	[RST_BUS_UART5]		= अणु 0x90c, BIT(21) पूर्ण,
	[RST_BUS_I2C0]		= अणु 0x91c, BIT(16) पूर्ण,
	[RST_BUS_I2C1]		= अणु 0x91c, BIT(17) पूर्ण,
	[RST_BUS_I2C2]		= अणु 0x91c, BIT(18) पूर्ण,
	[RST_BUS_I2C3]		= अणु 0x91c, BIT(19) पूर्ण,
	[RST_BUS_I2C4]		= अणु 0x91c, BIT(20) पूर्ण,
	[RST_BUS_SPI0]		= अणु 0x96c, BIT(16) पूर्ण,
	[RST_BUS_SPI1]		= अणु 0x96c, BIT(17) पूर्ण,
	[RST_BUS_EMAC0]		= अणु 0x97c, BIT(16) पूर्ण,
	[RST_BUS_EMAC1]		= अणु 0x97c, BIT(17) पूर्ण,
	[RST_BUS_TS]		= अणु 0x9bc, BIT(16) पूर्ण,
	[RST_BUS_THS]		= अणु 0x9fc, BIT(16) पूर्ण,
	[RST_BUS_SPDIF]		= अणु 0xa2c, BIT(16) पूर्ण,
	[RST_BUS_DMIC]		= अणु 0xa4c, BIT(16) पूर्ण,
	[RST_BUS_AUDIO_CODEC]	= अणु 0xa5c, BIT(16) पूर्ण,
	[RST_BUS_AUDIO_HUB]	= अणु 0xa6c, BIT(16) पूर्ण,

	[RST_USB_PHY0]		= अणु 0xa70, BIT(30) पूर्ण,
	[RST_USB_PHY1]		= अणु 0xa74, BIT(30) पूर्ण,
	[RST_USB_PHY2]		= अणु 0xa78, BIT(30) पूर्ण,
	[RST_USB_PHY3]		= अणु 0xa7c, BIT(30) पूर्ण,
	[RST_BUS_OHCI0]		= अणु 0xa8c, BIT(16) पूर्ण,
	[RST_BUS_OHCI1]		= अणु 0xa8c, BIT(17) पूर्ण,
	[RST_BUS_OHCI2]		= अणु 0xa8c, BIT(18) पूर्ण,
	[RST_BUS_OHCI3]		= अणु 0xa8c, BIT(19) पूर्ण,
	[RST_BUS_EHCI0]		= अणु 0xa8c, BIT(20) पूर्ण,
	[RST_BUS_EHCI1]		= अणु 0xa8c, BIT(21) पूर्ण,
	[RST_BUS_EHCI2]		= अणु 0xa8c, BIT(22) पूर्ण,
	[RST_BUS_EHCI3]		= अणु 0xa8c, BIT(23) पूर्ण,
	[RST_BUS_OTG]		= अणु 0xa8c, BIT(24) पूर्ण,
	[RST_BUS_KEYADC]	= अणु 0xa9c, BIT(16) पूर्ण,

	[RST_BUS_HDMI]		= अणु 0xb1c, BIT(16) पूर्ण,
	[RST_BUS_HDMI_SUB]	= अणु 0xb1c, BIT(17) पूर्ण,
	[RST_BUS_TCON_TOP]	= अणु 0xb5c, BIT(16) पूर्ण,
	[RST_BUS_TCON_TV0]	= अणु 0xb9c, BIT(16) पूर्ण,
	[RST_BUS_TCON_TV1]	= अणु 0xb9c, BIT(17) पूर्ण,
	[RST_BUS_TVE_TOP]	= अणु 0xbbc, BIT(16) पूर्ण,
	[RST_BUS_TVE0]		= अणु 0xbbc, BIT(17) पूर्ण,
	[RST_BUS_HDCP]		= अणु 0xc4c, BIT(16) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun50i_h616_ccu_desc = अणु
	.ccu_clks	= sun50i_h616_ccu_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun50i_h616_ccu_clks),

	.hw_clks	= &sun50i_h616_hw_clks,

	.resets		= sun50i_h616_ccu_resets,
	.num_resets	= ARRAY_SIZE(sun50i_h616_ccu_resets),
पूर्ण;

अटल स्थिर u32 pll_regs[] = अणु
	SUN50I_H616_PLL_CPUX_REG,
	SUN50I_H616_PLL_DDR0_REG,
	SUN50I_H616_PLL_DDR1_REG,
	SUN50I_H616_PLL_PERIPH0_REG,
	SUN50I_H616_PLL_PERIPH1_REG,
	SUN50I_H616_PLL_GPU_REG,
	SUN50I_H616_PLL_VIDEO0_REG,
	SUN50I_H616_PLL_VIDEO1_REG,
	SUN50I_H616_PLL_VIDEO2_REG,
	SUN50I_H616_PLL_VE_REG,
	SUN50I_H616_PLL_DE_REG,
	SUN50I_H616_PLL_AUDIO_REG,
पूर्ण;

अटल स्थिर u32 pll_video_regs[] = अणु
	SUN50I_H616_PLL_VIDEO0_REG,
	SUN50I_H616_PLL_VIDEO1_REG,
	SUN50I_H616_PLL_VIDEO2_REG,
पूर्ण;

अटल स्थिर u32 usb2_clk_regs[] = अणु
	SUN50I_H616_USB0_CLK_REG,
	SUN50I_H616_USB1_CLK_REG,
	SUN50I_H616_USB2_CLK_REG,
	SUN50I_H616_USB3_CLK_REG,
पूर्ण;

अटल व्योम __init sun50i_h616_ccu_setup(काष्ठा device_node *node)
अणु
	व्योम __iomem *reg;
	u32 val;
	पूर्णांक i;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg)) अणु
		pr_err("%pOF: Could not map clock registers\n", node);
		वापस;
	पूर्ण

	/* Enable the lock bits and the output enable bits on all PLLs */
	क्रम (i = 0; i < ARRAY_SIZE(pll_regs); i++) अणु
		val = पढ़ोl(reg + pll_regs[i]);
		val |= BIT(29) | BIT(27);
		ग_लिखोl(val, reg + pll_regs[i]);
	पूर्ण

	/*
	 * Force the output भागider of video PLLs to 0.
	 *
	 * See the comment beक्रमe pll-video0 definition क्रम the reason.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(pll_video_regs); i++) अणु
		val = पढ़ोl(reg + pll_video_regs[i]);
		val &= ~BIT(0);
		ग_लिखोl(val, reg + pll_video_regs[i]);
	पूर्ण

	/*
	 * Force OHCI 12M घड़ी sources to 00 (12MHz भागided from 48MHz)
	 *
	 * This घड़ी mux is still mysterious, and the code just enक्रमces
	 * it to have a valid घड़ी parent.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(usb2_clk_regs); i++) अणु
		val = पढ़ोl(reg + usb2_clk_regs[i]);
		val &= ~GENMASK(25, 24);
		ग_लिखोl(val, reg + usb2_clk_regs[i]);
	पूर्ण

	/*
	 * Force the post-भागider of pll-audio to 12 and the output भागider
	 * of it to 2, so 24576000 and 22579200 rates can be set exactly.
	 */
	val = पढ़ोl(reg + SUN50I_H616_PLL_AUDIO_REG);
	val &= ~(GENMASK(21, 16) | BIT(0));
	ग_लिखोl(val | (11 << 16) | BIT(0), reg + SUN50I_H616_PLL_AUDIO_REG);

	/*
	 * First घड़ी parent (osc32K) is unusable क्रम CEC. But since there
	 * is no good way to क्रमce parent चयन (both run with same frequency),
	 * just set second घड़ी parent here.
	 */
	val = पढ़ोl(reg + SUN50I_H616_HDMI_CEC_CLK_REG);
	val |= BIT(24);
	ग_लिखोl(val, reg + SUN50I_H616_HDMI_CEC_CLK_REG);

	i = sunxi_ccu_probe(node, reg, &sun50i_h616_ccu_desc);
	अगर (i)
		pr_err("%pOF: probing clocks fails: %d\n", node, i);
पूर्ण

CLK_OF_DECLARE(sun50i_h616_ccu, "allwinner,sun50i-h616-ccu",
	       sun50i_h616_ccu_setup);
