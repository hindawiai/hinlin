<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AppliedMicro X-Gene SoC GPIO-Standby Driver
 *
 * Copyright (c) 2014, Applied Micro Circuits Corporation
 * Author:	Tin Huynh <tnhuynh@apm.com>.
 *		Y Vo <yvo@apm.com>.
 *		Quan Nguyen <qnguyen@apm.com>.
 */

#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/acpi.h>

#समावेश "gpiolib.h"
#समावेश "gpiolib-acpi.h"

/* Common property names */
#घोषणा XGENE_NIRQ_PROPERTY		"apm,nr-irqs"
#घोषणा XGENE_NGPIO_PROPERTY		"apm,nr-gpios"
#घोषणा XGENE_IRQ_START_PROPERTY	"apm,irq-start"

#घोषणा XGENE_Dभग्न_उच्च_NGPIO		22
#घोषणा XGENE_Dभग्न_उच्च_NIRQ		6
#घोषणा XGENE_DFLT_IRQ_START_PIN	8
#घोषणा GPIO_MASK(x)			(1U << ((x) % 32))

#घोषणा MPA_GPIO_INT_LVL		0x0290
#घोषणा MPA_GPIO_OE_ADDR		0x029c
#घोषणा MPA_GPIO_OUT_ADDR		0x02a0
#घोषणा MPA_GPIO_IN_ADDR 		0x02a4
#घोषणा MPA_GPIO_SEL_LO 		0x0294

#घोषणा GPIO_INT_LEVEL_H	0x000001
#घोषणा GPIO_INT_LEVEL_L	0x000000

/**
 * काष्ठा xgene_gpio_sb - GPIO-Standby निजी data काष्ठाure.
 * @gc:				memory-mapped GPIO controllers.
 * @regs:			GPIO रेजिस्टर base offset
 * @irq_करोमुख्य:			GPIO पूर्णांकerrupt करोमुख्य
 * @irq_start:			GPIO pin that start support पूर्णांकerrupt
 * @nirq:			Number of GPIO pins that supports पूर्णांकerrupt
 * @parent_irq_base:		Start parent HWIRQ
 */
काष्ठा xgene_gpio_sb अणु
	काष्ठा gpio_chip	gc;
	व्योम __iomem		*regs;
	काष्ठा irq_करोमुख्य	*irq_करोमुख्य;
	u16			irq_start;
	u16			nirq;
	u16			parent_irq_base;
पूर्ण;

#घोषणा HWIRQ_TO_GPIO(priv, hwirq) ((hwirq) + (priv)->irq_start)
#घोषणा GPIO_TO_HWIRQ(priv, gpio) ((gpio) - (priv)->irq_start)

अटल व्योम xgene_gpio_set_bit(काष्ठा gpio_chip *gc,
				व्योम __iomem *reg, u32 gpio, पूर्णांक val)
अणु
	u32 data;

	data = gc->पढ़ो_reg(reg);
	अगर (val)
		data |= GPIO_MASK(gpio);
	अन्यथा
		data &= ~GPIO_MASK(gpio);
	gc->ग_लिखो_reg(reg, data);
पूर्ण

अटल पूर्णांक xgene_gpio_sb_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा xgene_gpio_sb *priv = irq_data_get_irq_chip_data(d);
	पूर्णांक gpio = HWIRQ_TO_GPIO(priv, d->hwirq);
	पूर्णांक lvl_type = GPIO_INT_LEVEL_H;

	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_EDGE_RISING:
	हाल IRQ_TYPE_LEVEL_HIGH:
		lvl_type = GPIO_INT_LEVEL_H;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
	हाल IRQ_TYPE_LEVEL_LOW:
		lvl_type = GPIO_INT_LEVEL_L;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	xgene_gpio_set_bit(&priv->gc, priv->regs + MPA_GPIO_SEL_LO,
			gpio * 2, 1);
	xgene_gpio_set_bit(&priv->gc, priv->regs + MPA_GPIO_INT_LVL,
			d->hwirq, lvl_type);

	/* Propagate IRQ type setting to parent */
	अगर (type & IRQ_TYPE_EDGE_BOTH)
		वापस irq_chip_set_type_parent(d, IRQ_TYPE_EDGE_RISING);
	अन्यथा
		वापस irq_chip_set_type_parent(d, IRQ_TYPE_LEVEL_HIGH);
पूर्ण

अटल काष्ठा irq_chip xgene_gpio_sb_irq_chip = अणु
	.name           = "sbgpio",
	.irq_eoi	= irq_chip_eoi_parent,
	.irq_mask       = irq_chip_mask_parent,
	.irq_unmask     = irq_chip_unmask_parent,
	.irq_set_type   = xgene_gpio_sb_irq_set_type,
पूर्ण;

अटल पूर्णांक xgene_gpio_sb_to_irq(काष्ठा gpio_chip *gc, u32 gpio)
अणु
	काष्ठा xgene_gpio_sb *priv = gpiochip_get_data(gc);
	काष्ठा irq_fwspec fwspec;

	अगर ((gpio < priv->irq_start) ||
			(gpio > HWIRQ_TO_GPIO(priv, priv->nirq)))
		वापस -ENXIO;

	fwspec.fwnode = gc->parent->fwnode;
	fwspec.param_count = 2;
	fwspec.param[0] = GPIO_TO_HWIRQ(priv, gpio);
	fwspec.param[1] = IRQ_TYPE_EDGE_RISING;
	वापस irq_create_fwspec_mapping(&fwspec);
पूर्ण

अटल पूर्णांक xgene_gpio_sb_करोमुख्य_activate(काष्ठा irq_करोमुख्य *d,
					 काष्ठा irq_data *irq_data,
					 bool reserve)
अणु
	काष्ठा xgene_gpio_sb *priv = d->host_data;
	u32 gpio = HWIRQ_TO_GPIO(priv, irq_data->hwirq);
	पूर्णांक ret;

	ret = gpiochip_lock_as_irq(&priv->gc, gpio);
	अगर (ret) अणु
		dev_err(priv->gc.parent,
		"Unable to configure XGene GPIO standby pin %d as IRQ\n",
				gpio);
		वापस ret;
	पूर्ण

	xgene_gpio_set_bit(&priv->gc, priv->regs + MPA_GPIO_SEL_LO,
			gpio * 2, 1);
	वापस 0;
पूर्ण

अटल व्योम xgene_gpio_sb_करोमुख्य_deactivate(काष्ठा irq_करोमुख्य *d,
		काष्ठा irq_data *irq_data)
अणु
	काष्ठा xgene_gpio_sb *priv = d->host_data;
	u32 gpio = HWIRQ_TO_GPIO(priv, irq_data->hwirq);

	gpiochip_unlock_as_irq(&priv->gc, gpio);
	xgene_gpio_set_bit(&priv->gc, priv->regs + MPA_GPIO_SEL_LO,
			gpio * 2, 0);
पूर्ण

अटल पूर्णांक xgene_gpio_sb_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d,
		काष्ठा irq_fwspec *fwspec,
		अचिन्हित दीर्घ *hwirq,
		अचिन्हित पूर्णांक *type)
अणु
	काष्ठा xgene_gpio_sb *priv = d->host_data;

	अगर ((fwspec->param_count != 2) ||
		(fwspec->param[0] >= priv->nirq))
		वापस -EINVAL;
	*hwirq = fwspec->param[0];
	*type = fwspec->param[1];
	वापस 0;
पूर्ण

अटल पूर्णांक xgene_gpio_sb_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
					अचिन्हित पूर्णांक virq,
					अचिन्हित पूर्णांक nr_irqs, व्योम *data)
अणु
	काष्ठा irq_fwspec *fwspec = data;
	काष्ठा irq_fwspec parent_fwspec;
	काष्ठा xgene_gpio_sb *priv = करोमुख्य->host_data;
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक i;

	hwirq = fwspec->param[0];
	क्रम (i = 0; i < nr_irqs; i++)
		irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq + i, hwirq + i,
				&xgene_gpio_sb_irq_chip, priv);

	parent_fwspec.fwnode = करोमुख्य->parent->fwnode;
	अगर (is_of_node(parent_fwspec.fwnode)) अणु
		parent_fwspec.param_count = 3;
		parent_fwspec.param[0] = 0;/* SPI */
		/* Skip SGIs and PPIs*/
		parent_fwspec.param[1] = hwirq + priv->parent_irq_base - 32;
		parent_fwspec.param[2] = fwspec->param[1];
	पूर्ण अन्यथा अगर (is_fwnode_irqchip(parent_fwspec.fwnode)) अणु
		parent_fwspec.param_count = 2;
		parent_fwspec.param[0] = hwirq + priv->parent_irq_base;
		parent_fwspec.param[1] = fwspec->param[1];
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs,
			&parent_fwspec);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops xgene_gpio_sb_करोमुख्य_ops = अणु
	.translate      = xgene_gpio_sb_करोमुख्य_translate,
	.alloc          = xgene_gpio_sb_करोमुख्य_alloc,
	.मुक्त           = irq_करोमुख्य_मुक्त_irqs_common,
	.activate	= xgene_gpio_sb_करोमुख्य_activate,
	.deactivate	= xgene_gpio_sb_करोमुख्य_deactivate,
पूर्ण;

अटल पूर्णांक xgene_gpio_sb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgene_gpio_sb *priv;
	पूर्णांक ret;
	व्योम __iomem *regs;
	काष्ठा irq_करोमुख्य *parent_करोमुख्य = शून्य;
	u32 val32;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	priv->regs = regs;

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret > 0) अणु
		priv->parent_irq_base = irq_get_irq_data(ret)->hwirq;
		parent_करोमुख्य = irq_get_irq_data(ret)->करोमुख्य;
	पूर्ण
	अगर (!parent_करोमुख्य) अणु
		dev_err(&pdev->dev, "unable to obtain parent domain\n");
		वापस -ENODEV;
	पूर्ण

	ret = bgpio_init(&priv->gc, &pdev->dev, 4,
			regs + MPA_GPIO_IN_ADDR,
			regs + MPA_GPIO_OUT_ADDR, शून्य,
			regs + MPA_GPIO_OE_ADDR, शून्य, 0);
        अगर (ret)
                वापस ret;

	priv->gc.to_irq = xgene_gpio_sb_to_irq;

	/* Retrieve start irq pin, use शेष अगर property not found */
	priv->irq_start = XGENE_DFLT_IRQ_START_PIN;
	अगर (!device_property_पढ़ो_u32(&pdev->dev,
					XGENE_IRQ_START_PROPERTY, &val32))
		priv->irq_start = val32;

	/* Retrieve number irqs, use शेष अगर property not found */
	priv->nirq = XGENE_Dभग्न_उच्च_NIRQ;
	अगर (!device_property_पढ़ो_u32(&pdev->dev, XGENE_NIRQ_PROPERTY, &val32))
		priv->nirq = val32;

	/* Retrieve number gpio, use शेष अगर property not found */
	priv->gc.ngpio = XGENE_Dभग्न_उच्च_NGPIO;
	अगर (!device_property_पढ़ो_u32(&pdev->dev, XGENE_NGPIO_PROPERTY, &val32))
		priv->gc.ngpio = val32;

	dev_info(&pdev->dev, "Support %d gpios, %d irqs start from pin %d\n",
			priv->gc.ngpio, priv->nirq, priv->irq_start);

	platक्रमm_set_drvdata(pdev, priv);

	priv->irq_करोमुख्य = irq_करोमुख्य_create_hierarchy(parent_करोमुख्य,
					0, priv->nirq, pdev->dev.fwnode,
					&xgene_gpio_sb_करोमुख्य_ops, priv);
	अगर (!priv->irq_करोमुख्य)
		वापस -ENODEV;

	priv->gc.irq.करोमुख्य = priv->irq_करोमुख्य;

	ret = devm_gpiochip_add_data(&pdev->dev, &priv->gc, priv);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"failed to register X-Gene GPIO Standby driver\n");
		irq_करोमुख्य_हटाओ(priv->irq_करोमुख्य);
		वापस ret;
	पूर्ण

	dev_info(&pdev->dev, "X-Gene GPIO Standby driver registered\n");

	/* Register पूर्णांकerrupt handlers क्रम GPIO संकेतed ACPI Events */
	acpi_gpiochip_request_पूर्णांकerrupts(&priv->gc);

	वापस ret;
पूर्ण

अटल पूर्णांक xgene_gpio_sb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgene_gpio_sb *priv = platक्रमm_get_drvdata(pdev);

	acpi_gpiochip_मुक्त_पूर्णांकerrupts(&priv->gc);

	irq_करोमुख्य_हटाओ(priv->irq_करोमुख्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id xgene_gpio_sb_of_match[] = अणु
	अणु.compatible = "apm,xgene-gpio-sb", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xgene_gpio_sb_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id xgene_gpio_sb_acpi_match[] = अणु
	अणु"APMC0D15", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, xgene_gpio_sb_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver xgene_gpio_sb_driver = अणु
	.driver = अणु
		   .name = "xgene-gpio-sb",
		   .of_match_table = xgene_gpio_sb_of_match,
		   .acpi_match_table = ACPI_PTR(xgene_gpio_sb_acpi_match),
		   पूर्ण,
	.probe = xgene_gpio_sb_probe,
	.हटाओ = xgene_gpio_sb_हटाओ,
पूर्ण;
module_platक्रमm_driver(xgene_gpio_sb_driver);

MODULE_AUTHOR("AppliedMicro");
MODULE_DESCRIPTION("APM X-Gene GPIO Standby driver");
MODULE_LICENSE("GPL");
