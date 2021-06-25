<शैली गुरु>
/*
 * Multiplexed-IRQs driver क्रम TS-4800's FPGA
 *
 * Copyright (c) 2015 - Savoir-faire Linux
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा IRQ_MASK        0x4
#घोषणा IRQ_STATUS      0x8

काष्ठा ts4800_irq_data अणु
	व्योम __iomem            *base;
	काष्ठा irq_करोमुख्य       *करोमुख्य;
	काष्ठा irq_chip         irq_chip;
पूर्ण;

अटल व्योम ts4800_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा ts4800_irq_data *data = irq_data_get_irq_chip_data(d);
	u16 reg = पढ़ोw(data->base + IRQ_MASK);
	u16 mask = 1 << d->hwirq;

	ग_लिखोw(reg | mask, data->base + IRQ_MASK);
पूर्ण

अटल व्योम ts4800_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा ts4800_irq_data *data = irq_data_get_irq_chip_data(d);
	u16 reg = पढ़ोw(data->base + IRQ_MASK);
	u16 mask = 1 << d->hwirq;

	ग_लिखोw(reg & ~mask, data->base + IRQ_MASK);
पूर्ण

अटल पूर्णांक ts4800_irqकरोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
				irq_hw_number_t hwirq)
अणु
	काष्ठा ts4800_irq_data *data = d->host_data;

	irq_set_chip_and_handler(irq, &data->irq_chip, handle_simple_irq);
	irq_set_chip_data(irq, data);
	irq_set_noprobe(irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops ts4800_ic_ops = अणु
	.map = ts4800_irqकरोमुख्य_map,
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल व्योम ts4800_ic_chained_handle_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा ts4800_irq_data *data = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	u16 status = पढ़ोw(data->base + IRQ_STATUS);

	chained_irq_enter(chip, desc);

	अगर (unlikely(status == 0)) अणु
		handle_bad_irq(desc);
		जाओ out;
	पूर्ण

	करो अणु
		अचिन्हित पूर्णांक bit = __ffs(status);
		पूर्णांक irq = irq_find_mapping(data->करोमुख्य, bit);

		status &= ~(1 << bit);
		generic_handle_irq(irq);
	पूर्ण जबतक (status);

out:
	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक ts4800_ic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा ts4800_irq_data *data;
	काष्ठा irq_chip *irq_chip;
	काष्ठा resource *res;
	पूर्णांक parent_irq;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	data->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(data->base))
		वापस PTR_ERR(data->base);

	ग_लिखोw(0xFFFF, data->base + IRQ_MASK);

	parent_irq = irq_of_parse_and_map(node, 0);
	अगर (!parent_irq) अणु
		dev_err(&pdev->dev, "failed to get parent IRQ\n");
		वापस -EINVAL;
	पूर्ण

	irq_chip = &data->irq_chip;
	irq_chip->name = dev_name(&pdev->dev);
	irq_chip->irq_mask = ts4800_irq_mask;
	irq_chip->irq_unmask = ts4800_irq_unmask;

	data->करोमुख्य = irq_करोमुख्य_add_linear(node, 8, &ts4800_ic_ops, data);
	अगर (!data->करोमुख्य) अणु
		dev_err(&pdev->dev, "cannot add IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	irq_set_chained_handler_and_data(parent_irq,
					 ts4800_ic_chained_handle_irq, data);

	platक्रमm_set_drvdata(pdev, data);

	वापस 0;
पूर्ण

अटल पूर्णांक ts4800_ic_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ts4800_irq_data *data = platक्रमm_get_drvdata(pdev);

	irq_करोमुख्य_हटाओ(data->करोमुख्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ts4800_ic_of_match[] = अणु
	अणु .compatible = "technologic,ts4800-irqc", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ts4800_ic_of_match);

अटल काष्ठा platक्रमm_driver ts4800_ic_driver = अणु
	.probe  = ts4800_ic_probe,
	.हटाओ = ts4800_ic_हटाओ,
	.driver = अणु
		.name = "ts4800-irqc",
		.of_match_table = ts4800_ic_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ts4800_ic_driver);

MODULE_AUTHOR("Damien Riegel <damien.riegel@savoirfairelinux.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:ts4800_irqc");
