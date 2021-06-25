<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Promontory GPIO driver
 *
 * Copyright (C) 2015 ASMedia Technology Inc.
 * Author: YD Tseng <yd_tseng@यंत्रedia.com.tw>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/acpi.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा PT_TOTAL_GPIO 8

/* PCI-E MMIO रेजिस्टर offsets */
#घोषणा PT_सूचीECTION_REG   0x00
#घोषणा PT_INPUTDATA_REG   0x04
#घोषणा PT_OUTPUTDATA_REG  0x08
#घोषणा PT_CLOCKRATE_REG   0x0C
#घोषणा PT_SYNC_REG        0x28

काष्ठा pt_gpio_chip अणु
	काष्ठा gpio_chip         gc;
	व्योम __iomem             *reg_base;
पूर्ण;

अटल पूर्णांक pt_gpio_request(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा pt_gpio_chip *pt_gpio = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;
	u32 using_pins;

	dev_dbg(gc->parent, "pt_gpio_request offset=%x\n", offset);

	spin_lock_irqsave(&gc->bgpio_lock, flags);

	using_pins = पढ़ोl(pt_gpio->reg_base + PT_SYNC_REG);
	अगर (using_pins & BIT(offset)) अणु
		dev_warn(gc->parent, "PT GPIO pin %x reconfigured\n",
			 offset);
		spin_unlock_irqrestore(&gc->bgpio_lock, flags);
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(using_pins | BIT(offset), pt_gpio->reg_base + PT_SYNC_REG);

	spin_unlock_irqrestore(&gc->bgpio_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम pt_gpio_मुक्त(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा pt_gpio_chip *pt_gpio = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;
	u32 using_pins;

	spin_lock_irqsave(&gc->bgpio_lock, flags);

	using_pins = पढ़ोl(pt_gpio->reg_base + PT_SYNC_REG);
	using_pins &= ~BIT(offset);
	ग_लिखोl(using_pins, pt_gpio->reg_base + PT_SYNC_REG);

	spin_unlock_irqrestore(&gc->bgpio_lock, flags);

	dev_dbg(gc->parent, "pt_gpio_free offset=%x\n", offset);
पूर्ण

अटल पूर्णांक pt_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा acpi_device *acpi_dev;
	acpi_handle handle = ACPI_HANDLE(dev);
	काष्ठा pt_gpio_chip *pt_gpio;
	पूर्णांक ret = 0;

	अगर (acpi_bus_get_device(handle, &acpi_dev)) अणु
		dev_err(dev, "PT GPIO device node not found\n");
		वापस -ENODEV;
	पूर्ण

	pt_gpio = devm_kzalloc(dev, माप(काष्ठा pt_gpio_chip), GFP_KERNEL);
	अगर (!pt_gpio)
		वापस -ENOMEM;

	pt_gpio->reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pt_gpio->reg_base)) अणु
		dev_err(dev, "Failed to map MMIO resource for PT GPIO.\n");
		वापस PTR_ERR(pt_gpio->reg_base);
	पूर्ण

	ret = bgpio_init(&pt_gpio->gc, dev, 4,
			 pt_gpio->reg_base + PT_INPUTDATA_REG,
			 pt_gpio->reg_base + PT_OUTPUTDATA_REG, शून्य,
			 pt_gpio->reg_base + PT_सूचीECTION_REG, शून्य,
			 BGPIOF_READ_OUTPUT_REG_SET);
	अगर (ret) अणु
		dev_err(dev, "bgpio_init failed\n");
		वापस ret;
	पूर्ण

	pt_gpio->gc.owner            = THIS_MODULE;
	pt_gpio->gc.request          = pt_gpio_request;
	pt_gpio->gc.मुक्त             = pt_gpio_मुक्त;
	pt_gpio->gc.ngpio            = PT_TOTAL_GPIO;
#अगर defined(CONFIG_OF_GPIO)
	pt_gpio->gc.of_node          = dev->of_node;
#पूर्ण_अगर
	ret = gpiochip_add_data(&pt_gpio->gc, pt_gpio);
	अगर (ret) अणु
		dev_err(dev, "Failed to register GPIO lib\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pt_gpio);

	/* initialize रेजिस्टर setting */
	ग_लिखोl(0, pt_gpio->reg_base + PT_SYNC_REG);
	ग_लिखोl(0, pt_gpio->reg_base + PT_CLOCKRATE_REG);

	dev_dbg(dev, "PT GPIO driver loaded\n");
	वापस ret;
पूर्ण

अटल पूर्णांक pt_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pt_gpio_chip *pt_gpio = platक्रमm_get_drvdata(pdev);

	gpiochip_हटाओ(&pt_gpio->gc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id pt_gpio_acpi_match[] = अणु
	अणु "AMDF030", 0 पूर्ण,
	अणु "AMDIF030", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, pt_gpio_acpi_match);

अटल काष्ठा platक्रमm_driver pt_gpio_driver = अणु
	.driver = अणु
		.name = "pt-gpio",
		.acpi_match_table = ACPI_PTR(pt_gpio_acpi_match),
	पूर्ण,
	.probe = pt_gpio_probe,
	.हटाओ = pt_gpio_हटाओ,
पूर्ण;

module_platक्रमm_driver(pt_gpio_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YD Tseng <yd_tseng@asmedia.com.tw>");
MODULE_DESCRIPTION("AMD Promontory GPIO Driver");
