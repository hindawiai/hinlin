<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 ROHM Semiconductors

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/rohm-generic.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/regmap.h>

/* clk control रेजिस्टरs */
/* BD71815 */
#घोषणा BD71815_REG_OUT32K	0x1d
/* BD70528 */
#घोषणा BD70528_REG_OUT32K	0x2c
/* BD71828 */
#घोषणा BD71828_REG_OUT32K	0x4B
/* BD71837 and BD71847 */
#घोषणा BD718XX_REG_OUT32K	0x2E

/*
 * BD71837, BD71847, BD70528 and BD71828 all use bit [0] to clk output control
 */
#घोषणा CLK_OUT_EN_MASK		BIT(0)


काष्ठा bd718xx_clk अणु
	काष्ठा clk_hw hw;
	u8 reg;
	u8 mask;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा regmap *regmap;
पूर्ण;

अटल पूर्णांक bd71837_clk_set(काष्ठा bd718xx_clk *c, अचिन्हित पूर्णांक status)
अणु
	वापस regmap_update_bits(c->regmap, c->reg, c->mask, status);
पूर्ण

अटल व्योम bd71837_clk_disable(काष्ठा clk_hw *hw)
अणु
	पूर्णांक rv;
	काष्ठा bd718xx_clk *c = container_of(hw, काष्ठा bd718xx_clk, hw);

	rv = bd71837_clk_set(c, 0);
	अगर (rv)
		dev_dbg(&c->pdev->dev, "Failed to disable 32K clk (%d)\n", rv);
पूर्ण

अटल पूर्णांक bd71837_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा bd718xx_clk *c = container_of(hw, काष्ठा bd718xx_clk, hw);

	वापस bd71837_clk_set(c, 0xffffffff);
पूर्ण

अटल पूर्णांक bd71837_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	पूर्णांक enabled;
	पूर्णांक rval;
	काष्ठा bd718xx_clk *c = container_of(hw, काष्ठा bd718xx_clk, hw);

	rval = regmap_पढ़ो(c->regmap, c->reg, &enabled);

	अगर (rval)
		वापस rval;

	वापस enabled & c->mask;
पूर्ण

अटल स्थिर काष्ठा clk_ops bd71837_clk_ops = अणु
	.prepare = &bd71837_clk_enable,
	.unprepare = &bd71837_clk_disable,
	.is_prepared = &bd71837_clk_is_enabled,
पूर्ण;

अटल पूर्णांक bd71837_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bd718xx_clk *c;
	पूर्णांक rval = -ENOMEM;
	स्थिर अक्षर *parent_clk;
	काष्ठा device *parent = pdev->dev.parent;
	काष्ठा clk_init_data init = अणु
		.name = "bd718xx-32k-out",
		.ops = &bd71837_clk_ops,
	पूर्ण;
	क्रमागत rohm_chip_type chip = platक्रमm_get_device_id(pdev)->driver_data;

	c = devm_kzalloc(&pdev->dev, माप(*c), GFP_KERNEL);
	अगर (!c)
		वापस -ENOMEM;

	c->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!c->regmap)
		वापस -ENODEV;

	init.num_parents = 1;
	parent_clk = of_clk_get_parent_name(parent->of_node, 0);

	init.parent_names = &parent_clk;
	अगर (!parent_clk) अणु
		dev_err(&pdev->dev, "No parent clk found\n");
		वापस -EINVAL;
	पूर्ण
	चयन (chip) अणु
	हाल ROHM_CHIP_TYPE_BD71837:
	हाल ROHM_CHIP_TYPE_BD71847:
		c->reg = BD718XX_REG_OUT32K;
		c->mask = CLK_OUT_EN_MASK;
		अवरोध;
	हाल ROHM_CHIP_TYPE_BD71828:
		c->reg = BD71828_REG_OUT32K;
		c->mask = CLK_OUT_EN_MASK;
		अवरोध;
	हाल ROHM_CHIP_TYPE_BD70528:
		c->reg = BD70528_REG_OUT32K;
		c->mask = CLK_OUT_EN_MASK;
		अवरोध;
	हाल ROHM_CHIP_TYPE_BD71815:
		c->reg = BD71815_REG_OUT32K;
		c->mask = CLK_OUT_EN_MASK;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unknown clk chip\n");
		वापस -EINVAL;
	पूर्ण
	c->pdev = pdev;
	c->hw.init = &init;

	of_property_पढ़ो_string_index(parent->of_node,
				      "clock-output-names", 0, &init.name);

	rval = devm_clk_hw_रेजिस्टर(&pdev->dev, &c->hw);
	अगर (rval) अणु
		dev_err(&pdev->dev, "failed to register 32K clk");
		वापस rval;
	पूर्ण
	rval = devm_of_clk_add_hw_provider(&pdev->dev, of_clk_hw_simple_get,
					   &c->hw);
	अगर (rval)
		dev_err(&pdev->dev, "adding clk provider failed\n");

	वापस rval;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id bd718x7_clk_id[] = अणु
	अणु "bd71837-clk", ROHM_CHIP_TYPE_BD71837 पूर्ण,
	अणु "bd71847-clk", ROHM_CHIP_TYPE_BD71847 पूर्ण,
	अणु "bd70528-clk", ROHM_CHIP_TYPE_BD70528 पूर्ण,
	अणु "bd71828-clk", ROHM_CHIP_TYPE_BD71828 पूर्ण,
	अणु "bd71815-clk", ROHM_CHIP_TYPE_BD71815 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, bd718x7_clk_id);

अटल काष्ठा platक्रमm_driver bd71837_clk = अणु
	.driver = अणु
		.name = "bd718xx-clk",
	पूर्ण,
	.probe = bd71837_clk_probe,
	.id_table = bd718x7_clk_id,
पूर्ण;

module_platक्रमm_driver(bd71837_clk);

MODULE_AUTHOR("Matti Vaittinen <matti.vaittinen@fi.rohmeurope.com>");
MODULE_DESCRIPTION("BD718(15/18/28/37/47/50) and BD70528 chip clk driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:bd718xx-clk");
