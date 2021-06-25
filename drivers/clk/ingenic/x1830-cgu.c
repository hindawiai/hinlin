<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * X1830 SoC CGU driver
 * Copyright (c) 2019 ोउॉओौओ (Zhou Yanjie) <zhouyanjie@wanyeetech.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>

#समावेश <dt-bindings/घड़ी/x1830-cgu.h>

#समावेश "cgu.h"
#समावेश "pm.h"

/* CGU रेजिस्टर offsets */
#घोषणा CGU_REG_CPCCR		0x00
#घोषणा CGU_REG_CPPCR		0x0c
#घोषणा CGU_REG_APLL		0x10
#घोषणा CGU_REG_MPLL		0x14
#घोषणा CGU_REG_CLKGR0		0x20
#घोषणा CGU_REG_OPCR		0x24
#घोषणा CGU_REG_CLKGR1		0x28
#घोषणा CGU_REG_DDRCDR		0x2c
#घोषणा CGU_REG_USBPCR		0x3c
#घोषणा CGU_REG_USBRDT		0x40
#घोषणा CGU_REG_USBVBFIL	0x44
#घोषणा CGU_REG_USBPCR1		0x48
#घोषणा CGU_REG_MACCDR		0x54
#घोषणा CGU_REG_EPLL		0x58
#घोषणा CGU_REG_I2SCDR		0x60
#घोषणा CGU_REG_LPCDR		0x64
#घोषणा CGU_REG_MSC0CDR		0x68
#घोषणा CGU_REG_I2SCDR1		0x70
#घोषणा CGU_REG_SSICDR		0x74
#घोषणा CGU_REG_CIMCDR		0x7c
#घोषणा CGU_REG_MSC1CDR		0xa4
#घोषणा CGU_REG_CMP_INTR	0xb0
#घोषणा CGU_REG_CMP_INTRE	0xb4
#घोषणा CGU_REG_DRCG		0xd0
#घोषणा CGU_REG_CPCSR		0xd4
#घोषणा CGU_REG_VPLL		0xe0
#घोषणा CGU_REG_MACPHYC		0xe8

/* bits within the OPCR रेजिस्टर */
#घोषणा OPCR_GATE_USBPHYCLK	BIT(23)
#घोषणा OPCR_SPENDN0		BIT(7)
#घोषणा OPCR_SPENDN1		BIT(6)

/* bits within the USBPCR रेजिस्टर */
#घोषणा USBPCR_SIDDQ		BIT(21)
#घोषणा USBPCR_OTG_DISABLE	BIT(20)

अटल काष्ठा ingenic_cgu *cgu;

अटल पूर्णांक x1830_usb_phy_enable(काष्ठा clk_hw *hw)
अणु
	व्योम __iomem *reg_opcr		= cgu->base + CGU_REG_OPCR;
	व्योम __iomem *reg_usbpcr	= cgu->base + CGU_REG_USBPCR;

	ग_लिखोl((पढ़ोl(reg_opcr) | OPCR_SPENDN0) & ~OPCR_GATE_USBPHYCLK, reg_opcr);
	ग_लिखोl(पढ़ोl(reg_usbpcr) & ~USBPCR_OTG_DISABLE & ~USBPCR_SIDDQ, reg_usbpcr);
	वापस 0;
पूर्ण

अटल व्योम x1830_usb_phy_disable(काष्ठा clk_hw *hw)
अणु
	व्योम __iomem *reg_opcr		= cgu->base + CGU_REG_OPCR;
	व्योम __iomem *reg_usbpcr	= cgu->base + CGU_REG_USBPCR;

	ग_लिखोl((पढ़ोl(reg_opcr) & ~OPCR_SPENDN0) | OPCR_GATE_USBPHYCLK, reg_opcr);
	ग_लिखोl(पढ़ोl(reg_usbpcr) | USBPCR_OTG_DISABLE | USBPCR_SIDDQ, reg_usbpcr);
पूर्ण

अटल पूर्णांक x1830_usb_phy_is_enabled(काष्ठा clk_hw *hw)
अणु
	व्योम __iomem *reg_opcr		= cgu->base + CGU_REG_OPCR;
	व्योम __iomem *reg_usbpcr	= cgu->base + CGU_REG_USBPCR;

	वापस (पढ़ोl(reg_opcr) & OPCR_SPENDN0) &&
		!(पढ़ोl(reg_usbpcr) & USBPCR_SIDDQ) &&
		!(पढ़ोl(reg_usbpcr) & USBPCR_OTG_DISABLE);
पूर्ण

अटल स्थिर काष्ठा clk_ops x1830_otg_phy_ops = अणु
	.enable		= x1830_usb_phy_enable,
	.disable	= x1830_usb_phy_disable,
	.is_enabled	= x1830_usb_phy_is_enabled,
पूर्ण;

अटल स्थिर s8 pll_od_encoding[64] = अणु
	0x0, 0x1,  -1, 0x2,  -1,  -1,  -1, 0x3,
	 -1,  -1,  -1,  -1,  -1,  -1,  -1, 0x4,
	 -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	 -1,  -1,  -1,  -1,  -1,  -1,  -1, 0x5,
	 -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	 -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	 -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	 -1,  -1,  -1,  -1,  -1,  -1,  -1, 0x6,
पूर्ण;

अटल स्थिर काष्ठा ingenic_cgu_clk_info x1830_cgu_घड़ीs[] = अणु

	/* External घड़ीs */

	[X1830_CLK_EXCLK] = अणु "ext", CGU_CLK_EXT पूर्ण,
	[X1830_CLK_RTCLK] = अणु "rtc", CGU_CLK_EXT पूर्ण,

	/* PLLs */

	[X1830_CLK_APLL] = अणु
		"apll", CGU_CLK_PLL,
		.parents = अणु X1830_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.pll = अणु
			.reg = CGU_REG_APLL,
			.rate_multiplier = 2,
			.m_shअगरt = 20,
			.m_bits = 9,
			.m_offset = 1,
			.n_shअगरt = 14,
			.n_bits = 6,
			.n_offset = 1,
			.od_shअगरt = 11,
			.od_bits = 3,
			.od_max = 64,
			.od_encoding = pll_od_encoding,
			.bypass_reg = CGU_REG_CPPCR,
			.bypass_bit = 30,
			.enable_bit = 0,
			.stable_bit = 3,
		पूर्ण,
	पूर्ण,

	[X1830_CLK_MPLL] = अणु
		"mpll", CGU_CLK_PLL,
		.parents = अणु X1830_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.pll = अणु
			.reg = CGU_REG_MPLL,
			.rate_multiplier = 2,
			.m_shअगरt = 20,
			.m_bits = 9,
			.m_offset = 1,
			.n_shअगरt = 14,
			.n_bits = 6,
			.n_offset = 1,
			.od_shअगरt = 11,
			.od_bits = 3,
			.od_max = 64,
			.od_encoding = pll_od_encoding,
			.bypass_reg = CGU_REG_CPPCR,
			.bypass_bit = 28,
			.enable_bit = 0,
			.stable_bit = 3,
		पूर्ण,
	पूर्ण,

	[X1830_CLK_EPLL] = अणु
		"epll", CGU_CLK_PLL,
		.parents = अणु X1830_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.pll = अणु
			.reg = CGU_REG_EPLL,
			.rate_multiplier = 2,
			.m_shअगरt = 20,
			.m_bits = 9,
			.m_offset = 1,
			.n_shअगरt = 14,
			.n_bits = 6,
			.n_offset = 1,
			.od_shअगरt = 11,
			.od_bits = 3,
			.od_max = 64,
			.od_encoding = pll_od_encoding,
			.bypass_reg = CGU_REG_CPPCR,
			.bypass_bit = 24,
			.enable_bit = 0,
			.stable_bit = 3,
		पूर्ण,
	पूर्ण,

	[X1830_CLK_VPLL] = अणु
		"vpll", CGU_CLK_PLL,
		.parents = अणु X1830_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.pll = अणु
			.reg = CGU_REG_VPLL,
			.rate_multiplier = 2,
			.m_shअगरt = 20,
			.m_bits = 9,
			.m_offset = 1,
			.n_shअगरt = 14,
			.n_bits = 6,
			.n_offset = 1,
			.od_shअगरt = 11,
			.od_bits = 3,
			.od_max = 64,
			.od_encoding = pll_od_encoding,
			.bypass_reg = CGU_REG_CPPCR,
			.bypass_bit = 26,
			.enable_bit = 0,
			.stable_bit = 3,
		पूर्ण,
	पूर्ण,

	/* Custom (SoC-specअगरic) OTG PHY */

	[X1830_CLK_OTGPHY] = अणु
		"otg_phy", CGU_CLK_CUSTOM,
		.parents = अणु X1830_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.custom = अणु &x1830_otg_phy_ops पूर्ण,
	पूर्ण,

	/* Muxes & भागiders */

	[X1830_CLK_SCLKA] = अणु
		"sclk_a", CGU_CLK_MUX,
		.parents = अणु -1, X1830_CLK_EXCLK, X1830_CLK_APLL, -1 पूर्ण,
		.mux = अणु CGU_REG_CPCCR, 30, 2 पूर्ण,
	पूर्ण,

	[X1830_CLK_CPUMUX] = अणु
		"cpu_mux", CGU_CLK_MUX,
		.parents = अणु -1, X1830_CLK_SCLKA, X1830_CLK_MPLL, -1 पूर्ण,
		.mux = अणु CGU_REG_CPCCR, 28, 2 पूर्ण,
	पूर्ण,

	[X1830_CLK_CPU] = अणु
		"cpu", CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु X1830_CLK_CPUMUX, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_CPCCR, 0, 1, 4, 22, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 15 पूर्ण,
	पूर्ण,

	[X1830_CLK_L2CACHE] = अणु
		"l2cache", CGU_CLK_DIV,
		.parents = अणु X1830_CLK_CPUMUX, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_CPCCR, 4, 1, 4, 22, -1, -1 पूर्ण,
	पूर्ण,

	[X1830_CLK_AHB0] = अणु
		"ahb0", CGU_CLK_MUX | CGU_CLK_DIV,
		.parents = अणु -1, X1830_CLK_SCLKA, X1830_CLK_MPLL, -1 पूर्ण,
		.mux = अणु CGU_REG_CPCCR, 26, 2 पूर्ण,
		.भाग = अणु CGU_REG_CPCCR, 8, 1, 4, 21, -1, -1 पूर्ण,
	पूर्ण,

	[X1830_CLK_AHB2PMUX] = अणु
		"ahb2_apb_mux", CGU_CLK_MUX,
		.parents = अणु -1, X1830_CLK_SCLKA, X1830_CLK_MPLL, -1 पूर्ण,
		.mux = अणु CGU_REG_CPCCR, 24, 2 पूर्ण,
	पूर्ण,

	[X1830_CLK_AHB2] = अणु
		"ahb2", CGU_CLK_DIV,
		.parents = अणु X1830_CLK_AHB2PMUX, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_CPCCR, 12, 1, 4, 20, -1, -1 पूर्ण,
	पूर्ण,

	[X1830_CLK_PCLK] = अणु
		"pclk", CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु X1830_CLK_AHB2PMUX, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_CPCCR, 16, 1, 4, 20, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 14 पूर्ण,
	पूर्ण,

	[X1830_CLK_DDR] = अणु
		"ddr", CGU_CLK_MUX | CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु -1, X1830_CLK_SCLKA, X1830_CLK_MPLL, -1 पूर्ण,
		.mux = अणु CGU_REG_DDRCDR, 30, 2 पूर्ण,
		.भाग = अणु CGU_REG_DDRCDR, 0, 1, 4, 29, 28, 27 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 31 पूर्ण,
	पूर्ण,

	[X1830_CLK_MAC] = अणु
		"mac", CGU_CLK_MUX | CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु X1830_CLK_SCLKA, X1830_CLK_MPLL,
					 X1830_CLK_VPLL, X1830_CLK_EPLL पूर्ण,
		.mux = अणु CGU_REG_MACCDR, 30, 2 पूर्ण,
		.भाग = अणु CGU_REG_MACCDR, 0, 1, 8, 29, 28, 27 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 4 पूर्ण,
	पूर्ण,

	[X1830_CLK_LCD] = अणु
		"lcd", CGU_CLK_MUX | CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु X1830_CLK_SCLKA, X1830_CLK_MPLL,
					 X1830_CLK_VPLL, X1830_CLK_EPLL पूर्ण,
		.mux = अणु CGU_REG_LPCDR, 30, 2 पूर्ण,
		.भाग = अणु CGU_REG_LPCDR, 0, 1, 8, 28, 27, 26 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 9 पूर्ण,
	पूर्ण,

	[X1830_CLK_MSCMUX] = अणु
		"msc_mux", CGU_CLK_MUX,
		.parents = अणु X1830_CLK_SCLKA, X1830_CLK_MPLL,
					 X1830_CLK_VPLL, X1830_CLK_EPLL पूर्ण,
		.mux = अणु CGU_REG_MSC0CDR, 30, 2 पूर्ण,
	पूर्ण,

	[X1830_CLK_MSC0] = अणु
		"msc0", CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु X1830_CLK_MSCMUX, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_MSC0CDR, 0, 2, 8, 29, 28, 27 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 4 पूर्ण,
	पूर्ण,

	[X1830_CLK_MSC1] = अणु
		"msc1", CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु X1830_CLK_MSCMUX, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_MSC1CDR, 0, 2, 8, 29, 28, 27 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 5 पूर्ण,
	पूर्ण,

	[X1830_CLK_SSIPLL] = अणु
		"ssi_pll", CGU_CLK_MUX | CGU_CLK_DIV,
		.parents = अणु X1830_CLK_SCLKA, X1830_CLK_MPLL,
					 X1830_CLK_VPLL, X1830_CLK_EPLL पूर्ण,
		.mux = अणु CGU_REG_SSICDR, 30, 2 पूर्ण,
		.भाग = अणु CGU_REG_SSICDR, 0, 1, 8, 28, 27, 26 पूर्ण,
	पूर्ण,

	[X1830_CLK_SSIPLL_DIV2] = अणु
		"ssi_pll_div2", CGU_CLK_FIXDIV,
		.parents = अणु X1830_CLK_SSIPLL पूर्ण,
		.fixभाग = अणु 2 पूर्ण,
	पूर्ण,

	[X1830_CLK_SSIMUX] = अणु
		"ssi_mux", CGU_CLK_MUX,
		.parents = अणु X1830_CLK_EXCLK, X1830_CLK_SSIPLL_DIV2, -1, -1 पूर्ण,
		.mux = अणु CGU_REG_SSICDR, 29, 1 पूर्ण,
	पूर्ण,

	[X1830_CLK_EXCLK_DIV512] = अणु
		"exclk_div512", CGU_CLK_FIXDIV,
		.parents = अणु X1830_CLK_EXCLK पूर्ण,
		.fixभाग = अणु 512 पूर्ण,
	पूर्ण,

	[X1830_CLK_RTC] = अणु
		"rtc_ercs", CGU_CLK_MUX | CGU_CLK_GATE,
		.parents = अणु X1830_CLK_EXCLK_DIV512, X1830_CLK_RTCLK पूर्ण,
		.mux = अणु CGU_REG_OPCR, 2, 1पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 29 पूर्ण,
	पूर्ण,

	/* Gate-only घड़ीs */

	[X1830_CLK_EMC] = अणु
		"emc", CGU_CLK_GATE,
		.parents = अणु X1830_CLK_AHB2, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 0 पूर्ण,
	पूर्ण,

	[X1830_CLK_EFUSE] = अणु
		"efuse", CGU_CLK_GATE,
		.parents = अणु X1830_CLK_AHB2, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 1 पूर्ण,
	पूर्ण,

	[X1830_CLK_OTG] = अणु
		"otg", CGU_CLK_GATE,
		.parents = अणु X1830_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 3 पूर्ण,
	पूर्ण,

	[X1830_CLK_SSI0] = अणु
		"ssi0", CGU_CLK_GATE,
		.parents = अणु X1830_CLK_SSIMUX, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 6 पूर्ण,
	पूर्ण,

	[X1830_CLK_SMB0] = अणु
		"smb0", CGU_CLK_GATE,
		.parents = अणु X1830_CLK_PCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 7 पूर्ण,
	पूर्ण,

	[X1830_CLK_SMB1] = अणु
		"smb1", CGU_CLK_GATE,
		.parents = अणु X1830_CLK_PCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 8 पूर्ण,
	पूर्ण,

	[X1830_CLK_SMB2] = अणु
		"smb2", CGU_CLK_GATE,
		.parents = अणु X1830_CLK_PCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 9 पूर्ण,
	पूर्ण,

	[X1830_CLK_UART0] = अणु
		"uart0", CGU_CLK_GATE,
		.parents = अणु X1830_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 14 पूर्ण,
	पूर्ण,

	[X1830_CLK_UART1] = अणु
		"uart1", CGU_CLK_GATE,
		.parents = अणु X1830_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 15 पूर्ण,
	पूर्ण,

	[X1830_CLK_SSI1] = अणु
		"ssi1", CGU_CLK_GATE,
		.parents = अणु X1830_CLK_SSIMUX, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 19 पूर्ण,
	पूर्ण,

	[X1830_CLK_SFC] = अणु
		"sfc", CGU_CLK_GATE,
		.parents = अणु X1830_CLK_SSIPLL, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 20 पूर्ण,
	पूर्ण,

	[X1830_CLK_PDMA] = अणु
		"pdma", CGU_CLK_GATE,
		.parents = अणु X1830_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 21 पूर्ण,
	पूर्ण,

	[X1830_CLK_TCU] = अणु
		"tcu", CGU_CLK_GATE,
		.parents = अणु X1830_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 30 पूर्ण,
	पूर्ण,

	[X1830_CLK_DTRNG] = अणु
		"dtrng", CGU_CLK_GATE,
		.parents = अणु X1830_CLK_PCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 1 पूर्ण,
	पूर्ण,

	[X1830_CLK_OST] = अणु
		"ost", CGU_CLK_GATE,
		.parents = अणु X1830_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 11 पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init x1830_cgu_init(काष्ठा device_node *np)
अणु
	पूर्णांक retval;

	cgu = ingenic_cgu_new(x1830_cgu_घड़ीs,
			      ARRAY_SIZE(x1830_cgu_घड़ीs), np);
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
CLK_OF_DECLARE_DRIVER(x1830_cgu, "ingenic,x1830-cgu", x1830_cgu_init);
