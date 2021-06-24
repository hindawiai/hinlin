<शैली गुरु>
/*
 * Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
 * Based on the TPS65218 driver
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <linux/mfd/lp873x.h>

#घोषणा BITS_PER_GPO		0x4
#घोषणा LP873X_GPO_CTRL_OD	0x2

काष्ठा lp873x_gpio अणु
	काष्ठा gpio_chip chip;
	काष्ठा lp873x *lp873;
पूर्ण;

अटल पूर्णांक lp873x_gpio_get_direction(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक offset)
अणु
	/* This device is output only */
	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक lp873x_gpio_direction_input(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset)
अणु
	/* This device is output only */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक lp873x_gpio_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा lp873x_gpio *gpio = gpiochip_get_data(chip);

	/* Set the initial value */
	वापस regmap_update_bits(gpio->lp873->regmap, LP873X_REG_GPO_CTRL,
				  BIT(offset * BITS_PER_GPO),
				  value ? BIT(offset * BITS_PER_GPO) : 0);
पूर्ण

अटल पूर्णांक lp873x_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा lp873x_gpio *gpio = gpiochip_get_data(chip);
	पूर्णांक ret, val;

	ret = regmap_पढ़ो(gpio->lp873->regmap, LP873X_REG_GPO_CTRL, &val);
	अगर (ret < 0)
		वापस ret;

	वापस val & BIT(offset * BITS_PER_GPO);
पूर्ण

अटल व्योम lp873x_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			    पूर्णांक value)
अणु
	काष्ठा lp873x_gpio *gpio = gpiochip_get_data(chip);

	regmap_update_bits(gpio->lp873->regmap, LP873X_REG_GPO_CTRL,
			   BIT(offset * BITS_PER_GPO),
			   value ? BIT(offset * BITS_PER_GPO) : 0);
पूर्ण

अटल पूर्णांक lp873x_gpio_request(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा lp873x_gpio *gpio = gpiochip_get_data(gc);
	पूर्णांक ret;

	चयन (offset) अणु
	हाल 0:
		/* No MUX Set up Needed क्रम GPO */
		अवरोध;
	हाल 1:
		/* Setup the CLKIN_PIN_SEL MUX to GPO2 */
		ret = regmap_update_bits(gpio->lp873->regmap, LP873X_REG_CONFIG,
					 LP873X_CONFIG_CLKIN_PIN_SEL, 0);
		अगर (ret)
			वापस ret;

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lp873x_gpio_set_config(काष्ठा gpio_chip *gc, अचिन्हित offset,
				  अचिन्हित दीर्घ config)
अणु
	काष्ठा lp873x_gpio *gpio = gpiochip_get_data(gc);

	चयन (pinconf_to_config_param(config)) अणु
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		वापस regmap_update_bits(gpio->lp873->regmap,
					  LP873X_REG_GPO_CTRL,
					  BIT(offset * BITS_PER_GPO +
					  LP873X_GPO_CTRL_OD),
					  BIT(offset * BITS_PER_GPO +
					  LP873X_GPO_CTRL_OD));

	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		वापस regmap_update_bits(gpio->lp873->regmap,
					  LP873X_REG_GPO_CTRL,
					  BIT(offset * BITS_PER_GPO +
					  LP873X_GPO_CTRL_OD), 0);
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा gpio_chip ढाँचा_chip = अणु
	.label			= "lp873x-gpio",
	.owner			= THIS_MODULE,
	.request		= lp873x_gpio_request,
	.get_direction		= lp873x_gpio_get_direction,
	.direction_input	= lp873x_gpio_direction_input,
	.direction_output	= lp873x_gpio_direction_output,
	.get			= lp873x_gpio_get,
	.set			= lp873x_gpio_set,
	.set_config		= lp873x_gpio_set_config,
	.base			= -1,
	.ngpio			= 2,
	.can_sleep		= true,
पूर्ण;

अटल पूर्णांक lp873x_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lp873x_gpio *gpio;
	पूर्णांक ret;

	gpio = devm_kzalloc(&pdev->dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, gpio);

	gpio->lp873 = dev_get_drvdata(pdev->dev.parent);
	gpio->chip = ढाँचा_chip;
	gpio->chip.parent = gpio->lp873->dev;

	ret = devm_gpiochip_add_data(&pdev->dev, &gpio->chip, gpio);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id lp873x_gpio_id_table[] = अणु
	अणु "lp873x-gpio", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, lp873x_gpio_id_table);

अटल काष्ठा platक्रमm_driver lp873x_gpio_driver = अणु
	.driver = अणु
		.name = "lp873x-gpio",
	पूर्ण,
	.probe = lp873x_gpio_probe,
	.id_table = lp873x_gpio_id_table,
पूर्ण;
module_platक्रमm_driver(lp873x_gpio_driver);

MODULE_AUTHOR("Keerthy <j-keerthy@ti.com>");
MODULE_DESCRIPTION("LP873X GPIO driver");
MODULE_LICENSE("GPL v2");
