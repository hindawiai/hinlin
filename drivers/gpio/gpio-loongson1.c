<शैली गुरु>
/*
 * GPIO Driver क्रम Loongson 1 SoC
 *
 * Copyright (C) 2015-2016 Zhang, Keguang <keguang.zhang@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/module.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bitops.h>

/* Loongson 1 GPIO Register Definitions */
#घोषणा GPIO_CFG		0x0
#घोषणा GPIO_सूची		0x10
#घोषणा GPIO_DATA		0x20
#घोषणा GPIO_OUTPUT		0x30

अटल व्योम __iomem *gpio_reg_base;

अटल पूर्णांक ls1x_gpio_request(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gc->bgpio_lock, flags);
	__raw_ग_लिखोl(__raw_पढ़ोl(gpio_reg_base + GPIO_CFG) | BIT(offset),
		     gpio_reg_base + GPIO_CFG);
	spin_unlock_irqrestore(&gc->bgpio_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम ls1x_gpio_मुक्त(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gc->bgpio_lock, flags);
	__raw_ग_लिखोl(__raw_पढ़ोl(gpio_reg_base + GPIO_CFG) & ~BIT(offset),
		     gpio_reg_base + GPIO_CFG);
	spin_unlock_irqrestore(&gc->bgpio_lock, flags);
पूर्ण

अटल पूर्णांक ls1x_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा gpio_chip *gc;
	पूर्णांक ret;

	gc = devm_kzalloc(dev, माप(*gc), GFP_KERNEL);
	अगर (!gc)
		वापस -ENOMEM;

	gpio_reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(gpio_reg_base))
		वापस PTR_ERR(gpio_reg_base);

	ret = bgpio_init(gc, dev, 4, gpio_reg_base + GPIO_DATA,
			 gpio_reg_base + GPIO_OUTPUT, शून्य,
			 शून्य, gpio_reg_base + GPIO_सूची, 0);
	अगर (ret)
		जाओ err;

	gc->owner = THIS_MODULE;
	gc->request = ls1x_gpio_request;
	gc->मुक्त = ls1x_gpio_मुक्त;
	gc->base = pdev->id * 32;

	ret = devm_gpiochip_add_data(dev, gc, शून्य);
	अगर (ret)
		जाओ err;

	platक्रमm_set_drvdata(pdev, gc);
	dev_info(dev, "Loongson1 GPIO driver registered\n");

	वापस 0;
err:
	dev_err(dev, "failed to register GPIO device\n");
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver ls1x_gpio_driver = अणु
	.probe	= ls1x_gpio_probe,
	.driver	= अणु
		.name	= "ls1x-gpio",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ls1x_gpio_driver);

MODULE_AUTHOR("Kelvin Cheung <keguang.zhang@gmail.com>");
MODULE_DESCRIPTION("Loongson1 GPIO driver");
MODULE_LICENSE("GPL");
