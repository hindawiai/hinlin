<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * GPIO Driver क्रम Dialog DA9055 PMICs.
 *
 * Copyright(c) 2012 Dialog Semiconductor Ltd.
 *
 * Author: David Dajun Chen <dchen@diasemi.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/driver.h>

#समावेश <linux/mfd/da9055/core.h>
#समावेश <linux/mfd/da9055/reg.h>
#समावेश <linux/mfd/da9055/pdata.h>

#घोषणा DA9055_VDD_IO			0x0
#घोषणा DA9055_PUSH_PULL		0x3
#घोषणा DA9055_ACT_LOW			0x0
#घोषणा DA9055_GPI			0x1
#घोषणा DA9055_PORT_MASK		0x3
#घोषणा DA9055_PORT_SHIFT(offset)	(4 * (offset % 2))

#घोषणा DA9055_INPUT			DA9055_GPI
#घोषणा DA9055_OUTPUT			DA9055_PUSH_PULL
#घोषणा DA9055_IRQ_GPI0			3

काष्ठा da9055_gpio अणु
	काष्ठा da9055 *da9055;
	काष्ठा gpio_chip gp;
पूर्ण;

अटल पूर्णांक da9055_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा da9055_gpio *gpio = gpiochip_get_data(gc);
	पूर्णांक gpio_direction = 0;
	पूर्णांक ret;

	/* Get GPIO direction */
	ret = da9055_reg_पढ़ो(gpio->da9055, (offset >> 1) + DA9055_REG_GPIO0_1);
	अगर (ret < 0)
		वापस ret;

	gpio_direction = ret & (DA9055_PORT_MASK) << DA9055_PORT_SHIFT(offset);
	gpio_direction >>= DA9055_PORT_SHIFT(offset);
	चयन (gpio_direction) अणु
	हाल DA9055_INPUT:
		ret = da9055_reg_पढ़ो(gpio->da9055, DA9055_REG_STATUS_B);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल DA9055_OUTPUT:
		ret = da9055_reg_पढ़ो(gpio->da9055, DA9055_REG_GPIO_MODE0_2);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस ret & (1 << offset);

पूर्ण

अटल व्योम da9055_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा da9055_gpio *gpio = gpiochip_get_data(gc);

	da9055_reg_update(gpio->da9055,
			DA9055_REG_GPIO_MODE0_2,
			1 << offset,
			value << offset);
पूर्ण

अटल पूर्णांक da9055_gpio_direction_input(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा da9055_gpio *gpio = gpiochip_get_data(gc);
	अचिन्हित अक्षर reg_byte;

	reg_byte = (DA9055_ACT_LOW | DA9055_GPI)
				<< DA9055_PORT_SHIFT(offset);

	वापस da9055_reg_update(gpio->da9055, (offset >> 1) +
				DA9055_REG_GPIO0_1,
				DA9055_PORT_MASK <<
				DA9055_PORT_SHIFT(offset),
				reg_byte);
पूर्ण

अटल पूर्णांक da9055_gpio_direction_output(काष्ठा gpio_chip *gc,
					अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा da9055_gpio *gpio = gpiochip_get_data(gc);
	अचिन्हित अक्षर reg_byte;
	पूर्णांक ret;

	reg_byte = (DA9055_VDD_IO | DA9055_PUSH_PULL)
					<< DA9055_PORT_SHIFT(offset);

	ret = da9055_reg_update(gpio->da9055, (offset >> 1) +
				DA9055_REG_GPIO0_1,
				DA9055_PORT_MASK <<
				DA9055_PORT_SHIFT(offset),
				reg_byte);
	अगर (ret < 0)
		वापस ret;

	da9055_gpio_set(gc, offset, value);

	वापस 0;
पूर्ण

अटल पूर्णांक da9055_gpio_to_irq(काष्ठा gpio_chip *gc, u32 offset)
अणु
	काष्ठा da9055_gpio *gpio = gpiochip_get_data(gc);
	काष्ठा da9055 *da9055 = gpio->da9055;

	वापस regmap_irq_get_virq(da9055->irq_data,
				  DA9055_IRQ_GPI0 + offset);
पूर्ण

अटल स्थिर काष्ठा gpio_chip reference_gp = अणु
	.label = "da9055-gpio",
	.owner = THIS_MODULE,
	.get = da9055_gpio_get,
	.set = da9055_gpio_set,
	.direction_input = da9055_gpio_direction_input,
	.direction_output = da9055_gpio_direction_output,
	.to_irq = da9055_gpio_to_irq,
	.can_sleep = true,
	.ngpio = 3,
	.base = -1,
पूर्ण;

अटल पूर्णांक da9055_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9055_gpio *gpio;
	काष्ठा da9055_pdata *pdata;
	पूर्णांक ret;

	gpio = devm_kzalloc(&pdev->dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	gpio->da9055 = dev_get_drvdata(pdev->dev.parent);
	pdata = dev_get_platdata(gpio->da9055->dev);

	gpio->gp = reference_gp;
	अगर (pdata && pdata->gpio_base)
		gpio->gp.base = pdata->gpio_base;

	ret = devm_gpiochip_add_data(&pdev->dev, &gpio->gp, gpio);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, gpio);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da9055_gpio_driver = अणु
	.probe = da9055_gpio_probe,
	.driver = अणु
		.name	= "da9055-gpio",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init da9055_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&da9055_gpio_driver);
पूर्ण
subsys_initcall(da9055_gpio_init);

अटल व्योम __निकास da9055_gpio_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&da9055_gpio_driver);
पूर्ण
module_निकास(da9055_gpio_निकास);

MODULE_AUTHOR("David Dajun Chen <dchen@diasemi.com>");
MODULE_DESCRIPTION("DA9055 GPIO Device Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da9055-gpio");
