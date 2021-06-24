<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright IBM Corp

#घोषणा pr_fmt(fmt) "clk-aspeed: " fmt

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/घड़ी/aspeed-घड़ी.h>

#समावेश "clk-aspeed.h"

#घोषणा ASPEED_NUM_CLKS		38

#घोषणा ASPEED_RESET2_OFFSET	32

#घोषणा ASPEED_RESET_CTRL	0x04
#घोषणा ASPEED_CLK_SELECTION	0x08
#घोषणा ASPEED_CLK_STOP_CTRL	0x0c
#घोषणा ASPEED_MPLL_PARAM	0x20
#घोषणा ASPEED_HPLL_PARAM	0x24
#घोषणा  AST2500_HPLL_BYPASS_EN	BIT(20)
#घोषणा  AST2400_HPLL_PROGRAMMED BIT(18)
#घोषणा  AST2400_HPLL_BYPASS_EN	BIT(17)
#घोषणा ASPEED_MISC_CTRL	0x2c
#घोषणा  UART_DIV13_EN		BIT(12)
#घोषणा ASPEED_MAC_CLK_DLY	0x48
#घोषणा ASPEED_STRAP		0x70
#घोषणा  CLKIN_25MHZ_EN		BIT(23)
#घोषणा  AST2400_CLK_SOURCE_SEL	BIT(18)
#घोषणा ASPEED_CLK_SELECTION_2	0xd8
#घोषणा ASPEED_RESET_CTRL2	0xd4

/* Globally visible घड़ीs */
अटल DEFINE_SPINLOCK(aspeed_clk_lock);

/* Keeps track of all घड़ीs */
अटल काष्ठा clk_hw_onecell_data *aspeed_clk_data;

अटल व्योम __iomem *scu_base;

/* TODO: ask Aspeed about the actual parent data */
अटल स्थिर काष्ठा aspeed_gate_data aspeed_gates[] = अणु
	/*				 clk rst   name			parent	flags */
	[ASPEED_CLK_GATE_ECLK] =	अणु  0,  6, "eclk-gate",		"eclk",	0 पूर्ण, /* Video Engine */
	[ASPEED_CLK_GATE_GCLK] =	अणु  1,  7, "gclk-gate",		शून्य,	0 पूर्ण, /* 2D engine */
	[ASPEED_CLK_GATE_MCLK] =	अणु  2, -1, "mclk-gate",		"mpll",	CLK_IS_CRITICAL पूर्ण, /* SDRAM */
	[ASPEED_CLK_GATE_VCLK] =	अणु  3, -1, "vclk-gate",		शून्य,	0 पूर्ण, /* Video Capture */
	[ASPEED_CLK_GATE_BCLK] =	अणु  4,  8, "bclk-gate",		"bclk",	CLK_IS_CRITICAL पूर्ण, /* PCIe/PCI */
	[ASPEED_CLK_GATE_DCLK] =	अणु  5, -1, "dclk-gate",		शून्य,	CLK_IS_CRITICAL पूर्ण, /* DAC */
	[ASPEED_CLK_GATE_REFCLK] =	अणु  6, -1, "refclk-gate",	"clkin", CLK_IS_CRITICAL पूर्ण,
	[ASPEED_CLK_GATE_USBPORT2CLK] =	अणु  7,  3, "usb-port2-gate",	शून्य,	0 पूर्ण, /* USB2.0 Host port 2 */
	[ASPEED_CLK_GATE_LCLK] =	अणु  8,  5, "lclk-gate",		शून्य,	0 पूर्ण, /* LPC */
	[ASPEED_CLK_GATE_USBUHCICLK] =	अणु  9, 15, "usb-uhci-gate",	शून्य,	0 पूर्ण, /* USB1.1 (requires port 2 enabled) */
	[ASPEED_CLK_GATE_D1CLK] =	अणु 10, 13, "d1clk-gate",		शून्य,	0 पूर्ण, /* GFX CRT */
	[ASPEED_CLK_GATE_YCLK] =	अणु 13,  4, "yclk-gate",		शून्य,	0 पूर्ण, /* HAC */
	[ASPEED_CLK_GATE_USBPORT1CLK] = अणु 14, 14, "usb-port1-gate",	शून्य,	0 पूर्ण, /* USB2 hub/USB2 host port 1/USB1.1 dev */
	[ASPEED_CLK_GATE_UART1CLK] =	अणु 15, -1, "uart1clk-gate",	"uart",	0 पूर्ण, /* UART1 */
	[ASPEED_CLK_GATE_UART2CLK] =	अणु 16, -1, "uart2clk-gate",	"uart",	0 पूर्ण, /* UART2 */
	[ASPEED_CLK_GATE_UART5CLK] =	अणु 17, -1, "uart5clk-gate",	"uart",	0 पूर्ण, /* UART5 */
	[ASPEED_CLK_GATE_ESPICLK] =	अणु 19, -1, "espiclk-gate",	शून्य,	0 पूर्ण, /* eSPI */
	[ASPEED_CLK_GATE_MAC1CLK] =	अणु 20, 11, "mac1clk-gate",	"mac",	0 पूर्ण, /* MAC1 */
	[ASPEED_CLK_GATE_MAC2CLK] =	अणु 21, 12, "mac2clk-gate",	"mac",	0 पूर्ण, /* MAC2 */
	[ASPEED_CLK_GATE_RSACLK] =	अणु 24, -1, "rsaclk-gate",	शून्य,	0 पूर्ण, /* RSA */
	[ASPEED_CLK_GATE_UART3CLK] =	अणु 25, -1, "uart3clk-gate",	"uart",	0 पूर्ण, /* UART3 */
	[ASPEED_CLK_GATE_UART4CLK] =	अणु 26, -1, "uart4clk-gate",	"uart",	0 पूर्ण, /* UART4 */
	[ASPEED_CLK_GATE_SDCLK] =	अणु 27, 16, "sdclk-gate",		शून्य,	0 पूर्ण, /* SDIO/SD */
	[ASPEED_CLK_GATE_LHCCLK] =	अणु 28, -1, "lhclk-gate",		"lhclk", 0 पूर्ण, /* LPC master/LPC+ */
पूर्ण;

अटल स्थिर अक्षर * स्थिर eclk_parent_names[] = अणु
	"mpll",
	"hpll",
	"dpll",
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable ast2500_eclk_भाग_प्रकारable[] = अणु
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

अटल स्थिर काष्ठा clk_भाग_प्रकारable ast2500_mac_भाग_प्रकारable[] = अणु
	अणु 0x0, 4 पूर्ण, /* Yep, really. Aspeed confirmed this is correct */
	अणु 0x1, 4 पूर्ण,
	अणु 0x2, 6 पूर्ण,
	अणु 0x3, 8 पूर्ण,
	अणु 0x4, 10 पूर्ण,
	अणु 0x5, 12 पूर्ण,
	अणु 0x6, 14 पूर्ण,
	अणु 0x7, 16 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable ast2400_भाग_प्रकारable[] = अणु
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

अटल स्थिर काष्ठा clk_भाग_प्रकारable ast2500_भाग_प्रकारable[] = अणु
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

अटल काष्ठा clk_hw *aspeed_ast2400_calc_pll(स्थिर अक्षर *name, u32 val)
अणु
	अचिन्हित पूर्णांक mult, भाग;

	अगर (val & AST2400_HPLL_BYPASS_EN) अणु
		/* Pass through mode */
		mult = भाग = 1;
	पूर्ण अन्यथा अणु
		/* F = 24Mhz * (2-OD) * [(N + 2) / (D + 1)] */
		u32 n = (val >> 5) & 0x3f;
		u32 od = (val >> 4) & 0x1;
		u32 d = val & 0xf;

		mult = (2 - od) * (n + 2);
		भाग = d + 1;
	पूर्ण
	वापस clk_hw_रेजिस्टर_fixed_factor(शून्य, name, "clkin", 0,
			mult, भाग);
पूर्ण;

अटल काष्ठा clk_hw *aspeed_ast2500_calc_pll(स्थिर अक्षर *name, u32 val)
अणु
	अचिन्हित पूर्णांक mult, भाग;

	अगर (val & AST2500_HPLL_BYPASS_EN) अणु
		/* Pass through mode */
		mult = भाग = 1;
	पूर्ण अन्यथा अणु
		/* F = clkin * [(M+1) / (N+1)] / (P + 1) */
		u32 p = (val >> 13) & 0x3f;
		u32 m = (val >> 5) & 0xff;
		u32 n = val & 0x1f;

		mult = (m + 1) / (n + 1);
		भाग = p + 1;
	पूर्ण

	वापस clk_hw_रेजिस्टर_fixed_factor(शून्य, name, "clkin", 0,
			mult, भाग);
पूर्ण

अटल स्थिर काष्ठा aspeed_clk_soc_data ast2500_data = अणु
	.भाग_प्रकारable = ast2500_भाग_प्रकारable,
	.eclk_भाग_प्रकारable = ast2500_eclk_भाग_प्रकारable,
	.mac_भाग_प्रकारable = ast2500_mac_भाग_प्रकारable,
	.calc_pll = aspeed_ast2500_calc_pll,
पूर्ण;

अटल स्थिर काष्ठा aspeed_clk_soc_data ast2400_data = अणु
	.भाग_प्रकारable = ast2400_भाग_प्रकारable,
	.eclk_भाग_प्रकारable = ast2400_भाग_प्रकारable,
	.mac_भाग_प्रकारable = ast2400_भाग_प्रकारable,
	.calc_pll = aspeed_ast2400_calc_pll,
पूर्ण;

अटल पूर्णांक aspeed_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा aspeed_clk_gate *gate = to_aspeed_clk_gate(hw);
	u32 clk = BIT(gate->घड़ी_idx);
	u32 rst = BIT(gate->reset_idx);
	u32 enval = (gate->flags & CLK_GATE_SET_TO_DISABLE) ? 0 : clk;
	u32 reg;

	/*
	 * If the IP is in reset, treat the घड़ी as not enabled,
	 * this happens with some घड़ीs such as the USB one when
	 * coming from cold reset. Without this, aspeed_clk_enable()
	 * will fail to lअगरt the reset.
	 */
	अगर (gate->reset_idx >= 0) अणु
		regmap_पढ़ो(gate->map, ASPEED_RESET_CTRL, &reg);
		अगर (reg & rst)
			वापस 0;
	पूर्ण

	regmap_पढ़ो(gate->map, ASPEED_CLK_STOP_CTRL, &reg);

	वापस ((reg & clk) == enval) ? 1 : 0;
पूर्ण

अटल पूर्णांक aspeed_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा aspeed_clk_gate *gate = to_aspeed_clk_gate(hw);
	अचिन्हित दीर्घ flags;
	u32 clk = BIT(gate->घड़ी_idx);
	u32 rst = BIT(gate->reset_idx);
	u32 enval;

	spin_lock_irqsave(gate->lock, flags);

	अगर (aspeed_clk_is_enabled(hw)) अणु
		spin_unlock_irqrestore(gate->lock, flags);
		वापस 0;
	पूर्ण

	अगर (gate->reset_idx >= 0) अणु
		/* Put IP in reset */
		regmap_update_bits(gate->map, ASPEED_RESET_CTRL, rst, rst);

		/* Delay 100us */
		udelay(100);
	पूर्ण

	/* Enable घड़ी */
	enval = (gate->flags & CLK_GATE_SET_TO_DISABLE) ? 0 : clk;
	regmap_update_bits(gate->map, ASPEED_CLK_STOP_CTRL, clk, enval);

	अगर (gate->reset_idx >= 0) अणु
		/* A delay of 10ms is specअगरied by the ASPEED करोcs */
		mdelay(10);

		/* Take IP out of reset */
		regmap_update_bits(gate->map, ASPEED_RESET_CTRL, rst, 0);
	पूर्ण

	spin_unlock_irqrestore(gate->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम aspeed_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा aspeed_clk_gate *gate = to_aspeed_clk_gate(hw);
	अचिन्हित दीर्घ flags;
	u32 clk = BIT(gate->घड़ी_idx);
	u32 enval;

	spin_lock_irqsave(gate->lock, flags);

	enval = (gate->flags & CLK_GATE_SET_TO_DISABLE) ? clk : 0;
	regmap_update_bits(gate->map, ASPEED_CLK_STOP_CTRL, clk, enval);

	spin_unlock_irqrestore(gate->lock, flags);
पूर्ण

अटल स्थिर काष्ठा clk_ops aspeed_clk_gate_ops = अणु
	.enable = aspeed_clk_enable,
	.disable = aspeed_clk_disable,
	.is_enabled = aspeed_clk_is_enabled,
पूर्ण;

अटल स्थिर u8 aspeed_resets[] = अणु
	/* SCU04 resets */
	[ASPEED_RESET_XDMA]	= 25,
	[ASPEED_RESET_MCTP]	= 24,
	[ASPEED_RESET_ADC]	= 23,
	[ASPEED_RESET_JTAG_MASTER] = 22,
	[ASPEED_RESET_MIC]	= 18,
	[ASPEED_RESET_PWM]	=  9,
	[ASPEED_RESET_PECI]	= 10,
	[ASPEED_RESET_I2C]	=  2,
	[ASPEED_RESET_AHB]	=  1,

	/*
	 * SCUD4 resets start at an offset to separate them from
	 * the SCU04 resets.
	 */
	[ASPEED_RESET_CRT1]	= ASPEED_RESET2_OFFSET + 5,
पूर्ण;

अटल पूर्णांक aspeed_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				 अचिन्हित दीर्घ id)
अणु
	काष्ठा aspeed_reset *ar = to_aspeed_reset(rcdev);
	u32 reg = ASPEED_RESET_CTRL;
	u32 bit = aspeed_resets[id];

	अगर (bit >= ASPEED_RESET2_OFFSET) अणु
		bit -= ASPEED_RESET2_OFFSET;
		reg = ASPEED_RESET_CTRL2;
	पूर्ण

	वापस regmap_update_bits(ar->map, reg, BIT(bit), 0);
पूर्ण

अटल पूर्णांक aspeed_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	काष्ठा aspeed_reset *ar = to_aspeed_reset(rcdev);
	u32 reg = ASPEED_RESET_CTRL;
	u32 bit = aspeed_resets[id];

	अगर (bit >= ASPEED_RESET2_OFFSET) अणु
		bit -= ASPEED_RESET2_OFFSET;
		reg = ASPEED_RESET_CTRL2;
	पूर्ण

	वापस regmap_update_bits(ar->map, reg, BIT(bit), BIT(bit));
पूर्ण

अटल पूर्णांक aspeed_reset_status(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	काष्ठा aspeed_reset *ar = to_aspeed_reset(rcdev);
	u32 reg = ASPEED_RESET_CTRL;
	u32 bit = aspeed_resets[id];
	पूर्णांक ret, val;

	अगर (bit >= ASPEED_RESET2_OFFSET) अणु
		bit -= ASPEED_RESET2_OFFSET;
		reg = ASPEED_RESET_CTRL2;
	पूर्ण

	ret = regmap_पढ़ो(ar->map, reg, &val);
	अगर (ret)
		वापस ret;

	वापस !!(val & BIT(bit));
पूर्ण

अटल स्थिर काष्ठा reset_control_ops aspeed_reset_ops = अणु
	.निश्चित = aspeed_reset_निश्चित,
	.deनिश्चित = aspeed_reset_deनिश्चित,
	.status = aspeed_reset_status,
पूर्ण;

अटल काष्ठा clk_hw *aspeed_clk_hw_रेजिस्टर_gate(काष्ठा device *dev,
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
	init.ops = &aspeed_clk_gate_ops;
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

अटल पूर्णांक aspeed_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा aspeed_clk_soc_data *soc_data;
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
	ar->rcdev.nr_resets = ARRAY_SIZE(aspeed_resets);
	ar->rcdev.ops = &aspeed_reset_ops;
	ar->rcdev.of_node = dev->of_node;

	ret = devm_reset_controller_रेजिस्टर(dev, &ar->rcdev);
	अगर (ret) अणु
		dev_err(dev, "could not register reset controller\n");
		वापस ret;
	पूर्ण

	/* SoC generations share common layouts but have dअगरferent भागisors */
	soc_data = of_device_get_match_data(dev);
	अगर (!soc_data) अणु
		dev_err(dev, "no match data for platform\n");
		वापस -EINVAL;
	पूर्ण

	/* UART घड़ी भाग13 setting */
	regmap_पढ़ो(map, ASPEED_MISC_CTRL, &val);
	अगर (val & UART_DIV13_EN)
		rate = 24000000 / 13;
	अन्यथा
		rate = 24000000;
	/* TODO: Find the parent data क्रम the uart घड़ी */
	hw = clk_hw_रेजिस्टर_fixed_rate(dev, "uart", शून्य, 0, rate);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_clk_data->hws[ASPEED_CLK_UART] = hw;

	/*
	 * Memory controller (M-PLL) PLL. This घड़ी is configured by the
	 * bootloader, and is exposed to Linux as a पढ़ो-only घड़ी rate.
	 */
	regmap_पढ़ो(map, ASPEED_MPLL_PARAM, &val);
	hw = soc_data->calc_pll("mpll", val);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_clk_data->hws[ASPEED_CLK_MPLL] =	hw;

	/* SD/SDIO घड़ी भागider and gate */
	hw = clk_hw_रेजिस्टर_gate(dev, "sd_extclk_gate", "hpll", 0,
				  scu_base + ASPEED_CLK_SELECTION, 15, 0,
				  &aspeed_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	hw = clk_hw_रेजिस्टर_भागider_table(dev, "sd_extclk", "sd_extclk_gate",
			0, scu_base + ASPEED_CLK_SELECTION, 12, 3, 0,
			soc_data->भाग_प्रकारable,
			&aspeed_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_clk_data->hws[ASPEED_CLK_SDIO] = hw;

	/* MAC AHB bus घड़ी भागider */
	hw = clk_hw_रेजिस्टर_भागider_table(dev, "mac", "hpll", 0,
			scu_base + ASPEED_CLK_SELECTION, 16, 3, 0,
			soc_data->mac_भाग_प्रकारable,
			&aspeed_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_clk_data->hws[ASPEED_CLK_MAC] = hw;

	अगर (of_device_is_compatible(pdev->dev.of_node, "aspeed,ast2500-scu")) अणु
		/* RMII 50MHz RCLK */
		hw = clk_hw_रेजिस्टर_fixed_rate(dev, "mac12rclk", "hpll", 0,
						50000000);
		अगर (IS_ERR(hw))
			वापस PTR_ERR(hw);

		/* RMII1 50MHz (RCLK) output enable */
		hw = clk_hw_रेजिस्टर_gate(dev, "mac1rclk", "mac12rclk", 0,
				scu_base + ASPEED_MAC_CLK_DLY, 29, 0,
				&aspeed_clk_lock);
		अगर (IS_ERR(hw))
			वापस PTR_ERR(hw);
		aspeed_clk_data->hws[ASPEED_CLK_MAC1RCLK] = hw;

		/* RMII2 50MHz (RCLK) output enable */
		hw = clk_hw_रेजिस्टर_gate(dev, "mac2rclk", "mac12rclk", 0,
				scu_base + ASPEED_MAC_CLK_DLY, 30, 0,
				&aspeed_clk_lock);
		अगर (IS_ERR(hw))
			वापस PTR_ERR(hw);
		aspeed_clk_data->hws[ASPEED_CLK_MAC2RCLK] = hw;
	पूर्ण

	/* LPC Host (LHCLK) घड़ी भागider */
	hw = clk_hw_रेजिस्टर_भागider_table(dev, "lhclk", "hpll", 0,
			scu_base + ASPEED_CLK_SELECTION, 20, 3, 0,
			soc_data->भाग_प्रकारable,
			&aspeed_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_clk_data->hws[ASPEED_CLK_LHCLK] = hw;

	/* P-Bus (BCLK) घड़ी भागider */
	hw = clk_hw_रेजिस्टर_भागider_table(dev, "bclk", "hpll", 0,
			scu_base + ASPEED_CLK_SELECTION_2, 0, 2, 0,
			soc_data->भाग_प्रकारable,
			&aspeed_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_clk_data->hws[ASPEED_CLK_BCLK] = hw;

	/* Fixed 24MHz घड़ी */
	hw = clk_hw_रेजिस्टर_fixed_rate(शून्य, "fixed-24m", "clkin",
					0, 24000000);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_clk_data->hws[ASPEED_CLK_24M] = hw;

	hw = clk_hw_रेजिस्टर_mux(dev, "eclk-mux", eclk_parent_names,
				 ARRAY_SIZE(eclk_parent_names), 0,
				 scu_base + ASPEED_CLK_SELECTION, 2, 0x3, 0,
				 &aspeed_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_clk_data->hws[ASPEED_CLK_ECLK_MUX] = hw;

	hw = clk_hw_रेजिस्टर_भागider_table(dev, "eclk", "eclk-mux", 0,
					   scu_base + ASPEED_CLK_SELECTION, 28,
					   3, 0, soc_data->eclk_भाग_प्रकारable,
					   &aspeed_clk_lock);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	aspeed_clk_data->hws[ASPEED_CLK_ECLK] = hw;

	/*
	 * TODO: There are a number of घड़ीs that not included in this driver
	 * as more inक्रमmation is required:
	 *   D2-PLL
	 *   D-PLL
	 *   YCLK
	 *   RGMII
	 *   RMII
	 *   UART[1..5] घड़ी source mux
	 */

	क्रम (i = 0; i < ARRAY_SIZE(aspeed_gates); i++) अणु
		स्थिर काष्ठा aspeed_gate_data *gd = &aspeed_gates[i];
		u32 gate_flags;

		/* Special हाल: the USB port 1 घड़ी (bit 14) is always
		 * working the opposite way from the other ones.
		 */
		gate_flags = (gd->घड़ी_idx == 14) ? 0 : CLK_GATE_SET_TO_DISABLE;
		hw = aspeed_clk_hw_रेजिस्टर_gate(dev,
				gd->name,
				gd->parent_name,
				gd->flags,
				map,
				gd->घड़ी_idx,
				gd->reset_idx,
				gate_flags,
				&aspeed_clk_lock);
		अगर (IS_ERR(hw))
			वापस PTR_ERR(hw);
		aspeed_clk_data->hws[i] = hw;
	पूर्ण

	वापस 0;
पूर्ण;

अटल स्थिर काष्ठा of_device_id aspeed_clk_dt_ids[] = अणु
	अणु .compatible = "aspeed,ast2400-scu", .data = &ast2400_data पूर्ण,
	अणु .compatible = "aspeed,ast2500-scu", .data = &ast2500_data पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver aspeed_clk_driver = अणु
	.probe  = aspeed_clk_probe,
	.driver = अणु
		.name = "aspeed-clk",
		.of_match_table = aspeed_clk_dt_ids,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(aspeed_clk_driver);

अटल व्योम __init aspeed_ast2400_cc(काष्ठा regmap *map)
अणु
	काष्ठा clk_hw *hw;
	u32 val, भाग, clkin, hpll;
	स्थिर u16 hpll_rates[][4] = अणु
		अणु384, 360, 336, 408पूर्ण,
		अणु400, 375, 350, 425पूर्ण,
	पूर्ण;
	पूर्णांक rate;

	/*
	 * CLKIN is the crystal oscillator, 24, 48 or 25MHz selected by
	 * strapping
	 */
	regmap_पढ़ो(map, ASPEED_STRAP, &val);
	rate = (val >> 8) & 3;
	अगर (val & CLKIN_25MHZ_EN) अणु
		clkin = 25000000;
		hpll = hpll_rates[1][rate];
	पूर्ण अन्यथा अगर (val & AST2400_CLK_SOURCE_SEL) अणु
		clkin = 48000000;
		hpll = hpll_rates[0][rate];
	पूर्ण अन्यथा अणु
		clkin = 24000000;
		hpll = hpll_rates[0][rate];
	पूर्ण
	hw = clk_hw_रेजिस्टर_fixed_rate(शून्य, "clkin", शून्य, 0, clkin);
	pr_debug("clkin @%u MHz\n", clkin / 1000000);

	/*
	 * High-speed PLL घड़ी derived from the crystal. This the CPU घड़ी,
	 * and we assume that it is enabled. It can be configured through the
	 * HPLL_PARAM रेजिस्टर, or set to a specअगरied frequency by strapping.
	 */
	regmap_पढ़ो(map, ASPEED_HPLL_PARAM, &val);
	अगर (val & AST2400_HPLL_PROGRAMMED)
		hw = aspeed_ast2400_calc_pll("hpll", val);
	अन्यथा
		hw = clk_hw_रेजिस्टर_fixed_rate(शून्य, "hpll", "clkin", 0,
				hpll * 1000000);

	aspeed_clk_data->hws[ASPEED_CLK_HPLL] = hw;

	/*
	 * Strap bits 11:10 define the CPU/AHB घड़ी frequency ratio (aka HCLK)
	 *   00: Select CPU:AHB = 1:1
	 *   01: Select CPU:AHB = 2:1
	 *   10: Select CPU:AHB = 4:1
	 *   11: Select CPU:AHB = 3:1
	 */
	regmap_पढ़ो(map, ASPEED_STRAP, &val);
	val = (val >> 10) & 0x3;
	भाग = val + 1;
	अगर (भाग == 3)
		भाग = 4;
	अन्यथा अगर (भाग == 4)
		भाग = 3;
	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, "ahb", "hpll", 0, 1, भाग);
	aspeed_clk_data->hws[ASPEED_CLK_AHB] = hw;

	/* APB घड़ी घड़ी selection रेजिस्टर SCU08 (aka PCLK) */
	hw = clk_hw_रेजिस्टर_भागider_table(शून्य, "apb", "hpll", 0,
			scu_base + ASPEED_CLK_SELECTION, 23, 3, 0,
			ast2400_भाग_प्रकारable,
			&aspeed_clk_lock);
	aspeed_clk_data->hws[ASPEED_CLK_APB] = hw;
पूर्ण

अटल व्योम __init aspeed_ast2500_cc(काष्ठा regmap *map)
अणु
	काष्ठा clk_hw *hw;
	u32 val, freq, भाग;

	/* CLKIN is the crystal oscillator, 24 or 25MHz selected by strapping */
	regmap_पढ़ो(map, ASPEED_STRAP, &val);
	अगर (val & CLKIN_25MHZ_EN)
		freq = 25000000;
	अन्यथा
		freq = 24000000;
	hw = clk_hw_रेजिस्टर_fixed_rate(शून्य, "clkin", शून्य, 0, freq);
	pr_debug("clkin @%u MHz\n", freq / 1000000);

	/*
	 * High-speed PLL घड़ी derived from the crystal. This the CPU घड़ी,
	 * and we assume that it is enabled
	 */
	regmap_पढ़ो(map, ASPEED_HPLL_PARAM, &val);
	aspeed_clk_data->hws[ASPEED_CLK_HPLL] = aspeed_ast2500_calc_pll("hpll", val);

	/* Strap bits 11:9 define the AXI/AHB घड़ी frequency ratio (aka HCLK)*/
	regmap_पढ़ो(map, ASPEED_STRAP, &val);
	val = (val >> 9) & 0x7;
	WARN(val == 0, "strapping is zero: cannot determine ahb clock");
	भाग = 2 * (val + 1);
	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, "ahb", "hpll", 0, 1, भाग);
	aspeed_clk_data->hws[ASPEED_CLK_AHB] = hw;

	/* APB घड़ी घड़ी selection रेजिस्टर SCU08 (aka PCLK) */
	regmap_पढ़ो(map, ASPEED_CLK_SELECTION, &val);
	val = (val >> 23) & 0x7;
	भाग = 4 * (val + 1);
	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, "apb", "hpll", 0, 1, भाग);
	aspeed_clk_data->hws[ASPEED_CLK_APB] = hw;
पूर्ण;

अटल व्योम __init aspeed_cc_init(काष्ठा device_node *np)
अणु
	काष्ठा regmap *map;
	u32 val;
	पूर्णांक ret;
	पूर्णांक i;

	scu_base = of_iomap(np, 0);
	अगर (!scu_base)
		वापस;

	aspeed_clk_data = kzalloc(काष्ठा_size(aspeed_clk_data, hws,
					      ASPEED_NUM_CLKS),
				  GFP_KERNEL);
	अगर (!aspeed_clk_data)
		वापस;

	/*
	 * This way all घड़ीs fetched beक्रमe the platक्रमm device probes,
	 * except those we assign here क्रम early use, will be deferred.
	 */
	क्रम (i = 0; i < ASPEED_NUM_CLKS; i++)
		aspeed_clk_data->hws[i] = ERR_PTR(-EPROBE_DEFER);

	map = syscon_node_to_regmap(np);
	अगर (IS_ERR(map)) अणु
		pr_err("no syscon regmap\n");
		वापस;
	पूर्ण
	/*
	 * We check that the regmap works on this very first access,
	 * but as this is an MMIO-backed regmap, subsequent regmap
	 * access is not going to fail and we skip error checks from
	 * this poपूर्णांक.
	 */
	ret = regmap_पढ़ो(map, ASPEED_STRAP, &val);
	अगर (ret) अणु
		pr_err("failed to read strapping register\n");
		वापस;
	पूर्ण

	अगर (of_device_is_compatible(np, "aspeed,ast2400-scu"))
		aspeed_ast2400_cc(map);
	अन्यथा अगर (of_device_is_compatible(np, "aspeed,ast2500-scu"))
		aspeed_ast2500_cc(map);
	अन्यथा
		pr_err("unknown platform, failed to add clocks\n");

	aspeed_clk_data->num = ASPEED_NUM_CLKS;
	ret = of_clk_add_hw_provider(np, of_clk_hw_onecell_get, aspeed_clk_data);
	अगर (ret)
		pr_err("failed to add DT provider: %d\n", ret);
पूर्ण;
CLK_OF_DECLARE_DRIVER(aspeed_cc_g5, "aspeed,ast2500-scu", aspeed_cc_init);
CLK_OF_DECLARE_DRIVER(aspeed_cc_g4, "aspeed,ast2400-scu", aspeed_cc_init);
