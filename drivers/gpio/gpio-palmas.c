<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI Palma series PMIC's GPIO driver.
 *
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/palmas.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

काष्ठा palmas_gpio अणु
	काष्ठा gpio_chip gpio_chip;
	काष्ठा palmas *palmas;
पूर्ण;

काष्ठा palmas_device_data अणु
	पूर्णांक ngpio;
पूर्ण;

अटल पूर्णांक palmas_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा palmas_gpio *pg = gpiochip_get_data(gc);
	काष्ठा palmas *palmas = pg->palmas;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg;
	पूर्णांक gpio16 = (offset/8);

	offset %= 8;
	reg = (gpio16) ? PALMAS_GPIO_DATA_सूची2 : PALMAS_GPIO_DATA_सूची;

	ret = palmas_पढ़ो(palmas, PALMAS_GPIO_BASE, reg, &val);
	अगर (ret < 0) अणु
		dev_err(gc->parent, "Reg 0x%02x read failed, %d\n", reg, ret);
		वापस ret;
	पूर्ण

	अगर (val & BIT(offset))
		reg = (gpio16) ? PALMAS_GPIO_DATA_OUT2 : PALMAS_GPIO_DATA_OUT;
	अन्यथा
		reg = (gpio16) ? PALMAS_GPIO_DATA_IN2 : PALMAS_GPIO_DATA_IN;

	ret = palmas_पढ़ो(palmas, PALMAS_GPIO_BASE, reg, &val);
	अगर (ret < 0) अणु
		dev_err(gc->parent, "Reg 0x%02x read failed, %d\n", reg, ret);
		वापस ret;
	पूर्ण
	वापस !!(val & BIT(offset));
पूर्ण

अटल व्योम palmas_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित offset,
			पूर्णांक value)
अणु
	काष्ठा palmas_gpio *pg = gpiochip_get_data(gc);
	काष्ठा palmas *palmas = pg->palmas;
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg;
	पूर्णांक gpio16 = (offset/8);

	offset %= 8;
	अगर (gpio16)
		reg = (value) ?
			PALMAS_GPIO_SET_DATA_OUT2 : PALMAS_GPIO_CLEAR_DATA_OUT2;
	अन्यथा
		reg = (value) ?
			PALMAS_GPIO_SET_DATA_OUT : PALMAS_GPIO_CLEAR_DATA_OUT;

	ret = palmas_ग_लिखो(palmas, PALMAS_GPIO_BASE, reg, BIT(offset));
	अगर (ret < 0)
		dev_err(gc->parent, "Reg 0x%02x write failed, %d\n", reg, ret);
पूर्ण

अटल पूर्णांक palmas_gpio_output(काष्ठा gpio_chip *gc, अचिन्हित offset,
				पूर्णांक value)
अणु
	काष्ठा palmas_gpio *pg = gpiochip_get_data(gc);
	काष्ठा palmas *palmas = pg->palmas;
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg;
	पूर्णांक gpio16 = (offset/8);

	offset %= 8;
	reg = (gpio16) ? PALMAS_GPIO_DATA_सूची2 : PALMAS_GPIO_DATA_सूची;

	/* Set the initial value */
	palmas_gpio_set(gc, offset, value);

	ret = palmas_update_bits(palmas, PALMAS_GPIO_BASE, reg,
				BIT(offset), BIT(offset));
	अगर (ret < 0)
		dev_err(gc->parent, "Reg 0x%02x update failed, %d\n", reg,
			ret);
	वापस ret;
पूर्ण

अटल पूर्णांक palmas_gpio_input(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा palmas_gpio *pg = gpiochip_get_data(gc);
	काष्ठा palmas *palmas = pg->palmas;
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg;
	पूर्णांक gpio16 = (offset/8);

	offset %= 8;
	reg = (gpio16) ? PALMAS_GPIO_DATA_सूची2 : PALMAS_GPIO_DATA_सूची;

	ret = palmas_update_bits(palmas, PALMAS_GPIO_BASE, reg, BIT(offset), 0);
	अगर (ret < 0)
		dev_err(gc->parent, "Reg 0x%02x update failed, %d\n", reg,
			ret);
	वापस ret;
पूर्ण

अटल पूर्णांक palmas_gpio_to_irq(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा palmas_gpio *pg = gpiochip_get_data(gc);
	काष्ठा palmas *palmas = pg->palmas;

	वापस palmas_irq_get_virq(palmas, PALMAS_GPIO_0_IRQ + offset);
पूर्ण

अटल स्थिर काष्ठा palmas_device_data palmas_dev_data = अणु
	.ngpio = 8,
पूर्ण;

अटल स्थिर काष्ठा palmas_device_data tps80036_dev_data = अणु
	.ngpio = 16,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_palmas_gpio_match[] = अणु
	अणु .compatible = "ti,palmas-gpio", .data = &palmas_dev_data,पूर्ण,
	अणु .compatible = "ti,tps65913-gpio", .data = &palmas_dev_data,पूर्ण,
	अणु .compatible = "ti,tps65914-gpio", .data = &palmas_dev_data,पूर्ण,
	अणु .compatible = "ti,tps80036-gpio", .data = &tps80036_dev_data,पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक palmas_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा palmas *palmas = dev_get_drvdata(pdev->dev.parent);
	काष्ठा palmas_platक्रमm_data *palmas_pdata;
	काष्ठा palmas_gpio *palmas_gpio;
	पूर्णांक ret;
	स्थिर काष्ठा palmas_device_data *dev_data;

	dev_data = of_device_get_match_data(&pdev->dev);
	अगर (!dev_data)
		dev_data = &palmas_dev_data;

	palmas_gpio = devm_kzalloc(&pdev->dev,
				माप(*palmas_gpio), GFP_KERNEL);
	अगर (!palmas_gpio)
		वापस -ENOMEM;

	palmas_gpio->palmas = palmas;
	palmas_gpio->gpio_chip.owner = THIS_MODULE;
	palmas_gpio->gpio_chip.label = dev_name(&pdev->dev);
	palmas_gpio->gpio_chip.ngpio = dev_data->ngpio;
	palmas_gpio->gpio_chip.can_sleep = true;
	palmas_gpio->gpio_chip.direction_input = palmas_gpio_input;
	palmas_gpio->gpio_chip.direction_output = palmas_gpio_output;
	palmas_gpio->gpio_chip.to_irq = palmas_gpio_to_irq;
	palmas_gpio->gpio_chip.set	= palmas_gpio_set;
	palmas_gpio->gpio_chip.get	= palmas_gpio_get;
	palmas_gpio->gpio_chip.parent = &pdev->dev;
#अगर_घोषित CONFIG_OF_GPIO
	palmas_gpio->gpio_chip.of_node = pdev->dev.of_node;
#पूर्ण_अगर
	palmas_pdata = dev_get_platdata(palmas->dev);
	अगर (palmas_pdata && palmas_pdata->gpio_base)
		palmas_gpio->gpio_chip.base = palmas_pdata->gpio_base;
	अन्यथा
		palmas_gpio->gpio_chip.base = -1;

	ret = devm_gpiochip_add_data(&pdev->dev, &palmas_gpio->gpio_chip,
				     palmas_gpio);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, palmas_gpio);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver palmas_gpio_driver = अणु
	.driver.name	= "palmas-gpio",
	.driver.of_match_table = of_palmas_gpio_match,
	.probe		= palmas_gpio_probe,
पूर्ण;

अटल पूर्णांक __init palmas_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&palmas_gpio_driver);
पूर्ण
subsys_initcall(palmas_gpio_init);
