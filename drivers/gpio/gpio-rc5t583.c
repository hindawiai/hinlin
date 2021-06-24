<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GPIO driver क्रम RICOH583 घातer management chip.
 *
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 * Author: Laxman dewangan <ldewangan@nvidia.com>
 *
 * Based on code
 *	Copyright (C) 2011 RICOH COMPANY,LTD
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/mfd/rc5t583.h>

काष्ठा rc5t583_gpio अणु
	काष्ठा gpio_chip gpio_chip;
	काष्ठा rc5t583 *rc5t583;
पूर्ण;

अटल पूर्णांक rc5t583_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा rc5t583_gpio *rc5t583_gpio = gpiochip_get_data(gc);
	काष्ठा device *parent = rc5t583_gpio->rc5t583->dev;
	uपूर्णांक8_t val = 0;
	पूर्णांक ret;

	ret = rc5t583_पढ़ो(parent, RC5T583_GPIO_MON_IOIN, &val);
	अगर (ret < 0)
		वापस ret;

	वापस !!(val & BIT(offset));
पूर्ण

अटल व्योम rc5t583_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा rc5t583_gpio *rc5t583_gpio = gpiochip_get_data(gc);
	काष्ठा device *parent = rc5t583_gpio->rc5t583->dev;
	अगर (val)
		rc5t583_set_bits(parent, RC5T583_GPIO_IOOUT, BIT(offset));
	अन्यथा
		rc5t583_clear_bits(parent, RC5T583_GPIO_IOOUT, BIT(offset));
पूर्ण

अटल पूर्णांक rc5t583_gpio_dir_input(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा rc5t583_gpio *rc5t583_gpio = gpiochip_get_data(gc);
	काष्ठा device *parent = rc5t583_gpio->rc5t583->dev;
	पूर्णांक ret;

	ret = rc5t583_clear_bits(parent, RC5T583_GPIO_IOSEL, BIT(offset));
	अगर (ret < 0)
		वापस ret;

	/* Set pin to gpio mode */
	वापस rc5t583_clear_bits(parent, RC5T583_GPIO_PGSEL, BIT(offset));
पूर्ण

अटल पूर्णांक rc5t583_gpio_dir_output(काष्ठा gpio_chip *gc, अचिन्हित offset,
			पूर्णांक value)
अणु
	काष्ठा rc5t583_gpio *rc5t583_gpio = gpiochip_get_data(gc);
	काष्ठा device *parent = rc5t583_gpio->rc5t583->dev;
	पूर्णांक ret;

	rc5t583_gpio_set(gc, offset, value);
	ret = rc5t583_set_bits(parent, RC5T583_GPIO_IOSEL, BIT(offset));
	अगर (ret < 0)
		वापस ret;

	/* Set pin to gpio mode */
	वापस rc5t583_clear_bits(parent, RC5T583_GPIO_PGSEL, BIT(offset));
पूर्ण

अटल पूर्णांक rc5t583_gpio_to_irq(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा rc5t583_gpio *rc5t583_gpio = gpiochip_get_data(gc);

	अगर (offset < RC5T583_MAX_GPIO)
		वापस rc5t583_gpio->rc5t583->irq_base +
				RC5T583_IRQ_GPIO0 + offset;
	वापस -EINVAL;
पूर्ण

अटल व्योम rc5t583_gpio_मुक्त(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा rc5t583_gpio *rc5t583_gpio = gpiochip_get_data(gc);
	काष्ठा device *parent = rc5t583_gpio->rc5t583->dev;

	rc5t583_set_bits(parent, RC5T583_GPIO_PGSEL, BIT(offset));
पूर्ण

अटल पूर्णांक rc5t583_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rc5t583 *rc5t583 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा rc5t583_platक्रमm_data *pdata = dev_get_platdata(rc5t583->dev);
	काष्ठा rc5t583_gpio *rc5t583_gpio;

	rc5t583_gpio = devm_kzalloc(&pdev->dev, माप(*rc5t583_gpio),
					GFP_KERNEL);
	अगर (!rc5t583_gpio)
		वापस -ENOMEM;

	rc5t583_gpio->gpio_chip.label = "gpio-rc5t583",
	rc5t583_gpio->gpio_chip.owner = THIS_MODULE,
	rc5t583_gpio->gpio_chip.मुक्त = rc5t583_gpio_मुक्त,
	rc5t583_gpio->gpio_chip.direction_input = rc5t583_gpio_dir_input,
	rc5t583_gpio->gpio_chip.direction_output = rc5t583_gpio_dir_output,
	rc5t583_gpio->gpio_chip.set = rc5t583_gpio_set,
	rc5t583_gpio->gpio_chip.get = rc5t583_gpio_get,
	rc5t583_gpio->gpio_chip.to_irq = rc5t583_gpio_to_irq,
	rc5t583_gpio->gpio_chip.ngpio = RC5T583_MAX_GPIO,
	rc5t583_gpio->gpio_chip.can_sleep = true,
	rc5t583_gpio->gpio_chip.parent = &pdev->dev;
	rc5t583_gpio->gpio_chip.base = -1;
	rc5t583_gpio->rc5t583 = rc5t583;

	अगर (pdata && pdata->gpio_base)
		rc5t583_gpio->gpio_chip.base = pdata->gpio_base;

	platक्रमm_set_drvdata(pdev, rc5t583_gpio);

	वापस devm_gpiochip_add_data(&pdev->dev, &rc5t583_gpio->gpio_chip,
				      rc5t583_gpio);
पूर्ण

अटल काष्ठा platक्रमm_driver rc5t583_gpio_driver = अणु
	.driver = अणु
		.name    = "rc5t583-gpio",
	पूर्ण,
	.probe		= rc5t583_gpio_probe,
पूर्ण;

अटल पूर्णांक __init rc5t583_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&rc5t583_gpio_driver);
पूर्ण
subsys_initcall(rc5t583_gpio_init);
