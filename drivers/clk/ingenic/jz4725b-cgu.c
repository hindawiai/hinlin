<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Ingenic JZ4725B SoC CGU driver
 *
 * Copyright (C) 2018 Paul Cercueil
 * Author: Paul Cercueil <paul@crapouillou.net>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>

#समावेश <dt-bindings/घड़ी/jz4725b-cgu.h>

#समावेश "cgu.h"
#समावेश "pm.h"

/* CGU रेजिस्टर offsets */
#घोषणा CGU_REG_CPCCR		0x00
#घोषणा CGU_REG_LCR		0x04
#घोषणा CGU_REG_CPPCR		0x10
#घोषणा CGU_REG_CLKGR		0x20
#घोषणा CGU_REG_OPCR		0x24
#घोषणा CGU_REG_I2SCDR		0x60
#घोषणा CGU_REG_LPCDR		0x64
#घोषणा CGU_REG_MSCCDR		0x68
#घोषणा CGU_REG_SSICDR		0x74
#घोषणा CGU_REG_CIMCDR		0x78

/* bits within the LCR रेजिस्टर */
#घोषणा LCR_SLEEP		BIT(0)

अटल काष्ठा ingenic_cgu *cgu;

अटल स्थिर s8 pll_od_encoding[4] = अणु
	0x0, 0x1, -1, 0x3,
पूर्ण;

अटल स्थिर u8 jz4725b_cgu_cpccr_भाग_प्रकारable[] = अणु
	1, 2, 3, 4, 6, 8,
पूर्ण;

अटल स्थिर u8 jz4725b_cgu_pll_half_भाग_प्रकारable[] = अणु
	2, 1,
पूर्ण;

अटल स्थिर काष्ठा ingenic_cgu_clk_info jz4725b_cgu_घड़ीs[] = अणु

	/* External घड़ीs */

	[JZ4725B_CLK_EXT] = अणु "ext", CGU_CLK_EXT पूर्ण,
	[JZ4725B_CLK_OSC32K] = अणु "osc32k", CGU_CLK_EXT पूर्ण,

	[JZ4725B_CLK_PLL] = अणु
		"pll", CGU_CLK_PLL,
		.parents = अणु JZ4725B_CLK_EXT, -1, -1, -1 पूर्ण,
		.pll = अणु
			.reg = CGU_REG_CPPCR,
			.rate_multiplier = 1,
			.m_shअगरt = 23,
			.m_bits = 9,
			.m_offset = 2,
			.n_shअगरt = 18,
			.n_bits = 5,
			.n_offset = 2,
			.od_shअगरt = 16,
			.od_bits = 2,
			.od_max = 4,
			.od_encoding = pll_od_encoding,
			.stable_bit = 10,
			.bypass_reg = CGU_REG_CPPCR,
			.bypass_bit = 9,
			.enable_bit = 8,
		पूर्ण,
	पूर्ण,

	/* Muxes & भागiders */

	[JZ4725B_CLK_PLL_HALF] = अणु
		"pll half", CGU_CLK_DIV,
		.parents = अणु JZ4725B_CLK_PLL, -1, -1, -1 पूर्ण,
		.भाग = अणु
			CGU_REG_CPCCR, 21, 1, 1, -1, -1, -1,
			jz4725b_cgu_pll_half_भाग_प्रकारable,
		पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_CCLK] = अणु
		"cclk", CGU_CLK_DIV,
		.parents = अणु JZ4725B_CLK_PLL, -1, -1, -1 पूर्ण,
		.भाग = अणु
			CGU_REG_CPCCR, 0, 1, 4, 22, -1, -1,
			jz4725b_cgu_cpccr_भाग_प्रकारable,
		पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_HCLK] = अणु
		"hclk", CGU_CLK_DIV,
		.parents = अणु JZ4725B_CLK_PLL, -1, -1, -1 पूर्ण,
		.भाग = अणु
			CGU_REG_CPCCR, 4, 1, 4, 22, -1, -1,
			jz4725b_cgu_cpccr_भाग_प्रकारable,
		पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_PCLK] = अणु
		"pclk", CGU_CLK_DIV,
		.parents = अणु JZ4725B_CLK_PLL, -1, -1, -1 पूर्ण,
		.भाग = अणु
			CGU_REG_CPCCR, 8, 1, 4, 22, -1, -1,
			jz4725b_cgu_cpccr_भाग_प्रकारable,
		पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_MCLK] = अणु
		"mclk", CGU_CLK_DIV,
		.parents = अणु JZ4725B_CLK_PLL, -1, -1, -1 पूर्ण,
		.भाग = अणु
			CGU_REG_CPCCR, 12, 1, 4, 22, -1, -1,
			jz4725b_cgu_cpccr_भाग_प्रकारable,
		पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_IPU] = अणु
		"ipu", CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु JZ4725B_CLK_PLL, -1, -1, -1 पूर्ण,
		.भाग = अणु
			CGU_REG_CPCCR, 16, 1, 4, 22, -1, -1,
			jz4725b_cgu_cpccr_भाग_प्रकारable,
		पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 13 पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_LCD] = अणु
		"lcd", CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु JZ4725B_CLK_PLL_HALF, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_LPCDR, 0, 1, 11, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 9 पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_I2S] = अणु
		"i2s", CGU_CLK_MUX | CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु JZ4725B_CLK_EXT, JZ4725B_CLK_PLL_HALF, -1, -1 पूर्ण,
		.mux = अणु CGU_REG_CPCCR, 31, 1 पूर्ण,
		.भाग = अणु CGU_REG_I2SCDR, 0, 1, 9, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 6 पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_SPI] = अणु
		"spi", CGU_CLK_MUX | CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु JZ4725B_CLK_EXT, JZ4725B_CLK_PLL, -1, -1 पूर्ण,
		.mux = अणु CGU_REG_SSICDR, 31, 1 पूर्ण,
		.भाग = अणु CGU_REG_SSICDR, 0, 1, 4, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 4 पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_MMC_MUX] = अणु
		"mmc_mux", CGU_CLK_DIV,
		.parents = अणु JZ4725B_CLK_PLL_HALF, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_MSCCDR, 0, 1, 5, -1, -1, -1 पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_UDC] = अणु
		"udc", CGU_CLK_MUX | CGU_CLK_DIV,
		.parents = अणु JZ4725B_CLK_EXT, JZ4725B_CLK_PLL_HALF, -1, -1 पूर्ण,
		.mux = अणु CGU_REG_CPCCR, 29, 1 पूर्ण,
		.भाग = अणु CGU_REG_CPCCR, 23, 1, 6, -1, -1, -1 पूर्ण,
	पूर्ण,

	/* Gate-only घड़ीs */

	[JZ4725B_CLK_UART] = अणु
		"uart", CGU_CLK_GATE,
		.parents = अणु JZ4725B_CLK_EXT, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 0 पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_DMA] = अणु
		"dma", CGU_CLK_GATE,
		.parents = अणु JZ4725B_CLK_PCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 12 पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_ADC] = अणु
		"adc", CGU_CLK_GATE,
		.parents = अणु JZ4725B_CLK_EXT, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 7 पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_I2C] = अणु
		"i2c", CGU_CLK_GATE,
		.parents = अणु JZ4725B_CLK_EXT, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 3 पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_AIC] = अणु
		"aic", CGU_CLK_GATE,
		.parents = अणु JZ4725B_CLK_EXT, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 5 पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_MMC0] = अणु
		"mmc0", CGU_CLK_GATE,
		.parents = अणु JZ4725B_CLK_MMC_MUX, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 6 पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_MMC1] = अणु
		"mmc1", CGU_CLK_GATE,
		.parents = अणु JZ4725B_CLK_MMC_MUX, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 16 पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_BCH] = अणु
		"bch", CGU_CLK_GATE,
		.parents = अणु JZ4725B_CLK_MCLK/* not sure */, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 11 पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_TCU] = अणु
		"tcu", CGU_CLK_GATE,
		.parents = अणु JZ4725B_CLK_EXT/* not sure */, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 1 पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_EXT512] = अणु
		"ext/512", CGU_CLK_FIXDIV,
		.parents = अणु JZ4725B_CLK_EXT पूर्ण,

		/* Doc calls it EXT512, but it seems to be /256... */
		.fixभाग = अणु 256 पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_RTC] = अणु
		"rtc", CGU_CLK_MUX,
		.parents = अणु JZ4725B_CLK_EXT512, JZ4725B_CLK_OSC32K, -1, -1 पूर्ण,
		.mux = अणु CGU_REG_OPCR, 2, 1पूर्ण,
	पूर्ण,

	[JZ4725B_CLK_UDC_PHY] = अणु
		"udc_phy", CGU_CLK_GATE,
		.parents = अणु JZ4725B_CLK_EXT, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_OPCR, 6, true पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init jz4725b_cgu_init(काष्ठा device_node *np)
अणु
	पूर्णांक retval;

	cgu = ingenic_cgu_new(jz4725b_cgu_घड़ीs,
			      ARRAY_SIZE(jz4725b_cgu_घड़ीs), np);
	अगर (!cgu) अणु
		pr_err("%s: failed to initialise CGU\n", __func__);
		वापस;
	पूर्ण

	retval = ingenic_cgu_रेजिस्टर_घड़ीs(cgu);
	अगर (retval)
		pr_err("%s: failed to register CGU Clocks\n", __func__);

	ingenic_cgu_रेजिस्टर_syscore_ops(cgu);
पूर्ण
CLK_OF_DECLARE_DRIVER(jz4725b_cgu, "ingenic,jz4725b-cgu", jz4725b_cgu_init);
