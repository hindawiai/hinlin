<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (C) 2018 ROHM Semiconductors

#समावेश <linux/gpio/driver.h>
#समावेश <linux/mfd/rohm-bd71828.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा GPIO_OUT_REG(off) (BD71828_REG_GPIO_CTRL1 + (off))
#घोषणा HALL_GPIO_OFFSET 3

काष्ठा bd71828_gpio अणु
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	काष्ठा gpio_chip gpio;
पूर्ण;

अटल व्योम bd71828_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			     पूर्णांक value)
अणु
	पूर्णांक ret;
	काष्ठा bd71828_gpio *bdgpio = gpiochip_get_data(chip);
	u8 val = (value) ? BD71828_GPIO_OUT_HI : BD71828_GPIO_OUT_LO;

	/*
	 * The HALL input pin can only be used as input. If this is the pin
	 * we are dealing with - then we are करोne
	 */
	अगर (offset == HALL_GPIO_OFFSET)
		वापस;

	ret = regmap_update_bits(bdgpio->regmap, GPIO_OUT_REG(offset),
				 BD71828_GPIO_OUT_MASK, val);
	अगर (ret)
		dev_err(bdgpio->dev, "Could not set gpio to %d\n", value);
पूर्ण

अटल पूर्णांक bd71828_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;
	काष्ठा bd71828_gpio *bdgpio = gpiochip_get_data(chip);

	अगर (offset == HALL_GPIO_OFFSET)
		ret = regmap_पढ़ो(bdgpio->regmap, BD71828_REG_IO_STAT,
				  &val);
	अन्यथा
		ret = regmap_पढ़ो(bdgpio->regmap, GPIO_OUT_REG(offset),
				  &val);
	अगर (!ret)
		ret = (val & BD71828_GPIO_OUT_MASK);

	वापस ret;
पूर्ण

अटल पूर्णांक bd71828_gpio_set_config(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				   अचिन्हित दीर्घ config)
अणु
	काष्ठा bd71828_gpio *bdgpio = gpiochip_get_data(chip);

	अगर (offset == HALL_GPIO_OFFSET)
		वापस -ENOTSUPP;

	चयन (pinconf_to_config_param(config)) अणु
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		वापस regmap_update_bits(bdgpio->regmap,
					  GPIO_OUT_REG(offset),
					  BD71828_GPIO_DRIVE_MASK,
					  BD71828_GPIO_OPEN_DRAIN);
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		वापस regmap_update_bits(bdgpio->regmap,
					  GPIO_OUT_REG(offset),
					  BD71828_GPIO_DRIVE_MASK,
					  BD71828_GPIO_PUSH_PULL);
	शेष:
		अवरोध;
	पूर्ण
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक bd71828_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	/*
	 * Pin usage is selected by OTP data. We can't पढ़ो it runसमय. Hence
	 * we trust that अगर the pin is not excluded by "gpio-reserved-ranges"
	 * the OTP configuration is set to OUT. (Other pins but HALL input pin
	 * on BD71828 can't really be used क्रम general purpose input - input
	 * states are used क्रम specअगरic हालs like regulator control or
	 * PMIC_ON_REQ.
	 */
	अगर (offset == HALL_GPIO_OFFSET)
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक bd71828_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bd71828_gpio *bdgpio;

	bdgpio = devm_kzalloc(dev, माप(*bdgpio), GFP_KERNEL);
	अगर (!bdgpio)
		वापस -ENOMEM;

	bdgpio->dev = dev;
	bdgpio->gpio.parent = dev->parent;
	bdgpio->gpio.label = "bd71828-gpio";
	bdgpio->gpio.owner = THIS_MODULE;
	bdgpio->gpio.get_direction = bd71828_get_direction;
	bdgpio->gpio.set_config = bd71828_gpio_set_config;
	bdgpio->gpio.can_sleep = true;
	bdgpio->gpio.get = bd71828_gpio_get;
	bdgpio->gpio.set = bd71828_gpio_set;
	bdgpio->gpio.base = -1;

	/*
	 * See अगर we need some implementation to mark some PINs as
	 * not controllable based on DT info or अगर core can handle
	 * "gpio-reserved-ranges" and exclude them from control
	 */
	bdgpio->gpio.ngpio = 4;
	bdgpio->gpio.of_node = dev->parent->of_node;
	bdgpio->regmap = dev_get_regmap(dev->parent, शून्य);
	अगर (!bdgpio->regmap)
		वापस -ENODEV;

	वापस devm_gpiochip_add_data(dev, &bdgpio->gpio, bdgpio);
पूर्ण

अटल काष्ठा platक्रमm_driver bd71828_gpio = अणु
	.driver = अणु
		.name = "bd71828-gpio"
	पूर्ण,
	.probe = bd71828_probe,
पूर्ण;

module_platक्रमm_driver(bd71828_gpio);

MODULE_AUTHOR("Matti Vaittinen <matti.vaittinen@fi.rohmeurope.com>");
MODULE_DESCRIPTION("BD71828 voltage regulator driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:bd71828-gpio");
