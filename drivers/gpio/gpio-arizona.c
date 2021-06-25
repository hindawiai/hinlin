<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * gpiolib support क्रम Wolfson Arizona class devices
 *
 * Copyright 2012 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/seq_file.h>

#समावेश <linux/mfd/arizona/core.h>
#समावेश <linux/mfd/arizona/pdata.h>
#समावेश <linux/mfd/arizona/रेजिस्टरs.h>

काष्ठा arizona_gpio अणु
	काष्ठा arizona *arizona;
	काष्ठा gpio_chip gpio_chip;
पूर्ण;

अटल पूर्णांक arizona_gpio_direction_in(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा arizona_gpio *arizona_gpio = gpiochip_get_data(chip);
	काष्ठा arizona *arizona = arizona_gpio->arizona;
	bool persistent = gpiochip_line_is_persistent(chip, offset);
	bool change;
	पूर्णांक ret;

	ret = regmap_update_bits_check(arizona->regmap,
				       ARIZONA_GPIO1_CTRL + offset,
				       ARIZONA_GPN_सूची, ARIZONA_GPN_सूची,
				       &change);
	अगर (ret < 0)
		वापस ret;

	अगर (change && persistent) अणु
		pm_runसमय_mark_last_busy(chip->parent);
		pm_runसमय_put_स्वतःsuspend(chip->parent);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक arizona_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा arizona_gpio *arizona_gpio = gpiochip_get_data(chip);
	काष्ठा arizona *arizona = arizona_gpio->arizona;
	अचिन्हित पूर्णांक reg, val;
	पूर्णांक ret;

	reg = ARIZONA_GPIO1_CTRL + offset;
	ret = regmap_पढ़ो(arizona->regmap, reg, &val);
	अगर (ret < 0)
		वापस ret;

	/* Resume to पढ़ो actual रेजिस्टरs क्रम input pins */
	अगर (val & ARIZONA_GPN_सूची) अणु
		ret = pm_runसमय_get_sync(chip->parent);
		अगर (ret < 0) अणु
			dev_err(chip->parent, "Failed to resume: %d\n", ret);
			pm_runसमय_put_स्वतःsuspend(chip->parent);
			वापस ret;
		पूर्ण

		/* Register is cached, drop it to ensure a physical पढ़ो */
		ret = regcache_drop_region(arizona->regmap, reg, reg);
		अगर (ret < 0) अणु
			dev_err(chip->parent, "Failed to drop cache: %d\n",
				ret);
			pm_runसमय_put_स्वतःsuspend(chip->parent);
			वापस ret;
		पूर्ण

		ret = regmap_पढ़ो(arizona->regmap, reg, &val);
		अगर (ret < 0) अणु
			pm_runसमय_put_स्वतःsuspend(chip->parent);
			वापस ret;
		पूर्ण

		pm_runसमय_mark_last_busy(chip->parent);
		pm_runसमय_put_स्वतःsuspend(chip->parent);
	पूर्ण

	अगर (val & ARIZONA_GPN_LVL)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक arizona_gpio_direction_out(काष्ठा gpio_chip *chip,
				     अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा arizona_gpio *arizona_gpio = gpiochip_get_data(chip);
	काष्ठा arizona *arizona = arizona_gpio->arizona;
	bool persistent = gpiochip_line_is_persistent(chip, offset);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(arizona->regmap, ARIZONA_GPIO1_CTRL + offset, &val);
	अगर (ret < 0)
		वापस ret;

	अगर ((val & ARIZONA_GPN_सूची) && persistent) अणु
		ret = pm_runसमय_get_sync(chip->parent);
		अगर (ret < 0) अणु
			dev_err(chip->parent, "Failed to resume: %d\n", ret);
			pm_runसमय_put(chip->parent);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (value)
		value = ARIZONA_GPN_LVL;

	वापस regmap_update_bits(arizona->regmap, ARIZONA_GPIO1_CTRL + offset,
				  ARIZONA_GPN_सूची | ARIZONA_GPN_LVL, value);
पूर्ण

अटल व्योम arizona_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा arizona_gpio *arizona_gpio = gpiochip_get_data(chip);
	काष्ठा arizona *arizona = arizona_gpio->arizona;

	अगर (value)
		value = ARIZONA_GPN_LVL;

	regmap_update_bits(arizona->regmap, ARIZONA_GPIO1_CTRL + offset,
			   ARIZONA_GPN_LVL, value);
पूर्ण

अटल स्थिर काष्ठा gpio_chip ढाँचा_chip = अणु
	.label			= "arizona",
	.owner			= THIS_MODULE,
	.direction_input	= arizona_gpio_direction_in,
	.get			= arizona_gpio_get,
	.direction_output	= arizona_gpio_direction_out,
	.set			= arizona_gpio_set,
	.can_sleep		= true,
पूर्ण;

अटल पूर्णांक arizona_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arizona *arizona = dev_get_drvdata(pdev->dev.parent);
	काष्ठा arizona_pdata *pdata = &arizona->pdata;
	काष्ठा arizona_gpio *arizona_gpio;
	पूर्णांक ret;

	arizona_gpio = devm_kzalloc(&pdev->dev, माप(*arizona_gpio),
				    GFP_KERNEL);
	अगर (!arizona_gpio)
		वापस -ENOMEM;

	arizona_gpio->arizona = arizona;
	arizona_gpio->gpio_chip = ढाँचा_chip;
	arizona_gpio->gpio_chip.parent = &pdev->dev;
#अगर_घोषित CONFIG_OF_GPIO
	arizona_gpio->gpio_chip.of_node = arizona->dev->of_node;
#पूर्ण_अगर

	चयन (arizona->type) अणु
	हाल WM5102:
	हाल WM5110:
	हाल WM8280:
	हाल WM8997:
	हाल WM8998:
	हाल WM1814:
		arizona_gpio->gpio_chip.ngpio = 5;
		अवरोध;
	हाल WM1831:
	हाल CS47L24:
		arizona_gpio->gpio_chip.ngpio = 2;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unknown chip variant %d\n",
			arizona->type);
		वापस -EINVAL;
	पूर्ण

	अगर (pdata->gpio_base)
		arizona_gpio->gpio_chip.base = pdata->gpio_base;
	अन्यथा
		arizona_gpio->gpio_chip.base = -1;

	pm_runसमय_enable(&pdev->dev);

	ret = devm_gpiochip_add_data(&pdev->dev, &arizona_gpio->gpio_chip,
				     arizona_gpio);
	अगर (ret < 0) अणु
		pm_runसमय_disable(&pdev->dev);
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver arizona_gpio_driver = अणु
	.driver.name	= "arizona-gpio",
	.probe		= arizona_gpio_probe,
पूर्ण;

module_platक्रमm_driver(arizona_gpio_driver);

MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("GPIO interface for Arizona devices");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:arizona-gpio");
