<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 Intel Corporation.
 * Zhu YiXin <yixin.zhu@पूर्णांकel.com>
 * Rahul Tanwar <rahul.tanwar@पूर्णांकel.com>
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <dt-bindings/घड़ी/पूर्णांकel,lgm-clk.h>
#समावेश "clk-cgu.h"

#घोषणा PLL_DIV_WIDTH		4
#घोषणा PLL_DDIV_WIDTH		3

/* Gate0 घड़ी shअगरt */
#घोषणा G_C55_SHIFT		7
#घोषणा G_QSPI_SHIFT		9
#घोषणा G_EIP197_SHIFT		11
#घोषणा G_VAULT130_SHIFT	12
#घोषणा G_TOE_SHIFT		13
#घोषणा G_SDXC_SHIFT		14
#घोषणा G_EMMC_SHIFT		15
#घोषणा G_SPIDBG_SHIFT		17
#घोषणा G_DMA3_SHIFT		28

/* Gate1 घड़ी shअगरt */
#घोषणा G_DMA0_SHIFT		0
#घोषणा G_LEDC0_SHIFT		1
#घोषणा G_LEDC1_SHIFT		2
#घोषणा G_I2S0_SHIFT		3
#घोषणा G_I2S1_SHIFT		4
#घोषणा G_EBU_SHIFT		5
#घोषणा G_PWM_SHIFT		6
#घोषणा G_I2C0_SHIFT		7
#घोषणा G_I2C1_SHIFT		8
#घोषणा G_I2C2_SHIFT		9
#घोषणा G_I2C3_SHIFT		10

#घोषणा G_SSC0_SHIFT		12
#घोषणा G_SSC1_SHIFT		13
#घोषणा G_SSC2_SHIFT		14
#घोषणा G_SSC3_SHIFT		15

#घोषणा G_GPTC0_SHIFT		17
#घोषणा G_GPTC1_SHIFT		18
#घोषणा G_GPTC2_SHIFT		19
#घोषणा G_GPTC3_SHIFT		20

#घोषणा G_ASC0_SHIFT		22
#घोषणा G_ASC1_SHIFT		23
#घोषणा G_ASC2_SHIFT		24
#घोषणा G_ASC3_SHIFT		25

#घोषणा G_PCM0_SHIFT		27
#घोषणा G_PCM1_SHIFT		28
#घोषणा G_PCM2_SHIFT		29

/* Gate2 घड़ी shअगरt */
#घोषणा G_PCIE10_SHIFT		1
#घोषणा G_PCIE11_SHIFT		2
#घोषणा G_PCIE30_SHIFT		3
#घोषणा G_PCIE31_SHIFT		4
#घोषणा G_PCIE20_SHIFT		5
#घोषणा G_PCIE21_SHIFT		6
#घोषणा G_PCIE40_SHIFT		7
#घोषणा G_PCIE41_SHIFT		8

#घोषणा G_XPCS0_SHIFT		10
#घोषणा G_XPCS1_SHIFT		11
#घोषणा G_XPCS2_SHIFT		12
#घोषणा G_XPCS3_SHIFT		13
#घोषणा G_SATA0_SHIFT		14
#घोषणा G_SATA1_SHIFT		15
#घोषणा G_SATA2_SHIFT		16
#घोषणा G_SATA3_SHIFT		17

/* Gate3 घड़ी shअगरt */
#घोषणा G_ARCEM4_SHIFT		0
#घोषणा G_IDMAR1_SHIFT		2
#घोषणा G_IDMAT0_SHIFT		3
#घोषणा G_IDMAT1_SHIFT		4
#घोषणा G_IDMAT2_SHIFT		5

#घोषणा G_PPV4_SHIFT		8
#घोषणा G_GSWIPO_SHIFT		9
#घोषणा G_CQEM_SHIFT		10
#घोषणा G_XPCS5_SHIFT		14
#घोषणा G_USB1_SHIFT		25
#घोषणा G_USB2_SHIFT		26


/* Register definition */
#घोषणा CGU_PLL0CZ_CFG0		0x000
#घोषणा CGU_PLL0CM0_CFG0	0x020
#घोषणा CGU_PLL0CM1_CFG0	0x040
#घोषणा CGU_PLL0B_CFG0		0x060
#घोषणा CGU_PLL1_CFG0		0x080
#घोषणा CGU_PLL2_CFG0		0x0A0
#घोषणा CGU_PLLPP_CFG0		0x0C0
#घोषणा CGU_LJPLL3_CFG0		0x0E0
#घोषणा CGU_LJPLL4_CFG0		0x100
#घोषणा CGU_C55_PCMCR		0x18C
#घोषणा CGU_PCMCR		0x190
#घोषणा CGU_IF_CLK1		0x1A0
#घोषणा CGU_IF_CLK2		0x1A4
#घोषणा CGU_GATE0		0x300
#घोषणा CGU_GATE1		0x310
#घोषणा CGU_GATE2		0x320
#घोषणा CGU_GATE3		0x310

#घोषणा PLL_DIV(x)		((x) + 0x04)
#घोषणा PLL_SSC(x)		((x) + 0x10)

#घोषणा CLK_NR_CLKS		(LGM_GCLK_USB2 + 1)

/*
 * Below table defines the pair's of regval & effective भागiders.
 * It's more efficient to provide an explicit table due to non-linear
 * relation between values.
 */
अटल स्थिर काष्ठा clk_भाग_प्रकारable pll_भाग[] = अणु
	अणु .val = 0, .भाग = 1 पूर्ण,
	अणु .val = 1, .भाग = 2 पूर्ण,
	अणु .val = 2, .भाग = 3 पूर्ण,
	अणु .val = 3, .भाग = 4 पूर्ण,
	अणु .val = 4, .भाग = 5 पूर्ण,
	अणु .val = 5, .भाग = 6 पूर्ण,
	अणु .val = 6, .भाग = 8 पूर्ण,
	अणु .val = 7, .भाग = 10 पूर्ण,
	अणु .val = 8, .भाग = 12 पूर्ण,
	अणु .val = 9, .भाग = 16 पूर्ण,
	अणु .val = 10, .भाग = 20 पूर्ण,
	अणु .val = 11, .भाग = 24 पूर्ण,
	अणु .val = 12, .भाग = 32 पूर्ण,
	अणु .val = 13, .भाग = 40 पूर्ण,
	अणु .val = 14, .भाग = 48 पूर्ण,
	अणु .val = 15, .भाग = 64 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable dcl_भाग[] = अणु
	अणु .val = 0, .भाग = 6  पूर्ण,
	अणु .val = 1, .भाग = 12 पूर्ण,
	अणु .val = 2, .भाग = 24 पूर्ण,
	अणु .val = 3, .भाग = 32 पूर्ण,
	अणु .val = 4, .भाग = 48 पूर्ण,
	अणु .val = 5, .भाग = 96 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data pll_p[] = अणु
	अणु .fw_name = "osc", .name = "osc" पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा clk_parent_data pllcm_p[] = अणु
	अणु .fw_name = "cpu_cm", .name = "cpu_cm" पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा clk_parent_data emmc_p[] = अणु
	अणु .fw_name = "emmc4", .name = "emmc4" पूर्ण,
	अणु .fw_name = "noc4", .name = "noc4" पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा clk_parent_data sdxc_p[] = अणु
	अणु .fw_name = "sdxc3", .name = "sdxc3" पूर्ण,
	अणु .fw_name = "sdxc2", .name = "sdxc2" पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा clk_parent_data pcm_p[] = अणु
	अणु .fw_name = "v_docsis", .name = "v_docsis" पूर्ण,
	अणु .fw_name = "dcl", .name = "dcl" पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा clk_parent_data cbphy_p[] = अणु
	अणु .fw_name = "dd_serdes", .name = "dd_serdes" पूर्ण,
	अणु .fw_name = "dd_pcie", .name = "dd_pcie" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा lgm_pll_clk_data lgm_pll_clks[] = अणु
	LGM_PLL(LGM_CLK_PLL0CZ, "pll0cz", pll_p, CLK_IGNORE_UNUSED,
		CGU_PLL0CZ_CFG0, TYPE_ROPLL),
	LGM_PLL(LGM_CLK_PLL0CM0, "pll0cm0", pllcm_p, CLK_IGNORE_UNUSED,
		CGU_PLL0CM0_CFG0, TYPE_ROPLL),
	LGM_PLL(LGM_CLK_PLL0CM1, "pll0cm1", pllcm_p, CLK_IGNORE_UNUSED,
		CGU_PLL0CM1_CFG0, TYPE_ROPLL),
	LGM_PLL(LGM_CLK_PLL0B, "pll0b", pll_p, CLK_IGNORE_UNUSED,
		CGU_PLL0B_CFG0, TYPE_ROPLL),
	LGM_PLL(LGM_CLK_PLL1, "pll1", pll_p, 0, CGU_PLL1_CFG0, TYPE_ROPLL),
	LGM_PLL(LGM_CLK_PLL2, "pll2", pll_p, CLK_IGNORE_UNUSED,
		CGU_PLL2_CFG0, TYPE_ROPLL),
	LGM_PLL(LGM_CLK_PLLPP, "pllpp", pll_p, 0, CGU_PLLPP_CFG0, TYPE_ROPLL),
	LGM_PLL(LGM_CLK_LJPLL3, "ljpll3", pll_p, 0, CGU_LJPLL3_CFG0, TYPE_LJPLL),
	LGM_PLL(LGM_CLK_LJPLL4, "ljpll4", pll_p, 0, CGU_LJPLL4_CFG0, TYPE_LJPLL),
पूर्ण;

अटल स्थिर काष्ठा lgm_clk_branch lgm_branch_clks[] = अणु
	LGM_DIV(LGM_CLK_PP_HW, "pp_hw", "pllpp", 0, PLL_DIV(CGU_PLLPP_CFG0),
		0, PLL_DIV_WIDTH, 24, 1, 0, 0, pll_भाग),
	LGM_DIV(LGM_CLK_PP_UC, "pp_uc", "pllpp", 0, PLL_DIV(CGU_PLLPP_CFG0),
		4, PLL_DIV_WIDTH, 25, 1, 0, 0, pll_भाग),
	LGM_DIV(LGM_CLK_PP_FXD, "pp_fxd", "pllpp", 0, PLL_DIV(CGU_PLLPP_CFG0),
		8, PLL_DIV_WIDTH, 26, 1, 0, 0, pll_भाग),
	LGM_DIV(LGM_CLK_PP_TBM, "pp_tbm", "pllpp", 0, PLL_DIV(CGU_PLLPP_CFG0),
		12, PLL_DIV_WIDTH, 27, 1, 0, 0, pll_भाग),
	LGM_DIV(LGM_CLK_DDR, "ddr", "pll2", CLK_IGNORE_UNUSED,
		PLL_DIV(CGU_PLL2_CFG0), 0, PLL_DIV_WIDTH, 24, 1, 0, 0,
		pll_भाग),
	LGM_DIV(LGM_CLK_CM, "cpu_cm", "pll0cz", 0, PLL_DIV(CGU_PLL0CZ_CFG0),
		0, PLL_DIV_WIDTH, 24, 1, 0, 0, pll_भाग),

	LGM_DIV(LGM_CLK_IC, "cpu_ic", "pll0cz", CLK_IGNORE_UNUSED,
		PLL_DIV(CGU_PLL0CZ_CFG0), 4, PLL_DIV_WIDTH, 25,
		1, 0, 0, pll_भाग),

	LGM_DIV(LGM_CLK_SDXC3, "sdxc3", "pll0cz", 0, PLL_DIV(CGU_PLL0CZ_CFG0),
		8, PLL_DIV_WIDTH, 26, 1, 0, 0, pll_भाग),

	LGM_DIV(LGM_CLK_CPU0, "cm0", "pll0cm0",
		CLK_IGNORE_UNUSED, PLL_DIV(CGU_PLL0CM0_CFG0),
		0, PLL_DIV_WIDTH, 24, 1, 0, 0, pll_भाग),
	LGM_DIV(LGM_CLK_CPU1, "cm1", "pll0cm1",
		CLK_IGNORE_UNUSED, PLL_DIV(CGU_PLL0CM1_CFG0),
		0, PLL_DIV_WIDTH, 24, 1, 0, 0, pll_भाग),

	/*
	 * Marking ngi_clk (next generation पूर्णांकerconnect) and noc_clk
	 * (network on chip peripheral clk) as critical घड़ीs because
	 * these are shared parent घड़ी sources क्रम many dअगरferent
	 * peripherals.
	 */
	LGM_DIV(LGM_CLK_NGI, "ngi", "pll0b",
		(CLK_IGNORE_UNUSED|CLK_IS_CRITICAL), PLL_DIV(CGU_PLL0B_CFG0),
		0, PLL_DIV_WIDTH, 24, 1, 0, 0, pll_भाग),
	LGM_DIV(LGM_CLK_NOC4, "noc4", "pll0b",
		(CLK_IGNORE_UNUSED|CLK_IS_CRITICAL), PLL_DIV(CGU_PLL0B_CFG0),
		4, PLL_DIV_WIDTH, 25, 1, 0, 0, pll_भाग),
	LGM_DIV(LGM_CLK_SW, "switch", "pll0b", 0, PLL_DIV(CGU_PLL0B_CFG0),
		8, PLL_DIV_WIDTH, 26, 1, 0, 0, pll_भाग),
	LGM_DIV(LGM_CLK_QSPI, "qspi", "pll0b", 0, PLL_DIV(CGU_PLL0B_CFG0),
		12, PLL_DIV_WIDTH, 27, 1, 0, 0, pll_भाग),
	LGM_DIV(LGM_CLK_CT, "v_ct", "pll1", 0, PLL_DIV(CGU_PLL1_CFG0),
		0, PLL_DIV_WIDTH, 24, 1, 0, 0, pll_भाग),
	LGM_DIV(LGM_CLK_DSP, "v_dsp", "pll1", 0, PLL_DIV(CGU_PLL1_CFG0),
		8, PLL_DIV_WIDTH, 26, 1, 0, 0, pll_भाग),
	LGM_DIV(LGM_CLK_VIF, "v_ifclk", "pll1", 0, PLL_DIV(CGU_PLL1_CFG0),
		12, PLL_DIV_WIDTH, 27, 1, 0, 0, pll_भाग),

	LGM_FIXED_FACTOR(LGM_CLK_EMMC4, "emmc4", "sdxc3", 0,  0,
			 0, 0, 0, 0, 1, 4),
	LGM_FIXED_FACTOR(LGM_CLK_SDXC2, "sdxc2", "noc4", 0,  0,
			 0, 0, 0, 0, 1, 4),
	LGM_MUX(LGM_CLK_EMMC, "emmc", emmc_p, 0, CGU_IF_CLK1,
		0, 1, CLK_MUX_ROUND_CLOSEST, 0),
	LGM_MUX(LGM_CLK_SDXC, "sdxc", sdxc_p, 0, CGU_IF_CLK1,
		1, 1, CLK_MUX_ROUND_CLOSEST, 0),
	LGM_FIXED(LGM_CLK_OSC, "osc", शून्य, 0, 0, 0, 0, 0, 40000000, 0),
	LGM_FIXED(LGM_CLK_SLIC, "slic", शून्य, 0, CGU_IF_CLK1,
		  8, 2, CLOCK_FLAG_VAL_INIT, 8192000, 2),
	LGM_FIXED(LGM_CLK_DOCSIS, "v_docsis", शून्य, 0, 0, 0, 0, 0, 16000000, 0),
	LGM_DIV(LGM_CLK_DCL, "dcl", "v_ifclk", 0, CGU_PCMCR,
		25, 3, 0, 0, 0, 0, dcl_भाग),
	LGM_MUX(LGM_CLK_PCM, "pcm", pcm_p, 0, CGU_C55_PCMCR,
		0, 1, CLK_MUX_ROUND_CLOSEST, 0),
	LGM_FIXED_FACTOR(LGM_CLK_DDR_PHY, "ddr_phy", "ddr",
			 CLK_IGNORE_UNUSED, 0,
			 0, 0, 0, 0, 2, 1),
	LGM_FIXED_FACTOR(LGM_CLK_PONDEF, "pondef", "dd_pool",
			 CLK_SET_RATE_PARENT, 0, 0, 0, 0, 0, 1, 2),
	LGM_MUX(LGM_CLK_CBPHY0, "cbphy0", cbphy_p, 0, 0,
		0, 0, MUX_CLK_SW | CLK_MUX_ROUND_CLOSEST, 0),
	LGM_MUX(LGM_CLK_CBPHY1, "cbphy1", cbphy_p, 0, 0,
		0, 0, MUX_CLK_SW | CLK_MUX_ROUND_CLOSEST, 0),
	LGM_MUX(LGM_CLK_CBPHY2, "cbphy2", cbphy_p, 0, 0,
		0, 0, MUX_CLK_SW | CLK_MUX_ROUND_CLOSEST, 0),
	LGM_MUX(LGM_CLK_CBPHY3, "cbphy3", cbphy_p, 0, 0,
		0, 0, MUX_CLK_SW | CLK_MUX_ROUND_CLOSEST, 0),

	LGM_GATE(LGM_GCLK_C55, "g_c55", शून्य, 0, CGU_GATE0,
		 G_C55_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_QSPI, "g_qspi", "qspi", 0, CGU_GATE0,
		 G_QSPI_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_EIP197, "g_eip197", शून्य, 0, CGU_GATE0,
		 G_EIP197_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_VAULT, "g_vault130", शून्य, 0, CGU_GATE0,
		 G_VAULT130_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_TOE, "g_toe", शून्य, 0, CGU_GATE0,
		 G_TOE_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_SDXC, "g_sdxc", "sdxc", 0, CGU_GATE0,
		 G_SDXC_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_EMMC, "g_emmc", "emmc", 0, CGU_GATE0,
		 G_EMMC_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_SPI_DBG, "g_spidbg", शून्य, 0, CGU_GATE0,
		 G_SPIDBG_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_DMA3, "g_dma3", शून्य, 0, CGU_GATE0,
		 G_DMA3_SHIFT, 0, 0),

	LGM_GATE(LGM_GCLK_DMA0, "g_dma0", शून्य, 0, CGU_GATE1,
		 G_DMA0_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_LEDC0, "g_ledc0", शून्य, 0, CGU_GATE1,
		 G_LEDC0_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_LEDC1, "g_ledc1", शून्य, 0, CGU_GATE1,
		 G_LEDC1_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_I2S0, "g_i2s0", शून्य, 0, CGU_GATE1,
		 G_I2S0_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_I2S1, "g_i2s1", शून्य, 0, CGU_GATE1,
		 G_I2S1_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_EBU, "g_ebu", शून्य, 0, CGU_GATE1,
		 G_EBU_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_PWM, "g_pwm", शून्य, 0, CGU_GATE1,
		 G_PWM_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_I2C0, "g_i2c0", शून्य, 0, CGU_GATE1,
		 G_I2C0_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_I2C1, "g_i2c1", शून्य, 0, CGU_GATE1,
		 G_I2C1_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_I2C2, "g_i2c2", शून्य, 0, CGU_GATE1,
		 G_I2C2_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_I2C3, "g_i2c3", शून्य, 0, CGU_GATE1,
		 G_I2C3_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_SSC0, "g_ssc0", "noc4", 0, CGU_GATE1,
		 G_SSC0_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_SSC1, "g_ssc1", "noc4", 0, CGU_GATE1,
		 G_SSC1_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_SSC2, "g_ssc2", "noc4", 0, CGU_GATE1,
		 G_SSC2_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_SSC3, "g_ssc3", "noc4", 0, CGU_GATE1,
		 G_SSC3_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_GPTC0, "g_gptc0", "noc4", 0, CGU_GATE1,
		 G_GPTC0_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_GPTC1, "g_gptc1", "noc4", 0, CGU_GATE1,
		 G_GPTC1_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_GPTC2, "g_gptc2", "noc4", 0, CGU_GATE1,
		 G_GPTC2_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_GPTC3, "g_gptc3", "osc", 0, CGU_GATE1,
		 G_GPTC3_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_ASC0, "g_asc0", "noc4", 0, CGU_GATE1,
		 G_ASC0_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_ASC1, "g_asc1", "noc4", 0, CGU_GATE1,
		 G_ASC1_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_ASC2, "g_asc2", "noc4", 0, CGU_GATE1,
		 G_ASC2_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_ASC3, "g_asc3", "osc", 0, CGU_GATE1,
		 G_ASC3_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_PCM0, "g_pcm0", शून्य, 0, CGU_GATE1,
		 G_PCM0_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_PCM1, "g_pcm1", शून्य, 0, CGU_GATE1,
		 G_PCM1_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_PCM2, "g_pcm2", शून्य, 0, CGU_GATE1,
		 G_PCM2_SHIFT, 0, 0),

	LGM_GATE(LGM_GCLK_PCIE10, "g_pcie10", शून्य, 0, CGU_GATE2,
		 G_PCIE10_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_PCIE11, "g_pcie11", शून्य, 0, CGU_GATE2,
		 G_PCIE11_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_PCIE30, "g_pcie30", शून्य, 0, CGU_GATE2,
		 G_PCIE30_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_PCIE31, "g_pcie31", शून्य, 0, CGU_GATE2,
		 G_PCIE31_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_PCIE20, "g_pcie20", शून्य, 0, CGU_GATE2,
		 G_PCIE20_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_PCIE21, "g_pcie21", शून्य, 0, CGU_GATE2,
		 G_PCIE21_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_PCIE40, "g_pcie40", शून्य, 0, CGU_GATE2,
		 G_PCIE40_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_PCIE41, "g_pcie41", शून्य, 0, CGU_GATE2,
		 G_PCIE41_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_XPCS0, "g_xpcs0", शून्य, 0, CGU_GATE2,
		 G_XPCS0_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_XPCS1, "g_xpcs1", शून्य, 0, CGU_GATE2,
		 G_XPCS1_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_XPCS2, "g_xpcs2", शून्य, 0, CGU_GATE2,
		 G_XPCS2_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_XPCS3, "g_xpcs3", शून्य, 0, CGU_GATE2,
		 G_XPCS3_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_SATA0, "g_sata0", शून्य, 0, CGU_GATE2,
		 G_SATA0_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_SATA1, "g_sata1", शून्य, 0, CGU_GATE2,
		 G_SATA1_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_SATA2, "g_sata2", शून्य, 0, CGU_GATE2,
		 G_SATA2_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_SATA3, "g_sata3", शून्य, 0, CGU_GATE2,
		 G_SATA3_SHIFT, 0, 0),

	LGM_GATE(LGM_GCLK_ARCEM4, "g_arcem4", शून्य, 0, CGU_GATE3,
		 G_ARCEM4_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_IDMAR1, "g_idmar1", शून्य, 0, CGU_GATE3,
		 G_IDMAR1_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_IDMAT0, "g_idmat0", शून्य, 0, CGU_GATE3,
		 G_IDMAT0_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_IDMAT1, "g_idmat1", शून्य, 0, CGU_GATE3,
		 G_IDMAT1_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_IDMAT2, "g_idmat2", शून्य, 0, CGU_GATE3,
		 G_IDMAT2_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_PPV4, "g_ppv4", शून्य, 0, CGU_GATE3,
		 G_PPV4_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_GSWIPO, "g_gswipo", "switch", 0, CGU_GATE3,
		 G_GSWIPO_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_CQEM, "g_cqem", "switch", 0, CGU_GATE3,
		 G_CQEM_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_XPCS5, "g_xpcs5", शून्य, 0, CGU_GATE3,
		 G_XPCS5_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_USB1, "g_usb1", शून्य, 0, CGU_GATE3,
		 G_USB1_SHIFT, 0, 0),
	LGM_GATE(LGM_GCLK_USB2, "g_usb2", शून्य, 0, CGU_GATE3,
		 G_USB2_SHIFT, 0, 0),
पूर्ण;


अटल स्थिर काष्ठा lgm_clk_dभाग_data lgm_dभाग_clks[] = अणु
	LGM_DDIV(LGM_CLK_CML, "dd_cml", "ljpll3", 0,
		 PLL_DIV(CGU_LJPLL3_CFG0), 0, PLL_DDIV_WIDTH,
		 3, PLL_DDIV_WIDTH, 24, 1, 29, 0),
	LGM_DDIV(LGM_CLK_SERDES, "dd_serdes", "ljpll3", 0,
		 PLL_DIV(CGU_LJPLL3_CFG0), 6, PLL_DDIV_WIDTH,
		 9, PLL_DDIV_WIDTH, 25, 1, 28, 0),
	LGM_DDIV(LGM_CLK_POOL, "dd_pool", "ljpll3", 0,
		 PLL_DIV(CGU_LJPLL3_CFG0), 12, PLL_DDIV_WIDTH,
		 15, PLL_DDIV_WIDTH, 26, 1, 28, 0),
	LGM_DDIV(LGM_CLK_PTP, "dd_ptp", "ljpll3", 0,
		 PLL_DIV(CGU_LJPLL3_CFG0), 18, PLL_DDIV_WIDTH,
		 21, PLL_DDIV_WIDTH, 27, 1, 28, 0),
	LGM_DDIV(LGM_CLK_PCIE, "dd_pcie", "ljpll4", 0,
		 PLL_DIV(CGU_LJPLL4_CFG0), 0, PLL_DDIV_WIDTH,
		 3, PLL_DDIV_WIDTH, 24, 1, 29, 0),
पूर्ण;

अटल पूर्णांक lgm_cgu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lgm_clk_provider *ctx;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, काष्ठा_size(ctx, clk_data.hws, CLK_NR_CLKS),
			   GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->clk_data.num = CLK_NR_CLKS;

	ctx->membase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ctx->membase))
		वापस PTR_ERR(ctx->membase);

	ctx->np = np;
	ctx->dev = dev;
	spin_lock_init(&ctx->lock);

	ret = lgm_clk_रेजिस्टर_plls(ctx, lgm_pll_clks,
				    ARRAY_SIZE(lgm_pll_clks));
	अगर (ret)
		वापस ret;

	ret = lgm_clk_रेजिस्टर_branches(ctx, lgm_branch_clks,
					ARRAY_SIZE(lgm_branch_clks));
	अगर (ret)
		वापस ret;

	ret = lgm_clk_रेजिस्टर_dभाग(ctx, lgm_dभाग_clks,
				    ARRAY_SIZE(lgm_dभाग_clks));
	अगर (ret)
		वापस ret;

	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get,
					   &ctx->clk_data);
पूर्ण

अटल स्थिर काष्ठा of_device_id of_lgm_cgu_match[] = अणु
	अणु .compatible = "intel,cgu-lgm" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver lgm_cgu_driver = अणु
	.probe = lgm_cgu_probe,
	.driver = अणु
		   .name = "cgu-lgm",
		   .of_match_table = of_lgm_cgu_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(lgm_cgu_driver);
