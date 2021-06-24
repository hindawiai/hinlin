<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/gpio/gpio-mb86s7x.c
 *
 *  Copyright (C) 2015 Fujitsu Semiconductor Limited
 *  Copyright (C) 2015 Linaro Ltd.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/of_device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>

#समावेश "gpiolib.h"
#समावेश "gpiolib-acpi.h"

/*
 * Only first 8bits of a रेजिस्टर correspond to each pin,
 * so there are 4 रेजिस्टरs क्रम 32 pins.
 */
#घोषणा PDR(x)	(0x0 + x / 8 * 4)
#घोषणा DDR(x)	(0x10 + x / 8 * 4)
#घोषणा PFR(x)	(0x20 + x / 8 * 4)

#घोषणा OFFSET(x)	BIT((x) % 8)

काष्ठा mb86s70_gpio_chip अणु
	काष्ठा gpio_chip gc;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	spinlock_t lock;
पूर्ण;

अटल पूर्णांक mb86s70_gpio_request(काष्ठा gpio_chip *gc, अचिन्हित gpio)
अणु
	काष्ठा mb86s70_gpio_chip *gchip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&gchip->lock, flags);

	val = पढ़ोl(gchip->base + PFR(gpio));
	val &= ~OFFSET(gpio);
	ग_लिखोl(val, gchip->base + PFR(gpio));

	spin_unlock_irqrestore(&gchip->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम mb86s70_gpio_मुक्त(काष्ठा gpio_chip *gc, अचिन्हित gpio)
अणु
	काष्ठा mb86s70_gpio_chip *gchip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&gchip->lock, flags);

	val = पढ़ोl(gchip->base + PFR(gpio));
	val |= OFFSET(gpio);
	ग_लिखोl(val, gchip->base + PFR(gpio));

	spin_unlock_irqrestore(&gchip->lock, flags);
पूर्ण

अटल पूर्णांक mb86s70_gpio_direction_input(काष्ठा gpio_chip *gc, अचिन्हित gpio)
अणु
	काष्ठा mb86s70_gpio_chip *gchip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर val;

	spin_lock_irqsave(&gchip->lock, flags);

	val = पढ़ोl(gchip->base + DDR(gpio));
	val &= ~OFFSET(gpio);
	ग_लिखोl(val, gchip->base + DDR(gpio));

	spin_unlock_irqrestore(&gchip->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mb86s70_gpio_direction_output(काष्ठा gpio_chip *gc,
					 अचिन्हित gpio, पूर्णांक value)
अणु
	काष्ठा mb86s70_gpio_chip *gchip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर val;

	spin_lock_irqsave(&gchip->lock, flags);

	val = पढ़ोl(gchip->base + PDR(gpio));
	अगर (value)
		val |= OFFSET(gpio);
	अन्यथा
		val &= ~OFFSET(gpio);
	ग_लिखोl(val, gchip->base + PDR(gpio));

	val = पढ़ोl(gchip->base + DDR(gpio));
	val |= OFFSET(gpio);
	ग_लिखोl(val, gchip->base + DDR(gpio));

	spin_unlock_irqrestore(&gchip->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mb86s70_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित gpio)
अणु
	काष्ठा mb86s70_gpio_chip *gchip = gpiochip_get_data(gc);

	वापस !!(पढ़ोl(gchip->base + PDR(gpio)) & OFFSET(gpio));
पूर्ण

अटल व्योम mb86s70_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित gpio, पूर्णांक value)
अणु
	काष्ठा mb86s70_gpio_chip *gchip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर val;

	spin_lock_irqsave(&gchip->lock, flags);

	val = पढ़ोl(gchip->base + PDR(gpio));
	अगर (value)
		val |= OFFSET(gpio);
	अन्यथा
		val &= ~OFFSET(gpio);
	ग_लिखोl(val, gchip->base + PDR(gpio));

	spin_unlock_irqrestore(&gchip->lock, flags);
पूर्ण

अटल पूर्णांक mb86s70_gpio_to_irq(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक irq, index;

	क्रम (index = 0;; index++) अणु
		irq = platक्रमm_get_irq(to_platक्रमm_device(gc->parent), index);
		अगर (irq < 0)
			वापस irq;
		अगर (irq == 0)
			अवरोध;
		अगर (irq_get_irq_data(irq)->hwirq == offset)
			वापस irq;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mb86s70_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mb86s70_gpio_chip *gchip;
	पूर्णांक ret;

	gchip = devm_kzalloc(&pdev->dev, माप(*gchip), GFP_KERNEL);
	अगर (gchip == शून्य)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, gchip);

	gchip->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(gchip->base))
		वापस PTR_ERR(gchip->base);

	gchip->clk = devm_clk_get_optional(&pdev->dev, शून्य);
	अगर (IS_ERR(gchip->clk))
		वापस PTR_ERR(gchip->clk);

	ret = clk_prepare_enable(gchip->clk);
	अगर (ret)
		वापस ret;

	spin_lock_init(&gchip->lock);

	gchip->gc.direction_output = mb86s70_gpio_direction_output;
	gchip->gc.direction_input = mb86s70_gpio_direction_input;
	gchip->gc.request = mb86s70_gpio_request;
	gchip->gc.मुक्त = mb86s70_gpio_मुक्त;
	gchip->gc.get = mb86s70_gpio_get;
	gchip->gc.set = mb86s70_gpio_set;
	gchip->gc.to_irq = mb86s70_gpio_to_irq;
	gchip->gc.label = dev_name(&pdev->dev);
	gchip->gc.ngpio = 32;
	gchip->gc.owner = THIS_MODULE;
	gchip->gc.parent = &pdev->dev;
	gchip->gc.base = -1;

	ret = gpiochip_add_data(&gchip->gc, gchip);
	अगर (ret) अणु
		dev_err(&pdev->dev, "couldn't register gpio driver\n");
		clk_disable_unprepare(gchip->clk);
		वापस ret;
	पूर्ण

	acpi_gpiochip_request_पूर्णांकerrupts(&gchip->gc);

	वापस 0;
पूर्ण

अटल पूर्णांक mb86s70_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mb86s70_gpio_chip *gchip = platक्रमm_get_drvdata(pdev);

	acpi_gpiochip_मुक्त_पूर्णांकerrupts(&gchip->gc);
	gpiochip_हटाओ(&gchip->gc);
	clk_disable_unprepare(gchip->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mb86s70_gpio_dt_ids[] = अणु
	अणु .compatible = "fujitsu,mb86s70-gpio" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mb86s70_gpio_dt_ids);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id mb86s70_gpio_acpi_ids[] = अणु
	अणु "SCX0007" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, mb86s70_gpio_acpi_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver mb86s70_gpio_driver = अणु
	.driver = अणु
		.name = "mb86s70-gpio",
		.of_match_table = mb86s70_gpio_dt_ids,
		.acpi_match_table = ACPI_PTR(mb86s70_gpio_acpi_ids),
	पूर्ण,
	.probe = mb86s70_gpio_probe,
	.हटाओ = mb86s70_gpio_हटाओ,
पूर्ण;
module_platक्रमm_driver(mb86s70_gpio_driver);

MODULE_DESCRIPTION("MB86S7x GPIO Driver");
MODULE_ALIAS("platform:mb86s70-gpio");
MODULE_LICENSE("GPL");
