<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Amlogic Meson8 DDR घड़ी controller
 *
 * Copyright (C) 2019 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 */

#समावेश <dt-bindings/घड़ी/meson8-ddr-clkc.h>

#समावेश <linux/clk-provider.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "clk-regmap.h"
#समावेश "clk-pll.h"

#घोषणा AM_DDR_PLL_CNTL			0x00
#घोषणा AM_DDR_PLL_CNTL1		0x04
#घोषणा AM_DDR_PLL_CNTL2		0x08
#घोषणा AM_DDR_PLL_CNTL3		0x0c
#घोषणा AM_DDR_PLL_CNTL4		0x10
#घोषणा AM_DDR_PLL_STS			0x14
#घोषणा DDR_CLK_CNTL			0x18
#घोषणा DDR_CLK_STS			0x1c

अटल काष्ठा clk_regmap meson8_ddr_pll_dco = अणु
	.data = &(काष्ठा meson_clk_pll_data)अणु
		.en = अणु
			.reg_off = AM_DDR_PLL_CNTL,
			.shअगरt   = 30,
			.width   = 1,
		पूर्ण,
		.m = अणु
			.reg_off = AM_DDR_PLL_CNTL,
			.shअगरt   = 0,
			.width   = 9,
		पूर्ण,
		.n = अणु
			.reg_off = AM_DDR_PLL_CNTL,
			.shअगरt   = 9,
			.width   = 5,
		पूर्ण,
		.l = अणु
			.reg_off = AM_DDR_PLL_CNTL,
			.shअगरt   = 31,
			.width   = 1,
		पूर्ण,
		.rst = अणु
			.reg_off = AM_DDR_PLL_CNTL,
			.shअगरt   = 29,
			.width   = 1,
		पूर्ण,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ddr_pll_dco",
		.ops = &meson_clk_pll_ro_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			.fw_name = "xtal",
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap meson8_ddr_pll = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = AM_DDR_PLL_CNTL,
		.shअगरt = 16,
		.width = 2,
		.flags = CLK_DIVIDER_POWER_OF_TWO,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ddr_pll",
		.ops = &clk_regmap_भागider_ro_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&meson8_ddr_pll_dco.hw
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data meson8_ddr_clk_hw_onecell_data = अणु
	.hws = अणु
		[DDR_CLKID_DDR_PLL_DCO]		= &meson8_ddr_pll_dco.hw,
		[DDR_CLKID_DDR_PLL]		= &meson8_ddr_pll.hw,
	पूर्ण,
	.num = 2,
पूर्ण;

अटल काष्ठा clk_regmap *स्थिर meson8_ddr_clk_regmaps[] = अणु
	&meson8_ddr_pll_dco,
	&meson8_ddr_pll,
पूर्ण;

अटल स्थिर काष्ठा regmap_config meson8_ddr_clkc_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = DDR_CLK_STS,
पूर्ण;

अटल पूर्णांक meson8_ddr_clkc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;
	व्योम __iomem *base;
	काष्ठा clk_hw *hw;
	पूर्णांक ret, i;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	regmap = devm_regmap_init_mmio(&pdev->dev, base,
				       &meson8_ddr_clkc_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/* Populate regmap */
	क्रम (i = 0; i < ARRAY_SIZE(meson8_ddr_clk_regmaps); i++)
		meson8_ddr_clk_regmaps[i]->map = regmap;

	/* Register all clks */
	क्रम (i = 0; i < meson8_ddr_clk_hw_onecell_data.num; i++) अणु
		hw = meson8_ddr_clk_hw_onecell_data.hws[i];

		ret = devm_clk_hw_रेजिस्टर(&pdev->dev, hw);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Clock registration failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस devm_of_clk_add_hw_provider(&pdev->dev, of_clk_hw_onecell_get,
					   &meson8_ddr_clk_hw_onecell_data);
पूर्ण

अटल स्थिर काष्ठा of_device_id meson8_ddr_clkc_match_table[] = अणु
	अणु .compatible = "amlogic,meson8-ddr-clkc" पूर्ण,
	अणु .compatible = "amlogic,meson8b-ddr-clkc" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver meson8_ddr_clkc_driver = अणु
	.probe		= meson8_ddr_clkc_probe,
	.driver		= अणु
		.name	= "meson8-ddr-clkc",
		.of_match_table = meson8_ddr_clkc_match_table,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(meson8_ddr_clkc_driver);
