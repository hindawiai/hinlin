<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ROHM BD9571MWV-M and BD9574MWF-M GPIO driver
 *
 * Copyright (C) 2017 Marek Vasut <marek.vasut+renesas@gmail.com>
 *
 * Based on the TPS65086 driver
 *
 * NOTE: Interrupts are not supported yet.
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/mfd/rohm-generic.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/mfd/bd9571mwv.h>

काष्ठा bd9571mwv_gpio अणु
	काष्ठा regmap *regmap;
	काष्ठा gpio_chip chip;
पूर्ण;

अटल पूर्णांक bd9571mwv_gpio_get_direction(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset)
अणु
	काष्ठा bd9571mwv_gpio *gpio = gpiochip_get_data(chip);
	पूर्णांक ret, val;

	ret = regmap_पढ़ो(gpio->regmap, BD9571MWV_GPIO_सूची, &val);
	अगर (ret < 0)
		वापस ret;
	अगर (val & BIT(offset))
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक bd9571mwv_gpio_direction_input(काष्ठा gpio_chip *chip,
					 अचिन्हित पूर्णांक offset)
अणु
	काष्ठा bd9571mwv_gpio *gpio = gpiochip_get_data(chip);

	regmap_update_bits(gpio->regmap, BD9571MWV_GPIO_सूची, BIT(offset), 0);

	वापस 0;
पूर्ण

अटल पूर्णांक bd9571mwv_gpio_direction_output(काष्ठा gpio_chip *chip,
					  अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा bd9571mwv_gpio *gpio = gpiochip_get_data(chip);

	/* Set the initial value */
	regmap_update_bits(gpio->regmap, BD9571MWV_GPIO_OUT,
			   BIT(offset), value ? BIT(offset) : 0);
	regmap_update_bits(gpio->regmap, BD9571MWV_GPIO_सूची,
			   BIT(offset), BIT(offset));

	वापस 0;
पूर्ण

अटल पूर्णांक bd9571mwv_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा bd9571mwv_gpio *gpio = gpiochip_get_data(chip);
	पूर्णांक ret, val;

	ret = regmap_पढ़ो(gpio->regmap, BD9571MWV_GPIO_IN, &val);
	अगर (ret < 0)
		वापस ret;

	वापस val & BIT(offset);
पूर्ण

अटल व्योम bd9571mwv_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			      पूर्णांक value)
अणु
	काष्ठा bd9571mwv_gpio *gpio = gpiochip_get_data(chip);

	regmap_update_bits(gpio->regmap, BD9571MWV_GPIO_OUT,
			   BIT(offset), value ? BIT(offset) : 0);
पूर्ण

अटल स्थिर काष्ठा gpio_chip ढाँचा_chip = अणु
	.label			= "bd9571mwv-gpio",
	.owner			= THIS_MODULE,
	.get_direction		= bd9571mwv_gpio_get_direction,
	.direction_input	= bd9571mwv_gpio_direction_input,
	.direction_output	= bd9571mwv_gpio_direction_output,
	.get			= bd9571mwv_gpio_get,
	.set			= bd9571mwv_gpio_set,
	.base			= -1,
	.ngpio			= 2,
	.can_sleep		= true,
पूर्ण;

अटल पूर्णांक bd9571mwv_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bd9571mwv_gpio *gpio;
	पूर्णांक ret;

	gpio = devm_kzalloc(&pdev->dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, gpio);

	gpio->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	gpio->chip = ढाँचा_chip;
	gpio->chip.parent = pdev->dev.parent;

	ret = devm_gpiochip_add_data(&pdev->dev, &gpio->chip, gpio);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id bd9571mwv_gpio_id_table[] = अणु
	अणु "bd9571mwv-gpio", ROHM_CHIP_TYPE_BD9571 पूर्ण,
	अणु "bd9574mwf-gpio", ROHM_CHIP_TYPE_BD9574 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, bd9571mwv_gpio_id_table);

अटल काष्ठा platक्रमm_driver bd9571mwv_gpio_driver = अणु
	.driver = अणु
		.name = "bd9571mwv-gpio",
	पूर्ण,
	.probe = bd9571mwv_gpio_probe,
	.id_table = bd9571mwv_gpio_id_table,
पूर्ण;
module_platक्रमm_driver(bd9571mwv_gpio_driver);

MODULE_AUTHOR("Marek Vasut <marek.vasut+renesas@gmail.com>");
MODULE_DESCRIPTION("BD9571MWV GPIO driver");
MODULE_LICENSE("GPL v2");
