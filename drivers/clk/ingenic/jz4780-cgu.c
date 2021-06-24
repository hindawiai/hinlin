<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Ingenic JZ4780 SoC CGU driver
 *
 * Copyright (c) 2013-2015 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 * Copyright (c) 2020 ोउॉओौओ (Zhou Yanjie) <zhouyanjie@wanyeetech.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/of.h>

#समावेश <dt-bindings/घड़ी/jz4780-cgu.h>

#समावेश "cgu.h"
#समावेश "pm.h"

/* CGU रेजिस्टर offsets */
#घोषणा CGU_REG_CLOCKCONTROL	0x00
#घोषणा CGU_REG_LCR				0x04
#घोषणा CGU_REG_APLL			0x10
#घोषणा CGU_REG_MPLL			0x14
#घोषणा CGU_REG_EPLL			0x18
#घोषणा CGU_REG_VPLL			0x1c
#घोषणा CGU_REG_CLKGR0			0x20
#घोषणा CGU_REG_OPCR			0x24
#घोषणा CGU_REG_CLKGR1			0x28
#घोषणा CGU_REG_DDRCDR			0x2c
#घोषणा CGU_REG_VPUCDR			0x30
#घोषणा CGU_REG_USBPCR			0x3c
#घोषणा CGU_REG_USBRDT			0x40
#घोषणा CGU_REG_USBVBFIL		0x44
#घोषणा CGU_REG_USBPCR1			0x48
#घोषणा CGU_REG_LP0CDR			0x54
#घोषणा CGU_REG_I2SCDR			0x60
#घोषणा CGU_REG_LP1CDR			0x64
#घोषणा CGU_REG_MSC0CDR			0x68
#घोषणा CGU_REG_UHCCDR			0x6c
#घोषणा CGU_REG_SSICDR			0x74
#घोषणा CGU_REG_CIMCDR			0x7c
#घोषणा CGU_REG_PCMCDR			0x84
#घोषणा CGU_REG_GPUCDR			0x88
#घोषणा CGU_REG_HDMICDR			0x8c
#घोषणा CGU_REG_MSC1CDR			0xa4
#घोषणा CGU_REG_MSC2CDR			0xa8
#घोषणा CGU_REG_BCHCDR			0xac
#घोषणा CGU_REG_CLOCKSTATUS		0xd4

/* bits within the OPCR रेजिस्टर */
#घोषणा OPCR_SPENDN0			BIT(7)
#घोषणा OPCR_SPENDN1			BIT(6)

/* bits within the USBPCR रेजिस्टर */
#घोषणा USBPCR_USB_MODE			BIT(31)
#घोषणा USBPCR_IDPULLUP_MASK	(0x3 << 28)
#घोषणा USBPCR_COMMONONN		BIT(25)
#घोषणा USBPCR_VBUSVLDEXT		BIT(24)
#घोषणा USBPCR_VBUSVLDEXTSEL	BIT(23)
#घोषणा USBPCR_POR				BIT(22)
#घोषणा USBPCR_SIDDQ			BIT(21)
#घोषणा USBPCR_OTG_DISABLE		BIT(20)
#घोषणा USBPCR_COMPDISTUNE_MASK	(0x7 << 17)
#घोषणा USBPCR_OTGTUNE_MASK		(0x7 << 14)
#घोषणा USBPCR_SQRXTUNE_MASK	(0x7 << 11)
#घोषणा USBPCR_TXFSLSTUNE_MASK	(0xf << 7)
#घोषणा USBPCR_TXPREEMPHTUNE	BIT(6)
#घोषणा USBPCR_TXHSXVTUNE_MASK	(0x3 << 4)
#घोषणा USBPCR_TXVREFTUNE_MASK	0xf

/* bits within the USBPCR1 रेजिस्टर */
#घोषणा USBPCR1_REFCLKSEL_SHIFT	26
#घोषणा USBPCR1_REFCLKSEL_MASK	(0x3 << USBPCR1_REFCLKSEL_SHIFT)
#घोषणा USBPCR1_REFCLKSEL_CORE	(0x2 << USBPCR1_REFCLKSEL_SHIFT)
#घोषणा USBPCR1_REFCLKDIV_SHIFT	24
#घोषणा USBPCR1_REFCLKDIV_MASK	(0x3 << USBPCR1_REFCLKDIV_SHIFT)
#घोषणा USBPCR1_REFCLKDIV_19_2	(0x3 << USBPCR1_REFCLKDIV_SHIFT)
#घोषणा USBPCR1_REFCLKDIV_48	(0x2 << USBPCR1_REFCLKDIV_SHIFT)
#घोषणा USBPCR1_REFCLKDIV_24	(0x1 << USBPCR1_REFCLKDIV_SHIFT)
#घोषणा USBPCR1_REFCLKDIV_12	(0x0 << USBPCR1_REFCLKDIV_SHIFT)
#घोषणा USBPCR1_USB_SEL			BIT(28)
#घोषणा USBPCR1_WORD_IF0		BIT(19)
#घोषणा USBPCR1_WORD_IF1		BIT(18)

/* bits within the USBRDT रेजिस्टर */
#घोषणा USBRDT_VBFIL_LD_EN		BIT(25)
#घोषणा USBRDT_USBRDT_MASK		0x7fffff

/* bits within the USBVBFIL रेजिस्टर */
#घोषणा USBVBFIL_IDDIGFIL_SHIFT	16
#घोषणा USBVBFIL_IDDIGFIL_MASK	(0xffff << USBVBFIL_IDDIGFIL_SHIFT)
#घोषणा USBVBFIL_USBVBFIL_MASK	(0xffff)

/* bits within the LCR रेजिस्टर */
#घोषणा LCR_PD_SCPU				BIT(31)
#घोषणा LCR_SCPUS				BIT(27)

/* bits within the CLKGR1 रेजिस्टर */
#घोषणा CLKGR1_CORE1			BIT(15)

अटल काष्ठा ingenic_cgu *cgu;

अटल अचिन्हित दीर्घ jz4780_otg_phy_recalc_rate(काष्ठा clk_hw *hw,
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

	हाल USBPCR1_REFCLKDIV_19_2:
		वापस 19200000;
	पूर्ण

	वापस parent_rate;
पूर्ण

अटल दीर्घ jz4780_otg_phy_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ req_rate,
				      अचिन्हित दीर्घ *parent_rate)
अणु
	अगर (req_rate < 15600000)
		वापस 12000000;

	अगर (req_rate < 21600000)
		वापस 19200000;

	अगर (req_rate < 36000000)
		वापस 24000000;

	वापस 48000000;
पूर्ण

अटल पूर्णांक jz4780_otg_phy_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ req_rate,
				   अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ flags;
	u32 usbpcr1, भाग_bits;

	चयन (req_rate) अणु
	हाल 12000000:
		भाग_bits = USBPCR1_REFCLKDIV_12;
		अवरोध;

	हाल 19200000:
		भाग_bits = USBPCR1_REFCLKDIV_19_2;
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

अटल पूर्णांक jz4780_otg_phy_enable(काष्ठा clk_hw *hw)
अणु
	व्योम __iomem *reg_opcr		= cgu->base + CGU_REG_OPCR;
	व्योम __iomem *reg_usbpcr	= cgu->base + CGU_REG_USBPCR;

	ग_लिखोl(पढ़ोl(reg_opcr) | OPCR_SPENDN0, reg_opcr);
	ग_लिखोl(पढ़ोl(reg_usbpcr) & ~USBPCR_OTG_DISABLE & ~USBPCR_SIDDQ, reg_usbpcr);
	वापस 0;
पूर्ण

अटल व्योम jz4780_otg_phy_disable(काष्ठा clk_hw *hw)
अणु
	व्योम __iomem *reg_opcr		= cgu->base + CGU_REG_OPCR;
	व्योम __iomem *reg_usbpcr	= cgu->base + CGU_REG_USBPCR;

	ग_लिखोl(पढ़ोl(reg_opcr) & ~OPCR_SPENDN0, reg_opcr);
	ग_लिखोl(पढ़ोl(reg_usbpcr) | USBPCR_OTG_DISABLE | USBPCR_SIDDQ, reg_usbpcr);
पूर्ण

अटल पूर्णांक jz4780_otg_phy_is_enabled(काष्ठा clk_hw *hw)
अणु
	व्योम __iomem *reg_opcr		= cgu->base + CGU_REG_OPCR;
	व्योम __iomem *reg_usbpcr	= cgu->base + CGU_REG_USBPCR;

	वापस (पढ़ोl(reg_opcr) & OPCR_SPENDN0) &&
		!(पढ़ोl(reg_usbpcr) & USBPCR_SIDDQ) &&
		!(पढ़ोl(reg_usbpcr) & USBPCR_OTG_DISABLE);
पूर्ण

अटल स्थिर काष्ठा clk_ops jz4780_otg_phy_ops = अणु
	.recalc_rate = jz4780_otg_phy_recalc_rate,
	.round_rate = jz4780_otg_phy_round_rate,
	.set_rate = jz4780_otg_phy_set_rate,

	.enable		= jz4780_otg_phy_enable,
	.disable	= jz4780_otg_phy_disable,
	.is_enabled	= jz4780_otg_phy_is_enabled,
पूर्ण;

अटल पूर्णांक jz4780_core1_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	काष्ठा ingenic_cgu *cgu = ingenic_clk->cgu;
	स्थिर अचिन्हित पूर्णांक समयout = 5000;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;
	u32 lcr, clkgr1;

	spin_lock_irqsave(&cgu->lock, flags);

	lcr = पढ़ोl(cgu->base + CGU_REG_LCR);
	lcr &= ~LCR_PD_SCPU;
	ग_लिखोl(lcr, cgu->base + CGU_REG_LCR);

	clkgr1 = पढ़ोl(cgu->base + CGU_REG_CLKGR1);
	clkgr1 &= ~CLKGR1_CORE1;
	ग_लिखोl(clkgr1, cgu->base + CGU_REG_CLKGR1);

	spin_unlock_irqrestore(&cgu->lock, flags);

	/* रुको क्रम the CPU to be घातered up */
	retval = पढ़ोl_poll_समयout(cgu->base + CGU_REG_LCR, lcr,
				 !(lcr & LCR_SCPUS), 10, समयout);
	अगर (retval == -ETIMEDOUT) अणु
		pr_err("%s: Wait for power up core1 timeout\n", __func__);
		वापस retval;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops jz4780_core1_ops = अणु
	.enable = jz4780_core1_enable,
पूर्ण;

अटल स्थिर s8 pll_od_encoding[16] = अणु
	0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,
	0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf,
पूर्ण;

अटल स्थिर काष्ठा ingenic_cgu_clk_info jz4780_cgu_घड़ीs[] = अणु

	/* External घड़ीs */

	[JZ4780_CLK_EXCLK] = अणु "ext", CGU_CLK_EXT पूर्ण,
	[JZ4780_CLK_RTCLK] = अणु "rtc", CGU_CLK_EXT पूर्ण,

	/* PLLs */

#घोषणा DEF_PLL(name) अणु \
	.reg = CGU_REG_ ## name, \
	.rate_multiplier = 1, \
	.m_shअगरt = 19, \
	.m_bits = 13, \
	.m_offset = 1, \
	.n_shअगरt = 13, \
	.n_bits = 6, \
	.n_offset = 1, \
	.od_shअगरt = 9, \
	.od_bits = 4, \
	.od_max = 16, \
	.od_encoding = pll_od_encoding, \
	.stable_bit = 6, \
	.bypass_reg = CGU_REG_ ## name, \
	.bypass_bit = 1, \
	.enable_bit = 0, \
पूर्ण

	[JZ4780_CLK_APLL] = अणु
		"apll", CGU_CLK_PLL,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.pll = DEF_PLL(APLL),
	पूर्ण,

	[JZ4780_CLK_MPLL] = अणु
		"mpll", CGU_CLK_PLL,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.pll = DEF_PLL(MPLL),
	पूर्ण,

	[JZ4780_CLK_EPLL] = अणु
		"epll", CGU_CLK_PLL,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.pll = DEF_PLL(EPLL),
	पूर्ण,

	[JZ4780_CLK_VPLL] = अणु
		"vpll", CGU_CLK_PLL,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.pll = DEF_PLL(VPLL),
	पूर्ण,

#अघोषित DEF_PLL

	/* Custom (SoC-specअगरic) OTG PHY */

	[JZ4780_CLK_OTGPHY] = अणु
		"otg_phy", CGU_CLK_CUSTOM,
		.parents = अणु -1, -1, JZ4780_CLK_EXCLK, -1 पूर्ण,
		.custom = अणु &jz4780_otg_phy_ops पूर्ण,
	पूर्ण,

	/* Muxes & भागiders */

	[JZ4780_CLK_SCLKA] = अणु
		"sclk_a", CGU_CLK_MUX,
		.parents = अणु -1, JZ4780_CLK_APLL, JZ4780_CLK_EXCLK,
			     JZ4780_CLK_RTCLK पूर्ण,
		.mux = अणु CGU_REG_CLOCKCONTROL, 30, 2 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_CPUMUX] = अणु
		"cpumux", CGU_CLK_MUX,
		.parents = अणु -1, JZ4780_CLK_SCLKA, JZ4780_CLK_MPLL,
			     JZ4780_CLK_EPLL पूर्ण,
		.mux = अणु CGU_REG_CLOCKCONTROL, 28, 2 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_CPU] = अणु
		"cpu", CGU_CLK_DIV,
		.parents = अणु JZ4780_CLK_CPUMUX, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_CLOCKCONTROL, 0, 1, 4, 22, -1, -1 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_L2CACHE] = अणु
		"l2cache", CGU_CLK_DIV,
		.parents = अणु JZ4780_CLK_CPUMUX, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_CLOCKCONTROL, 4, 1, 4, -1, -1, -1 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_AHB0] = अणु
		"ahb0", CGU_CLK_MUX | CGU_CLK_DIV,
		.parents = अणु -1, JZ4780_CLK_SCLKA, JZ4780_CLK_MPLL,
			     JZ4780_CLK_EPLL पूर्ण,
		.mux = अणु CGU_REG_CLOCKCONTROL, 26, 2 पूर्ण,
		.भाग = अणु CGU_REG_CLOCKCONTROL, 8, 1, 4, 21, -1, -1 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_AHB2PMUX] = अणु
		"ahb2_apb_mux", CGU_CLK_MUX,
		.parents = अणु -1, JZ4780_CLK_SCLKA, JZ4780_CLK_MPLL,
			     JZ4780_CLK_RTCLK पूर्ण,
		.mux = अणु CGU_REG_CLOCKCONTROL, 24, 2 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_AHB2] = अणु
		"ahb2", CGU_CLK_DIV,
		.parents = अणु JZ4780_CLK_AHB2PMUX, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_CLOCKCONTROL, 12, 1, 4, 20, -1, -1 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_PCLK] = अणु
		"pclk", CGU_CLK_DIV,
		.parents = अणु JZ4780_CLK_AHB2PMUX, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_CLOCKCONTROL, 16, 1, 4, 20, -1, -1 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_DDR] = अणु
		"ddr", CGU_CLK_MUX | CGU_CLK_DIV,
		.parents = अणु -1, JZ4780_CLK_SCLKA, JZ4780_CLK_MPLL, -1 पूर्ण,
		.mux = अणु CGU_REG_DDRCDR, 30, 2 पूर्ण,
		.भाग = अणु CGU_REG_DDRCDR, 0, 1, 4, 29, 28, 27 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_VPU] = अणु
		"vpu", CGU_CLK_MUX | CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_SCLKA, JZ4780_CLK_MPLL,
			     JZ4780_CLK_EPLL, -1 पूर्ण,
		.mux = अणु CGU_REG_VPUCDR, 30, 2 पूर्ण,
		.भाग = अणु CGU_REG_VPUCDR, 0, 1, 4, 29, 28, 27 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 2 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_I2SPLL] = अणु
		"i2s_pll", CGU_CLK_MUX | CGU_CLK_DIV,
		.parents = अणु JZ4780_CLK_SCLKA, JZ4780_CLK_EPLL, -1, -1 पूर्ण,
		.mux = अणु CGU_REG_I2SCDR, 30, 1 पूर्ण,
		.भाग = अणु CGU_REG_I2SCDR, 0, 1, 8, 29, 28, 27 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_I2S] = अणु
		"i2s", CGU_CLK_MUX,
		.parents = अणु JZ4780_CLK_EXCLK, JZ4780_CLK_I2SPLL, -1, -1 पूर्ण,
		.mux = अणु CGU_REG_I2SCDR, 31, 1 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_LCD0PIXCLK] = अणु
		"lcd0pixclk", CGU_CLK_MUX | CGU_CLK_DIV,
		.parents = अणु JZ4780_CLK_SCLKA, JZ4780_CLK_MPLL,
			     JZ4780_CLK_VPLL, -1 पूर्ण,
		.mux = अणु CGU_REG_LP0CDR, 30, 2 पूर्ण,
		.भाग = अणु CGU_REG_LP0CDR, 0, 1, 8, 28, 27, 26 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_LCD1PIXCLK] = अणु
		"lcd1pixclk", CGU_CLK_MUX | CGU_CLK_DIV,
		.parents = अणु JZ4780_CLK_SCLKA, JZ4780_CLK_MPLL,
			     JZ4780_CLK_VPLL, -1 पूर्ण,
		.mux = अणु CGU_REG_LP1CDR, 30, 2 पूर्ण,
		.भाग = अणु CGU_REG_LP1CDR, 0, 1, 8, 28, 27, 26 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_MSCMUX] = अणु
		"msc_mux", CGU_CLK_MUX,
		.parents = अणु -1, JZ4780_CLK_SCLKA, JZ4780_CLK_MPLL, -1 पूर्ण,
		.mux = अणु CGU_REG_MSC0CDR, 30, 2 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_MSC0] = अणु
		"msc0", CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_MSCMUX, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_MSC0CDR, 0, 2, 8, 29, 28, 27 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 3 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_MSC1] = अणु
		"msc1", CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_MSCMUX, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_MSC1CDR, 0, 2, 8, 29, 28, 27 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 11 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_MSC2] = अणु
		"msc2", CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_MSCMUX, -1, -1, -1 पूर्ण,
		.भाग = अणु CGU_REG_MSC2CDR, 0, 2, 8, 29, 28, 27 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 12 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_UHC] = अणु
		"uhc", CGU_CLK_MUX | CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_SCLKA, JZ4780_CLK_MPLL,
			     JZ4780_CLK_EPLL, JZ4780_CLK_OTGPHY पूर्ण,
		.mux = अणु CGU_REG_UHCCDR, 30, 2 पूर्ण,
		.भाग = अणु CGU_REG_UHCCDR, 0, 1, 8, 29, 28, 27 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 24 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_SSIPLL] = अणु
		"ssi_pll", CGU_CLK_MUX | CGU_CLK_DIV,
		.parents = अणु JZ4780_CLK_SCLKA, JZ4780_CLK_MPLL, -1, -1 पूर्ण,
		.mux = अणु CGU_REG_SSICDR, 30, 1 पूर्ण,
		.भाग = अणु CGU_REG_SSICDR, 0, 1, 8, 29, 28, 27 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_SSI] = अणु
		"ssi", CGU_CLK_MUX,
		.parents = अणु JZ4780_CLK_EXCLK, JZ4780_CLK_SSIPLL, -1, -1 पूर्ण,
		.mux = अणु CGU_REG_SSICDR, 31, 1 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_CIMMCLK] = अणु
		"cim_mclk", CGU_CLK_MUX | CGU_CLK_DIV,
		.parents = अणु JZ4780_CLK_SCLKA, JZ4780_CLK_MPLL, -1, -1 पूर्ण,
		.mux = अणु CGU_REG_CIMCDR, 31, 1 पूर्ण,
		.भाग = अणु CGU_REG_CIMCDR, 0, 1, 8, 30, 29, 28 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_PCMPLL] = अणु
		"pcm_pll", CGU_CLK_MUX | CGU_CLK_DIV,
		.parents = अणु JZ4780_CLK_SCLKA, JZ4780_CLK_MPLL,
			     JZ4780_CLK_EPLL, JZ4780_CLK_VPLL पूर्ण,
		.mux = अणु CGU_REG_PCMCDR, 29, 2 पूर्ण,
		.भाग = अणु CGU_REG_PCMCDR, 0, 1, 8, 28, 27, 26 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_PCM] = अणु
		"pcm", CGU_CLK_MUX | CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, JZ4780_CLK_PCMPLL, -1, -1 पूर्ण,
		.mux = अणु CGU_REG_PCMCDR, 31, 1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 3 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_GPU] = अणु
		"gpu", CGU_CLK_MUX | CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु -1, JZ4780_CLK_SCLKA, JZ4780_CLK_MPLL,
			     JZ4780_CLK_EPLL पूर्ण,
		.mux = अणु CGU_REG_GPUCDR, 30, 2 पूर्ण,
		.भाग = अणु CGU_REG_GPUCDR, 0, 1, 4, 29, 28, 27 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 4 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_HDMI] = अणु
		"hdmi", CGU_CLK_MUX | CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_SCLKA, JZ4780_CLK_MPLL,
			     JZ4780_CLK_VPLL, -1 पूर्ण,
		.mux = अणु CGU_REG_HDMICDR, 30, 2 पूर्ण,
		.भाग = अणु CGU_REG_HDMICDR, 0, 1, 8, 29, 28, 26 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 9 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_BCH] = अणु
		"bch", CGU_CLK_MUX | CGU_CLK_DIV | CGU_CLK_GATE,
		.parents = अणु -1, JZ4780_CLK_SCLKA, JZ4780_CLK_MPLL,
			     JZ4780_CLK_EPLL पूर्ण,
		.mux = अणु CGU_REG_BCHCDR, 30, 2 पूर्ण,
		.भाग = अणु CGU_REG_BCHCDR, 0, 1, 4, 29, 28, 27 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 1 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_EXCLK_DIV512] = अणु
		"exclk_div512", CGU_CLK_FIXDIV,
		.parents = अणु JZ4780_CLK_EXCLK पूर्ण,
		.fixभाग = अणु 512 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_RTC] = अणु
		"rtc_ercs", CGU_CLK_MUX | CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK_DIV512, JZ4780_CLK_RTCLK पूर्ण,
		.mux = अणु CGU_REG_OPCR, 2, 1पूर्ण,
	पूर्ण,

	/* Gate-only घड़ीs */

	[JZ4780_CLK_NEMC] = अणु
		"nemc", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_AHB2, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 0 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_OTG0] = अणु
		"otg0", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 2 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_SSI0] = अणु
		"ssi0", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_SSI, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 4 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_SMB0] = अणु
		"smb0", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_PCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 5 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_SMB1] = अणु
		"smb1", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_PCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 6 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_SCC] = अणु
		"scc", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 7 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_AIC] = अणु
		"aic", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 8 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_TSSI0] = अणु
		"tssi0", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 9 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_OWI] = अणु
		"owi", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 10 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_KBC] = अणु
		"kbc", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 13 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_SADC] = अणु
		"sadc", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 14 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_UART0] = अणु
		"uart0", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 15 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_UART1] = अणु
		"uart1", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 16 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_UART2] = अणु
		"uart2", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 17 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_UART3] = अणु
		"uart3", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 18 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_SSI1] = अणु
		"ssi1", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_SSI, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 19 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_SSI2] = अणु
		"ssi2", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_SSI, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 20 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_PDMA] = अणु
		"pdma", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 21 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_GPS] = अणु
		"gps", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 22 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_MAC] = अणु
		"mac", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 23 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_SMB2] = अणु
		"smb2", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_PCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 24 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_CIM] = अणु
		"cim", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 26 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_LCD] = अणु
		"lcd", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 28 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_TVE] = अणु
		"tve", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_LCD, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 27 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_IPU] = अणु
		"ipu", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 29 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_DDR0] = अणु
		"ddr0", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_DDR, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 30 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_DDR1] = अणु
		"ddr1", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_DDR, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR0, 31 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_SMB3] = अणु
		"smb3", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_PCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 0 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_TSSI1] = अणु
		"tssi1", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 1 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_COMPRESS] = अणु
		"compress", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 5 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_AIC1] = अणु
		"aic1", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 6 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_GPVLC] = अणु
		"gpvlc", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 7 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_OTG1] = अणु
		"otg1", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 8 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_UART4] = अणु
		"uart4", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 10 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_AHBMON] = अणु
		"ahb_mon", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 11 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_SMB4] = अणु
		"smb4", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_PCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 12 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_DES] = अणु
		"des", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 13 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_X2D] = अणु
		"x2d", CGU_CLK_GATE,
		.parents = अणु JZ4780_CLK_EXCLK, -1, -1, -1 पूर्ण,
		.gate = अणु CGU_REG_CLKGR1, 14 पूर्ण,
	पूर्ण,

	[JZ4780_CLK_CORE1] = अणु
		"core1", CGU_CLK_CUSTOM,
		.parents = अणु JZ4780_CLK_CPU, -1, -1, -1 पूर्ण,
		.custom = अणु &jz4780_core1_ops पूर्ण,
	पूर्ण,

पूर्ण;

अटल व्योम __init jz4780_cgu_init(काष्ठा device_node *np)
अणु
	पूर्णांक retval;

	cgu = ingenic_cgu_new(jz4780_cgu_घड़ीs,
			      ARRAY_SIZE(jz4780_cgu_घड़ीs), np);
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
CLK_OF_DECLARE_DRIVER(jz4780_cgu, "ingenic,jz4780-cgu", jz4780_cgu_init);
