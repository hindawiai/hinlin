<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * GPIO driver क्रम Analog Devices ADP5520 MFD PMICs
 *
 * Copyright 2009 Analog Devices Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/adp5520.h>
#समावेश <linux/gpio/driver.h>

काष्ठा adp5520_gpio अणु
	काष्ठा device *master;
	काष्ठा gpio_chip gpio_chip;
	अचिन्हित अक्षर lut[ADP5520_MAXGPIOS];
	अचिन्हित दीर्घ output;
पूर्ण;

अटल पूर्णांक adp5520_gpio_get_value(काष्ठा gpio_chip *chip, अचिन्हित off)
अणु
	काष्ठा adp5520_gpio *dev;
	uपूर्णांक8_t reg_val;

	dev = gpiochip_get_data(chip);

	/*
	 * There are dedicated रेजिस्टरs क्रम GPIO IN/OUT.
	 * Make sure we वापस the right value, even when configured as output
	 */

	अगर (test_bit(off, &dev->output))
		adp5520_पढ़ो(dev->master, ADP5520_GPIO_OUT, &reg_val);
	अन्यथा
		adp5520_पढ़ो(dev->master, ADP5520_GPIO_IN, &reg_val);

	वापस !!(reg_val & dev->lut[off]);
पूर्ण

अटल व्योम adp5520_gpio_set_value(काष्ठा gpio_chip *chip,
		अचिन्हित off, पूर्णांक val)
अणु
	काष्ठा adp5520_gpio *dev;
	dev = gpiochip_get_data(chip);

	अगर (val)
		adp5520_set_bits(dev->master, ADP5520_GPIO_OUT, dev->lut[off]);
	अन्यथा
		adp5520_clr_bits(dev->master, ADP5520_GPIO_OUT, dev->lut[off]);
पूर्ण

अटल पूर्णांक adp5520_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित off)
अणु
	काष्ठा adp5520_gpio *dev;
	dev = gpiochip_get_data(chip);

	clear_bit(off, &dev->output);

	वापस adp5520_clr_bits(dev->master, ADP5520_GPIO_CFG_2,
				dev->lut[off]);
पूर्ण

अटल पूर्णांक adp5520_gpio_direction_output(काष्ठा gpio_chip *chip,
		अचिन्हित off, पूर्णांक val)
अणु
	काष्ठा adp5520_gpio *dev;
	पूर्णांक ret = 0;
	dev = gpiochip_get_data(chip);

	set_bit(off, &dev->output);

	अगर (val)
		ret |= adp5520_set_bits(dev->master, ADP5520_GPIO_OUT,
					dev->lut[off]);
	अन्यथा
		ret |= adp5520_clr_bits(dev->master, ADP5520_GPIO_OUT,
					dev->lut[off]);

	ret |= adp5520_set_bits(dev->master, ADP5520_GPIO_CFG_2,
					dev->lut[off]);

	वापस ret;
पूर्ण

अटल पूर्णांक adp5520_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा adp5520_gpio_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा adp5520_gpio *dev;
	काष्ठा gpio_chip *gc;
	पूर्णांक ret, i, gpios;
	अचिन्हित अक्षर ctl_mask = 0;

	अगर (pdata == शून्य) अणु
		dev_err(&pdev->dev, "missing platform data\n");
		वापस -ENODEV;
	पूर्ण

	अगर (pdev->id != ID_ADP5520) अणु
		dev_err(&pdev->dev, "only ADP5520 supports GPIO\n");
		वापस -ENODEV;
	पूर्ण

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (dev == शून्य)
		वापस -ENOMEM;

	dev->master = pdev->dev.parent;

	क्रम (gpios = 0, i = 0; i < ADP5520_MAXGPIOS; i++)
		अगर (pdata->gpio_en_mask & (1 << i))
			dev->lut[gpios++] = 1 << i;

	अगर (gpios < 1) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	gc = &dev->gpio_chip;
	gc->direction_input  = adp5520_gpio_direction_input;
	gc->direction_output = adp5520_gpio_direction_output;
	gc->get = adp5520_gpio_get_value;
	gc->set = adp5520_gpio_set_value;
	gc->can_sleep = true;

	gc->base = pdata->gpio_start;
	gc->ngpio = gpios;
	gc->label = pdev->name;
	gc->owner = THIS_MODULE;

	ret = adp5520_clr_bits(dev->master, ADP5520_GPIO_CFG_1,
		pdata->gpio_en_mask);

	अगर (pdata->gpio_en_mask & ADP5520_GPIO_C3)
		ctl_mask |= ADP5520_C3_MODE;

	अगर (pdata->gpio_en_mask & ADP5520_GPIO_R3)
		ctl_mask |= ADP5520_R3_MODE;

	अगर (ctl_mask)
		ret = adp5520_set_bits(dev->master, ADP5520_LED_CONTROL,
			ctl_mask);

	ret |= adp5520_set_bits(dev->master, ADP5520_GPIO_PULLUP,
		pdata->gpio_pullup_mask);

	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to write\n");
		जाओ err;
	पूर्ण

	ret = devm_gpiochip_add_data(&pdev->dev, &dev->gpio_chip, dev);
	अगर (ret)
		जाओ err;

	platक्रमm_set_drvdata(pdev, dev);
	वापस 0;

err:
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver adp5520_gpio_driver = अणु
	.driver	= अणु
		.name	= "adp5520-gpio",
	पूर्ण,
	.probe		= adp5520_gpio_probe,
पूर्ण;

module_platक्रमm_driver(adp5520_gpio_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("GPIO ADP5520 Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:adp5520-gpio");
