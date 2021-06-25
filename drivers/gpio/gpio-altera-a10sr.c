<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright Intel Corporation (C) 2014-2016. All Rights Reserved
 *
 * GPIO driver क्रम  Altera Arria10 MAX5 System Resource Chip
 *
 * Adapted from gpio-tps65910.c
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/mfd/altera-a10sr.h>
#समावेश <linux/module.h>

/**
 * काष्ठा altr_a10sr_gpio - Altera Max5 GPIO device निजी data काष्ठाure
 * @gp:   : instance of the gpio_chip
 * @regmap: the regmap from the parent device.
 */
काष्ठा altr_a10sr_gpio अणु
	काष्ठा gpio_chip gp;
	काष्ठा regmap *regmap;
पूर्ण;

अटल पूर्णांक altr_a10sr_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा altr_a10sr_gpio *gpio = gpiochip_get_data(chip);
	पूर्णांक ret, val;

	ret = regmap_पढ़ो(gpio->regmap, ALTR_A10SR_PBDSW_REG, &val);
	अगर (ret < 0)
		वापस ret;

	वापस !!(val & BIT(offset - ALTR_A10SR_LED_VALID_SHIFT));
पूर्ण

अटल व्योम altr_a10sr_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				पूर्णांक value)
अणु
	काष्ठा altr_a10sr_gpio *gpio = gpiochip_get_data(chip);

	regmap_update_bits(gpio->regmap, ALTR_A10SR_LED_REG,
			   BIT(ALTR_A10SR_LED_VALID_SHIFT + offset),
			   value ? BIT(ALTR_A10SR_LED_VALID_SHIFT + offset)
			   : 0);
पूर्ण

अटल पूर्णांक altr_a10sr_gpio_direction_input(काष्ठा gpio_chip *gc,
					   अचिन्हित पूर्णांक nr)
अणु
	अगर (nr < (ALTR_A10SR_IN_VALID_RANGE_LO - ALTR_A10SR_LED_VALID_SHIFT))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक altr_a10sr_gpio_direction_output(काष्ठा gpio_chip *gc,
					    अचिन्हित पूर्णांक nr, पूर्णांक value)
अणु
	अगर (nr > (ALTR_A10SR_OUT_VALID_RANGE_HI - ALTR_A10SR_LED_VALID_SHIFT))
		वापस -EINVAL;

	altr_a10sr_gpio_set(gc, nr, value);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा gpio_chip altr_a10sr_gc = अणु
	.label = "altr_a10sr_gpio",
	.owner = THIS_MODULE,
	.get = altr_a10sr_gpio_get,
	.set = altr_a10sr_gpio_set,
	.direction_input = altr_a10sr_gpio_direction_input,
	.direction_output = altr_a10sr_gpio_direction_output,
	.can_sleep = true,
	.ngpio = 12,
	.base = -1,
पूर्ण;

अटल पूर्णांक altr_a10sr_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा altr_a10sr_gpio *gpio;
	पूर्णांक ret;
	काष्ठा altr_a10sr *a10sr = dev_get_drvdata(pdev->dev.parent);

	gpio = devm_kzalloc(&pdev->dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	gpio->regmap = a10sr->regmap;

	gpio->gp = altr_a10sr_gc;
	gpio->gp.parent = pdev->dev.parent;
	gpio->gp.of_node = pdev->dev.of_node;

	ret = devm_gpiochip_add_data(&pdev->dev, &gpio->gp, gpio);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, gpio);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id altr_a10sr_gpio_of_match[] = अणु
	अणु .compatible = "altr,a10sr-gpio" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, altr_a10sr_gpio_of_match);

अटल काष्ठा platक्रमm_driver altr_a10sr_gpio_driver = अणु
	.probe = altr_a10sr_gpio_probe,
	.driver = अणु
		.name	= "altr_a10sr_gpio",
		.of_match_table = of_match_ptr(altr_a10sr_gpio_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(altr_a10sr_gpio_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Thor Thayer <tthayer@opensource.altera.com>");
MODULE_DESCRIPTION("Altera Arria10 System Resource Chip GPIO");
