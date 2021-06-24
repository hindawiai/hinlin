<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020 Yangtao Li <frank@allwinnertech.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
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

#समावेश "ccu-sun50i-a100.h"

#घोषणा SUN50I_A100_PLL_SDM_ENABLE		BIT(24)
#घोषणा SUN50I_A100_PLL_OUTPUT_ENABLE		BIT(27)
#घोषणा SUN50I_A100_PLL_LOCK			BIT(28)
#घोषणा SUN50I_A100_PLL_LOCK_ENABLE		BIT(29)
#घोषणा SUN50I_A100_PLL_ENABLE			BIT(31)

#घोषणा SUN50I_A100_PLL_PERIPH1_PATTERN0	0xd1303333

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
#घोषणा SUN50I_A100_PLL_CPUX_REG		0x000
अटल काष्ठा ccu_mult pll_cpux_clk = अणु
	.enable		= SUN50I_A100_PLL_OUTPUT_ENABLE,
	.lock		= SUN50I_A100_PLL_LOCK,
	.mult		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.common		= अणु
		.reg		= 0x000,
		.hw.init	= CLK_HW_INIT("pll-cpux", "dcxo24M",
					      &ccu_mult_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

/* Some PLLs are input * N / भाग1 / P. Model them as NKMP with no K */
#घोषणा SUN50I_A100_PLL_DDR0_REG		0x010
अटल काष्ठा ccu_nkmp pll_ddr0_clk = अणु
	.enable		= SUN50I_A100_PLL_OUTPUT_ENABLE,
	.lock		= SUN50I_A100_PLL_LOCK,
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output भागider */
	.common		= अणु
		.reg		= 0x010,
		.hw.init	= CLK_HW_INIT("pll-ddr0", "dcxo24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE |
					      CLK_IS_CRITICAL),
	पूर्ण,
पूर्ण;

#घोषणा SUN50I_A100_PLL_PERIPH0_REG	0x020
अटल काष्ठा ccu_nkmp pll_periph0_clk = अणु
	.enable		= SUN50I_A100_PLL_OUTPUT_ENABLE,
	.lock		= SUN50I_A100_PLL_LOCK,
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output भागider */
	.fixed_post_भाग	= 2,
	.common		= अणु
		.reg		= 0x020,
		.features	= CCU_FEATURE_FIXED_POSTDIV,
		.hw.init	= CLK_HW_INIT("pll-periph0", "dcxo24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

#घोषणा SUN50I_A100_PLL_PERIPH1_REG	0x028
अटल काष्ठा ccu_nkmp pll_periph1_clk = अणु
	.enable		= SUN50I_A100_PLL_OUTPUT_ENABLE,
	.lock		= SUN50I_A100_PLL_LOCK,
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output भागider */
	.fixed_post_भाग	= 2,
	.common		= अणु
		.reg		= 0x028,
		.features	= CCU_FEATURE_FIXED_POSTDIV,
		.hw.init	= CLK_HW_INIT("pll-periph1", "dcxo24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;
#घोषणा SUN50I_A100_PLL_PERIPH1_PATTERN0_REG	0x128

#घोषणा SUN50I_A100_PLL_GPU_REG		0x030
अटल काष्ठा ccu_nkmp pll_gpu_clk = अणु
	.enable		= SUN50I_A100_PLL_OUTPUT_ENABLE,
	.lock		= SUN50I_A100_PLL_LOCK,
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output भागider */
	.common		= अणु
		.reg		= 0x030,
		.hw.init	= CLK_HW_INIT("pll-gpu", "dcxo24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

/*
 * For Video PLLs, the output भागider is described as "used for testing"
 * in the user manual. So it's not modelled and क्रमced to 0.
 */
#घोषणा SUN50I_A100_PLL_VIDEO0_REG	0x040
अटल काष्ठा ccu_nm pll_video0_clk = अणु
	.enable		= SUN50I_A100_PLL_OUTPUT_ENABLE,
	.lock		= SUN50I_A100_PLL_LOCK,
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input भागider */
	.fixed_post_भाग	= 4,
	.common		= अणु
		.reg		= 0x040,
		.features	= CCU_FEATURE_FIXED_POSTDIV,
		.hw.init	= CLK_HW_INIT("pll-video0", "dcxo24M",
					      &ccu_nm_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

#घोषणा SUN50I_A100_PLL_VIDEO1_REG	0x048
अटल काष्ठा ccu_nm pll_video1_clk = अणु
	.enable		= SUN50I_A100_PLL_OUTPUT_ENABLE,
	.lock		= SUN50I_A100_PLL_LOCK,
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input भागider */
	.fixed_post_भाग	= 4,
	.common		= अणु
		.reg		= 0x048,
		.features	= CCU_FEATURE_FIXED_POSTDIV,
		.hw.init	= CLK_HW_INIT("pll-video1", "dcxo24M",
					      &ccu_nm_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

#घोषणा SUN50I_A100_PLL_VIDEO2_REG	0x050
अटल काष्ठा ccu_nm pll_video2_clk = अणु
	.enable		= SUN50I_A100_PLL_OUTPUT_ENABLE,
	.lock		= SUN50I_A100_PLL_LOCK,
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input भागider */
	.fixed_post_भाग	= 4,
	.common		= अणु
		.reg		= 0x050,
		.features	= CCU_FEATURE_FIXED_POSTDIV,
		.hw.init	= CLK_HW_INIT("pll-video2", "dcxo24M",
					      &ccu_nm_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

#घोषणा SUN50I_A100_PLL_VE_REG		0x058
अटल काष्ठा ccu_nkmp pll_ve_clk = अणु
	.enable		= SUN50I_A100_PLL_OUTPUT_ENABLE,
	.lock		= SUN50I_A100_PLL_LOCK,
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output भागider */
	.common		= अणु
		.reg		= 0x058,
		.hw.init	= CLK_HW_INIT("pll-ve", "dcxo24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

/*
 * The COM PLL has m0 भागiders in addition to the usual N, M
 * factors. Since we only need 1 frequencies from this PLL: 45.1584 MHz,
 * ignore it क्रम now.
 */
#घोषणा SUN50I_A100_PLL_COM_REG		0x060
अटल काष्ठा ccu_sdm_setting pll_com_sdm_table[] = अणु
	अणु .rate = 451584000, .pattern = 0xc0014396, .m = 2, .n = 37 पूर्ण,
पूर्ण;

अटल काष्ठा ccu_nm pll_com_clk = अणु
	.enable		= SUN50I_A100_PLL_OUTPUT_ENABLE,
	.lock		= SUN50I_A100_PLL_LOCK,
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(0, 1),
	.sdm		= _SUNXI_CCU_SDM(pll_com_sdm_table, BIT(24),
					 0x160, BIT(31)),
	.common		= अणु
		.reg		= 0x060,
		.features	= CCU_FEATURE_SIGMA_DELTA_MOD,
		.hw.init	= CLK_HW_INIT("pll-com", "dcxo24M",
					      &ccu_nm_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

#घोषणा SUN50I_A100_PLL_VIDEO3_REG	0x068
अटल काष्ठा ccu_nm pll_video3_clk = अणु
	.enable		= SUN50I_A100_PLL_OUTPUT_ENABLE,
	.lock		= SUN50I_A100_PLL_LOCK,
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input भागider */
	.fixed_post_भाग	= 4,
	.common		= अणु
		.reg		= 0x068,
		.features	= CCU_FEATURE_FIXED_POSTDIV,
		.hw.init	= CLK_HW_INIT("pll-video3", "dcxo24M",
					      &ccu_nm_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

/*
 * The Audio PLL has m0, m1 भागiders in addition to the usual N, M
 * factors. Since we only need 4 frequencies from this PLL: 22.5792 MHz,
 * 24.576 MHz, 90.3168MHz and 98.304MHz ignore them क्रम now.
 * Enक्रमce the शेष क्रम them, which is m0 = 1, m1 = 0.
 */
#घोषणा SUN50I_A100_PLL_AUDIO_REG		0x078
अटल काष्ठा ccu_sdm_setting pll_audio_sdm_table[] = अणु
	अणु .rate = 45158400, .pattern = 0xc001bcd3, .m = 18, .n = 33 पूर्ण,
	अणु .rate = 49152000, .pattern = 0xc001eb85, .m = 20, .n = 40 पूर्ण,
	अणु .rate = 180633600, .pattern = 0xc001288d, .m = 3, .n = 22 पूर्ण,
	अणु .rate = 196608000, .pattern = 0xc001eb85, .m = 5, .n = 40 पूर्ण,
पूर्ण;

अटल काष्ठा ccu_nm pll_audio_clk = अणु
	.enable		= SUN50I_A100_PLL_OUTPUT_ENABLE,
	.lock		= SUN50I_A100_PLL_LOCK,
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(16, 6),
	.fixed_post_भाग	= 2,
	.sdm		= _SUNXI_CCU_SDM(pll_audio_sdm_table, BIT(24),
					 0x178, BIT(31)),
	.common		= अणु
		.reg		= 0x078,
		.features	= CCU_FEATURE_FIXED_POSTDIV |
				  CCU_FEATURE_SIGMA_DELTA_MOD,
		.hw.init	= CLK_HW_INIT("pll-audio", "dcxo24M",
					      &ccu_nm_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर cpux_parents[] = अणु "dcxo24M", "osc32k",
					     "iosc", "pll-cpux",
					      "pll-periph0" पूर्ण;
अटल SUNXI_CCU_MUX(cpux_clk, "cpux", cpux_parents,
		     0x500, 24, 3, CLK_SET_RATE_PARENT | CLK_IS_CRITICAL);
अटल SUNXI_CCU_M(axi_clk, "axi", "cpux", 0x500, 0, 2, 0);
अटल SUNXI_CCU_M(cpux_apb_clk, "cpux-apb", "cpux", 0x500, 8, 2, 0);

अटल स्थिर अक्षर * स्थिर psi_ahb1_ahb2_parents[] = अणु "dcxo24M", "osc32k",
						      "iosc", "pll-periph0",
						      "pll-periph0-2x" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX(psi_ahb1_ahb2_clk, "psi-ahb1-ahb2",
			     psi_ahb1_ahb2_parents, 0x510,
			     0, 2,	/* M */
			     8, 2,	/* P */
			     24, 3,	/* mux */
			     0);

अटल स्थिर अक्षर * स्थिर ahb3_apb1_apb2_parents[] = अणु "dcxo24M", "osc32k",
						       "psi-ahb1-ahb2",
						       "pll-periph0",
						       "pll-periph0-2x" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX(ahb3_clk, "ahb3", ahb3_apb1_apb2_parents, 0x51c,
			     0, 2,	/* M */
			     8, 2,	/* P */
			     24, 3,	/* mux */
			     0);

अटल SUNXI_CCU_MP_WITH_MUX(apb1_clk, "apb1", ahb3_apb1_apb2_parents, 0x520,
			     0, 2,	/* M */
			     8, 2,	/* P */
			     24, 3,	/* mux */
			     0);

अटल SUNXI_CCU_MP_WITH_MUX(apb2_clk, "apb2", ahb3_apb1_apb2_parents, 0x524,
			     0, 2,	/* M */
			     8, 2,	/* P */
			     24, 3,	/* mux */
			     0);

अटल स्थिर अक्षर * स्थिर mbus_parents[] = अणु "dcxo24M", "pll-ddr0",
					     "pll-periph0",
					     "pll-periph0-2x" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(mbus_clk, "mbus", mbus_parents, 0x540,
				 0, 3,		/* M */
				 24, 2,		/* mux */
				 BIT(31),	/* gate */
				 CLK_IS_CRITICAL);

अटल स्थिर अक्षर * स्थिर de_parents[] = अणु "pll-com", "pll-periph0-2x" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(de_clk, "de0", de_parents, 0x600,
				 0, 4,		/* M */
				 24, 1,		/* mux */
				 BIT(31),	/* gate */
				 CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_GATE(bus_de_clk, "bus-de", "psi-ahb1-ahb2",
		      0x60c, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर g2d_parents[] = अणु "pll-com", "pll-periph0-2x",
					     "pll-video0-2x", "pll-video1-2x",
					     "pll-video2-2x"पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(g2d_clk, "g2d",
				 g2d_parents,
				 0x630,
				 0, 4,		/* M */
				 24, 3,		/* mux */
				 BIT(31),	/* gate */
				 0);

अटल SUNXI_CCU_GATE(bus_g2d_clk, "bus-g2d", "psi-ahb1-ahb2",
		      0x63c, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर gpu_parents[] = अणु "pll-gpu" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(gpu_clk, "gpu", gpu_parents, 0x670,
				       0, 2,	/* M */
				       24, 1,	/* mux */
				       BIT(31),	/* gate */
				       0);

अटल SUNXI_CCU_GATE(bus_gpu_clk, "bus-gpu", "psi-ahb1-ahb2",
		      0x67c, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर ce_parents[] = अणु "dcxo24M", "pll-periph0-2x" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX_GATE(ce_clk, "ce", ce_parents, 0x680,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 1,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_GATE(bus_ce_clk, "bus-ce", "psi-ahb1-ahb2",
		      0x68c, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर ve_parents[] = अणु "pll-ve" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(ve_clk, "ve", ve_parents, 0x690,
				 0, 3,		/* M */
				 24, 1,		/* mux */
				 BIT(31),	/* gate */
				 CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_GATE(bus_ve_clk, "bus-ve", "psi-ahb1-ahb2",
		      0x69c, BIT(0), 0);

अटल SUNXI_CCU_GATE(bus_dma_clk, "bus-dma", "psi-ahb1-ahb2",
		      0x70c, BIT(0), 0);

अटल SUNXI_CCU_GATE(bus_msgbox_clk, "bus-msgbox", "psi-ahb1-ahb2",
		      0x71c, BIT(0), 0);

अटल SUNXI_CCU_GATE(bus_spinlock_clk, "bus-spinlock", "psi-ahb1-ahb2",
		      0x72c, BIT(0), 0);

अटल SUNXI_CCU_GATE(bus_hsसमयr_clk, "bus-hstimer", "psi-ahb1-ahb2",
		      0x73c, BIT(0), 0);

अटल SUNXI_CCU_GATE(avs_clk, "avs", "dcxo24M", 0x740, BIT(31), 0);

अटल SUNXI_CCU_GATE(bus_dbg_clk, "bus-dbg", "psi-ahb1-ahb2",
		      0x78c, BIT(0), 0);

अटल SUNXI_CCU_GATE(bus_psi_clk, "bus-psi", "psi-ahb1-ahb2",
		      0x79c, BIT(0), 0);

अटल SUNXI_CCU_GATE(bus_pwm_clk, "bus-pwm", "apb1", 0x7ac, BIT(0), 0);

अटल SUNXI_CCU_GATE(bus_iommu_clk, "bus-iommu", "apb1", 0x7bc, BIT(0), 0);

अटल SUNXI_CCU_GATE(mbus_dma_clk, "mbus-dma", "mbus",
		      0x804, BIT(0), 0);
अटल SUNXI_CCU_GATE(mbus_ve_clk, "mbus-ve", "mbus",
		      0x804, BIT(1), 0);
अटल SUNXI_CCU_GATE(mbus_ce_clk, "mbus-ce", "mbus",
		      0x804, BIT(2), 0);
अटल SUNXI_CCU_GATE(mbus_nand_clk, "mbus-nand", "mbus",
		      0x804, BIT(5), 0);
अटल SUNXI_CCU_GATE(mbus_csi_clk, "mbus-csi", "mbus",
		      0x804, BIT(8), 0);
अटल SUNXI_CCU_GATE(mbus_isp_clk, "mbus-isp", "mbus",
		      0x804, BIT(9), 0);
अटल SUNXI_CCU_GATE(mbus_g2d_clk, "mbus-g2d", "mbus",
		      0x804, BIT(10), 0);

अटल SUNXI_CCU_GATE(bus_dram_clk, "bus-dram", "psi-ahb1-ahb2",
		      0x80c, BIT(0), CLK_IS_CRITICAL);

अटल स्थिर अक्षर * स्थिर nand_spi_parents[] = अणु "dcxo24M",
						 "pll-periph0",
						 "pll-periph1",
						 "pll-periph0-2x",
						 "pll-periph1-2x" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX_GATE(nand0_clk, "nand0", nand_spi_parents, 0x810,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(nand1_clk, "nand1", nand_spi_parents, 0x814,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_GATE(bus_nand_clk, "bus-nand", "ahb3", 0x82c, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर mmc_parents[] = अणु "dcxo24M", "pll-periph0-2x",
					    "pll-periph1-2x" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX_GATE_POSTDIV(mmc0_clk, "mmc0", mmc_parents, 0x830,
					  0, 4,		/* M */
					  8, 2,		/* P */
					  24, 2,	/* mux */
					  BIT(31),	/* gate */
					  2,		/* post-भाग */
					  CLK_SET_RATE_NO_REPARENT);

अटल SUNXI_CCU_MP_WITH_MUX_GATE_POSTDIV(mmc1_clk, "mmc1", mmc_parents, 0x834,
					  0, 4,		/* M */
					  8, 2,		/* P */
					  24, 2,	/* mux */
					  BIT(31),	/* gate */
					  2,		/* post-भाग */
					  CLK_SET_RATE_NO_REPARENT);

अटल SUNXI_CCU_MP_WITH_MUX_GATE_POSTDIV(mmc2_clk, "mmc2", mmc_parents, 0x838,
					  0, 4,		/* M */
					  8, 2,		/* P */
					  24, 2,	/* mux */
					  BIT(31),	/* gate */
					  2,		/* post-भाग */
					  CLK_SET_RATE_NO_REPARENT);

अटल SUNXI_CCU_GATE(bus_mmc0_clk, "bus-mmc0", "ahb3", 0x84c, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_mmc1_clk, "bus-mmc1", "ahb3", 0x84c, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_mmc2_clk, "bus-mmc2", "ahb3", 0x84c, BIT(2), 0);

अटल SUNXI_CCU_GATE(bus_uart0_clk, "bus-uart0", "apb2", 0x90c, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_uart1_clk, "bus-uart1", "apb2", 0x90c, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_uart2_clk, "bus-uart2", "apb2", 0x90c, BIT(2), 0);
अटल SUNXI_CCU_GATE(bus_uart3_clk, "bus-uart3", "apb2", 0x90c, BIT(3), 0);
अटल SUNXI_CCU_GATE(bus_uart4_clk, "bus-uart4", "apb2", 0x90c, BIT(4), 0);

अटल SUNXI_CCU_GATE(bus_i2c0_clk, "bus-i2c0", "apb2", 0x91c, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_i2c1_clk, "bus-i2c1", "apb2", 0x91c, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_i2c2_clk, "bus-i2c2", "apb2", 0x91c, BIT(2), 0);
अटल SUNXI_CCU_GATE(bus_i2c3_clk, "bus-i2c3", "apb2", 0x91c, BIT(3), 0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(spi0_clk, "spi0", nand_spi_parents, 0x940,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(spi1_clk, "spi1", nand_spi_parents, 0x944,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(spi2_clk, "spi2", nand_spi_parents, 0x948,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_GATE(bus_spi0_clk, "bus-spi0", "ahb3", 0x96c, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_spi1_clk, "bus-spi1", "ahb3", 0x96c, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_spi2_clk, "bus-spi2", "ahb3", 0x96c, BIT(2), 0);

अटल SUNXI_CCU_GATE(emac_25m_clk, "emac-25m", "ahb3", 0x970,
		      BIT(31) | BIT(30), 0);

अटल SUNXI_CCU_GATE(bus_emac_clk, "bus-emac", "ahb3", 0x97c, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर ir_parents[] = अणु "osc32k", "iosc",
					   "pll-periph0", "pll-periph1" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX_GATE(ir_rx_clk, "ir-rx", ir_parents, 0x990,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_GATE(bus_ir_rx_clk, "bus-ir-rx", "ahb3", 0x99c, BIT(0), 0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(ir_tx_clk, "ir-tx", ir_parents, 0x9c0,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_GATE(bus_ir_tx_clk, "bus-ir-tx", "apb1", 0x9cc, BIT(0), 0);

अटल SUNXI_CCU_GATE(bus_gpadc_clk, "bus-gpadc", "apb1", 0x9ec, BIT(0), 0);

अटल SUNXI_CCU_GATE(bus_ths_clk, "bus-ths", "apb1", 0x9fc, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर audio_parents[] = अणु "pll-audio", "pll-com-audio" पूर्ण;
अटल काष्ठा ccu_भाग i2s0_clk = अणु
	.enable		= BIT(31),
	.भाग		= _SUNXI_CCU_DIV_FLAGS(8, 2, CLK_DIVIDER_POWER_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= अणु
		.reg		= 0xa10,
		.hw.init	= CLK_HW_INIT_PARENTS("i2s0",
						      audio_parents,
						      &ccu_भाग_ops,
						      CLK_SET_RATE_PARENT),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_भाग i2s1_clk = अणु
	.enable		= BIT(31),
	.भाग		= _SUNXI_CCU_DIV_FLAGS(8, 2, CLK_DIVIDER_POWER_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= अणु
		.reg		= 0xa14,
		.hw.init	= CLK_HW_INIT_PARENTS("i2s1",
						      audio_parents,
						      &ccu_भाग_ops,
						      CLK_SET_RATE_PARENT),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_भाग i2s2_clk = अणु
	.enable		= BIT(31),
	.भाग		= _SUNXI_CCU_DIV_FLAGS(8, 2, CLK_DIVIDER_POWER_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= अणु
		.reg		= 0xa18,
		.hw.init	= CLK_HW_INIT_PARENTS("i2s2",
						      audio_parents,
						      &ccu_भाग_ops,
						      CLK_SET_RATE_PARENT),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_भाग i2s3_clk = अणु
	.enable		= BIT(31),
	.भाग		= _SUNXI_CCU_DIV_FLAGS(8, 2, CLK_DIVIDER_POWER_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= अणु
		.reg		= 0xa1c,
		.hw.init	= CLK_HW_INIT_PARENTS("i2s3",
						      audio_parents,
						      &ccu_भाग_ops,
						      CLK_SET_RATE_PARENT),
	पूर्ण,
पूर्ण;

अटल SUNXI_CCU_GATE(bus_i2s0_clk, "bus-i2s0", "apb1", 0xa20, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_i2s1_clk, "bus-i2s1", "apb1", 0xa20, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_i2s2_clk, "bus-i2s2", "apb1", 0xa20, BIT(2), 0);
अटल SUNXI_CCU_GATE(bus_i2s3_clk, "bus-i2s3", "apb1", 0xa20, BIT(3), 0);

अटल काष्ठा ccu_भाग spdअगर_clk = अणु
	.enable		= BIT(31),
	.भाग		= _SUNXI_CCU_DIV_FLAGS(8, 2, CLK_DIVIDER_POWER_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= अणु
		.reg		= 0xa24,
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

अटल SUNXI_CCU_M_WITH_MUX_GATE(audio_codec_dac_clk, "audio-codec-dac",
				 audio_parents, 0xa50,
				 0, 4,		/* M */
				 24, 2,		/* mux */
				 BIT(31),	/* gate */
				 0);

अटल SUNXI_CCU_M_WITH_MUX_GATE(audio_codec_adc_clk, "audio-codec-adc",
				 audio_parents, 0xa54,
				 0, 4,		/* M */
				 24, 2,		/* mux */
				 BIT(31),	/* gate */
				 0);

अटल SUNXI_CCU_M_WITH_MUX_GATE(audio_codec_4x_clk, "audio-codec-4x",
				 audio_parents, 0xa58,
				 0, 4,		/* M */
				 24, 2,		/* mux */
				 BIT(31),	/* gate */
				 0);

अटल SUNXI_CCU_GATE(bus_audio_codec_clk, "bus-audio-codec", "apb1", 0xa5c,
		      BIT(0), 0);

/*
 * There are OHCI 12M घड़ी source selection bits क्रम 2 USB 2.0 ports.
 * We will क्रमce them to 0 (12M भागided from 48M).
 */
#घोषणा SUN50I_A100_USB0_CLK_REG		0xa70
#घोषणा SUN50I_A100_USB1_CLK_REG		0xa74

अटल SUNXI_CCU_GATE(usb_ohci0_clk, "usb-ohci0", "osc12M", 0xa70, BIT(31), 0);
अटल SUNXI_CCU_GATE(usb_phy0_clk, "usb-phy0", "dcxo24M", 0xa70, BIT(29), 0);

अटल SUNXI_CCU_GATE(usb_ohci1_clk, "usb-ohci1", "osc12M", 0xa74, BIT(31), 0);
अटल SUNXI_CCU_GATE(usb_phy1_clk, "usb-phy1", "dcxo24M", 0xa74, BIT(29), 0);

अटल SUNXI_CCU_GATE(bus_ohci0_clk, "bus-ohci0", "ahb3", 0xa8c, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_ohci1_clk, "bus-ohci1", "ahb3", 0xa8c, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_ehci0_clk, "bus-ehci0", "ahb3", 0xa8c, BIT(4), 0);
अटल SUNXI_CCU_GATE(bus_ehci1_clk, "bus-ehci1", "ahb3", 0xa8c, BIT(5), 0);
अटल SUNXI_CCU_GATE(bus_otg_clk, "bus-otg", "ahb3", 0xa8c, BIT(8), 0);

अटल SUNXI_CCU_GATE(bus_lradc_clk, "bus-lradc", "ahb3", 0xa9c, BIT(0), 0);

अटल SUNXI_CCU_GATE(bus_dpss_top0_clk, "bus-dpss-top0", "ahb3",
		      0xabc, BIT(0), 0);

अटल SUNXI_CCU_GATE(bus_dpss_top1_clk, "bus-dpss-top1", "ahb3",
		      0xacc, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर mipi_dsi_parents[] = अणु "dcxo24M", "pll-periph0-2x",
						 "pll-periph0" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(mipi_dsi_clk, "mipi-dsi",
				 mipi_dsi_parents,
				 0xb24,
				 0, 4,		/* M */
				 24, 2,		/* mux */
				 BIT(31),	/* gate */
				 0);

अटल SUNXI_CCU_GATE(bus_mipi_dsi_clk, "bus-mipi-dsi", "ahb3",
		      0xb4c, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर tcon_lcd_parents[] = अणु "pll-video0-4x",
						  "pll-video1-4x",
						  "pll-video2-4x",
						  "pll-video3-4x",
						  "pll-periph0-2x" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX_GATE(tcon_lcd_clk, "tcon-lcd0",
				  tcon_lcd_parents, 0xb60,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_GATE(bus_tcon_lcd_clk, "bus-tcon-lcd0", "ahb3",
		      0xb7c, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर ledc_parents[] = अणु "dcxo24M",
					     "pll-periph0" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX_GATE(ledc_clk, "ledc",
				  ledc_parents, 0xbf0,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_GATE(bus_ledc_clk, "bus-ledc", "ahb3", 0xbfc, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर csi_top_parents[] = अणु "pll-periph0-2x",
						"pll-video0-2x",
						"pll-video1-2x",
						"pll-video2-2x",
						"pll-video3-2x" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(csi_top_clk, "csi-top",
				 csi_top_parents, 0xc04,
				 0, 4,		/* M */
				 24, 3,		/* mux */
				 BIT(31),	/* gate */
				 0);

अटल स्थिर अक्षर * स्थिर csi0_mclk_parents[] = अणु "dcxo24M", "pll-video2",
						  "pll-video3", "pll-video0",
						  "pll-video1" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(csi0_mclk_clk, "csi0-mclk",
				 csi0_mclk_parents, 0xc08,
				 0, 5,		/* M */
				 24, 3,		/* mux */
				 BIT(31),	/* gate */
				 0);

अटल स्थिर अक्षर * स्थिर csi1_mclk_parents[] = अणु "dcxo24M", "pll-video3",
						  "pll-video0", "pll-video1",
						  "pll-video2" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(csi1_mclk_clk, "csi1-mclk",
				 csi1_mclk_parents, 0xc0c,
				 0, 5,		/* M */
				 24, 3,		/* mux */
				 BIT(31),	/* gate */
				 0);

अटल SUNXI_CCU_GATE(bus_csi_clk, "bus-csi", "ahb3", 0xc1c, BIT(0), 0);

अटल स्थिर अक्षर * स्थिर csi_isp_parents[] = अणु "pll-periph0-2x",
						"pll-video0-2x",
						"pll-video1-2x",
						"pll-video2-2x",
						"pll-video3-2x" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(csi_isp_clk, "csi-isp",
				 csi_isp_parents, 0xc20,
				 0, 5,		/* M */
				 24, 3,		/* mux */
				 BIT(31),	/* gate */
				 0);

/* Fixed factor घड़ीs */
अटल CLK_FIXED_FACTOR_FW_NAME(osc12M_clk, "osc12M", "hosc", 2, 1, 0);

अटल CLK_FIXED_FACTOR_HW(pll_com_audio_clk, "pll-com-audio",
			   &pll_com_clk.common.hw,
			   5, 1, CLK_SET_RATE_PARENT);

अटल CLK_FIXED_FACTOR_HW(pll_periph0_2x_clk, "pll-periph0-2x",
			   &pll_periph0_clk.common.hw,
			   1, 2, 0);

अटल CLK_FIXED_FACTOR_HW(pll_periph1_2x_clk, "pll-periph1-2x",
			   &pll_periph1_clk.common.hw,
			   1, 2, 0);

अटल स्थिर काष्ठा clk_hw *pll_video0_parents[] = अणु
	&pll_video0_clk.common.hw
पूर्ण;
अटल CLK_FIXED_FACTOR_HWS(pll_video0_4x_clk, "pll-video0-4x",
			    pll_video0_parents,
			    1, 4, CLK_SET_RATE_PARENT);
अटल CLK_FIXED_FACTOR_HWS(pll_video0_2x_clk, "pll-video0-2x",
			    pll_video0_parents,
			    1, 2, CLK_SET_RATE_PARENT);

अटल स्थिर काष्ठा clk_hw *pll_video1_parents[] = अणु
	&pll_video1_clk.common.hw
पूर्ण;
अटल CLK_FIXED_FACTOR_HWS(pll_video1_4x_clk, "pll-video1-4x",
			    pll_video1_parents,
			    1, 4, CLK_SET_RATE_PARENT);
अटल CLK_FIXED_FACTOR_HWS(pll_video1_2x_clk, "pll-video1-2x",
			    pll_video1_parents,
			    1, 2, CLK_SET_RATE_PARENT);

अटल स्थिर काष्ठा clk_hw *pll_video2_parents[] = अणु
	&pll_video2_clk.common.hw
पूर्ण;
अटल CLK_FIXED_FACTOR_HWS(pll_video2_4x_clk, "pll-video2-4x",
			    pll_video2_parents,
			    1, 4, CLK_SET_RATE_PARENT);
अटल CLK_FIXED_FACTOR_HWS(pll_video2_2x_clk, "pll-video2-2x",
			    pll_video2_parents,
			    1, 2, CLK_SET_RATE_PARENT);

अटल स्थिर काष्ठा clk_hw *pll_video3_parents[] = अणु
	&pll_video3_clk.common.hw
पूर्ण;
अटल CLK_FIXED_FACTOR_HWS(pll_video3_4x_clk, "pll-video3-4x",
			    pll_video3_parents,
			    1, 4, CLK_SET_RATE_PARENT);
अटल CLK_FIXED_FACTOR_HWS(pll_video3_2x_clk, "pll-video3-2x",
			    pll_video3_parents,
			    1, 2, CLK_SET_RATE_PARENT);

अटल काष्ठा ccu_common *sun50i_a100_ccu_clks[] = अणु
	&pll_cpux_clk.common,
	&pll_ddr0_clk.common,
	&pll_periph0_clk.common,
	&pll_periph1_clk.common,
	&pll_gpu_clk.common,
	&pll_video0_clk.common,
	&pll_video1_clk.common,
	&pll_video2_clk.common,
	&pll_video3_clk.common,
	&pll_ve_clk.common,
	&pll_com_clk.common,
	&pll_audio_clk.common,
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
	&g2d_clk.common,
	&bus_g2d_clk.common,
	&gpu_clk.common,
	&bus_gpu_clk.common,
	&ce_clk.common,
	&bus_ce_clk.common,
	&ve_clk.common,
	&bus_ve_clk.common,
	&bus_dma_clk.common,
	&bus_msgbox_clk.common,
	&bus_spinlock_clk.common,
	&bus_hsसमयr_clk.common,
	&avs_clk.common,
	&bus_dbg_clk.common,
	&bus_psi_clk.common,
	&bus_pwm_clk.common,
	&bus_iommu_clk.common,
	&mbus_dma_clk.common,
	&mbus_ve_clk.common,
	&mbus_ce_clk.common,
	&mbus_nand_clk.common,
	&mbus_csi_clk.common,
	&mbus_isp_clk.common,
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
	&bus_i2c0_clk.common,
	&bus_i2c1_clk.common,
	&bus_i2c2_clk.common,
	&bus_i2c3_clk.common,
	&spi0_clk.common,
	&spi1_clk.common,
	&spi2_clk.common,
	&bus_spi0_clk.common,
	&bus_spi1_clk.common,
	&bus_spi2_clk.common,
	&emac_25m_clk.common,
	&bus_emac_clk.common,
	&ir_rx_clk.common,
	&bus_ir_rx_clk.common,
	&ir_tx_clk.common,
	&bus_ir_tx_clk.common,
	&bus_gpadc_clk.common,
	&bus_ths_clk.common,
	&i2s0_clk.common,
	&i2s1_clk.common,
	&i2s2_clk.common,
	&i2s3_clk.common,
	&bus_i2s0_clk.common,
	&bus_i2s1_clk.common,
	&bus_i2s2_clk.common,
	&bus_i2s3_clk.common,
	&spdअगर_clk.common,
	&bus_spdअगर_clk.common,
	&dmic_clk.common,
	&bus_dmic_clk.common,
	&audio_codec_dac_clk.common,
	&audio_codec_adc_clk.common,
	&audio_codec_4x_clk.common,
	&bus_audio_codec_clk.common,
	&usb_ohci0_clk.common,
	&usb_phy0_clk.common,
	&usb_ohci1_clk.common,
	&usb_phy1_clk.common,
	&bus_ohci0_clk.common,
	&bus_ohci1_clk.common,
	&bus_ehci0_clk.common,
	&bus_ehci1_clk.common,
	&bus_otg_clk.common,
	&bus_lradc_clk.common,
	&bus_dpss_top0_clk.common,
	&bus_dpss_top1_clk.common,
	&mipi_dsi_clk.common,
	&bus_mipi_dsi_clk.common,
	&tcon_lcd_clk.common,
	&bus_tcon_lcd_clk.common,
	&ledc_clk.common,
	&bus_ledc_clk.common,
	&csi_top_clk.common,
	&csi0_mclk_clk.common,
	&csi1_mclk_clk.common,
	&bus_csi_clk.common,
	&csi_isp_clk.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sun50i_a100_hw_clks = अणु
	.hws	= अणु
		[CLK_OSC12M]		= &osc12M_clk.hw,
		[CLK_PLL_CPUX]		= &pll_cpux_clk.common.hw,
		[CLK_PLL_DDR0]		= &pll_ddr0_clk.common.hw,
		[CLK_PLL_PERIPH0]	= &pll_periph0_clk.common.hw,
		[CLK_PLL_PERIPH0_2X]	= &pll_periph0_2x_clk.hw,
		[CLK_PLL_PERIPH1]	= &pll_periph1_clk.common.hw,
		[CLK_PLL_PERIPH1_2X]	= &pll_periph1_2x_clk.hw,
		[CLK_PLL_GPU]		= &pll_gpu_clk.common.hw,
		[CLK_PLL_VIDEO0]	= &pll_video0_clk.common.hw,
		[CLK_PLL_VIDEO0_2X]	= &pll_video0_2x_clk.hw,
		[CLK_PLL_VIDEO0_4X]	= &pll_video0_4x_clk.hw,
		[CLK_PLL_VIDEO1]	= &pll_video1_clk.common.hw,
		[CLK_PLL_VIDEO1_2X]	= &pll_video1_2x_clk.hw,
		[CLK_PLL_VIDEO1_4X]	= &pll_video1_4x_clk.hw,
		[CLK_PLL_VIDEO2]	= &pll_video2_clk.common.hw,
		[CLK_PLL_VIDEO2_2X]	= &pll_video2_2x_clk.hw,
		[CLK_PLL_VIDEO2_4X]	= &pll_video2_4x_clk.hw,
		[CLK_PLL_VIDEO3]	= &pll_video3_clk.common.hw,
		[CLK_PLL_VIDEO3_2X]	= &pll_video3_2x_clk.hw,
		[CLK_PLL_VIDEO3_4X]	= &pll_video3_4x_clk.hw,
		[CLK_PLL_VE]		= &pll_ve_clk.common.hw,
		[CLK_PLL_COM]		= &pll_com_clk.common.hw,
		[CLK_PLL_COM_AUDIO]	= &pll_com_audio_clk.hw,
		[CLK_PLL_AUDIO]		= &pll_audio_clk.common.hw,
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
		[CLK_G2D]		= &g2d_clk.common.hw,
		[CLK_BUS_G2D]		= &bus_g2d_clk.common.hw,
		[CLK_GPU]		= &gpu_clk.common.hw,
		[CLK_BUS_GPU]		= &bus_gpu_clk.common.hw,
		[CLK_CE]		= &ce_clk.common.hw,
		[CLK_BUS_CE]		= &bus_ce_clk.common.hw,
		[CLK_VE]		= &ve_clk.common.hw,
		[CLK_BUS_VE]		= &bus_ve_clk.common.hw,
		[CLK_BUS_DMA]		= &bus_dma_clk.common.hw,
		[CLK_BUS_MSGBOX]	= &bus_msgbox_clk.common.hw,
		[CLK_BUS_SPINLOCK]	= &bus_spinlock_clk.common.hw,
		[CLK_BUS_HSTIMER]	= &bus_hsसमयr_clk.common.hw,
		[CLK_AVS]		= &avs_clk.common.hw,
		[CLK_BUS_DBG]		= &bus_dbg_clk.common.hw,
		[CLK_BUS_PSI]		= &bus_psi_clk.common.hw,
		[CLK_BUS_PWM]		= &bus_pwm_clk.common.hw,
		[CLK_BUS_IOMMU]		= &bus_iommu_clk.common.hw,
		[CLK_MBUS_DMA]		= &mbus_dma_clk.common.hw,
		[CLK_MBUS_VE]		= &mbus_ve_clk.common.hw,
		[CLK_MBUS_CE]		= &mbus_ce_clk.common.hw,
		[CLK_MBUS_न_अंकD]		= &mbus_nand_clk.common.hw,
		[CLK_MBUS_CSI]		= &mbus_csi_clk.common.hw,
		[CLK_MBUS_ISP]		= &mbus_isp_clk.common.hw,
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
		[CLK_BUS_I2C0]		= &bus_i2c0_clk.common.hw,
		[CLK_BUS_I2C1]		= &bus_i2c1_clk.common.hw,
		[CLK_BUS_I2C2]		= &bus_i2c2_clk.common.hw,
		[CLK_BUS_I2C3]		= &bus_i2c3_clk.common.hw,
		[CLK_SPI0]		= &spi0_clk.common.hw,
		[CLK_SPI1]		= &spi1_clk.common.hw,
		[CLK_SPI2]		= &spi2_clk.common.hw,
		[CLK_BUS_SPI0]		= &bus_spi0_clk.common.hw,
		[CLK_BUS_SPI1]		= &bus_spi1_clk.common.hw,
		[CLK_BUS_SPI2]		= &bus_spi2_clk.common.hw,
		[CLK_EMAC_25M]		= &emac_25m_clk.common.hw,
		[CLK_BUS_EMAC]		= &bus_emac_clk.common.hw,
		[CLK_IR_RX]		= &ir_rx_clk.common.hw,
		[CLK_BUS_IR_RX]		= &bus_ir_rx_clk.common.hw,
		[CLK_IR_TX]		= &ir_tx_clk.common.hw,
		[CLK_BUS_IR_TX]		= &bus_ir_tx_clk.common.hw,
		[CLK_BUS_GPADC]		= &bus_gpadc_clk.common.hw,
		[CLK_BUS_THS]		= &bus_ths_clk.common.hw,
		[CLK_I2S0]		= &i2s0_clk.common.hw,
		[CLK_I2S1]		= &i2s1_clk.common.hw,
		[CLK_I2S2]		= &i2s2_clk.common.hw,
		[CLK_I2S3]		= &i2s3_clk.common.hw,
		[CLK_BUS_I2S0]		= &bus_i2s0_clk.common.hw,
		[CLK_BUS_I2S1]		= &bus_i2s1_clk.common.hw,
		[CLK_BUS_I2S2]		= &bus_i2s2_clk.common.hw,
		[CLK_BUS_I2S3]		= &bus_i2s3_clk.common.hw,
		[CLK_SPDIF]		= &spdअगर_clk.common.hw,
		[CLK_BUS_SPDIF]		= &bus_spdअगर_clk.common.hw,
		[CLK_DMIC]		= &dmic_clk.common.hw,
		[CLK_BUS_DMIC]		= &bus_dmic_clk.common.hw,
		[CLK_AUDIO_DAC]		= &audio_codec_dac_clk.common.hw,
		[CLK_AUDIO_ADC]		= &audio_codec_adc_clk.common.hw,
		[CLK_AUDIO_4X]		= &audio_codec_4x_clk.common.hw,
		[CLK_BUS_AUDIO_CODEC]	= &bus_audio_codec_clk.common.hw,
		[CLK_USB_OHCI0]		= &usb_ohci0_clk.common.hw,
		[CLK_USB_PHY0]		= &usb_phy0_clk.common.hw,
		[CLK_USB_OHCI1]		= &usb_ohci1_clk.common.hw,
		[CLK_USB_PHY1]		= &usb_phy1_clk.common.hw,
		[CLK_BUS_OHCI0]		= &bus_ohci0_clk.common.hw,
		[CLK_BUS_OHCI1]		= &bus_ohci1_clk.common.hw,
		[CLK_BUS_EHCI0]		= &bus_ehci0_clk.common.hw,
		[CLK_BUS_EHCI1]		= &bus_ehci1_clk.common.hw,
		[CLK_BUS_OTG]		= &bus_otg_clk.common.hw,
		[CLK_BUS_LRADC]		= &bus_lradc_clk.common.hw,
		[CLK_BUS_DPSS_TOP0]	= &bus_dpss_top0_clk.common.hw,
		[CLK_BUS_DPSS_TOP1]	= &bus_dpss_top1_clk.common.hw,
		[CLK_MIPI_DSI]		= &mipi_dsi_clk.common.hw,
		[CLK_BUS_MIPI_DSI]	= &bus_mipi_dsi_clk.common.hw,
		[CLK_TCON_LCD]		= &tcon_lcd_clk.common.hw,
		[CLK_BUS_TCON_LCD]	= &bus_tcon_lcd_clk.common.hw,
		[CLK_LEDC]		= &ledc_clk.common.hw,
		[CLK_BUS_LEDC]		= &bus_ledc_clk.common.hw,
		[CLK_CSI_TOP]		= &csi_top_clk.common.hw,
		[CLK_CSI0_MCLK]		= &csi0_mclk_clk.common.hw,
		[CLK_CSI1_MCLK]		= &csi1_mclk_clk.common.hw,
		[CLK_BUS_CSI]		= &bus_csi_clk.common.hw,
		[CLK_CSI_ISP]		= &csi_isp_clk.common.hw,
	पूर्ण,
	.num = CLK_NUMBER,
पूर्ण;

अटल काष्ठा ccu_reset_map sun50i_a100_ccu_resets[] = अणु
	[RST_MBUS]		= अणु 0x540, BIT(30) पूर्ण,

	[RST_BUS_DE]		= अणु 0x60c, BIT(16) पूर्ण,
	[RST_BUS_G2D]		= अणु 0x63c, BIT(16) पूर्ण,
	[RST_BUS_GPU]		= अणु 0x67c, BIT(16) पूर्ण,
	[RST_BUS_CE]		= अणु 0x68c, BIT(16) पूर्ण,
	[RST_BUS_VE]		= अणु 0x69c, BIT(16) पूर्ण,
	[RST_BUS_DMA]		= अणु 0x70c, BIT(16) पूर्ण,
	[RST_BUS_MSGBOX]	= अणु 0x71c, BIT(16) पूर्ण,
	[RST_BUS_SPINLOCK]	= अणु 0x72c, BIT(16) पूर्ण,
	[RST_BUS_HSTIMER]	= अणु 0x73c, BIT(16) पूर्ण,
	[RST_BUS_DBG]		= अणु 0x78c, BIT(16) पूर्ण,
	[RST_BUS_PSI]		= अणु 0x79c, BIT(16) पूर्ण,
	[RST_BUS_PWM]		= अणु 0x7ac, BIT(16) पूर्ण,
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
	[RST_BUS_I2C0]		= अणु 0x91c, BIT(16) पूर्ण,
	[RST_BUS_I2C1]		= अणु 0x91c, BIT(17) पूर्ण,
	[RST_BUS_I2C2]		= अणु 0x91c, BIT(18) पूर्ण,
	[RST_BUS_I2C3]		= अणु 0x91c, BIT(19) पूर्ण,
	[RST_BUS_SPI0]		= अणु 0x96c, BIT(16) पूर्ण,
	[RST_BUS_SPI1]		= अणु 0x96c, BIT(17) पूर्ण,
	[RST_BUS_SPI2]		= अणु 0x96c, BIT(18) पूर्ण,
	[RST_BUS_EMAC]		= अणु 0x97c, BIT(16) पूर्ण,
	[RST_BUS_IR_RX]		= अणु 0x99c, BIT(16) पूर्ण,
	[RST_BUS_IR_TX]		= अणु 0x9cc, BIT(16) पूर्ण,
	[RST_BUS_GPADC]		= अणु 0x9ec, BIT(16) पूर्ण,
	[RST_BUS_THS]		= अणु 0x9fc, BIT(16) पूर्ण,
	[RST_BUS_I2S0]		= अणु 0xa20, BIT(16) पूर्ण,
	[RST_BUS_I2S1]		= अणु 0xa20, BIT(17) पूर्ण,
	[RST_BUS_I2S2]		= अणु 0xa20, BIT(18) पूर्ण,
	[RST_BUS_I2S3]		= अणु 0xa20, BIT(19) पूर्ण,
	[RST_BUS_SPDIF]		= अणु 0xa2c, BIT(16) पूर्ण,
	[RST_BUS_DMIC]		= अणु 0xa4c, BIT(16) पूर्ण,
	[RST_BUS_AUDIO_CODEC]	= अणु 0xa5c, BIT(16) पूर्ण,

	[RST_USB_PHY0]		= अणु 0xa70, BIT(30) पूर्ण,
	[RST_USB_PHY1]		= अणु 0xa74, BIT(30) पूर्ण,

	[RST_BUS_OHCI0]		= अणु 0xa8c, BIT(16) पूर्ण,
	[RST_BUS_OHCI1]		= अणु 0xa8c, BIT(17) पूर्ण,
	[RST_BUS_EHCI0]		= अणु 0xa8c, BIT(20) पूर्ण,
	[RST_BUS_EHCI1]		= अणु 0xa8c, BIT(21) पूर्ण,
	[RST_BUS_OTG]		= अणु 0xa8c, BIT(24) पूर्ण,

	[RST_BUS_LRADC]		= अणु 0xa9c, BIT(16) पूर्ण,
	[RST_BUS_DPSS_TOP0]	= अणु 0xabc, BIT(16) पूर्ण,
	[RST_BUS_DPSS_TOP1]	= अणु 0xacc, BIT(16) पूर्ण,
	[RST_BUS_MIPI_DSI]	= अणु 0xb4c, BIT(16) पूर्ण,
	[RST_BUS_TCON_LCD]	= अणु 0xb7c, BIT(16) पूर्ण,
	[RST_BUS_LVDS]		= अणु 0xbac, BIT(16) पूर्ण,
	[RST_BUS_LEDC]		= अणु 0xbfc, BIT(16) पूर्ण,
	[RST_BUS_CSI]		= अणु 0xc1c, BIT(16) पूर्ण,
	[RST_BUS_CSI_ISP]	= अणु 0xc2c, BIT(16) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun50i_a100_ccu_desc = अणु
	.ccu_clks	= sun50i_a100_ccu_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun50i_a100_ccu_clks),

	.hw_clks	= &sun50i_a100_hw_clks,

	.resets		= sun50i_a100_ccu_resets,
	.num_resets	= ARRAY_SIZE(sun50i_a100_ccu_resets),
पूर्ण;

अटल स्थिर u32 sun50i_a100_pll_regs[] = अणु
	SUN50I_A100_PLL_CPUX_REG,
	SUN50I_A100_PLL_DDR0_REG,
	SUN50I_A100_PLL_PERIPH0_REG,
	SUN50I_A100_PLL_PERIPH1_REG,
	SUN50I_A100_PLL_GPU_REG,
	SUN50I_A100_PLL_VIDEO0_REG,
	SUN50I_A100_PLL_VIDEO1_REG,
	SUN50I_A100_PLL_VIDEO2_REG,
	SUN50I_A100_PLL_VIDEO3_REG,
	SUN50I_A100_PLL_VE_REG,
	SUN50I_A100_PLL_COM_REG,
	SUN50I_A100_PLL_AUDIO_REG,
पूर्ण;

अटल स्थिर u32 sun50i_a100_pll_video_regs[] = अणु
	SUN50I_A100_PLL_VIDEO0_REG,
	SUN50I_A100_PLL_VIDEO1_REG,
	SUN50I_A100_PLL_VIDEO2_REG,
	SUN50I_A100_PLL_VIDEO3_REG,
पूर्ण;

अटल स्थिर u32 sun50i_a100_usb2_clk_regs[] = अणु
	SUN50I_A100_USB0_CLK_REG,
	SUN50I_A100_USB1_CLK_REG,
पूर्ण;

अटल काष्ठा ccu_pll_nb sun50i_a100_pll_cpu_nb = अणु
	.common = &pll_cpux_clk.common,
	/* copy from pll_cpux_clk */
	.enable = BIT(27),
	.lock   = BIT(28),
पूर्ण;

अटल काष्ठा ccu_mux_nb sun50i_a100_cpu_nb = अणु
	.common         = &cpux_clk.common,
	.cm             = &cpux_clk.mux,
	.delay_us       = 1,
	.bypass_index   = 4, /* index of pll periph0 */
पूर्ण;

अटल पूर्णांक sun50i_a100_ccu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *reg;
	u32 val;
	पूर्णांक i, ret;

	reg = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	/*
	 * Enable lock and enable bits on all PLLs.
	 *
	 * Due to the current design, multiple PLLs share one घातer चयन,
	 * so चयनing PLL is easy to cause stability problems.
	 * When initializing, we enable them by शेष. When disable,
	 * we only turn off the output of PLL.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(sun50i_a100_pll_regs); i++) अणु
		val = पढ़ोl(reg + sun50i_a100_pll_regs[i]);
		val |= SUN50I_A100_PLL_LOCK_ENABLE | SUN50I_A100_PLL_ENABLE;
		ग_लिखोl(val, reg + sun50i_a100_pll_regs[i]);
	पूर्ण

	/*
	 * In order to pass the EMI certअगरication, the SDM function of
	 * the peripheral 1 bus is enabled, and the frequency is still
	 * calculated using the previous भागision factor.
	 */
	ग_लिखोl(SUN50I_A100_PLL_PERIPH1_PATTERN0,
	       reg + SUN50I_A100_PLL_PERIPH1_PATTERN0_REG);

	val = पढ़ोl(reg + SUN50I_A100_PLL_PERIPH1_REG);
	val |= SUN50I_A100_PLL_SDM_ENABLE;
	ग_लिखोl(val, reg + SUN50I_A100_PLL_PERIPH1_REG);

	/*
	 * Force the output भागider of video PLLs to 0.
	 *
	 * See the comment beक्रमe pll-video0 definition क्रम the reason.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(sun50i_a100_pll_video_regs); i++) अणु
		val = पढ़ोl(reg + sun50i_a100_pll_video_regs[i]);
		val &= ~BIT(0);
		ग_लिखोl(val, reg + sun50i_a100_pll_video_regs[i]);
	पूर्ण

	/*
	 * Enक्रमce m1 = 0, m0 = 1 क्रम Audio PLL
	 *
	 * See the comment beक्रमe pll-audio definition क्रम the reason.
	 */
	val = पढ़ोl(reg + SUN50I_A100_PLL_AUDIO_REG);
	val &= ~BIT(1);
	val |= BIT(0);
	ग_लिखोl(val, reg + SUN50I_A100_PLL_AUDIO_REG);

	/*
	 * Force OHCI 12M घड़ी sources to 00 (12MHz भागided from 48MHz)
	 *
	 * This घड़ी mux is still mysterious, and the code just enक्रमces
	 * it to have a valid घड़ी parent.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(sun50i_a100_usb2_clk_regs); i++) अणु
		val = पढ़ोl(reg + sun50i_a100_usb2_clk_regs[i]);
		val &= ~GENMASK(25, 24);
		ग_लिखोl(val, reg + sun50i_a100_usb2_clk_regs[i]);
	पूर्ण

	ret = sunxi_ccu_probe(pdev->dev.of_node, reg, &sun50i_a100_ccu_desc);
	अगर (ret)
		वापस ret;

	/* Gate then ungate PLL CPU after any rate changes */
	ccu_pll_notअगरier_रेजिस्टर(&sun50i_a100_pll_cpu_nb);

	/* Reparent CPU during PLL CPU rate changes */
	ccu_mux_notअगरier_रेजिस्टर(pll_cpux_clk.common.hw.clk,
				  &sun50i_a100_cpu_nb);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun50i_a100_ccu_ids[] = अणु
	अणु .compatible = "allwinner,sun50i-a100-ccu" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sun50i_a100_ccu_driver = अणु
	.probe	= sun50i_a100_ccu_probe,
	.driver	= अणु
		.name	= "sun50i-a100-ccu",
		.of_match_table	= sun50i_a100_ccu_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun50i_a100_ccu_driver);
