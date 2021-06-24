<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * GPIO driver क्रम TI TPS65912x PMICs
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 *	Andrew F. Davis <afd@ti.com>
 *
 * Based on the Arizona GPIO driver and the previous TPS65912 driver by
 * Margarita Olaya Cabrera <magi@slimlogic.co.uk>
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/mfd/tps65912.h>

काष्ठा tps65912_gpio अणु
	काष्ठा gpio_chip gpio_chip;
	काष्ठा tps65912 *tps;
पूर्ण;

अटल पूर्णांक tps65912_gpio_get_direction(काष्ठा gpio_chip *gc,
				       अचिन्हित offset)
अणु
	काष्ठा tps65912_gpio *gpio = gpiochip_get_data(gc);

	पूर्णांक ret, val;

	ret = regmap_पढ़ो(gpio->tps->regmap, TPS65912_GPIO1 + offset, &val);
	अगर (ret)
		वापस ret;

	अगर (val & GPIO_CFG_MASK)
		वापस GPIO_LINE_सूचीECTION_OUT;
	अन्यथा
		वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक tps65912_gpio_direction_input(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा tps65912_gpio *gpio = gpiochip_get_data(gc);

	वापस regmap_update_bits(gpio->tps->regmap, TPS65912_GPIO1 + offset,
				  GPIO_CFG_MASK, 0);
पूर्ण

अटल पूर्णांक tps65912_gpio_direction_output(काष्ठा gpio_chip *gc,
					  अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा tps65912_gpio *gpio = gpiochip_get_data(gc);

	/* Set the initial value */
	regmap_update_bits(gpio->tps->regmap, TPS65912_GPIO1 + offset,
			   GPIO_SET_MASK, value ? GPIO_SET_MASK : 0);

	वापस regmap_update_bits(gpio->tps->regmap, TPS65912_GPIO1 + offset,
				  GPIO_CFG_MASK, GPIO_CFG_MASK);
पूर्ण

अटल पूर्णांक tps65912_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा tps65912_gpio *gpio = gpiochip_get_data(gc);
	पूर्णांक ret, val;

	ret = regmap_पढ़ो(gpio->tps->regmap, TPS65912_GPIO1 + offset, &val);
	अगर (ret)
		वापस ret;

	अगर (val & GPIO_STS_MASK)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम tps65912_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित offset,
			      पूर्णांक value)
अणु
	काष्ठा tps65912_gpio *gpio = gpiochip_get_data(gc);

	regmap_update_bits(gpio->tps->regmap, TPS65912_GPIO1 + offset,
			   GPIO_SET_MASK, value ? GPIO_SET_MASK : 0);
पूर्ण

अटल स्थिर काष्ठा gpio_chip ढाँचा_chip = अणु
	.label			= "tps65912-gpio",
	.owner			= THIS_MODULE,
	.get_direction		= tps65912_gpio_get_direction,
	.direction_input	= tps65912_gpio_direction_input,
	.direction_output	= tps65912_gpio_direction_output,
	.get			= tps65912_gpio_get,
	.set			= tps65912_gpio_set,
	.base			= -1,
	.ngpio			= 5,
	.can_sleep		= true,
पूर्ण;

अटल पूर्णांक tps65912_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps65912 *tps = dev_get_drvdata(pdev->dev.parent);
	काष्ठा tps65912_gpio *gpio;
	पूर्णांक ret;

	gpio = devm_kzalloc(&pdev->dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	gpio->tps = dev_get_drvdata(pdev->dev.parent);
	gpio->gpio_chip = ढाँचा_chip;
	gpio->gpio_chip.parent = tps->dev;

	ret = devm_gpiochip_add_data(&pdev->dev, &gpio->gpio_chip,
				     gpio);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, gpio);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id tps65912_gpio_id_table[] = अणु
	अणु "tps65912-gpio", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, tps65912_gpio_id_table);

अटल काष्ठा platक्रमm_driver tps65912_gpio_driver = अणु
	.driver = अणु
		.name = "tps65912-gpio",
	पूर्ण,
	.probe = tps65912_gpio_probe,
	.id_table = tps65912_gpio_id_table,
पूर्ण;
module_platक्रमm_driver(tps65912_gpio_driver);

MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_DESCRIPTION("TPS65912 GPIO driver");
MODULE_LICENSE("GPL v2");
