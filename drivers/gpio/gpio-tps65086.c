<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 *	Andrew F. Davis <afd@ti.com>
 *
 * Based on the TPS65912 driver
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/mfd/tps65086.h>

काष्ठा tps65086_gpio अणु
	काष्ठा gpio_chip chip;
	काष्ठा tps65086 *tps;
पूर्ण;

अटल पूर्णांक tps65086_gpio_get_direction(काष्ठा gpio_chip *chip,
				       अचिन्हित offset)
अणु
	/* This device is output only */
	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक tps65086_gpio_direction_input(काष्ठा gpio_chip *chip,
					 अचिन्हित offset)
अणु
	/* This device is output only */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tps65086_gpio_direction_output(काष्ठा gpio_chip *chip,
					  अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा tps65086_gpio *gpio = gpiochip_get_data(chip);

	/* Set the initial value */
	regmap_update_bits(gpio->tps->regmap, TPS65086_GPOCTRL,
			   BIT(4 + offset), value ? BIT(4 + offset) : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक tps65086_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा tps65086_gpio *gpio = gpiochip_get_data(chip);
	पूर्णांक ret, val;

	ret = regmap_पढ़ो(gpio->tps->regmap, TPS65086_GPOCTRL, &val);
	अगर (ret < 0)
		वापस ret;

	वापस val & BIT(4 + offset);
पूर्ण

अटल व्योम tps65086_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset,
			      पूर्णांक value)
अणु
	काष्ठा tps65086_gpio *gpio = gpiochip_get_data(chip);

	regmap_update_bits(gpio->tps->regmap, TPS65086_GPOCTRL,
			   BIT(4 + offset), value ? BIT(4 + offset) : 0);
पूर्ण

अटल स्थिर काष्ठा gpio_chip ढाँचा_chip = अणु
	.label			= "tps65086-gpio",
	.owner			= THIS_MODULE,
	.get_direction		= tps65086_gpio_get_direction,
	.direction_input	= tps65086_gpio_direction_input,
	.direction_output	= tps65086_gpio_direction_output,
	.get			= tps65086_gpio_get,
	.set			= tps65086_gpio_set,
	.base			= -1,
	.ngpio			= 4,
	.can_sleep		= true,
पूर्ण;

अटल पूर्णांक tps65086_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps65086_gpio *gpio;
	पूर्णांक ret;

	gpio = devm_kzalloc(&pdev->dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, gpio);

	gpio->tps = dev_get_drvdata(pdev->dev.parent);
	gpio->chip = ढाँचा_chip;
	gpio->chip.parent = gpio->tps->dev;

	ret = gpiochip_add_data(&gpio->chip, gpio);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tps65086_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps65086_gpio *gpio = platक्रमm_get_drvdata(pdev);

	gpiochip_हटाओ(&gpio->chip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id tps65086_gpio_id_table[] = अणु
	अणु "tps65086-gpio", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, tps65086_gpio_id_table);

अटल काष्ठा platक्रमm_driver tps65086_gpio_driver = अणु
	.driver = अणु
		.name = "tps65086-gpio",
	पूर्ण,
	.probe = tps65086_gpio_probe,
	.हटाओ = tps65086_gpio_हटाओ,
	.id_table = tps65086_gpio_id_table,
पूर्ण;
module_platक्रमm_driver(tps65086_gpio_driver);

MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_DESCRIPTION("TPS65086 GPIO driver");
MODULE_LICENSE("GPL v2");
