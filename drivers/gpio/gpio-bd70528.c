<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 ROHM Semiconductors
// gpio-bd70528.c ROHM BD70528MWV gpio driver

#समावेश <linux/gpio/driver.h>
#समावेश <linux/mfd/rohm-bd70528.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा GPIO_IN_REG(offset) (BD70528_REG_GPIO1_IN + (offset) * 2)
#घोषणा GPIO_OUT_REG(offset) (BD70528_REG_GPIO1_OUT + (offset) * 2)

काष्ठा bd70528_gpio अणु
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	काष्ठा gpio_chip gpio;
पूर्ण;

अटल पूर्णांक bd70528_set_debounce(काष्ठा bd70528_gpio *bdgpio,
				अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक debounce)
अणु
	u8 val;

	चयन (debounce) अणु
	हाल 0:
		val = BD70528_DEBOUNCE_DISABLE;
		अवरोध;
	हाल 1 ... 15000:
		val = BD70528_DEBOUNCE_15MS;
		अवरोध;
	हाल 15001 ... 30000:
		val = BD70528_DEBOUNCE_30MS;
		अवरोध;
	हाल 30001 ... 50000:
		val = BD70528_DEBOUNCE_50MS;
		अवरोध;
	शेष:
		dev_err(bdgpio->dev,
			"Invalid debounce value %u\n", debounce);
		वापस -EINVAL;
	पूर्ण
	वापस regmap_update_bits(bdgpio->regmap, GPIO_IN_REG(offset),
				 BD70528_DEBOUNCE_MASK, val);
पूर्ण

अटल पूर्णांक bd70528_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा bd70528_gpio *bdgpio = gpiochip_get_data(chip);
	पूर्णांक val, ret;

	/* Do we need to करो something to IRQs here? */
	ret = regmap_पढ़ो(bdgpio->regmap, GPIO_OUT_REG(offset), &val);
	अगर (ret) अणु
		dev_err(bdgpio->dev, "Could not read gpio direction\n");
		वापस ret;
	पूर्ण
	अगर (val & BD70528_GPIO_OUT_EN_MASK)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक bd70528_gpio_set_config(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				   अचिन्हित दीर्घ config)
अणु
	काष्ठा bd70528_gpio *bdgpio = gpiochip_get_data(chip);

	चयन (pinconf_to_config_param(config)) अणु
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		वापस regmap_update_bits(bdgpio->regmap,
					  GPIO_OUT_REG(offset),
					  BD70528_GPIO_DRIVE_MASK,
					  BD70528_GPIO_OPEN_DRAIN);
		अवरोध;
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		वापस regmap_update_bits(bdgpio->regmap,
					  GPIO_OUT_REG(offset),
					  BD70528_GPIO_DRIVE_MASK,
					  BD70528_GPIO_PUSH_PULL);
		अवरोध;
	हाल PIN_CONFIG_INPUT_DEBOUNCE:
		वापस bd70528_set_debounce(bdgpio, offset,
					    pinconf_to_config_argument(config));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक bd70528_direction_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा bd70528_gpio *bdgpio = gpiochip_get_data(chip);

	/* Do we need to करो something to IRQs here? */
	वापस regmap_update_bits(bdgpio->regmap, GPIO_OUT_REG(offset),
				 BD70528_GPIO_OUT_EN_MASK,
				 BD70528_GPIO_OUT_DISABLE);
पूर्ण

अटल व्योम bd70528_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			     पूर्णांक value)
अणु
	पूर्णांक ret;
	काष्ठा bd70528_gpio *bdgpio = gpiochip_get_data(chip);
	u8 val = (value) ? BD70528_GPIO_OUT_HI : BD70528_GPIO_OUT_LO;

	ret = regmap_update_bits(bdgpio->regmap, GPIO_OUT_REG(offset),
				 BD70528_GPIO_OUT_MASK, val);
	अगर (ret)
		dev_err(bdgpio->dev, "Could not set gpio to %d\n", value);
पूर्ण

अटल पूर्णांक bd70528_direction_output(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				    पूर्णांक value)
अणु
	काष्ठा bd70528_gpio *bdgpio = gpiochip_get_data(chip);

	bd70528_gpio_set(chip, offset, value);
	वापस regmap_update_bits(bdgpio->regmap, GPIO_OUT_REG(offset),
				 BD70528_GPIO_OUT_EN_MASK,
				 BD70528_GPIO_OUT_ENABLE);
पूर्ण

#घोषणा GPIO_IN_STATE_MASK(offset) (BD70528_GPIO_IN_STATE_BASE << (offset))

अटल पूर्णांक bd70528_gpio_get_o(काष्ठा bd70528_gpio *bdgpio, अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(bdgpio->regmap, GPIO_OUT_REG(offset), &val);
	अगर (!ret)
		ret = !!(val & BD70528_GPIO_OUT_MASK);
	अन्यथा
		dev_err(bdgpio->dev, "GPIO (out) state read failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक bd70528_gpio_get_i(काष्ठा bd70528_gpio *bdgpio, अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bdgpio->regmap, BD70528_REG_GPIO_STATE, &val);

	अगर (!ret)
		ret = !(val & GPIO_IN_STATE_MASK(offset));
	अन्यथा
		dev_err(bdgpio->dev, "GPIO (in) state read failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक bd70528_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret;
	काष्ठा bd70528_gpio *bdgpio = gpiochip_get_data(chip);

	/*
	 * There is a race condition where someone might be changing the
	 * GPIO direction after we get it but beक्रमe we पढ़ो the value. But
	 * application design where GPIO direction may be changed just when
	 * we पढ़ो GPIO value would be poपूर्णांकless as पढ़ोer could not know
	 * whether the वापसed high/low state is caused by input or output.
	 * Or then there must be other ways to mitigate the issue. Thus
	 * locking would make no sense.
	 */
	ret = bd70528_get_direction(chip, offset);
	अगर (ret == GPIO_LINE_सूचीECTION_OUT)
		ret = bd70528_gpio_get_o(bdgpio, offset);
	अन्यथा अगर (ret == GPIO_LINE_सूचीECTION_IN)
		ret = bd70528_gpio_get_i(bdgpio, offset);
	अन्यथा
		dev_err(bdgpio->dev, "failed to read GPIO direction\n");

	वापस ret;
पूर्ण

अटल पूर्णांक bd70528_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bd70528_gpio *bdgpio;
	पूर्णांक ret;

	bdgpio = devm_kzalloc(dev, माप(*bdgpio), GFP_KERNEL);
	अगर (!bdgpio)
		वापस -ENOMEM;
	bdgpio->dev = dev;
	bdgpio->gpio.parent = dev->parent;
	bdgpio->gpio.label = "bd70528-gpio";
	bdgpio->gpio.owner = THIS_MODULE;
	bdgpio->gpio.get_direction = bd70528_get_direction;
	bdgpio->gpio.direction_input = bd70528_direction_input;
	bdgpio->gpio.direction_output = bd70528_direction_output;
	bdgpio->gpio.set_config = bd70528_gpio_set_config;
	bdgpio->gpio.can_sleep = true;
	bdgpio->gpio.get = bd70528_gpio_get;
	bdgpio->gpio.set = bd70528_gpio_set;
	bdgpio->gpio.ngpio = 4;
	bdgpio->gpio.base = -1;
#अगर_घोषित CONFIG_OF_GPIO
	bdgpio->gpio.of_node = dev->parent->of_node;
#पूर्ण_अगर
	bdgpio->regmap = dev_get_regmap(dev->parent, शून्य);
	अगर (!bdgpio->regmap)
		वापस -ENODEV;

	ret = devm_gpiochip_add_data(dev, &bdgpio->gpio, bdgpio);
	अगर (ret)
		dev_err(dev, "gpio_init: Failed to add bd70528-gpio\n");

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver bd70528_gpio = अणु
	.driver = अणु
		.name = "bd70528-gpio"
	पूर्ण,
	.probe = bd70528_probe,
पूर्ण;

module_platक्रमm_driver(bd70528_gpio);

MODULE_AUTHOR("Matti Vaittinen <matti.vaittinen@fi.rohmeurope.com>");
MODULE_DESCRIPTION("BD70528 voltage regulator driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:bd70528-gpio");
