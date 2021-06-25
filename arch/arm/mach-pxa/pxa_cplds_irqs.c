<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Intel Reference Systems cplds
 *
 * Copyright (C) 2014 Robert Jarzmik
 *
 * Cplds motherboard driver, supporting lubbock and मुख्यstone SoC board.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>

#घोषणा FPGA_IRQ_MASK_EN 0x0
#घोषणा FPGA_IRQ_SET_CLR 0x10

#घोषणा CPLDS_NB_IRQ	32

काष्ठा cplds अणु
	व्योम __iomem *base;
	पूर्णांक irq;
	अचिन्हित पूर्णांक irq_mask;
	काष्ठा gpio_desc *gpio0;
	काष्ठा irq_करोमुख्य *irqकरोमुख्य;
पूर्ण;

अटल irqवापस_t cplds_irq_handler(पूर्णांक in_irq, व्योम *d)
अणु
	काष्ठा cplds *fpga = d;
	अचिन्हित दीर्घ pending;
	अचिन्हित पूर्णांक bit;

	करो अणु
		pending = पढ़ोl(fpga->base + FPGA_IRQ_SET_CLR) & fpga->irq_mask;
		क्रम_each_set_bit(bit, &pending, CPLDS_NB_IRQ) अणु
			generic_handle_irq(irq_find_mapping(fpga->irqकरोमुख्य,
							    bit));
		पूर्ण
	पूर्ण जबतक (pending);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम cplds_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा cplds *fpga = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक cplds_irq = irqd_to_hwirq(d);
	अचिन्हित पूर्णांक bit = BIT(cplds_irq);

	fpga->irq_mask &= ~bit;
	ग_लिखोl(fpga->irq_mask, fpga->base + FPGA_IRQ_MASK_EN);
पूर्ण

अटल व्योम cplds_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा cplds *fpga = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक cplds_irq = irqd_to_hwirq(d);
	अचिन्हित पूर्णांक set, bit = BIT(cplds_irq);

	set = पढ़ोl(fpga->base + FPGA_IRQ_SET_CLR);
	ग_लिखोl(set & ~bit, fpga->base + FPGA_IRQ_SET_CLR);

	fpga->irq_mask |= bit;
	ग_लिखोl(fpga->irq_mask, fpga->base + FPGA_IRQ_MASK_EN);
पूर्ण

अटल काष्ठा irq_chip cplds_irq_chip = अणु
	.name		= "pxa_cplds",
	.irq_ack	= cplds_irq_mask,
	.irq_mask	= cplds_irq_mask,
	.irq_unmask	= cplds_irq_unmask,
	.flags		= IRQCHIP_MASK_ON_SUSPEND | IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

अटल पूर्णांक cplds_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
				   irq_hw_number_t hwirq)
अणु
	काष्ठा cplds *fpga = d->host_data;

	irq_set_chip_and_handler(irq, &cplds_irq_chip, handle_level_irq);
	irq_set_chip_data(irq, fpga);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops cplds_irq_करोमुख्य_ops = अणु
	.xlate = irq_करोमुख्य_xlate_twocell,
	.map = cplds_irq_करोमुख्य_map,
पूर्ण;

अटल पूर्णांक cplds_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cplds *fpga = platक्रमm_get_drvdata(pdev);

	ग_लिखोl(fpga->irq_mask, fpga->base + FPGA_IRQ_MASK_EN);

	वापस 0;
पूर्ण

अटल पूर्णांक cplds_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा cplds *fpga;
	पूर्णांक ret;
	पूर्णांक base_irq;
	अचिन्हित दीर्घ irqflags = 0;

	fpga = devm_kzalloc(&pdev->dev, माप(*fpga), GFP_KERNEL);
	अगर (!fpga)
		वापस -ENOMEM;

	fpga->irq = platक्रमm_get_irq(pdev, 0);
	अगर (fpga->irq <= 0)
		वापस fpga->irq;

	base_irq = platक्रमm_get_irq(pdev, 1);
	अगर (base_irq < 0) अणु
		base_irq = 0;
	पूर्ण अन्यथा अणु
		ret = devm_irq_alloc_descs(&pdev->dev, base_irq, base_irq, CPLDS_NB_IRQ, 0);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	fpga->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(fpga->base))
		वापस PTR_ERR(fpga->base);

	platक्रमm_set_drvdata(pdev, fpga);

	ग_लिखोl(fpga->irq_mask, fpga->base + FPGA_IRQ_MASK_EN);
	ग_लिखोl(0, fpga->base + FPGA_IRQ_SET_CLR);

	irqflags = irq_get_trigger_type(fpga->irq);
	ret = devm_request_irq(&pdev->dev, fpga->irq, cplds_irq_handler,
			       irqflags, dev_name(&pdev->dev), fpga);
	अगर (ret == -ENOSYS)
		वापस -EPROBE_DEFER;

	अगर (ret) अणु
		dev_err(&pdev->dev, "couldn't request main irq%d: %d\n",
			fpga->irq, ret);
		वापस ret;
	पूर्ण

	irq_set_irq_wake(fpga->irq, 1);
	अगर (base_irq)
		fpga->irqकरोमुख्य = irq_करोमुख्य_add_legacy(pdev->dev.of_node,
							CPLDS_NB_IRQ,
							base_irq, 0,
							&cplds_irq_करोमुख्य_ops,
							fpga);
	अन्यथा
		fpga->irqकरोमुख्य = irq_करोमुख्य_add_linear(pdev->dev.of_node,
							CPLDS_NB_IRQ,
							&cplds_irq_करोमुख्य_ops,
							fpga);
	अगर (!fpga->irqकरोमुख्य)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक cplds_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cplds *fpga = platक्रमm_get_drvdata(pdev);

	irq_set_chip_and_handler(fpga->irq, शून्य, शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cplds_id_table[] = अणु
	अणु .compatible = "intel,lubbock-cplds-irqs", पूर्ण,
	अणु .compatible = "intel,mainstone-cplds-irqs", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cplds_id_table);

अटल काष्ठा platक्रमm_driver cplds_driver = अणु
	.driver		= अणु
		.name	= "pxa_cplds_irqs",
		.of_match_table = of_match_ptr(cplds_id_table),
	पूर्ण,
	.probe		= cplds_probe,
	.हटाओ		= cplds_हटाओ,
	.resume		= cplds_resume,
पूर्ण;

module_platक्रमm_driver(cplds_driver);

MODULE_DESCRIPTION("PXA Cplds interrupts driver");
MODULE_AUTHOR("Robert Jarzmik <robert.jarzmik@free.fr>");
MODULE_LICENSE("GPL");
