<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sl28cpld GPIO driver
 *
 * Copyright 2020 Michael Walle <michael@walle.cc>
 */

#समावेश <linux/device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpio/regmap.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

/* GPIO flavor */
#घोषणा GPIO_REG_सूची	0x00
#घोषणा GPIO_REG_OUT	0x01
#घोषणा GPIO_REG_IN	0x02
#घोषणा GPIO_REG_IE	0x03
#घोषणा GPIO_REG_IP	0x04

/* input-only flavor */
#घोषणा GPI_REG_IN	0x00

/* output-only flavor */
#घोषणा GPO_REG_OUT	0x00

क्रमागत sl28cpld_gpio_type अणु
	SL28CPLD_GPIO = 1,
	SL28CPLD_GPI,
	SL28CPLD_GPO,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq sl28cpld_gpio_irqs[] = अणु
	REGMAP_IRQ_REG_LINE(0, 8),
	REGMAP_IRQ_REG_LINE(1, 8),
	REGMAP_IRQ_REG_LINE(2, 8),
	REGMAP_IRQ_REG_LINE(3, 8),
	REGMAP_IRQ_REG_LINE(4, 8),
	REGMAP_IRQ_REG_LINE(5, 8),
	REGMAP_IRQ_REG_LINE(6, 8),
	REGMAP_IRQ_REG_LINE(7, 8),
पूर्ण;

अटल पूर्णांक sl28cpld_gpio_irq_init(काष्ठा platक्रमm_device *pdev,
				  अचिन्हित पूर्णांक base,
				  काष्ठा gpio_regmap_config *config)
अणु
	काष्ठा regmap_irq_chip_data *irq_data;
	काष्ठा regmap_irq_chip *irq_chip;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक irq, ret;

	अगर (!device_property_पढ़ो_bool(dev, "interrupt-controller"))
		वापस 0;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	irq_chip = devm_kzalloc(dev, माप(*irq_chip), GFP_KERNEL);
	अगर (!irq_chip)
		वापस -ENOMEM;

	irq_chip->name = "sl28cpld-gpio-irq";
	irq_chip->irqs = sl28cpld_gpio_irqs;
	irq_chip->num_irqs = ARRAY_SIZE(sl28cpld_gpio_irqs);
	irq_chip->num_regs = 1;
	irq_chip->status_base = base + GPIO_REG_IP;
	irq_chip->mask_base = base + GPIO_REG_IE;
	irq_chip->mask_invert = true;
	irq_chip->ack_base = base + GPIO_REG_IP;

	ret = devm_regmap_add_irq_chip_fwnode(dev, dev_fwnode(dev),
					      config->regmap, irq,
					      IRQF_SHARED | IRQF_ONESHOT,
					      0, irq_chip, &irq_data);
	अगर (ret)
		वापस ret;

	config->irq_करोमुख्य = regmap_irq_get_करोमुख्य(irq_data);

	वापस 0;
पूर्ण

अटल पूर्णांक sl28cpld_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_regmap_config config = अणु0पूर्ण;
	क्रमागत sl28cpld_gpio_type type;
	काष्ठा regmap *regmap;
	u32 base;
	पूर्णांक ret;

	अगर (!pdev->dev.parent)
		वापस -ENODEV;

	type = (uपूर्णांकptr_t)device_get_match_data(&pdev->dev);
	अगर (!type)
		वापस -ENODEV;

	ret = device_property_पढ़ो_u32(&pdev->dev, "reg", &base);
	अगर (ret)
		वापस -EINVAL;

	regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!regmap)
		वापस -ENODEV;

	config.regmap = regmap;
	config.parent = &pdev->dev;
	config.ngpio = 8;

	चयन (type) अणु
	हाल SL28CPLD_GPIO:
		config.reg_dat_base = base + GPIO_REG_IN;
		config.reg_set_base = base + GPIO_REG_OUT;
		/* reg_dir_out_base might be zero */
		config.reg_dir_out_base = GPIO_REGMAP_ADDR(base + GPIO_REG_सूची);

		/* This type supports पूर्णांकerrupts */
		ret = sl28cpld_gpio_irq_init(pdev, base, &config);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल SL28CPLD_GPO:
		config.reg_set_base = base + GPO_REG_OUT;
		अवरोध;
	हाल SL28CPLD_GPI:
		config.reg_dat_base = base + GPI_REG_IN;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "unknown type %d\n", type);
		वापस -ENODEV;
	पूर्ण

	वापस PTR_ERR_OR_ZERO(devm_gpio_regmap_रेजिस्टर(&pdev->dev, &config));
पूर्ण

अटल स्थिर काष्ठा of_device_id sl28cpld_gpio_of_match[] = अणु
	अणु .compatible = "kontron,sl28cpld-gpio", .data = (व्योम *)SL28CPLD_GPIO पूर्ण,
	अणु .compatible = "kontron,sl28cpld-gpi", .data = (व्योम *)SL28CPLD_GPI पूर्ण,
	अणु .compatible = "kontron,sl28cpld-gpo", .data = (व्योम *)SL28CPLD_GPO पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sl28cpld_gpio_of_match);

अटल काष्ठा platक्रमm_driver sl28cpld_gpio_driver = अणु
	.probe = sl28cpld_gpio_probe,
	.driver = अणु
		.name = "sl28cpld-gpio",
		.of_match_table = sl28cpld_gpio_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sl28cpld_gpio_driver);

MODULE_DESCRIPTION("sl28cpld GPIO Driver");
MODULE_AUTHOR("Michael Walle <michael@walle.cc>");
MODULE_LICENSE("GPL");
