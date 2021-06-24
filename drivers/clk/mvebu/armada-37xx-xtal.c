<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Marvell Armada 37xx SoC xtal घड़ीs
 *
 * Copyright (C) 2016 Marvell
 *
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 *
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा NB_GPIO1_LATCH	0x8
#घोषणा XTAL_MODE	    BIT(9)

अटल पूर्णांक armada_3700_xtal_घड़ी_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर अक्षर *xtal_name = "xtal";
	काष्ठा device_node *parent;
	काष्ठा regmap *regmap;
	काष्ठा clk_hw *xtal_hw;
	अचिन्हित पूर्णांक rate;
	u32 reg;
	पूर्णांक ret;

	xtal_hw = devm_kzalloc(&pdev->dev, माप(*xtal_hw), GFP_KERNEL);
	अगर (!xtal_hw)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, xtal_hw);

	parent = np->parent;
	अगर (!parent) अणु
		dev_err(&pdev->dev, "no parent\n");
		वापस -ENODEV;
	पूर्ण

	regmap = syscon_node_to_regmap(parent);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&pdev->dev, "cannot get regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	ret = regmap_पढ़ो(regmap, NB_GPIO1_LATCH, &reg);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot read from regmap\n");
		वापस ret;
	पूर्ण

	अगर (reg & XTAL_MODE)
		rate = 40000000;
	अन्यथा
		rate = 25000000;

	of_property_पढ़ो_string_index(np, "clock-output-names", 0, &xtal_name);
	xtal_hw = clk_hw_रेजिस्टर_fixed_rate(शून्य, xtal_name, शून्य, 0, rate);
	अगर (IS_ERR(xtal_hw))
		वापस PTR_ERR(xtal_hw);
	ret = of_clk_add_hw_provider(np, of_clk_hw_simple_get, xtal_hw);

	वापस ret;
पूर्ण

अटल पूर्णांक armada_3700_xtal_घड़ी_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	of_clk_del_provider(pdev->dev.of_node);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id armada_3700_xtal_घड़ी_of_match[] = अणु
	अणु .compatible = "marvell,armada-3700-xtal-clock", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver armada_3700_xtal_घड़ी_driver = अणु
	.probe = armada_3700_xtal_घड़ी_probe,
	.हटाओ = armada_3700_xtal_घड़ी_हटाओ,
	.driver		= अणु
		.name	= "marvell-armada-3700-xtal-clock",
		.of_match_table = armada_3700_xtal_घड़ी_of_match,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(armada_3700_xtal_घड़ी_driver);
