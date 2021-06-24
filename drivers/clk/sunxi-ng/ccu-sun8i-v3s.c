<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 Icenowy Zheng <icenowy@aosc.xyz>
 *
 * Based on ccu-sun8i-h3.c, which is:
 * Copyright (c) 2016 Maxime Ripard. All rights reserved.
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

#समावेश "ccu-sun8i-v3s.h"

अटल SUNXI_CCU_NKMP_WITH_GATE_LOCK(pll_cpu_clk, "pll-cpu",
				     "osc24M", 0x000,
				     8, 5,	/* N */
				     4, 2,	/* K */
				     0, 2,	/* M */
				     16, 2,	/* P */
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
#घोषणा SUN8I_V3S_PLL_AUDIO_REG	0x008

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

अटल SUNXI_CCU_NM_WITH_FRAC_GATE_LOCK(pll_video_clk, "pll-video",
					"osc24M", 0x0010,
					8, 7,		/* N */
					0, 4,		/* M */
					BIT(24),	/* frac enable */
					BIT(25),	/* frac select */
					270000000,	/* frac rate 0 */
					297000000,	/* frac rate 1 */
					BIT(31),	/* gate */
					BIT(28),	/* lock */
					0);

अटल SUNXI_CCU_NM_WITH_FRAC_GATE_LOCK(pll_ve_clk, "pll-ve",
					"osc24M", 0x0018,
					8, 7,		/* N */
					0, 4,		/* M */
					BIT(24),	/* frac enable */
					BIT(25),	/* frac select */
					270000000,	/* frac rate 0 */
					297000000,	/* frac rate 1 */
					BIT(31),	/* gate */
					BIT(28),	/* lock */
					0);

अटल SUNXI_CCU_NKM_WITH_GATE_LOCK(pll_ddr0_clk, "pll-ddr0",
				    "osc24M", 0x020,
				    8, 5,	/* N */
				    4, 2,	/* K */
				    0, 2,	/* M */
				    BIT(31),	/* gate */
				    BIT(28),	/* lock */
				    0);

अटल SUNXI_CCU_NK_WITH_GATE_LOCK_POSTDIV(pll_periph0_clk, "pll-periph0",
					   "osc24M", 0x028,
					   8, 5,	/* N */
					   4, 2,	/* K */
					   BIT(31),	/* gate */
					   BIT(28),	/* lock */
					   2,		/* post-भाग */
					   0);

अटल SUNXI_CCU_NM_WITH_FRAC_GATE_LOCK(pll_isp_clk, "pll-isp",
					"osc24M", 0x002c,
					8, 7,		/* N */
					0, 4,		/* M */
					BIT(24),	/* frac enable */
					BIT(25),	/* frac select */
					270000000,	/* frac rate 0 */
					297000000,	/* frac rate 1 */
					BIT(31),	/* gate */
					BIT(28),	/* lock */
					0);

अटल SUNXI_CCU_NK_WITH_GATE_LOCK_POSTDIV(pll_periph1_clk, "pll-periph1",
					   "osc24M", 0x044,
					   8, 5,	/* N */
					   4, 2,	/* K */
					   BIT(31),	/* gate */
					   BIT(28),	/* lock */
					   2,		/* post-भाग */
					   0);

अटल SUNXI_CCU_NM_WITH_GATE_LOCK(pll_ddr1_clk, "pll-ddr1",
				   "osc24M", 0x04c,
				   8, 7,	/* N */
				   0, 2,	/* M */
				   BIT(31),	/* gate */
				   BIT(28),	/* lock */
				   0);

अटल स्थिर अक्षर * स्थिर cpu_parents[] = अणु "osc32k", "osc24M",
					     "pll-cpu", "pll-cpu" पूर्ण;
अटल SUNXI_CCU_MUX(cpu_clk, "cpu", cpu_parents,
		     0x050, 16, 2, CLK_IS_CRITICAL);

अटल SUNXI_CCU_M(axi_clk, "axi", "cpu", 0x050, 0, 2, 0);

अटल स्थिर अक्षर * स्थिर ahb1_parents[] = अणु "osc32k", "osc24M",
					     "axi", "pll-periph0" पूर्ण;
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
					     "pll-periph0", "pll-periph0" पूर्ण;
अटल SUNXI_CCU_MP_WITH_MUX(apb2_clk, "apb2", apb2_parents, 0x058,
			     0, 5,	/* M */
			     16, 2,	/* P */
			     24, 2,	/* mux */
			     0);

अटल स्थिर अक्षर * स्थिर ahb2_parents[] = अणु "ahb1", "pll-periph0" पूर्ण;
अटल स्थिर काष्ठा ccu_mux_fixed_preभाग ahb2_fixed_preभागs[] = अणु
	अणु .index = 1, .भाग = 2 पूर्ण,
पूर्ण;
अटल काष्ठा ccu_mux ahb2_clk = अणु
	.mux		= अणु
		.shअगरt	= 0,
		.width	= 1,
		.fixed_preभागs	= ahb2_fixed_preभागs,
		.n_preभागs	= ARRAY_SIZE(ahb2_fixed_preभागs),
	पूर्ण,

	.common		= अणु
		.reg		= 0x05c,
		.features	= CCU_FEATURE_FIXED_PREDIV,
		.hw.init	= CLK_HW_INIT_PARENTS("ahb2",
						      ahb2_parents,
						      &ccu_mux_ops,
						      0),
	पूर्ण,
पूर्ण;

अटल SUNXI_CCU_GATE(bus_ce_clk,	"bus-ce",	"ahb1",
		      0x060, BIT(5), 0);
अटल SUNXI_CCU_GATE(bus_dma_clk,	"bus-dma",	"ahb1",
		      0x060, BIT(6), 0);
अटल SUNXI_CCU_GATE(bus_mmc0_clk,	"bus-mmc0",	"ahb1",
		      0x060, BIT(8), 0);
अटल SUNXI_CCU_GATE(bus_mmc1_clk,	"bus-mmc1",	"ahb1",
		      0x060, BIT(9), 0);
अटल SUNXI_CCU_GATE(bus_mmc2_clk,	"bus-mmc2",	"ahb1",
		      0x060, BIT(10), 0);
अटल SUNXI_CCU_GATE(bus_dram_clk,	"bus-dram",	"ahb1",
		      0x060, BIT(14), 0);
अटल SUNXI_CCU_GATE(bus_emac_clk,	"bus-emac",	"ahb2",
		      0x060, BIT(17), 0);
अटल SUNXI_CCU_GATE(bus_hsसमयr_clk,	"bus-hstimer",	"ahb1",
		      0x060, BIT(19), 0);
अटल SUNXI_CCU_GATE(bus_spi0_clk,	"bus-spi0",	"ahb1",
		      0x060, BIT(20), 0);
अटल SUNXI_CCU_GATE(bus_otg_clk,	"bus-otg",	"ahb1",
		      0x060, BIT(24), 0);
अटल SUNXI_CCU_GATE(bus_ehci0_clk,	"bus-ehci0",	"ahb1",
		      0x060, BIT(26), 0);
अटल SUNXI_CCU_GATE(bus_ohci0_clk,	"bus-ohci0",	"ahb1",
		      0x060, BIT(29), 0);

अटल SUNXI_CCU_GATE(bus_ve_clk,	"bus-ve",	"ahb1",
		      0x064, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_tcon0_clk,	"bus-tcon0",	"ahb1",
		      0x064, BIT(4), 0);
अटल SUNXI_CCU_GATE(bus_csi_clk,	"bus-csi",	"ahb1",
		      0x064, BIT(8), 0);
अटल SUNXI_CCU_GATE(bus_de_clk,	"bus-de",	"ahb1",
		      0x064, BIT(12), 0);

अटल SUNXI_CCU_GATE(bus_codec_clk,	"bus-codec",	"apb1",
		      0x068, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_pio_clk,	"bus-pio",	"apb1",
		      0x068, BIT(5), 0);
अटल SUNXI_CCU_GATE(bus_i2s0_clk,	"bus-i2s0",	"apb1",
		      0x068, BIT(12), 0);

अटल SUNXI_CCU_GATE(bus_i2c0_clk,	"bus-i2c0",	"apb2",
		      0x06c, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_i2c1_clk,	"bus-i2c1",	"apb2",
		      0x06c, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_uart0_clk,	"bus-uart0",	"apb2",
		      0x06c, BIT(16), 0);
अटल SUNXI_CCU_GATE(bus_uart1_clk,	"bus-uart1",	"apb2",
		      0x06c, BIT(17), 0);
अटल SUNXI_CCU_GATE(bus_uart2_clk,	"bus-uart2",	"apb2",
		      0x06c, BIT(18), 0);

अटल SUNXI_CCU_GATE(bus_ephy_clk,	"bus-ephy",	"ahb1",
		      0x070, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_dbg_clk,	"bus-dbg",	"ahb1",
		      0x070, BIT(7), 0);

अटल स्थिर अक्षर * स्थिर mod0_शेष_parents[] = अणु "osc24M", "pll-periph0",
						     "pll-periph1" पूर्ण;
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

अटल SUNXI_CCU_MP_WITH_MUX_GATE(mmc2_clk, "mmc2", mod0_शेष_parents, 0x090,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

अटल SUNXI_CCU_PHASE(mmc2_sample_clk, "mmc2_sample", "mmc2",
		       0x090, 20, 3, 0);
अटल SUNXI_CCU_PHASE(mmc2_output_clk, "mmc2_output", "mmc2",
		       0x090, 8, 3, 0);

अटल स्थिर अक्षर * स्थिर ce_parents[] = अणु "osc24M", "pll-periph0", पूर्ण;

अटल SUNXI_CCU_MP_WITH_MUX_GATE(ce_clk, "ce", ce_parents, 0x09c,
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

अटल स्थिर अक्षर * स्थिर i2s_parents[] = अणु "pll-audio-8x", "pll-audio-4x",
					    "pll-audio-2x", "pll-audio" पूर्ण;
अटल SUNXI_CCU_MUX_WITH_GATE(i2s0_clk, "i2s0", i2s_parents,
			       0x0b0, 16, 2, BIT(31), CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_GATE(usb_phy0_clk,	"usb-phy0",	"osc24M",
		      0x0cc, BIT(8), 0);
अटल SUNXI_CCU_GATE(usb_ohci0_clk,	"usb-ohci0",	"osc24M",
		      0x0cc, BIT(16), 0);

अटल स्थिर अक्षर * स्थिर dram_parents[] = अणु "pll-ddr0", "pll-ddr1",
					     "pll-periph0-2x" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX(dram_clk, "dram", dram_parents,
			    0x0f4, 0, 4, 20, 2, CLK_IS_CRITICAL);

अटल SUNXI_CCU_GATE(dram_ve_clk,	"dram-ve",	"dram",
		      0x100, BIT(0), 0);
अटल SUNXI_CCU_GATE(dram_csi_clk,	"dram-csi",	"dram",
		      0x100, BIT(1), 0);
अटल SUNXI_CCU_GATE(dram_ehci_clk,	"dram-ehci",	"dram",
		      0x100, BIT(17), 0);
अटल SUNXI_CCU_GATE(dram_ohci_clk,	"dram-ohci",	"dram",
		      0x100, BIT(18), 0);

अटल स्थिर अक्षर * स्थिर de_parents[] = अणु "pll-video", "pll-periph0" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(de_clk, "de", de_parents,
				 0x104, 0, 4, 24, 2, BIT(31),
				 CLK_SET_RATE_PARENT);

अटल स्थिर अक्षर * स्थिर tcon_parents[] = अणु "pll-video" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(tcon_clk, "tcon", tcon_parents,
				 0x118, 0, 4, 24, 3, BIT(31), 0);

अटल SUNXI_CCU_GATE(csi_misc_clk,	"csi-misc",	"osc24M",
		      0x130, BIT(31), 0);

अटल स्थिर अक्षर * स्थिर csi_mclk_parents[] = अणु "osc24M", "pll-video",
						 "pll-periph0", "pll-periph1" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(csi0_mclk_clk, "csi0-mclk", csi_mclk_parents,
				 0x130, 0, 5, 8, 3, BIT(15), 0);

अटल स्थिर अक्षर * स्थिर csi1_sclk_parents[] = अणु "pll-video", "pll-isp" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(csi1_sclk_clk, "csi-sclk", csi1_sclk_parents,
				 0x134, 16, 4, 24, 3, BIT(31), 0);

अटल SUNXI_CCU_M_WITH_MUX_GATE(csi1_mclk_clk, "csi-mclk", csi_mclk_parents,
				 0x134, 0, 5, 8, 3, BIT(15), 0);

अटल SUNXI_CCU_M_WITH_GATE(ve_clk, "ve", "pll-ve",
			     0x13c, 16, 3, BIT(31), 0);

अटल SUNXI_CCU_GATE(ac_dig_clk,	"ac-dig",	"pll-audio",
		      0x140, BIT(31), CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_GATE(avs_clk,		"avs",		"osc24M",
		      0x144, BIT(31), 0);

अटल स्थिर अक्षर * स्थिर mbus_parents[] = अणु "osc24M", "pll-periph0-2x",
					     "pll-ddr" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(mbus_clk, "mbus", mbus_parents,
				 0x15c, 0, 3, 24, 2, BIT(31), CLK_IS_CRITICAL);

अटल स्थिर अक्षर * स्थिर mipi_csi_parents[] = अणु "pll-video", "pll-periph0",
						 "pll-isp" पूर्ण;
अटल SUNXI_CCU_M_WITH_MUX_GATE(mipi_csi_clk, "mipi-csi", mipi_csi_parents,
			     0x16c, 0, 3, 24, 2, BIT(31), 0);

अटल काष्ठा ccu_common *sun8i_v3s_ccu_clks[] = अणु
	&pll_cpu_clk.common,
	&pll_audio_base_clk.common,
	&pll_video_clk.common,
	&pll_ve_clk.common,
	&pll_ddr0_clk.common,
	&pll_periph0_clk.common,
	&pll_isp_clk.common,
	&pll_periph1_clk.common,
	&pll_ddr1_clk.common,
	&cpu_clk.common,
	&axi_clk.common,
	&ahb1_clk.common,
	&apb1_clk.common,
	&apb2_clk.common,
	&ahb2_clk.common,
	&bus_ce_clk.common,
	&bus_dma_clk.common,
	&bus_mmc0_clk.common,
	&bus_mmc1_clk.common,
	&bus_mmc2_clk.common,
	&bus_dram_clk.common,
	&bus_emac_clk.common,
	&bus_hsसमयr_clk.common,
	&bus_spi0_clk.common,
	&bus_otg_clk.common,
	&bus_ehci0_clk.common,
	&bus_ohci0_clk.common,
	&bus_ve_clk.common,
	&bus_tcon0_clk.common,
	&bus_csi_clk.common,
	&bus_de_clk.common,
	&bus_codec_clk.common,
	&bus_pio_clk.common,
	&bus_i2c0_clk.common,
	&bus_i2c1_clk.common,
	&bus_uart0_clk.common,
	&bus_uart1_clk.common,
	&bus_uart2_clk.common,
	&bus_ephy_clk.common,
	&bus_dbg_clk.common,
	&mmc0_clk.common,
	&mmc0_sample_clk.common,
	&mmc0_output_clk.common,
	&mmc1_clk.common,
	&mmc1_sample_clk.common,
	&mmc1_output_clk.common,
	&mmc2_clk.common,
	&mmc2_sample_clk.common,
	&mmc2_output_clk.common,
	&ce_clk.common,
	&spi0_clk.common,
	&usb_phy0_clk.common,
	&usb_ohci0_clk.common,
	&dram_clk.common,
	&dram_ve_clk.common,
	&dram_csi_clk.common,
	&dram_ohci_clk.common,
	&dram_ehci_clk.common,
	&de_clk.common,
	&tcon_clk.common,
	&csi_misc_clk.common,
	&csi0_mclk_clk.common,
	&csi1_sclk_clk.common,
	&csi1_mclk_clk.common,
	&ve_clk.common,
	&ac_dig_clk.common,
	&avs_clk.common,
	&mbus_clk.common,
	&mipi_csi_clk.common,
पूर्ण;

अटल स्थिर काष्ठा clk_hw *clk_parent_pll_audio[] = अणु
	&pll_audio_base_clk.common.hw
पूर्ण;

अटल काष्ठा ccu_common *sun8i_v3_ccu_clks[] = अणु
	&pll_cpu_clk.common,
	&pll_audio_base_clk.common,
	&pll_video_clk.common,
	&pll_ve_clk.common,
	&pll_ddr0_clk.common,
	&pll_periph0_clk.common,
	&pll_isp_clk.common,
	&pll_periph1_clk.common,
	&pll_ddr1_clk.common,
	&cpu_clk.common,
	&axi_clk.common,
	&ahb1_clk.common,
	&apb1_clk.common,
	&apb2_clk.common,
	&ahb2_clk.common,
	&bus_ce_clk.common,
	&bus_dma_clk.common,
	&bus_mmc0_clk.common,
	&bus_mmc1_clk.common,
	&bus_mmc2_clk.common,
	&bus_dram_clk.common,
	&bus_emac_clk.common,
	&bus_hsसमयr_clk.common,
	&bus_spi0_clk.common,
	&bus_otg_clk.common,
	&bus_ehci0_clk.common,
	&bus_ohci0_clk.common,
	&bus_ve_clk.common,
	&bus_tcon0_clk.common,
	&bus_csi_clk.common,
	&bus_de_clk.common,
	&bus_codec_clk.common,
	&bus_pio_clk.common,
	&bus_i2s0_clk.common,
	&bus_i2c0_clk.common,
	&bus_i2c1_clk.common,
	&bus_uart0_clk.common,
	&bus_uart1_clk.common,
	&bus_uart2_clk.common,
	&bus_ephy_clk.common,
	&bus_dbg_clk.common,
	&mmc0_clk.common,
	&mmc0_sample_clk.common,
	&mmc0_output_clk.common,
	&mmc1_clk.common,
	&mmc1_sample_clk.common,
	&mmc1_output_clk.common,
	&mmc2_clk.common,
	&mmc2_sample_clk.common,
	&mmc2_output_clk.common,
	&ce_clk.common,
	&spi0_clk.common,
	&i2s0_clk.common,
	&usb_phy0_clk.common,
	&usb_ohci0_clk.common,
	&dram_clk.common,
	&dram_ve_clk.common,
	&dram_csi_clk.common,
	&dram_ohci_clk.common,
	&dram_ehci_clk.common,
	&de_clk.common,
	&tcon_clk.common,
	&csi_misc_clk.common,
	&csi0_mclk_clk.common,
	&csi1_sclk_clk.common,
	&csi1_mclk_clk.common,
	&ve_clk.common,
	&ac_dig_clk.common,
	&avs_clk.common,
	&mbus_clk.common,
	&mipi_csi_clk.common,
पूर्ण;

/* We hardcode the भागider to 1 क्रम SDM support */
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
अटल CLK_FIXED_FACTOR_HW(pll_periph0_2x_clk, "pll-periph0-2x",
			   &pll_periph0_clk.common.hw,
			   1, 2, 0);

अटल काष्ठा clk_hw_onecell_data sun8i_v3s_hw_clks = अणु
	.hws	= अणु
		[CLK_PLL_CPU]		= &pll_cpu_clk.common.hw,
		[CLK_PLL_AUDIO_BASE]	= &pll_audio_base_clk.common.hw,
		[CLK_PLL_AUDIO]		= &pll_audio_clk.hw,
		[CLK_PLL_AUDIO_2X]	= &pll_audio_2x_clk.hw,
		[CLK_PLL_AUDIO_4X]	= &pll_audio_4x_clk.hw,
		[CLK_PLL_AUDIO_8X]	= &pll_audio_8x_clk.hw,
		[CLK_PLL_VIDEO]		= &pll_video_clk.common.hw,
		[CLK_PLL_VE]		= &pll_ve_clk.common.hw,
		[CLK_PLL_DDR0]		= &pll_ddr0_clk.common.hw,
		[CLK_PLL_PERIPH0]	= &pll_periph0_clk.common.hw,
		[CLK_PLL_PERIPH0_2X]	= &pll_periph0_2x_clk.hw,
		[CLK_PLL_ISP]		= &pll_isp_clk.common.hw,
		[CLK_PLL_PERIPH1]	= &pll_periph1_clk.common.hw,
		[CLK_PLL_DDR1]		= &pll_ddr1_clk.common.hw,
		[CLK_CPU]		= &cpu_clk.common.hw,
		[CLK_AXI]		= &axi_clk.common.hw,
		[CLK_AHB1]		= &ahb1_clk.common.hw,
		[CLK_APB1]		= &apb1_clk.common.hw,
		[CLK_APB2]		= &apb2_clk.common.hw,
		[CLK_AHB2]		= &ahb2_clk.common.hw,
		[CLK_BUS_CE]		= &bus_ce_clk.common.hw,
		[CLK_BUS_DMA]		= &bus_dma_clk.common.hw,
		[CLK_BUS_MMC0]		= &bus_mmc0_clk.common.hw,
		[CLK_BUS_MMC1]		= &bus_mmc1_clk.common.hw,
		[CLK_BUS_MMC2]		= &bus_mmc2_clk.common.hw,
		[CLK_BUS_DRAM]		= &bus_dram_clk.common.hw,
		[CLK_BUS_EMAC]		= &bus_emac_clk.common.hw,
		[CLK_BUS_HSTIMER]	= &bus_hsसमयr_clk.common.hw,
		[CLK_BUS_SPI0]		= &bus_spi0_clk.common.hw,
		[CLK_BUS_OTG]		= &bus_otg_clk.common.hw,
		[CLK_BUS_EHCI0]		= &bus_ehci0_clk.common.hw,
		[CLK_BUS_OHCI0]		= &bus_ohci0_clk.common.hw,
		[CLK_BUS_VE]		= &bus_ve_clk.common.hw,
		[CLK_BUS_TCON0]		= &bus_tcon0_clk.common.hw,
		[CLK_BUS_CSI]		= &bus_csi_clk.common.hw,
		[CLK_BUS_DE]		= &bus_de_clk.common.hw,
		[CLK_BUS_CODEC]		= &bus_codec_clk.common.hw,
		[CLK_BUS_PIO]		= &bus_pio_clk.common.hw,
		[CLK_BUS_I2C0]		= &bus_i2c0_clk.common.hw,
		[CLK_BUS_I2C1]		= &bus_i2c1_clk.common.hw,
		[CLK_BUS_UART0]		= &bus_uart0_clk.common.hw,
		[CLK_BUS_UART1]		= &bus_uart1_clk.common.hw,
		[CLK_BUS_UART2]		= &bus_uart2_clk.common.hw,
		[CLK_BUS_EPHY]		= &bus_ephy_clk.common.hw,
		[CLK_BUS_DBG]		= &bus_dbg_clk.common.hw,
		[CLK_MMC0]		= &mmc0_clk.common.hw,
		[CLK_MMC0_SAMPLE]	= &mmc0_sample_clk.common.hw,
		[CLK_MMC0_OUTPUT]	= &mmc0_output_clk.common.hw,
		[CLK_MMC1]		= &mmc1_clk.common.hw,
		[CLK_MMC1_SAMPLE]	= &mmc1_sample_clk.common.hw,
		[CLK_MMC1_OUTPUT]	= &mmc1_output_clk.common.hw,
		[CLK_MMC2]		= &mmc2_clk.common.hw,
		[CLK_MMC2_SAMPLE]	= &mmc2_sample_clk.common.hw,
		[CLK_MMC2_OUTPUT]	= &mmc2_output_clk.common.hw,
		[CLK_CE]		= &ce_clk.common.hw,
		[CLK_SPI0]		= &spi0_clk.common.hw,
		[CLK_USB_PHY0]		= &usb_phy0_clk.common.hw,
		[CLK_USB_OHCI0]		= &usb_ohci0_clk.common.hw,
		[CLK_DRAM]		= &dram_clk.common.hw,
		[CLK_DRAM_VE]		= &dram_ve_clk.common.hw,
		[CLK_DRAM_CSI]		= &dram_csi_clk.common.hw,
		[CLK_DRAM_EHCI]		= &dram_ehci_clk.common.hw,
		[CLK_DRAM_OHCI]		= &dram_ohci_clk.common.hw,
		[CLK_DE]		= &de_clk.common.hw,
		[CLK_TCON0]		= &tcon_clk.common.hw,
		[CLK_CSI_MISC]		= &csi_misc_clk.common.hw,
		[CLK_CSI0_MCLK]		= &csi0_mclk_clk.common.hw,
		[CLK_CSI1_SCLK]		= &csi1_sclk_clk.common.hw,
		[CLK_CSI1_MCLK]		= &csi1_mclk_clk.common.hw,
		[CLK_VE]		= &ve_clk.common.hw,
		[CLK_AC_DIG]		= &ac_dig_clk.common.hw,
		[CLK_AVS]		= &avs_clk.common.hw,
		[CLK_MBUS]		= &mbus_clk.common.hw,
		[CLK_MIPI_CSI]		= &mipi_csi_clk.common.hw,
	पूर्ण,
	.num	= CLK_PLL_DDR1 + 1,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sun8i_v3_hw_clks = अणु
	.hws	= अणु
		[CLK_PLL_CPU]		= &pll_cpu_clk.common.hw,
		[CLK_PLL_AUDIO_BASE]	= &pll_audio_base_clk.common.hw,
		[CLK_PLL_AUDIO]		= &pll_audio_clk.hw,
		[CLK_PLL_AUDIO_2X]	= &pll_audio_2x_clk.hw,
		[CLK_PLL_AUDIO_4X]	= &pll_audio_4x_clk.hw,
		[CLK_PLL_AUDIO_8X]	= &pll_audio_8x_clk.hw,
		[CLK_PLL_VIDEO]		= &pll_video_clk.common.hw,
		[CLK_PLL_VE]		= &pll_ve_clk.common.hw,
		[CLK_PLL_DDR0]		= &pll_ddr0_clk.common.hw,
		[CLK_PLL_PERIPH0]	= &pll_periph0_clk.common.hw,
		[CLK_PLL_PERIPH0_2X]	= &pll_periph0_2x_clk.hw,
		[CLK_PLL_ISP]		= &pll_isp_clk.common.hw,
		[CLK_PLL_PERIPH1]	= &pll_periph1_clk.common.hw,
		[CLK_PLL_DDR1]		= &pll_ddr1_clk.common.hw,
		[CLK_CPU]		= &cpu_clk.common.hw,
		[CLK_AXI]		= &axi_clk.common.hw,
		[CLK_AHB1]		= &ahb1_clk.common.hw,
		[CLK_APB1]		= &apb1_clk.common.hw,
		[CLK_APB2]		= &apb2_clk.common.hw,
		[CLK_AHB2]		= &ahb2_clk.common.hw,
		[CLK_BUS_CE]		= &bus_ce_clk.common.hw,
		[CLK_BUS_DMA]		= &bus_dma_clk.common.hw,
		[CLK_BUS_MMC0]		= &bus_mmc0_clk.common.hw,
		[CLK_BUS_MMC1]		= &bus_mmc1_clk.common.hw,
		[CLK_BUS_MMC2]		= &bus_mmc2_clk.common.hw,
		[CLK_BUS_DRAM]		= &bus_dram_clk.common.hw,
		[CLK_BUS_EMAC]		= &bus_emac_clk.common.hw,
		[CLK_BUS_HSTIMER]	= &bus_hsसमयr_clk.common.hw,
		[CLK_BUS_SPI0]		= &bus_spi0_clk.common.hw,
		[CLK_BUS_OTG]		= &bus_otg_clk.common.hw,
		[CLK_BUS_EHCI0]		= &bus_ehci0_clk.common.hw,
		[CLK_BUS_OHCI0]		= &bus_ohci0_clk.common.hw,
		[CLK_BUS_VE]		= &bus_ve_clk.common.hw,
		[CLK_BUS_TCON0]		= &bus_tcon0_clk.common.hw,
		[CLK_BUS_CSI]		= &bus_csi_clk.common.hw,
		[CLK_BUS_DE]		= &bus_de_clk.common.hw,
		[CLK_BUS_CODEC]		= &bus_codec_clk.common.hw,
		[CLK_BUS_PIO]		= &bus_pio_clk.common.hw,
		[CLK_BUS_I2S0]		= &bus_i2s0_clk.common.hw,
		[CLK_BUS_I2C0]		= &bus_i2c0_clk.common.hw,
		[CLK_BUS_I2C1]		= &bus_i2c1_clk.common.hw,
		[CLK_BUS_UART0]		= &bus_uart0_clk.common.hw,
		[CLK_BUS_UART1]		= &bus_uart1_clk.common.hw,
		[CLK_BUS_UART2]		= &bus_uart2_clk.common.hw,
		[CLK_BUS_EPHY]		= &bus_ephy_clk.common.hw,
		[CLK_BUS_DBG]		= &bus_dbg_clk.common.hw,
		[CLK_MMC0]		= &mmc0_clk.common.hw,
		[CLK_MMC0_SAMPLE]	= &mmc0_sample_clk.common.hw,
		[CLK_MMC0_OUTPUT]	= &mmc0_output_clk.common.hw,
		[CLK_MMC1]		= &mmc1_clk.common.hw,
		[CLK_MMC1_SAMPLE]	= &mmc1_sample_clk.common.hw,
		[CLK_MMC1_OUTPUT]	= &mmc1_output_clk.common.hw,
		[CLK_MMC2]		= &mmc2_clk.common.hw,
		[CLK_MMC2_SAMPLE]	= &mmc2_sample_clk.common.hw,
		[CLK_MMC2_OUTPUT]	= &mmc2_output_clk.common.hw,
		[CLK_CE]		= &ce_clk.common.hw,
		[CLK_SPI0]		= &spi0_clk.common.hw,
		[CLK_I2S0]		= &i2s0_clk.common.hw,
		[CLK_USB_PHY0]		= &usb_phy0_clk.common.hw,
		[CLK_USB_OHCI0]		= &usb_ohci0_clk.common.hw,
		[CLK_DRAM]		= &dram_clk.common.hw,
		[CLK_DRAM_VE]		= &dram_ve_clk.common.hw,
		[CLK_DRAM_CSI]		= &dram_csi_clk.common.hw,
		[CLK_DRAM_EHCI]		= &dram_ehci_clk.common.hw,
		[CLK_DRAM_OHCI]		= &dram_ohci_clk.common.hw,
		[CLK_DE]		= &de_clk.common.hw,
		[CLK_TCON0]		= &tcon_clk.common.hw,
		[CLK_CSI_MISC]		= &csi_misc_clk.common.hw,
		[CLK_CSI0_MCLK]		= &csi0_mclk_clk.common.hw,
		[CLK_CSI1_SCLK]		= &csi1_sclk_clk.common.hw,
		[CLK_CSI1_MCLK]		= &csi1_mclk_clk.common.hw,
		[CLK_VE]		= &ve_clk.common.hw,
		[CLK_AC_DIG]		= &ac_dig_clk.common.hw,
		[CLK_AVS]		= &avs_clk.common.hw,
		[CLK_MBUS]		= &mbus_clk.common.hw,
		[CLK_MIPI_CSI]		= &mipi_csi_clk.common.hw,
	पूर्ण,
	.num	= CLK_I2S0 + 1,
पूर्ण;

अटल काष्ठा ccu_reset_map sun8i_v3s_ccu_resets[] = अणु
	[RST_USB_PHY0]		=  अणु 0x0cc, BIT(0) पूर्ण,

	[RST_MBUS]		=  अणु 0x0fc, BIT(31) पूर्ण,

	[RST_BUS_CE]		=  अणु 0x2c0, BIT(5) पूर्ण,
	[RST_BUS_DMA]		=  अणु 0x2c0, BIT(6) पूर्ण,
	[RST_BUS_MMC0]		=  अणु 0x2c0, BIT(8) पूर्ण,
	[RST_BUS_MMC1]		=  अणु 0x2c0, BIT(9) पूर्ण,
	[RST_BUS_MMC2]		=  अणु 0x2c0, BIT(10) पूर्ण,
	[RST_BUS_DRAM]		=  अणु 0x2c0, BIT(14) पूर्ण,
	[RST_BUS_EMAC]		=  अणु 0x2c0, BIT(17) पूर्ण,
	[RST_BUS_HSTIMER]	=  अणु 0x2c0, BIT(19) पूर्ण,
	[RST_BUS_SPI0]		=  अणु 0x2c0, BIT(20) पूर्ण,
	[RST_BUS_OTG]		=  अणु 0x2c0, BIT(24) पूर्ण,
	[RST_BUS_EHCI0]		=  अणु 0x2c0, BIT(26) पूर्ण,
	[RST_BUS_OHCI0]		=  अणु 0x2c0, BIT(29) पूर्ण,

	[RST_BUS_VE]		=  अणु 0x2c4, BIT(0) पूर्ण,
	[RST_BUS_TCON0]		=  अणु 0x2c4, BIT(4) पूर्ण,
	[RST_BUS_CSI]		=  अणु 0x2c4, BIT(8) पूर्ण,
	[RST_BUS_DE]		=  अणु 0x2c4, BIT(12) पूर्ण,
	[RST_BUS_DBG]		=  अणु 0x2c4, BIT(31) पूर्ण,

	[RST_BUS_EPHY]		=  अणु 0x2c8, BIT(2) पूर्ण,

	[RST_BUS_CODEC]		=  अणु 0x2d0, BIT(0) पूर्ण,

	[RST_BUS_I2C0]		=  अणु 0x2d8, BIT(0) पूर्ण,
	[RST_BUS_I2C1]		=  अणु 0x2d8, BIT(1) पूर्ण,
	[RST_BUS_UART0]		=  अणु 0x2d8, BIT(16) पूर्ण,
	[RST_BUS_UART1]		=  अणु 0x2d8, BIT(17) पूर्ण,
	[RST_BUS_UART2]		=  अणु 0x2d8, BIT(18) पूर्ण,
पूर्ण;

अटल काष्ठा ccu_reset_map sun8i_v3_ccu_resets[] = अणु
	[RST_USB_PHY0]		=  अणु 0x0cc, BIT(0) पूर्ण,

	[RST_MBUS]		=  अणु 0x0fc, BIT(31) पूर्ण,

	[RST_BUS_CE]		=  अणु 0x2c0, BIT(5) पूर्ण,
	[RST_BUS_DMA]		=  अणु 0x2c0, BIT(6) पूर्ण,
	[RST_BUS_MMC0]		=  अणु 0x2c0, BIT(8) पूर्ण,
	[RST_BUS_MMC1]		=  अणु 0x2c0, BIT(9) पूर्ण,
	[RST_BUS_MMC2]		=  अणु 0x2c0, BIT(10) पूर्ण,
	[RST_BUS_DRAM]		=  अणु 0x2c0, BIT(14) पूर्ण,
	[RST_BUS_EMAC]		=  अणु 0x2c0, BIT(17) पूर्ण,
	[RST_BUS_HSTIMER]	=  अणु 0x2c0, BIT(19) पूर्ण,
	[RST_BUS_SPI0]		=  अणु 0x2c0, BIT(20) पूर्ण,
	[RST_BUS_OTG]		=  अणु 0x2c0, BIT(24) पूर्ण,
	[RST_BUS_EHCI0]		=  अणु 0x2c0, BIT(26) पूर्ण,
	[RST_BUS_OHCI0]		=  अणु 0x2c0, BIT(29) पूर्ण,

	[RST_BUS_VE]		=  अणु 0x2c4, BIT(0) पूर्ण,
	[RST_BUS_TCON0]		=  अणु 0x2c4, BIT(4) पूर्ण,
	[RST_BUS_CSI]		=  अणु 0x2c4, BIT(8) पूर्ण,
	[RST_BUS_DE]		=  अणु 0x2c4, BIT(12) पूर्ण,
	[RST_BUS_DBG]		=  अणु 0x2c4, BIT(31) पूर्ण,

	[RST_BUS_EPHY]		=  अणु 0x2c8, BIT(2) पूर्ण,

	[RST_BUS_CODEC]		=  अणु 0x2d0, BIT(0) पूर्ण,
	[RST_BUS_I2S0]		=  अणु 0x2d0, BIT(12) पूर्ण,

	[RST_BUS_I2C0]		=  अणु 0x2d8, BIT(0) पूर्ण,
	[RST_BUS_I2C1]		=  अणु 0x2d8, BIT(1) पूर्ण,
	[RST_BUS_UART0]		=  अणु 0x2d8, BIT(16) पूर्ण,
	[RST_BUS_UART1]		=  अणु 0x2d8, BIT(17) पूर्ण,
	[RST_BUS_UART2]		=  अणु 0x2d8, BIT(18) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun8i_v3s_ccu_desc = अणु
	.ccu_clks	= sun8i_v3s_ccu_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun8i_v3s_ccu_clks),

	.hw_clks	= &sun8i_v3s_hw_clks,

	.resets		= sun8i_v3s_ccu_resets,
	.num_resets	= ARRAY_SIZE(sun8i_v3s_ccu_resets),
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun8i_v3_ccu_desc = अणु
	.ccu_clks	= sun8i_v3_ccu_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun8i_v3_ccu_clks),

	.hw_clks	= &sun8i_v3_hw_clks,

	.resets		= sun8i_v3_ccu_resets,
	.num_resets	= ARRAY_SIZE(sun8i_v3_ccu_resets),
पूर्ण;

अटल व्योम __init sun8i_v3_v3s_ccu_init(काष्ठा device_node *node,
					 स्थिर काष्ठा sunxi_ccu_desc *ccu_desc)
अणु
	व्योम __iomem *reg;
	u32 val;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg)) अणु
		pr_err("%pOF: Could not map the clock registers\n", node);
		वापस;
	पूर्ण

	/* Force the PLL-Audio-1x भागider to 4 */
	val = पढ़ोl(reg + SUN8I_V3S_PLL_AUDIO_REG);
	val &= ~GENMASK(19, 16);
	ग_लिखोl(val | (3 << 16), reg + SUN8I_V3S_PLL_AUDIO_REG);

	sunxi_ccu_probe(node, reg, ccu_desc);
पूर्ण

अटल व्योम __init sun8i_v3s_ccu_setup(काष्ठा device_node *node)
अणु
	sun8i_v3_v3s_ccu_init(node, &sun8i_v3s_ccu_desc);
पूर्ण

अटल व्योम __init sun8i_v3_ccu_setup(काष्ठा device_node *node)
अणु
	sun8i_v3_v3s_ccu_init(node, &sun8i_v3_ccu_desc);
पूर्ण

CLK_OF_DECLARE(sun8i_v3s_ccu, "allwinner,sun8i-v3s-ccu",
	       sun8i_v3s_ccu_setup);

CLK_OF_DECLARE(sun8i_v3_ccu, "allwinner,sun8i-v3-ccu",
	       sun8i_v3_ccu_setup);
