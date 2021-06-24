<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * GPIO Driver क्रम Dialog DA9052 PMICs.
 *
 * Copyright(c) 2011 Dialog Semiconductor Ltd.
 *
 * Author: David Dajun Chen <dchen@diasemi.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/seq_file.h>

#समावेश <linux/mfd/da9052/da9052.h>
#समावेश <linux/mfd/da9052/reg.h>
#समावेश <linux/mfd/da9052/pdata.h>

#घोषणा DA9052_INPUT				1
#घोषणा DA9052_OUTPUT_OPENDRAIN		2
#घोषणा DA9052_OUTPUT_PUSHPULL			3

#घोषणा DA9052_SUPPLY_VDD_IO1			0

#घोषणा DA9052_DEBOUNCING_OFF			0
#घोषणा DA9052_DEBOUNCING_ON			1

#घोषणा DA9052_OUTPUT_LOWLEVEL			0

#घोषणा DA9052_ACTIVE_LOW			0
#घोषणा DA9052_ACTIVE_HIGH			1

#घोषणा DA9052_GPIO_MAX_PORTS_PER_REGISTER	8
#घोषणा DA9052_GPIO_SHIFT_COUNT(no)		(no%8)
#घोषणा DA9052_GPIO_MASK_UPPER_NIBBLE		0xF0
#घोषणा DA9052_GPIO_MASK_LOWER_NIBBLE		0x0F
#घोषणा DA9052_GPIO_NIBBLE_SHIFT		4
#घोषणा DA9052_IRQ_GPI0			16
#घोषणा DA9052_GPIO_ODD_SHIFT			7
#घोषणा DA9052_GPIO_EVEN_SHIFT			3

काष्ठा da9052_gpio अणु
	काष्ठा da9052 *da9052;
	काष्ठा gpio_chip gp;
पूर्ण;

अटल अचिन्हित अक्षर da9052_gpio_port_odd(अचिन्हित offset)
अणु
	वापस offset % 2;
पूर्ण

अटल पूर्णांक da9052_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा da9052_gpio *gpio = gpiochip_get_data(gc);
	पूर्णांक da9052_port_direction = 0;
	पूर्णांक ret;

	ret = da9052_reg_पढ़ो(gpio->da9052,
			      DA9052_GPIO_0_1_REG + (offset >> 1));
	अगर (ret < 0)
		वापस ret;

	अगर (da9052_gpio_port_odd(offset)) अणु
		da9052_port_direction = ret & DA9052_GPIO_ODD_PORT_PIN;
		da9052_port_direction >>= 4;
	पूर्ण अन्यथा अणु
		da9052_port_direction = ret & DA9052_GPIO_EVEN_PORT_PIN;
	पूर्ण

	चयन (da9052_port_direction) अणु
	हाल DA9052_INPUT:
		अगर (offset < DA9052_GPIO_MAX_PORTS_PER_REGISTER)
			ret = da9052_reg_पढ़ो(gpio->da9052,
					      DA9052_STATUS_C_REG);
		अन्यथा
			ret = da9052_reg_पढ़ो(gpio->da9052,
					      DA9052_STATUS_D_REG);
		अगर (ret < 0)
			वापस ret;
		वापस !!(ret & (1 << DA9052_GPIO_SHIFT_COUNT(offset)));
	हाल DA9052_OUTPUT_PUSHPULL:
		अगर (da9052_gpio_port_odd(offset))
			वापस !!(ret & DA9052_GPIO_ODD_PORT_MODE);
		अन्यथा
			वापस !!(ret & DA9052_GPIO_EVEN_PORT_MODE);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम da9052_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा da9052_gpio *gpio = gpiochip_get_data(gc);
	पूर्णांक ret;

	अगर (da9052_gpio_port_odd(offset)) अणु
			ret = da9052_reg_update(gpio->da9052, (offset >> 1) +
						DA9052_GPIO_0_1_REG,
						DA9052_GPIO_ODD_PORT_MODE,
						value << DA9052_GPIO_ODD_SHIFT);
			अगर (ret != 0)
				dev_err(gpio->da9052->dev,
					"Failed to updated gpio odd reg,%d",
					ret);
	पूर्ण अन्यथा अणु
			ret = da9052_reg_update(gpio->da9052, (offset >> 1) +
						DA9052_GPIO_0_1_REG,
						DA9052_GPIO_EVEN_PORT_MODE,
						value << DA9052_GPIO_EVEN_SHIFT);
			अगर (ret != 0)
				dev_err(gpio->da9052->dev,
					"Failed to updated gpio even reg,%d",
					ret);
	पूर्ण
पूर्ण

अटल पूर्णांक da9052_gpio_direction_input(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा da9052_gpio *gpio = gpiochip_get_data(gc);
	अचिन्हित अक्षर रेजिस्टर_value;
	पूर्णांक ret;

	/* Format: function - 2 bits type - 1 bit mode - 1 bit */
	रेजिस्टर_value = DA9052_INPUT | DA9052_ACTIVE_LOW << 2 |
			 DA9052_DEBOUNCING_ON << 3;

	अगर (da9052_gpio_port_odd(offset))
		ret = da9052_reg_update(gpio->da9052, (offset >> 1) +
					DA9052_GPIO_0_1_REG,
					DA9052_GPIO_MASK_UPPER_NIBBLE,
					(रेजिस्टर_value <<
					DA9052_GPIO_NIBBLE_SHIFT));
	अन्यथा
		ret = da9052_reg_update(gpio->da9052, (offset >> 1) +
					DA9052_GPIO_0_1_REG,
					DA9052_GPIO_MASK_LOWER_NIBBLE,
					रेजिस्टर_value);

	वापस ret;
पूर्ण

अटल पूर्णांक da9052_gpio_direction_output(काष्ठा gpio_chip *gc,
					अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा da9052_gpio *gpio = gpiochip_get_data(gc);
	अचिन्हित अक्षर रेजिस्टर_value;
	पूर्णांक ret;

	/* Format: Function - 2 bits Type - 1 bit Mode - 1 bit */
	रेजिस्टर_value = DA9052_OUTPUT_PUSHPULL | DA9052_SUPPLY_VDD_IO1 << 2 |
			 value << 3;

	अगर (da9052_gpio_port_odd(offset))
		ret = da9052_reg_update(gpio->da9052, (offset >> 1) +
					DA9052_GPIO_0_1_REG,
					DA9052_GPIO_MASK_UPPER_NIBBLE,
					(रेजिस्टर_value <<
					DA9052_GPIO_NIBBLE_SHIFT));
	अन्यथा
		ret = da9052_reg_update(gpio->da9052, (offset >> 1) +
					DA9052_GPIO_0_1_REG,
					DA9052_GPIO_MASK_LOWER_NIBBLE,
					रेजिस्टर_value);

	वापस ret;
पूर्ण

अटल पूर्णांक da9052_gpio_to_irq(काष्ठा gpio_chip *gc, u32 offset)
अणु
	काष्ठा da9052_gpio *gpio = gpiochip_get_data(gc);
	काष्ठा da9052 *da9052 = gpio->da9052;

	पूर्णांक irq;

	irq = regmap_irq_get_virq(da9052->irq_data, DA9052_IRQ_GPI0 + offset);

	वापस irq;
पूर्ण

अटल स्थिर काष्ठा gpio_chip reference_gp = अणु
	.label = "da9052-gpio",
	.owner = THIS_MODULE,
	.get = da9052_gpio_get,
	.set = da9052_gpio_set,
	.direction_input = da9052_gpio_direction_input,
	.direction_output = da9052_gpio_direction_output,
	.to_irq = da9052_gpio_to_irq,
	.can_sleep = true,
	.ngpio = 16,
	.base = -1,
पूर्ण;

अटल पूर्णांक da9052_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9052_gpio *gpio;
	काष्ठा da9052_pdata *pdata;
	पूर्णांक ret;

	gpio = devm_kzalloc(&pdev->dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	gpio->da9052 = dev_get_drvdata(pdev->dev.parent);
	pdata = dev_get_platdata(gpio->da9052->dev);

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

अटल काष्ठा platक्रमm_driver da9052_gpio_driver = अणु
	.probe = da9052_gpio_probe,
	.driver = अणु
		.name	= "da9052-gpio",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(da9052_gpio_driver);

MODULE_AUTHOR("David Dajun Chen <dchen@diasemi.com>");
MODULE_DESCRIPTION("DA9052 GPIO Device Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da9052-gpio");
