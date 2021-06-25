<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sl28cpld पूर्णांकerrupt controller driver
 *
 * Copyright 2020 Kontron Europe GmbH
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>

#घोषणा INTC_IE 0x00
#घोषणा INTC_IP 0x01

अटल स्थिर काष्ठा regmap_irq sl28cpld_irqs[] = अणु
	REGMAP_IRQ_REG_LINE(0, 8),
	REGMAP_IRQ_REG_LINE(1, 8),
	REGMAP_IRQ_REG_LINE(2, 8),
	REGMAP_IRQ_REG_LINE(3, 8),
	REGMAP_IRQ_REG_LINE(4, 8),
	REGMAP_IRQ_REG_LINE(5, 8),
	REGMAP_IRQ_REG_LINE(6, 8),
	REGMAP_IRQ_REG_LINE(7, 8),
पूर्ण;

काष्ठा sl28cpld_पूर्णांकc अणु
	काष्ठा regmap *regmap;
	काष्ठा regmap_irq_chip chip;
	काष्ठा regmap_irq_chip_data *irq_data;
पूर्ण;

अटल पूर्णांक sl28cpld_पूर्णांकc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sl28cpld_पूर्णांकc *irqchip;
	पूर्णांक irq;
	u32 base;
	पूर्णांक ret;

	अगर (!dev->parent)
		वापस -ENODEV;

	irqchip = devm_kzalloc(dev, माप(*irqchip), GFP_KERNEL);
	अगर (!irqchip)
		वापस -ENOMEM;

	irqchip->regmap = dev_get_regmap(dev->parent, शून्य);
	अगर (!irqchip->regmap)
		वापस -ENODEV;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = device_property_पढ़ो_u32(&pdev->dev, "reg", &base);
	अगर (ret)
		वापस -EINVAL;

	irqchip->chip.name = "sl28cpld-intc";
	irqchip->chip.irqs = sl28cpld_irqs;
	irqchip->chip.num_irqs = ARRAY_SIZE(sl28cpld_irqs);
	irqchip->chip.num_regs = 1;
	irqchip->chip.status_base = base + INTC_IP;
	irqchip->chip.mask_base = base + INTC_IE;
	irqchip->chip.mask_invert = true;
	irqchip->chip.ack_base = base + INTC_IP;

	वापस devm_regmap_add_irq_chip_fwnode(dev, dev_fwnode(dev),
					       irqchip->regmap, irq,
					       IRQF_SHARED | IRQF_ONESHOT, 0,
					       &irqchip->chip,
					       &irqchip->irq_data);
पूर्ण

अटल स्थिर काष्ठा of_device_id sl28cpld_पूर्णांकc_of_match[] = अणु
	अणु .compatible = "kontron,sl28cpld-intc" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sl28cpld_पूर्णांकc_of_match);

अटल काष्ठा platक्रमm_driver sl28cpld_पूर्णांकc_driver = अणु
	.probe = sl28cpld_पूर्णांकc_probe,
	.driver = अणु
		.name = "sl28cpld-intc",
		.of_match_table = sl28cpld_पूर्णांकc_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(sl28cpld_पूर्णांकc_driver);

MODULE_DESCRIPTION("sl28cpld Interrupt Controller Driver");
MODULE_AUTHOR("Michael Walle <michael@walle.cc>");
MODULE_LICENSE("GPL");
