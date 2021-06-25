<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * gpiolib support क्रम Wolfson WM835x PMICs
 *
 * Copyright 2009 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/seq_file.h>

#समावेश <linux/mfd/wm8350/core.h>
#समावेश <linux/mfd/wm8350/gpपन.स>

काष्ठा wm8350_gpio_data अणु
	काष्ठा wm8350 *wm8350;
	काष्ठा gpio_chip gpio_chip;
पूर्ण;

अटल पूर्णांक wm8350_gpio_direction_in(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा wm8350_gpio_data *wm8350_gpio = gpiochip_get_data(chip);
	काष्ठा wm8350 *wm8350 = wm8350_gpio->wm8350;

	वापस wm8350_set_bits(wm8350, WM8350_GPIO_CONFIGURATION_I_O,
			       1 << offset);
पूर्ण

अटल पूर्णांक wm8350_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा wm8350_gpio_data *wm8350_gpio = gpiochip_get_data(chip);
	काष्ठा wm8350 *wm8350 = wm8350_gpio->wm8350;
	पूर्णांक ret;

	ret = wm8350_reg_पढ़ो(wm8350, WM8350_GPIO_LEVEL);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & (1 << offset))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम wm8350_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा wm8350_gpio_data *wm8350_gpio = gpiochip_get_data(chip);
	काष्ठा wm8350 *wm8350 = wm8350_gpio->wm8350;

	अगर (value)
		wm8350_set_bits(wm8350, WM8350_GPIO_LEVEL, 1 << offset);
	अन्यथा
		wm8350_clear_bits(wm8350, WM8350_GPIO_LEVEL, 1 << offset);
पूर्ण

अटल पूर्णांक wm8350_gpio_direction_out(काष्ठा gpio_chip *chip,
				     अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा wm8350_gpio_data *wm8350_gpio = gpiochip_get_data(chip);
	काष्ठा wm8350 *wm8350 = wm8350_gpio->wm8350;
	पूर्णांक ret;

	ret = wm8350_clear_bits(wm8350, WM8350_GPIO_CONFIGURATION_I_O,
				1 << offset);
	अगर (ret < 0)
		वापस ret;

	/* Don't have an atomic direction/value setup */
	wm8350_gpio_set(chip, offset, value);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा wm8350_gpio_data *wm8350_gpio = gpiochip_get_data(chip);
	काष्ठा wm8350 *wm8350 = wm8350_gpio->wm8350;

	अगर (!wm8350->irq_base)
		वापस -EINVAL;

	वापस wm8350->irq_base + WM8350_IRQ_GPIO(offset);
पूर्ण

अटल स्थिर काष्ठा gpio_chip ढाँचा_chip = अणु
	.label			= "wm8350",
	.owner			= THIS_MODULE,
	.direction_input	= wm8350_gpio_direction_in,
	.get			= wm8350_gpio_get,
	.direction_output	= wm8350_gpio_direction_out,
	.set			= wm8350_gpio_set,
	.to_irq			= wm8350_gpio_to_irq,
	.can_sleep		= true,
पूर्ण;

अटल पूर्णांक wm8350_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm8350 *wm8350 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm8350_platक्रमm_data *pdata = dev_get_platdata(wm8350->dev);
	काष्ठा wm8350_gpio_data *wm8350_gpio;
	पूर्णांक ret;

	wm8350_gpio = devm_kzalloc(&pdev->dev, माप(*wm8350_gpio),
				   GFP_KERNEL);
	अगर (wm8350_gpio == शून्य)
		वापस -ENOMEM;

	wm8350_gpio->wm8350 = wm8350;
	wm8350_gpio->gpio_chip = ढाँचा_chip;
	wm8350_gpio->gpio_chip.ngpio = 13;
	wm8350_gpio->gpio_chip.parent = &pdev->dev;
	अगर (pdata && pdata->gpio_base)
		wm8350_gpio->gpio_chip.base = pdata->gpio_base;
	अन्यथा
		wm8350_gpio->gpio_chip.base = -1;

	ret = devm_gpiochip_add_data(&pdev->dev, &wm8350_gpio->gpio_chip,
				     wm8350_gpio);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, wm8350_gpio);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver wm8350_gpio_driver = अणु
	.driver.name	= "wm8350-gpio",
	.probe		= wm8350_gpio_probe,
पूर्ण;

अटल पूर्णांक __init wm8350_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&wm8350_gpio_driver);
पूर्ण
subsys_initcall(wm8350_gpio_init);

अटल व्योम __निकास wm8350_gpio_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&wm8350_gpio_driver);
पूर्ण
module_निकास(wm8350_gpio_निकास);

MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("GPIO interface for WM8350 PMICs");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm8350-gpio");
