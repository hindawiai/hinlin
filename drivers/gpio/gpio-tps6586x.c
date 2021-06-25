<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * TI TPS6586x GPIO driver
 *
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 * Author: Laxman dewangan <ldewangan@nvidia.com>
 *
 * Based on tps6586x.c
 * Copyright (c) 2010 CompuLab Ltd.
 * Mike Rapoport <mike@compulab.co.il>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/tps6586x.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

/* GPIO control रेजिस्टरs */
#घोषणा TPS6586X_GPIOSET1	0x5d
#घोषणा TPS6586X_GPIOSET2	0x5e

काष्ठा tps6586x_gpio अणु
	काष्ठा gpio_chip gpio_chip;
	काष्ठा device *parent;
पूर्ण;

अटल पूर्णांक tps6586x_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा tps6586x_gpio *tps6586x_gpio = gpiochip_get_data(gc);
	uपूर्णांक8_t val;
	पूर्णांक ret;

	ret = tps6586x_पढ़ो(tps6586x_gpio->parent, TPS6586X_GPIOSET2, &val);
	अगर (ret)
		वापस ret;

	वापस !!(val & (1 << offset));
पूर्ण

अटल व्योम tps6586x_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित offset,
			      पूर्णांक value)
अणु
	काष्ठा tps6586x_gpio *tps6586x_gpio = gpiochip_get_data(gc);

	tps6586x_update(tps6586x_gpio->parent, TPS6586X_GPIOSET2,
			value << offset, 1 << offset);
पूर्ण

अटल पूर्णांक tps6586x_gpio_output(काष्ठा gpio_chip *gc, अचिन्हित offset,
				पूर्णांक value)
अणु
	काष्ठा tps6586x_gpio *tps6586x_gpio = gpiochip_get_data(gc);
	uपूर्णांक8_t val, mask;

	tps6586x_gpio_set(gc, offset, value);

	val = 0x1 << (offset * 2);
	mask = 0x3 << (offset * 2);

	वापस tps6586x_update(tps6586x_gpio->parent, TPS6586X_GPIOSET1,
				val, mask);
पूर्ण

अटल पूर्णांक tps6586x_gpio_to_irq(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा tps6586x_gpio *tps6586x_gpio = gpiochip_get_data(gc);

	वापस tps6586x_irq_get_virq(tps6586x_gpio->parent,
				TPS6586X_INT_PLDO_0 + offset);
पूर्ण

अटल पूर्णांक tps6586x_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps6586x_platक्रमm_data *pdata;
	काष्ठा tps6586x_gpio *tps6586x_gpio;
	पूर्णांक ret;

	pdata = dev_get_platdata(pdev->dev.parent);
	tps6586x_gpio = devm_kzalloc(&pdev->dev,
				माप(*tps6586x_gpio), GFP_KERNEL);
	अगर (!tps6586x_gpio)
		वापस -ENOMEM;

	tps6586x_gpio->parent = pdev->dev.parent;

	tps6586x_gpio->gpio_chip.owner = THIS_MODULE;
	tps6586x_gpio->gpio_chip.label = pdev->name;
	tps6586x_gpio->gpio_chip.parent = &pdev->dev;
	tps6586x_gpio->gpio_chip.ngpio = 4;
	tps6586x_gpio->gpio_chip.can_sleep = true;

	/* FIXME: add handling of GPIOs as dedicated inमाला_दो */
	tps6586x_gpio->gpio_chip.direction_output = tps6586x_gpio_output;
	tps6586x_gpio->gpio_chip.set	= tps6586x_gpio_set;
	tps6586x_gpio->gpio_chip.get	= tps6586x_gpio_get;
	tps6586x_gpio->gpio_chip.to_irq	= tps6586x_gpio_to_irq;

#अगर_घोषित CONFIG_OF_GPIO
	tps6586x_gpio->gpio_chip.of_node = pdev->dev.parent->of_node;
#पूर्ण_अगर
	अगर (pdata && pdata->gpio_base)
		tps6586x_gpio->gpio_chip.base = pdata->gpio_base;
	अन्यथा
		tps6586x_gpio->gpio_chip.base = -1;

	ret = devm_gpiochip_add_data(&pdev->dev, &tps6586x_gpio->gpio_chip,
				     tps6586x_gpio);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, tps6586x_gpio);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver tps6586x_gpio_driver = अणु
	.driver.name	= "tps6586x-gpio",
	.probe		= tps6586x_gpio_probe,
पूर्ण;

अटल पूर्णांक __init tps6586x_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&tps6586x_gpio_driver);
पूर्ण
subsys_initcall(tps6586x_gpio_init);
