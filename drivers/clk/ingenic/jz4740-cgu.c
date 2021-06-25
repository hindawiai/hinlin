<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Ingenic JZ4740 SoC CGU driver
 *
 * Copyright (c) 2015 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>

#समावेश <dt-bindings/घड़ी/jz4740-cgu.h>

#समावेश "cgu.h"
#समावेश "pm.h"

/* CGU रेजिस्टर offsets */
#घोषणा CGU_REG_CPCCR		0x00
#घोषणा CGU_REG_LCR		0x04
#घोषणा CGU_REG_CPPCR		0x10
#घोषणा CGU_REG_CLKGR		0x20
#घोषणा CGU_REG_SCR		0x24
#घोषणा CGU_REG_I2SCDR		0x60
#घोषणा CGU_REG_LPCDR		0x64
#घोषणा CGU_REG_MSCCDR		0x68
#घोषणा CGU_REG_UHCCDR		0x6c
#घोषणा CGU_REG_SSICDR		0x74

/* bits within a PLL control रेजिस्टर */
#घोषणा PLLCTL_M_SHIFT		23
#घोषणा PLLCTL_M_MASK		(0x1ff << PLLCTL_M_SHIFT)
#घोषणा PLLCTL_N_SHIFT		18
#घोषणा PLLCTL_N_MASK		(0x1f << PLLCTL_N_SHIFT)
#घोषणा PLLCTL_OD_SHIFT		16
#घोषणा PLLCTL_OD_MASK		(0x3 << PLLCTL_OD_SHIFT)
#घोषणा PLLCTL_STABLE		(1 << 10)
#घोषणा PLLCTL_BYPASS		(1 << 9)
#घोषणा PLLCTL_ENABLE		(1 << 8)

/* bits within the LCR रेजिस्टर */
#घोषणा LCR_SLEEP		(1 << 0)

/* bits within the CLKGR रेजिस्टर */
#घोषणा CLKGR_UDC		(1 << 11)

अटल काष्ठा ingenic_cgu *cgu;

अटल स्थिर s8 pll_od_encoding[4] = अणु
	0x0, 0x1, -1, 0x3,
पूर्ण;

अटल स्थिर u8 jz4740_cgu_cpccr_भाग_प्रकारable[] = अणु
	1, 2, 3, 4, 6, 8, 12, 16, 24, 32,
पूर्ण;

अटल स्थिर u8 jz4740_cgu_pll_half_भाग_प्रकारable[] = अणु
	2, 1,
पूर्ण;

अटल स्थिर काष्ठा ingenic_cgu_clk_info jz4740_cgu_घड़ीs[] = अणु

	/* External घड़ीs */

	[JZ4740_CLK_EXT] = अणु "ext", CGU_CLK_EXT पूर्ण,
	[JZ4740_CLK_RTC] = अणु "rtc", CGU_CLK_EXT पूर्ण,

	[JZ4740_CLK_PLL] = अणु
		"pll", CGU_CLK_PLL,
		.parents = अणु JZ4740_CLK_EXT, -1, -1, -1 पूर्ण,
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

	[JZ4740_CLK_PLL_HALF] = अणु
		"pll half", CGU_CLK_DIV,
		.parents = अणु JZ4740_CLK_PLL, -1, -1, -1 पूर्ण,
		.भाग = अणु
			CGU_REG_CPCCR, 21, 1, 1, -1, -1, -1,
			jz4740_cgu_pll_half_भाग_प्रकारable,
		पूर्ण,
	पूर्ण,

	[JZ4740_CLK_CCLK] = अणु
		"cclk", CGU_CLK_DIV,
		.parents = अणु JZ4740_CLK_PLL, -1, -1, -1 पूर्ण,
		.भाग = अणु
			CGU_REG_CPCCR, 0, 1, 4, 22, -1, -1,
			jz4740_cgu_cpccr_भाग_प्रकारable,
		पूर्ण,
	पूर्ण,

	[JZ4740_CLK_HCLK] = अणु
		"hclk", CGU_CLK_DIV,
		.parents = अणु JZ4740_CLK_PLL, -1, -1, -1 पूर्ण,
		.भाग = अणु
			CGU_REG_CPCCR, 4, 1, 4, 22, -1, -1,
			jz4740_cgu_cpccr_भाग_प्रकारable,
		पूर्ण,
	पूर्ण,

	[JZ4740_CLK_PCLK] = अणु
		"pclk", CGU_CLK_DIV,
		.parents = अणु JZ4740_CLK_PLL, -1, -1, -1 पूर्ण,
		.भाग = अणु
			CGU_REG_CPCCR, 8, 1, 4, 22, -1, -1,
			jz4740_cgu_cpccr_भाग_प्रकारable,
		पूर्ण,
	पूर्ण,

	[JZ4740_CLK_MCLK] = अणु
		"mclk", CGU_CLK_DIV,
		.parents = अणु JZ4740_CLK_PLL, -1, -1, -1 पूर्ण,
		.भाग = अणु
			CGU_REG_CPCCR, 12, 1, 4, 22, -1, -1,
			jz4740_cgu_cpccr_भाग_प्रकारable,
		पूर्ण,
	पूर्ण,

	[JZ4740_CLK_LCD] = अणु
		"lcd", CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु JZ4740_CLK_PLL_HALF, -1, -1, -1 पूर्ण,
		.भाग = अणु
			CGU_REG_CPCCR, 16, 1, 5, 22, -1, -1,
			jz4740_cgu_cpccr_भाग_प्रकारable,
		पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 10 पूर्ण,
	पूर्ण,

	[JZ4740_CLK_LCD_PCLK] = अणु
		"lcd_pclk", CGU_CLK_DIV,
		.parents = अणु JZ4740_CLK_PLL_HALF, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_LPCDR, 0, 1, 11, -1, -1, -1 पूर्ण,
	पूर्ण,

	[JZ4740_CLK_I2S] = अणु
		"i2s", CGU_CLK_MUX | CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु JZ4740_CLK_EXT, JZ4740_CLK_PLL_HALF, -1, -1 पूर्ण,
		.mux = अणु CGU_REG_CPCCR, 31, 1 पूर्ण,
		.भाग = अणु CGU_REG_I2SCDR, 0, 1, 9, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 6 पूर्ण,
	पूर्ण,

	[JZ4740_CLK_SPI] = अणु
		"spi", CGU_CLK_MUX | CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु JZ4740_CLK_EXT, JZ4740_CLK_PLL, -1, -1 पूर्ण,
		.mux = अणु CGU_REG_SSICDR, 31, 1 पूर्ण,
		.भाग = अणु CGU_REG_SSICDR, 0, 1, 4, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 4 पूर्ण,
	पूर्ण,

	[JZ4740_CLK_MMC] = अणु
		"mmc", CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु JZ4740_CLK_PLL_HALF, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_MSCCDR, 0, 1, 5, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 7 पूर्ण,
	पूर्ण,

	[JZ4740_CLK_UHC] = अणु
		"uhc", CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु JZ4740_CLK_PLL_HALF, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_UHCCDR, 0, 1, 4, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 14 पूर्ण,
	पूर्ण,

	[JZ4740_CLK_UDC] = अणु
		"udc", CGU_CLK_MUX | CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु JZ4740_CLK_EXT, JZ4740_CLK_PLL_HALF, -1, -1 पूर्ण,
		.mux = अणु CGU_REG_CPCCR, 29, 1 पूर्ण,
		.भाग = अणु CGU_REG_CPCCR, 23, 1, 6, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_SCR, 6, true पूर्ण,
	पूर्ण,

	/* Gate-only घड़ीs */

	[JZ4740_CLK_UART0] = अणु
		"uart0", CGU_CLK_GATE,
		.parents = अणु JZ4740_CLK_EXT, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 0 पूर्ण,
	पूर्ण,

	[JZ4740_CLK_UART1] = अणु
		"uart1", CGU_CLK_GATE,
		.parents = अणु JZ4740_CLK_EXT, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 15 पूर्ण,
	पूर्ण,

	[JZ4740_CLK_DMA] = अणु
		"dma", CGU_CLK_GATE,
		.parents = अणु JZ4740_CLK_PCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 12 पूर्ण,
	पूर्ण,

	[JZ4740_CLK_IPU] = अणु
		"ipu", CGU_CLK_GATE,
		.parents = अणु JZ4740_CLK_PCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 13 पूर्ण,
	पूर्ण,

	[JZ4740_CLK_ADC] = अणु
		"adc", CGU_CLK_GATE,
		.parents = अणु JZ4740_CLK_EXT, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 8 पूर्ण,
	पूर्ण,

	[JZ4740_CLK_I2C] = अणु
		"i2c", CGU_CLK_GATE,
		.parents = अणु JZ4740_CLK_EXT, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 3 पूर्ण,
	पूर्ण,

	[JZ4740_CLK_AIC] = अणु
		"aic", CGU_CLK_GATE,
		.parents = अणु JZ4740_CLK_EXT, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 5 पूर्ण,
	पूर्ण,

	[JZ4740_CLK_TCU] = अणु
		"tcu", CGU_CLK_GATE,
		.parents = अणु JZ4740_CLK_EXT, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 1 पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init jz4740_cgu_init(काष्ठा device_node *np)
अणु
	पूर्णांक retval;

	cgu = ingenic_cgu_new(jz4740_cgu_घड़ीs,
			      ARRAY_SIZE(jz4740_cgu_घड़ीs), np);
	अगर (!cgu) अणु
		pr_err("%s: failed to initialise CGU\n", __func__);
		वापस;
	पूर्ण

	retval = ingenic_cgu_रेजिस्टर_घड़ीs(cgu);
	अगर (retval)
		pr_err("%s: failed to register CGU Clocks\n", __func__);

	ingenic_cgu_रेजिस्टर_syscore_ops(cgu);
पूर्ण
CLK_OF_DECLARE_DRIVER(jz4740_cgu, "ingenic,jz4740-cgu", jz4740_cgu_init);
