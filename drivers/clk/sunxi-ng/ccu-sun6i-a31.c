<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 Chen-Yu Tsai
 *
 * Chen-Yu Tsai <wens@csie.org>
 *
 * Based on ccu-sun8i-h3.c by Maxime Ripard.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>

#समावेश "ccu_common.h"
#समावेश "ccu_reset.h"

#समावेश "ccu_div.h"
#समावेश "ccu_gate.h"
#समावेश "ccu_mp.h"
#समावेश "ccu_mult.h"
#समावेश "ccu_mux.h"
#समावेश "ccu_nk.h"
#समावेश "ccu_nkm.h"
#समावेश "ccu_nkmp.h"
#समावेश "ccu_nm.h"
#समावेश "ccu_phase.h"
#समावेश "ccu_sdm.h"

#समावेश "ccu-sun6i-a31.h"

अटल SUNXI_CCU_NKM_WITH_GATE_LOCK(pll_cpu_clk, "pll-cpu",
				     "osc24M", 0x000,
				     8, 5,	/* N */
				     4, 2,	/* K */
				     0, 2,	/* M */
				     BIT(31),	/* gate */
				     BIT(28),	/* lock */
				     0);

/*
 * The Audio PLL is supposed to have 4 outमाला_दो: 3 fixed factors from
 * the base (2x, 4x and 8x), and one variable भागider (the one true
 * pll audio).
 *
 * With sigma-delta modulation क्रम fractional-N on the audio PLL,
 * we have to use specअगरic भागiders. This means the variable भागider
 * can no दीर्घer be used, as the audio codec requests the exact घड़ी
 * rates we support through this mechanism. So we now hard code the
 * variable भागider to 1. This means the घड़ी rates will no दीर्घer
 * match the घड़ी names.
 */
#घोषणा SUN6I_A31_PLL_AUDIO_REG	0x008

अटल काष्ठा ccu_sdm_setting pll_audio_sdm_table[] = अणु
	अणु .rate = 22579200, .pattern = 0xc0010d84, .m = 8, .n = 7 पूर्ण,
	अणु .rate = 24576000, .pattern = 0xc000ac02, .m = 14, .n = 14 पूर्ण,
पूर्ण;

अटल SUNXI_CCU_NM_WITH_SDM_GATE_LOCK(pll_audio_base_clk, "pll-audio-base",
				       "osc24M", 0x008,
				       8, 7,	/* N */
				       0, 5,	/* M */
				       pll_audio_sdm_table, BIT(24),
				       0x284, BIT(31),
				       BIT(31),	/* gate */
				       BIT(28),	/* lock */
				       CLK_SET_RATE_UNGATE);

अटल SUNXI_CCU_NM_WITH_FRAC_GATE_LOCK(pll_video0_clk, "pll-video0",
					"osc24M", 0x010,
					8, 7,		/* N */
					0, 4,		/* M */
					BIT(24),	/* frac enable */
					BIT(25),	/* frac select */
					270000000,	/* frac rate 0 */
					297000000,	/* frac rate 1 */
					BIT(31),	/* gate */
					BIT(28),	/* lock */
					CLK_SET_RATE_UNGATE);

अटल SUNXI_CCU_NM_WITH_FRAC_GATE_LOCK(pll_ve_clk, "pll-ve",
					"osc24M", 0x018,
					8, 7,		/* N */
					0, 4,		/* M */
					BIT(24),	/* frac enable */
					BIT(25),	/* frac select */
					270000000,	/* frac rate 0 */
					297000000,	/* frac rate 1 */
					BIT(31),	/* gate */
					BIT(28),	/* lock */
					CLK_SET_RATE_UNGATE);

अटल SUNXI_CCU_NKM_WITH_GATE_LOCK(pll_ddr_clk, "pll-ddr",
				    "osc24M", 0x020,
				    8, 5,	/* N */
				    4, 2,	/* K */
				    0, 2,	/* M */
				    BIT(31),	/* gate */
				    BIT(28),	/* lock */
				    CLK_SET_RATE_UNGATE);

अटल SUNXI_CCU_NK_WITH_GATE_LOCK_POSTDIV(pll_periph_clk, "pll-periph",
					   "osc24M", 0x028,
					   8, 5,	/* N */
					   4, 2,	/* K */
					   BIT(31),	/* gate */
					   BIT(28),	/* lock */
					   2,		/* post-भाग */
					   CLK_SET_RATE_UNGATE);

अटल SUNXI_CCU_NM_WITH_FRAC_GATE_LOCK(pll_video1_clk, "pll-video1",
					"osc24M", 0x030,
					8, 7,		/* N */
					0, 4,		/* M */
					BIT(24),	/* frac enable */
					BIT(25),	/* frac select */
					270000000,	/* frac rate 0 */
					297000000,	/* frac rate 1 */
					BIT(31),	/* gate */
					BIT(28),	/* lock */
					CLK_SET_RATE_UNGATE);

अटल SUNXI_CCU_NM_WITH_FRAC_GATE_LOCK(pll_gpu_clk, "pll-gpu",
					"osc24M", 0x038,
					8, 7,		/* N */
					0, 4,		/* M */
					BIT(24),	/* frac enable */
					BIT(25),	/* frac select */
					270000000,	/* frac rate 0 */
					297000000,	/* frac rate 1 */
					BIT(31),	/* gate */
					BIT(28),	/* lock */
					CLK_SET_RATE_UNGATE);

/*
 * The MIPI PLL has 2 modes: "MIPI" and "HDMI".
 *
 * The MIPI mode is a standard NKM-style घड़ी. The HDMI mode is an
 * पूर्णांकeger / fractional घड़ी with चयनable multipliers and भागiders.
 * This is not supported here. We hardcode the PLL to MIPI mode.
 */
#घोषणा SUN6I_A31_PLL_MIPI_REG	0x040

अटल स्थिर अक्षर * स्थिर pll_mipi_parents[] = अणु "pll-video0", "pll-video1" पूर्ण;
अटल SUNXI_CCU_NKM_WITH_MUX_GATE_LOCK(pll_mipi_clk, "pll-mipi",
					pll_mipi_parents, 0x040,
					8, 4,	/* N */
					4, 2,	/* K */
					0, 4,	/* M */
					21, 0,	/* mux */
					BIT(31) | BIT(23) | BIT(22), /* gate */
					BIT(28),	/* lock */
					CLK_SET_RATE_UNGATE);

अटल SUNXI_CCU_NM_WITH_FRAC_GATE_LOCK(pll9_clk, "pll9",
					"osc24M", 0x044,
					8, 7,		/* N */
					0, 4,		/* M */
					BIT(24),	/* frac enable */
					BIT(25),	/* frac select */
					270000000,	/* frac rate 0 */
					297000000,	/* frac rate 1 */
					BIT(31),	/* gate */
					BIT(28),	/* lock */
					CLK_SET_RATE_UNGATE);

अटल SUNXI_CCU_NM_WITH_FRAC_GATE_LOCK(pll10_clk, "pll10",
					"osc24M", 0x048,
					8, 7,		/* N */
					0, 4,		/* M */
					BIT(24),	/* frac enable */
					BIT(25),	/* frac select */
					270000000,	/* frac rate 0 */
					297000000,	/* frac rate 1 */
					BIT(31),	/* gate */
					BIT(28),	/* lock */
					CLK_SET_RATE_UNGATE);

अटल स्थिर अक्षर * स्थिर cpux_parents[] = अणु "osc32k", "osc24M",
					     "pll-cpu", "pll-cpu" पूर्ण;
अटल SUNXI_CCU_MUX(cpu_clk, "cpu", cpux_parents,
		     0x050, 16, 2, CLK_SET_RATE_PARENT | CLK_IS_CRITICAL);

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

अटल SUNXI_CCU_DIV_TABLE(axi_clk, "axi", "cpu",
			   0x050, 0, 3, axi_भाग_प्रकारable, 0);

#घोषणा SUN6I_A31_AHB1_REG  0x054

अटल स्थिर अक्षर * स्थिर ahb1_parents[] = अणु "osc32k", "osc24M",
					     "axi", "pll-periph" पूर्ण;
अटल स्थिर काष्ठा ccu_mux_var_preभाग ahb1_preभागs[] = अणु
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
		.features	= CCU_FEATURE_VARIABLE_PREDIV,
		.hw.init	= CLK_HW_INIT_PARENTS("ahb1",
						      ahb1_parents,
						      &ccu_भाग_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable apb1_भाग_प्रकारable[] = अणु
	अणु .val = 0, .भाग = 2 पूर्ण,
	अणु .val = 1, .भाग = 2 पूर्ण,
	अणु .val = 2, .भाग = 4 पूर्ण,
	अणु .val = 3, .भाग = 8 पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;

अटल SUNXI_CCU_DIV_TABLE(apb1_clk, "apb1", "ahb1",
			   0x054, 8, 2, apb1_भाग_प्रकारable, 0);

अटल स्थिर अक्षर * स्थिर apb2_parents[] = अणु "osc32k", "osc24M",
					     "pll-periph", "pll-periph" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX(apb2_clk, "apb2", apb2_parents, 0x058,
			     0, 5,	/* M */
			     16, 2,	/* P */
			     24, 2,	/* mux */
			     0);

अटल SUNXI_CCU_GATE(ahb1_mipidsi_clk,	"ahb1-mipidsi",	"ahb1",
		      0x060, BIT(1), 0);
अटल SUNXI_CCU_GATE(ahb1_ss_clk,	"ahb1-ss",	"ahb1",
		      0x060, BIT(5), 0);
अटल SUNXI_CCU_GATE(ahb1_dma_clk,	"ahb1-dma",	"ahb1",
		      0x060, BIT(6), 0);
अटल SUNXI_CCU_GATE(ahb1_mmc0_clk,	"ahb1-mmc0",	"ahb1",
		      0x060, BIT(8), 0);
अटल SUNXI_CCU_GATE(ahb1_mmc1_clk,	"ahb1-mmc1",	"ahb1",
		      0x060, BIT(9), 0);
अटल SUNXI_CCU_GATE(ahb1_mmc2_clk,	"ahb1-mmc2",	"ahb1",
		      0x060, BIT(10), 0);
अटल SUNXI_CCU_GATE(ahb1_mmc3_clk,	"ahb1-mmc3",	"ahb1",
		      0x060, BIT(11), 0);
अटल SUNXI_CCU_GATE(ahb1_nand1_clk,	"ahb1-nand1",	"ahb1",
		      0x060, BIT(12), 0);
अटल SUNXI_CCU_GATE(ahb1_nand0_clk,	"ahb1-nand0",	"ahb1",
		      0x060, BIT(13), 0);
अटल SUNXI_CCU_GATE(ahb1_sdram_clk,	"ahb1-sdram",	"ahb1",
		      0x060, BIT(14), 0);
अटल SUNXI_CCU_GATE(ahb1_emac_clk,	"ahb1-emac",	"ahb1",
		      0x060, BIT(17), 0);
अटल SUNXI_CCU_GATE(ahb1_ts_clk,	"ahb1-ts",	"ahb1",
		      0x060, BIT(18), 0);
अटल SUNXI_CCU_GATE(ahb1_hsसमयr_clk,	"ahb1-hstimer",	"ahb1",
		      0x060, BIT(19), 0);
अटल SUNXI_CCU_GATE(ahb1_spi0_clk,	"ahb1-spi0",	"ahb1",
		      0x060, BIT(20), 0);
अटल SUNXI_CCU_GATE(ahb1_spi1_clk,	"ahb1-spi1",	"ahb1",
		      0x060, BIT(21), 0);
अटल SUNXI_CCU_GATE(ahb1_spi2_clk,	"ahb1-spi2",	"ahb1",
		      0x060, BIT(22), 0);
अटल SUNXI_CCU_GATE(ahb1_spi3_clk,	"ahb1-spi3",	"ahb1",
		      0x060, BIT(23), 0);
अटल SUNXI_CCU_GATE(ahb1_otg_clk,	"ahb1-otg",	"ahb1",
		      0x060, BIT(24), 0);
अटल SUNXI_CCU_GATE(ahb1_ehci0_clk,	"ahb1-ehci0",	"ahb1",
		      0x060, BIT(26), 0);
अटल SUNXI_CCU_GATE(ahb1_ehci1_clk,	"ahb1-ehci1",	"ahb1",
		      0x060, BIT(27), 0);
अटल SUNXI_CCU_GATE(ahb1_ohci0_clk,	"ahb1-ohci0",	"ahb1",
		      0x060, BIT(29), 0);
अटल SUNXI_CCU_GATE(ahb1_ohci1_clk,	"ahb1-ohci1",	"ahb1",
		      0x060, BIT(30), 0);
अटल SUNXI_CCU_GATE(ahb1_ohci2_clk,	"ahb1-ohci2",	"ahb1",
		      0x060, BIT(31), 0);

अटल SUNXI_CCU_GATE(ahb1_ve_clk,	"ahb1-ve",	"ahb1",
		      0x064, BIT(0), 0);
अटल SUNXI_CCU_GATE(ahb1_lcd0_clk,	"ahb1-lcd0",	"ahb1",
		      0x064, BIT(4), 0);
अटल SUNXI_CCU_GATE(ahb1_lcd1_clk,	"ahb1-lcd1",	"ahb1",
		      0x064, BIT(5), 0);
अटल SUNXI_CCU_GATE(ahb1_csi_clk,	"ahb1-csi",	"ahb1",
		      0x064, BIT(8), 0);
अटल SUNXI_CCU_GATE(ahb1_hdmi_clk,	"ahb1-hdmi",	"ahb1",
		      0x064, BIT(11), 0);
अटल SUNXI_CCU_GATE(ahb1_be0_clk,	"ahb1-be0",	"ahb1",
		      0x064, BIT(12), 0);
अटल SUNXI_CCU_GATE(ahb1_be1_clk,	"ahb1-be1",	"ahb1",
		      0x064, BIT(13), 0);
अटल SUNXI_CCU_GATE(ahb1_fe0_clk,	"ahb1-fe0",	"ahb1",
		      0x064, BIT(14), 0);
अटल SUNXI_CCU_GATE(ahb1_fe1_clk,	"ahb1-fe1",	"ahb1",
		      0x064, BIT(15), 0);
अटल SUNXI_CCU_GATE(ahb1_mp_clk,	"ahb1-mp",	"ahb1",
		      0x064, BIT(18), 0);
अटल SUNXI_CCU_GATE(ahb1_gpu_clk,	"ahb1-gpu",	"ahb1",
		      0x064, BIT(20), 0);
अटल SUNXI_CCU_GATE(ahb1_deu0_clk,	"ahb1-deu0",	"ahb1",
		      0x064, BIT(23), 0);
अटल SUNXI_CCU_GATE(ahb1_deu1_clk,	"ahb1-deu1",	"ahb1",
		      0x064, BIT(24), 0);
अटल SUNXI_CCU_GATE(ahb1_drc0_clk,	"ahb1-drc0",	"ahb1",
		      0x064, BIT(25), 0);
अटल SUNXI_CCU_GATE(ahb1_drc1_clk,	"ahb1-drc1",	"ahb1",
		      0x064, BIT(26), 0);

अटल SUNXI_CCU_GATE(apb1_codec_clk,	"apb1-codec",	"apb1",
		      0x068, BIT(0), 0);
अटल SUNXI_CCU_GATE(apb1_spdअगर_clk,	"apb1-spdif",	"apb1",
		      0x068, BIT(1), 0);
अटल SUNXI_CCU_GATE(apb1_digital_mic_clk,	"apb1-digital-mic",	"apb1",
		      0x068, BIT(4), 0);
अटल SUNXI_CCU_GATE(apb1_pio_clk,	"apb1-pio",	"apb1",
		      0x068, BIT(5), 0);
अटल SUNXI_CCU_GATE(apb1_daudio0_clk,	"apb1-daudio0",	"apb1",
		      0x068, BIT(12), 0);
अटल SUNXI_CCU_GATE(apb1_daudio1_clk,	"apb1-daudio1",	"apb1",
		      0x068, BIT(13), 0);

अटल SUNXI_CCU_GATE(apb2_i2c0_clk,	"apb2-i2c0",	"apb2",
		      0x06c, BIT(0), 0);
अटल SUNXI_CCU_GATE(apb2_i2c1_clk,	"apb2-i2c1",	"apb2",
		      0x06c, BIT(1), 0);
अटल SUNXI_CCU_GATE(apb2_i2c2_clk,	"apb2-i2c2",	"apb2",
		      0x06c, BIT(2), 0);
अटल SUNXI_CCU_GATE(apb2_i2c3_clk,	"apb2-i2c3",	"apb2",
		      0x06c, BIT(3), 0);
अटल SUNXI_CCU_GATE(apb2_uart0_clk,	"apb2-uart0",	"apb2",
		      0x06c, BIT(16), 0);
अटल SUNXI_CCU_GATE(apb2_uart1_clk,	"apb2-uart1",	"apb2",
		      0x06c, BIT(17), 0);
अटल SUNXI_CCU_GATE(apb2_uart2_clk,	"apb2-uart2",	"apb2",
		      0x06c, BIT(18), 0);
अटल SUNXI_CCU_GATE(apb2_uart3_clk,	"apb2-uart3",	"apb2",
		      0x06c, BIT(19), 0);
अटल SUNXI_CCU_GATE(apb2_uart4_clk,	"apb2-uart4",	"apb2",
		      0x06c, BIT(20), 0);
अटल SUNXI_CCU_GATE(apb2_uart5_clk,	"apb2-uart5",	"apb2",
		      0x06c, BIT(21), 0);

अटल स्थिर अक्षर * स्थिर mod0_शेष_parents[] = अणु "osc24M", "pll-periph" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX_GATE(nand0_clk, "nand0", mod0_शेष_parents,
				  0x080,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(nand1_clk, "nand1", mod0_शेष_parents,
				  0x084,
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

अटल SUNXI_CCU_PHASE(mmc0_sample_clk, "mmc0_sample", "mmc0",
		       0x088, 20, 3, 0);
अटल SUNXI_CCU_PHASE(mmc0_output_clk, "mmc0_output", "mmc0",
		       0x088, 8, 3, 0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(mmc1_clk, "mmc1", mod0_शेष_parents,
				  0x08c,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_PHASE(mmc1_sample_clk, "mmc1_sample", "mmc1",
		       0x08c, 20, 3, 0);
अटल SUNXI_CCU_PHASE(mmc1_output_clk, "mmc1_output", "mmc1",
		       0x08c, 8, 3, 0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(mmc2_clk, "mmc2", mod0_शेष_parents,
				  0x090,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_PHASE(mmc2_sample_clk, "mmc2_sample", "mmc2",
		       0x090, 20, 3, 0);
अटल SUNXI_CCU_PHASE(mmc2_output_clk, "mmc2_output", "mmc2",
		       0x090, 8, 3, 0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(mmc3_clk, "mmc3", mod0_शेष_parents,
				  0x094,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_PHASE(mmc3_sample_clk, "mmc3_sample", "mmc3",
		       0x094, 20, 3, 0);
अटल SUNXI_CCU_PHASE(mmc3_output_clk, "mmc3_output", "mmc3",
		       0x094, 8, 3, 0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(ts_clk, "ts", mod0_शेष_parents, 0x098,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(ss_clk, "ss", mod0_शेष_parents, 0x09c,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(spi0_clk, "spi0", mod0_शेष_parents, 0x0a0,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(spi1_clk, "spi1", mod0_शेष_parents, 0x0a4,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);
अटल SUNXI_CCU_MP_WITH_MUX_GATE(spi2_clk, "spi2", mod0_शेष_parents, 0x0a8,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(spi3_clk, "spi3", mod0_शेष_parents, 0x0ac,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल स्थिर अक्षर * स्थिर daudio_parents[] = अणु "pll-audio-8x", "pll-audio-4x",
					       "pll-audio-2x", "pll-audio" पूर्ण;
अटल SUNXI_CCU_MUX_WITH_GATE(daudio0_clk, "daudio0", daudio_parents,
			       0x0b0, 16, 2, BIT(31), CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_MUX_WITH_GATE(daudio1_clk, "daudio1", daudio_parents,
			       0x0b4, 16, 2, BIT(31), CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_MUX_WITH_GATE(spdअगर_clk, "spdif", daudio_parents,
			       0x0c0, 16, 2, BIT(31), CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_GATE(usb_phy0_clk,	"usb-phy0",	"osc24M",
		      0x0cc, BIT(8), 0);
अटल SUNXI_CCU_GATE(usb_phy1_clk,	"usb-phy1",	"osc24M",
		      0x0cc, BIT(9), 0);
अटल SUNXI_CCU_GATE(usb_phy2_clk,	"usb-phy2",	"osc24M",
		      0x0cc, BIT(10), 0);
अटल SUNXI_CCU_GATE(usb_ohci0_clk,	"usb-ohci0",	"osc24M",
		      0x0cc, BIT(16), 0);
अटल SUNXI_CCU_GATE(usb_ohci1_clk,	"usb-ohci1",	"osc24M",
		      0x0cc, BIT(17), 0);
अटल SUNXI_CCU_GATE(usb_ohci2_clk,	"usb-ohci2",	"osc24M",
		      0x0cc, BIT(18), 0);

/* TODO emac clk not supported yet */

अटल स्थिर अक्षर * स्थिर dram_parents[] = अणु "pll-ddr", "pll-periph" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX_GATE(mdfs_clk, "mdfs", dram_parents, 0x0f0,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  CLK_IS_CRITICAL);

अटल SUNXI_CCU_M_WITH_MUX(sdram0_clk, "sdram0", dram_parents,
			    0x0f4, 0, 4, 4, 1, CLK_IS_CRITICAL);
अटल SUNXI_CCU_M_WITH_MUX(sdram1_clk, "sdram1", dram_parents,
			    0x0f4, 8, 4, 12, 1, CLK_IS_CRITICAL);

अटल SUNXI_CCU_GATE(dram_ve_clk,	"dram-ve",	"mdfs",
		      0x100, BIT(0), 0);
अटल SUNXI_CCU_GATE(dram_csi_isp_clk,	"dram-csi-isp",	"mdfs",
		      0x100, BIT(1), 0);
अटल SUNXI_CCU_GATE(dram_ts_clk,	"dram-ts",	"mdfs",
		      0x100, BIT(3), 0);
अटल SUNXI_CCU_GATE(dram_drc0_clk,	"dram-drc0",	"mdfs",
		      0x100, BIT(16), 0);
अटल SUNXI_CCU_GATE(dram_drc1_clk,	"dram-drc1",	"mdfs",
		      0x100, BIT(17), 0);
अटल SUNXI_CCU_GATE(dram_deu0_clk,	"dram-deu0",	"mdfs",
		      0x100, BIT(18), 0);
अटल SUNXI_CCU_GATE(dram_deu1_clk,	"dram-deu1",	"mdfs",
		      0x100, BIT(19), 0);
अटल SUNXI_CCU_GATE(dram_fe0_clk,	"dram-fe0",	"mdfs",
		      0x100, BIT(24), 0);
अटल SUNXI_CCU_GATE(dram_fe1_clk,	"dram-fe1",	"mdfs",
		      0x100, BIT(25), 0);
अटल SUNXI_CCU_GATE(dram_be0_clk,	"dram-be0",	"mdfs",
		      0x100, BIT(26), 0);
अटल SUNXI_CCU_GATE(dram_be1_clk,	"dram-be1",	"mdfs",
		      0x100, BIT(27), 0);
अटल SUNXI_CCU_GATE(dram_mp_clk,	"dram-mp",	"mdfs",
		      0x100, BIT(28), 0);

अटल स्थिर अक्षर * स्थिर de_parents[] = अणु "pll-video0", "pll-video1",
					   "pll-periph-2x", "pll-gpu",
					   "pll9", "pll10" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(be0_clk, "be0", de_parents,
				 0x104, 0, 4, 24, 3, BIT(31), 0);
अटल SUNXI_CCU_M_WITH_MUX_GATE(be1_clk, "be1", de_parents,
				 0x108, 0, 4, 24, 3, BIT(31), 0);
अटल SUNXI_CCU_M_WITH_MUX_GATE(fe0_clk, "fe0", de_parents,
				 0x10c, 0, 4, 24, 3, BIT(31), 0);
अटल SUNXI_CCU_M_WITH_MUX_GATE(fe1_clk, "fe1", de_parents,
				 0x110, 0, 4, 24, 3, BIT(31), 0);

अटल स्थिर अक्षर * स्थिर mp_parents[] = अणु "pll-video0", "pll-video1",
					   "pll9", "pll10" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(mp_clk, "mp", mp_parents,
				 0x114, 0, 4, 24, 3, BIT(31), 0);

अटल स्थिर अक्षर * स्थिर lcd_ch0_parents[] = अणु "pll-video0", "pll-video1",
						"pll-video0-2x",
						"pll-video1-2x", "pll-mipi" पूर्ण;
अटल SUNXI_CCU_MUX_WITH_GATE(lcd0_ch0_clk, "lcd0-ch0", lcd_ch0_parents,
			       0x118, 24, 2, BIT(31), CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_MUX_WITH_GATE(lcd1_ch0_clk, "lcd1-ch0", lcd_ch0_parents,
			       0x11c, 24, 2, BIT(31), CLK_SET_RATE_PARENT);

अटल स्थिर अक्षर * स्थिर lcd_ch1_parents[] = अणु "pll-video0", "pll-video1",
						"pll-video0-2x",
						"pll-video1-2x" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(lcd0_ch1_clk, "lcd0-ch1", lcd_ch1_parents,
				 0x12c, 0, 4, 24, 3, BIT(31),
				 CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_M_WITH_MUX_GATE(lcd1_ch1_clk, "lcd1-ch1", lcd_ch1_parents,
				 0x130, 0, 4, 24, 3, BIT(31),
				 CLK_SET_RATE_PARENT);

अटल स्थिर अक्षर * स्थिर csi_sclk_parents[] = अणु "pll-video0", "pll-video1",
						 "pll9", "pll10", "pll-mipi",
						 "pll-ve" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(csi0_sclk_clk, "csi0-sclk", csi_sclk_parents,
				 0x134, 16, 4, 24, 3, BIT(31), 0);

अटल स्थिर अक्षर * स्थिर csi_mclk_parents[] = अणु "pll-video0", "pll-video1",
						 "osc24M" पूर्ण;
अटल स्थिर u8 csi_mclk_table[] = अणु 0, 1, 5 पूर्ण;
अटल काष्ठा ccu_भाग csi0_mclk_clk = अणु
	.enable		= BIT(15),
	.भाग		= _SUNXI_CCU_DIV(0, 4),
	.mux		= _SUNXI_CCU_MUX_TABLE(8, 3, csi_mclk_table),
	.common		= अणु
		.reg		= 0x134,
		.hw.init	= CLK_HW_INIT_PARENTS("csi0-mclk",
						      csi_mclk_parents,
						      &ccu_भाग_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_भाग csi1_mclk_clk = अणु
	.enable		= BIT(15),
	.भाग		= _SUNXI_CCU_DIV(0, 4),
	.mux		= _SUNXI_CCU_MUX_TABLE(8, 3, csi_mclk_table),
	.common		= अणु
		.reg		= 0x138,
		.hw.init	= CLK_HW_INIT_PARENTS("csi1-mclk",
						      csi_mclk_parents,
						      &ccu_भाग_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल SUNXI_CCU_M_WITH_GATE(ve_clk, "ve", "pll-ve",
			     0x13c, 16, 3, BIT(31), 0);

अटल SUNXI_CCU_GATE(codec_clk,	"codec",	"pll-audio",
		      0x140, BIT(31), CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_GATE(avs_clk,		"avs",		"osc24M",
		      0x144, BIT(31), 0);
अटल SUNXI_CCU_GATE(digital_mic_clk,	"digital-mic",	"pll-audio",
		      0x148, BIT(31), CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_M_WITH_MUX_GATE(hdmi_clk, "hdmi", lcd_ch1_parents,
				 0x150, 0, 4, 24, 2, BIT(31),
				 CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_GATE(hdmi_ddc_clk, "ddc", "osc24M", 0x150, BIT(30), 0);

अटल SUNXI_CCU_GATE(ps_clk, "ps", "lcd1-ch1", 0x140, BIT(31), 0);

अटल स्थिर अक्षर * स्थिर mbus_parents[] = अणु "osc24M", "pll-periph",
					     "pll-ddr" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX_GATE(mbus0_clk, "mbus0", mbus_parents, 0x15c,
				  0, 3,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  CLK_IS_CRITICAL);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(mbus1_clk, "mbus1", mbus_parents, 0x160,
				  0, 3,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  CLK_IS_CRITICAL);

अटल SUNXI_CCU_M_WITH_MUX_GATE(mipi_dsi_clk, "mipi-dsi", lcd_ch1_parents,
				 0x168, 16, 3, 24, 2, BIT(31),
				 CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_M_WITH_MUX_GATE(mipi_dsi_dphy_clk, "mipi-dsi-dphy",
				 lcd_ch1_parents, 0x168, 0, 3, 8, 2,
				 BIT(15), CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_M_WITH_MUX_GATE(mipi_csi_dphy_clk, "mipi-csi-dphy",
				 lcd_ch1_parents, 0x16c, 0, 3, 8, 2,
				 BIT(15), 0);

अटल SUNXI_CCU_M_WITH_MUX_GATE(iep_drc0_clk, "iep-drc0", de_parents,
				 0x180, 0, 3, 24, 2, BIT(31), 0);
अटल SUNXI_CCU_M_WITH_MUX_GATE(iep_drc1_clk, "iep-drc1", de_parents,
				 0x184, 0, 3, 24, 2, BIT(31), 0);
अटल SUNXI_CCU_M_WITH_MUX_GATE(iep_deu0_clk, "iep-deu0", de_parents,
				 0x188, 0, 3, 24, 2, BIT(31), 0);
अटल SUNXI_CCU_M_WITH_MUX_GATE(iep_deu1_clk, "iep-deu1", de_parents,
				 0x18c, 0, 3, 24, 2, BIT(31), 0);

अटल स्थिर अक्षर * स्थिर gpu_parents[] = अणु "pll-gpu", "pll-periph-2x",
					    "pll-video0", "pll-video1",
					    "pll9", "pll10" पूर्ण;
अटल स्थिर काष्ठा ccu_mux_fixed_preभाग gpu_preभागs[] = अणु
	अणु .index = 1, .भाग = 3, पूर्ण,
पूर्ण;

अटल काष्ठा ccu_भाग gpu_core_clk = अणु
	.enable		= BIT(31),
	.भाग		= _SUNXI_CCU_DIV(0, 3),
	.mux		= अणु
		.shअगरt		= 24,
		.width		= 3,
		.fixed_preभागs	= gpu_preभागs,
		.n_preभागs	= ARRAY_SIZE(gpu_preभागs),
	पूर्ण,
	.common		= अणु
		.reg		= 0x1a0,
		.features	= CCU_FEATURE_FIXED_PREDIV,
		.hw.init	= CLK_HW_INIT_PARENTS("gpu-core",
						      gpu_parents,
						      &ccu_भाग_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_भाग gpu_memory_clk = अणु
	.enable		= BIT(31),
	.भाग		= _SUNXI_CCU_DIV(0, 3),
	.mux		= अणु
		.shअगरt		= 24,
		.width		= 3,
		.fixed_preभागs	= gpu_preभागs,
		.n_preभागs	= ARRAY_SIZE(gpu_preभागs),
	पूर्ण,
	.common		= अणु
		.reg		= 0x1a4,
		.features	= CCU_FEATURE_FIXED_PREDIV,
		.hw.init	= CLK_HW_INIT_PARENTS("gpu-memory",
						      gpu_parents,
						      &ccu_भाग_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_भाग gpu_hyd_clk = अणु
	.enable		= BIT(31),
	.भाग		= _SUNXI_CCU_DIV(0, 3),
	.mux		= अणु
		.shअगरt		= 24,
		.width		= 3,
		.fixed_preभागs	= gpu_preभागs,
		.n_preभागs	= ARRAY_SIZE(gpu_preभागs),
	पूर्ण,
	.common		= अणु
		.reg		= 0x1a8,
		.features	= CCU_FEATURE_FIXED_PREDIV,
		.hw.init	= CLK_HW_INIT_PARENTS("gpu-hyd",
						      gpu_parents,
						      &ccu_भाग_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल SUNXI_CCU_M_WITH_MUX_GATE(ats_clk, "ats", mod0_शेष_parents, 0x1b0,
				 0, 3,		/* M */
				 24, 2,		/* mux */
				 BIT(31),	/* gate */
				 0);

अटल SUNXI_CCU_M_WITH_MUX_GATE(trace_clk, "trace", mod0_शेष_parents,
				 0x1b0,
				 0, 3,		/* M */
				 24, 2,		/* mux */
				 BIT(31),	/* gate */
				 0);

अटल स्थिर अक्षर * स्थिर clk_out_parents[] = अणु "osc24M", "osc32k", "osc24M",
						"axi", "ahb1" पूर्ण;
अटल स्थिर u8 clk_out_table[] = अणु 0, 1, 2, 11, 13 पूर्ण;

अटल स्थिर काष्ठा ccu_mux_fixed_preभाग clk_out_preभागs[] = अणु
	अणु .index = 0, .भाग = 750, पूर्ण,
	अणु .index = 3, .भाग = 4, पूर्ण,
	अणु .index = 4, .भाग = 4, पूर्ण,
पूर्ण;

अटल काष्ठा ccu_mp out_a_clk = अणु
	.enable		= BIT(31),
	.m		= _SUNXI_CCU_DIV(8, 5),
	.p		= _SUNXI_CCU_DIV(20, 2),
	.mux		= अणु
		.shअगरt		= 24,
		.width		= 4,
		.table		= clk_out_table,
		.fixed_preभागs	= clk_out_preभागs,
		.n_preभागs	= ARRAY_SIZE(clk_out_preभागs),
	पूर्ण,
	.common		= अणु
		.reg		= 0x300,
		.features	= CCU_FEATURE_FIXED_PREDIV,
		.hw.init	= CLK_HW_INIT_PARENTS("out-a",
						      clk_out_parents,
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
		.table		= clk_out_table,
		.fixed_preभागs	= clk_out_preभागs,
		.n_preभागs	= ARRAY_SIZE(clk_out_preभागs),
	पूर्ण,
	.common		= अणु
		.reg		= 0x304,
		.features	= CCU_FEATURE_FIXED_PREDIV,
		.hw.init	= CLK_HW_INIT_PARENTS("out-b",
						      clk_out_parents,
						      &ccu_mp_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_mp out_c_clk = अणु
	.enable		= BIT(31),
	.m		= _SUNXI_CCU_DIV(8, 5),
	.p		= _SUNXI_CCU_DIV(20, 2),
	.mux		= अणु
		.shअगरt		= 24,
		.width		= 4,
		.table		= clk_out_table,
		.fixed_preभागs	= clk_out_preभागs,
		.n_preभागs	= ARRAY_SIZE(clk_out_preभागs),
	पूर्ण,
	.common		= अणु
		.reg		= 0x308,
		.features	= CCU_FEATURE_FIXED_PREDIV,
		.hw.init	= CLK_HW_INIT_PARENTS("out-c",
						      clk_out_parents,
						      &ccu_mp_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल काष्ठा ccu_common *sun6i_a31_ccu_clks[] = अणु
	&pll_cpu_clk.common,
	&pll_audio_base_clk.common,
	&pll_video0_clk.common,
	&pll_ve_clk.common,
	&pll_ddr_clk.common,
	&pll_periph_clk.common,
	&pll_video1_clk.common,
	&pll_gpu_clk.common,
	&pll_mipi_clk.common,
	&pll9_clk.common,
	&pll10_clk.common,
	&cpu_clk.common,
	&axi_clk.common,
	&ahb1_clk.common,
	&apb1_clk.common,
	&apb2_clk.common,
	&ahb1_mipidsi_clk.common,
	&ahb1_ss_clk.common,
	&ahb1_dma_clk.common,
	&ahb1_mmc0_clk.common,
	&ahb1_mmc1_clk.common,
	&ahb1_mmc2_clk.common,
	&ahb1_mmc3_clk.common,
	&ahb1_nand1_clk.common,
	&ahb1_nand0_clk.common,
	&ahb1_sdram_clk.common,
	&ahb1_emac_clk.common,
	&ahb1_ts_clk.common,
	&ahb1_hsसमयr_clk.common,
	&ahb1_spi0_clk.common,
	&ahb1_spi1_clk.common,
	&ahb1_spi2_clk.common,
	&ahb1_spi3_clk.common,
	&ahb1_otg_clk.common,
	&ahb1_ehci0_clk.common,
	&ahb1_ehci1_clk.common,
	&ahb1_ohci0_clk.common,
	&ahb1_ohci1_clk.common,
	&ahb1_ohci2_clk.common,
	&ahb1_ve_clk.common,
	&ahb1_lcd0_clk.common,
	&ahb1_lcd1_clk.common,
	&ahb1_csi_clk.common,
	&ahb1_hdmi_clk.common,
	&ahb1_be0_clk.common,
	&ahb1_be1_clk.common,
	&ahb1_fe0_clk.common,
	&ahb1_fe1_clk.common,
	&ahb1_mp_clk.common,
	&ahb1_gpu_clk.common,
	&ahb1_deu0_clk.common,
	&ahb1_deu1_clk.common,
	&ahb1_drc0_clk.common,
	&ahb1_drc1_clk.common,
	&apb1_codec_clk.common,
	&apb1_spdअगर_clk.common,
	&apb1_digital_mic_clk.common,
	&apb1_pio_clk.common,
	&apb1_daudio0_clk.common,
	&apb1_daudio1_clk.common,
	&apb2_i2c0_clk.common,
	&apb2_i2c1_clk.common,
	&apb2_i2c2_clk.common,
	&apb2_i2c3_clk.common,
	&apb2_uart0_clk.common,
	&apb2_uart1_clk.common,
	&apb2_uart2_clk.common,
	&apb2_uart3_clk.common,
	&apb2_uart4_clk.common,
	&apb2_uart5_clk.common,
	&nand0_clk.common,
	&nand1_clk.common,
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
	&daudio0_clk.common,
	&daudio1_clk.common,
	&spdअगर_clk.common,
	&usb_phy0_clk.common,
	&usb_phy1_clk.common,
	&usb_phy2_clk.common,
	&usb_ohci0_clk.common,
	&usb_ohci1_clk.common,
	&usb_ohci2_clk.common,
	&mdfs_clk.common,
	&sdram0_clk.common,
	&sdram1_clk.common,
	&dram_ve_clk.common,
	&dram_csi_isp_clk.common,
	&dram_ts_clk.common,
	&dram_drc0_clk.common,
	&dram_drc1_clk.common,
	&dram_deu0_clk.common,
	&dram_deu1_clk.common,
	&dram_fe0_clk.common,
	&dram_fe1_clk.common,
	&dram_be0_clk.common,
	&dram_be1_clk.common,
	&dram_mp_clk.common,
	&be0_clk.common,
	&be1_clk.common,
	&fe0_clk.common,
	&fe1_clk.common,
	&mp_clk.common,
	&lcd0_ch0_clk.common,
	&lcd1_ch0_clk.common,
	&lcd0_ch1_clk.common,
	&lcd1_ch1_clk.common,
	&csi0_sclk_clk.common,
	&csi0_mclk_clk.common,
	&csi1_mclk_clk.common,
	&ve_clk.common,
	&codec_clk.common,
	&avs_clk.common,
	&digital_mic_clk.common,
	&hdmi_clk.common,
	&hdmi_ddc_clk.common,
	&ps_clk.common,
	&mbus0_clk.common,
	&mbus1_clk.common,
	&mipi_dsi_clk.common,
	&mipi_dsi_dphy_clk.common,
	&mipi_csi_dphy_clk.common,
	&iep_drc0_clk.common,
	&iep_drc1_clk.common,
	&iep_deu0_clk.common,
	&iep_deu1_clk.common,
	&gpu_core_clk.common,
	&gpu_memory_clk.common,
	&gpu_hyd_clk.common,
	&ats_clk.common,
	&trace_clk.common,
	&out_a_clk.common,
	&out_b_clk.common,
	&out_c_clk.common,
पूर्ण;

अटल स्थिर काष्ठा clk_hw *clk_parent_pll_audio[] = अणु
	&pll_audio_base_clk.common.hw
पूर्ण;

/* We hardcode the भागider to 1 क्रम now */
अटल CLK_FIXED_FACTOR_HWS(pll_audio_clk, "pll-audio",
			    clk_parent_pll_audio,
			    1, 1, CLK_SET_RATE_PARENT);
अटल CLK_FIXED_FACTOR_HWS(pll_audio_2x_clk, "pll-audio-2x",
			    clk_parent_pll_audio,
			    2, 1, CLK_SET_RATE_PARENT);
अटल CLK_FIXED_FACTOR_HWS(pll_audio_4x_clk, "pll-audio-4x",
			    clk_parent_pll_audio,
			    1, 1, CLK_SET_RATE_PARENT);
अटल CLK_FIXED_FACTOR_HWS(pll_audio_8x_clk, "pll-audio-8x",
			    clk_parent_pll_audio,
			    1, 2, CLK_SET_RATE_PARENT);
अटल CLK_FIXED_FACTOR_HW(pll_periph_2x_clk, "pll-periph-2x",
			   &pll_periph_clk.common.hw,
			   1, 2, 0);
अटल CLK_FIXED_FACTOR_HW(pll_video0_2x_clk, "pll-video0-2x",
			   &pll_video0_clk.common.hw,
			   1, 2, CLK_SET_RATE_PARENT);
अटल CLK_FIXED_FACTOR_HW(pll_video1_2x_clk, "pll-video1-2x",
			   &pll_video1_clk.common.hw,
			   1, 2, CLK_SET_RATE_PARENT);

अटल काष्ठा clk_hw_onecell_data sun6i_a31_hw_clks = अणु
	.hws	= अणु
		[CLK_PLL_CPU]		= &pll_cpu_clk.common.hw,
		[CLK_PLL_AUDIO_BASE]	= &pll_audio_base_clk.common.hw,
		[CLK_PLL_AUDIO]		= &pll_audio_clk.hw,
		[CLK_PLL_AUDIO_2X]	= &pll_audio_2x_clk.hw,
		[CLK_PLL_AUDIO_4X]	= &pll_audio_4x_clk.hw,
		[CLK_PLL_AUDIO_8X]	= &pll_audio_8x_clk.hw,
		[CLK_PLL_VIDEO0]	= &pll_video0_clk.common.hw,
		[CLK_PLL_VIDEO0_2X]	= &pll_video0_2x_clk.hw,
		[CLK_PLL_VE]		= &pll_ve_clk.common.hw,
		[CLK_PLL_DDR]		= &pll_ddr_clk.common.hw,
		[CLK_PLL_PERIPH]	= &pll_periph_clk.common.hw,
		[CLK_PLL_PERIPH_2X]	= &pll_periph_2x_clk.hw,
		[CLK_PLL_VIDEO1]	= &pll_video1_clk.common.hw,
		[CLK_PLL_VIDEO1_2X]	= &pll_video1_2x_clk.hw,
		[CLK_PLL_GPU]		= &pll_gpu_clk.common.hw,
		[CLK_PLL_MIPI]		= &pll_mipi_clk.common.hw,
		[CLK_PLL9]		= &pll9_clk.common.hw,
		[CLK_PLL10]		= &pll10_clk.common.hw,
		[CLK_CPU]		= &cpu_clk.common.hw,
		[CLK_AXI]		= &axi_clk.common.hw,
		[CLK_AHB1]		= &ahb1_clk.common.hw,
		[CLK_APB1]		= &apb1_clk.common.hw,
		[CLK_APB2]		= &apb2_clk.common.hw,
		[CLK_AHB1_MIPIDSI]	= &ahb1_mipidsi_clk.common.hw,
		[CLK_AHB1_SS]		= &ahb1_ss_clk.common.hw,
		[CLK_AHB1_DMA]		= &ahb1_dma_clk.common.hw,
		[CLK_AHB1_MMC0]		= &ahb1_mmc0_clk.common.hw,
		[CLK_AHB1_MMC1]		= &ahb1_mmc1_clk.common.hw,
		[CLK_AHB1_MMC2]		= &ahb1_mmc2_clk.common.hw,
		[CLK_AHB1_MMC3]		= &ahb1_mmc3_clk.common.hw,
		[CLK_AHB1_न_अंकD1]	= &ahb1_nand1_clk.common.hw,
		[CLK_AHB1_न_अंकD0]	= &ahb1_nand0_clk.common.hw,
		[CLK_AHB1_SDRAM]	= &ahb1_sdram_clk.common.hw,
		[CLK_AHB1_EMAC]		= &ahb1_emac_clk.common.hw,
		[CLK_AHB1_TS]		= &ahb1_ts_clk.common.hw,
		[CLK_AHB1_HSTIMER]	= &ahb1_hsसमयr_clk.common.hw,
		[CLK_AHB1_SPI0]		= &ahb1_spi0_clk.common.hw,
		[CLK_AHB1_SPI1]		= &ahb1_spi1_clk.common.hw,
		[CLK_AHB1_SPI2]		= &ahb1_spi2_clk.common.hw,
		[CLK_AHB1_SPI3]		= &ahb1_spi3_clk.common.hw,
		[CLK_AHB1_OTG]		= &ahb1_otg_clk.common.hw,
		[CLK_AHB1_EHCI0]	= &ahb1_ehci0_clk.common.hw,
		[CLK_AHB1_EHCI1]	= &ahb1_ehci1_clk.common.hw,
		[CLK_AHB1_OHCI0]	= &ahb1_ohci0_clk.common.hw,
		[CLK_AHB1_OHCI1]	= &ahb1_ohci1_clk.common.hw,
		[CLK_AHB1_OHCI2]	= &ahb1_ohci2_clk.common.hw,
		[CLK_AHB1_VE]		= &ahb1_ve_clk.common.hw,
		[CLK_AHB1_LCD0]		= &ahb1_lcd0_clk.common.hw,
		[CLK_AHB1_LCD1]		= &ahb1_lcd1_clk.common.hw,
		[CLK_AHB1_CSI]		= &ahb1_csi_clk.common.hw,
		[CLK_AHB1_HDMI]		= &ahb1_hdmi_clk.common.hw,
		[CLK_AHB1_BE0]		= &ahb1_be0_clk.common.hw,
		[CLK_AHB1_BE1]		= &ahb1_be1_clk.common.hw,
		[CLK_AHB1_FE0]		= &ahb1_fe0_clk.common.hw,
		[CLK_AHB1_FE1]		= &ahb1_fe1_clk.common.hw,
		[CLK_AHB1_MP]		= &ahb1_mp_clk.common.hw,
		[CLK_AHB1_GPU]		= &ahb1_gpu_clk.common.hw,
		[CLK_AHB1_DEU0]		= &ahb1_deu0_clk.common.hw,
		[CLK_AHB1_DEU1]		= &ahb1_deu1_clk.common.hw,
		[CLK_AHB1_DRC0]		= &ahb1_drc0_clk.common.hw,
		[CLK_AHB1_DRC1]		= &ahb1_drc1_clk.common.hw,
		[CLK_APB1_CODEC]	= &apb1_codec_clk.common.hw,
		[CLK_APB1_SPDIF]	= &apb1_spdअगर_clk.common.hw,
		[CLK_APB1_DIGITAL_MIC]	= &apb1_digital_mic_clk.common.hw,
		[CLK_APB1_PIO]		= &apb1_pio_clk.common.hw,
		[CLK_APB1_DAUDIO0]	= &apb1_daudio0_clk.common.hw,
		[CLK_APB1_DAUDIO1]	= &apb1_daudio1_clk.common.hw,
		[CLK_APB2_I2C0]		= &apb2_i2c0_clk.common.hw,
		[CLK_APB2_I2C1]		= &apb2_i2c1_clk.common.hw,
		[CLK_APB2_I2C2]		= &apb2_i2c2_clk.common.hw,
		[CLK_APB2_I2C3]		= &apb2_i2c3_clk.common.hw,
		[CLK_APB2_UART0]	= &apb2_uart0_clk.common.hw,
		[CLK_APB2_UART1]	= &apb2_uart1_clk.common.hw,
		[CLK_APB2_UART2]	= &apb2_uart2_clk.common.hw,
		[CLK_APB2_UART3]	= &apb2_uart3_clk.common.hw,
		[CLK_APB2_UART4]	= &apb2_uart4_clk.common.hw,
		[CLK_APB2_UART5]	= &apb2_uart5_clk.common.hw,
		[CLK_न_अंकD0]		= &nand0_clk.common.hw,
		[CLK_न_अंकD1]		= &nand1_clk.common.hw,
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
		[CLK_DAUDIO0]		= &daudio0_clk.common.hw,
		[CLK_DAUDIO1]		= &daudio1_clk.common.hw,
		[CLK_SPDIF]		= &spdअगर_clk.common.hw,
		[CLK_USB_PHY0]		= &usb_phy0_clk.common.hw,
		[CLK_USB_PHY1]		= &usb_phy1_clk.common.hw,
		[CLK_USB_PHY2]		= &usb_phy2_clk.common.hw,
		[CLK_USB_OHCI0]		= &usb_ohci0_clk.common.hw,
		[CLK_USB_OHCI1]		= &usb_ohci1_clk.common.hw,
		[CLK_USB_OHCI2]		= &usb_ohci2_clk.common.hw,
		[CLK_MDFS]		= &mdfs_clk.common.hw,
		[CLK_SDRAM0]		= &sdram0_clk.common.hw,
		[CLK_SDRAM1]		= &sdram1_clk.common.hw,
		[CLK_DRAM_VE]		= &dram_ve_clk.common.hw,
		[CLK_DRAM_CSI_ISP]	= &dram_csi_isp_clk.common.hw,
		[CLK_DRAM_TS]		= &dram_ts_clk.common.hw,
		[CLK_DRAM_DRC0]		= &dram_drc0_clk.common.hw,
		[CLK_DRAM_DRC1]		= &dram_drc1_clk.common.hw,
		[CLK_DRAM_DEU0]		= &dram_deu0_clk.common.hw,
		[CLK_DRAM_DEU1]		= &dram_deu1_clk.common.hw,
		[CLK_DRAM_FE0]		= &dram_fe0_clk.common.hw,
		[CLK_DRAM_FE1]		= &dram_fe1_clk.common.hw,
		[CLK_DRAM_BE0]		= &dram_be0_clk.common.hw,
		[CLK_DRAM_BE1]		= &dram_be1_clk.common.hw,
		[CLK_DRAM_MP]		= &dram_mp_clk.common.hw,
		[CLK_BE0]		= &be0_clk.common.hw,
		[CLK_BE1]		= &be1_clk.common.hw,
		[CLK_FE0]		= &fe0_clk.common.hw,
		[CLK_FE1]		= &fe1_clk.common.hw,
		[CLK_MP]		= &mp_clk.common.hw,
		[CLK_LCD0_CH0]		= &lcd0_ch0_clk.common.hw,
		[CLK_LCD1_CH0]		= &lcd1_ch0_clk.common.hw,
		[CLK_LCD0_CH1]		= &lcd0_ch1_clk.common.hw,
		[CLK_LCD1_CH1]		= &lcd1_ch1_clk.common.hw,
		[CLK_CSI0_SCLK]		= &csi0_sclk_clk.common.hw,
		[CLK_CSI0_MCLK]		= &csi0_mclk_clk.common.hw,
		[CLK_CSI1_MCLK]		= &csi1_mclk_clk.common.hw,
		[CLK_VE]		= &ve_clk.common.hw,
		[CLK_CODEC]		= &codec_clk.common.hw,
		[CLK_AVS]		= &avs_clk.common.hw,
		[CLK_DIGITAL_MIC]	= &digital_mic_clk.common.hw,
		[CLK_HDMI]		= &hdmi_clk.common.hw,
		[CLK_HDMI_DDC]		= &hdmi_ddc_clk.common.hw,
		[CLK_PS]		= &ps_clk.common.hw,
		[CLK_MBUS0]		= &mbus0_clk.common.hw,
		[CLK_MBUS1]		= &mbus1_clk.common.hw,
		[CLK_MIPI_DSI]		= &mipi_dsi_clk.common.hw,
		[CLK_MIPI_DSI_DPHY]	= &mipi_dsi_dphy_clk.common.hw,
		[CLK_MIPI_CSI_DPHY]	= &mipi_csi_dphy_clk.common.hw,
		[CLK_IEP_DRC0]		= &iep_drc0_clk.common.hw,
		[CLK_IEP_DRC1]		= &iep_drc1_clk.common.hw,
		[CLK_IEP_DEU0]		= &iep_deu0_clk.common.hw,
		[CLK_IEP_DEU1]		= &iep_deu1_clk.common.hw,
		[CLK_GPU_CORE]		= &gpu_core_clk.common.hw,
		[CLK_GPU_MEMORY]	= &gpu_memory_clk.common.hw,
		[CLK_GPU_HYD]		= &gpu_hyd_clk.common.hw,
		[CLK_ATS]		= &ats_clk.common.hw,
		[CLK_TRACE]		= &trace_clk.common.hw,
		[CLK_OUT_A]		= &out_a_clk.common.hw,
		[CLK_OUT_B]		= &out_b_clk.common.hw,
		[CLK_OUT_C]		= &out_c_clk.common.hw,
	पूर्ण,
	.num	= CLK_NUMBER,
पूर्ण;

अटल काष्ठा ccu_reset_map sun6i_a31_ccu_resets[] = अणु
	[RST_USB_PHY0]		= अणु 0x0cc, BIT(0) पूर्ण,
	[RST_USB_PHY1]		= अणु 0x0cc, BIT(1) पूर्ण,
	[RST_USB_PHY2]		= अणु 0x0cc, BIT(2) पूर्ण,

	[RST_AHB1_MIPI_DSI]	= अणु 0x2c0, BIT(1) पूर्ण,
	[RST_AHB1_SS]		= अणु 0x2c0, BIT(5) पूर्ण,
	[RST_AHB1_DMA]		= अणु 0x2c0, BIT(6) पूर्ण,
	[RST_AHB1_MMC0]		= अणु 0x2c0, BIT(8) पूर्ण,
	[RST_AHB1_MMC1]		= अणु 0x2c0, BIT(9) पूर्ण,
	[RST_AHB1_MMC2]		= अणु 0x2c0, BIT(10) पूर्ण,
	[RST_AHB1_MMC3]		= अणु 0x2c0, BIT(11) पूर्ण,
	[RST_AHB1_न_अंकD1]	= अणु 0x2c0, BIT(12) पूर्ण,
	[RST_AHB1_न_अंकD0]	= अणु 0x2c0, BIT(13) पूर्ण,
	[RST_AHB1_SDRAM]	= अणु 0x2c0, BIT(14) पूर्ण,
	[RST_AHB1_EMAC]		= अणु 0x2c0, BIT(17) पूर्ण,
	[RST_AHB1_TS]		= अणु 0x2c0, BIT(18) पूर्ण,
	[RST_AHB1_HSTIMER]	= अणु 0x2c0, BIT(19) पूर्ण,
	[RST_AHB1_SPI0]		= अणु 0x2c0, BIT(20) पूर्ण,
	[RST_AHB1_SPI1]		= अणु 0x2c0, BIT(21) पूर्ण,
	[RST_AHB1_SPI2]		= अणु 0x2c0, BIT(22) पूर्ण,
	[RST_AHB1_SPI3]		= अणु 0x2c0, BIT(23) पूर्ण,
	[RST_AHB1_OTG]		= अणु 0x2c0, BIT(24) पूर्ण,
	[RST_AHB1_EHCI0]	= अणु 0x2c0, BIT(26) पूर्ण,
	[RST_AHB1_EHCI1]	= अणु 0x2c0, BIT(27) पूर्ण,
	[RST_AHB1_OHCI0]	= अणु 0x2c0, BIT(29) पूर्ण,
	[RST_AHB1_OHCI1]	= अणु 0x2c0, BIT(30) पूर्ण,
	[RST_AHB1_OHCI2]	= अणु 0x2c0, BIT(31) पूर्ण,

	[RST_AHB1_VE]		= अणु 0x2c4, BIT(0) पूर्ण,
	[RST_AHB1_LCD0]		= अणु 0x2c4, BIT(4) पूर्ण,
	[RST_AHB1_LCD1]		= अणु 0x2c4, BIT(5) पूर्ण,
	[RST_AHB1_CSI]		= अणु 0x2c4, BIT(8) पूर्ण,
	[RST_AHB1_HDMI]		= अणु 0x2c4, BIT(11) पूर्ण,
	[RST_AHB1_BE0]		= अणु 0x2c4, BIT(12) पूर्ण,
	[RST_AHB1_BE1]		= अणु 0x2c4, BIT(13) पूर्ण,
	[RST_AHB1_FE0]		= अणु 0x2c4, BIT(14) पूर्ण,
	[RST_AHB1_FE1]		= अणु 0x2c4, BIT(15) पूर्ण,
	[RST_AHB1_MP]		= अणु 0x2c4, BIT(18) पूर्ण,
	[RST_AHB1_GPU]		= अणु 0x2c4, BIT(20) पूर्ण,
	[RST_AHB1_DEU0]		= अणु 0x2c4, BIT(23) पूर्ण,
	[RST_AHB1_DEU1]		= अणु 0x2c4, BIT(24) पूर्ण,
	[RST_AHB1_DRC0]		= अणु 0x2c4, BIT(25) पूर्ण,
	[RST_AHB1_DRC1]		= अणु 0x2c4, BIT(26) पूर्ण,
	[RST_AHB1_LVDS]		= अणु 0x2c8, BIT(0) पूर्ण,

	[RST_APB1_CODEC]	= अणु 0x2d0, BIT(0) पूर्ण,
	[RST_APB1_SPDIF]	= अणु 0x2d0, BIT(1) पूर्ण,
	[RST_APB1_DIGITAL_MIC]	= अणु 0x2d0, BIT(4) पूर्ण,
	[RST_APB1_DAUDIO0]	= अणु 0x2d0, BIT(12) पूर्ण,
	[RST_APB1_DAUDIO1]	= अणु 0x2d0, BIT(13) पूर्ण,

	[RST_APB2_I2C0]		= अणु 0x2d8, BIT(0) पूर्ण,
	[RST_APB2_I2C1]		= अणु 0x2d8, BIT(1) पूर्ण,
	[RST_APB2_I2C2]		= अणु 0x2d8, BIT(2) पूर्ण,
	[RST_APB2_I2C3]		= अणु 0x2d8, BIT(3) पूर्ण,
	[RST_APB2_UART0]	= अणु 0x2d8, BIT(16) पूर्ण,
	[RST_APB2_UART1]	= अणु 0x2d8, BIT(17) पूर्ण,
	[RST_APB2_UART2]	= अणु 0x2d8, BIT(18) पूर्ण,
	[RST_APB2_UART3]	= अणु 0x2d8, BIT(19) पूर्ण,
	[RST_APB2_UART4]	= अणु 0x2d8, BIT(20) पूर्ण,
	[RST_APB2_UART5]	= अणु 0x2d8, BIT(21) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun6i_a31_ccu_desc = अणु
	.ccu_clks	= sun6i_a31_ccu_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun6i_a31_ccu_clks),

	.hw_clks	= &sun6i_a31_hw_clks,

	.resets		= sun6i_a31_ccu_resets,
	.num_resets	= ARRAY_SIZE(sun6i_a31_ccu_resets),
पूर्ण;

अटल काष्ठा ccu_mux_nb sun6i_a31_cpu_nb = अणु
	.common		= &cpu_clk.common,
	.cm		= &cpu_clk.mux,
	.delay_us	= 1, /* > 8 घड़ी cycles at 24 MHz */
	.bypass_index	= 1, /* index of 24 MHz oscillator */
पूर्ण;

अटल व्योम __init sun6i_a31_ccu_setup(काष्ठा device_node *node)
अणु
	व्योम __iomem *reg;
	u32 val;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg)) अणु
		pr_err("%pOF: Could not map the clock registers\n", node);
		वापस;
	पूर्ण

	/* Force the PLL-Audio-1x भागider to 1 */
	val = पढ़ोl(reg + SUN6I_A31_PLL_AUDIO_REG);
	val &= ~GENMASK(19, 16);
	ग_लिखोl(val | (0 << 16), reg + SUN6I_A31_PLL_AUDIO_REG);

	/* Force PLL-MIPI to MIPI mode */
	val = पढ़ोl(reg + SUN6I_A31_PLL_MIPI_REG);
	val &= BIT(16);
	ग_लिखोl(val, reg + SUN6I_A31_PLL_MIPI_REG);

	/* Force AHB1 to PLL6 / 3 */
	val = पढ़ोl(reg + SUN6I_A31_AHB1_REG);
	/* set PLL6 pre-भाग = 3 */
	val &= ~GENMASK(7, 6);
	val |= 0x2 << 6;
	/* select PLL6 / pre-भाग */
	val &= ~GENMASK(13, 12);
	val |= 0x3 << 12;
	ग_लिखोl(val, reg + SUN6I_A31_AHB1_REG);

	sunxi_ccu_probe(node, reg, &sun6i_a31_ccu_desc);

	ccu_mux_notअगरier_रेजिस्टर(pll_cpu_clk.common.hw.clk,
				  &sun6i_a31_cpu_nb);
पूर्ण
CLK_OF_DECLARE(sun6i_a31_ccu, "allwinner,sun6i-a31-ccu",
	       sun6i_a31_ccu_setup);
