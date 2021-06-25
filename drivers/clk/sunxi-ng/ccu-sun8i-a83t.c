<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017 Chen-Yu Tsai. All rights reserved.
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
#समावेश "ccu_mux.h"
#समावेश "ccu_nkmp.h"
#समावेश "ccu_nm.h"
#समावेश "ccu_phase.h"

#समावेश "ccu-sun8i-a83t.h"

#घोषणा CCU_SUN8I_A83T_LOCK_REG	0x20c

/*
 * The CPU PLLs are actually NP घड़ीs, with P being /1 or /4. However
 * P should only be used क्रम output frequencies lower than 228 MHz.
 * Neither मुख्यline Linux, U-boot, nor the venकरोr BSPs use these.
 *
 * For now we can just model it as a multiplier घड़ी, and क्रमce P to /1.
 */
#घोषणा SUN8I_A83T_PLL_C0CPUX_REG	0x000
#घोषणा SUN8I_A83T_PLL_C1CPUX_REG	0x004

अटल काष्ठा ccu_mult pll_c0cpux_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(0),
	.mult		= _SUNXI_CCU_MULT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.common		= अणु
		.reg		= SUN8I_A83T_PLL_C0CPUX_REG,
		.lock_reg	= CCU_SUN8I_A83T_LOCK_REG,
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
		.reg		= SUN8I_A83T_PLL_C1CPUX_REG,
		.lock_reg	= CCU_SUN8I_A83T_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-c1cpux", "osc24M",
					      &ccu_mult_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

/*
 * The Audio PLL has d1, d2 भागiders in addition to the usual N, M
 * factors. Since we only need 2 frequencies from this PLL: 22.5792 MHz
 * and 24.576 MHz, ignore them क्रम now. Enक्रमce the शेष क्रम them,
 * which is d1 = 0, d2 = 1.
 */
#घोषणा SUN8I_A83T_PLL_AUDIO_REG	0x008

/* घड़ी rates द्विगुनd क्रम post भागider */
अटल काष्ठा ccu_sdm_setting pll_audio_sdm_table[] = अणु
	अणु .rate = 45158400, .pattern = 0xc00121ff, .m = 29, .n = 54 पूर्ण,
	अणु .rate = 49152000, .pattern = 0xc000e147, .m = 30, .n = 61 पूर्ण,
पूर्ण;

अटल काष्ठा ccu_nm pll_audio_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(2),
	.n		= _SUNXI_CCU_MULT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(0, 6),
	.fixed_post_भाग	= 2,
	.sdm		= _SUNXI_CCU_SDM(pll_audio_sdm_table, BIT(24),
					 0x284, BIT(31)),
	.common		= अणु
		.reg		= SUN8I_A83T_PLL_AUDIO_REG,
		.lock_reg	= CCU_SUN8I_A83T_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG |
				  CCU_FEATURE_FIXED_POSTDIV |
				  CCU_FEATURE_SIGMA_DELTA_MOD,
		.hw.init	= CLK_HW_INIT("pll-audio", "osc24M",
					      &ccu_nm_ops, CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

/* Some PLLs are input * N / भाग1 / P. Model them as NKMP with no K */
अटल काष्ठा ccu_nkmp pll_video0_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(3),
	.n		= _SUNXI_CCU_MULT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(0, 2), /* output भागider */
	.max_rate	= 3000000000UL,
	.common		= अणु
		.reg		= 0x010,
		.lock_reg	= CCU_SUN8I_A83T_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-video0", "osc24M",
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
		.reg		= 0x018,
		.lock_reg	= CCU_SUN8I_A83T_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-ve", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_nkmp pll_ddr_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(5),
	.n		= _SUNXI_CCU_MULT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(18, 1), /* output भागider */
	.common		= अणु
		.reg		= 0x020,
		.lock_reg	= CCU_SUN8I_A83T_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-ddr", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_nkmp pll_periph_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(6),
	.n		= _SUNXI_CCU_MULT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(18, 1), /* output भागider */
	.common		= अणु
		.reg		= 0x028,
		.lock_reg	= CCU_SUN8I_A83T_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-periph", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_nkmp pll_gpu_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(7),
	.n		= _SUNXI_CCU_MULT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(18, 1), /* output भागider */
	.common		= अणु
		.reg		= 0x038,
		.lock_reg	= CCU_SUN8I_A83T_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-gpu", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_nkmp pll_hsic_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(8),
	.n		= _SUNXI_CCU_MULT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(18, 1), /* output भागider */
	.common		= अणु
		.reg		= 0x044,
		.lock_reg	= CCU_SUN8I_A83T_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-hsic", "osc24M",
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
		.reg		= 0x048,
		.lock_reg	= CCU_SUN8I_A83T_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-de", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_nkmp pll_video1_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(10),
	.n		= _SUNXI_CCU_MULT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input भागider */
	.p		= _SUNXI_CCU_DIV(0, 2), /* बाह्यal भागider p */
	.max_rate	= 3000000000UL,
	.common		= अणु
		.reg		= 0x04c,
		.lock_reg	= CCU_SUN8I_A83T_LOCK_REG,
		.features	= CCU_FEATURE_LOCK_REG,
		.hw.init	= CLK_HW_INIT("pll-video1", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर c0cpux_parents[] = अणु "osc24M", "pll-c0cpux" पूर्ण;
अटल SUNXI_CCU_MUX(c0cpux_clk, "c0cpux", c0cpux_parents,
		     0x50, 12, 1, CLK_SET_RATE_PARENT | CLK_IS_CRITICAL);

अटल स्थिर अक्षर * स्थिर c1cpux_parents[] = अणु "osc24M", "pll-c1cpux" पूर्ण;
अटल SUNXI_CCU_MUX(c1cpux_clk, "c1cpux", c1cpux_parents,
		     0x50, 28, 1, CLK_SET_RATE_PARENT | CLK_IS_CRITICAL);

अटल SUNXI_CCU_M(axi0_clk, "axi0", "c0cpux", 0x050, 0, 2, 0);
अटल SUNXI_CCU_M(axi1_clk, "axi1", "c1cpux", 0x050, 16, 2, 0);

अटल स्थिर अक्षर * स्थिर ahb1_parents[] = अणु "osc16M-d512", "osc24M",
					     "pll-periph",
					     "pll-periph" पूर्ण;
अटल स्थिर काष्ठा ccu_mux_var_preभाग ahb1_preभागs[] = अणु
	अणु .index = 2, .shअगरt = 6, .width = 2 पूर्ण,
	अणु .index = 3, .shअगरt = 6, .width = 2 पूर्ण,
पूर्ण;
अटल काष्ठा ccu_भाग ahb1_clk = अणु
	.भाग		= _SUNXI_CCU_DIV_FLAGS(4, 2, CLK_DIVIDER_POWER_OF_TWO),
	.mux		= अणु
		.shअगरt	= 12,
		.width	= 2,

		.var_preभागs	= ahb1_preभागs,
		.n_var_preभागs	= ARRAY_SIZE(ahb1_preभागs),
	पूर्ण,
	.common		= अणु
		.reg		= 0x054,
		.hw.init	= CLK_HW_INIT_PARENTS("ahb1",
						      ahb1_parents,
						      &ccu_भाग_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल SUNXI_CCU_M(apb1_clk, "apb1", "ahb1", 0x054, 8, 2, 0);

अटल स्थिर अक्षर * स्थिर apb2_parents[] = अणु "osc16M-d512", "osc24M",
					     "pll-periph", "pll-periph" पूर्ण;

अटल SUNXI_CCU_MP_WITH_MUX(apb2_clk, "apb2", apb2_parents, 0x058,
			     0, 5,	/* M */
			     16, 2,	/* P */
			     24, 2,	/* mux */
			     0);

अटल स्थिर अक्षर * स्थिर ahb2_parents[] = अणु "ahb1", "pll-periph" पूर्ण;
अटल स्थिर काष्ठा ccu_mux_fixed_preभाग ahb2_preभाग = अणु
	.index = 1, .भाग = 2
पूर्ण;
अटल काष्ठा ccu_mux ahb2_clk = अणु
	.mux		= अणु
		.shअगरt		= 0,
		.width		= 2,
		.fixed_preभागs	= &ahb2_preभाग,
		.n_preभागs	= 1,
	पूर्ण,
	.common		= अणु
		.reg		= 0x05c,
		.hw.init	= CLK_HW_INIT_PARENTS("ahb2",
						      ahb2_parents,
						      &ccu_mux_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल SUNXI_CCU_GATE(bus_mipi_dsi_clk,	"bus-mipi-dsi",	"ahb1",
		      0x060, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_ss_clk,	"bus-ss",	"ahb1",
		      0x060, BIT(5), 0);
अटल SUNXI_CCU_GATE(bus_dma_clk,	"bus-dma",	"ahb1",
		      0x060, BIT(6), 0);
अटल SUNXI_CCU_GATE(bus_mmc0_clk,	"bus-mmc0",	"ahb1",
		      0x060, BIT(8), 0);
अटल SUNXI_CCU_GATE(bus_mmc1_clk,	"bus-mmc1",	"ahb1",
		      0x060, BIT(9), 0);
अटल SUNXI_CCU_GATE(bus_mmc2_clk,	"bus-mmc2",	"ahb1",
		      0x060, BIT(10), 0);
अटल SUNXI_CCU_GATE(bus_nand_clk,	"bus-nand",	"ahb1",
		      0x060, BIT(13), 0);
अटल SUNXI_CCU_GATE(bus_dram_clk,	"bus-dram",	"ahb1",
		      0x060, BIT(14), 0);
अटल SUNXI_CCU_GATE(bus_emac_clk,	"bus-emac",	"ahb2",
		      0x060, BIT(17), 0);
अटल SUNXI_CCU_GATE(bus_hsसमयr_clk,	"bus-hstimer",	"ahb1",
		      0x060, BIT(19), 0);
अटल SUNXI_CCU_GATE(bus_spi0_clk,	"bus-spi0",	"ahb1",
		      0x060, BIT(20), 0);
अटल SUNXI_CCU_GATE(bus_spi1_clk,	"bus-spi1",	"ahb1",
		      0x060, BIT(21), 0);
अटल SUNXI_CCU_GATE(bus_otg_clk,	"bus-otg",	"ahb1",
		      0x060, BIT(24), 0);
अटल SUNXI_CCU_GATE(bus_ehci0_clk,	"bus-ehci0",	"ahb2",
		      0x060, BIT(26), 0);
अटल SUNXI_CCU_GATE(bus_ehci1_clk,	"bus-ehci1",	"ahb2",
		      0x060, BIT(27), 0);
अटल SUNXI_CCU_GATE(bus_ohci0_clk,	"bus-ohci0",	"ahb2",
		      0x060, BIT(29), 0);

अटल SUNXI_CCU_GATE(bus_ve_clk,	"bus-ve",	"ahb1",
		      0x064, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_tcon0_clk,	"bus-tcon0",	"ahb1",
		      0x064, BIT(4), 0);
अटल SUNXI_CCU_GATE(bus_tcon1_clk,	"bus-tcon1",	"ahb1",
		      0x064, BIT(5), 0);
अटल SUNXI_CCU_GATE(bus_csi_clk,	"bus-csi",	"ahb1",
		      0x064, BIT(8), 0);
अटल SUNXI_CCU_GATE(bus_hdmi_clk,	"bus-hdmi",	"ahb1",
		      0x064, BIT(11), 0);
अटल SUNXI_CCU_GATE(bus_de_clk,	"bus-de",	"ahb1",
		      0x064, BIT(12), 0);
अटल SUNXI_CCU_GATE(bus_gpu_clk,	"bus-gpu",	"ahb1",
		      0x064, BIT(20), 0);
अटल SUNXI_CCU_GATE(bus_msgbox_clk,	"bus-msgbox",	"ahb1",
		      0x064, BIT(21), 0);
अटल SUNXI_CCU_GATE(bus_spinlock_clk,	"bus-spinlock",	"ahb1",
		      0x064, BIT(22), 0);

अटल SUNXI_CCU_GATE(bus_spdअगर_clk,	"bus-spdif",	"apb1",
		      0x068, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_pio_clk,	"bus-pio",	"apb1",
		      0x068, BIT(5), 0);
अटल SUNXI_CCU_GATE(bus_i2s0_clk,	"bus-i2s0",	"apb1",
		      0x068, BIT(12), 0);
अटल SUNXI_CCU_GATE(bus_i2s1_clk,	"bus-i2s1",	"apb1",
		      0x068, BIT(13), 0);
अटल SUNXI_CCU_GATE(bus_i2s2_clk,	"bus-i2s2",	"apb1",
		      0x068, BIT(14), 0);
अटल SUNXI_CCU_GATE(bus_tdm_clk,	"bus-tdm",	"apb1",
		      0x068, BIT(15), 0);

अटल SUNXI_CCU_GATE(bus_i2c0_clk,	"bus-i2c0",	"apb2",
		      0x06c, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_i2c1_clk,	"bus-i2c1",	"apb2",
		      0x06c, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_i2c2_clk,	"bus-i2c2",	"apb2",
		      0x06c, BIT(2), 0);
अटल SUNXI_CCU_GATE(bus_uart0_clk,	"bus-uart0",	"apb2",
		      0x06c, BIT(16), 0);
अटल SUNXI_CCU_GATE(bus_uart1_clk,	"bus-uart1",	"apb2",
		      0x06c, BIT(17), 0);
अटल SUNXI_CCU_GATE(bus_uart2_clk,	"bus-uart2",	"apb2",
		      0x06c, BIT(18), 0);
अटल SUNXI_CCU_GATE(bus_uart3_clk,	"bus-uart3",	"apb2",
		      0x06c, BIT(19), 0);
अटल SUNXI_CCU_GATE(bus_uart4_clk,	"bus-uart4",	"apb2",
		      0x06c, BIT(20), 0);

अटल स्थिर अक्षर * स्थिर cci400_parents[] = अणु "osc24M", "pll-periph",
					       "pll-hsic" पूर्ण;
अटल काष्ठा ccu_भाग cci400_clk = अणु
	.भाग		= _SUNXI_CCU_DIV_FLAGS(0, 2, 0),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= अणु
		.reg		= 0x078,
		.hw.init	= CLK_HW_INIT_PARENTS("cci400",
						      cci400_parents,
						      &ccu_भाग_ops,
						      CLK_IS_CRITICAL),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर mod0_शेष_parents[] = अणु "osc24M", "pll-periph" पूर्ण;

अटल SUNXI_CCU_MP_WITH_MUX_GATE(nand_clk, "nand", mod0_शेष_parents,
				  0x080,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(mmc0_clk, "mmc0", mod0_शेष_parents,
				  0x088,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_PHASE(mmc0_sample_clk, "mmc0-sample", "mmc0",
		       0x088, 20, 3, 0);
अटल SUNXI_CCU_PHASE(mmc0_output_clk, "mmc0-output", "mmc0",
		       0x088, 8, 3, 0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(mmc1_clk, "mmc1", mod0_शेष_parents,
				  0x08c,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_PHASE(mmc1_sample_clk, "mmc1-sample", "mmc1",
		       0x08c, 20, 3, 0);
अटल SUNXI_CCU_PHASE(mmc1_output_clk, "mmc1-output", "mmc1",
		       0x08c, 8, 3, 0);

अटल SUNXI_CCU_MP_MMC_WITH_MUX_GATE(mmc2_clk, "mmc2", mod0_शेष_parents,
				      0x090, 0);

अटल SUNXI_CCU_PHASE(mmc2_sample_clk, "mmc2-sample", "mmc2",
		       0x090, 20, 3, 0);
अटल SUNXI_CCU_PHASE(mmc2_output_clk, "mmc2-output", "mmc2",
		       0x090, 8, 3, 0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(ss_clk, "ss", mod0_शेष_parents,
				  0x09c,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(spi0_clk, "spi0", mod0_शेष_parents,
				  0x0a0,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 4,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(spi1_clk, "spi1", mod0_शेष_parents,
				  0x0a4,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 4,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_M_WITH_GATE(i2s0_clk, "i2s0", "pll-audio",
			     0x0b0, 0, 4, BIT(31), CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_M_WITH_GATE(i2s1_clk, "i2s1", "pll-audio",
			     0x0b4, 0, 4, BIT(31), CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_M_WITH_GATE(i2s2_clk, "i2s2", "pll-audio",
			     0x0b8, 0, 4, BIT(31), CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_M_WITH_GATE(tdm_clk, "tdm", "pll-audio",
			     0x0bc, 0, 4, BIT(31), CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_M_WITH_GATE(spdअगर_clk, "spdif", "pll-audio",
			     0x0c0, 0, 4, BIT(31), CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_GATE(usb_phy0_clk,	"usb-phy0",	"osc24M",
		      0x0cc, BIT(8), 0);
अटल SUNXI_CCU_GATE(usb_phy1_clk,	"usb-phy1",	"osc24M",
		      0x0cc, BIT(9), 0);
अटल SUNXI_CCU_GATE(usb_hsic_clk,	"usb-hsic",	"pll-hsic",
		      0x0cc, BIT(10), 0);
अटल काष्ठा ccu_gate usb_hsic_12m_clk = अणु
	.enable	= BIT(11),
	.common	= अणु
		.reg		= 0x0cc,
		.preभाग		= 2,
		.features	= CCU_FEATURE_ALL_PREDIV,
		.hw.init	= CLK_HW_INIT("usb-hsic-12m", "osc24M",
					      &ccu_gate_ops, 0),
	पूर्ण
पूर्ण;
अटल SUNXI_CCU_GATE(usb_ohci0_clk,	"usb-ohci0",	"osc24M",
		      0x0cc, BIT(16), 0);

/* TODO भागider has minimum of 2 */
अटल SUNXI_CCU_M(dram_clk, "dram", "pll-ddr", 0x0f4, 0, 4, CLK_IS_CRITICAL);

अटल SUNXI_CCU_GATE(dram_ve_clk,	"dram-ve",	"dram",
		      0x100, BIT(0), 0);
अटल SUNXI_CCU_GATE(dram_csi_clk,	"dram-csi",	"dram",
		      0x100, BIT(1), 0);

अटल स्थिर अक्षर * स्थिर tcon0_parents[] = अणु "pll-video0" पूर्ण;
अटल SUNXI_CCU_MUX_WITH_GATE(tcon0_clk, "tcon0", tcon0_parents,
				 0x118, 24, 3, BIT(31), CLK_SET_RATE_PARENT);

अटल स्थिर अक्षर * स्थिर tcon1_parents[] = अणु "pll-video1" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(tcon1_clk, "tcon1", tcon1_parents,
				 0x11c, 0, 4, 24, 2, BIT(31), CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_GATE(csi_misc_clk, "csi-misc", "osc24M", 0x130, BIT(16), 0);

अटल SUNXI_CCU_GATE(mipi_csi_clk, "mipi-csi", "osc24M", 0x130, BIT(31), 0);

अटल स्थिर अक्षर * स्थिर csi_mclk_parents[] = अणु "pll-video0", "pll-de",
						 "osc24M" पूर्ण;
अटल स्थिर u8 csi_mclk_table[] = अणु 0, 3, 5 पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_TABLE_GATE(csi_mclk_clk, "csi-mclk",
				       csi_mclk_parents, csi_mclk_table,
				       0x134,
				       0, 5,	/* M */
				       8, 3,	/* mux */
				       BIT(15),	/* gate */
				       0);

अटल स्थिर अक्षर * स्थिर csi_sclk_parents[] = अणु "pll-periph", "pll-ve" पूर्ण;
अटल स्थिर u8 csi_sclk_table[] = अणु 0, 5 पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_TABLE_GATE(csi_sclk_clk, "csi-sclk",
				       csi_sclk_parents, csi_sclk_table,
				       0x134,
				       16, 4,	/* M */
				       24, 3,	/* mux */
				       BIT(31),	/* gate */
				       0);

अटल SUNXI_CCU_M_WITH_GATE(ve_clk, "ve", "pll-ve", 0x13c,
			     16, 3, BIT(31), CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_GATE(avs_clk, "avs", "osc24M", 0x144, BIT(31), 0);

अटल स्थिर अक्षर * स्थिर hdmi_parents[] = अणु "pll-video1" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(hdmi_clk, "hdmi", hdmi_parents,
				 0x150,
				 0, 4,	/* M */
				 24, 2,	/* mux */
				 BIT(31),	/* gate */
				 CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_GATE(hdmi_slow_clk, "hdmi-slow", "osc24M", 0x154, BIT(31), 0);

अटल स्थिर अक्षर * स्थिर mbus_parents[] = अणु "osc24M", "pll-periph",
					     "pll-ddr" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(mbus_clk, "mbus", mbus_parents,
				 0x15c,
				 0, 3,	/* M */
				 24, 2,	/* mux */
				 BIT(31),	/* gate */
				 CLK_IS_CRITICAL);

अटल स्थिर अक्षर * स्थिर mipi_dsi0_parents[] = अणु "pll-video0" पूर्ण;
अटल स्थिर u8 mipi_dsi0_table[] = अणु 8 पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_TABLE_GATE(mipi_dsi0_clk, "mipi-dsi0",
				       mipi_dsi0_parents, mipi_dsi0_table,
				       0x168,
				       0, 4,	/* M */
				       24, 4,	/* mux */
				       BIT(31),	/* gate */
				       CLK_SET_RATE_PARENT);

अटल स्थिर अक्षर * स्थिर mipi_dsi1_parents[] = अणु "osc24M", "pll-video0" पूर्ण;
अटल स्थिर u8 mipi_dsi1_table[] = अणु 0, 9 पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_TABLE_GATE(mipi_dsi1_clk, "mipi-dsi1",
				       mipi_dsi1_parents, mipi_dsi1_table,
				       0x16c,
				       0, 4,	/* M */
				       24, 4,	/* mux */
				       BIT(31),	/* gate */
				       CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_M_WITH_GATE(gpu_core_clk, "gpu-core", "pll-gpu", 0x1a0,
			     0, 3, BIT(31), CLK_SET_RATE_PARENT);

अटल स्थिर अक्षर * स्थिर gpu_memory_parents[] = अणु "pll-gpu", "pll-ddr" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(gpu_memory_clk, "gpu-memory",
				 gpu_memory_parents,
				 0x1a4,
				 0, 3,		/* M */
				 24, 1,		/* mux */
				 BIT(31),	/* gate */
				 CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_M_WITH_GATE(gpu_hyd_clk, "gpu-hyd", "pll-gpu", 0x1a8,
			     0, 3, BIT(31), CLK_SET_RATE_PARENT);

अटल काष्ठा ccu_common *sun8i_a83t_ccu_clks[] = अणु
	&pll_c0cpux_clk.common,
	&pll_c1cpux_clk.common,
	&pll_audio_clk.common,
	&pll_video0_clk.common,
	&pll_ve_clk.common,
	&pll_ddr_clk.common,
	&pll_periph_clk.common,
	&pll_gpu_clk.common,
	&pll_hsic_clk.common,
	&pll_de_clk.common,
	&pll_video1_clk.common,
	&c0cpux_clk.common,
	&c1cpux_clk.common,
	&axi0_clk.common,
	&axi1_clk.common,
	&ahb1_clk.common,
	&ahb2_clk.common,
	&apb1_clk.common,
	&apb2_clk.common,
	&bus_mipi_dsi_clk.common,
	&bus_ss_clk.common,
	&bus_dma_clk.common,
	&bus_mmc0_clk.common,
	&bus_mmc1_clk.common,
	&bus_mmc2_clk.common,
	&bus_nand_clk.common,
	&bus_dram_clk.common,
	&bus_emac_clk.common,
	&bus_hsसमयr_clk.common,
	&bus_spi0_clk.common,
	&bus_spi1_clk.common,
	&bus_otg_clk.common,
	&bus_ehci0_clk.common,
	&bus_ehci1_clk.common,
	&bus_ohci0_clk.common,
	&bus_ve_clk.common,
	&bus_tcon0_clk.common,
	&bus_tcon1_clk.common,
	&bus_csi_clk.common,
	&bus_hdmi_clk.common,
	&bus_de_clk.common,
	&bus_gpu_clk.common,
	&bus_msgbox_clk.common,
	&bus_spinlock_clk.common,
	&bus_spdअगर_clk.common,
	&bus_pio_clk.common,
	&bus_i2s0_clk.common,
	&bus_i2s1_clk.common,
	&bus_i2s2_clk.common,
	&bus_tdm_clk.common,
	&bus_i2c0_clk.common,
	&bus_i2c1_clk.common,
	&bus_i2c2_clk.common,
	&bus_uart0_clk.common,
	&bus_uart1_clk.common,
	&bus_uart2_clk.common,
	&bus_uart3_clk.common,
	&bus_uart4_clk.common,
	&cci400_clk.common,
	&nand_clk.common,
	&mmc0_clk.common,
	&mmc0_sample_clk.common,
	&mmc0_output_clk.common,
	&mmc1_clk.common,
	&mmc1_sample_clk.common,
	&mmc1_output_clk.common,
	&mmc2_clk.common,
	&mmc2_sample_clk.common,
	&mmc2_output_clk.common,
	&ss_clk.common,
	&spi0_clk.common,
	&spi1_clk.common,
	&i2s0_clk.common,
	&i2s1_clk.common,
	&i2s2_clk.common,
	&tdm_clk.common,
	&spdअगर_clk.common,
	&usb_phy0_clk.common,
	&usb_phy1_clk.common,
	&usb_hsic_clk.common,
	&usb_hsic_12m_clk.common,
	&usb_ohci0_clk.common,
	&dram_clk.common,
	&dram_ve_clk.common,
	&dram_csi_clk.common,
	&tcon0_clk.common,
	&tcon1_clk.common,
	&csi_misc_clk.common,
	&mipi_csi_clk.common,
	&csi_mclk_clk.common,
	&csi_sclk_clk.common,
	&ve_clk.common,
	&avs_clk.common,
	&hdmi_clk.common,
	&hdmi_slow_clk.common,
	&mbus_clk.common,
	&mipi_dsi0_clk.common,
	&mipi_dsi1_clk.common,
	&gpu_core_clk.common,
	&gpu_memory_clk.common,
	&gpu_hyd_clk.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sun8i_a83t_hw_clks = अणु
	.hws	= अणु
		[CLK_PLL_C0CPUX]	= &pll_c0cpux_clk.common.hw,
		[CLK_PLL_C1CPUX]	= &pll_c1cpux_clk.common.hw,
		[CLK_PLL_AUDIO]		= &pll_audio_clk.common.hw,
		[CLK_PLL_VIDEO0]	= &pll_video0_clk.common.hw,
		[CLK_PLL_VE]		= &pll_ve_clk.common.hw,
		[CLK_PLL_DDR]		= &pll_ddr_clk.common.hw,
		[CLK_PLL_PERIPH]	= &pll_periph_clk.common.hw,
		[CLK_PLL_GPU]		= &pll_gpu_clk.common.hw,
		[CLK_PLL_HSIC]		= &pll_hsic_clk.common.hw,
		[CLK_PLL_DE]		= &pll_de_clk.common.hw,
		[CLK_PLL_VIDEO1]	= &pll_video1_clk.common.hw,
		[CLK_C0CPUX]		= &c0cpux_clk.common.hw,
		[CLK_C1CPUX]		= &c1cpux_clk.common.hw,
		[CLK_AXI0]		= &axi0_clk.common.hw,
		[CLK_AXI1]		= &axi1_clk.common.hw,
		[CLK_AHB1]		= &ahb1_clk.common.hw,
		[CLK_AHB2]		= &ahb2_clk.common.hw,
		[CLK_APB1]		= &apb1_clk.common.hw,
		[CLK_APB2]		= &apb2_clk.common.hw,
		[CLK_BUS_MIPI_DSI]	= &bus_mipi_dsi_clk.common.hw,
		[CLK_BUS_SS]		= &bus_ss_clk.common.hw,
		[CLK_BUS_DMA]		= &bus_dma_clk.common.hw,
		[CLK_BUS_MMC0]		= &bus_mmc0_clk.common.hw,
		[CLK_BUS_MMC1]		= &bus_mmc1_clk.common.hw,
		[CLK_BUS_MMC2]		= &bus_mmc2_clk.common.hw,
		[CLK_BUS_न_अंकD]		= &bus_nand_clk.common.hw,
		[CLK_BUS_DRAM]		= &bus_dram_clk.common.hw,
		[CLK_BUS_EMAC]		= &bus_emac_clk.common.hw,
		[CLK_BUS_HSTIMER]	= &bus_hsसमयr_clk.common.hw,
		[CLK_BUS_SPI0]		= &bus_spi0_clk.common.hw,
		[CLK_BUS_SPI1]		= &bus_spi1_clk.common.hw,
		[CLK_BUS_OTG]		= &bus_otg_clk.common.hw,
		[CLK_BUS_EHCI0]		= &bus_ehci0_clk.common.hw,
		[CLK_BUS_EHCI1]		= &bus_ehci1_clk.common.hw,
		[CLK_BUS_OHCI0]		= &bus_ohci0_clk.common.hw,
		[CLK_BUS_VE]		= &bus_ve_clk.common.hw,
		[CLK_BUS_TCON0]		= &bus_tcon0_clk.common.hw,
		[CLK_BUS_TCON1]		= &bus_tcon1_clk.common.hw,
		[CLK_BUS_CSI]		= &bus_csi_clk.common.hw,
		[CLK_BUS_HDMI]		= &bus_hdmi_clk.common.hw,
		[CLK_BUS_DE]		= &bus_de_clk.common.hw,
		[CLK_BUS_GPU]		= &bus_gpu_clk.common.hw,
		[CLK_BUS_MSGBOX]	= &bus_msgbox_clk.common.hw,
		[CLK_BUS_SPINLOCK]	= &bus_spinlock_clk.common.hw,
		[CLK_BUS_SPDIF]		= &bus_spdअगर_clk.common.hw,
		[CLK_BUS_PIO]		= &bus_pio_clk.common.hw,
		[CLK_BUS_I2S0]		= &bus_i2s0_clk.common.hw,
		[CLK_BUS_I2S1]		= &bus_i2s1_clk.common.hw,
		[CLK_BUS_I2S2]		= &bus_i2s2_clk.common.hw,
		[CLK_BUS_TDM]		= &bus_tdm_clk.common.hw,
		[CLK_BUS_I2C0]		= &bus_i2c0_clk.common.hw,
		[CLK_BUS_I2C1]		= &bus_i2c1_clk.common.hw,
		[CLK_BUS_I2C2]		= &bus_i2c2_clk.common.hw,
		[CLK_BUS_UART0]		= &bus_uart0_clk.common.hw,
		[CLK_BUS_UART1]		= &bus_uart1_clk.common.hw,
		[CLK_BUS_UART2]		= &bus_uart2_clk.common.hw,
		[CLK_BUS_UART3]		= &bus_uart3_clk.common.hw,
		[CLK_BUS_UART4]		= &bus_uart4_clk.common.hw,
		[CLK_CCI400]		= &cci400_clk.common.hw,
		[CLK_न_अंकD]		= &nand_clk.common.hw,
		[CLK_MMC0]		= &mmc0_clk.common.hw,
		[CLK_MMC0_SAMPLE]	= &mmc0_sample_clk.common.hw,
		[CLK_MMC0_OUTPUT]	= &mmc0_output_clk.common.hw,
		[CLK_MMC1]		= &mmc1_clk.common.hw,
		[CLK_MMC1_SAMPLE]	= &mmc1_sample_clk.common.hw,
		[CLK_MMC1_OUTPUT]	= &mmc1_output_clk.common.hw,
		[CLK_MMC2]		= &mmc2_clk.common.hw,
		[CLK_MMC2_SAMPLE]	= &mmc2_sample_clk.common.hw,
		[CLK_MMC2_OUTPUT]	= &mmc2_output_clk.common.hw,
		[CLK_SS]		= &ss_clk.common.hw,
		[CLK_SPI0]		= &spi0_clk.common.hw,
		[CLK_SPI1]		= &spi1_clk.common.hw,
		[CLK_I2S0]		= &i2s0_clk.common.hw,
		[CLK_I2S1]		= &i2s1_clk.common.hw,
		[CLK_I2S2]		= &i2s2_clk.common.hw,
		[CLK_TDM]		= &tdm_clk.common.hw,
		[CLK_SPDIF]		= &spdअगर_clk.common.hw,
		[CLK_USB_PHY0]		= &usb_phy0_clk.common.hw,
		[CLK_USB_PHY1]		= &usb_phy1_clk.common.hw,
		[CLK_USB_HSIC]		= &usb_hsic_clk.common.hw,
		[CLK_USB_HSIC_12M]	= &usb_hsic_12m_clk.common.hw,
		[CLK_USB_OHCI0]		= &usb_ohci0_clk.common.hw,
		[CLK_DRAM]		= &dram_clk.common.hw,
		[CLK_DRAM_VE]		= &dram_ve_clk.common.hw,
		[CLK_DRAM_CSI]		= &dram_csi_clk.common.hw,
		[CLK_TCON0]		= &tcon0_clk.common.hw,
		[CLK_TCON1]		= &tcon1_clk.common.hw,
		[CLK_CSI_MISC]		= &csi_misc_clk.common.hw,
		[CLK_MIPI_CSI]		= &mipi_csi_clk.common.hw,
		[CLK_CSI_MCLK]		= &csi_mclk_clk.common.hw,
		[CLK_CSI_SCLK]		= &csi_sclk_clk.common.hw,
		[CLK_VE]		= &ve_clk.common.hw,
		[CLK_AVS]		= &avs_clk.common.hw,
		[CLK_HDMI]		= &hdmi_clk.common.hw,
		[CLK_HDMI_SLOW]		= &hdmi_slow_clk.common.hw,
		[CLK_MBUS]		= &mbus_clk.common.hw,
		[CLK_MIPI_DSI0]		= &mipi_dsi0_clk.common.hw,
		[CLK_MIPI_DSI1]		= &mipi_dsi1_clk.common.hw,
		[CLK_GPU_CORE]		= &gpu_core_clk.common.hw,
		[CLK_GPU_MEMORY]	= &gpu_memory_clk.common.hw,
		[CLK_GPU_HYD]		= &gpu_hyd_clk.common.hw,
	पूर्ण,
	.num	= CLK_NUMBER,
पूर्ण;

अटल काष्ठा ccu_reset_map sun8i_a83t_ccu_resets[] = अणु
	[RST_USB_PHY0]		= अणु 0x0cc, BIT(0) पूर्ण,
	[RST_USB_PHY1]		= अणु 0x0cc, BIT(1) पूर्ण,
	[RST_USB_HSIC]		= अणु 0x0cc, BIT(2) पूर्ण,
	[RST_DRAM]		= अणु 0x0f4, BIT(31) पूर्ण,
	[RST_MBUS]		= अणु 0x0fc, BIT(31) पूर्ण,
	[RST_BUS_MIPI_DSI]	= अणु 0x2c0, BIT(1) पूर्ण,
	[RST_BUS_SS]		= अणु 0x2c0, BIT(5) पूर्ण,
	[RST_BUS_DMA]		= अणु 0x2c0, BIT(6) पूर्ण,
	[RST_BUS_MMC0]		= अणु 0x2c0, BIT(8) पूर्ण,
	[RST_BUS_MMC1]		= अणु 0x2c0, BIT(9) पूर्ण,
	[RST_BUS_MMC2]		= अणु 0x2c0, BIT(10) पूर्ण,
	[RST_BUS_न_अंकD]		= अणु 0x2c0, BIT(13) पूर्ण,
	[RST_BUS_DRAM]		= अणु 0x2c0, BIT(14) पूर्ण,
	[RST_BUS_EMAC]		= अणु 0x2c0, BIT(17) पूर्ण,
	[RST_BUS_HSTIMER]	= अणु 0x2c0, BIT(19) पूर्ण,
	[RST_BUS_SPI0]		= अणु 0x2c0, BIT(20) पूर्ण,
	[RST_BUS_SPI1]		= अणु 0x2c0, BIT(21) पूर्ण,
	[RST_BUS_OTG]		= अणु 0x2c0, BIT(24) पूर्ण,
	[RST_BUS_EHCI0]		= अणु 0x2c0, BIT(26) पूर्ण,
	[RST_BUS_EHCI1]		= अणु 0x2c0, BIT(27) पूर्ण,
	[RST_BUS_OHCI0]		= अणु 0x2c0, BIT(29) पूर्ण,
	[RST_BUS_VE]		= अणु 0x2c4, BIT(0) पूर्ण,
	[RST_BUS_TCON0]		= अणु 0x2c4, BIT(4) पूर्ण,
	[RST_BUS_TCON1]		= अणु 0x2c4, BIT(5) पूर्ण,
	[RST_BUS_CSI]		= अणु 0x2c4, BIT(8) पूर्ण,
	[RST_BUS_HDMI0]		= अणु 0x2c4, BIT(10) पूर्ण,
	[RST_BUS_HDMI1]		= अणु 0x2c4, BIT(11) पूर्ण,
	[RST_BUS_DE]		= अणु 0x2c4, BIT(12) पूर्ण,
	[RST_BUS_GPU]		= अणु 0x2c4, BIT(20) पूर्ण,
	[RST_BUS_MSGBOX]	= अणु 0x2c4, BIT(21) पूर्ण,
	[RST_BUS_SPINLOCK]	= अणु 0x2c4, BIT(22) पूर्ण,
	[RST_BUS_LVDS]		= अणु 0x2c8, BIT(0) पूर्ण,
	[RST_BUS_SPDIF]		= अणु 0x2d0, BIT(1) पूर्ण,
	[RST_BUS_I2S0]		= अणु 0x2d0, BIT(12) पूर्ण,
	[RST_BUS_I2S1]		= अणु 0x2d0, BIT(13) पूर्ण,
	[RST_BUS_I2S2]		= अणु 0x2d0, BIT(14) पूर्ण,
	[RST_BUS_TDM]		= अणु 0x2d0, BIT(15) पूर्ण,
	[RST_BUS_I2C0]		= अणु 0x2d8, BIT(0) पूर्ण,
	[RST_BUS_I2C1]		= अणु 0x2d8, BIT(1) पूर्ण,
	[RST_BUS_I2C2]		= अणु 0x2d8, BIT(2) पूर्ण,
	[RST_BUS_UART0]		= अणु 0x2d8, BIT(16) पूर्ण,
	[RST_BUS_UART1]		= अणु 0x2d8, BIT(17) पूर्ण,
	[RST_BUS_UART2]		= अणु 0x2d8, BIT(18) पूर्ण,
	[RST_BUS_UART3]		= अणु 0x2d8, BIT(19) पूर्ण,
	[RST_BUS_UART4]		= अणु 0x2d8, BIT(20) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun8i_a83t_ccu_desc = अणु
	.ccu_clks	= sun8i_a83t_ccu_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun8i_a83t_ccu_clks),

	.hw_clks	= &sun8i_a83t_hw_clks,

	.resets		= sun8i_a83t_ccu_resets,
	.num_resets	= ARRAY_SIZE(sun8i_a83t_ccu_resets),
पूर्ण;

#घोषणा SUN8I_A83T_PLL_P_SHIFT	16
#घोषणा SUN8I_A83T_PLL_N_SHIFT	8
#घोषणा SUN8I_A83T_PLL_N_WIDTH	8

अटल व्योम sun8i_a83t_cpu_pll_fixup(व्योम __iomem *reg)
अणु
	u32 val = पढ़ोl(reg);

	/* bail out अगर P भागider is not used */
	अगर (!(val & BIT(SUN8I_A83T_PLL_P_SHIFT)))
		वापस;

	/*
	 * If P is used, output should be less than 288 MHz. When we
	 * set P to 1, we should also decrease the multiplier so the
	 * output करोesn't go out of range, but not too much such that
	 * the multiplier stays above 12, the minimal operation value.
	 *
	 * To keep it simple, set the multiplier to 17, the reset value.
	 */
	val &= ~GENMASK(SUN8I_A83T_PLL_N_SHIFT + SUN8I_A83T_PLL_N_WIDTH - 1,
			SUN8I_A83T_PLL_N_SHIFT);
	val |= 17 << SUN8I_A83T_PLL_N_SHIFT;

	/* And clear P */
	val &= ~BIT(SUN8I_A83T_PLL_P_SHIFT);

	ग_लिखोl(val, reg);
पूर्ण

अटल पूर्णांक sun8i_a83t_ccu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	व्योम __iomem *reg;
	u32 val;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	reg = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	/* Enक्रमce d1 = 0, d2 = 1 क्रम Audio PLL */
	val = पढ़ोl(reg + SUN8I_A83T_PLL_AUDIO_REG);
	val &= ~BIT(16);
	val |= BIT(18);
	ग_लिखोl(val, reg + SUN8I_A83T_PLL_AUDIO_REG);

	/* Enक्रमce P = 1 क्रम both CPU cluster PLLs */
	sun8i_a83t_cpu_pll_fixup(reg + SUN8I_A83T_PLL_C0CPUX_REG);
	sun8i_a83t_cpu_pll_fixup(reg + SUN8I_A83T_PLL_C1CPUX_REG);

	वापस sunxi_ccu_probe(pdev->dev.of_node, reg, &sun8i_a83t_ccu_desc);
पूर्ण

अटल स्थिर काष्ठा of_device_id sun8i_a83t_ccu_ids[] = अणु
	अणु .compatible = "allwinner,sun8i-a83t-ccu" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sun8i_a83t_ccu_driver = अणु
	.probe	= sun8i_a83t_ccu_probe,
	.driver	= अणु
		.name	= "sun8i-a83t-ccu",
		.of_match_table	= sun8i_a83t_ccu_ids,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(sun8i_a83t_ccu_driver);
