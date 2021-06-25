<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 Icenowy Zheng <icenowy@aosc.io>
 *
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
#समावेश "ccu_nk.h"
#समावेश "ccu_nkm.h"
#समावेश "ccu_nkmp.h"
#समावेश "ccu_nm.h"
#समावेश "ccu_phase.h"

#समावेश "ccu-suniv-f1c100s.h"

अटल काष्ठा ccu_nkmp pll_cpu_clk = अणु
	.enable = BIT(31),
	.lock	= BIT(28),

	.n	= _SUNXI_CCU_MULT(8, 5),
	.k	= _SUNXI_CCU_MULT(4, 2),
	.m	= _SUNXI_CCU_DIV(0, 2),
	/* MAX is guessed by the BSP table */
	.p	= _SUNXI_CCU_DIV_MAX(16, 2, 4),

	.common	= अणु
		.reg		= 0x000,
		.hw.init	= CLK_HW_INIT("pll-cpu", "osc24M",
					      &ccu_nkmp_ops,
					      CLK_SET_RATE_UNGATE),
	पूर्ण,
पूर्ण;

/*
 * The Audio PLL is supposed to have 4 outमाला_दो: 3 fixed factors from
 * the base (2x, 4x and 8x), and one variable भागider (the one true
 * pll audio).
 *
 * We करोn't have any need क्रम the variable भागider क्रम now, so we just
 * hardcode it to match with the घड़ी names
 */
#घोषणा SUNIV_PLL_AUDIO_REG	0x008

अटल SUNXI_CCU_NM_WITH_GATE_LOCK(pll_audio_base_clk, "pll-audio-base",
				   "osc24M", 0x008,
				   8, 7,		/* N */
				   0, 5,		/* M */
				   BIT(31),		/* gate */
				   BIT(28),		/* lock */
				   CLK_SET_RATE_UNGATE);

अटल SUNXI_CCU_NM_WITH_FRAC_GATE_LOCK(pll_video_clk, "pll-video",
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

अटल SUNXI_CCU_NKM_WITH_GATE_LOCK(pll_ddr0_clk, "pll-ddr",
				    "osc24M", 0x020,
				    8, 5,		/* N */
				    4, 2,		/* K */
				    0, 2,		/* M */
				    BIT(31),		/* gate */
				    BIT(28),		/* lock */
				    CLK_IS_CRITICAL);

अटल काष्ठा ccu_nk pll_periph_clk = अणु
	.enable		= BIT(31),
	.lock		= BIT(28),
	.k		= _SUNXI_CCU_MULT(4, 2),
	.n		= _SUNXI_CCU_MULT(8, 5),
	.common		= अणु
		.reg		= 0x028,
		.hw.init	= CLK_HW_INIT("pll-periph", "osc24M",
					      &ccu_nk_ops, 0),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर cpu_parents[] = अणु "osc32k", "osc24M",
					     "pll-cpu", "pll-cpu" पूर्ण;
अटल SUNXI_CCU_MUX(cpu_clk, "cpu", cpu_parents,
		     0x050, 16, 2, CLK_IS_CRITICAL | CLK_SET_RATE_PARENT);

अटल स्थिर अक्षर * स्थिर ahb_parents[] = अणु "osc32k", "osc24M",
					    "cpu", "pll-periph" पूर्ण;
अटल स्थिर काष्ठा ccu_mux_var_preभाग ahb_preभागs[] = अणु
	अणु .index = 3, .shअगरt = 6, .width = 2 पूर्ण,
पूर्ण;
अटल काष्ठा ccu_भाग ahb_clk = अणु
	.भाग		= _SUNXI_CCU_DIV_FLAGS(4, 2, CLK_DIVIDER_POWER_OF_TWO),

	.mux		= अणु
		.shअगरt	= 12,
		.width	= 2,

		.var_preभागs	= ahb_preभागs,
		.n_var_preभागs	= ARRAY_SIZE(ahb_preभागs),
	पूर्ण,

	.common		= अणु
		.reg		= 0x054,
		.features	= CCU_FEATURE_VARIABLE_PREDIV,
		.hw.init	= CLK_HW_INIT_PARENTS("ahb",
						      ahb_parents,
						      &ccu_भाग_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable apb_भाग_प्रकारable[] = अणु
	अणु .val = 0, .भाग = 2 पूर्ण,
	अणु .val = 1, .भाग = 2 पूर्ण,
	अणु .val = 2, .भाग = 4 पूर्ण,
	अणु .val = 3, .भाग = 8 पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;
अटल SUNXI_CCU_DIV_TABLE(apb_clk, "apb", "ahb",
			   0x054, 8, 2, apb_भाग_प्रकारable, 0);

अटल SUNXI_CCU_GATE(bus_dma_clk,	"bus-dma",	"ahb",
		      0x060, BIT(6), 0);
अटल SUNXI_CCU_GATE(bus_mmc0_clk,	"bus-mmc0",	"ahb",
		      0x060, BIT(8), 0);
अटल SUNXI_CCU_GATE(bus_mmc1_clk,	"bus-mmc1",	"ahb",
		      0x060, BIT(9), 0);
अटल SUNXI_CCU_GATE(bus_dram_clk,	"bus-dram",	"ahb",
		      0x060, BIT(14), 0);
अटल SUNXI_CCU_GATE(bus_spi0_clk,	"bus-spi0",	"ahb",
		      0x060, BIT(20), 0);
अटल SUNXI_CCU_GATE(bus_spi1_clk,	"bus-spi1",	"ahb",
		      0x060, BIT(21), 0);
अटल SUNXI_CCU_GATE(bus_otg_clk,	"bus-otg",	"ahb",
		      0x060, BIT(24), 0);

अटल SUNXI_CCU_GATE(bus_ve_clk,	"bus-ve",	"ahb",
		      0x064, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_lcd_clk,	"bus-lcd",	"ahb",
		      0x064, BIT(4), 0);
अटल SUNXI_CCU_GATE(bus_deपूर्णांकerlace_clk,	"bus-deinterlace",	"ahb",
		      0x064, BIT(5), 0);
अटल SUNXI_CCU_GATE(bus_csi_clk,	"bus-csi",	"ahb",
		      0x064, BIT(8), 0);
अटल SUNXI_CCU_GATE(bus_tvd_clk,	"bus-tvd",	"ahb",
		      0x064, BIT(9), 0);
अटल SUNXI_CCU_GATE(bus_tve_clk,	"bus-tve",	"ahb",
		      0x064, BIT(10), 0);
अटल SUNXI_CCU_GATE(bus_de_be_clk,	"bus-de-be",	"ahb",
		      0x064, BIT(12), 0);
अटल SUNXI_CCU_GATE(bus_de_fe_clk,	"bus-de-fe",	"ahb",
		      0x064, BIT(14), 0);

अटल SUNXI_CCU_GATE(bus_codec_clk,	"bus-codec",	"apb",
		      0x068, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_spdअगर_clk,	"bus-spdif",	"apb",
		      0x068, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_ir_clk,	"bus-ir",	"apb",
		      0x068, BIT(2), 0);
अटल SUNXI_CCU_GATE(bus_rsb_clk,	"bus-rsb",	"apb",
		      0x068, BIT(3), 0);
अटल SUNXI_CCU_GATE(bus_i2s0_clk,	"bus-i2s0",	"apb",
		      0x068, BIT(12), 0);
अटल SUNXI_CCU_GATE(bus_i2c0_clk,	"bus-i2c0",	"apb",
		      0x068, BIT(16), 0);
अटल SUNXI_CCU_GATE(bus_i2c1_clk,	"bus-i2c1",	"apb",
		      0x068, BIT(17), 0);
अटल SUNXI_CCU_GATE(bus_i2c2_clk,	"bus-i2c2",	"apb",
		      0x068, BIT(18), 0);
अटल SUNXI_CCU_GATE(bus_pio_clk,	"bus-pio",	"apb",
		      0x068, BIT(19), 0);
अटल SUNXI_CCU_GATE(bus_uart0_clk,	"bus-uart0",	"apb",
		      0x068, BIT(20), 0);
अटल SUNXI_CCU_GATE(bus_uart1_clk,	"bus-uart1",	"apb",
		      0x068, BIT(21), 0);
अटल SUNXI_CCU_GATE(bus_uart2_clk,	"bus-uart2",	"apb",
		      0x068, BIT(22), 0);

अटल स्थिर अक्षर * स्थिर mod0_शेष_parents[] = अणु "osc24M", "pll-periph" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX_GATE(mmc0_clk, "mmc0", mod0_शेष_parents, 0x088,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_PHASE(mmc0_sample_clk, "mmc0_sample", "mmc0",
		       0x088, 20, 3, 0);
अटल SUNXI_CCU_PHASE(mmc0_output_clk, "mmc0_output", "mmc0",
		       0x088, 8, 3, 0);

अटल SUNXI_CCU_MP_WITH_MUX_GATE(mmc1_clk, "mmc1", mod0_शेष_parents, 0x08c,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_PHASE(mmc1_sample_clk, "mmc1_sample", "mmc1",
		       0x08c, 20, 3, 0);
अटल SUNXI_CCU_PHASE(mmc1_output_clk, "mmc1_output", "mmc1",
		       0x08c, 8, 3, 0);

अटल स्थिर अक्षर * स्थिर i2s_spdअगर_parents[] = अणु "pll-audio-8x",
						  "pll-audio-4x",
						  "pll-audio-2x",
						  "pll-audio" पूर्ण;

अटल SUNXI_CCU_MUX_WITH_GATE(i2s_clk, "i2s", i2s_spdअगर_parents,
			       0x0b0, 16, 2, BIT(31), 0);

अटल SUNXI_CCU_MUX_WITH_GATE(spdअगर_clk, "spdif", i2s_spdअगर_parents,
			       0x0b4, 16, 2, BIT(31), 0);

/* The BSP header file has a CIR_CFG, but no mod घड़ी uses this definition */

अटल SUNXI_CCU_GATE(usb_phy0_clk,	"usb-phy0",	"osc24M",
		      0x0cc, BIT(1), 0);

अटल SUNXI_CCU_GATE(dram_ve_clk,	"dram-ve",	"pll-ddr",
		      0x100, BIT(0), 0);
अटल SUNXI_CCU_GATE(dram_csi_clk,	"dram-csi",	"pll-ddr",
		      0x100, BIT(1), 0);
अटल SUNXI_CCU_GATE(dram_deपूर्णांकerlace_clk,	"dram-deinterlace",
		      "pll-ddr", 0x100, BIT(2), 0);
अटल SUNXI_CCU_GATE(dram_tvd_clk,	"dram-tvd",	"pll-ddr",
		      0x100, BIT(3), 0);
अटल SUNXI_CCU_GATE(dram_de_fe_clk,	"dram-de-fe",	"pll-ddr",
		      0x100, BIT(24), 0);
अटल SUNXI_CCU_GATE(dram_de_be_clk,	"dram-de-be",	"pll-ddr",
		      0x100, BIT(26), 0);

अटल स्थिर अक्षर * स्थिर de_parents[] = अणु "pll-video", "pll-periph" पूर्ण;
अटल स्थिर u8 de_table[] = अणु 0, 2, पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_TABLE_GATE(de_be_clk, "de-be",
				       de_parents, de_table,
				       0x104, 0, 4, 24, 3, BIT(31), 0);

अटल SUNXI_CCU_M_WITH_MUX_TABLE_GATE(de_fe_clk, "de-fe",
				       de_parents, de_table,
				       0x10c, 0, 4, 24, 3, BIT(31), 0);

अटल स्थिर अक्षर * स्थिर tcon_parents[] = अणु "pll-video", "pll-video-2x" पूर्ण;
अटल स्थिर u8 tcon_table[] = अणु 0, 2, पूर्ण;
अटल SUNXI_CCU_MUX_TABLE_WITH_GATE(tcon_clk, "tcon",
				     tcon_parents, tcon_table,
				     0x118, 24, 3, BIT(31),
				     CLK_SET_RATE_PARENT);

अटल स्थिर अक्षर * स्थिर deपूर्णांकerlace_parents[] = अणु "pll-video",
						    "pll-video-2x" पूर्ण;
अटल स्थिर u8 deपूर्णांकerlace_table[] = अणु 0, 2, पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_TABLE_GATE(deपूर्णांकerlace_clk, "deinterlace",
				       deपूर्णांकerlace_parents, deपूर्णांकerlace_table,
				       0x11c, 0, 4, 24, 3, BIT(31), 0);

अटल स्थिर अक्षर * स्थिर tve_clk2_parents[] = अणु "pll-video",
						 "pll-video-2x" पूर्ण;
अटल स्थिर u8 tve_clk2_table[] = अणु 0, 2, पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_TABLE_GATE(tve_clk2_clk, "tve-clk2",
				       tve_clk2_parents, tve_clk2_table,
				       0x120, 0, 4, 24, 3, BIT(31), 0);
अटल SUNXI_CCU_M_WITH_GATE(tve_clk1_clk, "tve-clk1", "tve-clk2",
			     0x120, 8, 1, BIT(15), 0);

अटल स्थिर अक्षर * स्थिर tvd_parents[] = अणु "pll-video", "osc24M",
					    "pll-video-2x" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(tvd_clk, "tvd", tvd_parents,
				 0x124, 0, 4, 24, 3, BIT(31), 0);

अटल स्थिर अक्षर * स्थिर csi_parents[] = अणु "pll-video", "osc24M" पूर्ण;
अटल स्थिर u8 csi_table[] = अणु 0, 5, पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_TABLE_GATE(csi_clk, "csi", csi_parents, csi_table,
				       0x120, 0, 4, 8, 3, BIT(15), 0);

/*
 * TODO: BSP says the parent is pll-audio, however common sense and experience
 * told us it should be pll-ve. pll-ve is totally not used in BSP code.
 */
अटल SUNXI_CCU_GATE(ve_clk, "ve", "pll-audio", 0x13c, BIT(31), 0);

अटल SUNXI_CCU_GATE(codec_clk, "codec", "pll-audio", 0x140, BIT(31), 0);

अटल SUNXI_CCU_GATE(avs_clk, "avs", "osc24M", 0x144, BIT(31), 0);

अटल काष्ठा ccu_common *suniv_ccu_clks[] = अणु
	&pll_cpu_clk.common,
	&pll_audio_base_clk.common,
	&pll_video_clk.common,
	&pll_ve_clk.common,
	&pll_ddr0_clk.common,
	&pll_periph_clk.common,
	&cpu_clk.common,
	&ahb_clk.common,
	&apb_clk.common,
	&bus_dma_clk.common,
	&bus_mmc0_clk.common,
	&bus_mmc1_clk.common,
	&bus_dram_clk.common,
	&bus_spi0_clk.common,
	&bus_spi1_clk.common,
	&bus_otg_clk.common,
	&bus_ve_clk.common,
	&bus_lcd_clk.common,
	&bus_deपूर्णांकerlace_clk.common,
	&bus_csi_clk.common,
	&bus_tve_clk.common,
	&bus_tvd_clk.common,
	&bus_de_be_clk.common,
	&bus_de_fe_clk.common,
	&bus_codec_clk.common,
	&bus_spdअगर_clk.common,
	&bus_ir_clk.common,
	&bus_rsb_clk.common,
	&bus_i2s0_clk.common,
	&bus_i2c0_clk.common,
	&bus_i2c1_clk.common,
	&bus_i2c2_clk.common,
	&bus_pio_clk.common,
	&bus_uart0_clk.common,
	&bus_uart1_clk.common,
	&bus_uart2_clk.common,
	&mmc0_clk.common,
	&mmc0_sample_clk.common,
	&mmc0_output_clk.common,
	&mmc1_clk.common,
	&mmc1_sample_clk.common,
	&mmc1_output_clk.common,
	&i2s_clk.common,
	&spdअगर_clk.common,
	&usb_phy0_clk.common,
	&dram_ve_clk.common,
	&dram_csi_clk.common,
	&dram_deपूर्णांकerlace_clk.common,
	&dram_tvd_clk.common,
	&dram_de_fe_clk.common,
	&dram_de_be_clk.common,
	&de_be_clk.common,
	&de_fe_clk.common,
	&tcon_clk.common,
	&deपूर्णांकerlace_clk.common,
	&tve_clk2_clk.common,
	&tve_clk1_clk.common,
	&tvd_clk.common,
	&csi_clk.common,
	&ve_clk.common,
	&codec_clk.common,
	&avs_clk.common,
पूर्ण;

अटल स्थिर काष्ठा clk_hw *clk_parent_pll_audio[] = अणु
	&pll_audio_base_clk.common.hw
पूर्ण;

अटल CLK_FIXED_FACTOR_HWS(pll_audio_clk, "pll-audio",
			    clk_parent_pll_audio,
			    4, 1, CLK_SET_RATE_PARENT);
अटल CLK_FIXED_FACTOR_HWS(pll_audio_2x_clk, "pll-audio-2x",
			    clk_parent_pll_audio,
			    2, 1, CLK_SET_RATE_PARENT);
अटल CLK_FIXED_FACTOR_HWS(pll_audio_4x_clk, "pll-audio-4x",
			    clk_parent_pll_audio,
			    1, 1, CLK_SET_RATE_PARENT);
अटल CLK_FIXED_FACTOR_HWS(pll_audio_8x_clk, "pll-audio-8x",
			    clk_parent_pll_audio,
			    1, 2, CLK_SET_RATE_PARENT);
अटल CLK_FIXED_FACTOR_HW(pll_video_2x_clk, "pll-video-2x",
			    &pll_video_clk.common.hw,
			    1, 2, 0);

अटल काष्ठा clk_hw_onecell_data suniv_hw_clks = अणु
	.hws	= अणु
		[CLK_PLL_CPU]		= &pll_cpu_clk.common.hw,
		[CLK_PLL_AUDIO_BASE]	= &pll_audio_base_clk.common.hw,
		[CLK_PLL_AUDIO]		= &pll_audio_clk.hw,
		[CLK_PLL_AUDIO_2X]	= &pll_audio_2x_clk.hw,
		[CLK_PLL_AUDIO_4X]	= &pll_audio_4x_clk.hw,
		[CLK_PLL_AUDIO_8X]	= &pll_audio_8x_clk.hw,
		[CLK_PLL_VIDEO]		= &pll_video_clk.common.hw,
		[CLK_PLL_VIDEO_2X]	= &pll_video_2x_clk.hw,
		[CLK_PLL_VE]		= &pll_ve_clk.common.hw,
		[CLK_PLL_DDR0]		= &pll_ddr0_clk.common.hw,
		[CLK_PLL_PERIPH]	= &pll_periph_clk.common.hw,
		[CLK_CPU]		= &cpu_clk.common.hw,
		[CLK_AHB]		= &ahb_clk.common.hw,
		[CLK_APB]		= &apb_clk.common.hw,
		[CLK_BUS_DMA]		= &bus_dma_clk.common.hw,
		[CLK_BUS_MMC0]		= &bus_mmc0_clk.common.hw,
		[CLK_BUS_MMC1]		= &bus_mmc1_clk.common.hw,
		[CLK_BUS_DRAM]		= &bus_dram_clk.common.hw,
		[CLK_BUS_SPI0]		= &bus_spi0_clk.common.hw,
		[CLK_BUS_SPI1]		= &bus_spi1_clk.common.hw,
		[CLK_BUS_OTG]		= &bus_otg_clk.common.hw,
		[CLK_BUS_VE]		= &bus_ve_clk.common.hw,
		[CLK_BUS_LCD]		= &bus_lcd_clk.common.hw,
		[CLK_BUS_DEINTERLACE]	= &bus_deपूर्णांकerlace_clk.common.hw,
		[CLK_BUS_CSI]		= &bus_csi_clk.common.hw,
		[CLK_BUS_TVD]		= &bus_tvd_clk.common.hw,
		[CLK_BUS_TVE]		= &bus_tve_clk.common.hw,
		[CLK_BUS_DE_BE]		= &bus_de_be_clk.common.hw,
		[CLK_BUS_DE_FE]		= &bus_de_fe_clk.common.hw,
		[CLK_BUS_CODEC]		= &bus_codec_clk.common.hw,
		[CLK_BUS_SPDIF]		= &bus_spdअगर_clk.common.hw,
		[CLK_BUS_IR]		= &bus_ir_clk.common.hw,
		[CLK_BUS_RSB]		= &bus_rsb_clk.common.hw,
		[CLK_BUS_I2S0]		= &bus_i2s0_clk.common.hw,
		[CLK_BUS_I2C0]		= &bus_i2c0_clk.common.hw,
		[CLK_BUS_I2C1]		= &bus_i2c1_clk.common.hw,
		[CLK_BUS_I2C2]		= &bus_i2c2_clk.common.hw,
		[CLK_BUS_PIO]		= &bus_pio_clk.common.hw,
		[CLK_BUS_UART0]		= &bus_uart0_clk.common.hw,
		[CLK_BUS_UART1]		= &bus_uart1_clk.common.hw,
		[CLK_BUS_UART2]		= &bus_uart2_clk.common.hw,
		[CLK_MMC0]		= &mmc0_clk.common.hw,
		[CLK_MMC0_SAMPLE]	= &mmc0_sample_clk.common.hw,
		[CLK_MMC0_OUTPUT]	= &mmc0_output_clk.common.hw,
		[CLK_MMC1]		= &mmc1_clk.common.hw,
		[CLK_MMC1_SAMPLE]	= &mmc1_sample_clk.common.hw,
		[CLK_MMC1_OUTPUT]	= &mmc1_output_clk.common.hw,
		[CLK_I2S]		= &i2s_clk.common.hw,
		[CLK_SPDIF]		= &spdअगर_clk.common.hw,
		[CLK_USB_PHY0]		= &usb_phy0_clk.common.hw,
		[CLK_DRAM_VE]		= &dram_ve_clk.common.hw,
		[CLK_DRAM_CSI]		= &dram_csi_clk.common.hw,
		[CLK_DRAM_DEINTERLACE]	= &dram_deपूर्णांकerlace_clk.common.hw,
		[CLK_DRAM_TVD]		= &dram_tvd_clk.common.hw,
		[CLK_DRAM_DE_FE]	= &dram_de_fe_clk.common.hw,
		[CLK_DRAM_DE_BE]	= &dram_de_be_clk.common.hw,
		[CLK_DE_BE]		= &de_be_clk.common.hw,
		[CLK_DE_FE]		= &de_fe_clk.common.hw,
		[CLK_TCON]		= &tcon_clk.common.hw,
		[CLK_DEINTERLACE]	= &deपूर्णांकerlace_clk.common.hw,
		[CLK_TVE2_CLK]		= &tve_clk2_clk.common.hw,
		[CLK_TVE1_CLK]		= &tve_clk1_clk.common.hw,
		[CLK_TVD]		= &tvd_clk.common.hw,
		[CLK_CSI]		= &csi_clk.common.hw,
		[CLK_VE]		= &ve_clk.common.hw,
		[CLK_CODEC]		= &codec_clk.common.hw,
		[CLK_AVS]		= &avs_clk.common.hw,
	पूर्ण,
	.num	= CLK_NUMBER,
पूर्ण;

अटल काष्ठा ccu_reset_map suniv_ccu_resets[] = अणु
	[RST_USB_PHY0]		=  अणु 0x0cc, BIT(0) पूर्ण,

	[RST_BUS_DMA]		=  अणु 0x2c0, BIT(6) पूर्ण,
	[RST_BUS_MMC0]		=  अणु 0x2c0, BIT(8) पूर्ण,
	[RST_BUS_MMC1]		=  अणु 0x2c0, BIT(9) पूर्ण,
	[RST_BUS_DRAM]		=  अणु 0x2c0, BIT(14) पूर्ण,
	[RST_BUS_SPI0]		=  अणु 0x2c0, BIT(20) पूर्ण,
	[RST_BUS_SPI1]		=  अणु 0x2c0, BIT(21) पूर्ण,
	[RST_BUS_OTG]		=  अणु 0x2c0, BIT(24) पूर्ण,
	[RST_BUS_VE]		=  अणु 0x2c4, BIT(0) पूर्ण,
	[RST_BUS_LCD]		=  अणु 0x2c4, BIT(4) पूर्ण,
	[RST_BUS_DEINTERLACE]	=  अणु 0x2c4, BIT(5) पूर्ण,
	[RST_BUS_CSI]		=  अणु 0x2c4, BIT(8) पूर्ण,
	[RST_BUS_TVD]		=  अणु 0x2c4, BIT(9) पूर्ण,
	[RST_BUS_TVE]		=  अणु 0x2c4, BIT(10) पूर्ण,
	[RST_BUS_DE_BE]		=  अणु 0x2c4, BIT(12) पूर्ण,
	[RST_BUS_DE_FE]		=  अणु 0x2c4, BIT(14) पूर्ण,
	[RST_BUS_CODEC]		=  अणु 0x2d0, BIT(0) पूर्ण,
	[RST_BUS_SPDIF]		=  अणु 0x2d0, BIT(1) पूर्ण,
	[RST_BUS_IR]		=  अणु 0x2d0, BIT(2) पूर्ण,
	[RST_BUS_RSB]		=  अणु 0x2d0, BIT(3) पूर्ण,
	[RST_BUS_I2S0]		=  अणु 0x2d0, BIT(12) पूर्ण,
	[RST_BUS_I2C0]		=  अणु 0x2d0, BIT(16) पूर्ण,
	[RST_BUS_I2C1]		=  अणु 0x2d0, BIT(17) पूर्ण,
	[RST_BUS_I2C2]		=  अणु 0x2d0, BIT(18) पूर्ण,
	[RST_BUS_UART0]		=  अणु 0x2d0, BIT(20) पूर्ण,
	[RST_BUS_UART1]		=  अणु 0x2d0, BIT(21) पूर्ण,
	[RST_BUS_UART2]		=  अणु 0x2d0, BIT(22) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc suniv_ccu_desc = अणु
	.ccu_clks	= suniv_ccu_clks,
	.num_ccu_clks	= ARRAY_SIZE(suniv_ccu_clks),

	.hw_clks	= &suniv_hw_clks,

	.resets		= suniv_ccu_resets,
	.num_resets	= ARRAY_SIZE(suniv_ccu_resets),
पूर्ण;

अटल काष्ठा ccu_pll_nb suniv_pll_cpu_nb = अणु
	.common	= &pll_cpu_clk.common,
	/* copy from pll_cpu_clk */
	.enable	= BIT(31),
	.lock	= BIT(28),
पूर्ण;

अटल काष्ठा ccu_mux_nb suniv_cpu_nb = अणु
	.common		= &cpu_clk.common,
	.cm		= &cpu_clk.mux,
	.delay_us	= 1, /* > 8 घड़ी cycles at 24 MHz */
	.bypass_index	= 1, /* index of 24 MHz oscillator */
पूर्ण;

अटल व्योम __init suniv_f1c100s_ccu_setup(काष्ठा device_node *node)
अणु
	व्योम __iomem *reg;
	u32 val;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg)) अणु
		pr_err("%pOF: Could not map the clock registers\n", node);
		वापस;
	पूर्ण

	/* Force the PLL-Audio-1x भागider to 4 */
	val = पढ़ोl(reg + SUNIV_PLL_AUDIO_REG);
	val &= ~GENMASK(19, 16);
	ग_लिखोl(val | (3 << 16), reg + SUNIV_PLL_AUDIO_REG);

	sunxi_ccu_probe(node, reg, &suniv_ccu_desc);

	/* Gate then ungate PLL CPU after any rate changes */
	ccu_pll_notअगरier_रेजिस्टर(&suniv_pll_cpu_nb);

	/* Reparent CPU during PLL CPU rate changes */
	ccu_mux_notअगरier_रेजिस्टर(pll_cpu_clk.common.hw.clk,
				  &suniv_cpu_nb);
पूर्ण
CLK_OF_DECLARE(suniv_f1c100s_ccu, "allwinner,suniv-f1c100s-ccu",
	       suniv_f1c100s_ccu_setup);
