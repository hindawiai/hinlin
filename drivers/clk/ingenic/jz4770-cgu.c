<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * JZ4770 SoC CGU driver
 * Copyright 2018, Paul Cercueil <paul@crapouillou.net>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>

#समावेश <dt-bindings/घड़ी/jz4770-cgu.h>

#समावेश "cgu.h"
#समावेश "pm.h"

/*
 * CPM रेजिस्टरs offset address definition
 */
#घोषणा CGU_REG_CPCCR		0x00
#घोषणा CGU_REG_LCR		0x04
#घोषणा CGU_REG_CPPCR0		0x10
#घोषणा CGU_REG_CLKGR0		0x20
#घोषणा CGU_REG_OPCR		0x24
#घोषणा CGU_REG_CLKGR1		0x28
#घोषणा CGU_REG_CPPCR1		0x30
#घोषणा CGU_REG_USBPCR1		0x48
#घोषणा CGU_REG_USBCDR		0x50
#घोषणा CGU_REG_I2SCDR		0x60
#घोषणा CGU_REG_LPCDR		0x64
#घोषणा CGU_REG_MSC0CDR		0x68
#घोषणा CGU_REG_UHCCDR		0x6c
#घोषणा CGU_REG_SSICDR		0x74
#घोषणा CGU_REG_CIMCDR		0x7c
#घोषणा CGU_REG_GPSCDR		0x80
#घोषणा CGU_REG_PCMCDR		0x84
#घोषणा CGU_REG_GPUCDR		0x88
#घोषणा CGU_REG_MSC1CDR		0xA4
#घोषणा CGU_REG_MSC2CDR		0xA8
#घोषणा CGU_REG_BCHCDR		0xAC

/* bits within the OPCR रेजिस्टर */
#घोषणा OPCR_SPENDH		BIT(5)		/* UHC PHY suspend */

/* bits within the USBPCR1 रेजिस्टर */
#घोषणा USBPCR1_UHC_POWER	BIT(5)		/* UHC PHY घातer करोwn */

अटल काष्ठा ingenic_cgu *cgu;

अटल पूर्णांक jz4770_uhc_phy_enable(काष्ठा clk_hw *hw)
अणु
	व्योम __iomem *reg_opcr		= cgu->base + CGU_REG_OPCR;
	व्योम __iomem *reg_usbpcr1	= cgu->base + CGU_REG_USBPCR1;

	ग_लिखोl(पढ़ोl(reg_opcr) & ~OPCR_SPENDH, reg_opcr);
	ग_लिखोl(पढ़ोl(reg_usbpcr1) | USBPCR1_UHC_POWER, reg_usbpcr1);
	वापस 0;
पूर्ण

अटल व्योम jz4770_uhc_phy_disable(काष्ठा clk_hw *hw)
अणु
	व्योम __iomem *reg_opcr		= cgu->base + CGU_REG_OPCR;
	व्योम __iomem *reg_usbpcr1	= cgu->base + CGU_REG_USBPCR1;

	ग_लिखोl(पढ़ोl(reg_usbpcr1) & ~USBPCR1_UHC_POWER, reg_usbpcr1);
	ग_लिखोl(पढ़ोl(reg_opcr) | OPCR_SPENDH, reg_opcr);
पूर्ण

अटल पूर्णांक jz4770_uhc_phy_is_enabled(काष्ठा clk_hw *hw)
अणु
	व्योम __iomem *reg_opcr		= cgu->base + CGU_REG_OPCR;
	व्योम __iomem *reg_usbpcr1	= cgu->base + CGU_REG_USBPCR1;

	वापस !(पढ़ोl(reg_opcr) & OPCR_SPENDH) &&
		(पढ़ोl(reg_usbpcr1) & USBPCR1_UHC_POWER);
पूर्ण

अटल स्थिर काष्ठा clk_ops jz4770_uhc_phy_ops = अणु
	.enable = jz4770_uhc_phy_enable,
	.disable = jz4770_uhc_phy_disable,
	.is_enabled = jz4770_uhc_phy_is_enabled,
पूर्ण;

अटल स्थिर s8 pll_od_encoding[8] = अणु
	0x0, 0x1, -1, 0x2, -1, -1, -1, 0x3,
पूर्ण;

अटल स्थिर u8 jz4770_cgu_cpccr_भाग_प्रकारable[] = अणु
	1, 2, 3, 4, 6, 8, 12,
पूर्ण;

अटल स्थिर काष्ठा ingenic_cgu_clk_info jz4770_cgu_घड़ीs[] = अणु

	/* External घड़ीs */

	[JZ4770_CLK_EXT] = अणु "ext", CGU_CLK_EXT पूर्ण,
	[JZ4770_CLK_OSC32K] = अणु "osc32k", CGU_CLK_EXT पूर्ण,

	/* PLLs */

	[JZ4770_CLK_PLL0] = अणु
		"pll0", CGU_CLK_PLL,
		.parents = अणु JZ4770_CLK_EXT पूर्ण,
		.pll = अणु
			.reg = CGU_REG_CPPCR0,
			.rate_multiplier = 1,
			.m_shअगरt = 24,
			.m_bits = 7,
			.m_offset = 1,
			.n_shअगरt = 18,
			.n_bits = 5,
			.n_offset = 1,
			.od_shअगरt = 16,
			.od_bits = 2,
			.od_max = 8,
			.od_encoding = pll_od_encoding,
			.bypass_reg = CGU_REG_CPPCR0,
			.bypass_bit = 9,
			.enable_bit = 8,
			.stable_bit = 10,
		पूर्ण,
	पूर्ण,

	[JZ4770_CLK_PLL1] = अणु
		/* TODO: PLL1 can depend on PLL0 */
		"pll1", CGU_CLK_PLL,
		.parents = अणु JZ4770_CLK_EXT पूर्ण,
		.pll = अणु
			.reg = CGU_REG_CPPCR1,
			.rate_multiplier = 1,
			.m_shअगरt = 24,
			.m_bits = 7,
			.m_offset = 1,
			.n_shअगरt = 18,
			.n_bits = 5,
			.n_offset = 1,
			.od_shअगरt = 16,
			.od_bits = 2,
			.od_max = 8,
			.od_encoding = pll_od_encoding,
			.bypass_reg = CGU_REG_CPPCR1,
			.no_bypass_bit = true,
			.enable_bit = 7,
			.stable_bit = 6,
		पूर्ण,
	पूर्ण,

	/* Main घड़ीs */

	[JZ4770_CLK_CCLK] = अणु
		"cclk", CGU_CLK_DIV,
		.parents = अणु JZ4770_CLK_PLL0, पूर्ण,
		.भाग = अणु
			CGU_REG_CPCCR, 0, 1, 4, 22, -1, -1,
			jz4770_cgu_cpccr_भाग_प्रकारable,
		पूर्ण,
	पूर्ण,
	[JZ4770_CLK_H0CLK] = अणु
		"h0clk", CGU_CLK_DIV,
		.parents = अणु JZ4770_CLK_PLL0, पूर्ण,
		.भाग = अणु
			CGU_REG_CPCCR, 4, 1, 4, 22, -1, -1,
			jz4770_cgu_cpccr_भाग_प्रकारable,
		पूर्ण,
	पूर्ण,
	[JZ4770_CLK_H1CLK] = अणु
		"h1clk", CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_PLL0, पूर्ण,
		.भाग = अणु
			CGU_REG_CPCCR, 24, 1, 4, 22, -1, -1,
			jz4770_cgu_cpccr_भाग_प्रकारable,
		पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 7 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_H2CLK] = अणु
		"h2clk", CGU_CLK_DIV,
		.parents = अणु JZ4770_CLK_PLL0, पूर्ण,
		.भाग = अणु
			CGU_REG_CPCCR, 16, 1, 4, 22, -1, -1,
			jz4770_cgu_cpccr_भाग_प्रकारable,
		पूर्ण,
	पूर्ण,
	[JZ4770_CLK_C1CLK] = अणु
		"c1clk", CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_PLL0, पूर्ण,
		.भाग = अणु
			CGU_REG_CPCCR, 12, 1, 4, 22, -1, -1,
			jz4770_cgu_cpccr_भाग_प्रकारable,
		पूर्ण,
		.gate = अणु CGU_REG_OPCR, 31, true पूर्ण, // disable CCLK stop on idle
	पूर्ण,
	[JZ4770_CLK_PCLK] = अणु
		"pclk", CGU_CLK_DIV,
		.parents = अणु JZ4770_CLK_PLL0, पूर्ण,
		.भाग = अणु
			CGU_REG_CPCCR, 8, 1, 4, 22, -1, -1,
			jz4770_cgu_cpccr_भाग_प्रकारable,
		पूर्ण,
	पूर्ण,

	/* Those भागided घड़ीs can connect to PLL0 or PLL1 */

	[JZ4770_CLK_MMC0_MUX] = अणु
		"mmc0_mux", CGU_CLK_DIV | CGU_CLK_GATE | CGU_CLK_MUX,
		.parents = अणु JZ4770_CLK_PLL0, JZ4770_CLK_PLL1, पूर्ण,
		.mux = अणु CGU_REG_MSC0CDR, 30, 1 पूर्ण,
		.भाग = अणु CGU_REG_MSC0CDR, 0, 1, 7, -1, -1, 31 पूर्ण,
		.gate = अणु CGU_REG_MSC0CDR, 31 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_MMC1_MUX] = अणु
		"mmc1_mux", CGU_CLK_DIV | CGU_CLK_GATE | CGU_CLK_MUX,
		.parents = अणु JZ4770_CLK_PLL0, JZ4770_CLK_PLL1, पूर्ण,
		.mux = अणु CGU_REG_MSC1CDR, 30, 1 पूर्ण,
		.भाग = अणु CGU_REG_MSC1CDR, 0, 1, 7, -1, -1, 31 पूर्ण,
		.gate = अणु CGU_REG_MSC1CDR, 31 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_MMC2_MUX] = अणु
		"mmc2_mux", CGU_CLK_DIV | CGU_CLK_GATE | CGU_CLK_MUX,
		.parents = अणु JZ4770_CLK_PLL0, JZ4770_CLK_PLL1, पूर्ण,
		.mux = अणु CGU_REG_MSC2CDR, 30, 1 पूर्ण,
		.भाग = अणु CGU_REG_MSC2CDR, 0, 1, 7, -1, -1, 31 पूर्ण,
		.gate = अणु CGU_REG_MSC2CDR, 31 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_CIM] = अणु
		"cim", CGU_CLK_DIV | CGU_CLK_GATE | CGU_CLK_MUX,
		.parents = अणु JZ4770_CLK_PLL0, JZ4770_CLK_PLL1, पूर्ण,
		.mux = अणु CGU_REG_CIMCDR, 31, 1 पूर्ण,
		.भाग = अणु CGU_REG_CIMCDR, 0, 1, 8, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 26 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_UHC] = अणु
		"uhc", CGU_CLK_DIV | CGU_CLK_GATE | CGU_CLK_MUX,
		.parents = अणु JZ4770_CLK_PLL0, JZ4770_CLK_PLL1, पूर्ण,
		.mux = अणु CGU_REG_UHCCDR, 29, 1 पूर्ण,
		.भाग = अणु CGU_REG_UHCCDR, 0, 1, 4, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 24 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_GPU] = अणु
		"gpu", CGU_CLK_DIV | CGU_CLK_GATE | CGU_CLK_MUX,
		.parents = अणु JZ4770_CLK_PLL0, JZ4770_CLK_PLL1, -1 पूर्ण,
		.mux = अणु CGU_REG_GPUCDR, 31, 1 पूर्ण,
		.भाग = अणु CGU_REG_GPUCDR, 0, 1, 3, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 9 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_BCH] = अणु
		"bch", CGU_CLK_DIV | CGU_CLK_GATE | CGU_CLK_MUX,
		.parents = अणु JZ4770_CLK_PLL0, JZ4770_CLK_PLL1, पूर्ण,
		.mux = अणु CGU_REG_BCHCDR, 31, 1 पूर्ण,
		.भाग = अणु CGU_REG_BCHCDR, 0, 1, 3, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 1 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_LPCLK_MUX] = अणु
		"lpclk", CGU_CLK_DIV | CGU_CLK_GATE | CGU_CLK_MUX,
		.parents = अणु JZ4770_CLK_PLL0, JZ4770_CLK_PLL1, पूर्ण,
		.mux = अणु CGU_REG_LPCDR, 29, 1 पूर्ण,
		.भाग = अणु CGU_REG_LPCDR, 0, 1, 11, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 28 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_GPS] = अणु
		"gps", CGU_CLK_DIV | CGU_CLK_GATE | CGU_CLK_MUX,
		.parents = अणु JZ4770_CLK_PLL0, JZ4770_CLK_PLL1, पूर्ण,
		.mux = अणु CGU_REG_GPSCDR, 31, 1 पूर्ण,
		.भाग = अणु CGU_REG_GPSCDR, 0, 1, 4, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 22 पूर्ण,
	पूर्ण,

	/* Those भागided घड़ीs can connect to EXT, PLL0 or PLL1 */

	[JZ4770_CLK_SSI_MUX] = अणु
		"ssi_mux", CGU_CLK_DIV | CGU_CLK_MUX,
		.parents = अणु JZ4770_CLK_EXT, -1,
			JZ4770_CLK_PLL0, JZ4770_CLK_PLL1 पूर्ण,
		.mux = अणु CGU_REG_SSICDR, 30, 2 पूर्ण,
		.भाग = अणु CGU_REG_SSICDR, 0, 1, 6, -1, -1, -1 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_PCM_MUX] = अणु
		"pcm_mux", CGU_CLK_DIV | CGU_CLK_MUX,
		.parents = अणु JZ4770_CLK_EXT, -1,
			JZ4770_CLK_PLL0, JZ4770_CLK_PLL1 पूर्ण,
		.mux = अणु CGU_REG_PCMCDR, 30, 2 पूर्ण,
		.भाग = अणु CGU_REG_PCMCDR, 0, 1, 9, -1, -1, -1 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_I2S] = अणु
		"i2s", CGU_CLK_DIV | CGU_CLK_GATE | CGU_CLK_MUX,
		.parents = अणु JZ4770_CLK_EXT, -1,
			JZ4770_CLK_PLL0, JZ4770_CLK_PLL1 पूर्ण,
		.mux = अणु CGU_REG_I2SCDR, 30, 2 पूर्ण,
		.भाग = अणु CGU_REG_I2SCDR, 0, 1, 9, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 13 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_OTG] = अणु
		"usb", CGU_CLK_DIV | CGU_CLK_GATE | CGU_CLK_MUX,
		.parents = अणु JZ4770_CLK_EXT, -1,
			JZ4770_CLK_PLL0, JZ4770_CLK_PLL1 पूर्ण,
		.mux = अणु CGU_REG_USBCDR, 30, 2 पूर्ण,
		.भाग = अणु CGU_REG_USBCDR, 0, 1, 8, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 2 पूर्ण,
	पूर्ण,

	/* Gate-only घड़ीs */

	[JZ4770_CLK_SSI0] = अणु
		"ssi0", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_SSI_MUX, पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 4 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_SSI1] = अणु
		"ssi1", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_SSI_MUX, पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 19 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_SSI2] = अणु
		"ssi2", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_SSI_MUX, पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 20 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_PCM0] = अणु
		"pcm0", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_PCM_MUX, पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 8 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_PCM1] = अणु
		"pcm1", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_PCM_MUX, पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 10 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_DMA] = अणु
		"dma", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_H2CLK, पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 21 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_I2C0] = अणु
		"i2c0", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_EXT, पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 5 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_I2C1] = अणु
		"i2c1", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_EXT, पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 6 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_I2C2] = अणु
		"i2c2", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_EXT, पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 15 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_UART0] = अणु
		"uart0", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_EXT, पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 15 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_UART1] = अणु
		"uart1", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_EXT, पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 16 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_UART2] = अणु
		"uart2", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_EXT, पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 17 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_UART3] = अणु
		"uart3", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_EXT, पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 18 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_IPU] = अणु
		"ipu", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_H0CLK, पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 29 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_ADC] = अणु
		"adc", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_EXT, पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 14 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_AIC] = अणु
		"aic", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_EXT, पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 8 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_AUX] = अणु
		"aux", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_C1CLK, पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 14 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_VPU] = अणु
		"vpu", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_H1CLK, पूर्ण,
		.gate = अणु CGU_REG_LCR, 30, false, 150 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_MMC0] = अणु
		"mmc0", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_MMC0_MUX, पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 3 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_MMC1] = अणु
		"mmc1", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_MMC1_MUX, पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 11 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_MMC2] = अणु
		"mmc2", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_MMC2_MUX, पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 12 पूर्ण,
	पूर्ण,
	[JZ4770_CLK_OTG_PHY] = अणु
		"usb_phy", CGU_CLK_GATE,
		.parents = अणु JZ4770_CLK_OTG पूर्ण,
		.gate = अणु CGU_REG_OPCR, 7, true, 50 पूर्ण,
	पूर्ण,

	/* Custom घड़ीs */

	[JZ4770_CLK_UHC_PHY] = अणु
		"uhc_phy", CGU_CLK_CUSTOM,
		.parents = अणु JZ4770_CLK_UHC, -1, -1, -1 पूर्ण,
		.custom = अणु &jz4770_uhc_phy_ops पूर्ण,
	पूर्ण,

	[JZ4770_CLK_EXT512] = अणु
		"ext/512", CGU_CLK_FIXDIV,
		.parents = अणु JZ4770_CLK_EXT पूर्ण,
		.fixभाग = अणु 512 पूर्ण,
	पूर्ण,

	[JZ4770_CLK_RTC] = अणु
		"rtc", CGU_CLK_MUX,
		.parents = अणु JZ4770_CLK_EXT512, JZ4770_CLK_OSC32K, पूर्ण,
		.mux = अणु CGU_REG_OPCR, 2, 1पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init jz4770_cgu_init(काष्ठा device_node *np)
अणु
	पूर्णांक retval;

	cgu = ingenic_cgu_new(jz4770_cgu_घड़ीs,
			      ARRAY_SIZE(jz4770_cgu_घड़ीs), np);
	अगर (!cgu) अणु
		pr_err("%s: failed to initialise CGU\n", __func__);
		वापस;
	पूर्ण

	retval = ingenic_cgu_रेजिस्टर_घड़ीs(cgu);
	अगर (retval)
		pr_err("%s: failed to register CGU Clocks\n", __func__);

	ingenic_cgu_रेजिस्टर_syscore_ops(cgu);
पूर्ण

/* We only probe via devicetree, no need क्रम a platक्रमm driver */
CLK_OF_DECLARE_DRIVER(jz4770_cgu, "ingenic,jz4770-cgu", jz4770_cgu_init);
