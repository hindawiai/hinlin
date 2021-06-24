<शैली गुरु>
/*
 * Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/
 *	Keerthy <j-keerthy@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether expressed or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 क्रम more details.
 *
 * Based on the LP873X driver
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <linux/mfd/lp87565.h>

काष्ठा lp87565_gpio अणु
	काष्ठा gpio_chip chip;
	काष्ठा regmap *map;
पूर्ण;

अटल पूर्णांक lp87565_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा lp87565_gpio *gpio = gpiochip_get_data(chip);
	पूर्णांक ret, val;

	ret = regmap_पढ़ो(gpio->map, LP87565_REG_GPIO_IN, &val);
	अगर (ret < 0)
		वापस ret;

	वापस !!(val & BIT(offset));
पूर्ण

अटल व्योम lp87565_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			     पूर्णांक value)
अणु
	काष्ठा lp87565_gpio *gpio = gpiochip_get_data(chip);

	regmap_update_bits(gpio->map, LP87565_REG_GPIO_OUT,
			   BIT(offset), value ? BIT(offset) : 0);
पूर्ण

अटल पूर्णांक lp87565_gpio_get_direction(काष्ठा gpio_chip *chip,
				      अचिन्हित पूर्णांक offset)
अणु
	काष्ठा lp87565_gpio *gpio = gpiochip_get_data(chip);
	पूर्णांक ret, val;

	ret = regmap_पढ़ो(gpio->map, LP87565_REG_GPIO_CONFIG, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val & BIT(offset))
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक lp87565_gpio_direction_input(काष्ठा gpio_chip *chip,
					अचिन्हित पूर्णांक offset)
अणु
	काष्ठा lp87565_gpio *gpio = gpiochip_get_data(chip);

	वापस regmap_update_bits(gpio->map,
				  LP87565_REG_GPIO_CONFIG,
				  BIT(offset), 0);
पूर्ण

अटल पूर्णांक lp87565_gpio_direction_output(काष्ठा gpio_chip *chip,
					 अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा lp87565_gpio *gpio = gpiochip_get_data(chip);

	lp87565_gpio_set(chip, offset, value);

	वापस regmap_update_bits(gpio->map,
				  LP87565_REG_GPIO_CONFIG,
				  BIT(offset), BIT(offset));
पूर्ण

अटल पूर्णांक lp87565_gpio_request(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा lp87565_gpio *gpio = gpiochip_get_data(gc);
	पूर्णांक ret;

	चयन (offset) अणु
	हाल 0:
	हाल 1:
	हाल 2:
		/*
		 * MUX can program the pin to be in EN1/2/3 pin mode
		 * Or GPIO1/2/3 mode.
		 * Setup the GPIO*_SEL MUX to GPIO mode
		 */
		ret = regmap_update_bits(gpio->map,
					 LP87565_REG_PIN_FUNCTION,
					 BIT(offset), BIT(offset));
		अगर (ret)
			वापस ret;

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lp87565_gpio_set_config(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
				   अचिन्हित दीर्घ config)
अणु
	काष्ठा lp87565_gpio *gpio = gpiochip_get_data(gc);

	चयन (pinconf_to_config_param(config)) अणु
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		वापस regmap_update_bits(gpio->map,
					  LP87565_REG_GPIO_CONFIG,
					  BIT(offset +
					      __ffs(LP87565_GOIO1_OD)),
					  BIT(offset +
					      __ffs(LP87565_GOIO1_OD)));
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		वापस regmap_update_bits(gpio->map,
					  LP87565_REG_GPIO_CONFIG,
					  BIT(offset +
					      __ffs(LP87565_GOIO1_OD)), 0);
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा gpio_chip ढाँचा_chip = अणु
	.label			= "lp87565-gpio",
	.owner			= THIS_MODULE,
	.request		= lp87565_gpio_request,
	.get_direction		= lp87565_gpio_get_direction,
	.direction_input	= lp87565_gpio_direction_input,
	.direction_output	= lp87565_gpio_direction_output,
	.get			= lp87565_gpio_get,
	.set			= lp87565_gpio_set,
	.set_config		= lp87565_gpio_set_config,
	.base			= -1,
	.ngpio			= 3,
	.can_sleep		= true,
पूर्ण;

अटल पूर्णांक lp87565_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lp87565_gpio *gpio;
	काष्ठा lp87565 *lp87565;
	पूर्णांक ret;

	gpio = devm_kzalloc(&pdev->dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	lp87565 = dev_get_drvdata(pdev->dev.parent);
	gpio->chip = ढाँचा_chip;
	gpio->chip.parent = lp87565->dev;
	gpio->map = lp87565->regmap;

	ret = devm_gpiochip_add_data(&pdev->dev, &gpio->chip, gpio);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id lp87565_gpio_id_table[] = अणु
	अणु "lp87565-q1-gpio", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, lp87565_gpio_id_table);

अटल काष्ठा platक्रमm_driver lp87565_gpio_driver = अणु
	.driver = अणु
		.name = "lp87565-gpio",
	पूर्ण,
	.probe = lp87565_gpio_probe,
	.id_table = lp87565_gpio_id_table,
पूर्ण;
module_platक्रमm_driver(lp87565_gpio_driver);

MODULE_AUTHOR("Keerthy <j-keerthy@ti.com>");
MODULE_DESCRIPTION("LP87565 GPIO driver");
MODULE_LICENSE("GPL v2");
