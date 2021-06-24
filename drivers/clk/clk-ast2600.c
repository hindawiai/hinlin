<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
// Copyright IBM Corp
// Copyright ASPEED Technology

#घोषणा pr_fmt(fmt) "clk-ast2600: " fmt

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/घड़ी/ast2600-घड़ी.h>

#समावेश "clk-aspeed.h"

#घोषणा ASPEED_G6_NUM_CLKS		71

#घोषणा ASPEED_G6_SILICON_REV		0x014
#घोषणा CHIP_REVISION_ID			GENMASK(23, 16)

#घोषणा ASPEED_G6_RESET_CTRL		0x040
#घोषणा ASPEED_G6_RESET_CTRL2		0x050

#घोषणा ASPEED_G6_CLK_STOP_CTRL		0x080
#घोषणा ASPEED_G6_CLK_STOP_CTRL2	0x090

#घोषणा ASPEED_G6_MISC_CTRL		0x0C0
#घोषणा  UART_DIV13_EN			BIT(12)

#घोषणा ASPEED_G6_CLK_SELECTION1	0x300
#घोषणा ASPEED_G6_CLK_SELECTION2	0x304
#घोषणा ASPEED_G6_CLK_SELECTION4	0x310

#घोषणा ASPEED_HPLL_PARAM		0x200
#घोषणा ASPEED_APLL_PARAM		0x210
#घोषणा ASPEED_MPLL_PARAM		0x220
#घोषणा ASPEED_EPLL_PARAM		0x240
#घोषणा ASPEED_DPLL_PARAM		0x260

#घोषणा ASPEED_G6_STRAP1		0x500

#घोषणा ASPEED_MAC12_CLK_DLY		0x340
#घोषणा ASPEED_MAC34_CLK_DLY		0x350

/* Globally visible घड़ीs */
अटल DEFINE_SPINLOCK(aspeed_g6_clk_lock);

/* Keeps track of all घड़ीs */
अटल काष्ठा clk_hw_onecell_data *aspeed_g6_clk_data;

अटल व्योम __iomem *scu_g6_base;

/*
 * Clocks marked with CLK_IS_CRITICAL:
 *
 *  ref0 and ref1 are essential क्रम the SoC to operate
 *  mpll is required अगर SDRAM is used
 */
अटल स्थिर काष्ठा aspeed_gate_data aspeed_g6_gates[] = अणु
	/*				    clk rst  name		parent	 flags */
	[ASPEED_CLK_GATE_MCLK]		= अणु  0, -1, "mclk-gate",	"mpll",	 CLK_IS_CRITICAL पूर्ण, /* SDRAM */
	[ASPEED_CLK_GATE_ECLK]		= अणु  1,  6, "eclk-gate",	"eclk",	 0 पूर्ण,	/* Video Engine */
	[ASPEED_CLK_GATE_GCLK]		= अणु  2,  7, "gclk-gate",	शून्य,	 0 पूर्ण,	/* 2D engine */
	/* vclk parent - dclk/d1clk/hclk/mclk */
	[ASPEED_CLK_GATE_VCLK]		= अणु  3, -1, "vclk-gate",	शून्य,	 0 पूर्ण,	/* Video Capture */
	[ASPEED_CLK_GATE_BCLK]		= अणु  4,  8, "bclk-gate",	"bclk",	 0 पूर्ण, /* PCIe/PCI */
	/* From dpll */
	[ASPEED_CLK_GATE_DCLK]		= अणु  5, -1, "dclk-gate",	शून्य,	 CLK_IS_CRITICAL पूर्ण, /* DAC */
	[ASPEED_CLK_GATE_REF0CLK]	= अणु  6, -1, "ref0clk-gate",	"clkin", CLK_IS_CRITICAL पूर्ण,
	[ASPEED_CLK_GATE_USBPORT2CLK]	= अणु  7,  3, "usb-port2-gate",	शून्य,	 0 पूर्ण,	/* USB2.0 Host port 2 */
	/* Reserved 8 */
	[ASPEED_CLK_GATE_USBUHCICLK]	= अणु  9, 15, "usb-uhci-gate",	शून्य,	 0 पूर्ण,	/* USB1.1 (requires port 2 enabled) */
	/* From dpll/epll/40mhz usb p1 phy/gpioc6/dp phy pll */
	[ASPEED_CLK_GATE_D1CLK]		= अणु 10, 13, "d1clk-gate",	"d1clk", 0 पूर्ण,	/* GFX CRT */
	/* Reserved 11/12 */
	[ASPEED_CLK_GATE_YCLK]		= अणु 13,  4, "yclk-gate",	शून्य,	 0 पूर्ण,	/* HAC */
	[ASPEED_CLK_GATE_USBPORT1CLK]	= अणु 14, 14, "usb-port1-gate",	शून्य,	 0 पूर्ण,	/* USB2 hub/USB2 host port 1/USB1.1 dev */
	[ASPEED_CLK_GATE_UART5CLK]	= अणु 15, -1, "uart5clk-gate",	"uart",	 0 पूर्ण,	/* UART5 */
	/* Reserved 16/19 */
	[ASPEED_CLK_GATE_MAC1CLK]	= अणु 20, 11, "mac1clk-gate",	"mac12", 0 पूर्ण,	/* MAC1 */
	[ASPEED_CLK_GATE_MAC2CLK]	= अणु 21, 12, "mac2clk-gate",	"mac12", 0 पूर्ण,	/* MAC2 */
	/* Reserved 22/23 */
	[ASPEED_CLK_GATE_RSACLK]	= अणु 24,  4, "rsaclk-gate",	शून्य,	 0 पूर्ण,	/* HAC */
	[ASPEED_CLK_GATE_RVASCLK]	= अणु 25,  9, "rvasclk-gate",	शून्य,	 0 पूर्ण,	/* RVAS */
	/* Reserved 26 */
	[ASPEED_CLK_GATE_EMMCCLK]	= अणु 27, 16, "emmcclk-gate",	शून्य,	 0 पूर्ण,	/* For card clk */
	/* Reserved 28/29/30 */
	[ASPEED_CLK_GATE_LCLK]		= अणु 32, 32, "lclk-gate",	शून्य,	 0 पूर्ण, /* LPC */
	[ASPEED_CLK_GATE_ESPICLK]	= अणु 33, -1, "espiclk-gate",	शून्य,	 0 पूर्ण, /* eSPI */
	[ASPEED_CLK_GATE_REF1CLK]	= अणु 34, -1, "ref1clk-gate",	"clkin", CLK_IS_CRITICAL पूर्ण,
	/* Reserved 35 */
	[ASPEED_CLK_GATE_SDCLK]		= अणु 36, 56, "sdclk-gate",	शून्य,	 0 पूर्ण,	/* SDIO/SD */
	[ASPEED_CLK_GATE_LHCCLK]	= अणु 37, -1, "lhclk-gate",	"lhclk", 0 पूर्ण,	/* LPC master/LPC+ */
	/* Reserved 38 RSA: no दीर्घer used */
	/* Reserved 39 */
	[ASPEED_CLK_GATE_I3C0CLK]	= अणु 40,  40, "i3c0clk-gate",	शून्य,	 0 पूर्ण,	/* I3C0 */
	[ASPEED_CLK_GATE_I3C1CLK]	= अणु 41,  41, "i3c1clk-gate",	शून्य,	 0 पूर्ण,	/* I3C1 */
	[ASPEED_CLK_GATE_I3C2CLK]	= अणु 42,  42, "i3c2clk-gate",	शून्य,	 0 पूर्ण,	/* I3C2 */
	[ASPEED_CLK_GATE_I3C3CLK]	= अणु 43,  43, "i3c3clk-gate",	शून्य,	 0 पूर्ण,	/* I3C3 */
	[ASPEED_CLK_GATE_I3C4CLK]	= अणु 44,  44, "i3c4clk-gate",	शून्य,	 0 पूर्ण,	/* I3C4 */
	[ASPEED_CLK_GATE_I3C5CLK]	= अणु 45,  45, "i3c5clk-gate",	शून्य,	 0 पूर्ण,	/* I3C5 */
	[ASPEED_CLK_GATE_I3C6CLK]	= अणु 46,  46, "i3c6clk-gate",	शून्य,	 0 पूर्ण,	/* I3C6 */
	[ASPEED_CLK_GATE_I3C7CLK]	= अणु 47,  47, "i3c7clk-gate",	शून्य,	 0 पूर्ण,	/* I3C7 */
	[ASPEED_CLK_GATE_UART1CLK]	= अणु 48,  -1, "uart1clk-gate",	"uart",	 0 पूर्ण,	/* UART1 */
	[ASPEED_CLK_GATE_UART2CLK]	= अणु 49,  -1, "uart2clk-gate",	"uart",	 0 पूर्ण,	/* UART2 */
	[ASPEED_CLK_GATE_UART3CLK]	= अणु 50,  -1, "uart3clk-gate",	"uart",  0 पूर्ण,	/* UART3 */
	[ASPEED_CLK_GATE_UART4CLK]	= अणु 51,  -1, "uart4clk-gate",	"uart",	 0 पूर्ण,	/* UART4 */
	[ASPEED_CLK_GATE_MAC3CLK]	= अणु 52,  52, "mac3clk-gate",	"mac34", 0 पूर्ण,	/* MAC3 */
	[ASPEED_CLK_GATE_MAC4CLK]	= अणु 53,  53, "mac4clk-gate",	"mac34", 0 पूर्ण,	/* MAC4 */
	[ASPEED_CLK_GATE_UART6CLK]	= अणु 54,  -1, "uart6clk-gate",	"uartx", 0 पूर्ण,	/* UART6 */
	[ASPEED_CLK_GATE_UART7CLK]	= अणु 55,  -1, "uart7clk-gate",	"uartx", 0 पूर्ण,	/* UART7 */
	[ASPEED_CLK_GATE_UART8CLK]	= अणु 56,  -1, "uart8clk-gate",	"uartx", 0 पूर्ण,	/* UART8 */
	[ASPEED_CLK_GATE_UART9CLK]	= अणु 57,  -1, "uart9clk-gate",	"uartx", 0 पूर्ण,	/* UART9 */
	[ASPEED_CLK_GATE_UART10CLK]	= अणु 58,  -1, "uart10clk-gate",	"uartx", 0 पूर्ण,	/* UART10 */
	[ASPEED_CLK_GATE_UART11CLK]	= अणु 59,  -1, "uart11clk-gate",	"uartx", 0 पूर्ण,	/* UART11 */
	[ASPEED_CLK_GATE_UART12CLK]	= अणु 60,  -1, "uart12clk-gate",	"uartx", 0 पूर्ण,	/* UART12 */
	[ASPEED_CLK_GATE_UART13CLK]	= अणु 61,  -1, "uart13clk-gate",	"uartx", 0 पूर्ण,	/* UART13 */
	[ASPEED_CLK_GATE_FSICLK]	= अणु 62,  59, "fsiclk-gate",	शून्य,	 0 पूर्ण,	/* FSI */
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable ast2600_eclk_भाग_प्रकारable[] = अणु
	अणु 0x0, 2 पूर्ण,
	अणु 0x1, 2 पूर्ण,
	अणु 0x2, 3 पूर्ण,
	अणु 0x3, 4 पूर्ण,
	अणु 0x4, 5 पूर्ण,
	अणु 0x5, 6 पूर्ण,
	अणु 0x6, 7 पूर्ण,
	अणु 0x7, 8 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable ast2600_emmc_extclk_भाग_प्रकारable[] = अणु
	अणु 0x0, 2 पूर्ण,
	अणु 0x1, 4 पूर्ण,
	अणु 0x2, 6 पूर्ण,
	अणु 0x3, 8 पूर्ण,
	अणु 0x4, 10 पूर्ण,
	अणु 0x5, 12 पूर्ण,
	अणु 0x6, 14 पूर्ण,
	अणु 0x7, 16 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable ast2600_mac_भाग_प्रकारable[] = अणु
	अणु 0x0, 4 पूर्ण,
	अणु 0x1, 4 पूर्ण,
	अणु 0x2, 6 पूर्ण,
	अणु 0x3, 8 पूर्ण,
	अणु 0x4, 10 पूर्ण,
	अणु 0x5, 12 पूर्ण,
	अणु 0x6, 14 पूर्ण,
	अणु 0x7, 16 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable ast2600_भाग_प्रकारable[] = अणु
	अणु 0x0, 4 पूर्ण,
	अणु 0x1, 8 पूर्ण,
	अणु 0x2, 12 पूर्ण,
	अणु 0x3, 16 पूर्ण,
	अणु 0x4, 20 पूर्ण,
	अणु 0x5, 24 पूर्ण,
	अणु 0x6, 28 पूर्ण,
	अणु 0x7, 32 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

/* For hpll/dpll/epll/mpll */
अटल काष्ठा clk_hw *ast2600_calc_pll(स्थिर अक्षर *name, u32 val)
अणु
	अचिन्हित पूर्णांक mult, भाग;

	अगर (val & BIT(24)) अणु
		/* Pass through mode */
		mult = भाग = 1;
	पूर्ण अन्यथा अणु
		/* F = 25Mhz * [(M + 2) / (n + 1)] / (p + 1) */
		u32 m = val  & 0x1fff;
		u32 n = (val >> 13) & 0x3f;
		u32 p = (val >> 19) & 0xf;
		mult = (m + 1) / (n + 1);
		भाग = (p + 1);
	पूर्ण
	वापस clk_hw_रेजिस्टर_fixed_factor(शून्य, name, "clkin", 0,
			mult, भाग);
पूर्ण;

अटल काष्ठा clk_hw *ast2600_calc_apll(स्थिर अक्षर *name, u32 val)
अणु
	अचिन्हित पूर्णांक mult, भाग;
	u32 chip_id = पढ़ोl(scu_g6_base + ASPEED_G6_SILICON_REV);

	अगर (((chip_id & CHIP_REVISION_ID) >> 16) >= 2) अणु
		अगर (val & BIT(24)) अणु
			/* Pass through mode */
			mult = भाग = 1;
		पूर्ण अन्यथा अणु
			/* F = 25Mhz * [(m + 1) / (n + 1)] / (p + 1) */
			u32 m = val & 0x1fff;
			u32 n = (val >> 13) & 0x3f;
			u32 p = (val >> 19) & 0xf;

			mult = (m + 1);
			भाग = (n + 1) * (p + 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (val & BIT(20)) अणु
			/* Pass through mode */
			mult = भाग = 1;
		पूर्ण अन्यथा अणु
			/* F = 25Mhz * (2-od) * [(m + 2) / (n + 1)] */
			u32 m = (val >> 5) & 0x3f;
			u32 od = (val >> 4) & 0x1;
			u32 n = val & 0xf;

			mult = (2 - od) * (m + 2);
			भाग = n + 1;
		पूर्ण
	पूर्ण
	वापस clk_hw_रेजिस्टर_fixed_factor(शून्य, name, "clkin", 0,
			mult, भाग);
पूर्ण;

अटल u32 get_bit(u8 idx)
अणु
	वापस BIT(idx % 32);
पूर्ण

अटल u32 get_reset_reg(काष्ठा aspeed_clk_gate *gate)
अणु
	अगर (gate->reset_idx < 32)
		वापस ASPEED_G6_RESET_CTRL;

	वापस ASPEED_G6_RESET_CTRL2;
पूर्ण

अटल u32 get_घड़ी_reg(काष्ठा aspeed_clk_gate *gate)
अणु
	अगर (gate->घड़ी_idx < 32)
		वापस ASPEED_G6_CLK_STOP_CTRL;

	वापस ASPEED_G6_CLK_STOP_CTRL2;
पूर्ण

अटल पूर्णांक aspeed_g6_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा aspeed_clk_gate *gate = to_aspeed_clk_gate(hw);
	u32 clk = get_bit(gate->घड़ी_idx);
	u32 rst = get_bit(gate->reset_idx);
	u32 reg;
	u32 enval;

	/*
	 * If the IP is in reset, treat the घड़ी as not enabled,
	 * this happens with some घड़ीs such as the USB one when
	 * coming from cold reset. Without this, aspeed_clk_enable()
	 * will fail to lअगरt the reset.
	 */
	अगर (gate->reset_idx >= 0) अणु
		regmap_पढ़ो(gate->map, get_reset_reg(gate), &reg);

		अगर (reg & rst)
			वापस 0;
	पूर्ण

	regmap_पढ़ो(gate->map, get_घड़ी_reg(gate), &reg);

	enval = (gate->flags & CLK_GATE_SET_TO_DISABLE) ? 0 : clk;

	वापस ((reg & clk) == enval) ? 1 : 0;
पूर्ण

अटल पूर्णांक aspeed_g6_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा aspeed_clk_gate *gate = to_aspeed_clk_gate(hw);
	अचिन्हित दीर्घ flags;
	u32 clk = get_bit(gate->घड़ी_idx);
	u32 rst = get_bit(gate->reset_idx);

	spin_lock_irqsave(gate->lock, flags);

	अगर (aspeed_g6_clk_is_enabled(hw)) अणु
		spin_unlock_irqrestore(gate->lock, flags);
		वापस 0;
	पूर्ण

	अगर (gate->reset_idx >= 0) अणु
		/* Put IP in reset */
		regmap_ग_लिखो(gate->map, get_reset_reg(gate), rst);
		/* Delay 100us */
		udelay(100);
	पूर्ण

	/* Enable घड़ी */
	अगर (gate->flags & CLK_GATE_SET_TO_DISABLE) अणु
		/* Clock is clear to enable, so use set to clear रेजिस्टर */
		regmap_ग_लिखो(gate->map, get_घड़ी_reg(gate) + 0x04, clk);
	पूर्ण अन्यथा अणु
		/* Clock is set to enable, so use ग_लिखो to set रेजिस्टर */
		regmap_ग_लिखो(gate->map, get_घड़ी_reg(gate), clk);
	पूर्ण

	अगर (gate->reset_idx >= 0) अणु
		/* A delay of 10ms is specअगरied by the ASPEED करोcs */
		mdelay(10);
		/* Take IP out of reset */
		regmap_ग_लिखो(gate->map, get_reset_reg(gate) + 0x4, rst);
	पूर्ण

	spin_unlock_irqrestore(gate->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम aspeed_g6_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा aspeed_clk_gate *gate = to_aspeed_clk_gate(hw);
	अचिन्हित दीर्घ flags;
	u32 clk = get_bit(gate->घड़ी_idx);

	spin_lock_irqsave(gate->lock, flags);

	अगर (gate->flags & CLK_GATE_SET_TO_DISABLE) अणु
		regmap_ग_लिखो(gate->map, get_घड़ी_reg(gate), clk);
	पूर्ण अन्यथा अणु
		/* Use set to clear रेजिस्टर */
		regmap_ग_लिखो(gate->map, get_घड़ी_reg(gate) + 0x4, clk);
	पूर्ण

	spin_unlock_irqrestore(gate->lock, flags);
पूर्ण

अटल स्थिर काष्ठा clk_ops aspeed_g6_clk_gate_ops = अणु
	.enable = aspeed_g6_clk_enable,
	.disable = aspeed_g6_clk_disable,
	.is_enabled = aspeed_g6_clk_is_enabled,
पूर्ण;

अटल पूर्णांक aspeed_g6_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				    अचिन्हित दीर्घ id)
अणु
	काष्ठा aspeed_reset *ar = to_aspeed_reset(rcdev);
	u32 rst = get_bit(id);
	u32 reg = id >= 32 ? ASPEED_G6_RESET_CTRL2 : ASPEED_G6_RESET_CTRL;

	/* Use set to clear रेजिस्टर */
	वापस regmap_ग_लिखो(ar->map, reg + 0x04, rst);
पूर्ण

अटल पूर्णांक aspeed_g6_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
				  अचिन्हित दीर्घ id)
अणु
	काष्ठा aspeed_reset *ar = to_aspeed_reset(rcdev);
	u32 rst = get_bit(id);
	u32 reg = id >= 32 ? ASPEED_G6_RESET_CTRL2 : ASPEED_G6_RESET_CTRL;

	वापस regmap_ग_लिखो(ar->map, reg, rst);
पूर्ण

अटल पूर्णांक aspeed_g6_reset_status(काष्ठा reset_controller_dev *rcdev,
				  अचिन्हित दीर्घ id)
अणु
	काष्ठा aspeed_reset *ar = to_aspeed_reset(rcdev);
	पूर्णांक ret;
	u32 val;
	u32 rst = get_bit(id);
	u32 reg = id >= 32 ? ASPEED_G6_RESET_CTRL2 : ASPEED_G6_RESET_CTRL;

	ret = regmap_पढ़ो(ar->map, reg, &val);
	अगर (ret)
		वापस ret;

	वापस !!(val & rst);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops aspeed_g6_reset_ops = अणु
	.निश्चित = aspeed_g6_reset_निश्चित,
	.deनिश्चित = aspeed_g6_reset_deनिश्चित,
	.status = aspeed_g6_reset_status,
पूर्ण;

अटल काष्ठा clk_hw *aspeed_g6_clk_hw_रेजिस्टर_gate(काष्ठा device *dev,
		स्थिर अक्षर *name, स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		काष्ठा regmap *map, u8 घड़ी_idx, u8 reset_idx,
		u8 clk_gate_flags, spinlock_t *lock)
अणु
	काष्ठा aspeed_clk_gate *gate;
	काष्ठा clk_init_data init;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &aspeed_g6_clk_gate_ops;
	init.flags = flags;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.num_parents = parent_name ? 1 : 0;

	gate->map = map;
	gate->घड़ी_idx = घड़ी_idx;
	gate->reset_idx = reset_idx;
	gate->flags = clk_gate_flags;
	gate->lock = lock;
	gate->hw.init = &init;

	hw = &gate->hw;
	ret = clk_hw_रेजिस्टर(dev, hw);
	अगर (ret) अणु
		kमुक्त(gate);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

अटल स्थिर अक्षर *स्थिर emmc_extclk_parent_names[] = अणु
	"emmc_extclk_hpll_in",
	"mpll",
पूर्ण;

अटल स्थिर अक्षर * स्थिर vclk_parent_names[] = अणु
	"dpll",
	"d1pll",
	"hclk",
	"mclk",
पूर्ण;

अटल स्थिर अक्षर * स्थिर d1clk_parent_names[] = अणु
	"dpll",
	"epll",
	"usb-phy-40m",
	"gpioc6_clkin",
	"dp_phy_pll",
पूर्ण;

अटल पूर्णांक aspeed_g6_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा aspeed_reset *ar;
	काष्ठा regmap *map;
	काष्ठा clk_hw *hw;
	u32 val, rate;
	पूर्णांक i, ret;

	map = syscon_node_to_regmap(dev->of_node);
	अगर (IS_ERR(map)) अणु
		dev_err(dev, "no syscon regmap\n");
		वापस PTR_ERR(map);
	पूर्ण

	ar = devm_kzalloc(dev, माप(*ar), GFP_KERNEL);
	अगर (!ar)
		वापस -ENOMEM;

	ar->map = map;

	ar->rcdev.owner = THIS_MODULE;
	ar->rcdev.nr_resets = 64;
	ar->rcdev.ops = &aspeed_g6_reset_ops;
	ar->rcdev.of_node = dev->of_node;

	ret = devm_reset_controller_रेजिस्टर(dev, &ar->rcdev);
	अगर (ret) अणु
		dev_err(dev, "could not register reset controller\n");
		वापस ret;
	पूर्ण

	/* UART घड़ी भाग13 setting */
	regmap_पढ़ो(map, ASPEED_G6_MISC_CTRL, &val);
	अगर (val & UART_DIV13_EN)
		rate = 24000000 / 13;
	अन्यथा
		rate = 24000000;
	hw = clk_hw_रेजिस्टर_fixed_rate(dev, "uart", शून्य, 0, rate);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_UART] = hw;

	/* UART6~13 घड़ी भाग13 setting */
	regmap_पढ़ो(map, 0x80, &val);
	अगर (val & BIT(31))
		rate = 24000000 / 13;
	अन्यथा
		rate = 24000000;
	hw = clk_hw_रेजिस्टर_fixed_rate(dev, "uartx", शून्य, 0, rate);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_UARTX] = hw;

	/* EMMC ext घड़ी */
	hw = clk_hw_रेजिस्टर_fixed_factor(dev, "emmc_extclk_hpll_in", "hpll",
					  0, 1, 2);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);

	hw = clk_hw_रेजिस्टर_mux(dev, "emmc_extclk_mux",
				 emmc_extclk_parent_names,
				 ARRAY_SIZE(emmc_extclk_parent_names), 0,
				 scu_g6_base + ASPEED_G6_CLK_SELECTION1, 11, 1,
				 0, &aspeed_g6_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);

	hw = clk_hw_रेजिस्टर_gate(dev, "emmc_extclk_gate", "emmc_extclk_mux",
				  0, scu_g6_base + ASPEED_G6_CLK_SELECTION1,
				  15, 0, &aspeed_g6_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);

	hw = clk_hw_रेजिस्टर_भागider_table(dev, "emmc_extclk",
					   "emmc_extclk_gate", 0,
					   scu_g6_base +
						ASPEED_G6_CLK_SELECTION1, 12,
					   3, 0, ast2600_emmc_extclk_भाग_प्रकारable,
					   &aspeed_g6_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_EMMC] = hw;

	/* SD/SDIO घड़ी भागider and gate */
	hw = clk_hw_रेजिस्टर_gate(dev, "sd_extclk_gate", "hpll", 0,
			scu_g6_base + ASPEED_G6_CLK_SELECTION4, 31, 0,
			&aspeed_g6_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	hw = clk_hw_रेजिस्टर_भागider_table(dev, "sd_extclk", "sd_extclk_gate",
			0, scu_g6_base + ASPEED_G6_CLK_SELECTION4, 28, 3, 0,
			ast2600_भाग_प्रकारable,
			&aspeed_g6_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_SDIO] = hw;

	/* MAC1/2 RMII 50MHz RCLK */
	hw = clk_hw_रेजिस्टर_fixed_rate(dev, "mac12rclk", "hpll", 0, 50000000);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);

	/* MAC1/2 AHB bus घड़ी भागider */
	hw = clk_hw_रेजिस्टर_भागider_table(dev, "mac12", "hpll", 0,
			scu_g6_base + ASPEED_G6_CLK_SELECTION1, 16, 3, 0,
			ast2600_mac_भाग_प्रकारable,
			&aspeed_g6_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_MAC12] = hw;

	/* RMII1 50MHz (RCLK) output enable */
	hw = clk_hw_रेजिस्टर_gate(dev, "mac1rclk", "mac12rclk", 0,
			scu_g6_base + ASPEED_MAC12_CLK_DLY, 29, 0,
			&aspeed_g6_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_MAC1RCLK] = hw;

	/* RMII2 50MHz (RCLK) output enable */
	hw = clk_hw_रेजिस्टर_gate(dev, "mac2rclk", "mac12rclk", 0,
			scu_g6_base + ASPEED_MAC12_CLK_DLY, 30, 0,
			&aspeed_g6_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_MAC2RCLK] = hw;

	/* MAC1/2 RMII 50MHz RCLK */
	hw = clk_hw_रेजिस्टर_fixed_rate(dev, "mac34rclk", "hclk", 0, 50000000);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);

	/* MAC3/4 AHB bus घड़ी भागider */
	hw = clk_hw_रेजिस्टर_भागider_table(dev, "mac34", "hpll", 0,
			scu_g6_base + 0x310, 24, 3, 0,
			ast2600_mac_भाग_प्रकारable,
			&aspeed_g6_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_MAC34] = hw;

	/* RMII3 50MHz (RCLK) output enable */
	hw = clk_hw_रेजिस्टर_gate(dev, "mac3rclk", "mac34rclk", 0,
			scu_g6_base + ASPEED_MAC34_CLK_DLY, 29, 0,
			&aspeed_g6_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_MAC3RCLK] = hw;

	/* RMII4 50MHz (RCLK) output enable */
	hw = clk_hw_रेजिस्टर_gate(dev, "mac4rclk", "mac34rclk", 0,
			scu_g6_base + ASPEED_MAC34_CLK_DLY, 30, 0,
			&aspeed_g6_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_MAC4RCLK] = hw;

	/* LPC Host (LHCLK) घड़ी भागider */
	hw = clk_hw_रेजिस्टर_भागider_table(dev, "lhclk", "hpll", 0,
			scu_g6_base + ASPEED_G6_CLK_SELECTION1, 20, 3, 0,
			ast2600_भाग_प्रकारable,
			&aspeed_g6_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_LHCLK] = hw;

	/* gfx d1clk : use dp clk */
	regmap_update_bits(map, ASPEED_G6_CLK_SELECTION1, GENMASK(10, 8), BIT(10));
	/* SoC Display घड़ी selection */
	hw = clk_hw_रेजिस्टर_mux(dev, "d1clk", d1clk_parent_names,
			ARRAY_SIZE(d1clk_parent_names), 0,
			scu_g6_base + ASPEED_G6_CLK_SELECTION1, 8, 3, 0,
			&aspeed_g6_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_D1CLK] = hw;

	/* d1 clk भाग 0x308[17:15] x [14:12] - 8,7,6,5,4,3,2,1 */
	regmap_ग_लिखो(map, 0x308, 0x12000); /* 3x3 = 9 */

	/* P-Bus (BCLK) घड़ी भागider */
	hw = clk_hw_रेजिस्टर_भागider_table(dev, "bclk", "hpll", 0,
			scu_g6_base + ASPEED_G6_CLK_SELECTION1, 20, 3, 0,
			ast2600_भाग_प्रकारable,
			&aspeed_g6_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_BCLK] = hw;

	/* Video Capture घड़ी selection */
	hw = clk_hw_रेजिस्टर_mux(dev, "vclk", vclk_parent_names,
			ARRAY_SIZE(vclk_parent_names), 0,
			scu_g6_base + ASPEED_G6_CLK_SELECTION2, 12, 3, 0,
			&aspeed_g6_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_VCLK] = hw;

	/* Video Engine घड़ी भागider */
	hw = clk_hw_रेजिस्टर_भागider_table(dev, "eclk", शून्य, 0,
			scu_g6_base + ASPEED_G6_CLK_SELECTION1, 28, 3, 0,
			ast2600_eclk_भाग_प्रकारable,
			&aspeed_g6_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_ECLK] = hw;

	क्रम (i = 0; i < ARRAY_SIZE(aspeed_g6_gates); i++) अणु
		स्थिर काष्ठा aspeed_gate_data *gd = &aspeed_g6_gates[i];
		u32 gate_flags;

		/*
		 * Special हाल: the USB port 1 घड़ी (bit 14) is always
		 * working the opposite way from the other ones.
		 */
		gate_flags = (gd->घड़ी_idx == 14) ? 0 : CLK_GATE_SET_TO_DISABLE;
		hw = aspeed_g6_clk_hw_रेजिस्टर_gate(dev,
				gd->name,
				gd->parent_name,
				gd->flags,
				map,
				gd->घड़ी_idx,
				gd->reset_idx,
				gate_flags,
				&aspeed_g6_clk_lock);
		अगर (IS_ERR(hw))
			वापस PTR_ERR(hw);
		aspeed_g6_clk_data->hws[i] = hw;
	पूर्ण

	वापस 0;
पूर्ण;

अटल स्थिर काष्ठा of_device_id aspeed_g6_clk_dt_ids[] = अणु
	अणु .compatible = "aspeed,ast2600-scu" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver aspeed_g6_clk_driver = अणु
	.probe  = aspeed_g6_clk_probe,
	.driver = अणु
		.name = "ast2600-clk",
		.of_match_table = aspeed_g6_clk_dt_ids,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(aspeed_g6_clk_driver);

अटल स्थिर u32 ast2600_a0_axi_ahb_भाग_प्रकारable[] = अणु
	2, 2, 3, 5,
पूर्ण;

अटल स्थिर u32 ast2600_a1_axi_ahb_भाग0_tbl[] = अणु
	3, 2, 3, 4,
पूर्ण;

अटल स्थिर u32 ast2600_a1_axi_ahb_भाग1_tbl[] = अणु
	3, 4, 6, 8,
पूर्ण;

अटल स्थिर u32 ast2600_a1_axi_ahb200_tbl[] = अणु
	3, 4, 3, 4, 2, 2, 2, 2,
पूर्ण;

अटल व्योम __init aspeed_g6_cc(काष्ठा regmap *map)
अणु
	काष्ठा clk_hw *hw;
	u32 val, भाग, भागbits, chip_id, axi_भाग, ahb_भाग;

	clk_hw_रेजिस्टर_fixed_rate(शून्य, "clkin", शून्य, 0, 25000000);

	/*
	 * High-speed PLL घड़ी derived from the crystal. This the CPU घड़ी,
	 * and we assume that it is enabled
	 */
	regmap_पढ़ो(map, ASPEED_HPLL_PARAM, &val);
	aspeed_g6_clk_data->hws[ASPEED_CLK_HPLL] = ast2600_calc_pll("hpll", val);

	regmap_पढ़ो(map, ASPEED_MPLL_PARAM, &val);
	aspeed_g6_clk_data->hws[ASPEED_CLK_MPLL] = ast2600_calc_pll("mpll", val);

	regmap_पढ़ो(map, ASPEED_DPLL_PARAM, &val);
	aspeed_g6_clk_data->hws[ASPEED_CLK_DPLL] = ast2600_calc_pll("dpll", val);

	regmap_पढ़ो(map, ASPEED_EPLL_PARAM, &val);
	aspeed_g6_clk_data->hws[ASPEED_CLK_EPLL] = ast2600_calc_pll("epll", val);

	regmap_पढ़ो(map, ASPEED_APLL_PARAM, &val);
	aspeed_g6_clk_data->hws[ASPEED_CLK_APLL] = ast2600_calc_apll("apll", val);

	/* Strap bits 12:11 define the AXI/AHB घड़ी frequency ratio (aka HCLK)*/
	regmap_पढ़ो(map, ASPEED_G6_STRAP1, &val);
	अगर (val & BIT(16))
		axi_भाग = 1;
	अन्यथा
		axi_भाग = 2;

	भागbits = (val >> 11) & 0x3;
	regmap_पढ़ो(map, ASPEED_G6_SILICON_REV, &chip_id);
	अगर (chip_id & BIT(16)) अणु
		अगर (!भागbits) अणु
			ahb_भाग = ast2600_a1_axi_ahb200_tbl[(val >> 8) & 0x3];
			अगर (val & BIT(16))
				ahb_भाग *= 2;
		पूर्ण अन्यथा अणु
			अगर (val & BIT(16))
				ahb_भाग = ast2600_a1_axi_ahb_भाग1_tbl[भागbits];
			अन्यथा
				ahb_भाग = ast2600_a1_axi_ahb_भाग0_tbl[भागbits];
		पूर्ण
	पूर्ण अन्यथा अणु
		ahb_भाग = ast2600_a0_axi_ahb_भाग_प्रकारable[(val >> 11) & 0x3];
	पूर्ण

	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, "ahb", "hpll", 0, 1, axi_भाग * ahb_भाग);
	aspeed_g6_clk_data->hws[ASPEED_CLK_AHB] = hw;

	regmap_पढ़ो(map, ASPEED_G6_CLK_SELECTION1, &val);
	val = (val >> 23) & 0x7;
	भाग = 4 * (val + 1);
	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, "apb1", "hpll", 0, 1, भाग);
	aspeed_g6_clk_data->hws[ASPEED_CLK_APB1] = hw;

	regmap_पढ़ो(map, ASPEED_G6_CLK_SELECTION4, &val);
	val = (val >> 9) & 0x7;
	भाग = 2 * (val + 1);
	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, "apb2", "ahb", 0, 1, भाग);
	aspeed_g6_clk_data->hws[ASPEED_CLK_APB2] = hw;

	/* USB 2.0 port1 phy 40MHz घड़ी */
	hw = clk_hw_रेजिस्टर_fixed_rate(शून्य, "usb-phy-40m", शून्य, 0, 40000000);
	aspeed_g6_clk_data->hws[ASPEED_CLK_USBPHY_40M] = hw;
पूर्ण;

अटल व्योम __init aspeed_g6_cc_init(काष्ठा device_node *np)
अणु
	काष्ठा regmap *map;
	पूर्णांक ret;
	पूर्णांक i;

	scu_g6_base = of_iomap(np, 0);
	अगर (!scu_g6_base)
		वापस;

	aspeed_g6_clk_data = kzalloc(काष्ठा_size(aspeed_g6_clk_data, hws,
				      ASPEED_G6_NUM_CLKS), GFP_KERNEL);
	अगर (!aspeed_g6_clk_data)
		वापस;

	/*
	 * This way all घड़ीs fetched beक्रमe the platक्रमm device probes,
	 * except those we assign here क्रम early use, will be deferred.
	 */
	क्रम (i = 0; i < ASPEED_G6_NUM_CLKS; i++)
		aspeed_g6_clk_data->hws[i] = ERR_PTR(-EPROBE_DEFER);

	/*
	 * We check that the regmap works on this very first access,
	 * but as this is an MMIO-backed regmap, subsequent regmap
	 * access is not going to fail and we skip error checks from
	 * this poपूर्णांक.
	 */
	map = syscon_node_to_regmap(np);
	अगर (IS_ERR(map)) अणु
		pr_err("no syscon regmap\n");
		वापस;
	पूर्ण

	aspeed_g6_cc(map);
	aspeed_g6_clk_data->num = ASPEED_G6_NUM_CLKS;
	ret = of_clk_add_hw_provider(np, of_clk_hw_onecell_get, aspeed_g6_clk_data);
	अगर (ret)
		pr_err("failed to add DT provider: %d\n", ret);
पूर्ण;
CLK_OF_DECLARE_DRIVER(aspeed_cc_g6, "aspeed,ast2600-scu", aspeed_g6_cc_init);
