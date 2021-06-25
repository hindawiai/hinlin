<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2019 Bootlin
 * Author: Paul Kocialkowski <paul.kocialkowski@bootlin.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>

#घोषणा LOGICVC_CTRL_REG		0x40
#घोषणा LOGICVC_CTRL_GPIO_SHIFT		11
#घोषणा LOGICVC_CTRL_GPIO_BITS		5

#घोषणा LOGICVC_POWER_CTRL_REG		0x78
#घोषणा LOGICVC_POWER_CTRL_GPIO_SHIFT	0
#घोषणा LOGICVC_POWER_CTRL_GPIO_BITS	4

काष्ठा logicvc_gpio अणु
	काष्ठा gpio_chip chip;
	काष्ठा regmap *regmap;
पूर्ण;

अटल व्योम logicvc_gpio_offset(काष्ठा logicvc_gpio *logicvc, अचिन्हित offset,
				अचिन्हित पूर्णांक *reg, अचिन्हित पूर्णांक *bit)
अणु
	अगर (offset >= LOGICVC_CTRL_GPIO_BITS) अणु
		*reg = LOGICVC_POWER_CTRL_REG;

		/* To the (भव) घातer ctrl offset. */
		offset -= LOGICVC_CTRL_GPIO_BITS;
		/* To the actual bit offset in reg. */
		offset += LOGICVC_POWER_CTRL_GPIO_SHIFT;
	पूर्ण अन्यथा अणु
		*reg = LOGICVC_CTRL_REG;

		/* To the actual bit offset in reg. */
		offset += LOGICVC_CTRL_GPIO_SHIFT;
	पूर्ण

	*bit = BIT(offset);
पूर्ण

अटल पूर्णांक logicvc_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा logicvc_gpio *logicvc = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक reg, bit, value;
	पूर्णांक ret;

	logicvc_gpio_offset(logicvc, offset, &reg, &bit);

	ret = regmap_पढ़ो(logicvc->regmap, reg, &value);
	अगर (ret)
		वापस ret;

	वापस !!(value & bit);
पूर्ण

अटल व्योम logicvc_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा logicvc_gpio *logicvc = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक reg, bit;

	logicvc_gpio_offset(logicvc, offset, &reg, &bit);

	regmap_update_bits(logicvc->regmap, reg, bit, value ? bit : 0);
पूर्ण

अटल पूर्णांक logicvc_gpio_direction_output(काष्ठा gpio_chip *chip,
					 अचिन्हित offset, पूर्णांक value)
अणु
	/* Pins are always configured as output, so just set the value. */
	logicvc_gpio_set(chip, offset, value);

	वापस 0;
पूर्ण

अटल काष्ठा regmap_config logicvc_gpio_regmap_config = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.name		= "logicvc-gpio",
पूर्ण;

अटल पूर्णांक logicvc_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *of_node = dev->of_node;
	काष्ठा logicvc_gpio *logicvc;
	पूर्णांक ret;

	logicvc = devm_kzalloc(dev, माप(*logicvc), GFP_KERNEL);
	अगर (!logicvc)
		वापस -ENOMEM;

	/* Try to get regmap from parent first. */
	logicvc->regmap = syscon_node_to_regmap(of_node->parent);

	/* Grab our own regmap अगर that fails. */
	अगर (IS_ERR(logicvc->regmap)) अणु
		काष्ठा resource res;
		व्योम __iomem *base;

		ret = of_address_to_resource(of_node, 0, &res);
		अगर (ret) अणु
			dev_err(dev, "Failed to get resource from address\n");
			वापस ret;
		पूर्ण

		base = devm_ioremap_resource(dev, &res);
		अगर (IS_ERR(base)) अणु
			dev_err(dev, "Failed to map I/O base\n");
			वापस PTR_ERR(base);
		पूर्ण

		logicvc_gpio_regmap_config.max_रेजिस्टर = resource_size(&res) -
			logicvc_gpio_regmap_config.reg_stride;

		logicvc->regmap =
			devm_regmap_init_mmio(dev, base,
					      &logicvc_gpio_regmap_config);
		अगर (IS_ERR(logicvc->regmap)) अणु
			dev_err(dev, "Failed to create regmap for I/O\n");
			वापस PTR_ERR(logicvc->regmap);
		पूर्ण
	पूर्ण

	logicvc->chip.parent = dev;
	logicvc->chip.owner = THIS_MODULE;
	logicvc->chip.label = dev_name(dev);
	logicvc->chip.base = -1;
	logicvc->chip.ngpio = LOGICVC_CTRL_GPIO_BITS +
			      LOGICVC_POWER_CTRL_GPIO_BITS;
	logicvc->chip.get = logicvc_gpio_get;
	logicvc->chip.set = logicvc_gpio_set;
	logicvc->chip.direction_output = logicvc_gpio_direction_output;

	platक्रमm_set_drvdata(pdev, logicvc);

	वापस devm_gpiochip_add_data(dev, &logicvc->chip, logicvc);
पूर्ण

अटल स्थिर काष्ठा of_device_id logicivc_gpio_of_table[] = अणु
	अणु
		.compatible	= "xylon,logicvc-3.02.a-gpio",
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, logicivc_gpio_of_table);

अटल काष्ठा platक्रमm_driver logicvc_gpio_driver = अणु
	.driver	= अणु
		.name		= "gpio-logicvc",
		.of_match_table	= logicivc_gpio_of_table,
	पूर्ण,
	.probe	= logicvc_gpio_probe,
पूर्ण;

module_platक्रमm_driver(logicvc_gpio_driver);

MODULE_AUTHOR("Paul Kocialkowski <paul.kocialkowski@bootlin.com>");
MODULE_DESCRIPTION("Xylon LogiCVC GPIO driver");
MODULE_LICENSE("GPL");
