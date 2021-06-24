<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * X1000 SoC CGU driver
 * Copyright (c) 2019 ोउॉओौओ (Zhou Yanjie) <zhouyanjie@wanyeetech.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>

#समावेश <dt-bindings/घड़ी/x1000-cgu.h>

#समावेश "cgu.h"
#समावेश "pm.h"

/* CGU रेजिस्टर offsets */
#घोषणा CGU_REG_CPCCR		0x00
#घोषणा CGU_REG_APLL		0x10
#घोषणा CGU_REG_MPLL		0x14
#घोषणा CGU_REG_CLKGR		0x20
#घोषणा CGU_REG_OPCR		0x24
#घोषणा CGU_REG_DDRCDR		0x2c
#घोषणा CGU_REG_USBPCR		0x3c
#घोषणा CGU_REG_USBPCR1		0x48
#घोषणा CGU_REG_USBCDR		0x50
#घोषणा CGU_REG_MACCDR		0x54
#घोषणा CGU_REG_I2SCDR		0x60
#घोषणा CGU_REG_LPCDR		0x64
#घोषणा CGU_REG_MSC0CDR		0x68
#घोषणा CGU_REG_I2SCDR1		0x70
#घोषणा CGU_REG_SSICDR		0x74
#घोषणा CGU_REG_CIMCDR		0x7c
#घोषणा CGU_REG_PCMCDR		0x84
#घोषणा CGU_REG_MSC1CDR		0xa4
#घोषणा CGU_REG_CMP_INTR	0xb0
#घोषणा CGU_REG_CMP_INTRE	0xb4
#घोषणा CGU_REG_DRCG		0xd0
#घोषणा CGU_REG_CPCSR		0xd4
#घोषणा CGU_REG_PCMCDR1		0xe0
#घोषणा CGU_REG_MACPHYC		0xe8

/* bits within the OPCR रेजिस्टर */
#घोषणा OPCR_SPENDN0		BIT(7)
#घोषणा OPCR_SPENDN1		BIT(6)

/* bits within the USBPCR रेजिस्टर */
#घोषणा USBPCR_SIDDQ		BIT(21)
#घोषणा USBPCR_OTG_DISABLE	BIT(20)

/* bits within the USBPCR1 रेजिस्टर */
#घोषणा USBPCR1_REFCLKSEL_SHIFT	26
#घोषणा USBPCR1_REFCLKSEL_MASK	(0x3 << USBPCR1_REFCLKSEL_SHIFT)
#घोषणा USBPCR1_REFCLKSEL_CORE	(0x2 << USBPCR1_REFCLKSEL_SHIFT)
#घोषणा USBPCR1_REFCLKDIV_SHIFT	24
#घोषणा USBPCR1_REFCLKDIV_MASK	(0x3 << USBPCR1_REFCLKDIV_SHIFT)
#घोषणा USBPCR1_REFCLKDIV_48	(0x2 << USBPCR1_REFCLKDIV_SHIFT)
#घोषणा USBPCR1_REFCLKDIV_24	(0x1 << USBPCR1_REFCLKDIV_SHIFT)
#घोषणा USBPCR1_REFCLKDIV_12	(0x0 << USBPCR1_REFCLKDIV_SHIFT)

अटल काष्ठा ingenic_cgu *cgu;

अटल अचिन्हित दीर्घ x1000_otg_phy_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	u32 usbpcr1;
	अचिन्हित refclk_भाग;

	usbpcr1 = पढ़ोl(cgu->base + CGU_REG_USBPCR1);
	refclk_भाग = usbpcr1 & USBPCR1_REFCLKDIV_MASK;

	चयन (refclk_भाग) अणु
	हाल USBPCR1_REFCLKDIV_12:
		वापस 12000000;

	हाल USBPCR1_REFCLKDIV_24:
		वापस 24000000;

	हाल USBPCR1_REFCLKDIV_48:
		वापस 48000000;
	पूर्ण

	वापस parent_rate;
पूर्ण

अटल दीर्घ x1000_otg_phy_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ req_rate,
				      अचिन्हित दीर्घ *parent_rate)
अणु
	अगर (req_rate < 18000000)
		वापस 12000000;

	अगर (req_rate < 36000000)
		वापस 24000000;

	वापस 48000000;
पूर्ण

अटल पूर्णांक x1000_otg_phy_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ req_rate,
				   अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ flags;
	u32 usbpcr1, भाग_bits;

	चयन (req_rate) अणु
	हाल 12000000:
		भाग_bits = USBPCR1_REFCLKDIV_12;
		अवरोध;

	हाल 24000000:
		भाग_bits = USBPCR1_REFCLKDIV_24;
		अवरोध;

	हाल 48000000:
		भाग_bits = USBPCR1_REFCLKDIV_48;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&cgu->lock, flags);

	usbpcr1 = पढ़ोl(cgu->base + CGU_REG_USBPCR1);
	usbpcr1 &= ~USBPCR1_REFCLKDIV_MASK;
	usbpcr1 |= भाग_bits;
	ग_लिखोl(usbpcr1, cgu->base + CGU_REG_USBPCR1);

	spin_unlock_irqrestore(&cgu->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक x1000_usb_phy_enable(काष्ठा clk_hw *hw)
अणु
	व्योम __iomem *reg_opcr		= cgu->base + CGU_REG_OPCR;
	व्योम __iomem *reg_usbpcr	= cgu->base + CGU_REG_USBPCR;

	ग_लिखोl(पढ़ोl(reg_opcr) | OPCR_SPENDN0, reg_opcr);
	ग_लिखोl(पढ़ोl(reg_usbpcr) & ~USBPCR_OTG_DISABLE & ~USBPCR_SIDDQ, reg_usbpcr);
	वापस 0;
पूर्ण

अटल व्योम x1000_usb_phy_disable(काष्ठा clk_hw *hw)
अणु
	व्योम __iomem *reg_opcr		= cgu->base + CGU_REG_OPCR;
	व्योम __iomem *reg_usbpcr	= cgu->base + CGU_REG_USBPCR;

	ग_लिखोl(पढ़ोl(reg_opcr) & ~OPCR_SPENDN0, reg_opcr);
	ग_लिखोl(पढ़ोl(reg_usbpcr) | USBPCR_OTG_DISABLE | USBPCR_SIDDQ, reg_usbpcr);
पूर्ण

अटल पूर्णांक x1000_usb_phy_is_enabled(काष्ठा clk_hw *hw)
अणु
	व्योम __iomem *reg_opcr		= cgu->base + CGU_REG_OPCR;
	व्योम __iomem *reg_usbpcr	= cgu->base + CGU_REG_USBPCR;

	वापस (पढ़ोl(reg_opcr) & OPCR_SPENDN0) &&
		!(पढ़ोl(reg_usbpcr) & USBPCR_SIDDQ) &&
		!(पढ़ोl(reg_usbpcr) & USBPCR_OTG_DISABLE);
पूर्ण

अटल स्थिर काष्ठा clk_ops x1000_otg_phy_ops = अणु
	.recalc_rate = x1000_otg_phy_recalc_rate,
	.round_rate = x1000_otg_phy_round_rate,
	.set_rate = x1000_otg_phy_set_rate,

	.enable		= x1000_usb_phy_enable,
	.disable	= x1000_usb_phy_disable,
	.is_enabled	= x1000_usb_phy_is_enabled,
पूर्ण;

अटल स्थिर s8 pll_od_encoding[8] = अणु
	0x0, 0x1, -1, 0x2, -1, -1, -1, 0x3,
पूर्ण;

अटल स्थिर काष्ठा ingenic_cgu_clk_info x1000_cgu_घड़ीs[] = अणु

	/* External घड़ीs */

	[X1000_CLK_EXCLK] = अणु "ext", CGU_CLK_EXT पूर्ण,
	[X1000_CLK_RTCLK] = अणु "rtc", CGU_CLK_EXT पूर्ण,

	/* PLLs */

	[X1000_CLK_APLL] = अणु
		"apll", CGU_CLK_PLL,
		.parents = अणु X1000_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.pll = अणु
			.reg = CGU_REG_APLL,
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
			.bypass_reg = CGU_REG_APLL,
			.bypass_bit = 9,
			.enable_bit = 8,
			.stable_bit = 10,
		पूर्ण,
	पूर्ण,

	[X1000_CLK_MPLL] = अणु
		"mpll", CGU_CLK_PLL,
		.parents = अणु X1000_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.pll = अणु
			.reg = CGU_REG_MPLL,
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
			.bypass_reg = CGU_REG_MPLL,
			.bypass_bit = 6,
			.enable_bit = 7,
			.stable_bit = 0,
		पूर्ण,
	पूर्ण,

	/* Custom (SoC-specअगरic) OTG PHY */

	[X1000_CLK_OTGPHY] = अणु
		"otg_phy", CGU_CLK_CUSTOM,
		.parents = अणु -1, -1, X1000_CLK_EXCLK, -1 पूर्ण,
		.custom = अणु &x1000_otg_phy_ops पूर्ण,
	पूर्ण,

	/* Muxes & भागiders */

	[X1000_CLK_SCLKA] = अणु
		"sclk_a", CGU_CLK_MUX,
		.parents = अणु -1, X1000_CLK_EXCLK, X1000_CLK_APLL, -1 पूर्ण,
		.mux = अणु CGU_REG_CPCCR, 30, 2 पूर्ण,
	पूर्ण,

	[X1000_CLK_CPUMUX] = अणु
		"cpu_mux", CGU_CLK_MUX,
		.parents = अणु -1, X1000_CLK_SCLKA, X1000_CLK_MPLL, -1 पूर्ण,
		.mux = अणु CGU_REG_CPCCR, 28, 2 पूर्ण,
	पूर्ण,

	[X1000_CLK_CPU] = अणु
		"cpu", CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु X1000_CLK_CPUMUX, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_CPCCR, 0, 1, 4, 22, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 30 पूर्ण,
	पूर्ण,

	[X1000_CLK_L2CACHE] = अणु
		"l2cache", CGU_CLK_DIV,
		.parents = अणु X1000_CLK_CPUMUX, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_CPCCR, 4, 1, 4, 22, -1, -1 पूर्ण,
	पूर्ण,

	[X1000_CLK_AHB0] = अणु
		"ahb0", CGU_CLK_MUX | CGU_CLK_DIV,
		.parents = अणु -1, X1000_CLK_SCLKA, X1000_CLK_MPLL, -1 पूर्ण,
		.mux = अणु CGU_REG_CPCCR, 26, 2 पूर्ण,
		.भाग = अणु CGU_REG_CPCCR, 8, 1, 4, 21, -1, -1 पूर्ण,
	पूर्ण,

	[X1000_CLK_AHB2PMUX] = अणु
		"ahb2_apb_mux", CGU_CLK_MUX,
		.parents = अणु -1, X1000_CLK_SCLKA, X1000_CLK_MPLL, -1 पूर्ण,
		.mux = अणु CGU_REG_CPCCR, 24, 2 पूर्ण,
	पूर्ण,

	[X1000_CLK_AHB2] = अणु
		"ahb2", CGU_CLK_DIV,
		.parents = अणु X1000_CLK_AHB2PMUX, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_CPCCR, 12, 1, 4, 20, -1, -1 पूर्ण,
	पूर्ण,

	[X1000_CLK_PCLK] = अणु
		"pclk", CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु X1000_CLK_AHB2PMUX, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_CPCCR, 16, 1, 4, 20, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 28 पूर्ण,
	पूर्ण,

	[X1000_CLK_DDR] = अणु
		"ddr", CGU_CLK_MUX | CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु -1, X1000_CLK_SCLKA, X1000_CLK_MPLL, -1 पूर्ण,
		.mux = अणु CGU_REG_DDRCDR, 30, 2 पूर्ण,
		.भाग = अणु CGU_REG_DDRCDR, 0, 1, 4, 29, 28, 27 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 31 पूर्ण,
	पूर्ण,

	[X1000_CLK_MAC] = अणु
		"mac", CGU_CLK_MUX | CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु X1000_CLK_SCLKA, X1000_CLK_MPLL पूर्ण,
		.mux = अणु CGU_REG_MACCDR, 31, 1 पूर्ण,
		.भाग = अणु CGU_REG_MACCDR, 0, 1, 8, 29, 28, 27 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 25 पूर्ण,
	पूर्ण,

	[X1000_CLK_LCD] = अणु
		"lcd", CGU_CLK_MUX | CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु X1000_CLK_SCLKA, X1000_CLK_MPLL पूर्ण,
		.mux = अणु CGU_REG_LPCDR, 31, 1 पूर्ण,
		.भाग = अणु CGU_REG_LPCDR, 0, 1, 8, 28, 27, 26 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 23 पूर्ण,
	पूर्ण,

	[X1000_CLK_MSCMUX] = अणु
		"msc_mux", CGU_CLK_MUX,
		.parents = अणु X1000_CLK_SCLKA, X1000_CLK_MPLLपूर्ण,
		.mux = अणु CGU_REG_MSC0CDR, 31, 1 पूर्ण,
	पूर्ण,

	[X1000_CLK_MSC0] = अणु
		"msc0", CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु X1000_CLK_MSCMUX, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_MSC0CDR, 0, 2, 8, 29, 28, 27 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 4 पूर्ण,
	पूर्ण,

	[X1000_CLK_MSC1] = अणु
		"msc1", CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु X1000_CLK_MSCMUX, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_MSC1CDR, 0, 2, 8, 29, 28, 27 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 5 पूर्ण,
	पूर्ण,

	[X1000_CLK_OTG] = अणु
		"otg", CGU_CLK_DIV | CGU_CLK_GATE | CGU_CLK_MUX,
		.parents = अणु X1000_CLK_EXCLK, -1,
					 X1000_CLK_APLL, X1000_CLK_MPLL पूर्ण,
		.mux = अणु CGU_REG_USBCDR, 30, 2 पूर्ण,
		.भाग = अणु CGU_REG_USBCDR, 0, 1, 8, 29, 28, 27 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 3 पूर्ण,
	पूर्ण,

	[X1000_CLK_SSIPLL] = अणु
		"ssi_pll", CGU_CLK_MUX | CGU_CLK_DIV,
		.parents = अणु X1000_CLK_SCLKA, X1000_CLK_MPLL, -1, -1 पूर्ण,
		.mux = अणु CGU_REG_SSICDR, 31, 1 पूर्ण,
		.भाग = अणु CGU_REG_SSICDR, 0, 1, 8, 29, 28, 27 पूर्ण,
	पूर्ण,

	[X1000_CLK_SSIPLL_DIV2] = अणु
		"ssi_pll_div2", CGU_CLK_FIXDIV,
		.parents = अणु X1000_CLK_SSIPLL पूर्ण,
		.fixभाग = अणु 2 पूर्ण,
	पूर्ण,

	[X1000_CLK_SSIMUX] = अणु
		"ssi_mux", CGU_CLK_MUX,
		.parents = अणु X1000_CLK_EXCLK, X1000_CLK_SSIPLL_DIV2, -1, -1 पूर्ण,
		.mux = अणु CGU_REG_SSICDR, 30, 1 पूर्ण,
	पूर्ण,

	[X1000_CLK_EXCLK_DIV512] = अणु
		"exclk_div512", CGU_CLK_FIXDIV,
		.parents = अणु X1000_CLK_EXCLK पूर्ण,
		.fixभाग = अणु 512 पूर्ण,
	पूर्ण,

	[X1000_CLK_RTC] = अणु
		"rtc_ercs", CGU_CLK_MUX | CGU_CLK_GATE,
		.parents = अणु X1000_CLK_EXCLK_DIV512, X1000_CLK_RTCLK पूर्ण,
		.mux = अणु CGU_REG_OPCR, 2, 1पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 27 पूर्ण,
	पूर्ण,

	/* Gate-only घड़ीs */

	[X1000_CLK_EMC] = अणु
		"emc", CGU_CLK_GATE,
		.parents = अणु X1000_CLK_AHB2, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 0 पूर्ण,
	पूर्ण,

	[X1000_CLK_EFUSE] = अणु
		"efuse", CGU_CLK_GATE,
		.parents = अणु X1000_CLK_AHB2, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 1 पूर्ण,
	पूर्ण,

	[X1000_CLK_SFC] = अणु
		"sfc", CGU_CLK_GATE,
		.parents = अणु X1000_CLK_SSIPLL, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 2 पूर्ण,
	पूर्ण,

	[X1000_CLK_I2C0] = अणु
		"i2c0", CGU_CLK_GATE,
		.parents = अणु X1000_CLK_PCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 7 पूर्ण,
	पूर्ण,

	[X1000_CLK_I2C1] = अणु
		"i2c1", CGU_CLK_GATE,
		.parents = अणु X1000_CLK_PCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 8 पूर्ण,
	पूर्ण,

	[X1000_CLK_I2C2] = अणु
		"i2c2", CGU_CLK_GATE,
		.parents = अणु X1000_CLK_PCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 9 पूर्ण,
	पूर्ण,

	[X1000_CLK_UART0] = अणु
		"uart0", CGU_CLK_GATE,
		.parents = अणु X1000_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 14 पूर्ण,
	पूर्ण,

	[X1000_CLK_UART1] = अणु
		"uart1", CGU_CLK_GATE,
		.parents = अणु X1000_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 15 पूर्ण,
	पूर्ण,

	[X1000_CLK_UART2] = अणु
		"uart2", CGU_CLK_GATE,
		.parents = अणु X1000_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 16 पूर्ण,
	पूर्ण,

	[X1000_CLK_TCU] = अणु
		"tcu", CGU_CLK_GATE,
		.parents = अणु X1000_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 18 पूर्ण,
	पूर्ण,

	[X1000_CLK_SSI] = अणु
		"ssi", CGU_CLK_GATE,
		.parents = अणु X1000_CLK_SSIMUX, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 19 पूर्ण,
	पूर्ण,

	[X1000_CLK_OST] = अणु
		"ost", CGU_CLK_GATE,
		.parents = अणु X1000_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 20 पूर्ण,
	पूर्ण,

	[X1000_CLK_PDMA] = अणु
		"pdma", CGU_CLK_GATE,
		.parents = अणु X1000_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR, 21 पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init x1000_cgu_init(काष्ठा device_node *np)
अणु
	पूर्णांक retval;

	cgu = ingenic_cgu_new(x1000_cgu_घड़ीs,
			      ARRAY_SIZE(x1000_cgu_घड़ीs), np);
	अगर (!cgu) अणु
		pr_err("%s: failed to initialise CGU\n", __func__);
		वापस;
	पूर्ण

	retval = ingenic_cgu_रेजिस्टर_घड़ीs(cgu);
	अगर (retval) अणु
		pr_err("%s: failed to register CGU Clocks\n", __func__);
		वापस;
	पूर्ण

	ingenic_cgu_रेजिस्टर_syscore_ops(cgu);
पूर्ण
/*
 * CGU has some children devices, this is useful क्रम probing children devices
 * in the हाल where the device node is compatible with "simple-mfd".
 */
CLK_OF_DECLARE_DRIVER(x1000_cgu, "ingenic,x1000-cgu", x1000_cgu_init);
