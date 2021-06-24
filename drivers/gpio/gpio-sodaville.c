<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  GPIO पूर्णांकerface क्रम Intel Sodaville SoCs.
 *
 *  Copyright (c) 2010, 2011 Intel Corporation
 *
 *  Author: Hans J. Koch <hjk@linutronix.de>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा DRV_NAME		"sdv_gpio"
#घोषणा SDV_NUM_PUB_GPIOS	12
#घोषणा PCI_DEVICE_ID_SDV_GPIO	0x2e67
#घोषणा GPIO_BAR		0

#घोषणा GPOUTR		0x00
#घोषणा GPOER		0x04
#घोषणा GPINR		0x08

#घोषणा GPSTR		0x0c
#घोषणा GPIT1R0		0x10
#घोषणा GPIO_INT	0x14
#घोषणा GPIT1R1		0x18

#घोषणा GPMUXCTL	0x1c

काष्ठा sdv_gpio_chip_data अणु
	पूर्णांक irq_base;
	व्योम __iomem *gpio_pub_base;
	काष्ठा irq_करोमुख्य *id;
	काष्ठा irq_chip_generic *gc;
	काष्ठा gpio_chip chip;
पूर्ण;

अटल पूर्णांक sdv_gpio_pub_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा sdv_gpio_chip_data *sd = gc->निजी;
	व्योम __iomem *type_reg;
	u32 reg;

	अगर (d->hwirq < 8)
		type_reg = sd->gpio_pub_base + GPIT1R0;
	अन्यथा
		type_reg = sd->gpio_pub_base + GPIT1R1;

	reg = पढ़ोl(type_reg);

	चयन (type) अणु
	हाल IRQ_TYPE_LEVEL_HIGH:
		reg &= ~BIT(4 * (d->hwirq % 8));
		अवरोध;

	हाल IRQ_TYPE_LEVEL_LOW:
		reg |= BIT(4 * (d->hwirq % 8));
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(reg, type_reg);
	वापस 0;
पूर्ण

अटल irqवापस_t sdv_gpio_pub_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sdv_gpio_chip_data *sd = data;
	अचिन्हित दीर्घ irq_stat = पढ़ोl(sd->gpio_pub_base + GPSTR);
	पूर्णांक irq_bit;

	irq_stat &= पढ़ोl(sd->gpio_pub_base + GPIO_INT);
	अगर (!irq_stat)
		वापस IRQ_NONE;

	क्रम_each_set_bit(irq_bit, &irq_stat, 32)
		generic_handle_irq(irq_find_mapping(sd->id, irq_bit));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sdv_xlate(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *node,
		स्थिर u32 *पूर्णांकspec, u32 पूर्णांकsize, irq_hw_number_t *out_hwirq,
		u32 *out_type)
अणु
	u32 line, type;

	अगर (node != irq_करोमुख्य_get_of_node(h))
		वापस -EINVAL;

	अगर (पूर्णांकsize < 2)
		वापस -EINVAL;

	line = *पूर्णांकspec;
	*out_hwirq = line;

	पूर्णांकspec++;
	type = *पूर्णांकspec;

	चयन (type) अणु
	हाल IRQ_TYPE_LEVEL_LOW:
	हाल IRQ_TYPE_LEVEL_HIGH:
		*out_type = type;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops irq_करोमुख्य_sdv_ops = अणु
	.xlate = sdv_xlate,
पूर्ण;

अटल पूर्णांक sdv_रेजिस्टर_irqsupport(काष्ठा sdv_gpio_chip_data *sd,
		काष्ठा pci_dev *pdev)
अणु
	काष्ठा irq_chip_type *ct;
	पूर्णांक ret;

	sd->irq_base = devm_irq_alloc_descs(&pdev->dev, -1, 0,
					    SDV_NUM_PUB_GPIOS, -1);
	अगर (sd->irq_base < 0)
		वापस sd->irq_base;

	/* mask + ACK all पूर्णांकerrupt sources */
	ग_लिखोl(0, sd->gpio_pub_base + GPIO_INT);
	ग_लिखोl((1 << 11) - 1, sd->gpio_pub_base + GPSTR);

	ret = devm_request_irq(&pdev->dev, pdev->irq,
			       sdv_gpio_pub_irq_handler, IRQF_SHARED,
			       "sdv_gpio", sd);
	अगर (ret)
		वापस ret;

	/*
	 * This gpio irq controller latches level irqs. Testing shows that अगर
	 * we unmask & ACK the IRQ beक्रमe the source of the पूर्णांकerrupt is gone
	 * then the पूर्णांकerrupt is active again.
	 */
	sd->gc = devm_irq_alloc_generic_chip(&pdev->dev, "sdv-gpio", 1,
					     sd->irq_base,
					     sd->gpio_pub_base,
					     handle_fasteoi_irq);
	अगर (!sd->gc)
		वापस -ENOMEM;

	sd->gc->निजी = sd;
	ct = sd->gc->chip_types;
	ct->type = IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW;
	ct->regs.eoi = GPSTR;
	ct->regs.mask = GPIO_INT;
	ct->chip.irq_mask = irq_gc_mask_clr_bit;
	ct->chip.irq_unmask = irq_gc_mask_set_bit;
	ct->chip.irq_eoi = irq_gc_eoi;
	ct->chip.irq_set_type = sdv_gpio_pub_set_type;

	irq_setup_generic_chip(sd->gc, IRQ_MSK(SDV_NUM_PUB_GPIOS),
			IRQ_GC_INIT_MASK_CACHE, IRQ_NOREQUEST,
			IRQ_LEVEL | IRQ_NOPROBE);

	sd->id = irq_करोमुख्य_add_legacy(pdev->dev.of_node, SDV_NUM_PUB_GPIOS,
				sd->irq_base, 0, &irq_करोमुख्य_sdv_ops, sd);
	अगर (!sd->id)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक sdv_gpio_probe(काष्ठा pci_dev *pdev,
					स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा sdv_gpio_chip_data *sd;
	पूर्णांक ret;
	u32 mux_val;

	sd = devm_kzalloc(&pdev->dev, माप(*sd), GFP_KERNEL);
	अगर (!sd)
		वापस -ENOMEM;

	ret = pcim_enable_device(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't enable device.\n");
		वापस ret;
	पूर्ण

	ret = pcim_iomap_regions(pdev, 1 << GPIO_BAR, DRV_NAME);
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't alloc PCI BAR #%d\n", GPIO_BAR);
		वापस ret;
	पूर्ण

	sd->gpio_pub_base = pcim_iomap_table(pdev)[GPIO_BAR];

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "intel,muxctl", &mux_val);
	अगर (!ret)
		ग_लिखोl(mux_val, sd->gpio_pub_base + GPMUXCTL);

	ret = bgpio_init(&sd->chip, &pdev->dev, 4,
			sd->gpio_pub_base + GPINR, sd->gpio_pub_base + GPOUTR,
			शून्य, sd->gpio_pub_base + GPOER, शून्य, 0);
	अगर (ret)
		वापस ret;

	sd->chip.ngpio = SDV_NUM_PUB_GPIOS;

	ret = devm_gpiochip_add_data(&pdev->dev, &sd->chip, sd);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "gpiochip_add() failed.\n");
		वापस ret;
	पूर्ण

	ret = sdv_रेजिस्टर_irqsupport(sd, pdev);
	अगर (ret)
		वापस ret;

	pci_set_drvdata(pdev, sd);
	dev_info(&pdev->dev, "Sodaville GPIO driver registered.\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_device_id sdv_gpio_pci_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_SDV_GPIO) पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver sdv_gpio_driver = अणु
	.driver = अणु
		.suppress_bind_attrs = true,
	पूर्ण,
	.name = DRV_NAME,
	.id_table = sdv_gpio_pci_ids,
	.probe = sdv_gpio_probe,
पूर्ण;
builtin_pci_driver(sdv_gpio_driver);
