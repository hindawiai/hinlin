<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2003-2015 Broadcom Corporation
 * All Rights Reserved
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/acpi.h>

/*
 * XLP GPIO has multiple 32 bit रेजिस्टरs क्रम each feature where each रेजिस्टर
 * controls 32 pins. So, pins up to 64 require 2 32-bit रेजिस्टरs and up to 96
 * require 3 32-bit रेजिस्टरs क्रम each feature.
 * Here we only define offset of the first रेजिस्टर क्रम each feature. Offset of
 * the रेजिस्टरs क्रम pins greater than 32 can be calculated as following(Use
 * GPIO_INT_STAT as example):
 *
 * offset = (gpio / XLP_GPIO_REGSZ) * 4;
 * reg_addr = addr + offset;
 *
 * where addr is base address of the that feature रेजिस्टर and gpio is the pin.
 */
#घोषणा GPIO_OUTPUT_EN		0x00
#घोषणा GPIO_PADDRV		0x08
#घोषणा GPIO_INT_EN00		0x18
#घोषणा GPIO_INT_EN10		0x20
#घोषणा GPIO_INT_EN20		0x28
#घोषणा GPIO_INT_EN30		0x30
#घोषणा GPIO_INT_POL		0x38
#घोषणा GPIO_INT_TYPE		0x40
#घोषणा GPIO_INT_STAT		0x48

#घोषणा GPIO_9XX_BYTESWAP	0X00
#घोषणा GPIO_9XX_CTRL		0X04
#घोषणा GPIO_9XX_OUTPUT_EN	0x14
#घोषणा GPIO_9XX_PADDRV		0x24
/*
 * Only क्रम 4 पूर्णांकerrupt enable reg are defined क्रम now,
 * total reg available are 12.
 */
#घोषणा GPIO_9XX_INT_EN00	0x44
#घोषणा GPIO_9XX_INT_EN10	0x54
#घोषणा GPIO_9XX_INT_EN20	0x64
#घोषणा GPIO_9XX_INT_EN30	0x74
#घोषणा GPIO_9XX_INT_POL	0x104
#घोषणा GPIO_9XX_INT_TYPE	0x114
#घोषणा GPIO_9XX_INT_STAT	0x124

#घोषणा GPIO_3XX_INT_EN00	0x18
#घोषणा GPIO_3XX_INT_EN10	0x20
#घोषणा GPIO_3XX_INT_EN20	0x28
#घोषणा GPIO_3XX_INT_EN30	0x30
#घोषणा GPIO_3XX_INT_POL	0x78
#घोषणा GPIO_3XX_INT_TYPE	0x80
#घोषणा GPIO_3XX_INT_STAT	0x88

/* Interrupt type रेजिस्टर mask */
#घोषणा XLP_GPIO_IRQ_TYPE_LVL	0x0
#घोषणा XLP_GPIO_IRQ_TYPE_EDGE	0x1

/* Interrupt polarity रेजिस्टर mask */
#घोषणा XLP_GPIO_IRQ_POL_HIGH	0x0
#घोषणा XLP_GPIO_IRQ_POL_LOW	0x1

#घोषणा XLP_GPIO_REGSZ		32
#घोषणा XLP_GPIO_IRQ_BASE	768
#घोषणा XLP_MAX_NR_GPIO		96

/* XLP variants supported by this driver */
क्रमागत अणु
	XLP_GPIO_VARIANT_XLP832 = 1,
	XLP_GPIO_VARIANT_XLP316,
	XLP_GPIO_VARIANT_XLP208,
	XLP_GPIO_VARIANT_XLP980,
	XLP_GPIO_VARIANT_XLP532,
	GPIO_VARIANT_VULCAN
पूर्ण;

काष्ठा xlp_gpio_priv अणु
	काष्ठा gpio_chip chip;
	DECLARE_BITMAP(gpio_enabled_mask, XLP_MAX_NR_GPIO);
	व्योम __iomem *gpio_पूर्णांकr_en;	/* poपूर्णांकer to first पूर्णांकr enable reg */
	व्योम __iomem *gpio_पूर्णांकr_stat;	/* poपूर्णांकer to first पूर्णांकr status reg */
	व्योम __iomem *gpio_पूर्णांकr_type;	/* poपूर्णांकer to first पूर्णांकr type reg */
	व्योम __iomem *gpio_पूर्णांकr_pol;	/* poपूर्णांकer to first पूर्णांकr polarity reg */
	व्योम __iomem *gpio_out_en;	/* poपूर्णांकer to first output enable reg */
	व्योम __iomem *gpio_paddrv;	/* poपूर्णांकer to first pad drive reg */
	spinlock_t lock;
पूर्ण;

अटल पूर्णांक xlp_gpio_get_reg(व्योम __iomem *addr, अचिन्हित gpio)
अणु
	u32 pos, regset;

	pos = gpio % XLP_GPIO_REGSZ;
	regset = (gpio / XLP_GPIO_REGSZ) * 4;
	वापस !!(पढ़ोl(addr + regset) & BIT(pos));
पूर्ण

अटल व्योम xlp_gpio_set_reg(व्योम __iomem *addr, अचिन्हित gpio, पूर्णांक state)
अणु
	u32 value, pos, regset;

	pos = gpio % XLP_GPIO_REGSZ;
	regset = (gpio / XLP_GPIO_REGSZ) * 4;
	value = पढ़ोl(addr + regset);

	अगर (state)
		value |= BIT(pos);
	अन्यथा
		value &= ~BIT(pos);

	ग_लिखोl(value, addr + regset);
पूर्ण

अटल व्योम xlp_gpio_irq_disable(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc  = irq_data_get_irq_chip_data(d);
	काष्ठा xlp_gpio_priv *priv = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	xlp_gpio_set_reg(priv->gpio_पूर्णांकr_en, d->hwirq, 0x0);
	__clear_bit(d->hwirq, priv->gpio_enabled_mask);
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल व्योम xlp_gpio_irq_mask_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc  = irq_data_get_irq_chip_data(d);
	काष्ठा xlp_gpio_priv *priv = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	xlp_gpio_set_reg(priv->gpio_पूर्णांकr_en, d->hwirq, 0x0);
	xlp_gpio_set_reg(priv->gpio_पूर्णांकr_stat, d->hwirq, 0x1);
	__clear_bit(d->hwirq, priv->gpio_enabled_mask);
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल व्योम xlp_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc  = irq_data_get_irq_chip_data(d);
	काष्ठा xlp_gpio_priv *priv = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	xlp_gpio_set_reg(priv->gpio_पूर्णांकr_en, d->hwirq, 0x1);
	__set_bit(d->hwirq, priv->gpio_enabled_mask);
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल पूर्णांक xlp_gpio_set_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc  = irq_data_get_irq_chip_data(d);
	काष्ठा xlp_gpio_priv *priv = gpiochip_get_data(gc);
	पूर्णांक pol, irq_type;

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		irq_type = XLP_GPIO_IRQ_TYPE_EDGE;
		pol = XLP_GPIO_IRQ_POL_HIGH;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		irq_type = XLP_GPIO_IRQ_TYPE_EDGE;
		pol = XLP_GPIO_IRQ_POL_LOW;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		irq_type = XLP_GPIO_IRQ_TYPE_LVL;
		pol = XLP_GPIO_IRQ_POL_HIGH;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		irq_type = XLP_GPIO_IRQ_TYPE_LVL;
		pol = XLP_GPIO_IRQ_POL_LOW;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	xlp_gpio_set_reg(priv->gpio_पूर्णांकr_type, d->hwirq, irq_type);
	xlp_gpio_set_reg(priv->gpio_पूर्णांकr_pol, d->hwirq, pol);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip xlp_gpio_irq_chip = अणु
	.name		= "XLP-GPIO",
	.irq_mask_ack	= xlp_gpio_irq_mask_ack,
	.irq_disable	= xlp_gpio_irq_disable,
	.irq_set_type	= xlp_gpio_set_irq_type,
	.irq_unmask	= xlp_gpio_irq_unmask,
	.flags		= IRQCHIP_ONESHOT_SAFE,
पूर्ण;

अटल व्योम xlp_gpio_generic_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा xlp_gpio_priv *priv = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *irqchip = irq_desc_get_chip(desc);
	पूर्णांक gpio, regoff;
	u32 gpio_stat;

	regoff = -1;
	gpio_stat = 0;

	chained_irq_enter(irqchip, desc);
	क्रम_each_set_bit(gpio, priv->gpio_enabled_mask, XLP_MAX_NR_GPIO) अणु
		अगर (regoff != gpio / XLP_GPIO_REGSZ) अणु
			regoff = gpio / XLP_GPIO_REGSZ;
			gpio_stat = पढ़ोl(priv->gpio_पूर्णांकr_stat + regoff * 4);
		पूर्ण

		अगर (gpio_stat & BIT(gpio % XLP_GPIO_REGSZ))
			generic_handle_irq(irq_find_mapping(
						priv->chip.irq.करोमुख्य, gpio));
	पूर्ण
	chained_irq_निकास(irqchip, desc);
पूर्ण

अटल पूर्णांक xlp_gpio_dir_output(काष्ठा gpio_chip *gc, अचिन्हित gpio, पूर्णांक state)
अणु
	काष्ठा xlp_gpio_priv *priv = gpiochip_get_data(gc);

	BUG_ON(gpio >= gc->ngpio);
	xlp_gpio_set_reg(priv->gpio_out_en, gpio, 0x1);

	वापस 0;
पूर्ण

अटल पूर्णांक xlp_gpio_dir_input(काष्ठा gpio_chip *gc, अचिन्हित gpio)
अणु
	काष्ठा xlp_gpio_priv *priv = gpiochip_get_data(gc);

	BUG_ON(gpio >= gc->ngpio);
	xlp_gpio_set_reg(priv->gpio_out_en, gpio, 0x0);

	वापस 0;
पूर्ण

अटल पूर्णांक xlp_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित gpio)
अणु
	काष्ठा xlp_gpio_priv *priv = gpiochip_get_data(gc);

	BUG_ON(gpio >= gc->ngpio);
	वापस xlp_gpio_get_reg(priv->gpio_paddrv, gpio);
पूर्ण

अटल व्योम xlp_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित gpio, पूर्णांक state)
अणु
	काष्ठा xlp_gpio_priv *priv = gpiochip_get_data(gc);

	BUG_ON(gpio >= gc->ngpio);
	xlp_gpio_set_reg(priv->gpio_paddrv, gpio, state);
पूर्ण

अटल स्थिर काष्ठा of_device_id xlp_gpio_of_ids[] = अणु
	अणु
		.compatible = "netlogic,xlp832-gpio",
		.data	    = (व्योम *)XLP_GPIO_VARIANT_XLP832,
	पूर्ण,
	अणु
		.compatible = "netlogic,xlp316-gpio",
		.data	    = (व्योम *)XLP_GPIO_VARIANT_XLP316,
	पूर्ण,
	अणु
		.compatible = "netlogic,xlp208-gpio",
		.data	    = (व्योम *)XLP_GPIO_VARIANT_XLP208,
	पूर्ण,
	अणु
		.compatible = "netlogic,xlp980-gpio",
		.data	    = (व्योम *)XLP_GPIO_VARIANT_XLP980,
	पूर्ण,
	अणु
		.compatible = "netlogic,xlp532-gpio",
		.data	    = (व्योम *)XLP_GPIO_VARIANT_XLP532,
	पूर्ण,
	अणु
		.compatible = "brcm,vulcan-gpio",
		.data	    = (व्योम *)GPIO_VARIANT_VULCAN,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xlp_gpio_of_ids);

अटल पूर्णांक xlp_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_chip *gc;
	काष्ठा gpio_irq_chip *girq;
	काष्ठा xlp_gpio_priv *priv;
	व्योम __iomem *gpio_base;
	पूर्णांक irq_base, irq, err;
	पूर्णांक ngpio;
	u32 soc_type;

	priv = devm_kzalloc(&pdev->dev,	माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	gpio_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(gpio_base))
		वापस PTR_ERR(gpio_base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	अगर (pdev->dev.of_node) अणु
		soc_type = (uपूर्णांकptr_t)of_device_get_match_data(&pdev->dev);
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा acpi_device_id *acpi_id;

		acpi_id = acpi_match_device(pdev->dev.driver->acpi_match_table,
						&pdev->dev);
		अगर (!acpi_id || !acpi_id->driver_data) अणु
			dev_err(&pdev->dev, "Unable to match ACPI ID\n");
			वापस -ENODEV;
		पूर्ण
		soc_type = (uपूर्णांकptr_t) acpi_id->driver_data;
	पूर्ण

	चयन (soc_type) अणु
	हाल XLP_GPIO_VARIANT_XLP832:
		priv->gpio_out_en = gpio_base + GPIO_OUTPUT_EN;
		priv->gpio_paddrv = gpio_base + GPIO_PADDRV;
		priv->gpio_पूर्णांकr_stat = gpio_base + GPIO_INT_STAT;
		priv->gpio_पूर्णांकr_type = gpio_base + GPIO_INT_TYPE;
		priv->gpio_पूर्णांकr_pol = gpio_base + GPIO_INT_POL;
		priv->gpio_पूर्णांकr_en = gpio_base + GPIO_INT_EN00;
		ngpio = 41;
		अवरोध;
	हाल XLP_GPIO_VARIANT_XLP208:
	हाल XLP_GPIO_VARIANT_XLP316:
		priv->gpio_out_en = gpio_base + GPIO_OUTPUT_EN;
		priv->gpio_paddrv = gpio_base + GPIO_PADDRV;
		priv->gpio_पूर्णांकr_stat = gpio_base + GPIO_3XX_INT_STAT;
		priv->gpio_पूर्णांकr_type = gpio_base + GPIO_3XX_INT_TYPE;
		priv->gpio_पूर्णांकr_pol = gpio_base + GPIO_3XX_INT_POL;
		priv->gpio_पूर्णांकr_en = gpio_base + GPIO_3XX_INT_EN00;

		ngpio = (soc_type == XLP_GPIO_VARIANT_XLP208) ? 42 : 57;
		अवरोध;
	हाल XLP_GPIO_VARIANT_XLP980:
	हाल XLP_GPIO_VARIANT_XLP532:
	हाल GPIO_VARIANT_VULCAN:
		priv->gpio_out_en = gpio_base + GPIO_9XX_OUTPUT_EN;
		priv->gpio_paddrv = gpio_base + GPIO_9XX_PADDRV;
		priv->gpio_पूर्णांकr_stat = gpio_base + GPIO_9XX_INT_STAT;
		priv->gpio_पूर्णांकr_type = gpio_base + GPIO_9XX_INT_TYPE;
		priv->gpio_पूर्णांकr_pol = gpio_base + GPIO_9XX_INT_POL;
		priv->gpio_पूर्णांकr_en = gpio_base + GPIO_9XX_INT_EN00;

		अगर (soc_type == XLP_GPIO_VARIANT_XLP980)
			ngpio = 66;
		अन्यथा अगर (soc_type == XLP_GPIO_VARIANT_XLP532)
			ngpio = 67;
		अन्यथा
			ngpio = 70;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unknown Processor type!\n");
		वापस -ENODEV;
	पूर्ण

	biपंचांगap_zero(priv->gpio_enabled_mask, XLP_MAX_NR_GPIO);

	gc = &priv->chip;

	gc->owner = THIS_MODULE;
	gc->label = dev_name(&pdev->dev);
	gc->base = 0;
	gc->parent = &pdev->dev;
	gc->ngpio = ngpio;
	gc->of_node = pdev->dev.of_node;
	gc->direction_output = xlp_gpio_dir_output;
	gc->direction_input = xlp_gpio_dir_input;
	gc->set = xlp_gpio_set;
	gc->get = xlp_gpio_get;

	spin_lock_init(&priv->lock);

	/* XLP(MIPS) has fixed range क्रम GPIO IRQs, Vulcan(ARM64) करोes not */
	अगर (soc_type != GPIO_VARIANT_VULCAN) अणु
		irq_base = devm_irq_alloc_descs(&pdev->dev, -1,
						XLP_GPIO_IRQ_BASE,
						gc->ngpio, 0);
		अगर (irq_base < 0) अणु
			dev_err(&pdev->dev, "Failed to allocate IRQ numbers\n");
			वापस irq_base;
		पूर्ण
	पूर्ण अन्यथा अणु
		irq_base = 0;
	पूर्ण

	girq = &gc->irq;
	girq->chip = &xlp_gpio_irq_chip;
	girq->parent_handler = xlp_gpio_generic_handler;
	girq->num_parents = 1;
	girq->parents = devm_kसुस्मृति(&pdev->dev, 1,
				     माप(*girq->parents),
				     GFP_KERNEL);
	अगर (!girq->parents)
		वापस -ENOMEM;
	girq->parents[0] = irq;
	girq->first = irq_base;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_level_irq;

	err = gpiochip_add_data(gc, priv);
	अगर (err < 0)
		वापस err;

	dev_info(&pdev->dev, "registered %d GPIOs\n", gc->ngpio);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id xlp_gpio_acpi_match[] = अणु
	अणु "BRCM9006", GPIO_VARIANT_VULCAN पूर्ण,
	अणु "CAV9006",  GPIO_VARIANT_VULCAN पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, xlp_gpio_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver xlp_gpio_driver = अणु
	.driver		= अणु
		.name	= "xlp-gpio",
		.of_match_table = xlp_gpio_of_ids,
		.acpi_match_table = ACPI_PTR(xlp_gpio_acpi_match),
	पूर्ण,
	.probe		= xlp_gpio_probe,
पूर्ण;
module_platक्रमm_driver(xlp_gpio_driver);

MODULE_AUTHOR("Kamlakant Patel <kamlakant.patel@broadcom.com>");
MODULE_AUTHOR("Ganesan Ramalingam <ganesanr@broadcom.com>");
MODULE_DESCRIPTION("Netlogic XLP GPIO Driver");
MODULE_LICENSE("GPL v2");
